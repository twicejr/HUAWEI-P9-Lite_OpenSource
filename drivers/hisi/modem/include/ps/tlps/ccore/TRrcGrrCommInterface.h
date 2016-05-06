/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TRrcGrrCommInterface.h
  Description     : TD&G RRC模块公共信息头文件
  History         :
      1.xuruimei       2011-10-10   Draft Enact

******************************************************************************/

#ifndef __TRRC_GRRCOMMINTERFACE_H__
#define __TRRC_GRRCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "GUCommInterface.h"

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/

/* TDS测量GSM小区的最大数 */
#define TRRC_GRR_GERAN_ARFCN_MAX_NUM                        (32)

/* GSM测量TDS载波的单一载波上最大小区数 */
#define TRRC_GRR_MAX_UTRAN_CELL_PER_FREQ_NUM                (32)

/* GAS请求 TDS测量小区列表中频点最大个数，实际上GAS最多下发3个被测频点，而TD最多
测9个频点，这个宏的值仍沿用 9 */
#define TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM              (9)

/* TDS 支持最大的BSIC VERFIED 小区个数*/
#define TRRC_GRR_GERAN_CELL_FOR_BSIC_MAX_NUM                (8)

/* TDS到GSM CCO消息中携带的系统消息最大个数 */
#define TRRC_RR_MAX_GERAN_SI_CNT                            (8)

/* TDS到GSM CCO消息中携带的系统消息最大字节数 */
#define TRRC_RR_MAX_GERAN_SI_LEN                            (23)

/* GERAN CS UE 能力编码后最大长度 */
#define TRRC_GRR_UE_CAP_GEREN_CS_MAX_LEN                    (128)

/* GERAN PS UE 能力编码后最大长度 */
#define TRRC_GRR_UE_CAP_GEREN_PS_MAX_LEN                    (128)

/* TD->G 出服务区搜网请求的最大PLMN列表 */
#define TRRC_GRR_MAX_AVAIL_PLMN_NUM                         (18)

/* TD->G 出服务区搜网，G回复的最大PLMN列表 */
#define TRRC_GRR_MAX_HIGH_PLMN_NUM                          (16)                /* 高质量的PLMN的最大个数 */
#define TRRC_GRR_MAX_LOW_PLMN_NUM                           (16)                /* 低质量的PLMN的最大个数 */

/* channel release GAS最多携带96个小区 */
#define RR_TRRC_MAX_UTRAN_TDD_CELL_NUM                      (96)

/* INTER_RAT_HANDOVER_INFO 长度, 最长250字节 */
#define RR_TRRC_INTER_RAT_HANDOVER_INFO_LEN                 (250)

/* TD->G cell resel或者cell change order携带的小区信息中信号强度无效值 */
#define RR_TRRC_INVALID_RXLEV                               (0X00FF)

/* G作为主模测量Td-scmda小区，TRRC上报的测量结果无效值 */
#define TRRC_GRR_INVALID_RSCP                               (-131 * 8)

#define TRRC_GRR_INVALID_RSSI                               (-102 * 8)
#define TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM              (9)
#define TRRC_GRR_MAX_FR_FREQ_NUM                            (9)
#define TRRC_GRR_LOWEST_FR_RSCP_THRES                       (-116)
#define TRRC_GRR_HIGHEST_FR_RSCP_THRES                      (-26)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM
 协议表格  :
     44060-8.4.2
     Access is denied in the new cell (i.e., the mobile station receives an
     IMMEDIATE ASSIGNMENT REJECT, a PACKET ASSIGNMENT REJECT or, in a UTRAN
     cell, an RRC CONNECTION REJECT message or fails to establish an RRC
     connection in an E-UTRAN cell as specified in 3GPP TS 36.331).
     Cause: "Immediate Assign Reject or Packet Access Reject on target cell";
 ASN.1描述 :
 枚举说明  : GU与TDS之间CELL RESEL, CCO结果
