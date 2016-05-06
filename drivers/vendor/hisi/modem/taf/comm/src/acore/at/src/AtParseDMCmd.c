

#include "AtCheckFunc.h"

#include "msp_errno.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/* AT命令初始状态表 */
AT_SUB_STATE_STRU AT_DM_CMD_NONE_STATE_TAB[]=
{
    /* 如果当前状态是ATCMD_NONE_STATE，atCheckCharD成功，则进入AT_DM_CMD_NAME_STATE */
    {    At_CheckCharD    ,    AT_DM_CMD_NAME_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DM命令命令名状态表 */
AT_SUB_STATE_STRU AT_DM_CMD_NAME_STATE_TAB[]=
{
    /* 如果当前状态是AT_DM_CMD_NAME_STATE，At_CheckCharStar成功，则进入AT_DM_CMD_STAR_STATE */
    {    At_CheckCharStar    ,    AT_DM_CMD_STAR_STATE    },

    /* 如果当前状态是AT_D_CMD_NAME_STATE，At_CheckCharWell成功，则进入AT_DM_CMD_WELL_STATE */
    {    At_CheckCharWell    ,    AT_DM_CMD_WELL_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DM命令字符状态表 */
AT_SUB_STATE_STRU AT_DM_CMD_CHAR_STATE_TAB[]=
{
    /* 如果当前状态是AT_DM_CMD_NAME_STATE，At_CheckCharStar成功，则进入AT_DM_CMD_STAR_STATE */
    {    At_CheckCharStar    ,    AT_DM_CMD_STAR_STATE    },

    /* 如果当前状态是AT_DM_CMD_NAME_STATE，At_CheckCharStar成功，则进入AT_DM_CMD_WELL_STATE */
    {    At_CheckCharWell    ,    AT_DM_CMD_WELL_STATE    },

    /* 如果当前状态是AT_DM_CMD_NAME_STATE，At_CheckCharStar成功，则进入AT_DM_CMD_NUM_STATE */
    {    At_CheckDmChar    ,    AT_DM_CMD_NUM_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT命令主状态表 */
AT_MAIN_STATE_STRU AT_DM_CMD_MAIN_STATE_TAB[] =
{
    /* 如果当前状态是AT_NONE_STATE，则进入AT_DM_CMD_NONE_STATE_TAB子状态表 */
    {    AT_NONE_STATE    ,    AT_DM_CMD_NONE_STATE_TAB    },

    /* 如果当前状态是AT_DM_CMD_NAME_STATE，则进入AT_DM_CMD_NAME_STATE_TAB子状态表 */
    {    AT_DM_CMD_NAME_STATE    ,    AT_DM_CMD_NAME_STATE_TAB    },

    /* 如果当前状态是AT_DM_CMD_NUM_STATE，则进入AT_DM_CMD_CHAR_STATE_TAB子状态表 */
    {    AT_DM_CMD_NUM_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* 如果当前状态是AT_DM_CMD_STAR_STATE，则进入AT_DM_CMD_CHAR_STATE_TAB子状态表 */
    {    AT_DM_CMD_STAR_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* 如果当前状态是AT_DM_CMD_WELL_STATE，则进入AT_DM_CMD_CHAR_STATE_TAB子状态表 */
    {    AT_DM_CMD_WELL_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* 主状态表结束 */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 函数名称: atParseDMCmd
 功能描述: 解析AT命令字符串,得出命令名,参数,命令类型,命令操作类型
              D*<GPRS_SC>[*[<called_address>][*[<L2P>][*[<cid>]]]]#
              D*<GPRS_SC_IP>[*<cid>[,<cid>]]#
              D**61*+1812555673*11*25#  ---  呼叫补充业务,此条命令需要调用MMI接口
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

VOS_UINT32 atParseDMCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  设置初始状态 */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  设置初始状态 */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  指向当前正在处理的字符*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  拷贝内容的起始指针 */
    VOS_UINT16 usLength = 0;                        /*  记录当前已经处理的字符个数*/

    /* 依次分析字符串中的每个字符*/
    while ( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))       /* 依次比较每个字符 */
    {
        curr_state = new_state;                  /* 当前状态设置为新状态*/

        /* 根据当前处理的字符和当前状态查表得到新状态*/
        new_state = atFindNextMainState(AT_DM_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch (new_state)                        /* 状态处理*/
        {
        case AT_DM_CMD_NAME_STATE:                /* AT DM命令命令名状态 */
            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;     /* 设置命令类型*/
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* 设置命令操作类型*/
            pucCopyPtr = pucCurrPtr;                 /* 准备接收DM类型命令名*/
            break;

        /* 有可能数字长度过界，或者gucAtParaIndex过界 */
        case AT_DM_CMD_NUM_STATE:                /* AT DM命令字符状态 */
            if (curr_state != new_state)          /* 新状态部分不等于当前状态*/
            {
                /* 存储参数到全局变量中 */
                if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* 准备接收下一个参数*/
            }
            break;

        case AT_DM_CMD_WELL_STATE:                /* AT DM命令字符#状态 */
        case AT_DM_CMD_STAR_STATE:                /* AT DM命令字符*状态 */
            if (AT_DM_CMD_NAME_STATE == curr_state)
            {
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /* 返回错误 */
                }
                pucCopyPtr = pucCurrPtr;             /* 准备接收参数*/
            }
            else
            {
                /* 存储参数到全局变量中 */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* 准备接收下一个参数*/
            }
            break;

        default:
            return AT_FAILURE;                  /* 返回错误 */
        }

        pucCurrPtr++;                             /* 继续分析下一个字符*/
    }

    switch (new_state)                           /* 根据最后的状态判断*/
    {
    case AT_DM_CMD_WELL_STATE:                   /* AT DM命令字符#状态 */
        break;

    default:
        return AT_FAILURE;                      /* 返回错误*/
    }
    
    return AT_SUCCESS;                          /* 返回正确*/
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


