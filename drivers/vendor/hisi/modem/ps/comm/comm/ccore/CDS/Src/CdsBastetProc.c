/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsBastetProc.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月30日
  最近修改   :
  功能描述   : 实现CDS BASTET相关功能
  函数列表   :

  修改历史   :
  1.日    期   : 2014年05月30日
    作    者   : d00173029
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
#include "CdsBastetProc.h"
#include "CdsUlProc.h"
#include "CdsDlProc.h"
#include "CdsMsgProc.h"
#include "CdsDebug.h"
#include "CdsIpfCtrl.h"
#include "CdsSoftFilter.h"
#include "QosFcCommon.h"
#include "NVIM_Interface.h"


/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_BST_PROC_C
/*lint +e767*/

#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
/*****************************************************************************
  1 宏定义
*****************************************************************************/
/*Only IP Head + SrcPort + DstPort Length is Enough to judge Protol*/
#define CDS_BST_IP_PORTS_LEN        ( 0x04U )
#define CDS_BST_TCP_STD_LEN         ( 20U )
#define CDS_GetBastetEntity()       ( &g_CdsBstEntity )
#define CDS_GetUsedModemId()        ( g_CdsBstEntity.usModemId )

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/
#ifdef BST_MODEM_SELF
extern VOS_VOID DSPP_TEST_EMAIL( VOS_UINT32 ulIpAddr );
#endif
/******************************************************************************
   3 私有定义
******************************************************************************/
VOS_VOID    CDS_ConfigBastetNetState    (
    const BST_CDS_NET_DEVICE_STATE_STRU    *pstNetMsg );

VOS_VOID    CDS_ConfigBastetRxEnable  (
    const BST_CDS_TX_RX_RPT_ENABLE_STRU    *pstFlagMsg );

VOS_VOID    CDS_ConfigBastetTxEnable  (
    const BST_CDS_TX_RX_RPT_ENABLE_STRU    *pstFlagMsg );

VOS_VOID    CDS_BstHookPacket           (
    const VOS_UINT32                        ulType,
    const TTF_MEM_ST                       *pstIpPkt );

VOS_UINT32  CDS_FwProcBastetData        (
    const VOS_UINT8                        *pData,
    const VOS_UINT32                        ulLen );

VOS_UINT32  CDS_RxDataFromBastet        (
    const VOS_UINT8                        *pData,
    const VOS_UINT32                        ulLen,
    const VOS_UINT8                         ucFlg);

VOS_UINT32  CDS_RegBstDlRcvCB           (
    const BST_CDS_REG_RCV_CB_STRU          *pstRegDlRcvFunMsg );

VOS_UINT32 CDS_ConfigAcoreModemRabid    (
    const BST_CDS_NET_ACORE_MODEM_RABID_STRU *pstModemRabIdMsg );

