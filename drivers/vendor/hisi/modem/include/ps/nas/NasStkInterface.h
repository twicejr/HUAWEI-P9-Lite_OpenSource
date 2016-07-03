
#ifndef __NAS_STK_INTERFACE_H__
#define __NAS_STK_INTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "TafAppMma.h"
#include "TafAppSsa.h"
#include "MnMsgApi.h"
#include "MnClient.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_STK_CALL_DISC_CAUSE_LEN     (3)
#define NAS_STK_CURC_RPT_CFG_MAX_SIZE   (8)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 结构名称: NAS_STK_MSG_ID_ENUM
 结构说明: NAS和STK之间的原语
*****************************************************************************/
enum NAS_STK_MSG_ID_ENUM
{
    /* 从STK_SS_REGISTERSS_REQ到TAF_STK_CS_STATE_IND消息及结构只是从TafOamInterface.h中移出，命名暂未修改 */
    /* STK  -> SSA */
    STK_SS_REGISTERSS_REQ               = 0x02,                                 /* _H2ASN_MsgChoice MN_APP_SS_REGISTER_REQ_STRU */
    STK_SS_ERASESS_REQ                  = 0x03,                                 /* _H2ASN_MsgChoice MN_APP_SS_ERASE_REQ_STRU */
    STK_SS_ACTIVATESS_REQ               = 0x04,                                 /* _H2ASN_MsgChoice MN_APP_SS_ACTIVATE_REQ_STRU */
    STK_SS_DEACTIVATESS_REQ             = 0x05,                                 /* _H2ASN_MsgChoice MN_APP_SS_DEACTIVATE_REQ_STRU */
    STK_SS_INTERROGATESS_REQ            = 0x06,                                 /* _H2ASN_MsgChoice MN_APP_SS_INTERROGATE_REQ_STRU */
    STK_SS_REGPWD_REQ                   = 0x07,                                 /* _H2ASN_MsgChoice MN_APP_SS_REGPWD_REQ_STRU */

    STK_SS_USSD_REQ                     = 0x09,                                 /* _H2ASN_MsgChoice MN_APP_SS_USSD_REQ_STRU */

    /* STK  -> TAF(MSG) */
    STK_MSG_SEND_REQ                    = 0x0a,                                 /* _H2ASN_MsgChoice MN_APP_MSG_SEND_REQ_STRU */

    /* STK  -> TAF(CALL) */
    STK_CALL_START_DTMF_REQ             = 0x0b,                                 /* _H2ASN_MsgChoice MN_APP_CALL_START_DTMF_REQ_STRU */
    STK_CALL_STOP_DTMF_REQ              = 0x0c,                                 /* _H2ASN_MsgChoice MN_APP_CALL_STOP_DTMF_REQ_STRU */

    STK_CALL_CALLORIG_REQ               = 0x0d,                                 /* _H2ASN_MsgChoice MN_APP_CALL_CALLORIG_REQ_STRU */
    STK_CALL_SUPS_CMD_REQ               = 0x0e,                                 /* _H2ASN_MsgChoice MN_APP_CALL_SUPS_REQ_STRU */

    /* TAF -> STK */
    TAF_STK_CMD_CNF                     = 0x10,                                 /* _H2ASN_MsgChoice MN_APP_CMD_CNF_STRU */

    /* TAF(SSA)-> STK */
    TAF_STK_SS_EVENT_IND                = 0x13,                                 /* _H2ASN_MsgChoice MN_APP_SS_EVENT_IND_STRU */

    /* TAF(SMS)-> STK */
    TAF_STK_MSG_EVENT_IND               = 0x14,                                 /* _H2ASN_MsgChoice MN_APP_MSG_EVENT_IND_STRU */

    /* TAF(CALL)-> STK */
    TAF_STK_CS_CALLINFO_EVENT_IND       = 0x15,                                 /* _H2ASN_MsgChoice MN_APP_CS_CALLINFO_MSG_STRU */

    /* TAF-> STK */
    TAF_STK_CURC_RPT_CFG_INFO_IND       = 0x16,                                 /* _H2ASN_MsgChoice TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU */

