

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtCheckFunc.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSEEXTENDCMD_C
/*lint +e960*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/
/* AT扩展命令初始状态状态表 */
AT_SUB_STATE_STRU AT_E_CMD_NONE_STATE_TAB[]=
{
    /* 如果当前状态是ATCMD_T_STATE，atCheckCharPlus成功，则进入AT_E_CMD_NAME_STATE */
    {    At_CheckCharPlus    ,    AT_E_CMD_NAME_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT扩展命令名状态表 */
AT_SUB_STATE_STRU AT_E_CMD_NAME_STATE_TAB[]=
{
    /* 如果当前状态是AT_E_CMD_NAME_STATE，atCheck_char成功，则进入AT_E_CMD_NAME_STATE */
    {    At_CheckChar    ,    AT_E_CMD_NAME_STATE    },

    /* 如果当前状态是AT_E_CMD_NAME_STATE，atCheck_equ成功，则进入AT_E_CMD_SET_STATE */
    {    At_CheckEqu    ,    AT_E_CMD_SET_STATE    },

    /* 如果当前状态是AT_E_CMD_NAME_STATE，atCheck_req成功，则进入AT_E_CMD_READ_STATE */
    {    At_CheckReq    ,    AT_E_CMD_READ_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT扩展命令等号状态表 */
AT_SUB_STATE_STRU AT_E_CMD_SET_STATE_TAB[]=
{
    /* 如果当前状态是AT_E_CMD_SET_STATE，atCheck_req成功，则进入AT_E_CMD_TEST_STATE */
    {    At_CheckReq    ,    AT_E_CMD_TEST_STATE    },

    /* 如果当前状态是AT_E_CMD_SET_STATE，atCheck_char成功，则进入AT_E_CMD_PARA_STATE */
    {    At_CheckChar    ,    AT_E_CMD_PARA_STATE    },

    /* 如果当前状态是AT_E_CMD_SET_STATE，atCheck_colon成功，则进入AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,    AT_E_CMD_COLON_STATE    },

    /* 如果当前状态是AT_E_CMD_SET_STATE，atCheck_quot成功，则进入AT_E_CMD_LEFT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_E_CMD_LEFT_QUOT_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT扩展命令参数状态表 */
AT_SUB_STATE_STRU AT_E_CMD_PARA_STATE_TAB[]=
{
    /* 如果当前状态是AT_E_CMD_PARA_STATE，atCheck_char成功，则进入AT_E_CMD_PARA_STATE */
    {    At_CheckChar    ,    AT_E_CMD_PARA_STATE    },

    /* 如果当前状态是AT_E_CMD_PARA_STATE，atCheck_char成功，则进入AT_E_CMD_PARA_STATE */
    {    atCheckblank    ,   AT_E_CMD_PARA_STATE    },

    /* 如果当前状态是AT_E_CMD_PARA_STATE，atCheckColon成功，则进入AT_E_CMD_PARA_STATE */
    {    atCheckColon    ,   AT_E_CMD_PARA_STATE    },

    /* 如果当前状态是AT_E_CMD_PARA_STATE，atCheckComma成功，则进入AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,   AT_E_CMD_COLON_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT扩展命令逗号状态表 */
AT_SUB_STATE_STRU AT_E_CMD_COLON_STATE_TAB[]=
{
    /* 如果当前状态是AT_E_CMD_COLON_STATE，atCheck_char成功，则进入AT_E_CMD_PARA_STATE */
    {    At_CheckChar    ,    AT_E_CMD_PARA_STATE    },

    /* 如果当前状态是AT_E_CMD_COLON_STATE，atCheck_colon成功，则进入AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,    AT_E_CMD_COLON_STATE    },

    /* 如果当前状态是AT_E_CMD_COLON_STATE，atCheck_quot成功，则进入AT_E_CMD_LEFT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_E_CMD_LEFT_QUOT_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT扩展命令左引号状态表 */
AT_SUB_STATE_STRU AT_E_CMD_LEFT_QUOT_STATE_TAB[]=
{
    /* 如果当前状态是AT_E_CMD_LEFT_QUOT_STATE，atCheck_char成功，则进入AT_E_CMD_LEFT_QUOT_STATE */
    {    At_CheckNoQuot    ,    AT_E_CMD_LEFT_QUOT_STATE    },

    /* 如果当前状态是AT_E_CMD_LEFT_QUOT_STATE，atCheck_quot成功，则进入AT_E_CMD_RIGHT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_E_CMD_RIGHT_QUOT_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT扩展命令右引号状态表 */
AT_SUB_STATE_STRU AT_E_CMD_RIGHT_QUOT_STATE_TAB[]=
{
    /* 如果当前状态是AT_E_CMD_RIGHT_QUOT_STATE，atCheck_colon成功，则进入AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,    AT_E_CMD_COLON_STATE    },

    /* 如果当前状态是AT_E_CMD_RIGHT_QUOT_STATE，atCheck_char成功，则进入AT_E_CMD_RIGHT_QUOT_STATE */
    {    At_CheckChar     ,    AT_E_CMD_RIGHT_QUOT_STATE    },

    /* 如果当前状态是AT_E_CMD_RIGHT_QUOT_STATE，atCheck_quot成功，则进入AT_E_CMD_RIGHT_QUOT_STATE */
    {    At_CheckQuot     ,    AT_E_CMD_RIGHT_QUOT_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT命令主状态表 */
AT_MAIN_STATE_STRU AT_E_CMD_MAIN_STATE_TAB[] =
{
    /* 如果当前状态是AT_NONE_STATE，则进入AT_E_CMD_NONE_STATE_TAB子状态表 */
    {    AT_NONE_STATE    ,    AT_E_CMD_NONE_STATE_TAB    },

    /* 如果当前状态是AT_E_CMD_NAME_STATE，则进入AT_E_CMD_NAME_STATE_TAB子状态表 */
    {    AT_E_CMD_NAME_STATE    ,    AT_E_CMD_NAME_STATE_TAB    },

    /* 如果当前状态是AT_E_CMD_SET_STATE，则进入AT_E_CMD_SET_STATE_TAB子状态表 */
    {    AT_E_CMD_SET_STATE    ,    AT_E_CMD_SET_STATE_TAB    },

    /* 如果当前状态是AT_E_CMD_PARA_STATE，则进入AT_E_CMD_PARA_STATE_TAB子状态表 */
    {    AT_E_CMD_PARA_STATE    ,    AT_E_CMD_PARA_STATE_TAB    },

    /* 如果当前状态是AT_E_CMD_COLON_STATE，则进入AT_E_CMD_COLON_STATE_TAB子状态表 */
    {    AT_E_CMD_COLON_STATE    ,    AT_E_CMD_COLON_STATE_TAB    },

    /* 如果当前状态是AT_E_CMD_LEFT_QUOT_STATE，则进入AT_E_CMD_LEFT_QUOT_STATE_TAB子状态表 */
    {    AT_E_CMD_LEFT_QUOT_STATE    ,    AT_E_CMD_LEFT_QUOT_STATE_TAB    },

    /* 如果当前状态是AT_E_CMD_RIGHT_QUOT_STATE，则进入AT_E_CMD_RIGHT_QUOT_STATE_TAB子状态表 */
    {    AT_E_CMD_RIGHT_QUOT_STATE    ,    AT_E_CMD_RIGHT_QUOT_STATE_TAB    },

    /* 主状态表结束 */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 函数名称: atParseExtendCmd
 功能描述: 解析AT扩展命令字符串,得出命令名,参数,命令类型,命令操作类型

 参数说明:
   pData [in] 输入的字符串
   usLen [in] 字符串的长度

 返 回 值:
    AT_SUCCESS: 成功
    AT_ERROR: 失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
 2.日    期   : 2013年03月11日
   作    者   : l00198894
   修改内容   : Body SAR项目

******************************************************************************/

VOS_UINT32 atParseExtendCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  设置初始状态 */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  设置初始状态 */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  指向当前正在处理的字符*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  拷贝内容的起始指针 */
    VOS_UINT16 usLength = 0;                        /*  记录当前已经处理的字符个数*/

    /* 依次分析字符串中的每个字符*/
    while(usLength++ < usLen)                  /* 依次比较每个字符 */
    {
        curr_state = new_state;                 /* 当前状态设置为新状态*/

        /*  根据当前处理的字符和当前状态查表得到新状态*/
        new_state = atFindNextMainState(AT_E_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                       /* 状态处理*/
        {
        case AT_E_CMD_NAME_STATE:               /* 扩展命令名状态*/
            if(curr_state != new_state)         /* 新状态部分不等于当前状态*/
            {
                g_stATParseCmd.ucCmdFmtType = AT_EXTEND_CMD_TYPE;           /* 设置命令类型*/
                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* 设置命令操作类型*/

                pucCopyPtr = pucCurrPtr;            /* 准备接收扩展类型命令名*/
            }
            break;

        case AT_E_CMD_SET_STATE:                /* AT扩展命令等号状态 */
            /* 存储命令名到全局变量中 */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* 设置命令操作类型*/
            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /* 返回错误 */
            }
            break;

        case AT_E_CMD_PARA_STATE:               /* AT扩展命令参数状态 */
        case AT_E_CMD_LEFT_QUOT_STATE:          /* AT扩展命令左引号状态 */
            if(curr_state != new_state)         /* 新状态部分不等于当前状态*/
            {
                pucCopyPtr = pucCurrPtr;            /* 准备接收参数内容*/
            }
            break;

        case AT_E_CMD_COLON_STATE:              /* AT扩展命令逗号状态 */
            if((curr_state != new_state) && (AT_E_CMD_SET_STATE != curr_state))         /* 新状态部分不等于当前状态*/
            {
                /* 存储参数到全局变量中 */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_ERROR;
                }

            }
            else
            {
                /*连续两个逗号,参数不存在*/
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, 0))
                {
                    return AT_ERROR;
                }

            }
            break;

        case AT_E_CMD_READ_STATE:                   /* AT扩展命令查询参数状态 */

            /* 存储命令名到全局变量中 */
            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /* 返回错误 */
            }

            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;   /* 设置命令操作类型*/

            break;

        case AT_E_CMD_TEST_STATE:                   /* AT扩展命令测试参数状态 */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;   /* 设置命令操作类型*/
            break;

        case AT_BUTT_STATE:                         /* 无效状态 */
            return AT_ERROR;                      /* 返回错误 */

        default:
            break;
        }
        pucCurrPtr++;                                 /* 继续分析下一个字符*/
    }

    switch(new_state)                               /* 根据最后的状态判断*/
    {
    case AT_E_CMD_PARA_STATE:                       /* AT扩展命令参数状态 */
    case AT_E_CMD_RIGHT_QUOT_STATE:                 /* AT扩展命令右引号状态 */

        /* 存储参数到全局变量中 */
        if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_ERROR;
        }

        break;

    case AT_E_CMD_NAME_STATE:                   /* AT扩展命令查询参数状态 */

        /* 存储命令名到全局变量中 */
        g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
        if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
        {
            atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
        }
        else
        {
            return AT_ERROR;                  /* 返回错误 */
        }

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* 设置命令操作类型*/

        break;

    case AT_E_CMD_COLON_STATE:                      /* AT命令后面跟有无参的逗号 */

        if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, 0))
        {
            return AT_ERROR;
        }

        break;

    case AT_E_CMD_SET_STATE:                        /* AT扩展命令等号状态 */
    case AT_E_CMD_TEST_STATE:                       /* AT扩展命令查询参数状态 */
    case AT_E_CMD_READ_STATE:                       /* AT扩展命令测试参数状态 */
        break;

    default:
        return AT_ERROR;                          /* 返回错误*/
    }
    return AT_SUCCESS;                              /*  返回正确*/
}

/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
/*****************************************************************************
 函 数 名  : AT_ParseSetDockCmd
 功能描述  : 检查当前是否DOCK设置命令，
             若是DOCK设置命令，
             提取命令名称和长度，参数字符串和长度到AT的全局变量
             修改AT模块的g_stATParseCmd.ucCmdOptType，gucAtCmdFmtType，gucAtParaIndex
 输入参数  : VOS_UINT8                          *pucData
             VOS_UINT16                          usLen
 输出参数  : 无
 返 回 值  : VOS_UINT32     AT_FAILURE 不是DOCK设置命令
                            AT_SUCCESS   是DOCK设置命令
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月26日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2013年2月25日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_ParseSetDockCmd(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_INT8                            cRet;
    VOS_UINT16                          usCmdlen;
    VOS_UINT32                          ulPos;
    VOS_UINT8                          *pucDataPara = VOS_NULL_PTR;
    AT_PARSE_CMD_NAME_TYPE_STRU         stAtCmdName;

    PS_MEM_SET(&stAtCmdName, 0, sizeof(stAtCmdName));

    if (0 == usLen)
    {
        return AT_FAILURE;
    }

    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);

    if (VOS_NULL_PTR == pucDataPara)
    {
        AT_ERR_LOG("AT_ParseSetDockCmd: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    PS_MEM_CPY(pucDataPara, pucData, usLen);

    /* 去掉字符串中的退格符 */
    if (AT_FAILURE == At_ScanDelChar(pucDataPara, &usLen))
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }

    /* 待处理的字符串长度小于"AT^DOCK="长度直接返回AT_FAILURE */
    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^DOCK=");
    if (usLen < usCmdlen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }

    /* AT命令头字符转大写 */
    At_UpString(pucDataPara, usCmdlen);

    /* 待处理的字符串头部不是"AT^DOCK="直接返回AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^DOCK=", usCmdlen);
    if (0 != cRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }

    /* 获取命令(不包含命令前缀AT)名称及长度 */
    ulPos = VOS_StrLen("AT");
    stAtCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^DOCK");
    PS_MEM_CPY(stAtCmdName.aucCmdName,
               (pucDataPara + ulPos),
               stAtCmdName.usCmdNameLen);
    stAtCmdName.aucCmdName[stAtCmdName.usCmdNameLen] = '\0';
    ulPos += stAtCmdName.usCmdNameLen;

    ulPos += VOS_StrLen("=");

    /* 获取命令的参数字符串及长度 */
    gastAtParaList[0].usParaLen = usLen - (VOS_UINT16)ulPos;
    PS_MEM_CPY(gastAtParaList[0].aucPara,
               (pucDataPara + ulPos),
               gastAtParaList[0].usParaLen);

    /* 设置命令类型，操作类型和参数个数 */
    gucAtParaIndex  = 1;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType = AT_EXTEND_CMD_TYPE;

    PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
    return AT_SUCCESS;
}
/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
