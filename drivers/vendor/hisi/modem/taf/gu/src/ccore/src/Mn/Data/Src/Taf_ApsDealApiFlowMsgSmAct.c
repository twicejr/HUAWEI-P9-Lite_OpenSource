/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Aps_DealApiFlowMsgSmAct.c
  Author       : 韩鲁峰
  Version      : V200R001
  Date         : 2005-0
  Description  :
  Function List:
        ---Aps_PdpActReq
        ---Aps_PdpActReqStateCheck
        ---Aps_PackSmActReqMsg
        ---Aps_ActReqFillState
        ---TAF_APS_SndPdpActivateRej

        ---Aps_PdpSecActReq
        ---Aps_SecActReqFillState
        ---Aps_PdpSecActReqParaCheck
        ---Aps_PdpSecActReqStateCheck
        ---Aps_PackSmSecActReqMsg

        ---Aps_PdpMdfReq
        ---Aps_PackSmMdfReqMsg
        ---TAF_APS_SndPdpModifyRej

        ---Aps_AppDeactReq
        ---Aps_PdpDeActReq
        ---Aps_PdpDeActOneReq
        ---Aps_PdpDeActReqParaCheck

        ---Aps_PdpAnsRej
        ---Aps_FindAllTearDownPdp
        ---Aps_CompAddr
        ---Aps_PackSmQos
        ---Aps_PackSmTft

        ---Aps_PackSmAddr
        ---Aps_PackSmApn
        ---Aps_TftValidOrNot
        ---Aps_QosValidOrNot
        ---Aps_FindPdpContext

        ---Aps_PackSmPco
        ---
  History      :
  1. Date:2005-0
     Author: ---
     Modification:Create
  2. 2006-02-23 modify by 韩鲁峰 FOR A32D02144
  3. 2006-03-03 MODIFY BY H41410 FOR A32D02345
  4. 2006-04-10 modify BY H41410 FOR A32D01902
  5. 2006-05-22 modify by h41410 for A32D03787
  6. 2006-07-03 modify by L47619 for A32D04540
  7. 2006-08-03 modify by L47619 for A32D05213
  8. 2006-08-03 modify by L47619 for A32D05212
************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "NasCommDef.h"
#include "MnComm.h"
#include "TafApsCtx.h"
#include "MnApsComm.h"
#include "TafApsSndSm.h"

#include "WasNvInterface.h"

#include "TafApsComFunc.h"
#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALAPIFLOWMSGSMACT_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : Aps_PdpActReq
 Description    : PDP激活
 Input          :
 Output         :
 Return Value   :
 Calls          : Aps_PdpActReqParaCheck()
 Called By      : Aps_PsCallOrig();
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : PS融合项目修改
*****************************************************************************/
VOS_UINT32  Aps_PdpActReq(
    APS_PDP_ACT_REQ_ST                 *pActReq
)
{
    SMREG_PDP_ACTIVATE_REQ_STRU         *pstPdpActReq;

    if ( VOS_NULL_PTR == pActReq)
    {
        APS_WARN_LOG("Aps_PdpActReq input null pointer !");
        return TAF_APS_FAIL;
    }

    APS_NORM_LOG("APS rcv APS_PDP_ACT_REQ_ST ");

    /* 构造消息并填充消息头 */
    pstPdpActReq = (SMREG_PDP_ACTIVATE_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_ACTIVATE_REQ);
    if (VOS_NULL_PTR == pstPdpActReq)
    {
        return TAF_APS_FAIL;
    }

    /*打包向SM发送的MSG;*/
    if ( TAF_APS_FAIL == Aps_PackSmActReqMsg (pActReq, pstPdpActReq))
    {
        APS_WARN_LOG("Aps PackSmActReq Msg ERR !");
        PS_FREE_MSG(WUEPS_PID_TAF, pstPdpActReq);
        return TAF_APS_FAIL;
    }

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstPdpActReq))
    {
        APS_WARN_LOG("Aps_PdpActReq Snd msg fail!");
        return TAF_APS_FAIL;
    }

    /*填充PDP状态机;*/
    Aps_ActReqFillState(pActReq);
    return TAF_APS_SUCC;
}

/*****************************************************************************
 函 数 名  : Aps_PackSmActReqMsg
 功能描述  : 打包向SM发送ACT_REQ的消息
 输入参数  : SMREG_PDP_ACTIVATE_REQ_STRU        *pActReq
             SMREG_PDP_ACTIVATE_REQ_STRU        *pStPdpActReq
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年xx月xx日
    作    者   : 韩鲁峰
    修改内容   : 新生成函数

  2.日    期   : 2010年05月14日
    作    者   : s62952
    修改内容   : 问题单号: AT2D19341

  3.日    期   : 2010年12月15日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010120605160，W单模下PDP激活后，修改为双模，
                 重选到G下数传无法恢复
  4.日    期   : 2012年01月05日
    作    者   : h44270
    修改内容   : 增加默认承载，当前发送到SM的CR变为从实体中的TI中来获取，不再
                 直接使用PDP ID
  5.日    期   : 2013年4月23日
    作    者   : L47619
    修改内容   : V9R1 IPv6&TAF/SM接口优化项目修改
*****************************************************************************/
VOS_UINT32 Aps_PackSmActReqMsg (
    APS_PDP_ACT_REQ_ST                 *pActReq,
    SMREG_PDP_ACTIVATE_REQ_STRU        *pStPdpActReq
)
{
    VOS_UINT32                          ulReturnValue;

    pStPdpActReq->bitOpAcsPointName = VOS_FALSE;
    pStPdpActReq->bitOpProtCfgOpt   = VOS_FALSE;
    pStPdpActReq->bitOpSapi         = VOS_FALSE;
    pStPdpActReq->bitOpSpare        = VOS_FALSE;

    /* 填写 ConnectId (CR)，当前CR等同于Pdp Id */
    pStPdpActReq->ucConnectId       = pActReq->ucPdpId;

    /*LLC SAPI*/
    pStPdpActReq->bitOpSapi         = VOS_TRUE;
    pStPdpActReq->ucSapi            = pActReq->ucSapi;

    /*QOS*/
    Aps_PackSmQos(  &(pActReq->ReqQos),
                    &(pStPdpActReq->stReqQos));

    /*ADDR*/
    ulReturnValue = Aps_PackSmAddr( &pActReq->ucPdpType,
                                    pActReq->aucIpAddr,
                                    &(pStPdpActReq->stReqPdpAddr));
    if (TAF_APS_FAIL == ulReturnValue)
    {
        APS_WARN_LOG("Aps_PackSmAddr err ");
        return  TAF_APS_FAIL;
    }

    /*APN*/
    if (0 == pActReq->aucApn[0])
    {
        /*如果APN长度为0，则不选APN*/
        pStPdpActReq->bitOpAcsPointName = VOS_FALSE;
    }
    else
    {
        pStPdpActReq->bitOpAcsPointName = VOS_TRUE;
        Aps_PackSmApn( pActReq->aucApn, &(pStPdpActReq->stAcsPointName));
    }

    if (APS_ADDR_PPP != pActReq->ucPdpType)
    {
        /*PCO*/
        pStPdpActReq->bitOpProtCfgOpt   = VOS_TRUE;
        if ( TAF_APS_FAIL == Aps_PackSmPco(pActReq, &pStPdpActReq->stProtCfgOpt))
        {
            APS_WARN_LOG("Aps_PackSmPco err ");
            return  TAF_APS_FAIL;
        }
    }

    return  TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      : Aps_SecActReqFillState
 Description    : 将输入的参数填入二次激活的PDP状态机中:QOS、TFT、SAPI;
                  将主激活PDP中的一些参数填入二次激活的PDP状态机中,包括PDPTYPE、ADDR、APN;
 Input          :
 Output         :
 Return Value   :
 Data Accessed  :
 Data Update    : g_PdpEntity[ucPdpId].
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
 2.日    期   : 2011年12月17日
   作    者   : s62952
   修改内容   : PS融合项目修改:删除状态处理,将这部分功能移到状态机中处理
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构替换
*****************************************************************************/
VOS_VOID    Aps_ActReqFillState(
    APS_PDP_ACT_REQ_ST                 *pActReq
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId                             = pActReq->ucPdpId;


    /*激活类型*/
    g_PdpEntity[ucPdpId].ActType        = APS_PDP_ACT_PRI;

    /*发起激活的方式*/
    g_PdpEntity[pActReq->ucPdpId].PdpProcTrackFlag  = VOS_TRUE;


    /*GPRS参数标识要置1*/
    g_PdpEntity[ucPdpId].PdpGprsParaFlag            = VOS_TRUE;

    /*QOS */
    g_PdpEntity[ucPdpId].PdpQosFlag                 = VOS_TRUE;
    PS_MEM_CPY(           &(g_PdpEntity[ucPdpId].PdpQos),
                          &(pActReq->ReqQos),
                          sizeof(APS_PDP_QOS_STRU));

    /*AUTH*/
    if (pActReq->OP_AUTH)
    {
        if ( TAF_PCO_NOT_AUTH != pActReq->PdpAuth.AuthType)
        {
            g_PdpEntity[ucPdpId].PdpAuthFlag        = VOS_TRUE;
            PS_MEM_CPY(   &g_PdpEntity[ucPdpId].AuthTab,
                          &pActReq->PdpAuth,
                          sizeof(TAF_PDP_PCO_AUTH_STRU));
        }
    }

    /*APN*/
    if (pActReq->OP_APN)
    {
        g_PdpEntity[ucPdpId].PdpApnFlag             = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpApn.ucLength        = pActReq->aucApn[0];
        if (pActReq->aucApn[0] > APS_MAX_LENGTH_OF_APN)
        {
            APS_WARN_LOG("pActReq->aucApn[0] > APS_MAX_LENGTH_OF_APN ");
            pActReq->aucApn[0] = APS_MAX_LENGTH_OF_APN;
        }
        PS_MEM_CPY(       g_PdpEntity[ucPdpId].PdpApn.aucValue,
                          &(pActReq->aucApn[1]),
                          pActReq->aucApn[0]);
    }

    /*ADDR.PdpType */
    g_PdpEntity[ucPdpId].PdpAddrFlag                = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum       = pActReq->ucPdpType;

    /*ADDR.value */
    if ( APS_ADDR_STATIC_IPV4 == pActReq->ucPdpType)
    {
        PS_MEM_CPY(       g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                          pActReq->aucIpAddr,
                          TAF_IPV4_ADDR_LEN );
    }
    else
    {
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[0]   = 0;
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[1]   = 0;
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[2]   = 0;
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[3]   = 0;
    }

    /*XID*/
    if ( pActReq->Op_Xid_PCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_PCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPCmprAlgrth = pActReq->ucPCmprAlgrth;
    }

    if ( pActReq->Op_Xid_DCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_DCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucDCmprAlgrth = pActReq->ucDCmprAlgrth;
    }

    /*Dns*/
    if (  (VOS_TRUE == pActReq->OP_DNS)
        &&(  (VOS_TRUE == pActReq->PdpDns.bitOpPrimDnsAddr)
           ||(VOS_TRUE == pActReq->PdpDns.bitOpSecDnsAddr) ))
    {
        /*有一个有效的DNS，就填状态机*/
        g_PdpEntity[ucPdpId].PdpDnsFlag             = VOS_TRUE;

        if (VOS_TRUE == pActReq->PdpDns.bitOpPrimDnsAddr)
        {
            g_PdpEntity[ucPdpId].PdpDns.OP_PriDns   = VOS_TRUE;

            PS_MEM_CPY(g_PdpEntity[ucPdpId].PdpDns.aucPriDns,
                       pActReq->PdpDns.aucPrimDnsAddr,
                       TAF_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pActReq->PdpDns.bitOpSecDnsAddr)
        {
            g_PdpEntity[ucPdpId].PdpDns.OP_SecDns   = VOS_TRUE;

            PS_MEM_CPY(g_PdpEntity[ucPdpId].PdpDns.aucSecDns,
                       pActReq->PdpDns.aucSecDnsAddr,
                       TAF_IPV4_ADDR_LEN);
        }
    }

    /*TFT*/
    g_PdpEntity[ucPdpId].PdpTftFlag                 = VOS_FALSE;

    return;
}


/*****************************************************************************
 Prototype      : Aps_PdpSecActReq()
 Description    : PDP二次激活. V100V001中二次激活只能由UE发起.在V200V001中,网络
                  也可以发起二次激活.
 Input          : pSecActReq
 Output         :
 Return Value   :
 Data Accessed  :
 Data Update    :
 Calls          : Aps_PdpSecActReqStateCheck()
                  Aps_PdpSecActReqParaCheck
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.日    期   : 2011年12月17日
   作    者   : s62952
   修改内容   : PS融合项目修改

  3.日    期   : 2012年5月3日
    作    者   : A00165503
    修改内容   : DTS2012042604902: GCF 8.2.2.35 用例失败
*****************************************************************************/
VOS_UINT32  Aps_PdpSecActReq(
    APS_PDP_SEC_ACT_REQ_ST             *pSecActReq
)
{
    VOS_UINT32                          ulResult;
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pActSecReqMsg;

    APS_NORM_LOG("APS rcv APS_PDP_ACT_SEC_REQ_ST ");


    /*检查输入参数是否合法;*/
    ulResult = Aps_PdpSecActReqParaCheck( pSecActReq );
    if (APS_PARA_INVALID == ulResult)
    {
        APS_WARN_LOG("Aps_PdpSecActReqParaCheck err ");

        return TAF_APS_FAIL;
    }
    /*在状态机中处理*/

    /*PDP类型是否PPP类型*/
    if ( APS_ADDR_PPP == g_PdpEntity[pSecActReq->ucPriPdpId].PdpAddr.ucPdpTypeNum)
    {
        /*激活失败的事件在调用该函数的函数中执行*/

        APS_WARN_LOG("prim PDP state err ");
        return  TAF_APS_FAIL;
    }

    /* 构造消息并填充消息头 */
    pActSecReqMsg = (SMREG_PDP_ACTIVATE_SEC_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_ACTIVATE_SEC_REQ);
    if (VOS_NULL_PTR == pActSecReqMsg)
    {
        return TAF_APS_FAIL;
    }

    /*调用函数Aps_PackSmSecActReqMsg()打包向SM发送的消息结构;*/
    Aps_PackSmSecActReqMsg(pSecActReq, pActSecReqMsg);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pActSecReqMsg))
    {
        APS_WARN_LOG("Aps_PdpSecActReq Snd msg fail!");
        return TAF_APS_FAIL;
    }

    /*填充状态机中*/
    Aps_SecActReqFillState(pSecActReq);

    return  TAF_APS_SUCC;

}

