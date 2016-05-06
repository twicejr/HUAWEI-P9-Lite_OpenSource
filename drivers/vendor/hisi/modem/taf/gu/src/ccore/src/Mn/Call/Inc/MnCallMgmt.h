/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallMgmt.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月22日
  最近修改   : 2007年8月22日
  功能描述   : 呼叫管理模块的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月22日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年7月12日
    作    者   : 胡文 44270
    修改内容   : 问题单号:AT2D04057

  3.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  4.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS1
******************************************************************************/
#ifndef  MN_CALL_MGMT_H
#define  MN_CALL_MGMT_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallCtx.h"
#include "MnCallApi.h"
#include "UsimPsApi.h"
#include "MnCallMnccProc.h"
#include "MnCallFacilityDecode.h"
#include "product_config.h"
/* Deleted by z00161729 for V9R1 STK升级, 2013-7-24, begin */
/* Deleted by z00161729 for V9R1 STK升级, 2013-7-24, end */
#include "siappstk.h"
#include "hi_list.h"
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include "CallImsaInterface.h"
#endif
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
#define MN_CALL_DISC_EVENT_CAUSE_LEN        (3)

#define MN_CALL_IS_OPEN_CODEC(ucCallState, ucStartedHifiFlag)           \
               ( (CALL_IMSA_SRVCC_CALL_ACTIVE       == ucCallState)        \
              || (CALL_IMSA_SRVCC_CALL_HELD         == ucCallState)         \
              || ((CALL_IMSA_SRVCC_CALL_ALERTING    == ucCallState)         \
               && (VOS_TRUE                         == ucStartedHifiFlag)))

/*****************************************************************************
  3类型定义
*****************************************************************************/
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-18, begin */

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-18, end */

enum MN_CALL_POWER_STATE_ENUM
{
    MN_CALL_POWER_STATE_OFF                 = 0, /*关机*/
    MN_CALL_POWER_STATE_ON                  = 1, /*开机*/
    MN_CALL_POWER_STATE_BUTT
};
typedef VOS_UINT8  MN_CALL_POWER_STATE_ENUM_U8;

/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define MN_CALL_SIM_ABSENT              PS_USIM_GET_STATUS_ABSENT               /* SIM不存在                                */
#define MN_CALL_SIM_PRESENT             PS_USIM_GET_STATUS_PRESENT              /* SIM存在                                  */

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/* PC回放导出全局变量使用 */
#define EVT_NAS_CALL_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* 为PC工程回放定义的消息 */

/* ASSERT */
#ifdef  _DEBUG
#define  MN_CALL_ASSERT(expr) \
        if(!(expr)) \
        { \
            MN_ERR_LOG("Assertion failed: " #expr); \
        }
#else
#define  MN_CALL_ASSERT(expr)   ((VOS_VOID)0)
#endif /* _DEBUG */

enum MN_CALL_HOOK_MSG_ID_ENUM
{
    /* STK呼叫事件 MT CALL  SI_STK_MT_CALL_EVENT_STRU */
    MN_CALL_HOOK_STK_MT_CALL_EVENT                          = 0x02aa,           /* _H2ASN_MsgChoice SI_STK_MT_CALL_EVENT_STRU        */
    /* STK呼叫事件 CALL Disconnect SI_STK_CALL_DISCONNECTED_EVENT_STRU */
    MN_CALL_HOOK_STK_CALL_DISC_EVENT                        = 0x02ab,           /* _H2ASN_MsgChoice SI_STK_CALL_DISCONNECTED_EVENT_STRU */
    /* STK呼叫事件 CALL Connect SI_STK_CALL_CONNECTED_EVENT_STRU */
    MN_CALL_HOOK_STK_CALL_CONN_EVENT                        = 0x02ac,           /* _H2ASN_MsgChoice SI_STK_CALL_CONNECTED_EVENT_STRU */

    MN_CALL_HOOK_STK_ENVELOPE                               = 0x0300,           /* _H2ASN_MsgChoice SI_STK_ENVELOPE_STRU */

    MN_CALL_HOOK_MSG_ID_BUTT
};
typedef VOS_UINT32 MN_CALL_HOOK_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/

/*****************************************************************************
结构名    : MN_CALL_HOOK_MSG_STRU
结构说明  : MN CALL 消息勾包结构体
1.日    期  : 2012年10月09日
  作    者  : l00198894
  修改内容  : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MN_CALL_HOOK_MSG_ID_ENUM_UINT32     enMsgId;                                /* 消息名 */
    VOS_UINT8                           aucContent[4];                          /* 消息内容 */
} MN_CALL_HOOK_MSG_STRU;

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
结构名    : TAF_CALL_DTMF_INFO_STRU
结构说明  : CALL模块用于缓存DTMF信息结构
1.日    期   : 2013年7月10日
  作    者   : l00198894
  修改内容   : V9R1 STK升级项目新增
