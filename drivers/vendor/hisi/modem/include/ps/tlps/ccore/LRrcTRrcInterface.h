/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LRrcTRrcInterface.h
  Description     : LTE RRC与TDS RRC之间接口文件
  History         :
      1.x49630       2011-9-14   Draft Enact

******************************************************************************/

#ifndef __LRRCTRRCINTERFACE_H__
#define __LRRCTRRCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "LPSCommon.h"
#include  "LRrcGuRrcCommInterface.h"
#include  "LRrcWRrcInterface.h"

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

#define LRRC_TRRC_MSG_HDR                (PS_MSG_ID_LRRC_TO_TRRC_BASE)
#define TRRC_LRRC_MSG_HDR                (PS_MSG_ID_TRRC_TO_LRRC_BASE)

/* UTRAN TDD UE 能力编码后最大长度*/
#define LRRC_TRRC_UE_CAP_UTRAN_MAX_LEN                      256


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    :
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum LRRC_TRRC_MSG_TYPE_ENUM
{
    /* T -> L Cell Resel */
    ID_TRRC_LRRC_CELL_RESEL_REQ             = (TRRC_LRRC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_REQ_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_CELL_RESEL_CNF             = (LRRC_TRRC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_CNF_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CELL_RESEL_STOP_REQ        = (TRRC_LRRC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_STOP_REQ_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_CELL_RESEL_STOP_CNF        = (LRRC_TRRC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_STOP_CNF_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L Redirect */
    ID_TRRC_LRRC_REDIRECTED_REQ             = (TRRC_LRRC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_REQ_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_REDIRECTED_CNF             = (LRRC_TRRC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_CNF_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_REDIRECTED_STOP_REQ        = (TRRC_LRRC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_STOP_REQ_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_REDIRECTED_STOP_CNF        = (LRRC_TRRC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_STOP_CNF_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L HO */
    ID_TRRC_LRRC_HANDOVER_REQ               = (TRRC_LRRC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_REQ_STRU */          /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_HANDOVER_CNF               = (LRRC_TRRC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_CNF_STRU */          /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_HANDOVER_STOP_REQ          = (TRRC_LRRC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_STOP_REQ_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_HANDOVER_STOP_CNF          = (LRRC_TRRC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_STOP_CNF_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L 低功耗 */
    ID_TRRC_LRRC_SET_DSP_POWER_REQ          = (TRRC_LRRC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice TRRC_LRRC_SET_DSP_POWER_REQ_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_SET_DSP_POWER_CNF          = (LRRC_TRRC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LRRC_TRRC_SET_DSP_POWER_CNF_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L Get Ue Capability Info */
    ID_TRRC_LRRC_GETUECAPINFO_REQ           = (TRRC_LRRC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice TRRC_LRRC_GETUECAPINFO_REQ_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_GETUECAPINFO_CNF           = (LRRC_TRRC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LRRC_TRRC_GETUECAPINFO_CNF_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L PLMN SEARCH */
    ID_TRRC_LRRC_PLMN_SEARCH_REQ            = (TRRC_LRRC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice TRRC_LRRC_PLMN_SEARCH_REQ_STRU */       /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_PLMN_SEARCH_CNF            = (LRRC_TRRC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice LRRC_TRRC_PLMN_SEARCH_CNF_STRU */       /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_PLMN_SEARCH_STOP_REQ       = (TRRC_LRRC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice TRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU */  /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_PLMN_SEARCH_STOP_CNF       = (LRRC_TRRC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice LRRC_TRRC_PLMN_SEARCH_STOP_CNF_STRU */  /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* T -> L Idle Meas */
    ID_TRRC_LRRC_IDLE_MEASURE_REQ           = (TRRC_LRRC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice TRRC_LRRC_IDLE_MEASURE_REQ_STRU */      /* SendPid:WUEPS_PID_WCOM; RcvPid:PS_PID_ERMM */
    ID_LRRC_TRRC_IDLE_MEASURE_CNF           = (LRRC_TRRC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice LRRC_TRRC_IDLE_MEASURE_CNF_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */
    ID_LRRC_TRRC_IDLE_MEASURE_IND           = (LRRC_TRRC_MSG_HDR + 0x0b),       /* _H2ASN_MsgChoice LRRC_TRRC_IDLE_MEASURE_IND_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */

    /* T -> L Conn Meas */
    ID_TRRC_LRRC_CONNECTED_MEASURE_REQ      = (TRRC_LRRC_MSG_HDR + 0x0b),       /* _H2ASN_MsgChoice TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU */ /* SendPid:WUEPS_PID_WCOM; RcvPid:PS_PID_ERMM */
    ID_LRRC_TRRC_CONNECTED_MEASURE_CNF      = (LRRC_TRRC_MSG_HDR + 0x0c),       /* _H2ASN_MsgChoice LRRC_TRRC_CONNECTED_MEASURE_CNF_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */
    ID_LRRC_TRRC_CONNECTED_MEASURE_IND      = (LRRC_TRRC_MSG_HDR + 0x0d),       /* _H2ASN_MsgChoice LRRC_TRRC_CONNECTED_MEASURE_IND_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WCOM */

    /* T -> L RelAll */
    ID_TRRC_LRRC_RELALL_REQ                 = (TRRC_LRRC_MSG_HDR + 0x0c),       /* _H2ASN_MsgChoice TRRC_LRRC_RELALL_REQ_STRU */            /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_RELALL_CNF                 = (LRRC_TRRC_MSG_HDR + 0x0e),       /* _H2ASN_MsgChoice LRRC_TRRC_RELALL_CNF_STRU */            /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */

    /* L -> T Cell Resel*/
    ID_LRRC_TRRC_CELL_RESEL_REQ             = (LRRC_TRRC_MSG_HDR + 0x0f),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_REQ_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CELL_RESEL_CNF             = (TRRC_LRRC_MSG_HDR + 0x0d),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_CNF_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_CELL_RESEL_STOP_REQ        = (LRRC_TRRC_MSG_HDR + 0x10),       /* _H2ASN_MsgChoice LRRC_TRRC_CELL_RESEL_STOP_REQ_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CELL_RESEL_STOP_CNF        = (TRRC_LRRC_MSG_HDR + 0x0e),       /* _H2ASN_MsgChoice TRRC_LRRC_CELL_RESEL_STOP_CNF_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> T Redirect */
    ID_LRRC_TRRC_REDIRECTED_REQ             = (LRRC_TRRC_MSG_HDR + 0x11),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_REQ_STRU */        /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_REDIRECTED_CNF             = (TRRC_LRRC_MSG_HDR + 0x0f),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_CNF_STRU */        /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_REDIRECTED_STOP_REQ        = (LRRC_TRRC_MSG_HDR + 0x12),       /* _H2ASN_MsgChoice LRRC_TRRC_REDIRECTED_STOP_REQ_STRU */   /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_REDIRECTED_STOP_CNF        = (TRRC_LRRC_MSG_HDR + 0x10),       /* _H2ASN_MsgChoice TRRC_LRRC_REDIRECTED_STOP_CNF_STRU */   /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> T HO */
    ID_LRRC_TRRC_HANDOVER_REQ               = (LRRC_TRRC_MSG_HDR + 0x13),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_REQ_STRU */          /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_HANDOVER_CNF               = (TRRC_LRRC_MSG_HDR + 0x11),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_CNF_STRU */          /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */
    ID_LRRC_TRRC_HANDOVER_STOP_REQ          = (LRRC_TRRC_MSG_HDR + 0x14),       /* _H2ASN_MsgChoice LRRC_TRRC_HANDOVER_STOP_REQ_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_HANDOVER_STOP_CNF          = (TRRC_LRRC_MSG_HDR + 0x12),       /* _H2ASN_MsgChoice TRRC_LRRC_HANDOVER_STOP_CNF_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L -> T 低功耗 */
    ID_LRRC_TRRC_SET_DSP_POWER_REQ          = (LRRC_TRRC_MSG_HDR + 0x15),       /* _H2ASN_MsgChoice LRRC_TRRC_SET_DSP_POWER_REQ_STRU */     /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_SET_DSP_POWER_CNF          = (TRRC_LRRC_MSG_HDR + 0x13),       /* _H2ASN_MsgChoice TRRC_LRRC_SET_DSP_POWER_CNF_STRU */     /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L-> T Get Ue Capability Info */
    ID_LRRC_TRRC_GETUECAPINFO_REQ           = (LRRC_TRRC_MSG_HDR + 0x16),       /* _H2ASN_MsgChoice LRRC_TRRC_GETUECAPINFO_REQ_STRU */      /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_GETUECAPINFO_CNF           = (TRRC_LRRC_MSG_HDR + 0x14),       /* _H2ASN_MsgChoice TRRC_LRRC_GETUECAPINFO_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    /* L -> T Idle Meas */
    ID_LRRC_TRRC_IDLE_MEASURE_REQ           = (LRRC_TRRC_MSG_HDR + 0x17),       /* _H2ASN_MsgChoice LRRC_TRRC_IDLE_MEASURE_REQ_STRU */      /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_IDLE_MEASURE_CNF           = (TRRC_LRRC_MSG_HDR + 0x15),       /* _H2ASN_MsgChoice TRRC_LRRC_IDLE_MEASURE_CNF_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */
    ID_TRRC_LRRC_IDLE_MEASURE_IND           = (TRRC_LRRC_MSG_HDR + 0x16),       /* _H2ASN_MsgChoice TRRC_LRRC_IDLE_MEASURE_IND_STRU */      /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */

    /* L -> T Conn Meas */
    ID_LRRC_TRRC_CONNECTED_MEASURE_REQ      = (LRRC_TRRC_MSG_HDR + 0x18),       /* _H2ASN_MsgChoice LRRC_TRRC_CONNECTED_MEASURE_REQ_STRU */ /* SendPid:PS_PID_ERMM; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_CONNECTED_MEASURE_CNF      = (TRRC_LRRC_MSG_HDR + 0x17),       /* _H2ASN_MsgChoice TRRC_LRRC_CONNECTED_MEASURE_CNF_STRU */ /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */
    ID_TRRC_LRRC_CONNECTED_MEASURE_IND      = (TRRC_LRRC_MSG_HDR + 0x18),       /* _H2ASN_MsgChoice TRRC_LRRC_CONNECTED_MEASURE_IND_STRU */ /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERMM */

    /* L -> T RelAll */
    ID_LRRC_TRRC_RELALL_REQ                = (LRRC_TRRC_MSG_HDR + 0x19),        /* _H2ASN_MsgChoice LRRC_TRRC_RELALL_REQ_STRU */             /* SendPid:PS_PID_ERRC; RcvPid:WUEPS_PID_WRR */
    ID_TRRC_LRRC_RELALL_CNF                = (TRRC_LRRC_MSG_HDR + 0x19),        /* _H2ASN_MsgChoice TRRC_LRRC_RELALL_CNF_STRU */             /* SendPid:WUEPS_PID_WRR; RcvPid:PS_PID_ERRC */

    ID_LRRC_TRRC_FR_INFO_CNF               = (LRRC_TRRC_MSG_HDR + 0x1a),        /* _H2ASN_MsgChoice LRRC_TRRC_FR_INFO_CNF_STRU */
    ID_TRRC_LRRC_FR_INFO_REQ               = (TRRC_LRRC_MSG_HDR + 0x1a),        /* _H2ASN_MsgChoice TRRC_LRRC_FR_INFO_REQ_STRU */

    ID_LRRC_TRRC_MSG_TYPE_BUTT = PS_MSG_ID_TRRC_TO_LRRC_BASE + 0x9f             /*!!!定义消息ID只能增加到0x9f*/
};

typedef VOS_UINT32 LRRC_TRRC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : TRRC_LRRC_CELL_RESEL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;
    LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                  enMeasBand;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}TRRC_LRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_CELL_RESEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示小区搜索结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* 当usResult 原因值为LRRC_GURRC_CELL_RESEL_NOT_EPLMNS时，stPlmnIdInfo 有效*/
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfoList;

    /* 当usResult 原因值为LRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESS时，
       ulTimerVaule有效,单位 :毫秒*/
    VOS_UINT32                                              ulTimerValue;

    VOS_INT16                                              sQrxLevMin;          /*RSRP最低接入门限，单位1/8dB*/
    VOS_INT16                                              sQqualMin;           /*RSRQ最低接入门限，单位1/8dB*/
    VOS_UINT32                                             ulReserved[4];
}LRRC_TRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_CELL_RESEL_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :TRRC指示LRRC停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_CELL_RESEL_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   LRRC指示TRRC已停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_REDIRECTED_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示重定向流程启动
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    /* 重定向类型 自主FR还是网侧FR */
    LRRC_GURRC_REDIR_TYPE_ENUM_UINT8                        enRedirType;
    VOS_UINT8                                               ucReserve;

    /* T->L重定向信息 */
    VOS_UINT16                                              usArfcnNum;
    WRRC_LRRC_ARFCN_INFO_STRU                               astRedirInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];


    /* 惩罚时间指的是RRC CON REJ 中携带定时器剩余时长单位:毫秒 */
    VOS_UINT16                                              usPunishTimerValue;

    /* 在REDIR INFO 指示搜索的时间 单位:毫秒,目前固定10000ms，
       在此时间内搜索指定小区后，直接进行其他的小区搜索，不需要等到此定时器超时后再搜索其他SUITABELE小区
    ***************************************************************************/
    VOS_UINT16                                              usSearchTimer;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;   /* 固定为SUITABLE */
    VOS_UINT8                                               aucReserve2[2];

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}TRRC_LRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_REDIRECTED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示重定向结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}LRRC_TRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_REDIRECTED_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :TRRC指示LRRC停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_REDIRECTED_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   LRRC指示TRRC已停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 结构名     :LRRC_TRRC_PLMN_ID_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :PLMN信息
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucPlmnId[3];
    VOS_UINT8                                               aucReserved[1];
}LRRC_TRRC_PLMN_ID_INFO_STRU;

/*****************************************************************************
 结构名    :    LRRC_GURRC_CELL_GLOBAL_ID_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  UTRAN/EUTRAN CELL GLOBAL ID信息
*****************************************************************************/
typedef struct
{
    LRRC_TRRC_PLMN_ID_INFO_STRU                            stPlmnId;
    VOS_UINT32                                              ulCellId;
}LRRC_TRRC_CELL_GLOBAL_ID_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_HANDOVER_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :TRRC指示LRRC启动HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                              bitOpCellGlobalId : 1;
    VOS_UINT32                                              bitSpare          : 31;
    /* L通知T当前驻留的国家码 */
    VOS_UINT8                                               aucMcc[3];
    VOS_UINT8                                               aucReserved[1];
    VOS_UINT16                                              usPrimaryScramCode; /* 当前主小区主扰码*/
    VOS_UINT16                                              usDlUarfcn;         /* 下行频点 */
    LRRC_TRRC_CELL_GLOBAL_ID_STRU                          stCellGlobalId;
    VOS_UINT32                                              ulHoDataLen;
    /* 该数据为编码后的RRC CONN RECFG */
    VOS_UINT8                                               aucHoData[4];
}TRRC_LRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_HANDOVER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  LRRC发给TRRC指示切换流程结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}LRRC_TRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_HANDOVER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :TRRC指示LRRC停止HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_HANDOVER_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   LRRC指示TRRC已停止HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_SET_DSP_POWER_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  TRRC指示LRRC对DSP省电模式操作
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}TRRC_LRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_SET_DSP_POWER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   LRRC指示TRRC对EDSP操作完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}LRRC_TRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_GETUECAPINFO_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  TRRC指示LRRC对提供UE能力信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usMcc;
    VOS_UINT8                                               aucReserved[2];
}TRRC_LRRC_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_GETUECAPINFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   LRRC指示TRRC对UE能力获取完成
 For EUTRA: the encoding of UE capabilities is defined in IE UE-EUTRA-Capability.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucEutranCapInfoData[LRRC_WRRC_UE_CAP_EUTRAN_MAX_LEN];
}LRRC_TRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_HANDOVER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :TRRC指示LRRC启动PLMN SEARCH流程
                 仅仅针对UTRAN UE在连接态下出服务区搜网流程，
                 LRRC需要在搜索过程中判断该小区是否满足SUITABLE准则，
                 与正常的指定的PLMN搜索过程一样，但是不驻留
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usArfcnNum;
    WRRC_LRRC_ARFCN_INFO_STRU                               astArfcnInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];
}TRRC_LRRC_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_PLMN_SEARCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  LRRC发给TRRC PLMN SEARCH 结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM_UINT16                enPLmnSearchRslt;
    VOS_UINT8                                               aucReserved[2];

    /* usPLmnSearchResult =  LRRC_WRRC_PLMN_SEARCH_SUCC ，填写原则如下
       LTE CELL中携带的PLMN LIST中，有RPLMN则填写RPLMN，否则选择其中
       一个PLMN 信息*/
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stSuitablePlmnId;

    /* usPLmnSearchResult =  LRRC_WRRC_PLMN_SEARCH_FAIL ，携带再次过程中搜索到
           所有的PLMN 信息，以高低质量排序传递给WRRC，具体准则同正常的
          PLMN LIST 搜索*/
    LRRC_GURRC_PLMN_ID_LIST_STRU                            stPlmnIdList;
}LRRC_TRRC_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :TRRC指示LRRC停止PLMN SEARCH流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_PLMN_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_PLMN_SEARCH_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   LRRC指示TRRC已停止PLMN SEARCH 流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_PLMN_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_IDLE_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示启动IDLE测量
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stIdleEutranArfcnInfoList;
}TRRC_LRRC_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_IDLE_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : LRRC发给TRRC指示IDLE测量启动结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_TRRC_IDLE_MEASURE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_IDLE_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示IDLE测量结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stMeasRslt;
}LRRC_TRRC_IDLE_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示启动CONNECTED测量
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;

    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_WRRC_STATE_TYPE_ENUM_UINT16                        enTRrcStateType;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_EUTRAN_INFO_LIST_STRU                        stConnEutranArfcnInfoList;
}TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_CONNECTED_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示CONNECTED测量启动结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucValidFreqNum;
    VOS_UINT8                                               ucReserved;
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}LRRC_TRRC_CONNECTED_MEASURE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_CONNECTED_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示CONNECTED 测量结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU                      stMeasRslt;
}LRRC_TRRC_CONNECTED_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_RELALL_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  TRRC指示LRRC执行RelAll操作
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_RELALL_REQ_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_RELALL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   LRRC指示TRRC执行RelAll操作完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_RELALL_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_CELL_RESEL_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : LRRC发给TRRC指示小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usPrimaryCode;

    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT8                                               aucReserved[2];

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;
}LRRC_TRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_CELL_RESEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示小区搜索结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32                enRslt;

    /* 当usResult 原因值为LRRC_GURRC_CELL_RESEL_NOT_EPLMNS时，
    stPlmnIdInfo 有效,该数据为小区的PLMN IDs 信息*/
    LRRC_GURRC_PLMN_ID_INFO_LIST_STRU                       stPlmnIdInfoList;

    /* 当usResult 原因值为LRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL,
       LRRC_GURRC_CELL_RESEL_CELL_BARRED, LRRC_GURRC_CELL_RESEL_ACCESS时，
       ulTimerVaule有效,单位 :毫秒*/
    VOS_UINT32                                              ulTimerValue;

    /* 当LT重选无法驻留时，填写此lQrxLevValue, 有符号、八倍精度、为按照协议计算后的实际门限值 */
    /* 此参数只能与LRRC_GURRC_CELL_RESEL_PATH_LOSS_CHECK_FAIL同时使用 */
    VOS_INT16                                               sQrxlevMin;
    VOS_INT16                                               sQqualMin;
    /* 预留位 */
    VOS_UINT32                                              aulReserved[4];

}TRRC_LRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_CELL_RESEL_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LRRC指示TRRC停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_CELL_RESEL_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示LRRC已停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_CELL_RESEL_STOP_CNF_STRU;

