/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallMnccProc.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月22日
  最近修改   : 2007年8月22日
  功能描述   : MNCC原语处理模块的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月22日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年10月20日
    作    者   : h44270
    修改内容   : 问题单号:A32D14153,来电时，用户尚未接听电话就打开了声码器,，AMR速率变换没有上报

  3.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  4.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS1
******************************************************************************/
#ifndef  MN_CALL_MNCC_PROC_H
#define  MN_CALL_MNCC_PROC_H



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasMncc.h"
#include "product_config.h"
#include "MnCallApi.h"
#include "MnCallMgmt.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/

#define CALL_MAX_ENT_NUM  7

/* 该结构用于CCBS操作过程中
   暂时存储CCBS信息 */
#define MN_CALL_CCBS_INVALID_INDEX              (0)
#define MN_CALL_CCBS_MAX_INDEX                  (5)
#define MN_CALL_CCBS_DEFAULT_INDEX              (1)

#define CCA_SS_DIAG_CCBS_POSSIBLE               (7)
#define MN_CALL_NET_TYPE_GSM                    (0)

typedef struct
{
    VOS_BOOL                            bWaitSendAlertStatus;
    VOS_UINT8                           ucCallId;
} MN_CALL_WAIT_SEND_ALERT_STRU;


#define MN_CALL_BCD_ODD_NUMBER_END                          (0xF0)

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* MN_CALL_MM_EMERGENCY_CONTENT_STRU、MN_CALL_MM_EMERGENCY_LIST_STRU调整到SDC */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */


typedef enum
{
    MN_CALL_ACTIVE_SWITCH_ON = 0,
    MN_CALL_ACTIVE_SWITCH_OFF,

    RMN_CALL_ACTIVE_SWITCH_BUTT
}MN_CALL_TIMER_ACTIVE_SWITCH_ENUM;               /*标识某CALLID是否激活了*/


typedef struct
{
    VOS_UINT32                          ulStartCallTime;                        /* 当前通话开始时间 单位为秒 */
    VOS_UINT32                          ulTotalCallTime;                        /*累计通话时间*/
    VOS_UINT32                          ulPreCallTime;                          /*上次通话时间*/
    MN_CALL_TIMER_ACTIVE_SWITCH_ENUM       CallidActiveSwitch;                  /*标识该Callid是否激活*/
}MN_CALL_TIMER_CALC_ST;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, begin */
/*****************************************************************************
 结构名    : TAF_CALL_SRVCC_CALL_INFO_STRU
 结构说明  : CALL同步IMSA的SRVCC过程中的呼叫信息

 修改记录  :
 1.日    期   : 2013年12月10日
   作    者   : w00176964
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                                          clientId;
    MN_OPERATION_ID_T                                       opId;
    VOS_UINT8                                               ucCallId;
    VOS_UINT8                                               ucTi;                      /* TI信息，保护TI FLAG和TI两项，具体格式参考上面描述 */
    MN_CALL_STATE_ENUM_UINT8                                enCallState;               /* IMSA同步过来的IMS域下的呼叫状态 */
    MN_CALL_MODE_ENUM_U8                                    enCallMode;
    MN_CALL_MPTY_STATE_ENUM_U8                              enMptyState;
    MN_CALL_DIR_ENUM_U8                                     enCallDir;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    VOS_UINT8                                               ucLocalAlertedFlag;        /* IMS域是否进行过本地振铃 */
    VOS_UINT8                                               aucReserve1[1];
    MN_CALL_BCD_NUM_STRU                                    stCallNumber;
    MN_CALL_CALLED_NUM_STRU                                 stCalledNumber;
    MN_CALL_BCD_NUM_STRU                                    stRedirectNumber;
    MN_CALL_BCD_NUM_STRU                                    stConnectNumber;
}TAF_CALL_SRVCC_CALL_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_CALL_LOG_IMSA_API_GET_SRVCC_CALL_INFO_STRU
 结构说明  : 调用IMSA的CALL_IMSA_GetSrvccCallInfo接口，勾消息

 修改记录  :
 1.日    期   : 2013年12月10日
   作    者   : w00176964
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucRslt;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucReserve[2];
    TAF_CALL_SRVCC_CALL_INFO_STRU       astCallInfo[CALL_MAX_ENT_NUM];
}TAF_CALL_LOG_IMSA_API_GET_SRVCC_CALL_INFO_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, end */
/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern VOS_UINT32 VOS_GetTick(VOS_VOID);

