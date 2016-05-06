/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : GUCommInterface.h
  版 本 号   : 初稿
  作    者   : s00184266
  生成日期   : 2011年10月18日
  最近修改   :
  功能描述   : GAS、WAS、TDS公用头文件，由 GAS、WAS维护
  函数列表   :
  修改历史   :
  1.日    期   : 2011年10月18日
    作    者   : s00184266
    修改内容   : 创建文件

******************************************************************************/

#ifndef __GUCOMMINTERFACE_H__
#define __GUCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含                            
*****************************************************************************/
#include "PsTypeDef.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义 
*****************************************************************************/
/* 3GPP 协议上规定最大EUTRAN频点数 */
#define GURRC_LTE_ARFCN_MAX_NUM                             (8)
    
/* 3GPP 协议上规定最大UTRAN频点数 */
#define GURRC_UTRAN_ARFCN_MAX_NUM                           (16)
    
/* 3GPP 协议上规定最大GERAN频点数 */
#define GURRC_GERAN_ARFCN_MAX_NUM                           (32)

#define RRC_MAX_INTER_GSM_CELL_NUM                          (64)                /* UTRAN的GSM邻区的最大个数 */

#define RRC_MAX_INTER_GSM_MESSAGE_MAXLEN                    (512)               /* 切换时包含的GSM消息的最大长度 */
#define RRC_MAX_INTER_GSM_MESSAGE_NUM                       (4)                 /* 切换时包含的GSM消息的最大数目 */
#define GSM_CARRIER_MAXNUM                                  (8)                 /* TRRC/WRRC保存的GSM小区个数最大值 */

#define GSM_CLASSMARK2_MAX_LEN                              (4)                 /* R6协议中Classmark2最大长度,不包含TRRC或WRR自已填充的IEI */
#define GSM_CLASSMARK3_MAX_LEN                              (32)                /* R8协议中Classmark3最大长度,不包含TRRC或WRR自已填充的IEI */

/* EUTRAN 专有优先级最大个数 */
#define GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM                  (64)

/* UTRAN 专有优先级最大个数 */
#define GURRC_UTRAN_DEDICATED_PRI_MAX_NUM                   (64)

/*****************************************************************************
  3 枚举定义 
*****************************************************************************/
/*****************************************************************************
 枚举名     :RRC_GRR_BANDINDICATOR_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 2G小区频带指示
*****************************************************************************/
enum RRC_GRR_BANDINDICATOR_ENUM
{
    RRC_GRR_BANDINDICATOR_DCS1800       = 0,
    RRC_GRR_BANDINDICATOR_PCS1900       ,

    RRC_GRR_BANDINDICATOR_BUTT
};
typedef VOS_UINT16    RRC_GRR_BANDINDICATOR_ENUM_UINT16;

/*****************************************************************************
 枚举名     :GURRC_VALID_FLAG_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 通用是否存在标志
*****************************************************************************/
enum GURRC_VALID_FLAG_ENUM
{
    GURRC_FLAG_INVALID                  = 0,
    GURRC_FLAG_VALID                    ,

    GURRC_FLAG_BUTT
};
typedef VOS_UINT8    GURRC_VALID_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名     :RRC_GSM_GERAN_SYS_INFO_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : GSM小区系统消息类型枚举
*****************************************************************************/
typedef enum
{
    GERAN_SYS_INFO_TYPE_SI              = 0,
    GERAN_SYS_INFO_TYPE_PSI             = 1,
    GERAN_SYS_INFO_TYPE_BUTT
}RRC_GSM_GERAN_SYS_INFO_ENUM;
typedef VOS_UINT8 RRC_GSM_GERAN_SYS_INFO_ENUM_UINT8;

/*****************************************************************************
 枚举名     :RRC_GSM_BAND_INDICATOR_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : GSM小区频段指示枚举
*****************************************************************************/
typedef enum
{
    EN_DSC_1800_USED                    = 0,
    EN_PDS_1900_USED
}RRC_GSM_BAND_INDICATOR_ENUM;
typedef VOS_UINT32  RRC_GSM_BAND_INDICATOR_ENUM_UINT32;

/*****************************************************************************
 枚举名     :RRC_SINGAL_INFO_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 异系统互操作时携带的连接类型
*****************************************************************************/
typedef enum
{
    EN_NO_SIG_INF0                              = 0,                            /* 无信令连接 */
    EN_SIG_CS,                                                                  /* 只存在CS连接 */
    EN_SIG_PS,                                                                  /* 只存在PS连接 */
    EN_SIG_CSANDPS                                                              /* 同时存在CS和PS连接 */
}RRC_SINGAL_INFO_ENUM;
typedef VOS_UINT32  RRC_SINGAL_INFO_ENUM_UINT32;

