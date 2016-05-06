#ifndef __RSANN_H__
#define __RSANN_H__
#include "security_types.h"
/* Constants.
   Note: MAX_NN_DIGITS is long enough to hold any RSA modulus, plus
   one more digit as required by R_GeneratePEMKeys (for n and phiN,
   whose lengths must be even). All natural numbers have at most
   MAX_NN_DIGITS digits, except for double-length intermediate values
   in NN_Mult (t), NN_ModMult (t), NN_ModInv (w), and NN_Div (c).
 */
/* Length of digit in bits */
#define NN_DIGIT_BITS 32
#define NN_HALF_DIGIT_BITS 16
/* Length of digit in bytes */
#define NN_DIGIT_LEN (NN_DIGIT_BITS / 8)
/* Maximum length in digits */
#define MAX_NN_DIGITS \
  ((MAX_RSA_MODULUS_LEN + NN_DIGIT_LEN - 1) / NN_DIGIT_LEN + 1)
/* Maximum digits */
#define MAX_NN_DIGIT 0xffffffff
#define MAX_NN_HALF_DIGIT 0xffff


#define LOW_HALF(x) ((x) & MAX_NN_HALF_DIGIT)
#define HIGH_HALF(x) (((x) >> NN_HALF_DIGIT_BITS) & MAX_NN_HALF_DIGIT)
#define TO_HIGH_HALF(x) (((uint32)(x)) << NN_HALF_DIGIT_BITS)
#define DIGIT_MSB(x) (uint16)(((x) >> (NN_DIGIT_BITS - 1)) & 1)
#define DIGIT_2MSB(x) (uint16)(((x) >> (NN_DIGIT_BITS - 2)) & 3)

void nn_digit_mult(uint32 a[2], uint32 b, uint32 c);
void nn_digit_div(uint32 *a, uint32 b[2], uint32 c);
void nn_decode (uint32 *a, uint16 digits, uint8 *b, uint16 len);
void nn_encode(uint8 *a, uint16 len, uint32 *b, uint16 digits);
void nn_assign(uint32 *a, uint32 *b, uint16 digits);
void nn_assign_zero(uint32 *a, uint16 digits);
void nn_assign2_exp(uint32 *a, uint16 b, uint16 digits);
uint32 nn_add(uint32 *a, uint32 *b, uint32 *c, uint16 digits);
uint32 nn_sub(uint32 *a, uint32 *b, uint32 *c, uint16 digits);
void nn_mult(uint32 *a, uint32 *b, uint32 *c, uint16 digits);
uint32 nn_lshift(uint32 *a, uint32 *b, uint16 c, uint16 digits);
uint32 nn_rshift(uint32 *a, uint32 *b, uint16 c, uint16 digits);
void nn_div(uint32 *a, uint32 *b, uint32 *c, uint16 cdigits, uint32 *d, uint16 ddigits);
void nn_mod(uint32 *a, uint32 *b, uint16 bdigits, uint32 *c, uint16 cdigits);
void nn_mod_mult(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint16 digits);
void nn_mod_exp(uint32 *a, uint32 *b, uint32 *c, uint16 cdigits, uint32 *d, uint16 ddigits);
void nn_mod_inv(uint32 *a, uint32 *b, uint32 *c, uint16 digits);
void nn_gcd(uint32 *a, uint32 *b, uint32 *c, uint16 digits);
uint16 nn_digits(uint32 *a, uint16 digits);
int16 nn_cmp(uint32 *a, uint32 *b, uint16 digits);
int16 nn_zero(uint32 *a, uint16 digits);
uint16 nn_bits(uint32 *a, uint16 digits);

#define NN_ASSIGN_DIGIT(a, b, digits) {nn_assign_zero (a, digits); a[0] = b;}
#define NN_EQUAL(a, b, digits) (! nn_cmp (a, b, digits))
#define NN_EVEN(a, digits) (((digits) == 0) || ! (a[0] & 1))


#endif

