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
#include <crypto/internal/hash.h>
#include <crypto/aead.h>
#include <crypto/sha.h>
#include <crypto/ctr.h>
#include <crypto/authenc.h>
#include <crypto/aes.h>
#include <crypto/des.h>
#include <linux/rtnetlink.h>

#include "dx_config.h"
#include "dx_driver.h"
#include "dx_buffer_mgr.h"
#include "dx_aead.h"
#include "dx_request_mgr.h"
#include "dx_hash.h"
#include "dx_sysfs.h"
#include "dx_sram_mgr.h"
#include "dx_hash.h"

#define template_aead	template_u.aead

#define MAX_AEAD_SETKEY_SEQ 12
#define MAX_AEAD_PROCESS_SEQ 23

#define MAX_HMAC_DIGEST_SIZE (SHA256_DIGEST_SIZE)
#define MAX_HMAC_BLOCK_SIZE (SHA256_BLOCK_SIZE)

#define AES_CCM_RFC4309_NONCE_SIZE 3
#define MAX_NONCE_SIZE CTR_RFC3686_NONCE_SIZE


/* Value of each ICV_CMP byte (of 8) in case of success */
#define ICV_VERIF_OK 0x01	

struct dx_aead_handle {
	dx_sram_addr_t sram_workspace_addr;
	struct list_head aead_list;
};

struct dx_aead_ctx {
	struct dx_drvdata *drvdata;
	uint8_t ctr_nonce[MAX_NONCE_SIZE]; /* used for ctr3686 iv and aes ccm */
	uint8_t *enckey;
	dma_addr_t enckey_dma_addr;
	union {
		struct {
			uint8_t *padded_authkey;
			uint8_t *ipad_opad; /* IPAD, OPAD*/
			dma_addr_t padded_authkey_dma_addr;
			dma_addr_t ipad_opad_dma_addr;
		} hmac;
		struct {
			uint8_t *xcbc_keys; /* K1,K2,K3 */
			dma_addr_t xcbc_keys_dma_addr;
		} xcbc;
	} auth_state;
	unsigned int enc_keylen;
	unsigned int auth_keylen;
	unsigned int authsize; /* Actual (reduced?) size of the MAC/ICv */
	enum sep_cipher_mode cipher_mode;
	enum FlowMode flow_mode;
	enum sep_hash_mode auth_mode;
};


static void dx_aead_exit(struct crypto_tfm *tfm)
{
	struct dx_aead_ctx *ctx = crypto_tfm_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;

	DX_LOG_DEBUG("Clearing context @%p for %s\n",
		crypto_tfm_ctx(tfm), crypto_tfm_alg_name(tfm));

	/* Unmap enckey buffer */
	if (ctx->enckey != NULL) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(ctx->enckey_dma_addr);
		dma_free_coherent(dev, AES_MAX_KEY_SIZE, ctx->enckey, ctx->enckey_dma_addr);
		DX_LOG_DEBUG("Freed enckey DMA buffer enckey_dma_addr=0x%llX\n",
			(unsigned long long)ctx->enckey_dma_addr);
		ctx->enckey_dma_addr = 0;
		ctx->enckey = NULL;
	}
	
	if (ctx->auth_mode == SEP_HASH_XCBC_MAC) { /* XCBC authetication */
		if (ctx->auth_state.xcbc.xcbc_keys != NULL) {
			DX_RESTORE_DMA_ADDR_TO_48BIT(
				ctx->auth_state.xcbc.xcbc_keys_dma_addr);
			dma_free_coherent(dev, SEP_AES_128_BIT_KEY_SIZE * 3,
				ctx->auth_state.xcbc.xcbc_keys, 
				ctx->auth_state.xcbc.xcbc_keys_dma_addr);
		}
		DX_LOG_DEBUG("Freed xcbc_keys DMA buffer xcbc_keys_dma_addr=0x%llX\n",
			(unsigned long long)ctx->auth_state.xcbc.xcbc_keys_dma_addr);
		ctx->auth_state.xcbc.xcbc_keys_dma_addr = 0;
		ctx->auth_state.xcbc.xcbc_keys = NULL;
	} else if (ctx->auth_mode != SEP_HASH_NULL) { /* HMAC auth. */
		if (ctx->auth_state.hmac.ipad_opad != NULL) {
			DX_RESTORE_DMA_ADDR_TO_48BIT(
				ctx->auth_state.hmac.ipad_opad_dma_addr);
			dma_free_coherent(dev, 2 * MAX_HMAC_DIGEST_SIZE,
				ctx->auth_state.hmac.ipad_opad,
				ctx->auth_state.hmac.ipad_opad_dma_addr);
			DX_LOG_DEBUG("Freed ipad_opad DMA buffer ipad_opad_dma_addr=0x%llX\n",
				(unsigned long long)ctx->auth_state.hmac.ipad_opad_dma_addr);
			ctx->auth_state.hmac.ipad_opad_dma_addr = 0;
			ctx->auth_state.hmac.ipad_opad = NULL;
		}
		if (ctx->auth_state.hmac.padded_authkey != NULL) {
			DX_RESTORE_DMA_ADDR_TO_48BIT(
				ctx->auth_state.hmac.padded_authkey_dma_addr);
			dma_free_coherent(dev, MAX_HMAC_BLOCK_SIZE,
				ctx->auth_state.hmac.padded_authkey,
				ctx->auth_state.hmac.padded_authkey_dma_addr);
			DX_LOG_DEBUG("Freed padded_authkey DMA buffer padded_authkey_dma_addr=0x%llX\n",
				(unsigned long long)ctx->auth_state.hmac.padded_authkey_dma_addr);
			ctx->auth_state.hmac.padded_authkey_dma_addr = 0;
			ctx->auth_state.hmac.padded_authkey = NULL;
		}
	}
}

static int dx_aead_init(struct crypto_tfm *tfm)
{
	struct dx_aead_ctx *ctx = crypto_tfm_ctx(tfm);
	struct aead_tfm *aead = &tfm->crt_aead;
	struct crypto_alg *alg = tfm->__crt_alg;
	struct dx_crypto_alg *dx_alg =
			container_of(alg, struct dx_crypto_alg, crypto_alg);
	struct device *dev;

	DX_LOG_DEBUG("Initializing context @%p for %s\n", ctx, crypto_tfm_alg_name(tfm));

	/* Initialize modes in instance */
	ctx->cipher_mode = dx_alg->cipher_mode;
	ctx->flow_mode = dx_alg->flow_mode;
	ctx->auth_mode = dx_alg->auth_mode;
	ctx->drvdata = dx_alg->drvdata;
	dev = &ctx->drvdata->plat_dev->dev;

	aead->reqsize = sizeof(struct aead_req_ctx);

	/* Allocate key buffer, cache line aligned */
	ctx->enckey = dma_alloc_coherent(dev, AES_MAX_KEY_SIZE,
		&ctx->enckey_dma_addr, GFP_KERNEL);
	if (ctx->enckey == NULL) {
		DX_LOG_ERR("Failed allocating key buffer\n");
		goto init_failed;
	}
	DX_UPDATE_DMA_ADDR_TO_48BIT(ctx->enckey_dma_addr, AES_MAX_KEY_SIZE);
	DX_LOG_DEBUG("Allocated enckey buffer in context ctx->enckey=@%p\n", ctx->enckey);

	/* Set default authlen value */
	ctx->authsize = tfm->crt_u.aead.authsize;
	if (ctx->auth_mode == SEP_HASH_XCBC_MAC) { /* XCBC authetication */
		/* Allocate dma-coherent buffer for XCBC's K1+K2+K3 */
		/* (and temporary for user key - up to 256b) */
		ctx->auth_state.xcbc.xcbc_keys = dma_alloc_coherent(dev,
			SEP_AES_128_BIT_KEY_SIZE * 3,
			&ctx->auth_state.xcbc.xcbc_keys_dma_addr, GFP_KERNEL);
		if (ctx->auth_state.xcbc.xcbc_keys == NULL) {
			DX_LOG_ERR("Failed allocating buffer for XCBC keys\n");
			goto init_failed;
		}
		DX_UPDATE_DMA_ADDR_TO_48BIT(
			ctx->auth_state.xcbc.xcbc_keys_dma_addr,
			SEP_AES_128_BIT_KEY_SIZE * 3);
	} else if (ctx->auth_mode != SEP_HASH_NULL) { /* HMAC authentication */
		/* Allocate dma-coherent buffer for IPAD + OPAD */
		ctx->auth_state.hmac.ipad_opad = dma_alloc_coherent(dev,
			2 * MAX_HMAC_DIGEST_SIZE,
			&ctx->auth_state.hmac.ipad_opad_dma_addr, GFP_KERNEL);
		if (ctx->auth_state.hmac.ipad_opad == NULL) {
			DX_LOG_ERR("Failed allocating IPAD/OPAD buffer\n");
			goto init_failed;
		}
		DX_UPDATE_DMA_ADDR_TO_48BIT(
			ctx->auth_state.hmac.ipad_opad_dma_addr,
			2 * MAX_HMAC_DIGEST_SIZE);
		DX_LOG_DEBUG("Allocated authkey buffer in context ctx->authkey=@%p\n",
			ctx->auth_state.hmac.ipad_opad);
	
		ctx->auth_state.hmac.padded_authkey = dma_alloc_coherent(dev,
			MAX_HMAC_BLOCK_SIZE,
			&ctx->auth_state.hmac.padded_authkey_dma_addr, GFP_KERNEL);
		if (ctx->auth_state.hmac.padded_authkey == NULL) {
			DX_LOG_ERR("failed to allocate padded_authkey\n");
			goto init_failed;
		}	
		DX_UPDATE_DMA_ADDR_TO_48BIT(
			ctx->auth_state.hmac.padded_authkey_dma_addr,
			MAX_HMAC_BLOCK_SIZE);
	} else {
		ctx->auth_state.hmac.ipad_opad = NULL;
		ctx->auth_state.hmac.padded_authkey = NULL;
	}

	return 0;

init_failed:
	dx_aead_exit(tfm);
	return -ENOMEM;
}
 