/*****************************************************************************
 枚举名     :RRC_SINGAL_INFO_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 异系统互操作时指示GSM是否激活了加密
*****************************************************************************/
enum RRC_CIPHER_ACTIVE_ENUM
{
    EN_RRC_CIPHER_INACTIVE              = 0,
    EN_RRC_CIPHER_ACTIVE                = 1,
    EN_RRC_CIPHER_ACTIVE_BUTT
};
typedef VOS_UINT32  RRC_CIPHER_ACTIVE_ENUM_UINT32;

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
 结构名     :GURRC_LTE_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LTE优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;

    /* 取值范围0~9,0表示优先级最低，9表示优先级最高，其中1~8对应协议上的0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[1];
}GURRC_LTE_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :GURRC_LTE_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LTE专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    GURRC_LTE_PRI_INFO_STRU                                 astLteDPriInfo[GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM];
}GURRC_LTE_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :GURRC_UTRAN_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :UTRAN优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;

    /* 取值范围0~9,0表示优先级最低，9表示优先级最高，其中1~8对应协议上的0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[1];
}GURRC_UTRAN_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :GURRC_UTRAN_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :UTRAN专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    GURRC_UTRAN_PRI_INFO_STRU                               astUtranDPriInfo[GURRC_UTRAN_DEDICATED_PRI_MAX_NUM];
}GURRC_UTRAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :GURRC_GERAN_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :2G优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;

    /* 取值范围0~9,0表示优先级最低，9表示优先级最高，其中1~8对应协议上的0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved2[3];
}GURRC_GERAN_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :GURRC_GERAN_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :2G专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    GURRC_GERAN_PRI_INFO_STRU                               astGeranDPriInfo[GURRC_GERAN_ARFCN_MAX_NUM];
}GURRC_GERAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :GURRC_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    /**************************************************************************
     bitLteDPriInfoPresent: 表示stLteDPriInfo是否有效，1表示有效，0表示无效
     bitUtranDPriInfoPresent: 表示stUtranDPriInfo是否有效，1表示有效，0表示无效
     bitGeranDPriInfoPresent: 表示stGeranDPriInfo是否有效，1表示有效，0表示无效
     bitDPriTimerPresent: 表示ulTimerValue是否有效，1表示有效，0表示无效
    **************************************************************************/

    VOS_UINT32                                              bitLteDPriInfoPresent  : 1;
    VOS_UINT32                                              bitUtranDPriInfoPresent: 1;
    VOS_UINT32                                              bitGeranDPriInfoPresent: 1;
    VOS_UINT32                                              bitDPriTimerPresent    : 1;
    VOS_UINT32                                              bitSpare               : 28;

    /* EUTRAN 频点优先级信息 */
    GURRC_LTE_DEDICATED_PRI_INFO_STRU                       stLteDPriInfo;

    /* URTAN 频点优先级信息 */
    GURRC_UTRAN_DEDICATED_PRI_INFO_STRU                     stUtranDPriInfo;

    /* GSM 频点优先级信息 */
    GURRC_GERAN_DEDICATED_PRI_INFO_STRU                     stGeranDPriInfo;

    /* T3230,T322 ,T320定时器实际剩余时长，单位：毫秒,
            如果T3230,T322 ,T320定时器不存在，表示该数据无限大 */
    VOS_UINT32                                              ulTimerValue;
}GURRC_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :RRC_SAVE_CELL_INFO_FOR_GAS_ST
 协议表格  :
 ASN.1描述   :
 结构说明  :GSM小区的信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNCC;
    VOS_UINT32                          ulBCC;
    VOS_UINT32                          ulBcchArcfn;
    VOS_UINT32                          ulFreqBandInd;
    VOS_UINT32                          ulFlag;                                 /* 该标记用于指示lFNOffset、ulTimeAlignmt是否有数据，0:表示无数据 1: 表示有数据*/
    VOS_INT32                           lFNOffset;
    VOS_UINT32                          ulTimeAlignmt;

    VOS_INT16                           sRxlev;                                 /* G小区信号电平，单位是dBm,没有测到信号电平时赋值为RRWRR_INVALID_RXLEV */
    VOS_UINT8                           aucReserve1[2];                         /* 4字节对齐，保留 */

}RRC_SAVE_CELL_INFO_FOR_GAS_ST;

/*****************************************************************************
 结构名     :RRC_SAVEINFO_FOR_GAS_ST
 协议表格  :
 ASN.1描述   :
 结构说明  :异系统状态下保存的GSM小区结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGsmCellNum;                           /* GSM小区个数 */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       RrcSaveCellInfoForGas[GSM_CARRIER_MAXNUM];
}RRC_SAVEINFO_FOR_GAS_ST;

/*****************************************************************************
 结构名     :RRC_GSM_MESSAGE_ST
 协议表格  :
 ASN.1描述   :
 结构说明  :切换到GSM小区携带的GSM小区信息结构
*****************************************************************************/
typedef struct
{
     VOS_UINT16                         usBitLength;                            /* 空口消息中GSM消息的长度*/
     VOS_UINT8                          aucReserve[2];                         /* 4字节对齐，保留 */
     VOS_UINT8                          aucData[RRC_MAX_INTER_GSM_MESSAGE_MAXLEN];/* 空口消息中GSM消息的内容 */
}RRC_GSM_MESSAGE_ST;

/*****************************************************************************
 结构名     :RRC_HANDOVER_GSM_GPRS_INFO_ST
 协议表格  :
 ASN.1描述   :
 结构说明  :切换到GSM小区GPRS信息结构
*****************************************************************************/
typedef struct
{
    RRC_SAVEINFO_FOR_GAS_ST             stRrcSaveInfoForGas;
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enBandIndictor;
    VOS_UINT16                          usMessageNUM;                           /* 空口消息中GSM消息的个数 */
    VOS_UINT8                           aucReserve1[2];                         /* 4字节对齐，保留 */
    RRC_GSM_MESSAGE_ST                  stGsmGprsMsg[RRC_MAX_INTER_GSM_MESSAGE_NUM];    
}RRC_HANDOVER_GSM_GPRS_INFO_ST;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/








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

#endif /* end of GUCommInterface.h */
