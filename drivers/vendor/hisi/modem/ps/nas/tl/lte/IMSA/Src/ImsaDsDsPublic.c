/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaDsDsPublic.c
  Description     : 该C文件实现公共的函数，如NV读写，USIM等
  History           :
     1.wangchen 00209181    2015-11-26  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaPublic.h"
#include "ImsaEntity.h"
#include "LNvCommon.h"
#include "LPsNvInterface.h"
#include "UsimPsInterface.h"
#include "ImsaNvInterface.h"
#include "SysNvId.h"
#include "NVIM_Interface.h"
#include "ImsaImsInterface.h"
#include "ImsaImsAdaption.h"
#include "NasCommPrint.h"
#include "VcImsaInterface.h"
#include "ImsaCdsInterface.h"
#include "ImsaImsInterface.h"
#include "MsgImsaInterface.h"
#include "ImsaRegManagement.h"
#include "ScInterface.h"
#include "CallImsaInterface.h"
#include "NasNvInterface.h"
#include "LNasNvInterface.h"
#include "ImsaDsDsPublic.h"
#if (VOS_OS_VER != VOS_WIN32)
#include "TafNvInterface.h"
#include "SysNvId.h"
#endif

#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaProcOmMsg.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_IMSAPUBLIC_C
#define    THIS_NAS_FILE_ID      NAS_FILE_ID_IMSAPUBLIC_C
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
IMSA_DSDS_PUBLIC_INFO_STRU       g_stDsdsPubilcInfo;

