

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtCmdFtmProc.h"
#include "ATCmdProc.h"
#include "AtMtaInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "msp_diag.h"
#endif

#include "AtTestParaCmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_FTM_PROC_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : At_SetLogPortPara
 功能描述  : ^LOGPORT的设置函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月20日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年8月9日
    作    者   : z60575
    修改内容   : LOG35_TL调用TL接口
*****************************************************************************/
VOS_UINT32 At_SetLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulOmLogPort;
    
    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多或没有 */
    if ((2 < gucAtParaIndex) || (0 == gucAtParaIndex))
    {
        return AT_ERROR;
    }

    if (AT_LOG_PORT_USB == gastAtParaList[0].ulParaValue)
    {
        ulOmLogPort = CPM_OM_PORT_TYPE_USB;
    }
    else
    {
        ulOmLogPort = CPM_OM_PORT_TYPE_VCOM;
    }

    /* 参数只有一个，默认永久生效 */
    if (1 == gucAtParaIndex)
    {
        gastAtParaList[1].ulParaValue = VOS_TRUE;
    }

    vos_printf("[socp set timer] : at port %d, log port %d, param %d.\n", 
        ucIndex, ulOmLogPort, gastAtParaList[1].ulParaValue);

    /* 调用OM的接口 */
    ulRslt = PPM_LogPortSwitch(ulOmLogPort, gastAtParaList[1].ulParaValue);

    if (VOS_OK == ulRslt)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_QryLogPortPara
 功能描述  : ^LOGPORT的查询函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月20日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年8月9日
    作    者   : z60575
    修改内容   : LOG35_TL调用TL接口
