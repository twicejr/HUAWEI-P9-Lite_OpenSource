/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LRrcCdmaInterface.h
  Description     : LTE RRC与内部之间接口文件
  History         :
      1.liutao 00222817       2013-12-30   Draft Enact
******************************************************************************/

#ifndef __LRRC_CDMA_INTERFACE_H__
#define __LRRC_CDMA_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


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
/* LRRC与CDMA之间的消息地址 */
#define LRRC_CDMA_INTRA_MSG_HDR                     (1000)
#define CDMA_LRRC_INTRA_MSG_HDR                     (2000)


#define LRRC_CDMA_BAND_MAX_NUM                      16


/* 1XRTT 与 HRPD两种各自支持最大的小区数为16 */
#define LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM             16
#define LRRC_CDMA_CELL_MAX_NUM                      32


#define LRRC_CDMA_UINT8_INVALID                     (0XFF)
#define LRRC_CDMA_UINT16_INVALID                    (0XFFFF)
#define LRRC_CDMA_UINT32_INVALID                    (0XFFFFFFFF)


#define LRRC_CDMA_MEAS_CGI_RESULT                   16

#define CDMA_LRRC_LTE_EARFCN_MAX_NUM                7
#define CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM           8 //#define CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM           9 cdma接口中限制为8



#define LRRC_CDMA_CONN_MEAS_PERIOD_VALUE            200
#define LRRC_CDMA_IDLE_MEAS_PERIOD_VALUE            200

#define LTE_CDMA_LTE_PRI_INFO_MAX_NUM               4
#define LTE_CDMA_CDMA_PRI_INFO_MAX_NUM              3

#define LEE_CDMA_MIN_RSRP                           30

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    :LRRC_CDMA_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :LRRC内部转换CDMA数据结构内部消息
*****************************************************************************/
enum LRRC_CDMA_MSG_TYPE_ENUM
{
    /* L->C CONN MEAS */
    LRRC_CDMA_CONN_MEAS_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice LRRC_CDMA_CONN_MEAS_REQ_STRU */
    CDMA_LRRC_CONN_MEAS_IND                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice CDMA_LRRC_CONN_MEAS_IND_STRU */

