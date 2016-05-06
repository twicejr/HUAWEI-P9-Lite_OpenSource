/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmSwitchOn.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月09日
  功能描述   : HRPD 开机状态机事件处理函数
  函数列表   :
  修改历史   :
 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasHsdFsmSwitchOn.h"
#include  "CnasHsdFsmSwitchOnTbl.h"
#include  "CnasHsdProcNvim.h"
#include  "CnasHsdProcCard.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasHsdCtx.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "NasComm.h"
#include  "NasUsimmApi.h"
#include  "CnasHsdFsmSwitchOn.h"
#include  "CnasHsdSndHlu.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include  "CnasHsdSndHsm.h"
#include  "CnasHsdSndEhsm.h"
#include  "NVIM_Interface.h"
#include  "CnasPrlMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_SWITCH_ON_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccStartReq_SwitchOn_Init
 功能描述  : SwitchOn状态机，初始化的状态，收到MMA的开机消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年06月08日
    作    者   : z00316370
    修改内容   : 卡状态获取接口变更
  3.日    期   : 2015年06月18日
    作    者   : z00316370
    修改内容   : 先给HSM开机

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvMsccStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_START_REQ_STRU            *pstStartReq;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enModeType;
    VOS_UINT32                          ul1xSupportFlag;
    VOS_UINT8                           ucIsReadNvPrlDirectly;
    VOS_UINT8                           ucIsReadDefaultPrl;

    pstStartReq = (MSCC_HSD_START_REQ_STRU *)pstMsg;

    /* 保存入口消息 */
    CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    if ((MODEM_ID_0 != pstStartReq->enModemId)
     && (MODEM_ID_1 != pstStartReq->enModemId))
    {
        /* 开机时，如果设置的modemId不是modem0也不是modem1的话，直接返回失败 */
        NAS_TRACE_HIGH("CNAS_HSD_RcvMsccStartReq_SwitchOn_Init: MSCC Send HSD unexpected ModemId=%d\r\n!", pstStartReq->enModemId);

        /* 通知MMA开机结果 */
        CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_FAIL);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_HSD_QuitFsmL2();

        return VOS_TRUE;
    }

    CNAS_CCB_SetCdmaModeModemId(pstStartReq->enModemId);

    /* 根据9203NV判断平台能力十分支持1X */
    ul1xSupportFlag = CNAS_HSD_Is1xSupport(pstStartReq->enModemId);

#else
    CNAS_CCB_SetCdmaModeModemId(MODEM_ID_0);

    /* 根据9203NV判断平台能力十分支持1X */
    ul1xSupportFlag = CNAS_HSD_Is1xSupport(MODEM_ID_0);
