

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SI_SIM.h
Author      : H59254
Version     : V200R001
Date        : 2008-10-18
Description : SIM卡的头文件
History     :
History     :
1.日    期  : 2008年10月18日
  作    者  : H59254
  修改内容  : Create
************************************************************************/
#ifndef __SI_PIH_H__
#define __SI_PIH_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "siapppih.h"
#include "UsimPsInterface.h"
#include "NVIM_Interface.h"
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "OamXmlComm.h"
#include "usimmvsimauth.h"
#endif  /*(OSA_CPU_CCPU == VOS_OSA_CPU)*/
#include "mdrv.h"
#include "omlist.h"
#include "msp_diag_comm.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define SI_PIH_PIN_CODE_LEN             (8)

#define SI_PIH_PCSC_DATA_CNF            (0xA5)

#define SI_PIH_APDU_HDR_LEN             (USIMM_APDU_HEADLEN)

#define SI_PIH_ATFILE_NAME_MAX          (40)

/*USIM-->GDSP*/
#define SI_PIH_DSP_POWER_LIMIT          (0x4715)

#define SI_PIH_FILE_START_INDEX         (1)

#define SI_PIH_BCPID_REG_MAX            (20)

#define SI_PIH_POLL_TIMER_START(pTimer,ulLength, Name)      VOS_StartRelTimer(pTimer,\
                                                                                MAPS_PIH_PID,\
                                                                                ulLength,\
                                                                                Name,\
                                                                                0,\
                                                                                VOS_RELTIMER_NOLOOP,\
                                                                                VOS_TIMER_NO_PRECISION)

#define SI_PIH_POLL_32K_TIMER_START(pTimer,ulLength, Name)  VOS_StartDrxTimer(pTimer,\
                                                                                MAPS_PIH_PID,\
                                                                                ulLength,\
                                                                                Name,\
                                                                                0)

#define SI_PIH_POLL_32K_TIMER_STOP(pTimer)                  VOS_StopDrxTimer(pTimer)

#define PIH_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(MAPS_PIH_PID), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define PIH_INFO_LOG(string)            (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PIH_PID, __FILE__, __LINE__, "%s", string)
#define PIH_NORMAL_LOG(string)          (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PIH_PID, __FILE__, __LINE__, "%s", string)
#define PIH_WARNING_LOG(string)         (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),MAPS_PIH_PID, __FILE__, __LINE__, "%s", string)
#define PIH_ERROR_LOG(string)           (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),MAPS_PIH_PID, __FILE__, __LINE__, "%s", string)

#define PIH_INFO1_LOG(string, para1)    (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PIH_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define PIH_NORMAL1_LOG(string, para1)  (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PIH_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define PIH_WARNING1_LOG(string, para1) (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),MAPS_PIH_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define PIH_ERROR1_LOG(string, para1)   (VOS_VOID)DIAG_LogReport(PIH_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),MAPS_PIH_PID, __FILE__, __LINE__, "%s,%d", string, para1)


#define PIH_BIT_N(num)                  (0x01 << (num))

#define SI_PIH_MNC_TWO_BYTES_LEN        (2)             /* MNC长度为2 */
#define SI_PIH_MNC_THREE_BYTES_LEN      (3)             /* MNC长度为3 */
#define SI_PIH_AD_MNC_LEN_POS           (3)             /* AD文件中MNC长度字段所在位置 */

#define SI_PIH_IMSI_MAX_LEN             (8)             /* IMSI中指示长度的最大值 */

#define PIH_SET_BIT(Data,BitNo)         (Data |= (VOS_UINT8)(0x1<<BitNo))

#define BIT_ACTIVECARD                  (3)             /*当前是否激活卡操作*/
#define BIT_HANDLEVSIM                  (2)             /*当前是否处理VSIM卡*/
#define BIT_VSIMSTATE                   (1)             /*当前VSIM卡是否激活*/
#define BIT_CURCARDOK                   (0)             /*当前卡是否在位 */

#define SI_PIH_DH_PARAP_MAX             (128)           /*DH 参数 P的最大长度*/
#define SI_PIH_DH_PARAG_MAX             (1)             /*DH 参数 G的最大长度*/

#define SI_PIH_VSIMAPN_MAX              (100)           /*VSIM APN 的最大长度，按照TAF的容量定义*/

#define SI_PIH_SMEM_ENDFLAG             (0x5A5A5A5A)

#define SI_PIH_HUK_LEN                  (0x10)
#define SI_PIH_HUK_BITS                 (128)

#define SI_PIH_APNSET_SMEM_ADDR         (g_ulTEEShareAddr)
#define SI_PIH_APNSET_SMEM_LEN          (0x400)         /*预留1K*/

#define SI_PIH_DHPARASET_SMEM_ADDR      (SI_PIH_APNSET_SMEM_ADDR+SI_PIH_APNSET_SMEM_LEN)
#define SI_PIH_DHPARASET_SMEM_LEN       (0x400)         /*预留1K*/

#define SI_PIH_VSIM_SMEM_ADDR           (SI_PIH_DHPARASET_SMEM_ADDR+SI_PIH_DHPARASET_SMEM_LEN)
#define SI_PIH_VSIM_SMEM_LEN            (0x1000)        /*预留4K*/


#define SI_PIH_GETCARDSTATUS_MAX        (200)

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
#define SI_PIH_TASKDELAY_TIMER_LEN      (20)
#else
#define SI_PIH_TASKDELAY_TIMER_LEN      (1)
#endif  /*(VOS_OS_VER != VOS_WIN32)*/

