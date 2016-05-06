
/**********************************************************************
 AES(Advanced Encryption Standard) Algorithm Implementation
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
 Space spending of constant tables:
	17450 bytes for LARGE_TABLES defined
	9258 bytes for LARGE_TABLES not defined
**********************************************************************/

#include"aes_alg.h"
#include"aescfg.h"
#include"aesbitop.h"

/*lint --e{506, 553, 734, 778, 801} */
static void crypto_gen_tabs();

#if BYTE_ORDER != LITTLE_ENDIAN
#define BYTE_SWAP
#endif

#ifdef BYTE_SWAP
#define IOSWAP(x) BSWAP(x)
#else
#define IOSWAP(x) (x)
#endif

#ifdef FORCE_ALIGN
#define COPY_U32(po, pi) {                \
	((uint8 *)(po))[0] = ((uint8 *)(pi))[0];\
	((uint8 *)(po))[1] = ((uint8 *)(pi))[1];\
	((uint8 *)(po))[2] = ((uint8 *)(pi))[2];\
	((uint8 *)(po))[3] = ((uint8 *)(pi))[3];\
}
#else
#define COPY_U32(po, pi) {                \
	*((uint32 *)(po)) = *((uint32 *)(pi));\
}
#endif

/* tables for accelerating algorithm */

static   uint8 fexp[256];   /* every exponent of 11B in finite field  */
static   uint8 flog[256];   /* logarithm in finite field of base 11B  */
static   uint8 sbx[256];    /* S-box                                  */
static   uint8 isb[256];    /* inverse of S-box                       */
static uint32 rco[ 10];    /* round constants. rco[j] = 2^(j-1)      */
static uint32 ftn[4][256]; /* SubBytes+MixColumns for a single byte  */
static uint32 itn[4][256]; /* inverse transform for decryption       */

/* only for last round transform, maybe expensive for some platform. */
#ifdef LARGE_TABLES
uint32 ftl[4][256]; /* SubBytes in last round for a single byte       */
uint32 itl[4][256]; /* inverse transform in last round for decryption */
#endif

uint16 tab_gen = 0;

/* finite field multiplication*/
#define FMUL(a,b) (a&&b ? fexp[(flog[a]+flog[b])%255] : 0)

/* round transform in a non-last round */
/* bo: block out, bi: block in, n:word to be calc, k: cur round key */
#define FRN(bo, bi, n, k) (             \
	bo[n] =                             \
	ftn[0][BYTEN(bi[(n + 0) & 3], 0)] ^ \
	ftn[1][BYTEN(bi[(n + 1) & 3], 1)] ^ \
	ftn[2][BYTEN(bi[(n + 2) & 3], 2)] ^ \
	ftn[3][BYTEN(bi[(n + 3) & 3], 3)] ^ \
	*(k + n))

#define IRN(bo, bi, n, k) (             \
	bo[n] =                             \
	itn[0][BYTEN(bi[(n + 0) & 3], 0)] ^ \
	itn[1][BYTEN(bi[(n + 3) & 3], 1)] ^ \
	itn[2][BYTEN(bi[(n + 2) & 3], 2)] ^ \
	itn[3][BYTEN(bi[(n + 1) & 3], 3)] ^ \
	*(k + n))

#ifdef LARGE_TABLES

/* S transform for every byte in a word */
#define LSBX(x, n) (                \
	ftl[0][BYTEN(x, (n + 0) & 3)] ^ \
	ftl[1][BYTEN(x, (n + 1) & 3)] ^ \
	ftl[2][BYTEN(x, (n + 2) & 3)] ^ \
	ftl[3][BYTEN(x, (n + 3) & 3)])

/* round transform in the last round */
#define FRL(bo, bi, n, k) (             \
	bo[n] =                             \
	ftl[0][BYTEN(bi[(n + 0) & 3], 0)] ^ \
	ftl[1][BYTEN(bi[(n + 1) & 3], 1)] ^ \
	ftl[2][BYTEN(bi[(n + 2) & 3], 2)] ^ \
	ftl[3][BYTEN(bi[(n + 3) & 3], 3)] ^ \
	*(k + n))

