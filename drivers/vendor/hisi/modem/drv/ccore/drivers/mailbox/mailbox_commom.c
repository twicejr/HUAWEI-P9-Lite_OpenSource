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

#include "mailbox.h"
#include <mdrv_timer.h>
#include "bsp_hardtimer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define MBX_PRINT_TIMES     10
#define SRAM_DSP_MNTN_INFO_ADDR  ((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_MNTN_INFO


/* 邮箱模块控制信息 */
MAILBOX_MAINCTRL_STRU   g_stMbxCtrl;
MAILBOX_MNTN_STRU       g_stMbxMntn;

MAILBOX_CHANNEL_TABLE_STRU g_astMbxChnTbl[EN_MAILBOX_SERVICE_BUTT] =
{
    {EN_MAILBOX_SERVICE_LTE_PS,      MBX_ADDRESSER_LTE_PHY_RL,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_CT,      MBX_ADDRESSER_LTE_PHY_CT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_BT,      MBX_ADDRESSER_LTE_PHY_BT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_OM,      MBX_ADDRESSER_LTE_PHY_OM,     MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
    {EN_MAILBOX_SERVICE_LTE_COEX,    MBX_ADDRESSER_LTE_PHY_COEX,   MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_HS_DIAG, MBX_ADDRESSER_LTE_PHY_HS_DIAG,MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
    {EN_MAILBOX_SERVICE_LTE_RCM,     MBX_ADDRESSER_LTE_PHY_RCM,    MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_PS,      MBX_ADDRESSER_TDS_PHY_RL,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_CT,      MBX_ADDRESSER_TDS_PHY_CT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_BT,      MBX_ADDRESSER_TDS_PHY_BT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_OM,      MBX_ADDRESSER_TDS_PHY_OM,     MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
    {EN_MAILBOX_SERVICE_TDS_HS_DIAG, MBX_ADDRESSER_TDS_PHY_HS_DIAG,MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
	{EN_MAILBOX_SERVICE_TDS_RCM,     MBX_ADDRESSER_TDS_PHY_RCM,    MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
	/* cdma部分 */
	{EN_MAILBOX_SERVICE_1X_RL,       MBX_ADDRESSER_1X_PHY_RL,      MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
	{EN_MAILBOX_SERVICE_1X_OM,       MBX_ADDRESSER_1X_PHY_OM,      MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
	{EN_MAILBOX_SERVICE_1X_CT,       MBX_ADDRESSER_1X_PHY_CT,      MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
	{EN_MAILBOX_SERVICE_1X_BT,       MBX_ADDRESSER_1X_PHY_BT,      MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
	{EN_MAILBOX_SERVICE_1X_HS_DIAG,  MBX_ADDRESSER_1X_PHY_HS_DIAG, MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},

    {EN_MAILBOX_SERVICE_HRPD_RL,     MBX_ADDRESSER_HRPD_PHY_RL,     MAILBOX_PS_DOWN_ADDR,   MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_HRPD_OM,     MBX_ADDRESSER_HRPD_PHY_OM,     MAILBOX_OM_DOWN_ADDR,   0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
    {EN_MAILBOX_SERVICE_HRPD_CT,     MBX_ADDRESSER_HRPD_PHY_CT,     MAILBOX_PS_DOWN_ADDR,   MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_HRPD_BT,     MBX_ADDRESSER_HRPD_PHY_BT,     MAILBOX_PS_DOWN_ADDR,   MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_HRPD_HS_DIAG,MBX_ADDRESSER_HRPD_PHY_HS_DIAG,MAILBOX_OM_DOWN_ADDR,   0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
#endif

    {EN_MAILBOX_SERVICE_RTT_SYS_CTRL,MBX_ADDRESSER_RTT_SYS_CTRL,   MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_RTT_AGENT,   MBX_ADDRESSER_RTT_AGENT,      MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_RTT_CBT,     MBX_ADDRESSER_RTT_CBT,        MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_RTT_HIFI_AGENT, MBX_ADDRESSER_RTT_HIFI_AGENT,  MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX}

};


u32 mbx_IsChnModMatch(u32 ulChn, u32 ulMod)
{
    if(ulChn >= EN_MAILBOX_SERVICE_BUTT)
    {
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    switch(ulChn)
    {
        case EN_MAILBOX_SERVICE_LTE_PS:
        case EN_MAILBOX_SERVICE_TDS_PS:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_1X_RL:
        case EN_MAILBOX_SERVICE_1X_OM:
        case EN_MAILBOX_SERVICE_HRPD_RL:
        case EN_MAILBOX_SERVICE_HRPD_OM:
#endif
        {
            if((MBX_ADDRESSER_LTE_PHY_RL == ulMod)
            ||(MBX_ADDRESSER_TDS_PHY_RL == ulMod)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
            ||(MBX_ADDRESSER_1X_PHY_RL == ulMod)
            ||(MBX_ADDRESSER_1X_PHY_OM == ulMod)
            ||(MBX_ADDRESSER_HRPD_PHY_RL == ulMod)
            ||(MBX_ADDRESSER_HRPD_PHY_OM == ulMod)
#endif
             )
            {
                return BSP_OK;
            }
            break;
        }
        case EN_MAILBOX_SERVICE_LTE_RCM:
        case EN_MAILBOX_SERVICE_TDS_RCM:
        {
            if((MBX_ADDRESSER_LTE_PHY_RCM == ulMod)
             ||(MBX_ADDRESSER_TDS_PHY_RCM == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        case EN_MAILBOX_SERVICE_LTE_CT:
        case EN_MAILBOX_SERVICE_LTE_BT:
        case EN_MAILBOX_SERVICE_TDS_CT:
        case EN_MAILBOX_SERVICE_TDS_BT:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_1X_CT:
        case EN_MAILBOX_SERVICE_1X_BT:
        case EN_MAILBOX_SERVICE_HRPD_CT:
        case EN_MAILBOX_SERVICE_HRPD_BT:
#endif
        {
            if((MBX_ADDRESSER_LTE_PHY_CT == ulMod)
             ||(MBX_ADDRESSER_LTE_PHY_BT == ulMod)
             ||(MBX_ADDRESSER_TDS_PHY_CT == ulMod)
             ||(MBX_ADDRESSER_TDS_PHY_BT == ulMod)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
             ||(MBX_ADDRESSER_1X_PHY_CT == ulMod)
			 ||(MBX_ADDRESSER_1X_PHY_BT == ulMod)
             ||(MBX_ADDRESSER_HRPD_PHY_CT == ulMod)
			 ||(MBX_ADDRESSER_HRPD_PHY_BT == ulMod)
#endif
			 )
            {
                return BSP_OK;
            }
            break;
        }

        default :
        {
            if(g_astMbxChnTbl[ulChn].ulModule == ulMod)
            {
                return BSP_OK;
            }
        }
    }
    return ERR_MAILBOX_PARAM_INCORRECT;
}

u32 mbx_GetChn(u32 ulMod)
{
    u32 i;

    for(i = 0; i < sizeof(g_astMbxChnTbl)/sizeof(MAILBOX_CHANNEL_TABLE_STRU); i++)
    {
        if(ulMod == g_astMbxChnTbl[i].ulModule)
        {
            return g_astMbxChnTbl[i].ulMbxChn;
        }
    }

    return (u32)EN_MAILBOX_SERVICE_BUTT;
}

/*****************************************************************************
 函 数 名  : mbx_mntnaddr
 功能描述  : 邮箱地址相关信息
*****************************************************************************/
void mbx_mntnaddr(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("地址信息\n");
    Mbx_Printf("PS下行邮箱地址                : %p.\n", (void*)MAILBOX_PS_DOWN_ADDR);
    Mbx_Printf("PS上行邮箱地址                : %p.\n", (void*)MAILBOX_PS_UP_ADDR);
    Mbx_Printf("OM下行邮箱地址                : %p.\n", (void*)MAILBOX_OM_DOWN_ADDR);
    Mbx_Printf("DSP握手地址                   : %p.\n", (void*)BSP_DSP_INIT_RESULT_ADDR);
    Mbx_Printf("模式设置地址                  : %p.\n", (void*)LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR);
    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : mbx_mntnabnormal
 功能描述  : 邮箱异常信息
*****************************************************************************/
void mbx_mntnabnormal(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("异常信息\n");
    Mbx_Printf("PS邮箱连续上报的CT/BT消息ID   : %d\n", g_stMbxMntn.stAbnormal.ulMulCtBtMsg);
    Mbx_Printf("PS邮箱上报的错误的模块ID      : %d\n", g_stMbxMntn.stAbnormal.ucComPsType);
    Mbx_Printf("请求处理的最大超时时长        : %d\n", g_stMbxMntn.stAbnormal.ulLongestReq);
    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : mbx_mntnother
 功能描述  : 邮箱其他可维可测信息
*****************************************************************************/
void mbx_mntnother(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("其他信息\n");
    Mbx_Printf("PS邮箱是否子帧中断  : %s\n", (g_stMbxCtrl.bIsSubFrameInt)?"yes":"no");
    Mbx_Printf("PS邮箱当前消息长度  : %d\n", g_stMbxCtrl.ulMsgLen);

    Mbx_Printf("最后十次低功耗唤醒时间信息\n");

    ulStart = (g_stMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice1)
        {
            Mbx_Printf("| slice1(0x%08x) - slice2(0x%08x) | = (0x%08x)   slice3 : 0x%08x\n",
                g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice1,
                g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice2,
                (g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice2 - g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice1),
                g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice3);
        }
    }

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : mbx_mntnnum
 功能描述  : 邮箱次数纪录相关信息
*****************************************************************************/
void mbx_mntnnum(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("计数信息\n");
    Mbx_Printf("PS邮箱中断次数           : %d\n", g_stMbxMntn.stNumber.ulComPsIntNum);
    Mbx_Printf("专有邮箱中断次数         : %d\n", g_stMbxMntn.stNumber.ulSpIntNum);

    Mbx_Printf("PS邮箱写请求次数         : %d\n", g_stMbxMntn.stNumber.ulPsComReqNum);
    Mbx_Printf("PS邮箱PS写请求次数       : %d\n", g_stMbxMntn.stNumber.ulPsComPsReqNum);
    Mbx_Printf("PS邮箱MSP写请求次数      : %d\n", g_stMbxMntn.stNumber.ulPsComMspReqNum);
    Mbx_Printf("PS邮箱RttAgent写请求次数 : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentReqNum);
    Mbx_Printf("OM邮箱写请求次数         : %d\n", g_stMbxMntn.stNumber.ulOmComReqNum);

    Mbx_Printf("PS邮箱PS读取次数         : %d\n", g_stMbxMntn.stNumber.ulPsComPsRdNum);
    Mbx_Printf("PS读取成功次数           : %d\n", g_stMbxMntn.stNumber.ulPsComPsRdOKNum);
    Mbx_Printf("MSP读取次数              : %d\n", g_stMbxMntn.stNumber.ulPsComMspRdNum);
    Mbx_Printf("MSP读取成功次数          : %d\n", g_stMbxMntn.stNumber.ulPsComMspRdOKNum);
    Mbx_Printf("RCM读取次数              : %d\n", g_stMbxMntn.stNumber.ulPsComRcmRdNum);
    Mbx_Printf("RCM读取成功次数          : %d\n", g_stMbxMntn.stNumber.ulPsComRcmRdOKNum);
    Mbx_Printf("RttAgent读取次数         : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentRdNum);
    Mbx_Printf("RttAgent读取成功次数     : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentRdOKNum);

    Mbx_Printf("PS邮箱PS回调次数         : %d\n", g_stMbxMntn.stNumber.ulPsComPsNotifyNum);
    Mbx_Printf("PS邮箱MSP回调次数        : %d\n", g_stMbxMntn.stNumber.ulPsComMspNotifyNum);
    Mbx_Printf("PS邮箱RCM回调次数        : %d\n", g_stMbxMntn.stNumber.ulPsComRcmNotifyNum);
    Mbx_Printf("PS邮箱RttAgent回调次数   : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentNotifyNum);

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : mbx_mntnmailfull
 功能描述  : 邮箱满写入丢失信息
*****************************************************************************/
void mbx_mntnmailfull(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    ulStart = g_stMbxMntn.stMailFull.ulPtr;

    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("邮箱满信息\n");
    Mbx_Printf("邮箱满次数          : %d\n", g_stMbxMntn.stMailFull.ulFullNum);

    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stMailFull.astFullInfo[j].ulSlice)
        {
            Mbx_Printf("类型 : %d   消息ID : 0x%08x   时间 : 0x%08x\n",
                g_stMbxMntn.stMailFull.astFullInfo[j].ulModId
                , g_stMbxMntn.stMailFull.astFullInfo[j].ulMsgId
                , g_stMbxMntn.stMailFull.astFullInfo[j].ulSlice);
        }
    }

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : mbx_mntnreqinfo
 功能描述  : 邮箱写请求信息
*****************************************************************************/
void mbx_mntnreqinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("邮箱写请求信息\n");

    ulStart = (g_stMbxMntn.stReqInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stReqInfo.astReq[j].ulSliceEnd)
        {
            Mbx_Printf("类型 : %d   消息ID : 0x%08x   请求时间 : 0x%08x   写入时间 : 0x%08x\n",
                g_stMbxMntn.stReqInfo.astReq[j].ulModId, g_stMbxMntn.stReqInfo.astReq[j].ulMsgId,
                g_stMbxMntn.stReqInfo.astReq[j].ulSliceStart, g_stMbxMntn.stReqInfo.astReq[j].ulSliceEnd);
        }
    }

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 函 数 名  : mbx_mntncnfinfo
 功能描述  : 邮箱读请求信息
*****************************************************************************/
void mbx_mntncnfinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    Mbx_Printf("***************************************************************\n");

    Mbx_Printf("最后十次浮动中断的信息\n");

    ulStart = (g_stMbxMntn.stIntInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stIntInfo.ulSlice[j])
        {
            Mbx_Printf("interrupt slice : 0x%08x\n", g_stMbxMntn.stIntInfo.ulSlice[j]);
        }
    }

    Mbx_Printf("最后十次原语读取的信息\n");

    ulStart = (g_stMbxMntn.stReadInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stReadInfo.astRead[j].ulSlice)
        {
            Mbx_Printf("app read , src 0x%x, slice 0x%08x\n",
                g_stMbxMntn.stReadInfo.astRead[j].ulSrc, g_stMbxMntn.stReadInfo.astRead[j].ulSlice);
        }
    }

    ulStart = (g_stMbxMntn.stCnfInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    Mbx_Printf("邮箱PS最后10条读请求信息\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stCnfInfo.astPsCnf[j].ulSlice)
        {
            Mbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astPsCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astPsCnf[j].ulSlice);
        }
    }

    ulStart = (g_stMbxMntn.stCnfInfo.ulRcmPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;
    Mbx_Printf("邮箱RCM最后10条读请求信息\n");
    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice)
        {
            Mbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astRcmCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice);
        }
    }
    ulStart = (g_stMbxMntn.stCnfInfo.ulCbtPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    Mbx_Printf("邮箱CT/BT最后10条读请求信息\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice)
        {
            Mbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astCbtCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice);
        }
    }

    Mbx_Printf("邮箱Rtt Agent最后10条读请求信息\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice)
        {
            Mbx_Printf("消息ID : 0x%08x   读取时间 : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astRttAgentCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice);
        }
    }

    Mbx_Printf("***************************************************************\n");
}

void mbx_mntnSleepCbInfo(void)
{
    u32 i =0,j=0;
    for(i=0; i<MAILBOX_MNTN_NUMBER; i++)
    {
        j = (g_stMbxMntn.stSleepCbInfo.ulPtr+i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)
        {
            Mbx_Printf("Callback Type : %d, Is Mbx wakeup :%d, end time(0x%08x) - start time(0x%08x) = %d  MS\n",
                g_stMbxMntn.stSleepCbInfo.astCbInfo[j].cbType,g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulWakeup,\
                g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd,g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart,\
                ((g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd-g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)/32));
        }
    }
}

void mbx_mntnDirectWriteInfo(void)
{
    u32 i = 0 ,k = 0;
    u32 j = g_stMbxMntn.stDirectInfo.ulPtr % MAILBOX_MNTN_NUMBER;
    Mbx_Printf("*************Direct Num 0x%x****************\n",g_stMbxMntn.stDirectInfo.ulPtr);
    Mbx_Printf("*************print lastest *****************\n");
    for(i = 0;i < MAILBOX_MNTN_NUMBER;i++)
    {
        k = (j+1)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stMbxMntn.stDirectInfo.ulSlice[k])
        {
            Mbx_Printf("第 %d 次，时间戳为 :0x%x\n",i,g_stMbxMntn.stDirectInfo.ulSlice[k]);
        }
    }
}
/*****************************************************************************
 函 数 名  : mbx_mntnerrorcode
 功能描述  : 邮箱错误码相关信息
*****************************************************************************/
void mbx_mntnerrorcode(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("错误码信息\n");
    Mbx_Printf("1  : 邮箱未初始化.\n");
    Mbx_Printf("2  : 输入参数错误.\n");
    Mbx_Printf("3  : 邮箱满.\n");
    Mbx_Printf("4  : 超时.\n");
    Mbx_Printf("5  : 专有邮箱数据覆盖.\n");
    Mbx_Printf("6  : 写失败.\n");
    Mbx_Printf("7  : 读失败.\n");
    Mbx_Printf("8  : 读信息为空.\n");
    Mbx_Printf("9  : DSP睡眠.\n");
    Mbx_Printf("10 : 其他.\n");
    Mbx_Printf("***************************************************************\n");
}


void mbx_debug(BSP_BOOL bDebug)
{
    g_stMbxMntn.bdbg = bDebug;
}

/*****************************************************************************
 函 数 名  : mailbox_help
 功能描述  : 邮箱打印帮助
*****************************************************************************/
void mailbox_help(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("邮箱地址相关信息                mbx_mntnaddr\n");
    Mbx_Printf("邮箱次数纪录相关信息            mbx_mntnnum\n");
    Mbx_Printf("邮箱写请求信息                  mbx_mntnreqinfo\n");
    Mbx_Printf("邮箱读请求信息                  mbx_mntncnfinfo\n");
    Mbx_Printf("邮箱满写入丢失信息              mbx_mntnmailfull\n");
    Mbx_Printf("邮箱异常信息                    mbx_mntnabnormal\n");
    Mbx_Printf("邮箱其他可维可测信息            mbx_mntnother\n");
    Mbx_Printf("邮箱操作失败错误码信息          mbx_mntnerrorcode\n");
    Mbx_Printf("邮箱打印信息开关                mbx_debug 1/0\n");
    Mbx_Printf("邮箱SLEEP回调信息               mbx_mntnSleepCbInfo\n");
    Mbx_Printf("邮箱直接写信息                  mbx_mntnDirectWriteInfo\n");
    Mbx_Printf("***************************************************************\n");
}


/*lint -save -e545 -e813*/
/*****************************************************************************
 Prototype       : Mbx_BbeIpcProc
 Description     : 邮箱的异常处理
                   BBE出现异常时，保存异常信息到AXI memory中，然后通过IPC中断
                   通知邮箱模块，由邮箱模块记录异常信息，并调用异常重启接口
 Return Value    : NONE
*****************************************************************************/
void Mbx_BbeIpcProc(void)
{
    u8  ucData[MBX_SYSTEM_ERROR_SIZE] = {0};     /* 4K缓存，前32字节存DSP信息 */
    u32 *pAddr;
    u16 usMode;

    usMode = *(u16*)SRAM_DSP_MNTN_INFO_ADDR;

    /* 0表示PS邮箱满 */
    if(0 == usMode)
    {
        /* 前4个字保存传入的参数 */
        pAddr = (u32*)ucData;

        *(pAddr++) = DRV_ERRNO_MBX_DSP_IPC;
        *(pAddr++) = 0;
        *(pAddr++) = 0;
        *(pAddr++) = 0;

        /* 保存DSP的异常信息 */
        Mbx_Memcpy((u8*)pAddr, (u8*)SRAM_DSP_MNTN_INFO_ADDR, SRAM_DSP_MNTN_SIZE); /* [false alarm]:fortify */

        /* 从第512字节开始保存邮箱驱动的异常信息 */
        Mbx_DumpSave(ucData+MBX_ERROR_RESERVE_SIZE, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

        system_error(DRV_ERRNO_MBX_DSP_IPC, 0, 0, (char*)ucData, MBX_SYSTEM_ERROR_SIZE);
    }
}
/*lint -restore*/


/*****************************************************************************
 函 数 名  : bsp_mailbox_init
 功能描述  : 邮箱模块初始化
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
void bsp_mailbox_init(void)
{
    s32 ret;

    if(BSP_TRUE == g_stMbxCtrl.bMbxInit)
    {
        Mbx_Printf("enter again.\n");
        return;
    }

    Mbx_Memset(&g_stMbxCtrl, 0, sizeof(MAILBOX_MAINCTRL_STRU));

    Mbx_Memset((void*)(&g_stMbxMntn), 0, sizeof(MAILBOX_MNTN_STRU));

    g_stMbxCtrl.bDspWakeFlag = BSP_FALSE;

    osl_sem_init(0, &g_stMbxCtrl.semDspWakeup);
    osl_sem_init(1, &g_stMbxCtrl.semDspMutex);
    g_stMbxCtrl.pulAxiAddr = (u32*)MBX_LDSP_WAKEUP_ADDR;
    g_stMbxCtrl.lAxiCnt = 0;
    ret = (s32)mdrv_ipc_int_connect(IPC_INT_DSP_PS_PUB_MBX, (VOIDFUNCPTR)Mbx_ComPsIntProc, 0);
	if(BSP_OK != ret)
	{
        Mbx_Printf("mdrv_ipc_int_connect failed.\n");
        return ;
	}

    ret = (s32)mdrv_ipc_int_enable(IPC_INT_DSP_PS_PUB_MBX);
	if(BSP_OK != ret)
	{
        Mbx_Printf("mdrv_ipc_int_enable failed.\n");
        return ;
	}

    ret = (s32)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX, (VOIDFUNCPTR)Mbx_ComPsIntProc, 0);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_enable failed.\n");
        return ;
    }

    /* DSP可维可测IPC中断 */
    ret = (s32)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_DSP_MNTN, (VOIDFUNCPTR)Mbx_BbeIpcProc, 0);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_DSP_MNTN);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_enable failed.\n");
        return ;
    }

    g_stMbxCtrl.bIsSubFrameInt = BSP_FALSE;

    Mbx_Printf("success.\n");
    return;
}


/*****************************************************************************
 函 数 名  : Mbx_ForbidDspSleep
 功能描述  : 设置AXI memory禁止DSP进入睡眠
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
void Mbx_ForbidDspSleep(void)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
#else
    unsigned long key;

    local_irq_save(key);
    g_stMbxCtrl.lAxiCnt++;
    writel(1, (unsigned)(g_stMbxCtrl.pulAxiAddr));
    local_irq_restore(key);

#endif
}


/*****************************************************************************
 函 数 名  : Mbx_ForbidDspSleep
 功能描述  : 清除AXI memory允许DSP进入睡眠
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
void Mbx_AllowDspSleep(void)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
#else
    unsigned long key;

    local_irq_save(key);
    if((--g_stMbxCtrl.lAxiCnt) <= 0)
    {
        g_stMbxCtrl.lAxiCnt = 0;
        writel(0, (unsigned)(g_stMbxCtrl.pulAxiAddr));
    }
    local_irq_restore(key);
  
#endif
}


/*****************************************************************************
 函 数 名  : Mbx_SpaceMalloc
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
u32 Mbx_SpaceMalloc(MAILBOX_RINGBUFF_STRU* pMbxHandle,u32 ulSizeReq)
{
    u32 ulFreeBuffSize;
    u32 wr,rd,size;

    wr   = pMbxHandle->ulRbufWrPtr;
    rd   = pMbxHandle->ulRbufRdPtr;
    size = pMbxHandle->ulRbufSize;

    /* 如果写指针非法，立即重启 */
    if(wr > size)
    {
        Mbx_SystemError((u32)DRV_ERRNO_MBX_UP_WR, wr, rd, ((__LINE__ << 16)|size));
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
        Mbx_Printf("Mbx_SpaceMalloc failed, ulFreeBuffSize(%d), ulSizeReq(%d), wr(%d), rd(%d), size(%d).\n",
            ulFreeBuffSize, ulSizeReq, wr, rd, size);
        return (u32)BSP_ERROR;
    }
}


void Mbx_MntnMailFull(MAILBOX_MSG_HAED_STRU* pstMsg)
{
    g_stMbxMntn.stMailFull.ulFullNum++;

    g_stMbxMntn.stMailFull.astFullInfo[g_stMbxMntn.stMailFull.ulPtr].ulModId = (u32)(pstMsg->usDstMod);
    g_stMbxMntn.stMailFull.astFullInfo[g_stMbxMntn.stMailFull.ulPtr].ulMsgId = *(u32*)(pstMsg->pPayload);
    g_stMbxMntn.stMailFull.astFullInfo[g_stMbxMntn.stMailFull.ulPtr].ulSlice = bsp_get_slice_value();

    g_stMbxMntn.stMailFull.ulPtr = (g_stMbxMntn.stMailFull.ulPtr+1)%MAILBOX_MNTN_NUMBER;
}


/*****************************************************************************
 Prototype       : Mbx_RbuffWrite
 Description     : 循环buffer写接口
 param           : pHead        循环buffer的首地址
                   pstMsg       待写入数据指针
 Return Value    : BSP_OK : 成功
                   ERR_MAILBOX_MEMORY_NOTENOUGH : 剩余空间不足
*****************************************************************************/
s32 Mbx_RbuffWrite(MAILBOX_RINGBUFF_STRU* pHead, MAILBOX_MSG_HAED_STRU* pstMsg)
{
    u32 ulMsgSize = pstMsg->usMsgSize + (sizeof(MAILBOX_MSG_HAED_STRU) - 4);
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempPPTR;

    /* 邮箱剩余空间检查 */
    if(BSP_OK != Mbx_SpaceMalloc(pHead,ulMsgSize))
    {
        Mbx_MntnMailFull(pstMsg);
        return ERR_MAILBOX_MEMORY_NOTENOUGH;
    }

    /* 新消息写入 */
    if((ulMsgSize + pHead->ulRbufWrPtr) <= pHead->ulRbufSize)
    {
        Mbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                        (void*)pstMsg,
                        (sizeof(MAILBOX_MSG_HAED_STRU) - 4));
        Mbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                        (void*)(pstMsg->pPayload),
                        pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pHead->ulRbufSize - pHead->ulRbufWrPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(MAILBOX_MSG_HAED_STRU) - 4))
        {
            Mbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)pstMsg,
                            ulCpySize0);

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg)+ulCpySize0),
                            ((sizeof(MAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0));

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + ((sizeof(MAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0)),
                            (void*)(pstMsg->pPayload),
                            pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            Mbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)(pstMsg),
                            (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                            (void*)(pstMsg->pPayload),
                            (ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4)));

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg->pPayload) + (ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4))),
                            ulCpySize1);
        }
    }

    /* 写指针更新,保证四字节对齐 */
    ulTempPPTR = ((pHead->ulRbufWrPtr + ulMsgSize + 3) & (~3));

    if(ulTempPPTR >= pHead->ulRbufSize)
    {
        ulTempPPTR -= pHead->ulRbufSize;
    }

    Mbx_MntnWriteEnd(pHead, pstMsg, ulTempPPTR);

    pHead->ulRbufWrPtr = ulTempPPTR;

    return BSP_OK;
}


