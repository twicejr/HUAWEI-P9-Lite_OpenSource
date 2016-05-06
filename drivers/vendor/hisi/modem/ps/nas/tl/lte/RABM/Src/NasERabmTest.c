


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmTest.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMTEST_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMTIMERMSGPROC_C
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
NAS_ERABM_UL_DATA_TRANS_INFO_STRU    g_stERabmUlDataTransInfo;
NAS_ERABM_DL_DATA_TRANS_INFO_STRU    g_stERabmDlDataTransInfo;



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ERABM_DebugInit
 Description     : 清除统计信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-17  Draft Enact

*****************************************************************************/
/*lint -e960*/
VOS_VOID NAS_ERABM_DebugInit(VOS_VOID)
{
    NAS_ERABM_MEM_SET_S(  &g_stERabmUlDataTransInfo,
                        sizeof(NAS_ERABM_UL_DATA_TRANS_INFO_STRU),
                        0,
                        sizeof(NAS_ERABM_UL_DATA_TRANS_INFO_STRU));
}

/*****************************************************************************
 Function Name   : NAS_ERABM_CmdHelp
 Description     : RABM模块命令显示
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangqianhui 00135146      2009-1-8  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ERABM_CmdHelp( VOS_VOID )
{
    (VOS_VOID)vos_printf("\r\n");
    (VOS_VOID)vos_printf("********************** NAS RABM 软调命令列表 *********************\r\n");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_DebugInit","清除RABM统计统计信息");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowEpsBearerDataTransInfo(ulEpsbId)","显示某承载数传信息");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowActiveEpsBearerDataTransInfo","显示所有激活承载数传信息");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowEpsbTftInfo(ulEpsbId)","显示某承载TFT信息");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowUlDataTransInfo","显示上行数传信息");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowDlDataTransInfo","显示下行数传信息");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowUlFilterInfo(ulFilterId)","显示上行过滤器信息");
    (VOS_VOID)vos_printf("*******************************************************************\r\n");
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowEpsBearerDataTransInfo
 Description     : 显示承载信息
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_ShowEpsBearerDataTransInfo( VOS_UINT32 ulEspbId )
{
    NAS_ERABM_BERER_DATA_TRANS_INFO_STRU    *pstEpsBearerDataTransInfo   = VOS_NULL_PTR;
    NAS_ERABM_EPSB_STATE_ENUM_UINT8          enEpsBearerState            = NAS_ERABM_GetEpsbStateInfo(ulEspbId);
    NAS_ERABM_RB_STATE_ENUM_UINT8            enRbState                   = NAS_ERABM_GetRbStateInfo(ulEspbId);

    if ((ulEspbId < NAS_ERABM_MIN_EPSB_ID) || (ulEspbId > NAS_ERABM_MAX_EPSB_ID))
    {
        (VOS_VOID)vos_printf("NAS_ERABM_ShowEpsBearerDataTransInfo:输入参数承载号的范围:5-15\r\n");
        return ;
    }

    pstEpsBearerDataTransInfo = NAS_ERABM_GetBearerDataTransInfoAddr(ulEspbId);

    (VOS_VOID)vos_printf("****************EPS承载%d对应的相关信息如下****************\r\n",ulEspbId);

    if (NAS_ERABM_EPSB_ACTIVE == enEpsBearerState)
    {
        (VOS_VOID)vos_printf("承载状态:%s\r\n","激活");
    }
    else
    {
        (VOS_VOID)vos_printf("承载状态:%s\r\n","未激活");
    }

    (VOS_VOID)vos_printf("关联RB号:%d\r\n",NAS_ERABM_GetEpsbRbIdInfo(ulEspbId));

    if (NAS_ERABM_RB_CONNECTED == enRbState)
    {
        (VOS_VOID)vos_printf("关联RB状态:%s\r\n","连接态");
    }
    else if (NAS_ERABM_RB_SUSPENDED == enRbState)
    {
        (VOS_VOID)vos_printf("关联RB状态:%s\r\n","暂停态");
    }
    else
    {
        (VOS_VOID)vos_printf("关联RB状态:%s\r\n","非连接态");
    }

    (VOS_VOID)vos_printf("承载QCI:%d\r\n",NAS_ERABM_GetEpsbQCI(ulEspbId));
    (VOS_VOID)vos_printf("发送数据包个数:%d\r\n",pstEpsBearerDataTransInfo->ulSendPackageNum);
    (VOS_VOID)vos_printf("丢弃数据包个数:%d\r\n",pstEpsBearerDataTransInfo->ulDiscardPackageNum);
    (VOS_VOID)vos_printf("关联DRB IDLE态下数据包个数:%d\r\n",pstEpsBearerDataTransInfo->ulIdlePackageNum);
    (VOS_VOID)vos_printf("关联DRB SUSPEND态下数据包个数:%d\r\n",pstEpsBearerDataTransInfo->ulSuspendPackageNum);
    (VOS_VOID)vos_printf("承载关联DRB不存在次数:%d\r\n",pstEpsBearerDataTransInfo->ulEpsbNoDrbTimes);
    (VOS_VOID)vos_printf("因承载关联DRB不存在而丢弃的数据包个数:%d\r\n",pstEpsBearerDataTransInfo->ulEpsbNoDrbDiscPackageNum);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowActiveEpsBearerDataTransInfo
 Description     : 显示所有激活承载的数传信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_ShowActiveEpsBearerDataTransInfo( VOS_VOID )
{
    VOS_UINT32                 ulEpsbId;
    VOS_UINT32                 ulActiveNum = NAS_ERABM_NULL;

    for ( ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++ )
    {
        if ( NAS_ERABM_EPSB_INACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            continue;
        }
        else
        {
            ulActiveNum++;

            /* 显示承载数传信息 */
            NAS_ERABM_ShowEpsBearerDataTransInfo(ulEpsbId);
        }
    }

    if ( NAS_ERABM_NULL == ulActiveNum )
    {
        (VOS_VOID)vos_printf("%-30s\r\n","当前不存在激活的EPS承载");
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowEpsbTftInfo
 Description     : 统计EPS承载的TFT信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangqianhui 00135146      2009-1-8  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_ShowEpsbTftInfo( VOS_UINT32 ulEspbId )
{
    ESM_ERABM_TFT_PF_STRU           *pstEpsbTft = VOS_NULL_PTR;
    VOS_UINT32                      ulEpsbTftNum = NAS_ERABM_NULL;
    VOS_UINT32                      ulLoop = NAS_ERABM_NULL;

    if ((ulEspbId < NAS_ERABM_MIN_EPSB_ID) || (ulEspbId > NAS_ERABM_MAX_EPSB_ID))
    {
        (VOS_VOID)vos_printf("NAS_ERABM_ShowEpsbTftInfo:输入参数承载号的范围:5-15\r\n");
        return ;
    }

    ulEpsbTftNum = NAS_ERABM_GetEpsbTftPfNum(ulEspbId);

    if ( NAS_ERABM_NULL == ulEpsbTftNum )
    {
        (VOS_VOID)vos_printf("EPS承载%d不存在TFT信息\r\n",ulEspbId);
        return;
    }
    else
    {
        (VOS_VOID)vos_printf("EPS承载%d存在%d个PF\r\n",ulEspbId,ulEpsbTftNum);
    }

    for ( ulLoop = 0 ; ulLoop < ulEpsbTftNum; ulLoop++ )
    {
        pstEpsbTft = NAS_ERABM_GetEpsbTftAddr(ulEspbId, ulLoop);
        (VOS_VOID)vos_printf("********RABM模块统计的EPS承载%d的第%d个PF的TFT信息********\r\n",ulEspbId,(ulLoop + 1));

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpRmtIpv4AddrAndMask )
        {
            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","TFT的目的IPv4", pstEpsbTft->aucRmtIpv4Address[0],
                                      pstEpsbTft->aucRmtIpv4Address[1],
                                      pstEpsbTft->aucRmtIpv4Address[2],
                                      pstEpsbTft->aucRmtIpv4Address[3]);

            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","TFT的掩码", pstEpsbTft->aucRmtIpv4Mask[0],
                                      pstEpsbTft->aucRmtIpv4Mask[1],
                                      pstEpsbTft->aucRmtIpv4Mask[2],
                                      pstEpsbTft->aucRmtIpv4Mask[3]);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpRmtIpv6AddrAndMask )
        {
            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","TFT的目的IPv6",
                                      pstEpsbTft->aucRmtIpv6Address[0],
                                      pstEpsbTft->aucRmtIpv6Address[1],
                                      pstEpsbTft->aucRmtIpv6Address[2],
                                      pstEpsbTft->aucRmtIpv6Address[3],
                                      pstEpsbTft->aucRmtIpv6Address[4],
                                      pstEpsbTft->aucRmtIpv6Address[5],
                                      pstEpsbTft->aucRmtIpv6Address[6],
                                      pstEpsbTft->aucRmtIpv6Address[7],
                                      pstEpsbTft->aucRmtIpv6Address[8],
                                      pstEpsbTft->aucRmtIpv6Address[9],
                                      pstEpsbTft->aucRmtIpv6Address[10],
                                      pstEpsbTft->aucRmtIpv6Address[11],
                                      pstEpsbTft->aucRmtIpv6Address[12],
                                      pstEpsbTft->aucRmtIpv6Address[13],
                                      pstEpsbTft->aucRmtIpv6Address[14],
                                      pstEpsbTft->aucRmtIpv6Address[15]);

            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","TFT的掩码",
                                      pstEpsbTft->aucRmtIpv6Mask[0],
                                      pstEpsbTft->aucRmtIpv6Mask[1],
                                      pstEpsbTft->aucRmtIpv6Mask[2],
                                      pstEpsbTft->aucRmtIpv6Mask[3],
                                      pstEpsbTft->aucRmtIpv6Mask[4],
                                      pstEpsbTft->aucRmtIpv6Mask[5],
                                      pstEpsbTft->aucRmtIpv6Mask[6],
                                      pstEpsbTft->aucRmtIpv6Mask[7],
                                      pstEpsbTft->aucRmtIpv6Mask[8],
                                      pstEpsbTft->aucRmtIpv6Mask[9],
                                      pstEpsbTft->aucRmtIpv6Mask[10],
                                      pstEpsbTft->aucRmtIpv6Mask[11],
                                      pstEpsbTft->aucRmtIpv6Mask[12],
                                      pstEpsbTft->aucRmtIpv6Mask[13],
                                      pstEpsbTft->aucRmtIpv6Mask[14],
                                      pstEpsbTft->aucRmtIpv6Mask[15]);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpLocalPortRange )
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的近端端口最小值", pstEpsbTft->usLcPortLowLimit);
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的近端端口最大值", pstEpsbTft->usLcPortHighLimit);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpRemotePortRange)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的远端端口最小值", pstEpsbTft->usRmtPortLowLimit);
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的远端端口最大值", pstEpsbTft->usRmtPortHighLimit);
        }

        if (NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpProtocolId)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的协议版本号", pstEpsbTft->ucProtocolId);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpSingleLocalPort)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的近端端口号", pstEpsbTft->usSingleLcPort);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpSingleRemotePort)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的远端端口号", pstEpsbTft->usSingleRmtPort);
        }

        (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT的优先级", pstEpsbTft->ucPrecedence);

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowUlDataTransInfo
 Description     : 显示上行数传信息
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_ShowUlDataTransInfo( VOS_VOID )
{
    NAS_ERABM_UL_DATA_TRANS_INFO_STRU *pstUlDataTransInfo = VOS_NULL_PTR;

    pstUlDataTransInfo = NAS_ERABM_GetUlDataTransInfoAddr();

    (VOS_VOID)vos_printf("****************************上行数传信息****************************\r\n");
    (VOS_VOID)vos_printf("上行收到总数据包数:%d\r\n",pstUlDataTransInfo->ulRecePackageNum);
    (VOS_VOID)vos_printf("上行发送总数据包数:%d\r\n",pstUlDataTransInfo->ulSendPackageNum);
    (VOS_VOID)vos_printf("上行丢弃总数据包数:%d\r\n",pstUlDataTransInfo->ulDiscPackageNum);
    (VOS_VOID)vos_printf("上行DRB于IDLE态下总数据包数:%d\r\n",pstUlDataTransInfo->ulIdlePackageNum);
    (VOS_VOID)vos_printf("上行DRB于SUSPEND态下总数据包数:%d\r\n",pstUlDataTransInfo->ulSuspendPackageNum);
    (VOS_VOID)vos_printf("上行未找到承载总数据包个数:%d\r\n",pstUlDataTransInfo->ulUnfoundBearerPackageNum);
    (VOS_VOID)vos_printf("上行DHCPV4 SERVER总数据包个数:%d\r\n",pstUlDataTransInfo->ulDhcpv4ServerPacketNum);
    (VOS_VOID)vos_printf("上行第一个分片包个数:%d\r\n",pstUlDataTransInfo->ulFirstSegmentPacketNum);
    (VOS_VOID)vos_printf("上行分片包个数:%d\r\n",pstUlDataTransInfo->ulSegmentPacketNum);
    (VOS_VOID)vos_printf("上行未找到端口号包个数:%d\r\n",pstUlDataTransInfo->ulUnfoundPortPacketNum);

    /* 显示所有激活承载数传信息 */
    NAS_ERABM_ShowActiveEpsBearerDataTransInfo();
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowDlDataTransInfo
 Description     : 显示下行数传信息
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_ShowDlDataTransInfo( VOS_VOID )
{
    NAS_ERABM_DL_DATA_TRANS_INFO_STRU *pstDlDataTransInfo = VOS_NULL_PTR;

    pstDlDataTransInfo = NAS_ERABM_GetDlDataTransInfoAddr();

    (VOS_VOID)vos_printf("****************************下行数传信息****************************\r\n");
    (VOS_VOID)vos_printf("下行收到总数据包数:%d\r\n",pstDlDataTransInfo->ulRecePackageNum);
    (VOS_VOID)vos_printf("下行发送总数据包数:%d\r\n",pstDlDataTransInfo->ulSendPackageNum);
    (VOS_VOID)vos_printf("下行丢弃总数据包数:%d\r\n",pstDlDataTransInfo->ulDiscPackageNum);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowUlFilterInfo
 Description     : 显示上行过滤器信息
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-02-02  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_ShowUlFilterInfo(VOS_UINT32 ulFilterId)
{
    IPF_FILTER_CONFIG_S *pstFilterInfo = VOS_NULL_PTR;
    VOS_INT32  ulRslt = IPF_ERROR;

    pstFilterInfo = NAS_ERABM_MEM_ALLOC(sizeof(IPF_FILTER_CONFIG_S));

    if (VOS_NULL_PTR == pstFilterInfo)
    {
        (VOS_VOID)vos_printf(" 获取过滤器信息失败\r\n");
        return;
    }
    /*lint -e64*/
    ulRslt = LDRV_IPF_GET_FILTER(IPF_MODEM0_ULFC, ulFilterId, pstFilterInfo);
    /*lint +e64*/

    if (IPF_SUCCESS == ulRslt)
    {
        (VOS_VOID)vos_printf("****************************上行过滤器信息****************************\r\n");

        (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的ID", pstFilterInfo->u32FilterID);

        (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的EPSB承载ID", pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltBid);

        (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的使能状态", pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltEn);

        if (NAS_ERABM_IPF_IPTYPE_IPV4 == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltType)
        {
            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","过滤器的目的IPv4", pstFilterInfo->stMatchInfo.u8DstAddr[0],
                                          pstFilterInfo->stMatchInfo.u8DstAddr[1],
                                          pstFilterInfo->stMatchInfo.u8DstAddr[2],
                                          pstFilterInfo->stMatchInfo.u8DstAddr[3]);

            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","过滤器的掩码", pstFilterInfo->stMatchInfo.u8DstMsk[0],
                                          pstFilterInfo->stMatchInfo.u8DstMsk[1],
                                          pstFilterInfo->stMatchInfo.u8DstMsk[2],
                                          pstFilterInfo->stMatchInfo.u8DstMsk[3]);

            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","过滤器的源IPv4", pstFilterInfo->stMatchInfo.u8SrcAddr[0],
                                          pstFilterInfo->stMatchInfo.u8SrcAddr[1],
                                          pstFilterInfo->stMatchInfo.u8SrcAddr[2],
                                          pstFilterInfo->stMatchInfo.u8SrcAddr[3]);
            /*lint -e40*/
            (VOS_VOID)vos_printf("%-30s : %d\r\n","IPV4过滤器local address域源码配置值,从低位到高位0的个数为", pstFilterInfo->stMatchInfo.u32LocalAddressMsk);
            /*lint +e40*/
        }
        else
        {
            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","过滤器的目的IPv6",
                                  pstFilterInfo->stMatchInfo.u8DstAddr[0],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[1],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[2],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[3],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[4],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[5],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[6],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[7],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[8],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[9],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[10],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[11],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[12],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[13],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[14],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[15]);

            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","过滤器的掩码",
                                  pstFilterInfo->stMatchInfo.u8DstMsk[0],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[1],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[2],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[3],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[4],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[5],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[6],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[7],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[8],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[9],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[10],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[11],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[12],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[13],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[14],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[15]);
            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","过滤器的源IPv6",
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[0],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[1],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[2],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[3],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[4],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[5],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[6],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[7],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[8],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[9],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[10],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[11],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[12],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[13],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[14],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[15]);
            /*lint -e40*/
            (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器local address域源码配置值,从低位到高位0的个数为", pstFilterInfo->stMatchInfo.u32LocalAddressMsk);
            /*lint +e40*/

        }
        (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的协议版本号", pstFilterInfo->stMatchInfo.unNextHeader.u32Protocol);

        if (NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltLPortEn)
        {
           (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的近端端口最小值", pstFilterInfo->stMatchInfo.unSrcPort.Bits.u16SrcPortLo);
           (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的近端端口最大值", pstFilterInfo->stMatchInfo.unSrcPort.Bits.u16SrcPortHi);
        }

        if (NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltRPortEn)
        {
           (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的远端端口最小值", pstFilterInfo->stMatchInfo.unDstPort.Bits.u16DstPortLo);
           (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的远端端口最大值", pstFilterInfo->stMatchInfo.unDstPort.Bits.u16DstPortHi);
        }

        if(NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltTosEn)
        {
            /*lint -e40*/
            /*lint -e10*/
            (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的ServiceType:",pstFilterInfo->stMatchInfo.unTrafficClass.Bits.u8TrafficClass);
            (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的ServiceType:",pstFilterInfo->stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask);
            /*lint +e10*/
            /*lint +e40*/
        }

        if(NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltSpiEn)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的FilterSpi:",pstFilterInfo->stMatchInfo.u32FltSpi);
        }

        if(NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltFlEn)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的FlowLable:",pstFilterInfo->stMatchInfo.u32FlowLable);
        }

        (VOS_VOID)vos_printf("%-30s : %d\r\n","过滤器的优先级", pstFilterInfo->stMatchInfo.unFltChain.Bits.u16FltPri);


    }
    else
    {
        (VOS_VOID)vos_printf(" 获取过滤器信息失败，错误码为:%d\r\n", ulRslt);
    }

    NAS_ERABM_MEM_FREE(pstFilterInfo);
}
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif






