/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaRegManagement.c
  Description     : 该C文件实现注册管理模块的初始化，内部消息的处理和发送
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaEntity.h"
#include "ImsaRegManagement.h"
#include "ImsaPublic.h"
#include "ImsaImsAdaption.h"
#include "ImsaImsInterface.h"
#include "math.h"
/*lint -e767*/
#define    THIS_FILE_ID             PS_FILE_ID_IMSAREGMANAGEMENT_C
#define    THIS_NAS_FILE_ID         NAS_FILE_ID_IMSAREGMANAGEMENT_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

VOS_UINT32 IMSA_RegFsmProcIdleReqReq(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);

VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegSuccess(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_UINT32 IMSA_RegFsmProcRegisteringProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_UINT32 IMSA_RegFsmProcRegisteringUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcRegisteredImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRegisteredUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcDeregingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcDeregingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcDeregingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcDeregingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcWaitRetryTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcWaitRetryUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcPendingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcPendingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcPendingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcPendingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
/*
VOS_UINT32 IMSA_RegFsmProcPendingImsRegSuccess(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
*/
VOS_UINT32 IMSA_RegFsmProcRollingBackProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRollingBackImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRollingBackUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRollingBackUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_VOID IMSA_RegResetPeriodTryImsRegTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);

IMSA_FSM_PROC IMSA_FsmGetProcItem(VOS_UINT32 ulState, VOS_UINT32 ulEvt);
VOS_UINT32 IMSA_FsmRun(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_VOID IMSA_RegResetRetryTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);
VOS_VOID IMSA_RegConverterReg2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pucIpAddr,
    const VOS_CHAR *pacPcscfAddr,
    IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvt
);
VOS_VOID IMSA_RegConfigIpAddress2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    const VOS_CHAR                     *pcUeAddr,
    const VOS_CHAR                     *pacPcscfAddr
);
VOS_VOID IMSA_RegSendImsMsgDereg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    VOS_UINT32                          ulIsLocal
);
VOS_UINT32 IMSA_RegSendImsMsgReg
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pcUeAddr,
    const VOS_CHAR *pcPcscfAddr
);
VOS_UINT32 IMSA_RegSendIntraMsgRegInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
VOS_UINT32 IMSA_RegSendIntraMsgDeregInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
VOS_UINT32 IMSA_RegGetAddrByParamType
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32 enParamType,
    VOS_CHAR *pucUeAddr,
    VOS_CHAR *pucPcscfAddr
);
VOS_UINT32 IMSA_RegParseImsError
(
    const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService,
    IMSA_IMS_OUTPUT_ERROR_STRU          *pstImsErrorInfo
);
VOS_UINT32 IMSA_RegCalculateRetryDelayTime
(
    VOS_UINT32                          ulMaxTime,
    VOS_UINT32                          ulBaseTime,
    VOS_UINT32                          ulConsecutiveFailures
);
VOS_UINT32 IMSA_RegCalculateRegFailureRetryIntervelTime
(
    VOS_UINT32                          ulRetryTimes,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration
);
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailure305
(
    IMSA_REG_ENTITY_STRU               *pstEntity
);
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut
(
    IMSA_REG_ENTITY_STRU               *pstEntity
);

VOS_VOID IMSA_RegInitRegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
);

VOS_VOID IMSA_RegReRegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
);

VOS_UINT32 IMSA_RegProcCustomBuildCause
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
);
VOS_UINT32 IMSA_RegProcImsMsgState(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairCreate
(
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr,
    const VOS_CHAR *pacPcscfAddr
);
VOS_VOID IMSA_RegAddrPairDestroy(IMSA_REG_ADDR_PAIR_STRU *pstAddrPair);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListAdd
(
    IMSA_REG_ADDR_PAIR_STRU **ppstListHead,
    IMSA_REG_ADDR_PAIR_STRU *pstNode
);
VOS_VOID IMSA_RegAddrPairListDestroy(IMSA_REG_ADDR_PAIR_STRU *pstListHead);
VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacPcscfAddr
);
VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewUeAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr
);
VOS_VOID IMSA_RegGetAddrPairListHead
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    IMSA_REG_ADDR_PAIR_STRU          ***pppstListHead
);
VOS_VOID IMSA_RegAddrPairListClearAllUsedFlag(IMSA_REG_ADDR_PAIR_STRU *pstList);


/**
 *  注册模块状态表定义
 *
 */
IMSA_REG_FSM_ITEM_STRU g_stImsaRegFsmTable[] =
{
    {IMSA_REG_STATUS_NOT_REGISTER, IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcIdleReqReq},

    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_IMS_REG_SUCCESS,  IMSA_RegFsmProcRegisteringImsRegSuccess},
    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcRegisteringImsRegFailure},
    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcRegisteringProtectTimeout},
    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcRegisteringUserDereg},

    {IMSA_REG_STATUS_REGISTERED,   IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcRegisteredImsRegFailure},
    {IMSA_REG_STATUS_REGISTERED,   IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcRegisteredUserDereg},

    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcDeregingImsRegFailure},
    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcDeregingProtectTimeout},
    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcDeregingUserReg},
    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcDeregingUserDereg},

    {IMSA_REG_STATUS_WAIT_RETRY,   IMSA_REG_EVT_TIMEOUT_RETRY,    IMSA_RegFsmProcWaitRetryTimeout},
    {IMSA_REG_STATUS_WAIT_RETRY,   IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcWaitRetryUserDereg},

    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcPendingProtectTimeout},
    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcPendingUserReg},
    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcPendingUserDereg},
    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcPendingImsRegFailure},
    /*{IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_IMS_REG_SUCCESS,  IMSA_RegFsmProcPendingImsRegSuccess},*/

    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcRollingBackProtectTimeout},
    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcRollingBackImsRegFailure},
    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcRollingBackUserReg},
    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcRollingBackUserDereg},

};


VOS_VOID IMSA_RegAddrPairMgrInit(IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr);
VOS_VOID IMSA_RegAddrPairMgrDeinit(const IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr);
VOS_UINT32 IMSA_RegAddrPairMgrGetNextUnused(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                            VOS_CHAR *pacUeIp,
                                            VOS_CHAR *pacPcscfIp);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListGetNextUnused(IMSA_REG_ADDR_PAIR_STRU *pstList);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairMgrGetFirst(IMSA_REG_TYPE_ENUM_UINT8 ulRegType);

VOS_VOID IMSA_RegAddrPairMgrClearAllUsedFlag(IMSA_REG_TYPE_ENUM_UINT8 enRegType);


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_FsmGetProcItem
 Description    : 获取状态事件处理函数
 Input          : ulState   当前状态
                  ulEvt     要处理的事件
 Output         : VOS_VOID
 Return Value   : 该状态该事件对应的处理函数，如果没有找到，返回VOS_NULL_PTR

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_FSM_PROC IMSA_FsmGetProcItem(VOS_UINT32 ulState, VOS_UINT32 ulEvt)
{
    VOS_UINT32 i = 0;

    for (i = 0; i < (sizeof(g_stImsaRegFsmTable)/sizeof(IMSA_REG_FSM_ITEM_STRU)); i++)
    {
        if ((g_stImsaRegFsmTable[i].ulState == ulState) &&
            (g_stImsaRegFsmTable[i].ulEvent == ulEvt))
        {
            return g_stImsaRegFsmTable[i].ProcFun;
        }
    }

    IMSA_INFO_LOG2("IMSA_FsmGetProcItem: not found fsm procedure", ulState, ulEvt);
    TLPS_PRINT2LAYER_INFO2(IMSA_FsmGetProcItem_ENUM, LNAS_PARAM_INVALID, ulState, ulEvt);

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function Name  : IMSA_FsmRun
 Description    : 事件驱动状态机运行一次
 Input          : pstEntity     所属注册实体
                  ulEvt         要处理的事件
                  pData         该事件对应的数据
 Output         : VOS_VOID
 Return Value   : 状态机运行结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_FsmRun(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData)
{
    IMSA_FSM_PROC FsmProcFun;

    IMSA_INFO_LOG2("IMSA_FsmRun:", pstEntity->enStatus, ulEvt);
    TLPS_PRINT2LAYER_INFO2(IMSA_FsmRun_ENUM, 1, pstEntity->enStatus, ulEvt);

    FsmProcFun = IMSA_FsmGetProcItem(pstEntity->enStatus, ulEvt);
    if (VOS_NULL_PTR != FsmProcFun)
    {
        return FsmProcFun(pstEntity, ulEvt, pData);
    }

    IMSA_ERR_LOG("IMSA_FsmRun: Not registered state and event");
    TLPS_PRINT2LAYER_ERROR(IMSA_FsmRun_ENUM, LNAS_PARAM_INVALID);

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_RegResetPeriodTryImsRegTimes
 Description    : 清0周期尝试IMS注册次数
 Input          : enRegType--------------注册类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID
 History        :
      1.xiongxianghui 00253310      2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegResetPeriodTryImsRegTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity = VOS_NULL_PTR;

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        pstRegEntity = IMSA_RegEntityGetByType(enRegType);

        pstRegEntity->ucTryRegTimes = 0;
    }
}


/*****************************************************************************
 Function Name  : IMSA_RegResetRetryTimes
 Description    : 清0重试次数
 Input          : enRegType--------------注册类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID
 History        :
      1.lihong 00150010      2013-10-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegResetRetryTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity = VOS_NULL_PTR;

    pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    pstRegEntity->ulRetryTimes = 0;
}

/*****************************************************************************
 Function Name  : IMSA_RegConverterReg2Ims
 Description    : 发起注册消息参数的转换
 Input          : pacPcscfAddr     PCSCF地址
                  pstInputEvent   存放转换结果的D2输入消息
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.wangchen 00209181    2013-10-09  Modify
*****************************************************************************/
VOS_VOID IMSA_RegConverterReg2Ims(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                    const VOS_CHAR *pucIpAddr,
                                    const VOS_CHAR *pacPcscfAddr,
                                    IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvt)
{
    IMSA_INFO_LOG("IMSA_RegConverterReg2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegConverterReg2Ims_ENUM, LNAS_ENTRY);

    /* 设置输入事件类型 */
    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    /* 设置输入Reason和opid */
    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_IP;

        /* 设置IP地址 */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalIp.acUeAddress, pucIpAddr, IMSA_IMS_IP_ADDRESS_STRING_SZ);

        /* 设置PCSCF地址 */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalIp.acPcscf, pacPcscfAddr, IMSA_IMS_EVENT_STRING_SZ);
    }
    else
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_EMC_IP;

        /* 设置IP地址 */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcIp.acUeAddress, pucIpAddr, IMSA_IMS_IP_ADDRESS_STRING_SZ);

        /* 设置PCSCF地址 */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcIp.acPcscf, pacPcscfAddr, IMSA_IMS_EVENT_STRING_SZ);
    }

}


/*****************************************************************************
 Function Name  : IMSA_RegConfigIpAddress2Ims
 Description    : 给IMS配置IP地址信息
 Input          : enRegType---------------------注册实体类型
                  pacPcscfAddr------------------IP地址指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-17  Draft Enact
      2.wangchen 00209181    2013-10-09  Modify
*****************************************************************************/
VOS_VOID IMSA_RegConfigIpAddress2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    const VOS_CHAR                     *pcUeAddr,
    const VOS_CHAR                     *pacPcscfAddr
)
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegConfigIpAddress2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegConfigIpAddress2Ims_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_RegConfigIpAddress2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegConfigIpAddress2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( pstImsaImsInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_RegConverterReg2Ims(enRegType, pcUeAddr, pacPcscfAddr, pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*释放消息空间*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}



/*****************************************************************************
 Function Name  : IMSA_RegSendImsMsgDereg
 Description    : 通知IMS去注册
 Input          : enRegType------------------注册实体类型
                  ulIsLocal------------------是否是本地去注册
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegSendImsMsgDereg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    VOS_UINT32                          ulIsLocal
)
{

    /*IMSA_DeregConfigIpAddress2Ims(enRegType,"");*/

    if (VOS_TRUE == ulIsLocal)
    {
        if (IMSA_REG_TYPE_NORMAL == enRegType)
        {
            IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER);
        }
        else
        {
            IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER_EMERGENCY);
        }

    }
    else
    {
        IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_DEREGISTER);
    }


}

/*****************************************************************************
 Function Name  : IMSA_SndD2MsgServiceRegInfo()
 Description    :  给D2发送service event的注册信息
 Input          : pstIMSCnf   卡鉴权结果
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leili 00132387      2013-10-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason)
{
    IMSA_IMS_INPUT_EVENT_STRU   *pstHiInputEvent;

    /*分配空间并检验分配是否成功*/
    pstHiInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstHiInputEvent )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndD2MsgServiceRegInfo:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndD2MsgServiceRegInfo_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( pstHiInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstHiInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SERVICE;

    pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = enInputServeReason;

    pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgServiceEvent(pstHiInputEvent);

    /*释放消息空间*/
    IMSA_MEM_FREE(pstHiInputEvent);

}



