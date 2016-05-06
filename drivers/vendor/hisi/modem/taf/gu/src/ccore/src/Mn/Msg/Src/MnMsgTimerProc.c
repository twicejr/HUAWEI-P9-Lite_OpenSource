/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgTimerProc.c
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月21日
  最近修改   :
  功能描述   : 实现MSG模块接收到Timer发送过来消息的函数接口
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月21日
    作    者   : 周君 40661
    修改内容   : 创建文件
  2.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D03741,编程规范问题：   1。枚举类型定义   2。全局变量的外部声名   3。文件或函数的注释问题；   打印信息不完整   1。增加调试打印代码
  3.日    期   : 2008年8月29日
    作    者   : fuyingjun
    修改内容   : 问题单号:AT2D05344, 短消息模块初始化过程结束后进行SDT工具与单板反复进行连接和断开操作,协议栈会重复上报初始化完成事件;
  4.日    期   : 2009年3月3日
    作    者   : z40661
    修改内容   : 问题单号：AT2D07942（AT2D09557）, 短信中心号码上报时间较长
  5.日    期   : 2009年3月3日
    作    者   : z40661
    修改内容   : 问题单号：AT2D08974, 短信打印级别过高
  6.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
  7.日    期   : 2009年4月1日
    作    者   : 周君 40661
    修改内容   : 问题单号:AT2D09786, 用AT+CMGD=,4删除短信时，长时间不回应，导致自动化脚本检测不到单板
  8.日    期   : 2009年7月18日
    作    者   : z40661
    修改内容   : 终端可配置需求合入
  9.日    期   : 2009年8月21日
    作    者   : f62575
    修改内容   : 问题单号:AT2D13974, 实验室网络环境下服务域为PS Only设置下发短信失败

 10.日    期   : 2010年5月7日
    作    者   : zhoujun /z40661
    修改内容   : AT2D19153，重发时间不够时，未能停止定时器
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "MnMsgInclude.h"
#include  "TafSdcCtx.h"

#include "MnMsgSendSpm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_TIMERPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 类型定义
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId;
}MN_MSG_TIMER_HANDLE_STRU;

/* 超时处理函数的类型定义 */
typedef VOS_VOID (* MN_MSG_TIMEOUT_PROC_FUNC)(VOS_UINT32 ulParam);

/* 定时器信息结构 */
typedef struct
{
    VOS_UINT32                          ulTimeout;
    MN_MSG_TIMEOUT_PROC_FUNC            pfnTimeoutProc;
} MN_MSG_TIMER_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulTimeLen;
}MN_MSG_TIMER_OPERATION_STRU;

LOCAL MN_CLIENT_ID_T                    g_clientId;
LOCAL MN_OPERATION_ID_T                 g_opId;
LOCAL VOS_UINT32                        g_ulLeftReportNum;
LOCAL MN_MSG_LIST_PARM_STRU             g_stList;

/*****************************************************************************
  3 函数声明
*****************************************************************************/
LOCAL VOS_VOID  MSG_GetEfCnfTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID  MSG_LinkCtrlTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitUsimTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitRetryPeriodTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitRetryIntervalTimeout(
    VOS_UINT32                          ulParam
);


LOCAL VOS_VOID MSG_WaitFdnCheckTimeout(
    VOS_UINT32                          ulParam
);


LOCAL VOS_VOID  MSG_WaitSmsMoControlCheckTimeout(
    VOS_UINT32                          ulParam
);

/*****************************************************************************
  4 变量定义
*****************************************************************************/
/* 所有可用的定时器资源 */
MN_MSG_TIMER_HANDLE_STRU                f_astMsgTimerHandle[MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG];

