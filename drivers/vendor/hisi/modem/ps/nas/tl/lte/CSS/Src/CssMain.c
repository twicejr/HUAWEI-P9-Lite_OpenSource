/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssMain.c
  Description     : 该C文件给出了CSS模块初始化和消息处理入口的实现
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssMain.h"
#include    "CssCloudStrategyPublic.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSMAIN_C

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
CSS_CONTROL_STRU                        g_stCssControl;
CSS_CONTROL_STRU                       *pgstCssControl = &g_stCssControl;
CSS_CLOUD_PUB_CONTROL_STRU              g_stCloudContrl;

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : CSS_Init
 Description    : CSS模块上电初始化函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_Init(VOS_VOID)
{
    /* 云特性全局变量初始化 */
    CSS_MEM_SET_S(&g_stCloudContrl, sizeof(CSS_CLOUD_PUB_CONTROL_STRU), 0, sizeof(CSS_CLOUD_PUB_CONTROL_STRU));

    /* 读取云通信使能NV */
    if (CSS_SUCC != CSS_ReadNvCloudStrategy())
    {
        /* 如果NV读取失败，则认为云通信特性不打开 */
        g_stCloudContrl.ucCloudEnable    = VOS_FALSE;
        g_stCloudContrl.ucPrefFreqEnable = VOS_FALSE;
    }
    #if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
    /* 初始化内存池 */
    CSS_MEM_SET_S(g_acCssCloudFreqMemory, CSS_CLOUD_MEM_TOTAL_LEN, 0, CSS_CLOUD_MEM_TOTAL_LEN);
    #endif

    if (VOS_TRUE == g_stCloudContrl.ucCloudEnable)
    {
        /* 读取NV中预置频点 */
        CSS_ReadNvCloudPrefArfcn();
    }

    /* 定时器初始化 */
    CSS_CloudContrlTimerInit();

    /* 初始化云端版本号 */
    CSS_InitMccVersion();


}

/*****************************************************************************
 Function Name  : CSS_MsgHandle()
 Description    : CSS函数处理函数，,根据接收到的消息的所属模块，将消息分发给处理该模块消息的子模块。
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsgHandle(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;
    #if (VOS_WIN32 != VOS_OS_VER)
    TLPS_ExcLog_SaveMsgList((VOS_VOID *)pHeader);
    #endif

    TLPS_PRINT2LAYER_INFO1(CSS_MsgHandle_ENUM, LNAS_ENTRY, pHeader->ulMsgName);

    CSS_PrintCssRevMsg(pHeader,CSS_GET_CSS_PRINT_BUF());

    switch(pHeader->ulSenderPid)
    {
        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case WUEPS_PID_MMC:
        case PS_PID_ERRC:
        case I1_UEPS_PID_GAS:
        case I1_WUEPS_PID_MMC:
        case WUEPS_PID_WCOM:
        case PS_PID_ERMM:
        case TPS_PID_RRC:
            CSS_ProcCommMsg(pRcvMsg);
            break;

        case PS_PID_MM:
            CSS_ProcLmmMsg(pRcvMsg);
            break;

        case PS_PID_HPA:
            CSS_ProcLphyMsg(pRcvMsg);
            break;

        case VOS_PID_TIMER:
            CSS_ProcTimerMsg((REL_TIMER_MSG *)pRcvMsg);
            break;
        case WUEPS_PID_AT:
            CSS_ProcAtMsg(pRcvMsg);
            break;
        default:
            break;

    }
}

/*****************************************************************************
 Function Name  : CSS_TaskEntry()
 Description    : CSS模块TASK入口处理
 Input          : struct MsgCB* pMsg-----------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1. wangchen 00209181  2015-05-14  Draft Enact

 *****************************************************************************/
VOS_VOID CSS_TaskEntry(MsgBlock * pMsg)/*lint -e818 -e830*/
{
    /* 判断入口参数是否合法*/
    if( VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 消息处理 */
    CSS_MsgHandle((const VOS_VOID *)pMsg);
    /* CSS消息处理完推送打印 */
    TLPS_SendPrintBufferInfo();

}

/*****************************************************************************
 Function Name  : CSS_PidInit
 Discription    : CSS的PID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-05-14  Draft Enact

*****************************************************************************/
VOS_UINT32 CSS_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    CSS_Init();
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

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : CSS_FidInit
 Discription    : CSS的FID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-05-14  Draft Enact

*****************************************************************************/
VOS_UINT32 CSS_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet;

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

                ulRet = VOS_RegisterPIDInfo(PS_PID_CSS,
                                            CSS_PidInit,
                                            CSS_TaskEntry);

                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }


                ulRet = VOS_RegisterMsgTaskPrio(UEPS_FID_CSS, VOS_PRIORITY_M1);
                if( PS_SUCC != ulRet )
                {
                    return ulRet;
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
    }

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif



