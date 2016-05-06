/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmOmMsgProc.h
  Description     : NasEsmOmMsgProc.c header file
  History         :
     1.sunbing       2008-12-30     Draft Enact
     2.
******************************************************************************/

#ifndef __NASESMOMMSGPROC_H__
#define __NASESMOMMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "OmCommon.h"
#include    "LnasFtmInterface.h"
#include    "LnasErrlogInterface.h"


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
#define NAS_ESM_LEN_VOS_MSG_HEADER          20
#define NAS_ESM_GetFtmInfoManageAddr()      (&(g_astEsmFtmInfoManage))
#define NAS_ESM_GetEsmInfoAddr()            (&(g_astEsmInfo))
#define NAS_ESM_GetFtmInfoActionFlag()      (NAS_ESM_GetFtmInfoManageAddr()->ulFtmActionFlag)
#define NAS_ESM_GetFtmInfoMsgSN()           (NAS_ESM_GetFtmInfoManageAddr()->ulMsgSN)
#define NAS_ESM_GetFtmInfoEsmCause()        (NAS_ESM_GetFtmInfoManageAddr()->ucEsmCause)
#define NAS_ESM_SetFtmOmManageFtmActionFlag(Flag)  (NAS_ESM_GetFtmInfoActionFlag() = Flag)

#define NAS_ESM_GetErrlogManageAddr()       (&(g_astEsmErrlogInfoManage))
#define NAS_ESM_GetErrlogActionFlag()       (NAS_ESM_GetErrlogManageAddr()->ulActionFlag)
#define NAS_ESM_SetErrlogActionFlag(Flag)   (NAS_ESM_GetErrlogActionFlag() = Flag)
#define NAS_ESM_GetErrlogMsgSN()            (NAS_ESM_GetErrlogManageAddr()->ulMsgSN)
#define NAS_ESM_GetErrlogAlmLevel()         (NAS_ESM_GetErrlogManageAddr()->usALMLevel)
#define NAS_ESM_SetErrlogAlmLevel(usLevel)  (NAS_ESM_GetErrlogAlmLevel() = usLevel)
#define NAS_ESM_GetErrlogAlmType()          (NAS_ESM_GetErrlogManageAddr()->usALMType)
#define NAS_ESM_GetErrlogAlmLowSlice()      (NAS_ESM_GetErrlogManageAddr()->ulAlmLowSlice)
#define NAS_ESM_GetErrlogAlmHighSlice()     (NAS_ESM_GetErrlogManageAddr()->ulAlmHighSlice)
#define NAS_ESM_GetErrlogAmount()           (NAS_ESM_GetErrlogManageAddr()->ulErrLogAmount)
#define NAS_ESM_GetErrlogNextNullPos()      (NAS_ESM_GetErrlogManageAddr()->ulNextNullPos)
#define NAS_ESM_GetErrlogInfo(ulIndex)      (NAS_ESM_GetErrlogManageAddr()->stEsmErrInfoDetail[ulIndex])
#define NAS_ESM_ERRLOG_MAX_NUM  (4)

#define NAS_ESM_COMP_OM_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_ESM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = MSP_PID_DIAG_APP_AGENT;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_ESM_TP_CMD_TYPE_ENUM
 枚举说明  : 命令类型取值
*****************************************************************************/
enum    NAS_ESM_TP_CMD_TYPE_ENUM
{
    NAS_ESM_TP_CMD_TYPE_TEST            = 0x00,

    NAS_ESM_TP_CMD_TYPE_BUTT
};
typedef VOS_UINT8   NAS_ESM_TP_CMD_TYPE_ENUM_UINT8 ;

/*****************************************************************************
 枚举名    : NAS_ESM_AIR_MSG_DIR_ENUM
 枚举说明  : 命令类型取值
*****************************************************************************/
enum    NAS_ESM_AIR_MSG_DIR_ENUM
{
    NAS_ESM_AIR_MSG_DIR_ENUM_UP         = 0x00,
    NAS_ESM_AIR_MSG_DIR_ENUM_DOWN             ,

    NAS_ESM_AIR_MSG_DIR_BUTT
};
typedef VOS_UINT8   NAS_ESM_AIR_MSG_DIR_ENUM_UINT8 ;

enum    NAS_ESM_FTM_ACTION_FLAG_ENUM
{
    NAS_ESM_FTM_ACTION_FLAG_CLOSE = 0,
    NAS_ESM_FTM_ACTION_FLAG_OPEN = 1,
    NAS_ESM_FTM_ACTION_FLAG_BUTT
};
typedef VOS_UINT32  NAS_ESM_FTM_ACTION_FLAG_ENUM_UINT32;

enum NAS_ESM_ERRLOG_LEVEL_ENUM
{
    NAS_ESM_ERRLOG_LEVEL_CRITICAL   = 1,/*代表紧急*/
    NAS_ESM_ERRLOG_LEVEL_MAJOR      = 2,/*代表重要*/
    NAS_ESM_ERRLOG_LEVEL_MINOR      = 3,/*代表次要*/
    NAS_ESM_ERRLOG_LEVEL_WARING     = 4,/*代表提示，*/
    NAS_ESM_ERRLOG_LEVEL_BUTT
};
typedef VOS_UINT16  NAS_ESM_ERRLOG_LEVEL_ENUM_UINT16;

