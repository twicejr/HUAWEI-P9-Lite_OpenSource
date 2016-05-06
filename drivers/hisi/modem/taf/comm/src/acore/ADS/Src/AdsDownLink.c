
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "mdrv.h"
#include "AcpuReset.h"
#include "AdsFilter.h"
#include "AdsDhcpInterface.h"
#include "AdsMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DOWNLINK_C
/*lint +e767*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : ADS_DL_CCpuResetCallback
 功能描述  : C核单独复位时ADS DL的回调处理函数
 输入参数  : enParam   -- 0表示复位前， 其他表示复位后
             lUserData -- 用户数据
 输出参数  : 无
 返 回 值  : VOS_INT
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月10日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_INT ADS_DL_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             lUserData
)
{
    ADS_CCPU_RESET_IND_STRU                *pstMsg = VOS_NULL_PTR;

    /* 参数为0表示复位前调用 */
    if (MDRV_RESET_CB_BEFORE == enParam)
    {
        ADS_TRACE_HIGH("before reset enter.\n");

        /* 防止IPF数据残留, 主动读取一次RD */
        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
        ADS_DBG_DL_CCORE_RESET_TRIG_EVENT(1);

        /* 构造消息 */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("before reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /* 填写消息头 */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_START_IND;

        /* 发消息 */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_TRACE_HIGH("before reset: send msg failed.\n");
            return VOS_ERROR;
        }

        /* 等待回复信号量初始为锁状态，等待消息处理完后信号量解锁。 */
        if (VOS_OK != VOS_SmP(ADS_GetDLResetSem(), ADS_RESET_TIMEOUT_LEN))
        {
            ADS_TRACE_HIGH("before reset VOS_SmP failed.\n");
            ADS_DBG_DL_RESET_LOCK_FAIL_NUM(1);
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("before reset succ.\n");
        return VOS_OK;
    }
    /* 复位后 */
    else if (MDRV_RESET_CB_AFTER == enParam)
    {
        ADS_TRACE_HIGH("after reset enter.\n");

        /* 构造消息 */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("after reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /* 填写消息头 */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_END_IND;

        /* 发消息 */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_TRACE_HIGH("after reset: send msg failed.\n");
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("after reset: succ.\n");
        ADS_DBG_DL_RESET_SUCC_NUM(1);
        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : ADS_DL_IpfIntCB
 功能描述  : ADS下行数据处理模块向IPF注册的中断回调函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化
*****************************************************************************/
VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID)
{
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
    ADS_DBG_DL_RCV_IPF_RD_INT_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_IpfAdqEmptyCB
 功能描述  : ADS向IPF注册的下行ADQ空中断处理函数
 输入参数  : IPF_ADQ_EMPTY_E eAdqEmpty
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : l60609
    修改内容   : 新生成函数
*****************************************************************************/
VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty)
{
    if (IPF_EMPTY_ADQ0 == eAdqEmpty)
    {
        ADS_DBG_DL_ADQ_RCV_AD0_EMPTY_INT_NUM(1);
    }
    else if (IPF_EMPTY_ADQ1 == eAdqEmpty)
    {
        ADS_DBG_DL_ADQ_RCV_AD1_EMPTY_INT_NUM(1);
    }
    else
    {
        ADS_DBG_DL_ADQ_RCV_AD0_EMPTY_INT_NUM(1);
        ADS_DBG_DL_ADQ_RCV_AD1_EMPTY_INT_NUM(1);
    }

    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_RCV_IPF_ADQ_EMPTY_INT_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvTiAdqEmptyExpired
 功能描述  : TI_ADS_DL_ADQ_EMPTY超时处理函数
 输入参数  : VOS_UINT32                          ulParam,
             VOS_UINT32                          ulTimerName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* 触发下行ADQ空中断处理事件 */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_ADQ_EMPTY_TMR_TIMEOUT_NUM(1);
    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ConfigAdq
 功能描述  : 配置AD
 输入参数  : IPF_AD_TYPE_E                       enAdType
             VOS_UINT                            ulIpfAdNum
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_ConfigAdq(
    IPF_AD_TYPE_E                       enAdType,
    VOS_UINT                            ulIpfAdNum
)
{
    IPF_AD_DESC_S                      *pstAdDesc = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc  = VOS_NULL_PTR;
    VOS_UINT32                          ulPoolId;
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          ulLen;
    VOS_INT32                           lRslt;

    if (IPF_AD_0 == enAdType)
    {
        ulPoolId = ADS_IPF_MEM_POOL_ID_AD0;
        ulLen    = ADS_IPF_AD0_MEM_BLK_SIZE;
    }
    else
    {
        ulPoolId = ADS_IPF_MEM_POOL_ID_AD1;
        ulLen    = ADS_IPF_AD1_MEM_BLK_SIZE;
    }

    for (ulCnt = 0; ulCnt < ulIpfAdNum; ulCnt++)
    {
        pstImmZc = ADS_IPF_AllocMem(ulPoolId, ulLen, IMM_MAC_HEADER_RES_LEN);
        if (VOS_NULL_PTR == pstImmZc)
        {
            ADS_DBG_DL_ADQ_ALLOC_MEM_FAIL_NUM(1);
            break;
        }

        ADS_DBG_DL_ADQ_ALLOC_MEM_SUCC_NUM(1);

        /* 填写AD描述符: OUTPUT0 ---> 目的地址; OUTPUT1 ---> SKBUFF */
        pstAdDesc = ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, ulCnt);
        pstAdDesc->u32OutPtr0 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc->data);
        pstAdDesc->u32OutPtr1 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc);
    }

    if (0 == ulCnt)
    {
        return 0;
    }

    /* 申请到AD才需要配置ADQ */
    lRslt = mdrv_ipf_config_dlad(enAdType, ulCnt, ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, 0));
    if (IPF_SUCCESS != lRslt)
    {
        /* 配置失败，释放内存 */
        ulTmp = ulCnt;
        for (ulCnt = 0; ulCnt < ulTmp; ulCnt++)
        {
            pstAdDesc = ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, ulCnt);
            pstImmZc  = (IMM_ZC_STRU *)phys_to_virt(pstAdDesc->u32OutPtr1);
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_ADQ_FREE_MEM_NUM(1);
        }

        ADS_DBG_DL_ADQ_CFG_IPF_FAIL_NUM(1);
        return 0;
    }

    /* 输出实际配置的AD数目 */
    ADS_DBG_DL_ADQ_CFG_AD_NUM(ulCnt);
    ADS_DBG_DL_ADQ_CFG_IPF_SUCC_NUM(1);
    return ulCnt;
}

