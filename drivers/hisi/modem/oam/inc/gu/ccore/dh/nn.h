/* NN.H - header file for NN.C
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */


/* Constants.

   Note: MAX_DIGITS_LEN is long enough to hold any RSA modulus, plus
   one more digit as required by R_GeneratePEMKeys (for n and phiN,
   whose lengths must be even). All natural numbers have at most
   MAX_DIGITS_LEN digits, except for double-length intermediate values
   in BIGNUM_Mult (t), BIGNUM_ModMult (t), BIGNUM_ModInv (w), and BIGNUM_Div (c).
 */
/* Length of digit in bits */
#define DIGIT_BITS 32
#define HALF_DIGIT_BITS 16
/* Length of digit in bytes */
#define DIGIT_LEN (DIGIT_BITS / 8)
/* Maximum length in digits */
#define MAX_DIGITS_LEN \
  ((MAX_MODULUS_LEN + DIGIT_LEN - 1) / DIGIT_LEN + 1)
/* Maximum digits */
#define MAX_DIGIT 0xffffffff
#define MAX_HALF_DIGIT 0xffff

/* Macros.
 */
#define LOW_HALF(x) ((x) & MAX_HALF_DIGIT)
#define HIGH_HALF(x) (((x) >> HALF_DIGIT_BITS) & MAX_HALF_DIGIT)
#define TO_HIGH_HALF(x) (((UINT4)(x)) << HALF_DIGIT_BITS)
#define DIGIT_MSB(x) (unsigned int)(((x) >> (DIGIT_BITS - 1)) & 1)
#define DIGIT_2MSB(x) (unsigned int)(((x) >> (DIGIT_BITS - 2)) & 3)

void BIGNUM_Decode(UINT4 *, unsigned int, unsigned char *, unsigned int);
void BIGNUM_Encode PROTO_LIST
  ((unsigned char *, unsigned int, UINT4 *, unsigned int));

void BIGNUM_Assign (UINT4 *, UINT4 *, unsigned int);
void BIGNUM_AssignZero (UINT4 *, unsigned int);
void BIGNUM_Assign2Exp (UINT4 *, unsigned int, unsigned int);

UINT4 BIGNUM_Add (UINT4 *, UINT4 *, UINT4 *, unsigned int);
UINT4 BIGNUM_Sub (UINT4 *, UINT4 *, UINT4 *, unsigned int);
void BIGNUM_Mult (UINT4 *, UINT4 *, UINT4 *, unsigned int);
void BIGNUM_Div (UINT4 *, UINT4 *, UINT4 *, unsigned int, UINT4 *, unsigned int);
UINT4 BIGNUM_LShift (UINT4 *, UINT4 *, unsigned int, unsigned int);
UINT4 BIGNUM_RShift (UINT4 *, UINT4 *, unsigned int, unsigned int);

void BIGNUM_Mod (UINT4 *, UINT4 *, unsigned int, UINT4 *, unsigned int);
void BIGNUM_ModMult (UINT4 *, UINT4 *, UINT4 *, UINT4 *, unsigned int);
void BIGNUM_ModExp (UINT4 *, UINT4 *, UINT4 *, unsigned int, UINT4 *, unsigned int);
void BIGNUM_ModInv (UINT4 *, UINT4 *, UINT4 *, unsigned int);
void NN_Gcd PROTO_LIST ((UINT4 *, UINT4 *, UINT4 *, unsigned int));

int BIGNUM_Cmp (UINT4 *, UINT4 *, unsigned int);
int BIGNUM_Zero (UINT4 *, unsigned int);
unsigned int BIGNUM_Bits (UINT4 *, unsigned int);
unsigned int BIGNUM_Digits (UINT4 *, unsigned int);

#define BIGNUM_ASSIGN_DIGIT(a, b, digits) {BIGNUM_AssignZero (a, digits); a[0] = b;}