#endif



    /* 存储卡状态 */
    CNAS_HSD_SaveCardStatus_SwitchOn(pstStartReq->enCsimStatus,
                                     pstStartReq->enUsimStatus);

    /* 根据MSCC的开机请求判断是混合模式还是混合模式 */
    enModeType = CNAS_HSD_CheckHybridMode(pstStartReq->ucSuppRatNum, &pstStartReq->aenRatMode[0]);

    /* 设置当前搜网模式 */
    CNAS_HSD_SetSysModeType(enModeType);

    /* 读取NV配置项 */
    CNAS_HSD_ReadNvimInfo_SwitchOn(ul1xSupportFlag);

    if (VOS_FALSE == ul1xSupportFlag)
    {
        /* 读取卡中的文件，仅当有卡并且1X不支持时才需要读取 */
        enCsimCardStatus                 = CNAS_CCB_GetCsimCardStatus();
        ucIsReadNvPrlDirectly            = CNAS_HSD_GetTestConfig()->ucReadNvPrlDirectly;
        ucIsReadDefaultPrl               = CNAS_HSD_GetTestConfig()->ucReadDefaultPrl;

        if ((VOS_FALSE                    == ucIsReadNvPrlDirectly)
         && (VOS_FALSE                    == ucIsReadDefaultPrl)
         && (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus))
        {
            if ((VOS_FALSE  == CNAS_PRL_GetPrlInfoValidFlag())
             || (VOS_TRUE   == pstStartReq->ucIsCardChanged))
            {
                /* 初始化PRL表重新读卡 */
                CNAS_PRL_InitPrlCtx(VOS_FALSE);

                /* 先读EPRL */
                if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
                {
                    CNAS_HSD_SndCardReadFileReq(USIMM_CSIM_EFEPRL_ID);
                }
                else
                {
                    CNAS_HSD_SndCardReadFileReq(USIMM_CDMA_EFEPRL_ID);
                }

                CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_EPRL_FLG);

                /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);
                CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF, TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN);

                return VOS_TRUE;
            }
        }

        if ((VOS_FALSE  == CNAS_PRL_GetPrlInfoValidFlag())
         || (VOS_TRUE   == pstStartReq->ucIsCardChanged))
        {
            /* 初始化PRL表重新读取Nv和DefaultPrl */
            CNAS_PRL_InitPrlCtx(VOS_FALSE);

            if (VOS_FALSE == ucIsReadDefaultPrl)
            {
                CNAS_HSD_ReadPrlNvim();
            }

            if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
            {
                CNAS_HSD_ReadDefaultPrl();
            }

            if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
            {
                /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
                CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

                /* 开机完成，退出层二状态机*/
                CNAS_HSD_QuitFsmL2();

                return VOS_TRUE;
            }
        }
        else
        {
            CNAS_PRL_LogHeaderInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader));
            CNAS_PRL_LogAcqRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo));
            CNAS_PRL_LogSysRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo));
        }
    }

    /* 处理中国电信定制事件 */
    CNAS_HSD_ProcessCTCCCustomize();

    /* 通知HSM开机 */
    CNAS_HSD_SndHsmStartReq();

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_XCC_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF, TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvGetCardFileCnf_SwitchOn_WaitUimFileCnf
 功能描述  : HSD在WAIT_CARD_FILE_CNF状态下，收到读取卡文件信息的回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年3月7日
    作    者   : y00245242
    修改内容   : 新生成函数
  3.日    期   : 2015年06月18日
    作    者   : z00316370
    修改内容   : 给HSM开机
  4.日    期   : 2015年08月18日
    作    者   : x00306642
    修改内容   : 增加读PRL文件失败的流程

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          enEfId;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return VOS_TRUE;
    }

    /* 清除读取文件的等待标记 */
    CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf((VOS_UINT16)enEfId);

    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF);

    /* 处理卡文件读取确认 */
    CNAS_HSD_ProcCardReadFileCnf(pstMsg);

    /* 判断当前文件的读取是否已经完成，若没有读取完成，则直接return，状态不变 */
    if (CNAS_HSD_READ_CARD_FILE_FLG_NULL != CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* 读取NV中PRL并解析PRL */
        CNAS_HSD_ReadPrlNvim();
    }

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* 读取default PRL */
        CNAS_HSD_ReadDefaultPrl();
    }

    /* 如果default PRL解析失败，通知上层开机失败 */
    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_HSD_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 处理中国电信定制事件 */
    CNAS_HSD_ProcessCTCCCustomize();

    /* 通知HSM开机 */
    CNAS_HSD_SndHsmStartReq();

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_XCC_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF, TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf
 功能描述  : HSD在WAIT_CARD_FILE_CNF状态下，等待读取UIM卡文件超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年06月18日
    作    者   : z00316370
    修改内容   : 给HSM开机

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf:read Card file expired");

    if (CNAS_HSD_READ_CARD_FILE_EPRL_FLG == (CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_HSD_READ_CARD_FILE_EPRL_FLG))
    {
        /* 清除等待读取EF-EPRL文件标志 */
        CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFEPRL_ID);

        /* 读取EF-PRL */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == CNAS_CCB_GetCsimCardStatus())
        {
            CNAS_HSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_HSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }

        /* 设置等待读取EF-PRL文件标志 */
        CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_PRL_FLG);

        /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态 */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* 启动保护定时器TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF, TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    if (CNAS_HSD_READ_CARD_FILE_PRL_FLG == (CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_HSD_READ_CARD_FILE_PRL_FLG))
    {
        /* 清除等待读取EF-PRL文件标志 */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == CNAS_CCB_GetCsimCardStatus())
        {
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }

        /* 读取NV中PRL并解析PRL */
        CNAS_HSD_ReadPrlNvim();

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* 读取default PRL */
            CNAS_HSD_ReadDefaultPrl();
        }

        /* 如果default PRL解析失败，通知上层开机失败 */
        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

            /* 开机完成，退出层二状态机*/
            CNAS_HSD_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    /* 处理中国电信定制事件 */
    CNAS_HSD_ProcessCTCCCustomize();

    /* 通知HSM开机 */
    CNAS_HSD_SndHsmStartReq();

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_XCC_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF, TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHsmStartCnf_SwitchOn_WaitHsmStartCnf
 功能描述  : HSD在WAIT_HSM_START_CNF 状态下,收到HSM的开机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  1.日    期   : 2015年06月18日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvHsmStartCnf_SwitchOn_WaitHsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF);

    /* 通知EHSM开机 */
    CNAS_HSD_SndEhsmStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_EHSM_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_EHSM_START_CNF, TI_CNAS_HSD_WAIT_EHSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf
 功能描述  : HSD在WAIT_HSM_START_CNF 状态下,等待HSM的开机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年06月15日
    作    者   : z00316370
    修改内容   : 给EHSM发送开机请求

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf:wait hsm start cnf expired");

    /* 通知EHSM开机 */
    CNAS_HSD_SndEhsmStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_EHSM_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_EHSM_START_CNF, TI_CNAS_HSD_WAIT_EHSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHluStartCnf_SwitchOn_WaitHluStartCnf
 功能描述  : HSD在WAIT_HLU_START_CNF 状态下,收到HLU的开机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年06月18日
    作    者   : z00316370
    修改内容   : 给CAS开机
