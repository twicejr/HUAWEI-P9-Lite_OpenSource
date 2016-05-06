/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsEntity.c
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : 实现CDS任务/实体管理、消息处理等
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CDS.h"
#include "CdsIpfCtrl.h"
#include "CdsDebug.h"
#include "CdsMsgProc.h"
#include "CdsUlProc.h"
#include "CdsSoftFilter.h"
#include "CdsImsProc.h"
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
#include "CdsBastetProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_ENTITY_C
/*lint +e767*/

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/
extern VOS_VOID Fc_LteInit(VOS_VOID);
extern VOS_VOID QosFc_Init(VOS_VOID);
extern VOS_VOID CDS_ClearIpFragBuff(VOS_VOID);

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/
VOS_UINT32                         g_ulCdsTaskId         = 0;   /*CDS任务ID*/
VOS_UINT32                         g_ulCdsTaskReadyFlag  = 0;   /*CDS任务运行状态*/
CDS_ENTITY_STRU                    g_astCdsEntity[CDS_MAX_MODEM_NUM]; /*CDS任务实体*/

#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT32  g_ulCdsStFlg = PS_FALSE;

    /*PC ST使用,g_ulCdsStFlg在ST用例中打开*/
    #define  CDS_ST_TMR_START(pHTIMER)      \
             if (PS_TRUE == g_ulCdsStFlg)   \
             {                              \
                (pHTIMER) = (HTIMER)0xffff; \
                return PS_SUCC;             \
             }
    #define  CDS_ST_TMR_STOP(pHTIMER)       \
             if (PS_TRUE == g_ulCdsStFlg)   \
             {                              \
                (pHTIMER) = 0;              \
                return;                     \
             }
#else
    #define  CDS_ST_TMR_START(pHTIMER)
    #define  CDS_ST_TMR_STOP(pHTIMER)
#endif

/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : CDS_GetCdsEntity
 功能描述  : 获得当前Modem的CDS实体指针
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月28日
      作    者   : y00151394
      修改内容   : 新增函数。

*****************************************************************************/
CDS_ENTITY_STRU* CDS_GetCdsEntity(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (enModemId >= CDS_MAX_MODEM_NUM)
    {
        return VOS_NULL_PTR;
    }

    return &(g_astCdsEntity[enModemId]);
}


/*****************************************************************************
 函 数 名  : CDS_TmrInit
 功能描述  : CDS 定时器初始化
 输入参数  : CDS_ENTITY_STRU *pstCdsEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2012年12月13日
    作    者   : y00151394
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_TimerInit (CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_TIMER_STRU          *pstTmr;

    /*NULL模式下10周期性定时器*/
    pstTmr = &(pstCdsEntity->astTimer[CDS_TMR_ID_DL_10MS_PERIODIC_TMR]);
    pstTmr->pstTmrHdr = VOS_NULL_PTR;
    pstTmr->ulTmrId   = CDS_TMR_ID_DL_10MS_PERIODIC_TMR;
    pstTmr->ulTmrLen  = CDS_TMR_LEN;
    pstTmr->ulPara    = pstCdsEntity->usModemId;

    /*环回模式B定时器*/
    pstTmr = &(pstCdsEntity->astTimer[CDS_TMR_ID_LB_MODE_B_TMR]);
    pstTmr->pstTmrHdr = VOS_NULL_PTR;
    pstTmr->ulTmrId   = CDS_TMR_ID_LB_MODE_B_TMR;
    pstTmr->ulTmrLen  = 0;
    pstTmr->ulPara    = pstCdsEntity->usModemId;

    /*上行数据保护定时器*/
    pstTmr = &(pstCdsEntity->astTimer[CDS_TMR_ID_UL_DATA_PROCTECT]);
    pstTmr->pstTmrHdr = VOS_NULL_PTR;
    pstTmr->ulTmrId   = CDS_TMR_ID_UL_DATA_PROCTECT;
    pstTmr->ulTmrLen  = CDS_UL_DATA_PROTECT_TMR_LEN;
    pstTmr->ulPara    = pstCdsEntity->usModemId;

    return;
}


