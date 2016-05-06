/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasETcRabmMsgProc.c
    Description : 处理RABM发给TC的消息
    History     :
     1.李洪 00150010       2009-10-15  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasETcERabmMsgProc.h"
#include    "TcRabmInterface.h"
#include    "NasETcMain.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCRABMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCRABMMSGPROC_C
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
/*****************************************************************************
 Function Name   : NAS_ETC_RabmMsgDistr
 Description     : RABM消息处理函数
 Input           : pRcvMsg-----------收到的消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ETC_RabmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pRabmMsg  = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ETC_INFO_LOG("NAS_ETC_RabmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_RabmMsgDistr_ENUM, LNAS_ENTRY);

    pRabmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch (pRabmMsg->ulMsgName)
    {
        /*如果收到的是ID_ETC_ERABM_REL_IND消息*/
        case ID_ETC_ERABM_REL_IND:
            break;

        /*如果收到的是ID_ETC_ERABM_SUSPEND_IND消息*/
        case ID_ETC_ERABM_SUSPEND_IND:
            NAS_ETC_RcvTcRabmSuspendInd( (ETC_ERABM_SUSPEND_IND_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_ETC_ERABM_RESUME_IND消息*/
        case ID_ETC_ERABM_RESUME_IND:
            NAS_ETC_RcvTcRabmResumeInd( (ETC_ERABM_RESUME_IND_STRU *) pRcvMsg );
            break;

        default:
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmActTestModeMsg
 Description     : 向RABM发送ACTIVATE TEST MODE消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcRabmActTestModeMsg( VOS_VOID )
{
    ETC_ERABM_ACTIVATE_TEST_MODE_STRU     *pstTcRabmActTestMode = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstTcRabmActTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_ACTIVATE_TEST_MODE_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcRabmActTestMode)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmActTestModeMsg:ERROR:TC->RABM,Memory Alloc FAIL!");
        return ;
    }

    /* 清空 */
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_MSG_ENTITY(pstTcRabmActTestMode),
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmActTestMode), 
                       0,
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmActTestMode));

    /* 填写消息头 */
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmActTestMode,ID_ETC_ERABM_ACTIVATE_TEST_MODE);

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcRabmActTestMode);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcRabmActTestModeMsg:NORM:Send ID_ETC_ERABM_ACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcRabmActTestModeMsg_ENUM, LNAS_FUNCTION_LABEL1);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmDeactTestModeMsg
 Description     : 向RABM发送DEACTIVATE TEST MODE消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcRabmDeactTestModeMsg( VOS_VOID )
{
    ETC_ERABM_DEACTIVATE_TEST_MODE_STRU     *pstTcRabmDeactTestMode = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstTcRabmDeactTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_DEACTIVATE_TEST_MODE_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcRabmDeactTestMode)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmDeactTestModeMsg:ERROR:TC->RABM,Memory Alloc FAIL!");
        return ;
    }

    /* 清空 */
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_MSG_ENTITY(pstTcRabmDeactTestMode), 
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmDeactTestMode),
                       0,
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmDeactTestMode));

    /* 填写消息头 */
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmDeactTestMode,ID_ETC_ERABM_DEACTIVATE_TEST_MODE);

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcRabmDeactTestMode);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcRabmDeactTestModeMsg:NORM:Send ID_ETC_ERABM_ACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcRabmDeactTestModeMsg_ENUM, LNAS_FUNCTION_LABEL1);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmSuspendRsp
 Description     : ETC模块回复ID_ETC_ERABM_SUSPEND_RSP消息
 Input           : ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-04  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ETC_SndTcRabmSuspendRsp
(
    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    ETC_ERABM_SUSPEND_RSP_STRU           *pstTcRabmSuspendRsp  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstTcRabmSuspendRsp = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_SUSPEND_RSP_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstTcRabmSuspendRsp)
    {
        /*打印异常信息*/
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmSuspendRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_MSG_ENTITY(pstTcRabmSuspendRsp),
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmSuspendRsp),
                       0, 
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmSuspendRsp));

    /*填写消息头*/
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmSuspendRsp, ID_ETC_ERABM_SUSPEND_RSP);

    /*填写响应结果*/
    pstTcRabmSuspendRsp->enRslt= enRslt;

    /*调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcRabmSuspendRsp);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmResumeRsp
 Description     : ESM模块回复ID_ETC_ERABM_RESUME_RSP消息
 Input           : ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-04  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ETC_SndTcRabmResumeRsp
(
    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    ETC_ERABM_RESUME_RSP_STRU            *pstTcRabmResumeRsp  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstTcRabmResumeRsp = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_RESUME_RSP_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstTcRabmResumeRsp)
    {
        /*打印异常信息*/
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmResumeRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_MSG_ENTITY(pstTcRabmResumeRsp), 
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmResumeRsp),
                       0, 
                       NAS_ETC_GET_MSG_LENGTH(pstTcRabmResumeRsp));

    /*填写消息头*/
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmResumeRsp, ID_ETC_ERABM_RESUME_RSP);

    /*填写响应结果*/
    pstTcRabmResumeRsp->enRslt= enRslt;

    /*调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcRabmResumeRsp);
}


/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcRabmSuspendInd
 Description     : ETC模块收到ID_ETC_ERABM_SUSPEND_IND处理函数
 Input           : ETC_ERABM_SUSPEND_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-04      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcRabmSuspendInd(const ETC_ERABM_SUSPEND_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* 设置状态为挂起态 */
    NAS_ETC_SetLModeStatus(NAS_ETC_L_MODE_STATUS_SUSPENDED);

    /* 回复ERABM挂起成功 */
    NAS_ETC_SndTcRabmSuspendRsp(ETC_ERABM_RSLT_TYPE_SUCC);
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcRabmResumeInd
 Description     : SM模块收到ID_EMM_ERABM_RESUME_IND处理函数
 Input           : ETC_ERABM_RESUME_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-04      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcRabmResumeInd(const ETC_ERABM_RESUME_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* 设置状态为正常态 */
    NAS_ETC_SetLModeStatus(NAS_ETC_L_MODE_STATUS_NORMAL);

    /* 回复ERABM解挂成功 */
    NAS_ETC_SndTcRabmResumeRsp(ETC_ERABM_RSLT_TYPE_SUCC);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasETcRabmMsgProc.c */