/*定时器信息表，该表中记录了每种定时器的超时时间和超时处理函数 */
MN_MSG_TIMER_INFO_STRU                  f_astMsgTimerInfoTbl[MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG] = {
    {60000, MSG_GetEfCnfTimeout},
    {3500, MSG_LinkCtrlTimeout},
    {10000,MSG_WaitUsimTimeout},
    {30000,MSG_WaitRetryPeriodTimeout},
    {5000,MSG_WaitRetryIntervalTimeout},
    {5000, MSG_WaitFdnCheckTimeout},
    {5000, MSG_WaitSmsMoControlCheckTimeout},
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    {60000,  TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired},
#if (FEATURE_ON == FEATURE_ETWS)
    {600000, TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired}                        /* 收到主通知时临时使能CBS的定时器 */
#endif
#endif
};

/*lint -save -e958 */

/*****************************************************************************
  5 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MN_MSG_PrintTimerInfo
 功能描述  : 定时器数据的打印函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月14日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_PrintTimerInfo(VOS_VOID)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); ulLoop++)
    {
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer No           ", (VOS_INT32)ulLoop);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer handle id    ", (VOS_INT32)f_astMsgTimerHandle[ulLoop].enTimerId);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer handle hTimer", (VOS_INT32)f_astMsgTimerHandle[ulLoop].hTimer);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer Table Length ", (VOS_INT32)f_astMsgTimerInfoTbl[ulLoop].ulTimeout);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer Table handle ", (VOS_INT32)f_astMsgTimerInfoTbl[ulLoop].pfnTimeoutProc);
    }
}

/*****************************************************************************
 函 数 名  : MSG_GetEfSmsTimerout
 功能描述  : 等待EFSMS文件时,定时器超时后如果当前还有文件未能读取,则继续读取下一
             个EFSMS文件,否则,根据其他文件在USIM中的存在情况向USIM请求其他文件的
             读取,如无其他文件存在,则上报初始化完成
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月21日
    作    者   : 周君 40661
    修改内容   : 新生成函数
 2.日    期   : 2013年8月3日
   作    者   : z60575
   修改内容   : TQE修改

*****************************************************************************/
VOS_VOID MSG_GetEfSmsTimerout(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MN_MSG_USIM_EFUST_INFO_STRU         stUstInfo;
    VOS_UINT8                           ucCurrRec;
    VOS_UINT32                          ulFileId[2];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId[0]    = USIMM_USIM_EFSMS_ID;
        ulFileId[1]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId[0]    = USIMM_TELE_EFSMS_ID;
        ulFileId[1]    = USIMM_TELE_EFSMSR_ID;
    }

    PS_MEM_SET(&stUstInfo, 0, sizeof(stUstInfo));

    /*获取下一条记录*/
    ucCurrRec = MN_MSG_GetSmCurrRecFromUsim();
    if (ucCurrRec < MN_MSG_GetSmCapacity(MN_MSG_MEM_STORE_SIM))
    {
        /*lint -e961*/
        MN_MSG_SetSmCurrRecFromUsim(++ucCurrRec);
        /*lint +e961*/
        ulRet = MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId[0], ucCurrRec);
        if (USIMM_API_SUCCESS == ulRet)
        {
            return;
        }
    }
    else
    {
        MN_MSG_SetSmCurrRecFromUsim(0);
    }

    MN_MSG_ReadUstInfo(&stUstInfo);
    if (VOS_TRUE == stUstInfo.bEfSmsrFlag)
    {
        ulRet =  MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId[1], 0);;
        if (USIMM_API_SUCCESS == ulRet)
        {
            return;
        }
    }

    /*无文件需要读取,置为上电完成*/
    MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_ON);

    /*向应用上报初始化完成*/
    MN_MSG_SmInitFinish(MN_CLIENT_ALL);
}

