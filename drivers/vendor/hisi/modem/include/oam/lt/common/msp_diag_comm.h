


#ifndef __MSP_DIAG_COMM_H__
#define __MSP_DIAG_COMM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "vos.h"
#include "mdrv.h"

/**************************************************************************
  宏定义
**************************************************************************/

/*最好PS将MODID 和DIAG_AIR_MSG_LOG_ID的地方都替换成DIAG_ID*/
#define DIAG_ID(module_id, log_type)   (VOS_UINT32)(module_id | (log_type << 12))

#define DIAG_AIR_MSG_LOG_ID(module_id, is_up_link)  DIAG_ID(module_id, is_up_link) /*module_id对应PID*/

#define DIAG_GEN_LOG_MODULE(modemid, modetype, level)  \
               (((VOS_UINT32)(modemid & 0xff) << 24)  \
              | ((VOS_UINT32)(modetype & 0xf) << 16)  \
              | ((VOS_UINT32)(level    & 0xf ) << 12))

#define DIAG_GEN_MODULE(modemid, modetype)  \
               (((VOS_UINT32)(modemid & 0xff) << 24)  \
              | ((VOS_UINT32)(modetype & 0xf) << 16))


#define DIAG_GEN_MODULE_EX(modemid, modetype, groupid)  \
                   (((VOS_UINT32)(modemid & 0xff) << 24)  \
                  | ((VOS_UINT32)(modetype & 0xf) << 16) \
                  | ((VOS_UINT32)(groupid  & 0xf)  << 8))

#define DIAG_GEN_LOG_ID(filenum, linenum)   \
                ((((VOS_UINT32)(filenum & 0XFFFF)) << 16)   \
                | ((VOS_UINT32)(linenum & 0XFFFF)))

/*is_up_link取值*/
#define OS_MSG_UL                (0x01)/* 表示上行消息*/
#define OS_MSG_DL                (0x02)/* 表示下行消息*/


#define DIAG_SIDE_UE             (0x1)  /* 表示UE接收的空口消息：NET-->UE*/
#define DIAG_SIDE_NET            (0x2)  /* 表示NET接收的空口消息：UE-->NET*/


/* 事件信息打印级别定义*/
#define DIAG_LOG_TYPE_INFO            0x00000008UL
#define DIAG_LOG_TYPE_AUDIT_FAILURE   0x00000004UL
#define DIAG_LOG_TYPE_AUDIT_SUCCESS   0x00000002UL
#define DIAG_LOG_TYPE_ERROR           0x00000001UL
#define DIAG_LOG_TYPE_WARNING         0x00000010UL

/*diag fw发给AGENT模块的请求，以及相应的回复消息*/
/*原本放在diag_message_id.h中,*/
#define ID_MSG_DIAG_HSO_DISCONN_IND                 (0x00010004)

/*diag AGENT发给PS模块的HSO回放请求*/
#define ID_MSG_DIAG_CMD_REPLAY_TO_PS    			(0x00010100)

/* 对外消息的范围与 DIAG_MESSAGE_TYPE_U32 拉通 */

/* 2000 - 2fff是与PS的消息范围 */

/* 由于TTF的层间消息上报涉及内存拷贝，所以把开关通知TTF，TTF自身检查开关未打开时，不执行内存拷贝，可提高CPU处理效率 */
#define     DIAG_TTF_TRACECFG_REQ                   (0x00002201)    /* 向TTF配置层间消息开关 */
#define     DIAG_TTF_DISCONN_REQ                    (0x00002203)    /* 通知TTF工具已断开 */


/* 3000 - 3fff是与PHY的消息范围 */
#define     DIAG_GUPHY_RELEASE_REQ                  (0x00003201)    /* 改为API方式通知，此消息废除 */


/* c000 - cfff是与HIFI的消息范围 */
#define     DIAG_HIFI_RELEASE_REQ                   (0x0000c001)


/*****************************************************************************
  4 Enum
*****************************************************************************/