*****************************************************************************/
VOS_UINT32 At_QryLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulOmLogPort;
    VOS_UINT32                          ulAtLogPort;
    VOS_UINT32                          ulRslt;

    usLength                            = 0;
    ulOmLogPort                         = AT_LOG_PORT_USB;

    ulRslt = PPM_QueryLogPort(&ulOmLogPort);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    if (COMM_LOG_PORT_USB == ulOmLogPort)
    {
        ulAtLogPort = AT_LOG_PORT_USB;
    }
    else
    {
        ulAtLogPort = AT_LOG_PORT_VCOM;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulAtLogPort);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_SetDpdtTestFlagPara
 功能描述  : 支持^DPDTTEST设置，
             命令格式:^DPDTTEST=<RatMode>,<Flag>
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月04日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_SetDpdtTestFlagPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU   stAtCmd;
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT发送至MTA的消息结构赋值 */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucFlag    = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    /* 发送消息给C核处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_DPDTTEST_FLAG_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTTEST_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_SetDpdtPara
 功能描述  : 支持^DPDT设置，
             命令格式:^DPDT=<RatMode>,<DpdtValue>
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月04日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_SetDpdtPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_DPDT_VALUE_REQ_STRU      stAtCmd;
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT发送至MTA的消息结构赋值 */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode   = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ulDpdtValue = gastAtParaList[1].ulParaValue;

    /* 发送消息给C核处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_DPDT_VALUE_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDT_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
 函 数 名  : At_SetQryDpdtPara
 功能描述  : 支持^DPDTQRY设置，
             命令格式:^DPDTQRY=<RatMode>
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月04日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_SetQryDpdtPara(VOS_UINT8 ucIndex)
{
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU      stAtCmd;
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT发送至MTA的消息结构赋值 */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* 发送消息给C核处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_QRY_DPDT_VALUE_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTQRY_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaSetDpdtTestFlagCnf
 功能描述  : AT模块收到MTA回复的Set Dpdt Flag回复消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月09日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetDpdtTestFlagCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pstMtaMsg         = VOS_NULL_PTR;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU  *pstSetDpdtFlagCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex   = 0;
    pstMtaMsg = (AT_MTA_MSG_STRU *)pMsg;
    pstSetDpdtFlagCnf = (MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU *)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_DPDTTEST_SET */
    if (AT_CMD_DPDTTEST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:Not AT_CMD_DPDTTEST_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if (MTA_AT_RESULT_NO_ERROR == pstSetDpdtFlagCnf->enResult)
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
 函 数 名  : AT_RcvMtaSetDpdtValueCnf
 功能描述  : AT模块收到MTA回复的Set Dpdt Value回复消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月09日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetDpdtValueCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pstMtaMsg          = VOS_NULL_PTR;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU     *pstSetDpdtValueCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    pstMtaMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstSetDpdtValueCnf = (MTA_AT_SET_DPDT_VALUE_CNF_STRU *)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_DPDT_SET */
    if (AT_CMD_DPDT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:Not AT_CMD_DPDT_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if (MTA_AT_RESULT_NO_ERROR == pstSetDpdtValueCnf->enResult)
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
 函 数 名  : AT_RcvMtaQryDpdtValueCnf
 功能描述  : AT模块收到MTA回复的Qry Dpdt Value回复消息的处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月09日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryDpdtValueCnf(VOS_VOID *pMsg)
{
    /* 定义局部变量 */
    AT_MTA_MSG_STRU                    *pstMtaMsg          = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU     *pstQryDpdtValueCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化消息变量 */
    ucIndex            = 0;
    pstMtaMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstQryDpdtValueCnf = (MTA_AT_QRY_DPDT_VALUE_CNF_STRU *)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* 判断当前操作类型是否为AT_CMD_DPDTQRY_SET */
    if (AT_CMD_DPDTQRY_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:Not AT_CMD_DPDTQRY_SET!");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 判断查询操作是否成功 */
    if (MTA_AT_RESULT_NO_ERROR == pstQryDpdtValueCnf->enResult)
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "^DPDTQRY: %d",
                                            pstQryDpdtValueCnf->ulDpdtValue);
    }
    else
    {
        ulResult = AT_ERROR;
        gstAtSendData.usBufLen = 0;
    }

    /* 调用At_FormatResultData发送命令结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : At_SetJamDetectPara
 功能描述  : 支持^JDETEX设置
             命令格式:^JDETEX=<mode>[,<METHOD>,<NPT>,<UCN>]
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月05日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_SetJamDetectPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamCfg;
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT发送至MTA的消息结构赋值 */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));

    stAtCmd.ucFlag         = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod       = AT_JAM_DETECT_DEFAULT_METHOD;

    if (0 == gastAtParaList[2].usParaLen)
    {
        stAtCmd.ucThreshold    = AT_JAM_DETECT_DEFAULT_THRESHOLD;
    }
    else
    {
        stAtCmd.ucThreshold    = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    }

    if (0 == gastAtParaList[3].usParaLen)
    {
        stAtCmd.ucFreqNum      = AT_JAM_DETECT_DEFAULT_FREQ_NUM;
    }
    else
    {
        stAtCmd.ucFreqNum      = (VOS_UINT8)gastAtParaList[3].ulParaValue;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_JAM_DETECT_CFG, &stNvJamCfg, sizeof(stNvJamCfg)))
    {
        AT_WARN_LOG("At_SetJamDetectPara():en_NV_Item_JAM_DETECT_CFG NV Read Fail!");
        return AT_ERROR;
    }

    /* 配置参数保存在NV消息结构中 */
    stNvJamCfg.ucMode      = stAtCmd.ucFlag;
    stNvJamCfg.ucMethod    = stAtCmd.ucMethod;
    stNvJamCfg.ucThreshold = stAtCmd.ucThreshold;
    stNvJamCfg.ucFreqNum   = stAtCmd.ucFreqNum;

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_JAM_DETECT_CFG, &stNvJamCfg, sizeof(stNvJamCfg)))
    {
        AT_WARN_LOG("At_SetJamDetectPara():en_NV_Item_JAM_DETECT_CFG NV Write Fail!");
        return AT_ERROR;
    }

    /* 发送消息给C核处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_JAM_DETECT_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_JDETEX_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_QryJamDetectPara
 功能描述  : ^JDETEX查询Jam Detect设置值
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : 执行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月9日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_QryJamDetectPara(VOS_UINT8 ucIndex)
{
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamDetect;

    PS_MEM_SET(&stNvJamDetect, 0x0, sizeof(stNvJamDetect));

    /* 通过读取NV来获取Jam Detect当前配置值 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_JAM_DETECT_CFG,
                           &stNvJamDetect,
                           sizeof(NV_NAS_JAM_DETECT_CFG_STRU)))
    {
        AT_WARN_LOG("At_QryJamDetectPara: NV_ReadEx en_NV_Item_JAM_DETECT_CFG fail!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stNvJamDetect.ucMode,
                                                    stNvJamDetect.ucMethod,
                                                    stNvJamDetect.ucThreshold,
                                                    stNvJamDetect.ucFreqNum);

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaSetJamDetectCnf
 功能描述  : AT模块收到MTA回复的Jam Detect设置结果处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : g00261581
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetJamDetectCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg;
    MTA_AT_SET_JAM_DETECT_CNF_STRU         *pstSetCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* 初始化 */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_JAM_DETECT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult     = AT_OK;
    ucIndex      = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_JDETEX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : Current Option is not AT_CMD_JDETEX_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaJamDetectInd
 功能描述  : AT模块收到MTA回复的Jam Ind上报消息处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : g00261581
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaJamDetectInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_JAM_DETECT_IND_STRU         *pstJamDetectInd;

    /* 初始化消息变量 */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstJamDetectInd     = (MTA_AT_JAM_DETECT_IND_STRU*)pstMtaMsg->aucContent;

    /* 通过ClientId获取ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaJamDetectInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    /* 上报干扰检测结果 */
    if (MTA_AT_JAM_RESULT_JAM_DISCOVERED == pstJamDetectInd->enJamResult)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^JDET: JAMMED%s",
                                                        gaucAtCrLf,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    if (MTA_AT_JAM_RESULT_JAM_DISAPPEARED == pstJamDetectInd->enJamResult)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^JDET: DETECTING%s",
                                                        gaucAtCrLf,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SetRatFreqLock
 功能描述  : 支持^FREQLOCK设置
             命令格式:^FREQLOCK=<enable>[,<freq>[,<ratMode>[,<band>]]]
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月11日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_SetRatFreqLock(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_FREQ_LOCK_REQ_STRU       stAtCmd;
    VOS_UINT32                          ulRst;

    /* 参数个数检查 */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU));
    stAtCmd.ucEnableFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* 如果锁频功能关闭，直接写Nv, 返回AT_OK */
    if (VOS_FALSE == stAtCmd.ucEnableFlg)
    {
        if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_FREQ_LOCK_CFG, &stAtCmd, sizeof(stAtCmd)))
        {
            AT_ERR_LOG("AT_SetRatFreqLock(): en_NV_Item_FREQ_LOCK_CFG NV Write Fail!");
            return AT_ERROR;
        }

        return AT_OK;
    }

    stAtCmd.usLockedFreq = (VOS_UINT16)gastAtParaList[1].ulParaValue;

    /* 解析命令中的接入模式 */
    if (0 == gastAtParaList[2].usParaLen)
    {
        stAtCmd.enRatMode = AT_MTA_FREQLOCK_RATMODE_WCDMA;
    }
    else
    {
        stAtCmd.enRatMode = (AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8)gastAtParaList[2].ulParaValue;
    }

    /* 解析命令中的BAND信息 */
    if (0 == gastAtParaList[3].usParaLen)
    {
        if (AT_MTA_FREQLOCK_RATMODE_GSM == stAtCmd.enRatMode)
        {
            return AT_ERROR;
        }
        stAtCmd.enBand = AT_MTA_GSM_BAND_BUTT;
    }
    else
    {
        stAtCmd.enBand = (AT_MTA_GSM_BAND_ENUM_UINT16)gastAtParaList[3].ulParaValue;
    }

    /* 发送消息给C核处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_FREQ_LOCK_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RATFREQLOCK_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaSetRatFreqLockCnf
 功能描述  : AT模块收到MTA回复的频点检查结果处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : g00261581
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetRatFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU      *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_FREQ_LOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_RATFREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : Current Option is not AT_CMD_RATFREQLOCK_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_QryRatFreqLock
 功能描述  : ^FREQLOCK查询锁频命令设置值
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : 执行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_QryRatFreqLock(VOS_UINT8 ucIndex)
{
    TAF_NVIM_FREQ_LOCK_CFG_STRU         stNvFreqLockCfg;

    PS_MEM_SET(&stNvFreqLockCfg, 0x0, sizeof(stNvFreqLockCfg));

    /* 通过读取NV来获取Freq Lock当前配置值 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_FREQ_LOCK_CFG,
                           &stNvFreqLockCfg,
                           sizeof(TAF_NVIM_FREQ_LOCK_CFG_STRU)))
    {
        AT_WARN_LOG("At_QryRatFreqLock: NV_ReadEx en_NV_Item_FREQ_LOCK_CFG fail!");
        return AT_ERROR;
    }

    /* 锁频功能关闭情况下只上报开关值:0 */
    if (VOS_FALSE == stNvFreqLockCfg.ucEnableFlg)
    {
        /* 查询结果上报 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg);

        return AT_OK;
    }

    /* 锁频功能设置在G模上，查询需要上报BAND信息 */
    if (TAF_NVIM_RAT_MODE_GSM == stNvFreqLockCfg.enRatMode)
    {
        /* 查询结果上报 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,\"0%d\",\"0%d\"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg,
                                                        stNvFreqLockCfg.usLockedFreq,
                                                        stNvFreqLockCfg.enRatMode,
                                                        stNvFreqLockCfg.enBand);
    }
    else
    {
        /* 查询结果上报 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,\"0%d\"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg,
                                                        stNvFreqLockCfg.usLockedFreq,
                                                        stNvFreqLockCfg.enRatMode);
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_SetGFreqLock
 功能描述  : 支持^GFREQLOCK设置
             命令格式:^GFREQLOCK =<enable>[,<freq>,<band>]
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_SetGFreqLock(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU    stGFreqLockInfo;
    VOS_UINT32                          ulRst;

    /* 参数个数检查 */
    if ((gucAtParaIndex != 1) && (gucAtParaIndex != 3))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 初始化 */
    PS_MEM_SET(&stGFreqLockInfo, 0, sizeof(AT_MTA_SET_GSM_FREQLOCK_REQ_STRU));

    /* 参数有效性检查 */
    /* 第一个参数必须带 */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stGFreqLockInfo.enableFlag = (PS_BOOL_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* 若启动锁频，则必须带第二个参数和第三个参数 */
    if (PS_TRUE == stGFreqLockInfo.enableFlag)
    {
        if ( (0 == gastAtParaList[1].usParaLen)
          || (0 == gastAtParaList[2].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            stGFreqLockInfo.usFreq = (VOS_UINT16)gastAtParaList[1].ulParaValue;
            stGFreqLockInfo.enBand = (AT_MTA_GSM_BAND_ENUM_UINT16)gastAtParaList[2].ulParaValue;
        }
    }

    /* 发送消息给C核处理 */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_GSM_FREQLOCK_REQ,
                                   &stGFreqLockInfo,
                                   sizeof(AT_MTA_SET_GSM_FREQLOCK_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GSM_FREQLOCK_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaSetGFreqLockCnf
 功能描述  : AT模块收到MTA回复的G模频点设置结果处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 新增
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetGFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU   *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_GSM_FREQLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_GSM_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : Current Option is not AT_CMD_GSM_FREQLOCK_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* 格式化命令返回 */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_NetMonFmtPlmnId
 功能描述  : PLMN ID 字符串化处理函数
 输入参数  : ulMcc -- Mcc
             ulMnc -- Mnc
 输出参数  : pstrPlmn  -- 字符串化后的PLMN
             pusLength --字符串化后的PLMN长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtPlmnId(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc,
    VOS_CHAR                           *pstrPlmn,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT32                          ulMaxLength;
    VOS_UINT32                          ulLength;

    ulLength                          = 0;
    ulMaxLength                       = AT_NETMON_PLMN_STRING_MAX_LENGTH;

    /* 格式输出MCC */
    ulLength += VOS_nsprintf( (VOS_CHAR *)pstrPlmn,
                              (VOS_UINT32)ulMaxLength,
                              "%X%X%X",
                              (ulMcc & 0x0f),
                              (ulMcc & 0x0f00)>>8,
                              (ulMcc & 0x0f0000)>>16 );


    /* 格式输出MNC */
    if (0x0f0000 == (ulMnc & 0x0f0000))
    {
        ulLength += VOS_nsprintf( (VOS_CHAR *)(pstrPlmn + ulLength),
                                  (VOS_UINT32)ulMaxLength - ulLength,
                                  ",%X%X",
                                  (ulMnc & 0x0f),
                                  (ulMnc & 0x0f00)>>8 );
    }
    else
    {
        ulLength += VOS_nsprintf( (VOS_CHAR *)(pstrPlmn + ulLength),
                                  (VOS_UINT32)ulMaxLength - ulLength,
                                  ",%X%X%X",
                                  (ulMnc & 0x0f),
                                  (ulMnc & 0xf00)>>8,
                                  (ulMnc & 0x0f0000)>>16 );
    }

    *pusLength = (VOS_UINT16)ulLength;

    return;
}

/*****************************************************************************
 函 数 名  : AT_NetMonFmtGsmSCellData
 功能描述  : GSM 服务小区输出 字符串化处理函数
 输入参数  : pstSCellInfo -- 服务小区数据结构
 输出参数  : pusLength  --  GSM 服务小区输出 字符串化长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtGsmSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    PS_MEM_SET(pucPlmnstr, 0, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* 格式输出PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: GSM,%s,%d,%d,%d,%X,%X",
                                        pucPlmnstr,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.enBand,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.usArfcn,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ucBsic,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ulCellID,
                                        pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.usLac );

    /* RSSI无效值，不显示 */
    if (AT_NETMON_GSM_RSSI_INVALID_VALUE == pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.sRssi)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.sRssi );
    }

    /* 无效值，不显示 */
    if (AT_NETMON_GSM_RX_QUALITY_INVALID_VALUE == pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ucRxQuality)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo.ucRxQuality );
    }

    /*输出TA*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stGsmSCellInfo.usTa );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    *pusLength = usLength;

    return;
}

/*****************************************************************************
 函 数 名  : AT_NetMonFmtUtranFddSCellData
 功能描述  : WCDMA 服务小区输出 字符串化处理函数
 输入参数  : pstSCellInfo -- 服务小区数据结构
 输出参数  : pusLength  --  WCDMA 服务小区输出 字符串化长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranFddSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    PS_MEM_SET(pucPlmnstr, 0, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* 格式输出PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: WCDMA,%s",
                                        pucPlmnstr );

    /*输出频点*/
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d",
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.usArfcn );

    /* PSC无效值，不显示 */
    if ((AT_NETMON_UTRAN_FDD_RSCP_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSCP)
        && (AT_NETMON_UTRAN_FDD_ECN0_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sECN0))
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.usPSC );
    }

    /*输出Cell ID*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.bitOpCellID)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%X",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulCellID );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    /*输出LAC*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.bitOpLAC)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            ",%X",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.usLAC );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    /* RSCP无效值，不显示 */
    if (AT_NETMON_UTRAN_FDD_RSCP_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSCP)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSCP );
    }

    /* RSSI无效值，不显示 */
    if (AT_NETMON_UTRAN_FDD_RSSI_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSSI)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sRSSI );
    }

    /* ECN0无效值，不显示 */
    if (AT_NETMON_UTRAN_FDD_ECN0_INVALID_VALUE == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sECN0)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.sECN0 );
    }

    /*输出DRX*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.bitOpDRX)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.ulDrx );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    /*输出URA Id*/
    if (PS_IE_PRESENT == pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.bitOpURA)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsFDD.usURA );
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "," );
    }

    *pusLength = usLength;

    return;
}

