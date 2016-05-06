#ifdef __cplusplus
extern "C"
{
#endif

#include "v_IO.h"
#include "mdrv_om.h"
#include "msp_diag.h"
#include "ftm_mntn.h"

#define THIS_FILE_ID           MSP_FILE_ID_FTM_MNTN_C

extern VOS_MSG_HOOK_FUNC    vos_MsgHook;
extern VOS_PRINT_HOOK g_pfnPrintHook;

/*lint -save -e830 -e438*/
/*****************************************************************************
 函 数 名  : ftm_mntn_printf
 功能描述  : 将打印信息存到buffer，上传到hids并打印输出到屏幕
 输入参数  : fmt-要打印的信息
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_mntn_printf(const VOS_CHAR * fmt, ... )
{
    VOS_INT32  rc = 0;
    VOS_UINT32 ulReturn = VOS_OK;
    /*lint -save -e530*/
    va_list    argument;
    /*lint -restore +e530*/
    VOS_CHAR   output_info[VOS_MAX_PRINT_LEN + 4];
    /*lint -save -e586*/
    /*lint -save -e830*/
    va_start(argument, fmt);
    /*lint -restore +e830*/
    rc = VOS_nvsprintf( output_info, VOS_MAX_PRINT_LEN, fmt, argument);
    /* 上报 */
    (VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(0, 0, 2), MSP_SYS_FTM_PID, __FILE__, __LINE__, (VOS_CHAR *)fmt, argument);

    va_end(argument);
    /*lint -restore*/

    /* 打印 */
    output_info[VOS_MAX_PRINT_LEN - 1] = '\0';

    if( rc >= VOS_MAX_PRINT_LEN - 1 )
    {
        VOS_UINT32  ulTempLen;
        VOS_CHAR *  pcWarning = " [!!!Warning: Print too long!!!]\r\n";
        ulTempLen = VOS_StrLen( pcWarning );
        (VOS_VOID)VOS_StrNCpy( output_info + ( VOS_MAX_PRINT_LEN - ulTempLen - 1 ), pcWarning, ulTempLen );
        rc = VOS_MAX_PRINT_LEN - 1; /* [false alarm]: 屏蔽Fortify错误 */

        (VOS_VOID)VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG );
        ulReturn = VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG;
    }
    else if( rc < 0 )
    {
        VOS_CHAR *  pcWarning = "\r\n### vos printf error: unknown internal error. ###\r\n";
        (VOS_VOID)VOS_StrCpy( output_info, pcWarning );
        rc = (VOS_INT32)VOS_StrLen( pcWarning ); /* [false alarm]: 屏蔽Fortify错误 */

        (VOS_VOID)VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR );
        ulReturn = VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR;
    }

    if( g_pfnPrintHook != VOS_NULL_PTR )
    {
        ulReturn = (VOS_UINT32)(*g_pfnPrintHook)( output_info );
        if( ulReturn != (VOS_UINT32)VOS_ERROR )
        {
            return (VOS_INT32)VOS_OK;
        }
    }

#if ((VOS_VXWORKS == VOS_OS_VER)  || (VOS_NUCLEUS == VOS_OS_VER) )
    printf( "%s",output_info );
#endif

#if (VOS_WIN32 == VOS_OS_VER)
    zprint(output_info );
#endif

#if (VOS_LINUX == VOS_OS_VER)
    printk( "%s",output_info );
#endif

#if (VOS_RTOSCK == VOS_OS_VER)
    (VOS_VOID)SRE_Printf( "%s",output_info );
#endif

    return (VOS_INT32)ulReturn;
}
/*lint -restore +e830 +e438*/

/*****************************************************************************
 函 数 名  : ftm_mntn_datahook
 功能描述  : 数据上报hids
 输入参数  : ulSendPid-发送模块id，ulRecvPid-接收模块id，ulLength-数据长度，pucData-数据起始地址
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID ftm_mntn_datahook(VOS_UINT32 ulSendPid, VOS_UINT32 ulRecvPid,VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    MsgBlock                           *pstMsg;
    VOS_UINT32                          ulResult;

    if (VOS_NULL_PTR == vos_MsgHook)
    {
        (VOS_VOID)ftm_mntn_printf("[%s]:WARNING:vos_MsgHook is Null.\n",__FUNCTION__);
        return;
    }

    pstMsg = (MsgBlock*)VOS_AllocMsg(ulSendPid, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        (VOS_VOID)ftm_mntn_printf("[%s]:WARNING:alloc msg failed\n",__FUNCTION__);
        return;
    }

    pstMsg->ulReceiverPid   = ulRecvPid;
    pstMsg->ulLength        = ulLength;
    (VOS_VOID)VOS_MemCpy(pstMsg->aucValue, pucData, ulLength);

    ulResult = (vos_MsgHook)((VOS_VOID *)(pstMsg));
    if (VOS_OK != ulResult)
    {
        (VOS_VOID)ftm_mntn_printf("[%s]: vos_MsgHook is Failed\n",__FUNCTION__);
    }

    (VOS_VOID)VOS_FreeMsg(ulSendPid, pstMsg);
    return;
}

#ifdef __cplusplus
}
#endif

