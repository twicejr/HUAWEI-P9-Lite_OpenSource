

#include "AtCheckFunc.h"

#include "msp_errno.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/* AT命令初始空状态表 */
AT_SUB_STATE_STRU AT_B_CMD_NONE_STATE_TAB[]=
{
    /* 如果当前状态是ATCMD_NONE_STATE，atCheckBasicCmdName成功，则进入AT_B_CMD_NAME_STATE */
    {    atCheckBasicCmdName    ,    AT_B_CMD_NAME_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT基本命令名状态表 */
AT_SUB_STATE_STRU AT_B_CMD_NAME_STATE_TAB[]=
{
    /* 如果当前状态是AT_B_CMD_NAME_STATE，atCheckBasicCmdName成功，则进入AT_B_CMD_NAME_STATE */
    {    atCheckBasicCmdName    ,    AT_B_CMD_NAME_STATE    },

    /* 如果当前状态是AT_B_CMD_NAME_STATE，At_CheckDigit成功，则进入AT_B_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_B_CMD_PARA_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT基本命令参数状态表 */
AT_SUB_STATE_STRU AT_B_CMD_PARA_STATE_TAB[]=
{
    /* 如果当前状态是AT_B_CMD_NAME_STATE，At_CheckDigit成功，则进入AT_B_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_B_CMD_PARA_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};



/* AT基本命令主状态表 */
AT_MAIN_STATE_STRU AT_B_CMD_MAIN_STATE_TAB[] =
{
    /* 如果当前状态是AT_NONE_STATE，则进入AT_B_CMD_NONE_STATE_TAB子状态表 */
    {    AT_NONE_STATE    ,    AT_B_CMD_NONE_STATE_TAB    },

    /* 如果当前状态是AT_B_CMD_NAME_STATE，则进入AT_B_CMD_NAME_STATE_TAB子状态表 */
    {    AT_B_CMD_NAME_STATE    ,    AT_B_CMD_NAME_STATE_TAB    },

    /* 如果当前状态是AT_B_CMD_PARA_STATE，则进入AT_B_CMD_PARA_STATE_TAB子状态表 */
    {    AT_B_CMD_PARA_STATE    ,    AT_B_CMD_PARA_STATE_TAB    },

    /* 主状态表结束 */
    {    AT_BUTT_STATE    ,    NULL    },

};


/* AT命令初始空状态表 */
AT_SUB_STATE_STRU AT_W_CMD_NAME_STATE_TAB[]=
{
    /* 如果当前状态是ATCMD_NONE_STATE，At_CheckBasicCmdName成功，则进入AT_B_CMD_NAME_STATE */
    {    At_CheckChar0x26    ,    AT_W_CMD_F_STATE    },

    {    At_CheckCharE    ,    AT_W_CMD_PARA_STATE    },
    {    At_CheckCharI,        AT_W_CMD_PARA_STATE    },

    {    At_CheckCharV    ,    AT_W_CMD_PARA_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT基本命令名状态表 */
AT_SUB_STATE_STRU AT_W_CMD_PARA_STATE_TAB[]=
{
    /* 如果当前状态是AT_B_CMD_NAME_STATE，At_CheckChar1成功，则进入AT_W_CMD_NAME_STATE */
    {    At_CheckChar1    ,    AT_W_CMD_NAME_STATE    },

    /* 如果当前状态是AT_B_CMD_NAME_STATE，At_CheckChar0成功，则进入AT_W_CMD_NAME_STATE */
    {    At_CheckChar0    ,    AT_W_CMD_NAME_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT基本命令名状态表 */
AT_SUB_STATE_STRU AT_W_CMD_0x26_STATE_TAB[]=
{
    /* 如果当前状态是AT_B_CMD_NAME_STATE，At_CheckCharF成功，则进入AT_W_CMD_NAME_STATE */
    {    At_CheckCharF    ,    AT_W_CMD_NAME_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};



/* AT基本命令主状态表 */
AT_MAIN_STATE_STRU AT_W_CMD_MAIN_STATE_TAB[] =
{
    /* 如果当前状态是AT_NONE_STATE，则进入AT_B_CMD_NONE_STATE_TAB子状态表 */
    {    AT_NONE_STATE    ,    AT_W_CMD_NAME_STATE_TAB    },

    /* 如果当前状态是AT_NONE_STATE，则进入AT_B_CMD_NONE_STATE_TAB子状态表 */
    {    AT_W_CMD_NAME_STATE    ,    AT_W_CMD_NAME_STATE_TAB    },

    /* 如果当前状态是AT_B_CMD_NAME_STATE，则进入AT_B_CMD_NAME_STATE_TAB子状态表 */
    {    AT_W_CMD_PARA_STATE    ,    AT_W_CMD_PARA_STATE_TAB    },

    /* 如果当前状态是AT_B_CMD_NAME_STATE，则进入AT_B_CMD_NAME_STATE_TAB子状态表 */
    {    AT_W_CMD_F_STATE    ,    AT_W_CMD_0x26_STATE_TAB    },

    /* 主状态表结束 */
    {    AT_BUTT_STATE    ,    NULL    },

};

/******************************************************************************
 函数名称: atParseBasicCmd
 功能描述: 解析AT基本命令字符串,得出命令名,参数,命令类型,命令操作类型

 参数说明:
   pData [in] 输入的字符串
   usLen [in] 字符串的长度

 返 回 值:
    AT_SUCCESS: 成功
    AT_FAILURE: 失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseBasicCmd(VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  设置初始状态 */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  设置初始状态 */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  指向当前正在处理的字符*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  拷贝内容的起始指针 */
    VOS_UINT16 usLength = 0;                        /*  记录当前已经处理的字符个数*/

    if(AT_FAILURE == atCheckBasicCmdName(*pucCurrPtr))
    {
        return AT_ERROR;
    }

    /* 依次分析字符串中的每个字符*/
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                    /* 依次比较每个字符 */
    {
        curr_state = new_state;                 /*  当前状态设置为新状态*/

        /*  根据当前处理的字符和当前状态查表得到新状态*/
        new_state = atFindNextMainState(AT_B_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                       /*  状态处理*/
        {
        case AT_B_CMD_NAME_STATE:               /*  基本命令名状态*/
            if(curr_state != new_state)         /*  新状态部分不等于当前状态*/
            {
                g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;            /*  设置命令类型*/
                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /*  设置命令操作类型*/
                pucCopyPtr = pucCurrPtr;            /*  准备接收基本类型命令名*/
            }
            break;

        case AT_B_CMD_PARA_STATE:               /* AT基本命令参数状态 */
            if(curr_state != new_state)         /* 新状态部分不等于当前状态*/
            {
                /* 存储命令名到全局变量中 */
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                      /* 返回错误 */
                }

                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* 设置命令操作类型*/
                pucCopyPtr = pucCurrPtr;                    /* 准备接收参数*/
            }
            break;

        default:
            return AT_FAILURE;                  /* 返回错误 */
        }
        pucCurrPtr++;                           /*  继续分析下一个字符*/
    }

    switch(new_state)                           /*  根据最后的状态判断*/
    {
    case AT_B_CMD_NAME_STATE:                   /*  基本命令名状态*/

        /* 存储命令名到全局变量中 */
        g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
        if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
        {
            atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
        }
        else
        {
            return AT_FAILURE;                  /* 返回错误 */
        }
        break;

    case AT_B_CMD_PARA_STATE:                   /*  基本命令名状态*/
        /* 存储参数到全局变量中 */
        if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_FAILURE;
        }

        break;

    default:                                    /* 其它错误状态*/
        return AT_FAILURE;                      /* 返回错误 */
    }

    return AT_SUCCESS;                          /*  返回正确*/
}

/******************************************************************************
 函数名称: atCheckCharWcmd
 功能描述: 比较、匹配字符&

 参数说明:
   pData [in] 输入的字符串
   usLen [in] 字符串的长度

 返 回 值:
    AT_SUCCESS: 成功
    AT_FAILURE: 失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atCheckCharWcmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT8 Char = *pData;

    if(usLen < 3)   /* 为何有此限制？岂不都返回失败？ */
    {
        return AT_FAILURE;
    }

    if( ('d' != Char) && ('D' != Char) && ('h' != Char) && ('H' != Char) && ('a' != Char) && ('A' != Char))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/******************************************************************************
 函数名称: atParseWCmd
 功能描述: 解析AT基本命令字符串,得出命令名,参数,命令类型,命令操作类型

 参数说明:
   pData [in] 输入的字符串
   usLen [in] 字符串的长度

 返 回 值:
    AT_SUCCESS: 成功
    AT_FAILURE: 失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseWCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  设置初始状态 */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  设置初始状态 */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  指向当前正在处理的字符*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  拷贝内容的起始指针 */
    VOS_UINT16 usLength = 0;                        /*  记录当前已经处理的字符个数*/

    At_UpString(pData,usLen);

    /* 依次分析字符串中的每个字符*/
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))
    {
        curr_state = new_state;                 /*  当前状态设置为新状态*/

        /*  根据当前处理的字符和当前状态查表得到新状态*/
        new_state = atFindNextMainState(AT_W_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        pucCopyPtr = pucCurrPtr;

        switch(new_state)                       /*  状态处理*/
        {
        case AT_W_CMD_NAME_STATE:
            if(usLength > 1)
            {
                if('E' == *(pucCopyPtr-1))
                {
                    /* atSetCurClientEtype(*pucCopyPtr - '0'); */
                }
                else if('V' == *(pucCopyPtr-1))
                {
                    /* atSetCurClientVtype(*pucCopyPtr - '0'); */
                }
                else if('&' == *(pucCopyPtr-1))
                {
                    /* atSetFPara(EN_AT_FW_CLIENT_ID_ALL); */
                }
                else
                {

                }
            }
            break;                  /* 返回错误 */

        default:
            break;
        }
        pucCurrPtr++;                           /*  继续分析下一个字符*/
    }

    switch(new_state)
    {
    case AT_W_CMD_NAME_STATE:
        return AT_OK;                          /*  返回正确*/

    default:
        return AT_ERROR;                          /* 返回错误 */
    }
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