/*****************************************************************************
 函 数 名  : CDS_StartTimer
 功能描述  : 启动定时器。

 输入参数  : CDS_ENTITY_STRU  *pstCdsEntity,
             VOS_UINT32 ulTmrId
 输出参数  : 无
 返 回 值  : PS_SUCC : 启动定时器成功
             PS_FAIL : 启动定时器失败
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_StartTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId)
{
    CDS_TIMER_STRU          *pstTmr;
    VOS_INT32                lLock;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*入参判断*/
    if (ulTmrId >= CDS_TMR_ID_MODEM_BUTT)
    {
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_StartTimer : Input ulTmrId Error.",ulTmrId);
        CDS_PRINT_INFO1(CDS_StartTimer_ENUM, CDS_PRINT_TIMER_ID_ERROR, ulTmrId);
        return PS_FAIL;
    }

    /*获得定时器结构体指针*/
    pstTmr = &(pstCdsEntity->astTimer[ulTmrId]);

    /*已运行*/
    if (VOS_NULL_PTR != pstTmr->pstTmrHdr)
    {
        return PS_SUCC;
    }

    /*启动定时器*/
    lLock = VOS_SplIMP();
    if (VOS_OK != PS_START_REL_TIMER(&(pstTmr->pstTmrHdr),
                                    UEPS_PID_CDS,
                                    pstTmr->ulTmrLen,
                                    ulTmrId,
                                    pstTmr->ulPara,
                                    VOS_RELTIMER_NOLOOP))
    {
        VOS_Splx(lLock);
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StartTimer : Start Tmr Fail.",pstCdsEntity->usModemId,ulTmrId);
        CDS_PRINT_ERROR2(CDS_StartTimer_ENUM,CDS_PRINT_START_TIMER_FAIL,pstCdsEntity->usModemId,ulTmrId);
        return PS_FAIL;
    }
    VOS_Splx(lLock);

    /*CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StartTimer : Start Timer Succ.",pstCdsEntity->usModemId,ulTmrId);*/
    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : CDS_StopTimer
 功能描述  : 停止CDS定时器

 输入参数  : CDS_ENTITY_STRU  *pstCdsEntity
             VOS_UINT32 ulTmrId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_StopTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId)
{
    CDS_TIMER_STRU          *pstTmr;
    VOS_INT32                lLock;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*入参判断*/
    if (ulTmrId >= CDS_TMR_ID_MODEM_BUTT)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_StopTimer : Timer ID Error.",ulTmrId);
        CDS_PRINT_ERROR1(CDS_StopTimer_ENUM,CDS_PRINT_TIMER_ID_ERROR,ulTmrId);
        return;
    }

    /*获得定时器结构体指针*/
    pstTmr = &(pstCdsEntity->astTimer[ulTmrId]);

    /*已停止*/
    if (VOS_NULL_PTR == pstTmr->pstTmrHdr)
    {
        return ;
    }

    /*停止定时器*/
    lLock = VOS_SplIMP();
    if (VOS_OK != PS_STOP_REL_TIMER(&(pstTmr->pstTmrHdr)))
    {
        VOS_Splx(lLock);
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StopTimer : Stop Tmr Fail.",pstCdsEntity->usModemId,ulTmrId);
        CDS_PRINT_ERROR2(CDS_StartTimer_ENUM,CDS_PRINT_STOP_TIMER_FAIL,pstCdsEntity->usModemId,ulTmrId);
        return;
    }
    VOS_Splx(lLock);

    /*CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_StopTimer : Stop Tmr Succ.",pstCdsEntity->usModemId,ulTmrId);*/
    return ;
}


