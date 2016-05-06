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

/* \file dx_cipher.h
   Discretix Cipher Crypto API
 */

#ifndef __DX_CIPHER_H__
#define __DX_CIPHER_H__

#include <linux/kernel.h>
#include <crypto/algapi.h>
#include "dx_driver.h"

#if DX_CC_HAS_SEC_KEY
#define MAX_KEY_BUF_SIZE (DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_BYTES)
#else
#define MAX_KEY_BUF_SIZE AES_MAX_KEY_SIZE
#endif

struct ablkcipher_req_ctx {
	struct async_gen_req_ctx gen_ctx;
	enum dx_req_dma_buf_type dma_buf_type;
	uint32_t in_nents;
	uint32_t in_mlli_nents;
	uint32_t out_nents;
	uint32_t out_mlli_nents;
	uint8_t *backup_info; /*store iv for generated IV flow*/
	bool is_giv;
	struct mlli_params mlli_params;
	enum dx_secure_dir_type sec_dir;
};



int dx_ablkcipher_alloc(struct dx_drvdata *drvdata);

int dx_ablkcipher_free(struct dx_drvdata *drvdata);

#endif /*__DX_CIPHER_H__*/
