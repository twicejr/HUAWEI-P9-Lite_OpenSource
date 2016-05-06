



#ifndef __OM_ERRORLOG_H__
#define __OM_ERRORLOG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 商用ERR log 上报相关 */
#define     ID_OM_ERR_LOG_CTRL_IND          (0x9001)
#define     ID_OM_ERR_LOG_REPORT_REQ        (0x9002)
#define     ID_OM_ERR_LOG_REPORT_CNF        (0x9003)

/* 工程模式主动上报相关 */
#define     ID_OM_FTM_CTRL_IND              (0x9004)
#define     ID_OM_FTM_REPROT_IND            (0x9005)

/* 工程模式命令上报相关 */
#define     ID_OM_FTM_REQUIRE_IND           (0x9006)
#define     ID_OM_FTM_REQUIRE_CNF           (0x9007)

/* 平台检测故障主动上报消息名称 */
#define     ID_OM_FAULT_ERR_LOG_IND         (0x9009) /* haojian 提议该处以后可能不止媒体组，还有其他组，所有改名 */

/* 平台检测告警主动上报消息名称 */
#define     ID_OM_ALARM_ERR_LOG_IND         (0x900A)

/* 业务信息收集相关 */
#define     ID_OM_INFO_CLT_REPORT_REQ       (0x9010)
#define     ID_OM_INFO_CLT_REPORT_CNF       (0x9011)

#define     OM_MAX_FAULT_ID                 (40)         /* 故障场景编号数量 */
#define     OM_MAX_MODULE_ID                (32)         /* 最多模块数量 */
#define     OM_PID_NULL                     (0)          /* OM PID为空 */
#define     OM_AP_NO_MSG_SEND               (0)          /* OM上报给AP消息完成 */
#define     OM_AP_SEND_MSG_FINISH           (0)          /* OM上报给AP消息完成 */
#define     OM_ERR_FAULT_ID                 (0xFFFFFFFF) /* 故障场景编号非法值 */

/* Error Log 上报定时器 */
#define OM_ERRLOG_TIMER_LENTH               (5000)

/* Clt INFO timer */
#define OM_CLTINFO_TIMER_LENTH               (5000)

/* Send Log Tool MSG Type*/
#define OM_ERRLOG_SEND_MSG                  (0x0000DDDD)
#define OM_ERRLOG_RCV_MSG                   (0x0000EEEE)
#define OM_APP_ERRLOG_HOOK_IND              (0xBBFF)

#define OM_CLTINFO_CNF_NEED_PROCESS          0
#define OM_CLTINFO_CNF_NOT_NEED_PROCESS      1
#define OM_CLTINFO_INVALID_PID               0x5a5abeef

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum OM_ERR_LOG_MSG_TYPE_ENUM
{
    OM_ERR_LOG_MSG_SET_ERR_REPORT = 0x01, /* 上层触发故障上报 */
    OM_ERR_LOG_MSG_ERR_REPORT_END = 0x02, /* 故障上报结束 */
    OM_ERR_LOG_MSG_ON_OFF         = 0x03, /* 控制上类型开关 */
    OM_ERR_LOG_MSG_ERR_REPORT     = 0x04, /* 故障上报 */
    OM_ERR_LOG_MSG_FTM_REPORT     = 0x05, /* 工程模式主动上报 */
    OM_ERR_LOG_MSG_RESULT         = 0x06, /* 上报Result */
    OM_ERR_LOG_MSG_FTM_REQ        = 0x07, /* 工程模式命令 */
    OM_ERR_LOG_MSG_FTM_CNF        = 0x08, /* 工程模式响应 */

    OM_ERR_LOG_MSG_FAULT_REPORT   = 0x09, /* 平台检测故障主动上报 */

    OM_ERR_LOG_MSG_ALARM_REPORT   = 0x0A, /* 平台检测告警主动上报 */

    OM_ERR_LOG_MSG_INFO_CLT_REQ   = 0x10, /* 信息收集命令 */
    OM_ERR_LOG_MSG_INFO_CLT_CNF   = 0x11, /* 信息收集响应 */
    OM_ERR_LOG_MSG_INFO_CLT_END   = 0x12,

    OM_ERR_LOG_MSG_TYPE_BUTT
};
typedef VOS_UINT32    OM_ERR_LOG_MSG_TYPE_ENUM_UINT32;


