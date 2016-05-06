/******************************************************************************


        @(#)Copyright(C)2015,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : LppLRrcInterface.h
    Description : 描述LRR与LRRC之间的接口
    History     :
      1.  liutao      222817 2015-06-24  Draft Enact
******************************************************************************/

#ifndef __LPPLRRCINTERFACE_H__
#define __LPPLRRCINTERFACE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "ComInterface.h"
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define LPP_LRRC_MSG_HDR                                    (PS_MSG_ID_LPP_TO_LRRC_BASE)
#define LRRC_LPP_MSG_HDR                                    (PS_MSG_ID_LRRC_TO_LPP_BASE)


/* UE支持最大BAND */
#define LRRC_LPP_MAX_BAND_IND_NUM                           (256)
/* 存放BAND信息最大的数组 */
#define LRRC_LPP_MAX_BAND_IND_ARRAY_NUM                     (8)

/* GNSS数据长度 */
#define LPP_LRRC_MAX_LOCATION_COORDINATES_DATA_LEN          (96)
#define LPP_LRRC_MAX_CHORIZONTAL_VELOCITY_DATA_LEN          (3)
#define LPP_LRRC_MAX_GNSS_TOD_MSEC_DATA_LEN                 (3)


/* ECID上报的最大邻区数 */
#define LRRC_LPP_MAX_ECID_MEAS_NCELL_RESULT_NUM             (32)

/* ECID上报的最大小区数，邻区 + 服务小区 */
#define LRRC_LPP_MAX_ECID_MEAS_RESULT_NUM                   (LRRC_LPP_MAX_ECID_MEAS_NCELL_RESULT_NUM + 1)


/* OTDOA 最大的PRS MUTING INFO 长度  4个字节*/
#define LPP_LRRC_MAX_PRS_MUTING_INFO_LEN                    (4)



/* OTDOA支持最大的异频邻区频点 */
#define LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM          (3)
/* OTDOA支持最大的频点数 */
#define LPP_LRRC_MAX_OTDOA_FREQ_INFO_NUM                    (LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM + 1)

/* OTDOA每个邻区频点上支持的最大小区个数*/
#define LPP_LRRC_MAX_OTDOA_NEIGHBOUR_SINGLE_FREQ_CELL_NUM   (24)

/* OTDOA所有频点支持的最大小区个数*/
#define LRRC_LPP_MAX_OTDOA_NEIGHBOUR_ALL_FREQ_CELL_NUM     \
                              (LPP_LRRC_MAX_OTDOA_NEIGHBOUR_SINGLE_FREQ_CELL_NUM * LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM)







/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : LPP_LRRC_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LPP与LRRC的消息原语类型
*****************************************************************************/
enum LPP_LRRC_MSG_ID_ENUM
{
    /* LPP发给LRRC的原语 */
    ID_LPP_LRRC_GNSS_DATA_INFO_IND                  = (LPP_LRRC_MSG_HDR + 0x00),/* _H2ASN_MsgChoice LPP_LRRC_GNSS_DATA_INFO_IND_STRU */
    ID_LPP_LRRC_ECID_MEAS_REQ                       = (LPP_LRRC_MSG_HDR + 0x01),/* _H2ASN_MsgChoice LPP_LRRC_ECID_MEAS_REQ_STRU */
    ID_LPP_LRRC_OTDOA_MEAS_REQ                      = (LPP_LRRC_MSG_HDR + 0x02),/* _H2ASN_MsgChoice LPP_LRRC_OTDOA_MEAS_REQ_STRU */

