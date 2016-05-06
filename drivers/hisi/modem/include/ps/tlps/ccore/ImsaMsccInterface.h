/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ImsaMsccInterface.h
  版 本 号   : 初稿
  作    者   : yanglinping y00245242
  生成日期   : 2015年1月22日
  功能描述   : IMSA和MSCC接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年1月22日
    作    者   : yanglinping y00245242
    修改内容   : 创建文件

******************************************************************************/


#ifndef __IMSAMSCCINTERFACE_H__
#define __IMSAMSCCINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include "vos.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 枚举名    : IMSA_CONTROL_CONN_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 内部消息ID定义
*****************************************************************************/
enum MSCC_IMSA_MSG_ID_ENUM
{
    /* MSCC发给IMSA的消息原语 */
    ID_MSCC_IMSA_START_REQ              = 0x00,                                 /* _H2ASN_MsgChoice MSCC_IMSA_START_REQ_STRU */
    ID_MSCC_IMSA_STOP_REQ               ,                                       /* _H2ASN_MsgChoice MSCC_IMSA_STOP_REQ_STRU */
    ID_MSCC_IMSA_DEREG_REQ              ,                                       /* _H2ASN_MsgChoice MSCC_IMSA_DEREGISTER_REQ_STRU */
    ID_MSCC_IMSA_SERVICE_CHANGE_IND     ,                                       /* _H2ASN_MsgChoice MSCC_IMSA_SERVICE_CHANGE_IND_STRU */
    ID_MSCC_IMSA_CAMP_INFO_CHANGE_IND   ,                                       /* _H2ASN_MsgChoice MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU */
    ID_MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND,                                       /* _H2ASN_MsgChoice MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU */

    /* IMSA发给MSCC的消息原语 */
    ID_IMSA_MSCC_START_CNF              = 0x40,                                 /* _H2ASN_MsgChoice IMSA_MSCC_START_CNF_STRU */
    ID_IMSA_MSCC_STOP_CNF               ,                                       /* _H2ASN_MsgChoice IMSA_MSCC_STOP_CNF_STRU */
    ID_IMSA_MSCC_DEREG_CNF              ,                                       /* _H2ASN_MsgChoice IMSA_MSCC_DEREGISTER_CNF_STRU */
    ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY   ,                                       /* _H2ASN_MsgChoice IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU */
    ID_IMSA_MSCC_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 MSCC_IMSA_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/


enum MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM
{
    MSCC_IMSA_IMS_VOPS_NOT_SUPPORT      =0,
    MSCC_IMSA_IMS_VOPS_SUPPORT,
    MSCC_IMSA_IMS_VOPS_BUTT
};
typedef VOS_UINT8 MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8;

enum MSCC_IMSA_EMS_INDICATOR_ENUM
{
    MSCC_IMSA_EMS_NOT_SUPPORT           =0,
    MSCC_IMSA_EMS_SUPPORT,
    MSCC_IMSA_EMS_BUTT
};
typedef VOS_UINT8 MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8;

enum MSCC_IMSA_RAT_TYPE_ENUM
{
    MSCC_IMSA_RAT_TYPE_GSM              =0,
    MSCC_IMSA_RAT_TYPE_UTRAN,
    MSCC_IMSA_RAT_TYPE_LTE,
    MSCC_IMSA_RAT_TYPE_BUTT
};
typedef VOS_UINT8 MSCC_IMSA_RAT_TYPE_ENUM_UINT8;

enum MSCC_IMSA_SERVICE_STATUS_ENUM
{
    MSCC_IMSA_NORMAL_SERVICE            =0,
    MSCC_IMSA_LIMITED_SERVICE,
    MSCC_IMSA_NO_SERVICE,
    MSCC_IMSA_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 MSCC_IMSA_SERVICE_STATUS_ENUM_UINT8;

enum MSCC_IMSA_ACCESS_TYPE_ENUM
{
    MSCC_IMSA_ACCESS_TYPE_UTRAN_TDD,
    MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD,
    MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD,
    MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD,
    MSCC_IMSA_ACCESS_TYPE_GERAN,

    MSCC_IMSA_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8 MSCC_IMSA_ACCESS_TYPE_ENUM_UINT8;

enum MSCC_IMSA_IMS_VOICE_CAP_ENUM
{
    MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE = 0,
    MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE,

    MSCC_IMSA_IMS_VOICE_CAP_BUTT
};
typedef VOS_UINT8 MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8;

/*****************************************************************************
 结构名    : MSCC_IMSA_VOICE_DOMAIN_ENUM_UINT32
 结构说明  : VOIDE DOMAIN类型
  1.日    期   : 2015年04月13日
    作    者   : f00179208
    修改内容   : 新建
 *****************************************************************************/
enum MSCC_IMSA_VOICE_DOMAIN_ENUM
{
    MSCC_IMSA_VOICE_DOMAIN_CS_ONLY            = 0,    /* CS voice only */
    MSCC_IMSA_VOICE_DOMAIN_IMS_PS_ONLY        = 1,    /* IMS PS voice only */
    MSCC_IMSA_VOICE_DOMAIN_CS_PREFERRED       = 2,    /* CS vocie preferred, IMS PS voice as secondary */
    MSCC_IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,    /* IMS PS voice preferred, CS vocie as secondary */

