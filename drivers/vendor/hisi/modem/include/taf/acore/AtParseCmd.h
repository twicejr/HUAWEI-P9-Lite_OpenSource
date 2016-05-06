

#ifndef _ATPARSECMD_H_
#define _ATPARSECMD_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
/*#include "ATCmdProc.h" */
#include "TafTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)
/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define AT_CHECK_BASE_HEX                       (16)
#define AT_CHECK_BASE_OCT                       (8)
#define AT_CHECK_BASE_DEC                       (10)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
typedef enum
{
    AT_NONE_STATE,                      /* 初始状态 */

    AT_B_CMD_NAME_STATE,            /* AT基本命令名状态 */
    AT_B_CMD_PARA_STATE,            /* AT基本命令参数状态 */

    AT_D_CMD_NAME_STATE,                /* AT D命令命令名状态 */
    AT_D_CMD_DIGIT_STATE,               /* AT D命令数字状态 */
    AT_D_CMD_CHAR_STATE,                /* AT D命令字母状态 */
    AT_D_CMD_RIGHT_ARROW_STATE,         /* AT D命令右箭头状态 */
    AT_D_CMD_DIALSTRING_STATE,          /* AT D命令拨号字符串状态 */
    AT_D_CMD_SEMICOLON_STATE,           /* AT D命令分号状态 */
    AT_D_CMD_CHAR_G_STATE,              /* AT D命令字符G状态 */
    AT_D_CMD_CHAR_I_STATE,              /* AT D命令字符I状态 */
    AT_D_CMD_LEFT_QUOT_STATE,           /* AT D命令左引号状态 */
    AT_D_CMD_RIGHT_QUOT_STATE,          /* AT D命令右引号状态 */

    AT_DM_CMD_NAME_STATE,
    AT_DM_CMD_STAR_STATE,              /* AT D命令第一个*状态 */
    AT_DM_CMD_WELL_STATE,               /* AT D命令字符#状态 */
    AT_DM_CMD_NUM_STATE,               /* AT D命令字符#状态 */

    AT_S_CMD_NAME_STATE,             /* AT S命令名状态 */
    AT_S_CMD_SET_STATE,              /* AT S命令设置状态 */
    AT_S_CMD_READ_STATE,             /* AT S命令查询状态 */
    AT_S_CMD_TEST_STATE,             /* AT S命令测试状态 */
    AT_S_CMD_PARA_STATE,             /* AT S命令参数状态 */

    AT_E_CMD_NAME_STATE,               /* AT扩展命令名状态 */
    AT_E_CMD_SET_STATE,                /* AT扩展命令等号状态 */
    AT_E_CMD_TEST_STATE,               /* AT扩展命令查询参数状态 */
    AT_E_CMD_READ_STATE,               /* AT扩展命令测试参数状态 */
    AT_E_CMD_PARA_STATE,               /* AT扩展命令参数状态 */
    AT_E_CMD_COLON_STATE,              /* AT扩展命令逗号状态 */
    AT_E_CMD_LEFT_QUOT_STATE,          /* AT扩展命令左引号状态 */
    AT_E_CMD_RIGHT_QUOT_STATE,         /* AT扩展命令右引号状态 */

    AT_PARA_LEFT_BRACKET_STATE,      /* 参数匹配左括号状态 */
    AT_PARA_NUM_STATE,               /* 参数匹配参数状态 */
    AT_PARA_LETTER_STATE,            /* 参数匹配字母状态 */
    AT_PARA_NUM_COLON_STATE,         /* 参数匹配数字逗号状态 */
    AT_PARA_NUM_SUB_STATE,           /* 参数匹配范围数字状态 */
    AT_PARA_NUM_SUB_COLON_STATE,     /* 参数匹配范围数字逗号状态 */
    AT_PARA_QUOT_COLON_STATE,        /* 参数匹配引号逗号状态 */
    AT_PARA_RIGHT_BRACKET_STATE,     /* 参数匹配右括号状态 */
    AT_PARA_SUB_STATE,               /* 参数匹配范围状态 */
    AT_PARA_LEFT_QUOT_STATE,         /* 参数匹配左引号状态 */
    AT_PARA_RIGHT_QUOT_STATE,        /* 参数匹配右引号状态 */
    AT_PARA_COLON_STATE,             /* 参数匹配逗号状态 */
    AT_PARA_ZERO_STATE,              /* 参数匹配数字0状态 */
    AT_PARA_ZERO_SUB_STATE,          /* 参数匹配范围数字0状态 */
    AT_PARA_HEX_STATE,               /* 参数匹配十六进制状态, 0x或0X */
    AT_PARA_HEX_SUB_STATE,           /* 参数匹配范围十六进制状态 */
    AT_PARA_HEX_NUM_STATE,           /* 参数匹十六进制数状态 */
    AT_PARA_HEX_NUM_SUB_STATE,       /* 参数匹配范围十六进制数字状态 */
    AT_PARA_NO_QUOT_LETTER_STATE,    /* 参数匹配无双引号包括字母状态 */

    AT_W_CMD_F_STATE,            /* AT基本命令&状态 */
    AT_W_CMD_NAME_STATE,            /* AT基本命令名W状态 */
    AT_W_CMD_PARA_STATE,            /* AT基本命令名W状态 */

    AT_BUTT_STATE                    /* 无效状态 */
}AT_STATE_TYPE_ENUM;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*模块名＋意义＋HEADER */