    /* TAF-> STK */
    TAF_STK_CS_STATE_IND                = 0x17,                                 /* _H2ASN_MsgChoice TAF_STK_CS_SERVICE_IND */

    /*------------------------------------------------------------------
                        NAS --->STK EVENT DOWNLOAD
     *-----------------------------------------------------------------*/

    ID_NAS_STK_MT_CALL_EVENT            = 0x18,                                 /* _H2ASN_MsgChoice NAS_STK_MT_CALL_EVENT_INFO_STRU */
    ID_NAS_STK_CALL_CONNECT_EVENT       = 0x19,                                 /* _H2ASN_MsgChoice NAS_STK_CALL_CONNECT_EVENT_STRU */
    ID_NAS_STK_CALL_DISC_EVENT          = 0x1a,                                 /* _H2ASN_MsgChoice NAS_STK_CALL_DISC_EVENT_INFO_STRU */
    ID_NAS_STK_LOC_STATUS_EVENT         = 0x1b,                                 /* _H2ASN_MsgChoice NAS_STK_LOC_STATUS_EVENT_STRU */
    ID_NAS_STK_NET_SRCH_MODE_CHG_EVENT  = 0x1c,                                 /* _H2ASN_MsgChoice NAS_STK_SRCHMODE_CHG_EVENT_STRU */
    ID_NAS_STK_NETWORK_REJECTION_EVENT  = 0x1d,                                 /* _H2ASN_MsgChoice NAS_STK_NETWORK_REJECTION_EVENT_STRU*/

    ID_NAS_STK_PS_CALLINFO_EVENT        = 0x1e,                                 /* _H2ASN_MsgChoice NAS_STK_PS_CALLINFO_EVENT_STRU */

    /*------------------------------------------------------------------
                        STK本地状态维护消息
     *-----------------------------------------------------------------*/
    ID_NAS_STK_LOCATION_INFO_IND         = 0x100,                               /* _H2ASN_MsgChoice NAS_STK_LOCATION_INFO_IND_STRU */
    ID_MMA_STK_1X_SERVICE_INFO_IND       = 0x101,                               /* _H2ASN_MsgChoice MMA_STK_SERVICE_INFO_IND_STRU */
    ID_NAS_STK_BUTT                      = 0xffffffff
};
typedef VOS_UINT32 NAS_STK_MSG_ID_ENUM_UINT32;


enum NAS_STK_UTRAN_MODE_ENUM
{
    NAS_STK_UTRAN_MODE_FDD,                                               /* UTRAN模式为WCDMA */
    NAS_STK_UTRAN_MODE_TDD,                                               /* UTRAN模式为TDSCDMA */
    NAS_STK_UTRAN_MODE_BUTT
};
typedef VOS_UINT8 NAS_STK_UTRAN_MODE_ENUM_UINT8;