enum OM_ERR_LOG_MOUDLE_ID_ENUM
{
    OM_ERR_LOG_MOUDLE_ID_GUNAS  = 0x020001,   /* GU NAS */
    OM_ERR_LOG_MOUDLE_ID_GNAS   = 0x020011,   /* G NAS */
    OM_ERR_LOG_MOUDLE_ID_UNAS   = 0x020021,   /* U NAS */
    OM_ERR_LOG_MOUDLE_ID_GAS    = 0x020002,   /* GAS */
    OM_ERR_LOG_MOUDLE_ID_WAS    = 0x020003,   /* WAS */
    OM_ERR_LOG_MOUDLE_ID_GUL2   = 0x020004,   /* GUL2 */
    OM_ERR_LOG_MOUDLE_ID_GL2    = 0x020014,   /* GL2 */
    OM_ERR_LOG_MOUDLE_ID_UL2    = 0x020024,   /* UL2 */
    OM_ERR_LOG_MOUDLE_ID_GUPHY  = 0x020005,   /* GUPHY */
    OM_ERR_LOG_MOUDLE_ID_GPHY   = 0x020015,   /* GPHY */
    OM_ERR_LOG_MOUDLE_ID_UPHY   = 0x020025,   /* UPHY */
    OM_ERR_LOG_MOUDLE_ID_USIMM  = 0x020006,   /* USIMM */
    OM_ERR_LOG_MOUDLE_ID_DRV_SCI= 0x020007,   /* SCI DRV */
    OM_ERR_LOG_MOUDLE_ID_HIFI   = 0x020008,   /* HIFI */
    OM_ERR_LOG_MOUDLE_ID_RRM    = 0x020009,   /* RRM */
    OM_ERR_LOG_MOUDLE_ID_LMM    = 0x020030,   /* LTE EMM */
    OM_ERR_LOG_MOUDLE_ID_ESM    = 0x020031,   /* LTE ESM */
    OM_ERR_LOG_MOUDLE_ID_LSMS   = 0x020032,   /* LTE SMS(复用GU SMS，不会使用，预留) */
    OM_ERR_LOG_MOUDLE_ID_LPP    = 0x020033,   /* LTE LPP */
    OM_ERR_LOG_MOUDLE_ID_LRRC   = 0x020034,   /* LTE RRC */
    OM_ERR_LOG_MOUDLE_ID_LTEL2  = 0x020035,   /* LTEL2 */
    OM_ERR_LOG_MOUDLE_ID_LPHY   = 0x020036,   /* LTE PHY */

    OM_ERR_LOG_MOUDLE_ID_TDS_MM  = 0x020040,   /* TDS MM */
    OM_ERR_LOG_MOUDLE_ID_TDS_GMM = 0x020041,   /* TDS GMM */
    OM_ERR_LOG_MOUDLE_ID_TDS_CC  = 0x020042,   /* TDS CC */
    OM_ERR_LOG_MOUDLE_ID_TDS_SM  = 0x020043,   /* TDS SM */
    OM_ERR_LOG_MOUDLE_ID_TDS_SMS = 0x020044,   /* TDS SMS(复用GU SMS，不会使用，预留) */
    OM_ERR_LOG_MOUDLE_ID_TDS_LPP = 0x020045,   /* TDS LPP */
    OM_ERR_LOG_MOUDLE_ID_TRRC    = 0x020046,   /* TDS RRC */
    OM_ERR_LOG_MOUDLE_ID_TDSL2   = 0x020047,   /* TDSL2 */
    OM_ERR_LOG_MOUDLE_ID_TDS_PHY = 0x020048,   /* TDS PHY */

