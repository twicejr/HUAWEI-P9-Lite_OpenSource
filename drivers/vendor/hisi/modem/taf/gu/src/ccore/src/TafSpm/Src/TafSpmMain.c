/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmMain.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : TafSpmMain.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月8日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmCtx.h"
#include "TafSpmMain.h"
#include "TafSpmFsmMainTbl.h"
#include "TafLog.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafSpmProcNvim.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, begin */
#include "TafSdcCtx.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, end */

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, begin */
#include "TafSpmServiceDomainSelProc.h"
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-15, end */
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
#include "TafSpmPreProcTbl.h"
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_MAIN_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SPM_BuildEventType
 功能描述  : 构造EventType
 输入参数  : pstMsg      :  消息内容
 输出参数  : 无
 返 回 值  : ulEventType事件类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID扩展
*****************************************************************************/
VOS_UINT32 TAF_SPM_BuildEventType(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstRcvTimerMsg = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 动作表里的时间消息不能靠消息头名称进行区分，依靠其结构体的ulName域进行区分
        所以此处进行分别处理 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;
        ulEventType    = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstRcvTimerMsg->ulName);

        /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */

        /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */
    }
    else
    {
        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstMsgHeader->ulMsgName);
    }

    return ulEventType;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_MsgProc
 功能描述  : TAF SPM的消息处理函数
 输入参数  : pstSrcMsg       :SPM模块收到的原始消息
             ppstDestMsg     :SPM模块处理完成后的目的消息
 输出参数  : 无
 返 回 值  : VOS_TRUE :当前消息在spm模块处理完成，不需要进入原有MN模块处理
             VOS_FALSE:spm模块处理未完成，需要进入原有MN模块处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年12月17日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 TAF_SPM_MsgProc(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
    REL_TIMER_MSG                      *pstRcvTimerMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader    = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstSrcMsg;

    /* 动作表里的时间消息不能靠消息头名称进行区分，依靠其结构体的ulName域进行区分
        所以此处进行分别处理 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pstRcvTimerMsg = (REL_TIMER_MSG *)pstSrcMsg;

        /* 只停止SPM自己的定时器,其它模块定时器在其内部自己停止 */
        if (MN_TIMER_CLASS_SPM == (pstRcvTimerMsg->ulName & MN_TIMER_CLASS_MASK))
        {
            TAF_SPM_StopTimer(pstRcvTimerMsg->ulName,(VOS_UINT16)pstRcvTimerMsg->ulPara);
        }
    }
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

    ulEventType = TAF_SPM_BuildEventType(pstSrcMsg);

    /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, begin */
    /* 如果已经预处理完成则直接返回 */
    if (VOS_TRUE == TAF_SPM_PreProcessMsg(ulEventType, pstSrcMsg))
    {
        return VOS_TRUE;
    }
    /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, end */

    /* 如果已经处理完成则直接返回 */
    ulRet = TAF_SPM_ProcessMsgInFsm(ulEventType, pstSrcMsg);

    /* 判断是否需要替换入口消息 */
    if (VOS_TRUE == TAF_SPM_GetUpdateEntryMsgFlg())
    {
        pstEntryMsg = TAF_SPM_GetServiceCtrlEntryMsgAddr();
       *ppstDestMsg = (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer;

        /* 消息已经使用，回复设置标记位，但不能清除消息。  */
        TAF_SPM_SetUpdateEntryMsgFlg(VOS_FALSE);
    }
    else
    {
       *ppstDestMsg = pstSrcMsg;
    }

    /* 继续处理处理 */
    return ulRet;
}



