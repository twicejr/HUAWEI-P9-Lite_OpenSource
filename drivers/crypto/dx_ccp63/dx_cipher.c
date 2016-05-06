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
#include <crypto/internal/skcipher.h>
#include <crypto/aes.h>
#include <crypto/ctr.h>
#include <crypto/des.h>

#include "dx_config.h"
#include "dx_driver.h"
#include "dx_lli_defs.h"
#include "dx_buffer_mgr.h"
#include "dx_cipher.h"
#include "dx_request_mgr.h"
#include "dx_sysfs.h"

#define MAX_ABLKCIPHER_SEQ_LEN 6

#define template_ablkcipher	template_u.ablkcipher

#define DX_MIN_AES_XTS_SIZE 0x10
#define DX_MAX_AES_XTS_SIZE 0x2000
struct dx_ablckcipher_handle {
	struct list_head ablkcipher_alg_list;
	/* This field is used for the secure key dropped flows */
	uint32_t  dropped_buffer;
	dma_addr_t  dropped_buffer_dma_addr;
};

struct dx_ablkcipher_ctx {
	struct dx_drvdata *drvdata;
	uint8_t *key;
	dma_addr_t key_dma_addr;
	int keylen;
	int key_round_number;
	int cipher_mode;
	int flow_mode;
	int is_secure_key;
	int is_aes_ctr_prot;
};

static void dx_ablkcipher_complete(struct device *dev, void *dx_req);


static int validate_keys_sizes(struct dx_ablkcipher_ctx *ctx_p, int size) {
	switch (ctx_p->flow_mode){
	case S_DIN_to_AES:
		switch (size){
		case SEP_AES_128_BIT_KEY_SIZE:
		case SEP_AES_192_BIT_KEY_SIZE:
			if (likely(ctx_p->cipher_mode != SEP_CIPHER_XTS))
				return 0;
			break;
		case SEP_AES_256_BIT_KEY_SIZE:
			return 0;
		case (SEP_AES_192_BIT_KEY_SIZE*2):
		case (SEP_AES_256_BIT_KEY_SIZE*2):
			if (likely(ctx_p->cipher_mode == SEP_CIPHER_XTS))
				return 0;
			break;
		default:
			break;
		}
	case S_DIN_to_DES:
		if (likely(size == DES3_EDE_KEY_SIZE ||
		    size == DES_KEY_SIZE))
			return 0;
		break;
#if DX_CC_HAS_MULTI2
	case S_DIN_to_MULTI2:
		if (likely(size == SEP_MULTI2_SYSTEM_N_DATA_KEY_SIZE))
			return 0;
		break;
#endif
	default:
		break;

	}
	return -EINVAL;
}


static int validate_data_size(struct dx_ablkcipher_ctx *ctx_p, unsigned int size) {
	switch (ctx_p->flow_mode){
	case S_DIN_to_AES:
		switch (ctx_p->cipher_mode){
		case SEP_CIPHER_XTS:
			if ((size >= DX_MIN_AES_XTS_SIZE) &&
			    (size <= DX_MAX_AES_XTS_SIZE) && 
			    IS_ALIGNED(size, AES_BLOCK_SIZE))
				return 0;
			break;
		case SEP_CIPHER_CBC_CTS:
			if (likely(size >= AES_BLOCK_SIZE))
				return 0;
			break;
		case SEP_CIPHER_OFB:
		case SEP_CIPHER_CTR:
				return 0;
		case SEP_CIPHER_ECB:
		case SEP_CIPHER_CBC:
			if (likely(IS_ALIGNED(size, AES_BLOCK_SIZE)))
				return 0;
			break;
		default:
			break;
		}
		break;
	case S_DIN_to_DES:
		if (likely(IS_ALIGNED(size, DES_BLOCK_SIZE)))
				return 0;
		break;
#if DX_CC_HAS_MULTI2
	case S_DIN_to_MULTI2:
		switch (ctx_p->cipher_mode) {
		case SEP_MULTI2_CBC:
			if (likely(IS_ALIGNED(size, SEP_MULTI2_BLOCK_SIZE)))
				return 0;
			break;
		case SEP_MULTI2_OFB:
			return 0;
		default:
			break;
		}
		break;
#endif /*DX_CC_HAS_MULTI2*/
	default:
		break;

	}
	return -EINVAL;
}

static int dx_ablkcipher_init(struct crypto_tfm *tfm)
{
	struct dx_ablkcipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	struct ablkcipher_tfm *ablktfm = &tfm->crt_ablkcipher;
	struct crypto_alg *alg = tfm->__crt_alg;
	struct dx_crypto_alg *dx_alg =
			container_of(alg, struct dx_crypto_alg, crypto_alg);
	struct device *dev;
	int rc = 0;

	DX_LOG_DEBUG("Initializing context @%p for %s\n", ctx_p, 
						crypto_tfm_alg_name(tfm));

	ablktfm->reqsize = sizeof(struct ablkcipher_req_ctx);
	ctx_p->cipher_mode = dx_alg->cipher_mode;
	ctx_p->flow_mode = dx_alg->flow_mode;
	ctx_p->is_secure_key = dx_alg->is_secure_key;
	ctx_p->drvdata = dx_alg->drvdata;
	dev = &ctx_p->drvdata->plat_dev->dev;

	/* Allocate key buffer, cache line aligned */
	ctx_p->key = kmalloc(MAX_KEY_BUF_SIZE, GFP_KERNEL|GFP_DMA);
	if (!ctx_p->key) {
		DX_LOG_ERR("Allocating key buffer in context failed\n");
		rc = -ENOMEM;
	}
	DX_LOG_DEBUG("Allocated key buffer in context ctx_p->key=@%p\n",
								ctx_p->key);

	/* Map key buffer */
	ctx_p->key_dma_addr = dma_map_single(dev, (void *)ctx_p->key,
					     MAX_KEY_BUF_SIZE, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, ctx_p->key_dma_addr)) {
		DX_LOG_ERR("Mapping Key %u B at va=%pK for DMA failed\n",
			MAX_KEY_BUF_SIZE, ctx_p->key);
		return -ENOMEM;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx_p->key_dma_addr, MAX_KEY_BUF_SIZE);
	DX_LOG_DEBUG("Mapped key %u B at va=%pK to dma=0x%llX\n",
		MAX_KEY_BUF_SIZE, ctx_p->key,
		(unsigned long long)ctx_p->key_dma_addr);

	return rc;
}

static void dx_ablkcipher_exit(struct crypto_tfm *tfm)
{
	struct dx_ablkcipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	struct device *dev = &ctx_p->drvdata->plat_dev->dev;

	DX_LOG_DEBUG("Clearing context @%p for %s\n",
		crypto_tfm_ctx(tfm), crypto_tfm_alg_name(tfm));

	/* Unmap key buffer */
	DX_RESTORE_DMA_ADDR_TO_48BIT(ctx_p->key_dma_addr);
	dma_unmap_single(dev, ctx_p->key_dma_addr, MAX_KEY_BUF_SIZE,
								DMA_TO_DEVICE);
	DX_LOG_DEBUG("Unmapped key buffer key_dma_addr=0x%llX\n", 
		(unsigned long long)ctx_p->key_dma_addr);


	/* Free key buffer in context */
	kfree(ctx_p->key);
	DX_LOG_DEBUG("Free key buffer in context ctx_p->key=@%p\n", ctx_p->key);
}

