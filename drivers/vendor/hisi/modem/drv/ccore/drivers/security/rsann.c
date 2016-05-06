/*   natural numbers routines  */

//#include "config.h"
#include "string.h"
#include "securec.h"
#include "rsann.h"
#include "rsa.h"

/*lint --e{534, 539, 734, 830} */
static uint32 nn_add_digit_mult(uint32 *a, uint32 *b, uint32 c, uint32 *d, uint16 digits);
static uint32 nn_sub_digit_mult(uint32 *a, uint32 *b, uint32 c, uint32 *d, uint16 digits);
static uint16 nn_digit_bits(uint32 a);


/* Computes a = b * c, where b and c are digits. Lengths: a[2].  */
void nn_digit_mult(uint32 a[2], uint32 b, uint32 c)
{
  uint32 t, u;
  uint16 bHigh, bLow, cHigh, cLow;

  bHigh = (uint16)HIGH_HALF (b);
  bLow = (uint16)LOW_HALF (b);
  cHigh = (uint16)HIGH_HALF (c);
  cLow = (uint16)LOW_HALF (c);

  a[0] = (uint32)bLow * (uint32)cLow;
  t = (uint32)bLow * (uint32)cHigh;
  u = (uint32)bHigh * (uint32)cLow;
  a[1] = (uint32)bHigh * (uint32)cHigh;
  
  if ((t += u) < u)
  {
    a[1] += TO_HIGH_HALF (1);
  }
  u = TO_HIGH_HALF (t);

  if ((a[0] += u) < u)
    a[1]++;
  a[1] += HIGH_HALF (t);
}


/* Sets a = b / c, where a and c are digits.   Lengths: b[2].
Assumes b[1] < c and HIGH_HALF (c) > 0. For efficiency, c should be   normalized. */
void nn_digit_div(uint32 *a, uint32 b[2], uint32 c)
{
  uint32 t[2], u, v;
  uint16 aHigh, aLow, cHigh, cLow;

  cHigh = (uint16)HIGH_HALF (c);
  cLow = (uint16)LOW_HALF (c);

  t[0] = b[0];
  t[1] = b[1];

  /* Underestimate high half of quotient and subtract. */
  if (cHigh == MAX_NN_HALF_DIGIT)
  {
    aHigh = (uint16)HIGH_HALF (t[1]);
  }
  else
  {
    aHigh = (uint16)(t[1] / (cHigh + 1));
  }
  u = (uint32)aHigh * (uint32)cLow;
  v = (uint32)aHigh * (uint32)cHigh;
  if ((t[0] -= TO_HIGH_HALF (u)) > (MAX_NN_DIGIT - TO_HIGH_HALF (u)))
  {
    t[1]--;
  }
  t[1] -= HIGH_HALF (u);
  t[1] -= v;

  /* Correct estimate.  */
  while ((t[1] > cHigh) || ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF (cLow)))) 
  {
    //printf("CE\n");
    if ((t[0] -= TO_HIGH_HALF (cLow)) > MAX_NN_DIGIT - TO_HIGH_HALF (cLow))
    {
      t[1]--;
    }
    t[1] -= cHigh;
    aHigh++;
  }
  //printf("Correct estimate. \n");
  /* Underestimate low half of quotient and subtract. */
  if (cHigh == MAX_NN_HALF_DIGIT)
  {
    aLow = (uint16)LOW_HALF (t[1]);
  }
  else
  {
    aLow =  (uint16)((TO_HIGH_HALF (t[1]) + HIGH_HALF (t[0])) / (cHigh + 1));
  }
  u = (uint32)aLow * (uint32)cLow;
  v = (uint32)aLow * (uint32)cHigh;
  if ((t[0] -= u) > (MAX_NN_DIGIT - u))
  {
    t[1]--;
  }
  if ((t[0] -= TO_HIGH_HALF (v)) > (MAX_NN_DIGIT - TO_HIGH_HALF (v)))
  {
    t[1]--;
  }
  t[1] -= HIGH_HALF (v);

  /* Correct estimate. */
  while ((t[1] > 0) || ((t[1] == 0) && t[0] >= c)) 
  {
  //printf("t[1] = %u t[0] = %u c = %u\n", t[1], t[0], c);
    if ((t[0] -= c) > (MAX_NN_DIGIT - c))
    {
      t[1]--;
    }
    aLow++;
  }
  
  *a = TO_HIGH_HALF (aHigh) + aLow;
}


 /* Decodes character string b into a, where character string is ordered from most to least significant.
   Lengths: a[digits], b[len]. Assumes b[i] = 0 for i < len - digits * NN_DIGIT_LEN. (Otherwise most significant bytes are truncated.)
 */
