/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasCcb.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月27日
  功能描述   : CnasCcb.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/
#ifndef _CNAS_CCB_H_
#define _CNAS_CCB_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"

#include "CnasPrlParse.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define P_REV_IN_USE_7                                      (7)

#define P_REV_IN_USE_6                                      (6)


#define CNAS_CCB_MAX_HOME_SID_NID_LIST                      (20)

#define CNAS_CCB_ICCID_OCTET_LEN                            (10)

/* the byte num of EFRUIMID read from card  5 or 8*/
#define CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define CNAS_CCB_EFRUIMID_OCTET_LEN_FIVE                    (5)

#define CNAS_CCB_UIMID_OCTET_LEN                            (4)
#define CNAS_CCB_MAX_LOG_MSG_STATE_NUM                      (100)

#define CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM                     (20)

#define CNAS_CCB_MAX_FREQ_NUM                               (10)

#define CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM                 (4)     /* match with the num of max xcc fsm entity */

#define CNAS_CCB_MEID_OCTET_LEN                             (7)
#define CNAS_CCB_ESN_OCTET_LEN                              (4)
#define CNAS_CCB_ESN_MEID_OCTET_LEN                         (8)
#define CNAS_CCB_MAX_AUTHDATA_USERNAME_LEN                  (253)   /* HRPD ppp AN鉴权用户名最长用户名，
                                                                       参考C.S0023-D section 3.4.53以及
                                                                       C.S0016-D,section 3.5.8.13,
                                                                       该长度理论最长为255-2(NAI长度以
                                                                       及鉴权算法保留字节占用的字节) */

#define CNAS_CCB_BYTE_LEN_8_BIT                             (8)

/* 根据 Pid以及usMsgName 构建EventType  */
/*
    约束: PID结构 Bit0~Bit11: 模块ID  Bit12~Bit15: 保留 Bit16~Bit19: CPU ID Bit20~Bit31: 保留
    例: PID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
        MSG: 0x0000abcd
        EVT: 0xABCDabcd
*/
#define CNAS_BuildEventType(ulSndPid,usMsgName) \
    (((VOS_UINT32)(/*lint -e778*/((ulSndPid) & 0xF0000)/*lint +e778*/ \
    | (((ulSndPid) & 0xFFF) << 4)) << 12) | (VOS_UINT16)(usMsgName))      /* 根据 Pid以及usMsgName 构建EventType  */

#define CNAS_MIN(x, y)\
        (((x)<(y))?(x):(y))

#define CNAS_MAX(x, y)\
        (((x)>(y))?(x):(y))

/*lint -e778 */
/*lint -e572 */
#ifndef CNAS_NTOHL                   /* 大小字节序转换*/
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define CNAS_NTOHL(x)    (x)
#define CNAS_HTONL(x)    (x)
#define CNAS_NTOHS(x)    (x)
#define CNAS_HTONS(x)    (x)
#else
#define CNAS_NTOHL(x)    ((((x) & 0x000000ffU) << 24) | \
                         (((x) & 0x0000ff00U) <<  8) | \
                         (((x) & 0x00ff0000U) >>  8) | \
                         (((x) & 0xff000000U) >> 24))

#define CNAS_HTONL(x)    ((((x) & 0x000000ffU) << 24) | \
                         (((x) & 0x0000ff00U) <<  8) | \
                         (((x) & 0x00ff0000U) >>  8) | \
                         (((x) & 0xff000000U) >> 24))

#define CNAS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))

#define CNAS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))
#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */
#endif
/*lint -e572 */
/*lint -e778 */

#define     CNAS_CAS_INVALID_SUBSTA     (0xFF)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum CNAS_CCB_CARD_STATUS_ENUM
{
    CNAS_CCB_CARD_STATUS_ABSENT         = 0x0000,
    CNAS_CCB_CARD_STATUS_UIM_PRESENT    = 0x0001,                   /* uim present */
    CNAS_CCB_CARD_STATUS_CSIM_PRESENT   = 0x0002,                   /* csim present */
    CNAS_CCB_CARD_STATUS_SIM_PRESENT    = 0x0003,                   /* sim present */
    CNAS_CCB_CARD_STATUS_USIM_PRESENT   = 0x0004,                   /* usim present */
    CNAS_CCB_CARD_STATUS_BUTT           = 0x0005
};
typedef VOS_UINT8 CNAS_CCB_CARD_STATUS_ENUM_UINT8;