/*****************************************************************************
 Prototype      : Aps_SecActReqFillState
 Description    : 将输入的参数填入二次激活的PDP状态机中:QOS、TFT、SAPI;
                  将主激活PDP中的一些参数填入二次激活的PDP状态机中,包括PDPTYPE、ADDR、APN;
 Input          :
 Output         :
 Return Value   :
 Data Accessed  :
 Data Update    : g_PdpEntity[ucPdpId].
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
 2.日    期   : 2011年12月17日
   作    者   : s62952
   修改内容   : PS融合项目修改
*****************************************************************************/
VOS_VOID    Aps_SecActReqFillState(
    APS_PDP_SEC_ACT_REQ_ST              *pSecActReq
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucPriPdpId;

    ucPdpId                             = pSecActReq->ucPdpId;
    ucPriPdpId                          = pSecActReq->ucPriPdpId;


    /*GPRS参数标识要置1*/
    g_PdpEntity[ucPdpId].PdpGprsParaFlag            = VOS_TRUE;

    /* 二次激活一定是APP主动发起激活 */
    g_PdpEntity[ucPdpId].PdpProcTrackFlag           = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct
                                                    = APS_APP_MANUL_ACT;
    g_PdpEntity[ucPdpId].ActType                    = APS_PDP_ACT_SEC;

    /*ADDR*/
    g_PdpEntity[ucPdpId].PdpAddrFlag    = g_PdpEntity[ucPriPdpId].PdpAddrFlag;
    g_PdpEntity[ucPdpId].PdpAddr        = g_PdpEntity[ucPriPdpId].PdpAddr;

    /*APN*/
    g_PdpEntity[ucPdpId].PdpApnFlag     = g_PdpEntity[ucPriPdpId].PdpApnFlag;
    g_PdpEntity[ucPdpId].PdpApn         = g_PdpEntity[ucPriPdpId].PdpApn;

    /*LinkedNsapi*/
    g_PdpEntity[ucPdpId].ActType        = APS_PDP_ACT_SEC;
    g_PdpEntity[ucPdpId].ucLinkedNsapi  = g_PdpEntity[ucPriPdpId].ucNsapi;

    /*TFT*/
    if ( VOS_TRUE == pSecActReq->Op_Tft )
    {
        g_PdpEntity[ucPdpId].PdpTftFlag = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpTft[0]  = pSecActReq->Tft;
    }

    /*QOS*/
    g_PdpEntity[ucPdpId].PdpQosFlag     = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpQos         = pSecActReq->Qos;

    /*AUTH*/
    g_PdpEntity[ucPdpId].PdpAuthFlag    = g_PdpEntity[ucPriPdpId].PdpAuthFlag;
    g_PdpEntity[ucPdpId].AuthTab        = g_PdpEntity[ucPriPdpId].AuthTab;

    /*XID*/
    if ( pSecActReq->Op_Xid_PCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_PCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPCmprAlgrth = pSecActReq->ucPCmprAlgrth;
    }

    if ( pSecActReq->Op_Xid_DCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_DCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucDCmprAlgrth = pSecActReq->ucDCmprAlgrth;
    }

    /*DNS*/
    g_PdpEntity[ucPdpId].PdpDnsFlag     = g_PdpEntity[ucPriPdpId].PdpDnsFlag;
    g_PdpEntity[ucPdpId].PdpDns         = g_PdpEntity[ucPriPdpId].PdpDns;

    return;
}

/*****************************************************************************
 函 数 名  : Aps_PdpSecActReqParaCheck
 功能描述  : 二次激活时输入的参数检查
 输入参数  : APS_PDP_SEC_ACT_REQ_ST *pSecActReq
 输出参数  : 无
 返 回 值  : APS_PARA_VALID
             APS_PARA_INVALID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005
    作    者   : 韩鲁峰
    修改内容   : 新生成函数

  2.日    期   : 2010年12月15日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010120605160, W单模下PDP激活后, 修改为双模,
                 重选到G下数传无法恢复

  3.日    期   : 2011年5月26日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011051903901, 网侧下发PDP_ACTIVATE_ACCEPT
                 消息中的QOS IE为reserved "0", PDP激活失败

  4.日    期   : 2012年5月3日
    作    者   : A00165503
    修改内容   : DTS2012042604902: GCF 8.2.2.35 用例失败
*****************************************************************************/
VOS_UINT32  Aps_PdpSecActReqParaCheck ( APS_PDP_SEC_ACT_REQ_ST *pSecActReq)
{

    /*入口参数的合法性由主调函数保证*/

    /*pdpId*/
    if( !(APS_JUDEG_PDPID_VALID(pSecActReq->ucPdpId)) )

    {
        return  APS_PARA_INVALID;
    }

    /*PriPdpId*/
    if( !(APS_JUDEG_PDPID_VALID(pSecActReq->ucPriPdpId)) )

    {
        return  APS_PARA_INVALID;
    }

#if 0
    /*TFT*/
    if( pSecActReq->Op_Tft )
    {
        if( TAF_APS_FAIL == Aps_TftValidOrNot(&pSecActReq->Tft))
        {
            return  APS_PARA_INVALID;
        }
    }
#endif

    return  APS_PARA_VALID;
}