#define IRL(bo, bi, n, k) (             \
	bo[n] =                             \
	itl[0][BYTEN(bi[(n + 0) & 3], 0)] ^ \
	itl[1][BYTEN(bi[(n + 3) & 3], 1)] ^ \
	itl[2][BYTEN(bi[(n + 2) & 3], 2)] ^ \
	itl[3][BYTEN(bi[(n + 1) & 3], 3)] ^ \
	*(k + n))

#else

#define LSBX(x, n) (                             \
	((uint32)sbx[BYTEN(x, (n + 0) & 3)] <<  0) ^ \
	((uint32)sbx[BYTEN(x, (n + 1) & 3)] <<  8) ^ \
	((uint32)sbx[BYTEN(x, (n + 2) & 3)] << 16) ^ \
	((uint32)sbx[BYTEN(x, (n + 3) & 3)] << 24))

#define FRL(bo, bi, n, k) (                              \
	bo[n] =                                              \
	ROTL(((uint32)sbx[BYTEN(bi[(n + 0) & 3], 0)]),  0) ^ \
	ROTL(((uint32)sbx[BYTEN(bi[(n + 1) & 3], 1)]),  8) ^ \
	ROTL(((uint32)sbx[BYTEN(bi[(n + 2) & 3], 2)]), 16) ^ \
	ROTL(((uint32)sbx[BYTEN(bi[(n + 3) & 3], 3)]), 24) ^ \
	*(k + n))

#define IRL(bo, bi, n, k) (                              \
	bo[n] =                                              \
	ROTL(((uint32)isb[BYTEN(bi[(n + 0) & 3], 0)]),  0) ^ \
	ROTL(((uint32)isb[BYTEN(bi[(n + 3) & 3], 1)]),  8) ^ \
	ROTL(((uint32)isb[BYTEN(bi[(n + 2) & 3], 2)]), 16) ^ \
	ROTL(((uint32)isb[BYTEN(bi[(n + 1) & 3], 3)]), 24) ^ \
	*(k + n))

#endif

static void crypto_gen_tabs() {

	uint32 i, t;
	uint8 p, q;

	/* log and power tables for GF(2**8) finite field with */
	/* 0x11b as modular polynomial - the simplest prmitive */
	/* root is 0x11, used here to generate the tables      */

	for(i = 0,p = 1; i < 256; ++i) {
		fexp[i] = (uint8)p;
		flog[p] = (uint8)i;
		p = p ^ (p << 1) ^ (p & 0x80 ? 0x01b : 0);
	}
	flog[1] = 0;

	p = 1;
	for(i = 0; i < 10; ++i) {
		rco[i] = p;
		p = (p << 1) ^ (p & 0x80 ? 0x1b : 0);
	}

	/* note that the affine byte transformation matrix in  */
	/* rijndael specification is in big endian format with */
	/* bit 0 as the most significant bit. In the remainder */
	/* of the specification the bits are numbered from the */
	/* least significant end of a byte.                    */

	for(i = 0; i < 256; ++i) {
		p = (i ? fexp[255 - flog[i]] : 0); q = p;
		q = (q >> 7) | (q << 1); p ^= q;
		q = (q >> 7) | (q << 1); p ^= q;
		q = (q >> 7) | (q << 1); p ^= q;
		q = (q >> 7) | (q << 1); p ^= q ^ 0x63;
		sbx[i] = (uint8)p;
		isb[p] = (uint8)i;
	}

	for(i = 0; i < 256; ++i) {
		p = sbx[i];

#ifdef LARGE_TABLES
		t = p;
		ftl[0][i] = t;
		ftl[1][i] = ROTL(t,  8);
		ftl[2][i] = ROTL(t, 16);
		ftl[3][i] = ROTL(t, 24);
#endif

		/* linear transform matrix f */
		/*         |2 3 1 1|         */
		/*         |1 2 3 1|         */
		/*         |1 1 2 3|         */
		/*         |3 1 1 2|         */
		t = ((uint32)FMUL(2, p)) |
			((uint32)p <<  8) |
			((uint32)p << 16) |
			((uint32)FMUL(3, p) << 24);

		ftn[0][i] = t;
		ftn[1][i] = ROTL(t,  8);
		ftn[2][i] = ROTL(t, 16);
		ftn[3][i] = ROTL(t, 24);

		p = isb[i];

#ifdef LARGE_TABLES
		t = p;
		itl[0][i] = t;
		itl[1][i] = ROTL(t,  8);
		itl[2][i] = ROTL(t, 16);
		itl[3][i] = ROTL(t, 24);
#endif

		/* inverse matrix of f       */
		/*         |E B D 9|         */
		/*         |9 E B D|         */
		/*         |D 9 E B|         */
		/*         |B D 9 E|         */
		t = ((uint32)FMUL(0xE, p)) |
			((uint32)FMUL(0x9, p) <<  8) |
			((uint32)FMUL(0xD, p) << 16) |
			((uint32)FMUL(0xB, p) << 24);

		itn[0][i] = t;
		itn[1][i] = ROTL(t,  8);
		itn[2][i] = ROTL(t, 16);
		itn[3][i] = ROTL(t, 24);
	}

	tab_gen = 1;
}