static int dx_ablkcipher_setkey(struct crypto_ablkcipher *tfm, 
				const u8 *key, 
				unsigned int keylen)
{
	struct dx_ablkcipher_ctx *ctx_p = 
				crypto_tfm_ctx(crypto_ablkcipher_tfm(tfm));
	struct device *dev = &ctx_p->drvdata->plat_dev->dev;
	u32 tmp[DES_EXPKEY_WORDS];

	DECL_CYCLE_COUNT_RESOURCES;

	DX_LOG_DEBUG("Setting key in context @%p for %s. keylen=%u\n",
		ctx_p, crypto_tfm_alg_name(crypto_ablkcipher_tfm(tfm)), keylen);
	dump_byte_array("key", (uint8_t *)key, keylen);
	
	/* STAT_PHASE_0: Init and sanity checks */
	START_CYCLE_COUNT();

#if DX_CC_HAS_MULTI2
	/*last byte of key buffer is round number and should not be a part of key size*/
	if (ctx_p->flow_mode == S_DIN_to_MULTI2) {
		keylen -=1;
	}
#endif /*DX_CC_HAS_MULTI2*/

	if (unlikely(validate_keys_sizes(ctx_p,keylen) != 0)) {
			DX_LOG_ERR("Unsupported key size %d.\n", keylen);
			crypto_ablkcipher_set_flags(tfm,
						CRYPTO_TFM_RES_BAD_KEY_LEN);
			return -EINVAL;
	}
	
	
	if (ctx_p->flow_mode == S_DIN_to_DES) {
		if (unlikely(!des_ekey(tmp, key)) &&
		(crypto_ablkcipher_get_flags(tfm) & CRYPTO_TFM_REQ_WEAK_KEY)) {
			tfm->base.crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
			return -EINVAL;
		}
	}
	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_0);

	/* STAT_PHASE_1: Copy key to ctx */
	START_CYCLE_COUNT();
	DX_RESTORE_DMA_ADDR_TO_48BIT(ctx_p->key_dma_addr);
	dma_sync_single_for_cpu(dev, ctx_p->key_dma_addr, 
					MAX_KEY_BUF_SIZE, DMA_TO_DEVICE);
#if DX_CC_HAS_MULTI2
	if (ctx_p->flow_mode == S_DIN_to_MULTI2) {
		memcpy(ctx_p->key, key, SEP_MULTI2_SYSTEM_N_DATA_KEY_SIZE);
		ctx_p->key_round_number = key[SEP_MULTI2_SYSTEM_N_DATA_KEY_SIZE];
		if (ctx_p->key_round_number < SEP_MULTI2_MIN_NUM_ROUNDS ||
		    ctx_p->key_round_number > SEP_MULTI2_MAX_NUM_ROUNDS) {
			crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
			return -EINVAL;
		}
	} else 
#endif /*DX_CC_HAS_MULTI2*/
	{
		memcpy(ctx_p->key, key, keylen);
		if (keylen == 24)
			memset(ctx_p->key + 24, 0, SEP_AES_KEY_SIZE_MAX - 24);
	}
	dma_sync_single_for_device(dev, ctx_p->key_dma_addr, 
					MAX_KEY_BUF_SIZE, DMA_TO_DEVICE);
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx_p->key_dma_addr ,MAX_KEY_BUF_SIZE);
	ctx_p->keylen = keylen;
	
	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_1);

	return 0;
}
						
						
#if DX_CC_HAS_SEC_KEY
static int dx_ablkcipher_secure_key_setkey(struct crypto_ablkcipher *tfm,
					   const u8 *key, unsigned int keylen)
{
	struct dx_ablkcipher_ctx *ctx_p = 
				crypto_tfm_ctx(crypto_ablkcipher_tfm(tfm));
	struct device *dev = &ctx_p->drvdata->plat_dev->dev;
	u32 skConfig = 0;
	DECL_CYCLE_COUNT_RESOURCES;

	DX_LOG_DEBUG("Setting key in context @%p for %s. keylen=%u\n",
		ctx_p, crypto_tfm_alg_name(crypto_ablkcipher_tfm(tfm)), keylen);
	
	if (keylen != DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES) {
		return -EINVAL;
	}

	/* STAT_PHASE_0: Init and sanity checks */
	START_CYCLE_COUNT();
	/* No sanity checks*/
	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_0);
	memcpy(&skConfig,
	       &key[DX_SECURE_KEY_RESTRICT_CONFIG_OFFSET * sizeof(u32)],
	       sizeof(u32));
	/* STAT_PHASE_1: Copy key to ctx */
	START_CYCLE_COUNT();
	/* The secure key is working only with one key size */
	DX_RESTORE_DMA_ADDR_TO_48BIT(ctx_p->key_dma_addr);
	dma_sync_single_for_cpu(dev, ctx_p->key_dma_addr,
					MAX_KEY_BUF_SIZE, DMA_TO_DEVICE);
	memcpy(ctx_p->key, key, MAX_KEY_BUF_SIZE);
	dma_sync_single_for_device(dev, ctx_p->key_dma_addr,
					MAX_KEY_BUF_SIZE, DMA_TO_DEVICE);
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx_p->key_dma_addr, MAX_KEY_BUF_SIZE);
		
	/*Get the keysize for the IV loading descriptor */
	switch(DX_CC_REG_FLD_GET(0, SECURE_KEY_RESTRICT, KEY_TYPE, skConfig)) {
	case DX_SECURE_KEY_AES_KEY128 :
		ctx_p->keylen = SEP_AES_128_BIT_KEY_SIZE;
		break;
	case DX_SECURE_KEY_AES_KEY256:
		ctx_p->keylen = SEP_AES_256_BIT_KEY_SIZE;
		break;
#if DX_CC_HAS_MULTI2
	case DX_SECURE_KEY_MULTI2:
		/*The keylen is not use in the multi2 IV loading desciptor.
		  The field is init to value that is converted to 0 in the
		  descriptor */
		ctx_p->keylen = SEP_AES_128_BIT_KEY_SIZE;
		break;
#endif /*DX_CC_HAS_MULTI2*/
	case DX_SECURE_KEY_BYPASS:
		break;
	default:
		return -EINVAL;
	}
	
	switch(DX_CC_REG_FLD_GET(0, SECURE_KEY_RESTRICT, MODE, skConfig)) {
	case DX_SECURE_KEY_CIPHER_CTR_NONCE_PROT:
	case DX_SECURE_KEY_CIPHER_CTR_NONCE_CTR_PROT_NSP:
		ctx_p->is_aes_ctr_prot = 1;
		break;
	default:
		ctx_p->is_aes_ctr_prot = 0;
	}
	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_1);
	return 0;
}
#endif /*DX_CC_HAS_SEC_KEY*/