/******************************************************************************
   4 全局变量定义
******************************************************************************/
CDS_BST_ENTITY_STRU g_CdsBstEntity          = { 0 };
/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : CDS_BST_MsgProc
 功能描述  : Bastet消息处理函数。
 输入参数  : MsgBlock  *pstMsg  消息公共头
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_BST_MsgProc(MsgBlock  *pstMsg)
{
    if ( VOS_NULL_PTR == pstMsg )
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_BST_MsgProc : Input NULL PTR.");
        CDS_PRINT_INFO(CDS_BST_MsgProc_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }
    CDS_INFO_LOG1( UEPS_PID_CDS, "CDS_BST_MsgProc : MsgId", TTF_GET_MSG_NAME(pstMsg) );
    CDS_PRINT_INFO1(CDS_BST_MsgProc_ENUM, CDS_PRINT_MSG_ID, TTF_GET_MSG_NAME(pstMsg));
    switch( TTF_GET_MSG_NAME(pstMsg) )
    {
        /* BASTET发给CDS的消息原语: 注册下行回调函数 */
        case ID_BST_CDS_REG_RCV_CB_REQ:
            CDS_RegBstDlRcvCB( (BST_CDS_REG_RCV_CB_STRU*)pstMsg );
            break;

        /* BASTET发给CDS的消息原语: ACORE使用的MODEM_RABID消息*/
        case ID_BST_CDS_NET_MODEM_RAB_IND:
            CDS_ConfigAcoreModemRabid( (const BST_CDS_NET_ACORE_MODEM_RABID_STRU *)
                                       pstMsg );
            break;

        /* BASTET发给CDS的消息原语: 当前NET_DEVICE状态 */
        case ID_BST_CDS_NET_DEVICE_UP_IND:
            CDS_ConfigBastetNetState( (BST_CDS_NET_DEVICE_STATE_STRU *)pstMsg );
            break;

        /* BASTET发给CDS的消息原语: 配置CDS是否发送TX_RX_IND消息 */
        case ID_BST_CDS_RX_RPT_CTRL_REQ:
            CDS_ConfigBastetRxEnable( (BST_CDS_TX_RX_RPT_ENABLE_STRU *)pstMsg );
            break;

        case ID_BST_CDS_TX_RPT_CTRL_REQ:
            CDS_ConfigBastetTxEnable( (BST_CDS_TX_RX_RPT_ENABLE_STRU *)pstMsg );
            break;

        default:
            CDS_INFO_LOG(UEPS_PID_CDS,"CDS_BST_MsgProc : Unknown Message.");
            CDS_PRINT_INFO(CDS_BST_MsgProc_ENUM, CDS_PRINT_MSG_NAME_ERROR);
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : CDS_BST_DecodeDl
 功能描述  : 解析下行IP包，获取目的端口号，协议类型信息
 输入参数  : TTF_MEM_ST *pstIpPkt TTF       格式数据包，调用者保证有效
 输出参数  : CDS_BST_IP_INFO_STRU *pstIpInfo解析后的IP包信息存储位置，调用者保证有效
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_DecodeBstDlPacket( TTF_MEM_ST *pstIpPkt, CDS_BST_IP_INFO_STRU *pstIpInfo )
{
    IPV4_HDR_STRU          *pstIpv4Hdr  = VOS_NULL_PTR;
    TCP_HDR_STRU           *pstTcpHdr   = VOS_NULL_PTR;
    VOS_UINT8              *pucIpData   = VOS_NULL_PTR;
    VOS_UINT32              ulHdrLen    = 0;
    VOS_UINT32              ulCopyLen   = 0;
    VOS_UINT32              ulCopeidFlag= PS_FALSE;

    /*保存IP头中信息*/
    pucIpData               = pstIpPkt->pData;
    pstIpv4Hdr              = (IPV4_HDR_STRU *)((VOS_UINT32)( pucIpData ));
    ulHdrLen                = (pstIpv4Hdr->ucIpHdrLen << 2) + CDS_BST_IP_PORTS_LEN;

    /* UMTS情况下，TTF_MEM存在级联情况，不能直接调用softfilter函数*/
    if ( pstIpPkt->usUsed < ulHdrLen )
    {
        pucIpData           = PS_MEM_ALLOC( UEPS_PID_CDS, ulHdrLen );
        if( VOS_NULL_PTR == pucIpData )
        {
            CDS_DBG_BST_FILTER_ALLOC_MEM_FAIL_NUM(1);
            CDS_INFO_LOG1( UEPS_PID_CDS, "CDS_BST_DecodeDl: No memory to Alloc Length", ulHdrLen );
            CDS_PRINT_INFO1(CDS_DecodeBstDlPacket_ENUM, CDS_PRINT_ALLOC_MEM_FAIL_HDRLEN, ulHdrLen);
            return PS_FALSE;
        }

        ulCopyLen = PS_MIN(ulHdrLen, TTF_MemGetLen(UEPS_PID_CDS, pstIpPkt));
        if( PS_SUCC != TTF_MemGet( UEPS_PID_CDS, pstIpPkt, 0,
                                   pucIpData, (VOS_UINT16)ulCopyLen ) )
        {
            CDS_DBG_BST_FILTER_ERROR_COPY_PKT_NUM(1);
            CDS_INFO_LOG1( UEPS_PID_CDS, "CDS_BST_DecodeDl Error Copy %u", ulCopeidFlag );
            CDS_PRINT_INFO1(CDS_DecodeBstDlPacket_ENUM, CDS_PRINT_COPY_ERROR_COPYFLAG, ulCopeidFlag);
            PS_MEM_FREE( UEPS_PID_CDS, pucIpData );
            return PS_FALSE;
        }
        CDS_DBG_BST_FILTER_SUCCS_COPY_PKT_NUM(1);
        /* 更新IP头信息 */
        ulCopeidFlag        = PS_TRUE;
        pstIpv4Hdr          = (IPV4_HDR_STRU *)((VOS_UINT32)(pucIpData));
        CDS_INFO_LOG1( UEPS_PID_CDS, "CDS_BST_DecodeDl: Coped OK", ulHdrLen );
        CDS_PRINT_INFO1(CDS_DecodeBstDlPacket_ENUM, CDS_PRINT_COPY_SUCC_HDRLEN, ulHdrLen);
    }
#ifdef BST_MODEM_SELF
    if ( IPV4_PROTOCOL_TCP == pstIpv4Hdr->ucProtocol )
    {
        DSPP_TEST_EMAIL( pstIpv4Hdr->unDestAddr.ulIpAddr );
    }
#endif
    /* 非TCP/UDP包，不进行处理 */
    if( ( IPV4_PROTOCOL_TCP != pstIpv4Hdr->ucProtocol )
      &&( IPV4_PROTOCOL_UDP != pstIpv4Hdr->ucProtocol ) )
    {
        CDS_INFO_LOG1( UEPS_PID_CDS,
                       "CDS_BST_DecodeDl: Unknow Protocol Packet",
                       pstIpv4Hdr->ucProtocol );
        CDS_PRINT_INFO1(CDS_DecodeBstDlPacket_ENUM, CDS_PRINT_UNKNOWN_PROTOCOL, pstIpv4Hdr->ucProtocol);
        CDS_DBG_BST_FILTER_WRONG_PROTOCOL_NUM(1);
        if ( PS_TRUE == ulCopeidFlag )
        {
            PS_MEM_FREE( UEPS_PID_CDS, pucIpData );
        }
        return PS_FALSE;
    }
    pstIpInfo->usProtocol   = pstIpv4Hdr->ucProtocol;
    /* IP 分片，不能确认端口，不处理 */
    if ( IP_NTOHS( pstIpv4Hdr->usOffset ) & ( IPV4_DF_MASK - 0x01U ) )
    {
        CDS_INFO_LOG1( UEPS_PID_CDS,
                       "CDS_BST_DecodeDl: Fragement Packet",
                       IP_NTOHS( pstIpv4Hdr->usOffset ) );
        CDS_PRINT_INFO1(CDS_DecodeBstDlPacket_ENUM, CDS_PRINT_FRAGMENT_PKT_OFFSET, IP_NTOHS( pstIpv4Hdr->usOffset ));
        CDS_DBG_BST_FILTER_FRAGEMENTD_PKT_NUM(1);
        if ( PS_TRUE == ulCopeidFlag )
        {
            PS_MEM_FREE( UEPS_PID_CDS, pucIpData );
        }
        return PS_FALSE;
    }
    pstTcpHdr               = (TCP_HDR_STRU *)((VOS_UINT32)(pucIpData +
                                               (pstIpv4Hdr->ucIpHdrLen << 2)));
    pstIpInfo->usDstPort    = IP_NTOHS( pstTcpHdr->usDstPort );
    if ( PS_TRUE == ulCopeidFlag )
    {
        PS_MEM_FREE( UEPS_PID_CDS, pucIpData );
    }
    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : CDS_BstGetDataType
 功能描述  : 判断是否为Bastet代理的下行数据包
 输入参数  : TTF_MEM_ST *pstIpPkt TTF格式数据包，调用者保证有效
 输出参数  : VOS_TRUE       数据为BASTET需要的IP包
             VOS_FALSE      数据非BASTET需要，通知DLPROC转发到A核
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_BstGetDataType( TTF_MEM_ST *pstIpPkt )
{
    CDS_BST_ENTITY_STRU    *pstBstEntity    = VOS_NULL_PTR;
    CDS_BST_IP_INFO_STRU    stIpInfo        = {0};

    if ( PS_FALSE == CDS_GetBastetSupportFlag())
    {
        return BST_IP_PKT_TO_AP;
    }

    pstBstEntity            = CDS_GetBastetEntity();
    if ( VOS_NULL_PTR == pstBstEntity->pfPortCheck )
    {
        return BST_IP_PKT_TO_AP;
    }

    if ( CDS_BASTET_NET_DEVICE_UNKNOW == pstBstEntity->usNetState )
    {
        CDS_DBG_BST_FILTER_NID_ERR_NUM(1);
        return BST_IP_PKT_TO_AP;
    }

    if ( VOS_NULL_PTR == pstIpPkt )
    {
        CDS_ERROR_LOG( UEPS_PID_CDS, "CDS_IsBastetPacket: pstIpPkt = NULL" );
        CDS_PRINT_ERROR(CDS_IsBastetPacket_ENUM, LL2_PARA_CHECK_FAIL);
        return BST_IP_PKT_TO_AP;
    }
    if ( IP_VERSION_V4 != IP_GET_VERSION( pstIpPkt->pData) )
    {
        CDS_DBG_BST_FILTER_NOT_IPVER4_PKT_NUM(1);
        return BST_IP_PKT_TO_AP;
    }

   /*                      *
    * 工作在垃圾包处理模式 *
    *                      */
    if ( CDS_BASTET_NET_DEVICE_DOWN == pstBstEntity->usNetState )
    {
        CDS_DBG_BST_FILTER_RUBBISH_NUM(1);
        return BST_IP_PKT_TO_BST;
    }
    if ( PS_FALSE == CDS_DecodeBstDlPacket( pstIpPkt, &stIpInfo ) )
    {
        CDS_INFO_LOG( UEPS_PID_CDS, "CDS_IsBastetPacket: Decode Ip V4 Packet Error" );
        CDS_PRINT_INFO(CDS_IsBastetPacket_ENUM, CDS_PRINT_IPV4_PKT_DECODE_ERROR);
        return BST_IP_PKT_TO_AP;
    }
    return pstBstEntity->pfPortCheck( stIpInfo.usProtocol, stIpInfo.usDstPort );
}

/*****************************************************************************
 函 数 名  : CDS_DlProcBastetData
 功能描述  : 从空口收到的Bastet包处理函数，转发到BASTET线程处理
 输入参数  : TTF_MEM_ST *pstIpPkt       TTF格式数据包
             VOS_UINT8    ucDeftRabId,  数据来源RAB
             VOS_UINT16   usModemId,    数据来源Modem
             VOS_UINT32   ulSduLen      承载SDU(IP包)实际长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DlProcBastetData( TTF_MEM_ST  *pstIpPkt,
                               VOS_UINT8    ucDeftRabId,
                               VOS_UINT16   usModemId,
                               VOS_UINT32   ulSduLen )
{
    CDS_BST_ENTITY_STRU    *pstBstEntity;

    if ( VOS_NULL_PTR == pstIpPkt )
    {
        CDS_DBG_BST_DL_RX_FUN_PARA_ERR(1);
        CDS_ERROR_LOG( UEPS_PID_CDS,"Enter CDS_DlProcBastetData: pstIpPkt = NULL " );
        CDS_PRINT_ERROR(CDS_DlProcBastetData_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }

    pstBstEntity            = CDS_GetBastetEntity();
    if ( VOS_NULL_PTR == pstBstEntity->pfRcvDlPacket )
    {
        CDS_DBG_BST_DL_RX_FUN_PARA_ERR(1);
        CDS_ERROR_LOG( UEPS_PID_CDS,"Enter CDS_DlProcBastetData: pfRcvDlPacket = NULL " );
        CDS_PRINT_ERROR(CDS_DlProcBastetData_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }

    CDS_DBG_BST_DL_RX_BST_PKT_NUM(1);
    CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF( pstIpPkt,
                                          ulSduLen,
                                          usModemId,
                                          ucDeftRabId );

    CDS_DBG_DL_REC_IP_PKT_INFO(pstIpPkt);
    CDS_DBG_BASTET_DL_IP_PKT_HOOK(pstIpPkt); /*鈎包*/

    pstBstEntity->pfRcvDlPacket( (VOS_UINT8 *)pstIpPkt,
                                 (VOS_UINT16)sizeof(TTF_MEM_ST) );

    /*发送消息*/
    CDS_DBG_BST_DL_SEND_TO_NIC_SUCC_NUM(1);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_RxDataFromBastet
 功能描述  : 接收来自BASTET的上行IP包，推入上行队列
 输入参数  : const VOS_UINT8 *pData,    数据指针头
             const VOS_UINT32 ulLen     数据长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CDS_RxDataFromBastet( const VOS_UINT8 *pData, const VOS_UINT32 ulLen, const VOS_UINT8 ucFlg )
{
    CDS_ENTITY_STRU            *pstCdsEntity= VOS_NULL_PTR;
    TTF_MEM_ST                 *pstTtfPkt   = VOS_NULL_PTR;
    VOS_INT32                   lLock;

    CDS_DBG_BST_UL_RX_FUN_CALL_NUM(1);
    /*入参判断*/
    if ( VOS_NULL_PTR == pData )
    {
        CDS_DBG_BST_UL_RX_FUN_PARA_ERR(1);
        CDS_INFO_LOG( UEPS_PID_CDS,"CDS_RxDataFromBastet: NULL pData" );
        CDS_PRINT_INFO(CDS_RxDataFromBastet_ENUM, LL2_PARA_CHECK_FAIL);
        return 0;
    }

    if( ( ulLen > ETH_MAX_MTU ) || ( 0 == ulLen ) )
    {
        CDS_DBG_BST_UL_RX_FUN_PARA_ERR(1);
        CDS_INFO_LOG1( UEPS_PID_CDS, "CDS_RxDataFromBastet: Packet Length Error.", ulLen );
        CDS_PRINT_INFO1(CDS_RxDataFromBastet_ENUM, CDS_PRINT_PKT_LEN_ERROR, ulLen);
        return 0;
    }

    if ( CDS_GetUsedModemId() >= MODEM_ID_BUTT )
    {
        CDS_DBG_BST_UL_RX_FUN_PARA_ERR(1);
        CDS_INFO_LOG1( UEPS_PID_CDS,"CDS_RxDataFromBastet: Invalid Modem Id.", CDS_GetUsedModemId() );
        CDS_PRINT_INFO1(CDS_RxDataFromBastet_ENUM, CDS_PRINT_MODEM_ID_ERROR, CDS_GetUsedModemId());
        return 0;
    }
    pstCdsEntity                = CDS_GetCdsEntity( CDS_GetUsedModemId() );
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_DBG_BST_UL_RX_FUN_PARA_ERR(1);
        CDS_INFO_LOG1( UEPS_PID_CDS, "CDS_RxDataFromBastet: Modem ID Error.", CDS_GetUsedModemId() );
        CDS_PRINT_INFO1(CDS_RxDataFromBastet_ENUM, CDS_PRINT_MODEM_ID_ERROR, CDS_GetUsedModemId());
        return 0;
    }
    CDS_DBG_BST_UL_RX_NIC_PKT_NUM(1);

    /*申请TTF内存,并将其拷贝到TTF内存中*/
    pstTtfPkt                   = CDS_AllocTtfMem(ulLen);
    if ( VOS_NULL_PTR == pstTtfPkt )
    {
        CDS_DBG_BST_UL_ALLOC_MEM_FAIL_NUM(1);
        CDS_INFO_LOG( UEPS_PID_CDS, "CDS_RxDataFromBastet: Alloc Mem Fail." );
        CDS_PRINT_INFO(CDS_RxDataFromBastet_ENUM, LL2_ALLOC_MEM_FAIL);
        return 0;
    }
    PS_MEM_CPY( pstTtfPkt->pData, pData, ulLen );
    if((ucFlg & CDS_BST_UL_DATA_HIGH_PRI) == CDS_BST_UL_DATA_HIGH_PRI)
    {
        pstTtfPkt->ucDataPriority =(VOS_UINT8) TTF_PS_DATA_PRIORITY_HIGH;
    }
    else
    {
        pstTtfPkt->ucDataPriority =(VOS_UINT8)  TTF_PS_DATA_PRIORITY_NORMAL;
    }

    /*入队*/
    lLock                       = VOS_SplIMP();
    if ( PS_SUCC != LUP_EnQue( pstCdsEntity->pstBastetUlQue, pstTtfPkt ) )
    {
        CDS_DBG_BST_UL_EN_QUE_FAIL_NUM(1);
        TTF_MemFree( UEPS_PID_CDS, pstTtfPkt );
        VOS_Splx(lLock);
        return 0;
    }
    CDS_DBG_BST_UL_EN_QUE_SUCC_NUM(1);
    VOS_Splx(lLock);
    /*wakeup cds*/
    CDS_SendEventToCds( CDS_EVENT_UL_BASTET_PROC );
    CDS_DBG_BST_UL_TRIGGER_BST_EVENT_NUM(1);
    return ulLen;
}

/*****************************************************************************
 函 数 名  : CDS_UlProcBastetData
 功能描述  : CdsEntity处理上行Bastet事件IP包
 输入参数  : 无(数据在pstBastetDataQue队列中)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_UlProcBastetData( VOS_VOID )
{
    VOS_UINT32              ulCnt;
    VOS_INT32               lLock;
    VOS_UINT16              usFilterResult;
    TTF_MEM_ST             *pstIpPkt;
    CDS_ENTITY_STRU        *pstCdsEntity;
    CDS_BST_ENTITY_STRU    *pstBstEntity;

    pstBstEntity            = CDS_GetBastetEntity();
    pstCdsEntity            = CDS_GetCdsEntity( pstBstEntity->usModemId );

    if (  pstBstEntity->usModemId >= MODEM_ID_BUTT )
    {
        CDS_ERROR_LOG( UEPS_PID_CDS, "Enter CDS_UlProcBastetData: WRONG Modem ID " );
        CDS_PRINT_ERROR(CDS_UlProcBastetData_ENUM, CDS_PRINT_MODEM_ID_ERROR);
        return PS_FAIL;
    }

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG( UEPS_PID_CDS, "Enter CDS_UlProcBastetData: CDS_GetCdsEntity Fail " );
        CDS_PRINT_ERROR(CDS_UlProcBastetData_ENUM, CDS_PRINT_GET_ENTITY_FAIL);
        return PS_FAIL;
    }

    for ( ulCnt = 0; ulCnt < CDS_BASTET_QUE_SIZE; ulCnt ++ )
    {
        lLock               = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue( pstCdsEntity->pstBastetUlQue, ( VOS_VOID **)&pstIpPkt) )
        {
            VOS_Splx(lLock);
            break;
        }
        VOS_Splx(lLock);
        if ( MMC_CDS_MODE_LTE == pstCdsEntity->enRanMode )
        {
            usFilterResult      = 0;
            /*LTE上行软过滤*/
            if (PS_SUCC != CDS_IpSoftFilter(pstIpPkt, &usFilterResult, pstCdsEntity))
            {
                CDS_DBG_BST_UL_SOFT_FILTER_FAIL_NUM(1);
                TTF_MemFree( UEPS_PID_CDS, pstIpPkt );
                continue;
            }
            /*将过滤结果存到TTF中*/
            CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt, usFilterResult);
        }
        else if ( MMC_CDS_MODE_GU == pstCdsEntity->enRanMode )
        {
            CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF( pstIpPkt, 0,
                                                      pstBstEntity->usModemId,  pstBstEntity->ucRabId );
        }
        else
        {
            TTF_MemFree( UEPS_PID_CDS, pstIpPkt );
            continue;
        }

        CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt);
        CDS_DBG_BASTET_UL_IP_PKT_HOOK(pstIpPkt);

        CDS_UlDispatchDataByRanMode( pstCdsEntity, pstIpPkt );
        CDS_DBG_BST_UL_SEND_PKT_TO_RAN_NUM(1);
    }

    CDS_TriggerUlProcOnFinalRD();

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : CDS_FwProcBastetData
 功能描述  : 入队Bastet认为非自行能够处理的IP包到A核
 输入参数  : VOS_UINT8        *pData    转发包TTF_MEM_ST
             VOS_UINT32        ulLen    辅助确认结构体长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_FwProcBastetData(
    const VOS_UINT8        *pData,
    const VOS_UINT32        ulLen )
{
    TTF_MEM_ST             *pstPktItem;

    CDS_DBG_BST_FW_PROC_BST_EVENT_NUM(1);
    if ( VOS_NULL_PTR == pData )
    {
        CDS_DBG_BST_FW2AP_FUN_PARA_ERR(1);
        CDS_INFO_LOG( UEPS_PID_CDS, "CDS_FwProcBastetData Null Message" );
        CDS_PRINT_INFO(CDS_FwProcBastetData_ENUM, LL2_PARA_CHECK_FAIL);
        return 0;
    }
    if ( (VOS_UINT32)sizeof(TTF_MEM_ST) != ulLen )
    {
        CDS_DBG_BST_FW2AP_FUN_PARA_ERR(1);
        CDS_INFO_LOG( UEPS_PID_CDS, "CDS_FwProcBastetData Wrong TTF Length" );
        CDS_PRINT_INFO(CDS_FwProcBastetData_ENUM, CDS_PRINT_TTF_LEN_ERROR);
        return 0;
    }
    pstPktItem                  =(TTF_MEM_ST *)pData;
    /*入队*/
    if (PS_SUCC != CDS_RxDlSdu(pstPktItem))
    {
        CDS_DBG_BST_FW2AP_QUE_FAIL_NUM(1);
        return 0;
    }
    CDS_SendEventToCds( CDS_EVENT_DL_DATA_PROC );
    CDS_DBG_BST_FW2AP_QUE_SUCC_NUM(1);
    /*返回TTF格式长度，代表数据正常发送，为0表示没有发送成功*/
    return (VOS_UINT32)sizeof(TTF_MEM_ST);
}