static void dx_aead_complete(struct device *dev, void *dx_req)
{
	struct aead_request *areq = (struct aead_request *)dx_req;
	struct aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	struct crypto_aead *tfm = crypto_aead_reqtfm(dx_req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	int err = 0;
	DECL_CYCLE_COUNT_RESOURCES;

	START_CYCLE_COUNT();

	dx_buffer_mgr_unmap_aead_request(dev, areq);



	/* Restore ordinary iv pointer */
	areq->iv = areq_ctx->backup_iv;

	if (areq_ctx->gen_ctx.op_type == SEP_CRYPTO_DIRECTION_DECRYPT) {
		if (memcmp(areq_ctx->mac_buf, areq_ctx->icv_virt_addr,
			ctx->authsize) != 0) {
			DX_LOG_DEBUG("Payload authentication failure, "
				"(auth-size=%d, cipher=%d).\n",
				ctx->authsize, ctx->cipher_mode);
			err = -EBADMSG;
		}
	} else { /*ENCRYPT*/
		if (unlikely(areq_ctx->is_icv_fragmented == true))
			dx_buffer_mgr_copy_scatterlist_portion(
				areq_ctx->mac_buf, areq->dst, areq->cryptlen,
				areq->cryptlen + ctx->authsize, DX_SG_FROM_BUF);

		/* If an IV was generated, copy it back to the user provided buffer. */
		if (areq_ctx->backup_giv != NULL) {
			if (ctx->cipher_mode == SEP_CIPHER_CTR) {
				memcpy(areq_ctx->backup_giv, areq_ctx->ctr_iv + CTR_RFC3686_NONCE_SIZE, CTR_RFC3686_IV_SIZE);
			} else if (ctx->cipher_mode == SEP_CIPHER_CCM) {
				memcpy(areq_ctx->backup_giv, areq_ctx->ctr_iv + CCM_BLOCK_IV_OFFSET, CCM_BLOCK_IV_SIZE);
			}
		}
	}


	END_CYCLE_COUNT(STAT_OP_TYPE_GENERIC, STAT_PHASE_4);
	aead_request_complete(areq, err);
}

static int xcbc_setkey(HwDesc_s *desc, struct dx_aead_ctx *ctx)
{
	/* Load the AES key */
	HW_DESC_INIT(&desc[0]);
	/* We are using for the source/user key the same buffer as for the output keys,
	   because after this key loading it is not needed anymore */
	HW_DESC_SET_DIN_TYPE(&desc[0], DMA_DLLI, ctx->auth_state.xcbc.xcbc_keys_dma_addr, ctx->auth_keylen, AXI_ID, NS_BIT);
	HW_DESC_SET_CIPHER_MODE(&desc[0], SEP_CIPHER_ECB);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[0], SEP_CRYPTO_DIRECTION_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[0], ctx->auth_keylen);
	HW_DESC_SET_FLOW_MODE(&desc[0], S_DIN_to_AES);
	HW_DESC_SET_SETUP_MODE(&desc[0], SETUP_LOAD_KEY0);

	HW_DESC_INIT(&desc[1]);
	HW_DESC_SET_DIN_CONST(&desc[1], 0x01010101, SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[1], DIN_AES_DOUT);
	HW_DESC_SET_DOUT_DLLI(&desc[1], ctx->auth_state.xcbc.xcbc_keys_dma_addr, AES_KEYSIZE_128, AXI_ID, NS_BIT, 0);

	HW_DESC_INIT(&desc[2]);
	HW_DESC_SET_DIN_CONST(&desc[2], 0x02020202, SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[2], DIN_AES_DOUT);
	HW_DESC_SET_DOUT_DLLI(&desc[2], (ctx->auth_state.xcbc.xcbc_keys_dma_addr
					 + AES_KEYSIZE_128),
			      AES_KEYSIZE_128, AXI_ID, NS_BIT, 0);

	HW_DESC_INIT(&desc[3]);
	HW_DESC_SET_DIN_CONST(&desc[3], 0x03030303, SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[3], DIN_AES_DOUT);
	HW_DESC_SET_DOUT_DLLI(&desc[3], (ctx->auth_state.xcbc.xcbc_keys_dma_addr
					  + 2 * AES_KEYSIZE_128),
			      AES_KEYSIZE_128, AXI_ID, NS_BIT, 0);

	return 4;
}

static int hmac_setkey(HwDesc_s *desc, struct dx_aead_ctx *ctx)
{
	unsigned int hmacPadConst[2] = { HMAC_IPAD_CONST, HMAC_OPAD_CONST };
	unsigned int digest_ofs = 0;
	unsigned int hash_mode = (ctx->auth_mode == SEP_HASH_SHA1) ? 
			SEP_HASH_HW_SHA1 : SEP_HASH_HW_SHA256;
	unsigned int digest_size = (ctx->auth_mode == SEP_HASH_SHA1) ? 
			SEP_SHA1_DIGEST_SIZE : SEP_SHA256_DIGEST_SIZE;

	int idx = 0;
	int i;

	/* calc derived HMAC key */
	for (i = 0; i < 2; i++) {
		/* Load hash initial state */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
		HW_DESC_SET_DIN_SRAM(&desc[idx],
			dx_ahash_get_larval_digest_sram_addr(
				ctx->drvdata, ctx->auth_mode),
			digest_size);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
		idx++;

		/* Load the hash current length*/
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
		HW_DESC_SET_DIN_CONST(&desc[idx], 0, HASH_LEN_SIZE);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
		idx++;

		/* Prepare ipad key */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_XOR_VAL(&desc[idx], hmacPadConst[i]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
		idx++;

		/* Perform HASH update */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
				   ctx->auth_state.hmac.padded_authkey_dma_addr,
				     SHA256_BLOCK_SIZE, AXI_ID, NS_BIT);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
		HW_DESC_SET_XOR_ACTIVE(&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
		idx++;

		/* Get the digset */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], 
				      (ctx->auth_state.hmac.ipad_opad_dma_addr +
				       digest_ofs),
				      digest_size, AXI_ID, NS_BIT, 0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
		HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_DISABLED);
		idx++;

		digest_ofs += digest_size;
	}

	return idx;
}

static int validate_keys_sizes(struct dx_aead_ctx *ctx)
{
	DX_LOG_DEBUG("enc_keylen=%u  authkeylen=%u\n",
		ctx->enc_keylen, ctx->auth_keylen);

	switch (ctx->auth_mode) {
	case SEP_HASH_SHA1:
	case SEP_HASH_SHA256:
		break;
	case SEP_HASH_XCBC_MAC:
		if ((ctx->auth_keylen != AES_KEYSIZE_128) &&
		    (ctx->auth_keylen != AES_KEYSIZE_192) &&
		    (ctx->auth_keylen != AES_KEYSIZE_256))
			return -ENOTSUPP;
		break;
	case SEP_HASH_NULL: /* Not authenc (e.g., CCM) - no auth_key) */
		if (ctx->auth_keylen > 0)
			return -EINVAL;
		break;
	default:
		DX_LOG_ERR("Invalid auth_mode=%d\n", ctx->auth_mode);
		return -EINVAL;
	}
	/* Check cipher key size */
	if (unlikely(ctx->flow_mode == S_DIN_to_DES)) {
		if (ctx->enc_keylen != DES3_EDE_KEY_SIZE) {
			DX_LOG_ERR("Invalid cipher(3DES) key size: %u\n",
				ctx->enc_keylen);
			return -EINVAL;
		}
	} else { /* Default assumed to be AES ciphers */
		if ((ctx->enc_keylen != AES_KEYSIZE_128) &&
		    (ctx->enc_keylen != AES_KEYSIZE_192) &&
		    (ctx->enc_keylen != AES_KEYSIZE_256)) {
			DX_LOG_ERR("Invalid cipher(AES) key size: %u\n",
				ctx->enc_keylen);
			return -EINVAL;
		}
	}

	return 0; /* All tests of keys sizes passed */
}
/*This function prepers the user key so it can pass to the hmac processing 
  (copy to intenral buffer or hash in case of key longer than block */
static int
dx_get_plain_hmac_key(struct crypto_aead *tfm, const u8 *key, unsigned int keylen)
{
	dma_addr_t key_dma_addr = 0;
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	uint32_t larval_addr = dx_ahash_get_larval_digest_sram_addr(
					ctx->drvdata, ctx->auth_mode);
	struct dx_crypto_req dx_req = {0};
	unsigned int blocksize;
	unsigned int digestsize;
	unsigned int hashmode;
	unsigned int idx = 0;
	int rc = 0;
	HwDesc_s desc[MAX_AEAD_SETKEY_SEQ];
	dma_addr_t padded_authkey_dma_addr = 
		ctx->auth_state.hmac.padded_authkey_dma_addr;

	switch (ctx->auth_mode) { /* auth_key required and >0 */
	case SEP_HASH_SHA1:
		blocksize = SHA1_BLOCK_SIZE;
		digestsize = SHA1_DIGEST_SIZE;
		hashmode = SEP_HASH_HW_SHA1;
		break;
	case SEP_HASH_SHA256:
	default:
		blocksize = SHA256_BLOCK_SIZE;
		digestsize = SHA256_DIGEST_SIZE;
		hashmode = SEP_HASH_HW_SHA256;
	}

	if (likely(keylen != 0)) {
		key_dma_addr = dma_map_single(dev, (void *)key, keylen, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(dev, key_dma_addr))) {
			DX_LOG_ERR("Mapping key va=0x%p len=%u for"
				   " DMA failed\n", key, keylen);
			return -ENOMEM;
		}
		DX_UPDATE_DMA_ADDR_TO_48BIT(key_dma_addr, keylen);
		if (keylen > blocksize) {
			/* Load hash initial state */
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], hashmode);
			HW_DESC_SET_DIN_SRAM(&desc[idx], larval_addr, digestsize);
			HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
			HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
			idx++;
	
			/* Load the hash current length*/
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], hashmode);
			HW_DESC_SET_DIN_CONST(&desc[idx], 0, HASH_LEN_SIZE);
			HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
			HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
			HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
			idx++;
	
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
					     key_dma_addr, 
					     keylen, AXI_ID, NS_BIT);
			HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
			idx++;
	
			/* Get hashed key */
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], hashmode); 
			HW_DESC_SET_DOUT_DLLI(&desc[idx],
					 padded_authkey_dma_addr,
					 digestsize,
					 AXI_ID, NS_BIT, 0);
			HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
			HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
			HW_DESC_SET_CIPHER_CONFIG1(&desc[idx],
							HASH_PADDING_DISABLED);
			HW_DESC_SET_CIPHER_CONFIG0(&desc[idx],
						   HASH_DIGEST_RESULT_LITTLE_ENDIAN);
			idx++;
	
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_DIN_CONST(&desc[idx], 0, (blocksize - digestsize));
			HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
			HW_DESC_SET_DOUT_DLLI(&desc[idx], 
					      (padded_authkey_dma_addr + digestsize),
					      (blocksize - digestsize),
					      AXI_ID, NS_BIT, 0);
			idx++;
		} else {
			HW_DESC_INIT(&desc[idx]);
			HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
					     key_dma_addr, 
					     keylen, AXI_ID, NS_BIT);
			HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
			HW_DESC_SET_DOUT_DLLI(&desc[idx], 
					      (padded_authkey_dma_addr),
					      keylen, AXI_ID, NS_BIT, 0);
			idx++;
	
			if ((blocksize - keylen) != 0) {
				HW_DESC_INIT(&desc[idx]);
				HW_DESC_SET_DIN_CONST(&desc[idx], 0,
						      (blocksize - keylen));
				HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
				HW_DESC_SET_DOUT_DLLI(&desc[idx], 
					(padded_authkey_dma_addr + keylen),
					(blocksize - keylen),
					AXI_ID, NS_BIT, 0);
				idx++;
			}
		}
	} else {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_CONST(&desc[idx], 0,
				      (blocksize - keylen));
		HW_DESC_SET_FLOW_MODE(&desc[idx], BYPASS);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], 
			padded_authkey_dma_addr,
			blocksize,
			AXI_ID, NS_BIT, 0);
		idx++;
	}

