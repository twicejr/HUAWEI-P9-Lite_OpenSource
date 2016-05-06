/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsImsProc.c
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2013年07月30日
  最近修改   :
  功能描述   : 实现CDS IMS相关功能
  函数列表   :

  修改历史   :
  1.日    期   : 2013年07月30日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CDS.h"
#include "CdsImsProc.h"
#include "CdsUlProc.h"
#include "CdsDlProc.h"
#include "CdsMsgProc.h"
#include "CdsDebug.h"
#include "CdsIpfCtrl.h"
#include "CdsSoftFilter.h"
//#include "LPdcpDlProc.h"

#if (CDS_FEATURE_ON == CDS_FEATURE_IMS)
#include "ImsNicInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_IMS_PROC_C
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
VOS_UINT32  g_ulCdsTracePktFlg = PS_FALSE;
CDS_IMS_DL_FRAGMENT_BUFF_STRU  g_stCdsImsDlFragInfoBuff = {0};

/******************************************************************************
   5 函数实现
******************************************************************************/

#if (CDS_FEATURE_OFF == CDS_FEATURE_IMS)

/*****************************************************************************
 函 数 名  : IMS_NIC_RegUlDataSendCb
 功能描述  : IMS Feature 关闭时的桩函数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/

/* IMS虚拟网卡上行数据发送回调定义 */
typedef VOS_UINT32 (*IMS_NIC_SEND_UL_DATA_FUNC)(VOS_UINT8 *pData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId);

VOS_UINT32 IMS_NIC_RegUlDataSendCb(IMS_NIC_SEND_UL_DATA_FUNC pFunc, MODEM_ID_ENUM_UINT16 enModemId)
{
    (VOS_VOID)pFunc;
    (VOS_VOID)enModemId;
    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_DlDataRcv
 功能描述  : IMS Feature 关闭时的桩函数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_DlDataRcv(VOS_UINT8 *pData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    (VOS_VOID)pData;
    (VOS_VOID)usLen;
    (VOS_VOID)enModemId;

    return PS_SUCC;
}

#endif

#if (CDS_FEATURE_OFF == CDS_FEATURE_LTE)
/*****************************************************************************
 函 数 名  : CDS_ERABM_GetDefaultEpsbId
 功能描述  : LTE Feature 关闭时的桩函数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年01月20日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_ERABM_GetDefaultEpsbId(VOS_UINT8 ucDrbId, VOS_UINT8 *pucDeftEpsbId)
{
    (VOS_VOID)ucDrbId;
    *pucDeftEpsbId = 5;
    return PS_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : CDS_TtfMemCopyAlloc
 功能描述  : 新申请一块内存，将pstSrc的内容拷贝到新内存上。
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
TTF_MEM_ST* CDS_TtfMemCopyAlloc(TTF_MEM_ST *pstSrc, VOS_UINT32 ulLen)
{
    TTF_MEM_ST      *pstDest;

    pstDest = CDS_AllocTtfMem(ulLen);
    if (VOS_NULL_PTR == pstDest)
    {
        return VOS_NULL_PTR;
    }

    /*内存拷贝*/
    if (PS_SUCC != TTF_MemGetHeadData(UEPS_PID_CDS,
                                      pstSrc,
                                      pstDest->pData,
                                      pstDest->usUsed))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDest);
        return VOS_NULL_PTR;
    }

    return pstDest;
}

/*****************************************************************************
 函 数 名  : CDS_SendIpPacket2PC
 功能描述  : 将数据包发送到PC Wireshark进行解析
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_SendIpPacket2PC(TTF_MEM_ST *pstIpPkt)
{
    TTF_MEM_ST          *pstDbgPkt;

    if (PS_TRUE != g_ulCdsTracePktFlg)
    {
        return ;
    }

    /*拷贝新内存*/
    pstDbgPkt = CDS_TtfMemCopyAlloc(pstIpPkt, pstIpPkt->usUsed);
    if (VOS_NULL_PTR == pstDbgPkt)
    {
        return ;
    }

    /*调用CDS DEBUG数据接收接口*/
    CDS_LTE_RecvDbgData(pstDbgPkt);
    return;
}


