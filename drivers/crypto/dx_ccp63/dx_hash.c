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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <crypto/algapi.h>
#include <crypto/hash.h>
#include <crypto/sha.h>
#include <crypto/md5.h>
#include <crypto/internal/hash.h>

#include "dx_config.h"
#include "dx_driver.h"
#include "dx_request_mgr.h"
#include "dx_buffer_mgr.h"
#include "dx_sysfs.h"
#include "dx_hash.h"
#include "dx_sram_mgr.h"

#define DX_MAX_AHASH_SEQ_LEN 12
#define DX_MAX_HASH_OPAD_TMP_KEYS_SIZE MAX(DX_MAX_HASH_BLCK_SIZE, 3 * AES_BLOCK_SIZE)

struct dx_ahash_handle {
	dx_sram_addr_t digest_len_sram_addr; /* const value in SRAM*/
	dx_sram_addr_t larval_digest_sram_addr;   /* const value in SRAM */
	struct list_head ahash_list;
	struct completion init_comp;
};

static const uint32_t digest_len_init[] = {
	0x00000040, 0x00000000, 0x00000000, 0x00000000 };
static const uint32_t md5_init[] = { 
	SHA1_H3, SHA1_H2, SHA1_H1, SHA1_H0 };
static const uint32_t sha1_init[] = { 
	SHA1_H4, SHA1_H3, SHA1_H2, SHA1_H1, SHA1_H0 };
static const uint32_t sha224_init[] = { 
	SHA224_H7, SHA224_H6, SHA224_H5, SHA224_H4,
	SHA224_H3, SHA224_H2, SHA224_H1, SHA224_H0 };
static const uint32_t sha256_init[] = {
	SHA256_H7, SHA256_H6, SHA256_H5, SHA256_H4,
	SHA256_H3, SHA256_H2, SHA256_H1, SHA256_H0 };
#if (DX_DEV_SHA_MAX > 256)
static const uint32_t digest_len_sha512_init[] = { 
	0x00000080, 0x00000000, 0x00000000, 0x00000000 };
static const uint64_t sha384_init[] = {
	SHA384_H7, SHA384_H6, SHA384_H5, SHA384_H4,
	SHA384_H3, SHA384_H2, SHA384_H1, SHA384_H0 };
static const uint64_t sha512_init[] = {
	SHA512_H7, SHA512_H6, SHA512_H5, SHA512_H4,
	SHA512_H3, SHA512_H2, SHA512_H1, SHA512_H0 };
#endif

static void dx_hash_create_data_desc(
	struct ahash_request *areq, 
	unsigned int flow_mode,HwDesc_s desc[],
	bool is_not_last_data,
	unsigned int *seq_size);

static void dx_hash_create_xcbc_setup(
	struct ahash_request *areq, 
	HwDesc_s desc[],
	unsigned int *seq_size);

static void dx_hash_create_cmac_setup(struct ahash_request *areq, 
				  HwDesc_s desc[],
				  unsigned int *seq_size);

struct dx_hash_alg {
	struct list_head entry;
	int ahash_mode;
	int hw_mode;
	int inter_digestsize;
	struct dx_drvdata *drvdata;
	struct ahash_alg ahash_alg;
};


struct ahash_key_req_ctx {
	uint32_t keylen;
	dma_addr_t key_dma_addr;
};

/* ahash per-session context */
struct dx_hash_ctx {
	struct dx_drvdata *drvdata;
	/* holds the origin digest; the digest after "setkey" if HMAC,* 
	   the initial digest if HASH. */
	uint8_t digest_buff[DX_MAX_HASH_DIGEST_SIZE]  ____cacheline_aligned;
	uint8_t opad_tmp_keys_buff[DX_MAX_HASH_OPAD_TMP_KEYS_SIZE]  ____cacheline_aligned;
	dma_addr_t opad_tmp_keys_dma_addr  ____cacheline_aligned;
	dma_addr_t digest_buff_dma_addr;
	/* use for hmac with key large then mode block size */
	struct ahash_key_req_ctx key_params;
	int ahash_mode;
	int hw_mode;
	int inter_digestsize;
	struct completion setkey_comp;
	bool is_hmac;
};

static inline void dx_set_hash_endianity(uint32_t mode, HwDesc_s *desc)
{
	if (unlikely((mode == SEP_HASH_MD5) ||
		(mode == SEP_HASH_SHA384) ||
		(mode == SEP_HASH_SHA512))) {
		HW_DESC_SET_BYTES_SWAP(desc, 1);
	} else {
		HW_DESC_SET_CIPHER_CONFIG0(desc, HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	}
}

static int dx_hash_map_result(struct device *dev, struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);

	state->digest_result_dma_addr = 
		dma_map_single(dev, (void *)state->digest_result_buff,
			       crypto_ahash_digestsize(tfm),
			       DMA_BIDIRECTIONAL);
	if (unlikely(dma_mapping_error(dev, state->digest_result_dma_addr))) {
		DX_LOG_ERR("Mapping digest result buffer %u B "
			   "at va=%pK for DMA failed\n",
			crypto_ahash_digestsize(tfm), req->result);
		return -ENOMEM;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(state->digest_result_dma_addr,
						crypto_ahash_digestsize(tfm));
	DX_LOG_DEBUG("Mapped digest result buffer %u B "
		     "at va=%pK to dma=0x%llX\n",
		crypto_ahash_digestsize(tfm), state->digest_result_buff,
		(unsigned long long)state->digest_result_dma_addr);

	return 0;
}

static int dx_hash_map_request(struct device *dev, struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	bool is_hmac = ctx->is_hmac;
	dx_sram_addr_t larval_digest_addr = dx_ahash_get_larval_digest_sram_addr(
					ctx->drvdata, ctx->ahash_mode);
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc;
	int rc = -ENOMEM;

	state->digest_buff = kzalloc(ctx->inter_digestsize, GFP_KERNEL|GFP_DMA);
	if (!state->digest_buff) {
		DX_LOG_ERR("Allocating digest-buffer in context failed\n");
		goto fail0;
	}

	DX_LOG_DEBUG("Allocated digest-buffer in context ctx->digest_buff=@%p\n", state->digest_buff);
	if (ctx->hw_mode != SEP_CIPHER_XCBC_MAC) {
		state->digest_bytes_len = kzalloc(HASH_LEN_SIZE, GFP_KERNEL|GFP_DMA);
		if (!state->digest_bytes_len) {
			DX_LOG_ERR("Allocating digest-bytes-len in context failed\n");
			goto fail1;
		}
		DX_LOG_DEBUG("Allocated digest-bytes-len in context state->>digest_bytes_len=@%p\n", state->digest_bytes_len);
	} else {
		state->digest_bytes_len = NULL;
	}

	state->opad_digest_buff = kzalloc(ctx->inter_digestsize, GFP_KERNEL|GFP_DMA);
	if (!state->opad_digest_buff) {
		DX_LOG_ERR("Allocating opad-digest-buffer in context failed\n");
		goto fail2;
	}
	DX_LOG_DEBUG("Allocated opad-digest-buffer in context state->digest_bytes_len=@%p\n", state->opad_digest_buff);

	state->digest_buff_dma_addr = dma_map_single(dev, (void *)state->digest_buff, ctx->inter_digestsize, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, state->digest_buff_dma_addr)) {
		DX_LOG_ERR("Mapping digest len %d B at va=%pK for DMA failed\n",
		ctx->inter_digestsize, state->digest_buff);
		goto fail3;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(state->digest_buff_dma_addr, 
							ctx->inter_digestsize);
	DX_LOG_DEBUG("Mapped digest %d B at va=%pK to dma=0x%llX\n",
		ctx->inter_digestsize, state->digest_buff,
		(unsigned long long)state->digest_buff_dma_addr);

	if (is_hmac) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->digest_buff_dma_addr);
		dma_sync_single_for_cpu(dev, ctx->digest_buff_dma_addr, ctx->inter_digestsize, DMA_BIDIRECTIONAL);
		DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->digest_buff_dma_addr, 
							ctx->inter_digestsize);
		if ((ctx->hw_mode == SEP_CIPHER_XCBC_MAC) || (ctx->hw_mode == SEP_CIPHER_CMAC)) {
			memset(state->digest_buff, 0, ctx->inter_digestsize);
		} else { /*sha*/
			memcpy(state->digest_buff, ctx->digest_buff, ctx->inter_digestsize);
#if (DX_DEV_SHA_MAX > 256)
			if (unlikely((ctx->ahash_mode == SEP_HASH_SHA512) || (ctx->ahash_mode == SEP_HASH_SHA384))) {
				memcpy(state->digest_bytes_len, digest_len_sha512_init, sizeof(digest_len_sha512_init));
			} else {
				memcpy(state->digest_bytes_len, digest_len_init, sizeof(digest_len_init));
			}
#else
			memcpy(state->digest_bytes_len, digest_len_init, sizeof(digest_len_init));
#endif
		}
		DX_RESTORE_DMA_ADDR_TO_48BIT(state->digest_buff_dma_addr);
		dma_sync_single_for_device(dev, state->digest_buff_dma_addr, ctx->inter_digestsize, DMA_BIDIRECTIONAL);
		DX_UPDATE_DMA_ADDR_TO_48BIT(state->digest_buff_dma_addr, 
							ctx->inter_digestsize);

		if (ctx->ahash_mode != SEP_HASH_NULL) {
			DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->opad_tmp_keys_dma_addr);
			dma_sync_single_for_cpu(dev, ctx->opad_tmp_keys_dma_addr, ctx->inter_digestsize, DMA_BIDIRECTIONAL);
			memcpy(state->opad_digest_buff, ctx->opad_tmp_keys_buff, ctx->inter_digestsize);
			DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->opad_tmp_keys_dma_addr, 
							ctx->inter_digestsize);
		} 
	} else { /*hash*/
		/* Copy the initial digests if hash flow. The SRAM contains the
		initial digests in the expected order for all SHA* */
		HW_DESC_INIT(&desc);
		HW_DESC_SET_DIN_SRAM(&desc, larval_digest_addr, ctx->inter_digestsize);
		HW_DESC_SET_DOUT_DLLI(&desc, state->digest_buff_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT, 0);
		HW_DESC_SET_FLOW_MODE(&desc, BYPASS);

		rc = send_request(ctx->drvdata, &dx_req, &desc, 1, 0);
		if (unlikely(rc != 0)) {
			DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
			goto fail0;
		}
	}

	if (ctx->hw_mode != SEP_CIPHER_XCBC_MAC) {
		state->digest_bytes_len_dma_addr = dma_map_single(dev, (void *)state->digest_bytes_len, HASH_LEN_SIZE, DMA_BIDIRECTIONAL);
		if (dma_mapping_error(dev, state->digest_bytes_len_dma_addr)) {
			DX_LOG_ERR("Mapping digest len %u B at va=%pK for DMA failed\n",
			HASH_LEN_SIZE, state->digest_bytes_len);
			goto fail4;
		}
		DX_UPDATE_DMA_ADDR_TO_48BIT(state->digest_bytes_len_dma_addr,
								HASH_LEN_SIZE);
		DX_LOG_DEBUG("Mapped digest len %u B at va=%pK to dma=0x%llX\n",
			HASH_LEN_SIZE, state->digest_bytes_len,
			(unsigned long long)state->digest_bytes_len_dma_addr);
	} else {
		state->digest_bytes_len_dma_addr = 0;
	}

	if (is_hmac && ctx->ahash_mode != SEP_HASH_NULL) {
		state->opad_digest_dma_addr = dma_map_single(dev, (void *)state->opad_digest_buff, ctx->inter_digestsize, DMA_BIDIRECTIONAL);
		if (dma_mapping_error(dev, state->opad_digest_dma_addr)) {
			DX_LOG_ERR("Mapping opad digest %d B at va=%pK for DMA failed\n",
			ctx->inter_digestsize, state->opad_digest_buff);
			goto fail5;
		}
		DX_UPDATE_DMA_ADDR_TO_48BIT(state->opad_digest_dma_addr,
							ctx->inter_digestsize);
		DX_LOG_DEBUG("Mapped opad digest %d B at va=%pK to dma=0x%llX\n",
			ctx->inter_digestsize, state->opad_digest_buff,
			(unsigned long long)state->opad_digest_dma_addr);
	} else {
		state->opad_digest_dma_addr = 0;
	}
	state->buff0_cnt = 0;
	state->buff1_cnt = 0;
	state->buff_index = 0;
	state->mlli_params.curr_pool = NULL;

	return 0;