#define SI_PIH_TASKDELAY_SEM_LEN        (1000)

#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define SI_PIH_CTRL_INFO_SIZE           (5)             /* AT最大通道个数（4个）+1 */
#else
#define SI_PIH_CTRL_INFO_SIZE           (2)
#endif  /*(FEATURE_ON == FEATURE_VCOM_EXT)*/

/* 根据随机数和通道号获得SessionID, 0x1f值根据USIMM_CHANNEL_NUMBER_MAX来设定 */
#define SI_PIH_MAKESESSION_ID(RandNum, ChannelID) \
        ((RandNum & (~0x1f)) | ChannelID)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum SI_PIH_REQ_ENUM
{
    SI_PIH_NULL_REQ                 = 0,
    SI_PIH_FDN_ENABLE_REQ           = 1,
    SI_PIH_FDN_DISALBE_REQ          = 2,
    SI_PIH_GACCESS_REQ              = 3,
    SI_PIH_BDN_QUERY_REQ            = 4,
    SI_PIH_FDN_QUERY_REQ            = 5,
    SI_PIH_PCSC_DATA_REQ            = 6,
    SI_PIH_ISDB_ACCESS_REQ          = 7,
    SI_PIH_HVSST_QUERY_REQ          = 8,
    SI_PIH_HVSST_SET_REQ            = 9,
    SI_PIH_HVSDH_SET_REQ            = 10,
    SI_PIH_HVSDH_QRY_REQ            = 11,
    SI_PIH_HVSCONT_QRY_REQ          = 12,
    SI_PIH_FILE_WRITE_REQ           = 13,
    SI_PIH_CCHO_SET_REQ             = 14,
    SI_PIH_CCHC_SET_REQ             = 15,
    SI_PIH_CGLA_SET_REQ             = 16,
    SI_PIH_CARD_ATR_QRY_REQ         = 17,
    SI_PIH_UICCAUTH_REQ             = 18,
    SI_PIH_URSM_REQ                 = 19,
    SI_PIH_CARDTYPE_QUERY_REQ       = 20,
    SI_PIH_CRSM_SET_REQ             = 21,
    SI_PIH_CRLA_SET_REQ             = 22,
    SI_PIH_SESSION_QRY_REQ          = 23,
    SI_PIH_SCICFG_SET_REQ           = 24,
    SI_PIH_SCICFG_QUERY_REQ         = 25,
    SI_PIH_HVTEE_SET_REQ            = 26,
    SI_PIH_HVCHECKCARD_REQ          = 27,
    SI_PIH_CIMI_QRY_REQ             = 28,
    SI_PIH_CCIMI_QRY_REQ            = 29,

    SI_PIH_REQ_BUTT
};
typedef VOS_UINT32      SI_PIH_REQ_ENUM_UINT32;

enum SI_PIH_LOCK_ENUM
{
    SI_PIH_UNLOCK                   = 0,
    SI_PIH_LOCKED                   = 1,
    SI_PIH_LOCK_BUTT
};
typedef VOS_UINT32  SI_PIH_LOCK_ENUM_UINT32;

enum SI_PIH_PROTECT_STATE_ENUM
{
    SI_PIH_PROTECT_OFF              = 0,
    SI_PIH_PROTECT_ON               = 1,
    SI_PIH_PROTECT_RUNING           = 2,
    SI_PIH_PROTECT_SATATE_BUTT
};
typedef VOS_UINT32      SI_PIH_PROTECT_STATE_ENUM_UINT32;

enum SI_PIH_PROTECT_FUN_ENUM
{
    SI_PIH_PROTECT_DISABLE          = 0,
    SI_PIH_PROTECT_ENABLE           = 1,
    SI_PIH_PROTECT_FUN_BUTT
};
typedef VOS_UINT32      SI_PIH_PROTECT_FUN_ENUM_UINT32;

enum SI_PIH_CARDSTATE_REPORT_ENUM
{
    SI_PIH_NEED_REPORT              = 0,
    SI_PIH_NO_NEED_REPORT           = 1,
    SI_PIH_REPORT_BUTT
};

enum SI_PIH_DSP_LIMIT_ENUM
{
    SI_PIH_DSP_POWER_LIMIT_OFF      = 0,
    SI_PIH_DSP_POWER_LIMIT_ON       = 1,
    SI_PIH_DSP_POWER_LIMIT_BUTT
};
typedef VOS_UINT16      SI_PIH_DSP_LIMIT_ENUM_UINT16;

enum SI_PIH_PCSC_CMD_ENUM
{
    SI_PIH_PCSC_POWER_ON         = 0,
    SI_PIH_PCSC_POWER_OFF        = 1,
    SI_PIH_PCSC_SIM_QUIRY        = 2,
    SI_PIH_PCSC_APDU_CMD         = 3,
    SI_PIH_PCSC_GET_ATR          = 4,
    SI_PIH_PCSC_GET_PARA         = 5,
    SI_PIH_PCSC_GET_CLKFREQ      = 6,
    SI_PIH_PCSC_GET_BAUDRATE     = 7,
    SI_PIH_PCSC_CMD_BUTT
};
typedef VOS_UINT32      SI_PIH_PCSC_CMD_ENUM_UINT32;

enum SI_PIH_PCSC_SIM_STATUS_ENUM
{
    SI_PIH_PCSC_SIM_ABSENT       = 0,
    SI_PIH_PCSC_SIM_PRESENT      = 1,
    SI_PIH_PCSC_SIM_BUTT
};

