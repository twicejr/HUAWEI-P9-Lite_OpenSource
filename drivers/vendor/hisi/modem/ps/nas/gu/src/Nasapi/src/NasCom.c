/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : NasCom.c
  Description  : NAS公共处理
  Function List: NAS_EventReport

  History:
      1.  s46746   2008.04.29 新版做成

*******************************************************************************/
#include "vos.h"
#include "NasComm.h"
#include "MM_Inc.h"
#include "NasMmlCtx.h"
#include "SmInclude.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_COM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/* 改RABM_TIMER_NAME_FD_FLUX_DETECT定时器为32k定时器 */
/* 当前默认挂32K时钟，否则需在下表明确指出 */
NAS_TIMER_PRECISION_STRU g_stNasTimerPrcision[]=
{
   {WUEPS_PID_MMA,  MMA_TIMER_FOR_PC_REPLAY,            VOS_TIMER_NO_PRECISION},
};

/*lint -e651*/
NAS_CONVERT_MTC_SESSION_STRU             g_stNasConvertMtcSessiontype[] =
{
    {RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL, MTC_SESSION_TYPE_CS_MO_NORMAL_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL, MTC_SESSION_TYPE_CS_MO_EMERGENCY_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_SS, MTC_SESSION_TYPE_CS_MO_SS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_SMS, MTC_SESSION_TYPE_CS_MO_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_NORMAL_CALL, MTC_SESSION_TYPE_CS_MT_NORMAL_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK, MTC_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_SS, MTC_SESSION_TYPE_CS_MT_SS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_SMS, MTC_SESSION_TYPE_CS_MT_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_LAU, MTC_SESSION_TYPE_CS_LAU, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_DETACH, MTC_SESSION_TYPE_CS_DETACH, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB, MTC_SESSION_TYPE_CS_MO_NORMAL_CSFB, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB, MTC_SESSION_TYPE_CS_MO_EMERGENCY_CSFB, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_CSFB, MTC_SESSION_TYPE_CS_MT_CSFB, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL, MTC_SESSION_TYPE_PS_CONVERSAT_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_STREAM_CALL, MTC_SESSION_TYPE_PS_STREAM_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL, MTC_SESSION_TYPE_PS_INTERACT_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL, MTC_SESSION_TYPE_PS_BACKGROUND_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, MTC_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_MO_SMS, MTC_SESSION_TYPE_PS_MO_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_MT_SMS, MTC_SESSION_TYPE_PS_MT_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_ATTACH, MTC_SESSION_TYPE_PS_ATTACH, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_RAU, MTC_SESSION_TYPE_PS_RAU, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_DETACH, MTC_SESSION_TYPE_PS_DETACH, 0, 0},
};
/*lint +e651*/


/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_GetTimerPrecision
 功能描述  : 获取定时器精度范围
 输入参数  : Pid       -- 启动定时器的PID
             ulName    -- 定时器名
 输出参数  : 无
 返 回 值  : VOS_TIMER_PRECISION_ENUM_UINT32 -- 定时器精度范围
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2013年9月4日
    作    者   : w00167002
    修改内容   : DTS2013090403562:NAS定时器清理，需要启动32K定时器。将MM/MMA/SMS
                模块的循环定时器修改为非循环定时器。

                定时器分为两种，26M定时器和32K定时器，
                 26M定时器，系统开销少，推荐使用，但当DRX睡眠时，停止计数，可能计时不准。
                 32K定时器，系统开销大，不推荐使用，但计时准确，
                 当选择无精度要求时(VOS_TIMER_NO_PRECISION)，启动26M定时器
                 其他有精度要求的，启动32K定时器。
             定时器选择依据:
               1）对IDLE态下定时器，要求定时器必须是精确定时的，包括我们异常保护定时器中
                  自己设计的要求绝对定时的； 协议定时器中必须绝对定时的，比如说必须绝对
                  定时才能通过GCF用例； 对这类定时器，使用32K定时器；
               2）其他IDLE定时器，不需要绝对定时的：挂到26M定时器；
               3）非IDLE态的定时器，使用26M定时器
