/******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : LLInterface.h
  Author      : g45205
  Version     : V200R001
  Date        : 2005-06-16
  Description : 该头文件定义了LLC模块对GMM和SMS的接口
  History     :
  1. Date:2005-06-16
     Author: g45205
     Modification:Create
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  3.日    期   : 2009年02月12日
    作    者   : f62575
    修改内容   : 问题单A32D08966，参考V1R1版本的清除PC-LINT告警方式清除V2R1版本和V1R2版本告警
  4.日    期   : 2009年6月30日
    作    者   : s46746
    修改内容   : AT2D12561,3G2情形GPRS下未启动加密，NAS指派层2加密算法后，层2对上行数据进行了加密
******************************************************************************/
#ifndef _LL_INTERFACE_H_
#define _LL_INTERFACE_H_

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "PsTypeDef.h"

/******************************************************************************
 2 宏定义
******************************************************************************/
/* 消息ID */
#define ID_LL_GMM_ASSIGN_REQ        0x0001
#define ID_LL_GMM_TRIGGER_REQ       0x0002
#define ID_LL_GMM_SUSPEND_REQ       0x0003
#define ID_LL_GMM_RESUME_REQ        0x0004
#define ID_LL_GMM_STATUS_IND        0x0005
#define ID_LL_GMM_ABORT_REQ         0x0006

#define ID_LL_UNITDATA_REQ          0x0015
#define ID_LL_UNITDATA_IND          0x0016
#define ID_LL_UNITDATA_CNF          0x0017

#define ID_LL_DATA_INFORM           0x0020

#define LL_INVALID_TLLI             0xFFFFFFFF

/* 无线优先级定义 */
/*
Priority (2 bit field)
This information field indicates the requested Radio Priority. This field is coded as shown in the following table. The
8 bit format has a default Radio Priority of 4.bit
bit
2 1
0 0 Radio Priority 1 (Highest priority)
0 1 Radio Priority 2
1 0 Radio Priority 3
1 1 Radio Priority 4 (Lower priority)
*/
#define LL_RADIO_PRI_1              0
#define LL_RADIO_PRI_2              1
#define LL_RADIO_PRI_3              2
#define LL_RADIO_PRI_4              3

/* SAPI取值定义 */
#define LL_SAPI_GMM                 1   /* SAPI1 for GMM */
#define LL_SAPI_SMS                 7   /* SAPI7 for SMS */

/* 用于表示指配命令具体功能的掩码
   b000 0000 : 1表示指配TLLI ;0表示不指配TLLI
   0b00 0000 : 1表示指配加密算法KC ; 0表示不指配加密算法KC */
#define LL_ASSIGN_REQ_MASK_TLLI     0x80
#define LL_ASSIGN_REQ_MASK_CiphAlg  0x40

/*
Type of ciphering algorithm
bits
3   2   1
0   0   0       ciphering not used
0   0   1       GPRS Encryption Algorithm GEA/1
0   1   0       GPRS Encryption Algorithm GEA/2
0   1   1       GPRS Encryption Algorithm GEA/3
1   0   0       GPRS Encryption Algorithm GEA/4
1   0   1       GPRS Encryption Algorithm GEA/5
1   1   0       GPRS Encryption Algorithm GEA/6
1   1   1       GPRS Encryption Algorithm GEA/7
*/
#define LL_GEA0     0       /* ciphering not used */
#define LL_GEA1     1
#define LL_GEA2     2
#define LL_GEA3     3
#define LL_GEA4     4
#define LL_GEA5     5
#define LL_GEA6     6
#define LL_GEA7     7


#define LL_GMM_TRIG_CAUSE_PAG_RSP               0   /* 寻呼响应 */
#define LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY 1   /* 小区更新但SGSN未指示Cell Notification*/
#define LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY    2   /* 小区更新且SGSN指示Cell Notification */


