

#include "AtCheckFunc.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSEPARA_C
/*lint +e960*/


/* 参数匹配初始空状态表 */
AT_SUB_STATE_STRU AT_PARA_NONE_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_NONE_STATE，atCheckLeftBracket成功，则进入AT_PARA_LEFT_BRACKET_STATE */
    {    At_CheckLeftBracket    ,    AT_PARA_LEFT_BRACKET_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配左括号状态表 */
AT_SUB_STATE_STRU AT_PARA_LEFT_BRACKET_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_LEFT_BRACKET_STATE，atCheckZero成功，则进入AT_PARA_ZERO_STATE */
    {At_CheckChar0,   AT_PARA_ZERO_STATE},

    /* 如果当前状态是AT_PARA_LEFT_BRACKET_STATE，atCheckDigit成功，则进入AT_PARA_NUM_STATE */
    {At_CheckDigit,  AT_PARA_NUM_STATE},

    /* 如果当前状态是AT_PARA_LEFT_BRACKET_STATE，at_NoQuotLetter成功，则进入AT_PARA_NO_QUOT_LETTER_STATE */
    {atNoQuotLetter, AT_PARA_NO_QUOT_LETTER_STATE},

    /* 如果当前状态是AT_PARA_LEFT_BRACKET_STATE，atCheckLetter成功，则进入AT_PARA_LETTER_STATE */
    {At_CheckLetter, AT_PARA_LETTER_STATE},

    /* 如果当前状态是AT_PARA_LEFT_BRACKET_STATE，atCheckQuot成功，则进入AT_PARA_LEFT_QUOT_STATE */
    {At_CheckQuot,   AT_PARA_LEFT_QUOT_STATE},

    /* 子状态表结束 */
    {NULL,           AT_BUTT_STATE},
};

/* 参数匹配参数状态表 */
AT_SUB_STATE_STRU AT_PARA_NUM_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_NUM_STATE，atCheckDigit成功，则进入AT_PARA_NUM_STATE */
    {   At_CheckDigit   ,   AT_PARA_NUM_STATE    },

    /* 如果当前状态是AT_PARA_NUM_STATE，atCheckColon成功，则进入AT_PARA_NUM_COLON_STATE */
    {   atCheckComma ,   AT_PARA_NUM_COLON_STATE  },

    /* 如果当前状态是AT_PARA_NUM_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  , AT_PARA_RIGHT_BRACKET_STATE   },

    /* 如果当前状态是AT_PARA_NUM_STATE，atCheckCharSub成功，则进入AT_PARA_SUB_STATE */
    {   At_CheckCharSub   ,   AT_PARA_SUB_STATE    },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配范围状态表 */
AT_SUB_STATE_STRU AT_PARA_SUB_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_SUB_STATE，atCheckZero成功，则进入AT_PARA_ZERO_SUB_STATE */
    {At_CheckChar0,  AT_PARA_ZERO_SUB_STATE},

    /* 如果当前状态是AT_PARA_SUB_STATE，atCheckDigit成功，则进入AT_PARA_NUM_SUB_STATE */
    {At_CheckDigit, AT_PARA_NUM_SUB_STATE},

    /* 子状态表结束 */
    {NULL,          AT_BUTT_STATE},
};

/* 参数匹配范围数字状态表 */
AT_SUB_STATE_STRU AT_PARA_NUM_SUB_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckDigit成功，则进入AT_PARA_NUM_SUB_STATE */
    {   At_CheckDigit   ,   AT_PARA_NUM_SUB_STATE    },

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckColon成功，则进入AT_PARA_NUM_SUB_COLON_STATE */
    {   atCheckComma ,   AT_PARA_NUM_SUB_COLON_STATE  },

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  ,   AT_PARA_RIGHT_BRACKET_STATE   },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配范围数字逗号状态表 */
AT_SUB_STATE_STRU AT_PARA_NUM_SUB_COLON_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_NUM_SUB_COLON_STATE，atCheckZero成功，则进入AT_PARA_ZERO_STATE */
    {At_CheckChar0,  AT_PARA_ZERO_STATE},

    /* 如果当前状态是AT_PARA_NUM_SUB_COLON_STATE，atCheckDigit成功，则进入AT_PARA_NUM_STATE */
    {At_CheckDigit, AT_PARA_NUM_STATE},

    /* 子状态表结束 */
    {NULL,          AT_BUTT_STATE},
};

