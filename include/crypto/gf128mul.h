/* gf128mul.h - GF(2^128) multiplication functions
 *
 * Copyright (c) 2003, Dr Brian Gladman, Worcester, UK.
 * Copyright (c) 2006 Rik Snel <rsnel@cube.dyndns.org>
 *
 * Based on Dr Brian Gladman's (GPL'd) work published at
 * http://fp.gladman.plus.com/cryptography_technology/index.htm
 * See the original copyright notice below.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */
/*
 ---------------------------------------------------------------------------
 Copyright (c) 2003, Dr Brian Gladman, Worcester, UK.   All rights reserved.

 LICENSE TERMS

 The free distribution and use of this software in both source and binary
 form is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright
      notice, this list of conditions and the following disclaimer;

   2. distributions in binary form include the above copyright
      notice, this list of conditions and the following disclaimer
      in the documentation and/or other associated materials;

   3. the copyright holder's name is not used to endorse products
      built using this software without specific written permission.

 ALTERNATIVELY, provided that this notice is retained in full, this product
 may be distributed under the terms of the GNU General Public License (GPL),
 in which case the provisions of the GPL apply INSTEAD OF those given above.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and/or fitness for purpose.
 ---------------------------------------------------------------------------
 Issue Date: 31/01/2006

 An implementation of field multiplication in Galois Field GF(128)
*/

#ifndef _CRYPTO_GF128MUL_H
#define _CRYPTO_GF128MUL_H

#include <crypto/b128ops.h>
#include <linux/slab.h>


/*	Multiply a GF128 field element by x. Field elements are held in arrays
    of bytes in which field bits 8n..8n + 7 are held in byte[n], with lower
    indexed bits placed in the more numerically significant bit positions
    within bytes.

    On little endian machines the bit indexes translate into the bit
    positions within four 32-bit words in the following way

    MS            x[0]           LS  MS            x[1]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    24...31 16...23 08...15 00...07  56...63 48...55 40...47 32...39

    MS            x[2]           LS  MS            x[3]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    88...95 80...87 72...79 64...71  120.127 112.119 104.111 96..103

    On big endian machines the bit indexes translate into the bit
    positions within four 32-bit words in the following way

    MS            x[0]           LS  MS            x[1]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    00...07 08...15 16...23 24...31  32...39 40...47 48...55 56...63

    MS            x[2]           LS  MS            x[3]		  LS
    ms   ls ms   ls ms   ls ms   ls  ms   ls ms   ls ms   ls ms   ls
    64...71 72...79 80...87 88...95  96..103 104.111 112.119 120.127
*/

/*	A slow generic version of gf_mul, implemented for lle and bbe
 * 	It multiplies a and b and puts the result in a */
void gf128mul_lle(be128 *a, const be128 *b);

void gf128mul_bbe(be128 *a, const be128 *b);

/* multiply by x in ble format, needed by XTS */
void gf128mul_x_ble(be128 *a, const be128 *b);

/* 4k table optimization */

struct gf128mul_4k {
	be128 t[256];
};

struct gf128mul_4k *gf128mul_init_4k_lle(const be128 *g);
struct gf128mul_4k *gf128mul_init_4k_bbe(const be128 *g);
void gf128mul_4k_lle(be128 *a, struct gf128mul_4k *t);
void gf128mul_4k_bbe(be128 *a, struct gf128mul_4k *t);

static inline void gf128mul_free_4k(struct gf128mul_4k *t)
{
	kfree(t);
}


/* 64k table optimization, implemented for lle and bbe */

struct gf128mul_64k {
	struct gf128mul_4k *t[16];
};

/* first initialize with the constant factor with which you
 * want to multiply and then call gf128_64k_lle with the other
 * factor in the first argument, the table in the second and a
 * scratch register in the third. Afterwards *a = *r. */
struct gf128mul_64k *gf128mul_init_64k_lle(const be128 *g);
struct gf128mul_64k *gf128mul_init_64k_bbe(const be128 *g);
void gf128mul_free_64k(struct gf128mul_64k *t);
void gf128mul_64k_lle(be128 *a, struct gf128mul_64k *t);
void gf128mul_64k_bbe(be128 *a, struct gf128mul_64k *t);

#endif /* _CRYPTO_GF128MUL_H */
