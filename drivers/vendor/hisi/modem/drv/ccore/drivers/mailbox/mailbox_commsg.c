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

#include "mailbox.h"
#include "mailbox_types.h"
#include <mdrv_timer.h>
#include <mdrv_bbp.h>
#include "bsp_hardtimer.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*lint -save -e717*/
/*****************************************************************************
 Prototype       : Mbx_ComPsPreProc
IPC_INT_DSP_PS_MAC_MBX Description     : PS邮箱的预处理函数(主要作用是更新PS/CTBT消息长度信息)
                   1. 邮箱内有PS消息，则更新PS消息长度
                   2. 邮箱内有CT/BT消息，则更新PS消息长度
                   3. 可能在中断中调用，不能打印和malloc
                   4. DSP保证邮箱中的原语未读走时不睡眠
 param           : None
 Return Value    : void
*****************************************************************************/
void Mbx_ComPsPreProc()
{
    unsigned long key;
    MAILBOX_RINGBUFF_STRU* pstComPsUpMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_PS_UP_ADDR;
    MAILBOX_MSG_HAED_STRU *pstMsgHead;
    u32 ulUpWrPtr = 0;

    /* 如果当前原语长度不为0，表示还未读走，不需要更新 */
    if(0 != g_stMbxCtrl.ulMsgLen)
    {
        return ;
    }

    local_irq_save(key);

#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
#else
    /* DSP是否睡眠,如果没睡眠 */
    if((NULL != g_stMbxCtrl.pfnGetDspStatusProc) && (BSP_FALSE == g_stMbxCtrl.pfnGetDspStatusProc()))
#endif
    {
        ulUpWrPtr = pstComPsUpMail->ulRbufWrPtr;

        /* 如果写指针非法，立即重启 */
        if(ulUpWrPtr > pstComPsUpMail->ulRbufSize)
        {
            local_irq_restore(key);

            system_error(DRV_ERRNO_MBX_UP_WR, ulUpWrPtr, pstComPsUpMail->ulRbufRdPtr, (char*)NULL, 0);

            return;
        }

        if(pstComPsUpMail->ulRbufRdPtr == ulUpWrPtr)
        {
            g_stMbxCtrl.ulMsgLen = 0;
        }
        else
        {
            pstMsgHead = (MAILBOX_MSG_HAED_STRU*) \
                (pstComPsUpMail->ulRbufRdPtr + pstComPsUpMail->pucRbufAddr + MAILBOX_ADDR_OFFSET);

            g_stMbxCtrl.ulMsgLen = (u32)(*(u32*)pstMsgHead);    /* 高16位记录mod，低16位记录长度 */  /*lint !e740*/
        }
    }
    local_irq_restore(key);

    return ;
}


/*****************************************************************************
 Prototype      : BSP_MailBox_ComMsgInit
 Description    : 通用邮箱的初始化(提供给协议栈调用，
                  接口内部实现上下行邮箱的初始化和与DSP握手信息的初始化)
 Input          : None
 Return Value   : None
*****************************************************************************/
void BSP_MailBox_ComMsgInit(unsigned int ulworkingmode)
{
    unsigned long key;
    u32 ret;

    ret = BSP_Mailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP);
    if((BSP_OK != ret) && (ERR_MAILBOX_DSP_POWERDOWN != ret))
    {
        Mbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
        return ;
    }

    local_irq_save(key);

    /* 初始化握手信息 */
    *((u32 *)BSP_DSP_INIT_RESULT_ADDR) = 0;

    /* PS向DSP设置工作模式(单卡、双卡、RTT、全系统等信息) */
    *((u32 *)BSP_DSP_WORKING_MODE_ADDR) = ulworkingmode;

    local_irq_restore(key);

    BSP_Mailbox_AllowDspSleep();

    Mbx_Printf("init success.\n");
}


/*****************************************************************************
 Prototype      : BSP_MailBox_IsDspOk
 Description    : 与DSP的握手函数，判断DSP是否初始化结束
                  (提供给协议栈调用，如果握手不成功，协议栈需要循环多次调用)
 Input          : None
 Return Value   : BSP_TRUE: DSP初始化结束，握手成功
                  BSP_FALSE:DSP没有初始化结束，握手不成功
*****************************************************************************/
int BSP_MailBox_IsDspOk(void)
{
    if(*((u32 *)BSP_DSP_INIT_RESULT_ADDR) != BSP_TL_SHAKEHAND_CMP)
    {
        return BSP_FALSE;
    }

    g_stMbxCtrl.bMbxInit = BSP_TRUE;
    return BSP_TRUE;
}


void Mbx_MntnWritStart(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    g_stMbxMntn.stReqInfo.astReq[g_stMbxMntn.stReqInfo.ulPtr].ulSliceStart = bsp_get_slice_value();

    switch(enMbxType)
    {
        case EN_MAILBOX_SERVICE_LTE_PS:
        case EN_MAILBOX_SERVICE_TDS_PS:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_1X_RL:
        case EN_MAILBOX_SERVICE_HRPD_RL:
#endif
            g_stMbxMntn.stNumber.ulPsComPsReqNum++;
            return;

        case EN_MAILBOX_SERVICE_LTE_CT:
        case EN_MAILBOX_SERVICE_LTE_BT:
        case EN_MAILBOX_SERVICE_TDS_CT:
        case EN_MAILBOX_SERVICE_TDS_BT:
        case EN_MAILBOX_SERVICE_LTE_COEX:
        case EN_MAILBOX_SERVICE_RTT_SYS_CTRL:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_1X_CT:
        case EN_MAILBOX_SERVICE_1X_BT:
        case EN_MAILBOX_SERVICE_HRPD_CT:
        case EN_MAILBOX_SERVICE_HRPD_BT:
#endif
            g_stMbxMntn.stNumber.ulPsComMspReqNum++;
            return;
        case EN_MAILBOX_SERVICE_LTE_RCM:
        case EN_MAILBOX_SERVICE_TDS_RCM:
            g_stMbxMntn.stNumber.ulPsComRcmReqNum++;
            return;
        case EN_MAILBOX_SERVICE_LTE_OM:
        case EN_MAILBOX_SERVICE_TDS_OM:
        case EN_MAILBOX_SERVICE_LTE_HS_DIAG:
        case EN_MAILBOX_SERVICE_TDS_HS_DIAG:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_1X_OM:
        case EN_MAILBOX_SERVICE_HRPD_OM:
#endif
            g_stMbxMntn.stNumber.ulOmComReqNum++;
            return;
        case EN_MAILBOX_SERVICE_RTT_AGENT:
            g_stMbxMntn.stNumber.ulPsComRttAgentReqNum++;
            return;
        default :
            return ;
    }
}