enum NAS_STK_SERVICE_STATUS_ENUM
{
    NAS_STK_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* 正常服务 */
    NAS_STK_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* 限制服务 */
    NAS_STK_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* 有限制区域服务 */
    NAS_STK_SERVICE_STATUS_NO_IMSI                  = 3,                        /* 无imsi */
    NAS_STK_SERVICE_STATUS_NO_SERVICE               = 4,                        /* 无服务 */
    NAS_STK_SERVICE_STATUS_DEEP_SLEEP               = 6,
    NAS_STK_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_STK_SERVICE_STATUS_ENUM_UINT8;


/*****************************************************************************
 结构名称: NAS_STK_NETWORK_REJECT_TYPE_ENUM
 结构说明: 通知STK发出的Reject类型
*****************************************************************************/
enum NAS_STK_NETWORK_REJECT_TYPE_ENUM
{
    NAS_STK_ATTACH_REJECT,
    NAS_STK_RAU_REJECT,
    NAS_STK_LAU_REJECT,
    NAS_STK_TAU_REJECT,
    NAS_STK_NETWORK_REJECT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_STK_NETWORK_REJECT_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称: NAS_STK_UPDATE_TYPE_ENUM
 结构说明: 通知STK的Update Type
    参考协议31111 8.92  Update/Attach Type，与STK定义的映射关系:
    NAS_STK_LUT_NORMAL_LU                                        '00' = "Normal Location Updating" in the case of a LOCATION UPDATING REQUEST message;
    NAS_STK_LUT_PERIODIC_UPDATING                                '01' = "Periodic Updating" in the case of a LOCATION UPDATING REQUEST message;
    NAS_STK_LUT_IMSI_ATTACH                                      '02' = "IMSI Attach" in the case of a LOCATION UPDATING REQUEST message;
    NAS_STK_ATTACH_NORMAL & PS_STK_ATTACH_NORMAL_CS_TRANS        '03' = "GPRS Attach" in the case of a GPRS ATTACH REQUEST message;
    NAS_STK_ATTACH_COMBINED & PS_STK_ATTACH_WHILE_IMSI_ATTACHED  '04' = "Combined GPRS/IMSI Attach" in the case of a GPRS ATTACH REQUEST message;
    NAS_STK_RAU_NORMAL & PS_STK_RAU_NORMAL_CS_TRANS & PS_STK_RAU_NORMAL_CS_UPDATED
                                                                '05' = "RA Updating" in the case of a ROUTING AREA UPDATE REQUEST message;
    NAS_STK_RAU_COMBINED                                         '06' = "Combined RA/LA Updating" in the case of a ROUTING AREA UPDATE REQUEST message;
    NAS_STK_RAU_WITH_IMSI_ATTACH                                 '07' = "Combined RA/LA Updating with IMSI Attach" in the case of a ROUTING AREA UPDATE REQUEST message;
    NAS_STK_RAU_PERIODIC_UPDATING                                '08' = "Periodic Updating" in the case of a ROUTING AREA UPDATE REQUEST message
                '09' = "EPS Attach" in the case of an EMM ATTACH REQUEST message
                '0A' = "Combined EPS/IMSI Attach" in the case of an EMM ATTACH REQUEST message
                '0B' = "TA updating " in the case of an EMM TRACKING AREA UPDATE REQUEST message
                '0C' = "Combined TA/LA updating" in the case of an EMM TRACKING AREA UPDATE REQUEST message
                '0D' = "Combined TA/LA updating with IMSI attach" in the case of an EMM TRACKING AREA UPDATE REQUEST message
                '0E' = "Periodic updating" in the case of an EMM TRACKING AREA UPDATE REQUEST message


*****************************************************************************/
enum NAS_STK_UPDATE_TYPE_ENUM
{
    NAS_STK_LUT_NORMAL_LU                   = 0,
    NAS_STK_LUT_PERIODIC_UPDATING           = 1,
    NAS_STK_LUT_IMSI_ATTACH                 = 2,

    NAS_STK_ATTACH_COMBINED                 = 0x10,                             /* combined attach                          */
    NAS_STK_ATTACH_WHILE_IMSI_ATTACHED      = 0x11,                             /* GPRS attach while IMSI attached          */
    NAS_STK_ATTACH_NORMAL                   = 0x12,                             /* normal attach                            */
    NAS_STK_ATTACH_NORMAL_CS_TRANS          = 0x13,                             /* CS通信中的normal attach(A+I)             */

    NAS_STK_RAU_COMBINED                    = 0x20,                             /* combined RAU                             */
    NAS_STK_RAU_WITH_IMSI_ATTACH            = 0x21,                             /* combined RAU with IMSI attach            */
    NAS_STK_RAU_NORMAL                      = 0x22,                             /* normal RAU                               */
    NAS_STK_RAU_NORMAL_CS_TRANS             = 0x23,                             /* CS通信中的normal RAU(A+I)                */
    NAS_STK_RAU_NORMAL_CS_UPDATED           = 0x24,
    NAS_STK_RAU_PERIODIC_UPDATING           = 0x25,