/** ****************************************************************************
 * Name        : CNAS_CCB_PS_RATTYPE_ENUM
 *
 * Description :
 *******************************************************************************/
enum CNAS_CCB_PS_RATTYPE_ENUM
{
    CNAS_CCB_PS_RATTYPE_NULL            = 0x00000000,
    CNAS_CCB_PS_RATTYPE_1X              = 0x00000001,
    CNAS_CCB_PS_RATTYPE_HRPD            = 0x00000002,
    CNAS_CCB_PS_RATTYPE_EHRPD           = 0x00000003,
    CNAS_CCB_PS_RATTYPE_LTE             = 0x00000004,
    CNAS_CCB_PS_RATTYPE_BUTT            = 0x00000005
};
typedef VOS_UINT32 CNAS_CCB_PS_RATTYPE_ENUM_UINT32;


/** ****************************************************************************
 * Name        : CNAS_CCB_1X_CAS_STATE_ENUM_UINT8
 *
 * Description : When MS is in the different state, MS should perform
 * different actions.
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum CNAS_CCB_1X_CAS_STATE_ENUM
{
    CNAS_CCB_1X_CAS_INIT_STATE          = 0x00,
    CNAS_CCB_1X_CAS_IDLE_STATE          = 0x01,
    CNAS_CCB_1X_CAS_ACCESS_STATE        = 0x02,
    CNAS_CCB_1X_CAS_TCH_STATE           = 0x03,
    CNAS_CCB_1X_CAS_NO_SERVICE_STATE    = 0x04,
    CNAS_CCB_1X_CAS_STATE_BUTT          = 0x05
};
typedef VOS_UINT8 CNAS_CCB_1X_CAS_STATE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8
 *
 * Description : .
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum CNAS_CCB_1X_CAS_SUB_STATE_ENUM
{
    CNAS_CCB_1X_CAS_SUB_STATE_NULL                          = 0x00,
    CNAS_CCB_1X_CAS_INIT_DETERM_SUB_STATE                   = 0x01,
    CNAS_CCB_1X_CAS_PILOT_CH_ACQ_SUB_STATE                  = 0x02,
    CNAS_CCB_1X_CAS_SYNC_CH_ACQ_SUB_STATE                   = 0x03,
    CNAS_CCB_1X_CAS_TIMING_CHNG_SUB_STATE                   = 0x04,
    CNAS_CCB_1X_CAS_IDLE_SUB_STATE                          = 0x10,
    CNAS_CCB_1X_CAS_UPDATE_OVERHEAD_SUB_STATE               = 0x20,
    CNAS_CCB_1X_CAS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE      = 0x21,
    CNAS_CCB_1X_CAS_PAG_RESP_SUB_STATE                      = 0x22,
    CNAS_CCB_1X_CAS_MOB_STATION_ORDR_RESP_SUB_STATE         = 0x23,
    CNAS_CCB_1X_CAS_REG_ACCESS_SUB_STATE                    = 0x24,
    CNAS_CCB_1X_CAS_MOB_STATION_MSG_TRANS_SUB_STATE         = 0x25,
    CNAS_CCB_1X_CAS_TCH_INIT_SUB_STATE                      = 0x30,
    CNAS_CCB_1X_CAS_REL_SUB_STATE                           = 0x31,
    CNAS_CCB_1X_CAS_WAIT_FOR_SERVICE_SUB_STATE              = 0x40,
    CNAS_CCB_1X_CAS_SUB_STATE_ENUM_BUTT                     = 0x41
};
typedef VOS_UINT8 CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8
 *
 * Description : .
 * Refers to
 *******************************************************************************/
enum CNAS_CCB_1X_CAS_P_REV_ENUM
{
    CNAS_CCB_1X_CAS_P_REV_JST_008               = 0x01,
    CNAS_CCB_1X_CAS_P_REV_IS_95                 = 0x02,
    CNAS_CCB_1X_CAS_P_REV_IS_95A                = 0x03,
    CNAS_CCB_1X_CAS_P_REV_IS_95B_CUSTOM         = 0x04,
    CNAS_CCB_1X_CAS_P_REV_IS_95B                = 0x05,
    CNAS_CCB_1X_CAS_P_REV_IS_2000               = 0x06,
    CNAS_CCB_1X_CAS_P_REV_IS_2000A              = 0x07,

