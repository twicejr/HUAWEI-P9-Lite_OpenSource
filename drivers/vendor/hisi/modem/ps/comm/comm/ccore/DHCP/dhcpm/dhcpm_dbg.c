
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



VOID DHCPM_LogRecordReg()
{
    /* 注册DHCPM模块error级别日志信息 */
    (VOID)PTM_DbgLogRecordReg(PTM_DBG_PRINT_MODULE_DHCPM, M_PTM_SYSTEM_NAME, M_PTM_MODULE_DHCPM, M_PTM_MODULE_DHCPM);
    return;
}


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