/*****************************************************************************
 函 数 名  : MSG_LinkCtrlTimeout
 功能描述  : 收到短信中继链路控制定时器超时指示SMS释放链路
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_LinkCtrlTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl;
    MN_MSG_MO_STATE_ENUM_U8             enMoState;

    enMoState = MN_MSG_GetMoState();
    enLinkCtrl = MN_MSG_GetLinkCtrlParam();
    if ((MN_MSG_LINK_CTRL_ONEOFF_ENABLE == enLinkCtrl)
     && (MN_MSG_MO_STATE_WAIT_REPORT_IND != enMoState))
    {
        (VOS_VOID)MN_MSG_UpdateLinkCtrlParam(MN_MSG_LINK_CTRL_DISABLE);
    }

    MN_MSG_SendSmsCpAckReq();
    return;
}

/*****************************************************************************
 函 数 名  : MSG_WaitUsimTimeout
 功能描述  : 等待USIM处理一些节点后,继续向USIM发送节点信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitUsimTimeout(
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulRealRec;
    VOS_BOOL                            bNeedSendUsim[255];
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulTotalNum = 0;
    VOS_BOOL                            bNeedStartTimer = VOS_FALSE;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType = TAF_SDC_GetSimType();

    PS_MEM_SET(bNeedSendUsim, 0, sizeof(bNeedSendUsim));

    MN_MSG_GetNeedSendUsim(&ulRealRec, bNeedSendUsim);
    for (i = 0; i < ulRealRec; i++)
    {
        if (VOS_TRUE == bNeedSendUsim[i])
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_ReadSmsInfo(MN_MSG_MEM_STORE_SIM,i,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
                continue;
            }
            if (EF_SMS_STATUS_MT_READ != (aucSmContent[0] & 0x03))
            {
                MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
                continue;
            }
            aucSmContent[0] = EF_SMS_STATUS_MT_READ;

            if (TAF_SDC_SIM_TYPE_SIM == enSimType)
            {
                ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID, aucSmContent, MN_MSG_EFSMS_LEN, (VOS_UINT8)(i + 1));
            }
            else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
            {
                ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID, aucSmContent, MN_MSG_EFSMS_LEN, (VOS_UINT8)(i + 1));
            }
            else
            {
                ulRet = USIMM_API_FAILED;
            }

            if (USIMM_API_SUCCESS != ulRet)
            {
                MN_WARN_LOG("MSG_WaitUsimTimeout:Add Usim Node Failed");
                bNeedStartTimer = VOS_TRUE;
                break;
            }
            ulTotalNum++;
            MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
        }
        if (ulTotalNum >=  MN_MSG_MAX_CHG_SM_STATE_NUM)
        {
            break;
        }
    }

    if ( (i + 1) < ulRealRec)
    {
        bNeedStartTimer = VOS_TRUE;
    }

    if (VOS_TRUE == bNeedStartTimer)
    {
        MN_MSG_StartTimer(MN_MSG_TID_WAIT_USIM,0);
    }
}

/*****************************************************************************
 函 数 名  : MSG_GetEfCnfTimeout()
 功能描述  : 初始化时读取USIM中的EFSMSS,EFSMSP,EFSMS,EFSMSR文件时,定时器超时后的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年2月04日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID  MSG_GetEfCnfTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    MN_MSG_GetUsimPowerState(&enPowerState);
    switch (enPowerState)
    {
        case MN_MSG_USIM_POWER_WAIT_EFSMSS:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSS");
            /*获取EFSMSP文件的内容*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSP_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSP_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSP:
            /* 上报EFSMSP文件读取完成 */
            MN_MSG_SmspInitFinish(MN_CLIENT_ALL);
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSP");
            /*获取EFSMS文件的内容*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMS_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMS_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSREC:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSREC");
            /*获取EFSMSR文件的内容*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSR_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSR_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMS:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMS");
            MSG_GetEfSmsTimerout();
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSR:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSR");
            /*上报初始化完成*/
            MN_MSG_GetUsimParmReq(USIMM_DEF_FILEID_BUTT);
            break;
        default:
            MN_WARN_LOG("MSG_GetEfCnfTimeout:Invalid enPowerState");
            break;
    }
}

