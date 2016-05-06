/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregFsmSwitchOn.c
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2015年01月05日
  功能描述   : 1X XREG开机状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasXregFsmSwitchOn.h"
#include  "CnasXregFsmSwitchOnTbl.h"
#include  "CnasMntn.h"
#include  "CnasXregCtx.h"
#include  "NasComm.h"
#include  "NasUsimmApi.h"
#include  "CnasXregProcess.h"
#include  "CnasXregTimer.h"
#include  "CnasXregSndInternalMsg.h"
#include  "CnasTimerMgmt.h"
#include  "CnasMntn.h"
#include  "siapppih.h"
#include  "NVIM_Interface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_SWITCH_ON_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
extern VOS_UINT32 I1_PIH_RegCardRefreshIndMsg(VOS_UINT32 ulRegPID);
extern VOS_UINT32 I1_PIH_DeregCardRefreshIndMsg(VOS_UINT32 ulRegPID);
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvXsdStartReq_SwitchOn_Init
 功能描述  : SwitchOn状态机，初始化的状态，收到Xsd的开机消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvXsdStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus;
    MODEM_ID_ENUM_UINT16                enCdmaModeModemId;

    /* 保存入口消息 */
    CNAS_XREG_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 读取NV配置项 */
    CNAS_XREG_ReadNvimInfo_SwitchOn();

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    /* 读取卡中的文件 */
    if (CNAS_CCB_CARD_STATUS_ABSENT != enCsimCardStatus)
    {
        /* 读EFterm文件 */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CSIM_EFTERM_ID);
        }
        else
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CDMA_EFTERM_ID);
        }

        CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_TERM_FLG);

        /* 读EFssci文件 */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CSIM_EFSSCI_ID);
        }
        else
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CDMA_EFSSCI_ID);
        }

        CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_SSCI_FLG);

        /* 迁移到 CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态 */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* 启动保护定时器TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT */
        CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT, TI_CNAS_XREG_TIMER_CARDFILE_CNF_LEN);
    }
    else
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XREG_SndSwitchOnRlst(CNAS_XREG_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_XREG_QuitFsmL2();
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 获取Cdma所处的modem ID */
    enCdmaModeModemId = CNAS_CCB_GetCdmaModeModemId();

    /* 去注册对应模PID */
    if (MODEM_ID_1 == enCdmaModeModemId)
    {
        /* 注册当前PID */
        I1_PIH_RegCardRefreshIndMsg(UEPS_PID_XREG);

        PIH_DeregCardRefreshIndMsg(UEPS_PID_XREG);
    }
    else
    {
        I1_PIH_DeregCardRefreshIndMsg(UEPS_PID_XREG);

        /* 注册当前PID */
        PIH_RegCardRefreshIndMsg(UEPS_PID_XREG);
    }
#else
    /* 注册当前PID */
    PIH_RegCardRefreshIndMsg(UEPS_PID_XREG);

#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf
 功能描述  : XREG在WAIT_CARD_FILE_CNF状态下，收到读取卡文件信息的回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数
  2.日    期   : 2015年3月7日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId;


    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return VOS_TRUE;
    }

    /* 停止XREG对应的状态保护定时器 */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT, 0);

    /* 清除读取文件的等待标记 */
    CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf((VOS_UINT16)enEfId);

    /* 处理卡文件读取确认 */
    CNAS_XREG_ProcCardReadFileCnf(pstMsg);

    /* 判断当前文件的读取是否已经完成，若没有读取完成，则直接return，状态不变 */
    if (CNAS_XREG_READ_CARD_FILE_FLG_NULL != CNAS_XREG_GetWaitCardFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XREG_SndSwitchOnRlst(CNAS_XREG_SWITCH_ON_RESULT_SUCCESS);

    /* 开机完成，退出层二状态机*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf
 功能描述  : XREG在WAIT_CARD_FILE_CNF状态下，等待读取UIM卡文件超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf:read Card file expired");

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XREG_SndSwitchOnRlst(CNAS_XREG_SWITCH_ON_RESULT_FAILURE);

    /* 开机完成，退出层二状态机*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndCardReadFileReq
 功能描述  : 开机时读取NV设置值
 输入参数  : enFileId -- 文件ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数
  2.日    期   : 2015年3月7日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  CNAS_XREG_SndCardReadFileReq(USIMM_CUIM_FILEID_ENUM_UINT16 enFileId)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    /* 读取EPRL，本次复用原来的接口，后续卡接口读取的时候，统一替换 */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      enFileId,
                                      0);

    ulRet = NAS_USIMMAPI_GetFileReq(UEPS_PID_XREG, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* 打印卡文件读取失败 */
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_SndCardReadFileReq: Read card file failure");

        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf
 功能描述  : 将MMA下发的卡状态信息转换成CCB使用的形式
             保存到全局变量中.
 输入参数  : ucCardStatus卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月05日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
)
{
    switch ( usEfId )
    {
        case USIMM_CDMA_EFTERM_ID:
        case USIMM_CSIM_EFTERM_ID:
            CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_TERM_FLG);
            break;

        case USIMM_CSIM_EFSSCI_ID:
        case USIMM_CDMA_EFSSCI_ID:
            CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_SSCI_FLG);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_ReadNvimInfo_SwitchOn
 功能描述  : 开机状态下读取NV项内容.
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月05日
   作    者   : g00256031
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_ReadNvimInfo_SwitchOn(VOS_VOID)
{
    CNAS_NVIM_1X_LAST_SCI_STRU          stLastSci;
    CNAS_NVIM_NO_CARD_MODE_CFG_STRU     stNoCardModeCfg;

    CNAS_XREG_SetLastSciValue(CNAS_XREG_SCI_DEF_VALUE);

    if (NV_OK == NV_Read(en_NV_Item_1X_LAST_SCI, &stLastSci, sizeof(stLastSci)))
    {
        /* 参数判断 */
        if (CNAS_XREG_SCI_MAX_VALUE >= stLastSci.ulSicValue)
        {
            CNAS_XREG_SetLastSciValue((VOS_UINT8)stLastSci.ulSicValue);
        }
        CNAS_MNTN_LogReadNVInfo(en_NV_Item_1X_LAST_SCI,
                                sizeof(stLastSci),
                                UEPS_PID_XREG,
                                (VOS_UINT8 *)&stLastSci);
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_ReadNvimInfo_SwitchOn:NV_Read Failed");
    }


    if (NV_OK == NV_Read(en_NV_Item_NO_CARD_MODE_CFG, &stNoCardModeCfg, sizeof(stNoCardModeCfg)))
    {
        /* 参数判断 */
        if (VOS_FALSE != stNoCardModeCfg.ulEnableFlag)
        {
            CNAS_XREG_EnableNoCardMode();
        }
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_ReadNvimInfo_SwitchOn:NV_Read Failed");
    }



    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