    NAS_STK_UPDATE_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 NAS_STK_UPDATE_TYPE_ENUM_UINT8;



enum TAF_CS_SERVICE_ENUM
{
    TAF_CS_OFF              = 0,
    TAF_CS_ON,
    TAF_CS_SERVICE_BUTT
};
typedef VOS_UINT32 TAF_CS_SERVICE_ENUM_UINT32;





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


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}NAS_STK_EVENT_MSG_HEADER_STRU;



typedef struct
{
    TAF_PLMN_ID_STRU                    stCurPlmnID;
    VOS_UINT16                          usLac;
    VOS_UINT8                           aucRsv[2];
}NAS_STK_LAC_INFO_STRU;


typedef struct
{
    TAF_PLMN_ID_STRU                    stCurPlmnID;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucRsv;
}NAS_STK_RAU_INFO_STRU;


typedef struct
{
    TAF_PLMN_ID_STRU                    stCurPlmnID;
    VOS_UINT16                          usTac;
    VOS_UINT8                           aucRsv[2];
}NAS_STK_TAU_INFO_STRU;


typedef struct
{
    TAF_MMA_RAT_TYPE_ENUM_UINT8              enRat;
    NAS_STK_UPDATE_TYPE_ENUM_UINT8           enUpdateAttachType;
    VOS_UINT8                                ucCauseCode;

    NAS_STK_NETWORK_REJECT_TYPE_ENUM_UINT8    enRejType;
    union
    {
        NAS_STK_LAC_INFO_STRU            stLacInfo;
        NAS_STK_RAU_INFO_STRU            stRauInfo;
        NAS_STK_TAU_INFO_STRU            stTauInfo;
    }uRejectInfo;
}NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgName;
    NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU               stNetworkRejectionEvent;
}NAS_STK_NETWORK_REJECTION_EVENT_STRU;



/*****************************************************************************
 结构名    : NAS_STK_MT_CALL_EVENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CALL发给STK模块的MT CALL EVENT消息信息字段结构
             stMtCallEvent MT CALL EVENT信息字段
             参考协议10223 7.5.1.2 Structure of ENVELOPE (EVENT DOWNLOAD - MT call)
                     11.14 11.1.2  Structure of ENVELOPE (EVENT DOWNLOAD - MT call)
             ucTi                           Transaction identifier
             stCallerNumber                 Address，其中ucNumLen为0表示没有主叫号码
             stSubCallNumber                Subaddress，其中IsExist为0表示没有主叫号码子地址
                                                            LastOctOffset表示主叫号码子地址长度
                                                            Octet3主叫号码子地址的第一个字节
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTi;
    VOS_UINT8                           aucReserved1[3];
    MN_CALL_BCD_NUM_STRU                stCallerNumber;
    MN_CALL_SUBADDR_STRU                stCallerSubNumber;
}NAS_STK_MT_CALL_EVENT_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_STK_MT_CALL_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CALL发给STK模块的MT CALL EVENT消息结构
             stMtCallEvent MT CALL EVENT信息字段
             参考协议10223 7.5.1.2 Structure of ENVELOPE (EVENT DOWNLOAD - MT call)
                      11.14 11.1.2 Structure of ENVELOPE (EVENT DOWNLOAD - MT call)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    NAS_STK_MT_CALL_EVENT_INFO_STRU     stMtCallEventInfo;
} NAS_STK_MT_CALL_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_STK_CALL_CONNECT_EVENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CALL发给STK模块的CALL CONNECT EVENT检查请求消息信息字段结构
             MN_CALL_DIR_ENUM_U8 enCallDir 指示进入通话的呼叫是否UE发起的呼叫
             stCallConnectEvent  CALL CONNECT EVENT信息字段
             参考协议10223 7.5.2.2 Structure of ENVELOPE (EVENT DOWNLOAD - call connected)
                     11.14 11.2.2  Structure of ENVELOPE (EVENT DOWNLOAD - call connected)
             ucTi                           Transaction identifier
             enCallDir                      呼叫方向
                                            in the case of connecting at the near end (an MT call), the terminal
                                            shall set the device identities to:
                                            - source: terminal;
                                            - destination: UICC.
                                            in the case of connecting at the far end (an MO call), the terminal
                                            shall set the device identities to:
                                            - source: network;
                                            - destination: UICC.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTi;
    MN_CALL_DIR_ENUM_U8                 enCallDir;
    VOS_UINT8                           aucRsv[2];
}NAS_STK_CALL_CONNECT_EVENT_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_STK_CALL_CONNECT_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CALL发给STK模块的CALL CONNECT EVENT检查请求消息结构
             stCallConnectEvent  CALL CONNECT EVENT信息字段
             参考协议10223 7.5.2.2 Structure of ENVELOPE (EVENT DOWNLOAD - call connected)
                     11.14 11.2.2  Structure of ENVELOPE (EVENT DOWNLOAD - call connected)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;
    NAS_STK_CALL_CONNECT_EVENT_INFO_STRU stCallConnectEventInfo;
} NAS_STK_CALL_CONNECT_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_STK_CALL_DISC_CAUSE_STRU
 协议表格  : CALL发给STK模块的CALL CONNECT EVENT消息释放原因值结构
 ASN.1描述 :
 结构说明  :
             ucExistFlg         指示是否存在原因值字段，因为要支持字段存在但没有原因值的情况，
                                ucExistFlg为VOS_TRUE，ucLen为0表示aucCause无效
             ucLen              指示原因值字段长度
             参考协议10223 7.5.3 Call disconnected event
                     11.14 11.3  Call disconnected event
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucExistFlg;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucCause[NAS_STK_CALL_DISC_CAUSE_LEN];
    VOS_UINT8                           aucReserved1[3];
}NAS_STK_CALL_DISC_CAUSE_STRU;

/*****************************************************************************
 结构名    : NAS_STK_CALL_DISC_EVENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CALL发给STK模块的CALL CONNECT EVENT消息信息字段结构
             ucLocalDiscFlg      指示是否本地释放
             stCallDiscEvent     CALL DISCONNECTED EVENT信息字段
             参考协议10223 7.5.3 Call disconnected event
                     11.14 11.3  Call disconnected event
            ucTi                           Transaction identifier
            ucNearEndFlg                   本端释放标志，
                                            in the case of "near end" disconnection, the terminal shall set the
                                            device identities to:
                                            - source: terminal;
                                            - destination: UICC.
                                            in the case of connecting at the far end (an MO call), the terminal
                                            shall set the device identities to:
                                            - source: network;
                                            - destination: UICC.
            stCause                        释放原因值
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucLocalDiscFlg;
    VOS_UINT8                           aucReserved1[2];
    NAS_STK_CALL_DISC_CAUSE_STRU        stCause;
}NAS_STK_CALL_DISC_EVENT_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_STK_CALL_DISC_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CALL发给STK模块的CALL CONNECT EVENT消息结构
             ucLocalDiscFlg      指示是否本地释放
             stCallDiscEvent     CALL DISCONNECTED EVENT信息字段
             参考协议10223 7.5.3 Call disconnected event
                     11.14 11.3  Call disconnected event
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;
    NAS_STK_CALL_DISC_EVENT_INFO_STRU    stCallDiscEventInfo;
} NAS_STK_CALL_DISC_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_STK_LOC_STATUS_EVENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CALL发给STK模块的LOCATION STATUS EVENT消息信息字段的结构
             ucCsServStatus           CS域服务状态
                    0           正常服务
                    1           限制服务
                    2           有限制区域服务 对应STK的限制服务
                    3           无imsi   对应STK的无服务
                    4           无服务
                    6           SLEEP    对应STK的无服务
             enRat                    接入技术类型      参考协议10223 8.61 Access technology
                    0           TAF_MMA_RAT_GSM              '00' = GSM
                    1           TAF_MMA_RAT_WCDMA            '03' = UTRAN
                    2           TAF_MMA_RAT_LTE              '08' = E-UTRAN
             stPlmn                   UE驻留的PLMN
             usLac                    UE驻留的位置区
             ulCellId                 UE驻留的小区，32BIT转数组的字节序规则，aucCellId[3]和aucCellId[2]仅在enRat 不为TAF_PH_RAT_GSM时有效
                   BIT 0 - 7            8-15            16 - 23         24 - 31
                      aucCellId[1]    aucCellId[0]    aucCellId[3]    aucCellId[2]

             参考协议
             10223 7.5.4.2 Structure of ENVELOPE (EVENT DOWNLOAD - Location status)
             11.14 11.4.2  Structure of ENVELOPE (EVENT DOWNLOAD - Location status)
*****************************************************************************/
typedef struct
{
    TAF_PLMN_ID_STRU                  stPlmn;
    TAF_MMA_RAT_TYPE_ENUM_UINT8       enRat;
    NAS_STK_SERVICE_STATUS_ENUM_UINT8 enServiceStatus;
    VOS_UINT16                        usLac;
    VOS_UINT32                        ulCellId;
}NAS_STK_LOC_STATUS_EVENT_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_STK_LOC_STATUS_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LOCATION STATUS EVENT消息结构
             stLocStatusEvent LOCATION STATUS EVENT消息信息字段的结构
             参考协议 10223 7.5.4 Location status event
                      11.14 11.4  Location status event
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;
    NAS_STK_LOC_STATUS_EVENT_INFO_STRU   stLocStatusEvent;
} NAS_STK_LOC_STATUS_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_STK_ACCTECH_CHG_EVENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Access Technology Change Event消息结构
             stAccTechChgEvent Access Technology Change Event消息信息字段的结构
             参考协议 10223 7.5.12 Access Technology Change Event
                      11.14 不涉及
            ucExistFlg      是否存在有效的接入技术
            enRat           UE驻留网络的接入技术