typedef VOS_UINT8       SI_PIH_PCSC_SIM_STATUS;

enum SI_PIH_HVSST_HANDLE_STATE_ENUM
{                                               /*OP_ActiveCard OP_HandleVsim   OP_VsimState    OP_CurCardOK*/
    SI_PIH_HVSST_DEACTIVE_RSIM_AGAIN    = 0x00, /*0             0               0               0*/ /*无需操作*/
    SI_PIH_HVSST_DEACTIVE_RSIM          = 0x01, /*0             0               0               1*/ /*需要操作*/
    SI_PIH_HVSST_STATE_ERROR2           = 0x02, /*0             0               1               0*/ /*VSIM激活，卡不在位，去激活硬卡*/
    SI_PIH_HVSST_STATE_ERROR3           = 0x03, /*0             0               1               1*/ /*VSIM激活时候去激活硬卡*/
    SI_PIH_HVSST_STATE_ERROR4           = 0x04, /*0             1               0               0*/ /*硬卡不在，VSIM未打开，去激活VSIM*/
    SI_PIH_HVSST_STATE_ERROR5           = 0x05, /*0             1               0               1*/ /*硬卡在，VSIM未打开，去激活VSIM*/
    SI_PIH_HVSST_DEACTIVE_VSIM_AGAIN    = 0x06, /*0             1               1               0*/ /*无需操作*/
    SI_PIH_HVSST_DEACTIVE_VSIM          = 0x07, /*0             1               1               1*/ /*需要操作*/
    SI_PIH_HVSST_ACTIVE_RSIM            = 0x08, /*1             0               0               0*/ /*需要操作*/
    SI_PIH_HVSST_ACTIVE_RSIM_AGAIN      = 0x09, /*1             0               0               1*/ /*重复激活硬卡*/
    SI_PIH_HVSST_ACTIVE_RSIM_AGAIN2     = 0x0A, /*1             0               1               0*/ /*VSIM激活失败,激活硬卡*/
    SI_PIH_HVSST_STATE_ERROR11          = 0x0B, /*1             0               1               1*/ /*VSIM激活时候,激活硬卡*/
    SI_PIH_HVSST_ACTIVE_VSIM            = 0x0C, /*1             1               0               0*/ /*需要操作*/
    SI_PIH_HVSST_ACTIVE_ERROR13         = 0x0D, /*1             1               0               1*/ /*硬卡在位时候激活VSIM*/
    SI_PIH_HVSST_ACTIVE_VSIM_AGAIN      = 0x0E, /*1             1               1               0*/ /*VSIM激活时候,使能VSIM*/
    SI_PIH_HVSST_ACTIVE_VSIM_AGAIN2     = 0x0F, /*1             1               1               1*/ /*无需操作*/
    SI_PIH_HVSST_HANDLE_STATE_BUTT
};
typedef VOS_UINT8      SI_PIH_HVSST_HANDLE_STATE_ENUM_UINT8;

enum SI_PIH_HVTEE_DATAFLAG_ENUM
{
    SI_PIH_HVTEE_APNSET                 = 0xA5A5A001,
    SI_PIH_HVTEE_DHSET                  = 0xA5A5A002,
    SI_PIH_HVTEE_VSIMDATA               = 0xA5A5A003,
    SI_PIH_HVTEE_DATAFLAG_BUTT
};
typedef VOS_UINT32      SI_PIH_HVTEE_DATAFLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SI_PIH_RACCESS_SRC_TYPE_ENUM
 结构说明  : 用来区分PIH发来的CRSM命令类型
  1.日    期   : 2015年4月9日
    作    者   : g00256031
*****************************************************************************/
enum SI_PIH_RACCESS_SRC_TYPE_ENUM
{
    SI_PIH_RACCESS_FROM_PIH      = 0,
    SI_PIH_RACCESS_FROM_AT
};
typedef VOS_UINT8      SI_PIH_RACCESS_SRC_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : SI_PIH_INFO_LIST_ENUM_UINT8
 结构说明  :
 1.日    期   : 2012年08月28日
   作    者   : h59254
   修改内容   : 新建
*****************************************************************************/
enum SI_PIH_INFO_LIST_ENUM
{
    SI_PIH_INFO_USED_LIST_ID = 0,
    SI_PIH_INFO_FREE_LIST_ID,
    SI_PIH_INFO_LIST_BUTT
};

typedef VOS_UINT8  SI_PIH_INFO_LIST_ENUM_UINT8;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;       /* 消息名 */
    VOS_UINT16                          usClient;        /* 客户端ID */
    VOS_UINT8                           ucOpID;
    VOS_UINT8                           ucRsv;
    SI_PIH_EVENT                        ulEventType;
}SI_PIH_MSG_HEADER_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;
    VOS_UINT8                           aucPIN2[SI_PIH_PIN_CODE_LEN];      /* PIN2码，如上层调用未带入PIN2码则为全0 */
} SI_PIH_FDN_ENABLE_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;
    VOS_UINT8                           aucPIN2[SI_PIH_PIN_CODE_LEN];      /* PIN2码，如上层调用未带入PIN2码则为全0 */
} SI_PIH_FDN_DISABLE_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[8];
}SI_PIH_GACCESS_REQ_STRU;