/*****************************************************************************
 函 数 名  : CDS_ProcLoopBackQue
 功能描述  : 处理环回数据
 输入参数  : CDS_ENTITY_STRU  *pstCdsEntity
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_ProcLoopBackQue(CDS_ENTITY_STRU  *pstCdsEntity)
{
    VOS_UINT32          ulCnt;
    TTF_MEM_ST         *pstIpPkt;
    VOS_UINT16          usResult;

    /*遍历环回队列*/
    for (ulCnt = 0; ulCnt < CDS_LB_QUE_SIZE; ulCnt ++)
    {
        /*出队*/
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstLBModeBQue,(VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        /*调用软过滤接口*/
        if (PS_SUCC != CDS_IpSoftFilter(pstIpPkt, &usResult,pstCdsEntity))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_LB_UL_SOFT_FILTER_FAIL_NUM(1);
            continue;
        }

        /*将过滤结果存到TTF中*/
        CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt,usResult);

        CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt);
        CDS_DBG_UL_LTE_IP_PKT_HOOK(pstIpPkt);

        /*按模式分发*/
        CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);

        /*增加计数*/
        CDS_DBG_LB_UL_SEND_PKT_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ClearLoopBackQue
 功能描述  : 清空环回下行缓存
 输入参数  : const CDS_ENTITY_STRU *pstCdsEntity
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年09月17日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ClearLoopBackQue(const CDS_ENTITY_STRU *pstCdsEntity)
{
    TTF_MEM_ST      *pstIpPkt;
    VOS_UINT32       ulCnt;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    for (ulCnt = 0; ulCnt < CDS_LB_QUE_SIZE; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstLBModeBQue,(VOS_VOID **)&pstIpPkt))
        {
            break;
        }

        TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
        CDS_DBG_LB_UL_CLEAR_PKT_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_RxLoopBackPkt
 功能描述  : CDS接收环回数据。由调用者保证入参正确性。
 输入参数  : CDS_RABM_TRANS_DATA_STRU *pstDlData, CDS_ENTITY_STRU *pstCdsEntity
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_RxLoopBackPkt(CDS_LB_DL_SDU_STRU *pstDlData, CDS_ENTITY_STRU *pstCdsEntity)
{
    TTF_MEM_ST            *pstDstTtf;
    VOS_INT32              lLock;

    /*非环回模式B直接释放*/
    if (CDS_LB_MODE_B != pstCdsEntity->ulLoopBackMode)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        CDS_DBG_LB_DL_RX_SDU_IN_NO_MODE_B(1);
        return;
    }

    /*申请目的内存*/
    pstDstTtf = CDS_AllocTtfMem(pstDlData->ulSduLen);
    if (VOS_NULL_PTR == pstDstTtf)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        CDS_DBG_LB_DL_ALLOC_MEM_FAIL(1);
        return;
    }

    /*进行内存拷贝*/
    if (PS_SUCC != TTF_MemGetHeadData(  UEPS_PID_CDS,
                                        pstDlData->pstSdu,
                                        pstDstTtf->pData,
                                        (VOS_UINT16)(pstDlData->ulSduLen)))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);
        TTF_MemFree(UEPS_PID_CDS,pstDstTtf);
        return;
    }

    /*释放源内存*/
    TTF_MemFree(UEPS_PID_CDS,pstDlData->pstSdu);

    /*保持必要信息，打桩设置:ModemId=0,RabId=5*/
    CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstDstTtf,
                                             pstCdsEntity->ucLBDefBearerId,
                                             MODEM_ID_0,
                                             pstCdsEntity->ucLBDefBearerId);

    /*入队*/
    lLock = VOS_SplIMP();
    if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstLBModeBQue,pstDstTtf))
    {
        VOS_Splx(lLock);
        TTF_MemFree(UEPS_PID_CDS,pstDstTtf);
        CDS_DBG_LB_DL_ENQUE_FAIL_NUM(1);
        return;
    }
    VOS_Splx(lLock);

    CDS_DBG_DL_REC_IP_PKT_INFO(pstDstTtf);
    CDS_DBG_DL_LTE_IP_PKT_HOOK(pstDstTtf);

    CDS_DBG_LB_DL_ENQUE_SUCC_NUM(1);

    /*启动环回定时器*/
    if (PS_SUCC != CDS_StartTimer(pstCdsEntity, CDS_TMR_ID_LB_MODE_B_TMR))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RxLoopBackPkt : Start LB Mode B Timer Fail.");
        CDS_PRINT_ERROR(CDS_RxLoopBackPkt_ENUM,CDS_PRINT_START_TIMER_FAIL);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_LoopBackModeBTimeoutProc
 功能描述  : 环回模式B定时器超时处理
 输入参数  : EL_TIMER_MSG  *pstTmrMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年09月17日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_LoopBackModeBTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg)
{
    CDS_ENTITY_STRU             *pstCdsEntity;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_LoopBackModeBTimeoutProc");
    CDS_PRINT_INFO(CDS_LoopBackModeBTimeoutProc_ENUM, LL2_FUNCTION_ENTER);

    /*入参判断*/
    CDS_ASSERT(VOS_NULL_PTR != pstTmrMsg);

    /*根据参数获取CDS实体*/
    pstCdsEntity = CDS_GetCdsEntity((MODEM_ID_ENUM_UINT16)(pstTmrMsg->ulPara));
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*停止定时器*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_LB_MODE_B_TMR);

    /*没有处于环回状态，直接返回*/
    if (PS_TRUE != pstCdsEntity->ulTestModeFlg)
    {
        CDS_ClearLoopBackQue(pstCdsEntity);
        return;
    }

    /*非模式B，则直接返回；GU环回模式4映射到CDS_LB_MODE_B*/
    if (CDS_LB_MODE_B != pstCdsEntity->ulLoopBackMode)
    {
        CDS_ClearLoopBackQue(pstCdsEntity);
        return;
    }

    /*发送上行数据*/
    CDS_ProcLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_LoopBackModeBTimeoutProc");
    CDS_PRINT_INFO(CDS_LoopBackModeBTimeoutProc_ENUM, LL2_FUNCTION_EXIT);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_Dl10msPeridicTmrTimeoutProc
 功能描述  : 下行10ms周期性定时器超时处理
 输入参数  : REL_TIMER_MSG  *pstTmrMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年09月17日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_Dl10msPeridicTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg)
{
    CDS_ENTITY_STRU             *pstCdsEntity;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_Dl10msPeridicTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, LL2_FUNCTION_ENTER);

    /*入参判断*/
    CDS_ASSERT(VOS_NULL_PTR != pstTmrMsg);

    /*根据参数获取CDS实体*/
    pstCdsEntity = CDS_GetCdsEntity((MODEM_ID_ENUM_UINT16)(pstTmrMsg->ulPara));
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    /*下行SDU队列空*/
    if (PS_TRUE == LUP_IsQueEmpty(CDS_GET_IPF_DL_SDU_QUE()))
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_Dl10msPeridicTmrTimeoutProc : DL Sdu Empty Stop Timer.");
        CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, CDS_PRINT_DL_SDU_QUE_EMPTY);
        return;
    }

    if (PS_SUCC != CDS_StartTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR))
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_Dl10msPeridicTmrTimeoutProc : ReStart Timer Fail.");
        CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, CDS_PRINT_RESTART_TIMER_FAIL);
        return;
    }

    /*处理下行数据或发送下行处理事件*/
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_10MS_TMR_TRIG_EVENT(1);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_Dl10msPeridicTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_Dl10msPeridicTmrTimeoutProc_ENUM, LL2_FUNCTION_EXIT);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_UlDataProtectTmrTimeoutProc
 功能描述  : 上行缓存保护定时器超时处理
 输入参数  : REL_TIMER_MSG  *pstTmrMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年09月17日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_UlDataProtectTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg)
{

    CDS_ENTITY_STRU             *pstCdsEntity;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_UlDataProtectTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_UlDataProtectTmrTimeoutProc_ENUM, LL2_FUNCTION_ENTER);

    /*入参判断*/
    CDS_ASSERT(VOS_NULL_PTR != pstTmrMsg);

    /*根据参数获取CDS实体*/
    pstCdsEntity = CDS_GetCdsEntity((MODEM_ID_ENUM_UINT16)(pstTmrMsg->ulPara));
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_UlDataProtectTmrTimeoutProc : Get CDS Entity Fail.",pstTmrMsg->ulPara);
        CDS_PRINT_INFO1(CDS_UlDataProtectTmrTimeoutProc_ENUM, CDS_PRINT_GET_ENTITY_FAIL_MODEM_ID, pstTmrMsg->ulPara);
        return;
    }

    /*停止定时器*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_UL_DATA_PROCTECT);

    /*清除Service Request标志位*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*发送上行缓存数据*/
    CDS_ClearUlBuffData(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_UlDataProtectTmrTimeoutProc");
    CDS_PRINT_INFO(CDS_UlDataProtectTmrTimeoutProc_ENUM, LL2_FUNCTION_EXIT);

    return;
}


