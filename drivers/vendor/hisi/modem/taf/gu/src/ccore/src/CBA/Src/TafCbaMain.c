

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaMain.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaProcAt.h"
#include  "TafCbaProcMmc.h"
#include  "TafCbaProcMma.h"
#include  "TafCbaProcUsim.h"
#include  "MnComm.h"
#include  "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_MAIN_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/




VOS_VOID TAF_CBA_MsgProc(
    struct MsgCB                       *pstMsg
)
{
    switch (pstMsg->ulSenderPid)
    {
        case UEPS_PID_GAS:
            TAF_CBA_ProcGasMsg(pstMsg);
            break;

        case WUEPS_PID_WRR:
            TAF_CBA_ProcWrrMsg(pstMsg);
            break;

        case WUEPS_PID_BMC:
            TAF_CBA_ProcBmcMsg(pstMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_ERRC:
            TAF_CBA_ProcLrrcMsg(pstMsg);
            break;
#endif

        case WUEPS_PID_MMC:
            TAF_CBA_ProcMmcMsg(pstMsg);
            break;

        case WUEPS_PID_AT:
            TAF_CBA_ProcAtMsg(pstMsg);
            break;

        case WUEPS_PID_MMA:
            TAF_CBA_ProcMmaMsg(pstMsg);
            break;


        default:
            TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_CBA_MsgProc: Unknown message sender, SenderPid, ", (VOS_INT32)pstMsg->ulSenderPid);
            break;

    }
}


#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
