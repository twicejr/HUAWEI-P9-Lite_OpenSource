

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CsdInit.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_CSD_INIT_C
/*lint -e767 */

#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CSD_InitDicc
 功能描述  : 初始化DICC通道参数，同时打开DICC通道
 输入参数  : vos_void
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CSD_InitDicc(VOS_VOID)
{
    VOS_UINT32                          ulDICCRslt;
    DICC_INIT_CHN_INFO_STRU             stSendInitInfo;
    DICC_INIT_CHN_INFO_STRU             stRcvInitInfo;

    /* 发送端参数设置 */
    stSendInitInfo.enUserRole      = DICC_CHAN_ROLE_SENDER;
    stSendInitInfo.u.stSndInitInfo.stSndChnInfo.usChnBlkNum
                                   = DICC_PER_QUEUE_MAX_NODE_NUM;
    stSendInitInfo.u.stSndInitInfo.stSndChnInfo.usChnBlkSize
                                   = DICC_INFO_BLOCK_MAX_LEN;

    /* 接收端参数设置 */
    stRcvInitInfo.enUserRole       = DICC_CHAN_ROLE_RECVER;

    /*中断响应函数*/
    stRcvInitInfo.u.stRcvInitInfo.pfuncRecvIsr
                                   = CSD_DL_ProcIsr;

    /*初始化DICC发送通道*/
    ulDICCRslt                     = DICC_SingleChnInit(ACPU_PID_CSD,
                                                        DICC_SERVICE_TYPE_CSD_DATA,
                                                        &stSendInitInfo,
                                                        DICC_CPU_ID_ACPU);
    if (DICC_OK != ulDICCRslt)
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD, "CSD_InitDicc::DICC Sender INIT FAIL",ulDICCRslt);

        return VOS_ERR;
    }

    /* 初始化DICC接收通道*/
    ulDICCRslt                     = DICC_SingleChnInit(ACPU_PID_CSD,
                                                        DICC_SERVICE_TYPE_CSD_DATA,
                                                        &stRcvInitInfo,
                                                        DICC_CPU_ID_ACPU);
    if (DICC_OK != ulDICCRslt)
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD, "CSD_InitDicc::DICC Sender INIT FAIL",ulDICCRslt);

        return VOS_ERR;
    }


    /*打开上行DICC发送通道*/
    ulDICCRslt                      = DICC_OpenChannel(ACPU_PID_CSD,
                                                       DICC_CHAN_ID_UL_CSD_DATA_CHAN,
                                                       DICC_CHAN_ROLE_SENDER,
                                                       DICC_CPU_ID_ACPU);
    if (DICC_OK != ulDICCRslt)
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD, "CSD_InitDicc::DICC SENDER OPEN FAIL",ulDICCRslt);

        return VOS_ERR;
    }

    /*打开下行DICC接收通道*/
    ulDICCRslt                      = DICC_OpenChannel(ACPU_PID_CSD,
                                                       DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                                       DICC_CHAN_ROLE_RECVER,
                                                       DICC_CPU_ID_ACPU);
    if (DICC_OK != ulDICCRslt)
    {
         CSD_ERROR_LOG1(ACPU_PID_CSD,"CSD_InitDicc :DICC RECVER OPEN FAIL",ulDICCRslt);

        return VOS_ERR;
    }


    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CSD_UL_PidInit
 功能描述  : CSD的初始化函数，包括上行下行公用部分
 输入参数  : enInitPhase:初始化阶段
 输出参数  : 无
 返 回 值  : VOS_OK:初始化成功
             VOS_ERR:初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月6日
   作    者   : w00199382
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CSD_UL_PidInit(enum VOS_INIT_PHASE_DEFINE ip)
{

    VOS_UINT32                          ulRslt;

    switch ( ip )
    {
        case   VOS_IP_LOAD_CONFIG:

            /*DICC通道初始化*/
            ulRslt = CSD_InitDicc();

            if (VOS_OK != ulRslt)
            {
                CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_UL_PidInit::CSD_InitDicc FAIL");

                return VOS_ERR;
            }

            /*全局变量初始化*/
            ulRslt = CSD_InitCtx();

            break;

        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CSD_FidInit
 功能描述  : CSD FID初始化
 输入参数  : enInitPhase:初始化阶段
 输出参数  : 无
 返 回 值  : VOS_OK:初始化成功
             VOS_ERR:初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月6日
   作    者   : w00199382
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CSD_FidInit (enum VOS_INIT_PHASE_DEFINE  enInitPhase)
{
    VOS_UINT32 ulReturnCode;

    switch ( enInitPhase )
    {
        case   VOS_IP_LOAD_CONFIG:

            /*初始化上行下行信号量*/
           ulReturnCode = CSD_InitSem();

            if (VOS_OK != ulReturnCode)
            {
                CSD_ERROR_LOG(ACPU_PID_CSD, "CSD_FidInit::CSD_InitSem FAIL");

                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(ACPU_PID_CSD,
                                              (Init_Fun_Type) CSD_UL_PidInit,
                                              (Msg_Fun_Type) CSD_UL_ProcMsg);
            if ( VOS_OK != ulReturnCode )
            {
                CSD_ERROR_LOG(ACPU_PID_CSD,
                              "CSD_FidInit::VOS_RegisterPIDInfo ACPU_PID_CSD FAIL");

                return VOS_ERR;
            }


            /* 上行自处理任务注册 */
            ulReturnCode  = VOS_RegisterSelfTask(ACPU_FID_CSD,
                                                 (VOS_TASK_ENTRY_TYPE)CSD_UL_ProcDataTask,
                                                 VOS_PRIORITY_P5,
                                                 CSD_UL_DATA_TASK_STACK_SIZE);
            if ( VOS_NULL_BYTE == ulReturnCode )
            {
                CSD_ERROR_LOG(ACPU_PID_CSD,
                              "CSD_FidInit, ERROR, Fail regist CSD_UL_ProcDataTask");

                return VOS_ERR;
            }

            /* 下行自处理任务注册 */
            ulReturnCode  = VOS_RegisterSelfTask(ACPU_FID_CSD,
                                                 (VOS_TASK_ENTRY_TYPE)CSD_DL_ProcDataTask,
                                                 VOS_PRIORITY_P5,
                                                 CSD_DL_DATA_TASK_STACK_SIZE);
            if ( VOS_NULL_BYTE == ulReturnCode )
            {
                CSD_ERROR_LOG(ACPU_PID_CSD,
                              "CSD_FidInit, ERROR, Fail regist CSD_DL_ProcDataTask");

                return VOS_ERR;
            }


            /* 任务优先级 */
            ulReturnCode = VOS_RegisterMsgTaskPrio(ACPU_FID_CSD, VOS_PRIORITY_P3);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            break;

        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;

    }

    return VOS_OK;
}
#else
/*****************************************************************************
 函 数 名  : CSD_FidInit
 功能描述  : CSD FID初始化
 输入参数  : enInitPhase:初始化阶段
 输出参数  : 无
 返 回 值  : VOS_OK:初始化成功
             VOS_ERR:初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月6日
   作    者   : w00199382
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CSD_FidInit (enum VOS_INIT_PHASE_DEFINE  enInitPhase)
{
    return VOS_OK;
}
#endif /*FEATURE_CSD*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


