/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LRrcRlcInterface.h
  Description     :
  History           :
      1.XiaoJun 58160       2009-08-25  Draft Enact
      2.Xuruimei 49630      2009-01-19  Modify
      3.Wang Yangcai 49178  2009-05-13  BJ9D00692:根据CP100平台修改消息ID
      4.guojiyu 00149868    2010-09-6 DTS2010082501092:流控配置L2UE能力和带宽信息修改合入

******************************************************************************/

#ifndef __LRRCLRLCINTERFACE_H__
#define __LRRCLRLCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LRrcPdcpInterface.h"
#include "LPSCommon.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define LRRC_LRLC_MSG_HDR             (PS_MSG_ID_RRC_TO_RLC_BASE)
#define LRLC_LRRC_MSG_HDR             (PS_MSG_ID_RLC_TO_RRC_BASE)

#define LPS_MAX_LMBMS_SESSION_NUM     (29)
#define LPS_MAX_LMBMS_PMCH_NUM        (15)
#define LPS_MAX_LMBMS_AREA_NUM        (8)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 结构名    : LRRC_LRLC_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC和RLC间的接口消息
*****************************************************************************/
enum LRRC_LRLC_MSG_TYPE_ENUM
{

    ID_LRRC_LRLC_CONFIG_REQ               = (LRRC_LRLC_MSG_HDR + 0x00),             /* _H2ASN_MsgChoice LRRC_LRLC_CONFIG_REQ_STRU */      /* RRC配置 RLC实体 */
    ID_LRRC_LRLC_CONFIG_CNF               = (LRLC_LRRC_MSG_HDR + 0x00),             /* _H2ASN_MsgChoice LRRC_LRLC_CONFIG_CNF_STRU */      /* RRC配置AM/UM/TM RLC实体的确认消息 */

    ID_LRRC_LRLC_RELEASE_REQ              = (LRRC_LRLC_MSG_HDR + 0x01),             /* _H2ASN_MsgChoice LRRC_LRLC_RELEASE_REQ_STRU */     /* RRC释放RLC实体 */
    ID_LRRC_LRLC_RELEASE_CNF              = (LRLC_LRRC_MSG_HDR + 0x01),             /* _H2ASN_MsgChoice LRRC_LRLC_RELEASE_CNF_STRU */     /* RRC释放RLC实体的确认*/

    ID_LRRC_LRLC_SUSPEND_REQ              = (LRRC_LRLC_MSG_HDR + 0x02),             /* _H2ASN_MsgChoice LRRC_LRLC_SUSPEND_REQ_STRU */     /* RRC挂起RLC实体 */
    ID_LRRC_LRLC_SUSPEND_CNF              = (LRLC_LRRC_MSG_HDR + 0x02),             /* _H2ASN_MsgChoice LRRC_LRLC_SUSPEND_CNF_STRU */     /* RRC挂起RLC实体的确认*/

    ID_LRRC_LRLC_RESUME_REQ               = (LRRC_LRLC_MSG_HDR + 0x03),             /* _H2ASN_MsgChoice LRRC_LRLC_RESUME_REQ_STRU */      /* RRC恢复RLC实体 */
    ID_LRRC_LRLC_RESUME_CNF               = (LRLC_LRRC_MSG_HDR + 0x03),             /* _H2ASN_MsgChoice LRRC_LRLC_RESUME_CNF_STRU */      /* RRC恢复RLC实体的确认*/

    ID_LRRC_LRLC_REESTABLISH_REQ          = (LRRC_LRLC_MSG_HDR + 0x04),             /* _H2ASN_MsgChoice LRRC_LRLC_REETBLSH_REQ_STRU */    /* RRC重建RLC实体 */
    ID_LRRC_LRLC_REESTABLISH_CNF          = (LRLC_LRRC_MSG_HDR + 0x04),             /* _H2ASN_MsgChoice LRRC_LRLC_REETBLSH_CNF_STRU */    /* RRC重建RLC实体的确认*/

    ID_LRRC_LRLC_TM_DATA_REQ              = (LRRC_LRLC_MSG_HDR + 0x05),             /* _H2ASN_MsgChoice LRRC_LRLC_TM_DATA_REQ_STRU */     /* RRC发送TM数据请求原语 */
    ID_LRRC_LRLC_TM_DATA_IND              = (LRLC_LRRC_MSG_HDR + 0x05),             /* _H2ASN_MsgChoice LRRC_LRLC_TM_DATA_IND_STRU */     /* RLC层上报TM数据原语 */

