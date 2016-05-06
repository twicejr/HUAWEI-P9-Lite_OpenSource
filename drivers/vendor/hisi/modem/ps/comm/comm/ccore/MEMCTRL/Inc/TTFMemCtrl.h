/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TTFMemCtrl.h
  版 本 号   : 初稿
  作    者   : h00163499
  生成日期   : 2012年12月24日
  最近修改   :
  功能描述   : 该头文件定义了获取TTF内存地址的相关信息
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月24日
    作    者   : h00163499
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TTF_MEMCTRL_H__
#define __TTF_MEMCTRL_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TtfMemoryMap.h"
#include "vos.h"
#include "TtfNvInterface.h"
#include "NVIM_Interface.h"
#include "NasNvInterface.h"
#include "PsCommonDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* TTF内存类型初始化标记 */
#define TTF_MEMCTRL_TYPE_INIT_FLG                       (1)

/* TTF内存类型存在不存在标记 */
#define TTF_MEMCTRL_TYPE_EXIST_FLG                      (1)

/* TTF内存类型可见不可见标记 */
#define TTF_MEMCTRL_TYPE_VISIBLE_FLG                    (1<<1)

#define TTF_MEMCTRL_INVAILD_SIZE                        (0xFFFFFFFF)

#define TTF_MEMCTRL_SET_ADDR_INIT_FLG(flg)              (g_stTtfMemCtrlAddr.stTtfMemCtrlAddrComm.ucInitFlg = flg)

#define TTF_MEMCTRL_GET_ADDR_INIT_FLG()                 (g_stTtfMemCtrlAddr.stTtfMemCtrlAddrComm.ucInitFlg)

#define TTF_MEMCTRL_SET_TYPE_FLG(type, flg)             (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulAttribute |= flg)

#define TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(type)            (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulAttribute)

#define TTF_MEMCTRL_SET_TYPE_LEN(type, len)             (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulLen = len)

#define TTF_MEMCTRL_GET_TYPE_LEN(type)                  (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulLen)

#define TTF_MEMCTRL_SET_TYPE_OFFSET_BASE_LEN(type, len) (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulOffsetBaseLen = len)

#define TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(type)      (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulOffsetBaseLen)

/* 内存保护魔术字长度 */
#define TTF_MEM_MAGIC_NUM_LEN                           (32)

/*魔术字初始化值 */
#define TTF_MEM_MAGIC_NUM_VALUE                         (0x5A)

#define TTF_DYNAMIC_MEM_LEN_ZERO                        (0)

#define TTF_MEMCTRL_PID_INVAILD                         (0xFF)

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
/* 向BSP动态申请uncached内存, 申请成功返回实际地址，申请失败则返回VOS_NULL_PTR */
#define TTF_UNCACHED_MEM_BSP_ALLOC(ulTtfMemByteSize)   mdrv_cachedmem_alloc(ulTtfMemByteSize)
#else
/* 当前内存都是在C核的uncache内存，A核保证编译和lint OK */
#define TTF_UNCACHED_MEM_BSP_ALLOC(ulTtfMemByteSize)   kmalloc(ulTtfMemByteSize, GFP_KERNEL)
#endif
#define TTF_MEM_SET_DYNAMIC_INIT_ADDR_FLAG(ulInitFlag) \
    (g_stTtfMemDynamicCtrlEntity.ulTtfMemDynamicInitAddrFlag = (ulInitFlag))

#define TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG() \
    (g_stTtfMemDynamicCtrlEntity.ulTtfMemDynamicInitAddrFlag)

#define TTF_MEM_SET_SUPPORT_WCDMA(Modem, IsSupportWcdma) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportWcdma = (IsSupportWcdma))

#define TTF_MEM_SET_SUPPORT_GSM(Modem, IsSupportGsm) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportGsm = (IsSupportGsm))

#define TTF_MEM_SET_SUPPORT_LTE(Modem, IsSupportLte) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportLte = (IsSupportLte))

#define TTF_MEM_SET_SUPPORT_TDS(Modem, IsSupportTds) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportTds = (IsSupportTds))

#define TTF_MEM_SET_SUPPORT_1X(Modem, IsSupport1X) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupport1X = (IsSupport1X))

