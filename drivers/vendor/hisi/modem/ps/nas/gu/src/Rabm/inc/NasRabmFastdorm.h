/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasRabmFastdorm.h
  版 本 号   : 初稿
  作    者   : m00217266
  生成日期   : 2014年6月18日
  最近修改   :
  功能描述   : NasRabmFastdorm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年6月18日
    作    者   : m00217266
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NAS_RABM_FASTDORM_H__
#define __NAS_RABM_FASTDORM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "rabminclude.h"
#include "AtRabmInterface.h"
#include "Nasrrcinterface.h"
#include "rabmext.h"
#include "RabmExtFunc.h"
#include "GmmRabmInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_RABM_SET_FD_ACT_FLG(FLAG)         ((g_stNasRabmFastDormCtx.ulActiveFlg) = (FLAG))

#define NAS_RABM_GET_FD_ACT_FLG()           (g_stNasRabmFastDormCtx.ulActiveFlg)

#define NAS_RABM_SET_FD_USER_DEF_NOFLUX_CNT(NoFluxCnt)  ((g_stNasRabmFastDormCtx.ulUserDefNoFluxCnt) = (NoFluxCnt))

#define NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT()       (g_stNasRabmFastDormCtx.ulUserDefNoFluxCnt)

#define NAS_RABM_SET_FD_CURR_NOFLUX_CNT(NoFluxCnt)  ((g_stNasRabmFastDormCtx.ulCurrNoFluxCnt) = (NoFluxCnt))

#define NAS_RABM_GET_FD_CURR_NOFLUX_CNT()   (g_stNasRabmFastDormCtx.ulCurrNoFluxCnt)

#define NAS_RABM_SET_FD_OPERATION_TYPE(FdOpType)   ((g_stNasRabmFastDormCtx.enFastDormOperationType) = (FdOpType))

#define NAS_RABM_GET_FD_OPERATION_TYPE()   (g_stNasRabmFastDormCtx.enFastDormOperationType)

#define NAS_RABM_GET_FD_STATUS()   (g_stNasRabmFastDormCtx.enCurrFastDormStatus)

#define NAS_RABM_SET_FD_STATUS(FdStatus)   ((g_stNasRabmFastDormCtx.enCurrFastDormStatus) = (FdStatus))

#define NAS_RABM_INC_FD_ULDATA_CNT()     (g_stNasRabmFastDormCtx.ulUlDataCnt++)

#define NAS_RABM_INC_FD_DLDATA_CNT()       (g_stNasRabmFastDormCtx.ulDlDataCnt++)

#define NAS_RABM_GET_FD_ULDATA_CNT()    (g_stNasRabmFastDormCtx.ulUlDataCnt)

#define NAS_RABM_GET_FD_DLDATA_CNT()    (g_stNasRabmFastDormCtx.ulDlDataCnt)

#define NAS_RABM_CLR_FD_ULDATA_CNT()    ((g_stNasRabmFastDormCtx.ulUlDataCnt) = (0))

#define NAS_RABM_CLR_FD_DLDATA_CNT()    ((g_stNasRabmFastDormCtx.ulDlDataCnt) = (0))

#define NAS_RABM_SET_FD_REL_RRC_EXEC_FLG()  (g_stNasRabmFastDormCtx.ulRelRrcExecFlg = VOS_TRUE)
#define NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG()  (g_stNasRabmFastDormCtx.ulRelRrcExecFlg = VOS_FALSE)
#define NAS_RABM_GET_FD_REL_RRC_EXEC_FLG()  (g_stNasRabmFastDormCtx.ulRelRrcExecFlg)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_RABM_FASTDORM_STATUS_ENUM
 枚举说明  : FAST DORMANCY相关的运行状态
 1.日    期   : 2011年10月17日
   作    者   : h44270
   修改内容   : 新建
 2.日    期   : 2014年06月13日
   作    者   : m00217266
   修改内容   : modify for FD Optimize
*****************************************************************************/
enum NAS_RABM_FASTDORM_STATUS_ENUM
{
    NAS_RABM_FASTDORM_INIT,                                                     /* 当前FAST DORMANCY在初始状态 */
    NAS_RABM_FASTDORM_DETECT,                                                   /* 当前FAST DORMANCY在检测状态，流量统计定时器已经启动，等待无流量时间达到AT命令设置时长 */
    NAS_RABM_FASTDORM_EXEC,                                                     /* 当前FAST DORMANCY处于检测GMM状态，准备发起FD */
    NAS_RABM_FASTDORM_BUTT
};
typedef VOS_UINT32 NAS_RABM_FASTDORM_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_RABM_OM_MSG_ID_ENUM_UINT32
 结构说明  : RABM发送给OM的可维可测消息
 1.日    期   : 2011年10月32日
   作    者   : h44270
   修改内容   : 新建，RABM发送给OM的可维可测消息ID枚举
