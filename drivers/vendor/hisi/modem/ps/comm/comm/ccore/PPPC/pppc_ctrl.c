

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ppp_inc.h"
#include "v_int.h"
#include "AtPppInterface.h"
#include "PppInterface.h"
#include "fwd_ppp.h"
#include "pppc_ctrl.h"
#include "taf_aps_ppp_pif.h"
#include "TTFLink.h"
#include "VosTaskPrioDef.h"
#include "NVIM_Interface.h"
#include "siapppih.h"
#include "pppc_pa_agent.h"
#include "CdsPppInterface.h"

#include "TTFMem.h"
#include "cttf_1x_rrlp_data_pif.h"
#include "ppp_trans_data_pif.h"
#include "rlp_ppp_pub_pif.h"
#include "cttf_1x_ppp_data_pif.h"
#include "cttf_hrpd_pa_public_pif.h"

#include "TtfNvInterface.h"
#include "pppc_eap_aka.h"
#include "pppc_ctrl.h"

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
#include "hdlc_hardware.h"
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_CTRL_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern VOS_MSG_HOOK_FUNC                vos_MsgHook; /* AT2D01724 */

/* PPP的上下文信息 */
PPPC_CONTEXT_INFO_STRU                  g_stPppContext;

/* PPPC的任务ID */
VOS_UINT32                              g_ulPppcTaskId;

/* APS消息链表,目前需要挂入链表的只有激活和去激活消息,收到本地去激活IND直接清除资源无需链表管理 */
TTF_LINK_ST                             g_stApsCmdLink;

/* PPP上下行队列从空到非空的通知消息计数 */
PPPC_DATA_Q_NOTIFY_CNT_STRU             g_stDataQNotifyCnt;

/* 存放进行PPP封装之后的CDS上行数据 */
VOS_UINT8                               g_aucUlEncapData[PPPC_MAX_UL_DATA_LEN];

PPPC_DATA_UL_ENCAP_MEM_STRU             g_astUlEncapMem[2];

/* PPPC处理次数达到门限之后跳出PPPC任务唤醒定时器 */
volatile HTIMER                         g_hReachMaxProcTimer = VOS_NULL_PTR;

/* PPPC接收到terminate request后起的restart timer, 等待1s后再向taf发送deact notify */
volatile HTIMER                         g_hRestartTimer     = VOS_NULL_PTR;
PS_BOOL_ENUM_UINT8                      g_ucLcpTermMask     = PS_FALSE;

/* PPPC接收到PA的接入鉴权通知后延时处理等到收到BSC的接入鉴权LCP协商报文后再处理 */
volatile HTIMER                         g_hAADelayTimer     = VOS_NULL_PTR;

/* PPP报文上行链表 */
TTF_LINK_ST                             g_stPppUlLink;

/* PPP报文下行链表 */
TTF_LINK_ST                             g_stPppDlLink;

/* 下行报文重组分片缓存链表 */
extern TTF_LINK_ST                      g_stPppRebuildIncompleteSliceLink;

/* PPPC的数据队列统计信息结构体 */
PPP_DATA_Q_STAT_STRU                    g_stPppcDataQueueStats;

/* 当PPPC处理次数达到门限时会跳出任务并启动定时器处理,此标志位表示定时器是否超时 */
PS_BOOL_ENUM_UINT8                      g_enIsReachTimeout = PS_TRUE;

/* 收到HRPD/eHRPD的激活消息时要分别起定时器,去激活不需要可以立刻处理 */
/* 0:HRPD 1:eHRPD 2:PDN */
PPPC_ACT_HRPD_DELAY_PROC_TIMER_STRU     g_astActHrpdTimer[PPPC_ACCESS_AUTH_DELAY_PROC_TIMER_MAX_NUM];

/* 判断是否是初始的接入鉴权,收到PA的接入鉴权通知时置为PS_TRUE */
PS_BOOL_ENUM_UINT8                      g_enInitAccessAuth  = PS_FALSE;

#ifdef PPPC_HDLC_ST_TEST
VOS_UINT16                              g_usPppcUlDataProto = 0x0021;
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : PPPC_ShowPppContext
 功能描述  : 获取PPP上下文信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月25日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ShowPppContext(VOS_VOID)
{
    vos_printf("********************PPPC测试信息************************\n");
    vos_printf("enRatMode:            %d\n", g_stPppContext.enRatMode);
    vos_printf("enDialMode:           %d\n", g_stPppContext.enDialMode);
    vos_printf("enRatMode:            %d\n", g_stPppContext.enModemId);
    vos_printf("ulSendPid:            %d\n", g_stPppContext.ulSendPid);
    vos_printf("usMtu:                %d\n", g_stPppContext.usMru);
    vos_printf("ulPppIdBitMask:       %d\n", g_stPppContext.ulPppIdBitMask);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ShowDLProcStats
 功能描述  : 获取PPP下行数据信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ShowDLProcStats(VOS_VOID)
{
    vos_printf("\n");
    vos_printf("********************PPPC下行数据信息************************\n");
    vos_printf("PPPC收到的下行数据包总个数:            %d\n",
                g_stPppcDataQueueStats.ul1xDlFrameRcvCnt + g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt);
    vos_printf("其中  1X模式收到的下行数据包总个数:    %d\n", g_stPppcDataQueueStats.ul1xDlFrameRcvCnt);
    vos_printf("            收到的下行协商报文个数:    %d\n", g_stPppcDataQueueStats.ul1xDlNegoRcvCnt);
    vos_printf("            发送的下行IP包个数:        %d\n", g_stPppcDataQueueStats.ul1xDlIPDataSndCnt);
    vos_printf("      HRPD模式收到的下行数据包总个数:  %d\n", g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt);
    vos_printf("            收到的下行协商报文个数:    %d\n", g_stPppcDataQueueStats.ulHrpdDlNegoRcvCnt);
    vos_printf("            发送的下行IP包个数:        %d\n", g_stPppcDataQueueStats.ulHrpdDlIPDataSndCnt);
    vos_printf("PPPC的存储下行数据链表的最大节点数:    %d\n", g_stPppcDataQueueStats.ulDlDataQMaxCnt);
    vos_printf("PPPC的下行数据链表的当前节点数:        %d\n", g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt);
    vos_printf("PPPC的下行数据入队数:                  %d\n", g_stPppcDataQueueStats.ulDlDataQEnqueueMsgCnt);
    vos_printf("PPPC的下行数据出队处理数:              %d\n", g_stPppcDataQueueStats.ulDlDataQProcMsgCnt);

    vos_printf("HDLC下行内存申请次数:                  %d\n", g_stPppcDataQueueStats.ulMemAllocDownlinkCnt);
    vos_printf("HDLC下行内存申请失败次数:              %d\n", g_stPppcDataQueueStats.ulMemAllocDownlinkFailCnt);
    vos_printf("HDLC硬件解封装IP包数:                  %d\n", g_stPppcDataQueueStats.ulDownlinkSndDataCnt);

    vos_printf("PPPC下行队列节点个数:                  %d\n", g_stPppDlLink.ulCnt);
    vos_printf("\n");

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ShowULProcStats
 功能描述  : 获取PPP上行数据信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ShowULProcStats(VOS_VOID)
{
    vos_printf("\n");
    vos_printf("************************************************************\n");
    vos_printf("****当前文件FILE ID*****[%d]\n", PS_FILE_ID_PPPC_CTRL_C);
    vos_printf("********************PPPC上行数据信息************************\n");
    vos_printf("PPPC收到的上行数据包总个数:            %d\n",
                g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt + g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt);
    vos_printf("其中  1X模式收到的上行数据:            %d\n", g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt);
    vos_printf("            发送的上行协商报文个数:    %d\n", g_stPppcDataQueueStats.ul1xUlNegoSndCnt);
    vos_printf("            发送的上行IP包个数:        %d\n", g_stPppcDataQueueStats.ul1xUlIPDataSndCnt);
    vos_printf("      HRPD模式收到的上行数据:          %d\n", g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt);
    vos_printf("            发送的上行协商报文个数:    %d\n", g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt);
    vos_printf("            发送的上行IP包个数:        %d\n", g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt);
    vos_printf("PPPC的存储上行数据链表的最大节点数:    %d\n", g_stPppcDataQueueStats.ulUlDataQMaxCnt);
    vos_printf("PPPC的上行数据链表的当前节点数:        %d\n", g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt);
    vos_printf("PPPC的上行数据入队数:                  %d\n", g_stPppcDataQueueStats.ulUlDataQEnqueueMsgCnt);
    vos_printf("PPPC的上行数据出队处理数:              %d\n", g_stPppcDataQueueStats.ulUlDataQProcMsgCnt);

    vos_printf("HDLC上行内存申请次数:                  %d\n", g_stPppcDataQueueStats.ulMemAllocUplinkCnt);
    vos_printf("HDLC上行内存申请失败次数:              %d\n", g_stPppcDataQueueStats.ulMemAllocUplinkFailCnt);
    vos_printf("HDLC硬件封装有效帧数:                  %d\n", g_stPppcDataQueueStats.ulUplinkSndDataCnt);
    vos_printf("HDLC其他内存释放次数:                  %d\n", g_stPppcDataQueueStats.ulMemFreeCnt);

    vos_printf("PPPC上行队列节点个数:                  %d\n", g_stPppUlLink.ulCnt);

    vos_printf("\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPP_GetUlEncapDataPtr
 功能描述  : 获取上行封装PPP帧数据缓存地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月19日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 *PPP_GetUlEncapDataPtr(VOS_VOID)
{
    return g_aucUlEncapData;
}

/*****************************************************************************
 函 数 名  : PPP_InitEncapDataPtr
 功能描述  : 初始化上行封装PPP帧数据缓存数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月19日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_InitEncapDataPtr(VOS_VOID)
{
    PS_MEM_SET(g_aucUlEncapData, 0, sizeof(g_aucUlEncapData));
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SetInitAccessAuthMode
 功能描述  : 设置初始携手模式
 输入参数  : enAccessAuth    初始携手模式
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月8日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SetInitAccessAuthMode(PS_BOOL_ENUM_UINT8 enAccessAuth)
{
    g_enInitAccessAuth  = enAccessAuth;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetInitAccessAuthMode
 功能描述  : 获取初始协商模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月8日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_GetInitAccessAuthMode(VOS_VOID)
{
    return g_enInitAccessAuth;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_IncreaseNegoRcvCnt
 功能描述  : 收到的PPP协商报文数加一
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_1X_IncreaseNegoRcvCnt(VOS_VOID)
{
    g_stPppcDataQueueStats.ul1xDlNegoRcvCnt++;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_IncreaseNegoRcvCnt
 功能描述  : 收到的PPP协商报文数加一
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HRPD_IncreaseNegoRcvCnt(VOS_VOID)
{
    g_stPppcDataQueueStats.ulHrpdDlNegoRcvCnt++;
    return;
}



/*****************************************************************************
 函 数 名  : PPP_GetActPppHeadNode
 功能描述  : 获取激活PPP消息的头节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID *PPP_GetActPppHeadNode()
{
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

    return (VOS_VOID *)pstApsCurrHeadNode;
}

/*****************************************************************************
 函 数 名  : PPP_GetConfigUserName
 功能描述  : 获取用户名
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : c00184031
    修改内容   : 新生成函数
  2.日    期   : 2015年05月29日
    作    者   : W00316385
    修改内容   : 区分模式

*****************************************************************************/
VOS_UINT32 PPP_GetConfigUserName
(
    VOS_UINT8                          *pucUserName,
    VOS_UINT32                          ulPppId
)
{
    VOS_UINT32                          ulUserNameLen;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;


    if (VOS_NULL_PTR == pucUserName)
    {
        PPPC_WARNING_LOG("parameter is NULL.");

        return VOS_ERR;
    }

    pstPppCont  = &g_stPppContext;
    /* 判断当前是否正在进行接入鉴权 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)ulPppId);
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        ulUserNameLen = pstPppCont->stHrpdContext.ucAccessAuthLen;

        /* 已经成功从卡中读取了接入鉴权的NAI信息 */
        if ((0 != ulUserNameLen) && (ulUserNameLen <= CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN))
        {
            VOS_StrNCpy((VOS_CHAR *)pucUserName,
                (VOS_CHAR *)(pstPppCont->stHrpdContext.aucAccessAuthUserName),
                ulUserNameLen);
            *(VOS_UINT8 *)(pucUserName + ulUserNameLen) = '\0';

            return VOS_OK;
        }

        /* 尝试根据IMSI构造NAI信息 */
        return PPPC_UIM_BuildNAIByIMSI(pucUserName, CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN + 1);
    }

    ulUserNameLen = pstPppCont->ulUserNameLen;

    VOS_StrNCpy((VOS_CHAR *)pucUserName,
        (VOS_CHAR *)(pstPppCont->aucUserName),
        ulUserNameLen);
    *(VOS_UINT8 *)(pucUserName + ulUserNameLen) = '\0';

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_GetConfigPassWord
 功能描述  : 获取密码
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : c00184031
    修改内容   : 新生成函数
  2.日    期   : 2015年05月29日
    作    者   : W00316385
    修改内容   : 区分模式

*****************************************************************************/
VOS_UINT32 PPP_GetConfigPassWord
(
    VOS_UINT8                          *pucPassWd
)
{
    VOS_UINT32                          ulPasswordLen;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;


    if (VOS_NULL_PTR == pucPassWd)
    {
        PPPC_WARNING_LOG("parameter is NULL.");

        return VOS_ERR;
    }

    pstPppCont  = &g_stPppContext;

    ulPasswordLen = pstPppCont->ulPasswordLen;

    VOS_StrNCpy((VOS_CHAR *)pucPassWd,
        (VOS_CHAR *)(pstPppCont->aucPassword),
        ulPasswordLen);
    *(VOS_UINT8 *)(pucPassWd + ulPasswordLen) = '\0';

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_GetDefaultMru
 功能描述  : 获取默认的MRU值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月29日
    作    者   : W00316385
    修改内容   :

*****************************************************************************/
VOS_UINT16 PPP_GetDefaultMru(VOS_VOID)
{
    return g_stPppContext.usMru;
}

/*****************************************************************************
 函 数 名  : PPPC_GetModemId
 功能描述  : 获取PPP的Modem ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : c00199705
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPPC_GetModemId(VOS_VOID)
{
    return g_stPppContext.enModemId;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_GetAppType
 功能描述  : 获取ApplicationType
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月20日
    作    者   : w00316385
    修改内容   :

*****************************************************************************/
VOS_UINT16 PPPC_HRPD_GetAppType(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.aenApplicationType[1];
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_GetStreamNumber
 功能描述  : 获取StreamNumber
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月25日
    作    者   : c00184031
    修改内容   :

*****************************************************************************/
VOS_UINT8 PPPC_HRPD_GetStreamNumber(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucStreamRN = 1;
    VOS_UINT8                           ucStreamSN = 2;
    VOS_UINT32                          ulSteamIndex;
    VOS_UINT32                          ulMaxSteamNum = 3;


    pstPppContext   = &g_stPppContext;

    /* 目前只支持DPA,EMPA场景待后续分析后再添加 */
    for (ulSteamIndex = 0; ulSteamIndex < ulMaxSteamNum; ulSteamIndex++)
    {
        /* stream number等于0为信令,实体中存储的流号从1开始 */
        if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_RN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_RN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_RN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex]))
        {
            ucStreamRN = (VOS_UINT8)(ulSteamIndex + 1);
        }
        else if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_SN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_SN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_SN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex]))
        {
            ucStreamSN = (VOS_UINT8)(ulSteamIndex + 1);
        }
        else
        {
            /* do nothing */
        }
    }

    /* 如果当前正在进行接入鉴权,返回RN的流号 */
    if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId)
    {
        return ucStreamRN;
    }
    else
    {
        return ucStreamSN;
    }
}

/*****************************************************************************
 函 数 名  : PPPC_FidTask
 功能描述  : PPPC任务处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-12-11
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_FidTask(VOS_VOID)
{
    MsgBlock*               pMsg;
    VOS_UINT32              ulEvent;
    VOS_UINT32              ulTaskID;
    VOS_UINT32              ulReturn;
    VOS_UINT32              ulEventMask;
    VOS_UINT32              ulExpectEVENT   = 0;
    VOS_UINT32              ulEventProcFlag = 0;


    ulTaskID = VOS_GetCurrentTaskID();

    if ( PS_NULL_UINT32 == ulTaskID )
    {
        PPPC_ERROR_LOG("PPPC, ERROR, reg Msg Func\r\n");
        return ;
    }

    if ( VOS_OK != VOS_CreateEvent( ulTaskID) )
    {
        PPPC_ERROR_LOG("PPPC, ERROR, create event FAIL\r\n");
        return ;
    }

    g_ulPppcTaskId = ulTaskID;

    ulExpectEVENT        = PPPC_UL_PKT_EVENT | PPPC_DL_PKT_EVENT | VOS_MSG_SYNC_EVENT;
    ulEventMask          = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    for(;;)
    {
        ulReturn = VOS_EventRead( ulExpectEVENT,
                                  ulEventMask,
                                  0,
                                  &ulEvent );

        ulEventProcFlag = 0;

        if(VOS_OK != ulReturn)
        {
            /* 避免出现获取Event失败导致RM任务出现死循环后切换不到其他任务 */
            (VOS_VOID)VOS_TaskDelay(1);
            (VOS_VOID)LogPrint("WTTF_MAC_RLC_UlFidTask::RM read event error.\r\n" );
            continue;
        }

        /* 有上下行报文的处理 */
        if ((PPPC_UL_PKT_EVENT == (ulEvent & PPPC_UL_PKT_EVENT))
            || (PPPC_DL_PKT_EVENT == (ulEvent & PPPC_DL_PKT_EVENT)))
        {

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkOpen();
#endif

            PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkClose();
#endif

            ulEventProcFlag = 1;
        }
        else
        {
            /* PCLINT */
        }

        if (1 == ulEventProcFlag)
        {
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg( ulTaskID );
        if  (VOS_NULL_PTR != pMsg)
        {
            if (VOS_NULL_PTR != vos_MsgHook)
            {
                
                /*lint -e522 by liukai*/
                (VOS_VOID)(vos_MsgHook)((VOS_VOID *)(pMsg));
                /*lint +e522 by liukai*/
            }

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkOpen();
#endif

            PPPC_MsgProc(pMsg);

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkClose();
#endif

            (VOS_VOID)VOS_FreeMsg(MSPS_PID_PPPC, pMsg);
        }
    }
    /*lint +e716*/
}

/*****************************************************************************
 函 数 名  : PPPC_FidInit
 功能描述  : PPPC在C核任务初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-01-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32  ulResult = PS_FAIL;


    switch (ip)
    {
        case   VOS_IP_LOAD_CONFIG:

            /*注册PPPC PID*/
            ulResult = VOS_RegisterPIDInfo(MSPS_PID_PPPC,
                                           PPPC_Init,
                                           PPPC_MsgProc);
            if (VOS_OK != ulResult)
            {
                vos_printf("PPPC_FidInit, register PPPC PID fail!\n");
                return VOS_ERR;
            }

            ulResult = VOS_RegisterMsgTaskEntry(MSPS_FID_PPPC, PPPC_FidTask);
            if( VOS_OK != ulResult )
            {
                vos_printf("PPPC_FidInit, reg msg routine FAIL!,%d\n", ulResult);
                return VOS_ERR;
            }

            ulResult = VOS_RegisterTaskPrio(MSPS_FID_PPPC, PPPC_TASK_PRI);
            if( VOS_OK != ulResult )
            {
                vos_printf("PPPC_FidInit, register priority fail!\n");
                return VOS_ERR;
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

/*****************************************************************************
 函 数 名  : PPPC_QueueInit
 功能描述  : 初始化上下行队列
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-10-30
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_QueueInit(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcDlDataQ;
    TTF_LINK_ST                        *pstPppcUlDataQ;


    /* 初始化下行队列 */
    pstPppcDlDataQ    = &g_stPppDlLink;
    PS_MEM_SET(&g_stPppDlLink, 0, sizeof(g_stPppDlLink));

    TTF_LinkInit(MSPS_PID_PPPC, pstPppcDlDataQ);

    /* 初始化上行队列 */
    pstPppcUlDataQ    = &(g_stPppUlLink);
    PS_MEM_SET(&g_stPppUlLink, 0, sizeof(g_stPppUlLink));

    TTF_LinkInit(MSPS_PID_PPPC, pstPppcUlDataQ);

    /* 初始化队列中待处理消息计数 */
    PS_MEM_SET(&g_stDataQNotifyCnt, 0, sizeof(g_stDataQNotifyCnt));

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearDlDataQ
 功能描述  : 清除下行报文队列
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ClearDlDataQ(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcDlDataQ;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT32                          ulRemainCnt;


    pstPppcDlDataQ    = &g_stPppDlLink;

    /* 释放所有Tx Entity相关的数据、节点缓存 */
    while (TTF_LINK_IS_NOT_EMPTY(pstPppcDlDataQ))
    {
        pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstPppcDlDataQ, &ulRemainCnt);

        /*异常:链表和链表个数不一致时, 容错处理, 返回VOS_NULL_PTR*/
        if (VOS_NULL_PTR == pstDlDataNode)
        {
            return;
        }

        /* 已保证循环释放TTFMemory */
        TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

        pstDlDataNode->pstPduMem = VOS_NULL_PTR;

        /* 释放TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);
        pstDlDataNode = VOS_NULL_PTR;
    }

    PPPC_INFO_LOG("PPP, PPPC_ClearDlDataQ, NORMAL, Clear Stat Info\n");

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearUlDataQ
 功能描述  : 清除上行报文队列
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ClearUlDataQ(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcUlDataQ;
    PPPC_DATA_LINK_NODE_STRU           *pstUlDataNode;
    VOS_UINT32                          ulRemainCnt;


    pstPppcUlDataQ    = &g_stPppUlLink;

    /* 释放所有Tx Entity相关的数据、节点缓存 */
    while (TTF_LINK_IS_NOT_EMPTY(pstPppcUlDataQ))
    {
        pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstPppcUlDataQ, &ulRemainCnt);

        /*异常:链表和链表个数不一致时, 容错处理, 返回VOS_NULL_PTR*/
        if (VOS_NULL_PTR == pstUlDataNode)
        {
            return;
        }

        /* 释放TTFMemory,上行一个节点对应一块TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstUlDataNode->pstPduMem);
        pstUlDataNode->pstPduMem = VOS_NULL_PTR;

        if (VOS_NULL_PTR != pstUlDataNode->pstUlDataInfo)
        {
            /* Free memory allocated for trace */
            PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode->pstUlDataInfo);
            pstUlDataNode->pstUlDataInfo    = VOS_NULL_PTR;
        }

        /* 释放TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);
        pstUlDataNode = VOS_NULL_PTR;
    }

    PPPC_INFO_LOG("PPP, PPPC_ClearUlDataQ, NORMAL, Clear Stat Info\n");

    return;
}

/*****************************************************************************
 函 数 名  : PPP_AdapterTtfMemorytoMBuf
 功能描述  : TtfMemory数据类型转换成MBUF
 输入参数  : pstTtfMem        TTFMemory类型数据
 输出参数  : 无
 返 回 值  : PMBUF_S *        MBUF类型的数据
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
PMBUF_S *PPPC_AdapterTtfMemorytoMBuf(TTF_MEM_ST *pstTtfMem)
{
    PMBUF_S                            *pstMBuf = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstCurrTtfMem = pstTtfMem;
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;


    /* 内部调用保证入参非空 */

    pstMBuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_PPPC, pstCurrTtfMem->usUsed);
    if (VOS_NULL_PTR == pstMBuf)
    {
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
        PPPC_WARNING_LOG("Get MBuf Memory fail!");
        PPP_DBG_ERR_CNT(PPP_PHERR_873);
        return VOS_NULL_PTR;
    }

    while(VOS_NULL_PTR != pstCurrTtfMem)
    {
        pucData     = pstCurrTtfMem->pData;
        if (VOS_NULL_PTR == pucData)
        {
            PPPC_WARNING_LOG1("TTFMemory to MBuf Get Data Ptr fail!", pstCurrTtfMem->usUsed);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

            /* 释放pstMBuf */
            PMBUF_Destroy(pstMBuf);
            PPP_DBG_ERR_CNT(PPP_PHERR_872);
            return VOS_NULL_PTR;
        }

        /* IP包长度不能超过1500字节算上转译字符也不会超过3K,
        每次拷贝都偏移ulTotalDataLength,ulTotalDataLength会在接口内部被刷新 */
        ulRet   = PMBUF_CopyDataFromBufferToPMBuf(pstMBuf,
                                             pstMBuf->ulTotalDataLength,
                                             pstCurrTtfMem->usUsed,
                                             pucData,
                                             MSPS_PID_PPPC);
        if (VOS_OK != ulRet)
        {
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
            PPPC_WARNING_LOG1("Copy Data to MBuf Memory fail!\r\n", ulRet);
            /* 释放pstMBuf */
            PMBUF_Destroy(pstMBuf);
            PPP_DBG_ERR_CNT(PPP_PHERR_874);
            return VOS_NULL_PTR;
        }

        pstCurrTtfMem   = pstCurrTtfMem->pNext;

    }

    TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

    return pstMBuf;
}

/*****************************************************************************
 函 数 名  : PPP_AdapterMBuftoTtfMemory
 功能描述  : MBUF数据类型转换成TTFMemory
 输入参数  : pstMBuf          MBUF类型数据
             ulMemPoolId      申请的内存池Id
             ulOffset         MBUF类型数据偏移量
             ulLength         MBUF类型数据转换为TTFMemory类型的长度
 输出参数  : 无
 返 回 值  : TTF_MEM_ST *     TTFMemory类型的数据
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
TTF_MEM_ST *PPPC_AdapterMBuftoTtfMemory
(
    PMBUF_S                            *pstMBuf,
    VOS_UINT32                          ulMemPoolId,
    VOS_UINT32                          ulOffset,
    VOS_UINT32                          ulLength
)
{
    TTF_MEM_ST                         *pstTtfMem = VOS_NULL_PTR;
    VOS_UINT8                          *pucData;


    if (ulOffset > pstMBuf->ulTotalDataLength)
    {
        return VOS_NULL_PTR;
    }

    pucData     = pstMBuf->stDataBlockDescriptor.pucData + ulOffset;

    /* MBUF转为TTFMemory只可能是递交上行数据时可能需要用到 */
    pstTtfMem   = TTF_MemBlkCopyAlloc(MSPS_PID_PPPC,
                ulMemPoolId, pucData, (VOS_UINT16)ulLength);

    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPPC_WARNING_LOG1("Copy Data to TTFMemory fail!\r\n", ulLength);
        PPP_DBG_ERR_CNT(PPP_PHERR_875);
        return VOS_NULL_PTR;
    }

    return pstTtfMem;
}


