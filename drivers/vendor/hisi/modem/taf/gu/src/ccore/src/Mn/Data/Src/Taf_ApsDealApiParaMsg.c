/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Aps_DealApiParaMsg.c
  Author       : 韩鲁峰
  Version      : V200R001
  Date         : 2005-0
  Description  : 对FLASH中数据表的处理，包括读写修改
  Function List:
        ---Aps_DefPsPdpContext()
        ---Aps_ChngPdpPri
        ---Aps_DefPdpPri
        ---Aps_DefPsPdpAuth
        ---Aps_ChngAuth

        ---Aps_DefPsSecPdpContext
        ---Aps_ChngSecPara
        ---Aps_DefSecPara
        ---Aps_DefPsTft
        ---Aps_ChngTft

        ---Aps_JudgeTftItemCombin
        ---Aps_DefPs3gReqQos
        ---Aps_ChngQos
        ---Aps_DefQos
        ---Aps_DefPs3gMinAcceptQos

        ---Aps_ChngMinQos
        ---Aps_DefMinQos
        ---Aps_DbQuery
        ---Aps_DbQueryButt
        ---Aps_QuePri

        ---Aps_QueSec
        ---Aps_QueTft
        ---Aps_QueState
        ---Aps_NvimAct
        ---Aps_JudegNvimActType

  History      :
  1. Date:2005-0
     Author: ---
     Modification:Create
  2. 2006-02-23 modify by 韩鲁峰 FOR A32D02144
  3. 2006-03-03 MODIFY BY H41410 FOR A32D02345
  4. 2006-04-14 modify by h41410 for A32D03182
  5. 2006-10-23 modify by L47619 for A32D06872
  6.日    期 : 2006-12-07
    作    者 : 韩鲁峰
    修改内容 : A32D07824 增加CGEQNEG的处理
  7.日    期 : 2007年09月26日
    作    者 : l00107747
    修改内容 : 问题单号：A32D12931,查询API接口增加错误码上报
  8.日    期   : 2009年5月20日
    作    者   : h44270
    修改内容   : 问题单号：AT2D11987,修改NV项头文件，将PS/SYS/RF的NV项拆分出来，以便于维护
  9.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 删除Taf_DbPdpProc, Aps_DbQuery, Aps_DbQueryButt,
                 Aps_GetParaPointer
************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"

#include "TafLog.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsCtx.h"
#include "TafApsComFunc.h"

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
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALAPIPARAMSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*暂存将被操作的PDP项，待操作结束后，与操作后的PDP项作比较，以决定需要对NVIM中
的数据进行怎样的修改*/
TAF_PDP_TABLE_STRU                      g_TmpPdpTab;


/*参数查询是否结束的标识*/

/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : Aps_DefPsPdpContext()
 Description    : 定义，修改，删除PDP CONTEXT.包括对两个数据结构的操作,FLASH中
                  PDP数据表和全局变量数据表.
 Input          : ClientId, 识别某个应用程序;
                  OpId, 识别某个应用程序中的某次呼叫;
                  pPara,指向PDP CONTEXT主结构的指针;
                        没有PDP CONTEXT主结构参数IE，表示删除PDP CONTEXT;
                        有PDP CONTEXT主结构参数IE，表示定义或修改PDP CONTEXT，
                        已经定义了PDP CONTEXT则为修改，否则，为定义。
 Output         : NO
 Return Value   :
 Calls          : VOS_UINT16 NV_Read();
                  VOS_UINT16 NV_Write();

 Called By      : TAFM
 Pseudocode     :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

  3.日    期   : 2012年01月02日
    作    者   : s46746
    修改内容   : DTS2012010200121: cgdcont不能删除二次PDP上下文,cgdscont不能
                 删除主PDP上下文,只能定义主PDP已经定义的二次上下文

  4.日    期   : 2012年5月26日
    作    者   : A00165503
    修改内容   : DTS2012052404203: +CGDCONT命令增加对<CID 0>的支持