/*****************************************************************************
 函 数 名  : MSG_WaitRetryPeriodTimeout()
 功能描述  : 重发周期定时器超时,不做任何处理,仅记录日志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitRetryPeriodTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_INFO_LOG("MSG_WaitRetryPeriodTimeout:RetryPeriodTimeout");
}

/*****************************************************************************
 函 数 名  : MSG_GetRetrySendDomain
 功能描述  : 获取短信发送重发承载域
             在用户配置了CS域为发送承载域的情况下优先在CS域重发
             否则，考虑在PS域重发短信
 输入参数  : MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain 用户期望发送短信的承载域集
 输出参数  : MN_MSG_SEND_DOMAIN_ENUM_U8         *penSendDomain    当前可用的发送域
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月29日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MSG_GetRetrySendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8         *penSendDomain
)
{
    /* 此处修改:
       修改前: 只有CS域有重发功能,PS域不存在此功能
       修改后: 支持在CS域和PS域重发 */
    *penSendDomain = MN_MSG_SEND_DOMAIN_NO;

    if ((MN_MSG_SEND_DOMAIN_CS == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain))
    {
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS, penSendDomain);
    }

    if (MN_MSG_SEND_DOMAIN_NO != *penSendDomain)
    {
        return;
    }

    if ((MN_MSG_SEND_DOMAIN_PS == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain))
    {
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS, penSendDomain);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MSG_WaitRetryIntervalTimeout()
 功能描述  : 重发时间间隔定时器超时,重新发送短信
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数

  2.日    期   : 2010年5月7日
    作    者   : zhoujun /z40661
    修改内容   : AT2D19153，重发时间不够时，未能停止定时器
  3.日    期   : 2011年3月29日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011030500602，增加CS域可用的判断标准，UE服务域为非PS
                 ONLY, IMSI在CS域有效且CS域未被BAR情况下可以尝试重发，支持在PS域重发短信
  4.日    期   : 2012年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012110604069，TAF层重发的SUBMIT短信TP-RD应该修改为1，
                 指示短信中心拒绝接收重复短信
  5.日    期   : 2012年12月28日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012122406218, 短信正向质量发现问题: 短信发送流程部分
  6.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
  7.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  8.日    期   : 2013年7月15日
    作    者   : y00245242
    修改内容   : 增加消息路由，定时器超时时，能正确路由   
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitRetryIntervalTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    SMR_SMT_MO_REPORT_STRU              stRpErrInfo;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    MN_MSG_GetMoEntity(&stMoEntity);

    PS_MEM_SET(&stRpErrInfo, 0, sizeof(stRpErrInfo));

    /* 当前不是发送短信过程中 */
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_WaitRetryIntervalTimeout:Mo State is NULL");
        return;
    }

    MSG_GetRetrySendDomain(stMoEntity.enHopeSendDomain, &stMoEntity.enSendDomain);

    if (MN_MSG_SEND_DOMAIN_NO != stMoEntity.enSendDomain)
    {
        /* TAF层重发的SUBMIT短信TP-RD应该修改为1，指示短信中心拒绝接收重复短信 */
        MN_MSG_SetTpRd(&stMoEntity);

        /*将一条完整的RP-Data发送给NAS层的SMS模块*/
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
        ulRet = MN_MSG_SendSmsRpDataReq(stMoEntity.enSendDomain,
                                        stMoEntity.aucRpDataInfo,
                                        stMoEntity.ucRpDataLen,
                                        stMoEntity.enMsgSignallingType);        
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */
        
        if (VOS_OK == ulRet)
        {
            /* 更新MO变量 */
            MN_MSG_CreateMoInfo(&stMoEntity);
            return;
        }

    }

    /* 上报发送短信失败 */
    MN_MSG_GetRpErrInfo(&stRpErrInfo);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MN_MSG_RcvSmsRpRpt(&stRpErrInfo);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    /*  还需要停止定时器 */
    MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);
}