/*****************************************************************************
 Function Name  : IMSA_RegSendImsMsgReg
 Description    : 请求D2 IMS发起注册
 Input          : enRegType        去注册实体类型，紧急或普通
                  pcUeAddr         本次注册使用的UE地址
                  pcPcscfAddr      本次注册使用的P-CSCF地址
 Output         : VOS_VOID
 Return Value   : 注册消息发送结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegSendImsMsgReg(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                 const VOS_CHAR *pcUeAddr,
                                 const VOS_CHAR *pcPcscfAddr)
{
    IMSA_INFO_LOG("IMSA_RegSendImsMsgReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendImsMsgReg_ENUM, LNAS_ENTRY);

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        /* set UE IP address to trigger register */
        IMSA_RegConfigIpAddress2Ims(enRegType, pcUeAddr, pcPcscfAddr);

        IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_REGISTER);
    }
    else if (IMSA_REG_TYPE_EMC == enRegType)
    {
        /* set UE IP address to trigger register */
        IMSA_RegConfigIpAddress2Ims(enRegType, pcUeAddr, pcPcscfAddr);

        IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_REGISTER_EMERGENCY);
    }
    else
    {
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegSendIntraMsgRegInd
 Description    : 发送内部消息通知注册指示
 Input          : enRegType        去注册实体类型，紧急或普通
                  enResult         注册结果
                  enAction         需要Service模块后续的操作
 Output         : VOS_VOID
 Return Value   : 发送结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegSendIntraMsgRegInd(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                      IMSA_REG_RESULT_ENUM_UINT32 enResult,
                                      IMSA_RESULT_ACTION_ENUM_UINT32 enAction)
{
    IMSA_REG_REG_IND_STRU stRegInd = {0};

    IMSA_INFO_LOG("IMSA_RegSendIntraMsgRegInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendIntraMsgRegInd_ENUM, LNAS_ENTRY);

    stRegInd.enRegType      = enRegType;
    stRegInd.enResult       = enResult;
    stRegInd.enResultAction = enAction;
    /**
     * 暂时不上报SIP Server返回的参数信息，
     * 待上层用户有需求时再添加
     */

    return IMSA_RegSendIntraMsg(ID_IMSA_REG_REG_IND, (VOS_UINT8*)&stRegInd, sizeof(IMSA_REG_REG_IND_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_RegSendIntraMsgDeregInd
 Description    : 发送内部消息通知去注册指示
 Input          : enRegType        去注册实体类型，紧急或普通
                  enResult         去注册结果
                  enAction         需要Service模块后续的操作
 Output         : VOS_VOID
 Return Value   : 发送结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegSendIntraMsgDeregInd(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                        IMSA_REG_RESULT_ENUM_UINT32 enResult,
                                        IMSA_RESULT_ACTION_ENUM_UINT32 enAction)
{
    IMSA_REG_DEREG_IND_STRU stDeregInd = {0};

    IMSA_INFO_LOG("IMSA_RegSendIntraMsgDeregInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendIntraMsgDeregInd_ENUM, LNAS_ENTRY);

    stDeregInd.enRegType      = enRegType;
    stDeregInd.enResult       = enResult;
    stDeregInd.enResultAction = enAction;
    /**
     * 暂时不上报SIP Server返回的参数信息，
     * 待上层用户有需求时再添加
     */

    return IMSA_RegSendIntraMsg(ID_IMSA_REG_DEREG_IND, (VOS_UINT8*)&stDeregInd, sizeof(IMSA_REG_DEREG_IND_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_RegSendIntraMsg
 Description    : 发送内部消息
 Input          : ulMsgId        内部消息id
                  pucMsg         内部消息内容地址
                  ulLen          内部消息内容长度
 Output         : VOS_VOID
 Return Value   : 发送结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegSendIntraMsg(VOS_UINT32 ulMsgId, const VOS_UINT8 *pucMsg, VOS_UINT32 ulLen)
{
    /* 借用消息结构头部分的定义 */
    IMSA_REG_REG_IND_STRU *pstIntraMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegSendIntraMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendIntraMsg_ENUM, LNAS_ENTRY);

    if (VOS_MSG_HEAD_LENGTH > ulLen)
    {
        IMSA_ERR_LOG("IMSA_RegSendIntraMsg: invalid param : uLen");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegSendIntraMsg_ENUM, LNAS_PARAM_INVALID);
        return VOS_FALSE;
    }

    /* 分配空间并检验分配是否成功 */
    pstIntraMsg = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(ulLen);
    if (VOS_NULL_PTR == pstIntraMsg)
    {
        IMSA_ERR_LOG("IMSA_RegSendIntraMsg: alloc fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegSendIntraMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* 拷贝特定消息的内容 */
    IMSA_MEM_CPY_S(pstIntraMsg, ulLen, pucMsg, ulLen);

    /* 填写消息头 */
    IMSA_WRITE_INTRA_MSG_HEAD(pstIntraMsg, ulMsgId, ulLen);

    /* 发送消息 */
    IMSA_SEND_INTRA_MSG((VOS_VOID*)pstIntraMsg);

    return VOS_TRUE;
}

VOS_UINT32 IMSA_RegGetAddrByParamType(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                      IMSA_REG_ADDR_PARAM_ENUM_UINT32 enParamType,
                                      VOS_CHAR *pucUeAddr,
                                      VOS_CHAR *pucPcscfAddr)
{
    VOS_UINT32 ulResult = VOS_TRUE;
    IMSA_REG_ADDR_PAIR_STRU *pstAddrPair = VOS_NULL_PTR;
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    #endif

    IMSA_INFO_LOG1("IMSA_RegGetAddrByParamType is entered!", enParamType);
    TLPS_PRINT2LAYER_INFO1(IMSA_RegGetAddrByParamType_ENUM, LNAS_ENTRY, enParamType);

    #if (FEATURE_ON == FEATURE_PTM)
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        pstControlMagnaer->enNrmAddrType = enParamType;
    }
    else
    {
        pstControlMagnaer->enEmcAddrType = enParamType;
    }
    #endif

    switch (enParamType)
    {
    case IMSA_REG_ADDR_PARAM_NEW:
        IMSA_RegAddrPairMgrClearAllUsedFlag(enRegType);

        IMSA_RegResetRetryTimes(enRegType);

        pstAddrPair = IMSA_RegAddrPairMgrGetFirst(enRegType);
        if (VOS_NULL_PTR != pstAddrPair)
        {
            IMSA_UtilStrNCpy(pucUeAddr, pstAddrPair->acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
            IMSA_UtilStrNCpy(pucPcscfAddr, pstAddrPair->acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);

            IMSA_INFO_LOG(pucUeAddr);
            IMSA_INFO_LOG(pucPcscfAddr);
        }
        else
        {
            ulResult = VOS_FALSE;
        }
        break;
    case IMSA_REG_ADDR_PARAM_NEXT:
        IMSA_RegResetRetryTimes(enRegType);

        ulResult = IMSA_RegAddrPairMgrGetNextUnused(enRegType, pucUeAddr, pucPcscfAddr);
        break;
    case IMSA_REG_ADDR_PARAM_SAME:
        ulResult = IMSA_RegAddrPairMgrGetCurrent(enRegType, pucUeAddr, pucPcscfAddr);
        break;
    case IMSA_REG_ADDR_PARAM_RESTORATION:
        IMSA_RegResetRetryTimes(enRegType);

        if ((VOS_FALSE == IMSA_RegAddrPairMgrGetNextUnused(enRegType, pucUeAddr, pucPcscfAddr)) &&
            (VOS_FALSE == IMSA_RegAddrPairMgrGetCurrent(enRegType, pucUeAddr, pucPcscfAddr)))
        {
            ulResult = VOS_FALSE;
        }
        break;
    default:
        ulResult = VOS_FALSE;
        IMSA_ERR_LOG1("IMSA_RegGetAddrByParamType: invalid param type", enParamType);
        TLPS_PRINT2LAYER_ERROR1(IMSA_RegGetAddrByParamType_ENUM, LNAS_PARAM_INVALID, enParamType);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcIdleReqReq
 Description    : Idle状态收到用户注册请求的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcIdleReqReq(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_UINT32 ulResult = VOS_FALSE;
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcIdleReqReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcIdleReqReq_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    /* 如果当前接入类型不支持IMS，不再发起注册 */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
        }
        else
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_NULL);
        }
        return VOS_FALSE;
    }

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* 根据注册请求参数获取一个地址对，如果失败则回复用户注册失败 */
    if (VOS_FALSE == IMSA_RegGetAddrByParamType(pstEntity->enRegType, pstRegReq->enAddrType, aucUeAddr, aucPcscfAddr))
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR, IMSA_RESULT_ACTION_NULL);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_RegErrRecord(pstEntity->enRegType, IMSA_ERR_LOG_REG_FAIL_REASON_NO_ADDR_PAIR);
        IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                 IMSA_ERR_LOG_REG_FAIL_REASON_NO_ADDR_PAIR,
                                 VOS_FALSE,
                                 VOS_FALSE,
                                 IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_REG_ADDR_PAIR);
        #endif
        return VOS_FALSE;
    }

    IMSA_CONN_UpdateNicPdpInfo();

    /* 发送注册命令，触发D2 IMS Stack开始进行注册 */
    ulResult = IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);
    if (VOS_FALSE == ulResult)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL, IMSA_RESULT_ACTION_NULL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_RegErrRecord(pstEntity->enRegType, IMSA_ERR_LOG_REG_FAIL_REASON_TRANSPORT);
        #endif
        return VOS_FALSE;
    }

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringImsRegSuccess
 Description    : Registering状态收到注册成功结果的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegSuccess(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegSuccess is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegSuccess_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 通知用户注册成功 */
    (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERED);

    /* 清0重试次数 */
    IMSA_RegResetRetryTimes(pstEntity->enRegType);

    /* 清0周期尝试IMS注册次数 */
    IMSA_RegResetPeriodTryImsRegTimes(pstEntity->enRegType);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegParseImsError
 Description    : 解析IMS上报的reasonDesc字段，转成IMSA希望的结构
 Input          : pstCsmOutputService----------OUTPUT SERVICE消息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-17  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegParseImsError
(
    const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService,
    IMSA_IMS_OUTPUT_ERROR_STRU          *pstImsErrorInfo
)
{
    if (VOS_TRUE == pstOutputService->bitOpErrorCode)
    {
        IMSA_MEM_CPY_S( pstImsErrorInfo,
                        sizeof(IMSA_IMS_OUTPUT_ERROR_STRU),
                        &pstOutputService->stErrorCode,
                        sizeof(IMSA_IMS_OUTPUT_ERROR_STRU));

        return IMSA_SUCC;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_RegParseImsError: HICSM_parseServiceError failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_RegParseImsError_ENUM, LNAS_FAIL);
        return IMSA_FAIL;
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegCalculateRetryDelayTime
 Description    : 计算retry delay time
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-09-30  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegCalculateRetryDelayTime
(
    VOS_UINT32                          ulMaxTime,
    VOS_UINT32                          ulBaseTime,
    VOS_UINT32                          ulConsecutiveFailures
)
{
    VOS_UINT32                          W                   = IMSA_NULL;
    VOS_UINT32                          ulTmp               = IMSA_NULL;
    VOS_UINT32                          ulRetryDelayTime    = IMSA_NULL;

    /*  RFC 5626规定的间隔时间计算公式如下：
    W = min (max-time, (base-time * (2 ^ consecutive-failures)))
    retry delay time = rand * W
    rand是个随机值，取值范围是50%~100%*/
    ulTmp = ulBaseTime * (VOS_UINT32)pow(2.0, (double)ulConsecutiveFailures);

    if (ulMaxTime >= ulTmp)
    {
        W = ulTmp;
    }
    else
    {
        W = ulMaxTime;
    }

    ulRetryDelayTime = (VOS_UINT32)(((VOS_Rand(51) + 50) / 100.0) * W);

    return ulRetryDelayTime;
}


/*****************************************************************************
 Function Name  : IMSA_RegCalculateRegFailureRetryIntervelTime
 Description    : 计算注册失败重新尝试间隔时间
 Input          : ulRetryTimes-----------------尝试次数
                  ulRetryAfter-----------------retry after时长
                  ulIsReRegisteration----------是否为重注册
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
      2.lihong 00150010      2013-10-08  Modify
*****************************************************************************/
VOS_UINT32 IMSA_RegCalculateRegFailureRetryIntervelTime
(
    VOS_UINT32                          ulRetryTimes,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration
)
{
    IMSA_REG_MANAGER_STRU              *pstImsaRegManager   = IMSA_RegCtxGet();
    VOS_UINT32                          ulRetryDelayTime    = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_RegCalculateRegFailureRetryIntervelTime is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegCalculateRegFailureRetryIntervelTime_ENUM, LNAS_ENTRY);

    /* 如果NV项配置间隔固定时长，则返回NV项配置的固定时长； */
    if (pstImsaRegManager->ulRetryPeriod != 0)
    {
        if (ulRetryAfter == 0)
        {
            return (1000 * pstImsaRegManager->ulRetryPeriod);
        }
        else
        {
            return (1000 * ulRetryAfter);
        }
    }

    /* 如果NV项配置间隔非固定时长，根据24.229 5.1.1.2.1章节以及RFC5626
       来计算注册失败重新尝试间隔时间，具体可以参见IMS需求文档2.3.9章节 */
    ulRetryDelayTime = IMSA_RegCalculateRetryDelayTime( pstImsaRegManager->ulMaxTime,
                                                        pstImsaRegManager->ulBaseTime,
                                                        ulRetryTimes);

    /* 如果是第一次初始注册，且不携带retry after，则取值5分钟和retry delay time
       的最小值；协议如下:
       After a first unsuccessful initial registration attempt,  if the Retry-After
       header field was not present and the initial registration was not performed
       as a consequence of a failed reregistration, the UE shall not wait more
       than 5 minutes before attempting a new registration.*/
    if ((1 == ulRetryTimes) && (IMSA_FALSE == ulIsReRegisteration)
       && (0 == ulRetryAfter))
    {
        return 1000 * IMSA_Min(IMSA_REG_FAILURE_RETRY_INTERVEL_5_MIN, ulRetryDelayTime);
    }

    if (0 != ulRetryAfter)
    {
        return 1000 * IMSA_Max(ulRetryAfter, ulRetryDelayTime);
    }
    else
    {
        return (1000 * ulRetryDelayTime);
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut
 Description    : 处理注册过程中IMS上报的注册失败，原因值为TIMERF_OUT；
 Input          : pstEntity--------------------实体信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-10-13  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut
(
    IMSA_REG_ENTITY_STRU               *pstEntity
)
{
    VOS_UINT32                          ulResult                                = VOS_FALSE;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1]    = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut is entered!");

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 获取下一个注册地址对，如果失败则回复用户注册失败 */
    if (VOS_FALSE == IMSA_RegGetAddrByParamType(    pstEntity->enRegType,
                                                    IMSA_REG_ADDR_PARAM_NEXT,
                                                    aucUeAddr,
                                                    aucPcscfAddr))
    {
        if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
        {
            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);

            return;
        }

        /*普通注册，且尝试次数未超过最大次数，则启动周期尝试IMS注册定时器*/
        if (pstEntity->ucTryRegTimes < IMSA_PRIOD_TRY_REG_MAX_TIMES)
        {
            IMSA_RegTimerStart(&pstEntity->stPeriodTryRegTimer, pstEntity->enRegType);

            /* 状态切换 */
            /* IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_PERIOD_TRY); */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_RETRY);

            pstEntity->ucTryRegTimes++;

            /* 释放资源 */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
                /* 停止注册时长保护定时器 */
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
        }
        else
        {
            pstEntity->ucTryRegTimes = 0;

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);
        }

        return;
    }

    IMSA_CONN_UpdateNicPdpInfo();

    /* 发送注册命令，触发IMS Stack开始进行注册 */
    ulResult = IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);
    if (VOS_FALSE == ulResult)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);
        return;
    }

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);

    return;
}



/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringImsRegFailure
 Description    : 处理注册过程中IMS上报的注册失败，原因值为305；
 Input          : pstEntity--------------------实体信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-15  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailure305
(
    IMSA_REG_ENTITY_STRU               *pstEntity
)
{
    VOS_UINT32                          ulResult                                = VOS_FALSE;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1]    = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure305 is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure305_ENUM, LNAS_ENTRY);

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    /* 获取下一个注册地址对，如果失败则回复用户注册失败 */
    if (VOS_FALSE == IMSA_RegGetAddrByParamType(    pstEntity->enRegType,
                                                    IMSA_REG_ADDR_PARAM_NEXT,
                                                    aucUeAddr,
                                                    aucPcscfAddr))
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);

        return ;
    }

    IMSA_CONN_UpdateNicPdpInfo();

    /* 发送注册命令，触发IMS Stack开始进行注册 */
    ulResult = IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);
    if (VOS_FALSE == ulResult)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);
        return ;
    }

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
}

