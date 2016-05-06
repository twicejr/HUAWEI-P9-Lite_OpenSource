/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : mailbox.h
  版 本 号   : 初稿
  作    者   : c64416
  生成日期   : 2012年12月14日
  最近修改   :
  功能描述   : 邮箱功能头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月14日
    作    者   : c64416
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAILBOX_H__
#define __MAILBOX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include <product_config.h>
#include <mdrv.h>
#include <bsp_external_stub.h>
#include "mailbox_types.h"
#include <mdrv_mailbox.h>
#include <tlphy_errno.h>
#include <bsp_om_enum.h>
#include <mdrv_errno.h>

#pragma pack(4)


#define FEATURE_MAILBOX_CDMA_NOT_USE FEATURE_OFF
/*****************************************************************************
  2 宏定义
*****************************************************************************/


/* 握手流程
PS initial (0) --> DSP start (2) --> DSP end (0xa5a5a5a5)
*/

/* DSP握手地址 */
#define BSP_DSP_INIT_RESULT_ADDR        LPHY_MAILBOX_LOAD_MEMORY_ADDR

/* 设置工作模式(单卡、双卡、RTT、全系统等) */
#define BSP_DSP_WORKING_MODE_ADDR       LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR


/* 握手成功标志 */
#define BSP_TL_SHAKEHAND_CMP            (0xa5a5a5a5)


/* PS邮箱的上下行起始地址和size */
#define MAILBOX_PS_DOWN_ADDR                LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR
#define MAILBOX_PS_UP_ADDR                  LPHY_MAILBOX_LHPA_UP_BASE_ADDR

#define MAILBOX_PS_DOWN_SIZE                LPHY_MAILBOX_LHPA_DOWN_SIZE
#define MAILBOX_PS_UP_SIZE                  LPHY_MAILBOX_LHPA_UP_SIZE


/* OM邮箱的下行起始地址和size */
#define MAILBOX_OM_DOWN_ADDR                LPHY_MAILBOX_OM_DOWN_BASE_ADDR

#define MAILBOX_OM_DOWN_SIZE                LPHY_MAILBOX_OM_DOWN_SIZE


/* 专有邮箱的上下行起始地址 */
#define MAILBOX_SP_UP_ADDR                  LPHY_MAILBOX_LMAC_UP_BASE_ADDR
#define MAILBOX_SP_DOWN_ADDR                LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR

/* 异常重启时由于空间限制，保存10条信息 */
#define MBX_ERROR_MNTN_NUM                  10

/* 可维可测记录信息的条数 */
#define MAILBOX_MNTN_NUMBER                 100

#define MAILBOX_ADDR_OFFSET                 MASTER_TCM_ADDR_OFFSET

#define MAILBOX_WAKEUP_TIMEOUT              10    /* 100ms */

/* 32K时钟的阈值:1ms */
#define MAILBOX_SLICE_THRESHOLD             32

/* 异常重启时，缓冲区中的前512字节预留给PS或DSP */
#define MBX_ERROR_RESERVE_SIZE              512

