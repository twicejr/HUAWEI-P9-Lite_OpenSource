#ifndef _SOFT_CRYPTO_H_
#define _SOFT_CRYPTO_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define SOFT_ENC	0	/* MODE == encrypt */
#define SOFT_DEC	1	/* MODE == decrypt */

#define    SOFT_ECB        1    /*  Are we inputLening in ECB mode?   */
#define    SOFT_CBC        2    /*  Are we inputLening in CBC mode?   */
#define    SOFT_CFB1       3

#define            KEY_LEN_ERROR                           1001
#define            OTHER_ERROR                             1002
#define            DATA_LEN_ERROR                          1003

/* UINT2 defines a two byte word */
#define	UINT2		unsigned short int

/* UINT4 defines a four byte word */
#define	UINT4		unsigned long int
#define POINTER		unsigned char *
#define PROTO_LIST(list) list

/*在win系统中，long为4个字节，long long 为8个字节。*/
/*其他系统，我没有测试过，请测试后修改宏*/
typedef unsigned int SilcUInt32;
typedef signed int SilcInt32;

#ifndef WIN32
	typedef unsigned long long SilcUInt64;
	typedef signed long long SilcInt64;
#else
	typedef unsigned __int64 SilcUInt64;
	typedef signed __int64 SilcInt64;
#endif


typedef struct {
	UINT4 state[4];                                   /* state (ABCD) */
	UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

/* Random structure.
 */
typedef struct {
  unsigned int bytesNeeded;
  unsigned char state[16];
  unsigned int outputAvailable;
  unsigned char output[16];
} R_RANDOM_STRUCT;


#define MIN_MODULUS_BITS 1024
#define MAX_MODULUS_BITS 1024
#define MAX_MODULUS_LEN ((MAX_MODULUS_BITS + 7) / 8)

#define RE_NEED_RANDOM 0x0408
#define RE_DATA 0x0401

/* Diffie-Hellman parameters.
*/
#define MAX_DH_BITS 128
typedef struct {
	unsigned char privateValue[MAX_DH_BITS];
	unsigned char priVallen;
	unsigned char prime[MAX_DH_BITS];                   /* prime */
	unsigned int  primeLen;
	unsigned char generator[MAX_DH_BITS];                /* generator */
	unsigned int generatorLen;                         /* length of generator */
} DH_KEY;

/* Gen  Rand */
	unsigned int Rand_SetSend(unsigned char *pSend, unsigned long ulSendlen);
	unsigned int Rand_GenRand(unsigned char *pRand, unsigned long ulRandLen);
/* */


	/*MD5*/
	void USIMM_MD5Init(MD5_CTX *);
	void USIMM_MD5Update(MD5_CTX *, unsigned char *, unsigned int);
	void USIMM_MD5Final(unsigned char [16], MD5_CTX *);


	/*DH*/
    void DH_ChangeDHParas(unsigned int ParaPLen, unsigned char *ParaP, unsigned int ParaGLen, unsigned char *ParaG);

    void DH_FillFixParams(DH_KEY *params);

	int InitDHParam(DH_KEY *pContext,                       /* new Diffie-Hellman parameters */
		unsigned int primeBits,                          /* length of prime in bits */
		unsigned int subPrimeBits                    /* length of subprime in bits */
		);

	int DH_GeneratePublicValue(
			unsigned char *publicValue,                             /* new public value */
			unsigned int pubValueLen,                    /* length of private value */
			DH_KEY *params                          /* Diffie-Hellman parameters */
	);

	int DH_ComputeAgreedKey(
			unsigned char *agreedKey,                                 /* new agreed key */
			unsigned char *otherPublicValue,                    /* other's public value */
			DH_KEY *params                           /* Diffie-Hellman parameters */
	);


	int AESEncrypt(unsigned char *plain, int plainLen, unsigned char *Key, unsigned short KeyLen, unsigned char *cipher, int cipherLen);
	int AESDecrypt(unsigned char *cipher, int cipherLen, unsigned char *Key, unsigned short KeyLen, unsigned char *plain, int plainLen);

	int AESEncryptS(unsigned char *input, int inputLen, unsigned char *Key, int keyBits, unsigned char *cipher, int cipherLen);
	int AESDecryptS(unsigned char *cipher, int cipherLen, unsigned char *Key, int keyBits, unsigned char *plain, int plainLen);

#ifdef  __cplusplus
}
#endif

#endif