#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = STAT_OP_TYPE_SETKEY;
#endif

	rc = send_request(ctx->drvdata, &dx_req, desc, idx, 0);
	if (unlikely(rc != 0))
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);

	if (likely(key_dma_addr != 0)) {
		DX_RESTORE_DMA_ADDR_TO_48BIT(key_dma_addr);
		dma_unmap_single(dev, key_dma_addr, keylen, DMA_TO_DEVICE);
	}

	return rc;
}


static int
dx_aead_setkey(struct crypto_aead *tfm, const u8 *key, unsigned int keylen)
{
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct rtattr *rta = (struct rtattr *)key;
	struct dx_crypto_req dx_req = {0};
	struct crypto_authenc_key_param *param;
	HwDesc_s desc[MAX_AEAD_SETKEY_SEQ];
	int seq_len = 0, rc = -EINVAL;
	DECL_CYCLE_COUNT_RESOURCES;

	DX_LOG_DEBUG("Setting key in context @%p for %s. key=%p keylen=%u\n",
		ctx, crypto_tfm_alg_name(crypto_aead_tfm(tfm)), key, keylen);

	/* STAT_PHASE_0: Init and sanity checks */
	START_CYCLE_COUNT();

	if (ctx->auth_mode != SEP_HASH_NULL) { /* authenc() alg. */
		if (!RTA_OK(rta, keylen))
			goto badkey;
		if (rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
			goto badkey;
		if (RTA_PAYLOAD(rta) < sizeof(*param))
			goto badkey;
		param = RTA_DATA(rta);
		ctx->enc_keylen = be32_to_cpu(param->enckeylen);
		key += RTA_ALIGN(rta->rta_len);
		keylen -= RTA_ALIGN(rta->rta_len);
		if (keylen < ctx->enc_keylen)
			goto badkey;
		ctx->auth_keylen = keylen - ctx->enc_keylen;

		if (ctx->cipher_mode == SEP_CIPHER_CTR) {
			/* the nonce is stored in bytes at end of key */
			if (ctx->enc_keylen <
			    (AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE))
				goto badkey;
			/* Copy nonce from last 4 bytes in CTR key to
			*  first 4 bytes in CTR IV */
			memcpy(ctx->ctr_nonce, key + ctx->auth_keylen + ctx->enc_keylen -
				CTR_RFC3686_NONCE_SIZE, CTR_RFC3686_NONCE_SIZE);
			/* Set CTR key size */
			ctx->enc_keylen -= CTR_RFC3686_NONCE_SIZE;
		}
	} else { /* non-authenc - has just one key */
		ctx->enc_keylen = keylen;
		ctx->auth_keylen = 0;
	}

	rc = validate_keys_sizes(ctx);
	if (unlikely(rc != 0))
		goto badkey;

	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_0);
	/* STAT_PHASE_1: Copy key to ctx */
	START_CYCLE_COUNT();

	/* Get key material */
	memcpy(ctx->enckey, key + ctx->auth_keylen, ctx->enc_keylen);
	if (ctx->enc_keylen == 24)
		memset(ctx->enckey + 24, 0, SEP_AES_KEY_SIZE_MAX - 24);
	if (ctx->auth_mode == SEP_HASH_XCBC_MAC) {
		memcpy(ctx->auth_state.xcbc.xcbc_keys, key, ctx->auth_keylen);
	} else if (ctx->auth_mode != SEP_HASH_NULL) { /* HMAC */
		rc = dx_get_plain_hmac_key(tfm, key, ctx->auth_keylen);
		if (rc != 0)
			goto badkey;
	}

	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_1);
	
	/* STAT_PHASE_2: Create sequence */
	START_CYCLE_COUNT();

	switch (ctx->auth_mode) {
	case SEP_HASH_SHA1:
	case SEP_HASH_SHA256:
		seq_len = hmac_setkey(desc, ctx);
		break;
	case SEP_HASH_XCBC_MAC:
		seq_len = xcbc_setkey(desc, ctx);
		break;
	case SEP_HASH_NULL: /* non-authenc modes, e.g., CCM */
		break; /* No auth. key setup */
	default:
		DX_LOG_ERR("Unsupported authenc (%d)\n", ctx->auth_mode);
		rc = -ENOTSUPP;
		goto badkey;
	}

	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_2);

	/* STAT_PHASE_3: Submit sequence to HW */
	START_CYCLE_COUNT();
	
	if (seq_len > 0) { /* For CCM there is no sequence to setup the key */
#ifdef ENABLE_CYCLE_COUNT
		dx_req.op_type = STAT_OP_TYPE_SETKEY;
#endif
		rc = send_request(ctx->drvdata, &dx_req, desc, seq_len, 0);
		if (unlikely(rc != 0)) {
			DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
			goto setkey_error;
		}
	}

	/* Update STAT_PHASE_3 */
	END_CYCLE_COUNT(STAT_OP_TYPE_SETKEY, STAT_PHASE_3);
	return rc;

badkey:
	crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);

setkey_error:
	return rc;
}

#if DX_CC_HAS_AES_CCM
static int dx_rfc4309_ccm_setkey(struct crypto_aead *tfm, const u8 *key, unsigned int keylen)
{
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	int rc = 0;
	
	if (keylen < 3)
		return -EINVAL;

	keylen -= 3;
	memcpy(ctx->ctr_nonce, key + keylen, 3);

	rc = dx_aead_setkey(tfm, key, keylen);

	return rc;
}
#endif /*DX_CC_HAS_AES_CCM*/

static int dx_aead_setauthsize(
	struct crypto_aead *authenc,
	unsigned int authsize)
{
	struct dx_aead_ctx *ctx = crypto_aead_ctx(authenc);
	
	/* Unsupported auth. sizes */
	if ((authsize == 0) ||
	    (authsize > crypto_aead_alg(authenc)->maxauthsize)) {
		return -ENOTSUPP;
	}

	ctx->authsize = authsize;
	DX_LOG_DEBUG("authlen=%d\n", ctx->authsize);

	return 0;
}

#if DX_CC_HAS_AES_CCM
static int dx_rfc4309_ccm_setauthsize(struct crypto_aead *authenc,
				      unsigned int authsize)
{
	switch (authsize) {
	case 8:
	case 12:
	case 16:
		break;
	default:
		return -EINVAL;
	}

	return dx_aead_setauthsize(authenc, authsize);
}

static int dx_ccm_setauthsize(struct crypto_aead *authenc,
				      unsigned int authsize)
{
	switch (authsize) {
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
	case 16:
		break;
	default:
		return -EINVAL;
	}

	return dx_aead_setauthsize(authenc, authsize);
}
#endif /*DX_CC_HAS_AES_CCM*/

static inline void 
dx_aead_create_assoc_desc(
	struct aead_request *areq, 
	unsigned int flow_mode,
	HwDesc_s desc[], 
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(areq);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	enum dx_req_dma_buf_type assoc_dma_type = areq_ctx->assoc_buff_type;
	unsigned int idx = *seq_size;

	switch (assoc_dma_type) {
	case DX_DMA_BUF_DLLI:
		DX_LOG_DEBUG("ASSOC buffer type DLLI\n");
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
			sg_dma_address(areq->assoc),
			areq->assoclen, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		if (ctx->auth_mode == SEP_HASH_XCBC_MAC)
			HW_DESC_SET_DIN_NOT_LAST_INDICATION(&desc[idx]);
		break;
	case DX_DMA_BUF_MLLI:
		DX_LOG_DEBUG("ASSOC buffer type MLLI\n");
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_MLLI,
				     areq_ctx->assoc.sram_addr,
				     areq_ctx->assoc.mlli_nents,
				     AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		if (ctx->auth_mode == SEP_HASH_XCBC_MAC)
			HW_DESC_SET_DIN_NOT_LAST_INDICATION(&desc[idx]);
		break;
	case DX_DMA_BUF_NULL:
	default:
		DX_LOG_ERR("Invalid ASSOC buffer type\n");
	}

	*seq_size = (++idx);
}

static inline void
dx_aead_process_authenc_data_desc(
	struct aead_request *areq, 
	unsigned int flow_mode,
	HwDesc_s desc[], 
	unsigned int *seq_size,
	int direct)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	enum dx_req_dma_buf_type data_dma_type = areq_ctx->data_buff_type;
	unsigned int idx = *seq_size;

	switch (data_dma_type) {
	case DX_DMA_BUF_DLLI:
	{
		struct scatterlist *cipher =
			(direct == SEP_CRYPTO_DIRECTION_ENCRYPT) ?
			areq->dst : areq->src;

		DX_LOG_DEBUG("AUTHENC: SRC/DST buffer type DLLI\n");
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			sg_dma_address(cipher), areq_ctx->cryptlen,
			AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		break;
	}
	case DX_DMA_BUF_MLLI:
	{
		/* DOUBLE-PASS flow (as default)
		 * assoc. + iv + data -compact in one table
		 * if assoclen is ZERO only IV perform */
		dx_sram_addr_t mlli_addr = areq_ctx->assoc.sram_addr;
		uint32_t mlli_nents = areq_ctx->assoc.mlli_nents;

		if (likely(areq_ctx->is_single_pass == true)) {
			if (direct == SEP_CRYPTO_DIRECTION_ENCRYPT){
				mlli_addr = areq_ctx->dst.sram_addr;
				mlli_nents = areq_ctx->dst.mlli_nents;
			} else {
				mlli_addr = areq_ctx->src.sram_addr;
				mlli_nents = areq_ctx->src.mlli_nents;
			}
		}

		DX_LOG_DEBUG("AUTHENC: SRC/DST buffer type MLLI\n");
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_MLLI,
			mlli_addr, mlli_nents, AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		break;
	}
	case DX_DMA_BUF_NULL:
	default:
		DX_LOG_ERR("AUTHENC: Invalid SRC/DST buffer type\n");
	}

	*seq_size = (++idx);
}

static inline void
dx_aead_process_cipher_data_desc(
	struct aead_request *areq, 
	unsigned int flow_mode,
	HwDesc_s desc[], 
	unsigned int *seq_size)
{
	unsigned int idx = *seq_size;
	struct aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	enum dx_req_dma_buf_type data_dma_type = areq_ctx->data_buff_type;

	if (areq_ctx->cryptlen == 0)
		return; /*null processing*/

	switch (data_dma_type) {
	case DX_DMA_BUF_DLLI:
		DX_LOG_DEBUG("CIPHER: SRC/DST buffer type DLLI\n");
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			sg_dma_address(areq->src),
			areq_ctx->cryptlen, AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_DLLI(&desc[idx],
			sg_dma_address(areq->dst),
			areq_ctx->cryptlen, AXI_ID, NS_BIT, 0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		break;
	case DX_DMA_BUF_MLLI:
		DX_LOG_DEBUG("CIPHER: SRC/DST buffer type MLLI\n");
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_MLLI,
			areq_ctx->src.sram_addr,
			areq_ctx->src.mlli_nents, AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_MLLI(&desc[idx],
			areq_ctx->dst.sram_addr,
			areq_ctx->dst.mlli_nents, AXI_ID, NS_BIT, 0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], flow_mode);
		break;
	case DX_DMA_BUF_NULL:
	default:
		DX_LOG_ERR("CIPHER: Invalid SRC/DST buffer type\n");
	}

	*seq_size = (++idx);
}

