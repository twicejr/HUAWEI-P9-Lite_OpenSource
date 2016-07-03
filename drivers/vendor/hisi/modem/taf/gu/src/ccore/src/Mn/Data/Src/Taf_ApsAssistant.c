

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnComm.h"
#include "NasOmInterface.h"
#include "NasOmTrans.h"
#include "MnApsComm.h"
#include "TafApsCtx.h"
#include "TafLog.h"
#include "TafApsMain.h"
#include "TafApsFsmMainTbl.h"
#include "NVIM_Interface.h"
#if (FEATURE_ON == FEATURE_IPV6)
#include "TafApsSndNd.h"
#endif
#include "TafApsComFunc.h"
#include "TafApsProcNvim.h"
#include "ApsL4aInterface.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsComFunc.h"
#include "TafSdcLib.h"
#include "TafApsSndCds.h"
#include "TafApsProcEpdszid.h"

#include "TafApsSndPpp.h"
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSASSISTANT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


VOS_UINT8                               g_ucApsInitFlg      = VOS_FALSE;
APS_PDP_MDF_REQ_ST                     *g_PdpModifyReqTable = VOS_NULL_PTR;
TAF_PDP_TABLE_STRU                     *g_TafCidTab         = VOS_NULL_PTR;
APS_PDP_CONTEXT_ENTITY_ST              *g_PdpEntity         = VOS_NULL_PTR;
TAF_PS_ANSWER_MODE_STRU                 g_PsAnsMode;

TAF_APS_CID_IMS_CFG_TBL_STRU          g_stCidImsCfgTable;



/* 终端可配置需求:2G拨号请求禁止Spare_bit3等参数 */
VOS_UINT8   g_ucDisable2GR5QosExt;

/*Mean throughput定制 */
VOS_UINT8   g_ucMeanThrough;

/* WINS可配置需求 */
VOS_UINT8   g_ApsWins;

/*WIN7 NDIS特性新增:用于保存^AUTHDATA命令的鉴权数据*/
TAF_NDIS_AUTHDATA_TABLE_STRU            *g_ApsNdisAuthdataTab = VOS_NULL_PTR;

HTIMER                                  g_hGprsDataReqTimer = VOS_NULL_PTR;
TAF_APS_GPRS_DATA_STRU                  g_stGprsDataReq = {0};


/*****************************************************************************
   3 函数实现
*****************************************************************************/

VOS_VOID Aps_Init(VOS_VOID)
{
    APS_NORM_LOG("APS INIT 1 begin...");

    /*若APS已经初始化,则直接返回*/
    if (VOS_TRUE == g_ucApsInitFlg)
    {
        return;
    }

    g_ucApsInitFlg                  = VOS_TRUE;


    TAF_APS_InitTask();



    /*申请内存,包括以下各全局数据: */
    g_PdpModifyReqTable
        = (APS_PDP_MDF_REQ_ST *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                             (TAF_APS_MAX_PDPID)*(sizeof(APS_PDP_MDF_REQ_ST)));
    if ( VOS_NULL_PTR == g_PdpModifyReqTable )
    {
        APS_ERR_LOG("PS_MEM_ALLOC err!");
        return;
    }

    g_TafCidTab
        = (TAF_PDP_TABLE_STRU *)PS_MEM_ALLOC( WUEPS_PID_TAF,
                                             ((TAF_MAX_CID +1)*(sizeof(TAF_PDP_TABLE_STRU))));
    if ( VOS_NULL_PTR == g_TafCidTab )
    {
        Aps_GlobVarFree();
        APS_ERR_LOG("PS_MEM_ALLOC err!");
        return;
    }

    g_PdpEntity
        = (APS_PDP_CONTEXT_ENTITY_ST *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                   ((TAF_APS_MAX_PDPID)*(sizeof(APS_PDP_CONTEXT_ENTITY_ST))));

    if ( VOS_NULL_PTR == g_PdpEntity )
    {
        Aps_GlobVarFree();
        APS_ERR_LOG("PS_MEM_ALLOC err!");
        return;
    }

    g_ApsNdisAuthdataTab = (TAF_NDIS_AUTHDATA_TABLE_STRU *)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ((TAF_MAX_CID + 1)* (sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU))));
    if ( VOS_NULL_PTR == g_ApsNdisAuthdataTab )
    {
        Aps_GlobVarFree();
        APS_ERR_LOG("VOS_MemAlloc for g_ApsNdisAuthdataTab err!");
        return;
    }

    PS_MEM_SET(&g_stCidImsCfgTable, 0x00, sizeof(g_stCidImsCfgTable));

    /*读取PDP Profile及可配置需求的NV数据*/
    Aps_DbInit();

    /*状态机初始化*/
    Aps_PdpEntityInit();

    APS_NORM_LOG("APS INIT 1 OK.");

    /* DMT测试桩 */
    TAF_APS_SetApsDmtTestStub(VOS_FALSE);

    return;
}


VOS_VOID    Aps_GlobVarFree(        VOS_VOID    )
{
    APS_NORM_LOG("APS Globle Variable Mem Free begin:");

    /*APS_PDP_MDF_REQ_ST            g_PdpModifyReqTable[APS_MAX_PDP_NUM + 1 ];*/
    if ( VOS_NULL_PTR != g_PdpModifyReqTable )
    {
        (VOS_VOID)APS_MEM_FREE(g_PdpModifyReqTable);
        g_PdpModifyReqTable         = VOS_NULL_PTR;
        APS_NORM_LOG("Aps_GlobVarFree g_PdpModifyReqTable is freed !");
    }

    /*TAF_PDP_TABLE_STRU            g_TafCidTab[TAF_MAX_CID + 1];*/
    if ( VOS_NULL_PTR != g_TafCidTab )
    {
        (VOS_VOID)APS_MEM_FREE(g_TafCidTab);
        g_TafCidTab                 = VOS_NULL_PTR;
        APS_NORM_LOG("Aps_GlobVarFree g_TafCidTab is freed !");
    }

    /*APS_PDP_CONTEXT_ENTITY_ST     g_PdpEntity[APS_MAX_PDP_NUM +1];*/
    if ( VOS_NULL_PTR != g_PdpEntity )
    {
        (VOS_VOID)APS_MEM_FREE(g_PdpEntity);
        g_PdpEntity                 = VOS_NULL_PTR;
        APS_NORM_LOG("Aps_GlobVarFree g_PdpEntity is freed !");
    }

    /*清APS的初始化标识*/
    g_ucApsInitFlg                  = VOS_FALSE;

    APS_NORM_LOG("APS Globle Variable Mem Free end.");

    return  ;
}


VOS_VOID Aps_DbInit( VOS_VOID )
{
    VOS_UINT16                          usDataLen;
    TAF_PS_ANSWER_MODE_STRU             stTmpTelePara;


    stTmpTelePara.enAnsMode  = TAF_PDP_ANSWER_MODE_MANUAL;
    stTmpTelePara.enAnsType  = TAF_PDP_ANSWER_TYPE_REJECT;
    stTmpTelePara.usClientId = 0;


    /*初始化PDP全局数据表*/
    Aps_PdpTabInit();

    /* 初始化g_ApsNdisAuthdataTab列表 */
    Aps_AuthdataTabInit();

    /*初始化自动应答参数*/
    /*从NVIM中读取g_TafTelePara*/
    usDataLen   = sizeof(TAF_PS_ANSWER_MODE_STRU);     /*读取长度*/

    if (NV_OK != NV_Read(en_NV_Item_PS_TelePara, (VOS_VOID*)&stTmpTelePara, usDataLen))
    {
        /*读取失败赋默认值*/
        g_PsAnsMode.enAnsMode           = TAF_PDP_ANSWER_MODE_MANUAL;
        g_PsAnsMode.enAnsType           = TAF_PDP_ANSWER_TYPE_REJECT;
        g_PsAnsMode.usClientId          = 0;
    }
    else
    {
        g_PsAnsMode.enAnsMode           = stTmpTelePara.enAnsMode;
        g_PsAnsMode.enAnsType           = stTmpTelePara.enAnsType;
        g_PsAnsMode.usClientId          = stTmpTelePara.usClientId;
    }

    return;
}


VOS_VOID    Aps_Customize_WINS(VOS_VOID)
{
    WINS_CONFIG_STRU    stWins;
    VOS_UINT32          ulLength;

    ulLength = 0;


    stWins.ucStatus = VOS_FALSE;
    stWins.ucWins   = WINS_CONFIG_ENABLE;

    (VOS_VOID)NV_GetLength(en_NV_Item_WINS_Config, &ulLength);
    if (ulLength > sizeof(stWins))
    {
        return;
    }
    if(NV_OK != NV_Read(en_NV_Item_WINS_Config, &stWins, ulLength))
    {
        /* 若读取en_NV_Item_WINS失败，则默认WINS设置为使能 */
        g_ApsWins = WINS_CONFIG_ENABLE;
        return;
    }

    if (0 == stWins.ucStatus)
    {
        /* 若en_NV_Item_WINS未设置，则参考Q的实现，默认WINS设置为使能 */
        g_ApsWins = WINS_CONFIG_ENABLE;
    }
    else
    {
        /* 判断ucWins值的合法性 */
        if ((WINS_CONFIG_DISABLE != stWins.ucWins) && (WINS_CONFIG_ENABLE != stWins.ucWins))
        {
            /* 若ucWins非法，则默认WINS设置为使能 */
            g_ApsWins = WINS_CONFIG_ENABLE;
        }
        else
        {
            g_ApsWins = stWins.ucWins;
        }
    }

    return;
}




VOS_VOID Aps_Customize_APN(VOS_VOID)
{
    APS_APN_CUSTOMIZE_STRU                  stApnCustmize;
    VOS_UINT8                               ucCid;
    VOS_UINT8                               ucApnLen;
    VOS_UINT8                               ucApn;
    VOS_UINT32                              i;


    PS_MEM_SET(&stApnCustmize, 0x00, sizeof(stApnCustmize));


    /*读取APN可配置NV项*/
    if(NV_OK == NV_Read(en_NV_Item_APN_Customize, &stApnCustmize, sizeof(APS_APN_CUSTOMIZE_STRU)))
    {
        if(0 != stApnCustmize.ucStatus)
        {
            /* 获取APN长度 */
            ucApnLen = (VOS_UINT8)VOS_StrNLen((VOS_CHAR *)stApnCustmize.aucApn, TAF_MAX_APN_LEN + 1);
            if ((0 == ucApnLen) || (ucApnLen > TAF_MAX_APN_LEN))
            {
                TAF_LOG1(WUEPS_PID_TAF,
                        TAF_APS,
                        PS_LOG_LEVEL_WARNING,
                        "Aps_Customize_APN:WARNING:ucApnLen is Abnormal,len :",
                        ucApnLen );
                return;
            }

            for (i=0;i < ucApnLen;i++)
            {
                ucApn = UPCASE(stApnCustmize.aucApn[i]);

                if((0 == i) || ((ucApnLen - 1) == i))
                {
                    if ( ! ((('A' <= ucApn ) && ('Z' >= ucApn)) ||
                             (('0' <= ucApn ) && ('9' >= ucApn))))
                    {
                        APS_WARN_LOG ("Invalid begin/end character in APN");
                        return;
                    }
                }
                else
                {
                    /* 检查字符的合法性 */
                    if ( ! ((('A' <= ucApn ) && ('Z' >= ucApn)) ||
                            (('0' <= ucApn ) && ('9' >= ucApn)) ||
                            ('-' == ucApn) ||
                            ('.' == ucApn)))
                    {
                        APS_WARN_LOG("Invalid character in APN");
                        return;
                    }
                }
            }

            for (ucCid = 1; ucCid <= TAF_MAX_CID; ucCid++)
            {
                /* 将定制的APN赋给g_TafCidTab结构体 */
                g_TafCidTab[ucCid].CidTab.stApn.ucLength = ucApnLen;
                (VOS_VOID)VOS_MemCpy(g_TafCidTab[ucCid].CidTab.stApn.aucValue,
                           stApnCustmize.aucApn,
                           ucApnLen);

                /*若已经定义了PDP上下文*/
                if((VOS_TRUE == g_TafCidTab[ucCid].usNvFlag) && (VOS_TRUE == g_TafCidTab[ucCid].ucUsed))
                {
                    /* 无需设置标志位 */
                }
                else
                {
                    /* 设置相应标志位 */
                    g_TafCidTab[ucCid].usNvFlag = VOS_TRUE;
                    g_TafCidTab[ucCid].ucUsed   = VOS_TRUE;
                }
            }
        }
    }
    return;

}

