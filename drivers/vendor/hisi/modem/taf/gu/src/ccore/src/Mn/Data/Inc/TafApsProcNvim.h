

#ifndef __TAFAPSPROCNVIM_H__
#define __TAFAPSPROCNVIM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafApsCtx.h"


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

VOS_VOID  TAF_APS_ReadDsFlowInfoFromNv(
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx
);
VOS_VOID  TAF_APS_ClearDsFlowInfoInNv( VOS_VOID );
VOS_VOID  TAF_APS_SaveDsFlowInfoToNv( VOS_VOID );

VOS_VOID TAF_APS_ReadPdpActLimitFlgFromNv(VOS_VOID);

VOS_VOID TAF_APS_ReadDsflowRateConfigFromNv(TAF_APS_SWITCH_DDR_RATE_INFO_STRU *pstSwitchDdrInfo);

VOS_VOID TAF_APS_Recorrect_ProfileNum(
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU     *pstDfsProfile,
    VOS_UINT32                              ulProfileNum);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_APS_ReadPktCdataInactivityTimeLenFromNv(VOS_VOID);


VOS_VOID TAF_APS_Read1xDataSoCfgNvim(VOS_VOID);

VOS_VOID TAF_APS_ReadCdataDiscingParaCfgFromNv(VOS_VOID);
VOS_VOID TAF_APS_ReadPppAuthInfoFromCardNv( VOS_VOID );


VOS_VOID TAF_APS_ReadCdataEhrpdAutoAttachFlagFromNv(VOS_VOID);

VOS_VOID TAF_APS_ReadCdataUlNdisFilterVaildFlagFromNv(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_ReadPdnTeardownPolicyNV(VOS_VOID);
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

#endif /* end of TafApsProcNvim.h */
