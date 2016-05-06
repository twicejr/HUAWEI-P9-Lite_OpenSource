

/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ScCommCtx.c
  版 本 号   : 初稿
  作    者   : d00212987
  生成日期   : 2015年08月10日
  最近修改   :
  功能描述   : SC CONTEXT文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月10日
    作    者   : d00212987
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ScCommCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_SC_CONTEXT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
 全局变量名    : g_stScCtx
 全局变量说明  : SC运行上下文
 1.日    期   : 2012年04月19日
   作    者   : w00184875
   修改内容   : 新建
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
static SC_CONTEXT_STRU                  g_stScCtx = {
    /* SC_COMM_GLOBAL_VAR */
    {
        {
            ".\\yaffs0\\SC\\Pers\\CKFile.bin",
            ".\\yaffs0\\SC\\Pers\\DKFile.bin",
            ".\\yaffs0\\SC\\Pers\\AKFile.bin",
            ".\\yaffs0\\SC\\Pers\\PIFile.bin",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I0.bin",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I1.bin"
        },
        {
            ".\\yaffs0\\SC\\Pers\\CKSign.hash",
            ".\\yaffs0\\SC\\Pers\\DKSign.hash",
            ".\\yaffs0\\SC\\Pers\\AKSign.hash",
            ".\\yaffs0\\SC\\Pers\\PISign.hash",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I0.hash",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I1.hash"
        }
    },
    /* SC_FAC_GLOBAL_VAR */
    {
        SC_AUTH_STATUS_UNDO,
        "",
        VOS_FALSE,
        ""
    },
    /* SC_APSEC_GLOBAL_VAR */
    {
        0,
        {0, 0},
        0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        SC_SECURITY_FILE_STATE_IDEL,
        {
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR}
        },
        ".\\SecureDataA.bin",
        ".\\SecureDataC.bin"
    }
};
#else
static SC_CONTEXT_STRU                  g_stScCtx = {
    /* SC_COMM_GLOBAL_VAR */
    {
        {
            "/mnvm2:0/SC/Pers/CKFile.bin",
            "/mnvm2:0/SC/Pers/DKFile.bin",
            "/mnvm2:0/SC/Pers/AKFile.bin",
            "/mnvm2:0/SC/Pers/PIFile.bin",
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I2.bin",
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.bin",
#endif
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
#endif
        },
        {
            "/mnvm2:0/SC/Pers/CKSign.hash",
            "/mnvm2:0/SC/Pers/DKSign.hash",
            "/mnvm2:0/SC/Pers/AKSign.hash",
            "/mnvm2:0/SC/Pers/PISign.hash",
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I2.hash",
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.hash",
#endif
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
#endif
        }
    },
    /* SC_FAC_GLOBAL_VAR */
    {
        SC_AUTH_STATUS_UNDO,
        "",
        VOS_FALSE,
        ""
    },
    /* SC_APSEC_GLOBAL_VAR */
    {
        0,
        {0, 0},
        0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        SC_SECURITY_FILE_STATE_IDEL,
        {
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR}
        },
        "/mnvm2:0/SC/Apsec/SecureDataA.bin",
        "/mnvm2:0/SC/Apsec/SecureDataC.bin"
    }
};

#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : SC_CTX_GetScCtxAddr
 功能描述  : 获取当前SC的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前SC的CTX地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月20日
   作    者   : w00184875
   修改内容   : 新生成函数

*****************************************************************************/
SC_CONTEXT_STRU* SC_CTX_GetScCtxAddr(VOS_VOID)
{
    return &(g_stScCtx);
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetCommGlobalVarAddr
 功能描述  : 获取SC公共操作的全局变量地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC公共操作的全局变量上下文指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
SC_COMM_GLOBAL_STRU*  SC_CTX_GetCommGlobalVarAddr( VOS_VOID )
{
    return &g_stScCtx.stScCommGlobalVar;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

