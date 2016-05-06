/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : mailbox_commsg.c
  版 本 号   : 初稿
  作    者   : c64416
  生成日期   : 2012年12月14日
  最近修改   :
  功能描述   : 普通邮箱处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月14日
    作    者   : c64416
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "xmailbox_types.h"
#include <mdrv_timer.h>
#include <mdrv_bbp.h>
#include <bsp_version.h>
#include "bsp_hardtimer.h"
#include "xmailbox.h"
#include "mdrv_dsp.h"
#include "bsp_ipc.h"

/*****************************************************************************
 函 数 名  : xMbx_ForbidDspSleep
 功能描述  : 设置AXI memory禁止DSP进入睡眠
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
static void xMbx_ForbidDspSleep(void)
{
    unsigned long key;

    local_irq_save(key);
    g_stxMbxCtrl.lAxiCnt++;
    writel(1, (unsigned)(g_stxMbxCtrl.pulAxiAddr));
    local_irq_restore(key);
}

/*****************************************************************************
 函 数 名  : xMbx_ForbidDspSleep
 功能描述  : 清除AXI memory允许DSP进入睡眠
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
static void xMbx_AllowDspSleep(void)
{
    unsigned long key;

    local_irq_save(key);
    if((--g_stxMbxCtrl.lAxiCnt) <= 0)
    {
        g_stxMbxCtrl.lAxiCnt = 0;
        writel(0, (unsigned)(g_stxMbxCtrl.pulAxiAddr));
    }
    local_irq_restore(key);
}

/*lint -save -e717*/
/*****************************************************************************
 Prototype       : xMbx_ComPsPreProc
IPC_INT_DSP_PS_MAC_MBX Description     : PS邮箱的预处理函数(主要作用是更新PS/CTBT消息长度信息)
                   1. 邮箱内有PS消息，则更新PS消息长度
                   2. 邮箱内有CT/BT消息，则更新PS消息长度
                   3. 可能在中断中调用，不能打印和malloc
                   4. DSP保证邮箱中的原语未读走时不睡眠
 param           : None
 Return Value    : void
*****************************************************************************/
void xMbx_ComPsPreProc()
{
    unsigned long key;
    xMAILBOX_RINGBUFF_STRU* pstComPsUpMail = (xMAILBOX_RINGBUFF_STRU*)(g_stxMbxShareAddr.ulCphyMbxHpaUpAddr);
    xMAILBOX_MSG_HAED_STRU *pstMsgHead;
    u32 ulUpWrPtr = 0;

    /* 如果当前原语长度不为0，表示还未读走，不需要更新 */
    if(0 != g_stxMbxCtrl.ulMsgLen) {
        return ;
    }

    local_irq_save(key);


    ulUpWrPtr = pstComPsUpMail->ulRbufWrPtr;

    /* 如果写指针非法，立即重启 */
    if(ulUpWrPtr > pstComPsUpMail->ulRbufSize)
    {
        local_irq_restore(key);
        system_error(DRV_ERRNO_MBX_UP_WR, ulUpWrPtr, pstComPsUpMail->ulRbufRdPtr, (char*)NULL, 0);
        return;
    }

    if(pstComPsUpMail->ulRbufRdPtr == ulUpWrPtr) {
        g_stxMbxCtrl.ulMsgLen = 0;
    } else {
        pstMsgHead = (xMAILBOX_MSG_HAED_STRU*) \
            (pstComPsUpMail->ulRbufRdPtr + pstComPsUpMail->pucRbufAddr + MAILBOX_ADDR_OFFSET);

        g_stxMbxCtrl.ulMsgLen = (u32)(*(u32*)pstMsgHead);    /* 高16位记录mod，低16位记录长度 */  /*lint !e740*/
    }

    local_irq_restore(key);

    return ;
}