*****************************************************************************/
enum TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM
{
    TRRC_GRR_CELL_RESEL_CCO_SUCC                              = 0,
    TRRC_GRR_CELL_RESEL_CCO_CELL_BARRED                      ,                  /* CELL BARRED */
    TRRC_GRR_CELL_RESEL_CCO_CELL_FORBID                      ,                  /* CELL 被 FORBID*/
    TRRC_GRR_CELL_RESEL_CCO_NOT_EPLMNS                       ,                  /* CELL携带的PLMN信息没有属于RPLMN和EPLMNS */
    TRRC_GRR_CELL_RESEL_CCO_ACCESS_NOT_PERMIT                ,                  /* CELL ACCESS 受限 */
    TRRC_GRR_CELL_RESEL_CCO_CONNECTION_REJECT                ,                  /* 立即指派被拒或连接被拒，该原因值只用于CCO流程 */
    TRRC_GRR_CELL_RESEL_CCO_UNSPECIFIC                       ,                  /* 其他未定义的错误 */
    TRRC_GRR_CELL_RESEL_S_OR_C1_CHECK_FAIL                   ,                  /*重选乒乓*/

    TRRC_GRR_CELL_RESEL_CCO_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TRRC_GRR_REDIRECTED_SUCC
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS与TDS之间REDIRECTED结果
*****************************************************************************/
enum TRRC_GRR_REDIRECTED_RESULT_ENUM
{
    TRRC_GRR_REDIRECTED_SUCC                              = 0,
    TRRC_GRR_REDIRECTED_FAIL                                 ,

    TRRC_GRR_REDIRECTED_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TRRC_GURRC_HANDOVER_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS与TDS之间HANDOVER 结果
*****************************************************************************/
enum TRRC_GRR_HANDOVER_RESULT_ENUM
{
    TRRC_GRR_HANDOVER_RESULT_SUCC                         = 0,

    /* 以下原因值用于TDS向GAS回复Handover失败原因 */
    TRRC_GRR_HANDOVER_RESULT_FREQ_NOT_IMPLEMENTED            ,                  /* HO消息配置了不支持的配置 */
    TRRC_GRR_HANDOVER_RESULT_CONFIG_UNKNOWN                  ,                  /* HO消息的配置无法找到 */
    TRRC_GRR_HANDOVER_RESULT_INVALID_CONFIG                  ,                  /* HO消息是无效的配置 */
    TRRC_GRR_HANDOVER_RESULT_RRC_CONNECT_FAILURE             ,                  /* HO做同步失败 */

    /* 以下原因值用于GAS向TDS回复handover失败原因 */
    TRRC_GRR_HANDOVER_RESULT_PROTOCOL_ERROR                  ,                  /* Handover command解码后异常 */
    TRRC_GRR_HANDOVER_RESULT_UNSUPORTED_CONFIGURATION        ,                  /* 不支持该频点/非法配置 */
    TRRC_GRR_HANDOVER_RESULT_PHY_CHANNEL_FAIL                ,                  /* 物理信道建立失败  */
    TRRC_GRR_HANDOVER_RESULT_MESSAGE_INVALID                 ,                  /* 切换的消息无效 */

    TRRC_GRR_HANDOVER_RESULT_UNSPECIFIC,

    TRRC_GRR_HANDOVER_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TRRC_GRR_VERIFY_TIME_INDEX_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TRR通知GRR，GSM BSIC初始确认和重确认的时间索引

 连接态索引取值如下:

     index    Tidentify,gsm  Treconfirm,gsm
                  (ms)            (ms)
    ------------------------------------------
      0          5000           5000

空闲态索引取值如下:

    index  DRX cycle length  Tidentify,gsm
                 (s)              (ms)
   ------------------------------------------
     0           0.08             360
     1           0.16             360
     2           0.32             360
     3           0.64             360
     4           1.28             180
     5           2.56             180
     6           5.12             180

*****************************************************************************/
enum TRRC_GRR_VERIFY_TIME_INDEX_ENUM
{
    TRRC_GRR_VERIFY_TIME_INDEX_0                            = 0,
    TRRC_GRR_VERIFY_TIME_INDEX_1                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_2                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_3                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_4                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_5                             ,
    TRRC_GRR_VERIFY_TIME_INDEX_6                             ,