*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvHluStartCnf_SwitchOn_WaitHluStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_HLU_START_CNF);

    /* 通知CAS开机 */
    CNAS_HSD_SndCasStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_CAS_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_START_CNF, TI_CNAS_HSD_WAIT_CAS_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf
 功能描述  : HSD在WAIT_HLU_START_CNF 状态下,等待HLU的开机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h300778
    修改内容   : 新生成函数
  2.日    期   : 2015年06月18日
    作    者   : z00316370
    修改内容   : 给CAS开机

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiHluStartCnfExpired_SwitchOn_WaitHluStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiHluStartCnfExpired_SwitchOn_WaitHluStartCnf: wait hlu start cnf expired");

    /* 通知CAS开机 */
    CNAS_HSD_SndCasStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_CAS_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_START_CNF, TI_CNAS_HSD_WAIT_CAS_START_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf
 功能描述  : HSD在WAIT_CAS_START_CNF 状态下,收到CAS的开机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年06月18日
    作    者   : z00316370
    修改内容   : 上报开机结果，退状态机
*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_START_CNF_STRU       *pstStartCnf;

    pstStartCnf = (CAS_CNAS_HRPD_START_CNF_STRU *)pstMsg;

    NAS_TRACE_HIGH("result=%d", pstStartCnf->enStartRslt);

    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_START_CNF);

    /* 通知MMA开机结果 */
    if (VOS_OK != pstStartCnf->enStartRslt)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);
    }
    else
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_SUCCESS);
    }

    /* 开机完成，退出层二状态机*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf
 功能描述  : HSD在WAIT_CAS_START_CNF 状态下,等待CAS的开机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

    /* 开机完成，退出层二状态机*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadNvimInfo_SwitchOn
 功能描述  :  开机时读取NV设置值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_HSD_ReadNvimInfo_SwitchOn(VOS_UINT32 ul1xSupportFlag)
{
    /* 读取NV中的MRU信息 */
    CNAS_HSD_ReadMruNvim();

    /* 读取NV中的存储的搜索时间间隔信息 */
    CNAS_HSD_ReadSearchIntervalNvim();

    CNAS_HSD_ReadHrpdSupportBandClassMaskNvim();

    if (VOS_FALSE == ul1xSupportFlag)
    {
        CNAS_HSD_ReadOperLockSysWhiteListInfoNvim();

        CNAS_HSD_ReadCTCCCustomizeFreqNvim();
    }

    CNAS_HSD_ReadTestConfigNvim();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCardReadFileReq
 功能描述  :  开机时读取卡文件的处理
 输入参数  : enFileId -- 文件ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数

  2.日    期   : 2015年3月7日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_HSD_SndCardReadFileReq(USIMM_CUIM_FILEID_ENUM_UINT16 enFileId)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;


    /* 当前只是走一下读卡流程，并不处理卡信息，后续搜网开发的时候，再进一步完善 */

    /* 读取EPRL，本次复用原来的接口，后续卡接口读取的时候，统一替换 */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      enFileId,
                                      0);

    ulRet = NAS_USIMMAPI_GetFileReq(UEPS_PID_HSD, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* 打印卡文件读取失败 */
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndCardReadFileReq: Read card file failure");
        return;
    }

    CNAS_MNTN_LogUsimmApiGetFileReq(UEPS_PID_HSD, ulRet, (CNAS_MNTN_LOG_GETFILE_INFO_STRU *)&stGetFileInfo);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SaveCardStatus_SwitchOn
 功能描述  : 将MMA下发的卡状态信息转换成CCB使用的形式
             保存到全局变量中.
 输入参数  : ucCardStatus卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年06月04日
    作    者   : z00316370
    修改内容   : 增加存储USIM状态