/*****************************************************************************
 函 数 名  : CDS_GetBearerDataFlowInfo
 功能描述  : CDS实体中RABID对应的流量统计实体.
 输入参数  : VOS_UINT8 ucRabId
             const CDS_ENTITY_STRU *pstCdsEntity

 输出参数  : CDS_BEARER_DATA_FLOW_STRU *
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
CDS_BEARER_DATA_FLOW_STRU* CDS_GetBearerDataFlowPtr(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{

    /*入参判断*/
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstCdsEntity,VOS_NULL_PTR);

    if ((CDS_NAS_MIN_BEARER_ID > ucRabId) || (CDS_NAS_MAX_BEARER_ID < ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : Input RabId Fail.RabID=",ucRabId);
        CDS_PRINT_ERROR1(CDS_GetBearerDataFlowPtr_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        return VOS_NULL_PTR;
    }

    return (CDS_BEARER_DATA_FLOW_STRU *)&(pstCdsEntity->stFlowStats.astBearerDS[ucRabId - CDS_NAS_MIN_BEARER_ID]);
}


/*****************************************************************************
 函 数 名  : CDS_GetBearerDataFlowInfo
 功能描述  : CDS提供给APS查询对应承载的流量统计信息
 输入参数  : VOS_UINT8   ucRabId
             CDS_BEARER_DATA_FLOW_STRU *pstDataFlowInfo

 输出参数  : CDS_BEARER_DATA_FLOW_STRU *pstDataFlowInfo
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

    2.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : DSDA修改

*****************************************************************************/
VOS_VOID CDS_GetBearerDataFlowInfo(VOS_UINT8 ucRabId,CDS_BEARER_DATA_FLOW_STRU *pstDataFlowInfo, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_BEARER_DATA_FLOW_STRU    *pstLocalValue;
    CDS_ENTITY_STRU              *pstCdsEntity;

    if (VOS_NULL_PTR == pstDataFlowInfo)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_GetBearerDataFlowInfo_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : Get CDS Entity Error. ModemId=",enModemId);
        CDS_PRINT_ERROR1(CDS_GetBearerDataFlowInfo_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        PS_MEM_SET(pstDataFlowInfo,0,sizeof(CDS_BEARER_DATA_FLOW_STRU));
        return;
    }

    pstLocalValue = CDS_GetBearerDataFlowPtr(ucRabId,pstCdsEntity);
    if (VOS_NULL_PTR == pstLocalValue)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GetBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucRabId);
        CDS_PRINT_ERROR1(CDS_GetBearerDataFlowInfo_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        PS_MEM_SET(pstDataFlowInfo,0,sizeof(CDS_BEARER_DATA_FLOW_STRU));
        return;
    }

    pstDataFlowInfo->ulTotalReceiveFluxHigh = pstLocalValue->ulTotalReceiveFluxHigh;
    pstDataFlowInfo->ulTotalReceiveFluxLow  = pstLocalValue->ulTotalReceiveFluxLow;
    pstDataFlowInfo->ulTotalSendFluxHigh    = pstLocalValue->ulTotalSendFluxHigh;
    pstDataFlowInfo->ulTotalSendFluxLow     = pstLocalValue->ulTotalSendFluxLow;

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ClearBearerDataFlowInfo
 功能描述  : CDS提供给APS清空对应承载的流量统计信息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

    2.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : DSDA修改

*****************************************************************************/
VOS_VOID CDS_ClearBearerDataFlowInfo(VOS_UINT8 ucBearerId, MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_BEARER_DATA_FLOW_STRU    *pstLocalValue;
    int                           intLockLevel;
    CDS_ENTITY_STRU              *pstCdsEntity;

    /*获得CDS实体指针*/
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : Get CDS Entity Error. ModemId=",enModemId);
        CDS_PRINT_ERROR1(CDS_ClearBearerDataFlowInfo_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        return;
    }

    /*获得承载流量统计指针*/
    pstLocalValue = CDS_GetBearerDataFlowPtr(ucBearerId,pstCdsEntity);
    if (VOS_NULL_PTR == pstLocalValue)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucBearerId);
        CDS_PRINT_ERROR1(CDS_ClearBearerDataFlowInfo_ENUM,CDS_PRINT_GET_BEARER_DATA_FLOW_PTR_FAIL,ucBearerId);
        return;
    }

    intLockLevel = VOS_SplIMP();
    pstLocalValue->ulTotalReceiveFluxHigh = 0;
    pstLocalValue->ulTotalReceiveFluxLow  = 0;
    pstLocalValue->ulTotalSendFluxHigh    = 0;
    pstLocalValue->ulTotalSendFluxLow     = 0;
    VOS_Splx(intLockLevel);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_DLDataFlowStats
 功能描述  : CDS下行接收到的流量
 输入参数  : VOS_UINT8 ucBearerId,
             VOS_UINT32 ulPktLen,
             CDS_ENTITY_STRU *pstCdsEntity

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

    2.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : DSDA修改