#define MBX_SYSTEM_ERROR_SIZE               0x1000



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum __MBX_ADDRESSEE_ID_ENUM__
{
    MBX_ADDRESSER_LTE_PHY_RL = 0,
    MBX_ADDRESSER_LTE_PHY_OM,
    MBX_ADDRESSER_LTE_PHY_BT,
    MBX_ADDRESSER_LTE_PHY_CT,
    MBX_ADDRESSER_LTE_PHY_COEX,
    MBX_ADDRESSER_LTE_PHY_HS_DIAG,
    MBX_ADDRESSER_LTE_PHY_RCM,

    MBX_ADDRESSER_TDS_PHY_RL = 16,
    MBX_ADDRESSER_TDS_PHY_OM,
    MBX_ADDRESSER_TDS_PHY_BT,
    MBX_ADDRESSER_TDS_PHY_CT,
    MBX_ADDRESSER_TDS_PHY_HS_DIAG,
    MBX_ADDRESSER_TDS_PHY_RCM,

    MBX_ADDRESSER_1X_PHY_RL = 32,
    MBX_ADDRESSER_1X_PHY_OM,
    MBX_ADDRESSER_1X_PHY_BT,
    MBX_ADDRESSER_1X_PHY_CT,
    MBX_ADDRESSER_1X_PHY_HS_DIAG,

    MBX_ADDRESSER_RTT_SYS_CTRL = 48,
    MBX_ADDRESSER_RTT_AGENT,
    MBX_ADDRESSER_RTT_CBT,
    MBX_ADDRESSER_RTT_HIFI_AGENT,
    
    MBX_ADDRESSER_HRPD_PHY_RL = 64,
    MBX_ADDRESSER_HRPD_PHY_OM,
    MBX_ADDRESSER_HRPD_PHY_BT,
    MBX_ADDRESSER_HRPD_PHY_CT,
    MBX_ADDRESSER_HRPD_PHY_HS_DIAG,

    MBX_ADDRESSEE_BUTT
};

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

typedef struct
{
    u32                     ulMbxChn;           /* 邮箱通道 */
    u32                     ulModule;           /* 模块ID */
    u32                     ulDlAddr;           /* 下行邮箱地址 */
    u32                     ulUlAddr;           /* 上行邮箱地址 */
    BSP_MBX_NOTIFY_FUNC     pFnCallBack;        /* 回调函数 */
    IPC_INT_LEV_E           ulIntNum;           /*ARM -> DSP中断号*/
} MAILBOX_CHANNEL_TABLE_STRU;

extern MAILBOX_CHANNEL_TABLE_STRU g_astMbxChnTbl[EN_MAILBOX_SERVICE_BUTT];


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*lint --e{43}*/ /*PCLINT: aulMsgBuf 43 is inevitable*/
typedef struct
{
    u8*         pucRbufAddr;    /* 环形buffer的起始地址(DSP侧)，ARM侧需要-0x0f000000 */
    u32         ulRbufSize;     /* Ring Buffer 的总长度，字节为单位 */
    u32         ulRbufRdPtr;    /* Ring Buffer 已用空间的首地址,读指针 */
    u32         ulRbufWrPtr;    /* Ring Buffer 空闲空间的首地址,写指针 */
    u32         aulMsgBuf[0];
} MAILBOX_RINGBUFF_STRU;


typedef struct __MAILBOX_MSG_HAED_STRU
{
    u16         usMsgSize;      /* 以字节为单位 */
    u16         usDstMod;
    u8*         pPayload;
}MAILBOX_MSG_HAED_STRU;


typedef struct
{
    BSP_BOOL                bMbxInit;               /* 邮箱是否初始化 */

    osl_sem_id              semDspMutex;
    osl_sem_id              semDspWakeup;
    BSP_BOOL                bDspWakeFlag;           /* 只在邮箱请求唤醒时设置，避免低功耗模块多次唤醒出错 */

    BSP_MBX_NOTIFY_FUNC     pfnSpNotifyProc;        /* 专有邮箱中断上报处理回调函数 */

    BSP_MBX_GET_STATUS_FUNC pfnGetDspStatusProc;    /* 获取DSP睡眠状态回调函数 */
    BSP_MBX_DSP_AWAKE_FUNC  pfnDspForceAwakeProc;   /* 强制唤醒DSP回调函数 */
    BSP_MBX_GET_STATUS_FUNC pfnGetSpMsgProc;        /* 获取专有邮箱是否允许DSP睡眠回调函数 */
    BSP_MBX_RCM_CALLBACK_FUNC pfnRcmNotifyProc;     /*获取通知RCM的回调函数*/

    BSP_BOOL                bIsSubFrameInt;         /* PS邮箱是否是子帧中断方式 */

    u32                     ulMsgLen;               /* PS邮箱中第一条消息长度,0表示为空 */
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    u32                 ulOmMsgLen;                 /* OM邮箱中第一条消息长度,0表示为空 */
#endif

    u32                     *pulAxiAddr;            /* PS邮箱读操作信号量 */
    s32                     lAxiCnt;                /* 记录AXI memory设置的次数，避免多线程操作错误 */
} MAILBOX_MAINCTRL_STRU;


