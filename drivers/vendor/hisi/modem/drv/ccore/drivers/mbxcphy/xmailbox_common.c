/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : mailbox_common.c
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
/*lint --e{801}*/ /*PCLINT: goto's warning 801 is inevitable*/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "xmailbox.h"
#include <mdrv_timer.h>
#include "bsp_hardtimer.h"
#include "bsp_ipc.h"
#include "mdrv_dsp.h"

#define MBX_PRINT_TIMES     10

/* 邮箱模块控制信息 */
xMAILBOX_MAINCTRL_STRU   g_stxMbxCtrl;
xMAILBOX_MNTN_STRU       g_stxMbxMntn;
xMAILBOX_ADDR_SHARE_STRU g_stxMbxShareAddr;
/*lint -save -e656*/
xMAILBOX_CHANNEL_TABLE_STRU g_astxMbxChnTbl[EN_MAILBOX_SERVICE_TOTAL_BUTT-EN_MAILBOX_SERVICE_BUTT] =
{
	/* cdma部分 */
	{EN_MAILBOX_SERVICE_1X_RL,       MBX_ADDRESSER_1X_PHY_RL,       0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
	{EN_MAILBOX_SERVICE_1X_OM,       MBX_ADDRESSER_1X_PHY_OM,       0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_OM_MBX },
	{EN_MAILBOX_SERVICE_1X_CT,       MBX_ADDRESSER_1X_PHY_CT,       0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
	{EN_MAILBOX_SERVICE_1X_BT,       MBX_ADDRESSER_1X_PHY_BT,       0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
	{EN_MAILBOX_SERVICE_1X_HS_DIAG,  MBX_ADDRESSER_1X_PHY_HS_DIAG,  0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_OM_MBX },
    
    {EN_MAILBOX_SERVICE_HRPD_RL,     MBX_ADDRESSER_HRPD_PHY_RL,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
    {EN_MAILBOX_SERVICE_HRPD_OM,     MBX_ADDRESSER_HRPD_PHY_OM,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_OM_MBX },
    {EN_MAILBOX_SERVICE_HRPD_CT,     MBX_ADDRESSER_HRPD_PHY_CT,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
    {EN_MAILBOX_SERVICE_HRPD_BT,     MBX_ADDRESSER_HRPD_PHY_BT,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
    {EN_MAILBOX_SERVICE_HRPD_HS_DIAG,MBX_ADDRESSER_HRPD_PHY_HS_DIAG,0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_OM_MBX },

};
/*lint -restore*/

u32 xmbx_IsChnModMatch(u32 ulChn, u32 ulMod)
{
    xMAILBOX_CHANNEL_TABLE_STRU* pMbxTbl;

    pMbxTbl = xMbx_get_tbl(ulChn);
    if (xMbx_invalid_type(ulChn)) {
        xMbx_Printf("invalid Channel %d.\n", ulChn);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    switch(ulChn)
    {
        case EN_MAILBOX_SERVICE_1X_RL:
        case EN_MAILBOX_SERVICE_1X_OM:
        {
            if((MBX_ADDRESSER_1X_PHY_RL == ulMod)||(MBX_ADDRESSER_1X_PHY_OM == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        case EN_MAILBOX_SERVICE_1X_CT:
        case EN_MAILBOX_SERVICE_1X_BT:
        {
            if((MBX_ADDRESSER_1X_PHY_CT == ulMod)||(MBX_ADDRESSER_1X_PHY_BT == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        case EN_MAILBOX_SERVICE_HRPD_RL:
        case EN_MAILBOX_SERVICE_HRPD_OM:
        {
            if((MBX_ADDRESSER_HRPD_PHY_RL == ulMod)||(MBX_ADDRESSER_HRPD_PHY_OM == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        case EN_MAILBOX_SERVICE_HRPD_CT:
        case EN_MAILBOX_SERVICE_HRPD_BT:
        {
            if((MBX_ADDRESSER_HRPD_PHY_CT == ulMod)||(MBX_ADDRESSER_HRPD_PHY_BT == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        default :
        {
            pMbxTbl = xMbx_get_tbl(ulChn);
            if (pMbxTbl->ulModule == ulMod)
            {
                return BSP_OK;
            }
        }
    }
    return ERR_MAILBOX_PARAM_INCORRECT;
}

/*lint -save -e656 -e665*/
u32 xmbx_GetChn(u32 ulMod)
{
    u32 i;
    xMAILBOX_CHANNEL_TABLE_STRU* pMbxTbl;

    if (xMbx_invalid_module(ulMod)) {
        return (u32)EN_MAILBOX_SERVICE_TOTAL_BUTT;
    }
        
    for(i = 0; i < EN_MAILBOX_SERVICE_TOTAL_BUTT - EN_MAILBOX_SERVICE_BUTT; i++)
    {
        pMbxTbl = xMbx_get_tbl(i + EN_MAILBOX_SERVICE_BUTT);
        if(ulMod == pMbxTbl->ulModule)
        {
            return pMbxTbl->ulMbxChn;
        }
    }

    return (u32)EN_MAILBOX_SERVICE_TOTAL_BUTT;
}
/*lint -restore*/
/*****************************************************************************
 函 数 名  : xmbx_mntnaddr
 功能描述  : 邮箱地址相关信息
*****************************************************************************/
void xmbx_mntnaddr(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("地址信息\n");
    xMbx_Printf("CPHY PS下行邮箱地址                : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr);
    xMbx_Printf("CPHY PS上行邮箱地址                : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxHpaUpAddr);
    xMbx_Printf("CPHY OM下行邮箱地址                : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxOmDownAddr);
    xMbx_Printf("CPHY DSP握手地址                   : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxLoadMemAddr);
    xMbx_Printf("CPHY 模式设置地址                  : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxWorkModeAddr);
    xMbx_Printf("CPHY pCphyMntnInfoAddr            : %p.\n", (void*)g_stxMbxShareAddr.pCphyMntnInfoAddr);
    xMbx_Printf("CPHY pCphyWakeupAddr               : %p.\n", (void*)g_stxMbxShareAddr.pCphyWakeupAddr);

    xMbx_Printf("***************************************************************\n");
}

/*****************************************************************************
 函 数 名  : xmbx_mntnabnormal
 功能描述  : 邮箱异常信息
*****************************************************************************/
void xmbx_mntnabnormal(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("异常信息\n");
    xMbx_Printf("PS邮箱连续上报的CT/BT消息ID   : %d\n", g_stxMbxMntn.stAbnormal.ulMulCtBtMsg);
    xMbx_Printf("PS邮箱上报的错误的模块ID      : %d\n", g_stxMbxMntn.stAbnormal.ucComPsType);
    xMbx_Printf("请求处理的最大超时时长        : %d\n", g_stxMbxMntn.stAbnormal.ulLongestReq);
    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : xmbx_mntnother
 功能描述  : 邮箱其他可维可测信息
*****************************************************************************/
void xmbx_mntnother(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("其他信息\n");
    xMbx_Printf("PS邮箱是否子帧中断  : %s\n", (g_stxMbxCtrl.bIsSubFrameInt)?"yes":"no");
    xMbx_Printf("PS邮箱当前消息长度  : %d\n", g_stxMbxCtrl.ulMsgLen);

    xMbx_Printf("最后十次低功耗唤醒时间信息\n");

    ulStart = (g_stxMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice1)
        {
            xMbx_Printf("| slice1(0x%08x) - slice2(0x%08x) | = (0x%08x)   slice3 : 0x%08x\n",
                g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice1,
                g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice2,
                (g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice2 - g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice1),
                g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice3);
        }
    }

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : xmbx_mntnnum
 功能描述  : 邮箱次数纪录相关信息
*****************************************************************************/
void xmbx_mntnnum(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("计数信息\n");
    xMbx_Printf("PS邮箱中断次数           : %d\n", g_stxMbxMntn.stNumber.ulComPsIntNum);
    xMbx_Printf("专有邮箱中断次数         : %d\n", g_stxMbxMntn.stNumber.ulSpIntNum);

    xMbx_Printf("PS邮箱写请求次数         : %d\n", g_stxMbxMntn.stNumber.ulPsComReqNum);
    xMbx_Printf("PS邮箱PS写请求次数       : %d\n", g_stxMbxMntn.stNumber.ulPsComPsReqNum);
    xMbx_Printf("PS邮箱MSP写请求次数      : %d\n", g_stxMbxMntn.stNumber.ulPsComMspReqNum);
    xMbx_Printf("PS邮箱RttAgent写请求次数 : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentReqNum);
    xMbx_Printf("OM邮箱写请求次数         : %d\n", g_stxMbxMntn.stNumber.ulOmComReqNum);

    xMbx_Printf("PS邮箱PS读取次数         : %d\n", g_stxMbxMntn.stNumber.ulPsComPsRdNum);
    xMbx_Printf("PS读取成功次数           : %d\n", g_stxMbxMntn.stNumber.ulPsComPsRdOKNum);
    xMbx_Printf("MSP读取次数              : %d\n", g_stxMbxMntn.stNumber.ulPsComMspRdNum);
    xMbx_Printf("MSP读取成功次数          : %d\n", g_stxMbxMntn.stNumber.ulPsComMspRdOKNum);
    xMbx_Printf("RCM读取次数              : %d\n", g_stxMbxMntn.stNumber.ulPsComRcmRdNum);
    xMbx_Printf("RCM读取成功次数          : %d\n", g_stxMbxMntn.stNumber.ulPsComRcmRdOKNum);
    xMbx_Printf("RttAgent读取次数         : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentRdNum);
    xMbx_Printf("RttAgent读取成功次数     : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentRdOKNum);

    xMbx_Printf("PS邮箱PS回调次数         : %d\n", g_stxMbxMntn.stNumber.ulPsComPsNotifyNum);
    xMbx_Printf("PS邮箱MSP回调次数        : %d\n", g_stxMbxMntn.stNumber.ulPsComMspNotifyNum);
    xMbx_Printf("PS邮箱RCM回调次数        : %d\n", g_stxMbxMntn.stNumber.ulPsComRcmNotifyNum);
    xMbx_Printf("PS邮箱RttAgent回调次数   : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentNotifyNum);

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : xmbx_mntnmailfull
 功能描述  : 邮箱满写入丢失信息
*****************************************************************************/
void xmbx_mntnmailfull(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    ulStart = g_stxMbxMntn.stMailFull.ulPtr;

    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("邮箱满信息\n");
    xMbx_Printf("邮箱满次数          : %d\n", g_stxMbxMntn.stMailFull.ulFullNum);

    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stMailFull.astFullInfo[j].ulSlice)
        {
            xMbx_Printf("类型 : %d   消息ID : 0x%08x   时间 : 0x%08x\n",
                g_stxMbxMntn.stMailFull.astFullInfo[j].ulModId
                , g_stxMbxMntn.stMailFull.astFullInfo[j].ulMsgId
                , g_stxMbxMntn.stMailFull.astFullInfo[j].ulSlice);
        }
    }

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : xmbx_mntnreqinfo
 功能描述  : 邮箱写请求信息
*****************************************************************************/
void xmbx_mntnreqinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("邮箱写请求信息\n");

    ulStart = (g_stxMbxMntn.stReqInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stReqInfo.astReq[j].ulSliceEnd)
        {
            xMbx_Printf("类型 : %d   消息ID : 0x%08x   请求时间 : 0x%08x   写入时间 : 0x%08x\n",
                g_stxMbxMntn.stReqInfo.astReq[j].ulModId, g_stxMbxMntn.stReqInfo.astReq[j].ulMsgId,
                g_stxMbxMntn.stReqInfo.astReq[j].ulSliceStart, g_stxMbxMntn.stReqInfo.astReq[j].ulSliceEnd);
        }
    }

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : xmbx_mntncnfinfo
 功能描述  : 邮箱读请求信息
*****************************************************************************/
void xmbx_mntncnfinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    xMbx_Printf("***************************************************************\n");

    xMbx_Printf("最后十次浮动中断的信息\n");

    ulStart = (g_stxMbxMntn.stIntInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stIntInfo.ulSlice[j])
        {
            xMbx_Printf("interrupt slice : 0x%08x\n", g_stxMbxMntn.stIntInfo.ulSlice[j]);
        }
    }

    xMbx_Printf("最后十次原语读取的信息\n");

    ulStart = (g_stxMbxMntn.stReadInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stReadInfo.astRead[j].ulSlice)
        {
            xMbx_Printf("app read , src 0x%x, slice 0x%08x\n",
                g_stxMbxMntn.stReadInfo.astRead[j].ulSrc, g_stxMbxMntn.stReadInfo.astRead[j].ulSlice);
        }
    }

    ulStart = (g_stxMbxMntn.stCnfInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    xMbx_Printf("邮箱PS最后10条读请求信息\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stCnfInfo.astPsCnf[j].ulSlice)
        {
            xMbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astPsCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astPsCnf[j].ulSlice);
        }
    }

    ulStart = (g_stxMbxMntn.stCnfInfo.ulRcmPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;
    xMbx_Printf("邮箱RCM最后10条读请求信息\n");
    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stxMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice)
        {
            xMbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astRcmCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice);
        }
    }
    ulStart = (g_stxMbxMntn.stCnfInfo.ulCbtPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    xMbx_Printf("邮箱CT/BT最后10条读请求信息\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice)
        {
            xMbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astCbtCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice);
        }
    }

    xMbx_Printf("邮箱Rtt Agent最后10条读请求信息\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice)
        {
            xMbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astRttAgentCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice);
        }
    }

    xMbx_Printf("***************************************************************\n");
}

void xmbx_mntnSleepCbInfo(void)
{
    u32 i =0,j=0;
    for(i=0; i<MAILBOX_MNTN_NUMBER; i++)
    {
        j = (g_stxMbxMntn.stSleepCbInfo.ulPtr+i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)
        {
            xMbx_Printf("Callback Type : %d, Is Mbx wakeup :%d, end time(0x%08x) - start time(0x%08x) = %d  MS\n",
                g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].cbType,g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulWakeup,\
                g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd,g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart,\
                ((g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd-g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)/32));
        }
    }
}

void xmbx_mntnDirectWriteInfo(void)
{
    u32 i = 0 ,k = 0;
    u32 j = g_stxMbxMntn.stDirectInfo.ulPtr % MAILBOX_MNTN_NUMBER;
    xMbx_Printf("*************Direct Num 0x%x****************\n",g_stxMbxMntn.stDirectInfo.ulPtr);
    xMbx_Printf("*************print lastest *****************\n");
    for(i = 0;i < MAILBOX_MNTN_NUMBER;i++)
    {
        k = (j+1)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stxMbxMntn.stDirectInfo.ulSlice[k])
        {
            xMbx_Printf("第 %d 次，时间戳为 :0x%x\n",i,g_stxMbxMntn.stDirectInfo.ulSlice[k]);
        }
    }
}
/*****************************************************************************
 函 数 名  : xmbx_mntnerrorcode
 功能描述  : 邮箱错误码相关信息
*****************************************************************************/
void xmbx_mntnerrorcode(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("错误码信息\n");
    xMbx_Printf("1  : 邮箱未初始化.\n");
    xMbx_Printf("2  : 输入参数错误.\n");
    xMbx_Printf("3  : 邮箱满.\n");
    xMbx_Printf("4  : 超时.\n");
    xMbx_Printf("5  : 专有邮箱数据覆盖.\n");
    xMbx_Printf("6  : 写失败.\n");
    xMbx_Printf("7  : 读失败.\n");
    xMbx_Printf("8  : 读信息为空.\n");
    xMbx_Printf("9  : DSP睡眠.\n");
    xMbx_Printf("10 : 其他.\n");
    xMbx_Printf("***************************************************************\n");
}


void xmbx_debug(BSP_BOOL bDebug)
{
    g_stxMbxMntn.bdbg = bDebug;
}

/*****************************************************************************
 函 数 名  : xmailbox_help
 功能描述  : 邮箱打印帮助
*****************************************************************************/
void xmailbox_help(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("邮箱地址相关信息                xmbx_mntnaddr\n");
    xMbx_Printf("邮箱次数纪录相关信息            xmbx_mntnnum\n");
    xMbx_Printf("邮箱写请求信息                  xmbx_mntnreqinfo\n");
    xMbx_Printf("邮箱读请求信息                  xmbx_mntncnfinfo\n");
    xMbx_Printf("邮箱满写入丢失信息              xmbx_mntnmailfull\n");
    xMbx_Printf("邮箱异常信息                    xmbx_mntnabnormal\n");
    xMbx_Printf("邮箱其他可维可测信息            xmbx_mntnother\n");
    xMbx_Printf("邮箱操作失败错误码信息          xmbx_mntnerrorcode\n");
    xMbx_Printf("邮箱打印信息开关                xmbx_debug 1/0\n");
    xMbx_Printf("邮箱SLEEP回调信息               xmbx_mntnSleepCbInfo\n");
    xMbx_Printf("邮箱直接写信息                  xmbx_mntnDirectWriteInfo\n");
    xMbx_Printf("***************************************************************\n");
}


/*lint -save -e545 -e813*/
/*****************************************************************************
 Prototype       : xMbx_BbeIpcProc
 Description     : 邮箱的异常处理
                   BBE出现异常时，保存异常信息到AXI memory中，然后通过IPC中断
                   通知邮箱模块，由邮箱模块记录异常信息，并调用异常重启接口
 Return Value    : NONE
*****************************************************************************/
void xMbx_BbeIpcProc(void)
{
    u8  ucData[MBX_SYSTEM_ERROR_SIZE] = {0};     /* 4K缓存，前32字节存DSP信息 */
    u32 *pAddr;
    u16 usMode;

    usMode = *(u16*)g_stxMbxShareAddr.pCphyMntnInfoAddr ;

    /* 0表示PS邮箱满 */
    if(0 == usMode)
    {
        /* 前4个字保存传入的参数 */
        pAddr = (u32*)ucData;

        *(pAddr++) = DRV_ERRNO_XMBX_DSP_IPC;
        *(pAddr++) = 0;
        *(pAddr++) = 0;
        *(pAddr++) = 0;

        /* 保存DSP的异常信息 */
        xMbx_Memcpy((u8*)pAddr, (u8*)g_stxMbxShareAddr.pCphyMntnInfoAddr, SRAM_CDSP_MNTN_SIZE); /* [false alarm]:fortify */

        /* 从第512字节开始保存邮箱驱动的异常信息 */
        xMbx_DumpSave(ucData+MBX_ERROR_RESERVE_SIZE, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

        system_error(DRV_ERRNO_XMBX_DSP_IPC, 0, 0, (char*)ucData, MBX_SYSTEM_ERROR_SIZE);
    }
}
/*lint -restore*/

/*****************************************************************************
 函 数 名  : bsp_xmailbox_init
 功能描述  : 邮箱模块初始化
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
void bsp_xmailbox_init(void)
{
    s32 ret;
    SRAM_SMALL_SECTIONS * pSram_Small_section;

    xMbx_Memset(&g_stxMbxCtrl, 0, sizeof(xMAILBOX_MAINCTRL_STRU));

    xMbx_Memset((void*)(&g_stxMbxMntn), 0, sizeof(xMAILBOX_MNTN_STRU));

    g_stxMbxCtrl.bDspWakeFlag = BSP_FALSE;

    osl_sem_init(0, &g_stxMbxCtrl.semDspWakeup);
    osl_sem_init(1, &g_stxMbxCtrl.semDspMutex);

    pSram_Small_section = (SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS);
    g_stxMbxShareAddr.pCphyMntnInfoAddr = pSram_Small_section->SRAM_CDSP_MNTN_INFO;
    g_stxMbxShareAddr.pCphyWakeupAddr = (void *)&pSram_Small_section->SRAM_CDSP_DRV;

    g_stxMbxCtrl.pulAxiAddr = (u32*)g_stxMbxShareAddr.pCphyWakeupAddr;
    g_stxMbxCtrl.lAxiCnt = 0;

    ret = (s32)bsp_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_PS_MBX, (VOIDFUNCPTR)xMbx_ComPsIntProc, 0);
	if(BSP_OK != ret)
	{
        xMbx_Printf("bsp_ipc_int_connect failed.\n");
        return ;
	}

    ret = (s32)bsp_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_PS_MBX);
	if(BSP_OK != ret)
	{
        xMbx_Printf("bsp_ipc_int_enable failed.\n");
        return ;
	}

    ret = (s32)bsp_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_RCM_MBX, (VOIDFUNCPTR)xMbx_ComPsIntProc, 0);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)bsp_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_RCM_MBX);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_enable failed.\n");
        return ;
    }

    /* DSP可维可测IPC中断 */
    ret = (s32)bsp_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_MNTN, (VOIDFUNCPTR)xMbx_BbeIpcProc, 0);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)bsp_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_MNTN);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_enable failed.\n");
        return ;
    }

    g_stxMbxCtrl.bIsSubFrameInt = BSP_FALSE;

    xMbx_Printf("success.\n");
    return;
}





/*****************************************************************************
 函 数 名  : xMbx_SpaceMalloc
 功能描述  : 消息写入空间申请
 输入参数  : MAILBOX_HANDLE_STRU* pMbxHandle,
             u32 ulSizeReq
 输出参数  : 无,
 返 回 值  : 申请成功失败标志

 修改历史      :
 1.	日    期   : 2012年8月23日
	作    者   : honghuiyong(164941)
	修改内容   : 新生成函数
 2.	日    期   : 2014年2月24日
	作    者   : cuijunqiang(64416)
	修改内容   : 修改获取读写指针缓存为局部变量(避免处理过程中DSP更新读指针)
*****************************************************************************/
u32 xMbx_SpaceMalloc(xMAILBOX_RINGBUFF_STRU* pMbxHandle,u32 ulSizeReq)
{
    u32 ulFreeBuffSize;
    u32 wr,rd,size;

    wr   = pMbxHandle->ulRbufWrPtr;
    rd   = pMbxHandle->ulRbufRdPtr;
    size = pMbxHandle->ulRbufSize;

    /* 如果写指针非法，立即重启 */
    if(wr > size)
    {
        xMbx_SystemError((u32)DRV_ERRNO_XMBX_UP_WR, wr, rd, ((__LINE__ << 16)|size));
    }

    if(wr < rd)
    {
        ulFreeBuffSize = (rd - wr);
    }
    else
    {
        ulFreeBuffSize = (size + rd - wr);
    }

    if(ulFreeBuffSize >= (ulSizeReq+4))
    {
        return BSP_OK;
    }
    else
    {
        xMbx_Printf("Mbx_SpaceMalloc failed, ulFreeBuffSize(%d), ulSizeReq(%d), wr(%d), rd(%d), size(%d).\n",
            ulFreeBuffSize, ulSizeReq, wr, rd, size);
        return (u32)BSP_ERROR;
    }
}


void xMbx_MntnMailFull(xMAILBOX_MSG_HAED_STRU* pstMsg)
{
    g_stxMbxMntn.stMailFull.ulFullNum++;

    g_stxMbxMntn.stMailFull.astFullInfo[g_stxMbxMntn.stMailFull.ulPtr].ulModId = (u32)(pstMsg->usDstMod);
    g_stxMbxMntn.stMailFull.astFullInfo[g_stxMbxMntn.stMailFull.ulPtr].ulMsgId = *(u32*)(pstMsg->pPayload);
    g_stxMbxMntn.stMailFull.astFullInfo[g_stxMbxMntn.stMailFull.ulPtr].ulSlice = bsp_get_slice_value();

    g_stxMbxMntn.stMailFull.ulPtr = (g_stxMbxMntn.stMailFull.ulPtr+1)%MAILBOX_MNTN_NUMBER;
}


/*****************************************************************************
 Prototype       : xMbx_RbuffWrite
 Description     : 循环buffer写接口
 param           : pHead        循环buffer的首地址
                   pstMsg       待写入数据指针
 Return Value    : BSP_OK : 成功
                   ERR_MAILBOX_MEMORY_NOTENOUGH : 剩余空间不足
*****************************************************************************/
s32 xMbx_RbuffWrite(xMAILBOX_RINGBUFF_STRU* pHead, xMAILBOX_MSG_HAED_STRU* pstMsg)
{
    u32 ulMsgSize = pstMsg->usMsgSize + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4);
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempPPTR;

    /* 邮箱剩余空间检查 */
    if(BSP_OK != xMbx_SpaceMalloc(pHead,ulMsgSize))
    {
        xMbx_MntnMailFull(pstMsg);
        return ERR_MAILBOX_MEMORY_NOTENOUGH;
    }

    /* 新消息写入 */
    if((ulMsgSize + pHead->ulRbufWrPtr) <= pHead->ulRbufSize)
    {
        xMbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                        (void*)pstMsg,
                        (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));
        xMbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                        (void*)(pstMsg->pPayload),
                        pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pHead->ulRbufSize - pHead->ulRbufWrPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(xMAILBOX_MSG_HAED_STRU) - 4))
        {
            xMbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)pstMsg,
                            ulCpySize0);

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg)+ulCpySize0),
                            ((sizeof(xMAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0));

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + ((sizeof(xMAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0)),
                            (void*)(pstMsg->pPayload),
                            pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            xMbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)(pstMsg),
                            (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                            (void*)(pstMsg->pPayload),
                            (ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)));

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg->pPayload) + (ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4))),
                            ulCpySize1);
        }
    }

    /* 写指针更新,保证四字节对齐 */
    ulTempPPTR = ((pHead->ulRbufWrPtr + ulMsgSize + 3) & (~3));

    if(ulTempPPTR >= pHead->ulRbufSize)
    {
        ulTempPPTR -= pHead->ulRbufSize;
    }

    xMbx_MntnWriteEnd(pHead, pstMsg, ulTempPPTR);

    pHead->ulRbufWrPtr = ulTempPPTR;

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : xMbx_GetNewMsgLen
 功能描述  : 获取新消息长度
 输入参数  : 	MBX_MSG_HAEDER_STRU* pMsg 新消息指针,
 输出参数  : 无,
 返 回 值  : 新消息长度
 本函数调用的函数  :
 调用本函数的函数  :
 访问的全局变量  :
 修改的全局变量  :
 修改的BBP寄存器列表  :

 修改历史      :
 1.	日    期   : 2012年8月23日
	作    者   : honghuiyong(164941)
	修改内容   : 新生成函数

*****************************************************************************/
u32 xMbx_GetNewMsgLen (xMAILBOX_MSG_HAED_STRU* pMsg)
{
    return(u32)(pMsg->usMsgSize);
}


/*****************************************************************************
 函 数 名  : xMbx_NewMsgReadOut
 功能描述  : 执行消息读出操作
 输入参数  : 	xMAILBOX_RINGBUFF_STRU* pMbxHandle,
 输出参数  : 	void* pMsg,
 返 回 值  :  更新后的CPTR指针

 修改历史      :
 1.	日    期   : 2012年8月23日
	作    者   : honghuiyong(164941)
	修改内容   : 新生成函数

*****************************************************************************/
u32 xMbx_NewMsgReadOut(xMAILBOX_MSG_HAED_STRU* pMsg,xMAILBOX_RINGBUFF_STRU* pMbxHandle)
{
    u32 ulMsgSize;
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempCPTR;
    xMAILBOX_MSG_HAED_STRU *pstMsg = NULL;

    pstMsg = (xMAILBOX_MSG_HAED_STRU*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + pMbxHandle->ulRbufRdPtr);
    ulMsgSize = xMbx_GetNewMsgLen(pstMsg) + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4);

    /* user space not enough, return failure, avoid overflow */
    if(pstMsg->usMsgSize > pMsg->usMsgSize)
    {
        pMsg->usMsgSize = pstMsg->usMsgSize;
        goto newmsgreadfailed;
    }

    /* 新消息读出 */
    if((ulMsgSize + pMbxHandle->ulRbufRdPtr) <= pMbxHandle->ulRbufSize)
    {
        xMbx_Memcpy((void*)pMsg,
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

        xMbx_Memcpy((void*)(pMsg->pPayload),
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pMbxHandle->ulRbufSize - pMbxHandle->ulRbufRdPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(xMAILBOX_MSG_HAED_STRU) - 4))
        {
            xMbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    ulCpySize0);

            xMbx_Memcpy((void*)((u32)pMsg + ulCpySize0),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                    (sizeof(xMAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0);

            xMbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0),
                    pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            xMbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

            xMbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                    ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

            xMbx_Memcpy((void*)((u32)(pMsg->pPayload) + ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                    ulCpySize1);
        }
    }

newmsgreadfailed:

    /* 读指针更新,保证四字节对齐 */
    ulTempCPTR = ((pMbxHandle->ulRbufRdPtr + ulMsgSize + 3) & (~3));

    if((ulTempCPTR) >= pMbxHandle->ulRbufSize)
    {
        ulTempCPTR -= pMbxHandle->ulRbufSize;
    }

    xMbx_MntnReadEnd(pMsg->pPayload, (enum __MBX_ADDRESSEE_ID_ENUM__)pMsg->usDstMod, ulTempCPTR, pMbxHandle->ulRbufWrPtr);

    pMbxHandle->ulRbufRdPtr = ulTempCPTR;

    return (ulTempCPTR);
}


/*****************************************************************************
 Prototype       : mdrv_MailBox_GetCdmaStatusReg
 Description     : 获取DSP睡眠状态回调函数注册接口，低功耗模块调用
 param           : pFun             获取DSP睡眠状态处理函数
 Return Value    : BSP_VOID
*****************************************************************************/
void mdrv_MailBox_GetCdmaStatusReg(BSP_xMBX_GET_STATUS_FUNC pFun)
{
    g_stxMbxCtrl.pfnGetDspStatusProc = pFun;
}


/*****************************************************************************
 Prototype       : mdrv_MailBox_CdmaForceAwakeReg
 Description     : DSP强制唤醒回调函数注册接口，低功耗模块调用
 param           : pFun             DSP强制唤醒处理函数
 Return Value    : BSP_VOID
*****************************************************************************/
void mdrv_MailBox_CdmaForceAwakeReg(BSP_xMBX_DSP_AWAKE_FUNC pFun)
{
    g_stxMbxCtrl.pfnDspForceAwakeProc = pFun;
}


/*****************************************************************************
 Prototype       : mdrv_MailBox_CdmaResumeProc
 Description     : DSP唤醒后的邮箱处理接口，低功耗模块调用
 param           : BSP_VOID
 Return Value    : BSP_VOID
*****************************************************************************/
void mdrv_MailBox_CdmaResumeProc(MAILBOX_CALLBACK_TYPE cbType, XMBX_RATMODE_ENUM_U32 enMode)
{
    u32 ulPtr = g_stxMbxMntn.stSleepCbInfo.ulPtr;
    g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].cbType       = cbType;
    if(cbType >= EN_MAILBOX_CALLBACK_DSP_BUTT)
    {
        xMbx_Printf("err parm ! %d \n",cbType);
        cbType = EN_MAILBOX_CALLBACK_DSP_BUTT;
    }
    if(g_stxMbxCtrl.pfnRcmNotifyProc)
    {
        g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulWakeup     = g_stxMbxCtrl.bDspWakeFlag;

        g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceStart = bsp_get_slice_value();
        g_stxMbxCtrl.pfnRcmNotifyProc(cbType);

        g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceEnd   = bsp_get_slice_value();

        ulPtr = g_stxMbxMntn.stSleepCbInfo.ulPtr +1;

        g_stxMbxMntn.stSleepCbInfo.ulPtr = ulPtr%MAILBOX_MNTN_NUMBER;
    }

    /* TODO:需要考虑哪个模式发起的唤醒(bDspWakeFlag要分为 bDspWakeFlag1X/bDspWakeFlagHRPD) */
    /* 只处理邮箱模块发起的唤醒 */
    if(EN_MAILBOX_CALLBACK_DSP_RESUME == cbType)
    {
        if(BSP_TRUE == g_stxMbxCtrl.bDspWakeFlag)
        {
            g_stxMbxMntn.stSleepInfo.astwakeup[g_stxMbxMntn.stSleepInfo.ulPtr].ulSlice2 = bsp_get_slice_value();
            g_stxMbxCtrl.bDspWakeFlag = BSP_FALSE;
            osl_sem_up(&g_stxMbxCtrl.semDspWakeup);
        }
    }
}


/*****************************************************************************
 Prototype       : BSP_xUniMailboxWrite
 Description     : 邮箱的通用写接口(由调用者保证传入的地址的合法性)
                   本接口实现类似memcpy函数的作用
                   接口内部保证DSP的唤醒操作，如果唤醒失败，返回ERR_MAILBOX_TIMEOUT
 Return Value    :
                   BSP_OK
                   ERR_MAILBOX_PARAM_INCORRECT
                   ERR_MAILBOX_TIMEOUT
*****************************************************************************/
unsigned int BSP_xUniMailboxWrite(void *pDst, void *pSrc, unsigned int ulLen)
{
    u32 ulret;

    if((NULL == pDst) || (NULL == pSrc) || (0 == ulLen))
    {
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    ulret = BSP_Mailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP);
    if(ulret)
    {
        return ulret;
    }

    xMbx_Memcpy(pDst, pSrc, ulLen);

    BSP_Mailbox_AllowDspSleep();

    return BSP_OK;
}


/*****************************************************************************
 Prototype       : BSP_xMailboxAbnormalProc
 Description     : 邮箱异常处理
                   协议栈接收消息超时后调用此接口保存邮箱相关信息
                   与协议栈商定，前0.5K保存协议栈信息，后3.5K保存邮箱信息
 Input           : ucData       缓存首地址
 Return Value    : NONE
*****************************************************************************/
void BSP_xMailboxAbnormalProc(unsigned char *ucData)
{
    if(BSP_NULL == ucData)
    {
        return;
    }

    xMbx_Printf("enter.\n");

    xMbx_DumpSave(ucData, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    xMbx_Printf("exit.\n");
}


/*****************************************************************************
 Prototype       : xMbx_DumpSave
 Description     : 邮箱异常重启信息保存接口
                    记录所有的请求信息
                    记录所有的读取请求、读取结果信息
                    记录最后一次DSP IPC中断上报的时间
                    记录唤醒DSP的时间信息
 Input           :  pData 缓冲区起始地址
                    ulSize 缓冲区大小
 Return Value    : NONE
*****************************************************************************/
void xMbx_DumpSave(u8* pData, u32 ulSize)
{
    u32 i,ptr;
    u32 ultmp = 0;

    /* 传入的空间大小最小3.5K */
    if((ulSize < (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE)) || (NULL == pData))
    {
        xMbx_Printf("ulSize %d, pData %p.\n", ulSize, pData);
        return;
    }

    ptr = g_stxMbxMntn.stReqInfo.ulPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/RWpointer/start slice/end slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stReqInfo.astReq[ptr].ulMsgId), 4*sizeof(u32)); /*lint !e420*/ /* [false alarm]:fortify */
        ultmp += 4*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 1600 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stxMbxMntn.stCnfInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stCnfInfo.astPsCnf[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 2400 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stxMbxMntn.stReadInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (read src/slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stReadInfo.astRead[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3200 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    /* 空间有限，只记录最后十次的唤醒信息 */
    ptr = (g_stxMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (req slice/callback slice/proc slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stSleepInfo.astwakeup[ptr]), 3*sizeof(u32));
        ultmp += 3*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3320 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    /* 空间有限，只记录最后十次的IPC时间信息 */
    ptr = (g_stxMbxMntn.stCallback.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (callback timer) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stCallback.ulSlice[ptr]), sizeof(u32));
        ultmp += sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3360 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stNumber), sizeof(g_stxMbxMntn.stNumber));
    ultmp += sizeof(g_stxMbxMntn.stNumber);

    /* ultmp value is 3408 */

    xMbx_Printf("ultmp = %d.\n", ultmp);

    xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stAbnormal), sizeof(g_stxMbxMntn.stAbnormal));
    ultmp += sizeof(g_stxMbxMntn.stAbnormal);

    /* ultmp value is 3424 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    /* 在最后32个字节保存上下行邮箱头信息 */
    if(BSP_OK == BSP_xMailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP,XMBX_MOD_OTHER))
    {
        xMbx_Memcpy(&pData[ulSize-(2*sizeof(xMAILBOX_RINGBUFF_STRU))],
            (BSP_VOID*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr, sizeof(xMAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        xMbx_Memcpy(&pData[ulSize - sizeof(xMAILBOX_RINGBUFF_STRU)],
            (BSP_VOID*)g_stxMbxShareAddr.ulCphyMbxHpaUpAddr, sizeof(xMAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        BSP_xMailbox_AllowDspSleep();
    }

}


/*****************************************************************************
 Prototype       : xMbx_SystemError
 Description     : 邮箱异常重启处理接口
                    记录所有的请求信息
                    记录所有的读取请求、读取结果信息
                    记录最后一次DSP IPC中断上报的时间
                    记录唤醒DSP的时间信息
 Input           : errcode  邮箱内部错误码
                   ulPara1,ulPara2,ulPara3   参数1,2,3，异常情况下只保存参数1
 Return Value    : NONE
*****************************************************************************/
void xMbx_SystemError(u32 errcode, u32 ulPara1, u32 ulPara2, u32 ulPara3)
{
    u8 *pData;
    u32 *pAddr;

    pData = osl_malloc(MBX_SYSTEM_ERROR_SIZE);
    if(NULL == pData)
    {
        /* 邮箱错误码由DRV_ERRNO_MBX_WR_FULL开始 */
        system_error(errcode, ulPara1, ulPara2, (char*)NULL, 0); /* [false alarm]:fortify */
        return ;
    }
    xMbx_Memset(pData, 0, MBX_SYSTEM_ERROR_SIZE);

    /* 前4个字保存传入的参数 */
    pAddr = (u32*)pData;

    *(pAddr++) = errcode;
    *(pAddr++) = ulPara1;
    *(pAddr++) = ulPara2;
    *(pAddr++) = ulPara3;

    /* 从第512字节处开始存储信息，与协议栈、DSP异常对齐 */
    xMbx_DumpSave((pData+MBX_ERROR_RESERVE_SIZE), (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    system_error(errcode, ulPara1, ulPara2, (char*)pData, MBX_SYSTEM_ERROR_SIZE);

    osl_free(pData);
}

/*lint -save -e778 -e656*/
void BSP_xMailbox_SetDtcmAddr(CPHY_CCORE_DYN_ADDR_SHARE_STRU *paddr)
{
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;

    g_stxMbxShareAddr.ulCphyMbxHpaDownAddr  = paddr->ulCphyMbxHpaDownAddr;
    g_stxMbxShareAddr.ulCphyMbxHpaUpAddr    = paddr->ulCphyMbxHpaUpAddr;
    g_stxMbxShareAddr.ulCphyMbxLoadMemAddr  = paddr->ulCphyMbxLoadMemAddr;
    g_stxMbxShareAddr.ulCphyMbxOmDownAddr   = paddr->ulCphyMbxOmDownAddr;
    g_stxMbxShareAddr.ulCphyMbxWorkModeAddr = paddr->ulCphyMbxWorkModeAddr;

    pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_1X_RL);
    pMbxTbl->ulDlAddr = g_stxMbxShareAddr.ulCphyMbxHpaDownAddr;
    pMbxTbl->ulUlAddr = g_stxMbxShareAddr.ulCphyMbxHpaUpAddr;

    pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_1X_OM);
    pMbxTbl->ulDlAddr = g_stxMbxShareAddr.ulCphyMbxOmDownAddr;

    pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_HRPD_RL);
    pMbxTbl->ulDlAddr = g_stxMbxShareAddr.ulCphyMbxHpaDownAddr;
    pMbxTbl->ulUlAddr = g_stxMbxShareAddr.ulCphyMbxHpaUpAddr;

    pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_HRPD_OM);
    pMbxTbl->ulDlAddr = g_stxMbxShareAddr.ulCphyMbxOmDownAddr;

    g_stxMbxCtrl.mem_init = 1;
    return;
}
/*lint -restore*/

BSP_BOOL mdrv_Mailbox_IsAllowCdmaSleep(XMBX_RATMODE_ENUM_U32 enMode)
{
    xMAILBOX_RINGBUFF_STRU* pstComPsDownMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr;

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return BSP_TRUE;
    }

    if(XMBX_MOD_1X == enMode)
    {
        if(pstComPsDownMail->ul1XWrCnt == pstComPsDownMail->ul1XRdCnt)
        {
            return BSP_TRUE;
        }
    }
    else if(XMBX_MOD_HRPD == enMode)
    {
        if(pstComPsDownMail->ulHRPDWrCnt == pstComPsDownMail->ulHRPDRdCnt)
        {
            return BSP_TRUE;
        }
    }

    return BSP_FALSE;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