*****************************************************************************/
VOS_VOID CDS_DLDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_BEARER_DATA_FLOW_STRU   *pstBearerDFInfo;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*获得承载流量统计指针*/
    pstBearerDFInfo = CDS_GetBearerDataFlowPtr(ucBearerId,pstCdsEntity);
    if (VOS_NULL_PTR == pstBearerDFInfo)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucBearerId);
        CDS_PRINT_ERROR1(CDS_DLDataFlowStats_ENUM,CDS_PRINT_GET_BEARER_DATA_FLOW_PTR_FAIL,ucBearerId);
        return;
    }

    /*增加下行流量统计*/
    pstBearerDFInfo->ulTotalReceiveFluxLow += ulPktLen;

    /*低32bit翻转*/
    if (pstBearerDFInfo->ulTotalReceiveFluxLow < ulPktLen)
    {
        pstBearerDFInfo->ulTotalReceiveFluxHigh ++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ULDataFlowStats
 功能描述  : CDS上行流量统计
 输入参数  : VOS_UINT8 ucBearerId,
             VOS_UINT32 ulPktLen,
             CDS_ENTITY_STRU *pstCdsEntity

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

    2.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : DSDA修改

*****************************************************************************/
VOS_VOID CDS_ULDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_BEARER_DATA_FLOW_STRU   *pstBearerDFInfo;

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    /*获得承载流量统计指针*/
    pstBearerDFInfo = CDS_GetBearerDataFlowPtr(ucBearerId,pstCdsEntity);
    if (VOS_NULL_PTR == pstBearerDFInfo)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ClearBearerDataFlowInfo : CDS_GetBearerDataFlowPtr Fail.RabID=",ucBearerId);
         CDS_PRINT_ERROR1(CDS_ULDataFlowStats_ENUM,CDS_PRINT_GET_BEARER_DATA_FLOW_PTR_FAIL,ucBearerId);
        return;
    }

    /*增加上行流量统计*/
    pstBearerDFInfo->ulTotalSendFluxLow += ulPktLen;

    /*低32bit翻转*/
    if (pstBearerDFInfo->ulTotalSendFluxLow < ulPktLen)
    {
        pstBearerDFInfo->ulTotalSendFluxHigh ++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_DLThrDataFlowStats
 功能描述  : CDS下行统计直通通道流量,供LPDCP调用
 输入参数  : VOS_UINT32 ulPktLen
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年09月15日
      作    者   : l00304941
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_LPDCP_DLThrDataFlowStats(VOS_UINT8 ucEpsbID,VOS_UINT32 ulPktLen)
{
    CDS_ENTITY_STRU       *pstCdsEntity;

    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    CDS_DLDataFlowStats(ucEpsbID, ulPktLen, pstCdsEntity);

    return;
}


/*****************************************************************************
 函 数 名  : CDS_SendEventToCds
 功能描述  : 调用该接口向CDS触发事件处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_SendEventToCds(VOS_UINT32 ulEvent)
{
    if (1 == g_ulCdsTaskReadyFlag)
    {
        (VOS_VOID)VOS_EventWrite(g_ulCdsTaskId, ulEvent);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_LPdcpWakeupCds
 功能描述  : LPdcp唤醒CDS处理下行数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年4月22日
      作    者   : h00218138
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_LPdcpWakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_SDU_TRIGGER_EVENT_NUM(1);
    return;
}


/*****************************************************************************
 函 数 名  : CDS_LSubFrmIntWakeupCds
 功能描述  : L模上行1ms子帧中断触发事件，唤醒CDS处理下行数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_LSubFrmIntWakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_LTE_1MS_INT_TRIG_EVENT(1);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_UmtsIntWakeupCds
 功能描述  : UMTS模DSP上行中断触发事件，唤醒CDS处理下行数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年02月02日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_UmtsIntWakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_UMTS_INT_TRIG_EVENT(1);
    return;
}

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
/*****************************************************************************
 函 数 名  : CDS_CDMA_WakeupCds
 功能描述  : CDMA上行中断触发事件，唤醒CDS处理下行数据
 输入参数  :无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年10月25日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_CDMA_WakeupCds(VOS_VOID)
{
    CDS_SendEventToCds(CDS_EVENT_DL_DATA_PROC);
    CDS_DBG_DL_CDMA_INT_TRIG_EVENT(1);
    return;
}
#endif

/*****************************************************************************
 函 数 名  : CDS_EventProc
 功能描述  : CDS事件处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_EventProc(VOS_UINT32 ulEvent)
{
    /*处理上行IPF唤醒*/
    if (ulEvent & CDS_EVENT_UL_IPF_INT)
    {
        CDS_UlProcIpfResult();
        CDS_DBG_UL_PROC_IPF_INT_NUM(1);
    }
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
    /*处理BASTET发出的上行IP包*/
    if (ulEvent & CDS_EVENT_UL_BASTET_PROC)
    {
        if(PS_TRUE == CDS_GetBastetSupportFlag())
        {
            CDS_UlProcBastetData();
            CDS_DBG_BST_UL_PROC_BST_EVENT_NUM(1);
        }
    }

#endif
    /*处理下行缓存*/
    if (ulEvent & CDS_EVENT_DL_DATA_PROC)
    {
        CDS_ConfigDlIPF();
        CDS_DBG_DL_PROC_EVENT_NUM(1);
    }

    /*IMS Proc*/
    if (ulEvent & CDS_EVENT_UL_IMS_PROC)
    {
        CDS_UlProcImsData(MODEM_ID_0);
        CDS_DBG_IMS_UL_PROC_IMS_EVENT_NUM(1);
    }

    /*ADQ空*/
    if (ulEvent & CDS_EVENT_UL_ADQ_EMPTY)
    {
        CDS_AllocMemForAdq();
        CDS_DBG_UL_PROC_ADQ_EMPTY_INT_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_EntityInit
 功能描述  : CDS 实体初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2011年12月13日
    作    者   : y00151394
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_EntityInit (VOS_VOID)
{
    VOS_UINT32               ulCnt;
    CDS_ENTITY_STRU         *pstCdsEntity;

    for (ulCnt = 0; ulCnt < CDS_MAX_MODEM_NUM; ulCnt ++)
    {
        pstCdsEntity = &(g_astCdsEntity[ulCnt]);
        /*设置ModemId*/
        pstCdsEntity->usModemId = (VOS_UINT16)ulCnt;

        /*设置环回标志位PS_FALSE,状态为Deactive态*/
        pstCdsEntity->ulTestModeFlg     = PS_FALSE;
        pstCdsEntity->ulLoopBackMode    = CDS_LB_MODE_BUTT;
        pstCdsEntity->ulLoopBackState   = CDS_LB_STATE_DEACTIVE;

        /*设置Service Request状态*/
        pstCdsEntity->ulServiceReqFlg   = PS_FALSE;

        /*重置GU SR标志*/
        CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

        /*接入模式设置为NULL*/
        pstCdsEntity->enRanMode = MMC_CDS_MODE_NULL;

        /*创建上行缓存队列*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstUlDataQue),CDS_UL_IDLE_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create UL Idle Que Fail.\n");
            return;
        }

        /*创建环回缓存队列*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstLBModeBQue),CDS_LB_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create Loop Back Que Fail.\n");
            return;
        }

        /*创建IMS队列*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstIMSDataQue),CDS_IMS_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create UL Idle Que Fail.\n");
            return;
        }

#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
        /*创建BASTET队列*/
        if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(pstCdsEntity->pstBastetUlQue),CDS_BASTET_QUE_SIZE))
        {
            PS_PRINTF("CDS_EntityInit : Create Bastet Que Fail.\n");
            return;
        }
#endif
        /*定时器初始化*/
        CDS_TimerInit(pstCdsEntity);
        /*上行IMS承载配置信息和上行软过滤器*/
        pstCdsEntity->ulImsBearerNum = 0;
        PS_MEM_SET(pstCdsEntity->astImsBearerInfo,0,sizeof(IMSA_CDS_IMS_BEARER_STRU) * IMSA_CDS_MAX_IMS_BEARER_NUM);
        pstCdsEntity->stImsPortInfo.usMaxImsPort = 0;
        pstCdsEntity->stImsPortInfo.usMinImsPort = 0;

        pstCdsEntity->ulUlSoftFilterNum = 0;
        PS_MEM_SET(pstCdsEntity->astUlSoftFilter,0, sizeof(CDS_SOFTFILTER_INFO_STRU) * CDS_MAX_SOFT_FILTER_NUM);

        /*特殊承载号初始化，全部初始化为5*/
        pstCdsEntity->ucMbmsBearerId        = CDS_NAS_MIN_BEARER_ID;
        pstCdsEntity->ucDbgBearerId         = CDS_NAS_MIN_BEARER_ID;
        pstCdsEntity->ucLBDefBearerId       = CDS_NAS_MIN_BEARER_ID;

        /*测试需求，上下行丢包开关*/
        pstCdsEntity->ulULPktDiscardFlg = PS_FALSE;
        pstCdsEntity->ulDLPktDiscardFlg = PS_FALSE;

        CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);

    }

    return ;
}