/* ==============服务层头结构枚举值定义==================================== */

/* DIAG_SERVICE_HEAD_STRU:ssid4b */
enum DIAG_SSID_TYPE
{
    DIAG_SSID_APP_CPU   = 0x1,
    DIAG_SSID_MODEM_CPU,
    DIAG_SSID_LTE_DSP,
    DIAG_SSID_LTE_BBP,
    DIAG_SSID_GU_DSP,
    DIAG_SSID_HIFI,
    DIAG_SSID_TDS_DSP,
    DIAG_SSID_TDS_BBP,
    DIAG_SSID_MCU,
    DIAG_SSID_GPU,
    DIAG_SSID_GU_BBP,
    DIAG_SSID_IOM3,
    DIAG_SSID_ISP,
    DIAG_SSID_X_DSP,
    DIAG_SSID_BUTT
};
typedef VOS_UINT32 DIAG_SSID_TYPE_U32;


/* DIAG_SERVICE_HEAD_STRU:sessionid8b */
#define MSP_SERVICE_SESSION_ID        (0x1) /* 标识Service与Client之间的连接,固定为1*/

/* DIAG_SERVICE_HEAD_STRU:mt2b */
enum DIAG_MSGTYPE_TYPE
{
    DIAG_MT_RSV   = 0x0,
    DIAG_MT_REQ   = 0x1,
    DIAG_MT_CNF   = 0x2,
    DIAG_MT_IND   = 0x3
};
typedef VOS_UINT32 DIAG_DIRECTION_TYPE_U32;

/* ======================================================================== */


/* ==============消息层头结构枚举值定义==================================== */

/* MSP_DIAG_STID_STRU:pri4b */
enum DIAG_MESSAGE_TYPE
{
    DIAG_MSG_TYPE_RSV   = 0x0,
    DIAG_MSG_TYPE_MSP   = 0x1,
    DIAG_MSG_TYPE_PS    = 0x2,
    DIAG_MSG_TYPE_PHY   = 0x3,
    DIAG_MSG_TYPE_BBP   = 0x4,
    DIAG_MSG_TYPE_HSO   = 0x5,
    DIAG_MSG_TYPE_BSP   = 0x9,
    DIAG_MSG_TYPE_ISP   = 0xa,
    DIAG_MSG_TYPE_AUDIO = 0xc,
    DIAG_MSG_TYPE_BUTT
};
typedef VOS_UINT32 DIAG_MESSAGE_TYPE_U32;

/* MSP_DIAG_STID_STRU:mode4b */
enum DIAG_MODE_TYPE
{
    DIAG_MODE_LTE  = 0x0,
    DIAG_MODE_TDS  = 0x1,
    DIAG_MODE_GSM  = 0x2,
    DIAG_MODE_UMTS = 0x3,
    DIAG_MODE_1X   = 0x4,
    DIAG_MODE_HRPD = 0x5,
    DIAG_MODE_COMM = 0xf
};
typedef VOS_UINT32 DIAG_MODE_TYPE_U32;

/* MSP_DIAG_STID_STRU:pri4b */
enum DIAG_MSG_SUB_TYPE_TYPE
{
    DIAG_MSG_CMD        = 0x0,
    DIAG_MSG_PS_AIR     = 0x1,
    DIAG_MSG_PS_LAYER   = 0x2,
    DIAG_MSG_PS_PRINT   = 0x3,
    DIAG_MSG_PS_EVENT   = 0x4,
    DIAG_MSG_PS_USER    = 0x5,
    DIAG_MSG_PS_VOLTE   = 0x6,
    DIAG_MSG_PS_STRUCT  = 0x7,
    DIAG_MSG_PS_DOT     = 0x8,
    DIAG_MSG_DSP_PRINT  = 0x9,
    DIAG_MSG_RAE_CNF    = 0xa,
    DIAG_MSG_RAE_IND    = 0xb,
    DIAG_MSG_STAT       = 0x1f
};
typedef VOS_UINT32 DIAG_MSG_SUB_TYPE_U32;