*****************************************************************************/
typedef struct
{
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    VOS_UINT8                           aucRsv[3];
}NAS_STK_ACCTECH_CHG_EVENT_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_STK_SRCHMODE_CHG_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Access Technology Change Event消息结构
             stNetSrchModeChgEvent Network Search Mode Change Event消息信息字段的结构
             参考协议 10223 7.5.15 Network Search Mode Change Event
                      11.14 不涉及
             ucSrchMode            UE配置的搜网模式
                                   0   automatic selection mode
                                   1   manual selection mode
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSrchMode; /* typedef TAF_UINT8 TAF_PH_PLMN_SEL_MODE;   */
}NAS_STK_SRCHMODE_CHG_EVENT_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_STK_SRCHMODE_CHG_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Access Technology Change Event消息结构
             stNetSrchModeChgEvent Network Search Mode Change Event消息信息字段的结构
             参考协议 10223 7.5.15 Network Search Mode Change Event
                      11.14 不涉及
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;
    NAS_STK_SRCHMODE_CHG_EVENT_INFO_STRU stSrchModeChgEvent;
} NAS_STK_SRCHMODE_CHG_EVENT_STRU;


typedef struct
{
    NAS_STK_SERVICE_STATUS_ENUM_UINT8    enCsServiceStatus;
    VOS_UINT8                            aucReserved1[3];
}NAS_STK_SERVICE_STATUS_INFO_STRU;