IMSA_DSDS_TASKTYPE_INFO_STRU g_stImsaDsdsTaskTypeInfo[] =
{
    {RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL,   IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL,   IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,   IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},

    {RRM_PS_TASK_TYPE_LTE_IMS_MO_SS,            IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_MT_SS,            IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},

    {RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS,           IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,           IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},

    {RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,         IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
    {RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER,       IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0, 0, {0,0,0}},
};

#define IMSA_DSDS_TASKTYPETBL_NUM  (sizeof(g_stImsaDsdsTaskTypeInfo)/sizeof(IMSA_DSDS_TASKTYPE_INFO_STRU))


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 函 数 名  : IMSA_DsdsGetTaskStatusByTaskType
 功能描述  : TaskType维护表处理，通过enTaskType查找到对应的维护表Index
             内部调用函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
IMSA_TASKTYPE_STATUS_ENUM_UINT8 IMSA_DsdsGetTaskStatusByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskStatusByTaskType is entered!");

    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus;
        }
    }

    return IMSA_TASKTYPE_STATUS_BUTT;
}
/*****************************************************************************
 函 数 名  : IMSA_DsdsIsHasActiveResource
 功能描述  : 是否有处于ACTIVE状态的任务
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月23日
   作    者   : w00209181
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  IMSA_DsdsIsHasActiveResource
(
    VOS_VOID
)
{

    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (IMSA_TASKTYPE_STATUS_ACTIVE == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus)
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 函 数 名  : IMSA_Dsds_RRM_RfResourceIsShared
 功能描述  : 封装RRM查询RF资源是否共享接口(DSDS功能是否打开)
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
PS_RRM_RF_SHARED_ENUM_UINT8 IMSA_Dsds_RRM_RfResourceIsShared(VOS_VOID)
{
    PS_RRM_RF_SHARED_ENUM_UINT8 enRet = PS_RRM_RF_NOT_SHARED;
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager;
    #endif
    IMSA_INFO_LOG("IMSA_Dsds_RRM_RfResourceIsShared is entered!");
    #if (FEATURE_ON == FEATURE_DSDS)
    pstControlManager = IMSA_GetControlManagerAddress();
    #endif

    #if (FEATURE_ON == FEATURE_DSDS)
    #if (VOS_OS_VER != VOS_WIN32)

    enRet = RRM_RfResourceIsShared(IMSA_DSDS_MODEM0,VOS_RATMODE_LTE);

    /*尽管DSDS特性宏以及RRM_RfResourceIsShared返回Shared,但如enActiveModem为Single，仍然认为特性不开*/
    if (IMSA_FALSE == pstControlManager->ucDsdsNvCfgStatus)
    {
       enRet = PS_RRM_RF_NOT_SHARED;
    }
    #endif
    #endif

    return enRet;
}
/*****************************************************************************
 Function Name   : IMSA_DsdsIsResourceStatusReady
 Description     : 供其他模块调用，发送资源申请，启动定时器
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
IMSA_RESOURCE_STATUS_ENUM_UINT8  IMSA_DsdsGetResourceStatus
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
)
{
    if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        return IMSA_RESOURCE_STATUS_ACTIVE;
    }

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_RESOURCE_STATUS_ACTIVE;
    }

    if (IMSA_TRUE == IMSA_DsdsIsHasActiveResource())
    {
        return IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF;
    }


    if (IMSA_TASKTYPE_STATUS_NULL == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_RESOURCE_STATUS_NULL;
    }

    if (IMSA_TASKTYPE_STATUS_APPLYING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_RESOURCE_STATUS_APPLYING;
    }

    return IMSA_RESOURCE_STATUS_WAIT_STATUS_IND;

}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : IMSA_DsdsGetIndexByTaskType
 功能描述  : TaskType维护表处理，通过enTaskType查找到对应的维护表Index
             内部调用函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 IMSA_DsdsGetIndexByTaskType (RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetIndexByTaskType is entered!");

    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return ulIndex;
        }
    }

    return ulIndex;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsGetTaskStatusByTaskType
 功能描述  : TaskType维护表处理，通过enTaskType查找到对应的维护表Index
             内部调用函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsSetTaskStatusByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_TASKTYPE_STATUS_ENUM_UINT8         enTaskStatus,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsSetTaskStatusByTaskType is entered!");

    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = enTaskStatus;

            g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc = enTrigerSrc;
            g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara      = ulPara;
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsGetTaskSrcByTaskType
 功能描述  : TaskType维护表处理，通过enTaskType查找到对应的维护表Index
             内部调用函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsModifyTaskSrcByTaskType
(
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskSrcByTaskType is entered!");

    /* 由于注册任务，关机和其他触发源的定时器时长不一致，所以修改为关机时，需要将原有定时器
    停止，启动关机定时器 */
    ulIndex = IMSA_DsdsGetIndexByTaskType(enTaskType);

    if (IMSA_DSDS_ABNORMAL_IDX == ulIndex)
    {
        return;
    }

    if ((IMSA_TASKTYPE_STATUS_APPLYING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus) &&
        (RRM_PS_TASK_TYPE_LTE_IMS_REGISTER == enTaskType) &&
        (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == enTrigerSrc))
    {
        IMSA_DsdsStopApplyReqTimer(enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

        g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc = enTrigerSrc;

        IMSA_DsdsStartApplyReqTimer(enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);
    }
    else
    {
        g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc = enTrigerSrc;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsGetTaskSrcByTaskType
 功能描述  : TaskType维护表处理，通过enTaskType查找到对应的维护表Index
             内部调用函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 IMSA_DsdsGetTaskSrcByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskSrcByTaskType is entered!");

    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc;
        }
    }

    return IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsGetTaskSrcByTaskType
 功能描述  : TaskType维护表处理，通过enTaskType查找到对应的维护表Index
             内部调用函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 IMSA_DsdsGetTaskParaByTaskType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsGetTaskParaByTaskType is entered!");

    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (enTaskType == g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType)
        {
            return g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara;
        }
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsTaskTypeProcTaskApply
 功能描述  : 发起PS_RRM_RADIO_RESOURCE_APPLY_REQ时，对TaskType维护表的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsTaskTypeProcByTaskApplyType
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara,
    VOS_UINT8                               ucHasBuffer
)
{
    VOS_UINT32                          ulIndexOfTbl    = IMSA_DsdsGetIndexByTaskType(enTaskType);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndexOfTbl)
    {
        IMSA_ERR_LOG("IMSA_DsdsTaskTypeProcByTaskApplyType,ab index!");
        return;
    }

    if (IMSA_TRUE == IMSA_DsdsIsHasActiveResource())
    {
        g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].enStatus = IMSA_TASKTYPE_STATUS_ACTIVE;
    }
    else
    {
        g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].enStatus = IMSA_TASKTYPE_STATUS_APPLYING;
    }

    g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].enTrigerSrc  = enTrigerSrc;
    g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].ulPara       = ulPara;
    g_stImsaDsdsTaskTypeInfo[ulIndexOfTbl].ucHasBuffer  = ucHasBuffer;

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_ITFDSDS_SndSingleApplyReq
 功能描述  : 向DSDS RRM发送单条申请资源的请求消息，内部使用，不对外
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 IMSA_DsdsSndSingleApplyReq(RRM_PS_TASK_TYPE_ENUM_UINT16  enTaskType)
{
    PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU  *pstApplyReq         = VOS_NULL_PTR;

    /*申请消息空间*/
    pstApplyReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU));

    /* 检查申请空间是否成功 */
    if (VOS_NULL_PTR == pstApplyReq)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_CONN_SndCdsSetImsBearerReqS:ERROR:Alloc Msg fail!");
        return IMSA_FALSE;
    }

    IMSA_WRITE_RRM_MSG_HEAD(pstApplyReq, ID_PS_RRM_RADIO_RESOURCE_APPLY_REQ, sizeof(PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU));
    //IMSA_WRITE_RRM_MSG_HEAD(pstOccCnf, ID_PS_RRM_RADIO_RESOURCE_OCCUPY_CNF);

    pstApplyReq->enModemId  = IMSA_DSDS_MODEM0;
    pstApplyReq->enRatType  = VOS_RATMODE_LTE;
    pstApplyReq->enTaskType = enTaskType;
    pstApplyReq->stMsgHeader.ulMsgName    = ID_PS_RRM_RADIO_RESOURCE_APPLY_REQ;

    /* 打印消息 */
    IMSA_INFO_LOG1("IMSA_ITFDSDS_SndSingleApplyReq,send msg,enTaskType=",
                      pstApplyReq->enTaskType);
    /* 发送消息 */
    IMSA_SND_MSG(pstApplyReq);

    return IMSA_SUCC;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsTaskTypeProcApplyCnf
 功能描述  : 收到RRM_PS_RADIO_RESOURCE_APPLY_CNF，对TaskType维护表的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsTaskTypeProcByApplyCnf(RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType)
{
    IMSA_DSDS_TASKTYPE_INFO_STRU          *pstImsaTskTypeInfo = VOS_NULL_PTR;
    VOS_UINT32  ulLoop;

    for(ulLoop = 0; ulLoop < IMSA_DSDS_TASKTYPETBL_NUM; ulLoop++)
    {
        pstImsaTskTypeInfo = &g_stImsaDsdsTaskTypeInfo[ulLoop];

        /*只要有一个回来，所有Applying的都转为Active*/
        if (IMSA_TASKTYPE_STATUS_APPLYING == pstImsaTskTypeInfo->enStatus)
        {
            pstImsaTskTypeInfo->enStatus = IMSA_TASKTYPE_STATUS_ACTIVE;
        }

        /*这种情况下存在Pending的是一种异常*/
        if (IMSA_TASKTYPE_STATUS_PENDING == pstImsaTskTypeInfo->enStatus)
        {
            IMSA_ERR_LOG("IMSA_DsdsTaskTypeProcApplyCnf,ab index!");
        }
    }

    return;
}
/*****************************************************************************
 Function Name  : IMSA_ProcMsgRegResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgRegResourceApplyCnf
(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex = IMSA_FALSE;
    VOS_UINT32                          ulRst   = IMSA_TRUE;

    /* 调用处理函数 */
    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        IMSA_ERR_LOG("IMSA_ProcMsgRegResourceApplyCnf,ab index!");
        return;
    }

    /* 停止定时器 */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    if (IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        ulRst = IMSA_RegFsmProcWaitRetryResourceApplyCnf(g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara);

        if (IMSA_FALSE == ulRst)
        {
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        ulRst = IMSA_SRV_ProcPeriodRegResourceApplyCnf(g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara);

        if (IMSA_FALSE == ulRst)
        {
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        IMSA_ProcStopResourceApplyCnf();
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG == g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc)
    {
        if (IMSA_FALSE == IMSA_SRV_ProcDeRegResourceApplyCnf())
        {
            /* 如果不需要发起去注册流程，则主动释放资源 */
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else
    {
        if (IMSA_FALSE == IMSA_SRV_ProcGetNormSevResourceApplyCnf(g_stImsaDsdsTaskTypeInfo[ulIndex].ulPara))
        {
            /* 如果不需要发起去注册流程，则主动释放资源 */
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgDeRegResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgDeRegResourceApplyCnf
(
    VOS_VOID
)
{
    VOS_UINT32                              ulIndex = IMSA_FALSE;

    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        return;
    }

    /* 停止定时器 */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    /* 调用处理函数 */
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER))
    {
        IMSA_ProcStopResourceApplyCnf();
    }
    else
    {
        if (IMSA_FALSE == IMSA_SRV_ProcDeRegResourceApplyCnf())
        {
            /* 如果不需要发起去注册流程，则主动释放资源 */
            IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER, IMSA_FALSE, 0);
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoCallResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMoCallResourceApplyCnf
(
    VOS_UINT32              ulIndex
)
{
    /* 停止定时器 */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    if (IMSA_FALSE == g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer)
    {
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL, IMSA_FALSE, 0);
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
        return;
    }

    /* 调用处理函数 */
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_MO_CALL == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL))
    {
        IMSA_CallProcMoCallResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stMoCall);
    }
    else
    {
        IMSA_CallProcEconfResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stEnhancedConferrence);
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoEmcCallResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMoEmcCallResourceApplyCnf
(
    VOS_UINT32              ulIndex
)
{
    /* 停止定时器 */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);


    /* 如果是紧急呼叫#380的场景，则是不存在缓存消息的 */
    if (IMSA_FALSE == g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer)
    {
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL, IMSA_FALSE, 0);
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
        return;
    }

    /* 调用处理函数 */
    IMSA_CallProcEmcResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stEmcCall);
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoEmcCallResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMtCallResourceApplyCnf
(
    VOS_VOID
)
{
    VOS_UINT32                              ulIndex = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        return;
    }

    /* 停止定时器 */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    /* 调用处理函数 */
    if (IMSA_FALSE == IMSA_CallProcMtResourceApplyCnf((VOS_UINT8)IMSA_DsdsGetTaskParaByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL)))
    {
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL);
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMoEmcCallResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMoSmsResourceApplyCnf
(
    VOS_UINT32      ulIndex
)
{
    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    /* 停止定时器 */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    /* */
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMS == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        /* 调用处理函数 */
        IMSA_SMSProcMoResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stMoSms);
    }
    else if(IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMMA == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        IMSA_SMSProcSmmaResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stSmma);
    }
    else  /* 如果是SMMA重传*/
    {
        IMSA_SMSProcSmmaRetransResourceApplyCnf();
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgMtSmsResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgMtSmsResourceApplyCnf
(
    VOS_UINT32      ulIndex
)
{
    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    /* 停止定时器 */
    IMSA_DsdsStopApplyReqTimer(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

    if (IMSA_FALSE == g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer)
    {
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS, IMSA_FALSE, 0);
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
        return;
    }

    /* 调用处理函数 */
    IMSA_SMSProcMtResourceApplyCnf(&g_stDsdsPubilcInfo.stBufferInfo.stMtSms);
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsgResourceApplyCnf
 Discription    : 收到ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF消息的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ProcMsgResourceApplyCnf
(
    const RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU *pstApplyCnf
)
{
    VOS_UINT32                          ulIndex = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_ProcMsgResourceApplyCnf: ENTER");

    if (PS_RRM_RESULT_SUCCESS != pstApplyCnf->enResult)
    {
        /* 增加保护 */
        return;
    }

    ulIndex = IMSA_DsdsGetIndexByTaskType(pstApplyCnf->enTaskType);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        IMSA_ERR_LOG("IMSA_ProcMsgResourceApplyCnf,ab index!");
        return;
    }

    /* 如果当前状态是NULL，出现该场景是REL IND和ACTIVE CNF对冲的场景，直接丢弃 */
    /* 如果当前状态已经是ACTIVE，则是其他task已经申请到了资源，不需要等响应，直接丢弃 */
    if ((IMSA_TASKTYPE_STATUS_ACTIVE == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus) ||
        (IMSA_TASKTYPE_STATUS_NULL == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus))
    {
        return;
    }

    /*处理TaskType维护表*/
    IMSA_DsdsTaskTypeProcByApplyCnf(pstApplyCnf->enTaskType);

    /* 如果是注册类型的激活，则直接调用SERVICE模块提供的API接口 */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_ProcMsgRegResourceApplyCnf();
    }

    /* 如果短信任务的激活，则调用短信模块提供的API接口 */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        IMSA_ProcMsgMoSmsResourceApplyCnf(ulIndex);
    }

    /* 如果短信任务的激活，则调用短信模块提供的API接口 */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
    {
        IMSA_ProcMsgMtSmsResourceApplyCnf(ulIndex);
    }

    /* 如果是MO CALL，则调用呼叫模块提供的API接口 */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL))
    {
        IMSA_ProcMsgMoCallResourceApplyCnf(ulIndex);
    }

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        IMSA_ProcMsgMoEmcCallResourceApplyCnf(ulIndex);
    }

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
    {
        IMSA_ProcMsgMtCallResourceApplyCnf();
    }

    /* 如果是去注册申请资源成功 */
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER))
    {
        IMSA_ProcMsgDeRegResourceApplyCnf();
    }
    return;
}
/*****************************************************************************
 函 数 名  : IMSA_DsdsSndRrmReleaseInd
 功能描述  : 构造发送rrm的release ind消息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : W00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmReleaseInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16    enTaskType,
    PS_BOOL_ENUM_UINT8              enRelAllFlg,
    VOS_UINT32                      ulDelayTime
)
{
    PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU *pstRelReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_DsdsSndRrmReleaseInd is entered.");

    /*分配消息空间*/
    pstRelReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU));

    /* 检查申请空间是否成功 */
    if (VOS_NULL_PTR == pstRelReq)
    {
        /* 如果申请失败，则返回申请内存失败 */
        return;
    }

    IMSA_MEM_SET_S( pstRelReq,
                    sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU),
                    0,
                    sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstRelReq, ID_PS_RRM_RADIO_RESOURCE_RELEASE_IND,sizeof(PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU));

    pstRelReq->enModemId    = IMSA_DSDS_MODEM0;
    pstRelReq->enRatType    = VOS_RATMODE_LTE;
    pstRelReq->enTaskType   = enTaskType;
    pstRelReq->enRelAllFlag = enRelAllFlg;
    pstRelReq->ulRelDelaytimer = ulDelayTime;


    /* 发送消息 */
    IMSA_SND_MSG(pstRelReq);
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsSndRrmRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_REGISTER_IND消息
 输入参数  : enTaskType         :注册任务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月21日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{
    /* 定义原语类型指针 */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_REGISTER_IND_STRU));

    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 返回失败 */
        return;
    }

    IMSA_MEM_SET_S( pstMsg,
                    sizeof(PS_RRM_REGISTER_IND_STRU),
                    0,
                    sizeof(PS_RRM_REGISTER_IND_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstMsg, ID_PS_RRM_REGISTER_IND,sizeof(PS_RRM_REGISTER_IND_STRU));

    pstMsg->enModemId                       = IMSA_DSDS_MODEM0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*发送消息*/
    IMSA_SND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsSndRrmDeRegisterInd
 功能描述  : 向RRM发送ID_PS_RRM_DEREGISTER_IND消息
 输入参数  : enTaskType         :注册任务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月21日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmDeRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
)
{
    /* 定义原语类型指针 */
    PS_RRM_DEREGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_DEREGISTER_IND_STRU));

    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 返回失败 */
        return;
    }

    IMSA_MEM_SET_S( pstMsg,
                    sizeof(PS_RRM_DEREGISTER_IND_STRU),
                    0,
                    sizeof(PS_RRM_DEREGISTER_IND_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstMsg, ID_PS_RRM_DEREGISTER_IND, sizeof(PS_RRM_DEREGISTER_IND_STRU));

    pstMsg->enModemId                       = IMSA_DSDS_MODEM0;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_LTE;

    /*发送消息*/
    IMSA_SND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_DsdsProcRrmPsStatusInd
 功能描述  : 收到RRM的PS STATUS IND消息，通知RRM进行去注册,同时申请资源
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月23日
   作    者   : w00209181
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  IMSA_DsdsProcRrmPsStatusInd
(
    RRM_PS_STATUS_IND_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    /* 如果同时向RRM注册了资源，且其中某个可以申请到资源，则将所有的任务都给RRM模块发送申请 */
    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {
        if (IMSA_TASKTYPE_STATUS_PENDING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus)
        {
            IMSA_DsdsSndRrmDeRegisterInd(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);

            IMSA_DsdsSndSingleApplyReq(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);

            g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_APPLYING;

            IMSA_DsdsStartApplyReqTimer(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);
        }
    }

    return;
}
/*****************************************************************************
 函 数 名  : IMSA_DsdsSndRrmOccupyCnf
 功能描述  : 针对被抢消息ID_RRM_PS_RADIO_RESOURCE_OCCUPY_REQ，回复CNF
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月24日
    作    者   : w00209181
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMSA_DsdsSndRrmOccupyCnf(VOS_VOID)
{
    PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU  *pstOccCnf = VOS_NULL_PTR;

    if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        return;
    }

    pstOccCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU));

    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstOccCnf)
    {
        /* 返回失败 */
        return;
    }

    IMSA_MEM_SET_S( pstOccCnf,
                    sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU),
                    0,
                    sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU));

    IMSA_WRITE_RRM_MSG_HEAD(pstOccCnf, ID_PS_RRM_RADIO_RESOURCE_OCCUPY_CNF,sizeof(PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU));

    /*发送消息*/
    IMSA_SND_MSG(pstOccCnf);

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcOccupyReq
 Description     :   处理抢占
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcResourceOccupyCnf
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType
)
{
    if (VOS_FALSE == IMSA_IsTimerRunning(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer))
    {
        return;
    }
    IMSA_StopTimer(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer);
    IMSA_DsdsSndRrmOccupyCnf();

    IMSA_DsdsSetTaskStatusByTaskType(enTaskType,
                                     IMSA_TASKTYPE_STATUS_NULL,
                                     IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                     0);
}
/*****************************************************************************
 Function Name   : IMSA_DsdsProcOccupyReq
 Description     :   处理抢占
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcResourceOccupyReq
(
    RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU *pstOccupyReq
)
{
    /*如果是非紧急抢占，启动一个保护定时器，保护发送抢占cnf*/
    if ((RRM_PS_URGENT_TYPE_NO_URGENT == pstOccupyReq->enUrgentType) ||
        (RRM_PS_URGENT_TYPE_SHORT_OCCUPY == pstOccupyReq->enUrgentType))
    {
        /* 目前只有短信流程和去注册流程会发生抢占  */
        /* 启动延迟处理抢占消息的定时器 */
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer);
    }
    else if (RRM_PS_URGENT_TYPE_URGENT == pstOccupyReq->enUrgentType)
    {
        /*如果是紧急抢占，立即回复cnf，内部结束流程 */
        IMSA_DsdsSndRrmOccupyCnf();

        if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
        {
            IMSA_SMSProcMoSmsRfOccupiedDelayTimerExp();

            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);


        }

        if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
        {
            IMSA_SMSProcMtSmsRfOccupiedDelayTimerExp();

            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);


        }
    }
    return;
}
/*****************************************************************************
 Function Name   : IMSA_DsdsStartApplyReqTimer
 Description     : 根据任务类型，启动定时器
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsStartApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
)
{
    if (RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMoCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMtCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitEmcCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMoSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitMtSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_REGISTER == enTaskType)
    {
        if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == enTrigerSrc)
        {
            IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitPowerOffRfTimer);
        }
        else
        {
            IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitRegRFTimer);
        }
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER == enTaskType)
    {
        IMSA_StartTimer(&g_stDsdsPubilcInfo.stWaitDeRegRFTimer);
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsStopApplyReqTimer
 Description     : 根据任务类型，启动定时器
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsStopApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
)
{
    if (RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMoCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMtCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitEmcCallRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMoSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitMtSmsRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_REGISTER == enTaskType)
    {
        if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == enTrigerSrc)
        {
            IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitPowerOffRfTimer);
        }
        else
        {
            IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitRegRFTimer);
        }
        //IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitRegRFTimer);
    }
    else if (RRM_PS_TASK_TYPE_LTE_IMS_DEREGISTER == enTaskType)
    {
        IMSA_StopTimer(&g_stDsdsPubilcInfo.stWaitDeRegRFTimer);
    }
    else
    {
    }
    return;
}
/*****************************************************************************
 Function Name   : IMSA_DsdsProcRegResourceApplyReq
 Description     : 供其他模块调用，发送资源申请，启动定时器
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcResourceApplyReq
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara,
    VOS_UINT8                               ucHasBuffer
)
{

    IMSA_DsdsSndSingleApplyReq(enTaskType);

    IMSA_DsdsTaskTypeProcByTaskApplyType(enTaskType, enTrigerSrc, ulPara, ucHasBuffer);

    if (IMSA_TASKTYPE_STATUS_APPLYING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        IMSA_DsdsStartApplyReqTimer(enTaskType, enTrigerSrc);
        return;
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcResourceApplyReq
 Description     : 供其他模块调用，发送资源申请，启动定时器
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_UINT32  IMSA_DsdsProcResourceRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc,
    VOS_UINT32                              ulPara
)
{
    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_TRUE;
    }

    /* 现有流程中应该不会有这种场景 */
    if (IMSA_TASKTYPE_STATUS_APPLYING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_FALSE;
    }

    if (IMSA_TASKTYPE_STATUS_PENDING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        return IMSA_FALSE;
    }

    if (IMSA_TASKTYPE_STATUS_NULL == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
    {
        IMSA_DsdsSndRrmRegisterInd(enTaskType);

        IMSA_DsdsSetTaskStatusByTaskType(enTaskType, IMSA_TASKTYPE_STATUS_PENDING ,enTrigerSrc, ulPara);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcRegResourceTimerExp
 Description     : 申请注册资源定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcRegResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    IMSA_INFO_LOG("IMSA_DsdsProcRegResourceTimerExp: ENTER");

    ulIndex = IMSA_DsdsGetIndexByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        IMSA_ERR_LOG("IMSA_DsdsProcRegResourceTimerExp,ab index!");
        return;
    }

    if (IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        /* 通知RRM模块释放资源 */
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);

        /* 将注册任务通知给RRM模块 */
        IMSA_DsdsSndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

        /* 状态切换 */
        //IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_TASKTYPE_STATUS_PENDING);
        g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_PENDING;

        /* 需要通知MMA VOICE 不可用 */
        IMSA_SRV_ProcGetNorServiceResourceApplyExp();

        return;
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_RegFsmProcWaitRetryResourceApplyExp();

        /* 通知RRM模块释放资源 */
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);

        /* 修改触发源为获取服务 */
        IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

        /* 将注册任务通知给RRM模块 */
        IMSA_DsdsSndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

        /* 状态切换 */
        g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_PENDING;
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        /* 通知RRM模块释放资源 */
        IMSA_DsdsSndRrmReleaseInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER, IMSA_FALSE, 0);

        /* 调用函数处理 */
        if (IMSA_TRUE == IMSA_SRV_ProcPeriodRegResourceApplyExp())
        {
            /* 将注册任务通知给RRM模块 */
            IMSA_DsdsSndRrmRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            /* 修改触发源为获取服务 */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            /* 状态切换 */
            g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus = IMSA_TASKTYPE_STATUS_PENDING;
        }
        else
        {
            IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_TASKTYPE_STATUS_NULL,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                             0);
        }
    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_ProcStopResourceApplyTimerExp();

        /* 通知RRM模块释放资源 */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

    }
    else if (IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG == IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        (VOS_VOID)IMSA_SRV_ProcDeRegResourceApplyTimerExp();

        /* 通知RRM模块释放资源 */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcMoCallResourceTimerExp
 Description     : 申请注册资源定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMoCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL))
    {
        return;
    }

    /* 通知RRM模块释放资源 */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL);

    /* 通知SPM释放呼叫 */
    IMSA_CallProcMoOrEmcResourceApplyTimerExp();

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : 申请注册资源定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcEmcCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        return;
    }

    /* 通知RRM模块释放资源 */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL);

    /* 通知SPM释放呼叫 */
    IMSA_CallProcMoOrEmcResourceApplyTimerExp();

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : 申请注册资源定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMtCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL))
    {
        return;
    }

    IMSA_CallProcMtResourceApplyTimerExp((VOS_UINT8)IMSA_DsdsGetTaskParaByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL));

    /* 通知RRM模块释放资源 */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL);

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : 申请注册资源定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMoSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_RF_RES_APPLY_TRIGER_SRC_MO_SMS== IMSA_DsdsGetTaskSrcByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
        {
            return;
        }
        /* 通知RRM模块释放资源 */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

        IMSA_SMSProcMoResourceApplyTimerExp();
    }
    else
    {
        if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
        {
            return;
        }

        /* 通知RRM模块释放资源 */
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
        IMSA_SMSProcSmmaResourceApplyTimerExp();
    }

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : 申请注册资源定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcMtSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    if (IMSA_TASKTYPE_STATUS_APPLYING != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
    {
        return;
    }

    /* 通知RRM模块释放资源 */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS);
    //IMSA_SMSProcMoResourceApplyTimerExp();

    return;
}

