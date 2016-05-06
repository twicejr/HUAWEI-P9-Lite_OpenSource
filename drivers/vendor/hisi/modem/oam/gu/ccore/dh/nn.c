/* NN.C - natural numbers routines
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

#include "softcrypto.h"
#include "nn.h"
/*lint -e553 */
#if (VOS_WIN32 == VOS_OS_VER)
#include "memory.h"
#endif
/*lint +e553 */

#include "product_config.h"

/*lint -e701 -e702 -e732 -e734 -e713 -e737 -e734*/

#if (FEATURE_VSIM == FEATURE_ON)
static UINT4 BIGNUM_AddDigitMult (UINT4 *, UINT4 *, UINT4, UINT4 *, unsigned int);
static UINT4 BIGNUM_SubDigitMult (UINT4 *, UINT4 *, UINT4, UINT4 *, unsigned int);

static void BIGNUM_DigitMult (UINT4 a[2], UINT4 b, UINT4 c);
static void BIGNUM_DigitDiv (UINT4 *a, UINT4 b[2], UINT4 c);

static unsigned int NN_DigitBits PROTO_LIST ((UINT4));

void BIGNUM_Decode (UINT4 *a, unsigned int digits, unsigned char *b, unsigned int len)
{
  UINT4 t;
  int j;
  unsigned int i, u;

  for (i = 0, j = len - 1; i < digits && j >= 0; i++) {
    t = 0;
    for (u = 0; j >= 0 && u < DIGIT_BITS; j--, u += 8)
      t |= ((UINT4)b[j]) << u;
    a[i] = t;
  }

  for (; i < digits; i++)
    a[i] = 0;
}

void BIGNUM_Encode (unsigned char *a, unsigned int len, UINT4 *b, unsigned int digits)
{
  UINT4 t;
  int j;
  unsigned int i, u;

  for (i = 0, j = len - 1; i < digits && j >= 0; i++) {
    t = b[i];
    for (u = 0; j >= 0 && u < DIGIT_BITS; j--, u += 8)
      a[j] = (unsigned char)(t >> u);
  }

  for (; j >= 0; j--)
    a[j] = 0;
}

void BIGNUM_Assign (UINT4 *a, UINT4 *b, unsigned int digits)
{
  unsigned int i;

  for (i = 0; i < digits; i++)
    a[i] = b[i];
}

void BIGNUM_AssignZero (UINT4 *a, unsigned int digits)
{
  unsigned int i;

  for (i = 0; i < digits; i++)
    a[i] = 0;
}

UINT4 BIGNUM_Add (UINT4 *a, UINT4 *b, UINT4 *c, unsigned int digits)
{
  UINT4 ai, carry;
  unsigned int i;

  carry = 0;

  for (i = 0; i < digits; i++) {
    if ((ai = b[i] + carry) < carry)
      ai = c[i];
    else if ((ai += c[i]) < c[i])
      carry = 1;
    else
      carry = 0;
    a[i] = ai;
  }

  return (carry);
}

UINT4 BIGNUM_Sub (UINT4 *a, UINT4 *b, UINT4 *c, unsigned int digits)
{
  UINT4 ai, borrow;
  unsigned int i;

  borrow = 0;

  for (i = 0; i < digits; i++) {
    if ((ai = b[i] - borrow) > (MAX_DIGIT - borrow))
      ai = MAX_DIGIT - c[i];
    else if ((ai -= c[i]) > (MAX_DIGIT - c[i]))
      borrow = 1;
    else
      borrow = 0;
    a[i] = ai;
  }

  return (borrow);
}

void BIGNUM_Mult (UINT4 *a, UINT4 *b, UINT4 *c, unsigned int digits)
{
  UINT4 t[2*MAX_DIGITS_LEN];
  unsigned int bDigits, cDigits, i;

  BIGNUM_AssignZero (t, 2 * digits);

  bDigits = BIGNUM_Digits (b, digits);
  cDigits = BIGNUM_Digits (c, digits);

  for (i = 0; i < bDigits; i++)
    t[i+cDigits] += BIGNUM_AddDigitMult (&t[i], &t[i], b[i], c, cDigits);

  BIGNUM_Assign (a, t, 2 * digits);

}

UINT4 BIGNUM_LShift (UINT4 *a, UINT4 *b, unsigned int c, unsigned int digits)
{
  UINT4 bi, carry;
  unsigned int i, t;

  if (c >= DIGIT_BITS)
    return (0);

  t = DIGIT_BITS - c;

  carry = 0;

  for (i = 0; i < digits; i++) {
    bi = b[i];
    a[i] = (bi << c) | carry;
    carry = c ? (bi >> t) : 0;
  }

  return (carry);
}

UINT4 BIGNUM_RShift (UINT4 *a, UINT4 *b, unsigned int c, unsigned int digits)
{
  UINT4 bi, carry;
  int i;
  unsigned int t;

  if (c >= DIGIT_BITS)
    return (0);

  t = DIGIT_BITS - c;

  carry = 0;

  for (i = digits - 1; i >= 0; i--) {
    bi = b[i];
    a[i] = (bi >> c) | carry;
    carry = c ? (bi << t) : 0;
  }

  return (carry);
}

