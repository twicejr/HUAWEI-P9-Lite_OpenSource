

#include "AtCheckFunc.h"
#include "ATCmdProc.h"
#include "AtCmdMsgProc.h"
#include "AtInputProc.h"

#include "at_common.h"

#include "AcpuReset.h"

#include "AtInternalMsg.h"

#include "AtParseCore.h"

#include "AtDataProc.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSECORE_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/


/* 命令表头结点 */
HI_LIST_S g_stCmdTblList = {0};

/* 解析过程参数 */
AT_PARSECMD_STRU g_stATParseCmd;

/* 参数列表 */
VOS_UINT8 gucAtParaIndex = 0;

AT_PARSE_PARA_TYPE_STRU gastAtParaList[AT_MAX_PARA_NUMBER];

/* 每个客户端的解析信息 */
AT_PARSE_CONTEXT_STRU g_stParseContext[AT_MAX_CLIENT_NUM];

/* 由于SMS命令与普通命令格式不一致，用来缓存SMS命令的相应的内容 */
/* 解决短信命令支持多通道并发命令名被覆盖问题
   由g_stCmdElement=> g_stCmdElement[AT_MAX_CLIENT_NUM] */
AT_PAR_CMD_ELEMENT_STRU g_stCmdElement[AT_MAX_CLIENT_NUM];



/*****************************************************************************
 函 数 名  : At_ParseInit
 功能描述  : 解析器初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月21日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理编译warning

*****************************************************************************/
VOS_VOID At_ParseInit(VOS_VOID)
{
    VOS_UINT32 i = 0;

    PS_MEM_SET(&g_stATParseCmd,   0, sizeof(g_stATParseCmd));
    PS_MEM_SET(g_stParseContext,  0, sizeof(g_stParseContext));
    PS_MEM_SET(g_stCmdElement,    0, sizeof(g_stCmdElement));

    /*lint -e717*/

    HI_INIT_LIST_HEAD(&g_stCmdTblList);

    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        HI_INIT_LIST_HEAD(&(g_stParseContext[i].stCombineCmdInfo.stCombineCmdList));
    }

    /*lint -e717*/

    return;
}

/******************************************************************************
 函数名称: AT_RegisterCmdTable
 功能描述: 命令表注册

 参数说明:
   pstCmdTblEntry [in] 命令表指针
   usCmdNum [in] 命令表中命令个数

 作    者: 崔军强/00064416 [2011-09-30]
******************************************************************************/
VOS_UINT32 AT_RegisterCmdTable(const AT_PAR_CMD_ELEMENT_STRU* pstCmdTblEntry, VOS_UINT16 usCmdNum)
{
    HI_LIST_S* pCmdTblHeader = NULL;
    AT_PAR_CMDTBL_LIST_STRU* pstCmdTblNode = NULL;

    /* 命令表不为空，且命令个数不为0 */
    if((NULL == pstCmdTblEntry) || (0 == usCmdNum))
    {
        return ERR_MSP_FAILURE;
    }

    pCmdTblHeader = &g_stCmdTblList;

    /* 把新请求的errcodetbl添加到链表中 */
    pstCmdTblNode = (AT_PAR_CMDTBL_LIST_STRU *)AT_MALLOC(sizeof(AT_PAR_CMDTBL_LIST_STRU));
    if(NULL == pstCmdTblNode)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    pstCmdTblNode->usCmdNum = usCmdNum;

    pstCmdTblNode->pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)pstCmdTblEntry;

    msp_list_add_tail((&pstCmdTblNode->stCmdTblList), pCmdTblHeader);

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 函 数 名  : AT_ClacCmdProc
 功能描述  : +CLAC 命令信息输出
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ClacCmdProc(VOS_VOID)
{
    VOS_UINT16 i = 0;
    HI_LIST_S* me = NULL;
    AT_PAR_CMDTBL_LIST_STRU* pstCmdTblNode = NULL;
    AT_PAR_CMD_ELEMENT_STRU* pstCmdElement = NULL;

    msp_list_for_each(me, &g_stCmdTblList)
    {
        pstCmdTblNode = msp_list_entry(me, AT_PAR_CMDTBL_LIST_STRU , stCmdTblList);

        pstCmdElement = pstCmdTblNode->pstCmdElement;

        if(NULL == pstCmdElement)
        {
            continue;
        }

        for(i = 0; i < pstCmdTblNode->usCmdNum; i++)
        {
            /* 判断是否需要显示 */
            if(0 == (pstCmdElement[i].ulChkFlag & CMD_TBL_CLAC_IS_INVISIBLE))
            {
                gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                  "%s%c%c", pstCmdElement[i].pszCmdName, ucAtS3, ucAtS4);
            }
        }
    }

    return ;
}


/*****************************************************************************
 函 数 名  : AT_BlockCmdCheck
 功能描述  : 检查是否有阻塞的命令
 输出参数  : 无
 返 回 值  : PRIVATE VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月11日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 AT_BlockCmdCheck(VOS_VOID)
{
    VOS_UINT8 i = 0;
    VOS_UINT8 ucBlockid = AT_MAX_CLIENT_NUM;

    /* 查询所有通道状态 */
    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        /* 如果某通道处于非ready态，则直接返回，不处理 */
        if(AT_FW_CLIENT_STATUS_READY != g_stParseContext[i].ucClientStatus)
        {
            return AT_MAX_CLIENT_NUM;
        }

        if((0 != g_stParseContext[i].usBlockCmdLen) && (NULL != g_stParseContext[i].pBlockCmd))
        {
            ucBlockid = i;
        }
    }

    return ucBlockid;
}


/*****************************************************************************
 函 数 名  : AT_ClearBlockCmdInfo
 功能描述  : 清空被阻塞的命令信息
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月11日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ClearBlockCmdInfo(VOS_UINT8 ucIndex)
{
    if(NULL != g_stParseContext[ucIndex].pBlockCmd)
    {
        AT_FREE(g_stParseContext[ucIndex].pBlockCmd);
        g_stParseContext[ucIndex].pBlockCmd = NULL;
    }

    g_stParseContext[ucIndex].usBlockCmdLen = 0;

    return;
}

#if 0
/*****************************************************************************
 函 数 名  : AT_BlockCmdProc
 功能描述  : 阻塞命令的处理
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : PRIVATE AT_RRETURN_CODE_ENUM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月11日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
PRIVATE AT_RRETURN_CODE_ENUM AT_BlockCmdProc(VOS_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM ulResult = AT_WAIT_ASYNC_RETURN;
    VOS_UINT8* pData = NULL;
    VOS_UINT16 usLen = 0;

    pData = g_stParseContext[ucIndex].pBlockCmd;
    usLen = g_stParseContext[ucIndex].usBlockCmdLen;

    /* TODO: 缓存 A/ */

    ulResult = (AT_RRETURN_CODE_ENUM)At_CombineCmdChkProc(ucIndex, pData, usLen);

    /* 返回结果 */
    if((AT_FAILURE == ulResult) || (AT_SUCCESS == ulResult))
    {
        return ulResult;
    }

    if(AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);

        return ulResult;
    }

    AT_ClearBlockCmdInfo(ucIndex);

    return ulResult;
}
#endif

/*****************************************************************************
 函 数 名  : AT_CheckProcBlockCmd
 功能描述  : 检查和处理阻塞命令
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月11日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_CheckProcBlockCmd(VOS_VOID)
{
    VOS_UINT8 ucIndex;
    VOS_UINT32 ulRet;


    /* 判断是否有缓存的命令 */
    ucIndex = AT_BlockCmdCheck();
    if(ucIndex < AT_MAX_CLIENT_NUM)
    {
        /* 发送消息处理缓存命令 */
        ulRet = At_SendCmdMsg(ucIndex, &ucIndex, sizeof(ucIndex), AT_COMBIN_BLOCK_MSG);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            /* 由定时器超时去处理 */
        }
    }

    return ;
}


/*****************************************************************************
 函 数 名  : AT_ParseCmdOver
 功能描述  : 本通道的当前命令处理结束（组合命令时只表示一条命令处理完毕）
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ParseCmdOver(VOS_UINT8 ucIndex)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo = NULL;

    if(ucIndex >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    pstCombineCmdInfo = &pClientContext->stCombineCmdInfo;

    if(pstCombineCmdInfo->usProcNum < pstCombineCmdInfo->usTotalNum)
    {
        pstCombineCmdInfo->usProcNum++;
    }
    else    /* 避免被误调用 */
    {
        pstCombineCmdInfo->usProcNum = pstCombineCmdInfo->usTotalNum;
    }

    /* 判断组合命令是否处理完毕 */
    if((pstCombineCmdInfo->usProcNum < pstCombineCmdInfo->usTotalNum))
    {
        /* 发送消息处理下一条命令 */
        ulRet = At_SendCmdMsg(ucIndex, &ucIndex, sizeof(ucIndex), AT_COMBIN_BLOCK_MSG);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            /* 消息发送失败恢复解析器状态 */
            pClientContext->ucClientStatus = AT_FW_CLIENT_STATUS_READY;
        }

        return ;
    }

    return;
}


/*****************************************************************************
 函 数 名  : AT_BlockCmdTimeOutProc
 功能描述  : 缓存命令超时处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月11日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_BlockCmdTimeOutProc(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = 0;

    At_FormatResultData(ucIndex, AT_ERROR);

    AT_ClearBlockCmdInfo(ucIndex);

    return ;
}


/*****************************************************************************
 函 数 名  : AT_PendClientProc
 功能描述  : PEND客户端处理
 输入参数  : ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月11日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2012年9月18日
    作    者   : l00171473
    修改内容   : V7R1C50_At_Abort

  3.日    期   : 2013年10月19日
    作    者   : w00167002
    修改内容   : NETSCAN:支持多通道AT打断
*****************************************************************************/
VOS_VOID AT_PendClientProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    if ((4 == usLen)
        && ('S' == At_UpChar(pData[0])) && ('T' == At_UpChar(pData[1]))
        && ('O' == At_UpChar(pData[2])) && ('P' == At_UpChar(pData[3])))
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_ResetCombinParseInfo(ucIndex);
    }
    else if(AT_CMD_A_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        if(('A' != At_UpChar(pData[0])) || ('T' != At_UpChar(pData[1]))
            || ('H' != At_UpChar(pData[2])))
        {
        }
        else
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            At_ResetCombinParseInfo(ucIndex);
        }
    }

    else if ( VOS_TRUE == AT_IsAbortCmdStr(ucIndex, pData, usLen) )
    {
        /* AT打断当前PEND状态的处理 */
        AT_AbortCmdProc(ucIndex);
    }

    else
    {
    }

    return ;
}


