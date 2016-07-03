
#ifndef __MNMSGCOMMPROC_H__
#define __MNMSGCOMMPROC_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafTypeDef.h"
#include  "MnMsgApi.h"
#include  "UsimPsInterface.h"
#include  "MnComm.h"

#include "NasSms.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif

#include "siappstk.h"

#include "TafMmaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*----------------------------EF ID(31.102)-------------------------------------*/
#define  EF_SMS_INVALID_ID                                  0xFFFF

/*----------------------------EF SMS STATUS(31.102)-----------------------------*/
#define  EF_SMS_STATUS_FREE_SPACE                           0x00                /*空位置*/
#define  EF_SMS_STATUS_USED_SPACE                           0x01                /*已使用的位置*/
#define  EF_SMS_STATUS_MT_READ                              0x01                /*已收到且阅读的消息*/
#define  EF_SMS_STATUS_MT_TO_BE_READ                        0x03                /*已收到未阅读的消息*/
#define  EF_SMS_STATUS_MO_TO_BE_SEND                        0x07                /*MO未发送的消息*/
#define  EF_SMS_STATUS_MO_SEND_TO_NT                        0x05                /*MO已发送到网侧的消息*/
#define  EF_SMS_STATUS_NO_SRR                               0x05                /*未请求状态报告的消息*/
#define  EF_SMS_STATUS_SRR_NOT_RCV                          0x0D                /*请求状态报告但未收到状态报告的消息*/
#define  EF_SMS_STATUS_SRR_RCV_NOT_STOR                     0x15                /*已收到状态报告未存储的消息*/
#define  EF_SMS_STATUS_SRR_RCV_STOR                         0x1D                /*已收到状态报告且存储的消息*/

/*-------------------------EF SMS STATUS REPORT(31.102)-------------------------*/
#define  EF_SMS_STATUS_REPORT_EMPTY                         0x00                /*状态报告为空*/

#define  MN_MSG_MAX_TPDU_LEN                                232
#define  MN_MSG_TPMR_POS                                    0x01

#define  MN_MSG_EFSMS_LEN                                   176                 /*EFSMS文件的长度*/
#define  MN_MSG_EFSMSR_LEN                                  30                  /*EFSMSR文件的长度*/

#define  MN_MSG_NO_AVAILABLE_REC                            0xff                /*查看USIM或NVIM中空闲的记录数*/
#define  MN_MSG_NO_AVAILABLE_SMS_REC                        0xffffffff                /*查看USIM或NVIM中空闲的记录数*/

#define  MN_MSG_SIM_EXIST                                   1                   /*存在SIM卡*/
#define  MN_MSG_SIM_NOT_EXIST                               0                   /*不存在SIM卡*/

#define  MN_MSG_MAX_DELETE_REC_NUM                          10                  /*SMA一次能够删除的记录数目*/
#define  MN_MSG_MAX_ORG_REC_NUM                             10                  /*保留内存中原始短信的条数*/

#define  MN_MSG_MAX_RPDATA_LEN                              248                 /*23040 7.3.1.2 RP DATA (Mobile Station to Network)长度*/

#define  MN_MSG_USIM_DEF_REC                                0

#define MN_MSG_SIM_MEM_FULL_SET                             0xFE
#define MN_MSG_SIM_MEM_FULL_UNSET                           0xFF

/*DEVICE ID*/
#define  MN_MSG_DEVICE_NETWORK                              83
#define  MN_MSG_DEVICE_UICC                                 81

#define  MN_MSG_NV_SMSP_VOLUME                              1
#define  MN_MSG_FILE_NONE_REC                               0

#define MN_MSG_PC_REPLAY_MSG_PART1                          (ID_TAF_PC_REPLAY_BASE + 0x01)              /* 为PC工程回放定义的消息 */
#define MN_MSG_PC_REPLAY_MSG_PART2                          (ID_TAF_PC_REPLAY_BASE + 0x02)              /* 为PC工程回放定义的消息 */
#define MN_MSG_PC_REPLAY_MSG_PART3                          (ID_TAF_PC_REPLAY_BASE + 0x03)              /* 为PC工程回放定义的消息 */

#define MN_MSG_USIM_ENVELOPE_RSP_UNKNOWN_ERROR              (0x6F00)            /* 规避联通SIM卡MO SMS Ctrl错误 */

#ifdef __PS_WIN32_RECUR__
VOS_UINT32 NAS_MSG_RestoreContextData(struct MsgCB * pMsg);
#endif

#define MN_MSG_MAX_CHG_SM_STATE_NUM                         20
/*****************************************************************************
  3 类型定义
*****************************************************************************/

