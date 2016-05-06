

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "RnicDebug.h"
#include "RnicCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/

RNIC_MNTN_STATS_STRU                    g_stRnicMntnStats = {0};
RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
VOS_UINT32                              g_ulRnicPrintUlDataFlg = VOS_FALSE;
VOS_UINT32                              g_ulRnicPrintDlDataFlg = VOS_FALSE;


/******************************************************************************
   5 函数实现
******************************************************************************/

VOS_VOID RNIC_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulRnicPrintUlDataFlg = ulFlg;
}

/*****************************************************************************
 函 数 名  : RNIC_ShowRnicPdpStats
 功能描述  : 显示RNIC pdp的信息
 输入参数  : ucRmNetId : 网卡ID
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年11月23日
      作    者   : f00179208
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID RNIC_ShowRnicPdpStats(VOS_UINT8 ucRmNetId)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtx;

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowRnicPdpStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    pstPdpCtx                           = RNIC_GetPdpCtxAddr(ucRmNetId);

    PS_PRINTF("RNIC %d IPV4 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV4 PDP IPV4ADDR                   %d\n\n", ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ulIpv4Addr);

    PS_PRINTF("RNIC %d IPV6 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV6 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV6 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV6 PDP IPV6ADDR                   %s\n\n", ucRmNetId, pstPdpCtx->stIpv6PdpInfo.aucIpv6Addr);

    PS_PRINTF("RNIC %d IPV4V6 PDP STATUS                   %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4V6 PDP RABID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4V6 PDP PDNID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV4ADDR                 %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ulIpv4Addr);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV6ADDR                 %s\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.aucIpv6Addr);
}

/*****************************************************************************
 函 数 名  : RNIC_ShowUlProcStats
 功能描述  : 显示RNIC上行统计信息
 输入参数  : ucRmNetId : 网卡ID
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年01月12日
      作    者   : S62952
      修改内容   : 新生成函数
    2.日    期   : 2012年11月23日
      作    者   : f00179208
      修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_VOID RNIC_ShowULProcStats(VOS_UINT8 ucRmNetId)
{
    PS_PRINTF("NET TX RMNETID ERR NUM                                 %d\n", g_stRnicMntnStats.ulNetTxRmNetIdErrNum);
    PS_PRINTF("SPE TX PORTID ERR NUM                                  %d\n", g_stRnicMntnStats.ulSpeTxPortIdErrNum);

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowUlProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* 上行统计量 */
    PS_PRINTF("RNIC %d流控状态                                        %d\n", ucRmNetId, g_stRnicCtx.astSpecCtx[ucRmNetId].enFlowCtrlStatus);
    PS_PRINTF("RNIC %d收到上行IPV4数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4PktNum);
    PS_PRINTF("RNIC %d收到上行IPV6数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv6PktNum);
    PS_PRINTF("IPV4V6类型激活时RNIC %d收到上行数据的个数IPV4IPV6      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4v6PktNum);
    PS_PRINTF("RNIC %d未激活时收到上行数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvUndiaPktNum);
    PS_PRINTF("RNIC %d上行发送给ADS数据的个数                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktNum);
    PS_PRINTF("RNIC %d调ADS发送上行数据失败的个数                     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktFailNum);
    PS_PRINTF("RNIC %d未拨上号前上行收到IPV4广播包的个数              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlIpv4BrdcstPktNum);
    PS_PRINTF("RNIC %d上行转换为IMM_ZC失败的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlImmzcFailPktNum);
    PS_PRINTF("RNIC %d上行去除MAC头失败的个数                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRmvMacHdrFailPktNum);
    PS_PRINTF("RNIC %d网卡私有数据错误丢掉上行数据包的个数            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetCardDiscardNum);
    PS_PRINTF("RNIC %d网卡ID错误丢掉上行数据包的个数                  %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetIdDiscardNum);
    PS_PRINTF("RNIC %dModem ID错误丢掉上行数据包的个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlModemIdDiscardNum);
    PS_PRINTF("RNIC %d流控丢掉上行数据包的个数                        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlFlowCtrlDiscardNum);
    PS_PRINTF("RNIC %d收到错误数据包的个数非ipv4ipv6包                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvErrPktNum);
    PS_PRINTF("RNIC %d成功上报APP按需拨号                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpSucc);
    PS_PRINTF("RNIC %d上报APP按需拨号失败                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpFail);
    PS_PRINTF("RNIC %d成功上报APP断开拨号                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownSucc);
    PS_PRINTF("RNIC %d上报APP断开拨号失败                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownFail);

    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        PS_PRINTF("拨号模式                                           %d\n", g_stRnicCtx.stDialMode.enDialMode);
        PS_PRINTF("按需拨号是否上报事件                               %d\n", g_stRnicCtx.stDialMode.enEventReportFlag);
        PS_PRINTF("按需拨号断开时间                                   %d\n", g_stRnicCtx.stDialMode.ulIdleTime);
    }

    PS_PRINTF("RNIC %d RAB ID错误，RNIC丢弃的数据包个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRabIdErr);
    PS_PRINTF("RNIC %d PDN ID错误，RNIC丢弃的数据包个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlPdnIdErr);

    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ShowDLProcStats
 功能描述  : 显示RNIC下行统计信息
 输入参数  : ucRmNetId : 网卡ID
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年01月12日
      作    者   : S62952
      修改内容   : 新生成函数
    2.日    期   : 2012年11月23日
      作    者   : f00179208
      修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_VOID RNIC_ShowDLProcStats(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* 下行统计量 */
    PS_PRINTF("RNIC %d收到下行IPV4数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv4PktNum);
    PS_PRINTF("RNIC %d收到下行IPV6数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv6PktNum);
    PS_PRINTF("RNIC %d发送下行数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktNum);
    PS_PRINTF("RNIC %d发送下行数据失败的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktFailNum);
    PS_PRINTF("RNIC %d收到下行数据包大于MTU的个数                 %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvBigPktNum);
    PS_PRINTF("RNIC %d网卡未激活丢弃的数据个数                    %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlDiscardPktNum);
    PS_PRINTF("RNIC %d下行加MAC头失败的个数                       %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlAddMacHdFailNum);
    PS_PRINTF("RNIC %d网卡私有数据错误丢掉下行数据包的个数        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetCardDiscardNum);
    PS_PRINTF("RNIC %d网卡ID错误丢掉下行数据包的个数              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetIdDiscardNum);
    PS_PRINTF("RNIC %d收到错误数据包的个数非ipv4ipv6包            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvErrPktNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ShowResetStats
 功能描述  : 显示RNIC信号量初始化信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年04月15日
      作    者   : f00179208
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID RNIC_ShowResetStats(VOS_VOID)
{
    PS_PRINTF("模块初始化标识                              %d\n", g_astRnicStats[0].ulSemInitFlg);
    PS_PRINTF("当前的二进制信号量                          %p\n", g_stRnicCtx.hResetSem);
    PS_PRINTF("创建的二进制信号量                          %p\n", g_astRnicStats[0].hBinarySemId);
    PS_PRINTF("创建二进制信号量失败次数                    %d\n", g_astRnicStats[0].ulCreateBinarySemFailNum);
    PS_PRINTF("锁二进制信号量失败次数                      %d\n", g_astRnicStats[0].ulLockBinarySemFailNum);
    PS_PRINTF("最后一次锁二进制信号量失败原因              %x\n", g_astRnicStats[0].ulLastBinarySemErrRslt);
    PS_PRINTF("复位成功的次数                              %d\n", g_astRnicStats[0].ulResetSucessNum);
}

/* Added by m00217266 for L-C互操作项目, 2014-2-19, begin */
/*****************************************************************************
 函 数 名  : RNIC_Rmnet_Config_Check_Info
 功能描述  : 打印网卡配置信息检验失败的统计信息
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ShowRmnetConfigCheckInfo(VOS_VOID)
{
    PS_PRINTF("Totla req                           %d\n", g_stRnicRmnetConfigCheckInfo.ucTotlaCnt);
    PS_PRINTF("Modem type err                      %d\n", g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt);
    PS_PRINTF("Rmnet id err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt);
    PS_PRINTF("Modem ID err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt);
    PS_PRINTF("Pdn ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt);
    PS_PRINTF("Rab ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt);
    PS_PRINTF("Rmnet status err                    %d\n", g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt);
    PS_PRINTF("IP type err                         %d\n", g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt);
    PS_PRINTF("Send err                            %d\n", g_stRnicRmnetConfigCheckInfo.ucSendErrCnt);
    PS_PRINTF("Success                             %d\n", g_stRnicRmnetConfigCheckInfo.ucSuccCnt);
}
/* Added by m00217266 for L-C互操作项目, 2014-2-19, end */

/*****************************************************************************
 函 数 名  : RNIC_Help
 功能描述  : RNIC调试信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年01月12日
      作    者   : S62952
      修改内容   : 新生成函数
    2.日    期   : 2012年11月23日
      作    者   : f00179208
      修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_VOID RNIC_Help(VOS_VOID)
{

    PS_PRINTF("********************RNIC调试信息************************\n");
    PS_PRINTF("RNIC_ShowULProcStats  ucRmNetId                 显示指定RNIC网卡上行统计信息\n");
    PS_PRINTF("RNIC_ShowDLProcStats  ucRmNetId                 显示指定RNIC网卡下行统计信息\n");
    PS_PRINTF("RNIC_ShowRnicPdpStats ucRmNetId                 显示指定RNIC网卡PDP激活信息\n");
    PS_PRINTF("RNIC_ShowResetStats                             显示指定RNIC复位状态信息\n");

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ShowDataFromIpStack
 功能描述  : 打印收到IP协议栈的数据
 输入参数  : pstSkb   :SKBUF数据首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年04月25日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
)
{
    VOS_UINT32                          i;

    PS_PRINTF("RNIC_ShowDataFromIpStack: data len is %d. \r\n", pstSkb->len);

    PS_PRINTF("RNIC_ShowDataFromIpStack: data content is: \r\n");

    for (i = 0; i < pstSkb->len; i++)
    {
        if (pstSkb->data[i] > 0xf)
        {
            PS_PRINTF("%x", pstSkb->data[i]);
        }
        else
        {
            PS_PRINTF("0%x", pstSkb->data[i]);
        }
    }

    PS_PRINTF("\r\n");

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