/*****************************************************************************
 函 数 名  : AT_NetMonFmtGsmNCellData
 功能描述  : GSM 临区输出 字符串化处理函数
 输入参数  : pstNCellInfo -- 临区数据结构
             usInLen      -- 输入长度
 输出参数  : pusOutLen    --  GSM 临区输出 字符串化处理函数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtGsmNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucGsmNCellCnt > NETMON_MAX_GSM_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucGsmNCellCnt = NETMON_MAX_GSM_NCELL_NUM;
    }

    /* GSM邻区显示 */
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucGsmNCellCnt; ulLoop++)
    {
        /* 如果输出的不是第一个邻区，先打印回车换行 */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                gaucAtCrLf );
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: GSM,%d,%d",
                                            pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].enBand,
                                            pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].usAfrcn );

        /*输出Bsic*/
        if (PS_IE_PRESENT == pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].bitOpBsic)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                ",%d",
                                                pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].ucBsic );
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "," );
        }

        /*输出Cell ID*/
        if (PS_IE_PRESENT == pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].bitOpCellID)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                ",%X",
                                                pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].ulCellID );
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                                "," );
        }

         /*输出LAC*/
        if (PS_IE_PRESENT == pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].bitOpLAC)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%X",
                                               pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].usLAC );
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "," );
        }

        /*输出RSSI*/
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            ",%d",
                                            pstNCellInfo->stNCellInfo.astGsmNCellInfo[ulLoop].sRSSI );
    }

    *pusOutLen = usLength;

    return;
}
/*****************************************************************************
 函 数 名  : AT_NetMonFmtUtranFddNCellData
 功能描述  : WCDMA 临区输出 字符串化处理函数
 输入参数  : pstNCellInfo -- 临区数据结构
             usInLen      -- 输入长度
 输出参数  : pusOutLen    --  WCDMA临区输出 字符串化处理函数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranFddNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucUtranNCellCnt > NETMON_MAX_UTRAN_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucUtranNCellCnt = NETMON_MAX_UTRAN_NCELL_NUM;
    }

    /*WCDMA 临区显示*/
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucUtranNCellCnt; ulLoop++)
    {
        /* 如果不是第一次打印邻区，打印回车换行 */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                gaucAtCrLf);
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                            "^MONNC: WCDMA,%d,%d,%d,%d",
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].usArfcn,
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].usPSC,
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].sRSCP,
                                            pstNCellInfo->stNCellInfo.u.astFddNCellInfo[ulLoop].sECN0 );
    }

    *pusOutLen = usLength;

    return;
}