fail5:
	if (state->digest_bytes_len_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(state->digest_bytes_len_dma_addr);
		dma_unmap_single(dev, state->digest_bytes_len_dma_addr, HASH_LEN_SIZE, DMA_BIDIRECTIONAL);
		state->digest_bytes_len_dma_addr = 0;
	}
fail4:
	if (state->digest_buff_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(state->digest_buff_dma_addr);
		dma_unmap_single(dev, state->digest_buff_dma_addr, ctx->inter_digestsize, DMA_BIDIRECTIONAL);
		state->digest_buff_dma_addr = 0;
	}
fail3:
	if (state->opad_digest_buff != NULL)
		kfree(state->opad_digest_buff);
fail2:
	if (state->digest_bytes_len != NULL)
		kfree(state->digest_bytes_len);
fail1:
	if (state->digest_buff != NULL)
		kfree(state->digest_buff);
fail0:
	return rc;
}

static void dx_hash_unmap_request(struct device *dev, struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	if (state->digest_buff_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(state->digest_buff_dma_addr);
		dma_unmap_single(dev, state->digest_buff_dma_addr,
				 ctx->inter_digestsize, DMA_BIDIRECTIONAL);
		DX_LOG_DEBUG("Unmapped digest-buffer: digest_buff_dma_addr=0x%llX\n",
			(unsigned long long)state->digest_buff_dma_addr);
		state->digest_buff_dma_addr = 0;
	}
	if (state->digest_bytes_len_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(state->digest_bytes_len_dma_addr);
		dma_unmap_single(dev, state->digest_bytes_len_dma_addr,
				 HASH_LEN_SIZE, DMA_BIDIRECTIONAL);
		DX_LOG_DEBUG("Unmapped digest-bytes-len buffer: digest_bytes_len_dma_addr=0x%llX\n",
			(unsigned long long)state->digest_bytes_len_dma_addr);
		state->digest_bytes_len_dma_addr = 0;
	}
	if (state->opad_digest_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(state->opad_digest_dma_addr);
		dma_unmap_single(dev, state->opad_digest_dma_addr,
				 ctx->inter_digestsize, DMA_TO_DEVICE);
		DX_LOG_DEBUG("Unmapped opad-digest: opad_digest_dma_addr=0x%llX\n",
			(unsigned long long)state->opad_digest_dma_addr);
		state->opad_digest_dma_addr = 0;
	}

	if (state->opad_digest_buff != NULL)
		kfree(state->opad_digest_buff);
	if (state->digest_bytes_len != NULL)
		kfree(state->digest_bytes_len);
	if (state->digest_buff != NULL)
		kfree(state->digest_buff);
}

static void dx_hash_unmap_result(struct device *dev, struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);

	if (state->digest_result_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(state->digest_result_dma_addr);
		dma_unmap_single(dev,
				 state->digest_result_dma_addr,
				 crypto_ahash_digestsize(tfm),
				  DMA_BIDIRECTIONAL);	
		DX_LOG_DEBUG("unmpa digest result buffer "
			     "va (%pK) pa (%llx) len %u\n",
			     state->digest_result_buff, 
			     (unsigned long long)state->digest_result_dma_addr,
			     crypto_ahash_digestsize(tfm));
		memcpy(req->result,
		       state->digest_result_buff,
		       crypto_ahash_digestsize(tfm));
	}
	state->digest_result_dma_addr = 0;
}

static void dx_hash_update_complete(struct device *dev, void *dx_req)
{
	struct ahash_request *req = (struct ahash_request *)dx_req;

	DX_LOG_DEBUG("req=%pK\n", req);

	dx_buffer_mgr_unmap_ahash_request(dev, req, false);
	req->base.complete(&req->base, 0);
}

static void dx_hash_digest_complete(struct device *dev, void *dx_req)
{
	struct ahash_request *req = (struct ahash_request *)dx_req;
	DX_LOG_DEBUG("req=%pK\n", req);

	dx_buffer_mgr_unmap_ahash_request(dev, req, false);
	dx_hash_unmap_result(dev, req);
	dx_hash_unmap_request(dev, req);
	req->base.complete(&req->base, 0);
}

static void dx_hash_complete(struct device *dev, void *dx_req)
{
	struct ahash_request *req = (struct ahash_request *)dx_req;

	DX_LOG_DEBUG("req=%pK\n", req);

	dx_buffer_mgr_unmap_ahash_request(dev, req, false);
	dx_hash_unmap_result(dev, req);
	dx_hash_unmap_request(dev, req);
	req->base.complete(&req->base, 0);
}