/*****************************************************************************
 函 数 名  : AT_HoldBlockCmd
 功能描述  : 保存阻塞命令字符串
 输入参数  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月11日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_HoldBlockCmd(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32 ulTimerName = 0;
    VOS_UINT32 ulTempIndex = 0;
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    pstClientContext = &(g_stParseContext[ucIndex]);

    /* 只支持缓存一条数据，当有新的AT命令字符流则覆盖本通道之前缓存的命令信息 */
    if(NULL != pstClientContext->pBlockCmd)
    {
        AT_FREE(pstClientContext->pBlockCmd);
    }

    pstClientContext->pBlockCmd = (VOS_UINT8*)AT_MALLOC(usLen);
    if(NULL == pstClientContext->pBlockCmd)
    {
        pstClientContext->usBlockCmdLen = 0;
        return ;
    }

    PS_MEM_CPY(pstClientContext->pBlockCmd, pData, usLen);
    pstClientContext->usBlockCmdLen = usLen;

    ulTempIndex  = (VOS_UINT32)ucIndex;
    ulTimerName  = AT_HOLD_CMD_TIMER;
    ulTimerName |= AT_INTERNAL_PROCESS_TYPE;
    ulTimerName |= (ulTempIndex<<12);

    /* 重启定时器 */
    VOS_StopRelTimer(&pstClientContext->hTimer);

    AT_StartRelTimer(&pstClientContext->hTimer, AT_HOLD_CMD_TIMER_LEN, ulTimerName, 0, VOS_RELTIMER_NOLOOP);

    return ;
}


/*****************************************************************************
 函 数 名  : AT_ParseCmdIsComb
 功能描述  : 判断是否有通道组合命令没有处理结束（本通道有组合命令没有处理结
             束则丢弃新输入的命令，其他通道则允许继续处理）
 输入参数  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : PRIVATE VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : L47619
    修改内容   : 修改AT通道并发处理逻辑，本函数仅做组合命令判断，不做并发逻辑判断

*****************************************************************************/
VOS_UINT32 AT_ParseCmdIsComb(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    pstClientContext = &(g_stParseContext[ucIndex]);

    /* 表示本通道有组合命令正在处理 */
    if(pstClientContext->stCombineCmdInfo.usProcNum < pstClientContext->stCombineCmdInfo.usTotalNum)
    {
        CmdStringFormat(ucIndex, pData, &usLen);

        AT_PendClientProc(ucIndex, pData, usLen);

        return ERR_MSP_FAILURE;
    }

    return ERR_MSP_SUCCESS;

}


/*****************************************************************************
 函 数 名  : AT_ParseCmdIsPend
 功能描述  : 判断是否有正在处理的通道，有的话丢弃或缓存
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : ERR_MSP_FAILURE : 有通道处于阻塞状态，不需要继续处理
             ERR_MSP_SUCCESS : 无阻塞通道，命令可正常处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2012年02月20日
    作    者   : f00179208
    修改内容   : 增加AT命令RIL对应的HSIC AT通道的并发执行
  3.日    期   : 2012年06月19日
    作    者   : f62575
    修改内容   : 问题单号:DTS2012061505515，GCF用例31.9.1.1 因为STOP命令失效失败
*****************************************************************************/
VOS_UINT32 AT_ParseCmdIsPend(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32 i = 0;
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        pstClientContext = &(g_stParseContext[i]);

        if (i == ucIndex)
        {
            /* 本通道处于PEND状态时需要判断是否是STOP或ATH */
            if (AT_FW_CLIENT_STATUS_PEND == pstClientContext->ucClientStatus)
            {
                CmdStringFormat(ucIndex, pData, &usLen);

                AT_PendClientProc(ucIndex, pData, usLen);
                return ERR_MSP_FAILURE;
            }
        }
        /* 其他通道处于PEND状态或短信状态 */
        else if ((AT_FW_CLIENT_STATUS_PEND == pstClientContext->ucClientStatus)
              || (AT_SMS_MODE == pstClientContext->ucMode))
        {
            /* Added by L60609 for MUX，2012-08-03,  Begin */
            /* 判断本通道以及遍历到的通道是否可以并发 */
            if (VOS_TRUE == AT_IsConcurrentPorts(ucIndex, (VOS_UINT8)i))
            {
                /* 如果是，则继续遍历通道 */
                continue;
            }
            /* Added by L60609 for MUX，2012-08-03,  End */
            else
            {
                /* 如果不是，则缓存该命令 */
                AT_HoldBlockCmd(ucIndex, pData, usLen);
                return ERR_MSP_FAILURE;
            }
        }
        else
        {
        }
    }

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 函 数 名  : AT_DiscardInvalidCharForSms
 功能描述  : +CMGS,+CMGW,+CMGC命令的检查和特殊处理
 输入参数  : TAF_UINT8* pData
             TAF_UINT16 *pusLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_DiscardInvalidCharForSms(TAF_UINT8* pData, TAF_UINT16 *pusLen)
{
    TAF_CHAR   aucCMGSCmd[] = "AT+CMGS=";
    TAF_CHAR   aucCMGWCmd[] = "AT+CMGW=";
    TAF_CHAR   aucCMGCCmd[] = "AT+CMGC=";
    TAF_CHAR   aucTmpCmd[9];
    VOS_INT    iCMGSResult;
    VOS_INT    iCMGWResult;
    VOS_INT    iCMGCResult;

    if (*pusLen < VOS_StrLen(aucCMGSCmd))
    {
        return;
    }

    PS_MEM_CPY(aucTmpCmd, pData, sizeof(aucTmpCmd) - 1);
    At_UpString((TAF_UINT8 *)aucTmpCmd, sizeof(aucTmpCmd) - 1);
    aucTmpCmd[8] = '\0';

    iCMGSResult = VOS_StrCmp(aucCMGSCmd, aucTmpCmd);
    iCMGWResult = VOS_StrCmp(aucCMGWCmd, aucTmpCmd);
    iCMGCResult = VOS_StrCmp(aucCMGCCmd, aucTmpCmd);
    if ((0 != iCMGSResult) && (0 != iCMGWResult)&&(0 != iCMGCResult))
    {
        return;
    }

    /*  MAC系统上的MP后台问题:AT+CMGS=**<CR><^z><Z>(或AT+CMGW=**<CR><^z><Z>)
       为了规避该问题，需要在接收到如上形式的码流后，
       需要将命令后的无效字符<^z><Z>删去  */
    /*lint -e960 Note -- Violates MISRA 2004 Required Rule 4.1, Prohibited escape sequence used (hexadecimal)*/
    if ((ucAtS3 == pData[*pusLen - 3]) && ('\x1a' == pData[*pusLen - 2])
        && (('z' == pData[*pusLen - 1]) || ('Z' == pData[*pusLen - 1])))
    /*lint +e960*/
    {
        /* 删去结尾的<^z><Z>字符 */
        *pusLen -= 2;
    }
    /* MAC系统SFR后台问题: AT+CMGS=<LENGTH><CR><LF><CR>*/
    else if ((ucAtS3 == pData[*pusLen - 3])
          && (ucAtS4 == pData[*pusLen - 2])
          && (ucAtS3 == pData[*pusLen - 1]))
    {
        /* 删去结尾的<LF><CR>字符 */
        *pusLen -= 2;
    }
    /* 判断pData码流的结尾是否为<CR><LF>形式 */
    else if ((ucAtS3 == pData[*pusLen - 2]) && (ucAtS4 == pData[*pusLen - 1]))
    {
        /* 删去结尾的<LF>字符 */
        *pusLen -= 1;
    }
    else
    {
    }

    return;
}



/*****************************************************************************
 函 数 名  : AT_ResetParseVariable
 功能描述  : 重新初始化解析用全局变量
 输出参数  : 无
 返 回 值  : PRIVATE VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : c64416
    修改内容   : 新生成函数

  2.日    期   : 2011年10月28日
    作    者   : o00132663
    修改内容   : AT融合项目，AT参数列表未初始化导致解析失败
*****************************************************************************/
VOS_VOID AT_ResetParseVariable(VOS_VOID)
{
    PS_MEM_SET(&g_stATParseCmd, 0 , sizeof(AT_PARSECMD_STRU));

    PS_MEM_SET(gastAtParaList, 0 , sizeof(gastAtParaList));

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_BUTT;
    g_stATParseCmd.ucCmdFmtType = AT_CMD_TYPE_BUTT;

    gucAtParaIndex = 0;
    return;
}


/*****************************************************************************
 函 数 名  : AT_ParseCmdType
 功能描述  : 根据命令类型解析命令字符串
 输入参数  :  VOS_UINT8 * pData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_ParseCmdType( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT16 usDataTmpLen = usLen - 2;
    VOS_UINT8* pDataTmp = pData + 2;
    VOS_UINT32 ulResult = 0;

    /* 调用的地方保证pData不为空 */

    if(usLen < 2)
    {
        return AT_ERROR;
    }

    if(AT_SUCCESS == At_CheckCharA(*pData))   /* 如果是'A'/'a' */
    {
        if(AT_SUCCESS == At_CheckCharT(*(pData+1)))   /* 如果是'T'/'t' */
        {
            if(2 == usLen)
            {
                return AT_OK;
            }

            if(3 == usLen)
            {
                if(AT_SUCCESS == At_CheckSemicolon(pData[2]))
                {
                    return AT_OK;
                }
            }

            AT_ResetParseVariable();    /* 重置解释器所用的全局变量 */

            pDataTmp = pData + 2;
            usDataTmpLen = usLen - 2;

            /* 非D命令，需要去除命令结尾的';' */
            if(AT_SUCCESS != (At_CheckCharD(*pDataTmp)) && (';' == *(pDataTmp+usDataTmpLen-1)))
            {
                usDataTmpLen--;
            }

            switch(*pDataTmp)      /* 根据第三个字符进行分发 */
            {
            case '^':   /* 扩展命令 */
            case '+':   /* 扩展命令 */
            case '$':   /* 扩展命令 */
                return atParseExtendCmd(pDataTmp, usDataTmpLen);

            case 'd':
            case 'D':   /* D命令 */

                return ParseDCmdPreProc(pDataTmp, usDataTmpLen);

            case 's':
            case 'S':   /* S命令 */
                return atParseSCmd(pDataTmp, usDataTmpLen);

            default:    /*基本命令 */
                {
                    ulResult = atParseBasicCmd(pDataTmp, usDataTmpLen);

                    if(AT_FAILURE == ulResult)
                    {
                        ulResult = AT_ERROR;
                    }

                    return ulResult;
                }
            }
        }
    }

    return AT_ERROR;
}