    TRRC_GRR_VERIFY_TIME_INDEX_BUTT
};
typedef VOS_UINT16 TRRC_GRR_VERIFY_TIME_INDEX_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TRRC_GRR_RESULT_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 通用回复结果标志
*****************************************************************************/
enum TRRC_GRR_RESULT_ENUM
{
    TRRC_GRR_RESULT_SUCC                                    = 0,
    TRRC_GRR_RESULT_FAIL                                    ,

    TRRC_GRR_RESULT_BUTT
};
typedef VOS_UINT8    TRRC_GRR_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TRRC_GRR_SET_DSP_POWER_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间设置DSP省电模式命令
*****************************************************************************/
enum TRRC_GRR_SET_DSP_POWER_CMD_ENUM
{
    TRRC_GRR_SET_DSP_POWER_OPEN                             = 0,
    TRRC_GRR_SET_DSP_POWER_CLOSE                             ,

    TRRC_GRR_SET_DSP_POWER_TYPE_BUTT
};

typedef VOS_UINT32 TRRC_GRR_SET_DSP_POWER_CMD_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TRRC_GRR_SET_DSP_POWER_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : G与TD之间设置DSP省电模式结果
*****************************************************************************/
enum TRRC_GRR_SET_DSP_POWER_RESULT_ENUM
{
    TRRC_GRR_SET_DSP_POWER_SUCC                             = 0,
    TRRC_GRR_SET_DSP_POWER_FAIL                              ,

    TRRC_GRR_SET_DSP_POWER_RESULT_BUTT
};

typedef VOS_UINT32 TRRC_GRR_SET_DSP_POWER_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TRRC_GRR_MEAS_BAND_WIDTH_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 带宽枚举(测量带宽)
*****************************************************************************/
enum TRRC_GRR_MEAS_BAND_WIDTH_ENUM
{
    TRRC_GRR_MEAS_BAND_WIDTH_3840MCPS                       = 0,                /* 带宽为3.84 Mcps */
    TRRC_GRR_MEAS_BAND_WIDTH_1280MCPS                       = 1,                /* 带宽为1.28 Mcps */

    TRRC_GRR_MEAS_BAND_WIDTH_BUTT
};
typedef VOS_UINT8 TRRC_GRR_MEAS_BAND_WIDTH_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GRR_TRRC_MEAS_GAS_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GAS主模测量时将GAS目前的状态带给TRRC; 释放测量时, TRRC 忽略GAS状态。
*****************************************************************************/
enum GRR_TRRC_MEAS_GAS_STATUS_ENUM
{
    GRR_TRRC_MEAS_GAS_STATUS_IDLE                           = 0,                /* IDLE态 */
    GRR_TRRC_MEAS_GAS_STATUS_CONNECT                         ,                  /* CONNECT态 */

    GRR_TRRC_MEAS_GAS_STATUS_BUTT
};
typedef VOS_UINT8 GRR_TRRC_MEAS_GAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TRRC_GRR_MEAS_TAS_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TDS主模测量时将TDS目前的状态带给TRRC
*****************************************************************************/
enum TRRC_GRR_MEAS_TAS_STATUS_ENUM
{
    TRRC_GRR_MEAS_TAS_STATUS_IDLE                           = 0,                /* IDLE态 */
    TRRC_GRR_MEAS_TAS_STATUS_CELL_PCH                          ,                /* CELL_PCH态 */
    TRRC_GRR_MEAS_TAS_STATUS_URA_PCH                           ,                /* URA_PCH态 */
    TRRC_GRR_MEAS_TAS_STATUS_CELL_FACH                         ,                /* CELL_FACH态 */
    TRRC_GRR_MEAS_TAS_STATUS_CELL_DCH                          ,                /* CELL_DCH态 */