/* 邮箱模块的可维可测信息 */

/* 原语次数相关信息  */
typedef struct
{
    u32     ulComPsIntNum;      /* PS邮箱中断次数 */
    u32     ulSpIntNum;         /* 专有邮箱中断次数 */

    u32     ulPsComReqNum;      /* PS邮箱请求次数 */
    u32     ulPsComPsReqNum;    /* PS邮箱PS写请求次数 */
    u32     ulPsComMspReqNum;   /* PS邮箱MSP写请求次数 */
    u32     ulPsComRcmReqNum;   /* PS邮箱RCM写请求次数*/
    u32     ulPsComRttAgentReqNum; /* PS邮箱RttAgent写请求次数 */
    u32     ulOmComReqNum;      /* OM邮箱写请求次数 */

    u32     ulPsComPsRdNum;     /* PS邮箱PS读取次数 */
    u32     ulPsComPsRdOKNum;   /* PS邮箱PS读取成功次数 */
    u32     ulPsComRcmRdNum;    /* PS邮箱RCM读取次数*/
    u32     ulPsComRcmRdOKNum;  /* PS邮箱RCM读取次数*/
    u32     ulPsComMspRdNum;    /* PS邮箱MSP读取次数 */
    u32     ulPsComMspRdOKNum;  /* PS邮箱MSP读取成功次数 */
    u32     ulPsComRttAgentRdNum;/* PS邮箱RTT AGENT读取次数 */
    u32     ulPsComRttAgentRdOKNum;/* PS邮箱RTT AGENT读取成功次数 */

#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    u32     ulOmComOmRdNum;     /* OM邮箱OM读取次数 */
    u32     ulOmComOmRdOKNum;   /* OM邮箱OM读取成功次数 */
#endif

    u32     ulPsComPsNotifyNum; /* PS邮箱PS回调次数 */
    u32     ulPsComMspNotifyNum;/* PS邮箱MSP回调次数 */
    u32     ulPsComRcmNotifyNum;/* PS邮箱RCM回调次数*/
    u32     ulPsComRttAgentNotifyNum;/* PS邮箱RTT AGENT回调次数 */
} MAILBOX_MNTN_NUMBER_STRU;

typedef struct
{
    u32     ulModId;            /* 写邮箱类型 */
    u32     ulMsgId;            /* 消息ID */
    u32     ulSlice;            /* 时间 */
} MAILBOX_MNTN_MSGINFO_STRU;

/* 写原语时邮箱满时相关信息  */
typedef struct
{
    u32     ulFullNum;          /* 邮箱满的次数 */

    u32     ulPtr;              /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_MSGINFO_STRU   astFullInfo[MAILBOX_MNTN_NUMBER];
} MAILBOX_MNTN_MAILFULL_STRU;

/* 异常信息  */
typedef struct
{
    u8      ucComPsType;        /* PS邮箱内收到的非PS原语、CT/BT类型的消息 */
    u32     ulMulCtBtMsg;       /* PS邮箱内连续收到多条CT/BT类型的消息，记录msgid */

    u32     ulLongestReq;       /* 请求最大时长 */

    u32     ulNInitSlic;        /* 最后一次未初始化时请求的时间戳,记录内存被踩 */
} MAILBOX_MNTN_ABNORMAL_STRU;