/*****************************************************************************
 Function Name  : IMSA_RegInitRegWaitForRetryCommonProc
 Description    : 初始注册等待重试公共处理
 Input          : pstEntity--------------------实体信息指针
                  ulRetryAfter-----------------retry after
                  usSipStatusCode--------------错误码
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong   00150010      2013-10-11  Draft Enact
      2.zhaochen 00308719      2015-12-19  F项目:将初始注册流程和重注册流程拆分开
*****************************************************************************/
VOS_VOID IMSA_RegInitRegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
)
{
    VOS_UINT32                          ulRetryTimerLen = IMSA_NULL;
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 计算注册失败再尝试间隔时间 */
    ulRetryTimerLen = IMSA_RegCalculateRegFailureRetryIntervelTime( pstEntity->ulRetryTimes,
                                                                    ulRetryAfter,
                                                                    VOS_FALSE);
    if (0 != ulRetryTimerLen)
    {
        /* 启动retry定时器 */
        pstEntity->stRetryTimer.ulTimerLen = ulRetryTimerLen;
        IMSA_RegTimerStart(&pstEntity->stRetryTimer, pstEntity->enRegType);

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_RETRY);

        /* 如果是DSDS流程，则需要先将资源释放，等定时器超时后，再申请资源  */
        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            /* 停止注册时长保护定时器 */
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
        #endif

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                    usSipStatusCode,
                                    ulRetryTimerLen);
        #endif
    }
    else
    {
        /* 调用305处理函数后，会修改注册地址对类型，所以需要先上报CHR */
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                    usSipStatusCode,
                                    ulRetryTimerLen);
        #endif
        IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);
    }

}

/*****************************************************************************
 Function Name  : IMSA_RegWaitForRetryCommonProc
 Description    : 重注册等待重试公共处理
 Input          : pstEntity--------------------实体信息指针
                  ulRetryAfter-----------------retry after
                  usSipStatusCode--------------错误码
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong   00150010      2013-10-11  Draft Enact
      2.zhaochen 00308719      2015-12-19  F项目:将初始注册流程和重注册流程拆分开
*****************************************************************************/
VOS_VOID IMSA_RegReRegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
)
{
    VOS_UINT32                          ulRetryTimerLen = IMSA_NULL;

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 计算注册失败再尝试间隔时间 */
    if (0!= ulRetryAfter)
    {
        ulRetryTimerLen = ulRetryAfter * 1000;
    }

    if (0 != ulRetryTimerLen)
    {
        /* 启动retry定时器 */
        pstEntity->stRetryTimer.ulTimerLen = ulRetryTimerLen;
        IMSA_RegTimerStart(&pstEntity->stRetryTimer, pstEntity->enRegType);

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_RETRY);

        /* 通知SERVICE使用当前参数继续尝试注册 */
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                             IMSA_REG_RESULT_FAIL,
                                             IMSA_RESULT_ACTION_WAIT_RETRY_TIME_OUT);
    }
    else
    {
        /* 通知SERVICE使用当前参数继续尝试注册 */
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                             IMSA_REG_RESULT_FAIL,
                                             IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR);
    }
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                usSipStatusCode,
                                ulRetryTimerLen);
    #endif

}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringImsRegFailureRatNotSup
 Description    : 处理注册过程中IMS上报的注册失败
 Input          : pstEntity--------------------实体信息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailureRatNotSup
(
    IMSA_REG_ENTITY_STRU               *pstEntity
)
{
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
    }
    else
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);
    }

    /* 进入该分支的状态时，在G/W下PS域还没注册成功，但是IMS已经注册失败， */
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                             IMSA_ERR_LOG_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT,
                             VOS_FALSE,
                             VOS_FALSE,
                             IMSA_ERR_LOG_EMC_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT);
    #endif
}
/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringImsRegFailureRatNotSup
 Description    : 处理注册过程中IMS上报的注册失败
 Input          : pstEntity--------------------实体信息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegFailureOthers
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo
)
{
    IMSA_REG_MANAGER_STRU              *pstImsaRegManager   = IMSA_RegCtxGet();

    /* 根据NV配置的再尝试次数，使用当前注册参数再去尝试注册，
       如果NV配置的尝试次数为0，则进行无限次尝试；
       如果NV配置的尝试次数不为0，则进行有效次尝试，当尝试超出有效次时，
       则变换参数后再次发起注册 */
    if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
    {
        /* 停止保护定时器 */
        IMSA_RegTimerStop(&pstEntity->stProtectTimer);

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

        /* 通知SERVICE紧急注册失败 */
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);

        return VOS_TRUE;
    }
    if (0 == pstImsaRegManager->ulSaveRetryTimes)
    {
        IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure: retry limitless times!");
        TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, 1);
        IMSA_RegInitRegWaitForRetryCommonProc( pstEntity,
                                               pstImsErrorInfo->ulRetryAfter,
                                               pstImsErrorInfo->usSipStatusCode);
    }
    else
    {
        if (pstEntity->ulRetryTimes < pstImsaRegManager->ulSaveRetryTimes)
        {
            IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure: retry limitary times!");
            TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, 2);
            IMSA_RegInitRegWaitForRetryCommonProc( pstEntity,
                                                   pstImsErrorInfo->ulRetryAfter,
                                                   pstImsErrorInfo->usSipStatusCode);
        }
        else
        {
            IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure: retry with next addr!");
            TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, 3);
            /* 因为要获取当次注册失败的地址对类型，所以需要再发起下一次注册前，先上报CHR */
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif
            IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);
        }
    }
    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringImsRegFailure
 Description    : 处理注册过程中IMS上报的注册失败
 Input          : pstEntity--------------------实体信息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-15  Draft Enact
      2.lihong 00150010      2013-10-08  Modify:retry time
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegFailure
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulEvt,
    VOS_VOID                           *pData
)
{
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo = VOS_NULL_PTR;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;


    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_RegErrRecord(pstEntity->enRegType, IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE);
    #endif

    /* 尝试次数加1 */
    pstEntity->ulRetryTimes++;

    /* 目前G/W不支持IMS，IMSA不再获取下一个地址发起注册 */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        IMSA_RegFsmProcRegisteringImsRegFailureRatNotSup(pstEntity);
        return VOS_TRUE;
    }

    if (VOS_NULL_PTR == pData)
    {
        IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);

        return VOS_TRUE;
    }

    pstImsErrorInfo = (IMSA_IMS_OUTPUT_ERROR_STRU*)pData;

    /* 处理定制原因值，如果处理完成，则返回 */
    if (IMSA_HANDLED == IMSA_RegProcCustomBuildCause( pstEntity,
                                                  pstImsErrorInfo->ulRetryAfter,
                                                  pstImsErrorInfo->usSipStatusCode))
    {
        return VOS_TRUE;
    }

    switch (pstImsErrorInfo->usSipStatusCode)
    {
        case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT:
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif
            IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut(pstEntity);
            break;
        case IMSA_SIP_NW_ERROR_CAUSE_USE_PROXY:
        /* case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT: */
        case IMSA_SIP_NW_ERROR_CAUSE_UNAUTHORIZED:
        case IMSA_IMS_INT_ERROR_CODE_REGISTER_TIMER_OUT:
            /* 因为要获取当次注册失败的地址对类型，所以需要再发起下一次注册前，先上报CHR */
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif
            IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);
            break;
        case IMSA_SIP_NW_ERROR_CAUSE_REQUEST_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_INTERNAL_ERROR:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_BUSY_EVERYWHERE:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE:

            /* 由于紧急呼是需要考虑接通速度的，所以就不起retry定时器等待了，
               直接回复紧急注册失败，触发SPM去CS域尝试紧急呼 */
            if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
            {
                /* 停止保护定时器 */
                IMSA_RegTimerStop(&pstEntity->stProtectTimer);

                /* 状态切换 */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

                /* 通知SERVICE紧急注册失败 */
                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL_REMOTE,
                                                        IMSA_RESULT_ACTION_NULL);

                #if (FEATURE_ON == FEATURE_PTM)
                IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        VOS_FALSE,
                                        pstImsErrorInfo->usSipStatusCode,
                                        IMSA_ERR_LOG_CALL_STATUS_IDLE);
                #endif
                return VOS_TRUE;
            }

            (VOS_VOID)IMSA_RegFsmProcRegisteringImsRegFailureOthers(pstEntity, pstImsErrorInfo);

            break;

        case IMSA_IMS_INT_ERROR_CODE_TCP_ERROR:
        case IMSA_IMS_INT_ERROR_CODE_IPSEC_ERROR:
            /* 因为要获取当次注册失败的地址对类型，所以需要再发起下一次注册前，先上报CHR */
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif

            /* 如果获取当前正在使用的地址对成功，则使用该地址对重新发起注册 */
            if (VOS_TRUE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                        IMSA_REG_ADDR_PARAM_SAME,
                                                        aucUeAddr,
                                                        aucPcscfAddr))
            {
                /* 停止保护定时器 */
                IMSA_RegTimerStop(&pstEntity->stProtectTimer);

                IMSA_CONN_UpdateNicPdpInfo();

                /* 向D2 IMS发送注册消息 */
                (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

                /* 启动保护定时器 */
                IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

                /* 状态切换 */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
            }
            else
            {
                IMSA_WARN_LOG("IMSA_RegFsmProcRegisteringImsRegFailure:get current para failed!");
                TLPS_PRINT2LAYER_WARNING(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, LNAS_PARAM_INVALID);

                /* 停止保护定时器 */
                IMSA_RegTimerStop(&pstEntity->stProtectTimer);

                /* 状态切换 */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL_TRANSPORT,
                                                        IMSA_RESULT_ACTION_NULL);
            }

            break;
        case IMSA_SIP_NW_ERROR_CAUSE_FORBIDDEN:
            /* 停止保护定时器 */
            IMSA_RegTimerStop(&pstEntity->stProtectTimer);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

            /* 通知SERVICE模块注册失败 */
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL_FORBIDDEN,
                                                    IMSA_RESULT_ACTION_NULL);
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif
            break;
        default:
            (VOS_VOID)IMSA_RegFsmProcRegisteringImsRegFailureOthers(pstEntity, pstImsErrorInfo);
            break;

    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegProcNwNotifyMsgByEvent
 Description    : 根据notify event type进行不同处理
 Input          : pstEntity--------------------实体信息指针
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00150010      2014-12-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegProcNwNotifyMsgByEvent
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_VOID                           *pData
)
{
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo = VOS_NULL_PTR;

    pstImsErrorInfo = (IMSA_IMS_OUTPUT_ERROR_STRU*)pData;

    IMSA_INFO_LOG1("IMSA_RegProcNwNotifyMsgByEvent:", pstImsErrorInfo->ucServerNtyEvent);
    TLPS_PRINT2LAYER_INFO1(IMSA_RegProcNwNotifyMsgByEvent_ENUM, 1, pstImsErrorInfo->ucServerNtyEvent);

    switch (pstImsErrorInfo->ucServerNtyEvent)
    {
        case IMSA_IMS_SERVICE_NOTIFY_EVENT_DEACTED:
            IMSA_RegReRegWaitForRetryCommonProc( pstEntity,
                                            pstImsErrorInfo->ulRetryAfter,
                                            pstImsErrorInfo->usSipStatusCode);
            break;
        case IMSA_IMS_SERVICE_NOTIFY_EVENT_REJED:
        case IMSA_IMS_SERVICE_NOTIFY_EVENT_UNREGED:
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_NULL);
            #if (FEATURE_ON == FEATURE_PTM)
            /* 记录网侧去注册IMS事件 */
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_NW_INIT);
            }
            #endif
            break;
        default:
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_NULL);
            #if (FEATURE_ON == FEATURE_PTM)
            /* 记录网侧去注册IMS事件 */
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_NW_INIT);
            }
            #endif
            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteredImsRegFailureAndRatNotSup
 Description    : 处理已注册状态下IMS上报的注册失败
 Input          : pstEntity--------------------实体信息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegFsmProcRegisteredImsRegFailureAndRatNotSup
