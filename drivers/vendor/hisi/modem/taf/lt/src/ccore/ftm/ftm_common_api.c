/******************************************************************************

                  版权所有 (C), 1998-2010, 华为技术有限公司

******************************************************************************
  文 件 名   : ftm_api.c
  版 本 号   : V1.0
  作    者   : 陈文峰/00149739
  生成日期   : 2010-05-12
  功能描述   : TODO: ...

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2010-05-12
    作    者 : 陈文峰/00149739
    修改内容 : 创建文件

******************************************************************************/

/******************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
******************************************************************************/
#include "ftm_errno.h"
#include "taf_drx.h"
#include "osm.h"
#include "gen_msg.h"
#include <ftm.h>
#include "ftm_ct.h"
#include "ftm_mntn.h"

/*lint --e{830,539,525}*/

/*lint -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_COMMON_API_C
/*lint -e767*/

/* 温度定时查询定时器ID */
VOS_UINT32 g_ulFtmCmTmsTimer;


/*****************************************************************************
函 数 名  : ftm_comm_starttimer
功能描述  : 启动FTM模块超时定时器
输入参数  : reqID 使用者消息ID
输出参数  : pulTimer 定时器ID
返 回 值  : 成功返回ERR_FTM_SUCCESS, 失败返回ERR_FTM_FAILURE
*****************************************************************************/
VOS_UINT32 ftm_comm_starttimer(VOS_UINT32* pulTimer, VOS_UINT32 reqId)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    /* 避免多请求时，定时器没释放，造成积累 */
    if(0 != (*pulTimer))
    {
    	/*lint -save -e740*/
		(VOS_VOID)VOS_StopRelTimer((HTIMER*)pulTimer);
		/*lint -restore*/
        *pulTimer = 0;
    }
	/*lint -save -e740*/
    ulRet = VOS_StartRelTimer((HTIMER*)pulTimer, MSP_SYS_FTM_PID, FTM_CT_OVER_TIME,
        0, reqId, (VOS_UINT8)VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
	/*lint -restore*/
    if(ulRet != ERR_FTM_SUCCESS)
    {
        ulRet = ERR_FTM_FAILURE;
    }

    return ulRet;
}

/*****************************************************************************
函 数 名  : ftm_comm_stoptimer
功能描述  : 停止FTM模块超时定时器
输入参数  : pulTier 定时器ID
输出参数  : 无
返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回ERR_FTM_FAILURE
****************************************************************************/
VOS_UINT32 ftm_comm_stoptimer(VOS_UINT32* pulTimer)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    if(*pulTimer != 0)
    {
    	/*lint -save -e740*/
        ulRet     = VOS_StopRelTimer((HTIMER*)pulTimer);
		/*lint -restore*/
        *pulTimer = 0;
    }

    if(ulRet != ERR_FTM_SUCCESS)
    {
        ulRet = ERR_FTM_FAILURE;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ftm_comm_send
 功能描述  : 从MSP_SYS_FTM_PID任务发送消息到UEPS_PID_AT任务
 输入参数  : ulMsgId 消息ID
             ulParam1 消息内容
             ulParam1  消息长度
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回ERR_FTM_FAILURE
*****************************************************************************/
VOS_UINT32 ftm_comm_send(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    VOS_UINT32 ulRet = ftm_SendDataMsg(MSP_SYS_FTM_PID, WUEPS_PID_AT, ulMsgId, ulParam1, ulParam2);

    if(ulRet != ERR_FTM_SUCCESS)
    {
        ulRet = ERR_FTM_FAILURE;
    }

    return ulRet;
}

VOS_UINT32 ftm_MsgProcInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRet = 0;

    if (ip == VOS_IP_RESTART)
    {
        drx_taf_init();
		
        /* 初始化FTM模块信息 */
        ftm_MainInfoInit();


        /* 初始化邮箱  */
		/*lint -save -e746*/
        (VOS_VOID)ftm_mailbox_init();
		/*lint -restore*/

    }

    return ulRet;
}