/*****************************************************************************
 函 数 名  : At_SetNetMonSCellPara
 功能描述  : ^MONSC查询服务小区消息
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : 执行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetNetMonSCellPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg( gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    ID_AT_MTA_SET_NETMON_SCELL_REQ,
                                    VOS_NULL_PTR,
                                    0,
                                    I0_UEPS_PID_MTA );

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MONSC_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 函 数 名  : At_SetNetMonNCellPara
 功能描述  : ^MONNC查询邻区信息
 输入参数  : ucIndex - 用户索引
 输出参数  : 无
 返 回 值  : 执行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetNetMonNCellPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg( gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    ID_AT_MTA_SET_NETMON_NCELL_REQ,
                                    VOS_NULL_PTR,
                                    0,
                                    I0_UEPS_PID_MTA );

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MONNC_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
/*****************************************************************************
 函 数 名  : AT_RcvMtaSetNetMonSCellCnf
 功能描述  : AT模块收到MTA回复的MONSC设置结果处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetNetMonSCellCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pstRcvMsg                         = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf                         = (MTA_AT_NETMON_CELL_INFO_STRU *)pstRcvMsg->aucContent;

    usLength                          = 0;
    ucIndex                           = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitServingCellCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitServingCellCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MONSC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitServingCellCnf : Current Option is not AT_CMD_JDETEX_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( (MTA_AT_RESULT_ERROR   == pstSetCnf->enResult)
      || (MTA_NETMON_SCELL_TYPE != pstSetCnf->enCellType) )
    {
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    switch(pstSetCnf->enRatType)
    {
        case MTA_AT_NETMON_CELL_INFO_GSM:
        {
            AT_NetMonFmtGsmSCellData(pstSetCnf, &usLength);
            break;
        }
        case MTA_AT_NETMON_CELL_INFO_UTRAN_FDD:
        {
            AT_NetMonFmtUtranFddSCellData(pstSetCnf, &usLength);
            break;
        }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case MTA_AT_NETMON_CELL_INFO_UTRAN_TDD:
        {
            AT_NetMonFmtUtranTddSCellData(pstSetCnf, &usLength);
            break;
        }
#endif
#if (FEATURE_ON == FEATURE_LTE)
        case MTA_AT_NETMON_CELL_INFO_LTE:
        {
            AT_NetMonFmtEutranSCellData(pstSetCnf, &usLength);
            break;
        }
#endif
        default:
            usLength += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "^MONSC: NONE" );
            break;
    }


    /* 输出结果 */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvMtaSetNetMonNCellCnf
 功能描述  : AT模块收到MTA回复的MONNC设置结果处理函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetNetMonNCellCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT16                          usLengthTemp;

    /* 初始化 */
    pstRcvMsg                         = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf                         = (MTA_AT_NETMON_CELL_INFO_STRU *)pstRcvMsg->aucContent;

    ucIndex                           = 0;
    usLength                          = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitNeighCellCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitNeighCellCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* 当前AT是否在等待该命令返回 */
    if (AT_CMD_MONNC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetMonitNeighCellCnf : Current Option is not AT_CMD_JDETEX_SET.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( (MTA_AT_RESULT_ERROR   == pstSetCnf->enResult)
      || (MTA_NETMON_NCELL_TYPE != pstSetCnf->enCellType) )
    {
        gstAtSendData.usBufLen = usLength;
        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    usLengthTemp   = 0;
    usLength       = 0;

    /* GSM邻区显示 */
    AT_NetMonFmtGsmNCellData(pstSetCnf, usLengthTemp, &usLength);

    /* UTRAN邻区显示 */
    usLengthTemp = usLength;

    if (MTA_NETMON_UTRAN_FDD_TYPE == pstSetCnf->stNCellInfo.enCellMeasTypeChoice)
    {
        AT_NetMonFmtUtranFddNCellData(pstSetCnf, usLengthTemp, &usLength);
    }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    else if (MTA_NETMON_UTRAN_TDD_TYPE == pstSetCnf->stNCellInfo.enCellMeasTypeChoice)
    {
        AT_NetMonFmtUtranTddNCellData(pstSetCnf, usLengthTemp, &usLength);
    }
#endif
    else
    {
        /*类型不对，不进行任何处理*/
        ;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* LTE邻区显示 */
    usLengthTemp = usLength;

    AT_NetMonFmtEutranNCellData(pstSetCnf, usLengthTemp, &usLength);
#endif

    /* 无邻区，返回NONE */
    if ( 0 == ( pstSetCnf->stNCellInfo.ucGsmNCellCnt +
                pstSetCnf->stNCellInfo.ucUtranNCellCnt + pstSetCnf->stNCellInfo.ucLteNCellCnt ) )
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: NONE" );
    }

    /* 输出结果 */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : AT_NetMonFmtUtranTddSCellData
 功能描述  : TD-SCDMA 服务小区输出 字符串化处理函数
 输入参数  : pstSCellInfo -- 服务小区数据结构
 输出参数  : pusLength  --  TD-SCDMA 服务小区输出 字符串化长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranTddSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    PS_MEM_SET(pucPlmnstr, 0, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* 格式输出PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: TD_SCDMA,%s",
                                        pucPlmnstr );

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d,%d,%d,%X,%X,%d,%d,%d",
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.usArfcn,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.usSyncID,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.usSC,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.ulCellID,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.usLAC,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.sRSCP,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.ulDrx,
                                        pstSCellInfo->unSCellInfo.stUtranSCellInfo.u.stCellMeasResultsTDD.usRac );

    *pusLength = usLength;

    return;
}
/*****************************************************************************
 函 数 名  : AT_NetMonFmtUtranFddNCellData
 功能描述  : TD-SCDMA 临区输出 字符串化处理函数
 输入参数  : pstNCellInfo -- 临区数据结构
             usInLen      -- 输入长度
 输出参数  : pusOutLen    --  TD-SCDMA临区输出 字符串化处理函数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtUtranTddNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucUtranNCellCnt > NETMON_MAX_UTRAN_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucUtranNCellCnt = NETMON_MAX_UTRAN_NCELL_NUM;
    }

    /*WCDMA 临区显示*/
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucUtranNCellCnt; ulLoop++)
    {
        /* 如果不是第一次打印邻区，打印回车换行 */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                 "%s",
                                                 gaucAtCrLf );
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: TD_SCDMA,%d,%d,%d,%d",
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].usArfcn,
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].usSyncID,
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].usSC,
                                            pstNCellInfo->stNCellInfo.u.astTddNCellInfo[ulLoop].sRSCP );
    }

    *pusOutLen = usLength;

    return;
}
#endif

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : AT_NetMonFmtEutranSCellData
 功能描述  : LTE 服务小区输出 字符串化处理函数
 输入参数  : pstSCellInfo -- 服务小区数据结构
 输出参数  : pusLength  --  LTE 服务小区输出 字符串化长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtEutranSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
)
{
    VOS_UINT8                           pucPlmnstr[AT_NETMON_PLMN_STRING_MAX_LENGTH];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          ulPlmnStrLen;
    VOS_UINT16                          usLength;

    usLength                          = 0;
    ulPlmnStrLen                      = 0;
    PS_MEM_SET(pucPlmnstr, 0, sizeof(pucPlmnstr));

    ulMcc = pstSCellInfo->unSCellInfo.stLteSCellInfo.ulMcc;
    ulMnc = pstSCellInfo->unSCellInfo.stLteSCellInfo.ulMnc;

    AT_NetMonFmtPlmnId(ulMcc, ulMnc, (VOS_CHAR *)pucPlmnstr, &ulPlmnStrLen);

    /* 格式输出PLMN */
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^MONSC: LTE,%s",
                                        pucPlmnstr );

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d,%X,%X,%X,%d,%d,%d",
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.usArfcn,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.ulCellID,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.ulPID,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.usTAC,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.sRSRP,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.sRSRQ,
                                        pstSCellInfo->unSCellInfo.stLteSCellInfo.sRSSI );
    *pusLength = usLength;

    return;
}