static inline void dx_aead_process_digest_result_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;
	unsigned int hash_mode = (ctx->auth_mode == SEP_HASH_SHA1) ?
				SEP_HASH_HW_SHA1 : SEP_HASH_HW_SHA256;
	int direct = req_ctx->gen_ctx.op_type;

	/* Get final ICV result */
	if (direct == SEP_CRYPTO_DIRECTION_ENCRYPT) {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], req_ctx->icv_dma_addr,
			ctx->authsize, AXI_ID, NS_BIT, 1);
		if (ctx->auth_mode == SEP_HASH_XCBC_MAC) {
			HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC); 
		} else {
			HW_DESC_SET_CIPHER_CONFIG0(&desc[idx],
				HASH_DIGEST_RESULT_LITTLE_ENDIAN);
			HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
		}
	} else { /*Decrypt*/
		/* Get ICV out from hardware */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
		HW_DESC_SET_DOUT_DLLI(&desc[idx], req_ctx->mac_buf_dma_addr,
			ctx->authsize, AXI_ID, NS_BIT, 1);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], HASH_DIGEST_RESULT_LITTLE_ENDIAN);
		HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_DISABLED);
		if (ctx->auth_mode == SEP_HASH_XCBC_MAC) {
			HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
			HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
		} else {
			HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
		}
	}

	*seq_size = (++idx);
}

static inline void dx_aead_setup_cipher_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int hw_iv_size = req_ctx->hw_iv_size;
	unsigned int idx = *seq_size;
	int direct = req_ctx->gen_ctx.op_type;

	/* Setup cipher state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], direct);
	HW_DESC_SET_FLOW_MODE(&desc[idx], ctx->flow_mode);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
		req_ctx->gen_ctx.iv_dma_addr, hw_iv_size, AXI_ID, NS_BIT);
	if (ctx->cipher_mode == SEP_CIPHER_CTR) {
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
	} else {
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	}
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->cipher_mode);
	idx++;

	/* Setup enc. key */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], direct);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_FLOW_MODE(&desc[idx], ctx->flow_mode);
	if (ctx->flow_mode == S_DIN_to_AES) {
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr, 
			((ctx->enc_keylen == 24) ?
			 SEP_AES_KEY_SIZE_MAX : ctx->enc_keylen), AXI_ID, NS_BIT);
		HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	} else {
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
			ctx->enc_keylen, AXI_ID, NS_BIT);
		HW_DESC_SET_KEY_SIZE_DES(&desc[idx], ctx->enc_keylen);
	}
	HW_DESC_SET_CIPHER_MODE(&desc[idx], ctx->cipher_mode);
	idx++;

	*seq_size = idx;
}

static inline void dx_aead_process_cipher(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size,
	unsigned int data_flow_mode)
{
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	int direct = req_ctx->gen_ctx.op_type;
	unsigned int idx = *seq_size;

	if (req_ctx->cryptlen == 0)
		return; /*null processing*/

	dx_aead_setup_cipher_desc(req, desc, &idx);
	dx_aead_process_cipher_data_desc(req, data_flow_mode, desc, &idx);
	if (direct == SEP_CRYPTO_DIRECTION_ENCRYPT) {
		/* We must wait for DMA to write all cipher */
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
		HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
		idx++;
	}

	*seq_size = idx;
}

static inline void dx_aead_hmac_setup_digest_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	unsigned int hash_mode = (ctx->auth_mode == SEP_HASH_SHA1) ?
				SEP_HASH_HW_SHA1 : SEP_HASH_HW_SHA256;
	unsigned int digest_size = (ctx->auth_mode == SEP_HASH_SHA1) ? 
				SEP_SHA1_DIGEST_SIZE : SEP_SHA256_DIGEST_SIZE;
	unsigned int idx = *seq_size;

	/* Loading hash ipad xor key state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
		ctx->auth_state.hmac.ipad_opad_dma_addr,
		digest_size, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load init. digest len (64 bytes) */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
	HW_DESC_SET_DIN_SRAM(&desc[idx],
		dx_ahash_get_initial_digest_len_sram_addr(ctx->drvdata, hash_mode),
		HASH_LEN_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	*seq_size = idx;
}

static inline void dx_aead_xcbc_setup_digest_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	unsigned int idx = *seq_size;

	/* Loading MAC state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_CONST(&desc[idx], 0, SEP_AES_BLOCK_SIZE);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K1 */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			     ctx->auth_state.xcbc.xcbc_keys_dma_addr,
			     AES_KEYSIZE_128, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K2 */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			     (ctx->auth_state.xcbc.xcbc_keys_dma_addr + 
			      AES_KEYSIZE_128),
			     AES_KEYSIZE_128, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	idx++;

	/* Setup XCBC MAC K3 */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			     (ctx->auth_state.xcbc.xcbc_keys_dma_addr +
			      2 * AES_KEYSIZE_128),
			     AES_KEYSIZE_128, AXI_ID, NS_BIT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE2);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_XCBC_MAC);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	idx++;

	*seq_size = idx;
}

static inline void dx_aead_process_digest_header_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int hw_iv_size = req_ctx->hw_iv_size;
	unsigned int idx = *seq_size;

	/* Hash associated data */
	if (req->assoclen > 0)
		dx_aead_create_assoc_desc(req, DIN_HASH, desc, &idx);

	/* Hash IV */
	HW_DESC_INIT(&desc[idx]);
	if (ctx->cipher_mode == SEP_CIPHER_CTR) {
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			(req_ctx->gen_ctx.iv_dma_addr + CTR_RFC3686_NONCE_SIZE),
			CTR_RFC3686_IV_SIZE, AXI_ID, NS_BIT);
	} else {
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			req_ctx->gen_ctx.iv_dma_addr,
			hw_iv_size, AXI_ID, NS_BIT);
	}
	if ((ctx->auth_mode == SEP_HASH_XCBC_MAC) && (req_ctx->cryptlen > 0)) {
		HW_DESC_SET_DIN_NOT_LAST_INDICATION(&desc[idx]);
	}
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
	idx++;

	*seq_size = idx;
}

static inline void dx_aead_process_digest_scheme_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct dx_aead_handle *aead_handle = ctx->drvdata->aead_handle;
	unsigned int hash_mode = (ctx->auth_mode == SEP_HASH_SHA1) ?
				SEP_HASH_HW_SHA1 : SEP_HASH_HW_SHA256;
	unsigned int digest_size = (ctx->auth_mode == SEP_HASH_SHA1) ? 
				SEP_SHA1_DIGEST_SIZE : SEP_SHA256_DIGEST_SIZE;
	unsigned int idx = *seq_size;

	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
	HW_DESC_SET_DOUT_SRAM(&desc[idx], aead_handle->sram_workspace_addr,
			HASH_LEN_SIZE);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE1);
	HW_DESC_SET_CIPHER_DO(&desc[idx], DO_PAD);
	idx++;

	/* Get final ICV result */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DOUT_SRAM(&desc[idx], aead_handle->sram_workspace_addr,
			digest_size);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
	idx++;

	/* Loading hash opad xor key state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
		(ctx->auth_state.hmac.ipad_opad_dma_addr + digest_size),
		digest_size, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load init. digest len (64 bytes) */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], hash_mode);
	HW_DESC_SET_DIN_SRAM(&desc[idx],
		dx_ahash_get_initial_digest_len_sram_addr(ctx->drvdata, hash_mode),
		HASH_LEN_SIZE);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Perform HASH update */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_SRAM(&desc[idx], aead_handle->sram_workspace_addr,
			digest_size);
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
	idx++;

	*seq_size = idx;
}

static inline void dx_aead_load_mlli_to_sram(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);

	if (unlikely(
		(req_ctx->assoc_buff_type == DX_DMA_BUF_MLLI) ||
		(req_ctx->data_buff_type == DX_DMA_BUF_MLLI) ||
		(req_ctx->is_single_pass == false))) {
		DX_LOG_DEBUG("Copy-to-sram: mlli_dma=%08x, mlli_size=%u\n",
			(unsigned int)ctx->drvdata->mlli_sram_addr,
			req_ctx->mlli_params.mlli_len);
		/* Copy MLLI table host-to-sram */
		HW_DESC_INIT(&desc[*seq_size]);
		HW_DESC_SET_DIN_TYPE(&desc[*seq_size], DMA_DLLI,
			req_ctx->mlli_params.mlli_dma_addr,
			req_ctx->mlli_params.mlli_len, AXI_ID, NS_BIT);
		HW_DESC_SET_DOUT_SRAM(&desc[*seq_size],
			ctx->drvdata->mlli_sram_addr,
			req_ctx->mlli_params.mlli_len);
		HW_DESC_SET_FLOW_MODE(&desc[*seq_size], BYPASS);
		(*seq_size)++;
	}
}

static inline enum FlowMode dx_aead_get_data_flow_mode(
	enum sep_crypto_direction direct,
	enum FlowMode setup_flow_mode,
	bool is_single_pass)
{
	enum FlowMode data_flow_mode;

	if (direct == SEP_CRYPTO_DIRECTION_ENCRYPT) {
		if (setup_flow_mode == S_DIN_to_AES)
			data_flow_mode = likely(is_single_pass) ?
				AES_to_HASH_and_DOUT : DIN_AES_DOUT;
		else
			data_flow_mode = likely(is_single_pass) ?
				DES_to_HASH_and_DOUT : DIN_DES_DOUT;
	} else { /* Decrypt */
		if (setup_flow_mode == S_DIN_to_AES)
			data_flow_mode = likely(is_single_pass) ?
					AES_and_HASH : DIN_AES_DOUT;
		else
			data_flow_mode = likely(is_single_pass) ?
					DES_and_HASH : DIN_DES_DOUT;
	}

	return data_flow_mode;
}

static inline void dx_aead_hmac_authenc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	int direct = req_ctx->gen_ctx.op_type;
	unsigned int data_flow_mode = dx_aead_get_data_flow_mode(
		direct, ctx->flow_mode, req_ctx->is_single_pass);

	if (req_ctx->is_single_pass == true) {
		/**
		 * Single-pass flow
		 */
		dx_aead_hmac_setup_digest_desc(req, desc, seq_size);
		dx_aead_process_digest_header_desc(req, desc, seq_size);
		dx_aead_setup_cipher_desc(req, desc, seq_size);
		dx_aead_process_cipher_data_desc(req, data_flow_mode, desc, seq_size);
		dx_aead_process_digest_scheme_desc(req, desc, seq_size);
		dx_aead_process_digest_result_desc(req, desc, seq_size);
		return;
	}

	/** 
	 * Double-pass flow
	 * Fallback for unsupported single-pass modes, 
	 * i.e. using assoc. data of non-word-multiple */
	if (direct == SEP_CRYPTO_DIRECTION_ENCRYPT) {
		/* encrypt first.. */
		dx_aead_process_cipher(req, desc, seq_size, data_flow_mode);
		/* authenc after..*/
		dx_aead_hmac_setup_digest_desc(req, desc, seq_size);
		dx_aead_process_authenc_data_desc(req, DIN_HASH, desc, seq_size, direct);
		dx_aead_process_digest_scheme_desc(req, desc, seq_size);
		dx_aead_process_digest_result_desc(req, desc, seq_size);

	} else { /*DECRYPT*/
		/* authenc first..*/
		dx_aead_hmac_setup_digest_desc(req, desc, seq_size);
		dx_aead_process_authenc_data_desc(req, DIN_HASH, desc, seq_size, direct);
		dx_aead_process_digest_scheme_desc(req, desc, seq_size);
		/* decrypt after.. */
		dx_aead_process_cipher(req, desc, seq_size, data_flow_mode);
		/* read the digest result with setting the completion bit
		   must be after the cipher operation */
		dx_aead_process_digest_result_desc(req, desc, seq_size);
	}
}