static int dx_hash_digest(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	bool is_hmac = ctx->is_hmac;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	uint32_t digestsize = crypto_ahash_digestsize(tfm);
	dx_sram_addr_t larval_digest_addr = dx_ahash_get_larval_digest_sram_addr(
					ctx->drvdata, ctx->ahash_mode);
	int idx = 0;
	int rc = 0;

	DX_LOG_DEBUG("===== %s-digest (%d) ====\n", is_hmac?"hmac":"hash", req->nbytes);

	if (unlikely(dx_hash_map_request(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_source() failed\n");
		return -ENOMEM;
	}

	if (unlikely(dx_hash_map_result(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_digest() failed\n");
		return -ENOMEM;
	}

	if (unlikely(dx_buffer_mgr_map_ahash_request_final(ctx->drvdata, req, 1) != 0)) {
		DX_LOG_ERR("map_ahash_request_final() failed\n");
		return -ENOMEM;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_digest_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	/* If HMAC then load hash IPAD xor key, if HASH then load initial digest */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	if (is_hmac) {
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT);
	} else {
		HW_DESC_SET_DIN_SRAM(&desc[idx], larval_digest_addr, ctx->inter_digestsize);
	}
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load the hash current length */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);

	if (is_hmac) {
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_bytes_len_dma_addr, HASH_LEN_SIZE, AXI_ID, NS_BIT);
	} else {
		HW_DESC_SET_DIN_CONST(&desc[idx], 0, HASH_LEN_SIZE);
		if (likely(req->nbytes != 0)) {
			HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
		} else {
			HW_DESC_SET_CIPHER_DO(&desc[idx], DO_PAD);
		}
	}
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	dx_hash_create_data_desc(req, DIN_HASH, desc, false, &idx);

	if (is_hmac) {
		/* HW last hash block padding (aka. "DO_PAD") */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_buff_dma_addr, HASH_LEN_SIZE, AXI_ID, NS_BIT, 0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE1);
		HW_DESC_SET_CIPHER_DO(&desc[idx], DO_PAD);
		idx++;

		/* store the hash digest result in the context */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_buff_dma_addr, digestsize, AXI_ID, NS_BIT, 0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		dx_set_hash_endianity(ctx->ahash_mode, &desc[idx]);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
		idx++;

		/* Loading hash opad xor key state */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->opad_digest_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
		idx++;

		/* Load the hash current length */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_SRAM(&desc[idx], dx_ahash_get_initial_digest_len_sram_addr(ctx->drvdata, ctx->ahash_mode), HASH_LEN_SIZE);
		HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Memory Barrier: wait for IPAD/OPAD axi write to complete */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
		HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
		idx++;

		/* Perform HASH update */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, digestsize, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
		idx++;
	}

	/* Get final MAC result */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode); 
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_result_dma_addr, digestsize, AXI_ID, NS_BIT, 1);   /*TODO*/
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_DISABLED);
	dx_set_hash_endianity(ctx->ahash_mode, &desc[idx]);
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
		dx_hash_unmap_result(dev, req);
		dx_hash_unmap_request(dev, req);
	}
	return rc;
}

static int dx_hash_update(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	uint32_t idx = 0;
	int rc;

	DX_LOG_DEBUG("===== %s-update (%d) ====\n", ctx->is_hmac ?
					"hmac":"hash", req->nbytes);

	if (req->nbytes == 0) {
		/* no real updates required */
		return 0;
	}

	if (unlikely(rc = dx_buffer_mgr_map_ahash_request_update(ctx->drvdata, req))) {
		if (rc == 1) {
			DX_LOG_DEBUG(" data size not require HW update %x\n",
				     req->nbytes);
			/* No hardware updates are required */
			return 0;
		}
		DX_LOG_ERR("map_ahash_request_update() failed\n");
		return -ENOMEM;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_update_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	/* Restore hash digest */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	idx++;
	/* Restore hash current length */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_bytes_len_dma_addr, HASH_LEN_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	dx_hash_create_data_desc(req, DIN_HASH, desc, false, &idx);

	/* store the hash digest result in context */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_buff_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT, 0);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	idx++;

	/* store current hash length in context */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_bytes_len_dma_addr, HASH_LEN_SIZE, AXI_ID, NS_BIT, 1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE1);
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
	}
	return rc;
}

static int dx_hash_finup(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	bool is_hmac = ctx->is_hmac;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	int idx = 0;
	int rc;
	uint32_t digestsize = crypto_ahash_digestsize(tfm);

	DX_LOG_DEBUG("===== %s-finup (%d) ====\n", is_hmac?"hmac":"hash", req->nbytes);
	if (unlikely(dx_buffer_mgr_map_ahash_request_final(ctx->drvdata, req, 1) != 0)) {
		DX_LOG_ERR("map_ahash_request_final() failed\n");
		return -ENOMEM;
	}
	if (unlikely(dx_hash_map_result(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_digest() failed\n");
		return -ENOMEM;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	/* Restore hash digest */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Restore hash current length */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_bytes_len_dma_addr, HASH_LEN_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	dx_hash_create_data_desc(req, DIN_HASH, desc, false, &idx);

	if (is_hmac) {
		/* Store the hash digest result in the context */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_buff_dma_addr, digestsize, AXI_ID, NS_BIT, 0);
		dx_set_hash_endianity(ctx->ahash_mode,&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
		idx++;

		/* Loading hash OPAD xor key state */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->opad_digest_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
		idx++;

		/* Load the hash current length */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_SRAM(&desc[idx], dx_ahash_get_initial_digest_len_sram_addr(ctx->drvdata, ctx->ahash_mode), HASH_LEN_SIZE);
		HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Memory Barrier: wait for IPAD/OPAD axi write to complete */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
		HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
		idx++;

		/* Perform HASH update on last digest */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, digestsize, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
		idx++;
	}

	/* Get final MAC result */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_result_dma_addr, digestsize, AXI_ID, NS_BIT, 1); /*TODO*/
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_DISABLED);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	dx_set_hash_endianity(ctx->ahash_mode,&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode); 
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
		dx_hash_unmap_result(dev, req);
	}
	return rc;
}

static int dx_hash_final(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	bool is_hmac = ctx->is_hmac;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	int idx = 0;
	int rc;
	uint32_t digestsize = crypto_ahash_digestsize(tfm);

	DX_LOG_DEBUG("===== %s-final (%d) ====\n", is_hmac?"hmac":"hash", req->nbytes);

	if (unlikely(dx_buffer_mgr_map_ahash_request_final(ctx->drvdata, req, 0) != 0)) {
		DX_LOG_ERR("map_ahash_request_final() failed\n");
		return -ENOMEM;
	}

	if (unlikely(dx_hash_map_result(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_digest() failed\n");
		return -ENOMEM;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	/* Restore hash digest */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Restore hash current length */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_DISABLED);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_bytes_len_dma_addr, HASH_LEN_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	dx_hash_create_data_desc(req, DIN_HASH, desc, false, &idx);

	/* "DO-PAD" must be enabled only when writing current length to HW */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_DO(&desc[idx], DO_PAD);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_bytes_len_dma_addr, HASH_LEN_SIZE, AXI_ID, NS_BIT, 0);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	idx++;

	if (is_hmac) {
		/* Store the hash digest result in the context */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_buff_dma_addr, digestsize, AXI_ID, NS_BIT, 0);
		dx_set_hash_endianity(ctx->ahash_mode,&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
		idx++;

		/* Loading hash OPAD xor key state */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->opad_digest_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
		idx++;

		/* Load the hash current length */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_SRAM(&desc[idx], dx_ahash_get_initial_digest_len_sram_addr(ctx->drvdata, ctx->ahash_mode), HASH_LEN_SIZE);
		HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Memory Barrier: wait for IPAD/OPAD axi write to complete */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
		HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
		idx++;

		/* Perform HASH update on last digest */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, digestsize, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
		idx++;
	}

	/* Get final MAC result */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_result_dma_addr, digestsize, AXI_ID, NS_BIT, 1);  /*TODO*/
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_DISABLED);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	dx_set_hash_endianity(ctx->ahash_mode,&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
		dx_hash_unmap_result(dev, req);
	}
	return rc;
}

static int dx_hash_init(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;

	DX_LOG_DEBUG("===== init (%d) ====\n", req->nbytes);

	state->xcbc_count = 0;
	dx_hash_map_request(dev, req);
	return 0;
}

static int dx_hash_export(struct ahash_request *req, void *out)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(ahash);

	memcpy(out, ctx, sizeof(struct dx_hash_ctx));
	return 0;
}

static int dx_hash_import(struct ahash_request *req, const void *in)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(ahash);

	memcpy(ctx, in, sizeof(struct dx_hash_ctx));
	return 0;
}