void Mbx_MntnWriteEnd(MAILBOX_RINGBUFF_STRU* pHead, MAILBOX_MSG_HAED_STRU* pstMsg, u32 ulTempPPTR)
{
    u32 ulInterval = 0;

    g_stMbxMntn.stReqInfo.astReq[g_stMbxMntn.stReqInfo.ulPtr].ulSliceEnd = bsp_get_slice_value();
    g_stMbxMntn.stReqInfo.astReq[g_stMbxMntn.stReqInfo.ulPtr].ulModId = pstMsg->usDstMod;
    g_stMbxMntn.stReqInfo.astReq[g_stMbxMntn.stReqInfo.ulPtr].ulMsgId = *(u32*)(pstMsg->pPayload);
    g_stMbxMntn.stReqInfo.astReq[g_stMbxMntn.stReqInfo.ulPtr].ulRWPtr = (pHead->ulRbufRdPtr << 16) | ulTempPPTR;

    ulInterval = (g_stMbxMntn.stReqInfo.astReq[g_stMbxMntn.stReqInfo.ulPtr].ulSliceEnd
                - g_stMbxMntn.stReqInfo.astReq[g_stMbxMntn.stReqInfo.ulPtr].ulSliceStart);
    if(ulInterval > g_stMbxMntn.stAbnormal.ulLongestReq)
    {
        g_stMbxMntn.stAbnormal.ulLongestReq = ulInterval;
    }

    g_stMbxMntn.stReqInfo.ulPtr = (g_stMbxMntn.stReqInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;
}

/*lint -save -e958*/
/*****************************************************************************
 Prototype       : Mailbox_ComMsgWrite
 Description     : 邮箱写接口处理封装接口
 Input           : ucModule     模块ID
                   pstAddr      邮箱头地址
                   pData        数据指针
                   ulLen        数据长度(以字节为单位)
 Output          : None.
 Return Value    : BSP_OK: 成功
                   其他: 失败
*****************************************************************************/
u32 Mailbox_ComMsgWrite(u8 ucModule,
                            MAILBOX_RINGBUFF_STRU* pstAddr,
                            void* pData,
                            u32 ulLen)
{
    unsigned long key;
    s32 ret = BSP_OK;
    MAILBOX_MSG_HAED_STRU stBuffer = {0};

    stBuffer.usMsgSize = (u16)((ulLen + 3) & (~3));
    stBuffer.usDstMod = (u16)ucModule;
    stBuffer.pPayload = pData;

    /* coverity[lock_acquire] */
    local_irq_save(key);
    ret = Mbx_RbuffWrite(pstAddr, &stBuffer);
    local_irq_restore(key);

    if(BSP_OK != ret)
    {
        Mbx_Printf("Mbx_RbuffWrite failed %d, ucModule %d.\n", ret, ucModule);
        Mbx_SystemError((u32)TLPHY_REBOOT_MOD_ID_DL_MBX_FULL, (u32)stBuffer.usMsgSize, pstAddr->ulRbufRdPtr, pstAddr->ulRbufWrPtr);
    }
    else
    {
        if((MBX_ADDRESSER_LTE_PHY_BT == ucModule)
            || (MBX_ADDRESSER_LTE_PHY_CT == ucModule)
            || (MBX_ADDRESSER_TDS_PHY_BT == ucModule)
            || (MBX_ADDRESSER_TDS_PHY_CT == ucModule)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
			||(MBX_ADDRESSER_1X_PHY_CT == ucModule)
			||(MBX_ADDRESSER_1X_PHY_BT == ucModule)
			||(MBX_ADDRESSER_HRPD_PHY_CT == ucModule)
			||(MBX_ADDRESSER_HRPD_PHY_BT == ucModule)
#endif
			)
        {
            Mbx_Printf(" Write CBT 0x%x success.\n",  *((u32*)pData));
        }
    }

    return (u32)ret;
}
/*lint -restore*/
/*****************************************************************************
 Prototype       : BSP_Mailbox_ForbidDspSleep
 Description     : 禁止DSP睡眠接口(与BSP_Mailbox_AllowDspSleep配对使用)
 Input           : enProcType     DSP睡眠时的处理类型
                    EN_MAILBOX_SLEEP_WAKEUP : 强制唤醒时会有等待处理，
                                              不能在中断回调中输入此参数
                                              只能在任务中输入此参数
                    EN_MAILBOX_SLEEP_LOST   : 中断回调和任务中都可输入此参数
                   pkey : intLock key

 Return Value    : BSP_OK: 成功,DSP当前没睡眠，且已设置禁止DSP进入睡眠
                   ERR_MAILBOX_DSP_POWERDOWN : 当输入为EN_MAILBOX_SLEEP_LOST,
                                               DSP当前处于低功耗状态,设置失败
                   ERR_MAILBOX_TIMEOUT       : 当输入为EN_MAILBOX_SLEEP_WAKEUP,
                                               唤醒DSP超时(10s)
*****************************************************************************/
unsigned int BSP_Mailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    return BSP_OK;
#else
    s32 ret;

    Mbx_ForbidDspSleep();

    if(EN_MAILBOX_SLEEP_DIRECT == enProcType)/*直接返回OK*/
    {
        g_stMbxMntn.stDirectInfo.ulSlice[g_stMbxMntn.stDirectInfo.ulPtr%MAILBOX_MNTN_NUMBER] = bsp_get_slice_value();
        g_stMbxMntn.stDirectInfo.ulPtr++;
        return BSP_OK;
    }

    if((NULL != g_stMbxCtrl.pfnGetDspStatusProc) && (BSP_TRUE == g_stMbxCtrl.pfnGetDspStatusProc()))
    {
        if(EN_MAILBOX_SLEEP_WAKEUP == enProcType)
        {
            ret = osl_sem_downtimeout(&g_stMbxCtrl.semDspMutex, (MAILBOX_WAKEUP_TIMEOUT*2));
            if(BSP_OK != ret)
            {
                Mbx_Printf("semTake semDspMutex failed.\n");

                ret = ERR_MAILBOX_TIMEOUT;
                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            /* 调用低功耗接口唤醒DSP */
            if(NULL == g_stMbxCtrl.pfnDspForceAwakeProc)
            {
                ret = ERR_MAILBOX_TIMEOUT;

                osl_sem_up(&g_stMbxCtrl.semDspMutex);

                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            /* 记录标志，表示是邮箱模块发起的唤醒DSP */
            g_stMbxCtrl.bDspWakeFlag = BSP_TRUE;

            g_stMbxMntn.stSleepInfo.astwakeup[g_stMbxMntn.stSleepInfo.ulPtr].ulSlice1 = bsp_get_slice_value();

            g_stMbxCtrl.pfnDspForceAwakeProc();

            /* 等待DSP被唤醒 */
            /* coverity[lock] */
            ret = osl_sem_downtimeout(&g_stMbxCtrl.semDspWakeup, MAILBOX_WAKEUP_TIMEOUT);

            g_stMbxMntn.stSleepInfo.astwakeup[g_stMbxMntn.stSleepInfo.ulPtr].ulSlice3 = bsp_get_slice_value();
            g_stMbxMntn.stSleepInfo.ulPtr = (g_stMbxMntn.stSleepInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;

            if(BSP_OK != ret)
            {
                Mbx_Printf("semTake semDspWakeup failed.\n");

                ret = ERR_MAILBOX_TIMEOUT;

                osl_sem_up(&g_stMbxCtrl.semDspMutex);

                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            osl_sem_up(&g_stMbxCtrl.semDspMutex);
        }
        else if(EN_MAILBOX_SLEEP_LOST == enProcType)
        {
            ret = ERR_MAILBOX_DSP_POWERDOWN;

            goto mbx_forbiddspsleep_fail;/*lint !e801*/
        }
        else
        {
            Mbx_Printf("enProcType %d.\n",enProcType);

            ret = ERR_MAILBOX_PARAM_INCORRECT;

            goto mbx_forbiddspsleep_fail;/*lint !e801*/
        }
    }

    return BSP_OK;

mbx_forbiddspsleep_fail:

    Mbx_AllowDspSleep();

    return (u32)ret;
#endif
}


/*****************************************************************************
 Prototype       : BSP_Mailbox_AllowDspSleep
 Description     : 允许DSP睡眠接口(与BSP_Mailbox_ForbidDspSleep配对使用)
 Input           : key : intLock key
 Return Value    : None
*****************************************************************************/
void BSP_Mailbox_AllowDspSleep(void)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
#else
    Mbx_AllowDspSleep();
#endif
}


/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgWrite
 Description     : 邮箱写接口(每次只支持写一条原语)
 Input           : enMbxType    邮箱的业务类型
                   pData        数据指针
                   ulLen        数据长度(以字节为单位)
                   enProcType   DSP睡眠时的处理类型
 Output          : None.
 Return Value    : BSP_OK: 成功
                   其他: 失败
*****************************************************************************/
unsigned int BSP_MailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType)
{
    u32 ret = 0;
    MAILBOX_RINGBUFF_STRU* pstAddr;
    u8 ucModule = 0;

    g_stMbxMntn.stNumber.ulPsComReqNum++;

    if((BSP_NULL == pData) || (0 == ulLen) || (ulLen > 0xfffc) ||(enMbxType >= EN_MAILBOX_SERVICE_BUTT))
    {
        Mbx_Printf("pData %p, ulLen %d, enMbxType %d.\n", pData, ulLen, enMbxType);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    if((EN_MAILBOX_SERVICE_LTE_CT == enMbxType)
        || (EN_MAILBOX_SERVICE_LTE_BT == enMbxType)
        || (EN_MAILBOX_SERVICE_TDS_CT == enMbxType)
        || (EN_MAILBOX_SERVICE_TDS_BT == enMbxType)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
		||(EN_MAILBOX_SERVICE_1X_CT == enMbxType)
		||(EN_MAILBOX_SERVICE_1X_BT == enMbxType)
		||(EN_MAILBOX_SERVICE_HRPD_CT == enMbxType)
		||(EN_MAILBOX_SERVICE_HRPD_BT == enMbxType)
#endif
		)
    {
        Mbx_Printf("Write CBT 0x%x request.\n", *((u32*)pData));
    }

    if(!(g_stMbxCtrl.bMbxInit))
    {
        g_stMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ERR_MAILBOX_NOT_INIT;
    }
	/*lint -save -e737*/
    Mbx_Trace(pData, ulLen);
	/*lint -restore*/
    pstAddr     = (MAILBOX_RINGBUFF_STRU*)g_astMbxChnTbl[enMbxType].ulDlAddr;
    ucModule    = (u8)g_astMbxChnTbl[enMbxType].ulModule;

    Mbx_MntnWritStart(enMbxType);

    ret = BSP_Mailbox_ForbidDspSleep(enProcType);
    if(BSP_OK != ret)
    {
        return ret;
    }

    ret = Mailbox_ComMsgWrite(ucModule, pstAddr, pData, ulLen);
    if(BSP_OK != ret)
    {
        Mbx_Printf("Mailbox_ComMsgWrite failed %d.\n", ret);
    }

    if(BSP_OK == ret)
    {
        if(BSP_OK != mdrv_ipc_int_send(MBX_IPC_CORE_DSP,g_astMbxChnTbl[enMbxType].ulIntNum))
        {
            Mbx_Printf("mdrv_ipc_int_send PS failed. Int Num %d\n",g_astMbxChnTbl[enMbxType].ulIntNum);
        }
    }

    BSP_Mailbox_AllowDspSleep();

    return ret;
}

/*****************************************************************************
 Prototype       : BSP_MailBox_ComNotifyReg
 Description     : 邮箱数据到达通知注册接口（子帧中断即使没数据也要回调）
 param           : enMbxType        邮箱的业务类型
                   pFun             邮箱数据到达处理函数
 Return Value    : BSP_OK: 成功
                   ERR_MAILBOX_NOT_INIT
                   ERR_MAILBOX_PARAM_INCORRECT
*****************************************************************************/
unsigned int BSP_MailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
                                BSP_MBX_NOTIFY_FUNC pFun)
{
    /* 目前的机制允许一类业务只注册一个回调函数，对相关通道需要特殊处理 */
    if(enMbxType >= EN_MAILBOX_SERVICE_BUTT)
    {
        Mbx_Printf("enMbxType %d.\n", enMbxType);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    switch(enMbxType)
    {
        case EN_MAILBOX_SERVICE_LTE_PS:
        case EN_MAILBOX_SERVICE_TDS_PS:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_1X_RL:
        case EN_MAILBOX_SERVICE_HRPD_RL:
#endif
        {
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_LTE_PS].pFnCallBack = pFun;
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_TDS_PS].pFnCallBack = pFun;
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_1X_RL].pFnCallBack = pFun;
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_HRPD_RL].pFnCallBack = pFun;
#endif
            break;
        }

        case EN_MAILBOX_SERVICE_LTE_CT:
        case EN_MAILBOX_SERVICE_LTE_BT:
        case EN_MAILBOX_SERVICE_TDS_CT:
        case EN_MAILBOX_SERVICE_TDS_BT:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_LTE_COEX:
        case EN_MAILBOX_SERVICE_1X_BT:
        case EN_MAILBOX_SERVICE_1X_CT:
        case EN_MAILBOX_SERVICE_HRPD_BT:
        case EN_MAILBOX_SERVICE_HRPD_CT:
#endif
        {
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_LTE_CT].pFnCallBack = pFun;
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_LTE_BT].pFnCallBack = pFun;
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_TDS_CT].pFnCallBack = pFun;
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_TDS_BT].pFnCallBack = pFun;
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
			g_astMbxChnTbl[EN_MAILBOX_SERVICE_LTE_COEX].pFnCallBack = pFun;
			g_astMbxChnTbl[EN_MAILBOX_SERVICE_1X_BT].pFnCallBack = pFun;
			g_astMbxChnTbl[EN_MAILBOX_SERVICE_1X_CT].pFnCallBack = pFun;
			g_astMbxChnTbl[EN_MAILBOX_SERVICE_HRPD_BT].pFnCallBack = pFun;
			g_astMbxChnTbl[EN_MAILBOX_SERVICE_HRPD_CT].pFnCallBack = pFun;