    CNAS_CCB_1X_CAS_P_REV_ENUM_BUTT
};
typedef VOS_UINT8 CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_CCB_1X_CALL_STATE_ENUM
 结构说明  : 1X呼叫状态

 1.日    期   : 2015年05月22日
   作    者   : L00301449
   修改内容   : 新增
*****************************************************************************/
enum CNAS_CCB_1X_CALL_STATE_ENUM
{
    CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ORDER,
    CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
    CNAS_CCB_1X_CALL_STATE_CONVERSATION,
    CNAS_CCB_1X_CALL_STATE_IDLE,
    CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
    CNAS_CCB_1X_CALL_STATE_ORIG_CALL,

    CNAS_CCB_1X_CALL_STATE_BUTT
};
typedef VOS_UINT8 CNAS_CCB_1X_CALL_STATE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_CCB_1X_SO_TYPE_ENUM
 结构说明  : 1X业务类型

 1.日    期   : 2015年07月22日
   作    者   : y00322978
   修改内容   : 新增
*****************************************************************************/
enum CNAS_CCB_1X_SO_TYPE_ENUM
{
    CNAS_CCB_1X_SO_TYPE_VOICE,
    CNAS_CCB_1X_SO_TYPE_SMS,
    CNAS_CCB_1X_SO_TYPE_PS,
    CNAS_CCB_1X_SO_TYPE_LOOPBACK,
    CNAS_CCB_1X_SO_TYPE_AGPS,
    CNAS_CCB_1X_SO_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_CCB_1X_SO_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_CCB_1X_RETURN_CAUSE_ENUM
 结构说明  : C.S0005-A_v6.0 Table 2.7.1.3.2.1-2 RETURN_CASUSE Codes

 1.日    期   : 2015.07.13
   作    者   : m00312079
   修改内容   : 新增
*****************************************************************************/
enum CNAS_CCB_1X_RETURN_CAUSE_ENUM
{
    CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS             = 0x00,
    CNAS_CCB_1X_RETURN_CAUSE_SYSTEM_NOT_ACQ            = 0x01,
    CNAS_CCB_1X_RETURN_CAUSE_PROTOCOL_MISMATCH         = 0x02,
    CNAS_CCB_1X_RETURN_CAUSE_REG_REJ                   = 0x03,
    CNAS_CCB_1X_RETURN_CAUSE_WRONG_SID                 = 0x04,
    CNAS_CCB_1X_RETURN_CAUSE_WRONG_NID                 = 0x05,

    CNAS_CCB_1X_RETURN_CAUSE_BUTT
};
typedef VOS_UINT8 CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : CNAS_CCB_ESN_MEID_TYPE_ENUM
 结构说明  :

 1.日    期   : 2015.09.30
   作    者   : y00307564
   修改内容   : 新增
 *******************************************************************************/
enum CNAS_CCB_ESN_MEID_TYPE_ENUM
{
    CNAS_CCB_ESN_MEID_TYPE_ESN      = 0,
    CNAS_CCB_ESN_MEID_TYPE_MEID        ,

    CNAS_CCB_ESN_MEID_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_CCB_ESN_MEID_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_CCB_SERVICE_STATUS_ENUM_UINT32
 结构说明  : 服务状态
 1.日    期: 2016年01月23日
   作    者: h00313353
   修改内容: 新增
*****************************************************************************/
enum CNAS_CCB_SERVICE_STATUS_ENUM
{
    CNAS_CCB_SERVICE_STATUS_NO_SERVICE                      = 0,        /* 无服务   */
    CNAS_CCB_SERVICE_STATUS_LIMITED_SERVICE                 = 1,        /* 限制服务 */
    CNAS_CCB_SERVICE_STATUS_NORMAL_SERVICE                  = 2,        /* 正常服务 */

