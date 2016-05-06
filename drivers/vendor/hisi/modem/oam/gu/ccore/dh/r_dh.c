#include <stdio.h>
#include <time.h>
#include "softcrypto.h"
#include "rand.h"
#include "nn.h"
#include "v_lib.h"
#include "product_config.h"

/*lint -e701 -e702 -e732 -e734 -e713 -e737 -e734 -e774*/

#if (FEATURE_VSIM == FEATURE_ON)
unsigned char prime[MAX_DH_BITS]
                     = {0xCE,0x67,0xDC,0xBE,0xEB,0x01,0x4B,0xA8,0x74,0xD8,0xCD,0xE2,0xFE,0xDC,0x99,0x72,0x17,0xD6,0x52,0xD7,0x45,0x41,0x83,0xB9,0x75,0xEE,0x94,0x26,0x3E,0xB7,0xC1,0xB6,
                        0x1B,0x4F,0x7E,0x4B,0x2B,0x0F,0x1A,0xCC,0x89,0x78,0xA9,0xEA,0xCD,0xCF,0xA0,0x6B,0xFC,0x18,0x73,0x94,0x1F,0x9B,0x31,0xBA,0x1F,0xB0,0x8F,0x7F,0xF0,0xC4,0xB0,0x05,
                        0x99,0xC7,0xC6,0x2E,0x3B,0xCD,0xDC,0x5D,0xF8,0x10,0xB6,0x4B,0x75,0x55,0x57,0x5E,0x00,0x6B,0x37,0xB7,0x7C,0x24,0x2B,0x61,0x18,0xE4,0xBB,0xFB,0x5C,0x63,0xBD,0xA7,
                        0x19,0x88,0x68,0x1C,0x8E,0x88,0x43,0x1F,0x94,0x79,0x0C,0x91,0x39,0x4C,0x76,0x7D,0x0C,0x41,0xC4,0x04,0x23,0x35,0xFA,0xF0,0xD2,0xBD,0xFE,0xB0,0xC4,0xA2,0x27,0x93};

unsigned char generator[]= {0x02};


void DH_ChangeDHParas(unsigned int ParaPLen, unsigned char *ParaP, unsigned int ParaGLen, unsigned char *ParaG)
{
    if ((ParaP != NULL)&&(ParaPLen != 0))
    {
        memcpy(prime, ParaP, sizeof(prime));
    }

    if ((ParaG != NULL)&&(ParaGLen != 0))
    {
        memcpy(generator, ParaG, sizeof(generator));
    }

    return;
}

void DH_FillFixParams(DH_KEY *params)
{
    params->generatorLen = sizeof(generator);

    memcpy(params->generator, generator, params->generatorLen);

    params->primeLen = sizeof(prime);

    memcpy(params->prime, prime, params->primeLen);

    return;
}

/*lint -e438*/
int RandomUpdate (R_RANDOM_STRUCT *randomStruct, unsigned char *block, unsigned int blockLen)
{
  MD5_CTX context;
  unsigned char digest[16];
  unsigned int i, x;

  USIMM_MD5Init (&context);
  USIMM_MD5Update (&context, block, blockLen);
  USIMM_MD5Final (digest, &context);

  /* add digest to state */
  x = 0;
  for (i = 0; i < 16; i++) {
    x += randomStruct->state[15-i] + digest[15-i];
    randomStruct->state[15-i] = (unsigned char)x;
    x >>= 8;
  }

  if (randomStruct->bytesNeeded < blockLen)
    randomStruct->bytesNeeded = 0;
  else
    randomStruct->bytesNeeded -= blockLen;

  /* Zeroize sensitive information.
   */
  memset ((POINTER)digest, 0, sizeof (digest));
  x = 0;

  return (0);
}
/*lint +e438*/

int GenerateBytes (unsigned char *block, unsigned int blockLen, R_RANDOM_STRUCT *randomStruct)
{
  MD5_CTX context;
  unsigned int available, i;

  if (randomStruct->bytesNeeded)
    return (RE_NEED_RANDOM);

  available = randomStruct->outputAvailable;

  while (blockLen > available) {
    memcpy
      ((POINTER)block, (POINTER)&randomStruct->output[16-available],
       available);
    block += available;
    blockLen -= available;

    /* generate new output */
    USIMM_MD5Init (&context);
    USIMM_MD5Update (&context, randomStruct->state, 16);
    USIMM_MD5Final (randomStruct->output, &context);
    available = 16;

    /* increment state */
    for (i = 0; i < 16; i++)
      if (randomStruct->state[15-i]++)
        break;
  }

  memcpy ((POINTER)block, (POINTER)&randomStruct->output[16-available], blockLen);
  randomStruct->outputAvailable = available - blockLen;

  return (0);
}

