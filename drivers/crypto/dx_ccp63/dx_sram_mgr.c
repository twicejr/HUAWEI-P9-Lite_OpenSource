/***************************************************************
*  Copyright 2014 (c) Discretix Technologies Ltd.              *
*  This software is protected by copyright, international      *
*  treaties and various patents. Any copy, reproduction or     *
*  otherwise use of this software must be authorized in a      *
*  license agreement and include this Copyright Notice and any *
*  other notices specified in the license agreement.           *
*  Any redistribution in binary form must be authorized in the *
*  license agreement and include this Copyright Notice and     *
*  any other notices specified in the license agreement and/or *
*  in materials provided with the binary distribution.         *
****************************************************************/

#include "dx_driver.h"
#include "dx_sram_mgr.h"


/**
 * struct dx_sram_mgr_ctx -Internal RAM context manager
 * @sram_free_offset:   the offset to the non-allocated area
 */
struct dx_sram_mgr_ctx {
	dx_sram_addr_t sram_free_offset;
};


/**
 * dx_sram_mgr_fini() - Cleanup SRAM pool.
 * 
 * @drvdata: Associated device driver context
 */
void dx_sram_mgr_fini(struct dx_drvdata *drvdata)
{
	struct dx_sram_mgr_ctx *smgr_ctx = drvdata->sram_mgr_handle;

	/* Free "this" context */
	if (smgr_ctx != NULL) {
		memset(smgr_ctx, 0, sizeof(struct dx_sram_mgr_ctx));
		kfree(smgr_ctx);
	}
}

/**
 * dx_sram_mgr_init() - Initializes SRAM pool. 
 *	The first X bytes of SRAM are reserved for ROM usage, hence, pool 
 *	starts right after X bytes.
 *	Returns zero for success, negative value otherwise.
 * 
 * @drvdata: Associated device driver context
 */
int dx_sram_mgr_init(struct dx_drvdata *drvdata)
{
	struct dx_sram_mgr_ctx *smgr_ctx;
	int rc;

	/* Allocate "this" context */
	drvdata->sram_mgr_handle = kzalloc(
			sizeof(struct dx_sram_mgr_ctx), GFP_KERNEL);
	if (!drvdata->sram_mgr_handle) {
		DX_LOG_ERR("Not enough memory to allocate SRAM_MGR ctx (%zu)\n",
			sizeof(struct dx_sram_mgr_ctx));
		rc = -ENOMEM;
		goto out;
	}
	smgr_ctx = drvdata->sram_mgr_handle;

	/* Pool starts after ROM bytes */
#ifdef DX_HOST_SEP_SRAM_THRESHOLD_REG_OFFSET
	smgr_ctx->sram_free_offset = (dma_addr_t)READ_REGISTER(drvdata->cc_base +
			DX_CC_REG_OFFSET(HOST_RGF, HOST_SEP_SRAM_THRESHOLD));
	if ((smgr_ctx->sram_free_offset & 0x3) != 0) {
		DX_LOG_ERR("Invalid SRAM threshold (addr=0x%08llX)\n",
			smgr_ctx->sram_free_offset);
		rc = -ENODEV;
		goto out;
	}
#else /* No SRAM threshold (not SEP) */
	smgr_ctx->sram_free_offset = 0;
#endif

	return 0;

out:
	dx_sram_mgr_fini(drvdata);
	return rc;
}

/*!
 * Allocated buffer from SRAM pool. 
 * Note: Caller is responsible to free the LAST allocated buffer. 
 * This function does not taking care of any fragmentation may occur 
 * by the order of calls to alloc/free. 
 * 
 * \param drvdata 
 * \param size The requested bytes to allocate
 */
dx_sram_addr_t dx_sram_mgr_alloc(struct dx_drvdata *drvdata, uint32_t size)
{
	struct dx_sram_mgr_ctx *smgr_ctx = drvdata->sram_mgr_handle;
	dx_sram_addr_t p;

	if (unlikely((size & 0x3) != 0)) {
		DX_LOG_ERR("Requested buffer size (%u) is not multiple of 4",
			size);
		return NULL_SRAM_ADDR;
	}
	if (unlikely(size > (DX_CC_SRAM_SIZE - smgr_ctx->sram_free_offset))) {
		DX_LOG_ERR("Not enough space to allocate %u B (at offset %llu)\n",
			size, smgr_ctx->sram_free_offset);
		return NULL_SRAM_ADDR;
	}
	
	p = smgr_ctx->sram_free_offset;
	smgr_ctx->sram_free_offset += size;
	DX_LOG_DEBUG("Allocated %u B @ %u\n", size, (unsigned int)p);
	return p;
}

/**
 * dx_sram_mgr_const2sram_desc() - Create const descriptors sequence to
 *	set values in given array into SRAM. 
 * Note: each const value can't exceed word size.
 * 
 * @src:	  A pointer to array of words to set as consts.
 * @dst:	  The target SRAM buffer to set into
 * @nelements:	  The number of words in "src" array
 * @seq:	  A pointer to the given IN/OUT descriptor sequence
 * @seq_len:	  A pointer to the given IN/OUT sequence length
 */
void dx_sram_mgr_const2sram_desc(
	const uint32_t *src, dx_sram_addr_t dst,
	unsigned int nelement,
	HwDesc_s *seq, unsigned int *seq_len)
{
	uint32_t i;
	unsigned int idx = *seq_len;

	for (i = 0; i < nelement; i++, idx++) {
		HW_DESC_INIT(&seq[idx]);
		HW_DESC_SET_DIN_CONST(&seq[idx], src[i], sizeof(uint32_t));
		HW_DESC_SET_DOUT_SRAM(&seq[idx], dst + (i * sizeof(uint32_t)), sizeof(uint32_t));
		HW_DESC_SET_FLOW_MODE(&seq[idx], BYPASS);
	}

	*seq_len = idx;
}

