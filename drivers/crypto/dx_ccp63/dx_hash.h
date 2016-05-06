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

/* \file dx_hash.h
   Discretix Hash Crypto API
 */

#ifndef __DX_HASH_H__
#define __DX_HASH_H__


#define HMAC_IPAD_CONST	0x36363636
#define HMAC_OPAD_CONST	0x5C5C5C5C
#if (DX_DEV_SHA_MAX > 256)
#define HASH_LEN_SIZE 16
#define DX_MAX_HASH_DIGEST_SIZE	SHA512_DIGEST_SIZE
#define DX_MAX_HASH_BLCK_SIZE SHA512_BLOCK_SIZE
#else
#define HASH_LEN_SIZE 8
#define DX_MAX_HASH_DIGEST_SIZE	SHA256_DIGEST_SIZE
#define DX_MAX_HASH_BLCK_SIZE SHA256_BLOCK_SIZE
#endif

#define XCBC_MAC_K1_OFFSET 0
#define XCBC_MAC_K2_OFFSET 16
#define XCBC_MAC_K3_OFFSET 32

/* ahash state */
struct ahash_req_ctx {
	uint8_t buff0[DX_MAX_HASH_BLCK_SIZE] ____cacheline_aligned;
	uint8_t buff1[DX_MAX_HASH_BLCK_SIZE] ____cacheline_aligned;
	uint8_t digest_result_buff[DX_MAX_HASH_DIGEST_SIZE] ____cacheline_aligned;
	struct async_gen_req_ctx gen_ctx ____cacheline_aligned;
	enum dx_req_dma_buf_type data_dma_buf_type;
	uint8_t *digest_buff;
	uint8_t *opad_digest_buff;
	uint8_t *digest_bytes_len;
	dma_addr_t opad_digest_dma_addr;
	dma_addr_t digest_buff_dma_addr;
	dma_addr_t digest_bytes_len_dma_addr;
	dma_addr_t digest_result_dma_addr;
	uint32_t buff0_cnt;
	uint32_t buff1_cnt;
	uint32_t buff_index;
	uint32_t xcbc_count; /* count xcbc update operatations */
	struct scatterlist buff_sg[2];
	struct scatterlist *curr_sg;
	uint32_t in_nents;
	uint32_t mlli_nents;
	struct mlli_params mlli_params;	
};

int dx_hash_alloc(struct dx_drvdata *drvdata);
int dx_hash_init_sram_digest_consts(struct dx_drvdata *drvdata);
int dx_hash_free(struct dx_drvdata *drvdata);

/*!
 * Gets the initial digest length
 * 
 * \param drvdata 
 * \param mode The Hash mode. Supported modes: MD5/SHA1/SHA224/SHA256/SHA384/SHA512
 * 
 * \return uint32_t returns the address of the initial digest length in SRAM
 */
dx_sram_addr_t
dx_ahash_get_initial_digest_len_sram_addr(void *drvdata, uint32_t mode);

/*!
 * Gets the address of the initial digest in SRAM 
 * according to the given hash mode
 * 
 * \param drvdata 
 * \param mode The Hash mode. Supported modes: MD5/SHA1/SHA224/SHA256/SHA384/SHA512
 * 
 * \return uint32_t The address of the inital digest in SRAM
 */
dx_sram_addr_t dx_ahash_get_larval_digest_sram_addr(void *drvdata, uint32_t mode);

#endif /*__DX_HASH_H__*/