/*****************************************************************************
 函 数 名  : ADS_DL_AllocMemForAdq
 功能描述  : 处理ADQ
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年4月24日
    作    者   : A00165503
    修改内容   : DTS2015042201072: 优化ADQ空中断处理, 防止内存无法及时补充

*****************************************************************************/
VOS_VOID ADS_DL_AllocMemForAdq(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT32                          ulIpfAd0Num;
    VOS_UINT32                          ulIpfAd1Num;
    VOS_UINT32                          ulActAd0Num;
    VOS_UINT32                          ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* 获取两个ADQ的空闲的AD个数 */
    lRslt = mdrv_ipf_get_dlad_num(&ulIpfAd0Num, &ulIpfAd1Num);
    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_ADQ_GET_FREE_AD_FAIL_NUM(1);
        return;
    }

    ADS_DBG_DL_ADQ_GET_FREE_AD_SUCC_NUM(1);

    /* 首先配置大内存的ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ulActAd1Num = ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num);
        ADS_DBG_DL_ADQ_CFG_AD1_NUM(ulActAd1Num);
    }

    /* 再配置小内存的ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ulActAd0Num = ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num);
        ADS_DBG_DL_ADQ_CFG_AD0_NUM(ulActAd0Num);
    }

    /* AD0为空或者AD1为空需要重新启动定时器 */
    if ( ((0 == ulActAd0Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd0Num))
      || ((0 == ulActAd1Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd1Num)) )
    {
        /* 如果两个ADQ任何一个空且申请不到内存，启定时器 */
        ADS_StartTimer(TI_ADS_DL_ADQ_EMPTY, TI_ADS_DL_ADQ_EMPTY_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_SendNdClientDataInd
 功能描述  : RA包及ECHO REQUEST等报文通过VOS发给NDCLIENT
 输入参数  : VOS_VOID *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_SendNdClientDataInd(IMM_ZC_STRU *pstImmZc)
{
    ADS_NDCLIENT_DATA_IND_STRU         *pstMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;

    ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

    /* 申请消息 */
    pstMsg = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + ulDataLen - 2);
    if (VOS_NULL_PTR == pstMsg)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstMsg is NULL!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_NDCLIENT_DATA_IND_STRU) + ulDataLen - 2 - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    pstMsg->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstMsg->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstMsg->enModemId     = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
    pstMsg->ucRabId       = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);;
    pstMsg->usLen         = (VOS_UINT16)ulDataLen;

    /* 拷贝数据内容 */
    pucData = IMM_ZcGetDataPtr(pstImmZc);
    PS_MEM_CPY(pstMsg->aucData, pucData, ulDataLen);

    /* 发送消息 */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg);
    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_SendDhcpClientDataInd
 功能描述  : DHCPv6报文通过VOS发给DHCP CLIENT
 输入参数  : IMM_ZC_STRU *pstImmZc
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月18日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_SendDhcpClientDataInd(IMM_ZC_STRU *pstImmZc)
{
    ADS_DHCP_DATA_IND_STRU             *pstMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;

    ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

    /* 申请消息 */
    pstMsg = (ADS_DHCP_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_DHCP_DATA_IND_STRU) + ulDataLen - 2);

    /* 内存申请失败，返回 */
    if( VOS_NULL_PTR == pstMsg )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpClientDataInd: pstMsg is NULL!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_DHCP_DATA_IND_STRU) + ulDataLen - 2 - VOS_MSG_HEAD_LENGTH));

    /* 填写消息内容 */
    pstMsg->ulReceiverPid = UEPS_PID_DHCP;
    pstMsg->enMsgId       = ID_ADS_DHCP_DATA_IND;
    pstMsg->enModemId     = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
    pstMsg->ucRabId       = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);
    pstMsg->usLen         = (VOS_UINT16)ulDataLen;

    /* 拷贝数据 */
    pucData = IMM_ZcGetDataPtr(pstImmZc);
    PS_MEM_CPY(pstMsg->aucData, pucData, ulDataLen);

    /* 调用VOS发送原语 */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg);
    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpClientDataInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_FreeIpfUsedAd0
 功能描述  : 释放IPF的使用的AD0
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月18日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_DL_FreeIpfUsedAd0(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    /*lint -e813*/ /* added by zwx247453 for pc工程转3650, 2015-08-24, begin */
    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD0_DESC_SIZE];
    /*lint +e813*/ /* added by zwx247453 for pc工程转3650, 2015-08-24, end */

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE));
    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_0, (VOS_UINT32 *)&ulAdNum, astAdDesc))
    {
        /* 释放ADQ0的内存 */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)phys_to_virt(astAdDesc[i].u32OutPtr1));
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_FreeIpfUsedAd1
 功能描述  : 释放IPF的使用的AD1
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月18日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_DL_FreeIpfUsedAd1(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    /*lint -e813*/ /* added by zwx247453 for pc工程转3650, 2015-08-24, begin */
    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD1_DESC_SIZE];
    /*lint +e813*/ /* added by zwx247453 for pc工程转3650, 2015-08-24, end */

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD1_DESC_SIZE));
    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_1, (VOS_UINT32 *)&ulAdNum, astAdDesc))
    {
        /* 释放ADQ1的内存 */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD1_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)phys_to_virt(astAdDesc[i].u32OutPtr1));
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_Xmit
 功能描述  : 分发数据包, 并在每个承载上的最后一个包上做标记
 输入参数  : ucInstance --- modem ID
             ucRabId    --- RABID [5, 15]
             pstImmZc   --- IP buff
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月29日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_Xmit(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId,
    IMM_ZC_STRU                        *pstImmZc
)
{
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstLstImmZc    = VOS_NULL_PTR;
    VOS_UINT32                          ulExParam;
    VOS_UINT16                          usIpfResult;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucExRabId;

    /* 检查MODEMID */
    if (!ADS_IS_MODEMID_VALID(ucInstance))
    {
        if (VOS_NULL_PTR != pstImmZc)
        {
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_RMNET_MODEMID_ERR_NUM(1);
        }

        return;
    }

    /* 获取RABID对应下行回调函数指针 */
    if (ADS_IS_RABID_VALID(ucRabId))
    {
        pRcvDlDataFunc = ADS_DL_GET_DATA_CALLBACK_FUNC(ucInstance, ucRabId);
        ulExParam      = ADS_DL_GET_DATA_EXPARAM(ucInstance, ucRabId);
    }
    else
    {
        if (VOS_NULL_PTR != pstImmZc)
        {
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_RMNET_RABID_ERR_NUM(1);
        }

        return;
    }

    /* 获取缓存的数据 */
    pstLstImmZc = ADS_DL_GET_LST_DATA_PTR(ucInstance, ucRabId);

    /* 发送下行数据 */
    if (VOS_NULL_PTR != pRcvDlDataFunc)
    {
        if (VOS_NULL_PTR != pstLstImmZc)
        {
            pstLstImmZc->psh = (VOS_NULL_PTR != pstImmZc) ? 0 : 1;

            usIpfResult = ADS_DL_GET_IPF_RESULT_FORM_IMM(pstLstImmZc);
            enIpType    = ADS_DL_GET_IPTYPE_FROM_IPF_RESULT(usIpfResult);
            ucExRabId   = ADS_BUILD_EXRABID(ucInstance, ucRabId);

            (VOS_VOID)pRcvDlDataFunc(ucExRabId, pstLstImmZc, enIpType, ulExParam);
            ADS_DBG_DL_RMNET_TX_PKT_NUM(1);
        }

        ADS_DL_SET_LST_DATA_PTR(ucInstance, ucRabId, pstImmZc);
    }
    else
    {
        if (VOS_NULL_PTR != pstImmZc)
        {
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_RMNET_NO_FUNC_FREE_PKT_NUM(1);
        }

        if (VOS_NULL_PTR != pstLstImmZc)
        {
            IMM_ZcFree(pstLstImmZc);
            ADS_DBG_DL_RMNET_NO_FUNC_FREE_PKT_NUM(1);
        }

        ADS_DL_SET_LST_DATA_PTR(ucInstance, ucRabId, VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ProcTxData
 功能描述  : 处理下行RD
 输入参数  : pstImmZc --- 非空代表正常数据, 空指针代表要推送最后一个包
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月1日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_ProcTxData(IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    if (VOS_NULL_PTR != pstImmZc)
    {
        ucInstance = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
        ucRabId    = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);

        ADS_DL_Xmit(ucInstance, ucRabId, pstImmZc);
    }
    else
    {
        for (ucInstance = 0; ucInstance < ADS_INSTANCE_MAX_NUM; ucInstance++)
        {
            for (ucRabId = ADS_RAB_ID_MIN; ucRabId <= ADS_RAB_ID_MAX; ucRabId++)
            {
                ADS_DL_Xmit(ucInstance, ucRabId, VOS_NULL_PTR);
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RdDescTransImmMem
 功能描述  : 将RD描述符转换成IMM内存格式, 保存相关描述符信息
 输入参数  : pstRdDesc --- RD描述符
 输出参数  : 无
 返 回 值  : IMM_ZC_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
IMM_ZC_STRU* ADS_DL_RdDescTransImmMem(const IPF_RD_DESC_S *pstRdDesc)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulCacheLen;

    /* 将OUT指针转换为IMM内存指针 */
    pstImmZc = (IMM_ZC_STRU *)phys_to_virt(pstRdDesc->u32OutPtr);
    if (VOS_NULL_PTR == pstImmZc)
    {
        return VOS_NULL_PTR;
    }

    /* 统一刷CACHE */
    ulCacheLen = pstRdDesc->u16PktLen + IMM_MAC_HEADER_RES_LEN;
    ADS_IPF_DL_MEM_UNMAP(pstImmZc, ulCacheLen);

    /* 设置数据真实长度 */
    IMM_ZcPut(pstImmZc, pstRdDesc->u16PktLen);

    /* 保存描述符信息: u16Result/u16UsrField1 */
    ADS_DL_SAVE_RD_DESC_TO_IMM(pstImmZc, pstRdDesc);

    return pstImmZc;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ProcIpfResult
 功能描述  : ADS下行IPF事件处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年4月24日
    作    者   : s62952
    修改内容   : DTS2012040103554: D态单板复位, 增加喂狗处理

  3.日    期   : 2012年5月4日
    作    者   : z60575
    修改内容   : DTS2012050301768: IPF失败时内存泄露

  4.日    期   : 2012年5月24日
    作    者   : z60575
    修改内容   : DTS2012052306799: 现在狗是常开的，不需要判断，并且WatchDog相关
                 代码已经无人维护，全局变量无人赋值，判断后实际就不喂狗，删除判断

  5.日    期   : 2012年11月19日
    作    者   : A00165503
    修改内容   : DTS2012112206761: 底软动态组包参数调整

  6.日    期   : 2013年12月11日
    作    者   : A00165503
    修改内容   : DTS2013120905502: 不丢弃IPF检查错误的数据包

  7.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : DTS2015081008249: ADS数传过程中持锁, 防止系统进入休眠

***************************************************************************/
VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID)
{
    ADS_DL_IPF_RESULT_STRU             *pstIpfResult = VOS_NULL_PTR;
    IPF_RD_DESC_S                      *pstRdDesc = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulRdNum = IPF_DLRD_DESC_SIZE;
    VOS_UINT32                          ulTxTimeout = 0;
    VOS_UINT32                          ulCacheLen;
    VOS_UINT32                          ulCnt;

    /*
    IPF_RD_DESC_S中u16Result含义
    [15]Reserve
    [14]bd_cd_noeqBD中len和CD的长度不等错误提示，0表示长度匹配，1表示长度不匹配
    [13]pkt_parse_err数据解析错误指示，0表示数据解析正常，1表示数据解析错误
    [12]bd_pkt_noeqBD中len和IP包头指示的len不等错误指示，0表示长度匹配，1表示长度不匹配
    [11]head_len_err IPV4长度错误指示信号，IPV6不检查长度，0表示头长度正确，1表示头长度错误
    [10]version_err版本号错误指示，0表示版本号是4或6，1表示版本号不是4或6
    [9]ip_type IP包类型，0表示IPV4，1表示IPV6
    [8]ff_type分片包第一个分片是否包含上层头指示，0表示分片包第一个分片包括上层头(IP包未分片时也为0)
     1表示分片包第一个分片包括上层头
    [7:6]pf_type IP包分片指示类型，00表示IP包未分片，01表示IP包分片，且为第一个分片，
       02表示分片，且为最后一个分片，03表示分片，且为中间分片
    [0:5]bear_id承载号，如果为0x3F代表所有过滤器不匹配
    */

    /*
    IPF_RD_DESC_S中user field域含义
    u16UsrField1: RabId
    u32UsrField2: 目的TTF_MEM_ST指针
    u32UsrField3: 源TTF_MEM_ST指针
    */

    /* 获取RD */
    pstRdDesc = ADS_DL_GET_IPF_RD_DESC_PTR(0);
    mdrv_ipf_get_dlrd(&ulRdNum, pstRdDesc);

    /* 获取的RD为0 */
    if (0 == ulRdNum)
    {
        /* 增加RD获取个数为0的统计个数 */
        ADS_DBG_DL_RDQ_GET_RD0_NUM(1);
        return;
    }

#if (FEATURE_OFF == FEATURE_LTE)
    mdrv_wdt_feed(0);
#endif

    /* 增加RD统计个数 */
    ADS_DBG_DL_RDQ_RX_RD_NUM(ulRdNum);

    /* 先配置AD，再处理RD */
    ADS_DL_AllocMemForAdq();

    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt++)
    {
        pstRdDesc = ADS_DL_GET_IPF_RD_DESC_PTR(ulCnt);

        /* 转换为IMM内存 */
        pstImmZc = ADS_DL_RdDescTransImmMem(pstRdDesc);
        if (VOS_NULL_PTR == pstImmZc)
        {
            ADS_DBG_DL_RDQ_TRANS_MEM_FAIL_NUM(1);
            continue;
        }

        /* 统计下行周期性收到的数据字节数，用于流量查询 */
        ADS_RECV_DL_PERIOD_PKT_NUM(pstRdDesc->u16PktLen);

        /* 获取IPF RESULT */
        pstIpfResult = (ADS_DL_IPF_RESULT_STRU *)&(pstRdDesc->u16Result);

        /* BearId 0x3F: 正常下行数据包需要转发给NDIS/PPP/RNIC*/
        if (CDS_ADS_DL_IPF_BEARER_ID_INVALID == pstIpfResult->usBearedId)
        {
            if (ADS_DL_IPF_RD_RSLT_IS_ERR_PKT(*((VOS_UINT16 *)pstIpfResult)))
            {
                ADS_DBG_DL_RDQ_RX_ERR_PKT_NUM(1);
            }

            ADS_MNTN_HookIpPkt(pstImmZc, ID_IPS_TRACE_ADS_DL,
                               pstRdDesc->u16UsrField1, pstRdDesc->u32UsrField2,
                               pstRdDesc->u32UsrField3, pstRdDesc->u16Result);

            ulTxTimeout = ADS_DL_TX_WAKE_LOCK_TMR_LEN;

            ADS_DL_ProcTxData(pstImmZc);
            ADS_DBG_DL_RDQ_RX_NORM_PKT_NUM(1);
        }
        else
        {
            /* 统一刷CACHE */
            ulCacheLen = IMM_ZcGetUsedLen(pstImmZc) + IMM_MAC_HEADER_RES_LEN;
            ADS_IPF_SPE_MEM_UNMAP(pstImmZc, ulCacheLen);

            /* 匹配下行过滤规则的数据
             * BearId 19: NDClient包，需要转发给NDClient
             * BearId 17: DHCPv6包，需要转发给DHCP
             * [0, 15]定义为非法数据包;
             * [16, 18, 20, 21]目前直接释放
             */
            if (CDS_ADS_DL_IPF_BEARER_ID_ICMPV6 == pstIpfResult->usBearedId)
            {
                ADS_DL_SendNdClientDataInd(pstImmZc);
                ADS_DBG_DL_RDQ_RX_ND_PKT_NUM(1);
            }
            else if (CDS_ADS_DL_IPF_BEARER_ID_DHCPV6 == pstIpfResult->usBearedId)
            {
                ADS_DL_SendDhcpClientDataInd(pstImmZc);
                ADS_DBG_DL_RDQ_RX_DHCP_PKT_NUM(1);
            }
            else
            {
                ADS_DBG_DL_RDQ_FILTER_ERR_PKT_NUM(1);
            }

            ADS_IPF_SPE_MEM_MAP(pstImmZc, ulCacheLen);
            IMM_ZcFree(pstImmZc);
        }
    }

    /* 推送最后一个数据 */
    ADS_DL_ProcTxData(VOS_NULL_PTR);

    ADS_DL_EnableTxWakeLockTimeout(ulTxTimeout);
    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_IsFcAssemTuneNeeded
 功能描述  : 检查是否需要调整流控组包参数
 输入参数  : ulRdNum   - 数据包个数
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要调整
             VOS_FALSE - 不需要调整
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;
    VOS_UINT32                          ulRslt = VOS_FALSE;

    /* 获取流控阈值参数 */
    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    if (0 != pstFcAssemInfo->ulEnableMask)
    {
        pstFcAssemInfo->ulRdCnt += ulRdNum;

        if (ADS_TIME_AFTER_EQ(ADS_GET_CURR_KERNEL_TIME(), (pstFcAssemInfo->ulTmrCnt + pstFcAssemInfo->ulExpireTmrLen)))
        {
            if (VOS_FALSE == pstFcAssemInfo->ulFcActiveFlg)
            {
                if (pstFcAssemInfo->ulRdCnt >= pstFcAssemInfo->ulRateUpLev)
                {
                    ADS_DBG_DL_FC_ACTIVATE_NUM(1);
                    pstFcAssemInfo->ulFcActiveFlg = VOS_TRUE;
                    ulRslt = VOS_TRUE;
                }
            }
            else
            {
                if (pstFcAssemInfo->ulRdCnt <= pstFcAssemInfo->ulRateDownLev)
                {
                    pstFcAssemInfo->ulFcActiveFlg = VOS_FALSE;
                }
            }

            ADS_DBG_DL_FC_TMR_TIMEOUT_NUM(1);
            pstFcAssemInfo->ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
            pstFcAssemInfo->ulRdCnt = 0;
        }
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RegDrvAssemFunc
 功能描述  : 下行流控注册函数, 用于解决下行突发流量, FC无法及时调整流程参数,
             FC向ADS注册流控的回调函数, 以及触发流控阈值参数
 输入参数  : pstDrvAssemParam - 触发流控阈值参数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID ADS_DL_RegDrvAssemFunc(FC_ADS_DRV_ASSEM_STRU *pstDrvAssemParam)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemParamInfo;

    pstFcAssemParamInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    pstFcAssemParamInfo->ulEnableMask     = pstDrvAssemParam->ucEnableMask;
    pstFcAssemParamInfo->ulRateUpLev      = pstDrvAssemParam->ulDlRateUpLev;
    pstFcAssemParamInfo->ulRateDownLev    = pstDrvAssemParam->ulDlRateDownLev;
    pstFcAssemParamInfo->ulExpireTmrLen   = pstDrvAssemParam->ulExpireTmrLen;
    pstFcAssemParamInfo->pFcAssemTuneFunc = pstDrvAssemParam->pDrvAssemFunc;

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RegDlDataCallback
 功能描述  : ADS下行数据处理模块为上层模块提供的注册下行数据接收函数接口
 输入参数  : ucExRabId --- 扩展RABID
             pFunc     --- 数据接收回调
             ulExParam --- 扩展参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_RegDlDataCallback(
    VOS_UINT8                           ucExRabId,
    RCV_DL_DATA_FUNC                    pFunc,
    VOS_UINT32                          ulExParam
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    /* 检查MODEMID */
    ucInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_MODEMID_VALID(ucInstance))
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_RegDlDataCallback: ModemId is invalid! <ModemId>", ucInstance);
        return VOS_ERR;
    }

    /* 检查RABID */
    ucRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ucRabId))
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_DL,
            "ADS_DL_RegDlDataCallback: RabId is invalid! <ModemId>,<RabId>", ucInstance, ucRabId);
        return VOS_ERR;
    }

    /* 保存下行数据回调参数 */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstance, ucRabId);
    pstDlRabInfo->ucRabId           = ucRabId;
    pstDlRabInfo->ulExParam         = ulExParam;
    pstDlRabInfo->pRcvDlDataFunc    = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RegFilterDataCallback
 功能描述  : ADS下行数据处理模块为上层模块提供的注册下行数据过滤接收函数接口
 输入参数  : VOS_UINT8                           ucRabId
             ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
             RCV_DL_DATA_FUNC                    pFunc
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_DL_RegFilterDataCallback(
    VOS_UINT8                           ucRabId,
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
    RCV_DL_DATA_FUNC                    pFunc
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId的高2个bit表示modem id*/
    ucInstanceIndex = ADS_GET_MODEMID_FROM_EXRABID(ucRabId);
    ucRealRabId     = ADS_GET_RABID_FROM_EXRABID(ucRabId);

    /* RabId合法性检查 */
    if (!ADS_IS_RABID_VALID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* 设置ADS下行数据过滤回调内容 */
    pstDlRabInfo->ucRabId               = ucRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = pFunc;

    /* 保存过滤地址信息 */
    ADS_FILTER_SaveIPAddrInfo(pstFilterIpAddr);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_DeregFilterDataCallback
 功能描述  : ADS下行数据处理模块为上层模块提供的去注册下行数据过滤接收函数接口
 输入参数  : VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_DL_DeregFilterDataCallback(VOS_UINT8 ucRabId)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId的高2个bit表示modem id*/
    ucInstanceIndex = ADS_GET_MODEMID_FROM_EXRABID(ucRabId);
    ucRealRabId     = ADS_GET_RABID_FROM_EXRABID(ucRabId);

    /* RabId合法性检查 */
    if (!ADS_IS_RABID_VALID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_DeregFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* 去注册ADS下行数据过滤回调内容 */
    pstDlRabInfo->pRcvDlFilterDataFunc  = VOS_NULL_PTR;

    /* 清除过滤信息 */
    ADS_FILTER_Reset();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ProcPdpStatusInd
 功能描述  : 处理PDP状态变化消息
 输入参数  : MODEM_ID_ENUM_UINT16                enModemId,
             VOS_UINT8                           ucRabId,
             ADS_PDP_STATUS_ENUM_UINT8           enPdpStatus,
             ADS_QCI_TYPE_ENUM_UINT8             enQciType,
             ADS_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_ProcPdpStatusInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    ADS_PDP_STATUS_ENUM_UINT8           enPdpStatus,
    ADS_QCI_TYPE_ENUM_UINT8             enQciType,
    ADS_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;

    enPktType      = ADS_CDS_IPF_PKT_TYPE_IP;
    ucInstanceIndex = (VOS_UINT8)enModemId;

    /* RabId合法性检查 */
    if (!ADS_IS_RABID_VALID(ucRabId))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_ProcPdpStatusInd: Rab Id is invalid");
        return VOS_ERR;
    }

    if (ADS_PDP_PPP == enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId);

    /* PDP激活 */
    if (ADS_PDP_STATUS_ACT == enPdpStatus)
    {
        /* 设置ADS下行数据回调的RABID */
        pstDlRabInfo->ucRabId           = ucRabId;
        pstDlRabInfo->enPktType         = enPktType;
    }
    /* PDP去激活  */
    else if (ADS_PDP_STATUS_DEACT == enPdpStatus)
    {
        /* 清除ADS下行数据回调内容 */
        pstDlRabInfo->ucRabId           = ADS_RAB_ID_INVALID;
        pstDlRabInfo->enPktType         = ADS_CDS_IPF_PKT_TYPE_IP;
        pstDlRabInfo->ulExParam         = 0;
        pstDlRabInfo->pRcvDlDataFunc    = VOS_NULL_PTR;
    }
    else
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_ProcPdpStatusInd: Pdp Status is invalid");
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvTafPdpStatusInd
 功能描述  : 处理ID_APS_ADS_PDP_STATUS_IND消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化
  3.日    期   : 2012年11月24日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
*****************************************************************************/
VOS_UINT32 ADS_DL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    VOS_UINT32                          ulRslt;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    ulRslt = ADS_DL_ProcPdpStatusInd(pstPdpStatusInd->enModemId,
                                     pstPdpStatusInd->ucRabId,
                                     pstPdpStatusInd->enPdpStatus,
                                     pstPdpStatusInd->enQciType,
                                     pstPdpStatusInd->enPdpType);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvCcpuResetStartInd
 功能描述  : ADS_DL收到ADS_DL消息ID_CCPU_ADS_DL_START_RESET_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数

  2.日    期   : 2015年9月1日
    作    者   : A00165503
    修改内容   : DTS2015082300106: 下行灌小包, A核触发C核单独复位后整机重启

  3.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : DTS2015081008249: ADS数传过程中持锁, 防止系统进入休眠

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;

    ADS_TRACE_HIGH("proc reset msg: enter.\n");

    /* 停止所有启动的定时器 */
    for (ucIndex = 0; ucIndex < ADS_MAX_TIMER_NUM; ucIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_DL, ucIndex, ADS_TIMER_STOP_CAUSE_USER);
    }

    /* 重置下行上下文 */
    ADS_ResetDlCtx();

    /* 释放IPF的AD */
    ADS_DL_FreeIpfUsedAd1();
    ADS_DL_FreeIpfUsedAd0();

    /* 释放信号量，使得调用API任务继续运行 */
    VOS_SmV(ADS_GetDLResetSem());

    ADS_TRACE_HIGH("proc reset msg: leave.\n");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvCcpuResetEndInd
 功能描述  : ADS_DL收到ADS_DL消息ID_CCPU_ADS_DL_RESET_END_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年09月10日
   作    者   : f00179208
   修改内容   : 新生成函数

  2.日    期   : 2015年9月1日
    作    者   : A00165503
    修改内容   : DTS2015082300106: 下行灌小包, A核触发C核单独复位后整机重启
*****************************************************************************/
VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(
    MsgBlock                           *pstMsg
)
{
    ADS_TRACE_HIGH("proc reset msg: enter.\n");

    /* 重置调试信息 */
    ADS_ResetDebugInfo();

    /* 复位IPF */
    mdrv_ipf_reinit_dlreg();

    /* 重新初始化ADQ */
    ADS_DL_AllocMemForAdq();

    ADS_TRACE_HIGH("proc reset msg: leave.\n");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvTafMsg
 功能描述  : 接收来自TAF的消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
 2.日    期   : 2014年02月14日
   作    者   : m00217266
   修改内容   : pdp status ind 改为taf aps发送
*****************************************************************************/
VOS_UINT32 ADS_DL_RcvTafMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_DL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvCdsMsg
 功能描述  : 接收来自CDS的消息
             暂时没有要处理的消息，预留便于后续扩展
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg)
{
    /* 暂时没有要处理的消息，如果收到消息可能有错误 */
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvAdsDlMsg
 功能描述  : 接收来自ADS DL的消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvAdsDlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_DL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            ADS_DL_RcvCcpuResetEndInd(pMsg);
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RcvAdsDlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ProcMsg
 功能描述  : ADS下行消息处理函数
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年4月15日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  3.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : pdp status ind 改为taf aps发送
  4.日    期   : 2015年6月25日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 消息的分发处理 */
    switch ( pMsg->ulSenderPid )
    {
        /* 来自APS的消息 */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ADS_DL_RcvTafMsg(pMsg);
            return;

        /* 来自CDS的消息 */
        case UEPS_PID_CDS:
            ADS_DL_RcvCdsMsg(pMsg);
            return;

        /* 来自ADS DL的消息 */
        case ACPU_PID_ADS_DL:
            ADS_DL_RcvAdsDlMsg(pMsg);
            return;

        default:
            return;
    }
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

