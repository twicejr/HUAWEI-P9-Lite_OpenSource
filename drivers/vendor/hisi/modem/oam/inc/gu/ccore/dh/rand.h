/*
 * rand.h
 *
 * Pseudo-random number generation, based on OpenBSD arc4random().
 *
 * Copyright (c) 2000 Dug Song <dugsong@monkey.org>
 * Copyright (c) 1996 David Mazieres <dm@lcs.mit.edu>
 *
 * $Id: rand.h,v 1.4 2002/04/07 19:01:25 dugsong Exp $
 */

#ifndef DNET_RAND_H
#define DNET_RAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

typedef struct rand_handle rand_t;
//__BEGIN_DECLS
rand_t	*rand_open(void);

int	 rand_get(rand_t *r, void *buf, size_t len);
int	 rand_set(rand_t *r, const void *seed, size_t len);
int	 rand_add(rand_t *r, const void *buf, size_t len);

unsigned char rand_uint8(rand_t *r);
unsigned short int rand_uint16(rand_t *r);
unsigned int rand_uint32(rand_t *r);

int	 rand_shuffle(rand_t *r, void *base, size_t nmemb, size_t size);

rand_t	*rand_close(rand_t *r);
//__END_DECLS
#ifdef __cplusplus
}
#endif
#endif /* DNET_RAND_H */