/*****************************************************************************
 函 数 名  : CDS_ConfigBastetNetState
 功能描述  : 获取ID_BST_CDS_NET_DEVICE_UP_IND信息，保持当前网卡状态
 输入参数  : const BST_CDS_NET_DEVICE_STATE_STRU *pstNetMsg 消息结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ConfigBastetNetState( const BST_CDS_NET_DEVICE_STATE_STRU *pstNetMsg )
{
    CDS_BST_ENTITY_STRU        *pstBstEntity = VOS_NULL_PTR;
    pstBstEntity                = CDS_GetBastetEntity();
    if ( VOS_NULL_PTR == pstNetMsg )
    {
        CDS_INFO_LOG( UEPS_PID_CDS, "CDS_ConfigBastetNetState Null Message" );
        CDS_PRINT_INFO(CDS_ConfigBastetNetState_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }
    pstBstEntity->usNetState    = (VOS_UINT16)pstNetMsg->ulNetDeviceState;
}

/*****************************************************************************
 函 数 名  : CDS_RegBstDlRcvCB
 功能描述  : 注册下行收包回调函数
 输入参数  : const BST_CDS_REG_RCV_CB_STRU *pstRegDlRcvFunMsg 消息结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_RegBstDlRcvCB( const BST_CDS_REG_RCV_CB_STRU *pstRegDlRcvFunMsg )
{
    CDS_BST_ENTITY_STRU        *pstBstEntity    = VOS_NULL_PTR;
    pstBstEntity                = CDS_GetBastetEntity();

    if ( VOS_NULL_PTR == pstRegDlRcvFunMsg->pfRcvCb )
    {
        CDS_ERROR_LOG( UEPS_PID_CDS, "CDS_RegBstDlRcvCB NULL DATA" );
        CDS_PRINT_ERROR(CDS_RegBstDlRcvCB_ENUM, LL2_PARA_CHECK_FAIL);
        return PS_FAIL;
    }
    pstBstEntity->pfRcvDlPacket = pstRegDlRcvFunMsg->pfRcvCb;
    pstBstEntity->pfPortCheck   = pstRegDlRcvFunMsg->pfChkPortCb;
    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : CDS_RegBstDlRcvCB
 功能描述  : 注册下行收包回调函数
 输入参数  : const BST_CDS_REG_RCV_CB_STRU *pstRegDlRcvFunMsg 消息结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_ConfigAcoreModemRabid(
    const BST_CDS_NET_ACORE_MODEM_RABID_STRU *pstModemRabIdMsg )
{
    CDS_BST_ENTITY_STRU        *pstBstEntity    = VOS_NULL_PTR;
    pstBstEntity                = CDS_GetBastetEntity();

    pstBstEntity->usModemId     = pstModemRabIdMsg->usModemId;
    pstBstEntity->ucRabId       = (VOS_UINT8)pstModemRabIdMsg->usRabId;
    CDS_INFO_LOG2( UEPS_PID_CDS, "CDS_ConfigAcoreModemRabid config modem id:%d,RABID:%d",
                           pstBstEntity->usModemId,  pstBstEntity->ucRabId);
    CDS_PRINT_INFO2(CDS_ConfigAcoreModemRabid_ENUM, CDS_PRINT_MODEM_ID_RABID, pstBstEntity->usModemId,  pstBstEntity->ucRabId);
    return PS_SUCC;
}
/*****************************************************************************
 函 数 名  : CDS_ConfigBastetTxRxEnable
 功能描述  : 获取ID_BST_CDS_TX_RX_RPT_CTRL_REQ消息，配置是否上报数据收发标志
 输入参数  : const BST_CDS_TX_RX_RPT_ENABLE_STRU *pstFlagMsg 消息结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ConfigBastetRxEnable( const BST_CDS_TX_RX_RPT_ENABLE_STRU *pstFlagMsg )
{
    CDS_BST_ENTITY_STRU        *pstBstEntity    = VOS_NULL_PTR;

    pstBstEntity                = CDS_GetBastetEntity();
    if ( VOS_NULL_PTR == pstFlagMsg )
    {
        CDS_INFO_LOG( UEPS_PID_CDS, "CDS_ConfigBastetTxRxEnable Null Message" );
        CDS_PRINT_INFO(CDS_ConfigBastetTxRxEnable_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }
    pstBstEntity->ucRptEnable   = (VOS_UINT8)pstFlagMsg->ulEnableFlag;
    return;
}

/*****************************************************************************
 函 数 名  : CDS_ConfigBastetTxRxEnable
 功能描述  : 获取ID_BST_CDS_TX_RX_RPT_CTRL_REQ消息，配置是否上报数据收发标志
 输入参数  : const BST_CDS_TX_RX_RPT_ENABLE_STRU *pstFlagMsg 消息结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ConfigBastetTxEnable( const BST_CDS_TX_RX_RPT_ENABLE_STRU *pstFlagMsg )
{
    CDS_BST_ENTITY_STRU        *pstBstEntity    = VOS_NULL_PTR;

    pstBstEntity                = CDS_GetBastetEntity();
    if ( VOS_NULL_PTR == pstFlagMsg )
    {
        CDS_INFO_LOG( UEPS_PID_CDS, "CDS_ConfigBastetTxRxEnable Null Message" );
        CDS_PRINT_INFO(CDS_ConfigBastetTxRxEnable_ENUM, LL2_PARA_CHECK_FAIL);
        return;
    }
    pstBstEntity->ucTxRptEnable   = (VOS_UINT8)pstFlagMsg->ulEnableFlag;
    return;
}


/*****************************************************************************
 函 数 名  : CDS_BastetCheckChannelId
 功能描述  : 检查当前使用的RabId, ModemId是否有变化，如果变化则立即通知Bastet
 输入参数  : VOS_UINT16 usModemId,  当前使用的modemId
             VOS_UINT8 ucRabId      当前使用的RabId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_BstSendRsmCbMsg( VOS_VOID )
{
    BST_CDS_SEND_CB_INFO_STRU  *pstChnlInfoMsg  = VOS_NULL_PTR;
    VOS_UINT32                  ulMsgLen;

    ulMsgLen                    = sizeof( BST_CDS_SEND_CB_INFO_STRU );
    pstChnlInfoMsg              = CDS_ALLOC_MSG_WITH_HDR( ulMsgLen );

    if (VOS_NULL_PTR == pstChnlInfoMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_UpdateBastetModemId : Alloc Msg Fail. Size .", ulMsgLen );
        CDS_PRINT_ERROR1(CDS_BstSendRsmCbMsg_ENUM, CDS_PRINT_ALLOC_MSG_FAIL_SIZE, ulMsgLen);
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR( pstChnlInfoMsg, UEPS_PID_BASTET );
    pstChnlInfoMsg->ulMsgId     = ID_BST_CDS_CHANNEL_INFO_IND;
    pstChnlInfoMsg->pSendCbFun  = CDS_RxDataFromBastet;
    pstChnlInfoMsg->pResmCbFun  = CDS_FwProcBastetData;

    /*发送消息*/
    CDS_SEND_MSG( pstChnlInfoMsg );
    return;
}