    /* L->C CELL RELSEL */
    LRRC_CDMA_CELL_RESEL_REQ                    = (LRRC_CDMA_INTRA_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice LRRC_CDMA_CELL_RESEL_REQ_STRU */
    CDMA_LRRC_CELL_RESEL_CNF                    = (CDMA_LRRC_INTRA_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice CDMA_LRRC_CELL_RESEL_CNF_STRU */


    /* L->C CELL REDIR */
    LRRC_CDMA_CELL_REDIR_REQ                    = (LRRC_CDMA_INTRA_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice LRRC_CDMA_CELL_REDIR_REQ_STRU */
    CDMA_LRRC_CELL_REDIR_CNF                    = (CDMA_LRRC_INTRA_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice CDMA_LRRC_CELL_REDIR_CNF_STRU */


    /* L->C IDLE MEAS */
    LRRC_CDMA_IDLE_MEAS_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice LRRC_CDMA_IDLE_MEAS_REQ_STRU */
    CDMA_LRRC_IDLE_MEAS_IND                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice CDMA_LRRC_IDLE_MEAS_IND_STRU */

    /* L->C IDLE PRI */
    LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ         = (LRRC_CDMA_INTRA_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU */
    /* C->L IDLE PRI */
    CDMA_LRRC_SET_IDELMOBILITY_INFO_REQ         = (CDMA_LRRC_INTRA_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice CDMA_LRRC_SET_IDELMOBILITY_INFO_REQ_STRU */


    /* C->L  MEAS */
    CDMA_LRRC_MEAS_CELL_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice CDMA_LRRC_MEAS_CELL_REQ_STRU */
    LRRC_CDMA_MEAS_CELL_IND                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice LRRC_CDMA_MEAS_CELL_IND_STRU */

    /* L->C MESA STOP */
    LRRC_CDMA_STOP_MEAS_REQ                     = (LRRC_CDMA_INTRA_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice LRRC_CDMA_STOP_MEAS_REQ_STRU */

    /* C->L MESA STOP */
    CDMA_LRRC_STOP_MEAS_REQ                     = (CDMA_LRRC_INTRA_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice CDMA_LRRC_STOP_MEAS_REQ_STRU */

    /* L->C STOP Mobility */
    LRRC_CDMA_STOP_CELL_RESEL_REQ                 = (LRRC_CDMA_INTRA_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice LRRC_CDMA_STOP_CELL_RESEL_REQ_STRU */

    /* C->L STOP Mobility CNF */
    CDMA_LRRC_STOP_CELL_RESEL_CNF                 = (CDMA_LRRC_INTRA_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU */

    /* L->C STOP Mobility */
    LRRC_CDMA_STOP_CELL_REDIR_REQ                 = (LRRC_CDMA_INTRA_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice LRRC_CDMA_STOP_CELL_REDIR_REQ_STRU */

    /* C->L STOP Mobility CNF */
    CDMA_LRRC_STOP_CELL_REDIR_CNF                 = (CDMA_LRRC_INTRA_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice CDMA_LRRC_STOP_CELL_REDIR_CNF_STRU */

    LRRC_CDMA_MSG_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_CDMA_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名     :LRRC_CDMA_VALID_FLAG_ENUM
 协议表格   :
 ASN.1描述   :
 枚举说明 : 通用是否存在标志
*****************************************************************************/
enum LRRC_CDMA_VALID_FLAG_ENUM
{
    LRRC_CDMA_FLAG_INVALID                      = 0,
    LRRC_CDMA_FLAG_VALID                           ,

    LRRC_CDMA_FLAG_BUTT
};
typedef VOS_UINT8    LRRC_CDMA_VALID_FLAG_ENUM_UINT8;


/*****************************************************************************
 枚举名     :LRRC_CDMA_SYSTEM_TYPE_ENUM
 协议表格   :
 ASN.1描述   :
 枚举说明 : CDMA RAT的系统类型
*****************************************************************************/
enum LRRC_CDMA_SYSTEM_TYPE_ENUM
{
    LRRC_CDMA_SYSTEM_TYPE_1XRTT                             = 0,
    LRRC_CDMA_SYSTEM_TYPE_HRPD,

    LRRC_CDMA_SYSTEM_TYPE_BUTT
};
typedef VOS_UINT8    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名     :LRRC_CDMA_SYSTEM_TYPE_ENUM
 协议表格   :
 ASN.1描述   :
 枚举说明 : CDMA RAT的系统类型
*****************************************************************************/
enum LRRC_CDMA_MEAS_TYPE_ENUM
{
    LRRC_CDMA_MEAS_TYPE_IRAT                               = 0,
    LRRC_CDMA_MEAS_TYPE_SIB8,

    LRRC_CDMA_MEAS_TYPE_BUTT
};
typedef VOS_UINT8    LRRC_CDMA_MEAS_TYPE_UINT8;


/*****************************************************************************
 枚举名     :LRRC_CDMA_MEAS_RESULT_FLAG_ENUM
 协议表格   :
 ASN.1描述   :
 枚举说明 : CDMA小区测量结果
*****************************************************************************/
enum CDMA_LRRC_MEAS_RESULT_FLAG_ENUM
{
    /* Measurement completed successfully.Rest of the para are valid only in this case */
    CDMA_LRRC_MEAS_RESULT_SUCCESS               = 0,

    /* Measuremen failed since 1xRTT is on call,Need triger the meas again */
    CDMA_LRRC_MEAS_RESULT_1X_ONCALL,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_ACQ_FAIL,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_EMPTY_INFO,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_BAND_NOT_SPORT_FAIL,

    /* Meas failed, Need triger the meas again*/
    CDMA_LRRC_MEAS_RESULT_FAIL,

    CDMA_LRRC_MEAS_RESULT_FLAG_BUTT
};
typedef VOS_UINT32    CDMA_LRRC_MEAS_RESULT_FLAG_ENUM_UINT32;


/*****************************************************************************
 枚举名     :LRRC_CDMA_MEAS_RESULT_FLAG_ENUM
 协议表格   :
 ASN.1描述   :
 枚举说明 : LTE小区测量结果
*****************************************************************************/
enum LRRC_CDMA_MEAS_RESULT_FLAG_ENUM
{
    /* Measurement completed successfully */
    LRRC_CDMA_MEAS_RESULT_SUCCESS                           = 0,

    /* Meas failed, Need triger the meas again */
    LRRC_CDMA_MEAS_RESULT_ACQ_FAIL,

    /* Meas failed, Need triger the meas again*/
    LRRC_CDMA_MEAS_RESULT_BAND_NOT_SPORT_FAIL,

    /* Meas failed, Need triger the meas again*/
    LRRC_CDMA_MEAS_RESULT_FAIL,

    LRRC_CDMA_MEAS_RESULT_FLAG_BUTT
};
typedef VOS_UINT32    LRRC_CDMA_MEAS_RESULT_FLAG_ENUM_UINT32;


/*****************************************************************************
 枚举名     :CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8
 协议表格   :
 ASN.1描述   :
 枚举说明 : CDMA回复小区重选或者重定向的结果
*****************************************************************************/
enum CDMA_LRRC_CELL_RESEL_RESULT_ENUM
{
    CDMA_LRRC_CELL_RESEL_RESULT_SUCCESS                     = 0,

    /* System change to target failed since target system could not be acquired */
    CDMA_LRRC_CELL_RESEL_RESULT_ACQ_FAIL,

    /* System change to target failed since PS registration on target system failed  */
    CDMA_LRRC_CELL_RESEL_RESULT_PS_REG_FAIL,

    /* System change to target failed since PS session establish on target system failed */
    CDMA_LRRC_CELL_RESEL_RESULT_PS_SESSION_FAIL,

    CDMA_LRRC_CELL_RESEL_RESULT_FAIL,

    CDMA_LRRC_CELL_RESEL_RESULT_BUTT
};
typedef VOS_UINT8    CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8;

//#define CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8 CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8
typedef CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8 CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8;


/*****************************************************************************
 枚举名     :CDMA_LRRC_CELL_REDIR_RESULT_ENUM
 协议表格   :
 ASN.1描述   :
 枚举说明 : 测量带宽枚举
*****************************************************************************/
enum CDMA_LRRC_MEAS_BAND_WIDTH_ENUM
{
    CDMA_LRRC_MEAS_BAND_WIDTH_6RB               = 0,                /* 带宽为6RB   */
    CDMA_LRRC_MEAS_BAND_WIDTH_15RB                 ,                /* 带宽为15RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_25RB                 ,                /* 带宽为25RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_50RB                 ,                /* 带宽为50RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_75RB                 ,                /* 带宽为75RB  */
    CDMA_LRRC_MEAS_BAND_WIDTH_100RB                ,                /* 带宽为100RB */

    CDMA_LRRC_MEAS_BAND_WIDTH_BUTT
};
typedef VOS_UINT8 CDMA_LRRC_MEAS_BAND_WIDTH_ENUM_UINT8;

/*****************************************************************************
 枚举名     :CDMA_LRRC_SYSCHG_STOP_REASON_ENUM
 协议表格   :
 ASN.1描述   :
 枚举说明 : 测量带宽枚举
*****************************************************************************/
enum LRRC_CDMA_SYSCHG_STOP_REASON_ENUM
{
    LRRC_CDMA_SYSCHG_STOP_REASON_RESEL              = 0,                /* 停止重选  */
    LRRC_CDMA_SYSCHG_STOP_REASON_REDIR                 ,                /* 停止重定向  */

    LRRC_CDMA_SYSCHG_STOP_REASON_BUTT
};
typedef VOS_UINT32 LRRC_CDMA_SYSCHG_STOP_REASON_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : LRRC_CDMA_MEAS_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA 小区信息列表
*****************************************************************************/
typedef struct
{
    /* 0xffff 表示无效 */
    VOS_UINT16                  usCellToReportCgi;

    /* [0,2047] */
    VOS_UINT16                  usChannel;

    /* 与LTE的空口值一致 */
    VOS_UINT8                   ucBand;

    /* [[0,15],0xff], 0XFF,表示无效 */
    VOS_UINT8                   ucSearchWinSize;
    VOS_UINT16                  usCellNum;
    VOS_UINT16                  ausCellPn[LRRC_CDMA_CELL_MAX_NUM];
}LRRC_CDMA_MEAS_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_CDMA_HPRD_CONN_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接态CDMA HPRD小区信息列表
*****************************************************************************/
typedef struct
{
    /* LTE CDMA系统测量对应的小区的周期，单位MS
       0:代码仅仅启动一次测量，及发送一次测量一次
       other:发送一次REQ，周期上报测量结果,固定200ms
       计算公式:
    */
    VOS_UINT32                          ulPeriod;

    /*  针对BAND进行发送，在一个OBJ里有多个，按照多个进行发送 */
    VOS_UINT32                          ulBandInfoNum;
    LRRC_CDMA_MEAS_CELL_INFO_STRU       stLrrcCdemaMeasCellInfo[LRRC_CDMA_BAND_MAX_NUM];
}LRRC_CDMA_HPRD_CONN_CELL_INFO_LIST_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA 小区测量结果
*****************************************************************************/
typedef struct
{
    /* This is one from the meas cmd receive */
    VOS_UINT16                          usCellPn;

    /* CDMA pilot phase, in chips ,only for 1xRTT */
    VOS_UINT16                          usPilotPhase;

    /* (0,30),CDMA pilt strength 实际计算时需要乘以 -0.5  */
    VOS_INT16                           sPilotStrength;
    VOS_UINT16                          usReserved;
}CDMA_LRRC_CELL_MEAS_RESULT_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA 小区测量结果信息
*****************************************************************************/
typedef struct
{
    CDMA_LRRC_MEAS_RESULT_FLAG_ENUM_UINT32                  ulMeasResultFlg;

    VOS_UINT16                                              usChannel;
    VOS_UINT8                                               ucBand;

    /* 0: no CGI is available
       1: CGI is available
    */
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucCgiResutlFlg;

    /* It carries the EVDO cell sector ID */
    VOS_UINT8                                               aucCgiResult[LRRC_CDMA_MEAS_CGI_RESULT];

    VOS_UINT16                                              usReserved;
    VOS_UINT16                                              usCellNum;
    CDMA_LRRC_CELL_MEAS_RESULT_STRU                         astCellResultList[LRRC_CDMA_CELL_MAX_NUM];
}CDMA_LRRC_MEAS_RESULT_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_HPRD_CONN_MEAS_RESULT_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接态CDMA HPRD测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBandInfoNum;
    CDMA_LRRC_MEAS_RESULT_STRU          stCdemaLrrcConnMeasResultInfo[LRRC_CDMA_BAND_MAX_NUM];
}CDMA_LRRC_HPRD_CONN_MEAS_RESULT_LIST_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA系统中LTE邻区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usEarfcn;
    CDMA_LRRC_MEAS_BAND_WIDTH_ENUM_UINT8        ucMeasBandWidth;
    VOS_UINT8                                   ucRxLevMin;

    VOS_UINT8                                   ucRxLevMinOffset;
    VOS_UINT8                                   ucPeMax;
    VOS_UINT8                                   ucReserved;
    VOS_UINT8                                   ucPlmnNum;
    VOS_UINT32                                  ulPlmnId[CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM];
}CDMA_LRRC_CELL_INFO_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_MEAS_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA系统中LTE邻区列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulLteEarFcn; // num?
    CDMA_LRRC_CELL_INFO_STRU                    astLteCellInfo[CDMA_LRRC_LTE_EARFCN_MAX_NUM];
}CDMA_LRRC_MEAS_CELL_INFO_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_CELL_MEAS_RESULT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE邻区测量结果信息
*****************************************************************************/
typedef struct
{
    /* 默认填写值 0XFFFFFFFF */
    VOS_UINT32                                              ulPlmnId;
    VOS_UINT16                                              usCellId;

    /* [-141,0]*/
    VOS_INT16                                               sRsrp;
}LRRC_CDMA_CELL_MEAS_RESULT_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE邻区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usEarfcn;
    VOS_UINT8                                               aucReserved[1];
    VOS_UINT8                                               ucPlmnNum;
    LRRC_CDMA_CELL_MEAS_RESULT_INFO_STRU                    astCellResultInfo[CDMA_LRRC_LTE_CELL_PLMNID_MAX_NUM];
}LRRC_CDMA_CELL_MEAS_RESULT_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_CELL_MEAS_RESULT_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE邻区测量结果列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulCellResultNum;
    LRRC_CDMA_CELL_MEAS_RESULT_STRU                         astLteResult[CDMA_LRRC_LTE_EARFCN_MAX_NUM];
}LRRC_CDMA_CELL_MEAS_RESULT_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_IDLE_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA IDLE 小区信息列表
*****************************************************************************/
typedef struct
{
    /* 0xffff 表示无效 */
    VOS_UINT16                  usCellToReportCgi;
    VOS_UINT16                  usChannel;

    VOS_UINT8                   ucBand;

    VOS_UINT8                   ucCellReselectionPriority;
    VOS_UINT16                  usCellNum;
    VOS_UINT16                  ausCellPn[LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM];
}LRRC_CDMA_IDLE_CELL_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_HPRD_IDLE_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA IDLE HPRD小区信息列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBandInfoNum;
    LRRC_CDMA_IDLE_CELL_INFO_STRU       astLrrcCdemaIdleCellInfo[LRRC_CDMA_CELL_MAX_NUM];
#if (FEATURE_BALONG_CL == FEATURE_ON)
    VOS_UINT16                          usHighPrioNum;
    VOS_UINT8                           aucReserved[2];
#endif
}LRRC_CDMA_HPRD_IDLE_CELL_INFO_LIST_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_IDLE_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA 小区测量结果信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usChannel;
    VOS_UINT8                                               ucBand;

    /* 0: no CGI is available
       1: CGI is available
    */
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucCgiResutlFlg;

    /* It carries the EVDO cell sector ID */
    VOS_UINT8                                               aucCgiResult[LRRC_CDMA_MEAS_CGI_RESULT];

    VOS_UINT16                                              usResered;
    VOS_UINT16                                              usCellNum;
    CDMA_LRRC_CELL_MEAS_RESULT_STRU                         astCellResultList[LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM];
}CDMA_LRRC_IDLE_MEAS_RESULT_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_HPRD_IDLE_MEAS_RESULT_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA HPRD测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBandInfoNum;
    CDMA_LRRC_IDLE_MEAS_RESULT_STRU     astLrrcCdemaIdleMeasResultInfo[LRRC_CDMA_CELL_MAX_NUM];
}CDMA_LRRC_HPRD_IDLE_MEAS_RESULT_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_STOP_MEAS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE向CDMA发送停止测量信息
*****************************************************************************/
typedef struct
{
    LRRC_CDMA_MEAS_TYPE_UINT8                               ucStopCmd;
    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8                        ucCdmaSystemType;
    VOS_UINT8                                               aucReserved[2];
}LRRC_CDMA_STOP_MEAS_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_STOP_MEAS_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE向CDMA发送停止测量信息列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulStopMeasNum;
    LRRC_CDMA_STOP_MEAS_INFO_STRU                           astLrrcCdmaStopMeasInfo[LRRC_CDMA_SYSTEM_TYPE_BUTT];
}LRRC_CDMA_STOP_MEAS_INFO_LIST_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_CONN_MEAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给CDMA指示小区测量原语，适用于CONN
             1、原VIA接口是MmcRatAPI_IRAT_Meas_Cmd
             2、接口目前仅仅使用CONN态功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               aucReserved[2];

    LRRC_CDMA_HPRD_CONN_CELL_INFO_LIST_STRU                 stLRrcCdmaHprdConnCellInfoList;
}LRRC_CDMA_CONN_MEAS_REQ_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_CONN_MEAS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA发给LRRC指示小区测量结果原语，适用于IDLE与CONN
             1、原VIA接口是RatMmcAPI_IRAT_Meas_Ind
             2、接口目前仅仅使用CONN态功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;

    /* 暂时保留 */
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               aucReserved[2];

    CDMA_LRRC_HPRD_CONN_MEAS_RESULT_LIST_STRU               stCdmaLRrcHprdMeasResultList;
}CDMA_LRRC_CONN_MEAS_IND_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_CELL_RESEL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE发给CDMA用于系统间重选
             1、原VIA接口是MmcRatAPI_IRAT_System_Change_Req
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8                        ucCdmaSystemType;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT8                                               ucBand;

    VOS_UINT16                                              usChannel;

    /* Cell Num must > 0 */
    VOS_UINT16                                              usCellNum;
    VOS_UINT16                                              ausCellPn[LRRC_CDMA_ONE_TYPE_CELL_MAX_NUM];
}LRRC_CDMA_CELL_RESEL_REQ_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_CELL_RESEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA发给LTE用于系统间重选回复
             1、原VIA接口是RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8                  ucCellReselResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_CELL_RESEL_CNF_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_CELL_REDIR_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE发给CDMA用于系统间重定向
             1、原VIA接口是MmcRatAPI_IRAT_System_Change_Req
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSTEM_TYPE_ENUM_UINT8                        ucCdmaSystemType;
    VOS_UINT8                                               ucBand;
    VOS_UINT16                                              usChannel;
}LRRC_CDMA_CELL_REDIR_REQ_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_CELL_REDIR_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA发给LTE用于系统间重定向回复
             1、原VIA接口是RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8                  ucCellRedirResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_CELL_REDIR_CNF_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_IDLE_MEAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给CDMA指示小区测量原语，适用于IDLE态
             1、原VIA接口是MmcRatAPI_IRAT_SIB8_Meas_Cmd
             2、接口目前仅仅使用IDLE态功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               ucWindowSize;
    VOS_UINT8                                               ucReserved;

    /* CDMA系统测量对应的小区的周期，单位MS
       0:代码仅仅启动一次测量，及发送一次测量一次
       other:发送一次REQ，周期上报测量结果 ，目前固定为200ms
    */
    VOS_UINT32                                              ulPeriod;

    LRRC_CDMA_HPRD_IDLE_CELL_INFO_LIST_STRU                 stLRrcCdmaHprdIdleCellInfoList;
}LRRC_CDMA_IDLE_MEAS_REQ_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_IDLE_MEAS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA发给LRRC指示小区测量结果原语，适用于IDLE
             1、原VIA接口是RatMmcAPI_IRAT_Meas_Ind
             2、接口目前仅仅使用IDLE态功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         ucHprdInfoFlag;
    LRRC_CDMA_VALID_FLAG_ENUM_UINT8                         uc1XRttInfoFlag;
    VOS_UINT8                                               aucReserved[2];

    CDMA_LRRC_MEAS_RESULT_FLAG_ENUM_UINT32                  ulMeasResultFlg;

    CDMA_LRRC_HPRD_IDLE_MEAS_RESULT_LIST_STRU               stCdmaLRrcHprdIdleMeasResultList;
}CDMA_LRRC_IDLE_MEAS_IND_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_MEAS_CELL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA发给LTE用于测量LTE小区
             1、原VIA接口是RatMmcAPI_IRAT_RATMeas_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_MEAS_CELL_INFO_LIST_STRU                      stCdmaLrrcMeasInfoList;
}CDMA_LRRC_MEAS_CELL_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_MEAS_CELL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE向CDMA上报测量结果
             1、原VIA接口是MmcRatAPI_IRAT_RATMeas_Ind
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_MEAS_RESULT_FLAG_ENUM_UINT32                  ulReultFlag;

    LRRC_CDMA_CELL_MEAS_RESULT_LIST_STRU                    stLrrcMeasResultList;
}LRRC_CDMA_MEAS_CELL_IND_STRU;