/*****************************************************************************
 结构名    : SI_PIH_ISDB_ACCESS_REQ_STRU
 结构说明  : ISDB透传APDU的请求数据结构
 1.日    期   : 2012年08月28日
   作    者   : h59254
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;        /* PIH消息头    */
    VOS_UINT32                          ulDataLen;          /* PIH消息长度  */
    VOS_UINT8                           aucData[8];         /* PIH消息内容  */
}SI_PIH_ISDB_ACCESS_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU          stMsgHeader;
    VOS_UINT32                      ulMsgType;
    VOS_UINT32                      ulCmdType;
    VOS_UINT32                      ulCmdLen;
    VOS_UINT8                       aucAPDU[8];
}SI_PIH_PCSC_REQ_STRU;

typedef VOS_VOID (*PUSIMPCSCPROC)(SI_PIH_PCSC_REQ_STRU *pstMsg);

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;        /* PIH消息头 */
    SI_PIH_HVSST_SET_STRU               stHvSSTData;
} SI_PIH_HVSST_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;        /* PIH消息头 */
    VOS_UINT8                           ucFileNameLen;
    VOS_UINT8                           aucFileName[SI_PIH_ATFILE_NAME_MAX];
    VOS_UINT8                           ucRef;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulFileDataLen;
    VOS_UINT8                           aucFileData[4];
} SI_PIH_FILE_WRITE_REQ_STRU;

typedef struct
{
    SI_PIH_PROTECT_FUN_ENUM_UINT32      enProtectFun;
    SI_PIH_PROTECT_STATE_ENUM_UINT32    enProtectState;
}SI_PIH_PROTECT_CTRL_STRU;

typedef struct
{
    SI_PIH_LOCK_ENUM_UINT32             enPIHLock;
    VOS_UINT16                          usClient;
    VOS_UINT8                           ucOpID;
    VOS_UINT8                           ucResv;
    VOS_UINT32                          enCmdType;
    SI_PIH_EVENT                        ulEventType;
}SI_PIH_CTRL_INFO_STRU;

typedef struct
{
    SI_PIH_POLLTIMER_STATE_ENUM_UINT32  enPollState;
    VOS_UINT32                          enPollData;
    VOS_UINT32                          ulTimeLen;
    VOS_UINT32                          ulTimerName;
    HTIMER                              stTimer;
}SI_PIH_POLL_TIME_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;
    SI_PIH_DSP_LIMIT_ENUM_UINT16        enLimit;
}SI_PIH_DSP_LIMIT_STRU;

typedef struct
{
    VOS_UINT8                           ucIMSILen;
    VOS_UINT8                           aucIMSI[9];
    VOS_UINT8                           aucRsv[2];
}SI_PIH_IMSI_STRU;

typedef struct
{
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT16                          usRspLen;
    VOS_UINT8                           aucRspCotent[USIMM_T0_APDU_MAX_LEN];
}SI_PIH_CSIM_CTRL_STRU;

typedef struct
{
    VOS_UINT16                     usIndex;
    VOS_UINT16                     usRefNum;
    VOS_UINT16                     usTotalNum;
    VOS_UINT16                     usRsv;
    FILE                           *fpFile;
}SI_PIH_FWRITE_PARA_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;          /* 消息类型 */
    VOS_UINT32                      ulResult;           /* PC/SC命令执行结果 */
    VOS_UINT32                      ulCmdType;          /* 命令类型 */
    VOS_UINT32                      ulRspLen;           /* 命令执行得到的数据长度 */
    VOS_UINT8                       aucContent[4];      /* 数据内容 */
}SI_PIH_PCSC_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;          /* 消息类型 */
    VOS_UINT8                       aucContent[4];      /* 数据内容 */
}SI_PIH_HOOK_MSG_STRU;

/*****************************************************************************
 结构名    : SI_PIH_CCHO_SET_REQ_STRU
 结构说明  : 打开逻辑通道请求数据结构
 1.日    期   : 2013年05月14日
   作    者   : g47350
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;                            /* PIH消息头 */
    VOS_UINT32                          ulAIDLen;                               /* AID的长度 */
    VOS_UINT8                           aucADFName[2*USIMM_AID_LEN_MAX];        /* 考虑到中移动不对AID长度检测的需求将长度增大1倍 */
}SI_PIH_CCHO_SET_REQ_STRU;

/*****************************************************************************
 结构名    : SI_PIH_CCHC_SET_REQ_STRU
 结构说明  : 打开逻辑通道请求数据结构
 1.日    期   : 2013年05月14日
   作    者   : g47350
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;                            /* PIH消息头 */
    VOS_UINT32                          ulSessionID;                            /* 逻辑通道号 */
}SI_PIH_CCHC_SET_REQ_STRU;

/*****************************************************************************
 结构名    : SI_PIH_CGLA_REQ_STRU
 结构说明  : 透传逻辑通道APDU的请求数据结构
 1.日    期   : 2013年05月14日
   作    者   : g47350
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;                            /* PIH消息头    */
    VOS_UINT32                          ulSessionID;                            /* 逻辑通道号 */
    VOS_UINT32                          ulDataLen;                              /* 命令长度  */
    VOS_UINT8                           aucData[SI_APDU_MAX_LEN + 1];           /* 命令内容 ,带LE字段多一个字节 */
    VOS_UINT8                           aucRsv[3];
}SI_PIH_CGLA_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[4];
}SI_PIH_HVSDH_SET_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;
}SI_PIH_HVS_QRY_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;        /* PIH消息头 */
    SI_PIH_UICCAUTH_STRU                stAuthData;
} SI_PIH_UICCAUTH_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;        /* PIH消息头 */
    SI_PIH_ACCESSFILE_STRU              stCmdData;
} SI_PIH_ACCESSFILE_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;        /* PIH消息头 */
    SI_PIH_CARD_SLOT_ENUM_UINT32        enCard0Slot;
    SI_PIH_CARD_SLOT_ENUM_UINT32        enCard1Slot;
    SI_PIH_CARD_SLOT_ENUM_UINT32        enCard2Slot;
} SI_PIH_SCICFG_SET_REQ_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;        /* PIH消息头 */
    SI_PIH_HVTEE_SET_STRU               stHvtee;
} SI_PIH_HVTEE_SET_REQ_STRU;

