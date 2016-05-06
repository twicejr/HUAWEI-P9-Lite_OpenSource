/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasSend.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : 该C文件给出了GmmCasSend模块的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 根据问题单A32D02368修改
  3. l40632 2006-04-17 根据问题单A32D03141修改
  4. l40632 2006-04-27 根据问题单A32D03429修改
  5. x51137 2006/4/28 A32D02889
  6. l40632 2006-05-29 根据问题单A32D03821修改
  7. l40632 2006-06-19 根据问题单A32D04282修改
  8. l40632 2006-07-12 根据问题单A32D03834修改
  9.Date        : 2006-09-19
    Author      : s46746
    Modification: 问题单号:A32D06255
 10.Date        : 2006-10-19
    Author      : L47619
    Modification: 问题单号:A32D06916
 11.日    期   : 2006年02月16日
    作    者   : luojian 60022475
    修改内容   : 问题单号:A32D08391
 12.日    期   : 2007年05月25日
    作    者   : luojian 60022475
    修改内容   : 根据问题单号:A32D11232
 13.日    期   : 2007年09月10日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D12829
 14.日    期   : 2007年9月27日
    作    者   : s46746
    修改内容   : 将卡无效信息从RRMM_NAS_INFO_CHANGE消息中拿掉
 15.日    期   : 2007-10-26
    作    者   : hanlufeng
    修改内容   : A32D13172
 20.日    期   : 2007年12月04日
    作    者   : s46746
    修改内容   : 1.GMM模块进行ATTACH和RAU时，如果此时接入层进行临区任务，
                   会导致LLC将ATTACH和RAU延迟发送，使得ATTACH和RAU时间过长；
                 2.GMM在进行RAU请求时，如果DRX参数不改变，将不会在消息中
                   带DRX参数，这样跨SGSN的RAU时，可能导致网侧不识别UE的DR
                   X参数，  使得RAU不能成功。
 21.日    期   : 2007年12月14日
    作    者   : s46746
    修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
 22.日    期   : 2008年8月18日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05016，修改CGREG的状态判断
 23.日    期   : 2008年9月10日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05403，修改CGREG的状态
 24.日    期   : 2008年10月21日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D06285，添加对状态GMM_REGISTERED_NO_CELL_AVAILABLECGREG的判断
 25.日    期   : 2008年12月02日
    作    者   : x00115505
    修改内容   : AT2D06945:CREG、CGREG主动上报修改
 26.日    期   : 2009年02月28日
    作    者   : o00132663
    修改内容   : AT2D09507, 在丢网时，CREG,CGREG上报2:没有注册，但MT正在搜寻要注册的新的运营商。
 27.日    期   : 2009年04月11日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D10976/AT2D10989,gstGmmCasGlobalCtrl.ulReadyTimerValue时长为0xffffffff,导致单板复位
 28.日    期   : 2009年6月30日
    作    者   : s46746
    修改内容   : AT2D12561,3G2情形GPRS下未启动加密，NAS指派层2加密算法后，层2对上行数据进行了加密
 29.日    期   : 2009年10月27日
    作    者   : x00115505
    修改内容   : AT2D15257:CS detach过程中，PS注册状态改变
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasUtranCtrlInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "NasGmmProcLResult.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASSEND_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/
/*VOS_UINT8               gaucGmmNasMsgTmp[GMM_NAS_MSG_DATA_MAX];*/                 /* 传递NAS消息的临时数据区 */
/*VOS_UINT8               gaucGmmLlcDataReq[GMM_LLC_MSG_PDULEN_MAX];*/              /* 向LLC发送data req的消息数据内容 */

/* DRX参数中Split pg cycle code对应表 */
static VOS_UINT16       gausGmmDrxCycleCodeTab[GMM_DRX_CYCLE_CODE_TAB_MAX] =
{
    71,             /*code as 65*/
    72,             /*code as 66*/
    74,
    75,
    77,
    79,
    80,
    83,
    86,
    88,
    90,
    92,
    96,
    101,
    103,
    107,
    112,
    116,
    118,
    128,
    141,
    144,
    150,
    160,
    171,
    176,
    192,
    214,
    224,
    235,
    256,
    288,
    320,
    352             /*code as 98*/
};


/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM 发送消息处理       -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_SndLlcDataReq
 Description    : 向TTF组模块发送LL_UNITDATA_REQ_MSG消息
                  HSS 4100 V200R001 新增
 Input          : NAS_MSG_STRU            *pstNasL3Msg,     NAS LAYER3消息指针
                  LL_NAS_UNITDATA_REQ_ST  *pstUnitDataReq   LL_NAS_UNITDATA_REQ消息内容指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2006年02月16日
    作    者   : luojian 60022475
    修改内容   : 问题单号:A32D08391
  3.日    期   : 2009年04月11日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D10976/AT2D10989,gstGmmCasGlobalCtrl.ulReadyTimerValue时长为0xffffffff,导致单板复位
  4.日    期   : 2011年04月20日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2011040804149，【V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
  5.日    期   : 2015年4月7日
    作    者   : wx270776
    修改内容   : 问题单号:DTS2015040701865，天际通关机优化，增加消息内容
