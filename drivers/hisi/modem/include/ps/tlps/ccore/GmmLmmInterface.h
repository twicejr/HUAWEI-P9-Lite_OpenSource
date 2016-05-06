
#ifndef __GMMLMMINTERFACE_H__
#define __GMMLMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#include "LPSCommon.h"

#include "PsTypeDef.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define LMM_GMM_NAS_TOKEN_LEN           32   /*长度不确认，在协议上没有找到依据*/
#define LMM_GMM_CK_LEN                  16
#define LMM_GMM_IK_LEN                  16

#define LMM_GMM_EMERGENCY_NUM_MAX_LEN            (46)
#define LMM_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS   (16)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    GMM_LMM_MSG_ID_ENUM
{
    /* GMM发给LMM的消息原语 */
    ID_GMM_LMM_RESEL_SECU_INFO_REQ      = 0x01+PS_MSG_ID_GMM_TO_LMM_BASE,       /* _H2ASN_MsgChoice GMM_LMM_RESEL_SECU_INFO_REQ */
    ID_GMM_LMM_HO_SECU_INFO_REQ         = 0x02+PS_MSG_ID_GMM_TO_LMM_BASE,       /* _H2ASN_MsgChoice GMM_LMM_HO_SECU_INFO_REQ  */
    ID_GMM_LMM_INFO_CHANGE_NOTIFY_REQ   = 0x03+PS_MSG_ID_GMM_TO_LMM_BASE,       /* _H2ASN_MsgChoice GMM_LMM_INFO_CHANGE_NOTIFY_REQ */
    ID_GMM_LMM_TIMER_STATE_NOTIFY        = 0x04+PS_MSG_ID_GMM_TO_LMM_BASE,      /* _H2ASN_MsgChoice GMM_LMM_TIMER_STATE_NOTIFY_STRU */

    ID_GMM_LMM_BEGIN_SESSION_NOTIFY    = 0x05+PS_MSG_ID_GMM_TO_LMM_BASE,        /* _H2ASN_MsgChoice GMM_LMM_BEGIN_SESSION_NOTIFY_STRU */
    ID_GMM_LMM_END_SESSION_NOTIFY      = 0x06+PS_MSG_ID_GMM_TO_LMM_BASE,        /* _H2ASN_MsgChoice GMM_LMM_END_SESSION_NOTIFY_STRU */

    /* LMM发送给GMM的消息原语*/
    ID_LMM_GMM_RESEL_SECU_INFO_CNF      = 0x01+PS_MSG_ID_LMM_TO_GMM_BASE,       /* _H2ASN_MsgChoice LMM_GMM_RESEL_SECU_INFO_CNF */
    ID_LMM_GMM_HO_SECU_INFO_CNF         = 0x02+PS_MSG_ID_LMM_TO_GMM_BASE,       /* _H2ASN_MsgChoice LMM_GMM_HO_SECU_INFO_CNF */
    ID_LMM_GMM_INFO_CHANGE_NOTIFY       = 0x03+PS_MSG_ID_LMM_TO_GMM_BASE,       /* _H2ASN_MsgChoice LMM_GMM_INFO_CHANGE_NOTIFY_STRU */

    ID_GMM_LMM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 GMM_LMM_MSG_ID_ENUM_UINT32;



/*****************************************************************************
 枚举名: GMM_LMM_RESULT_ID_ENUM
 协议格式:
 ASN.1描述:
 枚举说明:
*****************************************************************************/
enum    GMM_LMM_RESULT_ID_ENUM
{
    GMM_LMM_SUCC                        = 0x00000000,
    GMM_LMM_FAIL                        ,
    GMM_LMM_ERR_ID_BUTT
};
typedef VOS_UINT32 GMM_LMM_RESULT_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LMM_GMM_SECU_INFO_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum    LMM_GMM_SECU_INFO_RSLT_ENUM
{
    LMM_GMM_SECU_INFO_RSLT_SUCC         = 0,
    LMM_GMM_SECU_INFO_RSLT_FAIL,

    LMM_GMM_SECU_INFO_RSLT_BUTT
};
typedef VOS_UINT32 LMM_GMM_SECU_INFO_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GMM_LMM_GPRS_MM_STATE_ENUM
 结构说明  : GSM下GMM状态
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新增
*****************************************************************************/
enum    GMM_LMM_GPRS_MM_STATE_ENUM
{
    GMM_LMM_GPRS_MM_STATE_IDLE           = 0,           /* G下GMM为idle态 */
    GMM_LMM_GPRS_MM_STATE_STANDBY        = 1,           /* G下GMM为standby态 */
    GMM_LMM_GPRS_MM_STATE_READY          = 2,           /* G下GMM为ready态 */

    GMM_LMM_GPRS_MM_STATE_BUTT
};
typedef VOS_UINT32 GMM_LMM_GPRS_MM_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GMM_LMM_PACKET_MM_STATE_ENUM
 结构说明  : W下GMM状态
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新增
*****************************************************************************/
enum    GMM_LMM_PACKET_MM_STATE_ENUM
{
    GMM_LMM_PACKET_MM_STATE_PMM_DETACH     = 0,           /* W下GMM为detach态 */
    GMM_LMM_PACKET_MM_STATE_PMM_IDLE       = 1,           /* W下GMM为idle态 */
    GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED  = 2,           /* W下GMM为connect态 */

    GMM_LMM_PACKET_MM_STATE_BUTT
};
typedef VOS_UINT32 GMM_LMM_PACKET_MM_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : GMM_LMM_GPRS_SUSPENSION_STATE_ENUM
 结构说明  : GPRS是否挂起状态
 1.日    期   : 2011年10月27日
   作    者   : s46746
   修改内容   : 新增
*****************************************************************************/
enum    GMM_LMM_GPRS_SUSPENSION_STATE_ENUM
{
    GMM_LMM_GPRS_NOT_SUSPENSION             = 0,           /* G下GMM为非挂起态 */
    GMM_LMM_GPRS_SUSPENSION                 = 1,           /* G下GMM为挂起态 */

    GMM_LMM_GPRS_SUSPENSION_BUTT
};
typedef VOS_UINT32 GMM_LMM_GPRS_SUSPENSION_STATE_ENUM_UINT32;
/*****************************************************************************
 枚举名    : GMM_LMM_TIMER_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :定时器的运行情况
*****************************************************************************/
enum    GMM_LMM_TIMER_STATE_ENUM
{
    GMM_LMM_TIMER_STOP         = 0,
    GMM_LMM_TIMER_START,
    GMM_LMM_TIMER_EXP,

    GMM_LMM_TIMER_BUTT
};
typedef VOS_UINT32 GMM_LMM_TIMER_STATE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : LMM_GMM_NW_IMS_VOICE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧支持的IMS VOICE枚举
*****************************************************************************/
enum LMM_GMM_NW_IMS_VOICE_ENUM
{
    LMM_GMM_NW_IMS_VOICE_NOT_SUPPORTED   = 0,
    LMM_GMM_NW_IMS_VOICE_SUPPORTED        = 1,

    LMM_GMM_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT32 LMM_GMM_NW_IMS_VOICE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_GMM_NW_EMC_BS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网侧支持的EMC BEARER SERVICEE枚举
*****************************************************************************/
enum LMM_GMM_NW_EMC_BS_ENUM
{
    LMM_GMM_NW_EMC_BS_NOT_SUPPORTED      = 0,
    LMM_GMM_NW_EMC_BS_SUPPORTED           = 1,

    LMM_GMM_NW_EMC_BS_BUTT
};
typedef VOS_UINT32 LMM_GMM_NW_EMC_BS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_GMM_LTE_CS_CAPBILITY_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE的CS域能力
*****************************************************************************/
enum LMM_GMM_LTE_CS_CAPBILITY_ENUM
{
    LMM_GMM_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    LMM_GMM_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    LMM_GMM_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    LMM_GMM_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT32 LMM_GMM_LTE_CS_CAPBILITY_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
结构名    :GMM_LMM_RESEL_SECU_INFO_REQ_STRU中
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];  /*预留*/
}GMM_LMM_RESEL_SECU_INFO_REQ_STRU;

/*****************************************************************************
结构名    :LMM_GMM_UMTS_SECU_CONTEXT_STRU
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          KSI;
    VOS_UINT8                           aucUmtsCk[LMM_GMM_CK_LEN];
    VOS_UINT8                           aucUmtsIk[LMM_GMM_IK_LEN];
}LMM_GMM_UMTS_SECU_CONTEXT_STRU;

/*****************************************************************************
结构名    :LMM_GMM_RESEL_SECU_INFO_STRU中
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    LMM_GMM_UMTS_SECU_CONTEXT_STRU      stUmtsSecuContext;
    VOS_UINT8                           aucNasToken[LMM_GMM_NAS_TOKEN_LEN];

}LMM_GMM_RESEL_SECU_INFO_STRU;

/*****************************************************************************
结构名    :GMM_LMM_RESEL_SECU_INFO_REQ_STRU中
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSecuInfo   : 1;
    VOS_UINT32                          bitSpare        : 31;

    LMM_GMM_SECU_INFO_RSLT_ENUM_UINT32  enRslt;
    LMM_GMM_RESEL_SECU_INFO_STRU        stReselSecuInfo;
}LMM_GMM_RESEL_SECU_INFO_CNF_STRU;

/*****************************************************************************
结构名    :GMM_LMM_HO_SECU_INFO_REQ_STRU
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];  /*预留*/
}GMM_LMM_HO_SECU_INFO_REQ_STRU;