/*****************************************************************************
 函 数 名  : TAF_SPM_RegFsm
 功能描述  : 各个状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月8日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年01月02日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_VOID TAF_SPM_RegFsm( VOS_VOID  )
{
    /* Added by s00217060 for VoLTE_PhaseIII  项目, 2014-01-02, begin */
    /* 预处理注册 */
    TAF_FSM_RegisterFsm((TAF_SPM_GetPreFsmDescAddr()),
                         "TAF_SPM:FSM:PreProcess",
                         TAF_SPM_GetPreProcessStaTblSize(),
                         TAF_SPM_GetPreProcessStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    /* Added by s00217060 for VoLTE_PhaseIII  项目, 2014-01-02, end */

    /* 主处理状态机注册 */
    TAF_FSM_RegisterFsm(TAF_SPM_GetMainFsmDescAddr(),
                         "TAF_SPM:FSM:MainProcess",
                         TAF_SPM_GetMainProcessStaTblSize(),
                         TAF_SPM_GetMainProcessStaTbl(),
                         VOS_NULL_PTR,
                         TAF_SPM_InitFsmCtx_Main);

    /* service ctrl状态机注册 */
    TAF_FSM_RegisterFsm(TAF_SPM_GetServiceCtrlFsmDescAddr(),
                         "TAF_SPM:FSM:ServiceCtrlProcess",
                         TAF_SPM_GetServiceCtrlStaTblSize(),
                         TAF_SPM_GetServiceCtrlProcessStaTbl(),
                         VOS_NULL_PTR,
                         TAF_SPM_InitFsmCtx_ServiceCtrl);


    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_PreProcessMsg
 功能描述  : SPM消息预处理
 输入参数  : ulEventType  :消息类型
             pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:预处理完成
             VOS_FALSE:还需要进行状态机中处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    TAF_ACTION_FUNC                     pActFun;
    VOS_UINT32                          ulRet;

    ulRet   = VOS_TRUE;

    TAF_INFO_LOG1(WUEPS_PID_TAF,"TAF_SPM_PreProcessMsg", ulEventType);

    /* 消息预处理 */
    pstFsmDesc = TAF_SPM_GetPreFsmDescAddr();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, TAF_SPM_MAIN_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 预处理消息,分为两类消息,一类为预处理结束就返回,另外一类为预处理
        结束后,仍然需要进行到状态机中继续处理,因此此处直接通过函数返回预处
        理结束后是否需要进行状态机处理*/
        ulRet = (*pActFun) ( ulEventType, (struct MsgCB*)pstMsg);
        return ulRet;
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcessMsgInFsm
 功能描述  : 对消息进行状态机处理
 输入参数  : ulEventType: 消息事件类型
             pstMsg     : 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucFsmIndex;
    VOS_UINT8                           ucNewFsmIndex;
    VOS_UINT16                          usClientId;

    ulRet       = VOS_FALSE;
    usClientId  = TAF_SPM_INVALID_CLIENT_ID;
    ucFsmIndex  = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    /* 获取到client ID后才在实体状态机中进行查找相同 client ID,否则直接在main状态机中进行处理 */
    if (VOS_TRUE == TAF_SPM_GetClientId(pstMsg, &usClientId))
    {
        ucFsmIndex = TAF_SPM_GetEntityFsmIndexByClientId(usClientId);
    }

    /* 状态机索引有效,说明有相同client ID的实体状态机在运行 */
    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX != ucFsmIndex)
    {
        /* 设置当前client ID实体状态机的client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* 设置当前client ID实体状态机的数组索引 */
        TAF_SPM_SetCurrEntityFsmAddr(ucFsmIndex);

        /* 消息进入client ID实体状态机处理 */
        ulRet   = TAF_SPM_ProcessMsgInEntityFsm(ucFsmIndex, ulEventType, pstMsg);

        return ulRet;
    }

    /* 索引无效说明未找到相同client id的状态机,需要在main中继续查找 */
    ulRet = TAF_SPM_FSM_ProcessEvent(TAF_SPM_MAIN_STA_IDLE, ulEventType, pstMsg, TAF_SPM_GetMainFsmDescAddr());

    /* 已经处理完成返回 */
    if (VOS_FALSE == ulRet)
    {
        return VOS_FALSE;
    }

    /* 说明有可能启动了状态机,需要获取新的空闲client ID实体状态机索引  */
    ucNewFsmIndex = TAF_SPM_GetEntityFsmIndexByClientId(usClientId);

    /* 索引有效则取出指定的状态机ID */
    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX != ucNewFsmIndex)
    {
        /* 设置当前client ID实体状态机的client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* 设置当前client ID实体状态机的数组索引 */
        TAF_SPM_SetCurrEntityFsmAddr(ucNewFsmIndex);

        /* 主状态机有可能启动状态机,如果启动状态机,消息还需要进子状态机处理 */
        ulRet = TAF_SPM_ProcessMsgInEntityFsm(ucNewFsmIndex, ulEventType, pstMsg);
    }

    return ulRet;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcessMsgInEntityFsm
 功能描述  : 在client ID实体状态机里对消息进行处理
 输入参数  : ucFsmIndex   :状态机索引
             ulEventType  :消息事件类型
             pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcessMsgInEntityFsm(
    VOS_UINT8                           ucFsmIndex,
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    TAF_SPM_FSM_CTX_STRU               *pstCurrSubFsm = VOS_NULL_PTR;

    /*  获取指定索引的Sub状态机 */
    pstCurrSubFsm   = TAF_SPM_GetEntityFsmCtxAddrByFsmIndex(ucFsmIndex);

    ulRet           = TAF_SPM_FSM_ProcessEvent(pstCurrSubFsm->ulState, ulEventType,
                                               pstMsg, pstCurrSubFsm->pstFsmDesc);

    return ulRet;
}


