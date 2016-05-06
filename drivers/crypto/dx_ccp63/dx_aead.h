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

/* \file dx_aead.h
   Discretix AEAD Crypto API
 */

#ifndef __DX_AEAD_H__
#define __DX_AEAD_H__

#include <linux/kernel.h>
#include <crypto/algapi.h>
#include <crypto/ctr.h>


/* mac_cmp - HW writes 8 B but all bytes hold the same value */
#define ICV_CMP_SIZE 8
#define CCM_CONFIG_BUF_SIZE (AES_BLOCK_SIZE*3)
#define MAX_MAC_SIZE MAX(SHA256_DIGEST_SIZE, AES_BLOCK_SIZE)


/* defines for AES GCM configuration buffer */
#define GCM_BLOCK_LEN_SIZE 8

#define GCM_BLOCK_RFC4_IV_OFFSET    	4  
#define GCM_BLOCK_RFC4_IV_SIZE  	    8  /* IV size for rfc's */
#define GCM_BLOCK_RFC4_NONCE_OFFSET 	0  
#define GCM_BLOCK_RFC4_NONCE_SIZE   	4  



/* Offsets into AES CCM configuration buffer */
#define CCM_B0_OFFSET 0
#define CCM_A0_OFFSET 16
#define CCM_CTR_COUNT_0_OFFSET 32
/* CCM B0 and CTR_COUNT constants. */
#define CCM_BLOCK_NONCE_OFFSET 1  /* Nonce offset inside B0 and CTR_COUNT */
#define CCM_BLOCK_NONCE_SIZE   3  /* Nonce size inside B0 and CTR_COUNT */
#define CCM_BLOCK_IV_OFFSET    4  /* IV offset inside B0 and CTR_COUNT */
#define CCM_BLOCK_IV_SIZE      8  /* IV size inside B0 and CTR_COUNT */

enum aead_ccm_header_size {
	ccm_header_size_null = -1,
	ccm_header_size_zero = 0,
	ccm_header_size_2 = 2,
	ccm_header_size_6 = 6,
	ccm_header_size_max = INT32_MAX
};

struct aead_req_ctx {
	/* Allocate cache line although only 4 bytes are needed to
	*  assure next field falls @ cache line 
	*  Used for both: digest HW compare and CCM/GCM MAC value */
	uint8_t mac_buf[MAX_MAC_SIZE] ____cacheline_aligned;
	uint8_t ctr_iv[AES_BLOCK_SIZE] ____cacheline_aligned;

	//used in gcm 
	uint8_t gcm_iv_inc1[AES_BLOCK_SIZE] ____cacheline_aligned;
	uint8_t gcm_iv_inc2[AES_BLOCK_SIZE] ____cacheline_aligned;
	uint8_t hkey[AES_BLOCK_SIZE] ____cacheline_aligned;
	struct {
	uint8_t lenA[GCM_BLOCK_LEN_SIZE] ____cacheline_aligned;
	uint8_t lenC[GCM_BLOCK_LEN_SIZE] ;
	} gcm_len_block ;

	uint8_t ccm_config[CCM_CONFIG_BUF_SIZE] ____cacheline_aligned;
	unsigned int hw_iv_size ____cacheline_aligned; /*HW actual size input*/
	uint8_t backup_mac[MAX_MAC_SIZE]; /*used to prevent cache coherence problem*/
	uint8_t *backup_iv; /*store iv for generated IV flow*/
	uint8_t *backup_giv; /*store iv for rfc3686(ctr) flow*/
	dma_addr_t mac_buf_dma_addr; /* internal ICV DMA buffer */
	dma_addr_t ccm_iv0_dma_addr; /* buffer for internal ccm configurations */
	dma_addr_t icv_dma_addr; /* Phys. address of ICV */

	//used in gcm 
	dma_addr_t gcm_iv_inc1_dma_addr; /* buffer for internal gcm configurations */
	dma_addr_t gcm_iv_inc2_dma_addr; /* buffer for internal gcm configurations */
	dma_addr_t hkey_dma_addr; /* Phys. address of hkey */
	dma_addr_t gcm_block_len_dma_addr; /* Phys. address of gcm block len */

	uint8_t *icv_virt_addr; /* Virt. address of ICV */
	struct async_gen_req_ctx gen_ctx;
	struct dx_mlli assoc;
	struct dx_mlli src;
	struct dx_mlli dst;
	enum dx_req_dma_buf_type assoc_buff_type;
	enum dx_req_dma_buf_type data_buff_type;
	uint32_t curr_mlli_size; /* mlli size in SRAM (in octets) */
	struct mlli_params mlli_params;
	unsigned int cryptlen;
	struct scatterlist ccm_adata_sg;
	enum aead_ccm_header_size ccm_hdr_size;
	unsigned int req_authsize;
	enum sep_cipher_mode cipher_mode;
	bool is_icv_fragmented;
	bool is_single_pass;
	bool plaintext_authenticate_only; //for gcm_rfc4543
};

int dx_aead_alloc(struct dx_drvdata *drvdata);
int dx_aead_free(struct dx_drvdata *drvdata);

#endif /*__DX_AEAD_H__*/