    /* LRRC发给LPP的原语 */
    ID_LRRC_LPP_LAS_LCS_CAPABILITY_IND              = (LRRC_LPP_MSG_HDR + 0x00),/* _H2ASN_MsgChoice LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU */
    ID_LRRC_LPP_ECID_MEAS_CNF                       = (LRRC_LPP_MSG_HDR + 0x01),/* _H2ASN_MsgChoice LRRC_LPP_ECID_MEAS_CNF_STRU */
    ID_LRRC_LPP_ECID_MEAS_IND                       = (LRRC_LPP_MSG_HDR + 0x02),/* _H2ASN_MsgChoice LRRC_LPP_ECID_MEAS_IND_STRU */
    ID_LRRC_LPP_OTDOA_MEAS_CNF                      = (LRRC_LPP_MSG_HDR + 0x03),/* _H2ASN_MsgChoice LRRC_LPP_OTDOA_MEAS_CNF_STRU */
    ID_LRRC_LPP_OTDOA_MEAS_IND                      = (LRRC_LPP_MSG_HDR + 0x04),/* _H2ASN_MsgChoice LRRC_LPP_OTDOA_MEAS_IND_STRU */

    ID_LPP_LRRC_MSG_ID_BUTT
};
typedef VOS_UINT32   LPP_LRRC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LPP_LRRC_INFO_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LPP与LRRC信息有效性标记
*****************************************************************************/
enum LPP_LRRC_INFO_FLAG_ENUM
{
    LPP_LRRC_INFO_FLAG_INVALID,
    LPP_LRRC_INFO_FLAG_VALID,
    LPP_LRRC_INFO_FLAG_BUTT
};
typedef VOS_UINT8   LPP_LRRC_INFO_FLAG_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LPP通知LRRC GPS数据类型
*****************************************************************************/
enum LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM
{
    LPP_LRRC_LOC_COOR_ELLIP_POINT,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_ALTI,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_UNCERTAIN_CIRCLE,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_UNCERTAIN_ELLIPS,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_ALTI_AND_UNCERTAIN_ELLIPS,
    LPP_LRRC_LOC_COOR_ELLIP_ARC,
    LPP_LRRC_LOC_COOR_POLYGON,
    LPP_LRRC_LOC_COOR_BUTT
};
typedef VOS_UINT8   LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LPP_LRRC_LCS_MEAS_CMD_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LPP发送LCS的测量命令
*****************************************************************************/
enum LPP_LRRC_LCS_MEAS_CMD_ENUM
{
    LPP_LRRC_LCS_MEAS_CMD_REL,
    LPP_LRRC_LCS_MEAS_CMD_SETUP,
    LPP_LRRC_LCS_MEAS_CMD_BUTT
};
typedef VOS_UINT8   LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LRRC_LPP_LCS_MEAS_RESULT_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC回复LPP测量结果类型
*****************************************************************************/
enum LRRC_LPP_LCS_MEAS_RESULT_ENUM
{
    LRRC_LPP_LCS_MEAS_RESULT_SUCC,
    LRRC_LPP_LCS_MEAS_IDLE_STATUS_ERROR,                                        /* RRC处于IDLE态流程 */
    LRRC_LPP_LCS_MEAS_CONN_REL_STATUS_ERROR,                                    /* RRC处于连接态释放流程 */
    LRRC_LPP_LCS_MEAS_PHY_FAIL_STATUS_ERROR,                                    /* RRC配置PHY失败 */
    LRRC_LPP_LCS_MEAS_PARAM_INVALID_ERROR,                                      /* 参数不合法，比如EARFCN越界 */
    LRRC_LPP_LCS_MEAS_RESULT_OTHER_CAUSE,
    LRRC_LPP_LCS_MEAS_RESULT_BUTT
};
typedef VOS_UINT8   LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : PRS的带宽
*****************************************************************************/
enum LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
{
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N6,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N15,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N25,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N50,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N75,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N100,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : PRS的带宽
*****************************************************************************/
enum LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM
{
    LPP_LRRC_OTDOA_NUMDL_FRAMES_1                   = 1,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_2                   = 2,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_4                   = 4,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_6                   = 6,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : PRS的带宽
*****************************************************************************/
enum LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM
{
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO2,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO4,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO8,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO16,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_ANT_PORT_CFG_ENMUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : CRI的PORT
*****************************************************************************/
enum LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM
{
    LPP_LRRC_OTDOA_ANT_PORT_1_OR_2,
    LPP_LRRC_OTDOA_ANT_PORT_4,

