/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasMntn.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年7月4日
  最近修改   :
  功能描述   : CnasMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月4日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_MNTN_H__
#define __CNAS_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "UsimPsInterface.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "msp_diag_comm.h"
#include  "NasOmInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 打印记录的条数 */
#define CNAS_MNTN_PRINT_MSG_MAX_NUM                         (10)

/* 获取MNTN上下文地址 */
#define CNAS_MNTN_GetCtxAddr()                              (&g_stCnasMntnCtx)

/* 获取打印控制信息地址 */
#define CNAS_MNTN_GetPrintCtrlInfoAddr()                    (&((CNAS_MNTN_GetCtxAddr())->stPrintCtrlInfo))

/* 获取打印消息缓存地址 */
#define CNAS_MNTN_GetPrintMsgAddr()                         (&((CNAS_MNTN_GetCtxAddr())->stPrintMsg))

/* 获取打印类型: 串口或者SDT */
#define CNAS_MNTN_GetPrintType()                            ((CNAS_MNTN_GetPrintCtrlInfoAddr())->enPrintType)

/* 获取Info级别打印控制开关 */
#define CNAS_MNTN_GetInfoPrintFlg()                         ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulInfoPrintFlg)

/* 获取Normal级别打印控制开关 */
#define CNAS_MNTN_GetNorPrintFlg()                          ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulNorPrintFlg)

/* 获取WARNING级别打印控制开关 */
#define CNAS_MNTN_GetWarnPrintFlg()                         ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulWarnPrintFlg)

/* 获取ERR级别打印控制开关 */
#define CNAS_MNTN_GetErrPrintFlg()                          ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulErrPrintFlg)

#define CNAS_MNTN_LOG_AIR_MSG_OFFSET                        (4)

#define CNAS_INFO_LOG(Mod,String)   { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_NORMAL_LOG(Mod,String)   { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_WARNING_LOG(Mod,String)   { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_WARNING_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_WARNING_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_WARNING_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }


#define CNAS_WARNING_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_ERROR_LOG(Mod,String)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