enum MN_MSG_MT_CUSTOMIZE_ENUM
{
    MN_MSG_MT_CUSTOMIZE_NONE,
    MN_MSG_MT_CUSTOMIZE_DCM,
    MN_MSG_MT_CUSTOMIZE_BUTT
} ;
typedef VOS_UINT8 MN_MSG_MT_CUSTOMIZE_ENUM_UINT8;


enum MN_MSG_MO_STATE_ENUM
{
    MN_MSG_MO_STATE_NULL                                    = 0,                /*空闲*/
    MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP                      = 1,
    MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP                       = 2,                /*等待USIM的MO SMS CONTROL 过程响应消息*/
    MN_MSG_MO_STATE_WAIT_REPORT_IND                         = 3,                /*等待报告指示*/
    MN_MSG_MO_STATE_MAX
} ;
typedef VOS_UINT8   MN_MSG_MO_STATE_ENUM_U8;

enum MN_MSG_MT_STATE_ENUM
{
    MN_MSG_MT_STATE_NULL                                    = 0,                /*空闲*/
    MN_MSG_MT_STATE_WAIT_REPORT_REQ                         = 2,                /*等待报告指示*/
    MN_MSG_MT_STATE_MAX
};
typedef VOS_UINT8   MN_MSG_MT_STATE_ENUM_U8;

enum MN_MSG_MO_TYPE_ENUM
{
    MN_MSG_MO_TYPE_MO,
    MN_MSG_MO_TYPE_SMMA,
    MN_MSG_MO_TYPE_BUFFER_STK,
    MN_MSG_MO_TYPE_MAX
};
typedef VOS_UINT8   MN_MSG_MO_TYPE_ENUM_U8;

enum MN_MSG_MO_SEND_FROM_ENUM
{
    MN_MSG_MO_SEND_FROM_CLIENT,
    MN_MSG_MO_SEND_FROM_MEM,
    MN_MSG_MO_SEND_FROM_MAX
};
typedef VOS_UINT8 MN_MSG_MO_SEND_FROM_ENUM_U8;

enum MN_MSG_USIM_ACTION_ENUM
{
    MN_MSG_USIM_READ,
    MN_MSG_USIM_LIST,
    MN_MSG_USIM_WRITE,
    MN_MSG_USIM_DELETE,
    MN_MSG_USIM_WRITE_EFSMSP,
    MN_MSG_USIM_DELETE_EFSMSP,
    MN_MSG_USIM_MODIFYSTATUS,
    MN_MSG_USIM_DELETE_STARPT,
    MN_MSG_USIM_RCVNEWMSG,
    MN_MSG_USIM_RCVSTARPT,
    MN_MSG_USIM_SEND,
    MN_MSG_USIM_RCVMORPT,
    MN_MSG_USIM_SET_EFSMSS,
    MN_MSG_USIM_MAX
};
typedef VOS_UINT8 MN_MSG_USIM_ACTION_ENUM_U8;

enum MN_MSG_SET_USIM_ENUM
{
    MN_MSG_SET_USIM_LIST,
    MN_MSG_SET_USIM_DELETE,
    MN_MSG_SET_USIM_DELETE_BEGIN,
    MN_MSG_SET_USIM_DELETE_STARPT,
    MN_MSG_SET_USIM_DELETE_STARPT_BEGIN,
    MN_MSG_SET_USIM_DELETE_EFSMSP,
    MN_MSG_SET_USIM_MAX
};
typedef VOS_UINT8 MN_MSG_SET_USIM_ENUM_U8;

enum MN_MSG_USIM_POWER_STATE_ENUM
{
    MN_MSG_USIM_POWER_BEGIN,
    MN_MSG_USIM_POWER_WAIT_EFSMSS,
    MN_MSG_USIM_POWER_WAIT_EFSMSP,
    MN_MSG_USIM_POWER_WAIT_EFSMSREC,
    MN_MSG_USIM_POWER_WAIT_EFSMS,
    MN_MSG_USIM_POWER_WAIT_EFSMSR,
    MN_MSG_USIM_POWER_ON
};
typedef VOS_UINT8 MN_MSG_USIM_POWER_STATE_ENUM_U8;

enum MN_MSG_SEND_FAIL_FLAG
{
    MN_MSG_SEND_FAIL_NO_DOMAIN,
    MN_MSG_SEND_FAIL_PS_DOMAIN,
    MN_MSG_SEND_FAIL_CS_DOMAIN,
    MN_MSG_SEND_FAIL_CSPS_DOMAIN
};
typedef VOS_UINT8 MN_MSG_SEND_FAIL_FLAG_U8;

enum MN_MSG_DOMAIN_AVAIL_FLAG
{
    MN_MSG_NO_DOMAIN_AVAIL,
    MN_MSG_PS_DOMAIN_AVAIL,
    MN_MSG_CS_DOMAIN_AVAIL,
    MN_MSG_CSPS_DOMAIN_AVAIL
};
typedef VOS_UINT8 MN_MSG_DOMAIN_AVAIL_FLAG_U8;

enum MN_MSG_RETRY_FLAG
{
    MN_MSG_RETRY_OFF,                                                           /* 重发功能未开启 */
    MN_MSG_RETRY_BEGIN,                                                         /* 重发开始 */
    MN_MSG_RETRY_END                                                            /* 重发结束 */
};
typedef VOS_UINT8 MN_MSG_RETRY_FLAG_U8;




typedef struct
{
    VOS_UINT8                           ucBufferNum;
    VOS_UINT8                           aucReserved1[3];
}MN_MSG_SMS_BUFFER_CAP_STRU;

typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           ucRecIndex;                             /*操作USIM的记录数*/
    VOS_UINT16                          usEfId;                                 /*操作文件的ID*/
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType;                           /*操作是Delete时才有效*/
    MN_MSG_USIM_ACTION_ENUM_U8          enSmaUsimAction;                        /*对USIM进行的操作调用的函数*/
}MN_MSG_USIM_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bCreateNode;                                  /*该记录是否已被使用*/
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
}MN_MSG_WRITE_USIM_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;                                  /*该记录是否已被使用*/
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
}MN_MSG_SET_USIM_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucUsimStatus;                           /*SIM卡状态*/
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;                           /*标识是否在上电过程中*/
    VOS_UINT8                           aucReserve[2];
} MN_MSG_USIM_STATUS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmssFlag;                            /*是否支持EFSMSS文件*/
    VOS_BOOL                            bEfSmsFlag;                             /*SMS Storage 存在与否*/
    VOS_BOOL                            bEfSmsrFlag;                            /*SMSR Storage 存在与否*/
    VOS_BOOL                            bEfSmspFlag;                            /*SMSP 存在与否*/
    VOS_BOOL                            bMoSmsCtrlFlag;                         /*是否支持MO-SMS Control by USIM*/
    VOS_BOOL                            bSmsPpDataFlag;                         /*是否支持Data download via SMS-PP*/
}MN_MSG_USIM_EFUST_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucEfSmssNeedRefreshFlag;                            /*EFSMSS文件是否需要更新*/
    VOS_UINT8                           ucEfSmsNeedRefreshFlag;                             /*SMS Storage 文件是否需要更新*/
    VOS_UINT8                           ucEfSmsrNeedRefreshFlag;                        /*SMSR Storage文件是否需要更新*/
    VOS_UINT8                           ucEfSmspNeedRefreshFlag;                            /*SMSP文件是否需要更新*/
}MN_MSG_USIM_EFUST_NEED_REFRESH_STRU;



typedef struct
{
    VOS_BOOL                            bUsed;                                  /*该记录是否有效*/
    MN_MSG_SRV_PARAM_STRU               stParm;                                 /*EFSMSP的内容*/
}MN_MSG_USIM_EFSMSP_DTL_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucLastUsedTpMr;                         /*前一次使用的MR值*/
    MN_MSG_MEM_FLAG_ENUM_U8             enMemCapExcNotFlag;                     /*存储器能力溢出通知标志*/
    VOS_UINT8                           aucRFU[253];
}MN_MSG_SMSS_INFO_STRU;

typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState;                           /*Mo时SMA状态*/
    VOS_BOOL                            bEnvelopePending;                       /*MO SMS CONTROL功能启动时,是否正在等待USIM的回复*/
    VOS_UINT8                           ucMr;                                   /*Msg Reference*/
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea;                             /*保存的位置,USIM,NVIM或是不保存*/
    VOS_UINT32                          ulSaveIndex;                            /*存入USIM或NVIM的索引号*/
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType;
    MN_MSG_MO_TYPE_ENUM_U8              enSmsMoType;                            /*表明是发送短信还是SMMA*/
    VOS_UINT8                           aucReserve1[2];
    VOS_BOOL                            bReportFlag;                            /*表明是否需要上报,仅对SMMA有效*/
    VOS_BOOL                            bStaRptInd;
    VOS_UINT8                           aucRpDataInfo[MN_MSG_MAX_RPDATA_LEN];   /*23040 7.3.1.2 RP DATA (Mobile Station to Network)的数据或23040 7.3.2 RP SMMA的数据*/
    VOS_UINT8                           ucRpDataLen;
    VOS_UINT8                           aucReserve2[3];
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
} MN_MSG_MO_ENTITY_STRU;