/*****************************************************************************
 函 数 名  : PPPC_RcvRlpDlFrame
 功能描述  : PPP模块收到RLP的下行报文
 输入参数  : pstData          数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_RcvRlpDlFrame
(
    VOS_UINT16                          usSeqNr,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
)
{
    /* 内部调用保证入参非空 */


    /* 调用分片重组函数处理 */
    FWD_PppRebuild(usSeqNr, pstData, ucRatMode, ucPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_PrepareUlEncapMem
 功能描述  : 为封装上行数据准备内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_PrepareUlEncapMem(VOS_UINT16 usLen)
{
    VOS_UINT16                          usFrmedMaxLen;
    VOS_UINT16                          usFirstFragmentLen  = 0;
    VOS_UINT16                          usSecendFragmentLen = 0;

    /* 根据(2*原始数据长度+13B)计算 */
    VOS_UINT32                          ulMaxLen            = PPPC_MAX_UL_ENCAP_LEN - 7;


    if ((0 == usLen) || (usLen > ulMaxLen))
    {
        PPPC_WARNING_LOG1("Data len is invalid %d\r\n", usLen);
        return VOS_ERR;
    }

    /* 封装后可能的最大数据长度(2*原始数据长度+13B) */
    usFrmedMaxLen = (VOS_UINT16)(2 * usLen + 13);
    usFirstFragmentLen  = (usFrmedMaxLen >= PPPC_MAX_UL_ENCAP_LEN) ? PPPC_MAX_UL_ENCAP_LEN : usFrmedMaxLen;
    usSecendFragmentLen = (usFrmedMaxLen >= PPPC_MAX_UL_ENCAP_LEN) ? (usFrmedMaxLen - usFirstFragmentLen) : 0;

    /* 申请第一块内存 */
    if (PS_TRUE == g_astUlEncapMem[0].enPtrIsUsed)
    {
        TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[0].pstDataPtr);
        g_astUlEncapMem[0].pstDataPtr = VOS_NULL_PTR;
        g_astUlEncapMem[0].enPtrIsUsed = PS_FALSE;
    }

    g_astUlEncapMem[0].pstDataPtr  = TTF_MemBlkAlloc(MSPS_PID_PPPC,
        TTF_MEM_POOL_ID_UL_DATA, usFirstFragmentLen);

    /* 申请不到内存返回错误 */
    if (VOS_NULL_PTR == g_astUlEncapMem[0].pstDataPtr)
    {
        PPPC_INFO_LOG("Alloc Fail");
        return VOS_ERR;
    }
    g_astUlEncapMem[0].enPtrIsUsed = PS_TRUE;

    if (0 != usSecendFragmentLen)
    {
        /* 申请第二块内存 */
        if (PS_TRUE == g_astUlEncapMem[1].enPtrIsUsed)
        {
            TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[1].pstDataPtr);
            g_astUlEncapMem[1].pstDataPtr = VOS_NULL_PTR;
            g_astUlEncapMem[1].enPtrIsUsed = PS_FALSE;
        }

        g_astUlEncapMem[1].pstDataPtr  = TTF_MemBlkAlloc(MSPS_PID_PPPC,
            TTF_MEM_POOL_ID_UL_DATA, usSecendFragmentLen);

        /* 申请不到内存返回错误 */
        if (VOS_NULL_PTR == g_astUlEncapMem[1].pstDataPtr)
        {
            PPPC_INFO_LOG("Alloc Fail");
            return VOS_ERR;
        }
        g_astUlEncapMem[1].enPtrIsUsed = PS_TRUE;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_DlEnqueueData
 功能描述  : 1X和HRPD公用的下行报文入队接口,内存不在这个接口中释放
 输入参数  : pstPppSdu         PPP数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_DlEnqueueData
(
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode,
    TTF_LINK_ST                        *pstDataLink,
    VOS_UINT32                         *pulNonEmptyEvent
)
{
    VOS_UINT32                          ulTemporyEmptyEvent = PS_FALSE;
    VOS_UINT32                          ulRet;


    /* 将数据结点插入队列尾部 */
    ulRet = TTF_LinkSafeInsertTail(MSPS_PID_PPPC, pstDataLink,
            &(pstDlNode->stNode), &ulTemporyEmptyEvent);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Insert Fail", ulRet);

        return ulRet;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_SendDlDataNotifyCommon
 功能描述  : 下行有数据需要发送通知，1X和HRPD都使用该接口
 输入参数  : pstDataLink         链表
             ulNonEmptyEvent     记录队列是否发生了由空到非空的转变
             ulSendMsgCnt        发送个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SendDlDataNotifyCommon
(
    TTF_LINK_ST                        *pstDataLink,
    VOS_UINT32                          ulSendMsgCnt
)
{
    g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt = TTF_LinkCnt(MSPS_PID_PPPC, pstDataLink);
    if (g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt > g_stPppcDataQueueStats.ulDlDataQMaxCnt)
    {
        /* 刷新下行队列中挂接的最大节点统计值 */
        g_stPppcDataQueueStats.ulDlDataQMaxCnt = g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt;
        PPPC_INFO_LOG1("The DL Quene max count is %d.\n", g_stPppcDataQueueStats.ulDlDataQMaxCnt);
    }

    /*向PPP发送数据处理指示*/
    if (VOS_OK != PPPC_SndDlDataNotify())
    {
        /* 发送消息通知失败，需要清空整个队列 */
        PPPC_ClearDlDataQ();
        PPPC_WARNING_LOG("Send DL data notify fail.");
        return;
    }

    g_stPppcDataQueueStats.ulDlDataQEnqueueMsgCnt += ulSendMsgCnt;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_DlEnqueueData
 功能描述  : 下行HRPD报文入队
 输入参数  : pstPppSdu         PPP数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HRPD_DlEnqueueData(RLP_PPP_HRPD_TRANS_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;   /* 记录队列是否发生了由空到非空的转变 */
    VOS_UINT32                          ulRet;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;


    /* 申请节点 */
    pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstDlNode)
    {
        PPPC_WARNING_LOG("Alloc Fail");

        /* 释放RLP申请的TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstPackets->pstSdu);

        return;
    }

    PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstDlNode->ulPduCnt     = 1;
    pstDlNode->pstPduMem    = pstPackets->pstSdu;
    pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstDlNode->ucStreamNum  = pstPackets->ucStreamNumber;
    pstDlNode->usHigherLayerProtocol  = pstPackets->ucHigherLayerProtocol;

    /* TODO: aucReservLabel needs to copied
    pstDlNode->ucResvLabel  = pstPackets->ucReservationLabel;*/
    pstDlNode->enRatMode    = PPPC_GetRatMode();

    ulRet   = PPPC_DlEnqueueData(pstDlNode, &g_stPppDlLink, &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        /* 释放RLP申请的TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstPackets->pstSdu);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

    /* TODO:目前HRPD数据每次只发一个,后续需要跟PA一起修改为与1X一样一次发送16个 */
    PPPC_SendDlDataNotifyCommon(&g_stPppDlLink, 1);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_FreePacketsTtmMem
 功能描述  : 释放下行报文中的TTF内存
 输入参数  : pstPackets         下行报文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月17日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_FreePacketsTtmMem(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulLoop;


    /* 内部调用保证入参非空 */

    for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ulLoop++)
    {
        if (VOS_NULL_PTR != pstPackets->astDeliverSdus[ulLoop].pstSdu)
        {
            /* 释放RLP申请的TTF内存 */
            TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_DlEnqueueData
 功能描述  : 下行1X报文入队
 输入参数  : pstPppSdu         PPP数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_1X_DlEnqueueData(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;   /* 记录队列是否发生了由空到非空的转变 */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPduIndex      = 0;
    TTF_LINK_ST                        *pstDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;

#if (FEATURE_OFF == FEATURE_HARDWARE_HDLC_ON_CCPU)
    TTF_MEM_ST                         *pstTtfMem       = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstNextTtfMem   = VOS_NULL_PTR;
#endif

    pstDataLink    = &g_stPppDlLink;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ++ulLoop)
     {
         if (VOS_NULL_PTR == pstPackets->astDeliverSdus[ulLoop].pstSdu)
         {
             PPPC_WARNING_LOG1("pstSdu is null. ulLoop:%d.", ulLoop);
             continue;
         }

         /* 申请节点 */
         pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
         if (VOS_NULL_PTR == pstDlNode)
         {
             PPPC_WARNING_LOG1("Alloc Fail", ulLoop);

             /* 释放RLP申请的TTF内存 */
             TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);

             continue;
         }

         PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
         pstDlNode->pstPduMem    = pstPackets->astDeliverSdus[ulLoop].pstSdu;
         pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
         pstDlNode->ucPdnId      = pstPackets->ucPdnId;
         pstDlNode->enRatMode    = PPPC_RAT_MODE_1X;
         pstDlNode->pstPduMem->usApp        = pstPackets->astDeliverSdus[ulPduIndex].usSeq;

         ulRet = PPPC_DlEnqueueData(pstDlNode, pstDataLink, &ulNonEmptyEvent);
         if (VOS_OK != ulRet)
         {
             PPPC_WARNING_LOG1("Insert Fail", ulLoop);

             /* 释放RLP申请的TTF内存 */
             TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);

             /* 释放节点 */
             TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

             continue;
         }
     }

#else

    /* 申请节点 */
    pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstDlNode)
    {
        PPPC_WARNING_LOG("Alloc Fail");

        PPPC_FreePacketsTtmMem(pstPackets);

        return;
    }

    /* 节点初始化 */
    PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstDlNode->ucPdnId      = pstPackets->ucPdnId;
    pstDlNode->enRatMode    = PPPC_RAT_MODE_1X;
    pstDlNode->pstPduMem    = pstPackets->astDeliverSdus[ulPduIndex].pstSdu;

    pstTtfMem               = pstDlNode->pstPduMem;
    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPPC_WARNING_LOG("TTF Mem is null");

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

    pstTtfMem->usApp        = pstPackets->astDeliverSdus[ulPduIndex].usSeq;

    for (ulLoop = 1; ulLoop < pstPackets->ucSduCount; ++ulLoop)
    {
        pstTtfMem->pNext    = pstPackets->astDeliverSdus[ulLoop].pstSdu;
        pstNextTtfMem       = pstTtfMem->pNext;

        if (VOS_NULL_PTR == pstTtfMem->pNext)
        {
            PPPC_WARNING_LOG1("pstSdu is null. ulLoop:%d.", ulLoop);
            continue;
        }

        /* usApp用于存储序列号 */
        pstTtfMem->pNext->usApp = pstPackets->astDeliverSdus[ulLoop].usSeq;
        pstTtfMem               = pstNextTtfMem;
        ulPduIndex++;
    }
    pstTtfMem->pNext        = VOS_NULL_PTR;

    pstDlNode->ulPduCnt     = ulPduIndex + 1;
    /* 节点赋值完毕插入队列 */
    ulRet = PPPC_DlEnqueueData(pstDlNode, pstDataLink, &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Insert Fail", ulLoop);

        PPPC_FreePacketsTtmMem(pstPackets);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

#endif

    /* 通知PPPC处理下行链表 */
    PPPC_SendDlDataNotifyCommon(pstDataLink, pstPackets->ucSduCount);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_UlEnqueueData
 功能描述  : 1X和HRPD公用的上行数据入队接口,节点内存在这个接口中释放
 输入参数  : pstNode         上行节点
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月05日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_UlEnqueueData(PPPC_DATA_LINK_NODE_STRU *pstUlNode)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;    /* 记录队列是否发生了由空到非空的转变 */
    VOS_UINT32                          ulRet;
    TTF_LINK_ST                        *pstUlDataLink;


    pstUlDataLink    = &g_stPppUlLink;

    /* 将数据结点插入队列尾部 */
    ulRet = TTF_LinkSafeInsertTail(MSPS_PID_PPPC, pstUlDataLink,
            &(pstUlNode->stNode), &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        /* 释放TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstUlNode->pstPduMem);

        if (VOS_NULL_PTR != pstUlNode->pstUlDataInfo)
        {
            /* Free memory allocated for trace */
            PS_MEM_FREE(MSPS_PID_PPPC, pstUlNode->pstUlDataInfo);
            pstUlNode->pstUlDataInfo    = VOS_NULL_PTR;
        }

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlNode);

        PPPC_WARNING_LOG("The UL data node is failed to insert!\n");
        return;
    }

    g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt = TTF_LinkCnt(MSPS_PID_PPPC, pstUlDataLink);
    if (g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt > g_stPppcDataQueueStats.ulUlDataQMaxCnt)
    {
        /* 刷新上行队列中挂接的最大节点统计值 */
        g_stPppcDataQueueStats.ulUlDataQMaxCnt = g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt;
        PPPC_INFO_LOG1("The UL Quene max count is %d.\n", g_stPppcDataQueueStats.ulUlDataQMaxCnt);
    }

    /*向PPP发送数据处理指示*/
    if (VOS_OK != PPPC_SndUlDataNotify())
    {
        PPPC_WARNING_LOG("Send UL data notify fail.\n");
        /* 发送消息通知失败，需要清空整个队列 */
        PPPC_ClearUlDataQ();
        return;
    }

    g_stPppcDataQueueStats.ulUlDataQEnqueueMsgCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_UlEnqueueData
 功能描述  : PPP模块上行HRPD数据报文入队
 输入参数  : pstNode         数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月05日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HRPD_UlEnqueueData(const CDS_CDMA_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    TTF_MEM_ST                         *pstTTFMem;


    /* 申请节点 */
    pstUlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstUlNode)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_INFO_LOG("Alloc mem fail.");
        return;
    }

    PPP_MemSet(pstUlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstUlNode->ulPduCnt     = 1;
    pstUlNode->pstPduMem    = pstPppSdu->pstSdu;
    pstUlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstUlNode->ucPdnId      = pstPppSdu->ucPdnId;
    pstUlNode->enRatMode    = PPPC_GetRatMode();
    pstUlNode->ucStreamNum  = PPPC_HRPD_GetStreamNumber(1);

    /* enIpDataType 用于rrlp */
    pstUlNode->enIpDataType = TTF_ParseIpDataType(MSPS_PID_PPPC, pstPppSdu->pstSdu);

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    if (PPPC_RAT_MODE_EHRPD == pstUlNode->enRatMode)
    {
        TTF_MEM_RESUME_TO_HDR(pstUlNode->pstPduMem, 1);
        pstUlNode->pstPduMem->pData[0] = pstUlNode->ucPdnId;
    }
#endif

    TTF_NodeInit(&(pstUlNode->stNode));

    /* 上行节点在公共入队函数中释放 */
    PPPC_UlEnqueueData(pstUlNode);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_UlEnqueueData
 功能描述  : PPP模块上行1X数据报文入队
 输入参数  : pstNode         数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月04日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_1X_UlEnqueueData(const CDS_CDMA_1X_TRANS_DATA_STRU *pstPppSdu)
{
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    TTF_MEM_ST                         *pstTTFMem;


    /* 申请节点 */
    pstUlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstUlNode)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_INFO_LOG("Alloc mem fail.");
        return;
    }

    PPP_MemSet(pstUlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstUlNode->ulPduCnt     = 1;
    pstUlNode->pstPduMem    = pstPppSdu->pstSdu;
    pstUlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstUlNode->ucPdnId      = pstPppSdu->ucPdnId;
    pstUlNode->enRatMode    = PPPC_RAT_MODE_1X;
    TTF_NodeInit(&(pstUlNode->stNode));

    /* enIpDataType 用于rrlp */
    pstUlNode->enIpDataType = TTF_ParseIpDataType(MSPS_PID_PPPC, pstPppSdu->pstSdu);

    /* pstUlDataInfo用于rrlp上行trace勾取 */
    pstUlNode->pstUlDataInfo    = (PS_DATA_EXT_INFO_STRU *)PS_MEM_ALLOC(
        MSPS_PID_PPPC, sizeof(PS_DATA_EXT_INFO_STRU));
    if (VOS_NULL_PTR == pstUlNode->pstUlDataInfo)
    {
        /* 释放TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstUlNode->pstPduMem);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlNode);

        PPPC_WARNING_LOG("pstUlDataInfo is failed to alloc!\n");
        return;
    }

    FWD_PppFillDataInfo(pstPppSdu->pstSdu->pData, pstUlNode->pstUlDataInfo);

    /* 上行节点在公共入队函数中释放 */
    PPPC_UlEnqueueData(pstUlNode);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_DlSoftProc
 功能描述  : PPP下行软件处理
 输入参数  : pstDlDataLink         下行链路
             ucPppId                PPP ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_DlSoftProc
(
    TTF_LINK_ST                        *pstDlDataLink,
    VOS_UINT8                           ucPppId
)
{
    TTF_MEM_ST                         *pstTtfMem;
    TTF_MEM_ST                         *pstNextTtfMem;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT32                          ulRemainCnt;
    VOS_UINT16                          usSeq;
    VOS_UINT32                          ulPduIndex;


    pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
        pstDlDataLink, &ulRemainCnt);

    /* 队列为空的时候返回空指针 */
    if ( VOS_NULL_PTR == pstDlDataNode )
    {
        PPPC_WARNING_LOG("PPP DL Queue is Empty!\r\n");
        return;
    }

    pstTtfMem   = pstDlDataNode->pstPduMem;
    usSeq       = pstTtfMem->usApp;

    for (ulPduIndex = 0; ulPduIndex < pstDlDataNode->ulPduCnt; ulPduIndex++)
    {
        /* 入队时已保证所有的TTFMEM非空 */
        pstNextTtfMem   = pstTtfMem->pNext;

        /* 下行报文出队统计 */
        g_stPppcDataQueueStats.ulDlDataQProcMsgCnt++;

        /* 如果TTFMEM中的usUsed大于可能的最大分片报文长度,跳过此分片处理下一片报文 */
        if (pstTtfMem->usUsed > TTF_BIT2BYTE(PPPC_MAX_FRAGMENT_BIT_LEN))
        {
            PPPC_WARNING_LOG1("Ttf Mem used len is invalid:%d\r\n", pstTtfMem->usUsed);
        }
        else
        {
            PPPC_RcvRlpDlFrame(usSeq, pstTtfMem, pstDlDataNode->enRatMode, ucPppId);
        }

        if (VOS_NULL_PTR != pstNextTtfMem)
        {
            pstTtfMem   = pstNextTtfMem;
            usSeq       = pstNextTtfMem->usApp;
        }
        else
        {
            break;
        }
    }

    TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

    /* 释放节点 */
    TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SetupAAPppByState
 功能描述  : 判断接入鉴权PPP的状态决定是否需要Setup
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月14日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SetupAAPppByState(VOS_VOID)
{
    PPPINFO_S                          *pstPppInfo;
    PPPLCPINFO_S                       *pstLcpInfo;


    pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];

    /* 接入鉴权只支持CHAP, 而且不能省略 */
    PPPC_SetAuthSwitch(PPPC_AUTH_SWITCH_OFF, PPPC_AUTH_SWITCH_ON);

    if (VOS_NULL_PTR == pstPppInfo->pstLcpInfo)
    {
        /* 如果LCP实体没有创建需要Setup接入鉴权PPP */
        PPPC_SetupPpp(PPPC_PPP_ID_FOR_ACCESS_AUTH);
    }
    else
    {
        pstLcpInfo  = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
        if ((PPP_STATE_INITIAL == pstLcpInfo->stFsm.ucState)
            || (PPP_STATE_STARTING == pstLcpInfo->stFsm.ucState)
            || (PPP_STATE_CLOSED == pstLcpInfo->stFsm.ucState))
        {
           /* 如果状态为initial/starting/closed需要Setup接入鉴权PPP */
            PPPC_SetupPpp(PPPC_PPP_ID_FOR_ACCESS_AUTH);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ActAccessAuth
 功能描述  : 进行接入鉴权
 输入参数  : pstPppInfo             PPP实体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ActAccessAuth(PPPINFO_S *pstPppInfo)
{
    VOS_UINT8                           ucPppId;
    VOS_UINT32                          ulRet;

    ucPppId = (VOS_UINT8)pstPppInfo->ulRPIndex;

    if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId)
    {
        /* 设置接入鉴权状态 */
        if (PS_FALSE == PPPC_IsDoingAccessAuth(ucPppId))
        {
            /* 通知RPA接入鉴权开始 */
            PPPC_HRPD_SendRpaAccessAuthPhaseInd();

            /* 设置接入鉴权标志位 */
            PPPC_ChangeAccessAuthState(PS_TRUE, PPPC_PPP_ID_FOR_ACCESS_AUTH);

            /* 如果PA给PPPC发送过接入鉴权通知说明是初始协商 */
            if (PS_TRUE == PPPC_GetInitAccessAuthMode())
            {
                if (VOS_NULL_PTR != g_hAADelayTimer)
                {
                    ulRet = VOS_StopRelTimer((HTIMER*)&g_hAADelayTimer);
                    if (VOS_OK != ulRet)
                    {
                        PPPC_WARNING_LOG("Stop AA delay proc timer fail!");
                    }
                    g_hAADelayTimer = VOS_NULL_PTR;
                }
            }

        }

     }
}

/*****************************************************************************
 函 数 名  : PPPC_DlDequeueProc
 功能描述  : 下行报文出队处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_DlDequeueProc()
{
    TTF_LINK_ST                        *pstDlDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT8                           ucPppId = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRemainCnt;
#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT32                          ulDealCnt = 0;
#endif


    pstDlDataLink  = &g_stPppDlLink;

    pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstDlDataLink);
    /* 队列为空的时候返回空指针 */
    if ( VOS_NULL_PTR == pstDlDataNode )
    {
        PPPC_WARNING_LOG("PPP DL Queue is Empty!\r\n");
        return;
    }

    /* 获取PPP ID */
    ulRet = PPPC_GetCurrentPppId(pstDlDataNode->enRatMode, pstDlDataNode->ucStreamNum, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG3("Get ppp id fail!\r\n", pstDlDataNode->enRatMode,
            pstDlDataNode->ucStreamNum, ucPppId);

        pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstDlDataLink, &ulRemainCnt);

        TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);

        return;
    }

    /* 启动MAX PPP Inactive Timer */
    PPPC_StartPppInactiveTimer(ucPppId);

    if ((PS_FALSE == PPPC_IsDoingAccessAuth(ucPppId))
        && (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId))
    {
        /* 如果接入鉴权PPP处于initial/starting/closed状态,收到网络config
            报文不会有任何处理,需要手动触发一下 */
        PPPC_SetupAAPppByState();
    }

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    if (PPPC_RAT_MODE_EHRPD == pstDlDataNode->enRatMode)
    {
        PPPC_DlSoftProc(pstDlDataLink, ucPppId);
        return;
    }

    ulRet = PPPC_HDLC_HARD_DefPacket(pstDlDataLink, (VOS_UINT16)ucPppId, &ulDealCnt);

    /* 下行报文出队统计 */
    g_stPppcDataQueueStats.ulDlDataQProcMsgCnt += ulDealCnt;

    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Def packet fail!\r\n", ucPppId);
        return;
    }

    return;

#else

    PPPC_DlSoftProc(pstDlDataLink, ucPppId);
    return;

#endif
}

/*****************************************************************************
 函 数 名  : PPPC_UlDequeueProc
 功能描述  : 上行报文出队处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UlDequeueProc(VOS_VOID)
{
    TTF_LINK_ST                        *pstUlDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstUlDataNode;
    VOS_UINT8                           ucPdnId;
    VOS_UINT32                          ulRet = VOS_OK;
    VOS_UINT32                          ulRemainCnt;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT8                           ucPppId = 0;
    VOS_UINT32                          ulDealCnt = 0;
#endif

    pstUlDataLink  = &g_stPppUlLink;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlDataLink);

    if(VOS_NULL_PTR == pstUlDataNode)
    {
        PPPC_WARNING_LOG("PPP UL Queue is Empty!\r\n");
        return VOS_OK;
    }

    ucPdnId     = pstUlDataNode->ucPdnId;

    ulRet   = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Get Ppp Id Fail! ucPdnId:[%d], ucPppId:[%d].\r\n", ucPdnId, ucPppId);

        /* 获取PPP ID失败已经无法处理数据,删除当前节点 */
        pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstUlDataLink, &ulRemainCnt);

        /* 释放TTFMemory,上行一个节点对应一块TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstUlDataNode->pstPduMem);
        pstUlDataNode->pstPduMem = VOS_NULL_PTR;

        if (VOS_NULL_PTR != pstUlDataNode->pstUlDataInfo)
        {
            /* Free memory allocated for trace */
            PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode->pstUlDataInfo);
            pstUlDataNode->pstUlDataInfo    = VOS_NULL_PTR;
        }

        /* 释放TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);
        pstUlDataNode = VOS_NULL_PTR;

        return VOS_OK;
    }

    #ifdef PPPC_HDLC_ST_TEST
    ulRet   = PPPC_HDLC_HARD_FrmPacket((VOS_UINT16)ucPppId, g_usPppcUlDataProto, pstUlDataLink, &ulDealCnt);
    #else

    /*填充协议域*/
    if (PPPC_RAT_MODE_EHRPD == PPPC_GetRatMode())
    {
        ulRet   = PPPC_HDLC_HARD_FrmPacket((VOS_UINT16)ucPppId, PPP_H_PF_VSNP, pstUlDataLink, &ulDealCnt);
    }
    else
    {
        ulRet   = PPPC_HDLC_HARD_FrmPacket((VOS_UINT16)ucPppId, PPP_IP, pstUlDataLink, &ulDealCnt);
    }
    #endif

    /* 上行报文出队数统计 */
    g_stPppcDataQueueStats.ulUlDataQProcMsgCnt += ulDealCnt;
    return ulRet;

#else

    pstUlDataNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlDataLink);
    /* 队列为空的时候返回空指针 */
    if ( VOS_NULL_PTR == pstUlDataNode )
    {
        PPPC_WARNING_LOG("PPP UL Queue is Empty!\r\n");
        return VOS_OK;
    }

    if (VOS_NULL_PTR == pstUlDataNode->pstPduMem)
    {
        PPPC_WARNING_LOG("pstUlDataNode->pstPduMem is null!\r\n");
        return VOS_OK;
    }

    /* 准备上行数据内存 */
    ulRet   = PPPC_PrepareUlEncapMem(pstUlDataNode->pstPduMem->usUsed);
    if (VOS_OK != ulRet)
    {
        PPPC_INFO_LOG("Alloc ul mem fail!\r\n");

        return VOS_OK;
    }

    pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
        pstUlDataLink, &ulRemainCnt);


    /* 上行报文出队数统计 */
    g_stPppcDataQueueStats.ulUlDataQProcMsgCnt++;

    ucPdnId     = pstUlDataNode->ucPdnId;

    PPPC_RcvCdsUlFrame(ucPdnId, pstUlDataNode->pstPduMem, pstUlDataNode->enRatMode,
        pstUlDataNode->pstUlDataInfo, pstUlDataNode->ucStreamNum);

    /* 释放节点 */
    TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);

    return VOS_OK;

#endif
}

/*****************************************************************************
 函 数 名  : PPPC_ProcLinkNodeByDirection
 功能描述  : 按照时间戳处理或者处理上行队列、下行队列
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_ProcLinkNodeByDirection
(
    VOS_UINT32                              ulDlStamp,
    VOS_UINT32                              ulUlStamp,
    PPPC_PROC_LINK_DIRECTION_ENUM_UINT16    enProcDire,
    VOS_UINT32                             *pulPppcUlCallCnt
)
{
    VOS_UINT32                              ulRet = VOS_OK;


    switch (enProcDire)
    {
        case PPPC_PROC_DL_NODE:

            PPPC_DlDequeueProc();

            break;

        case PPPC_PROC_UL_NODE:

            ulRet = PPPC_UlDequeueProc();

            break;

        case PPPC_PROC_BY_STAMP:

            /* stamp值越大表示入队越晚 */
            if (ulDlStamp >= ulUlStamp)
            {
                (*pulPppcUlCallCnt)++;
                ulRet = PPPC_UlDequeueProc();
            }
            else
            {
                *pulPppcUlCallCnt = 0;
                PPPC_DlDequeueProc();
            }

            break;

        default:

            PPPC_WARNING_LOG3("Invalid direction!\r\n",
                enProcDire, ulDlStamp, ulUlStamp);

            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_DequeueProc
 功能描述  : 上下行报文按入队时间顺序出队
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_DequeueProc(PPPC_PROC_LINK_DIRECTION_ENUM_UINT16 enProcDire)
{
    TTF_LINK_ST                        *pstDlLink;
    TTF_LINK_ST                        *pstUlLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    VOS_UINT32                          ulDlStamp;
    VOS_UINT32                          ulUlStamp;
#if (FEATURE_OFF == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT32                          ulTimerLoop     = 0;
    VOS_UINT32                          ulDelayNoteLoop = 0;
#endif
    VOS_UINT32                          ulRet           = VOS_OK;
    /* 上行任务连续调用次数 */
    VOS_UINT32                          ulPppcUlCallCnt = 0;

    pstDlLink       = &g_stPppDlLink;
    pstUlLink       = &g_stPppUlLink;


    for (;;)
    {
        ulRet = VOS_OK;

#if (FEATURE_OFF == FEATURE_HARDWARE_HDLC_ON_CCPU)

        /* 处理次数达到门限时起定时器并退出PPPC任务 */
        if (ulTimerLoop >= PPPC_MAX_NOTIFY_PPPC_PROC_CNT)
        {
            if ((VOS_NULL_PTR == g_hReachMaxProcTimer) && (PS_TRUE == g_enIsReachTimeout))
            {
                (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_hReachMaxProcTimer, MSPS_PID_PPPC,
                    PPPC_REACH_MAX_PROC_TIMER_AWAKE_LEN, 0, PPPC_AWAKE_SELF_REACH_MAX_PROC_TIMER,
                    VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
                g_enIsReachTimeout = PS_FALSE;
            }

            break;
        }

        /* 处理次数达到门限时做延时处理防止PPPC一直占着CPU */
        if (ulDelayNoteLoop >= PPPC_MAX_NOTIFY_PPPC_DELAY_CNT)
        {
            VOS_TaskDelay(1);
            ulDelayNoteLoop = 0;
        }

        ulTimerLoop++;
        ulDelayNoteLoop++;

        /* 软件解封装时，一个NODE结点下面最多有20个TTF内存，结点数大于100时，优先处理下行 */
        if (pstDlLink->ulCnt > PPPC_MAX_DL_NODE_CNT)
        {
            /* 下行队列深度大于门限时强制处理下行队列 */
            PPPC_DlDequeueProc();
            continue;
        }
#else
        /* HDLC硬件解封装时，一个NODE结点下面有1个TTF内存，结点数大于1000时，优先处理下行 */
        if (pstDlLink->ulCnt > PPPC_MAX_DL_NODE_CNT * 10)
        {
            /* 下行队列深度大于门限时强制处理下行队列 */
            PPPC_DlDequeueProc();
            continue;
        }
#endif

        if (ulPppcUlCallCnt > PPPC_UL_CONTINUOUS_MAX_CALL_CNT)
        {
            /* 上行连续调用大于门限时强制处理下行队列 */
            ulPppcUlCallCnt = 0;
            PPPC_DlDequeueProc();
            continue;
        }

        pstDlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstDlLink);
        pstUlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlLink);

        if ((VOS_NULL_PTR == pstDlNode) && (VOS_NULL_PTR == pstUlNode))
        {
            /* 上下行队列都为空的时候退出循环 */
            PPPC_INFO_LOG("PPP DL and UL Queue is Empty!\r\n");
            break;
        }
        else if ((VOS_NULL_PTR != pstDlNode) && (VOS_NULL_PTR != pstUlNode))
        {
            ulDlStamp   = pstDlNode->ulTimeStamp;
            ulUlStamp   = pstUlNode->ulTimeStamp;

            ulRet = PPPC_ProcLinkNodeByDirection(ulDlStamp, ulUlStamp,
                enProcDire, &ulPppcUlCallCnt);
        }
        else if (VOS_NULL_PTR != pstDlNode)
        {
            /* 只有下行队列有节点 */
            PPPC_DlDequeueProc();
        }
        else
        {
            /* 只有上行队列有节点 */
            ulRet = PPPC_UlDequeueProc();
        }

        if (VOS_OK != ulRet)
        {
            break;
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : PPPC_AwakeSelfProcUlDataTimeoutProc
 功能描述  : 当内存不足时PPPC每300ms唤醒自己处理数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_AwakeSelfProcUlDataTimeoutProc(VOS_VOID)
{
    PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TracePackets
 功能描述  : PPPC模块报文跟踪
 输入参数  : CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo
             TTF_MEM_ST                         *pstTtfMem
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_TracePackets
(
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo,
    TTF_MEM_ST                         *pstTtfMem
)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnTrace = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;


    /* 可维可测 */
    if ((VOS_NULL_PTR != pstMntnInfo) && (VOS_NULL_PTR != pstTtfMem))
    {
        if (VOS_NULL_PTR != pstTtfMem->pData)
        {
            ulDataLen   = pstMntnInfo->ulLength;

            pstMntnTrace = (CTTF_PPPC_TRACE_DATA_STRU *)PPP_Malloc(
                           PPPC_OM_TRANS_DATA_OFFSET_LEN + ulDataLen);
            if (VOS_NULL_PTR != pstMntnTrace)
            {
                PS_MEM_SET(pstMntnTrace, 0, PPPC_OM_TRANS_DATA_OFFSET_LEN + ulDataLen);
                PS_MEM_CPY(pstMntnTrace, pstMntnInfo, PPPC_OM_TRANS_DATA_OFFSET_LEN);

                (VOID)PS_MEM_CPY(pstMntnTrace->aucValue, pstTtfMem->pData, ulDataLen);

                PPP_MNTN_TRACE_MSG(pstMntnTrace);

                PPP_Free(pstMntnTrace);

                pstMntnTrace = VOS_NULL_PTR;
            }
        }
    }
    (VOS_VOID)pstMntnTrace;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckRlpPacketsAndFreeMem
 功能描述  : 1X模式检查PPPC模块收到RLP的下行报文队列有效性
 输入参数  : pstPackets          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月24日
    作    者   : c001114540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_1X_CheckRlpPacketsAndFreeMem
(
    CTTF_1X_RLP_PPP_DELIVER_DATA_STRU  *pstPackets
)
{
    VOS_UINT32                          ulLoop;

    /* 空指针检查 */
    if (VOS_NULL_PTR == pstPackets)
    {
        PPPC_WARNING_LOG("Null Pointer");

        return VOS_ERR;
    }

    /* 报文数量为0 */
    if (0 == pstPackets->ucSduCount)
    {
        PPPC_WARNING_LOG("SduCount is 0");

        return VOS_ERR;
    }

    /* 报文数量异常 */
    if (pstPackets->ucSduCount > CTTF_1X_RLP_PPP_MAX_SDU_COUNT)
    {
        PPPC_WARNING_LOG1("SduCount is %d", pstPackets->ucSduCount);

        for (ulLoop = 0; ulLoop < CTTF_1X_RLP_PPP_MAX_SDU_COUNT; ++ulLoop)
        {
            if (VOS_NULL_PTR != pstPackets->astDeliverSdus[ulLoop].pstSdu)
            {
                TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);
            }
        }

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_PushRlpPacketsEvent
 功能描述  : 1X模式PPPC模块收到RLP的下行报文入队
 输入参数  : pstPackets          PPP报文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月23日
    作    者   : c001114540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_PushRlpPacketsEvent(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    CDS_CDMA_1X_TRANS_DATA_STRU         stPppSdu;
    VOS_UINT32                          ulLoop;


    if (VOS_OK != PPPC_1X_CheckRlpPacketsAndFreeMem(pstPackets))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return VOS_ERR;
    }

    /* 如果是中继模式则直接调用CDS接口透传报文 */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        stPppSdu.ucPdnId = pstPackets->ucPdnId;
        for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ++ulLoop)
        {
            /* 由CDS判断pstPackets->astDeliverSdus[ulLoop].pstSdu是否为VOS_NULL_PTR */
            stPppSdu.ulSduLen   = pstPackets->astDeliverSdus[ulLoop].ulSduLen;
            stPppSdu.pstSdu     = pstPackets->astDeliverSdus[ulLoop].pstSdu;
            CDS_CDMA_1X_DL_DataInd(&stPppSdu, g_stPppContext.enModemId);

        }
        CDS_CDMA_WakeupCds();

        return VOS_OK;
    }

    /* 将下行报文加入队列 */
    PPPC_1X_DlEnqueueData(pstPackets);

    g_stPppcDataQueueStats.ul1xDlFrameRcvCnt += pstPackets->ucSduCount;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_CheckRpaPackets
 功能描述  : HRPD模式检查PPPC模块收到RPA的下行报文队列有效性
 输入参数  : pstPppSdu          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HRPD_CheckRpaPackets
(
    RLP_PPP_HRPD_TRANS_DATA_STRU       *pstPppSdu
)
{
    /* 空指针检查 */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* 下行TTF内存为空返回错误 */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* 下行帧长为0返回错误 */
    if (0 == pstPppSdu->ulSduLen)
    {
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_IsPacketByPass
 功能描述  : HRPD/eHRPD模式RLP下行报文是否透传到CDS,发送给RN的报文要递交到PPP 0,
             然后判断是否是中继模式,中继模式透传,网络模式PPPC自己处理
 输入参数  : ucStreamNum      流号,用于判断报文是否是发送给RN的
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月8日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_HRPD_IsPacketByPass(VOS_UINT8 ucStreamNum)
{
    VOS_UINT32                          ulRet;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;


    ulRet = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, ucStreamNum);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get app type fail!\r\n", ucStreamNum);
        return PS_FALSE;
    }

    /* 如果对应流中绑定的是RN,则不管是中继模式还是网络模式报文都要PPPC自己处理 */
    if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_RN == enAppType)
        || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_RN == enAppType)
        || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_RN == enAppType))
    {
        return PS_FALSE;
    }

    /* 如果绑定的不是RN,则需要判定中继模式,如果是则透传 */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : PPP_HRPD_DL_DataInd
 功能描述  : HRPD/eHRPD模式RLP下行报文发送到PPPC
 输入参数  : pstPppSdu      下行数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HRPD_DL_DataInd(RLP_PPP_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    CDS_CDMA_HRPD_TRANS_DATA_STRU       stPppData;
    VOS_UINT32                          ulMinPppMntnLen;
    PS_BOOL_ENUM_UINT8                  enIsByPass;


    if (VOS_OK != PPPC_HRPD_CheckRpaPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    /* 可维可测 */
    PS_MEM_SET(&g_stPppRlpMntnInfo, 0, sizeof(g_stPppRlpMntnInfo));
    pstMntnInfo     = &g_stPppRlpMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MAX_MNTN_INFO_LEN);

    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = CTTF_PID_HRPD_FPA;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_RCV_DL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucStreamNum     = pstPppSdu->ucStreamNumber;
    pstMntnInfo->usHigherLayerProtocol  = pstPppSdu->ucHigherLayerProtocol;
    pstMntnInfo->ucNumReservLabels      = pstPppSdu->ucNumReservLabels;
    PS_MEM_CPY(pstMntnInfo->aucReservLabel, pstPppSdu->aucReservLabel, CTTF_HRPD_PA_MAX_NUM_RESERV_LABELS);
    pstMntnInfo->enRatMode       = PPPC_GetRatMode();
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);
    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    enIsByPass = PPPC_HRPD_IsPacketByPass(pstPppSdu->ucStreamNumber);
    if (PS_TRUE == enIsByPass)
    {
        stPppData.ucPdnId  = 1;
        stPppData.ulSduLen = pstPppSdu->ulSduLen;
        stPppData.pstSdu   = pstPppSdu->pstSdu;
        pstPppSdu->pstSdu  = VOS_NULL_PTR;
        CDS_CDMA_HRPD_DL_DataInd(&stPppData, g_stPppContext.enModemId);

        CDS_CDMA_WakeupCds();

        return;
    }

    /* 将下行报文加入队列 */
    PPPC_HRPD_DlEnqueueData(pstPppSdu);

    g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_CheckCdsPackets
 功能描述  : 1X模式检查PPPC模块收到CDS的上行报文队列有效性
 输入参数  : pstPppSdu          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_1X_CheckCdsPackets