/*****************************************************************************
 函 数 名  : MSG_WaitFdnCheckTimeout
 功能描述  : 等待USIM的FDN检查结果超时处理
 输入参数  : ulParam        短信模块定时器透传参数，FDN场景未使用
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年02月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitFdnCheckTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_BOOL                            bBufferEntity;

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    /* 获取等待FDN检查结果的MO实体或缓存 */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: discard SMS MO CONTROL RESPONSE.");
        return;
    }

    /* MO状态不匹配: 没有等待SMS MO CONTROL RESPONSE消息 */
    if (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_WaitFdnCheckTimeout: Mo State is invalid.");
        return;
    }

    /*
    等待USIM模块的FDN消息超时:
            通知APP短信发送请求被拒绝；
            释放短信发送实体；
    */
    MN_WARN_LOG("MSG_WaitFdnCheckTimeout: wait for FDN check response timeout.");
    MN_SendClientResponse(stMoEntity.clientId,
                          stMoEntity.opId,
                          MN_ERR_CLASS_SMS_INTERNAL);

    /* 销毁等待FDN检查结果的MO实体或缓存 */
    MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);

    /* 通知SPM检查结果 */
    TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_FDN_CHECK_TIMEROUT);

    return;

}

/*****************************************************************************
 函 数 名  : MN_MSG_InitAllTimers
 功能描述  : 初始化所有定时器，应在初始化及Reset时被调用
 输入参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月04日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_InitAllTimers(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        f_astMsgTimerHandle[i].hTimer = VOS_NULL_PTR;
        f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_StartTimer
 功能描述  : 启动指定的定时器
 输入参数  : enTimerId:指定定时器TimerId
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_StartTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        MN_WARN_LOG("MN_MSG_StartTimer: Invalid enTimerId. ");
        return;
    }

    /* 寻找空闲的定时器句柄 */
    for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        if (VOS_NULL_PTR == f_astMsgTimerHandle[i].hTimer)
        {
            break;
        }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        /* 启动VOS定时器 */
        ulRet = NAS_StartRelTimer(&f_astMsgTimerHandle[i].hTimer,
                                  WUEPS_PID_TAF,
                                  f_astMsgTimerInfoTbl[enTimerId - MN_TIMER_CLASS_MSG].ulTimeout,
                                  (VOS_UINT32)enTimerId,
                                  ulParam,
                                  VOS_RELTIMER_NOLOOP);
        if (VOS_OK == ulRet)
        {
            /* 记录超时处理函数 */
            f_astMsgTimerHandle[i].enTimerId = enTimerId;
        }
        else
        {
            MN_WARN_LOG("MN_MSG_StartTimer: VOS_StartRelTimer failed.");
        }
    }
    else
    {
        MN_WARN_LOG("MN_MSG_StartTimer: Can not find free timer handle.");
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_StopTimer
 功能描述  : 停止指定的定时器
 输入参数  : enTimerId:指定定时器TimerId
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年11月26日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_StopTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return;
    }

    /* 寻找entityId和enTimerId与输入匹配的句柄 */
    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        /* 停止VOS定时器 */
        ulRet = NAS_StopRelTimer(WUEPS_PID_TAF, enTimerId, &f_astMsgTimerHandle[i].hTimer);
        if (VOS_OK == ulRet)
        {
            f_astMsgTimerHandle[i].hTimer = VOS_NULL_PTR;
            f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
        }
        else
        {
            MN_WARN_LOG("MN_MSG_StopTimer: NAS_StopRelTimer failed.");
        }
    }
    else
    {
        MN_WARN_LOG("MN_MSG_StopTimer: Can not find the timer handle.");
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_StopAllRunningTimer
 功能描述  : 停止运行当前所有正在运行的定时器
 输入参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月1日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_StopAllRunningTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        if ( (VOS_NULL_PTR      != f_astMsgTimerHandle[i].hTimer)
          && (MN_MSG_TID_MAX    != f_astMsgTimerHandle[i].enTimerId) )
        {
             /* 停止VOS定时器 */
            if (VOS_OK == NAS_StopRelTimer(WUEPS_PID_TAF,
                                 f_astMsgTimerHandle[i].enTimerId,
                                 &f_astMsgTimerHandle[i].hTimer))
            {
                f_astMsgTimerHandle[i].hTimer    = VOS_NULL_PTR;
                f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
            }
            else
            {
                MN_WARN_LOG("MN_MSG_StopAllRunningTimer: NAS_StopRelTimer failed.");
            }
        }
    }

    return;
}