(
    IMSA_REG_ENTITY_STRU               *pstEntity
)
{
    if  (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
    }
    else
    {
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_NULL);
    }
    #if (FEATURE_ON == FEATURE_PTM)
    if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
    {
        IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
    }
    #endif
}
/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteredImsRegFailureTimerFOut
 Description    : 处理已注册状态下IMS上报的注册失败
 Input          : pstEntity--------------------实体信息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegFsmProcRegisteredImsRegFailureTimerFOut
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo
)
{
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1]    = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    if (VOS_FALSE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                 IMSA_REG_ADDR_PARAM_NEXT,
                                                 aucUeAddr,
                                                 aucPcscfAddr))
    {
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR);
    }
    else
    {
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);

        IMSA_CONN_UpdateNicPdpInfo();

        /* 向D2 IMS发送注册消息 */
        (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

        /* 启动保护定时器 */
        IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
    }
    #if (FEATURE_ON == FEATURE_PTM)
    if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
    {
        IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                    pstImsErrorInfo->usSipStatusCode,
                                    VOS_FALSE);
    }
    #endif
}
/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteredImsRegFailureOthers
 Description    : 处理已注册状态下IMS上报的注册失败
 Input          : pstEntity--------------------实体信息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegFsmProcRegisteredImsRegFailureOthers
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo
)
{
    IMSA_REG_MANAGER_STRU              *pstImsaRegManager   = IMSA_RegCtxGet();

    /* 根据NV配置的再尝试次数，使用当前注册参数再去尝试注册，
       如果NV配置的尝试次数为0，则进行无限次尝试；
       如果NV配置的尝试次数不为0，则进行有效次数尝试，当尝试超出有效次数时，
       则使用下一组参数尝试注册 */
    if (0 == pstImsaRegManager->ulSaveRetryTimes)
    {
        IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure: retry limitless times!");
        TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, 1);
        IMSA_RegReRegWaitForRetryCommonProc( pstEntity,
                                        pstImsErrorInfo->ulRetryAfter,
                                        pstImsErrorInfo->usSipStatusCode);
    }
    else
    {
        if (pstEntity->ulRetryTimes < pstImsaRegManager->ulSaveRetryTimes)
        {
            IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure: retry limitary times!");
            TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, 2);
            IMSA_RegReRegWaitForRetryCommonProc( pstEntity,
                                            pstImsErrorInfo->ulRetryAfter,
                                            pstImsErrorInfo->usSipStatusCode);
        }
        else
        {
            /* 通知SERVICE使用下一组参数继续尝试注册 */
            IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure: retry with next addr!");
            TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, 3);
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);
            /* 进入该分支的状态时，在G/W下PS域还没注册成功，但是IMS已经注册失败， */
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                            pstImsErrorInfo->usSipStatusCode,
                                            VOS_FALSE);
            }
            #endif
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteredImsRegFailure
 Description    : 处理已注册状态下IMS上报的注册失败
 Input          : pstEntity--------------------实体信息指针
                  ulEvt------------------------事件ID
                  pData------------------------错误信息指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
      2.lihong 00150010      2013-10-08  Modify:retry time
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRegisteredImsRegFailure
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulEvt,
    VOS_VOID                           *pData
)
{
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo   = VOS_NULL_PTR;
    IMSA_REG_REJ_FORBIDDEN_CTRL_STRU   *pstRegRejForbCtrl = IMSA_REG_GetRegRejForbCtrlAddr();

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    /* 尝试次数加1 */
    pstEntity->ulRetryTimes++;

    /* 切换状态 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    /* 目前G/W不支持IMS，IMSA不再获取下一个地址发起注册 */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        IMSA_RegFsmProcRegisteredImsRegFailureAndRatNotSup(pstEntity);
        return VOS_TRUE;
    }

    /* IMS紧急重新注册异常后，无需再发起IMS紧急初始注册，直接进行IMS紧急信令
       承载释放，因为紧急呼已经被释放了 */
    if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
    {
        /* 通知SERVICE不再尝试注册 */
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_NULL);

        return VOS_TRUE;
    }

    if (VOS_NULL_PTR == pData)
    {
        /* 通知SERVICE使用下一组参数继续尝试注册 */
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);

        #if (FEATURE_ON == FEATURE_PTM)
        if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
        {
            IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                        VOS_FALSE,
                                        VOS_FALSE);
        }
        #endif
        return VOS_TRUE;
    }

    pstImsErrorInfo = (IMSA_IMS_OUTPUT_ERROR_STRU*)pData;

    switch (pstImsErrorInfo->usSipStatusCode)
    {
        case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT:

            /* 如果定制NV没有打开，则按照原有流程处理 */
            if (VOS_TRUE != pstRegRejForbCtrl->ucTempForbFeatureFlag)
            {
                IMSA_RegFsmProcRegisteredImsRegFailureTimerFOut(pstEntity, pstImsErrorInfo);
            }

            /* 如果定制NV打开，则按照定制要求的流程处理 */
            else
            {
                IMSA_RegReRegWaitForRetryCommonProc( pstEntity,
                                                     pstImsErrorInfo->ulRetryAfter,
                                                     pstImsErrorInfo->usSipStatusCode);
            }
            break;

        case IMSA_SIP_NW_ERROR_CAUSE_USE_PROXY:
        /* case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT: */

            /* 通知SERVICE使用下一组参数继续尝试注册 */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);
            /* 进入该分支的状态时，在G/W下PS域还没注册成功，但是IMS已经注册失败， */
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                            pstImsErrorInfo->usSipStatusCode,
                                            VOS_FALSE);
            }
            #endif
            break;

        case IMSA_SIP_NW_ERROR_CAUSE_REQUEST_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_INTERNAL_ERROR:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_BUSY_EVERYWHERE:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE:
            IMSA_RegReRegWaitForRetryCommonProc( pstEntity,
                                                 pstImsErrorInfo->ulRetryAfter,
                                                 pstImsErrorInfo->usSipStatusCode);
            break;
        case IMSA_IMS_INT_ERROR_CODE_NOTIFY_DEREGISTER:
            IMSA_RegProcNwNotifyMsgByEvent(pstEntity, pData);
            break;
        case IMSA_IMS_INT_ERROR_CODE_TCP_ERROR:
        case IMSA_IMS_INT_ERROR_CODE_IPSEC_ERROR:

            /* 通知SERVICE使用当前参数继续尝试注册 */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR);
            /* 进入该分支的状态时，在G/W下PS域还没注册成功，但是IMS已经注册失败， */
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                            pstImsErrorInfo->usSipStatusCode,
                                            VOS_FALSE);
            }
            #endif
            break;
        case IMSA_SIP_NW_ERROR_CAUSE_FORBIDDEN:
            /* 通知SERVICE模块不再尝试注册 */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL_FORBIDDEN,
                                                    IMSA_RESULT_ACTION_NULL);
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                            pstImsErrorInfo->usSipStatusCode,
                                            VOS_FALSE);
            }
            #endif
            break;

        default:
            IMSA_RegReRegWaitForRetryCommonProc( pstEntity,
                                                 pstImsErrorInfo->ulRetryAfter,
                                                 pstImsErrorInfo->usSipStatusCode);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringProtectTimeout
 Description    : Registering状态收到保护定时器超时的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRegisteringProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 本地去注册 */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType, VOS_TRUE);

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 设置期望状态 */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    /*保存注册参数*/
    pstEntity->enPendingRegParam = IMSA_REG_ADDR_PARAM_NEXT;

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_ROLLING_BACK);

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_RegErrRecord(pstEntity->enRegType,IMSA_ERR_LOG_REG_FAIL_REASON_TIMEOUT);
    #endif

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteringUserDereg
 Description    : Registering状态收到用户去注册请求的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRegisteringUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 发起去注册 */
    IMSA_RegSendImsMsgDereg(pstDeregReq->enDeRegType, pstDeregReq->ulLocalFlag);

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_DEREGING);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRegisteredUserDereg
 Description    : Registered状态收到用户去注册请求的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRegisteredUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* 去注册D2 IMS */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType,pstDeregReq->ulLocalFlag);

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 切换状态 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_DEREGING);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcDeregingUserDereg
 Description    : Dereging状态收到用户去注册请求的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.x00253310       2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcDeregingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingUserDereg is entered!");

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 去注册D2 IMS */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType,pstDeregReq->ulLocalFlag);

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_RegFsmProcDeregingImsRegFailure
 Description    : Dereging状态收到注册失败结果的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcDeregingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcDeregingImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 通知用户 */
    (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

    /* 切换状态 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcDeregingProtectTimeout
 Description    : Dereging状态收到保护定时器超时的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcDeregingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcDeregingProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /**
     * 如果正在执行的是本地去注册，理论上是不会有超时事件;
     * 如果正在执行的是普通去注册，超时后本地去注册以同步状态并获取更友好的行为
     */

    /* 本地去注册 */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType, VOS_TRUE);

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 保存期望状态 */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_NOT_REGISTER;

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_ROLLING_BACK);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcDeregingUserReg
 Description    : Dereging状态收到用户注册请求的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcDeregingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingUserReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcDeregingUserReg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* 设置期望状态 */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    /* 保存注册参数 */
    pstEntity->enPendingRegParam = pstRegReq->enAddrType;

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_PENDING);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcWaitRetryTimeout
 Description    : WaitRetry状态收到定时器超时的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcWaitRetryTimeout
(
    IMSA_REG_ENTITY_STRU   *pstEntity,
    VOS_UINT32              ulEvt,
    VOS_VOID               *pData
)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1];
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1];

    IMSA_INFO_LOG("IMSA_RegFsmProcWaitRetryTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcWaitRetryTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 如果当前接入类型不支持IMS，不再发起注册 */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

        if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
        }
        else
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_NULL);
        }
        return VOS_TRUE;
    }

    if (VOS_TRUE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                IMSA_REG_ADDR_PARAM_SAME,
                                                aucUeAddr,
                                                aucPcscfAddr))
    {
        switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
        {
            case IMSA_RESOURCE_STATUS_ACTIVE:

                IMSA_CONN_UpdateNicPdpInfo();

                /* 向D2 IMS发送注册消息 */
                (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

                /* 启动保护定时器 */
                IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

                /* 状态切换 */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
                break;
            #if (FEATURE_ON == FEATURE_DSDS)
            case  IMSA_RESOURCE_STATUS_NULL:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP,
                                              IMSA_REG_ADDR_PARAM_SAME,
                                              VOS_FALSE);

                break;
            #endif
            default:
                break;

        }
    }
    else
    {
        /**
         * 不会走到这个分支。原因如果在等待过程中连接断开，CONN会通知SERVICE，
         * SERVICE会通知REG本地去注册，即在WAIT RETRY状态下会受到本地去注册请求；
         * 在WAIT RETRY状态时上层处于REGING，不会再给注册模块发注册请求，
         * 如果出现，那就是SERVICE模块出问题了
         */
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_RegFsmProcWaitRetryUserDereg
 Description    : WaitRetry状态收到用户去注册请求的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcWaitRetryUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcWaitRetryUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcWaitRetryUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 停止重试定时器 */
    IMSA_RegTimerStop(&pstEntity->stRetryTimer);

    /* 通知用户 */
    (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcPendingProtectTimeout
 Description    : Pending状态收到超时消息的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcPendingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcPendingProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 本地去注册 */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType, VOS_TRUE);

    /* 启动保护定时器 */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* 状态切换 */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_ROLLING_BACK);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcPendingUserReg
 Description    : Pending状态收到用户注册请求消息的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcPendingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcPendingUserReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingUserReg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* 保存注册参数 */
    pstEntity->enPendingRegParam = pstRegReq->enAddrType;

    /* 设置期望状态 */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcPendingUserDereg
 Description    : Pending状态收到用户去注册请求消息的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcPendingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcPendingUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* 保存注册参数 */
    pstEntity->ulPendingDeregParam = pstDeregReq->ulLocalFlag;

    /* 设置期望状态 */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_NOT_REGISTER;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcPendingImsRegFailure
 Description    : Pending状态收到注册失败消息的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcPendingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcPendingImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 如果当前状态和期望状态一致，则通知用户 */
    if (IMSA_REG_STATUS_NOT_REGISTER == pstEntity->enExceptedStatus)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);
        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
    }
    /* 如果期望状态是注册，则发起注册 */
    else if (IMSA_REG_STATUS_REGISTERED == pstEntity->enExceptedStatus)
    {
        /* 根据保存的注册参数选取一组地址对进行注册 */
        if (VOS_TRUE == IMSA_RegGetAddrByParamType(pstEntity->enRegType, pstEntity->enPendingRegParam, aucUeAddr, aucPcscfAddr))
        {
            IMSA_CONN_UpdateNicPdpInfo();

            (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

            /* 启动保护定时器 */
            IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
        }
        else
        {
            IMSA_ERR_LOG("IMSA_RegFsmProcPendingImsRegFailure: select address pair failure");
            TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcPendingImsRegFailure_ENUM, LNAS_FAIL);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR, IMSA_RESULT_ACTION_NULL);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
        }
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegFsmProcPendingImsRegFailure: invalid excepted status");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcPendingImsRegFailure_ENUM, IMSA_STATE_ERROR);

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
    }

    return VOS_TRUE;
}

/**
 * 状态机处理函数
 *
 * Roll-back时发生超时的处理，这个场景应该尽量避免发生才对，
 * 因为目前的Roll-back是通过本地去注册来实现的，本地区注册
 * 理论上不应该有超时才对
 *
 * @param[in]   pstEntity   注册实例
 * @param[in]   ulEvt       收到的事件, 参考 #IMSA_REG_EVT_ENUM
 * @param[in]   pData       事件对应的其它参数数据
 */
VOS_UINT32 IMSA_RegFsmProcRollingBackProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 根据期望状态通知用户 */
    switch (pstEntity->enExceptedStatus)
    {
    case IMSA_REG_STATUS_NOT_REGISTER:
        {
            /* 停止保护定时器 */
            IMSA_RegTimerStop(&pstEntity->stProtectTimer);

            /* 通知用户 */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_TIMEOUT, IMSA_RESULT_ACTION_NULL);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
            break;
        }
    case IMSA_REG_STATUS_REGISTERED:
        {
            /* 停止保护定时器 */
            IMSA_RegTimerStop(&pstEntity->stProtectTimer);

            /* 通知用户 */
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_TIMEOUT, IMSA_RESULT_ACTION_NULL);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
            break;
        }
    default:
        IMSA_ERR_LOG("IMSA_RegFsmProcRollingBackProtectTimeout: invalid excepted status");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcRollingBackProtectTimeout_ENUM, IMSA_STATE_ERROR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRollingBackImsRegFailure
 Description    : Roll-back状态收到注册失败消息的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRollingBackImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* 根据期望状态通知用户 */
    switch (pstEntity->enExceptedStatus)
    {
    case IMSA_REG_STATUS_NOT_REGISTER:
        {
            /* 停止保护定时器 */
            IMSA_RegTimerStop(&pstEntity->stProtectTimer);

            /* 通知用户 */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
            break;
        }
    case IMSA_REG_STATUS_REGISTERED:
        IMSA_RegTimerStop(&pstEntity->stProtectTimer);

        /* 如果当前接入类型不支持IMS，不再发起注册 */
        if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
        {
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

            if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
            {
                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL,
                                                        IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
            }
            else
            {
                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL,
                                                        IMSA_RESULT_ACTION_NULL);
            }
            return VOS_TRUE;
        }

        /* 如果期望状态是注册，则根据保存的注册参数选取一组地址对进行注册 */
        if (VOS_TRUE == IMSA_RegGetAddrByParamType(pstEntity->enRegType, pstEntity->enPendingRegParam, aucUeAddr, aucPcscfAddr))
        {
            IMSA_CONN_UpdateNicPdpInfo();

            (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

            /* 启动保护定时器 */
            IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
        }
        else
        {
            IMSA_ERR_LOG("IMSA_RegFsmProcRollingBackImsRegFailure: select address pair failure");
            TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcRollingBackImsRegFailure_ENUM, LNAS_FAIL);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR, IMSA_RESULT_ACTION_NULL);

            /* 状态切换 */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
        }
        break;

    default:
        IMSA_ERR_LOG("IMSA_RegFsmProcRollingBackImsRegFailure: invalid excepted status");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcRollingBackImsRegFailure_ENUM, IMSA_STATE_ERROR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRollingBackUserReg
 Description    : Roll-back状态收到用户注册请求消息的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRollingBackUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackUserReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackUserReg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* 保存注册参数 */
    pstEntity->enPendingRegParam = pstRegReq->enAddrType;

    /* 设置期望状态 */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_RegFsmProcRollingBackUserDereg
 Description    : Roll-back状态收到用户去注册请求消息的处理
 Input          : pstEntity     当前注册实体
                  ulEvt         事件id
                  pData         事件data
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegFsmProcRollingBackUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* 保存注册参数 */
    pstEntity->ulPendingDeregParam = pstDeregReq->ulLocalFlag;

    /* 设置期望状态 */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_NOT_REGISTER;

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_RegEntityGetByType
 Description    : 根据注册类型获取注册实体
 Input          : enRegType     注册类型
 Output         : VOS_VOID
 Return Value   : 获取到的注册实体指针

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_REG_ENTITY_STRU* IMSA_RegEntityGetByType(IMSA_REG_TYPE_ENUM_UINT8 enRegType)
{
    IMSA_REG_MANAGER_STRU *pstRegCtx = IMSA_RegCtxGet();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        return &pstRegCtx->stNormalRegEntity;
    }
    else
    {
        return &pstRegCtx->stEmcRegEntity;
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegProcUserRegReqMsg
 Description    : 处理用户注册请求
 Input          : pRcvMsg     注册请求消息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegProcUserRegReqMsg(const VOS_VOID *pRcvMsg)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;
    IMSA_REG_REG_REQ_STRU *pstRegReqData = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcUserRegReqMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcUserRegReqMsg_ENUM, LNAS_ENTRY);

    pstRegReqData = (IMSA_REG_REG_REQ_STRU *)pRcvMsg;
    pstRegEntity = IMSA_RegEntityGetByType(pstRegReqData->enRegType);

    return IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_USER_REG_REQ, (VOS_VOID *)pstRegReqData);
}

