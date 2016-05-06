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


#ifndef __SECURE_KEY_INT_DEFS_H__
#define __SECURE_KEY_INT_DEFS_H__


/* secure key message format
	Word No.    Bits        Field Name
	0	    31:0        Token
	1	    31:0        Version
	2-4                     Nonce
	5           2:0         Secure key type (aes128 / aes256 / multi2)
		    3           Direction (enc / dec)
                    7:4         Cipher mode (cbc / ctr / ofb / cbc_cts)
                    15:8        Number of rounds (only for Multi2)
                    31:16       reserved
       6            31:0        Lower bound address
       7            31:0        Upper bound address
       8-17                     Restricted key  (encryption of the secured key padded with zeroes)
       18-21                    mac results
*/

#define DX_SECURE_KEY_TOKEN_OFFSET			0
#define DX_SECURE_KEY_TOKEN_VALUE			0x9DB2F60F

#define DX_SECURE_KEY_VERSION_OFFSET			1

#define DX_SECURE_KEY_NONCE_OFFSET			2

#define DX_SECURE_KEY_RESTRICT_CONFIG_OFFSET		5
#define DX_SECURE_KEY_RESTRICT_KEY_TYPE_BIT_SHIFT	0
#define DX_SECURE_KEY_RESTRICT_KEY_TYPE_BIT_SIZE	3
#define DX_SECURE_KEY_RESTRICT_DIR_BIT_SHIFT		3
#define DX_SECURE_KEY_RESTRICT_DIR_BIT_SIZE		1
#define DX_SECURE_KEY_RESTRICT_MODE_BIT_SHIFT		4
#define DX_SECURE_KEY_RESTRICT_MODE_BIT_SIZE		4
#define DX_SECURE_KEY_RESTRICT_NROUNDS_BIT_SHIFT	8
#define DX_SECURE_KEY_RESTRICT_NROUNDS_BIT_SIZE		8
#define DX_SECURE_KEY_RESTRICT_CTR_RANGE_BIT_SHIFT	16
#define DX_SECURE_KEY_RESTRICT_CTR_RANGE_BIT_SIZE	16

#define DX_SECURE_KEY_RESTRICT_LOWER_BOUNND_OFFSET	6
#define DX_SECURE_KEY_RESTRICT_UPPER_BOUND_OFFSET	8

#define DX_SECURE_KEY_RESTRICT_IV_CTR_OFFSET		10

#define DX_SECURE_KEY_RESTRICT_KEY_OFFSET		14
#define DX_SECURE_KEY_RESTRICT_KEY_SIZE_IN_BYTES	40

#define DX_SECURE_KEY_MAC_OFFSET			24
#define DX_SECURE_KEY_PACKAGE_BUF_SIZE_IN_WORDS		28

#define HW_CIPHER_MULTI2_OFB				2

#define DX_SECURE_KEY_BYTE_MASK				0xFF

#define DX_SECURE_KEY_MAINTENANCE_MIN_PAIRS		1
#define DX_SECURE_KEY_MAINTENANCE_MAX_PAIRS		5

#define DX_SECURE_KEY_MAJOR_VERSION			2
#define DX_SECURE_KEY_MINOR_VERSION			1
#define DX_SECURE_KEY_VERSION_NUM			(DX_SECURE_KEY_MAJOR_VERSION<<16 |DX_SECURE_KEY_MINOR_VERSION )


/* CCM data structers: B0, A, text(key) - Note! each part should be a multiple of 16B */

/* B0[16B]: 0x7a,nonce[12],00,00,0x28 */
#define DX_SECURE_KEY_B0_SIZE_IN_BYTES		16
#define DX_SECURE_KEY_B0_FLAGS_OFFSET		0
#define DX_SECURE_KEY_B0_FLAGS_VALUE		0x7A
#define DX_SECURE_KEY_B0_NONCE_OFFSET		1
#define DX_SECURE_KEY_B0_DATA_LEN_OFFSET	15