(
    const CDS_CDMA_1X_TRANS_DATA_STRU  *pstPppSdu
)
{
    TTF_MEM_ST                         *pstTTFMem;


    /* 空指针检查 */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* 上行TTF内存为空返回错误 */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* 上行帧长为0返回错误 */
    if (0 == pstPppSdu->ulSduLen)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_PullPacketEvent
 功能描述  : 1X模式下PPP模块收到CDS的上行报文入队处理
 输入参数  : pstPppSdu        PPP报文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_1X_PullPacketEvent(const CDS_CDMA_1X_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stTmpSdu;
    VOS_UINT32                          ulMinPppMntnLen;
    TTF_MEM_ST                         *pstTTFMem;
    VOS_UINT32                          ulRet   = VOS_OK;
    VOS_UINT8                           ucPppId = 0;

    if (VOS_OK != PPPC_1X_CheckCdsPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    ulRet   = PPPC_GetPppIdByPdn(pstPppSdu->ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG2("Get Ppp Id Fail! ucPdnId:[%d], ucPppId:[%d].\r\n", pstPppSdu->ucPdnId, ucPppId);
        return;
    }

    /* 可维可测 */
    /* 1X模式PPPC模块收到CDS的上行报文跟踪 */
    PS_MEM_SET(&g_stPppCdsMntnInfo, 0, sizeof(g_stPppCdsMntnInfo));
    pstMntnInfo     = &g_stPppCdsMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MAX_MNTN_INFO_LEN);
    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = UEPS_PID_CDS;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_FRAME_RCV_UL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucPdnId         = pstPppSdu->ucPdnId;
    pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);

    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    /* 如果是中继模式则直接调用RLP接口透传报文 */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        PS_MEM_SET(&stTmpSdu, 0, sizeof(PPP_RLP_1X_TRANS_DATA_STRU));
        stTmpSdu.ucPdnId            = pstPppSdu->ucPdnId;
        stTmpSdu.ulSduLen           = pstPppSdu->ulSduLen;
        stTmpSdu.pstSdu             = pstPppSdu->pstSdu;
        stTmpSdu.enIpDataType       = IP_DATA_TYPE_NULL;
        stTmpSdu.ucTotalPppFrgmt    = 1;
        stTmpSdu.ucCurrPppFrgmt     = 0;

        CTTF_1X_RLP_ReverseLink_DataReq(&stTmpSdu);

        CTTF_1X_RLP_ReverseLink_TriggerDataProc();

        PPPC_INFO_LOG("The Dial Mode is relay!\n");

        return;
    }

    /* TODO comment out for UT*/
#if 0
    /* 检查PdnId */
    if (pstPppSdu->ucPdnId != g_stPppContext.ucPdnId)
    {
        TTF_MemFree(MSPS_PID_PPPC, pstPppSdu->pstSdu);
        PPPC_WARNING_LOG("Pdn Id is error!");
        return;
    }
#endif

    /* 将上行报文加入队列 */
    PPPC_1X_UlEnqueueData(pstPppSdu);


    g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_CheckCdsPackets
 功能描述  : HRPD模式检查PPPC模块收到CDS的上行报文队列有效性
 输入参数  : pstPppSdu          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HRPD_CheckCdsPackets
(
    const CDS_CDMA_HRPD_TRANS_DATA_STRU    *pstPppSdu
)
{
    TTF_MEM_ST                         *pstTTFMem;


    /* 空指针检查 */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* 上行TTF内存为空返回错误 */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* 上行帧长为0返回错误 */
    if (0 == pstPppSdu->ulSduLen)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_PullPacketEvent
 功能描述  : HRPD模式下PPP模块收到CDS的上行报文入队处理
 输入参数  : pstPppSdu        PPP报文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月04日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HRPD_PullPacketEvent(const CDS_CDMA_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType;
    VOS_UINT32                          ulMinPppMntnLen;
    TTF_MEM_ST                         *pstTTFMem;
    VOS_UINT32                          ulRet   = VOS_OK;
    VOS_UINT8                           ucPppId = 0;


    if (VOS_OK != PPPC_HRPD_CheckCdsPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    ulRet   = PPPC_GetPppIdByPdn(pstPppSdu->ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG2("Get Ppp Id Fail! ucPdnId:[%d], ucPppId:[%d].\r\n", pstPppSdu->ucPdnId, ucPppId);
        return;
    }

    /* 可维可测 */
    /* HRPD模式PPPC模块收到CDS的上行报文跟踪 */
    PS_MEM_SET(&g_stPppCdsMntnInfo, 0, sizeof(g_stPppCdsMntnInfo));
    pstMntnInfo     = &g_stPppCdsMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MIN_MNTN_INFO_LEN);
    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = UEPS_PID_CDS;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_RCV_UL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucPdnId         = pstPppSdu->ucPdnId;
    pstMntnInfo->enRatMode       = PPPC_GetRatMode();
    pstMntnInfo->ucStreamNum     = PPPC_HRPD_GetStreamNumber(1);
    /* 获取stream2的绑定应用信息 */
    enAppType                    = g_stPppContext.stHrpdContext.aenApplicationType[1];
    pstMntnInfo->ucNumReservLabels = 1;
    pstMntnInfo->aucReservLabel[0] = PPPC_HRPD_PaAgentGetResvLabel(enAppType);
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);

    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    /* 如果是中继模式则直接调用RLP接口透传报文 */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        stHrpdSdu.ucReservationLabel    = PPPC_HRPD_PA_BEST_EFFORT;

        /* CDS传递过来的数据必然是要通过stream sn发送到网络的,因此参数填为业务ppp id */
        stHrpdSdu.ucStreamNumber        = PPPC_HRPD_GetStreamNumber(1);
        stHrpdSdu.ulSduLen              = pstPppSdu->ulSduLen;
        stHrpdSdu.pstSdu                = pstPppSdu->pstSdu;
        stHrpdSdu.enStreamMode          = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;
        stHrpdSdu.enIpDataType          = IP_DATA_TYPE_NULL;
        stHrpdSdu.ucTotalPppFrgmt       = 1;
        stHrpdSdu.ucCurrPppFrgmt        = 0;

        CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

        return;
    }

    /* 将上行报文加入队列 */
    PPPC_HRPD_UlEnqueueData(pstPppSdu);


    g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendTafOrHsmReconnInd
 功能描述  : Send reconnection indication msg to Taf or Hsm when PPP finds no link.
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-24
    作    者   : d00314740
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendTafOrHsmReconnInd
(
    VOS_UINT8                           ucPdnId
)
{
    PPP_APS_RECONN_IND_STRU            *pstReconnInd;

    pstReconnInd    = (PPP_APS_RECONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(PPP_APS_RECONN_IND_STRU));

    if (VOS_NULL_PTR == pstReconnInd)
    {
        PPPC_WARNING_LOG1("Alloc pstReconnInd Mem Fail! PppId:", ucPdnId);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstReconnInd + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(PPP_APS_RECONN_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstReconnInd->ulReceiverPid     = g_stPppContext.ulSendPid;
    pstReconnInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstReconnInd->enMsgId           = ID_PPP_APS_RECONN_IND;
    pstReconnInd->usOpId            = 0;
    pstReconnInd->ucPdnId           = ucPdnId;

    /* Send reconnection ind msg */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstReconnInd))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_PPP_APS_RECONN_IND msg fail! PdnId:%d\n", ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendEhsmReconnInd
 功能描述  : Send reconnection indication msg to Ehsm when PPP finds no link.
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-24
    作    者   : d00314740
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendEhsmReconnInd(VOS_VOID)
{
    CTTF_CNAS_EHRPD_RECONN_IND_STRU    *pstReconnInd;

    pstReconnInd    = (CTTF_CNAS_EHRPD_RECONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_RECONN_IND_STRU));

    if (VOS_NULL_PTR == pstReconnInd)
    {
        PPPC_WARNING_LOG("Alloc pstReconnInd Mem Fail!");

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstReconnInd + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(CTTF_CNAS_EHRPD_RECONN_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstReconnInd->ulReceiverPid     = g_stPppContext.ulSendPid;
    pstReconnInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstReconnInd->enMsgId           = ID_CTTF_CNAS_EHRPD_RECONN_IND;
    pstReconnInd->usOpId            = 0;

    /* Send reconnection ind msg */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstReconnInd))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_RECONN_IND msg fail! PdnId:%d\n");
    }

    return;
}
#if (PPPC_FEATURE_OFF == PPPC_FEATURE_MULTI_MODEM)
/*****************************************************************************
 函 数 名  : I1_TAF_APS_GetPppLinkStatus
 功能描述  : 不存在多modem时打桩Modem1获取链路状态，防止单编译时编译失败
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-12-18
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 I1_TAF_APS_GetPppLinkStatus(VOS_VOID)
{
    PPPC_WARNING_LOG("Do not support multi modem,modem1!");

    return TAF_APS_PPP_LINK_STATUS_BUTT;
}
#endif

#if (PPPC_FEATURE_OFF == PPPC_FEATURE_MODEM_2)
/*****************************************************************************
 函 数 名  : I2_TAF_APS_GetPppLinkStatus
 功能描述  : 不存在多modem时打桩Modem2获取链路状态，防止单编译时编译失败
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-12-18
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 I2_TAF_APS_GetPppLinkStatus(VOS_VOID)
{
    PPPC_WARNING_LOG("Do not support multi modem,modem2!");

    return TAF_APS_PPP_LINK_STATUS_BUTT;
}

#endif
/*****************************************************************************
 函 数 名  : PPPC_GetLinkStatus
 功能描述  : 获取链路状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-12-18
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 PPPC_GetLinkStatus(VOS_VOID)
{
    TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  enLinkStatus;

    if (MODEM_ID_0 == g_stPppContext.enModemId)
    {
        enLinkStatus = TAF_APS_GetPppLinkStatus();
    }
    else if (MODEM_ID_1 == g_stPppContext.enModemId)
    {
        enLinkStatus = I1_TAF_APS_GetPppLinkStatus();
    }
    else
    {
        enLinkStatus = I2_TAF_APS_GetPppLinkStatus();
    }

    return enLinkStatus;
}

/*****************************************************************************
 函 数 名  : PPPC_GetConnectionStatus
 功能描述  : 获取connection的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : connection状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-28
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
CTTF_HRPD_PA_CONNECTION_STATUS_ENUM_UINT8 PPPC_GetConnectionStatus(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.enConnectionStatus;
}

/*****************************************************************************
 函 数 名  : PPPC_SendRpaReConnInd
 功能描述  : 给PA发送conneciton重建消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-28
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendRpaReConnReq(VOS_VOID)
{
    CTTF_HRPD_PPP_PA_RECONN_REQ_STRU   *pstPppReConnReq;

    pstPppReConnReq = (CTTF_HRPD_PPP_PA_RECONN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_HRPD_PPP_PA_RECONN_REQ_STRU));
    if (VOS_NULL_PTR == pstPppReConnReq)
    {
        PPPC_ERROR_LOG("Alloc ID_CTTF_HRPD_PPP_PA_RECONN_REQ Mem Fail!\r\n");
        return;
    }

    pstPppReConnReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppReConnReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppReConnReq->enMsgId        = ID_CTTF_HRPD_PPP_PA_RECONN_REQ;
    pstPppReConnReq->usOpId         = 0;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppReConnReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_HRPD_PPP_PA_RECONN_REQ msg fail!");
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_ULSendNegoFrame
 功能描述  : 上行发送PPP协商报文
 输入参数  : pstMBuf    PPP协商数据
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-05
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_ULSendNegoFrame(PMBUF_S *pstMBuf, VOS_UINT32 ulRPIndex)
{
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTotalLen;
    VOS_UINT32                          ulMinPppMntnLen;
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    VOS_UINT8                           ucPdnId = 0;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;


    /* 内部调用pstMBuf不为空 */

    ulTotalLen  = (VOS_UINT32)pstMBuf->ulTotalDataLength;

    /* 协商报文较短，无需多次拷贝，只需拷贝一次，字节数小于1500Byte */
    pstTtfMem = PPPC_AdapterMBuftoTtfMemory(pstMBuf, TTF_MEM_POOL_ID_UL_DATA, 0, pstMBuf->ulTotalDataLength);
    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_894);
        /* 数据拷贝到TtfMemory失败也需要释放MBUF */
        PMBUF_Destroy(pstMBuf);
        return VOS_ERR;
    }

    PMBUF_Destroy(pstMBuf);

    enRatMode   = PPPC_GetRatMode();

    if (PPPC_RAT_MODE_1X == enRatMode)
    {
        ulRet     = PPPC_1X_GetPdnId((VOS_UINT8)ulRPIndex, &ucPdnId);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get PDN Id Fail! ulRPIndex:%d, ucPdnId:%d\r\n", ulRPIndex, ucPdnId);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
            return VOS_ERR;
        }

        /* 上行数据报文发送到RLP */
        stRlpSdu.ucPdnId            = ucPdnId;
        stRlpSdu.enIpDataType       = IP_DATA_TYPE_NULL;
        stRlpSdu.ucTotalPppFrgmt    = 1;
        stRlpSdu.ucCurrPppFrgmt     = 0;
        stRlpSdu.ulSduLen           = ulTotalLen;
        stRlpSdu.pstSdu             = pstTtfMem;

        /* 可维可测 */
        /* 1X模式PPPC模块发送到RLP的上行报文跟踪 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(ulTotalLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = MSPS_PID_1X_RRLP;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_NEGO_UL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stRlpSdu.ucPdnId;
        pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stRlpSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        /* 1x 根据CNAS的需求，当进行ppp协商时，如果当前链路不存在，则向CNAS发送ReconnectInd */
        /* 1x 根据CNAS的需求，当进行ppp协商时，如果当前链路不存在, 将当前的协商报文丢弃。 */
        if (TAF_APS_PPP_LINK_NOT_EXISTED == PPPC_GetLinkStatus())
        {
            PPPC_WARNING_LOG("Nego when tch not exist, 1x");

            PPPC_WARNING_LOG("Nego for not ACCESS_AUTH when link not exists, 1x");
            TTF_MemFree(MSPS_PID_PPPC, stRlpSdu.pstSdu);

            /* 向CNAS发送ReconnectReq */
            PPPC_SendTafOrHsmReconnInd(ucPdnId);
        }
        else
        {
            CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

            /* 触发RLP处理上行报文 */
            CTTF_1X_RLP_ReverseLink_TriggerDataProc();

            /* 上行协商报文计数加1 */
            g_stPppcDataQueueStats.ul1xUlNegoSndCnt++;
        }
    }
    else
    {
        /* 获取stream2的应用绑定信息 */
        stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber((VOS_UINT8)ulRPIndex);
        ulRet = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, stHrpdSdu.ucStreamNumber);

        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get App Type Fail! ulRPIndex, StreamNumber",
                ulRPIndex, stHrpdSdu.ucStreamNumber);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

            return VOS_ERR;
        }

        stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
        stHrpdSdu.ulSduLen          = ulTotalLen;
        stHrpdSdu.pstSdu            = pstTtfMem;
        stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;
        stHrpdSdu.enIpDataType      = IP_DATA_TYPE_NULL;
        stHrpdSdu.ucTotalPppFrgmt   = 1;
        stHrpdSdu.ucCurrPppFrgmt    = 0;

        /* 可维可测 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(ulTotalLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = CTTF_PID_HRPD_RPA;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_NEGO_UL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucStreamNum     = stHrpdSdu.ucStreamNumber;
        pstMntnInfo->ucNumReservLabels = 1;
        pstMntnInfo->aucReservLabel[0] = stHrpdSdu.ucReservationLabel;
        pstMntnInfo->enRatMode       = PPPC_GetRatMode();
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stHrpdSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        /* 根据CNAS的需求，当进行ppp协商时，如果当前链路不存在，则向CNAS发送ReconnectInd */
        /* 根据CNAS的需求，当进行ppp协商时，如果当前链路不存在, 不是接入鉴权，将当前的协商报文丢弃;
            是接入鉴权, 不丢弃。 */
        if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ulRPIndex)
        {
            /* 如果connection不存在，给PA发送connection重建消息 */
            if (CTTF_HRPD_PA_CONNECTION_NOT_EXIST_ENUM == PPPC_GetConnectionStatus())
            {
                TTF_MemFree(MSPS_PID_PPPC, stHrpdSdu.pstSdu);
                PPPC_WARNING_LOG("Nego for ACCESS_AUTH when Connection not exists");

                PPPC_SendRpaReConnReq();
            }
            else
            {
                CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                /* 上行协商报文计数加1 */
                g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt++;
            }
        }
        else
        {
            if (PPPC_RAT_MODE_HRPD == enRatMode)
            {
                if (TAF_APS_PPP_LINK_NOT_EXISTED == PPPC_GetLinkStatus())
                {
                    PPPC_WARNING_LOG("Nego for not ACCESS_AUTH when link not exists, HRPD");
                    TTF_MemFree(MSPS_PID_PPPC, stHrpdSdu.pstSdu);

                    ulRet     = PPPC_1XHrpdGetPdnId((VOS_UINT8)ulRPIndex, &ucPdnId);
                    if (VOS_OK != ulRet)
                    {
                        PPPC_WARNING_LOG2("Get PDN Id Fail! ulRPIndex:%d, ucPdnId:%d\r\n", ulRPIndex, ucPdnId);
                        return VOS_ERR;
                    }

                    /* 向CNAS发送ReconnectReq, HRPD */
                    PPPC_SendTafOrHsmReconnInd(ucPdnId);
                }
                else
                {
                    CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                    /* 上行协商报文计数加1 */
                    g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt++;
                }
            }
            else
            {
                /* EHRPD */
                if (CNAS_CTTF_EHRPD_LINK_NOT_EXISTED == CNAS_EHSM_GetPdnLinkStatus())
                {
                    PPPC_WARNING_LOG("Nego for not ACCESS_AUTH when link not exists, EHRPD");
                    TTF_MemFree(MSPS_PID_PPPC, stHrpdSdu.pstSdu);

                    /* 向CNAS发送ReconnectReq, EHRPD */
                    PPPC_SendEhsmReconnInd();
                }
                else
                {
                    CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                    /* 上行协商报文计数加1 */
                    g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt++;
                }
            }
        }
    }

    /* 启动MAX PPP Inactive Timer */
    PPPC_StartPppInactiveTimer((VOS_UINT8)ulRPIndex);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_RcvCdsUlFrame
 功能描述  : 收到CDS上行报文处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_RcvCdsUlFrame
(
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstTtfMemory,
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo,
    VOS_UINT8                           ucStreamNum
)
{
    TTF_MEM_ST                         *pstData;
    VOS_INT32                           lTotalLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRlpSduLen = 0;
    VOS_UINT32                          ulAccmValue = 0;
    VOS_UINT32                          ulAsynDataLen = 0;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucPppId  = 0;
    PPPINFO_S                          *pstPppInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;
    VOS_UINT8                          *pucDstDataPtr;
    IP_DATA_TYPE_ENUM_UINT8             enIpDataType;
    VOS_UINT32                          ulLoop;


    if (VOS_NULL_PTR == pstTtfMemory)
    {
        PPPC_WARNING_LOG2("Input para is null!\r\n", ucPdnId, enRatMode);
        return VOS_ERR;
    }

    if (PPPC_RAT_MODE_BUTT <= enRatMode)
    {
        PPPC_WARNING_LOG2("Invalid Rat Mode", ucPdnId, enRatMode);
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);
        return VOS_ERR;
    }

    ulRet       = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_895);
        PPPC_WARNING_LOG1("Get Ppp Id Fail!\r\n", ucPppId);
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);
        return VOS_ERR;
    }

    /* 解析具体的Ip包的数据类型，供rlp使用 */
    enIpDataType    = TTF_ParseIpDataType(MSPS_PID_PPPC, pstTtfMemory);

    pstPppInfo                  = &g_astPppPool[ucPppId];
    ulAccmValue    = (pstPppInfo->ulLocalAccm | pstPppInfo->ulRemoteAccm);

    /* 调用解析函数数据和信令分别处理 */
    ulRet   = FWD_PppEncap(ucPdnId, pstTtfMemory->pData, pstTtfMemory->usUsed,
                ulAccmValue, &ulAsynDataLen);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_897);
        PPPC_WARNING_LOG2("Encap PPP Fail!\r\n", ulAsynDataLen, ulRet);

        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);

        return VOS_ERR;
    }

    /* 数据已处理完毕可以释放内存 */
    TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);

    lTotalLen  = (VOS_INT32)ulAsynDataLen;
    pucDstDataPtr   = PPP_GetUlEncapDataPtr();

    /* TCP ACK 提前相关参数赋值 */
    stRlpSdu.enIpDataType       = enIpDataType;
    stRlpSdu.ucTotalPppFrgmt    = (VOS_UINT8)((lTotalLen / PPPC_MAX_UL_ENCAP_LEN) + 1);
    stHrpdSdu.enIpDataType      = enIpDataType;
    stHrpdSdu.ucTotalPppFrgmt   = (VOS_UINT8)((lTotalLen / PPPC_MAX_UL_ENCAP_LEN) + 1);

    enAppType = CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_BUTT;

    if ((PPPC_RAT_MODE_HRPD == enRatMode) || (PPPC_RAT_MODE_EHRPD == enRatMode))
    {
        /* 获取stream2的应用绑定信息 */
        ulRet = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, ucStreamNum);

        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get App Type Fail!", ucStreamNum, ucPppId);

            /* 释放内存 */
            for (ulLoop = 0; ulLoop < PPPC_MAX_UL_ENCAP_MEM_NUM; ulLoop++)
            {
                if (VOS_NULL_PTR != g_astUlEncapMem[ulLoop].pstDataPtr)
                {
                    TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[ulLoop].pstDataPtr);
                    g_astUlEncapMem[ulLoop].pstDataPtr = VOS_NULL_PTR;
                }
            }

            return VOS_ERR;
        }
    }

    /* 从第一块开始处理起 */
    ulIndex   = 0;
    pstData   = g_astUlEncapMem[ulIndex].pstDataPtr;

    while ((lTotalLen > 0) && (ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM)
        && (pstData != VOS_NULL_PTR))
    {
        ulRlpSduLen     = (VOS_UINT32)PS_MIN(lTotalLen, PPPC_MAX_UL_ENCAP_LEN);

        (VOID)PS_MEM_CPY(pstData->pData, pucDstDataPtr, ulRlpSduLen);
        pstData->usUsed = (VOS_UINT16)ulRlpSduLen;

        if (PPPC_RAT_MODE_1X == enRatMode)
        {
            /* 上行数据报文发送到RLP */
            stRlpSdu.ucPdnId            = ucPdnId;
            stRlpSdu.ucCurrPppFrgmt     = (VOS_UINT8)ulIndex;
            stRlpSdu.ulSduLen           = ulRlpSduLen;
            stRlpSdu.pstSdu             = pstData;
            if (VOS_NULL_PTR != pstUlDataInfo)
            {
                PS_MEM_CPY(&(stRlpSdu.stUlDataInfo), pstUlDataInfo, sizeof(PS_DATA_EXT_INFO_STRU));
                PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataInfo);
            }

            CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

            /* 上行IP包报文计数加1 */
            g_stPppcDataQueueStats.ul1xUlIPDataSndCnt++;
        }
        else
        {
            /* CDS传递过来的数据必然是要通过stream sn发送到网络的,因此参数填为业务ppp id */
            stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber(1);
            stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
            stHrpdSdu.ulSduLen          = ulRlpSduLen;
            stHrpdSdu.pstSdu            = pstData;
            stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;
            stHrpdSdu.ucCurrPppFrgmt    = (VOS_UINT8)ulIndex;

            CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

            /* 上行IP包报文计数加1 */
            g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt++;
        }

        g_astUlEncapMem[ulIndex].enPtrIsUsed    = PS_FALSE;
        g_astUlEncapMem[ulIndex].pstDataPtr     = VOS_NULL_PTR;

        lTotalLen           -= (VOS_INT32)ulRlpSduLen;
        pucDstDataPtr       += ulRlpSduLen;
        ulIndex++;

        if (ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM)    /* 防止数组越界 */
        {
            pstData   = g_astUlEncapMem[ulIndex].pstDataPtr;
        }
    }

    if (PPPC_RAT_MODE_1X == enRatMode)
    {
        /* 触发RLP处理上行报文 */
        CTTF_1X_RLP_ReverseLink_TriggerDataProc();
    }

    /* 启动MAX PPP Inactive Timer */
    PPPC_StartPppInactiveTimer((VOS_UINT8)pstPppInfo->ulRPIndex);

    return VOS_OK;
}

/** **************************************************************************
  Generate high layer data info trace msg and send it.

  @param[in]    pstUlDataInfo   Pointer to struct containing high layer data info.

  @return   VOS_VOID
*/