VOS_VOID Aps_Customize_TrafficClass(VOS_VOID)
{
    VOS_UINT8                               ucCid;
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU         stTrafficClass;
    VOS_UINT8                               ucCustomize = VOS_ERR;   /* 是否定制的标记 */
    VOS_UINT32                              ulLength;

    /* 由于定制的Traffic Class为如下值:
        0：subscribed value
        1: Conversational class
        2: Streaming Class
        3: Interactive Class
        4: Background Calass

        而g_TafCidTab中存储的Traffic Class的取值则为:
        0: Conversational class
        1: Streaming Class
        2: Interactive Class
        3: Background Calass
        4：subscribed value

        故在对g_TafCidTab赋值时，须将定制NV项中的Traffic Class转换为g_TafCidTab中的合法值
     */
    VOS_UINT8                               ucRealTafficClass;


    stTrafficClass.ucStatus       = VOS_FALSE;
    stTrafficClass.ucTrafficClass = 0;
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_TRAFFIC_CLASS_Type, &ulLength);

    /*读取Traffic Class可配置NV项*/
    if(NV_OK == NV_Read(en_NV_Item_TRAFFIC_CLASS_Type,
                        &stTrafficClass,
                        ulLength))
    {
        if(0 != stTrafficClass.ucStatus)
        {
            switch (stTrafficClass.ucTrafficClass)
            {
                case APS_3GPP_QOS_TRAFFIC_CLASS_SUBSCRIBE:
                    ucRealTafficClass = 4;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL:
                    ucRealTafficClass = 0;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING:
                    ucRealTafficClass = 1;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE:
                    ucRealTafficClass = 2;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND:
                    ucRealTafficClass = 3;
                    break;
                default :
                    /* 若定制的traffic class错误，则采用默认的Interactive类型 */
                    ucRealTafficClass = 4;
                    break;
            }

            for (ucCid = 1; ucCid <= TAF_MAX_CID; ucCid++)
            {
                /* 设置为定制的Traffic Class */
                g_TafCidTab[ucCid].QosTab.ucTrafficClass = ucRealTafficClass;

                /*若已经定义了QOS*/
                if((VOS_TRUE == g_TafCidTab[ucCid].usNvFlag) && (VOS_TRUE == g_TafCidTab[ucCid].ucQosTabFlag))
                {
                    /* 无需设置标志位 */
                }
                else
                {
                    /* 设置相应标志位 */
                    g_TafCidTab[ucCid].usNvFlag     = VOS_TRUE;
                    g_TafCidTab[ucCid].ucQosTabFlag = VOS_TRUE;
                }
            }

            /* 置定制标记为VOS_OK */
            ucCustomize = VOS_OK;
        }
    }

    if (VOS_ERR == ucCustomize)
    {
        /* 参考Q实现，若未定制Traffic Class,则用Interactive类型发起PDP激活请求 */
        for (ucCid = 1; ucCid <= TAF_MAX_CID; ucCid++)
        {

            /* 将Traffic Class置为subscribed类型 */
            g_TafCidTab[ucCid].QosTab.ucTrafficClass = 4;  /* 4: subscribed value */



            /*若已经定义了QOS*/
            if((VOS_TRUE == g_TafCidTab[ucCid].usNvFlag) && (VOS_TRUE == g_TafCidTab[ucCid].ucQosTabFlag))
            {
                /* 无需设置标志位 */
            }
            else
            {
                /* 设置相应标志位 */
                g_TafCidTab[ucCid].usNvFlag     = VOS_TRUE;
                g_TafCidTab[ucCid].ucQosTabFlag = VOS_TRUE;
            }
        }
    }

    return;

}


VOS_VOID Aps_Customize_MeanThrough(VOS_VOID)
{
    APS_MEAN_THROUGH_CUSTOMIZE_STRU     stMeanThrough;
    VOS_UINT32                          ulLength;


    ulLength                    = 0;
    stMeanThrough.ucStatus      = VOS_FALSE;
    stMeanThrough.ucMeanThrough = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MEAN_THROUGHPUT, &ulLength);

    /*读取APN可配置NV项*/
    if(NV_OK == NV_Read(en_NV_Item_MEAN_THROUGHPUT,
                        &stMeanThrough,
                        ulLength))
    {
        if(1 == stMeanThrough.ucStatus)
        {
            g_ucMeanThrough = stMeanThrough.ucMeanThrough;
        }
        else
        {
            g_ucMeanThrough = APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT;
        }

    }
    else
    {
        g_ucMeanThrough = APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT;
    }
    return;

}


VOS_VOID Aps_Customize_Disable2GR5QosExt(VOS_VOID)
{
    APS_2G_DISABLE_BIT3_CUSTOMIZE_STRU  stDisable2GBit3;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    stDisable2GBit3.ucStatus        = 0;
    stDisable2GBit3.ucDisable2GBit3 = 0;


    (VOS_VOID)NV_GetLength(en_NV_Item_2G_DISABLE_SPARE_BIT3, &ulLength);

    /*读取2G下拨号请求禁止Spare_bit3等参数的可配置NV项*/
    if(NV_OK == NV_Read(en_NV_Item_2G_DISABLE_SPARE_BIT3,
                        &stDisable2GBit3,
                        ulLength))
    {
        if (1 == stDisable2GBit3.ucStatus)
        {
            g_ucDisable2GR5QosExt = stDisable2GBit3.ucDisable2GBit3;
        }
        else
        {
            g_ucDisable2GR5QosExt = APS_2G_BIT3_DISABLE;
        }
    }
    else
    {
        g_ucDisable2GR5QosExt = APS_2G_BIT3_DISABLE;
    }
    return;
}


/*****************************************************************************
 Prototype      : Aps_InitCustomizeData()
 Description    : 根据定制的要求，初始化相应数据
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-07-11
    Author      : L47619
    Modification: 可定制需求
*****************************************************************************/
VOS_VOID    Aps_InitCustomizeData(VOS_VOID)
{
    /* 可定制需求: 单板默认APN设置 */
    Aps_Customize_APN();

    /* 可定制需求: Traffic Class定制 */
    Aps_Customize_TrafficClass();

    /* 可定制需求: Mean Throughput 定制 */
    Aps_Customize_MeanThrough();

    /* 可定制需求: 2G拨号请求禁止Spare_bit3等参数 */
    Aps_Customize_Disable2GR5QosExt();

    /* 可定制需求: WINS是否使能定制 */
    Aps_Customize_WINS();

    return;
}


