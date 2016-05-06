/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcPsTransfer.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年10月21日
  最近修改   :
  功能描述   : MTC模块处理PS域切换相关功能相关数据结构定义及函数声明
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MTCPSTRANSFER_H__
#define __MTCPSTRANSFER_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MtcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  5 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  6 函数声明
*****************************************************************************/
VOS_VOID MTC_RcvRrcAreaLostInd(VOS_VOID * pMsg);

VOS_VOID MTC_SndModem0MtaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
);

VOS_VOID MTC_SndModem0GmmRrcAreaLostInd(VOS_VOID);


VOS_VOID MTC_SndModem0MmaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
);

VOS_VOID MTC_RcvRrcAreaAvaliableInd(VOS_VOID * pMsg);

VOS_VOID MTC_ProcCurrCampPlmnInfoForSvlte(VOS_VOID);

VOS_VOID MTC_ProcCurrCampPlmnInfoForLC(VOS_VOID);

/* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
VOS_VOID MTC_RcvGsmCellInfoInd(VOS_VOID *pMsg);
/* Added by Y00213812 for 主动离网重选, 2014-04-10, end */



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MtcPsTransfer.h */