typedef struct
{
    SI_PIH_HVTEE_DATAFLAG_ENUM_UINT32   enFlag;
    VOS_UINT32                          ulDataLen;
}SI_PIH_HVTEE_SHAREHEAD_STRU;

typedef struct
{
    VOS_UINT32                          ulSPublicKeyLen;
    VOS_UINT8                           aucSPublicKey[VSIM_KEYLEN_MAX];
    VOS_UINT32                          ulCPublicKeyLen;
    VOS_UINT8                           aucCPublicKey[VSIM_KEYLEN_MAX];
    VOS_UINT32                          ulCPrivateKeyLen;
    VOS_UINT8                           aucCPrivateKey[VSIM_KEYLEN_MAX];
    VOS_UINT32                          ulParaPLen;
    VOS_UINT8                           aucParaPKey[SI_PIH_DH_PARAP_MAX];
    VOS_UINT32                          ulParaGLen;
    VOS_UINT8                           aucParaGKey[SI_PIH_DH_PARAG_MAX];
    VOS_UINT8                           aucRsv[3];
}SI_PIH_HVTEEDHPARA_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;
}SI_PIH_HVCHECKCARD_REQ_STRU;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usEfId;         /* 文件ID */
    VOS_UINT8                           ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                           ucRsv;          /* 保留 */
}SI_PIH_GETFILE_INFO_STRU;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usEfId;         /* 文件ID */
    VOS_UINT8                           ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                           ucRsv;          /* 保留 */
    VOS_UINT32                          ulEfLen ;       /* 更新数据长度 */
    VOS_UINT8                           *pucEfContent;  /* 更新数据内容 */
}SI_PIH_SETFILE_INFO_STRU;

/*****************************************************************************
 结构名    : SI_PIH_CARDINFO_STRU
 结构说明  : PIH模块保存USIM卡信息数据结构
*****************************************************************************/
typedef struct
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enPhyCardType;
    USIMM_CARD_TYPE_ENUM_UINT32         enGUTLCardType;     /*USIM/SIM*/
    USIMM_CARD_SERVIC_ENUM_UINT32       enGUTLSvcStatus;    /*USIM/SIM Status*/
    USIMM_CARD_TYPE_ENUM_UINT32         enCDMACardType;     /*CSIM/UIM*/
    USIMM_CARD_SERVIC_ENUM_UINT32       enCDMASvcStatus;    /*CSIM/UIM Status*/
}SI_PIH_CARDINFO_STRU;

/*****************************************************************************
 结构名    : SI_PIH_CRSM_SET_REQ_STRU
 结构说明  : CRSM请求数据结构
 1.日    期   : 2015年04月08日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;                            /* PIH消息头 */
    SI_PIH_CRSM_STRU                    stMsgContent;
}SI_PIH_CRSM_SET_REQ_STRU;

/*****************************************************************************
 结构名    : SI_PIH_CRLA_SET_REQ_STRU
 结构说明  : CRLA请求数据结构
 1.日    期   : 2015年04月08日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    SI_PIH_MSG_HEADER_STRU              stMsgHeader;                            /* PIH消息头 */
    SI_PIH_CRLA_STRU                    stMsgContent;
}SI_PIH_CRLA_SET_REQ_STRU;

typedef struct
{
    VOS_UINT32                          ulAppType;
    VOS_UINT32                          ulSessionID;
}SI_PIH_CHANNELAPPINFO_STRU;

/*****************************************************************************
 结构名    : SI_PIH_CTRL_INFO_NODE_STRU
 结构说明  : PIH控制信息节点
 1.日    期   : 2015年05月12日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_LIST_S                           stListNode;
    VOS_UINT16                          usClient;
    VOS_UINT8                           ucOpID;
    VOS_UINT8                           ucResv;
    VOS_UINT32                          enCmdType;
    SI_PIH_EVENT                        ulEventType;
}SI_PIH_CTRL_INFO_NODE_STRU;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern SI_PIH_POLL_TIME_STRU        g_stPIHPollTime[3];

extern VOS_MSG_HOOK_FUNC            vos_MsgHook;

extern VOS_UINT32                   g_aulPIHUsimBCPid[SI_PIH_BCPID_REG_MAX];

extern VOS_UINT32                   g_aulPIHRefreshBCPid[SI_PIH_BCPID_REG_MAX];

extern SI_PIH_CARDINFO_STRU         g_stPihCardInfo;

extern SI_PIH_CSIM_CTRL_STRU        g_stPIHCSIMCtrlInfo;


#if (FEATURE_ON == FEATURE_VSIM)
extern SI_PIH_FWRITE_PARA_STRU      g_stPIHFileWriteGlobal;

extern VOS_UINT8                    g_aucVsimAPNData[SI_PIH_VSIMAPN_MAX];

extern VOS_UINT32                   g_ulTEEShareAddr;
#endif  /*(FEATURE_ON == FEATURE_VSIM)*/