/* v7r2 code begin */

/*****************************************************************************
 结构名    : LRRC_GURRC_REDIR_CELL_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : 重定向中携带的小区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usPrimaryCode;
    VOS_UINT16                                              usArfcn;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usSysInfoLen;
    VOS_UINT8                                               aucData[LRRC_WRRC_UTRAN_BCCH_CONTAINER_MAX_BYTE_LEN];
}LRRC_TRRC_REDIR_CELL_INFO_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_REDIR_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示LRRC重定向信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcnNum;
    VOS_UINT16                                              usCellInfoNum;
    VOS_UINT16                                              ausArfcn[LRRC_TRRC_REDIR_FREQ_MAX_MUN];
    LRRC_TRRC_REDIR_CELL_INFO_STRU                          astCellInfo[LRRC_WRRC_REDIR_CELL_MAX_MUN];
}LRRC_TRRC_REDIR_INFO_LIST_STRU;
/* v7r2 code end */

/*****************************************************************************
 结构名    : LRRC_TRRC_REDIRECTED_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : LRRC发给TRRC指示重定向流程启动
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    /* v7r2 code begin */
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8                enCellCampedType;
    VOS_UINT8                                               aucReserved[2];

    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enDPriInfoPresent;      /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    LRRC_TRRC_REDIR_INFO_LIST_STRU                          stRedirInfoList;    /* 小区信息 */
    LRRC_GURRC_DEDICATED_PRI_INFO_STRU                      stDPriInfo;             /* 专用优先级信息 */
    /* v7r2 code end */

    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU                  stRedirEutraInfo;
}LRRC_TRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_REDIRECTED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示重定向结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32                enRslt;
}TRRC_LRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_REDIRECTED_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LRRC指示TRRC停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_REDIRECTED_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示LRRC已停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 结构名    :  LRRC_TRRC_HANDOVER_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LRRC指示TRRC启动HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/

    /*LTE可用频点, 大于0，可进行自主FR，否则不可以; 和csfb取与关系*/
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU                  stRedirEutraInfo;

    /* CSFB 标志,1:表示是CSFB, 0: 表示不是CSFB */
    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enCsfbInd;
    VOS_UINT8                                               ucReserved;

    VOS_UINT16                                              usHoDatalen;
    VOS_UINT8                                               aucHoData[4];       /*  编码后的HANDOVER TO UTRAN COMMAND 数据*/
}LRRC_TRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_HANDOVER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  TRRC发给LRRC指示切换流程结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32                  enRslt;
}TRRC_LRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_HANDOVER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LRRC指示TRRC停止HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_HANDOVER_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示LRRC已停止HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_SET_DSP_POWER_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  LRRC指示TRRC对DSP省电模式操作
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32                enSetLDspPowerCmd;
}LRRC_TRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_SET_DSP_POWER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示LRRC对EDSP操作完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32             enRslt;
}TRRC_LRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_GETUECAPINFO_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  LRRC指示TRRC对提供UE能力信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usMcc;
    VOS_UINT8                                               aucReserved[2];
}LRRC_TRRC_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_GETUECAPINFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示LRRC对UE能力获取完成
 For UTRA: the octet string contains the INTER RAT HANDOVER INFO message defined in TS 25.331 [19].
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16                 enRslt;
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucUtranCapInfoData[LRRC_TRRC_UE_CAP_UTRAN_MAX_LEN];
}TRRC_LRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_IDLE_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示启动测量
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU                    stUtranCellInfoList;
}LRRC_TRRC_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_IDLE_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : TRRC发给LRRC指示IDLE测量启动结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}TRRC_LRRC_IDLE_MEASURE_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_IDLE_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示IDLE测量结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU                   stUtranMeasResult;
}TRRC_LRRC_IDLE_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_CONNECTED_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给LRRC指示启动CONNECTED测量
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    LRRC_GURRC_MEAS_CMD_ENUM_UINT16                         enMeasCmd;
    LRRC_GURRC_UTRAN_CELL_INFO_LIST_STRU                    stUtranCellInfoList;
}LRRC_TRRC_CONNECTED_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_CONNECTED_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示CONNECTED测量启动结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    LRRC_GURRC_MEAS_RESULT_ENUM_UINT32                      enRslt;
}TRRC_LRRC_CONNECTED_MEASURE_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_LRRC_CONNECTED_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给TRRC指示CONNECTED 测量结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GURRC_LRRC_UTRAN_MEAS_RESULT_IND_STRU                   stUtranMeasResult;
}TRRC_LRRC_CONNECTED_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    :    LRRC_TRRC_RELALL_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  LRRC指示TRRC执行RelAll操作
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}LRRC_TRRC_RELALL_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_LRRC_RELALL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示LRRC执行RelAll操作完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_LRRC_RELALL_CNF_STRU;


