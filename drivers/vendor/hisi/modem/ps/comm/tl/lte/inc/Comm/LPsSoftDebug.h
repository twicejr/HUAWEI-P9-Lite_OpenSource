/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : LPsSoftDebug.h
  版 本 号   : 初稿
  作    者   : 郑军燕 00148421
  生成日期   : 2010年8月26日
  最近修改   :
  功能描述   : 协议栈提供的软调信息
  函数列表   :
  修改历史   :
  1.日    期   : 2010年8月26日
    作    者   : 郑军燕 00148421
    修改内容   : 创建文件

******************************************************************************/

#ifndef __LPS_SOFTDEBUG_H__
#define __LPS_SOFTDEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "LUPAppItf.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define LPS_OM_IPV6_ADDR_LEN    16
#define LPS_OM_IPV4_ADDR_LEN     4
#define LPS_NAS_ESM_MAX_EPSB_NUM            (11)                /*最大承载数*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : LPS_LNAS_STA_ENUM
 枚举说明  : NAS状态
*****************************************************************************/
enum LPS_LNAS_STA_ENUM
{
    LPS_LNAS_STA_ATTACHED                 = 0,    /*NAS处于注册态*/
    LPS_LNAS_STA_DETACHED                 = 1,    /*NAS处于去注册态*/
    LPS_LNAS_STA_NO_SERVICE               = 2,    /*NAS处于覆盖区丢失状态*/
    LPS_LNAS_STA_OTHER                    = 3,    /*其他状态*/

    LPS_LNAS_STA_BUTT
};
typedef VOS_UINT32  LPS_LNAS_STA_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LPS_NAS_IP_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IP类型枚举
*****************************************************************************/
enum LPS_NAS_IP_TYPE_ENUM
{
    LPS_NAS_IP_TYPE_IPV4                 = 0x01,
    LPS_NAS_IP_TYPE_IPV6                 = 0x02,
    LPS_NAS_IP_TYPE_IPV4_IPV6            = 0x03,

    LPS_NAS_IP_TYPE_BUTT
};
typedef VOS_UINT8 LPS_NAS_IP_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LPS_LRRC_PROTOCOL_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RRC的协议状态
*****************************************************************************/
enum LPS_LRRC_PROTOCOL_STATE_ENUM
{
    LPS_LRRC_PROTOCOL_IDLE                   = 0,
    LPS_LRRC_PROTOCOL_CONNECTED              = 1,
    LPS_LRRC_PROTOCOL_STATE_BUTT
};
typedef VOS_UINT8 LPS_LRRC_PROTOCOL_STATE_ENUM_UINT8;

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
 结构名    : LPS_LRRC_S_TMSI_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : S-TMSI数据结构
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enIsExisted;           /* 用来指示S-TMSI是否存在, PS_TRUE:存在, PS_FALSE:不存在 */
    VOS_UINT8                           ucMmec;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulMTmsi;
}LPS_LRRC_S_TMSI_STRU;

/*****************************************************************************
 结构名    : LPS_LRRC_DEBUG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC软调信息结构
*****************************************************************************/
typedef struct
{
    LPS_LRRC_PROTOCOL_STATE_ENUM_UINT8          enRrcPtlState;   /* RRC协议状态 */
    VOS_UINT8                                   aucReserved[3];
    LPS_LRRC_S_TMSI_STRU                        stStmsi;         /* S-TMSI信息 */
}LPS_LRRC_DEBUG_INFO_STRU;

/*****************************************************************************
 结构名    : LPS_LNAS_IP_ADDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UE IP地址和PDN ID信息
*****************************************************************************/
typedef struct
{
    LPS_NAS_IP_TYPE_ENUM_UINT8          enIpType;   /*IP地址类型*/
    VOS_UINT8                           ucPndId;    /*缺省承载号*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucIpv4Addr[LPS_OM_IPV4_ADDR_LEN]; /*IPV4地址*/
    VOS_UINT8                           aucIpv6Addr[LPS_OM_IPV6_ADDR_LEN]; /*IPV6地址*/
}LPS_LNAS_IP_ADDR_STRU;


/*****************************************************************************
 结构名    : LPS_LNAS_UE_IP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UE IP地址信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                       ulPdnNum; /*有效缺省承载数目*/
    LPS_LNAS_IP_ADDR_STRU            astUeIpInfo[LPS_NAS_ESM_MAX_EPSB_NUM]; /*缺省承载的IP地址*/
}LPS_LNAS_UE_IP_INFO_STRU;


/*****************************************************************************
 结构名    : LPS_AUTOTEST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PS为自动化测试上报的信息结构
*****************************************************************************/
typedef struct
{
    L2_THROUGHPUT_ULDL_STAT_STRU                    stAppThoughputInfo;  /*APP发送给PDCP/APP接收到PDCP的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stPdcpThoughputInfo; /*PDCP发送给RLC/PDCP接收到RLC的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stRlcThoughputInfo;  /*RLC发送给MAC/RLC接收到MAC的统计信息*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stMacThoughputInfo;  /*MAC发送给RTT/MAC接收到RTT的统计信息*/
    LPS_LNAS_UE_IP_INFO_STRU                        stUeIpInfo;
    VOS_UINT32                                      ulNasStatus;
    VOS_UINT8                                       ucRrcStatus;
    VOS_UINT8                                       enIsExisted;
    VOS_UINT8                                       ucMmec;
    VOS_UINT8                                       aucReserved[1];
    VOS_UINT32                                      ulTmsi;
    /*VOS_UINT8                                       aucUeIP[4];
 */
    VOS_UINT32                                      ulIdleMemRes;

}LPS_AUTOTEST_INFO_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern LPS_LNAS_STA_ENUM_UINT32 LNAS_DEBUG_GetEmmSta(VOS_VOID);
extern VOS_VOID LNAS_DEBUG_GetUeIpInfo(LPS_LNAS_UE_IP_INFO_STRU* pstUeIpInfo);
extern  VOS_UINT32  LPS_LRRC_GetRrcSoftDebugInfo( LPS_LRRC_DEBUG_INFO_STRU *pstPsRrcSoftDebugInfo );
extern  VOS_VOID PrintLPsInfo(const LPS_AUTOTEST_INFO_STRU *pstAutoTestInfo);
extern  VOS_VOID GetLPsInfo(VOS_VOID);

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LPsSoftDebug.h */