/*****************************************************************************
 函 数 名  : Aps_PackSmSecActReqMsg
 功能描述  : 打包向SM发送SEC_ACT_REQ的消息
 输入参数  : APS_PDP_SEC_ACT_REQ_ST             *pSecActReq
             SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pStSecActReq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年xx月xx日
    作    者   : 韩鲁峰
    修改内容   : 新生成函数

  2.日    期   : 2006年03月03日
    作    者   : H41410
    修改内容   : 问题单号: A32D02345

  3.日    期   : 2010年12月15日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010120605160，W单模下PDP激活后，修改为双模，
                 重选到G下数传无法恢复
  4.日    期   : 2012年01月05日
    作    者   : h44270
    修改内容   : 增加默认承载，当前发送到SM的CR变为从实体中的TI中来获取，不再
                 直接使用PDP ID

*****************************************************************************/
VOS_VOID Aps_PackSmSecActReqMsg(
    APS_PDP_SEC_ACT_REQ_ST             *pSecActReq,
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pStSecActReq
)
{
    /* 填写 ConnectId (CR)，当前CR等同于Pdp Id */
    pStSecActReq->ucConnectId       = pSecActReq->ucPdpId;
    pStSecActReq->bitOpSapi         = VOS_FALSE;
    pStSecActReq->bitOpTft          = VOS_FALSE;
    pStSecActReq->bitOpSpare        = VOS_FALSE;

    /*LLC SAPI*/
    pStSecActReq->bitOpSapi         = VOS_TRUE;
    pStSecActReq->ucSapi            = pSecActReq->ucSapi;

    /*QOS*/
    Aps_PackSmQos(  &(pSecActReq->Qos),
                    &(pStSecActReq->stRequestedQos)   );

    /*TFT*/
    if ( VOS_TRUE == pSecActReq->Op_Tft )
    {
        pStSecActReq->bitOpTft      = VOS_TRUE;
        Aps_PackSmTft(    pSecActReq->ucPdpId,
                          &pSecActReq->Tft,
                          &(pStSecActReq->stTft) );
    }

    /*PrimNsapi*/
    pStSecActReq->ucPrimNsapi       = g_PdpEntity[pSecActReq->ucPriPdpId].ucNsapi;

    return;
}

/*****************************************************************************
 函 数 名  : Aps_PdpMdfReq
 功能描述  : PDP修改
 输入参数  : APS_PDP_MDF_REQ_ST              *pMdfReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005
    作    者   : ---
    修改内容   : 新生成函数

  2.日    期   : 2011年5月26日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011051903901, 网侧下发PDP_ACTIVATE_ACCEPT
                 消息中的QOS IE为reserved "0", PDP激活失败

  3.日    期   : 2011年12月22日
    作    者   : A00165503
    修改内容   : PS Project: 修改PDP修改处理逻辑

*****************************************************************************/
VOS_UINT32  Aps_PdpMdfReq( APS_PDP_MDF_REQ_ST              *pMdfReq)
{

    SMREG_PDP_MODIFY_REQ_STRU          *pstPdpModReq;

    APS_NORM_LOG("APS rcv APS_PDP_MDF_REQ_ST ");

    if ( VOS_NULL_PTR == pMdfReq )
    {
        /*上报修改失败*/
        APS_WARN_LOG("ERROR! The input pointer parameter  can not be NULL ! ");
        return(TAF_APS_FAIL);
    }

    /*将输入的参数存储到表g_PdpModifyReqTable*/
    g_PdpModifyReqTable[pMdfReq->ucPdpId]   = (*pMdfReq);

    /*置有无修改QOS的标识*/
    if ( pMdfReq->Op_Qos )
    {
        g_PdpModifyReqTable[pMdfReq->ucPdpId].Op_Spare = APS_MDF_HAS_QOS;
    }
    else
    {
        g_PdpModifyReqTable[pMdfReq->ucPdpId].Op_Spare = APS_MDF_NO_QOS;
    }

    /* 构造消息并填充消息头 */
    pstPdpModReq = (SMREG_PDP_MODIFY_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_MODIFY_REQ);
    if (VOS_NULL_PTR == pstPdpModReq)
    {
        return TAF_APS_FAIL;
    }

    /*构造向SM发送的修改消息*/
    Aps_PackSmMdfReqMsg( pMdfReq, pstPdpModReq);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstPdpModReq))
    {
        APS_WARN_LOG("Aps_PdpMdfReq Snd msg fail!");
        return TAF_APS_FAIL;
    }

    return(TAF_APS_SUCC);
}

/*****************************************************************************
 Prototype      : Aps_PackSmMdfReqMsg
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Accessed  :
 Data Update    :
 Calls          :
 Called By      : Aps_PdpMdfReq
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
  2.2006-03-03 MODIFY BY H41410 FOR A32D02345
  3.日    期   : 2012年01月05日
    作    者   : h44270
    修改内容   : 增加默认承载，当前发送到SM的CR变为从实体中的TI中来获取，不再
                 直接使用PDP ID
  4.日    期   : 2012年04月04日
    作    者   : s62952
    修改内容   : 问题单号:DTS20120404,删除TFT处理

  5.日    期   : 2013年4月23日
    作    者   : L47619
    修改内容   : V9R1 IPv6&TAF/SM接口优化项目修改
*****************************************************************************/
VOS_VOID    Aps_PackSmMdfReqMsg( APS_PDP_MDF_REQ_ST             *pMdfReq,
                                            SMREG_PDP_MODIFY_REQ_STRU       *pStPdpMdfReq   )
{
    /*StPcpMsg的初始化*/
    /* ST_PCP_MSG的消息构造 */

    /* 填写 ConnectId (CR)，当前CR等同于Pdp Id */
    pStPdpMdfReq->ucConnectId           = pMdfReq->ucPdpId;
    pStPdpMdfReq->bitOpRequestedNewQos  = VOS_FALSE;
    pStPdpMdfReq->bitOpNsapi            = VOS_FALSE;
    pStPdpMdfReq->bitOpNewtft           = VOS_FALSE;
    pStPdpMdfReq->bitOpSapi             = VOS_FALSE;
    pStPdpMdfReq->bitOpSpare            = VOS_FALSE;

    /*SAPI*/
    pStPdpMdfReq->bitOpSapi             = VOS_TRUE;
    pStPdpMdfReq->ucSapi                = pMdfReq->ucSapi;

    /*Qos*/
    if ( pMdfReq->Op_Qos)
    {
        pStPdpMdfReq->bitOpRequestedNewQos = VOS_TRUE;
        Aps_PackSmQos(      &(pMdfReq->Qos),
                            &(pStPdpMdfReq->stRequestedNewQos) );
    }

   #if 0
    /*TFT */
    if ( pMdfReq->Op_Tft)
    {
        pStPdpMdfReq->OP_Newtft         = VOS_TRUE;
        Aps_PackSmTft(      pMdfReq->ucPdpId,
                            &pMdfReq->Tft,
                            &pStPdpMdfReq->Newtft );
    }
    #endif

    /*向MODIRY_REQ中填写NSAPI */
    pStPdpMdfReq->bitOpNsapi            = VOS_TRUE;
    pStPdpMdfReq->ucNsapi               = g_PdpEntity[pMdfReq->ucPdpId].ucNsapi;

    return;
}


/*****************************************************************************
 Prototype      : Aps_AppDeactReq()
 Description    : APP发起去激活，则调用此函数.此函数的特点是状态机中的去激
                  活方式中设置为APP去激活,不上报去激活，而是等SM或SNDCP响应后
                  再上报DEACT_CNF.
 Input          : ucPdpId,
                  RejCause
 Output         : NO
 Return Value   : NO
 Data Accessed  : NO
 Data Update    : NO
 Calls          : Aps_PdpDeActReq()
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function

  2.日    期   : 2011年12月22日
    作    者   : A00165503
    修改内容   : PS Project: 修改PDP去激活处理逻辑
  3. 日    期   : 2010年12月27日
     作    者   : h44270
     修改内容   : Modified by PS Project, 增加cause的填写
  4.日    期   : 2012年06月05日
    作    者   : f00179208
    修改内容   : DTS2012060200787, 去激活默认承载，挂接的专有承载也需要一起去激活
  5.日    期   : 2012年06月29日
    作    者   : f00179208
    修改内容   : DTS2012062902425, IPV4V6拨号，IPV4成功IPV6失败，会内部去激活掉IPV4的PDP
  6.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 Aps_AppDeactReq(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    VOS_UINT32                          ulResult;
    APS_PDP_DEACT_REQ_ST                ApsDeActReq;

    /* 初始化 */
    ulResult                            = VOS_OK;

    /* 填写去激活参数 */
    ApsDeActReq.ucPdpId                 = ucPdpId;
    ApsDeActReq.ucTearDown              = TAF_PDP_NOT_TEAR_DOWN;
    ApsDeActReq.enCause                 = enCause;

    /* 如果需要去激活的PDP是主PDP则带上Teardown标识 */
    if (APS_PDP_ACT_PRI == TAF_APS_GetPdpEntActType(ucPdpId))
    {
        ApsDeActReq.ucTearDown      = TAF_PDP_TEAR_DOWN;
    }

    /* 调用去激活函数 */
    ulResult    = Aps_PdpDeActReq(&ApsDeActReq);
    if (VOS_OK != ulResult)
    {
        MN_ERR_LOG("Aps_AppDeactReq: Deactivate PDP failed!");
    }

    g_PdpEntity[ucPdpId].PdpProcTrackFlag   = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitDeAct
                                            = APS_APP_INIT_DEACT;
     return ulResult;
}