/*****************************************************************************
 函 数 名  : At_MatchSmsCmdName
 功能描述  : 在SMS命令表中匹配命令名
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : PRIVATE VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2012年9月19日
    作    者   : l00171473
    修改内容   : V7R1C50_At_Abort, 添加短信命令ABORT支持
  3.日    期   : 2012年11月19日
    作    者   : f62575
    修改内容   : DTS2012112010227, 解决短信命令支持多通道并发命令名被覆盖问题；
  4.日    期   : 2013年3月5日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 At_MatchSmsCmdName(VOS_UINT8 ucIndex, VOS_CHAR *pszCmdName)
{
    VOS_UINT32                          i = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    for (i = 0; i < gusAtSmsCmdNum; i++)
    {
        if (VOS_NULL_PTR != (TAF_CHAR*)gastAtSmsCmdTab[i].pszCmdName)
        {
            if (ERR_MSP_SUCCESS == AT_STRCMP(pszCmdName, (TAF_CHAR*)gastAtSmsCmdTab[i].pszCmdName))
            {
                if ( AT_CMGF_MSG_FORMAT_TEXT == pstSmsCtx->enCmgfMsgFormat)
                {
                    g_stCmdElement[ucIndex].pszParam = gastAtSmsCmdTab[i].ParaText;
                }
                else
                {
                    g_stCmdElement[ucIndex].pszParam = gastAtSmsCmdTab[i].ParaPDU;
                }

                g_stCmdElement[ucIndex].ulCmdIndex      = gastAtSmsCmdTab[i].ulCmdIndex;
                g_stCmdElement[ucIndex].pfnSetProc      = gastAtSmsCmdTab[i].pfnSetProc;
                g_stCmdElement[ucIndex].ulSetTimeOut    = gastAtSmsCmdTab[i].ulSetTimeOut;
                g_stCmdElement[ucIndex].pfnQryProc      = NULL;
                g_stCmdElement[ucIndex].ulQryTimeOut    = 0;
                g_stCmdElement[ucIndex].pfnTestProc     = gastAtSmsCmdTab[i].pfnTestProc;
                g_stCmdElement[ucIndex].ulTestTimeOut   = gastAtSmsCmdTab[i].ulTestTimeOut;

                g_stCmdElement[ucIndex].pfnAbortProc    = gastAtSmsCmdTab[i].pfnAbortProc;
                g_stCmdElement[ucIndex].ulAbortTimeOut  = gastAtSmsCmdTab[i].ulAbortTimeOut;

                g_stCmdElement[ucIndex].ulParamErrCode  = gastAtSmsCmdTab[i].ulParamErrCode;
                g_stCmdElement[ucIndex].ulChkFlag       = gastAtSmsCmdTab[i].ulChkFlag;
                g_stCmdElement[ucIndex].pszCmdName      = gastAtSmsCmdTab[i].pszCmdName;

                g_stParseContext[ucIndex].pstCmdElement = &g_stCmdElement[ucIndex];

                return AT_SUCCESS;
            }
        }
    }

    g_stParseContext[ucIndex].pstCmdElement = NULL;

    return AT_FAILURE;
}


/******************************************************************************
 函数名称: atMatchCmdName
 功能描述: 匹配命令名称

 参数说明:
   CmdType [in] 命令类型

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 atMatchCmdName (VOS_UINT8 ucClientId, VOS_UINT32 CmdType)
{
    VOS_UINT32 i = 0;
    /* VOS_UINT32 ulRet = ERR_MSP_FAILURE; */
    HI_LIST_S* me = NULL;
    HI_LIST_S* pCmdTblList = NULL;
    AT_PAR_CMDTBL_LIST_STRU* pstCmdNode = NULL;
    VOS_CHAR *pszCmdName = NULL;

    /* 调用的地方保证输入的指针不为空 */

    pCmdTblList = &(g_stCmdTblList);

    /* 全部格式化为大写字符 */
    if(AT_FAILURE == At_UpString(g_stATParseCmd.stCmdName.aucCmdName,g_stATParseCmd.stCmdName.usCmdNameLen))
    {
        return AT_ERROR;
    }

    pszCmdName = (VOS_CHAR *)g_stATParseCmd.stCmdName.aucCmdName;

    if((AT_EXTEND_CMD_TYPE == CmdType) || (AT_BASIC_CMD_TYPE == CmdType))
    {
        /* 短信命令需要特殊处理 */
        if(ERR_MSP_SUCCESS == At_MatchSmsCmdName(ucClientId, pszCmdName))
        {
            return ERR_MSP_SUCCESS;
        }

        msp_list_for_each(me, pCmdTblList)
        {
            pstCmdNode = msp_list_entry(me, AT_PAR_CMDTBL_LIST_STRU, stCmdTblList);

            for(i = 0; i < pstCmdNode->usCmdNum; i++)
            {
                if((NULL == pstCmdNode->pstCmdElement) || (NULL == pstCmdNode->pstCmdElement[i].pszCmdName))
                {
                    continue;
                }

                if(ERR_MSP_SUCCESS == AT_STRCMP((VOS_CHAR *)pszCmdName, (VOS_CHAR *)pstCmdNode->pstCmdElement[i].pszCmdName))
                {
                    g_stParseContext[ucClientId].pstCmdElement = &(pstCmdNode->pstCmdElement[i]);

                    return ERR_MSP_SUCCESS;
                }
            }
        }
    }

    return AT_CMD_NOT_SUPPORT;
}


/******************************************************************************
 函数名称: ParseParam
 功能描述: 解析参数

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ParseParam(AT_PAR_CMD_ELEMENT_STRU* pstCmdElement)
{
    VOS_UINT32 ulParaLen = 0;

    if(AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType)
    {
        if((NULL != pstCmdElement) && (NULL != pstCmdElement->pszParam))
        {
            ulParaLen = AT_STRLEN((VOS_CHAR *)pstCmdElement->pszParam);  /* 获取参数脚本长度 */
            if(AT_SUCCESS != atParsePara((VOS_UINT8*)pstCmdElement->pszParam,(VOS_UINT16)ulParaLen))  /* 参数匹配 */
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }
    }

    return ERR_MSP_SUCCESS;
}


AT_RRETURN_CODE_ENUM_UINT32 fwCmdTestProc(VOS_UINT8 ucIndex, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

    /* 调用的地方保证指针不为空 */

    if(NULL != pstCmdElement->pfnTestProc)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)pstCmdElement->pfnTestProc(ucIndex);

        if(AT_WAIT_ASYNC_RETURN == ulResult)
        {
            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

            /* 开定时器 */
            if(AT_SUCCESS != At_StartTimer(pstCmdElement->ulTestTimeOut, ucIndex))
            {
                return AT_ERROR;
            }

            At_SetAtCmdAbortTickInfo(ucIndex, VOS_GetTick());
        }

        return ulResult;
    }
    else if(NULL != pstCmdElement->pszParam)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
           (TAF_CHAR*)pgucAtSndCodeAddr, (TAF_CHAR*)pgucAtSndCodeAddr,
           "%s: %s", pstCmdElement->pszCmdName, pstCmdElement->pszParam);

        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}


/******************************************************************************
 函数名称: atCmdDispatch
 功能描述: 命令分发

 参数说明:
   ucClientId [in] client id

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
AT_RRETURN_CODE_ENUM_UINT32 atCmdDispatch (VOS_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;
    PFN_AT_FW_CMD_PROC pfnCmdProc = NULL;
    VOS_UINT32 ulTimerLen = 0;
    AT_PAR_CMD_ELEMENT_STRU* pstCmdElement = g_stParseContext[ucIndex].pstCmdElement;

    switch (g_stATParseCmd.ucCmdOptType)
    {
    case AT_CMD_OPT_SET_PARA_CMD:
    case AT_CMD_OPT_SET_CMD_NO_PARA:
        pfnCmdProc = pstCmdElement->pfnSetProc;          /* 设置无参数命令 */
        ulTimerLen = pstCmdElement->ulSetTimeOut;
        break;

    case AT_CMD_OPT_READ_CMD:
        pfnCmdProc = pstCmdElement->pfnQryProc;          /* 查询参数 */
        ulTimerLen = pstCmdElement->ulQryTimeOut;
        break;

    case AT_CMD_OPT_TEST_CMD:
        return fwCmdTestProc(ucIndex, pstCmdElement);         /* 测试参数 */

    default:
        return AT_ERROR;                        /* 其它情况，则返回错误 */
    }

    if(NULL == pfnCmdProc)
    {
        return AT_ERROR;
    }

    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)pfnCmdProc(ucIndex);

    if(AT_WAIT_ASYNC_RETURN == ulResult)
    {
        /* 开定时器 */
        if(AT_SUCCESS != At_StartTimer(ulTimerLen, ucIndex))
        {
            return AT_ERROR;
        }

        At_SetAtCmdAbortTickInfo(ucIndex, VOS_GetTick());

        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    }

    return ulResult;
}


/*****************************************************************************
 函 数 名  : LimitedCmdProc
 功能描述  : 命令受限查询和处理
 输入参数  : VOS_UINT8 ucClientId
             VOS_UINT8 *pData
             VOS_UINT16 usLen
             AT_PAR_CMD_ELEMENT_STRU* pstCmdElement
 输出参数  : 无
 返 回 值  : AT_OK      : 表示受限条件不满足，需要继续处理
             AT_ERROR   : 表示受限条件满足，需要返回ERROR
             AT_SUCCESS : 表示DOCK命令转发到E5通道处理，不需要返回应答
             其他       : 特定错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月10日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  3.日    期   : 2012年04月07日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012032702424,打开对DOCK命令的支持
*****************************************************************************/
VOS_UINT32 LimitedCmdProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement)
{
    VOS_BOOL bE5CheckRight = VOS_TRUE;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

    if(NULL == pstCmdElement)
    {
        return AT_ERROR;
    }


     /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */

    /* 如果E5密码保护受限，则调用查询E5受限条件接口，受限的话返回AT_ERROR，否则返回AT_OK */
    if(0 == (pstCmdElement->ulChkFlag & CMD_TBL_E5_IS_LOCKED))
    {
        /* 非AT通道 非WIFI通道, 均不需密码保护 */
        if ( (AT_USBCOM_USER != gastAtClientTab[ucClientId].UserType)
          && (AT_SOCK_USER != gastAtClientTab[ucClientId].UserType)
          && (AT_APP_SOCK_USER != gastAtClientTab[ucClientId].UserType))
        {
            /* 继续进行PIN码保护的检查 */
        }
        else
        {
            bE5CheckRight = AT_E5CheckRight(ucClientId, pData, usLen);
            if(VOS_TRUE == bE5CheckRight)
            {
                /* E5已解锁，继续进行PIN码保护的检查 */
            }
            else
            {
                return AT_SUCCESS;  /* AT_E5CheckRight 内部已返回上报结果 */
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* 如果是E5 DOCK命令，则直接调用DOCK命令转发接口，返回AT_SUCCESS */
    if(pstCmdElement->ulChkFlag & CMD_TBL_IS_E5_DOCK)
    {
        if (AT_USBCOM_USER == gastAtClientTab[ucClientId].UserType)
        {
            ulResult = (AT_RRETURN_CODE_ENUM_UINT32)AT_DockHandleCmd(ucClientId, pData, usLen);
            if(AT_SUCCESS == ulResult)
            {
                return AT_SUCCESS;  /* 命令内容已转发到E5通道，本通道不返回任何结果 */
            }
            else
            {
                return AT_ERROR;    /* 处理失败，返回ERROR */
            }
        }
    }

    /* 如果PIN码保护受限，则调用查询PIN码受限条件接口，受限的话返回AT_ERROR，否则返回AT_OK */
    if(0 == (pstCmdElement->ulChkFlag & CMD_TBL_PIN_IS_LOCKED))
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_CheckUsimStatus((VOS_UINT8*)pstCmdElement->pszCmdName, ucClientId);
        if(AT_SUCCESS == ulResult)
        {
            /* PIN码已解锁，继续后续的检查处理 */
        }
        else
        {
            return ulResult;    /* 返回具体锁定的原因值 */
        }
    }


    return AT_OK;
}

/*****************************************************************************
 函 数 名  : CmdParseProc
 功能描述  : 命令解析处理
 输入参数  : VOS_UINT8 ucClientId
              VOS_UINT8 *pDataIn
             VOS_UINT16 usLenIn
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CmdParseProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;
    AT_PAR_CMD_ELEMENT_STRU* pstCmdElement = NULL;

    /* 该函数调用处可保证ucClientId的合法性，pDataIn不为空 */


    /* 匹配命令名称 */
    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)atMatchCmdName(ucClientId, g_stATParseCmd.ucCmdFmtType);
    if(ERR_MSP_SUCCESS != ulResult)
    {
        /* HAL_DIAG_SDM_FUN(EN_SDM_AT_FW_PARSE_FAILURE, 6, 0, 0); */
        return ulResult;
    }

    pstCmdElement = g_stParseContext[ucClientId].pstCmdElement;

    if(NULL == pstCmdElement)
    {
        return AT_ERROR;
    }

    /* 受限命令判断和处理接口，返回失败表示处于受限条件，直接返回错误码 */
    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)LimitedCmdProc(ucClientId, pData, usLen, pstCmdElement);
    if(AT_OK != ulResult)
    {
        return ulResult;
    }

    /* 匹配解析参数 */
    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)ParseParam(pstCmdElement);

    if(ERR_MSP_SUCCESS != ulResult)
    {
        /* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
        if(AT_CMD_SD == pstCmdElement->ulCmdIndex)
        {
            return AT_SDParamErrCode();
        }
       /* Add by w00199382 for V7代码同步, 2012-04-07, End   */

        /* HAL_DIAG_SDM_FUN(EN_SDM_AT_FW_PARSE_FAILURE, 7, 0, 0); */
        if(AT_RRETURN_CODE_BUTT == pstCmdElement->ulParamErrCode)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            return (AT_RRETURN_CODE_ENUM_UINT32)(pstCmdElement->ulParamErrCode);
        }
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 下发的AT命令是否与CL模式下需要保护的AT命令相匹配，匹配的话，直接返回操作不允许 */
    if (VOS_TRUE == At_CheckCurrRatModeIsCL(ucClientId))
    {
        if (VOS_TRUE == atCmdIsSupportedByCLMode(ucClientId))
        {
            return AT_CME_OPERATION_NOT_ALLOWED_IN_CL_MODE;
        }
    }
