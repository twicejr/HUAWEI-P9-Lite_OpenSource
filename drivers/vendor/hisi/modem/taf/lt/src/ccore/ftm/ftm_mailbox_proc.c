/******************************************************************************

                  版权所有 (C), 1998-2012, 华为技术有限公司

*******************************************************************************
  文 件 名   : ftm_mailbox_proc.c
  版 本 号   : V1.0
  作    者   : l00169177
  生成日期   : 2012-12-24
  功能描述   : FTM模块邮箱适配

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2012-12-24
    作    者 : l00169177
    修改内容 : 创建文件

******************************************************************************/
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include <ftm_ct.h>
/*lint -save -e537*/
#include <ftm_errno.h>
/*lint -restore*/
#include <taf_drx.h>
#include "ftm_mntn.h"
/*lint -save -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_MAILBOX_PROC_C
/*lint -restore*/
/* 邮箱数据可读通知信号量，邮箱回调设置 */
VOS_SEM g_mailbox_readsem = 0;

/*lint --e{830,539,525}*/

/*****************************************************************************
 函 数 名  : ftm_mailbox_msgproc
 功能描述  : 邮箱数据读取
 输入参数  : enMbxType 邮箱数据类型
 输出参数  : 无
 返 回 值  : 0无数据，大于0为邮箱数据长度
*****************************************************************************/
VOS_UINT32 ftm_mailbox_msgproc(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    VOS_UINT32 ulRet      = 0;
    VOS_UINT32 ulMsgSize  = 0;
    VOS_VOID* pMailBoxMsg = NULL;
    MsgBlock* pMsgBlock   = NULL;
    VOS_UINT32 ret = ERR_FTM_UNKNOWN;

    /* 读取消息长度 */
    ulMsgSize = BSP_MailBox_ComMsgSize(enMbxType);
    if(ulMsgSize == 0 )
    {
        return ulMsgSize;
    }

    pMailBoxMsg = VOS_MemAlloc(MSP_SYS_FTM_PID, ((DYNAMIC_MEM_PT)), ulMsgSize);
    if(NULL == pMailBoxMsg)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] VOS_MemAlloc failed.\n", __FUNCTION__, __LINE__, VOS_GetSlice());
        return 0;
    }

    /* 读取邮箱数据 */
    ulRet = BSP_MailBox_ComMsgRead(enMbxType, pMailBoxMsg, ulMsgSize, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        (VOS_VOID)VOS_MemFree(MSP_SYS_FTM_PID, pMailBoxMsg);
        return 0;
    }

    /* 发送消息到MSP_SYS_FTM_PID任务 */
    pMsgBlock = (MsgBlock*)VOS_AllocMsg(MSP_SYS_FTM_PID, sizeof(OS_MSG_STRU));
    if (!pMsgBlock) {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]VOS_MemAlloc failed\n",__FUNCTION__,__LINE__,VOS_GetSlice());
        return 0;
    }

    OS_MSG_STRU* pMsg = (OS_MSG_STRU*)pMsgBlock->aucValue;

    pMsgBlock->ulReceiverPid = MSP_SYS_FTM_PID;
    pMsgBlock->ulSenderPid   = MSP_SYS_FTM_PID;
    pMsg->ulMsgId  = ID_MSG_L1A_CT_IND;
    pMsg->ulParam1 = pMailBoxMsg;
    pMsg->ulParam2 = ulMsgSize;

    ftm_mntn_datahook(MSP_LDSP_PID, MSP_SYS_FTM_PID, ulMsgSize, (VOS_UINT8 *)pMailBoxMsg);

    ret = VOS_SendMsg(MSP_SYS_FTM_PID, pMsgBlock);
    if (ret != VOS_OK){
        (VOS_VOID)ftm_mntn_printf("[%s line%d,slice %d]send msg to MSP_SYS_FTM_PID FAILED \n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return 0;
    }

    return ulMsgSize;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_taskproc
 功能描述  : 读邮箱数据自处理任务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID ftm_mailbox_taskproc(VOS_UINT32 ulPara0,
                              VOS_UINT32 ulPara1,
                              VOS_UINT32 ulPara2,
                              VOS_UINT32 ulPara3)
{
	/*lint -save -e716*/
	while(1)
	/*lint -restore*/
    {
        if(VOS_ERR == VOS_SmP(g_mailbox_readsem, 0))
        {
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] VOS_Smp failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        }

		/*vote for lock*/
		drx_taf_fid_vote_lock(DRX_FTM_MAILBOX_VOTE);
       /* LTE CT 原语 */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_LTE_CT) > 0)
        {
            continue;
        }

      /* LTE BT 原语 */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_LTE_BT) > 0)
        {
            continue;
        }

        /* TDS CT 原语 */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_TDS_CT) > 0)
        {
            continue;
        }

        /* TDS BT 原语 */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_TDS_BT) > 0)
        {
            continue;
        }
		/*vote for lock*/
		drx_taf_fid_vote_unlock(DRX_FTM_MAILBOX_VOTE);
    }

}