/* 封装发送事件消息头 */
#define CNAS_CFG_MSG_HDR(pstMsg, ulSendPid, ulReceiPid, enEventId, ulEventLen)\
        (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
        (pstMsg)->ulSenderPid     = ulSendPid;\
        (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
        (pstMsg)->ulReceiverPid   = ulReceiPid;\
        (pstMsg)->ulLength        = (ulEventLen);\
        (pstMsg)->enMsgId         = (enEventId)


#define CNAS_SoftReboot(stCnasRebootInfo) CNAS_SoftReBoot_WithLineNoAndFileID( (__LINE__), (THIS_FILE_ID), (stCnasRebootInfo))

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_MNTN_MSG_ID_BASE_ENUM
 结构说明  : CNAS各模块发送给OM的可维可测消息
  1.日    期   : 2014年07月04日
    作    者   : l60609
    修改内容   : CNAS各模块发送给OM的可维可测消息
*****************************************************************************/
enum CNAS_MNTN_MSG_ID_BASE_ENUM
{
    /* 0x6000 ~ 0x6FFF为LOG保留 */
    ID_CNAS_MNTN_LOG_MSG_BASE           = 0x6000,                                   /* LOG模块间可维可测消息起始 */

    /* 0x7000 ~ 0x7FFF为XSD保留 */
    ID_CNAS_MNTN_XSD_MSG_BASE           = 0x7000,                                   /* XSD模块间可维可测消息起始 */

    /* 0x8000 ~ 0x8FFF为PRL保留 */
    ID_CNAS_MNTN_PRL_MSG_BASE           = 0x8000,                                   /* PRL模块可维可测消息起始 */

    /* 0x9000 ~ 0x9FFF为PRL保留 */
    ID_CNAS_MNTN_HSD_MSG_BASE           = 0x9000,                                   /* HSD模块可维可测消息起始 */
    ID_CNAS_MNTN_HSM_MSG_BASE           = 0xa000,

    ID_CNAS_MNTN_MSG_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_MSG_ID_BASE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : CNAS_MNTN_TIMER_ACTION_ENUM
 结构说明  : timer动作
  1.日    期   : 2014年07月11日
    作    者   : y00245242
    修改内容   : 新建
*****************************************************************************/
enum CNAS_MNTN_TIMER_ACTION_ENUM
{
    CNAS_MNTN_TIMER_ACTION_START,

    CNAS_MNTN_TIMER_ACTION_STOP,

    CNAS_MNTN_TIMER_ACTION_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_TIMER_ACTION_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_MNTN_MSG_ID_ENUM
 结构说明  : CNAS各模块发送给OM的可维可测消息
  1.日    期   : 2014年07月04日
    作    者   : l60609
    修改内容   : CNAS各模块发送给OM的可维可测消息
*****************************************************************************/
enum CNAS_MNTN_MSG_ID_ENUM
{
    ID_CNAS_MNTN_LOG_FSM_INFO_IND   = ID_CNAS_MNTN_LOG_MSG_BASE,     /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_FSM_INFO_STRU */

    ID_CNAS_MNTN_LOG_MSG_INFO_IND,                                   /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_MSG_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_TIMER_INFO_IND,                                 /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_TIMER_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ,                         /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU */

    ID_CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND,                       /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND,                       /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU */

    ID_CNAS_DIAG_LOG_READ_NV_INFO_IND,                               /*_H2ASN_MsgChoice  CNAS_DIAG_LOG_NV_INFO_IND_STRU */

    ID_CNAS_DIAG_LOG_WRITE_NV_INFO_IND,                              /*_H2ASN_MsgChoice  CNAS_DIAG_LOG_NV_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND,                         /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_1X_CSCH_DATA_IND,                               /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU */

    ID_CNAS_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_MNTN_PRINT_TYPE_ENUM
 结构说明  : CNAS各模块打印类型:串口打印或者工具(eg:SDT)输出
  1.日    期   : 2014年07月04日
    作    者   : l60609
    修改内容   : CNAS各模块打印类型
*****************************************************************************/
enum CNAS_MNTN_PRINT_TYPE_ENUM
{
    CNAS_MNTN_PRINT_TYPE_SDT,                                                   /* 默认勾到SDT中 */
    CNAS_MNTN_PRINT_TYPE_COM,

    CNAS_MNTN_PRINT_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_PRINT_TYPE_ENUM_UINT32;



enum CNAS_REBOOT_SCENE_ENUM
{
    CNAS_REBOOT_SCENE_TI_XSD_WAIT_CAS_SUSPEND_CNF_EXPIRED,
    CNAS_REBOOT_SCENE_TI_HSD_WAIT_CAS_SUSPEND_CNF_EXPIRED,

    CNAS_REBOOT_SCENE_BUTT
};

typedef VOS_UINT8 CNAS_REBOOT_SCENE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_HANDSET_INFO_TYPE_ENUM
 枚举说明  : 手机信息类型
 1.日    期   : 2015年5月18日
   作    者   : z00316370
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HANDSET_INFO_TYPE_ENUM
{
    CNAS_HANDSET_INFO_TYPE_STATE,
    CNAS_HANDSET_INFO_TYPE_HVERSION,

    CNAS_HANDSET_INFO_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_HANDSET_INFO_TYPE_ENUM_UINT32;

enum    CNAS_HRPD_OM_AIR_MSG_UP_DOWN_ENUM
{
    CNAS_HRPD_OM_AIR_MSG_UP,             /* UPWARD */
    CNAS_HRPD_OM_AIR_MSG_DOWN,             /* DOWNWARD */

    CNAS_HRPD_OM_AIR_MSG_BUTT
};
typedef VOS_UINT8   CNAS_HRPD_OM_AIR_MSG_UP_DOWN_ENUM_UINT8;
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
 结构名    : CNAS_MNTN_LOG_FSM_INFO_STRU
 结构说明  : ID_CNAS_MNTN_LOG_FSM_INFO_IND的消息结构
 1.日    期   : 2014年07月04日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    VOS_UINT32                          ulCurFsmId;
    VOS_UINT32                          ulCurFsmState;
    VOS_UINT8                           ucConnectId;
    VOS_UINT8                           aucReserved[3];
}CNAS_MNTN_LOG_FSM_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_LOG_TIMER_INFO_STRU
 结构说明  : ID_CNAS_MNTN_LOG_TIMER_INFO_IND的消息结构
 1.日    期   : 2014年07月11日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    VOS_UINT32                          ulTimerId;                              /* timer ID */
    VOS_UINT32                          ulParam;                                /* timer ID对应的交易标识 */
    VOS_UINT32                          ulTimerLen;                             /* timer 时长 */
    CNAS_MNTN_TIMER_ACTION_ENUM_UINT32  enTimerAct;                             /* timer 状态: start or stop */
}CNAS_MNTN_LOG_TIMER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_PRINT_CTRL_INFO
 结构说明  : 打印控制信息
 1.日    期   : 2014年07月04日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_MNTN_PRINT_TYPE_ENUM_UINT32    enPrintType;
    VOS_UINT32                          ulInfoPrintFlg;                         /* VOS_TRUE: 打印 VOS_FALSE: 不打印 默认值VOS_FALSE */
    VOS_UINT32                          ulNorPrintFlg;                          /* VOS_TRUE: 打印 VOS_FALSE: 不打印 默认值VOS_FALSE */
    VOS_UINT32                          ulWarnPrintFlg;                         /* VOS_TRUE: 打印 VOS_FALSE: 不打印 默认值VOS_TRUE */
    VOS_UINT32                          ulErrPrintFlg;                          /* VOS_TRUE: 打印 VOS_FALSE: 不打印 默认值VOS_TRUE */
}CNAS_MNTN_PRINT_CTRL_INFO;

/*****************************************************************************
 结构名    : CNAS_MNTN_PRINT_RECORD_STRU
 结构说明  : SDT打印一条打印消息内容
 1.日    期   : 2014年07月04日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[4];
}CNAS_MNTN_PRINT_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_PRINT_MSG_STRU
 结构说明  : 打印消息
 1.日    期   : 2014年07月04日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    CNAS_MNTN_PRINT_RECORD_STRU         astPrintRecord[CNAS_MNTN_PRINT_MSG_MAX_NUM];
}CNAS_MNTN_PRINT_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_LOG_SAVE_PARA_STRU
 结构说明  : log save的参数
 1.日    期   : 2014年07月11日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_UINT32                          ulParaNum;
    VOS_INT32                           lPara1;
    VOS_INT32                           lPara2;
    VOS_INT32                           lPara3;
    VOS_INT32                           lPara4;
}CNAS_MNTN_LOG_SAVE_PARA_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_LOG_MSG_INFO_IND_STRU
 结构说明  : 从OM输出消息结构
 1.日    期   : 2014年07月07日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    CNAS_MNTN_PRINT_MSG_STRU            stPrintMsg;
}CNAS_MNTN_LOG_MSG_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU
 结构说明  : 调用USIMM_GetFileReq接口，勾消息

 修改记录  :
 1.日    期   : 2014年07月17日
   作    者   : l60609
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulRslt;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           ucReserved;
}CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU
 结构说明  : 调用encodix编码API进行编码失败，上报可维可测消息

 修改记录  :
 1.日    期   : 2014年11月17日
   作    者   : l00256032
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_INT32                               lRslt;                              /* 编码API返回的结果 */
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enEncodeMsgType;
    VOS_UINT8                               aucReserved[3];
}CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU
 结构说明  : 调用encodix解码API进行解码失败，上报可维可测消息

 修改记录  :
 1.日    期   : 2014年11月17日
   作    者   : l00256032
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_INT32                               lRslt;                              /* 解码API返回的结果 */
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8  enDecodeMsgType;
    VOS_UINT8                               aucReserved[3];
}CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_DIAG_LOG_NV_INFO_IND_STRU
 结构说明  : CNAS读取NV信息，上报可维可测消息

 修改记录  :
 1.日    期   : 2015年07月07日
   作    者   : y00322978
   修改内容   : 新增
 2.日    期   : 2015年10月08日
   作    者   : t00323010
   修改内容   : DTS2015092201636修改接头体名字

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT32                              ulPid;
    VOS_UINT8                               aucNvInfo[4];/* NV内容 */
}CNAS_DIAG_LOG_NV_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU
 结构说明  : 可维可测公共状态信息

 修改记录  :
 1.日    期   : 2015年08月13日
   作    者   : w00242748
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT8                               ucCsimStatus;
    VOS_UINT8                               aucReserved[3];                     /* 保留字节 */
}CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU;