#endif

    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)atCmdDispatch(ucClientId);

    return ulResult;
}


/*****************************************************************************
 函 数 名  : RepeatCmdProc
 功能描述  : A/命令的处理
 输入参数  : VOS_UINT8 ucClientId
             AT_FW_CLIENT_CONTEXT_STRU* pstClientContext
             AT_FW_CLIENT_CMD_CTRL_STRU* pstCmdfmtCtrl
 输出参数  : 无
 返 回 值  : PRIVATE VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RepeatCmdProc(AT_PARSE_CONTEXT_STRU* pstClientContext)
{
    VOS_UINT8* pData = pstClientContext->aucDataBuff;
    VOS_UINT32 ulLen = pstClientContext->usDataLen;

    if(ucAtS4 == *pData)
    {
        pData++;
        ulLen--;
    }

    /* 检查是否是"A/" */
    if(3 == ulLen)
    {
        if(AT_SUCCESS == At_CheckCharA(*pData))
        {
            if(AT_SUCCESS == atCheckChar0x2f(*(pData+1)))
            {
                if(0 == pstClientContext->usCmdLineLen)
                {
                    pstClientContext->usDataLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pstClientContext->aucDataBuff,
                        (VOS_CHAR *)pstClientContext->aucDataBuff, "AT%c", ucAtS3);
                }
                else
                {
                   PS_MEM_CPY(pstClientContext->aucDataBuff, (VOS_UINT8*)pstClientContext->pucCmdLine,
                        pstClientContext->usCmdLineLen);

                   pstClientContext->usDataLen = pstClientContext->usCmdLineLen;
                }
            }
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : SaveRepeatCmd
 功能描述  : 保存当前命令字符串
 输入参数  : pstClientContext : 解析器上下文
             pData            : AT命令字符串
             usLen            : AT命令字符串长度
 输出参数  : 无
 返 回 值  : PRIVATE VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月6日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SaveRepeatCmd(AT_PARSE_CONTEXT_STRU* pstClientContext, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    /* 保存A/命令缓存 */
    if(NULL != pstClientContext->pucCmdLine)
    {
        AT_FREE(pstClientContext->pucCmdLine);
    }

    pstClientContext->pucCmdLine = (VOS_UINT8 *)AT_MALLOC(usLen);
    if(NULL == pstClientContext->pucCmdLine)
    {
        return;
    }

    PS_MEM_CPY(pstClientContext->pucCmdLine, pData, usLen);
    pstClientContext->usCmdLineLen = usLen;

    return;
}


/******************************************************************************
 函数名称: ScanDelChar
 功能描述: 扫描退格符

 参数说明:
   pData [in/out] 字符串内容
   pLen [in/out] 字符串长度
   AtS5 [in] 退格符

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ScanDelChar( VOS_UINT8 *pData, VOS_UINT16 *pLen, VOS_UINT8 AtS5)
{
    VOS_UINT16 usChkLen  = 0;
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = pData;
    VOS_UINT8  *pRead    = pData;
    VOS_UINT16 usNum     = 0;    /* 记录逗号的个数 */

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* 输入参数检查 */
    while ( usChkLen++ < *pLen )
    {
        if('"' == *pRead)
        {
            usNum++;
            *pWrite++ = *pRead;
            usLen++;
        }
        else if((AtS5 == *pRead) && (0 == (usNum%2)))       /*删除上一字符,引号内的删除符不处理*/
        {
            if( usLen > 0 )
            {
                pWrite--;
                usLen--;
            }
        }
        else                        /*选择有效字符*/
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}


/******************************************************************************
 函数名称: ScanCtlChar
 功能描述: 扫描控制符(去除字符串中小于0x20的字符)

 参数说明:
   pData [in/out] 字符串内容
   pLen [in/out] 字符串长度

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ScanCtlChar( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT8  *pWrite    = pData;
    VOS_UINT8  *pRead     = pData;
    VOS_UINT16 usChkLen   = 0;
    VOS_UINT16 usLen      = 0;
    VOS_UINT16 usNum      = 0;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* Added by c64416 for 引号中的控制字符不删除, DTS2011120903650 2011/12/21, begin */
    while( usChkLen++ < *pLen )
    {
        if( 0x20 <= *pRead )   /* 选择有效字符 */
        {
            if('"' == *pRead)
            {
                usNum++;
            }
            *pWrite++ = *pRead;
            usLen++;
        }
        else
        {
            if(usNum%2)            /* 双引号内的小于0x20的字符不去除 */
            {
                *pWrite++ = *pRead;
                usLen++;
            }
        }
        pRead++;
    }
    /* Added by c64416 for 引号中的控制字符不删除, DTS2011120903650 2011/12/21, end */

    *pLen  =  usLen;
    return AT_SUCCESS;
}


/******************************************************************************
 函数名称: ScanBlankChar
 功能描述: 扫描引号外空格符

 参数说明:
   pData [in/out] 字符串内容
   pLen [in/out] 字符串长度

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ScanBlankChar( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    /* VOS_UINT8  *pCheck        = pData; */
    VOS_UINT8  *pWrite        = pData;
    VOS_UINT8  *pRead         = pData;
    VOS_UINT16 usChkLen       = 0;
    VOS_UINT16 usLen          = 0;
    VOS_UINT16 usColonBankCnt = 0;
    VOS_BOOL bIsColonBack  = FALSE;
    VOS_BOOL bIsEqual      = FALSE;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

#if 0
    /* 检查引号 */
    while( usQoutNum ++ < *pLen )
    {
        if('"' == *pCheck++)
        {
            ulChkQout++;
        }
    }

    if(1 == (ulChkQout % 2))
    {
        return AT_FAILURE;
    }
#endif

    /* 检查 */
    while( usChkLen++ < *pLen )
    {
        if('=' == *pRead)
        {
            bIsEqual = TRUE;
        }

        if((' ' == *pRead) && (TRUE != bIsEqual))
        {
            /* 等号前的空格去除 */
        }
        else    /* rim逗号前后的空格 */
        {
            if(0x20 != *pRead && ',' != *pRead)
            {
                /* rim','后空格 */
                if(bIsColonBack)
                {
                    pWrite -= usColonBankCnt;
                    usLen  -= usColonBankCnt;
                    usColonBankCnt = 0;
                    bIsColonBack   = FALSE;
                }
                else
                {
                    usColonBankCnt = 0;
                }
            }
            else if(',' == *pRead)
            {
                /* rim','前空格 */
                pWrite -= usColonBankCnt;
                usLen  -= usColonBankCnt;
                usColonBankCnt = 0;
                bIsColonBack   = TRUE;
            }
            else
            {
                usColonBankCnt++;
            }

            *pWrite++ = *pRead;
            usLen++;
        }

        pRead++;
    }

    pWrite -= usColonBankCnt;
    usLen  -= usColonBankCnt;

    *pLen  =  usLen;
    return AT_SUCCESS;
}


/*****************************************************************************
 函 数 名  : ScanBlankCharAfterEq
 功能描述  : 删除紧挨着等号后面的空格,ScanBlankChar函数的补丁函数
 输入参数  : IN OUT U8_T *pData
             IN OUT U16_T *pLen
 输出参数  : 无
 返 回 值  : PRIVATE U32_T

 修改历史      :
  1.日    期   : 2012年10月15日
    作    者   : c64416
    修改内容   : DTS2012102905864, 新生成函数

*****************************************************************************/
PRIVATE VOS_UINT32 ScanBlankCharAfterEq(IN OUT VOS_UINT8 *pData,IN OUT VOS_UINT16 *pLen)
{
    VOS_UINT8  *pWrite        = pData;
    VOS_UINT8  *pRead         = pData;
    VOS_UINT16 usChkLen       = 0;
    VOS_UINT16 usLen          = 0;
    VOS_BOOL   bIsEqual      = FALSE;
    VOS_BOOL   bIsEqualNoSp  = FALSE;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* 检查 */
    while( usChkLen++ < *pLen )
    {
        if('=' == *pRead)
        {
            bIsEqual = TRUE;
        }
        else
        {
            if((TRUE != bIsEqual) || (TRUE == bIsEqualNoSp))
            {
                /* 等号前的字符全部复制，等号后的非空格字符全部复制 */
            }
            else
            {
                if(' ' == *pRead)
                {
                    pRead++;
                    continue;
                }
                else
                {
                    bIsEqualNoSp = TRUE;
                }
            }
        }

        *pWrite++ = *pRead;
        usLen++;

        pRead++;
    }

    *pLen  =  usLen;
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_FormatCmdStr
 Description    : 格式化命令字符串
 Input          : pData --- 字符串
                  pLen  --- 长度地址
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期   : 2008年12月8日
    作    者   : o00132663
    修改内容   : AT2D07342, AT命令增加对双字节ASCII编码的支持。
*****************************************************************************/
VOS_UINT32 FormatCmdStr (VOS_UINT8 *pData, VOS_UINT16 *pLen, VOS_UINT8 AtS3)
{
    VOS_UINT8  *pCheck    = pData;
    VOS_UINT32 ulChkS3Len = 0;
    VOS_UINT32 ulFlg      = 0;
    VOS_UINT16 usLen      = 0;

    /* 保留行结束符之前的字符 */
    while ( ulChkS3Len++ < *pLen  )
    {
        if(AtS3 == *pCheck++)
        {
            ulFlg = 1;
            break;
        }
        else
        {
            /* *pCheck &= 0x7f; */   /* 忽略每个字节的最高bit位 */
            usLen++;
        }
    }

    if( 1 !=  ulFlg )
    {
        return AT_FAILURE;
    }
    else
    {
        *pLen  =  usLen;
        return AT_SUCCESS;
    }
}

/*****************************************************************************
 函 数 名  : AT_DiscardInvalidChar
 功能描述  : 过滤出现在"AT"之前的误码
 输入参数  : VOS_UINT8* pData
             VOS_UINT16 *pusLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月2日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2011年12月2日
   作    者   : 崔军强/00064416
   修改内容   : 程序效率优化

*****************************************************************************/
VOS_UINT32  AT_DiscardInvalidChar(VOS_UINT8* pucData, VOS_UINT16 *pusLen)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usLen;

    /*DTS2011122400231 AT命令最大长度限制修改 : h00135900 start in 2011-12-24*/
    if ((*pusLen == 0) || (AT_CMD_MAX_LEN < *pusLen))
    {
        (VOS_VOID)vos_printf("AT_DiscardInvalidChar: usLen > AT_CMD_MAX_LEN or usLen = 0. usLen :%d", *pusLen);
        return ERR_MSP_FAILURE;
    }
    /*DTS2011122400231 AT命令最大长度限制修改 : h00135900 end in 2011-12-24*/
    for(i = 0; i < (*pusLen); i++)
    {
        if(AT_SUCCESS != At_CheckCharA(pucData[i]))
        {
            continue;
        }
        else if(AT_SUCCESS != At_CheckCharT(pucData[i+1]))
        {
            continue;
        }
        else
        {
            if (0 != i)
            {
                usLen = (*pusLen - i);
                PS_MEM_CPY(pucData, (pucData+i), usLen);
                *pusLen = usLen;
            }

            return ERR_MSP_SUCCESS;
        }
    }

    return ERR_MSP_FAILURE;
}