/*****************************************************************************
 Prototype      : Aps_PdpDeActReq()
 Description    : PDP去修改,或拒绝网络发起的激活。
                  当拒绝网络发起的激活时，输入的参数pDeActReq->ucTearDown
                  必须为TAF_PDP_NOT_TEAR_DOWN，即只拒绝一个PDP。
                  该函数包括了状态修改和定时器启动
 Input          : pDeActReq
 Output         :
 Return Value   :
 Data Accessed  :
 Calls          : Aps_OnePdpDeActReq
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年12月22日
    作    者   : A00165503
    修改内容   : PS Project: 修改PDP去激活处理逻辑
  3.日    期   : 2012年06月05日
    作    者   : f00179208
    修改内容   : DTS2012060200787, 去激活默认承载，挂接的专有承载也需要一起去激活
*****************************************************************************/
VOS_UINT32 Aps_PdpDeActReq(
    APS_PDP_DEACT_REQ_ST               *pDeActReq
)
{
    VOS_UINT8                           ucPdpId;

    APS_NORM_LOG("APS rcv APS_PDP_DEACT_REQ_ST ");

    ucPdpId = pDeActReq->ucPdpId;


    /*如果PDP类型是PPP,不应该填TEARDOWN,此时若有TEARDWN,则按照没有TEARDOWN进行去激活*/
    if ( ( VOS_FALSE == g_PdpEntity[ucPdpId].PdpAddrFlag)
        || ( APS_ADDR_PPP == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
    {
        /*没有地址,说明是PPP;或者填写了ADDRFLAG,但PDP类型为PPP*/
        pDeActReq->ucTearDown           = TAF_PDP_NOT_TEAR_DOWN;
    }

    if (TAF_PDP_NOT_TEAR_DOWN == pDeActReq->ucTearDown)
    {
        /* 状态机中的TEARDOWN赋值 */
        APS_SET_PDPENTITY_TEATDOWN(ucPdpId, APS_DEACT_NOTEARDOWN);
        Aps_PdpDeActOneReq(pDeActReq, APS_SYS_REL);
    }
    else
    {
        APS_SET_PDPENTITY_TEATDOWN(ucPdpId, APS_DEACT_TEARDOWN);
        Aps_PdpDeActOneReq(pDeActReq, APS_SYS_REL);
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : Aps_PdpDeActOneReq()
 Description    : 去激活一个PDP,此函数不进行状态修改;
 Input          : pDeActReq
                  ucRelSmType   去激活SM的类型:
                            #define APS_LOCAL_REL     0
                            #define APS_SYS_REL       1
 Output         : NO
 Return Value   : NO
 Data Accessed  :
 Data Update    :
 Calls          :
 Called By      : Aps_PdpDeActReq()
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
  2.日    期   : 2011年10月8日
    作    者   : A00165503
    修改内容   : AT Project: 不需要再上报TAF_PS_EVT_PDP_DEACTIVE_ING事件
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_VOID    Aps_PdpDeActOneReq(         APS_PDP_DEACT_REQ_ST   *pDeActReq,
                                        VOS_UINT8               ucRelSmType)
{
    SMREG_PDP_DEACTIVATE_REQ_STRU      *pStDeActReq;

    /* 构造消息并填充消息头 */
    pStDeActReq = (SMREG_PDP_DEACTIVATE_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_DEACTIVATE_REQ);
    if (VOS_NULL_PTR == pStDeActReq)
    {
        return;
    }

    /* 填写 ConnectId (CR)，当前CR等同于Pdp Id */
    pStDeActReq->ucConnectId            = pDeActReq->ucPdpId;

    /*消息初始化*/
    pStDeActReq->bitOpTearDownInd       = VOS_FALSE;
    pStDeActReq->bitOpNsapi             = VOS_FALSE;
    pStDeActReq->bitOpPcpTaCause        = VOS_FALSE;
    pStDeActReq->bitOpSpare             = VOS_FALSE;

    /*填充消息*/
    pStDeActReq->bitOpTearDownInd       = VOS_TRUE;
    pStDeActReq->ucTearDownInd          = pDeActReq->ucTearDown;

    /*不填NSAPI，因为清资源时可能还没有分配NSAPI
    pStDeActReq->OP_Nsapi               = VOS_TRUE;
    pStDeActReq->ucNsapi                = g_PdpEntity[pDeActReq->ucPdpId].ucNsapi;
    */

    pStDeActReq->enCause                = pDeActReq->enCause;

    /*赋值去激活SM的原因,本地释放或者系统释放*/
    pStDeActReq->bitOpPcpTaCause        = VOS_TRUE;
    pStDeActReq->enPcpTaCause           = ucRelSmType;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pStDeActReq))
    {
        APS_WARN_LOG("Aps_PdpDeActOneReq Snd msg fail!");
    }

    return;
}



/*****************************************************************************
 Prototype      : Aps_PdpDeActReqParaCheck()
 Description    : 检查函数Aps_PdpActReq()的入口参数是否合法
 Input          : pSmActReq
 Output         :
 Return Value   : pucResult,取值: APS_PARA_VALID、APS_PARA_INVALID
 Data Accessed  : NO
 Data Update    : NO
 Calls          :
 Called By      : Aps_PdpActReq()
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_PdpDeActReqParaCheck( APS_PDP_DEACT_REQ_ST *pDeActReq )
{
    if ( VOS_NULL == pDeActReq)
    {
        APS_WARN_LOG("Aps_PdpDeActReq input pointer is NULL ");
        return  APS_PARA_INVALID;
    }

    if (!(APS_JUDEG_PDPID_VALID(pDeActReq->ucPdpId)))
    {
        APS_WARN_LOG("Aps_PdpDeActReq input ucPdpId ERR ");
        return  APS_PARA_INVALID;
    }

    if (!(APS_JUDEG_TEARDOWN_VALID(pDeActReq->ucTearDown)))
    {
        APS_WARN_LOG("Aps_PdpDeActReq input ucTearDown ERR ");
        return  APS_PARA_INVALID;
    }

    return  APS_PARA_VALID;

}


/*****************************************************************************
 Prototype      : Aps_PackSmQos()
 Description    : 将APS的QOS结构打包成SM需要的QOS结构
 Input          : pApSQos
 Output         : pSmQos
 Return Value   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年12月29日
    作    者   : A00165503
    修改内容   : PS Project: 修改获取当前RAT类型的方式

  3.日    期   : 2012年5月28日
    作    者   : A00165503
    修改内容   : DTS2012052605200: NV50060使能, 且禁止Spare_bit3等参数时,
                 W模PDP激活QOS参数异常
  4.日    期   : 2012年7月6日
    作    者   : z60575
    修改内容   : DTS2012070400072: 协议版本为r7时也不带QOS OCT 17和18
  5.日    期   : 2013年6月18日
    作    者   : Y00213812
    修改内容   : DTS2013032204300: 协议版本为r7时，判断NV9008中接入能力，判断
                 是否携带QOS OCT 17和18

*****************************************************************************/
VOS_VOID  Aps_PackSmQos   (
    APS_PDP_QOS_ST                     *pApsQos,
    SM_TAF_QOS_STRU                    *pSmQos
)
{
    VOS_INT8                            ue_revision;
    WAS_NVIM_UE_CAPA_STRU               stUECapa;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    PS_MEM_SET(&stUECapa, 0x00, sizeof(WAS_NVIM_UE_CAPA_STRU));
    /* 读取支持上行16QAM,DC UPA 支持能力 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(WAS_NVIM_UE_CAPA_STRU)))
    {
        APS_WARN_LOG("Aps_PackSmQos: en_NV_Item_WAS_RadioAccess_Capa NV Read  Fail!");
        return;
    }

    ue_revision = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);


#if (PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (ue_revision >= PS_PTL_VER_R5)
    {
        if ( ( TAF_APS_RAT_TYPE_GSM == TAF_APS_GetCurrPdpEntityRatType())
          && ( APS_2G_BIT3_ENABLE == g_ucDisable2GR5QosExt ))
        {
            /* IEI Length */
            pSmQos->ulQosLen = 0xB;
        }
        else
        {
#if (PS_UE_REL_VER >= PS_PTL_VER_R7)
            if (TAF_APS_R7_SUPP_UL16QAM_OR_DCUPA(ue_revision, stUECapa))
            {
                enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
                /* TDS速率达不到11M以上，因此TDS下还是按照长度为E，避免仪器无法兼容 */
                if ((TAF_SDC_SYS_MODE_WCDMA == TAF_SDC_GetSysMode())
                && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
                {
                    pSmQos->ulQosLen = 0xE;
                }
                else
                {
                    pSmQos->ulQosLen = 0x10;
                }
            }
            else
#endif
            {
                /* IEI Length */
                pSmQos->ulQosLen = 0xE;
            }

        }
    }
    else
#endif
    {
        if (ue_revision >= PS_PTL_VER_R99)
        {
            /* IEI Length */
            pSmQos->ulQosLen = 0xB;
        }
        else
        {
            /* IEI Length */
            pSmQos->ulQosLen = 0x3;
        }
    }

    /* ucDelayClass左移3位, 使ucDelayClass的3个有效位位于协议中QOS IE octet3的
    1~8位中的第6,5,4位, 使用同样的方法打包协议中QOS IE 的其余octet */
    pSmQos->aucQos[0]       = (VOS_UINT8)((pApsQos->ucDelayClass)<<3);
    pSmQos->aucQos[0]       |= (pApsQos->ucReliabClass);

    pSmQos->aucQos[1]       = (VOS_UINT8)((pApsQos->ucPeakThrough)<<4);
    pSmQos->aucQos[1]       |= (pApsQos->ucPrecedenceClass);

    pSmQos->aucQos[2]       = (pApsQos->ucMeanThrough);

    if (ue_revision >= PS_PTL_VER_R99)
    {
        pSmQos->aucQos[3]   = (VOS_UINT8)((pApsQos->ucTrafficClass)<<5);
        pSmQos->aucQos[3]   |= (VOS_UINT8)((pApsQos->ucDeliverOrder)<<3);
        pSmQos->aucQos[3]   |= (pApsQos->ucDeliverOfErrSdu);

        pSmQos->aucQos[4]   = (pApsQos->ucMaximSduSize);
        pSmQos->aucQos[5]   = (pApsQos->ucMaxBitRateForUp);
        pSmQos->aucQos[6]   = (pApsQos->ucMaxBitRateForDown);

        pSmQos->aucQos[7]   = (VOS_UINT8)((pApsQos->ucResidualBer)<<4);
        pSmQos->aucQos[7]  |= (pApsQos->ucSduErrRatio);

        pSmQos->aucQos[8]  = (VOS_UINT8)((pApsQos->ucTransDelay)<<2);
        pSmQos->aucQos[8]  |= (pApsQos->ucTraffHandlPrior);

        pSmQos->aucQos[9]  = (pApsQos->ucGuarantBitRateForUp);
        pSmQos->aucQos[10] = (pApsQos->ucGuarantBitRateForDown);
    }

#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (ue_revision >= PS_PTL_VER_R5)
    {
        if ( (TAF_APS_RAT_TYPE_GSM != TAF_APS_GetCurrPdpEntityRatType())
          || (APS_2G_BIT3_ENABLE != g_ucDisable2GR5QosExt) )
        {
            pSmQos->aucQos[11]  = (VOS_UINT8)((pApsQos->ucSignallingIndication)<<4);
            pSmQos->aucQos[11] |= (pApsQos->ucSrcStatisticsDescriptor);

            pSmQos->aucQos[12]  = (pApsQos->ucMaxBitRateForDownExt);
            pSmQos->aucQos[13]  = (pApsQos->ucGuarantBitRateForDownExt);
        }
    }
#endif
#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (0x10 == pSmQos->ulQosLen)
    {
        if ( ( TAF_APS_RAT_TYPE_GSM != TAF_APS_GetCurrPdpEntityRatType())
          || (APS_2G_BIT3_ENABLE != g_ucDisable2GR5QosExt) )
        {
            pSmQos->aucQos[14]  = (pApsQos->ucMaxBitRateForUpExt);
            pSmQos->aucQos[15]  = (pApsQos->ucGuarantBitRateForUpExt);
        }
    }
#endif
    return;

}

/*****************************************************************************
 Prototype      : Aps_PackSmTft
 Description    : 将APS的TFT结构打包成SM需要的TFT结构.基本继承V100R001.V200添加
                  3个新成员,需要修改.
 Input          : pApSTft
 Output         : pSmTft
 Return Value   :
 Calls          :
 Called By      :
    VOS_UINT32              OP_SourcePort           : 1;
    VOS_UINT32              OP_DestPort             : 1;
    VOS_UINT32              OP_SourceIpAddrAndMask  : 1;
    VOS_UINT32              OP_ProtocolId           : 1;
    VOS_UINT32              OP_ulSecuParaIndex      : 1;

    VOS_UINT32              OP_ucTypeOfService      : 1;
    VOS_UINT32              OP_ucTypeOfServiceMask  : 1;
 History        : ---
  1.Date        : 2005-05
    Author      : ---
    Modification: Created function
  2.Date        : 2005-
    Author      : ---
    Modification: V200添加了3个成员,还没有修改
  3.2006-03-03 MODIFY BY H41410 FOR A32D02345
  4.2006-08-03 modify by L47619 for A32D05213
  5.2006-08-03 modify by L47619 for A32D05212
*****************************************************************************/
VOS_VOID  Aps_PackSmTft   (     VOS_UINT8           ucPdpId,
                                APS_PDP_TFT_ST*     pApsTft,
                                SM_TAF_TFT_STRU*    pSmTft  )
{

    VOS_UINT16 usBufSize = 0;


    /*协议中的OCTET3的高3位是TFT的操作码,本版的TFT只支持creat 和replace TFT, 不支持
    其他TFT操作, 参考10.5.6.12/24008; OCTET3的低4位赋值为包过滤器的数目,
    OCTET3的低4位 = 1;*/
    /*根据该PDP当前是否已经使用了TFT决定操作类型是creat 还是replace*/
    if (g_PdpEntity[ucPdpId].PdpTftFlag)
    {
        pSmTft->aucNewtft[0] = APS_TFT_REPLACE_TFT | APS_TFT_ONE_FILTER;
    }
    else
    {
        pSmTft->aucNewtft[0] = APS_TFT_CREAT_TFT | APS_TFT_ONE_FILTER;
    }

    /* OCTET4开始为filter1的内容 */
    pSmTft->aucNewtft[1] =(VOS_UINT8)pApsTft->ucPacketFilterId;/* OCTET4 Packet filter identifier 1 */
    pSmTft->aucNewtft[2] = pApsTft->ucPrecedence;              /* OCTET5 ,Packet filter evaluation precedence 1 */

    /* pSmTft->Newtft[3] 为下边filter1的4个component项的长度和,待填完下面的
    4个component项后再填此字节 */

    /* 从数组的[4]开始填filter1的components */
    usBufSize = APS_TFT_FILTER1_COMPONENT_BEGIN;

    if ( pApsTft->OP_SourceIpAddrAndMask )
    {
        /* component1是 IPv4 source address type */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_IPV4_ADDR;
        usBufSize++;

        /* pSmTft->Newtft[5～8] 赋值为4个字节的地址pApsTft-> ucSourceIpAddress;
        " Bit 8 of octet 5 represents the most signifi cant bit of the IP address
        and bit 1 of octet 8 the least signifi cant bit ." */
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[0];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[1];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[2];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[3];
        usBufSize++;

        /*pSmTft->Newtft[9～12]赋值为4个字节的掩码pApsTft->ucSourceIpMask;*/
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[0];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[1];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[2];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[3];
        usBufSize++;
    }


    if ( pApsTft->OP_ProtocolId )
    {
        /* component2是 Protocol identifier/Next header type*/
        pSmTft->aucNewtft[usBufSize] = APS_TFT_PROTOCAL_ID;
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->ucProtocolId;
        usBufSize++;
    }


    if ( pApsTft->OP_DestPort )
    {
        /* component3是 Destination port range type */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_DEST_PORT_RANG ;
        usBufSize++;

        /*pSmTft->Newtft[16~17] = pApsTft->usDestinationPortLowLimit;
        其中port range low limit先发送*/
        /*高字节先发*/
        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usDstPortLowLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* 高位字节 */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usDstPortLowLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* 低位字节 */
        usBufSize++ ;

        /*pSmTft->Newtft[18~19] = pApsTft->usDestinationPortHighLimit;
        port range high limit后发送 */
        /*高字节先发*/
        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usDstPortHighLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* 高位字节 */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usDstPortHighLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* 低位字节 */
        usBufSize++ ;
    }


    if ( pApsTft->OP_SourcePort )
    {
        /* component4是 Source port range type */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_SOURCE_PORT_RANG;
        usBufSize++;
        /*pSmTft->Newtft[21~22] = pApsTft->usSourcePortLowLimit*/

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usSrcPortLowLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* 高位字节 */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usSrcPortLowLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* 低位字节 */
        usBufSize++;

        /*pSmTft->Newtft[23~24] = pApsTft->usSourcePortHighLimit;*/
        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usSrcPortHighLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* 高位字节 */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usSrcPortHighLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* 低位字节 */
        usBufSize++;
    }


    if ( pApsTft->OP_ulSecuParaIndex)
    {
        /* component4是 IP Sec SPI */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_SPI;
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_32_TO_25_OCTET)>>24);/* 最高位字节 */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_24_TO_17_OCTET)>>16);/* 次高位字节 */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_16_TO_8_OCTET)>>8);  /* 次低位字节 */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_7_TO_0_OCTET));      /* 最低位字节 */
        usBufSize++;
    }


    if ( pApsTft->OP_ucTypeOfService )
    {
        /* component4是 TOS (IPv4) / Traffic Class (IPv6) and Mask */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_TOS;
        usBufSize++;

        pSmTft->aucNewtft[usBufSize] = pApsTft->ucTypeOfService;        /*TOS*/
        usBufSize++;

        pSmTft->aucNewtft[usBufSize] = pApsTft->ucTypeOfServiceMask;
        usBufSize++;
    }

    /* pSmTft->Newtft[3]    = filter1中的所有4个components的长度和
                            = TFT码流数组的字节数- TFT码流前边4个域的字节数*/
    pSmTft->aucNewtft[APS_TFT_FILTER1_LENGTH_LOCATION]
        = (VOS_UINT8)(usBufSize - APS_TFT_FILTER1_OP_ID_PRE_LEN_AMOUNT);

    /* TFT码流数组的字节数 =  TFT码流数组最后一个字节的索引数 + 1 */
    pSmTft->ulTftLen = usBufSize;

    return;
}