/*****************************************************************************
 结构名    : LRRC_TRRC_MSG_DATA
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_TRRC_MSG_DATA数据结构，用于生成ASN文件
*****************************************************************************/
typedef struct
{
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32                          enMsgId;            /*_H2ASN_MsgChoice_Export LRRC_TRRC_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_TRRC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_TRRC_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : LRRC_TRRCInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_TRRCInterface_MSG数据结构,用于生成ASN文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_TRRC_MSG_DATA                                      stMsgData;
}LRrcTRrcInterface_MSG;

/*****************************************************************************
 结构名    : TRRC_LRRC_FR_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示LRRC获取LTE自主FR频点
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
}TRRC_LRRC_FR_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_TRRC_FR_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC指示TRRC获取LTE自主FR频点的结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    LRRC_TRRC_MSG_TYPE_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
    LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU    stRedirEutraInfo;
}LRRC_TRRC_FR_INFO_CNF_STRU;

#define MAX_LATEST_BAND39_CELL_NUM  4
/*****************************************************************************
 结构名    : TRRC_LRRC_FR_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示LRRC获取LTE自主FR频点
*****************************************************************************/
typedef struct
{
    VOS_UINT32         ulCenterFreq;
    VOS_UINT32         ulLowFreq;
    VOS_UINT32         ulHighFreq;
    LPS_32K_TIMESTAMP  stTstamp;
}LTE_SINGLE_CELL_FREQ_INFO;

/*****************************************************************************
 结构名    : TRRC_LRRC_FR_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示LRRC获取LTE自主FR频点
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulValidNum;
    LTE_SINGLE_CELL_FREQ_INFO  astCellFreqInfo[MAX_LATEST_BAND39_CELL_NUM];
}LTE_LATEST_BAND39_CELL_FREQ_INFO;


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
 Function Name   : Trrc_Get_LatestLteBand39CellInfo
 Description     : LTE提供给TDS最近成功MIB的LTE Band39小区，用于TDS剔除重复区间的
                   搜索
 Input           :
 Output          : None
 Return          : LTE_LATEST_BAND39_CELL_FREQ_INFO

 History         :
    1.韩磊  00133115      2015-11-27  Draft Enact

*****************************************************************************/
extern LTE_LATEST_BAND39_CELL_FREQ_INFO* Trrc_Get_LatestLteBand39CellInfo(VOS_VOID);


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

#endif /* end of LRRC_TRRCInterface.h */