VOS_VOID PPP_TraceDlHighLayerInfo
(
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
)
{
    PPPC_TRACE_HIGH_LAYER_INFO_STRU     stHighLayerInfoMsg;

    stHighLayerInfoMsg.ulSenderPid      = MSPS_PID_PPPC;
    stHighLayerInfoMsg.ulReceiverPid    = MSPS_PID_PPPC;
    stHighLayerInfoMsg.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stHighLayerInfoMsg.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stHighLayerInfoMsg.ulLength         = sizeof(PPPC_TRACE_HIGH_LAYER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stHighLayerInfoMsg.enMsgId          = ID_CTTF_1X_PPPC_TRACE_HIGH_LAYER_INFO_DL;
    PS_MEM_CPY(&(stHighLayerInfoMsg.stUlDataInfo), pstUlDataInfo, sizeof(PS_DATA_EXT_INFO_STRU));

    TTF_TRACE_MSG(&stHighLayerInfoMsg);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_SendRlpDlDatatoCds
 功能描述  : 下行报文发送到CDS
 输入参数  : ucPdnId      承载号
             pstSynMBuf   MBUF格式的数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_SendRlpDlDatatoCds
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
)
{
    CDS_CDMA_1X_TRANS_DATA_STRU         stPppSdu;
    PS_DATA_EXT_INFO_STRU               stDataInfo;
    CDS_CDMA_HRPD_TRANS_DATA_STRU       stHrpdSdu;
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    VOS_UINT32                          ulMinPppMntnLen;


    PPP_MemSet(&stPppSdu, 0, sizeof(stPppSdu));
    PPP_MemSet(&stHrpdSdu, 0, sizeof(stHrpdSdu));

    if (PPPC_RAT_MODE_1X == ucRatMode)
    {
        stPppSdu.ucPdnId    = ucPdnId;
        stPppSdu.ulSduLen   = pstData->usUsed;
        stPppSdu.pstSdu     = pstData;

        /* 性能优化，勾取trace */
        FWD_PppFillDataInfo(pstData->pData, &(stDataInfo));
        stDataInfo.usStartSN    = usStartSeq;
        stDataInfo.usEndSN      = usEndSeq;
        PPP_TraceDlHighLayerInfo(&(stDataInfo));

        /* 可维可测 */
        /* 1X模式PPPC模块发送到CDS的下行报文跟踪 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(stPppSdu.ulSduLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = UEPS_PID_CDS;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_FRAME_SEND_DL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stPppSdu.ucPdnId;
        pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stPppSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CDS_CDMA_1X_DL_DataInd(&stPppSdu, g_stPppContext.enModemId);
        CDS_CDMA_WakeupCds();

        /* 下行发送IP包计数加1 */
        g_stPppcDataQueueStats.ul1xDlIPDataSndCnt++;
    }
    else
    {
        stHrpdSdu.ucPdnId    = ucPdnId;
        stHrpdSdu.ulSduLen   = pstData->usUsed;
        stHrpdSdu.pstSdu     = pstData;

        /* 可维可测 */
        /* HRPD模式PPPC模块发送到CDS的下行报文跟踪 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(stHrpdSdu.ulSduLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = UEPS_PID_CDS;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_SEND_DL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stHrpdSdu.ucPdnId;
        pstMntnInfo->enRatMode       = ucRatMode;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stHrpdSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CDS_CDMA_HRPD_DL_DataInd(&stHrpdSdu, g_stPppContext.enModemId);
        CDS_CDMA_WakeupCds();

        /* 下行发送IP包计数加1 */
        g_stPppcDataQueueStats.ulHrpdDlIPDataSndCnt++;
    }

    return;
}


#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

/*****************************************************************************
 函 数 名  : PPPC_ProcAsFrmDataInd
 功能描述  : 按照数据帧处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ProcAsFrmDataInd(struct MsgCB * pMsg)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstHdlcEnable;
    VOS_UINT16                               usPppId;
    VOS_UINT16                               usProtocol;
    TTF_MEM_ST                              *pstMem;


    pstHdlcEnable = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU*)pMsg;

    usPppId       = pstHdlcEnable->usPppId;
    usProtocol    = pstHdlcEnable->usProtocol;
    pstMem        = pstHdlcEnable->pstMem;


    PPPC_HDLC_HARD_ProcAsFrmPacket(usPppId, usProtocol, pstMem);

    return;
}

#endif


/*****************************************************************************
 函 数 名  : PPPC_AwakeSelfReachMaxProcTimeoutProc
 功能描述  : 当处理次数达到门限时,PPPC每定时唤醒自己处理上下行数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_AwakeSelfReachMaxProcTimeoutProc(VOS_VOID)
{
    g_hReachMaxProcTimer = VOS_NULL_PTR;
    g_enIsReachTimeout   = PS_TRUE;
    PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_AccessAuthDelayTimeoutproc
 功能描述  : PPPC收到PA的接入鉴权消息时延时5s等到收到BSC的LCP协商报文后再处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_AccessAuthDelayTimeoutproc()
{
    g_hAADelayTimer = VOS_NULL_PTR;

    /* 为了给PA回复接入鉴权RESPONSE，设置接入鉴权标志位 */
    PPPC_ChangeAccessAuthState(PS_TRUE, PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* 通知PA不用做接入鉴权 */
    PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_NO_ACCESS_AUTH);

    /* 恢复接入鉴权标志位 */
    PPPC_ChangeAccessAuthState(PS_FALSE, PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* 设置初始接入鉴权标志位 */
    PPPC_SetInitAccessAuthMode(PS_FALSE);

    /* 不拦截用户的拨号请求 */
    /* 超时则任务不需要做接入鉴权，与接入鉴权成功相同处理 */
    PPPC_AccessAuthSuccProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_AccessAuthDelayProcTimeoutProc
 功能描述  : 接入鉴权超时处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_AccessAuthDelayProcTimeoutProc
(
    PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16 enActMode
)
{
    switch(enActMode)
    {
        case PPPC_ACCESS_AUTH_ACT_MODE_HRPD:

            if (VOS_NULL_PTR == g_astActHrpdTimer[0].pstMsgPtr)
            {
                PPPC_WARNING_LOG1("Invalid input ptr\r\n", enActMode);
                return;
            }

            PPPC_RespApsActFail((APS_PPP_ACT_REQ_STRU *)g_astActHrpdTimer[0].pstMsgPtr);

            PPP_Free(g_astActHrpdTimer[0].pstMsgPtr);
            g_astActHrpdTimer[0].pstMsgPtr       = VOS_NULL_PTR;
            g_astActHrpdTimer[0].hDelayProcTimer = VOS_NULL_PTR;

            break;

        case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_ATTACH:

            if (VOS_NULL_PTR == g_astActHrpdTimer[1].pstMsgPtr)
            {
                PPPC_WARNING_LOG1("Invalid input ptr\r\n", enActMode);
                return;
            }

            PPPC_RespEhsmAttachFail((CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)g_astActHrpdTimer[1].pstMsgPtr);

            PPP_Free(g_astActHrpdTimer[1].pstMsgPtr);
            g_astActHrpdTimer[1].pstMsgPtr       = VOS_NULL_PTR;
            g_astActHrpdTimer[1].hDelayProcTimer = VOS_NULL_PTR;

            break;

        case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_PDN:

            if (VOS_NULL_PTR == g_astActHrpdTimer[2].pstMsgPtr)
            {
                PPPC_WARNING_LOG1("Invalid input ptr\r\n", enActMode);
                return;
            }

            PPPC_RespEhsmPdnConnectFail((CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)g_astActHrpdTimer[2].pstMsgPtr);

            PPP_Free(g_astActHrpdTimer[2].pstMsgPtr);
            g_astActHrpdTimer[2].pstMsgPtr       = VOS_NULL_PTR;
            g_astActHrpdTimer[2].hDelayProcTimer = VOS_NULL_PTR;

            break;

        default:

            PPPC_WARNING_LOG1("Invalid rate mode\r\n", enActMode);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetDialMode
 功能描述  : 获取拨号模式
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月28日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 PPPC_GetDialMode(VOS_VOID)
{
    return g_stPppContext.enDialMode;
}

/*****************************************************************************
 函 数 名  : PPPC_SetDialMode
 功能描述  : 设置拨号模式，只支持中继和网络模式
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月01日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SetDialMode(TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 enDialMode)
{
    g_stPppContext.enDialMode = enDialMode;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetRatMode
 功能描述  : 获取当前模式是1X,HRPD或者eHRPD
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
PPPC_RAT_MODE_ENUM_UINT8 PPPC_GetRatMode(VOS_VOID)
{
    return g_stPppContext.enRatMode;
}

/*****************************************************************************
 函 数 名  : PPPC_SetRatMode
 功能描述  : 设定当前模式1X,HRPD或者eHRPD
 输入参数  : PPPC_RAT_MODE_ENUM_UINT8 enRatMode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SetRatMode(PPPC_RAT_MODE_ENUM_UINT8 enRatMode)
{
    g_stPppContext.enRatMode = enRatMode;
    return;
}


/*****************************************************************************
 函 数 名  : PPPC_GetCurrentPdnId
 功能描述  : 获取当前的PDN ID,此接口可以在PPP协商过程中使用
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_GetCurrentPdnId(VOS_UINT8 *pucPdnId)
{
    PPPC_DATA_LINK_NODE_STRU           *pstApsCurrHeadNode  = VOS_NULL_PTR;
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode          = PPPC_RAT_MODE_BUTT;

    enRateMode  = PPPC_GetRatMode();
    if (PPPC_RAT_MODE_BUTT >= enRateMode)
    {
        pstApsCurrHeadNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(
                    MSPS_PID_PPPC, &g_stApsCmdLink);

        if (VOS_NULL_PTR != pstApsCurrHeadNode)
        {
            *pucPdnId = pstApsCurrHeadNode->ucPdnId;

            return VOS_OK;
        }
        else
        {
            PPPC_WARNING_LOG("Node is null\r\n");
        }
    }
    else
    {
        /* Invalid rate mode */
        PPPC_WARNING_LOG1("Invalid rate mode!enRateMode\r\n", enRateMode);
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_GetPdnId
 功能描述  : 1X模式获取当前的PDN ID
 输入参数  : VOS_UINT8 ucPppId
 输出参数  : VOS_UINT8 *pucPdnId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_1X_GetPdnId(VOS_UINT8 ucPppId, VOS_UINT8 *pucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucBit;


    pstPppContext   = &g_stPppContext;
    for (ucBit = 0; ucBit < A11_MAX_PDN_NUM; ++ucBit)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucBit))
        {
            *pucPdnId = ucBit;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_GetServicePppId
 功能描述  : 获取业务PPP Id
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月28日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_GetServicePppId(VOS_VOID)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT32                          ulIndex;


    pstPppContext   = &g_stPppContext;

    for (ulIndex = PPPC_PPP_ID_MIN; ulIndex <= PPPC_PPP_ID_MAX; ++ulIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, ulIndex))
        {
            break;
        }
    }

    /* 如果业务PPP ID大于上限则默认返回最小值1,当前业务PPP ID其实只会是1 */
    if (PPPC_PPP_ID_MIN != ulIndex)
    {
        PPPC_WARNING_LOG1("PPP id invalid!", ulIndex);
        ulIndex = PPPC_PPP_ID_MIN;
    }

    return ulIndex;
}

/*****************************************************************************
 函 数 名  : PPPC_GetCurrentPppId
 功能描述  : 获取PPP Id
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_GetCurrentPppId
(
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode,
    VOS_UINT8                           ucStreamNum,
    VOS_UINT8                          *pucPppId
)
{
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16  enAppType;
    VOS_UINT32                          ulRet;


    if (PPPC_RAT_MODE_1X == enRateMode)
    {
        *pucPppId   = (VOS_UINT8)PPPC_GetServicePppId();
    }
    else
    {
        ulRet   = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, ucStreamNum);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get app fail\r\n", enRateMode, ucStreamNum);
            return ulRet;
        }

        if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_RN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_RN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_RN == enAppType))
        {
            *pucPppId   = PPPC_PPP_ID_FOR_ACCESS_AUTH;
        }
        else if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_SN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_SN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_SN == enAppType))
        {
            *pucPppId   = (VOS_UINT8)PPPC_GetServicePppId();
        }
        else
        {
            PPPC_WARNING_LOG2("Get invalid app type\r\n", enRateMode, ucStreamNum);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_1XHrpdGetPdnId
 功能描述  : 根据PPP Id和PDN ID之间的映射关系获取Pdn Id,只有1X和HRPD可以使用,
             eHRPD模式一个PPP Id可以对应多个PDN ID不可以通过这种方式获取
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_1XHrpdGetPdnId(VOS_UINT16 usPppId, VOS_UINT8 *pucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT32                          ulPdnIndex;


    pstPppContext   = &g_stPppContext;

    for (ulPdnIndex = 0; ulPdnIndex < A11_MAX_PDN_NUM; ulPdnIndex++)
    {
        if (0 != TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[usPppId], ulPdnIndex))
        {
            *pucPdnId = (VOS_UINT8)ulPdnIndex;

            return VOS_OK;
        }
    }

    PPP_DBG_ERR_CNT(PPP_PHERR_806);

    PPPC_WARNING_LOG1("Get Pdn Id Fail!ucPppId\r\n", usPppId);

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_GetPppIdByPdn
 功能描述  : 根据PPP Id和PDN Id之间的映射关系获取PPP Id
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_GetPppIdByPdn(VOS_UINT8 ucPdnId, VOS_UINT8 *pucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppIdIndex;


    /* 检查PDN id */
    pstPppContext   = &g_stPppContext;
    for (ucPppIdIndex = PPPC_PPP_ID_MIN; ucPppIdIndex <= PPPC_PPP_ID_MAX; ++ucPppIdIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppIdIndex], ucPdnId))
        {
            *pucPppId = ucPppIdIndex;
            if ((PPPC_PPP_ID_MIN != ucPppIdIndex) && (0 != ucPppIdIndex))
            {
                /* PPP ID不是1或0时都是异常的 */
                PPPC_WARNING_LOG4("ucPppId %d,ucPdnId %d,ppp1 %d ppp0 %d\r\n",
                    ucPppIdIndex, ucPdnId, pstPppContext->aulPppIdMapPdnId[1], pstPppContext->aulPppIdMapPdnId[0]);
            }
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_IsPdnIdUnique
 功能描述  : 判断当前PDN ID是不是唯一的
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月05日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_IsPdnIdUnique(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppId;
    VOS_UINT8                           ucBit;
    VOS_UINT8                           ucPdnNum = 0;


    if (VOS_OK != PPPC_GetPppIdByPdn(ucPdnId, &ucPppId))
    {
        return VOS_ERR;
    }

    pstPppContext   = &g_stPppContext;
    for (ucBit = 0; ucBit < A11_MAX_PDN_NUM; ++ucBit)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucBit))
        {
            ++ucPdnNum;
        }
    }
    if (PPPC_PDN_ID_UNIQUE == ucPdnNum)
    {
        return VOS_OK;
    }
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_MappingPppIdandPdnId
 功能描述  : 记录PPP Id和Pdn Id之间的映射关系
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : c00184031
    修改内容   : 新生成函数
  1.日    期   : 2015年05月27日
    作    者   : w00316385
    修改内容   : RabId改为PdnId

