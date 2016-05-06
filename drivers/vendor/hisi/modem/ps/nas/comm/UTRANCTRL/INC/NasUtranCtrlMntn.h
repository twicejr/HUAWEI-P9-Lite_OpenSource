/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlMntn.h
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年8月16日
  最近修改   :
  功能描述   : NasUtranCtrlMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月16日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NASUTRANCTRLMNTN_H__
#define __NASUTRANCTRLMNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "NasUtranCtrlCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)


/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_UTRANCTRL_OM_MSG_ID_ENUM
 结构说明  : UTRANCTRL模块可维可测消息ID枚举
 1.日    期   : 2012年8月19日
   作    者   : w00167002
   修改内容   : 新增
*****************************************************************************/
enum NAS_UTRANCTRL_OM_MSG_ID_ENUM
{
    NAS_UTRANCTRL_OM_MSG_LOG_FSM_INFO                       = 0x8000,           /* UTRANCTRL 模块LOG FSM INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_USER_CFG_EHPLMN_INFO,                              /* UTRANCTRL 模块LOG USER CFG EHPLMN INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_UTRAN_MODE_AUTO_SWITCH_INFO,                       /* UTRANCTRL 模块LOG UTRANMODE AUTO SWITCH INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_MSG_QUEUE_INFO,                                    /* UTRANCTRL 模块LOG MSG QUEUE INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_RUNNING_CONTEXT_FOR_PC_REPLAY  = 0x8500,           /* UTRANCTRL 模块的回放消息 */
    NAS_UTRANCTRL_OM_MSG_BUTT
};
typedef VOS_UINT32  NAS_UTRANCTRL_OM_MSG_ID_ENUM_UINT32;

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
 结构名    : NAS_UTRANCTRL_LOG_FSM_INFO_STRU
 结构说明  : 当前UTRANCTRL的FSM可维可测信息
 1.日    期   : 2012年8月16日
   作    者   : w00167002
   修改内容   : 新建 for V7R1C50_GUTL_PhaseII
*****************************************************************************/
typedef struct
{
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32                        enFsmId;                /* 当前的状态机名称 */
    VOS_UINT32                                              ulState;                /* 当前的状态机状态 */
    VOS_UINT8                                               ucSearchedSpecTdMccFlg; /* 记录是否有搜到中国网络标识 */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8              enCurUtranSwitchMode;   /* 当前UTRAN的自动切换模式 */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enCurrUtranMode;        /* NVIM中保存的UTRAN模式 */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enPreUtranMode;         /* 上次发给RRC的UTRAN模式 */
    VOS_UINT8                                               ucReplaceMmcMsgFlg;     /* 替换发给MMC的消息标记:VOS-TRUE:需要用缓存的消息替换发给MMC的消息；VOS_FALSE:不需要替换发给MMC的消息 */
    VOS_UINT8                                               aucReserve[3];
}NAS_UTRANCTRL_LOG_FSM_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_UTRANCTRL_MNTN_INFO_STRU
 结构说明  : UTRANCTRL模块的可维可测信息
 1.日    期   : 2012年8月16
   作    者   : w00167002
   修改内容   : 新建 for V7R1C50_GUTL_PhaseII
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    NAS_UTRANCTRL_OM_MSG_ID_ENUM_UINT32                     enMsgId;            /* 消息类型 */      /* _H2ASN_Skip */

    union
    {
        NAS_UTRANCTRL_LOG_FSM_INFO_STRU                     stLogFsmInfo;             /* 可维可测LOG状态机信息 */
        NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU           stUtranModeAutoSwitch;    /* 可维可测当前用户配置的UTRAN切换模式可维可测信息 */
        NAS_UTRANCTRL_MSG_QUEUE_STRU                        stBufferEntryMsgQueue;    /* 可维可测当前UTRANCTRL模块的缓存队列信息 */
    }u;
}NAS_UTRANCTRL_MNTN_INFO_STRU;




/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo( VOS_VOID );
VOS_VOID  NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo( VOS_VOID );
VOS_VOID  NAS_UTRANCTRL_SndOmBufferQueueMsg(VOS_VOID);

#endif  /* END OF #if (FEATURE_ON == FEATURE_UE_MODE_TDS)  */

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

#endif /* end of NasUtranCtrlMntn.h */