/* a smart way to calc mul(e, x) in finite field for each byte of word */
#define FMULX(e) ((((e)&0x7f7f7f7f) << 1) ^ ((((e)&0x80808080) >> 7) * 0x1b))
/* to calc a dkey from ekey */
#define IMIX(y,x) {     \
	u = FMULX(x);       \
	v = FMULX(u);       \
	w = FMULX(v);       \
	t = w ^ (x);        \
	(y)  = u ^ v ^ w;   \
	(y) ^=              \
		ROTR(u^t,  8) ^ \
		ROTR(v^t, 16) ^ \
		ROTR(  t, 24);  \
}

/* initialize the key schedule from the user supplied key */

/* one loop for Nk==4 */
#define LOOP4(i) {                             \
	t  = ROTR(t, 8);                           \
	t  = LSBX(t, 0) ^ rco[i];                  \
	t ^= ekey[4 * i + 0]; ekey[4 * i + 4] = t; \
	t ^= ekey[4 * i + 1]; ekey[4 * i + 5] = t; \
	t ^= ekey[4 * i + 2]; ekey[4 * i + 6] = t; \
	t ^= ekey[4 * i + 3]; ekey[4 * i + 7] = t; \
}

/* one loop for Nk==6 */
#define LOOP6(i) {                             \
	t  = ROTR(t, 8);                           \
	t  = LSBX(t, 0) ^ rco[i];                  \
	t ^= ekey[6 * i + 0]; ekey[6 * i + 6] = t; \
	t ^= ekey[6 * i + 1]; ekey[6 * i + 7] = t; \
	t ^= ekey[6 * i + 2]; ekey[6 * i + 8] = t; \
	t ^= ekey[6 * i + 3]; ekey[6 * i + 9] = t; \
	t ^= ekey[6 * i + 4]; ekey[6 * i +10] = t; \
	t ^= ekey[6 * i + 5]; ekey[6 * i +11] = t; \
}

/* one loop for Nk==8. when Nk>6, key schedule is different from Nk<=6! */
#define LOOP8(i) {                             \
	t  = ROTR(t, 8);                           \
	t  = LSBX(t, 0) ^ rco[i];                  \
	t ^= ekey[8 * i + 0]; ekey[8 * i + 8] = t; \
	t ^= ekey[8 * i + 1]; ekey[8 * i + 9] = t; \
	t ^= ekey[8 * i + 2]; ekey[8 * i +10] = t; \
	t ^= ekey[8 * i + 3]; ekey[8 * i +11] = t; \
	t  = LSBX(t, 0);/*Here is the difference*/ \
	t ^= ekey[8 * i + 4]; ekey[8 * i +12] = t; \
	t ^= ekey[8 * i + 5]; ekey[8 * i +13] = t; \
	t ^= ekey[8 * i + 6]; ekey[8 * i +14] = t; \
	t ^= ekey[8 * i + 7]; ekey[8 * i +15] = t; \
}

