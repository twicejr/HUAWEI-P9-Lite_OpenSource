

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtCmdImsProc.h"
#include "ATCmdProc.h"

#include "AtDataProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_IMS_PROC_C
/*lint +e767 +e960*/

#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*AT与IMSA模块间消息处理函数指针*/
const AT_IMSA_MSG_PRO_FUNC_STRU g_astAtImsaMsgTab[]=
{
    /* 消息ID */                            /* 消息处理函数 */
    {ID_IMSA_AT_CIREG_SET_CNF,              AT_RcvImsaCiregSetCnf},
    {ID_IMSA_AT_CIREG_QRY_CNF,              AT_RcvImsaCiregQryCnf},
    {ID_IMSA_AT_CIREP_SET_CNF,              AT_RcvImsaCirepSetCnf},
    {ID_IMSA_AT_CIREP_QRY_CNF,              AT_RcvImsaCirepQryCnf},
    {ID_IMSA_AT_VOLTEIMPU_QRY_CNF,          AT_RcvImsaImpuSetCnf},
    {ID_IMSA_AT_CIREGU_IND,                 AT_RcvImsaCireguInd},
    {ID_IMSA_AT_CIREPH_IND,                 AT_RcvImsaCirephInd},
    {ID_IMSA_AT_CIREPI_IND,                 AT_RcvImsaCirepiInd},
    {ID_IMSA_AT_CCWAI_SET_CNF,              AT_RcvImsaCcwaiSetCnf},
    {ID_IMSA_AT_VT_PDP_ACTIVATE_IND,        AT_RcvImsaVtPdpActInd},
    {ID_IMSA_AT_VT_PDP_DEACTIVATE_IND,      AT_RcvImsaVtPdpDeactInd},
    {ID_IMSA_AT_MT_STATES_IND,              AT_RcvImsaMtStateInd},
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : AT_ProcImsaMsg
 功能描述  : 处理来自IMSA模块的消息
 输入参数  : AT_IMSA_MSG_STRU *pMsg
 输出参数  : 无
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID AT_ProcImsaMsg(AT_IMSA_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*从g_astAtProcMsgFromImsaTab中获取消息个数*/
    ulMsgCnt = sizeof(g_astAtImsaMsgTab)/sizeof(AT_IMSA_MSG_PRO_FUNC_STRU);

    /*从消息包中获取MSG ID*/
    ulMsgId  = pstMsg->ulMsgId;

    /*g_astAtProcMsgFromImsaTab查表，进行消息分发*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtImsaMsgTab[i].ulMsgId == ulMsgId)
        {
            ulRst = g_astAtImsaMsgTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("AT_ProcImsaMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*没有找到匹配的消息*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("AT_ProcImsaMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCiregSetCnf
 功能描述  : +CIREG设置命令回复处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCiregSetCnf(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CIREG_SET_CNF_STRU         *pstCiregCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstCiregCnf = (IMSA_AT_CIREG_SET_CNF_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCiregCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCiregSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCiregSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CIREG_SET */
    if ( AT_CMD_CIREG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCiregSetCnf: WARNING:Not AT_CMD_CIREG_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( VOS_OK == pstCiregCnf->ulResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCiregQryCnf
 功能描述  : +CIREG查询命令回复处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCiregQryCnf(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CIREG_QRY_CNF_STRU         *pstCiregCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* 初始化消息变量 */
    ucIndex     = 0;
    usLength    = 0;
    pstCiregCnf = (IMSA_AT_CIREG_QRY_CNF_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCiregCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCiregQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCiregQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CIREG_QRY */
    if ( AT_CMD_CIREG_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCiregQryCnf: WARNING:Not AT_CMD_CIREG_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( VOS_OK == pstCiregCnf->ulResult )
    {

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: %d,",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstCiregCnf->enCireg);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                           "%d",
                                           pstCiregCnf->ulRegInfo);

        /* 如果IMS未注册，<ext_info>参数无意义，且不输出，详见3GPP 27007 v11 8.71 */
        if ((VOS_FALSE != pstCiregCnf->ulRegInfo) && (VOS_FALSE != pstCiregCnf->bitOpExtInfo))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                               ",%d",
                                               pstCiregCnf->ulExtInfo);
        }

        ulResult                = AT_OK;
    }
    else
    {
        ulResult                = AT_ERROR;
    }

    gstAtSendData.usBufLen  = usLength;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCirepSetCnf
 功能描述  : +CIREP设置命令回复处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirepSetCnf(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CIREP_SET_CNF_STRU         *pstCirepCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstCirepCnf = (IMSA_AT_CIREP_SET_CNF_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirepCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirepSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCirepSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CIREP_SET */
    if ( AT_CMD_CIREP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCirepSetCnf: WARNING:Not AT_CMD_CIREP_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( VOS_OK == pstCirepCnf->ulResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCirepQryCnf
 功能描述  : +CIREP查询命令回复处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirepQryCnf(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CIREP_QRY_CNF_STRU         *pstCirepCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstCirepCnf = (IMSA_AT_CIREP_QRY_CNF_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirepCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirepQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCirepQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CIREP_QRY */
    if ( AT_CMD_CIREP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCirepQryCnf: WARNING:Not AT_CMD_CIREP_QRY!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if ( VOS_OK == pstCirepCnf->ulResult )
    {

        gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d,%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       pstCirepCnf->enReport,
                                                       pstCirepCnf->enImsvops);

        ulResult                = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen  = 0;
        ulResult                = AT_ERROR;
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvImsaImpuSetCnf
 功能描述  : +CIREP查询命令回复处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月17日
    作    者   : c64416
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaImpuSetCnf(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_VOLTEIMPU_QRY_CNF_STRU      *pstImpuCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_CHAR                            acString[AT_IMSA_IMPU_MAX_LENGTH+1];

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstImpuCnf  = (IMSA_AT_VOLTEIMPU_QRY_CNF_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstImpuCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_IMPU_SET */
    if ( AT_CMD_IMPU_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:Not AT_CMD_IMPU_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    VOS_MemSet(acString, 0, sizeof(acString));
    if(pstImpuCnf->ulImpuLen > AT_IMSA_IMPU_MAX_LENGTH)
    {
        VOS_MemCpy(acString, pstImpuCnf->aucImpu, AT_IMSA_IMPU_MAX_LENGTH);
    }
    else
    {
        VOS_MemCpy(acString, pstImpuCnf->aucImpu, pstImpuCnf->ulImpuLen);
    }

    /* 判断查询操作是否成功 */
    if ( VOS_OK == pstImpuCnf->ulResult )
    {

        gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %s",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       acString);

        ulResult                = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen  = 0;
        ulResult                = AT_ERROR;
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCirephInd
 功能描述  : +CIREPH主动上报命令处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirephInd(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CIREPH_IND_STRU            *pstCirephInd;
    VOS_UINT8                           ucIndex;

    /* 初始化消息变量 */
    ucIndex      = 0;
    pstCirephInd = (IMSA_AT_CIREPH_IND_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirephInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirephInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 判断查询操作是否成功 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: %d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CIREPH].pucText,
                                                    pstCirephInd->enHandover,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCirepiInd
 功能描述  : +CIREPI主动上报命令处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirepiInd(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CIREPI_IND_STRU            *pstCirepiInd;
    VOS_UINT8                           ucIndex;

    /* 初始化消息变量 */
    ucIndex      = 0;
    pstCirepiInd = (IMSA_AT_CIREPI_IND_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirepiInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirepiInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 判断查询操作是否成功 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: %d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CIREPI].pucText,
                                                    pstCirepiInd->enImsvops,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCireguInd
 功能描述  : +CIREGU主动上报命令处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCireguInd(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CIREGU_IND_STRU            *pstCireguInd;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* 初始化消息变量 */
    ucIndex      = 0;
    usLength     = 0;
    pstCireguInd = (IMSA_AT_CIREGU_IND_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCireguInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCireguInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* 判断查询操作是否成功 */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s%s: %d",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_CIREGU].pucText,
                                       pstCireguInd->ulRegInfo);

    /* 如果IMS未注册，<ext_info>参数无意义 */
    if ((VOS_FALSE != pstCireguInd->ulRegInfo) && (VOS_FALSE != pstCireguInd->bitOpExtInfo))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstCireguInd->ulExtInfo);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaCcwaiSetCnf
 功能描述  : ^CCWAI设置命令回复处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : z00212940
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCcwaiSetCnf(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_CCWAI_SET_CNF_STRU          *pstCcwaiCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstCcwaiCnf = (IMSA_AT_CCWAI_SET_CNF_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCcwaiCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCcwaiSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_CCWAI_SET */
    if ( AT_CMD_CCWAI_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCcwaiSetCnf: WARNING:Not AT_CMD_CCWAI_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断设置操作是否成功 */
    if (VOS_OK == pstCcwaiCnf->ulResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaVtIpv4PdpActInd
 功能描述  : VT IPV4承载激活指示处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID AT_RcvImsaVtIpv4PdpActInd(
    VOS_UINT8                           ucIndex,
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd
)
{
    VOS_UINT32                          ulIPAddr;                               /* IP 地址，网侧分配*/
    VOS_UINT32                          ulSubNetMask;                           /* 子网掩码地址，根据IP地址计算*/
    VOS_UINT32                          ulGateWay;                              /* 网关地址，也是本DHCP Server的地址*/
    VOS_UINT32                          ulPrimDNS;                              /* 主 DNS地址，网侧分配*/
    VOS_UINT32                          ulSecDNS;                               /* 次 DNS地址，网侧分配*/

    ulIPAddr     = AT_GetLanAddr32(pstPdpActInd->stPdpAddr.aucIpv4Addr);
    ulSubNetMask = AT_DHCPGetIPMask(ulIPAddr);
    ulGateWay    = AT_DHCPGetGateWay(ulIPAddr, ulSubNetMask);
    ulPrimDNS    = 0;
    ulSecDNS     = 0;

    if (pstPdpActInd->stIpv4Dns.bitOpPrimDnsAddr)
    {
        ulPrimDNS = AT_GetLanAddr32(pstPdpActInd->stIpv4Dns.aucPrimDnsAddr);
    }

    if (pstPdpActInd->stIpv4Dns.bitOpSecDnsAddr)
    {
        ulSecDNS = AT_GetLanAddr32(pstPdpActInd->stIpv4Dns.aucSecDnsAddr);
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^VTDCONNV4:%08X,%08X,%08X,%08X,%08X,%08X%s",
                                                    gaucAtCrLf,
                                                    VOS_HTONL(ulIPAddr),
                                                    VOS_HTONL(ulSubNetMask),
                                                    VOS_HTONL(ulGateWay),
                                                    VOS_HTONL(ulGateWay),
                                                    VOS_HTONL(ulPrimDNS),
                                                    VOS_HTONL(ulSecDNS),
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaVtIpv6PdpActInd
 功能描述  : VT IPV6承载激活指示处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID AT_RcvImsaVtIpv6PdpActInd(
    VOS_UINT8                           ucIndex,
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength     = 0;
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, TAF_IPV6_ADDR_LEN);

    usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s^VTDCONNV6:", gaucAtCrLf);

    /* 填写IPV6地址 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstPdpActInd->stPdpAddr.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* 填写IPV6掩码, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6网关, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写DHCP IPV6, 该字段填全0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstPdpActInd->stIpv6Dns.aucPrimDnsAddr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* 填写IPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstPdpActInd->stIpv6Dns.aucSecDnsAddr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);


    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", gaucAtCrLf);


    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

}

/*****************************************************************************
 函 数 名  : AT_RcvImsaVtIpv4v6PdpActInd
 功能描述  : VT IPV4V6承载激活指示处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID AT_RcvImsaVtIpv4v6PdpActInd(
    VOS_UINT8                           ucIndex,
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd
)
{
    AT_RcvImsaVtIpv4PdpActInd(ucIndex, pstPdpActInd);
    AT_RcvImsaVtIpv6PdpActInd(ucIndex, pstPdpActInd);
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaVtPdpActInd
 功能描述  : VT承载激活指示处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaVtPdpActInd(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd;
    VOS_UINT8                           ucIndex;

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstPdpActInd = (IMSA_AT_VT_PDP_ACTIVATE_IND_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstPdpActInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaVtPdpActInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    switch(pstPdpActInd->stPdpAddr.enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_RcvImsaVtIpv4PdpActInd(ucIndex, pstPdpActInd);
            break;
        case TAF_PDP_IPV6:
            AT_RcvImsaVtIpv6PdpActInd(ucIndex, pstPdpActInd);
            break;
        case TAF_PDP_IPV4V6:
            AT_RcvImsaVtIpv4v6PdpActInd(ucIndex, pstPdpActInd);
            break;
        default:
            return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvImsaVtPdpDeactInd
 功能描述  : VT承载去激活指示处理函数
 输入参数  : *pMsg        回复消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaVtPdpDeactInd(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU *pstPdpDeactInd;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* 初始化消息变量 */
    usLength       = 0;
    ucIndex        = 0;
    pstPdpDeactInd = (IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU *)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstPdpDeactInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaVtPdpDeactInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    switch(pstPdpDeactInd->enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^VTDENDV4%s",
                                               gaucAtCrLf,
                                               gaucAtCrLf);
            break;
        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                            "%s^VTDENDV6%s",
                                                            gaucAtCrLf,
                                                            gaucAtCrLf);
            break;
        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                            "%s^VTDENDV4%s",
                                                            gaucAtCrLf,
                                                            gaucAtCrLf);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                            "%s^VTDENDV6%s",
                                                            gaucAtCrLf,
                                                            gaucAtCrLf);

            break;
        default:
            return VOS_ERR;
    }

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : AT_RcvImsaMtStateInd
 功能描述  : 被叫状态指示处理函数
 输入参数  : *pMsg        IMSA上报消息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月18日
    作    者   : m00277840
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_RcvImsaMtStateInd(VOS_VOID * pMsg)
{
    /* 定义局部变量 */
    IMSA_AT_MT_STATES_IND_STRU          *pstMtStatusInd;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acString[AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH + 1];

    /* 初始化消息变量 */
    ucIndex     = 0;
    pstMtStatusInd  = (IMSA_AT_MT_STATES_IND_STRU*)pMsg;

    /* 通过ClientId获取ucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtStatusInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    VOS_MemSet(acString, 0, sizeof(acString));
    VOS_MemCpy(acString, pstMtStatusInd->aucAsciiCallNum, AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH);

    gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s^IMSMTRPT: %s,%d,%d%s",
                                                   gaucAtCrLf,
                                                   acString,
                                                   pstMtStatusInd->ucMtStatus,
                                                   pstMtStatusInd->ulCauseCode,
                                                   gaucAtCrLf);
    /* 调用At_SendResultData发送命令结果 */
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