/*****************************************************************************
 函 数 名  : CDS_PidInit
 功能描述  : CDS PID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2011年12月13日
    作    者   : y00151394
    修改内容   : 新生成函数

*****************************************************************************/
STATIC VOS_UINT32 CDS_PidInit (enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:
        /* 1. 各全局变量使用的全局内存申请处理 */
            CDS_ClearIpFragBuff();

        /* 2. 全局变量初始 由于初始化涉及到TCM，所以移到HpaMsgProc.c的DSP初始化完成在调用该函数*/
            CDS_EntityInit();

            if (PS_SUCC != CDS_IpfInit())
            {
                PS_PRINTF("CDS_PidInit : Init IPF Fail\r\n");
                return PS_FAIL;
            }

            /* 流控初始化 */
            Fc_LteInit();
            QosFc_Init();

        /* 3. 定时器初始化函数 */

        /* 4. 定时器登记 */

        /* 5. 状态机登记, */

        /* 6. 全局开关变量初始化配置 */

        /* 7. 各子模块初始化函数调用 */

        /* 8. OTHERS初始化过程执行 */
        #if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
            CDS_BstInit();
        #endif
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return PS_SUCC;
}


/*lint -e715*/
#if (VOS_OS_VER == VOS_WIN32)

/*****************************************************************************
 函 数 名  : CDS_FidTask
 功能描述  : CDS FID任务处理函数用于WIN32
 输入参数  : ulQueueID - Task Queue ID
             FID_value - FID
             Para1 - 参数1, 未使用
             Para2 - 参数2, 未使用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_FidTask(VOS_UINT32 ulQueueID, VOS_UINT32 FID_value,
                                     VOS_UINT32 Para1, VOS_UINT32 Para2)
{
    MsgBlock       *pMsg              = VOS_NULL_PTR;
    VOS_UINT32      ulEvent           = 0;
    VOS_UINT32      ulTaskID          = 0;
    VOS_UINT32      ulEventMask       = 0;
    VOS_UINT32      ulExpectEvent     = 0;

    ulTaskID = VOS_GetCurrentTaskID();

    if (PS_NULL_UINT32 == ulTaskID)
    {
        PS_PRINTF("CDS ERROR, reg Msg Func \r\n");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        PS_PRINTF("CDS ERROR, Create Event Fail \r\n");
        return;
    }

    g_ulCdsTaskId           = ulTaskID;
    g_ulCdsTaskReadyFlag    = 1;

    ulExpectEvent           = CDS_EVENT_UL_IPF_INT | CDS_EVENT_DL_DATA_PROC | CDS_EVENT_UL_ADQ_EMPTY
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
                              | CDS_EVENT_UL_IMS_PROC | CDS_EVENT_UL_BASTET_PROC | VOS_MSG_SYNC_EVENT;
#else
                              | CDS_EVENT_UL_IMS_PROC | VOS_MSG_SYNC_EVENT;
#endif
    ulEventMask             = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while(1)
    /*lint +e716*/
    {
        if (VOS_OK != VOS_EventRead(ulExpectEvent,ulEventMask,0,&ulEvent))
        {
            PS_PRINTF("CDS Read Event Error .\r\n");
            continue;
        }

        /*事件处理*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            CDS_EventProc(ulEvent);
            continue;
        }

        /*消息处理*/
        pMsg = (MsgBlock *)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            switch(TTF_GET_MSG_RECV_PID(pMsg))
            {
            case UEPS_PID_CDS:
                CDS_RecvMsgProc(pMsg);
                break;
            default:
                PS_PRINTF("CDS Recv Unkown Message %d\r\n", TTF_GET_MSG_NAME(pMsg));
                break;
            }

            VOS_SysFreeMsg(pMsg);
        }
    }

}