/*****************************************************************************
 函 数 名  : CDS_RxDataFromImsNIC
 功能描述  : CDS从IMS虚拟网卡接收数据
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_RxDataFromImsNIC(const VOS_UINT8 *pData, VOS_UINT16 usLen,MODEM_ID_ENUM_UINT16 enModemId)
{
    CDS_ENTITY_STRU             *pstCdsEntity;
    TTF_MEM_ST                  *pstTtfPkt;
    VOS_INT32                    lLock;

    CDS_DBG_IMS_UL_RX_FUN_CALL_NUM(1);

    /*入参判断*/
    if (VOS_NULL_PTR == pData)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "CDS_RxPktFromImsNIC:Input Para is NULL");
        CDS_PRINT_ERROR(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        CDS_DBG_IMS_UL_RX_FUN_PARA_ERR(1);
        return PS_FAIL;
    }

    if ((0 == usLen) || (usLen > ETH_MAX_MTU))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RxPktFromImsNIC ; Packet Length Error.",usLen);
        CDS_PRINT_ERROR1(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_PKT_LEN_ERROR,usLen);
        CDS_DBG_IMS_UL_RX_FUN_PARA_ERR(1);
        return PS_FAIL;
    }

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RxPktFromImsNIC ; Modem ID Error.",enModemId);
        CDS_PRINT_ERROR1(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_GET_ENTITY_FAIL,enModemId);
        CDS_DBG_IMS_UL_RX_FUN_PARA_ERR(1);
        return PS_FAIL;
    }

    CDS_DBG_IMS_UL_RX_NIC_PKT_NUM(1);

    /*申请TTF内存,并将其拷贝到TTF内存中*/
    pstTtfPkt = CDS_AllocTtfMem(usLen);
    if (VOS_NULL_PTR == pstTtfPkt)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RxDataFromImsNIC: Alloc Mem Fail.");
        CDS_PRINT_ERROR(CDS_RxDataFromImsNIC_ENUM,CDS_PRINT_MEM_ALLOC_FAIL);
        CDS_DBG_IMS_UL_ALLOC_MEM_FAIL_NUM(1);
        return PS_FAIL;
    }
    PS_MEM_CPY(pstTtfPkt->pData,pData,usLen);

    /*入队*/
    lLock = VOS_SplIMP();
    if (PS_SUCC != LUP_EnQue(pstCdsEntity->pstIMSDataQue,pstTtfPkt))
    {
        VOS_Splx(lLock);
        CDS_DBG_IMS_UL_EN_QUE_FAIL_NUM(1);
        TTF_MemFree(UEPS_PID_CDS, pstTtfPkt);
        CDS_SendEventToCds(CDS_EVENT_UL_IMS_PROC);
        CDS_DBG_IMS_UL_TRIGGER_IMS_EVENT_NUM(1);
        return PS_FAIL;
    }
    VOS_Splx(lLock);
    CDS_DBG_IMS_UL_EN_QUE_SUCC_NUM(1);

    /*wakeup cds*/
    CDS_SendEventToCds(CDS_EVENT_UL_IMS_PROC);
    CDS_DBG_IMS_UL_TRIGGER_IMS_EVENT_NUM(1);
    return PS_SUCC;
}