typedef struct
{
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState;
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;
    MN_MSG_RCV_DOMAIN_ENUM_U8           enRcvDomain;
    VOS_UINT8                           aucReserve[1];
    MN_MSG_DCS_CODE_STRU                stDcs;
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
}MN_MSG_MT_ENTITY_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;                                  /*是否使用*/
    MN_MSG_MO_ENTITY_STRU               stMoInfo;                               /*短信信息*/
    VOS_UINT8                           aucEfSmContent[MN_MSG_EFSMS_LEN];
}MN_MSG_STORE_MSG_STRU;


typedef struct
{
    VOS_UINT32                          ulTotal;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer;
}MN_MSG_MO_BUFFER_STRU;

typedef struct
{
    VOS_UINT32                          ulRetryPeriod;                          /*短信重发的周期*/
    VOS_UINT32                          ulRetryInterval;                        /*短信重发的时间间隔*/
    VOS_UINT8                           ucSmsRetryCmSrvRejNum;
    VOS_UINT8                           aucSmsRetryCmSrvRejCause[TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM];
}MN_MSG_RETRY_INFO_STRU;

typedef struct
{
    VOS_UINT8                           aucRpDataInfo[MN_MSG_MAX_RPDATA_LEN];   /*23040 7.3.1.2 RP DATA (Network to Mobile Station*/
    VOS_UINT8                           ucRpDataLen;
    VOS_UINT8                           aucReserve[3];
}MN_MSG_RP_ERR_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;
    MN_MSG_BCD_ADDR_STRU                stOrgAddr;
    MN_MSG_BCD_ADDR_STRU                stDestAddr;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
}MN_MSG_RP_DATA_STRU;

typedef struct
{
    VOS_BOOL                            bRpUserDataExist;
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;
    VOS_UINT8                           ucRpUserDataIei;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
}MN_MSG_RP_ACK_STRU;


typedef struct
{
    VOS_BOOL                            bRpUserDataExist;
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;                                 /*无意义待删除*/
    VOS_UINT8                           ucRpUserDataIei;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
    VOS_UINT8                           ucRpCauseLen;
    MN_MSG_RP_CAUSE_STRU                stRpCause;
}MN_MSG_RP_ERR_STRU;

enum
{
    MN_MSG_WRITE_EFSMS_CAUSE_OK,
    MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL,
    MN_MSG_WRITE_EFSMS_CAUSE_MEM_PROBLEM,
    MN_MSG_WRITE_EFSMS_CAUSE_UNSEPCIFIC,
    MN_MSG_WRITE_EFSMS_CAUSE_MAX
};
typedef VOS_UINT32 MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32;

/*******************************************************************************
 结构名    : MN_MSG_STORAGE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信或状态报告接收处理方式,存储介质,文件ID,记录在文件中的索引
*******************************************************************************/
typedef struct
{
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /* action of received status report */
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /* memory store: NVIM or USIM of received msg*/
    VOS_UINT16                          usFileIndex;                            /* file id: EFSMS or EFSMSR */
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT32                          ulIndex;                                /* index of  status report in file */
}MN_MSG_STORAGE_INFO_STRU;


typedef struct
{

    TAF_FDN_CONFIG_STRU                 stFdnConfig;
}TAF_MSG_FDN_INFO_STRU;

/*****************************************************************************
  4 宏定义
*****************************************************************************/

/*****************************************************************************
  5 接口函数声明
*****************************************************************************/
extern VOS_UINT8                            g_ucSetEfSmsFail;
extern VOS_UINT8                            g_ucNasSmsPsConcatencateFlag;
#if ( VOS_WIN32 == VOS_OS_VER )
extern VOS_UINT8                            g_ucSetEfSmsCapacity;
extern VOS_UINT8                            g_ucSetEfSmssClear;
extern VOS_UINT8                            g_ucSetEfSmspNoRsp;
extern VOS_UINT8                            g_ucSetEfSmsNoResponse;
extern VOS_UINT8                            g_ucDisableMoRetry;
extern MN_MSG_CLASS0_TAILOR_U8              g_enClass0Tailor;
extern VOS_UINT8                            g_ucPpDownloadStub;
#endif





VOS_VOID MN_MSG_SetSmsFileRefreshFlag (VOS_UINT16 usEfId, VOS_UINT8 ucFileRefreshFlag);


VOS_UINT8 MN_MSG_GetSmsFileRefreshFlag (VOS_UINT16 usEfId);



