/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpm_dbg.c
  版 本 号   : 初稿
  作    者   : y00138047
  生成日期   : 2012年6月21日
  最近修改   :
  功能描述   : dhcpm调试文件
  函数列表   :
*
*       1.                DHCPM_DbgCmdReg
*       2.                DHCPM_DbgInit
*       3.                DHCPM_DebugCbgCntProc
*       4.                DHCPM_DebugClearCnt
*       5.                DHCPM_DebugOut
*       6.                DHCPM_DebugOut_Stub
*       7.                DHCPM_DebugPrintLevelSet
*       8.                DHCPM_InitDbgCounter
*       9.                DHCPM_LogRecordReg
*       10.                DHCPM_PrintExceptions
*

  修改历史   :
  1.日    期   : 2012年6月21日
    作    者   : y00138047
    修改内容   : 创建文件

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc_dbg.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpm_interface.h"
#include "dhcpm_comp.h"
#include "dhcpm_dbg.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPM_DBG_C
/*lint +e767*/

ULONG *g_pulDhcpMCountArray = NULL;
ULONG g_ulDhcpMDbgInitFlg = VOS_FALSE;

VOID DHCPM_DebugPrintLevelSet( ULONG ulArgc, CHAR *szArgv[] )
{
    ULONG ulPrintLevel = 0;

    if (1 != ulArgc)
    {
        (VOID)vos_printf( "\r\n Please input print level!" );
        return;
    }

    if (0 != VOS_StrToUint32(szArgv[0], &ulPrintLevel))
    {
        (VOID)vos_printf("\r\n Please input parameter(1~4) !");
        return;
    }

    PTM_SetPrintLevel(PTM_DBG_PRINT_MODULE_DHCPM, ulPrintLevel);

    return;
}

VOID DHCPM_PrintExceptions()
{
    ULONG i = 0;

    for ( i = 0 ; i < DHCPM_MAX_COUNTER_NUM ; i++ )
    {
        if ( 0 == g_pulDhcpMCountArray[i] )
        {
            continue;
        }

        (VOID)vos_printf("\r\n dhcpMCount[%u] = %u", i, g_pulDhcpMCountArray[i]);
    }

    return;
}

VOID DHCPM_DebugClearCnt( )
{
    PGP_MemZero(g_pulDhcpMCountArray, sizeof(ULONG) * DHCPM_MAX_COUNTER_NUM);
    (VOID)vos_printf("\r\n dhcpm dbgcnt has been cleared");
    return;
}


VOID DHCPM_DebugCbgCntProc( ULONG argc, CHAR *argv[] )
{
    LONG lReturn = 0;

    if ( 0 == argc )
    {
        return;
    }

    lReturn = VOS_MemCmp("clear", argv[0], 5);
    if ( 0 == lReturn )
    {
        DHCPM_DebugClearCnt();
        return;
    }

    lReturn = VOS_MemCmp("show", argv[0], 4);
    if ( 0 == lReturn )
    {
        DHCPM_PrintExceptions();
        return;
    }

    return;
}


struct Command_S g_stDhcpMCommand[ ] =
{
#ifdef __SPU_DEBUG_VER__
    {"print",    "set print level", NULL, DHCPM_DebugPrintLevelSet},
#endif
    {"dbgcnt", "show or clear the count", NULL, DHCPM_DebugCbgCntProc},
};

struct Command_Group_S g_stDhcpMCmdGroup =
{
    sizeof(g_stDhcpMCommand) / sizeof(struct Command_S),
    30,
    g_stDhcpMCommand
};


/*****************************************************************************
 函 数 名  : DHCPM_LogRecordReg
 功能描述  : 注册日志打印
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPM_LogRecordReg()
{
    /* 注册DHCPM模块error级别日志信息 */
    (VOID)PTM_DbgLogRecordReg(PTM_DBG_PRINT_MODULE_DHCPM, M_PTM_SYSTEM_NAME, M_PTM_MODULE_DHCPM, M_PTM_MODULE_DHCPM);
    return;
}

/*****************************************************************************
 函 数 名  : DHCPM_DbgCmdReg
 功能描述  : 注册调试命令
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPM_DbgCmdReg()
{
    ULONG ulRet = 0;

    /* 注册调试命令 */
    ulRet = CommandsRegister( ( LPCommand_Group_S ) &g_stDhcpMCmdGroup,
                               "dhcpm", "dhcpm debug commands" );
    if ( VOS_OK != ulRet )
    {
        DHCPM_DebugPrint(PTM_LOG_ERR,"CommandsRegister error ， ulRet = %d",ulRet);
    }
    return;
}

ULONG DHCPM_InitDbgCounter()
{
    ULONG ulMemLen = 0;

    ulMemLen = sizeof(ULONG) * DHCPM_MAX_COUNTER_NUM;
    g_pulDhcpMCountArray = PGP_MemAlloc(DHCPM_HANDLE, ulMemLen);
    if ( NULL == g_pulDhcpMCountArray )
    {
        return VOS_ERR;
    }
    VOS_MemSet(g_pulDhcpMCountArray, 0, ulMemLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCPM_DbgInit
 功能描述  : dhcpm 调试命令手段初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPM_DbgInit()
{
    ULONG ulReturn = 0;

    if ( VOS_TRUE == g_ulDhcpMDbgInitFlg )
    {
        return VOS_OK;
    }

    DHCPM_LogRecordReg();

    DHCPM_DbgCmdReg();

    ulReturn = DHCPM_InitDbgCounter();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    g_ulDhcpMDbgInitFlg = VOS_TRUE;

    return VOS_OK;
}

#ifdef __WIN32_PLATFORM__
VOID PTM_DebugOut_Stub(ULONG ulLevel, CHAR *pszFormat, ...)
{
}
#endif


