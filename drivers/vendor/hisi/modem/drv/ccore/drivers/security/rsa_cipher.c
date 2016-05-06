//#include "config.h"
#include "string.h"
#include "securec.h"
#include "rsa.h"
#include "rsann.h"
/*lint --e{534, 732} */
int16 rsa_public_block(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_public_key *public_key)
{
  uint32 c[MAX_NN_DIGITS] = {0}, e[MAX_NN_DIGITS] = {0}, m[MAX_NN_DIGITS] = {0},
  n[MAX_NN_DIGITS] = {0};
  uint16 eDigits = 0, nDigits = 0;

  (void)memset_s (c, sizeof (c), 0, sizeof (c));
  (void)memset_s (m, sizeof (m), 0, sizeof (m));
  (void)memset_s (n, sizeof (n), 0, sizeof (n));

  nn_decode (m, MAX_NN_DIGITS, input, input_len);
  nn_decode (n, MAX_NN_DIGITS, public_key->modulus, MAX_RSA_MODULUS_LEN);
  nn_decode (e, MAX_NN_DIGITS, public_key->public_exponent, MAX_RSA_MODULUS_LEN);
  nDigits = nn_digits (n, MAX_NN_DIGITS);
  eDigits = nn_digits (e, MAX_NN_DIGITS);

  if (nn_cmp (m, n, nDigits) >= 0)
  return -1;

  /* Compute c = m^e mod n. */
  nn_mod_exp (c, m, e, eDigits, n, nDigits);

	*output_len = (uint16)(public_key->bits + 7) / 8;
	nn_encode (output, *output_len, c, nDigits);

	return (0);
}

int16 rsa_private_block(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_private_key *private_key)
{
  uint32 c[MAX_NN_DIGITS] = {0}, cP[MAX_NN_DIGITS] = {0}, cQ[MAX_NN_DIGITS] = {0},
  dP[MAX_NN_DIGITS] = {0}, dQ[MAX_NN_DIGITS] = {0}, mP[MAX_NN_DIGITS] = {0},
  mQ[MAX_NN_DIGITS] = {0}, n[MAX_NN_DIGITS] = {0}, p[MAX_NN_DIGITS] = {0}, q[MAX_NN_DIGITS] = {0},
  qInv[MAX_NN_DIGITS] = {0}, t[MAX_NN_DIGITS] = {0};
  uint16 cDigits = 0, nDigits = 0, pDigits = 0;

  (void)memset_s (c , sizeof (c) , 0, sizeof (c));
  (void)memset_s (cP, sizeof (cP), 0, sizeof (cP));
  (void)memset_s (cQ, sizeof (cQ), 0, sizeof (cQ));
  (void)memset_s (dP, sizeof (dP), 0, sizeof (dP));
  (void)memset_s (dQ, sizeof (dQ), 0, sizeof (dQ));
  (void)memset_s (mP, sizeof (mP), 0, sizeof (mP));
  (void)memset_s (mQ, sizeof (mQ), 0, sizeof (mQ));
  (void)memset_s (p,  sizeof (p) , 0, sizeof (p));
  (void)memset_s (q,  sizeof (q) , 0, sizeof (q));
  (void)memset_s (qInv, sizeof (qInv), 0, sizeof (qInv));
  (void)memset_s (t, sizeof (t), 0, sizeof (t));

  nn_decode (c, MAX_NN_DIGITS, input, input_len);
  nn_decode (n, MAX_NN_DIGITS, private_key->modulus, MAX_RSA_MODULUS_LEN);
  nn_decode (p, MAX_NN_DIGITS, private_key->prime[0], MAX_RSA_PRIME_LEN);
  nn_decode (q, MAX_NN_DIGITS, private_key->prime[1], MAX_RSA_PRIME_LEN);
  nn_decode (dP, MAX_NN_DIGITS, private_key->prime_exponent[0], MAX_RSA_PRIME_LEN);
  nn_decode (dQ, MAX_NN_DIGITS, private_key->prime_exponent[1], MAX_RSA_PRIME_LEN);
  nn_decode (qInv, MAX_NN_DIGITS, private_key->coefficient, MAX_RSA_PRIME_LEN);


  cDigits = nn_digits (c, MAX_NN_DIGITS);
  nDigits = nn_digits (n, MAX_NN_DIGITS);
  pDigits = nn_digits (p, MAX_NN_DIGITS);

  if (nn_cmp (c, n, nDigits) >= 0)
  return -1;

  /* Compute mP = cP^dP mod p  and  mQ = cQ^dQ mod q. (Assumes q has length at most pDigits, i.e., p > q.) */
  nn_mod (cP, c, cDigits, p, pDigits);
  nn_mod (cQ, c, cDigits, q, pDigits);
  nn_mod_exp (mP, cP, dP, pDigits, p, pDigits);

  nn_assign_zero (mQ, nDigits);
  nn_mod_exp (mQ, cQ, dQ, pDigits, q, pDigits);

  /* Chinese Remainder Theorem:  m = ((((mP - mQ) mod p) * qInv) mod p) * q + mQ.   */
  if (nn_cmp (mP, mQ, pDigits) >= 0)
  {
    (void)nn_sub (t, mP, mQ, pDigits);
  }
  else
  {
    (void)nn_sub (t, mQ, mP, pDigits);
    (void)nn_sub (t, p, t, pDigits);
  }
  nn_mod_mult (t, t, qInv, p, pDigits);
  nn_mult (t, t, q, pDigits);
  (void)nn_add (t, t, mQ, nDigits);

	*output_len = (uint16)(private_key->bits + 7) / 8;
	nn_encode (output, *output_len, t, nDigits);

	return (0);
}

int16 rsa_private_encrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_private_key *private_key )
{
  int16 status;
  uint8 pkcsBlock[MAX_RSA_MODULUS_LEN];
  int16 i, modulusLen;

	(void)memset_s (pkcsBlock, sizeof (pkcsBlock), 0, sizeof (pkcsBlock));
	modulusLen = (int16)((uint16)(private_key->bits + 7) / 8);
	if (input_len + 11 > modulusLen)
		return -1;

  pkcsBlock[0] = 0;
  pkcsBlock[1] = 1;

  for (i = 2; i < modulusLen - input_len - 1; i++)
  {
    pkcsBlock[i] = 0xff;
  }
  /* separator */
  pkcsBlock[i++] = 0;
  (void)memcpy_s (&pkcsBlock[i], input_len, input, input_len);
  status = rsa_private_block(pkcsBlock, (uint16)modulusLen, output, output_len, private_key);

  return status;

}

int16 rsa_public_decrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_public_key *public_key)
{
  int16 status;
  uint8 pkcsBlock[MAX_RSA_MODULUS_LEN];
  int16 i;
  uint16 modulusLen, pkcsBlockLen;

	(void)memset_s (pkcsBlock, sizeof (pkcsBlock), 0, sizeof (pkcsBlock));
	modulusLen = (uint16)(public_key->bits + 7) / 8;
	if (input_len > modulusLen)
		return -1;

  status = rsa_public_block(input, input_len, pkcsBlock, &pkcsBlockLen, public_key);
  if (0 != status)
  {
    return (status);
  }

  if (pkcsBlockLen != modulusLen)
    return -1;

  /* Require block type 1. */
  if ((pkcsBlock[0] != 0) || (pkcsBlock[1] != 1))
    return -1;

  for (i = 2; i < modulusLen-1; i++)
    if (pkcsBlock[i] != 0xff)
      break;

  /* separator */
  if (pkcsBlock[i++] != 0)
    return -1;

  *output_len = modulusLen - i;

  if (*output_len + 11 > modulusLen)
    return -1;

  (void)memcpy_s (output, *output_len, &pkcsBlock[i], *output_len);
  return (0);
}

int16 rsa_public_encrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_public_key *public_key )
{
  int16 status;
  uint8 pkcsBlock[MAX_RSA_MODULUS_LEN];
  int16 i, modulusLen;

	(void)memset_s (pkcsBlock, sizeof (pkcsBlock), 0, sizeof (pkcsBlock));
	modulusLen = (int16)((uint16)(public_key->bits + 7) / 8);
	if (input_len + 11 > modulusLen)
		return -1;

  pkcsBlock[0] = 0;
  pkcsBlock[1] = 1;

  for (i = 2; i < modulusLen - input_len - 1; i++)
  {
    pkcsBlock[i] = 0xff;
  }
  /* separator */
  pkcsBlock[i++] = 0;
  (void)memcpy_s (&pkcsBlock[i], input_len, input, input_len);
  status = rsa_public_block(pkcsBlock, (uint16)modulusLen, output, output_len, public_key);

  return status;

}


int16 rsa_private_decrypt(uint8 *input, uint16 input_len, uint8 *output, uint16 *output_len, rsa_private_key *private_key)
{
  int16 status;
  uint8 pkcsBlock[MAX_RSA_MODULUS_LEN];
  int16 i;
  uint16 modulusLen, pkcsBlockLen;

	(void)memset_s (pkcsBlock, sizeof (pkcsBlock), 0, sizeof (pkcsBlock));
	modulusLen = (uint16)(private_key->bits + 7) / 8;
	if (input_len > modulusLen)
		return -1;

  status = rsa_private_block(input, input_len, pkcsBlock, &pkcsBlockLen, private_key);
  if (0 != status)
  {
    return (status);
  }

  if (pkcsBlockLen != modulusLen)
    return -1;

  /* Require block type 1. */
  if ((pkcsBlock[0] != 0) || (pkcsBlock[1] != 1))
    return -1;

  for (i = 2; i < modulusLen-1; i++)
    if (pkcsBlock[i] != 0xff)
      break;

  /* separator */
  if (pkcsBlock[i++] != 0)
    return -1;

  *output_len = modulusLen - i;

  if (*output_len + 11 > modulusLen)
    return -1;

  (void)memcpy_s (output, *output_len, &pkcsBlock[i], *output_len);
  return (0);
}