VOS_UINT32 MN_MSG_CheckUsimStatus(VOS_VOID);


MN_MSG_MO_STATE_ENUM_U8 MN_MSG_GetMoState(VOS_VOID);


VOS_VOID MN_MSG_SetMoRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  enMsgSignallingType
);


TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMoRouteStackType(VOS_VOID);


MN_MSG_MT_STATE_ENUM_U8 MN_MSG_GetMtState(VOS_VOID);

VOS_VOID TAF_MSG_SetMtState(
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState
);


VOS_VOID MN_MSG_SetMtRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  enMsgSignallingType
);


TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMtRouteStackType(VOS_VOID);


VOS_VOID MN_MSG_GetMoEntity(
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
);


VOS_VOID MN_MSG_CreateMoInfo(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity
);


VOS_VOID MN_MSG_GetTpMR(
    VOS_UINT8                           *pucTpMr
);


VOS_VOID MN_MSG_AddTpMR(VOS_VOID);


VOS_UINT32 MN_MSG_GetStoreMsgIndex(VOS_VOID);


VOS_VOID  MN_MSG_SaveStoreMsg(
    VOS_UINT32                          ulIndex,
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const VOS_UINT8                     *pucEfSmContent
);


VOS_UINT32  MN_MSG_GetStoreMsg(
    MN_MSG_STORE_MSG_STRU               *pstStoreMsg
);


VOS_VOID  MN_MSG_FreeStoreMsg(
    VOS_UINT32                          ulIndex
);


VOS_UINT32 MN_MSG_ProcMoCtrl(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    const VOS_UINT8                     aucRpDataInfo[]
);


VOS_VOID MN_MSG_DestroyMoInfo(VOS_VOID);


VOS_VOID MN_MSG_CreateMtInfo(VOS_VOID);


VOS_VOID MN_MSG_DestroyMtInfo(VOS_VOID);


VOS_UINT32 MN_MSG_CreateNewUsimNode(
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
);

/*清空内存中索引为ucIndex的USIM节点相关信息*/

VOS_VOID MN_MSG_DestroyUsimNode(
    VOS_UINT32                          ulIndex
);

VOS_VOID MN_MSG_UpdateUstInfo(
);

VOS_UINT32 MN_MSG_MoFeatureAvailable(VOS_VOID);


VOS_VOID MN_MSG_UpdateSmssInfo(
    VOS_BOOL                            bEfSmssState,
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo,
    VOS_UINT32                          ulFileLen
);


VOS_UINT32  MN_MSG_ReadSmssInfo(
    MN_MSG_SMSS_INFO_STRU               *pstSmssInfo
);


VOS_VOID MN_MSG_Internal_SendRpt(
    VOS_BOOL                            bRpAck   ,                              /*is Rp-Ack or Rp-Error*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause,                              /*used when bRpAck==FALSE*/
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause                               /*TP-Cause*/
);


VOS_VOID  MN_MSG_GetCurCfgParm(
    MN_MSG_CONFIG_PARM_STRU             *pstCfgParm
);


VOS_VOID  MN_MSG_UpdateRegState(
    VOS_UINT8                           ucDomain,
    VOS_BOOL                            bAttachFlag
);


VOS_VOID  MN_MSG_UpdateTotalSmspInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucNumofSmsp,
    VOS_UINT8                           ucEfLen,
    const VOS_UINT8                     *pucSmspContent
);


VOS_VOID  MN_MSG_UpdateEachMemSmInfo(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsLen
);


VOS_VOID  MN_MSG_UpdateSmsInfo(
    VOS_BOOL                            bEfSmsState,
    VOS_UINT8                           ucEFSmNum
);


VOS_VOID   MN_MSG_ReadUstInfo(
    MN_MSG_USIM_EFUST_INFO_STRU         *pstEfUstInfo
);


VOS_VOID  MN_MSG_UpdateUsimStateInfo(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState
);


VOS_VOID MN_MSG_UpdateMoSaveInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea,
    VOS_UINT32                          ulSaveIndex
);


VOS_UINT32 MN_MSG_StartMo(
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penSendDomain
);


VOS_VOID MN_MSG_StartMemNotification(VOS_VOID);


VOS_VOID MN_MSG_SendMemAvail(VOS_VOID);


VOS_BOOL MN_MSG_IsUsimFileExist(
    VOS_UINT16                          usEfId
);


VOS_UINT32 MN_MSG_ReadSmsInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmContent
);


VOS_UINT32 MN_MSG_ReadSmsrInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsrContent
);


VOS_VOID  MN_MSG_UpdateEachMemSmsrInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsrLen
);