/*****************************************************************************
 函 数 名  : CDS_SendBastetRxInd
 功能描述  : 提示Bastet模块，当前有非Bastet数据IP包在接收，不可以快速拆链
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_BstSendRxInd( VOS_VOID )
{
    BST_CDS_TX_RX_MSG_STRU     *pstTrxMsg;
    CDS_BST_ENTITY_STRU        *pstBstEntity;
    VOS_UINT32                  ulMsgLen;

    if ( PS_FALSE == CDS_GetBastetSupportFlag() )
    {
        return;
    }

    pstBstEntity                = CDS_GetBastetEntity();
    if ( PS_FALSE == pstBstEntity->ucRptEnable )
    {
        return;
    }
    ulMsgLen                = sizeof( BST_CDS_TX_RX_MSG_STRU );
    pstTrxMsg               = CDS_ALLOC_MSG_WITH_HDR( ulMsgLen );

    if (VOS_NULL_PTR == pstTrxMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NoticeBastetTxRx : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_BstSendTxRxInd_ENUM, CDS_PRINT_ALLOC_MSG_FAIL_SIZE, ulMsgLen);
        return;
    }

    pstBstEntity->ucRptEnable   = PS_FALSE;

    /*填写消息内容*/
    CDS_CFG_MSG_HDR( pstTrxMsg, UEPS_PID_BASTET );
    pstTrxMsg->ulMsgId      = ID_BST_CDS_RX_IND;
    /*发送消息*/
    CDS_SEND_MSG(pstTrxMsg);
    return;
}