AES_ctx *crypto_aes_set_key(AES_ctx *ctx, const void *pk, uint32 klen, uint32 enc_only) {

	uint32 i, t, u, v, w;
	uint32 *ekey = ctx->ekey;
	uint32 *dkey = ctx->dkey;
	const uint32 *in_key = (const uint32 *)pk;

	ctx->decrypt = !enc_only;

	if(!tab_gen)
		crypto_gen_tabs();

	ctx->klen = (klen + 31) / 32;

	COPY_U32(ekey+0, in_key+0); ekey[0] = IOSWAP(ekey[0]);
	COPY_U32(ekey+1, in_key+1); ekey[1] = IOSWAP(ekey[1]);
	COPY_U32(ekey+2, in_key+2); ekey[2] = IOSWAP(ekey[2]);
	COPY_U32(ekey+3, in_key+3); ekey[3] = IOSWAP(ekey[3]);

	if(4 == ctx->klen) {
		t = ekey[3];
		for(i = 0; i < 10; ++i) LOOP4(i);
		goto set_dec_key;
	}

	COPY_U32(ekey+4, in_key+4); ekey[4] = IOSWAP(ekey[4]);
	COPY_U32(ekey+5, in_key+5); ekey[5] = IOSWAP(ekey[5]);

	if(6 == ctx->klen) {
		t = ekey[5];
		for(i = 0; i < 8; ++i) LOOP6(i);
		goto set_dec_key;
	}

	COPY_U32(ekey+6, in_key+6); ekey[6] = IOSWAP(ekey[6]);
	COPY_U32(ekey+7, in_key+7); ekey[7] = IOSWAP(ekey[7]);

	if(8 == ctx->klen) {
		t = ekey[7];
		for(i = 0; i < 7; ++i) LOOP8(i);
		goto set_dec_key;
	}

set_dec_key:
	/* if not encrypt only */
	if (ctx->decrypt) {
		dkey[0] = ekey[0];
		dkey[1] = ekey[1];
		dkey[2] = ekey[2];
		dkey[3] = ekey[3];

		for(i = 4; i < 4*ctx->klen + 24; ++i) {
			IMIX(dkey[i], ekey[i]);
		}

		dkey[4*ctx->klen + 24] = ekey[4*ctx->klen + 24];
		dkey[4*ctx->klen + 25] = ekey[4*ctx->klen + 25];
		dkey[4*ctx->klen + 26] = ekey[4*ctx->klen + 26];
		dkey[4*ctx->klen + 27] = ekey[4*ctx->klen + 27];
	}

	return ctx;
}

/* encrypt a block of text */
/* bo: block out, bi: block in, k: pointer to current round key */
#define FROUNDN(bo, bi, k) \
	FRN(bo, bi, 0, k);     \
	FRN(bo, bi, 1, k);     \
	FRN(bo, bi, 2, k);     \
	FRN(bo, bi, 3, k);     \
	k += 4

#define FROUNDL(bo, bi, k) \
	FRL(bo, bi, 0, k);     \
	FRL(bo, bi, 1, k);     \
	FRL(bo, bi, 2, k);     \
	FRL(bo, bi, 3, k)