/*****************************************************************************
 Function Name  : IMSA_RegProcUserDeregReqMsg
 Description    : 处理用户去注册请求
 Input          : pRcvMsg     去注册请求消息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegProcUserDeregReqMsg(const VOS_VOID *pRcvMsg)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;
    IMSA_REG_DEREG_REQ_STRU *pstDeregReqData = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcUserDeregReqMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcUserDeregReqMsg_ENUM, LNAS_ENTRY);

    pstDeregReqData = (IMSA_REG_DEREG_REQ_STRU *)pRcvMsg;
    pstRegEntity = IMSA_RegEntityGetByType(pstDeregReqData->enDeRegType);

    return IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_USER_DEREG_REQ, (VOS_VOID *)pstDeregReqData);
}


/*****************************************************************************
 Function Name  : IMSA_RegProcImsMsgState
 Description    : 处理D2上报的注册状态指示
 Input          : pstCsmOutputService     D2上报的Service消息
 Output         : VOS_VOID
 Return Value   : 处理结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegProcImsMsgState(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;
    VOS_UINT32 ulResult = VOS_FALSE;
    IMSA_IMS_OUTPUT_ERROR_STRU                      stImsErrorInfo = {0};

    IMSA_INFO_LOG1("IMSA_RegProcImsMsgState: ", pstOutputService->enServeState);
    TLPS_PRINT2LAYER_INFO1(IMSA_RegProcImsMsgState_ENUM, LNAS_ENTRY, pstOutputService->enServeState);

    if (pstOutputService->ulIsEmergency)
    {
        pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_EMC);
    }
    else
    {
        pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_NORMAL);
    }

    switch (pstOutputService->enServeState)
    {
    case IMSA_IMS_SERVICE_STATE_INACTIVE:
    case IMSA_IMS_SERVICE_STATE_FAILED:
    case IMSA_IMS_SERVICE_STATE_UNKNOWN:

        /* Convert IMS extra parameter to REG data structure */
        ulResult = IMSA_RegParseImsError(pstOutputService, &stImsErrorInfo);

        if (IMSA_SUCC == ulResult)
        {
            ulResult = IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_IMS_REG_FAILURE, &stImsErrorInfo);
        }
        else
        {
            ulResult = IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_IMS_REG_FAILURE, VOS_NULL_PTR);
        }

        break;
    case IMSA_IMS_SERVICE_STATE_ACTIVE:
        ulResult = IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_IMS_REG_SUCCESS, VOS_NULL_PTR);
        break;
    case IMSA_IMS_SERVICE_STATE_REGISTERING:
    case IMSA_IMS_SERVICE_STATE_DEREGISTERING:
    case IMSA_IMS_SERVICE_STATE_ROAMING:
    default:
        IMSA_INFO_LOG1("IMSA_RegProcImsMsgState: state need not handle", pstOutputService->enServeState);
        TLPS_PRINT2LAYER_INFO1(IMSA_RegProcImsMsgState_ENUM, IMSA_STATE_ERROR, pstOutputService->enServeState);
        break;
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_RegProcTimeoutProtect
 Description    : 保护定时器超时处理
 Input          : pTimerMsg     超时定时器
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegProcTimeoutProtect(const VOS_VOID *pTimerMsg)
{
    IMSA_REG_TYPE_ENUM_UINT8 enRegType;
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcTimeoutProtect is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcTimeoutProtect_ENUM, LNAS_ENTRY);

    enRegType = (IMSA_REG_TYPE_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pTimerMsg);

    pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    (VOS_VOID)IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_TIMEOUT_PROTECT, VOS_NULL_PTR);
}

/*****************************************************************************
 Function Name  : IMSA_RegProcTimeoutRetry
 Description    : 重试定时器超时处理
 Input          : pTimerMsg     超时定时器
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegProcTimeoutRetry(const VOS_VOID *pTimerMsg)
{
    IMSA_REG_TYPE_ENUM_UINT8 enRegType;
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcTimeoutRetry is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcTimeoutRetry_ENUM, LNAS_ENTRY);

    enRegType = (IMSA_REG_TYPE_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pTimerMsg);

    pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    (VOS_VOID)IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_TIMEOUT_RETRY, VOS_NULL_PTR);
}

/*****************************************************************************
 Function Name  : IMSA_RegProcCustomBuildCause()
 Description    : 处理定制需求中的原因值流程
 Input          : pstEntity-----------注册实体
                  ulRetryAfter--------Retry-After头
                  usSipStatusCode-----错误原因值
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719     2015-12-19  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegProcCustomBuildCause
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT16                          usSipStatusCode
)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulRetryTimerLen   = IMSA_NULL;
    VOS_UINT32                          ucIsLastParamFlag = VOS_FALSE;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1]    = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_REG_MANAGER_STRU                   *pstImsaRegManager      = IMSA_RegCtxGet();
    IMSA_REG_REJ_FORBIDDEN_CTRL_STRU        *pstRegRejForbCtrl      = IMSA_REG_GetRegRejForbCtrlAddr();
    IMSA_NV_REG_TEMP_REJ_CAUSE_LIST_STRU    *pstRegTempRejCauseList = IMSA_REG_GetRegTempRejCauseListAddr();
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU               *pstControlMagnaer      = IMSA_GetControlManagerAddress();
    #endif

    TLPS_PRINT2LAYER_INFO2(IMSA_RegProcCustomBuildCause_ENUM, IMSA_REG_ERROR_CODE,1 , usSipStatusCode);
    /* 紧急注册失败，直接去CS域尝试 */
    if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
    {
        return IMSA_NOT_HANDLED;
    }

    /* 定制NV没有打开，则不处理 */
    if (VOS_TRUE != pstRegRejForbCtrl->ucTempForbFeatureFlag)
    {
        TLPS_PRINT2LAYER_INFO(IMSA_RegProcCustomBuildCause_ENUM, IMSA_NOT_SUPPORT);
        return IMSA_NOT_HANDLED;
    }

    /* 循环遍历配置的临时原因值列表，如果列表中没有传入的参数的原因值，则不处理 */
    for (i = 0 ; i < pstRegTempRejCauseList->ucSingleCauseNum ; i++)
    {
        TLPS_PRINT2LAYER_INFO2(IMSA_RegProcCustomBuildCause_ENUM, IMSA_REG_ERROR_CODE, 2 , pstRegTempRejCauseList->ausSingleCauseList[i]);
        if (usSipStatusCode == pstRegTempRejCauseList->ausSingleCauseList[i])
        {
            TLPS_PRINT2LAYER_INFO1(IMSA_RegProcCustomBuildCause_ENUM, IMSA_REG_ERROR_CODE, usSipStatusCode);
            break;
        }
    }

    if (i == pstRegTempRejCauseList->ucSingleCauseNum)
    {
        return IMSA_NOT_HANDLED;
    }

    /* 停止保护定时器 */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* 如果Retry-After不为0，则重试定时器时长为Retry-After */
    if (0 != ulRetryAfter)
    {
        ulRetryTimerLen = 1000 * ulRetryAfter;
    }

    /* 如果Retry-After为0，计算注册失败再尝试间隔时间 */
    else
    {
        /* 根据RFC5626来计算注册失败重新尝试间隔时间 */
        ulRetryTimerLen = 1000 * (IMSA_RegCalculateRetryDelayTime( pstImsaRegManager->ulMaxTime,
                                                                  pstImsaRegManager->ulBaseTime,
                                                                  pstEntity->ulRetryTimes));
    }

    /* 取下一个地址对，如果失败，则取第一个地址对 */
    if (VOS_FALSE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                 IMSA_REG_ADDR_PARAM_NEXT,
                                                 aucUeAddr,
                                                 aucPcscfAddr))
    {
        TLPS_PRINT2LAYER_INFO(IMSA_RegProcCustomBuildCause_ENUM, IMSA_NO_ADDR_PAIR);
        (VOS_VOID)IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                     IMSA_REG_ADDR_PARAM_NEW,
                                     aucUeAddr,
                                     aucPcscfAddr);

        /* 如果所有地址对都尝试过了，则记录标志，在Retry-After不存在时计算定时器时长 */
        ucIsLastParamFlag = VOS_TRUE;
    }

    /* 如果Retry-After不存在，且不是所有地址对都尝试过了的情况，则不启动定时器，直接发起下一次尝试 */
    if ((0 == ulRetryAfter) && (VOS_FALSE == ucIsLastParamFlag))
    {
        /* 上报CHR */
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                    usSipStatusCode,
                                    0);
        #endif

        IMSA_CONN_UpdateNicPdpInfo();

        /* 向D2 IMS发送注册消息 */
        (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

        /* 启动保护定时器 */
        IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
    }

    /* 其他情况，根据计算结果启动重试定时器 */
    else
    {
        /* 启动retry定时器 */
        pstEntity->stRetryTimer.ulTimerLen = ulRetryTimerLen;
        IMSA_RegTimerStart(&pstEntity->stRetryTimer, pstEntity->enRegType);

        /* 如果是DSDS流程，则需要先将资源释放，等定时器超时后，再申请资源  */
        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            /* 停止注册时长保护定时器 */
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
        #endif

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_RETRY);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                    usSipStatusCode,
                                    ulRetryTimerLen);
        #endif

    }
    return IMSA_HANDLED;
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairCreate
 Description    : 创建一个地址对实例
 Input          : enIpType     地址对地址类型，IPv4或者IPv6
                  pacUeAddr    UE地址
                  pacPcscfAddr PCSCF地址
 Output         : VOS_VOID
 Return Value   : 地址对实例指针，如果创建失败，则返回VOS_NULL_PTR

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairCreate(IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                const VOS_CHAR *pacUeAddr,
                                                const VOS_CHAR *pacPcscfAddr)
{
    IMSA_REG_ADDR_PAIR_STRU *pstAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairCreate is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairCreate_ENUM, LNAS_ENTRY);

    pstAddrPair = (IMSA_REG_ADDR_PAIR_STRU*)IMSA_MEM_ALLOC(sizeof(IMSA_REG_ADDR_PAIR_STRU));
    if (pstAddrPair != VOS_NULL_PTR)
    {
        IMSA_MEM_SET_S( pstAddrPair,
                        sizeof(IMSA_REG_ADDR_PAIR_STRU),
                        0,
                        sizeof(IMSA_REG_ADDR_PAIR_STRU));

        pstAddrPair->ucHasTryed = VOS_FALSE;
        pstAddrPair->enIpType = enIpType;
        IMSA_UtilStrNCpy(pstAddrPair->acUeAddr, pacUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(pstAddrPair->acPcscfAddr, pacPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }

    return pstAddrPair;
}


/*****************************************************************************
 Function Name  : IMSA_RegAddrPairDestroy
 Description    : 销毁一个地址对实例
 Input          : pstAddrPair  待销毁的地址对实例指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegAddrPairDestroy(IMSA_REG_ADDR_PAIR_STRU *pstAddrPair)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairDestroy is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairDestroy_ENUM, LNAS_ENTRY);

    if (pstAddrPair)
    {
        IMSA_MEM_FREE(pstAddrPair);
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairListAdd
 Description    : 向地址对列表中添加一个新的地址对，新的地址对会被添加到列表的尾部
 Input          : ppstListHead  指向地址对列表的指针
                  pstNode       新添加的地址对
 Output         : VOS_VOID
 Return Value   : 成功添加的地址对指针

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListAdd(IMSA_REG_ADDR_PAIR_STRU **ppstListHead, IMSA_REG_ADDR_PAIR_STRU *pstNode)
{
    IMSA_REG_ADDR_PAIR_STRU *pstTmp = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairListAdd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListAdd_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == *ppstListHead)
    {
        *ppstListHead = pstNode;

        pstNode->pstNext = VOS_NULL_PTR;
    }
    else
    {
        pstTmp = *ppstListHead;
        while (VOS_NULL_PTR != pstTmp->pstNext)
        {
            pstTmp = pstTmp->pstNext;
        }
        pstTmp->pstNext = pstNode;

        pstNode->pstNext = VOS_NULL_PTR;
    }

    return pstNode;
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairListDestroy
 Description    : 销毁整个地址对列表
 Input          : pstListHead   待销毁的地址对列表
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegAddrPairListDestroy(IMSA_REG_ADDR_PAIR_STRU *pstListHead)
{
    IMSA_REG_ADDR_PAIR_STRU *pstTmpAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairListDestroy is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListDestroy_ENUM, LNAS_ENTRY);

    while (pstListHead)
    {
        pstTmpAddrPair = pstListHead;
        pstListHead = pstListHead->pstNext;

        IMSA_RegAddrPairDestroy(pstTmpAddrPair);
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairMgrInit
 Description    : 地址对管理模块初始化
 Input          : pstPairMgr   待初始化的地址对管理模块
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegAddrPairMgrInit(IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairMgrInit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrInit_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET_S( pstPairMgr,
                    sizeof(IMSA_REG_ADDR_PAIR_MGR_STRU),
                    0,
                    sizeof(IMSA_REG_ADDR_PAIR_MGR_STRU));
}


/*****************************************************************************
 Function Name  : IMSA_RegAddrPairMgrDeinit
 Description    : 地址对管理模块去初始化
 Input          : pstPairMgr   待去初始化的地址对管理模块
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegAddrPairMgrDeinit(const IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairMgrDeinit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrDeinit_ENUM, LNAS_ENTRY);

    IMSA_RegAddrPairListDestroy(pstPairMgr->pstIpv6List);
    IMSA_RegAddrPairListDestroy(pstPairMgr->pstIpv4List);
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr
 Description    : 根据新加入的PCSCF和当前UE地址更新地址对列表
 Input          : pstAddrPairMgr    地址对管理模块
                  enIpType          新加入的PCSCF地址类型
                  pacPcscfAddr      新加入的PCSCF地址
 Output         : VOS_VOID
 Return Value   : 更新结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr(IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
                                                     IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                     const VOS_CHAR *pacPcscfAddr)
{
    VOS_CHAR *pacDstAddr = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU *pstNewPair = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU **ppstDstPairList = VOS_NULL_PTR;
    VOS_UINT8 ulResult = VOS_FALSE;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr_ENUM, LNAS_ENTRY);

    /* 根据PCSCF地址类型决定要更新哪个列表以及使用哪个UE地址 */
    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        pacDstAddr = pstAddrPairMgr->acUeAddrIpv4;
        ppstDstPairList = &pstAddrPairMgr->pstIpv4List;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        pacDstAddr = pstAddrPairMgr->acUeAddrIpv6;
        ppstDstPairList = &pstAddrPairMgr->pstIpv6List;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr_ENUM, IMSA_IP_TYPE_ERROR);
        return VOS_FALSE;
    }

    if (0 != VOS_StrLen(pacDstAddr))
    {
        pstNewPair = IMSA_RegAddrPairCreate(enIpType, pacDstAddr, pacPcscfAddr);
        if (pstNewPair)
        {
            (VOS_VOID)IMSA_RegAddrPairListAdd(ppstDstPairList, pstNewPair);

            ulResult = VOS_TRUE;
        }
        else
        {
            IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr: alloc memory fail");
            TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr_ENUM, LNAS_NULL_PTR);
        }
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairMgrUpdateWithNewUeAddr
 Description    : 根据新加入的UE地址和已有的PCSCF地址更新地址对列表
 Input          : pstAddrPairMgr    地址对管理模块
                  enIpType          新加入的UE地址类型
                  pacPcscfAddr      新加入的UE地址
 Output         : VOS_VOID
 Return Value   : 更新结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewUeAddr(IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
                                                  IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                  const VOS_CHAR *pacUeAddr)
{
    IMSA_REG_ADDR_PAIR_STRU *pstNewPair = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU **ppstDstPairList = VOS_NULL_PTR;
    VOS_UINT8 ulResult = VOS_FALSE;
    VOS_UINT8 i = 0;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrUpdateWithNewUeAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrUpdateWithNewUeAddr_ENUM, LNAS_ENTRY);

    /* 根据地址类型选择要更新的列表 */
    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        ppstDstPairList = &pstAddrPairMgr->pstIpv4List;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        ppstDstPairList = &pstAddrPairMgr->pstIpv6List;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewUeAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewUeAddr_ENUM, IMSA_IP_TYPE_ERROR);
        return VOS_FALSE;
    }

    for (i = 0; i < IMSA_PCSCF_MAX_NUM; i++)
    {
        /* 选取地址类型匹配的PCSCF来生成新的地址对 */
        if ((0 != VOS_StrLen(pstAddrPairMgr->astPcscfs[i].acIpAddr)) &&
            (pstAddrPairMgr->astPcscfs[i].enIpType == enIpType))
        {
            pstNewPair = IMSA_RegAddrPairCreate(enIpType, pacUeAddr, pstAddrPairMgr->astPcscfs[i].acIpAddr);
            if (pstNewPair)
            {
                (VOS_VOID)IMSA_RegAddrPairListAdd(ppstDstPairList, pstNewPair);

                ulResult = VOS_TRUE;
            }
            else
            {
                IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewUeAddr: alloc memory fail");
                TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewUeAddr_ENUM, LNAS_NULL_PTR);
            }
        }
    }

    return ulResult;
}