static inline void
dx_aead_xcbc_authenc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	int direct = req_ctx->gen_ctx.op_type;
	unsigned int data_flow_mode = dx_aead_get_data_flow_mode(
		direct, ctx->flow_mode, req_ctx->is_single_pass);

	if (req_ctx->is_single_pass == true) {
		/**
		 * Single-pass flow
		 */
		dx_aead_xcbc_setup_digest_desc(req, desc, seq_size);
		dx_aead_process_digest_header_desc(req, desc, seq_size);
		dx_aead_setup_cipher_desc(req, desc, seq_size);
		dx_aead_process_cipher_data_desc(req, data_flow_mode, desc, seq_size);
		dx_aead_process_digest_result_desc(req, desc, seq_size);
		return;
	}

	/** 
	 * Double-pass flow
	 * Fallback for unsupported single-pass modes, 
	 * i.e. using assoc. data of non-word-multiple */
	if (direct == SEP_CRYPTO_DIRECTION_ENCRYPT) {
		/* encrypt first.. */
		dx_aead_process_cipher(req, desc, seq_size, data_flow_mode);
		/* authenc after.. */
		dx_aead_xcbc_setup_digest_desc(req, desc, seq_size);
		dx_aead_process_authenc_data_desc(req, DIN_HASH, desc, seq_size, direct);
		dx_aead_process_digest_result_desc(req, desc, seq_size);
	} else { /*DECRYPT*/
		/* authenc first.. */
		dx_aead_xcbc_setup_digest_desc(req, desc, seq_size);
		dx_aead_process_authenc_data_desc(req, DIN_HASH, desc, seq_size, direct);
		/* decrypt after..*/
		dx_aead_process_cipher(req, desc, seq_size, data_flow_mode);
		/* read the digest result with setting the completion bit
		   must be after the cipher operation */
		dx_aead_process_digest_result_desc(req, desc, seq_size);
	}
}

static int validate_data_size(struct dx_aead_ctx *ctx,
	enum sep_crypto_direction direct, struct aead_request *req)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	unsigned int assoclen = req->assoclen;
	unsigned int cipherlen = (direct == SEP_CRYPTO_DIRECTION_DECRYPT) ?
			(req->cryptlen - ctx->authsize) : req->cryptlen;

	if (unlikely((direct == SEP_CRYPTO_DIRECTION_DECRYPT) &&
		(req->cryptlen < ctx->authsize)))
		goto data_size_err;

	areq_ctx->is_single_pass = true; /*defaulted to fast flow*/

	switch (ctx->flow_mode) {
	case S_DIN_to_AES:
		if (unlikely((ctx->cipher_mode == SEP_CIPHER_CBC) &&
			!IS_ALIGNED(cipherlen, AES_BLOCK_SIZE)))
			goto data_size_err;
		if (ctx->cipher_mode == SEP_CIPHER_CCM)
			break;
		if (ctx->cipher_mode == SEP_CIPHER_GCTR)
		{
			if (areq_ctx->plaintext_authenticate_only == true)
				areq_ctx->is_single_pass = false; 
			break;
		}

		if (!IS_ALIGNED(assoclen, sizeof(uint32_t)))
			areq_ctx->is_single_pass = false;

		if ((ctx->cipher_mode == SEP_CIPHER_CTR) &&
		    !IS_ALIGNED(cipherlen, sizeof(uint32_t)))
			areq_ctx->is_single_pass = false;

		break;
	case S_DIN_to_DES:
		if (unlikely(!IS_ALIGNED(cipherlen, DES_BLOCK_SIZE)))
			goto data_size_err;
		if (unlikely(!IS_ALIGNED(assoclen, DES_BLOCK_SIZE)))
			areq_ctx->is_single_pass = false;
		break;
	default:
		DX_LOG_ERR("Unexpected flow mode (%d)\n", ctx->flow_mode);
		goto data_size_err;
	}

	return 0;

data_size_err:
	return -EINVAL;
}

#if DX_CC_HAS_AES_CCM
static unsigned int format_ccm_a0(uint8_t *pA0Buff, uint32_t headerSize)
{
	unsigned int len = 0;
	if ( headerSize == 0 ) {
		return 0;
	} 
	if ( headerSize < ((1UL << 16) - (1UL << 8) )) {
		len = 2;

		pA0Buff[0] = (headerSize >> 8) & 0xFF;
		pA0Buff[1] = headerSize & 0xFF;
	} else {
		len = 6;

		pA0Buff[0] = 0xFF;
		pA0Buff[1] = 0xFE;
		pA0Buff[2] = (headerSize >> 24) & 0xFF;
		pA0Buff[3] = (headerSize >> 16) & 0xFF;
		pA0Buff[4] = (headerSize >> 8) & 0xFF;
		pA0Buff[5] = headerSize & 0xFF;
	}

	return len;
}

static int set_msg_len(u8 *block, unsigned int msglen, int csize)
{
	__be32 data;

	memset(block, 0, csize);
	block += csize;

	if (csize >= 4)
		csize = 4;
	else if (msglen > (1 << (8 * csize)))
		return -EOVERFLOW;

	data = cpu_to_be32(msglen);
	memcpy(block - csize, (u8 *)&data + 4 - csize, csize);

	return 0;
}

static inline int dx_aead_ccm(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;
	unsigned int cipher_flow_mode;
	dma_addr_t mac_result;


	if (req_ctx->gen_ctx.op_type == SEP_CRYPTO_DIRECTION_DECRYPT) {
		cipher_flow_mode = AES_to_HASH_and_DOUT;
		mac_result = req_ctx->mac_buf_dma_addr;
	} else { /* Encrypt */
		cipher_flow_mode = AES_and_HASH;
		mac_result = req_ctx->icv_dma_addr;
	}

	/* load key */
	HW_DESC_INIT(&desc[idx]);	
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CTR);	
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr, 
			((ctx->enc_keylen == 24) ? 
			 SEP_AES_KEY_SIZE_MAX : ctx->enc_keylen), 
			 AXI_ID, NS_BIT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* load ctr state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CTR);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			req_ctx->gen_ctx.iv_dma_addr, 
			     AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);	
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* load MAC key */
	HW_DESC_INIT(&desc[idx]);	
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CBC_MAC);	
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr, 
			((ctx->enc_keylen == 24) ? 
			 SEP_AES_KEY_SIZE_MAX : ctx->enc_keylen), 
			 AXI_ID, NS_BIT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	idx++;

	/* load MAC state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CBC_MAC);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			req_ctx->mac_buf_dma_addr, 
			     AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);	
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	idx++;


	/* prcess assoc data */
	if (req->assoclen > 0) {
		dx_aead_create_assoc_desc(req, DIN_HASH, desc, &idx);
	} else {
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
				      sg_dma_address(&req_ctx->ccm_adata_sg),
				     AES_BLOCK_SIZE + req_ctx->ccm_hdr_size,
				     AXI_ID, NS_BIT);
		HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
		idx++;
	}

	/* process the cipher */
	if (req_ctx->cryptlen != 0) {
		dx_aead_process_cipher_data_desc(req, cipher_flow_mode, desc, &idx);
	}

	/* Read temporal MAC */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CBC_MAC);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], req_ctx->mac_buf_dma_addr,
			      ctx->authsize, AXI_ID, NS_BIT, 0);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	idx++;

	/* load AES-CTR state (for last MAC calculation)*/
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_CTR);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_ENCRYPT);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			     req_ctx->ccm_iv0_dma_addr ,
			     AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
	HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
	idx++;

	/* encrypt the "T" value and store MAC in mac_state */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			req_ctx->mac_buf_dma_addr , ctx->authsize, AXI_ID, NS_BIT);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], mac_result , ctx->authsize, AXI_ID, NS_BIT, 1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
	idx++;	

	*seq_size = idx;
	return 0;
}

int config_ccm_adata(struct aead_request *req) {
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	//unsigned int size_of_a = 0, rem_a_size = 0;
	unsigned int lp = req->iv[0];
	unsigned int l = lp + 1;  /* This is L' of RFC 3610. */
	unsigned int m = ctx->authsize;  /* This is M' of RFC 3610. */
	uint8_t *b0 = req_ctx->ccm_config + CCM_B0_OFFSET;
	uint8_t *a0 = req_ctx->ccm_config + CCM_A0_OFFSET;
	uint8_t *ctr_count_0 = req_ctx->ccm_config + CCM_CTR_COUNT_0_OFFSET;
	unsigned int cryptlen = (req_ctx->gen_ctx.op_type == 
				 SEP_CRYPTO_DIRECTION_ENCRYPT) ? 
				req->cryptlen : 
				(req->cryptlen - ctx->authsize);
	int rc;
	memset(req_ctx->mac_buf, 0, AES_BLOCK_SIZE);
	memset(req_ctx->ccm_config, 0, AES_BLOCK_SIZE*3);

	/* taken from crypto/ccm.c */
	/* 2 <= L <= 8, so 1 <= L' <= 7. */
	if (1 > req->iv[0] || req->iv[0] > 7) {
		DX_LOG_ERR("illegal iv value %X\n",req->iv[0]);
		return -EINVAL;
	}
	memcpy(b0, req->iv, AES_BLOCK_SIZE);

	/* format control info per RFC 3610 and
	 * NIST Special Publication 800-38C
	 */
	*b0 |= (8 * ((m - 2) / 2));
	if (req->assoclen > 0)
		*b0 |= 64;  /* Enable bit 6 if Adata exists. */
	
	rc = set_msg_len(b0 + 16 - l, cryptlen, l);  /* Write L'. */
	if (rc != 0) {
		return rc;
	}
	 /* END of "taken from crypto/ccm.c" */
	
	/* l(a) - size of associated data. */
	req_ctx->ccm_hdr_size = format_ccm_a0 (a0, req->assoclen);

	memset(req->iv + 15 - req->iv[0], 0, req->iv[0] + 1);
	req->iv [15] = 1;

	memcpy(ctr_count_0, req->iv, AES_BLOCK_SIZE) ;
	ctr_count_0[15] = 0;

	return 0;
}

static void dx_rfc4309_ccm_process(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);

	/* L' */
	memset(areq_ctx->ctr_iv, 0, AES_BLOCK_SIZE);
	areq_ctx->ctr_iv[0] = 3;  /* For RFC 4309, always use 4 bytes for message length (at most 2^32-1 bytes). */

	/* In RFC 4309 there is an 11-bytes nonce+IV part, that we build here. */
	memcpy(areq_ctx->ctr_iv + CCM_BLOCK_NONCE_OFFSET, ctx->ctr_nonce, CCM_BLOCK_NONCE_SIZE);
	memcpy(areq_ctx->ctr_iv + CCM_BLOCK_IV_OFFSET,    req->iv,        CCM_BLOCK_IV_SIZE);
	req->iv = areq_ctx->ctr_iv;	
}
#endif /*DX_CC_HAS_AES_CCM*/

