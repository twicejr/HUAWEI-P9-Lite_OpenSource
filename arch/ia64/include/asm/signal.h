
#ifndef _ASM_IA64_SIGNAL_H
#define _ASM_IA64_SIGNAL_H

#include <uapi/asm/signal.h>


#define _NSIG		64
#define _NSIG_BPW	64
#define _NSIG_WORDS	(_NSIG / _NSIG_BPW)

# ifndef __ASSEMBLY__

/* Most things should be clean enough to redefine this at will, if care
   is taken to make libc match.  */

typedef unsigned long old_sigset_t;

typedef struct {
	unsigned long sig[_NSIG_WORDS];
} sigset_t;

#  include <asm/sigcontext.h>

# endif /* !__ASSEMBLY__ */
#endif /* _ASM_IA64_SIGNAL_H */