VOS_UINT32 IMSA_RegAddrPairMgrAddPcscfAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                           IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                           IMSA_PCSCF_SRC_TYPE_UINT8 enSrcType,
                                           const VOS_CHAR *pacIpAddr)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    VOS_UINT8 i = 0;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrAddPcscfAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrAddPcscfAddr_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_PCSCF_MAX_NUM; i++)
    {
        if (0 == VOS_StrLen(pstRegEntity->stPairMgrCtx.astPcscfs[i].acIpAddr))
        {
            /* 寻找未使用的空间存储新加入的PCSCF地址 */
            pstRegEntity->stPairMgrCtx.astPcscfs[i].enIpType = enIpType;
            pstRegEntity->stPairMgrCtx.astPcscfs[i].enSrcType = enSrcType;

            IMSA_UtilStrNCpy(pstRegEntity->stPairMgrCtx.astPcscfs[i].acIpAddr, pacIpAddr, IMSA_IPV6_ADDR_STRING_LEN);

            /* 使用新的PCSCF地址更新地址对列表 */
            (VOS_VOID)IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr(&pstRegEntity->stPairMgrCtx, enIpType, pacIpAddr);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_RegGetAddrPairListHead
 Description    : 获取地址对列表头指针
 Input          : ulRegType-----------------注册类型
                  enIpType------------------IP类型
                  pppstListHead--------------地址对列表头指针的指针的指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegGetAddrPairListHead
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    IMSA_REG_ADDR_PAIR_STRU          ***pppstListHead
)
{
    IMSA_REG_ADDR_PAIR_MGR_STRU        *pstAddrPairMgr      = VOS_NULL_PTR;
    IMSA_REG_ENTITY_STRU               *pstRegEntity        = IMSA_RegEntityGetByType(ulRegType);

    IMSA_INFO_LOG("IMSA_RegGetAddrPairListHead is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegGetAddrPairListHead_ENUM, LNAS_ENTRY);

    pstAddrPairMgr = &pstRegEntity->stPairMgrCtx;

    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        if (VOS_NULL_PTR == pstAddrPairMgr->pstIpv4List)
        {
            return ;
        }

        *pppstListHead = &pstAddrPairMgr->pstIpv4List;
    }
    else
    {
        if (VOS_NULL_PTR == pstAddrPairMgr->pstIpv6List)
        {
            return ;
        }

        *pppstListHead = &pstAddrPairMgr->pstIpv6List;
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairMgrRmvPcscfAddr
 Description    : 删除P-CSCF地址
 Input          : ulRegType-----------------注册类型
                  enIpType------------------IP类型
                  pacIpAddr-----------------P-CSCF地址指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegAddrPairMgrRmvPcscfAddr
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    VOS_CHAR                           *pacIpAddr
)
{
    VOS_UINT32                          i                   = IMSA_NULL;
    IMSA_REG_ENTITY_STRU               *pstRegEntity        = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU        *pstAddrPairMgr      = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU            *pstTmpAddrPairPrior = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU            *pstTmpAddrPair      = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU           **ppstListHead        = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrRmvPcscfAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrRmvPcscfAddr_ENUM, LNAS_ENTRY);

    pstAddrPairMgr = &pstRegEntity->stPairMgrCtx;

    /* 如果去除的连接涉及到当前正在使用的地址对，CONN模块会负责通知SERVICE模块
       连接释放或者当前注册参数失效，SERVICE模会再通知注册模块本地去注册；地址对
       的管理只需要删除P-CSCF地址信息和关联的地址对即可 */

    /* 如果当前注册参数中的P-CSCF地址与入参相同，则清除current指针 */
    if (pstAddrPairMgr->pstCurrent != VOS_NULL_PTR)
    {
        if ((0 == VOS_StrCmp(pstAddrPairMgr->pstCurrent->acPcscfAddr, pacIpAddr))
            && (pstAddrPairMgr->pstCurrent->enIpType == enIpType))
        {
            pstAddrPairMgr->pstCurrent = VOS_NULL_PTR;
        }
    }

    /* 清除存储的P-CSCF地址信息 */
    for (i = 0; i < IMSA_PCSCF_MAX_NUM; i++)
    {
        if (0 == VOS_StrLen(pstAddrPairMgr->astPcscfs[i].acIpAddr))
        {
            continue ;
        }

        if ((0 == VOS_StrCmp(pstAddrPairMgr->astPcscfs[i].acIpAddr, pacIpAddr))
            && (pstAddrPairMgr->astPcscfs[i].enIpType == enIpType))
        {
            IMSA_MEM_SET_S( &pstAddrPairMgr->astPcscfs[i],
                            sizeof(IMSA_REG_PCSCF_STRU),
                            0,
                            sizeof(IMSA_REG_PCSCF_STRU));
        }
    }

    IMSA_RegGetAddrPairListHead(ulRegType, enIpType, &ppstListHead);

    if (VOS_NULL_PTR == ppstListHead)
    {
        return IMSA_SUCC;
    }

    /* 清除入参P-CSCF相关的地址对 */

    /* 如果要删除的地址对是列表的第一个记录 */
    pstTmpAddrPair = *ppstListHead;
    if ((0 == VOS_StrCmp(pstTmpAddrPair->acPcscfAddr, pacIpAddr))
            && (pstTmpAddrPair->enIpType == enIpType))
    {
        /* 修改表头 */
        *ppstListHead = pstTmpAddrPair->pstNext;

         IMSA_RegAddrPairDestroy(pstTmpAddrPair);

         return IMSA_SUCC;
    }

    pstTmpAddrPairPrior = pstTmpAddrPair;
    pstTmpAddrPair      = pstTmpAddrPair->pstNext;
    while (pstTmpAddrPair != VOS_NULL_PTR)
    {
        if ((0 == VOS_StrCmp(pstTmpAddrPair->acPcscfAddr, pacIpAddr))
            && (pstTmpAddrPair->enIpType == enIpType))
        {
            /* 将当前地址对从列表中删除 */
            pstTmpAddrPairPrior->pstNext = pstTmpAddrPair->pstNext;

            IMSA_RegAddrPairDestroy(pstTmpAddrPair);

            return IMSA_SUCC;
        }

        pstTmpAddrPairPrior = pstTmpAddrPair;
        pstTmpAddrPair      = pstTmpAddrPair->pstNext;
    }

    return IMSA_SUCC;
}

VOS_UINT32 IMSA_RegAddrPairMgrAddUeAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                        IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                        const VOS_CHAR *pacIpAddr)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    VOS_CHAR *pacDstAddr = VOS_NULL_PTR;
    VOS_UINT32 ulResult = VOS_FALSE;
    VOS_UINT32      ulLength = 0;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrAddUeAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrAddUeAddr_ENUM, LNAS_ENTRY);

    /* 根据地址类型选取要存储的地址 */
    if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        pacDstAddr = (VOS_CHAR *)pstRegEntity->stPairMgrCtx.acUeAddrIpv6;
        ulLength = IMSA_IPV6_ADDR_STRING_LEN;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        pacDstAddr = (VOS_CHAR *)pstRegEntity->stPairMgrCtx.acUeAddrIpv4;
        ulLength = IMSA_IPV4_ADDR_STRING_LEN;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrAddUeAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrAddUeAddr_ENUM, IMSA_IP_TYPE_ERROR);
        return VOS_FALSE;
    }

    /* 如果目标地址未使用，则存储新的UE地址 */
    if (0 == VOS_StrLen(pacDstAddr))
    {
        IMSA_UtilStrNCpy(pacDstAddr, pacIpAddr, ulLength);

        /* 使用新加入的UE地址更新地址对列表 */
        (VOS_VOID)IMSA_RegAddrPairMgrUpdateWithNewUeAddr(&pstRegEntity->stPairMgrCtx, enIpType, pacIpAddr);

        ulResult = VOS_TRUE;
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_RegAddrPairMgrRmvUeAddrs
 Description    : 删除IP地址
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-16  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegAddrPairMgrRmvUeAddr
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    VOS_CHAR                           *pacIpAddr
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity        = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU        *pstAddrPairMgr      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrRmvUeAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrRmvUeAddr_ENUM, LNAS_ENTRY);

    (VOS_VOID)pacIpAddr;

    pstAddrPairMgr = &pstRegEntity->stPairMgrCtx;

    /* 如果去除的连接涉及到当前正在使用的地址对，CONN模块会负责通知SERVICE模块
       连接释放或者当前注册参数失效，SERVICE模会再通知注册模块本地去注册；地址对
       的管理只需要删除IP地址信息和关联的地址对即可 */

    /* 如果当前注册参数中的IP地址与入参相同，则清除current指针 */
    if (pstAddrPairMgr->pstCurrent != VOS_NULL_PTR)
    {
        if (pstAddrPairMgr->pstCurrent->enIpType == enIpType)
        {
            pstAddrPairMgr->pstCurrent = VOS_NULL_PTR;
        }
    }

    /* 清除存储的IP地址信息 */
    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        IMSA_MEM_SET_S( pstAddrPairMgr->acUeAddrIpv4,
                        IMSA_IPV4_ADDR_STRING_LEN + 1,
                        0x0,
                        IMSA_IPV4_ADDR_STRING_LEN + 1);

        IMSA_RegAddrPairListDestroy(pstAddrPairMgr->pstIpv4List);

        pstAddrPairMgr->pstIpv4List = VOS_NULL_PTR;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        IMSA_MEM_SET_S( pstAddrPairMgr->acUeAddrIpv6,
                        IMSA_IPV6_ADDR_STRING_LEN + 1,
                        0x0,
                        IMSA_IPV6_ADDR_STRING_LEN + 1);

        IMSA_RegAddrPairListDestroy(pstAddrPairMgr->pstIpv6List);
        pstAddrPairMgr->pstIpv6List = VOS_NULL_PTR;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrRmvUeAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrRmvUeAddr_ENUM, IMSA_IP_TYPE_ERROR);
    }

    return IMSA_SUCC;
}

VOS_UINT32 IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                         VOS_CHAR  *pacUeAddr,
                                         VOS_CHAR  *pacPcscfAddr)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrMgr = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU *pstDstAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrGetCurrent is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrGetCurrent_ENUM, LNAS_ENTRY);

    pstAddrMgr = &pstRegEntity->stPairMgrCtx;

    pstDstAddrPair = pstAddrMgr->pstCurrent;

    /* 返回结果 */
    if (VOS_NULL_PTR == pstDstAddrPair)
    {
        return VOS_FALSE;
    }
    else
    {
        IMSA_UtilStrNCpy(pacUeAddr, pstDstAddrPair->acUeAddr, IMSA_IPV6_ADDR_STRING_LEN + 1);
        IMSA_UtilStrNCpy(pacPcscfAddr, pstDstAddrPair->acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN + 1);

        IMSA_INFO_LOG(pacUeAddr);
        IMSA_INFO_LOG(pacPcscfAddr);

        return VOS_TRUE;
    }
}

VOS_VOID IMSA_RegAddrPairListClearAllUsedFlag(IMSA_REG_ADDR_PAIR_STRU *pstList)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairListClearAllUsedFlag is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListClearAllUsedFlag_ENUM, LNAS_ENTRY);

    while (pstList)
    {
        pstList->ucHasTryed = VOS_FALSE;

        pstList = pstList->pstNext;
    }
}


VOS_VOID IMSA_RegAddrPairMgrClearAllUsedFlag(IMSA_REG_TYPE_ENUM_UINT8 enRegType)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrClearAllUsedFlag is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrClearAllUsedFlag_ENUM, LNAS_ENTRY);

    IMSA_RegAddrPairListClearAllUsedFlag(pstRegEntity->stPairMgrCtx.pstIpv4List);
    IMSA_RegAddrPairListClearAllUsedFlag(pstRegEntity->stPairMgrCtx.pstIpv6List);
}

IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListGetNextUnused(IMSA_REG_ADDR_PAIR_STRU *pstList)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairListGetNextUnused is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListGetNextUnused_ENUM, LNAS_ENTRY);

    while (pstList)
    {
        if (VOS_FALSE == pstList->ucHasTryed)
        {
            return pstList;
        }

        pstList = pstList->pstNext;
    }

    return VOS_NULL_PTR;
}

IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairMgrGetFirst(IMSA_REG_TYPE_ENUM_UINT8 ulRegType)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrGetFirst is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrGetFirst_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR != pstRegEntity->stPairMgrCtx.pstIpv6List)
    {
        pstRegEntity->stPairMgrCtx.pstCurrent = pstRegEntity->stPairMgrCtx.pstIpv6List;

        return pstRegEntity->stPairMgrCtx.pstIpv6List;
    }
    else if (VOS_NULL_PTR != pstRegEntity->stPairMgrCtx.pstIpv4List)
    {
        pstRegEntity->stPairMgrCtx.pstCurrent = pstRegEntity->stPairMgrCtx.pstIpv4List;

        return pstRegEntity->stPairMgrCtx.pstIpv4List;
    }
    else
    {
        return VOS_NULL_PTR;
    }
}