/* ERROR LOG故障&警告类型*/
enum NAS_ESM_ERRLOG_TYPE_ENUM
{
    NAS_ESM_ERRLOG_TYPE_COMMUNICATION       = 0x00, /* 通信     */
    NAS_ESM_ERRLOG_TYPE_SERVING_QUALITY     = 0x01, /* 业务质量 */
    NAS_ESM_ERRLOG_TYPE_PROCESS_ERROR       = 0x02, /* 处理出错 */
    NAS_ESM_ERRLOG_TYPE_EQUIPMENT_TROUBLE   = 0x03, /* 设备故障 */
    NAS_ESM_ERRLOG_TYPE_ENVIRONMENT_TROUBLE = 0x04, /* 环境故障 */
};
typedef VOS_UINT16 NAS_ESM_ERRLOG_TYPE_ENUM_UINT16;


enum NAS_ESM_ERRLOG_ACTION_FLAG_ENUM
{
    NAS_ESM_ERRLOG_ACTION_FLAG_CLOSE  = 0,
    NAS_ESM_ERRLOG_ACTION_FLAG_OPEN   = 1,
    NAS_ESM_ERRLOG_ACTION_FLAG_BUTT
};
typedef VOS_UINT32  NAS_ESM_ERRLOG_ACTION_FLAG_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_ESM_TRANSPARENT_CMD_REQ_STRU
 结构说明  : OMT->ESM的透明命令下发结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /*原语类型*/
    APP_MSG_HEADER

    NAS_ESM_TP_CMD_TYPE_ENUM_UINT8      enEsmTpCmdType;
    VOS_UINT8                           aucRsv[3];
}NAS_ESM_TRANSPARENT_CMD_REQ_STRU;


typedef struct
{
    /* 取值和含义见 24301 9.9.4.4 */
    VOS_UINT8                           ucEsmCause;
    VOS_UINT8                           aucRsv[3];
}ESM_DATABASE_INFO_STRU;

typedef struct
{
    /* 打开或者关闭工程模式上报功能 0:close 1:open*/
    VOS_UINT32                          ulFtmActionFlag;
    /* ESM给OM发送的每个工程模式消息都有此编号，上电为0，然后依次加 1 */
    VOS_UINT32                          ulMsgSN;
    /* ESM工程模式管理结构临时存储CnCause，用于与本地数据库进行比对 */
    VOS_UINT8                           ucEsmCause;
    VOS_UINT8                           aucRsv[3];

}ESM_FTM_INFO_MANAGE_STRU;


typedef struct
{
   NAS_OM_ACT_PDP_INFO_STRU            stActPdpInfo;
}APP_ESM_DT_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_OM_LOG_REG_CID_INFO_STRU
 结构说明  : ESM向OM输出的可维可测的注册时选择的CID
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;        /*_H2ASN_Skip*/

    VOS_UINT32                                    ulRegCid;
} NAS_ESM_OM_LOG_REG_CID_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32                  g_NasEsmOmInfoIndFlag;

extern ESM_FTM_INFO_MANAGE_STRU             g_astEsmFtmInfoManage;
extern ESM_DATABASE_INFO_STRU               g_astEsmInfo;

extern VOS_UINT32   g_ulRptPdpStatus;
extern VOS_UINT32   g_ulNasEsmOmMsgHookFlag;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID     NAS_ESM_OmInfoIndProc(VOS_VOID);
extern VOS_VOID     NAS_ESM_FtmInfoInit(VOS_VOID);
extern VOS_UINT32   NAS_ESM_RevOmFtmCtrlMsg(MsgBlock   *pMsgStru);
extern VOS_UINT32   NAS_ESM_CompareEsmDatabaseInfo(VOS_VOID);
extern VOS_VOID     NAS_ESM_UpdateEsmDatabaseInfo(VOS_VOID);
extern VOS_VOID     NAS_ESM_SendOmFtmMsg(VOS_VOID);

//extern VOS_VOID NAS_ESM_OmMsgDistrForAcpuPidOm( VOS_VOID *pRcvMsg );





/*****************************************************************************
  9 OTHERS
*****************************************************************************/

extern VOS_VOID NAS_ESM_SndAirMsgReportInd
(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLength,
    NAS_ESM_AIR_MSG_DIR_ENUM_UINT8      enMsgDir,
    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId
);
extern VOS_VOID NAS_ESM_SndEsmOmTpCmdCnfMsg(const VOS_UINT8 *pucData,
                                                               VOS_UINT32 ulLength);
extern VOS_VOID NAS_ESM_SndKeyEventReportInd(OM_PS_KEY_EVENT_ENUM_UINT8 enKeyEvent);
extern VOS_VOID NAS_ESM_TransparentMsgProc( VOS_VOID* pRcvMsg );
extern VOS_VOID NAS_ESM_OmMsgDistr
(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_OmInfoIndMsgProc(VOS_VOID *pRcvMsg);
extern VOS_UINT32 LTE_MsgHook(VOS_VOID * pMsg);
/*niuxiufan DT end */

extern VOS_VOID NAS_ESM_ReportActPdpInfo( VOS_VOID);

extern VOS_VOID NAS_ESM_SndOmRegCidInfo(VOS_UINT32  ulRegCid);








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

#endif /* end of NasEsmOmMsgProc.h */