static int dx_hash_setkey(struct crypto_ahash *ahash,
			const u8 *key, unsigned int keylen)
{
	unsigned int hmacPadConst[2] = { HMAC_IPAD_CONST, HMAC_OPAD_CONST };
	struct dx_crypto_req dx_req = {0};
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	int blocksize = crypto_tfm_alg_blocksize(&ahash->base);
	int digestsize = crypto_ahash_digestsize(ahash);
	int i, idx = 0, rc = 0;
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	dx_sram_addr_t larval_addr = dx_ahash_get_larval_digest_sram_addr(
					ctx->drvdata, ctx->ahash_mode);

	DX_LOG_DEBUG("===== setkey (%d) ====\n", keylen);

	/* The keylen value distinguishes HASH in case keylen is ZERO bytes,
	   any NON-ZERO value utilizes HMAC flow */
	ctx->key_params.keylen = keylen;
	ctx->key_params.key_dma_addr = dma_map_single(
					&ctx->drvdata->plat_dev->dev,
					(void *)key,
					keylen, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(&ctx->drvdata->plat_dev->dev,
				       ctx->key_params.key_dma_addr))) {
		DX_LOG_ERR("Mapping key va=0x%p len=%u for"
			   " DMA failed\n", key, keylen);
		return -ENOMEM;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->key_params.key_dma_addr, keylen);
	DX_LOG_DEBUG("mapping key-buffer: key_dma_addr=0x%llX "
		     "keylen=%u\n",
		     (unsigned long long)ctx->key_params.key_dma_addr,
		     ctx->key_params.keylen);
	ctx->is_hmac = true;
	if (keylen != 0) {
		if (keylen > blocksize) {
			/* Load hash initial state */
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
			HW_DESC_SET_DIN_SRAM(&desc[idx], larval_addr,
					ctx->inter_digestsize);
			HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
			HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
			idx++;
	
			/* Load the hash current length*/
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
			HW_DESC_SET_DIN_CONST(&desc[idx], 0, HASH_LEN_SIZE);
			HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
			HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
			HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
			idx++;
	
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
					     ctx->key_params.key_dma_addr, 
					     keylen, AXI_ID, NS_BIT);
			HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
			idx++;
	
			/* Get hashed key */
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode); 
			HW_DESC_SET_DOUT_DLLI(&desc[idx], ctx->opad_tmp_keys_dma_addr,
					      digestsize, AXI_ID, NS_BIT, 0);
			HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
			HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
			HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_DISABLED);
			dx_set_hash_endianity(ctx->ahash_mode,&desc[idx]);
			idx++;
	
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_DIN_CONST(&desc[idx], 0, (blocksize - digestsize));
			HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
			HW_DESC_SET_DOUT_DLLI(&desc[idx], 
					      (ctx->opad_tmp_keys_dma_addr + digestsize),
					      (blocksize - digestsize),
					      AXI_ID, NS_BIT, 0);
			idx++;
	
	
		} else {
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
					     ctx->key_params.key_dma_addr, 
					     keylen, AXI_ID, NS_BIT);
			HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
			HW_DESC_SET_DOUT_DLLI(&desc[idx],
					(ctx->opad_tmp_keys_dma_addr),
					keylen, AXI_ID, NS_BIT, 0);
			idx++;

			if ((blocksize - keylen) != 0) {
				HW_DESC_INIT(&desc[idx]);
				HW_DESC_SET_DIN_CONST(&desc[idx], 0, (blocksize - keylen));
				HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
				HW_DESC_SET_DOUT_DLLI(&desc[idx], 
						      (ctx->opad_tmp_keys_dma_addr + keylen),
						      (blocksize - keylen),
						      AXI_ID, NS_BIT, 0);
				idx++;
			}
	
		}
	} else {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_CONST(&desc[idx], 0, blocksize);
		HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], 
				      (ctx->opad_tmp_keys_dma_addr),
				      blocksize,
				      AXI_ID, NS_BIT, 0);
		idx++;
	}

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 0);
	if (unlikely(rc != 0)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		goto out;
	}

	/* calc derived HMAC key */
	for (idx = 0, i = 0; i < 2; i++) {
		/* Load hash initial state */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_SRAM(&desc[idx], larval_addr,
				ctx->inter_digestsize);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
		idx++;

		/* Load the hash current length*/
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_DIN_CONST(&desc[idx], 0, HASH_LEN_SIZE);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Prepare ipad key */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_XOR_VAL(&desc[idx], hmacPadConst[i]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
		idx++;

		/* Perform HASH update */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
				     ctx->opad_tmp_keys_dma_addr,
				     blocksize, AXI_ID, NS_BIT);
		HW_DESC_SET_CIPHER_MODE(&desc[idx],ctx->hw_mode);
		HW_DESC_SET_XOR_ACTIVE(&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
		idx++;

		/* Get the IPAD/OPAD xor key (Note, IPAD is the initial digest of the first HASH "update" state) */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		if (i > 0) /* Not first iteration */
			HW_DESC_SET_DOUT_DLLI(&desc[idx],
					      ctx->opad_tmp_keys_dma_addr,
					      ctx->inter_digestsize,
					      AXI_ID, NS_BIT, 0);
		else /* First iteration */
			HW_DESC_SET_DOUT_DLLI(&desc[idx],
					      ctx->digest_buff_dma_addr,
					      ctx->inter_digestsize,
					      AXI_ID, NS_BIT, 0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
		idx++;
	}

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 0);

out:
	if (rc != 0)
		crypto_ahash_set_flags(ahash, CRYPTO_TFM_RES_BAD_KEY_LEN);

	DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->key_params.key_dma_addr);
	dma_unmap_single(&ctx->drvdata->plat_dev->dev,
			ctx->key_params.key_dma_addr,
			ctx->key_params.keylen, DMA_TO_DEVICE);
	DX_LOG_DEBUG("Unmapped key-buffer: key_dma_addr=0x%llX keylen=%u\n",
			(unsigned long long)ctx->key_params.key_dma_addr,
			ctx->key_params.keylen);
	return rc;
}


static int dx_xcbc_setkey(struct crypto_ahash *ahash,
			const u8 *key, unsigned int keylen)
{
	struct dx_crypto_req dx_req = {0};
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	int idx = 0, rc = 0;
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];

	DX_LOG_DEBUG("===== setkey (%d) ====\n", keylen);

	switch (keylen) {
		case AES_KEYSIZE_128:
		case AES_KEYSIZE_192:
		case AES_KEYSIZE_256:
			break;
		default:
			return -EINVAL;
	}

	ctx->key_params.keylen = keylen;

	ctx->key_params.key_dma_addr = dma_map_single(
					&ctx->drvdata->plat_dev->dev,
					(void *)key,
					keylen, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(&ctx->drvdata->plat_dev->dev,
				       ctx->key_params.key_dma_addr))) {
		DX_LOG_ERR("Mapping key va=0x%p len=%u for"
			   " DMA failed\n", key, keylen);
		return -ENOMEM;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->key_params.key_dma_addr, keylen);
	DX_LOG_DEBUG("mapping key-buffer: key_dma_addr=0x%llX "
		     "keylen=%u\n",
		     (unsigned long long)ctx->key_params.key_dma_addr,
		     ctx->key_params.keylen);
	
	ctx->is_hmac = true;
	/* 1. Load the AES key */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->key_params.key_dma_addr, keylen, AXI_ID, NS_BIT);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_ECB);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], keylen);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_CONST(&desc[idx], 0x01010101, SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], (ctx->opad_tmp_keys_dma_addr + 
					   XCBC_MAC_K1_OFFSET), 
			      SEP_AES_128_BIT_KEY_SIZE, AXI_ID, NS_BIT, 0);
	idx++;

	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_CONST(&desc[idx], 0x02020202, SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], (ctx->opad_tmp_keys_dma_addr + 
					   XCBC_MAC_K2_OFFSET), 
			      SEP_AES_128_BIT_KEY_SIZE, AXI_ID, NS_BIT, 0);
	idx++;

	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_CONST(&desc[idx], 0x03030303, SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], (ctx->opad_tmp_keys_dma_addr + 
					   XCBC_MAC_K3_OFFSET),
			       SEP_AES_128_BIT_KEY_SIZE, AXI_ID, NS_BIT, 0);
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 0);

	if (rc != 0)
		crypto_ahash_set_flags(ahash, CRYPTO_TFM_RES_BAD_KEY_LEN);

	DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->key_params.key_dma_addr);
	dma_unmap_single(&ctx->drvdata->plat_dev->dev,
			ctx->key_params.key_dma_addr,
			ctx->key_params.keylen, DMA_TO_DEVICE);
	DX_LOG_DEBUG("Unmapped key-buffer: key_dma_addr=0x%llX keylen=%u\n",
			(unsigned long long)ctx->key_params.key_dma_addr,
			ctx->key_params.keylen);

	return rc;
}
#if DX_CC_HAS_CMAC
static int dx_cmac_setkey(struct crypto_ahash *ahash,
			const u8 *key, unsigned int keylen)
{
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	
	DX_LOG_DEBUG("===== setkey (%d) ====\n", keylen);

	ctx->is_hmac = true;

	switch (keylen) {
		case AES_KEYSIZE_128:
		case AES_KEYSIZE_192:
		case AES_KEYSIZE_256:
			break;
		default:
			return -EINVAL;
	}

	ctx->key_params.keylen = keylen;

	/* STAT_PHASE_1: Copy key to ctx */
	START_CYCLE_COUNT();
	
	DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->opad_tmp_keys_dma_addr);
	dma_sync_single_for_cpu(&ctx->drvdata->plat_dev->dev,
				ctx->opad_tmp_keys_dma_addr, 
				keylen, DMA_TO_DEVICE);

	memcpy(ctx->opad_tmp_keys_buff, key, keylen);
	if (keylen == 24)
		memset(ctx->opad_tmp_keys_buff + 24, 0, SEP_AES_KEY_SIZE_MAX - 24);
	
	dma_sync_single_for_device(&ctx->drvdata->plat_dev->dev,
				   ctx->opad_tmp_keys_dma_addr, 
				   keylen, DMA_TO_DEVICE);
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->opad_tmp_keys_dma_addr, keylen);
		
	ctx->key_params.keylen = keylen;
	
	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_1);

	return 0;
}
#endif