void nn_decode(uint32 *a, uint16 digits, uint8 *b, uint16 len)
{
  uint32 t;
  int16 j;
  int16 i, u;

  for (i = 0, j = len - 1; i < digits && j >= 0; i++) 
  {
    t = 0;
    for (u = 0; j >= 0 && u < NN_DIGIT_BITS; j--, u += 8)
    {
      t |= ((uint32)b[j]) << u;
    }
    a[i] = t;
  }
  
  for (; i < digits; i++)
  {
    a[i] = 0;
  }
}

/* Encodes b into character string a, where character string is ordered from most to least significant.
   Lengths: a[len], b[digits]. Assumes NN_Bits (b, digits) <= 8 * len. (Otherwise most significant digits are truncated.)
 */
void nn_encode(uint8 *a, uint16 len, uint32 *b, uint16 digits)
{
  uint32 t;
  int16 j;
  uint16 i, u;
//printf("nn_encode \n");
  for (i = 0, j = len - 1; i < digits && j >= 0; i++) 
  {
    t = b[i];
    for (u = 0; j >= 0 && u < NN_DIGIT_BITS; j--, u += 8)
    {
      a[j] = (uint8)(t >> u);
    }
  }

  for (; j >= 0; j--)
  {
    a[j] = 0;
  }
}

/* Assigns a = b. Lengths: a[digits], b[digits].  */

void nn_assign(uint32 *a, uint32 *b, uint16 digits)
{
  uint16 i;

  for(i=0; i<digits; i++)
  {
    a[i] = b[i];
  }
}

/* Assigns a = 0. Lengths: a[digits].  */
void nn_assign_zero(uint32 *a, uint16 digits)
{
  uint16 i;

  for(i=0; i<digits; i++)
  {
    a[i] = 0;
  }
}


/* Assigns a = 2^b. Lengths: a[digits]. Requires b < digits * NN_DIGIT_BITS.  */
void nn_assign2_exp(uint32 *a, uint16 b, uint16 digits)
{
  nn_assign_zero(a, digits);
  if(b >= digits * NN_DIGIT_BITS)
  {
    return;
  }
  a[b / NN_DIGIT_BITS] = (uint32)1 << (b % NN_DIGIT_BITS);
}

/* Computes a = b + c. Returns carry. Lengths: a[digits], b[digits], c[digits]. */
uint32 nn_add(uint32 *a, uint32 *b, uint32 *c, uint16 digits)
{
  uint32 ai, carry;
  int16 i;

  carry = 0;
  for(i = 0; i < digits; i++)
  {
    if((ai = b[i] + carry) < carry)
    {
      ai = c[i];
    }
    else if((ai += c[i]) < c[i])
    {
      carry = 1;
    }
    else
    {
      carry = 0;
    }
    a[i] = ai;
  }
  return carry;
}


/* Computes a = b - c. Returns borrow. Lengths: a[digits], b[digits], c[digits]. */
uint32 nn_sub(uint32 *a, uint32 *b, uint32 *c, uint16 digits)
{
  uint32 ai, borrow;
  int16 i;

  borrow = 0;
  for (i = 0; i < digits; i++) 
  {
    if ((ai = b[i] - borrow) > (MAX_NN_DIGIT - borrow))
    {
      ai = MAX_NN_DIGIT - c[i];
    }
    else if ((ai -= c[i]) > (MAX_NN_DIGIT - c[i]))
    {
      borrow = 1;
    }
    else
    {
      borrow = 0;
    }
    a[i] = ai;
  }
  return borrow;	
}

/* Computes a = b * c. Lengths: a[2*digits], b[digits], c[digits]. Assumes digits < MAX_NN_DIGITS. */
void nn_mult(uint32 *a, uint32 *b, uint32 *c, uint16 digits)
{
  uint32 t[2 * MAX_NN_DIGITS];
  int16 bdigits, cdigits, i;

  memset_s (t,sizeof (t), 0, sizeof (t));

  nn_assign_zero(t, (uint16)(2*digits));
  bdigits = (int16)nn_digits (b, digits);
  cdigits = (int16)nn_digits (c, digits);

  for (i = 0; i < bdigits; i++)
  {
    t[i+cdigits] += nn_add_digit_mult (&t[i], &t[i], b[i], c, (uint16)cdigits);
  }
  
  nn_assign (a, t, (uint16)(2 * digits));
}


