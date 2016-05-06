

#ifndef __ATCMDPACKETPROC_H__
#define __ATCMDPACKETPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "AtRnicInterface.h"

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
VOS_UINT32 AT_SetChdataPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryChdataPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetDhcpPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryDhcpPara_AppUser(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryDhcpPara_NdisUser(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryDhcpPara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_TestDhcpPara(VOS_UINT8 ucIndex);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT32 AT_SetDhcpv6Para(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryDhcpV6Para_AppUser(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryDhcpV6Para_NdisUser(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryDhcpv6Para(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestDhcpv6Para(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetApRaInfoPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryApRaInfoPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestApRaInfoPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetApLanAddrPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryApLanAddrPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_TestApLanAddrPara(VOS_UINT8 ucIndex);

#endif

VOS_UINT32  At_SetApConnStPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32  At_QryApConnStPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 AT_TestApConnStPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetApThroughputPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 At_QryApThroughputPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 AT_TestApThroughputPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetApEndPppPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetApDsFlowRptCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryApDsFlowRptCfgPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetDsFlowNvWriteCfgPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_QryDsFlowNvWriteCfgPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetImsPdpCfg(VOS_UINT8 ucIndex);

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

#endif /* end of AtCmdPacketProc.h */