static inline void
dx_ablkcipher_create_setup_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	unsigned int iv_size = crypto_ablkcipher_ivsize(tfm);
	int direction = areq_ctx->gen_ctx.op_type;
	
	switch (ctx_p->cipher_mode) {
	case SEP_CIPHER_CBC:
	case SEP_CIPHER_CBC_CTS:
	case SEP_CIPHER_CTR:
	case SEP_CIPHER_OFB:
		/* Load cipher state */
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
				     areq_ctx->gen_ctx.iv_dma_addr, iv_size,
				     AXI_ID, NS_BIT);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
		HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
		if ((ctx_p->cipher_mode == SEP_CIPHER_CTR) || 
		    (ctx_p->cipher_mode == SEP_CIPHER_OFB) ) {
			HW_DESC_SET_SETUP_MODE(&desc[*seq_size],
							SETUP_LOAD_STATE1);
		} else {
			HW_DESC_SET_SETUP_MODE(&desc[*seq_size],
							SETUP_LOAD_STATE0);
		}
		(*seq_size)++;
		/*FALLTHROUGH*/
	case SEP_CIPHER_ECB:
		/* Load key */
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
		if (ctx_p->flow_mode == S_DIN_to_AES) {
			HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI, 
							ctx_p->key_dma_addr, 
				((ctx_p->keylen == 24) ? AES_MAX_KEY_SIZE : 
						ctx_p->keylen), AXI_ID, NS_BIT);
			HW_DESC_SET_KEY_SIZE_AES(&desc[*seq_size], 
								ctx_p->keylen);
		} else {
			/*des*/
			HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
							ctx_p->key_dma_addr,
							ctx_p->keylen,
							AXI_ID, NS_BIT);
			HW_DESC_SET_KEY_SIZE_DES(&desc[*seq_size],
						 ctx_p->keylen);
		}
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
		HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_KEY0);
		(*seq_size)++;
		break;
	case SEP_CIPHER_XTS:
		/* Load AES key */
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
						ctx_p->key_dma_addr,
						ctx_p->keylen/2, AXI_ID,
						NS_BIT);
		HW_DESC_SET_KEY_SIZE_AES(&desc[*seq_size], ctx_p->keylen/2);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
		HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_KEY0);
		(*seq_size)++;

		/* load XEX key */
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI, 
					(ctx_p->key_dma_addr+ctx_p->keylen/2),
					ctx_p->keylen/2, AXI_ID, NS_BIT);
		HW_DESC_SET_XEX_DATA_UNIT_SIZE(&desc[*seq_size], req->nbytes);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
		HW_DESC_SET_KEY_SIZE_AES(&desc[*seq_size], ctx_p->keylen/2);
		HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_XEX_KEY);
		(*seq_size)++;
	
		/* Set state */
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_STATE1);
		HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
		HW_DESC_SET_KEY_SIZE_AES(&desc[*seq_size], ctx_p->keylen/2);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
						areq_ctx->gen_ctx.iv_dma_addr,
							SEP_AES_BLOCK_SIZE,
								AXI_ID, NS_BIT);
		(*seq_size)++;
		break;
	default:
		DX_LOG_ERR("Unsupported cipher mode (%d)\n", 
							ctx_p->cipher_mode);
		BUG();
	}
}

#if DX_CC_HAS_MULTI2
static inline void dx_ablkcipher_create_multi2_setup_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	unsigned int iv_size = crypto_ablkcipher_ivsize(tfm);
	
	int direction = areq_ctx->gen_ctx.op_type;
	/* Load system key */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
	HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI, ctx_p->key_dma_addr,
						SEP_MULTI2_SYSTEM_KEY_SIZE,
						AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
	HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_KEY0);
	(*seq_size)++;

	/* load data key */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI, 
					(ctx_p->key_dma_addr + 
						SEP_MULTI2_SYSTEM_KEY_SIZE),
				SEP_MULTI2_DATA_KEY_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_MULTI2_NUM_ROUNDS(&desc[*seq_size],
						ctx_p->key_round_number);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
	HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
	HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_STATE0 );
	(*seq_size)++;
	
	
	/* Set state */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
			     areq_ctx->gen_ctx.iv_dma_addr,
			     iv_size, AXI_ID, NS_BIT);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
	HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
	HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_STATE1);	
	(*seq_size)++;
	
}
#endif /*DX_CC_HAS_MULTI2*/

#if DX_CC_HAS_SEC_KEY
static inline void
dx_ablkcipher_create_secure_key_setup_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	unsigned int iv_size = crypto_ablkcipher_ivsize(tfm);
	
	int direction = areq_ctx->gen_ctx.op_type;

	/* Load system key */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_DIN_TYPE(&desc[*seq_size], NO_DMA,
			     ctx_p->key_dma_addr,
			     DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			     AXI_ID, NS_BIT);
	HW_DESC_STOP_QUEUE(&desc[*seq_size]);
	(*seq_size)++;

	/* Load cipher state */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
			     areq_ctx->gen_ctx.iv_dma_addr,
			     iv_size, AXI_ID, NS_BIT);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], direction);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], ctx_p->flow_mode);
	HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
	/*The state is loaded in any case of multi2 or AES CTR/OFB 
	  with SETUP_LOAD_STATE1 all other case with SETUP_LOAD_STATE0*/
	if ((ctx_p->flow_mode == S_DIN_to_MULTI2) ||
	    (ctx_p->cipher_mode == SEP_CIPHER_CTR) ||
	    (ctx_p->cipher_mode == SEP_CIPHER_OFB)) {
		HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_STATE1);
	} else {
		HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_STATE0);
	}
	HW_DESC_SET_KEY_SIZE_AES(&desc[*seq_size], ctx_p->keylen);
	(*seq_size)++;
		
}

static inline void
dx_ablkcipher_create_secure_bypass_setup_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	
	/* Load system key */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_DIN_TYPE(&desc[*seq_size], NO_DMA,
			     ctx_p->key_dma_addr,
			     DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			     AXI_ID, NS_BIT);
	HW_DESC_STOP_QUEUE(&desc[*seq_size]);
	(*seq_size)++;		
}

/* Load key to disable the secure key restrictions */
static inline void
dx_ablkcipher_create_disable_secure_key_setup_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	unsigned int flow_mode = ctx_p->flow_mode;

	switch (flow_mode) {
	case BYPASS:
		flow_mode = S_DIN_to_AES;
		break;
	default:
		break;
	}
	

	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_CIPHER_MODE(&desc[*seq_size], ctx_p->cipher_mode);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[*seq_size], areq_ctx->gen_ctx.op_type);
	HW_DESC_SET_DIN_CONST(&desc[*seq_size], 0, SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_KEY_SIZE_AES(&desc[*seq_size], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], flow_mode);
	HW_DESC_SET_SETUP_MODE(&desc[*seq_size], SETUP_LOAD_KEY0);
	(*seq_size)++;		
}
#endif /*DX_CC_HAS_SEC_KEY*/

