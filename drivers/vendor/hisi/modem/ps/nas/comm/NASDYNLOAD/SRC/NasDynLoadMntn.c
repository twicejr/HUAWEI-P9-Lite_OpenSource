/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasDynLoadMntn.c
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2015年8月27日
  最近修改   :
  功能描述   : 动态加载的可维可测相关处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月27日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasDynLoadMntn.h"
#include "gunas_errno.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_DYNLOAD_MNTN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_LogRegisterInfo
 功能描述  : 打印注册信息
 输入参数  : enRatType:接入技术
             ulPid    :PID
             ulInit   :初始化函数地址
             ulUnload :卸载函数地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogRegisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit,
    VOS_UINT32                          ulUnload
)
{
    NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogRegisterInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_REGISTER;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;
    pstMsg->ulInit                      = ulInit;
    pstMsg->ulUnload                    = ulUnload;

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_LogDeregisterInfo
 功能描述  : 打印去注册信息
 输入参数  : enRatType:接入技术
             ulPid    :PID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogDeregisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid
)
{
    NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogDeregisterInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_DEREGISTER;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_LogExcuteInitInfo
 功能描述  : 打印加载模块的初始化信息
 输入参数  : pstDynloadCbRatInfo :保存的所有接入技术的初始化与卸载函数信息
             enRatType           :接入技术
             ulPid               :PID
             ulInit              :初始化函数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogExcuteInitInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit
)
{
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogExcuteInitInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;
    pstMsg->ulInit                      = ulInit;

    PS_MEM_CPY(pstMsg->astNasDynloadCbRatInfo, pstDynloadCbRatInfo, VOS_RATMODE_BUTT*sizeof(NAS_DYNLOAD_CB_RAT_INFO_STRU));

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_LogExcuteUnloadInfo
 功能描述  : 打印加载模块的卸载信息
 输入参数  : pstDynloadCbRatInfo :保存的所有接入技术的初始化与卸载函数信息
             enRatType           :接入技术
             ulPid               :PID
             ulUnload            :卸载函数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogExcuteUnloadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulUnload
)
{
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU                *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogExcuteUnloadInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;
    pstMsg->ulUnload                    = ulUnload;

    PS_MEM_CPY(pstMsg->astNasDynloadCbRatInfo, pstDynloadCbRatInfo, VOS_RATMODE_BUTT*sizeof(NAS_DYNLOAD_CB_RAT_INFO_STRU));

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_LogStartDrvLoadInfo
 功能描述  : 调用底软函数前进行勾包操作，以防挂死
 输入参数  : NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo
             VOS_RATMODE_ENUM_UINT32             enRatType
             VOS_UINT32                          ulPid
             VOS_UINT32                          ulUnload
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogStartDrvLoadInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType
)
{
    NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU                *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogStartDrvLoadInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD;
    pstMsg->enRatMode                   = enRatType;

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_DYNLOAD_LogFinishDrvLoadInfo
 功能描述  : 调用底软函数后进行勾包操作，以防挂死
 输入参数  : NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogFinishDrvLoadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_INT32                           lLoadResult
)
{
    NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU              *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogFinishDrvLoadInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD;
    pstMsg->lLoadResult                 = lLoadResult;

    PS_MEM_CPY(pstMsg->astNasDynloadCbRatInfo, pstDynloadCbRatInfo, VOS_RATMODE_BUTT*sizeof(NAS_DYNLOAD_CB_RAT_INFO_STRU));

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_Dynload_SoftReBoot_WithLineNoAndFileID
 功能描述  : 动态加载模块主动条用复位函数
 输入参数  : ulLineNO,
             ulFileID,
             stCnasRebootInfo

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_Dynload_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_DYNLOAD_REBOOT_INFO_STRU       *pstRebootInfo
)
{
    VOS_UINT32                                              ulSlice;
    VOS_UINT32                                              ulTaskTcb;
    NAS_REBOOT_MOD_ID_ENUM_UINT32                           ulModuleId;
    VOS_RATMODE_ENUM_UINT32                                 enRatMode;

    ulSlice   = VOS_GetSlice();

    if (UEPS_PID_MSCC == pstRebootInfo->ulPid)
    {
        ulModuleId = NAS_REBOOT_MOD_ID_DYNLOAD;
    }
    else
    {
        ulModuleId = NAS_REBOOT_MOD_ID_BUTT;
    }

    ulTaskTcb = VOS_GetTCBFromPid(pstRebootInfo->ulPid);

    enRatMode = pstRebootInfo->enRatMode;

    mdrv_om_system_error( (VOS_INT)(ulModuleId | enRatMode),
                          (VOS_INT)ulTaskTcb,
                          (VOS_INT)((ulFileID << 16) | ulLineNO),
                          (VOS_CHAR *)(&ulSlice),
                          sizeof(ulSlice) );
    return;

}





/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