#define TTF_MEM_SET_SUPPORT_EVDO(Modem, IsSupportEvdo) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportEvdo = (IsSupportEvdo))

#define TTF_MEM_GET_DYNAMIC_ADDR_TYPE() \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[0])

#define TTF_MEM_SET_TTF_BASE_ADDR(ulTtfMemBaseAddr) \
    (g_stTtfMemDynamicCtrlEntity.pucTtfMemBaseAddr = (ulTtfMemBaseAddr))

#define TTF_MEM_GET_TTF_BASE_ADDR() \
    (g_stTtfMemDynamicCtrlEntity.pucTtfMemBaseAddr)

#define TTF_MEM_SET_TTF_TOTAL_LEN(ulDynamicTtfMemLen) \
    (g_stTtfMemDynamicCtrlEntity.ulMemTotalLen = (ulDynamicTtfMemLen))

#define TTF_MEM_GET_TTF_TOTAL_LEN() \
    (g_stTtfMemDynamicCtrlEntity.ulMemTotalLen)

#define TTF_DYNAMIC_MEM_SET_OFFSETBASE(type, OffsetBaseLen) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulOffsetBaseLen = OffsetBaseLen)

#define TTF_DYNAMIC_MEM_GET_OFFSETBASE(type) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulOffsetBaseLen)

#define TTF_DYNAMIC_MEM_SET_LEN(type, len) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulLen = len)

#define TTF_DYNAMIC_MEM_GET_LEN(type) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulLen)

#define TTF_DYNAMIC_MEM_SET_ATTRIBUTE(type, attribute) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulAttribute |= attribute)

#define TTF_DYNAMIC_MEM_GET_ATTRIBUTE(type) \
    (g_stTtfMemDynamicCtrlEntity.astTtfMemAddrType[type].ulAttribute)

#define WTTF_BBPMST_MAC_TB_HEAD_NUM                 (g_stBbpMstTBHeadInfo.ulTBHeadNum)
#define WTTF_BBPMST_MAC_TB_DATA_NUM                 (g_stBbpMstTBHeadInfo.ulTBHeadNum - g_stBbpMstTBHeadInfo.ulTBHeadReserved)

/* 头部区长度，单位:字节 */
#define WTTF_BBPMST_MAC_TB_HEAD_BUFF_LEN            ((WTTF_BBPMST_MAC_TB_HEAD_NUM) * (WTTF_MAC_HSDPA_TB_HEAD_SIZE))

/* 数据区长度，单位:字节 */
#define WTTF_BBPMST_MAC_TB_DATA_BUFF_LEN            ((WTTF_BBPMST_MAC_TB_DATA_NUM) * (WTTF_MAC_HSDPA_TB_DATA_SIZE))

#define TTF_DYNAMIC_MEM_CHECK_PERIOD_COUNTER        (1000)

/* 是否支持WCDMA */
#define TTF_MEM_GET_SUPPORT_WCDMA(Modem) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportWcdma)

/* 是否支持GSM */
#define TTF_MEM_GET_SUPPORT_GSM(Modem) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportGsm)

/* 是否支持LTE */
#define TTF_MEM_GET_SUPPORT_LTE(Modem) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportLte)

/* 是否支持TDS */
#define TTF_MEM_GET_SUPPORT_TDS(Modem) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportTds)

/* 是否支持1X */
#define TTF_MEM_GET_SUPPORT_1X(Modem) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupport1X)

/* 是否支持EVDO */
#define TTF_MEM_GET_SUPPORT_EVDO(Modem) \
    (g_stTtfMemDynamicCtrlEntity.astModelSupport[Modem].enSupportEvdo)

#define TTF_MEM_SET_W_RF_RXEVM_TEST_EN(IsTestEnable) \
    (g_stTtfMemDynamicCtrlEntity.ulWRfRxEVMTestEn = IsTestEnable)

#define TTF_MEM_GET_W_RF_RXEVM_TEST_EN() \
    (g_stTtfMemDynamicCtrlEntity.ulWRfRxEVMTestEn)