VOS_VOID MN_MSG_UpdateEachMemSmspInfo(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bUsed,
    const MN_MSG_SRV_PARAM_STRU         *pstScvParm
);


VOS_UINT32 MN_MSG_ReadSmspInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    MN_MSG_SRV_PARAM_STRU                *stSrvParm
);


VOS_VOID MN_MSG_GetSmStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    VOS_UINT32                          *pulEachStatusRec
);


VOS_UINT32 MN_MSG_GetStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucStatus
);


VOS_UINT32 MN_MSG_GetAvailSmRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_UINT32 MN_MSG_GetAvailSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_UINT8 MN_MSG_GetAvailSmspRecIndex(VOS_VOID);


VOS_UINT32 MN_MSG_GetReplaceSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_VOID  MN_MSG_GetUsimPowerState(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     *penPowerState
);

VOS_UINT32 MN_MSG_GetSmCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_UINT32 MN_MSG_GetSmspCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_UINT32 MN_MSG_GetSmsrCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_BOOL MN_MSG_IsValidSmIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex
);


VOS_BOOL MN_MSG_IsValidSmspIndex(
    VOS_UINT8                           ucIndex
);


VOS_BOOL MN_MSG_IsEmptySmsp(
    VOS_UINT8                           ucIndex
);


VOS_VOID  MN_MSG_GetCurRcvMsgPath(
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    *pstRcvPath
);


VOS_UINT32  MN_MSG_UpdateRcvMsgPath(
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPath
);


VOS_BOOL  MN_MSG_GetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType
);


VOS_VOID  MN_MSG_SetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_BOOL                            bReportFlag
);


VOS_VOID   MN_MSG_GetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penRealSendDomain
);


VOS_VOID  MN_MSG_GetCurAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             *penMemStatus
);


VOS_UINT32  MN_MSG_UpdateAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             enMemStatus
);


VOS_UINT32  MN_MSG_FindNodeByUsimResult(
    VOS_UINT8                           ucRecIndex,
    VOS_UINT16                          usEfId,
    MN_MSG_USIM_INFO_STRU               *pSmaUsimInfo,
    VOS_UINT32                          *pulIndex
);


VOS_UINT8  MN_MSG_GetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType
);


VOS_VOID  MN_MSG_SetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_UINT8                           ucRec
);


VOS_BOOL MN_MSG_GetSmsMoCtrlPend(VOS_VOID);


VOS_VOID MN_MSG_UpdateSmaMoState(
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState
);


VOS_UINT32  MN_MSG_MoSmsControlEnvelopeReq(
    VOS_UINT16                          usClientId,
    MN_MSG_BCD_ADDR_STRU               *pstRpDestAddr,
    MN_MSG_BCD_ADDR_STRU               *pstTpDestAddr
);




VOS_UINT32  MN_MSG_SmsPPEnvelopeReq(
    const MN_MSG_BCD_ADDR_STRU          *pstAddr,
    const VOS_UINT8                     *pucTpduData,
    const VOS_UINT32                    ulTpduLen
);


VOS_UINT32  MN_MSG_SendSmma(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bReportFlag,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);



VOS_VOID  MN_MSG_WriteSmssFile(
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo
);

#if ((NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON))
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const VOS_UINT32                   *pulMeIndex,
    const MN_MSG_WRITE_USIM_INFO_STRU  *pstWriteUsimInfo,
    VOS_UINT8                          *pucContentInfo
);

#else

VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            bCreateNode,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
);
#endif



VOS_UINT32  MN_MSG_WriteSmsrFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
);


VOS_UINT32  MN_MSG_WriteSmspFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    const MN_MSG_SRV_PARAM_STRU          *stSrvParm
);


VOS_VOID  MN_MSG_RecoverOrgSrvParm(
    VOS_UINT8                           ucIndex,
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSrvParam
);


VOS_VOID  MN_MSG_RecoverOrgSm(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmContent
);


VOS_VOID  MN_MSG_RecoverOrgSmsr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmsrContent
);


VOS_VOID MN_MSG_CreateEFSmContent(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucStatus,
    VOS_UINT8                           *pucContent
);


VOS_UINT32 MN_MSG_ParseEFSmContent(
    const VOS_UINT8                     *pucContent,
    MN_MSG_BCD_ADDR_STRU                *pstScAddr,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData,
    VOS_UINT8                           *pucStatus
);


VOS_VOID MN_MSG_GetAppStatus(
    VOS_UINT8                           ucStatus,
    MN_MSG_STATUS_TYPE_ENUM_U8          *penStatus
);