#if DX_CC_HAS_AES_GCM

static inline void dx_aead_gcm_setup_ghash_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;

	/* load key to AES*/
	HW_DESC_INIT(&desc[idx]);	
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_ECB);	
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_ENCRYPT);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr, 
			ctx->enc_keylen, AXI_ID, NS_BIT); 
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* process one zero block to generate hkey */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_CONST(&desc[idx], 0x0, AES_BLOCK_SIZE);
	HW_DESC_SET_DOUT_DLLI(&desc[idx],
				  req_ctx->hkey_dma_addr,
				  AES_BLOCK_SIZE,
				  AXI_ID, NS_BIT, 0); 
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
	idx++;

	/* Memory Barrier */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
	HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
	idx++;

	/* Load GHASH subkey */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
			req_ctx->hkey_dma_addr, 
				 AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_HASH_HW_GHASH);	
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED);	
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Configure Hash Engine to work with GHASH.
	   Since it was not possible to extend HASH submodes to add GHASH,
	   The following command is necessary in order to select GHASH (according to HW designers)*/
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
	HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_HASH_HW_GHASH);	
	HW_DESC_SET_CIPHER_DO(&desc[idx], 1); //1=AES_SK RKEK
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_ENCRYPT);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED); 
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Load GHASH initial STATE (which is 0). (for any hash there is an initial state) */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_CONST(&desc[idx], 0x0, AES_BLOCK_SIZE);
	HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_HASH);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_HASH_HW_GHASH);
	HW_DESC_SET_CIPHER_CONFIG1(&desc[idx], HASH_PADDING_ENABLED); 
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	*seq_size = idx;
}

static inline void dx_aead_gcm_setup_gctr_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;

	/* load key to AES*/
	HW_DESC_INIT(&desc[idx]);	
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_GCTR);	
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_ENCRYPT);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr, 
			ctx->enc_keylen, AXI_ID, NS_BIT); 
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	if ((req_ctx->cryptlen != 0) && (req_ctx->plaintext_authenticate_only==false)){
		/* load AES/CTR initial CTR value inc by 2*/
		HW_DESC_INIT(&desc[idx]);
		HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_GCTR);
		HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
		HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
				req_ctx->gcm_iv_inc2_dma_addr, 
					 AES_BLOCK_SIZE, AXI_ID, NS_BIT);
		HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_ENCRYPT);	
		HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
		HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
		idx++;
	}

	*seq_size = idx;
}

static inline void dx_aead_process_gcm_result_desc(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	dma_addr_t mac_result; 
	unsigned int idx = *seq_size;

	if (req_ctx->gen_ctx.op_type == SEP_CRYPTO_DIRECTION_DECRYPT) {
		mac_result = req_ctx->mac_buf_dma_addr;
	} else { /* Encrypt */
		mac_result = req_ctx->icv_dma_addr;
	}

	/* prcess(ghash) gcm_block_len */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI, 
		req_ctx->gcm_block_len_dma_addr,
		AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_HASH);
	idx++;

	/* Store GHASH state after GHASH(Associated Data + Cipher +LenBlock) */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_HASH_HW_GHASH);
	HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], req_ctx->mac_buf_dma_addr,
				  AES_BLOCK_SIZE, AXI_ID, NS_BIT, 0);
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_WRITE_STATE0);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_HASH_to_DOUT);
	HW_DESC_SET_AES_NOT_HASH_MODE(&desc[idx]);

	idx++; 

	/* load AES/CTR initial CTR value inc by 1*/
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_GCTR);
	HW_DESC_SET_KEY_SIZE_AES(&desc[idx], ctx->enc_keylen);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
				 req_ctx->gcm_iv_inc1_dma_addr, 
				 AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_CIPHER_CONFIG0(&desc[idx], SEP_CRYPTO_DIRECTION_ENCRYPT);	
	HW_DESC_SET_SETUP_MODE(&desc[idx], SETUP_LOAD_STATE1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], S_DIN_to_AES);
	idx++;

	/* Memory Barrier */
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_DIN_NO_DMA(&desc[idx], 0, 0xfffff0);
	HW_DESC_SET_DOUT_NO_DMA(&desc[idx], 0, 0, 1);
	idx++;

	/* process GCTR on stored GHASH and store MAC in mac_state*/
	HW_DESC_INIT(&desc[idx]);
	HW_DESC_SET_CIPHER_MODE(&desc[idx], SEP_CIPHER_GCTR);
	HW_DESC_SET_DIN_TYPE(&desc[idx], DMA_DLLI,
		req_ctx->mac_buf_dma_addr,
		AES_BLOCK_SIZE, AXI_ID, NS_BIT);
	HW_DESC_SET_DOUT_DLLI(&desc[idx], mac_result , ctx->authsize, AXI_ID, NS_BIT, 1);
	HW_DESC_SET_FLOW_MODE(&desc[idx], DIN_AES_DOUT);
	idx++;	

	*seq_size = idx;
}

static inline int dx_aead_gcm(
	struct aead_request *req,
	HwDesc_s desc[],
	unsigned int *seq_size)
{
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;
	unsigned int cipher_flow_mode;

	if (req_ctx->gen_ctx.op_type == SEP_CRYPTO_DIRECTION_DECRYPT) {
		cipher_flow_mode = AES_and_HASH;
	} else { /* Encrypt */
		cipher_flow_mode = AES_to_HASH_and_DOUT;
	}


	//in RFC4543 no data to encrypt. just copy data from src to dest.
	if (req_ctx->plaintext_authenticate_only==true){     
		dx_aead_process_cipher_data_desc(req, BYPASS, desc, seq_size);
		dx_aead_gcm_setup_ghash_desc(req, desc, seq_size);
		/* prcess(ghash) assoc data */
		dx_aead_create_assoc_desc(req, DIN_HASH, desc, seq_size);
		dx_aead_gcm_setup_gctr_desc(req, desc, seq_size);
		dx_aead_process_gcm_result_desc(req, desc, seq_size);
		idx = *seq_size;
		return 0;
	}

	// for gcm and rfc4106.
	dx_aead_gcm_setup_ghash_desc(req, desc, seq_size);
	/* prcess(ghash) assoc data */
	if (req->assoclen > 0)
		dx_aead_create_assoc_desc(req, DIN_HASH, desc, seq_size);
	dx_aead_gcm_setup_gctr_desc(req, desc, seq_size);
	/* process(gctr+ghash) */
	if (req_ctx->cryptlen != 0)
		dx_aead_process_cipher_data_desc(req, cipher_flow_mode, desc, seq_size); 
	dx_aead_process_gcm_result_desc(req, desc, seq_size);

	idx = *seq_size;
	return 0;
}

#ifdef DX_DEBUG
static inline void dx_aead_dump_gcm(
	const char* title,
	struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);

	if (ctx->cipher_mode != SEP_CIPHER_GCTR)
		return;

	if (title != NULL) {
		DX_LOG_DEBUG("----------------------------------------------------------------------------------");
		DX_LOG_DEBUG("%s\n", title);
	}

	DX_LOG_DEBUG("cipher_mode %d, authsize %d, enc_keylen %d, assoclen %d, cryptlen %d \n", \
				 ctx->cipher_mode, ctx->authsize, ctx->enc_keylen, req->assoclen, req_ctx->cryptlen );

	if ( ctx->enckey != NULL ) {
		dump_byte_array("mac key",ctx->enckey, 16);
	}

	dump_byte_array("req->iv",req->iv, AES_BLOCK_SIZE);

	dump_byte_array("gcm_iv_inc1",req_ctx->gcm_iv_inc1, AES_BLOCK_SIZE);

	dump_byte_array("gcm_iv_inc2",req_ctx->gcm_iv_inc2, AES_BLOCK_SIZE);

	dump_byte_array("hkey",req_ctx->hkey, AES_BLOCK_SIZE);

	dump_byte_array("mac_buf",req_ctx->mac_buf, AES_BLOCK_SIZE);

	dump_byte_array("gcm_len_block",req_ctx->gcm_len_block.lenA, AES_BLOCK_SIZE);

	if (req->assoc!=NULL && req->assoclen) {
		dump_byte_array("req->assoc",sg_virt(req->assoc), req->assoclen);
	}

	if (req->src!=NULL && req->cryptlen) {
		dump_byte_array("req->src",sg_virt(req->src), req->cryptlen);
	}

	if (req->dst!=NULL) {
		dump_byte_array("req->dst",sg_virt(req->dst), req->cryptlen+ctx->authsize);
    }
}
#endif

int config_gcm_context(struct aead_request *req) {
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	
	unsigned int cryptlen = (req_ctx->gen_ctx.op_type == 
				 SEP_CRYPTO_DIRECTION_ENCRYPT) ? 
				req->cryptlen : 
				(req->cryptlen - ctx->authsize);
	__be32 counter = cpu_to_be32(2);

	DX_LOG_DEBUG("config_gcm_context() cryptlen = %d, req->assoclen = %d ctx->authsize = %d \n", cryptlen, req->assoclen, ctx->authsize);

	memset(req_ctx->hkey, 0, AES_BLOCK_SIZE);

	memset(req_ctx->mac_buf, 0, AES_BLOCK_SIZE);

    memcpy(req->iv + 12, &counter, 4);
	memcpy(req_ctx->gcm_iv_inc2, req->iv, 16);

	counter = cpu_to_be32(1);
	memcpy(req->iv + 12, &counter, 4);
	memcpy(req_ctx->gcm_iv_inc1, req->iv, 16);


	if (req_ctx->plaintext_authenticate_only == false)
	{
		__be64 temp64;
		temp64 = cpu_to_be64(req->assoclen * 8);
		memcpy ( &req_ctx->gcm_len_block.lenA , &temp64, sizeof(temp64) );
		temp64 = cpu_to_be64(cryptlen * 8);
		memcpy ( &req_ctx->gcm_len_block.lenC , &temp64, 8 );
	}
	else { //rfc4543=>  all data(AAD,IV,Plain) are considered additional data that is nothing is encrypted.
		__be64 temp64;
		temp64 = cpu_to_be64((req->assoclen+GCM_BLOCK_RFC4_IV_SIZE+cryptlen) * 8);
		memcpy ( &req_ctx->gcm_len_block.lenA , &temp64, sizeof(temp64) );
		temp64 = 0;
		memcpy ( &req_ctx->gcm_len_block.lenC , &temp64, 8 );
	}

	return 0;
}

static void dx_rfc4_gcm_process(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);

	memcpy(areq_ctx->ctr_iv + GCM_BLOCK_RFC4_NONCE_OFFSET, ctx->ctr_nonce, GCM_BLOCK_RFC4_NONCE_SIZE);
	memcpy(areq_ctx->ctr_iv + GCM_BLOCK_RFC4_IV_OFFSET,    req->iv, GCM_BLOCK_RFC4_IV_SIZE);
	req->iv = areq_ctx->ctr_iv;	
}


#endif /*DX_CC_HAS_AES_GCM*/

