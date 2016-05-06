

#include "AtCheckFunc.h"

#include "msp_errno.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/* AT S命令初始状态表 */
AT_SUB_STATE_STRU AT_S_CMD_NONE_STATE_TAB[]=
{
    /* 如果当前状态是ATCMD_NONE_STATE，atCheckCharS成功，则进入AT_S_CMD_NAME_STATE */
    {    At_CheckCharS    ,    AT_S_CMD_NAME_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT S命令名状态表 */
AT_SUB_STATE_STRU AT_S_CMD_NAME_STATE_TAB[]=
{
    /* 如果当前状态是AT_S_CMD_NAME_STATE，atCheck_num成功，则进入AT_S_CMD_NAME_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_NAME_STATE    },

    /* 如果当前状态是AT_S_CMD_NAME_STATE，atCheck_equ成功，则进入AT_S_CMD_SET_STATE */
    {    At_CheckEqu    ,    AT_S_CMD_SET_STATE    },

    /* 如果当前状态是AT_S_CMD_NAME_STATE，atCheck_req成功，则进入AT_S_CMD_READ_STATE */
    {    At_CheckReq    ,    AT_S_CMD_READ_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};


/* AT S命令设置状态表 */
AT_SUB_STATE_STRU AT_S_CMD_SET_STATE_TAB[]=
{
    /* 如果当前状态是AT_S_CMD_SET_STATE，atCheck_num成功，则进入AT_S_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_PARA_STATE    },

    /* 如果当前状态是AT_S_CMD_SET_STATE，atCheck_req成功，则进入AT_S_CMD_TEST_STATE */
    {    At_CheckReq    ,    AT_S_CMD_TEST_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT S命令参数状态表 */
AT_SUB_STATE_STRU AT_S_CMD_PARA_STATE_TAB[]=
{
    /* 如果当前状态是AT_S_CMD_PARA_STATE，atCheck_num成功，则进入AT_S_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_PARA_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};


/* AT S命令主状态表 */
AT_MAIN_STATE_STRU AT_S_CMD_MAIN_STATE_TAB[] =
{
    /* 如果当前状态是AT_NONE_STATE，则进入AT_S_CMD_NONE_STATE_TAB子状态表 */
    {    AT_NONE_STATE    ,    AT_S_CMD_NONE_STATE_TAB    },

    /* 如果当前状态是ATCMD_B_CMD_STATE，则进入AT_S_CMD_NAME_STATE_TAB子状态表 */
    {    AT_S_CMD_NAME_STATE    ,    AT_S_CMD_NAME_STATE_TAB    },

    /* 如果当前状态是AT_S_CMD_SET_STATE，则进入AT_S_CMD_SET_STATE_TAB子状态表 */
    {    AT_S_CMD_SET_STATE    ,    AT_S_CMD_SET_STATE_TAB    },

    /* 如果当前状态是AT_S_CMD_PARA_STATE，则进入AT_S_CMD_PARA_STATE_TAB子状态表 */
    {    AT_S_CMD_PARA_STATE    ,    AT_S_CMD_PARA_STATE_TAB    },

    /* 主状态表结束 */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 函数名称: atParseSCmd
 功能描述: 解析AT命令字符串,得出命令名,参数,命令类型,命令操作类型

 参数说明:
   pData [in] 输入的字符串
   usLen [in] 字符串的长度

 返 回 值:
    AT_SUCCESS: 成功
    AT_ERROR: 失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseSCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  设置初始状态 */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  设置初始状态 */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  指向当前正在处理的字符*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  拷贝内容的起始指针 */
    VOS_UINT16 usLength = 0;                        /*  记录当前已经处理的字符个数*/

    /* 依次分析字符串中的每个字符 */
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                      /* 依次比较每个字符 */
    {
        curr_state = new_state;                     /*  当前状态设置为新状态*/

        /*  根据当前处理的字符和当前状态查表得到新状态*/
        new_state = atFindNextMainState(AT_S_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch (new_state)                        /*  状态处理*/
        {
        case AT_S_CMD_NAME_STATE:                /*  S命令名状态*/
            if (curr_state != new_state)          /*  新状态部分不等于当前状态*/
            {
                g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;         /*  设置命令类型*/
                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /*  设置命令操作类型*/
                pucCopyPtr = pucCurrPtr;             /*  准备接收S命令名*/
            }
            break;

        case AT_S_CMD_SET_STATE:                 /* AT S命令等号状态 */

            /* 存储命令名到全局变量中 */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* 设置命令操作类型*/

            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /* 返回错误 */
            }
            break;

        case AT_S_CMD_PARA_STATE:               /* AT S命令参数状态 */
            if (curr_state != new_state)         /* 新状态部分不等于当前状态*/
            {
                pucCopyPtr = pucCurrPtr;            /* 准备接收 S类型命令名*/
            }
            break;

        case AT_S_CMD_READ_STATE:                  /* AT S命令查询参数状态 */

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

            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;  /* 设置命令操作类型*/

            break;

        case AT_S_CMD_TEST_STATE:                  /* AT S命令测试参数状态 */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;  /* 设置命令操作类型*/
            break;

        default:
            return AT_ERROR;                  /* 返回错误 */
        }
        pucCurrPtr++;                             /*  继续分析下一个字符*/
    }

    switch(new_state)                           /*  根据最后的状态判断*/
    {
    case AT_S_CMD_PARA_STATE:                   /* AT S命令参数状态 */

        /* 存储参数到全局变量中 */
        if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_ERROR;
        }

        break;

    case AT_S_CMD_NAME_STATE:                   /* AT S命令状态*/
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
        break;

    case AT_S_CMD_SET_STATE:                         /* 无效状态 */
    case AT_S_CMD_READ_STATE:                         /* 初始状态 */
    case AT_S_CMD_TEST_STATE:                         /* 初始状态 */
        break;

    default:
        return AT_ERROR;                  /* 返回错误 */
    }
    return AT_SUCCESS;                          /*  返回正确*/
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