    CNAS_CCB_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 CNAS_CCB_SERVICE_STATUS_ENUM_UINT32;

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
 结构名    : CNAS_CCB_1X_CALL_STATE_STRU
 结构说明  : CALL STATE 信息
 1.日    期   : 2015年7月21日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       en1xCallState;
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8                          en1xSoType;
    VOS_UINT8                                               aucRslv[2];
}CNAS_CCB_1X_CALL_STATE_STRU;


/*****************************************************************************
 结构名    : CNAS_CCB_UIMID_STRU
 结构说明  : UIMID 信息
 1.日    期   : 2015年6月3日
   作    者   : y00346957
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucEFRUIMID[CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT]; /* all the bytes in the EFRUIMID  */
}CNAS_CCB_UIMID_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_ESNMEIDME_INFO_STRU
 结构说明  : ESNMEIDMEID 信息
 1.日    期   : 2015年9月30日
   作    者   : y00307564
   修改内容   : DTS2015082403731新建
*****************************************************************************/
typedef struct
{
    CNAS_CCB_ESN_MEID_TYPE_ENUM_UINT8   enEsnMeidType;

    union
    {
        VOS_UINT8                       aucEsn[CNAS_CCB_ESN_OCTET_LEN];
        VOS_UINT8                       aucMeid[CNAS_CCB_MEID_OCTET_LEN];
    }u;
}CNAS_CCB_ESNMEIDME_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU
 结构说明  : HRPDUPPID 信息,HRPD接入鉴权用户名
 1.日    期   : 2015年9月30日
   作    者   : y00307564
   修改内容   : DTS2015082403731新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAccessAuthAvailFlag;     /* VOS_TRUE/VOS_FALSE */
    VOS_UINT8                           ucAccessAuthUserNameLen;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           aucAccessAuthUserName[CNAS_CCB_MAX_AUTHDATA_USERNAME_LEN];
}CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_CARD_INFO_STRU
 结构说明  : 卡信息
 1.日    期   : 2014年7月15日
   作    者   : h00246512
   修改内容   : 新建
 2.日    期   : 2015年6月02日
   作    者   : y00346957
   修改内容   : 增加卡的UIMID
 3.日    期   : 2015年9月30日
   作    者   : y00307564
   修改内容   : 增加卡的ESNMEIDME和PPP AN鉴权用户名