/* 参数匹配右括号状态表 */
AT_SUB_STATE_STRU AT_PARA_RIGHT_BRACKET_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_RIGHT_BRACKET_STATE，atCheckColon成功，则进入AT_PARA_COLON_STATE */
    {   atCheckComma ,   AT_PARA_COLON_STATE  },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配逗号状态表 */
AT_SUB_STATE_STRU AT_PARA_COLON_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_COLON_STATE，atCheckLeftBracket成功，则进入AT_PARA_LEFT_BRACKET_STATE */
    {   At_CheckLeftBracket  ,   AT_PARA_LEFT_BRACKET_STATE   },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配左引号状态表 */
AT_SUB_STATE_STRU AT_PARA_LEFT_QUOT_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_LEFT_QUOT_STATE，atCheckNoQuot成功，则进入AT_PARA_LEFT_QUOT_STATE */
    {   At_CheckNoQuot   ,   AT_PARA_LEFT_QUOT_STATE },

    /* 如果当前状态是AT_PARA_LEFT_QUOT_STATE，atCheckQuot成功，则进入AT_PARA_RIGHT_QUOT_STATE */
    {   At_CheckQuot ,    AT_PARA_RIGHT_QUOT_STATE },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配右引号状态表 */
AT_SUB_STATE_STRU AT_PARA_RIGHT_QUOT_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_RIGHT_QUOT_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  ,   AT_PARA_RIGHT_BRACKET_STATE   },

    /* 如果当前状态是AT_PARA_RIGHT_QUOT_STATE，atCheckColon成功，则进入AT_PARA_QUOT_COLON_STATE */
    {   atCheckComma ,   AT_PARA_QUOT_COLON_STATE },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配字母状态表 */
AT_SUB_STATE_STRU AT_PARA_LETTER_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_LETTER_STATE，atCheckLetter成功，则进入AT_PARA_LETTER_STATE */
    {   At_CheckLetter    ,   AT_PARA_LETTER_STATE },

    /* 如果当前状态是AT_PARA_LETTER_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {   At_CheckRightBracket  ,   AT_PARA_RIGHT_BRACKET_STATE   },

    /* 如果当前状态是AT_PARA_LETTER_STATE，atCheckCharSub成功，则进入AT_PARA_LETTER_STATE */
    {   At_CheckCharSub   ,   AT_PARA_LETTER_STATE },

    /* 如果当前状态是AT_PARA_LETTER_STATE，atCheckColon成功，则进入AT_PARA_LETTER_STATE */
    {   atCheckColon     ,   AT_PARA_LETTER_STATE },

    /* 如果当前状态是AT_PARA_LETTER_STATE，atCheckblank成功，则进入AT_PARA_LETTER_STATE */
    {   atCheckblank     ,   AT_PARA_LETTER_STATE },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* 参数匹配数字逗号状态表 */
AT_SUB_STATE_STRU AT_PARA_NUM_COLON_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_NUM_COLON_STATE，atCheckZero成功，则进入AT_PARA_ZERO_STATE */
    {At_CheckChar0,  AT_PARA_ZERO_STATE},

    /* 如果当前状态是AT_PARA_NUM_COLON_STATE，atCheckDigit成功，则进入AT_PARA_NUM_STATE */
    {At_CheckDigit, AT_PARA_NUM_STATE},

    /* 子状态表结束 */
    {NULL,          AT_BUTT_STATE},
};

