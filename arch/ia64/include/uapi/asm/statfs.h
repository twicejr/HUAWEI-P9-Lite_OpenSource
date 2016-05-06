#ifndef _ASM_IA64_STATFS_H
#define _ASM_IA64_STATFS_H

/*
 * Based on <asm-i386/statfs.h>.
 *
 * Modified 1998, 1999, 2003
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */


#define ARCH_PACK_COMPAT_STATFS64 __attribute__((packed,aligned(4)))

#include <asm-generic/statfs.h>

#endif /* _ASM_IA64_STATFS_H */