/*lint -restore*/
/*****************************************************************************
 Prototype       : BSP_xMailbox_ForbidDspSleep
 Description     : 禁止DSP睡眠接口(与BSP_Mailbox_AllowDspSleep配对使用)
 Input           : enProcType     DSP睡眠时的处理类型
                    EN_MAILBOX_SLEEP_WAKEUP : 强制唤醒时会有等待处理，
                                              不能在中断回调中输入此参数
                                              只能在任务中输入此参数
                    EN_MAILBOX_SLEEP_LOST   : 中断回调和任务中都可输入此参数
                   pkey : intLock key
                   commtype  通信制式 0表示1X， 1表示hrpd，2表示其他不需要传制式的场景

 Return Value    : BSP_OK: 成功,DSP当前没睡眠，且已设置禁止DSP进入睡眠
                   ERR_MAILBOX_DSP_POWERDOWN : 当输入为EN_MAILBOX_SLEEP_LOST,
                                               DSP当前处于低功耗状态,设置失败
                   ERR_MAILBOX_TIMEOUT       : 当输入为EN_MAILBOX_SLEEP_WAKEUP,
                                               唤醒DSP超时(10s)
*****************************************************************************/
unsigned int BSP_xMailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType, u32 commtype)
{
    s32 ret;

    if (g_stxMbxCtrl.mem_init == 0) {
        xMbx_Printf("xMailbox is not inited \n");
        return ERR_MAILBOX_NOT_INIT;
    }

    xMbx_ForbidDspSleep();

    if(EN_MAILBOX_SLEEP_DIRECT == enProcType)/*直接返回OK*/
    {
        g_stxMbxMntn.stDirectInfo.ulSlice[g_stxMbxMntn.stDirectInfo.ulPtr%MAILBOX_MNTN_NUMBER] = bsp_get_slice_value();
        g_stxMbxMntn.stDirectInfo.ulPtr++;
        return BSP_OK;
    }

    /* TODO: 需要考虑禁止哪个模式睡眠 */
    if((NULL != g_stxMbxCtrl.pfnGetDspStatusProc) && (BSP_TRUE == g_stxMbxCtrl.pfnGetDspStatusProc(commtype)))
    {
        if (EN_MAILBOX_SLEEP_WAKEUP == enProcType) {
            ret = osl_sem_downtimeout(&g_stxMbxCtrl.semDspMutex, (MAILBOX_WAKEUP_TIMEOUT*2));
            if(BSP_OK != ret)
            {
                xMbx_Printf("semTake semDspMutex failed.\n");

                ret = ERR_MAILBOX_TIMEOUT;
                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            /* 调用低功耗接口唤醒DSP */
            if(NULL == g_stxMbxCtrl.pfnDspForceAwakeProc)
            {
                ret = ERR_MAILBOX_TIMEOUT;

                osl_sem_up(&g_stxMbxCtrl.semDspMutex);

                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            /* 记录标志，表示是邮箱模块发起的唤醒DSP */
            g_stxMbxCtrl.bDspWakeFlag = BSP_TRUE;

            g_stxMbxMntn.stSleepInfo.astwakeup[g_stxMbxMntn.stSleepInfo.ulPtr].ulSlice1 = bsp_get_slice_value();
            
            /* TODO: 需要考虑唤醒哪个模式 */
            g_stxMbxCtrl.pfnDspForceAwakeProc(commtype);

            /* 等待DSP被唤醒 */
            /* coverity[lock] */
            ret = osl_sem_downtimeout(&g_stxMbxCtrl.semDspWakeup, MAILBOX_WAKEUP_TIMEOUT);

            g_stxMbxMntn.stSleepInfo.astwakeup[g_stxMbxMntn.stSleepInfo.ulPtr].ulSlice3 = bsp_get_slice_value();
            g_stxMbxMntn.stSleepInfo.ulPtr = (g_stxMbxMntn.stSleepInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;

            if (BSP_OK != ret) {
                xMbx_Printf("semTake semDspWakeup failed.\n");

                ret = ERR_MAILBOX_TIMEOUT;

                osl_sem_up(&g_stxMbxCtrl.semDspMutex);

                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            osl_sem_up(&g_stxMbxCtrl.semDspMutex);
        }
        else if(EN_MAILBOX_SLEEP_LOST == enProcType)
        {
            ret = ERR_MAILBOX_DSP_POWERDOWN;
            goto mbx_forbiddspsleep_fail;/*lint !e801*/
        }
        else
        {
            ret = ERR_MAILBOX_PARAM_INCORRECT;

            goto mbx_forbiddspsleep_fail;/*lint !e801*/
        }
    }

    return BSP_OK;

mbx_forbiddspsleep_fail:

    xMbx_AllowDspSleep();

    return (u32)ret;
}


/*****************************************************************************
 Prototype       : BSP_xMailbox_AllowDspSleep
 Description     : 允许DSP睡眠接口(与BSP_Mailbox_ForbidDspSleep配对使用)
 Input           : key : intLock key
 Return Value    : None
*****************************************************************************/
void BSP_xMailbox_AllowDspSleep(void)
{

    xMbx_AllowDspSleep();

}

/*****************************************************************************
 Prototype      : BSP_xMailBox_ComMsgInit
 Description    : 通用邮箱的初始化(提供给协议栈调用，
                  接口内部实现上下行邮箱的初始化和与DSP握手信息的初始化)
 Input          : None
 Return Value   : None
*****************************************************************************/
void BSP_xMailBox_ComMsgInit(unsigned int ulworkingmode)
{
    //unsigned long key;
    //u32 ret;
/*
    ret = BSP_xMailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP);
    if((BSP_OK != ret) && (ERR_MAILBOX_DSP_POWERDOWN != ret))
    {
        xMbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
        return ;
    }
*/
    //local_irq_save(key);

    /* 初始化握手信息 */
// *((u32 *)g_stxMbxShareAddr.ulCphyMbxLoadMemAddr) = 0;

    /* PS向DSP设置工作模式(单卡、双卡、RTT、全系统等信息) */
// *((u32 *)g_stxMbxShareAddr.ulCphyMbxWorkModeAddr) = ulworkingmode;

    //local_irq_restore(key);

    //BSP_xMailbox_AllowDspSleep();

    xMbx_Printf("init success.\n");
}


/*****************************************************************************
 Prototype      : BSP_xMailBox_IsDspOk
 Description    : 与DSP的握手函数，判断DSP是否初始化结束
                  (提供给协议栈调用，如果握手不成功，协议栈需要循环多次调用)
 Input          : None
 Return Value   : BSP_TRUE: DSP初始化结束，握手成功
                  BSP_FALSE:DSP没有初始化结束，握手不成功
*****************************************************************************/
int BSP_xMailBox_IsDspOk(void)
{
    if (g_stxMbxCtrl.mem_init == 0) {
        xMbx_Printf("xMailbox is not inited \n");
        return BSP_FALSE;
    }
    
    if(*((u32 *)g_stxMbxShareAddr.ulCphyMbxLoadMemAddr) != BSP_CPHY_SHAKEHAND_CMP)
    {
        return BSP_FALSE;
    }

    g_stxMbxCtrl.bMbxInit = BSP_TRUE;
    return BSP_TRUE;
}


void xMbx_MntnWritStart(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceStart = bsp_get_slice_value();

    switch(enMbxType)
    {
        case EN_MAILBOX_SERVICE_1X_RL:
        case EN_MAILBOX_SERVICE_HRPD_RL:

            g_stxMbxMntn.stNumber.ulPsComPsReqNum++;
            return;


        case EN_MAILBOX_SERVICE_1X_CT:
        case EN_MAILBOX_SERVICE_1X_BT:
        case EN_MAILBOX_SERVICE_HRPD_CT:
        case EN_MAILBOX_SERVICE_HRPD_BT:

            g_stxMbxMntn.stNumber.ulPsComMspReqNum++;
            return;

        case EN_MAILBOX_SERVICE_1X_OM:
        case EN_MAILBOX_SERVICE_HRPD_OM:
            g_stxMbxMntn.stNumber.ulOmComReqNum++;
            return;
        default :
            return ;
    }
}

void xMbx_MntnWriteEnd(xMAILBOX_RINGBUFF_STRU* pHead, xMAILBOX_MSG_HAED_STRU* pstMsg, u32 ulTempPPTR)
{
    u32 ulInterval = 0;

    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceEnd = bsp_get_slice_value();
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulModId = pstMsg->usDstMod;
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulMsgId = *(u32*)(pstMsg->pPayload);
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulRWPtr = (pHead->ulRbufRdPtr << 16) | ulTempPPTR;

    ulInterval = (g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceEnd
                - g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceStart);
    if(ulInterval > g_stxMbxMntn.stAbnormal.ulLongestReq)
    {
        g_stxMbxMntn.stAbnormal.ulLongestReq = ulInterval;
    }

    g_stxMbxMntn.stReqInfo.ulPtr = (g_stxMbxMntn.stReqInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;
}

/*lint -save -e958*/
/*****************************************************************************
 Prototype       : xMailbox_ComMsgWrite
 Description     : 邮箱写接口处理封装接口
 Input           : ucModule     模块ID
                   pstAddr      邮箱头地址
                   pData        数据指针
                   ulLen        数据长度(以字节为单位)
 Output          : None.
 Return Value    : BSP_OK: 成功
                   其他: 失败
*****************************************************************************/
u32 xMailbox_ComMsgWrite(u8 ucModule,
                            xMAILBOX_RINGBUFF_STRU* pstAddr,
                            void* pData,
                            u32 ulLen)
{
    unsigned long key;
    s32 ret = BSP_OK;
    xMAILBOX_MSG_HAED_STRU stBuffer = {0};

    stBuffer.usMsgSize = (u16)((ulLen + 3) & (~3));
    stBuffer.usDstMod = (u16)ucModule;
    stBuffer.pPayload = pData;

    /* coverity[lock_acquire] */
    local_irq_save(key);
    ret = xMbx_RbuffWrite(pstAddr, &stBuffer);
    local_irq_restore(key);

    if(BSP_OK != ret)
    {
        xMbx_Printf("Mbx_RbuffWrite failed %d, ucModule %d.\n", ret, ucModule);
        xMbx_SystemError((u32)DRV_ERRNO_XMBX_WR_FULL, (u32)stBuffer.usMsgSize, pstAddr->ulRbufRdPtr, pstAddr->ulRbufWrPtr);
    }
    else
    {
        if ((MBX_ADDRESSER_1X_PHY_CT == ucModule) ||(MBX_ADDRESSER_1X_PHY_BT == ucModule)
            ||(MBX_ADDRESSER_HRPD_PHY_CT == ucModule) ||(MBX_ADDRESSER_HRPD_PHY_BT == ucModule))

        {
            xMbx_Printf(" Write CBT 0x%x success.\n",  *((u32*)pData));
        }
    }

    return (u32)ret;
}

/*lint -save -e656 -e661*/
/*****************************************************************************
 Prototype       : BSP_xMailBox_ComMsgWrite
 Description     : 邮箱写接口(每次只支持写一条原语)
 Input           : enMbxType    邮箱的业务类型
                   pData        数据指针
                   ulLen        数据长度(以字节为单位)
                   enProcType   DSP睡眠时的处理类型
 Output          : None.
 Return Value    : BSP_OK: 成功
                   其他: 失败
*****************************************************************************/
unsigned int BSP_xMailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType)
{
    u32 ret = 0;
    xMAILBOX_RINGBUFF_STRU* pstAddr;
    u8 ucModule = 0;
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;
	u32 xmbx_ipc_coreid;
	u32 xmbx_commtype;

    g_stxMbxMntn.stNumber.ulPsComReqNum++;

    /* coverity[cond_at_least] */ /* coverity[cond_between] */
    if((BSP_NULL == pData) || (0 == ulLen) || (ulLen > 0xfffc) ||xMbx_invalid_type(enMbxType))
    {
        xMbx_Printf("pData %p, ulLen %d, enMbxType %d.\n", pData, ulLen, enMbxType);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    /* coverity[cond_between] */
    if(IS_XMBX_1X_MSG_WR(enMbxType))
    {
    	xmbx_commtype = XMBX_MOD_1X;
    }
    /* coverity[between] */ /* coverity[dead_error_condition] */
    else if(IS_XMBX_HRPD_MSG_WR(enMbxType))
    {
        xmbx_commtype = XMBX_MOD_HRPD;
    }
    else
    {
        /* coverity[dead_error_line] */
        xmbx_commtype = XMBX_MOD_OTHER;
    }
	
    if((EN_MAILBOX_SERVICE_1X_CT == enMbxType)
		||(EN_MAILBOX_SERVICE_1X_BT == enMbxType)
		||(EN_MAILBOX_SERVICE_HRPD_CT == enMbxType)
		||(EN_MAILBOX_SERVICE_HRPD_BT == enMbxType))
    {
        xMbx_Printf("Write CBT 0x%x request.\n", *((u32*)pData));
    }

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ERR_MAILBOX_NOT_INIT;
    }
	/*lint -save -e737*/
    xMbx_Trace(pData, ulLen);
	/*lint -restore*/
    pMbxTbl = xMbx_get_tbl(enMbxType);
    pstAddr     = (xMAILBOX_RINGBUFF_STRU*)pMbxTbl->ulDlAddr;
    ucModule    = (u8)pMbxTbl->ulModule;

    xMbx_MntnWritStart(enMbxType);

    ret = BSP_xMailbox_ForbidDspSleep(enProcType,xmbx_commtype);
    if(BSP_OK != ret)
    {
        xMbx_Printf("***[%s]BSP_xMailbox_ForbidDspSleep ret %d\n",__FUNCTION__, ret);
        return ret;
    }

    ret = xMailbox_ComMsgWrite(ucModule, pstAddr, pData, ulLen);
    if(BSP_OK != ret)
    {
        xMbx_Printf("Mailbox_ComMsgWrite failed %d.\n", ret);
    }

    if(BSP_OK == ret)
    {
        if(IS_XMBX_1X_MSG_WR(enMbxType))
        {
            pstAddr->ul1XWrCnt++;
        }
        else if(IS_XMBX_HRPD_MSG_WR(enMbxType))
        {
            pstAddr->ulHRPDWrCnt++;
        }
        else
        {
            // do nothing
        }
        
        if(CHIP_K3V5 == bsp_get_version_info()->chip_type) {
			xmbx_ipc_coreid = IPC_CORE_LDSP;
        }
		else {
			xmbx_ipc_coreid = IPC_CORE_BBE;
		}
        if(BSP_OK != bsp_ipc_int_send((IPC_INT_CORE_E)xmbx_ipc_coreid, pMbxTbl->ulIntNum)) {
            xMbx_Printf("failed to send IPC int %d\n",pMbxTbl->ulIntNum);
        }
    }

    BSP_xMailbox_AllowDspSleep();

    return ret;
}
/*lint -restore*/

/*lint -save -e656 -e778*/
/*****************************************************************************
 Prototype       : BSP_xMailBox_ComNotifyReg
 Description     : 邮箱数据到达通知注册接口（子帧中断即使没数据也要回调）
 param           : enMbxType        邮箱的业务类型
                   pFun             邮箱数据到达处理函数
 Return Value    : BSP_OK: 成功
                   ERR_MAILBOX_NOT_INIT
                   ERR_MAILBOX_PARAM_INCORRECT
*****************************************************************************/
unsigned int BSP_xMailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
                                BSP_xMBX_NOTIFY_FUNC pFun)
{
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;
    /* 目前的机制允许一类业务只注册一个回调函数，对相关通道需要特殊处理 */
    if(xMbx_invalid_type(enMbxType))
    {
        xMbx_Printf("enMbxType %d.\n", enMbxType);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    switch(enMbxType)
    {
        case EN_MAILBOX_SERVICE_1X_RL:
        case EN_MAILBOX_SERVICE_HRPD_RL:
        {
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_1X_RL);
            pMbxTbl->pFnCallBack = pFun;
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_HRPD_RL);
            pMbxTbl->pFnCallBack = pFun;
            break;
        }
        case EN_MAILBOX_SERVICE_1X_BT:
        case EN_MAILBOX_SERVICE_1X_CT:
        case EN_MAILBOX_SERVICE_HRPD_BT:
        case EN_MAILBOX_SERVICE_HRPD_CT:
        {
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_1X_BT);
            pMbxTbl->pFnCallBack = pFun;
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_1X_CT);
            pMbxTbl->pFnCallBack = pFun;
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_HRPD_BT);
            pMbxTbl->pFnCallBack = pFun;
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_HRPD_CT);
            pMbxTbl->pFnCallBack = pFun;
            break;
        }

        default :
        {
            pMbxTbl = xMbx_get_tbl(enMbxType);
            pMbxTbl->pFnCallBack = pFun;
        }
    }

    return BSP_OK;
}
/*lint -restore*/