/*****************************************************************************
 结构名    : GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
        从G模到L模的异系统变换，当G模挂起时，需要给L模发送此消息，设置bitOpGConnState为1，告知G模的连接状态；
        从U模到L模的异系统变换，当U模挂起时，需要给L模发送此消息，设置bitOpUConnState为1，告知U模的连接状态。
        从G模到L模的异系统变换，当G模挂起时，需要给L模发送此消息，通知LMM PS域的状态。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                                              bitOpGprsMmState         : 1;
    VOS_UINT32                                              bitOpPacketMmState       : 1;
    VOS_UINT32                                              bitOpGprsSuspensionState : 1;
    VOS_UINT32                                              bitSpare                 : 29;

    GMM_LMM_GPRS_MM_STATE_ENUM_UINT32                       enGprsMmState;         /* G下GMM连接状态 */
    GMM_LMM_PACKET_MM_STATE_ENUM_UINT32                     enPacketMmState;       /* W下GMM连接状态 */
    GMM_LMM_GPRS_SUSPENSION_STATE_ENUM_UINT32               enGprsSuspensionState; /* GMM是否为被挂起状态 */
} GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU;

/*****************************************************************************
 结构名    : LMM_GMM_EMERGENCY_NUM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucCategory;
    VOS_UINT8                           ucEmcNumLen;    /*紧急呼号码长度，即aucEmcNum的有效长度*/
    VOS_UINT8                           aucEmcNum[LMM_GMM_EMERGENCY_NUM_MAX_LEN];
} LMM_GMM_EMERGENCY_NUM_STRU;