/*****************************************************************************
 函 数 名  : CDS_BstSendTxInd
 功能描述  : 提示Bastet模块，当前有非Bastet数据IP包在发送，不可以快速拆链
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年05月22日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_BstSendTxInd( VOS_VOID )
{
    BST_CDS_TX_RX_MSG_STRU     *pstTrxMsg;
    CDS_BST_ENTITY_STRU        *pstBstEntity;
    VOS_UINT32                  ulMsgLen;

    if ( PS_FALSE == CDS_GetBastetSupportFlag() )
    {
        return;
    }

    pstBstEntity                = CDS_GetBastetEntity();
    if ( PS_FALSE == pstBstEntity->ucTxRptEnable )
    {
        return;
    }
    ulMsgLen                = sizeof( BST_CDS_TX_RX_MSG_STRU );
    pstTrxMsg               = CDS_ALLOC_MSG_WITH_HDR( ulMsgLen );

    if (VOS_NULL_PTR == pstTrxMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NoticeBastetTxRx : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_BstSendTxRxInd_ENUM, CDS_PRINT_ALLOC_MSG_FAIL_SIZE, ulMsgLen);
        return;
    }

    pstBstEntity->ucTxRptEnable   = PS_FALSE;

    /*填写消息内容*/
    CDS_CFG_MSG_HDR( pstTrxMsg, UEPS_PID_BASTET );
    pstTrxMsg->ulMsgId      = ID_BST_CDS_TX_IND;
    /*发送消息*/
    CDS_SEND_MSG(pstTrxMsg);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_BstInit
 功能描述  : LTE流控初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_BstInit(VOS_VOID)
{
    VOS_UINT32                          ulReturnCode;
    BASTET_SUPPORT_FLG_STRU             stBastetFlag;

    /* 读NV项en_NV_Item_SVLTE_FLAG，失败，直接返回 */
    ulReturnCode = NV_ReadEx(MODEM_ID_0,en_NV_Item_Bastet_CONFIG,
                      &stBastetFlag, sizeof(BASTET_SUPPORT_FLG_STRU));
    if (PS_SUCC != ulReturnCode)
    {
         CDS_INFO_LOG(UEPS_PID_CDS, "read nv en_NV_Item_Bastet_CONFIG failed.");
         CDS_PRINT_INFO(CDS_BstInit_ENUM, CDS_PRINT_NV_READ_FAIL);
         return;
    }

    /* 赋值到全局变量中 */
    g_CdsBstEntity.ucNvFlag            = stBastetFlag.ucActiveFlg;
    g_CdsBstEntity.ucHookFlag          = stBastetFlag.ucHookFlg;
    g_CdsBstEntity.ucRabId             = FC_MIN_RABID;
    g_CdsBstEntity.ucRptEnable         = PS_TRUE;
    g_CdsBstEntity.ucTxRptEnable       = PS_TRUE;
    g_CdsBstEntity.usNetState          = CDS_BASTET_NET_DEVICE_UNKNOW;
    g_CdsBstEntity.usModemId           = MODEM_ID_0;
    g_CdsBstEntity.pfRcvDlPacket       = VOS_NULL_PTR;
    g_CdsBstEntity.pfPortCheck         = VOS_NULL_PTR;
    CDS_BstSendRsmCbMsg();
    return;
}