/*****************************************************************************
 结构名    : CNAS_MNTN_CTX_STRU
 结构说明  : 可维可测总体上下文
 1.日    期   : 2014年07月04日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CNAS_MNTN_PRINT_CTRL_INFO           stPrintCtrlInfo;

    CNAS_MNTN_PRINT_MSG_STRU            stPrintMsg;
}CNAS_MNTN_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_MNTN_TIMER_INFO_STRU
 结构说明  : CNAS定时器信息结构

 1.日    期   : 2014年07月03日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerId;          /* 定时器标识 */
    VOS_UINT32                          ulParam;            /* 定时器参数标识, 如相同timer ID不同交易标识 */
    VOS_UINT32                          ulTimerLen;         /* 定时器时长 */
    CNAS_MNTN_TIMER_ACTION_ENUM_UINT32  enTimerAct;         /* 定时器动作: 停止与启动 */
}CNAS_MNTN_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_USIMM_GETFILE_INFO_STRU
 结构说明  : 获取文件

 1.日    期   : 2015年02月03日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* 应用类型 */
    VOS_UINT16                  usEfId;         /* 文件ID */
    VOS_UINT8                   ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                   ucRsv;          /* 保留 */
}CNAS_MNTN_LOG_GETFILE_INFO_STRU;




typedef struct
{
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulFsmId;
    VOS_UINT32                          ulFsmState;
    CNAS_REBOOT_SCENE_ENUM_UINT8        enRebootScene;
    VOS_UINT8                           aucReserved[3];
}CNAS_REBOOT_INFO_STRU;