*****************************************************************************/
enum NAS_RABM_OM_MSG_ID_ENUM
{
    /* MMC发送给OM的消息 */
    NAS_RABM_OM_MSG_FASTDORM_STATUS = 0x1111,                                   /*_H2ASN_MsgChoice  NAS_MMC_LOG_FSM_INFO_STRU */
    NAS_RABM_OM_MSG_BUTT
};
typedef VOS_UINT32 NAS_RABM_OM_MSG_ID_ENUM_UINT32;


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
 结构名    : NAS_RABM_FASTDORM_CTX_STRU
 结构说明  : RABM中保存与FAST DORMANCY相关的参数
  1.日    期   : 2011年10月18日
    作    者   : h44270
    修改内容   : 新建

  2.日    期   : 2011年12月20日
    作    者   : o00132663
    修改内容   : PS融合项目，为FD增加简单计数器

  3.日    期   : 2015年1月9日
    作    者   : A00165503
    修改内容   : DTS2014123000271: RRC释放流程增加停止控制
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulActiveFlg;
    VOS_UINT32                              ulCurrNoFluxCnt;                    /* 无流量时长计数，以秒为单位 */
    AT_RABM_FASTDORM_OPERATION_ENUM_UINT32  enFastDormOperationType;            /* 当前FAST DORMANCY的操作方式 */
    VOS_UINT32                              ulUserDefNoFluxCnt;                 /* 用户定义的无流量时长要求 */
    NAS_RABM_FASTDORM_STATUS_ENUM_UINT32    enCurrFastDormStatus;               /* 存储当前的FAST DORMANCY运行状态 */
    VOS_UINT32                              ulUlDataCnt;                        /* 上行数据计数器 */
    VOS_UINT32                              ulDlDataCnt;                        /* 下行数据计数器 */

    VOS_UINT32                              ulRelRrcExecFlg;

} NAS_RABM_FASTDORM_CTX_STRU;


/*****************************************************************************
 结构名    : NAS_RABM_LOG_FASTDORM_INFO_STRU
 结构说明  : RABM中用于定位的上下文信息
 1.日    期   : 2011年10月32日
   作    者   : h44270
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                   */ /*_H2ASN_Skip*/
    NAS_RABM_FASTDORM_CTX_STRU          stFastDormCtx;

    NAS_RABM_TIMER_STATUS_ENUM_UINT8    aenTimerState[3];
    VOS_UINT8                           ucReserved;

}NAS_RABM_LOG_FASTDORM_INFO_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 全局变量声明
*****************************************************************************/
extern NAS_RABM_FASTDORM_CTX_STRU              g_stNasRabmFastDormCtx;


/*****************************************************************************
  11 函数声明
*****************************************************************************/

extern VOS_UINT8 NAS_RABM_CheckPdpRbStatus(VOS_VOID);
extern VOS_UINT8 NAS_RABM_CheckGmmAndRabmStatus(
            GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus
        );
extern VOS_VOID NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(
           AT_RABM_FASTDORM_OPERATION_ENUM_UINT32                enAtFastDormType,
           RRC_FASTDORM_START_TYPE_ENUM_UINT32                 *penWrrFastDormType
       );
extern VOS_VOID NAS_RABM_InitFastDormCtx(VOS_VOID);
extern VOS_VOID NAS_RABM_ProcFastDormStatusInTransfer( VOS_VOID );
extern VOS_VOID NAS_RABM_AbortRelRrcProcedure(VOS_VOID);
extern VOS_VOID NAS_RABM_RcvAtFastDormStartReq(
           AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvAtFastDormStopReq(
           AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvGetFastDormParaReq(
           AT_RABM_QRY_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvReleaseRrcReq(
           AT_RABM_RELEASE_RRC_REQ_STRU *pstMsg
       );
extern VOS_VOID NAS_RABM_RcvSetFastDormParaReq(
           AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvWasFastDormInfoInd(
           struct MsgCB                       *pMsg
       );
extern VOS_VOID NAS_RABM_ResumeFastDorm(VOS_VOID);
extern VOS_VOID NAS_RABM_RevertFastDormEnv(VOS_VOID);

extern VOS_VOID NAS_RABM_SuspendFastDorm(VOS_VOID);
extern VOS_VOID NAS_RABM_SysModeChgProcFastDorm(
           GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
           GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
       );
extern VOS_VOID NAS_RABM_FastDormFluxDetectExpired(VOS_VOID);
extern VOS_VOID NAS_RABM_FastDormRetryExpired(VOS_VOID);
extern VOS_VOID NAS_RABM_FastDormWaitGmmProcQryRsltExpired(VOS_VOID);

extern VOS_VOID NAS_RABM_SndWasFastDormStartReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32 enOptFlag
);

extern VOS_VOID NAS_RABM_SndWasFastDormStopReq(VOS_VOID);

extern VOS_VOID NAS_RABM_SndGmmMmlProcStatusQryReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32 enOptFlag
);

extern VOS_VOID NAS_RABM_SndAtSetFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
);
extern VOS_VOID NAS_RABM_SndAtQryFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucRslt
);

extern VOS_VOID  NAS_RABM_SndOmFastdormStatus(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasRabmFastdorm.h */