/* Computes a = b * 2^c (i.e., shifts left c bits), returning carry. Lengths: a[digits], b[digits]. Requires c < NN_DIGIT_BITS. */
uint32 nn_lshift(uint32 *a, uint32 *b, uint16 c, uint16 digits)
{
  uint32 bi, carry;
  int16 i, t;
  
  if (c >= NN_DIGIT_BITS)
  {
    return (0);
  }
  
  t = NN_DIGIT_BITS - c;

  carry = 0;

  for (i = 0; i < digits; i++) 
  {
    bi = b[i];
    a[i] = (bi << c) | carry;
    carry = c ? (bi >> t) : 0;
  }
  return (carry);
}

/* Computes a = b * 2^c (i.e., shifts left c bits), returning carry. Lengths: a[digits], b[digits]. Requires c < NN_DIGIT_BITS. */
uint32 nn_rshift(uint32 *a, uint32 *b, uint16 c, uint16 digits)
{
  uint32 bi, carry;
  int16 i, t;

  if (c >= NN_DIGIT_BITS)
  {
    return 0;
  }
  t = NN_DIGIT_BITS - c;
  carry = 0;
  for (i = digits - 1; i >= 0; i--) 
  {
    bi = b[i];
    a[i] = (bi >> c) | carry;
    carry = c ? (bi << t) : 0;
  }  
  return (carry);
}


/* Computes a = c div d and b = c mod d.  Lengths: a[cDigits], b[dDigits], c[cDigits], d[dDigits].
   Assumes d > 0, cDigits < 2 * MAX_NN_DIGITS,  dDigits < MAX_NN_DIGITS.  */
void nn_div(uint32 *a, uint32 *b, uint32 *c, uint16 cdigits, uint32 *d, uint16 ddigits)
{
  uint32 ai, cc[2*MAX_NN_DIGITS+1], dd[MAX_NN_DIGITS], t;
  int16 i;
  uint16 dddigits, shift;
  
  memset_s (cc,sizeof (cc), 0, sizeof (cc));
  memset_s (dd,sizeof (dd), 0, sizeof (dd));
  
  dddigits = nn_digits (d, ddigits);

  if (dddigits == 0)
    return;  
  /* Normalize operands. */
  shift = NN_DIGIT_BITS - nn_digit_bits (d[dddigits-1]);
  nn_assign_zero (cc, dddigits);
  cc[cdigits] = nn_lshift (cc, c, shift, cdigits);
  nn_lshift (dd, d, shift, dddigits);
  t = dd[dddigits-1];
  
  nn_assign_zero (a, cdigits);

  for (i = cdigits-dddigits; i >= 0; i--) 
  {
       //printf("nn_div i = %d  \n", i);
    /* Underestimate quotient digit and subtract. */
    if (t == MAX_NN_DIGIT)
    {
      ai = cc[i+dddigits];
    }
    else
    {
      nn_digit_div (&ai, &cc[i+dddigits-1], t + 1);
    }
    cc[i+dddigits] -= nn_sub_digit_mult (&cc[i], &cc[i], ai, dd, dddigits);

    /* Correct estimate. */
    while (cc[i+dddigits] || (nn_cmp (&cc[i], dd, dddigits) >= 0)) 
    {
      ai++;
      cc[i+dddigits] -= nn_sub (&cc[i], &cc[i], dd, dddigits);
    }
    
    a[i] = ai;
  }
  
  /* Restore result. */
  nn_assign_zero (b, ddigits);
  nn_rshift (b, cc, shift, dddigits);

}


/* Computes a = b mod c.  Lengths: a[cDigits], b[bDigits], c[cDigits].
   Assumes c > 0, bDigits < 2 * MAX_NN_DIGITS, cDigits < MAX_NN_DIGITS. */