VOS_VOID ftm_MsgProc(MsgBlock *pMsgBlock)
{
	/*lint -save -e830*/
	VOS_UINT32 ret = ERR_FTM_SUCCESS;
	/*lint -restore*/

    OS_MSG_STRU* pMsg = NULL;
    OS_MSG_STRU stEvent = { 0 };

    if (NULL == pMsgBlock)
    {
        return;
    }

	/*vote lock */
	drx_taf_fid_vote_lock(DRX_FTM_VOTE);
    if (pMsgBlock->ulSenderPid == DOPRA_PID_TIMER)   /* 超时定时器消息 */
    {
        stEvent.ulMsgId  = ID_MSG_FTM_TIME_OUT;
        stEvent.ulParam1 =  VOS_MemAlloc(MSP_SYS_FTM_PID, (DYNAMIC_MEM_PT), sizeof(OSM_MSG_TIMER_STRU));

        if (NULL != stEvent.ulParam1)/* [false alarm]:fortify */
        {
			/*lint -save -e740*/
			((OSM_MSG_TIMER_STRU*)(stEvent.ulParam1))->ulPara = ((REL_TIMER_MSG*)pMsgBlock)->ulPara;/* [false alarm]:fortify */
			((OSM_MSG_TIMER_STRU*)(stEvent.ulParam1))->ulTimeId = (VOS_UINT32) (((REL_TIMER_MSG*)pMsgBlock)->hTm);/* [false alarm]:fortify */
			/*lint -restore*/
            stEvent.ulParam2 = sizeof(OSM_MSG_TIMER_STRU);/* [false alarm]:fortify */
            ret              = ftm_TaskMsg(&stEvent);/* [false alarm]:fortify */
        }/* [false alarm]:fortify */
    }
    else if (pMsgBlock->ulSenderPid == WUEPS_PID_AT)   /* A核发送来的消息 */
    {
        ret = FTM_MsgConvert(pMsgBlock, &stEvent);/* [false alarm]:fortify */
        if (ERR_FTM_SUCCESS == ret)/* [false alarm]:fortify */
        {
            ret  = ftm_TaskMsg(&stEvent);/* [false alarm]:fortify */
        }/* [false alarm]:fortify */
    }
    else   /* LRTT与TRTT发来的消息 */
    {
        pMsg = (OS_MSG_STRU*)(pMsgBlock->aucValue);
        ret  = ftm_TaskMsg(pMsg);/* [false alarm]:fortify */
    }/* [false alarm]:fortify */
	/* vote unlock */
	drx_taf_fid_vote_unlock(DRX_FTM_VOTE);
/*lint -save -e438*/
}
/*lint -restore*/
/*****************************************************************************
 函数名称: FTM_FidInit
 功能描述: 系统任务 ，被系统调用

 参数说明:
   VOS_INIT_PHASE_DEFINE ip [in/out] : 输入的操作类别


 返 回 值:
    成功：VOS_OK: 表示操作成功
    失败：OTHER
          操作失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 陈文峰/00149739 [2011-01-22]
*****************************************************************************/
VOS_UINT32 MSP_FtmFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal;

    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:

        ulRelVal = VOS_RegisterPIDInfo(MSP_SYS_FTM_PID, (Init_Fun_Type) ftm_MsgProcInit, (Msg_Fun_Type) ftm_MsgProc);
        if (ulRelVal != VOS_OK)
        {
            HAL_SDMLOG("In MSP_FtmFidInit Failed,  VOS_RegisterPIDInfo\n");
            return VOS_ERR;
        }

        ulRelVal = VOS_RegisterMsgTaskPrio(MSP_FTM_FID, VOS_PRIORITY_M2);

        if (ulRelVal != VOS_OK)
        {
            HAL_SDMLOG("In MSP_FtmFidInit Failed,  VOS_RegisterMsgTaskPrio\n");/* [false alarm]:fortify */
            return VOS_ERR;/* [false alarm]:fortify */
        }

        ulRelVal = VOS_RegisterSelfTask(MSP_FTM_FID, ftm_mailbox_taskproc, VOS_PRIORITY_M2, 4096);/* [false alarm]:fortify */
        if (VOS_NULL_BYTE  == ulRelVal)/* [false alarm]:fortify */
        {
            HAL_SDMLOG("In MSP_FtmFidInit Failed,  VOS_RegisterSelfTask\n");/* [false alarm]:fortify*/
            return VOS_ERR;/* [false alarm]:fortify */
        }/* [false alarm]:fortify */

        break;

    default:
        break;
    }

    return VOS_OK;
}