    LPP_LRRC_OTDOA_ANT_PORT_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_CP_TYPE_ENMUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : OTDOA assistance info中的天线数据
*****************************************************************************/
enum LPP_LRRC_OTDOA_CP_TYPE_ENUM
{
    LPP_LRRC_OTDOA_CP_TYPE_NORMAL,

    LPP_LRRC_OTDOA_CP_TYPE_EXTENDED,

    LPP_LRRC_OTDOA_CP_TYPE_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8;

/*********************************************************
 枚举名    : LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
**********************************************************/
enum LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM
{
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1 = 0,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_2,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_4,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_8,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_10,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_20,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_32,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_64,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_BUTT
};
typedef VOS_UINT16 LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16
*****************************************************************************/
enum LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM
{
    LRRC_LPP_OTDOA_MEAS_NO_ERROR,
    LRRC_LPP_OTDOA_TARGET_DEVICE_UNDEFINED,
    LRRC_LPP_OTDOA_ASSISTANCE_DATA_MISSING,
    LRRC_LPP_OTDOA_UNABLE_TO_MEASURE_REF_CELL,
    LRRC_LPP_OTDOA_UNABLE_TO_MEASURE_ANY_NEIGHBOUR_CELL,
    LRRC_LPP_OTDOA_ATTEMPTED_BUT_UNABLE_TO_MEASURE_SOME_NEIGHBOUR_CELLS,
    LRRC_LPP_OTDOA_CONFIG_PHY_FAIL,
    LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_BUFF
};
typedef VOS_UINT16 LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16;

/*****************************************************************************
  5 Struct
*****************************************************************************/

/*****************************************************************************
 结构名称   : LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC上报LCS业务UE的能力
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    /* 0:代表不支持，1:代表支持*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucUeRxTxTimeDiffMeasFlag;

    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaUeAssistFlag;

    /* 0:代表不支持，1:代表支持 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucInterFreqRSTDMeasFlag;

    /* 0:代表不支持，1:代表支持 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAddOtdoaNeighbourCellInfoListFlag;

    /*
    usBandNum 取值范围[1,256]
    ulBandInd,每个BIT，1:代表支持，0代表不支持，ulBandInd[0]中第一个BIT代表BAND1,依次类推;
    */

    VOS_UINT32                                      ulBandNum;
    VOS_UINT32                                      aulBandInd[LRRC_LPP_MAX_BAND_IND_ARRAY_NUM];

}LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_LOCATION_COORDINATES_DATA_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LocationCoordinatesData数据信息
*****************************************************************************/
typedef struct
{
    LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM_UINT8   enLocationCoordinatesType;
    VOS_UINT16                                      usLocationCoordinatesDataLen;
    VOS_UINT8                                       ucReserved;
    VOS_UINT8                                       aucLocationCoordinatesData[LPP_LRRC_MAX_LOCATION_COORDINATES_DATA_LEN];
}LPP_LRRC_LOCATION_COORDINATES_DATA_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_GPS_DATA_INFO_REQ_STRU
 协议表格   :
 ASN.1 描述 : 36.331协议LocationInfo-r10
 结构说明   : LPP下发LocationCoordinatesData数据给LRRC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/
    /*

    0: 删除数据，RRC清除本地数据
    1: 代表有新数据，覆盖本地数据

    */

    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucGnssDataFlag;

    /* 0:代表没有数据，1:有数据*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucHorizontalVelocityFlag;

    /* 0:代表没有数据，1:有数据*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucGnssTodMsecFlag;

    /* 0:代表没有数据，1:有数据*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucLocationDataFlag;

    /*
    GPS各个数据的长度，单位字节，均是编码后的数据长度
    ellipsoid-Point-r10                                       6
    ellipsoidPointWithAltitude-r10                            8
    ellipsoidPointWithUncertaintyCircle-r11                   7
    ellipsoidPointWithUncertaintyEllipse-r11                  10
    ellipsoidPointWithAltitudeAndUncertaintyEllipsoid-r11     13
    ellipsoidArc-r11                                          12
    polygon-r11                                               90

    horizontalVelocity-r10                                    3
    gnss-TOD-msec-r10                                         3

    */