*****************************************************************************/
VOS_VOID GMM_SndLlcDataReq (
    NAS_MSG_STRU                       *pstNasL3Msg,
    LL_NAS_UNITDATA_REQ_ST             *pstUnitDataReq
)
{
    /* 发送消息内容变量 */
    LL_NAS_UNITDATA_REQ_MSG            *pstDataReqMsg = VOS_NULL_PTR;       /* 待发送的消息指针 */
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulRet;

    /* 消息指针有效性判断 */
    if ( (VOS_NULL == pstNasL3Msg)
      || (VOS_NULL == pstUnitDataReq) )
    {
        /* 无效指针则打印错误信息 */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndLlcDataReq():Error: Invaild pointer");

        return;
    }
    
    ulMsgLen = sizeof(LL_NAS_UNITDATA_REQ_MSG);
    
    /* 当LAYER3 NAS消息长度小于4字节，则保留4字节长度，否则取消息实际长度 */
    if ( (pstNasL3Msg->ulNasMsgSize) > sizeof(pstUnitDataReq->aucPdu) )
    {
        ulMsgLen = sizeof(LL_NAS_UNITDATA_REQ_MSG) + (pstNasL3Msg->ulNasMsgSize - sizeof(pstUnitDataReq->aucPdu)); 
    }

    /* 创建发送消息 */
    pstDataReqMsg = (LL_NAS_UNITDATA_REQ_MSG *)PS_ALLOC_MSG( WUEPS_PID_GMM, ulMsgLen - VOS_MSG_HEAD_LENGTH );
    if (VOS_NULL_PTR == pstDataReqMsg)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_SndLlcDataReq():Error: Failed in VOS_AllocMsg()");
        return;
    }
    
    /* DOPRA消息头固定的参数 */
    pstDataReqMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstDataReqMsg->ulReceiverPid        = UEPS_PID_LL;

    /* 填写消息发送参数 */
    pstDataReqMsg->usMsgType            = ID_LL_UNITDATA_REQ;           /* LL_UNITDATA_REQ 消息ID */
    pstDataReqMsg->usTransId            = GMM_LLC_TRANSID;              /* 子进程，这里填SAPI, GMM使用1 */

    /* 拷贝通知给LL的消息 */
    Gmm_MemCpy( &(pstDataReqMsg->stUnitDataReq),
                pstUnitDataReq,
                (sizeof(LL_NAS_UNITDATA_REQ_ST) - sizeof(pstUnitDataReq->aucPdu)) );

    /* 拷贝LAYER3 NAS消息 */
    Gmm_MemCpy( pstDataReqMsg->stUnitDataReq.aucPdu,
                pstNasL3Msg->aucNasMsg,
                pstNasL3Msg->ulNasMsgSize );

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstDataReqMsg);
    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndLlcDataReq():Error: Failed in VOS_SendMsg()");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 创建LL_GMM_ASSIGN_REQ_MSG消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