/******************************************************************************
 函数名称: CmdStringFormat
 功能描述: 格式化命令字符串

 参数说明:
   ucClientId [in] client id
   pData [in/out] 字符串内容
   pusLen [in/out] 字符串长度

 作    者: 崔军强/00064416 [2011-04-01]
  2.日    期   : 2012年10月31日
    作    者   : c64416
    修改内容   : DTS2012102905864
******************************************************************************/
VOS_UINT32 CmdStringFormat(VOS_UINT8 ucClientId, VOS_UINT8 *pData,VOS_UINT16* pusLen)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;

    ulRet = FormatCmdStr(pData,pusLen, ucAtS3);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    /* 扫描退格符 */
    ulRet = ScanDelChar(pData,pusLen, ucAtS5);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    /* 扫描控制符 */
    ulRet = ScanCtlChar(pData,pusLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    /* 扫描空格符 */
    ulRet = ScanBlankChar(pData,pusLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    /* 扫描紧挨着等号后面的空格符 */
    ulRet = ScanBlankCharAfterEq(pData,pusLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    return ERR_MSP_SUCCESS;
}
/*****************************************************************************
 函 数 名  : CheckAnyCharCmdName
 功能描述  : 匹配任意字符参数命令的名称
 输入参数  : VOS_UINT8 *pData
             VOS_UINT16* usLen
             VOS_UINT8 *plName
             VOS_UINT8 *pbName
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL CheckAnyCharCmdName(VOS_UINT8 *pData, VOS_UINT16* pusLen, VOS_UINT8 *plName, VOS_UINT8 *pbName)
{
    VOS_UINT16 i;
    VOS_UINT8  bFound   = 0;      /* check if found string ANY CHAR CMD */
    VOS_UINT8  ucOffset = 0;
    VOS_UINT8* pHeader = pData;   /* remember the header of the pointer */

    for(i=0; i < *pusLen; i++,pHeader++)
    {
        if (' ' == *pHeader)
        {
            continue;          /* skip space char */
        }
        else if ((plName[ucOffset] == *pHeader) || (pbName[ucOffset] == *pHeader))
        {
            ucOffset++;

            if ('?' == plName[ucOffset])
            {
                bFound = 1;    /* found string ANY CHAR CMD  */
            }
        }
        else
        {
            break;             /* not ANY CHAR CMD, go out */
        }
    }

    if (bFound)
    {
        if ((VOS_StrLen((VOS_CHAR *)plName) - 1) == ucOffset)
        {                          /* found string ANY CHAR CMD */
            *pusLen -= i;            /* remove string "AT^CPBW=" */
            PS_MEM_MOVE(pData, pData+i, *pusLen);
            return TRUE;
        }
    }

    return FALSE;
}

/*****************************************************************************
 函 数 名  : AnyCharCmdParse
 功能描述  : 任意字符参数命令解析
 输入参数  : VOS_UINT8* pData
             VOS_UINT16 usLen
             VOS_UINT8* pName
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AnyCharCmdParse(VOS_UINT8* pData, VOS_UINT16 usLen, VOS_UINT8* pName)
{
    VOS_UINT16 i,j;
    VOS_UINT8  bInQoute = 0;

    VOS_UINT8  aucPara[AT_PARA_MAX_LEN + 1]  = {0};     /* 用来放置解析出的参数字符串 */
    VOS_UINT16 usParaLen                     = 0;       /* 用来标识参数字符串长度 */

    AT_ResetParseVariable();    /* 重置解释器所用的全局变量 */

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* 设置命令操作类型*/
    g_stATParseCmd.ucCmdFmtType = AT_EXTEND_CMD_TYPE;       /* 设置命令类型*/

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)pName) - 2;    /* 命令名 ^CPBW 长度*/

    PS_MEM_CPY(g_stATParseCmd.stCmdName.aucCmdName, pName, g_stATParseCmd.stCmdName.usCmdNameLen);

    /* ^CPBW=[<index>][,<number>[,<type>[,<text>,<coding>]]] */
    /* ^SCPBW= (1-65535),(numa),(0-255),(numb),(0-255),(numc),(0-255),(numd),(0-255),(text),(0,1),(email)*/
    /* +CPBW=[<index>][,<number>[,<type>[,<text>]]] */

    /* seperate para by char ',' */
    for(i=0; i < usLen; i++,pData++)
    {
        if ((' ' == *pData) && (0 == bInQoute))
        {
            continue;          /* skip space char not in quatation*/
        }
        else if (',' == *pData)
        {
            if (bInQoute)
            {
                if (1 == bInQoute)
                {
                    /* 表明该','号是参数的一部分，而非参数分隔符 */
                    aucPara[usParaLen] = *pData;
                    usParaLen++;

                    continue;
                }

                bInQoute = 0;      /* 双引号内可能还有双引号，不能再根据第二个双引号认为字符串结束 , 以参数分割符','作为字符串结束符。*/

                /* 处理以下异常 : 在字符串后面，','前面的无效空格 */
                for(j=usParaLen-1; j>0; j--)
                {
                    if(' ' == aucPara[j])
                    {
                        usParaLen --;
                    }
                    else if ('"' == aucPara[j])
                    {
                        break;
                    }
                    else
                    {
                        return AT_CME_INCORRECT_PARAMETERS;    /* 最后一个双引号后面有其它字符，返回错误 */
                    }
                }
            }

            if(i < (usLen-1))
            {
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(aucPara, usParaLen))
                {
                    return AT_ERROR;
                }

                usParaLen = 0;

                /* too many para */
            }

            continue;
        }
        else
        {
            /* 存储参数到全局变量中 */
            aucPara[usParaLen] = *pData;
            usParaLen++;

            if ('"' == *pData)
            {
                bInQoute++;
            }
        }
    }

    if(ERR_MSP_SUCCESS != atfwParseSaveParam(aucPara, usParaLen))
    {
        return AT_ERROR;
    }

    return AT_SUCCESS;
}


/*****************************************************************************
 函 数 名  : AnyCharCmdProc
 功能描述  : 支持任意字符的字符串参数的命令的处理
            (来自V3R1的需求，此类命令不支持组合命令)
 输入参数  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AnyCharCmdProc(VOS_UINT8 *pData, VOS_UINT16* pusLen)
{
    VOS_UINT16 i;
    VOS_UINT32 ulRet = 0;
    VOS_UINT8  ucCmdName_lowercase[3][16]={"at^cpbw=?", "at+cpbw=?", "at^scpbw=?"};
    VOS_UINT8  ucCmdName_uppercase[3][16]={"AT^CPBW=?", "AT+CPBW=?", "AT^SCPBW=?"};

    for(i = 0; i < 3; i++)
    {
        if(TRUE == CheckAnyCharCmdName(pData, pusLen, ucCmdName_lowercase[i], ucCmdName_uppercase[i]))
        {
            ulRet = FormatCmdStr(pData,pusLen, ucAtS3);
            if(ERR_MSP_SUCCESS != ulRet)
            {
                return AT_ERROR;
            }

            return AnyCharCmdParse(pData, *pusLen, &(ucCmdName_uppercase[i][2]));
        }
    }

    return AT_FAILURE;
}



/*****************************************************************************
 函 数 名  : At_ReadyClientCmdProc
 功能描述  : Ready状态的通道的命令处理
 输入参数  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2011年12月2日
    作    者   : L00171473
    修改内容   : 过滤出现在"AT"之前的误码
*****************************************************************************/
VOS_VOID At_ReadyClientCmdProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32 ulRet                           = ERR_MSP_FAILURE;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult         = AT_WAIT_ASYNC_RETURN;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;

    if(usLen < 3)
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    SaveRepeatCmd(pClientContext, pData, usLen);

    At_ResetCombinParseInfo(ucIndex);

    /* Modified by l00171473 for DTS2011120801675 UART通道校准 , 2011-12-3, begin */
    ulRet = AT_DiscardInvalidChar(pData, &usLen);
    if (ERR_MSP_SUCCESS != ulRet)
    {
        return ;
    }
    /* Modified by l00171473 for DTS2011120801675 UART通道校准 , 2011-12-3, end */

    ulRet = AnyCharCmdProc(pData, &usLen);

    if(AT_SUCCESS == ulRet)     /* 是任意字符参数的命令 */
    {
        /* 命令处理 */
        ulRet = CmdParseProc(ucIndex, pData, usLen);
        if((AT_OK != ulRet) && (AT_WAIT_ASYNC_RETURN != ulRet))
        {
            At_ResetCombinParseInfo(ucIndex);
        }

        At_FormatResultData(ucIndex, ulRet);

        return ;
    }
    else if(AT_FAILURE != ulRet)    /* 是任意字符参数的命令，但参数解析失败 */
    {
        At_FormatResultData(ucIndex, ulRet);

        return;
    }
    else    /* 不是任意字符参数的命令 */
    {
        /* do nothing */
    }

    ulRet = CmdStringFormat(ucIndex, pData, &usLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        At_FormatResultData(ucIndex, ulRet);

        return;
    }

    /* 根据V3R1要求，前两个字符不是"AT"，不返回任何信息 */
    if(AT_SUCCESS != At_CheckCharA(*pData))   /* 如果不是'A'/'a' */
    {
        return;
    }

    if(AT_SUCCESS != At_CheckCharT(*(pData+1)))   /* 如果不是'T'/'t' */
    {
        return;
    }

    /* SIMLOCK命令可能有61个参数，特殊处理 */
    if (AT_SUCCESS == At_ProcSimLockPara(ucIndex, pData, usLen))
    {
        return;
    }

    /* ^DOCK命令后面还有"^"和"="，特殊处理 */
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (AT_SUCCESS == AT_HandleDockSetCmd(ucIndex, pData, usLen))
    {
        return;
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* AP-Modem形态下，产线命令AT^FACAUTHPUBKEY和AT^SIMLOCKDATAWRITE的设置命令，参数已经超过了解析器中
       参数长度上限512，需要特殊处理*/
    if (AT_SUCCESS == At_HandleApModemSpecialCmd(ucIndex, pData, usLen))
    {
        return;
    }

    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_CombineCmdChkProc(ucIndex, pData, usLen);

    /* 返回结果 */
    if((AT_FAILURE == ulResult) || (AT_SUCCESS == ulResult))
    {
        return ;
    }

    if(AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return;
}


/*****************************************************************************
 函 数 名  : atCmdMsgProc
 功能描述  : 命令处理
 输入参数  : VOS_UINT8 ucClientId
              VOS_UINT8 *pDataIn
             VOS_UINT16 usLenIn
 输出参数  : 无
 返 回 值  : PRIVATE VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : c64416
    修改内容   : 新生成函数
  2.日    期   : 2012年06月28日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目，增加AT_XML_MODE子模式的处理
  3.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  5.日    期   : 2013年2月20日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_VOID atCmdMsgProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32                          ulRet = ERR_MSP_FAILURE;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_WAIT_ASYNC_RETURN;
    AT_PARSE_CONTEXT_STRU              *pClientContext = NULL;
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    if ((0 == usLen) || (AT_CMD_MAX_LEN < usLen))
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    if (AT_SMS_MODE == pClientContext->ucMode)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_SmsProc(ucIndex, pData, usLen);

        if ((AT_SUCCESS == ulResult)
         || (AT_WAIT_SMS_INPUT == ulResult))
        {
            At_FormatResultData(ucIndex,ulResult);
            return ;
        }

        gastAtClientTab[ucIndex].usSmsTxtLen = 0;   /* 短信BUFFER清空 */

        At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);         /* 置回命令状态 */

        if (AT_WAIT_ASYNC_RETURN == ulResult)
        {
            if (NULL != pClientContext->pstCmdElement)
            {
                /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
                if (AT_SUCCESS != At_StartTimer(pClientContext->pstCmdElement->ulSetTimeOut, ucIndex))
                {
                    AT_ERR_LOG("atCmdMsgProc():ERROR:Start Timer Failed");
                }
                /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

                pClientContext->ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
            }
            return;
        }

        At_FormatResultData(ucIndex,ulResult);
        return;
    }
    else if (AT_XML_MODE == pClientContext->ucMode)
    {
        /* 调用XML输入处理函数 */
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_ProcXmlText(ucIndex, pData, usLen);

        /* 处理成功，输出提示符">" */
        if (AT_WAIT_XML_INPUT == ulResult)
        {
            At_FormatResultData(ucIndex,ulResult);
            return;
        }

        /* 清空缓存区 */
        PS_MEM_FREE(WUEPS_PID_AT, pstAgpsCtx->stXml.pcXmlTextHead);                         /* XML BUFFER清空 */
        pstAgpsCtx->stXml.pcXmlTextHead = VOS_NULL_PTR;
        pstAgpsCtx->stXml.pcXmlTextCur  = VOS_NULL_PTR;

        At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);                           /* 置回命令状态 */

        if (AT_WAIT_ASYNC_RETURN == ulResult)
        {
            if (NULL != pClientContext->pstCmdElement)
            {
                if (AT_SUCCESS != At_StartTimer(pClientContext->pstCmdElement->ulSetTimeOut, ucIndex))
                {
                    AT_ERR_LOG("atCmdMsgProc():ERROR:Start Timer Failed");
                }

                pClientContext->ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
            }
            return;
        }

        At_FormatResultData(ucIndex,ulResult);
        return;
    }
    else
    {
    }

    /* 避免组合命令处理过程中其他通道有命令输入 */
    ulRet = AT_ParseCmdIsComb(ucIndex, pData, usLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return;
    }

    /* 判断是否有PEND状态的通道 */
    ulRet = AT_ParseCmdIsPend(ucIndex, pData, usLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return;
    }

    At_ReadyClientCmdProc(ucIndex, pData, usLen);

    return ;
}