/* 最后10条原语请求信息记录 */
typedef struct
{
    u32     ulModId;            /* 写邮箱类型 */
    u32     ulMsgId;            /* 消息ID */
    u32     ulRWPtr;            /* 读写指针，高16位读指针，低16位写指针 */
    u32     ulSliceStart;       /* 发起请求的时间 */
    u32     ulSliceEnd;         /* 写入邮箱的时间 */
} MAILBOX_MNTN_REQ_STRU;

typedef struct
{
    u32     ulPtr;              /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_REQ_STRU astReq[MAILBOX_MNTN_NUMBER];
} MAILBOX_MNTN_REQINFO_STRU;


/* 读取的最后10条原语信息记录 */
typedef struct
{
    u32     ulMsgId;            /* 消息ID */
    u32     ulRWptr;            /* 读写指针，高16位读指针，低16位写指针 */
    u32     ulSlice;            /* 读取时间 */
} MAILBOX_MNTN_CNF_STRU;

typedef struct
{
    u32     ulPsPtr;            /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_CNF_STRU astPsCnf[MAILBOX_MNTN_NUMBER];
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
     u32     ulOmPtr;            /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_CNF_STRU astOmCnf[MAILBOX_MNTN_NUMBER];
#endif
    u32     ulRcmPtr;           /*循环指针，用于循环存储*/
    MAILBOX_MNTN_CNF_STRU astRcmCnf[MAILBOX_MNTN_NUMBER];
    u32     ulCbtPtr;            /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_CNF_STRU astCbtCnf[MAILBOX_MNTN_NUMBER];
    u32     ulRttAgentPtr;       /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_CNF_STRU astRttAgentCnf[MAILBOX_MNTN_NUMBER];
} MAILBOX_MNTN_CNFINFO_STRU;


typedef struct
{
    u32     ulPtr;              /* 循环指针,用于循环存储 */
    u32     ulSlice[MAILBOX_MNTN_NUMBER];   /* slice 记录 */
} MAILBOX_MNTN_INTSLICE_STRU;


typedef struct
{
    u32     ulSrc;              /* 读取者id */
    u32     ulSlice;            /* 读取的发起时间 */
} MAILBOX_MNTN_READ_STRU;

typedef struct
{
    u32     ulPsPtr;            /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_READ_STRU astRead[MAILBOX_MNTN_NUMBER];
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    u32     ulOmPtr;            /* 循环指针,用于循环存储 */
    MAILBOX_MNTN_READ_STRU astOmRead[MAILBOX_MNTN_NUMBER];
#endif


} MAILBOX_MNTN_READINFO_STRU;


typedef struct
{
    u32     ulSlice1;            /* 发起强制唤醒的时间 */
    u32     ulSlice2;            /* 强制唤醒回复的时间 */
    u32     ulSlice3;            /* 唤醒处理的时间 */
} MAILBOX_MNTN_WAKEUP_STRU;

typedef struct
{
    u32     ulPtr;
    MAILBOX_MNTN_WAKEUP_STRU astwakeup[MAILBOX_MNTN_NUMBER];   /* 强制唤醒时间 */
} MAILBOX_MNTN_SLEEP_STRU;

typedef struct
{
    MAILBOX_CALLBACK_TYPE       cbType;                     /*回调类型*/
    BSP_BOOL                    ulWakeup;                   /* 是否由邮箱唤醒 */
    u32                         ulSliceStart;
    u32                         ulSliceEnd;
}MAILBOX_MNTN_CB_STRU;

typedef struct
{
    u32 ulPtr;
    MAILBOX_MNTN_CB_STRU    astCbInfo[MAILBOX_MNTN_NUMBER];
}MAILBOX_MNTN_SLEEPCB_STRU;

