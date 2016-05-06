/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : DRVAGENTMain.c
  版 本 号   : 初稿
  作    者   : 鲁琳/l60609
  生成日期   : 2011年10月3日
  最近修改   :
  功能描述   : At Agent
  函数列表   :
  修改历史   :
  1.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : 创建文件
  2.日    期   : 2011年12月31日
    作    者   : s46746
    修改内容   : 删除^HWNATQRY命令

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafDrvAgentMain.h"
#include "TafDrvAgent.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_DRVAGENT_TASK_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*DrvAgent模块保存平台特性*/
VOS_UINT8                            g_ucDrvAgentSystemAppConfigAddr;

/*AT AGENT模块消息处理函数对应表*/
const DRV_AGENT_MSG_PROC_STRU g_astDrvAgentMsgProcTab[]=
{
    /* 消息ID */                            /* 消息处理函数 */
    {DRV_AGENT_MSID_QRY_REQ,                DRVAGENT_RcvDrvAgentMsidQryReq},
    {DRV_AGENT_GCF_IND,                     DRVAGENT_RcvDrvAgentGcfInd},
    {DRV_AGENT_GAS_MNTN_CMD,                DRVAGENT_RcvDrvAgentGasMntnCmd},

    {DRV_AGENT_HARDWARE_QRY,                DRVAGENT_RcvDrvAgentHardwareQry},
    {DRV_AGENT_FULL_HARDWARE_QRY,           DRVAGENT_RcvDrvAgentFullHardwareQry},
    {DRV_AGENT_RXDIV_SET_REQ,               DRVAGENT_RcvDrvAgentSetRxdiv},
    {DRV_AGENT_RXDIV_QRY_REQ,               DRVAGENT_RcvDrvAgentQryRxdiv},
    {DRV_AGENT_SIMLOCK_SET_REQ,             DRVAGENT_RcvDrvAgentSetSimlock},

    {DRV_AGENT_VERTIME_QRY_REQ,             DRVAGENT_RcvDrvAgentVertimeQry},

    {DRV_AGENT_YJCX_SET_REQ,                DRVAGENT_RcvDrvAgentYjcxSet},
    {DRV_AGENT_YJCX_QRY_REQ,                DRVAGENT_RcvDrvAgentYjcxQry},

    {DRV_AGENT_GPIOPL_SET_REQ,              DRVAGENT_RcvDrvAgentDeviceGpioplSet},
    {DRV_AGENT_GPIOPL_QRY_REQ,              DRVAGENT_RcvDrvAgentDeviceGpioplQry},
    {DRV_AGENT_DATALOCK_SET_REQ,            DRVAGENT_RcvDrvAgentDeviceDatalockSet},
    {DRV_AGENT_TBATVOLT_QRY_REQ,            DRVAGENT_RcvDrvAgentDeviceTbatvoltQry},
    {DRV_AGENT_TMODE_SET_REQ,               DRVAGENT_RcvDrvAgentDeviceTmodeSet},
    {DRV_AGENT_VERSION_QRY_REQ,             DRVAGENT_RcvDrvAgentDeviceVersionQry},
    {DRV_AGENT_SECUBOOT_QRY_REQ,            DRVAGENT_RcvDrvAgentDeviceSecuBootQry},
    {DRV_AGENT_FCHAN_SET_REQ,               DRVAGENT_RcvDrvAgentDeviceFchanSet},

    {DRV_AGENT_SFEATURE_QRY_REQ,            DRVAGENT_RcvDrvAgentDeviceSfeatureQry},
    {DRV_AGENT_PRODTYPE_QRY_REQ,            DRVAGENT_RcvDrvAgentDeviceProdtypeQry},


    {DRV_AGENT_APPDMVER_QRY_REQ,            DRVAGENT_RcvDrvAgentAppdmverReq},
    {DRV_AGENT_DLOADINFO_QRY_REQ,           DRVAGENT_RcvDrvAgentDloadInfoReq},
    {DRV_AGENT_FLASHINFO_QRY_REQ,           DRVAGENT_RcvDrvAgentFlashInfoQry},
    {DRV_AGENT_AUTHORITYVER_QRY_REQ,        DRVAGENT_RcvDrvAgentAuthorityVerQry},
    {DRV_AGENT_AUTHORITYID_QRY_REQ,         DRVAGENT_RcvDrvAgentAuthorityIdQry},
    {DRV_AGENT_AUTHVER_QRY_REQ,             DRVAGENT_RcvDrvAgentAuthVerQry},
    {DRV_AGENT_GODLOAD_SET_REQ,             DRVAGENT_RcvDrvAgentGodloadSet},
    {DRV_AGENT_PFVER_QRY_REQ,               DRVAGENT_RcvDrvAgentPfverQry},
    {DRV_AGENT_SDLOAD_SET_REQ,              DRVAGENT_RcvDrvAgentSdloadSet},
    {DRV_AGENT_SDREBOOT_REQ,                DRVAGENT_RcvDrvAgentSdRebootReq},
    {DRV_AGENT_DLOADVER_QRY_REQ,            DRVAGENT_RcvDrvAgentDloadVerQryReq},
    {DRV_AGENT_TSELRF_SET_REQ,              DRVAGENT_RcvDrvAgentTseLrfSet},
    {DRV_AGENT_HKADC_GET_REQ,               DRVAGENT_RcvDrvAgentHkAdcGet},
    {DRV_AGENT_TBAT_QRY_REQ,                DRVAGENT_RcvDrvAgentTbatQry},
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
    {DRV_AGENT_CPULOAD_QRY_REQ,             DRVAGENT_RcvDrvAgentCpuloadQry},
    {DRV_AGENT_MFREELOCKSIZE_QRY_REQ,       DRVAGENT_RcvDrvAgentMfreelocksizeQry},
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
    {DRV_AGENT_MEMINFO_QRY_REQ,             DRVAGENT_RcvDrvAgentMemInfoQry},
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */
    {DRV_AGENT_IMSICHG_QRY_REQ,             DRVAGENT_RcvDrvAgentImsiChgQry},
    {DRV_AGENT_INFORBU_SET_REQ,             DRVAGENT_RcvDrvAgentInfoRbuSet},
    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/
    #if ( FEATURE_ON == FEATURE_LTE )
    {DRV_AGENT_INFORRS_SET_REQ,             DRVAGENT_RcvDrvAgentInfoRrsSet},
    #endif
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合*/
    {DRV_AGENT_CPNN_QRY_REQ,                DRVAGENT_RcvDrvAgentCpnnQry},
    {DRV_AGENT_CPNN_TEST_REQ,               DRVAGENT_RcvDrvAgentCpnnTest},
    {DRV_AGENT_NVBACKUP_SET_REQ,            DRVAGENT_RcvDrvAgentNvBackupSet},

    {DRV_AGENT_NVRESTORE_SET_REQ,           DRVAGENT_RcvDrvAgentSetNvRestore},
    {DRV_AGENT_NVRSTSTTS_QRY_REQ,           DRVAGENT_RcvDrvAgentQryNvRestoreRst},
    {DRV_AGENT_NVRESTORE_MANU_DEFAULT_REQ,  DRVAGENT_RcvDrvAgentNvRestoreManuDefault},

    {DRV_AGENT_ADC_SET_REQ,                 DRVAGENT_RcvDrvAgentAdcSet},
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
    {DRV_AGENT_SPWORD_SET_REQ,              DRVAGENT_RcvAtSpwordSet},
#endif
    {DRV_AGENT_SIMLOCK_NV_SET_REQ,          DRVAGENT_RcvDrvAgentSetSimlockNv},
    {DRV_AGENT_PSTANDBY_SET_REQ,            DRVAGENT_RcvDrvAgentSetStandby},
    {DRV_AGENT_SECUBOOT_SET_REQ,            DRVAGENT_RcvDrvAgentSetSecuBoot},

    {DRV_AGENT_NVBACKUPSTAT_QRY_REQ,        DRVAGENT_RcvDrvAgentNvBackupStatReq},
    {DRV_AGENT_NANDBBC_QRY_REQ,             DRVAGENT_RcvDrvAgentNandBadBlockReq},
    {DRV_AGENT_NANDVER_QRY_REQ,             DRVAGENT_RcvDrvAgentNandDevInfoReq},
    {DRV_AGENT_CHIPTEMP_QRY_REQ,            DRVAGENT_RcvDrvAgentChipTempReq},


    {DRV_AGENT_SARREDUCTION_SET_REQ,        DRVAGENT_RcvDrvAgentSARReductionSet},

    {DRV_AGENT_MAX_LOCK_TIMES_SET_REQ,      DRVAGENT_RcvDrvAgentSetMaxLockTms},

    {DRV_AGENT_AP_SIMST_SET_REQ,            DRVAGENT_RcvDrvAgentSetApSimSt},

    {DRV_AGENT_HUK_SET_REQ,                 DRVAGENT_RcvDrvAgentHukSetReq},
    {DRV_AGENT_FACAUTHPUBKEY_SET_REQ,       DRVAGENT_RcvDrvAgentFacAuthPubkeySetReq},
    {DRV_AGENT_IDENTIFYSTART_SET_REQ,       DRVAGENT_RcvDrvAgentIdentifyStartSetReq},
    {DRV_AGENT_IDENTIFYEND_SET_REQ,         DRVAGENT_RcvDrvAgentIdentifyEndSetReq},
    {DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ,    DRVAGENT_RcvDrvAgentSimlockDataWriteSetReq},
    {DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ,    DRVAGENT_RcvDrvAgentPhoneSimlockInfoQryReq},
    {DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ,     DRVAGENT_RcvDrvAgentSimlockDataReadQryReq},
    {DRV_AGENT_PHONEPHYNUM_SET_REQ,         DRVAGENT_RcvDrvAgentPhonePhynumSetReq},
    {DRV_AGENT_PHONEPHYNUM_QRY_REQ,         DRVAGENT_RcvDrvAgentPhonePhynumQryReq},
    {DRV_AGENT_PORTCTRLTMP_SET_REQ,         DRVAGENT_RcvDrvAgentPortctrlTmpSetReq},
    {DRV_AGENT_PORTATTRIBSET_SET_REQ,       DRVAGENT_RcvDrvAgentPortAttribSetReq},
    {DRV_AGENT_PORTATTRIBSET_QRY_REQ,       DRVAGENT_RcvDrvAgentPortAttribQryReq},
    {DRV_AGENT_OPWORD_SET_REQ,              DRVAGENT_RcvDrvAgentOpwordSetReq},

    {DRV_AGENT_SWVER_SET_REQ,               DRVAGENT_RcvDrvAgentSwverSetReq},
    {DRV_AGENT_QRY_CCPU_MEM_INFO_REQ,       DRVAGENT_RcvDrvAgentCcpuMemQryReq},

#if (FEATURE_ON == FEATURE_VSIM)
    {DRV_AGENT_HVPDH_REQ,                   DRVAGENT_RcvDrvAgentHvpdhSetReq},
#endif

    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
    {DRV_AGENT_NVMANUFACTUREEXT_SET_REQ,    DRVAGENT_RcvDrvAgentNvManufactureExtSet},
    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */

    {DRV_AGENT_ANTSWITCH_SET_REQ,           DRVAGENT_RcvDrvAgentSetAntSwitchReq},
    {DRV_AGENT_ANTSWITCH_QRY_REQ,           DRVAGENT_RcvDrvAgentQryAntSwitchReq},


};