*****************************************************************************/
typedef struct
{
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCsimCardStatus;  /* CSIM卡状态 */
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enUsimCardStatus;  /* USIM卡状态 */
    VOS_UINT8                                               aucCardIccId[CNAS_CCB_ICCID_OCTET_LEN];     /* 卡文件2fe2，卡中保存的ICCID*/
    CNAS_CCB_UIMID_STRU                                     stUIMID;                  /* 卡文件6f31，卡中保存的UIMID */

    CNAS_CCB_ESNMEIDME_INFO_STRU                            stEsnMeidMe;              /* 卡文件6f38，esn meid me */
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                     stHrpdAccessAuthInfo;     /* 卡文件6f57，当前卡文件中的hrpd ppp an 鉴权用户名 */
}CNAS_CCB_CARD_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_1X_SYS_INFO_STRU
 结构说明  : CDAM 1x Sys info信息
  1.日    期   : 2015年10月27日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usChannel;
}CNAS_CCB_1X_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_NW_INFO_STRU
 结构说明  : 网络信息
 1.日    期   : 2014年9月15日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucConcurrentSupported;                  /* 并发业务是否支持 */
    VOS_UINT8                               ucPRevInUse;                            /* 协议使用版本 */
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8        enCasSta;                               /* CAS的状态 */

    CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8    enCasSubSta;                            /* CAS的子状态 */
    CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8        enProtocolRev;                          /* CAS上报的手机支持的最高协议版本 */
    VOS_UINT8                               uc1XRfAvailFlg;                           /* RF资源可用标记:VOS_TRUE :默认RF资源可用
                                                                                                    VOS_FALSE:RF资源不可用 */

    VOS_UINT8                               aucReserved[2];

    CNAS_CCB_1X_SYS_INFO_STRU               st1xSysInfo;
}CNAS_CCB_NW_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CALL_CONFIG_INFO_STRU
 结构说明  : 呼叫配置信息
 1.日    期   : 2014年9月15日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* 注册模块赋值，XCC会使用 */
    VOS_UINT8                           ucIsMtCallInRoamingAcc;     /*Mobile terminated calls*/
    VOS_UINT8                           aucReserved[3];
}CNAS_CALL_CONFIG_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_CUSTOM_CFG_INFO_STRU
 结构说明  : NVIM配置信息
 1.日    期   : 2014年10月23日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPowerOffCampOnCtrlFlg;                /* 关机驻留控制标记 */
    VOS_UINT8                           aucReserved[3];
}CNAS_CCB_CUSTOM_CFG_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_1X_HOME_SID_NID_STRU
 结构说明  : HOME_SID_NID相关信息
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usReserved;
}CNAS_CCB_1X_HOME_SID_NID_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_1X_HOME_SID_NID_LIST_STRU
 结构说明  : HOME_SID_NID列表信息
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserved[3];
    CNAS_CCB_1X_HOME_SID_NID_STRU       astHomeSidNid[CNAS_CCB_MAX_HOME_SID_NID_LIST];
}CNAS_CCB_1X_HOME_SID_NID_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_MODEM_INFO_STRU
 结构说明  : C模与modem对接的modem信息
 1.日    期   : 2015年5月21日
   作    者   : w00242748
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enCdmaModeModemId;
    VOS_UINT8                           aucReserve[2];
}CNAS_CCB_MODEM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_1X_SRV_INFO_STRU
 结构说明  : 1X服务信息
 1.日    期   : 2016年01月26日
   作    者   : h00313353
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 enCurSrvStatus; /* 存储1X当前服务状态 */
    VOS_UINT8                           aucReserved[4];
}CNAS_CCB_1X_SRV_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_MSG_STATE_STRU
 结构说明  : 发送接收消息状态结构体

  1.日    期   : 2015年7月12日
    作    者   : y00322978
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReceiveTime;  /* 接收时间 */
    VOS_UINT32                          ulExitTime;     /* 结束时间 */
    VOS_UINT16                          usSendPid;      /* 发送PID */
    VOS_UINT16                          usReceivePid;   /* 接收PID */
    VOS_UINT16                          usMsgName;      /* 消息名 */
    VOS_UINT8                           ucCnasFsmId;    /* 对应模块状态机ID  */
    VOS_UINT8                           ucCnasState;    /* 对应模块的s当前状态  */
}CNAS_CCB_MSG_STATE_STRU;
/*****************************************************************************
 结构名    : CNAS_CCB_LOG_MSG_STATUS_STRU
 结构说明  : 发送接收消息状态结构体

  1.日    期   : 2015年7月12日
    作    者   : y00322978
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    CNAS_CCB_MSG_STATE_STRU             stMsgState[CNAS_CCB_MAX_LOG_MSG_STATE_NUM];
    VOS_UINT32                          ucLatestIndex;
}CNAS_CCB_LOG_MSG_STATUS_STRU;
/*****************************************************************************
 结构名    : CNAS_CCB_MNTN_CTX_STRU
 结构说明  : cnas 模块勾取发送接收消息结构体 可维可测

  1.日    期   : 2015年7月12日
    作    者   : y00322978
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    CNAS_CCB_LOG_MSG_STATUS_STRU            stLogMsgState;
}CNAS_CCB_MNTN_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_SYS_INFO_STRU
 结构说明  : 保存的SID和MCC信息

  1.日    期   : 2015年5月21日
    作    者   : w00242748
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}CNAS_CCB_SYS_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_NVIM_OPER_LOCK_WHITE_SID_STRU
 结构说明  : en_NV_Item_OPER_LOCK_WHITE_SID_INFO NV项结构
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /* 白名单是否使能 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* 支持白名单的个数,个数为0时表示不支持白名单 */
    CNAS_CCB_SYS_INFO_STRU              astSysInfo[CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_FREQENCY_CHANNEL_STRU
 结构说明  : 频点结构
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT8                           aucReserved[2];
}CNAS_CCB_FREQENCY_CHANNEL_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_CTCC_CUSTOMIZE_INFO_STRU
 结构说明  : 中国电信定制频点结构
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_CCB_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CCB_MAX_FREQ_NUM];
}CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_CTCC_CUSTOMIZE_INFO_STRU
 结构说明  : 中国电信定制结构
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                  stCustFreqList;
}CNAS_CCB_CTCC_CUSTOMIZE_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU
 结构说明  : CDAM standard channels信息
  1.日    期   : 2015年7月14日
    作    者   : y00245242
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryA;
    VOS_UINT16                          usPrimaryB;
    VOS_UINT16                          usSecondaryA;
    VOS_UINT16                          usSecondaryB;
}CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_CTX_STRU
 结构说明  : CNAS的公共信息
 1.日    期   : 2014年7月15日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_CCB_CARD_INFO_STRU                                 stCardInfo;
    CNAS_CALL_CONFIG_INFO_STRU                              stCallInfoCfg;
    CNAS_CCB_NW_INFO_STRU                                   stNwInfo;
    CNAS_CCB_CUSTOM_CFG_INFO_STRU                           stCustomCfg;                    /* NVIM中的定制信息 */

    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU                      stHomeSidNidList;
    CNAS_CCB_MODEM_INFO_STRU                                stModemInfo;

    CNAS_CCB_PS_RATTYPE_ENUM_UINT32                         enCurrPsRatType;
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32                         enPrevPsRatType;

    CNAS_CCB_1X_CALL_STATE_STRU                             astMntn1xCallState[CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM];

    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8                     en1xReturnCause;

    VOS_UINT8                                               uc1XCallExistCount;             /* 呼叫计数器 */
    VOS_UINT8                                               ucHomeSidNidDependOnPrlFlg;
    VOS_UINT8                                               aucRsved[1];

    CNAS_CCB_MNTN_CTX_STRU                                  stMntnInfo;
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                  stOperLockSysWhiteList;

    CNAS_CCB_CTCC_CUSTOMIZE_INFO_STRU                       stCTCCCustInfo;

    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                    stCdmaStandardChan;

    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stOhmFreq;

    CNAS_CCB_1X_SRV_INFO_STRU                               st1XSrvInfo;
}CNAS_CCB_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_CCB_MODEM_PID_TAB_STRU
 结构说明  : DSDA 两个modem接收AT发送消息的PID映射表

  1.日    期   : 2015年5月21日
    作    者   : w00242748
    修改内容   : 新生成
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulModem0Pid;
    VOS_UINT32                           ulModem1Pid;
}CNAS_CCB_MODEM_PID_TAB_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetCsimCardStatus( VOS_VOID );