#else
/*****************************************************************************
 函 数 名  : CDS_FidTask
 功能描述  : CDS FID任务处理函数用于VXWORK
 输入参数  : ulQueueID - Task Queue ID
             FID_value - FID
             Para1 - 参数1, 未使用
             Para2 - 参数2, 未使用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_FidTask(VOS_UINT32 ulQueueID, VOS_UINT32 FID_value,
                                     VOS_UINT32 Para1, VOS_UINT32 Para2)
{
    MsgBlock       *pMsg              = VOS_NULL_PTR;
    VOS_UINT32      ulEvent           = 0;
    VOS_UINT32      ulTaskID          = 0;
    VOS_UINT32      ulEventMask       = 0;
    VOS_UINT32      ulExpectEvent     = 0;

    ulTaskID = VOS_GetCurrentTaskID();

    if (PS_NULL_UINT32 == ulTaskID)
    {
        PS_PRINTF("CDS ERROR, reg Msg Func \r\n");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        PS_PRINTF("CDS ERROR, Create Event Fail \r\n");
        return;
    }

    g_ulCdsTaskId           = ulTaskID;
    g_ulCdsTaskReadyFlag    = 1;

    ulExpectEvent           = CDS_EVENT_UL_IPF_INT | CDS_EVENT_DL_DATA_PROC | CDS_EVENT_UL_ADQ_EMPTY
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
                              | CDS_EVENT_UL_BASTET_PROC
#endif
                              | CDS_EVENT_UL_IMS_PROC |VOS_MSG_SYNC_EVENT;

    ulEventMask             = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    for(;;)
    /*lint +e716*/
    {
        if (VOS_OK != VOS_EventRead(ulExpectEvent,ulEventMask,0,&ulEvent))
        {
            PS_PRINTF("CDS Read Event Error .\r\n");
            continue;
        }

        /*事件处理*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            CDS_EventProc(ulEvent);
            continue;
        }

        /*消息处理*/
        pMsg = (MsgBlock *)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            switch(TTF_GET_MSG_RECV_PID(pMsg))
            {
            case UEPS_PID_CDS:
                CDS_RecvMsgProc(pMsg);
                break;
            default:
                PS_PRINTF("CDS Recv Unkown Message %d\r\n", TTF_GET_MSG_NAME(pMsg));
                break;
            }

            PS_FREE_MSG(UEPS_PID_CDS,pMsg);
        }
    }

}

