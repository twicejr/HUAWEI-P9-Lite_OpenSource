

#include "AtCheckFunc.h"

#include "msp_errno.h"

#include "at_common.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/* AT命令初始状态表 */
AT_SUB_STATE_STRU AT_D_CMD_NONE_STATE_TAB[]=
{
    /* 如果当前状态是ATCMD_NONE_STATE，atCheckCharD成功，则进入AT_D_CMD_NAME_STATE */
    {    At_CheckCharD    ,    AT_D_CMD_NAME_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令命令名状态表 */
AT_SUB_STATE_STRU AT_D_CMD_NAME_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_NAME_STATE，At_CheckCharRightArrow成功，则进入AT_D_CMD_RIGHT_ARROW_STATE */
    {    At_CheckCharRightArrow    ,    AT_D_CMD_RIGHT_ARROW_STATE    },

    /* 如果当前状态是AT_D_CMD_NAME_STATE，atCheckDailString成功，则进入AT_D_CMD_DIALSTRING_STATE */
    {    At_CheckDialNum    ,    AT_D_CMD_DIALSTRING_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令拨号字符串状态表 */
AT_SUB_STATE_STRU AT_D_CMD_DIALSTRING_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，atCheckDailString成功，则进入AT_D_CMD_DIALSTRING_STATE */
    {    At_CheckDialNum    ,    AT_D_CMD_DIALSTRING_STATE    },

    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，At_CheckCharI成功，则进入AT_D_CMD_CHAR_I_STATE */
    {    At_CheckCharI    ,    AT_D_CMD_CHAR_I_STATE    },

    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，At_CheckCharG成功，则进入AT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，At_CheckSemicolon成功，则进入AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令字符I状态表 */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_I_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_CHAR_I_STATE，At_CheckCharG成功，则进入AT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* 如果当前状态是AT_D_CMD_CHAR_I_STATE，At_CheckSemicolon成功，则进入AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令字符G状态表 */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_G_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_CHAR_G_STATE，At_CheckSemicolon成功，则进入AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令右箭头状态表 */
AT_SUB_STATE_STRU AT_D_CMD_RIGHT_ARROW_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_RIGHT_ARROW_STATE，atCheck_quot成功，则进入AT_D_CMD_LEFT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_D_CMD_LEFT_QUOT_STATE    },

    /* 如果当前状态是AT_D_CMD_RIGHT_ARROW_STATE，atCheck_num成功，则进入AT_D_CMD_DIGIT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* 如果当前状态是AT_D_CMD_RIGHT_ARROW_STATE，At_CheckUpLetter成功，则进入AT_D_CMD_CHAR_STATE */
    {    At_CheckUpLetter    ,    AT_D_CMD_CHAR_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令字母状态表 */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_CHAR_STATE，atCheckCharStr成功，则进入AT_D_CMD_CHAR_STATE */
    {    At_CheckUpLetter    ,    AT_D_CMD_CHAR_STATE    },

    /* 如果当前状态是AT_D_CMD_CHAR_STATE，atCheck_quot成功，则进入AT_D_CMD_RIGHT_QUOT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令左引号状态表 */
AT_SUB_STATE_STRU AT_D_CMD_LEFT_QUOT_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_LEFT_QUOT_STATE，atCheckCharStr成功，则进入AT_D_CMD_LEFT_QUOT_STATE */
    {    At_CheckNoQuot    ,    AT_D_CMD_LEFT_QUOT_STATE    },

    /* 如果当前状态是AT_D_CMD_LEFT_QUOT_STATE，atCheck_quot成功，则进入AT_D_CMD_RIGHT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_D_CMD_RIGHT_QUOT_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D命令右引号状态表 */
AT_SUB_STATE_STRU AT_D_CMD_RIGHT_QUOT_STATE_TAB[]=
{
    /* 如果当前状态是AT_D_CMD_RIGHT_ARROW_STATE，atCheck_num成功，则进入AT_D_CMD_DIGIT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，At_CheckCharI成功，则进入AT_D_CMD_CHAR_I_STATE */
    {    At_CheckCharI    ,    AT_D_CMD_CHAR_I_STATE    },

    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，At_CheckCharG成功，则进入AT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，At_CheckSemicolon成功，则进入AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};



/* AT命令主状态表 */
AT_MAIN_STATE_STRU AT_D_CMD_MAIN_STATE_TAB[] =
{
    /* 如果当前状态是AT_NONE_STATE，则进入AT_D_CMD_NONE_STATE_TAB子状态表 */
    {    AT_NONE_STATE    ,    AT_D_CMD_NONE_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_NAME_STATE，则进入AT_D_CMD_NAME_STATE_TAB子状态表 */
    {    AT_D_CMD_NAME_STATE    ,    AT_D_CMD_NAME_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_DIALSTRING_STATE，则进入AT_D_CMD_DIALSTRING_STATE_TAB子状态表 */
    {    AT_D_CMD_DIALSTRING_STATE    ,    AT_D_CMD_DIALSTRING_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_CHAR_I_STATE，则进入AT_D_CMD_CHAR_I_STATE_TAB子状态表 */
    {    AT_D_CMD_CHAR_I_STATE    ,    AT_D_CMD_CHAR_I_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_CHAR_G_STATE，则进入AT_D_CMD_CHAR_G_STATE_TAB子状态表 */
    {    AT_D_CMD_CHAR_G_STATE    ,    AT_D_CMD_CHAR_G_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_CHAR_STATE，则进入AT_D_CMD_CHAR_STATE_TAB子状态表 */
    {    AT_D_CMD_CHAR_STATE    ,    AT_D_CMD_CHAR_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_RIGHT_ARROW_STATE，则进入AT_D_CMD_RIGHT_ARROW_STATE_TAB子状态表 */
    {    AT_D_CMD_RIGHT_ARROW_STATE    ,    AT_D_CMD_RIGHT_ARROW_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_LEFT_QUOT_STATE，则进入AT_D_CMD_LEFT_QUOT_STATE_TAB子状态表 */
    {    AT_D_CMD_LEFT_QUOT_STATE    ,    AT_D_CMD_LEFT_QUOT_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_RIGHT_QUOT_STATE，则进入AT_D_CMD_RIGHT_QUOT_STATE_TAB子状态表 */
    {    AT_D_CMD_RIGHT_QUOT_STATE    ,    AT_D_CMD_RIGHT_QUOT_STATE_TAB    },

    /* 如果当前状态是AT_D_CMD_DIGIT_STATE，则进入AT_D_CMD_DIGIT_STATE_TAB子状态表 */
    {    AT_D_CMD_DIGIT_STATE    ,    AT_D_CMD_RIGHT_QUOT_STATE_TAB    },

    /* 主状态表结束 */
    {    AT_BUTT_STATE    ,    NULL    },
};

/*******************************************************************************
 函数名称: atParseDCmd
 功能描述: 解析AT命令字符串,得出命令名,参数,命令类型,命令操作类型
            D[<dial_string>][I][G][;]
            D>mem<n>[I][G][;]
            D><n>[I][G][;]
            D><name>[I][G][;]

 参数说明:
   pData [in/out] 输入的字符串
   usLen [in] 字符串的长度

 返 回 值:
    AT_SUCCESS: 成功
    AT_FAILURE: 失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
******************************************************************************/

static VOS_UINT32 atParseDCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  设置初始状态 */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  设置初始状态 */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  指向当前正在处理的字符*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  拷贝内容的起始指针 */
    VOS_UINT16 usLength = 0;                        /*  记录当前已经处理的字符个数*/

    /* 依次分析字符串中的每个字符*/
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                     /* 依次比较每个字符 */
    {
        curr_state = new_state;                  /* 当前状态设置为新状态*/

        /* 根据当前处理的字符和当前状态查表得到新状态*/
        new_state = atFindNextMainState(AT_D_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                        /* 状态处理*/
        {
        case AT_D_CMD_NAME_STATE:                /* AT D命令命令名状态 */
            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;     /* 设置命令类型*/
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* 设置命令操作类型*/
            pucCopyPtr = pucCurrPtr;                 /* 准备接收D类型命令名*/
            break;

        case AT_D_CMD_RIGHT_ARROW_STATE:         /* AT D命令右箭头状态 */
        case AT_D_CMD_DIALSTRING_STATE:          /* AT D命令拨号字符串状态 */
            if(curr_state != new_state)          /* 新状态部分不等于当前状态*/
            {
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /* 返回错误 */
                }
                pucCopyPtr = pucCurrPtr;             /* 准备接收参数*/
            }
            break;

        case AT_D_CMD_DIGIT_STATE:               /* AT D命令数字状态 */
        case AT_D_CMD_LEFT_QUOT_STATE:           /* AT D命令左引号状态 */
        case AT_D_CMD_CHAR_STATE:
            if(curr_state != new_state)          /* 新状态部分不等于当前状态*/
            {
                /* 存储参数到全局变量中 */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* 准备接收下一个参数*/
            }
            break;

        case AT_D_CMD_CHAR_I_STATE:              /* AT D命令字符I状态 */
        case AT_D_CMD_CHAR_G_STATE:              /* AT D命令字符G状态 */
        case AT_D_CMD_SEMICOLON_STATE:           /* AT D命令分号状态 */
            /* 存储参数到全局变量中 */
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
            {
                return AT_FAILURE;
            }

            pucCopyPtr = pucCurrPtr;                /* 准备接收下一个参数*/
            break;

        case AT_BUTT_STATE:                     /* 无效状态 */
            return AT_FAILURE;                  /* 返回错误 */

        default:
            break;
        }
        pucCurrPtr++;                             /* 继续分析下一个字符*/
    }

    switch(new_state)                           /* 根据最后的状态判断*/
    {
    case AT_D_CMD_SEMICOLON_STATE:              /* AT D命令分号状态 */
        break;

    case AT_D_CMD_DIALSTRING_STATE:             /* AT D命令拨号字符串状态 */
    case AT_D_CMD_DIGIT_STATE:                  /* AT D命令数字状态 */
    case AT_D_CMD_RIGHT_QUOT_STATE:             /* AT D命令右引号状态 */
    case AT_D_CMD_CHAR_G_STATE:                 /* AT D命令字符G状态 */
    case AT_D_CMD_CHAR_I_STATE:                 /* AT D命令字符I状态 */
        /* 存储参数到全局变量中 */
        if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_FAILURE;
        }

        break;

    default:
        return AT_FAILURE;                      /* 返回错误*/
    }
    return AT_SUCCESS;                          /* 返回正确*/
}

/******************************************************************************
 函 数 名  : atCdataParseDCmd
 功能描述  : 保存#777拨号信息
 输入参数  : VOS_UINT8                          *pData
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
VOS_VOID atCdataParseDCmd(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;            /* 设置命令类型*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* 设置命令操作类型*/

    /* 接收D类型命令名*/
    g_stATParseCmd.stCmdName.usCmdNameLen = 1;
    g_stATParseCmd.stCmdName.aucCmdName[0] = *pData;
}



/******************************************************************************
 函数名称: atScanDcmdModifier
 功能描述: 扫描D命令的修饰符

 参数说明:
   pData [in/out] 需检查的字符串
   pLen [in/out] 需检查的字符串长度地址

 返 回 值:
    TODO: ...

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
******************************************************************************/
static VOS_VOID atScanDcmdModifier( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT16 usChkLen  = 0;
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = pData;
    VOS_UINT8  *pRead    = pData;

    /* 输入参数检查 */
    while ( usChkLen++ < *pLen )
    {
        /*删除修饰符，',','T','P','!','W','@'*/
        if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
            && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }

    *pLen  =  usLen;
    return;
}

/******************************************************************************
 函数名称: atScanDmcmdModifier
 功能描述: 扫描Dm命令的修饰符

 参数说明:
   pData [in/out] 需检查的字符串
   pLen [in/out] 需检查的字符串长度地址

 返 回 值:
    TODO: ...

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]

  2.日    期   : 2013年10月12日
    作    者   : l00198894
    修改内容   : DTS2013100901373:ATD命令PPP拨号参数解析
******************************************************************************/
static VOS_VOID atScanDmcmdModifier( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = VOS_NULL_PTR;
    VOS_UINT8  *pRead    = VOS_NULL_PTR;
    VOS_UINT8  *pTmp     = VOS_NULL_PTR;
    VOS_UINT8  *pDataTmp = VOS_NULL_PTR;
    VOS_UINT8  aucStr[]  = "*99**PPP";
    VOS_UINT16 usStrLen  = 0;

    pDataTmp = (VOS_UINT8*)AT_MALLOC(*pLen + 1);
    if (VOS_NULL_PTR == pDataTmp)
    {
        vos_printf("atScanDmcmdModifier(): AT_MALLOC Failed!\n");
        return;
    }

    atRangeCopy(pDataTmp, pData, (pData + *pLen));

    /* 保证字符串有结束符 */
    pDataTmp[*pLen] = 0;

    pRead   = pDataTmp;
    pWrite  = pDataTmp;

    pTmp = (VOS_UINT8*)AT_STRSTR((VOS_CHAR *)pDataTmp,(VOS_CHAR *)aucStr);
    if(NULL != pTmp)
    {
        usStrLen = (VOS_UINT16)AT_STRLEN((VOS_CHAR *)aucStr);
        /* 检查前一半参数 */
        while ( pRead < pTmp )
        {
            /*删除修饰符，',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
        while( pRead < (pTmp+usStrLen) )
        {
            *pWrite++ = *pRead++;
            usLen++;
        }
        while( pRead < (pDataTmp+(*pLen)) )
        {
            /*删除修饰符，',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
    }
    else
    {
        /* 输入参数检查 */
        while ( pRead < (pDataTmp+(*pLen)) )
        {
            /*删除修饰符，',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
    }

    atRangeCopy(pData, pDataTmp, (pDataTmp + *pLen));

    *pLen = usLen;

    AT_FREE(pDataTmp);
    return;
}

/******************************************************************************
 函数名称: ScanQuateChar
 功能描述: 去除字符串中的引号(D命令解析前的处理)

 参数说明:
   pData [in/out] 字符串内容
   usLen [in] 字符串长度

 作    者: 崔军强/00064416 [2011-04-01]
******************************************************************************/
static VOS_UINT32 ScanQuateChar( VOS_UINT8 * pData, VOS_UINT16 * pusLen)
{
    VOS_UINT8 *pWrite = pData;
    VOS_UINT8 *pRead  = pData;
    VOS_UINT16 usChkLen = 0;
    VOS_UINT16 usLen    = 0;

    if(0 == *pusLen)
    {
        return AT_FAILURE;
    }

    while(usChkLen++ < *pusLen)
    {
        /* 去除引号 */
        if('"' != *pRead)
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pusLen = usLen;

    return AT_SUCCESS;
}


/******************************************************************************
 函数名称: ParseDCmdPreProc
 功能描述: D命令解析前的预处理

 参数说明:
   pData [in/out] 字符串内容
   usLen [in] 字符串长度

 作    者: 崔军强/00064416 [2011-04-01]

  2.日    期   : 2012年11月16日
    作    者   : f62575
    修改内容  : 问题单DTS2012111409590: 解决拨ATD38944425#123i，返回50的错误码问题

  3.日    期   : 2013年10月12日
    作    者   : l00198894
    修改内容   : DTS2013100901373:ATD命令PPP拨号参数解析

******************************************************************************/
VOS_UINT32 ParseDCmdPreProc( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT16 usTmpLen = usLen;
    VOS_UINT8* pTmp = pData;
    VOS_UINT32 ulResult = AT_FAILURE;

    /* 为了规避LINUX下拨号命令中带有引号(ATDT"*99#")的问题，将引号去除 */
    ScanQuateChar(pTmp, &usTmpLen);

#if 0
    if(AT_SUCCESS == atCheckMmiString(pTmp,usTmpLen))              /* 补充业务处理 */
    {
        if(AT_FAILURE == At_CheckCharWell(pTmp[usTmpLen - 1]))      /* 如果不是以#号结尾 */
        {
            atScanDcmdModifier(pTmp,&usTmpLen);                    /* 扫描修饰符 */

            /* 因为要把命令名拷贝到gstATCmdName.usCmdNameLen中以备命令匹配，
            所以，把内容拷贝到参数列表的第一个缓存中*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;                   /* 设置命令类型 */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;          /* 设置命令操作类型 */
            g_stATParseCmd.stCmdName.usCmdNameLen = 1;
            g_stATParseCmd.stCmdName.aucCmdName[0] = 'D';
            ulResult = AT_SUCCESS;
        }
        else
        {
            atScanDmcmdModifier(pTmp,&usTmpLen);                    /* 扫描修饰符 */

            /* 因为要把命令名拷贝到gstATCmdName.usCmdNameLen中以备命令匹配，
            所以，把内容拷贝到参数列表的第一个缓存中*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDMCmd(pTmp,usTmpLen);                /* 如果带分号 */
            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }
        }
    }
    else
#endif    
    {
        if(AT_SUCCESS == At_CheckCharWell(pTmp[usTmpLen - 1]))      /* 如果不是以#号结尾 */
        {
            atScanDmcmdModifier(pTmp,&usTmpLen);                    /* 扫描修饰符 */

            /* 因为要把命令名拷贝到gstATCmdName.usCmdNameLen中以备命令匹配，
            所以，把内容拷贝到参数列表的第一个缓存中*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDMCmd(pTmp,usTmpLen);                /* 如果带分号 */
            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }
        }
        /* 解析#777,判断"#777"命令字符 */
        else if (AT_CheckStrStartWith(&pTmp[1], (VOS_UINT8 *)"#777"))
        {
            ulResult = AT_SaveCdataDialParam(pTmp, usTmpLen);

            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }

            atCdataParseDCmd(pTmp,usTmpLen);
        }
        else
        {
            if(AT_FAILURE == atCheckRightArrowStr(pTmp,usTmpLen))
            {
                atScanDcmdModifier(pTmp,&usTmpLen);                        /* 扫描修饰符 */
            }

            /* 因为要把命令名拷贝到gstATCmdName.usCmdNameLen中以备命令匹配，
            所以，把内容拷贝到参数列表的第一个缓存中*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDCmd(pTmp,usTmpLen);                       /* D命令 */

            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }

        }
    }

    return ulResult;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