/* A[32B]: 0x12,config,N,base[4],tail[4],token[4],sw_version[4],0[12]*/
#define DX_SECURE_KEY_ADATA_SIZE_IN_BYTES	48
#define DX_SECURE_KEY_ADATA_LEN_OFFSET		(DX_SECURE_KEY_B0_SIZE_IN_BYTES+1)
#define DX_SECURE_KEY_ADATA_LEN_IN_BYTES	0x2E
#define DX_SECURE_KEY_ADATA_CONFIG_OFFSET	18
#define DX_SECURE_KEY_ADATA_NROUNDS_OFFSET	19
#define DX_SECURE_KEY_ADATA_LOWER_BOUND_OFFSET	20 
#define DX_SECURE_KEY_ADATA_LOWER_BOUND_OFFSET_IN_WORDS		DX_SECURE_KEY_ADATA_LOWER_BOUND_OFFSET/sizeof(uint32_t) 
#define DX_SECURE_KEY_ADATA_UPPER_BOUND_OFFSET	28 
#define DX_SECURE_KEY_ADATA_UPPER_BOUND_OFFSET_IN_WORDS		DX_SECURE_KEY_ADATA_UPPER_BOUND_OFFSET/sizeof(uint32_t)  
#define DX_SECURE_KEY_ADATA_TOKEN_OFFSET	36 
#define DX_SECURE_KEY_ADATA_TOKEN_OFFSET_IN_WORDS	 	DX_SECURE_KEY_ADATA_TOKEN_OFFSET/sizeof(uint32_t) 
#define DX_SECURE_KEY_ADATA_VERSION_OFFSET	40 
#define DX_SECURE_KEY_ADATA_VERSION_OFFSET_IN_WORDS	 	DX_SECURE_KEY_ADATA_VERSION_OFFSET/sizeof(uint32_t) 
#define DX_SECURE_KEY_ADATA_IV_CTR_OFFSET	44 
#define DX_SECURE_KEY_ADATA_IV_CTR_OFFSET_IN_WORDS		DX_SECURE_KEY_ADATA_IV_CTR_OFFSET/sizeof(uint32_t)
#define DX_SECURE_KEY_ADATA_CTR_RANGE_OFFSET	60 
#define DX_SECURE_KEY_ADATA_CTR_RANGE_OFFSET_IN_WORDS		DX_SECURE_KEY_ADATA_CTR_RANGE_OFFSET/sizeof(uint32_t)



/* text[48B]: key[40],0[8] */
#define DX_SECURE_KEY_CCM_KEY_OFFSET		(DX_SECURE_KEY_B0_SIZE_IN_BYTES+DX_SECURE_KEY_ADATA_SIZE_IN_BYTES)
#define DX_SECURE_KEY_CCM_KEY_OFFSET_IN_WORDS	DX_SECURE_KEY_CCM_KEY_OFFSET/sizeof(uint32_t) 
#define DX_SECURE_KEY_CCM_KEY_SIZE_IN_BYTES	48 

#define DX_SECURE_KEY_CCM_BUF_IN_BYTES		(DX_SECURE_KEY_B0_SIZE_IN_BYTES+DX_SECURE_KEY_ADATA_SIZE_IN_BYTES+DX_SECURE_KEY_CCM_KEY_SIZE_IN_BYTES)
#define DX_SECURE_KEY_CCM_BUF_IN_WORDS		DX_SECURE_KEY_CCM_BUF_IN_BYTES/sizeof(uint32_t)



#define DX_SECURE_KEY_SET_NONCE_LEN(val, nonceLen)  val|=((nonceSize&0xF)<<4)
#define DX_SECURE_KEY_SET_CTR_LEN(val, ctrLen)  val|=(ctrLen&0xF)

#define DX_SECURE_KEY_GET_NONCE_LEN(val) ((val>>4)&0xF)
#define DX_SECURE_KEY_GET_CTR_LEN(val)   (val&0xF)

#endif /*__SECURE_KEY_INT_DEFS_H__*/


