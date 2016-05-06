#ifndef __MDRV_CCORE_PUBLIC_H__
#define __MDRV_CCORE_PUBLIC_H__
#ifdef __cplusplus
extern "C"
{
#endif

#define MDRV_OK                  (0)
#define MDRV_ERROR               (-1)

typedef int (*FUNCPTR_1)(int);
typedef int  (*pFUNCPTR)(void);

#if defined(__VXWORKS__)
/* VOIDFUNCPTR/FUNCPTR is defined in vxworks OS, 
 * to avoid duplicated definition
 */
#include <vxWorks.h>
#else
typedef int (*FUNCPTR)(void);
typedef void (*VOIDFUNCPTR)(unsigned int );
#endif


#ifdef __cplusplus
}
#endif
#endif