/*****************************************************************************
 Function Name   : IMSA_DsdsProcEmcCallResourceTimerExp
 Description     : 申请注册资源定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32
                   IMSA_TRUE:可以直接发起流程
                   IMSA_FALSE:等RRM响应

 History         :
    1.wangchen 00209181     2015-11-24  Draft Enact

*****************************************************************************/
VOS_VOID  IMSA_DsdsProcOccupyDelayTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_StopTimer(&g_stDsdsPubilcInfo.stDelayProcOccupiedTimer);

    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS))
    {
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);

        IMSA_SMSProcMoSmsRfOccupiedDelayTimerExp();
    }


    if (IMSA_TASKTYPE_STATUS_ACTIVE == IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
    {
        IMSA_DsdsSetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);

        IMSA_SMSProcMtSmsRfOccupiedDelayTimerExp();
    }

    IMSA_DsdsSndRrmOccupyCnf();

    return;
}

/*****************************************************************************
 Function Name  : IMSA_DsdsClearResource()
 Description    : DSDS模块资源清理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181  2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_DsdsClearResource(VOS_VOID)
{
     VOS_UINT32                          ulIndex = IMSA_DSDS_ABNORMAL_IDX;

    /*使用遍历查找索引值*/
    for(ulIndex = 0; ulIndex < IMSA_DSDS_TASKTYPETBL_NUM; ulIndex++)
    {


        if (IMSA_TASKTYPE_STATUS_PENDING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus)
        {
            IMSA_DsdsSndRrmDeRegisterInd(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);
        }

        if ((IMSA_TASKTYPE_STATUS_APPLYING == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus) ||
            (IMSA_TASKTYPE_STATUS_ACTIVE == g_stImsaDsdsTaskTypeInfo[ulIndex].enStatus))
        {
            /* 停止定时器 */
            IMSA_DsdsStopApplyReqTimer(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

            IMSA_DsdsProcResourceRelease(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType);
        }

        /* 状态修改为NULL */
        IMSA_DsdsSetTaskStatusByTaskType(g_stImsaDsdsTaskTypeInfo[ulIndex].enTaskType, IMSA_TASKTYPE_STATUS_NULL, IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT, 0);

        g_stImsaDsdsTaskTypeInfo[ulIndex].ucHasBuffer = IMSA_FALSE;
    }
}