    ID_LRRC_LRLC_ERROR_IND                = (LRLC_LRRC_MSG_HDR + 0x06),             /* _H2ASN_MsgChoice LRRC_LRLC_ERR_IND_STRU */         /* RLC层使用此消息向RRC报告RLC层出现的问题和复位的情况 */

    ID_LRRC_LRLC_MBMS_CFG_REQ             = (LRRC_LRLC_MSG_HDR + 0x06),             /* _H2ASN_MsgChoice LRRC_LRLC_MBMS_CFG_REQ_STRU */      /* RRC配置 MBMS业务的实体信息 */
    ID_LRRC_LRLC_MBMS_CFG_CNF             = (LRLC_LRRC_MSG_HDR + 0x07),             /* _H2ASN_MsgChoice LRRC_LRLC_MBMS_CFG_CNF_STRU */      /* RRC配置MBMS业务的实体的确认消息 */
    ID_LRRC_LRLC_MCCH_DATA_IND            = (LRLC_LRRC_MSG_HDR + 0x08),             /* _H2ASN_MsgChoice LRRC_LRLC_MCCH_DATA_IND_STRU */     /* RLC层上报MCCH数据原语 */

    ID_LRRC_LRLC_MSG_TYPE_END
};
typedef VOS_UINT32 LRRC_LRLC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : LRRC_LRLC_SN_FIELD_LENGTH_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC SN field length的枚举
*****************************************************************************/
enum LRRC_LRLC_SN_FIELD_LENGTH_ENUM
{
    LRRC_LRLC_MSGHDR_5BIT                 = 0x0,                                  /*消息头中SN的长度为5BIT*/
    LRRC_LRLC_MSGHDR_10BIT                     ,
    LRRC_LRLC_MSGHDR_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_SN_FIELD_LENGTH_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LRLC_ERR_IND_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC错误指示的枚举
*****************************************************************************/
enum LRRC_LRLC_ERR_IND_ENUM
{
    LRRC_LRLC_ERR_RL_FAIL                      ,                                  /*链路检测失败*/
    LRRC_LRLC_ERR_NORMAL                       ,                                  /*RLC自身发生错误*/
    LRRC_LRLC_ERR_MEMFULL                      ,                                  /*RLC下行内存满*/
    LRRC_LRLC_ERR_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_ERR_IND_ENUM_UINT8;

/*****************************************************************************
 结构名    : LRRC_LRLC_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC层配置的结果:成功还是失败
*****************************************************************************/
enum LRRC_LRLC_RSLT_ENUM
{
    LRRC_LRLC_SUCC                            = 0,
    LRRC_LRLC_FAIL                            = 1,
    LRRC_LRLC_RSLT_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_RSLT_ENUM_UINT8;
/*****************************************************************************
 结构名    : LRRC_LRLC_SET_INFO_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 设置L2 Rlc相关信息
*****************************************************************************/
enum LRRC_LRLC_SET_INFO_TYPE_ENUM
{
    LRRC_LRLC_SET_UECAP                       = 0,                /* 设置UE Category */
    LRRC_LRLC_SET_BANDWIDTCH                  = 1,                /* 设置带宽 */
    LRRC_LRLC_SET_TYPE_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_SET_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_LRLC_PARA_VALID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 参数是否有效标识
*****************************************************************************/
enum LRRC_LRLC_PARA_VALID_ENUM
{
    LRRC_LRLC_PARA_INVALID                = 0,                                    /* 参数无效 */
    LRRC_LRLC_PARA_VALID,                                                         /* 参数有效 */
    LRRC_LRLC_PARA_BUTT
};
typedef VOS_UINT8 LRRC_LRLC_PARA_VALID_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_LRLC_ENTITY_REL_FALG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 指示RLC实体是否释放
*****************************************************************************/
enum LRRC_LRLC_ENTITY_REL_FALG_ENUM
{
    LRRC_LRLC_ENTITY_REL_NOT_NEED         = 0,                                    /* 不需要释放 */
    LRRC_LRLC_ENTITY_REL_NEED,                                                    /* 需要释放 */
    LRRC_LRLC_ENTITY_REL_BUTT
};
typedef VOS_UINT8 LRRC_LRLC_ENTITY_REL_FALG_ENUM_UINT8;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : LRRC_LRLC_UL_AM_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC AM模式上行的配置信息
*****************************************************************************/
/*AM的配置信息*/
typedef struct
{
    VOS_UINT16                          usPollRetransmitTimer;
    VOS_UINT16                          usPollPDU;

    VOS_UINT16                          usPollByte;

    VOS_UINT8                           ucMaxRetxThreshold;
    VOS_UINT8                           aucRev[1];
}LRRC_LRLC_UL_AM_INFO_STRU;                                                 /* 36.331 6.3.2 接口是用枚举值还是实际值? */

/*****************************************************************************
 结构名    : LRRC_LRLC_DL_AM_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC AM模式的下行配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReorderingTimer;
    VOS_UINT32                          ulTStatusProhibit;
}LRRC_LRLC_DL_AM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_AM_CONFIG_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC AM模式的配置信息
*****************************************************************************/
typedef struct
{
    LRRC_LRLC_UL_AM_INFO_STRU             stUlAmRlcInfo;
    LRRC_LRLC_DL_AM_INFO_STRU             stDlAmRlcInfo;
}LRRC_LRLC_AM_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_UL_UM_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC UM模式的上行配置信息
*****************************************************************************/
/*UM的配置信息*/
typedef struct
{
    LRRC_LRLC_SN_FIELD_LENGTH_ENUM_UINT8  enSnFieldLength;
    VOS_UINT8                           aucRev[3];
}LRRC_LRLC_UL_UM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_DL_UM_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC UM模式的下行配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReorderingTimer;

