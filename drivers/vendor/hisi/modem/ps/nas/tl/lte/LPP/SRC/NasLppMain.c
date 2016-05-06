/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppMain.c
  Description     : 该C文件给出了LPP_MAIN模块的实现
  History           :
  lifuxin 00253982 2015-7-7 新开发
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasLppPublic.h"
#include    "LPsOm.h"
#include    "TlPsDrv.h"
#include    "NasLppLrrcMsgProc.h"
#include    "NasLppMtaMsgProc.h"
#include    "NasLppTimerMsgProc.h"
#include    "NasLppEmmMsgProc.h"
#include    "NasLppMain.h"
#include    "EtcLppInterface.h"
#include    "NasLppLcsMsgProc.h"
#include    "NasLppEtcMsgProc.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLPPMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPMAIN_C

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
/*****************************************************************************
 Function Name  : NAS_LPP_TaskEntry
 Description    : LPP模块TASK入口处理,根据接收到的消息的所属模块，将消息分发给处理该模块消息的子模块。
 Input          : struct MsgCB* pMsg-----------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lifuxin 00253982 2015-7-7 Draft Enact
 *****************************************************************************/
VOS_VOID  NAS_LPP_TaskEntry(MsgBlock * pMsg)
{
    /* 定义消息头指针*/
#if (FEATURE_LPP == FEATURE_ON)
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_TaskEntry is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_TaskEntry_ENUM, LNAS_LPP_TaskEntryEnter);

    /* 判断入口参数是否合法*/
    if( VOS_NULL_PTR == pMsg)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_TaskEntry:ERROR: No Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TaskEntry_ENUM, LNAS_LPP_TaskEntryNullMsg);
        return;
    }

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pMsg;

    /*打印收到的消息*/
    NAS_LPP_PrintLppRevMsg(pHeader,NAS_COMM_GET_LPP_PRINT_BUF());

    /*打印消息码流*/
    NAS_LPP_NORM_LOG("====================IN MSG CONTENT is : ============");
    NAS_COMM_PrintArray(             NAS_COMM_GET_LPP_PRINT_BUF(),
                                     (VOS_UINT8 *)pMsg,
                                     (pMsg->ulLength + NAS_LPP_MSG_HEADER_LENGTH));
    NAS_LPP_NORM_LOG("====================================================");

    switch(pHeader->ulSenderPid)
    {
        case PS_PID_MM:
            NAS_LPP_EmmMsgDistr(pMsg);
            break;

        case PS_PID_ERRC:
            NAS_LPP_LrrcMsgDistr(pMsg);
            break;

        case VOS_PID_TIMER:
            NAS_LPP_TimerMsgDistr(pMsg);
            break;

        case UEPS_PID_MTA:
            NAS_LPP_MtaMsgDistr(pMsg);
            break;

        case PS_PID_LPP:
            NAS_LPP_LppMsgDistr(pMsg);
            break;

        case PS_PID_TC:
            NAS_LPP_EtcMsgDistr(pMsg);
            break;

        case WUEPS_PID_LCS:
            NAS_LPP_LcsMsgDistr(pMsg);
            break;

        default:
            NAS_LPP_WARN_LOG("NAS_LPP_TaskEntry:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_TaskEntry_ENUM, LNAS_LPP_TaskEntryNoThisMsg);
            break;
    }
#endif
    return;
}
/*****************************************************************************
 Function Name  : NAS_LPP_PidInit
 Discription    : LPP的PID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.lifuxin 00253982 2015-7-7 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
#if (FEATURE_LPP == FEATURE_ON)

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    NAS_LPP_LppCtxInit();
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }
#endif
    return VOS_OK;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasLppMain.c */