/*****************************************************************************
 结构名    : LRRC_CDMA_LTE_PRI_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE专有优先级信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usLteEarfcn;
    VOS_UINT8                                               ucPri;
    VOS_UINT8                                               ucReserved;
}LRRC_CDMA_LTE_PRI_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_CDMA_PRI_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA专有优先级信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usChannel;
    VOS_UINT8                                               ucBand;
    VOS_UINT8                                               ucPri;
}LRRC_CDMA_CDMA_PRI_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_CDMA_IDELMOBILITY_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE接收到的专有优先级信息
*****************************************************************************/
typedef struct
{
    /* 剩余时间 单位: S */
    VOS_UINT16                                              usT320LeftValue;
    VOS_UINT8                                               ucLtePriInfoNum;
    VOS_UINT8                                               ucCdmaPriInfoNum;

    LRRC_CDMA_LTE_PRI_INFO_STRU                             astrLrrcCdmaLtePriInfo[LTE_CDMA_LTE_PRI_INFO_MAX_NUM];
    LRRC_CDMA_CDMA_PRI_INFO_STRU                            astrLrrcCdmaCdmaPriInfo[LTE_CDMA_CDMA_PRI_INFO_MAX_NUM];
}LRRC_CDMA_IDELMOBILITY_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE发送给CDMA的专有优先级信息
             1、原VIA接口是MmcRatAPI_IRAT_Set_IdleModeMobilityCtrlInfo_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/


    LRRC_CDMA_IDELMOBILITY_INFO_STRU                        struLrrcCdmaIdleMobilityInfo;
}LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU;