/*****************************************************************************
 函 数 名  : Mbx_GetNewMsgLen
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
u32 Mbx_GetNewMsgLen (MAILBOX_MSG_HAED_STRU* pMsg)
{
    return(u32)(pMsg->usMsgSize);
}


/*****************************************************************************
 函 数 名  : Mbx_NewMsgReadOut
 功能描述  : 执行消息读出操作
 输入参数  : 	MAILBOX_RINGBUFF_STRU* pMbxHandle,
 输出参数  : 	void* pMsg,
 返 回 值  :  更新后的CPTR指针

 修改历史      :
 1.	日    期   : 2012年8月23日
	作    者   : honghuiyong(164941)
	修改内容   : 新生成函数

*****************************************************************************/
u32 Mbx_NewMsgReadOut(MAILBOX_MSG_HAED_STRU* pMsg,MAILBOX_RINGBUFF_STRU* pMbxHandle)
{
    u32 ulMsgSize;
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempCPTR;
    MAILBOX_MSG_HAED_STRU *pstMsg = NULL;

    pstMsg = (MAILBOX_MSG_HAED_STRU*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + pMbxHandle->ulRbufRdPtr);
    ulMsgSize = Mbx_GetNewMsgLen(pstMsg) + (sizeof(MAILBOX_MSG_HAED_STRU) - 4);

    /* user space not enough, return failure, avoid overflow */
    if(pstMsg->usMsgSize > pMsg->usMsgSize)
    {
        pMsg->usMsgSize = pstMsg->usMsgSize;
        goto newmsgreadfailed;
    }

    /* 新消息读出 */
    if((ulMsgSize + pMbxHandle->ulRbufRdPtr) <= pMbxHandle->ulRbufSize)
    {
        Mbx_Memcpy((void*)pMsg,
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

        Mbx_Memcpy((void*)(pMsg->pPayload),
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pMbxHandle->ulRbufSize - pMbxHandle->ulRbufRdPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(MAILBOX_MSG_HAED_STRU) - 4))
        {
            Mbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    ulCpySize0);

            Mbx_Memcpy((void*)((u32)pMsg + ulCpySize0),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                    (sizeof(MAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0);

            Mbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0),
                    pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            Mbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

            Mbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                    ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

            Mbx_Memcpy((void*)((u32)(pMsg->pPayload) + ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
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

    Mbx_MntnReadEnd(pMsg->pPayload, (enum __MBX_ADDRESSEE_ID_ENUM__)pMsg->usDstMod, ulTempCPTR, pMbxHandle->ulRbufWrPtr);

    pMbxHandle->ulRbufRdPtr = ulTempCPTR;

    return (ulTempCPTR);
}


/*****************************************************************************
 Prototype       : BSP_MailBox_GetDspStatusReg
 Description     : 获取DSP睡眠状态回调函数注册接口，低功耗模块调用
 param           : pFun             获取DSP睡眠状态处理函数
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_GetDspStatusReg(BSP_MBX_GET_STATUS_FUNC pFun)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    g_stMbxCtrl.pfnGetDspStatusProc = NULL;
#else
    g_stMbxCtrl.pfnGetDspStatusProc = pFun;
#endif
}


/*****************************************************************************
 Prototype       : BSP_MailBox_DspForceAwakeReg
 Description     : DSP强制唤醒回调函数注册接口，低功耗模块调用
 param           : pFun             DSP强制唤醒处理函数
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_DspForceAwakeReg(BSP_MBX_DSP_AWAKE_FUNC pFun)
{
    g_stMbxCtrl.pfnDspForceAwakeProc = pFun;
}


/*****************************************************************************
 Prototype       : BSP_MailBox_GetSpMsgStatusReg
 Description     : 获取专有邮箱允许DSP睡眠状态回调函数注册接口，PS调用
 param           : pFun             获取DSP睡眠状态处理函数
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_GetSpMsgStatusReg(BSP_MBX_GET_STATUS_FUNC pFun)
{
    g_stMbxCtrl.pfnGetSpMsgProc = pFun;
}


/*****************************************************************************
 Prototype       : BSP_MailBox_DspAwakeProc
 Description     : DSP唤醒后的邮箱处理接口，低功耗模块调用
 param           : BSP_VOID
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_DspAwakeProc(MAILBOX_CALLBACK_TYPE cbType)
{
    u32 ulPtr = g_stMbxMntn.stSleepCbInfo.ulPtr;
    g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].cbType       = cbType;
    if(cbType >= EN_MAILBOX_CALLBACK_DSP_BUTT)
    {
        Mbx_Printf("err parm ! %d \n",cbType);
        cbType = EN_MAILBOX_CALLBACK_DSP_BUTT;
    }
    if(g_stMbxCtrl.pfnRcmNotifyProc)
    {
        g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulWakeup     = g_stMbxCtrl.bDspWakeFlag;

        g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceStart = bsp_get_slice_value();
        g_stMbxCtrl.pfnRcmNotifyProc(cbType);

        g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceEnd   = bsp_get_slice_value();

        ulPtr = g_stMbxMntn.stSleepCbInfo.ulPtr +1;

        g_stMbxMntn.stSleepCbInfo.ulPtr = ulPtr%MAILBOX_MNTN_NUMBER;
    }
    if(EN_MAILBOX_CALLBACK_DSP_RESUME == cbType)
    {
        /* 只处理邮箱模块发起的唤醒 */
        if(BSP_TRUE == g_stMbxCtrl.bDspWakeFlag)
        {
            g_stMbxMntn.stSleepInfo.astwakeup[g_stMbxMntn.stSleepInfo.ulPtr].ulSlice2 = bsp_get_slice_value();
            g_stMbxCtrl.bDspWakeFlag = BSP_FALSE;
            osl_sem_up(&g_stMbxCtrl.semDspWakeup);
        }
    }
}


/*****************************************************************************
 Prototype       : BSP_MailBox_IsAllowDspSleep
 Description     : 查询是否允许DSP睡眠的处理接口，低功耗模块调用
                    调用此接口时低功耗模块保证DSP未睡眠
                    此接口只检测PS邮箱和专有邮箱，不检查OM邮箱(OM原语无时延要求)
 param           : BSP_VOID
 Return Value    : BSP_BOOL: TRUE-allow;FALSE-forbid
*****************************************************************************/
int BSP_MailBox_IsAllowDspSleep(void)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    return BSP_FALSE;
#else
    BSP_BOOL bFlag;
    MAILBOX_RINGBUFF_STRU* pstComPsUpMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_PS_UP_ADDR;
    MAILBOX_RINGBUFF_STRU* pstComPsDownMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_PS_DOWN_ADDR;
    MAILBOX_RINGBUFF_STRU* pstOmDownMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_OM_DOWN_ADDR;

    if(!(g_stMbxCtrl.bMbxInit))
    {
        g_stMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return BSP_TRUE;
    }

    /* 第一优先级先查AXI memory，AXI memory设置时不允许DSP睡眠 */
    if(*(g_stMbxCtrl.pulAxiAddr) == 1)
    {
        return BSP_FALSE;
    }

    /* 专有邮箱有原语未读走禁止睡眠 */
    if(NULL != g_stMbxCtrl.pfnGetSpMsgProc)
    {
        bFlag = g_stMbxCtrl.pfnGetSpMsgProc();
        if(BSP_TRUE != bFlag)
        {
            return bFlag;
        }
    }

    /* PS邮箱有原语未读走禁止睡眠 */
    if((pstComPsUpMail->ulRbufRdPtr != pstComPsUpMail->ulRbufWrPtr)
        || (pstComPsDownMail->ulRbufRdPtr != pstComPsDownMail->ulRbufWrPtr)
        || (pstOmDownMail->ulRbufRdPtr != pstOmDownMail->ulRbufWrPtr))
    {
        return BSP_FALSE;
    }

    return BSP_TRUE;
#endif
}


/*****************************************************************************
 Prototype       : BSP_UniMailboxWrite
 Description     : 邮箱的通用写接口(由调用者保证传入的地址的合法性)
                   本接口实现类似memcpy函数的作用
                   接口内部保证DSP的唤醒操作，如果唤醒失败，返回ERR_MAILBOX_TIMEOUT
 Return Value    :
                   BSP_OK
                   ERR_MAILBOX_PARAM_INCORRECT
                   ERR_MAILBOX_TIMEOUT
*****************************************************************************/
unsigned int BSP_UniMailboxWrite(void *pDst, void *pSrc, unsigned int ulLen)
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

    Mbx_Memcpy(pDst, pSrc, ulLen);

    BSP_Mailbox_AllowDspSleep();

    return BSP_OK;
}