typedef struct
{
    TAF_PLMN_ID_STRU                    stPlmn;
    VOS_UINT16                          usLac;
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
    NAS_STK_UTRAN_MODE_ENUM_UINT8       enUtranMode;
    VOS_UINT32                          ulCellId;
}NAS_STK_SYS_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /* 消息头 */        /*_H2ASN_Skip*/
    NAS_STK_SYS_INFO_STRU               stSysInfo;
    NAS_STK_SERVICE_STATUS_INFO_STRU    stServiceStatus;
}NAS_STK_LOCATION_INFO_IND_STRU;

/*****************************************************************************
 结构名    : STK_CALL_ADDR_STRU
 协议表格  : 参考协议102.223 8.1
                     24008   10.5.4.7
 ASN.1描述 : ucLen          数组aucAddr中的有效字节数；
             ucAddrType     地址类型: TON and NPI；
             aucAddr        被叫号码: Dialling number string，一个字节包含2个数字
 结构说明  : STK发给CALL 发起CS域呼叫的请求结构
*****************************************************************************/
#define STK_CALL_ADDR_MAX_LEN                               (40)
typedef struct
{
    VOS_UINT8                           ucAddrType;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucAddr[STK_CALL_ADDR_MAX_LEN];
}STK_CALL_ADDR_STRU;

