/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TRrcGrrInterface.h
  Description     : TDS RRC与GRR之间接口文件
  History         :
      1.Xuruimei 49630       2011-10-08   Draft Enact

******************************************************************************/

#ifndef __TRRC_GRRINTERFACE_H__
#define __TRRC_GRRINTERFACE_H__

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
#include  "TRrcGrrCommInterface.h"

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

#define TRRC_GRR_MSG_HDR                (PS_MSG_ID_TRRC_TO_GRR_BASE)
#define GRR_TRRC_MSG_HDR                (PS_MSG_ID_GRR_TO_TRRC_BASE)


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
enum TRRC_GRR_MSG_TYPE_ENUM
{
    /* G -> T Cell Resel */
    ID_GRR_TRRC_CELL_RESEL_REQ                 = (GRR_TRRC_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_REQ_STRU */
    ID_TRRC_GRR_CELL_RESEL_CNF                 = (TRRC_GRR_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_CNF_STRU */
    ID_GRR_TRRC_CELL_RESEL_STOP_REQ            = (GRR_TRRC_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_STOP_REQ_STRU */
    ID_TRRC_GRR_CELL_RESEL_STOP_CNF            = (TRRC_GRR_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_STOP_CNF_STRU */

    /* G -> T Redirect */
    ID_GRR_TRRC_REDIRECTED_REQ                 = (GRR_TRRC_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_REQ_STRU */
    ID_TRRC_GRR_REDIRECTED_CNF                 = (TRRC_GRR_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_CNF_STRU */
    ID_GRR_TRRC_REDIRECTED_STOP_REQ            = (GRR_TRRC_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_STOP_REQ_STRU */
    ID_TRRC_GRR_REDIRECTED_STOP_CNF            = (TRRC_GRR_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_STOP_CNF_STRU */

    /* G -> T CCO */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_REQ          = (GRR_TRRC_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_REQ_STRU */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_CNF          = (TRRC_GRR_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ     = (GRR_TRRC_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF     = (TRRC_GRR_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU */

    /* G -> T 获取HO信息 */
    ID_GRR_TRRC_IRAT_HANDOVER_INFO_REQ         = (GRR_TRRC_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice GRR_TRRC_IRAT_HANDOVER_INFO_REQ_STRU */
    ID_TRRC_GRR_IRAT_HANDOVER_INFO_CNF         = (TRRC_GRR_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice TRRC_GRR_IRAT_HANDOVER_INFO_CNF_STRU */

    /* G -> T HO */
    ID_GRR_TRRC_HANDOVER_REQ                   = (GRR_TRRC_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_REQ_STRU */
    ID_TRRC_GRR_HANDOVER_CNF                   = (TRRC_GRR_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_CNF_STRU */
    ID_GRR_TRRC_HANDOVER_STOP_REQ              = (GRR_TRRC_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_STOP_REQ_STRU */
    ID_TRRC_GRR_HANDOVER_STOP_CNF              = (TRRC_GRR_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_STOP_CNF_STRU */

    /* G -> T 低功耗 */
    ID_GRR_TRRC_SET_DSP_POWER_REQ              = (GRR_TRRC_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice GRR_TRRC_SET_DSP_POWER_REQ_STRU */
    ID_TRRC_GRR_SET_DSP_POWER_CNF              = (TRRC_GRR_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice TRRC_GRR_SET_DSP_POWER_CNF_STRU */

    /* G -> T Meas */
    ID_GRR_TRRC_MEASURE_REQ                    = (GRR_TRRC_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice GRR_TRRC_MEASURE_REQ_STRU */
    ID_TRRC_GRR_MEASURE_CNF                    = (TRRC_GRR_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice TRRC_GRR_MEASURE_CNF_STRU */
    ID_TRRC_GRR_MEASURE_IND                    = (TRRC_GRR_MSG_HDR + 0x0b),     /* _H2ASN_MsgChoice TRRC_GRR_MEASURE_IND_STRU */

    /* T -> G Cell Resel*/
    ID_TRRC_GRR_CELL_RESEL_REQ                 = (TRRC_GRR_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_REQ_STRU */
    ID_GRR_TRRC_CELL_RESEL_CNF                 = (GRR_TRRC_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_CNF_STRU */
    ID_TRRC_GRR_CELL_RESEL_STOP_REQ            = (TRRC_GRR_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_RESEL_STOP_REQ_STRU */
    ID_GRR_TRRC_CELL_RESEL_STOP_CNF            = (GRR_TRRC_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_RESEL_STOP_CNF_STRU */

    /* T -> G Redirect */
    ID_TRRC_GRR_REDIRECTED_REQ                 = (TRRC_GRR_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_REQ_STRU */
    ID_GRR_TRRC_REDIRECTED_CNF                 = (GRR_TRRC_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_CNF_STRU */
    ID_TRRC_GRR_REDIRECTED_STOP_REQ            = (TRRC_GRR_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice TRRC_GRR_REDIRECTED_STOP_REQ_STRU */
    ID_GRR_TRRC_REDIRECTED_STOP_CNF            = (GRR_TRRC_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice GRR_TRRC_REDIRECTED_STOP_CNF_STRU */

    /* T -> G CCO */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_REQ          = (TRRC_GRR_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_CNF          = (GRR_TRRC_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_CNF_STRU */
    ID_TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ     = (TRRC_GRR_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU */
    ID_GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF     = (GRR_TRRC_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU */

    /* T -> G HO */
    ID_TRRC_GRR_HANDOVER_REQ                   = (TRRC_GRR_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_REQ_STRU */
    ID_GRR_TRRC_HANDOVER_CNF                   = (GRR_TRRC_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_CNF_STRU */
    ID_TRRC_GRR_HANDOVER_STOP_REQ              = (TRRC_GRR_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice TRRC_GRR_HANDOVER_STOP_REQ_STRU */
    ID_GRR_TRRC_HANDOVER_STOP_CNF              = (GRR_TRRC_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice GRR_TRRC_HANDOVER_STOP_CNF_STRU */

    /* T -> G OOS PLMN SEARCH */
    ID_TRRC_GRR_PLMN_SEARCH_REQ                = (TRRC_GRR_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice TRRC_GRR_PLMN_SEARCH_REQ_STRU */
    ID_GRR_TRRC_PLMN_SEARCH_CNF                = (GRR_TRRC_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice GRR_TRRC_PLMN_SEARCH_CNF_STRU */
    ID_TRRC_GRR_PLMN_SEARCH_STOP_REQ           = (TRRC_GRR_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice TRRC_GRR_PLMN_SEARCH_STOP_REQ_STRU */
    ID_GRR_TRRC_PLMN_SEARCH_STOP_CNF           = (GRR_TRRC_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice GRR_TRRC_PLMN_SEARCH_STOP_CNF_STRU */

    /* T -> G 低功耗 */
    ID_TRRC_GRR_SET_DSP_POWER_REQ              = (TRRC_GRR_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice TRRC_GRR_SET_DSP_POWER_REQ_STRU */
    ID_GRR_TRRC_SET_DSP_POWER_CNF              = (GRR_TRRC_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice GRR_TRRC_SET_DSP_POWER_CNF_STRU */

    /* T -> G Get Ue Capability Info */
    ID_TRRC_GRR_GETUECAPINFO_REQ               = (TRRC_GRR_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice TRRC_GRR_GETUECAPINFO_REQ_STRU */
    ID_GRR_TRRC_GETUECAPINFO_CNF               = (GRR_TRRC_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice GRR_TRRC_GETUECAPINFO_CNF_STRU */

    /* T -> G Meas */
    ID_TRRC_GRR_MEASURE_REQ                    = (TRRC_GRR_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice TRRC_GRR_MEASURE_REQ_STRU */
    ID_GRR_TRRC_MEASURE_CNF                    = (GRR_TRRC_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice GRR_TRRC_MEASURE_CNF_STRU */
    ID_GRR_TRRC_MEASURE_IND                    = (GRR_TRRC_MSG_HDR + 0x19),     /* _H2ASN_MsgChoice GRR_TRRC_MEASURE_IND_STRU */

    /* T -> G  Gsm Cell Bsic Verify  */
    ID_TRRC_GRR_BSIC_VERIFIED_REQ              = (TRRC_GRR_MSG_HDR + 0x1a),     /* _H2ASN_MsgChoice TRRC_GRR_BSIC_VERIFIED_REQ_STRU */
    ID_GRR_TRRC_BSIC_VERIFIED_CNF              = (GRR_TRRC_MSG_HDR + 0x1a),     /* _H2ASN_MsgChoice GRR_TRRC_BSIC_VERIFIED_CNF_STRU */
    ID_GRR_TRRC_BSIC_VERIFIED_IND              = (GRR_TRRC_MSG_HDR + 0x1b),     /* _H2ASN_MsgChoice GRR_TRRC_BSIC_VERIFIED_IND_STRU */

    /* T -> G RelAll */
    ID_TRRC_GRR_RELALL_REQ                     = (TRRC_GRR_MSG_HDR + 0x1c),     /* _H2ASN_MsgChoice TRRC_GRR_RELALL_REQ_STRU */
    ID_GRR_TRRC_RELALL_CNF                     = (GRR_TRRC_MSG_HDR + 0x1c),     /* _H2ASN_MsgChoice GRR_TRRC_RELALL_CNF_STRU */

    ID_TRRC_GRR_MSG_TYPE_BUTT

};
typedef VOS_UINT32  TRRC_GRR_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : GRR_TRRC_CELL_RESEL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RR接收到网络发送的小区重选命令消息，通过此原语指示TRRC进行小区重选
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU                        stUtranTddCell;     /* 重选到 TDS目标小区结构 */
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;       /* TDS: 不使用此IE */
    TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8                  enCampType;        /* 需要目标小区是按照ANYCELL或者SUITABLE驻留准则进行驻留 */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved[2];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}GRR_TRRC_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_CELL_RESEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示小区搜索结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;
    VOS_UINT32                                              ulTBarLen;          /* 单位为ms，仅在enCnf为EN_CELL_RESEL_FAIL_REASON_CELL_BAR时有效 */
    /* 当GT重选无法驻留时，填写此sQrxLevValue, 有符号、八倍精度、为按照协议计算后的实际门限值 */
    /* 此参数只能与TRRC_GRR_CELL_RESEL_S_OR_C1_CHECK_FAIL同时使用 */
    VOS_INT16                                               sQrxlevMin;
    /*预留位*/
    VOS_INT16                                               sReserved;
}TRRC_GRR_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 结构名    :GRR_TRRC_CELL_RESEL_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :GRR指示TRRC停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_CELL_RESEL_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示GRR已停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_REDIRECTED_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR指示TRRC进行重定向请求结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    /* 在REDIR INFO 指示搜索的时间 单位:毫秒,目前固定10000ms，
    在此时间内,TLRRC只能在指示的频点内进行搜索，超时后，可以任意点上搜索，TRRC目前不使用 */
    VOS_UINT16                                              usSearchTimer;

	VOS_UINT8												aucReserved1[1];
    VOS_UINT8                                               ucUtranTddCellCnt;  /* total valid cell number */
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU                        astUtranTddCell[RR_TRRC_MAX_UTRAN_TDD_CELL_NUM];

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved2[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}GRR_TRRC_REDIRECTED_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_REDIRECTED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示重定向结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32                  enRslt;
}TRRC_GRR_REDIRECTED_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_REDIRECTED_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR指示TRRC停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_REDIRECTED_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示GRR已停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_CELL_CHANGE_ORDER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR指示TRRC启动CCO
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU                        stUtranTddCell;     /* CCO到 TDS目标小区结构 */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}GRR_TRRC_CELL_CHANGE_ORDER_REQ_STRU;

/*****************************************************************************
 结构名    :   TRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示GRR完成CCO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;

    /* 当usResult 原因值为TRRC_GRR_CELL_RESEL_CCO_CELL_BARRED时，
       ulTimerVaule值为TRRC指示的惩罚时间,其它原因值不适用此字段 ,单位 :毫秒 */
    VOS_UINT32                                              ulTimerValue; 
}TRRC_GRR_CELL_CHANGE_ORDER_CNF_STRU;

/*****************************************************************************
 结构名    :  GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  GRR指示TRRC停止CCO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_CHANGE_ORDER_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :   TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示GRR已停止CCO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_CHANGE_ORDER_STOP_CNF_STRU;

/*******************************************************************************
 结构名    : GRR_TRRC_IRAT_HANDOVER_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR向TRR获取inter rat hand over info。
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /* _H2ASN_Skip */
    PS_BOOL_ENUM_UINT8                                      enNeedCmprVer;      /* 是否需要压缩版本的信息 */
    VOS_UINT8                                               aucReserved[3];     /* 保留字段,便于将来扩展 */
}GRR_TRRC_IRAT_HANDOVER_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_IRAT_HANDOVER_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR inter rat hand over info。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usDataLen;
    VOS_UINT8                                               aucData[RR_TRRC_INTER_RAT_HANDOVER_INFO_LEN];
}TRRC_GRR_IRAT_HANDOVER_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_HANDOVER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR发给TRRC指示启动切换流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;       /* 信令连接的类型，不使用该IE */
    RRC_CIPHER_ACTIVE_ENUM_UINT32                           enCipherActiveFlg;  /* 指示GSM加密是否激活 */
    VOS_UINT16                                              usHandOverInfoLen;  /* 切换时空口消息中包含的信息的长度 */
    VOS_UINT8                                               aucHandOverInfo[2]; /* 切换时空口消息中包含的信息的地址 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}GRR_TRRC_HANDOVER_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_HANDOVER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示切换流程结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32                    enRslt;
}TRRC_GRR_HANDOVER_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_HANDOVER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR指示TRRC停止HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_HANDOVER_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示GRR已停止HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 结构名    :    GRR_TRRC_SET_DSP_POWER_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  GRR指示TRRC对DSP上下电操作
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_CMD_ENUM_UINT32                  enSetGDspPowerCmd;
}GRR_TRRC_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 结构名    :    TRRC_GRR_SET_DSP_POWER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示GRR对DSP操作完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;             /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_RESULT_ENUM_UINT32               enRslt;
}TRRC_GRR_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_UTRAN_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UTRAN异系统信息
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcn;

   /* 当usCellIdNum = 0时，表示仅仅有频点信息而无小区信息 */
   VOS_UINT16                                               usCellIdNum;
   /* xrm 确认，ausUtranCellIdInfo的填法 */
   VOS_UINT16                                               ausUtranCellIdInfo[TRRC_GRR_MAX_UTRAN_CELL_PER_FREQ_NUM];
}TRRC_UTRAN_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_UTRAN_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UTRAN异系统信息列表
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcnNum;

   /****************************************************************************
   频点信息中高优先级频点个数，则为IDLE态下有效, 连接态下该字段为保留，
   如果usArfcnNum =  usHighPriNum，表示仅仅只有高优先级频点，
   astUtranCellInfo存放顺序为:高优先级信息 -> 中优先级信息 -> 低优先级信息
   ****************************************************************************/
   VOS_UINT16                                               usHighPrioNum;
   TRRC_UTRAN_CELL_INFO_STRU                                astUtranCellInfo[TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
}TRRC_UTRAN_CELL_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : TRRC_UTRAN_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : UTRAN CELL 测量结果
             1. 如果MS尝试去测量这个小区，但没有测到这个小区，则上报最低值-116 * 8。
             2. 如果MS由于时间原因没有去测这个小区，则上报无效值TRRC_GRR_INVALID_iNVALID_RSCP。
             3. 如果MS尝试去测量这个小区，且测到了这个小区，上报该小区的测量结果。
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usCellParamId;
    VOS_INT16                                               sRscp;              /* 精度1/8 */
}TRRC_UTRAN_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : TRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : UTRAN 单个频点 测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_INT16                                               sRssi;              /* 精度1/8，GTL目前不使用 */
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usCellNum;
    TRRC_UTRAN_CELL_MEAS_RESULT_STRU                        astUtranCellInfo[TRRC_GRR_MAX_UTRAN_CELL_PER_FREQ_NUM];
}TRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_UTRAN_MEAS_RESULT_IND_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : UTRAN CELL 测量结果列表
            注意： 1. 如果GAS下发了单频点测量，则TRRC最多上报该频点下的 5 个小区测量结果。
                   2. 如果GAS下发的测量请求中一个频点下的小区个数超过了 5 个，则TRRC最多上报该频点下的 5 个小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcnNum;
    VOS_UINT8                                               aucReserved[2];
    TRRC_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU                 astUtranResult[TRRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
}TRRC_GRR_UTRAN_MEAS_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR发给TRRC指示测量配置
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    TRRC_GRR_MEAS_CMD_ENUM_UINT16                           enMeasCmd;
    GRR_TRRC_MEAS_GAS_STATUS_ENUM_UINT8                     enGasStatus;
    VOS_UINT8                                               aucReserved[3];
    TRRC_UTRAN_CELL_INFO_LIST_STRU                          stUtranCellInfoList;
}GRR_TRRC_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示测量配置结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    TRRC_GRR_RESULT_ENUM_UINT8                              enRslt;
    VOS_UINT8                                               aucReserved[1];
}TRRC_GRR_MEASURE_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示测量结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    TRRC_GRR_UTRAN_MEAS_RESULT_IND_STRU                     stMeasResult;
}TRRC_GRR_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_GERAN_CELL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GERAN异系统信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                               usArfcn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                        enBandInd;
}TRRC_GRR_GERAN_CELL_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_GERAN_CELL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GERAN异系统信息
*****************************************************************************/
typedef struct
{
    TRRC_GRR_GERAN_CELL_STRU                                stGCellFreq;
    TRRC_GRR_BSIC_INFO_STRU                                 stBsic;
}TRRC_GRR_GERAN_CELL_INFO_STRU;

/*****************************************************************************
 结构名    :   TRRC_GRR_BSIC_VERIFIED_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示GRR启动BSIC流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usGeranInfoNum;
    TRRC_GRR_VERIFY_TIME_INDEX_ENUM_UINT16                  enVerifyTimeIndex;
    VOS_UINT8                                               aucReserved[2];
    TRRC_GRR_GERAN_CELL_INFO_STRU                           astGeranInfo[TRRC_GRR_GERAN_CELL_FOR_BSIC_MAX_NUM];
}TRRC_GRR_BSIC_VERIFIED_REQ_STRU;

/*****************************************************************************
 结构名    :  GRR_TRRC_BSIC_VERIFIED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  GRR指示TRRC返回BSIC启动结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
}GRR_TRRC_BSIC_VERIFIED_CNF_STRU;

/*****************************************************************************
 结构名    :   GRR_TRRC_BSIC_VERIFIED_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   GRR指示TRRC，BSIC验证结果
*****************************************************************************/
typedef struct
{
    TRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;
    VOS_UINT32                                              ulTimeAlignment;
    VOS_INT32                                               lFNOffset;
}GRR_TRRC_BSIC_VERIFIED_RESULT_STRU;

/*****************************************************************************
 结构名    :   GRR_TRRC_BSIC_VERIFIED_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   GRR指示TRRC，BSIC验证结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usArfcnNum;
    GRR_TRRC_BSIC_VERIFIED_RESULT_STRU                      astGeranBsicVerifedResult[TRRC_GRR_GERAN_CELL_FOR_BSIC_MAX_NUM];
}GRR_TRRC_BSIC_VERIFIED_IND_STRU;

/*****************************************************************************
 结构名    :   TRRC_SAVE_GCELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示GRR启动重选携带的GSM小区信息
*****************************************************************************/
typedef struct
{
    TRRC_GRR_BSIC_INFO_STRU                                 stBsicInfo;         /* BSIC值 */
    VOS_UINT16                                              usBcchArcfn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;
    VOS_INT32                                               lFNOffset;
    VOS_UINT32                                              ulTimeAlignmt;
    VOS_INT16                                               sRxlev;             /* G小区信号电平，单位是dBm,没有测到信号电平时赋值为RR_TRRC_INVALID_RXLEV */
    VOS_UINT8                                               aucReserved[2];
}TRRC_SAVE_GCELL_INFO_STRU;

/*****************************************************************************
 结构名    :   TRRC_GRR_CELL_RESEL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   TRRC指示GRR启动重选
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_SAVE_GCELL_INFO_STRU                               stGsmCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;

    TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8                  enCampType;

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved[2];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}TRRC_GRR_CELL_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_CELL_RESEL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR发给TRRC指示小区重选结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;

    /* 当usResult 原因值为
       TRRC_GURRC_CELL_RESEL_CELL_BARRED时，ulTimerVaule值为20min（20*60*1000）, TRRC_GURRC_CELL_RESEL_ACCESS时，
       ulTimerVaule为100s（100*1000）,单位 :毫秒*/
    VOS_UINT32                                              ulTimerValue;
    /* 当usResult 原因值为TRRC_GRR_CELL_RESEL_S_OR_C1_CHECK_FAIL时， sC1Param参数有效
        表示与C1值计算相关的参数，TRRC计算公式C1= sRxlev- sC1Param, Rxlev为一精度   */
    VOS_INT16                                               sC1Param;
    
    VOS_UINT8                                               aucReserved[2]; 
}GRR_TRRC_CELL_RESEL_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_CELL_RESEL_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示GRR停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_RESEL_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :   GRR_TRRC_CELL_RESEL_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   GRR指示TRRC已停止小区搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_RESEL_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_REDIRECTED_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示重定向流程启动.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/

    TRRC_GRR_CELL_CAMPEDON_TYPE_ENUM_UINT8                  enCellCampedType;
    VOS_UINT8                                               aucReserved1[3];

    /* ulGsmCellCnt =0表示全频搜索，否则先搜这些小区，搜不到再全频搜 */
    VOS_UINT32                                              ulGsmCellCnt;
    RRC_SAVE_CELL_INFO_FOR_GAS_ST                           astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];   /* 每个GSM小区信息 */

    VOS_UINT32                                              ulWaitTimeLen;                          /* wait time时间，单位是ms */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               aucReserved2[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}TRRC_GRR_REDIRECTED_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_REDIRECTED_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR发给TRRC指示重定向结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32                  enRslt;
}GRR_TRRC_REDIRECTED_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_REDIRECTED_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示GRR停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_REDIRECTED_STOP_REQ_STRU;

/*****************************************************************************
 结构名    :  GRR_TRRC_REDIRECTED_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  GRR指示TRRC已停止重定向流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_REDIRECTED_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GSM_GREAN_SYS_INFO_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示CCO的系统消息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulCnt;              /* 指示数组长度1-23*//* 有效值为1~23 */
    VOS_UINT8                                               aucGeranSysInfoBlock[TRRC_RR_MAX_GERAN_SI_LEN];
    VOS_UINT8                                               aucReserved[1];
}TRRC_GSM_GREAN_SYS_INFO_ST;

/*****************************************************************************
 结构名    : TRRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示CCO的系统消息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucReserved[2];
    RRC_GSM_GERAN_SYS_INFO_ENUM_UINT8                       enGeranInfoInd;     /* ucGeranSysInfoCnt为0时，此值无效 */
    VOS_UINT8                                               ucGeranSysInfoCnt;  /* 有效值为 0~ 8 */
    TRRC_GSM_GREAN_SYS_INFO_ST                              stGeranSysInfo[TRRC_RR_MAX_GERAN_SI_CNT];
}TRRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST;

/*****************************************************************************
 结构名    : TRRC_CELL_CHANGE_GSM_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示CCO信息
*****************************************************************************/
typedef struct
{
    TRRC_GRR_BSIC_INFO_STRU                                 stBsicInfo;         /* BSIC值 */
    VOS_INT16                                               sRxlev;             /* G小区信号电平，单位是dBm,没有测到信号电平时赋值为RR_TRRC_INVALID_RXLEV */
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;
    VOS_UINT16                                              usBcchArfcn;
    VOS_UINT8                                               ucNCmodeFlag;       /* NCMode存在标志， 0表示不存在，1表示存在 */
    VOS_UINT8                                               ucNCmode;           /* NCMode 网络控制模式，用于是否上报测量报告。 确认*/
    TRRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST             stGeranSysInfo;
}TRRC_CELL_CHANGE_GSM_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示CCO流程启动
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_CELL_CHANGE_GSM_CELL_INFO_STRU                     stGsmCellInfo;      /* GSM小区信息 */

    /* 专有优先级信息, 0: 表示不存在，1 表示存在*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucReserved[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}TRRC_GRR_CELL_CHANGE_ORDER_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_CELL_CHANGE_ORDER_CNF_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : GRR发给TRRC指示CCO结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32              enRslt;
}GRR_TRRC_CELL_CHANGE_ORDER_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示GRR停止CCO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_CELL_CHANGE_ORDER_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR指示TRRC已停止CCO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_CELL_CHANGE_ORDER_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_HANDOVER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示HO流程启动, 协议6.2.2
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    RRC_HANDOVER_GSM_GPRS_INFO_ST                           stGsmGprsCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32                             enSignalInfo;
    VOS_INT16                                               sTaValue;           /* 范围 [-24,256],单位 1/8 chip, 6400 chip = 5ms */
    PS_BOOL_ENUM_UINT8                                      enLteOriginatedFlg; /* 当前业务是否L下发起的CSFB。优先级高于准FR */
    VOS_UINT8                                               ucReserved;
    TRRC_GRR_FAST_RETURN_STRU                               stFastReturn;
}TRRC_GRR_HANDOVER_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_HANDOVER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR发给TRRC指示HO结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32                    enRslt;
}GRR_TRRC_HANDOVER_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_HANDOVER_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC指示GRR停止HO流程
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_HANDOVER_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_HANDOVER_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR向TRRC回复已停止HO流程确认结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_PLMN_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC出服务区请求GAS搜网
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                              ulGsmCellCnt;       /* 如果有GSM邻区，则只需要找到这些邻区的PLMN即可,取值范围 0 ~ 32,0表示没有邻区，需要GAS作全频段搜索 */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST                           astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];                 /* 每个GSM小区信息 */

    VOS_UINT32                                              ulAvailPlmnIdNum;   /* PLMN ID个数 */
    TRRC_GRR_PLMN_ID_STRU                                   astAvailPlmnIdList[TRRC_GRR_MAX_AVAIL_PLMN_NUM];            /* PlMN标识 */
}TRRC_GRR_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_LOW_PLMN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR向TRRC回复的低优先级PLMN ID 结构
*****************************************************************************/
typedef struct
{
    TRRC_GRR_PLMN_ID_STRU                                   stPlmnId;           /* PLMN ID */
    VOS_INT32                                               lRscp;              /* RSCP测量值 */
}TRRC_GRR_LOW_PLMN_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_PLMN_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR指示TRRC回复PLMN列表结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulHighPlmnNum;      /* 高质量PLMN的个数 */
    VOS_UINT32                                              ulLowPlmnNum;       /* 低质量PLMN的个数 */
    TRRC_GRR_PLMN_ID_STRU                                   astHighPlmnList[TRRC_GRR_MAX_HIGH_PLMN_NUM];  /* 高质量PLMN列表   */
    TRRC_GRR_LOW_PLMN_INFO_STRU                             astLowPlmnList[TRRC_GRR_MAX_LOW_PLMN_NUM];    /* 低质量PLMN列表   */
}TRRC_GRR_PLMN_ID_LIST_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_PLMN_SEARCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR向TRRC回复的出服务区搜网确认结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_RESULT_ENUM_UINT8                              enRslt;
    VOS_UINT8                                               aucReserved[3];

    /* enResult原因值为TRRC_GRR_RESULT_SUCC时,才需要查找是否有PLMN，如果没有PLMN，则认为也是失败 */
    TRRC_GRR_PLMN_ID_LIST_STRU                              stPlmnIdList;       /* 上报的PLMN ID列表 */
}GRR_TRRC_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_PLMN_SEARCH_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC通知GRR停止出服务区搜网流程结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_PLMN_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_PLMN_SEARCH_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR向TRRC回复的已停止出服务区搜网流程确认结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_PLMN_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 结构名    :    TRRC_GRR_SET_DSP_POWER_REQ_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  TRRC指示GRR对DSP省电模式操作
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_CMD_ENUM_UINT32                  enSetGDspPowerCmd;
}TRRC_GRR_SET_DSP_POWER_REQ_STRU;

/*****************************************************************************
 结构名    :    GRR_TRRC_SET_DSP_POWER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   GRR指示TRRC对DSP操作完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                          enMsgId;             /*_H2ASN_Skip*/
    TRRC_GRR_SET_DSP_POWER_RESULT_ENUM_UINT32              enRslt;
}GRR_TRRC_SET_DSP_POWER_CNF_STRU;

/*****************************************************************************
 结构名    :  TRRC_GRR_GETUECAPINFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  TRRC指示GRR 提供UE能力信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}TRRC_GRR_GETUECAPINFO_REQ_STRU;

/*****************************************************************************
 结构名    :    GRR_TRRC_GETUECAPINFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   GRR指示TRRC对UE能力获取完成,GERAN UE CAP填写原则见下

For GERAN CS: the octet string contains the concatenated string of the Mobile Station Classmark 2
and Mobile Station Classmark 3. The first 5 octets correspond to Mobile Station Classmark 2
and the following octets correspond to Mobile Station Classmark 3. The Mobile Station Classmark 2
is formatted as 'TLV' and is coded in the same way as the Mobile Station Classmark 2 information
element in TS 24.008 [49]. The first octet is the Mobile station classmark 2 IEI and its value shall
be set to 33H. The second octet is the Length of mobile station classmark 2 and its value shall be
set to 3. The octet 3 contains the first octet of the value part of the Mobile Station Classmark 2
information element, the octet 4 contains the second octet of the value part of the Mobile Station
Classmark 2 information element and so on. For each of these octets, the first/ leftmost/ most significant
bit of the octet contains b8 of the corresponding octet of the Mobile Station Classmark 2. The Mobile
Station Classmark 3 is formatted as 'V' and is coded in the same way as the value part in the Mobile
station classmark 3 information element in TS 24.008 [49]. The sixth octet of this octet string contains
octet 1 of the value part of Mobile station classmark 3, the seventh of octet of this octet string contains
octet 2 of the value part of Mobile station classmark 3 and so on. Note.


For GERAN PS: the encoding of UE capabilities is formatted as 'V' and is coded in the same way as the
value part in the MS Radio Access Capability information element in TS 24.008 [49].
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32       enMsgId;                                /*_H2ASN_Skip*/
    TRRC_GRR_RESULT_ENUM_UINT8          enRslt;

    VOS_UINT8                           ucClassmark2Len;                        /* Classmark2 长度,不包含TRRC或WRR自已填充的IEI */
    VOS_UINT8                           aucClassmark2[GSM_CLASSMARK2_MAX_LEN];  /* Classmark2 内容 */

    VOS_UINT8                           ucClassmark3Len;                        /* Classmark3 长度,不包含TRRC或WRR自已填充的IEI */
    VOS_UINT8                           aucClassmark3[GSM_CLASSMARK3_MAX_LEN];  /* Classmark3 内容 */

    VOS_UINT8                           aucReserved[1];                         /* 4字节对齐，保留 */
}GRR_TRRC_GETUECAPINFO_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_IRAT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GERAN异系统信息列表
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcnNum;

   /****************************************************************************
   频点信息中高优先级频点个数，IDLE态下有效，连接态该字段为保留，
   如果usArfcnNum =  usHighPriNum，表示仅仅只有高优先级频点，
   astGeranCellInfo存放顺序为:高优先级信息 -> 中优先级信息 -> 低优先级信息
   数组下标为GSM小区的CELL ID
   ****************************************************************************/
   VOS_UINT16                                               usHighPrioNum;
   VOS_UINT16                                               usMgsmNum;          /* GSM分组组数，连接态有效，IDLE态该字段保留 */
   VOS_UINT8                                                aucReserved[2];
   TRRC_GRR_GERAN_CELL_STRU                                 astGeranCellInfo[TRRC_GRR_GERAN_ARFCN_MAX_NUM];
}TRRC_GRR_IRAT_INFO_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_IDLE_MEASURE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC发给GRR指示启动IDLE测量
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    TRRC_GRR_MEAS_CMD_ENUM_UINT16                           enMeasCmd;
    TRRC_GRR_MEAS_TAS_STATUS_ENUM_UINT8                     enTasStatus;
    VOS_UINT8                                               aucReserved[3];
    TRRC_GRR_IRAT_INFO_STRU                                 stInterRatInfo;
}TRRC_GRR_MEASURE_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_MEASURE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR发给TRRC指示测量启动结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[1];
    TRRC_GRR_RESULT_ENUM_UINT8                              enRslt;
}GRR_TRRC_MEASURE_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_GERAN_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GERAN CELL 测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    RRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;          /* 保持L->W时测量请求消息中的频段指示一致 */
    VOS_INT16                                               sRssi;              /* sRssi 取值范围[-110 * 8,-48 * 8],单位:dbm,精度1/8 */
    VOS_UINT8                                               aucReserved[2];
}GRR_TRRC_GERAN_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_GERAN_MEAS_RESULT_IND_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  : GERAN CELL 测量结果列表
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcnNum;
    VOS_UINT8                                               aucReserved[2];
    GRR_TRRC_GERAN_CELL_MEAS_RESULT_STRU                    astGeranCellResult[TRRC_GRR_GERAN_ARFCN_MAX_NUM];
}GRR_TRRC_GERAN_MEAS_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : GRR_TRRC_MEASURE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GRR发给TRRC指示测量结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    GRR_TRRC_GERAN_MEAS_RESULT_IND_STRU                     stMeasResult;
}GRR_TRRC_MEASURE_IND_STRU;

/*****************************************************************************
 结构名    :  TRRC_GRR_RELALL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  TRRC指示GRR执行RelAll操作

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    TRRC_GRR_RELALL_REASON_ENUM_UINT8                       enRelReason;
    VOS_UINT8                                               aucReserved[3];
}TRRC_GRR_RELALL_REQ_STRU;

/*****************************************************************************
 结构名    :   GRR_TRRC_RELALL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :   GRR指示TRRC执行RelAll操作完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                                               aucReserved[4];
}GRR_TRRC_RELALL_CNF_STRU;

/*****************************************************************************
 结构名    : TRRC_GRR_MSG_DATA
 协议表格  :
 ASN.1描述 :
 结构说明  : TRRC_GRR_MSG_DATA数据结构，用于生成ASN文件
*****************************************************************************/
typedef struct
{
    TRRC_GRR_MSG_TYPE_ENUM_UINT32                           enMsgId;            /*_H2ASN_MsgChoice_Export TRRC_GRR_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                               aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TRRC_GRR_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TRRC_GRR_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : TRrcGrrInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : TRrcGrrInterface_MSG数据结构,用于生成ASN文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TRRC_GRR_MSG_DATA                                       stMsgData;
}TRrcGrrInterface_MSG;


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

#endif /* end of TRrcGrrInterface.h */