void crypto_aes_encrypt(const AES_ctx *ctx, const void *pi, void *po) {
	uint32 b0[4], b1[4];
	const uint32 *kp = ctx->ekey;
	const uint32 *iblk = (const uint32 *)pi;
	uint32 *oblk = (uint32 *)po;

	COPY_U32(b0+0, iblk+0); b0[0] = IOSWAP(b0[0]) ^ *(kp+0);
	COPY_U32(b0+1, iblk+1); b0[1] = IOSWAP(b0[1]) ^ *(kp+1);
	COPY_U32(b0+2, iblk+2); b0[2] = IOSWAP(b0[2]) ^ *(kp+2);
	COPY_U32(b0+3, iblk+3); b0[3] = IOSWAP(b0[3]) ^ *(kp+3);

	kp += 4;

	if(ctx->klen > 6) {
		FROUNDN(b1, b0, kp); FROUNDN(b0, b1, kp);
	}

	if(ctx->klen > 4) {
		FROUNDN(b1, b0, kp); FROUNDN(b0, b1, kp);
	}

	FROUNDN(b1, b0, kp); FROUNDN(b0, b1, kp);
	FROUNDN(b1, b0, kp); FROUNDN(b0, b1, kp);
	FROUNDN(b1, b0, kp); FROUNDN(b0, b1, kp);
	FROUNDN(b1, b0, kp); FROUNDN(b0, b1, kp);
	FROUNDN(b1, b0, kp); FROUNDL(b0, b1, kp);

	b0[0] = IOSWAP(b0[0]); COPY_U32(oblk+0, b0+0);
	b0[1] = IOSWAP(b0[1]); COPY_U32(oblk+1, b0+1);
	b0[2] = IOSWAP(b0[2]); COPY_U32(oblk+2, b0+2);
	b0[3] = IOSWAP(b0[3]); COPY_U32(oblk+3, b0+3);
}

/* decrypt a block of text */
/* bo: block out, bi: block in, k: pointer to current round key */
#define IROUNDN(bo, bi, k) \
	IRN(bo, bi, 0, k);     \
	IRN(bo, bi, 1, k);     \
	IRN(bo, bi, 2, k);     \
	IRN(bo, bi, 3, k);     \
	k -= 4

#define IROUNDL(bo, bi, k) \
	IRL(bo, bi, 0, k);     \
	IRL(bo, bi, 1, k);     \
	IRL(bo, bi, 2, k);     \
	IRL(bo, bi, 3, k)

void crypto_aes_decrypt(const AES_ctx *ctx, const void *pi, void *po) {
	uint32 b0[4], b1[4];
	const uint32 *kp = ctx->dkey + 4*ctx->klen + 24;
	const uint32 *iblk = (const uint32 *)pi;
	uint32 *oblk = (uint32 *)po;

	COPY_U32(b0+0, iblk+0); b0[0] = IOSWAP(b0[0]) ^ *(kp+0);
	COPY_U32(b0+1, iblk+1); b0[1] = IOSWAP(b0[1]) ^ *(kp+1);
	COPY_U32(b0+2, iblk+2); b0[2] = IOSWAP(b0[2]) ^ *(kp+2);
	COPY_U32(b0+3, iblk+3); b0[3] = IOSWAP(b0[3]) ^ *(kp+3);

	kp -= 4;

	if(ctx->klen > 6) {
		IROUNDN(b1, b0, kp); IROUNDN(b0, b1, kp);
	}

	if(ctx->klen > 4) {
		IROUNDN(b1, b0, kp); IROUNDN(b0, b1, kp);
	}

	IROUNDN(b1, b0, kp); IROUNDN(b0, b1, kp);
	IROUNDN(b1, b0, kp); IROUNDN(b0, b1, kp);
	IROUNDN(b1, b0, kp); IROUNDN(b0, b1, kp);
	IROUNDN(b1, b0, kp); IROUNDN(b0, b1, kp);
	IROUNDN(b1, b0, kp); IROUNDL(b0, b1, kp);

	b0[0] = IOSWAP(b0[0]); COPY_U32(oblk+0, b0+0);
	b0[1] = IOSWAP(b0[1]); COPY_U32(oblk+1, b0+1);
	b0[2] = IOSWAP(b0[2]); COPY_U32(oblk+2, b0+2);
	b0[3] = IOSWAP(b0[3]); COPY_U32(oblk+3, b0+3);
}