static void dx_hash_free_ctx(struct dx_hash_ctx *ctx)
{
	struct device *dev = &ctx->drvdata->plat_dev->dev;

	if (ctx->digest_buff_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->digest_buff_dma_addr);
		dma_unmap_single(dev, ctx->digest_buff_dma_addr,
				 sizeof(ctx->digest_buff), DMA_BIDIRECTIONAL);
		DX_LOG_DEBUG("Unmapped digest-buffer: "
			     "digest_buff_dma_addr=0x%llX\n",
			(unsigned long long)ctx->digest_buff_dma_addr);
		ctx->digest_buff_dma_addr = 0;
	}
	if (ctx->opad_tmp_keys_dma_addr != 0) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->opad_tmp_keys_dma_addr);
		dma_unmap_single(dev, ctx->opad_tmp_keys_dma_addr,
				 sizeof(ctx->opad_tmp_keys_buff),
				 DMA_BIDIRECTIONAL);
		DX_LOG_DEBUG("Unmapped opad-digest: "
			     "opad_tmp_keys_dma_addr=0x%llX\n",
			(unsigned long long)ctx->opad_tmp_keys_dma_addr);
		ctx->opad_tmp_keys_dma_addr = 0;
	}

	ctx->key_params.keylen = 0;

}


static int dx_hash_alloc_ctx(struct dx_hash_ctx *ctx)
{
	struct device *dev = &ctx->drvdata->plat_dev->dev;

	ctx->key_params.keylen = 0;

	ctx->digest_buff_dma_addr = dma_map_single(dev, (void *)ctx->digest_buff, sizeof(ctx->digest_buff), DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, ctx->digest_buff_dma_addr)) {
		DX_LOG_ERR("Mapping digest len %zu B at va=%pK for DMA failed\n",
			sizeof(ctx->digest_buff), ctx->digest_buff);
		goto fail;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->digest_buff_dma_addr,
						sizeof(ctx->digest_buff));
	DX_LOG_DEBUG("Mapped digest %zu B at va=%pK to dma=0x%llX\n",
		sizeof(ctx->digest_buff), ctx->digest_buff,
		(unsigned long long)ctx->digest_buff_dma_addr);

	ctx->opad_tmp_keys_dma_addr = dma_map_single(dev, (void *)ctx->opad_tmp_keys_buff, sizeof(ctx->opad_tmp_keys_buff), DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, ctx->opad_tmp_keys_dma_addr)) {
		DX_LOG_ERR("Mapping opad digest %zu B at va=%pK for DMA failed\n",
			sizeof(ctx->opad_tmp_keys_buff),
			ctx->opad_tmp_keys_buff);
		goto fail;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->opad_tmp_keys_dma_addr,
					sizeof(ctx->opad_tmp_keys_buff));
	DX_LOG_DEBUG("Mapped opad_tmp_keys %zu B at va=%pK to dma=0x%llX\n",
		sizeof(ctx->opad_tmp_keys_buff), ctx->opad_tmp_keys_buff,
		(unsigned long long)ctx->opad_tmp_keys_dma_addr);

	ctx->is_hmac = false;
	return 0;

fail:
	dx_hash_free_ctx(ctx);
	return -ENOMEM;
}


static int dx_hash_cra_init(struct crypto_tfm *tfm)
{
	struct dx_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	struct hash_alg_common * hash_alg_common = 
		container_of(tfm->__crt_alg, struct hash_alg_common, base);
	struct ahash_alg *ahash_alg = 
		container_of(hash_alg_common, struct ahash_alg, halg);
	struct dx_hash_alg *dx_alg =
			container_of(ahash_alg, struct dx_hash_alg, ahash_alg);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				sizeof(struct ahash_req_ctx));

	ctx->ahash_mode = dx_alg->ahash_mode;
	ctx->hw_mode = dx_alg->hw_mode;
	ctx->inter_digestsize = dx_alg->inter_digestsize;
	ctx->drvdata = dx_alg->drvdata;

	return dx_hash_alloc_ctx(ctx);
}

static void dx_hash_cra_exit(struct crypto_tfm *tfm)
{
	struct dx_hash_ctx *ctx = crypto_tfm_ctx(tfm);

	dx_hash_free_ctx(ctx);
}

static int dx_mac_update(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	int rc;
	uint32_t idx = 0;

	if (req->nbytes == 0) {
		/* no real updates required */
		return 0;
	}

	state->xcbc_count++;

	if (unlikely(rc = dx_buffer_mgr_map_ahash_request_update(ctx->drvdata, req))) {
		if (rc == 1) {
			DX_LOG_DEBUG(" data size not require HW update %x\n",
				     req->nbytes);
			/* No hardware updates are required */
			return 0;
		}
		DX_LOG_ERR("map_ahash_request_update() failed\n");
		return -ENOMEM;
	}

	if (ctx->hw_mode == SEP_CIPHER_XCBC_MAC) {
		dx_hash_create_xcbc_setup(req, desc, &idx);
	} else {
		dx_hash_create_cmac_setup(req, desc, &idx);
	}
	
	dx_hash_create_data_desc(req, DIN_AES_DOUT, desc, true, &idx);

	/* store the hash digest result in context */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_buff_dma_addr, ctx->inter_digestsize, AXI_ID, NS_BIT, 1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_AES_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	idx++;

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_update_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
	}
	return rc;
}

static int dx_mac_final(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	int idx = 0;
	int rc = 0;
	uint32_t keySize, keyLen;
	uint32_t digestsize = crypto_ahash_digestsize(tfm);

	uint32_t rem_cnt = state->buff_index ? state->buff1_cnt :
			state->buff0_cnt;
	

	if (ctx->hw_mode == SEP_CIPHER_XCBC_MAC) {
		keySize = SEP_AES_128_BIT_KEY_SIZE;
		keyLen  = SEP_AES_128_BIT_KEY_SIZE;
	} else {
		keySize = (ctx->key_params.keylen == 24) ? AES_MAX_KEY_SIZE : ctx->key_params.keylen;
		keyLen =  ctx->key_params.keylen;
	}

	DX_LOG_DEBUG("===== final  xcbc reminder (%d) ====\n", rem_cnt);

	if (unlikely(dx_buffer_mgr_map_ahash_request_final(ctx->drvdata, req, 0) != 0)) {
		DX_LOG_ERR("map_ahash_request_final() failed\n");
		return -ENOMEM;
	}

	if (unlikely(dx_hash_map_result(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_digest() failed\n");
		return -ENOMEM;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	if (state->xcbc_count && (rem_cnt == 0)) {
		/* Load key for ECB decryption */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_ECB);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_DECRYPT);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
				     (ctx->opad_tmp_keys_dma_addr + 
				      XCBC_MAC_K1_OFFSET),
				    keySize, AXI_ID, NS_BIT);
		HW_DESC_SET_KEY_SIZE_AES(&desc[idx], keyLen);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
		idx++;


		/* Initiate decryption of block state to previous block_state-XOR-M[n] */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, SEP_AES_BLOCK_SIZE, AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_buff_dma_addr, SEP_AES_BLOCK_SIZE, AXI_ID, NS_BIT,0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
		idx++;

		/* Memory Barrier: wait for axi write to complete */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
		HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
		idx++;
	}
	
	if (ctx->hw_mode == SEP_CIPHER_XCBC_MAC) {
		dx_hash_create_xcbc_setup(req, desc, &idx);
	} else {
		dx_hash_create_cmac_setup(req, desc, &idx);
	}

	if (state->xcbc_count == 0) {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_KEY_SIZE_AES(&desc[idx], keyLen);
		HW_DESC_SET_CMAC_SIZE0_MODE(&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
		idx++;
	} else if (rem_cnt > 0) {
		dx_hash_create_data_desc(req, DIN_AES_DOUT, desc, false, &idx);
	} else {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_CONST(&desc[idx], 0x00, SEP_AES_BLOCK_SIZE);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
		idx++;
	}
	
	/* Get final MAC result */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_result_dma_addr, digestsize, AXI_ID, NS_BIT, 1); /*TODO*/
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_AES_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode); 
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
		dx_hash_unmap_result(dev, req);
	}
	return rc;
}