enum DIAG_MODEM_ID
{
    DIAG_MODEM_0 = 0x0,
    DIAG_MODEM_1 = 0x1,
    DIAG_MODEM_2 = 0x2
};
typedef unsigned int DIAG_MODEM_ID_U32;


/* DIAG_SERVICE_HEAD_STRU:sid8b */
enum DIAG_SID_TYPE
{
    MSP_SID_DEFAULT   = 0x0,
    MSP_SID_AT_SERVICE,
    MSP_SID_DIAG_SERVICE,
    MSP_SID_DATA_SERVICE,
    MSP_SID_NV_SERVICE,
    MSP_SID_USIM_SERVICE,
    MSP_SID_DM_SERVICE,
    MSP_SID_CBT_SERVICE,
    MSP_SID_BUTT
};

typedef unsigned int MSP_SID_TYPE_U32;

typedef enum
{
    PS_LOG_LEVEL_OFF  = 0,
    PS_LOG_LEVEL_ERROR,
    PS_LOG_LEVEL_WARNING,
    PS_LOG_LEVEL_NORMAL,
    PS_LOG_LEVEL_INFO,
    PS_LOG_LEVEL_BUTT
}PS_LOG_LEVEL_EN;

/**************************************************************************
  5 结构定义
**************************************************************************/

/* ==============帧结构描述================================================ */

/* 描述 :一级头: service头 */
typedef struct
{
    VOS_UINT32    sid8b       :8;
    VOS_UINT32    mdmid3b     :3;
    VOS_UINT32    rsv1b       :1;
    VOS_UINT32    ssid4b      :4;
    VOS_UINT32    sessionid8b :8;
    VOS_UINT32    mt2b        :2;
    VOS_UINT32    index4b     :4;
    VOS_UINT32    eof1b       :1;
    VOS_UINT32    ff1b        :1;

    VOS_UINT32    ulMsgTransId;
    VOS_UINT8     aucTimeStamp[8];
}DIAG_SERVICE_HEAD_STRU;


/* 描述 :二级头: DIAG消息头 */
typedef struct
{
    VOS_UINT32    cmdid19b:19;
    VOS_UINT32    sec5b   :5;
    VOS_UINT32    mode4b  :4;
    VOS_UINT32    pri4b   :4;
} MSP_DIAG_STID_STRU;

typedef struct
{
    union
    {
        VOS_UINT32          ulID;           /* 结构化ID */
        MSP_DIAG_STID_STRU  stID;
    };

    VOS_UINT32          ulDataSize;     /* ucData的长度 */
    VOS_UINT8           aucData[0];
}DIAG_MSG_INFO_STRU;

/* 描述 :三级头: 工具软件信息头，用于REQ/CNF消息 */
typedef struct
{
    VOS_UINT32 ulAuid;         /* 原AUID*/
    VOS_UINT32 ulSn;           /* HSO分发，插件命令管理*/
    VOS_UINT8  ucData[0];      /* 参数的数据*/
} MSP_DIAG_DATA_REQ_STRU;

typedef MSP_DIAG_DATA_REQ_STRU MSP_DIAG_DATA_CNF_STRU;


/* 描述 :整体帧结构 */
typedef struct
{
    DIAG_SERVICE_HEAD_STRU      stService;

    union
    {
        VOS_UINT32          ulCmdId;           /* 结构化ID */
        MSP_DIAG_STID_STRU  stID;
    };

    VOS_UINT32                  ulMsgLen;
#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT8                   aucData[4];
#else
    VOS_UINT8                   aucData[0];
#endif

}DIAG_FRAME_INFO_STRU;