    MSCC_IMSA_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32  MSCC_IMSA_VOICE_DOMAIN_ENUM_UINT32;
/*****************************************************************************
 结构名    : MSCC_IMSA_START_TYPE_ENUM_UINT32
 结构说明  : 开启IMS协议栈的操作类型
  1.日    期   : 2015年07月03日
    作    者   : f00179208
    修改内容   : 新建
 *****************************************************************************/
enum MSCC_IMSA_START_TYPE_ENUM
{
    MSCC_IMSA_START_TYPE_POWER_ON            = 0,
    MSCC_IMSA_START_TYPE_IMS_SWITCH_ON       = 1,
    MSCC_IMSA_START_TYPE_BUTT
};
typedef VOS_UINT32  MSCC_IMSA_START_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : MSCC_IMSA_STOP_TYPE_ENUM_UINT32
 结构说明  : 关闭IMS协议栈的操作类型
  1.日    期   : 2015年07月03日
    作    者   : f00179208
    修改内容   : 新建
 *****************************************************************************/
enum MSCC_IMSA_STOP_TYPE_ENUM
{
    MSCC_IMSA_STOP_TYPE_POWER_OFF            = 0,
    MSCC_IMSA_STOP_TYPE_IMS_SWITCH_OFF       = 1,
    MSCC_IMSA_STOP_TYPE_BUTT
};
typedef VOS_UINT32  MSCC_IMSA_STOP_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    /* 逻辑从右往左，ulMcc第0字节表示MCC digit1， ulMcc第1字节表示MCC digit2，
       ulMcc第2字节表示MCC digit3，ulMcc第3字节无效；
       逻辑从右往左，ulMnc第0字节表示MNC digit1， ulMnc第1字节表示MNC digit2，
       ulMnc第2字节表示MNC digit3，ulMnc第3字节无效；
       例如MCC+MNC为46001，则ulMcc为0x00000604,ulMnc为0x000f0100*/
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
}MSCC_IMSA_PLMN_ID_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    MSCC_IMSA_START_TYPE_ENUM_UINT32     enStartType;
}MSCC_IMSA_START_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}IMSA_MSCC_START_CNF_STRU;


/*****************************************************************************
 结构名    : IMSA_CALL_RESULT_ACTION_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_CALL_RESULT_ACTION_IND_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    MSCC_IMSA_STOP_TYPE_ENUM_UINT32      enStopType;
}MSCC_IMSA_STOP_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}IMSA_MSCC_STOP_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}MSCC_IMSA_DEREGISTER_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}IMSA_MSCC_DEREGISTER_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32                            ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                              bitRoamingValid : 1;
    VOS_UINT32                                              bitSpare        : 31;
    
    MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8                 enImsVoPsInd;
    MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8                      enEmsInd;
    MSCC_IMSA_SERVICE_STATUS_ENUM_UINT8                     enPsServiceStatus;
    VOS_UINT8                                               ucPsSimValid;       /* VOS_TRUE :有效，VOS_FALSE :无效*/
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8                           enRat;              /* 当前接入技术 */
    VOS_UINT8                                               ucRoamingFlg;       /* VOS_TRUE :漫游，VOS_FALSE :非漫游*/
    VOS_UINT8                                               aucReserve[2];
}MSCC_IMSA_SERVICE_CHANGE_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;                    /*_H2ASN_Skip*/

    MSCC_IMSA_ACCESS_TYPE_ENUM_UINT8    enAccessType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          usLac;
    VOS_UINT16                          usTac;
    MSCC_IMSA_PLMN_ID_STRU              stPlmnId;
    VOS_UINT32                          ulCellId;
}MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  enImsVoiceCap;
    VOS_UINT8                           ucIsExistPersistentBearer; /* 0:表示不存在1:表示存在*/
    VOS_UINT8                           aucRsv[2];
}IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;                    /*_H2ASN_Skip*/
    MSCC_IMSA_VOICE_DOMAIN_ENUM_UINT32  enVoiceDomain;              /* 0:cs only 1:ps only 2:cs prefer 3:ps prefer */
}MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU;

typedef struct
{
    MSCC_IMSA_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_MsgChoice_Export MSCC_IMSA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MSCC_IMSA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MSCC_IMSA_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    MSCC_IMSA_MSG_DATA                  stMsgData;
} ImsaMsccInterface_MSG;


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

#endif /* end of ImsaMsccInterface.h */