VOS_VOID MN_MSG_GetPsStatus(
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    VOS_UINT8                           *pucStatus
);


VOS_VOID  MN_MSG_UpdateTotalSmsrInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucSmsrRec,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           *pucSmspContent
);


VOS_VOID MN_MSG_GetSmsrStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec
);

/***********************************************************************
函 数 名  : MN_MSG_GetSmspStorageList
功能描述  : 获取当前USIM或NVIM中短信参数的storage list
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : pusTotalRec:当前存储器的总容量
            psUsedRec:当前存储器的已用空间
返 回 值  : 无
************************************************************************/
VOS_VOID MN_MSG_GetSmspStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    MN_MSG_SRV_PARAM_STRU                *pstSrvParam
);


VOS_UINT32 MN_MSG_DeleteMultiSm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT32                          *pulDeleteCount
);


VOS_UINT32  MN_MSG_DeleteMultiStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT8                           *pucDeleteCount
);



VOS_VOID MSG_BuildDeliverEvtParm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_DELIVER_EVT_INFO_STRU        *pstDeliverEvt
);


MN_OPERATION_ID_T  MN_MSG_GetBCopId(VOS_VOID);


VOS_VOID MN_MSG_GetUsimParmReq(
    VOS_UINT16                          usEfId
);


VOS_VOID MN_MSG_SmInit(VOS_VOID);

VOS_VOID  MN_MSG_ReadMsgNvimInfo( VOS_VOID );


VOS_VOID MN_MSG_SmCfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
);


MN_MSG_LINK_CTRL_U8 MN_MSG_GetLinkCtrlParam(VOS_VOID);


VOS_UINT32 MN_MSG_UpdateLinkCtrlParam(
    MN_MSG_LINK_CTRL_U8                 setValue
);


VOS_VOID MN_MSG_InitSmsServiceData(MN_MSG_CONFIG_PARM_STRU  *pstServicePara);



VOS_VOID MN_MSG_UpdateNeedSendUsim(
    VOS_UINT32                          ulInedx,
    VOS_BOOL                            bUpdateStatus
);


VOS_VOID MN_MSG_GetNeedSendUsim(
    VOS_UINT32                          *pulRealRec,
    VOS_BOOL                            *pbNeedSendUsim
);

/*****************************************************************************
*  Prototype       : MN_MSG_FailToWriteEfsms
*  Description     : 短信写SIM卡的EFSMS文件失败后,MS按协议要求回复网络RP-ERROR并修改EFSMSS文件；
*  Input           : enMemStore  --- 发生存储失败的存储介质类型
                     ucFailCause --- 当前存储失败的原因
                        存储区满；
                        存储区不可用；
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-04-12
*     Author       : 傅映君
*     Modification : Created function
*****************************************************************************/
VOS_VOID MN_MSG_FailToWriteEfsms(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32   enFailCause
);

/*****************************************************************************
*  Prototype       : MN_MSG_UpdateSendFailFlag
*  Description     : 更新当前发送失败的域
*  Input           : enSendFailFlag --- 当前发送失败的域;
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 VOS_VOID MN_MSG_UpdateSendFailFlag(
 	MN_MSG_SEND_FAIL_FLAG_U8			enSendFailFlag
 );


VOS_VOID MN_MSG_GetRetryInfo(
    MN_MSG_RETRY_INFO_STRU              *pstRetryInfo
);

/*****************************************************************************
*  Prototype       : MN_MSG_GetSendFailFlag
*  Description     : 获取当前发送失败的域
*  Input           : 无;
*  Output          :
*  Return Value    : 当前发送失败的域
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 MN_MSG_SEND_FAIL_FLAG_U8 MN_MSG_GetSendFailFlag(VOS_VOID);


VOS_VOID  MN_MSG_RcvSmsRpRpt(SMR_SMT_MO_REPORT_STRU *pstMsg);


VOS_VOID MN_MSG_SaveRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg);


VOS_VOID MN_MSG_GetRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg);


MN_MSG_CLASS0_TAILOR_U8 MN_MSG_GetClass0Tailor(VOS_VOID);


VOS_VOID MN_MSG_SetClass0Tailor(MN_MSG_CLASS0_TAILOR_U8                 enClass0Tailor);


MN_MSG_SEND_DOMAIN_ENUM_U8  MN_MSG_GetRealPrefSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeDomain
);


VOS_VOID  MN_MSG_GetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid,
    MN_MSG_DCS_CODE_STRU                *pstDcs
);


VOS_VOID  MN_MSG_SetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_DCS_CODE_STRU                stDcs
);


VOS_VOID MN_MSG_RptMsg(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList,
    MN_MSG_LIST_EVT_INFO_STRU           *pstListRptEvt
);



VOS_VOID  MN_MSG_InitRcvPath( VOS_VOID );

/***  All the following functions are defined in MnMsgReqProc.c  ***/
extern VOS_UINT32  MSG_ChangeSmStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_USIM_ACTION_ENUM_U8          enAction,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsContent,
    VOS_UINT8                           *pucChangeNum
);