typedef LRRC_CDMA_SET_IDELMOBILITY_INFO_REQ_STRU    CDMA_LRRC_SET_IDELMOBILITY_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_CDMA_STOP_MEAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE向CDMA发送停止测量的请求
             1、原VIA接口是MmcRatAPI_Stop_IRAT_Meas_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_STOP_MEAS_INFO_LIST_STRU                      stLrrcCdmaStopMeasInfoList;
}LRRC_CDMA_STOP_MEAS_REQ_STRU;


/*****************************************************************************
 结构名    : CDMA_LRRC_STOP_MEAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA向LTE发送停止测量的请求
             1、原VIA接口是RatMmcAPI_Stop_IRAT_Meas_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
}CDMA_LRRC_STOP_MEAS_REQ_STRU;


/*****************************************************************************
 结构名    : LRRC_CDMA_MSG_DATA
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_GRR_MSG_DATA数据结构，用于生成ASN文件
*****************************************************************************/
typedef struct
{
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_CDMA_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_CDMA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_CDMA_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : LRrcCdmaInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : LRrcCdmaInterface_MSG数据结构,用于生成ASN文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_CDMA_MSG_DATA                                       stMsgData;
}LRrcCdmaInterface_MSG;

/*****************************************************************************
 结构名    : LRRC_CDMA_STOP_CELL_RESEL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE向CDMA发送停止互操作的请求
             1、原VIA接口是MmcRatAPI_IRAT_System_Change_Abort_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSCHG_STOP_REASON_ENUM_UINT32                ulLrrcCdmaSysChgStopReason;
}LRRC_CDMA_STOP_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_CDMA_STOP_CELL_REDIR_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE向CDMA发送停止互操作的请求
             1、原VIA接口是MmcRatAPI_IRAT_System_Change_Abort_Cmd
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    LRRC_CDMA_SYSCHG_STOP_REASON_ENUM_UINT32                ulLrrcCdmaSysChgStopReason;
}LRRC_CDMA_STOP_CELL_REDIR_REQ_STRU;

/*****************************************************************************
 结构名    : CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA发给LTE停止系统间重选回复
             1、原VIA接口是RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_RESEL_RESULT_ENUM_UINT8                  ucCellReselResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 结构名    : CDMA_LRRC_STOP_CELL_RESEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDMA发给LTE停止系统间重定向回复
             1、原VIA接口是RatMmcAPI_IRAT_System_Change_Rsp
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_CDMA_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    CDMA_LRRC_CELL_REDIR_RESULT_ENUM_UINT8                  ucCellRedirResult;
    VOS_UINT8                                               aucReserved[3];
}CDMA_LRRC_STOP_CELL_REDIR_CNF_STRU;

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

#endif /* end of LRrcCdmaInterface.h */