void nn_mod(uint32 *a, uint32 *b, uint16 bdigits, uint32 *c, uint16 cdigits)
{
  uint32 t[2 * MAX_NN_DIGITS];

  memset_s (t,sizeof (t), 0, sizeof (t));
  
  nn_div (t, a, b, bdigits, c, cdigits); 
}


/* Computes a = b * c mod d.  Lengths: a[digits], b[digits], c[digits], d[digits]. Assumes d > 0, digits < MAX_NN_DIGITS. */
void nn_mod_mult(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint16 digits)
{
  uint32 t[2*MAX_NN_DIGITS];

  memset_s (t,sizeof (t), 0, sizeof (t));

  nn_mult (t, b, c, digits);
  nn_mod (a, t,(uint16)(2 * digits), d, digits);

}

/* Computes a = b^c mod d.  Lengths: a[dDigits], b[dDigits], c[cDigits], d[dDigits]. Assumes d > 0, cDigits > 0, dDigits < MAX_NN_DIGITS.
 */
void nn_mod_exp(uint32 *a, uint32 *b, uint32 *c, uint16 cdigits, uint32 *d, uint16 ddigits)
{
  uint32 power[3][MAX_NN_DIGITS], ci, t[MAX_NN_DIGITS];
  int16 i;
  uint16 cibits, j, s;

  memset_s (power,sizeof (power), 0, sizeof (power));
  memset_s (t,sizeof (t), 0, sizeof (t));

  /* Store b, b^2 mod d, and b^3 mod d. */
  nn_assign (power[0], b, ddigits); 
  nn_mod_mult (power[1], power[0], b, d, ddigits);
  nn_mod_mult (power[2], power[1], b, d, ddigits);
  
  NN_ASSIGN_DIGIT (t, 1, ddigits);

  cdigits = nn_digits (c, cdigits);
  for (i = cdigits - 1; i >= 0; i--) 
  {
    ci = c[i];
    cibits = NN_DIGIT_BITS;    
    /* Scan past leading zero bits of most significant digit.  */
    if (i == (int16)(cdigits - 1)) 
    {
      while (! DIGIT_2MSB (ci)) 
      {
        ci <<= 2;
        cibits -= 2;
      }
    }

    for (j = 0; j < cibits; j += 2, ci <<= 2) 
    {
    /* Compute t = t^4 * b^s mod d, where s = two MSB's of ci.  */
      nn_mod_mult (t, t, t, d, ddigits);
      nn_mod_mult (t, t, t, d, ddigits);
      if ((s = DIGIT_2MSB (ci)) != 0)
      {
        nn_mod_mult (t, t, power[s-1], d, ddigits);
      }
    }
  }
  
  nn_assign (a, t, ddigits);  

}


/* Compute a = 1/b mod c, assuming inverse exists.   Lengths: a[digits], b[digits], c[digits].
   Assumes gcd (b, c) = 1, digits < MAX_NN_DIGITS. */
void nn_mod_inv(uint32 *a, uint32 *b, uint32 *c, uint16 digits)
{
  uint32 q[MAX_NN_DIGITS], t1[MAX_NN_DIGITS], t3[MAX_NN_DIGITS],
         u1[MAX_NN_DIGITS], u3[MAX_NN_DIGITS], v1[MAX_NN_DIGITS],
         v3[MAX_NN_DIGITS], w[2*MAX_NN_DIGITS];
  int16 u1Sign;

  memset_s (q,sizeof (q), 0, sizeof (q));
  memset_s (t1,sizeof (t1), 0, sizeof (t1));
  memset_s (t3,sizeof (t3), 0, sizeof (t3));
  memset_s (u1,sizeof (u1), 0, sizeof (u1));
  memset_s (u3,sizeof (u3), 0, sizeof (u3));
  memset_s (v1,sizeof (v1), 0, sizeof (v1));
  memset_s (v3,sizeof (v3), 0, sizeof (v3));
  memset_s (w,sizeof (w), 0, sizeof (w));

  /* Apply extended Euclidean algorithm, modified to avoid negative numbers.  */
  NN_ASSIGN_DIGIT (u1, 1, digits);
  nn_assign_zero (v1, digits);
  nn_assign (u3, b, digits);
  nn_assign (v3, c, digits);
  u1Sign = 1;

  while (! nn_zero (v3, digits)) 
  {
    nn_div (q, t3, u3, digits, v3, digits);
    nn_mult (w, q, v1, digits);
    nn_add (t1, u1, w, digits);
    nn_assign (u1, v1, digits);
    nn_assign (v1, t1, digits);
    nn_assign (u3, v3, digits);
    nn_assign (v3, t3, digits);
    u1Sign = -u1Sign;
  }
  
  /* Negate result if sign is negative. */
  if (u1Sign < 0)
  {
    nn_sub (a, c, u1, digits);
  }
  else
  {
    nn_assign (a, u1, digits);
  }

}