    /* 以下模块不具备收发消息功能，需借助COM模块中转 */
    OM_ERR_LOG_MOUDLE_ID_IMS     = 0x020050,   /* IMS */
    OM_ERR_LOG_MOUDLE_ID_IMSA    = 0x020051,   /* IMSA */

    OM_ERR_LOG_MOUDLE_ID_BUTT
};
typedef VOS_UINT32    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32;

enum OM_APP_SWITCH_MSG_ID_ENUM
{
    OM_APP_SWITCH_MSG_ID_ERR_LOG = 0x03000001, /* Error log开关消息 */
    OM_APP_SWITCH_MSG_ID_FTM     = 0x03000002, /* 工程模式开关消息 */
    OM_APP_SWITCH_MSG_ID_BUTT
};

/* 错误码 */
enum OM_APP_SEND_RESULT_ENUM
{
    OM_APP_MSG_OK                   = 0x00,
    OM_APP_VCOM_DEV_INDEX_ERR       = 0x01,
    OM_APP_MSG_LENGTH_ERR           = 0x02,
    OM_APP_MSG_TYPE_ERR             = 0x03,
    OM_APP_SEND_MODEM_ID_ERR        = 0x04,
    OM_APP_OMACPU_ALLOC_MSG_ERR     = 0x05,
    OM_APP_OMACPU_WRITE_NV_ERR      = 0x06,
    OM_APP_OMACPU_READ_NV_ERR       = 0x07,
    OM_APP_MSG_MODULE_ID_ERR        = 0x08,
    OM_APP_SEND_FAULT_ID_ERR        = 0x09,
    OM_APP_NO_FAULT_ID_ERR          = 0x0A,
    OM_APP_REPORT_NOT_FINISH_ERR    = 0x0B,
    OM_APP_ERRLOG_SWITCH_CLOSE_ERR  = 0x0C,
    OM_APP_ERRLOG_START_TIMER_ERR   = 0x0D,
    OM_APP_OMCCPU_ALLOC_MSG_ERR     = 0x0E,

    OM_APP_SEND_RESULT_BUTT
};

/* 开关变量 */
enum OM_APP_SWITCH_ENUM
{
    OM_APP_STATUS_CLOSE = 0x00,
    OM_APP_STATUS_OPEN  = 0x01,

    OM_APP_STATUS_BUTT
};

enum OM_INFO_CLT_SCENE_TYPE_ENUM
{
    OM_INFO_CLT_SCENE_TYPE_FREQ_BAND                        = 0x4001,
    OM_INFO_CLT_SCENE_TYPE_NETWORK_INFO                     = 0x4002,
    OM_INFO_CLT_SCENE_TYPE_BUTT
};
typedef VOS_UINT16    OM_INFO_CLT_SCENE_TYPE_ENUM_UINT16;

/* COMM提供给其他API接口组件的通知注册接口形式 */
typedef  VOS_UINT32 (*pFuncOMGetData)(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, VOS_VOID *pData, VOS_UINT32 ulLen);

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

/* OM error log 消息头 */
typedef struct
{
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulMsgLen;
}OM_ALARM_MSG_HEAD_STRU;

/* Error Log Payload header */
typedef struct
{
    VOS_UINT32                          ulMsgModuleId;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usAlmId;
    VOS_UINT16                          usAlmLevel;
    VOS_UINT16                          usAlmType;
    VOS_UINT32                          usAlmLowSlice;
    VOS_UINT32                          usAlmHighSlice;
    VOS_UINT32                          ulAlmLength;
}OM_ERR_LOG_HEADER_STRU;


/* FTM Payload header */
typedef struct
{
    VOS_UINT32                          ulMsgModuleId;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usProjectId;
    VOS_UINT32                          ulProjectLength;
}OM_FTM_HEADER_STRU;

/* Info Clt Payload header */
typedef struct
{
    VOS_UINT32                          ulMsgModuleId;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usSceneType;
    VOS_UINT32                          ulMsgLength;
}OM_INFO_CLT_HEADER_STRU;