/*****************************************************************************
 函 数 名  : At_CmdStreamRcv
 功能描述  : AT命令字符串的预处理
 输入参数  : VOS_UINT8 ucIndex
             VOS_UINT8* pData
             VOS_UINT16 usLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_CmdStreamRcv(VOS_UINT8 ucIndex, VOS_UINT8* pData, VOS_UINT16 usLen)
{
    VOS_UINT8* pHead = NULL;
    VOS_UINT16 usCount = 0;  /* 当前指向的字符位置 */
    VOS_UINT16 usTotal = 0;  /* 已经处理的字符个数 */
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    /* ucIndex只检查一次，后续的子函数不再检查 */
    if((NULL == pData) || (ucIndex >= AT_MAX_CLIENT_NUM))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    pstClientContext = &(g_stParseContext[ucIndex]);

    pHead = pData;

    /* 行结束符(<CR>或者用户指定) */
    while(usCount++ < usLen)
    {
        /*lint -e960 Note -- Violates MISRA 2004 Required Rule 4.1, Prohibited escape sequence used (hexadecimal)*/
        if(At_CheckCmdSms(*(pData+usCount-1), pstClientContext->ucMode))
        /*lint +e960*/
        {
            /* 缓存中已经有数据 */
            if(pstClientContext->usDataLen > 0)
            {
                if((pstClientContext->usDataLen + usCount) >= AT_CMD_MAX_LEN)
                {
                    pstClientContext->usDataLen = 0;
                    return ERR_MSP_INSUFFICIENT_BUFFER;
                }

                PS_MEM_CPY(&pstClientContext->aucDataBuff[pstClientContext->usDataLen], pHead, usCount);
                pstClientContext->usDataLen += usCount;
            }
            else    /* 缓存中无数据 */
            {
                PS_MEM_CPY(&pstClientContext->aucDataBuff[0], pHead, (VOS_SIZE_T)(usCount-usTotal));
                pstClientContext->usDataLen = usCount-usTotal;
            }

            RepeatCmdProc(pstClientContext);

            atCmdMsgProc(ucIndex, pstClientContext->aucDataBuff, pstClientContext->usDataLen);

            pHead = pData+usCount;
            usTotal = usCount;
            pstClientContext->usDataLen = 0;
        }
    }

    /* 有部分字符未处理，需要缓存 */
    if(usTotal < usLen)
    {
        if((pstClientContext->usDataLen + (usLen-usTotal)) >= AT_CMD_MAX_LEN)
        {
            pstClientContext->usDataLen = 0;
            return ERR_MSP_INSUFFICIENT_BUFFER;
        }

        PS_MEM_CPY(&pstClientContext->aucDataBuff[pstClientContext->usDataLen],pHead,(VOS_UINT32)(usLen-usTotal));

        pstClientContext->usDataLen += (VOS_UINT16)(usLen-usTotal); /* (pData-pHead+ulLen); */
    }

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 函 数 名  : At_CombineBlockCmdProc
 功能描述  : 组合命令和缓存命令的处理
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID At_CombineBlockCmdProc(VOS_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_WAIT_ASYNC_RETURN;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo = NULL;
    VOS_UINT8* pucBlockCmd = NULL;
    VOS_UINT16 usBlockCmdLen = 0;

    if(ucIndex >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    pstCombineCmdInfo = &pClientContext->stCombineCmdInfo;

    /* 判断组合命令是否处理完毕 */
    if((pstCombineCmdInfo->usProcNum < pstCombineCmdInfo->usTotalNum))
    {
        /* 处理下一条命令 */
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_CombineCmdProc(ucIndex);

        /* 返回结果 */
        if((AT_FAILURE == ulResult) || (AT_SUCCESS == ulResult))
        {
            return ;
        }

        if(AT_WAIT_ASYNC_RETURN != ulResult)
        {
            At_FormatResultData(ucIndex, ulResult);
        }

        return ;
    }

    /* 判断是否有缓存的命令 */
    ucIndex = AT_BlockCmdCheck();
    if(ucIndex < AT_MAX_CLIENT_NUM)
    {
        pClientContext = &(g_stParseContext[ucIndex]);

        /* 停止缓存命令的定时器 */
        AT_StopRelTimer(ucIndex, &pClientContext->hTimer);

        usBlockCmdLen = pClientContext->usBlockCmdLen;
        pucBlockCmd = (VOS_UINT8*)AT_MALLOC(usBlockCmdLen);
        if(NULL == pucBlockCmd)
        {
            /* 留待超时返回或下条命令处理结束后触发 */
            return ;
        }

        PS_MEM_CPY(pucBlockCmd, pClientContext->pBlockCmd, usBlockCmdLen);

        AT_ClearBlockCmdInfo(ucIndex);

        /* 处理缓存命令 */
        At_ReadyClientCmdProc(ucIndex, pucBlockCmd, usBlockCmdLen);

        AT_FREE(pucBlockCmd);
        pucBlockCmd = NULL;

        return ;
    }

    return;
}

/*****************************************************************************
 函 数 名  : At_CmdMsgDistr
 功能描述  : AT自处理消息分发
 输入参数  : AT_MSG_STRU* pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : c64416
    修改内容   : 新生成函数

  2.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : C核单独复位项目

  3.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加模式切换命令处理

  4.日    期   : 2013年12月28日
    作    者   : j00174725
    修改内容   : HSUART PHASE III

  5.日    期   : 2015年3月12日
    作    者   : A00165503
    修改内容   : DTS2015032409785: 增加水线检测功能

  6.日    期   : 2015年9月5日
    作    者   : A00165503
    修改内容   : DTS2015090105100: NDIS网卡禁用无法断开连接
*****************************************************************************/
VOS_VOID At_CmdMsgDistr(AT_MSG_STRU *pstMsg)
{
    VOS_UINT16                          usLen = 0;
    VOS_UINT8                          *pData = NULL;
    VOS_UINT8                           ucIndex = 0;

    usLen   = pstMsg->usLen;
    pData   = pstMsg->aucValue;
    ucIndex = pstMsg->ucIndex;

    /* C核/HIFI复位时，模拟的是AT给AT发的消息 */
    switch(pstMsg->ucType)
    {
        case ID_CCPU_AT_RESET_START_IND:
            AT_RcvCcpuResetStartInd(pstMsg);
            return;

        case ID_CCPU_AT_RESET_END_IND:
            AT_RcvCcpuResetEndInd(pstMsg);
            return;

        case ID_HIFI_AT_RESET_START_IND:
            AT_RcvHifiResetStartInd(pstMsg);
            return;

        case ID_HIFI_AT_RESET_END_IND:
             AT_RcvHifiResetEndInd(pstMsg);
            return;

        default:
            break;
    }

    AT_AddUsedClientId2Tab(ucIndex);

    /* 如果处于C核复位前则不处理任何AT命令 */
    if (VOS_TRUE == AT_GetResetFlag())
    {
        return;
    }

    if (AT_SWITCH_CMD_MODE_MSG == pstMsg->ucType)
    {
        AT_RcvSwitchCmdModeMsg(pstMsg->ucIndex);
        return;
    }

    if (AT_WATER_LOW_MSG == pstMsg->ucType)
    {
        AT_RcvWaterLowMsg(pstMsg->ucIndex);
        return;
    }

    if (AT_NCM_CONN_STATUS_MSG == pstMsg->ucType)
    {
        AT_NDIS_ConnStatusChgProc(NCM_IOCTL_STUS_BREAK);
        return;
    }

#ifdef __PS_WIN32_RECUR__
    if(AT_PC_REPLAY_MSG == pstMsg->ucType)
    {
        AT_RestoreContextData(pstMsg);
        return;
    }

    if(AT_PC_REPLAY_MSG_CLIENT_TAB == pstMsg->ucType)
    {
        AT_RestoreClientData((NAS_AT_SDT_AT_CLIENT_TABLE_STRU *)pstMsg);
        return;
    }
#endif

    if(AT_COMBIN_BLOCK_MSG == pstMsg->ucType)
    {
        At_CombineBlockCmdProc(ucIndex);
        return;
    }

    At_CmdStreamRcv(ucIndex, pData, usLen);

    return;
}


/******************************************************************************
 函数名称: atfwParseSaveParam
 功能描述: 解析字符串并保存参数到全局变量

 参数说明:
   pStringBuf [in/out] 字符串内容
   usLen [in] 字符串长度

 作    者: 崔军强/00064416 [2011-04-01]
 2.日    期   : 2013年03月11日
   作    者   : l00198894
   修改内容   : Body SAR项目

******************************************************************************/
VOS_UINT32 atfwParseSaveParam(VOS_UINT8* pStringBuf, VOS_UINT16 usLen)
{
    if ((usLen > AT_PARA_MAX_LEN) || (gucAtParaIndex >= AT_MAX_PARA_NUMBER))
    {
        return ERR_MSP_FAILURE;
    }

    /* 如果长度为0，则允许字符串指针为空，否则返回失败 */
    if ((NULL == pStringBuf) && (0 != usLen))
    {
        return ERR_MSP_FAILURE;
    }

    /* 如果字符串长度为0，则不需要拷贝 */
    if((0 != usLen) && (NULL != pStringBuf))
    {
        PS_MEM_CPY(gastAtParaList[gucAtParaIndex].aucPara, pStringBuf, usLen);
    }

    gastAtParaList[gucAtParaIndex].usParaLen = usLen;

    gucAtParaIndex++;

    return ERR_MSP_SUCCESS;
}

/******************************************************************************
 函 数 名  : AT_SaveCdataDialParam
 功能描述  : 保存拨号信息"#777"
 输入参数  : VOS_UINT8                          *pStringBuf
             VOS_UINT16                          usLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : y00314741
    修改内容   : 新生成函数

******************************************************************************/
VOS_UINT32 AT_SaveCdataDialParam(
    VOS_UINT8                          *pStringBuf,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                          *pucCurrPtr = pStringBuf;
    VOS_UINT16                          usLength;

    if ((usLen > AT_PARA_MAX_LEN) || (NULL == pStringBuf))
    {
        return ERR_MSP_FAILURE;
    }
    /* 为适配解析"*99#", "*98#",
       将"#777"解析存为:
       #,
       #777,
       777
    */

    if (AT_CDATA_DIAL_777_LEN < usLen)
    {
        /* 指针跳过'D' */
        pucCurrPtr++;

        /* 保存'#' */
        gastAtParaList[gucAtParaIndex].aucPara[0] = *pucCurrPtr;
        gastAtParaList[gucAtParaIndex].usParaLen  = 1;

        /* 保存'#777' */
        gucAtParaIndex++;
        usLength = usLen - 1;
        PS_MEM_CPY(gastAtParaList[gucAtParaIndex].aucPara, pucCurrPtr, usLength);
        gastAtParaList[gucAtParaIndex].usParaLen = usLength;

        /* 保存'777' */
        pucCurrPtr++;
        gucAtParaIndex++;
        usLength--;
        PS_MEM_CPY(gastAtParaList[gucAtParaIndex].aucPara, pucCurrPtr, usLength);
        gastAtParaList[gucAtParaIndex].usParaLen = usLength;

    }

    gucAtParaIndex++;

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 函 数 名  : At_CmdTestProcOK
 功能描述  : 命令的测试模式下返回OK的处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_CmdTestProcOK(VOS_UINT8 ucIndex)
{
    return AT_OK;
}


/*****************************************************************************
 函 数 名  : At_CmdTestProcERROR
 功能描述  : 命令的测试模式下返回ERROR的处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c64416
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_CmdTestProcERROR(VOS_UINT8 ucIndex)
{
    return AT_ERROR;
}


/******************************************************************************
 函数名称: atFWSendMsg
 功能描述: AT框架给其他模块发送消息

 参数说明:
   TaskId [in] 任务ID
   MsgId [in] 消息ID
   VOS_VOID * pData [in/out] 发送信息的内容
   uLen [in] 发送信息的长度

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 atFWSendMsg(VOS_UINT32 TaskId,  VOS_VOID* pData, VOS_UINT32 uLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    MsgBlock *pMsgBlock = NULL;

    pMsgBlock = VOS_AllocMsg(WUEPS_PID_AT, uLen);
    if(NULL == pMsgBlock)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    pMsgBlock->ulReceiverPid = TaskId;
    pMsgBlock->ulSenderPid   = WUEPS_PID_AT;

    VOS_MemCpy(pMsgBlock->aucValue, pData, uLen);

    ulRet = VOS_SendMsg(WUEPS_PID_AT, pMsgBlock);
    if (VOS_OK != ulRet)
    {

    }
    else
    {
        ulRet = ERR_MSP_SUCCESS;
    }

    return ulRet;
}


/******************************************************************************
 函数名称: AT_FwSendClientMsg
 功能描述: 二进制消息回复处理接口

 参数说明:
   ucClientId [in] client id
   ulMsgId [in] message id
   usMsgParamSize [in] 消息体大小
   VOS_VOID* pMsgParam [in] 消息体内容

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 AT_FwSendClientMsg(VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgId, VOS_UINT16 usMsgParamSize, VOS_VOID* pMsgParam)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT32 ulMsgLen = 0;
    AT_FW_MSG_STRU* pstAtFwMsg = NULL;
    AT_FW_CMD_BINARY_MSG_STRU* pstBinaryInfo = NULL;

    if ((0 == usMsgParamSize) || (NULL == pMsgParam))
    {
        return ERR_MSP_FAILURE;
    }

    ulMsgLen = sizeof(AT_FW_MSG_STRU) + sizeof(AT_FW_CMD_BINARY_MSG_STRU) + usMsgParamSize;

    pstAtFwMsg = (AT_FW_MSG_STRU*)AT_MALLOC(ulMsgLen);
    if (NULL == pstAtFwMsg)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    pstAtFwMsg->ulMsgId = ID_MSG_AT_FW_CMD_BINARY_MSG;
    pstBinaryInfo = (AT_FW_CMD_BINARY_MSG_STRU*)pstAtFwMsg->pMsgParam;
    pstBinaryInfo->ucClientId = 0;
    pstBinaryInfo->ucSysMode = 0;
    pstBinaryInfo->usMsgSize = usMsgParamSize;
    pstBinaryInfo->ulMsgId = ulMsgId;
    PS_MEM_CPY(pstBinaryInfo->pMsg, pMsgParam, usMsgParamSize);

    ulRet = atFWSendMsg(ulRcvPid, pstAtFwMsg, ulMsgLen);
    if (ERR_MSP_SUCCESS != ulRet)
    {
        (VOS_VOID)vos_printf("atFWSendMsg failed ulRet %d", ulRet);
    }

    AT_FREE(pstAtFwMsg);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : AT_IsAbortCmdStr
 功能描述  : 判断输入字符串是否与NV中的打断命令一致, 即是否是打断命令.
             与手机产品线确认Balong平台的打断机制需求，在AT端口输入一条AT命令后，如果该命令支持打断，
             后续该端口接收到"AT"字符，表示需要打断命令的执行，打断完成后在该端口输出"ABORT"，
             表示打断完成，可以接收下一条命令；如果该命令不支持打断，实现与目前保持一致，
             即在命令执行完前，该端口接收到的所有字符都被丢弃。

 输入参数  :ucIndex : 当前通道索引
            pucData : AT命令字符串, 输入的字符已经去除了不可见字符(<0x20的ASCII字符),
                       空格,回车等字符. 但没有字符串结束符
             usLen   : AT命令字符串长度, 已去除了空格 回车等字符后的长度
 输出参数  : 无
 返 回 值  : VOS_TRUE : 是打断命令
             VOS_FALSE: 不是打断命令
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : l00171473
    修改内容   : 新生成函数, V7R1C50_At_Abort
  2.日    期   : 2013年10月18日
    作    者   : w00242748
    修改内容   : NETSCAN打断命令修改

  3.日    期   : 2013年10月19日
    作    者   : w00167002
    修改内容   : 修改当前函数，传入index,支持各通道下的命令打断；

  4.日    期   : 2013年10月31日
    作    者   : w00167002
    修改内容   : NETSCAN:减少翻转考虑优化
  5.日    期   : 2013年10月31日
    作    者   : w00167002
    修改内容   : NETSCAN:TICK不变时候也会打断
*****************************************************************************/

VOS_UINT32 AT_IsAbortCmdStr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara = VOS_NULL_PTR;
    VOS_UINT32                          ulAbortCmdStrLen;
    VOS_UINT32                          ulAtCurrSetTick;
    AT_CMD_ABORT_TICK_INFO             *pstCmdAbortTick     = VOS_NULL_PTR;
    VOS_UINT32                          ulTimeInternal;

    ulAtCurrSetTick = VOS_GetTick();
    pstCmdAbortTick = At_GetAtCmdAbortTickInfo();

    /* 输入的字符已经去除了不可见字符(<0x20的ASCII字符),空格, S3, S5等字符. 但没有字符串结束符 */

    ulAbortCmdStrLen = 0;

    /* 获取打断命令的参数 */
    pstAbortCmdPara  = AT_GetAbortCmdPara();

    if (VOS_NULL_PTR == pstAbortCmdPara)
    {
        return VOS_FALSE;
    }

    /* 判断是否使能打断命令功能 */
    if ( VOS_TRUE != pstAbortCmdPara->ucAbortEnableFlg )
    {
        return VOS_FALSE;
    }



    /* 检测当前打断tick值是否满足相隔125ms条件,如果不满足，则直接返回不打断 */
    if  ( ulAtCurrSetTick >= pstCmdAbortTick->ulAtSetTick[ucIndex] )
    {

        ulTimeInternal = ulAtCurrSetTick - pstCmdAbortTick->ulAtSetTick[ucIndex];
    }
    else
    {
        ulTimeInternal = ulAtCurrSetTick + (AT_MAX_TICK_TIME_VALUE - pstCmdAbortTick->ulAtSetTick[ucIndex]);
    }

    if ( ulTimeInternal < AT_MIN_ABORT_TIME_INTERNAL)
    {
        return VOS_FALSE;
    }

    /* 检测当前是否是任意字符打断，如果是，则直接返回打断 */
    if  ( VOS_TRUE == At_GetAtCmdAnyAbortFlg() )
    {
        return VOS_TRUE;
    }

    /* 长度判断 */
    ulAbortCmdStrLen = VOS_StrLen((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr);
    if ( (0 == usLen) || (usLen != ulAbortCmdStrLen) )
    {
        return VOS_FALSE;
    }

    /* 当前不是任意字符打断，则需要检测AT打断内容，是打断命令，则返回打断 */
    if ( (0 == VOS_StrNiCmp((VOS_CHAR *)pucData, (VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, usLen)) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_AbortCmdProc
 功能描述  : AT打断的统一处理入口
 输入参数  :  VOS_UINT8 ucIndex : 索引号
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : l00171473
    修改内容   : 新生成函数, V7R1C50_At_Abort

*****************************************************************************/
VOS_VOID AT_AbortCmdProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulTimerLen;
    VOS_UINT32                          ulResult;

    /* 空指针检查 */
    if ( VOS_NULL_PTR == g_stParseContext[ucIndex].pstCmdElement )
    {
        AT_WARN_LOG("AT_AbortCmdProc: pstCmdElement NULL.");
        return;
    }

    if ( VOS_NULL_PTR == g_stParseContext[ucIndex].pstCmdElement->pfnAbortProc )
    {
        return;
    }

    /* 调用当前正在处理的AT命令的Abort函数 */
    ulResult = g_stParseContext[ucIndex].pstCmdElement->pfnAbortProc(ucIndex);
    if ( AT_WAIT_ASYNC_RETURN == ulResult )
    {
        /* 由于当前AT端口的状态已经处于PEND状态, 此处不需要再更新端口状态 */

        /* 启动打断保护定时器, 超时后需要向AT端口上报ABORT */
        ulTimerLen = g_stParseContext[ucIndex].pstCmdElement->ulAbortTimeOut;
        if ( 0 == ulTimerLen )
        {
            AT_WARN_LOG("AT_AbortCmdProc: TimerLen 0.");
            return;
        }

        /* 起保护定时器 */
        if ( AT_SUCCESS != At_StartTimer(ulTimerLen, ucIndex) )
        {
            AT_WARN_LOG("AT_AbortCmdProc: StartTimer Err.");
            return;
        }
    }
    /* 表示AT直接打断 不需要等异步消息 */
    else if ( (AT_ABORT == ulResult)
           || (AT_OK    == ulResult) )
    {
        ulResult               = AT_ABORT;
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex,ulResult);
    }
    /* 其它异常，如消息发送失败 内存申请失败，当前命令操作类型不支持打断
       (如在指定搜过程收到打断命令, 但当前指定搜不支持打断)等，丢弃 不做打断处理 */
    else
    {
        AT_WARN_LOG1("AT_AbortCmdProc, WARNING, Return Code %d!", ulResult);
    }

}

/*****************************************************************************
 函 数 名  : AT_GetCmdElementInfo
 功能描述  : 在各命令表中查找指定命令
 输入参数  : pucCmdName : 命令名字符串
             ulCmdType  : 命令类型
 输出参数  : 无
 返 回 值  : 命令表中该指定命令的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : l00171473
    修改内容   : 新生成函数, V7R1C50_At_Abort

*****************************************************************************/
AT_PAR_CMD_ELEMENT_STRU* AT_GetCmdElementInfo(
    VOS_UINT8                          *pucCmdName,
    VOS_UINT32                          ulCmdType
)
{
    HI_LIST_S                          *pstCurList    = VOS_NULL_PTR;
    HI_LIST_S                          *pstCmdTblList = VOS_NULL_PTR;
    AT_PAR_CMDTBL_LIST_STRU            *pstCurCmdNode = VOS_NULL_PTR;
    VOS_UINT32                          i;


    /* 调用的地方保证输入的指针不为空 */

    pstCmdTblList   = &(g_stCmdTblList);

    /* 如果命令类型不是扩展命令也不是基本命令，直接返回空指针 */
    if ((AT_EXTEND_CMD_TYPE != ulCmdType) && (AT_BASIC_CMD_TYPE != ulCmdType))
    {
        return VOS_NULL_PTR;
    }

    /* 在各命令表中查找指定命令 */
    msp_list_for_each(pstCurList, pstCmdTblList)
    {
        pstCurCmdNode = msp_list_entry(pstCurList, AT_PAR_CMDTBL_LIST_STRU, stCmdTblList);

        for (i = 0; i < pstCurCmdNode->usCmdNum; i++)
        {
            /* 没找到时，在命令表中查找下一条命令 */
            if ((NULL == pstCurCmdNode->pstCmdElement) || (NULL == pstCurCmdNode->pstCmdElement[i].pszCmdName))
            {
                continue;
            }
            /* 找到时，指针指到相应的命令 */
            if (ERR_MSP_SUCCESS == AT_STRCMP((VOS_CHAR*)pucCmdName, (VOS_CHAR*)pstCurCmdNode->pstCmdElement[i].pszCmdName))
            {
                return &(pstCurCmdNode->pstCmdElement[i]);
            }
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : AT_SaveCmdElementInfo
 功能描述  : 在各命令表中匹配指定命令并保存该命令的命令描述表信息
 输入参数  : ucIndex    : AT通道的index
             pucCmdName : 命令名字符串
             ulCmdType  : 命令类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : l00171473
    修改内容   : 新生成函数, V7R1C50_At_Abort

*****************************************************************************/
VOS_VOID AT_SaveCmdElementInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucCmdName,
    VOS_UINT32                          ulCmdType
)
{
    AT_PAR_CMD_ELEMENT_STRU            *pstGetCmdElemnet;

    if (VOS_NULL_PTR == pucCmdName)
    {
        return;
    }

    /* 没有找到相应的指定命令时，直接返回 */
    pstGetCmdElemnet = AT_GetCmdElementInfo(pucCmdName, ulCmdType);
    if (VOS_NULL_PTR == pstGetCmdElemnet)
    {
        AT_ERR_LOG("AT_SaveCmdElementInfo: GetCmdElementInfo Failed.");
        return;
    }

    /* 找到时，保存到全局变量 */
    g_stParseContext[ucIndex].pstCmdElement = pstGetCmdElemnet;

    return;
}


/*****************************************************************************
 函 数 名  : AT_IsAnyParseClientPend
 功能描述  : 判断是否有端口处于PEND状态
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : 若有一个通道处于PEND状态，则返回VOS_UINT32
             若所有通道都处于READY状态，则返回VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : j00174725
    修改内容   : HSUART PHASE III
*****************************************************************************/
VOS_UINT32 AT_IsAnyParseClientPend(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucClientIndex;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    if (pstPortBuffCfg->ucNum > AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM;
    }

    /* 根据当前记录的通道查询通道状态 */
    for (i = 0; i < pstPortBuffCfg->ucNum; i++)
    {
        ucClientIndex = (VOS_UINT8)pstPortBuffCfg->ulUsedClientID[i];

        if (ucClientIndex >= AT_CLIENT_ID_BUTT)
        {
            continue;
        }

        if (AT_FW_CLIENT_STATUS_PEND == g_stParseContext[ucClientIndex].ucClientStatus)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_IsAllClientDataMode
 功能描述  : 判断是否所有端口都处于DADA模式
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : 若当前所有使用的通道都处于数据模式，则返回AT_DATA_MODE
             若当前所有使用的通道有一个不处于数据模式且不处于pend状态，则返回AT_CMD_MODE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : j00174725
    修改内容   : HSUART PHASE III
*****************************************************************************/
VOS_UINT32 AT_IsAllClientDataMode(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT32                          ulDataModeNum;

    ulDataModeNum = 0;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    if (pstPortBuffCfg->ucNum > AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM;
    }

    /* 查看有多少个通道处于data模式 */
    for (i = 0; i < pstPortBuffCfg->ucNum; i++)
    {
        ucClientIndex = (VOS_UINT8)pstPortBuffCfg->ulUsedClientID[i];
        if (ucClientIndex >= AT_CLIENT_ID_BUTT)
        {
            continue;
        }

        if (AT_DATA_MODE == gastAtClientTab[ucClientIndex].Mode)
        {
            ulDataModeNum++;
        }
    }

    /* 所有通道有处理data模式 */
    if (ulDataModeNum == pstPortBuffCfg->ucNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : atCmdIsSupportedByCLMode
 功能描述  : 判断当前的at 命令在CLI模式下是否需要保护
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : VOS_UINT8
 返 回 值  :
            若下发的AT命令的cmdindex属于下列的在CL模式下待保护的AT命令的index，返回VOS_TRUE
            若下发的AT命令的cmdindex不属于下列的在CL模式下待保护的AT命令的index，返回VOS_FALSE

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : f00279542
    修改内容   : new add
  2.修改历史   : 2015年12月22日
    作    者   : c00299063
    修改内容   : 修改AT_CMD_CCMGS AT_CMD_CCMGW AT_CMD_CCMGD
*****************************************************************************/
VOS_UINT8 atCmdIsSupportedByCLMode(VOS_UINT8 ucIndex)
{
    AT_PAR_CMD_ELEMENT_STRU            *pstCmdElement = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulCmdArraySize;
    VOS_UINT32                          aulCmdIndex[]  = {
                                                             AT_CMD_CLIP,
                                                             AT_CMD_DTMF,
                                                             AT_CMD_CARDMODE,
                                                             AT_CMD_ACTIVEMODEM,
                                                             AT_CMD_CMGS,
                                                             #if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
                                                             AT_CMD_CSCB,
                                                             #endif
                                                             AT_CMD_CNMI,
                                                             AT_CMD_CSCA,
                                                             AT_CMD_CSASM,
                                                             AT_CMD_CUSD,
                                                             AT_CMD_CMGW,
                                                             AT_CMD_CMGD,
                                                             AT_CMD_CCWA,
                                                             AT_CMD_CCFC,
                                                             AT_CMD_CLIR,
                                                             AT_CMD_CMMS,
                                                             AT_CMD_CSSN,
                                                             AT_CMD_CELLINFO,
                                                             AT_CMD_CPMS,
                                                             AT_CMD_RELEASERRC,
                                                             AT_CMD_EOPLMN,
                                                             AT_CMD_CNMR,
                                                             #if (FEATURE_ON == FEATURE_IMS)
                                                             AT_CMD_CALL_MODIFY_INIT,
                                                             AT_CMD_CALL_MODIFY_ANS,
                                                             AT_CMD_ECONFDIAL,
                                                             AT_CMD_CLCCECONF,
                                                             AT_CMD_ECONFERR,
                                                             AT_CMD_CACMIMS,
                                                             #endif
                                                             AT_CMD_CHLD_EX};

    ulCmdArraySize = sizeof((aulCmdIndex)) / sizeof((aulCmdIndex[0]));

    pstCmdElement = g_stParseContext[ucIndex].pstCmdElement;

    /* CLCK的操作类型为SC和FD不需要禁，其它的需要禁掉 */
    if (AT_CMD_CLCK == pstCmdElement->ulCmdIndex)
    {
        if ((AT_CLCK_SC_TYPE == gastAtParaList[0].ulParaValue)
         || (AT_CLCK_FD_TYPE == gastAtParaList[0].ulParaValue))
        {
            return VOS_FALSE;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* CPWD的操作类型为SC和FD不需要禁，其它的需要禁掉 */
    if (AT_CMD_CPWD == pstCmdElement->ulCmdIndex)
    {
        if ((AT_CLCK_SC_TYPE == gastAtParaList[0].ulParaValue)
         || (AT_CLCK_P2_TYPE == gastAtParaList[0].ulParaValue))
        {
            return VOS_FALSE;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* 判断下发的AT命令的cmdindex是否属于下列的在CL模式下待保护的AT命令的index */
    for (ulLoop = 0; ulLoop < ulCmdArraySize; ulLoop++)
    {
        if (pstCmdElement->ulCmdIndex == aulCmdIndex[ulLoop])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