LL_GMM_ASSIGN_REQ_MSG *GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI ucAssignFlg)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg = VOS_NULL_PTR;

    pAssignReqMsg = (LL_GMM_ASSIGN_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                        sizeof(LL_GMM_ASSIGN_REQ_MSG) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_MakeLlgmmAssignReqMsg():Error: Failed in VOS_AllocMsg()");
        return pAssignReqMsg;
    }

    pAssignReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pAssignReqMsg->ulReceiverPid   = UEPS_PID_LL;

    /* 填写消息内容 */
    pAssignReqMsg->usMsgType = ID_LL_GMM_ASSIGN_REQ;
    pAssignReqMsg->usTransId = GMM_LLC_TRANSID;

    /* TLLI的操作类型 */
    switch (ucAssignFlg)
    {
        case GMM_OP_TLLI_ASSIGN:        /* 指配new TLLI */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLI指配有效标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* new TLLI值参数 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            0xffffffff;                     /* 新指配标志的参数 */
            break;

        case GMM_OP_TLLI_MODIFY:        /* 修改new and old TLLI，在完成new TLLI指配后 */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLI指配有效标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* new TLLI值参数 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            gstGmmCasGlobalCtrl.ulOldTLLI;  /* old TLLI值参数 */
            break;

        case GMM_OP_TLLI_UNASSIGN:      /* 去指配old TLLI，当前存在有效old TLLI的条件下 */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLI指配有效标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* 去指配标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            0xffffffff;                     /* 去指配标志的参数 */
            break;

        case GMM_OP_TLLI_UNASSIGN_SYS:  /* 去指配默认TLLI和old TLLI */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLI指配有效标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            0xffffffff;                     /* 去指配标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* 不能是0xffffffff */
            break;

        case GMM_OP_TLLI_SYNC:          /* 同步LLC的TLLI */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLI指配有效标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* 当前默认TLLI */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            0xffffffff;
            break;

        case GMM_OP_TLLI_KC:            /* 指配Kc和加密算法 */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_CiphAlg;     /* 加密算法指配有效标志 */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* 当前默认TLLI */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            gstGmmCasGlobalCtrl.ulOldTLLI;  /* 默认old TLLI */
            break;

        default:
            break;
    }

    /* 填写加密算法参数 */
    pAssignReqMsg->stLlGmmAssReq.ucCiphAlg =
                        gstGmmCasGlobalCtrl.ucGprsCipherAlg;

    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        pAssignReqMsg->stLlGmmAssReq.enCiphStartFlg = LL_GMM_CIPH_START;
    }
    else
    {
        pAssignReqMsg->stLlGmmAssReq.enCiphStartFlg = LL_GMM_CIPH_STOP;
    }

    /* 填写Kc参数 */
    Gmm_MemCpy(pAssignReqMsg->stLlGmmAssReq.aucKc,
                        NAS_MML_GetSimPsSecurityGsmKc(),
                        8);
    /* 填写RAND参数 */
    Gmm_MemCpy(pAssignReqMsg->stLlGmmAssReq.ucRand,
                        g_GmmAuthenCtrl.aucRandSav,
                        16);

    return pAssignReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : 创建LL_GMM_TRIGGER_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-06
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
LL_GMM_TRIGGER_REQ_MSG *GMM_MakeLlgmmTriggerReqMsg(VOS_UINT8 ucCause)
{
    LL_GMM_TRIGGER_REQ_MSG   *pTriggerReqMsg = VOS_NULL_PTR;

    pTriggerReqMsg = (LL_GMM_TRIGGER_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                        sizeof(LL_GMM_TRIGGER_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pTriggerReqMsg)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_MakeLlgmmTriggerReqMsg():Error: Failed in VOS_AllocMsg()");
        return pTriggerReqMsg;
    }


    pTriggerReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTriggerReqMsg->ulReceiverPid   = UEPS_PID_LL;
    pTriggerReqMsg->usMsgType = ID_LL_GMM_TRIGGER_REQ;

    /* 填写消息内容 */
    pTriggerReqMsg->stLlGmmTrigReq.ulTlli  = gstGmmCasGlobalCtrl.ulTLLI;
    pTriggerReqMsg->stLlGmmTrigReq.ucCause = ucCause;
    pTriggerReqMsg->stLlGmmTrigReq.ucRsv   = 0;

    return pTriggerReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : 创建LL_GMM_SUSPEND_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-06
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2010年9月09日
    作    者   : l65478
    修改内容   : DTS2010090302562,PDP激活过程中发生重选，PDP激活事件比标杆慢
*****************************************************************************/
LL_GMM_SUSPEND_REQ_MSG *GMM_MakeLlgmmSuspendReqMsg(VOS_VOID)
{
    LL_GMM_SUSPEND_REQ_MSG   *pSuspendReqMsg = VOS_NULL_PTR;

    pSuspendReqMsg = (LL_GMM_SUSPEND_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(LL_GMM_SUSPEND_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pSuspendReqMsg)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_MakeLlgmmSuspendReqMsg():Error: Failed in VOS_AllocMsg()");
        return pSuspendReqMsg;
    }


    pSuspendReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSuspendReqMsg->ulReceiverPid   = UEPS_PID_LL;
    pSuspendReqMsg->usMsgType = ID_LL_GMM_SUSPEND_REQ;

    /* 填写消息内容 */
    pSuspendReqMsg->aucReserve[0] = 0;
    pSuspendReqMsg->aucReserve[1] = 0;
    pSuspendReqMsg->aucReserve[2] = 0;
    pSuspendReqMsg->aucReserve[3] = 0;

    return pSuspendReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : 创建LL_GMM_RESUME_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-06
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2010年9月09日
    作    者   : l65478
    修改内容   : DTS2010090302562,PDP激活过程中发生重选，PDP激活事件比标杆慢
*****************************************************************************/
LL_GMM_RESUME_REQ_MSG *GMM_MakeLlgmmResumeReqMsg(VOS_UINT32  ulResumeType)
{
    LL_GMM_RESUME_REQ_MSG   *pResumeReqMsg = VOS_NULL_PTR;

    pResumeReqMsg = (LL_GMM_RESUME_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(LL_GMM_RESUME_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pResumeReqMsg)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_MakeLlgmmResumeReqMsg():Error: Failed in VOS_AllocMsg()");
        return pResumeReqMsg;
    }


    pResumeReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pResumeReqMsg->ulReceiverPid   = UEPS_PID_LL;
    pResumeReqMsg->usMsgType = ID_LL_GMM_RESUME_REQ;

    /* 填写消息内容 */
    pResumeReqMsg->ulResumeType = ulResumeType;

    return pResumeReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : 创建GRRGMM_ASSIGN_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
GRRGMM_ASSIGN_REQ_ST *GMM_MakeGrrmmAssignReqMsg(VOS_UINT32 ulCause)
{
    GRRGMM_ASSIGN_REQ_ST    *pReqMsg;

    pReqMsg = (GRRGMM_ASSIGN_REQ_ST*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                        sizeof(GRRGMM_ASSIGN_REQ_ST) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pReqMsg)
    {
        GMM_LOG_ERR("GMM_MakeGrrmmAssignReqMsg():Error: Failed in VOS_AllocMsg()");
        return pReqMsg;
    }

    pReqMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pReqMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pReqMsg->MsgHeader.ulMsgName  = GRRGMM_ASSIGN_REQ;

    /* 填写消息内容 */
    pReqMsg->ulTlli     = gstGmmCasGlobalCtrl.ulTLLI;
    pReqMsg->ulOldTlli  = gstGmmCasGlobalCtrl.ulOldTLLI;

    pReqMsg->ulTlliCause = ulCause;

    return pReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : 在2G时构造假的RR连接建立成功消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_SndRrmmEstCnfGsm(VOS_UINT8 ucRrmmEstOpid)
{
    RRMM_EST_CNF_STRU     *pRrEstCnf;
    VOS_UINT32             ulRet;

    pRrEstCnf = (RRMM_EST_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                    sizeof(RRMM_EST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pRrEstCnf)
    {
        /*打印错误信息*/
        GMM_LOG_ERR("GMM_SndRrmmEstReqGsm():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* 填写EST CNF消息内容 */
    pRrEstCnf->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pRrEstCnf->MsgHeader.ulSenderPid     = WUEPS_PID_WRR;  /* 模拟WRRC发送 */
    pRrEstCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pRrEstCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;   /* GMM接收 */

    pRrEstCnf->MsgHeader.ulMsgName   = RRMM_EST_CNF;        /* 模拟发送消息名称 */

    pRrEstCnf->ulCnDomainId = RRC_NAS_PS_DOMAIN;
    pRrEstCnf->ulOpId       = ucRrmmEstOpid;
    pRrEstCnf->ulResult     = RRC_EST_SUCCESS;

    /* 2G网络下，发送EST CNF到GMM消息队列 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pRrEstCnf);
    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_SndRrmmEstReqGsm():Error: Failed in VOS_SendMsg()");
        return;
    }
    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 在2G时构造假的RR连接建立成功消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2006-09-19
    Author      : s46746
    Modification: 问题单号:A32D06255
*****************************************************************************/
VOS_VOID GMM_SndRrmmEstReqGsm(VOS_UINT8 ucRrmmEstOpid, NAS_MSG_STRU *pMsg)
{
    /*S_UINT8              ucCiphInd;*/
    /*VOS_UINT32             ulRet;*/
    GMM_SndRrmmEstCnfGsm(ucRrmmEstOpid);

#if 0
    /* 将RRMM_EST_REQ中的NAS消息内容发给LLC */
    if ( (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
       /*||(GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)*/
       ||(0x20 == (g_GmmGlobalCtrl.ucState & 0xF0)) )
    {
        if (0 == gstGmmCasGlobalCtrl.ucGprsCipherAlg)
        {
            ucCiphInd = 0; /*0-LLC不加密*/
        }
        else
        {
            ucCiphInd = 1; /*1-LLC加密*/
        }
    }
    else
    {
        ucCiphInd = 0; /*0-LLC不加密*/
    }

    /* 向LLC发送消息 */
    GMM_SndLlcDataReq(LL_RADIO_PRI_1,/*RRC_NAS_MSG_PRIORTY_HIGH,*/ /* 见3G的函数接口使用 */
                      ucCiphInd,
                      (VOS_UINT16)pMsg->ulNasMsgSize,
                      pMsg->aucNasMsg);
#endif

    GMM_SndRrmmDataReqGsm(pMsg);

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 在2G时构造假的RR连接释放消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2007-10-26
    Author      : hanlufeng
    Modification: A32D13172
*****************************************************************************/
VOS_VOID GMM_SndRrmmRelReqGsm()
{
    RRMM_REL_IND_STRU                   RrRelInd;

    /* 填写EST CNF消息内容 */
    RrRelInd.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulSenderPid      = WUEPS_PID_WRR;  /* 模拟WRRC发送 */
    RrRelInd.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverPid    = WUEPS_PID_GMM;   /* GMM接收 */

    RrRelInd.MsgHeader.ulMsgName        = RRMM_REL_IND;    /* 模拟发送消息名称 */

    RrRelInd.ulCnDomainId               = RRC_NAS_PS_DOMAIN;
    RrRelInd.ulRrcConnStatus            = RRC_RRC_CONN_STATUS_ABSENT;
    RrRelInd.ulRelCause                 = RRC_REL_CAUSE_RR_NORM_EVENT;

    /*直接调用GMM处理消息RRMM_REL_IND的函数*/
    Gmm_RcvRrmmRelInd(&RrRelInd);

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 在2G时向LLC发信令数据消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2006-09-19
    Author      : s46746
    Modification: 问题单号:A32D06255
  3.日    期    : 2009年03月18日
    作    者    : l65478
    修改内容    : 根据问题单号：AT2D08671,数传状态下，W出服务区后，切到G，数传恢复失败，因为GMM没有配置LL加密算法
  4.日    期    : 2015年4月9日
    作    者    : wx270776
    修改内容    : 问题单号:DTS2015040701865，天际通关机优化，增加判断是否携带enNeedCnf标志。
                  在携带后，LL将gmm的消息发送到网测后，会通知给GMM.这样在关机时候，
                  PS域DETACH消息发送到网络侧后，LL通知给GMM后，GMM可以认为PS域DETACH
                  完成，给MMC回复关机结果，加快关机速度。
*****************************************************************************/
VOS_VOID GMM_SndRrmmDataReqGsm(
    NAS_MSG_STRU                       *pMsg
)
{
    VOS_UINT8                           ucCiphInd;
    PS_BOOL_ENUM_UINT8                  enNeedCnf;
    VOS_UINT16                          usMui;     
    LL_NAS_UNITDATA_REQ_ST              stUnitDataReq;

    /* 获取加密方式 */
    ucCiphInd       = NAS_GMM_GetCiphInd(pMsg);    
    enNeedCnf       = VOS_FALSE;
    usMui           = 0;
    PS_MEM_SET(&stUnitDataReq, 0x00, sizeof(LL_NAS_UNITDATA_REQ_ST));

    if(0 != gstGmmCasGlobalCtrl.ucGprsCipherAlg)
    {
        if(VOS_FALSE == gstGmmCasGlobalCtrl.ucGprsCipherAssign)
        {
            GMM_AssignGsmKc();
        }
    }

    /* GSM下，在关机PS域DETACH时候，需要携带NeedCnf标志 */
    if (VOS_TRUE == NAS_GMM_IsPowerOffPsDetachMsg(pMsg))
    {
        (VOS_VOID)NAS_GMM_IncreaseMui();
        enNeedCnf   = VOS_TRUE;                
        usMui       = NAS_GMM_GetMui();
        NAS_GMM_SetPowerOffDetachPsMui(usMui);
    }

    /* 填充消息结构体 */
    stUnitDataReq.ulTlli              = gstGmmCasGlobalCtrl.ulTLLI;
    stUnitDataReq.ucRadioPri          = LL_RADIO_PRI_1;
    stUnitDataReq.ucCiphInd           = ucCiphInd;
    stUnitDataReq.enNeedCnf           = enNeedCnf;
    stUnitDataReq.usMui               = usMui;
    stUnitDataReq.usPduLen            = (VOS_UINT16)pMsg->ulNasMsgSize;

    /* 发送DATA REQ消息到LLC */
    GMM_SndLlcDataReq(pMsg, &stUnitDataReq);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetAttachStatus
 功能描述  : 获取GMM的注册状态
 输入参数  : 无
 输出参数  : RRC_NAS_ATTACH_STATUS_ENUM_UINT32 注册状态
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,W/G下注册状态没有更新
*****************************************************************************/
RRC_NAS_ATTACH_STATUS_ENUM_UINT32  NAS_GMM_GetAttachStatus(VOS_VOID)
{
    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        return RRC_NAS_ATTACH;
    }
    else
    {
        return RRC_NAS_NOT_ATTACH;
    }
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_GetPTmsiRAI_GUL
 功能描述  : GUL多模时，获取PTMSI-GUL
 输入参数  : 无
 输出参数  : aucPtmsi    获取到的PTMSI
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月8日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年4月25日
   作    者   : l65478
   修改内容   : DTS2012041402691,连接建立ID类型错误
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetPTmsi_GUL(
    VOS_UINT8                           aucPtmsi[RRC_NAS_PTMSI_LEN]
)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    VOS_UINT8                          *pucMappedPtmsiAddr  = VOS_NULL_PTR;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT32                          ulLocalPtmsiFlg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    VOS_UINT8                           ucPtmsiValidFlg;

    ucPtmsiValidFlg          = GMM_UEID_P_TMSI;


    /* 取得存储PTMSI数据的地址 */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();
    pucMappedPtmsiAddr  = NAS_GMM_GetMappedPtmsiAddr();

    /* GU本地的PTMSI是否有效，VOS_TRUE:有效;VOS_FALSE:无效; */
    ucUeIdMask          = NAS_GMM_GetUeIdMask();
    ulLocalPtmsiFlg     = VOS_FALSE;

    if ( GMM_UEID_P_TMSI == ( ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    ulGetGutiRst            = NAS_GMM_MapPtmsiFromGUTI();
    enTinType               = NAS_MML_GetTinType();

    /* 4.7.3.1.1 GPRS attach procedure initiation (GMM_MAPPED_INFO_FROM_EPS_STRU)
       If the MS supports S1 mode, the MS shall handle the P-TMSI or IMSI IE as follows
    */
    if ( (NAS_MML_TIN_TYPE_GUTI == enTinType) && (VOS_OK == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    else if ( ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType) || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
           && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /*If the TIN is deleted,and the MS doesnot holds a valid P-TMSI and a RAI,and the MS holds a valid GUTI, the MS shall map the GUTI into the P-TMSI  */
    else if ( (NAS_MML_TIN_TYPE_INVALID  == enTinType)
           && (VOS_FALSE            == ulLocalPtmsiFlg)
           && (VOS_OK               == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    else if ( (NAS_MML_TIN_TYPE_INVALID == enTinType) && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    else
    {
        ucPtmsiValidFlg = GMM_UEID_INVALID;
        PS_MEM_SET(aucPtmsi, 0xff, NAS_MML_MAX_PTMSI_LEN);
    }

    return ucPtmsiValidFlg;

}
#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_GetOldRai
 功能描述  : GUL多模时，获取RAI
 输入参数  : 无
 输出参数  : aucPtmsi    获取到的PTMSI
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月14日
   作    者   : w00166186
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_GMM_GetOldRai(
    GMM_RAI_STRU                       *pstGmmRai
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    GMM_RAI_STRU                       *pstMappedRai = VOS_NULL_PTR;
    VOS_UINT32                          ulGetGutiRst;
#endif

    NAS_MML_RAI_STRU                       *pstLastSuccRai;

#if (FEATURE_ON == FEATURE_LTE)
    /* GU本地的PTMSI是否有效，VOS_TRUE:有效;VOS_FALSE:无效; */
    ulLocalPtmsiFlg     = VOS_FALSE;
    ucUeIdMask         = NAS_GMM_GetUeIdMask();
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    ulGetGutiRst            = NAS_GMM_MapRaiFromGUTI();
    enTinType               = NAS_MML_GetTinType();
    pstMappedRai            = NAS_GMM_GetMappedRaiAddr();

    if ( ((NAS_MML_TIN_TYPE_GUTI  == enTinType)
        && (VOS_OK  == ulGetGutiRst))
      || ((NAS_MML_TIN_TYPE_INVALID == enTinType)
        && (VOS_OK  == ulGetGutiRst)
        && (VOS_FALSE == ulLocalPtmsiFlg)) )
    {
        (VOS_VOID)VOS_MemCpy(pstGmmRai, pstMappedRai, sizeof(GMM_RAI_STRU));
        return;
    }
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &(pstGmmRai->Lai.PlmnId));

    pstGmmRai->ucRac          = pstLastSuccRai->ucRac;
    pstGmmRai->Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    pstGmmRai->Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetPTmsiRAI
 功能描述  : 获取PTMSI和RAI
 输入参数  : 无
 输出参数  : NAS_INFO_PTMSI_RAI_STRU *pstPmsiRai,当前P-TMSI_RAI
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,W/G下注册状态没有更新
  2.日    期   : 2012年3月8日
    作    者   : w00176964
    修改内容   : DTS2012031308021:GUL 多模时获取PTMSI错误
  3.日    期   : 2012年5月14日
    作    者   : w00166186
    修改内容   : DTS2012042406661:向WAS发送NAS INFO时，old rai填错

*****************************************************************************/
VOS_VOID  NAS_GMM_GetPTmsiRAI(
    NAS_INFO_PTMSI_RAI_STRU            *pstPtmsiRai
)
{

    GMM_RAI_STRU                      stGmmRai;
    NAS_MML_PLMN_ID_STRU              stPlmnId;

    /* 获取OLD RAI */
    NAS_GMM_GetOldRai(&stGmmRai);

    NAS_GMM_ConvertPlmnIdToMmcFormat(&stGmmRai.Lai.PlmnId, &stPlmnId);

    pstPtmsiRai->stPlmnId.ulMcc = stPlmnId.ulMcc;
    pstPtmsiRai->stPlmnId.ulMnc = stPlmnId.ulMnc;

    pstPtmsiRai->usLac = ((VOS_UINT16)stGmmRai.Lai.aucLac[1]
                       |(VOS_UINT16)((VOS_UINT16) stGmmRai.Lai.aucLac[0]<<8));

    pstPtmsiRai->ucRac = stGmmRai.ucRac;

#if (FEATURE_ON == FEATURE_LTE)
    (VOS_VOID)NAS_GMM_GetPTmsi_GUL(pstPtmsiRai->aucPtmsi);

#else
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus()  )
    {
        PS_MEM_SET(pstPtmsiRai->aucPtmsi, (VOS_CHAR)0xff, NAS_MML_MAX_PTMSI_LEN);
    }
    else
    {
        PS_MEM_CPY(pstPtmsiRai->aucPtmsi, NAS_MML_GetUeIdPtmsi(), NAS_MML_MAX_PTMSI_LEN);
    }
#endif


    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 在2G时向GRR发NAS INFO CHANGE消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2006年12月5日
    作    者   : luojian 60022475
    修改内容   : Maps3000接口修改
  4.日    期   : 2007年05月25日
    作    者   : luojian 60022475
    修改内容   : 根据问题单号:A32D11232
  5.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
  7.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题
  8.日    期   : 2014年4月24日
    作    者   : s00217060
    修改内容   : 从L模获取映射的安全上下文之后，通知GU模
*****************************************************************************/
VOS_VOID NAS_GMM_SndGasInfoChangeReq(VOS_UINT32 ulMask)
{
    GRRMM_NAS_INFO_CHANGE_REQ_STRU     *pSndMsg;
    GAS_NAS_INFO_ST                    *pNasInfo;

    pSndMsg = (GRRMM_NAS_INFO_CHANGE_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                    sizeof(GRRMM_NAS_INFO_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);


    if (VOS_NULL_PTR == pSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndGasInfoChangeReq():Error: Failed in VOS_AllocMsg");
        return;
    }

    /* NAS消息公共消息部分填写 */
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pSndMsg->MsgHeader.ulMsgName       = GRRMM_NAS_INFO_CHANGE_REQ;

    pNasInfo = &(pSndMsg->stNasInfo);

    PS_MEM_SET(pNasInfo, 0x0, sizeof(GAS_NAS_INFO_ST));
    pNasInfo->ulCnDomainId = RRC_NAS_PS_DOMAIN;             /* 置CN域标志 */

    /* Attach状态取值 */
    if (RRC_NAS_MASK_ATTACH == (ulMask & RRC_NAS_MASK_ATTACH))
    {
        pNasInfo->bitOpAttach = VOS_TRUE;

        pNasInfo->ulAttach = NAS_GMM_GetAttachStatus();

    }

    /* 取得DRX长度和当前SplitPgCycle值 */
    if (RRC_NAS_MASK_DRX == (ulMask & RRC_NAS_MASK_DRX))
    {
        pNasInfo->bitOpDrxLength = VOS_TRUE;

        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
        pNasInfo->ulDrxLength = (VOS_UINT32)NAS_MML_GetNonDrxTimer();
        pNasInfo->ulSplitPgCycle = GMM_CasGetSplitCycle(NAS_MML_GetSplitPgCycleCode());
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */
    }

    /* CK 信息发生改变 */
    if (RRC_NAS_MASK_SECURITY_KEY == (ulMask & RRC_NAS_MASK_SECURITY_KEY))
    {
        pNasInfo->bitOpSecurityKey = VOS_TRUE;

        Gmm_MemCpy(pNasInfo->stSecurityKey.aucKc,
                   NAS_MML_GetSimPsSecurityGsmKc(),
                   NAS_MML_GSM_KC_LEN);
    }

    /* P_TMSI和RAI赋值 */
    if (RRC_NAS_MASK_PTMSI_RAI == (ulMask & RRC_NAS_MASK_PTMSI_RAI))
    {
        pNasInfo->bitOpPTmsiRai = VOS_TRUE;

        NAS_GMM_GetPTmsiRAI(&(pNasInfo->stPtmsiRai));

    }

    if (RRC_NAS_MASK_DEL_KEY == (ulMask & RRC_NAS_MASK_DEL_KEY))
    {
        pNasInfo->bitOpDelKey = VOS_TRUE;
    }

    /* GMM服务状态填充 */
    if (NAS_GSM_MASK_GSM_GMM_STATE == (ulMask & NAS_GSM_MASK_GSM_GMM_STATE))
    {
        pNasInfo->bitOpGmmState = VOS_TRUE;

        pNasInfo->ucGsmGmmState = GMM_CasGetGmmState();
    }

    /* NAS_GSM_MASK_READY_TIMER填充 */
    if (NAS_GSM_MASK_READY_TIMER == (ulMask & NAS_GSM_MASK_READY_TIMER))
    {
        pNasInfo->bitOpReadyTime    = VOS_TRUE;

        pNasInfo->ulReadyTimerValue = gstGmmCasGlobalCtrl.ulReadyTimerValue;
    }

    /* GMM当前MS GPRS模式填充 */
    if (NAS_GSM_MASK_MS_GPRS_MODE == (ulMask & NAS_GSM_MASK_MS_GPRS_MODE))
    {
        pNasInfo->bitOpGprsMode = VOS_TRUE;

        pNasInfo->ucMsGprsMode  = GMM_CasGetMsGprsMode();
    }


    /* GMM当前NAS_GSM_MASK_MAPPED_SECURITY_KEY填充 */
    if (NAS_GSM_MASK_MAPPED_SECURITY_KEY == (ulMask & NAS_GSM_MASK_MAPPED_SECURITY_KEY))
    {
        pNasInfo->bitOpIdleMappedLSecurity = VOS_TRUE;

        Gmm_MemCpy(pNasInfo->stSecurityKey.aucKc,
                   NAS_MML_GetSimPsSecurityGsmKc(),
                   NAS_MML_GSM_KC_LEN);
    }

    /* 向GAS发送INFO_CHANGE_REQ */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_GMM, pSndMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndGasInfoChangeReq():Error: Failed in GMM_SndGasMsg()");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 2G网络下通知GAS模块GMM消息过程
                  HSS 4100 V200R001 新增
                  GMM消息过程包括:
                  GMM ATTACH
                  GMM RAU
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2007-11-21
    Author      : l00107747
    Modification: Created function
  2.日    期   : 2014年05月22日
    作    者   : W00242748
    修改内容   : DTS2014050900899:将GMM的处理状态通知给WAS
*****************************************************************************/
VOS_VOID NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ENUM_UINT16 usProcType,
                                  RRMM_GMM_PROC_FLAG_ENUM_UINT16 usProcFlag)
{
    RRMM_GMM_PROC_NOTIFY_STRU          *pstGmmProcNotify;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulReceivePid;

    pstGmmProcNotify = (RRMM_GMM_PROC_NOTIFY_STRU *)PS_ALLOC_MSG(
                    WUEPS_PID_GMM,
                    sizeof(RRMM_GMM_PROC_NOTIFY_STRU)
                    - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstGmmProcNotify)
    {
        /*打印错误信息*/
        GMM_LOG_ERR("GMM_SndRrmmGmmProcNotify():Error: Failed in VOS_AllocMsg()");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstGmmProcNotify + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RRMM_GMM_PROC_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 该函数在被调用时，需在GU下 */
    if ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType() )
    {
        ulReceivePid = UEPS_PID_GAS;
    }
    else
    {
        ulReceivePid = WUEPS_PID_WRR;
    }

    /* 填写GRRGMM_GPRS_PROC_FINISHED_IND消息内容 */
    pstGmmProcNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGmmProcNotify->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstGmmProcNotify->stMsgHeader.ulMsgName       = RRMM_GMM_PROC_NOTIFY;
    pstGmmProcNotify->usGmmProcFlag               = usProcFlag;
    pstGmmProcNotify->usGmmProcType               = usProcType;

    /* 2G网络下，发送GMM消息 */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstGmmProcNotify);
    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_SndRrmmGmmProcNotify():Error: Failed in VOS_SendMsg()");
        return;
    }
}

/*****************************************************************************
函 数 名  : GMM_SndRrmmGmmProcAns
功能描述  : 处理RRMM_GMM_PROC_ENQ原语
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期: 2014年05月23日
  作    者: w00242748
  修改内容: DTS2014050900899:将GMM的处理状态通知给WAS

*****************************************************************************/
VOS_VOID NAS_GMM_SndRrmmGmmProcAns(VOS_VOID)
{
    RRMM_GMM_PROC_ANS_STRU             *pstGmmProcAns;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulReceivePid;
    RRMM_GMM_PROC_CONN_TYPE_ENUM_UINT16 enConnType;

    pstGmmProcAns = (RRMM_GMM_PROC_ANS_STRU *)PS_ALLOC_MSG(
                    WUEPS_PID_GMM,
                    sizeof(RRMM_GMM_PROC_ANS_STRU)
                    - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstGmmProcAns)
    {
        /*打印错误信息*/
        GMM_LOG_ERR("GMM_SndRrmmGmmProcAns():Error: Failed in VOS_AllocMsg()");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstGmmProcAns + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RRMM_GMM_PROC_ANS_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 该函数在被调用时，需在GU下 */
    if ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType() )
    {
        ulReceivePid = UEPS_PID_GAS;
    }
    else
    {
        ulReceivePid = WUEPS_PID_WRR;
    }

    enConnType = RRMM_GMM_PROC_CONN_TYPE_NO_CONN;

    if ( GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState )
    {
        enConnType = RRMM_GMM_PROC_CONN_TYPE_ATTACH_SIG_CONN;
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState )
    {
        enConnType = RRMM_GMM_PROC_CONN_TYPE_RAU_SIG_CONN;
    }
    else if ( GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState )
    {
        enConnType = RRMM_GMM_PROC_CONN_TYPE_PS_SERVICE_CONN;
    }
    else
    {

    }

    /* 填写GRRGMM_GPRS_PROC_FINISHED_IND消息内容 */
    pstGmmProcAns->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGmmProcAns->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstGmmProcAns->stMsgHeader.ulMsgName       = RRMM_GMM_PROC_ANS;
    pstGmmProcAns->enGmmConnType               = enConnType;

    /* 2G网络下，发送GMM消息 */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstGmmProcAns);
    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_SndRrmmGmmProcAns():Error: Failed in VOS_SendMsg()");
        return;
    }
}



/*****************************************************************************
 Prototype      : GMM_SndRabmRauInd
 Description    : 向RABM发送GMMRABM_ROUTING_AREA_UPDATE_IND消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2006-10-19
    Author      : L47619
    Modification: 问题单：A32D06916
*****************************************************************************/
VOS_VOID GMM_SndRabmRauInd(VOS_UINT8 ucRauCause, VOS_UINT8 ucResult)
{
    GMMRABM_ROUTING_AREA_UPDATE_IND_MSG *pRauInd;
    VOS_UINT32          ulRet;

    pRauInd = (GMMRABM_ROUTING_AREA_UPDATE_IND_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(GMMRABM_ROUTING_AREA_UPDATE_IND_MSG)
                - VOS_MSG_HEAD_LENGTH );
    if (VOS_NULL_PTR == pRauInd)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_SndRabmRauInd():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* 填写消息内容 */
    pRauInd->ulTLLI        = gstGmmCasGlobalCtrl.ulTLLI;
    pRauInd->ucGmmRauCause = ucRauCause;
    pRauInd->ucResult      = ucResult;
    Gmm_MemSet(&pRauInd->aucRecvNPDUNumListIE[0],
                    0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN);
    if ( (0 < g_GmmRauCtrl.ucNpduCnt)
      && (RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN > g_GmmRauCtrl.ucNpduCnt) )
    {/* N-PDU NUMBER 有效 */
        pRauInd->aucRecvNPDUNumListIE[0] = 0x26;        /*N-PDU IEI*/
        pRauInd->aucRecvNPDUNumListIE[1] = g_GmmRauCtrl.ucNpduCnt;
        Gmm_MemCpy(&pRauInd->aucRecvNPDUNumListIE[2],
                   &g_GmmRauCtrl.aucNpduNum[0],
                    g_GmmRauCtrl.ucNpduCnt);                                     /* 填写N-PDU NUMBER                         */
    }
    /*else
    {*/ /* N-PDU NUMBER 无效 */
    /*    VOS_MemSet(&pRauInd->aucRecvNPDUNumListIE[0],
                    0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN);
    }*/

    /* 填写DOPRA消息头 */
    pRauInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pRauInd->MsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pRauInd->MsgHeader.ulMsgName   = ID_GMM_RABM_ROUTING_AREA_UPDATE_IND;

    PS_MEM_SET(pRauInd->aucReserve,0x00,sizeof(pRauInd->aucReserve));

    /* 向RABM发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pRauInd);
    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GMM_SndRabmRauInd():Error: Failed in VOS_SendMsg()");
    }

    return;
}


/*****************************************************************************
 Prototype      :
 Description    : 发送LL_GMM_SUSPEND_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_SndLlcSuspendReq(VOS_VOID)
{
    LL_GMM_SUSPEND_REQ_MSG  *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32               ulRet;
    /* TLLI有效性判断 */
    /*if (GMM_LOCAL_TLLI != gstGmmCasGlobalCtrl.ucflgTLLI)*/
    /*{*/ /*没有LOCAL TLLI，说明没有完成ATTACH*/
     /*没有ATTACH，是不可能存在LLC数据传输*/
     /*没有数据传输，不需要挂起LLC*/
    /*    GMM_LOG_ERR("GMM_SndLlcSuspendReq():Error: Is not GMM_LOCAL_TLLI");*/
    /*    return;*/
    /*}*/
    /* 创建消息 */
    pSendMsg = GMM_MakeLlgmmSuspendReqMsg();
    if (VOS_NULL_PTR == pSendMsg)
    {
        GMM_LOG_ERR("GMM_SndLlcSuspendReq():Error: message make unsuccessfully!");
        return;
    }

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_SndLlcSuspendReq():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 发送LL_GMM_ABORT_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-12-12
    Author      : s46746
    Modification: Created function
  2.日    期   : 2009年06月30日
    作    者   : l65478
    修改内容   : 问题单：AT2D12655,增加清除LLC数据类型的处理
*****************************************************************************/
VOS_VOID Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8 ucClearDataType)
{
    LL_GMM_ABORT_REQ_MSG    *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32               ulRet;

    pSendMsg = (LL_GMM_ABORT_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(LL_GMM_ABORT_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pSendMsg)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("Gmm_SndLlcAbortReq():Error: Failed in VOS_AllocMsg()");
        return;
    }

    pSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSendMsg->ulReceiverPid   = UEPS_PID_LL;
    pSendMsg->usMsgType       = ID_LL_GMM_ABORT_REQ;
    pSendMsg->enClearDataType = ucClearDataType;

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("Gmm_SndLlcAbortReq():Error: Send msg fail!");
    }

    return;
}


/*****************************************************************************
 Prototype      :
 Description    : 发送LL_GMM_RESUME_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2010年9月09日
    作    者   : l65478
    修改内容   : DTS2010090302562,PDP激活过程中发生重选，PDP激活事件比标杆慢
*****************************************************************************/
VOS_VOID GMM_SndLlcResumeReq(VOS_UINT32  ulResumeType)
{
    LL_GMM_RESUME_REQ_MSG   *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32               ulRet;
    /* TLLI有效性判断 */
    /*if (GMM_LOCAL_TLLI != gstGmmCasGlobalCtrl.ucflgTLLI)*/
    /*{*/ /*没有LOCAL TLLI，说明LLC没有数据传输*/
     /*不会挂起LLC，也就不需要恢复LLC挂起*/
    /*    GMM_LOG_ERR("GMM_SndLlcResumeReq():Error: Is not GMM_LOCAL_TLLI");*/
    /*  return;*/
    /*}*/
    /* 创建消息 */
    pSendMsg = GMM_MakeLlgmmResumeReqMsg(ulResumeType);
    if (VOS_NULL_PTR == pSendMsg)
    {
        GMM_LOG_ERR("GMM_SndLlcResumeReq():Error: Message make unsuccessfully!");
        return;
    }

    if (LL_GMM_RESUME_TYPE_SIGNAL != ulResumeType)
    {
        gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
    }

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_SndLlcResumeReq():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 发送LL_GMM_TRIGGER_REQ消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-14
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_SndLlcTriggerReq(VOS_UINT8 ucCause)
{
    LL_GMM_TRIGGER_REQ_MSG   *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32                ulRet;

    pSendMsg = GMM_MakeLlgmmTriggerReqMsg(ucCause);
    if (VOS_NULL_PTR == pSendMsg)
    {
        GMM_LOG_ERR("GMM_SndLlcTriggerReq():Error: Failed in GMM_MakeLlgmmTriggerReqMsg()");
        return;
    }


    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_SndLlcTriggerReq():Error: Send msg fail!");
    }

    return;
}


/*****************************************************************************
 Prototype      : GMM_SndMmcSuspendRsp
 Description    : 向MMC发送MMCGMM_SUSPEND_RSP 消息
                  HSS 4121 V100R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-04-05
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_SndMmcSuspendRsp(VOS_VOID)
{
    MMCGMM_SUSPEND_RSP_ST              *pstMsg;
    MMCGMM_SUSPEND_RSP_ST              *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_SUSPEND_RSP_ST);

    pstInternalMsg  = (MMCGMM_SUSPEND_RSP_ST*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_SUSPEND_RSP;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 获得DRX参数中的Split pg cycle值
                  根据Split pg cycle code列表计算对应的Split pg cycle
                  HSS 4121 V100R001 新增
 Input          :
 Output         :
 Return Value   : VOS_UINT32
                  704           等效于no DRX
                  其他值        有效的Split pg cycle

 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-06-14
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_CasGetSplitCycle(VOS_UINT8 ucSplitCode)
{
    VOS_UINT32      ulSplitCycle = 0;

    /* 等效于no DRX */
    if (0 == ucSplitCode)
    {
        return 704;
    }

    /* code 1 to 64 */
    if (65 > ucSplitCode)
    {
        ulSplitCycle = ucSplitCode;
        return ulSplitCycle;
    }

    /* 其他split cycle从split code表中取得 */
    if (GMM_DRX_CYCLE_CODE_NUMBER < ucSplitCode)
    {
        ulSplitCycle = 32;              /* 默认有效值 */
    }
    else
    {
        ulSplitCycle = gausGmmDrxCycleCodeTab[ucSplitCode-65];
    }

    return ulSplitCycle;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndMmcResumeRsp
 功能描述  : GMM向mmc发送resume rsp
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : W00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcResumeRsp(VOS_VOID)
{
    MMCGMM_RESUME_RSP_ST               *pstMsg;
    MMCGMM_RESUME_RSP_ST               *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(MMCGMM_RESUME_RSP_ST);

    pstInternalMsg  = (MMCGMM_RESUME_RSP_ST*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_RESUME_RSP;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_SndRabmSysSrvChgInd
 功能描述  : 发送ID_GMM_RABM_SYS_SRV_CHG_IND至RABM
 输入参数  : enSysMode          - 当前系统模式
             bRatChangeFlg      - 异系统切换标志
             bDataSuspendFlg    - 挂起标志
             ucRebuildRabFlag   - RAB是否需要重建
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月6日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 Phase II 调整:支持GUL异系统HO CCO

  3.日    期   : 2011年8月19日
    作    者   : w00167002
    修改内容   : V7R1 Phase II 调整:保留字段清零

*****************************************************************************/
VOS_VOID NAS_GMM_SndRabmSysSrvChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode,
    VOS_BOOL                            bRatChangeFlg,
    VOS_BOOL                            bDataSuspendFlg,
    VOS_UINT8                           ucRebuildRabFlag
)
{
    GMM_RABM_SYS_SRV_CHG_IND_STRU      *pstSysSrvChgInd;

    /* 构造消息 */
    pstSysSrvChgInd = (GMM_RABM_SYS_SRV_CHG_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_GMM,
                            sizeof(GMM_RABM_SYS_SRV_CHG_IND_STRU));
    if (VOS_NULL_PTR == pstSysSrvChgInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM,
            "NAS_GMM_SndRabmSysSrvChgInd: Memory alloc failed.");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSysSrvChgInd + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(GMM_RABM_SYS_SRV_CHG_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstSysSrvChgInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysSrvChgInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstSysSrvChgInd->stMsgHeader.ulMsgName       = ID_GMM_RABM_SYS_SRV_CHG_IND;

    /* 填写消息内容 */
    pstSysSrvChgInd->enSysMode          = enSysMode;
    pstSysSrvChgInd->bRatChangeFlg      = bRatChangeFlg;
    pstSysSrvChgInd->bDataSuspendFlg    = bDataSuspendFlg;

    pstSysSrvChgInd->ucRebuildRabFlag   = ucRebuildRabFlag;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstSysSrvChgInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM,
            "NAS_GMM_SndRabmSysSrvChgInd: Send message failed.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SndGasGprsAuthFailNotifyReq
 功能描述  : 连续3次鉴权被拒时，通知GAS,参考T3302的时长，Bar掉当前小区
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : l00130025
    修改内容   : DTS2012032004389，Netork连续3次被Ms Auth Rej或T3318/T3320超时时，没有通知GAS Bar掉当前小区,
                 相关协议TS 24.008 4.3.2.6.1 & 4.7.7.6,Ts43.022 3.5.5
                 If the MS deems that the network has failed the authentication check,
                 then it shall request RR or RRC to release the RR connection and the PS signalling connection, if any,
                 and bar the active cell or cells (see 3GPP TS 25.331 [23c] and 3GPP TS 44.018 [84]).
*****************************************************************************/
VOS_VOID  NAS_GMM_SndGasGprsAuthFailNotifyReq(VOS_VOID)
{

    RRMM_AUTH_FAIL_NOTIFY_REQ_STRU      *pMsg;
    VOS_UINT32                           ulRet;

    if (NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
		return;
	}

    pMsg = (RRMM_AUTH_FAIL_NOTIFY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                                  sizeof(RRMM_AUTH_FAIL_NOTIFY_REQ_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;

    pMsg->MsgHeader.ulMsgName       = RRMM_AUTH_FAIL_NOTIFY_REQ;

    pMsg->ulT3302TimerLen           = g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);

    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM,"NAS_GMM_SndGasGprsAuthFailNotifyReq:ERROR: Send msg Fail.");
    }

    return;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
