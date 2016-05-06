/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccSndImsa.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年01月26日
  功能描述   : MSCC发送IMSA消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月26日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccSndImsa.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaMsccInterface.h"
#endif
#include "MsccMmcInterface.h"
#include "NasMsccCtx.h"
#include "NasMntn.h"
#include "NasUtranCtrlCtx.h"
#include "NasComm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_IMSA_C

#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndImsaSrvInfoNotify
 功能描述  : 发送消息给IMSA
 输入参数  : enPsServiceStatus  --PS的服务状态
             ucRoamingValid     --漫游标记是否有效
             ucRoamingFlg       --漫游标记
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月24日
   作    者   : y00245242
   修改内容   : 新生成函数
  2.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 增加漫游标记
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaSrvInfoNotify(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enCurPsServiceSta,
    VOS_UINT8                           ucRoamingValid,    
    VOS_UINT8                           ucRoamingFlg       
)
{
    MSCC_IMSA_SERVICE_CHANGE_IND_STRU  *pstSndMsg    = VOS_NULL_PTR;
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstNwCapInfo = VOS_NULL_PTR;
    NAS_MSCC_SYS_INFO_STRU             *pstSysInfo   = VOS_NULL_PTR;

    pstSysInfo   = NAS_MSCC_GetCurrSysInfo();

    /* 申请内存  */
    pstSndMsg = (MSCC_IMSA_SERVICE_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_IMSA_SERVICE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaSrvInfoNotify: Memory allocation is failure");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_SERVICE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in header information */
    pstSndMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid        = UEPS_PID_MSCC;
    pstSndMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid      = PS_PID_IMSA;
    pstSndMsg->ulLength           = sizeof(MSCC_IMSA_SERVICE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* fill in message name */
    pstSndMsg->ulMsgId            = ID_MSCC_IMSA_SERVICE_CHANGE_IND;

    /* set PS service status */
    pstSndMsg->enPsServiceStatus  = (MSCC_IMSA_SERVICE_STATUS_ENUM_UINT8)enCurPsServiceSta;

    /* set PS sim valid */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        pstSndMsg->ucPsSimValid = VOS_FALSE;
    }
    else
    {
        pstSndMsg->ucPsSimValid = VOS_TRUE;
    }

    /* fill RAT */
    pstSndMsg->enRat              = (MSCC_IMSA_RAT_TYPE_ENUM_UINT8)pstSysInfo->st3gppSysInfo.enSysMode;

    pstSndMsg->bitRoamingValid    = ucRoamingValid;
    pstSndMsg->ucRoamingFlg       = ucRoamingFlg;

    if (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode)
    {
        /* by the way, here get lte network capability information */
        pstNwCapInfo              = NAS_MSCC_GetLteNwCapInfo();
    }
    else
    {
        /* by the way, here get GU network capability information */
        pstNwCapInfo              = NAS_MSCC_GetGuNwCapInfo();
    }

    /* fill in network capability infomation */
    pstSndMsg->enEmsInd           = (MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8)pstNwCapInfo->enNwEmcBsCap;
    pstSndMsg->enImsVoPsInd       = (MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8)pstNwCapInfo->enNwImsVoCap;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* send message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndImsaCampInfoChangeInd
 功能描述  : 发送消息给IMSA, 指示驻留信息(包括漫游或CGI信息)发生改变
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月26日
   作    者   : y00245242
   修改内容   : 新生成函数
  2.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaCampInfoChangeInd(VOS_VOID)
{
    MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU                    *pstSndMsg    = VOS_NULL_PTR;
    NAS_MSCC_SYS_INFO_STRU                                 *pstSysInfo   = VOS_NULL_PTR;

    pstSysInfo   = NAS_MSCC_GetCurrSysInfo();

    /* 申请内存  */
    pstSndMsg = (MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaCampInfoChangeInd: Memory allocation is failure");
        return;
    }

    PS_MEM_SET(pstSndMsg, 0, sizeof(MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU));

    /* fill in header information */
    pstSndMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid        = UEPS_PID_MSCC;
    pstSndMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid      = PS_PID_IMSA;
    pstSndMsg->ulLength           = sizeof(MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* fill in message name */
    pstSndMsg->ulMsgId            = ID_MSCC_IMSA_CAMP_INFO_CHANGE_IND;


    /* set PLMN identity */
    pstSndMsg->stPlmnId.ulMcc     = pstSysInfo->st3gppSysInfo.stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.ulMnc     = pstSysInfo->st3gppSysInfo.stPlmnId.ulMnc;

    /* set cell identity */
    pstSndMsg->ulCellId           = pstSysInfo->st3gppSysInfo.ulCellId;

    if (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode)
    {
        if (NAS_MSCC_LMM_ACCESS_TYPE_EUTRAN_TDD == pstSysInfo->st3gppSysInfo.enLmmAccessType)
        {
            pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD;
        }
        else
        {
            pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD;
        }

        /* IMSA要求usTac的高8bit是系统消息中的Tac，低8bit是系统消息中的TacCnt */
        pstSndMsg->usTac          = pstSysInfo->st3gppSysInfo.usLac;
    }
    else
    {
        if (NAS_MSCC_SYS_MODE_WCDMA == pstSysInfo->st3gppSysInfo.enSysMode)
        {
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD;
            }
            else
            {
                pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_UTRAN_TDD;
            }
        }
        else
        {
            pstSndMsg->enAccessType     = MSCC_IMSA_ACCESS_TYPE_GERAN;
        }

        /* Get LAC */
        pstSndMsg->usLac          = pstSysInfo->st3gppSysInfo.usLac;
    }

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* send message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndImsaStopReq
 功能描述  : 向imsa发送关机请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年7月26日
    作    者   : f00179208
    修改内容   : DTS2015052504823：增加打开IMS协议栈的操作类型
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaStopReq(
    MSCC_IMSA_STOP_TYPE_ENUM_UINT32     enStopType
)
{
    MSCC_IMSA_STOP_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_IMSA_STOP_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_IMSA_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaStopReq: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_IMSA;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->ulLength         = sizeof(MSCC_IMSA_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MSCC_IMSA_STOP_REQ;

    pstMsg->enStopType       = enStopType;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
	
    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndImsaStartReq
 功能描述  : 向imsa发送开机请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年7月26日
    作    者   : f00179208
    修改内容   : DTS2015052504823：增加打开IMS协议栈的操作类型
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaStartReq(
    MSCC_IMSA_START_TYPE_ENUM_UINT32    enStartType
)
{
    MSCC_IMSA_START_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_IMSA_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_IMSA_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaStartReq: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_IMSA;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->ulLength         = sizeof(MSCC_IMSA_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MSCC_IMSA_START_REQ;

    pstMsg->enStartType      = enStartType;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("SEND MSG!");

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_SndImsaVoiceDomainChangeInd
 功能描述  : 向imsa发送ID_MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月15日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaVoiceDomainChangeInd(
    MSCC_IMSA_VOICE_DOMAIN_ENUM_UINT32                      enVoiceDomain
)
{
    MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU                 *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaVoiceDomainChangeInd: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_IMSA;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->ulLength         = sizeof(MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND;
    pstMsg->enVoiceDomain    = enVoiceDomain;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