VOS_VOID CNAS_CCB_InitCcbCtx(VOS_VOID);

CNAS_CCB_CTX_STRU* CNAS_CCB_GetCcbCtxAddr( VOS_VOID );

VOS_VOID CNAS_CCB_SetCsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus
);
VOS_UINT16 CNAS_CCB_GetCasCardStatus(VOS_VOID);

VOS_UINT8 CNAS_CCB_GetConcurrentSupportedFlag(VOS_VOID);

VOS_VOID CNAS_CCB_SetConcurrentSupportedFlag(
    VOS_UINT8                           ucConcurrentSupported
);

VOS_UINT8 CNAS_CCB_GetPRevInUse(VOS_VOID);

VOS_VOID CNAS_CCB_SetPRevInUse(
    VOS_UINT8                           ucPRevInUse
);
VOS_VOID CNAS_CCB_SetMtCallInRoamingAccFlg(
    VOS_UINT8                           ucIsMtCallInRoamingAcc
);

VOS_UINT8 CNAS_CCB_GetMtCallInRoamingAccFlg( VOS_VOID );

VOS_VOID CNAS_CCB_SetCasState(
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enSta
);

CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_CCB_GetCasState(VOS_VOID);

VOS_VOID CNAS_CCB_SetPowerOffCampOnCtrlFlg(
    VOS_UINT8                           ucPowerOffCampOnFlg
);

VOS_UINT8 CNAS_CCB_GetPowerOffCampOnCtrlFlg( VOS_VOID );

VOS_VOID CNAS_CCB_InitHomeSidNidList(
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList
);

CNAS_CCB_1X_HOME_SID_NID_LIST_STRU* CNAS_CCB_GetHomeSidNidList(VOS_VOID);

CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8 CNAS_CCB_GetCasSubState(VOS_VOID);

VOS_VOID CNAS_CCB_SetCasSubState(
    CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8    enSubSta
);

CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8 CNAS_CCB_GetHighProRev(VOS_VOID);

VOS_VOID CNAS_CCB_SetHighProRev(
    CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8    enProtocolRev
);


CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xVoiceCallState(VOS_VOID);

CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xSmsCallState(
    VOS_VOID
);
CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xPsCallState(
    VOS_VOID
);
CNAS_CCB_1X_SO_TYPE_ENUM_UINT8 CNAS_CCB_ConvertSoToServiceType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  en1xSo
);