/*****************************************************************************
  6 函数声明
*****************************************************************************/

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
extern VOS_VOID SI_PIH_InitList(VOS_VOID);

extern SI_PIH_CTRL_INFO_NODE_STRU* SI_PIH_GetCtrlNode(
    SI_PIH_INFO_LIST_ENUM_UINT8         enListType
);

extern VOS_VOID SI_PIH_PutCtrlNode(
    SI_PIH_INFO_LIST_ENUM_UINT8         enListType,
    SI_PIH_CTRL_INFO_NODE_STRU         *pstCtrlInfo
);

extern VOS_VOID SI_PIH_PutCtrlNode_Head(
    SI_PIH_INFO_LIST_ENUM_UINT8         enListType,
    SI_PIH_CTRL_INFO_NODE_STRU         *pstCtrlInfo
);

extern VOS_VOID SI_PIH_VsimWriteableFileUpdate(
    VOS_UINT16                          usFileId,
    VOS_UINT8                           *pucFileContent
);

extern VOS_VOID SI_PIH_VsimWriteableFileClear(VOS_VOID);

extern VOS_UINT32 SI_PIH_ImsiBcd2Ascii(
    VOS_UINT8                           ucLen,
    VOS_UINT8                           *pucNum,
    VOS_UINT8                           *pucAsciiStr);

extern VOS_VOID SI_PIH_BcdNumToAsciiNum(
    VOS_UINT8                           *pucAsciiNum,
    VOS_UINT8                           *pucBcdNum,
    VOS_UINT8                           ucBcdNumLen);

extern VOS_VOID SI_PIH_ActiveSimCnfProc(
    USIMM_SINGLECMD_CNF_STRU            *pMsg);

extern VOS_VOID SI_PIH_ReDhNegotiateIndProc(VOS_VOID);

extern VOS_VOID SI_PIH_AuthCnfProc(
    USIMM_AUTHENTICATION_CNF_STRU       *pstMsg);

extern VOS_VOID SI_PIH_GetFileCnfProc(
    USIMM_READFILE_CNF_STRU             *pstMsg);

extern VOS_VOID SI_PIH_SetFileCnfProc(
    USIMM_UPDATEFILE_CNF_STRU           *pstMsg);

extern VOS_UINT32 SI_PIH_HvsDHSetHandle(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucData);

extern VOS_UINT32 SI_PIH_HvsDHQueryHandle(VOS_VOID);

extern VOS_VOID SI_PIH_DecodeImsiHPLMN(
    VOS_UINT8                           *pucImsi,
    VOS_UINT8                           ucMNCLen,
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont);

extern VOS_VOID SI_PIH_DecodeEHPLMN(
    VOS_UINT8                           *pucData,
    VOS_UINT32                          ulDateLen,
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont);

extern VOS_BOOL SI_PIH_GetEHPlmnNVState(VOS_VOID);

extern VOS_UINT8 SI_PIH_GetMncLen(
    VOS_UINT8                           *pucAdContent,
    VOS_UINT32                          ulFileSize);

extern VOS_VOID SI_PIH_GetRSimContent(
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont);

extern VOS_UINT32 SI_PIH_GetUsimUstState(
    VOS_UINT8                           *pucUst,
    VOS_UINT32                          ulUstLen,
    VOS_UINT32                          ulBitNo);

extern VOS_UINT32 SI_PIH_DecodeVSimFile(
    VOS_UINT8                           *pucXMLData,
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont);

extern VOS_VOID SI_PIH_GetVSimContent(
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont);

extern VOS_UINT8* SI_PIH_GetVSimFileContent(
    OAM_XML_NODE_STRU                   *pstXmlNode,
    VOS_CHAR                            *pcEFName,
    VOS_UINT32                          *pulDataLen);

extern VOS_UINT32 SI_PIH_HvsContQueryHandle(VOS_VOID);

extern VOS_UINT32 SI_PIH_HVSSTQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pMsg
);

extern VOS_BOOL SI_PIH_HVSSTStateCheck(
    SI_PIH_HVSST_REQ_STRU               *pMsg,
    SI_PIH_EVENT_INFO_STRU              *pstEvent
);

extern VOS_UINT32 SI_PIH_HVSSTSetHandle(
    SI_PIH_HVSST_REQ_STRU               *pMsg
);

extern VOS_UINT32 SI_PIH_ATFileWriteHandle(
    SI_PIH_FILE_WRITE_REQ_STRU          *pstMsg);

extern VOS_VOID SI_PIH_GetEFIDFromPath(
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    VOS_UINT16                         *pusEFID
);

extern VOS_UINT32 SI_PIH_GetFileReq(
    VOS_UINT32                          ulSendPara,
    SI_PIH_GETFILE_INFO_STRU           *pstGetFileInfo
);

extern VOS_UINT32 SI_PIH_SendFdnReqMsg(
    USIMM_FBDN_HANDLE_ENUM_UINT32       ulType,
    VOS_UINT8                           *pucPin2);

extern VOS_UINT32 SI_PIH_SendDeactiveReqMsg(
    VOS_UINT32                          ulSendPara);

extern VOS_UINT32 SI_PIHSendATMsg(
    SI_PIH_EVENT_INFO_STRU              *pstEvent);

extern VOS_UINT32 SI_PIH_EventCallBack(
    SI_PIH_EVENT_INFO_STRU              *pstEvent);


extern VOS_UINT32 SI_PIH_SetFileReq(
    SI_PIH_SETFILE_INFO_STRU            *pstSetFileInfo);