#define LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP       1     /* unsolicited UA response */
#define LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP       2     /* unsolicited DM response */
#define LL_GMM_STA_CAUSE_RETRANS_SABM_N200        3     /* SABM命令重发N200次 */
#define LL_GMM_STA_CAUSE_RETRANS_DISC_N200        4     /* DISC命令重发N200次 */
#define LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200     5     /* XID命令重复N200次 */
#define LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200   6     /* 查询对方是否处于忙状态超过N200次 */
#define LL_GMM_STA_CAUSE_LLC_INIT_RE_EST          7     /* LLC发起ABM重建 */
#define LL_GMM_STA_CAUSE_PEER_INIT_RE_EST         8     /* 对端发起ABM重建 */
#define LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION      9     /* 检测到帧拒绝条件 */
#define LL_GMM_STA_CAUSE_RECV_FRMR_RSP            10    /* 接收到FRMR响应 */
#define LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL          11    /* TLLI指配失败 */
#define LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL         12    /* LLC帧发送触发请求失败 */
#define LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL         13    /* LLC挂起失败 */
#define LL_GMM_STA_CAUSE_GMM_RESUME_FAIL          14    /* LLC恢复失败 */

/* 根据L3数据判断是否为GMM数据,如果首字节为0x08则为GMM数据，如果为0x0A则为SM数据 */
#define LL_GMM_DATA                               0x8
#define LL_SM_DATA                                0xA

/******************************************************************************
  3 结构定义
******************************************************************************/

/******************************************************************************
  4 枚举定义
******************************************************************************/

enum LL_GMM_CIPH_FLG_ENUM
{
    LL_GMM_CIPH_STOP            = 0,    /*0: 停止 */
    LL_GMM_CIPH_START           = 1,    /*1: 启动 */
    LL_GMM_CIPH_FLG_BUTT        = 2
};
typedef VOS_UINT8 LL_GMM_CIPH_FLG_ENUM_UINT8;

enum LL_GMM_CLEAR_DATA_TYPE_ENUM
{
    LL_GMM_CLEAR_DATA_TYPE_GMM          = 0x01,    /* GMM信令 */
    LL_GMM_CLEAR_DATA_TYPE_SM           = 0x02,    /* SM信令 */
    LL_GMM_CLEAR_DATA_TYPE_CELL_UPDT    = 0x04,    /* CELL_UPDATE数据 */
    LL_GMM_CLEAR_DATA_TYPE_PAGE_RSP     = 0x08,    /* PAGE_RSP数据 */
    LL_GMM_CLEAR_DATA_TYPE_USER         = 0x10,    /* 用户面数据 */
    LL_GMM_CLEAR_DATA_TYPE_SMS          = 0x20,    /* 短消息数据 */
    LL_GMM_CLEAR_DATA_TPYE_BUTT
};
typedef VOS_UINT8 LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8;

#define LL_GMM_CLEAR_DATA_TYPE_TRIG              ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_CELL_UPDT \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_PAGE_RSP )

#define LL_GMM_CLEAR_DATA_TYPE_NO_SM_SIGNALLING  ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_GMM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_TRIG )

#define LL_GMM_CLEAR_DATA_TYPE_SIGNALLING        ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_GMM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_SM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_TRIG )

#define LL_GMM_CLEAR_DATA_TYPE_ALL               ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_GMM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_SM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_TRIG \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_USER \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_SMS )

/* GMM通知LL恢复数据的类型 */
enum LL_GMM_RESUME_TYPE_ENUM
{
    LL_GMM_RESUME_TYPE_ALL              = 0,
    LL_GMM_RESUME_TYPE_SIGNAL           = 1,
    LL_GMM_RESUME_TYPE_BUTT
};
typedef VOS_UINT32    LL_GMM_RESUME_TYPE_ENUM_UINT32;


/******************************************************************************
  5 全局变量声明
******************************************************************************/


/******************************************************************************
  6 消息头定义
******************************************************************************/


/******************************************************************************
  7 消息定义
******************************************************************************/


/******************************************************************************
  8 结构定义
******************************************************************************/
#pragma pack(4)