2.日    期   :2013年10月24日
  作    者   :z00161729
  修改内容   :DTS2013102403705:dtmf不支持off_length参数，SBM IOT认证需要stop dtmf req和下一个start dtmf req间隔大于70ms小于600ms

*****************************************************************************/
typedef struct
{
    MN_CALL_ID_T                        CallId;
    VOS_CHAR                            cKey;                                   /* DTMF Key */
    VOS_UINT16                          usOnLength;                             /* DTMF持续时间，0: 代表停止DTMF */

    VOS_UINT16                          usOffLength;                            /* stop dtmf req和start dtmf req时间间隔，单位ms*/
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           aucReserved1[3];
} TAF_CALL_DTMF_INFO_STRU;

/*****************************************************************************
结构名    : TAF_CALL_DTMF_NODE_STRU
结构说明  : CALL模块DTMF缓存链表节点结构
1.日    期   : 2013年7月10日
  作    者   : l00198894
  修改内容   : V9R1 STK升级项目新增
*****************************************************************************/
typedef struct
{
    TAF_CALL_DTMF_INFO_STRU             stDtmf;
    HI_LIST_S                           stList;
} TAF_CALL_DTMF_NODE_STRU;

#define TAF_CALL_DTMF_BUF_MAX_CNT               (32)                            /* 最多缓存DTMF信息的个数 */

/*****************************************************************************
结构名    : TAF_CALL_DTMF_CTX_STRU
结构说明  : CALL模块用于保存DTMF信息
1.日    期   : 2013年7月10日
  作    者   : l00198894
  修改内容   : V9R1 STK升级项目新增
*****************************************************************************/
typedef struct
{
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;
    VOS_UINT8                           ucDtmfCnt;
    VOS_UINT8                           aucReserved1[2];
    TAF_CALL_DTMF_INFO_STRU             stCurrDtmf;
    HI_LIST_S                           stList;
} TAF_CALL_DTMF_CTX_STRU;
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
  6 全局变量声明
*****************************************************************************/


/*****************************************************************************
  7 接口函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_CALL_StartFluxCalculate
 功能描述  : 开始统计通话时间
 输入参数  : VOS_UINT8 ucCallId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-09-01
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2011年10月05日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
extern VOS_VOID  MN_CALL_StartFluxCalculate( VOS_UINT8 ucCallId);

/*****************************************************************************
 函 数 名  : MN_CALL_StopFluxCalculate
 功能描述  : 停止统计通话时间
 输入参数  : VOS_UINT8 ucCallId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-09-01
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2011年10月05日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_VOID  MN_CALL_StopFluxCalculate( VOS_UINT8 ucCallId);

/* 复位所有的呼叫信息 */
VOS_VOID   MN_CALL_ResetAllCalls(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);

/* 分配Call ID */
VOS_UINT32 MN_CALL_AllocCallId(MN_CALL_ID_T *pCallId);

/* 释放Call ID */
VOS_VOID   MN_CALL_FreeCallId(MN_CALL_ID_T  callId);

/* 检查是否可以发起/接听一个新的呼叫 */
VOS_BOOL   MN_CALL_IsAllowToMakeNewCall(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

/* 新建一个呼叫管理实体 */
VOS_VOID  MN_CALL_CreateCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulTi,
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo,
    const MN_CALL_BCD_NUM_STRU          *pstNumber
);

VOS_VOID  MN_CALL_CreateMoCallEntity(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
);

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT8 TAF_CALL_IsCallTypeEcall(MN_CALL_ID_T ucCallId);
#endif

VOS_VOID TAF_CALL_UpdateCallInfo(
    MN_CALL_ID_T                        ucCallId,
    MN_CALL_INFO_STRU                  *pstCallInfo
);

VOS_UINT32 MN_CALL_GetSpecificCallInfo(
    MN_CALL_ID_T                        CallId,
    MN_CALL_MGMT_STRU                  *pstCallInfo
);

VOS_VOID MN_CALL_GetCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                           *pbReleaseFlag
);

VOS_VOID TAF_CALL_FillDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    TAF_CALL_EVT_DTMF_CNF_STRU         *pstDtmfCnf
);

VOS_UINT8 TAF_CALL_IsCallTypeEmgencyCall(MN_CALL_ID_T ucCallId);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */


/*****************************************************************************
 函 数 名  : MN_CALL_CreateMtCallEntity
 功能描述  : 新建一个被叫呼叫管理实体，保存所有应用数据到全局变量
 输入参数  : callId         - 呼叫的ID
             ucTi           - 呼叫实体对应的Ti
             pstSetup       - 被叫请求中携带的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : l00198894
    修改内容   : DTS2012100901666: 新增函数

*****************************************************************************/
VOS_VOID  MN_CALL_CreateMtCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi,
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup
);