VOS_VOID TAF_APS_ConvertLocalPdpTab2NvPdpTab(
    CONST TAF_PDP_TABLE_STRU           *pstLocalPdpTab,
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTab
)
{
    /* CID */
    pstNvPdpTab->ucUsed                     = pstLocalPdpTab->ucUsed;
    pstNvPdpTab->ucCid                      = pstLocalPdpTab->ucCid;
    pstNvPdpTab->ucPriCidFlag               = pstLocalPdpTab->ucPriCidFlag;
    pstNvPdpTab->ucPriCid                   = pstLocalPdpTab->ucPriCid;
    pstNvPdpTab->CidTab.enPdpType           = pstLocalPdpTab->CidTab.stPdpAddr.enPdpType;
    Taf_IpAddr2LenStr(pstLocalPdpTab->CidTab.stPdpAddr.aucIpv4Addr, pstNvPdpTab->CidTab.aucPdpAddr);
    PS_MEM_CPY(&pstNvPdpTab->CidTab.stApn, &pstLocalPdpTab->CidTab.stApn, sizeof(TAF_PDP_APN_STRU));
    pstNvPdpTab->CidTab.enPdpDcomp          = pstLocalPdpTab->CidTab.enPdpDcomp;
    pstNvPdpTab->CidTab.enPdpHcomp          = pstLocalPdpTab->CidTab.enPdpHcomp;
    pstNvPdpTab->CidTab.enIpv4AddrAlloc     = pstLocalPdpTab->CidTab.enIpv4AddrAlloc;
    pstNvPdpTab->CidTab.enEmergencyInd      = pstLocalPdpTab->CidTab.enEmergencyInd;
    pstNvPdpTab->CidTab.enPcscfDiscovery    = pstLocalPdpTab->CidTab.enPcscfDiscovery;
    pstNvPdpTab->CidTab.enImCnSignalFlg     = pstLocalPdpTab->CidTab.enImCnSignalFlg;

    /* EPS QOS */
    if (VOS_TRUE == pstLocalPdpTab->ucEpsQosInfoFlg)
    {
        pstNvPdpTab->ucEpsQosInfoFlg        = pstLocalPdpTab->ucEpsQosInfoFlg;
        PS_MEM_CPY(&pstNvPdpTab->stEpsQosInfo, &pstLocalPdpTab->stEpsQosInfo, sizeof(TAF_EPS_QOS_STRU));
    }

    /* UMTS QOS */
    if (VOS_TRUE == pstLocalPdpTab->ucQosTabFlag)
    {
        pstNvPdpTab->ucQosTabFlag           = pstLocalPdpTab->ucQosTabFlag;
        PS_MEM_CPY(&pstNvPdpTab->QosTab, &pstLocalPdpTab->QosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* MIN UTMS QOS */
    if (VOS_TRUE == pstLocalPdpTab->ucMinQosFlag)
    {
        pstNvPdpTab->ucMinQosFlag           = pstLocalPdpTab->ucMinQosFlag;
        PS_MEM_CPY(&pstNvPdpTab->MinQosTab, &pstLocalPdpTab->MinQosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* TFT */
    pstNvPdpTab->ucPfTabFlag               = pstLocalPdpTab->ucPfTabFlag;
    pstNvPdpTab->ucPfNum                    = pstLocalPdpTab->ucPfNum;
    PS_MEM_CPY(&pstNvPdpTab->astPfTab[0], &pstLocalPdpTab->astPfTab[0], sizeof(TAF_PDP_PF_STRU) * TAF_MAX_SDF_PF_NUM);

    /* DNS */
    pstNvPdpTab->ucDnsFlag                  = pstLocalPdpTab->ucDnsFlag;
    pstNvPdpTab->DnsTab.bitOpPrimDnsAddr    = pstLocalPdpTab->DnsTab.bitOpPrimDnsAddr;
    pstNvPdpTab->DnsTab.bitOpSecDnsAddr     = pstLocalPdpTab->DnsTab.bitOpSecDnsAddr;
    PS_MEM_CPY(pstNvPdpTab->DnsTab.aucPrimDnsAddr, pstLocalPdpTab->DnsTab.aucPrimDnsAddr, sizeof(pstNvPdpTab->DnsTab.aucPrimDnsAddr));
    PS_MEM_CPY(pstNvPdpTab->DnsTab.aucSecDnsAddr, pstLocalPdpTab->DnsTab.aucSecDnsAddr, sizeof(pstNvPdpTab->DnsTab.aucSecDnsAddr));

    /* NV FLAG */
    pstNvPdpTab->usNvFlag                   = pstLocalPdpTab->usNvFlag;

    return;
}


VOS_VOID TAF_APS_ConvertNvPdpTab2LocalPdpTab(
    CONST TAF_NV_PDP_TABLE_STRU        *pstNvPdpTab,
    TAF_PDP_TABLE_STRU                 *pstLocalPdpTab
)
{
    /* CID */
    pstLocalPdpTab->ucUsed                      = pstNvPdpTab->ucUsed;
    pstLocalPdpTab->ucCid                       = pstNvPdpTab->ucCid;
    pstLocalPdpTab->ucPriCidFlag                = pstNvPdpTab->ucPriCidFlag;
    pstLocalPdpTab->ucPriCid                    = pstNvPdpTab->ucPriCid;
    pstLocalPdpTab->CidTab.stPdpAddr.enPdpType  = pstNvPdpTab->CidTab.enPdpType;
    Taf_LenStr2IpAddr(pstNvPdpTab->CidTab.aucPdpAddr, pstLocalPdpTab->CidTab.stPdpAddr.aucIpv4Addr);
    PS_MEM_CPY(&pstLocalPdpTab->CidTab.stApn, &pstNvPdpTab->CidTab.stApn, sizeof(TAF_PDP_APN_STRU));
    pstLocalPdpTab->CidTab.enPdpDcomp           = pstNvPdpTab->CidTab.enPdpDcomp;
    pstLocalPdpTab->CidTab.enPdpHcomp           = pstNvPdpTab->CidTab.enPdpHcomp;
    pstLocalPdpTab->CidTab.enIpv4AddrAlloc      = pstNvPdpTab->CidTab.enIpv4AddrAlloc;
    pstLocalPdpTab->CidTab.enEmergencyInd       = pstNvPdpTab->CidTab.enEmergencyInd;
    pstLocalPdpTab->CidTab.enPcscfDiscovery     = pstNvPdpTab->CidTab.enPcscfDiscovery;
    pstLocalPdpTab->CidTab.enImCnSignalFlg      = pstNvPdpTab->CidTab.enImCnSignalFlg;

    /* EPS QOS */
    if (VOS_TRUE == pstNvPdpTab->ucEpsQosInfoFlg)
    {
        pstLocalPdpTab->ucEpsQosInfoFlg         = pstNvPdpTab->ucEpsQosInfoFlg;
        PS_MEM_CPY(&pstLocalPdpTab->stEpsQosInfo, &pstNvPdpTab->stEpsQosInfo, sizeof(TAF_EPS_QOS_STRU));
    }

    /* UMTS QOS */
    if (VOS_TRUE == pstNvPdpTab->ucQosTabFlag)
    {
        pstLocalPdpTab->ucQosTabFlag            = pstNvPdpTab->ucQosTabFlag;
        PS_MEM_CPY(&pstLocalPdpTab->QosTab, &pstNvPdpTab->QosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* MIN UTMS QOS */
    if (VOS_TRUE == pstNvPdpTab->ucMinQosFlag)
    {
        pstLocalPdpTab->ucMinQosFlag            = pstNvPdpTab->ucMinQosFlag;
        PS_MEM_CPY(&pstLocalPdpTab->MinQosTab, &pstNvPdpTab->MinQosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* TFT */
    pstLocalPdpTab->ucPfTabFlag                 = pstNvPdpTab->ucPfTabFlag;
    pstLocalPdpTab->ucPfNum                     = pstNvPdpTab->ucPfNum;
    PS_MEM_CPY(&pstLocalPdpTab->astPfTab[0], &pstNvPdpTab->astPfTab[0], sizeof(TAF_PDP_PF_STRU) * TAF_MAX_SDF_PF_NUM);

    /* DNS */
    pstLocalPdpTab->ucDnsFlag                   = pstNvPdpTab->ucDnsFlag;
    pstLocalPdpTab->DnsTab.bitOpPrimDnsAddr     = pstNvPdpTab->DnsTab.bitOpPrimDnsAddr;
    pstLocalPdpTab->DnsTab.bitOpSecDnsAddr      = pstNvPdpTab->DnsTab.bitOpSecDnsAddr;
    PS_MEM_CPY(pstLocalPdpTab->DnsTab.aucPrimDnsAddr, pstNvPdpTab->DnsTab.aucPrimDnsAddr, sizeof(pstLocalPdpTab->DnsTab.aucPrimDnsAddr));
    PS_MEM_CPY(pstLocalPdpTab->DnsTab.aucSecDnsAddr, pstNvPdpTab->DnsTab.aucSecDnsAddr, sizeof(pstLocalPdpTab->DnsTab.aucSecDnsAddr));

    /* NV FLAG */
    pstLocalPdpTab->usNvFlag                    = pstNvPdpTab->usNvFlag;

    return;
}


VOS_VOID    Aps_PdpTabInit(VOS_VOID)
{
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTable = VOS_NULL_PTR;
    VOS_UINT16                          usIndex;
    VOS_UINT16                          usNvId;

    if (VOS_NULL_PTR == g_TafCidTab)
    {
        APS_ERR_LOG("ERROR:Aps_PdpTabInit g_TafCidTab is NUILL PTR!");
        return;
    }

    pstNvPdpTable = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstNvPdpTable)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_PdpTabInit: Alloc memory fail!");
        return;
    }

    /* 对表项的占用位清除 */
    for (usIndex = 0; usIndex <= TAF_MAX_CID; usIndex++)
    {
        /* 清空g_TafCidTab */
        PS_MEM_SET(&g_TafCidTab[usIndex], 0, sizeof(TAF_PDP_TABLE_STRU));

        g_TafCidTab[usIndex].ucUsed         = VOS_FALSE;
        g_TafCidTab[usIndex].ucCid          = (VOS_UINT8)usIndex;
        g_TafCidTab[usIndex].ucEpsQosInfoFlg = VOS_FALSE;
        g_TafCidTab[usIndex].ucQosTabFlag   = VOS_FALSE;
        g_TafCidTab[usIndex].ucMinQosFlag   = VOS_FALSE;
        g_TafCidTab[usIndex].ucPfTabFlag    = VOS_FALSE;
        g_TafCidTab[usIndex].ucDnsFlag      = VOS_FALSE;
        g_TafCidTab[usIndex].ucPriCidFlag   = VOS_FALSE;

        /* 初始化PDP基本信息 */
        g_TafCidTab[usIndex].CidTab.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
        g_TafCidTab[usIndex].CidTab.stApn.ucLength          = 0;
        g_TafCidTab[usIndex].CidTab.enPdpDcomp              = TAF_PDP_D_COMP_OFF;
        g_TafCidTab[usIndex].CidTab.enPdpHcomp              = TAF_PDP_H_COMP_OFF;

        /* 初始化Qos表 */
        g_TafCidTab[usIndex].QosTab.ucTrafficClass          = 4;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucDeliverOrder          = 2;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucDeliverErrSdu         = 3;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.usMaxSduSize            = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulMaxBitUl              = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulMaxBitDl              = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucResidualBer           = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucSduErrRatio           = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.usTransDelay            = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucTraffHandlePrior      = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulGuarantBitUl          = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulGuarantBitDl          = 0;    /*Subscribed value*/

    }

    /* 读取NV(0-11), 实现NV结构->本地结构转换 */
    for (usIndex = 0; usIndex <= TAF_MAX_CID_NV; usIndex++)
    {
        PS_MEM_SET(pstNvPdpTable, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));

        usNvId = en_NV_Item_Taf_PdpPara_0 + usIndex;
        if (NV_OK != NV_Read(usNvId, pstNvPdpTable, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_PdpTabInit: Read NV fail!");
            continue;
        }

        /* NV PDP参数表结构->LOCAL PDP参数表结构 */
        TAF_APS_ConvertNvPdpTab2LocalPdpTab(pstNvPdpTable, TAF_APS_GetTafCidInfoAddr(usIndex));
    }

    /* 初始化可配置需求的相应数据 */
    Aps_InitCustomizeData();

    /* 释放临时内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstNvPdpTable);

    return;
}



VOS_VOID    Aps_AuthdataTabInit(VOS_VOID)
{
    VOS_UINT16                              usIndex;
    VOS_UINT16                              usDataLen;
    TAF_NDIS_AUTHDATA_TABLE_STRU            TmpAuthdataTab;


    PS_MEM_SET(&TmpAuthdataTab, 0x00, sizeof(TmpAuthdataTab));


    if (VOS_NULL_PTR == g_ApsNdisAuthdataTab)
    {
        APS_ERR_LOG("Aps_AuthdataTabInit:ERROR:g_ApsNdisAuthdataTab is NUILL PTR!");
        return;
    }

    usDataLen = sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU);

    for (usIndex = 0; usIndex <= TAF_MAX_CID; usIndex++)
    {
        /*清空g_ApsNdisAuthdataTab*/
        PS_MEM_SET(&g_ApsNdisAuthdataTab[usIndex], 0, usDataLen);

        g_ApsNdisAuthdataTab[usIndex].ucUsed                    = VOS_FALSE;

        /* 初始化鉴权信息 */
        g_ApsNdisAuthdataTab[usIndex].stAuthData.enAuthType     = TAF_PDP_AUTH_TYPE_NONE;
        g_ApsNdisAuthdataTab[usIndex].stAuthData.aucPlmn[0]     = 0;
        g_ApsNdisAuthdataTab[usIndex].stAuthData.aucPassword[0] = 0;
        g_ApsNdisAuthdataTab[usIndex].stAuthData.aucUsername[0] = 0;
    }

    for (usIndex = 0; usIndex <= TAF_MAX_CID_NV; usIndex++)
    {
        /*total 11 records*/
        if (NV_OK == NV_Read((NV_ID_ENUM_U16)((en_NV_Item_NDIS_Authdata_1 + usIndex) - 1),
                              (VOS_VOID*)&TmpAuthdataTab,
                              usDataLen))
        {
            /*所对应的NV项是否曾在NV Table中设置过*/
            if (VOS_TRUE == TmpAuthdataTab.ucUsed)
            {
                /*保存NV内容到g_ApsNdisAuthdataTab中*/
                g_ApsNdisAuthdataTab[usIndex] = TmpAuthdataTab;
            }
        }
    }
}

/*****************************************************************************
 Prototype      : Aps_PdpEntityInit()
 Description    : 初始化PDP状态机
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : NO
 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_PdpEntityInit(VOS_VOID)
{
    VOS_UINT8           ucTmpPdpId;

    for(ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++ )
    {
        Aps_ReleaseApsResource(ucTmpPdpId);
    }


    return;
}



VOS_VOID    Aps_ReleaseSndcpResource    (   VOS_UINT8   ucPdpId )
{
    if (TAF_APS_FAIL == Aps_SmMsgModSnDeActInd ( ucPdpId ))
    {
        APS_ERR_LOG("Snd Sndcp Deact Msg Fail !");
    }

    /* SNDCP激活标记置为INACTIVE */
    g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;

    return;
}




VOS_VOID    Aps_ReleaseApsResource  (   VOS_UINT8   ucPdpId )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_ReleaseEpdszidResource();

    /* disabe dormant timer feature  */
    TAF_APS_SetSocmDormantTiLen(0);

    TAF_APS_SetUserCfgDormTiVal(0);
#endif

    PS_MEM_SET(&g_PdpEntity[ucPdpId], 0x00, sizeof(APS_PDP_CONTEXT_ENTITY_ST));

    g_PdpEntity[ucPdpId].ulUsedFlg              = VOS_FALSE;
    g_PdpEntity[ucPdpId].ucPdpId                = ucPdpId;
    g_PdpEntity[ucPdpId].stClientInfo.ucCid     = TAF_APS_INVALID_CID;

    g_PdpEntity[ucPdpId].stCdataInfo.enLastReOrigErr = TAF_XCC_FAIL_LAYER_BUTT;

    g_PdpModifyReqTable[ucPdpId].Op_Spare            = APS_MDF_NO_QOS;

    return;
}



VOS_VOID Aps_3GQos2AppQos_ForMaxBitRateForUp(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucMaxBitRateForUpExt)
      && (0 == pApsQos->ucMaxBitRateForUpExt_2) )
    {
        /*  In MS to network direction:
            0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
            In network to MS direction:
            0 0 0 0 0 0 0 0 Reserved
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
            0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

            0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
            0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

            1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
            1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

            1 1 1 1 1 1 1 1 0kbps
        */
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucMaxBitRateForUp)
        {
            pTafQos->ulMaxBitUl = APS_APP_QOS_BIT_0KBPS;
        }
        else if( pApsQos->ucMaxBitRateForUp >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulMaxBitUl
                =   ((pApsQos->ucMaxBitRateForUp - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucMaxBitRateForUp >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulMaxBitUl
                =   ((pApsQos->ucMaxBitRateForUp - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulMaxBitUl = pApsQos->ucMaxBitRateForUp;
        }
    }
    else if ( (0 != pApsQos->ucMaxBitRateForUpExt)
           && (0 == pApsQos->ucMaxBitRateForUpExt_2) )
    {
        /*In MS to network direction and in network to MS direction:
          0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for uplink in octet 9.

          For all other values: Ignore the value indicated by the Maximum bit rate for uplink in octet 9
          and use the following value:
          0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
          0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

          0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
          1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

          1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
          1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
         */
        if (pApsQos->ucMaxBitRateForUpExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucMaxBitRateForUpExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS));
        }
        else
        {
            /* 若大于APS_3GPP_QOS_BIT_256MBPS，则赋值为256000 */
            pTafQos->ulMaxBitUl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucMaxBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucMaxBitRateForUpExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* 若大于APS_APP_QOS_BIT_10GBPS，则赋值为10000000 */
            pTafQos->ulMaxBitUl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}


VOS_VOID Aps_3GQos2AppQos_ForMaxBitRateForDown(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucMaxBitRateForDownExt)
      && (0 == pApsQos->ucMaxBitRateForDownExt_2) )
    {
        /*usMaxBitDl*/
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucMaxBitRateForDown )
        {
            pTafQos->ulMaxBitDl = APS_APP_QOS_BIT_0KBPS;
        }
        else if( pApsQos->ucMaxBitRateForDown >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulMaxBitDl
                =   ((pApsQos->ucMaxBitRateForDown - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucMaxBitRateForDown >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulMaxBitDl
                =   ((pApsQos->ucMaxBitRateForDown - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulMaxBitDl = pApsQos->ucMaxBitRateForDown;
        }
    }
    else if ( (0 != pApsQos->ucMaxBitRateForDownExt)
           && (0 == pApsQos->ucMaxBitRateForDownExt_2) )
    {
        /*In MS to network direction and in network to MS direction:
          0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9.

          For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9
          and use the following value:
          0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
          0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

          0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
          1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

          1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
          1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
        */
        if (pApsQos->ucMaxBitRateForDownExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucMaxBitRateForDownExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS));
        }
        else
        {
            /* 若大于APS_3GPP_QOS_BIT_256MBPS，则赋值为256000 */
            pTafQos->ulMaxBitDl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucMaxBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucMaxBitRateForDownExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* 若大于APS_APP_QOS_BIT_10GBPS，则赋值为10000000 */
            pTafQos->ulMaxBitDl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}


VOS_VOID Aps_3GQos2AppQos_ForGuarantBitRateForUp(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucGuarantBitRateForUpExt)
      && (0 == pApsQos->ucGuarantBitRateForUpExt_2) )
    {
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucGuarantBitRateForUp)
        {
            pTafQos->ulGuarantBitUl = APS_APP_QOS_BIT_0KBPS;
        }
        else if ( pApsQos->ucGuarantBitRateForUp >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulGuarantBitUl
                =   ((pApsQos->ucGuarantBitRateForUp - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucGuarantBitRateForUp >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulGuarantBitUl
                =   ((pApsQos->ucGuarantBitRateForUp - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulGuarantBitUl = pApsQos->ucGuarantBitRateForUp;
        }
    }
    else if ( (0 != pApsQos->ucGuarantBitRateForUpExt)
           && (0 == pApsQos->ucGuarantBitRateForUpExt_2) )
    {
        /*  Guaranteed bit rate for downlink (extended), octet 16
            Bits
            8 7 6 5 4 3 2 1
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for downlink in octet 13.

            For all other values: Ignore the value indicated by the Guaranteed bit rate for downlink in octet 9
            and use the following value:
            0 0 0 0 0 0 0 1 The guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
            0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

            0 1 0 0 1 0 1 1 The guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
            1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

            1 0 1 1 1 0 1 1 The guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
            1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForUpExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucGuarantBitRateForUpExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucGuarantBitRateForUpExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulGuarantBitUl =
                APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS);
        }
        else if (pApsQos->ucGuarantBitRateForUpExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulGuarantBitUl =
                APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS);
        }
        else
        {
            /* 若大于APS_3GPP_QOS_BIT_256MBPS，则赋值为256000 */
            pTafQos->ulGuarantBitUl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucGuarantBitRateForUpExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* 若大于APS_APP_QOS_BIT_10GBPS，则赋值为10000000 */
            pTafQos->ulGuarantBitUl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}


VOS_VOID Aps_3GQos2AppQos_ForGuarantBitRateForDown(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucGuarantBitRateForDownExt)
      && (0 == pApsQos->ucGuarantBitRateForDownExt_2) )
    {
        /*usGuarantBitDl*/
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucGuarantBitRateForDown)
        {
            pTafQos->ulGuarantBitDl = APS_APP_QOS_BIT_0KBPS;
        }
        else if( pApsQos->ucGuarantBitRateForDown >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulGuarantBitDl
                =   ((pApsQos->ucGuarantBitRateForDown - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucGuarantBitRateForDown >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulGuarantBitDl
                =   ((pApsQos->ucGuarantBitRateForDown - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulGuarantBitDl = pApsQos->ucGuarantBitRateForDown;
        }
    }
    else if ( (0 != pApsQos->ucGuarantBitRateForDownExt)
           && (0 == pApsQos->ucGuarantBitRateForDownExt_2) )
    {
        /*  Guaranteed bit rate for downlink (extended), octet 16
            Bits
            8 7 6 5 4 3 2 1
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for downlink in octet 13.

            For all other values: Ignore the value indicated by the Guaranteed bit rate for downlink in octet 9
            and use the following value:
            0 0 0 0 0 0 0 1 The guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
            0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

            0 1 0 0 1 0 1 1 The guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
            1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

            1 0 1 1 1 0 1 1 The guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
            1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForDownExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucGuarantBitRateForDownExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucGuarantBitRateForDownExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulGuarantBitDl =
                APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS);
        }
        else if (pApsQos->ucGuarantBitRateForDownExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulGuarantBitDl =
                APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS);
        }
        else
        {
            /* 若大于APS_3GPP_QOS_BIT_256MBPS，则赋值为256000 */
            pTafQos->ulGuarantBitDl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucGuarantBitRateForDownExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* 若大于APS_APP_QOS_BIT_10GBPS，则赋值为10000000 */
            pTafQos->ulGuarantBitDl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}


VOS_VOID Aps_3GQos2AppQos(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    /*ucTrafficClass*/
    /*
    In MS to network direction:
    0 0 0       Subscribed traffic class
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       Conversational class
    0 1 0       Streaming class
    0 1 1       Interactive class
    1 0 0       Background class
    1 1 1       Reserved
    */
    if ( APS_3GPP_QOS_TRAFFICCLASS_BOT == pApsQos->ucTrafficClass)
    {   /*网络不应该发0过来，若发来了，则认为0是最差的服务*/
        pTafQos->ucTrafficClass = APS_QOS_TRAFFIC_CLASS_BACKGROUND;
    }
    else
    {
        pTafQos->ucTrafficClass
            =   pApsQos->ucTrafficClass - APS_TRAFFICCLASS_APP3GPP_DIFF_VAL;
    }


    /*ucDeliverOrder*/
    /*
        In MS to network direction:
        0 0     Subscribed delivery order
        In network to MS direction:
        0 0     Reserved
        In MS to network direction and in network to MS direction:
        0 1     With delivery order ('yes')
        1 0     Without delivery order ('no')
        1 1     Reserved
        ~~~~~~~~~~~~~~~~~~~~~
        0 - no
        1 - yes
        2 - subscribed value.
    */
    if ((APS_3GPP_QOS_DELIVERORDER_BOT < pApsQos->ucDeliverOrder) &&
        (pApsQos->ucDeliverOrder < APS_3GPP_QOS_DELIVERORDER_TOP))
    {
        pTafQos->ucDeliverOrder
            =   APS_DELIVERORDER_APP3GPP_DIFF_VAL - pApsQos->ucDeliverOrder;
    }
    else
    {
        pTafQos->ucDeliverOrder = APS_APPQOS_DELIVERORDER_SUBSCRIB;
    }

    /*ucDeliverErrSdu*/
    /*
        In MS to network direction:
        0 0 0       Subscribed delivery of erroneous SDUs
        In network to MS direction:
        0 0 0       Reserved
        In MS to network direction and in network to MS direction:
        0 0 1       No detect ('-')
        0 1 0       Erroneous SDUs are delivered ('yes')
        0 1 1       Erroneous SDUs are not delivered ('no')
        1 1 1       Reserved
        ~~~~~~~~~~~~~~~~
        0 - no
        1 - yes
        2 - no detect
        3 - subscribed value
    */
    if ( pApsQos->ucDeliverOfErrSdu <= APS_3GPP_QOS_DELIVER_ERRSDU_TOP)
    {
        pTafQos->ucDeliverErrSdu
            =   APS_DELIVEROFERRSDU_APP3GPP_DIFF_VAL - pApsQos->ucDeliverOfErrSdu;
    }
    else
    {
        pTafQos->ucDeliverErrSdu = APS_APPQOS_DELIVEReRRSDU_SUBSCRIB;
    }

    /*usMaxSduSize*/
    
    if ( APS_3GPP_QOS_MAXSDUSIZE_1520OCTS == pApsQos->ucMaximSduSize )
    {
        pTafQos->usMaxSduSize = APS_APP_QOS_MAXSDUSIZE_1520OCTS;
    }
    else if ( APS_3GPP_QOS_MAXSDUSIZE_1510OCTS == pApsQos->ucMaximSduSize)
    {
        pTafQos->usMaxSduSize = APS_APP_QOS_MAXSDUSIZE_1510OCTS;
    }
    else if ( APS_3GPP_QOS_MAXSDUSIZE_1502OCTS == pApsQos->ucMaximSduSize)
    {
        pTafQos->usMaxSduSize = APS_APP_QOS_MAXSDUSIZE_1502OCTS;
    }
    else
    {
        pTafQos->usMaxSduSize = APS_3GPP_QOS_MAXSDUSIZE_GRANUL_10 * (pApsQos->ucMaximSduSize);
    }

    /*ulMaxBitUl*/
    Aps_3GQos2AppQos_ForMaxBitRateForUp(pApsQos, pTafQos);

    /*ulMaxBitDl*/
    Aps_3GQos2AppQos_ForMaxBitRateForDown(pApsQos, pTafQos);

    /*ucResidualBer*/
    /*
        In network to MS direction:
        0 0 0 0     Reserved
        In MS to network direction and in network to MS direction:
        The Residual BER value consists of 4 bits. The range is from 5*10-2 to 6*10-8.
        0 0 0 1     5*10-2
        0 0 1 0     1*10-2
        0 0 1 1     5*10-3
        0 1 0 0     4*10-3
        0 1 0 1     1*10-3
        0 1 1 0     1*10-4
        0 1 1 1     1*10-5
        1 0 0 0     1*10-6
        1 0 0 1     6*10-8
        1 1 1 1     Reserved
    */
    pTafQos->ucResidualBer = pApsQos->ucResidualBer;


    /*ucSduErrRatio*/
    /*
        In MS to network direction:
        0 0 0 0     Subscribed SDU error ratio
        In network to MS direction:
        0 0 0 0     Reserved
        In MS to network direction and in network to MS direction:
        The SDU error ratio value consists of 4 bits. The range is is from 1*10-1 to 1*10-6.
        0 0 0 1     1*10-2
        0 0 1 0     7*10-3
        0 0 1 1     1*10-3
        0 1 0 0     1*10-4
        0 1 0 1     1*10-5
        0 1 1 0     1*10-6
        0 1 1 1     1*10-1
        1 1 1 1     Reserved
    */
    pTafQos->ucSduErrRatio = pApsQos->ucSduErrRatio;


    /*usTransDelay*/
    /*
        In MS to network direction:
        0 0 0 0 0 0     Subscribed transfer delay
        In network to MS direction:
        0 0 0 0 0 0     Reserved
        In MS to network direction and in network to MS direction:

        0 0 0 0 0 1     The Transfer delay is binary coded in 6 bits, using a granularity of 10 ms
        0 0 1 1 1 1     giving a range of values from 10 ms to 150 ms in 10 ms increments

        0 1 0 0 0 0     The transfer delay is 200 ms + ((the binary coded value in 6 bits - 010000) * 50 ms)
        0 1 1 1 1 1     giving a range of values from 200 ms to 950 ms in 50ms increments

        1 0 0 0 0 0     The transfer delay is 1000 ms + ((the binary coded value in 6 bits - 100000) * 100 ms)
        1 1 1 1 1 0     giving a range of values from 1000 ms to 4000 ms in 100ms increments

        1 1 1 1 1 1     Reserved
    */
    if ( pApsQos->ucTransDelay >= APS_3GPP_QOS_TRANSDELAY_1000MS )
    {
        pTafQos->usTransDelay
            =   ((pApsQos->ucTransDelay - APS_3GPP_QOS_TRANSDELAY_1000MS)
              * APS_3GPP_QOS_TRANSDELAY_INC_100MS)
              + APS_APP_QOS_TRANSDELAY_1000MS;
    }
    else if ( pApsQos->ucTransDelay >= APS_3GPP_QOS_TRANSDELAY_200MS )
    {
        pTafQos->usTransDelay
            =   ((pApsQos->ucTransDelay - APS_3GPP_QOS_TRANSDELAY_200MS)
              * APS_3GPP_QOS_TRANSDELAY_INC_50MS)
              + APS_APP_QOS_TRANSDELAY_200MS;
    }
    else
    {
        pTafQos->usTransDelay
            =   pApsQos->ucTransDelay * APS_3GPP_QOS_TRANSDELAY_INC_10MS;
    }


    /*ucTraffHandlePrior;*/
    /*
        In MS to network direction:
        0 0     Subscribed traffic handling priority
        In network to MS direction:
        0 0     Reserved
        In MS to network direction and in network to MS direction:
        0 1     Priority level 1
        1 0     Priority level 2
        1 1     Priority level 3
    */
    pTafQos->ucTraffHandlePrior = pApsQos->ucTraffHandlPrior;


    /*ulGuarantBitUl;*/
    Aps_3GQos2AppQos_ForGuarantBitRateForUp(pApsQos, pTafQos);

    /*ulGuarantBitDl*/
    Aps_3GQos2AppQos_ForGuarantBitRateForDown(pApsQos, pTafQos);

#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pTafQos->ucSrcStatisticsDescriptor = pApsQos->ucSrcStatisticsDescriptor;
    pTafQos->ucSignallingIndication    = pApsQos->ucSignallingIndication;
#else
    pTafQos->ucSrcStatisticsDescriptor = APS_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN;
    pTafQos->ucSignallingIndication    = APS_QOS_SIGNAL_IND_NOT_OPTIMISE;
#endif

    return;
}


VOS_UINT32    Aps_SetEvtApn(
    VOS_UINT8                       ucPdpId,
    TAF_PDP_APN_STRU               *pstPdpApn)
{
    VOS_UINT32                  ulRelt;

    VOS_UINT8                   aucTmpEntityApn[APS_MAX_LENGTH_OF_APN + 1];
    VOS_UINT8                   aucTmpLenStr[TAF_MAX_APN_LEN + 1];

    if ( VOS_FALSE == g_PdpEntity[ucPdpId].PdpApnFlag)
    {
        ulRelt = VOS_ERR;
    }
    else if(g_PdpEntity[ucPdpId].PdpApn.ucLength > APS_MAX_LENGTH_OF_APN)
    {
        ulRelt = VOS_ERR;
    }
    else
    {
        ulRelt = VOS_OK;

        aucTmpEntityApn[0]      = g_PdpEntity[ucPdpId].PdpApn.ucLength;

        PS_MEM_CPY(             &aucTmpEntityApn[1],
                                g_PdpEntity[ucPdpId].PdpApn.aucValue,
                                aucTmpEntityApn[0]);

        Taf_Apn2Lenstr(aucTmpEntityApn, aucTmpLenStr);

        pstPdpApn->ucLength = aucTmpLenStr[0];
        if (pstPdpApn->ucLength > TAF_MAX_APN_LEN)
        {
            pstPdpApn->ucLength = TAF_MAX_APN_LEN;
        }
        PS_MEM_CPY(pstPdpApn->aucValue, &aucTmpLenStr[1], pstPdpApn->ucLength);
    }

    return ulRelt;
}



VOS_VOID Aps_SetEvtDns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_DNS_STRU                   *pstDns,
    TAF_PDP_IPV6_DNS_STRU              *pstIpv6Dns
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE == pstPdpEntity->PdpDnsFlag)
    {
        PS_MEM_CPY((VOS_CHAR*)pstDns,
                   (VOS_CHAR*)&pstPdpEntity->PdpDns,
                   sizeof(TAF_PDP_DNS_STRU));
    }

#if (FEATURE_ON == FEATURE_IPV6)
    PS_MEM_CPY((VOS_CHAR*)pstIpv6Dns,
               (VOS_CHAR*)&pstPdpEntity->stPdpIpV6Dns,
               sizeof(MN_APS_PDP_IPV6_DNS_STRU));
#endif

    return;
}


VOS_VOID MN_APS_SetEvtNbns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_NBNS_STRU                  *pstNbns
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    PS_MEM_SET(pstNbns, 0x00, sizeof(TAF_PDP_NBNS_STRU));

    /* Primary NBNS */
    if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_PriNbns)
    {
        pstNbns->bitOpPrimNbnsAddr   = VOS_TRUE;

        PS_MEM_CPY(pstNbns->aucPrimNbnsAddr,
                   pstPdpEntity->stPdpNbns.aucPriNbns,
                   TAF_IPV4_ADDR_LEN);
    }

    /* Secondary NBNS */
    if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_SecNbns)
    {
        pstNbns->bitOpSecNbnsAddr  = VOS_TRUE;

        PS_MEM_CPY(pstNbns->aucSecNbnsAddr,
                   pstPdpEntity->stPdpNbns.aucSecNbns,
                   TAF_IPV4_ADDR_LEN);
    }

    return;
}


VOS_VOID MN_APS_SetEvtGateWay(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_FALSE == pstPdpEntity->bitOpPdpGateWay)
    {
        pstPsCallEvt->stGateWay.bitOpGateWayAddr = VOS_FALSE;
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->stPdpGateWay.bitOpGateWay)
        {
            pstPsCallEvt->stGateWay.bitOpGateWayAddr = VOS_TRUE;

            PS_MEM_CPY(pstPsCallEvt->stGateWay.aucGateWayAddr,
                       pstPdpEntity->stPdpGateWay.aucGateWay,
                       TAF_IPV4_ADDR_LEN);
        }
    }

    return;
}





/*****************************************************************************
 Prototype      : Aps_FillEvtPcoIpcpInfo
 Description    : 填写上报事件的PCO信息中IPCP信息
 Input          : ---
 Output         : ---
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-9-29
    Author      : L47619
    Modification: 根据问题单新增:A32D06451
*****************************************************************************/
VOS_VOID  Aps_FillEvtPcoIpcpInfo(VOS_UINT8 *pucIpcpInfo, SM_TAF_PROT_CFG_OPT_STRU *pSmPco)
{
    VOS_UINT8       ucSubPackNum = 0;
    VOS_UINT16      usIpcpInfoLen = 0;
    VOS_UINT32      ulLocation = 0;
    VOS_UINT16      usCurPackLen = 0;
    VOS_UINT8 *     pucIpcpInfoBegin = pucIpcpInfo;

    pucIpcpInfo += 2;                /*跳过IPCP总长度字段2字节*/

    pucIpcpInfo += 1;                /*跳过IPCP子包个数字段1字节*/

    ulLocation += 1;                 /*跳过PCO中的第一个字段:0x80*/

    while((ulLocation + 1) < pSmPco->ulPcoLen)
    {
        usCurPackLen = pSmPco->aucProtCfgOpt[ulLocation + 2];

        if ( (0x80 == pSmPco->aucProtCfgOpt[ulLocation])
             && (0x21 == pSmPco->aucProtCfgOpt[ulLocation + 1]) )
        {
            ucSubPackNum++;
            usIpcpInfoLen += usCurPackLen;

            /*lint -e961*/
            *pucIpcpInfo++ = ((0xFF00 & usCurPackLen) >> 8);
            *pucIpcpInfo++ = (0xFF & usCurPackLen);
            /*lint +e961*/

            /*拷贝子包内容:*/
            PS_MEM_CPY(pucIpcpInfo, &(pSmPco->aucProtCfgOpt[ulLocation + 3]), usCurPackLen);

            pucIpcpInfo += usCurPackLen;
        }

        ulLocation += 2 + 1 + usCurPackLen;
    }

    /*统计上报事件中的PCO的IPCP信息总长度:*/
    usIpcpInfoLen += 1 + (ucSubPackNum * 2);

    /*lint -e961*/
    /*填写PCO中IPCP信息总长度字段:*/
    *pucIpcpInfoBegin++ = ((0xFF00 & usIpcpInfoLen) >> 8);
    *pucIpcpInfoBegin++ = (0xFF & usIpcpInfoLen);
    /*lint +e961*/

    /*填写子包个数:*/
    *pucIpcpInfoBegin = ucSubPackNum;

    return;
}


VOS_UINT32 Aps_SetEvtAddr(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr
)
{
    VOS_UINT32                          ulRelt;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    ulRelt = VOS_OK;

    if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
    {
        PS_MEM_CPY(pstPdpAddr->aucIpv4Addr,
                   pstPdpEntity->PdpAddr.aucIpAddr,
                   TAF_IPV4_ADDR_LEN);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (MN_APS_ADDR_IPV6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
    {
        PS_MEM_CPY(pstPdpAddr->aucIpv6Addr,
                   pstPdpEntity->PdpAddr.aucIpV6Addr,
                   TAF_IPV6_ADDR_LEN);
    }
    else if (MN_APS_ADDR_IPV4V6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
    {
        PS_MEM_CPY(pstPdpAddr->aucIpv4Addr,
                   pstPdpEntity->PdpAddr.aucIpAddr,
                   TAF_IPV4_ADDR_LEN);

        PS_MEM_CPY(pstPdpAddr->aucIpv6Addr,
                   pstPdpEntity->PdpAddr.aucIpV6Addr,
                   TAF_IPV6_ADDR_LEN);
    }
#endif
    else
    {
        ulRelt = VOS_ERR;
    }

    return ulRelt;
}



VOS_VOID TAF_APS_SetEvtPcscf(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_PCSCF_STRU                 *pstPcscf,
    TAF_PDP_IPV6_PCSCF_STRU            *pstIpv6Pcscf
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpPrimPcscfAddr)
    {
        pstPcscf->bitOpPrimPcscfAddr     = VOS_TRUE;
        PS_MEM_CPY(pstPcscf->aucPrimPcscfAddr,
                   pstPdpEntity->stPdpPcscf.aucPrimPcscfAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pstPcscf->bitOpPrimPcscfAddr     = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpSecPcscfAddr)
    {
        pstPcscf->bitOpSecPcscfAddr      = VOS_TRUE;
        PS_MEM_CPY(pstPcscf->aucSecPcscfAddr,
                   pstPdpEntity->stPdpPcscf.aucSecPcscfAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pstPcscf->bitOpSecPcscfAddr     = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpThiPcscfAddr)
    {
        pstPcscf->bitOpThiPcscfAddr      = VOS_TRUE;
        PS_MEM_CPY(pstPcscf->aucThiPcscfAddr,
                   pstPdpEntity->stPdpPcscf.aucThiPcscfAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pstPcscf->bitOpThiPcscfAddr     = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        pstIpv6Pcscf->bitOpPrimPcscfAddr = VOS_TRUE;
        PS_MEM_CPY(pstIpv6Pcscf->aucPrimPcscfAddr,
                   pstPdpEntity->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
    else
    {
        pstIpv6Pcscf->bitOpPrimPcscfAddr = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
    {
        pstIpv6Pcscf->bitOpSecPcscfAddr  = VOS_TRUE;
        PS_MEM_CPY(pstIpv6Pcscf->aucSecPcscfAddr,
                   pstPdpEntity->stPdpIpv6Pcscf.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
    else
    {
        pstIpv6Pcscf->bitOpSecPcscfAddr  = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
    {
        pstIpv6Pcscf->bitOpThiPcscfAddr  = VOS_TRUE;
        PS_MEM_CPY(pstIpv6Pcscf->aucThiPcscfAddr,
                   pstPdpEntity->stPdpIpv6Pcscf.aucThiPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
    else
    {
        pstIpv6Pcscf->bitOpThiPcscfAddr  = VOS_FALSE;
    }

#endif

    return;
}

/*****************************************************************************
 Prototype      : Aps_DecideTransMode
 Description    :
 Input          : ---
 Output         : ---
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_DecideTransMode(VOS_UINT8                       ucPdpId,
                                RABM_TRANS_MODE_ENUM           *pTransMode   )
{
    if ( g_PdpEntity[ucPdpId].PdpQos.ucReliabClass
         < APS_3GPP_QOS_RELIABCLASS_UNKGTPLLC_ACKRLC_PRODATA)
    {
        *pTransMode             = RABM_ABM_ENUM;
    }
    else
    {
        *pTransMode             = RABM_ADM_ENUM;
    }

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_CHAR* MN_APS_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
)
{
    if (usRadix == 16)
    {
        /*lint -e586*/
        pcStr += sprintf(pcStr, "%x", usValue);
        /*lint +e586*/
    }
    else if(usRadix == 10)
    {
        /*lint -e586*/
        pcStr += sprintf(pcStr, "%d", usValue);
        /*lint +e586*/
    }
    else
    {
    }

    return pcStr;
}


VOS_UINT32 MN_APS_ConvertIpv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    MN_APS_IPV6_STR_TYPE_ENUM_UINT8     enIpStrType
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[MN_APS_IPV6_STR_MAX_TOKENS];
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucTokensNum;
    VOS_UINT8                           ucRadix;
    VOS_UINT32                          i;

    pucBuffer                           = aucAddrStr;

    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    /* 根据IP字符串格式表达类型, 配置对应的转换参数 */
    switch (enIpStrType)
    {
        case MN_APS_IPV6_STR_TYPE_HEX:
            ucDelimiter = MN_APS_IPV6_STR_DELIMITER;
            ucTokensNum = 8;
            ucRadix     = 16;
            break;

        case MN_APS_IPV6_STR_TYPE_DEC:
            ucDelimiter = MN_APS_IPV4_STR_DELIMITER;
            ucTokensNum = 16;
            ucRadix     = 10;
            break;

        default:
            MN_ERR_LOG1("MN_APS_ConvertIpv6AddrToStr: Wrong IPV6 string type:",
                        enIpStrType);
            return VOS_ERR;
    }
/*lint -e961*/
    /* 根据IP字符串格式表达类型, 获取分段的IP地址数值 */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        if (MN_APS_IPV6_STR_TYPE_HEX == enIpStrType)
        {
            usAddrNum <<= 8;
            usAddrNum  |= *aucIpAddr++;
        }

        ausAddrValue[i] = usAddrNum;
    }

    /* 遍历IP地址分段, 创建有分隔符标记的IP地址字符串 */
    for (i=0; i < ucTokensNum; i++)
    {
        pucBuffer    = (VOS_UINT8*)MN_APS_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix);
        *pucBuffer++ = ucDelimiter;
    }

    /* 取出最后一个分隔符, 补充字符串结束符 */
    if (aucAddrStr != pucBuffer)
    {
        *(--pucBuffer) = '\0';
    }
/*lint +e961*/

    return VOS_OK;
}
#endif

/**********************************************************
 Function:       Taf_IpAddr2LenStr
 Description:    将SM协议IP地址格式转化为字符串+ 长度格式的IP地址
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pucIpAddr - SM协议定义的IP地址
 Output:         pucStr - 字符串格式的IP地址
 Return:
 Others:
**********************************************************/
VOS_VOID Taf_IpAddr2LenStr(CONST VOS_UINT8* pucIpAddr, VOS_UINT8 *pucStr)
{
    VOS_UINT8 i, j = 1;
    VOS_UINT8 ucHundred;
    VOS_UINT8 ucDecade;
    VOS_UINT8 ucSingle;

    for (i = 0; i < 4; i++)
    {
        ucHundred = pucIpAddr[i] / 100;
        ucDecade = (VOS_UINT8)((pucIpAddr[i] - (ucHundred * 100)) / 10);
        ucSingle = (VOS_UINT8)((pucIpAddr[i] - (ucHundred * 100)) - (ucDecade * 10));
        if (ucHundred != 0)
        {
            pucStr[j] = ucHundred + 0x30;  /*将百位转化为字符*/
            j++;
        }
        if ((0 != ucHundred) || (0 != ucDecade ))
        {
            pucStr[j] = ucDecade + 0x30;   /*将十位转化为字符*/
            j++;
        }
        pucStr[j] = ucSingle + 0x30;       /*将个位转化为字符*/
        j++;
        /* mod by zzy,最后一个位段时不应该填充点号，否则导致缓冲区溢出 */
        if (i != 3)
        {
            pucStr[j] = '.';                   /*一个位段结束后填充'.'号*/
        }
        j++;
    }
    pucStr[0] = j - 2; /*填充整个字符串的长度*/
    return;
}

/**********************************************************
 Function:       Taf_Apn2Lenstr
 Description:    将协议定义的APN格式转化为字符串格式的APN
 Calls:          Taf_Apn2str
 Data Accessed:
 Data Updated:
 Input:          pucApn - 协议定义的APN
 Output:         pucStr - 字符串格式的Apn
 Return:
 Others:
**********************************************************/
VOS_VOID Taf_Apn2Lenstr(VOS_UINT8* pucApn, VOS_UINT8 *pucStr)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucLabelLen = 0;

    if (0 == pucApn[0])
    {   /*APN长度为0，直接长度赋值返回*/
        pucStr[0] = 0;
        return;
    }
    ucLabelLen = pucApn[1]; /*第1个label的长度*/
    for (i = 1; (i < pucApn[0]) && (i < TAF_MAX_APN_LEN); i++)
    {   /*从第1个有效字符开始检查*/
        if (j < ucLabelLen)
        {   /*拷贝ucLabelLen个字符*/
            pucStr[i] = pucApn[i + 1];
            j++;  /*有效字符数增1*/
        }
        else
        {   /*拷贝一个Label完毕后，追加一个'.'号*/
            pucStr[i] = '.';
            j = 0;     /*开始下一个Label的长度累计*/
            ucLabelLen = pucApn[i + 1]; /*取下一个label的长度*/
        }
    }
    pucStr[0] = i - 1;  /*字符串的长度*/
    return;
}



VOS_UINT32 Taf_CheckActCid(VOS_UINT8 ucCid)
{
    VOS_UINT8 ucTi;

    for (ucTi = 0; ucTi < TAF_APS_MAX_PDPID; ucTi++)
    {
        if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucTi, ucCid))
         && (VOS_TRUE == g_PdpEntity[ucTi].ulUsedFlg))
        {
            /*Cid正在被激活*/
            return TAF_TRUE;
        }
    }
    return TAF_FALSE;
}


/*****************************************************************************
 Prototype      : Aps_Str2LenStr
 Description    : 将有字符串结束符的字符串转换为字符串长度+字符串的形式
 Input          : pStr
                  ulStrMaxLen:被转换的字符串的最大长度，用于避免拷贝越界
 Output         : pLenStr
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_Str2LenStr(             VOS_UINT32          ulMaxStrLen,
                                        VOS_UINT8          *pStr,
                                        VOS_UINT8          *pLenStr )
{
    VOS_UINT32                          ulRealStrLen;
    VOS_UINT32                          ulTempAddr;

    ulRealStrLen                        = VOS_StrLen((VOS_CHAR *)pStr);

    /*如果实际长度超过最大长度,则强制赋值为最大长度*/
    if (ulMaxStrLen < ulRealStrLen )
    {
        ulRealStrLen                    = ulMaxStrLen;
    }

    pLenStr[0]                          = (VOS_UINT8)ulRealStrLen;

    ulTempAddr = (VOS_UINT32)&pLenStr[1];
    PS_MEM_CPY((VOS_UINT32 *)ulTempAddr, pStr, ulRealStrLen);

    return;
}

/*****************************************************************************
 Prototype      : Aps_LenStr2Str
 Description    : 将字符串长度+字符串的形式转换为有字符串结束符的字符串形式
 Input          : pLenStr
 Output         : pStr
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_LenStr2Str(             VOS_UINT8           ucMaxLen,
                                        VOS_UINT8          *pLenStr,
                                        VOS_UINT8          *pStr )
{
    VOS_UINT8                           ucRealLen;

    ucRealLen                           = pLenStr[0];

    if ( ucRealLen > ucMaxLen)
    {
        ucRealLen                       = ucMaxLen;
    }

    PS_MEM_CPY(pStr, &pLenStr[1], ucRealLen);

    pStr[ucRealLen]  = '\0';

    return;
}



VOS_VOID  Taf_PsParaSetResult(  VOS_UINT16           ClientId,
                            VOS_UINT8                  OpId,
                            TAF_PARA_SET_RESULT     Result,
                            TAF_PARA_TYPE           ParaType,
                            VOS_VOID                   *pPara )
{
    MN_SETPARA_SendMsg(ClientId,
                       OpId,
                       Result,
                       ParaType,
                       pPara);

    return;
}


/*****************************************************************************
 Prototype      : Aps_Option12Cids
 Description    : 检查是否操作接口中的全部12个CID
 Input          : pLenStr
 Output         : pStr
 Return Value   : APS_PARA_VALID
                  APS_PARA_INVALID
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_Option12Cids(           VOS_UINT8          *paucCid )
{
    VOS_UINT8                           ucCidLoc;
    VOS_UINT8                           ulCidFlg;

    ulCidFlg                            = TAF_CID_NUMS_INVALID;

    /*如果全部都非0，即操作12个PDP，返回失败*/
    for (ucCidLoc = 0; ucCidLoc < (APS_PDP_MAX_CID+1); ucCidLoc ++)
    {
        if ( 0 == paucCid[ucCidLoc])
        {   /*有一个等于0，则不操作全部的12个CID*/
            ulCidFlg                    = TAF_CID_NUMS_VALID;
            break;
        }
    }

    return  ulCidFlg;
}


/*****************************************************************************
 Prototype      : Aps_Option0Cid
 Description    : 检查是否操作接口中的全部12个CID
 Input          : pLenStr
 Output         : pStr
 Return Value   : APS_PARA_VALID
                  APS_PARA_INVALID
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_Option0Cid(             VOS_UINT8          *paucCid )
{
    VOS_UINT8                           ucCidLoc;
    VOS_UINT8                           ulCidFlg;

    ulCidFlg                            = TAF_CID_NUMS_INVALID;


    /*如果全部都是0，即操作0个PDP，也返回失败*/
    for (ucCidLoc = 0; ucCidLoc < (APS_PDP_MAX_CID+1); ucCidLoc ++)
    {
        if (0 != paucCid[ucCidLoc])
        {   /*有一个不等于0,就跳出检查*/
            ulCidFlg                    = TAF_CID_NUMS_VALID;
            break;
        }
    }

    return  ulCidFlg;
}




VOS_VOID    Aps_PowerOff(VOS_VOID)
{
    VOS_UINT8                   ucPdpId;
    TAF_APS_STA_ENUM_UINT32     enState;

    for ( ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++ )
    {
        enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if  ( TAF_APS_STA_INACTIVE != enState )
        {
            if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
              && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
            {
                (VOS_VOID)Aps_SmMsgModSnDeActInd(ucPdpId);
            }

            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_GMM_PS_DETACH);

            if (TAF_APS_RAT_TYPE_NULL != TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 设置当前PS业务所在的模式 */
                TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_NULL);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                /* 通知外部模块当前PS业务所在的模式 */
                TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_NULL);

                /* 通知PPPC本地去激活 */
                if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
                {
                    TAF_APS_SndPppDeactInd(ucPdpId);
                }
#endif
            }
        }
    }

    TAF_APS_SaveDsFlowInfoToNv();

    TAF_APS_ReleaseDfs();

#if (FEATURE_ON == FEATURE_IPV6)
    TAF_APS_SndNdRelInd();
#endif

    /* 停止所有定时器*/
    TAF_APS_StopAllTimer();

    /*调用初始化函数:*/
    Aps_PdpEntityInit();

    /* APS CTX模块初始化 */
    TAF_APS_InitCtx();

    /* 关机导致的本地释放, 可能不会走正常的状态机流程,
     * 需要主动通知一下STK当前的PS域呼叫状态
     */
    TAF_APS_SndStkPsCallEvent();

    return;
}