/* 参数匹配引号逗号状态表 */
AT_SUB_STATE_STRU AT_PARA_QUOT_COLON_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_QUOT_COLON_STATE，atCheckQuot成功，则进入AT_PARA_LEFT_QUOT_STATE */
    {   At_CheckQuot  ,   AT_PARA_LEFT_QUOT_STATE },

    /* 子状态表结束 */
    {    NULL    ,    AT_BUTT_STATE    },
};


/* 支持八进制、十六进制参数 BEGIN */

/* 参数匹配数字0状态表 */
AT_SUB_STATE_STRU AT_PARA_ZERO_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_ZERO_STATE，at_CheckHex成功，则进入AT_PARA_HEX_STATE */
    {atCheckHex,          AT_PARA_HEX_STATE},

    /* 如果当前状态是AT_PARA_ZERO_STATE，atCheckDigit成功，则进入AT_PARA_NUM_STATE */
    {At_CheckDigit,        AT_PARA_NUM_STATE},

    /* 如果当前状态是AT_PARA_ZERO_STATE，atCheckColon成功，则进入AT_PARA_NUM_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_COLON_STATE},

    /* 如果当前状态是AT_PARA_ZERO_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE},

    /* 如果当前状态是AT_PARA_ZERO_STATE，atCheckCharSub成功，则进入AT_PARA_SUB_STATE */
    {At_CheckCharSub,      AT_PARA_SUB_STATE},

    /* 子状态表结束 */
    {NULL,                 AT_BUTT_STATE},
};

/* 参数匹配十六进制状态表 */
AT_SUB_STATE_STRU AT_PARA_HEX_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_HEX_STATE，at_CheckHex成功，则进入AT_PARA_HEX_NUM_STATE */
    {atCheckHexNum, AT_PARA_HEX_NUM_STATE},

    /* 子状态表结束 */
    {NULL,           AT_BUTT_STATE},
};

/* 参数匹配十六进制数字状态表 */
AT_SUB_STATE_STRU AT_PARA_HEX_NUM_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_ZERO_STATE，at_CheckHex成功，则进入AT_PARA_HEX_STATE */
    {atCheckHexNum,       AT_PARA_HEX_NUM_STATE},

    /* 如果当前状态是AT_PARA_ZERO_STATE，atCheckColon成功，则进入AT_PARA_NUM_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_COLON_STATE},

    /* 如果当前状态是AT_PARA_ZERO_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE},

    /* 如果当前状态是AT_PARA_ZERO_STATE，atCheckCharSub成功，则进入AT_PARA_SUB_STATE */
    {At_CheckCharSub,      AT_PARA_SUB_STATE},

    /* 子状态表结束 */
    {NULL,                 AT_BUTT_STATE},
};

/* 参数匹配范围数字0状态表 */
AT_SUB_STATE_STRU AT_PARA_ZERO_SUB_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_ZERO_SUB_STATE，at_CheckHex成功，则进入AT_PARA_HEX_SUB_STATE */
    {atCheckHex,          AT_PARA_HEX_SUB_STATE},

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckDigit成功，则进入AT_PARA_NUM_SUB_STATE */
    {At_CheckDigit,        AT_PARA_NUM_SUB_STATE    },

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckColon成功，则进入AT_PARA_NUM_SUB_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_SUB_COLON_STATE  },

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE   },

    /* 子状态表结束 */
    {NULL,                 AT_BUTT_STATE    },
};

/* 参数匹配范围十六进制状态表 */
AT_SUB_STATE_STRU AT_PARA_HEX_SUB_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_HEX_SUB_STATE，at_CheckHex成功，则进入AT_PARA_HEX_NUM_SUB_STATE */
    {atCheckHexNum, AT_PARA_HEX_NUM_SUB_STATE},

    /* 子状态表结束 */
    {NULL,           AT_BUTT_STATE},
};