/*****************************************************************************
 Name    : CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU
 Description  : 解析xcc 收到的 CSCH DATA IND 空口消息
 History     :
  1.Date     : 2016-01-04
    Author   : y00322978
    Modify   : create
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                          /* 消息头 */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32                            enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                                              usMsgDataLen;
    CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enCschMsgType;
    VOS_UINT8                                               ucReserv;
    VOS_UINT8                                               aucData[4];

}CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CNAS_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_MNTN_MSG_DATA                  stMsgData;
}CNAS_MNTN_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_MNTN_InitCtx(VOS_VOID);
VOS_VOID CNAS_MNTN_InitPrintMsgBuff(VOS_VOID);

VOS_VOID CNAS_MNTN_LogFsmInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState,
    VOS_UINT8                           ucConnectId
);
VOS_VOID CNAS_MNTN_LogSave(
    VOS_UINT32                          ulPid,
    VOS_CHAR                           *pcString,
    LOG_LEVEL_EN                        enLevel,
    CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
);
VOS_VOID CNAS_MNTN_PrintToCom(
    LOG_LEVEL_EN                        enLevel,
    VOS_CHAR                           *pcString,
    CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
);
VOS_VOID CNAS_MNTN_PrintToOm(VOS_VOID);
VOS_VOID CNAS_MNTN_SetPrintType(
    CNAS_MNTN_PRINT_TYPE_ENUM_UINT32    enPrintType
);

/* Deleted by wx270776 for OM融合, 2015-08-21, begin */
/* Deleted by wx270776 for OM融合, 2015-08-21, end */

VOS_VOID CNAS_MNTN_LogUsimmApiGetFileReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulRslt,
    CNAS_MNTN_LOG_GETFILE_INFO_STRU    *pstGetFileInfo
);


VOS_VOID  CNAS_MNTN_TraceIntMsg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulLength,
    VOS_VOID                           *pMsg
);

VOS_VOID CNAS_MNTN_TraceTimerMsg(
    VOS_UINT32                          ulModuleId,
    CNAS_MNTN_TIMER_INFO_STRU          *pstMntnTimerInfo
);

VOS_UINT32 CNAS_MNTN_GetPrintCtrlFlg(
    LOG_LEVEL_EN                        enLevel
);

VOS_VOID CNAS_MNTN_LogEncodeAbnormalInfoInd(
    VOS_UINT32                              ulModuleId,
    VOS_INT32                               lRslt,
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enEncodeMsgType
);

VOS_VOID CNAS_MNTN_LogDecodeAbnormalInfoInd(
    VOS_UINT32                              ulModuleId,
    VOS_INT32                               lRslt,
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8  enDecodeMsgType
);

VOS_VOID CNAS_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    CNAS_REBOOT_INFO_STRU               stCnasRebootInfo
);

extern VOS_VOID CNAS_HandsetInfoQry_Proc(
    VOS_UINT32                          ulInfoType
);

extern VOS_VOID CNAS_HandsetStateInfo_Proc(
    VOS_UINT32                          ulInfoType
);

extern VOS_VOID CNAS_HandsetHighVerInfo_Proc(
    VOS_UINT32                          ulInfoType
);


VOS_VOID CNAS_MNTN_LogReadNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
);

VOS_VOID CNAS_MNTN_LogWriteNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
);

VOS_VOID CNAS_MNTN_LogKeyEvent(
    NAS_OM_EVENT_ID_ENUM                enEvent,
    VOS_UINT32                          ulSendPid
);

VOS_VOID CNAS_MNTN_LogOmAirMsg(
    CNAS_HRPD_OM_AIR_MSG_UP_DOWN_ENUM_UINT8                 ulDir,
    VOS_UINT16                                              ulAirMsgId,
    VOS_UINT32                                              ulSendPid,
    VOS_UINT32                                              ulLength,
    VOS_UINT8                                              *pucData
);

VOS_VOID CNAS_MNTN_AddLogMsgState(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulReceivePid,
    VOS_UINT16                          usMsgName
);
VOS_VOID CNAS_MNTN_UpdateMsgExitTime( VOS_VOID );
VOS_VOID CNAS_MNTN_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMsgHeader
);



VOS_VOID CNAS_MNTN_LogCommonStatusInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT8                           ucCardStatus
);
VOS_VOID CNAS_MNTN_Log1xCschDataIndMsg(
    VOS_UINT32                                              ulPid,
    VOS_UINT16                                              usMsgDataLen,
    CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enCschMsgType,
    VOS_UINT8                                              *pucData
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasMntn.h */
