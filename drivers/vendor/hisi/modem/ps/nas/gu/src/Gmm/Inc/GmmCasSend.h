/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasSend.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-10-21
  Description : GmmCasSend模块的内部头文件
  History     :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. Date:2005-04-05
     Author: Roger Leo
     Modification:added for A32D02352
  3. l40632 2006-05-29 根据问题单A32D03821修改
  4.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  5.日    期   : 2007年12月14日
    作    者   : s46746
    修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
  6.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
************************************************************************/

#ifndef _GMM_CAS_SEND_H_
#define _GMM_CAS_SEND_H_

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
#define GMM_LLC_TRANSID     1           /* GMM使用的SAPI */

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/* 通知LLC的TLLI操作方式 */
typedef VOS_UINT8   GMM_OP_TLLI;
#define GMM_OP_TLLI_ASSIGN              0
#define GMM_OP_TLLI_MODIFY              1
#define GMM_OP_TLLI_UNASSIGN            2
#define GMM_OP_TLLI_UNASSIGN_SYS        3
#define GMM_OP_TLLI_SYNC                4
#define GMM_OP_TLLI_KC                  5

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
VOS_UINT32 GMM_SndGasAbortReq (VOS_UINT32  ulAbortMode);
VOS_UINT32 GMM_SndGasDataReq (
            VOS_UINT8       ucPriorityInd,  /* 消息优先级指示*/
            NAS_MSG_STRU   *pMsg            /* 该CN Domain的NAS消息首地址*/
            );
VOS_UINT32 GMM_SndGasEstReq (
            VOS_UINT32      ulEstCause,     /* RRC Connection Setup原因*/
            VOS_UINT32      ulIdnnsType,    /* 3是响应paging的,6代表其他*/
            NAS_MSG_STRU   *pMsg            /* 该CN Domain的NAS消息首地址*/
            );
VOS_VOID GMM_SndGasNasInfoChangeReq (
            VOS_UINT32           ulMask          /* 各IE有效标志*/
            );
VOS_VOID GMM_SndGasRelReq (VOS_VOID);
VOS_VOID GMM_SndRrmmRelReqGsm(VOS_VOID);


VOS_VOID GMM_SndCasGmmStatusMsg(VOS_UINT8 ucRejCause);
VOS_VOID GMM_SndCasMmcInfoInd (VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndCasSmDataInd(VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndCasSmsUnitdataInd(VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndCasTcDataInd (VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndAttachReqGsm (VOS_VOID);

NAS_MSG_STRU* GMM_MakeNasMsgStru(VOS_UINT8 *pData, VOS_UINT32 ulSize);
LL_NAS_UNITDATA_REQ_ST* GMM_MakeGmmStatusMsgGsm(VOS_UINT8 ucRejectCause);
VOS_VOID GMM_MakeLlcNasMsgHeader(LL_NAS_UNITDATA_REQ_ST *pstNasMsg);
LL_NAS_UNITDATA_REQ_ST *GMM_MakeAttachReqMsgGsm (VOS_VOID);
LL_NAS_UNITDATA_REQ_ST* GMM_MakeAuthenAndCipherRspMsgGsm(
                            VOS_UINT8 ucResFlg                  /* 0:表示不需回传res;1:表示需回传res */
                            );
LL_NAS_UNITDATA_REQ_ST* GMM_MakeIdentityRspMsgGsm(VOS_UINT8 ucIdType);

LL_GMM_ASSIGN_REQ_MSG   *GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI ucAssignFlg);
LL_GMM_TRIGGER_REQ_MSG  *GMM_MakeLlgmmTriggerReqMsg(VOS_UINT8 ucCause);
LL_GMM_SUSPEND_REQ_MSG  *GMM_MakeLlgmmSuspendReqMsg(VOS_VOID);
LL_GMM_RESUME_REQ_MSG   *GMM_MakeLlgmmResumeReqMsg(VOS_UINT32  ulResumeType);
GRRGMM_ASSIGN_REQ_ST  *GMM_MakeGrrmmAssignReqMsg(VOS_UINT32 ulCause);


VOS_VOID GMM_SndRrmmEstCnfGsm(VOS_UINT8 ucRrmmEstOpid);
VOS_VOID GMM_SndRrmmEstReqGsm(VOS_UINT8 ucRrmmEstOpid, NAS_MSG_STRU *pMsg);
VOS_VOID GMM_SndRrmmDataReqGsm(NAS_MSG_STRU *pMsg);
/*VOS_VOID GMM_SndRabmRauInd(VOS_UINT8 ucRauCause);*/
VOS_VOID GMM_SndRabmRauInd(VOS_UINT8 ucRauCause, VOS_UINT8 ucResult);
VOS_VOID NAS_GMM_SndGasInfoChangeReq(VOS_UINT32 ulMask);
VOS_VOID GMM_SndLlcSuspendReq(VOS_VOID);
VOS_VOID Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8 ucClearDataType);
VOS_VOID GMM_SndLlcResumeReq(VOS_UINT32  ulResumeType);
VOS_VOID GMM_SndLlcTriggerReq(VOS_UINT8 ucCause);


VOS_VOID GMM_SndRabmGprsInfoInd(VOS_UINT8 ucGprsSupported,VOS_UINT8 ucProc,VOS_UINT8 ucRau);
VOS_VOID GMM_SndRabmGprsSuspensionInd(VOS_UINT8 ucProc);
VOS_VOID GMM_SndRabmGprsResumeInd(VOS_UINT8 ucProc,VOS_UINT8 ucResult);

VOS_VOID GMM_SndMmcSuspendRsp(VOS_VOID);

extern VOS_VOID NAS_GMM_SndMmcResumeRsp(VOS_VOID);


VOS_VOID NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ENUM_UINT16 usProcType,
                                              RRMM_GMM_PROC_FLAG_ENUM_UINT16 usProcFlag);

VOS_VOID NAS_GMM_SndRrmmGmmProcAns(VOS_VOID);


VOS_UINT32 GMM_CasGetSplitCycle(VOS_UINT8 ucSplitCode);

VOS_VOID NAS_GMM_SndRabmSysSrvChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode,
    VOS_BOOL                            bRatChangeFlg,
    VOS_BOOL                            bDataSuspendFlg,
    VOS_UINT8                           ucucRebuildRabFlag
);


VOS_VOID  NAS_GMM_SndGasGprsAuthFailNotifyReq(VOS_VOID);



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

#endif /* end of GmmCasSend.h*/