/*****************************************************************************
 函 数 名  : CDS_UlProcImsData
 功能描述  : 处理上行IMS数据。默认按Modem0处理。
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_UlProcImsData(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32              ulCnt;
    TTF_MEM_ST             *pstIpPkt;
    VOS_INT32               lLock;
    CDS_ENTITY_STRU        *pstCdsEntity;
    IPF_RESULT_STRU        *pstIpfResult;
    VOS_UINT16              usResult;

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    for (ulCnt = 0; ulCnt < CDS_IMS_QUE_SIZE; ulCnt ++)
    {
        lLock = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(pstCdsEntity->pstIMSDataQue, (VOS_VOID **)&pstIpPkt))
        {
            VOS_Splx(lLock);
            break;
        }
        VOS_Splx(lLock);

        /*上行软过滤*/
        usResult = 0;
        if (PS_SUCC != CDS_IpSoftFilter(pstIpPkt, &usResult,pstCdsEntity))
        {
            TTF_MemFree(UEPS_PID_CDS, pstIpPkt);
            CDS_DBG_IMS_UL_SOFT_FILTER_FAIL_NUM(1);
            continue;
        }

        /*将过滤结果存到TTF中*/
        pstIpfResult = (IPF_RESULT_STRU *)((VOS_UINT32)&usResult);
        CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstIpPkt, usResult, enModemId, pstIpfResult->usBearedId);

        pstIpPkt->ucReserve = CDS_JudgIpPktType((VOS_UINT8)pstIpfResult->usBearedId,pstCdsEntity,pstIpPkt);
        CDS_PRINT_INFO2(CDS_UlProcImsData_ENUM, CDS_PRINT_TYPE, pstIpPkt->ucReserve,pstIpPkt->usUsed);       
        
        CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt);
        CDS_DBG_IMS_UL_IP_PKT_HOOK(pstIpPkt); /*鈎包*/

        /*发送到空口*/
        CDS_UlDispatchDataByRanMode(pstCdsEntity,pstIpPkt);
        CDS_DBG_IMS_UL_SEND_PKT_TO_RAN_NUM(1);

    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_IsNdClientPkt
 功能描述  : 判断下行数据包是否是NDCLIENT数据包.
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CDS_IsNdClientPkt(const TTF_MEM_ST *pstIpPkt)
{
    CDS_IP_DATA_INFO_STRU       stIpv6Info = {0};
    ICMP_HDR_STRU              *pstIcmpHdr;

    /*非IPv6数据包*/
    if (IP_VERSION_V6 != IP_GET_VERSION(pstIpPkt->pData))
    {
        return PS_FALSE;
    }

    /*解析IPv6数据包*/
    CDS_DecodeIpv6Packet(pstIpPkt, &stIpv6Info);

    /*NextHdr不是ICMPv6*/
    if (IPV6_NEXTHDR_ICMP != stIpv6Info.ucNextHdr)
    {
        return PS_FALSE;
    }

    /*IP分片*/
    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != stIpv6Info.ucIpSegType)
    {
        return PS_FALSE;
    }

    /*偏移到ICMPv6头,判断Type范围*/
    pstIcmpHdr = (ICMP_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + stIpv6Info.ulHdrLen));
    if ((ICMPV6_TYPE_RS <= pstIcmpHdr->ucType)
        && (ICMPV6_TYPE_REDIRECT >= pstIcmpHdr->ucType))
    {
        return PS_TRUE;
    }

    return  PS_FALSE;
}