VOS_VOID IMSA_DsdsSaveMoCallMsg
(
    SPM_IMSA_CALL_ORIG_REQ_STRU             *pstMoCall
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stMoCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU),
                    pstMoCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU));
}

VOS_VOID IMSA_DsdsSaveMoEmcCallMsg
(
    SPM_IMSA_CALL_ORIG_REQ_STRU             *pstEmcCall
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stEmcCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU),
                    pstEmcCall,
                    sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU));
}

VOS_VOID IMSA_DsdsSaveEconfCallMsg
(
    SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU       *pstEnhancedConferrence
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stEnhancedConferrence,
                    sizeof(SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU),
                    pstEnhancedConferrence,
                    sizeof(SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU));
}

VOS_VOID IMSA_DsdsSaveMoSmsMsg
(
    const MSG_IMSA_RP_DATA_REQ_STRU               *pstMoSms
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stMoSms,
                    (sizeof(MSG_IMSA_RP_DATA_REQ_STRU) - 4 + pstMoSms->ulDataLen + 1),
                    pstMoSms,
                    (sizeof(MSG_IMSA_RP_DATA_REQ_STRU) - 4 + pstMoSms->ulDataLen + 1));
}

VOS_VOID IMSA_DsdsSaveMtSmsMsg
(
    const IMSA_IMS_OUTPUT_SMS_EVENT_STRU            *pstMtSms
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stMtSms,
                    sizeof(IMSA_IMS_OUTPUT_SMS_EVENT_STRU),
                    pstMtSms,
                    sizeof(IMSA_IMS_OUTPUT_SMS_EVENT_STRU));
}