VOS_UINT32 Aps_JudgeSapiValid(VOS_UINT8 ucSapi)
{
    if (TAF_APS_RAT_TYPE_GSM == TAF_APS_GetCurrPdpEntityRatType())
    {
        /* 当前网络接入模式为GSM时检查此参数 */
        if ( (APS_SAPI_3 == ucSapi)
          || (APS_SAPI_5 == ucSapi)
          || (APS_SAPI_9 == ucSapi)
          || (APS_SAPI_11 == ucSapi) )
        {
            return  APS_SAPI_VALID;
        }
        else
        {
            return  APS_SAPI_INVALID;
        }
    }
    else
    {
        return  APS_SAPI_VALID;
    }
}



VOS_VOID    Aps_LoadDefault(VOS_VOID)
{
    TAF_NV_PDP_TABLE_STRU  *psTmpPdpTbl;
    TAF_PS_ANSWER_MODE_STRU stTmpTelePara;
    TAF_UINT8               ucCid;
    TAF_UINT32              ulResult;

    /*Part 1: +CGEQREQ, +CGEQMIN, +CGTFT, +CGDCONT, +CGDSCONT, ^CGAUTH, ^CGDNS*/
    psTmpPdpTbl = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));

    if (VOS_NULL_PTR == psTmpPdpTbl)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_LoadDefault: Ps Mem Alloc Fail!");
        return;
    }

    PS_MEM_SET(psTmpPdpTbl , 0, sizeof(TAF_NV_PDP_TABLE_STRU));
    for (ucCid = 1 ; ucCid <= TAF_MAX_CID_NV; ucCid++)
    {
        ulResult = NV_Write((NV_ID_ENUM_U16)(en_NV_Item_Taf_PdpPara_0 + ucCid),
                             psTmpPdpTbl ,
                             sizeof(TAF_NV_PDP_TABLE_STRU));
        if (NV_OK != ulResult)
        {
            APS_WARN_LOG("Aps_LoadDefault:WARNING:NV_Write PDP Para FAIL!");
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, psTmpPdpTbl);

    /*Part 2: +CGAUTO*/
    PS_MEM_SET(&stTmpTelePara, 0, sizeof(TAF_PS_ANSWER_MODE_STRU));
    ulResult = NV_Write( en_NV_Item_PS_TelePara,
                         &stTmpTelePara,
                         sizeof(TAF_PS_ANSWER_MODE_STRU));
    if (NV_OK != ulResult)
    {
        APS_WARN_LOG("Aps_LoadDefault:WARNING:NV_Write PS_TelePara FAIL!");
    }

    return;
}