/*****************************************************************************
 枚举名    : TTF_MEM_PLATFORM_SUPPORT_WCDMA_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 是否支持wcdma
*****************************************************************************/
enum TTF_MEM_PLATFORM_SUPPORT_WCDMA_ENUM
{
    TTF_MEM_PLATFORM_SUPPORT_WCDMA  = 0,                /* 支持WCDMA */
    TTF_MEM_PLATFORM_NOT_SUPPORT_WCDMA,                 /* 不支持WCDMA */
    TTF_MEM_PLATFORM_SUPPORT_BUTT
};
typedef VOS_UINT8 TTF_MEM_PLATFORM_SUPPORT_WCDMA_ENUM8;

/*****************************************************************************
 枚举名    : TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 回调函数表示
*****************************************************************************/
enum TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM
{
    TTF_MEMCTRL_CALLBACK_FUNC_DRV  = 0,                /* 底软回调 */
    TTF_MEMCTRL_CALLBACK_FUNC_TTF,                     /* TTF回调 */

    TTF_MEMCTRL_CALLBACK_FUNC_BUTT
};
typedef VOS_UINT8 TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM_ENUM8;

/*****************************************************************************
 枚举名    : TTF_MEM_MSG_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 消息上报ID
*****************************************************************************/
enum TTF_MEM_MSG_ID_ENUM
{
    ID_TRACE_TTF_MEM_LEAK_IND               = 0X0315,   /* _H2ASN_MsgChoice TTF_MEM_LEAK_INFO_IND_MSG */
    ID_TRACE_TTF_MEM_ERR_IND                = 0x0316,   /* _H2ASN_MsgChoice TTF_MEM_ERROR_INFO_IND_STRU */

    ID_TRACE_TTF_MEM_BUTT
};
typedef VOS_UINT16 TTF_MEM_MSG_ID_ENUM_UINT16;

enum TTF_MEM_POOL_BLK_INDEX_ENUM
{
    TTF_MEM_POOL_BLK_INDEX_0    = 0,
    TTF_MEM_POOL_BLK_INDEX_1,
    TTF_MEM_POOL_BLK_INDEX_2,
    TTF_MEM_POOL_BLK_INDEX_3,

    TTF_MEM_POOL_BLK_INDEX_BUTT
};
typedef VOS_UINT32 TTF_MEM_POOL_BLK_INDEX_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8
 协议表格  :
 ASN.1描述 :
 枚举说明  : 回调函数表示
*****************************************************************************/
enum TTF_MEMCTRL_MODEL_SUPPORT_ENUM
{
    TTF_MEMCTRL_MODEL_SUPPORT_NO    = 0,                 /* 不支持 */
    TTF_MEMCTRL_MODEL_SUPPORT_YES,                       /* 支持 */

    TTF_MEMCTRL_MODEL_SUPPORT_BUTT
};
typedef VOS_UINT8 TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8;

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
结构名    : TTF_MEMCTRL_ADDR_TYPE_STRU
协议表格  : 无
ASN.1描述 : 无
结构说明  : TTF内存地址类型结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAttribute;        /* TTF内存地址类型属性 */
    VOS_UINT32                          ulLen;              /* TTF内存地址类型占用的长度 */
    VOS_UINT32                          ulOffsetBaseLen;    /* TTF内存地址类型基于基地址偏移的长度 */
} TTF_MEMCTRL_ADDR_TYPE_STRU;

/*****************************************************************************
结构名    : TTF_MEM_DYNAMIC_CRTL_ENTITY_STRU
协议表格  : 无
ASN.1描述 : 无
结构说明  : TTF动态内存申请管理实体结构
*****************************************************************************/
typedef struct
{
    /* 是否支持WCDMA表示 */
    TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8    enSupportWcdma;

    /* 是否支持GSM表示 */
    TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8    enSupportGsm;

    /* 是否支持LTE表示 */
    TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8    enSupportLte;

    /* 是否支持TDS表示 */
    TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8    enSupportTds;

    /* 是否支持CDMA 1X表示 */
    TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8    enSupport1X;

    /* 是否支持EVDO表示 */
    TTF_MEMCTRL_MODEL_SUPPORT_ENUM_ENUM8    enSupportEvdo;

    VOS_UINT8                               aucRsv[2];
} TTF_MEMCTRL_MODEL_SUPPORT_STRU;