/*****************************************************************************
 函 数 名  : CDS_SendNdDataIndMsg
 功能描述  : 发送ND数据包到NDCLIENT处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_SendNdDataIndMsg(TTF_MEM_ST *pstNdPkt, VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_NDCLIENT_ND_DATA_IND_STRU  *pstDataInd;
    VOS_UINT32                      ulMsgLen;
    VOS_UINT32                      ulPktLen;

    CDS_ASSERT(VOS_NULL_PTR != pstNdPkt);
    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Enter CDS_SendNdDataIndMsg.ucRabid=",ucRabId);
    CDS_PRINT_INFO1(CDS_SendNdDataIndMsg_ENUM, CDS_PRINT_RABID, ucRabId);

    /*申请消息内存*/
    ulPktLen = TTF_MemGetLen(UEPS_PID_CDS,pstNdPkt);
    ulMsgLen = sizeof(CDS_NDCLIENT_ND_DATA_IND_STRU) + ulPktLen;
    pstDataInd = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstDataInd)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_SendNdDataIndMsg : Alloc Msg Fail. Size=",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_SendNdDataIndMsg_ENUM,CDS_PRINT_ALLOC_MEM_FAIL_HDRLEN,ulMsgLen);
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstDataInd,UEPS_PID_NDCLIENT);
    pstDataInd->enMsgId   = ID_CDS_NDCLIENT_ND_DATA_IND;
    pstDataInd->enModemId = pstCdsEntity->usModemId;
    pstDataInd->ucRabId   = ucRabId;
    pstDataInd->ulLen     = ulPktLen;

    /*内存拷贝*/
    if (PS_SUCC != TTF_MemGetHeadData(UEPS_PID_CDS,
                                      pstNdPkt,
                                      pstDataInd->aucData,
                                      (VOS_UINT16)ulPktLen))
    {
        /*lint -e961*/
        PS_FREE_MSG(UEPS_PID_CDS, pstDataInd);
        /*lint +e961*/
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_SendNdDataIndMsg : TTF_MemGetHeadData Error.");
        CDS_PRINT_ERROR(CDS_SendNdDataIndMsg_ENUM,CDS_PRINT_MEM_GET_HEAD_DATA);
        return ;
    }

    /*发送消息*/
    CDS_SEND_MSG(pstDataInd);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_SendNdDataIndMsg Succ.");
    CDS_PRINT_INFO(CDS_SendNdDataIndMsg_ENUM, LL2_FUNCTION_EXIT);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_IsImsBearer
 功能描述  : 判断RabId是否是IMS承载
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CDS_IsImsBearer(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32      ulCnt;

    /*遍历*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        if (ucRabId == pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 函 数 名  : CDS_IsImsDefBearer
 功能描述  : 判断RabId是否是IMS缺省承载
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CDS_IsImsDefBearer(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32      ulCnt;

    /*遍历*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        if ((IMSA_CDS_IMS_BEARER_TYPE_SIGNAL == pstCdsEntity->astImsBearerInfo[ulCnt].enBearerType)
            && (ucRabId == pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 函 数 名  : CDS_ImsSaveFragmentPktInfo
 功能描述  : CDS IMS 保存下行分片包信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年02月07日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ImsSaveFragmentPktInfo(const CDS_IP_DATA_INFO_STRU *pstIpPktInfo)
{
    CDS_IMS_DL_FRAGMENT_BUFF_STRU   *pstImsFragBuff;

    if (VOS_NULL_PTR == pstIpPktInfo)
    {
        return;
    }

    pstImsFragBuff = CDS_IMS_GET_DL_FRAGMENT_BUFF();

    PS_MEM_CPY(&(pstImsFragBuff->astIpPktInfo[pstImsFragBuff->ulIndex]),
               pstIpPktInfo,
               sizeof(CDS_IP_DATA_INFO_STRU));

    pstImsFragBuff->ulIndex = TTF_MOD_ADD(pstImsFragBuff->ulIndex,1,CDS_IMS_DL_FRAGMENT_BUFF_SIZE);

    return ;
}

/*****************************************************************************
 函 数 名  : CDS_ImsGetDestPortFromFragBuff
 功能描述  : CDS IMS 从分片包缓存信息中获取目的端口号
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年02月07日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_ImsGetDestPortFromFragBuff(VOS_UINT16 *pusDestPort,
                                                    const CDS_IP_DATA_INFO_STRU *pstIpPktInfo)
{
    VOS_UINT32                       ulCnt;
    CDS_IP_DATA_INFO_STRU           *pstBuffPktInfo;
    CDS_IMS_DL_FRAGMENT_BUFF_STRU   *pstImsFragBuff;

    pstImsFragBuff = CDS_IMS_GET_DL_FRAGMENT_BUFF();

    for(ulCnt = 0; ulCnt < CDS_IMS_DL_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstBuffPktInfo = &(pstImsFragBuff->astIpPktInfo[ulCnt]);

        if ((PS_TRUE == CDS_IsIpv4FragInfoEq(pstIpPktInfo, pstBuffPktInfo))
            || (PS_TRUE == CDS_IsIpv6FragInfoEq(pstIpPktInfo, pstBuffPktInfo)))
        {
            *pusDestPort = pstBuffPktInfo->usDestPort;
            return PS_SUCC;
        }
    }

    return PS_FAIL;
}

/*****************************************************************************
 函 数 名  : CDS_ImsGetPktDestPort
 功能描述  : CDS IMS 获取数据包目的端口号
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年02月07日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_ImsGetPktDestPort(VOS_UINT16 *pusDestPort,
                                        const CDS_IP_DATA_INFO_STRU *pstIpPktInfo)
{
    /*非IP分片包*/
    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT == pstIpPktInfo->ucIpSegType)
    {
        *pusDestPort = pstIpPktInfo->usDestPort;
        return PS_SUCC;
    }

    /*头分片，保存IP包信息*/
    if (CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD == pstIpPktInfo->ucIpSegType)
    {
        *pusDestPort = pstIpPktInfo->usDestPort;
        CDS_ImsSaveFragmentPktInfo(pstIpPktInfo);
        return PS_SUCC;
    }

    /*中间分片和尾分片，从缓存队列中查找目的端口号*/
    if (PS_SUCC != CDS_ImsGetDestPortFromFragBuff(pusDestPort,pstIpPktInfo))
    {
        *pusDestPort = 0;
        return PS_FAIL;
    }

    /*异常保护,端口号不能为0*/
    if (0 == *pusDestPort)
    {
        return PS_FAIL;
    }

    return PS_SUCC;

}