    LRRC_LRLC_SN_FIELD_LENGTH_ENUM_UINT8  enSnFieldLength;
    VOS_UINT8                           aucRev[3];
}LRRC_LRLC_DL_UM_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_UM_CONFIG_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC UM模式的配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitUlUmFlg      :1;                     /*上行UM的RLC参参数是否存在*/
    VOS_UINT32                          bitDlUmFlg      :1;                     /*下行UM的RLC参参数是否存在*/
    VOS_UINT32                          bitSpare        :30;

    LRRC_LRLC_UL_UM_INFO_STRU             stUlUmRlcInfo;
    LRRC_LRLC_DL_UM_INFO_STRU             stDlUmRlcInfo;
}LRRC_LRLC_UM_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_UL_LCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC 逻辑信道上行参数信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucLchPrio;                      /* 36.331 6.3.2 INTEGER (1..16) */
    VOS_UINT8                                   ucLchGrp;                       /* 36.331 6.3.2 INTEGER (0..3) */
    VOS_UINT16                                  usLchPrioBitRate;               /* 36.331 6.3.2 */
    VOS_UINT16                                  usBucketSizeDuration;           /* 36.331 6.3.2 */
    LRRC_LRLC_PARA_VALID_ENUM_UINT8             enLogicChSrMask;                /* 36.331 6.3.2 logicalChannelSR-Mask-r9 0:无效，1:有效 */
    VOS_UINT8                                   ucRev;
}LRRC_LRLC_UL_LCH_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_LCH_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC 逻辑信道参数信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitUlLchParaFlg        :1;              /* 指示上行逻辑信道配置参数是否存在 */
    VOS_UINT32                          bitSpare               :31;

