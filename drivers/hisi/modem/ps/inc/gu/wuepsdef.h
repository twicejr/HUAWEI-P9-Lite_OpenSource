/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Wuepsdef.h
  Author      : Zongyan Lee
  Version     : V100R001
  Date        : 2005-04-15
  Description : MAPS TAF OM对外的接口头文件。
  History     :
  1. Date:2005-04-15
     Author: Zongyan Lee
     Modification:Create
  2. Date:2005-09-08
     Author: Xiaopeng Du
     Modification:add for A32D00484
************************************************************************/

#ifndef _WUEPS_DEF_H_
#define _WUEPS_DEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "wuepscfg.h"
#include "frmwkext.h"

extern const VOS_UINT16 taskPidDefTbl[WUEPS_MAX_PID_NUM];

#ifndef NULL
    #define NULL                    0
#endif

#if (VOS_OS_VER == VOS_WIN32)
    #ifndef VOID
        #define VOID                VOS_VOID
    #endif
#endif

/* 表示肯定/否定的全局宏 */
#define    WUEPS_TRUE               0
#define    WUEPS_FALSE              1

#define    WUEPS_OK                 0
#define    WUEPS_NG                 1

/* 表示无效的全局宏 */
#define    WUEPS_INVALID            (-1)

/* 取两数的最大值/最小值的全局宏 */
#define    WUEPS_MAX(a,b)           (((a)>(b)) ? (a) : (b))
#define    WUEPS_MIN(a,b)           (((a)<=(b))? (a) : (b))

/* ASSERT定义 */
#define    WUEPS_ASSERT( exp )      if( (exp) == 0 ){VOS_ASSERT(exp);}

#define WUEPS_PS_STUB_SWITCH 1

#ifndef PS_RAND_MAX
#define PS_RAND_MAX 0x7fff
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif
