/*
 * rand.c
 *
 * Pseudorandom number generation, based on OpenBSD arc4random().
 *
 * Copyright (c) 2000 Dug Song <dugsong@monkey.org>
 * Copyright (c) 1996 David Mazieres <dm@lcs.mit.edu>
 *
 * $Id: rand.c,v 1.15 2005/02/15 06:37:07 dugsong Exp $
 */

#include "rand.h"
#include "v_lib.h"

#if (VOS_WIN32 == VOS_OS_VER)
typedef unsigned char u_char;
typedef unsigned int  u_int;
/* XXX */
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <wincrypt.h>
#define inline __inline
#elif (VOS_VXWORKS == VOS_OS_VER)
#else
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
#endif

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "product_config.h"

/*lint -e701 -e702 -e732 -e734 -e713 -e737 -e734*/

#if (FEATURE_VSIM == FEATURE_ON)
struct rand_handle {
	unsigned char		 i;
	unsigned char		 j;
	unsigned char		 s[256];
	u_char		*tmp;
	int		 tmplen;
};

/*lint -e578*/
static void rand_addrandom(rand_t *rand, u_char *buf, int len)
{
	int i;
	unsigned char si;

	rand->i--;
	for (i = 0; i < 256; i++) {
		rand->i = (rand->i + 1);
		si = rand->s[rand->i];
		rand->j = (rand->j + si + buf[i % len]);
		rand->s[rand->i] = rand->s[rand->j];
		rand->s[rand->j] = si;
	}
	rand->j = rand->i;
}
/*lint +e578*/

rand_t * rand_open(void)
{
    int i;
	rand_t *r;
	u_char seed[256];
#if (VOS_WIN32 == VOS_OS_VER)
	HCRYPTPROV hcrypt = 0;

	CryptAcquireContext(&hcrypt, NULL, NULL, PROV_RSA_FULL,
	    CRYPT_VERIFYCONTEXT);
	CryptGenRandom(hcrypt, sizeof(seed), seed);
	CryptReleaseContext(hcrypt, 0);
#elif ((VOS_VXWORKS == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))
    for (i = 0; i < 256; i++)
    {
        seed[i] = VOS_Rand(0xff);
    }
#else
	struct timeval *tv = (struct timeval *)seed;
	int fd;

	if ((fd = open("/dev/arandom", O_RDONLY)) != -1 ||
	    (fd = open("/dev/urandom", O_RDONLY)) != -1) {
		read(fd, seed + sizeof(*tv), sizeof(seed) - sizeof(*tv));
		close(fd);
	}
	gettimeofday(tv, NULL);
#endif
/*lint -e539*/
	if ((r = malloc(sizeof(*r))) != NULL) {

        for (i = 0; i < 256; i++)
	       	r->s[i] = i;
	    r->i = r->j = 0;

		rand_addrandom(r, seed, 128);
		rand_addrandom(r, seed + 128, 128);
		r->tmp = NULL;
		r->tmplen = 0;
	}
/*lint +e539*/
	return (r);
}

int rand_get(rand_t *r, void *buf, size_t len)
{
	u_char *prime;
	u_int i;

	for (prime = buf, i = 0; i < len; i++) {

       	unsigned char si, sj;

	    r->i = (r->i + 1);
	    si = r->s[r->i];
	    r->j = (r->j + si);
	    sj = r->s[r->j];
	    r->s[r->i] = sj;
	    r->s[r->j] = si;
	    prime[i] = (r->s[(si + sj) & 0xff]);

		//prime[i] = rand_getbyte(r);
	}
	return (0);
}

int rand_set(rand_t *r, const void *buf, size_t len)
{
    int i;
    for (i = 0; i < 256; i++)
	   	r->s[i] = i;
/*lint -e539*/
	r->i = r->j = 0;
/*lint +e539*/

	//rand_init(r);
	rand_addrandom(r, (u_char *)buf, (int)len);
	rand_addrandom(r, (u_char *)buf, (int)len);
	return (0);
}


rand_t * rand_close(rand_t *r)
{
	if (r != NULL) {
		if (r->tmp != NULL)
			free(r->tmp);
		free(r);
	}
	return (NULL);
}
#endif

/*lint +e701 +e702 +e732 +e734 +e713 +e737 +e734*/