/*===========================================================================*/
/*GMM和LLME的接口原语定义*/
/*===========================================================================*/
typedef struct
{
    /*TLLI all 1's表示无效值*/
    VOS_UINT32  ulTlliOld;
    VOS_UINT32  ulTlliNew;

    /* 用于表示指配命令具体功能的掩码
       b000 0000 : 当b等于1时表示指配TLLI ;0表示不指配TLLI
       0b00 0000 : 当b等于1时表示指配加密算法KC ; 0表示不指配加密算法KC
#define LL_ASSIGN_REQ_MASK_TLLI     0x80
#define LL_ASSIGN_REQ_MASK_CiphAlg  0x40 */
    VOS_UINT8   ucMask;

    /*64 bits Kc parameter received from GMM*/
    VOS_UINT8   aucKc[8];

    /* 128 bits RAND parameter received from GMM */
    VOS_UINT8   ucRand[16];
/*
Type of ciphering algorithm
bits
3   2   1
0   0   0       ciphering not used
0   0   1       GPRS Encryption Algorithm GEA/1
0   1   0       GPRS Encryption Algorithm GEA/2
0   1   1       GPRS Encryption Algorithm GEA/3
1   0   0       GPRS Encryption Algorithm GEA/4
1   0   1       GPRS Encryption Algorithm GEA/5
1   1   0       GPRS Encryption Algorithm GEA/6
1   1   1       GPRS Encryption Algorithm GEA/7

#define LL_GEA0     0       ciphering not used
#define LL_GEA1     1
#define LL_GEA2     2
#define LL_GEA3     3
#define LL_GEA4     4
#define LL_GEA5     5
#define LL_GEA6     6
#define LL_GEA7     7 */
    VOS_UINT8                           ucCiphAlg;      /* 加密算法，目前支持GEA1、GEA2、GEA3 */

    LL_GMM_CIPH_FLG_ENUM_UINT8          enCiphStartFlg; /* 加密是否启动标志 */

    VOS_UINT8                           ucRsv;          /* 四字节补齐 */
} LL_GMM_ASSIGN_REQ_ST;

typedef struct
{
    VOS_UINT32  ulTlli;
/*
#define LL_GMM_TRIG_CAUSE_PAG_RSP               0   寻呼响应
#define LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY 1   小区更新但SGSN未指示Cell Notification
#define LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY    2   小区更新且SGSN指示Cell Notification */
    VOS_UINT8   ucCause;                            /* GMM触发的原因 */

    VOS_UINT8   ucRsv;                              /*四字节补齐*/
    VOS_UINT16  usRsv;                              /*四字节补齐*/
} LL_GMM_TRIGGER_REQ_ST;

typedef struct
{
    VOS_UINT32 ulTlli;
/*
#define LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP       1     unsolicited UA response
#define LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP       2     unsolicited DM response
#define LL_GMM_STA_CAUSE_RETRANS_SABM_N200        3     SABM命令重发N200次
#define LL_GMM_STA_CAUSE_RETRANS_DISC_N200        4     DISC命令重发N200次
#define LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200     5     XID命令重复N200次
#define LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200   6     查询对方是否处于忙状态超过N200次
#define LL_GMM_STA_CAUSE_LLC_INIT_RE_EST          7     LLC发起ABM重建
#define LL_GMM_STA_CAUSE_PEER_INIT_RE_EST         8     对端发起ABM重建
#define LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION      9     检测到帧拒绝条件
#define LL_GMM_STA_CAUSE_RECV_FRMR_RSP            10    接收到FRMR响应
#define LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL          11    TLLI指配失败
#define LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL         12    LLC帧发送触发请求失败
#define LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL         13    LLC挂起失败
#define LL_GMM_STA_CAUSE_GMM_RESUME_FAIL          14    LLC恢复失败 */

    VOS_UINT16  usCause;                                /* 报告状态指示的原因 */

    VOS_UINT16  usRsv;                                  /*四字节补齐*/
} LL_GMM_STATUS_IND_ST;


/*===========================================================================*/
/*LLE对GMM/SMS/非确认数据传输接口原语定义*/
/*===========================================================================*/
typedef struct
{
    VOS_UINT32              ulTlli;         /* 目前LLC并不使用NAS数据中带的TLLI*/
    VOS_UINT8               ucRadioPri;     /* 无线优先级别 */
    VOS_UINT8               ucCiphInd;      /* 是否加密的指示，0:不加密 1:加密*/
    PS_BOOL_ENUM_UINT8      enNeedCnf;
    VOS_UINT8               ucRsv;
    VOS_UINT16              usMui;          /* LLC与MM交互使用的SDU的编号 */
    VOS_UINT16              usPduLen;       /* 数据长度 */
    VOS_UINT8               aucPdu[4];      /* GMM和SMS的数据*/
} LL_NAS_UNITDATA_REQ_ST;