#endif
            break;
        }

        case EN_MAILBOX_SERVICE_RTT_AGENT:
        {
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_RTT_AGENT].pFnCallBack = pFun;
            break;
        }

        default :
        {
            g_astMbxChnTbl[enMbxType].pFnCallBack = pFun;
        }
    }

    return BSP_OK;
}


/*****************************************************************************
 Prototype       : BSP_MailBox_IntTypeSet
 Description     : 设置PS邮箱中断源接口(默认IPC中断方式)
                   只用于PS邮箱，OM邮箱无中断上报
 param           : None
 Return Value    : 0: 成功; 其他: 设置的type非法
*****************************************************************************/
unsigned int BSP_MailBox_IntTypeSet(MAILBOX_INT_TYPE_E enIntType)
{
    s32 ret;

    switch(enIntType)
    {
        case EN_MAILBOX_INT_SUBFRAME:
        {
            if(BSP_OK != BSP_Mailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP))
            {
                Mbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
                return ERR_MAILBOX_TIMEOUT;
            }

            mdrv_bbp_register_lte_intr_cb(Mbx_ComPsIntProc);

            ret = mdrv_bbp_enable_lte_intr();/* [false alarm]:fortify */
            if(BSP_OK != ret)
            {
                Mbx_Printf("BSP_BBPIntTimerEnable failed.\n");
            }

            BSP_Mailbox_AllowDspSleep();

            ret = (s32)mdrv_ipc_int_disable(IPC_INT_DSP_PS_PUB_MBX);
            if(BSP_OK != ret)
            {
                Mbx_Printf("mdrv_ipc_int_disable failed.\n");
            }

            ret = (s32)mdrv_ipc_int_disconnect(IPC_INT_DSP_PS_PUB_MBX, NULL, 0); /* [false alarm]:fortify */
            if(BSP_OK != ret)
            {
                Mbx_Printf("mdrv_ipc_int_disconnect failed.\n");
            }

            g_stMbxCtrl.bIsSubFrameInt = BSP_TRUE;

            break;
        }

        case EN_MAILBOX_INT_COM_IPC:
        {
            ret = (s32)mdrv_ipc_int_connect(IPC_INT_DSP_PS_PUB_MBX, (VOIDFUNCPTR)Mbx_ComPsIntProc, 0);
            if(BSP_OK != ret)
            {
                Mbx_Printf("mdrv_ipc_int_connect failed.\n");
            }

            ret = (s32)mdrv_ipc_int_enable(IPC_INT_DSP_PS_PUB_MBX);
            if(BSP_OK != ret)
            {
                Mbx_Printf("mdrv_ipc_int_enable failed.\n");
            }

            if(BSP_OK != BSP_Mailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP))
            {
                Mbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
                return ERR_MAILBOX_TIMEOUT;
            }

            mdrv_bbp_disable_lte_intr();

            mdrv_bbp_clear_lte_intr();

            BSP_Mailbox_AllowDspSleep();

            g_stMbxCtrl.bIsSubFrameInt = BSP_FALSE;

            break;
        }

        default :
        {
            Mbx_Printf("enIntType %d.\n", enIntType);
            return ERR_MAILBOX_PARAM_INCORRECT;
        }
    }

    return BSP_OK;
}


