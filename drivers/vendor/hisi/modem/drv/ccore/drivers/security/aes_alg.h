/**********************************************************************
 AES(Advanced Encryption Standard) Algorithm Interface
 Author: Algorithm Team of Security Solution Department. SunYi 15569
***********************************************************************
					Copyright 2005 HuaWei Tech. Inc.
						ALL RIGHTS RESERVED
***********************************************************************
 This is an independent implementation of the encryption algorithm:
           RIJNDAEL by Joan Daemen and Vincent Rijmen
 which is choosed as AES(Advanced Encryption Standard) algorithm by
 NIST(National Institute of Standards and Technology, US).
***********************************************************************
 This implemention references the implemention of Dr Brian Gladman
 (gladman@seven77.demon.co.uk) 14th January 1999.
**********************************************************************/

/**********************************************************************
AES_set_key(AES_ctx *ctx, const void *pk, uint32 klen, uint16 enc_only)
FUNCTION:	generate round keys
   INPUT:	ctx		: context contains round key info
			pk		: random key given by user
			klen	: len of key, must be 128/192/256
			enc_only:
				0: gen both enc and dec round keys(slower key gen)
				1: gen enc round keys only(faster key gen)
***********************************************************************
AES_encrypt(const AES_ctx *ctx, const void *pi, void *po)

FUNCTION:	encrypting one block
   INPUT:	ctx		: context from AES_set_key
			pi		: plain text block for input
			po		: cipher text block for input
  Notice: the size of block must be 128bits=16bytes
***********************************************************************
AES_decrypt(const AES_ctx *ctx, const void *pi, void *po)
FUNCTION:	decrypting one block
   INPUT:	ctx		: context from AES_set_key with enc_only=0
			pi		: plain text block for input
			po		: cipher text block for input
  Notice:
		the size of block must be 128bits = 16bytes
		ctx must be get from AES_set_key, and enc_only must be 0
**********************************************************************/
#include "aescfg.h"
#include "security_types.h"

#ifndef __AES_ALG_H__
#define __AES_ALG_H__


typedef struct _AES_ctx {
	uint32  klen;     /* key length, affect round number of enc or dec */
	uint32  ekey[64]; /* round keys for encryption                     */
	uint32  dkey[64]; /* round keys for decryption                     */
	uint32  decrypt;  /* to tell if the decrypt round keys are exist   */
} AES_ctx;


AES_ctx *crypto_aes_set_key(AES_ctx *ctx, const void *pk, uint32 klen, uint32 enc_only);
void crypto_aes_encrypt(const AES_ctx *ctx, const void *pi, void *po);
void crypto_aes_decrypt(const AES_ctx *ctx, const void *pi, void *po);

#endif /* _AES_H_ */