VOS_VOID IMSA_DsdsSaveMoSmmaMsg
(
    const MSG_IMSA_SMMA_REQ_STRU    *pstSmma
)
{
    IMSA_MEM_CPY_S( &g_stDsdsPubilcInfo.stBufferInfo.stSmma,
                    sizeof(MSG_IMSA_SMMA_REQ_STRU),
                    pstSmma,
                    sizeof(MSG_IMSA_SMMA_REQ_STRU));
}


VOS_VOID IMSA_DsdsProcResourceRelease
(
    RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType
)
{
    VOS_UINT32                              ulIndex = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_ProcMsgMtCallResourceApplyCnf: ENTER");

    ulIndex = IMSA_DsdsGetIndexByTaskType(enTaskType);

    if (IMSA_DSDS_TASKTYPETBL_NUM <= ulIndex)
    {
        return;
    }

    if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        if (IMSA_TASKTYPE_STATUS_PENDING == IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
        {
            IMSA_DsdsSndRrmDeRegisterInd(enTaskType);
        }
        else if (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(enTaskType))
        {
            IMSA_DsdsSndRrmReleaseInd(enTaskType,
                                      VOS_FALSE,
                                      VOS_FALSE);

            /* 停止定时器 */
            IMSA_DsdsStopApplyReqTimer(enTaskType, g_stImsaDsdsTaskTypeInfo[ulIndex].enTrigerSrc);

        }
        IMSA_DsdsSetTaskStatusByTaskType(enTaskType,
                                         IMSA_TASKTYPE_STATUS_NULL,
                                         IMSA_RF_RES_APPLY_TRIGER_SRC_BUTT,
                                         0);
    }
}