VOS_UINT32 IMSA_RegAddrPairMgrGetNextUnused(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                            VOS_CHAR *pacUeIp,
                                            VOS_CHAR *pacPcscfIp)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrMgr = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU *pstDstAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrGetNextUnused is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrGetNextUnused_ENUM, LNAS_ENTRY);

    pstAddrMgr = &pstRegEntity->stPairMgrCtx;

    /* 如果还没有当前地址对，则从地址列表中第一个开始 */
    if (VOS_NULL_PTR == pstAddrMgr->pstCurrent)
    {
        pstDstAddrPair = IMSA_RegAddrPairMgrGetFirst(ulRegType);
    }
    /* 如果已经存在地址列表 */
    else
    {
        /* 如果已经存在当前地址对，则首先将当前地址对设置为已经尝试过 */
        pstAddrMgr->pstCurrent->ucHasTryed = VOS_TRUE;

        /**
         * TODO: 当重新从第一个地址对开始搜索时，
         *       就意味着要将之前已经标记尝试过的地址对全部清除标记吗？
         */

        /**
         * 这里从当前位置开始向后找，目前暂不考虑向前找。
         * 主要是出现优先级高且还未尝试过的地址对在当前地址对之前可能的
         * 场景如：
         *     刚开始使用IPv4地址注册，期间IPv6的连接建立成功，这时新增
         * 的IPv6生成的地址对可能会排到当前使用IPv4的前边。
         * 目前暂不支持这种场景
         */

        /**
         * 如果当前是IPv6，因IPv6优先，所以从当前位置(及IPv6列表)向后查找；
         * 如果IPv6列表未找到，则再尝试从IPv4的列表中查找
         */
        if (IMSA_IP_TYPE_IPV6 == pstAddrMgr->pstCurrent->enIpType)
        {
            pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstCurrent);
            if (VOS_NULL_PTR == pstDstAddrPair)
            {
                pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstIpv4List);
            }
        }
        else
        /**
         * 如果当前是IPv4，因IPv6优先，所以先从IPv6列表中向后查找；
         * 如果IPv6列表未找到，则再尝试从IPv4列表中继续查找
         */
        {
            pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstIpv6List);
            if (VOS_NULL_PTR == pstDstAddrPair)
            {
                pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstCurrent);
            }
        }
    }

    /* 返回结果 */
    if (VOS_NULL_PTR == pstDstAddrPair)
    {
        return VOS_FALSE;
    }
    else
    {
        /* 将current指针指向获取到的地址对地址 */
        pstAddrMgr->pstCurrent = pstDstAddrPair;

        IMSA_UtilStrNCpy(pacUeIp, pstDstAddrPair->acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(pacPcscfIp, pstDstAddrPair->acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);

        IMSA_INFO_LOG(pacUeIp);
        IMSA_INFO_LOG(pacPcscfIp);

        return VOS_TRUE;
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegGetRegedPara
 Description    : 获取注册上的参数
 Input          : ulRegType--------------------注册实体类型
                  pacUeAddr--------------------注册上的IP地址指针
                  pacPcscfAddr-----------------注册上的P-CSCF地址指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-17  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_RegGetRegedPara
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    VOS_CHAR                           *pacUeAddr,
    VOS_CHAR                           *pacPcscfAddr,
    IMSA_IP_TYPE_ENUM_UINT8            *penIptype
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegGetRegedPara is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegGetRegedPara_ENUM, LNAS_ENTRY);

    if ((VOS_NULL_PTR == pacUeAddr) || (VOS_NULL_PTR == pacPcscfAddr)
        || (ulRegType >= IMSA_REG_TYPE_BUTT) || (VOS_NULL_PTR == penIptype))
    {
        IMSA_ERR_LOG("IMSA_RegGetRegedPara:Input Para Illegal");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegGetRegedPara_ENUM, LNAS_PARAM_INVALID);

        return IMSA_FAIL;
    }

    pstRegEntity = IMSA_RegEntityGetByType(ulRegType);

    if ((IMSA_REG_STATUS_REGISTERED != pstRegEntity->enStatus) &&
        (IMSA_REG_STATUS_REGISTERING != pstRegEntity->enStatus))
    {
        return IMSA_FAIL;
    }

    if (VOS_FALSE == IMSA_RegGetAddrByParamType(    ulRegType,
                                                    IMSA_REG_ADDR_PARAM_SAME,
                                                    pacUeAddr,
                                                    pacPcscfAddr))
    {
        return IMSA_FAIL;
    }
    else
    {
        *penIptype = pstRegEntity->stPairMgrCtx.pstCurrent->enIpType;

        return IMSA_SUCC;
    }
}
/*****************************************************************************
 Function Name  : IMSA_RegSaveRegedPara
 Description    : 去激活承载前，存储注册参数
 Input          : ulRegType--------------------注册实体类型
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2014-3-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegSaveRegedPara
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = VOS_NULL_PTR;
    /* IMSA_REG_ENTITY_STRU                   *pstRegEntity        = VOS_NULL_PTR; */
    VOS_UINT32                              ulRslt          = IMSA_FAIL;
    VOS_CHAR                                acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                                acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_IP_TYPE_ENUM_UINT8                 enIpType = IMSA_IP_TYPE_BUTT;

    IMSA_INFO_LOG("IMSA_RegSaveRegedPara is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSaveRegedPara_ENUM, LNAS_ENTRY);

    pstImsaControlManager = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == ulRegType)
    {
        ulRslt = IMSA_RegGetRegedPara(  ulRegType,
                                        acRegUeAddr,
                                        acRegPcscfAddr,
                                        &enIpType);

        /* 如果能获取到注册的参数，则在删除承载信息前进行备份  */
        if (IMSA_FAIL != ulRslt)
        {
            /* 删除承载信息前，备份释放承载的类型和CID */
            pstImsaControlManager->stNrmRegParaInfo.ucCid = ucCid;
            pstImsaControlManager->stNrmRegParaInfo.enIpType = enPdpType;

            /* 备份IP地址 */
            IMSA_MEM_CPY_S( pstImsaControlManager->stNrmRegParaInfo.acUeAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1,
                            acRegUeAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1);

            /* 备份P-CSCF地址 */
            IMSA_MEM_CPY_S( pstImsaControlManager->stNrmRegParaInfo.acPcscfAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1,
                            acRegPcscfAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1);
        }
    }
    else
    {
        ulRslt = IMSA_RegGetRegedPara(  ulRegType,
                                        acRegUeAddr,
                                        acRegPcscfAddr,
                                        &enIpType);

        /* 如果能获取到注册的参数，则在删除承载信息前进行备份  */
        if (IMSA_FAIL != ulRslt)
        {
            /* 删除承载信息前，备份释放承载的类型和CID */
            pstImsaControlManager->stEmcRegParaInfo.ucCid = ucCid;
            pstImsaControlManager->stEmcRegParaInfo.enIpType = enPdpType;

            /* 备份IP地址 */
            IMSA_MEM_CPY_S( pstImsaControlManager->stEmcRegParaInfo.acUeAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1,
                            acRegUeAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1);

            /* 备份P-CSCF地址 */
            IMSA_MEM_CPY_S( pstImsaControlManager->stEmcRegParaInfo.acPcscfAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1,
                            acRegPcscfAddr,
                            IMSA_IPV6_ADDR_STRING_LEN + 1);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_RegEntityInit
 Description    : 初始化注册实体
 Input          : pstRegEntity    待初始化的实体指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegEntityInit(IMSA_REG_ENTITY_STRU *pstRegEntity)
{
    IMSA_INFO_LOG("IMSA_RegEntityInit IMSA_RegEntityInitis entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegEntityInit_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET_S(pstRegEntity, sizeof(IMSA_REG_ENTITY_STRU), 0, sizeof(IMSA_REG_ENTITY_STRU));

    pstRegEntity->stProtectTimer.usName = TI_IMSA_REG_PROTECT;
    pstRegEntity->stProtectTimer.ucMode = VOS_RELTIMER_NOLOOP;
    pstRegEntity->stProtectTimer.ulTimerLen = IMSA_REG_TIMER_LEN_PROTECT;

    pstRegEntity->stRetryTimer.usName = TI_IMSA_REG_RETRY;
    pstRegEntity->stRetryTimer.ucMode = VOS_RELTIMER_NOLOOP;
    pstRegEntity->stRetryTimer.ulTimerLen = IMSA_REG_TIMER_LEN_RETRY;

    pstRegEntity->stPeriodTryRegTimer.usName = TI_IMSA_REG_PERIOD_TRY;
    pstRegEntity->stPeriodTryRegTimer.ucMode = VOS_RELTIMER_NOLOOP;
    pstRegEntity->stPeriodTryRegTimer.ulTimerLen = IMSA_REG_TIMER_LEN_PERIOD_TRY_REG;

    IMSA_RegAddrPairMgrInit(&pstRegEntity->stPairMgrCtx);
}

/*****************************************************************************
 Function Name  : IMSA_RegEntityDeinit
 Description    : 反初始化注册实体
 Input          : pstRegEntity    待反初始化的实体指针
 Output         : VOS_VOID
 Return Value   : 反初始化结果

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-08-31  Modify
*****************************************************************************/
VOS_VOID IMSA_RegEntityDeinit(IMSA_REG_ENTITY_STRU *pstRegEntity)
{
    IMSA_INFO_LOG("IMSA_RegEntityDeinit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegEntityDeinit_ENUM, LNAS_ENTRY);

    if (IMSA_IsTimerRunning(&pstRegEntity->stProtectTimer))
    {
        IMSA_RegTimerStop(&pstRegEntity->stProtectTimer);
    }

    if (IMSA_IsTimerRunning(&pstRegEntity->stRetryTimer))
    {
        IMSA_RegTimerStop(&pstRegEntity->stRetryTimer);
    }

    if (IMSA_IsTimerRunning(&pstRegEntity->stPeriodTryRegTimer))
    {
        IMSA_RegTimerStop(&pstRegEntity->stPeriodTryRegTimer);
    }

    IMSA_RegAddrPairMgrDeinit(&pstRegEntity->stPairMgrCtx);

    IMSA_RegEntityInit(pstRegEntity);
}

/*****************************************************************************
 Function Name  : IMSA_RegMgrInit
 Description    : 注册实体管理上下文初始化
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegMgrInit(VOS_VOID)
{
    IMSA_REG_MANAGER_STRU *pstRegCtx = IMSA_RegCtxGet();

    IMSA_INFO_LOG("IMSA_RegMgrInit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegMgrInit_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET_S(pstRegCtx, sizeof(IMSA_REG_MANAGER_STRU), 0, sizeof(IMSA_REG_MANAGER_STRU));

    IMSA_RegEntityInit(&pstRegCtx->stNormalRegEntity);
    pstRegCtx->stNormalRegEntity.enRegType = IMSA_REG_TYPE_NORMAL;
    IMSA_RegEntityInit(&pstRegCtx->stEmcRegEntity);
    pstRegCtx->stEmcRegEntity.enRegType = IMSA_REG_TYPE_EMC;
}

/*****************************************************************************
 Function Name  : IMSA_RegMgrDeinit
 Description    : 注册实体管理上下文反初始化
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-29  Draft Enact
      2.lihong 00150010    2013-08-31  Modify
*****************************************************************************/
VOS_VOID IMSA_RegMgrDeinit( VOS_VOID )
{
    IMSA_REG_MANAGER_STRU *pstRegCtx = IMSA_RegCtxGet();

    IMSA_INFO_LOG("IMSA_RegMgrDeinit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegMgrDeinit_ENUM, LNAS_ENTRY);

    IMSA_RegEntityDeinit(&pstRegCtx->stNormalRegEntity);
    pstRegCtx->stNormalRegEntity.enRegType = IMSA_REG_TYPE_NORMAL;
    IMSA_RegEntityDeinit(&pstRegCtx->stEmcRegEntity);
    pstRegCtx->stEmcRegEntity.enRegType = IMSA_REG_TYPE_EMC;

    pstRegCtx->stImsMsg.bitOpImsMsg = VOS_FALSE;
}


VOS_VOID IMSA_RegPrintNrmRegState( VOS_VOID )
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_NORMAL);

    switch (pstRegEntity->enStatus)
    {
        case IMSA_REG_STATUS_NOT_REGISTER:
            IMSA_INFO_LOG("Current Normal Reg State: NOT REGISTER");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_REG_STATUS_REGISTERING:
            IMSA_INFO_LOG("Current Normal Reg State: REGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_REG_STATUS_REGISTERED:
            IMSA_INFO_LOG("Current Normal Reg State: REGISTERED");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_REG_STATUS_DEREGING:
            IMSA_INFO_LOG("Current Normal Reg State: DEREGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_REG_STATUS_WAIT_RETRY:
            IMSA_INFO_LOG("Current Normal Reg State: WATI RETRY");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_WAIT_RETRY);
            break;
        case IMSA_REG_STATUS_PENDING:
            IMSA_INFO_LOG("Current Normal Reg State: PENDING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_PENDING);
            break;
        case IMSA_REG_STATUS_ROLLING_BACK:
            IMSA_INFO_LOG("Current Normal Reg State: ROLLING BACK");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_ROLLING_BACK);
            break;
        default:
            IMSA_INFO_LOG("Current Normal Reg State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}


VOS_VOID IMSA_RegPrintEmcRegState( VOS_VOID )
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_EMC);

    switch (pstRegEntity->enStatus)
    {
        case IMSA_REG_STATUS_NOT_REGISTER:
            IMSA_INFO_LOG("Current Emc Reg State: NOT REGISTER");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_REG_STATUS_REGISTERING:
            IMSA_INFO_LOG("Current Emc Reg State: REGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_REG_STATUS_REGISTERED:
            IMSA_INFO_LOG("Current Emc Reg State: REGISTERED");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_REG_STATUS_DEREGING:
            IMSA_INFO_LOG("Current Emc Reg State: DEREGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_REG_STATUS_WAIT_RETRY:
            IMSA_INFO_LOG("Current Emc Reg State: WAIT RETRY");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_WAIT_RETRY);
            break;
        case IMSA_REG_STATUS_PENDING:
            IMSA_INFO_LOG("Current Emc Reg State: PENDING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_PENDING);
            break;
        case IMSA_REG_STATUS_ROLLING_BACK:
            IMSA_INFO_LOG("Current Emc Reg State: ROLLING BACK");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_ROLLING_BACK);
            break;
        default:
            IMSA_INFO_LOG("Current Emc Reg State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_RegGetRegedPara
 Description    : 获取注册上的参数
 Input          : ulRegType--------------------注册实体类型
                  pacUeAddr--------------------注册上的IP地址指针
                  pacPcscfAddr-----------------注册上的P-CSCF地址指针
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2015-12-12  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RegNotifyImsLocalDereg
(
    VOS_VOID
)
{
    /* 去注册D2 IMS */
    IMSA_RegSendImsMsgDereg(IMSA_REG_TYPE_NORMAL, VOS_TRUE);
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_UINT32 IMSA_RegFsmProcWaitRetryResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enParamType
)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1];
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1];
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_REG_ENTITY_STRU *pstEntity = VOS_NULL_PTR;

    pstEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_NORMAL);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    if (IMSA_REG_STATUS_WAIT_RETRY != pstEntity->enStatus)
    {
        return IMSA_FALSE;
    }

    if (VOS_TRUE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                enParamType,
                                                aucUeAddr,
                                                aucPcscfAddr))
    {
        /* 如果获取当前正在使用的地址对成功，则使用该地址对重新发起注册 */
        IMSA_CONN_UpdateNicPdpInfo();

        /* 向D2 IMS发送注册消息 */
        (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

        /* 启动保护定时器 */
        IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

        /* 状态切换 */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);

        IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
    }
    else
    {
        /**
         * 不会走到这个分支。原因如果在等待过程中连接断开，CONN会通知SERVICE，
         * SERVICE会通知REG本地去注册，即在WAIT RETRY状态下会受到本地去注册请求；
         * 在WAIT RETRY状态时上层处于REGING，不会再给注册模块发注册请求，
         * 如果出现，那就是SERVICE模块出问题了
         */

        return IMSA_FALSE;
    }
    return IMSA_TRUE;
}


VOS_VOID IMSA_RegFsmProcWaitRetryResourceApplyExp( VOS_VOID)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_NORMAL);

    /* 需要将注册状态迁移至DEREG状态 */
    IMSA_REG_FSM_STATE_TRANS(pstRegEntity, IMSA_REG_STATUS_NOT_REGISTER);

    /* 通知SERVICE模块，将状态迁移至CONN+DEREG，同时注册资源 */
    IMSA_RegSendIntraMsgRegInd(pstRegEntity->enRegType,
                               IMSA_REG_RESULT_FAIL_REMOTE,
                               IMSA_RESULT_ACTION_REG_NORF);
}
#endif

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : IMSA_SndRegErrLogInfo
 功能描述  : 将IMSA的注册ERROR LOG 信息勾到HIDS
 输入参数  : stImsRegRstEvent   IMS注册失败结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : w00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_SndRegErrLogInfo
(
    IMSA_ERR_LOG_REG_FAIL_STRU  stImsRegRstEvent
)
{
    IMSA_REG_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_REG_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_REG_ERROR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaRegErrlog,
                    sizeof(IMSA_ERR_LOG_REG_FAIL_STRU),
                    &stImsRegRstEvent,
                    sizeof(IMSA_ERR_LOG_REG_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsg);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
/*****************************************************************************
 函 数 名  : IMSA_SndNotInitRegErrLogInfo
 功能描述  : 将IMSA的注册ERROR LOG 信息勾到HIDS
 输入参数  : stImsRegRstEvent   IMS注册失败结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : w00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_SndNotInitRegErrLogInfo
(
    IMSA_ERR_LOG_NOT_INIT_REG_STRU  stImsRegRstEvent
)
{
    IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NOT_INIT_REG_ERR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaNotInitReg,
                    sizeof(IMSA_ERR_LOG_NOT_INIT_REG_STRU),
                    &stImsRegRstEvent,
                    sizeof(IMSA_ERR_LOG_NOT_INIT_REG_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsg);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_SndNormPdnConnFailErrLogInfo
 功能描述  : 将IMSA的注册ERROR LOG 信息勾到HIDS
 输入参数  : stImsRegRstEvent   IMS注册失败结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : w00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_SndNormPdnConnFailErrLogInfo
(
    IMSA_ERR_LOG_PDN_CONN_FAIL_STRU  stImsaPdnConnFail
)
{
    IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NORM_PDN_CONN_REJ_ERR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaPdnConnFail,
                    sizeof(IMSA_ERR_LOG_PDN_CONN_FAIL_STRU),
                    &stImsaPdnConnFail,
                    sizeof(IMSA_ERR_LOG_PDN_CONN_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsg);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_SndNormPdnConnFailErrLogInfo
 功能描述  : 将IMSA的注册ERROR LOG 信息勾到HIDS
 输入参数  : stImsRegRstEvent   IMS注册失败结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : w00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_SndNormRegFailErrLogInfo
(
    IMSA_ERR_LOG_NORM_REG_FAIL_STRU  stImsaNormRegFail
)
{
    IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S(IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NORM_REG_FAIL_ERR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaNormRegFail,
                    sizeof(IMSA_ERR_LOG_NORM_REG_FAIL_STRU),
                    &stImsaNormRegFail,
                    sizeof(IMSA_ERR_LOG_NORM_REG_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsg);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_SndNormInitDeregErrLogInfo
 功能描述  : 将IMSA的注册ERROR LOG 信息勾到HIDS
 输入参数  : stImsRegRstEvent   IMS注册失败结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : w00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_SndNormInitDeregErrLogInfo
(
    IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU  stImsaNormInitDereg
)
{
    IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NORM_REG_FAIL_ERR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaInitDereg,
                    sizeof(IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU),
                    &stImsaNormInitDereg,
                    sizeof(IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsg);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_PdnRejErrRecord
 功能描述  : 记录PDN建链被拒事件
 输入参数  : enPdnConnRejCause  PDN被拒原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_PdnRejErrRecord
(
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enPdnConnRejCause
)
{
    IMSA_ERR_LOG_REG_FAIL_STRU                              stImsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;


    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_REG_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* 模块异常不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_REG_FAIL_STRU);

    /* 填充CS注册失败异常信息 */
    IMSA_MEM_SET_S(&stImsRegRstEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsRegRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_REG_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 枚举值需要转换 */
    stImsRegRstEvent.enRegisterReason       = IMSA_ERR_LOG_REGISTER_REASON_BUTT;
    stImsRegRstEvent.enRegFailReason        = IMSA_ERR_LOG_REG_FAIL_REASON_BUTT;
    stImsRegRstEvent.enVopsStatus           = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsRegRstEvent.enPdnConnRejCause      = enPdnConnRejCause;
    stImsRegRstEvent.enPdnConnStatus        = IMSA_ConnState2ErrlogConnState(IMSA_CONN_GetNormalConnStatus());
    stImsRegRstEvent.enPsServiceStatus      = IMSA_PsSerStates2ErrlogPsStates(IMSA_GetPsServiceStatus());

    if (VOS_FALSE == pstControlMagnaer->ucImsaUsimStatus)
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_UNAVAILABLE;
    }
    else
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_AVAILABLE;
    }

    /* 勾包到HIDS */
    IMSA_SndRegErrLogInfo(stImsRegRstEvent);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_PdnRejErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_PdnRejErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}
/*****************************************************************************
 函 数 名  : IMSA_RegErrRecord
 功能描述  : 记录IMSA注册失败事件
 输入参数  : enRegFailReason  注册失败原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_RegErrRecord
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8 enRegFailReason
)
{
    IMSA_ERR_LOG_REG_FAIL_STRU                              stImsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};


    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_REG_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* 模块异常不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_REG_FAIL_STRU);

    /* 填充CS注册失败异常信息 */
    IMSA_MEM_SET_S(&stImsRegRstEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsRegRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_REG_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 枚举值需要转换 */
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        stImsRegRstEvent.enRegisterReason       = IMSA_RegAddrType2ErrlogRegReason(pstControlMagnaer->enNrmAddrType);
    }
    else
    {
        stImsRegRstEvent.enRegisterReason       = IMSA_RegAddrType2ErrlogRegReason(pstControlMagnaer->enEmcAddrType);
    }
    stImsRegRstEvent.enRegFailReason        = enRegFailReason;
    stImsRegRstEvent.enVopsStatus           = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsRegRstEvent.enPdnConnRejCause      = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    stImsRegRstEvent.enPdnConnStatus        = IMSA_ConnState2ErrlogConnState(IMSA_CONN_GetNormalConnStatus());
    stImsRegRstEvent.enPsServiceStatus      = IMSA_PsSerStates2ErrlogPsStates(IMSA_GetPsServiceStatus());

    if (VOS_FALSE == pstControlMagnaer->ucImsaUsimStatus)
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_UNAVAILABLE;
    }
    else
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_AVAILABLE;
    }

    if (VOS_TRUE == IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_NORMAL, aucUeAddr, aucPcscfAddr))
    {
        IMSA_MEM_CPY_S( stImsRegRstEvent.aucPcscfAddr,
                        IMSA_IPV6_ADDR_STRING_LEN+1,
                        aucPcscfAddr,
                        IMSA_IPV6_ADDR_STRING_LEN+1);
    }
    /* HIDS勾包 */
    IMSA_SndRegErrLogInfo(stImsRegRstEvent);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_NotInitRegErrRecord
 功能描述  : 记录IMSA不发起注册的原因值
 输入参数  : enRegFailReason  注册失败原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_NotInitRegErrRecord
