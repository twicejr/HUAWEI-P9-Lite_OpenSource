#ifndef __CIPHER_AES_H__
#define __CIPHER_AES_H__

//#include "config.h"
#include "aes_alg.h"


/*  Generic Defines  */


#define     MODE_ECB              1 /*  Are we ciphering in ECB mode?   */
#define     MODE_CBC              2 /*  Are we ciphering in CBC mode?   */
#define     MODE_CFB1             3 /*  Are we ciphering in 1-bit CFB mode? */
#ifndef     TRUE
#define     TRUE                  1
#endif
#ifndef     FALSE
#define     FALSE                 0
#endif
#define     BITSPERBLOCK        128 /* Default number of bits in a cipher block */

/*  Error Codes  */
#define     SUCCESS              0
#define     BAD_KEY_DIR          -1 /*  Key direction is invalid, e.g., unknown value */
#define     BAD_KEY_MAT          -2 /*  Key material not of correct length */
#define     BAD_KEY_INSTANCE     -3 /*  Key passed is not valid */
#define     BAD_CIPHER_MODE      -4 /*  Params struct passed to cipherInit invalid */
#define     BAD_CIPHER_STATE     -5 /*  Cipher in wrong state (e.g., not initialized) */
#define     BAD_BLOCK_LENGTH     -6
#define     BAD_CIPHER_INSTANCE  -7
#define     BAD_DATA             -8 /*  Data contents are invalid, e.g., invalid padding */
#define     BAD_OTHER            -9 /*  Unknown error */
#define	  BAD_CIPHER	-10

/*  Algorithm-specific Defines  */
#define     MAX_KEY_SIZE         64 /* # of ASCII char's needed to represent a key */
#define     MAX_IV_SIZE          16 /* # bytes needed to represent an IV  */


typedef struct _crypto_aes
{
	AES_ctx 	aes_ctx;
	uint8 iv[MAX_IV_SIZE];
	uint32 mode;
	
}crypto_aes;

int16 crypto_aes_init(crypto_aes *cipher, uint8 keymaterial[64], int16 keybits, int32 mode, uint8 iv[32]);
int16 crypto_aes_encrypt_block(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen );
int16 crypto_aes_decrypt_block(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen );
int16 crypto_aes_encrypt_pad(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen );
int16 crypto_aes_decrypt_pad(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen );
#endif