/*****************************************************************************
 函 数 名  : MN_CALL_DeleteCallEntity
 功能描述  : 清除一个呼叫管理实体
 输入参数  : callId - 需要清除的呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_DeleteCallEntity(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCcEntityId
 功能描述  : 根据CallId获取EntityId
 输入参数  : callId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcTi(
    MN_CALL_ID_T                        callId
);
/*****************************************************************************
 函 数 名  : MN_CALL_GetCcCallDir
 功能描述  : 根据CallId获取EntityId
 输入参数  : callId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcCallDir(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_ReportEvent
 功能描述  : 向所有Client上报呼叫事件
 输入参数  : callId      - 需要上报事件的呼叫的ID
              enEventType - 事件类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ReportEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_EVENT_ENUM_U32              enEventType
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateClientId
 功能描述  : 更新指定呼叫的Client ID信息
 输入参数  : callId   - 需要更新Client ID的呼叫的ID
              clientId - 新的Client ID值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateClientId(
    MN_CALL_ID_T                        callId,
    MN_CLIENT_ID_T                      ucClientId
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCallState
 功能描述  : 更新指定呼叫的呼叫状态信息
 输入参数  : callId      - 需要更新状态的呼叫的ID
              enCallState - 新的呼叫状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateMptyState
 功能描述  : 更新指定呼叫的MPTY状态信息
 输入参数  : callId      - 需要更新MPTY状态的呼叫的ID
              enMptyState - 新的MPTY状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateMptyState(
    MN_CALL_ID_T                        callId,
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCallType
 功能描述  : 更新指定呼叫的呼叫类型信息
 输入参数  : callId     - 需要更新呼叫类型的呼叫的ID
              enCallType - 新的呼叫类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallType(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCallMode
 功能描述  : 更新指定呼叫的呼叫模式信息
 输入参数  : callId     - 需要更新呼叫模式的呼叫的ID
              enCallMode - 新的呼叫模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallMode(
    MN_CALL_ID_T                        callId,
    MN_CALL_MODE_ENUM_U8                enCallMode
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateDataCallCfgInfo
 功能描述  : 更新指定呼叫的数据呼叫配置信息
 输入参数  : callId     - 需要更新数据呼叫配置的呼叫的ID
             pstDataCfg - 新的数据呼叫配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo
);


/*****************************************************************************
 函 数 名  : MN_CALL_UpdateRedirNumber
 功能描述  : 更新指定呼叫的转移号码信息
 输入参数  : callId         - 需要更新转移号码的呼叫的ID
              pstRedirNumber - 新的转移号码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRedirNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNumber
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateConnNumber
 功能描述  : 更新指定呼叫的连接号码信息
 输入参数  : callId        - 需要更新连接号码的呼叫的ID
              pstConnNumber - 新的连接号码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateConnNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstConnNumber
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCallNumber
 功能描述  : 更新指定呼叫来电号码信息
 输入参数  : callId        - 需要更新连接号码的呼叫的ID
              pstCallNumber - 新的连接号码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstCallNumber
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCalledNumber
 功能描述  : 更新指定呼叫被叫号码信息
 输入参数  : callId             - 需要更新连接号码的呼叫的ID
             pstCalledNumber    - 新的连接被叫号码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : l00198894
    修改内容   : DTS2012100901666: 新生成函数

*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCalledNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CALLED_NUM_STRU      *pstCalledNumber
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateSsNotify
 功能描述  : 更新指定呼叫的补充业务通知信息
 输入参数  : callId    - 需要更新补充业务命令的呼叫的ID
              pstSsInfo - 新的补充业务通知信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateSsNotify(
    MN_CALL_ID_T                        callId,
    const MN_CALL_SS_NOTIFY_STRU        *pstSsInfo
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCcCause
 功能描述  : 更新指定呼叫的CC原因值信息
 输入参数  : callId    - 需要更新CC原因值的呼叫的ID
              enCcCause - 新的CC原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCcCause(
    MN_CALL_ID_T                        callId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCcCause
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateNoCliCause
 功能描述  : 更新指定呼叫的无号码显示原因信息
 输入参数  : callId       - 需要更新无号码显示原因的呼叫的ID
              enNoCliCause - 新的无号码显示原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateNoCliCause(
    MN_CALL_ID_T                        callId,
    MN_CALL_NO_CLI_CAUSE_ENUM_U8        enNoCliCause
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateRabId
 功能描述  : 更新指定呼叫的RAB ID信息
 输入参数  : callId  - 需要更新RAB ID的呼叫的ID
              ucRabId - 新的RAB ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRabId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCallState
 功能描述  : 获取指定呼叫的状态信息
 输入参数  : callId       - 需要获取状态信息的呼叫的ID
 输出参数  : penCallState - 获得的呼叫状态
              penMptyState - 获得的MPTY状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               *penCallState,
    MN_CALL_MPTY_STATE_ENUM_U8          *penMptyState
);

TAF_CALL_SUB_STATE_ENUM_UINT8 TAF_CALL_GetCallSubState(
    MN_CALL_ID_T                        callId
);

VOS_VOID TAF_CALL_SetCallSubState(
    MN_CALL_ID_T                        callId,
    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState
);


/*****************************************************************************
 函 数 名  : MN_CALL_GetCallsByState
 功能描述  : 获取特定呼叫状态的所有呼叫
 输入参数  : CallState     - 指定的呼叫状态
 输出参数  : pulNumOfCalls - 指定状态的呼叫个数
              pCallIds      - 指定状态的呼叫ID列表(输入的缓存需能容纳7个记录)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);

/* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */

/*****************************************************************************
 函 数 名  : MN_CALL_RegSsKeyEvent
 功能描述  : 注册补充业务操作的关注事件
             当关注的呼叫上发生关注的事件时，注册的后续操作(enSubseqOp)
             将被执行; 其它事件在发生时不会引起任何操作, 将被忽略
 输入参数  : callId     - 标识发生事件的呼叫
              enEvt      - 关注的事件类型
              enSubseqOp - 该事件将引起的操作
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_RegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    MN_CALL_SS_SUBSEQ_OP_ENUM           enSubseqOp
);

/*****************************************************************************
 函 数 名  : MN_CALL_ClearSsKeyEvent
 功能描述  : 清除所有的关注事件
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
VOS_VOID  MN_CALL_ClearSsKeyEvent(VOS_VOID);


/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCallMgmtProgress
 功能描述  : 当发生了补充业务操作相关的事件时, 更新补充业务操作的进展.
             该函数根据发生的事件和已注册的关注事件来产生特定操作.
 输入参数  : callId  - 标识发生事件的呼叫
             enEvt   - 发生的事件类型
             ulErrno - 如果是操作拒绝类的事件, 需要携带错误码，该参数只有在
                       向上层上报操作失败时才有效.
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallSupsProgress(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    VOS_UINT32                          ulErrno
);

/*****************************************************************************
 函 数 名  : TAF_CALL_SetCsCallExistFlg
 功能描述  : 设置当前是否处于CS CALL 和紧急呼标记
 输入参数  : ucCallExitFlg - 是否有call
             enCallType    - call type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月9日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    TAF_CALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

/*****************************************************************************
 函 数 名  : MN_CALL_BeginCallMgmtCmdProgress
 功能描述  : 开始进行补充业务操作, 记录初始信息, 设置补充业务进行标志
 输入参数  : clientId - 发起该补充业务操作的Client的ID
              enCallMgmtCmd    - 发起的补充业务操作
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_BeginCallSupsCmdProgress(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_SUPS_CMD_ENUM_U8            enCallSupsCmd
);

/*****************************************************************************
 函 数 名  : MN_CALL_IsCallSupsCmdInProgress
 功能描述  : 查看当前是否在进行补充业务操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE - 正在进行补充业务操作,  VOS_FALSE - 没有进行补充业务操作
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL  MN_CALL_IsCallSupsCmdInProgress(VOS_VOID);


/*****************************************************************************
 函 数 名  : MN_CALL_GetCallInfoList
 功能描述  : 获取当前所有状态不为IDLE的呼叫信息
 输入参数  : pucNumOfCalls - 输出缓存最多能存储的呼叫信息个数
 输出参数  : pucNumOfCalls - 实际输出的(状态不为IDLE的)呼叫信息个数
              pstCallInfos  - 输出的呼叫信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallInfoList(
    TAF_UINT8                           *pucNumOfCalls,
    MN_CALL_INFO_STRU                   *pstCallInfos
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCallsByState
 功能描述  : 获取特定MPTY状态的所有呼叫
 输入参数  : enMptyState   - 指定的MPTY状态
 输出参数  : pulNumOfCalls - 指定状态的呼叫个数
             pCallIds      - 指定状态的呼叫ID列表(输入的缓存需能容纳7个记录)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallsByMptyState(
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);

/*****************************************************************************
 函 数 名  : MN_CALL_TiUsedCheck
 功能描述  : 检查当前Ti是否属于某个呼叫实体
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE - 属于FDN号码,  VOS_FALSE - 不属于FDN号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL  MN_CALL_TiUsedCheck(
    VOS_UINT32                          ulTi
);


/*****************************************************************************
 函 数 名  : MN_CALL_CheckNotIdleStateExist
 功能描述  : 判定当前是否有非Idle态的实体存在
 输入参数  : CallState     - 指定的呼叫状态
 输出参数  : pulNumOfCalls - 指定状态的呼叫个数
             pCallIds      - 指定状态的呼叫ID列表(输入的缓存需能容纳7个记录)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL  MN_CALL_CheckNotIdleStateExist( VOS_VOID );


/*****************************************************************************
 函 数 名  : MN_CALL_CheckCallEntityExist
 功能描述  : 判定当前指定call id的实体是否存在
 输入参数  : CallState     - 指定的呼叫状态
 输出参数  : pulNumOfCalls - 指定状态的呼叫个数
             pCallIds      - 指定状态的呼叫ID列表(输入的缓存需能容纳7个记录)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL  MN_CALL_CheckCallEntityExist(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 Prototype      : MN_CALL_InvokeId_Alloc()
 Description    : 分配InvokeId，此函数为原来的代码进行移植
 Input          : ucTi: 呼叫标识
 Output         : *pInvokeId: 分配的InvokeId
 Return Value   : VOS_OK    分配成功
                : VOS_ERROR 分配失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_INT32 MN_CALL_InvokeIdAlloc(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           *pInvokeId,
    VOS_UINT8                           ucOperateCode
);


/*****************************************************************************
 函 数 名  : MN_CALL_GetDataCallCfgInfo
 功能描述  : 获取指定呼叫的数据呼叫配置信息
 输入参数  : callId     - 需要更新数据呼叫配置的呼叫的ID
             pstDataCfg - 新的数据呼叫配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_GetDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateTi
 功能描述  : 更新指定呼叫的TI信息
 输入参数  : callId  - 需要更新RAB ID的呼叫的ID
             ucTi    - 新的Ti值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateTi(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
);

VOS_UINT8 TAF_CALL_GetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId
);
VOS_VOID TAF_CALL_SetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucSrvccLocalAlertedFlag
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetNotIdleStateCalls
 功能描述  : 获取不处于Idle状态的Call
 输入参数  : callId  - 需要获取状态信息的呼叫的ID
 输出参数  : pCallState - 获得的呼叫状态
             pMptyState - 获得的MPTY状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_GetNotIdleStateCalls(
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);

/*****************************************************************************
 Prototype      : MN_CALL_SsOpCodeTransToSsEvent
 Description    : 将操作码转换成对应的事件
 Input          : sSOpCode - 操作码
 Output         : penEvent - 对应的事件
 Return Value   : VOS_OK    - 转换成功
                : VOS_ERR   - 转换失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-03-26
    Author      : h44270
    Modification: Created function
*****************************************************************************/
VOS_UINT32  MN_CALL_SsOpCodeTransToSsEvent(
    MN_CALL_SS_OPERATION_CODE_T         sSOpCode,
    MN_CALL_SS_PROGRESS_EVT_ENUM        *penEvent
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCallInfoByCallId
 功能描述  : 根据呼叫Id来获取对应的实体呼叫管理信息
 输入参数  : callId        - 需要更新数据呼叫配置的呼叫的ID
             pstMgmtEntity - 呼叫管理实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_INFO_STRU                   *pstCallInfo
);