static int dx_aead_process(struct aead_request *req, enum sep_crypto_direction direct)
{
	int rc = 0;
	int seq_len = 0;
	HwDesc_s desc[MAX_AEAD_PROCESS_SEQ]; 
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	struct device *dev = &ctx->drvdata->plat_dev->dev;
	struct dx_crypto_req dx_req = {0};

	DECL_CYCLE_COUNT_RESOURCES;

	DX_LOG_DEBUG("%s context=%p req=%p iv=%p src=%p src_ofs=%d dst=%p dst_ofs=%d cryptolen=%d\n",
		((direct==SEP_CRYPTO_DIRECTION_ENCRYPT)?"Encrypt":"Decrypt"), ctx, req, req->iv,
		sg_virt(req->src), req->src->offset, sg_virt(req->dst), req->dst->offset, req->cryptlen);

	/* STAT_PHASE_0: Init and sanity checks */
	START_CYCLE_COUNT();
	
	/* Check data length according to mode */
	if (unlikely(validate_data_size(ctx, direct, req) != 0)) {
		DX_LOG_ERR("Unsupported crypt/assoc len %d/%d.\n",
				req->cryptlen, req->assoclen);
		crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_BLOCK_LEN);
		return -EINVAL;
	}

	/* Setup DX request structure */
	dx_req.user_cb = (void *)dx_aead_complete;
	dx_req.user_arg = (void *)req;

#ifdef ENABLE_CYCLE_COUNT
	dx_req.op_type = (direct == SEP_CRYPTO_DIRECTION_DECRYPT) ?
		STAT_OP_TYPE_DECODE : STAT_OP_TYPE_ENCODE;
#endif
	/* Setup request context */
	areq_ctx->gen_ctx.op_type = direct;
	areq_ctx->req_authsize = ctx->authsize;
	areq_ctx->cipher_mode = ctx->cipher_mode;

	END_CYCLE_COUNT(dx_req.op_type, STAT_PHASE_0);

	/* STAT_PHASE_1: Map buffers */
	START_CYCLE_COUNT();
	
	if (ctx->cipher_mode == SEP_CIPHER_CTR) {
		/* Build CTR IV - Copy nonce from last 4 bytes in
		*  CTR key to first 4 bytes in CTR IV */
		memcpy(areq_ctx->ctr_iv, ctx->ctr_nonce, CTR_RFC3686_NONCE_SIZE);
		if (areq_ctx->backup_giv == NULL) /*User none-generated IV*/
			memcpy(areq_ctx->ctr_iv + CTR_RFC3686_NONCE_SIZE,
				req->iv, CTR_RFC3686_IV_SIZE);
		/* Initialize counter portion of counter block */
		*(__be32 *)(areq_ctx->ctr_iv + CTR_RFC3686_NONCE_SIZE +
			    CTR_RFC3686_IV_SIZE) = cpu_to_be32(1);

		/* Replace with counter iv */
		req->iv = areq_ctx->ctr_iv;
		areq_ctx->hw_iv_size = CTR_RFC3686_BLOCK_SIZE;
	} else if ((ctx->cipher_mode == SEP_CIPHER_CCM) || 
		   (ctx->cipher_mode == SEP_CIPHER_GCTR) ) {
		areq_ctx->hw_iv_size = AES_BLOCK_SIZE;
		if (areq_ctx->ctr_iv != req->iv) {
			memcpy(areq_ctx->ctr_iv, req->iv, AES_BLOCK_SIZE);
			req->iv = areq_ctx->ctr_iv;
		}
	}  else {
		areq_ctx->hw_iv_size = crypto_aead_ivsize(tfm);
	}

#if DX_CC_HAS_AES_CCM
	if (ctx->cipher_mode == SEP_CIPHER_CCM) {
		rc = config_ccm_adata(req);
		if (unlikely(rc != 0)) {
			DX_LOG_ERR("config_ccm_adata() returned with a failure %d!", rc);
			goto exit; 
		}
	} else {
		areq_ctx->ccm_hdr_size = ccm_header_size_null;		
	}
#else
	areq_ctx->ccm_hdr_size = ccm_header_size_null;		
#endif /*DX_CC_HAS_AES_CCM*/

#if DX_CC_HAS_AES_GCM 
	if (ctx->cipher_mode == SEP_CIPHER_GCTR) {
		rc = config_gcm_context(req);
		if (unlikely(rc != 0)) {
			DX_LOG_ERR("config_gcm_context() returned with a failure %d!", rc);
			goto exit; 
		}
	} 
#endif /*DX_CC_HAS_AES_GCM*/

	rc = dx_buffer_mgr_map_aead_request(ctx->drvdata, req);
	if (unlikely(rc != 0)) {
		DX_LOG_ERR("map_request() failed\n");
		goto exit;
	}

	/* do we need to generate IV? */
	if (areq_ctx->backup_giv != NULL) {

		/* set the DMA mapped IV address*/
		if (ctx->cipher_mode == SEP_CIPHER_CTR) {
			dx_req.ivgen_dma_addr[0] = areq_ctx->gen_ctx.iv_dma_addr + CTR_RFC3686_NONCE_SIZE;
			dx_req.ivgen_dma_addr_len = 1;
		} else if (ctx->cipher_mode == SEP_CIPHER_CCM) {
			/* In ccm, the IV needs to exist both inside B0 and inside the counter.
			   It is also copied to iv_dma_addr for other reasons (like returning
			   it to the user).
			   So, using 3 (identical) IV outputs. */
			dx_req.ivgen_dma_addr[0] = areq_ctx->gen_ctx.iv_dma_addr + CCM_BLOCK_IV_OFFSET;
			dx_req.ivgen_dma_addr[1] = sg_dma_address(&areq_ctx->ccm_adata_sg) + CCM_B0_OFFSET          + CCM_BLOCK_IV_OFFSET;
			dx_req.ivgen_dma_addr[2] = sg_dma_address(&areq_ctx->ccm_adata_sg) + CCM_CTR_COUNT_0_OFFSET + CCM_BLOCK_IV_OFFSET;
			dx_req.ivgen_dma_addr_len = 3;
		} else {
			dx_req.ivgen_dma_addr[0] = areq_ctx->gen_ctx.iv_dma_addr;
			dx_req.ivgen_dma_addr_len = 1;
		}

		/* set the IV size (8/16 B long)*/
		dx_req.ivgen_size = crypto_aead_ivsize(tfm);
	}

	END_CYCLE_COUNT(dx_req.op_type, STAT_PHASE_1);

	/* STAT_PHASE_2: Create sequence */
	START_CYCLE_COUNT();

	/* Load MLLI tables to SRAM if necessary */
	dx_aead_load_mlli_to_sram(req, desc, &seq_len);

	/*TODO: move seq len by reference */
	switch (ctx->auth_mode) {
	case SEP_HASH_SHA1:
	case SEP_HASH_SHA256:
		dx_aead_hmac_authenc(req, desc, &seq_len);
		break;
	case SEP_HASH_XCBC_MAC:
		dx_aead_xcbc_authenc(req, desc, &seq_len);
		break;
#if ( DX_CC_HAS_AES_CCM || DX_CC_HAS_AES_GCM )
	case SEP_HASH_NULL:
#if DX_CC_HAS_AES_CCM
		if (ctx->cipher_mode == SEP_CIPHER_CCM) {
			dx_aead_ccm(req, desc, &seq_len);
		}
#endif /*DX_CC_HAS_AES_CCM*/
#if DX_CC_HAS_AES_GCM
		if (ctx->cipher_mode == SEP_CIPHER_GCTR) {
			dx_aead_gcm(req, desc, &seq_len);
		}
#endif /*DX_CC_HAS_AES_GCM*/
			break;
#endif
	default:	
		DX_LOG_ERR("Unsupported authenc (%d)\n", ctx->auth_mode);
		dx_buffer_mgr_unmap_aead_request(dev, req);
		rc = -ENOTSUPP;
		goto exit;
	}

	END_CYCLE_COUNT(dx_req.op_type, STAT_PHASE_2);

	/* STAT_PHASE_3: Lock HW and push sequence */
	START_CYCLE_COUNT();

	rc = send_request(ctx->drvdata, &dx_req, desc, seq_len, 1);

	if (unlikely(rc != -EINPROGRESS)) {
		DX_LOG_ERR("send_request() failed (rc=%d)\n", rc);
		dx_buffer_mgr_unmap_aead_request(dev, req);
	}

	
	END_CYCLE_COUNT(dx_req.op_type, STAT_PHASE_3);
exit:
	return rc;
}

static int dx_aead_encrypt(struct aead_request *req)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;

	areq_ctx->plaintext_authenticate_only = false;

	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;
}

#if DX_CC_HAS_AES_CCM
static int dx_rfc4309_ccm_encrypt(struct aead_request *req)
{
	/* Very similar to dx_aead_encrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;
	
	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;
	
	dx_rfc4309_ccm_process(req);
	
	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;
}
#endif /* DX_CC_HAS_AES_CCM */

static int dx_aead_decrypt(struct aead_request *req)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;
	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;

	areq_ctx->plaintext_authenticate_only = false;

	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_DECRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;

}