static int dx_mac_finup(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	int idx = 0;
	int rc = 0;
	uint32_t key_len = 0;
	uint32_t digestsize = crypto_ahash_digestsize(tfm);

	DX_LOG_DEBUG("===== finup xcbc(%d) ====\n", req->nbytes);
	if (state->xcbc_count > 0 && req->nbytes == 0) {
		DX_LOG_DEBUG("No data to update. Call to fdx_mac_final \n");
		return dx_mac_final(req);
	}
	
	if (unlikely(dx_buffer_mgr_map_ahash_request_final(ctx->drvdata, req, 1) != 0)) {
		DX_LOG_ERR("map_ahash_request_final() failed\n");
		return -ENOMEM;
	}
	if (unlikely(dx_hash_map_result(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_digest() failed\n");
		return -ENOMEM;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	if (ctx->hw_mode == SEP_CIPHER_XCBC_MAC) {
		key_len = SEP_AES_128_BIT_KEY_SIZE;
		dx_hash_create_xcbc_setup(req, desc, &idx);
	} else {
		key_len = ctx->key_params.keylen;
		dx_hash_create_cmac_setup(req, desc, &idx);
	}

	if (req->nbytes == 0) {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_KEY_SIZE_AES(&desc[idx], key_len);
		HW_DESC_SET_CMAC_SIZE0_MODE(&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
		idx++;
	} else {
		dx_hash_create_data_desc(req, DIN_AES_DOUT, desc, false, &idx);
	}
	
	/* Get final MAC result */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_result_dma_addr, digestsize, AXI_ID, NS_BIT, 1); /*TODO*/
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_AES_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode); 
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
		dx_hash_unmap_result(dev, req);
	}
	return rc;
}

static int dx_mac_digest(struct ahash_request *req)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	struct dx_crypto_req dx_req = {0};
	HwDesc_s desc[DX_MAX_AHASH_SEQ_LEN];
	uint32_t keyLen;
	int idx = 0;
	int rc;

	DX_LOG_DEBUG("===== -digest mac (%d) ====\n",  req->nbytes);
	
	if (unlikely(dx_hash_map_request(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_source() failed\n");
		return -ENOMEM;
	}
	if (unlikely(dx_hash_map_result(dev, req) != 0)) {
		DX_LOG_ERR("map_ahash_digest() failed\n");
		return -ENOMEM;
	}

	if (unlikely(dx_buffer_mgr_map_ahash_request_final(ctx->drvdata, req, 1) != 0)) {
		DX_LOG_ERR("map_ahash_request_final() failed\n");
		return -ENOMEM;
	}
	
	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_hash_digest_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_ENCODE; /* Use "Encode" stats */
#endif

	
	if (ctx->hw_mode == SEP_CIPHER_XCBC_MAC) {
		keyLen = SEP_AES_128_BIT_KEY_SIZE;
		dx_hash_create_xcbc_setup(req, desc, &idx);
	} else {
		keyLen = ctx->key_params.keylen;
		dx_hash_create_cmac_setup(req, desc, &idx);
	}

	if (req->nbytes == 0) {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode);
		HW_DESC_SET_KEY_SIZE_AES(&desc[idx], keyLen);
		HW_DESC_SET_CMAC_SIZE0_MODE(&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
		idx++;
	} else {
		dx_hash_create_data_desc(req, DIN_AES_DOUT, desc, false, &idx);
	}
	
	/* Get final MAC result */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], state->digest_result_dma_addr, SEP_AES_BLOCK_SIZE, AXI_ID, NS_BIT,1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_AES_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx],DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->hw_mode); 
	idx++;

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_ahash_request(dev, req, true);
		dx_hash_unmap_result(dev, req);
		dx_hash_unmap_request(dev, req);
	}
	return rc;
}

struct dx_hash_template {
	char name[CRYPTO_MAX_ALG_NAME];
	char driver_name[CRYPTO_MAX_ALG_NAME];
	char hmac_name[CRYPTO_MAX_ALG_NAME];
	char hmac_driver_name[CRYPTO_MAX_ALG_NAME];
	unsigned int blocksize;
	struct ahash_alg template_ahash;
	int ahash_mode;
	int hw_mode;
	int inter_digestsize;
	struct dx_drvdata *drvdata;
};

/* ahash descriptors */
static struct dx_hash_template driver_hash[] = {
	{
		.name = "sha1",
		.driver_name = "sha1-dx",
		.hmac_name = "hmac(sha1)",
		.hmac_driver_name = "hmac-sha1-dx",
		.blocksize = SHA1_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_hash_update,
			.final = dx_hash_final,
			.finup = dx_hash_finup,
			.digest = dx_hash_digest,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.setkey = dx_hash_setkey,
			.halg = {
				.digestsize = SHA1_DIGEST_SIZE,
				},
			},
		.ahash_mode = SEP_HASH_SHA1,
		.hw_mode = SEP_HASH_HW_SHA1,
		.inter_digestsize = SHA1_DIGEST_SIZE,
	},
	{
		.name = "sha256",
		.driver_name = "sha256-dx",
		.hmac_name = "hmac(sha256)",
		.hmac_driver_name = "hmac-sha256-dx",
		.blocksize = SHA256_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_hash_update,
			.final = dx_hash_final,
			.finup = dx_hash_finup,
			.digest = dx_hash_digest,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.setkey = dx_hash_setkey,
			.halg = {
				.digestsize = SHA256_DIGEST_SIZE,
				},
			},
		.ahash_mode = SEP_HASH_SHA256,
		.hw_mode = SEP_HASH_HW_SHA256,
		.inter_digestsize = SHA256_DIGEST_SIZE,
	},
	{
		.name = "sha224",
		.driver_name = "sha224-dx",
		.hmac_name = "hmac(sha224)",
		.hmac_driver_name = "hmac-sha224-dx",
		.blocksize = SHA224_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_hash_update,
			.final = dx_hash_final,
			.finup = dx_hash_finup,
			.digest = dx_hash_digest,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.setkey = dx_hash_setkey,
			.halg = {
				.digestsize = SHA224_DIGEST_SIZE,
				},
			},
		.ahash_mode = SEP_HASH_SHA224,
		.hw_mode = SEP_HASH_HW_SHA256,
		.inter_digestsize = SHA256_DIGEST_SIZE,
	},
#if (DX_DEV_SHA_MAX > 256)
	{
		.name = "sha384",
		.driver_name = "sha384-dx",
		.hmac_name = "hmac(sha384)",
		.hmac_driver_name = "hmac-sha384-dx",
		.blocksize = SHA384_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_hash_update,
			.final = dx_hash_final,
			.finup = dx_hash_finup,
			.digest = dx_hash_digest,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.setkey = dx_hash_setkey,
			.halg = {
				.digestsize = SHA384_DIGEST_SIZE,
				},
			},
		.ahash_mode = SEP_HASH_SHA384,
		.hw_mode = SEP_HASH_HW_SHA512,
		.inter_digestsize = SHA512_DIGEST_SIZE,
	},
	{
		.name = "sha512",
		.driver_name = "sha512-dx",
		.hmac_name = "hmac(sha512)",
		.hmac_driver_name = "hmac-sha512-dx",
		.blocksize = SHA512_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_hash_update,
			.final = dx_hash_final,
			.finup = dx_hash_finup,
			.digest = dx_hash_digest,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.setkey = dx_hash_setkey,
			.halg = {
				.digestsize = SHA512_DIGEST_SIZE,
				},
			},
		.ahash_mode = SEP_HASH_SHA512,
		.hw_mode = SEP_HASH_HW_SHA512,
		.inter_digestsize = SHA512_DIGEST_SIZE,
	},
#endif
	{
		.name = "md5",
		.driver_name = "md5-dx",
		.hmac_name = "hmac(md5)",
		.hmac_driver_name = "hmac-md5-dx",
		.blocksize = MD5_HMAC_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_hash_update,
			.final = dx_hash_final,
			.finup = dx_hash_finup,
			.digest = dx_hash_digest,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.setkey = dx_hash_setkey,
			.halg = {
				.digestsize = MD5_DIGEST_SIZE,
				},
			},
		.ahash_mode = SEP_HASH_MD5,
		.hw_mode = SEP_HASH_HW_MD5,
		.inter_digestsize = MD5_DIGEST_SIZE,
	},
	{
		.name = "xcbc(aes)",
		.driver_name = "xcbc-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_mac_update,
			.final = dx_mac_final,
			.finup = dx_mac_finup,
			.digest = dx_mac_digest,
			.setkey = dx_xcbc_setkey,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.halg = {
				.digestsize = AES_BLOCK_SIZE,
				},
			},
			.ahash_mode = SEP_HASH_NULL,
			.hw_mode = SEP_CIPHER_XCBC_MAC,
			.inter_digestsize = AES_BLOCK_SIZE,
		},