/*****************************************************************************
 Prototype      : Aps_PackSmAddr()
 Description    : 将APS的ADDR结构打包成SM需要的ADDR结构
 Input          : pucPdpType指向的PDP类型,
                  取值为:APS_ADDR_STATIC_IPV4, APS_ADDR_DYNAMIC_IPV4, APS_ADDR_PPP
                  pucAppAddr指向的PDP地址
 Output         : pSmAddr指向的结构体
 Return Value   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_PackSmAddr  (
    VOS_UINT8                          *pucPdpType,
    VOS_UINT8                          *pucAppAddr,
    SM_TAF_PDP_ADDR_STRU               *pSmAddr
)
{
    /*STATIC IPV4*/
    if (APS_ADDR_STATIC_IPV4    == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = TAF_IPV4_ADDR_LEN + 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = APS_PDP_TYPE_NUM_IPV4;
        PS_MEM_CPY(         &(pSmAddr->aucPdpAddr[2]),
                            pucAppAddr,
                            TAF_IPV4_ADDR_LEN);
    }
    else if (APS_ADDR_DYNAMIC_IPV4 == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = APS_PDP_TYPE_NUM_IPV4;
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (MN_APS_ADDR_IPV6 == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = MN_APS_PDP_TYPE_NUM_IPV6;
    }
    else if (MN_APS_ADDR_IPV4V6 == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = MN_APS_PDP_TYPE_NUM_IPV4V6;
    }
#endif
    else
    {
        /*PPP*/
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_ETSI;
        pSmAddr->aucPdpAddr[1]  = APS_PDP_TYPE_NUM_PPP;
    }

    return(TAF_APS_SUCC);

}