extern VOS_UINT32 SI_PIH_UiccAuthHandle(
    SI_PIH_UICCAUTH_REQ_STRU            *pstMsg);

extern VOS_UINT32 SI_PIH_AccessFileHandle(
    SI_PIH_ACCESSFILE_REQ_STRU          *pstMsg);

extern VOS_UINT32 SI_PIH_FwriteParaCheck(
    SI_PIH_FILE_WRITE_REQ_STRU          *pstMsg);

extern VOS_UINT32 SI_PIH_ParaCheck(
    VOS_UINT16                          usClient);

extern VOS_VOID SI_PIH_PollTimerPro(
    SI_PIH_POLL_TIME_STRU               *pstPIHTimer);

extern VOS_UINT32  SI_PIH_FdnBdnStateReport(
    VOS_UINT32                          ulState,
    VOS_UINT32                          SimError,
    VOS_UINT32                          ulCmdType);

extern VOS_UINT32  SI_PIH_MsgSyncProc(
    PS_SI_MSG_STRU                      *pMsg
);

extern VOS_UINT32  SI_PIH_MsgAsyncProc(
    PS_SI_MSG_STRU                      *pMsg
);

extern VOS_VOID SI_PIH_SendPCSCCnfMsg(
    VOS_UINT32                          ulCmdType,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           *pucContent);

extern VOS_UINT32  SI_PIH_MsgProc(
    PS_SI_MSG_STRU                      *pMsg
);

extern VOS_VOID SI_PIH_PCSCDataCnf(
    VOS_UINT32                          ulCmdType,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           *pucContent);

extern VOS_UINT32 SI_PIH_PCSCApduCheck(
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucApdu,
    VOS_UINT32                          *pulRspLen,
    VOS_UINT8                           *pucRsp);

extern VOS_UINT32 SI_PIH_IsdbAccessReqProc(
    SI_PIH_ISDB_ACCESS_REQ_STRU         *pstMsg);

extern VOS_UINT32 SI_PIH_CchoSetReqProc(
    SI_PIH_CCHO_SET_REQ_STRU            *pstMsg);

extern VOS_UINT32 SI_PIH_CchcSetReqProc(
    SI_PIH_CCHC_SET_REQ_STRU            *pstMsg);

extern VOS_UINT32 SI_PIH_CglaSetReqProc(
    SI_PIH_CGLA_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_PowerOn(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_PowerOff(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_SimQuiry(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_GetATR(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_GetPara(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_GetClkFreq(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_GetBaudRate(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_VOID SI_PIH_PCSC_ApduCmd(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);

extern VOS_UINT32 SI_PIH_PCSCCmdHandle(
    SI_PIH_PCSC_REQ_STRU                *pstMsg);


extern VOS_VOID SI_PIH_IsdbAccessCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg);

extern VOS_VOID SI_PIH_RefreshIndProc(
    USIMM_STKREFRESH_IND_STRU           *pstMsg);

extern VOS_VOID SI_PIH_CardTimeOutProc(VOS_VOID);

extern VOS_VOID SI_PIH_ProtectResetCnfProc(
    USIMM_SINGLECMD_CNF_STRU            *pstMsg);

extern VOS_VOID SI_PIH_StatusCnfProc(
    USIMM_SINGLECMD_CNF_STRU            *pstMsg);

extern VOS_VOID SI_PIH_PCSCCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg);

extern VOS_VOID SI_PIH_GAccessCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg);

extern VOS_UINT32 SI_PIH_ATRQryReqProc(VOS_VOID);

extern VOS_VOID SI_PIH_OpenChannelCnfProc(
    USIMM_OPENCHANNEL_CNF_STRU          *pstMsg);

extern VOS_VOID SI_PIH_CloseChannelCnfProc(
    USIMM_CLOSECHANNEL_CNF_STRU         *pstMsg);

extern VOS_VOID SI_PIH_AccessChannelCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg);

extern VOS_VOID SI_PIH_CardUsimStatusInd(
    USIMM_CARDSTATUS_IND_STRU           *pstMsg);

extern VOS_VOID SI_PIH_SendMsg2DSPSingle(
    SI_PIH_DSP_LIMIT_ENUM_UINT16        enLimit);

extern VOS_VOID SI_PIH_SendMsg2DSPAll(
    SI_PIH_DSP_LIMIT_ENUM_UINT16        enLimit);

extern VOS_VOID SI_PIH_SendMsg2DSP(
    SI_PIH_DSP_LIMIT_ENUM_UINT16        enLimit);

extern VOS_VOID SI_PIH_CardStateIndProc(
    USIMM_CARDSTATUS_IND_STRU           *pstMsg);

extern VOS_UINT32 SI_PIH_UsimIndMsgProc(
    PS_SI_MSG_STRU                      *pstMsg);

extern VOS_UINT32 SI_PIH_UsimCnfMsgProc(
    PS_SI_MSG_STRU                      *pMsg);

extern VOS_UINT32 SI_PIH_UsimMsgProc(
    PS_SI_MSG_STRU                      *pMsg);

extern VOS_UINT32 SI_PIH_TimerMsgProc(
    REL_TIMER_MSG                       *pstMsg);

extern VOS_UINT32 SI_PIH_STKMsgProc(
    PS_SI_MSG_STRU                       *pstMsg);

extern VOS_VOID SI_PIH_ChangePollTimer(
    SI_PIH_TIMER_NAME_ENUM_UINT32       enTimerName,
    SI_PIH_POLLTIMER_STATE_ENUM_UINT32  enState,
    VOS_UINT32                          ulTimerLen,
    USIMM_POLL_FCP_ENUM_UINT32          enData);

extern VOS_UINT32 SI_PIH_CheckGCFTestCard(VOS_VOID);

extern VOS_VOID SI_PIH_MNTNDataHook(
    VOS_UINT32                          ulHookMsgName,
    VOS_UINT32                          ulHookDataLen,
    VOS_UINT8                           *pucHookData);


extern VOS_UINT32 SI_PIH_SendProtectResetReqMsg(VOS_VOID);

extern VOS_UINT32 SI_PIH_SendStatusReqMsg(
    USIMM_POLL_FCP_ENUM_UINT32          enNeedFcp);

extern VOS_UINT32 SI_PIH_SendImsiPollingReqMsg(VOS_VOID);

extern VOS_UINT32 SI_PIH_CloseChannelReq(
    VOS_UINT32                          ulAppType,
    VOS_UINT32                          ulSessionID);

extern VOS_UINT32 SI_PIH_OpenChannelReq(
    VOS_UINT32                          ulAIDLen,
    VOS_UINT8                           *pucADFName);


extern VOS_UINT32 SI_PIH_SendActiveCardReqMsg(
    VOS_UINT32                          ulSendPara
);

extern VOS_UINT32 SI_PIH_HexToAsciiCode(
    VOS_UINT8                           ucSrc,
    VOS_CHAR                            *pcDst);

extern VOS_UINT32 SI_PIH_AsciiToHexCode(
    VOS_CHAR                            cSrc,
    VOS_UINT8                           *pucDst);

extern VOS_UINT32 SI_PIH_SendTPDUReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          ulSendPara,
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    USIMM_TPDU_DATA_STRU               *pstTpduData
);

extern VOS_VOID SI_PIH_PollTimerInit(SI_VOID);

extern VOS_VOID SI_PIH_InitList(VOS_VOID);


extern VOS_UINT32 SI_PIH_GetAppBySession(
    VOS_UINT32                          ulSessionID,
    USIMM_CARDAPP_ENUM_UINT32           *penAppType);

extern VOS_UINT32 SI_PIH_GetAppSession(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          *pulSessionID);

extern VOS_VOID SI_PIH_ClearAppSession(
    VOS_UINT32                          ulSessionID);

extern VOS_VOID SI_PIH_SetAppSession(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);


extern VOS_UINT32 SI_PIH_CardTypeQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pMsg);

extern VOS_UINT32 SI_PIH_CrsmSetHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg);

extern VOS_UINT32 SI_PIH_CrlaSetHandle(
    SI_PIH_MSG_HEADER_STRU              *pMsg);

extern VOS_UINT32 SI_PIH_CardSessionQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg);

