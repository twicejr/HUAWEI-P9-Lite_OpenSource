


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmEsmMsgProc.h"
#include  "NasERabmEmmMsgProc.h"
#include  "NasERabmTest.h"
#include  "LUPZeroCopy.h"
#include  "NasIpInterface.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmPublic.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMAPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMAPPMSGPROC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*上行数据包匹配控制开关:如果当前只有一条承载激活，且没有上行TFT
  g_ulSrcIpMatchSwitch = 1,则进行源IP的匹配
  g_ulSrcIpMatchSwitch = 0,则不进行源IP匹配*/
VOS_UINT32                              g_ulSrcIpMatchSwitch = 1;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ERABM_AppMsgDistr
 Description     : APP消息分发处理函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangqianhui 00135146      2009-3-7  Draft Enact
    2.lihong 00150010           2010-4-12 Modify

*****************************************************************************/
VOS_VOID  NAS_ERABM_AppMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU            *pRrcMsg;

    pRrcMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_AppMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_AppMsgDistr_ENUM, LNAS_ENTRY);


    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_AppMsgDistr:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_AppMsgDistr_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    /*根据消息名，调用相应的消息处理函数*/
    switch (pRrcMsg->ulMsgName)
    {
        /*如果收到的是APP_ERABM_DATA_TRANS_REQ消息，调用NAS_ERABM_RcvRabmAppDataReq函数*/
        case ID_APP_ERABM_DATA_TRANS_REQ:
            NAS_ERABM_RcvRabmAppDataReq((APP_ERABM_DATA_TRANS_REQ_STRU *) pRcvMsg);
            break;
        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_AppMsgDistr:WARNING:APP->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_AppMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }

}

