

#ifndef __ATINIT_H__
#define __ATINIT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtCtx.h"
#include "AtInputProc.h"
#if (VOS_LINUX == VOS_OS_VER)
#if (defined(CONFIG_BALONG_SPE))
#include "mdrv_spe_wport.h"
#endif /* CONFIG_BALONG_SPE */
#else
#include "Linuxstub.h"
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
/* 多时隙等级最大宏定义 */
#define AT_GAS_GRR_MULTISLOT_CLASS_MAX  (12)

#if (defined(CONFIG_BALONG_SPE))
/* 设置SPE端口参数 */
#define AT_SET_SPE_PORT_ATTR_BYPASS_MODE(pstAttr)\
            ((spe_wport_attr_t *)(pstAttr))->is_bypass_mode = 1;\
            ((spe_wport_attr_t *)(pstAttr))->is_ipf_port    = 1;\
            ((spe_wport_attr_t *)(pstAttr))->net_dev        = VOS_NULL_PTR
#endif


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum AT_GAS_HIGH_MULTISLOT_CLASS_ENUM
{
    AT_GAS_HIGH_MULTISLOT_CLASS_0,
    AT_GAS_HIGH_MULTISLOT_CLASS_1,
    AT_GAS_HIGH_MULTISLOT_CLASS_2,
    AT_GAS_HIGH_MULTISLOT_CLASS_3,

    AT_GAS_HIGH_MULTISLOT_CLASS_BUTT
};
typedef VOS_UINT8 AT_GAS_HIGH_MULTISLOT_CLASS_ENUM_UINT8;


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
 结构名    : AT_NV_UE_CAPABILITY_STRU
 协议表格  : 无
 结构说明  : 存储在NV中的UE能力信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved1[11];                       /* 留作以后扩展 */
    VOS_UINT8                           ucAsRelIndicator;                       /* Access Stratum Release Indicator             */

    VOS_UINT8                           ucHSDSCHSupport;                        /* 是否支持enHSDSCHSupport的标志                */
    VOS_UINT8                           ucHSDSCHPhyCategory;                    /* 支持HS-DSCH物理层的类型标志                  */

    VOS_UINT8                           ucMacEhsSupport;
    VOS_UINT8                           ucHSDSCHPhyCategoryExt;
    VOS_UINT8                           ucMultiCellSupport;                     /* 是否支持 Multi cell support,如果支持MultiCell,Ex2存在 */
    VOS_UINT8                           ucHSDSCHPhyCategoryExt2;                /* HS-DSCH physical layer category extension 2 */

    VOS_UINT8                           aucReserved2[17];                       /* 留作以后扩展 */

    VOS_UINT8                           ucHSDSCHPhyCategoryExt3;                /* HS-DSCH physical layer category extension 3 */
    VOS_UINT8                           ucDcMimoSupport;                        /* 是否支持DC+MIMO */

    VOS_UINT8                           aucReserved3[3];                        /* 留作以后扩展 */

} AT_NV_UE_CAPABILITY_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID AT_ReadPlatformNV(VOS_VOID);
extern VOS_VOID AT_ReadClientConfigNV(VOS_VOID);

extern VOS_VOID AT_GetCpmsMtMem(
           MODEM_ID_ENUM_UINT16                enModemId,
           MN_MSG_MEM_STORE_ENUM_U8           *penSmMemStore
       );
extern AT_CGSMS_SEND_DOMAIN_ENUM_U8 AT_SendDomainNvimToProto(
    VOS_UINT32                           ulNvimSendDomain
    );
extern VOS_VOID AT_ReadSmsSendDomainNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsMeStorageInfoNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsClass0TailorNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsNV(VOS_VOID);


extern VOS_VOID  AT_ReadRoamCapaNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsFilterCfgNv( VOS_VOID );
extern VOS_VOID  AT_ReadSystemAppConfigNV(VOS_VOID);

extern VOS_VOID AT_ReadAtDislogPwdNV(VOS_VOID);
extern VOS_VOID AT_ReadAtRightPasswordNV(VOS_VOID);
extern VOS_VOID AT_ReadAtDissdPwdNV(VOS_VOID);
extern VOS_VOID AT_ReadNotSupportRetValueNV(VOS_VOID);
extern VOS_VOID AT_ReadE5NV(VOS_VOID);

extern VOS_UINT32 AT_IsAbortCmdCharValid(
    VOS_UINT8                          *pucAbortCmdChar,
    VOS_UINT32                          ulLen
    );
extern VOS_VOID AT_ReadAbortCmdParaNV(VOS_VOID);

extern VOS_VOID AT_ReadSysNV(VOS_VOID);

extern VOS_VOID AT_ReadCellSignReportCfgNV( VOS_VOID );

extern VOS_VOID AT_ReadPppDialErrCodeNV( VOS_VOID );
extern VOS_VOID AT_ReadReportRegActFlgNV( VOS_VOID );
extern VOS_VOID AT_ReadCregAndCgregCiFourByteRptNV( VOS_VOID );
#if (FEATURE_ON == FEATURE_IPV6)
extern VOS_VOID AT_ReadIpv6CapabilityNV( VOS_VOID );
extern VOS_VOID AT_ReadIpv6AddrTestModeCfgNV(VOS_VOID);
#endif
extern VOS_VOID AT_ReadDialConnectDisplayRateNV(VOS_VOID);

extern VOS_VOID  AT_ReadPsNV(VOS_VOID);
extern VOS_VOID  AT_ReadCsNV(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID AT_ReadLTENV(VOS_VOID);
#endif

extern VOS_UINT32 AT_ValidateWasCategory(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT32 AT_ValidateWasCategoryExt(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT32 AT_ValidateWasCategoryExt2(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT32 AT_ValidateWasCategoryExt3(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT8 AT_GetWasDefaultCategory(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
    );
extern VOS_UINT8 AT_CalcWasCategory(
                                    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
                                    );

extern VOS_VOID AT_ReadWasCapabilityNV(VOS_VOID);
extern VOS_VOID AT_ReadGasCapabilityNV(VOS_VOID);

extern VOS_UINT32  AT_ReadPhyNV(VOS_VOID);

extern VOS_VOID  AT_ReadNV(VOS_VOID);

extern VOS_VOID AT_InitDeviceCmd(VOS_VOID);

extern VOS_VOID AT_UsbSwitchGwMode(VOS_VOID);
extern VOS_VOID AT_InitPort(VOS_VOID);
extern VOS_VOID AT_InitStk(VOS_VOID);
extern VOS_VOID AT_InitPara(VOS_VOID);

#if (defined(CONFIG_BALONG_SPE))
VOS_VOID AT_SpeInit(VOS_VOID);
#endif

extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);

VOS_VOID AT_ReadSsNV( VOS_VOID );

VOS_VOID AT_ReadUartCfgNV(VOS_VOID);

VOS_VOID AT_UsbEnableCB(VOS_VOID);

VOS_VOID AT_UsbDisableCB(VOS_VOID);

VOS_VOID AT_HsicEnableCB(VOS_VOID);

VOS_VOID AT_HsicDisableCB(VOS_VOID);

VOS_VOID AT_ReadPortBuffCfgNV(VOS_VOID);


VOS_VOID AT_WriteCcpuResetRecordNvim(VOS_UINT8 ucCcpuResetFlag);


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

#endif /* end of AtInit.h */