/*****************************************************************************
 函 数 名  : MN_MSG_IsTimerStarting
 功能描述  : 判断某个定时器当前是否时开启状态
 输入参数  : enTimerId:指定定时器TimerId
 输出参数  : 无
 返 回 值  : VOS_TRUE:该定时器已开启
             VOS_FALSE:该定时器已关闭

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月18日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_UINT32  MN_MSG_IsTimerStarting(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          i;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        if (VOS_NULL_PTR != f_astMsgTimerHandle[i].hTimer)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : MN_MSG_GetTimerRemainTime
 功能描述  : 获取定时器剩余的时间
 输入参数  : enTimerId:指定定时器TimerId
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月18日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
*****************************************************************************/
VOS_UINT32  MN_MSG_GetTimerRemainTime(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          i;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return 0;
    }
    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }
    if ( i >= (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        return 0;
    }

    ulTick = 0;

    /* hTimer 为空时，说明此定时器已超时或停止 */
    if (VOS_NULL_PTR != f_astMsgTimerHandle[i].hTimer)
    {
        if (VOS_OK != VOS_GetRelTmRemainTime(&(f_astMsgTimerHandle[i].hTimer), &ulTick))
        {
            ulTick = 0;
        }
    }
    return ulTick * MN_MSG_TIMER_TICK;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateRetryPeriod
 功能描述  : 更新定时器模块中当前短信重发时间周期和时间间隔
 输入参数  : enTimerId :当前定时器ID
             ulTimerLen:更新后定时器的时长
 无 输出参数  :
 返 回 值  :无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_UpdateRetryPeriod(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    VOS_UINT32                          i = (VOS_UINT32)(enTimerId - MN_TIMER_CLASS_MSG);

    if ( i >= (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG) )
    {
        MN_WARN_LOG("MN_MSG_UpdateRetryPeriod: Can not find the timer Id.");
        return;
    }
    f_astMsgTimerInfoTbl[i].ulTimeout = ulTimerLen;
}


/*****************************************************************************
 函 数 名  : MN_MSG_UpdateListInfo
 功能描述  : 更新列表上报给APP时所需参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_MSG_UpdateListInfo(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList
)
{
    g_clientId = clientId;
    g_opId = opId;
    g_ulLeftReportNum = ulLeftReportNum;
    PS_MEM_CPY(&g_stList,pstList,sizeof(g_stList));

}

/*****************************************************************************
 函 数 名  : MSG_ListMsgWaitAppTimeout
 功能描述  : 列表定时器超时后上报应用剩余需列表的短信
 输入参数  : ulParam  -  定时器参数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年1月10日
    作    者   : 傅映君/f62575
    修改内容   : DTS2010010400031 组合AT命令AT+CPMS="SM";+CMGL=4无响应
  3.日    期   : 2012年12月12日
    作    者   : z60575
    修改内容   : TQE修改

  4.日    期   : 2013年9月29日
    作    者   : w00167002
    修改内容   : DTS201309210014:删除C核TASKDELAY处理，在V9低功耗时，会导致
                   TASKDELAY后未被唤醒，导致AT消息没有回复。
                 MSG_ListMsgWaitAppTimeout函数更名为TAF_MSG_ListLeftMsg.
                 并进行函数位置调整。

*****************************************************************************/
VOS_VOID TAF_MSG_ListLeftMsg(VOS_VOID)
{
    MN_MSG_LIST_EVT_INFO_STRU           *pstListEvt;


    pstListEvt = (MN_MSG_LIST_EVT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_LIST_EVT_INFO_STRU));
    if (VOS_NULL_PTR == pstListEvt)
    {
        MN_ERR_LOG("TAF_MSG_ListLeftMsg:ALLOC MEM FAIL");
        return;
    }
    else
    {
        pstListEvt->bSuccess = VOS_TRUE;
        pstListEvt->bLastListEvt = VOS_TRUE;
        pstListEvt->bFirstListEvt = VOS_FALSE;

        PS_MEM_CPY( &(pstListEvt->stReceivedListPara), &g_stList, sizeof(MN_MSG_LIST_PARM_STRU) );
    }

    if (0 == g_ulLeftReportNum)
    {
        pstListEvt->ulReportNum = 0;
        pstListEvt->ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportListEvent(g_clientId,g_opId,pstListEvt,MN_MSG_EVT_LIST);
    }
    else
    {
        /* 调用函数分段上报需列表个数 */
        MN_MSG_RptMsg(g_clientId, g_opId, g_ulLeftReportNum, &g_stList, pstListEvt);
    }
    PS_MEM_FREE(WUEPS_PID_TAF, pstListEvt);
}