/*****************************************************************************
 Function Name  : IMSA_DsdsInit
 Description    : IMSA CONN模块的初始化
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181  2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_DsdsInit( VOS_VOID )
{
    IMSA_DSDS_PUBLIC_INFO_STRU          *pstPublicInfo = &g_stDsdsPubilcInfo;

    pstPublicInfo->stWaitRegRFTimer.phTimer             = VOS_NULL_PTR;
    pstPublicInfo->stWaitRegRFTimer.ucMode              = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitRegRFTimer.usName              = TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitRegRFTimer.ulTimerLen          = TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitDeRegRFTimer.phTimer           = VOS_NULL_PTR;
    pstPublicInfo->stWaitDeRegRFTimer.ucMode            = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitDeRegRFTimer.usName            = TI_IMSA_DEREG_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitDeRegRFTimer.ulTimerLen        = TI_IMSA_DEREG_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMoCallRFTimer.phTimer          = VOS_NULL_PTR;
    pstPublicInfo->stWaitMoCallRFTimer.ucMode           = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMoCallRFTimer.usName           = TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMoCallRFTimer.ulTimerLen       = TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMtCallRFTimer.phTimer          = VOS_NULL_PTR;
    pstPublicInfo->stWaitMtCallRFTimer.ucMode           = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMtCallRFTimer.usName           = TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMtCallRFTimer.ulTimerLen       = TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitEmcCallRFTimer.phTimer         = VOS_NULL_PTR;
    pstPublicInfo->stWaitEmcCallRFTimer.ucMode          = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitEmcCallRFTimer.usName          = TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitEmcCallRFTimer.ulTimerLen      = TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMoSmsRFTimer.phTimer           = VOS_NULL_PTR;
    pstPublicInfo->stWaitMoSmsRFTimer.ucMode            = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMoSmsRFTimer.usName            = TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMoSmsRFTimer.ulTimerLen        = TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stWaitMtSmsRFTimer.phTimer           = VOS_NULL_PTR;
    pstPublicInfo->stWaitMtSmsRFTimer.ucMode            = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitMtSmsRFTimer.usName            = TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitMtSmsRFTimer.ulTimerLen        = TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER_LEN;

    pstPublicInfo->stDelayProcOccupiedTimer.phTimer     = VOS_NULL_PTR;
    pstPublicInfo->stDelayProcOccupiedTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stDelayProcOccupiedTimer.usName      = TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER;
    pstPublicInfo->stDelayProcOccupiedTimer.ulTimerLen  = TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER_LEN;

    pstPublicInfo->stWaitPowerOffRfTimer.phTimer        = VOS_NULL_PTR;
    pstPublicInfo->stWaitPowerOffRfTimer.ucMode         = VOS_RELTIMER_NOLOOP;
    pstPublicInfo->stWaitPowerOffRfTimer.usName         = TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER;
    pstPublicInfo->stWaitPowerOffRfTimer.ulTimerLen     = TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER_LEN;

    IMSA_DsdsClearResource();

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_RrmMsgDistr()
 Description    : RRM消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_RrmMsgDistr(const VOS_VOID *pRcvMsg)
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF:
            IMSA_ProcMsgResourceApplyCnf(pRcvMsg);
            break;

        case ID_RRM_PS_RADIO_RESOURCE_OCCUPY_REQ:
            IMSA_DsdsProcResourceOccupyReq((RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU*)pRcvMsg);
            break;

        case ID_RRM_PS_STATUS_IND:
            IMSA_DsdsProcRrmPsStatusInd((RRM_PS_STATUS_IND_STRU*)pRcvMsg);
            break;

        default:
            break;
    }
}


#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaPublic.c */