/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgSize
 Description     : 获取通用邮箱中第一条原语的长度
                   (提供给上层调用，驱动不提供邮箱中原语条数接口，需要上层循环
                   读，以避免上层漏掉中断通知时造成邮箱中原语缓存)
 param           : enMbxType        邮箱的业务类型
 Return Value    : 0:  没有获取原语（邮箱为空，或有其他类型的原语未读走）
                   其他值: 邮箱第一条原语的长度
*****************************************************************************/
unsigned int BSP_MailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    u32 ret;
    u32 len;
    unsigned long key;

    if(enMbxType >= EN_MAILBOX_SERVICE_BUTT)
    {
        Mbx_Printf("enMbxType %d.\n", enMbxType);
        return 0;
    }

#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        local_irq_save(key);
        len = (g_stMbxCtrl.ulOmMsgLen & 0x0000ffff);
        ret = mbx_IsChnModMatch(enMbxType, (g_stMbxCtrl.ulOmMsgLen >> 16));
        local_irq_restore(key);
    }
    else if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        local_irq_save(key);
        len = (g_stMbxCtrl.ulMsgLen & 0x0000ffff);
        ret = mbx_IsChnModMatch(enMbxType, (g_stMbxCtrl.ulMsgLen >> 16));
        local_irq_restore(key);
    }
    else
    {
        Mbx_Printf("input error mode.\n");
        return 0;
    }
#else
    local_irq_save(key);
    len = (g_stMbxCtrl.ulMsgLen & 0x0000ffff);
    ret = mbx_IsChnModMatch(enMbxType, (g_stMbxCtrl.ulMsgLen >> 16));
    local_irq_restore(key);