static inline void
dx_ablkcipher_create_data_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	unsigned int flow_mode = ctx_p->flow_mode;

	switch (ctx_p->flow_mode) {
	case S_DIN_to_AES:
		flow_mode = DIN_AES_DOUT;
		break;
	case S_DIN_to_DES:
		flow_mode = DIN_DES_DOUT;
		break;
#if DX_CC_HAS_MULTI2
	case S_DIN_to_MULTI2:
		flow_mode = DIN_MULTI2_DOUT;
		break;
#endif /*DX_CC_HAS_MULTI2*/
	default:
		DX_LOG_ERR("invalid flow mode, flow_mode = %d \n", flow_mode);
		return;
	}
	/* Process */
	if (likely(areq_ctx->dma_buf_type == DX_DMA_BUF_DLLI)){
		DX_LOG_DEBUG(" data params addr 0x%llX length 0x%X \n",
			     (unsigned long long)sg_dma_address(req->src),
			     req->nbytes);
		DX_LOG_DEBUG(" data params addr 0x%llX length 0x%X \n",
			     (unsigned long long)sg_dma_address(req->dst),
			     req->nbytes);
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
				     sg_dma_address(req->src),
				     req->nbytes, AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_DLLI(&desc[*seq_size],
				      sg_dma_address(req->dst),
				      req->nbytes,
				      AXI_ID, NS_BIT, 1);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], flow_mode);
		(*seq_size)++;
	} else {
		/* bypass */
		DX_LOG_DEBUG(" bypass params addr 0x%llX "
			     "length 0x%X addr 0x%08X\n",
			(unsigned long long)areq_ctx->mlli_params.mlli_dma_addr,
			areq_ctx->mlli_params.mlli_len,
			(unsigned int)ctx_p->drvdata->mlli_sram_addr);
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
				     areq_ctx->mlli_params.mlli_dma_addr,
				     areq_ctx->mlli_params.mlli_len,
				     AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_SRAM(&desc[*seq_size],
				      ctx_p->drvdata->mlli_sram_addr,
				      areq_ctx->mlli_params.mlli_len);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], BYPASS);
		(*seq_size)++;

		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_MLLI,
			ctx_p->drvdata->mlli_sram_addr,
				     areq_ctx->in_mlli_nents, AXI_ID, NS_BIT);
		if (areq_ctx->out_nents == 0) {
			DX_LOG_DEBUG(" din/dout params addr 0x%08X "
				     "addr 0x%08X\n",
			(unsigned int)ctx_p->drvdata->mlli_sram_addr,
			(unsigned int)ctx_p->drvdata->mlli_sram_addr);
			HW_DESC_SET_DOUT_MLLI(&desc[*seq_size], 
			ctx_p->drvdata->mlli_sram_addr,
					      areq_ctx->in_mlli_nents,
					       AXI_ID, NS_BIT,1);
		} else {
			DX_LOG_DEBUG(" din/dout params "
				     "addr 0x%08X addr 0x%08X\n",
				(unsigned int)ctx_p->drvdata->mlli_sram_addr,
				(unsigned int)ctx_p->drvdata->mlli_sram_addr + 
				(uint32_t)LLI_ENTRY_BYTE_SIZE * 
							areq_ctx->in_nents);
			HW_DESC_SET_DOUT_MLLI(&desc[*seq_size], 
				(ctx_p->drvdata->mlli_sram_addr +
				LLI_ENTRY_BYTE_SIZE * 
						areq_ctx->in_mlli_nents), 
				areq_ctx->out_mlli_nents, AXI_ID, NS_BIT,1);
		}
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], flow_mode);
		(*seq_size)++;
	}
}

#if DX_CC_HAS_SEC_KEY
static inline void
dx_ablkcipher_create_secure_key_mlli_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);

	if (likely(areq_ctx->dma_buf_type == DX_DMA_BUF_MLLI)) {
		/* bypass */
		DX_LOG_DEBUG(" bypass params addr 0x%llX "
			     "length 0x%X addr 0x%08X\n",
			(unsigned long long)areq_ctx->mlli_params.mlli_dma_addr,
			areq_ctx->mlli_params.mlli_len,
			(unsigned int)ctx_p->drvdata->mlli_sram_addr);
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
				     areq_ctx->mlli_params.mlli_dma_addr,
				     areq_ctx->mlli_params.mlli_len,
				     AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_SRAM(&desc[*seq_size],
				      ctx_p->drvdata->mlli_sram_addr,
				      areq_ctx->mlli_params.mlli_len);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], BYPASS);
		(*seq_size)++;	
	}
}