/*****************************************************************************
 Prototype       : BSP_MailboxAbnormalProc
 Description     : 邮箱异常处理
                   协议栈接收消息超时后调用此接口保存邮箱相关信息
                   与协议栈商定，前0.5K保存协议栈信息，后3.5K保存邮箱信息
 Input           : ucData       缓存首地址
 Return Value    : NONE
*****************************************************************************/
void BSP_MailboxAbnormalProc(unsigned char *ucData)
{
    if(BSP_NULL == ucData)
    {
        return;
    }

    Mbx_Printf("enter.\n");

    Mbx_DumpSave(ucData, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    Mbx_Printf("exit.\n");
}


/*****************************************************************************
 Prototype       : Mbx_DumpSave
 Description     : 邮箱异常重启信息保存接口
                    记录所有的请求信息
                    记录所有的读取请求、读取结果信息
                    记录最后一次DSP IPC中断上报的时间
                    记录唤醒DSP的时间信息
 Input           :  pData 缓冲区起始地址
                    ulSize 缓冲区大小
 Return Value    : NONE
*****************************************************************************/
void Mbx_DumpSave(u8* pData, u32 ulSize)
{
    u32 i,ptr;
    u32 ultmp = 0;

    /* 传入的空间大小最小3.5K */
    if((ulSize < (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE)) || (NULL == pData))
    {
        Mbx_Printf("ulSize %d, pData %p.\n", ulSize, pData);
        return;
    }

    ptr = g_stMbxMntn.stReqInfo.ulPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/RWpointer/start slice/end slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stReqInfo.astReq[ptr].ulMsgId), 4*sizeof(u32)); /*lint !e420*/ /* [false alarm]:fortify */
        ultmp += 4*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 1600 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stMbxMntn.stCnfInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stCnfInfo.astPsCnf[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 2400 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stMbxMntn.stReadInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (read src/slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stReadInfo.astRead[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3200 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    /* 空间有限，只记录最后十次的唤醒信息 */
    ptr = (g_stMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (req slice/callback slice/proc slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stSleepInfo.astwakeup[ptr]), 3*sizeof(u32));
        ultmp += 3*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3320 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    /* 空间有限，只记录最后十次的IPC时间信息 */
    ptr = (g_stMbxMntn.stCallback.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (callback timer) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stCallback.ulSlice[ptr]), sizeof(u32));
        ultmp += sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3360 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stNumber), sizeof(g_stMbxMntn.stNumber));
    ultmp += sizeof(g_stMbxMntn.stNumber);

    /* ultmp value is 3408 */

    Mbx_Printf("ultmp = %d.\n", ultmp);

    Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stAbnormal), sizeof(g_stMbxMntn.stAbnormal));
    ultmp += sizeof(g_stMbxMntn.stAbnormal);

    /* ultmp value is 3424 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    /* 在最后32个字节保存上下行邮箱头信息 */
    if(BSP_OK == BSP_Mailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP))
    {
        Mbx_Memcpy(&pData[ulSize-(2*sizeof(MAILBOX_RINGBUFF_STRU))],
            (BSP_VOID*)MAILBOX_PS_DOWN_ADDR, sizeof(MAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        Mbx_Memcpy(&pData[ulSize - sizeof(MAILBOX_RINGBUFF_STRU)],
            (BSP_VOID*)MAILBOX_PS_UP_ADDR, sizeof(MAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        BSP_Mailbox_AllowDspSleep();
    }

}


/*****************************************************************************
 Prototype       : Mbx_SystemError
 Description     : 邮箱异常重启处理接口
                    记录所有的请求信息
                    记录所有的读取请求、读取结果信息
                    记录最后一次DSP IPC中断上报的时间
                    记录唤醒DSP的时间信息
 Input           : errcode  邮箱内部错误码
                   ulPara1,ulPara2,ulPara3   参数1,2,3，异常情况下只保存参数1
 Return Value    : NONE
*****************************************************************************/
void Mbx_SystemError(u32 errcode, u32 ulPara1, u32 ulPara2, u32 ulPara3)
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
    Mbx_Memset(pData, 0, MBX_SYSTEM_ERROR_SIZE);

    /* 前4个字保存传入的参数 */
    pAddr = (u32*)pData;

    *(pAddr++) = errcode;
    *(pAddr++) = ulPara1;
    *(pAddr++) = ulPara2;
    *(pAddr++) = ulPara3;

    /* 从第512字节处开始存储信息，与协议栈、DSP异常对齐 */
    Mbx_DumpSave((pData+MBX_ERROR_RESERVE_SIZE), (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    system_error(errcode, ulPara1, ulPara2, (char*)pData, MBX_SYSTEM_ERROR_SIZE);

    osl_free(pData);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