/*****************************************************************************
 函 数 名  : CDS_IsImsUtPkt
 功能描述  : 判断是否是IMS UT数据包，如果是则发送到A核.
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年01月16日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_IsImsUtPkt(const TTF_MEM_ST *pstIpPkt,const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_IP_DATA_INFO_STRU       stIpPktInfo = {0};
    VOS_UINT16                  ulDestPort  = 0;

    /*解析数据包*/
    if (IP_VERSION_V4 == IP_GET_VERSION(pstIpPkt->pData))
    {
        CDS_DecodeIpv4Packet(pstIpPkt, &stIpPktInfo);
    }
    else if (IP_VERSION_V6 == IP_GET_VERSION(pstIpPkt->pData))
    {
        CDS_DecodeIpv6Packet(pstIpPkt, &stIpPktInfo);
    }
    else
    {
        return PS_FALSE;
    }

    /*启用IPSEC协议*/
    if ((0 != stIpPktInfo.ulAhSpi) || (0 != stIpPktInfo.ulEspSpi))
    {
        return PS_FALSE;
    }

    /*获取目的端口号失败，发送到IMS协议栈处理*/
    if (PS_SUCC != CDS_ImsGetPktDestPort(&ulDestPort, &stIpPktInfo))
    {
        CDS_DBG_IMS_DL_GET_DEST_PORT_FAIL_NUM(1);
        return PS_FALSE;
    }

    /*没有目的端口号*/
    if ((ulDestPort >= pstCdsEntity->stImsPortInfo.usMinImsPort)
        && (ulDestPort <= pstCdsEntity->stImsPortInfo.usMaxImsPort))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : CDS_DlProcImsData
 功能描述  : 处理下行VoLte数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DlProcImsUtPkt(CDS_IMS_SDU_STRU *pstImsSdu, const CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32              ulResult;
    VOS_UINT8               ucDeftRabId;
    TTF_MEM_ST             *pstIpPkt;

    CDS_DBG_IMS_DL_RX_IMS_Ut_PKT_NUM(1);

    if (MMC_CDS_MODE_GU == pstCdsEntity->enRanMode)
    {
        ulResult = CDS_GUGetDefaultRabId(pstImsSdu->ucRabId,&ucDeftRabId,pstCdsEntity->usModemId);
    }
    else
    {
        ulResult = CDS_ERABM_GetDefaultEpsbId(pstImsSdu->ucDrbId,&ucDeftRabId);
    }

    if (PS_SUCC != ulResult)
    {
        TTF_MemFree(UEPS_PID_CDS, pstImsSdu->pstSdu);
        CDS_DBG_IMS_DL_Ut_PKT_PROC_ERR_NUM(1);
        return;
    }

    /*保存必要信息*/
    pstIpPkt = pstImsSdu->pstSdu;
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,
                                         pstImsSdu->ulSduLen,
                                         pstCdsEntity->usModemId,
                                         ucDeftRabId);

    /*入队*/
    if (PS_SUCC != CDS_RxDlSdu(pstIpPkt))
    {
        CDS_DBG_DL_LTE_ENQUE_FAIL_NUM(1);
        CDS_DBG_IMS_DL_Ut_PKT_PROC_ERR_NUM(1);
        return;
    }

    CDS_DBG_DL_LTE_ENQUE_SUCC_NUM(1);
    CDS_DBG_IMS_DL_Ut_PKT_PROC_SUCC_NUM(1);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_DlProcImsData
 功能描述  : 处理下行VoLte数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DlProcImsData(CDS_IMS_SDU_STRU *pstImsSdu, const CDS_ENTITY_STRU *pstCdsEntity)
{
    TTF_MEM_ST          *pstImsPkt;

    CDS_DBG_IMS_DL_RX_IMS_PKT_NUM(1);

    /*如果是非连续内存，则拷贝到连续内存上；否则继续使用原来的内存*/
    if (VOS_NULL_PTR == pstImsSdu->pstSdu->pNext)
    {
        pstImsPkt = pstImsSdu->pstSdu;
    }
    else
    {
        pstImsPkt = CDS_TtfMemCopyAlloc(pstImsSdu->pstSdu,pstImsSdu->ulSduLen);
        TTF_MemFree(UEPS_PID_CDS,pstImsSdu->pstSdu);
    }

    if (VOS_NULL_PTR == pstImsPkt)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_DlProcImsData : Copy Alloc Ttf Mem Fail.Len=",pstImsSdu->ulSduLen);
        CDS_PRINT_ERROR1(CDS_DlProcImsData_ENUM,LL2_PTR_NULL,pstImsSdu->ulSduLen);
        CDS_DBG_IMS_DL_ALLOC_MEM_FAIL_NUM(1);
        return ;
    }

    /*保存必要信息*/
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstImsPkt,
                                         pstImsPkt->usUsed,
                                         pstCdsEntity->usModemId,
                                         pstImsSdu->ucRabId);

    CDS_DBG_IMS_DL_IP_PKT_HOOK(pstImsPkt);
    CDS_DBG_DL_REC_IP_PKT_INFO(pstImsPkt);

    /*NDCLIENT数据包，发送到NDCLIENT*/
    if ((PS_TRUE == CDS_IsImsDefBearer(pstImsSdu->ucRabId,pstCdsEntity))
         && (PS_TRUE == CDS_IsNdClientPkt(pstImsPkt)))
    {
        CDS_SendNdDataIndMsg(pstImsPkt,pstImsSdu->ucRabId,pstCdsEntity);
        TTF_MemFree(UEPS_PID_CDS,pstImsPkt);
        CDS_DBG_IMS_DL_RX_ND_PKT_NUM(1);
        return;
    }
    else if (PS_TRUE == CDS_IsImsUtPkt(pstImsPkt, pstCdsEntity))
    {
        /*更新内存指针*/
        pstImsSdu->pstSdu = pstImsPkt;
        CDS_DlProcImsUtPkt(pstImsSdu,pstCdsEntity);
        return;
    }

    /*发送到IMS NIC*/
    if (PS_SUCC != IMS_NIC_DlDataRcv(pstImsPkt->pData,
                                     pstImsPkt->usUsed,
                                     pstCdsEntity->usModemId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstImsPkt);
        CDS_DBG_IMS_DL_SEND_TO_NIC_FAIL_NUM(1);
        return;
    }

    /*释放内存*/
    TTF_MemFree(UEPS_PID_CDS,pstImsPkt);
    CDS_DBG_IMS_DL_SEND_TO_NIC_SUCC_NUM(1);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_ProcSetImsBearerReqMsg
 功能描述  : 处理IMSA 设置承载请求消息.默认按Modem0处理。
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_SendImsaSetImsBearerCnfMsg(VOS_UINT32 ulResult)
{
    IMSA_CDS_SET_IMS_BEARER_CNF_STRU   *pstCnfMsg;
    VOS_UINT32                          ulMsgLen;

    CDS_INFO_LOG1(UEPS_PID_CDS,"Enter CDS_SendImsaSetImsBearerCnfMsg. ulResult=",ulResult);
    CDS_PRINT_INFO1(CDS_SendImsaSetImsBearerCnfMsg_ENUM, CDS_PRINT_CNF_RESULT, ulResult);

    ulMsgLen = sizeof(IMSA_CDS_SET_IMS_BEARER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_SendImsaSetImsBearerCnfMsg : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_SendImsaSetImsBearerCnfMsg_ENUM,CDS_PRINT_ALLOC_MEM_FAIL_HDRLEN,ulMsgLen);
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstCnfMsg,PS_PID_IMSA);
    pstCnfMsg->ulMsgId  = ID_IMSA_CDS_SET_IMS_BEARER_CNF;
    pstCnfMsg->ulResult = ulResult;

    /*发送消息*/
    CDS_SEND_MSG(pstCnfMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_SendImsaSetImsBearerCnfMsg Succ.");
    CDS_PRINT_INFO(CDS_SendImsaSetImsBearerCnfMsg_ENUM, LL2_FUNCTION_EXIT);

    return;
}
/*****************************************************************************
 函 数 名  : CDS_ProcSetImsBearerReqMsg
 功能描述  : 处理IMSA 设置承载请求消息.默认按Modem0处理。
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_ImsaSetImsBearerReqMsgProc(MsgBlock *pstMsg)
{
    IMSA_CDS_SET_IMS_BEARER_REQ_STRU   *pstReqMsg;
    CDS_ENTITY_STRU                    *pstCdsEntity;
    VOS_UINT32                         ulLoop = 0;
    VOS_UINT8                          ucEpsbId;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ImsaSetImsBearerReqMsgProc.");
    CDS_PRINT_INFO(CDS_ImsaSetImsBearerReqMsgProc_ENUM, LL2_FUNCTION_ENTER);

    pstReqMsg = (IMSA_CDS_SET_IMS_BEARER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->ulImsBearerNum > IMSA_CDS_MAX_IMS_BEARER_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ImsaSetImsBearerReqMsgProc : IMS Bearer Number Error.",pstReqMsg->ulImsBearerNum);
        CDS_PRINT_ERROR1(CDS_ImsaSetImsBearerReqMsgProc_ENUM,CDS_PRINT_IMS_BEARER_NUM_ERR,pstReqMsg->ulImsBearerNum);
        CDS_SendImsaSetImsBearerCnfMsg(PS_FAIL);
        return;
    }

    /*默认按MODEM_0处理*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ImsaSetImsBearerReqMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ImsaSetImsBearerReqMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        CDS_SendImsaSetImsBearerCnfMsg(PS_FAIL);
        return;
    }

    /*注册IMS NIC回调函数*/
    if (PS_SUCC != IMS_NIC_RegUlDataSendCb((IMS_NIC_SEND_UL_DATA_FUNC)CDS_RxDataFromImsNIC,
                                            pstCdsEntity->usModemId))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ImsaSetImsBearerReqMsgProc : IMS_NIC_RegUlDataSendCb Fail.");
        CDS_PRINT_ERROR(CDS_ImsaSetImsBearerReqMsgProc_ENUM,LL2_FUNCTION_RETURN_ERROR);
        CDS_SendImsaSetImsBearerCnfMsg(PS_FAIL);
        return;
    }

    /*更新CDS实体信息*/
    pstCdsEntity->ulImsBearerNum = pstReqMsg->ulImsBearerNum;
    PS_MEM_CPY(pstCdsEntity->astImsBearerInfo,
               pstReqMsg->astImsBearerArray,
               pstReqMsg->ulImsBearerNum * sizeof(IMSA_CDS_IMS_BEARER_STRU));
    for(ulLoop = 0; ulLoop < pstCdsEntity->ulImsBearerNum; ulLoop ++)
    {
        ucEpsbId = pstCdsEntity->astImsBearerInfo[ulLoop].ucEpsbId;
        CDS_LPDCP_SetImsBearer(ucEpsbId);
    }

    pstCdsEntity->stImsPortInfo.usMinImsPort = pstReqMsg->stImsPortInfo.usMinImsPort;
    pstCdsEntity->stImsPortInfo.usMaxImsPort = pstReqMsg->stImsPortInfo.usMaxImsPort;

    /*发送成功消息*/
    CDS_SendImsaSetImsBearerCnfMsg(PS_SUCC);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ImsaSetImsBearerReqMsgProc Succ.");
    CDS_PRINT_INFO(CDS_ImsaSetImsBearerReqMsgProc_ENUM, LL2_FUNCTION_EXIT);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_IMSA_MsgProc
 功能描述  : IMSA消息处理函数。
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_IMSA_MsgProc(MsgBlock  *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_IMSA_MsgProc : Input NULL PTR.");
        CDS_PRINT_INFO(CDS_IMSA_MsgProc_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_IMSA_CDS_SET_IMS_BEARER_REQ:
        CDS_ImsaSetImsBearerReqMsgProc(pstMsg);
        break;

    default:
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_IMSA_MsgProc: Msg Id Error.MsgID=",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_INFO1(CDS_IMSA_MsgProc_ENUM, CDS_PRINT_MSG_ID_ERROR, TTF_GET_MSG_NAME(pstMsg));
        break;

    }

    return;

}
/*****************************************************************************
 函 数 名  : CDS_JudgIpPktType
 功能描述  : 根据IP包大小判断类型
 输入参数  : VOS_UINT8 ucRabId pstCdsEntity pstIpPkt
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年08月21日
      作    者   : c00253308
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CDS_JudgIpPktType(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt)
{
    VOS_UINT32      ulCnt;

    /*遍历*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        if((ucRabId == pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId)
                    &&(IMSA_CDS_IMS_BEARER_TYPE_MEDIA == pstCdsEntity->astImsBearerInfo[ulCnt].enBearerType))
        {
            if (pstIpPkt->usUsed > CDS_IMS_MIN_SPEECH_FRM)
            {
                return IP_PKT_TYPE_IMS_SPEECH;
            }
            else
            {
                return IP_PKT_TYPE_IMS_SILENCE;
            }
        }
    }
    return IP_PKT_TYPE_NORMAL;
}
/*****************************************************************************
 函 数 名  : CDS_PdcpGetImsBeareByRabId
 功能描述  : 判断RabId是否是IMS承载,供PDCP在建立下行实体时调用
 输入参数  : ucRabId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年12月10日
      作    者   : c00253308
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CDS_PdcpGetImsBeareByRabId(VOS_UINT8 ucRabId)
{
    VOS_UINT32      ulCnt;
    CDS_ENTITY_STRU *pstCdsEntity;
    
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);

    /*遍历*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        if (ucRabId == pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