static inline void
dx_ablkcipher_create_secure_key_data_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	struct dx_ablckcipher_handle * handle = 
					ctx_p->drvdata->ablckcipher_handle;
	unsigned int flow_mode = ctx_p->flow_mode;

	switch (ctx_p->flow_mode) {
	case S_DIN_to_AES:
		flow_mode = DIN_AES_DOUT;
		break;
#if DX_CC_HAS_MULTI2
	case S_DIN_to_MULTI2:
		flow_mode = DIN_MULTI2_DOUT;
		break;
#endif
	default:
		DX_LOG_ERR("invalid flow mode, flow_mode = %d \n", flow_mode);
		return;
	}

	/* Process */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], flow_mode);
	if (likely(areq_ctx->dma_buf_type == DX_DMA_BUF_DLLI)){
		DX_LOG_DEBUG(" data params addr 0x%llX length 0x%X \n",
			     (unsigned long long)sg_dma_address(req->src),
			     req->nbytes);
		DX_LOG_DEBUG(" data params addr 0x%llX length 0x%X \n",
			     (unsigned long long)sg_dma_address(req->dst),
			     req->nbytes);
		if (likely(!ctx_p->is_aes_ctr_prot)) {
			HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
					     sg_dma_address(req->src),
					     req->nbytes, AXI_ID, NS_BIT);
			HW_DESC_SET_DOUT_DLLI(&desc[*seq_size],
					      sg_dma_address(req->dst),
					      req->nbytes,
					      AXI_ID, NS_BIT, 1);
		} else {
			/* In case of counter protection the operation
			is done in the SEP so the stop queue and NO DMA 
			should be set */
			HW_DESC_SET_DIN_TYPE(&desc[*seq_size], NO_DMA,
					     sg_dma_address(req->src),
					     req->nbytes, AXI_ID, NS_BIT);
			HW_DESC_SET_DOUT_TYPE(&desc[*seq_size], NO_DMA,
					      sg_dma_address(req->dst),
					      req->nbytes,
					      AXI_ID, NS_BIT);
		}
	} else {
		/*The MLLI table was already loaded before */
		if (likely((areq_ctx->sec_dir != DX_NO_DMA_IS_SECURE))) {
			if (areq_ctx->sec_dir == DX_SRC_DMA_IS_SECURE) {
				HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
						     sg_dma_address(req->src),
						     req->nbytes, AXI_ID,
									NS_BIT);
				HW_DESC_SET_DOUT_MLLI(&desc[*seq_size], 
					ctx_p->drvdata->mlli_sram_addr, 
					areq_ctx->out_mlli_nents, AXI_ID,
						      NS_BIT,
						      !ctx_p->is_aes_ctr_prot);
			} else {
				HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_MLLI,
					ctx_p->drvdata->mlli_sram_addr,
					areq_ctx->in_mlli_nents, AXI_ID,
									NS_BIT);
				HW_DESC_SET_DOUT_DLLI(&desc[*seq_size],
						      sg_dma_address(req->dst),
						      req->nbytes,
						      AXI_ID, NS_BIT,
						      !ctx_p->is_aes_ctr_prot);
			}
		} else {
			/* In case of counter protection the flow is done in the
			   SEP and it can be done MLLI to MLLI*/
			HW_DESC_SET_DIN_TYPE(&desc[*seq_size], NO_DMA,
				ctx_p->drvdata->mlli_sram_addr,
				areq_ctx->in_mlli_nents, AXI_ID, NS_BIT);
			if (areq_ctx->out_nents == 0) {
				HW_DESC_SET_DOUT_TYPE(&desc[*seq_size], NO_DMA,
					ctx_p->drvdata->mlli_sram_addr, 
					areq_ctx->out_mlli_nents, AXI_ID, NS_BIT);
			} else {
				HW_DESC_SET_DOUT_TYPE(&desc[*seq_size],  NO_DMA,
				(ctx_p->drvdata->mlli_sram_addr +
				LLI_ENTRY_BYTE_SIZE * 
						areq_ctx->in_mlli_nents), 
				areq_ctx->out_mlli_nents, AXI_ID, NS_BIT);
			}
		}
	}
	if (unlikely(ctx_p->is_aes_ctr_prot)) {
		HW_DESC_STOP_QUEUE(&desc[*seq_size]);
	}
	(*seq_size)++;
	if (ctx_p->is_aes_ctr_prot) {
		/* dummy completion descriptor */
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
				     handle->dropped_buffer_dma_addr,
				     sizeof(handle->dropped_buffer),
				     AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_DLLI(&desc[*seq_size],
				      handle->dropped_buffer_dma_addr,
				      sizeof(handle->dropped_buffer),
				      AXI_ID, NS_BIT, 1);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], flow_mode);
		(*seq_size)++;
	}

}

static inline void
dx_ablkcipher_create_secure_bypass_data_desc(
	struct ablkcipher_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	struct dx_ablckcipher_handle * handle = 
					ctx_p->drvdata->ablckcipher_handle;
	unsigned int flow_mode = ctx_p->flow_mode;

	switch (ctx_p->flow_mode) {
	case BYPASS:
		break;
	default:
		DX_LOG_ERR("invalid flow mode, flow_mode = %d \n", flow_mode);
		return;
	}

	/* Process */
	HW_DESC_INIT(&desc[*seq_size]);
	if (likely(areq_ctx->dma_buf_type == DX_DMA_BUF_DLLI)){
		DX_LOG_DEBUG(" data params addr 0x%llX length 0x%X \n",
			     (unsigned long long)sg_dma_address(req->src),
			     req->nbytes);
		DX_LOG_DEBUG(" data params addr 0x%llX length 0x%X \n",
			     (unsigned long long)sg_dma_address(req->dst),
			     req->nbytes);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], NO_DMA,
				     sg_dma_address(req->src),
				     req->nbytes, AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_DLLI(&desc[*seq_size],
				      sg_dma_address(req->dst),
				      req->nbytes,
				      AXI_ID, NS_BIT, 0);
	} else {
		/*The MLLI table was already loaded before */
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], NO_DMA,
			ctx_p->drvdata->mlli_sram_addr,
			areq_ctx->in_mlli_nents, AXI_ID, NS_BIT);
		/* The Dout is holding the type of the input
		as the input must be NO_DMA for teh special descripotr 
		and the output must be DLLI due ot the restrictions*/ 
		HW_DESC_SET_DOUT_MLLI(&desc[*seq_size],
				      sg_dma_address(req->dst),
				      req->nbytes,
				      AXI_ID, NS_BIT, 0);
	}
	HW_DESC_STOP_QUEUE(&desc[*seq_size]);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], flow_mode);
	(*seq_size)++;

	/* dummy completion register */
	HW_DESC_INIT(&desc[*seq_size]);
	HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
			     handle->dropped_buffer_dma_addr,
			     sizeof(handle->dropped_buffer), AXI_ID, NS_BIT);
	HW_DESC_SET_DOUT_DLLI(&desc[*seq_size],
			      handle->dropped_buffer_dma_addr,
			      sizeof(handle->dropped_buffer),
			      AXI_ID, NS_BIT, 1);
	HW_DESC_SET_FLOW_MODE(&desc[*seq_size], flow_mode);
	(*seq_size)++;
}

#endif /*DX_CC_HAS_SEC_KEY*/

static int dx_ablkcipher_process(struct ablkcipher_request *req, 
				 enum sep_crypto_direction direction)
{
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct device *dev = &ctx_p->drvdata->plat_dev->dev;
	HwDesc_s desc[MAX_ABLKCIPHER_SEQ_LEN];
	struct dx_crypto_req dx_req = {0};
	int rc, seq_len = 0,cts_restore_flag = 0;
	DECL_CYCLE_COUNT_RESOURCES;

	DX_LOG_DEBUG("%s req=%p info=%p nbytes=%d\n",
		((direction==SEP_CRYPTO_DIRECTION_ENCRYPT)?"Encrypt":"Decrypt"),
		     req, req->info, req->nbytes);

	/* STAT_PHASE_0: Init and sanity checks */
	START_CYCLE_COUNT();
	
	/* TODO: check data length according to mode */
	if (unlikely(validate_data_size(ctx_p, req->nbytes))) {
		DX_LOG_ERR("Unsupported data size %d.\n", req->nbytes);
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_BLOCK_LEN);
		return -EINVAL;
	}
	if (req->nbytes == 0) {
		/* No data to process is valid */
		return 0;
	}
        /*For CTS in case of data size aligned to 16 use CBC mode*/
	if (((req->nbytes % AES_BLOCK_SIZE) == 0) && (ctx_p->cipher_mode == SEP_CIPHER_CBC_CTS)){

		ctx_p->cipher_mode = SEP_CIPHER_CBC;
		cts_restore_flag = 1;
	}


	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_ablkcipher_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = (direction == SEP_CRYPTO_DIRECTION_DECRYPT) ?
		STAT_OP_TYPE_DECODE : STAT_OP_TYPE_ENCODE;

#endif

	/* Setup request context */
	areq_ctx->gen_ctx.op_type = direction;
	
	END_CYCLE_COUNT(direction, STAT_PHASE_0);

	/* STAT_PHASE_1: Map buffers */
	START_CYCLE_COUNT();
	
	rc = dx_buffer_mgr_map_ablkcipher_request(ctx_p->drvdata, req);
	if (unlikely(rc != 0)) {
		DX_LOG_ERR("map_request() failed\n");
		goto exit_process;
	}

	END_CYCLE_COUNT(direction, STAT_PHASE_1);

	/* STAT_PHASE_2: Create sequence */
	START_CYCLE_COUNT();

	/* Setup processing */