#if DX_CC_HAS_CMAC
	{
		.name = "cmac(aes)",
		.driver_name = "cmac-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.template_ahash = {
			.init = dx_hash_init,
			.update = dx_mac_update,
			.final = dx_mac_final,
			.finup = dx_mac_finup,
			.digest = dx_mac_digest,
			.setkey = dx_cmac_setkey,
			.export = dx_hash_export,
			.import = dx_hash_import,
			.halg = {
				.digestsize = AES_BLOCK_SIZE,
				},
			},
			.ahash_mode = SEP_HASH_NULL,
			.hw_mode = SEP_CIPHER_CMAC,
			.inter_digestsize = AES_BLOCK_SIZE,
		},
#endif
};

static struct dx_hash_alg *
dx_hash_create_alg(struct dx_hash_template *template, bool keyed)
{
	struct dx_hash_alg *t_crypto_alg;
	struct ahash_alg *halg;
	struct crypto_alg *alg;

	t_crypto_alg = kzalloc(sizeof(struct dx_hash_alg), GFP_KERNEL);
	if (!t_crypto_alg) {
		DX_LOG_ERR("failed to allocate t_alg\n");
		return ERR_PTR(-ENOMEM);
	}

	t_crypto_alg->ahash_alg = template->template_ahash;
	halg = &t_crypto_alg->ahash_alg;
	alg = &halg->halg.base;

	if (keyed) {
		snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->hmac_name);
		snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->hmac_driver_name);
	} else {
		snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->name);
		snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->driver_name);
	}
	alg->cra_module = THIS_MODULE;
	alg->cra_init = dx_hash_cra_init;
	alg->cra_exit = dx_hash_cra_exit;
	alg->cra_ctxsize = sizeof(struct dx_hash_ctx);
	alg->cra_priority = DX_CRA_PRIO;
	alg->cra_blocksize = template->blocksize;
	alg->cra_alignmask = 0;
	alg->cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_TYPE_AHASH |
			CRYPTO_ALG_KERN_DRIVER_ONLY;
	alg->cra_type = &crypto_ahash_type;

	t_crypto_alg->ahash_mode = template->ahash_mode;
	t_crypto_alg->hw_mode = template->hw_mode;
	t_crypto_alg->inter_digestsize = template->inter_digestsize;

	return t_crypto_alg;
}

int dx_hash_init_sram_digest_consts(struct dx_drvdata *drvdata)
{
	struct dx_ahash_handle *ahash_handle = drvdata->ahash_handle;
	dx_sram_addr_t sram_buff_ofs = ahash_handle->digest_len_sram_addr;
	unsigned int larval_seq_len = 0;
	HwDesc_s larval_seq[SEP_DIGEST_SIZE_MAX/sizeof(uint32_t)];
	int rc = 0;
#if (DX_DEV_SHA_MAX > 256)
	int i;
#endif

	/* Copy-to-sram digest-len */
	dx_sram_mgr_const2sram_desc(digest_len_init, sram_buff_ofs,
		ARRAY_SIZE(digest_len_init), larval_seq, &larval_seq_len);
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0))
		goto init_digest_const_err;

	sram_buff_ofs += sizeof(digest_len_init);
	larval_seq_len = 0;

#if (DX_DEV_SHA_MAX > 256)
	/* Copy-to-sram digest-len for sha384/512 */
	dx_sram_mgr_const2sram_desc(digest_len_sha512_init, sram_buff_ofs,
		ARRAY_SIZE(digest_len_sha512_init), larval_seq, &larval_seq_len);
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0))
		goto init_digest_const_err;

	sram_buff_ofs += sizeof(digest_len_sha512_init);
	larval_seq_len = 0;
#endif

	/* The initial digests offset */
	ahash_handle->larval_digest_sram_addr = sram_buff_ofs;

	/* Copy-to-sram initial SHA* digests */
	dx_sram_mgr_const2sram_desc(md5_init, sram_buff_ofs,
		ARRAY_SIZE(md5_init), larval_seq, &larval_seq_len);
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0))
		goto init_digest_const_err;
	sram_buff_ofs += sizeof(md5_init);
	larval_seq_len = 0;

	dx_sram_mgr_const2sram_desc(sha1_init, sram_buff_ofs,
		ARRAY_SIZE(sha1_init), larval_seq, &larval_seq_len);
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0))
		goto init_digest_const_err;
	sram_buff_ofs += sizeof(sha1_init);
	larval_seq_len = 0;

	dx_sram_mgr_const2sram_desc(sha224_init, sram_buff_ofs,
		ARRAY_SIZE(sha224_init), larval_seq, &larval_seq_len);
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0))
		goto init_digest_const_err;
	sram_buff_ofs += sizeof(sha224_init);
	larval_seq_len = 0;

	dx_sram_mgr_const2sram_desc(sha256_init, sram_buff_ofs,
		ARRAY_SIZE(sha256_init), larval_seq, &larval_seq_len);
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0))
		goto init_digest_const_err;
	sram_buff_ofs += sizeof(sha256_init);
	larval_seq_len = 0;

#if (DX_DEV_SHA_MAX > 256)
	/* We are forced to swap each double-word larval before copying to sram */
	for (i = 0; i < ARRAY_SIZE(sha384_init); i++) {
		const uint32_t const0 = ((uint32_t *)((uint64_t *)&sha384_init[i]))[1];
		const uint32_t const1 = ((uint32_t *)((uint64_t *)&sha384_init[i]))[0];

		dx_sram_mgr_const2sram_desc(&const0, sram_buff_ofs, 1,
			larval_seq, &larval_seq_len);
		sram_buff_ofs += sizeof(uint32_t);
		dx_sram_mgr_const2sram_desc(&const1, sram_buff_ofs, 1,
			larval_seq, &larval_seq_len);
		sram_buff_ofs += sizeof(uint32_t);
	}
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0)) {
		DX_LOG_ERR("send_request() failed (rc = %d)\n", rc);
		goto init_digest_const_err;
	}
	larval_seq_len = 0;

	for (i = 0; i < ARRAY_SIZE(sha512_init); i++) {
		const uint32_t const0 = ((uint32_t *)((uint64_t *)&sha512_init[i]))[1];
		const uint32_t const1 = ((uint32_t *)((uint64_t *)&sha512_init[i]))[0];

		dx_sram_mgr_const2sram_desc(&const0, sram_buff_ofs, 1,
			larval_seq, &larval_seq_len);
		sram_buff_ofs += sizeof(uint32_t);
		dx_sram_mgr_const2sram_desc(&const1, sram_buff_ofs, 1,
			larval_seq, &larval_seq_len);
		sram_buff_ofs += sizeof(uint32_t);
	}
	rc = send_request_init(drvdata, larval_seq, larval_seq_len);
	if (unlikely(rc != 0)) {
		DX_LOG_ERR("send_request() failed (rc = %d)\n", rc);
		goto init_digest_const_err;
	}
#endif

init_digest_const_err:
	return rc;
}

