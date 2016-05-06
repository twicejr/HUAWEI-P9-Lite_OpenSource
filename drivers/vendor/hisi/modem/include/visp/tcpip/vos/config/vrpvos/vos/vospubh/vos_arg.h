
#ifndef _VOS_ARG_H_
#define _VOS_ARG_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#if (VRP_OS_WINDOWS == VRP_YES)
#include "vos/ansilib/win32/stdarg.h" /*All os should have this ANSI Head file.*/
#elif (VRP_OS_PSOS == VRP_YES)
#if ( VRP_CPU_mPPC == VRP_YES )
#include "vos/ansilib/psos/ppc/stdarg.h"
#else
#include "vos/ansilib/psos/stdarg.h"
#endif
#elif (VRP_OS_VXWORKS == VRP_YES)
/* edit by L00105073 for BC3D01411: 从Tornado目录中包含各类型CPU对应的头文件 */
#include "vos/ansilib/vxworks/stdarg.h"
#else
/*Linux直接添加系统的头文件*/
#include <stdarg.h>
#endif


#ifdef  __cplusplus
}
#endif

#endif