#endif
    if(BSP_OK == ret)
    {
        return len;
    }

    return 0;
}


/* 发起读取请求时间信息记录 */
void Mbx_MntnReadStart(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    MAILBOX_MNTN_READ_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    pstCnf = &(g_stMbxMntn.stReadInfo.astRead[g_stMbxMntn.stReadInfo.ulPsPtr]);
    pluPtr = &(g_stMbxMntn.stReadInfo.ulPsPtr);

    pstCnf->ulSrc = enMbxType;
    pstCnf->ulSlice = bsp_get_slice_value();
    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;

    if((EN_MAILBOX_SERVICE_LTE_PS == enMbxType)
        || (EN_MAILBOX_SERVICE_TDS_PS == enMbxType)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        || (EN_MAILBOX_SERVICE_1X_RL == enMbxType)
        || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType)
#endif
    )
    {
        g_stMbxMntn.stNumber.ulPsComPsRdNum++;
    }
    else if((EN_MAILBOX_SERVICE_LTE_RCM == enMbxType)
        || (EN_MAILBOX_SERVICE_TDS_RCM == enMbxType))
    {
        g_stMbxMntn.stNumber.ulPsComRcmRdNum++;
    }
    else if(EN_MAILBOX_SERVICE_RTT_AGENT== enMbxType)
    {
        g_stMbxMntn.stNumber.ulPsComRttAgentRdNum++;
    }
    else
    {
        g_stMbxMntn.stNumber.ulPsComMspRdNum++;
    }

}


void Mbx_MntnReadEnd(void* pData, enum __MBX_ADDRESSEE_ID_ENUM__ enMbxType, u32 pRd, u32 pWr)
{
    MAILBOX_MNTN_CNF_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    if((MBX_ADDRESSER_LTE_PHY_RL == enMbxType)
     ||(MBX_ADDRESSER_TDS_PHY_RL == enMbxType)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
	 ||(MBX_ADDRESSER_1X_PHY_RL == enMbxType)
	 ||(MBX_ADDRESSER_HRPD_PHY_RL == enMbxType)
#endif
	 )
    {
        g_stMbxMntn.stNumber.ulPsComPsRdOKNum++;

        pstCnf = &(g_stMbxMntn.stCnfInfo.astPsCnf[g_stMbxMntn.stCnfInfo.ulPsPtr]);

        pluPtr = &(g_stMbxMntn.stCnfInfo.ulPsPtr);
    }
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    else if((MBX_ADDRESSER_1X_PHY_OM == enMbxType) || (MBX_ADDRESSER_HRPD_PHY_OM == enMbxType))
    {
        g_stMbxMntn.stNumber.ulOmComOmRdNum++;

        pstCnf = &(g_stMbxMntn.stCnfInfo.astOmCnf[g_stMbxMntn.stCnfInfo.ulOmPtr]);

        pluPtr = &(g_stMbxMntn.stCnfInfo.ulOmPtr);
    }
#endif
    else if((MBX_ADDRESSER_LTE_PHY_RCM == enMbxType)
     ||(MBX_ADDRESSER_TDS_PHY_RCM == enMbxType))
    {
        g_stMbxMntn.stNumber.ulPsComRcmRdOKNum++;
        pstCnf = &(g_stMbxMntn.stCnfInfo.astRcmCnf[g_stMbxMntn.stCnfInfo.ulRcmPtr]);
        pluPtr = &(g_stMbxMntn.stCnfInfo.ulRcmPtr);
    }
    else if(MBX_ADDRESSER_RTT_AGENT == enMbxType)
    {
        g_stMbxMntn.stNumber.ulPsComRttAgentRdOKNum++;
        pstCnf = &(g_stMbxMntn.stCnfInfo.astRttAgentCnf[g_stMbxMntn.stCnfInfo.ulRttAgentPtr]);
        pluPtr = &(g_stMbxMntn.stCnfInfo.ulRttAgentPtr);
        
    }
    else
    {
        g_stMbxMntn.stNumber.ulPsComMspRdOKNum++;

        pstCnf = &(g_stMbxMntn.stCnfInfo.astCbtCnf[g_stMbxMntn.stCnfInfo.ulCbtPtr]);

        pluPtr = &(g_stMbxMntn.stCnfInfo.ulCbtPtr);
    }

    pstCnf->ulMsgId = *(u32*)pData;
    pstCnf->ulRWptr = (pRd << 16) | pWr;
    pstCnf->ulSlice = bsp_get_slice_value();

    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;
}