/*****************************************************************************
 结构名    : STK_CALL_SUBADDR_STRU
 协议表格  : 参考协议102.223 8.3
                     24008   10.5.4.8
 ASN.1描述 : ucLen          数组aucSubAddr中的有效字节数；
             aucSubAddr     被叫子地址: Subaddress
 结构说明  : STK发给CALL 发起CS域呼叫的请求结构
*****************************************************************************/
#define STK_CALL_SUBADDR_MAX_LEN                            (20)
typedef struct
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucSubAddr[STK_CALL_SUBADDR_MAX_LEN];
}STK_CALL_SUBADDR_STRU;

/*****************************************************************************
 结构名    : STK_CALL_BC_STRU
 协议表格  : 参考协议102.223 8.4    Capability configuration parameters
                     24008   10.5.4.5
 ASN.1描述 : ucLen          数组aucBc中的有效字节数；
             aucBc          Capability configuration parameters
 结构说明  : STK发给CALL 发起CS域呼叫的请求结构
*****************************************************************************/
#define STK_CALL_BC_MAX_LEN                                  (14)
typedef struct
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT8                           aucBc[STK_CALL_BC_MAX_LEN];
}STK_CALL_BC_STRU;


/*****************************************************************************
 结构名    : MN_APP_SS_REGISTER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS Register SS业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_REGISTERSS_REQ_STRU          stTafSsRegisterSsReq;
} MN_APP_SS_REGISTER_REQ_STRU;


/*****************************************************************************
 结构名    : MN_APP_SS_REGPWD_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS PWD请求响应消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_GETPWD_RSP_STRU              stTafSsRegPwdRsp;
} MN_APP_SS_REGPWD_RSP_STRU;

/*****************************************************************************
 结构名    : MN_APP_SS_ERASE_REQ_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS Erase SS业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_ERASESS_REQ_STRU             stTafSsEraseSsReq;
} MN_APP_SS_ERASE_REQ_STRU;

/*****************************************************************************
 结构名    : MN_APP_SS_ACTIVATE_REQ_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS ACTIVATE SS业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_ACTIVATESS_REQ_STRU          stTafSsActivateSsReq;
} MN_APP_SS_ACTIVATE_REQ_STRU;

/*****************************************************************************
 结构名    : MN_APP_SS_DEACTIVATE_REQ_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS DEACTIVATE SS业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_DEACTIVATESS_REQ_STRU        stTafSsDeActivateSsReq;
} MN_APP_SS_DEACTIVATE_REQ_STRU;

/*****************************************************************************
 结构名    : MN_APP_SS_INTERROGATE_REQ_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS INTERROGATE SS业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_INTERROGATESS_REQ_STRU       stTafSsInterrogateSsReq;
} MN_APP_SS_INTERROGATE_REQ_STRU;


/*****************************************************************************
 结构名    : MN_APP_SS_REGPWD_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS REG PWD SS业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_REGPWD_REQ_STRU              stTafSsRegPwdReq;
} MN_APP_SS_REGPWD_REQ_STRU;

/*****************************************************************************
 结构名    : MN_APP_SS_USSD_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SS USSD业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_SS_PROCESS_USS_REQ_STRU         stTafSsUssdReq;
} MN_APP_SS_USSD_REQ_STRU;


/*****************************************************************************
 结构名    : MN_APP_SS_REGISTER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给SMS业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    MN_MSG_SEND_PARM_STRU               stMsgSendReq;
} MN_APP_MSG_SEND_REQ_STRU;

/*****************************************************************************
 结构名    : MN_APP_CALL_START_DTMF_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给CALL 开始DTMF业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           callID;
    TAF_CALL_DTMF_PARAM_STRU            stTafStartDtmfPara;
} MN_APP_CALL_START_DTMF_REQ_STRU;


/*****************************************************************************
 结构名    : MN_APP_CALL_STOP_DTMF_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : STK发给CALL 停止DTMF业务
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           callID;
    VOS_UINT8                           aucData[4];
} MN_APP_CALL_STOP_DTMF_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           callID;
    STK_CALL_ADDR_STRU                  stCalledAddr;
    STK_CALL_SUBADDR_STRU               stSubAddr;
    STK_CALL_BC_STRU                    stBc;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           aucReserve[3];
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;                         /* Emergency Catory */
} MN_APP_CALL_CALLORIG_REQ_STRU;

