/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcEntityMgmt.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年10月15日
  最近修改   : 2007年10月15日
  功能描述   : 定义CC实体管理模块的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2007年10月15日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年7月12日
    作    者   : 梁金广 65478
    修改内容   : 问题单号:AT2D04057
  3.日    期   : 2008年12月15日
    作    者   :S62952
    修改内容   : 问题单号:AT2D07162
******************************************************************************/
#ifndef  NAS_CC_ENTITY_MGMT_H
#define  NAS_CC_ENTITY_MGMT_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasCcCommon.h"
#include "NasCcCtx.h"
#include "NasCcIe.h"
#include "NasSsIe.h"
#include "NasCcInclude.h"
/* Added by n00355355 for 呼叫重建, 2015-9-18, begin */
#include "MmCcInterface.h"
/* Added by n00355355 for 呼叫重建, 2015-9-18, end */

/*****************************************************************************
  2 类型定义
*****************************************************************************/
/* MPTY事件 */
typedef enum
{
    NAS_CC_MPTY_EVT_INVOKE,                                                     /* 发起了一个MPTY操作 */
    NAS_CC_MPTY_EVT_SUCCESS,                                                    /* MPTY操作成功 */
    NAS_CC_MPTY_EVT_FAIL,                                                       /* MPTY操作失败 */
    NAS_CC_MPTY_EVT_MAX
} NAS_CC_MPTY_EVT_ENUM;


/* DTMF状态 */
typedef enum
{
    NAS_CC_DTMF_S_IDLE,                                                         /* 空闲，可以发起新的DTMF操作 */
    NAS_CC_DTMF_S_START_REQ,                                                    /* 已经向网络发出START DTMF消息，还未收到回复 */
    NAS_CC_DTMF_S_STOP_REQ,                                                     /* 已经向网络发出STOP DTMF消息，还未收到回复 */

    NAS_CC_DTMF_S_START_REJ,                                                    /* 收到网络的start dtmf rej消息*/

    NAS_CC_DTMF_S_UNKNOWN
} NAS_CC_DTMF_STATE_ENUM;

/* DTMF缓冲状态 */
typedef enum
{
    NAS_CC_DTMF_Q_NULL,                                                         /* 缓冲区为空*/
    NAS_CC_DTMF_Q_START_REQ,                                                    /* 最近存入的为START DTMF消息*/
    NAS_CC_DTMF_Q_STOP_REQ,                                                     /* 最近存入的为STOP DTMF消息*/
    NAS_CC_DTMF_Q_UNKNOWN
} NAS_CC_DTMF_Q_STATE_ENUM;

/* DTMF请求类型 */
enum NAS_CC_DTMF_REQ_ENUM
{
    NAS_CC_DTMF_START_REQ,
    NAS_CC_DTMF_STOP_REQ,
    NAS_CC_DTMF_REQ_BUTT
};
typedef VOS_UINT8  NAS_CC_DTMF_REQ_ENUM_U8;


/* 承载能力参数索引 */
enum NAS_CC_BC_PARAM_IDX_ENUM
{
    NAS_CC_BC_PARAM_1,                                                          /* 来自BC1的参数 */
    NAS_CC_BC_PARAM_2,                                                          /* 来自BC2的参数 */
    NAS_CC_BC_PARAM_CURR                                                        /* 当前使用的BC参数 */
};
typedef VOS_UINT8  NAS_CC_BC_PARAM_IDX_ENUM_U8;

