/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndAt.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsSndAt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_APS_SNDAT_H__
#define __TAF_APS_SNDAT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "Ps.h"
#include "AtMnInterface.h"
#include "TafApsApi.h"

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


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID  TAF_APS_SndClearDsFlowCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_VOID  TAF_APS_SndDsFlowRptInd(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
);

/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_VOID  TAF_APS_SndGetDsFlowInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQryInfo
);
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */

VOS_VOID  TAF_APS_SndConfigDsFlowRptCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);
VOS_VOID TAF_APS_SndSetPdpCtxStateCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);
VOS_VOID  TAF_APS_SndSetPrimPdpCtxInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_VOID TAF_APS_SndSetSecPdpCtxInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_VOID  TAF_APS_SndSetTftInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_VOID TAF_APS_SndSetAnsModeInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_VOID TAF_APS_SndSetCgeqosCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_UINT32  TAF_APS_SndSetAuthDataInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_UINT32  TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
);

VOS_VOID  TAF_APS_SndGetDynamicSecPdpCtxInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
);

VOS_UINT32  TAF_APS_SndGetDynamicTftInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
);

VOS_VOID  TAF_APS_SndGetCgeqosrdpCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_UINT32  TAF_APS_SndGetPdpIpAddrInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

VOS_UINT32  TAF_APS_SndGetUmtsQosInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

VOS_UINT32  TAF_APS_SndGetUmtsQosMinInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

VOS_UINT32  TAF_APS_SndGetDynamicUmtsQosInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

VOS_UINT32  TAF_APS_SndGetPdpDnsInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);
/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)
VOS_VOID  TAF_APS_SndGetLtecsInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);
VOS_VOID  TAF_APS_SndGetCemodeInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);
VOS_VOID  TAF_APS_SndSetPdprofInfoCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode
);
#endif
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

VOS_UINT32  TAF_APS_SndSetCqosPriCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                        ulErrCode
);

VOS_VOID  TAF_APS_SndSetApDsFlowRptCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID  TAF_APS_SndGetApDsFlowRptCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_APDSFLOW_RPT_CFG_STRU          *pstRptCfg
);

VOS_VOID  TAF_APS_SndApDsFlowRptInd(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_APDSFLOW_REPORT_STRU           *pstRptInfo
);

VOS_VOID  TAF_APS_SndSetDsFlowNvWriteCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndGetDsFlowNvWriteCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_DSFLOW_NV_WRITE_CFG_STRU       *pstWriteNvCfg
);

VOS_UINT32  TAF_APS_SndSetPktCdataInactivityTimerLenCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_UINT32  TAF_APS_SndGetPktCdataInactivityTimerLenCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucTimeLen,
    VOS_UINT32                          ulErrCode
);
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

#endif /* end of TafApsSndAt.h */