    VOS_UINT8                                       aucHorizontalVelocityData[LPP_LRRC_MAX_CHORIZONTAL_VELOCITY_DATA_LEN];
    VOS_UINT8                                       aucGnssTodMsecData[LPP_LRRC_MAX_GNSS_TOD_MSEC_DATA_LEN];
    VOS_UINT8                                       aucReserved[2];

    LPP_LRRC_LOCATION_COORDINATES_DATA_STRU         stLocationCoordinatesData;
}LPP_LRRC_GNSS_DATA_INFO_IND_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_ECELL_ID_MEAS_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LPP下发LRRC启动或者停止ECELL ID测量请求
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8                ucLcsMeasCmd;

    /* 0:代表不支持，1:代表支持*/
    VOS_UINT8                                       ucRxTxTimeDiffMeasFlag;
    VOS_UINT8                                       aucReserved[2];
}LPP_LRRC_ECID_MEAS_REQ_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_ECID_MEAS_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC回复LPP回复的确认消息
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8             ucResult;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LPP_ECID_MEAS_CNF_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : GLOBAL ID信息
*****************************************************************************/
typedef struct
{
    /* PLMN ID与空口保持一致 */
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucReserved;

    /* 系统消息里的CELL ID 信息*/
    VOS_UINT32                          ulCellIdentity;
}LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_ECID_MEAS_RESULT_STRU
 协议表格   :
 ASN.1 描述 : 36355中MeasuredResultsElement IE
 结构说明   : LRRC上报ECID测量每个小区具体的信息
*****************************************************************************/
typedef struct
{

    /* 0:代表UeRxTxTimeDiff数据无效，1:代表UeRxTxTimeDiff数据有效 ,SFN和UeRxTxTimeDiff同时有效，仅仅主小区可以有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucUeRxTxTimeDiffMeasFlag;

    /* 0:代表CellGlobalId数据无效，1:代表CellGlobalId数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 取值[0,97] */
    VOS_UINT8                                       ucRsrp;
    /* 取值[0,34] */
    VOS_UINT8                                       ucRsrq;

    /* 整体取值[0,262143],其中[65536,262143]为扩展数据 */
    VOS_UINT32                                      ulArfcn;

    /* 取值[0,503] */
    VOS_UINT16                                      usPhyCellId;

    VOS_UINT16                                      usSfn;
    /* 取值[0,4095] */
    VOS_UINT16                                      usUeRxTxTimeDiff;

    VOS_UINT16                                      usReserved;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stGlobalIdInfo;
}LRRC_LPP_ECID_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC上报ECELL ID数据信息列表
*****************************************************************************/
typedef struct
{
    /* 取值[1,33] */
    VOS_UINT32                                      ulCellNum;
    LRRC_LPP_ECID_MEAS_RESULT_STRU                  astLrrcLppEcidMeasResult[LRRC_LPP_MAX_ECID_MEAS_RESULT_NUM];
}LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_ECID_MEAS_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LRRC上报ECELL ID数据信息
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU             stLrrcLppEcidMeasResultList;
}LRRC_LPP_ECID_MEAS_IND_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_PRS_INFO_STRU
 协议表格   :
 ASN.1 描述 : 36355 PRS-Info
 结构说明   : PRS信息
*****************************************************************************/
typedef struct
{
    /* 0:代表PRS_MUTING_INFO数据无效，1:代表PRS_MUTING_INFO数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsMutingInfoFlag;

    LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8         ucPrsBandWidth;
    LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8          ucNumdlFrames;

    VOS_UINT8                                       ucResvered1;

    /* 取值 (0,4095)*/
    VOS_UINT16                                      usPrsConfigurationIndex;

    VOS_UINT8                                       ucResvered2;

    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8  ucPrsMutingInfoType;

    VOS_UINT16                                      usPrsMutingInfo;
    VOS_UINT8                                       aucResvered3[2];

}LPP_LRRC_PRS_INFO_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU
 协议表格   :
 ASN.1 描述 : 36355 OTDOA-ReferenceCellInfo
 结构说明   : OTDOA REFERENCE CELL INFO
*****************************************************************************/
typedef struct
{
    /* 0:代表CellGlobalId数据无效，1:代表CellGlobalId数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:PRS INFO 无效，1: PRS INFO 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsInfoFlag;

    /* 0:ucAntennaPortConfig 无效，1: ucAntennaPortConfig 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAntennaPortConfigFlag;

    /* 如果空口没有配置，在下发物理层时，由LRRC填写成与主小区一致, */
    /*
    The field is mandatory present if the antenna port configuration of the OTDOA assistance data reference cell is not the same as the antenna port configuration of the target devices's current primary cell.
    */
    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8          ucAntennaPortConfig;

    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8               ucCpLen;

    VOS_UINT8                                       aucReserved[1];

    /* 取值[0,503] */
    VOS_UINT16                                      usPhyCellId;

    VOS_UINT32                                      ulEarfcn;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LPP_LRRC_PRS_INFO_STRU                          stPrsInfo;

}LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU
 协议表格   :
 ASN.1 描述 : 36355 OTDOA-NeighbourCellInfoElement
 结构说明   : OTDOA 邻区信息
*****************************************************************************/
typedef struct
{
    /* 0:代表CellGlobalId数据无效，1:代表CellGlobalId数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:PRS INFO 无效，1: PRS INFO 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsInfoFlag;

    /* 0:ucAntennaPortConfig 无效，1: ucAntennaPortConfig 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAntennaPortConfigFlag;

    /* 0:SlotNumberOffset 无效，1: SlotNumberOffset 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucSlotNumberOffsetFlag;

    /* 0:prs-SubframeOffset 无效，1: prs-SubframeOffset 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsSubFramOffsettFlag;


    /* The field is mandatory present if the antenna port configuration is not the same as for the assistance data reference cell; otherwise it is not present. */
    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8          ucAntennaPortConfig;


    /* The field is mandatory present if the cyclic prefix length is not the same as for the assistance data reference cell; otherwise it is not present. */
    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8               ucCpLen;

    /* 取值[0,19] */
    VOS_UINT8                                       ucSlotNumberOffset;

    /* 取值[0,503] */
    VOS_UINT16                                      usPhyCellId;

    /* 取值[0,1279] */
    VOS_UINT16                                      usPrsSubframeOffset;

    /* 取值[0,16383] */
    VOS_UINT16                                      usExpectedRSTD;

    /* 取值[0,1023] */
    VOS_UINT16                                      usExpectedRSTDUncertainty;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    /* The field is mandatory present if the PRS configuration is not the same as for the assistance data reference cell; otherwise it is not present. */
    LPP_LRRC_PRS_INFO_STRU                          stPrsInfo;

}LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 每个邻区频点的小区信息列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulEarfcn;
    VOS_UINT32                                      ulCellNum;
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU         stOtdoaNeighbourCellInfoList[LPP_LRRC_MAX_OTDOA_NEIGHBOUR_SINGLE_FREQ_CELL_NUM];
}LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU
 协议表格   :
 ASN.1 描述 : 36355 OTDOA-NeighbourCellInfoList
 结构说明   : OTDOA NEIGHBOUR CELL INFO
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulFreqInfoNum;

    LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU         stOtdoaNeighbourFreqInfoList[LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM];
}LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_MEAS_ASSISTANCE_DATA_STRU
 协议表格   :
 ASN.1 描述 : 36355  OTDOA-ProvideAssistanceData
 结构说明   : OTDOA 辅助数据