/* Error log和工程模式开关type=0x03 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID; /* Err log:0x03000001 工程模式:0x03000002 */
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucAlmStatus; /* 开关状态 0:close 1:open */
    VOS_UINT8                           ucAlmLevel;  /* 告警级别 */
}APP_OM_CTRL_STATUS_STRU;


/* APP请求Error log上报type=0x01 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usFaultId; /* 故障场景编号 */
}APP_OM_REQ_ERR_LOG_STRU;

/* APP请求Info Clt上报type=0x10 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usInfoID;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgContent[4];
}APP_OM_INFO_CLT_REQ_STRU;

/* APP请求FTM上报type=0x07 App->OM */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usProjectMsgID;  /* 工程模式命令消息 */
    VOS_UINT32                          ulTransID;       /* 命令和响应的会话ID，响应消息按照对应的命令带的ID填写 */
    VOS_UINT32                          ulProjectLength; /* OMPayload部分消息长度 */
    VOS_UINT8                           aucMsgContent[4];
}APP_OM_FTM_REQ_STRU;

/* FTM上报APP type=0x08 OM->App */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usProjectMsgID; /* 工程模式命令消息 */
    VOS_UINT32                          ulTransID;      /* 命令和响应的会话ID，响应消息按照对应的命令带的ID填写 */
    VOS_UINT32                          ulProjectLength;/* 工程模式上报信息长度（MsgContent部分长度,如果长度为0 aucMsgContent内容长度也为0 ） */
    VOS_UINT8                           aucMsgContent[4];
}OM_APP_FTM_CNF_STRU;

/* 工程模式命令上报组件对应PID结构体数组 */
typedef struct
{
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT32                          ulPID;
}APP_OM_FTM_MSG_PID_STRU;

/* Result To App type=0x06  OM -> App */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usRsv;
    VOS_UINT32                          ulStatus; /* result */
}OM_APP_RESULT_CNF_STRU;

/* Error log 上报完成 type=0x02 OM-> APP */
typedef struct
{
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
    VOS_UINT32                          ulMsgModuleID;
    VOS_UINT16                          usModemID;
    VOS_UINT16                          usRev;
    VOS_UINT32                          ulReportStatus; /* result */
    VOS_UINT32                          ulTrigLowSlice; /* 记录触发上报请求时的时间戳 */
    VOS_UINT32                          ulTrigHighSlice;
}OM_APP_REPORT_STATUS_STRU;

/* ERRLOG 上报开关 OM->各组 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucAlmStatus;  /* 打开或者关闭ERRLOG上报功能 0:close 1:open */
    VOS_UINT8                           ucAlmLevel;   /* 上报级别 */
}OM_ERROR_LOG_CTRL_IND_STRU;

/* 下发给各组件的商用ERR log上报请求 OM->各组 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           aucRsv[2];
}OM_ERR_LOG_REPORT_REQ_STRU;

/* 各组件上报的商用ERR log 各组 -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 故障内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    VOS_UINT8                           aucContent[4]; /* 故障内容 */
} OM_ERR_LOG_REPORT_CNF_STRU;

/* 工程模式主动上报开关 OM->各组 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           ucActionFlag; /* 打开或者关闭工程模式上报功能 0:close 1:open*/
    VOS_UINT8                           aucRsv[1];
}OM_FTM_CTRL_IND_STRU;

/* 工程模式命令上报 OM->各组 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           aucContent[2];
}OM_FTM_REQUIRE_STRU;

/* 各组件工程模式主动上报内容 各组件 -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 工程模式上报的内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    VOS_UINT8                           aucContent[4]; /* 工程模式上报的内容 */
}OM_FTM_REPROT_IND_STRU;

/* 各组件故障主动上报内容 各组件 -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* 故障主动上报的内容长度,如果ulRptlen为0,aucContent内容长度也为0 */
    VOS_UINT8                           aucContent[4]; /* 故障主动上报的内容 */
}OM_FAULT_ERR_LOG_IND_STRU;