*****************************************************************************/
VOS_VOID Aps_DefPsPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    ulReturn                            = TAF_APS_SUCC;

    if ( ( VOS_NULL == pPara )
      || (!(TAF_PS_PDP_CONTEXT_CID_VALID(pPara->ucCid))) )
    {
        APS_WARN_LOG("Aps_DefPsPdpContext input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }


    /*将对应的项暂时保存到临时变量g_TmpPdpTab中*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];


    /*根据pPara判断是否是删除PDP_PRI参数*/
    if (VOS_FALSE == pPara->ucDefined)
    {
        /*删除PDP_PRI定义*/
        /*----------------------------------------------------------
           CID0的删除操作协议上要求恢复特定的默认值, 目前不支持,
           统一返回ERROR, 参考 TS 27.007 R11 section 10.1.0
        ----------------------------------------------------------*/
        if (0 == pPara->ucCid)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "Aps_DefPsPdpContext: Can't delete CID <0>");
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /*根据终端的要求，如果该指定删除的CID不处于APS_PDP_INACTIVE状态，
           则禁止做删除操作*/
        if (TAF_TRUE == Taf_CheckActCid(pPara->ucCid))
        {
            APS_WARN_LOG("Aps_DefPsPdpContext: Can't delete the Context of \
                          the CID which is not in APS_PDP_INACTIVE state!");
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /*如果该项的PDP_PRI参数子项已经定义*/
        if ( VOS_TRUE == g_TmpPdpTab.ucUsed )
        {
            /* 如果该项的PDP定义的是二次PDP上下文，不能删除 */
            if (VOS_TRUE == g_TmpPdpTab.ucPriCidFlag)
            {
                *pulErrCode = TAF_PARA_SET_ERROR;
                return;
            }
            else
            {
                /*清除PDP的定义标识*/
                g_TafCidTab[pPara->ucCid].ucUsed        = VOS_FALSE;

                Aps_DeleteLinkedCidSecPdpContext(pPara->ucCid);
            }
        }
        else
        {
            /*若本来就没有定义,则直接上报删除成功*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {
        /*定义或者修改PDP_PRI参数*/
        ulReturn = Aps_ChngPdpPri( pPara, pPara->ucCid );
        if ( TAF_APS_FAIL == ulReturn )
        {
            /*如果修改失败*/
            g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;

            APS_WARN_LOG("Aps_ChngPdpPri ERR!");
            *pulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
            return;
        }

        /*如果原来是二次PDP，则进行标识操作和必要参数的设置*/
        if (g_TafCidTab[pPara->ucCid].ucPriCidFlag)
        {
            g_TafCidTab[pPara->ucCid].ucPriCidFlag  = VOS_FALSE;
        }

        /*AT或APP定义PdpPri参数时,对于没有输入的参数，用此函数进行缺省定义。*/
        Aps_DefPdpPri( pPara, pPara->ucCid );

    }

    ulReturn = Aps_NvimAct( pPara->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {
        /*操作成功*/
        *pulErrCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*操作NVIM失败，恢复原值*/
        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        APS_WARN_LOG("NVIM ACT ERR!");
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        return;
    }
}


/*****************************************************************************
 Prototype      : Aps_ChngPdpPri
 Description    : APP修改PdpPri参数时,用此函数将传入的参数填入PDP表中.
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

  3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，协议升级，增加enImCnSignalFlg和enPcscfDiscovery

*****************************************************************************/
VOS_UINT32  Aps_ChngPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
)
{
    /*pPdpPriPara和ucCid 是否为空在主调函数中检查，不在此被调函数中检查*/

    if ( VOS_TRUE  == pPdpPriPara->bitOpPdpType )
    {
        g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType   = pPdpPriPara->enPdpType;
    }

    if ( VOS_TRUE  == pPdpPriPara->bitOpApn )
    {
        /* 字符串转换为没有字符串结束符的参数形式 */
        PS_MEM_SET(&g_TafCidTab[ucCid].CidTab.stApn, 0x00,
                   sizeof(TAF_PDP_APN_STRU));

        g_TafCidTab[ucCid].CidTab.stApn.ucLength = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pPdpPriPara->aucApn);
        PS_MEM_CPY(g_TafCidTab[ucCid].CidTab.stApn.aucValue,
                   pPdpPriPara->aucApn,
                   TAF_MAX_APN_LEN);
    }

    if ( (VOS_TRUE     == pPdpPriPara->bitOpPdpAddr)
      && (TAF_PDP_IPV4 == pPdpPriPara->stPdpAddr.enPdpType) )
    {
        /* 字符串转换为没有字符串结束符的参数形式 */
        PS_MEM_SET(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr, 0x00,
                   sizeof(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr));

        PS_MEM_CPY(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr,
                   pPdpPriPara->stPdpAddr.aucIpv4Addr,
                   TAF_IPV4_ADDR_LEN);
    }

    if ( VOS_TRUE  == pPdpPriPara->bitOpPdpDcomp )
    {
        g_TafCidTab[ucCid].CidTab.enPdpDcomp  = pPdpPriPara->enPdpDcomp;
    }

    if ( VOS_TRUE  == pPdpPriPara->bitOpPdpHcomp )
    {
        g_TafCidTab[ucCid].CidTab.enPdpHcomp  = pPdpPriPara->enPdpHcomp;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpIpv4AddrAlloc )
    {
        g_TafCidTab[ucCid].CidTab.enIpv4AddrAlloc = pPdpPriPara->enIpv4AddrAlloc;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpEmergencyInd)
    {
        g_TafCidTab[ucCid].CidTab.enEmergencyInd = pPdpPriPara->enEmergencyFlg;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpImCnSignalFlg)
    {
        g_TafCidTab[ucCid].CidTab.enImCnSignalFlg = pPdpPriPara->enImCnSignalFlg;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpPcscfDiscovery)
    {
        g_TafCidTab[ucCid].CidTab.enPcscfDiscovery = pPdpPriPara->enPcscfDiscovery;
    }

    return  TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      : Aps_DefPdpPri
 Description    : APP定义PdpPri参数时,对于没有输入的参数，用此函数进行缺省定义。
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3.日    期   : 2012年5月18日
    作    者   : z60575
    修改内容   : DTS2012051706679 添加ucIpv4AddrAlloc和ucEmergency
  4.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，协议升级，增加enImCnSignalFlg和enPcscfDiscovery

*****************************************************************************/
VOS_VOID  Aps_DefPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
)
{
    /*pQosPara和ucCid 在主调函数中检查，不在此被调函数中检查*/

    if ( (VOS_FALSE == pPdpPriPara->bitOpPdpType)
      && (TAF_PDP_IPV4   != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
#if ( FEATURE_ON == FEATURE_IPV6 )
      && (TAF_PDP_IPV6   != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
      && (TAF_PDP_IPV4V6 != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
#endif
      && (TAF_PDP_PPP    != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType) )
    {
        g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType   =   TAF_PDP_IPV4;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpApn)
    {
        PS_MEM_SET(g_TafCidTab[ucCid].CidTab.stApn.aucValue, 0, TAF_MAX_APN_LEN);
        g_TafCidTab[ucCid].CidTab.stApn.ucLength    =   0;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpPdpAddr)
    {
        PS_MEM_SET(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr, 0, TAF_IPV4_ADDR_LEN);
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpPdpDcomp)
    {
        g_TafCidTab[ucCid].CidTab.enPdpDcomp        =   TAF_PDP_D_COMP_OFF;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpPdpHcomp)
    {
        g_TafCidTab[ucCid].CidTab.enPdpHcomp        =   TAF_PDP_H_COMP_OFF;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpIpv4AddrAlloc)
    {
        g_TafCidTab[ucCid].CidTab.enIpv4AddrAlloc   =   0;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpEmergencyInd)
    {
        g_TafCidTab[ucCid].CidTab.enEmergencyInd       =   0;
    }

    if ( VOS_FALSE   == pPdpPriPara->bitOpImCnSignalFlg)
    {
        g_TafCidTab[ucCid].CidTab.enImCnSignalFlg = TAF_PDP_NOT_FOR_IMS_CN_SIG_ONLY;
    }

    if ( VOS_FALSE   == pPdpPriPara->bitOpPcscfDiscovery)
    {
        g_TafCidTab[ucCid].CidTab.enPcscfDiscovery = TAF_PDP_PCSCF_DISCOVERY_NOT_INFLUENCED;
    }

    g_TafCidTab[ucCid].ucUsed                   = VOS_TRUE;

    return;
}

/*****************************************************************************
 Prototype      : Aps_DefPsSecPdpContext()
 Description    : 定义、修改、删除Secondary PDP Context。定义二次PDP，要求该
                  PDP已经被定义过，通过此函数将它转换为二次PDP项，关联到一个
                  主PDP上。注意二次激活关联到的主激活必须是IP类型,不能是PPP类型
 Input          : ClientId, 识别某个应用程序;
                  OpId, 识别某个应用程序中的某次呼叫;
                  pPara,指向TAF_PDP_SEC_EXT_STRU结构的指针;
                        没有TAF_PDP_SEC_EXT_STRU结构参数IE，表示删除;
                        有TAF_PDP_SEC_EXT_STRU结构参数IE，表示定义或修改，
                        已经定义了TAF_PDP_SEC_EXT_STRU则为修改，否则，为定义。
 Output         :
 Return Value   : 0--定义、修改、删除操作成功;
                  1--定义、修改、删除操作失败;
 Data Access    :
 Data Update    : g_TafCidTab[]
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3.日    期   : 2012年01月02日
    作    者   : s46746
    修改内容   : DTS2012010200121: cgdcont不能删除二次PDP上下文,cgdscont不能
                 删除主PDP上下文,只能定义主PDP已经定义的二次上下文
  4.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，协议升级，结构变更

*****************************************************************************/
VOS_VOID Aps_DefPsSecPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    if ( VOS_NULL == pPara )
    {   /*输入参数有错*/
        *pulErrCode = TAF_PARA_SET_ERROR;
        APS_WARN_LOG("input para err!");
        return;
    }

    /*将对应的项暂时保存到临时变量g_TmpPdpTab中*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];

    if (VOS_FALSE == pPara->ucDefined)
    {
        /*删除定义*/
        /*如果该项的PDP_PRI参数子项已经定义*/
        if (VOS_TRUE == g_TmpPdpTab.ucUsed )
        {
            if (VOS_TRUE == g_TmpPdpTab.ucPriCidFlag)
            {
                /* 主PDP未定义二次PDP定义时被去定义*/
                g_TafCidTab[pPara->ucCid].ucUsed        = VOS_FALSE;
                g_TafCidTab[pPara->ucCid].ucPriCidFlag  = VOS_FALSE;
            }
            else
            {
                *pulErrCode = TAF_PARA_SET_ERROR;
                return;
            }
        }
        else
        {   /*若本来就没有定义,则直接上报删除成功*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {
        if ((VOS_FALSE == g_TafCidTab[pPara->ucLinkdCid].ucUsed)
         || (VOS_TRUE == g_TafCidTab[pPara->ucLinkdCid].ucPriCidFlag))
        {

            /* 若本来就没有定义,或定义的是二次PDP上下文返回错误 */
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /*定义或者修改参数*/
        Aps_ChngSecPara(pPara);

        /*该项没有定义，则是定义，需要缺省设置没有输入的值*/
        if (  (TAF_FREE == g_TmpPdpTab.ucUsed)
            ||(TAF_FREE == g_TmpPdpTab.ucPriCidFlag) )
        {
            /*若没输入主CID，则出错*/
            if (VOS_FALSE == pPara->bitOpLinkdCid)
            {
                g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;

                *pulErrCode = TAF_PARA_SET_ERROR;
                APS_WARN_LOG("input para err!");
                return;
            }

        }

        /*APP定义SecPdpPara参数时,对于没有输入的参数，用此函数进行缺省定义。*/
        Aps_DefSecPara( pPara );
    }


    ulReturn = Aps_NvimAct( pPara->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {   /*操作成功*/
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*操作NVIM失败，恢复原值*/

        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("input para err!");
    }
    return;
}

/*****************************************************************************
 Prototype      : Aps_ChngSecPara
 Description    : APP修改PdpPri参数时,用此函数将传入的参数填入PDP表中.
 Input          : pPara
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

  3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，协议升级，增加enImCnSignalFlg和enPcscfDiscovery

*****************************************************************************/
VOS_VOID  Aps_ChngSecPara(TAF_PDP_SEC_CONTEXT_EXT_STRU   *pSecPara )
{
    if ( pSecPara->bitOpLinkdCid)
    {
        g_TafCidTab[pSecPara->ucCid].ucPriCid
            = pSecPara->ucLinkdCid;
    }

    if ( pSecPara->bitOpPdpDcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpDcomp
            = pSecPara->enPdpDcomp;
    }

    if ( pSecPara->bitOpPdpHcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpHcomp
            = pSecPara->enPdpHcomp;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_DefSecPara
 Description    : APP定义PdpPri参数时,对于没有输入的参数，用此函数进行缺省定义。
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

  3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，结构变更

*****************************************************************************/
VOS_VOID  Aps_DefSecPara( TAF_PDP_SEC_CONTEXT_EXT_STRU   *pSecPara )
{
    g_TafCidTab[pSecPara->ucCid].ucUsed            = VOS_TRUE;
    g_TafCidTab[pSecPara->ucCid].ucPriCidFlag      = VOS_TRUE;

    if ( VOS_FALSE == pSecPara->bitOpPdpDcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpDcomp
            = TAF_PDP_D_COMP_OFF;
    }

    if ( VOS_FALSE == pSecPara->bitOpPdpHcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpHcomp
            = TAF_PDP_H_COMP_OFF;
    }

    return;
}

/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */


/*****************************************************************************
 Prototype      : Aps_DefPsDns()
 Description    : 定义、修改、删除DNS的鉴权信息。
 Input          : ClientId, 识别某个应用程序;
                  OpId, 识别某个应用程序中的某次呼叫;
                  pPara,指向TAF_PDP_AUTH_EXT_STRU结构的指针;
                        没有TAF_PDP_AUTH_EXT_STRU结构参数IE，表示删除;
                        有TAF_PDP_AUTH_EXT_STRU结构参数IE，表示定义或修改，
                        已经定义了TAF_PDP_AUTH_EXT_STRU则为修改，否则，为定义。
                  ucCid:[1,11]
 Output         :
 Return Value   : 0--定义、修改、删除操作成功;
                  1--定义、修改、删除操作失败;
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

  3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，结构变更

*****************************************************************************/
VOS_VOID Aps_DefPsDns(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_DNS_EXT_STRU               *pDnsPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    if ( ( VOS_NULL == pDnsPara )
         || (!(TAF_PS_CID_VALID(pDnsPara->ucCid))))
    {
        /*上报参数设置失败*/
        *pulErrCode = TAF_PARA_SET_ERROR;
        APS_WARN_LOG("input para err!");
        return;
    }

    /*将对应的项暂时保存到临时变量g_TmpPdpTab中*/
    g_TmpPdpTab = g_TafCidTab[pDnsPara->ucCid];

    if (VOS_FALSE == pDnsPara->ucDefined)
    {   /*删除定义*/
        if ( (VOS_TRUE == g_TmpPdpTab.ucDnsFlag)
            ||(VOS_TRUE == g_TmpPdpTab.DnsTab.bitOpPrimDnsAddr)
            ||(VOS_TRUE == g_TmpPdpTab.DnsTab.bitOpSecDnsAddr) )
        {
            g_TafCidTab[pDnsPara->ucCid].ucDnsFlag          = VOS_FALSE;
            g_TafCidTab[pDnsPara->ucCid].DnsTab.bitOpPrimDnsAddr   = VOS_FALSE;
            g_TafCidTab[pDnsPara->ucCid].DnsTab.bitOpSecDnsAddr   = VOS_FALSE;
        }
        else
        {   /*若本来就没有定义,则直接上报删除成功*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {
        /*将参数填入全局变量*/
        ulReturn = Aps_ChngDns( pDnsPara, pDnsPara->ucCid );
        if ( TAF_APS_FAIL == ulReturn )
        {   /*如果修改失败*/
            g_TafCidTab[pDnsPara->ucCid] = g_TmpPdpTab;

            *pulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
            APS_WARN_LOG("NVIM ACT ERR!");
            return;
        }

        /*该项的DNS子项没有定义，则是定义，但DNS不需要缺省设置没有输入的参数值*/
        if ( TAF_FREE == g_TmpPdpTab.ucDnsFlag)
        {
            g_TafCidTab[pDnsPara->ucCid].ucDnsFlag = TAF_USED;
        }
    }

    ulReturn = Aps_NvimAct( pDnsPara->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {   /*操作成功*/
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*操作NVIM失败，恢复原值*/

        g_TafCidTab[pDnsPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_ChngDns
 Description    : APP修改TFT参数时,用此函数将传入的参数填入PDP表中.
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

  3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，结构变更

*****************************************************************************/
VOS_UINT32  Aps_ChngDns(
    TAF_PDP_DNS_EXT_STRU               *pDnsPara,
    VOS_UINT8                           ucCid
)
{

    /*pQosPara和ucCid 在主调函数中检查，不在此被调函数中检查*/

    if ( TAF_USED == pDnsPara->bitOpPrimDnsAddr)
    {
        g_TafCidTab[ucCid].DnsTab.bitOpPrimDnsAddr = VOS_TRUE;

        PS_MEM_CPY(g_TafCidTab[ucCid].DnsTab.aucPrimDnsAddr,
                   pDnsPara->aucPrimDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    if ( TAF_USED == pDnsPara->bitOpSecDnsAddr)
    {
        g_TafCidTab[ucCid].DnsTab.bitOpSecDnsAddr = VOS_TRUE;

        PS_MEM_CPY(g_TafCidTab[ucCid].DnsTab.aucSecDnsAddr,
                   pDnsPara->aucSecDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    return  TAF_APS_SUCC;
}
/*****************************************************************************
 Prototype      : Aps_DefPs3gReqQos()
 Description    : 定义、修改、删除PDP Context中的3G QOS参数
 Input          : ClientId, 识别某个应用程序;如果CID不指定，表示删除所有定义的CID
                  OpId, 识别某个应用程序中的某次呼叫;
                  pPara,指向TAF_PDP_QOS_EXT_STRU结构的指针;
                        没有TAF_PDP_QOS_EXT_STRU结构参数IE，表示删除;
                        有TAF_PDP_QOS_EXT_STRU结构参数IE，表示定义或修改，
                        已经定义了TAF_PDP_QOS_EXT_STRU则为修改，否则，为定义。
 Output         :
 Return Value   : 0--定义、修改、删除操作成功;
                  1--定义、修改、删除操作失败;
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

*****************************************************************************/
VOS_VOID Aps_DefPs3gReqQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    APS_NORM_LOG("into Aps_DefPs3gReqQos ");

    if ( ( VOS_NULL == pPara )
         || (!(TAF_PS_CID_VALID(pPara->ucCid))))
    {
        APS_WARN_LOG("input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /*将对应的项暂时保存到临时变量g_TmpPdpTab中*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];


    /*根据pPara判断是否是删除PDP表参数*/
    if (VOS_FALSE == pPara->ucDefined)
    {   /*删除QOS定义*/
        APS_NORM_LOG("Aps_DefPs3gReqQos Delete qos def !");
        if ( VOS_TRUE == g_TmpPdpTab.ucQosTabFlag )
        {   /*该项的QOS子项已经定义*/
            g_TafCidTab[pPara->ucCid].ucQosTabFlag  = VOS_FALSE;
        }
        else
        {   /*若本来就没有定义,则直接上报删除成功*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {   /*定义或者修改QOS*/
        APS_NORM_LOG("Aps_DefPs3gReqQos Chng qos def !");
        Aps_ChngQos( pPara, pPara->ucCid );

        /*定义QOS时，对于没有输入的参数，用此函数进行缺省定义*/
        Aps_DefQos( pPara, pPara->ucCid );
    }

    /* 参考Q实现效果，在使用AT+CGEQREQ进行QOS的设置时，并不写入NV */
    if ( TAF_APS_SUCC   == Aps_NvimAct( pPara->ucCid ) )
    {   /*操作成功*/
        APS_NORM_LOG("Aps_DefPs3gReqQos Chng qos succ !");
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*操作NVIM失败，恢复原值*/
        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }
    return;

}

/*****************************************************************************
 函 数 名  : Aps_ChngQos
 功能描述  : APP修改QOS参数时,用此函数将传入的参数填入PDP表中.
 输入参数  : pPara
             ucCid
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_ChngQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{

    /*pQosPara和ucCid 在主调函数中检查，不在此被调函数中检查*/

    if ( VOS_TRUE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[ucCid].QosTab.ucTrafficClass    = pQosPara->ucTrafficClass;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[ucCid].QosTab.ucDeliverOrder    = pQosPara->ucDeliverOrder;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[ucCid].QosTab.ucDeliverErrSdu   = pQosPara->ucDeliverErrSdu;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[ucCid].QosTab.usMaxSduSize      = pQosPara->usMaxSduSize;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[ucCid].QosTab.ulMaxBitUl        = pQosPara->ulMaxBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[ucCid].QosTab.ulMaxBitDl        = pQosPara->ulMaxBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[ucCid].QosTab.ucResidualBer     = pQosPara->ucResidualBer;
    }

    if ( VOS_TRUE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[ucCid].QosTab.ucSduErrRatio     = pQosPara->ucSduErrRatio;
    }

    if ( VOS_TRUE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[ucCid].QosTab.usTransDelay      = pQosPara->usTransDelay;
    }

    if ( VOS_TRUE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[ucCid].QosTab.ucTraffHandlePrior= pQosPara->ucTraffHandlePrior;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[ucCid].QosTab.ulGuarantBitUl    = pQosPara->ulGtdBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[ucCid].QosTab.ulGuarantBitDl    = pQosPara->ulGtdBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[ucCid].QosTab.ucSrcStatisticsDescriptor = pQosPara->ucSrcStatisticsDes;
    }

    if ( VOS_TRUE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[ucCid].QosTab.ucSignallingIndication    = pQosPara->ucSignalIndication;
    }

    return;

}

/*****************************************************************************
 函 数 名  : Aps_DefQos
 功能描述  : 定义QOS时，对于没有输入的参数，用此函数进行缺省定义。
 输入参数  : pPara
             ucCid
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_DefQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{
    /*pQosPara和ucCid 在主调函数中检查，不在此被调函数中检查*/

    /*QOS标识置位*/
    g_TafCidTab[pQosPara->ucCid].ucQosTabFlag               = TAF_USED;

    if ( TAF_FREE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucTrafficClass  = APS_APPQOS_TRAFFCLASS_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucDeliverOrder  = APS_APPQOS_DELIVERORDER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucDeliverErrSdu = APS_APPQOS_DELIVEReRRSDU_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.usMaxSduSize    = APS_APPQOS_MAXSDUSIZE_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulMaxBitUl      = APS_APPQOS_MAXBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulMaxBitDl      = APS_APPQOS_MAXBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucResidualBer   = APS_APPQOS_RESIDUALBER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucSduErrRatio   = APS_APPQOS_SDUERRRATIO_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.usTransDelay    = APS_APPQOS_TRANSDELAY_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucTraffHandlePrior = APS_APPQOS_TRAFFHANDPRIOR_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulGuarantBitUl  = APS_APPQOS_GUARANTBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulGuarantBitDl  = APS_APPQOS_GUARANTBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[ucCid].QosTab.ucSrcStatisticsDescriptor = APS_APPQOS_SRCSTATISTICSDES_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[ucCid].QosTab.ucSignallingIndication    = APS_APPQOS_SIGNALINDICATION_SUBSCRIB;
    }

    return;

}
/*****************************************************************************
 Prototype      : Aps_DefPs3gMinAcceptQos()
 Description    : 定义、修改、删除PDP Context中的3G最小可接受QOS参数。实现过程
                  与定义QOS非常类似。
 Input          : ClientId, 识别某个应用程序;
                  OpId, 识别某个应用程序中的某次呼叫;
                  pPara,指向TAF_PDP_QOS_EXT_STRU结构的指针;
                        没有TAF_PDP_QOS_EXT_STRU结构参数IE，表示删除MINQOS;
                        有TAF_PDP_QOS_EXT_STRU结构参数IE，表示定义或修改MINQOS，
                        已经定义了TAF_PDP_QOS_EXT_STRU则为修改，否则，为定义。
 Output         :
 Return Value   : 0--定义、修改、删除操作成功;
                  1--定义、修改、删除操作失败;
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

*****************************************************************************/
VOS_VOID Aps_DefPs3gMinAcceptQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    ulReturn                            = TAF_APS_SUCC;

    if ( ( VOS_NULL == pPara )
         || (!(TAF_PS_CID_VALID(pPara->ucCid))))
    {
        APS_WARN_LOG("input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /*将对应的项暂时保存到临时变量g_TmpPdpTab中*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];


    /*根据pPara判断是否是删除PDP表参数*/
    if (VOS_FALSE == pPara->ucDefined)
    {   /*删除MINQOS定义*/

        if ( VOS_TRUE == g_TmpPdpTab.ucMinQosFlag )
        {   /*该项的MINQOS子项已经定义*/
            g_TafCidTab[pPara->ucCid].ucMinQosFlag  = VOS_FALSE;
        }
        else
        {   /*若本来就没有定义,则直接上报删除成功*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {   /*定义或者修改MINQOS*/

        Aps_ChngMinQos(  pPara, pPara->ucCid );

        /*定义MINQOS时，对于没有输入的参数，用此函数进行缺省定义,缺省
           值为网络协商,即网络返回任何值都接受*/
        Aps_DefMinQos( pPara, pPara->ucCid );
    }

    ulReturn        =  Aps_NvimAct( pPara->ucCid );
    if ( TAF_APS_SUCC   == ulReturn )
    {   /*操作成功*/

        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*操作NVIM失败，恢复原值*/
        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }
    return;

}

/*****************************************************************************
 函 数 名  : Aps_ChngMinQos
 功能描述  : APP修改QOS参数时,用此函数将传入的参数填入PDP表中.
 输入参数  : pPara
             ucCid
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_ChngMinQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{

    /*pQosPara和ucCid 在主调函数中检查，不在此被调函数中检查*/

    if ( VOS_TRUE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[ucCid].MinQosTab.ucTrafficClass    = pQosPara->ucTrafficClass;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[ucCid].MinQosTab.ucDeliverOrder    = pQosPara->ucDeliverOrder;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[ucCid].MinQosTab.ucDeliverErrSdu   = pQosPara->ucDeliverErrSdu;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[ucCid].MinQosTab.usMaxSduSize      = pQosPara->usMaxSduSize;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulMaxBitUl        = pQosPara->ulMaxBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulMaxBitDl        = pQosPara->ulMaxBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[ucCid].MinQosTab.ucResidualBer     = pQosPara->ucResidualBer;
    }

    if ( VOS_TRUE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[ucCid].MinQosTab.ucSduErrRatio     = pQosPara->ucSduErrRatio;
    }

    if ( VOS_TRUE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[ucCid].MinQosTab.usTransDelay      = pQosPara->usTransDelay;
    }

    if ( VOS_TRUE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[ucCid].MinQosTab.ucTraffHandlePrior= pQosPara->ucTraffHandlePrior;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulGuarantBitUl    = pQosPara->ulGtdBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulGuarantBitDl    = pQosPara->ulGtdBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[ucCid].MinQosTab.ucSrcStatisticsDescriptor = pQosPara->ucSrcStatisticsDes;
    }

    if ( VOS_TRUE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[ucCid].MinQosTab.ucSignallingIndication    = pQosPara->ucSignalIndication;
    }

    return;

}

/*****************************************************************************
 函 数 名  : Aps_DefMinQos
 功能描述  : 定义MINQOS时，对于没有输入的参数，用此函数进行缺省定义,缺省
             值为网络协商,即网络返回任何值都接受。
 输入参数  : pPara
             ucCid
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_DefMinQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{
    /*pQosPara和ucCid 在主调函数中检查，不在此被调函数中检查*/

    /*QOS标识置位*/
    g_TafCidTab[pQosPara->ucCid].ucMinQosFlag                  = TAF_USED;

    if ( TAF_FREE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucTrafficClass  = APS_APPQOS_TRAFFCLASS_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucDeliverOrder  = APS_APPQOS_DELIVERORDER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucDeliverErrSdu = APS_APPQOS_DELIVEReRRSDU_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.usMaxSduSize    = APS_APPQOS_MAXSDUSIZE_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulMaxBitUl      = APS_APPQOS_MAXBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulMaxBitDl      = APS_APPQOS_MAXBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucResidualBer   = APS_APPQOS_RESIDUALBER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucSduErrRatio   = APS_APPQOS_SDUERRRATIO_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.usTransDelay    = APS_APPQOS_TRANSDELAY_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucTraffHandlePrior = APS_APPQOS_TRAFFHANDPRIOR_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulGuarantBitUl  = APS_APPQOS_GUARANTBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulGuarantBitDl  = APS_APPQOS_GUARANTBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucSrcStatisticsDescriptor = APS_APPQOS_SRCSTATISTICSDES_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucSignallingIndication    = APS_APPQOS_SIGNALINDICATION_SUBSCRIB;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_DefNdisAuthdata()
 Description    : 定义，修改，删除NDIS的AUTHDATA.包括对两个数据结构的操作,FLASH中
                  AUTHDATA数据表和全局变量数据表.
 Input          : ClientId, 识别某个应用程序;
                  OpId, 识别某个应用程序中的某次呼叫;
                  pPara,指向AUTHDATA主结构的指针;
                        没有AUTHDATA主结构参数IE，表示删除AUTHDATA;
                        有AUTHDATA主结构参数IE，表示定义或修改AUTHDATA，
                        已经定义了AUTHDATA则为修改，否则，为定义。
 Output         : NO
 Return Value   :
 Calls          :
 History        :
  1.Date        : 2009-09-02
    Author      : L47619
    Modification: Created function

  2.Date        : 2011-07-21
    Author      : k66584
    Modification: 问题单号: DTS2011040706046，更新暂不使用的NV项UENDIS_AUTHDATA_0

  3.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  4.日    期   : 2012年1月27日
    作    者   : h44270
    修改内容   : PS融合项目，删除冗余代码和全局变量

  5.日    期   : 2013年12月25日
    作    者   : A00165503
    修改内容   : DTS2013122403650: ^AUTHDATA命令支持CID0
*****************************************************************************/
VOS_VOID    Aps_DefNdisAuthdata (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_AUTHDATA_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode)
{
    VOS_UINT32                          ulReturn;
    VOS_UINT32                          ulNvimRet;
    TAF_NDIS_AUTHDATA_TABLE_STRU        TmpAuthdataTab;
    TAF_NDIS_AUTHDATA_TABLE_STRU        stTmpAuthdataTab;

    ulReturn                            = TAF_APS_SUCC;
    if ( ( VOS_NULL == pPara )
        || (!(TAF_PS_PDP_CONTEXT_CID_VALID(pPara->ucCid))))
    {
        APS_WARN_LOG("Aps_DefNdisAuthdata input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    stTmpAuthdataTab = g_ApsNdisAuthdataTab[pPara->ucCid];

    if (VOS_FALSE == pPara->ucDefined)
    {   /*删除AUTHDATA定义*/

        /*如果该项的PDP_PRI参数子项已经定义*/
        if ( VOS_TRUE == stTmpAuthdataTab.ucUsed )
        {
            /*清除PDP的定义标识*/
            g_ApsNdisAuthdataTab[pPara->ucCid].ucUsed = VOS_FALSE;
        }
        else
        {   /*若本来就没有定义,则直接上报删除成功*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {   /*定义或者修改PDP_PRI参数*/

        ulReturn = Aps_ChngAuthdata( pPara, pPara->ucCid );
        if ( TAF_APS_FAIL == ulReturn )
        {   /*如果修改失败*/
            g_ApsNdisAuthdataTab[pPara->ucCid] = stTmpAuthdataTab;
            *pulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
            APS_WARN_LOG("Aps_ChngAuthdata ERR!");
            return;
        }

        /*AT或APP定义PdpPri参数时,对于没有输入的参数，用此函数进行缺省定义。*/
        Aps_DefAuthdata( pPara, pPara->ucCid );
    }

    if ( NV_OK == NV_Read((NV_ID_ENUM_U16)((en_NV_Item_NDIS_Authdata_1 + pPara->ucCid) - 1),
                              (VOS_VOID*)&TmpAuthdataTab,
                              sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU)) )
    {
        if ( 0 == VOS_MemCmp(&TmpAuthdataTab,
                               &g_ApsNdisAuthdataTab[pPara->ucCid],
                               sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU)) )
        {
            *pulErrCode = TAF_PARA_OK;
            APS_INFO_LOG("Aps_DefNdisAuthdata():The content to write is same as NV's");
            return;
        }
    }

    /* 写入NV */
    ulNvimRet   = NV_Write((NV_ID_ENUM_U16)((en_NV_Item_NDIS_Authdata_1 + pPara->ucCid) - 1),
                            &g_ApsNdisAuthdataTab[pPara->ucCid],
                            sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU));

    if (TAF_APS_SUCC == ulNvimRet)
    {   /*操作成功*/

        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*操作NVIM失败，恢复原值*/

        g_ApsNdisAuthdataTab[pPara->ucCid] = stTmpAuthdataTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }

    return;
}


/*****************************************************************************
 Prototype      : Aps_ChngAuthdata
 Description    : APP修改authdata参数时,用此函数将传入的参数填入PDP表中.
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_ApsNdisAuthdataTab[ucCid]
 Calls          :
 Called By      : Aps_DefNdisAuthdata
 History        : ---
  1.Date        : 2009-09-02
    Author      : L47619
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

*****************************************************************************/
VOS_UINT32  Aps_ChngAuthdata(
    TAF_AUTHDATA_EXT_STRU              *pAuthdataPara,
    VOS_UINT8                           ucCid
)
{
    if ( VOS_TRUE  == pAuthdataPara->bitOpAuthType)
    {
        g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType = pAuthdataPara->enAuthType;
    }

    if ( VOS_TRUE  == pAuthdataPara->bitOpPlmn)
    {
        PS_MEM_CPY( g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn,
                    pAuthdataPara->aucPlmn,
                    VOS_StrLen((VOS_CHAR *)pAuthdataPara->aucPlmn) + 1);
    }

    if ( VOS_TRUE  == pAuthdataPara->bitOpPassWord)
    {
        PS_MEM_CPY( g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                    pAuthdataPara->aucPassWord,
                    VOS_StrLen((VOS_CHAR *)pAuthdataPara->aucPassWord) + 1);
    }

    if ( VOS_TRUE  == pAuthdataPara->bitOpUserName)
    {
        PS_MEM_CPY( g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                    pAuthdataPara->aucUserName,
                    VOS_StrLen((VOS_CHAR *)pAuthdataPara->aucUserName) + 1);
    }

    return  TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      : Aps_DefAuthdata
 Description    : APP定义AUTHDATA参数时,对于没有输入的参数，用此函数进行缺省定义。
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_ApsNdisAuthdataTab[ucCid]
 Calls          :
 Called By      : Aps_DefNdisAuthdata
 History        : ---
  1.Date        : 2009-09-02
    Author      : L47619
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

*****************************************************************************/
VOS_VOID  Aps_DefAuthdata(
    TAF_AUTHDATA_EXT_STRU              *pAuthdataPara,
    VOS_UINT8                           ucCid
)
{
    if ( TAF_FREE  == pAuthdataPara->bitOpAuthType)
    {
        g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType = TAF_PDP_AUTH_TYPE_NONE;
    }

    if ( TAF_FREE  == pAuthdataPara->bitOpPlmn)
    {
        PS_MEM_SET(g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn, 0, TAF_MAX_AUTHDATA_PLMN_LEN + 1);
    }

    if ( TAF_FREE  == pAuthdataPara->bitOpPassWord)
    {
        PS_MEM_SET(g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                   0,
                   TAF_MAX_AUTHDATA_PASSWORD_LEN + 1);
    }

    if ( TAF_FREE  == pAuthdataPara->bitOpUserName)
    {
        PS_MEM_SET(g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                   0,
                   TAF_MAX_AUTHDATA_USERNAME_LEN + 1);
    }

    g_ApsNdisAuthdataTab[ucCid].ucUsed = VOS_TRUE;

    return;
}

/*****************************************************************************
 Prototype      : Aps_QuePri()
 Description    :
 Input          : ucCid
 Output         : PdpPriExtPara,
                  pucErrorCode
 Return Value   :
 Data Access    : g_TafCidTab
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3.日    期   : 2012年5月18日
    作    者   : z60575
    修改内容   : DTS2012051706679 添加ucIpv4AddrAlloc和ucEmergency
    3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，结构变更

*****************************************************************************/
VOS_VOID Aps_QuePri(
    VOS_UINT8                           ucCid,
    TAF_PRI_PDP_QUERY_INFO_STRU        *pPdpPriPara,
    VOS_UINT32                         *pulErrorCode
)
{
    /*初始化*/
    *pulErrorCode                       = TAF_PARA_OK;

    /*该PDP没有定义*/
    if (TAF_FREE == g_TafCidTab[ucCid].ucUsed)
    {
        *pulErrorCode                    = TAF_PARA_PDP_CONTEXT_NOT_DEFINED;
        return;
    }

    /*该PDP被定义成二次PDP*/
    if (TAF_USED == g_TafCidTab[ucCid].ucPriCidFlag)
    {
       *pulErrorCode                    = TAF_PARA_PDP_CONTEXT_NOT_DEFINED;
        return;
    }

    pPdpPriPara->ucCid                  = ucCid;

    /*PDPTYPE*/
    pPdpPriPara->stPriPdpInfo.stPdpAddr.enPdpType   = g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType;

    /*APN*/
    if ( g_TafCidTab[ucCid].CidTab.stApn.ucLength >  TAF_MAX_APN_LEN )
    {
        *pulErrorCode                   = TAF_PARA_UNSPECIFIED_ERROR;
        return;
    }
    else if( 0 != g_TafCidTab[ucCid].CidTab.stApn.ucLength )
    {
        pPdpPriPara->stPriPdpInfo.stApn.ucLength = g_TafCidTab[ucCid].CidTab.stApn.ucLength;
        PS_MEM_CPY(pPdpPriPara->stPriPdpInfo.stApn.aucValue,
                   g_TafCidTab[ucCid].CidTab.stApn.aucValue,
                   pPdpPriPara->stPriPdpInfo.stApn.ucLength);
    }
    else
    {
        pPdpPriPara->stPriPdpInfo.stApn.aucValue[0] = '\0';
    }

    /*ADDR*/
    /* 原先的实现:PPP类型的IP地址不上报，只有IP类型的地址才上报
       修改后的实现:为了与终端的实现一致，现在无论是IP还是PPP类型都上报IP地址*/
    PS_MEM_CPY(pPdpPriPara->stPriPdpInfo.stPdpAddr.aucIpv4Addr,
               g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr,
               TAF_IPV4_ADDR_LEN);

    /*XID*/
    pPdpPriPara->stPriPdpInfo.enPdpDcomp  = g_TafCidTab[ucCid].CidTab.enPdpDcomp;
    pPdpPriPara->stPriPdpInfo.enPdpHcomp  = g_TafCidTab[ucCid].CidTab.enPdpHcomp;

    pPdpPriPara->stPriPdpInfo.enIpv4AddrAlloc  = g_TafCidTab[ucCid].CidTab.enIpv4AddrAlloc;
    pPdpPriPara->stPriPdpInfo.enEmergencyInd   = g_TafCidTab[ucCid].CidTab.enEmergencyInd;

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    pPdpPriPara->stPriPdpInfo.enImCnSignalFlg  = g_TafCidTab[ucCid].CidTab.enImCnSignalFlg;
    pPdpPriPara->stPriPdpInfo.enPcscfDiscovery = g_TafCidTab[ucCid].CidTab.enPcscfDiscovery;
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueSec();
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

*****************************************************************************/
VOS_VOID Aps_QueSec(
    VOS_UINT8                           ucCid,
    TAF_PDP_SEC_CONTEXT_STRU           *pPdpSecPara,
    VOS_UINT32                         *pulErrorCode
)
{
    /*初始化*/
    *pulErrorCode                       = TAF_PARA_OK;

    if ( TAF_FREE == g_TafCidTab[ucCid].ucUsed)
    {
       *pulErrorCode                    = TAF_PARA_SEC_PDP_CONTEXT_NOT_DEFINED;
        return;
    }

    if ( TAF_USED == g_TafCidTab[ucCid].ucPriCidFlag)
    {   /*此Cid定义成从属PDP context*/

        pPdpSecPara->ucCid             = ucCid;
        pPdpSecPara->ucLinkdCid        = g_TafCidTab[ucCid].ucPriCid;
        pPdpSecPara->enPdpDcomp        = g_TafCidTab[ucCid].CidTab.enPdpDcomp;
        pPdpSecPara->enPdpHcomp        = g_TafCidTab[ucCid].CidTab.enPdpHcomp;
    }
    else
    {   /*此Cid不是从属PDP Context*/
       *pulErrorCode                    = TAF_PARA_SEC_PDP_CONTEXT_NOT_DEFINED;
    }

    return;
}


/*****************************************************************************
 Prototype      : Aps_QueState
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2012年06月25日
    作    者   : f62575
    修改内容   : DTS2012062802463, CGACT查询命令仅输出CGDCONT配置过的INDEX的拨号状态；

  3.日    期   : 2012年06月25日
    作    者   : z60575
    修改内容   : DTS2012120801696, 网测激活的CID需要能查询到

  4.日    期   : 2015年3月2日
    作    者   : A00165503
    修改内容   : DTS2015021101062: PDP修改过程中查询PDP状态异常
*****************************************************************************/
VOS_VOID Aps_QueState(
    VOS_UINT8                           ucCid,
    TAF_CID_STATE_STRU                 *pPsState,
    VOS_UINT32                         *pulErrorCode
)
{
    VOS_UINT8                   ucTmpPdpId;
    VOS_UINT32                  ucState;
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enCdataPsState;

    /*初始化*/
    *pulErrorCode               = TAF_PARA_OK;

    pPsState->ucCid             = ucCid;
    pPsState->ucState           = TAF_PDP_INACTIVE;

    if ((VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(ucCid))
     && (ucCid >= APS_PDP_MIN_CID)
     && (ucCid <= APS_PDP_MAX_CID))
    {
        *pulErrorCode               = TAF_PARA_UNSPECIFIED_ERROR;
        return;
    }

    for ( ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++)
    {
        ucState = TAF_APS_GetPdpIdMainFsmState(ucTmpPdpId);

        enCdataPsState = TAF_APS_GetPdpEntCdataPsState(ucTmpPdpId);

        /* X模下判断当前PDP是否激活需要判断主状态和CDATA的PS状态 */
        if ( (VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucTmpPdpId, ucCid))
          && ( (TAF_APS_STA_ACTIVE == ucState)
            || (TAF_APS_STA_MS_MODIFYING == ucState)
            || (TAF_APS_STA_MS_DEACTIVATING == ucState)
            || (TAF_APS_STA_CDATA_DISCING   == ucState)
            || (TAF_APS_CDATA_PS_STATE_ACTIVE == enCdataPsState) ) )
        {
            pPsState->ucState  = TAF_PDP_ACTIVE;
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Aps_QueRealIpAddr
 功能描述  : 查询CID对应的PDP实体的IP地址
 输入参数  : VOS_UINT8                           ucCid
             TAF_PDP_ADDR_QUERY_INFO_STRU    *paucIpAddr
             VOS_UINT8                          *pucErrorCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年
    作    者   : ---
    修改内容   : 新生成函数

  2.日    期   : 2011年6月3日
    作    者   : A00165503
    修改内容   : 增加IPV6地址的处理


  3.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  4. 日    期   : 2010年12月27日
     作    者   : h44270
     修改内容   : Modified by PS Project, 查询状态的函数修改，删除middle pdp id的概念

*****************************************************************************/
VOS_VOID Aps_QueRealIpAddr(
    VOS_UINT8                           ucCid,
    TAF_PDP_ADDR_QUERY_INFO_STRU       *paucIpAddr,
    VOS_UINT32                         *pulErrorCode
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
    TAF_APS_STA_ENUM_UINT32             enState;
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enCdataPsState;

    /* 初始化 */
    *pulErrorCode                       = TAF_PARA_OK;
    paucIpAddr->ucCid                   = ucCid;

    PS_MEM_SET(&paucIpAddr->stPdpAddr, 0x00, sizeof(TAF_PDP_ADDR_STRU));

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
        enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

        enCdataPsState = TAF_APS_GetPdpEntCdataPsState(ucPdpId);

        /* 此查询需要在AT上报给用户激活成功后，PPP协商和IPv6地址协商期间查询的地址不准确 */
        if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
         && ((TAF_APS_STA_ACTIVE          == enState)
          || (TAF_APS_CDATA_PS_STATE_ACTIVE == enCdataPsState)))
        {
            if (APS_ADDR_PPP == pstPdpEntity->PdpAddr.ucPdpTypeNum)
            {
                /* PPP类型 */
                *pulErrorCode   = TAF_PARA_UNSPECIFIED_ERROR;
            }
#if (FEATURE_ON == FEATURE_IPV6)
            else if (MN_APS_ADDR_IPV6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
            {
                /* IPV6类型 */
                paucIpAddr->stPdpAddr.enPdpType = TAF_PDP_IPV6;
                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv6Addr,
                           pstPdpEntity->PdpAddr.aucIpV6Addr,
                           TAF_IPV6_ADDR_LEN);
            }
            else if (MN_APS_ADDR_IPV4V6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
            {
                /* IPV4V6类型 */
                paucIpAddr->stPdpAddr.enPdpType = TAF_PDP_IPV4V6;

                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv4Addr,
                           pstPdpEntity->PdpAddr.aucIpAddr,
                           TAF_IPV4_ADDR_LEN);

                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv6Addr,
                           pstPdpEntity->PdpAddr.aucIpV6Addr,
                           TAF_IPV6_ADDR_LEN);
            }
#endif
            else
            {
                /*IP类型*/
                paucIpAddr->stPdpAddr.enPdpType = TAF_PDP_IPV4;
                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv4Addr,
                           pstPdpEntity->PdpAddr.aucIpAddr,
                           TAF_IPV4_ADDR_LEN);
            }

            break;
        }
    }

    /* 如果没有找到对应的PDP */
    if (ucPdpId >= TAF_APS_MAX_PDPID)
    {
        *pulErrorCode = TAF_PARA_UNSPECIFIED_ERROR;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueQosNeg
 Description    : 查询PDP协商后实际使用的QOS
 Input          : ucCid
 Output         : pQosNeg
                  pucErrorCode
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2006-11-08
    Author      : h41410
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体
  3. 日    期   : 2010年12月27日
     作    者   : h44270
     修改内容   : Modified by PS Project, 查询状态的函数修改，删除middle pdp id的概念

*****************************************************************************/
VOS_VOID Aps_QueQosNeg(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pQosNeg,
    VOS_UINT32                         *pulErrorCode
)
{
    VOS_UINT8                           ucTmpPdpId;

    APS_NORM_LOG("Into Aps_QueQosNeg");

    /*初始化*/
    *pulErrorCode                       = TAF_PARA_OK;

    for ( ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++)
    {
        if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucTmpPdpId, ucCid))
         && (VOS_TRUE == g_PdpEntity[ucTmpPdpId].PdpNsapiFlag))
        {   /*如果在状态机中找到了该CID*/

            Aps_3GQos2AppQos(       &(g_PdpEntity[ucTmpPdpId].PdpQos),
                                    &(pQosNeg->stQosInfo));
            pQosNeg->ucCid          = ucCid;
            break;
        }
    }

    /*如果没有找到对应的PDP*/
    if ( ucTmpPdpId >= TAF_APS_MAX_PDPID)
    {
        *pulErrorCode = TAF_PARA_UNSPECIFIED_ERROR;
        APS_NORM_LOG("Aps_QueQosNeg: This CID is not ACTIVE.");
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueDns
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

  3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，结构变更

*****************************************************************************/
VOS_VOID Aps_QueDns(
    VOS_UINT8                           ucCid,
    TAF_DNS_QUERY_INFO_STRU            *paucDns,
    VOS_UINT32                         *pulErrorCode
)
{
    TAF_PDP_DNS_STRU                   *pCidDns;

    /*初始化*/
    *pulErrorCode                       = TAF_PARA_OK;

    paucDns->ucCid                      = ucCid;
    paucDns->stDnsInfo.bitOpSpare       = VOS_FALSE;


    if ( TAF_FREE == g_TafCidTab[ucCid].ucDnsFlag)
    {   /*ucDnsFlag未定义*/
       *pulErrorCode                    = TAF_PARA_UNSPECIFIED_ERROR;
        return;
    }

    /*指针赋值，以使代码的简洁*/
    pCidDns                             = &g_TafCidTab[ucCid].DnsTab;

    /*处理PriDns字符串*/
    if (pCidDns->bitOpPrimDnsAddr)
    {
        paucDns->stDnsInfo.bitOpPrimDnsAddr = VOS_TRUE;
        PS_MEM_CPY(paucDns->stDnsInfo.aucPrimDnsAddr,
                   pCidDns->aucPrimDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        paucDns->stDnsInfo.bitOpPrimDnsAddr = VOS_FALSE;
    }

    /*处理SecDns字符串*/
    if (pCidDns->bitOpSecDnsAddr)
    {
        paucDns->stDnsInfo.bitOpSecDnsAddr = VOS_TRUE;
        PS_MEM_CPY(paucDns->stDnsInfo.aucSecDnsAddr,
                   pCidDns->aucSecDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        paucDns->stDnsInfo.bitOpSecDnsAddr = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueAuthdata
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2009-09-07
    Author      : L47619
    Modification: Created function

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改入参结构体

*****************************************************************************/
VOS_VOID Aps_QueAuthdata(
    VOS_UINT8                           ucCid,
    TAF_AUTHDATA_QUERY_INFO_STRU       *pAuthDataPara,
    VOS_UINT32                         *pulErrorCode
)
{
    /*初始化*/
    *pulErrorCode                       = TAF_PARA_OK;

    /*该AUTHDATA没有定义*/
    if (TAF_FREE == g_ApsNdisAuthdataTab[ucCid].ucUsed)
    {
       *pulErrorCode                    = TAF_PARA_NDIS_AUTHDATA_NOT_DEFINED;
        return;
    }

    pAuthDataPara->ucCid                        = ucCid;

    /*AUTHTYPE*/
    pAuthDataPara->stAuthDataInfo.enAuthType    = g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType;

    /*PLMN*/
    if( 0 != VOS_StrLen((VOS_CHAR *)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn))
    {
        PS_MEM_CPY(pAuthDataPara->stAuthDataInfo.aucPlmn,
                   g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPlmn));
    }
    else
    {
        PS_MEM_SET(pAuthDataPara->stAuthDataInfo.aucPlmn,
                   0,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPlmn));
    }

    /*PASSWORD*/
    if ( 0 != VOS_StrLen((VOS_CHAR *)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword))
    {
        PS_MEM_CPY(pAuthDataPara->stAuthDataInfo.aucPassword,
                   g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPassword));
    }
    else
    {
        PS_MEM_SET(pAuthDataPara->stAuthDataInfo.aucPassword,
                   0,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPassword));
    }

    /*USERNAME*/
    if ( 0 != VOS_StrLen((VOS_CHAR *)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername))
    {
        PS_MEM_CPY(pAuthDataPara->stAuthDataInfo.aucUsername,
                   g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucUsername));
    }
    else
    {
        PS_MEM_SET(pAuthDataPara->stAuthDataInfo.aucUsername,
                   0,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucUsername));
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_NvimAct()
 Description    : 对NVIM的操作，包括读、定义、修改。所有对参数的操作都会涉及到
                  对NVIM的操作。对NVIM操作的直接原因是全局变量表的修改。因此参
                  数操作接口函数完成对全局变量表的操作后，就会调用此函数来实现
                  对NVIM的操作。
                  操作成功,则更新g_TafCidTab中的index号码
 Input          : ucCid
 Output         : NO
 Return Value   : TAF_APS_SUCC,
                  TAF_APS_FAIL
 Data Access    : g_TmpPdpTab,
                  g_TafCidTab[pPara->ucCid]
 Data Update    :
 Calls          : NV_Write
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年12月24日
    作    者   : o00132663
    修改内容   : PS融合项目，PDPTBL局部变量太大，改为动态申请内存

  3.日    期   : 2012年3月6日
    作    者   : z40661/anhuiqing
    修改内容   : NVIM失败后继续向下执行，DTS2012030203625

  4.日    期   : 2014年3月3日
    作    者   : A00165503
    修改内容   : DTS2014030404070: APS本地结构适配NV结构
*****************************************************************************/
VOS_UINT32 Aps_NvimAct(VOS_UINT8 ucCid)
{
    TAF_PDP_TABLE_STRU                 *pstTmpLocalPdpTbl;
    TAF_NV_PDP_TABLE_STRU              *pstTmpNvPdpTbl;
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTbl;
    VOS_UINT16                          usNvId;
    APS_NVIM_ACT_TYPE                   NvimActType;

    /* CID大于最大NV个数的操作, 直接返回成功 */
    if (ucCid > TAF_MAX_CID_NV)
    {
        return TAF_APS_SUCC;
    }

    usNvId      = en_NV_Item_Taf_PdpPara_0 + ucCid;
    NvimActType = Aps_JudegNvimActType(ucCid);

    /* 申请内存 */
    pstTmpLocalPdpTbl = (TAF_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstTmpLocalPdpTbl)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_NvimAct: Alloc pstTmpLocalPdpTbl fail.");
        return  TAF_APS_FAIL;
    }

    pstTmpNvPdpTbl = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstTmpNvPdpTbl)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTmpLocalPdpTbl);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_NvimAct: Alloc pstTmpNvPdpTbl fail.");
        return  TAF_APS_FAIL;
    }

    pstNvPdpTbl = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstNvPdpTbl)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTmpLocalPdpTbl);
        PS_MEM_FREE(WUEPS_PID_TAF, pstTmpNvPdpTbl);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_NvimAct: Alloc pstNvPdpTbl fail.");
        return  TAF_APS_FAIL;
    }

    PS_MEM_SET(pstTmpLocalPdpTbl, 0x00, sizeof(TAF_PDP_TABLE_STRU));
    PS_MEM_SET(pstTmpNvPdpTbl, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));
    PS_MEM_SET(pstNvPdpTbl, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));

    if (NV_OK != NV_Read(usNvId, pstNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)) )
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Read pstNvPdpTbl fail! <NvId>", (VOS_INT32)usNvId);
    }

    if (APS_NVIM_ADD == NvimActType)
    {
        /* 添加记录 */
        g_TafCidTab[ucCid].usNvFlag = VOS_TRUE;

        /* 参考Q实现，QOS不写入NV项 */
        PS_MEM_CPY(pstTmpLocalPdpTbl, &g_TafCidTab[ucCid], sizeof(TAF_PDP_TABLE_STRU));
        pstTmpLocalPdpTbl->ucQosTabFlag = VOS_FALSE;
        PS_MEM_SET(&pstTmpLocalPdpTbl->QosTab, 0, sizeof(TAF_UMTS_QOS_STRU));
        pstTmpLocalPdpTbl->QosTab.ucTrafficClass  = 4;
        pstTmpLocalPdpTbl->QosTab.ucDeliverOrder  = 2;
        pstTmpLocalPdpTbl->QosTab.ucDeliverErrSdu = 3;

        /* 转换本地结构->NV结构 */
        TAF_APS_ConvertLocalPdpTab2NvPdpTab(pstTmpLocalPdpTbl, pstTmpNvPdpTbl);

        /* 比较NV内容是否改变 */
        if (0 != PS_MEM_CMP(pstNvPdpTbl, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            if (NV_OK != NV_Write(usNvId, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
            {
                TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Write pstTmpNvPdpTbl(ADD) fail! <NvId>", (VOS_INT32)usNvId);
            }
        }
    }
    else if ( APS_NVIM_CHNG == NvimActType )
    {   /*修改记录*/

        /* 参考Q实现，QOS不写入NV项 */
        PS_MEM_CPY(pstTmpLocalPdpTbl, &g_TafCidTab[ucCid], sizeof(TAF_PDP_TABLE_STRU));
        pstTmpLocalPdpTbl->ucQosTabFlag = VOS_FALSE;
        PS_MEM_SET(&pstTmpLocalPdpTbl->QosTab, 0, sizeof(TAF_UMTS_QOS_STRU));
        pstTmpLocalPdpTbl->QosTab.ucTrafficClass  = 4;
        pstTmpLocalPdpTbl->QosTab.ucDeliverOrder  = 2;
        pstTmpLocalPdpTbl->QosTab.ucDeliverErrSdu = 3;

        /* 转换本地结构->NV结构 */
        TAF_APS_ConvertLocalPdpTab2NvPdpTab(pstTmpLocalPdpTbl, pstTmpNvPdpTbl);

        /* 比较NV内容是否改变 */
        if (0 != PS_MEM_CMP(pstNvPdpTbl, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            if (NV_OK != NV_Write(usNvId, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
            {
                TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Write pstTmpNvPdpTbl(CHG) fail! <NvId>", (VOS_INT32)usNvId);
            }
        }
    }
    else
    {
        /* 删除记录 */
        g_TafCidTab[ucCid].usNvFlag = VOS_FALSE;
        PS_MEM_SET(pstTmpNvPdpTbl, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));

        if (NV_OK != NV_Write(usNvId, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Write pstTmpNvPdpTbl(DEL) fail! <NvId>", (VOS_INT32)usNvId);
        }
    }

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstTmpLocalPdpTbl);
    PS_MEM_FREE(WUEPS_PID_TAF, pstTmpNvPdpTbl);
    PS_MEM_FREE(WUEPS_PID_TAF, pstNvPdpTbl);

    return  TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      :
 Description    : 根据g_TafCidTab[ucCid]和g_TmpPdpTab的参数的定义情况判断此次
                  操作是添加,修改还是删除.
 Input          :
 Output         :
 Return Value   : typedef VOS_UINT8   APS_NVIM_ACT_TYPE;
                  #define APS_NVIM_ADD                    0
                  #define APS_NVIM_CHNG                   1
                  #define APS_NVIM_DELETE                 2
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
APS_NVIM_ACT_TYPE   Aps_JudegNvimActType ( VOS_UINT8        ucCid   )
{
    /*ucCid由主调函数保证合法性*/
    if ( APS_NVIM_DELETE_ITEM(ucCid) )
    {
        return  APS_NVIM_DELETE;
    }
    else if ( APS_NVIM_UPDATE_ITEM )
    {   /*不是删除，才有可能是更新或添加*/
        return  APS_NVIM_CHNG;
    }
    else
    {
        return  APS_NVIM_ADD;
    }
}

/*****************************************************************************
 Prototype      : Aps_SetPsAnsMode
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_PsAnsMode
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年1月27日
    作    者   : h44270
    修改内容   : PS融合项目，删除冗余代码和全局变量
*****************************************************************************/
VOS_VOID Aps_SetPsAnsMode(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_ANSWER_MODE_ENUM_UINT8      enAnsMode,
    VOS_UINT32                         *pulErrorCode
)
{
    VOS_UINT32                          ulNvimRet;
    TAF_PS_ANSWER_MODE_STRU             stTmpPsAnsMode;


    /*将对应的项暂时保存到临时变量g_TmpPsAnsMode中*/
    stTmpPsAnsMode                      = g_PsAnsMode;


    /*定义或者修改PDP_PRI参数*/
    g_PsAnsMode.enAnsMode               = enAnsMode;
    g_PsAnsMode.enAnsType               = TAF_PDP_ANSWER_TYPE_ACCEPT;
    g_PsAnsMode.usClientId              = ClientId;

    /*修改应答模式*/
    ulNvimRet   = NV_Write(           en_NV_Item_PS_TelePara,
                                       &g_PsAnsMode,
                                       sizeof(TAF_PS_ANSWER_MODE_STRU));
    if ( NV_OK == ulNvimRet )
    {
        *pulErrorCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*操作NVIM失败，恢复原值*/
        g_PsAnsMode                    = stTmpPsAnsMode;
        *pulErrorCode = TAF_PARA_WRITE_NVIM_ERROR;
        return;
    }
}

/*****************************************************************************
 函 数 名  : MN_APS_GetUtmsQosInfo
 功能描述  :
 输入参数  : VOS_UINT8                           ucCid
             TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
             VOS_UINT32                         *pulErrCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_GetUtmsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
)
{
    if ( VOS_FALSE == g_TafCidTab[ucCid].ucQosTabFlag )
    {
        /* Qos未定义 */
        *pulErrCode = TAF_PARA_QOS_NOT_DEFINED;
        return;
    }

    pstUmtsQosQueryInfo->ucCid      = ucCid;
    pstUmtsQosQueryInfo->stQosInfo  = g_TafCidTab[ucCid].QosTab;

    *pulErrCode = TAF_PARA_OK;

    return;
}

/*****************************************************************************
 函 数 名  : MN_APS_GetUtmsQosMinInfo
 功能描述  :
 输入参数  : VOS_UINT8                           ucCid
             TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
             VOS_UINT32                         *pulErrCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_GetUtmsQosMinInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
)
{
    if ( VOS_FALSE == g_TafCidTab[ucCid].ucMinQosFlag )
    {
        /* Qos未定义 */
        *pulErrCode = TAF_PARA_QOS_NOT_DEFINED;
        return;
    }

    pstUmtsQosQueryInfo->ucCid      = ucCid;
    pstUmtsQosQueryInfo->stQosInfo  = g_TafCidTab[ucCid].MinQosTab;

    *pulErrCode = TAF_PARA_OK;

    return;
}




/*****************************************************************************
 函 数 名  : TAF_APS_QueryPfInTft
 功能描述  : 查询TFT参数, 并从中获取PfId对应的索引
 输入参数  : VOS_UINT8                  ucCid,
             VOS_UINT8                  ucPacketFilterId,
 输出参数  : VOS_UINT8                 *pucPfIndex
 返 回 值  : VOS_TRUE                   - 索引查询成功
             VOS_FALSE                  - 没有查询到PfId对应的索引
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_QueryPfIdInTft(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPacketFilterId,
    VOS_UINT8                          *pucPfIndex
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucPfNum;

    /* 参数初始化 */
    *pucPfIndex      = VOS_NULL;
    ucIndex         = VOS_NULL;
    ucPfNum         = g_TafCidTab[ucCid].ucPfNum;

    /* 循环查找索引值 */
    for (ucIndex = 0; ucIndex < ucPfNum; ucIndex++)
    {
        if (ucPacketFilterId == g_TafCidTab[ucCid].astPfTab[ucIndex].ucPacketFilterId)
        {
            *pucPfIndex = ucIndex;
            return VOS_TRUE;
        }
    }

    /* 未找到返回失败 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_IsSetTftInfoValid
 功能描述  : 检查TFT参数本身的有效性
 输入参数  : TAF_TFT_EXT_STRU          *pstTftInfo
 输出参数  : 无
 返 回 值  : VOS_TRUE       - TFT参数有效
             VOS_FALSE      - TFT参数无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_IsSetTftInfoValid(
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    /* 如果是修改TFT参数, 则PfId, 优先级都是必须的 */
    if ( (VOS_TRUE == pstTftInfo->ucDefined)
      && (VOS_TRUE == pstTftInfo->bitOpPktFilterId)
      && (VOS_TRUE == pstTftInfo->bitOpPrecedence) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_CheckTftInfoValid
 功能描述  : 检查TFT参数的有效性及可设置性
 输入参数  : TAF_TFT_EXT_STRU          *pstTftInfo
 输出参数  : VOS_UINT8                 *pucPfIndex      -返回可用的PF索引值
 返 回 值  : VOS_TRUE       - TFT参数有效
             VOS_FALSE      - TFT参数不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_CheckTftInfoValid(
    TAF_TFT_EXT_STRU                   *pstTftInfo,
    VOS_UINT8                          *pucPfIndex
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucPfPrecedence;
    VOS_UINT8                           ucPfId;

    /* 参数初始化 */
    ulIndex         = VOS_NULL;
    ucPfPrecedence  = VOS_NULL;
    ucPfId          = VOS_NULL;

    /* 检查TFT参数本身的有效性 */
    /* 此处还需要参考北京代码实现 */
    if (VOS_FALSE == TAF_APS_IsSetTftInfoValid(pstTftInfo))
    {
        TAF_PS_WARN_LOG("TAF_APS_CheckTftInfoValid: TFT info error!");
        return VOS_FALSE;
    }

    /* 同一个Cid下,优先级不能相同*/
    for (ulIndex = 0; ulIndex < g_TafCidTab[pstTftInfo->ucCid].ucPfNum; ulIndex++)
    {
        ucPfPrecedence  = g_TafCidTab[pstTftInfo->ucCid].astPfTab[ulIndex].ucPrecedence;
        ucPfId          = g_TafCidTab[pstTftInfo->ucCid].astPfTab[ulIndex].ucPacketFilterId;

        /* 允许对同一个Packetfilter设置相同的优先级*/
        if ((ucPfPrecedence == pstTftInfo->ucPrecedence)
         && (ucPfId != pstTftInfo->ucPacketFilterId))
        {
            TAF_PS_WARN_LOG("TAF_APS_CheckTftInfoValid: Pf precedence error!");
            return VOS_FALSE;
        }
    }

    /* 查找指定PF ID */
    if (VOS_FALSE == TAF_APS_QueryPfIdInTft(pstTftInfo->ucCid,
                                            pstTftInfo->ucPacketFilterId,
                                            pucPfIndex))
    {
        /* 若指定PF不存在，或者PF数已满，则返回设置错误 */
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        if (g_TafCidTab[pstTftInfo->ucCid].ucPfNum >= TAF_MAX_SDF_PF_NUM)
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
        {
            TAF_PS_WARN_LOG("TAF_APS_CheckTftInfoValid: Pf number is full!");
            return VOS_FALSE;
        }
        else
        {
            /*lint -e961*/
            *pucPfIndex = g_TafCidTab[pstTftInfo->ucCid].ucPfNum++;
            /*lint +e961*/
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FillTftInfo
 功能描述  : 将设置参数填充进PDP表全局变量
 输入参数  : VOS_UINT8                           ucCid
             VOS_UINT8                           ucPfIndex
             TAF_TFT_EXT_STRU                   *pstTftInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : l00198894
    修改内容   : 新生成函数

  2.日    期   : 2015年9月28日
    作    者   : W00316404
    修改内容   : R11 TFT 协议升级

*****************************************************************************/
VOS_VOID TAF_APS_FillTftInfo(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPfIndex,
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    /* pstTftInfo, ucCid, ucPfIndex的有效性由主调函数保证 */
    if ( VOS_TRUE == pstTftInfo->bitOpPktFilterId )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucPacketFilterId = pstTftInfo->ucPacketFilterId;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpPrecedence )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucPrecedence      = pstTftInfo->ucPrecedence;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpSrcPortRange )
    {
        if(pstTftInfo->usLowSourcePort == pstTftInfo->usHighSourcePort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleRemotePort = VOS_TRUE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRemotePortRange  = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usSingleRmtPort       = pstTftInfo->usLowSourcePort;
        }
        else if(pstTftInfo->usLowSourcePort < pstTftInfo->usHighSourcePort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleRemotePort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRemotePortRange  = VOS_TRUE;

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usRmtPortHighLimit    = pstTftInfo->usHighSourcePort;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usRmtPortLowLimit     = pstTftInfo->usLowSourcePort;
        }
        else
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleRemotePort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRemotePortRange  = VOS_FALSE;
        }

    }

    if ( VOS_TRUE == pstTftInfo->bitOpDestPortRange )
    {
        if(pstTftInfo->usLowDestPort == pstTftInfo->usHighDestPort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleLocalPort = VOS_TRUE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalPortRange  = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usSingleLcPort       = pstTftInfo->usLowDestPort;
        }
        else if(pstTftInfo->usLowDestPort < pstTftInfo->usHighDestPort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleLocalPort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalPortRange = VOS_TRUE;

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usLcPortLowLimit = pstTftInfo->usLowDestPort;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usLcPortHighLimit = pstTftInfo->usHighDestPort;
        }
        else
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleLocalPort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalPortRange  = VOS_FALSE;
        }

    }

    if ( VOS_TRUE == pstTftInfo->bitOpSrcIp )
    {
        if (TAF_PDP_IPV4 == pstTftInfo->stSourceIpaddr.enPdpType )
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv4AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Address,
                       pstTftInfo->stSourceIpaddr.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Mask,
                       pstTftInfo->stSourceIpMask.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv6AddrAndMask = VOS_FALSE;
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Address,
                       0x00,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Mask,
                       0x00,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        }
        else if (TAF_PDP_IPV6 == pstTftInfo->stSourceIpaddr.enPdpType )
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv6AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Address,
                       pstTftInfo->stSourceIpaddr.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Mask,
                       pstTftInfo->stSourceIpMask.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv4AddrAndMask = VOS_FALSE;
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Address,
                       0x00,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Mask,
                       0x00,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        }
        else
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv4AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Address,
                       pstTftInfo->stSourceIpaddr.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Mask,
                       pstTftInfo->stSourceIpMask.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv6AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Address,
                       pstTftInfo->stSourceIpaddr.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Mask,
                       pstTftInfo->stSourceIpMask.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        }
    }

    if ( VOS_TRUE == pstTftInfo->bitOpTosMask )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpTypeOfService   = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucTypeOfService      = pstTftInfo->ucTypeOfService;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucTypeOfServiceMask  = pstTftInfo->ucTypeOfServiceMask;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpProtocolId )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpProtocolId    = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucProtocolId       = pstTftInfo->ucProtocolId;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpSpi )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSecuParaIndex = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ulSecuParaIndex    = pstTftInfo->ulSecuParaIndex;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpNwPktFilterId )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucNwPacketFilterId = pstTftInfo->ucNwPktFilterId;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpFlowLable )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpFlowLabelType = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ulFlowLabelType    = pstTftInfo->ulFlowLable;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpDirection)
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].enDirection = pstTftInfo->ucDirection;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpLocalIpv4AddrAndMask )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalIpv4AddrAndMask = VOS_TRUE;
        PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucLocalIpv4Addr,
                   pstTftInfo->aucLocalIpv4Addr,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucLocalIpv4Mask,
                   pstTftInfo->aucLocalIpv4Mask,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
    }

    if ( VOS_TRUE == pstTftInfo->bitOpLocalIpv6AddrAndMask )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalIpv6AddrAndMask = VOS_TRUE;
        PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucLocalIpv6Addr,
                   pstTftInfo->aucLocalIpv6Addr,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucLocalIpv6Prefix         = pstTftInfo->ucLocalIpv6Prefix;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetTftInfo
 功能描述  : 定义、修改、删除PDP Context中的TFT参数
 输入参数  : TAF_TFT_EXT_STRU                   *pstTftInfo
             VOS_UINT32                         *pulErrCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2012年04月23日
    作    者   : z60575
    修改内容   : DTS2012042304705修改，删除CID的TFT信息时需要写NV项