#if DX_CC_HAS_SEC_KEY
	if (ctx_p->is_secure_key == 0) {
#endif /*DX_CC_HAS_SEC_KEY*/
#if DX_CC_HAS_MULTI2
		if (ctx_p->flow_mode == S_DIN_to_MULTI2) {
			dx_ablkcipher_create_multi2_setup_desc(req,
							       desc,
							       &seq_len);
		} else
#endif /*DX_CC_HAS_MULTI2*/
		{
			dx_ablkcipher_create_setup_desc(req, desc, &seq_len);
		}
		/* Data processing */
		dx_ablkcipher_create_data_desc(req, desc, &seq_len);
#if DX_CC_HAS_SEC_KEY
	} else {
		dx_ablkcipher_create_secure_key_mlli_desc(req, desc, &seq_len);
		dx_ablkcipher_create_secure_key_setup_desc(req, desc, &seq_len);
		/* Data processing */
		dx_ablkcipher_create_secure_key_data_desc(req, desc, &seq_len);
		dx_ablkcipher_create_disable_secure_key_setup_desc(req, 
								   desc,
								   &seq_len);
	}
#endif /*DX_CC_HAS_SEC_KEY*/

	/* do we need to generate IV? */
	if (areq_ctx->is_giv == true) {
		dx_req.ivgen_dma_addr[0] = areq_ctx->gen_ctx.iv_dma_addr;
		dx_req.ivgen_dma_addr_len = 1;
		/* set the IV size (8/16 B long)*/
		dx_req.ivgen_size = crypto_ablkcipher_ivsize(tfm);
	}
	END_CYCLE_COUNT(direction, STAT_PHASE_2);

	/* STAT_PHASE_3: Lock HW and push sequence */
	START_CYCLE_COUNT();
	
	rc = send_request(ctx_p->drvdata, &dx_req, desc, seq_len, 1);
	if (unlikely(rc != -EINPROGRESS)) {
		/* Failed to send the request or request
						completed synchronously */
		dx_buffer_mgr_unmap_ablkcipher_request(dev, req);
	}

	END_CYCLE_COUNT(direction, STAT_PHASE_3);

exit_process:
	if (cts_restore_flag != 0)
		ctx_p->cipher_mode = SEP_CIPHER_CBC_CTS;
	
	return rc;
}

static int dx_ablkcipher_process_secure_bypass(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct dx_ablkcipher_ctx *ctx_p = crypto_ablkcipher_ctx(tfm);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	struct device *dev = &ctx_p->drvdata->plat_dev->dev;
	HwDesc_s desc[MAX_ABLKCIPHER_SEQ_LEN];
	struct dx_crypto_req dx_req = {0};
	int rc, seq_len = 0;
	DECL_CYCLE_COUNT_RESOURCES;

	DX_LOG_DEBUG("req=%p info=%p nbytes=%d\n",
		     req, req->info, req->nbytes);

	/* STAT_PHASE_0: Init and sanity checks */
	START_CYCLE_COUNT();
	
	if (req->nbytes == 0) {
		/* No data to process is valid */
		return 0;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_ablkcipher_complete;
	dx_req.user_arg = (void *)req;
#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = (direction == SEP_CRYPTO_DIRECTION_DECRYPT) ?
		STAT_OP_TYPE_DECODE : STAT_OP_TYPE_ENCODE;

#endif

	
	END_CYCLE_COUNT(direction, STAT_PHASE_0);

	/* STAT_PHASE_1: Map buffers */
	START_CYCLE_COUNT();
	
	rc = dx_buffer_mgr_map_ablkcipher_request(ctx_p->drvdata, req);
	if (unlikely(rc != 0)) {
		DX_LOG_ERR("map_request() failed\n");
		goto exit_process;
	}
	if(areq_ctx->sec_dir == DX_SRC_DMA_IS_SECURE) {
		rc = -ENOMEM;
		goto free_mem;
	}
	END_CYCLE_COUNT(direction, STAT_PHASE_1);

	/* STAT_PHASE_2: Create sequence */
	START_CYCLE_COUNT();

	/* Setup processing */
	dx_ablkcipher_create_secure_key_mlli_desc(req, desc, &seq_len);
	dx_ablkcipher_create_secure_bypass_setup_desc(req, desc, &seq_len);
	/* Data processing */
	dx_ablkcipher_create_secure_bypass_data_desc(req, desc, &seq_len);
	dx_ablkcipher_create_disable_secure_key_setup_desc(req, 
							   desc,
							   &seq_len);

	END_CYCLE_COUNT(direction, STAT_PHASE_2);

	/* STAT_PHASE_3: Lock HW and push sequence */
	START_CYCLE_COUNT();
	
	rc = send_request(ctx_p->drvdata, &dx_req, desc, seq_len, 1);
free_mem:
	if (unlikely(rc != -EINPROGRESS)) {
		/* Failed to send the request or request
						completed synchronously */
		dx_buffer_mgr_unmap_ablkcipher_request(dev, req);
	}

	END_CYCLE_COUNT(direction, STAT_PHASE_3);
exit_process:

	
	return rc;
}

static void dx_ablkcipher_complete(struct device *dev, void *dx_req)
{
	struct ablkcipher_request *areq = (struct ablkcipher_request *)dx_req;
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(areq);

	DECL_CYCLE_COUNT_RESOURCES;

	START_CYCLE_COUNT();
	dx_buffer_mgr_unmap_ablkcipher_request(dev, areq);
	areq->info = areq_ctx->backup_info;
	END_CYCLE_COUNT(STAT_OP_TYPE_GENERIC, STAT_PHASE_4);
	
	ablkcipher_request_complete(areq, 0);
}

static int dx_ablkcipher_encrypt(struct ablkcipher_request *req)
{
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);
	areq_ctx->backup_info = req->info;
	areq_ctx->is_giv = false;
	return dx_ablkcipher_process(req, SEP_CRYPTO_DIRECTION_ENCRYPT);
}

static int dx_ablkcipher_decrypt(struct ablkcipher_request *req)
{
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(req);

	areq_ctx->backup_info = req->info;
	areq_ctx->is_giv = false;
	return dx_ablkcipher_process(req, SEP_CRYPTO_DIRECTION_DECRYPT);
}