(
    VOS_VOID
)
{
    IMSA_ERR_LOG_NOT_INIT_REG_STRU      stImsNotInitRegEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;


    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_NOT_INIT_REG_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* 模块异常不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_NOT_INIT_REG_STRU);

    /* 填充CS注册失败异常信息 */
    IMSA_MEM_SET_S(&stImsNotInitRegEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNotInitRegEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_NOT_INIT_REG_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    /* 枚举值需要转换 */
    stImsNotInitRegEvent.stRegConditionStatus.enVopsStatus               = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsNotInitRegEvent.stRegConditionStatus.enPsServiceStatus          = IMSA_PsSerStates2ErrlogPsStates(IMSA_GetPsServiceStatus());
    stImsNotInitRegEvent.stRegConditionStatus.enImsaCampedRatType        = pstControlMagnaer->stImsaNetworkInfo.enImsaCampedRatType;
    stImsNotInitRegEvent.stRegConditionStatus.enVoiceDomain              = (IMSA_ERR_LOG_VOICE_DOMAIN_ENUM_UINT8)pstControlMagnaer->stImsaConfigPara.enVoiceDomain;
    stImsNotInitRegEvent.stRegConditionStatus.ucImsSupportFlag           = (VOS_UINT8)IMSA_SRV_IsCurRatSupportIms();
    stImsNotInitRegEvent.stRegConditionStatus.ucIsSupportRoamNotRegFlag  = pstControlMagnaer->stImsaConfigPara.ucRoamingImsNotSupportFlag;
    stImsNotInitRegEvent.stRegConditionStatus.ucIsRoamingFlag            = pstControlMagnaer->stImsaNetworkInfo.ucImsaRoamingFlg;
    stImsNotInitRegEvent.stRegConditionStatus.ucIsImsRegForbidden        = IMSA_GetIsImsRegForbidden();

    if (IMSA_OP_TRUE == pstControlMagnaer->stImsaCommonInfo.bitOpHomeNetDomainName)
    {
        stImsNotInitRegEvent.stRegConditionStatus.ucHomeNetDomainNameValid = IMSA_TRUE;
    }

    if (IMSA_OP_TRUE == pstControlMagnaer->stImsaCommonInfo.stImsaUeId.bitOpImpi)
    {
        stImsNotInitRegEvent.stRegConditionStatus.ucImpiValid = IMSA_TRUE;
    }

    if (IMSA_OP_TRUE == pstControlMagnaer->stImsaCommonInfo.stImsaUeId.bitOpTImpu)
    {
        stImsNotInitRegEvent.stRegConditionStatus.ucImpuValid = IMSA_TRUE;
    }

    if (VOS_FALSE == pstControlMagnaer->ucImsaUsimStatus)
    {
        stImsNotInitRegEvent.stRegConditionStatus.enUsimStatus = IMSA_USIM_STATUS_UNAVAILABLE;
    }
    else
    {
        stImsNotInitRegEvent.stRegConditionStatus.enUsimStatus = IMSA_USIM_STATUS_AVAILABLE;
    }

    /* 如果发起注册的条件状态没有发生变化，则不需要重复上报 */
    if (VOS_FALSE == (IMSA_MEM_CMP(  &stImsNotInitRegEvent.stRegConditionStatus,
                                    &pstControlMagnaer->stRegConditionStatus,
                                    sizeof(IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU))))
    {
        return;
    }

    IMSA_MEM_CPY_S( &pstControlMagnaer->stRegConditionStatus,
                    sizeof(IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU),
                    &stImsNotInitRegEvent.stRegConditionStatus,
                    sizeof(IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU));

    /* HIDS勾包 */
    IMSA_SndNotInitRegErrLogInfo(stImsNotInitRegEvent);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNotInitRegEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_NormPdnConnRejErrRecord
 功能描述  : 记录IMSA发起PDN建链被拒事件
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_NormPdnConnRejErrRecord
(
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32      enPdnConnRejCause,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enNwRejCause
)
{
    IMSA_ERR_LOG_PDN_CONN_FAIL_STRU     stImsNormPdnConnRejEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_PDN_CONN_REJ_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_PDN_CONN_FAIL_STRU);

    /* 填充CS注册失败异常信息 */
    IMSA_MEM_SET_S(&stImsNormPdnConnRejEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNormPdnConnRejEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_PDN_CONN_REJ_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsNormPdnConnRejEvent.enPdnConnRejCause  = enPdnConnRejCause;
    stImsNormPdnConnRejEvent.enNwRejCause       = enNwRejCause;

    /* HIDS勾包 */
    IMSA_SndNormPdnConnFailErrLogInfo(stImsNormPdnConnRejEvent);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNormPdnConnRejEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_NormRegFailErrRecord
 功能描述  : 记录IMSA发起注册失败事件
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_NormRegFailErrRecord
(
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8 enRegFailReason,
    VOS_UINT16                              usSipStatusCode,
    VOS_UINT32                              ulRetryTimerLen
)
{
    IMSA_ERR_LOG_NORM_REG_FAIL_STRU     stImsNormRegEvent;
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_REG_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                   = IMSA_GetControlManagerAddress();
    pstNormalConn                       = IMSA_CONN_GetNormalConnAddr();

    /* 模块异常不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_NORM_REG_FAIL_STRU);

    /* 填充CS注册失败异常信息 */
    IMSA_MEM_SET_S(&stImsNormRegEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNormRegEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_REG_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsNormRegEvent.enImsaCampedRatType   = pstControlMagnaer->stImsaNetworkInfo.enImsaCampedRatType;
    stImsNormRegEvent.enRegisterAddrType    = IMSA_RegAddrType2ErrlogRegReason(pstControlMagnaer->enNrmAddrType);
    stImsNormRegEvent.enRegFailReason       = enRegFailReason;
    stImsNormRegEvent.usSipStatusCode       = usSipStatusCode;
    stImsNormRegEvent.ulRetryTimerLen       = ulRetryTimerLen;
    stImsNormRegEvent.ucIsApnChangeFlag     = pstNormalConn->ucIsApnChanged;

    if (VOS_TRUE == IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_NORMAL, aucUeAddr, aucPcscfAddr))
    {
        IMSA_MEM_CPY_S( stImsNormRegEvent.aucPcscfAddr,
                        IMSA_IPV6_ADDR_STRING_LEN+1,
                        aucPcscfAddr,
                        IMSA_IPV6_ADDR_STRING_LEN+1);
    }

    /* HIDS勾包 */
    IMSA_SndNormRegFailErrLogInfo(stImsNormRegEvent);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNormRegEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_NormInitDeregErrRecord
 功能描述  : 记录IMSA发起去注册事件
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_NormInitDeregErrRecord
(
    IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32  enInitDeregCause
)
{
    IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU  stImsNormInitDeregEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_INIT_DEREG_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* 模块异常不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU);

    /* 填充CS注册失败异常信息 */
    IMSA_MEM_SET_S(&stImsNormInitDeregEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNormInitDeregEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_INIT_DEREG_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsNormInitDeregEvent.enImsaCampedRatType = pstControlMagnaer->stImsaNetworkInfo.enImsaCampedRatType;
    stImsNormInitDeregEvent.enInitDeregCause    = enInitDeregCause;

    /* HIDS勾包 */
    IMSA_SndNormInitDeregErrLogInfo(stImsNormInitDeregEvent);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNormInitDeregEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}
/*****************************************************************************
 函 数 名  : IMSA_RegFailErrLogRecord
 功能描述  : 记录IMSA发起去注册事件
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_PdnConnFailErrLogRecord
(
    IMSA_CONN_TYPE_ENUM_UINT32                      enConnType,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32      enPdnConnRejCause,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enNwRejCause,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enEmcRegFailReason
)
{
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_NormPdnConnRejErrRecord(enPdnConnRejCause,
                                     enNwRejCause);
    }
    else
    {
        IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                enEmcRegFailReason,
                                enNwRejCause,
                                VOS_FALSE,
                                VOS_FALSE,
                                IMSA_ERR_LOG_CALL_STATUS_IDLE);
    }
}

/*****************************************************************************
 函 数 名  : IMSA_RegFailErrLogRecord
 功能描述  : 记录IMSA发起去注册事件
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月06日
    作    者   : W00209181
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_RegFailErrLogRecord
(
    IMSA_REG_TYPE_ENUM_UINT8                        enRegType,
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enNormRegFailReason,
    VOS_UINT16                                      usSipStatusCode,
    VOS_UINT32                                      ulRetryTimerLen,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enEmcRegFailReason
)
{
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        IMSA_NormRegFailErrRecord(enNormRegFailReason,
                                  usSipStatusCode,
                                  ulRetryTimerLen);
    }
    else
    {
        /* 如果IMS注册失败，则记录呼叫失败 */
        IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                enEmcRegFailReason,
                                IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                VOS_FALSE,
                                usSipStatusCode,
                                IMSA_ERR_LOG_CALL_STATUS_IDLE);
    }
}


#endif
/*lint +e961*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaRegManagement.c */