/* 诊断消息层为上层提供的参数结构 */
typedef struct
{
    DIAG_SSID_TYPE_U32          ulSSId;         /* 数据产生的CPU ID */
    DIAG_MESSAGE_TYPE_U32       ulMsgType;      /* 所属组件 */
    DIAG_MODE_TYPE_U32          ulMode;         /* 模式 */
    DIAG_MSG_SUB_TYPE_U32       ulSubType;      /* 子类型，DIAG_MSG_SUB_TYPE_U32 */
    DIAG_DIRECTION_TYPE_U32     ulDirection;    /* 上报消息的方向 */
    VOS_UINT32                  ulModemid;
    VOS_UINT32                  ulMsgId;        /* 低16位有效 */
    VOS_UINT32                  ulTransId;      /* TransId */
} MSP_DIAG_CNF_INFO_STRU;

/* ======================================================================== */


typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulMessageID;  /* Specify the message id.*/
    VOS_UINT32 ulSideId;     /* 空口消息的方向*/
    VOS_UINT32 ulDestMod;    /* 目的模块*/
    VOS_UINT32 ulDataSize;   /* the data size in bytes.*/
    VOS_VOID* pData;      /* Pointer to the data buffer.*/
} DIAG_AIR_MSG_LOG_STRU;

typedef DIAG_AIR_MSG_LOG_STRU DIAG_LAYER_MSG_STRU;

typedef struct
{
    VOS_UINT32 ulMessageID;    /* Specify the message id.*/
    VOS_UINT32 ulDataSize;     /* the data size in bytes.*/
    VOS_VOID* pData;        /* Pointer to the data buffer.*/
} DIAG_USERPLANE_MSG_STRU;

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
/* 发送给MSP_PID_DIAG_APP_AGENT的投票请求消息结构体 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgId;
    SOCP_VOTE_ID_ENUM_U32   ulVoteId;    /* 投票组件 */
    SOCP_VOTE_TYPE_ENUM_U32 ulVoteType;  /* 投票类型 */
}DIAG_MSG_SOCP_VOTE_REQ_STRU;

/* 反对票消息回复 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgId;
    SOCP_VOTE_ID_ENUM_U32   ulVoteId;    /* 投票组件 */
    SOCP_VOTE_TYPE_ENUM_U32 ulVoteType;  /* 投票类型 */
    VOS_UINT32              ulVoteRst;   /* 投票结果，0-成功, 0xFFFFFFFF-失败 */
}DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU;
#endif


/* service层为上层提供的获取buffer的返回结构 */
typedef struct
{
    DIAG_SERVICE_HEAD_STRU      *pHeadService;
    DIAG_MSG_INFO_STRU          *pHeadMessage;
    VOS_VOID                    *pData;
    VOS_UINT32                  ulSize;         /* 数据长度 */
    VOS_UINT32                  ulLength;       /* 包含包头的实际长度 */
}DIAG_SERVICE_REPORT_STRU;



/*****************************************************************************
描述 : 与TTF间的层间消息配置的参数结构(为避免字节对齐问题，TTF必须引用此结构)
MSGID:DIAG_TTF_LAYERCFG_REQ
REQ : DIAG_TTF_TRACECFG_REQ_STRU(此消息不需要回复)
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgId;

    VOS_UINT8                   aucSrcPid[VOS_PID_BUTT-VOS_PID_DOPRAEND];
    VOS_UINT8                   aucDstPid[VOS_PID_BUTT-VOS_PID_DOPRAEND];
}DIAG_TTF_TRACECFG_REQ_STRU;


/*****************************************************************************
枚举名    : OM_AT_MSG_ENUM
枚举说明  : AT给OM发送的请求消息类型

  1.日    期   : 2012年4月4日
    作    者   : h59254
    修改内容   : V7R1C51 锁网锁卡项目新增
*****************************************************************************/
enum OM_AT_MSG_ENUM
{
    AT_OM_PORT_SWITCH           = 0,    /* OM口切换请求，在USB和HSIC之间切换 */
    AT_OM_HSIC_PORT_CONNECT,            /* OM将OM口与HSIC关联上 */
    AT_OM_HSIC_PORT_DISCONNECT,         /* OM将OM口与HSIC取消关联 */
    AT_OM_MSG_BUTT
};
typedef VOS_UINT32 OM_AT_MSG_ENUM_UINT32;