*****************************************************************************/
VOS_VOID TAF_APS_SetTftInfo(
    TAF_TFT_EXT_STRU                   *pstTftInfo,
    VOS_UINT32                         *pulErrCode
)
{
    /* 设置, 修改TFT参数NV项及全局变量 */
    VOS_UINT32                          ulReturn;
    VOS_UINT8                           ucPfIndex;

    /* 参数初始化 */
    ulReturn                            = TAF_APS_SUCC;
    ucPfIndex                           = VOS_NULL;

    /* 检查入参(cid)的有效性 */
    if ( ( VOS_NULL_PTR == pstTftInfo )
       || (!(TAF_PS_CID_VALID(pstTftInfo->ucCid))))
    {
        TAF_PS_WARN_LOG("TAF_APS_SetTftInfo input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /* 将对应的项暂时保存到临时变量g_TmpPdpTab 中 */
    g_TmpPdpTab = g_TafCidTab[pstTftInfo->ucCid];

    /*根据参数设置类型，进行消息的设置与删除操作*/
    if (VOS_FALSE == pstTftInfo->ucDefined)
    {
        /* CID状态激活中, 则禁止做删除操作 */
        if (TAF_TRUE == Taf_CheckActCid(pstTftInfo->ucCid))
        {
            TAF_PS_WARN_LOG("TAF_APS_SetTftInfo: Delete is not allowed when cid is operating!");
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /* 根据ucCid，删除本地相应结构中的TFT信息 */
        g_TafCidTab[pstTftInfo->ucCid].ucPfTabFlag  = VOS_FALSE;
        g_TafCidTab[pstTftInfo->ucCid].ucPfNum      = VOS_NULL;

        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        PS_MEM_SET((VOS_UINT32 *)(g_TafCidTab[pstTftInfo->ucCid].astPfTab),
                   VOS_NULL,
                   sizeof(TAF_PDP_PF_STRU) * TAF_MAX_SDF_PF_NUM);
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {
        /* 定义或者修改TFT参数 */
        g_TafCidTab[pstTftInfo->ucCid].ucPfTabFlag = VOS_TRUE;

        /* 检查设置的TFT参数 */
        if (VOS_FALSE == TAF_APS_CheckTftInfoValid(pstTftInfo, &ucPfIndex))
        {
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /* 将设置参数填充进PDP表全局变量 */
        TAF_APS_FillTftInfo(pstTftInfo->ucCid, ucPfIndex, pstTftInfo);

        /* 此处缺少对全局变量的合法性检查 */
    }

    /* 写入NV项 */
    ulReturn = Aps_NvimAct( pstTftInfo->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {
        /* 操作成功 */
        *pulErrCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*操作NVIM失败，恢复原值*/
        g_TafCidTab[pstTftInfo->ucCid] = g_TmpPdpTab;
        TAF_PS_WARN_LOG("NVIM ACT ERR!");
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FillTftQryParam
 功能描述  : 查询PDP Context中的TFT参数
 输入参数  : VOS_UINT8                           ucCid
 输出参数  : TAF_TFT_QUREY_INFO_STRU            *pPdpTftPara
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : l00198894
    修改内容   : 新生成函数

  2.日    期   : 2015年9月28日
    作    者   : W00316404
    修改内容   : R11 TFT 协议升级

*****************************************************************************/
VOS_VOID TAF_APS_FillTftQryParam(
    VOS_UINT8                           ucCid,
    TAF_TFT_QUREY_INFO_STRU            *pPdpTftPara
)
{
    VOS_UINT8                           ucIndex;

    /*初始化*/
    ucIndex                             = 0;

    /* 填充查询的TFT参数 */
    pPdpTftPara->ucCid                  = ucCid;
    pPdpTftPara->ucPfNum                = g_TafCidTab[ucCid].ucPfNum;

    /* 循环填充所有的TFT参数 */
    for (ucIndex = 0; ucIndex < pPdpTftPara->ucPfNum; ucIndex++)
    {
        pPdpTftPara->astPfInfo[ucIndex].bitOpRmtIpv4AddrAndMask    = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpRmtIpv4AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpRmtIpv6AddrAndMask    = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpRmtIpv6AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpProtocolId            = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpProtocolId;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSingleLocalPort       = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSingleLocalPort;
        pPdpTftPara->astPfInfo[ucIndex].bitOpLocalPortRange        = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpLocalPortRange;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSingleRemotePort      = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSingleRemotePort;
        pPdpTftPara->astPfInfo[ucIndex].bitOpRemotePortRange       = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpRemotePortRange;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSecuParaIndex         = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSecuParaIndex;
        pPdpTftPara->astPfInfo[ucIndex].bitOpTypeOfService         = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpTypeOfService;
        pPdpTftPara->astPfInfo[ucIndex].bitOpFlowLabelType         = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpFlowLabelType;
        pPdpTftPara->astPfInfo[ucIndex].bitOpLocalIpv4AddrAndMask  = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpLocalIpv4AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpLocalIpv6AddrAndMask  = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpLocalIpv6AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSpare                 = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSpare;
        pPdpTftPara->astPfInfo[ucIndex].ucPacketFilterId           = g_TafCidTab[ucCid].astPfTab[ucIndex].ucPacketFilterId;
        pPdpTftPara->astPfInfo[ucIndex].ucNwPacketFilterId         = g_TafCidTab[ucCid].astPfTab[ucIndex].ucNwPacketFilterId;
        pPdpTftPara->astPfInfo[ucIndex].enDirection                = g_TafCidTab[ucCid].astPfTab[ucIndex].enDirection;
        pPdpTftPara->astPfInfo[ucIndex].ucPrecedence               = g_TafCidTab[ucCid].astPfTab[ucIndex].ucPrecedence;

        pPdpTftPara->astPfInfo[ucIndex].ulSecuParaIndex            = g_TafCidTab[ucCid].astPfTab[ucIndex].ulSecuParaIndex;
        pPdpTftPara->astPfInfo[ucIndex].usSingleLcPort             = g_TafCidTab[ucCid].astPfTab[ucIndex].usSingleLcPort;
        pPdpTftPara->astPfInfo[ucIndex].usLcPortHighLimit          = g_TafCidTab[ucCid].astPfTab[ucIndex].usLcPortHighLimit;
        pPdpTftPara->astPfInfo[ucIndex].usLcPortLowLimit           = g_TafCidTab[ucCid].astPfTab[ucIndex].usLcPortLowLimit;
        pPdpTftPara->astPfInfo[ucIndex].usSingleRmtPort            = g_TafCidTab[ucCid].astPfTab[ucIndex].usSingleRmtPort;
        pPdpTftPara->astPfInfo[ucIndex].usRmtPortHighLimit         = g_TafCidTab[ucCid].astPfTab[ucIndex].usRmtPortHighLimit;
        pPdpTftPara->astPfInfo[ucIndex].usRmtPortLowLimit          = g_TafCidTab[ucCid].astPfTab[ucIndex].usRmtPortLowLimit;
        pPdpTftPara->astPfInfo[ucIndex].ucProtocolId               = g_TafCidTab[ucCid].astPfTab[ucIndex].ucProtocolId;
        pPdpTftPara->astPfInfo[ucIndex].ucTypeOfService            = g_TafCidTab[ucCid].astPfTab[ucIndex].ucTypeOfService;
        pPdpTftPara->astPfInfo[ucIndex].ucTypeOfServiceMask        = g_TafCidTab[ucCid].astPfTab[ucIndex].ucTypeOfServiceMask;

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv4Address,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv4Address,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv4Mask,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv4Mask,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv6Address,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv6Address,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv6Mask,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv6Mask,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucLocalIpv4Addr,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucLocalIpv4Addr,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucLocalIpv4Mask,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucLocalIpv4Mask,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucLocalIpv6Addr,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucLocalIpv6Addr,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

        pPdpTftPara->astPfInfo[ucIndex].ucLocalIpv6Prefix          = g_TafCidTab[ucCid].astPfTab[ucIndex].ucLocalIpv6Prefix;

        pPdpTftPara->astPfInfo[ucIndex].ulFlowLabelType            = g_TafCidTab[ucCid].astPfTab[ucIndex].ulFlowLabelType;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_SetEpsQosInfo
 功能描述  : 设置, 修改, 删除EPS QOS参数NV项及全局变量
 输入参数  : TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
             VOS_UINT32                         *pulErrCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SetEpsQosInfo(
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
)
{
    /* 设置, 修改EPS QOS参数NV项及全局变量 */
    VOS_UINT32                          ulReturn;
    VOS_UINT32                          ulDelFlag;

    /* 参数初始化 */
    ulReturn                            = TAF_APS_SUCC;
    ulDelFlag                           = 0;

    if ( ( VOS_NULL_PTR == pstEpsQosInfo )
       || (!(TAF_PS_CID_VALID(pstEpsQosInfo->ucCid))))
    {
        TAF_PS_WARN_LOG("TAF_APS_SetEpsQosInfo input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /* 将对应的项暂时保存到临时变量g_TmpPdpTab 中 */
    g_TmpPdpTab = g_TafCidTab[pstEpsQosInfo->ucCid];

    /* 定义或者修改EPS_QOS参数 */
    g_TafCidTab[pstEpsQosInfo->ucCid].ucEpsQosInfoFlg           = VOS_TRUE;

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpQCI )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ucQCI    = pstEpsQosInfo->ucQCI;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpDLGBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulDLGBR  = pstEpsQosInfo->ulDLGBR;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpULGBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulULGBR  = pstEpsQosInfo->ulULGBR;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpDLMBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulDLMBR  = pstEpsQosInfo->ulDLMBR;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpULMBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulULMBR  = pstEpsQosInfo->ulULMBR;
        ulDelFlag++;
    }

    /* 参数只有cid, 删除该cid对应的EQOS信息 */
    if ( 0 == ulDelFlag )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].ucEpsQosInfoFlg       = VOS_FALSE;
        PS_MEM_SET(&(g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo),
                    0x00,
                    sizeof(TAF_EPS_QOS_STRU));
    }

    ulReturn = Aps_NvimAct( pstEpsQosInfo->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {
        /* 操作成功 */
        *pulErrCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*操作NVIM失败，恢复原值*/
        g_TafCidTab[pstEpsQosInfo->ucCid] = g_TmpPdpTab;
        TAF_PS_WARN_LOG("NVIM ACT ERR!");
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_QueEpsQosInfo
 功能描述  : 查询EPS QOS参数
 输入参数  : VOS_UINT8                           ucCid
             TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
             VOS_UINT32                         *pulErrCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月27日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_QueEpsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
)
{
    /* 参数初始化 */
    *pulErrCode                         = TAF_PARA_OK;

    /* 该EQOS没有定义 */
    if (TAF_FREE == g_TafCidTab[ucCid].ucEpsQosInfoFlg)
    {
        *pulErrCode                     = TAF_PARA_EPS_QOS_NOT_DEFINED;
        return;
    }

    /* 填充查询的EPS QOS结果 */
    pstEpsQosInfo->ucCid                = ucCid;

    pstEpsQosInfo->bitOpQCI             = VOS_TRUE;
    pstEpsQosInfo->ucQCI                = g_TafCidTab[ucCid].stEpsQosInfo.ucQCI;
    pstEpsQosInfo->bitOpDLGBR           = VOS_TRUE;
    pstEpsQosInfo->ulDLGBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulDLGBR;
    pstEpsQosInfo->bitOpULGBR           = VOS_TRUE;
    pstEpsQosInfo->ulULGBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulULGBR;
    pstEpsQosInfo->bitOpDLMBR           = VOS_TRUE;
    pstEpsQosInfo->ulDLMBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulDLMBR;
    pstEpsQosInfo->bitOpULMBR           = VOS_TRUE;
    pstEpsQosInfo->ulULMBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulULMBR;

    return;
}

/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
/*****************************************************************************
 函 数 名  : Aps_DefPsPdprofmod
 功能描述  : 设置PDPROFMOD参数
 输入参数  :
             VOS_UINT8                                     ucCid
             VOS_UINT8                                     OpId
             TAF_PDP_PROFILE_EXT_STRU         *pPara
             VOS_UINT32                                 *pulErrCode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月15日
    作    者   : x00126983
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID    Aps_DefPsPdprofmod (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PROFILE_EXT_STRU           *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulTmpErrCode;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  stSetPdpCtxInfoReq;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU          stAuthDataReq;

    PS_MEM_SET(&stSetPdpCtxInfoReq, 0, sizeof(stSetPdpCtxInfoReq));
    PS_MEM_SET(&stAuthDataReq, 0, sizeof(stAuthDataReq));
    stSetPdpCtxInfoReq.stCtrl.usClientId = ClientId;
    stSetPdpCtxInfoReq.stCtrl.ucOpId     = OpId;
    ulTmpErrCode                         = 0;

    stSetPdpCtxInfoReq.stPdpContextInfo.bitOpPdpType = pPara->bitOpPdpType;
    stSetPdpCtxInfoReq.stPdpContextInfo.bitOpApn = pPara->bitOpApn;
    stSetPdpCtxInfoReq.stPdpContextInfo.bitOpSpare = pPara->bitOpSpare;

    stSetPdpCtxInfoReq.stPdpContextInfo.ucCid = pPara->ucCid;
    stSetPdpCtxInfoReq.stPdpContextInfo.ucDefined = pPara->ucDefined;

    stSetPdpCtxInfoReq.stPdpContextInfo.enPdpType = pPara->enPdpType;
    PS_MEM_CPY((VOS_UINT8*)(stSetPdpCtxInfoReq.stPdpContextInfo.aucApn),
               (VOS_UINT8*)(pPara->aucApn),
               (TAF_MAX_APN_LEN + 1));

    /* 设置Primary PDP上下文 */
    Aps_DefPsPdpContext(stSetPdpCtxInfoReq.stCtrl.usClientId,
                        stSetPdpCtxInfoReq.stCtrl.ucOpId,
                        &(stSetPdpCtxInfoReq.stPdpContextInfo),
                        &ulTmpErrCode);
    if (TAF_PARA_OK != ulTmpErrCode)
    {
        *pulErrCode = ulTmpErrCode;
        return;
    }

    stAuthDataReq.stCtrl.usClientId = ClientId;
    stAuthDataReq.stCtrl.ucOpId = OpId;

    stAuthDataReq.stAuthDataInfo.bitOpUserName = pPara->bitOpUsername;
    stAuthDataReq.stAuthDataInfo.bitOpPassWord = pPara->bitOpPassword;
    stAuthDataReq.stAuthDataInfo.bitOpAuthType = pPara->bitOpAuthType;
    stAuthDataReq.stAuthDataInfo.bitOpSpare    = pPara->bitOpSpare;

    stAuthDataReq.stAuthDataInfo.ucCid         = pPara->ucCid;
    stAuthDataReq.stAuthDataInfo.ucDefined     = pPara->ucDefined;

    stAuthDataReq.stAuthDataInfo.enAuthType    = pPara->ucAuthType;
    PS_MEM_CPY((VOS_UINT8*)(stAuthDataReq.stAuthDataInfo.aucPassWord),
               (VOS_UINT8*)(pPara->aucPassWord),
               (TAF_MAX_AUTHDATA_PASSWORD_LEN + 1));
    PS_MEM_CPY((VOS_UINT8*)(stAuthDataReq.stAuthDataInfo.aucUserName),
               (VOS_UINT8*)(pPara->aucUserName),
               (TAF_MAX_AUTHDATA_USERNAME_LEN + 1));

    /* 设置AUTHDATA参数(NDIS) */
    Aps_DefNdisAuthdata(stAuthDataReq.stCtrl.usClientId,
                        stAuthDataReq.stCtrl.ucOpId,
                        &(stAuthDataReq.stAuthDataInfo),
                        &ulTmpErrCode);

    *pulErrCode = ulTmpErrCode;
    return;
}
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

#endif

/*****************************************************************************
 函 数 名  : Aps_DeleteLinkedCidSecPdpContext
 功能描述  : 删除某个主Cid下面的所有二次PDP上下文
 输入参数  : VOS_UINT8                           ucCid

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月2日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Aps_DeleteLinkedCidSecPdpContext(
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          i;

    for (i = 1 ; i <= TAF_MAX_CID; i++)
    {
        if ((VOS_TRUE == g_TafCidTab[i].ucUsed )
         && (VOS_TRUE == g_TafCidTab[i].ucPriCidFlag))
        {
            if (ucCid == g_TafCidTab[i].ucPriCid)
            {
                g_TafCidTab[i].ucUsed        = VOS_FALSE;
                g_TafCidTab[i].ucPriCidFlag  = VOS_FALSE;
            }
        }
    }
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