/* 参数匹配范围十六进制数字状态表 */
AT_SUB_STATE_STRU AT_PARA_HEX_NUM_SUB_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_HEX_NUM_SUB_STATE，at_CheckHexNum成功，则进入AT_PARA_HEX_NUM_SUB_STATE */
    {atCheckHexNum,       AT_PARA_HEX_NUM_SUB_STATE},

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckColon成功，则进入AT_PARA_NUM_SUB_COLON_STATE */
    {atCheckComma,        AT_PARA_NUM_SUB_COLON_STATE  },

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE   },

    /* 子状态表结束 */
    {NULL,                 AT_BUTT_STATE    },
};

/* 支持八进制、十六进制参数 END */

/* 支持无双引号包括字符串 BEGIN */

/* 参数匹配无双引号包括字母状态表 */
AT_SUB_STATE_STRU AT_PARA_NO_QUOT_LETTER_STATE_TAB[]=
{
    /* 如果当前状态是AT_PARA_NO_QUOT_LETTER_STATE，atCheckLetter成功，则进入AT_PARA_NO_QUOT_LETTER_STATE */
    {At_CheckLetter,       AT_PARA_NO_QUOT_LETTER_STATE },

    /* 如果当前状态是AT_PARA_NO_QUOT_LETTER_STATE，atCheckRightBracket成功，则进入AT_PARA_RIGHT_BRACKET_STATE */
    {At_CheckRightBracket, AT_PARA_RIGHT_BRACKET_STATE   },

    /* 子状态表结束 */
    {NULL,                 AT_BUTT_STATE    },
};

/* 支持无双引号包括字符串 END */