/*****************************************************************************
 函 数 名    : TAF_SPM_FSM_ProcessEvent
 功能描述    : 状态机的事件处理函数
 输入参数    : ulCurState :当前状态
               ulEventType:处理事件
               ulMsgID    :消息ID
               pRcvMsg    :消息指针
               pstFsmDesc :状态机描述表
 输出参数    :
 返回值      : VOS_UINT32:处理是否完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : w00176964
    修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 TAF_SPM_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg,
    TAF_FSM_DESC_STRU                  *pstFsmDesc
)
{
    TAF_ACTION_FUNC                     pActFun = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_SPM_FSM_ProcessEvent", ulCurState, ulEventType);

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        TAF_INFO_LOG1(WUEPS_PID_TAF,"TAF_SPM_FSM_ProcessEvent", ulRet);
        return ulRet;
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_Init
 功能描述  : SPM初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SPM_Init(VOS_VOID)
{
    /* 初始化SPM模块CTX */
    TAF_SPM_InitCtx(TAF_SPM_GetSpmCtxAddr());

    /*注册状态机*/
    TAF_SPM_RegFsm();

    /* 读取NV操作 */
    TAF_SPM_ReadNvimInfo();

    /* 默认值启动MAIN状态机 */
    TAF_SPM_FSM_InitMainFsm(TAF_SPM_FSM_MAIN, TAF_SPM_GetMainFsmDescAddr(), TAF_SPM_MAIN_STA_IDLE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitCtx
 功能描述  : SPM CTX模块初始化
 输入参数  : pstSpmCtx-SPM模块上下文
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月8日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 增强型多方通话
*****************************************************************************/
VOS_VOID  TAF_SPM_InitCtx(
    TAF_SPM_CONTEXT_STRU               *pstSpmCtx
)
{
    /* 初始化所有的实体状态机 */
    TAF_SPM_InitEntityFsm();

    TAF_SPM_InitMainFsm();

    /* 初始化SPM定时器上下文 */
    TAF_SPM_InitAllTimers(pstSpmCtx->astSpmTimerCtx);

    TAF_SPM_InitMainCtrlInfo(&(pstSpmCtx->stMainCtrlInfo));

    TAF_SPM_InitServiceCtrlCfgInfo(&(pstSpmCtx->stServiceCtrlCfgInfo));

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-28, begin */
    TAF_SPM_InitServiceReqBufferMsgQueue();
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-28, end */

    /* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, begin */
#if (FEATURE_IMS == FEATURE_ON)
    TAF_SPM_InitDomainSelCtx(&(pstSpmCtx->stDomainSelCtx));

    TAF_SPM_InitEconfInfo();
#endif
    /* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, end */
}


/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

