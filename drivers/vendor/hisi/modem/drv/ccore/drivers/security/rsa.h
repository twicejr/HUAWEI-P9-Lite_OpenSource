#ifndef __RSA_H__
#define __RSA_H__

#include "security_types.h"

/* <AG5D00482 by wangyali on 20061218 begin */
//delete the including of "huawei_oeminfo.h"
/* AG5D00482 by wangyali on 20061218 end> */
/* rsa key lengths */
#define MIN_RSA_MODULUS_BITS 508
#define MAX_RSA_MODULUS_BITS 1024

#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 7)/8)
#define MAX_RSA_PRIME_BITS ((MAX_RSA_MODULUS_BITS +1)/2)
#define MAX_RSA_PRIME_LEN ((MAX_RSA_PRIME_BITS+7)/8)

/* 结构体rsa_public_key在文件huawei_oeminfo.h中定义，删除此处的定义 */
/* <AG5D00482 by wangyali on 20061218 begin */
typedef struct _rsa_public_key
{
  uint32 bits;
  uint8 modulus[MAX_RSA_MODULUS_LEN];
  uint8 public_exponent[MAX_RSA_MODULUS_LEN];
}rsa_public_key;
/* AG5D00482 by wangyali on 20061218 end> */

typedef struct _rsa_private_key
{
  uint32 bits;
  uint8 modulus[MAX_RSA_MODULUS_LEN];
  uint8 public_exponent[MAX_RSA_MODULUS_LEN];
  uint8 private_exponent[MAX_RSA_MODULUS_LEN];
  uint8 prime[2][MAX_RSA_MODULUS_LEN];
  uint8 prime_exponent[2][MAX_RSA_MODULUS_LEN];   /* exponents for CRT */
  uint8 coefficient[MAX_RSA_MODULUS_LEN];         /* CRT coefficient */
}rsa_private_key;

int16 rsa_public_block(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_public_key *public_key);
int16 rsa_private_block(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_private_key *private_key);
int16 rsa_private_encrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_private_key *private_key );
int16 rsa_public_decrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_public_key *public_key);
int16 rsa_public_encrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_public_key *public_key );
int16 rsa_private_decrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_private_key *private_key);
#endif