/* Computes a = gcd(b, c). Lengths: a[digits], b[digits], c[digits]. Assumes b > c, digits < MAX_NN_DIGITS. */
void nn_gcd(uint32 *a, uint32 *b, uint32 *c, uint16 digits)
{
  uint32 t[MAX_NN_DIGITS], u[MAX_NN_DIGITS], v[MAX_NN_DIGITS];

  memset_s (t,sizeof (t), 0, sizeof (t));
  memset_s (u,sizeof (u), 0, sizeof (u));
  memset_s (v,sizeof (v), 0, sizeof (v));

  nn_assign (u, b, digits);
  nn_assign (v, c, digits);

  while (! nn_zero (v, digits)) 
  {
    nn_mod (t, u, digits, v, digits);
    nn_assign (u, v, digits);
    nn_assign (v, t, digits);
  }
  nn_assign (a, u, digits);
}


/* returns the langth of a in digits; lengths: a[digits] */
uint16 nn_digits(uint32 *a, uint16 digits)
{
  int16 i;

  for(i=digits-1; i>=0; i--)
  {
    if(a[i] != 0)
    {
      break;
    }
  }
  return (uint16)(i+1);
}

int16 nn_cmp(uint32 *a, uint32 *b, uint16 digits)
{
  int16 i;

  for(i=digits-1; i>=0; i--)
  {
    if(a[i]>b[i])
    {
      return 1;
    }
    if(a[i]<b[i])
    {
      return -1;
    }
  }
  return 0;
}

int16 nn_zero(uint32 *a, uint16 digits)
{
  int16 i;  
  for (i = 0; i < digits; i++)
  {
    if (a[i])
    {
      return (0);
    }
  }
  return (1);
}

/* Returns the significant length of a in bits.  Lengths: a[digits]. */
uint16 nn_bits(uint32 *a, uint16 digits)
{
  if ((digits = nn_digits (a, digits)) == 0)
  {
    return (0);
  }
  return (uint16)((digits - 1) * NN_DIGIT_BITS + nn_digit_bits (a[digits-1]));
}

/* Computes a = b + c*d, where c is a digit. Returns carry. Lengths: a[digits], b[digits], d[digits]. */
static uint32 nn_add_digit_mult(uint32 *a, uint32 *b, uint32 c, uint32 *d, uint16 digits)
{
  uint32 carry, t[2];
  int16 i;

  if (c == 0)
    return (0);

  carry = 0;
  
  for (i = 0; i < digits; i++) 
  {
    nn_digit_mult (t, c, d[i]);
    if ((a[i] = b[i] + carry) < carry)
    {
      carry = 1;
    }
    else
    {
      carry = 0;
    }
    if ((a[i] += t[0]) < t[0])
    {
      carry++;
    }
    carry += t[1];
  }  
  return (carry);
}

/* Computes a = b - c*d, where c is a digit. Returns borrow.  Lengths: a[digits], b[digits], d[digits]. */
static uint32 nn_sub_digit_mult(uint32 *a, uint32 *b, uint32 c, uint32 *d, uint16 digits)
{
  uint32 borrow, t[2];
  int16 i;

  if (c == 0)
    return (0);

  borrow = 0;
  
  for (i = 0; i < digits; i++) 
  {
    nn_digit_mult (t, c, d[i]);

    if ((a[i] = b[i] - borrow) > (MAX_NN_DIGIT - borrow))
    {
      borrow = 1;
    }
    else
    {
      borrow = 0;
    }
    if ((a[i] -= t[0]) > (MAX_NN_DIGIT - t[0]))
    {
      borrow++;
    }
    borrow += t[1];
  }  
  return (borrow);
}

static uint16 nn_digit_bits(uint32 a)
{
  int16 i;
  
  for (i = 0; i < NN_DIGIT_BITS; i++, a >>= 1)
    if (a == 0)
      break;    
  return (uint16)i;
}