/*****************************************************************************
 结构名    : MN_APP_CALL_SUPS_REQ_STRU
 协议表格  :
 ASN.1描述 : clientId            OAM_CLIENT_ID_STK
             opId                Operation ID, 标识本次操作，TAF会透传会STK模块
             stSupsPara
                enCallSupsCmd    MN_CALL_SUPS_CMD_REL_ALL_CALL   释放所有呼叫；
                                 MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH HOLD所有ACTIVE呼叫，接听等待的呼叫；
                                 MN_CALL_SUPS_CMD_REL_CALL_X 挂断指定呼叫；
                callId           挂断指定呼叫时有效，其他情况填0
                stRedirectNum    enCallSupsCmd为MN_CALL_SUPS_CMD_DEFLECT_CALL时有效
 结构说明  : STK发给CALL 发起CS域呼叫相关补充业务的请求结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    MN_CALL_SUPS_PARAM_STRU             stSupsPara;
} MN_APP_CALL_SUPS_REQ_STRU;

/*****************************************************************************
 结构名    : MN_APP_CMD_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAF发给AT/STK的CMD CNF消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_CMD_CNF_EVENT                    stCmdCnfEvent;
} MN_APP_CMD_CNF_STRU;

/*****************************************************************************
 结构名    : MN_APP_SS_EVENT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAF发给AT/STK的SS事件结构
 enEventType含义待确认
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulEventType;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU  stSsEvent;
} MN_APP_SS_EVENT_IND_STRU;

/*****************************************************************************
 结构名    : MN_APP_MSG_EVENT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAF发给AT/STK的SMS事件结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_MSG_EVENT_ENUM_U32               enEventType;
    MN_MSG_EVENT_INFO_STRU              stEvent;
} MN_APP_MSG_EVENT_IND_STRU;


/*****************************************************************************
 结构名    : MN_APP_CS_CALLINFO_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAF发给AT/STK的CS CALL事件结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    MN_CALL_INFO_STRU                   stCsCallInfo;
} MN_APP_CS_CALLINFO_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           aucCurcRptCfg[NAS_STK_CURC_RPT_CFG_MAX_SIZE];
 }TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgName;
    TAF_CS_SERVICE_ENUM_UINT32                  enCSState;
}TAF_STK_CS_SERVICE_IND;



typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgId;
    MN_CALL_EVENT_ENUM_U32          enEventType;
    VOS_UINT8                       aucEvent[4];
} NAS_CALL_STK_EVT_STRU;




typedef struct
{
    VOS_UINT32                      ulMcc;
    VOS_UINT16                      usImsi11_12;
    VOS_UINT16                      usSid;
    VOS_UINT16                      usNid;
    VOS_UINT16                      usBaseId;
    VOS_INT32                       lBaseLatitude;
    VOS_INT32                       lBaseLongtitude;
}MMA_STK_1X_SYS_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MMA_STK_1X_SYS_INFO_STRU            stSysInfo;
    NAS_STK_SERVICE_STATUS_INFO_STRU    stServiceStatus;
}MMA_STK_SERVICE_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_STK_PS_CALLINFO_EVENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAF发给STK模块的PS CALL INFO EVENT消息结构,
             当存在一个数据业务(包括CDMA和LTE的默认承载)的时候就发送 TRUE
             当所有数据业务都断开的时候发送 FALSE
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_BOOL                            bPsCallExist;
} NAS_STK_PS_CALLINFO_EVENT_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    NAS_STK_MSG_ID_ENUM_UINT32          enMsgId;            /* _H2ASN_MsgChoice_Export NAS_STK_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_STK_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} NAS_STK_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    NAS_STK_INTERFACE_MSG_DATA           stMsgData;
} NasStkInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/




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

#endif