/*****************************************************************************
 函 数 名  : MN_CALL_DeRegSsKeyEvent
 功能描述  : 删除补充业务操作的关注事件
 输入参数  : callId     - 标识发生事件的呼叫
             enEvt      - 不需要关注的事件类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_DeRegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt
);

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcRelCallSsKeyEvent
 功能描述  : 补充业务在进行中对异常状态的响应函数
 输入参数  : callId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月12日
    作    者   : 胡文 44270
    修改内容   : 新生成函数，问题单号:AT2D04057
*****************************************************************************/
VOS_VOID  TAF_CALL_ProcRelCallSsKeyEvent(
    MN_CALL_ID_T                        callId
);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCcbsSetup
 功能描述  : 更新全局变量f_stCcbsSetup的内容
 输入参数  : pstCcbsSetup - Mo setup内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2009-12-25
    作    者  : z00161729
    修改内容  : 新生成函数，
*****************************************************************************/

VOS_VOID  MN_CALL_UpdateCcbsSetup(
    const NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCcbsSupsProgress
 功能描述  : 当发生了补充业务操作相关的事件时, 更新补充业务操作的进展.
             该函数根据发生的事件和已注册的关注事件来产生特定操作.
 输入参数  : callId     - 标识发生事件的呼叫
             ulErrno    - 如果是操作拒绝类的事件, 需要携带错误码，该参数只有在
                          向上层上报操作失败时才有效.
             enSsResult - 操作结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCcbsSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCcbsSetup
 功能描述  :获取全局变量f_stCcbsSetup的内容
 输入参数  :pstCcbsSetup - Mo setup内容
 输出参数  :无
 返 回 值  :无
 调用函数  :
 被调函数  :

 修改历史       :
  1.日    期    : 2009-12-25
    作    者    : z00161729
    修改内容    : 新生成函数，
*****************************************************************************/
VOS_VOID  MN_CALL_GetCcbsSetup(
    NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
);

VOS_VOID MN_CALL_UpdateCcCallDir(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateRecallSupsProgress
 功能描述  : 当发生了补充业务操作相关的事件时, 更新补充业务操作的进展.
             该函数根据发生的事件和已注册的关注事件来产生特定操作.
 输入参数  : callId  - 标识发生事件的呼叫
             ulErrno - 如果是操作拒绝类的事件, 需要携带错误码，该参数只有在
                       向上层上报操作失败时才有效.
             enSsResult - 操作结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRecallSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);

/*****************************************************************************
 Prototype      : MN_CALL_CallCtrlProcess
 Description    : 调用USIM模块提供的call control接口，发送Envelop命令给USIM模块
 Input          : pstParam - 主叫的信息，用于填写Envelop命令中的相应参数
 Output         :
 Return Value   : VOS_OK    - 操作成功
                : VOS_ERR - 操作失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-08-19
    Author      : huwen
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_CallCtrlProcess(
    MN_CALL_ORIG_PARAM_STRU             *pstParam
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCallCtrlState
 功能描述  : 更新指定呼叫的呼叫状态信息
 输入参数  : callId          - 需要更新状态的呼叫的ID
              enCallCtrlState - 新的呼叫控制状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallCtrlState(
    MN_CALL_ID_T                        callId,
    MN_CALL_CTRL_STATE_ENUM_U32         enCallCtrlState
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetAlsLineInfo
 功能描述  : 获取当前使用线路号
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 用户当前使用的线路号
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月22日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_ALS_LINE_NO_ENUM_U8  MN_CALL_GetAlsLineInfo(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateAlsLineNbr
 功能描述  : 更新指定呼叫使用的线路号信息
 输入参数  : callId - 需要更新状态的呼叫的ID
             enAlsLineNbr - 新的线路号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_CALL_UpdateAlsLineNbr(
    MN_CALL_ID_T                        callId,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLineNbr
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateAlsLineInfo
 功能描述  : 更新内存和NVIM中的LINE信息
 输入参数  : enAlsLine :选择的线路号
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月22日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_UpdateAlsLineInfo(
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine,
    VOS_BOOL                            bUpdateNvim
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCallType
 功能描述  : 获取指定呼叫的呼叫类型信息
 输入参数  : callId     - 需要更新呼叫类型的呼叫的ID
              enCallType - 新的呼叫类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
extern MN_CALL_TYPE_ENUM_U8  MN_CALL_GetCallType(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateRbId
 功能描述  : 刷新RbId
 输入参数  : 无
 输出参数  : pulNumOfCalls - 呼叫个数
              pCallIds - 对应的呼叫Id
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID  MN_CALL_UpdateRbId(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulRbId
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetRbId
 功能描述  : 根据CallId获取RbId
 输入参数  : callId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32 MN_CALL_GetRbId(MN_CALL_ID_T callId);

/*****************************************************************************
 函 数 名  : MN_CALL_SetVideoCallChannelOpenFlg
 功能描述  : 设置可视电话业务信道已经建立标识
 输入参数  : bVideoCallChannelOpenFlg - 可视电话信道打开标志
             callId                   - 呼叫ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月1日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SetVideoCallChannelOpenFlg(
    VOS_BOOL                            bVideoCallChannelOpenFlg,
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetVideoCallChannelOpenFlg
 功能描述  : 查询可视电话业务信道是否打开标识
 输入参数  : callId                   - 呼叫ID
 输出参数  : 无
 返 回 值  : VOS_TRUE - 可视电话业务信道打开
             VOS_FALSE - 可视电话业务信道未打开
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月1日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL MN_CALL_GetVideoCallChannelOpenFlg(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_ConCallMsgTypeToCcMsgType
 功能描述  : 将CALLL的定义的消息类型转换为CC定义的消息类型
 输入参数  : enCallMsgType :  设置需携带UUS1的消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_ConCallMsgTypeToCcMsgType(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType,
    NAS_CC_MSG_TYPE_ENUM_U8             *penCcMsgType
);

/*****************************************************************************
 函 数 名  : MN_CALL_ConCcMsgTypeToCallMsgType
 功能描述  : 将CC的消息类型转换为CALL的消息类型
 输入参数  : enCcMsgType    :CC定义的消息名称
 输出参数  : penCallMsgType :CALL定义的消息名称
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_ConCcMsgTypeToCallMsgType(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      *penCallMsgType
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateRptUus1Info
 功能描述  : 更新上报Call信息中UUS1值
 输入参数  : callId         :呼叫ID
             enCcMsgType    :需更新的消息类型
             pstUserUser    :UUS1信息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_CALL_UpdateRptUus1Info(
    MN_CALL_ID_T                        callId,
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser
);

/*****************************************************************************
 函 数 名  : MN_CALL_ConCcUusInfoToCall
 功能描述  : 将CC的UUS消息格式转换为需上报的消息格式
 输入参数  : enCcMsgType        :需转换的消息类型
             pstUserUser        :CC上报的UUS的消息格式
 输出参数  : pstUus1Info        :转换后上报的UUS的消息格式
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_CALL_ConCcUusInfoToCall(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

/*****************************************************************************
 函 数 名  : MN_CALL_ConCallUusInfoToCc
 功能描述  : 填充激活UUS1相关信息
 输入参数  : enMsgType    :  需转换的消息类型
             pstUus1Info  :  用户需要设置UUS1相关信息
 输出参数  : pstUuieInfo  :  发送到网络UUIE信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  MN_CALL_ConCallUusInfoToCc(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
);
/*****************************************************************************
 函 数 名  : NAS_CALL_SndOutsideContextData
 功能描述  : 把CALL外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月30日
    作    者   : 王毛 00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CALL_SndOutsideContextData(VOS_VOID);
/*****************************************************************************
 函 数 名  : NAS_CALL_RestoreContextData
 功能描述  : 恢复CALL全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月1日
    作    者   : 王毛 00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CALL_RestoreContextData(struct MsgCB * pMsg);

/*****************************************************************************
 函 数 名  : MN_CALL_InfoReqProc
 功能描述  : 获取当前所有呼叫的信息
 输入参数  : clientId    - 发起该请求的Client的ID
             opId        - Operation ID, 标识本次操作
             callId      - 呼叫ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : 范晶/00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_CALL_CallInfoReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);


/*****************************************************************************
 函 数 名  : MN_CALL_GetCdur
 功能描述  : 获取指定呼叫的通话时长
 输入参数  : MN_CLIENT_ID_T                      clientId  发起该请求的Client的ID
             MN_OPERATION_ID_T                   opId      Operation ID, 标识本次操作
             MN_CALL_ID_T                        callId    呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月6日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_CALL_GetCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_RcvTafAgentGetCallInfo
 功能描述  : 获取CID的参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_CALL_RcvTafAgentGetCallInfo(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_CALL_GetCallInfoByStatus
 功能描述  : 根据呼叫状态来获取对应的实体呼叫管理信息
 输入参数  : MN_CALL_STATE_ENUM_U8   enCallStatus- 呼叫状态
             MN_CALL_INFO_STRU      *pstCallInfo - 呼叫管理实体信息
 输出参数  : 无
 返 回 值  : VOS_UINT32

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_GetSpecificStatusCallInfo(
    MN_CALL_STATE_ENUM_U8                enCallStatus,
    MN_CALL_INFO_STRU                   *pstCallInfo
);

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
/* 移这部分函数到文件MnCallSendApp.c文件中 */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

/*****************************************************************************
 函 数 名  : MN_CALL_CreateStkMoCallEntity
 功能描述  : 新建一个STK主叫呼叫管理实体，保存所有应用数据到全局变量
 输入参数  : callId         - 呼叫的ID
             enCallType     - 呼叫的类型
             pstOrigParam   - 主叫请求中携带的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
*****************************************************************************/
VOS_VOID  MN_CALL_CreateStkMoCallEntity(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkCallOrig);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateSubAddress
 功能描述  : 获取呼叫实体的子地址
 输入参数  : VOS_UINT8                           ucCallId         呼叫实体索引
             MN_CALL_SUBADDR_STRU               *pstSubCallNumber 子地址
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_UpdateSubAddress(
    VOS_UINT8                           ucCallId,
    MN_CALL_SUBADDR_STRU               *pstSubCallNumber
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateOpId
 功能描述  : 更新呼叫实体的OPID
 输入参数  : VOS_UINT8                           ucCallId         呼叫实体索引
             MN_OPERATION_ID_T                   opId             Operation ID, 标识本次操作
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_UpdateOpId(
    VOS_UINT8                           ucCallId,
    MN_OPERATION_ID_T                   opId
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateCallReleaseFlag
 功能描述  : 更新呼叫实体的释放标志
 输入参数  : VOS_UINT8                           ucCallId         呼叫实体索引
 输出参数  : VOS_BOOL                            bReleaseFlag     呼叫实体的释放标志
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_UpdateCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                            bReleaseFlag
);

/*****************************************************************************
 函 数 名  : MN_CALL_RecordCallEntityRedirectInfo
 功能描述  : 记录CC接入的呼叫信息，包括转移号码和转移号的子号码等
 输入参数  : callId     呼叫的ID
             pstSetup   接入的呼叫信息
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目新增函数
*****************************************************************************/
VOS_VOID  MN_CALL_RecordCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        NAS_CC_MSG_SETUP_MT_STRU            *pstSetup);

/*****************************************************************************
 函 数 名  : MN_CALL_ReadCallEntityRedirectInfo
 功能描述  : 读取转移呼叫号码和转移号码的子地址等信息
 输入参数  : callId     呼叫的ID
             pstSetup   接入的呼叫信息
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目新增函数
*****************************************************************************/
VOS_VOID  MN_CALL_ReadCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        MN_CALL_CLPR_GET_CNF_STRU          *pstGetClprCnf);

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */


/* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */
/*****************************************************************************
 函 数 名  : MN_CALL_AllowSupsOperation
 功能描述  : 判断呼叫相关的补充业务操作是否允许
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否允许呼叫相关的补充业务操作
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : h44270
    修改内容   : STK&DCM 项目新增函数
  2.日    期   : 2013年03月23日
    作    者   : f62575
    修改内容   : DTS2013031406373，解决DTMF过程中呼叫不能挂断问题
*****************************************************************************/
VOS_UINT32 MN_CALL_AllowSupsOperation(VOS_VOID);

/* Deleted by l00198894 for V9R1 STK升级, 2013/07/11 */


/*****************************************************************************
 函 数 名  : MN_CALL_GetNetDiscEventInfo
 功能描述  : 获取UE发起的DISCONNECT, RELEASE, RELEASE COMPLETE消息的CAUSE, CALLID和TI
 输入参数  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE消息
 输出参数  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent 呼叫释放事件结构
             VOS_UINT8                          *pucTi,     消息对应的呼叫TI
             VOS_UINT8                          *pucCallId  消息对应的CALL ID
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR     获取操作成功
                其他                获取操作失败

*****************************************************************************/
VOS_UINT32 MN_CALL_GetNetDiscEventInfo(
    const MNCC_IND_PRIM_MSG_STRU       *pstMsg,
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, begin */
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, end */
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
);