/*****************************************************************************
 函 数 名  : CDS_GetBastetSupportFlag
 功能描述  : LTE流控初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 CDS_GetBastetSupportFlag(VOS_VOID)
{
    CDS_BST_ENTITY_STRU        *pstBstEntity;

    pstBstEntity                = CDS_GetBastetEntity();

    return pstBstEntity->ucNvFlag;
}



/*****************************************************************************
 函 数 名  : CDS_GU_BstProcDlData
 功能描述 :GU模式下处理下行数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_TRUE ----bastet模块已处理，CDS模块不需要继续处理，
                       PS_FALSE----CDS模块需要继续处理
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月24日
      作    者   : z00128442
      修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 CDS_GU_BstProcDlData( CDS_RABM_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId )
{
    VOS_UINT32                          ulDataType;
    CDS_ENTITY_STRU                    *pstCdsEntity;
    VOS_UINT8                           ucDeftRabId = 0;
    TTF_MEM_ST                         *pstSdu;

    if ( PS_FALSE == CDS_GetBastetSupportFlag() )
    {
        return PS_FALSE;
    }

    if( VOS_NULL_PTR == pstDlData )
    {
        return PS_FALSE;
    }

    pstCdsEntity                        = CDS_GetCdsEntity( enModemId );
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return PS_FALSE;
    }

    ulDataType                          = CDS_BstGetDataType( pstDlData->pstSdu );

    switch( ulDataType )
    {
        case BST_IP_PKT_TO_BST:
        {
            /*下行流量统计*/
            CDS_DLDataFlowStats(pstDlData->ucRabId,pstDlData->ulSduLen,pstCdsEntity);
            /*获得缺省PDP承载ID*/
            if (PS_SUCC != CDS_GUGetDefaultRabId(pstDlData->ucRabId,&ucDeftRabId,enModemId))
            {
                return PS_FALSE;
            }
            CDS_DlProcBastetData( pstDlData->pstSdu,
                                  ucDeftRabId,
                                  enModemId,
                                  pstDlData->ulSduLen);
            return PS_TRUE;
        }
        case BST_IP_PKT_TO_AP_BST:
        {
            /*下行流量统计*/
            CDS_DLDataFlowStats(pstDlData->ucRabId,pstDlData->ulSduLen,pstCdsEntity);
            /*获得缺省PDP承载ID*/
            if (PS_SUCC != CDS_GUGetDefaultRabId(pstDlData->ucRabId,&ucDeftRabId,enModemId))
            {
                return PS_FALSE;
            }
            pstSdu = TTF_MemBlkCopyAllocFromMem( UEPS_PID_CDS,
                                                 TTF_MEM_POOL_ID_DL_PDU,
                                                 pstDlData->pstSdu,
                                                 0,
                                                 (VOS_UINT16)pstDlData->ulSduLen );

            if(pstSdu != VOS_NULL_PTR)
            {
                CDS_DlProcBastetData( pstSdu,
                                      ucDeftRabId,
                                      enModemId,
                                      pstDlData->ulSduLen);
            }
            return PS_FALSE;
        }
        default:
            break;
    }

    return PS_FALSE;
}

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
extern VOS_VOID L2_DlAppThrStatProc(VOS_UINT32 ulLength);