VOS_UINT16         *g_pusDrvAgentUsimTempTable  = VOS_NULL_PTR;                 /*SIM hkadc转换表*/
VOS_UINT16         *g_pusDrvAgentBatTempTable   = VOS_NULL_PTR;                 /*Battery hkadc转换表*/
VOS_UINT16         *g_pusDrvAgentAdcTable       = VOS_NULL_PTR;                 /*PA hkadc转换表*/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : DRVAGENT_GetSystemAppConfigAddr
 功能描述  : 获取DRVAGENT模块控制特性的NV的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 控制特性的信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月07日
   作    者   : s62952
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8* DRVAGENT_GetSystemAppConfigAddr(VOS_VOID)
{
    return &g_ucDrvAgentSystemAppConfigAddr;
}

/*****************************************************************************
 函 数 名  : DRVAGENT_ReadSystemAppConfigNV
 功能描述  : 读取特性控制NV相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月18日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月17日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID  DRVAGENT_ReadSystemAppConfigNV(VOS_VOID)
{
    VOS_UINT8                                   *pucSystemAppConfig;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU              stSysAppConfig;


    stSysAppConfig.usSysAppConfigType= SYSTEM_APP_BUTT;


    /* 获取控制特性的NV上下文地址 */
    pucSystemAppConfig                  = DRVAGENT_GetSystemAppConfigAddr();


    /*读取失败按默认值处理 */
    if (VOS_OK != NV_Read(en_NV_Item_System_APP_Config,&stSysAppConfig,sizeof(VOS_UINT16)))
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
        return;
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType)
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
    }
    else
    {
        *pucSystemAppConfig  = (VOS_UINT8)stSysAppConfig.usSysAppConfigType;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DRVAGENT_Init
 功能描述  : DRVAGENT任务初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE  ip
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  DRVAGENT_Init(enum VOS_INIT_PHASE_DEFINE  ip)
{
    switch( ip )
    {
        case VOS_IP_INITIAL:
            DRVAGENT_ReadSystemAppConfigNV();
            if (VOS_OK != DRVAGENT_TempReadInit())
            {
                MN_WARN_LOG("DRVAGENT_Init: DRVAGENT_TempReadInit Failed!");
                return VOS_ERR;
            }

            break;

        default:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DRVAGENT_DispatchMsg
 功能描述  : 分发AT发给DRVAGENT的消息
 输入参数  : struct MsgCB * pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  DRVAGENT_DispatchMsg (struct MsgCB * pstMsg)
{
    /*消息为空，直接返回*/
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("DRVAGENT_DispatchMsg: pstMsg is NULL!");
        return;
    }

    /*只接收来自AT模块的消息*/
    switch (pstMsg->ulSenderPid)
    {
        case WUEPS_PID_AT:
            DRVAGENT_ProcMsgFromAt(pstMsg);
            break;
        case WUEPS_PID_SAR:
            DRVAGENT_ProcMsgFromSPY(pstMsg);
            break;
        default:
            MN_WARN_LOG("DRVAGENT_DispatchMsg: pstMsg isn't AT!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DRVAGENT_ProcMsgFromSPY
 功能描述  : 处理来自SPY的消息
 输入参数  : const VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月9日
    作    者   : w00184875
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DRVAGENT_ProcMsgFromSPY(VOS_VOID *pMsg)
{
    MN_APP_SAR_ANTENSTATUS_MSG_STRU    *pSpyMsg;

    pSpyMsg = (MN_APP_SAR_ANTENSTATUS_MSG_STRU*)pMsg;

    if(SAR_ANTSTATE_IND == pSpyMsg->ulMsgId)
    {
        DRVAGENT_RcvDrvAgentAntStateInd(pMsg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DRVAGENT_ProcMsgFromAt
 功能描述  : 处理来自AT的消息
 输入参数  : const VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DRVAGENT_ProcMsgFromAt(VOS_VOID *pMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT16                          usMsgId;
    VOS_UINT32                          ulRst;

    /*从g_astDRVAGENTMsgProcTab中获取消息个数*/
    ulMsgCnt = sizeof(g_astDrvAgentMsgProcTab)/sizeof(DRV_AGENT_MSG_PROC_STRU);

    /*从消息包中获取MSG ID*/
    usMsgId  = ((MN_APP_REQ_MSG_STRU *)pMsg)->usMsgName;

    /*g_astDRVAGENTMsgProcTab查表，进行消息分发*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astDrvAgentMsgProcTab[i].ulMsgType == usMsgId)
        {
            ulRst = g_astDrvAgentMsgProcTab[i].pMsgProcFunc(pMsg);

            if (VOS_ERR == ulRst)
            {
                MN_ERR_LOG("DRVAGENT_ProcMsgFromAt: Msg Proc Err!");
            }

            return;
        }
    }

    /*没有找到匹配的消息*/
    if (ulMsgCnt == i)
    {
        MN_ERR_LOG("DRVAGENT_ProcMsgFromAt: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : DRVAGENT_SendMsg
 功能描述  : AT AGENT向AT发送消息函数
 输入参数  : VOS_UINT32                          ulMsgId
             VOS_UINT32                         ulLen
             VOS_UINT8                          *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

  2.日    期   : 2011年11月15日
    作    者   : o00132663
    修改内容   : AT融合项目，根据检视意见修改，结构定义前增加st
*****************************************************************************/
VOS_VOID DRVAGENT_SendMsg(
    VOS_UINT32                          ulRcvPid,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
)
{
    DRV_AGENT_MSG_STRU                 *pstDrvAgentMsgStr;
    AT_APPCTRL_STRU                    *pstAtAppCtrl = VOS_NULL_PTR;

    /* 判断输入参数 */
    if ((VOS_NULL_PTR == pData) || (0 == ulLen))
    {
        MN_ERR_LOG("DRVAGENT_SendMsg: para is invalid!");
        return;
    }

    /* 消息空间申请 */
    pstDrvAgentMsgStr = (DRV_AGENT_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_DRV_AGENT, sizeof(ulMsgId)+ ulLen);
    if (VOS_NULL_PTR == pstDrvAgentMsgStr)
    {
        MN_ERR_LOG("DRVAGENT_SendMsg: alloc msg fail!");
        return;
    }

    /* 调用MN_APS_SndPsEvt发消息的消息结构头都是AT_APPCTRL_STRU */
    pstAtAppCtrl = (AT_APPCTRL_STRU *)pData;

    pstAtAppCtrl->usClientId = MN_GetRealClientId(pstAtAppCtrl->usClientId, WUEPS_PID_DRV_AGENT);

    /* 填消息包 */
    pstDrvAgentMsgStr->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDrvAgentMsgStr->ulSenderPid     = WUEPS_PID_DRV_AGENT;
    pstDrvAgentMsgStr->ulReceiverPid   = ulRcvPid;
    pstDrvAgentMsgStr->ulMsgId         = ulMsgId;
    PS_MEM_CPY(pstDrvAgentMsgStr->aucContent, pData, ulLen);

    /* 发送消息到AT_PID */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_DRV_AGENT, pstDrvAgentMsgStr))
    {
        MN_ERR_LOG("DRVAGENT_SendMsg: send msg fail!");
        return;
    }
}

/*****************************************************************************
 函 数 名  : DRVAGENT_TempReadInit
 功能描述  : 温度读取初始化相关全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月27日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DRVAGENT_TempReadInit(VOS_VOID)
{
    VOS_UINT32      ulAdcTblLen     = VOS_NULL;
    VOS_UINT32      ulUsimTblLen    = VOS_NULL;
    VOS_UINT32      ulBattTblLen    = VOS_NULL;

    /*从NV相中读取温度转换表*/
    if (NV_OK != NV_GetLength(en_NV_Item_PA_TEMP_SENSOR_TABLE, &ulAdcTblLen))  /*获取ADC转换表长度*/
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: NV_GetLength (PA) fail.");
        return VOS_ERR;
    }

    g_pusDrvAgentAdcTable = (VOS_UINT16*)PS_MEM_ALLOC(WUEPS_PID_DRV_AGENT, ulAdcTblLen);

    if (VOS_NULL_PTR == g_pusDrvAgentAdcTable)
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: PS_MEM_ALLOC (PA) fail.");
        return VOS_ERR;
    }

    if(NV_OK != NV_Read(en_NV_Item_PA_TEMP_SENSOR_TABLE, g_pusDrvAgentAdcTable, ulAdcTblLen))/*获取ADC转换表内容*/
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: NV_Read (PA) fail.");
        return VOS_ERR;
    }

    if (NV_OK != NV_GetLength(en_NV_Item_USIM_TEMP_SENSOR_TABLE, &ulUsimTblLen))
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: NV_GetLength (USIM) fail.");
        return VOS_ERR;
    }

    g_pusDrvAgentUsimTempTable = (VOS_UINT16*)PS_MEM_ALLOC(WUEPS_PID_DRV_AGENT, ulUsimTblLen);

    if (VOS_NULL_PTR == g_pusDrvAgentUsimTempTable)
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: PS_MEM_ALLOC (USIM) fail.");
        return VOS_ERR;
    }

    if(NV_OK != NV_Read(en_NV_Item_USIM_TEMP_SENSOR_TABLE,
                        (VOS_VOID*)g_pusDrvAgentUsimTempTable, ulUsimTblLen))
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: NV_Read (USIM) fail.");
        return VOS_ERR;
    }

    if (NV_OK != NV_GetLength(en_NV_Item_BATT_TEMP_SENSOR_TABLE, &ulBattTblLen))
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: NV_GetLength (BATT) fail.");
        return VOS_ERR;
    }

    g_pusDrvAgentBatTempTable = (VOS_UINT16*)PS_MEM_ALLOC(WUEPS_PID_DRV_AGENT, ulBattTblLen);

    if (VOS_NULL_PTR == g_pusDrvAgentBatTempTable)
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: PS_MEM_ALLOC (BATT) fail.");
        return VOS_ERR;
    }

    if(NV_OK != NV_Read(en_NV_Item_BATT_TEMP_SENSOR_TABLE,
                        (VOS_VOID*)g_pusDrvAgentBatTempTable, ulBattTblLen))
    {
        MN_WARN_LOG("DRVAGENT_TempReadInit: NV_Read (BATT) fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