/*****************************************************************************
 枚举名    : NAS_CC_OM_MSG_ID_ENUM_U32
 结构说明  : CC发送给OM的可维可测消息
  1.日    期   : 2014年6月30日
    作    者   : w00242748
    修改内容   : CC发送给OM的可维可测消息ID枚举
  2.日    期   : 2014年12月20日
    作    者   : b00269685
    修改内容   : 增加缓存的消息打印
*****************************************************************************/
enum NAS_CC_OM_MSG_ID_ENUM
{
    /* CC发送给OM的消息 */
    CCOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_CC_LOG_STATE_INFO_STRU */
    CCOM_LOG_BUFFER_MSG_INFO_IND                  = 0x1001,      /*_H2ASN_MsgChoice  NAS_CC_LOG_BUFFER_MSG_INFO_STRU */
    CCOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_CC_OM_MSG_ID_ENUM_UINT32;

#define NAS_CC_MAX_BC_PARAM_NUM    (NAS_CC_BC_PARAM_2 + 1)


/* 承载能力参数结构 */
typedef struct
{
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enItc;
} NAS_CC_BC_PARAMS_STRU;

/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
typedef void (*NAS_CC_FUNC_VOID)(void);

/*****************************************************************************
结构名    : NAS_CC_SS_SWITCH_PROC_FUNC_MAP_STRU
结构说明  : CC模块补充业务状态切换函数对照表
1.日    期  : 2013年07月11日
  作    者  : l00198894
  修改内容  : V9R1 STK升级项目
*****************************************************************************/
typedef struct
{
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enHoldState;                            /* 呼叫保持业务切换状态 */
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enRetrieveState;                        /* 呼叫恢复业务切换状态 */
    NAS_CC_FUNC_VOID                    pFunc;
} NAS_CC_SS_SWITCH_PROC_FUNC_MAP_STRU;
/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

/*****************************************************************************
 结构名    : NAS_CC_LOG_STATE_INFO_STRU
 结构说明  : 勾CC的状态的结构

 修改记录  :
 1.日    期   : 2014年06月30日
   作    者   : w00242748
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    NAS_CC_CALL_STATE_ENUM_U8           enCcState;
    VOS_UINT8                           aucRsv3[3];
}NAS_CC_LOG_STATE_INFO_STRU;




/*****************************************************************************
  3 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_CC_InitEntities
 功能描述  : 初始化所有CC实体，在CC模块初始化时必须调用该函数。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_CC_InitEntities(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_CC_CreateEntity
 功能描述  : 创建并初始化一个CC实体
 输入参数  : ucCallId  - 上层的呼叫ID，在主叫过程中该参数可以从来自上层的原语中
                         得到；在被叫过程中该参数无意义，可填任意值
             ucTi      - 呼叫的Transcation ID. 在主叫过程中填为CC_INVALID_TI_VALUE，
                         本函数将为新建的实体分配一个新的Ti；在被叫过程中需从来自
                         MM的原语中获得该参数值并传入函数。
 输出参数  : pEntityId - 新创建的CC实体的ID
 返 回 值  : VOS_TRUE - 创建成功  VOS_FALSE - 创建失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_CC_CreateEntity(
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucTi,
    NAS_CC_ENTITY_ID_T                  *pEntityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_DeleteEntity
 功能描述  : 删除一个CC实体
 输入参数  : entityId - 需要删除的实体ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_DeleteEntity(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetEntityByTi
 功能描述  : 取得与指定Ti值对应的CC实体的ID
 输入参数  : ucTi - Transcation ID
 输出参数  : 无
 返 回 值  : 取得的CC实体ID. 如果没有找到对应实体，则返回CC_INVALID_ENTITY_ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
NAS_CC_ENTITY_ID_T  NAS_CC_GetEntityByTi(
    VOS_UINT8                           ucTi
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetEntityTi
 功能描述  : 取得指定CC实体的Ti值
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 该实体的Ti值.
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  NAS_CC_GetEntityTi(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetCallId
 功能描述  : 取得指定CC实体的Call ID值
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 该实体的Call ID.
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  NAS_CC_GetCallId(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_UpdateCallId
 功能描述  : 更新指定CC实体的Call ID值
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID  NAS_CC_UpdateCallId(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucCallId
);


/*****************************************************************************
 函 数 名  : NAS_CC_UpdateBcParams
 功能描述  : 更新实体中保存的承载能力参数
 输入参数  : entityId  - CC实体的ID
              enIdx     - 需要更新的承载能力参数的索引(BC1 or BC2)
              pstParams - 承载能力参数的内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月27日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_UpdateBcParams(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_BC_PARAM_IDX_ENUM_U8         enIdx,
    const NAS_CC_BC_PARAMS_STRU         *pstParams
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetBcParams
 功能描述  : 取得实体中保存的承载能力参数
 输入参数  : entityId  - CC实体的ID
              enIdx     - 需要获取的承载能力参数的索引(BC1, BC2 or Current)
 输出参数  : pstParams - 取得的承载能力参数的内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月27日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_GetBcParams(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_BC_PARAM_IDX_ENUM_U8         enIdx,
    NAS_CC_BC_PARAMS_STRU               *pstParams
);


/*****************************************************************************
 函 数 名  : NAS_CC_BcAlertnate
 功能描述  : BC发生交替，该函数将是当前使用的BC参数集发生切换
 输入参数  : entityId  - CC实体的ID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月27日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_BcAlertnate(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetCallState
 功能描述  : 取得指定CC实体的呼叫状态
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 该实体的呼叫状态.
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
NAS_CC_CALL_STATE_ENUM_U8  NAS_CC_GetCallState(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_ChangeCallState
 功能描述  : 改变指定CC实体的呼叫状态。该函数还会做一些在进入新状态时每个流程
             都必须的执行的操作，如进入NULL状态时释放CC实体等。
 输入参数  : entityId - CC实体的ID
             state    - 新的呼叫状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeCallState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_CALL_STATE_ENUM_U8           enState
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetHoldAuxState
 功能描述  : 取得指定CC实体的呼叫保持状态
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 该实体的呼叫保持状态.
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
NAS_CC_HOLD_AUX_STATE_ENUM_U8 NAS_CC_GetHoldAuxState(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_ChangeHoldAuxState
 功能描述  : 改变指定CC实体的呼叫保持状态
 输入参数  : entityId - CC实体的ID
              state    - 新的呼叫保持状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeHoldAuxState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       state
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetMptyAuxState
 功能描述  : 取得指定CC实体的Mpty状态
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 该实体的Mpty状态.
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
NAS_CC_MPTY_AUX_STATE_ENUM_U8 NAS_CC_GetMptyAuxState(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_ChangeMptyAuxState
 功能描述  : 改变指定CC实体的Mpty状态
 输入参数  : entityId - CC实体的ID
             state    - 新的Mpty状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeMptyAuxState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enState
);


/*****************************************************************************
 函 数 名  : NAS_CC_CheckMptyOperation
 功能描述  : 检查MPTY操作是否可以在当前状态下进行
 输入参数  : entityId      - 需要检查的操作
             enSsOperation - 操作的补充业务码
 输出参数  : 无
 返 回 值  : VOS_OK - 检查通过； VOS_ERR - 检查失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_CheckMptyOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
);


/*****************************************************************************
 函 数 名  : NAS_CC_HandleMptyEvent
 功能描述  : 处理MPTY事件，根据发生的事件改变各个CC实体的从状态
 输入参数  : entityId      - 发生事件的CC实体的ID
              enMptyEvent   - 发生的事件
              operationCode - 引起该事件的补充业务操作码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_HandleMptyEvent(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MPTY_EVT_ENUM                enMptyEvent,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetDtmfState
 功能描述  : 获取指定CC实体的DTMF状态
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 该实体的DTMF状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
NAS_CC_DTMF_STATE_ENUM  NAS_CC_GetDtmfState(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_ChangeDtmfState
 功能描述  : 改变指定CC实体的DTMF状态
 输入参数  : entityId - CC实体的ID
              state    - 新的DTMF状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeDtmfState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_DTMF_STATE_ENUM              enState
);


/*****************************************************************************
 函 数 名  : NAS_CC_PushStartDtmfReq
 功能描述  : 将一个Start DTMF请求存入缓存队列
 输入参数  : entityId  - CC实体的ID
              enDtmfReq - DTMF请求的类型(START/STOP)
              ucKey     - Start DTMF请求中的DTMF字符，仅当请求类型为START时有效
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月22日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_QueueDtmfReq(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_DTMF_REQ_ENUM_U8             enDtmfReq,
    VOS_UINT8                           ucKey
);


/*****************************************************************************
 函 数 名  : NAS_CC_SendBufferedDtmfReq
 功能描述  : 发送一个缓存的DTMF请求
 输入参数  : entityId  - CC实体ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_CC_SendBufferedDtmfReq(
    NAS_CC_ENTITY_ID_T                  entityId
);


/*****************************************************************************
 函 数 名  : NAS_CC_StoreSsOperation
 功能描述  : 通过invoke类型的facility消息发起补充业务操作时，调用该函数存储该
             补充业务操作，以便收到网络的facility回复时能由invoke ID得到相应的
             补充业务操作码
 输入参数  : entityId      - CC实体的ID
              ucInvokeId    - 补充业务操作的invoke ID
              enSsOperation - 补充业务操作码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_StoreSsOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucInvokeId,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
);


/*****************************************************************************
 函 数 名  : NAS_CC_RestoreSsOperation
 功能描述  : 取得存储的补充业务操作，并清除该存储项
 输入参数  : entityId      - CC实体的ID
              ucInvokeId    - 补充业务操作的invoke ID
 输出参数  : penSsOperation - 取得的补充业务操作码
 返 回 值  : VOS_OK - 操作成功；VOS_ERR - 没有找到符合条件的存储项，操作失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_RestoreSsOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucInvokeId,
    NAS_SS_OPERATION_ENUM_U8            *penSsOperation
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetStoredSsOperation
 功能描述  : 取得存储的补充业务操作
 输入参数  : entityId      - CC实体的ID
              ucInvokeId    - 补充业务操作的invoke ID
 输出参数  : penSsOperation - 取得的补充业务操作码
 返 回 值  : VOS_OK - 操作成功；VOS_ERR - 没有找到符合条件的存储项，操作失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_CC_GetStoredSsOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucInvokeId,
    NAS_SS_OPERATION_ENUM_U8            *penSsOperation
);

/*****************************************************************************
 函 数 名  : NAS_CC_SetStartT310Flag
 功能描述  : 设置是否启T310定时器标志
 输入参数  : entityId - CC实体的ID
             ulSet     - 设置标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月06日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SetStartT310Flag(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulSet
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetStartT310Flag
 功能描述  : 获取是否启动T310的标志
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : 标志的状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月06日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_CC_GetStartT310Flag(
    NAS_CC_ENTITY_ID_T                  entityId
);

/*****************************************************************************
 函 数 名  : NAS_CC_IsAllowNewMtCall
 功能描述  : 判定是否能接收新的MT呼叫
 输入参数  : entityId - CC实体的ID
 输出参数  : 无
 返 回 值  : progress标志的状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月15日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL  NAS_CC_IsAllowNewMtCall(VOS_VOID);
/*****************************************************************************
 函 数 名  : NAS_CC_FlushDTMFBuff
 功能描述  : 清除缓存的DTMF消息
 输入参数  : entityId - CC实体ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月12日
    作    者   : 梁金广 65478
    修改内容   : 问题单号:AT2D04057
*****************************************************************************/
VOS_VOID NAS_CC_FlushDTMFBuff(
    NAS_CC_ENTITY_ID_T                  entityId
);
/*****************************************************************************
 函 数 名  : NAS_CC_SndOutsideContextData
 功能描述  : 把CC外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月30日
    作    者   : 王毛 00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_CC_SndOutsideContextData(VOS_VOID);

/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
NAS_CC_CALL_TYPE_ENUM_U8  NAS_CC_GetCallType(
    NAS_CC_ENTITY_ID_T                  entityId
);

VOS_BOOL  NAS_CC_IsSpecCallEntityInUse(
    NAS_CC_ENTITY_ID_T                  entityId
);

/* Added by n00355355 for 呼叫重建, 2015-9-17, end */



#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 函 数 名  : NAS_CC_RestoreContextData
 功能描述  : 恢复CC全局变量。
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
VOS_UINT32 NAS_CC_RestoreContextData(struct MsgCB * pMsg);
#endif


/*****************************************************************************
 函 数 名  : NAS_CC_ProcAtPrimitive
 功能描述  : 接收和处理来自AT的原语
 输入参数  : pMsg - AT发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : o00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ProcAtPrimitive(
    const VOS_VOID                      *pMsg
);

/*****************************************************************************
 函 数 名  : NAS_CC_ProcAtCcStateQry
 功能描述  : 接收和处理来自AT的AT_CC_MSG_STATE_QRY_REQ原语
 输入参数  : pMsg - AT发给CC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : o00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_ProcAtCcStateQry(
    const VOS_VOID                      *pMsg
);


/*****************************************************************************
 函 数 名  : NAS_CC_GetEntityByCallId
 功能描述  : 取得与指定CallId值对应的CC实体的ID
 输入参数  : ucCallId - 呼叫ID
 输出参数  : 无
 返 回 值  : 取得的CC实体ID. 如果没有找到对应实体，则返回CC_INVALID_ENTITY_ID
*****************************************************************************/
NAS_CC_ENTITY_ID_T  NAS_CC_GetEntityByCallId(
    VOS_UINT8                           ucCallId
);

/* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
VOS_UINT32 NAS_CC_CheckSsSwitchHoldAllowed(VOS_VOID);

VOS_UINT32 NAS_CC_CheckSsSwitchRetrieveAllowed(VOS_VOID);

VOS_VOID NAS_CC_ProcSsSwitchSingleCallRetrieveSucc(VOS_VOID);

VOS_VOID NAS_CC_ProcSsSwitchSingleCallRetrieveFail(VOS_VOID);

VOS_VOID NAS_CC_ProcSsSwitchSingleCallHoldSucc(VOS_VOID);

VOS_VOID NAS_CC_ProcSsSwitchSingleCallHoldFail(VOS_VOID);

VOS_VOID NAS_CC_ProcSsSwitchMultiCallSucc(VOS_VOID);

VOS_VOID NAS_CC_ProcSsSwitchMultiCallFail(VOS_VOID);

VOS_VOID NAS_CC_ProcSsSwitchMain(VOS_VOID);

/* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_VOID NAS_CC_ProcSsSwitchCallRelease(NAS_CC_ENTITY_ID_T EntityID);
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  NAS_CC_CreateCcEntityWithCallEntityInfo(
    VOS_VOID                           *pMsg
);
#endif

VOS_VOID  NAS_CC_DeleteAllEntities(VOS_VOID);
VOS_VOID  NAS_CC_GetEntityTiInfo(
    VOS_UINT8                          *pucTiNum,
    VOS_UINT8                          *pucTi
);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */

VOS_UINT32  NAS_CC_IsOnlySpecTypeCall(
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType
);

MMCC_SESSION_TYPE_ENUM_UINT8  NAS_CC_ConvertCallTypeToSessionType(
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_CC_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
);
VOS_VOID NAS_CC_RcvAcpuOmErrLogRptReq(
    const VOS_VOID                           *pMsg
);
VOS_VOID NAS_CC_RcvAcpuOmErrLogCtrlInd(
    const VOS_VOID                           *pMsg
);
VOS_VOID NAS_CC_RcvAcpuOmMsg(
    const VOS_VOID                     *pMsg
);
#endif

VOS_UINT32 NAS_CC_IsLastCallEntityID(NAS_CC_ENTITY_ID_T EntityID);

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

#endif /* NAS_CC_ENTITY_MGMT_H */