int dx_hash_alloc(struct dx_drvdata *drvdata)
{
	struct dx_ahash_handle *ahash_handle;
	dx_sram_addr_t sram_buff;
	uint32_t sram_size_to_alloc;
	int rc = 0;
	int alg;

	ahash_handle = kzalloc(sizeof(struct dx_ahash_handle), GFP_KERNEL);
	if (ahash_handle == NULL) {
		DX_LOG_ERR("kzalloc failed to allocate %zu B\n",
			sizeof(struct dx_ahash_handle));
		rc = -ENOMEM;
		goto fail;
	}

	sram_size_to_alloc = sizeof(digest_len_init) +
#if (DX_DEV_SHA_MAX > 256)
			sizeof(digest_len_sha512_init) +
			sizeof(sha384_init) +
			sizeof(sha512_init) +
#endif
			sizeof(md5_init) +
			sizeof(sha1_init) +
			sizeof(sha224_init) +
			sizeof(sha256_init);
				
	sram_buff = dx_sram_mgr_alloc(drvdata, sram_size_to_alloc);
	if (sram_buff == NULL_SRAM_ADDR) {
		DX_LOG_ERR("SRAM pool exhausted\n");
		rc = -ENOMEM;
		goto fail;
	}

	/* The initial digest-len offset */
	ahash_handle->digest_len_sram_addr = sram_buff;

	/*must be set before the alg registration as it is being used there*/
	drvdata->ahash_handle = ahash_handle;
	rc = dx_hash_init_sram_digest_consts(drvdata);
	if (unlikely(rc != 0)) {
		DX_LOG_ERR("Init digest CONST failed (rc=%d)\n", rc);
		goto fail;
	}

	INIT_LIST_HEAD(&ahash_handle->ahash_list);

	/* ahash registration */
	for (alg = 0; alg < ARRAY_SIZE(driver_hash); alg++) {
		struct dx_hash_alg *t_alg;
		
		/* register hmac version */

		if ((((struct dx_hash_template)driver_hash[alg]).hw_mode != SEP_CIPHER_XCBC_MAC) &&
			(((struct dx_hash_template)driver_hash[alg]).hw_mode != SEP_CIPHER_CMAC)) {
			t_alg = dx_hash_create_alg(&driver_hash[alg], true);
			if (IS_ERR(t_alg)) {
				rc = PTR_ERR(t_alg);
				DX_LOG_ERR("%s alg allocation failed\n",
					 driver_hash[alg].driver_name);
				goto fail;
			}
			t_alg->drvdata = drvdata;
	
			rc = crypto_register_ahash(&t_alg->ahash_alg);
			if (unlikely(rc != 0)) {
				DX_LOG_ERR("%s alg registration failed\n",
					t_alg->ahash_alg.halg.base.cra_driver_name);
				kfree(t_alg);
				goto fail;
			} else
				list_add_tail(&t_alg->entry, &ahash_handle->ahash_list);
		}

		/* register hash version */
		t_alg = dx_hash_create_alg(&driver_hash[alg], false);
		if (IS_ERR(t_alg)) {
			rc = PTR_ERR(t_alg);
			DX_LOG_ERR("%s alg allocation failed\n",
				 driver_hash[alg].driver_name);
			goto fail;
		}
		t_alg->drvdata = drvdata;
		
		rc = crypto_register_ahash(&t_alg->ahash_alg);
		if (unlikely(rc != 0)) {
			DX_LOG_ERR("%s alg registration failed\n",
				t_alg->ahash_alg.halg.base.cra_driver_name);
			kfree(t_alg);
			goto fail;
		} else
			list_add_tail(&t_alg->entry, &ahash_handle->ahash_list);
	}

	return 0;

fail:

	if (drvdata->ahash_handle != NULL) {
		kfree(drvdata->ahash_handle);
		drvdata->ahash_handle = NULL;
	}
	return rc;
}

int dx_hash_free(struct dx_drvdata *drvdata)
{
	struct dx_hash_alg *t_ahash_alg, *ahash_n;
	struct dx_ahash_handle *ahash_handle = drvdata->ahash_handle;

	if (ahash_handle != NULL) {
		list_for_each_entry_safe(t_ahash_alg, ahash_n, &ahash_handle->ahash_list, entry) {
			crypto_unregister_ahash(&t_ahash_alg->ahash_alg);
			list_del(&t_ahash_alg->entry);
			kfree(t_ahash_alg);
		}

		kfree(ahash_handle);
		drvdata->ahash_handle = NULL;
	}
	return 0;
}

static void dx_hash_create_xcbc_setup(struct ahash_request *areq, 
				  HwDesc_s desc[],
				  unsigned int *seq_size) {
	unsigned int idx = *seq_size;
	struct ahash_req_ctx *state = ahash_request_ctx(areq);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	/* Setup XCBC MAC K1 */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, (ctx->opad_tmp_keys_dma_addr 
						    + XCBC_MAC_K1_OFFSET),
			     SEP_AES_128_BIT_KEY_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Setup XCBC MAC K2 */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, (ctx->opad_tmp_keys_dma_addr 
						    + XCBC_MAC_K2_OFFSET),
			      SEP_AES_128_BIT_KEY_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Setup XCBC MAC K3 */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, (ctx->opad_tmp_keys_dma_addr 
						    + XCBC_MAC_K3_OFFSET),
			     SEP_AES_128_BIT_KEY_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE2);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Loading MAC state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, SEP_AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;
	*seq_size = idx;
}

static void dx_hash_create_cmac_setup(struct ahash_request *areq, 
				  HwDesc_s desc[],
				  unsigned int *seq_size) {
	unsigned int idx = *seq_size;
	struct ahash_req_ctx *state = ahash_request_ctx(areq);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	/* Setup CMAC Key */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->opad_tmp_keys_dma_addr,
		((ctx->key_params.keylen == 24) ? AES_MAX_KEY_SIZE : ctx->key_params.keylen), AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CMAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->key_params.keylen);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Load MAC state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr, SEP_AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CMAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->key_params.keylen);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;
	*seq_size = idx;
}

static void dx_hash_create_data_desc(struct ahash_request *areq, 
				  unsigned int flow_mode,HwDesc_s desc[],
				  bool is_not_last_data, 
				  unsigned int *seq_size)
{
	unsigned int idx = *seq_size;
	struct ahash_req_ctx *areq_ctx = ahash_request_ctx(areq);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	struct dx_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	if (likely(areq_ctx->data_dma_buf_type == DX_DMA_BUF_DLLI)) {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
				     sg_dma_address(areq_ctx->curr_sg), 
				     areq_ctx->curr_sg->length, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		idx++;
	} else {
		if (areq_ctx->data_dma_buf_type == 
					DX_DMA_BUF_NULL) {
			DX_LOG_DEBUG(" NULL mode\n");
			/* nothing to build */
			return;
		}
		/* bypass */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
				     areq_ctx->mlli_params.mlli_dma_addr, 
				     areq_ctx->mlli_params.mlli_len, 
				     AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_SRAM(&desc[idx], 
			ctx->drvdata->mlli_sram_addr, 
			areq_ctx->mlli_params.mlli_len);
		HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
		idx++;
		/* process */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_MLLI, 
			ctx->drvdata->mlli_sram_addr, 
			areq_ctx->mlli_nents,
			AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		idx++;
	}
	if (is_not_last_data) {
		HW_DESC_SET_DIN_NOT_LAST_INDICATION(&desc[idx-1]);
	}
	/* return updated desc sequence size */
	*seq_size = idx;
}

/*!
 * Gets the address of the initial digest in SRAM 
 * according to the given hash mode
 * 
 * \param drvdata
 * \param mode The Hash mode. Supported modes: MD5/SHA1/SHA224/SHA256
 * 
 * \return uint32_t The address of the inital digest in SRAM
 */
dx_sram_addr_t dx_ahash_get_larval_digest_sram_addr(void *drvdata, uint32_t mode)
{
	struct dx_drvdata *_drvdata = (struct dx_drvdata *)drvdata;
	struct dx_ahash_handle *ahash_handle = _drvdata->ahash_handle;

	switch (mode) {
	case SEP_HASH_NULL:
		break; /*Ignore*/
	case SEP_HASH_MD5:
		return (ahash_handle->larval_digest_sram_addr);
	case SEP_HASH_SHA1:
		return (ahash_handle->larval_digest_sram_addr +
			sizeof(md5_init));
	case SEP_HASH_SHA224:
		return (ahash_handle->larval_digest_sram_addr +
			sizeof(md5_init) +
			sizeof(sha1_init));
	case SEP_HASH_SHA256:
		return (ahash_handle->larval_digest_sram_addr +
			sizeof(md5_init) +
			sizeof(sha1_init) +
			sizeof(sha224_init));
#if (DX_DEV_SHA_MAX > 256)
	case SEP_HASH_SHA384:
		return (ahash_handle->larval_digest_sram_addr +
			sizeof(md5_init) +
			sizeof(sha1_init) +
			sizeof(sha224_init) +
			sizeof(sha256_init));
	case SEP_HASH_SHA512:
		return (ahash_handle->larval_digest_sram_addr +
			sizeof(md5_init) +
			sizeof(sha1_init) +
			sizeof(sha224_init) +
			sizeof(sha256_init) +
			sizeof(sha384_init));
#endif
	default:
		DX_LOG_ERR("Invalid hash mode (%d)\n", mode);
	}

	/*This is valid wrong value to avoid kernel crash*/
	return ahash_handle->larval_digest_sram_addr;
}

dx_sram_addr_t
dx_ahash_get_initial_digest_len_sram_addr(void *drvdata, uint32_t mode)
{
	struct dx_drvdata *_drvdata = (struct dx_drvdata *)drvdata;
	struct dx_ahash_handle *ahash_handle = _drvdata->ahash_handle;
	dx_sram_addr_t digest_len_addr = ahash_handle->digest_len_sram_addr;

	switch (mode) {
	case SEP_HASH_SHA1:
	case SEP_HASH_SHA224:
	case SEP_HASH_SHA256:
	case SEP_HASH_MD5:
		return digest_len_addr;
#if (DX_DEV_SHA_MAX > 256)
	case SEP_HASH_SHA384:
	case SEP_HASH_SHA512:
		return  digest_len_addr + sizeof(digest_len_init);
#endif
	default:
		return digest_len_addr; /*to avoid kernel crash*/
	}
}