/*****************************************************************************
 函 数 名  : AT_NetMonFmtEutranNCellData
 功能描述  : LTE 临区输出 字符串化处理函数
 输入参数  : pstNCellInfo -- 临区数据结构
             usInLen   -- 输入长度
 输出参数  : pusOutLen  --  LTE临区输出 字符串化处理函数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NetMonFmtEutranNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;

    usLength                          = usInLen;

    if (pstNCellInfo->stNCellInfo.ucLteNCellCnt > NETMON_MAX_LTE_NCELL_NUM)
    {
        pstNCellInfo->stNCellInfo.ucLteNCellCnt = NETMON_MAX_LTE_NCELL_NUM;
    }

     /* LTE邻区显示 */
    for (ulLoop = 0; ulLoop < pstNCellInfo->stNCellInfo.ucLteNCellCnt; ulLoop++)
    {
        /* 如果不是第一次打印邻区，打印回车换行 */
        if (0 != usLength)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                gaucAtCrLf);
        }

        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "^MONNC: LTE,%d,%X,%d,%d,%d",
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].usArfcn,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].ulPID,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].sRSRP,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].sRSRQ,
                                            pstNCellInfo->stNCellInfo.astLteNCellInfo[ulLoop].sRSSI );
    }

    *pusOutLen = usLength;

    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

