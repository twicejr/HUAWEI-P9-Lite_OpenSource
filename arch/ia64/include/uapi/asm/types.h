
#ifndef _UAPI_ASM_IA64_TYPES_H
#define _UAPI_ASM_IA64_TYPES_H


#ifndef __KERNEL__
#include <asm-generic/int-l64.h>
#endif

#ifdef __ASSEMBLY__
# define __IA64_UL(x)		(x)
# define __IA64_UL_CONST(x)	x

#else
# define __IA64_UL(x)		((unsigned long)(x))
# define __IA64_UL_CONST(x)	x##UL

#endif /* !__ASSEMBLY__ */

#endif /* _UAPI_ASM_IA64_TYPES_H */
