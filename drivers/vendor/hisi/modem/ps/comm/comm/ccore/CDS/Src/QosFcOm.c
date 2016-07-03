


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CDS.h"
#include "QosFcOm.h"
#include "QosFcStatus.h"
#include "QosFcRabStatus.h"
#include "QosFcChannelFlowCtrl.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_QOS_FC_OM_C
/*lint +e767*/




/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/
QOS_FC_STATS_INFO_STRU g_stQosFcStats = {0};

extern VOS_INT32 g_iRabEntityCnt;
extern QOS_FC_RAB_ENTITY_STRU g_stQosFcRabEntity[FC_MAX_RAB_NUM];
extern QOS_FC_RAB_STATE_ENUM_UINT32 g_enRabState[MODEM_ID_BUTT][FC_MAX_RAB_NUM];
extern QOS_FC_CHANNEL_ENTITY_STRU g_stQosFcChannelEntity[FC_MAX_RAB_NUM];



/******************************************************************************
   5 函数实现
******************************************************************************/

VOS_VOID QosFc_ShowState(VOS_VOID)
{
    PS_PRINTF("QoS流控状态     %d\r\n", g_stQosFcCtrl.enFlowCtrl);
    return;
}


VOS_VOID QosFc_ShowRabState(VOS_VOID)
{
    VOS_UINT32  i,k;
    VOS_UINT32  j=5;

    PS_PRINTF("QoS流控RAB状态\r\n");
    for(k = 0; k < MODEM_ID_BUTT; k++)
    {
        for(i = 0; i < FC_MAX_RAB_NUM; )
        {
            PS_PRINTF("RabId:   %2d  State:  %d",  i + 5, g_enRabState[k][i]);
            i++;
            while(--j)
            {
                if(i < FC_MAX_RAB_NUM)
                {
                	PS_PRINTF(" :  %d", g_enRabState[k][i++]);
                }
            }
            j = 5;
            PS_PRINTF("\r\n");
        }
        PS_PRINTF("\r\n");
    }

    PS_PRINTF("\r\n");
    return;
}


VOS_VOID QosFc_ShowEntity(VOS_VOID)
{
    VOS_UINT32  i;

    PS_PRINTF("QoS流控实体状态: %d\r\n", g_iRabEntityCnt);
    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(FC_INVALID_RABID == g_stQosFcRabEntity[i].ucRabId)
        {
            break;
        }
        PS_PRINTF("Entity:    %2d  QCI:  %d  Priority: %d  LinkRabId:  %2d  State: %d\r\n",
                            g_stQosFcRabEntity[i].ucRabId,
                            g_stQosFcRabEntity[i].enQci,
                            g_stQosFcRabEntity[i].ucPriority,
                            g_stQosFcRabEntity[i].ucLinkRabId,
                            g_stQosFcRabEntity[i].enRabState);
    }
    PS_PRINTF("\r\n");
    return;
}


VOS_VOID QosFc_ShowChannel(VOS_VOID)
{
    VOS_UINT32  i;

    PS_PRINTF("QoS流控通道状态\r\n");
    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(FC_INVALID_RABID == g_stQosFcChannelEntity[i].ucRabId)
        {
            break;
        }
        PS_PRINTF("Channel:    %2d  QCI:  %d  State : %d\r\n",
                            g_stQosFcChannelEntity[i].ucRabId,
                            g_stQosFcChannelEntity[i].enQci,
                            g_stQosFcChannelEntity[i].enChannelState);
    }
    PS_PRINTF("\r\n");
    return;
}