*****************************************************************************/
VOS_VOID  CNAS_HSD_SaveCardStatus_SwitchOn(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enCsimCardStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enUsimCardStatus
)
{
    /* 设置CSIM卡状态 */
    if (NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT == enCsimCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_UIM_PRESENT);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_CSIM_PRESENT);
    }
    else
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_ABSENT);
    }

    /* 设置USIM卡状态 */
    if (NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT == enUsimCardStatus)
    {
        CNAS_CCB_SetUsimCardStatus(CNAS_CCB_CARD_STATUS_SIM_PRESENT);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT == enUsimCardStatus)
    {
        CNAS_CCB_SetUsimCardStatus(CNAS_CCB_CARD_STATUS_USIM_PRESENT);
    }
    else
    {
        CNAS_CCB_SetUsimCardStatus(CNAS_CCB_CARD_STATUS_ABSENT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SaveCardStatus_SwitchOn
 功能描述  : 将MMA下发的卡状态信息转换成CCB使用的形式
             保存到全局变量中.
 输入参数  : usEfId:文件ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
)
{
    switch ( usEfId )
    {
        case USIMM_CDMA_EFEPRL_ID:
        case USIMM_CSIM_EFEPRL_ID:
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_EPRL_FLG);
            break;

        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_PRL_FLG);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSD, "NAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvEhsmStartCnf_SwitchOn_WaitEhsmStartCnf
 功能描述  : HSD在WAIT_HSM_START_CNF 状态下,收到HSM的开机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2015年06月05日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvEhsmStartCnf_SwitchOn_WaitEhsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止HSD对应的状态保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_EHSM_START_CNF);

    /* 通知HLU开机 */
    CNAS_HSD_SndHluStartReq();

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_HLU_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HLU_START_CNF, TI_CNAS_HSD_WAIT_HLU_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf
 功能描述  : HSD在WAIT_EHSM_START_CNF 状态下,等待EHSM的开机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月05日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf:wait ehsm start cnf expired");

    /* 通知HLU开机 */
    CNAS_HSD_SndHluStartReq();

    /* 迁移到 CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF状态,并启动保护定时器TI_CNAS_HSD_WAIT_HLU_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HLU_START_CNF, TI_CNAS_HSD_WAIT_HLU_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadDefaultPrl
 功能描述  : 获取default PRL并解析

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月18日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadDefaultPrl(VOS_VOID)
{
    VOS_UINT8                          *pucPrlBuf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    /* 解析default PRL */
    pucPrlBuf = CNAS_PRL_GetDefaultPrl();

    ulRslt = CNAS_PRL_ProcPrlInfo(pucPrlBuf, CNAS_PRL_GetDefaultPrlSize(), CNAS_PRL_SSPR_P_REV_3);

    if (VOS_TRUE == ulRslt)
    {
        CNAS_HSD_LogPrlSourceType(CNAS_HSD_PRL_TYPE_HARD_CODE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_Is1xSupport
 功能描述  : 判断plat是否支持1X
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_Is1xSupport(MODEM_ID_ENUM_UINT16                enModemId)
{
    PLATAFORM_RAT_CAPABILITY_STRU       stModem0PlatRat;
    VOS_UINT16                          i;

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_Platform_RAT_CAP, &stModem0PlatRat,
                           sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Is1xSupport read NV en_NV_Item_Platform_RAT_CAP failed!\r\n");
        return VOS_FALSE;
    }

    for (i = 0; i < stModem0PlatRat.usRatNum; i++)
    {
        if (PLATFORM_RAT_1X == stModem0PlatRat.aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