/* 参数匹配主状态表 */
AT_MAIN_STATE_STRU AT_MAIN_PARA_STATE_TAB[] =
{
    /* 如果当前状态是AT_NONE_STATE，则进入AT_PARA_NONE_STATE_TAB子状态表 */
    {   AT_NONE_STATE   ,   AT_PARA_NONE_STATE_TAB  },

    /* 如果当前状态是AT_PARA_LEFT_BRACKET_STATE，则进入AT_PARA_LEFT_BRACKET_STATE_TAB子状态表 */
    {   AT_PARA_LEFT_BRACKET_STATE  , AT_PARA_LEFT_BRACKET_STATE_TAB    },

    /* 如果当前状态是AT_PARA_RIGHT_BRACKET_STATE，则进入AT_PARA_RIGHT_BRACKET_STATE_TAB子状态表 */
    {   AT_PARA_RIGHT_BRACKET_STATE  , AT_PARA_RIGHT_BRACKET_STATE_TAB    },

    /* 如果当前状态是AT_PARA_LETTER_STATE，则进入AT_PARA_LETTER_STATE_TAB子状态表 */
    {   AT_PARA_LETTER_STATE    ,   AT_PARA_LETTER_STATE_TAB    },

    /* 如果当前状态是AT_PARA_NUM_STATE，则进入AT_PARA_NUM_STATE_TAB子状态表 */
    {   AT_PARA_NUM_STATE    ,   AT_PARA_NUM_STATE_TAB  },

    /* 如果当前状态是AT_PARA_NUM_COLON_STATE，则进入AT_PARA_NUM_COLON_STATE_TAB子状态表 */
    {   AT_PARA_NUM_COLON_STATE ,    AT_PARA_NUM_COLON_STATE_TAB  },

    /* 如果当前状态是AT_PARA_SUB_STATE，则进入AT_PARA_SUB_STATE_TAB子状态表 */
    {   AT_PARA_SUB_STATE    ,   AT_PARA_SUB_STATE_TAB  },

    /* 如果当前状态是AT_PARA_NUM_SUB_STATE，则进入AT_PARA_NUM_SUB_STATE_TAB子状态表 */
    {   AT_PARA_NUM_SUB_STATE   ,  AT_PARA_NUM_SUB_STATE_TAB  },

    /* 如果当前状态是AT_PARA_NUM_SUB_COLON_STATE，则进入AT_PARA_NUM_SUB_COLON_STATE_TAB子状态表 */
    {   AT_PARA_NUM_SUB_COLON_STATE  ,   AT_PARA_NUM_SUB_COLON_STATE_TAB  },

    /* 如果当前状态是AT_PARA_COLON_STATE，则进入AT_PARA_COLON_STATE_TAB子状态表 */
    {   AT_PARA_COLON_STATE ,    AT_PARA_COLON_STATE_TAB  },

    /* 如果当前状态是AT_PARA_LEFT_QUOT_STATE，则进入AT_PARA_LEFT_QUOT_STATE_TAB子状态表 */
    {   AT_PARA_LEFT_QUOT_STATE ,   AT_PARA_LEFT_QUOT_STATE_TAB    },

    /* 如果当前状态是AT_PARA_RIGHT_QUOT_STATE，则进入AT_PARA_RIGHT_QUOT_STATE_TAB子状态表 */
    {   AT_PARA_RIGHT_QUOT_STATE    ,   AT_PARA_RIGHT_QUOT_STATE_TAB    },

    /* 如果当前状态是AT_PARA_QUOT_COLON_STATE，则进入AT_PARA_QUOT_COLON_STATE_TAB子状态表 */
    {   AT_PARA_QUOT_COLON_STATE    ,   AT_PARA_QUOT_COLON_STATE_TAB    },

    /* 如果当前状态是AT_PARA_ZERO_STATE，则进入AT_PARA_ZERO_STATE_TAB子状态表 */
    {AT_PARA_ZERO_STATE,           AT_PARA_ZERO_STATE_TAB},

    /* 如果当前状态是AT_PARA_ZERO_SUB_STATE，则进入AT_PARA_ZERO_SUB_STATE_TAB子状态表 */
    {AT_PARA_ZERO_SUB_STATE,       AT_PARA_ZERO_SUB_STATE_TAB},

    /* 如果当前状态是AT_PARA_HEX_STATE，则进入AT_PARA_HEX_STATE_TAB子状态表 */
    {AT_PARA_HEX_STATE,            AT_PARA_HEX_STATE_TAB},

    /* 如果当前状态是AT_PARA_HEX_NUM_STATE，则进入AT_PARA_HEX_NUM_STATE_TAB子状态表 */
    {AT_PARA_HEX_NUM_STATE,        AT_PARA_HEX_NUM_STATE_TAB},

    /* 如果当前状态是AT_PARA_HEX_SUB_STATE，则进入AT_PARA_HEX_SUB_STATE_TAB子状态表 */
    {AT_PARA_HEX_SUB_STATE,        AT_PARA_HEX_SUB_STATE_TAB},

    /* 如果当前状态是AT_PARA_HEX_NUM_SUB_STATE，则进入AT_PARA_HEX_NUM_SUB_STATE_TAB子状态表 */
    {AT_PARA_HEX_NUM_SUB_STATE,    AT_PARA_HEX_NUM_SUB_STATE_TAB},

    /* 如果当前状态是AT_PARA_NO_QUOT_LETTER_STATE，则进入AT_PARA_NO_QUOT_LETTER_STATE_TAB子状态表 */
    {AT_PARA_NO_QUOT_LETTER_STATE, AT_PARA_NO_QUOT_LETTER_STATE_TAB},

    /* 主状态表结束 */
    {   AT_BUTT_STATE   ,   NULL  },
};

pAtChkFuncType      pgAtCheckFunc   = NULL;