/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* 判断条件函数指针*/
typedef TAF_UINT32 (*pATChkCharFuncType)(TAF_UINT8);

/* 子状态表类型：如果判断条件函数成功，则进入返回对应的子状态*/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    pATChkCharFuncType  pFuncName;                      /*    判断条件函数,如果成功，返回next_state*/
    AT_STATE_TYPE_ENUM next_state;                    /*    下一个状态 */
}AT_SUB_STATE_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/* 当前状态表类型：如果新状态等于当前状态，则进入对应的子状态表*/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_STATE_TYPE_ENUM curr_state;                    /*当前状态*/
    AT_SUB_STATE_STRU  *pSubStateTab;             /*对应的子态表*/
}AT_MAIN_STATE_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*lint -esym(752,At_RangeCopy)*/
TAF_VOID At_RangeCopy(TAF_UINT8 *pucDst,TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd);

/*lint -esym(752,At_RangeToU32)*/
TAF_UINT32 At_RangeToU32(TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd);


/* 把字符串中的某一段拷贝到指定地 */
/*lint -esym(752,atRangeCopy)*/
VOS_VOID atRangeCopy(VOS_UINT8 *pucDst,VOS_UINT8 * pucBegain, VOS_UINT8 * pucEnd);

/* 把字符串中的某一段转成无符号整型值 */
/*lint -esym(752,atRangeToU32)*/
VOS_UINT32 atRangeToU32(VOS_UINT8 * pucBegain, VOS_UINT8 * pucEnd);

/*lint -esym(752,atFindNextSubState)*/
AT_STATE_TYPE_ENUM atFindNextSubState(AT_SUB_STATE_STRU *pSubStateTab,VOS_UINT8 ucInputChar);

/*lint -esym(752,atFindNextMainState)*/
AT_STATE_TYPE_ENUM atFindNextMainState(AT_MAIN_STATE_STRU *pMainStateTab,VOS_UINT8 ucInputChar,AT_STATE_TYPE_ENUM InputState);

/*lint -esym(752,atAuc2ul)*/
extern VOS_UINT32 atAuc2ul(VOS_UINT8 *nptr,VOS_UINT16 usLen,VOS_UINT32 *pRtn);

/*lint -esym(752,At_ul2Auc)*/
VOS_VOID At_ul2Auc(VOS_UINT32 ulValue,TAF_UINT16 usLen,VOS_UINT8 *pRtn);


#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MapsTemplate.h*/