int SetupDHAgreement  (unsigned char *publicValue, unsigned char *privateValue, unsigned int privateValueLen, DH_KEY *params, R_RANDOM_STRUCT *randomStruct)
{
  int status;
  UINT4 g[MAX_DIGITS_LEN], p[MAX_DIGITS_LEN], x[MAX_DIGITS_LEN],
    y[MAX_DIGITS_LEN];
  unsigned int pDigits, xDigits;

  BIGNUM_Decode (p, MAX_DIGITS_LEN, params->prime, params->primeLen);
  pDigits = BIGNUM_Digits (p, MAX_DIGITS_LEN);
  BIGNUM_Decode (g, pDigits, params->generator, params->generatorLen);

  /* Generate private value.
   */
  status = GenerateBytes (privateValue, privateValueLen, randomStruct);
  if (0 != status)
    return (status);
  BIGNUM_Decode (x, pDigits, privateValue, privateValueLen);
  xDigits = BIGNUM_Digits (x, pDigits);

  /* Compute y = g^x mod p.
   */
  BIGNUM_ModExp (y, g, x, xDigits, p, pDigits);

  BIGNUM_Encode (publicValue, params->primeLen, y, pDigits);

  /* Zeroize sensitive information.
   */
  memset ((POINTER)x, 0, sizeof (x));

  return (0);
}

/*lint -e525 -e438*/
int GeneratePublicKey(DH_KEY *params, unsigned char *publicValue, unsigned int pubValueLen)
{
    rand_t *rd;
	int rv;
    time_t seed;
    unsigned int bytesNeeded;
    unsigned char seedByte[20] = {0};
    R_RANDOM_STRUCT randomStruct;

    bytesNeeded = pubValueLen;
	randomStruct.bytesNeeded = bytesNeeded;
	memset ((POINTER)randomStruct.state, 0, sizeof (randomStruct.state));
	randomStruct.outputAvailable = 0;

    time(&seed);
    rd = rand_open();
    if (rd == NULL) return -1;
    rand_set(rd,&seed,4);
    if (rd == NULL) return -1;

    while (1)
    {
		bytesNeeded = randomStruct.bytesNeeded;

		if (bytesNeeded == 0)
            break;
        rand_get(rd,seedByte,16);
        if (rd == NULL) return -1;

        RandomUpdate(&randomStruct, seedByte, 16);
    }

    rd = rand_close(rd);

    params->priVallen = pubValueLen;

	rv = SetupDHAgreement(publicValue,params->privateValue,pubValueLen,	params,&randomStruct);
	return rv;
}
/*lint +e525 +e438*/

int DH_GeneratePublicValue(unsigned char *publicValue, unsigned int pubValueLen, DH_KEY *params)
{
	return GeneratePublicKey(params, publicValue, pubValueLen);
}

/*lint -e578*/
int AgreeKey(DH_KEY *params,unsigned char *agreedKey,unsigned int keyLen, unsigned char *otherPublicValue)
{
    UINT4 prime[MAX_DIGITS_LEN], x[MAX_DIGITS_LEN], y[MAX_DIGITS_LEN], z[MAX_DIGITS_LEN];
    unsigned int pDigits, xDigits;

    BIGNUM_Decode (prime, MAX_DIGITS_LEN, params->prime, params->primeLen);
    pDigits = BIGNUM_Digits (prime, MAX_DIGITS_LEN);
    BIGNUM_Decode (x, pDigits, params->privateValue, params->priVallen);
    xDigits = BIGNUM_Digits (x, pDigits);
    BIGNUM_Decode (y, pDigits, otherPublicValue, params->primeLen);

    if (BIGNUM_Cmp (y, prime, pDigits) >= 0)
        return (RE_DATA);

    /* Compute z = y^x mod prime.
    */
    BIGNUM_ModExp (z, y, x, xDigits, prime, pDigits);
    BIGNUM_Encode (agreedKey, params->primeLen, z, pDigits);

    return 0;
}
/*lint -e578*/

int DH_ComputeAgreedKey(unsigned char *agreedKey,  unsigned char *otherPublicValue, DH_KEY *params )
{
	return AgreeKey(params, agreedKey, MAX_DH_BITS, otherPublicValue);
}
#endif

/*lint +e701 +e702 +e732 +e734 +e713 +e737 +e734 +e774*/