void BIGNUM_Div (UINT4 *a, UINT4 *b, UINT4 *c, unsigned int cDigits, UINT4 *d, unsigned int dDigits)
{
  UINT4 ai, cc[2*MAX_DIGITS_LEN+1], dd[MAX_DIGITS_LEN], t;
  int i;
  unsigned int ddDigits, shift;

  ddDigits = BIGNUM_Digits (d, dDigits);
  if (ddDigits == 0)
    return;

  shift = DIGIT_BITS - NN_DigitBits (d[ddDigits-1]);
  BIGNUM_AssignZero (cc, ddDigits);
  cc[cDigits] = BIGNUM_LShift (cc, c, shift, cDigits);
  BIGNUM_LShift (dd, d, shift, ddDigits);
  t = dd[ddDigits-1];

  BIGNUM_AssignZero (a, cDigits);

  for (i = cDigits-ddDigits; i >= 0; i--) {
    if (t == MAX_DIGIT)
      ai = cc[i+ddDigits];
    else
      BIGNUM_DigitDiv (&ai, &cc[i+ddDigits-1], t + 1);
    cc[i+ddDigits] -= BIGNUM_SubDigitMult (&cc[i], &cc[i], ai, dd, ddDigits);

    /* Correct estimate.
     */
    while (cc[i+ddDigits] || (BIGNUM_Cmp (&cc[i], dd, ddDigits) >= 0)) {
      ai++;
      cc[i+ddDigits] -= BIGNUM_Sub (&cc[i], &cc[i], dd, ddDigits);
    }

    a[i] = ai;
  }


  BIGNUM_AssignZero (b, dDigits);
  BIGNUM_RShift (b, cc, shift, ddDigits);

}

void BIGNUM_Mod (UINT4 *a, UINT4 *b, unsigned int bDigits, UINT4 *c, unsigned int cDigits)
{
  UINT4 t[2 * MAX_DIGITS_LEN];

  BIGNUM_Div (t, a, b, bDigits, c, cDigits);

}

void BIGNUM_ModMult (UINT4 *a, UINT4 *b, UINT4 *c, UINT4 *d, unsigned int digits)
{
  UINT4 t[2*MAX_DIGITS_LEN];

  BIGNUM_Mult (t, b, c, digits);
  BIGNUM_Mod (a, t, 2 * digits, d, digits);
}

void BIGNUM_ModExp (UINT4 *a, UINT4 *b, UINT4 *c, unsigned int cDigits, UINT4 *d, unsigned int dDigits)
{
  UINT4 bPower[3][MAX_DIGITS_LEN], ci, t[MAX_DIGITS_LEN];
  int i;
  unsigned int ciBits, j, s;

  BIGNUM_Assign (bPower[0], b, dDigits);
  BIGNUM_ModMult (bPower[1], bPower[0], b, d, dDigits);
  BIGNUM_ModMult (bPower[2], bPower[1], b, d, dDigits);

  BIGNUM_ASSIGN_DIGIT (t, 1, dDigits);

  cDigits = BIGNUM_Digits (c, cDigits);
  for (i = cDigits - 1; i >= 0; i--) {
    ci = c[i];
    ciBits = DIGIT_BITS;

    /* Scan past leading zero bits of most significant digit.
     */
    if (i == (int)(cDigits - 1)) {
      while (! DIGIT_2MSB (ci)) {
        ci <<= 2;
        ciBits -= 2;
      }
    }

    for (j = 0; j < ciBits; j += 2, ci <<= 2) {
      /* Compute t = t^4 * b^s mod d, where s = two MSB's of ci.
       */
      BIGNUM_ModMult (t, t, t, d, dDigits);
      BIGNUM_ModMult (t, t, t, d, dDigits);
      if ((s = DIGIT_2MSB (ci)) != 0)
        BIGNUM_ModMult (t, t, bPower[s-1], d, dDigits);
    }
  }

  BIGNUM_Assign (a, t, dDigits);

}

int BIGNUM_Cmp (UINT4 *a, UINT4 *b, unsigned int digits)
{
  int i;

  for (i = digits - 1; i >= 0; i--) {
    if (a[i] > b[i])
      return (1);
    if (a[i] < b[i])
      return (-1);
  }

  return (0);
}

int BIGNUM_Zero (UINT4 *a, unsigned int digits)
{
  unsigned int i;

  for (i = 0; i < digits; i++)
    if (a[i])
      return (0);

  return (1);
}

unsigned int BIGNUM_Digits (UINT4 *a, unsigned int digits)
{
  int i;

  for (i = digits - 1; i >= 0; i--)
    if (a[i])
      break;

  return (unsigned int)(i + 1);
}