/*****************************************************************************
 函 数 名  : CDS_LTE_BstProcDlData
 功能描述 :LTE模式下处理下行数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_TRUE ----bastet模块已处理，CDS模块不需要继续处理，
                       PS_FALSE----CDS模块需要继续处理
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月24日
      作    者   : z00128442
      修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 CDS_LTE_BstProcDlData(CDS_LPDCP_DATA_STRU *pstDsLpdcpData,VOS_UINT8 ucRabId )
{
    VOS_UINT32                          ulDataType;
    CDS_ENTITY_STRU                    *pstCdsEntity;
    VOS_UINT8                           ucDeftEpsbID;
    TTF_MEM_ST                         *pstSdu;

    if ( PS_FALSE == CDS_GetBastetSupportFlag() )
    {
        return PS_FALSE;
    }

    if( VOS_NULL_PTR == pstDsLpdcpData )
    {
        return PS_FALSE;
    }

    /*LTE默认放在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);

    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return PS_FALSE;
    }

    ulDataType                          = CDS_BstGetDataType(pstDsLpdcpData->pstSdu);

    switch( ulDataType )
    {
        case BST_IP_PKT_TO_BST:
        {
            /*下行流量统计*/
            CDS_DLDataFlowStats(ucRabId,pstDsLpdcpData->ulSduLen,pstCdsEntity);
            L2_DlAppThrStatProc(pstDsLpdcpData->ulSduLen);
            /*获得缺省EPS承载ID*/
            if (PS_SUCC != CDS_ERABM_GetDefaultEpsbId(pstDsLpdcpData->ucRbId,&ucDeftEpsbID))
            {
                return PS_FALSE;
            }
            CDS_DlProcBastetData( pstDsLpdcpData->pstSdu,
                              ucDeftEpsbID,
                              MODEM_ID_0,
                              pstDsLpdcpData->ulSduLen );
            return PS_TRUE;
        }
        case BST_IP_PKT_TO_AP_BST:
        {
            /*下行流量统计*/
            CDS_DLDataFlowStats(ucRabId,pstDsLpdcpData->ulSduLen,pstCdsEntity);
            L2_DlAppThrStatProc(pstDsLpdcpData->ulSduLen);
            /*获得缺省PDP承载ID*/
            if (PS_SUCC != CDS_ERABM_GetDefaultEpsbId(pstDsLpdcpData->ucRbId,&ucDeftEpsbID))
            {
                return PS_FALSE;
            }
            pstSdu = TTF_MemBlkCopyAllocFromMem( UEPS_PID_CDS,
                                             TTF_MEM_POOL_ID_DL_PDU,
                                             pstDsLpdcpData->pstSdu,
                                             0,
                                             (VOS_UINT16)pstDsLpdcpData->ulSduLen );

            if(pstSdu != VOS_NULL_PTR)
            {
                CDS_DlProcBastetData( pstSdu,
                                      ucDeftEpsbID,
                                      MODEM_ID_0,
                                      pstDsLpdcpData->ulSduLen);
            }
            return PS_FALSE;
        }
        default:
            break;
    }

    return PS_FALSE;
}
#endif
/*lint +e429*/
/*lint -restore*/
#else
/*****************************************************************************
 函 数 名  : CDS_BstSendTxInd
 功能描述 :bastet模块未定义时，该函数空实现
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月24日
      作    者   : z00128442
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_BstSendTxInd( VOS_VOID )
{
    return;
}
/*****************************************************************************
 函 数 名  : CDS_BstSendRxInd
 功能描述 :bastet模块未定义时，该函数空实现
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月24日
      作    者   : z00128442
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_BstSendRxInd( VOS_VOID )
{
    return;
}

/*****************************************************************************
 函 数 名  : CDS_GU_BstProcDlData
 功能描述 :bastet模块未定义时，该函数空实现
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月24日
      作    者   : z00128442
      修改内容   : 新生成函数

*****************************************************************************/

PS_BOOL_ENUM_UINT8 CDS_GU_BstProcDlData( CDS_RABM_TRANS_DATA_STRU *pstDlData, MODEM_ID_ENUM_UINT16 enModemId )
{
    return PS_FALSE;
}


#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
/*****************************************************************************
 函 数 名  : CDS_LTE_BstProcDlData
 功能描述 :bastet模块未定义时，该函数空实现
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月24日
      作    者   : z00128442
      修改内容   : 新生成函数

*****************************************************************************/

PS_BOOL_ENUM_UINT8 CDS_LTE_BstProcDlData(CDS_LPDCP_DATA_STRU *pstDsLpdcpData,VOS_UINT8 ucRabId )
{
    return PS_FALSE;
}
#endif

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