VOS_VOID CNAS_CCB_Set1xCallState(
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       en1xCallState,
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8                          en1xSoType
);


CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_Get1xReturnCause(VOS_VOID);

VOS_VOID CNAS_CCB_Set1xReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8                     en1xReturnCause
);


VOS_VOID CNAS_CCB_Set1XRfAvailFlg(
    VOS_UINT8                           uc1XRfAvailFlg
);

VOS_UINT8 CNAS_CCB_Get1XRfAvailFlg( VOS_VOID );


CNAS_CCB_UIMID_STRU* CNAS_CCB_GetUIMID(VOS_VOID);


VOS_VOID CNAS_CCB_SetCdmaModeModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

MODEM_ID_ENUM_UINT16 CNAS_CCB_GetCdmaModeModemId( VOS_VOID );

VOS_UINT32 CNAS_CCB_ConvertPidBasedOnModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulRcvPid
);

VOS_UINT32 CNAS_CCB_GetModem0Pid(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulSenderPid
);

VOS_UINT8* CNAS_CCB_GetCardIccIdAddr(VOS_VOID);

VOS_VOID CNAS_CCB_InitIccId(VOS_VOID);

VOS_VOID CNAS_CCB_InitUIMID(VOS_VOID);

VOS_VOID CNAS_CCB_InitEsnMeidMeInfo(VOS_VOID);

VOS_VOID CNAS_CCB_InitHrpdAccessAuthInfo(VOS_VOID);

extern VOS_VOID CNAS_CCB_SetUsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enUsimCardStatus
);

extern CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetUsimCardStatus( VOS_VOID );

VOS_VOID CNAS_CCB_SetPrevRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enPsRatType
);
CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetPrevPsRatType(VOS_VOID);
VOS_VOID CNAS_CCB_SetCurrPsRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32    enPsRatType
);
CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetCurrPsRatType(VOS_VOID);


CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_CovertReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   enCnas1xReturnCause
);

VOS_VOID CNAS_CCB_InitMntnInfo(
    CNAS_CCB_MNTN_CTX_STRU             *pstMntnInfo
);

VOS_VOID CNAS_CCB_Set1XCallExistCount(
    VOS_UINT8                           uc1XCallExistCount
);

VOS_UINT8 CNAS_CCB_Get1XCallExistCount( VOS_VOID );

VOS_UINT8 CNAS_CCB_GetHomeSidNidDependOnPrlFlg(VOS_VOID);

VOS_VOID CNAS_CCB_SetHomeSidNidDependOnPrlFlg(
    VOS_UINT8                           ucFlg
);

CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU* CNAS_CCB_GetOperLockSysWhiteList(VOS_VOID);

CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU* CNAS_CCB_GetCTCCCustomizeFreqList(VOS_VOID);

CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU* CNAS_CCB_GetCdmaStandardChannels(VOS_VOID);

VOS_VOID CNAS_CCB_InitCdmaStandardChannels(
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan
);

CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_CCB_GetCdmaOhmFreq(VOS_VOID);

VOS_VOID CNAS_CCB_SetCdmaOhmFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstOhmFreq
);

VOS_VOID CNAS_CCB_ClearCdmaOhmFreq(VOS_VOID);

VOS_VOID CNAS_CCB_Set1xSysInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT16                          usBandClass,
    VOS_UINT16                          usChannel
);

CNAS_CCB_1X_SYS_INFO_STRU* CNAS_CCB_Get1xSysInfo(VOS_VOID);

CNAS_CCB_ESNMEIDME_INFO_STRU* CNAS_CCB_GetEsnMeidMeInfoAddr(VOS_VOID);

CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU* CNAS_CCB_GetHrpdAccesAuthInfoAddr(VOS_VOID);
VOS_UINT32 CNAS_CCB_IsCurCallStateIdle( VOS_VOID );
CNAS_CCB_1X_SRV_INFO_STRU* CNAS_CCB_GetCur1XSrvInfo(VOS_VOID);

CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 CNAS_CCB_GetCur1XSrvStatus(VOS_VOID);

VOS_VOID CNAS_CCB_SetCur1XSrvStatus(
    CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 enSrvStatus
);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