#if DX_CC_HAS_AES_CCM
static int dx_rfc4309_ccm_decrypt(struct aead_request *req)
{
	/* Very similar to dx_aead_decrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;
	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;
	
	dx_rfc4309_ccm_process(req);
	
	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_DECRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;
}
#endif /* DX_CC_HAS_AES_CCM */

#if DX_CC_HAS_AES_GCM

static int dx_rfc4106_gcm_setkey(struct crypto_aead *tfm, const u8 *key, unsigned int keylen)
{
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	int rc = 0;
	
	DX_LOG_DEBUG("dx_rfc4106_gcm_setkey()  keylen %d, key %p \n", keylen, key );

	dump_byte_array("req->key ",key, keylen);

	if (keylen < 4)
		return -EINVAL;

	keylen -= 4;
	memcpy(ctx->ctr_nonce, key + keylen, 4);

	rc = dx_aead_setkey(tfm, key, keylen);

	return rc;
}

static int dx_rfc4543_gcm_setkey(struct crypto_aead *tfm, const u8 *key, unsigned int keylen)
{
	struct dx_aead_ctx *ctx = crypto_aead_ctx(tfm);
	int rc = 0;
	
	DX_LOG_DEBUG("dx_rfc4543_gcm_setkey()  keylen %d, key %p \n", keylen, key );

	dump_byte_array("req->key ",key, keylen);

	if (keylen < 4)
		return -EINVAL;

	keylen -= 4;
	memcpy(ctx->ctr_nonce, key + keylen, 4);

	rc = dx_aead_setkey(tfm, key, keylen);

	return rc;
}

static int dx_gcm_setauthsize(struct crypto_aead *authenc,
				      unsigned int authsize)
{
	switch (authsize) {
	case 4:
	case 8:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		break;
	default:
		return -EINVAL;
	}

	return dx_aead_setauthsize(authenc, authsize);
}

static int dx_rfc4106_gcm_setauthsize(struct crypto_aead *authenc,
				      unsigned int authsize)
{
		DX_LOG_DEBUG("dx_rfc4106_gcm_setauthsize()  authsize %d \n", authsize );

		switch (authsize) {
		case 8:
		case 12:
		case 16:
			break;
		default:
			return -EINVAL;
		}

		return dx_aead_setauthsize(authenc, authsize);
}

static int dx_rfc4543_gcm_setauthsize(struct crypto_aead *authenc,
				      unsigned int authsize)
{
	DX_LOG_DEBUG("dx_rfc4543_gcm_setauthsize()  authsize %d \n", authsize );

	if (authsize != 16)
		return -EINVAL;

	return dx_aead_setauthsize(authenc, authsize);
}

static int dx_rfc4106_gcm_encrypt(struct aead_request *req)
{
	/* Very similar to dx_aead_encrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;
	

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;
	
	areq_ctx->plaintext_authenticate_only = false;

	dx_rfc4_gcm_process(req);

	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;
}

static int dx_rfc4543_gcm_encrypt(struct aead_request *req)
{
	/* Very similar to dx_aead_encrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;
	
	//plaintext is not encryped with rfc4543
	areq_ctx->plaintext_authenticate_only = true;

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;
	
	dx_rfc4_gcm_process(req);

	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;
}

static int dx_rfc4106_gcm_decrypt(struct aead_request *req)
{
	/* Very similar to dx_aead_decrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;


	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;
	
	areq_ctx->plaintext_authenticate_only = false;

	dx_rfc4_gcm_process(req);

	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_DECRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;
}

static int dx_rfc4543_gcm_decrypt(struct aead_request *req)
{
	/* Very similar to dx_aead_decrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;

	//plaintext is not decryped with rfc4543
	areq_ctx->plaintext_authenticate_only = true;

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;
	
	dx_rfc4_gcm_process(req);

	rc = dx_aead_process(req, SEP_CRYPTO_DIRECTION_DECRYPT);
	if (rc != -EINPROGRESS)
		req->iv = areq_ctx->backup_iv;

	return rc;
}
#endif /* DX_CC_HAS_AES_GCM */

static int dx_aead_givencrypt(struct aead_givcrypt_request *req)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(&req->areq);
	int rc;

	areq_ctx->plaintext_authenticate_only = false;

	/* Backup orig. IV */
	areq_ctx->backup_iv = req->areq.iv;
	/* Backup orig. "giv". This indicates that we need to generate IV */
	areq_ctx->backup_giv = req->giv;
	/* request IV points to payload's header */
	req->areq.iv = req->giv;

	rc = dx_aead_process(&req->areq, SEP_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS)
		req->areq.iv = areq_ctx->backup_iv;
	return rc;
}

#if DX_CC_HAS_AES_CCM
static int dx_rfc4309_ccm_givencrypt(struct aead_givcrypt_request *req)
{
	/* Very similar to dx_aead_givencrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(&req->areq);
	int rc;

	/* Backup orig. IV */
	areq_ctx->backup_iv = req->areq.iv;
	/* Backup orig. "giv". This indicates that we need to generate IV */
	areq_ctx->backup_giv = req->giv;
	/* request IV points to payload's header */
	req->areq.iv = req->giv;
	
	dx_rfc4309_ccm_process(&req->areq);
	
	rc = dx_aead_process(&req->areq, SEP_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS)
		req->areq.iv = areq_ctx->backup_iv;

	return rc;
}
#endif /* DX_CC_HAS_AES_CCM */

/* DX Block aead alg */
static struct dx_alg_template aead_algs[] = {
	{
		.name = "authenc(hmac(sha1),cbc(aes))",
		.driver_name = "authenc-hmac-sha1-cbc-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			/* defaulted to "<built-in>" */
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_SHA1,
	},
	{
		.name = "authenc(hmac(sha1),cbc(des3_ede))",
		.driver_name = "authenc-hmac-sha1-cbc-des3-dx",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			/* defaulted to "<built-in>" */
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.auth_mode = SEP_HASH_SHA1,
	},
	{
		.name = "authenc(hmac(sha256),cbc(aes))",
		.driver_name = "authenc-hmac-sha256-cbc-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			/* defaulted to "<built-in>" */
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_SHA256,
	},
	{
		.name = "authenc(hmac(sha256),cbc(des3_ede))",
		.driver_name = "authenc-hmac-sha256-cbc-des3-dx",
		.blocksize = DES3_EDE_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			/* defaulted to "<built-in>" */
			.ivsize = DES3_EDE_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_DES,
		.auth_mode = SEP_HASH_SHA256,
	},
	{
		.name = "authenc(xcbc(aes),cbc(aes))",
		.driver_name = "authenc-xcbc-aes-cbc-aes-dx",
		.blocksize = AES_BLOCK_SIZE,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			/* defaulted to "<built-in>" */
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CBC,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_XCBC_MAC,
	},
	{
		.name = "authenc(hmac(sha1),rfc3686(ctr(aes)))",
		.driver_name = "authenc-hmac-sha1-rfc3686-ctr-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_SHA1,
	},
	{
		.name = "authenc(hmac(sha256),rfc3686(ctr(aes)))",
		.driver_name = "authenc-hmac-sha256-rfc3686-ctr-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_SHA256,
	},
	{
		.name = "authenc(xcbc(aes),rfc3686(ctr(aes)))",
		.driver_name = "authenc-xcbc-aes-rfc3686-ctr-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_aead_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			.givencrypt = dx_aead_givencrypt,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_XCBC_MAC,
	},
#if DX_CC_HAS_AES_CCM
	{
		.name = "ccm(aes)",
		.driver_name = "ccm-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_ccm_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			/* Generated IV (.givencrypt) is not supported for ccm(aes) by Linux kernel, probably due 
			   to complicated IV format. Hence, not supported here as well. */
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CCM,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_NULL,
	},
	{
		.name = "rfc4309(ccm(aes))",
		.driver_name = "rfc4309-ccm-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_rfc4309_ccm_setkey,
			.setauthsize = dx_rfc4309_ccm_setauthsize,
			.encrypt = dx_rfc4309_ccm_encrypt,
			.decrypt = dx_rfc4309_ccm_decrypt,
			.givencrypt = dx_rfc4309_ccm_givencrypt,
			.ivsize = CCM_BLOCK_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		},
		.cipher_mode = SEP_CIPHER_CCM,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_NULL,
	},
#endif /*DX_CC_HAS_AES_CCM*/
#if DX_CC_HAS_AES_GCM
	{
		.name = "gcm(aes)",
		.driver_name = "gcm-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_aead_setkey,
			.setauthsize = dx_gcm_setauthsize,
			.encrypt = dx_aead_encrypt,
			.decrypt = dx_aead_decrypt,
			/* Generated IV (.givencrypt) is not supported for gcm(aes) by Linux kernel, probably due 
			   to complicated IV format. Hence, not supported here as well. */
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		},
		.cipher_mode = SEP_CIPHER_GCTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_NULL,
	},
	{
		.name = "rfc4106(gcm(aes))",
		.driver_name = "rfc4106-gcm-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_rfc4106_gcm_setkey,
			.setauthsize = dx_rfc4106_gcm_setauthsize,
			.encrypt = dx_rfc4106_gcm_encrypt,
			.decrypt = dx_rfc4106_gcm_decrypt,
			.givencrypt = dx_aead_givencrypt,
			.ivsize = GCM_BLOCK_RFC4_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		},
		.cipher_mode = SEP_CIPHER_GCTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_NULL,
	},
	{
		.name = "rfc4543(gcm(aes))",
		.driver_name = "rfc4543-gcm-aes-dx",
		.blocksize = 1,
		.type = CRYPTO_ALG_TYPE_AEAD,
		.template_aead = {
			.setkey = dx_rfc4543_gcm_setkey,
			.setauthsize = dx_rfc4543_gcm_setauthsize,
			.encrypt = dx_rfc4543_gcm_encrypt,
			.decrypt = dx_rfc4543_gcm_decrypt,
			.givencrypt = dx_aead_givencrypt,
			.ivsize = GCM_BLOCK_RFC4_IV_SIZE,
			.maxauthsize = AES_BLOCK_SIZE,
		},
		.cipher_mode = SEP_CIPHER_GCTR,
		.flow_mode = S_DIN_to_AES,
		.auth_mode = SEP_HASH_NULL,
	}, 
#endif /*DX_CC_HAS_AES_GCM*/
};

static struct dx_crypto_alg *dx_aead_create_alg(struct dx_alg_template *template)
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
	alg->cra_ctxsize = sizeof(struct dx_aead_ctx);
	alg->cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY |
			 template->type;
	alg->cra_init = dx_aead_init;
	alg->cra_exit = dx_aead_exit;
	alg->cra_type = &crypto_aead_type;
	alg->cra_aead = template->template_aead;

	t_alg->cipher_mode = template->cipher_mode;
	t_alg->flow_mode = template->flow_mode;
	t_alg->auth_mode = template->auth_mode;

	return t_alg;
}

int dx_aead_alloc(struct dx_drvdata *drvdata)
{
	struct dx_aead_handle *aead_handle;
	struct dx_crypto_alg *t_alg;
	int rc = -ENOMEM;
	int alg;

	aead_handle = kmalloc(sizeof(struct dx_aead_handle), GFP_KERNEL);
	if (aead_handle == NULL) {
		rc = -ENOMEM;
		goto fail0;
	}

	aead_handle->sram_workspace_addr = dx_sram_mgr_alloc(
		drvdata, MAX_HMAC_DIGEST_SIZE);
	if (aead_handle->sram_workspace_addr == NULL_SRAM_ADDR) {
		DX_LOG_ERR("SRAM pool exhausted\n");
		rc = -ENOMEM;
		goto fail1;
	}

	drvdata->aead_handle = aead_handle;
	INIT_LIST_HEAD(&aead_handle->aead_list);

	/* Linux crypto */
	for (alg = 0; alg < ARRAY_SIZE(aead_algs); alg++) {
		t_alg = dx_aead_create_alg(&aead_algs[alg]);
		if (IS_ERR(t_alg)) {
			rc = PTR_ERR(t_alg);
			DX_LOG_ERR("%s alg allocation failed\n",
				 aead_algs[alg].driver_name);
			goto fail1;
		}
		t_alg->drvdata = drvdata;

		rc = crypto_register_alg(&t_alg->crypto_alg);
		if (unlikely(rc != 0)) {
			DX_LOG_ERR("%s alg registration failed\n",
				t_alg->crypto_alg.cra_driver_name);
			goto fail2;
		} else {
			list_add_tail(&t_alg->entry, &aead_handle->aead_list);
			DX_LOG_DEBUG("Registered %s\n", t_alg->crypto_alg.cra_driver_name);
		}
	}

	return 0;

fail2:
	kfree(t_alg);
fail1:
	kfree(aead_handle);
fail0:
	return rc;
}

int dx_aead_free(struct dx_drvdata *drvdata)
{
	struct dx_crypto_alg *t_alg, *n;
	struct dx_aead_handle *aead_handle =
		(struct dx_aead_handle *)drvdata->aead_handle;

	if (aead_handle != 0) {
		/* Remove registered algs */
		list_for_each_entry_safe(t_alg, n, &aead_handle->aead_list, entry) {
			crypto_unregister_alg(&t_alg->crypto_alg);
			list_del(&t_alg->entry);
			kfree(t_alg);
		}
		kfree(aead_handle);
		drvdata->aead_handle = NULL;
	}

	return 0;
}