*****************************************************************************/
VOS_VOID PPPC_MappingPppIdandPdnId(VOS_UINT8 ucPppId, VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* 记录PPP Id和Pdn Id的映射关系 */
    TTF_SET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucPdnId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearMappingByPppId
 功能描述  : 根据Ppp Id清除PPP Id和Pdn Id之间的映射关系
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : c00184031
    修改内容   : 新生成函数
  1.日    期   : 2015年05月27日
    作    者   : w00316385
    修改内容   : RabId改为PdnId

*****************************************************************************/
VOS_VOID PPPC_ClearMappingByPppId(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;

    pstPppContext   = &g_stPppContext;
    pstPppContext->aulPppIdMapPdnId[ucPppId] = 0;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearMappingByPdnId
 功能描述  : 根据Pdn Id清除PPP Id和Pdn Id之间的映射关系
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ClearMappingByPdnId(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppId;


    pstPppContext   = &g_stPppContext;
    for (ucPppId = PPPC_PPP_ID_MIN; ucPppId <= PPPC_PPP_ID_MAX; ++ucPppId)
    {
        TTF_CLEAR_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckPdnId
 功能描述  : 检查PDN id是否有效
 输入参数  : VOS_UINT8 ucPdnId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_CheckPdnId(VOS_UINT8 ucPdnId)
{
    /* PDN ID的取值范围为0~14 */
    if (ucPdnId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1("PDN id is error! PDN Id = %d\r\n", ucPdnId);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckRateMode
 功能描述  : 检查Rate mode是否有效
 输入参数  : TAF_APS_PPP_RAT_MODE_ENUM_UINT8 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_CheckRateMode(TAF_APS_PPP_RAT_MODE_ENUM_UINT8 enMode)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    switch(enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
        case TAF_APS_PPP_RAT_MODE_HRPD:
            ulRet = VOS_OK;
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckPdnType
 功能描述  : 检查Pdn Type是否有效
 输入参数  : TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_CheckPdnType(TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    switch(enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            ulRet = VOS_OK;
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_IsPdnIdUsing
 功能描述  : 检查PDN id是否在使用中
 输入参数  : VOS_UINT8 ucPdnId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsPdnIdUsing(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppIdIndex;


    /* 检查PDN id */
    pstPppContext   = &g_stPppContext;
    for (ucPppIdIndex = PPPC_PPP_ID_MIN; ucPppIdIndex <= PPPC_PPP_ID_MAX; ++ucPppIdIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppIdIndex], ucPdnId))
        {
            return PS_TRUE;
        }
    }
    return PS_FALSE;
}

/*****************************************************************************
 函 数 名  : PPPC_IsDoingAccessAuth
 功能描述  : 是否正在进行接入鉴权
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-23
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsDoingAccessAuth(VOS_UINT8 ucPppId)
{
    PPPINFO_S                          *pstPppInfo;


    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("Invalid ppp id!\r\n", ucPppId);
        return PS_FALSE;
    }

    pstPppInfo                  = &g_astPppPool[ucPppId];

    return pstPppInfo->enIsDoingAccessAuth;
}

/*****************************************************************************
 函 数 名  : PPPC_ChangeAccessAuthState
 功能描述  : 设置接入鉴权状态
 输入参数  : PS_BOOL_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-23
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ChangeAccessAuthState
(
    PS_BOOL_ENUM_UINT8                  enIsDoingAcessAuth,
    VOS_UINT8                           ucPppId
)
{
    PPPINFO_S                          *pstPppInfo;


    pstPppInfo                      = &g_astPppPool[ucPppId];
    pstPppInfo->enIsDoingAccessAuth = enIsDoingAcessAuth;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_AddPppId
 功能描述  : 新增一个PppId
 输入参数  : 无
 输出参数  : VOS_UINT8 *pucPppId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_AddPppId(VOS_UINT8 *pucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* 当前业务协商只支持一路PPP，后续有需求再放开 */
#if 0
    for (ucPppIdBit = PPPC_PPP_ID_MIN; ucPppIdBit <= PPPC_PPP_ID_MAX; ++ucPppIdBit)
    {
        if (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, ucPppIdBit))
        {
            TTF_SET_A_BIT(pstPppContext->ulPppIdBitMask, ucPppIdBit);
            *pucPppId = ucPppIdBit;
            return VOS_OK;
        }
    }
#endif
    /* 此时已异常，PPPID固定返回1，业务可以恢复 */
    if (PPPC_BIT_MASK_EMPTY != TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, PPPC_PPP_ID_MIN))
    {
        PPPC_WARNING_LOG1("Ppp id bitmask abnormal!", pstPppContext->ulPppIdBitMask);
    }
    TTF_SET_A_BIT(pstPppContext->ulPppIdBitMask, PPPC_PPP_ID_MIN);

    *pucPppId = PPPC_PPP_ID_MIN;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_DeletePppId
 功能描述  : 删除一个PppId
 输入参数  : 无
 输出参数  : VOS_UINT8 ucPppId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_DeletePppId(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* 对PPP Id的有效性进行检查 */
    TTF_CLEAR_A_BIT(pstPppContext->ulPppIdBitMask, ucPppId);
    pstPppContext->aulPppIdMapPdnId[ucPppId] = 0;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_SndUlDataNotify
 功能描述  : PPP上行消息队列内结点个数为0时，向PPP发送数据处理指示
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_SndUlDataNotify(VOS_VOID)
{

    (VOS_VOID)VOS_EventWrite(g_ulPppcTaskId, PPPC_UL_PKT_EVENT);


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_SndDlDataNotify
 功能描述  : PPP下行消息队列内结点个数为0时，向PPP发送数据处理指示
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_SndDlDataNotify(VOS_VOID)
{
    (VOS_VOID)VOS_EventWrite(g_ulPppcTaskId, PPPC_DL_PKT_EVENT);


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_ApsCmdLinkInit
 功能描述  : 初始化APS的消息链表,目前需要挂入链表的只有激活和去激活消息,
             收到本地去激活IND直接清除资源无需链表管理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-05
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ApsCmdLinkInit(VOS_VOID)
{
    TTF_LinkInit(MSPS_PID_PPPC, &g_stApsCmdLink);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearApsCmdLinkNode
 功能描述  : 清除APS发给PPP的消息链表
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-06
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ClearApsCmdLinkNode(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    while (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearEhsmPdnCmdLinkNode
 功能描述  : 清除EHSM发给PPP的PDN消息链表
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ClearEhsmPdnCmdLinkNode(VOS_UINT8 ucPdnId)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstNextNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    while (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        pstNextNode         = VOS_NULL_PTR;
        (VOS_VOID)TTF_LinkPeekNext(MSPS_PID_PPPC, pstEhsmPppCmdLink, (TTF_NODE_ST *)pstCurrentHeadNode, (TTF_NODE_ST **)&pstNextNode);

        if (pstCurrentHeadNode->ucPdnId == ucPdnId)
        {
            TTF_LinkRemoveNode(MSPS_PID_PPPC, pstEhsmPppCmdLink, (TTF_NODE_ST *)pstCurrentHeadNode);
            PPP_Free(pstCurrentHeadNode);
        }
        pstCurrentHeadNode  = pstNextNode;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SetIpCapability
 功能描述  : 设置IP地址类型
 输入参数  : VOS_UINT8 ucPdnType
 输出参数  : PPPINFO_S *pstPppInfo
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-12
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SetIpCapability
(
    VOS_UINT8                           ucPdnType,
    PPPINFO_S                          *pstPppInfo,
    VOS_UINT32                          ulSendPid
)
{
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is NULL.");
        return;
    }

    switch(ucPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV4;
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV6;
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            /* 1X、HRPD不支持IPV6,eHRPD才支持IPV6,目前用PID来区分 */
            if (UEPS_PID_EHSM == ulSendPid)
            {
                pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_ALL;
            }
            else
            {
                pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV4;
            }
            break;
        default:
            PPPC_WARNING_LOG1("ucPdnType is error. %d", ucPdnType);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearUlEncapMem
 功能描述  : 清除上行数据内存
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-02
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ClearUlEncapMem(VOS_VOID)
{
    VOS_UINT32                          ulIndex;


    for (ulIndex = 0; ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM; ulIndex++)
    {
        if (VOS_NULL_PTR != g_astUlEncapMem[ulIndex].pstDataPtr)
        {
            TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[ulIndex].pstDataPtr);
        }
    }

    PS_MEM_SET(&g_astUlEncapMem[0], 0, sizeof(g_astUlEncapMem));

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SetupPpp
 功能描述  : 创建PPP链路，触发发送LCP配置请求消息
 输入参数  : ucPppId    PPP Id
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-04
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SetupPpp(VOS_UINT8 ucPppId)
{
    PPP_LUPPARA_S                       stPPPMsg;
    VOS_UINT32                          ulRet;


    ulRet = PPP_StartNegoTimer(ucPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Start timer fail!\r\n", ucPppId, ulRet);
    }

    PPP_MemSet(&stPPPMsg, 0, sizeof(PPP_LUPPARA_S));

    /* ulRPIndex指示PPP Id,从1开始才是合法的,当前只能是1,后面需要从TAF传过来 */
    ulRet = Ppp_UsmIoCtl(ucPppId, PPP_ISLUP, (CHAR *)&stPPPMsg);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_811);
        PPPC_WARNING_LOG2("notify ppp fail,ulRpIndex, ulRet", ucPppId, ulRet);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_LinkDown
 功能描述  : 协商删除PPP链路
 输入参数  : ucPppId    PPP Id
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-04
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_LinkDown
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                          ulLcpSendFlag
)
{
    PPPINFO_S                              *pstPppInfo;


    pstPppInfo                  = &g_astPppPool[ucPppId];

    if(VOS_TRUE == ulLcpSendFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_948);
        PPPC_INFO_LOG("[ppp]PPP_A11MsgProc: (VOS_TRUE == pstA11Msg->ucLcpSendFlag)\r\n ");

        PPP_DBG_OK_CNT(PPP_PHOK_949);
        pstPppInfo->bFailFlag = PPPA11DOWN;
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        return;
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_951);
        pstPppInfo->bFailFlag = PPPA11DOWNNOLCPTER;

        (VOID)PPP_Shell_ISLIoCtl(ucPppId, PPP_ISLDOWN, (CHAR *)VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_FillPdnInfo
 功能描述  : 拷贝信息到PDN context
 输入参数  : PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-05
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_FillPdnInfo
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode
)
{
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    ulRet = PPP_GetPDNContextByPDNID(pstCurrentHeadNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstCurrentHeadNode->ucPdnId);
        return;
    }

    pstPDNContext->stEhrpd.ucPdnId      = pstCurrentHeadNode->ucPdnId;
    pstPDNContext->stEhrpd.enAttachType = pstCurrentHeadNode->stEhsmCmdNode.enAttachType;
    pstPDNContext->stEhrpd.enPdnType    = pstCurrentHeadNode->stEhsmCmdNode.enPdnType;
    pstPDNContext->stEhrpd.ucAddressAllocCause    = pstCurrentHeadNode->stEhsmCmdNode.ucAddressAllocCause;

    /* 拷贝APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstCurrentHeadNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ExtractPdnInfoFromHeadNode
 功能描述  : 从头结点里提取PDN 上下文信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-26
    作    者   : h00309869
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ExtractPdnInfoFromHeadNode(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 拷贝信息到PDN context */
    PPPC_FillPdnInfo(pstCurrentHeadNode);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SetAuthSwitch
 功能描述  : 设置鉴权开关
 输入参数  : VOS_UINT32        ulPapSwitch
             VOS_UINT32        ulChapSwitch
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-19
    作    者   : c003338085
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SetAuthSwitch
(
    VOS_UINT32        ulPapSwitch,
    VOS_UINT32        ulChapSwitch
)
{
    g_ulAuthPapOnoff = ulPapSwitch;
    g_ulAuthChapOnoff = ulChapSwitch;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetAuthSwitch
 功能描述  : 根据配置的鉴权类型及密码、用户名信息，获得鉴权开关取值
 输入参数  : TAF_APS_PPP_AUTH_TYPE_ENUM_UINT8    enAuthType
             PPPC_CONTEXT_INFO_STRU             *pstPppCont
 输出参数  : VOS_UINT32*                         pulPapSwitch
             VOS_UINT32*                         pulChapSwitch
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-20
    作    者   : c003338085
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_GetAuthSwitch
(
    TAF_APS_PPP_AUTH_TYPE_ENUM_UINT8    enAuthType,
    PPPC_CONTEXT_INFO_STRU             *pstPppCont,
    VOS_UINT32*                         pulOutPapSwitch,
    VOS_UINT32*                         pulOutChapSwitch
)
{
    VOS_UINT32                          ulPapSwitch = PPPC_AUTH_SWITCH_ON;
    VOS_UINT32                          ulChapSwitch = PPPC_AUTH_SWITCH_ON;
    PS_BOOL_ENUM_UINT8                  enUsrOrPwdEmpty = PS_FALSE;

    enUsrOrPwdEmpty = ((0 == pstPppCont->ulUserNameLen) || (0 == pstPppCont->ulPasswordLen));

    switch(enAuthType)
    {
        /* 鉴权类型为None时，不进行鉴权 */
        case TAF_APS_PPP_AUTH_TYPE_NONE:
            ulPapSwitch = PPPC_AUTH_SWITCH_OFF;
            ulChapSwitch = PPPC_AUTH_SWITCH_OFF;
            break;

        /* 鉴权类型为PAP时，不管用户名和密码情况，只进行PAP鉴权处理 */
        case TAF_APS_PPP_AUTH_TYPE_PAP:
            ulPapSwitch = PPPC_AUTH_SWITCH_ON;
            ulChapSwitch = PPPC_AUTH_SWITCH_OFF;
            break;

        /* 鉴权类型为CHAP时，用户名和密码不为空的情况，才进行CHAP鉴权处理 */
        case TAF_APS_PPP_AUTH_TYPE_CHAP:
            ulPapSwitch = PPPC_AUTH_SWITCH_OFF;
            ulChapSwitch = ((PS_FALSE == enUsrOrPwdEmpty)? PPPC_AUTH_SWITCH_ON : PPPC_AUTH_SWITCH_OFF);
            break;

        /* 鉴权类型为PAP/CHAP时，PAP鉴权始终处理，用户名和密码不为空的情况，才进行CHAP鉴权处理 */
        case TAF_APS_PPP_AUTH_TYPE_PAP_OR_CHAP:
            ulPapSwitch = PPPC_AUTH_SWITCH_ON;
            ulChapSwitch = ((PS_FALSE == enUsrOrPwdEmpty)? PPPC_AUTH_SWITCH_ON : PPPC_AUTH_SWITCH_OFF);
            break;

        default:
            PPPC_WARNING_LOG3("Invalid AuthType %d.\r\n", enAuthType, pstPppCont->ulUserNameLen, pstPppCont->ulPasswordLen);
            break;
    }

    *pulOutPapSwitch = ulPapSwitch;
    *pulOutChapSwitch = ulChapSwitch;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_AttachReqMsgNodeProc
 功能描述  : PPPC模块Attach Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_AttachReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    PPPINFO_S                              *pstPppInfo;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 存储收到激活消息时APS的PID和接入模式 */
    g_stPppContext.ulSendPid = pstCurrentHeadNode->ulSenderPid;
    PPPC_SetRatMode(PPPC_RAT_MODE_EHRPD);

    /* 考虑对冲场景，必须保证串行处理 */
    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        PPP_HDLC_HARD_SetUp(pstCurrentHeadNode->ucPppId);

#endif

        /* eHrpd不支持PAP和CHAP */
        PPPC_SetAuthSwitch(PPPC_AUTH_SWITCH_OFF, PPPC_AUTH_SWITCH_OFF);

        PPPC_FillPdnInfo(pstCurrentHeadNode);

        pstPppInfo = &g_astPppPool[pstCurrentHeadNode->ucPppId];

        /* 如果没有LCP实体或者PHASE不在ETWORK直接发起PPP建链(HANDOVER和INITIAL的判断条件一致) */
        if ((VOS_NULL_PTR == pstPppInfo->pstLcpInfo)
                || (PPP_PHASE_NETWORK != pstPppInfo->usPhase))
        {
            /* PPP发起建链 */
            PPPC_SetupPpp(pstCurrentHeadNode->ucPppId);
        }
        else/*否则发起VSNCP协商 */
        {
            PPP_VSNCP_NotifyVSNCPStart(pstPppInfo, pstCurrentHeadNode->ucPdnId);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_DisConnAllPDN
 功能描述  : 断开所有PDN连接
 输入参数  : ucPppId    PPP ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-20
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_DisConnAllPDN(VOS_UINT8 ucPppId)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT32                          ulRet;
    PPPINFO_S                          *pstPppInfo;
    PDN_CONTEXT_S                      *pstPDNContext;
    PS_BOOL_ENUM_UINT8                  enNeedLcpTerm = PS_TRUE;

    pstPppInfo = &g_astPppPool[ucPppId];

    for ( ucPdnId = 0; ucPdnId < A11_MAX_PDN_NUM; ucPdnId++)
    {
        if (PS_TRUE != PPPC_IsPdnIdUsing(ucPdnId))
        {
            continue;
        }

        ulRet = PPP_GetPDNContextByPDNID(ucPdnId, &pstPDNContext);
        if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
        {
            PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
            continue;
        }

        if (PPP_STATE_INITIAL != pstPDNContext->stEhrpd.stVSNCP.ucState)
        {
            enNeedLcpTerm = PS_FALSE;

            /* PPP发起VSNCP去激活 */
            PPP_VSNCP_NotifyVSNCPStop(pstPppInfo, ucPdnId);
        }
    }

    if (PS_TRUE == enNeedLcpTerm)
    {
        /* PPP发起PPP去激活 */
        PPPC_LinkDown(ucPppId, VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_DetachReqMsgNodeProc
 功能描述  : PPPC模块Detach Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_DetachReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;

    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    /* 考虑对冲场景，必须保证串行处理 */
    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;
        PPPC_DisConnAllPDN(pstCurrentHeadNode->ucPppId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_PdnConnectReqMsgNodeProc
 功能描述  : PPPC模块PDN Connect Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_PdnConnectReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                  enIsHandling    = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 存储收到激活消息时APS的PID */
    g_stPppContext.ulSendPid = pstCurrentHeadNode->ulSenderPid;

    /* 考虑对冲场景，必须保证串行处理 */
    enIsHandling    = pstCurrentHeadNode->enIsHandling;
    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

        PPPC_FillPdnInfo(pstCurrentHeadNode);
        /* PPP发起VSNCP协商 */
        PPP_VSNCP_NotifyVSNCPStart(&g_astPppPool[pstCurrentHeadNode->ucPppId], pstCurrentHeadNode->ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_PdnDisconnectReqMsgNodeProc
 功能描述  : PPPC模块PDN Disconnect Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_PdnDisconnectReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    /* 考虑对冲场景，必须保证串行处理 */
    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }


    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

        /* PPP发起VSNCP去激活 */
        PPP_VSNCP_NotifyVSNCPStop(&g_astPppPool[pstCurrentHeadNode->ucPppId], pstCurrentHeadNode->ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmMsgNodeProc
 功能描述  : PPPC模块消息节点处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmMsgNodeProc(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    PS_BOOL_ENUM_UINT8                      enIsDoingInitAA = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 如果当前正在进行接入鉴权,不能同时做PPP的业务协商 */
    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsDoingInitAA)
    {
        PPPC_WARNING_LOG("It is now doing access authentication!\r\n");
        return;
    }

    enMsgType           = pstCurrentHeadNode->stEhsmCmdNode.enMsgType;
    switch(enMsgType)
    {
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            PPPC_AttachReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            PPPC_DetachReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            PPPC_PdnConnectReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            PPPC_PdnDisconnectReqMsgNodeProc();

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmAttachCheckParam
 功能描述  : 检查Attach消息参数
 输入参数  : CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EhsmAttachCheckParam
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    if (pstAttachReq->enModemId >= MODEM_ID_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid modem id!", pstAttachReq->enModemId);
        return VOS_ERR;
    }

    if (pstAttachReq->ucPdnId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1("PDN id is error!", pstAttachReq->ucPdnId);
        return VOS_ERR;
    }

    if (pstAttachReq->enAttachType >= CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid enAttachType!", pstAttachReq->enAttachType);
        return VOS_ERR;
    }

    if ((CNAS_CTTF_EHRPD_PDN_TYPE_INVALID == pstAttachReq->enPdnType)
        || (pstAttachReq->enPdnType > CNAS_CTTF_EHRPD_PDN_TYPE_IPV4V6))
    {
        PPPC_WARNING_LOG1("Invalid enPdnType", pstAttachReq->enPdnType);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmAttachReqProc
 功能描述  : PPPC模块处理Ehsm的Attach请求
 输入参数  : CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmAttachReqProc
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstEhsmAttachInfo;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    VOS_UINT32                          ulRet;
    PPPINFO_S                          *pstPppInfo;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    PS_BOOL_ENUM_UINT8                  enIsInitAccessAuth;


    /* 内部调用保证指针入参非空 */

    /* 检查参数 */
    ulRet = PPPC_EhsmAttachCheckParam(pstAttachReq);
    if (VOS_OK != ulRet)
    {
        PPPC_RespEhsmAttachFail(pstAttachReq);
        PPPC_WARNING_LOG("Ehsm attah check param fail!");
        return;
    }

    /* 如果是初始接入鉴权则不入队启定时器等到接入鉴权完成后再处理 */
    enIsInitAccessAuth = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsInitAccessAuth)
    {
        /* EHSM不能重复ATTACH,元素1专门存储Attach消息 */
        if (VOS_NULL_PTR != g_astActHrpdTimer[1].hDelayProcTimer)
        {
            PPPC_WARNING_LOG1("Ehsm reattach!\r\n", pstAttachReq->ucPdnId);
            return;
        }

        pstEhsmAttachInfo = (CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)PPP_Malloc(
                        sizeof(CNAS_CTTF_EHRPD_ATTACH_REQ_STRU));
        if (VOS_NULL_PTR == pstEhsmAttachInfo)
        {
            PPPC_WARNING_LOG1("Alloc mem fail.", pstAttachReq->ucPdnId);
            return;
        }

        PS_MEM_CPY(pstEhsmAttachInfo, pstAttachReq,
                sizeof(CNAS_CTTF_EHRPD_ATTACH_REQ_STRU));

        g_astActHrpdTimer[1].pstMsgPtr = (VOS_VOID *)pstEhsmAttachInfo;
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_astActHrpdTimer[1].hDelayProcTimer,
            MSPS_PID_PPPC, PPPC_ACCESS_AUTH_HRPD_ACT_DELAY_PROC_TIMER_LEN,
            (VOS_UINT32)PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_ATTACH,
            PPPC_ACCESS_AUTH_ACT_HRPD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        return;
    }

    /* 收到EHSM发给PPP的Attach消息直接入队 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PPPC_SetRatMode(PPPC_RAT_MODE_EHRPD);

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid                = pstAttachReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType    = pstAttachReq->enMsgId;
    pstEhsmMsgNode->usOpId                     = pstAttachReq->usOpId;
    pstEhsmMsgNode->ucPdnId                    = pstAttachReq->ucPdnId;
    pstEhsmMsgNode->stEhsmCmdNode.enPdnType    = pstAttachReq->enPdnType;
    pstEhsmMsgNode->stEhsmCmdNode.enAttachType = pstAttachReq->enAttachType;
    pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause = pstAttachReq->ucAddressAllocCause;
    pstEhsmMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_AddPppId(&pstEhsmMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Add Ppp Id fail!");
        PPP_Free(pstEhsmMsgNode);
        PPPC_RespEhsmAttachFail(pstAttachReq);
        return;
    }

    pstPppCont  = &g_stPppContext;

    /* 拷贝用户名 */
    ulUserNameLen    = VOS_StrNLen((VOS_CHAR *)pstAttachReq->aucUserName,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucUserName,
        (VOS_CHAR *)pstAttachReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* 拷贝密码 */
    ulPasswordLen    = VOS_StrNLen((VOS_CHAR *)pstAttachReq->aucPassword,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucPassword,
        (VOS_CHAR *)pstAttachReq->aucPassword, ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    /* 拷贝APN */
    PS_MEM_CPY(&(pstEhsmMsgNode->stEhsmCmdNode.stApn),
        &(pstAttachReq->stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPdnAddress),
        (VOS_INT8 *)&(pstAttachReq->stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPco),
        (VOS_INT8 *)&(pstAttachReq->stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstEhsmMsgNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstAttachReq->aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    pstEhsmPppCmdLink           = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    /* 存储modem id */
    g_stPppContext.enModemId    = pstAttachReq->enModemId;

    /* 映射ppp id和Pdn id */
    PPPC_MappingPppIdandPdnId(pstEhsmMsgNode->ucPppId, pstAttachReq->ucPdnId);

    PPPC_EhsmMsgNodeProc();

    pstPppInfo                  = &g_astPppPool[pstEhsmMsgNode->ucPppId];

    pstPppInfo->bEhrpdUser      = VOS_TRUE;

    /* ppp id映射到PPP内部需要自增 */
    pstPppInfo->ulRPIndex   = pstEhsmMsgNode->ucPppId;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmDetachReqProc
 功能描述  : PPPC模块处理Ehsm的Detach请求
 输入参数  : pstDetachReq    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmDetachReqProc
(
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstDetachReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                  enIsDoingInitAA;


    /* 内部调用保证指针入参非空 */

    /* 如果在ppp deact状态下, 收到EHsm的DeactReq消息，则直接给EHsm回DeactSucc */
    if (PPPC_MIN_ACTIVE_ENTITY >= g_stPppContext.ulPppIdBitMask)
    {
        PPPC_WARNING_LOG("Rcv EhsmDetachReq Msg when ppp deact.");
        PPPC_RespEhsmDetach(CNAS_CTTF_EHRPD_RSLT_SUCCESS, pstDetachReq);
        return;
    }

    enIsDoingInitAA = PPPC_EhsmDetachProcWhenAccessAuth();
    if (PS_TRUE == enIsDoingInitAA)
    {
        PPPC_RespEhsmDetach(CNAS_CTTF_EHRPD_RSLT_SUCCESS, pstDetachReq);
        return;
    }

    /* 收到detach消息应优先处理，此时要清空队列中的所有节点 */
    PPPC_ClearApsCmdLinkNode();

    /* 收到APS发给PPP的去激活消息直接入队 */
    pstEhsmMsgNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid             = pstDetachReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType = pstDetachReq->enMsgId;
    pstEhsmMsgNode->usOpId                  = pstDetachReq->usOpId;
    pstEhsmMsgNode->enIsHandling            = PS_FALSE;

    pstEhsmMsgNode->ucPppId                 = (VOS_UINT8)PPPC_GetServicePppId();

    pstEhsmPppCmdLink                       = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmPdnConnectCheckParam
 功能描述  : 检查PdnConnect消息参数
 输入参数  : CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU    *pstPdnConnectReq
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EhsmPdnConnectCheckParam
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    if (pstPdnConnectReq->ucPdnId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1("PDN id is error!", pstPdnConnectReq->ucPdnId);
        return VOS_ERR;
    }

    if (pstPdnConnectReq->enAttachType >= CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid enAttachType!", pstPdnConnectReq->enAttachType);
        return VOS_ERR;
    }

    if ((CNAS_CTTF_EHRPD_PDN_TYPE_INVALID == pstPdnConnectReq->enPdnType)
        || (pstPdnConnectReq->enPdnType > CNAS_CTTF_EHRPD_PDN_TYPE_IPV4V6))
    {
        PPPC_WARNING_LOG1("Invalid enPdnType", pstPdnConnectReq->enPdnType);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmPdnConnectReqProc
 功能描述  : PPPC模块处理Ehsm的PDN Connect请求
 输入参数  : pstPdnConnectReq    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnConnectReqProc
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    VOS_UINT32                          ulRet;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnInfo;
    PS_BOOL_ENUM_UINT8                  enIsInitAccessAuth;


    /* 内部调用保证指针入参非空 */

    ulRet = PPPC_EhsmPdnConnectCheckParam(pstPdnConnectReq);
    if (VOS_OK != ulRet)
    {
        PPPC_RespEhsmPdnConnectFail(pstPdnConnectReq);
        PPPC_WARNING_LOG("Pdn connect check param fail!");
        return;
    }

    /* 如果是初始接入鉴权则不入队启定时器等到接入鉴权完成后再处理 */
    enIsInitAccessAuth = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsInitAccessAuth)
    {
        /* PDN不能重复连接,元素2专门存储PDN CONN消息 */
        if (VOS_NULL_PTR != g_astActHrpdTimer[2].hDelayProcTimer)
        {
            PPPC_WARNING_LOG1("PDN reconnect!\r\n", pstPdnConnectReq->ucPdnId);
            return;
        }

        pstPdnConnInfo = (CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)PPP_Malloc(
                        sizeof(CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU));
        if (VOS_NULL_PTR == pstPdnConnInfo)
        {
            PPPC_WARNING_LOG1("Alloc mem fail.", pstPdnConnectReq->ucPdnId);
            return;
        }

        PS_MEM_CPY(pstPdnConnInfo, pstPdnConnectReq,
                sizeof(CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU));

        g_astActHrpdTimer[2].pstMsgPtr = (VOS_VOID *)pstPdnConnInfo;
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_astActHrpdTimer[2].hDelayProcTimer,
            MSPS_PID_PPPC, PPPC_ACCESS_AUTH_HRPD_ACT_DELAY_PROC_TIMER_LEN,
            (VOS_UINT32)PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_PDN,
            PPPC_ACCESS_AUTH_ACT_HRPD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        return;
    }

    /* 收到APS发给PPP的激活消息直接入队 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PPPC_SetRatMode(PPPC_RAT_MODE_EHRPD);

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid                = pstPdnConnectReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType    = pstPdnConnectReq->enMsgId;
    pstEhsmMsgNode->usOpId                     = pstPdnConnectReq->usOpId;
    pstEhsmMsgNode->ucPdnId                    = pstPdnConnectReq->ucPdnId;
    pstEhsmMsgNode->stEhsmCmdNode.enAttachType = pstPdnConnectReq->enAttachType;
    pstEhsmMsgNode->stEhsmCmdNode.enPdnType    = pstPdnConnectReq->enPdnType;
    pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause    = pstPdnConnectReq->ucAddressAllocCause;
    pstEhsmMsgNode->enIsHandling               = PS_FALSE;

    pstPppCont = &g_stPppContext;

    /* 拷贝用户名 */
    ulUserNameLen    = VOS_StrNLen((VOS_CHAR *)pstPdnConnectReq->aucUserName,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucUserName,
        (VOS_CHAR *)pstPdnConnectReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* 拷贝密码 */
    ulPasswordLen    = VOS_StrNLen((VOS_CHAR *)pstPdnConnectReq->aucPassword,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucPassword,
        (VOS_CHAR *)pstPdnConnectReq->aucPassword, ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    /* 拷贝APN */
    PS_MEM_CPY(&(pstEhsmMsgNode->stEhsmCmdNode.stApn),
        &(pstPdnConnectReq->stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPdnAddress),
        (VOS_INT8 *)&(pstPdnConnectReq->stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPco),
        (VOS_INT8 *)&(pstPdnConnectReq->stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstEhsmMsgNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPdnConnectReq->aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);


    pstEhsmMsgNode->ucPppId      = (VOS_UINT8)PPPC_GetServicePppId();

    pstEhsmPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    /* 映射ppp id和Pdn id */
    PPPC_MappingPppIdandPdnId(pstEhsmMsgNode->ucPppId, pstPdnConnectReq->ucPdnId);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmDisconnReqProcWhenAccessAuth
 功能描述  : 接入鉴权时收到Disconn请求处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-10-10
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EhsmDisconnReqProcWhenAccessAuth(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingAA;


    enIsDoingAA = PPPC_GetInitAccessAuthMode();

    if (PS_TRUE == enIsDoingAA)
    {
        if (VOS_NULL_PTR != g_astActHrpdTimer[2].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[2].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
            }
            g_astActHrpdTimer[2].hDelayProcTimer  = VOS_NULL_PTR;

            if (VOS_NULL_PTR != g_astActHrpdTimer[2].pstMsgPtr)
            {
                PPP_Free(g_astActHrpdTimer[2].pstMsgPtr);
                g_astActHrpdTimer[2].pstMsgPtr = VOS_NULL_PTR;
            }
        }

        /* 如果在做接入按鉴权Disconn不需要入队处理 */
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmDetachProcWhenAccessAuth
 功能描述  : 接入鉴权时收到Detach请求处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-10-10
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EhsmDetachProcWhenAccessAuth(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingInitAA;


    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();

    if (PS_TRUE == enIsDoingInitAA)
    {
        if (VOS_NULL_PTR != g_astActHrpdTimer[1].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[1].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
            }
            g_astActHrpdTimer[1].hDelayProcTimer  = VOS_NULL_PTR;

            if (VOS_NULL_PTR != g_astActHrpdTimer[1].pstMsgPtr)
            {
                PPP_Free(g_astActHrpdTimer[1].pstMsgPtr);
                g_astActHrpdTimer[1].pstMsgPtr = VOS_NULL_PTR;
            }
        }

        /* 收到Detach时有PDN Conn请求也不需要处理了 */
        (VOS_VOID)PPPC_EhsmDisconnReqProcWhenAccessAuth();

        /* 如果在做接入鉴权Detach不需要处理 */
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmPdnDisconnectReqProc
 功能描述  : PPPC模块处理Ehsm的PDN Disconnect请求
 输入参数  : pMsg    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnDisconnectReqProc
(
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                  enIsContinue;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstPdnDisconnectReq->ucPdnId))
    {
        PPPC_RespEhsmPdnDisconnect(CNAS_CTTF_EHRPD_RSLT_FAILURE, pstPdnDisconnectReq);
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    enIsContinue = PPPC_EhsmDisconnReqProcWhenAccessAuth();
    if (PS_FALSE == enIsContinue)
    {
        PPPC_RespEhsmPdnDisconnect(CNAS_CTTF_EHRPD_RSLT_SUCCESS, pstPdnDisconnectReq);
        return;
    }

    /* 收到APS发给PPP的去激活消息直接入队 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid             = pstPdnDisconnectReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType = pstPdnDisconnectReq->enMsgId;
    pstEhsmMsgNode->usOpId                  = pstPdnDisconnectReq->usOpId;
    pstEhsmMsgNode->ucPdnId                 = pstPdnDisconnectReq->ucPdnId;
    pstEhsmMsgNode->enIsHandling            = PS_FALSE;

    if (VOS_OK != PPPC_GetPppIdByPdn(pstEhsmMsgNode->ucPdnId, &pstEhsmMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Get Ppp Id fail!");
        PPP_Free(pstEhsmMsgNode);
        PPPC_RespEhsmPdnDisconnect(CNAS_CTTF_EHRPD_RSLT_FAILURE, pstPdnDisconnectReq);
        return;
    }

    pstEhsmPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmPdnDisconnectIndProc
 功能描述  : PPPC模块处理EHSM的本地去激活命令
 输入参数  : pstDeActInd    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnDisconnectIndProc
(
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU *pstPdnDisconnectInd
)
{
    VOS_UINT8                               ucPppId;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstPdnDisconnectInd->ucPdnId))
    {
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    /* 无条件清楚延时处理 */
    (VOS_VOID)PPPC_EhsmDisconnReqProcWhenAccessAuth();

    if (VOS_OK != PPPC_GetPppIdByPdn(pstPdnDisconnectInd->ucPdnId, &ucPppId))
    {
        PPPC_WARNING_LOG("Get Ppp Id fail!\r\n");
        return;
    }

    PPPC_ClearEhsmPdnCmdLinkNode(pstPdnDisconnectInd->ucPdnId);
    PPPC_ClearMappingByPdnId(pstPdnDisconnectInd->ucPdnId);

    /* 全局变量 PDN相关信息的清除 */
    PPP_VSNCP_ClearPdnContext(pstPdnDisconnectInd->ucPdnId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_DetachSelf
 功能描述  : 如果本地是eHRPD模式收到切换到1X/HRPD模式的消息需要先本地去激活
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-12-29
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_DetachSelf(VOS_VOID)
{
    PPPINFO_S                              *pstPppInfo;
    VOS_UINT8                               ucPppId;


    /* 内部调用保证指针入参非空 */

    ucPppId                 = (VOS_UINT8)PPPC_GetServicePppId();
    pstPppInfo              = &g_astPppPool[ucPppId];

    /* 无条件清除延时处理 */
    (VOS_VOID)PPPC_EhsmDetachProcWhenAccessAuth();

    /* 必须无条件清除本地资源 */
    PPPC_ClearApsCmdLinkNode();
    PPP_DeleteCB(pstPppInfo, PS_FALSE);

    PPPC_DeletePppId(ucPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmLocDetachIndProc
 功能描述  : PPPC模块处理EHSM的本地去激活命令
 输入参数  : pstDetachInd    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmLocDetachIndProc(CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU *pstDetachInd)
{
    PPPC_DetachSelf();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgEhsmProc
 功能描述  : PPPC模块处理EHSM命令
 输入参数  : pMsg    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgEhsmProc(struct MsgCB * pMsg)
{
    Cnas_cttf_ehrpd_ehsm_ppp_pif_MSG       *pstEhsmPppPublicInfo;
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU        *pstAttachReq;
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU        *pstDetachReq;
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU      *pstPdnConnectReq;
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU      *pstPdnDisconnectReq;
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU  *pstPdnDiscconectInd;
    CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU    *pstDetachInd;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;


    /* 前面已经保证pMsg非空 */

    pstEhsmPppPublicInfo        = (Cnas_cttf_ehrpd_ehsm_ppp_pif_MSG *)pMsg;
    enMsgType                   = pstEhsmPppPublicInfo->stMsgReq.ulMsgId;

    switch(enMsgType)
    {
        /* Attach请求 */
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            pstAttachReq         = (CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)pMsg;

            PPPC_EhsmAttachReqProc(pstAttachReq);

            break;
        /* Detach请求 */
        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            pstDetachReq         = (CNAS_CTTF_EHRPD_DETACH_REQ_STRU *)pMsg;

            PPPC_EhsmDetachReqProc(pstDetachReq);

            break;
        /* PDN Connect请求 */
        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            pstPdnConnectReq        = (CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)pMsg;

            PPPC_EhsmPdnConnectReqProc(pstPdnConnectReq);

            break;
        /* PDN Disconnect请求 */
        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            pstPdnDisconnectReq     = (CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU *)pMsg;

            PPPC_EhsmPdnDisconnectReqProc(pstPdnDisconnectReq);

            break;

        /* 本地PDN断开 */
        case ID_CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND:

            pstPdnDiscconectInd     = (CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU *)pMsg;

            PPPC_EhsmPdnDisconnectIndProc(pstPdnDiscconectInd);

            break;

        /* 本地去激活 */
        case ID_CNAS_CTTF_EHRPD_LOC_DETACH_IND:

            pstDetachInd            = (CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU *)pMsg;

            PPPC_EhsmLocDetachIndProc(pstDetachInd);

            break;

        /* NAS通知的链路状态消息，不作处理 */
        case ID_CNAS_CTTF_EHRPD_LINK_STATUS_NTF:

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ActReqMsgNodeProc
 功能描述  : PPPC模块激活消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-04
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ActReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    VOS_UINT32                              ulPapSwitch = PPPC_AUTH_SWITCH_ON;
    VOS_UINT32                              ulChapSwitch = PPPC_AUTH_SWITCH_ON;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    if (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        enIsHandling    = pstApsCurrHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 存储收到激活消息时APS的PID和接入模式 */
    g_stPppContext.ulSendPid = pstApsCurrHeadNode->ulSenderPid;

    switch(pstApsCurrHeadNode->stApsCmdNode.enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
            PPPC_SetRatMode(PPPC_RAT_MODE_1X);
            PPPC_GetAuthSwitch(pstApsCurrHeadNode->stApsCmdNode.enAuthType, &g_stPppContext, &ulPapSwitch, &ulChapSwitch);
            break;
        case TAF_APS_PPP_RAT_MODE_HRPD:
            PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
            PPPC_GetAuthSwitch(pstApsCurrHeadNode->stApsCmdNode.enAuthType, &g_stPppContext, &ulPapSwitch, &ulChapSwitch);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Rate Mode is %d.\r\n", pstApsCurrHeadNode->stApsCmdNode.enMode);
            break;
    }

    /* 考虑对冲场景，必须保证串行处理 */
    if (PS_FALSE == enIsHandling)
    {
        pstApsCurrHeadNode->enIsHandling = PS_TRUE;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        PPP_HDLC_HARD_SetUp(pstApsCurrHeadNode->ucPppId);

#endif
        /* 设置鉴权开关 */
        PPPC_SetAuthSwitch(ulPapSwitch, ulChapSwitch);

        /* PPP发起建链 */
        PPPC_SetupPpp(pstApsCurrHeadNode->ucPppId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_DeActReqMsgNodeProc
 功能描述  : PPPC模块去激活消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-04
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_DeActReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    VOS_UINT32                              ulLcpSendFlag;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    /* 考虑对冲场景，必须保证串行处理 */
    if (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        enIsHandling    = pstApsCurrHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }


    if (PS_FALSE == enIsHandling)
    {
        pstApsCurrHeadNode->enIsHandling = PS_TRUE;

        /* 此时需要发送ppp terminate协商报文 */
        ulLcpSendFlag                    = 1;

        /* PPP发起PPP去激活 */
        PPPC_LinkDown(pstApsCurrHeadNode->ucPppId, ulLcpSendFlag);
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_TafMsgNodeProc
 功能描述  : PPPC模块消息节点处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafMsgNodeProc(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    PS_BOOL_ENUM_UINT8                      enIsDoingInitAA = PS_FALSE;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 如果当前正在进行初始接入鉴权,不能同时做PPP的业务协商 */
    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsDoingInitAA)
    {
        PPPC_WARNING_LOG("It is now doing access authentication!\r\n");
        return;
    }

    enMsgType           = pstCurrentHeadNode->stApsCmdNode.enMsgType;
    switch(enMsgType)
    {
        case ID_APS_PPP_ACT_REQ:

            PPPC_ActReqMsgNodeProc();

            break;

        case ID_APS_PPP_DEACT_REQ:

            PPPC_DeActReqMsgNodeProc();

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Aps Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_RespApsPdnIsActived
功能描述  : 成功建立1X连接后，以重复的PdnId再次激活，PPP回复成功激活的消息
输入参数  :    APS_PPP_ACT_REQ_STRU    *pApsActReq,
                VOS_VOID               *pPppInfo,
                VOS_UINT32              ulResult
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-07-28
作    者   : zWX297122
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsPdnIsActived
(
    APS_PPP_ACT_REQ_STRU               *pApsActReq,
    VOS_VOID                           *pPppInfo,
    VOS_UINT32                          ulResult
)
{
    PPPINFO_S                          *pstPppInfo;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;


    /* 申请响应消息内存 */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsActCnf->ulReceiverPid         = pApsActReq->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pApsActReq->usOpId;
    pstApsActCnf->ulResult              = ulResult;
    pstApsActCnf->ucPdnId               = pApsActReq->ucPdnId;
    pstApsActCnf->enPdnType             = pApsActReq->enPdnType;

    pstApsActCnf->usMtu                 = PPPC_MAX_FRAME_LEN;

    if (VOS_NULL_PTR != pPppInfo)
    {
        /* 非空说明应该是激活成功，需要把DNS和IP地址填入 */
        pstPppInfo                                = (PPPINFO_S *)pPppInfo;
        pstLcpInfo                                = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
        pstIpcpInfo                               = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
        pstIpv6cpInfo                             = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

        if (VOS_NULL_PTR != pstLcpInfo)
        {
            pstApsActCnf->usMtu                   = pstLcpInfo->stHisOptions.mru;
        }

        if (VOS_NULL_PTR != pstIpcpInfo)
        {
            pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
            pstApsActCnf->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
            pstApsActCnf->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
            PS_MEM_CPY(pstApsActCnf->aucIpv4Addr, &(pstIpcpOption->ouraddr),
                sizeof(pstApsActCnf->aucIpv4Addr));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS));
        }

        if (VOS_NULL_PTR != pstIpv6cpInfo)
        {
            pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);

            PS_MEM_CPY(pstApsActCnf->aucIpv6Addr + TAF_APS_PPP_IPV6_ADDR_LEN/2,
                pstIpv6cpOption->OurV6InId, TAF_APS_PPP_IPV6_ADDR_LEN/2);
        }
    }

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    return ;
}

/*****************************************************************************
 函 数 名  : PPPC_AccessAuthSuccProc
 功能描述  : 初始接入鉴权成功时的处理,需要停定时器并处理激活消息,另外不能忘记释放
             激活消息的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-10-10
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_AccessAuthSuccProc(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRet;


    for (ulIndex = 0; ulIndex < PPPC_ACCESS_AUTH_DELAY_PROC_TIMER_MAX_NUM; ulIndex++)
    {
        if (VOS_NULL_PTR == g_astActHrpdTimer[ulIndex].hDelayProcTimer)
        {
            continue;
        }

        ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[ulIndex].hDelayProcTimer);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Stop timer fail!", ulRet, ulIndex);
        }

        g_astActHrpdTimer[ulIndex].hDelayProcTimer = VOS_NULL_PTR;

        if (VOS_NULL_PTR == g_astActHrpdTimer[ulIndex].pstMsgPtr)
        {
            continue;
        }

        if (0 == ulIndex)
        {
            /* 激活HRPD的消息入队处理 */
            PPPC_TafActReqProc((APS_PPP_ACT_REQ_STRU *)g_astActHrpdTimer[ulIndex].pstMsgPtr);
            PPP_Free(g_astActHrpdTimer[ulIndex].pstMsgPtr);
        }
        else
        {
            /* 激活eHRPD的Attach消息或PDN消息入队处理 */
            PPPC_MsgEhsmProc((struct MsgCB *)g_astActHrpdTimer[ulIndex].pstMsgPtr);
            PPP_Free(g_astActHrpdTimer[ulIndex].pstMsgPtr);
        }
        g_astActHrpdTimer[ulIndex].pstMsgPtr    = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_StopAccessAuthDelayProcTimer
 功能描述  : TAF去激活PPP时需要判断当前是否正在做接入鉴权.如果正在做初始接入鉴权,
             检查是否有HRPD的延时定时器在运行,有则停定时器.
 输入参数  : pstPppActReq    TAF激活消息
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8 PS_TRUE:继续向后执行 PS_FALSE:返回
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-10-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_StopAllAccessAuthDelayProcTimer(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRet;


    for (ulIndex = 0; ulIndex < PPPC_ACCESS_AUTH_DELAY_PROC_TIMER_MAX_NUM; ulIndex++)
    {
        if (VOS_NULL_PTR != g_astActHrpdTimer[ulIndex].pstMsgPtr)
        {
            switch ((PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16)ulIndex)
            {
                case PPPC_ACCESS_AUTH_ACT_MODE_HRPD:
                    PPPC_RespApsActFail((APS_PPP_ACT_REQ_STRU *)g_astActHrpdTimer[0].pstMsgPtr);
                    break;
                case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_ATTACH:
                    PPPC_RespEhsmAttachFail((CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)g_astActHrpdTimer[1].pstMsgPtr);
                    break;
                case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_PDN:
                    PPPC_RespEhsmPdnConnectFail((CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)g_astActHrpdTimer[2].pstMsgPtr);
                    break;
                default:
                    break;
            }
            PPP_Free(g_astActHrpdTimer[ulIndex].pstMsgPtr);
            g_astActHrpdTimer[ulIndex].pstMsgPtr = VOS_NULL_PTR;
        }

        if (VOS_NULL_PTR != g_astActHrpdTimer[ulIndex].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[ulIndex].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG2("Stop timer fail!", ulRet, ulIndex);
                continue;
            }

            g_astActHrpdTimer[ulIndex].hDelayProcTimer = VOS_NULL_PTR;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafDeactProcWhenAccessAuth
 功能描述  : TAF去激活PPP时需要判断当前是否正在做接入鉴权.如果正在做初始接入鉴权,
             检查是否有HRPD的延时定时器在运行,有则停定时器.
 输入参数  : pstPppActReq    TAF激活消息
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8 PS_TRUE:继续向后执行 PS_FALSE:返回
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-10-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_TafDeactProcWhenAccessAuth
(
    TAF_APS_PPP_RAT_MODE_ENUM_UINT8     enRateMode
)
{
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingInitAA;


    /* 不在做初始接入鉴权,则按照原来流程继续执行 */
    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();
    if (PS_FALSE == enIsDoingInitAA)
    {
        return PS_TRUE;
    }


    if (TAF_APS_PPP_RAT_MODE_1X == enRateMode)
    {
        PPPC_WARNING_LOG("Receive 1X deact msg when doing InitAccessAuth");
        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* 初始接入鉴权只要设置一次即可 */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        PPPC_StopAllAccessAuthDelayProcTimer();
        return PS_TRUE;
    }
    else
    {
        PPPC_WARNING_LOG("Receive HRPD deact msg when doing InitAccessAuth");
        if (VOS_NULL_PTR != g_astActHrpdTimer[0].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[0].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
            }

            if (VOS_NULL_PTR != g_astActHrpdTimer[0].pstMsgPtr)
            {
                PPP_Free(g_astActHrpdTimer[0].pstMsgPtr);
                g_astActHrpdTimer[0].pstMsgPtr = VOS_NULL_PTR;
            }

            g_astActHrpdTimer[0].hDelayProcTimer = VOS_NULL_PTR;

        }
        return PS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : PPPC_TafActProcWhenInitAccessAuth
 功能描述  : TAF激活PPP时需要判断当前是否正在做接入鉴权.如果正在做初始接入鉴权,
             激活1X时需要停定时器,且停止接入鉴权;激活HRPD时启定时器延时处理.
 输入参数  : pstPppActReq    TAF激活消息
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8 PS_TRUE:继续向后执行 PS_FALSE:返回
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-10-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_TafActProcWhenInitAccessAuth
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    APS_PPP_ACT_REQ_STRU               *pstHrpdInfo;
    PS_BOOL_ENUM_UINT8                  enIsInitAccessAuth;
    PPPINFO_S                          *pstPppInfo;


    /* 不在做初始接入鉴权,则按照原来流程继续执行 */
    enIsInitAccessAuth = PPPC_GetInitAccessAuthMode();
    if (PS_FALSE == enIsInitAccessAuth)
    {
        PPPC_WARNING_LOG1("It is not doing AA now.", enIsInitAccessAuth);
        return PS_TRUE;
    }

    if (TAF_APS_PPP_RAT_MODE_1X == pstPppActReq->enMode)
    {
        PPPC_WARNING_LOG2("Receive 1X act msg when doing AA.",
            enIsInitAccessAuth, pstPppActReq->enMode);

        pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];

        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* 初始接入鉴权只要设置一次即可 */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        PPPC_StopAllAccessAuthDelayProcTimer();

        PPP_Core_NotifyUperLcpDown(pstPppInfo);

        return PS_TRUE;
    }
    else
    {
        /* NAS不能重复激活 */
        if (VOS_NULL_PTR != g_astActHrpdTimer[0].hDelayProcTimer)
        {
            PPPC_WARNING_LOG1("Hrpd act timer has been already run.",
                    pstPppActReq->ucPdnId);
            return PS_FALSE;
        }

        pstHrpdInfo = (APS_PPP_ACT_REQ_STRU *)PPP_Malloc(
                        sizeof(APS_PPP_ACT_REQ_STRU));
        if (VOS_NULL_PTR == pstHrpdInfo)
        {
            PPPC_WARNING_LOG1("Alloc mem fail.", pstPppActReq->ucPdnId);
            return PS_FALSE;
        }

        PS_MEM_CPY(pstHrpdInfo, pstPppActReq, sizeof(APS_PPP_ACT_REQ_STRU));

        g_astActHrpdTimer[0].pstMsgPtr = (VOS_VOID *)pstHrpdInfo;
        /* 如果在做初始接入鉴权时收到激活HRPD的请求则启定时器延时处理,返回FALSE */
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_astActHrpdTimer[0].hDelayProcTimer,
            MSPS_PID_PPPC, PPPC_ACCESS_AUTH_HRPD_ACT_DELAY_PROC_TIMER_LEN,
            (VOS_UINT32)PPPC_ACCESS_AUTH_ACT_MODE_HRPD, PPPC_ACCESS_AUTH_ACT_HRPD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        return PS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : PPPC_TafActReqProc
 功能描述  : PPPC模块处理TAF的PPP激活命令
 输入参数  : pMsg    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-24
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafActReqProc
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    VOS_UINT8                           ucPppId = 0;
    VOS_UINT32                          ulRetVal;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    PS_BOOL_ENUM_UINT8                  enIsContinue;


    /* 内部调用保证指针入参非空 */

    /* 对ucPdnId进行检查 */
    if (VOS_OK != PPPC_CheckPdnId(pstPppActReq->ucPdnId))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input PdnId is too large! %d\r\n", pstPppActReq->ucPdnId);
        return;
    }

    /* 对enMode进行检查 */
    if (VOS_OK != PPPC_CheckRateMode(pstPppActReq->enMode))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input Rate mode is error! %d\r\n", pstPppActReq->enMode);
        return;
    }

    /* 对enPdnType进行检查 */
    if (VOS_OK != PPPC_CheckPdnType(pstPppActReq->enPdnType))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input Pdn type is error! %d\r\n", pstPppActReq->enPdnType);
        return;
    }

    /* 1X模式下一个PppId只与一个PdnId对应，需要检查重复的PdnId*/
    ulRetVal = PPPC_GetPppIdByPdn(pstPppActReq->ucPdnId, &ucPppId);
    if (VOS_OK == ulRetVal)
    {
        pstPppInfo = &g_astPppPool[ucPppId];

        /* 入参中的PdnId已成功建立连接 */
        if ((PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
            &&  (1 == pstPppInfo->bPppSuccess))
        {
            /* PPP发送激活成功的消息 */
            PPPC_RespApsPdnIsActived(pstPppActReq, pstPppInfo, VOS_OK);

            PPPC_WARNING_LOG2("The PDN has been actived! %d\r\n",
                ucPppId, pstPppActReq->ucPdnId);

            return ;
        }
    }

    /* 判断是否在做初始接入鉴权决定是否申请节点入队继续往后执行 */
    enIsContinue = PPPC_TafActProcWhenInitAccessAuth(pstPppActReq);
    if (PS_TRUE != enIsContinue)
    {
        PPPC_WARNING_LOG2("It is doing AA now! %d\r\n",
            ucPppId, pstPppActReq->ucPdnId);
        return;
    }

    /* 收到APS发给PPP的激活消息直接入队 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstApsMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstApsMsgNode->stNode));

    pstApsMsgNode->ulSenderPid               = pstPppActReq->ulSenderPid;
    pstApsMsgNode->stApsCmdNode.enMsgType    = pstPppActReq->enMsgId;
    pstApsMsgNode->usOpId                    = pstPppActReq->usOpId;
    pstApsMsgNode->ucPdnId                   = pstPppActReq->ucPdnId;
    pstApsMsgNode->stApsCmdNode.enMode       = pstPppActReq->enMode;
    pstApsMsgNode->stApsCmdNode.enPdnType    = pstPppActReq->enPdnType;
    pstApsMsgNode->stApsCmdNode.enAuthType   = pstPppActReq->enAuthType;
    pstApsMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_AddPppId(&pstApsMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Add Ppp Id fail!");
        PPP_Free(pstApsMsgNode);
        PPPC_RespApsActFail(pstPppActReq);
        return;
    }

    pstPppCont       = &g_stPppContext;

    /* 拷贝用户名 */
    ulUserNameLen    = VOS_StrNLen((VOS_CHAR *)pstPppActReq->aucUserName,
                            TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucUserName,
        (VOS_CHAR *)pstPppActReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* 拷贝密码 */
    ulPasswordLen    = VOS_StrNLen((VOS_CHAR *)pstPppActReq->aucPassword,
                            TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_CHAR *)(pstPppCont->aucPassword),
        (VOS_CHAR *)(pstPppActReq->aucPassword), ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    pstApsPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstApsPppCmdLink, &(pstApsMsgNode->stNode));


    /* 存储modem id */
    g_stPppContext.enModemId    = VOS_GetModemIDFromPid(pstPppActReq->ulSenderPid);

    /* 映射Pdn id和ppp id */
    PPPC_MappingPppIdandPdnId(pstApsMsgNode->ucPppId, pstPppActReq->ucPdnId);

    PPPC_TafMsgNodeProc();

    pstPppInfo                  = &g_astPppPool[pstApsMsgNode->ucPppId];
    PPPC_SetIpCapability(pstPppActReq->enPdnType, pstPppInfo, pstApsMsgNode->ulSenderPid);

    pstPppInfo->bEhrpdUser      = VOS_FALSE;

    /* ppp id映射到PPP内部需要自增 */
    pstPppInfo->ulRPIndex       = pstApsMsgNode->ucPppId;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafDeActReqProc
 功能描述  : PPPC模块处理TAF的PPP去激活命令
 输入参数  : pMsg    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-24
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafDeActReqProc(APS_PPP_DEACT_REQ_STRU *pstPppDeActReq)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsContinue;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstPppDeActReq->ucPdnId))
    {
        PPPC_RespApsDeActFail(pstPppDeActReq);
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    /* 如果在ppp deact状态下, 收到taf的DeactReq消息，则直接给taf回DeactSucc */
    if (PPPC_MIN_ACTIVE_ENTITY >= g_stPppContext.ulPppIdBitMask)
    {
        PPPC_WARNING_LOG("Rcv TafDeActReq Msg when ppp deact.");
        PPPC_RespApsDeActDirect(PS_SUCC, pstPppDeActReq);
        return;
    }

    enIsContinue = PPPC_TafDeactProcWhenAccessAuth(pstPppDeActReq->enMode);
    if (PS_FALSE == enIsContinue)
    {
        PPPC_RespApsDeActDirect(PS_SUCC, pstPppDeActReq);
        return;
    }

    /* 收到deact消息应优先处理，此时要清空队列中的所有节点 */
    PPPC_ClearApsCmdLinkNode();

    /* 收到APS发给PPP的去激活消息直接入队 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstApsMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstApsMsgNode->stNode));

    pstApsMsgNode->ulSenderPid               = pstPppDeActReq->ulSenderPid;
    pstApsMsgNode->stApsCmdNode.enMsgType    = pstPppDeActReq->enMsgId;
    pstApsMsgNode->usOpId                    = pstPppDeActReq->usOpId;
    pstApsMsgNode->ucPdnId                   = pstPppDeActReq->ucPdnId;
    pstApsMsgNode->stApsCmdNode.enMode       = pstPppDeActReq->enMode;
    pstApsMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_GetPppIdByPdn(pstApsMsgNode->ucPdnId, &pstApsMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG1("Get Ppp Id fail! ucPdnID:%d.\n", pstApsMsgNode->ucPdnId);
        PPP_Free(pstApsMsgNode);
        PPPC_RespApsDeActFail(pstPppDeActReq);
        return;
    }

    pstApsPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstApsPppCmdLink, &(pstApsMsgNode->stNode));

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafDeActIndProc
 功能描述  : PPPC模块处理TAF的本地去激活命令
 输入参数  : pstDeActInd    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafDeActIndProc(APS_PPP_DEACT_IND_STRU *pstDeActInd)
{
    PPPINFO_S                              *pstPppInfo;
    VOS_UINT8                               ucPppId;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstDeActInd->ucPdnId))
    {
        PPPC_WARNING_LOG1("Input PdnId is too large! ucPdnId:%d\r\n", pstDeActInd->ucPdnId);
        return;
    }

    /* 无条件向下执行,不需要判定返回值 */
    (VOS_VOID)PPPC_TafDeactProcWhenAccessAuth(pstDeActInd->enMode);

    if (VOS_OK != PPPC_GetPppIdByPdn(pstDeActInd->ucPdnId, &ucPppId))
    {
        PPPC_WARNING_LOG1("Get Ppp Id fail! ucPdnId:%d\r\n", pstDeActInd->ucPdnId);
        return;
    }

    pstPppInfo              = &g_astPppPool[ucPppId];

    /* 必须无条件清除本地资源 */
    PPPC_ClearApsCmdLinkNode();
    PPP_DeleteCB(pstPppInfo, PS_FALSE);

    PPPC_DeletePppId(ucPppId);

    /* 对PDN信息进行清除 */
    /* todo */

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafModeChangeNtfProc
 功能描述  : PPPC模块处理TAF的模式切换命令
 输入参数  : pstModeChangeNtf   TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-04
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafModeChangeNtfProc(APS_PPP_MODE_CHANGE_NTF_STRU *pstModeChangeNtf)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    PPPINFO_S                          *pstPppInfo;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstModeChangeNtf->ucPdnId))
    {
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    enRatMode = PPPC_GetRatMode();
    if (PPPC_RAT_MODE_EHRPD == enRatMode)
    {
        PPPC_DetachSelf();
        PPPC_WARNING_LOG("Rat mode is eHRPD,should detach self!\r\n");
        return;
    }
    else if (PPPC_RAT_MODE_1X == enRatMode)
    {
        /* 从1X起到HRPD且业务PPP处于激活态时需要通知PA打开流 */
        pstPppInfo = &g_astPppPool[PPPC_PPP_ID_MIN];

        if ((TAF_APS_PPP_RAT_MODE_HRPD == pstModeChangeNtf->enMode)
            && (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg))
        {
            PPPC_HRPD_SendOpenStreamReq();
        }
    }
    else
    {
        /* 编程规范 */
    }

    switch(pstModeChangeNtf->enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
            PPPC_SetRatMode(PPPC_RAT_MODE_1X);

            /* 从hrpd切到1x时，需要将hrpd相关的定时器都停掉 */
            PPPC_StopAllAccessAuthDelayProcTimer();
            break;
        case TAF_APS_PPP_RAT_MODE_HRPD:
            PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Rate Mode is %d.\r\n", pstModeChangeNtf->enMode);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafDialModeNtfProc
 功能描述  : PPPC模块处理TAF的拨号模式切换命令
 输入参数  : pstDialModeNtf   TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-01
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafDialModeNtfProc(APS_PPP_DIAL_MODE_NTF_STRU *pstDialModeNtf)
{
    /* 内部调用保证指针入参非空 */

    switch(pstDialModeNtf->enDialMode)
    {
        case TAF_APS_PPP_CDATA_DIAL_MODE_RELAY:
        case TAF_APS_PPP_CDATA_DIAL_MODE_NETWORK:
            PPPC_SetDialMode(pstDialModeNtf->enDialMode);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Dial Mode is %d.\r\n", pstDialModeNtf->enDialMode);
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_HRPD_RcvCommittedIndProc
 功能描述  : PPPC模块收到RPA的committed配置消息处理,保存APP和Stream的映射关系
 输入参数  : pMsg    PA配置消息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_RcvCommittedIndProc(struct MsgCB * pMsg)
{
    CTTF_PPP_HRPD_COMMITTED_IND_STRU   *pstCommttedInd;
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    VOS_UINT32                          ulIndex;


    pstCommttedInd  = (CTTF_PPP_HRPD_COMMITTED_IND_STRU*)pMsg;

    g_stPppContext.enModemId    = pstCommttedInd->enModemId;

    pstHrpdContext  = &(g_stPppContext.stHrpdContext);

    for (ulIndex = 0; ulIndex < PPPC_MAX_PA_BINDING_APP_NUM; ulIndex++)
    {
        /* 分别存放Stream1,2,3 */
        pstHrpdContext->aenApplicationType[ulIndex]
            = pstCommttedInd->enApplicationType[ulIndex];
    }

    pstHrpdContext->enIsSendOpenFlag = PS_FALSE;

    /* 读取卡文件 */
    (VOS_VOID)PPPC_ReadFixedData();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_RcvReservationsIndProc
 功能描述  : PPPC模块收到RPA的Reservation个数配置消息处理,保存到上下文中
 输入参数  : pMsg    PA配置消息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_RcvReservationsIndProc(struct MsgCB * pMsg)
{
    CTTF_PPP_HRPD_RESERVATIONS_IND_STRU    *pstReservationsInd;


    pstReservationsInd      = (CTTF_PPP_HRPD_RESERVATIONS_IND_STRU*)pMsg;

    PA_AGENT_HRPD_SetMaxReservNum(pstReservationsInd);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_SendOpenStreamReq
 功能描述  : PPPC模块准备好收发数据时通知PA打开Stream
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendOpenStreamReq(VOS_VOID)
{
    PPPC_HRPD_CONTEXT_STRU                 *pstHrpdContext;
    PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU  *pstPppOpenStreamReq;


    pstHrpdContext      = &(g_stPppContext.stHrpdContext);

    /* 如果已经发过，不需要发送打开流的请求消息 */
    if (PS_TRUE == pstHrpdContext->enIsSendOpenFlag)
    {
        PPPC_WARNING_LOG("No need to send open stream request!\r\n");
        return;
    }
    pstHrpdContext->enIsSendOpenFlag = PS_TRUE;

    pstPppOpenStreamReq = (PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU));
    if (VOS_NULL_PTR == pstPppOpenStreamReq)
    {
        PPPC_ERROR_LOG("Alloc Ppp Open Stream Mem Fail!\r\n");
        return;
    }

    pstPppOpenStreamReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppOpenStreamReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppOpenStreamReq->enMsgId        = ID_PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ;
    pstPppOpenStreamReq->usOpId         = 0;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppOpenStreamReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_SendCloseStreamReq
 功能描述  : PPPC模块不能收发数据时通知PA关闭Stream
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendCloseStreamReq(VOS_VOID)
{
    PPPC_HRPD_CONTEXT_STRU              *pstHrpdContext;
    PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU  *pstPppCloseStreamReq;


    pstHrpdContext      = &(g_stPppContext.stHrpdContext);
    /* 如果已经发过，不需要发送关闭流的请求消息 */
    if (PS_FALSE == pstHrpdContext->enIsSendOpenFlag)
    {
        PPPC_WARNING_LOG("No need to send close stream request!\r\n");
        return;
    }
    pstHrpdContext->enIsSendOpenFlag = PS_FALSE;

    pstPppCloseStreamReq = (PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU));
    if (VOS_NULL_PTR == pstPppCloseStreamReq)
    {
        PPPC_ERROR_LOG("Alloc ppp close stream mem fail!\r\n");
        return;
    }

    pstPppCloseStreamReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppCloseStreamReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppCloseStreamReq->enMsgId        = ID_PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ;
    pstPppCloseStreamReq->usOpId         = 0;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppCloseStreamReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_GetStreamNumByAppType
 功能描述  : 根据应用类型从上下文中获取流号
 输入参数  : enAppType    应用携带的QoS信息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_HRPD_GetStreamNumByAppType
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType,
    VOS_UINT8                                  *pucStreamNum
)
{
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    VOS_UINT32                          ulIndex;


    pstHrpdContext  = &(g_stPppContext.stHrpdContext);
    for (ulIndex = 0; ulIndex < PPPC_MAX_PA_BINDING_APP_NUM; ulIndex++)
    {
        if (enAppType == pstHrpdContext->aenApplicationType[ulIndex])
        {
            *pucStreamNum   = (VOS_UINT8)ulIndex + 1;
            return VOS_OK;
        }
    }

    PPPC_WARNING_LOG1("Warning:Do not have this app info!", enAppType);

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_GetAppTypeByStreamNum
 功能描述  : 根据流号获取应用类型
 输入参数  : ucStreamNum    流号
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-09-29
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_HRPD_GetAppTypeByStreamNum
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16  *penAppType,
    VOS_UINT8                                   ucStreamNum
)
{
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;


    if ((ucStreamNum > PPPC_MAX_PA_BINDING_APP_NUM) || (0 == ucStreamNum))
    {
        PPPC_WARNING_LOG1("Input invalid stream number!", ucStreamNum);
        return VOS_ERR;
    }

    pstHrpdContext  = &(g_stPppContext.stHrpdContext);
    *penAppType     = pstHrpdContext->aenApplicationType[ucStreamNum-1];

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPPC_HRPD_SendOpenQoSReq
 功能描述  : PPPC模块通知PA做QoS协商
 输入参数  : pstQoSInfo    应用携带的QoS信息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendOpenQoSReq(PPPC_HRPD_RESERVATION_QOS_INFO_STRU *pstQoSInfo)
{
    PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU    *pstQoSReq;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStreamNum;


    if (VOS_NULL_PTR == pstQoSInfo)
    {
        PPPC_WARNING_LOG("Warning:Input parameter is null!");
        return;
    }

    ulRet   = PPPC_HRPD_GetStreamNumByAppType(pstQoSInfo->enApplicationType, &ucStreamNum);
    if (VOS_OK != ulRet)
    {
        return;
    }

    pstQoSReq   = (PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU));
    if (VOS_NULL_PTR == pstQoSReq)
    {
        PPPC_ERROR_LOG("Alloc ppp open qos mem fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstQoSReq + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstQoSReq->ulReceiverPid    = CTTF_PID_HRPD_RPA;
    pstQoSReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQoSReq->enMsgId          = ID_PPP_CTTF_HRPD_MFPA_QOS_REQ;
    pstQoSReq->usOpId           = 0;
    pstQoSReq->ucStreamNumber   = ucStreamNum;
    pstQoSReq->ucNumFwdReservations = pstQoSInfo->ucNumFwdReservations;
    pstQoSReq->ucNumRevReservations = pstQoSInfo->ucNumRevReservations;
    PS_MEM_CPY(pstQoSReq->astFwdReservations, pstQoSInfo->astFwdReservations,
                sizeof(pstQoSReq->astFwdReservations));
    PS_MEM_CPY(pstQoSReq->astRevReservations, pstQoSInfo->astRevReservations,
                sizeof(pstQoSReq->astRevReservations));

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstQoSReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_MFPA_QOS_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_SendCloseQoSReq
 功能描述  : PPPC模块通知PA做关闭QoS协商
 输入参数  : pstCloseQoSInfo    应用携带的QoS信息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendCloseQoSReq
(
    PPPC_HRPD_RESERVATION_QOS_CLOSE_INFO_STRU *pstQoSCloseInfo
)
{
    PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU  *pstQoSCloseReq;


    if (VOS_NULL_PTR == pstQoSCloseInfo)
    {
        PPPC_WARNING_LOG("Warning:Input parameter is null!");
        return;
    }

    pstQoSCloseReq   = (PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU));
    if (VOS_NULL_PTR == pstQoSCloseReq)
    {
        PPPC_ERROR_LOG("Alloc ppp close qos mem fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstQoSCloseReq + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstQoSCloseReq->ulReceiverPid    = CTTF_PID_HRPD_RPA;
    pstQoSCloseReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQoSCloseReq->enMsgId          = ID_PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ;
    pstQoSCloseReq->usOpId           = 0;
    pstQoSCloseReq->ucNumFwdReservations = pstQoSCloseInfo->ucNumFwdReservations;
    pstQoSCloseReq->ucNumRevReservations = pstQoSCloseInfo->ucNumRevReservations;

    PS_MEM_CPY(pstQoSCloseReq->aucFwdReservationLabels, pstQoSCloseInfo->aucFwdReservationLabels,
                sizeof(pstQoSCloseReq->aucFwdReservationLabels));
    PS_MEM_CPY(pstQoSCloseReq->aucRevReservationLabels, pstQoSCloseInfo->aucRevReservationLabels,
                sizeof(pstQoSCloseReq->aucRevReservationLabels));

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstQoSCloseReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_GetFileReq
 功能描述  : 读取文件通知
 输入参数  : USIMM_DEF_FILEID_ENUM_UINT32 enFileID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-25
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_HRPD_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileID)
{
    USIMM_READFILE_REQ_STRU            *pstMsg;
    VOS_CHAR                           *pcFilePath;


    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        /*返回函数错误信息*/
        return VOS_ERR;
    }

    /* 申请消息内存 */
    pstMsg   = (USIMM_READFILE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_READFILE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*填充消息内容*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (MODEM_ID_0 == g_stPppContext.enModemId)
    {
        pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_USIM;
    }
    else
    {
        pstMsg->stMsgHeader.ulReceiverPid     = I1_WUEPS_PID_USIM;
    }
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_CDMA_APP;

    pstMsg->stFilePath.ulPathLen              = VOS_StrLen(pcFilePath);
    VOS_MemCpy(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_READFILE_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_IsCaveAlgorithmEnable
 功能描述  : HRPD模式接入鉴权是否支持CAVE算法
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8 PS_FALSE不支持，PS_TRUE支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月01日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsCaveAlgorithmEnable(VOS_VOID)
{
    return g_stPppContext.enCaveEnable;
}

/*****************************************************************************
 函 数 名  : PPPC_SaveAccessAuthUserNameInfo
 功能描述  : 保存接入鉴权的用户名信息
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月25日
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SaveAccessAuthUserNameInfo(VOS_UINT8 *pstMsg)
{
    VOS_UINT8                          *pucTemp = pstMsg;
    VOS_UINT8                           ucNAILen;


    /* refer to 3GPP2 C.S0016-D v2.0 Section 3.5.8.13 */
    /* MsgLen | NAILen | Access Auth User Name |
         8bit     8bit        1~127Butes         */
    pucTemp++;
    ucNAILen = *pucTemp;
    pucTemp++;

    if (ucNAILen <= CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN)
    {
        PS_MEM_CPY(g_stPppContext.stHrpdContext.aucAccessAuthUserName, pucTemp, ucNAILen);
        g_stPppContext.stHrpdContext.aucAccessAuthUserName[ucNAILen] = '\0';
        g_stPppContext.stHrpdContext.ucAccessAuthLen    = ucNAILen;
    }
    else
    {
        PPPC_WARNING_LOG1("the length of access auth user name is error. NAILen:%d.\n", ucNAILen);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SaveRunCaveRandu
 功能描述  : 保存RAND
 输入参数  : VOS_UINT32 ulRandu
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SaveRunCaveRandu(VOS_UINT32 ulRandu)
{
    g_stPppContext.stHrpdContext.ulRandu = ulRandu;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetRunCaveRandu
 功能描述  : 保存RAND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_GetRunCaveRandu(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.ulRandu;
}

/*****************************************************************************
 函 数 名  : PPPC_UsimmCdmaSpecAuthProc
 功能描述  : CHAP鉴权MD5算法计算回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月29日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_UsimmCdmaSpecAuthProc(USIMM_CDMASPECAUTH_CNF_STRU *pstMsg)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstActPppNode = VOS_NULL_PTR;
    PPPINFO_S                          *pstPppInfo;
    PPPCHAPINFO_S                      *pstChapInfo;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;
    PS_BOOL_ENUM_UINT8                  enIsCaveAlgorithmEnable;
    VOS_UINT32                          ulRandu;


    /* 停止定时器 */

    if (USIMM_CDMASPEC_COMPUTEIP != pstMsg->enAuthType)
    {
        PPPC_WARNING_LOG("enAuthType isn't USIMM_CDMASPEC_COMPUTEIP.\n");
        return;
    }

    if (USIMM_COMPUTEIP_HRPD != pstMsg->uAuthCnf.stComputeIPCnf.enComputeIPType)
    {
        PPPC_WARNING_LOG("enComputeIPType isn't USIMM_COMPUTEIP_CHAP.\n");
        return;
    }

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        /* 接入鉴权不需要从节点获取密码 */
        enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstMsg->stCmdResult.ulSendPara);
        if (PS_TRUE != enIsDoingAccessAuth)
        {
            pstActPppNode = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_GetActPppHeadNode();

            if (VOS_NULL_PTR == pstActPppNode)
            {
                PPPC_WARNING_LOG("pstActPppNode is NULL.\n");
                return;
            }

            pstPppInfo = &g_astPppPool[pstActPppNode->ucPppId];
        }
        else
        {
            pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];
        }

        pstChapInfo = pstPppInfo->pstChapInfo;
        if (VOS_NULL_PTR == pstChapInfo)
        {
            PPPC_WARNING_LOG("pstChapInfo is NULL.\n");
            return;
        }

        /*保存Response 及长度*/
        PS_MEM_CPY(pstChapInfo->szResponse, pstMsg->uAuthCnf.stComputeIPCnf.aucRspData,
            pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen);

        pstChapInfo->szResponse[pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen] = 0;
        pstChapInfo->ucRespLen = (VOS_UINT8)pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen;
        PPP_CHAP_SendResponse(pstPppInfo);
    }
    else
    {
        PPPC_WARNING_LOG1("The result of MD5 CHAP AUTH error. ErrorCode:%d.\n", pstMsg->stCmdResult.ulErrorCode);
        /* 在支持CAVE算法的情况下，使用MD5算法接入鉴权失败时，再使用CAVE算法鉴权 */
        enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstMsg->stCmdResult.ulSendPara);
        enIsCaveAlgorithmEnable = PPPC_IsCaveAlgorithmEnable();
        if ((PS_TRUE == enIsDoingAccessAuth) && (PS_TRUE == enIsCaveAlgorithmEnable))
        {
            ulRandu = PPPC_GetRunCaveRandu();
            PPPC_UIM_RunCaveAuthReq(ulRandu);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_UsimCaveAuthCnfProc
 功能描述  : 收到CAVE鉴权结果消息的处理
 输入参数  : USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UsimCaveAuthCnfProc(USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf)
{
    PS_BOOL_ENUM_UINT8                      enIsDoingAccessAuth;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstActPppNode = VOS_NULL_PTR;
    PPPINFO_S                              *pstPppInfo;
    PPPCHAPINFO_S                          *pstChapInfo;
    USIMM_RUNCAVE_AUTH_CNF_STRU            *pstUsimmRuncaveAuthCnf;


    /* 鉴权失败，不用给BS回复响应，BS超时处理 */
    if (USIMM_AUTH_CDMA_SUCCESS != pUsimAuthCnf->enResult)
    {
        PPPC_WARNING_LOG1("PPPC_UsimAuthenticationCnfProc: Auth fail", pUsimAuthCnf->enResult);
        return VOS_ERR;
    }

    /* 取AUTHU值 */
    pstUsimmRuncaveAuthCnf          = &(pUsimAuthCnf->uCnfData.stRunCaveCnf);

    /* 接入鉴权不需要从节点获取密码 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pUsimAuthCnf->stCmdResult.ulSendPara);
    if (PS_TRUE != enIsDoingAccessAuth)
    {
        pstActPppNode = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_GetActPppHeadNode();

        if (VOS_NULL_PTR == pstActPppNode)
        {
            PPPC_WARNING_LOG("pstActPppNode is NULL.\n");
            return VOS_ERR;
        }

        pstPppInfo = &g_astPppPool[pstActPppNode->ucPppId];
    }
    else
    {
        pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (VOS_NULL_PTR == pstChapInfo)
    {
        PPPC_WARNING_LOG("pstChapInfo is NULL.\n");
        return VOS_ERR;
    }

    /*保存Response 及长度*/
    PS_MEM_SET(pstChapInfo->szResponse, 0, sizeof(pstChapInfo->szResponse));
    pstChapInfo->szResponse[0] = pstUsimmRuncaveAuthCnf->aucAuthr[0];
    pstChapInfo->szResponse[1] = pstUsimmRuncaveAuthCnf->aucAuthr[1];
    pstChapInfo->szResponse[2] = pstUsimmRuncaveAuthCnf->aucAuthr[2];
    pstChapInfo->ucRespLen = CHAP_MAX_RESPONSE_LENGTH;
    PPP_CHAP_SendResponse(pstPppInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_UsimEapAuthCnfProc
 功能描述  : 收到EAP鉴权结果消息的处理
 输入参数  : USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UsimEapAuthCnfProc(USIMM_AUTHENTICATION_CNF_STRU  *pstUsimAuthCnf)
{
    PPPC_EAP_AUTH_RESULT_STRU           stAuthRes;
    USIMM_AUTH_RESULT_ENUM_UINT32       enResult;
    USIMM_TELECOM_AUTH_CNF_STRU        *pstTELECnf;
    const VOS_UINT8                     ucLen = 1;                              /* 卡计算结果中长度占的字节数 */

    enResult = pstUsimAuthCnf->enResult;
    switch ( enResult )
    {
        case USIMM_AUTH_UMTS_SUCCESS :
        case USIMM_AUTH_GSM_SUCCESS :
        case USIMM_AUTH_IMS_SUCCESS :
        case USIMM_AUTH_CDMA_SUCCESS :

            stAuthRes.enResult = PPPC_USIMM_AUTH_SUCCESS;
            break;

        case USIMM_AUTH_MAC_FAILURE :

            stAuthRes.enResult = PPPC_USIMM_AUTH_MAC_FAILURE;
            break;

        case USIMM_AUTH_SYNC_FAILURE :

            stAuthRes.enResult = PPPC_USIMM_AUTH_SYNC_FAILURE;
            break;

        default:

            stAuthRes.enResult = PPPC_USIMM_AUTH_OTHER_FAILURE;
            break;
    }

    pstTELECnf = &(pstUsimAuthCnf->uCnfData.stTELECnf);

    stAuthRes.ucAuthRseLen = pstTELECnf->aucAuthRes[0];

    PS_MEM_CPY(stAuthRes.aucAuthRes, pstTELECnf->aucAuthRes + ucLen , sizeof(stAuthRes.aucAuthRes));
    PS_MEM_CPY(stAuthRes.aucAuts, pstTELECnf->aucAuts + ucLen, sizeof(stAuthRes.aucAuts));
    PS_MEM_CPY(stAuthRes.aucCK, pstTELECnf->aucCK + ucLen, sizeof(stAuthRes.aucCK));
    PS_MEM_CPY(stAuthRes.aucIK, pstTELECnf->aucIK + ucLen, sizeof(stAuthRes.aucIK));

    stAuthRes.ucIdentifier = (VOS_UINT8)pstUsimAuthCnf->stCmdResult.ulSendPara;

    PPPC_EAP_AKA_ReciveAuthRes(&stAuthRes);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_UsimmAuthenticationCnfProc
 功能描述  : 收到鉴权结果消息的处理
 输入参数  : USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UsimmAuthenticationCnfProc(USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf)
{
    USIMM_AUTH_TYPE_ENUM_UINT32             enAuthType;
    VOS_UINT32                              ulRet;


    enAuthType = pUsimAuthCnf->enAuthType;

    switch (enAuthType)
    {
        case USIMM_RUNCAVE_AUTH:

            ulRet = PPPC_UsimCaveAuthCnfProc(pUsimAuthCnf);

            break;

        case USIMM_EAP_AUTH:
        case USIMM_3G_AUTH:

            ulRet = PPPC_UsimEapAuthCnfProc(pUsimAuthCnf);

            break;

        default:

            /* 其他类型，这里不用处理 */
            PPPC_WARNING_LOG1("PPPC_UsimAuthenticationCnfProc: enAuthType", pUsimAuthCnf->enAuthType);
            ulRet = VOS_ERR;

            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgTafProc
 功能描述  : PPPC模块处理TAF命令
 输入参数  : pMsg    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-04
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgTafProc(struct MsgCB * pMsg)
{
    Taf_aps_ppp_pif_MSG                    *pstApsPppPublicInfo;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    APS_PPP_ACT_REQ_STRU                   *pstPppActReq;
    APS_PPP_DEACT_REQ_STRU                 *pstPppDeActReq;
    APS_PPP_DEACT_IND_STRU                 *pstPppDeActInd;
    APS_PPP_MODE_CHANGE_NTF_STRU           *pstModeChangeNtf;
    APS_PPP_DIAL_MODE_NTF_STRU             *pstDialModeNtf;


    /* 前面已经保证pMsg非空 */

    pstApsPppPublicInfo         = (Taf_aps_ppp_pif_MSG *)pMsg;
    enMsgType                   = pstApsPppPublicInfo->stMsgData.enMsgId;

    /*如果是接收到从TE发送来的数据帧*/
    switch(enMsgType)
    {
        /* PPP激活去激活消息在同一个地方break */
        case ID_APS_PPP_ACT_REQ:

            pstPppActReq            = (APS_PPP_ACT_REQ_STRU *)pMsg;

            PPPC_TafActReqProc(pstPppActReq);

            break;

        case ID_APS_PPP_DEACT_REQ:

            pstPppDeActReq          = (APS_PPP_DEACT_REQ_STRU *)pMsg;

            PPPC_TafDeActReqProc(pstPppDeActReq);

            break;

        case ID_APS_PPP_DEACT_IND:

            pstPppDeActInd          = (APS_PPP_DEACT_IND_STRU *)pMsg;

            PPPC_TafDeActIndProc(pstPppDeActInd);

            break;

        case ID_APS_PPP_MODE_CHANGE_NTF:

            pstModeChangeNtf        = (APS_PPP_MODE_CHANGE_NTF_STRU *)pMsg;

            PPPC_TafModeChangeNtfProc(pstModeChangeNtf);

            break;

        case ID_APS_PPP_DIAL_MODE_NTF:

            pstDialModeNtf          = (APS_PPP_DIAL_MODE_NTF_STRU *)pMsg;

            PPPC_TafDialModeNtfProc(pstDialModeNtf);

            break;

        /* NAS通知的链路状态消息，不作处理 */
        case ID_APS_PPP_LINK_STATUS_NTF:

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Aps Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetDataLinkStatus
 功能描述  : 获取上下行链表的是否为空的状态
 输入参数  : 无
 输出参数  : penUlDataLinkNotNull    PS_FALSE:上行空 PS_TRUE:上行非空
             penDlDataLinkNotNull    PS_FALSE:下行空 PS_TRUE:下行非空
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-12-28
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_GetUlDlDataLinkStatus
(
    PS_BOOL_ENUM_UINT8                 *penUlDataLinkNotNull,
    PS_BOOL_ENUM_UINT8                 *penDlDataLinkNotNull
)
{
    TTF_LINK_ST                        *pstDlLink;
    TTF_LINK_ST                        *pstUlLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;


    /* 内部调用保证入参非空 */
    pstDlLink       = &g_stPppDlLink;
    pstUlLink       = &g_stPppUlLink;

    /* 判断上下行链表是否为空 */
    pstDlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstDlLink);
    pstUlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlLink);
    if (VOS_NULL_PTR != pstDlNode)
    {
        *penDlDataLinkNotNull = PS_TRUE;
    }

    if (VOS_NULL_PTR != pstUlNode)
    {
        *penUlDataLinkNotNull = PS_TRUE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_WakeSelf
 功能描述  : 当定时器为空且还有数据需要处理时PPPC唤醒自己
 输入参数  : penUlDataLinkNotNull    PS_FALSE:上行空 PS_TRUE:上行非空
             penDlDataLinkNotNull    PS_FALSE:下行空 PS_TRUE:下行非空
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-12-28
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_WakeSelf
(
    PS_BOOL_ENUM_UINT8                  enUlDataLinkNotNull,
    PS_BOOL_ENUM_UINT8                  enDlDataLinkNotNull
)
{
    /* 如果定时器非空已经有唤醒机制不需要唤醒自己 */
    if (VOS_NULL_PTR != g_hReachMaxProcTimer)
    {
        return;
    }

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    /* 如果硬件HDLC申请不到内存已经启动定时器则不需要自唤醒 */
    if (VOS_NULL_PTR != g_stHdlcConfigInfo.stHdlcFrmTimerHandle)
    {
        return;
    }
#endif

    if (PS_TRUE == enUlDataLinkNotNull)
    {
        PPPC_WARNING_LOG("PPPC Wakeself for ul link!");
        PPPC_SndUlDataNotify();
    }
    else if (PS_TRUE == enDlDataLinkNotNull)
    {
        PPPC_WARNING_LOG("PPPC Wakeself for dl link!");
        PPPC_SndDlDataNotify();
    }
    else
    {
        /* 编程规范 */
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_SendRpaAccessAuthPhaseInd
 功能描述  : PPPC通知PA接入鉴权开始
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月28日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HRPD_SendRpaAccessAuthPhaseInd(VOS_VOID)
{
    CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND_STRU    *pstPppAccessAuthPhase;
    PS_BOOL_ENUM_UINT8                              enIsDoingAccesAuth;

    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth(PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* 如果当前在做接入鉴权则说明已经通知过PA接入鉴权开始，不用再通知 */
    if (PS_TRUE == enIsDoingAccesAuth)
    {
        PPPC_WARNING_LOG("Send PA Access Auth Begin Error");
        return;
    }

    pstPppAccessAuthPhase = (CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND_STRU));
    if (VOS_NULL_PTR == pstPppAccessAuthPhase)
    {
        PPPC_ERROR_LOG("Alloc RPA Access Auth Phase Ind msg Memory Fail!\r\n");
        return;
    }

    pstPppAccessAuthPhase->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppAccessAuthPhase->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppAccessAuthPhase->enMsgId        = ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND;
    pstPppAccessAuthPhase->usOpId         = 0;

    /* 发送接入鉴权消息进入PPP阶段 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppAccessAuthPhase))
    {
        PPPC_WARNING_LOG("Send ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_SendRpaAccessAuthRsp
 功能描述  : PPPC通知PA接入鉴权结束
 输入参数  : enResult       接入鉴权结果
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月28日
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendRpaAccessAuthRsp
(
    CTTF_HRPD_PPP_ACCESS_AUTH_RESULT_ENUM_UINT8 enResult
)
{
    CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP_STRU  *pstPppAccessAuthRsp;
    PS_BOOL_ENUM_UINT8                      enIsDoingAccesAuth;

    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth(PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* 如果当前没有在做接入鉴权则不通知PA接入鉴权结束 */
    if (PS_FALSE == enIsDoingAccesAuth)
    {
        PPPC_WARNING_LOG1("Send PA Access Auth Rsp Error", enResult);
        return;
    }

    /* 初始接入鉴权标志清除 */
    PPPC_SetInitAccessAuthMode(PS_FALSE);

    pstPppAccessAuthRsp = (CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP_STRU));
    if (VOS_NULL_PTR == pstPppAccessAuthRsp)
    {
        PPPC_ERROR_LOG("Alloc Access Auth Rsp Ind Mem Fail!\r\n");
        return;
    }

    pstPppAccessAuthRsp->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppAccessAuthRsp->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppAccessAuthRsp->enMsgId        = ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP;
    pstPppAccessAuthRsp->usOpId         = 0;
    pstPppAccessAuthRsp->enResult       = enResult;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppAccessAuthRsp))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_AccessAuthProc
 功能描述  : PPPC模块收到CTTF_PID_HRPD_RPA任务发来消息的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-12-11
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_AccessAuthProc(struct MsgCB * pMsg)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode;


    if (VOS_NULL_PTR != g_hAADelayTimer)
    {
        (VOS_VOID)VOS_StopRelTimer((HTIMER*)&g_hAADelayTimer);
    }

    (VOS_VOID)VOS_StartRelTimer((HTIMER*)&(g_hAADelayTimer), MID_PPPC, PPPC_AA_DELAY_TIMER_LEN,
        0, PPPC_ACCESS_AUTH_DELAY_PROC_TIMER, VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

    /* 设置初始接入鉴权标志位 */
    PPPC_SetInitAccessAuthMode(PS_TRUE);

    enRateMode  = PPPC_GetRatMode();
    if ((PPPC_RAT_MODE_HRPD != enRateMode) && (PPPC_RAT_MODE_EHRPD != enRateMode))
    {
        /* 需要接入鉴权,只能是HRPD或eHRPD模式,此时PA没有通知,设置为HRPD模式处理 */
        PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_AccessAuthFinsh
 功能描述  : PPPC收到PA发送的ACCESS AUTH Finsh处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-28
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_AccessAuthFinsh(VOS_VOID)
{
    PPPINFO_S                          *pstPppInfo;

    pstPppInfo = &(g_astPppPool[0]);
    PPP_CHAP_ReceiveSuccess(pstPppInfo);

    /* 此时已经不能再发协商报文了，需要DOWN掉 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, PPP_EVENT_LCPDOWN, NULL);
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_UpdateConnectionStatus
 功能描述  : 更新connection的状态
 输入参数  : pMsg       PA发给PPP的链路状态消息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-28
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_UpdateConnectionStatus(struct MsgCB * pMsg)
{
    CTTF_HRPD_PA_PPP_CONNECTION_STATUS_IND_STRU    *pstConnectionStatus;
    CTTF_HRPD_PA_CONNECTION_STATUS_ENUM_UINT8       enStatus;

    pstConnectionStatus = (CTTF_HRPD_PA_PPP_CONNECTION_STATUS_IND_STRU *)pMsg;
    enStatus            = pstConnectionStatus->enStatus;

    if (CTTF_HRPD_PA_CONNECTION_STATUS_ENUM_BUTT > enStatus)
    {
        g_stPppContext.stHrpdContext.enConnectionStatus = enStatus;
    }
    else
    {
        PPPC_WARNING_LOG1("Error Connection Status", enStatus);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgHrpdRpaProc
 功能描述  : PPPC模块收到CTTF_PID_HRPD_RPA任务发来消息的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-03
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_MsgRpaProc(struct MsgCB * pMsg)
{
    CTTF_HRPD_PA_PPP_PIF_MSG_TYPE_ENUM_UINT16     enMsgType;


    enMsgType   = *(CTTF_HRPD_PA_PPP_PIF_MSG_TYPE_ENUM_UINT16 *)(pMsg->aucValue);

    switch (enMsgType)
    {
        case ID_CTTF_PPP_HRPD_COMMITTED_IND:

            PPPC_HRPD_RcvCommittedIndProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_RESERVATIONS_IND:

            PPPC_HRPD_RcvReservationsIndProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_OPEN_RESERVATION_IND:

            PPPC_HrpdPaAgentRcvOpenReservProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_CLOSE_RESERVATIONS_IND:

            PPPC_HrpdPaAgentRcvCloseReservProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_RESERVATION_DL_MSG:

            PPPC_HRPD_PaAgentRcvReservDlMsgProc(pMsg);

            break;

        case ID_CTTF_HRPD_PA_PPP_ACCESS_AUTH_IND:

            PPPC_HRPD_AccessAuthProc(pMsg);

            break;
        case ID_CTTF_HRPD_PA_PPP_ACCESS_FINISH_IND:

            PPPC_HRPD_AccessAuthFinsh();

            break;
        case ID_CTTF_HRPD_PA_PPP_CONNECTION_STATUS_IND:

            PPPC_HRPD_UpdateConnectionStatus(pMsg);

            break;
        default:

            PPPC_WARNING_LOG1("Rcv invalid PA message!\r\n", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgUsimmProc
 功能描述  : PPPC模块收到WUEPS_PID_USIM任务发来消息的处理
 输入参数  : PPPC_UIM_MSG_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-29
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgUsimmProc(PPPC_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case USIMM_CDMASPECAUTH_CNF:
            PPPC_UsimmCdmaSpecAuthProc((USIMM_CDMASPECAUTH_CNF_STRU *)pstMsg);
            break;

        /* 鉴权响应 */
        case USIMM_AUTHENTICATION_CNF:
            PPPC_UsimmAuthenticationCnfProc((USIMM_AUTHENTICATION_CNF_STRU *)pstMsg);
            break;

        /* 读取文件请求CNF */
        case USIMM_READFILE_CNF:
            PPPC_UsimmReadFileCnfProc((USIMM_READFILE_CNF_STRU *)pstMsg);
            break;

        default:

            PPPC_WARNING_LOG1("Invalid Usim msg", pstMsg->ulMsgName);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgPihProc
 功能描述  : PPPC模块收到MAPS_PIH_PID任务发来消息的处理
 输入参数  : PPPC_UIM_MSG_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-08-13
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgPihProc(PPPC_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case USIMM_CARDSTATUS_IND:
            PPPC_PihUsimStatusIndProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_Init
 功能描述  : PPPC模块初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-10-30
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_Init(enum VOS_INIT_PHASE_DEFINE enPhase )
{
    TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU   stNvCfgOptions;
    VOS_UINT32                          ulDefaultTimerLen = 86400;           /* MAX PPP Inactive Timer默认时长24小时 */

    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:

        /* 初始化固定数据集合 */
        PPPC_InitFixedData();

        /* 初始化OM可维可测信息*/
        PPP_MNTN_CMO_Init();

        /* 初始化PPP上下文 */
        PS_MEM_SET(&g_stPppContext, 0, sizeof(g_stPppContext));

        if (NV_OK != NV_Read(en_NV_Item_TTF_PPPC_CONFIG_OPTIONS, &stNvCfgOptions, sizeof(TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU)))
        {
            g_stPppContext.usMru                = PPPC_MAX_FRAME_LEN;
            g_stPppContext.enCaveEnable         = PS_FALSE;
            g_stPppContext.stHrpdContext.ulPppInactTimerLen = ulDefaultTimerLen;
        }
        else
        {
            g_stPppContext.usMru                = stNvCfgOptions.usMru;
            g_stPppContext.enCaveEnable         = (stNvCfgOptions.ucCaveEnable > 0) ? PS_TRUE : PS_FALSE;
            g_stPppContext.stHrpdContext.ulPppInactTimerLen = stNvCfgOptions.ulPppInactTimerLen;
            if ((g_stPppContext.usMru < PPPC_MIN_FRAME_LEN)
                || (g_stPppContext.usMru > PPPC_MAX_FRAME_LEN))
            {
                g_stPppContext.usMru = PPPC_MAX_FRAME_LEN;
            }

            /* 大于0才是有效值，否则设为默认值24小时 */
            if (g_stPppContext.stHrpdContext.ulPppInactTimerLen > 0)
            {
                g_stPppContext.stHrpdContext.ulPppInactTimerLen = ulDefaultTimerLen;
            }

        }

        PPP_TaskInit();
        PPP_TaskEntry();

        /* 初始化上下行队列 */
        PPPC_QueueInit();

        /* 初始化APS消息链表 */
        PPPC_ApsCmdLinkInit();

        /* 初始化PA AGENT上下文 */
        PPPC_HRPD_PaAgentInit();

        /* 初始化上行数据内存 */
        PS_MEM_SET(&g_astUlEncapMem[0], 0, sizeof(g_astUlEncapMem));

        /* 初始化初始接入鉴权时收到NAS的激活请求时延时处理的定时器 */
        PS_MEM_SET(&g_astActHrpdTimer[0], 0, sizeof(g_astActHrpdTimer));

        /* 初始化接入鉴权connection状态 */
        g_stPppContext.stHrpdContext.enConnectionStatus = CTTF_HRPD_PA_CONNECTION_NOT_EXIST_ENUM;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        /* 初始化HDLC */
        if (VOS_OK != PPP_HDLC_HARD_Init())
        {
            return VOS_ERR;
        }

#endif

        /* 注册到PIH，准备接收卡状态消息 */
        PIH_RegUsimCardStatusIndMsg(MSPS_PID_PPPC);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        /* 注册到PIH，准备接收卡1状态消息 */
        I1_PIH_RegUsimCardStatusIndMsg(MSPS_PID_PPPC);
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
            vos_printf("1X RMAC, ERROR, INIT_PHASE = %d \r", enPhase);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgProc
 功能描述  : PPP模块中的消息处理函数，他处理定时器消息以及从AT模块接
             收到的命令。如果成功将返回VOS_OK，否则为VOS_ERR。
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-10-30
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgProc(struct MsgCB * pMsg)
{
    if(VOS_NULL_PTR == pMsg)
    {
        PPPC_WARNING_LOG("PPPC_MsgProc pMsg is NULL!\r\n");
        return;
    }

#if defined (CTTF_PC_ST_SWITCH)
    CTTF_HookMsg(pMsg);
#endif

    switch (pMsg->ulSenderPid)
    {
        /*如果是定时器发来的消息*/
        case VOS_PID_TIMER:

            PPPC_MsgTimerProc((VOS_VOID *)pMsg);

            break;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:

            PPPC_MsgTafProc((VOS_VOID *)pMsg);

            break;

        case UEPS_PID_EHSM:

            PPPC_MsgEhsmProc((VOS_VOID *)pMsg);

            break;

        case CTTF_PID_HRPD_RPA:

            PPPC_HRPD_MsgRpaProc((VOS_VOID *)pMsg);

            break;

        case WUEPS_PID_USIM:
        case I1_WUEPS_PID_USIM:

            PPPC_MsgUsimmProc((PPPC_UIM_MSG_STRU *)pMsg);

            break;

        case MAPS_PIH_PID:
        case I1_MAPS_PIH_PID:

            PPPC_MsgPihProc((PPPC_UIM_MSG_STRU *)pMsg);

            break;

        case MSP_PID_DIAG_APP_AGENT:
        case MSP_PID_DIAG_AGENT:

            PPP_MNTN_CMO_MsgProc(pMsg);

            break;

        default:

            PPPC_WARNING_LOG1("PPPC_MsgProc Sender Pid is Invalid!\r\n", pMsg->ulSenderPid);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsActFail
 功能描述  : PPP回复APS Act失败
 输入参数  : pstPppActReq   APS_PPP_ACT_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsActFail
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;


    if (VOS_NULL_PTR == pstPppActReq)
    {
        return;
    }
    /* 申请响应消息内存 */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_ERROR_LOG("Alloc Ppp Act Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsActCnf->ulReceiverPid         = pstPppActReq->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pstPppActReq->usOpId;
    pstApsActCnf->ulResult              = VOS_ERR;
    pstApsActCnf->ucPdnId               = pstPppActReq->ucPdnId;
    pstApsActCnf->enPdnType             = pstPppActReq->enPdnType;

    g_ucLcpTermMask = PS_FALSE;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_PPP_APS_ACT_CNF!!!\n");

    /* OM可维可测信息:失败次数加1 */
    g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
    PPP_MNTN_CalcOtherFailCnt();
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsDeActFail
 功能描述  : PPP回复APS DeAct失败
 输入参数  : pstPppDeActReq   APS_PPP_DEACT_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsDeActFail
(
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;


    /* 申请响应消息内存 */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_ERROR_LOG("Alloc Ppp DeAct Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDeActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDeActCnf->ulReceiverPid         = pstPppDeActReq->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId               = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId                = pstPppDeActReq->usOpId;
    pstApsDeActCnf->ulResult              = VOS_ERR;
    pstApsDeActCnf->ucPdnId               = pstPppDeActReq->ucPdnId;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_PPP_APS_DEACT_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsActCmd
 功能描述  : PPP回复APS激活PPP命令
 输入参数  : pPppInfo       PPP信息，激活失败时填VOS_NULL_PTR,否则非空
             ulResult       VOS_OK/VOS_ERR
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-05
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsActCmd(VOS_VOID* pPppInfo, VOS_UINT32 ulResult, TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType)
{
    PPPINFO_S                          *pstPppInfo;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enUsedPdnType = enPdnType;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_WARNING_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    if (VOS_OK != ulResult)
    {
        PPPC_DeletePppId(pstApsMsgNode->ucPppId);
        enUsedPdnType = pstApsMsgNode->stApsCmdNode.enPdnType;

        g_ucLcpTermMask = PS_FALSE;

        /* OM可维可测信息:失败次数加1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;

        PPP_MNTN_CalcOtherFailCnt();
    }
    else
    {
        /* OM可维可测信息:成功次数加1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulSuccCnt++;
    }

    /* OM维测上报 */
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    /* 申请响应消息内存 */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsActCnf->ulReceiverPid         = pstApsMsgNode->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pstApsMsgNode->usOpId;
    pstApsActCnf->ulResult              = ulResult;
    pstApsActCnf->ucPdnId               = pstApsMsgNode->ucPdnId;
    pstApsActCnf->enPdnType             = enUsedPdnType;

    pstApsActCnf->usMtu                 = PPPC_MAX_FRAME_LEN;

    if (VOS_NULL_PTR != pPppInfo)
    {
        /* 非空说明应该是激活成功，需要把DNS和IP地址填入 */
        pstPppInfo                                = (PPPINFO_S *)pPppInfo;
        pstLcpInfo                                = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
        pstIpcpInfo                               = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
        pstIpv6cpInfo                             = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

        if ((VOS_NULL_PTR != pstLcpInfo)
             && (1 == pstLcpInfo->stHisOptions.neg_mru))
        {
            pstApsActCnf->usMtu                   = pstLcpInfo->stHisOptions.mru;
        }

        if (VOS_NULL_PTR != pstIpcpInfo)
        {
            pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
            pstApsActCnf->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
            pstApsActCnf->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
            PS_MEM_CPY(pstApsActCnf->aucIpv4Addr, &(pstIpcpOption->ouraddr),
                sizeof(pstApsActCnf->aucIpv4Addr));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS));
        }

        if (VOS_NULL_PTR != pstIpv6cpInfo)
        {
            pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);
            PS_MEM_CPY(pstApsActCnf->aucIpv6Addr + TAF_APS_PPP_IPV6_ADDR_LEN/2,
                pstIpv6cpOption->OurV6InId, TAF_APS_PPP_IPV6_ADDR_LEN/2);
        }
    }

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstApsPppCmdLink);

    PPP_Free(pstApsMsgNode);

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsDeActCmd
 功能描述  : 不需要协商直接回复去激活消息
 输入参数  : ulResult   去激活结果
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-10-10
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsDeActDirect
(
    VOS_UINT32                          ulResult,
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;


    /* 申请响应消息内存 */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp DeAct Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDeActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDeActCnf->ulReceiverPid       = pstPppDeActReq->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId             = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId              = pstPppDeActReq->usOpId;
    pstApsDeActCnf->ulResult            = ulResult;
    pstApsDeActCnf->ucPdnId             = pstPppDeActReq->ucPdnId;

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsDeActCmd
 功能描述  : 回复去激活消息
 输入参数  : ulResult   去激活结果
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-05
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsDeActCmd(VOS_UINT32 ulResult)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_WARNING_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    PPPC_DeletePppId(pstApsMsgNode->ucPppId);

    /* 申请响应消息内存 */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp DeAct Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDeActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDeActCnf->ulReceiverPid       = pstApsMsgNode->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId             = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId              = pstApsMsgNode->usOpId;
    pstApsDeActCnf->ulResult            = ulResult;
    pstApsDeActCnf->ucPdnId             = pstApsMsgNode->ucPdnId;

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstApsPppCmdLink);

    PPP_Free(pstApsMsgNode);

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_IsNegoComplete
 功能描述  : 判断IPV4V6协商是否完成了
 输入参数  : pstPppInfo
 输出参数  : penUsedPdnType         PPP实际使用的地址类型
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-08-31
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_IsNegoComplete
(
    VOS_VOID                           *pPppInfo,
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enPdnType,
    VOS_UINT32                          ulSenderPid,
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    *penUsedPdnType
)
{
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT32                          ulRet = VOS_ERR ;


    pstPppInfo  = (PPPINFO_S*)pPppInfo;

    switch(enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            if (pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
                *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV4;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            if (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
                *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV6;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            /* 只有eHRPD才需要支持协商IPV6 */
            if (UEPS_PID_EHSM == ulSenderPid)
            {
                if ((pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
                    && (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS))
                {
                    ulRet = VOS_OK;
                    *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV4V6;
                }
            }
            else
            {
                /* 1X和HRPD只会协商IPV4,此时需要向NAS返回实际使用的地址类型IPV4 */
                if (pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
                {
                    ulRet = VOS_OK;
                    *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV4;
                }
            }
            break;
        default:

            PPPC_WARNING_LOG2("Pdntype and sender pid value", enPdnType, ulSenderPid);
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsModifyIndCmd
 功能描述  : 回复APS IP地址修改消息
 输入参数  : pstPppInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-08-31
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsModifyIndCmd(PPPINFO_S* pstPppInfo)
{
    PPP_APS_MODIFY_IND_STRU            *pstApsModifyInd;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    VOS_UINT8                           ucPdnId = 0;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enUsedPdnType = TAF_APS_PPP_ADDR_TYPE_BUTT;
    VOS_UINT32                          ulRet;


    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is null!\r\n");
        return;
    }

    ulRet = PPPC_IsNegoComplete((VOS_VOID *)pstPppInfo,
            g_stPppContext.enPdnType, g_stPppContext.ulSendPid, &enUsedPdnType);

    if (VOS_OK != ulRet)
    {
        return;
    }

    if (VOS_OK != PPPC_1X_GetPdnId((VOS_UINT8)pstPppInfo->ulRPIndex, &ucPdnId))
    {
        PPPC_WARNING_LOG1("Get Pdn Id failed, ucPppId:[%d]\n", pstPppInfo->ulRPIndex);
        return;
    }

    /* 申请响应消息内存 */
    pstApsModifyInd    = (PPP_APS_MODIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstApsModifyInd)
    {
        PPPC_WARNING_LOG("Alloc Ppp Modify Ind Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsModifyInd + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsModifyInd->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstApsModifyInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsModifyInd->enMsgId             = ID_PPP_APS_MODIFY_IND;
    pstApsModifyInd->usOpId              = 0;
    pstApsModifyInd->ucPdnId             = ucPdnId;
    pstApsModifyInd->enPdnType           = enUsedPdnType;

    pstLcpInfo                           = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
    pstIpcpInfo                          = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstIpv6cpInfo                        = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

    if (VOS_NULL_PTR != pstLcpInfo)
    {
        pstApsModifyInd->usMtu           = pstLcpInfo->stHisOptions.mru;
    }
    else
    {
        pstApsModifyInd->usMtu           = PPPC_MAX_FRAME_LEN;
    }

    if (VOS_NULL_PTR != pstIpcpInfo)
    {
        pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
        pstApsModifyInd->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
        pstApsModifyInd->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
        PS_MEM_CPY(pstApsModifyInd->aucIpv4Addr, &(pstIpcpOption->ouraddr),
            sizeof(pstApsModifyInd->aucIpv4Addr));
        PS_MEM_CPY(pstApsModifyInd->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
            sizeof(pstApsModifyInd->stIpv4Dns.aucIpv4PrimDNS));
        PS_MEM_CPY(pstApsModifyInd->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
            sizeof(pstApsModifyInd->stIpv4Dns.aucIpv4SecDNS));
    }

    if (VOS_NULL_PTR != pstIpv6cpInfo)
    {
        pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);
        PS_MEM_CPY(pstApsModifyInd->aucIpv6Addr + TAF_APS_PPP_IPV6_ADDR_LEN/2,
            pstIpv6cpOption->OurV6InId, TAF_APS_PPP_IPV6_ADDR_LEN/2);
    }

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsModifyInd))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_MODIFY_IND msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_IsReadyToRespActCmd
 功能描述  : 网络协商完成后，根据PDNType来判断是否通知APS
 输入参数  : pPppInfo       PPP信息，激活失败时填VOS_NULL_PTR,否则非空
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_IsReadyToRespActCmd(VOS_VOID* pPppInfo)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    VOS_UINT32                          ulRet = VOS_ERR;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enUsedPdnType = TAF_APS_PPP_ADDR_TYPE_BUTT;


    if (VOS_NULL_PTR == pPppInfo)
    {
        return;
    }

    pstPppInfo        = (PPPINFO_S *)pPppInfo;

    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_RespApsModifyIndCmd(pstPppInfo);
        return;
    }

    ulRet = PPPC_IsNegoComplete(pPppInfo,
            pstApsMsgNode->stApsCmdNode.enPdnType, pstApsMsgNode->ulSenderPid, &enUsedPdnType);

    if (VOS_OK == ulRet)
    {
        g_stPppContext.enPdnType = pstApsMsgNode->stApsCmdNode.enPdnType;
        PPPC_RespApsActCmd(pPppInfo, VOS_OK, enUsedPdnType);
    }

}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmAttachFail
 功能描述  : PPP回复Ehsm Attach失败
 输入参数  : pstAttachReq   CNAS_CTTF_EHRPD_ATTACH_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmAttachFail
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pstAttachCnf;


    if (VOS_NULL_PTR == pstAttachReq)
    {
        return;
    }

    /* 申请响应消息内存 */
    pstAttachCnf    = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnf)
    {
        PPPC_ERROR_LOG("Alloc Ehsm Attach Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAttachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstAttachCnf->ulReceiverPid         = pstAttachReq->ulSenderPid;
    pstAttachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstAttachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_ATTACH_CNF;
    pstAttachCnf->usOpId                = pstAttachReq->usOpId;
    pstAttachCnf->ucPdnId               = pstAttachReq->ucPdnId;
    pstAttachCnf->enAttachRslt          = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    pstAttachCnf->enErrorCode           = CNAS_CTTF_EHRPD_ERROR_CODE_PARA_ERROR;
    pstAttachCnf->enAttachType          = pstAttachReq->enAttachType;
    pstAttachCnf->enPdnType             = pstAttachReq->enPdnType;

    if (CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL == pstAttachCnf->enAttachType)
    {
        g_ucLcpTermMask = PS_FALSE;
    }

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstAttachCnf))
    {
        PPPC_WARNING_LOG("Error:Send ID_CTTF_CNAS_EHRPD_ATTACH_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_ATTACH_CNF!!!\n");

    /* OM可维可测信息:失败次数加1 */
    g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
    PPP_MNTN_CalcOtherFailCnt();
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmDetach
 功能描述  : PPP回复Ehsm Detach失败
 输入参数  : enResult       回复成功或失败
             pstDetachReq   CNAS_CTTF_EHRPD_DETACH_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmDetach
(
    CNAS_CTTF_EHRPD_RSLT_ENUM_UINT8     enResult,
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstDetachReq
)
{
    CTTF_CNAS_EHRPD_DETACH_CNF_STRU    *pstDetachCnf;


    /* 申请响应消息内存 */
    pstDetachCnf    = (CTTF_CNAS_EHRPD_DETACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU));
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        PPPC_ERROR_LOG("Alloc Ehsm Detach Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDetachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstDetachCnf->ulReceiverPid         = pstDetachReq->ulSenderPid;
    pstDetachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstDetachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_DETACH_CNF;
    pstDetachCnf->usOpId                = pstDetachReq->usOpId;
    pstDetachCnf->enDetachRslt          = enResult;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachCnf))
    {
        PPPC_WARNING_LOG("Error:Send ID_CTTF_CNAS_EHRPD_DETACH_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_DETACH_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnConnectFail
 功能描述  : PPP回复PDN Connect失败
 输入参数  : pstPdnConnectReq   CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnConnectFail
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnConnectCnf;


    if (VOS_NULL_PTR == pstPdnConnectReq)
    {
        return;
    }

    /* 申请响应消息内存 */
    pstPdnConnectCnf = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnConnectCnf)
    {
        PPPC_WARNING_LOG("Alloc PDN Connect Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnConnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnConnectCnf->ulReceiverPid         = pstPdnConnectReq->ulSenderPid;
    pstPdnConnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnConnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF;
    pstPdnConnectCnf->usOpId                = pstPdnConnectReq->usOpId;
    pstPdnConnectCnf->enPdnConnRslt         = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    pstPdnConnectCnf->ucPdnId               = pstPdnConnectReq->ucPdnId;
    pstPdnConnectCnf->enErrorCode           = CNAS_CTTF_EHRPD_ERROR_CODE_PARA_ERROR;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnConnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF!!!\n");

    /* OM可维可测信息:失败次数加1 */
    g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
    PPP_MNTN_CalcOtherFailCnt();
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnDisconnect
 功能描述  : PPP回复Ehsm PDN Disconnect失败
 输入参数  : pstPdnDisconnectReq   CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnDisconnect
(
    CNAS_CTTF_EHRPD_RSLT_ENUM_UINT8     enResult,
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
)
{
    CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU  *pstPdnDisconnectCnf;


    /* 申请响应消息内存 */
    pstPdnDisconnectCnf  = (CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnDisconnectCnf)
    {
        PPPC_WARNING_LOG("Alloc PDN Disconnect Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnDisconnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnDisconnectCnf->ulReceiverPid         = pstPdnDisconnectReq->ulSenderPid;
    pstPdnDisconnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnDisconnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF;
    pstPdnDisconnectCnf->usOpId                = pstPdnDisconnectReq->usOpId;
    pstPdnDisconnectCnf->enDiscRslt            = enResult;
    pstPdnDisconnectCnf->ucPdnId               = pstPdnDisconnectReq->ucPdnId;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDisconnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmAttachCmd
 功能描述  : PPP回复Ehsm激活PPP命令
 输入参数  : pIpcpInfo      IPCP信息，激活失败时填VOS_NULL_PTR,否则非空
             ulResult       VOS_OK/VOS_ERR
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmAttachCmd(VOS_VOID* pVsncpInfo, VOS_UINT32 ulResult)
{
    PPPINFO_S                          *pstPppInfo;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPVSNCPINFO_S                     *pstVsncpInfo;
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pstAttachCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstEhsmMsgNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstEhsmMsgNode->ucPdnId);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);
        return;
    }

    /* 申请响应消息内存 */
    pstAttachCnf    = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnf)
    {
        PPPC_WARNING_LOG1("Alloc Attach Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAttachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstAttachCnf->ulReceiverPid         = pstEhsmMsgNode->ulSenderPid;
    pstAttachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstAttachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_ATTACH_CNF;
    pstAttachCnf->usOpId                = pstEhsmMsgNode->usOpId;
    pstAttachCnf->ucPdnId               = pstEhsmMsgNode->ucPdnId;

    if (VOS_OK == ulResult)
    {
        pstAttachCnf->enAttachRslt      = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
        pstAttachCnf->enErrorCode       = CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_BUTT;

        /* OM可维可测信息:成功次数加1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulSuccCnt++;
    }
    else
    {
        pstAttachCnf->enAttachRslt      = CNAS_CTTF_EHRPD_RSLT_FAILURE;
        pstAttachCnf->enErrorCode       = pstPDNContext->stEhrpd.enErrorCode;

        PPPC_ClearMappingByPppId(pstEhsmMsgNode->ucPppId);
        PPPC_DeletePppId(pstEhsmMsgNode->ucPppId);

         if (CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL == pstAttachCnf->enAttachType)
        {
            g_ucLcpTermMask = PS_FALSE;
        }

        /* OM可维可测信息:失败次数加1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
        PPP_MNTN_CalcOtherFailCnt();
    }

    /* OM维测上报 */
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    pstAttachCnf->enAttachType          = pstEhsmMsgNode->stEhsmCmdNode.enAttachType;
    pstAttachCnf->enPdnType             = pstEhsmMsgNode->stEhsmCmdNode.enPdnType;
    pstAttachCnf->ucAddressAllocCause   = pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause;
    pstAttachCnf->usMtu                 = PPP_GetDefaultMru();

    if (VOS_NULL_PTR != pVsncpInfo)
    {
        pstVsncpInfo                    = (PPPVSNCPINFO_S *)pVsncpInfo;
        pstPppInfo                      = (PPPINFO_S *)(pstVsncpInfo->pstPppInfo);

        if (VOS_NULL_PTR != pstPppInfo)
        {
            pstLcpInfo                  = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;

            if ((VOS_NULL_PTR != pstLcpInfo)
                 && (1 == pstLcpInfo->stHisOptions.neg_mru))
            {
                pstAttachCnf->usMtu     = pstLcpInfo->stHisOptions.mru;
            }
        }
    }

    /* 拷贝APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstAttachCnf->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstAttachCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_ATTACH_CNF msg fail!");
    }
    else
    {
        if (VOS_OK == ulResult)
        {
            /* 此时可以收发数据，通知PA open stream */
            PPPC_HRPD_SendOpenStreamReq();
        }
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmDetachCmd
 功能描述  : 回复去激活消息
 输入参数  : ulResult   去激活结果
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmDetachCmd(VOS_UINT32 ulResult)
{
    CTTF_CNAS_EHRPD_DETACH_CNF_STRU    *pstDetachCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (VOS_OK == ulResult)
    {
        /* 此时没有PDN连接不能收发数据，通知PA close stream */
        PPPC_HRPD_SendCloseStreamReq();
    }

    PPPC_DeletePppId(pstEhsmMsgNode->ucPppId);

    /* 申请响应消息内存 */
    pstDetachCnf    = (CTTF_CNAS_EHRPD_DETACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU));
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        PPPC_WARNING_LOG1("Alloc PPP Detach Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDetachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstDetachCnf->ulReceiverPid       = pstEhsmMsgNode->ulSenderPid;
    pstDetachCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDetachCnf->enMsgId             = ID_CTTF_CNAS_EHRPD_DETACH_CNF;
    pstDetachCnf->usOpId              = pstEhsmMsgNode->usOpId;

    if (VOS_OK == ulResult)
    {
        pstDetachCnf->enDetachRslt    = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
    }
    else
    {
        pstDetachCnf->enDetachRslt    = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    }

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_DETACH_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    /* 回复NAS Detach则不需要发送detach_ind */
    g_ucLcpTermMask = PS_FALSE;

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendPdnConnectCnf
 功能描述  : 发送PDN Connect Cnf消息
 输入参数  : pstMsgLinkNode      节点信息
             ulResult            VOS_OK/VOS_ERR
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-13
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendPdnConnectCnf
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstMsgLinkNode,
    VOS_UINT32                          ulResult
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnConnectCnf;
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    ulRet = PPP_GetPDNContextByPDNID(pstMsgLinkNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstMsgLinkNode->ucPdnId);

        return;
    }

    /* 申请响应消息内存 */
    pstPdnConnectCnf    = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnConnectCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnConnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnConnectCnf->ulReceiverPid         = pstMsgLinkNode->ulSenderPid;
    pstPdnConnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnConnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF;
    pstPdnConnectCnf->usOpId                = pstMsgLinkNode->usOpId;

    if (VOS_OK == ulResult)
    {
        pstPdnConnectCnf->enPdnConnRslt     = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
        pstPdnConnectCnf->enErrorCode       = CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_BUTT;

        /* OM可维可测信息:成功次数加1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulSuccCnt++;
    }
    else
    {
        pstPdnConnectCnf->enPdnConnRslt     = CNAS_CTTF_EHRPD_RSLT_FAILURE;
        pstPdnConnectCnf->enErrorCode       = pstPDNContext->stEhrpd.enErrorCode;

        PPPC_ClearMappingByPdnId(pstMsgLinkNode->ucPdnId);

        /* OM可维可测信息:失败次数加1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;

        PPP_MNTN_CalcOtherFailCnt();
    }

    /* OM维测上报 */
    PPP_MNTN_CMO_SendOmResourceStateInfo();


    pstPdnConnectCnf->ucPdnId               = pstMsgLinkNode->ucPdnId;
    pstPdnConnectCnf->enAttachType          = pstPDNContext->stEhrpd.enAttachType;
    pstPdnConnectCnf->enPdnType             = pstPDNContext->stEhrpd.enPdnType;
    pstPdnConnectCnf->ucAddressAllocCause   = pstPDNContext->stEhrpd.ucAddressAllocCause;

    /* 拷贝APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstPdnConnectCnf->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnConnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnConnectCmd
 功能描述  : PPP回复Ehsm PDN Connect Request消息
 输入参数  : pIpcpInfo      IPCP信息，激活失败时填VOS_NULL_PTR,否则非空
             ulResult       VOS_OK/VOS_ERR
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnConnectCmd
(
    VOS_VOID                           *pVsncpInfo,
    VOS_UINT32                          ulResult
)
{
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (ID_CNAS_CTTF_EHRPD_ATTACH_REQ == pstEhsmMsgNode->stEhsmCmdNode.enMsgType)
    {
        PPPC_RespEhsmAttachCmd(pVsncpInfo, ulResult);
        return;
    }
#if 0
    if (VOS_OK == PPPC_IsPdnIdUnique(pstEhsmMsgNode->ucPdnId))
    {
        PPPC_INFO_LOG("The PDN Id is unique!\r\n");
        PPPC_RespEhsmAttachCmd(pVsncpInfo, ulResult);
        return;
    }
#endif
    if (ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ != pstEhsmMsgNode->stEhsmCmdNode.enMsgType)
    {
        PPPC_WARNING_LOG("No PDNConnReq!\r\n");
        return;
    }

    /* 发送PDN Connect Cnf消息 */
    PPPC_SendPdnConnectCnf(pstEhsmMsgNode, ulResult);

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    if (VOS_OK == ulResult)
    {
        /* 此时可以收发数据，通知PA open stream */
        PPPC_HRPD_SendOpenStreamReq();
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnDisconnectCmd
 功能描述  : 回复Ehsm PDN Disconnect Request消息
 输入参数  : ulResult   PDN Disconnect结果
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnDisconnectCmd(VOS_UINT32 ulResult)
{
    CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU  *pstPdnDisconnectCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ != pstEhsmMsgNode->stEhsmCmdNode.enMsgType)
    {
        PPPC_WARNING_LOG("No PDNDisConnReq!\r\n");
        return;
    }

    PPPC_ClearMappingByPdnId(pstEhsmMsgNode->ucPdnId);

    /* 申请响应消息内存 */
    pstPdnDisconnectCnf    = (CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnDisconnectCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Disconnect Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnDisconnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnDisconnectCnf->ulReceiverPid       = pstEhsmMsgNode->ulSenderPid;
    pstPdnDisconnectCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPdnDisconnectCnf->enMsgId             = ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF;
    pstPdnDisconnectCnf->usOpId              = pstEhsmMsgNode->usOpId;
    pstPdnDisconnectCnf->ucPdnId             = pstEhsmMsgNode->ucPdnId;

    if (VOS_OK == ulResult)
    {
        pstPdnDisconnectCnf->enDiscRslt      = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
    }
    else
    {
        pstPdnDisconnectCnf->enDiscRslt      = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    }

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDisconnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_JudgeApsCmdRseultWhenDeleteCB
 功能描述  : 判断当删除PPP控制块时是否需要及填写什么响应消息和结果,如果是去激活
             消息,即使协商失败也会删除PPP控制块因此可以直接回复成功
 输入参数  : ucPppId
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-05
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_JudgeApsCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_SendApsDeactNotify(ucPppId);
        PPPC_INFO_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    enMsgType   = pstApsMsgNode->stApsCmdNode.enMsgType;
    if (ID_APS_PPP_ACT_REQ == enMsgType)
    {
        /* 如果节点中的消息类型是PPP激活消息，此时却删除PPP控制块说明协商失败 */
        PPPC_RespApsActCmd(VOS_NULL_PTR, VOS_ERR, TAF_APS_PPP_ADDR_TYPE_BUTT);
    }
    else if (ID_APS_PPP_DEACT_REQ == enMsgType)
    {
        /* 如果节点中的消息类型是PPP去激活消息，此时已达到目的，回复成功 */
        PPPC_RespApsDeActCmd(VOS_OK);
    }
    else
    {
        /* nothing */
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_JudgeEhsmCmdRseultWhenDeleteCB
 功能描述  : 判断当删除PPP控制块时是否需要及填写什么响应消息和结果,如果是去激活
             消息,即使协商失败也会删除PPP控制块因此可以直接回复成功
 输入参数  : ucPppId
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_JudgeEhsmCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    TTF_LINK_ST                                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU                        *pstEhsmMsgNode;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16            enMsgType;


    /* 由网侧断开所有PDN连接导致PPP释放链路 */
    if (PS_TRUE == g_astPppPool[ucPppId].enServerTermReq)
    {
        PPPC_SendEhsmDetachNotify(ucPppId);
        return;
    }

    pstEhsmPppCmdLink = &g_stApsCmdLink;

    /* 在EHSM命令链表中取头节点 */
    pstEhsmMsgNode    = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_SendEhsmDetachNotify(ucPppId);
        PPPC_INFO_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    enMsgType   = pstEhsmMsgNode->stEhsmCmdNode.enMsgType;

    switch(enMsgType)
    {
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            /* 如果节点中的消息类型是激活消息，此时却删除PPP控制块说明协商失败 */
            PPPC_RespEhsmAttachCmd(VOS_NULL_PTR, VOS_ERR);

            break;

        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            /* 如果节点中的消息类型是去激活消息，此时已达到目的，回复成功 */
            PPPC_RespEhsmDetachCmd(VOS_OK);

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            PPPC_RespEhsmPdnConnectCmd(VOS_NULL_PTR, VOS_ERR);

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            PPPC_RespEhsmPdnDisconnectCmd(VOS_OK);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_JudgeCmdRseultWhenDeleteCB
 功能描述  : 判断当删除PPP控制块时是否需要及填写什么响应消息和结果,如果是去激活
             消息,即使协商失败也会删除PPP控制块因此可以直接回复成功
 输入参数  : ucPppId
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_JudgeCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;


    if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId)
    {
        PPPC_WARNING_LOG1("Access auth no need to send result to nas!", ucPppId);
        return;
    }

    enRatMode = PPPC_GetRatMode();
    switch(enRatMode)
    {
        case PPPC_RAT_MODE_1X:
        case PPPC_RAT_MODE_HRPD:

            PPPC_JudgeApsCmdRseultWhenDeleteCB(ucPppId);

            break;

        case PPPC_RAT_MODE_EHRPD:

            PPPC_JudgeEhsmCmdRseultWhenDeleteCB(ucPppId);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Rat mode", enRatMode);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendApsDeactNotify
 功能描述  : 给APS发送去激活通知
 输入参数  : ucPppId    PPP ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-05
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendApsDeactNotify(VOS_UINT8 ucPppId)
{
    PPP_APS_DEACT_NTF_STRU             *pstDeactNotify;
    VOS_UINT8                           ucPdnId = 0;

    /* 如果已收到LCP TIMERNATE REQ，并且没有通知NAS ,则通知NAS，否则不处理*/
    if (PS_TRUE != g_ucLcpTermMask)
    {
        return;
    }
    g_ucLcpTermMask = PS_FALSE;

    if (VOS_OK != PPPC_1X_GetPdnId(ucPppId, &ucPdnId))
    {
        PPPC_WARNING_LOG1("Get Pdn Id failed, ucPppId:[%d]\n", ucPppId);
        PPPC_DeletePppId(ucPppId);
        return;
    }

    PPPC_DeletePppId(ucPppId);

    pstDeactNotify  = (PPP_APS_DEACT_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_NTF_STRU));
    if (VOS_NULL_PTR == pstDeactNotify)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Deact Notify Mem Fail! PppId:%d\n", ucPppId);
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDeactNotify + VOS_MSG_HEAD_LENGTH, 0, (sizeof(PPP_APS_DEACT_NTF_STRU) - VOS_MSG_HEAD_LENGTH));
    pstDeactNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstDeactNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDeactNotify->enMsgId             = ID_PPP_APS_DEACT_NTF;
    pstDeactNotify->usOpId              = 0;
    pstDeactNotify->ucPdnId             = ucPdnId;
    pstDeactNotify->enMode              = PPPC_GetRatMode();

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDeactNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_PPP_APS_DEACT_NOTIFY msg fail! PppId:%d\n", ucPppId);
    }

    PPP_DeleteCB(&g_astPppPool[ucPppId], PS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendEhsmPdnDisconnectNotify
 功能描述  : 给EHSM发送PDN Disconnect通知
 输入参数  : ucPdnId    PDN ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendEhsmPdnDisconnectNotify(VOS_UINT8 ucPdnId)
{
    CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU  *pstPdnDiscNotify;
    VOS_UINT8                           ucPppId;
    VOS_UINT32                          ulLcpSendFlag;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;


    if (VOS_OK == PPPC_IsPdnIdUnique(ucPdnId))
    {
        PPPC_INFO_LOG("The pdn Id is unique!\r\n");
        if (VOS_OK == PPPC_GetPppIdByPdn(ucPdnId, &ucPppId))
        {
            PPPC_INFO_LOG("Get PppId successed!\r\n");

            pstEhsmPppCmdLink  = &g_stApsCmdLink;

            /* 在APS命令链表中取头节点,如果链表为空说明是网络发起的重协商,需要发Detach Ind */
            pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
            if (VOS_NULL_PTR == pstEhsmMsgNode)
            {
                PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
                g_astPppPool[ucPppId].enServerTermReq = PS_TRUE;
            }

            /* 此时需要发送ppp terminate协商报文 */
            ulLcpSendFlag                    = 1;

            /* PPP发起PPP去激活 */
            PPPC_LinkDown(ucPppId, ulLcpSendFlag);
        }
        else
        {
            PPPC_WARNING_LOG1("Get PppId failed! PdnId:%d\n", ucPdnId);
        }
        return;
    }

    PPPC_ClearMappingByPdnId(ucPdnId);

    pstPdnDiscNotify  = (CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU));
    if (VOS_NULL_PTR == pstPdnDiscNotify)
    {
        PPPC_WARNING_LOG("Alloc Ppp Pdn Disconnect Notify Mem Fail!\r\n");

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnDiscNotify + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstPdnDiscNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstPdnDiscNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPdnDiscNotify->enMsgId             = ID_CTTF_CNAS_EHRPD_PDN_DISC_IND;
    pstPdnDiscNotify->usOpId              = 0;
    pstPdnDiscNotify->ucPdnId             = ucPdnId;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDiscNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_IND msg fail! PdnID:%d\n", ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendEhsmDetachNotify
 功能描述  : 给EHSM发送去激活通知
 输入参数  : ucPppId    PPP ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendEhsmDetachNotify(VOS_UINT8 ucPppId)
{
    CTTF_CNAS_EHRPD_DETACH_IND_STRU    *pstDetachNotify;

    /* 此时PPPC不能发送数据,通知PA关闭流 */
    PPPC_HRPD_SendCloseStreamReq();

    /* 如果已收到LCP TIMERNATE REQ，并且没有通知NAS ,则通知NAS，否则不处理
        如果Attach没有成功过也不用通知NAS Detach_ind */
    if ((PS_TRUE != g_ucLcpTermMask) || (PS_TRUE != g_astPppPool[ucPppId].enInactiveTimerEnable))
    {
        PPPC_WARNING_LOG2("No need to Notify EHSM", g_ucLcpTermMask,
                g_astPppPool[ucPppId].enInactiveTimerEnable);
        return;
    }
    g_ucLcpTermMask = PS_FALSE;

    PPPC_DeletePppId(ucPppId);

    pstDetachNotify  = (CTTF_CNAS_EHRPD_DETACH_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_IND_STRU));
    if (VOS_NULL_PTR == pstDetachNotify)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Detach Notify Mem Fail! PppId:%d\n", ucPppId);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDetachNotify + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(CTTF_CNAS_EHRPD_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstDetachNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstDetachNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDetachNotify->enMsgId             = ID_CTTF_CNAS_EHRPD_DETACH_IND;
    pstDetachNotify->usOpId              = 0;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_CTTF_CNAS_EHRPD_DETACH_IND msg fail! PppId:%d\n", ucPppId);
    }

    PPP_DeleteCB(&g_astPppPool[ucPppId], PS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ReceiveLCPTermReq
 功能描述  : 收到网侧去激活通知
 输入参数  : ucPppId    PPP ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ReceiveLCPTermReq(VOS_UINT8 ucPppId)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;

    enRatMode = PPPC_GetRatMode();
    switch(enRatMode)
    {
        case PPPC_RAT_MODE_1X:
        case PPPC_RAT_MODE_HRPD:

            PPPC_SendApsDeactNotify(ucPppId);

            break;

        case PPPC_RAT_MODE_EHRPD:

            PPPC_SendEhsmDetachNotify(ucPppId);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Rat mode", enRatMode);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_MD5ChapAuthReq
 功能描述  : HRPD模式，CHAP鉴权，由UIM卡使用MD5算法计算，由SIM卡产生Response
 输入参数  : PPPINFO_S *pstPppInfo, PPPAUTHMSG_S *pstAuthMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-29
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_UIM_MD5ChapAuthReq(PPPINFO_S *pstPppInfo, PPPC_AUTH_MSG_STRU *pstAuthMsg)
{
    USIMM_CDMASPECAUTH_REQ_STRU        *pstMsg;


    /* 内部调用，保证入参非空 */

    /* 申请消息内存 */
    pstMsg   = (USIMM_CDMASPECAUTH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_CDMASPECAUTH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*填充消息内容*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_CDMASPECAUTH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (MODEM_ID_0 == g_stPppContext.enModemId)
    {
        pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_USIM;
    }
    else
    {
        pstMsg->stMsgHeader.ulReceiverPid     = I1_WUEPS_PID_USIM;
    }
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_CDMASPECAUTH_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_CDMA_APP;

    pstMsg->enAuthType                        = USIMM_CDMASPEC_COMPUTEIP;
    pstMsg->uAuthData.stComputeIP.enComputeIPType = USIMM_COMPUTEIP_HRPD;
    pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.ucCHAPID = pstAuthMsg->ucPktID;
    pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.stChapChallenge.ucDataLen = pstAuthMsg->ucPwdLen;


    PS_MEM_CPY(pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.stChapChallenge.aucData,
                pstAuthMsg->szPwd, pstAuthMsg->ucPwdLen);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_CDMASPECAUTH_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : PPPC_GetPppAuthInfo
 功能描述  : 获取pppContext
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-12-10
    作    者   : q00359829
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID PPPC_GetPppAuthInfo(CTTF_PPPC_AUTH_INFO_STRU *pstPppAuthInfo)
{
    pstPppAuthInfo->ulUserNameLen = g_stPppContext.ulUserNameLen;
    pstPppAuthInfo->ulPasswordLen = g_stPppContext.ulPasswordLen;
    PS_MEM_CPY(&(pstPppAuthInfo->aucUserName[0]),&(g_stPppContext.aucUserName[0]),
                    sizeof(pstPppAuthInfo->aucUserName));
    PS_MEM_CPY(&(pstPppAuthInfo->aucPassword[0]),&(g_stPppContext.aucPassword[0]),
                    sizeof(pstPppAuthInfo->aucPassword));

    pstPppAuthInfo->ucAANaiLen = g_stPppContext.stHrpdContext.ucAccessAuthLen;
    PS_MEM_CPY(&(pstPppAuthInfo->aucAANai[0]),&(g_stPppContext.stHrpdContext.aucAccessAuthUserName[0]),
                    sizeof(pstPppAuthInfo->aucAANai));
}

/*****************************************************************************
 函 数 名  : PPPC_StartPppInactiveTimer
 功能描述  : 启动MAX PPP Inactive Timer
 输入参数  : ucPppId         PPP ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-12-31
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_StartPppInactiveTimer(VOS_UINT8 ucPppId)
{
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTimerLen = VOS_TIMER_MAX_LENGTH;


    pstPppInfo = &g_astPppPool[ucPppId];

    /* 判断Max PPP Inactive Timer开关是否打开 */
    if (PS_TRUE != pstPppInfo->enInactiveTimerEnable)
    {
        return;
    }

    /* 启动MAX PPP Inactive Timer */
    if (VOS_NULL_PTR != pstPppInfo->hPppInactiveTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstPppInfo->hPppInactiveTimer));
        pstPppInfo->hPppInactiveTimer = VOS_NULL_PTR;
    }
    /* VOS定时器时长最大为18小时，ulTimerLen单位是毫秒，ulPppInactTimerLen单位是秒，需进行转换 */
    if (pstPppInfo->ulPppInactTimerLen < ulTimerLen/1000)
    {
        ulTimerLen = pstPppInfo->ulPppInactTimerLen*1000;
    }
    pstPppInfo->ulPppInactTimeOutCnt = 0;
    ulRet = VOS_StartRelTimer(&(pstPppInfo->hPppInactiveTimer),
                      MID_PPPC,
                      ulTimerLen,
                      pstPppInfo->ulRPIndex,
                      PPPC_MAX_PPP_INACTIVE_TIMER,
                      VOS_TIMER_NOLOOP,
                      VOS_TIMER_PRECISION_0);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Start PPP Inactive Timer Failed", ucPppId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_InactivePppTimeoutProc
 功能描述  : MAX PPP Inactive Timer超时
 输入参数  : ucPppId         PPP ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-12-31
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_InactivePppTimeoutProc(VOS_UINT8 ucPppId)
{
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTimerLen = VOS_TIMER_MAX_LENGTH;
    VOS_UINT32                          ulReminTimerLen;

    pstPppInfo = &g_astPppPool[ucPppId];

    pstPppInfo->ulPppInactTimeOutCnt++;

    pstPppInfo->hPppInactiveTimer = VOS_NULL_PTR;

    if (pstPppInfo->ulPppInactTimeOutCnt * ulTimerLen/1000 >= pstPppInfo->ulPppInactTimerLen)
    {
        g_ucLcpTermMask = PS_TRUE;
        PPPC_DisConnAllPDN(ucPppId);
        /*PPPC_SendEhsmDetachNotify(ucPppId);*/
    }
    else
    {
        /* VOS定时器时长最大为18小时，ulTimerLen单位是毫秒，ulPppInactTimerLen单位是秒，需进行转换 */
        ulReminTimerLen = pstPppInfo->ulPppInactTimerLen -  pstPppInfo->ulPppInactTimeOutCnt * ulTimerLen/1000;
        if (ulReminTimerLen < ulTimerLen/1000)
        {
            ulTimerLen = ulReminTimerLen*1000;
        }
        ulRet = VOS_StartRelTimer(&(pstPppInfo->hPppInactiveTimer),
                      MID_PPPC,
                      ulTimerLen,
                      pstPppInfo->ulRPIndex,
                      PPPC_MAX_PPP_INACTIVE_TIMER,
                      VOS_TIMER_NOLOOP,
                      VOS_TIMER_PRECISION_0);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG1("Start PPP Inactive Timer Failed", ucPppId);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SetAttachErrorCode
 功能描述  : 设置Attach失败的原因值
 输入参数  : enErrorCode         失败的原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-12
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SetAttachErrorCode(CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16  enErrorCode)
{
    VOS_UINT32                          ulRet;
    PDN_CONTEXT_S                      *pstPDNContext = VOS_NULL_PTR;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;

    if ((CNAS_CTTF_EHRPD_ERROR_CODE_LCP_EAP_FAILURE == enErrorCode)
         || (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_OTHER_FAILURE == enErrorCode))
    {
        /* EAP鉴权失败和ESTABLISH阶段LCP重传次数达到门限导致的Attach失败应从队列头节点中取PDN ID */

        pstEhsmPppCmdLink  = &g_stApsCmdLink;

        /* 在APS命令链表中取头节点 */
        pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
        if (VOS_NULL_PTR == pstEhsmMsgNode)
        {
            PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
            return;
        }

        ulRet = PPP_GetPDNContextByPDNID(pstEhsmMsgNode->ucPdnId,&pstPDNContext);
        if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext) )
        {
            PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
            return;
        }

        pstPDNContext->stEhrpd.enErrorCode = enErrorCode;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendNasModify
 功能描述  : 通知NAS Modify
 输入参数  : pstVSNCPInfo       VSNCP实体
             pstPDNContext      PDN上下文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-01-12
    作    者   : t00359887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendEhsmModifyInd(PPPVSNCPINFO_S *pstVSNCPInfo)
{
    CTTF_CNAS_EHRPD_MODIFY_IND_STRU    *pstModify;
    PDN_CONTEXT_S                      *pstPDNContext;
    PPPINFO_S                          *pstPppInfo;
    PPPLCPINFO_S                       *pstLcpInfo;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    VOS_UINT32                          ulRet;

    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    /* 如果当前队列节点为空或者当前处理队列节点中的PDN ID与VSNCP实体中的PDN ID不相同说明是重协商才需要通知NAS Modify */
    if ((VOS_NULL_PTR != pstEhsmMsgNode)
         && (pstEhsmMsgNode->ucPdnId == pstVSNCPInfo->ucPDNID))
    {
        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID,
                                     &pstPDNContext);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return;
    }

    pstModify = (CTTF_CNAS_EHRPD_MODIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstModify)
    {
        PPPC_ERROR_LOG("Alloc NAS Ehrpd Modify Ind Mem Fail!\r\n");
        return;
    }

    pstModify->ulReceiverPid    = UEPS_PID_EHSM;
    pstModify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstModify->enMsgId          = ID_CTTF_CNAS_EHRPD_MODIFY_IND;
    pstModify->usOpId           = 0;
    pstModify->ucPdnId          = pstVSNCPInfo->ucPDNID;
    pstModify->usMtu            = PPP_GetDefaultMru();

    if (VOS_NULL_PTR != pstVSNCPInfo)
    {
        pstPppInfo                      = (PPPINFO_S *)(pstVSNCPInfo->pstPppInfo);

        if (VOS_NULL_PTR != pstPppInfo)
        {
            pstLcpInfo                  = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;

            if ((VOS_NULL_PTR != pstLcpInfo)
                 && (1 == pstLcpInfo->stHisOptions.neg_mru))
            {
                pstModify->usMtu     = pstLcpInfo->stHisOptions.mru;
            }
        }
    }

    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstModify->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);
    /* 拷贝APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));

    /* 发送Modify消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstModify))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_MODIFY_IND msg fail!");
    }

    return;
}
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