/*****************************************************************************
枚举名    : OM_PORT_SWITCH_MODE_ENUM
枚举说明  : USB SWITCH切换类型

  1.日    期   : 2012年4月4日
    作    者   : h59254
    修改内容   : V7R1C51 可维可测项目新增
*****************************************************************************/
enum OM_PORT_SWITCH_MODE_ENUM
{
    OM_PORT_SWITCH_MODEM2AP     = USB_SWITCH_OFF,
    OM_PORT_SWITCH_AP2MODEM     = USB_SWITCH_ON,
    OM_PORT_SWITCH_BUTT
};
typedef VOS_UINT32 OM_PORT_SWITCH_MODE_ENUM_UINT32;

/*****************************************************************************
结构名    : OM_PORT_SWITCH_MSG_STRU
结构说明  : AP+MODEM形态产品AP-Modem USB切换消息结构

  1.日    期   : 2012年4月10日
    作    者   : h59254
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER
   OM_AT_MSG_ENUM_UINT32            ulMsgName;      /*切换消息名*/
   OM_PORT_SWITCH_MODE_ENUM_UINT32  ulSwitchMode;   /*切换模式，从AP到Modem或Modem到AP*/
}OM_PORT_SWITCH_MSG_STRU;

/*****************************************************************************
结构名    : OM_HSIC_CONNECT_MSG_STRU
结构说明  : AP+MODEM形态产品AT要求关联OM和HSIC的消息结构

  1.日    期   : 2012年4月10日
    作    者   : h59254
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER
   OM_AT_MSG_ENUM_UINT32            ulMsgName;      /*切换消息名*/
}OM_HSIC_CONNECT_MSG_STRU;

/**************************************************************************
  函数声明
**************************************************************************/


/* ==============主动上报接口参数========================================== */

typedef struct
{
    VOS_UINT32        ulModule;		/* DIAG_GEN_MODULE*/
    VOS_UINT32        ulPid;
    VOS_UINT32        ulEventId;		/* 事件ID */
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
}DIAG_EVENT_IND_STRU;

typedef struct
{
    VOS_UINT32        ulModule;       /* DIAG_GEN_MODULE*/
    VOS_UINT32        ulPid;
    VOS_UINT32        ulMsgId;
    VOS_UINT32        ulDirection;
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
}DIAG_AIR_IND_STRU;

typedef struct
{
    VOS_UINT32        ulModule;       /* DIAG_GEN_MODULE*/
    VOS_UINT32        ulPid;
    VOS_UINT32        ulMsgId;
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
}DIAG_USER_IND_STRU;


typedef struct
{
    VOS_UINT32        ulId;
    VOS_UINT32        ulMessageID;
    VOS_UINT32        ulSideId;
    VOS_UINT32        ulDestMod;
    VOS_UINT32        ulDataSize;
    VOS_VOID          *pData;
} DIAG_VOLTE_LOG_STRU;

typedef struct
{
    VOS_UINT32        ulModule;
    VOS_UINT32        ulPid;
    VOS_UINT32        ulMsgId;
    VOS_UINT32        ulReserve;
    VOS_UINT32        ulLength;
    VOS_VOID          *pData;
} DIAG_TRANS_IND_STRU;

/* 层间消息过滤接口，入参为标准的OSA消息格式，返回值为是否过滤: 0-不过滤,上报; 其他-过滤,不上报 */
typedef VOS_UINT32 (*DIAG_TraceFilterFunc)(const VOS_VOID *pMsg);


/*****************************************************************************
 Function Name   : DIAG_TraceFilterFuncReg
 Description     : 层间消息过滤注册接口(此接口不支持重复注册，多次注册返还失败)
 Input           : 过滤处理函数
 Output          : None
 Return          : 返回值为注册结果: 0-注册成功；其他-注册失败

 History         :
    1.c64416      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceFilterFuncReg(DIAG_TraceFilterFunc pFun);

/* 层间消息匹配接口，入参和返回值为标准的OSA消息格式 */
typedef VOS_VOID* (*DIAG_TraceMatchFunc)(VOS_VOID *pMsg);