/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ERABM_RcvRabmAppDataReq( const APP_ERABM_DATA_TRANS_REQ_STRU *pRcvMsg )
{
    NAS_ERABM_APP_DATA_TRANS_SET_RESLT_STRU             stAppRabmDataTrans;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmAppDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmAppDataReq_ENUM, LNAS_ENTRY);

    if ( (NAS_ERABM_OP_TRUE == pRcvMsg->stDataTransInfo.bitOpIpv4)
          || (NAS_ERABM_OP_TRUE == pRcvMsg->stDataTransInfo.bitOpIpv6))
    {
        NAS_ERABM_MEM_CPY_S((NAS_ERABM_GetAppDataInfoAddr()),
                            sizeof(APP_ERABM_DATA_TRANS_INFO_STRU),
                            &(pRcvMsg->stDataTransInfo), 
                            sizeof(APP_ERABM_DATA_TRANS_INFO_STRU));

        stAppRabmDataTrans.enSetRslt = APP_ERABM_DATA_TRANS_SET_SUCCESS;
    }
    else
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmAppDataReq:WARNING:APP->RABM IP Bit error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmAppDataReq_ENUM, LNAS_ERABM_IPBitError);

        stAppRabmDataTrans.enSetRslt = APP_ERABM_DATA_TRANS_SET_FAIL;
    }

    stAppRabmDataTrans.ulMsgId = ID_APP_ERABM_DATA_TRANS_CNF;
    stAppRabmDataTrans.usOriginalId = pRcvMsg->usTerminalId;
    stAppRabmDataTrans.usTerminalId = pRcvMsg->usOriginalId;
    stAppRabmDataTrans.ulSn = pRcvMsg->ulSN;

    NAS_ERABM_SndRabmAppDataCnf(&stAppRabmDataTrans);
}


 VOS_VOID  NAS_ERABM_SndRabmAppDataCnf( const NAS_ERABM_APP_DATA_TRANS_SET_RESLT_STRU
                                                      *pstRabmAppDataTrans )
{
    APP_ERABM_DATA_TRANS_CNF_STRU        *pstRabmAppDataCnf = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_SndRabmAppDataCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_SndRabmAppDataCnf_ENUM, LNAS_ENTRY);

    /*入口参数检查*/
    if ((APP_ERABM_DATA_TRANS_SET_SUCCESS != pstRabmAppDataTrans->enSetRslt)
         &&(APP_ERABM_DATA_TRANS_SET_FAIL != pstRabmAppDataTrans->enSetRslt))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmAppDataCnf:ERROR: Input para error!");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_SndRabmAppDataCnf_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*分配空间和检测是否分配成功*/
    pstRabmAppDataCnf = (VOS_VOID *)NAS_ERABM_ALLOC_MSG(
                                        sizeof(APP_ERABM_DATA_TRANS_CNF_STRU));
    if ( VOS_NULL_PTR == pstRabmAppDataCnf )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmAppDataCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /*清空*/
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_MSG_ENTITY(pstRabmAppDataCnf), 
                        NAS_ERABM_GET_MSG_LENGTH(pstRabmAppDataCnf),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstRabmAppDataCnf));

    /*填写消息头*/
    NAS_ERABM_WRITE_APP_MSG_HEAD(pstRabmAppDataCnf, pstRabmAppDataTrans->ulMsgId,\
           pstRabmAppDataTrans->usOriginalId,pstRabmAppDataTrans->usTerminalId,\
                              pstRabmAppDataTrans->ulSn);
    /*填写消息实体*/
    pstRabmAppDataCnf->enSetOpRslt  = pstRabmAppDataTrans->enSetRslt;

    /* 调用消息发送函数 */
    NAS_ERABM_SND_MSG(pstRabmAppDataCnf);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_AppAssignMidHeader
 Description     : 分配APP消息头APP_PS_MSG_HEADER中的MID参数
 Input           : VOS_UINT32  *pulOriMid,
                    VOS_UINT32 *pulTerMid
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-4-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_AppAssignMidHeader
(
    VOS_UINT16                         *pusOriMid,
    VOS_UINT16                         *pusTerMid
)
{
    /*初始化MID参数值*/
    *pusOriMid = UE_APP_SUBSYS_ID;  /*FFS*/
    *pusTerMid = UE_MODULE_RABM_ID;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_IsExistUplinkPfinTft
 Description     : 判断承载的TFT中是否存在上行的PacketFilter
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu 00143951      2010-5-14  Draft Enact

*****************************************************************************/
PS_BOOL_ENUM_UINT8  NAS_ERABM_IsExistUplinkPfinTft( VOS_UINT32 ulEpsbId)
{
    VOS_UINT32                          ulTftPfCnt = NAS_ERABM_NULL;
    ESM_ERABM_TFT_PF_STRU               *pstTftPf   = VOS_NULL_PTR;

    for(ulTftPfCnt = 0; ulTftPfCnt < NAS_ERABM_GetEpsbTftPfNum(ulEpsbId); ulTftPfCnt++)
    {
        pstTftPf = NAS_ERABM_GetEpsbTftAddr(ulEpsbId, ulTftPfCnt);

        if ((APP_ESM_TRANSFER_DIRECTION_UPLINK == pstTftPf->enDirection)
         || (APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK == pstTftPf->enDirection))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SaveIpv4SegDataInfo
 Description     : 保存分片包信息(包括identifier,源和目的IP地址)
 Input           : NAS_ERABM_IPV4_HEADER_STRU   *pstIpv4HeaderInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangqianhui 00135146    2010-11-27    Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SaveIpv4SegDataInfo
(
    const NAS_ERABM_IPV4_HEADER_STRU   *pstIpv4HeaderInfo,
    VOS_UINT8                           ucBearerId
)
{
    static VOS_UINT16                   usIndex         = NAS_ERABM_NULL;
    VOS_UINT32                          ulLoop          = NAS_ERABM_NULL;
    NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU  *pstSegDataInfo  = VOS_NULL_PTR;

    /* 遍历分片信息数组，查看是否分片信息已存在，若存在则直接返回 */
    for (ulLoop = NAS_ERABM_NULL; ulLoop < NAS_ERABM_GetIpv4SegBuffItemNum(); ulLoop++)
    {
        pstSegDataInfo = NAS_ERABM_GetIpv4SegBuffItemAddr(ulLoop);
        if ((pstIpv4HeaderInfo->ulIdentifier == pstSegDataInfo->ulIdentifier)
           && (0 == NAS_ERABM_MEM_CMP(  pstIpv4HeaderInfo->aucSrcIpV4Addr,
                                        pstSegDataInfo->aucSrcIpV4Addr,
                                        NAS_ERABM_IPV4_ADDR_LEN))
           && (0 == NAS_ERABM_MEM_CMP(  pstIpv4HeaderInfo->aucDesIpV4Addr,
                                        pstSegDataInfo->aucDesIpV4Addr,
                                        NAS_ERABM_IPV4_ADDR_LEN)))
        {
            pstSegDataInfo->ucBearerId = ucBearerId;
            return;
        }
    }

    /* 存储分片信息 */
    pstSegDataInfo = NAS_ERABM_GetIpv4SegBuffItemAddr(usIndex);
    pstSegDataInfo->ulIdentifier    = pstIpv4HeaderInfo->ulIdentifier;
    NAS_ERABM_MEM_CPY_S(  pstSegDataInfo->aucSrcIpV4Addr,
                        NAS_ERABM_IPV4_ADDR_LEN,
                        pstIpv4HeaderInfo->aucSrcIpV4Addr,
                        NAS_ERABM_IPV4_ADDR_LEN);
    NAS_ERABM_MEM_CPY_S(  pstSegDataInfo->aucDesIpV4Addr,
                        NAS_ERABM_IPV4_ADDR_LEN,
                        pstIpv4HeaderInfo->aucDesIpV4Addr,
                        NAS_ERABM_IPV4_ADDR_LEN);
    pstSegDataInfo->ucBearerId = ucBearerId;

    usIndex = (usIndex + 1) % NAS_ERABM_MAX_SEG_BUFF_ITEM_NUM;

    if (NAS_ERABM_GetIpv4SegBuffItemNum() < NAS_ERABM_MAX_SEG_BUFF_ITEM_NUM)
    {
        NAS_ERABM_AddSelfIpv4SegBuffItemNum();
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_DecodeIpV4Data
 Description     : 将IPv4包进行大小端转换
 Input           : VOS_UINT32 *pulSrcData
                   VOS_UINT32 *puLDestData
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00135146      2009-7-27  Draft Enact

*****************************************************************************/

VOS_VOID NAS_ERABM_DecodeIpV4Data
(
    VOS_UINT8 *pucSrcData,
    NAS_ERABM_IPV4_HEADER_STRU *pstDestData
)
{
    VOS_UINT8                            *pSrcData    = pucSrcData;
    VOS_UINT32                            ulIndex     = NAS_ERABM_NULL;
    NAS_ERABM_IPV4_HEADER_STRU           *pstIpv4Data = pstDestData;

    /* 跳转Identifier的起始位置 */
    ulIndex = ulIndex + 4;

    pstIpv4Data->ulIdentifier = (pSrcData[ulIndex] << NAS_ERABM_MOVEMENT_8_BITS)\
                                | pSrcData[ulIndex+1];

    /* 跳转source ip address 的起始位置 */
    ulIndex = ulIndex + 8;
    NAS_ERABM_MEM_CPY_S(  pstIpv4Data->aucSrcIpV4Addr,
                        NAS_ERABM_IPV4_ADDR_LEN,
                        &pSrcData[ulIndex],
                        NAS_ERABM_IPV4_ADDR_LEN);

    /* 跳转destination ip address 的起始位置 */
    ulIndex = ulIndex + 4;
    NAS_ERABM_MEM_CPY_S(  pstIpv4Data->aucDesIpV4Addr,
                        NAS_ERABM_IPV4_ADDR_LEN,
                        &pSrcData[ulIndex],
                        NAS_ERABM_IPV4_ADDR_LEN);
}


/*****************************************************************************
 Function Name   : NAS_ERABM_DecodeIpV6Data
 Description     : 将IPv6包进行大小端转换
 Input           : (VOS_VOID *)pstSdu->pData
                   pulIpv6Data
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00135146      2009-7-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_DecodeIpV6Data
(
    VOS_UINT8 *pucSrcData,
    NAS_ERABM_IPV6_HEADER_STRU *pstDestData
)
{


    VOS_UINT8                            *pSrcData    = pucSrcData;
    VOS_UINT32                            ulIndex     = NAS_ERABM_NULL;
    NAS_ERABM_IPV6_HEADER_STRU           *pstIpv6Data = pstDestData;

    /* 调转到IPV6源地址起始位置 */
    ulIndex = ulIndex + 8;

    pSrcData = pSrcData + ulIndex;
    NAS_ERABM_MEM_CPY_S(pstIpv6Data->aucSrcIpV6Addr, APP_MAX_IPV6_ADDR_LEN, pSrcData, APP_MAX_IPV6_ADDR_LEN);
}
/*lint +e961*/
/*lint +e960*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