/*****************************************************************************
 Prototype      : Aps_PackSmApn()
 Description    : 将SM的QOS结构打包成APS的QOS结构
 Input          : pucAppApn指向的数组
 Output         : pSmApn指向的结构体
 Return Value   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_PackSmApn(  VOS_UINT8              *pucAppApn,
                            SM_TAF_APN_STRU      *pSmApn      )
{
    pSmApn->ulApnLen           = *pucAppApn;

    if (pSmApn->ulApnLen < APS_MAX_LENGTH_OF_APN )
    {
        PS_MEM_CPY(       pSmApn->aucApnAddr,
                          &(pucAppApn[1]),
                          pSmApn->ulApnLen   );
    }
    else
    {
        pSmApn->ulApnLen       = 0;
    }

    return;
}



/*****************************************************************************
 函 数 名  : MN_APS_QosValidOrNot_ForTrafficHandlingPriority
 功能描述  : Traffic handling priority合法性校验(Aps_QosValidOrNot降圈复杂度)
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年06月01日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_APS_QosValidOrNot_ForTrafficHandlingPriority(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* 不属于闭区间[0, 3]*/
    if(psQos->ucTraffHandlPrior > APS_3GPP_QOS_TRAFFHANDLPRIOR_TOP)
    {
        APS_WARN_LOG("psQos->ucTraffHandlPrior , Aps_QosValidOrNot()");
    }

    return TAF_APS_SUCC;
}/* end of Function */

#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
/*****************************************************************************
 函 数 名  : Aps_QosValidOrNot_ForSrcStatisticsDescriptor
 功能描述  : Source statistics descriptor合法性校验(Aps_QosValidOrNot降圈复杂度)
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Aps_QosValidOrNot_ForSrcStatisticsDescriptor(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* 不属于闭区间[0, 15]*/
    if(psQos->ucSrcStatisticsDescriptor > APS_3GPP_QOS_SSD_TOP)
    {
        APS_WARN_LOG("psQos->ucSrcStatisticsDescriptor not valid , Aps_QosValidOrNot()");
        return(TAF_APS_FAIL);
    }

    return TAF_APS_SUCC;
}


/*****************************************************************************
 函 数 名  : Aps_QosValidOrNot_ForSignallingIndication
 功能描述  : Signalling indication合法性校验(Aps_QosValidOrNot降圈复杂度)
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2011年06月01日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011052605913,[B052]UE对PDP激活接受消息检查过严
                 当Guaranteed bit rate for downlink为reserved 255(0xFF)时，PDP激活失败
*****************************************************************************/
VOS_UINT32 Aps_QosValidOrNot_ForSignallingIndication(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* 不属于闭区间[0, 1]*/
    if(psQos->ucSignallingIndication > APS_3GPP_QOS_SIG_IND_TOP)
    {
        APS_WARN_LOG("psQos->ucSignallingIndication not valid , Aps_QosValidOrNot()");
    }

    return TAF_APS_SUCC;
}