UINT4 BIGNUM_AddDigitMult (UINT4 *a, UINT4 *b, UINT4 c, UINT4 *d, unsigned int digits)
{
  UINT4 carry, t[2];
  unsigned int i;

  if (c == 0)
    return (0);

  carry = 0;
  for (i = 0; i < digits; i++) {
    BIGNUM_DigitMult (t, c, d[i]);
    if ((a[i] = b[i] + carry) < carry)
      carry = 1;
    else
      carry = 0;
    if ((a[i] += t[0]) < t[0])
      carry++;
    carry += t[1];
  }

  return (carry);
}

UINT4 BIGNUM_SubDigitMult (UINT4 *a, UINT4 *b, UINT4 c, UINT4 *d, unsigned int digits)
{
  UINT4 borrow, t[2];
  unsigned int i;

  if (c == 0)
    return (0);

  borrow = 0;
  for (i = 0; i < digits; i++) {
    BIGNUM_DigitMult (t, c, d[i]);
    if ((a[i] = b[i] - borrow) > (MAX_DIGIT - borrow))
      borrow = 1;
    else
      borrow = 0;
    if ((a[i] -= t[0]) > (MAX_DIGIT - t[0]))
      borrow++;
    borrow += t[1];
  }

  return (borrow);
}

static unsigned int NN_DigitBits (UINT4 a)
{
  unsigned int i;

  for (i = 0; i < DIGIT_BITS; i++, a >>= 1)
    if (a == 0)
      break;

  return (i);
}

/* Computes a = b * c, where b and c are digits.

   Lengths: a[2].
 */
void BIGNUM_DigitMult (UINT4 a[2], UINT4 b, UINT4 c)
{
  UINT4 t, u;
  UINT2 bHigh, bLow, cHigh, cLow;

  bHigh = (UINT2)HIGH_HALF (b);
  bLow = (UINT2)LOW_HALF (b);
  cHigh = (UINT2)HIGH_HALF (c);
  cLow = (UINT2)LOW_HALF (c);

  a[0] = (UINT4)bLow * (UINT4)cLow;
  t = (UINT4)bLow * (UINT4)cHigh;
  u = (UINT4)bHigh * (UINT4)cLow;
  a[1] = (UINT4)bHigh * (UINT4)cHigh;

  if ((t += u) < u)
    a[1] += TO_HIGH_HALF (1);
  u = TO_HIGH_HALF (t);

  if ((a[0] += u) < u)
    a[1]++;
  a[1] += HIGH_HALF (t);
}

/* Sets a = b / c, where a and c are digits.

   Lengths: b[2].
   Assumes b[1] < c and HIGH_HALF (c) > 0. For efficiency, c should be
   normalized.
 */
void BIGNUM_DigitDiv (UINT4 *a, UINT4 b[2], UINT4 c)
{
  UINT4 t[2], u, v;
  UINT2 aHigh, aLow, cHigh, cLow;

  cHigh = (UINT2)HIGH_HALF (c);
  cLow = (UINT2)LOW_HALF (c);

  t[0] = b[0];
  t[1] = b[1];

  /* Underestimate high half of quotient and subtract.
   */
  if (cHigh == MAX_HALF_DIGIT)
    aHigh = (UINT2)HIGH_HALF (t[1]);
  else
    aHigh = (UINT2)(t[1] / (cHigh + 1));
  u = (UINT4)aHigh * (UINT4)cLow;
  v = (UINT4)aHigh * (UINT4)cHigh;
  if ((t[0] -= TO_HIGH_HALF (u)) > (MAX_DIGIT - TO_HIGH_HALF (u)))
    t[1]--;
  t[1] -= HIGH_HALF (u);
  t[1] -= v;

  /* Correct estimate.
   */
  while ((t[1] > cHigh) ||
         ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF (cLow)))) {
    if ((t[0] -= TO_HIGH_HALF (cLow)) > MAX_DIGIT - TO_HIGH_HALF (cLow))
      t[1]--;
    t[1] -= cHigh;
    aHigh++;
  }

  /* Underestimate low half of quotient and subtract.
   */
  if (cHigh == MAX_HALF_DIGIT)
    aLow = (UINT2)LOW_HALF (t[1]);
  else
    aLow =
      (UINT2)((TO_HIGH_HALF (t[1]) + HIGH_HALF (t[0])) / (cHigh + 1));
  u = (UINT4)aLow * (UINT4)cLow;
  v = (UINT4)aLow * (UINT4)cHigh;
  if ((t[0] -= u) > (MAX_DIGIT - u))
    t[1]--;
  if ((t[0] -= TO_HIGH_HALF (v)) > (MAX_DIGIT - TO_HIGH_HALF (v)))
    t[1]--;
  t[1] -= HIGH_HALF (v);

  /* Correct estimate.
   */
  while ((t[1] > 0) || ((t[1] == 0) && t[0] >= c)) {
    if ((t[0] -= c) > (MAX_DIGIT - c))
      t[1]--;
    aLow++;
  }

  *a = TO_HIGH_HALF (aHigh) + aLow;
}
#endif

/*lint +e701 +e702 +e732 +e734 +e713 +e737 +e734*/
