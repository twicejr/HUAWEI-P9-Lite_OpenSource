/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregMntn.c
  版 本 号   : 初稿
  作    者   : d00212987
  生成日期   : 2015年10月23日
  功能描述   : 1X REG(register)发给Mntn的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月23日
    作    者   : d00212987
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsLogdef.h"
#include  "CnasXregCtx.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"
#include  "CnasXregMntn.h"
#include  "CnasXregListProc.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

extern CNAS_XREG_ZONE_NODE_STRU         *g_pstCnasXregCurrZoneNode;
extern CNAS_XREG_SIDNID_NODE_STRU       *g_pstCnasXregCurrSidNidNode;
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XREG_TransferRegType
 功能描述  : 将注册类型转换为可维可测的类型
 输入参数  : enRegType: 原始注册类型
 输出参数  : 无
 返 回 值  : NAS_OM_CDMA_REG_TYPE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
NAS_OM_CDMA_REG_TYPE_ENUM_UINT32 CNAS_XREG_TransferRegType(
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8                enRegType
)
{
    NAS_OM_CDMA_REG_TYPE_ENUM_UINT32    enRegTypeMntn = NAS_OM_CDMA_REG_MODE_BUTT;

    switch (enRegType)
    {
        case CAS_CNAS_1X_TIMER_BASED_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_TIMER_BASED_REGISTRATION;
            break;

        case CAS_CNAS_1X_POWER_UP_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_POWER_UP_REGISTRATION;
            break;

        case CAS_CNAS_1X_ZONE_BASED_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_ZONE_BASED_REGISTRATION;
            break;

        case CAS_CNAS_1X_POWER_DOWN_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_POWER_DOWN_REGISTRATION;
            break;

        case CAS_CNAS_1X_PARAMETER_CHANGED_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_PARAMETER_CHANGED_REGISTRATION;
            break;

        case CAS_CNAS_1X_ORDERED_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_ORDERED_REGISTRATION;
            break;

        case CAS_CNAS_1X_DISTANCE_BASED_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_DISTANCE_BASED_REGISTRATION;
            break;

        case CAS_CNAS_1X_USER_ZONE_BASED_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_USER_ZONE_BASED_REGISTRATION;
            break;

        case CAS_CNAS_1X_ENCRYPTION_RE_SYNC_REQUIRED_REGISTRATION:
            enRegTypeMntn = NAS_OM_CDMA_ENCRYPTION_RE_SYNC_REQUIRED_REGISTRATION;
            break;

        default:
            break;
    }

    return enRegTypeMntn;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndOmRegReportCnf
 功能描述  : XREG模块发送给OM回复请求消息
 输入参数  : enResult: 消息处理结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndOmRegReportCnf(
    NAS_OM_RESULT_ENUM_UINT32               enResult,
    OM_NAS_CDMA_REG_INFO_REPORT_REQ_STRU   *pstMsg
)
{
    NAS_OM_CDMA_REG_INFO_REPORT_CNF_STRU   *pstSndMsg;

    pstSndMsg = (NAS_OM_CDMA_REG_INFO_REPORT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         UEPS_PID_XREG,
                                         sizeof(NAS_OM_CDMA_REG_INFO_REPORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        return ;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(NAS_OM_CDMA_REG_INFO_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSn                     = pstMsg->ulSn;
    pstSndMsg->ulTimeStamp              = pstMsg->ulTimeStamp;
    pstSndMsg->usOriginalId             = pstMsg->usOriginalId;
    pstSndMsg->usTerminalId             = pstMsg->usTerminalId;

    pstSndMsg->ulReceiverPid            = MSP_PID_DIAG_APP_AGENT;
    pstSndMsg->ulMsgId                  = ID_NAS_OM_CDMA_REG_INFO_REPORT_CNF;
    pstSndMsg->enResult                 = enResult;

    PS_SEND_MSG(UEPS_PID_XREG, pstSndMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndOmRegPRDReportInd
 功能描述  : XREG模块给OM上报周期性注册时长
 输入参数  : enResult: 消息处理结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndOmRegPRDReportInd(
    VOS_UINT8                               ucRegPeriod
)
{
    NAS_OM_CDMA_REG_PRD_REPORT_IND_STRU           *pstSndInfoInd;
    DIAG_TRANS_IND_STRU                            stIndMsg;

    if (NAS_OM_REPORT_START != CNAS_XREG_GetOmRegReportFlag())
    {
        return;
    }

    pstSndInfoInd = (NAS_OM_CDMA_REG_PRD_REPORT_IND_STRU*)PS_MEM_ALLOC(
                                         UEPS_PID_XREG,
                                         sizeof(NAS_OM_CDMA_REG_PRD_REPORT_IND_STRU));
    if (VOS_NULL_PTR == pstSndInfoInd)
    {
        return ;
    }

    /*初始化参数*/
    PS_MEM_SET(pstSndInfoInd, 0X00, sizeof(NAS_OM_CDMA_REG_PRD_REPORT_IND_STRU));

    pstSndInfoInd->usToolsId                = 0;
    pstSndInfoInd->usPrimId                 = ID_NAS_OM_CDMA_REG_PRD_REPORT_IND;
    pstSndInfoInd->ulRegPrd                 = ((CNAS_XREG_GetCountMax(ucRegPeriod) * CNAS_XREG_MS_PER_COUNT) / 1000); /* 转换为秒 */

    stIndMsg.ulPid      = UEPS_PID_XREG;
    stIndMsg.ulLength   = sizeof(NAS_OM_CDMA_REG_PRD_REPORT_IND_STRU);
    stIndMsg.ulModule   = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(UEPS_PID_XREG), DIAG_MODE_COMM);
    stIndMsg.ulMsgId    = ID_NAS_OM_CDMA_REG_PRD_REPORT_IND;
    stIndMsg.pData      = (VOS_VOID*)pstSndInfoInd;

    (VOS_VOID)DIAG_TransReport(&stIndMsg);

    PS_MEM_FREE(UEPS_PID_XREG, pstSndInfoInd);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndOmRegTypeReportInd
 功能描述  : XREG模块给OM上报注册类型
 输入参数  : enResult: 消息处理结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndOmRegTypeReportInd(
    NAS_OM_CDMA_REG_TYPE_ENUM_UINT32               enRegType
)
{
    NAS_OM_CDMA_REG_TYPE_REPORT_IND_STRU          *pstSndInfoInd;
    DIAG_TRANS_IND_STRU                            stIndMsg;

    if (NAS_OM_REPORT_START != CNAS_XREG_GetOmRegReportFlag())
    {
        return;
    }

    pstSndInfoInd = (NAS_OM_CDMA_REG_TYPE_REPORT_IND_STRU*)PS_MEM_ALLOC(
                                         UEPS_PID_XREG,
                                         sizeof(NAS_OM_CDMA_REG_TYPE_REPORT_IND_STRU));
    if (VOS_NULL_PTR == pstSndInfoInd)
    {
        return ;
    }

    /*初始化参数*/
    PS_MEM_SET(pstSndInfoInd, 0X00, sizeof(NAS_OM_CDMA_REG_TYPE_REPORT_IND_STRU));

    pstSndInfoInd->usToolsId                = 0;
    pstSndInfoInd->usPrimId                 = ID_NAS_OM_CDMA_REG_TYPE_REPORT_IND;
    pstSndInfoInd->enRegType                = enRegType;

    stIndMsg.ulPid    = UEPS_PID_XREG;
    stIndMsg.ulLength = sizeof(NAS_OM_CDMA_REG_TYPE_REPORT_IND_STRU);
    stIndMsg.ulModule = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(UEPS_PID_XREG), DIAG_MODE_COMM);
    stIndMsg.ulMsgId  = ID_NAS_OM_CDMA_REG_TYPE_REPORT_IND;
    stIndMsg.pData    = (VOS_VOID*)pstSndInfoInd;

    (VOS_VOID)DIAG_TransReport(&stIndMsg);

    PS_MEM_FREE(UEPS_PID_XREG, pstSndInfoInd);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndOmRegListReportInd
 功能描述  : XREG模块给OM上报注册列表(包含 SID NID ZONE)
 输入参数  : enResult: 消息处理结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndOmRegListReportInd(VOS_VOID)
{
    NAS_OM_CDMA_REG_LIST_REPORT_IND_STRU           *pstSndInfoInd;
    DIAG_TRANS_IND_STRU                             stIndMsg;
    HI_LIST_S                                      *pstListHeader;
    HI_LIST_S                                      *pstIndexNode;
    HI_LIST_S                                      *pstTempNode;
    CNAS_XREG_ZONE_NODE_STRU                       *pstIndexZoneNode;
    CNAS_XREG_SIDNID_NODE_STRU                     *pstIndexSidNidNode;
    VOS_UINT32                                      ulSidNidIndex = 0;
    VOS_UINT32                                      ulZoneIndex  = 0;
    VOS_UINT32                                      i;

    if (NAS_OM_REPORT_START != CNAS_XREG_GetOmRegReportFlag())
    {
        return;
    }

    pstSndInfoInd = (NAS_OM_CDMA_REG_LIST_REPORT_IND_STRU*)PS_MEM_ALLOC(
                                         UEPS_PID_XREG,
                                         sizeof(NAS_OM_CDMA_REG_LIST_REPORT_IND_STRU));
    if (VOS_NULL_PTR == pstSndInfoInd)
    {
        return ;
    }

    /*初始化参数*/
    PS_MEM_SET(pstSndInfoInd, 0X00, sizeof(NAS_OM_CDMA_REG_LIST_REPORT_IND_STRU));

    pstSndInfoInd->usToolsId                = 0;
    pstSndInfoInd->usPrimId                 = ID_NAS_OM_CDMA_REG_LIST_REPORT_IND;

    /* ZONE LIST*/
    if (VOS_NULL_PTR != g_pstCnasXregCurrZoneNode)
    {
        pstSndInfoInd->astZoneList[ulZoneIndex].usRegZone   = g_pstCnasXregCurrZoneNode->usRegZone;
        pstSndInfoInd->astZoneList[ulZoneIndex].usSid       = g_pstCnasXregCurrZoneNode->usSid;
        pstSndInfoInd->astZoneList[ulZoneIndex].usNid       = g_pstCnasXregCurrZoneNode->usNid;
        pstSndInfoInd->astZoneList[ulZoneIndex].enBlkSys    = g_pstCnasXregCurrZoneNode->enBlkSys;
        pstSndInfoInd->astZoneList[ulZoneIndex].usBandClass = g_pstCnasXregCurrZoneNode->usBandClass;

        ulZoneIndex++;
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_ZONE_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexZoneNode = msp_list_entry(pstIndexNode, CNAS_XREG_ZONE_NODE_STRU, stListNode);

        PS_MEM_CPY(&(pstSndInfoInd->astZoneList[ulZoneIndex]),
                   pstIndexZoneNode,
                   sizeof(CNAS_XREG_ZONE_NODE_STRU));

        pstSndInfoInd->astZoneList[ulZoneIndex].usRegZone   = pstIndexZoneNode->usRegZone;
        pstSndInfoInd->astZoneList[ulZoneIndex].usSid       = pstIndexZoneNode->usSid;
        pstSndInfoInd->astZoneList[ulZoneIndex].usNid       = pstIndexZoneNode->usNid;
        pstSndInfoInd->astZoneList[ulZoneIndex].enBlkSys    = pstIndexZoneNode->enBlkSys;
        pstSndInfoInd->astZoneList[ulZoneIndex].usBandClass = pstIndexZoneNode->usBandClass;

        ulZoneIndex++;
    }

    for (i = ulZoneIndex; i < NAS_OM_CDMA_ZONE_NODE_MAX_NUM; i++)
    {
        pstSndInfoInd->astZoneList[i].enBlkSys = NAS_OM_CDMA_BLKSYS_BUTT;
    }

    /* SID NDI IST*/
    ulSidNidIndex = 0;
    if (VOS_NULL_PTR != g_pstCnasXregCurrSidNidNode)
    {
        pstSndInfoInd->astSidNidList[ulSidNidIndex].usSid       = g_pstCnasXregCurrSidNidNode->usSid;
        pstSndInfoInd->astSidNidList[ulSidNidIndex].usNid       = g_pstCnasXregCurrSidNidNode->usNid;
        pstSndInfoInd->astSidNidList[ulSidNidIndex].enBlkSys    = g_pstCnasXregCurrSidNidNode->enBlkSys;
        pstSndInfoInd->astSidNidList[ulSidNidIndex].usBandClass = g_pstCnasXregCurrSidNidNode->usBandClass;
        ulSidNidIndex++;
    }

    pstListHeader = CNAS_XREG_GetListHeader(CNAS_XREG_SIDNID_USED_LIST_ID);

    msp_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstIndexSidNidNode = msp_list_entry(pstIndexNode, CNAS_XREG_SIDNID_NODE_STRU, stListNode);

        pstSndInfoInd->astSidNidList[ulSidNidIndex].usSid       = pstIndexSidNidNode->usSid;
        pstSndInfoInd->astSidNidList[ulSidNidIndex].usNid       = pstIndexSidNidNode->usNid;
        pstSndInfoInd->astSidNidList[ulSidNidIndex].enBlkSys    = pstIndexSidNidNode->enBlkSys;
        pstSndInfoInd->astSidNidList[ulSidNidIndex].usBandClass = pstIndexSidNidNode->usBandClass;
    }

    for (i = ulSidNidIndex; i < NAS_OM_CDMA_SIDNID_NODE_MAX_NUM; i++)
    {
        pstSndInfoInd->astSidNidList[i].enBlkSys = NAS_OM_CDMA_BLKSYS_BUTT;
    }

    if (0 < (ulSidNidIndex + ulZoneIndex))
    {
        stIndMsg.ulPid    = UEPS_PID_XREG;
        stIndMsg.ulLength = sizeof(NAS_OM_CDMA_REG_LIST_REPORT_IND_STRU);
        stIndMsg.ulModule = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(UEPS_PID_XREG), DIAG_MODE_COMM);
        stIndMsg.ulMsgId  = ID_NAS_OM_CDMA_REG_LIST_REPORT_IND;
        stIndMsg.pData    = (VOS_VOID*)pstSndInfoInd;

        (VOS_VOID)DIAG_TransReport(&stIndMsg);
    }

    PS_MEM_FREE(UEPS_PID_XREG, pstSndInfoInd);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