/*****************************************************************************
 函 数 名  : Aps_QosValidOrNot_ForMaxBitRateForDownExt
 功能描述  : Max bitrate for downlink(extended)合法性校验(Aps_QosValidOrNot降圈复杂度)
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2011年06月01日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011052605913,[B052]UE对PDP激活接受消息检查过严
                 当Guaranteed bit rate for downlink为reserved 255(0xFF)时，PDP激活失败
*****************************************************************************/
VOS_UINT32 Aps_QosValidOrNot_ForMaxBitRateForDownExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* 不属于闭区间[0, 250](R6版本区间为[0, 74], R7版本区间为[0, 250])*/
    if(psQos->ucMaxBitRateForDownExt > APS_3GPP_MAX_BITRATE_DOWN_TOP)
    {
        APS_WARN_LOG("psQos->ucMaxBitRateForDownExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucMaxBitRateForDownExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucMaxBitRateForDown))
        {
            APS_WARN_LOG("psQos->ucMaxBitRateForDown not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}


/*****************************************************************************
 函 数 名  : Aps_QosValidOrNot_ForGuarantBitRateForDownExt
 功能描述  : Guaranteed bitrate for downlink(extended)合法性校验(Aps_QosValidOrNot降圈复杂度)
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2011年06月01日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011052605913,[B052]UE对PDP激活接受消息检查过严
                 当Guaranteed bit rate for downlink为reserved 255(0xFF)时，PDP激活失败
*****************************************************************************/
VOS_UINT32 Aps_QosValidOrNot_ForGuarantBitRateForDownExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* 不属于闭区间[0, 250](R6版本区间为[0, 74], R7版本区间为[0, 250])*/
    if(psQos->ucGuarantBitRateForDownExt > APS_3GPP_GUARANT_BITRATE_DOWN_TOP)
    {
        APS_WARN_LOG("psQos->ucGuarantBitRateForDownExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucGuarantBitRateForDownExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucGuarantBitRateForDown))
        {
            APS_WARN_LOG("psQos->ucGuarantBitRateForDown not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}
#endif


#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
/*****************************************************************************
 函 数 名  : Aps_QosValidOrNot_ForMaxBitRateForUpExt
 功能描述  : Max bitrate for downlink(extended)合法性校验(Aps_QosValidOrNot降圈复杂度)
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2011年06月01日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011052605913,[B052]UE对PDP激活接受消息检查过严
                 当Guaranteed bit rate for downlink为reserved 255(0xFF)时，PDP激活失败
*****************************************************************************/
VOS_UINT32 Aps_QosValidOrNot_ForMaxBitRateForUpExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* 不属于闭区间[0, 250](R7版本区间为[0, 250])*/
    if(psQos->ucMaxBitRateForUpExt > APS_3GPP_MAX_BITRATE_UP_TOP)
    {
        APS_WARN_LOG("psQos->ucMaxBitRateForUpExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucMaxBitRateForUpExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucMaxBitRateForUp))
        {
            APS_WARN_LOG("psQos->ucMaxBitRateForUpExt not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}

/*****************************************************************************
 函 数 名  : Aps_QosValidOrNot_ForGuarantBitRateForUpExt
 功能描述  : Guaranteed bitrate for downlink(extended)合法性校验(Aps_QosValidOrNot降圈复杂度)
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2011年06月01日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011052605913,[B052]UE对PDP激活接受消息检查过严
                 当Guaranteed bit rate for downlink为reserved 255(0xFF)时，PDP激活失败
*****************************************************************************/
VOS_UINT32 Aps_QosValidOrNot_ForGuarantBitRateForUpExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* 不属于闭区间[0, 250](R7版本区间为[0, 250])*/
    if(psQos->ucGuarantBitRateForUpExt > APS_3GPP_GUARANT_BITRATE_UP_TOP)
    {
        APS_WARN_LOG("psQos->ucGuarantBitRateForUpExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucGuarantBitRateForUpExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucGuarantBitRateForUp))
        {
            APS_WARN_LOG("psQos->ucGuarantBitRateForUpExt not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : Aps_QosValidOrNot
 功能描述  : 检查QOS Parameter 是否合法。QOS各 Parameter 的取值见10.5.6.5/24008
 输入参数  : psQos
 输出参数  :
 返 回 值  : TAF_APS_SUCC, QOS合法
             TAF_APS_FAIL,程序执行 error , 或QOS非法。
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月14日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2011年5月19日
    作    者   : o00132663
    修改内容   : 根据问题单号：DTS2011051801887,网侧下发PDP_ACTIVATE_ACCEPT
                 消息中的QOS IE为reserved “0”，PDP激活失败
  3.日    期   : 2011年06月01日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011052605913,[B052]UE对PDP激活接受消息检查过严
                 当Guaranteed bit rate for downlink为reserved 255(0xFF)时，PDP激活失败
*****************************************************************************/
VOS_UINT32 Aps_QosValidOrNot(
    APS_PDP_QOS_STRU                   *psQos
)
{
    /* ucDelayClass不属于闭区间[0, 4] */
    if ( (APS_3GPP_QOS_DELAYCLASS_BOT == psQos->ucDelayClass)
      || (psQos->ucDelayClass > APS_3GPP_QOS_DELAYCLASS_TOP) )
    {
        APS_NORM_LOG("psQos->ucDelayClass not valid , Aps_QosValidOrNot()");

        /*All other values are interpreted as Delay class 4 (best effort) in
        this version */
        psQos->ucDelayClass = APS_3GPP_QOS_DELAYCLASS_4;
    }

    /* ucReliabClass不属于闭区间[0, 5] */
    if ( (APS_3GPP_QOS_RELIABCLASS_BOT == psQos->ucReliabClass)
      || (psQos->ucReliabClass > APS_3GPP_QOS_RELIABCLASS_TOP) )
    {
        APS_NORM_LOG("psQos->ucReliabClass not valid , Aps_QosValidOrNot()");

        /*All other values are interpreted as Unacknowledged GTP and LLC;
        Acknowledged RLC, Protected data in this version of the protocol.*/
        psQos->ucReliabClass = APS_3GPP_QOS_RELIABCLASS_UNKGTPLLC_ACKRLC_PRODATA;
    }

    /* ucPeakThrough不属于闭区间[0, 9] */
    if ( (APS_3GPP_QOS_PEAKTHROUGH_BOT == psQos->ucPeakThrough)
      || (psQos->ucPeakThrough > APS_3GPP_QOS_PEAKTHROUGH_TOP) )
    {
        APS_NORM_LOG("psQos->ucPeakThrough not valid , Aps_QosValidOrNot()");

        /*All other values are interpreted as Up to 1 000 octet/s in this
        version of the protocol.*/
        psQos->ucPeakThrough = APS_3GPP_QOS_PEAKTHROUGH_1000_OCTPS;
    }

    /* ucPrecedenceClass不属于闭区间[0, 3] */
    if ( (APS_3GPP_QOS_PRECEDENCECLASS_BOT == psQos->ucPrecedenceClass)
      || (psQos->ucPrecedenceClass > APS_3GPP_QOS_PRECEDENCECLASS_TOP) )
    {
        APS_NORM_LOG("psQos->ucPrecedenceClass not valid , Aps_QosValidOrNot()");

        /*自动转换为 Normal priority*/
        psQos->ucPrecedenceClass = APS_3GPP_QOS_PRECEDENCECLASS_NORMPRI;
    }

    /* 不属于闭区间[0,18]*/
    if ( (APS_3GPP_QOS_MEANTHROUGH_BOT == psQos->ucMeanThrough)
      || ( (psQos->ucMeanThrough > APS_3GPP_QOS_MEANTHROUGH_TOP)
        && (APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT != psQos->ucMeanThrough) ) )
    {
        APS_NORM_LOG("psQos->ucMeanThrough not valid , Aps_QosValidOrNot()");

        /*自动转换为 Best effort*/
        psQos->ucMeanThrough = APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT;
    }

    /* 不属于闭区间[0, 4]*/
    if (psQos->ucTrafficClass > APS_3GPP_QOS_TRAFFICCLASS_TOP)
    {
        APS_WARN_LOG("psQos->ucTrafficClass not valid , Aps_QosValidOrNot()");
        /* The network shall map all other values not explicitly defined onto one
           of the values defined in this version of the protocol */
    }

    /*  不属于闭区间[0,3]*/
    if (psQos->ucDeliverOrder > APS_3GPP_QOS_DELIVERORDER_TOP)
    {
        APS_WARN_LOG("psQos->ucDeliverOrder not valid , Aps_QosValidOrNot()");
    }

    /* 不属于闭区间[0, 3]*/
    if (psQos->ucDeliverOfErrSdu > APS_3GPP_QOS_DELIVER_ERRSDU_TOP)
    {
        APS_WARN_LOG("psQos->ucDeliverOfErrSdu not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* ucMaximSduSize不属于闭区间[0, 153] */
    if (psQos->ucMaximSduSize > APS_3GPP_QOS_MAXSDUSIZE_TOP)
    {
        APS_WARN_LOG("psQos->ucMaximSduSize not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* 不属于闭区间[0, 9]*/
    if (psQos->ucResidualBer > APS_3GPP_QOS_RESIDUALBER_TOP)
    {
        APS_WARN_LOG("psQos->ucResidualBer not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* 不属于闭区间[0, 7]*/
    if (psQos->ucSduErrRatio > APS_3GPP_QOS_SDUERRRATIO_TOP)
    {
        APS_WARN_LOG("psQos->ucSduErrRatio not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* 不属于闭区间[0,0x3E]*/
    /* The Transfer delay value is ignored if the Traffic Class is interactive
       class or Background class. */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE != psQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND  != psQos->ucTrafficClass)
      && (psQos->ucTransDelay > APS_3GPP_QOS_TRANSDELAY_TOP) )
    {
        APS_WARN_LOG("psQos->ucTransDelay not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* The Traffic handling priority value is ignored if the Traffic Class is
       Conversational class,Streaming class or Background class */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE == psQos->ucTrafficClass) )
    {
        if (TAF_APS_SUCC != MN_APS_QosValidOrNot_ForTrafficHandlingPriority(psQos))
        {
            return (TAF_APS_FAIL);
        }
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForSrcStatisticsDescriptor(psQos))
    {
        return(TAF_APS_FAIL);
    }

    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForSignallingIndication(psQos))
    {
        return(TAF_APS_FAIL);
    }

    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForMaxBitRateForDownExt(psQos))
    {
        return(TAF_APS_FAIL);
    }

    /* The Guaranteed bit rate for downlink value is ignored
       if the Traffic Class is Interactive class or Background class,
       or Maximum bit rate for uplink is set to 0 kbps. */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE != psQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND  != psQos->ucTrafficClass)
      && (0xFF != psQos->ucMaxBitRateForDown) )
    {
        if (TAF_APS_SUCC != Aps_QosValidOrNot_ForGuarantBitRateForDownExt(psQos))
        {
            return TAF_APS_FAIL;
        }
    }
    #endif

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForMaxBitRateForUpExt(psQos))
    {
        return(TAF_APS_FAIL);
    }

    /* The Guaranteed bit rate for uplink value is ignored
       if the Traffic Class is Interactive class or Background class,
       or Maximum bit rate for uplink is set to 0 kbps. */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE != psQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND  != psQos->ucTrafficClass)
      && (0xFF != psQos->ucMaxBitRateForUp) )
    {
        if (TAF_APS_SUCC != Aps_QosValidOrNot_ForGuarantBitRateForUpExt(psQos))
        {
            return TAF_APS_FAIL;
        }
    }
    #endif

    return(TAF_APS_SUCC);
}


/*****************************************************************************
 Prototype      : Aps_PackSmPco
 Description    : 打包SM需要的PCO信息，包括LCP，AUTH，IPCP(DNS)
 Input          :
 Output         :
 Return Value   :
 Data Accessed  :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Aps_PackSmPco(
    APS_PDP_ACT_REQ_ST                 *pActReq,
    SM_TAF_PROT_CFG_OPT_STRU           *pSmPco
)
{
    VOS_UINT8                          *pPcoCur;

    if ((VOS_NULL_PTR == pActReq) || (VOS_NULL_PTR == pSmPco))
    {
        APS_WARN_LOG("ERROR! The Input can not be NULL !");
        return VOS_ERR;
    }

    /*打包PCO的IE中的第3个字节-- 1 0000 Configuration protocol(PPP for IP PDP type)
      0x80                    -- 1 0000 000    */
    pSmPco->aucProtCfgOpt[0]        = 0x80;

    pPcoCur                         = &pSmPco->aucProtCfgOpt[1];


    /*打包LCP*/

    /*打包AUTH*/
    pPcoCur                         = Aps_PackPcoAuth(pActReq, pPcoCur);

    /*打包IPCP*/
#if (FEATURE_ON == FEATURE_IPV6)
    if (MN_APS_ADDR_IPV6 != pActReq->ucPdpType)
    {
        pPcoCur = Aps_PackPcoIpcp(pActReq, pPcoCur);
        if (VOS_NULL_PTR == pPcoCur)
        {
            MN_ERR_LOG("Aps_PackSmPco: Fill IPCP parameter failed!");
            return VOS_ERR;
        }
    }

    if ( (MN_APS_ADDR_IPV6   == pActReq->ucPdpType)
      || (MN_APS_ADDR_IPV4V6 == pActReq->ucPdpType) )
    {
        pPcoCur = MN_APS_FillPcoIpV6DnsPara(pPcoCur);
        if (VOS_NULL_PTR == pPcoCur)
        {
            MN_ERR_LOG("Aps_PackSmPco: Fill IPV6 DNS parameter failed!");
            return VOS_ERR;
        }
    }
#else
    pPcoCur = Aps_PackPcoIpcp(pActReq, pPcoCur);
    if (VOS_NULL_PTR == pPcoCur)
    {
        MN_ERR_LOG("Aps_PackSmPco: Fill IPCP parameter failed!");
        return VOS_ERR;
    }
#endif

    /*最后填写 pSmPco->ulCnt */
    pSmPco->ulPcoLen = (VOS_UINT32)(pPcoCur - pSmPco->aucProtCfgOpt);

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : Aps_PackPcoAuth
 Description    : 打包SM需要的PCO信息中的AUTH
 Input          : ApsAuthPara
                  pPcoAuthStart, 放置AUTH信息的第一个字节的地址
 Output         :
 Return Value   : 放置AUTH信息的最后一个字节的地址+1, 即将放置下一个IE的第一个
                  字节
 Data Accessed  :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_UINT8  *Aps_PackPcoAuth(            APS_PDP_ACT_REQ_ST     *pActReq,
                                        VOS_UINT8              *pPcoAuthBegin)
{
    VOS_UINT8                          *pAuthCurLoc;
    VOS_UINT8                          *pProPapCntLenLoc;
    VOS_UINT8                          *pInPapLenLoc;
    VOS_UINT8                           ucPapLen;
    VOS_UINT8                           ucStrLen;
    VOS_UINT8                           i;

    TAF_PDP_PCO_AUTH_STRU              *pApsAuthPara;

    if (VOS_TRUE != pActReq->OP_AUTH)
    {
        return pPcoAuthBegin;
    }

    pApsAuthPara                        = &(pActReq->PdpAuth);

    pAuthCurLoc                         = pPcoAuthBegin;

    if ( TAF_PCO_AUTH_PAP == pApsAuthPara->AuthType )
    {
        /*lint -e961*/
        /*PAP认证方式*/
        /* Password Authentication Protocol */
        *pAuthCurLoc++ = 0xC0;
        *pAuthCurLoc++ = 0x23;

        /* 暂时不填 PROTOCAL ID1的长度, 记住索引地址, 填完下面所有信息后再填*/
        pProPapCntLenLoc                    = pAuthCurLoc++;

        /* code (Authenticate-Request) */
        *pAuthCurLoc++ = 0x01;

        /* Identifier */
        *pAuthCurLoc++ = 0x00;

        /* 暂时不填PAP内容的Length, 占2个字节, 记住索引地址, 填完下面所有信息后再填 */
        pInPapLenLoc                        = pAuthCurLoc++;
        pAuthCurLoc++;

        /*如果输入了AUTH信息，则填写输入的用户名和密码信息*/

        /* Peer-ID Length */
        *pAuthCurLoc++                  = pApsAuthPara->AuthContent.stPap.aucUserName[0];

        /* Peer-Id  */
        ucStrLen                        = pApsAuthPara->AuthContent.stPap.aucUserName[0];
        if ( ucStrLen > TAF_MAX_USERNAME_LEN)
        {
            ucStrLen                    = TAF_MAX_USERNAME_LEN;
        }
        if ( 0 != ucStrLen)
        {
            for(i = 1; i <= ucStrLen; i++)
            {
                *pAuthCurLoc++          = pApsAuthPara->AuthContent.stPap.aucUserName[i];
            }
        }

        /* Passwd-Length  */
        *pAuthCurLoc++                  = pApsAuthPara->AuthContent.stPap.aucPassword[0];

        /* Password-ID  */
        ucStrLen                        = pApsAuthPara->AuthContent.stPap.aucPassword[0];
        if ( ucStrLen > TAF_MAX_PASSCODE_LEN)
        {
            ucStrLen                    = TAF_MAX_PASSCODE_LEN;
        }
        if ( 0 != ucStrLen)
        {
            for(i = 1; i <= ucStrLen; i++)
            {
                *pAuthCurLoc++          = pApsAuthPara->AuthContent.stPap.aucPassword[i];
            }
        }

        /* PAP内容的Length */
        ucPapLen                            = (VOS_UINT8)((pAuthCurLoc
                                              - pPcoAuthBegin)
                                              - APS_PAP_PIDOCTS_AND_LENOCT_LEN);
        /* PROTOCAL ID1的长度 */
       *pProPapCntLenLoc                    = ucPapLen;

        /* PAP内容的Length, 占2个字节 */
       *pInPapLenLoc++                      = 0;
       *pInPapLenLoc                        = ucPapLen;
    }
    else if ( TAF_PCO_AUTH_CHAP == pApsAuthPara->AuthType )
    {
        /*CHAP认证方式*/
        /* Challenge 报文 */
        *pAuthCurLoc++ = 0xC2;
        *pAuthCurLoc++ = 0x23;

        /*Length of Challenge contents: 长度固定*/
        *pAuthCurLoc++ = pApsAuthPara->AuthContent.stChap.aucChallenge[0];

        /*Challenge contents*/
        PS_MEM_CPY(pAuthCurLoc,
                   &pApsAuthPara->AuthContent.stChap.aucChallenge[1],
                   pApsAuthPara->AuthContent.stChap.aucChallenge[0]);

        pAuthCurLoc += pApsAuthPara->AuthContent.stChap.aucChallenge[0];

        /* Response 报文 */
        *pAuthCurLoc++ = 0xC2;
        *pAuthCurLoc++ = 0x23;

        /*Length of Response contents */
        /*Response contents包括固定长度为21的头+user，如果user>106，认为AUTH无效*/
        if ((pApsAuthPara->AuthContent.stChap.aucResponse[0] - TAF_PCO_AUTH_CHAP_RESPONSE_HEAD_LEN)
            > TAF_PCO_AUTH_CHAP_RESPONSE_CONTENT_LEN)
        {
            return pPcoAuthBegin;
        }

        *pAuthCurLoc++ = pApsAuthPara->AuthContent.stChap.aucResponse[0];
        /*lint +e961*/

        /*Challenge contents*/
        PS_MEM_CPY(pAuthCurLoc,
                   &pApsAuthPara->AuthContent.stChap.aucResponse[1],
                   pApsAuthPara->AuthContent.stChap.aucResponse[0]);

        pAuthCurLoc += pApsAuthPara->AuthContent.stChap.aucResponse[0];

    }
    else
    {
        /*无需认证，直接返回*/
    }

    return  pAuthCurLoc;
}

/*****************************************************************************
 Prototype      : Aps_PackPcoIpcp
 Description    : 打包SM需要的PCO信息中的IPCP
 Input          :
 Output         :
 Return Value   : 放置AUTH信息的最后一个字节的地址+1, 即将放置下一个IE的第一个
                  字节
 Data Accessed  :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : 韩鲁峰
    Modification: Created function
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，DNS和NBNS结构变换
*****************************************************************************/
VOS_UINT8  *Aps_PackPcoIpcp(            APS_PDP_ACT_REQ_ST     *pActReq,
                                        VOS_UINT8              *pPcoIpcpBegin)
{
    VOS_UINT8                          *pIpcpCurLoc;
    VOS_UINT8                          *pProIpcpCntLenLoc;
    VOS_UINT8                          *pInIpcpLenLoc;
    VOS_UINT8                           ucIpcpLen;


    pIpcpCurLoc                         = pPcoIpcpBegin;

    /*lint -e961*/
    /* IPCP Protocol */
    *pIpcpCurLoc++                      = 0x80;
    *pIpcpCurLoc++                      = 0x21;

    /* 暂时不填 PROTOCAL ID1的长度, 记住索引地址, 填完下面所有信息后再填*/
    pProIpcpCntLenLoc                   = pIpcpCurLoc++;

    /* code (Authenticate-Request) */
    *pIpcpCurLoc++                      = 0x01;

    /* Identifier */
    *pIpcpCurLoc++                      = 0x00;

    /* 暂时不填IPCP内容的Length, 占2个字节, 记住索引地址, 填完下面所有信息
    后再填 */
    pInIpcpLenLoc                       = pIpcpCurLoc++;
    pIpcpCurLoc++;


    /*主DNS*/
    *pIpcpCurLoc++                      = 0x81;             /*PriDns*/
    *pIpcpCurLoc++                      = 0x06;             /*长度*/

    if ( (pActReq->OP_DNS) && (pActReq->PdpDns.bitOpPrimDnsAddr) )
    {
        PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpDns.aucPrimDnsAddr, TAF_IPV4_ADDR_LEN);
        pIpcpCurLoc                    += 4;                /*DNS为4个字节*/
    }
    else
    {
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
    }

    if (WINS_CONFIG_ENABLE == g_ApsWins)
    {
        /*主NBNS*/
        if ( (pActReq->OP_NBNS) && (pActReq->PdpNbns.bitOpPrimNbnsAddr) )
        {
            *pIpcpCurLoc++              = APS_PPP_PRI_NBNS_ID;     /*PriNbns*/
            *pIpcpCurLoc++              = 0x06;             /*长度*/

            PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpNbns.aucPrimNbnsAddr, TAF_IPV4_ADDR_LEN);
            pIpcpCurLoc                    += 4;                /*NBNS为4个字节*/
        }
    }

    /*副DNS*/
    *pIpcpCurLoc++                      = 0x83;             /*SecDns*/
    *pIpcpCurLoc++                      = 0x06;             /*长度*/

    if ( (pActReq->OP_DNS) && (pActReq->PdpDns.bitOpSecDnsAddr) )
    {
        PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpDns.aucSecDnsAddr, TAF_IPV4_ADDR_LEN);
        pIpcpCurLoc                    += 4;                /*DNS为4个字节*/
    }
    else
    {
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
    }


    if (WINS_CONFIG_ENABLE == g_ApsWins)
    {
        /*副NBNS*/
        if ( (pActReq->OP_NBNS) && (pActReq->PdpNbns.bitOpSecNbnsAddr) )
        {
            *pIpcpCurLoc++              = APS_PPP_SEC_NBNS_ID;      /*SecNbns*/
            *pIpcpCurLoc++              = 0x06;                     /*长度*/

            PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpNbns.aucSecNbnsAddr, TAF_IPV4_ADDR_LEN);
            pIpcpCurLoc                    += 4;                    /*NBNS为4个字节*/
        }
    }

    ucIpcpLen                           = (VOS_UINT8)((pIpcpCurLoc
                                          - pPcoIpcpBegin)
                                          - APS_PAP_PIDOCTS_AND_LENOCT_LEN);
    /* PROTOCAL ID1的长度 */
    *pProIpcpCntLenLoc                  = ucIpcpLen;

    /* PAP内容的Length, 占2个字节 */
    *pInIpcpLenLoc++                    = 0;
    *pInIpcpLenLoc                      = ucIpcpLen;
    /*lint +e961*/
    return  pIpcpCurLoc;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : MN_APS_FillPcoIpV6DnsPara
 功能描述  : 填写PCO信息DNS Server IPV6 Address
 输入参数  : pucPcoPkt - PCO Packet地址
 输出参数  : 无
 返 回 值  : VOS_UINT8*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月1日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年4月21日
    作    者   : A00165503
    修改内容   : DTS2012042100658: IPv6拨号无法获取辅DNS Server IPv6地址
*****************************************************************************/
VOS_UINT8* MN_APS_FillPcoIpV6DnsPara(
    VOS_UINT8                          *pucPcoPkt
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucIPv6DnsAddrNum;

    /* 目前支持获取的DNS Server IPv6 Address个数为2 */
    ucIPv6DnsAddrNum = 2;

    for (i = 0; i < ucIPv6DnsAddrNum; i++)
    {
        /*--------------------------------------------------
           填写Protocol identifier (2 octets)
           0003H (DNS Server IPV6 Address Request)
        --------------------------------------------------*/
        /*lint -e961*/
        *pucPcoPkt++ = 0x00;
        *pucPcoPkt++ = 0x03;

        /*----------------------------------------------------------------------
           填写Length of the protocol identifier contents of the unit (1 octet)
        ----------------------------------------------------------------------*/
        *pucPcoPkt++ = 0;
        /*lint +e961*/
    }

    return pucPcoPkt;

}
#endif

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