/*****************************************************************************
 函 数 名  : ftm_mailbox_ltect_cb
 功能描述  : LTE CT类型数据到底回调
 输入参数  : enIntType 邮箱中断类型
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID ftm_mailbox_ltect_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_ltebt_cb
 功能描述  : LTE BT类型数据到底回调
 输入参数  : enIntType 邮箱中断类型
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID ftm_mailbox_ltebt_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_tdsct_cb
 功能描述  : TDS CT类型数据到底回调
 输入参数  : enIntType 邮箱中断类型
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID ftm_mailbox_tdsct_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_tdsbt_cb
 功能描述  : TDS BT类型数据到底回调
 输入参数  : enIntType 邮箱中断类型
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID ftm_mailbox_tdsbt_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_ltect_write
 功能描述  : 写LTE CT类型数据到邮箱
 输入参数  : param 原语内容
             ulLen 原语长度
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_UINT32 ftm_mailbox_ltect_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;
    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_CT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send lte ct to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_FTM_FAILURE;
    }

    (VOS_VOID)ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_ltebt_write
 功能描述  : 写LTE bT类型数据到邮箱
 输入参数  : param 原语内容
             ulLen 原语长度
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_UINT32 ftm_mailbox_ltebt_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_BT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send lte ct to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_FTM_FAILURE;
    }

    ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_tdsct_write
 功能描述  : 写TDS CT类型数据到邮箱
 输入参数  : param 原语内容
             ulLen 原语长度
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_UINT32 ftm_mailbox_tdsct_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_TDS_CT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {

        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send tds ct to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_FTM_FAILURE;
    }

    ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_tdsbt_write
 功能描述  : 写LTE BT类型数据到邮箱
 输入参数  : param 原语内容
             ulLen 原语长度
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_UINT32 ftm_mailbox_tdsbt_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_TDS_BT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {

        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send tds bt to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_FTM_FAILURE;
    }

    ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_ltect_write
 功能描述  : 写LTE CT类型数据到邮箱
 输入参数  : param 原语内容
             ulLen 原语长度
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_UINT32 ftm_mailbox_ct_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    if(EN_FCHAN_MODE_TD_SCDMA == mode)
    {
        ulRet = ftm_mailbox_tdsct_write(param, ulLen);
    }
    else
    {
        ulRet = ftm_mailbox_ltect_write(param, ulLen);
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ftm_mailbox_bt_write
 功能描述  : 写LTE BT类型数据到邮箱
 输入参数  : param 原语内容
             ulLen 原语长度
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_UINT32 ftm_mailbox_bt_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    if(EN_FCHAN_MODE_TD_SCDMA == mode)
    {
        ulRet = ftm_mailbox_tdsbt_write(param, ulLen);
    }
    else
    {
        ulRet = ftm_mailbox_ltebt_write(param, ulLen);
    }

    return ulRet;
}


/*****************************************************************************
 函 数 名  : ftm_mailbox_init
 功能描述  : FTM模块邮箱适配初始化
 输入参数  : param 原语内容
             ulLen 原语长度
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_UINT32 ftm_mailbox_init(VOS_VOID)
{
    if(VOS_OK != VOS_SmBCreate( "ftm_mailbox_taskproc", 0, VOS_SEMA4_FIFO, &g_mailbox_readsem))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]VOS_SmBCreate failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_LTE_CT, ftm_mailbox_ltect_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_LTE_CT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_LTE_BT, ftm_mailbox_ltebt_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_LTE_BT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_TDS_CT, ftm_mailbox_tdsct_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_TDS_CT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_TDS_BT, ftm_mailbox_tdsbt_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_TDS_BT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_FTM_FAILURE;
    }

    return ERR_FTM_SUCCESS;
}

