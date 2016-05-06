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

#ifndef __DX_SRAM_MGR_H__
#define __DX_SRAM_MGR_H__


#ifndef DX_CC_SRAM_SIZE
#define DX_CC_SRAM_SIZE 4096
#endif

struct dx_drvdata;

/**
 * Address (offset) within CC internal SRAM
 */

typedef uint64_t dx_sram_addr_t;

#define NULL_SRAM_ADDR ((dx_sram_addr_t)-1)

/*!
 * Initializes SRAM pool. 
 * The first X bytes of SRAM are reserved for ROM usage, hence, pool 
 * starts right after X bytes. 
 *  
 * \param drvdata 
 *  
 * \return int Zero for success, negative value otherwise.
 */
int dx_sram_mgr_init(struct dx_drvdata *drvdata);

/*!
 * Uninits SRAM pool.
 * 
 * \param drvdata 
 */
void dx_sram_mgr_fini(struct dx_drvdata *drvdata);

/*!
 * Allocated buffer from SRAM pool. 
 * Note: Caller is responsible to free the LAST allocated buffer. 
 * This function does not taking care of any fragmentation may occur 
 * by the order of calls to alloc/free. 
 * 
 * \param drvdata 
 * \param size The requested bytes to allocate
 */
dx_sram_addr_t dx_sram_mgr_alloc(struct dx_drvdata *drvdata, uint32_t size);

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
	HwDesc_s *seq, unsigned int *seq_len);

#endif /*__DX_SRAM_MGR_H__*/