#endif
/*lint +e715*/

/*****************************************************************************
 函 数 名  : CDS_FidInit
 功能描述  : CDS任务初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2011年12月13日
    作    者   : y00151394
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32   ulResult = PS_FAIL;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:
            /* MAC UL PID初始化*/
            ulResult = VOS_RegisterPIDInfo(UEPS_PID_CDS,
                                CDS_PidInit,
                                CDS_RecvMsgProc);
            if (PS_SUCC != ulResult)
            {
                return (VOS_UINT32)PS_FAIL;
            }

            ulResult = VOS_RegisterMsgTaskEntry(UEPS_FID_CDS, (VOS_VOIDFUNCPTR)CDS_FidTask);

            if (PS_SUCC != ulResult)
            {
                PS_PRINTF("LUEPS_FID_CDS Reg msg routine FAIL!,ulRslt\n", ulResult);
                return (VOS_UINT32)PS_FAIL;
            }

            /*同LRLCMAC_DL任务优先级相同*/
            ulResult = VOS_RegisterMsgTaskPrio(UEPS_FID_CDS, VOS_PRIORITY_P3);

            if( PS_SUCC != ulResult )
            {
                PS_PRINTF("Error: UEPS_FID_CDS VOS_RegisterMsgTaskPrio failed!");
                return (VOS_UINT32)PS_FAIL;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