/*****************************************************************************
结构名    : TTF_MEM_DYNAMIC_CRTL_ENTITY_STRU
协议表格  : 无
ASN.1描述 : 无
结构说明  : TTF动态内存申请管理实体结构
*****************************************************************************/
typedef struct
{
    /* 是否进行RxEvm测试，1为测试模式，0为正常模式 */
    VOS_UINT32                          ulWRfRxEVMTestEn;

    /* BBPMaster和TTF内存池初始化标志，防止重复调用初始化函数 */
    VOS_UINT32                          ulTtfMemDynamicInitAddrFlag;

    VOS_UINT32                          ulMemTotalLen;

    TTF_MEMCTRL_MODEL_SUPPORT_STRU      astModelSupport[MODEM_ID_BUTT];

    /* 用于存储内存块分配 */
    TTF_MEMCTRL_ADDR_TYPE_STRU          astTtfMemAddrType[TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT];

    /* 用于存储动态申请内存的基地址 */
    VOS_UINT8                          *pucTtfMemBaseAddr;
}TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU;


/*****************************************************************************
结构名    : TTF_MEMCTRL_ADDR_COMM_STRU
协议表格  : 无
ASN.1描述 : 无
结构说明  : TTF内存地址公共结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucInitFlg;          /* 初始化标记 */
    VOS_UINT8                           ucRcv[3];           /* 保留位 */
} TTF_MEMCTRL_ADDR_COMM_STRU;

/*****************************************************************************
结构名    : TTF_MEMCTRL_ADDR_TYPE_STRU
协议表格  : 无
ASN.1描述 : 无
结构说明  : TTF内存地址类型结构
*****************************************************************************/
typedef struct
{
    TTF_MEMCTRL_ADDR_COMM_STRU          stTtfMemCtrlAddrComm;
    TTF_MEMCTRL_ADDR_TYPE_STRU          astTtfMemCtrlAddrType[TTF_MEMCTRL_ADDR_TYPE_BUTT];
} TTF_MEMCTRL_ADDR_STRU;

/*****************************************************************************
 结构名    : TTF_MEM_ERROR_INFO_IND_STRU
 结构说明  : 动态申请内存被踩上报结构
 1.日    期   : 2014年3月19日
   作    者   : c00212970
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT16                              usMsgName;
    VOS_UINT8                               aucRsv[2];
    TTF_DYNAMIC_MEM_ADDR_TYPE_ENUM_UINT32   ulMagicNumFlag;
    VOS_UINT32                              aulMagicNum[TTF_MEM_MAGIC_NUM_LEN];
    TTF_MEMCTRL_ADDR_TYPE_STRU              astTtfMemAddrType[TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT];
} TTF_MEM_ERROR_INFO_IND_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern TTF_MEMCTRL_ADDR_STRU                   g_stTtfMemCtrlAddr;

/* BBPMST头部TB块信息 */
extern WTTF_MACDL_BBPMST_TB_HEAD_STRU          g_stBbpMstTBHeadInfo;

extern TTF_MEM_SOLUTION_CFG_NV_STRU            g_stTtfMemSolution;

/*  TTF动态内存维护实体 */
extern TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU        g_stTtfMemDynamicCtrlEntity;

/*****************************************************************************
  5 OTHERS定义
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
extern VOS_VOID TTF_MEMCTRL_ModelSupport(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_UINT32       TTF_MEMCTRL_CCORE_AddrInit(VOS_UINT32 ulPid);
extern VOS_UINT32       TTF_MEMCTRL_GetOffsetBaseLen(VOS_UINT32  ulType);
extern VOS_UINT_PTR     TTF_MEMCTRL_GetTypeAddr(VOS_UINT_PTR ulAddr, VOS_UINT32 ulType);
extern VOS_UINT32       TTF_MEMCTRL_DynamicAddrInit(VOS_UINT32 ulPid);
extern VOS_VOID         TTF_MEMCTRL_CheckTTFDynamicMem(VOS_UINT32 ulPid);
extern VOS_UINT_PTR     TTF_MEMCTRL_GetTtfInternalMemBaseAddr(VOS_VOID);
extern VOS_VOID         TTF_MEMCTRL_AddrPrint(VOS_VOID);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Fc.h */