/******************************************************************************
 函数名称: atCmparePara
 功能描述: 参数比较

 参数说明:
  This function has no arguments.

 返 回 值:
    AT_SUCCESS: 成功
    AT_FAILURE: 失败

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atCmparePara(VOS_VOID)
{
    /*检查输入参数*/
    if(NULL != pgAtCheckFunc)
    {
        /*检查参数列表对应的参数是否存在*/
        if(0 < gastAtParaList[g_stATParseCmd.ucParaCheckIndex].usParaLen)
        {
            /*如果参数检查错误*/
            if(AT_SUCCESS != pgAtCheckFunc(&gastAtParaList[g_stATParseCmd.ucParaCheckIndex]))
            {
                return AT_FAILURE;           /*  返回错误*/
            }
        }

        /*记录已检查参数的全局变量加1*/
        g_stATParseCmd.ucParaCheckIndex++;

        /*清空，以备比较下一个参数,否则，对比参数继续增加*/
        if(0 != g_stATParseCmd.ucParaNumRangeIndex)
        {
            g_stATParseCmd.ucParaNumRangeIndex = 0;
            PS_MEM_SET(g_stATParseCmd.astParaNumRange,0x00,sizeof(g_stATParseCmd.astParaNumRange));
        }

        if(0 != g_stATParseCmd.ucParaStrRangeIndex)
        {
            g_stATParseCmd.ucParaStrRangeIndex = 0;
            PS_MEM_SET(g_stATParseCmd.auStrRange,0x00,sizeof(g_stATParseCmd.auStrRange));
        }

        pgAtCheckFunc = NULL;

        return AT_SUCCESS;                   /*  返回正确*/
    }
    else
    {
        return AT_FAILURE;                   /*  返回错误*/
    }
}