/*****************************************************************************
 Prototype       : Mbx_MsgRead
 Description     : 邮箱原语读接口
                   (此接口内部调用)
 param           : pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
                   ulLen        pData缓冲区的size(以字节为单位)
 Return Value    : 0 : 成功
                   其他 : 失败
*****************************************************************************/
u32 Mbx_MsgRead(MAILBOX_SERVICE_TYPE_E enMbxType, void* pData, u32 ulLen)
{
    unsigned long key;
    u32 ret;
    u32 mod;
    u32 len;
    MAILBOX_MSG_HAED_STRU stBuffer = {0};
    MAILBOX_RINGBUFF_STRU* pstComPsUpMail;
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        pstComPsUpMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_PS_UP_ADDR;
    }
    else if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        pstComPsUpMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_OM_DOWN_ADDR;
    }
    else
    {
        Mbx_Printf(" input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }
#else
    pstComPsUpMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_PS_UP_ADDR;
#endif
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        local_irq_save(key);
        mod = (u16)(g_stMbxCtrl.ulMsgLen >> 16);
        len = (u16)(g_stMbxCtrl.ulMsgLen & 0x0000ffff);
        local_irq_restore(key);
    }
    else if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        local_irq_save(key);
        mod = (u16)(g_stMbxCtrl.ulOmMsgLen >> 16);
        len = (u16)(g_stMbxCtrl.ulOmMsgLen & 0x0000ffff);
        local_irq_restore(key);
    }
    else
    {
        Mbx_Printf("input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }
#else
    local_irq_save(key);
    mod = (u16)(g_stMbxCtrl.ulMsgLen >> 16);
    len = (u16)(g_stMbxCtrl.ulMsgLen & 0x0000ffff);
    local_irq_restore(key);
#endif

    ret = mbx_IsChnModMatch(enMbxType, mod);
    if(BSP_OK != ret)
    {
        Mbx_Printf("enMbxType(0x%x)  g_stMbxCtrl.ulMsgLen(0x%x).\n",
            enMbxType, g_stMbxCtrl.ulMsgLen);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    if(ulLen != len)
    {
        Mbx_Printf("ulLen(0x%x) != g_stMbxCtrl.ulMsgLen(0x%x).\n",
            ulLen, g_stMbxCtrl.ulMsgLen);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    stBuffer.usMsgSize = (u16)ulLen;  /* for compare with actually length */
    stBuffer.pPayload = pData;

    local_irq_save(key);
    ret = Mbx_NewMsgReadOut(&stBuffer, pstComPsUpMail); /* [false alarm]:fortify */
    local_irq_restore(key);

    if(stBuffer.usMsgSize != (u16)len)
    {
        Mbx_Printf("pBuffer->usMsgSize(0x%x) != g_stMbxCtrl.ulMsgLen(0x%x).\n",
            stBuffer.usMsgSize, g_stMbxCtrl.ulMsgLen);

        ret = ERR_MAILBOX_READ_FAILED;
    }
    else
    {
        ret = BSP_OK;
    }

    /* 读取成功后把长度清零，触发下次读取 */
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        local_irq_save(key);
        g_stMbxCtrl.ulOmMsgLen = 0;
        local_irq_restore(key);
    }
    else if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        local_irq_save(key);
        g_stMbxCtrl.ulMsgLen = 0;
        local_irq_restore(key);
    }
    else
    {
        Mbx_Printf(" input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }
#else
    local_irq_save(key);
    g_stMbxCtrl.ulMsgLen = 0;
    local_irq_restore(key);
#endif
    return ret;
}


/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgRead
 Description     : 邮箱读接口
                   (此接口会唤醒DSP，需要BSP_MailBox_ComMsgSize返回非空时调用)
 param           : enMbxType    邮箱的业务类型
                   pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
                   ulLen        pData缓冲区的size(以字节为单位)
                   enProcType   DSP睡眠时的处理类型
 Return Value    : 0 : 成功
                   其他 : 失败
*****************************************************************************/
unsigned int BSP_MailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType)
{
    unsigned long key;
    u32 ret;
    u16 mod;
    u16 len;
    u32 ulChn;
    MAILBOX_INT_TYPE_E enType;

    if((BSP_NULL == pData) || (0 == ulLen) || (enMbxType >= EN_MAILBOX_SERVICE_BUTT))
    {
        Mbx_Printf(" %p,%d,%d.\n", pData, ulLen, enMbxType);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    /* 记录发起请求的时间信息 */
    Mbx_MntnReadStart(enMbxType);

    if(!(g_stMbxCtrl.bMbxInit))
    {
        g_stMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ERR_MAILBOX_NOT_INIT;
    }

    ret = BSP_Mailbox_ForbidDspSleep(enProcType);
    if(BSP_OK != ret)
    {
        Mbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
        return ret;
    }

    ret = Mbx_MsgRead(enMbxType, pData, ulLen);
	/*lint -save -e737*/
    Mbx_Trace(pData,ulLen);
	/*lint -restore*/
    /* 更新g_stMbxCtrl.ulPsMsgLen */
    Mbx_ComPsPreProc();

    BSP_Mailbox_AllowDspSleep();

#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    if((EN_MAILBOX_SERVICE_1X_RL == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        local_irq_save(key);
        mod = (u16)(g_stMbxCtrl.ulMsgLen >> 16);
        len = (u16)(g_stMbxCtrl.ulMsgLen & 0x0000ffff);
        local_irq_restore(key);
    }
    else if((EN_MAILBOX_SERVICE_1X_OM == enMbxType) || (EN_MAILBOX_SERVICE_HRPD_OM == enMbxType))
    {
        local_irq_save(key);
        mod = (u16)(g_stMbxCtrl.ulOmMsgLen >> 16);
        len = (u16)(g_stMbxCtrl.ulOmMsgLen & 0x0000ffff);
        local_irq_restore(key);
    }
    else
    {
        Mbx_Printf("input error mode.\n");
        return ERR_MAILBOX_PARAM_INCORRECT;
    }
#else
    local_irq_save(key);
    mod = (u16)(g_stMbxCtrl.ulMsgLen >> 16);
    len = (u16)(g_stMbxCtrl.ulMsgLen & 0x0000ffff);
    local_irq_restore(key);
#endif
    if(0 != len)
    {
        ulChn = mbx_GetChn(mod);
        if(EN_MAILBOX_SERVICE_BUTT == ulChn)
        {
            /* DSP写入了非法的MOD，保存现场并重启 */
            Mbx_SystemError((u32)DRV_ERRNO_MBX_DL_MOD, g_stMbxCtrl.ulMsgLen, (u32)mod, (u32)len); /* [false alarm]:fortify */
            return ret;
        }

        if(((u16)MBX_ADDRESSER_LTE_PHY_RL == mod) || ((u16)MBX_ADDRESSER_TDS_PHY_RL == mod)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        || ((u16)MBX_ADDRESSER_1X_PHY_RL == mod)
        || ((u16)MBX_ADDRESSER_HRPD_PHY_RL == mod)
#endif
        )
        {
            g_stMbxMntn.stNumber.ulPsComPsNotifyNum++;

            g_stMbxMntn.stCallback.ulSlice[g_stMbxMntn.stCallback.ulPtr] = bsp_get_slice_value();
            g_stMbxMntn.stCallback.ulPtr = (g_stMbxMntn.stCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;
        }
        else if(((u16)MBX_ADDRESSER_LTE_PHY_RCM == mod) || ((u16)MBX_ADDRESSER_TDS_PHY_RCM == mod))
        {
            g_stMbxMntn.stNumber.ulPsComRcmNotifyNum++;
            g_stMbxMntn.stRcmCallback.ulSlice[g_stMbxMntn.stRcmCallback.ulPtr] = bsp_get_slice_value();
            g_stMbxMntn.stRcmCallback.ulPtr = (g_stMbxMntn.stRcmCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;
        }
        else if((u16)MBX_ADDRESSER_RTT_AGENT == mod)
        {
            g_stMbxMntn.stNumber.ulPsComRttAgentNotifyNum++;
            g_stMbxMntn.stRttAgentCallback.ulSlice[g_stMbxMntn.stRttAgentCallback.ulPtr] = bsp_get_slice_value();
            g_stMbxMntn.stRttAgentCallback.ulPtr = (g_stMbxMntn.stRttAgentCallback.ulPtr + 1) % MAILBOX_MNTN_NUMBER;
        }
        else
        {
            g_stMbxMntn.stNumber.ulPsComMspNotifyNum++;
        }

        if(g_astMbxChnTbl[ulChn].pFnCallBack)
        {
            enType = g_stMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
            g_astMbxChnTbl[ulChn].pFnCallBack(enType);
        }
    }

    return ret;
}

void Mbx_CallBackProc(void)
{
    MAILBOX_INT_TYPE_E enType;
    u32 ulChn;
    u16 mod;
    u16 len;
    unsigned long key;

    local_irq_save(key);
    mod = (u16)(g_stMbxCtrl.ulMsgLen >> 16);
    len = (u16)(g_stMbxCtrl.ulMsgLen & 0x0000ffff);
    local_irq_restore(key);

    /* 子帧中断或有PS原语则回调PS */
    if((g_stMbxCtrl.bIsSubFrameInt)
        || ((0 != len) && (((u16)MBX_ADDRESSER_LTE_PHY_RL == mod) || ((u16)MBX_ADDRESSER_TDS_PHY_RL == mod)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        || ((u16)MBX_ADDRESSER_1X_PHY_RL == mod)
        || ((u16)MBX_ADDRESSER_HRPD_PHY_RL == mod)
#endif
      )))
    {
        if(g_astMbxChnTbl[EN_MAILBOX_SERVICE_LTE_PS].pFnCallBack)
        {
            g_stMbxMntn.stNumber.ulPsComPsNotifyNum++;

            g_stMbxMntn.stCallback.ulSlice[g_stMbxMntn.stCallback.ulPtr] = bsp_get_slice_value();
            g_stMbxMntn.stCallback.ulPtr = (g_stMbxMntn.stCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;

            enType = g_stMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_LTE_PS].pFnCallBack(enType);
        }
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        else if(g_astMbxChnTbl[EN_MAILBOX_SERVICE_1X_RL].pFnCallBack)
        {
            g_stMbxMntn.stNumber.ulPsComPsNotifyNum++;

            g_stMbxMntn.stCallback.ulSlice[g_stMbxMntn.stCallback.ulPtr] = bsp_get_slice_value();
            g_stMbxMntn.stCallback.ulPtr = (g_stMbxMntn.stCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;

            enType = g_stMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
            g_astMbxChnTbl[EN_MAILBOX_SERVICE_1X_RL].pFnCallBack(enType);
        }
#endif
    }

    /* PS原语已经在上面回调，此处还要判断是否其他的原语 */
    if((0 != len) && ((u16)MBX_ADDRESSER_LTE_PHY_RL != mod) && ((u16)MBX_ADDRESSER_TDS_PHY_RL != mod))
    {
        ulChn = mbx_GetChn(mod);
        if(EN_MAILBOX_SERVICE_BUTT == ulChn)
        {
            /* DSP写入了非法的MOD，保存现场并重启 */
            Mbx_SystemError((u32)DRV_ERRNO_MBX_DL_MOD, g_stMbxCtrl.ulMsgLen, (u32)mod, (u32)len); /* [false alarm]:fortify */
            return ;
        }

        if(g_astMbxChnTbl[ulChn].pFnCallBack)
        {
            if(((u16)MBX_ADDRESSER_LTE_PHY_RCM == mod)||((u16)MBX_ADDRESSER_TDS_PHY_RCM == mod))
            {
                g_stMbxMntn.stNumber.ulPsComRcmNotifyNum++;
                g_stMbxMntn.stRcmCallback.ulSlice[g_stMbxMntn.stRcmCallback.ulPtr] = bsp_get_slice_value();
                g_stMbxMntn.stRcmCallback.ulPtr = (g_stMbxMntn.stRcmCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;
            }
            else if((u16)MBX_ADDRESSER_RTT_AGENT == mod)
            {
                g_stMbxMntn.stNumber.ulPsComRttAgentNotifyNum++;
                g_stMbxMntn.stRttAgentCallback.ulSlice[g_stMbxMntn.stRttAgentCallback.ulPtr] = bsp_get_slice_value();
                g_stMbxMntn.stRttAgentCallback.ulPtr = (g_stMbxMntn.stRttAgentCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;
            }
            else
            {
                g_stMbxMntn.stNumber.ulPsComMspNotifyNum++;
            }

            enType = g_stMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
            g_astMbxChnTbl[ulChn].pFnCallBack(enType);
        }
    }

    return;
}

/*****************************************************************************
 Prototype       : Mbx_ComPsIntProc
 Description     : PS邮箱中断处理函数
                   (如果DSP写邮箱后通过浮动中断通知ARM，DSP应保证在ARM未读走数据前不休眠)
 param           : None
 Return Value    : None
*****************************************************************************/
void Mbx_ComPsIntProc(void)
{
    g_stMbxMntn.stNumber.ulComPsIntNum++;

    if(!(g_stMbxCtrl.bMbxInit))
    {
        g_stMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ;
    }

    /* 记录时间，定位中断丢失 */
    g_stMbxMntn.stIntInfo.ulSlice[g_stMbxMntn.stIntInfo.ulPtr] = bsp_get_slice_value();
    g_stMbxMntn.stIntInfo.ulPtr = (g_stMbxMntn.stIntInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;

    Mbx_ForbidDspSleep();

    /* 更新当前原语长度 */
    Mbx_ComPsPreProc();

    Mbx_AllowDspSleep();

    Mbx_CallBackProc();

    return ;
}

/*****************************************************************************
 Prototype       : BSP_MailBox_IsDspSleep
 Description     : DSP是否睡眠
 param           : None
 Return Value    : 0 --- 未睡眠; 1 --- 睡眠
*****************************************************************************/
u32 BSP_MailBox_IsDspSleep(void)
{
    /* DSP未睡眠 */
    if((NULL != g_stMbxCtrl.pfnGetDspStatusProc) && (BSP_FALSE == g_stMbxCtrl.pfnGetDspStatusProc()))
    {
        return BSP_FALSE;
    }

    return BSP_TRUE;
}
/*****************************************************************************
 Prototype       : BSP_MailBox_Rcm_CallBackReg
 Description     : Rcm 事件回调注册接口
 param           : None
 Return Value    :
*****************************************************************************/
void BSP_MailBox_Rcm_CallBackReg(BSP_MBX_RCM_CALLBACK_FUNC pFunc)
{
    g_stMbxCtrl.pfnRcmNotifyProc = pFunc;
}
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
void Mbx_ComOmPreProc();
void Mbx_MntnRead(void* pData, MAILBOX_SERVICE_TYPE_E enMbxType)
{
    MAILBOX_MNTN_CNF_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    if((EN_MAILBOX_SERVICE_LTE_PS == enMbxType)
     ||(EN_MAILBOX_SERVICE_TDS_PS == enMbxType)
     ||(EN_MAILBOX_SERVICE_1X_RL == enMbxType)
     ||(EN_MAILBOX_SERVICE_HRPD_RL == enMbxType))
    {
        pstCnf = &(g_stMbxMntn.stCnfInfo.astPsCnf[g_stMbxMntn.stCnfInfo.ulPsPtr]);

        pluPtr = &(g_stMbxMntn.stCnfInfo.ulPsPtr);
    }
    else if ( (EN_MAILBOX_SERVICE_LTE_OM == enMbxType)
            ||(EN_MAILBOX_SERVICE_1X_OM == enMbxType)
            ||(EN_MAILBOX_SERVICE_HRPD_OM == enMbxType) )
    {
        pstCnf = &(g_stMbxMntn.stCnfInfo.astOmCnf[g_stMbxMntn.stCnfInfo.ulOmPtr]);

        pluPtr = &(g_stMbxMntn.stCnfInfo.ulOmPtr);
    }
    else
    {
        pstCnf = &(g_stMbxMntn.stCnfInfo.astCbtCnf[g_stMbxMntn.stCnfInfo.ulCbtPtr]);

        pluPtr = &(g_stMbxMntn.stCnfInfo.ulCbtPtr);
    }

    pstCnf->ulMsgId = *(u32*)pData;
    pstCnf->ulSlice = bsp_get_slice_value();

    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;
}



/*****************************************************************************
 Prototype       : Mailbox_OmMsgRead
 Description     : Om原语读接口
                   (此接口内部调用)
 param           : pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
                   ulLen        pData缓冲区的size(以字节为单位)
 Return Value    : 0 : 成功
                   其他 : 失败
*****************************************************************************/
u32 Mailbox_OmMsgRead(void* pData, u32 ulLen)
{
    unsigned long key;
    u32 ret;
    u32 i;
    MAILBOX_MSG_HAED_STRU stBuffer = {0};
    MAILBOX_RINGBUFF_STRU* pstComOmDownMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_OM_DOWN_ADDR;

    if(ulLen != g_stMbxCtrl.ulOmMsgLen)
    {
        Mbx_Printf(" ulLen(%d) != g_stMbxCtrl.ulOmMsgLen(%d).\n",
            ulLen, g_stMbxCtrl.ulOmMsgLen);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    stBuffer.usMsgSize = (u16)ulLen;  /* for compare with actually length */
    stBuffer.pPayload = pData;

    local_irq_save(key);
    ret = Mbx_NewMsgReadOut(&stBuffer, pstComOmDownMail);
    local_irq_restore(key);

    if(stBuffer.usMsgSize != g_stMbxCtrl.ulOmMsgLen)
    {
        Mbx_Printf("pBuffer->usMsgSize(%d) != g_stMbxCtrl.ulOmMsgLen(%d).\n",
            stBuffer.usMsgSize, g_stMbxCtrl.ulOmMsgLen);

        ret = ERR_MAILBOX_READ_FAILED;
    }
    else if(( MBX_ADDRESSER_1X_PHY_OM != stBuffer.usDstMod ) || ( MBX_ADDRESSER_HRPD_PHY_OM != stBuffer.usDstMod ))
    {
        Mbx_Printf("pBuffer->usDstMod %d.\n",
            stBuffer.usDstMod);

        ret = ERR_MAILBOX_READ_FAILED;
    }
    else
    {
        g_stMbxMntn.stNumber.ulOmComOmRdOKNum++;

        ret = BSP_OK;
    }

    Mbx_MntnRead(pData, EN_MAILBOX_SERVICE_LTE_OM);

    /* 读取成功后把长度清零，触发下次读取 */
    local_irq_save(key);
    g_stMbxCtrl.ulOmMsgLen = 0;
    local_irq_restore(key);

    /* 更新g_stMbxCtrl.ulOmMsgLen */
    Mbx_ComOmPreProc();

    return ret;
}

/*****************************************************************************
 Prototype       : Mbx_ComOmPreProc
IPC_INT_DSP_PS_MAC_MBX Description     : PS邮箱的预处理函数(主要作用是更新PS/
CTBT消息长度信息)
                   1. 邮箱内有PS消息，则更新PS消息长度
                   2. 邮箱内有CT/BT消息，则更新PS消息长度
                   3. 可能在中断中调用，不能打印和malloc
                   4. DSP保证邮箱中的原语未读走时不睡眠
 param           : None
 Return Value    : void
*****************************************************************************/
void Mbx_ComOmPreProc()
{
    unsigned long key;
    MAILBOX_RINGBUFF_STRU* pstComOmUpMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_OM_DOWN_ADDR;
    MAILBOX_MSG_HAED_STRU *pstMsgHead;
    u32 ulUpWrPtr = 0;

    /* 如果当前原语长度不为0，表示还未读走，不需要更新 */
    if( 0 != g_stMbxCtrl.ulOmMsgLen )
    {
        return ;
    }

    local_irq_save(key);


    ulUpWrPtr = pstComOmUpMail->ulRbufWrPtr;

    /* 如果写指针非法，立即重启 */
    if(ulUpWrPtr > pstComOmUpMail->ulRbufSize)
    {
        local_irq_restore(key);
        systemError(BSP_MODU_MBX, (int)ulUpWrPtr, (int)pstComOmUpMail->ulRbufRdPtr, (char*)NULL, 0);
        return;
    }

    if(pstComOmUpMail->ulRbufRdPtr == ulUpWrPtr)
    {
        g_stMbxCtrl.ulOmMsgLen = 0;
    }
    else
    {
        pstMsgHead = (MAILBOX_MSG_HAED_STRU*) \
            (pstComOmUpMail->ulRbufRdPtr + pstComOmUpMail->pucRbufAddr + MAILBOX_ADDR_OFFSET);
         g_stMbxCtrl.ulOmMsgLen = (u32)(*(u32*)pstMsgHead);    /* 高16位记录mod，低16位记录长度 */  /*lint !e740*/
    }

    local_irq_restore(key);

    return ;
}


#endif


#ifdef __cplusplus
#if __cplusplus
}

#endif
#endif




/* end C file */