typedef struct
{
    VOS_UINT32  ulTlli;
    VOS_UINT8   ucCiphInd;  /* 是否加密的指示，0:不加密 1:加密*/
    VOS_UINT8   ucRsv;      /* 四字节补齐*/
    VOS_UINT16  usPduLen;
    VOS_UINT8   aucPdu[4];
} LL_NAS_UNITDATA_IND_ST;

/*===========================================================================*/
/*LLC--GMM/SMS消息定义*/
/*===========================================================================*/

typedef struct
{
    VOS_MSG_HEADER

    /*消息类型*/
    VOS_UINT16 usMsgType;

    /*子进程，这里填SAPI*/
    VOS_UINT16 usTransId;

    /*消息体结构*/
    LL_GMM_ASSIGN_REQ_ST  stLlGmmAssReq;
} LL_GMM_ASSIGN_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*消息类型*/
    VOS_UINT16 usMsgType;

    /*子进程，这里填SAPI*/
    VOS_UINT16 usTransId;

    /*消息体结构*/
    LL_GMM_TRIGGER_REQ_ST stLlGmmTrigReq;
} LL_GMM_TRIGGER_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*消息类型*/
    VOS_UINT16  usMsgType;

    /*子进程，这里填SAPI*/
    VOS_UINT16  usTransId;

    /* 保留域 */
    VOS_UINT8   aucReserve[4];
} LL_GMM_SUSPEND_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*消息类型*/
    VOS_UINT16 usMsgType;

    /*子进程，这里填SAPI*/
    VOS_UINT16 usTransId;

    /* 恢复数据传送类型:信令数据，用户数据 */
    LL_GMM_RESUME_TYPE_ENUM_UINT32  ulResumeType;
} LL_GMM_RESUME_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER                /* _H2ASN_Skip */
    VOS_UINT32  ulMsgName;        /* message name *//* _H2ASN_Skip */
    LL_GMM_STATUS_IND_ST    stLlGmmStatusInd;
} LL_GMM_STATUS_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*消息类型*/
    VOS_UINT16 usMsgType;

    /*子进程，这里填SAPI*/
    VOS_UINT16 usTransId;

    /*消息体结构*/
    LL_NAS_UNITDATA_REQ_ST  stUnitDataReq;
} LL_NAS_UNITDATA_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*消息类型*/
    VOS_UINT32 ulMsgName;

    /*消息体结构*/
    VOS_UINT16              usMui;          /* LLC与MM交互使用的SDU的编号 */

    VOS_UINT8               aucRsv[2];
} LL_NAS_UNITDATA_CNF_MSG;

typedef struct
{
    VOS_MSG_HEADER                /* _H2ASN_Skip */
    VOS_UINT32  ulMsgName;        /* message name *//* _H2ASN_Skip */
    LL_NAS_UNITDATA_IND_ST  stUnitDataInd;
} LL_NAS_UNITDATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    /*消息类型*/
    VOS_UINT16 usMsgType;

    /*子进程，这里填SAPI*/
    VOS_UINT16 usTransId;

    /*消息体结构*/
    LL_NAS_UNITDATA_IND_ST  stUnitDataInd;
} LL_SMS_UNITDATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER                /* _H2ASN_Skip */
    VOS_UINT32  ulMsgName;        /* message name *//* _H2ASN_Skip */
} LL_DATA_INFORM_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*消息类型*/
    VOS_UINT16                          usMsgType;

    LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8   enClearDataType;

    /*子进程，这里填SAPI*/
    VOS_UINT8                           ucRsv;
} LL_GMM_ABORT_REQ_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/******************************************************************************
  8 UNION定义
******************************************************************************/


/******************************************************************************
  9 OTHERS定义
******************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /*LLInterface.h*/

