
#ifndef __ptp__ppi__h__
#define __ptp__ppi__h__

#ifdef __cplusplus
    extern "C" {
#endif

extern ULONG g_ulPtpPpiDebugSwitch;      /* PPI下发调试开关 */
extern PTP_PPI_COUNT_S g_stPtpPpiCount;  /* PPI下发统计 */

/******************************************************************************
*Func Name   : PTP_PPI_LogMsg
*Description : PTP PPI可谓可测记录接口,包括日志/统计/调试
*Input       : ulDebugFlag:设置PPI调试标记,1-打开,0-关闭
*Output      : 
*Return      : .
*******************************************************************************/
extern VOID PTP_PPI_LogMsg(ULONG ulRet,USHORT usPtpPortNumber, ULONG ulPtpPpiCmd, PTP_PPI_S *pstPtpPpiInfo);

#ifdef __cplusplus
}
#endif

#endif