*****************************************************************************/
typedef struct
{
    /* 0:otdoa ReferenceCellInfo 无效，1: otdoa ReferenceCellInfo 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaReferenceCellInfoFlag;

    /* 0:otdoa NeighbourCellInfo 无效，1: otdoa NeighbourCellInfo 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaNeighbourCellInfoFlag;

    VOS_UINT8                                       aucReserved[2];

    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU         stOtdoaReferenceCellInfo;

    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU    stOtdoaNeighbourCellInfo;
}LPP_LRRC_OTDOA_MEAS_ASSISTANCE_DATA_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_MEAS_REQ_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LPP下发LRRC启动或者停止OTDOA测量请求
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8                ucLcsMeasCmd;

    /* 0:OtdoaMeasAssistanceData  无效，1: OtdoaMeasAssistanceData 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaMeasAssistanceDataFlag;
    LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16        enOtdoaRprtInterval;

    LPP_LRRC_OTDOA_MEAS_ASSISTANCE_DATA_STRU        stLppLrrcOtdoaMeasAssistanceData;
}LPP_LRRC_OTDOA_MEAS_REQ_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_MEAS_CNF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LPP下发LRRC启动或者停止OTDOA测量请求
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/
    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8             ucResult;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LPP_OTDOA_MEAS_CNF_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_OTDOA_MEAS_QUALITY_STRU
 协议表格   :
 ASN.1 描述 : 36355 OTDOA-MeasQuality
 结构说明   : OTDOA MEAS QUALITY信息
*****************************************************************************/
typedef struct
{

    /* 0:代表ErrorNumSample数据无效，1:代表ErrorNumSample数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucErrorNumSampleFlag;

    /* 取值[0,3]*/
    VOS_UINT8                                       ucErrorResolution;

    /* 取值[0,31]*/
    VOS_UINT8                                       ucErrorValue;

    /* 取值[0,7]*/
    VOS_UINT8                                       ucErrorNumSample;

}LRRC_LPP_OTDOA_MEAS_QUALITY_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_STRU
 协议表格   :
 ASN.1 描述 : 36331 NeighbourMeasurementElement
 结构说明   : OTDOA邻区测量信息
*****************************************************************************/
typedef struct
{

    /* 0:代表CellGlobalId数据无效，1:代表CellGlobalId数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    VOS_UINT8                                       aucReserved[3];

    /* 取值[0,503] */
    VOS_UINT16                                      usPhyCellIdNeighbour;

    /* 取值[0,12711] */
    VOS_UINT16                                      usRstd;

    VOS_UINT32                                      ulEarfcn;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU                stNeighboureMeasQuality;

}LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_STRU;

/*****************************************************************************
 结构名称   : LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU
 协议表格   :
 ASN.1 描述 : 36355 NeighbourMeasurementList
 结构说明   : OTDOA上报的邻区的测量信息
*****************************************************************************/
typedef struct
{

    VOS_UINT32                                      ulCellNum;
    LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_STRU              stNeighbourMeasurement[LRRC_LPP_MAX_OTDOA_NEIGHBOUR_ALL_FREQ_CELL_NUM];
}LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU;

/*****************************************************************************
 结构名称   : LPP_LRRC_OTDOA_MEAS_IND_STRU
 协议表格   :
 ASN.1 描述 : 36355 OTDOA-SignalMeasurementInformation
 结构说明   : LRRC上报OTDOA结果
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16 usError;

    /* 0:代表CellGlobalId数据无效，1:代表CellGlobalId数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:代表OTDOA-MeasQuality数据无效，1:代表OTDOA-MeasQuality数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaMeasqualityFlag;

    VOS_UINT16                                      usSfn;

    /* 取值[0,503] */
    VOS_UINT16                                      usPhyCellIdRef;

    VOS_UINT32                                      ulEarfcn;


    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU                stReferenceMeasQuality;

    LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU         stNeighbourMeasurementList;

}LRRC_LPP_OTDOA_MEAS_IND_STRU;

/*****************************************************************************
 结构名    : LppLRrcInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于
*****************************************************************************/
typedef struct
{
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgID;                    /*_H2ASN_MsgChoice_Export LPP_LRRC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                                       aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LPP_LRRC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}LPP_LRRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LPP_LRRC_MSG_DATA                               stMsgData;
}LppLRrcInterface_MSG;


/*****************************************************************************
  6 OTHERS
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