VOS_UINT32  Taf_ApsIsSndcpActive(VOS_UINT8  ucNsapi, RABM_TRANS_MODE_ENUM *penTransMode)
{
    VOS_UINT8   ucLoop;

    /*查找指定的CID是否已激活*/
    for (ucLoop = 0; ucLoop < TAF_APS_MAX_PDPID; ucLoop++)
    {
        if (VOS_TRUE == g_PdpEntity[ucLoop].ulUsedFlg)
        {
            if (ucNsapi == g_PdpEntity[ucLoop].ucNsapi)
            {
                if (APS_SNDCP_ACT == g_PdpEntity[ucLoop].PdpProcTrack.ucSNDCPActOrNot)
                {
                    *penTransMode = g_PdpEntity[ucLoop].GprsPara.TransMode;

                    return VOS_TRUE;
                }
                else
                {
                    return VOS_FALSE;
                }
            }
        }
    }

    return VOS_FALSE;
}


/*******************************************************************************
  Module:      TAF_DecodeMaxBitrateOfQos
  Function:    将网侧下发的QoS信息中的Maximum bit rate(uplink and downlink)
               解码为实际的最大比特率
  Input:       ucMaxBitrateOfQos    Qos信息中的原始最大比特率字节
               pulRealMaxBitrate    解码后的实际最大比特率信息
  Output:      None
  NOTE:
  Return:      VOS_OK   解码成功
               VOS_ERR  解码失败
  History:
      1.  L47619      2009.03.26   热保护方案
*******************************************************************************/
VOS_UINT32  TAF_DecodeMaxBitrateOfQos(VOS_UINT8   ucMaxBitrateOfQos,
#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
                                                  VOS_UINT8   ucMaxBitrateOfQosExt,
#endif
                                                  VOS_UINT32  *pulRealMaxBitrate)
{
    if (VOS_NULL_PTR == pulRealMaxBitrate)
    {
        APS_WARN_LOG("TAF_DecodeMaxBitrateOfQos:WARNING:pulRealMaxBitrate is Null Ptr!");
        return VOS_ERR;
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (0 != ucMaxBitrateOfQosExt)
    {
        *pulRealMaxBitrate = (APS_APP_QOS_BIT_8600KBPS
             + (ucMaxBitrateOfQosExt * APS_3GPP_QOS_BIT_INC_100KBPS));
    }
    else
    #endif
    {
        if (APS_3GPP_QOS_BIT_0KBPS == ucMaxBitrateOfQos)
        {
            *pulRealMaxBitrate = APS_APP_QOS_BIT_0KBPS;
        }
        else if( ucMaxBitrateOfQos >= APS_3GPP_QOS_BIT_576KBPS)
        {
            *pulRealMaxBitrate
                =   ((ucMaxBitrateOfQos - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (ucMaxBitrateOfQos >= APS_3GPP_QOS_BIT_64KBPS)
        {
            *pulRealMaxBitrate
                =   ((ucMaxBitrateOfQos - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            *pulRealMaxBitrate = (VOS_UINT32)ucMaxBitrateOfQos;
        }
    }

    return VOS_OK;
}


/*******************************************************************************
  Module:      TAF_EncodeMaxBitrateOfQos
  Function:    将网侧下发的QoS信息中的Maximum bit rate(uplink and downlink)
               解码为实际的最大比特率
  Input:       ulRealMaxBitrate      实际最大比特率信息
               pucMaxBitrateOfQos    编码后Qos信息中的最大比特率字节
  Output:      None
  NOTE:
  Return:      VOS_OK   编码成功
               VOS_ERR  编码失败
  History:
      1.  L47619      2009.03.26   热保护方案
*******************************************************************************/
VOS_UINT32  TAF_EncodeMaxBitrateOfQos(VOS_UINT32  ulRealMaxBitrate,
#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
                                                  VOS_UINT8   *pucMaxBitrateOfQosExt,
#endif
                                                  VOS_UINT8   *pucMaxBitrateOfQos
                                                  )
{
    if (VOS_NULL_PTR == pucMaxBitrateOfQos)
    {
        APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:pucMaxBitrateOfQos is Null Ptr!");
        return VOS_ERR;
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
    {
        *pucMaxBitrateOfQosExt = 0;
    }
    #endif

    if(ulRealMaxBitrate == 0)
    {
        *pucMaxBitrateOfQos   = 255;  /*1 1 1 1 1 1 1 1*/
    }
    else if(ulRealMaxBitrate <= 63)
    {
        *pucMaxBitrateOfQos   = (VOS_UINT8)ulRealMaxBitrate;
    }
    else
    {
        if (ulRealMaxBitrate <= 568)
        {
            *pucMaxBitrateOfQos = (VOS_UINT8)(((ulRealMaxBitrate - 64) / 8) + 64);
        }
        else
        {
            if (ulRealMaxBitrate < 576)
            {
                *pucMaxBitrateOfQos = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (ulRealMaxBitrate <= 8640)
                {
                    *pucMaxBitrateOfQos = (VOS_UINT8)(((ulRealMaxBitrate - 576) / 64) + 128);
                }
                else
                {
                #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    *pucMaxBitrateOfQos = 254;  /*1 1 1 1 1 1 1 0*/
                #else
                    /* If the sending entity wants to indicate a Maximum bit rate for downlink */
                    /* higher than 8640 kbps, it shall set octet 9 to "11111110", i.e. 8640 kbps, */
                    /* and shall encode the value for the Maximum bit rate in octet 15. */
                    if (ulRealMaxBitrate < 8700)
                    {
                        *pucMaxBitrateOfQos = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        if (ulRealMaxBitrate <= 16000)
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt
                                    = (VOS_UINT8)((ulRealMaxBitrate - 8600) / 100);
                            }
                            else
                            {
                                /* 为空指针，则代表编码MAX UL Bitrate，但截止到R6协议，MAX UL Bitrate不会超出8640，
                                        故将之置为8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (ulRealMaxBitrate <= 128000)
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt
                                    = (VOS_UINT8)(((ulRealMaxBitrate - 16000) / 1000) + 74);
                            }
                            else
                            {
                                /* 为空指针，则代表编码MAX UL Bitrate，但截止到R6协议，MAX UL Bitrate不会超出8640，
                                        故将之置为8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                        else if (ulRealMaxBitrate <= 256000)
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt
                                    = (VOS_UINT8)(((ulRealMaxBitrate - 128000) / 2000) + 186);
                            }
                            else
                            {
                                /* 为空指针，则代表编码MAX UL Bitrate，但截止到R6协议，MAX UL Bitrate不会超出8640，
                                        故将之置为8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                    #endif
                        else
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt = 74;  /*0 1 0 0 1 0 1 0*/
                            #else
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                            }
                            else
                            {
                                /* 为空指针，则代表编码MAX UL Bitrate，但截止到R6协议，MAX UL Bitrate不会超出8640，
                                        故将之置为8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                    }
                #endif
                }
            }
        }
    }

    return VOS_OK;
}

/*******************************************************************************
  Module:      Aps_UpdateWinsConfig
  Function:    用户通过AT命令设置WINS时，为了保证立即生效，必须同步更新g_ApsWins
  Input:       VOS_VOID
  Output:      None
  NOTE:
  Return:      None
  History:
      1.  L47619      2009.07.13   可配置需求:WINS
*******************************************************************************/
VOS_VOID    Aps_UpdateWinsConfig(VOS_UINT8 ucWins)
{
    if ((WINS_CONFIG_DISABLE != ucWins) && (WINS_CONFIG_ENABLE != ucWins))
    {
        /* ucWins值无效 */
        return;
    }

    /* 更新g_ApsWins */
    g_ApsWins = ucWins;

    return;
}


VOS_VOID Aps_GetPdpContextInfo_ForActTypeAndNsapi(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* 获得PDP激活类型和对应的主PDP的Nsapi */
    if ( APS_PDP_ACT_PRI == g_PdpEntity[ucPdpId].ActType )
    {
        pstPdpCntxt->enActType = NAS_OM_PDP_ACT_PRI;
    }
    else if ( APS_PDP_ACT_SEC == g_PdpEntity[ucPdpId].ActType )
    {
        pstPdpCntxt->enActType = NAS_OM_PDP_ACT_SEC;
        pstPdpCntxt->ucLinkedNsapi = g_PdpEntity[ucPdpId].ucLinkedNsapi;
    }
    else
    {
        /*打印警告信息---ActType错误:*/
        APS_WARN_LOG("Aps_GetPdpContextInfo: ActType is error!");
    }

    return;
}


VOS_VOID Aps_GetPdpContextInfo_ForSapi(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* 获得Sapi */
    if ( VOS_TRUE == g_PdpEntity[ucPdpId].GprsPara.Op_Sapi )
    {
        pstPdpCntxt->ucPdpLlcSapi = g_PdpEntity[ucPdpId].GprsPara.ucSapi;
    }
    else
    {
        pstPdpCntxt->ucPdpLlcSapi = 0xFF;
    }

    return;
}


VOS_VOID Aps_GetPdpContextInfo_ForRadioPriority(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* 获得RadioPriority */
    if ( VOS_TRUE == g_PdpEntity[ucPdpId].GprsPara.Op_RadioPriority )
    {
        pstPdpCntxt->ucPdpRadioPriority = g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority;
    }
    else
    {
        pstPdpCntxt->ucPdpRadioPriority = 0xFF;
    }

    return;
}



VOS_VOID Aps_GetPdpContextInfo_ForIpAddress(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* 为了OM能兼容显示未添加IPV6的IP地址，初始化ucPdpType为无效的IP地址类型。
       因为老版本该接口会初始化ucPdpType为0，而新版本ucPdpType值只能取
       MN_APS_ADDR_BUTT，APS_ADDR_STATIC_IPV4，MN_APS_ADDR_IPV6，MN_APS_ADDR_IPV4V6
    */

    switch (g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
    {
        case APS_ADDR_STATIC_IPV4 :/* IPV4 */
            /* 获得Ip地址 */
            PS_MEM_CPY( pstPdpCntxt->aucIpAddr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                    4 );

            pstPdpCntxt->enPdpType = APS_ADDR_STATIC_IPV4;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        /* IPV6 */
        case MN_APS_ADDR_IPV6:
            PS_MEM_CPY( pstPdpCntxt->aucIpv6Addr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpV6Addr,
                    TAF_IPV6_ADDR_LEN );

            pstPdpCntxt->enPdpType = MN_APS_ADDR_IPV6;

            break;

        /* IPV4V6 */
        case MN_APS_ADDR_IPV4V6:
            PS_MEM_CPY( pstPdpCntxt->aucIpAddr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                    4 );

            PS_MEM_CPY( pstPdpCntxt->aucIpv6Addr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpV6Addr,
                    TAF_IPV6_ADDR_LEN );

            pstPdpCntxt->enPdpType = MN_APS_ADDR_IPV4V6;

            break;
#endif
        default:
            pstPdpCntxt->enPdpType = APS_ADDR_STATIC_IPV4;
            break;
    }


    return;
}


VOS_UINT32 Aps_IsInvalidAlphaInApn(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulLoop
)
{
    if (((g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] >= 'A')
          && (g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] <= 'Z'))
        || ((g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] >= 'a')
            && (g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] <= 'z'))
        || ((g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] >= '0')
            && (g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] <= '9'))
        || ('-' == g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1]))
    {
        return TAF_APS_SUCC;
    }
    else
    {
        return TAF_APS_FAIL;
    }
}


VOS_VOID Aps_GetPdpContextInfo_ForApn(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    VOS_UINT32                          ulLoop;
    /* 获得APN */
    if ((g_PdpEntity[ucPdpId].PdpApn.ucLength <= (APS_MAX_LENGTH_OF_APN - 1))
        && (g_PdpEntity[ucPdpId].PdpApn.ucLength > 1))
    {
        pstPdpCntxt->ucApnLength = g_PdpEntity[ucPdpId].PdpApn.ucLength - 1;

        for (ulLoop = 0; ulLoop < pstPdpCntxt->ucApnLength; ulLoop++)
        {
            if (TAF_APS_SUCC == Aps_IsInvalidAlphaInApn(ucPdpId, ulLoop))
            {
                pstPdpCntxt->aucApn[ulLoop] = g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1];
            }
            else
            {
                pstPdpCntxt->aucApn[ulLoop] = '.';
            }
        }
    }
    else
    {
        /*打印警告信息---ucApnLength超出101:*/
        APS_WARN_LOG("Aps_GetPdpContextInfo: ucApnLength > 100");
    }

    return;
}


VOS_VOID Aps_GetPdpContextInfo(
    VOS_UINT8                           ucNsapi,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    VOS_UINT8                           ucPdpId;

    PS_MEM_SET(pstPdpCntxt, 0, sizeof(NAS_PDP_CONTEXT_STRU));

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (ucNsapi == g_PdpEntity[ucPdpId].ucNsapi)
        {
        #if 0
            if ((APS_PDP_ACTIVE == g_PdpEntity[ucPdpId].EntityState)
                || (APS_PDP_MODIFY_PENDING == g_PdpEntity[ucPdpId].EntityState))
            {
        #endif
                /* 获得PDP的NSAPI */
                pstPdpCntxt->ucNsapi = g_PdpEntity[ucPdpId].ucNsapi;

                /* 获得PDP上下文的状态 */
                pstPdpCntxt->enActivePDPContexts = SM_OM_PDP_ACTIVATED;

                /* 获得PDP激活类型和对应的主PDP的Nsapi */
                Aps_GetPdpContextInfo_ForActTypeAndNsapi(ucPdpId, pstPdpCntxt);

                /* 获得Sapi */
                Aps_GetPdpContextInfo_ForSapi(ucPdpId, pstPdpCntxt);

                /* 获得RadioPriority */
                Aps_GetPdpContextInfo_ForRadioPriority(ucPdpId, pstPdpCntxt);

                /* 获得Ip地址 */
                Aps_GetPdpContextInfo_ForIpAddress(ucPdpId, pstPdpCntxt);

                /* 获得APN */
                Aps_GetPdpContextInfo_ForApn(ucPdpId, pstPdpCntxt);

                break;
        #if 0
            }
        #endif
        }
    }

    if (TAF_APS_MAX_PDPID == ucPdpId)
    {
        pstPdpCntxt->enActivePDPContexts = SM_OM_PDP_NOT_ACTIVATED;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_APS_FillCallEvtPdpAvtivateIndFromEsm(
    TAF_PS_CALL_PDP_MANAGE_IND_STRU    *pstCallEvt,
    APP_ESM_PDP_MANAGER_IND_STRU       *pstEsmPdpManageInd
)
{

    /* 初始化事件 */
    PS_MEM_SET(pstCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    /* 填充事件内容 */
    pstCallEvt->stCtrl.ulModuleId       = WUEPS_PID_AT;
    pstCallEvt->stCtrl.usClientId       = TAF_CLIENTID_BROADCAST;
    pstCallEvt->ucCid                   = (VOS_UINT8)pstEsmPdpManageInd->ulCid;

}
#endif


VOS_VOID TAF_APS_FillEvtPdpType(
    TAF_PDP_TYPE_ENUM_UINT8            *penPdpType,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeRequest;

    enPdpTypeRequest = TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid);

    /*----------------------------------------------------------------------
       以用户请求IP类型为基准
       (1) IPv4v6类型, 上报呼叫事件的IP类型为承载IP类型
       (2) 其他类型, 上报呼叫事件的IP类型为用户请求IP类型
    ----------------------------------------------------------------------*/
#if (FEATURE_ON == FEATURE_IPV6)
    if (TAF_PDP_IPV4V6 == enPdpTypeRequest)
    {
        *penPdpType  = TAF_APS_ConvertPdpType(TAF_APS_GetPdpEntPdpAddrType(ucPdpId));
        return;
    }
#endif

    *penPdpType = enPdpTypeRequest;

    return;
}



/*lint +e958*/
#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_APS_SetEvtTftInfo(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_TFT_STRU                   *pstTft
)
{
    VOS_UINT32                          i;
    TAF_PDP_PF_STRU                    *pstTafPf = VOS_NULL_PTR;
    SM_ESM_PF_STRU                     *pstPdpPf = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstTft->ulPfNum = pstPdpEntity->stTft.ulPfNum;

    for (i = 0; i < pstTft->ulPfNum; i++)
    {
        pstTafPf = &pstTft->astPf[i];
        pstPdpPf = &pstPdpEntity->stTft.astCidPf[i].stPf;

        pstTafPf->bitOpRmtIpv4AddrAndMask = pstPdpPf->bitOpRmtIpv4AddrAndMask;
        pstTafPf->bitOpRmtIpv6AddrAndMask = pstPdpPf->bitOpRmtIpv6AddrAndMask;
        pstTafPf->bitOpProtocolId         = pstPdpPf->bitOpProtocolId;
        pstTafPf->bitOpSingleLocalPort    = pstPdpPf->bitOpSingleLocalPort;
        pstTafPf->bitOpLocalPortRange     = pstPdpPf->bitOpLocalPortRange;
        pstTafPf->bitOpSingleRemotePort   = pstPdpPf->bitOpSingleRemotePort;
        pstTafPf->bitOpRemotePortRange    = pstPdpPf->bitOpRemotePortRange;
        pstTafPf->bitOpSecuParaIndex      = pstPdpPf->bitOpSecuParaIndex;
        pstTafPf->bitOpTypeOfService      = pstPdpPf->bitOpTypeOfService;
        pstTafPf->bitOpFlowLabelType      = pstPdpPf->bitOpFlowLabelType;
        pstTafPf->bitOpLocalIpv4AddrAndMask = pstPdpPf->bitOpLocalIpv4AddrAndMask;
        pstTafPf->bitOpLocalIpv6AddrAndMask = pstPdpPf->bitOpLocalIpv6AddrAndMask;
        pstTafPf->bitOpSpare              = pstPdpPf->bitOpSpare;

        pstTafPf->ucPacketFilterId        = pstPdpPf->ucPacketFilterId;
        pstTafPf->ucNwPacketFilterId      = pstPdpPf->ucNwPacketFilterId;
        pstTafPf->enDirection             = pstPdpPf->enDirection;
        pstTafPf->ucPrecedence            = pstPdpPf->ucPrecedence;
        pstTafPf->ulSecuParaIndex         = pstPdpPf->ulSecuParaIndex;
        pstTafPf->usSingleLcPort          = pstPdpPf->usSingleLcPort;
        pstTafPf->usLcPortHighLimit       = pstPdpPf->usLcPortHighLimit;
        pstTafPf->usLcPortLowLimit        = pstPdpPf->usLcPortLowLimit;
        pstTafPf->usSingleRmtPort         = pstPdpPf->usSingleRmtPort;
        pstTafPf->usRmtPortHighLimit      = pstPdpPf->usRmtPortHighLimit;
        pstTafPf->usRmtPortLowLimit       = pstPdpPf->usRmtPortLowLimit;
        pstTafPf->ucProtocolId            = pstPdpPf->ucProtocolId;
        pstTafPf->ucTypeOfService         = pstPdpPf->ucTypeOfService;
        pstTafPf->ucTypeOfServiceMask     = pstPdpPf->ucTypeOfServiceMask;
        pstTafPf->ulFlowLabelType         = pstPdpPf->ulFlowLabelType;

        PS_MEM_CPY(pstTafPf->aucRmtIpv4Address, pstPdpPf->aucRmtIpv4Address, TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucRmtIpv4Mask,    pstPdpPf->aucRmtIpv4Mask,    TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucRmtIpv6Address, pstPdpPf->aucRmtIpv6Address, TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucRmtIpv6Mask,    pstPdpPf->aucRmtIpv6Mask,    TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucLocalIpv4Addr,  pstPdpPf->aucLocalIpv4Addr,  TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucLocalIpv4Mask,  pstPdpPf->aucLocalIpv4Mask,  TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucLocalIpv6Addr,  pstPdpPf->aucLocalIpv6Addr,  TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        pstTafPf->ucLocalIpv6Prefix = pstPdpPf->ucLocalIpv6Prefix;

    }

    return;
}
#endif

#if 0
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_APS_ProcCardReadFileCnf_CDMA_EFDGC(
    struct MsgCB                       *pstMsg
)
{
    /*
    Data dormant timer         : 1 byte
    EPZID Type Information     : 1 byte
    Hysteresis Activation Time : 1 byte
    */
    USIMM_READFILE_CNF_STRU            *pstFile  = VOS_NULL_PTR;
    VOS_UINT8                           uc1XPktDtInactivityTmrLen;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* 判断文件的读取结果 */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        /*读卡失败，读取NV */
        TAF_APS_Read1xPktDataInactivityTimeLenFromNv();

        return;
    }

    uc1XPktDtInactivityTmrLen = pstFile->aucEf[0];

    TAF_APS_SetPktCdataInactivityTimerLen(uc1XPktDtInactivityTmrLen);
    return;
}



VOS_VOID TAF_APS_ProcUsimMsg(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          ulEfId;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &ulEfId))
    {
        return;
    }

    switch (ulEfId)
    {
        case USIMM_CDMA_EFDGC_ID:
        case USIMM_CSIM_EFDGC_ID:
            TAF_APS_ProcCardReadFileCnf_CDMA_EFDGC(pstMsg);
            break;
        default:

            break;

    }

    return;
}
#endif
#endif


VOS_VOID TAF_APS_SnDataReq(VOS_UINT8 ucMode, VOS_UINT8 ucNsapi, VOS_UINT32 ulLen)
{
    VOS_VOID                           *pData = VOS_NULL_PTR;
    SN_DATA_REQ_ST                      stSnDataReq;
    SN_UNITDATA_REQ_ST                  stSnUnitDataReq;
    VOS_UINT16                          i;

    PS_MEM_SET(&stSnDataReq, 0, sizeof(SN_DATA_REQ_ST));
    PS_MEM_SET(&stSnUnitDataReq, 0, sizeof(SN_UNITDATA_REQ_ST));

    pData = PS_MEM_ALLOC(WUEPS_PID_TAF, ulLen);
    if (VOS_NULL_PTR == pData)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: alloc memory failed! ");
        return;
    }

    if (0 == ucMode)
    {
        stSnUnitDataReq.ucNsapi     = ucNsapi;
        stSnUnitDataReq.usDataLen   = (VOS_UINT16)ulLen;
        stSnUnitDataReq.pPdu        = pData;

        for (i = 0; i < stSnUnitDataReq.usDataLen; i++)
        {
            *((VOS_UINT8*)(stSnUnitDataReq.pPdu) + i) = 5;
        }

        if (VOS_OK != SN_UnitDataReq(&stSnUnitDataReq))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: SN_UnitDataReq ERROR! ");
        }
    }
    else
    {
        stSnDataReq.ucNsapi         = ucNsapi;
        stSnDataReq.ucMask          = 0;
        stSnDataReq.usDataLen       = (VOS_UINT16)ulLen;
        stSnDataReq.pPdu            = pData;

        for (i = 0; i < stSnDataReq.usDataLen; i++)
        {
            *((VOS_UINT8*)(stSnDataReq.pPdu) + i) = 5;
        }

        if (VOS_OK != SN_DataReq(&stSnDataReq))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: SN_DataReq ERROR! ");
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pData);
    return;
}


VOS_VOID TAF_APS_GprsDataReqTimeoutFunc(VOS_VOID)
{
    TAF_APS_GPRS_DATA_STRU             *pstDataReq = &g_stGprsDataReq;

    /* 发送一次数据 */
    TAF_APS_SnDataReq(pstDataReq->ucMode, pstDataReq->ucNsapi, pstDataReq->ulLen);

    pstDataReq->usSendTimes--;
    if (pstDataReq->usSendTimes > 0)
    {
        (VOS_VOID)VOS_StartCallBackRelTimer(&g_hGprsDataReqTimer,
                                             WUEPS_PID_TAF,
                                             pstDataReq->ulMillSecs,
                                             0,
                                             0,
                                             VOS_RELTIMER_NOLOOP,
                                             (REL_TIMER_FUNC)TAF_APS_GprsDataReqTimeoutFunc,
                                             VOS_TIMER_PRECISION_5);
    }
}


VOS_VOID TAF_APS_GprsDataReq(
    VOS_UINT8                           ucMode,
    VOS_UINT8                           ucNsapi,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucTimes,
    VOS_UINT32                          ulMillSecs
)
{
    TAF_APS_GPRS_DATA_STRU             *pstDataReq = &g_stGprsDataReq;

    if (0 == ucTimes)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: Invalid times, times = 0! ");
        return;
    }

    pstDataReq->ucMode        = ucMode;
    pstDataReq->ucNsapi       = ucNsapi;
    pstDataReq->ulLen         = ulLen;
    pstDataReq->usSendTimes   = ucTimes;
    pstDataReq->ulMillSecs    = ulMillSecs;

    /* 发送一次数据 */
    TAF_APS_SnDataReq(ucMode, ucNsapi, ulLen);

    pstDataReq->usSendTimes--;
    if (pstDataReq->usSendTimes > 0)
    {
        (VOS_VOID)VOS_StartCallBackRelTimer(&g_hGprsDataReqTimer,
                                             WUEPS_PID_TAF,
                                             ulMillSecs,
                                             0,
                                             0,
                                             VOS_RELTIMER_NOLOOP,
                                             (REL_TIMER_FUNC)TAF_APS_GprsDataReqTimeoutFunc,
                                             VOS_TIMER_PRECISION_5);
    }
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