    TRRC_GRR_MEAS_TAS_STATUS_BUTT
};
typedef VOS_UINT8 TRRC_GRR_MEAS_TAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 小区驻留方式
*****************************************************************************/
enum TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM
{
    TRRC_GRR_CELL_CAMPEDON_SUITABLE                         = 0,                /* 小区驻留在方式为suitable   */
    TRRC_GRR_CELL_CAMPEDON_ANY_CELL                            ,                /* 小区驻留在方式为acceptable */

    TRRC_GRR_CELL_CAMPEDON_TYPE_BUTT
};

typedef VOS_UINT8 TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TRRC_GURRC_MEAS_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 测量指令
*****************************************************************************/
enum TRRC_GRR_MEAS_CMD_ENUM
{
    TRRC_GRR_MEAS_CMD_ENUM_RELEASE                          = 0,
    TRRC_GRR_MEAS_CMD_ENUM_SETUP                             ,

    TRRC_GRR_MEAS_CMD_ENUM_BUTT
};

typedef VOS_UINT16 TRRC_GRR_MEAS_CMD_ENUM_UINT16;


/*****************************************************************************
 枚举名    : TRRC_GRR_RELALL_REASON_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : TRRC给GRR发送的释放原因
*****************************************************************************/
enum TRRC_GRR_RELALL_REASON_ENUM
{
    TRRC_GRR_REL_REASON_OTHER                               = 0,
    TRRC_GRR_REL_REASON_TO_GSM                                 ,

    TRRC_GRR_REL_REASON_BUTT
};
typedef VOS_UINT8 TRRC_GRR_RELALL_REASON_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    :TRRC_GRR_PLMN_ID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PLMN ID结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                                              ulMnc;              /* MNC,2 or 3 bytes */
}TRRC_GRR_PLMN_ID_STRU;

/*****************************************************************************
 结构名    :TRRC_GRR_BSIC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CELL BSIC Info，协议36331 6.3.4
            ucNcc(GSM Network Colour Code)  正常范围:(0..7), 8 表示无效值
            ucBcc(GSM Base Station Colour Code)  正常范围:(0..7) , 8 表示无效值
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNcc;
    VOS_UINT8                                               ucBcc;
    VOS_UINT8                                               aucReserved[2];
}TRRC_GRR_BSIC_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_CELL_SEL_UTRAN_TDD_CELL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDD小区描述
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;                            /* 频点 */
    VOS_UINT16                              usCellParamId;                      /* 如果扰码无效使用0xFFFF值 */
    VOS_UINT8                               ucDiversity;                        /* 分集指示 TDS: SCTD applied，目前不使用，但GAS会填写 */
    TRRC_GRR_MEAS_BAND_WIDTH_ENUM_UINT8     enBandWidth;                        /* TD小区信道带宽,仅2个值有效。默认值为TRRC_GRR_MEAS_BAND_WIDTH_3840TCPS */
    VOS_UINT8                               ucSyncCaseTstd;                     /* 3.84 Mcps: Sync case; 1.28 Mcps: TSTD applied，目前不使用，但GAS会填写  */
    VOS_UINT8                               aucReserved[1];                     /* 4字节对齐，保留 */
}RRC_CELL_SEL_UTRAN_TDD_CELL_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_FAST_RETURN_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TDD用于GSM快速返回TDD的结构
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFRValid;      /* 如果此值为false，就表示不支持fast return，不用处理后续的信息 */
    VOS_UINT8                           ucFreqNum;

    /* band1:每个Arfcn的范围[9400,9499]; band2:每个Arfcn的范围[9500,9599]; band3:每个Arfcn的范围[10050,10125]; */
    VOS_UINT16                          ausArfcn[TRRC_GRR_MAX_FR_FREQ_NUM];
    VOS_INT16                           sRscpThres;     /* 对应实际RSCP的范围[-116 ~ -26] */
    VOS_UINT8                           aucReserve[2];
}TRRC_GRR_FAST_RETURN_STRU;
/*准FR特性end*/
/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/










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

#endif