extern VOS_UINT32 SI_PIH_IMSICheckPinSatus(VOS_UINT32 ulCardStatus);

extern VOS_UINT32 SI_PIH_CIMIQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg);

extern VOS_UINT32 SI_PIH_CCIMIQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg);

extern VOS_VOID SI_PIH_ClearChannelInfo(VOS_VOID);

extern VOS_VOID SI_PIH_SaveChannelInfo(
    VOS_UINT32                          ulChannelID,
    VOS_UINT32                          ulSessionID,
    VOS_UINT32                          ulAppType);

extern VOS_VOID SI_PIH_RAccessCnfFromAT(
    USIMM_RACCESS_CNF_STRU              *pstRAccessCnf);

extern VOS_UINT32 SI_PIH_ImsiPollingCnfProc(
    USIMM_RACCESS_CNF_STRU              *pstRAccessCnf);

extern VOS_VOID SI_PIH_InitGlobalVar(VOS_VOID);

extern VOS_UINT32 SI_PIH_HukEncode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen
);

extern SI_PIH_HVTEE_ERROR_ENUM_UINT32 SI_PIH_HvteeDataCheck(
    SI_PIH_HVTEE_DATAFLAG_ENUM_UINT32   enFlag,
    VOS_UINT32                          ulMaxLen,
    VOS_UINT8                           *pucData
);

extern VOS_UINT32 SI_PIH_HvteeApnHandle(VOS_VOID);

extern VOS_UINT32 SI_PIH_HvteeDHHandle(VOS_VOID);

extern VOS_UINT32 SI_PIH_HvteeVSIMHandle(VOS_VOID);

extern VOS_UINT32 SI_PIH_HvteeSetHandle(
    SI_PIH_HVTEE_SET_REQ_STRU           *pstMsg
);

extern VOS_UINT32 SI_PIH_SciCfgSetHandle(
    SI_PIH_SCICFG_SET_REQ_STRU          *pstMsg
);

extern VOS_UINT32 SI_PIH_SciCfgQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg
);

extern VOS_UINT32 SI_PIH_HvCheckCardHandle(
    SI_PIH_HVCHECKCARD_REQ_STRU         *pstMsg
);

extern VOS_VOID SI_PIH_InitTEEShareAddr(VOS_VOID);


/*外部接口*/
extern VOS_UINT32 USIMM_CCB_GetUsimSimulateIsimStatus(VOS_VOID);

extern VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid );

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
extern VOS_UINT32 USIMM_CCB_IsCardExist(VOS_VOID);;
#endif  /*((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT))*/

#endif  /*(OSA_CPU_CCPU == VOS_OSA_CPU)*/

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

#endif