typedef struct
{
    BSP_BOOL                        bdbg;
    MAILBOX_MNTN_ABNORMAL_STRU      stAbnormal;         /* 邮箱异常 */
    MAILBOX_MNTN_NUMBER_STRU        stNumber;           /* 原语次数相关信息 */
    MAILBOX_MNTN_MAILFULL_STRU      stMailFull;         /* 邮箱满信息 */
    MAILBOX_MNTN_REQINFO_STRU       stReqInfo;          /* 最后N条原语请求信息记录 */
    MAILBOX_MNTN_CNFINFO_STRU       stCnfInfo;          /* 读取最后N条原语信息记录 */
    MAILBOX_MNTN_INTSLICE_STRU      stIntInfo;          /* 最后N条浮动中断的时间 */
    MAILBOX_MNTN_INTSLICE_STRU      stCallback;         /* 回调协议栈的时间 */
    MAILBOX_MNTN_INTSLICE_STRU      stRcmCallback;      /* 回调RCM的时间*/
    MAILBOX_MNTN_INTSLICE_STRU      stDirectInfo;       /* 直接写计数*/
    MAILBOX_MNTN_INTSLICE_STRU      stRttAgentCallback; /* 回调RTT AGENT的时间 */
    MAILBOX_MNTN_READINFO_STRU      stReadInfo;         /* 发起读取请求的时间 */
    MAILBOX_MNTN_SLEEP_STRU         stSleepInfo;        /* 向低功耗模块发起强制唤醒的信息 */
    MAILBOX_MNTN_SLEEPCB_STRU       stSleepCbInfo;      /* 低功耗模块调用邮箱接口处理信息 */
} MAILBOX_MNTN_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#define Mbx_Printf(fmt,...) \
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MBX,"[BBE16 MailBox]:<%s> "fmt,__FUNCTION__,##__VA_ARGS__)
extern MAILBOX_MNTN_STRU       g_stMbxMntn;
extern MAILBOX_MAINCTRL_STRU   g_stMbxCtrl;

#define Mbx_Trace(pdata,ulLen)                                                              \
    if(g_stMbxMntn.bdbg == TRUE)                                                            \
    {\
        u32 i;\
        Mbx_Printf("<%s> datalen : 0x%x,slice :0x%x\n",__func__,ulLen,bsp_get_slice_value());     \
        for(i=0;i<ulLen;i++)\
        {\
            Mbx_Printf("%02x ",*((char*)pdata+i));\
        }\
        Mbx_Printf("\n");\
    };


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern void Mbx_ComPsIntProc(void);

extern void Mbx_ForbidDspSleep(void);

extern void Mbx_AllowDspSleep(void);

extern s32 Mbx_RbuffWrite(MAILBOX_RINGBUFF_STRU* pHead, MAILBOX_MSG_HAED_STRU* pstMsg);

extern u32 Mbx_NewMsgReadOut(MAILBOX_MSG_HAED_STRU* pMsg,MAILBOX_RINGBUFF_STRU* pMbxHandle);

extern void Mbx_SpIntProc(void);

extern void Mbx_ComPsPreProc(void);

extern void Mbx_BbeIpcProc(void);

extern void Mbx_WrFullProc(MAILBOX_RINGBUFF_STRU* pstAddr, u32 usSize, u32 ulRd, u32 ulWr);

extern void Mbx_SystemError(u32 errcode, u32 ulPara1, u32 ulPara2, u32 ulPara3);

extern void Mbx_DumpSave(u8* pData, u32 ulSize);

extern u32 mbx_IsChnModMatch(u32 ulChn, u32 ulMod);

extern void Mbx_MntnWriteEnd(MAILBOX_RINGBUFF_STRU* pHead, MAILBOX_MSG_HAED_STRU* pstMsg, u32 ulTempPPTR);

extern void Mbx_MntnReadEnd(void* pData, enum __MBX_ADDRESSEE_ID_ENUM__ enMbxType, u32 pRd, u32 pWr);

extern u32 mbx_GetChn(u32 ulMod);

extern u32 BSP_MailBox_IsDspSleep(void);

#pragma pack(0)




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of mailbox.h */

