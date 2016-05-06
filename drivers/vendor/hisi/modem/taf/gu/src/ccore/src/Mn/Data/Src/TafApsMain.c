
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsMain.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : 总消息入口处理函数，全局变量的初始化，预处理的消息入口,
               状态机入口消息
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : S62952
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafFsm.h"
#include "TafApsCtx.h"
#include "TafApsMain.h"
#include "TafApsPreProcTbl.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafLog.h"
#include "PsCommonDef.h"
#include "TafApsGetPdpIdList.h"
#include "TafApsProcIpFilter.h"
#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsFsmCdataDiscingTbl.h"
#include "TafApsMntn.h"
#include "TafApsFsmCdataHandOffTbl.h"


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_MAIN_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_RegMainFsm
 功能描述  : APS Main状态机处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RegMainFsm( VOS_VOID  )
{
    /* 状态机注册 */

    TAF_FSM_RegisterFsm((TAF_APS_GetMainFsmDescAddr()),
                         "TAF:FSM:APS:MAIN",
                         (VOS_UINT32)(TAF_APS_GetMainFsmStaTblSize()),
                         TAF_APS_GetMainFsmStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RegSubFsm
 功能描述  : Sub状态机处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RegSubFsm( VOS_VOID  )
{

    /* MS ACTIVATING状态机注册 */
    TAF_FSM_RegisterFsm((TAF_APS_GetMsActivatingFsmDescAddr()),
                         "TAF:FSM:APS:Ms Activating",
                         (VOS_UINT32)TAF_APS_GetMsActivatingStaTblSize(),
                         TAF_APS_GetMsActivatingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);


    /* NW ACTIVATING状态机注册 */
    TAF_FSM_RegisterFsm((TAF_APS_GetNwActivatingFsmDescAddr()),
                         "TAF:FSM:APS:Nw Activating",
                         (VOS_UINT32)TAF_APS_GetNwActivatingStaTblSize(),
                         TAF_APS_GetNwActivatingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /*MS DEACTIVATING状态机注册 */
    TAF_FSM_RegisterFsm((TAF_APS_GetMsDeactivatingFsmDescAddr()),
                         "TAF:FSM:APS:MS Deactivating",
                         (VOS_UINT32)TAF_APS_GetMsDeactivatingStaTblSize(),
                         TAF_APS_GetMsDeactivatingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* MS MODIFYING状态机注册 */
    TAF_FSM_RegisterFsm((TAF_APS_GetMsModifyingFsmDescAddr()),
                         "TAF:FSM:APS:Ms Modifying",
                         (VOS_UINT32)TAF_APS_GetMsModifyingStaTblSize(),
                         TAF_APS_GetMsModifyingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* CDATA ESTING状态机注册 */
    TAF_FSM_RegisterFsm((TAF_APS_GetCdataEstingFsmDescAddr()),
                         "TAF:FSM:APS:CDATA ESTING",
                         (VOS_UINT32)TAF_APS_GetCdataEstingStaTblSize(),
                         TAF_APS_GetCdataEstingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* CDATA DISCING状态机注册 */
    TAF_FSM_RegisterFsm((TAF_APS_GetCdataDiscingFsmDescAddr()),
                         "TAF:FSM:APS:CDATA DISCING",
                         (VOS_UINT32)TAF_APS_GetCdataDiscingStaTblSize(),
                         TAF_APS_GetCdataDiscingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    /* CDATA HANDOFF状态机注册 */
    TAF_FSM_RegisterFsm((TAF_APS_GetCdataHandOffFsmDescAddr()),
                         "TAF:FSM:APS:CDATA HANDOFF",
                         (VOS_UINT32)TAF_APS_GetCdataHandOffStaTblSize(),
                         TAF_APS_GetCdataHandOffStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RegPreFsm
 功能描述  : APS预处理状态机注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RegPreFsm( VOS_VOID  )
{
    /* 预处理注册 */

    TAF_FSM_RegisterFsm((TAF_APS_GetPreFsmDescAddr()),
                         "NAS:FSM:MMC:PreProcess",
                         TAF_APS_GetPreProcessStaTblSize(),
                         TAF_APS_GetPreProcessStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_InitTask
 功能描述  : APS初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : DTS2015022600839: 流量上下文初始化放到任务初始化函数中
*****************************************************************************/
VOS_VOID  TAF_APS_InitTask( VOS_VOID )
{

    /* 初始化APS模块CTX */
    TAF_APS_InitCtx();

    /* 初始化APS流量统计上下文 */
    TAF_APS_InitDsFlowCtx(TAF_APS_GetDsFlowCtxAddr());

    /* 初始化DDR调频信息 */
    TAF_APS_InitSwitchDdrInfo();

    /*注册状态机*/
    TAF_APS_RegFsm();

    return;
}
/*****************************************************************************
 函 数 名  : TAF_APS_InitEntityFsm
 功能描述  : 实体状态机的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月28日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年6月27日
    作    者   : A00165503
    修改内容   : DTS2012062608382: APS初始化PS域卡状态为有效, 规避MMC不通知-
                 APS的场景下发起PDP激活失败
*****************************************************************************/
VOS_VOID  TAF_APS_InitEntityFsm( VOS_VOID )
{
    VOS_UINT8                           i;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstCurrPdpEntityFsm;

    /* for 循环，初始化所有实体状态机上下文，包括主状态机和子状态机 */
    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        /* 根据设置当前的实体状态机 */
        TAF_APS_SetCurrPdpEntityFsmAddr(i);
        pstCurrPdpEntityFsm = TAF_APS_GetCurrPdpEntityFsmAddr();

        /* 初始化实体上下文 */
        TAF_APS_InitMainFsmCtx(&pstCurrPdpEntityFsm->stMainFsm);
        TAF_APS_InitSubFsmCtx(&pstCurrPdpEntityFsm->stSubFsm);

        pstCurrPdpEntityFsm->ucPdpId = TAF_APS_INVALID_PDPID;                       /* 当前状态机所对应的PDP ID */

        pstCurrPdpEntityFsm->ucCallActiveFlg = VOS_FALSE;
    }

}
/*****************************************************************************
 函 数 名  : TAF_APS_InitCtx
 功能描述  : APS CTX模块初始化
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月16日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年06月16日
    作    者   : m00217266
    修改内容   : 添加PDP激活受限上下文初始化(AT&T&DCM定制 PDP激活受限)

  3.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: 增加呼叫建立保护定时器时长初始化

  4.日    期   : 2014年11月1日
    作    者   : A00165503
    修改内容   : DTS2014122908593: 增加PDN连接断开策略初始化

  5.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : DTS2015022600839: 流量上下文初始化放到任务初始化函数中
*****************************************************************************/
VOS_VOID  TAF_APS_InitCtx( VOS_VOID )
{
    TAF_APS_CONTEXT_STRU               *pApsCtx;

    /* 初始化APS模块CTX */
    pApsCtx   = TAF_APS_GetApsCtxAddr();

    /* 初始化所有的实体状态机 */
    TAF_APS_InitEntityFsm();

    /* 初始化内部缓存队列 */
    TAF_APS_InitInternalBuffer(TAF_APS_GetCachMsgBufferAddr());

    /* 初始化APS定时器上下文 */
    TAF_APS_InitAllTimers(TAF_APS_GetTimerCtxAddr());


    /* 初始化内部消息队列 */
    TAF_APS_InitInternalMsgQueue(&pApsCtx->stInternalMsgQueue);

    /* 初始化AT命令缓存队列 */
    TAF_APS_InitCmdBufferQueue(TAF_APS_GetCmdBufferQueueAddr());

    /* 初始化上行NDIS Filter有效 */
    TAF_APS_SetUlNdisFilterValidFlag(TAF_APS_UL_NDIS_FILTER_VALID);

    /* 初始化上行NDIS需要使用的IP Filter定义 */
    TAF_APS_IpfUlNdisFilterInit();

    /* 初始化PDP激活受限标志，和PDP激活失败次数计数器 */
    TAF_APS_InitPdpActLimitInfo();

    /* 初始化呼叫保护定时器时长 */
    TAF_APS_InitCallRemainTmrLen();

    TAF_APS_SET_RAT_TYPE_IN_SUSPEND(TAF_APS_RAT_TYPE_NULL);

    TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_NULL);
    TAF_APS_SetCurrPdpEntitySimRegStatus(VOS_TRUE);
    /* 设置当前PS业务所在的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_NULL);

#if (FEATURE_ON == FEATURE_LTE)
    /* 初始化PDN连接断开策略配置信息 */
    TAF_APS_InitPdnTeardownPolicy();
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_Set1XPsServiceStatus(VOS_FALSE);
    TAF_APS_SetClDelaySearch(VOS_TRUE);
    TAF_APS_SetIsHrpdDisabledFlag(VOS_FALSE);

    TAF_APS_InitCdataCtx();
    TAF_APS_Init3GpdOpInfo();
    g_stTafApsCtx.ulIsAlreadyRead3GpdFile = VOS_FALSE;
    g_stTafApsCtx.ulReadSim3GpdFileFlg      = TAF_APS_READ_USIM_FILE_FLG_NULL;
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RegFsm
 功能描述  : 注册状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_RegFsm( VOS_VOID )
{
    /* 注册预处理状态机 */
    TAF_APS_RegPreFsm();

    /* 注册主状态机 */
    TAF_APS_RegMainFsm();

    /* 注册子状态机 */
    TAF_APS_RegSubFsm();

}

/*****************************************************************************
 函 数 名    : TAF_APS_FSM_ProcessEvent
 功能描述    : 状态机的事件处理函数
 输入参数    :
               ulCurState :当前状态
               ulEventType:处理事件
               ulMsgID    :消息ID
               pRcvMsg    :消息指针
               pstFsmDesc :状态机描述表
 输出参数    :
 返回值      : VOS_UINT32:处理是否完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 TAF_APS_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg,
    TAF_FSM_DESC_STRU                  *pstFsmDesc
)
{
    TAF_ACTION_FUNC                     pActFun;
    VOS_UINT32                          ulRet;

    TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_FSM_ProcessEvent", ulCurState, ulEventType);

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 如果返回的事件处理函数不为空,调用它进行事件处理 */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        TAF_INFO_LOG1(WUEPS_PID_TAF,"TAF_APS_FSM_ProcessEvent", ulRet);
        return VOS_TRUE;
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_ProcessBufferMsg
 功能描述  : 处理缓存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcessBufferMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前的实现机制下，不会有缓存消息，因此只保留了函数的框架，
       待后续需要的时候，再进行扩充 */

    return;
}



/*****************************************************************************
 函 数 名  : TAF_APS_PostProcessMsg
 功能描述  : APS状态机后处理函数,将当前收到的消息进行缓存或者丢弃的处理
 输入参数  : ulEventType:消息类型
             pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将当前的消息进行缓存 */
    /* 当前应该不会出现缓存需要，因此代码先注释掉，这样所有状态机不处理的消息，
       都进行丢弃 */
    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_MsgPreProcess
 功能描述  : MMC消息预处理
 输入参数  : ulEventType:消息类型
              pMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:预处理完成
              VOS_FALSE:还需要进行状态机中处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_ACTION_FUNC                     pActFun;
    TAF_FSM_DESC_STRU                  *pstFsmDesc;
    VOS_UINT32                          ulRet;

    /* 消息预处理 */

    TAF_INFO_LOG1(WUEPS_PID_TAF,"TAF_APS_PreProcessMsg", (VOS_INT32)ulEventType);

    pstFsmDesc = TAF_APS_GetPreFsmDescAddr();

    /* 查找状态转移表中的相应的动作处理函数 */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, TAF_APS_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* 预处理消息,分为两类消息,一类为预处理结束就返回,另外一类为预处理
        结束后,仍然需要进行到状态机中继续处理,因此此处直接通过函数返回预处
        理结束后是否需要进行状态机处理*/
        ulRet = (*pActFun) ( ulEventType, pstMsg);
        return ulRet;
    }

    /* 消息未被处理完成需继续处理 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_ProcessMsgInFsm
 功能描述  : 消息状态机处理
 输入参数  : ulEventType :  消息类型+PID
              pMsg        :  消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:该消息是否处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstCurPdpEntityFsmCtx;
    VOS_UINT8                           i;
    TAF_APS_FSM_ID_ENUM_UINT32          enPreSubFsmId;
    TAF_APS_PDPID_LIST_STRU             stPdpIdList;
    /* 可维可测，处理前、后状态机状态 */
    TAF_APS_FSM_STATUS_INFO_STRU        stPriFsmInfo;
    TAF_APS_FSM_STATUS_INFO_STRU        stCurrFsmInfo;

    /* 清空需要送出的PDP操作列表的变量pstPdpIdList */
    PS_MEM_SET(&stPdpIdList, 0, sizeof(TAF_APS_PDPID_LIST_STRU));

    /* 获取需要操作的Pdp 列表 */
    TAF_APS_GetFsmPdpIdList(ulEventType, pstMsg, &stPdpIdList);

    ulRet = VOS_FALSE;

    for (i = 0; i < stPdpIdList.ucPdpNum; i++)
    {
        /* 根据PDP ID来设置当前的实体状态机 */
        TAF_APS_SetCurrPdpEntityFsmAddr(stPdpIdList.aucPdpId[i]);

        /* 设置当前状态机实体的PDP ID */
        TAF_APS_SetCurrFsmEntityPdpId(stPdpIdList.aucPdpId[i]);

        /* 可维可测，打印当前PDP实体信息 */
        TAF_APS_LogPdpEntityInfo(stPdpIdList.aucPdpId[i]);

        PS_MEM_SET(&stPriFsmInfo, 0xFF, sizeof(TAF_APS_FSM_STATUS_INFO_STRU));
        PS_MEM_SET(&stCurrFsmInfo, 0xFF, sizeof(TAF_APS_FSM_STATUS_INFO_STRU));

        pstCurPdpEntityFsmCtx = TAF_APS_GetCurrPdpEntityFsmAddr();

        /* 如果当前子状态机已经存在，则直接进入到子状态机处理 */
        if (TAF_APS_FSM_BUTT != pstCurPdpEntityFsmCtx->stSubFsm.enFsmId)
        {

            enPreSubFsmId = pstCurPdpEntityFsmCtx->stSubFsm.enFsmId;

            stPriFsmInfo.enFsmId = pstCurPdpEntityFsmCtx->stSubFsm.enFsmId;
            stPriFsmInfo.ulState = pstCurPdpEntityFsmCtx->stSubFsm.ulState;

            ulRet     = TAF_APS_FSM_ProcessEvent( pstCurPdpEntityFsmCtx->stSubFsm.ulState,
                                                  ulEventType,
                                                  (VOS_VOID*)pstMsg,
                                                  pstCurPdpEntityFsmCtx->stSubFsm.pstFsmDesc );
            /* 当前子状态机如果发生变化，并且不是退出子状态机，
              说明进行了子状态机切换，需要再次进入到状态机处理函数中 */
            if ( (TAF_APS_FSM_BUTT != pstCurPdpEntityFsmCtx->stSubFsm.enFsmId )
               &&( enPreSubFsmId != pstCurPdpEntityFsmCtx->stSubFsm.enFsmId ) )
            {
                ulRet     = TAF_APS_FSM_ProcessEvent( pstCurPdpEntityFsmCtx->stSubFsm.ulState,
                                                      ulEventType,
                                                      (VOS_VOID*)pstMsg,
                                                      pstCurPdpEntityFsmCtx->stSubFsm.pstFsmDesc );
            }

            stCurrFsmInfo.enFsmId = pstCurPdpEntityFsmCtx->stSubFsm.enFsmId;
            stCurrFsmInfo.ulState = pstCurPdpEntityFsmCtx->stSubFsm.ulState;

        }
        else
        {
            stPriFsmInfo.enFsmId = pstCurPdpEntityFsmCtx->stMainFsm.enFsmId;
            stPriFsmInfo.ulState = pstCurPdpEntityFsmCtx->stMainFsm.ulState;

            /* 先在主状态机进行消息处理 */
            ulRet     = TAF_APS_FSM_ProcessEvent( pstCurPdpEntityFsmCtx->stMainFsm.ulState,
                                                  ulEventType,
                                                  (VOS_VOID*)pstMsg,
                                                  pstCurPdpEntityFsmCtx->stMainFsm.pstFsmDesc );
            if (VOS_TRUE == ulRet)
            {
                /* 如果当前主状态机已经进行了处理，并且此时子状态机存在，说明主状态状态机
                   处理函数中，启动了子状态机，再次进入到子状态机进行处理 */
                if (TAF_APS_FSM_BUTT != pstCurPdpEntityFsmCtx->stSubFsm.enFsmId)
                {
                    /* 消息处理 */
                    ulRet     = TAF_APS_FSM_ProcessEvent( pstCurPdpEntityFsmCtx->stSubFsm.ulState,
                                                          ulEventType,
                                                          (VOS_VOID*)pstMsg,
                                                          pstCurPdpEntityFsmCtx->stSubFsm.pstFsmDesc );
                }

            }

            stCurrFsmInfo.enFsmId = pstCurPdpEntityFsmCtx->stSubFsm.enFsmId;
            stCurrFsmInfo.ulState = pstCurPdpEntityFsmCtx->stSubFsm.ulState;
        }

        /* 可维可测，打印处理消息前后的状态机信息 */
        TAF_APS_LogFsmMntnInfo(&stPriFsmInfo, &stCurrFsmInfo);
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_APS_BuildEventType
 功能描述  : 构造EventType
 输入参数  : ulEventType :  消息类型+PID
              pMsg        :  消息内容
 输出参数  : 无
 返 回 值  : ulEventType事件类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2015年6月6日
    作    者   : l00198894
    修改内容   : Modem PID扩展
*****************************************************************************/
VOS_UINT32 TAF_APS_BuildEventType(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader;
    REL_TIMER_MSG                      *pstRcvTimerMsg;
    VOS_UINT32                          ulEventType = 0;
    APS_SNDCP_COMMON_MSG               *pstSnCommonMsg;

    /*
       动作表里的时间消息不能靠消息头名称进行区分，依靠其结构体的ulName域进行区分
       所以此处进行分别处理
    */
    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;
    if ( VOS_PID_TIMER == pstMsgHeader->ulSenderPid )
    {
        pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstRcvTimerMsg->ulName);

    }
    else if (WUEPS_PID_SM == pstMsgHeader->ulSenderPid)
    {
        ulEventType = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstMsgHeader->ulMsgName);
    }
    else if (UEPS_PID_SN == pstMsgHeader->ulSenderPid)
    {
        /* SNDCP的格式，也需要特殊处理一下，msgname的长度不同 */
        pstSnCommonMsg = (APS_SNDCP_COMMON_MSG*)pstMsg;
        ulEventType = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstSnCommonMsg->usMsgType);
    }
    else
    {
        ulEventType = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstMsgHeader->ulMsgName);
    }

    return ulEventType;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcMsgEntry
 功能描述  : APS的消息处理函数的入口
 输入参数  : pstMsg : 待处理的消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_ProcMsgEntry(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulEventType;
    REL_TIMER_MSG                      *pstRcvTimerMsg;


    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_APS_ProcMsgEntry:null pointer");
        return;
    }

    /* 如果是超时消息，需要显式的清除定时器的运行状态 */
    if ( VOS_PID_TIMER == ((MSG_HEADER_STRU*)pstMsg)->ulSenderPid )
    {
        pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        TAF_APS_StopTimer(pstRcvTimerMsg->ulName, pstRcvTimerMsg->ulPara);
    }

    /*
       动作表里的消息处理函数依照发送者的PID和消息名来区分，两者共同
       构造EventType
    */
    ulEventType = TAF_APS_BuildEventType(pstMsg);


    /* 如果在预处理中已经处理完成则直接返回 */
    if ( VOS_TRUE == TAF_APS_PreProcessMsg(ulEventType, pstMsg))
    {
        return;
    }

    /* 进入状态机处理 */
    ulRet  = TAF_APS_ProcessMsgInFsm(ulEventType, pstMsg);

    /* 此处流程上有点问题，需要增加判定，只有子状态机有退出的时候，
       才需要处理缓存 */

    /* 该消息在状态机中已经处理完成,可尝试处理一下缓存 */
    if ( VOS_TRUE == ulRet)
    {
        TAF_APS_ProcessBufferMsg(ulEventType, pstMsg);
    }
    /* 在当前状态机中未处理完毕，判断消息是否需要打断当前的L2状态机,后处理 */
    else
    {
        TAF_APS_PostProcessMsg(ulEventType, pstMsg);
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcMsg
 功能描述  : APS的消息处理函数
 输入参数  : pstMsg : APS收到的消息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月16日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_ProcMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTERNAL_MSG_BUF_STRU      *pstNextMsg;

    /* 先处理外部消息 */
    TAF_APS_ProcMsgEntry(pstMsg);

    /* 外部消息处理完成后处理内部消息 */
    pstNextMsg = TAF_APS_GetNextInternalMsg();

    while (VOS_NULL_PTR != pstNextMsg)
    {

        /* 将该消息钩出来,以便于在PSTAS中显示 */
        DIAG_TraceReport(pstNextMsg);
        TAF_APS_ProcMsgEntry((struct MsgCB *)pstNextMsg);

        /* 寻找下一条内部消息 */
        pstNextMsg = TAF_APS_GetNextInternalMsg();
    }

    return;
}

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



