/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasTcOmMsgProc.c
  Description     :
  History         :
     1.lihong       2010-04-15   Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasETcOmMsgProc.h"
#include "NasETcPublic.h"

#include "TlPsDrv.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCOMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCOMMSGPROC_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ETC_SndAirMsgReportInd
(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLength,
    NAS_ETC_AIR_MSG_DIR_ENUM_UINT8       enMsgDir,
    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId
)
{
#ifndef PS_ITT_PC_TEST
    DIAG_AIR_IND_STRU       stAirMsg;
    VOS_UINT8                  *pucTmpData = VOS_NULL_PTR;

    /*分配空口消息空间*/
    pucTmpData = (VOS_UINT8*)
                        NAS_ETC_MEM_ALLOC(ulLength);

    if(VOS_NULL_PTR== pucTmpData)
    {
        NAS_ETC_ERR_LOG("NAS_ETC_SndAirMsgReportInd: MEM_ALLOC ERR!");
        return;
    }

    NAS_ETC_MEM_CPY_S(pucTmpData,ulLength, pucData, ulLength);

    /*设置空口消息方向*/
    if(NAS_ETC_AIR_MSG_DIR_ENUM_UP == enMsgDir)
    {
        stAirMsg.ulModule = DIAG_AIR_MSG_LOG_ID(PS_PID_TC, OS_MSG_UL);
        stAirMsg.ulPid = PS_PID_TC;
        stAirMsg.ulDirection = DIAG_SIDE_NET;
    }
    else
    {
        stAirMsg.ulModule = DIAG_AIR_MSG_LOG_ID(PS_PID_TC, OS_MSG_DL);
        stAirMsg.ulPid = PS_PID_TC;
        stAirMsg.ulDirection = DIAG_SIDE_UE;
    }
    stAirMsg.ulMsgId = (VOS_UINT32)(enMsgId+ PS_MSG_ID_AIR_BASE);
    stAirMsg.ulLength = ulLength;
    stAirMsg.pData = (void*)pucTmpData;

    /*上报空口消息*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_AIRMSGREPORT(&stAirMsg))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_SndAirMsgReportInd: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndAirMsgReportInd_ENUM, LNAS_TC_SendMsgFail);
    }

    /*释放空口消息空间*/
    NAS_ETC_MEM_FREE(pucTmpData);
#endif

    NAS_ETC_NORM_LOG("TC->OMT: PS_OMT_AIR_MSG_REPORT_IND\r");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndAirMsgReportInd_ENUM, LNAS_FUNCTION_LABEL1);
}


VOS_VOID NAS_ETC_SndKeyEventReportInd(OM_PS_KEY_EVENT_ENUM_UINT8 enKeyEvent)
{
#if (VOS_WIN32 != VOS_OS_VER)
    DIAG_EVENT_IND_STRU stDiagEventInd;

#ifndef PS_ITT_PC_TEST
    NAS_ETC_MEM_SET_S(&stDiagEventInd, sizeof(DIAG_EVENT_IND_STRU), 0, sizeof(DIAG_EVENT_IND_STRU));

    stDiagEventInd.ulModule = LPS_OM_ID(UE_MODULE_TC_ID, DIAG_LOG_TYPE_INFO);
    stDiagEventInd.ulPid = UE_MODULE_TC_ID;
    stDiagEventInd.ulEventId = (VOS_UINT32)(enKeyEvent+OM_PS_KEY_EVENT_BASE_ID);

    /*lint -e778*/
    /*lint -e648*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_EVENTREPORT(&stDiagEventInd))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_SndKeyEventReportInd: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndKeyEventReportInd_ENUM, LNAS_TC_SendMsgFail);
    }
    /*lint +e648*/
    /*lint +e778*/
#endif

#endif

    NAS_ETC_NORM_LOG("TC->OMT: PS_OMT_KEY_EVT_REPORT_IND\r");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndKeyEventReportInd_ENUM, LNAS_FUNCTION_LABEL1);
}
/*lint +e961*/
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