VOS_UINT32 MN_MSG_ReadMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
);
VOS_UINT32 MN_MSG_WriteMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
);

VOS_VOID MN_MSG_CsDomainAvailable(VOS_BOOL *pbCsDomainAvailable);

VOS_VOID MN_MSG_DeliverMsgNotSupport(
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_BOOL                            *pbSupportFlag,
    MN_MSG_TP_CAUSE_ENUM_U8             *penTpCause
);

VOS_VOID MN_MSG_MtSpecificFeatureInit(VOS_VOID);

VOS_VOID MN_MSG_GetReplaceFeature(VOS_UINT8 *pucActFlg);


VOS_VOID MN_MSG_GetCloseSMSFeature(VOS_UINT8 *pucActFlg);

VOS_VOID MN_MSG_CloseSmsCapabilityFeatureInit(VOS_VOID);

VOS_VOID MN_MSG_SetCloseSMSFeature(VOS_UINT8 ucActFlg);


VOS_UINT32 MN_MSG_MoCtrlAllowedWithModification(
    SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);

/*****************************************************************************
 Prototype      : GMM_GetCurNetwork
 Description    : 获取GMM的当前工作网络
                  HSS 4100 V200R001 新增
                  非GMM模块使用
 Input          :
 Output         :
 Return Value   : GMM工作网络
                  GMM_RABM_CURNET_3G    3G网络
                  GMM_RABM_CURNET_2G    2G网络
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/VOS_UINT8 GMM_GetCurNetwork (VOS_VOID);

VOS_VOID TAF_MMA_GetRegStateInfo( TAF_PH_REG_STATE_STRU *pstCurRegInf );


VOS_VOID MN_MSG_SendMsgToSms(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);


VOS_UINT32 MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl(
    SI_STK_ENVELOPEDWON_CNF_STRU        *pstEnvelope,
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
);


VOS_VOID MN_MSG_RcvUsimMoControlRsp(
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
);


VOS_VOID  MN_MSG_RcvUsimEnvelopRsp(
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
);


VOS_UINT32 MN_MSG_SendFdnCheckInfo(MN_MSG_MO_ENTITY_STRU *pstMoEntity);


VOS_UINT32 MN_MSG_CheckMoSmsCtrl(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbCheckMoCtrl
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32  MN_MSG_IsLteNeedSmsRetry(
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause
);

#endif

VOS_UINT32  MN_MSG_IsGuNeedSmsRetry(
    SMR_SMT_ERROR_ENUM_UINT32           enErrCause
);


VOS_VOID MN_MSG_InitMoBuffer(VOS_VOID);


VOS_UINT32 MN_MSG_GetMoBufferCap(VOS_VOID);


VOS_UINT32 MN_MSG_GetSpecificStatusMoEntity(
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus,
    VOS_BOOL                           *pbBufferEntity,
    VOS_UINT32                         *pulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);


VOS_VOID MN_MSG_UpdateSpecificMoEntityStatus(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus
);


VOS_VOID MN_MSG_CreateMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_UINT8                           aucEfSmContent[]
);


VOS_VOID MN_MSG_DestroySpecificMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex
);


VOS_UINT32 MN_MSG_CheckMoMsg(
    VOS_UINT8                           aucEfSmContent[],
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbRequireCheck,
    VOS_BOOL                           *pbBufferEntity
);


VOS_VOID MN_MSG_GetMtCustomizeInfo(MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize);


VOS_VOID MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag);


VOS_VOID MN_MSG_SetTpRd(MN_MSG_MO_ENTITY_STRU *pstMoEntity);

VOS_VOID TAF_MSG_SetUsimStatus(
    VOS_UINT8                           ucUsimStatus
);
VOS_UINT8 TAF_MSG_GetUsimStatus(VOS_VOID);
VOS_VOID TAF_MSG_UpdateMtRcvDomain(
    VOS_UINT8                           ucRcvDomain
);
MN_MSG_RCV_DOMAIN_ENUM_U8 TAF_MSG_GetMtRcvDomain(VOS_VOID);


VOS_UINT8 MN_MSG_StartLinkCtrl(VOS_VOID);

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

#endif /* __MNMSGCOMMPROC_H__ */