/*****************************************************************************
 Prototype       : BSP_xMailBox_ComMsgSize
 Description     : 获取通用邮箱中第一条原语的长度
                   (提供给上层调用，驱动不提供邮箱中原语条数接口，需要上层循环
                   读，以避免上层漏掉中断通知时造成邮箱中原语缓存)
 param           : enMbxType        邮箱的业务类型
 Return Value    : 0:  没有获取原语（邮箱为空，或有其他类型的原语未读走）
                   其他值: 邮箱第一条原语的长度
*****************************************************************************/
unsigned int BSP_xMailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    u32 ret;
    u32 len;
    u32 xmbx_commtype;
    unsigned long key;
    /* coverity[cond_at_least] */ /* coverity[cond_between] */
    if (xMbx_invalid_type(enMbxType)) {
        xMbx_Printf("enMbxType %d.\n", enMbxType);
        return 0;
    }
    /* coverity[cond_between] */
    if(IS_XMBX_1X_MSG_WR(enMbxType))
    {
        xmbx_commtype = XMBX_MOD_1X;
    }
    /* coverity[between] */ /* coverity[dead_error_condition] */
    else if(IS_XMBX_HRPD_MSG_WR(enMbxType))
    {
        xmbx_commtype = XMBX_MOD_HRPD;
    }
    else
    {
        /* coverity[dead_error_line] */
        xmbx_commtype = XMBX_MOD_OTHER;
    }

    if((NULL != g_stxMbxCtrl.pfnGetDspStatusProc) && (BSP_TRUE == g_stxMbxCtrl.pfnGetDspStatusProc(xmbx_commtype)))
    {
        return 0;
    }

    if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        xMbx_ComOmPreProc();
        local_irq_save(key);
        len = (g_stxMbxCtrl.ulOmMsgLen & 0x0000ffff);
        ret = xmbx_IsChnModMatch(enMbxType, (g_stxMbxCtrl.ulOmMsgLen >> 16));
        local_irq_restore(key);
    } 
    else if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        xMbx_ComPsPreProc();
        local_irq_save(key);
        len = (g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
        ret = xmbx_IsChnModMatch(enMbxType, (g_stxMbxCtrl.ulMsgLen >> 16));
        local_irq_restore(key);
    } 
    else 
    {
        xMbx_Printf("input error mode.\n");
        return 0;
    }

    if(BSP_OK == ret) {
        return len;
    }

    return 0;
}