/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-4, begin */
VOS_UINT8 TAF_CALL_IsMtCallAllowed(
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup,
    VOS_UINT8                           ucCallId,
    MN_CALL_CC_CAUSE_ENUM_U8           *penCause
);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-4, end */

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSetupInd
 功能描述  : 处理MNCC_SETUP_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSetupCnf
 功能描述  : 处理MNCC_SETUP_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSetupComplInd
 功能描述  : 处理MNCC_SETUP_COMPL_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupComplInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccCallProcInd
 功能描述  : 处理MNCC_CALL_PROC_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccCallProcInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccSyncInd
 功能描述  : 处理MNCC_SYNC_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSyncInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccAlertInd
 功能描述  : 处理MNCC_ALERT_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccAlertInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccDiscInd
 功能描述  : 处理MNCC_DISC_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccDiscInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRelInd
 功能描述  : 处理MNCC_REL_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRelInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRelCnf
 功能描述  : 处理MNCC_REL_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRelCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRejInd
 功能描述  : 处理MNCC_REJ_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRejInd(
    MNCC_IND_PRIM_MSG_STRU             *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccFacilityInd
 功能描述  : 处理MNCC_FACILITYS_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccHoldCnf
 功能描述  : 处理MNCC_HOLD_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccHoldCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccHoldRej
 功能描述  : 处理MNCC_HOLD_REJ原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccHoldRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRetrieveCnf
 功能描述  : 处理MNCC_RETRIEVE_CNF原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRetrieveCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRetrieveRej
 功能描述  : 处理MNCC_RETRIEVE_REJ原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRetrieveRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccFacilityLocalRej
 功能描述  : 处理MNCC_RETRIEVE_REJ原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityLocalRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);
/*****************************************************************************
 函 数 名  : MN_CALL_ReportCoeceEvent
 功能描述  : 上报声码器控制事件
 输入参数  : callId - 需要上报事件的呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ReportChannelEvent(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enEventType
);

/*****************************************************************************
 函 数 名  : CALL_SetChannelOpenFlg
 功能描述  : 设置信道打开标志
 输入参数  : bChannelOpenFlg - 语音信道打开标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SetChannelOpenFlg(
    VOS_BOOL                            bChannelOpenFlg
);
/*****************************************************************************
 函 数 名  : CALL_GetChannelOpenFlg
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL MN_CALL_GetChannelOpenFlg( VOS_VOID );

/*****************************************************************************
 函 数 名  : CALL_SetWaitSendAlertStatus
 功能描述  :
 输入参数  : bWaitSendAlertStatus   - 业务信道的状态
             uccallId               - 呼叫Id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SetWaitSendAlertStatus(
    VOS_BOOL                            bWaitSendAlertStatus,
    VOS_UINT8                           uccallId
);

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccProgressInd
 功能描述  : 处理MNCC_PROGRESS_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccProgressInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/*****************************************************************************
 函 数 名  : MN_CALL_SetMmEmerNumList
 功能描述  : 存储来自MM子层的紧急呼叫号码列表
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_SetMmEmerNumList(
    MNCC_EMERGENCY_LIST_IND_STRU        *pstMnccEmcListInd
);

VOS_UINT32 MN_CALL_GetTchParm(
    MN_CALL_CHANNEL_PARAM_STRU          *pstChannParm
);
/*****************************************************************************
 函 数 名  : MN_CALL_GetTchStatus
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL MN_CALL_GetTchStatus( VOS_VOID );


/*****************************************************************************
 函 数 名  : MN_CALL_PorcMnccPromptInd
 功能描述  : 处理MNCC_PROMPT_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID MN_CALL_PorcMnccPromptInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);
/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccEstInd
 功能描述  : 处理MNCC_CC_EST_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID MN_CALL_ProcMnccEstInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);
/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccRecallInd
 功能描述  : 处理MNCC_RECALL_IND原语
 输入参数  : pstMsg - 来自CC的原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRecallInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 函 数 名  : CALL_GetWaitSendAlertStatus
 功能描述  :
 输入参数  :
 输出参数  : pbWaitSendAlertStatus - 当前是否处于等待发送alerting消息状态
              puccallId             - 对应的呼叫Id
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_GetWaitSendAlertStatus(
    VOS_BOOL                            *pbWaitSendAlertStatus,
    VOS_UINT8                           *puccallId
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCcUus1Info
 功能描述  : 调用CC模块中函数更新UUS1信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_UpdateCcUus1Info(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCcUus1Info
 功能描述  : 获取CC保存的UUS1相关信息
 输入参数  : 无
 输出参数  : pulActNum      :CC总共激活个数
             pstUus1Info    :激活UUS1的信息
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcUus1Info(
    VOS_UINT32                          *pulActNum,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

VOS_VOID  MN_CALL_ProcUusInfoInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  MN_CALL_ProcEmergencyListInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */


VOS_VOID MN_CALL_ReportHoldEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId );

VOS_VOID MN_CALL_ReportRetrieveEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId );


/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-30, begin */
VOS_VOID  MN_CALL_ProcBufferedCall(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_CALL_ProcBufferedRedialMessage(
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-30, end */


/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, begin */

VOS_VOID MN_CALL_SndAtChannelInfoInd(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enChannelEvent,
    MN_CALL_CHANNEL_INFO_STRU          *pstChannelInfo,
    VOS_UINT8                           ucIsLocalAlertingFlag
);

/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
/* 删除该函数，功能实现移到函数MN_CALL_ReportChannelEvent中 */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
/* Added by l00171473 for DTS2013010800120 语音带宽信息上报, 2013-1-5, end */

VOS_UINT32 TAF_CALL_IsNeedLocalAlerting(const NAS_CC_IE_PROGRESS_INDICATOR_STRU *pstProgInd);

/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
VOS_VOID  TAF_CALL_RcvCcStartDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  TAF_CALL_RcvCcStartDtmfRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  TAF_CALL_RcvCcStopDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  TAF_CALL_ProcMnccSrvccStatusInd(
    MNCC_SRVCC_STATUS_IND_STRU         *pstSrvccMsg
);

VOS_VOID TAF_CALL_MapCallInfoToCcInfo(
    MNCC_ENTITY_STATUS_STRU            *pstCcInfo,
    VOS_UINT8                          *pucCallNum
);

VOS_VOID TAF_CALL_ProcDtmfBuffer(VOS_VOID);

VOS_VOID TAF_CALL_ProcSrvccSyncInfo(VOS_VOID);
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
VOS_UINT8 TAF_CALL_IsEcallRedialExist(VOS_VOID);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_ProcessEcallPeriodTimerLen(VOS_UINT8 ucCallId);

VOS_VOID TAF_CALL_ProcEcallRel(
    MN_CALL_MGMT_STRU                  *pstCallEntity);
#endif

VOS_VOID  MN_CALL_SendVcMsg(
    CALL_VC_MSG_ID_ENUM_U16             enEventType
);

VOS_VOID TAF_CALL_SetTchCallType(TAF_CALL_TYPE_ENUM_UINT16 enCallType);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */



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

#endif /* MN_CALL_MNCC_PROC_H */

