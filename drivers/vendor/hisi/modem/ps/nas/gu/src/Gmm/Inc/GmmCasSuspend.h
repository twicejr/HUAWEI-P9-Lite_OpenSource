/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasSuspend.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-10-21
  Description : GmmCasSuspend模块的内部头文件
  History     :
  1. Date:2005-11-25
     Author: Roger Leo
     Modification:update
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
************************************************************************/

#ifndef _GMM_CAS_SUSPEND_H_
#define _GMM_CAS_SUSPEND_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#pragma pack(4)         /* 1字节对齐，数据结构定义保证4字节对齐 */
                        /* 放在include后，不影响其他头文件的pack参数 */
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

VOS_UINT32 GMM_BufferMsgQueueIn(VOS_VOID);
VOS_UINT32 GMM_BufferMsgQueueOut(VOS_VOID);
VOS_UINT32 GMM_BufferMsgSend(VOS_VOID);
VOS_VOID GMM_BufferMsgResume(VOS_VOID);
VOS_VOID GMM_BufferMsgDump(VOS_VOID);
VOS_VOID GMM_BufferMsgReceive(struct MsgCB* pMsgIn);
VOS_VOID NAS_GMM_ClearMsgFromBuff(
        VOS_UINT32                     ulMsgName,
        VOS_UINT32                     ulSenderPid,
        VOS_UINT32                     ulReceiverPid
);
/*VOS_UINT8 GMM_IsExistMsgHold(VOS_UINT32 ulMask);*/
VOS_VOID  GMM_FreeCasMsgHoldBuf (VOS_VOID);
/*VOS_VOID  GMM_ResumeMsgHold(VOS_UINT32 ulMask, GMM_CAS_STATE CasType);*/

VOS_VOID GMM_RcvMmcSuspendInd(VOS_VOID* pRcvMsg);
VOS_VOID GMM_RcvMmcResumeInd(VOS_VOID* pRcvMsg);
VOS_VOID GMM_ResumeSuccess(VOS_VOID);
VOS_VOID GMM_ResumeFailure(VOS_VOID);

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

#endif /* end of GmmCasSuspend.h*/