/* 发起读取请求时间信息记录 */
void xMbx_MntnReadStart(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    xMAILBOX_MNTN_READ_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    pstCnf = &(g_stxMbxMntn.stReadInfo.astRead[g_stxMbxMntn.stReadInfo.ulPsPtr]);
    pluPtr = &(g_stxMbxMntn.stReadInfo.ulPsPtr);

    pstCnf->ulSrc = enMbxType;
    pstCnf->ulSlice = bsp_get_slice_value();
    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;

    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        g_stxMbxMntn.stNumber.ulPsComPsRdNum++;
    }
    else
    {
        g_stxMbxMntn.stNumber.ulPsComMspRdNum++;
    }

}


void xMbx_MntnReadEnd(void* pData, enum __MBX_ADDRESSEE_ID_ENUM__ enMbxType, u32 pRd, u32 pWr)
{
    xMAILBOX_MNTN_CNF_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    if((MBX_ADDRESSER_1X_PHY_RL == enMbxType) || (MBX_ADDRESSER_HRPD_PHY_RL == enMbxType))
    {
        g_stxMbxMntn.stNumber.ulPsComPsRdOKNum++;

        pstCnf = &(g_stxMbxMntn.stCnfInfo.astPsCnf[g_stxMbxMntn.stCnfInfo.ulPsPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulPsPtr);
    }
    else if((MBX_ADDRESSER_1X_PHY_OM == enMbxType) || (MBX_ADDRESSER_HRPD_PHY_OM == enMbxType))
    {
        g_stxMbxMntn.stNumber.ulOmComOmRdNum++;

        pstCnf = &(g_stxMbxMntn.stCnfInfo.astOmCnf[g_stxMbxMntn.stCnfInfo.ulOmPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulOmPtr);
    }
    else
    {
        g_stxMbxMntn.stNumber.ulPsComMspRdOKNum++;

        pstCnf = &(g_stxMbxMntn.stCnfInfo.astCbtCnf[g_stxMbxMntn.stCnfInfo.ulCbtPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulCbtPtr);
    }

    pstCnf->ulMsgId = *(u32*)pData;
    pstCnf->ulRWptr = (pRd << 16) | pWr;
    pstCnf->ulSlice = bsp_get_slice_value();

    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;
}


/*****************************************************************************
 Prototype       : xMbx_MsgRead
 Description     : 邮箱原语读接口
                   (此接口内部调用)
 param           : pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
                   ulLen        pData缓冲区的size(以字节为单位)
 Return Value    : 0 : 成功
                   其他 : 失败
*****************************************************************************/
u32 xMbx_MsgRead(MAILBOX_SERVICE_TYPE_E enMbxType, void* pData, u32 ulLen)
{
    unsigned long key;
    u32 ret;
    u32 mod;
    u32 len;
    xMAILBOX_MSG_HAED_STRU stBuffer = {0};
    xMAILBOX_RINGBUFF_STRU* pstComPsUpMail;

    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        pstComPsUpMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxHpaUpAddr;
    } 
    else if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        pstComPsUpMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr;
    } 
    else 
    {
        xMbx_Printf(" input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }

    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } 
    else if((EN_MAILBOX_SERVICE_1X_OM == enMbxType)  || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulOmMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulOmMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } 
    else 
    {
        xMbx_Printf("input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }

    ret = xmbx_IsChnModMatch(enMbxType, mod);
    if(BSP_OK != ret) 
    {
        xMbx_Printf("enMbxType(0x%x)  g_stxMbxCtrl.ulMsgLen(0x%x).\n",
            enMbxType, g_stxMbxCtrl.ulMsgLen);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    if(ulLen != len) 
    {
        xMbx_Printf("ulLen(0x%x) != g_stxMbxCtrl.ulMsgLen(0x%x).\n",
            ulLen, g_stxMbxCtrl.ulMsgLen);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    stBuffer.usMsgSize = (u16)ulLen;  /* for compare with actually length */
    stBuffer.pPayload = pData;

    local_irq_save(key);
    ret = xMbx_NewMsgReadOut(&stBuffer, pstComPsUpMail); /* [false alarm]:fortify */
    local_irq_restore(key);

    if(stBuffer.usMsgSize != (u16)len) 
    {
        xMbx_Printf("pBuffer->usMsgSize(0x%x) != g_stxMbxCtrl.ulMsgLen(0x%x).\n",
            stBuffer.usMsgSize, g_stxMbxCtrl.ulMsgLen);
        ret = ERR_MAILBOX_READ_FAILED;
    } 
    else 
    {
        if(IS_XMBX_1X_MSG_WR(enMbxType))
        {
            pstComPsUpMail->ul1XRdCnt++;
        }
        else if(IS_XMBX_HRPD_MSG_WR(enMbxType))
        {
            pstComPsUpMail->ulHRPDRdCnt++;
        }
        else
        {
            // do nothing
        }
        ret = BSP_OK;
    }
    
    /* 读取成功后把长度清零，触发下次读取 */
    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        local_irq_save(key);
        g_stxMbxCtrl.ulMsgLen = 0;
        local_irq_restore(key);
    } 
    else if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        local_irq_save(key);
        g_stxMbxCtrl.ulOmMsgLen = 0;
        local_irq_restore(key);
    } 
    else 
    {
        xMbx_Printf(" input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }

    return ret;
}


/*****************************************************************************
 Prototype       : BSP_xMailBox_ComMsgRead
 Description     : 邮箱读接口
                   (此接口会唤醒DSP，需要BSP_MailBox_ComMsgSize返回非空时调用)
 param           : enMbxType    邮箱的业务类型
                   pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
                   ulLen        pData缓冲区的size(以字节为单位)
                   enProcType   DSP睡眠时的处理类型
 Return Value    : 0 : 成功
                   其他 : 失败
*****************************************************************************/
unsigned int BSP_xMailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType)
{
    unsigned long key;
    u32 ret;
    u16 mod;
    u16 len;
    u32 ulChn;
    u32 xmbx_commtype;
    MAILBOX_INT_TYPE_E enType;
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;

    /* coverity[cond_at_least] */ /* coverity[cond_between] */
    if((BSP_NULL == pData) || (0 == ulLen) || (xMbx_invalid_type(enMbxType)))
    {
        xMbx_Printf(" %p,%d,%d.\n", pData, ulLen, enMbxType);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    /* coverity[cond_between] */
    if(IS_XMBX_1X_MSG_WR(enMbxType))
    {
    	xmbx_commtype = XMBX_MOD_1X;
    }
    /* coverity[between] */ /* coverity[dead_error_condition] */
    else if(IS_XMBX_HRPD_MSG_WR(enMbxType))
    {
        xmbx_commtype = XMBX_MOD_HRPD;
    }
    else
    {
        /* coverity[dead_error_line] */
        xmbx_commtype = XMBX_MOD_OTHER;
    }
	
    /* 记录发起请求的时间信息 */
    xMbx_MntnReadStart(enMbxType);

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ERR_MAILBOX_NOT_INIT;
    }

    ret = BSP_xMailbox_ForbidDspSleep(enProcType,xmbx_commtype);
    if(BSP_OK != ret)
    {
        xMbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
        return ret;
    }

    ret = xMbx_MsgRead(enMbxType, pData, ulLen);

	/*lint -save -e737*/
    xMbx_Trace(pData,ulLen);
	/*lint -restore*/
    /* 更新g_stxMbxCtrl.ulPsMsgLen */
    xMbx_ComPsPreProc();

    BSP_xMailbox_AllowDspSleep();

    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } 
#if 0
    else if(EN_MAILBOX_SERVICE_XSYS_OM == enMbxType) 
    {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulOmMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulOmMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } 
#endif
    else 
    {
        xMbx_Printf("input error mode.\n");
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    if(0 != len) {
        ulChn = xmbx_GetChn(mod);
        if(EN_MAILBOX_SERVICE_TOTAL_BUTT == ulChn) 
        {
            /* DSP写入了非法的MOD，保存现场并重启 */
            xMbx_SystemError((u32)DRV_ERRNO_XMBX_DL_MOD, g_stxMbxCtrl.ulMsgLen, (u32)mod, (u32)len); /* [false alarm]:fortify */
            return ret;
        }

        if(((u16)MBX_ADDRESSER_1X_PHY_RL == mod) || ((u16)MBX_ADDRESSER_HRPD_PHY_RL == mod))
        {
            g_stxMbxMntn.stNumber.ulPsComPsNotifyNum++;
            g_stxMbxMntn.stCallback.ulSlice[g_stxMbxMntn.stCallback.ulPtr] = bsp_get_slice_value();
            g_stxMbxMntn.stCallback.ulPtr = (g_stxMbxMntn.stCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;
        } 
        else 
        {
            g_stxMbxMntn.stNumber.ulPsComMspNotifyNum++;
        }

        pMbxTbl = xMbx_get_tbl(ulChn);
        if(pMbxTbl->pFnCallBack) {
            enType = g_stxMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
            pMbxTbl->pFnCallBack(enType);
        }
    }

    return ret;
}

/*lint -save -e656 -e778*/
void xMbx_CallBackProc(void)
{
    MAILBOX_INT_TYPE_E enType;
    u32 ulChn;
    u16 mod;
    u16 len;
    unsigned long key;
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;

    local_irq_save(key);
    mod = (u16)(g_stxMbxCtrl.ulMsgLen >> 16);
    len = (u16)(g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
    local_irq_restore(key);

    /* 子帧中断或有PS原语则回调PS */
    if((g_stxMbxCtrl.bIsSubFrameInt) || ((0 != len) && (((u16)MBX_ADDRESSER_1X_PHY_RL == mod) || ((u16)MBX_ADDRESSER_HRPD_PHY_RL == mod)))) 
    {
        pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_1X_RL);
        
        if(pMbxTbl->pFnCallBack) 
        {
            g_stxMbxMntn.stNumber.ulPsComPsNotifyNum++;
            g_stxMbxMntn.stCallback.ulSlice[g_stxMbxMntn.stCallback.ulPtr] = bsp_get_slice_value();
            g_stxMbxMntn.stCallback.ulPtr = (g_stxMbxMntn.stCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;

            enType = g_stxMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
            pMbxTbl->pFnCallBack(enType);
        }

        /* PS原语已经在上面回调，此处还要判断是否其他的原语 */
        if((0 != len) && ((u16)MBX_ADDRESSER_LTE_PHY_RL != mod) && ((u16)MBX_ADDRESSER_TDS_PHY_RL != mod)) {
            ulChn = xmbx_GetChn(mod);
            if(EN_MAILBOX_SERVICE_TOTAL_BUTT == ulChn) {
                /* DSP写入了非法的MOD，保存现场并重启 */
                xMbx_SystemError((u32)DRV_ERRNO_XMBX_DL_MOD, g_stxMbxCtrl.ulMsgLen, (u32)mod, (u32)len); /* [false alarm]:fortify */
                return ;
            }
         }

    return;
    }
}
/*lint -restore*/

/*****************************************************************************
 Prototype       : xMbx_ComPsIntProc
 Description     : PS邮箱中断处理函数
                   (如果DSP写邮箱后通过浮动中断通知ARM，DSP应保证在ARM未读走数据前不休眠)
 param           : None
 Return Value    : None
*****************************************************************************/
void xMbx_ComPsIntProc(void)
{
    g_stxMbxMntn.stNumber.ulComPsIntNum++;

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ;
    }

    /* 记录时间，定位中断丢失 */
    g_stxMbxMntn.stIntInfo.ulSlice[g_stxMbxMntn.stIntInfo.ulPtr] = bsp_get_slice_value();
    g_stxMbxMntn.stIntInfo.ulPtr = (g_stxMbxMntn.stIntInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;

    xMbx_ForbidDspSleep();

    /* 更新当前原语长度 */
    xMbx_ComPsPreProc();

    xMbx_AllowDspSleep();

    xMbx_CallBackProc();

    return ;
}

/*****************************************************************************
 Prototype       : BSP_xMailBox_Rcm_CallBackReg
 Description     : Rcm 事件回调注册接口
 param           : None
 Return Value    :
*****************************************************************************/
void BSP_xMailBox_Rcm_CallBackReg(BSP_xMBX_RCM_CALLBACK_FUNC pFunc)
{
    g_stxMbxCtrl.pfnRcmNotifyProc = pFunc;
}

/*****************************************************************************
 Prototype       : xMbx_ComOmPreProc
IPC_INT_DSP_PS_MAC_MBX Description     : PS邮箱的预处理函数(主要作用是更新PS/
CTBT消息长度信息)
                   1. 邮箱内有PS消息，则更新PS消息长度
                   2. 邮箱内有CT/BT消息，则更新PS消息长度
                   3. 可能在中断中调用，不能打印和malloc
                   4. DSP保证邮箱中的原语未读走时不睡眠
 param           : None
 Return Value    : void
*****************************************************************************/
void xMbx_ComOmPreProc()
{
    unsigned long key;
    xMAILBOX_RINGBUFF_STRU* pstComOmUpMail;
	    xMAILBOX_MSG_HAED_STRU *pstMsgHead;
    u32 ulUpWrPtr = 0;

    pstComOmUpMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxOmDownAddr ;

    /* 如果当前原语长度不为0，表示还未读走，不需要更新 */
    if( 0 != g_stxMbxCtrl.ulOmMsgLen )
    {
        return ;
    }

    local_irq_save(key);


    ulUpWrPtr = pstComOmUpMail->ulRbufWrPtr;

    /* 如果写指针非法，立即重启 */
    if(ulUpWrPtr > pstComOmUpMail->ulRbufSize)
    {
        local_irq_restore(key);
        system_error(DRV_ERRNO_XMBX_UP_WR, ulUpWrPtr, pstComOmUpMail->ulRbufRdPtr, (char*)NULL, 0);
        return;
    }

    if(pstComOmUpMail->ulRbufRdPtr == ulUpWrPtr)
    {
        g_stxMbxCtrl.ulOmMsgLen = 0;
    }
    else
    {
        pstMsgHead = (xMAILBOX_MSG_HAED_STRU*) \
            (pstComOmUpMail->ulRbufRdPtr + pstComOmUpMail->pucRbufAddr + MAILBOX_ADDR_OFFSET);
         g_stxMbxCtrl.ulOmMsgLen = (u32)(*(u32*)pstMsgHead);    /* 高16位记录mod，低16位记录长度 */  /*lint !e740*/
    }

    local_irq_restore(key);

    return ;
}

void xMbx_MntnRead(void* pData, MAILBOX_SERVICE_TYPE_E enMbxType)
{
    xMAILBOX_MNTN_CNF_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        pstCnf = &(g_stxMbxMntn.stCnfInfo.astPsCnf[g_stxMbxMntn.stCnfInfo.ulPsPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulPsPtr);
    }
    else if ((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        pstCnf = &(g_stxMbxMntn.stCnfInfo.astOmCnf[g_stxMbxMntn.stCnfInfo.ulOmPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulOmPtr);
    }
    else
    {
        pstCnf = &(g_stxMbxMntn.stCnfInfo.astCbtCnf[g_stxMbxMntn.stCnfInfo.ulCbtPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulCbtPtr);
    }

    pstCnf->ulMsgId = *(u32*)pData;
    pstCnf->ulSlice = bsp_get_slice_value();

    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;
}

/*****************************************************************************
 Prototype       : xMailbox_OmMsgRead
 Description     : Om原语读接口
                   (此接口内部调用)
 param           : pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
                   ulLen        pData缓冲区的size(以字节为单位)
 Return Value    : 0 : 成功
                   其他 : 失败
*****************************************************************************/
u32 xMailbox_OmMsgRead(void* pData, u32 ulLen)
{
    unsigned long key;
    u32 ret;

    xMAILBOX_MSG_HAED_STRU stBuffer = {0};
    xMAILBOX_RINGBUFF_STRU* pstComOmDownMail;

    pstComOmDownMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxOmDownAddr ;

    if(ulLen != g_stxMbxCtrl.ulOmMsgLen)
    {
        xMbx_Printf(" ulLen(%d) != g_stxMbxCtrl.ulOmMsgLen(%d).\n",
            ulLen, g_stxMbxCtrl.ulOmMsgLen);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    stBuffer.usMsgSize = (u16)ulLen;  /* for compare with actually length */
    stBuffer.pPayload = pData;

    local_irq_save(key);
    ret = xMbx_NewMsgReadOut(&stBuffer, pstComOmDownMail);
    local_irq_restore(key);

    if(stBuffer.usMsgSize != g_stxMbxCtrl.ulOmMsgLen)
    {
        xMbx_Printf("pBuffer->usMsgSize(%d) != g_stxMbxCtrl.ulOmMsgLen(%d).\n",
            stBuffer.usMsgSize, g_stxMbxCtrl.ulOmMsgLen);

        ret = ERR_MAILBOX_READ_FAILED;
    }
    else if(( MBX_ADDRESSER_1X_PHY_OM != stBuffer.usDstMod ) || ( MBX_ADDRESSER_HRPD_PHY_OM != stBuffer.usDstMod ))
    {
        xMbx_Printf("pBuffer->usDstMod %d.\n",
            stBuffer.usDstMod);

        ret = ERR_MAILBOX_READ_FAILED;
    }
    else
    {
        g_stxMbxMntn.stNumber.ulOmComOmRdOKNum++;

        ret = BSP_OK;
    }

    xMbx_MntnRead(pData, EN_MAILBOX_SERVICE_1X_OM);

    /* 读取成功后把长度清零，触发下次读取 */
    local_irq_save(key);
    g_stxMbxCtrl.ulOmMsgLen = 0;
    local_irq_restore(key);

    /* 更新g_stxMbxCtrl.ulOmMsgLen */
    xMbx_ComOmPreProc();

    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}

#endif
#endif




/* end C file */