    LRRC_LRLC_UL_LCH_INFO_STRU          stUlLchInfo;

}LRRC_LRLC_LCH_CONFIG_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_CONFIG_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的配置信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             ucRbId;
    LRLC_MODE_ENUM_UINT8                  enRlcMode;
    /* 指示RLC实体是否需要先释放再配置,0:不需要释放,1:需要先释放,然后根据最新参数进行配置  */
    LRRC_LRLC_ENTITY_REL_FALG_ENUM_UINT8  enRelInd;
    VOS_UINT8                             ucLchId;
    LRRC_LRLC_LCH_CONFIG_STRU             stLchCfg;

    union
    {
        LRRC_LRLC_AM_CONFIG_INFO_STRU     stAmInfo;
        LRRC_LRLC_UM_CONFIG_INFO_STRU     stUmInfo;
    }u;
}LRRC_LRLC_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_CONFIG_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的配置消息
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;

    VOS_UINT8                             ucRbNum;
    VOS_UINT8                             ucRev;
    LRRC_LRLC_CONFIG_INFO_STRU            astRlcInfo[PS_MAX_RB_NUM];
}LRRC_LRLC_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC->RRC的确认消息
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;

    LRRC_LRLC_RSLT_ENUM_UINT8             enResult;
    VOS_UINT8                             ucRev;
}LRRC_LRLC_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的释放，挂起，恢复消息
*****************************************************************************/
/*Release, supend消息*/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRbNum;
    VOS_UINT8                           ucRev;
    VOS_UINT8                           aucRbId[PS_MAX_RB_NUM];
}LRRC_LRLC_RELEASE_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的释放响应消息
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_SUSPEND_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的挂起消息
*****************************************************************************/
/*Release, supend消息*/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRbNum;
    VOS_UINT8                           ucRev;
    VOS_UINT8                           aucRbId[PS_MAX_RB_NUM];
}LRRC_LRLC_SUSPEND_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_SUSPEND_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的挂起响应消息
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_SUSPEND_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_RESUME_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的恢复息
*****************************************************************************/
/*Release, supend消息*/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRbNum;
    VOS_UINT8                           ucRev;
    VOS_UINT8                           aucRbId[PS_MAX_RB_NUM];
}LRRC_LRLC_RESUME_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_RESUME_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的恢复响应消息
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_RESUME_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_RLC_RETBLSH_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC-RLC的实体重建消息
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRev[2];
}LRRC_LRLC_REETBLSH_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_TM_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LRLC_TM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_TM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LRLC_TM_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_REETBLSH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的重建响应消息
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_REETBLSH_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_MBMS_PMCH_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的MBMS配置信息
*****************************************************************************/
typedef struct
{
    /*bit0:表示逻辑信道0是否有效，1表示有效，0表示无效，bit位:1-28分别表示逻辑信道1-28，
    比特位29-31保留，都填写0*/
    VOS_UINT32                          ulMbmsLchInfo;
}LRRC_LRLC_MBMS_PMCH_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_MBMS_AREA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的MBMS配置信息,数组astLMbmsPmch值为0表示对应PMCH无效，
             数组astLMbmsPmch值不为0表示PMCH对应有效；数组下标对应PMCH索引0-14
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             ucLMbmsAreaId;
    VOS_UINT8                             aucRev[3];
    LRRC_LRLC_MBMS_PMCH_INFO_STRU         astLMbmsPmch[LPS_MAX_LMBMS_PMCH_NUM];
}LRRC_LRLC_MBMS_AREA_INFO_STRU;


/*****************************************************************************
 结构名    : LRRC_LRLC_MBMS_CFG_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的MBMS配置信息
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;

    VOS_UINT8                             ucLMbmsAreaNum;
    VOS_UINT8                             ucRev;
    LRRC_LRLC_MBMS_AREA_INFO_STRU         astLMbmsAreaInfo[LPS_MAX_LMBMS_AREA_NUM];

}LRRC_LRLC_MBMS_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_MBMS_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC->RLC的MBMS配置响应消息
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_MBMS_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_MCCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32          enMsgName;                          /*_H2ASN_Skip*/

    VOS_UINT8                               ucAreaId;
    VOS_UINT8                               aucRsv1[3];

    VOS_UINT16                              usFrame;                            /*空口接收MCCH消息的帧号*/
    VOS_UINT8                               ucSubFrame;                         /*空口接收MCCH消息的子帧号*/
    VOS_UINT8                               aucRsv2[1];

    VOS_UINT32                              ulDataLength;
    VOS_UINT8                               aucData[4];
} LRRC_LRLC_MCCH_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LRRC_LRLC_ERR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RLC-RRC的错误指示
*****************************************************************************/
typedef struct
{
    /* 消息头 */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* 消息类型 */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                            /*_H2ASN_Skip*/

    LRRC_LRLC_ERR_IND_ENUM_UINT8          enErrType;
    VOS_UINT8                             ucRbId;                               /*触发重建立的RbId*/
    VOS_UINT16                            usSn;                                 /*触发重建立的sn*/
}LRRC_LRLC_ERR_IND_STRU;

typedef struct
{
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LRLC_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LRLC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_LRLC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LRRC_LRLC_MSG_DATA                    stMsgData;
}RrcRlcInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
 /* 设置L2 相关信息，其中 ucInitType=1，ulInitValue代表设置的是UE能力级别
    ucInitType=1，ulInitValue代表设置的时小区下行带宽*/
 extern VOS_VOID FC_InitFlowCtrlPara(VOS_UINT8 ucInitType,VOS_UINT32 ulInitValue);


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