typedef struct
{
    VOS_UINT32                        ulMcc;
    VOS_UINT32                        ulMnc;
}OM_INFO_CLT_PLMN_ID_STRU;

/* 下发给各组件的信息收集上报请求 OM->各组 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    OM_INFO_CLT_SCENE_TYPE_ENUM_UINT16  enSceneType;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                           aucContent[4];
}OM_INFO_CLT_REPORT_REQ_STRU;

/* 各组件上报的信息收集 各组 -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptLen;      /* 故障主动上报的内容长度,如果ulRptLen为0,aucContent内容长度也为0 */
    VOS_UINT8                           aucContent[4]; /* 故障主动上报的内容 */
} OM_INFO_CLT_REPORT_CNF_STRU;

/* OM收到各组Error Log上报内容 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    OM_ALARM_MSG_HEAD_STRU              stOmHeader;
}OM_RCV_DATA_INFO_STRU;

/* 结构说明  : OM商用Errlog运行上下文 */
typedef struct
{
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    enProjectModule;   /* 设备号 */
    pFuncOMGetData                      pSendUlAtFunc;     /* 各组件注册 接收数据函数 */
}OM_REGISTER_PROJECT_CTX_STRU;

/*****************************************************************************
 结构名    : OM_ERRLOG_TRANS_MSG_STRU
 结构说明  : Error Log 消息勾包结构体
 1.日    期   : 2014年09月19日
   作    者   : d00212987
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucFuncType;
    VOS_UINT8           ucCpuId;
    VOS_UINT16          usLength;
    VOS_UINT32          ulSn;           /*Sequence Number for Trace, Event, OTA msg.*/
    VOS_UINT32          ulTimeStamp;    /*CPU time coming from ARM.*/
    VOS_UINT16          usPrimId;
    VOS_UINT16          usToolId;
    VOS_UINT32          ulDateType;
    VOS_UINT8           aucValue[4];
}OM_ERRLOG_TRANS_MSG_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/******************************************************************************
函数名  ：OM_RegisterGetData
功能描述：OM Ccpu接收各组件上报工程模式数据到APP回调函数注册接口
输入参数：enProjectModule        ：回调组建编号，固定为OM_VOLTE_MOUDLE_PROJECT
          pFuncProjectCallbak    ：回调函数指针
输出参数：NA
返回值  ：VOS_OK/VOS_ERR
修改历史：
1.  日期    ：2014年1月2日
作者    ：
修改内容：新生成函数
说明:
    1、工程模式主动上报开关通知各组件，Data域包含完整的OmHeard和OMPayload
    2、工程模式命令上报消息通知各组件，Data域包含完整的OmHeard和OMPayload
*****************************************************************************/
extern VOS_UINT32 OM_RegisterGetData(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, pFuncOMGetData pFuncProjectCallback);

/******************************************************************************
函数名  ：OM_GetData
功能描述：OM Ccpu接收各组件上报工程模式数据
输入参数：enProjectModule    ：组建编号
          pData              ：发送数据
          ulLen              ：发送数据长度
输出参数：NA
返回值  ：VOS_OK/VOS_ERR
修改历史：
1.  日期    ：2014年1月2日
作者    ：
修改内容：新生成函数
说明：pData从OMHeader的MsgType域开始。相当于调用组件预先申请Header部分，其中Header部分的SN字段由COMM填写
*****************************************************************************/
extern VOS_UINT32 OM_GetData(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, VOS_VOID *pData, VOS_UINT32 ulLen);

extern VOS_VOID OM_AcpuSendVComData(VOS_UINT8 *pData, VOS_UINT32 uslength);
extern VOS_INT  OM_AcpuReadVComData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pucData, VOS_UINT32 ulength);

extern VOS_VOID OM_AcpuErrLogMsgProc(MsgBlock* pMsg);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of omerrorlog.h */


