/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Tc.c
  Description  : TC部分的功能函数
  Function List:
      1. Tc_RcvActRbTest
      2. Tc_RcvCloseLoop
      3. Tc_RcvDeactRbTest
      4. Tc_RcvGmmDataInd
      5. Tc_RcvMmcRelInd
      6. Tc_RcvMmDataInd
      7. Tc_RcvOpenLoop
      8. Tc_RcvRabmRabInd
      9. Tc_RcvRabmTestCnf
     10. Tc_RcvRabmTestLoopCnf
     11. Tc_SendMsg
     12. Tc_SndCcTestReq
     13. Tc_SndDataReq
     14. Tc_SndGmmTestReq
     15. Tc_SndMmcTestReq
     16. Tc_SndMmTestReq
     17. Tc_SndRabmTestLoopReq
     18. Tc_SndRabmTestReq
     19. Tc_SndSmsTestReq
     20. Tc_SndSmTestReq
     21. Tc_SndSsTestReq
     22. Tc_TaskEntry
     23. Tc_TaskInit
     24. Tc_GetState
     25. Tc_GetMode
  History:
      1.  张志勇      2004.05.24   新规作成
      2.  L47619   2005.11.26   问题单: A32D00767
      3.  L47619   2005.11.26   问题单: A32D01107
      4.  L47619   2006.01.10   问题单: A32D01571
      5.  L47619   2006.01.12   问题单: A32D01547
      6.  L47619   2006.02.21   问题单: A32D02126
      7.  韩鲁峰   2006-04-12   for A32D02451
      8.  韩鲁峰   2006-04-25   for A32D01738
      9.  L47619   2006.08.24   问题单: A32D05570
      10. L47619   2006.09.08   问题单: A32D06342
      11. L47619   2006.04.12   问题单: A32D08523
*******************************************************************************/
#include "Tcinclude.h"
#include "psprimitive.h"
#include "pscfg.h"

#include "NasComm.h"
#include "NasMmlCtx.h"

#include "NasUtranCtrlInterface.h"
#include "NasWphyInterface.h"
#include "NasMmcSndMscc.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

TC_GLOBAL_CTRL_STRU               g_TcInfo;                                             /* TC全局控制信息                           */


/***********************************************************************
 *  MODULE   : Tc_SndMmTestReq
 *  FUNCTION : 向MM发送TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
 ************************************************************************/
