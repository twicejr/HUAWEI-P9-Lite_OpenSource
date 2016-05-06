/*****************************************************************************

                  版权所有 (C), 1998-2010, 华为技术有限公司

*****************************************************************************
  文 件 名   : ftm.h
  版 本 号   : V1.0
  作    者   : 陈文峰/00149739
  生成日期   : 2010-05-12
  功能描述   : TODO: ...

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2010-05-12
    作    者 : 陈文峰/00149739
    修改内容 : 创建文件

*****************************************************************************/

/*****************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
*****************************************************************************/


#ifndef __FTM_H__
#define __FTM_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "osm.h"
#include <taf_ftm.h>

#define FTM_NONESIG_RTT_OPEN        (1)
#define FTM_NONESIG_RTT_CLOSE       (0)

#define MSP_IMEI_LEN       (15)

#undef UINT32
#define  UINT32 unsigned long
#undef INT32
#define  INT32 long
#undef INT16
#define   INT16 short
#undef UINT16
#define UINT16 unsigned short
#undef UINT8
#define UINT8 unsigned char
#undef INT8
#define INT8 unsigned char

/* 供上层如SYM注册*/
typedef VOS_VOID (*FTM_RESET_CALLBACK_PFN)( VOS_VOID);



extern VOS_UINT32 ftm_TaskMsg(OS_MSG_STRU * pMsg);
/*****************************************************************************
 函数名称: ftm_SymResetCallBackReg
 功能描述: 供SYM模块调用注册回调接口，进行SYM相关初始化

 参数说明:
   pfun [in]：SYM传入的函数接口

 返 回 值:

 调用要求: SYM在初始化时调用
 调用举例: TODO: ...
*****************************************************************************/
extern VOS_VOID ftm_SymResetCallBackReg(FTM_RESET_CALLBACK_PFN pfun);

extern VOS_UINT32 ftm_OnlineUpgradeSetFun(VOS_VOID);

extern VOS_UINT32 FTM_MsgConvert(MsgBlock* pMsg, OS_MSG_STRU* pstFtmMsg);
extern VOS_UINT32 ftm_SendDataMsg(VOS_UINT32 ulSenderId, VOS_UINT32 ulRecverId, VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

extern VOS_BOOL pom_GetDspInitFlg(VOS_VOID);

#ifdef __cplusplus
}
#endif

#endif /*__FTM_H__*/


