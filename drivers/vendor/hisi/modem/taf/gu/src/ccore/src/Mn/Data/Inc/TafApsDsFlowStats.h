/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsDsFlowStats.h
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : TafApsDsFlowStats.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSDSFLOWSTATS_H__
#define __TAFAPSDSFLOWSTATS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "Ps.h"
#include "TafApsApi.h"
#include "ApsCdsInterface.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "cttf_1x_rlp_bo_pif.h"
#include "cnas_cttf_hrpd_pa_pif.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_APS_CDATA_NO_DATA_TIME_LEN_PER_TIMES                    (20)   /* 单位 毫秒 */

#define TAF_APS_CDATA_EVDO_NO_DATA_TIME_LEN_PER_TIMES               (80)   /* 单位 毫秒 */

/* 64位长整型运算，加法 : rst = argA + argB */
#define TAF_APS_BIT64_ADD(rstHi, rstLo, argAHi, argALo, argBHi, argBLo) \
    { \
        if ((argALo) > (0xFFFFFFFF - (argBLo))) \
        { \
            (rstHi) = (argAHi) + ((argBHi) + 1); \
        } \
        else \
        { \
            (rstHi) = (argAHi) + (argBHi); \
        } \
        (rstLo) = (argALo) + (argBLo); \
    }


/* 64位长整型运算，减法 : rst = argA - argB */
/* Notes: we assumed argA always great than or equal to argB */
#define TAF_APS_BIT64_SUB(rstHi, rstLo, argAHi, argALo, argBHi, argBLo) \
    { \
        if ((argALo) < (argBLo)) \
        { \
            (rstHi) = (argAHi) - ((argBHi) + 1); \
        } \
        else \
        { \
            (rstHi) = (argAHi) - (argBHi); \
        } \
        (rstLo) = (argALo) - (argBLo); \
    }


/* 64位长整型运算，比较 : rst = (argA > argB) ? GREAT : ((argA == argB) ? EQUAL : LESS) */
#define TAF_APS_BIT64_COMPARE(argAHi, argALo, argBHi, argBLo, result) \
    {\
        if ((argAHi) > (argBHi))\
        {\
            result = TAF_APS_BIT64_GREAT;\
        }\
        else if (((argAHi) == (argBHi)) && ((argALo) > (argBLo)))\
        {\
            result = TAF_APS_BIT64_GREAT;\
        }\
        else if (((argAHi) == (argBHi)) && ((argALo) == (argBLo)))\
        {\
            result = TAF_APS_BIT64_EQUAL;\
        }\
        else\
        {\
            result = TAF_APS_BIT64_LESS;\
        }\
    }


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名称  : TAF_APS_BIT64_CMP_RSLT_ENUM
 枚举说明  : 64位整型比较结果
*****************************************************************************/
enum TAF_APS_BIT64_CMP_RSLT_ENUM
{
    TAF_APS_BIT64_GREAT                 = 0,
    TAF_APS_BIT64_EQUAL,
    TAF_APS_BIT64_LESS
};
typedef VOS_UINT32 TAF_APS_BIT64_CMP_RSLT_ENUM_UINT32;


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

VOS_VOID  TAF_APS_StartDsFlowStats(
    VOS_UINT8                           ucRabId
);

VOS_VOID  TAF_APS_StopDsFlowStats(
    VOS_UINT8                           ucRabId
);
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */

VOS_VOID  TAF_APS_QryDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQryInfo,
    VOS_UINT8                           ucRabId
);

VOS_VOID  TAF_APS_QryAllRabDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU         *pstTotalDsFlowQryInfo
);
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

VOS_VOID  TAF_APS_ClearDsFlowStats(
    VOS_UINT8                           ucRabId
);

VOS_VOID  TAF_APS_ClearAllRabDsFlowStats( VOS_VOID );

VOS_VOID  TAF_APS_StartDsFlowRpt( VOS_VOID );

VOS_VOID  TAF_APS_StopDsFlowRpt( VOS_VOID );

VOS_VOID TAF_APS_QryDsFlowReportInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
);

VOS_VOID TAF_APS_QryAllRabDsFlowReportInfo(
    TAF_DSFLOW_REPORT_STRU             *pstTotalDsFlowRptInfo
);
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_VOID  TAF_APS_GetCurrentFlowInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_INFO_STRU               *pstCurrentFlowInfo
);
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

VOS_VOID  TAF_APS_UpdateAllRabCurrentFlowInfo( VOS_VOID );

VOS_UINT32  TAF_APS_CheckIfActiveRabIdExist( VOS_VOID );

VOS_VOID  TAF_APS_CalcDsflowRate(
    VOS_UINT32                          ulStartHigh,
    VOS_UINT32                          ulStartLow,
    VOS_UINT32                          ulEndHigh,
    VOS_UINT32                          ulEndLow,
    VOS_UINT32                          ulPeriod,
    VOS_UINT32                         *pulRate
);

VOS_VOID TAF_APS_ClearApDsFlowStats(VOS_VOID);
VOS_VOID TAF_APS_ProcApDsFlowRpt(VOS_VOID);

VOS_VOID TAF_APS_ReleaseDfs(VOS_VOID);

VOS_UINT32 TAF_APS_FindDfsReqValue(
    VOS_UINT32                         *pulReqValue,
    VOS_UINT32                          ulDLRate,
    VOS_UINT32                          ulULRate
);

VOS_UINT32 TAF_APS_CheckIfMinDdrBand(
    VOS_UINT32                          ulReqValue
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_APS_ProcRlpDataStatusCb(
    const RLPITF_1X_RLP_DATA_STAT_STRU       * const pstRlpDataStat
);

VOS_VOID TAF_APS_ProcEvdoRlpDataStatusCb(
    PS_BOOL_ENUM_UINT8                  enFlowActivity
);
#endif


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

#endif /* end of TafApsDsFlowStats.h */
