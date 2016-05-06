#ifndef __MDRV_PUBLIC_H__
#define __MDRV_PUBLIC_H__
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef OK
#define OK                  (0)
#endif

#ifndef ERROR
#define ERROR               (-1)
#endif

#ifndef __VOIDFUNCPTR
#define __VOIDFUNCPTR
typedef void (*VOIDFUNCPTR)(unsigned int );
#endif

#ifndef __FUNCPTR_1
#define __FUNCPTR_1
typedef int (*FUNCPTR_1)(int);
#endif

#ifndef __pFUNCPTR
#define __pFUNCPTR
typedef int  (*pFUNCPTR)(void);
#endif

#ifdef __cplusplus
}
#endif
#endif