VOS_VOID QosFc_ShowPara(VOS_VOID)
{
    PS_PRINTF("QoS流控参数 :\r\n");
    PS_PRINTF("\r\n");
    PS_PRINTF("QoS流控是否使能             %s\r\n", g_stQosFcCtrl.bQosFcEnable?"Yes":"No");
    PS_PRINTF("最高优先级承载是否流控      %s\r\n", g_stQosFcCtrl.bHighFcEnable?"Yes":"No");
    PS_PRINTF("触发QoS流控包数             %d\r\n", g_stQosFcCtrl.ulPktCntLimit);
    PS_PRINTF("触发QoS流控时长             %d\r\n", g_stQosFcCtrl.ulTimerLen);
    PS_PRINTF("随机丢包率                  %d\r\n", g_stQosFcCtrl.ulRandomDiscardRate);
    PS_PRINTF("丢包率                      %d\r\n", g_stQosFcCtrl.ulDiscardRate);
    PS_PRINTF("警告阈值                    %d\r\n", g_stQosFcCtrl.ulWarningThres);
    PS_PRINTF("丢包阈值                    %d\r\n", g_stQosFcCtrl.ulDiscardThres);
    PS_PRINTF("随机丢包阈值                %d\r\n", g_stQosFcCtrl.ulRandomDiscardThres);
    PS_PRINTF("恢复阈值                    %d\r\n", g_stQosFcCtrl.ulRestoreThres);

    PS_PRINTF("\r\n");
    return;
}


VOS_VOID QosFc_OutPutRabStats(CONST VOS_UINT32 *aulData)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 j = 5;

    for(i = 0; i < FC_MAX_RAB_NUM; )
    {
        PS_PRINTF("%10d",  aulData[i++]);
        while(--j)
        {
            if(i < FC_MAX_RAB_NUM)
            {
                PS_PRINTF("  %6d", aulData[i++]);
            }
        }
        j = 5;
        PS_PRINTF("\r\n");
    }
    return;
}


VOS_VOID QosFc_ShowStats(VOS_VOID)
{
    VOS_UINT32 i = 0;
    PS_PRINTF("QoS流控统计 :\r\n");
    PS_PRINTF("\r\n");
    PS_PRINTF("收到CREATE消息数量      %d\r\n", g_stQosFcStats.ulCreateMsgNum);
    PS_PRINTF("收到RELEASE消息数量     %d\r\n", g_stQosFcStats.ulReleaseMsgNum);
    PS_PRINTF("创建承载次数            %d\r\n", g_stQosFcStats.ulCreateRabNum);
    PS_PRINTF("更新承载次数            %d\r\n", g_stQosFcStats.ulUpdateRabNum);
    PS_PRINTF("释放承载次数            %d\r\n", g_stQosFcStats.ulReleaseRabNum);
    PS_PRINTF("上行LTE丢包总数         %d\r\n", g_stQosFcStats.ulUlLteDiscardTotalNum);
    PS_PRINTF("上行GU丢包总数          %d\r\n", g_stQosFcStats.ulUlGUDiscardTotalNum);
    PS_PRINTF("下行LTE丢包总数         %d\r\n", g_stQosFcStats.ulDlLteDiscardTotalNum);
    PS_PRINTF("下行GU丢包总数          %d\r\n", g_stQosFcStats.ulDlGUDiscardTotalNum);

    PS_PRINTF("上行每个承载进入随机丢包状态次数     \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulToRandomDiscardNum[i]);
    }

    PS_PRINTF("上行每个承载进入丢包状态次数        \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulToDiscardNum[i]);
    }

    PS_PRINTF("上行每个承载恢复正常状态次数       \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulToNormalNum[i]);
    }

    PS_PRINTF("上行每个承载上丢包状态时收包数量       \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulRcvPktNumOnD[i]);
    }

    PS_PRINTF("上行每个承载上丢包状态时丢包数量       \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulDiscardPktNumOnD[i]);
    }

    PS_PRINTF("上行每个承载上随机丢包状态时收包数量       \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulRcvPktNumOnRD[i]);
    }

    PS_PRINTF("上行每个承载上随机丢包状态时丢包数量      \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulDiscardPktNumOnRD[i]);
    }

    PS_PRINTF("\r\n");
    PS_PRINTF("通道流控次数       \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulChannelToFc[i]);
    }

    PS_PRINTF("解通道流控次数       \r\n");
    for(i = 0; i < MODEM_ID_BUTT; i++)
    {
        QosFc_OutPutRabStats(g_stQosFcStats.aulChannelResume[i]);
    }

    PS_PRINTF("\r\n");

    return;
}


VOS_VOID QosFc_ResetStats(VOS_VOID)
{
    PS_MEM_SET(&g_stQosFcStats, 0, sizeof(QOS_FC_STATS_INFO_STRU));
    return;

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