/*****************************************************************************
 函 数 名  : MN_CALL_GetUeDiscEventInfo
 功能描述  : 获取UE发起的DISCONNECT, RELEASE, RELEASE COMPLETE消息的CAUSE,CALLID和TI
 输入参数  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE消息
 输出参数  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent 呼叫释放事件结构
             VOS_UINT8                          *pucTi,     消息对应的呼叫TI
             VOS_UINT8                          *pucCallId  消息对应的CALL ID
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR     获取操作成功
                其他                获取操作失败

*****************************************************************************/
VOS_UINT32 MN_CALL_GetUeDiscEventInfo(
    const MNCC_REQ_PRIM_MSG_STRU       *pstMsg,
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, begin */
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, end */
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
);

VOS_UINT32 MN_CALL_IsNeedCallRedial(
    MN_CALL_ID_T                        ucCallId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
VOS_UINT32 TAF_CALL_IsOrigNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsConfNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsConnNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsCendNeedRpt(VOS_VOID);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/*****************************************************************************
 函 数 名  : MN_CALL_GetCsCause
 功能描述  : 获取指定呼叫的CC原因值信息
 输入参数  : callId    - 需要更新CC原因值的呼叫的ID
 输出参数  : 无
 返 回 值  : TAF_CS_CAUSE_ENUM_UINT32 -CC原因值

 修改历史:

  1.日    期   : 2013年07月09日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目,返回值类型变成TAF_CS_CAUSE_ENUM_UINT32
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32  MN_CALL_GetCsCause(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 函 数 名  : MN_CALL_UpdateDiscCallDir
 功能描述  : 更新CALL挂断的方向
 输入参数  : callId     - 呼叫ID
             ucIsUser   - 是否是用户发起的挂断
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_CALL_UpdateDiscCallDir(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucIsUser
);

VOS_VOID  MN_CALL_GetMgmtEntityInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_MGMT_STRU                   *pstMgmtEntity
);

VOS_UINT8 TAF_CALL_GetDisconnectFlg(
    MN_CALL_ID_T                        callId
);

/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
VOS_VOID TAF_CALL_InitDtmfCtx(VOS_VOID);

VOS_VOID TAF_CALL_ResetDtmfCtx(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_CheckUserDtmfCallId(
    MN_CALL_ID_T                        CallId
);

TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_GetAllowedDtmfCallId(
    MN_CALL_ID_T                       *pCallId
);

TAF_CALL_DTMF_CTX_STRU* TAF_CALL_GetDtmfCtx(VOS_VOID);

TAF_CALL_DTMF_STATE_ENUM_UINT8 TAF_CALL_GetDtmfState(VOS_VOID);

VOS_VOID TAF_CALL_SetDtmfState(
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enState
);

VOS_UINT8 TAF_CALL_GetDtmfBufCnt(VOS_VOID);

HI_LIST_S* TAF_CALL_GetDtmfListHead(VOS_VOID);

TAF_CALL_DTMF_INFO_STRU* TAF_CALL_GetDtmfCurInfo(VOS_VOID);

/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
/* 移这部分函数到文件MnCallSendApp.c文件中 */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_SaveDtmfInfo(
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfInfo
);

VOS_VOID TAF_CALL_DelDtmfNode(
    TAF_CALL_DTMF_NODE_STRU            *pstNode
);
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

VOS_VOID TAF_CALL_PreProcRelAllCall(VOS_VOID);

/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
/* 移这部分函数到文件MnCallSendApp.c文件中 */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_CALL_CreateCallEntitiesWithImsCallInfo(
    VOS_UINT8                           ucSrvccCallNum,
    CALL_IMSA_SRVCC_CALL_INFO_STRU     *pstSrvccCallInfo,
    VOS_UINT8                           ucStartedHifiFlag
);

VOS_VOID TAF_CALL_ProcSrvccDtmfBuffInfo(TAF_CALL_DTMF_BUFF_STRU *pstDtmfBuffInfo);
#endif
MN_CALL_MGMT_STRU *TAF_CALL_GetCallEntityAddr(VOS_VOID);
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */

VOS_UINT32 TAF_CALL_IsCallRedialCause(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_VOID MN_CALl_VoicePreferJudgeVoiceCallExist(VOS_VOID);
VOS_VOID MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_UINT32 ulVoiceFlag);
#endif

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

#endif /* MN_CALL_MGMT_H */