static int dx_ablkcipher_givencrypt(struct skcipher_givcrypt_request *req)
{
	struct crypto_ablkcipher *tfm = skcipher_givcrypt_reqtfm(req);
	struct ablkcipher_request *subreq = skcipher_givcrypt_reqctx(req);
	struct ablkcipher_req_ctx *areq_ctx = ablkcipher_request_ctx(subreq);
	int rc;
	/*set the correct tfm and req params*/
	ablkcipher_request_set_tfm(subreq, skcipher_geniv_cipher(tfm));
	ablkcipher_request_set_crypt(subreq, req->creq.src, req->creq.dst,
				     req->creq.nbytes, req->creq.info);
	ablkcipher_request_set_callback(subreq, req->creq.base.flags,
					req->creq.base.complete,
					req->creq.base.data);
	/* Backup orig. IV */
	areq_ctx->backup_info = subreq->info;
	/* request IV points to payload's header */
	subreq->info = req->giv;
	/*set the giv flag */
	areq_ctx->is_giv = true;
	rc = dx_ablkcipher_process(subreq, SEP_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS)
		subreq->info = areq_ctx->backup_info;

	return rc;
}

/* DX Block cipher alg */
static struct dx_alg_template ablkcipher_algs[] = {
#if DX_CC_HAS_AES_XTS
	{
		.name = "xts(aes)",
		.driver_name = "xts-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE * 2,
			.max_keysize = AES_MAX_KEY_SIZE * 2,
			.ivsize = AES_BLOCK_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_CIPHER_XTS,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 0,
	},
#endif /*DX_CC_HAS_AES_XTS*/
	{
		.name = "ecb(aes)",
		.driver_name = "ecb-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = 0,
			},
		.cipher_mode = SEP_CIPHER_ECB,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 0,
	},
	{
		.name = "cbc(aes)",
		.driver_name = "cbc-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 0,
	},
	{
		.name = "ofb(aes)",
		.driver_name = "ofb-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_CIPHER_OFB,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 0,
	},
#if DX_CC_HAS_AES_CTS
	{
		.name = "cts1(cbc(aes))",
		.driver_name = "cts1-cbc-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_CIPHER_CBC_CTS,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 0,
	},
#endif
	{
		.name = "ctr(aes)",
		.driver_name = "ctr-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 0,
	},
	{
		.name = "cbc(des3_ede)",
		.driver_name = "cbc-3des-dx",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.is_secure_key = 0,
	},
	{
		.name = "ecb(des3_ede)",
		.driver_name = "ecb-3des-dx",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = 0,
			},
		.cipher_mode = SEP_CIPHER_ECB,
		.flow_mode = S_DIN_to_DES,
		.is_secure_key = 0,
	},
	{
		.name = "cbc(des)",
		.driver_name = "cbc-des-dx",
		.blocksize = DES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BLOCK_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.is_secure_key = 0,
	},
	{
		.name = "ecb(des)",
		.driver_name = "ecb-des-dx",
		.blocksize = DES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = 0,
			},
		.cipher_mode = SEP_CIPHER_ECB,
		.flow_mode = S_DIN_to_DES,
		.is_secure_key = 0,
	},
#if DX_CC_HAS_MULTI2
	{
		.name = "cbc(multi2)",
		.driver_name = "cbc-multi2-dx",
		.blocksize = SEP_MULTI2_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = SEP_MULTI2_SYSTEM_N_DATA_KEY_SIZE + 1,
			.max_keysize = SEP_MULTI2_SYSTEM_N_DATA_KEY_SIZE + 1,
			.ivsize = SEP_MULTI2_IV_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_MULTI2_CBC,
		.flow_mode = S_DIN_to_MULTI2,
		.is_secure_key = 0,
	},
	{
		.name = "ofb(multi2)",
		.driver_name = "ofb-multi2-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_encrypt,
			.min_keysize = SEP_MULTI2_SYSTEM_N_DATA_KEY_SIZE + 1,
			.max_keysize = SEP_MULTI2_SYSTEM_N_DATA_KEY_SIZE + 1,
			.ivsize = SEP_MULTI2_IV_SIZE,
			.geniv = "dx-ablkcipher-gen-iv",
			},
		.cipher_mode = SEP_MULTI2_OFB,
		.flow_mode = S_DIN_to_MULTI2,
		.is_secure_key = 0,
	},
#endif /*DX_CC_HAS_MULTI2*/
#if DX_CC_HAS_SEC_KEY
	{
		.name = "cbc(saes)",
		.driver_name = "cbc-saes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_secure_key_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.max_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.ivsize = AES_BLOCK_SIZE,
			},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 1,
	},
#if DX_CC_HAS_AES_CTS
	{
		.name = "cts1(cbc(saes))",
		.driver_name = "cts1-cbc-saes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_secure_key_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.max_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.ivsize = AES_BLOCK_SIZE,
			},
		.cipher_mode = SEP_CIPHER_CBC_CTS,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 1,
	},
#endif /*DX_CC_HAS_AES_CTS*/
	{
		.name = "ctr(saes)",
		.driver_name = "ctr-saes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_secure_key_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.max_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.ivsize = AES_BLOCK_SIZE,
			},
		.cipher_mode = SEP_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.is_secure_key = 1,
	},
#if DX_CC_HAS_MULTI2
	{
		.name = "cbc(smulti2)",
		.driver_name = "cbc-smulti2-dx",
		.blocksize = SEP_MULTI2_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_secure_key_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_decrypt,
			.min_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.max_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.ivsize = SEP_MULTI2_IV_SIZE,
			},
		.cipher_mode = SEP_MULTI2_CBC,
		.flow_mode = S_DIN_to_MULTI2,
		.is_secure_key = 1,
	},
	{
		.name = "ofb(smulti2)",
		.driver_name = "ofb-smulti2-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_secure_key_setkey,
			.encrypt = dx_ablkcipher_encrypt,
			.decrypt = dx_ablkcipher_encrypt,
			.min_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.max_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.ivsize = SEP_MULTI2_IV_SIZE,
			},
		.cipher_mode = SEP_MULTI2_OFB,
		.flow_mode = S_DIN_to_MULTI2,
		.is_secure_key = 1,
	},
#endif /*DX_CC_HAS_MULTI2*/
	{
		.name = "sbypass",
		.driver_name = "sbypass-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_ABLKCIPHER,
		.template_ablkcipher = {
			.setkey = dx_ablkcipher_secure_key_setkey,
			.encrypt = dx_ablkcipher_process_secure_bypass,
			.decrypt = dx_ablkcipher_process_secure_bypass,
			.min_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			.max_keysize = DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES,
			},
		.cipher_mode = SEP_CIPHER_NULL_MODE,
		.flow_mode = BYPASS,
		.is_secure_key = 1,
	},
#endif /*DX_CC_HAS_SEC_KEY*/
};

static 
struct dx_crypto_alg *dx_ablkcipher_create_alg(struct dx_alg_template *template)
{
	struct dx_crypto_alg *t_alg;
	struct crypto_alg *alg;

	t_alg = kzalloc(sizeof(struct dx_crypto_alg), GFP_KERNEL);
	if (!t_alg) {
		DX_LOG_ERR("failed to allocate t_alg\n");
		return ERR_PTR(-ENOMEM);
	}

	alg = &t_alg->crypto_alg;

	snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s", template->name);
	snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 template->driver_name);
	alg->cra_module = THIS_MODULE;
	alg->cra_priority = DX_CRA_PRIO;
	alg->cra_blocksize = template->blocksize;
	alg->cra_alignmask = 0;
	alg->cra_ctxsize = sizeof(struct dx_ablkcipher_ctx);
	alg->cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY |
			template->type;
	alg->cra_init = dx_ablkcipher_init;
	alg->cra_exit = dx_ablkcipher_exit;
	alg->cra_type = &crypto_ablkcipher_type;
	alg->cra_ablkcipher = template->template_ablkcipher;

	t_alg->cipher_mode = template->cipher_mode;
	t_alg->flow_mode = template->flow_mode;
	t_alg->is_secure_key = template->is_secure_key;

	return t_alg;
}

static struct crypto_template dx_ablkcipher_giv_tmpl;

int dx_ablkcipher_free(struct dx_drvdata *drvdata)
{
	struct dx_crypto_alg *t_alg, *n;
	struct dx_ablckcipher_handle *ablckcipher_handle = 
						drvdata->ablckcipher_handle;
	struct device *dev;
	dev = &drvdata->plat_dev->dev;

	if (ablckcipher_handle != NULL) {
		/* Remove registered algs */
		list_for_each_entry_safe(t_alg, n,
				&ablckcipher_handle->ablkcipher_alg_list,
					 entry) {
			crypto_unregister_alg(&t_alg->crypto_alg);
			list_del(&t_alg->entry);
			kfree(t_alg);
		}
		if (ablckcipher_handle->dropped_buffer_dma_addr != 0) {
			DX_RESTORE_DMA_ADDR_TO_48BIT(
				ablckcipher_handle->dropped_buffer_dma_addr);
			dma_unmap_single(dev,
			ablckcipher_handle->dropped_buffer_dma_addr,
			sizeof(ablckcipher_handle->dropped_buffer),
			DMA_TO_DEVICE);
			ablckcipher_handle->dropped_buffer_dma_addr = 0;
		}
		kfree(ablckcipher_handle);
		drvdata->ablckcipher_handle = NULL;

		crypto_unregister_template(&dx_ablkcipher_giv_tmpl);
	}
	return 0;
}



int dx_ablkcipher_alloc(struct dx_drvdata *drvdata)
{
	struct dx_ablckcipher_handle *ablkcipher_handle;
	struct dx_crypto_alg *t_alg;
	int rc = -ENOMEM;
	int alg;

	ablkcipher_handle = kmalloc(sizeof(struct dx_ablckcipher_handle),
		GFP_KERNEL);
	if (ablkcipher_handle == NULL)
		return -ENOMEM;

	ablkcipher_handle->dropped_buffer_dma_addr = dma_map_single(
		&drvdata->plat_dev->dev,
		&ablkcipher_handle->dropped_buffer,
		sizeof(ablkcipher_handle->dropped_buffer),
		DMA_TO_DEVICE);
	if (ablkcipher_handle->dropped_buffer_dma_addr == 0) {
		DX_LOG_ERR("Mapping dummy DMA failed\n");
		goto fail0;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(ablkcipher_handle->dropped_buffer_dma_addr,
				    sizeof(ablkcipher_handle->dropped_buffer));
#if DX_CC_HAS_SEC_KEY
	/*set 32 low bits*/
	WRITE_REGISTER(drvdata->cc_base + 
		       DX_CC_REG_OFFSET(CRY_KERNEL,
			       DSCRPTR_FILTER_DROPPED_ADDRESS),
		       (ablkcipher_handle->dropped_buffer_dma_addr & 
								UINT32_MAX));
	/*set 32 high bits*/
	WRITE_REGISTER(drvdata->cc_base + 
		       DX_CC_REG_OFFSET(CRY_KERNEL,
			       DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH),
		       (ablkcipher_handle->dropped_buffer_dma_addr >> 32));
#endif

	drvdata->ablckcipher_handle = ablkcipher_handle;
	INIT_LIST_HEAD(&ablkcipher_handle->ablkcipher_alg_list);

	/* Linux crypto */
	DX_LOG_DEBUG("Number of algorithms = %zu\n", ARRAY_SIZE(ablkcipher_algs));
	for (alg = 0; alg < ARRAY_SIZE(ablkcipher_algs); alg++) {
		DX_LOG_DEBUG("creating %s\n", ablkcipher_algs[alg].driver_name);
		t_alg = dx_ablkcipher_create_alg(&ablkcipher_algs[alg]);
		if (IS_ERR(t_alg)) {
			rc = PTR_ERR(t_alg);
			DX_LOG_ERR("%s alg allocation failed\n",
				 ablkcipher_algs[alg].driver_name);
			goto fail0;
		}
		t_alg->drvdata = drvdata;

		DX_LOG_DEBUG("registering %s\n", ablkcipher_algs[alg].driver_name);
		rc = crypto_register_alg(&t_alg->crypto_alg);
		DX_LOG_DEBUG("%s alg registration rc = %x\n",
			t_alg->crypto_alg.cra_driver_name, rc);
		if (unlikely(rc != 0)) {
			DX_LOG_ERR("%s alg registration failed\n",
				t_alg->crypto_alg.cra_driver_name);
			kfree(t_alg);
			goto fail0;
		} else {
			list_add_tail(&t_alg->entry, 
				      &ablkcipher_handle->ablkcipher_alg_list);
			DX_LOG_DEBUG("Registered %s\n", 
					t_alg->crypto_alg.cra_driver_name);
		}
	}
	rc = crypto_register_template(&dx_ablkcipher_giv_tmpl);
	if (rc != 0) {
		goto fail0;
	}
	return 0;

fail0:
	dx_ablkcipher_free(drvdata);
	return rc;
}

static int dx_ablkcipher_giv_init(struct crypto_tfm *tfm)
{
	tfm->crt_ablkcipher.reqsize = sizeof(struct ablkcipher_request) + sizeof(struct ablkcipher_req_ctx);
	return skcipher_geniv_init(tfm);
}

static void dx_ablkcipher_giv_exit(struct crypto_tfm *tfm)
{
	return skcipher_geniv_exit(tfm);
}

static struct crypto_instance *dx_ablkcipher_giv_alloc(struct rtattr **tb)
{
	struct crypto_instance *inst;

	inst = skcipher_geniv_alloc(&dx_ablkcipher_giv_tmpl, tb, 0, 0);
	if (IS_ERR(inst))
		return inst;


	inst->alg.cra_ablkcipher.givencrypt = dx_ablkcipher_givencrypt;

	inst->alg.cra_init = dx_ablkcipher_giv_init;
	inst->alg.cra_exit = dx_ablkcipher_giv_exit;


	return inst;

}

static void dx_ablkcipher_giv_free(struct crypto_instance *inst)
{
	skcipher_geniv_free(inst);
}

static struct crypto_template dx_ablkcipher_giv_tmpl = {
	.name = "dx-ablkcipher-gen-iv",
	.alloc = dx_ablkcipher_giv_alloc,
	.free = dx_ablkcipher_giv_free,
	.module = THIS_MODULE,
};