*****************************************************************************/
VOS_TIMER_PRECISION_ENUM_UINT32 NAS_GetTimerPrecision(
    VOS_PID                             Pid,
    VOS_UINT32                          ulName
)
{
    VOS_UINT32                      i;
    VOS_TIMER_PRECISION_ENUM_UINT32 ulPrecision;

    /* 默认为有精度要求，挂在32K时钟上 */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for(i=0; i<( sizeof(g_stNasTimerPrcision)/sizeof(NAS_TIMER_PRECISION_STRU) ); i++)
    {
        if (  (Pid == g_stNasTimerPrcision[i].ulPid)
            &&( (ulName == g_stNasTimerPrcision[i].ulTimerName)
              ||(NAS_TIMER_ALL == g_stNasTimerPrcision[i].ulTimerName)))
        {
            ulPrecision = g_stNasTimerPrcision[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}

/*****************************************************************************
 Function   : NAS_StartRelTimer
 Description: NAS启动定时器函数.
 Input      : Pid       -- process ID of application
              ulLength  -- expire time. the metrics is millsecond
              ulName    -- timer name to be pass to application as a parameter
              ulParam   -- additional parameter to be pass to application
              ucMode    -- timer work mode
                           VOS_RELTIMER_LOOP  -- start periodically
                           VOS_RELTIMER_NOLOO -- start once time
              ulPrecision -- Timer Precision
 Output     : phTm      -- timer address which system retuns to application
 Return     : VOS_OK on success and errno on failure
 HISTORY    :
      1.  日    期   : 2011年06月24日
          作    者   : c00173809
          修改内容   : 根据问题单号：DTS2011051202669，SM的T3380,T3390超时消息解析不正确。
      2. 日    期   : 2013年06月28日
         作    者   : l00167671
         修改内容   : DCM LOGGER项目定时器事件上报
*****************************************************************************/
VOS_UINT32 NAS_StartRelTimer(HTIMER *phTm, VOS_PID Pid, VOS_UINT32 ulLength,
    VOS_UINT32 ulName, VOS_UINT32 ulParam, VOS_UINT8 ucMode)
{
    VOS_UINT32                          ulRet;
    NAS_TIMER_OPERATION_STRU            stTimer;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    if ( ulLength >= VOS_TIMER_MAX_LENGTH )
    {
        ulLength = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulPrecision = NAS_GetTimerPrecision(Pid, ulName);

    ulRet = VOS_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode, ulPrecision);

    stTimer.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulSenderPid      = Pid;
    stTimer.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulReceiverPid    = VOS_PID_TIMER;
    stTimer.MsgHeader.ulLength         = sizeof(NAS_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;

    if ((WUEPS_PID_MMA == Pid) || (WUEPS_PID_RABM == Pid))
    {
        stTimer.MsgHeader.ulMsgName = ulParam;
    }
    else if (WUEPS_PID_SM == Pid)
    {
        if (0xff == ulParam)
        {
            stTimer.MsgHeader.ulMsgName = ulParam;
        }
        else
        {
            stTimer.MsgHeader.ulMsgName = ulName;
        }
    }
    else
    {
        stTimer.MsgHeader.ulMsgName = ulName;
    }

    stTimer.ulTimeAction        = NAS_TIMER_OPERATION_START;
    stTimer.ulTimeLen           = ulLength;

    DIAG_TraceReport(&stTimer);

    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    NAS_TIMER_EventReport(stTimer.MsgHeader.ulMsgName,Pid, NAS_OM_EVENT_TIMER_OPERATION_START);
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

    return ulRet;
}

/*****************************************************************************
 Function   : NAS_StartRelTimer
 Description: MM层停止定时器函数.
 Input      : Pid       -- process ID of application
              ulName    -- timer name to be pass to application as a parameter
 Output     : phTm      -- timer address which system retuns to application
 Return     : VOS_OK on success and errno on failure
   1. 日    期   : 2013年06月28日
     作    者   : l00167671
     修改内容   : DCM LOGGER项目定时器事件上报
 2. 日    期   : 2013年07月24日
    作    者   : w00242748
    修改内容   : DTS2013071705401
*****************************************************************************/
VOS_UINT32 NAS_StopRelTimer(VOS_PID Pid, VOS_UINT32 ulName, HTIMER *phTm)
{
    VOS_UINT32                          ulRet;
    NAS_TIMER_OPERATION_STRU            stTimer;

    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;

    if ((VOS_NULL_PTR != phTm)
     && (VOS_NULL_PTR != *phTm))
    {
        if ( VOS_OK != VOS_GetRelTmRemainTime(phTm, &ulTimerRemainLen ) )
        {
            ulTimerRemainLen = 0;
        }
    }

    if ((0 != ulTimerRemainLen) && (VOS_FALSE == g_ucSmTimerFiveExpireFlag))
    {
        NAS_TIMER_EventReport(ulName, Pid, NAS_OM_EVENT_TIMER_OPERATION_STOP);
    }
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

    ulRet = VOS_StopRelTimer(phTm);


    stTimer.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulSenderPid      = Pid;
    stTimer.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulReceiverPid    = VOS_PID_TIMER;
    stTimer.MsgHeader.ulLength         = sizeof(NAS_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;

    stTimer.MsgHeader.ulMsgName = ulName;

    stTimer.ulTimeAction        = NAS_TIMER_OPERATION_STOP;
    stTimer.ulTimeLen           = 0x0;

    DIAG_TraceReport(&stTimer);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_ConvertCustomMsRelToPsUeRel
 功能描述  : 将NV项中定制的协议版本转换为代码中定义的协议版本宏
 输入参数  : enCustomMsRel
 输出参数  : 无
 返 回 值  : 转换后协议版本
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月15日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月15日
   作    者   : z40661
   修改内容  :NV项NAS_Support_3GPP_Relase(8288)设置的协议版本为R7，与当前UE支持的协议版本不一致
 3.日    期   : 2015年6月4日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_INT8 NAS_ConvertCustomMsRelToPsUeRel(
    NAS_MML_3GPP_REL_ENUM_UINT8         enCustomMsRel
)
{
    VOS_INT8                            cVersion;

    switch (enCustomMsRel)
    {
        case NAS_MML_3GPP_REL_R4:
            cVersion = PS_PTL_VER_R4;
            break;

        case NAS_MML_3GPP_REL_R5:
            cVersion = PS_PTL_VER_R5;
            break;

        case NAS_MML_3GPP_REL_R6:
            cVersion = PS_PTL_VER_R6;
            break;

        case NAS_MML_3GPP_REL_R7:
            cVersion = PS_PTL_VER_R7;
            break;

        case NAS_MML_3GPP_REL_R8:
            cVersion = PS_PTL_VER_R8;
            break;

        case NAS_MML_3GPP_REL_R9:
            cVersion = PS_PTL_VER_R9;
            break;

        case NAS_MML_3GPP_REL_R10:
            cVersion = PS_PTL_VER_R10;
            break;

        case NAS_MML_3GPP_REL_R11:
            cVersion = PS_PTL_VER_R11;
            break;

        default:
            cVersion = PS_UE_REL_VER;
            break;
    }

    return cVersion;
}

/*****************************************************************************
 函 数 名  : NAS_Common_Get_Supported_3GPP_Version
 功能描述  : 获取当前与网络交互的协议版本
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年05月10日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2009年06月17日
    作    者   : o00132663
    修改内容   : 根据终端可配置需求修改
  3.日    期   : 2011年07月26日
    作    者   : z00161729
    修改内容   : MMC_Com.c文件删除移动
  5.日    期   : 2012年03月15日
    作    者   : s46746
    修改内容   : 对于R7、R8新增信息单元,使用协议版本控制
  6.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
  7.日    期   : 2015年7月4日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_INT8 NAS_Common_Get_Supported_3GPP_Version(VOS_UINT32 ulCnDomainId)
{
    VOS_INT8                           cVersion;
    VOS_INT8                           cVersionFromNV;
    NAS_MML_MS_3GPP_REL_STRU          *pstMs3GppRel     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;
    NAS_MML_NETWORK_3GPP_REL_STRU     *pstNetwork3GppRel= VOS_NULL_PTR    ;

    cVersion            = PS_PTL_VER_R11;
    pstMs3GppRel        = NAS_MML_GetMs3GppRel();
    enRatType           = NAS_MML_GetCurrNetRatType();
    pstNetwork3GppRel   = NAS_MML_GetNetwork3GppRel();

    if (NAS_MML_NET_RAT_TYPE_GSM == enRatType)
    {
        cVersionFromNV = NAS_ConvertCustomMsRelToPsUeRel(pstMs3GppRel->enMsGsmRel);

        if (cVersionFromNV > PS_PTL_VER_R11)
        {
            cVersion = PS_PTL_VER_R11;
        }
        else
        {
            cVersion = cVersionFromNV;
        }

        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        if (NAS_MSCC_PIF_SRVDOMAIN_CS == ulCnDomainId)
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
        {
            switch (pstMs3GppRel->enMsMscRel)
            {
                case PS_CUSTOM_REL_VER_R97:
                    cVersion = PS_PTL_VER_PRE_R99;
                    break;

                case PS_CUSTOM_REL_VER_AUTO:
                    if (GRRMM_MSC_RELEASE98_OR_OLDER == pstNetwork3GppRel->enNetMscRel)
                    {
                        cVersion = PS_PTL_VER_PRE_R99;
                    }
                    break;

                default:
                    break;
            }
        }
        else
        {/* PS DOMAIN */
            switch ( pstMs3GppRel->enMsSgsnRel)
            {
                case PS_CUSTOM_REL_VER_R97:
                    cVersion = PS_PTL_VER_PRE_R99;
                    break;

                case PS_CUSTOM_REL_VER_AUTO:
                    if (GRRMM_SGSN_RELEASE98_OR_OLDER == pstNetwork3GppRel->enNetSgsnRel)
                    {
                        cVersion = PS_PTL_VER_PRE_R99;
                    }
                    break;

                default:
                    break;
            }
        }
    }
    else
    {/* WCDMA */
        cVersionFromNV = NAS_ConvertCustomMsRelToPsUeRel(pstMs3GppRel->enMsWcdmaRel);

        if (cVersionFromNV > PS_PTL_VER_R11)
        {
            cVersion = PS_PTL_VER_R11;
        }
        else
        {
            cVersion = cVersionFromNV;
        }
    }


    return cVersion;
}


/*****************************************************************************
 函 数 名  : NAS_ImsiToImsiStr
 功能描述  : 将全局变量的Imsi转换成字串形式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期  : 2009年7月3日
   作    者  : h44270
   修改内容  : creat function
*****************************************************************************/
VOS_VOID NAS_ImsiToImsiStr(VOS_CHAR  *pcImsi)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucImsi;

    pucImsi = NAS_MML_GetSimImsi();

    for (i = 1; i < 9; i++)
    {
        /*lint -e961*/
        if (1 == i)
        {
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        else
        {
            *pcImsi++ = (pucImsi[i] & 0x0f) + 0x30;
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        /*lint +e961*/
    }
}


/*****************************************************************************
 函 数 名  : NAS_PreventTestImsiRegFlg
 功能描述  : 在NV项激活时，判定当前的IMSI是否是测试号段，是的话返回VOS_TRUE,
              其他情况下，都返回VOS_FALSE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_BOOL NAS_PreventTestImsiRegFlg(VOS_VOID)
{
    VOS_CHAR                            *pcLabImsi1="00101";
    VOS_CHAR                            *pcLabImsi2="00102";
    VOS_CHAR                            *pcLabImsi3="00201";
    VOS_INT                             iImsiCmpRslt1,iImsiCmpRslt2,iImsiCmpRslt3;
    VOS_UINT32                          ulResult;
    NAS_PREVENT_TEST_IMSI_REG_STRU      stTestImsiFlg;
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_UINT32                          ulLength;

    ulLength = 0;


    stTestImsiFlg.ucStatus = VOS_FALSE;
    stTestImsiFlg.ucActFlg = VOS_FALSE;

    (VOS_VOID)NV_GetLength(en_NV_Item_PREVENT_TEST_IMSI_REG, &ulLength);
    if (ulLength > sizeof(stTestImsiFlg))
    {
        return VOS_FALSE;
    }
    ulResult = NV_Read(en_NV_Item_PREVENT_TEST_IMSI_REG,
                       &stTestImsiFlg,
                       ulLength);
    if (NV_OK != ulResult)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_PreventTestImsiRegFlg:WARNING: Read en_NV_Item_PREVENT_TEST_IMIS_REG Err");
        return VOS_FALSE;
    }

    /* stTestImsiFlg.ucStatus = 0; */
    /* stTestImsiFlg.ucActFlg = 0; */

    /* 在NV项激活的情况下，判定是否有特殊的号段 */
    if ((VOS_TRUE == stTestImsiFlg.ucStatus)
     && (VOS_TRUE == stTestImsiFlg.ucActFlg))
    {
        NAS_ImsiToImsiStr(acTmpImsi);

        iImsiCmpRslt1 = VOS_MemCmp(acTmpImsi, pcLabImsi1, 5);
        iImsiCmpRslt2 = VOS_MemCmp(acTmpImsi, pcLabImsi2, 5);
        iImsiCmpRslt3 = VOS_MemCmp(acTmpImsi, pcLabImsi3, 5);

        if ((0 == iImsiCmpRslt1)
          ||(0 == iImsiCmpRslt2)
          ||(0 == iImsiCmpRslt3))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_ConvertSessionTypeToMTCFormat
 功能描述  : 将NAS Session Type转换成MTC的Session Type
 输入参数  : RRC_NAS_SESSION_TYPE_ENUM_UINT8
 输出参数  : MTC_SESSION_TYPE_ENUM_UINT8
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
VOS_UINT32 NAS_ConvertSessionTypeToMTCFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enNasSessionType,
    MTC_SESSION_TYPE_ENUM_UINT8        *penMtcSessionType
)
{
    VOS_UINT32                          ulMaxIndex;
    VOS_UINT32                          i;

    ulMaxIndex  = sizeof(g_stNasConvertMtcSessiontype) / sizeof(NAS_CONVERT_MTC_SESSION_STRU);

    for (i = 0; i < ulMaxIndex; i++)
    {
        if (enNasSessionType == g_stNasConvertMtcSessiontype[i].enNasSessionType)
        {
            *penMtcSessionType = g_stNasConvertMtcSessiontype[i].enMtcSessionType;
            return VOS_OK;
        }
    }

    *penMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_ConvertSessionTypeToMTCFormat:ERROR: Convert session type err!");

    return VOS_ERR;
}



/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