/*****************************************************************************
 Function Name   : DIAG_TraceMatchFuncReg
 Description     : 层间消息过滤注册接口(此接口不支持重复注册，多次注册返还失败)
 Input           : 过滤处理函数
 Output          : None
 Return          : 返回值为注册结果: 0-注册成功；其他-注册失败

 History         :
    1.c64416      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceMatchFuncReg(DIAG_TraceMatchFunc pFun);


/*****************************************************************************
 函 数 名  : DIAG_TransReport
 功能描述  : 结构化数据上报接口(替换原来的DIAG_ReportCommand)
 输入参数  : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_TRANS_IND_STRU->ulMsgId(透传命令ID)
             DIAG_TRANS_IND_STRU->ulLength(透传信息的长度)
             DIAG_TRANS_IND_STRU->pData(透传信息)
*****************************************************************************/
VOS_UINT32 DIAG_TransReport(DIAG_TRANS_IND_STRU *pstData);

/*****************************************************************************
 函 数 名  : DIAG_TransReport_Ex
 功能描述  : 结构化数据上报的扩展接口(相比DIAG_TransReport，新增了11-8bits 组件信息)
 输入参数  : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-8:groupid )
 输入参数  : DIAG_TRANS_IND_STRU->ulPid(模块的PID)
             DIAG_TRANS_IND_STRU->ulMsgId(透传命令ID)
             DIAG_TRANS_IND_STRU->ulLength(透传信息的长度)
             DIAG_TRANS_IND_STRU->pData(透传信息)
*****************************************************************************/
VOS_UINT32 DIAG_TransReport_Ex(DIAG_TRANS_IND_STRU *pstData);

/*****************************************************************************
 函 数 名  : DIAG_LogReport
 功能描述  : 打印上报接口
 输入参数  : ulModuleId( 31-24:modemid,23-16:modeid,15-12:level )
             ulPid( PID )
             pcFileName(上报时会把文件路径删除，只保留文件名)
             ulLineNum(行号)
             pszFmt(可变参数)
*****************************************************************************/
VOS_UINT32 DIAG_LogReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid, VOS_CHAR *cFileName, VOS_UINT32 ulLineNum, VOS_CHAR* pszFmt, ...);


#define LTE_DIAG_PRINTF_PARAM_MAX_NUM       (6)
/******************************************************************************
函数名称: DIAG_LogIdReport
功能描述: 打印点类型的打印接口函数
参数说明:
            ulModuleId[in]  : ( 31-24:modemid,23-16:modeid,15-12:level )
            ulPid[in]       : PID
            ulLogId[in]     : 由文件号和行号根据DIAG_LOG_ID生成
            amount[in]      : 可变参数个数（不包括ulModuleId/ulLevel/ulLogId/amout）
            ...             : 可变参数
调用约束:
            1. 绝对禁止对此函数进行二次封装，只能转定义
            2. 支持可变的参数个数，但必须在调用时由参数amount指定参数个数
            3. 可变参数只支持int类型
            4. 目前版本中支持的最大参数个数是6个，超过的参数默认丢弃
******************************************************************************/
VOS_INT32 DIAG_LogIdReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid,
                        VOS_UINT32 ulLogId, VOS_UINT32 amount, ...);

/*****************************************************************************
 函 数 名  : DIAG_EventReport
 功能描述  : 事件上报接口，给PS使用(替换原来的DIAG_ReportEventLog)
 输入参数  : DIAG_EVENT_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_EVENT_IND_STRU->ulEventId(event ID)
             DIAG_EVENT_IND_STRU->ulLength(event的长度)
             DIAG_EVENT_IND_STRU->pData(event信息)
*****************************************************************************/
VOS_UINT32 DIAG_EventReport(DIAG_EVENT_IND_STRU *pstEvent);