VOS_VOID Tc_SndMmTestReq(VOS_UINT8 ucMode)
{
    TCMM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* 定义原语类型指针                         */

    pTestReq = (TCMM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCMM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    pTestReq->MsgHeader.ulMsgName        = TCMM_TEST_REQ;                               /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndMmTestReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndGmmTestReq
 *  FUNCTION : 向GMM发送TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
 ************************************************************************/
VOS_VOID Tc_SndGmmTestReq(VOS_UINT8 ucMode)
{
    TCGMM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                        /* 定义原语类型指针                         */

    pTestReq = (TCGMM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCGMM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;
    pTestReq->MsgHeader.ulMsgName        = TCGMM_TEST_REQ;                              /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndGmmTestReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndSmTestReq
 *  FUNCTION : 向SM发送TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      2.  韩鲁峰   2005-04-25   for A32D01738
 ************************************************************************/
VOS_VOID Tc_SndSmTestReq(VOS_UINT8 ucMode)
{
    TCSM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* 定义原语类型指针                         */

    pTestReq = (TCSM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCSM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_SM;
    pTestReq->MsgHeader.ulMsgName        = TCSM_TEST_REQ;                               /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndSmTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndSmsTestReq
 *  FUNCTION : 向SMS发送TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      2.  韩鲁峰   2005-04-25   for A32D01738
 ************************************************************************/
VOS_VOID Tc_SndSmsTestReq(VOS_UINT8 ucMode)
{
    TCSMS_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                        /* 定义原语类型指针                         */

    pTestReq = (TCSMS_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCSMS_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_SMS;
    pTestReq->MsgHeader.ulMsgName        = TCSMS_TEST_REQ;                              /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndSmsTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndSsTestReq
 *  FUNCTION : 向Ss发送TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
 ************************************************************************/
VOS_VOID Tc_SndSsTestReq(VOS_UINT8 ucMode)
{
    TCSS_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* 定义原语类型指针                         */

    pTestReq = (TCSS_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCSS_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_SS;
    pTestReq->MsgHeader.ulMsgName        = TCSS_TEST_REQ;                               /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndSsTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndCcTestReq
 *  FUNCTION : 向Cc发送TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
 ************************************************************************/
VOS_VOID Tc_SndCcTestReq(VOS_UINT8 ucMode)
{
    TCCC_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* 定义原语类型指针                         */

    pTestReq = (TCCC_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCCC_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_CC;
    pTestReq->MsgHeader.ulMsgName        = TCCC_TEST_REQ;                               /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndCcTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndRabmTestReq
 *  FUNCTION : 向RABM发送TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
 ************************************************************************/
VOS_VOID Tc_SndRabmTestReq(VOS_UINT8 ucMode)
{
    TCRABM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                       /* 定义原语类型指针                         */

    pTestReq = (TCRABM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCRABM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;
    pTestReq->MsgHeader.ulMsgName        = TCRABM_TEST_REQ;                             /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndRabmTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndRabmTestLoopReq
 *  FUNCTION : 向RABM发送LOOP TEST消息
 *  INPUT    : VOS_UINT8 ucMode      模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      2.日    期   : 2012年09月07日
        作    者   : l00171473
        修改内容   : 内存清零

      3.日    期   : 2012年9月18日
        作    者   : z40661
        修改内容   : DTS2012091600237,TC环回存在问题。
 ************************************************************************/
VOS_VOID Tc_SndRabmTestLoopReq(VOS_UINT8 ucMode)
{
    VOS_UINT8                       k;                                                      /* 定义循环变量                             */
    TCRABM_TEST_LOOP_REQ_STRU   *pTestReq= VOS_NULL_PTR;                                        /* 定义原语类型指针                         */

    pTestReq = (TCRABM_TEST_LOOP_REQ_STRU*)PS_ALLOC_MSG(
                WUEPS_PID_TC, sizeof(TCRABM_TEST_LOOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }



    PS_MEM_SET((VOS_INT8*)pTestReq + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(TCRABM_TEST_LOOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);



    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;
    pTestReq->MsgHeader.ulMsgName        = TCRABM_TEST_LOOP_REQ;                        /* 消息名称                                 */

    pTestReq->ulMode = ucMode;                                                          /* 设置模式                                 */
    if(TC_LOOP_CLOSE == ucMode)
    {                                                                                   /* 如果模式是闭环                           */
        pTestReq->ulRBNum = g_TcInfo.TcModeInfo.ucLbNum;                                /* 通知LB实体的个数                         */

        pTestReq->ucTestLoopMode = g_TcInfo.TcModeInfo.ucTcMode;

        for(k = 0;k < g_TcInfo.TcModeInfo.ucLbNum;k++)
        {                                                                               /* 对于每个LB实体个数                       */
            pTestReq->aLBIdList[k].ulRBID
                = g_TcInfo.TcModeInfo.aLBList[k].ucRBID;                                /* 保存LB的RB ID信息                        */
            pTestReq->aLBIdList[k].ulUpRlcSduSize
                = g_TcInfo.TcModeInfo.aLBList[k].usUpRlcSduSize;                        /* 保存LB的上行RLC SIZE信息                 */
        }
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndRabmTestLoopReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndDataReq
 *  FUNCTION : 向MM或GMM发送回复网侧的响应消息。
 *  INPUT    : VOS_UINT8  ucMsgType    消息类型
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.25   新规作成
 ************************************************************************/
VOS_VOID Tc_SndDataReq(VOS_UINT8 ucMsgType)
{
    TCMM_DATA_REQ_STRU          *pMmDataReq= VOS_NULL_PTR;                                      /* 定义原语类型指针                         */
    TCGMM_DATA_REQ_STRU         *pGmmDataReq= VOS_NULL_PTR;                                     /* 定义原语类型指针                         */

    if( TC_CN_DOMAIN_CS == g_TcInfo.ucCnDomain )
    {                                                                                   /* 判断消息发向CN的CS域                     */
        pMmDataReq = (TCMM_DATA_REQ_STRU*)PS_ALLOC_MSG(
                      WUEPS_PID_TC, sizeof(TCMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
        if( VOS_NULL_PTR == pMmDataReq )
        {                                                                               /* 内存申请失败                             */
            return;                                                                     /* 返回                                     */
        }

        pMmDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pMmDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
        pMmDataReq->MsgHeader.ulMsgName        = TCMM_DATA_REQ;                         /* 消息名称                                 */


        pMmDataReq->SendTcMsg.ulTcMsgSize = TC_CMPMSG_SIZE;                             /* 设置消息长度                             */
        pMmDataReq->SendTcMsg.aucTcMsg[0] = 0x0F;                                       /* 设置PD                                   */
        pMmDataReq->SendTcMsg.aucTcMsg[1] = ucMsgType;                                  /* 设置消息类型                             */

        g_TcInfo.ucMsgType = TC_MSG_INVALID;                                            /* 清除正在处理的消息                       */

        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pMmDataReq))
        {
            NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndGmmTestReq():WARNING:SEND MSG FIAL");
        }
    }
    else
    {                                                                                   /* 判断消息发向CN的PS域                     */
        pGmmDataReq = (TCGMM_DATA_REQ_STRU*)PS_ALLOC_MSG(
                       WUEPS_PID_TC, sizeof(TCGMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
        if( VOS_NULL_PTR == pGmmDataReq )
        {                                                                               /* 内存申请失败                             */
            return;                                                                     /* 返回                                     */
        }

        pGmmDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pGmmDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;
        pGmmDataReq->MsgHeader.ulMsgName        = TCGMM_DATA_REQ;                       /* 消息名称                                 */

        pGmmDataReq->SendTcMsg.ulTcMsgSize = TC_CMPMSG_SIZE;                            /* 设置消息长度                             */
        pGmmDataReq->SendTcMsg.aucTcMsg[0] = 0x0F;                                      /* 设置PD                                   */
        pGmmDataReq->SendTcMsg.aucTcMsg[1] = ucMsgType;                                 /* 设置消息类型                             */

        g_TcInfo.ucMsgType = TC_MSG_INVALID;                                            /* 清除正在处理的消息                       */

        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pGmmDataReq))
        {
            NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndGmmTestReq():WARNING:SEND MSG FIAL");
        }
    }
    return;
}


/***********************************************************************
 *  MODULE   : Tc_SndRrcfTestControlMsg
 *  FUNCTION : 向RRCF发送环回启停消息
 *  INPUT    : VOS_UINT32  ulMode    启动或停止标识
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619      2006.09.08   根据问题单新增:A32D06342
 ************************************************************************/
VOS_VOID Tc_SndRrcfTestControlMsg(VOS_UINT32 ulMode)
{
    TC_RRCF_TEST_CONTROL_MSG    *pTestControlMsg;
    VOS_UINT32                   ulLength;

    ulLength        = sizeof(TC_RRCF_TEST_CONTROL_MSG) - VOS_MSG_HEAD_LENGTH;
    pTestControlMsg = (TC_RRCF_TEST_CONTROL_MSG *)PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pTestControlMsg )
    {
        /*打印出错信息---申请消息包失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_ERROR, "Tc_SndRrcfTestControlMsg:ERROR:Allocates a message packet for TC_RRCF_TEST_CONTROL_MSG msg FAIL!");
        return;
    }

    /*填写消息头:*/
    pTestControlMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pTestControlMsg->ulSenderPid     = WUEPS_PID_TC;
    pTestControlMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestControlMsg->ulReceiverPid   = WUEPS_PID_WRR;
    pTestControlMsg->ulLength        = ulLength;

    /*填写消息体:*/
    pTestControlMsg->ulMsgName       = TC_RRCF_TEST_CONTROL;
    pTestControlMsg->ulMode          = ulMode;

    /*发送该消息:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pTestControlMsg ) )
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_WARNING, "Tc_SndRrcfTestControlMsg:WARNING:Send TC_RRCF_TEST_CONTROL_MSG Msg Fail!");
    }

    return;
}



/* Deleted by wx270776 for OM融合, 2015-7-16, begin */
//RFA模块被OM删除，此段代码不起作用，故删除
#if 0
/***********************************************************************
 *  MODULE   : Tc_SndRfaTestControlMsg
 *  FUNCTION : 向RFA发送环回启停消息
 *  INPUT    : VOS_UINT32  ulMsgName    启动或停止消息原语ID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619      2007.09.24   Create
 ************************************************************************/
VOS_VOID Tc_SndRfaTestControlMsg(VOS_UINT32 ulMsgName)
{
    TC_RFA_CONTROL_MSG          *pTestControlMsg;
    TC_RFA_ACT_REQ_MSG          *pTcRfaActReq;
    TC_RFA_DEACT_REQ_MSG        *pTcRfaDeactReq;
    VOS_UINT32                   ulLength;

    ulLength        = sizeof(TC_RFA_CONTROL_MSG) - VOS_MSG_HEAD_LENGTH;
    pTestControlMsg = (TC_RFA_CONTROL_MSG *)PS_ALLOC_MSG( WUEPS_PID_TC, ulLength );
    if ( VOS_NULL_PTR == pTestControlMsg )
    {
        /*打印出错信息---申请消息包失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_ERROR, "Tc_SndRfaTestControlMsg:ERROR:Allocates a message packet for TC_RFA_CONTROL_MSG msg FAIL!");
        return;
    }

    if ( ID_TC_RFA_ACT_REQ == ulMsgName )
    {
        pTcRfaActReq = (TC_RFA_ACT_REQ_MSG *)pTestControlMsg;

        /*填写消息头:*/
        pTcRfaActReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pTcRfaActReq->ulSenderPid     = WUEPS_PID_TC;
        pTcRfaActReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pTcRfaActReq->ulReceiverPid   = WUEPS_PID_RFA;
        pTcRfaActReq->ulLength        = ulLength;

        /*填写消息体:*/
        pTcRfaActReq->ulMsgName       = ulMsgName;
    }
    else
    {
        pTcRfaDeactReq = (TC_RFA_DEACT_REQ_MSG *)pTestControlMsg;

        /*填写消息头:*/
        pTcRfaDeactReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pTcRfaDeactReq->ulSenderPid     = WUEPS_PID_TC;
        pTcRfaDeactReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pTcRfaDeactReq->ulReceiverPid   = WUEPS_PID_RFA;
        pTcRfaDeactReq->ulLength        = ulLength;

        /*填写消息体:*/
        pTcRfaDeactReq->ulMsgName       = ulMsgName;
    }

    /*发送该消息:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TC, pTestControlMsg ) )
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_WARNING, "Tc_SndRfaTestControlMsg:WARNING:Send TC_RFA_CONTROL_MSG Msg Fail!");
    }

    return;
}
#endif
/* Deleted by wx270776 for OM融合, 2015-7-16, end */

/*****************************************************************************
函 数 名  : Tc_SndMtaResetStoredPosInfoInd
功能描述  : TC向MTA发送清除定位辅助数据指示消息
输入参数  : enUePosTech         UE Positioning Technology
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
VOS_VOID Tc_SndMtaResetStoredPosInfoInd(TC_UE_POS_TECH_ENUM_UINT8 enUePosTech)
{
    TCMTA_RESET_UE_POS_STORED_INFO_STRU         *pstResetInd;

    /* 申请消息内存 */
    pstResetInd = (TCMTA_RESET_UE_POS_STORED_INFO_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCMTA_RESET_UE_POS_STORED_INFO_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstResetInd )
    {
        return;
    }

    pstResetInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstResetInd->stMsgHeader.ulReceiverPid   = UEPS_PID_MTA;
    pstResetInd->stMsgHeader.ulMsgName       = TCMTA_RESET_UE_POS_STORED_INFO_IND;

    pstResetInd->enUePosTech                 = enUePosTech;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstResetInd))
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_WARNING, "Tc_SndMtaResetStoredPosInfoInd:WARNING:Send TCMTA_RESET_UE_POS_STORED_INFO_IND Msg Fail!");
    }

    return;
}


/***********************************************************************
 *  MODULE   : Tc_RcvRabmTestCnf
 *  FUNCTION : 收到RABM的响应，保存RAB信息，向网侧回响应消息。
 *  INPUT    : VOS_VOID     *pMsg           收到的RABM原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      2.   张志勇      2004.11.23   修改发送去激活cmp消息的时机，在发送DataReq以前
 ************************************************************************/
VOS_VOID Tc_RcvRabmTestCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                     k;                                                        /* 定义循环变量                             */
    TCRABM_TEST_CNF_STRU      *pRabmTestCnf;                                            /* 收到的消息                               */

    VOS_UINT16                    usRbCnt;
    pRabmTestCnf = (TCRABM_TEST_CNF_STRU *) pMsg;
    g_TcInfo.TcRabInfo.ulRabCnt = pRabmTestCnf->ulRabCnt;                               /* 保存目前的RAB个数                        */

    for(k = 0;k < (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt;k++)
    {                                                                                   /* 对于已经建立的RAB个数                    */
        g_TcInfo.TcRabInfo.aRabInfo[k].ulRabId      =
            pRabmTestCnf->aRabInfo[k].ulRabId;                                          /* 对每个RAB ID进行赋值                     */
        g_TcInfo.TcRabInfo.aRabInfo[k].ulCnDomainId =
            pRabmTestCnf->aRabInfo[k].ulCnDomainId;                                     /* 对每个RAB进所属的CN域行赋值              */
        /*g_TcInfo.TcRabInfo.aRabInfo[k].ulRbId       =     */
        /*    pRabmTestCnf->aRabInfo[k].ulRbId;             */                              /* 保存RAB中的RB ID                         */
        usRbCnt = (VOS_UINT16)g_TcInfo.TcRabInfo.aRabInfo[k].ulRbCnt;
        g_TcInfo.TcRabInfo.aRabInfo[k].aulRbId[usRbCnt] =
             pRabmTestCnf->aRabInfo[k].ulRbId;
        (g_TcInfo.TcRabInfo.aRabInfo[k].ulRbCnt)++;
    }
    if(TC_RRC_CONN_STATUS_PRESENT == g_TcInfo.ucRrcConnStatus)
    {                                                                                   /* 判断RRC连接是否存在                      */
        switch(g_TcInfo.ucTcState)
        {                                                                               /* 根据当前的状态进行分发                   */
        case TC_OPEN_TEST_LOOP:
        case TC_CLOSE_TEST_LOOP:
/* 2004.11.23 del end */
            /*Tc_SndDataReq(TC_DEACT_RB_TEST_MODE_CMP);*/                                   /* 发送去激活消息                           */
            g_TcInfo.ucTcState = TC_NORMAL_MODE;                                        /* 状态迁入NORMAL                           */
/* 2004.11.23 del end */
            break;
        case TC_NORMAL_MODE:
            Tc_SndDataReq(TC_ACT_RB_TEST_MODE_CMP);                                     /* 发送激活消息                             */
            g_TcInfo.ucTcState = TC_OPEN_TEST_LOOP;                                     /* 状态迁入OPEN                             */
            break;
        default:
            break;
        }
    }
    else
    {                                                                                   /* RRC连接不存在                            */
        g_TcInfo.ucTcState = TC_NORMAL_MODE;                                            /* 状态迁入NORMAL                           */
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_RcvRabmTestLoopCnf
 *  FUNCTION : 收到RABM的响应，向网侧回响应消息。
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      2.日    期   : 2013年3月30日
        作    者   : l00167671
        修改内容   : 主动上报AT命令控制下移至C核
 ************************************************************************/
VOS_VOID Tc_RcvRabmTestLoopCnf()
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8             enCurrUtranMode;

    switch(g_TcInfo.ucMsgType)
    {                                                                                   /* 根据当前的状态进行分发                   */
    case TC_CLOSE_UE_TEST_LOOP:
        Tc_SndDataReq(TC_CLOSE_UE_TEST_LOOP_CMP);                                       /* 发送闭环响应消息                         */
        g_TcInfo.ucTcState = TC_CLOSE_TEST_LOOP;                                        /* 状态迁入CLOSE                            */

        enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
        if ((VOS_FALSE == g_TcInfo.ucSndWphyCloseLoopNtfLable)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrUtranMode))
        {
            /* 根据DSP需求，在W下通知WPHY进入环回 */
            NAS_TC_SndWphyCloseLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_TRUE;
        }

        /* 闪灯: WCDMA PS环回建立 */
        if (TC_CN_DOMAIN_PS == g_TcInfo.ucCnDomain)
        {
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
        }
        break;
    case TC_OPEN_UE_TEST_LOOP:
        Tc_SndDataReq(TC_OPEN_UE_TEST_LOOP_CMP);                                        /* 发送开环响应消息                         */
        g_TcInfo.ucTcState = TC_OPEN_TEST_LOOP;                                         /* 状态迁入OPEN                             */

        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            /* 根据DSP需求，在W下通知WPHY退出环回 */
            NAS_TC_SndWphyOpenLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_FALSE;
        }

        /* 闪灯: WCDMA PS环回释放 */
        if (TC_CN_DOMAIN_PS == g_TcInfo.ucCnDomain)
        {
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
        }
        break;
    default:
        break;
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_RcvRabmRabInd
 *  FUNCTION : 收到RABM上报的RAB信息，存储并判断是否是正在使用的RAB。
 *  INPUT    : VOS_VOID     *pMsg           收到的RABM原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      1.   张志勇      2004.11.24   使用了结构体赋值语句,改为对结构体的成员直接赋值
 ************************************************************************/
VOS_VOID Tc_RcvRabmRabInd(VOS_VOID *pMsg)
{
    TCRABM_RAB_IND_STRU                 *pRabmInd;                                      /* 收到的消息                               */
    VOS_UINT8                               i,j;                                            /* 定义循环变量                             */
    VOS_UINT16     usRbCnt = 0,usRabCnt = 0,usRbLoop = 0;

    pRabmInd = (TCRABM_RAB_IND_STRU *) pMsg;                                            /* 结构体指针类型转换                       */
    if( TC_RAB_SETUP == pRabmInd->ulRabChangeType )
    {                                                                                   /* 判断RAB的修改模式                        */
        for( i = 0; i < (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt; i++ )
        {                                                                               /* 在当前已经存储的rab信息中进行搜索        */
            if((g_TcInfo.TcRabInfo.aRabInfo[i].ulRabId
                          == pRabmInd->RabInfo.ulRabId)&&
               (g_TcInfo.TcRabInfo.aRabInfo[i].ulCnDomainId
                          == pRabmInd->RabInfo.ulCnDomainId))
            {                                                                           /* 这个RAB ID已经存在了                     */
                break;                                                                  /* 不处理                                   */
            }
        }
        if( i == (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt )
        {                                                                               /* 如果没有找到相同的rab                    */
            g_TcInfo.TcRabInfo.aRabInfo[(VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt].ulRabId =
                pRabmInd->RabInfo.ulRabId;                                              /* 对每个RAB ID进行赋值                     */
            g_TcInfo.TcRabInfo.aRabInfo[(VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt].ulCnDomainId =
                pRabmInd->RabInfo.ulCnDomainId;                                         /* 对每个RAB进所属的CN域行赋值              */
            usRabCnt = (VOS_UINT16)g_TcInfo.TcRabInfo.ulRabCnt;
                g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].aulRbId[0] =
                    pRabmInd->RabInfo.ulRbId;
                g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].ulRbCnt = 1;
            g_TcInfo.TcRabInfo.ulRabCnt ++;                                             /* 更新目前的RAB个数                        */
        }
        else
        {
            usRabCnt = i;
            usRbCnt = (VOS_UINT16)g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].ulRbCnt;

            if (  (usRabCnt < (TC_RABM_MAX_RAB_SETUP))
                &&(usRbCnt < RRC_NAS_MAX_RB_PER_RAB))
            {
                g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].aulRbId[usRbCnt] =
                    pRabmInd->RabInfo.ulRbId;
                (g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].ulRbCnt)++;
            }
            else
            {
                PS_NAS_LOG2(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvRabmRabInd:WARNING:overflow ulRabCnt ,ulRbCnt :" ,usRabCnt, usRbCnt);
            }
        }
    }
    else
    {                                                                                   /* 释放RAB信息                              */
        for( i = 0; i < (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt; i++ )
        {                                                                               /* 更新rab存储信息                          */
            if((g_TcInfo.TcRabInfo.aRabInfo[i].ulRabId == pRabmInd->RabInfo.ulRabId)&&
              (g_TcInfo.TcRabInfo.aRabInfo[i].ulCnDomainId
                                  == pRabmInd->RabInfo.ulCnDomainId))
            {                                                                           /* 找到该RAB ID的位置                       */
                for( j = i ; j < ((VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt - 1) ; j++ )
                {                                                                       /* 删除该RAB                                */
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulCnDomainId =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulCnDomainId;
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulRabId      =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRabId;
                    #if 0
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulRbId       =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRbId;
                    #else
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulRbCnt =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRbCnt;
                    if (g_TcInfo.TcRabInfo.aRabInfo[j].ulRbCnt < RRC_NAS_MAX_RB_PER_RAB)
                    {
                        for(usRbLoop = 0;usRbLoop < g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRbCnt;usRbLoop++)
                        {
                            g_TcInfo.TcRabInfo.aRabInfo[j].aulRbId[usRbLoop] =
                                g_TcInfo.TcRabInfo.aRabInfo[j + 1].aulRbId[usRbLoop];
                        }
                    }
                    else
                    {
                        PS_NAS_LOG2(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvRabmRabInd:WARNING:overflow ulRabCnt ,ulRbCnt :" ,j + 1, (VOS_INT32)g_TcInfo.TcRabInfo.aRabInfo[j].ulRbCnt);
                    }
                    #endif
                }
                g_TcInfo.TcRabInfo.ulRabCnt --;                                         /* 更新目前的RAB个数                        */
                break;
            }
        }
        if(0 == g_TcInfo.TcRabInfo.ulRabCnt)
        {                                                                               /* 如果已经没有rb存在                       */
            switch(g_TcInfo.ucTcState)
            {                                                                           /* 根据当前的状态判断                       */
            case TC_OPEN_TEST_LOOP:
                if(TC_CLOSE_UE_TEST_LOOP == g_TcInfo.ucMsgType)
                {                                                                       /* 如果正在处理闭环消息                     */
                    g_TcInfo.ucMsgType = TC_MSG_INVALID;                                /* 清除正在处理的消息                       */
                    Tc_SndRabmTestLoopReq(TC_LOOP_OPEN);                                /* 通知RABM去开环处理                       */
                }
                break;
            case TC_CLOSE_TEST_LOOP:
                if(TC_OPEN_UE_TEST_LOOP != g_TcInfo.ucMsgType)
                {                                                                       /* 如果正在处理去激活消息不处理，否则，通知 *
                                                                                         * RABM开环处理                             */
                    Tc_SndRabmTestLoopReq(TC_LOOP_OPEN);                                /* 通知RABM去开环处理                       */
                }
                break;
            default:
                break;
            }
        }
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndRlcTcModeInfo
 *  FUNCTION : 向RLC发送TC模式信息
 *  INPUT    : VOS_UINT8    ucTcFlag    TC环回启停标志
               VOS_UINT8    ucTcMode    TC环回模式信息
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1. L47619      2007.03.22   MAPS3000

  2.日    期   : 2012年7月14日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseI: 确认当前UTRAN模式，进而确认当前的接收PID.
 ************************************************************************/
VOS_VOID  Tc_SndRlcTcModeInfo(VOS_UINT8 ucTcFlag, VOS_UINT8 ucTcMode)
{
    TC_RLC_TEST_IND_STRU    *pTcRlcTestInd;
    VOS_UINT32              ulLength;

    ulLength = sizeof(TC_RLC_TEST_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pTcRlcTestInd = (TC_RLC_TEST_IND_STRU *)PS_ALLOC_MSG( WUEPS_PID_TC, ulLength );
    if ( VOS_NULL_PTR == pTcRlcTestInd )
    {
        /*打印出错信息---申请消息包失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndRlcTcModeInfo:ERROR:Allocates a message packet for TC_RLC_TEST_IND_STRU msg FAIL!");
        return;
    }

    pTcRlcTestInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pTcRlcTestInd->ulSenderPid     = WUEPS_PID_TC;
    pTcRlcTestInd->ulReceiverCpuId = VOS_LOCAL_CPUID;

    pTcRlcTestInd->ulReceiverPid   = WUEPS_PID_RLC;

    pTcRlcTestInd->ulLength        = ulLength;
    pTcRlcTestInd->enMsgName       = ID_TC_RLC_TEST_IND;

    if ( TC_LOOP_CLOSE == ucTcFlag )
    {
        if ( TC_MODE_1 == ucTcMode )
        {
            pTcRlcTestInd->enTcMode = TEST_LOOP_MODE1;
        }
        else if ( TC_MODE_2 == ucTcMode )
        {
            pTcRlcTestInd->enTcMode = TEST_LOOP_MODE2;
        }
        else
        {
            pTcRlcTestInd->enTcMode = TEST_LOOP_BUTT;
        }
    }
    else
    {
        pTcRlcTestInd->enTcMode = TEST_LOOP_NULL;
    }

    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_TC, (struct MsgCB **)&pTcRlcTestInd) )
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndRlcTcModeInfo:ERROR:Snd TC_RLC_TEST_IND_STRU msg FAIL!");
    }

    return;
}


/***********************************************************************
 *  MODULE   : Tc_RcvCloseLoop
 *  FUNCTION : 判断是否启动回环测试，配置LB参数
 *  INPUT    : VOS_UINT8  * pRcvTcMsg    TC_CLOSE_UE_TEST_LOOP消息指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.张 志 勇     2004.05.24   新规作成
 2.L47619       2006.01.10   问题单:A32D01571
 3.日    期   : 2010年3月16日
   作    者   : z00163274
   修改内容   : 问题单AT2D17622修改
 4.日    期   : 2013年8月29日
   作    者   : w00242748
   修改内容   : KLOC告警清理
 5.日    期   : 2015年6月9日
   作    者   : wx270776
   修改内容   : TAS需求: 通知MTC环回状态
 ************************************************************************/
VOS_VOID Tc_RcvCloseLoop(VOS_UINT8 * pRcvTcMsg)
{
    VOS_UINT8       i,k;                                                                    /* 定义循环变量                             */
    VOS_UINT8       ucFindFlg = WUEPS_FALSE;                                                /* 定义状态变量                             */
    VOS_UINT16      usRlcsize = 0;                                                          /* 定义中间变量                             */
    VOS_UINT16      usRbLoop = 0;
    VOS_UINT8                           ucLbNum;
    VOS_UINT8                           ucRabCnt;
    VOS_UINT8                           ucRbCnt;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* 没有正在处理其它消息                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseLoop:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType ");
        return;
    }
    if( 0 == g_TcInfo.TcRabInfo.ulRabCnt )
    {                                                                                   /* 当前不存在可用的rab                      */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseLoop:WARNING:0 == g_TcInfo.TcRabInfo.ulRabCnt");
        return;
    }


    switch(g_TcInfo.ucTcState)
    {                                                                                   /* 根据当前的状态进行分发                   */
    case TC_OPEN_TEST_LOOP:
        g_TcInfo.ucMsgType = TC_CLOSE_UE_TEST_LOOP;                                     /* 记录正在处理的消息类型                   */
        g_TcInfo.TcModeInfo.ucTcMode = pRcvTcMsg[2];                                    /* 保存模式信息                             */

        /*TC向RLC发送TC启动及环回模式信息:*/
        Tc_SndRlcTcModeInfo(TC_LOOP_CLOSE, g_TcInfo.TcModeInfo.ucTcMode);

        g_TcInfo.TcModeInfo.ucLbNum = 0;                                                /* 初始化LB实体个数是0                      */
        if(TC_MODE_1 == g_TcInfo.TcModeInfo.ucTcMode)
        {                                                                               /* 判断模式是否是1                          */
            ucLbNum = NAS_COMM_MIN(pRcvTcMsg[3], TC_LB_MAX_RBNUM);
            for( i = 0 ; i < ucLbNum ; i++ )
            {                                                                           /* 在LB信息的长度内循环                     */
                if((( i + 1 ) % 3) == 0 )
                {                                                                       /* 每3个字节一个单位进行存储                */
                    g_TcInfo.TcModeInfo.aLBList[g_TcInfo.TcModeInfo.ucLbNum].ucRBID
                                                              = pRcvTcMsg[4+i]&(0x1F);  /* 保存RB ID                                */
                    usRlcsize = pRcvTcMsg[2+i];                                         /* 存储RLC SIZE的高8位数                    */
                    usRlcsize = ((usRlcsize << 8)&0xFF00) | pRcvTcMsg[3+i];             /* 高8位向左移位，存储低8位的数             */
                    g_TcInfo.TcModeInfo.aLBList[g_TcInfo.TcModeInfo.ucLbNum].
                        usUpRlcSduSize = usRlcsize;                                     /* 取得RLC SIZE的数值                       */
                    g_TcInfo.TcModeInfo.ucLbNum++;                                      /* LB实体的个数更新                         */
                }
            }
            for( i = 0; i < g_TcInfo.TcModeInfo.ucLbNum; i++ )
            {                                                                           /* 检查LB中的RB ID是否存在                  */
                ucFindFlg = WUEPS_FALSE;                                                /* 不存在或者CN域不一致                     */
                ucRabCnt = NAS_COMM_MIN(((VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt), TC_RABM_MAX_RAB_SETUP);
                for(k = 0; k < ucRabCnt; k++ )
                {                                                                       /* 在当前存在的RAB中查找                    */
                    ucRbCnt = NAS_COMM_MIN(((VOS_UINT8)g_TcInfo.TcRabInfo.aRabInfo[k].ulRbCnt), RRC_NAS_MAX_RB_PER_RAB);
                    for(usRbLoop = 0;usRbLoop < ucRbCnt;usRbLoop++)
                    {
                        if(g_TcInfo.TcModeInfo.aLBList[i].ucRBID ==
                                (VOS_UINT8)g_TcInfo.TcRabInfo.aRabInfo[k].aulRbId[usRbLoop])
                        {                                                                   /* LB实体里的RB ID是否在已经建立的RAB中，而 *
                                                                                             * 且RAB的CN域与g_TcInfo.ucCnDomain一致     */
                            ucFindFlg = WUEPS_TRUE;                                         /* 存在且一致                               */
                            break;
                        }
                    }
                }
                if(WUEPS_FALSE == ucFindFlg)
                {                                                                       /* LB实体中的RB不存在或者与当前测试的域不同 */
                    PS_NAS_LOG1(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING,
                            "Tc_RcvCloseLoop:WARNING: Can't find match RbId!", g_TcInfo.TcModeInfo.aLBList[i].ucRBID);
                }
            }
            Tc_SndRabmTestLoopReq(TC_LOOP_CLOSE);                                       /* 通知RABM闭环处理                         */
        }
        else
        {                                                                               /* 模式不是1                                */
            Tc_SndRabmTestLoopReq(TC_LOOP_CLOSE);
        }

        /* 通知MTC环回状态 */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_START);
        break;
    case TC_CLOSE_TEST_LOOP:
        Tc_SndDataReq(TC_CLOSE_UE_TEST_LOOP_CMP);                                       /* 发送开环响应消息                         */
        break;
    default:
        break;
    }
}

/***********************************************************************
 *  MODULE   : Tc_RcvOpenLoop
 *  FUNCTION : 判断是否启动回环测试，配置LB参数
 *  INPUT    : VOS_UINT8
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.张 志 勇     s2004.05.24   新规作成
 2.日    期   : 2015年6月9日
   作    者   : wx270776
   修改内容   : TAS需求: 通知MTC环回状态

 ************************************************************************/
VOS_VOID Tc_RcvOpenLoop()
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* 没有正在处理其它消息                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoop:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }
    if( 0 == g_TcInfo.TcRabInfo.ulRabCnt )
    {                                                                                   /* 当前不存在可用的rab                      */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoop:WARNING:0 == g_TcInfo.TcRabInfo.ulRabCnt");
        return;
    }
    PS_NAS_MEM_SET(&g_TcInfo.TcModeInfo,0,sizeof(TC_MODE_INFO_STRU));                      /* 初始化内存                               */
    switch(g_TcInfo.ucTcState)
    {                                                                                   /* 根据当前的状态进行分发                   */
    case TC_CLOSE_TEST_LOOP:
        g_TcInfo.ucMsgType = TC_OPEN_UE_TEST_LOOP;                                      /* 记录正在处理的消息类型                   */

        /*TC向RLC发送TC环回停止信息:*/
        Tc_SndRlcTcModeInfo(TC_LOOP_OPEN, 0);
        Tc_SndRabmTestLoopReq(TC_LOOP_OPEN);                                            /* 通知RABM去开环处理                       */

        /* 通知MTC环回状态 */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
        break;

    case TC_NORMAL_MODE:
    case TC_OPEN_TEST_LOOP:
        Tc_SndDataReq(TC_OPEN_UE_TEST_LOOP_CMP);                                        /* 发送激活响应消息                         */

        break;

    default:
        break;
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_RcvActRbTest
 *  FUNCTION : 通知nas其它task激活
 *  INPUT    : VOS_UINT8
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.25   新规作成
      2.   L47619      2006.08.24   问题单: A32D05570
      3.   L47619      2006.09.08   问题单: A32D06342
      4.日    期   : 2011年9月14日
        作    者   : l00171473
        修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送激活
      5.日    期   : 2015年6月9日
        作    者   : wx270776
        修改内容   : TAS需求: 通知MTC环回状态
 ************************************************************************/
VOS_VOID Tc_RcvActRbTest()
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* 没有正在处理其它消息                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvActRbTest:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }
    switch(g_TcInfo.ucTcState)
    {                                                                                   /* 根据当前的状态进行分发                   */
    case TC_NORMAL_MODE:
        g_TcInfo.ucMsgType = TC_ACT_RB_TEST_MODE;                                       /* 记录正在处理的消息类型                   */

        /* Deleted by wx270776 for OM融合, 2015-7-16, begin */
        //Tc_SndRfaTestControlMsg(ID_TC_RFA_ACT_REQ);
        /* Deleted by wx270776 for OM融合, 2015-7-16, end */

        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            /* 根据DSP需求，在W下通知WPHY进入环回 */
            NAS_TC_SndWphyCloseLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_TRUE;
        }

        Tc_SndRabmTestReq(TC_RB_TEST_ACTIVE);                                           /* 通知RABM激活                             */
        Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                                             /* 通知MM激活                               */
        Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                                            /* 通知GMM激活                              */
        g_TcInfo.ucRrcConnStatus = TC_RRC_CONN_STATUS_PRESENT;                          /* RRC连接存在的标志位置位                  */

        /* 通知MTC环回状态 */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_START);
        break;

    case TC_OPEN_TEST_LOOP:
    case TC_CLOSE_TEST_LOOP:
        Tc_SndDataReq(TC_ACT_RB_TEST_MODE_CMP);                                         /* 发送激活响应消息                         */
        break;

    default:
        break;
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_RcvDeactRbTest
 *  FUNCTION : 通知nas其它task去激活
 *  INPUT    : VOS_UINT8
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.25   新规作成
      2.   张志勇      2004.11.23   修改发送去激活cmp消息的时机，在发送DataReq以前
      3.   L47619      2006.08.24   问题单: A32D05570
      4.   L47619      2006.09.08   问题单: A32D06342
      5. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送去激活
      6.日    期    : 2015年6月9日
        作    者    : wx270776
        修改内容    : TAS需求: 通知MTC环回状态
 ************************************************************************/
VOS_VOID Tc_RcvDeactRbTest()
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8             enCurrUtranMode;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* 没有正在处理其它消息                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvDeactRbTest:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }
    switch(g_TcInfo.ucTcState)
    {                                                                                   /* 根据当前的状态进行分发                   */
    case TC_OPEN_TEST_LOOP:
    case TC_CLOSE_TEST_LOOP:
        g_TcInfo.ucMsgType = TC_DEACT_RB_TEST_MODE;                                     /* 记录正在处理的消息类型                   */

        /* Deleted by wx270776 for OM融合, 2015-7-16, begin */
        //Tc_SndRfaTestControlMsg(ID_TC_RFA_DEACT_REQ);
        /* Deleted by wx270776 for OM融合, 2015-7-16, end */

        enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
        if ((VOS_TRUE == g_TcInfo.ucSndWphyCloseLoopNtfLable)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrUtranMode))
        {
            /* 根据DSP需求，在W下通知WPHY退出环回 */
            NAS_TC_SndWphyOpenLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_FALSE;
        }

        Tc_SndDataReq(TC_DEACT_RB_TEST_MODE_CMP);                                       /* 发送去激活响应消息                       */
        Tc_SndRabmTestReq(TC_RB_TEST_DEACTIVE);                                         /* 通知RABM去激活                           */
        Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                                           /* 通知MM去激活                             */
        Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                                          /* 通知GMM去激活                            */

        /* 通知MTC环回状态 */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
        break;

    case TC_NORMAL_MODE:
        Tc_SndDataReq(TC_DEACT_RB_TEST_MODE_CMP);                                       /* 发送去激活响应消息                       */
        break;

    default:
        break;
    }
    return;
}

/*****************************************************************************
函 数 名  : Tc_RcvResetUePosStoredInfo
功能描述  : 收到RESET UE POSITIONING STORED INFORMATION消息的处理
输入参数  : pRcvTcMsg
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史
1.日    期  : 2012年7月09日
  作    者  : L47619
  修改内容  : 新生成函数
*****************************************************************************/
VOS_VOID Tc_RcvResetUePosStoredInfo(VOS_UINT8 * pRcvTcMsg)
{
    TC_UE_POS_TECH_ENUM_UINT8           enUePosTech;

    /* 获取enUePosTech */
    enUePosTech = pRcvTcMsg[2];

    switch (enUePosTech)
    {
        case TC_UE_POS_TECH_AGPS:
        case TC_UE_POS_TECH_AGNSS:
            /* 向MTA发送清除指示 */
            Tc_SndMtaResetStoredPosInfoInd(enUePosTech);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvResetUePosStoredInfo:WARNING:Abnormal Msg!");
            break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Tc_GetMsgSize
 *  FUNCTION : 根据消息的原语ID，计算向L1发送的消息长度的工具函数
 *  INPUT    : usMsgId         发送的原语ID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : 消息长度
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.20  根据问题单新增:A32D02126
 ************************************************************************/
VOS_UINT32  Tc_GetMsgSize( VOS_UINT16 usMsgId )
{
    VOS_UINT32  ulMsgSize;

    switch ( usMsgId )
    {
        case TC_CLOSE_TCH_LOOP_REQ:
            ulMsgSize = sizeof(TC_CLOSE_TCH_LOOP_REQ_STRU);
            break;
        case TC_OPEN_TCH_LOOP_REQ:
            ulMsgSize = sizeof(TC_OPEN_TCH_LOOP_REQ_STRU);
            break;
        case TC_TEST_INTERFACE_REQ:
            ulMsgSize = sizeof(TC_TEST_INTERFACE_REQ_STRU);
            break;
        case TC_TEST_MODE_W_TO_G_IND:
            ulMsgSize = sizeof(TC_TEST_MODE_W_TO_G_IND_STRU);
            break;
        default:
            ulMsgSize = 0;
            break;
    }

    return ulMsgSize;
}



/***********************************************************************
 *  MODULE   : Tc_SndPhyMsg
 *  FUNCTION : 向L1发送消息的工具函数
 *  INPUT    : usMsgId         发送的原语ID
               pucStru         原语的结构体指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : WUEPS_SND_MSG_SUCCESS        发送成功
 *             WUEPS_SND_MSG_FAILURE        发送失败
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.20  根据问题单新增:A32D02126
 ************************************************************************/
VOS_INT32  Tc_SndPhyMsg( VOS_UINT16 usMsgId, VOS_UCHAR *pucStru )
{
    VOS_UINT32      ulMsgSize;
    VOS_UCHAR       *pMsg;
    MSG_CB          *pTmpMsg;

    ulMsgSize = Tc_GetMsgSize( usMsgId );
    if ( 0 == ulMsgSize )
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndPhyMsg:WARNING:usMsgId is Abnormal!");
        return VOS_ERR;
    }

    /*申请消息包:*/
    pMsg = ( VOS_UCHAR * )PS_ALLOC_MSG( WUEPS_PID_TC, ulMsgSize );
    if ( VOS_NULL_PTR == pMsg )
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndPhyMsg:ERROR:Alloc msg Error!");
        return VOS_ERR;
    }

    /*填写消息头:*/
    pTmpMsg                     = (MSG_CB *)pMsg;
    pTmpMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pTmpMsg->ulSenderPid        = WUEPS_PID_TC;
    pTmpMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;

    pTmpMsg->ulReceiverPid      = DSP_PID_GPHY;

    pTmpMsg->ulLength           = ulMsgSize;
    /*填写消息体:*/
    PS_NAS_MEM_CPY( pMsg + VOS_MSG_HEAD_LENGTH, pucStru, ulMsgSize );

    /*发送消息:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TC, pMsg ) )
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }

}


/***********************************************************************
 *  MODULE   : Tc_ParseTchLoopType
 *  FUNCTION : 分析TC_CLOSE_TCH_LOOP_CMD原语中的TCH环路类型
 *  INPUT    : ucSubChannel       原语中的IE字段:Sub-channel
 *  OUTPUT   : VOS_VOID
 *  RETURN   : 环路类型
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.18  根据问题单新增:A32D02126
 ************************************************************************/
VOS_UINT16 Tc_ParseTchLoopType( VOS_UINT8 ucSubChannel )
{
    VOS_UINT8 ucTag = (ucSubChannel & 0x3E) >> 1;

    if ( 0x0 == ucTag )
    {
        return TC_TCH_LOOP_TYPE_A;
    }
    else if ( 0x01 == ucTag )
    {
        return TC_TCH_LOOP_TYPE_B;
    }
    else if ( ( ucTag >= 0x02 ) && ( ucTag <= 0x03 ) )
    {
        return TC_TCH_LOOP_TYPE_C;
    }
    else if ( ( ucTag >= 0x04 ) && ( ucTag <= 0x07 ) )
    {
        return TC_TCH_LOOP_TYPE_D;
    }
    else if ( ( ucTag >= 0x08 ) && ( ucTag <= 0x0B ) )
    {
        return TC_TCH_LOOP_TYPE_E;
    }
    else if ( ( ucTag >= 0x0C ) && ( ucTag <= 0x0F ) )
    {
        return TC_TCH_LOOP_TYPE_F;
    }
    else if ( ( ucTag >= 0x1C ) && ( ucTag <= 0x1F ) )
    {
        return TC_TCH_LOOP_TYPE_I;
    }
    else
    {
        return TC_TCH_LOOP_TYPE_ABNORMAL;
    }
}



/***********************************************************************
 *  MODULE   : Tc_ParseTchChannelType
 *  FUNCTION : 分析TC_CLOSE_TCH_LOOP_CMD原语中的TCH的Channel类型
 *  INPUT    : ucSubChannel       原语中的IE字段:Sub-channel
 *  OUTPUT   : VOS_VOID
 *  RETURN   : Channel类型
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.20  根据问题单新增:A32D02126
 ************************************************************************/
VOS_UINT16 Tc_ParseTchChannelType( VOS_UINT8 ucSubChannel )
{
    VOS_UINT16  usChannelType = (VOS_UINT16)ucSubChannel & 0x1;

    return usChannelType;
}



/***********************************************************************
 *  MODULE   : Tc_ParseTestDevice
 *  FUNCTION : 分析TC_TEST_INTERFACE原语中的Test Device 类型
 *  INPUT    : ucTestDevice       原语中的IE字段:Test Device
 *  OUTPUT   : VOS_VOID
 *  RETURN   : 环路类型
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.18  根据问题单新增:A32D02126
 ************************************************************************/
VOS_UINT16 Tc_ParseTestDevice( VOS_UINT8 ucTestDeviceIE )
{
    VOS_UINT16   usTestDevice = (VOS_UINT16)(ucTestDeviceIE & 0x07);

    usTestDevice &= 0x00FF;

    if (     (TC_TEST_DEVICE_0 != usTestDevice)
          && (TC_TEST_DEVICE_1 != usTestDevice)
          && (TC_TEST_DEVICE_2 != usTestDevice)
          && (TC_TEST_DEVICE_3 != usTestDevice) )
    {
        usTestDevice = TC_TEST_DEVICE_ABNORMAL;
    }
    return usTestDevice;
}



/***********************************************************************
 *  MODULE   : Tc_SndOpenLoopAck
 *  FUNCTION : 向网侧发送OPEN_LOOP_ACK消息
 *  INPUT    : ucAckInfo                  最后一位置为1的Acknowledge Info
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.18  根据问题单新增:A32D02126
 ************************************************************************/
VOS_VOID Tc_SndOpenLoopAck(VOS_UINT8 ucAckInfo)
{
    TCMM_DATA_REQ_STRU          *pMmDataReq = VOS_NULL_PTR;                         /* 定义原语类型指针 */


    pMmDataReq = (TCMM_DATA_REQ_STRU*)PS_ALLOC_MSG(
                  WUEPS_PID_TC, sizeof(TCMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pMmDataReq )
    {                                                                                   /* 内存申请失败                             */
        return;                                                                         /* 返回                                     */
    }

    pMmDataReq->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pMmDataReq->MsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pMmDataReq->MsgHeader.ulLength         = sizeof( TCMM_DATA_REQ_STRU ) - VOS_MSG_HEAD_LENGTH;
    pMmDataReq->MsgHeader.ulMsgName        = TCMM_DATA_REQ;                         /* 消息名称         */

    pMmDataReq->SendTcMsg.ulTcMsgSize = 3;                                          /* 设置消息长度     */
    pMmDataReq->SendTcMsg.aucTcMsg[0] = 0x0F;                                       /* 设置PD           */
    pMmDataReq->SendTcMsg.aucTcMsg[1] = TC_OPEN_LOOP_CMD;                           /* 设置消息类型     */
    pMmDataReq->SendTcMsg.aucTcMsg[2] = ucAckInfo;                                  /* 填写Acknowledge Info */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pMmDataReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndOpenLoopAck():WARNING:SEND MSG FIAL");
    }

    return;
}



/***********************************************************************
 *  MODULE   : Tc_RcvPhyCloseTchLoopCnf
 *  FUNCTION : 接收到物理层的关闭TCH环回测试的CNF原语
 *  INPUT    : pCloseTchLoopCnf         除去VOS_MSG_HEADER的HPA消息指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.20  根据问题单新增:A32D02126
 ************************************************************************/
VOS_VOID Tc_RcvPhyCloseTchLoopCnf(TC_CLOSE_TCH_LOOP_CNF_STRU *pCloseTchLoopCnf)
{
    if ( (TC_NORMAL_MODE == g_TcInfo.ucTcState)
         && (TC_CLOSE_TCH_LOOP_CMD == g_TcInfo.ucMsgType) )
    {
        /*切换TC状态:*/
        g_TcInfo.ucTcState = TC_GSM_CLOSE_TCH_LOOP;

        /*发送激活响应消息:*/
        Tc_SndDataReq(TC_CLOSE_TCH_LOOP_ACK);
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvPhyCloseTchLoopCnf:WARNING:Abnormal Msg!");
    }
}



/***********************************************************************
 *  MODULE   : Tc_RcvPhyOpenTchLoopCnf
 *  FUNCTION : 接收到物理层的打开TCH环回测试的CNF原语
 *  INPUT    : pOpenTchLoopCnf          除去VOS_MSG_HEADER的HPA消息指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.20  根据问题单新增:A32D02126
 ************************************************************************/
VOS_VOID Tc_RcvPhyOpenTchLoopCnf(TC_OPEN_TCH_LOOP_CNF_STRU *pOpenTchLoopCnf)
{
    VOS_UINT8      ucAckInfo;

    if ( (TC_GSM_CLOSE_TCH_LOOP == g_TcInfo.ucTcState)
         && (TC_OPEN_LOOP_CMD == g_TcInfo.ucMsgType) )
    {
        if ( TC_TCH_LOOP_TYPE_C == g_TcInfo.usTchLoopType )
        {
            /*把从网侧收到的OPEN_LOOP_CMD消息的最后一个比特置"1"，然后回发给网侧*/
            ucAckInfo = (VOS_UINT8)(pOpenTchLoopCnf->usAckInfo | 0x1);
            Tc_SndOpenLoopAck(ucAckInfo);
        }

        /*切换TC状态:*/
        g_TcInfo.ucTcState = TC_NORMAL_MODE;

        /*清消息标志:*/
        g_TcInfo.ucMsgType = TC_MSG_INVALID;
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvPhyOpenTchLoopCnf:WARNING:Abnormal Msg!");
    }
}



/***********************************************************************
 *  MODULE   : Tc_RcvPhyTestInterfaceCnf
 *  FUNCTION : 接收到物理层的TEST_INTERFACE的CNF原语
 *  INPUT    : pTestInterfaceCnf        除去VOS_MSG_HEADER的HPA消息指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.20  根据问题单新增:A32D02126
 ************************************************************************/
VOS_VOID Tc_RcvPhyTestInterfaceCnf(TC_TEST_INTERFACE_CNF_STRU *pTestInterfaceCnf)
{
    if ( (TC_GSM_CLOSE_TCH_LOOP == g_TcInfo.ucTcState)
         && (TC_TEST_INTERFACE == g_TcInfo.ucMsgType) )
    {
        /*清消息标志:*/
        g_TcInfo.ucMsgType = TC_MSG_INVALID;
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvPhyTestInterfaceCnf:WARNING:Abnormal Msg!");
    }
}



/***********************************************************************
 *  MODULE   : Tc_RcvCloseTchLoopCmd
 *  FUNCTION : 接收到GSM下的TC_CLOSE_TCH_LOOP_CMD原语
 *  INPUT    : pRcvTcMsg         收到的原语码流指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.17  根据问题单新增:A32D02126
      2.   L47619   2006.08.24   问题单: A32D05570
      3. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送激活
      4. 日    期   : 2015年5月15日
         作    者   : wx270776
         修改内容   : 增加TAS环回可维可测

 ************************************************************************/
VOS_VOID Tc_RcvCloseTchLoopCmd(VOS_UCHAR *pRcvTcMsg)
{
    TC_CLOSE_TCH_LOOP_REQ_STRU  TcCloseTchLoopReq;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                      /*没有正在处理其它消息*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseTchLoopCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {                                                                      /*根据当前的状态进行分发*/
        case TC_NORMAL_MODE:
            g_TcInfo.ucMsgType = TC_CLOSE_TCH_LOOP_CMD;                    /*记录正在处理的消息类型*/

            /*向以下模块发送启动环回消息:*/
            Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                            /*通知MM激活(2G和3G中的处理一致，故也使用宏TC_RB_TEST_ACTIVE)*/
            Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                           /*通知GMM激活*/

            /*分析TCH 环回类型:*/
            g_TcInfo.usTchLoopType = Tc_ParseTchLoopType(pRcvTcMsg[2]);

            /*向物理层发送指示:*/
            TcCloseTchLoopReq.usMsgID       = TC_CLOSE_TCH_LOOP_REQ;
            TcCloseTchLoopReq.usTchLoopType = g_TcInfo.usTchLoopType;                           /*分析GSM下TCH的环路类型*/
            TcCloseTchLoopReq.usSubChan     = Tc_ParseTchChannelType(pRcvTcMsg[2]);             /*分析GSM下TCH的Channel类型*/
            if ( VOS_OK != Tc_SndPhyMsg(TC_CLOSE_TCH_LOOP_REQ, (VOS_UCHAR *)(&TcCloseTchLoopReq)) )
            {
                g_TcInfo.ucMsgType = TC_MSG_INVALID;
            }

            /* 通知MTC环回状态 */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_START);
            break;

        case TC_GSM_CLOSE_TCH_LOOP:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseTchLoopCmd:WARNING:Ignore this Msg!");
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_RcvCloseTchLoopCmd:ERROR:g_TcInfo.ucTcState ERROR!");
            break;
    }
    return;
}



/***********************************************************************
 *  MODULE   : Tc_RcvOpenLoopCmd
 *  FUNCTION : 接收到GSM下的TC_OPEN_LOOP_CMD原语
 *  INPUT    : pRcvTcMsg         收到的原语码流指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.17  根据问题单新增:A32D02126
      2.   L47619   2006.08.24   问题单: A32D05570
      3. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送激活
      4. 日    期   : 2015年5月15日
         作    者   : wx270776
         修改内容   : 增加TAS环回可维可测

 ************************************************************************/
VOS_VOID Tc_RcvOpenLoopCmd(VOS_UCHAR *pRcvTcMsg)
{
    TC_OPEN_TCH_LOOP_REQ_STRU   TcOpenTchLoopReq;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                      /*没有正在处理其它消息*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoopCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {                                                                      /*根据当前的状态进行分发*/
        case TC_GSM_CLOSE_TCH_LOOP:
            g_TcInfo.ucMsgType = TC_OPEN_LOOP_CMD;                         /*记录正在处理的消息类型*/

            /*向以下模块发送结束环回消息:*/
            Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知MM激活*/
            Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*通知GMM激活*/

            /*向物理层发送指示:*/
            TcOpenTchLoopReq.usMsgID   = TC_OPEN_TCH_LOOP_REQ;
            TcOpenTchLoopReq.usAckInfo = (VOS_UINT16)(pRcvTcMsg[2]);
            if ( VOS_OK != Tc_SndPhyMsg(TC_OPEN_TCH_LOOP_REQ, (VOS_UCHAR *)(&TcOpenTchLoopReq)) )
            {
                g_TcInfo.ucMsgType = TC_MSG_INVALID;
            }

            /* 通知MTC环回状态 */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        case TC_NORMAL_MODE:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoopCmd:WARNING:Ignore this Msg!");
            break;

        default:
            break;
    }

    return;
}



/***********************************************************************
 *  MODULE   : Tc_RcvTestInterface
 *  FUNCTION : 接收到GSM下的TC_TEST_INTERFACE原语
 *  INPUT    : pRcvTcMsg         收到的原语码流指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.17  根据问题单新增:A32D02126
 ************************************************************************/
VOS_VOID Tc_RcvTestInterface(VOS_UCHAR *pRcvTcMsg)
{
    TC_TEST_INTERFACE_REQ_STRU      TcTestInterfaceReq;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                      /*没有正在处理其它消息*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvTestInterface:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {                                                                      /*根据当前的状态进行分发*/
        case TC_GSM_CLOSE_TCH_LOOP:
            g_TcInfo.ucMsgType = TC_TEST_INTERFACE;                        /*记录正在处理的消息类型*/

            /*向物理层发送指示:*/
            TcTestInterfaceReq.usMsgID      = TC_TEST_INTERFACE_REQ;
            TcTestInterfaceReq.usTestDevice = Tc_ParseTestDevice(pRcvTcMsg[2]);
            if ( VOS_OK != Tc_SndPhyMsg(TC_TEST_INTERFACE_REQ, (VOS_UCHAR *)(&TcTestInterfaceReq)) )
            {
                g_TcInfo.ucMsgType = TC_MSG_INVALID;
            }
            break;
        case TC_NORMAL_MODE:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvTestInterface:WARNING:Ignore this Msg!");
            break;
        default:
            break;
    }
    return;
}



/***********************************************************************
 *  MODULE   : Tc_RcvHpaMsgHandle
 *  FUNCTION : 接收到HPA的原语
 *  INPUT    : pMsg           收到的HPA原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.02.17  根据问题单新增:A32D02126
 ************************************************************************/
VOS_VOID  Tc_RcvHpaMsgHandle(struct MsgCB *pMsg)
{
    VOS_UINT16      usMsgId;

    usMsgId = *((VOS_UINT16 *)(pMsg->aucValue));

    switch (usMsgId)
    {
        case TC_CLOSE_TCH_LOOP_CNF:
            Tc_RcvPhyCloseTchLoopCnf( &(((TC_CLOSE_TCH_LOOP_CNF_MSG *)pMsg)->TcCloseTchLoopCnf) );
            break;
        case TC_OPEN_TCH_LOOP_CNF:
            Tc_RcvPhyOpenTchLoopCnf( &(((TC_OPEN_TCH_LOOP_CNF_MSG *)pMsg)->TcOpenTchLoopCnf) );
            break;
        case TC_TEST_INTERFACE_CNF:
            Tc_RcvPhyTestInterfaceCnf( &(((TC_TEST_INTERFACE_CNF_MSG *)pMsg)->TcTestInterfaceCnf) );
            break;
        default:
            break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndGrmGtmSetupReq
 *  FUNCTION : 向GRM发送建立环回请求信息
 *  INPUT    : pMsg           收到的GPRS_TEST_MODE_CMD空口消息指针
 *  OUTPUT   : VOID
 *  RETURN   : WUEPS_SND_MSG_SUCCESS        发送成功
               WUEPS_SND_MSG_FAILURE        发送失败
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.04.12  根据问题单新增:A32D08523
 ************************************************************************/
VOS_UINT32  Tc_SndGrmGtmSetupReq(VOS_UCHAR *pMsg)
{
    GRM_GTM_SETUP_REQ_MSG   *pSetupReqMsg;
    VOS_UINT32               ulMsgLength;

    /*GRM_GTM_SETUP_REQ_MSG 的消息长度*/
    ulMsgLength = sizeof(GRM_GTM_SETUP_REQ_MSG) - VOS_MSG_HEAD_LENGTH;

    /*申请消息包*/
    pSetupReqMsg = (GRM_GTM_SETUP_REQ_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pSetupReqMsg )
    {
        /*打印出错信息---申请消息包失败*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmSetupReq:ERROR:Alloc msg Fail!");
        return VOS_ERR;
    }
    /*填写消息头*/
    pSetupReqMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulSenderPid       = WUEPS_PID_TC;
    pSetupReqMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulReceiverPid     = UEPS_PID_GRM;
    pSetupReqMsg->ulLength          = ulMsgLength;

    /*填写消息内容*/
    pSetupReqMsg->usMsgType         = ID_GRM_GTM_SETUP_REQ;
    pSetupReqMsg->usTransId         = 0;

    pSetupReqMsg->stGLSetupReq.ucPduDescript1 = pMsg[2];    /*第一个PDU Descript字节*/
    pSetupReqMsg->stGLSetupReq.ucPduDescript2 = pMsg[3];    /*第二个PDU Descript字节*/
    pSetupReqMsg->stGLSetupReq.ucModeFlag     = pMsg[4];    /*Mode Flag字节*/
    pSetupReqMsg->stGLSetupReq.Rsv            = 0;          /*为了四字节对齐而加入的Reserved字节*/

    /*发送该消息*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pSetupReqMsg) )
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmSetupReq:WARNING:SEND GRM_GTM_SETUP_REQ msg FAIL!");
        return VOS_ERR;
    }
    else
    {
        /*打印流程信息---发送了消息:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmSetupReq:NORMAL:SEND GRM_GTM_SETUP_REQ Msg Success.");

        /*记录下当前的子状态*/
        g_TcInfo.ucMsgType = TC_GPRS_TEST_MODE_CMD;
        return VOS_OK;
    }
}




/***********************************************************************
 *  MODULE   : Tc_SndGrmGtmRelRsp
 *  FUNCTION : 向GRM发送释放环回响应
 *  INPUT    : VOID
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.04.12  根据问题单新增:A32D08523
 ************************************************************************/
VOS_VOID  Tc_SndGrmGtmRelRsp(VOS_VOID)
{
    GRM_GTM_REL_RSP_MSG     *pRelRspMsg;
    VOS_UINT32               ulMsgLength;

    /*GRM_GTM_REL_RSP_MSG 的消息长度*/
    ulMsgLength = sizeof(GRM_GTM_REL_RSP_MSG) - VOS_MSG_HEAD_LENGTH;

    /*申请消息包*/
    pRelRspMsg = (GRM_GTM_REL_RSP_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pRelRspMsg )
    {
        /*打印出错信息---申请消息包失败*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmRelRsp:ERROR:Alloc msg Fail!");
        return;
    }

    /*填写消息头*/
    pRelRspMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pRelRspMsg->ulSenderPid       = WUEPS_PID_TC;
    pRelRspMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pRelRspMsg->ulReceiverPid     = UEPS_PID_GRM;
    pRelRspMsg->ulLength          = ulMsgLength;

    /*填写消息内容*/
    pRelRspMsg->usMsgType         = ID_GRM_GTM_REL_RSP;
    pRelRspMsg->usTransId         = 0;

    /*发送该消息*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pRelRspMsg) )
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmRelRsp:WARNING:SEND GRM_GTM_REL_RSP msg FAIL!");
    }
    else
    {
        /*打印流程信息---发送了消息:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmRelRsp:NORMAL:SEND GRM_GTM_REL_RSP Msg Success.");
    }

    return;

}


/***********************************************************************
 *  MODULE   : Tc_RcvGrmGtmSetupCnf
 *  FUNCTION : 接收到GRM的建立环回确认信息
 *  INPUT    : pMsg             TC_GTM_SETUP_CNF_MSG消息指针
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.04.12  根据问题单新增:A32D08523
      2. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送激活

 ************************************************************************/
VOS_VOID  Tc_RcvGrmGtmSetupCnf(VOS_UCHAR *pMsg)
{
    TC_GTM_SETUP_CNF_MSG *pSetupCnfMsg;

    pSetupCnfMsg = (TC_GTM_SETUP_CNF_MSG *)pMsg;

    if ( (TC_NORMAL_MODE == g_TcInfo.ucTcState)
         && (TC_GPRS_TEST_MODE_CMD == g_TcInfo.ucMsgType) )
    {
        if ( GTM_STATUS_SETUP_OK == pSetupCnfMsg->usTransId )
        {
            /*切换状态:*/
            g_TcInfo.ucTcState = TC_GPRS_CLOSE_TCH_LOOP;
            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            /* 闪灯: GPRS环回建立 */
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT);
			/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
        }
        else   /*失败*/
        {
            /*打印警告信息---GPRS环回建立失败:*/
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmSetupCnf:WARNING:GPRS TC setup FAIL!");

            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /*向以下模块发送结束环回消息:*/
            Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知MM激活*/
            Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*通知GMM激活*/
            Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*通知CC激活*/
            Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SM激活*/
            Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*通知SMS激活*/
            Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SS激活*/
        }
    }
    else
    {
        /*打印警告信息---接收了不合逻辑的消息:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmSetupCnf:WARNING:RECEIVE An Illogic Msg!");
    }

    return;
}




/***********************************************************************
 *  MODULE   : Tc_RcvGrmGtmRelInd
 *  FUNCTION : 接收到GRM的释放环回指示信息
 *  INPUT    : VOID
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.04.12  根据问题单新增:A32D08523
      2. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送激活
      3. 日    期   : 2013年3月30日
         作    者   : l00167671
         修改内容   : 主动上报AT命令控制下移至C核
 ************************************************************************/
VOS_VOID  Tc_RcvGrmGtmRelInd(VOS_VOID)
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmRelInd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    if ( TC_GPRS_CLOSE_TCH_LOOP == g_TcInfo.ucTcState )
    {
        /*向GRM发送释放环回响应信息*/
        Tc_SndGrmGtmRelRsp();

        /*向以下模块发送结束环回消息:*/
        Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知MM激活*/
        Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*通知GMM激活*/
        Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*通知CC激活*/
        Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SM激活*/
        Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*通知SMS激活*/
        Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SS激活*/

        /*切换状态*/
        g_TcInfo.ucTcState = TC_NORMAL_MODE;

		/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        /* 闪灯: GPRS环回释放 */
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT);
		/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmRelInd:WARNING:Illogic State when receive TC_GTM_REL_IND Msg!");
    }

    return;
}




/***********************************************************************
 *  MODULE   : Tc_RcvGrmMsgHandle
 *  FUNCTION : 接收到GRM的原语
 *  INPUT    : pMsg           收到的GRM原语头指针
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.04.12  根据问题单新增:A32D08523
 ************************************************************************/
VOS_VOID  Tc_RcvGrmMsgHandle(struct MsgCB *pMsg)
{
    GPRS_LOOP_NO_CONTENT_MSG    *pRcvMsg;

    pRcvMsg = (GPRS_LOOP_NO_CONTENT_MSG *)pMsg;
    switch ( pRcvMsg->usMsgType )
    {
        case ID_TC_GTM_SETUP_CNF :
            Tc_RcvGrmGtmSetupCnf((VOS_UCHAR *)pMsg);
            break;
        case ID_TC_GTM_REL_IND :
            Tc_RcvGrmGtmRelInd();
            break;
        case ID_GTM_TC_SRB_SETUP_CNF:
            Tc_RcvGrmGtmEgprsSetupCnf((VOS_UCHAR *)pMsg);
            break;
        case ID_GTM_TC_SRB_REL_IND:
            Tc_RcvGrmGtmEgprsRelInd();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmMsgHandle:WARNING:Msg type Error!");
            break;
    }

    return;
}



/***********************************************************************
 *  MODULE   : Tc_RcvGprsTestModeCmd
 *  FUNCTION : 接收到GPRS下的GPRS_TEST_MODE_CMD
 *  INPUT    : pRcvTcMsg        收到的GPRS_TEST_MODE_CMD原语指针
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2006.04.12  根据问题单新增:A32D08523
      2. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送激活

 ************************************************************************/
VOS_VOID  Tc_RcvGprsTestModeCmd(VOS_UCHAR *pRcvTcMsg)
{
    VOS_UINT32      ulResult;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGprsTestModeCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
            /*向GRM发送建立环回请求信息*/
            ulResult = Tc_SndGrmGtmSetupReq(pRcvTcMsg);
            if ( VOS_OK == ulResult )
            {
                /*向以下模块发送启动环回消息:*/
                Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                            /*通知MM激活(2G和3G中的处理一致，故也使用宏TC_RB_TEST_ACTIVE)*/
                Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                           /*通知GMM激活*/
                Tc_SndCcTestReq(TC_RB_TEST_ACTIVE);                            /*通知CC激活*/
                Tc_SndSmTestReq(TC_RB_TEST_ACTIVE);                            /*通知SM激活*/
                Tc_SndSmsTestReq(TC_RB_TEST_ACTIVE);                           /*通知SMS激活*/
                Tc_SndSsTestReq(TC_RB_TEST_ACTIVE);                            /*通知SS激活*/
            }
            break;
        case TC_GPRS_CLOSE_TCH_LOOP:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGprsTestModeCmd:WARNING:Ignore this Msg!");
            break;
        default:
            break;
    }

    return;
}



/*****************************************************************************
 函 数 名  : Tc_SndGrmGtmEgprsSetupReq
 功能描述  : 向GRM发送建立EGPRS环回请求信息
 输入参数  : ucModeFlg - 环回模式
 输出参数  : 无
 返 回 值  : VOS_OK    -  消息发送成功
             VOS_ERR   -  消息发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年08月05日
    作    者   : L47619
    修改内容   : EGPRS环回特性

  2.日    期   : 2011年8月11日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011081101776, TC和GRM之间的接口增加环回模式参数

*****************************************************************************/
VOS_UINT32  Tc_SndGrmGtmEgprsSetupReq(
    VOS_UINT8                           ucModeFlg

)
{
    TC_GTM_SRB_SETUP_REQ_MSG     *pSetupReqMsg;
    VOS_UINT32                       ulMsgLength;

    /*ID_TC_GTM_SRB_SETUP_REQ 的消息长度*/
    ulMsgLength = sizeof(TC_GTM_SRB_SETUP_REQ_MSG) - VOS_MSG_HEAD_LENGTH;

    /*申请消息包*/
    pSetupReqMsg = (TC_GTM_SRB_SETUP_REQ_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pSetupReqMsg )
    {
        /*打印出错信息---申请消息包失败*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmEgprsSetupReq:ERROR:Alloc msg Fail!");
        return VOS_ERR;
    }
    /*填写消息头*/
    pSetupReqMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulSenderPid       = WUEPS_PID_TC;
    pSetupReqMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulReceiverPid     = UEPS_PID_GRM;
    pSetupReqMsg->ulLength          = ulMsgLength;

    /*填写消息内容*/
    pSetupReqMsg->usMsgType         = ID_TC_GTM_SRB_SETUP_REQ;
    pSetupReqMsg->usModeFlg         = ucModeFlg;

    /*发送该消息*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pSetupReqMsg) )
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmEgprsSetupReq:WARNING:SEND TC_GTM_SRB_SETUP_REQ_MSG msg FAIL!");
        return VOS_ERR;
    }
    else
    {
        /*打印流程信息---发送了消息:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmEgprsSetupReq:NORMAL:SEND TC_GTM_SRB_SETUP_REQ_MSG Msg Success.");

        /*记录下当前的子状态*/
        g_TcInfo.ucMsgType = TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD;
        return VOS_OK;
    }
}


/***********************************************************************
 *  MODULE   : Tc_SndGrmGtmEgprsRelRsp
 *  FUNCTION : 向GRM发送释放EGPRS环回响应
 *  INPUT    : VOID
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2008.08.05  EGPRS特性
 ************************************************************************/
VOS_VOID  Tc_SndGrmGtmEgprsRelRsp(VOS_VOID)
{
    TC_GTM_SRB_REL_RSP_MSG     *pRelRspMsg;
    VOS_UINT32                     ulMsgLength;

    /*TC_GTM_SRB_REL_RSP_MSG 的消息长度*/
    ulMsgLength = sizeof(TC_GTM_SRB_REL_RSP_MSG) - VOS_MSG_HEAD_LENGTH;

    /*申请消息包*/
    pRelRspMsg = (TC_GTM_SRB_REL_RSP_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pRelRspMsg )
    {
        /*打印出错信息---申请消息包失败*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmEgprsRelRsp:ERROR:Alloc msg Fail!");
        return;
    }

    /*填写消息头*/
    pRelRspMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pRelRspMsg->ulSenderPid       = WUEPS_PID_TC;
    pRelRspMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pRelRspMsg->ulReceiverPid     = UEPS_PID_GRM;
    pRelRspMsg->ulLength          = ulMsgLength;

    /*填写消息内容*/
    pRelRspMsg->usMsgType         = ID_TC_GTM_SRB_REL_RSP;
    pRelRspMsg->usTransId         = 0;

    /*发送该消息*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pRelRspMsg) )
    {
        /*打印警告信息---发送消息失败:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmEgprsRelRsp:WARNING:SEND ID_TC_GTM_SRB_REL_RSP msg FAIL!");
    }
    else
    {
        /*打印流程信息---发送了消息:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmEgprsRelRsp:NORMAL:SEND ID_TC_GTM_SRB_REL_RSP Msg Success.");
    }

    return;
}



/***********************************************************************
 *  MODULE   : Tc_RcvGrmGtmEgprsSetupCnf
 *  FUNCTION : 接收到GRM的建立EGPRS环回确认信息
 *  INPUT    : pMsg             GTM_TC_SRB_SETUP_CNF消息指针
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2008.08.05  EGPRS特性
      2. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送激活
      3. 日    期   : 2013年3月30日
         作    者   : l00167671
         修改内容   : 主动上报AT命令控制下移至C核
 ************************************************************************/
VOS_VOID  Tc_RcvGrmGtmEgprsSetupCnf(VOS_UCHAR *pMsg)
{
    GTM_TC_SRB_SETUP_CNF_MSG *pSetupCnfMsg;

    pSetupCnfMsg = (GTM_TC_SRB_SETUP_CNF_MSG *)pMsg;

    if ( (TC_NORMAL_MODE == g_TcInfo.ucTcState)
         && (TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD == g_TcInfo.ucMsgType) )
    {
        if ( GTM_STATUS_SETUP_OK == pSetupCnfMsg->usTransId )
        {
            /*切换状态:*/
            g_TcInfo.ucTcState = TC_EGPRS_CLOSE_TCH_LOOP;
            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            /* 闪灯: EGPRS环回建立 */
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT);
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
        }
        else   /*失败*/
        {
            /*打印警告信息---EGPRS环回建立失败:*/
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsSetupCnf:WARNING:EGPRS TC setup FAIL!");

            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /*向以下模块发送结束环回消息:*/
            Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知MM激活*/
            Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*通知GMM激活*/
            Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*通知CC激活*/
            Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SM激活*/
            Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*通知SMS激活*/
            Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SS激活*/
        }
    }
    else
    {
        /*打印警告信息---接收了不合逻辑的消息:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsSetupCnf:WARNING:RECEIVE An Illogic Msg!");
    }

    return;
}



/***********************************************************************
 *  MODULE   : Tc_RcvGrmGtmEgprsRelInd
 *  FUNCTION : 接收到GRM的释放EGPRS环回指示信息
 *  INPUT    : VOID
 *  OUTPUT   : VOID
 *  RETURN   : VOID
 *  NOTE     :
 *  HISTORY  :
      1.   L47619   2008.08.05  EGPRS特性
      2. 日    期   : 2011年9月14日
         作    者   : l00171473
         修改内容   : V7R1PhaseII, TC环回调整，删除向MMC发送去激活
      3. 日    期   : 2013年3月30日
         作    者   : l00167671
         修改内容   : 主动上报AT命令控制下移至C核
 ************************************************************************/
VOS_VOID  Tc_RcvGrmGtmEgprsRelInd(VOS_VOID)
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsRelInd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    if ( TC_EGPRS_CLOSE_TCH_LOOP == g_TcInfo.ucTcState )
    {
        /*向GRM发送释放EGPRS环回释放响应信息*/
        Tc_SndGrmGtmEgprsRelRsp();

        /*向以下模块发送结束环回消息:*/
        Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知MM激活*/
        Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*通知GMM激活*/
        Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*通知CC激活*/
        Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SM激活*/
        Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*通知SMS激活*/
        Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*通知SS激活*/

        /*切换状态*/
        g_TcInfo.ucTcState = TC_NORMAL_MODE;

        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        /* 闪灯: EGPRS环回释放 */
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsRelInd:WARNING:Illogic State when receive ID_GTM_TC_SRB_REL_IND Msg!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : Tc_RcvEgprsLoopBackCmd
 功能描述  : 接收到EGPRS下的TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD
 输入参数  : ucModeFlg - 环回模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年08月05日
    作    者   : L47619
    修改内容   : EGPRS环回特性

  2.日    期   : 2011年8月11日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011081101776, TC和GRM之间的接口增加环回模式参数

*****************************************************************************/
VOS_VOID  Tc_RcvEgprsLoopBackCmd(
    VOS_UINT8                           ucModeFlg
)
{
    VOS_UINT32      ulResult;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvEgprsLoopBackCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
            /*向GRM发送建立EGPRS环回请求信息*/
            ulResult = Tc_SndGrmGtmEgprsSetupReq(ucModeFlg);
            if ( VOS_OK == ulResult )
            {
                /*向以下模块发送启动环回消息:*/
                Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                            /*通知MM激活(2G和3G中的处理一致，故也使用宏TC_RB_TEST_ACTIVE)*/
                Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                           /*通知GMM激活*/
                Tc_SndCcTestReq(TC_RB_TEST_ACTIVE);                            /*通知CC激活*/
                Tc_SndSmTestReq(TC_RB_TEST_ACTIVE);                            /*通知SM激活*/
                Tc_SndSmsTestReq(TC_RB_TEST_ACTIVE);                           /*通知SMS激活*/
                Tc_SndSsTestReq(TC_RB_TEST_ACTIVE);                            /*通知SS激活*/
            }
            break;
        case TC_EGPRS_CLOSE_TCH_LOOP:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvEgprsLoopBackCmd:WARNING:Ignore this Msg!");
            break;
        default:
            break;
    }

    return;
}


/***********************************************************************
 *  MODULE   : Tc_RcvMmDataInd
 *  FUNCTION : 收到TCMM_DATA_IND原语的处理
 *  INPUT    : VOS_VOID     *pMsg           收到的MM原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      2.   L47619   2006.02.17   问题单:A32D02126
 ************************************************************************/
VOS_VOID Tc_RcvMmDataInd(VOS_VOID *pMsg)
{
    TCMM_DATA_IND_STRU         *pRcvMsg;                                                /* 收到的消息                               */
    VOS_UINT8                      *pRcvTcMsg;                                              /* 原语中承载的Tc空口消息                   */
    VOS_UINT8                      ucMsgType;                                               /* 空口消息得类型                           */

    pRcvMsg = (TCMM_DATA_IND_STRU *)(pMsg);                                             /* 结构体类型转换                           */

    if( 2 > pRcvMsg->RcvTcMsg.ulTcMsgSize )
    {                                                                                   /* 消息过短                                 */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvMmDataInd:WARNING:2 > pRcvMsg->RcvTcMsg.ulTcMsgSize");
        return;
    }
    if(( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&
       ( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0)))
    {                                                                                   /* PD为f和SI为0，可以分发处理               */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvMmDataInd:WARNING:( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0))");
        return;
    }
    pRcvTcMsg = pRcvMsg->RcvTcMsg.aucTcMsg;                                             /* 取得消息内容地址                         */
    ucMsgType = pRcvTcMsg[1];                                                           /* 取得空口消息得类型                       */
    g_TcInfo.ucCnDomain = TC_CN_DOMAIN_CS;                                              /* 记录消息在CS信令上传输                   */
    switch(ucMsgType)
    {                                                                                   /* 按照消息类型进行分发                     */
    case TC_CLOSE_UE_TEST_LOOP:
        Tc_RcvCloseLoop(pRcvTcMsg);                                                     /* 处理TC_CLOSE_UE_TEST_LOOP消息            */
        break;
    case TC_OPEN_UE_TEST_LOOP:
        Tc_RcvOpenLoop();                                                               /* 处理TC_OPEN_UE_TEST_LOOP消息             */
        break;
    case TC_ACT_RB_TEST_MODE:
        Tc_RcvActRbTest();                                                              /* 处理TC_ACT_RB_TEST_MODE消息              */
        break;
    case TC_DEACT_RB_TEST_MODE:
        Tc_RcvDeactRbTest();                                                            /* 处理TC_DEACT_RB_TEST_MODE消息            */
        break;
    case TC_RESET_UE_POS_STORED_INFO:
        Tc_RcvResetUePosStoredInfo(pRcvTcMsg);
        break;
    case TC_CLOSE_TCH_LOOP_CMD:
        Tc_RcvCloseTchLoopCmd(pRcvTcMsg);
        break;
    case TC_OPEN_LOOP_CMD:
        Tc_RcvOpenLoopCmd(pRcvTcMsg);
        break;
    case TC_TEST_INTERFACE:
        Tc_RcvTestInterface(pRcvTcMsg);
        break;
    default:
        break;
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_RcvGmmDataInd
 *  FUNCTION : 收到TCGMM_DATA_IND原语的处理
 *  INPUT    : VOS_VOID     *pMsg           收到的MM原语头指针
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   张志勇      2004.05.24   新规作成
      2.日    期   : 2011年8月11日
        作    者   : A00165503
        修改内容   : 问题单号: DTS2011081101776, TC和GRM之间的接口增加环回模式参数
 ************************************************************************/
VOS_VOID Tc_RcvGmmDataInd(VOS_VOID *pMsg)
{
    TCGMM_DATA_IND_STRU                *pRcvMsg;                                                /* 收到的消息                               */
    VOS_UINT8                          *pRcvTcMsg;                                              /* 原语中承载的Tc空口消息                   */
    VOS_UINT8                           ucMsgType;                                               /* 空口消息得类型                           */
    VOS_UINT8                           ucModeFlg;

    pRcvMsg = (TCGMM_DATA_IND_STRU *)(pMsg);                                             /* 结构体类型转换                           */
    if( 2 > pRcvMsg->RcvTcMsg.ulTcMsgSize )
    {                                                                                   /* 消息过短                                 */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGmmDataInd:WARNING:2 > pRcvMsg->RcvTcMsg.ulTcMsgSize");
        return;
    }
    if(( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&
       ( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0)))
    {                                                                                   /* PD为f和SI为0，可以分发处理               */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGmmDataInd:WARNING:( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0))");
        return;
    }

    pRcvTcMsg = pRcvMsg->RcvTcMsg.aucTcMsg;                                             /* 取得消息内容地址                         */
    ucMsgType = pRcvTcMsg[1];                                                           /* 取得空口消息得类型                       */
    g_TcInfo.ucCnDomain = TC_CN_DOMAIN_PS;                                              /* 记录消息在PS信令上传输                   */
    switch(ucMsgType)
    {                                                                                   /* 按照消息类型进行分发                     */
    case TC_CLOSE_UE_TEST_LOOP:
        Tc_RcvCloseLoop(pRcvTcMsg);                                                     /* 处理TC_CLOSE_UE_TEST_LOOP消息            */
        break;
    case TC_OPEN_UE_TEST_LOOP:
        Tc_RcvOpenLoop();                                                               /* 处理TC_OPEN_UE_TEST_LOOP消息             */
        break;
    case TC_ACT_RB_TEST_MODE:
        Tc_RcvActRbTest();                                                              /* 处理TC_ACT_RB_TEST_MODE消息              */
        break;
    case TC_DEACT_RB_TEST_MODE:
        Tc_RcvDeactRbTest();                                                            /* 处理TC_DEACT_RB_TEST_MODE消息            */
        break;
    case TC_RESET_UE_POS_STORED_INFO:
        Tc_RcvResetUePosStoredInfo(pRcvTcMsg);
        break;
    case TC_GPRS_TEST_MODE_CMD:
        Tc_RcvGprsTestModeCmd(pRcvTcMsg);
        break;
    case TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD:
        ucModeFlg = pRcvTcMsg[2];
        Tc_RcvEgprsLoopBackCmd(ucModeFlg);
        break;
    default:
        break;
    }
    return;
}

/*******************************************************************************
 *  Module   : Tc_TaskInit
 *  Function : TC TASK模块初始化函数
 *  Input    : VOS_VOID
 *  Output   : VOS_VOID
 *  NOTE     :
 *  Return   : VOS_VOID
 *  History  :
      1.   张志勇      2004.05.24   新规作成
      2.   L47619   2006.02.17   问题单:A32D02126
*******************************************************************************/
VOS_VOID Tc_TaskInit()
{
    PS_NAS_MEM_SET(&g_TcInfo,0,sizeof(TC_GLOBAL_CTRL_STRU));                               /* 初始化全局变量                           */

    g_TcInfo.ucMsgType     = TC_MSG_INVALID;
    g_TcInfo.usTchLoopType = TC_TCH_LOOP_TYPE_ABNORMAL;

}


/* 050205 huxuef Add for Pid消息分发函数 begin */
/*******************************************************************************
  Module:   Tc_TaskEntry
  Function: TC Pid提供为FID的消息处理函数
  Input:    struct MsgCB * pMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇      2005.02.05   新规作成
      2.   L47619   2006.02.21   问题单:A32D02126
      3.  日    期   : 2011年10月11日
          作    者   : l00171473
          修改内容   : V7R1 phase II, TC环回调整，维护PS TC业务存在标志
*******************************************************************************/
VOS_VOID Tc_TaskEntry (struct MsgCB * pRcvMsg)
{
    MSG_HEADER_STRU*        pMsgHeader;

    if ( VOS_NULL_PTR == pRcvMsg )
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_TaskEntry:WARNING:The Entry Pointer is NULL!");
        return;
    }

    if ( DSP_PID_GPHY == pRcvMsg->ulSenderPid )
    {
        Tc_RcvHpaMsgHandle(pRcvMsg);
        return;
    }

    if ( UEPS_PID_GRM == pRcvMsg->ulSenderPid )
    {
        Tc_RcvGrmMsgHandle(pRcvMsg);
        return;
    }

    pMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch( pMsgHeader->ulMsgName )
    {                                                                       /* 对MM消息进行分发                         */
    case TCMM_DATA_IND:
        Tc_RcvMmDataInd(pRcvMsg);                                           /* 消息分发处理                             */
        break;

    case TCGMM_DATA_IND:
        Tc_RcvGmmDataInd(pRcvMsg);                                          /* 消息分发处理                             */
        break;

    case TCMM_RR_REL_IND:
        NAS_TC_RcvMmRelInd(pRcvMsg);
        break;

    case TCGMM_RR_REL_IND:
        NAS_TC_RcvGmmRelInd(pRcvMsg);
        break;

    case TCRABM_TEST_CNF:
        Tc_RcvRabmTestCnf(pRcvMsg);                                         /* 消息分发处理                             */
        break;

    case TCRABM_TEST_LOOP_CNF:
        Tc_RcvRabmTestLoopCnf();                                            /* RABM消息分发处理                         */
        break;

    case TCRABM_RAB_IND:
        Tc_RcvRabmRabInd(pRcvMsg);                                          /* RABM消息分发处理                         */
        break;

    case TCGMM_HANDOVER_IND:
        NAS_TC_RcvGmmHandoverInd(pRcvMsg);
        break;

    default:
        break;
    }
}

/******************************************************************************
 * 函数名称 ： WuepsTcPidInit
 * 功能描述 ： WUEPS TC PID的初始化函数
 * 参数说明 ： 无
 * 备    注 ：
 * 返 回 值 ： VOS_UINT32 初始化结果：
 *             0  : 成功
 *             非0: 失败
 *
 * 变更历史 ：
 *           No.  姓名      变更                                    日   期
 *           1    张志勇    新建                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsTcPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
        Tc_TaskInit();                                                      /* TC TASK初始化                            */
        break;
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}


/*****************************************************************************
Function            : Tc_GetState()
Description         : 此接口提供TC当前状态
Calls               : VOS_VOID
Called By           :
Input               : VOS_VOID
Output              : VOS_VOID
Return Value        : TC_NORMAL_MODE                TC的通常状态，此时RB测试没有激活
                      TC_OPEN_TEST_LOOP             TC的开环状态，此时RB测试已经激活，
                                                    回环测试还没有进行
                      TC_CLOSE_TEST_LOOP            TC的闭环状态，此时RB测试已经激活，
                                                    回环测试正在进行
                      TC_ABNORMAL_STATE             TC状态异常
Others              :
*****************************************************************************/
VOS_UINT32  Tc_GetState(VOS_VOID)
{
    if ( g_TcInfo.ucTcState <= TC_CLOSE_TEST_LOOP )
    {
        return g_TcInfo.ucTcState;
    }
    else
    {
        return TC_ABNORMAL_STATE;
    }

}


/*****************************************************************************
Function            : Tc_GetMode()
Description         : 此接口提供TC当前的环回模式
Calls               : VOS_VOID
Called By           :
Input               : VOS_VOID
Output              : VOS_VOID
Return Value        : TC_MODE_1               环回模式1
                      TC_MODE_2               环回模式2
Creat               : L47619      2006-01-12
*****************************************************************************/
VOS_UINT32  Tc_GetMode(VOS_VOID)
{
    return g_TcInfo.TcModeInfo.ucTcMode;
}



/*****************************************************************************
 函 数 名  : NAS_TC_RcvMmRelInd
 功能描述  : 收到MM上报的连接释放信息，根据TC的状态进行处理
 输入参数  : struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月14日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2015年5月15日
   作    者   : wx270776
   修改内容   : TAS环回测试可维可测

*****************************************************************************/
VOS_VOID NAS_TC_RcvMmRelInd(
    struct MsgCB                       *pstMsg
)
{
    /* 如果RRC连接存在标志已不存在，表示已收到过REL IND，则直接返回 */
    if (TC_RRC_CONN_STATUS_ABSENT == g_TcInfo.ucRrcConnStatus)
    {
        return;
    }

    /* 清除RRC连接存在标志 */
    g_TcInfo.ucRrcConnStatus = TC_RRC_CONN_STATUS_ABSENT;

    /* 根据当前的状态进行分发 */
    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
          /* 此状态下收到MMC_REL_IND,表明经历了W2G流程
             (W2G时，RABM收到suspend IND，会调用Tc_TaskInit将TC初始化)。
             此状态下的处理与如下状态一致，无需break */
        case TC_OPEN_TEST_LOOP:
        case TC_CLOSE_TEST_LOOP:
            if(TC_DEACT_RB_TEST_MODE != g_TcInfo.ucMsgType)
            {                                                                   /* 如果正在处理去激活消息不处理，否则，通知 *
                                                                                 * NAS其它TASK去激活                        */
                Tc_SndRabmTestReq(TC_RB_TEST_DEACTIVE);                         /* 通知RABM去激活                           */
                Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                           /* 通知MM去激活                             */
                Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                          /* 通知GMM去激活                            */
            }

            /* 通知MTC环回测试停止 */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        case TC_GSM_CLOSE_TCH_LOOP:
        case TC_GPRS_CLOSE_TCH_LOOP:
            /* 通知MTC环回测试停止 */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        default:
            break;
    }

    g_TcInfo.ucMsgType = TC_MSG_INVALID;                                        /* 清除正在处理的消息类型                   */
    return;
}

/*****************************************************************************
 函 数 名  : NAS_TC_RcvGmmRelInd
 功能描述  : 收到GMM上报的连接释放消息，根据TC的状态进行处理
 输入参数  : struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月14日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2012年4月12日
   作    者   : A00165503
   修改内容   : DTS2012041202517: CS域环回, PS域连接释放, TC直接进入去激活
                状态, 导致环回失败

 3.日    期   : 2015年5月15日
   作    者   : wx270776
   修改内容   : TAS环回测试可维可测

*****************************************************************************/
VOS_VOID NAS_TC_RcvGmmRelInd(
    struct MsgCB                       *pstMsg
)
{
    /* 如果RRC连接存在标志已不存在，表示已收到过REL IND，则直接返回 */
    if(TC_RRC_CONN_STATUS_ABSENT == g_TcInfo.ucRrcConnStatus)
    {
        return;
    }

    /* 如果是CS环回, 不处理PS连接释放 */
    if (TC_CN_DOMAIN_CS == g_TcInfo.ucCnDomain)
    {
        return;
    }

    /* 清除RRC连接存在标志 */
    g_TcInfo.ucRrcConnStatus = TC_RRC_CONN_STATUS_ABSENT;

    /* 根据当前的状态进行分发 */
    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
          /* 此状态下收到MMC_REL_IND,表明经历了W2G流程
             (W2G时，RABM收到suspend IND，会调用Tc_TaskInit将TC初始化)。
             此状态下的处理与如下状态一致，无需break */
        case TC_OPEN_TEST_LOOP:
        case TC_CLOSE_TEST_LOOP:
            if(TC_DEACT_RB_TEST_MODE != g_TcInfo.ucMsgType)
            {                                                                   /* 如果正在处理去激活消息不处理，否则，通知 *
                                                                                 * NAS其它TASK去激活                        */
                Tc_SndRabmTestReq(TC_RB_TEST_DEACTIVE);                         /* 通知RABM去激活                           */
                Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                           /* 通知MM去激活                             */
                Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                          /* 通知GMM去激活                            */
            }

            /* 通知MTC环回测试停止 */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        case TC_GSM_CLOSE_TCH_LOOP:
        case TC_GPRS_CLOSE_TCH_LOOP:
            /* 通知MTC环回测试停止 */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        default:
            break;
    }

    g_TcInfo.ucMsgType = TC_MSG_INVALID;                                        /* 清除正在处理的消息类型                   */
    return;
}

/*****************************************************************************
 函 数 名  : NAS_TC_RcvGmmHandoverInd
 功能描述  : 收到GMM上报的异系统切换消息，根据TC的状态进行处理
 输入参数  : struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月14日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_TC_RcvGmmHandoverInd(
    struct MsgCB                       *pstMsg
)
{
    TCGMM_HANDOVER_IND_STRU            *pstHandoverMsg = VOS_NULL_PTR;
    TC_TEST_MODE_W_TO_G_IND_STRU        stTcTestModeWToGInd;

    pstHandoverMsg = (TCGMM_HANDOVER_IND_STRU*)pstMsg;

    if (NAS_MML_NET_RAT_TYPE_GSM == pstHandoverMsg->enNetRat)
    {
        /* 向物理层发送指示: */
        stTcTestModeWToGInd.usMsgID = TC_TEST_MODE_W_TO_G_IND;

        if ( VOS_OK != Tc_SndPhyMsg(TC_TEST_MODE_W_TO_G_IND, (VOS_UCHAR *)(&stTcTestModeWToGInd)) )
        {
            NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_RcvGmmHandoverInd:ERROR:Send TC_TEST_MODE_W_TO_G_IND fail!");
        }
    }
    /* 根据DSP需求，切换到W下通知WPHY进入环回 */
    else if ((NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == pstHandoverMsg->enNetRat))
    {
        NAS_TC_SndWphyCloseLoopNtf();
    }
    else
    {

    }
    return;
}


/*****************************************************************************
 函 数 名  : NAS_TC_SndWphyCloseLoopNtf
 功能描述  : 给WPHY发送消息通知进入换回模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月17日
   作    者   : z60575
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_TC_SndWphyCloseLoopNtf(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    TC_WPHY_CLOSE_LOOP_NTF_STRU        *pstMsg;

    /* 申请TC_WPHY_CLOSE_LOOP_NTF_STRU消息 */
    ulLength    = sizeof(TC_WPHY_CLOSE_LOOP_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (TC_WPHY_CLOSE_LOOP_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Alloc Message Fail");

        return;
    }

    PS_MEM_SET(pstMsg,0x00,sizeof(TC_WPHY_CLOSE_LOOP_NTF_STRU));

    /* 填写消息头 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_WPHY;
    pstMsg->ulLength        = ulLength;

    /* 填写消息体 */
    pstMsg->usMsgId         = ID_TC_WPHY_CLOSE_LOOP_NTF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Send Message Fail");

        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_TC_SndWphyOpenLoopNtf
 功能描述  : 给WPHY发送消息通知退出入换回模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月17日
   作    者   : z60575
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_TC_SndWphyOpenLoopNtf(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    TC_WPHY_OPEN_LOOP_NTF_STRU         *pstMsg;

    /* 申请TC_WPHY_CLOSE_LOOP_NTF_STRU消息 */
    ulLength    = sizeof(TC_WPHY_OPEN_LOOP_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (TC_WPHY_OPEN_LOOP_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Alloc Message Fail");

        return;
    }

    PS_MEM_SET(pstMsg,0x00,sizeof(TC_WPHY_OPEN_LOOP_NTF_STRU));

    /* 填写消息头 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_WPHY;
    pstMsg->ulLength        = ulLength;

    /* 填写消息体 */
    pstMsg->usMsgId         = ID_TC_WPHY_OPEN_LOOP_NTF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Send Message Fail");

        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_TC_SndMtcStatusInfoInd
 功能描述  : 给MTC发送消息通知TC环回测试状态信息
 输入参数  : MTC_NAS_TC_STATUS_ENUM_UINT16    enTcStatus  TC环回状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月5日
   作    者   : wx270776
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_TC_SndMtcStatusInfoInd(
    MTC_NAS_TC_STATUS_ENUM_UINT16       enTcStatus
)
{

    VOS_UINT32                          ulMsgLength;
    NAS_MTC_TC_STATUS_INFO_IND_STRU    *pstNasSndMtcMsg = VOS_NULL_PTR;

    /* 申请MTC_NAS_TC_STATUS_INFO_IND_STRU消息 */
    ulMsgLength      = sizeof(NAS_MTC_TC_STATUS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstNasSndMtcMsg  = (NAS_MTC_TC_STATUS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);

    if (VOS_NULL_PTR == pstNasSndMtcMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndMtcStatusInfoInd, Alloc Message Fail");
        return;
    }

    PS_MEM_SET(pstNasSndMtcMsg, 0x00, sizeof(NAS_MTC_TC_STATUS_INFO_IND_STRU));

    /* 填写消息头 */
    pstNasSndMtcMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNasSndMtcMsg->ulSenderPid      = WUEPS_PID_TC;
    pstNasSndMtcMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNasSndMtcMsg->ulReceiverPid    = UEPS_PID_MTC;
    pstNasSndMtcMsg->ulLength         = ulMsgLength;

    /* 填写消息体 */
    pstNasSndMtcMsg->ulMsgName        = ID_NAS_MTC_TC_STATUS_INFO_IND;
    pstNasSndMtcMsg->enRatMode        = NAS_TC_GetNetRatMode();
    pstNasSndMtcMsg->enTcStatus       = enTcStatus;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstNasSndMtcMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndMtcStatusInfoInd, Send Message Fail");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_TC_GetNetRatMode
 功能描述  : 获取当前接入技术
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : MTC_NAS_RAT_MODE_ENUM_UINT16  通知MTC当前接入技术
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月5日
   作    者   : wx270776
   修改内容   : 新生成函数

*****************************************************************************/
MTC_NAS_RAT_MODE_ENUM_UINT16 NAS_TC_GetNetRatMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurUtrMod;
    MTC_NAS_RAT_MODE_ENUM_UINT16        enSndMtcNetRatMode;

    enCurNetRat                       = NAS_MML_GetCurrNetRatType();
    enCurUtrMod                       = NAS_UTRANCTRL_GetCurrUtranMode();
    enSndMtcNetRatMode                = MTC_NAS_RAT_MODE_BUTT;

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurNetRat)
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_GSM;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_WCDMA;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_TDSCDMA;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_LTE     == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_LTE;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_LTE     == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_CDMA;
    }
    else
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_BUTT;
    }

    return enSndMtcNetRatMode;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