/*****************************************************************************
 函 数 名  : MN_MSG_ProcTimeoutMsg
 功能描述  : 处理定时器超时消息。
 输入参数  : pMsg  - 定时器超时消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月04日
    作    者   : 周君40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_ProcTimeoutMsg(
    REL_TIMER_MSG                       * pTmrMsg
)
{
    MN_MSG_TIMER_HANDLE_STRU            *pstHandle;
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          i;

    enTimerId = (MN_MSG_TIMER_ID_ENUM_U32)pTmrMsg->ulName;
    if (enTimerId < MN_TIMER_CLASS_MSG)
    {
        return;
    }
    else
    {
        for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
        {
            if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
            {
                break;
            }
        }

        if ( i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG) )
        {
            ulIndex = enTimerId - MN_TIMER_CLASS_MSG;

        }
        else
        {
            MN_WARN_LOG1("MN_MSG_ProcTimeoutMsg:Invalid Timer ID", (VOS_INT32)enTimerId);
            return;
        }
    }

    MN_NORM_LOG1("TAF SMA Timer expired.", (VOS_INT32)enTimerId);

    /* 由ulName得到定时器句柄 将该句柄复位 */
    pstHandle = (MN_MSG_TIMER_HANDLE_STRU *)&f_astMsgTimerHandle[i];
    pstHandle->hTimer = VOS_NULL_PTR;
    pstHandle->enTimerId = MN_MSG_TID_MAX;

    /* 调用Timer ID对应的超时处理函数 */
    f_astMsgTimerInfoTbl[ulIndex].pfnTimeoutProc(pTmrMsg->ulPara);
}

/*****************************************************************************
 函 数 名  : MSG_WaitSmsMoControlCheckTimeout
 功能描述  : 等待USIM的SMS MO CONTROL检查结果超时处理
 输入参数  : ulParam        短信模块定时器透传参数，SMS MO CONTROL场景未使用
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年09月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID  MSG_WaitSmsMoControlCheckTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_BOOL                            bBufferEntity;

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    /* 获取等待FDN检查结果的MO实体或缓存 */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: discard SMS MO CONTROL RESPONSE.");
        return;
    }

    /*
    等待USIM模块的SMS MO CONTROL RESPONSE消息超时:
            通知APP短信发送请求被拒绝；
            释放短信发送实体；
    */
    MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: wait for SMS MO CONTROL RESPONSE timeout.");
    MN_SendClientResponse(stMoEntity.clientId,
                          stMoEntity.opId,
                          MN_ERR_CLASS_SMS_INTERNAL);

    /* 销毁等待SMS MO CONTROL检查结果的MO实体或缓存 */
    MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);

    /* 通知SPM检查结果 */
    TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_CTRL_CHECK_TIMEOUT);

    return;

}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