/*****************************************************************************
 函 数 名  : DIAG_AirMsgReport
 功能描述  : 空口消息上报接口，给PS使用(替换原来的DIAG_ReportAirMessageLog)
 输入参数  : DIAG_AIR_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_AIR_IND_STRU->ulMsgId(空口消息ID)
             DIAG_AIR_IND_STRU->ulDirection(空口消息的方向)
             DIAG_AIR_IND_STRU->ulLength(空口消息的长度)
             DIAG_AIR_IND_STRU->pData(空口消息信息)
*****************************************************************************/
VOS_UINT32 DIAG_AirMsgReport(DIAG_AIR_IND_STRU *pstAir);


/*****************************************************************************
 函 数 名  : DIAG_TraceReport
 功能描述  : 层间消息上报接口，给PS使用(替换原来的DIAG_ReportLayerMessageLog)
 输入参数  : pMsg(标准的VOS消息体，源模块、目的模块信息从消息体中获取)

*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);  /* lint !e830 */

/*****************************************************************************
 函 数 名  : DIAG_UserPlaneReport
 功能描述  : 用户面上报接口，给PS使用(替换原来的DIAG_ReportUserPlaneMessageLog)
 输入参数  : DIAG_USER_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_USER_IND_STRU->ulMsgId(用户面消息ID)
             DIAG_USER_IND_STRU->ulLength(用户面消息的长度)
             DIAG_USER_IND_STRU->pData(用户面信息)
*****************************************************************************/
VOS_UINT32 DIAG_UserPlaneReport(DIAG_USER_IND_STRU *pstUser);

/*****************************************************************************
 Function Name   : DIAG_ReportVoLTELog
 Description     : 给IMS提供的VOLTE特性信息上报接口
 Input           : DIAG_VoLTE_LOG_STRU* pRptMessage
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.fuxin      2013-12-30  create
*****************************************************************************/
VOS_UINT32 DIAG_ReportVoLTELog(DIAG_VOLTE_LOG_STRU* pRptMessage);

/*****************************************************************************
 Function Name   : DIAG_GetConnState
 Description     : 获取当前工具连接状态
 Return          : 1:connect; 0:disconnect

 History         :
    1.c00326366      2015-6-24  Draft Enact
*****************************************************************************/
VOS_UINT32 DIAG_GetConnState(VOS_VOID);


/*****************************************************************************
  外部接口定义
*****************************************************************************/
extern VOS_UINT32 DIAG_ErrorLog(VOS_CHAR * cFileName,VOS_UINT32 ulFileId, VOS_UINT32 ulLine,
                VOS_UINT32 ulErrNo, VOS_VOID * pBuf, VOS_UINT32 ulLen);

#define MNTN_RecordErrorLog(ulErrNo,pBuf,ulLen) \
    DIAG_ErrorLog(__FILE__,THIS_FILE_ID,__LINE__,ulErrNo,pBuf,ulLen)


/*****************************************************************************
 函 数 名  : Log_GetPrintLevel
 功能描述  : 得到模块Id、子模块Id在打印级别记录表中的索引号
 return    : PS_LOG_LEVEL_EN
 History         :
    1.c00326366      2015-6-24  Draft Enact
*****************************************************************************/
extern VOS_UINT32 Diag_GetLogLevel(VOS_UINT32 ulPid);


#if(VOS_OS_VER == VOS_LINUX)
/*****************************************************************************
 Function Name   : DIAG_LogShowToFile
 Description     : 给AT命令提供的调用接口，保存DIAG的log到文件中
 Input           : bIsSendMsg 是否给A核发送消息保存A核log
 Return          : VOS_VOID

 History         :
    1.c00326366      2015-6-20  Draft Enact
*****************************************************************************/
extern VOS_VOID DIAG_LogShowToFile(VOS_BOOL bIsSendMsg);
#endif

#ifdef __cplusplus
}
#endif
#endif