/*****************************************************************************
 结构名    : LMM_GMM_INFO_CHANGE_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;

    VOS_UINT32                              bitOpEmcNumList : 1;
    VOS_UINT32                              bitOpImsVoPS    : 1;
    VOS_UINT32                              bitOpEmcBS      : 1;
    VOS_UINT32                              bitOpLteCsCap   : 1;
    VOS_UINT32                              bitSpare        : 28;

    VOS_UINT8                               ucEmergencyNumAmount;
    VOS_UINT8                               aucReserved[3];
    LMM_GMM_EMERGENCY_NUM_STRU              astEmergencyNumList[LMM_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS];

    LMM_GMM_NW_IMS_VOICE_ENUM_UINT32        enNwImsVoPS;
    LMM_GMM_NW_EMC_BS_ENUM_UINT32           enNwEmcBS;
    LMM_GMM_LTE_CS_CAPBILITY_ENUM_UINT32    enLteCsCap ;
} LMM_GMM_INFO_CHANGE_NOTIFY_STRU;


/*****************************************************************************
结构名    :LMM_GMM_HO_SECU_INFO_CNF_STRU
协议表格  :
ASN.1描述 :
结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSecuCntxt  : 1;
    VOS_UINT32                          bitSpare        : 31;

    LMM_GMM_SECU_INFO_RSLT_ENUM_UINT32  enRslt;
    LMM_GMM_UMTS_SECU_CONTEXT_STRU      stHoUmtsSecuCntxt;
}LMM_GMM_HO_SECU_INFO_CNF_STRU;

/*****************************************************************************
 枚举名    : GMM_LMM_SESSION_TYPE_ENUM_UINT8
 枚举说明  : SESSION类型
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum GMM_LMM_SESSION_TYPE_ENUM
{
    GMM_LMM_SESSION_TYPE_MO_SMS,
    GMM_LMM_SESSION_TYPE_MT_SMS,
    GMM_LMM_SESSION_TYPE_PS_ATTACH,
    GMM_LMM_SESSION_TYPE_PS_RAU,
    GMM_LMM_SESSION_TYPE_PS_DETACH,
    GMM_LMM_SESSION_TYPE_PS_CONVERSAT_CALL,
    GMM_LMM_SESSION_TYPE_PS_STREAM_CALL,
    GMM_LMM_SESSION_TYPE_PS_INTERACT_CALL,
    GMM_LMM_SESSION_TYPE_PS_BACKGROUND_CALL,
    GMM_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    GMM_LMM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 GMM_LMM_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : GMM_LMM_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMM_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[3];
}GMM_LMM_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : GMM_LMM_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月22日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMM_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType;
    VOS_UINT8                           aucReserved[3];
}GMM_LMM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
结构名    :LMM_GMM_TIMER_INFO_STRU
协议表格  :
ASN.1描述 :
结构说明  :定时器相关信息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          bitOpT3312  :1;
    VOS_UINT32                          bitOpRsv    :31;

    GMM_LMM_TIMER_STATE_ENUM_UINT32      enT3312State;
}GMM_LMM_TIMER_STATE_NOTIFY_STRU;




typedef struct
{
    GMM_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_MsgChoice_Export GMM_LMM_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          GMM_LMM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}GMM_LMM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    GMM_LMM_INTERFACE_MSG_DATA           stMsgData;
} GmmLmmInterface_MSG;







/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern    GMM_LMM_RESULT_ID_ENUM_UINT32  STUB_NAS_LMM_CompLmmHoSecuInfoCnf(
                    LMM_GMM_HO_SECU_INFO_CNF_STRU   *pstLmmHoSecuInfoCnf );

/*****************************************************************************
 函数名称: Nas_GetLrrcConnFailureFlag
 协议表格:
 ASN.1 描述:
 函数说明: 获取rrc connection failure标识，LNAS提供给GU NAS调用
           VOS_TRUE表示标识有效，异系统到GU需要发起RAU
           VOS_FALSE表示标识无效
*****************************************************************************/
extern VOS_UINT32  Nas_GetLrrcConnFailureFlag( VOS_VOID );



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

#endif /* end of GmmLmmInterface.h */

