/******************************************************************************
 函数名称: atParsePara
 功能描述: 解析参数脚本字符串,与命令解析得出的参数进行比较,并返回结果

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

VOS_UINT32 atParsePara( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT16 usLength = 0;                        /*  记录当前已经处理的字符个数*/
    VOS_UINT8 *pucCurrPtr = pData;                  /*  指向当前正在处理的字符*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  拷贝内容的起始指针 */
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  设置初始状态 */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  设置初始状态 */

    /* 依次分析字符串中的每个字符*/
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaNumRangeIndex < AT_MAX_PARA_NUMBER) && (g_stATParseCmd.ucParaStrRangeIndex < AT_MAX_PARA_NUMBER))        /* 依次比较每个字符 */
    {
        curr_state = new_state;                 /*  当前状态设置为新状态*/

        /* 根据当前处理的字符和当前状态查表得到新状态 */
        new_state = atFindNextMainState(AT_MAIN_PARA_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                       /* 状态处理*/
        {
        case AT_PARA_NUM_STATE:                 /* 参数状态*/
        case AT_PARA_LETTER_STATE:              /* 字母状态*/
        case AT_PARA_LEFT_QUOT_STATE:           /* 参数左引号状态*/
        case AT_PARA_NUM_SUB_STATE:             /* 范围数字状态*/
        case AT_PARA_ZERO_STATE:                /* 数字0状态 */
        case AT_PARA_ZERO_SUB_STATE:            /* 范围数字0状态 */
        case AT_PARA_NO_QUOT_LETTER_STATE:      /* 无双引号包括字母状态 */
            if(curr_state != new_state)         /* 新状态部分不等于当前状态*/
            {
                pucCopyPtr = pucCurrPtr;            /*  准备接收参数*/
            }
            break;

        case AT_PARA_HEX_STATE:                 /* 十六进制状态 */
            /* continue */
        case AT_PARA_HEX_NUM_STATE:             /* 十六进制数字状态 */
            /* continue */
        case AT_PARA_HEX_SUB_STATE:             /* 匹配范围十六进制状态 */
            /* continue */
        case AT_PARA_HEX_NUM_SUB_STATE:         /* 匹配范围十六进制数字状态 */
            break;

        case AT_PARA_QUOT_COLON_STATE:          /* 引号逗号状态 */

            /* 拷贝到字符参数脚本列表 */
            /* 字符参数索引加1*/

            if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
            {
                atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex++],pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_FAILURE;                  /* 返回错误 */
            }
            break;

        case AT_PARA_NUM_SUB_COLON_STATE:

            /* 转成数字拷贝到数字参数脚本列表的上界 */
            /* 数字参数索引加1*/
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex++].ulBig = atRangeToU32(pucCopyPtr,pucCurrPtr);

            break;

        case AT_PARA_NUM_COLON_STATE:

            /* 转成数字拷贝到数字参数脚本列表的下界 */
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall = atRangeToU32(pucCopyPtr,pucCurrPtr);

            /* 上界等于下界*/
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulBig = g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall;

            /* 数字参数索引加1*/
            g_stATParseCmd.ucParaNumRangeIndex++;

            break;

        case AT_PARA_SUB_STATE:

            /* 转成数字拷贝到数字参数脚本列表的下界 */
            g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall = atRangeToU32(pucCopyPtr,pucCurrPtr);

            break;

        case AT_PARA_RIGHT_BRACKET_STATE:             /* 参数匹配右括号状态 */
            switch (curr_state)
            {
            case AT_PARA_NUM_SUB_STATE:          /* 参数匹配范围数字状态 */
                /* continue */
            case AT_PARA_ZERO_SUB_STATE:
                /* continue */
            case AT_PARA_HEX_NUM_SUB_STATE:

                /* 转成数字拷贝到数字参数脚本列表的上界 */
                /* 数字参数索引加1*/
                g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex++].ulBig = atRangeToU32(pucCopyPtr,pucCurrPtr);

                pgAtCheckFunc = atCheckNumPara;    /* 设置参数比较函数 */

                break;

            case AT_PARA_NUM_STATE:
                /* continue */
            case AT_PARA_ZERO_STATE:
                /* continue */
            case AT_PARA_HEX_NUM_STATE:

                /* 转成数字拷贝到数字参数脚本列表的下界 */
                g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall = atRangeToU32(pucCopyPtr,pucCurrPtr);

                /* 上界等于下界*/
                g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulBig = g_stATParseCmd.astParaNumRange[g_stATParseCmd.ucParaNumRangeIndex].ulSmall;

                /* 数字参数索引加1*/
                g_stATParseCmd.ucParaNumRangeIndex++;

                pgAtCheckFunc = atCheckNumPara;    /* 设置参数比较函数 */

                break;

            case AT_PARA_LETTER_STATE:

                /* 拷贝到字符参数脚本列表 */
                if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
                {
                    atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex],pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /* 返回错误 */
                }

                /* 设置参数比较函数 */
                pgAtCheckFunc = At_CheckStringPara;

                break;

            case AT_PARA_NO_QUOT_LETTER_STATE:      /* 无双引号包括字母状态 */

                /* 拷贝到字符参数脚本列表 */
                if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
                {
                    atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex],pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /* 返回错误 */
                }

                /* 设置参数比较函数 */
                pgAtCheckFunc = atCheckNoQuotStringPara;

                break;

            default:    /* AT_PARA_RIGHT_QUOT_STATE */

                /* 拷贝到字符参数脚本列表 */
                if ((VOS_UINT32)(pucCurrPtr - pucCopyPtr) < sizeof(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex]))
                {
                    atRangeCopy(g_stATParseCmd.auStrRange[g_stATParseCmd.ucParaStrRangeIndex++],pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /* 返回错误 */
                }

                /* 设置参数比较函数 */
                pgAtCheckFunc = atCheckCharPara;

                break;
            }

            if(AT_FAILURE == atCmparePara())       /* 参数比较 */
            {
                return AT_FAILURE;                   /* 返回错误 */
            }
            break;

        case AT_BUTT_STATE:                     /* 无效状态 */
            return AT_FAILURE;                  /* 返回错误 */

        default:
            break;
        }
        pucCurrPtr++;                               /*  继续分析下一个字符*/
    }

    if(AT_NONE_STATE == new_state)                  /* 初始状态 */
    {
        return AT_FAILURE;                          /* 返回错误 */
    }

    return AT_SUCCESS;                          /*  返回正确*/
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


