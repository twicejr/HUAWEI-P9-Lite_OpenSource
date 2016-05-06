/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmSwitchOn.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : 1X SD开机状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXsdFsmSwitchOn.h"
#include  "CnasXsdFsmSwitchOnTbl.h"
#include  "CnasXsdProcNvim.h"
#include  "CnasXsdProcCard.h"
#include  "CnasXsdSndXcc.h"
#include  "CnasXsdSndXreg.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdMntn.h"
#include  "NasComm.h"
#include  "NasUsimmApi.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SWITCH_ON_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccStartReq_SwitchOn_Init
 功能描述  : SwitchOn状态机，初始化的状态，收到MSCC的开机消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年5月21日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvMsccStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_START_REQ_STRU                                *pstStartReq;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCsimCardStatus;

    VOS_UINT8                           ucIsReadNvPrlDirectly;
    MODEM_ID_ENUM_UINT16                enPreModemId;
    VOS_UINT8                           ucIsReadDefaultPrl;
    USIMM_DEF_FILEID_ENUM_UINT32        enHomeSidNidFileId;
    USIMM_DEF_FILEID_ENUM_UINT32        enEPrlFileId;

    ucIsReadDefaultPrl                  = VOS_FALSE;
    enHomeSidNidFileId                  = USIMM_CDMA_EFCDMAHOME_ID;
    enEPrlFileId                        = USIMM_CDMA_EFEPRL_ID;

    pstStartReq = (MSCC_XSD_START_REQ_STRU*)pstMsg;

    /* 保存入口消息 */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    enPreModemId = CNAS_CCB_GetCdmaModeModemId();

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    if ((MODEM_ID_0 != pstStartReq->enModemId)
     && (MODEM_ID_1 != pstStartReq->enModemId))
    {
        /* 开机时，如果设置的modemId不是modem0也不是modem1的话，直接返回失败 */
        NAS_TRACE_HIGH("CNAS_XSD_RcvMsccStartReq_SwitchOn_Init: MSCC Send XSD unexpected ModemId=%d\r\n!", pstStartReq->enModemId);

        /* 通知MMA开机结果 */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_XSD_QuitFsmL2();

        return VOS_TRUE;
    }

    CNAS_CCB_SetCdmaModeModemId(pstStartReq->enModemId);
#else

    CNAS_CCB_SetCdmaModeModemId(MODEM_ID_0);
#endif

    /* 读取NV配置项 */
    CNAS_XSD_ReadNvimInfo_SwitchOn();

    /* 存储卡状态 */
    CNAS_XSD_SaveCardStatus_SwitchOn(pstStartReq->enCardStatus);

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        enHomeSidNidFileId              = USIMM_CSIM_EFCDMAHOME_ID;
        enEPrlFileId                    = USIMM_CSIM_EFEPRL_ID;
    }

    /* 读取卡中的文件 */
    ucIsReadNvPrlDirectly            = CNAS_XSD_GetTestConfig()->ucReadNvPrlDirectly;

    ucIsReadDefaultPrl               = CNAS_XSD_GetTestConfig()->ucReadDefaultPrl;

    if ((VOS_FALSE                    == ucIsReadNvPrlDirectly)
     && (VOS_FALSE                    == ucIsReadDefaultPrl)
     && (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus))
    {
        if ((VOS_FALSE   == CNAS_PRL_GetPrlInfoValidFlag())
         || (VOS_TRUE    == pstStartReq->ucIsCardChanged))
        {
            /* 初始化PRL表重新读卡 */
            CNAS_PRL_InitPrlCtx(VOS_FALSE);

            /* 读取卡的PRL */
            /* 先读EPRL */
            CNAS_XSD_SndCardReadFileReq(enEPrlFileId);
            CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

            CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_EPRL_FLG);
            CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

            /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态 */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

            /* 启动保护定时器TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

            return VOS_TRUE;
        }
    }

    /* 测试需求*/
    if ((VOS_TRUE == ucIsReadNvPrlDirectly)
     || (VOS_TRUE == ucIsReadDefaultPrl))
    {
        CNAS_XSD_ProcTestConfig_SwitchOn_Init(ucIsReadNvPrlDirectly,
                                              ucIsReadDefaultPrl,
                                              enCsimCardStatus,
                                              enHomeSidNidFileId);

        return VOS_TRUE;
    }

    if ( (enPreModemId != CNAS_CCB_GetCdmaModeModemId())
      && (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus) )
    {
        /* 初始化PRL表重新读卡 */
        CNAS_PRL_InitPrlCtx(VOS_FALSE);

        /* 读取卡的PRL */
        /* 先读EPRL */
        CNAS_XSD_SndCardReadFileReq(enEPrlFileId);
        CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_EPRL_FLG);
        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

        /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* 启动保护定时器TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    if ((VOS_FALSE  == CNAS_PRL_GetPrlInfoValidFlag())
     || (VOS_TRUE   == pstStartReq->ucIsCardChanged))
    {
        /* 初始化PRL表重新读取Nv和DefaultPrl */
        CNAS_PRL_InitPrlCtx(VOS_FALSE);

        CNAS_XSD_ReadPrlNvim();

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            CNAS_XSD_ReadDefaultPrl();
        }

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* 通知MMA开机结果 */
            CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

            /* 开机完成，退出层二状态机*/
            CNAS_XSD_QuitFsmL2();

            return VOS_TRUE;
        }
    }
    else
    {
        CNAS_PRL_LogHeaderInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader));
        CNAS_PRL_LogAcqRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo));
        CNAS_PRL_LogSysRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo));
    }

    if (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus)
    {
        /* 读取卡中的Home Sid/Nid List */
        CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

        /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* 启动保护定时器TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    /* 通知XCC开机 */
    CNAS_XSD_SndXccStartReq();

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvGetCardFileCnf_SwitchOn_WaitUimFileCnf
 功能描述  : XSD在WAIT_CARD_FILE_CNF状态下，收到读取卡文件信息的回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数
 修改历史      :
  2.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : Usimm卡接口调整

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          ulEfId;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &ulEfId))
    {
        return VOS_FALSE;
    }

    /* 清除读取文件的等待标记 */
    CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf((VOS_UINT16)ulEfId);

    /* 处理卡文件读取确认 */
    CNAS_XSD_ProcCardReadFileCnf(pstMsg);

    /* 判断当前文件的读取是否已经完成，若没有读取完成，则直接return，状态不变 */
    if (CNAS_XSD_READ_CARD_FILE_FLG_NULL != CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    /* 完成所有读取请求后，停止XSD对应的状态保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF);

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* 读取NV中PRL并解析PRL */
        CNAS_XSD_ReadPrlNvim();
    }

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* 读取default PRL */
        CNAS_XSD_ReadDefaultPrl();
    }

    /* 如果default PRL解析失败，通知上层开机失败 */
    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* 通知MMA开机结果 */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_XSD_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 通知XCC开机 */
    CNAS_XSD_SndXccStartReq();

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf
 功能描述  : XSD在WAIT_CARD_FILE_CNF状态下，等待读取UIM卡文件超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年6月30日
   作    者   : z00316370
   修改内容   : 卡状态更改

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                    enCsimCardStatus;

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf:read Card file expired");

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    if (CNAS_XSD_READ_CARD_FILE_EPRL_FLG == (CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_XSD_READ_CARD_FILE_EPRL_FLG))
    {
        /* 清除等待读取EF-EPRL文件标志 */
        CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFEPRL_ID);

        /* 读取EF-PRL */

        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_XSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }

        /* 设置等待读取EF-PRL文件标志 */
        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_PRL_FLG);

        /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* 启动保护定时器TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    if (CNAS_XSD_READ_CARD_FILE_PRL_FLG == (CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_XSD_READ_CARD_FILE_PRL_FLG))
    {
        /* 清除等待读取EF-PRL文件标志 */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }
        /* 读取NV中PRL并解析PRL */
        CNAS_XSD_ReadPrlNvim();

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* 读取default PRL */
            CNAS_XSD_ReadDefaultPrl();
        }

        /* 如果default PRL解析失败，通知上层开机失败 */
        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* 通知MMA开机结果 */
            CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

            /* 开机完成，退出层二状态机*/
            CNAS_XSD_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SndXccStartReq();

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXccStartCnf_SwitchOn_WaitXccStartCnf
 功能描述  : XSD在WAIT_XCC_START_CNF 状态下,收到XCC的开机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXccStartCnf_SwitchOn_WaitXccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 停止XSD对应的状态保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF);

    /* 通知XREG开机 */
    CNAS_XSD_SndXregStartReq();

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XREG_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_START_CNF, TI_CNAS_XSD_WAIT_XREG_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf
 功能描述  : XSD在WAIT_XCC_START_CNF 状态下,等待XCC的开机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf:wait xcc start cnf expired");

    /* 通知XREG开机 */
    CNAS_XSD_SndXregStartReq();

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XREG_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_START_CNF, TI_CNAS_XSD_WAIT_XREG_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXregStartCnf_SwitchOn_WaitXregStartCnf
 功能描述  : XSD在WAIT_XREG_START_CNF 状态下,收到XREG的开机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数
 2.日    期   : 2015年4月15日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXregStartCnf_SwitchOn_WaitXregStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_START_REQ_STRU            *pstStartReq = VOS_NULL_PTR;

    /* 停止XSD对应的状态保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XREG_START_CNF);

    pstStartReq = (MSCC_XSD_START_REQ_STRU *)&(CNAS_XSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer[0]);

    /* 通知CAS开机 */
    CNAS_XSD_SndCasStartReq(pstStartReq);


    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_CAS_START_CNF */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_START_CNF, TI_CNAS_XSD_WAIT_CAS_START_CNF_LEN);
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf
 功能描述  : XSD在WAIT_XREG_START_CNF 状态下,等待XREG的开机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年4月15日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_START_REQ_STRU            *pstStartReq = VOS_NULL_PTR;

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf: wait xreg start cnf expired");

    pstStartReq = (MSCC_XSD_START_REQ_STRU *)&(CNAS_XSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer[0]);

    /* 通知CAS开机 */
    CNAS_XSD_SndCasStartReq(pstStartReq);

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_CAS_START_CNF */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_START_CNF, TI_CNAS_XSD_WAIT_CAS_START_CNF_LEN);
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf
 功能描述  : XSD在WAIT_CAS_START_CNF 状态下,收到CAS的开机确认回复消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :


 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_START_CNF_STRU         *pstStartCnf;

    pstStartCnf = (CAS_CNAS_1X_START_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("result=%d", pstStartCnf->enRslt);

    /* 停止XSD对应的状态保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_START_CNF);

    /* 通知MMA开机结果 */
    if (CNAS_CAS_1X_RSLT_FAILURE == pstStartCnf->enRslt)
    {
        /* 通知MMA开机失败 */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_XSD_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 通知MMA开机成功 */
    CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_SUCC);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_SUCCESS);

    /* 开机完成，退出层二状态机*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf
 功能描述  : XSD在WAIT_CAS_START_CNF 状态下,等待CAS的开机确认回复消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 通知MMA开机结果 */
    CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

    /* 开机完成，退出层二状态机*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ReadNvimInfo_SwitchOn
 功能描述  :  开机时读取NV设置值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 迭代7开发
  3.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17

*****************************************************************************/
VOS_VOID  CNAS_XSD_ReadNvimInfo_SwitchOn(VOS_VOID)
{
    /* 读取NV中的MRU信息 */
    CNAS_XSD_ReadMruNvim();

    /* read NVIM of Bandclass Information */
    CNAS_XSD_ReadBandClassNvim();

    /* 读取NV中的HOME SID NID信息 */
    CNAS_XSD_ReadHomeSidNidNvim();

    CNAS_XSD_ReadSearchIntervalNvim();

    CNAS_XSD_ReadChanRepeatScanScheduleConfigNvim();

    CNAS_XSD_ReadTestConfigNvim();

    CNAS_XSD_ReadAddAvoidListCfgNvim();

    CNAS_XSD_ReadNegPrefSysCmpCtrlNvim();

    CNAS_XSD_ReadHomeSidNidDependOnCfgNvim();

    CNAS_XSD_ReadOperLockSysWhiteListInfoNvim();

    CNAS_XSD_ReadCTCCCustomizeFreqNvim();

    CNAS_XSD_ReadCdmaStandardChannelsNvim();

    /* 读取CallBack模式配置 */
    CNAS_XSD_ReadCallBackCfgNvim();

    /* 读取CDMA 1X 优选频点信息 */
    CNAS_XSD_ReadCdma1XCustomPrefChannelsNvim();

    CNAS_XSD_Read1xSupportBandClassMaskNvim();

    CNAS_XSD_ReadNoCardModeCfgNvim();

    CNAS_XSD_ReadEmcRedialSysAcqCfgNvim();

    CNAS_XSD_Read1xAvoidScheduleInfoNvim();

    CNAS_XSD_Read1xPowerOffCampOnCtrlFlgNvim();

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ReadNvimInfo_SwitchOn
 功能描述  :  开机时读取NV设置值
 输入参数  : enFileId -- 文件ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XSD_SndCardReadFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileId)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    /* 读取EPRL，本次复用原来的接口，后续卡接口读取的时候，统一替换 */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      (VOS_UINT16)enFileId,
                                      0);

    ulRet = NAS_USIMMAPI_GetFileReq(UEPS_PID_XSD, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* 打印卡文件读取失败 */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_SndCardReadFileReq: Read card file failure");
        return;
    }

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveCardStatus_SwitchOn
 功能描述  : 将MMA下发的卡状态信息转换成CCB使用的形式
             保存到全局变量中.
 输入参数  : ucCardStatus卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月15日
   作    者   : h00246512
   修改内容   : 新生成函数
 2.日    期   : 2015年6月30日
   作    者   : z00316370
   修改内容   : 卡状态更改

*****************************************************************************/
VOS_VOID  CNAS_XSD_SaveCardStatus_SwitchOn(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enCardStatus
)
{
    if (NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT == enCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_UIM_PRESENT);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == enCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_CSIM_PRESENT);
    }
    else
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_ABSENT);
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveCardStatus_SwitchOn
 功能描述  : 将MMA下发的卡状态信息转换成CCB使用的形式
             保存到全局变量中.
 输入参数  : ucCardStatus卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月15日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
)
{
    switch ( usEfId )
    {
        case USIMM_CDMA_EFEPRL_ID: /* EF_CUIM_EPRL */
        case USIMM_CSIM_EFEPRL_ID:
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_EPRL_FLG);
            break;

        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_PRL_FLG);
            break;

        case USIMM_CDMA_EFCDMAHOME_ID: /* EF_CUIM_HOME */
        case USIMM_CSIM_EFCDMAHOME_ID:
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "NAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ReadDefaultPrl
 功能描述  : 获取default PRL并解析

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月11日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadDefaultPrl(VOS_VOID)
{
    VOS_UINT8                          *pucPrlBuf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    /* 解析default PRL */
    pucPrlBuf = CNAS_PRL_GetDefaultPrl();

    ulRslt = CNAS_PRL_ProcPrlInfo(pucPrlBuf, CNAS_PRL_GetDefaultPrlSize(), CNAS_PRL_SSPR_P_REV_3);

    if (VOS_TRUE == ulRslt)
    {
        CNAS_XSD_LogPrlSourceType(CNAS_XSD_PRL_TYPE_HARD_CODE);
    }

#if 0
    /* 用当前default PRL写入到NVRM中 */
    if (CNAS_PRL_GetDefaultPrlSize() <= NV_PREFERRED_ROAMING_LIST_SIZE)
    {
        if (NV_OK != NV_Write(en_NV_Item_PRL_LIST, pucPrlBuf, NV_PREFERRED_ROAMING_LIST_SIZE))
        {
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadPrlNvim:Write Nvim Failed!");
        }
    }
#endif

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcTestConfig_SwitchOn_Init
 功能描述  : 开机处理测试控制项
 输入参数  : VOS_UINT8                           ucIsReadNvPrlDirectly
             VOS_UINT8                           ucIsReadDefaultPrl
             CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus
             USIMM_DEF_FILEID_ENUM_UINT32        enHomeSidNidFileId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月31日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcTestConfig_SwitchOn_Init(
    VOS_UINT8                           ucIsReadNvPrlDirectly,
    VOS_UINT8                           ucIsReadDefaultPrl,
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus,
    USIMM_DEF_FILEID_ENUM_UINT32        enHomeSidNidFileId
)
{
    /* 不支持既要读NV中的，又要读缺省的 */
    if ((VOS_TRUE == ucIsReadNvPrlDirectly)
     && (VOS_TRUE == ucIsReadDefaultPrl))
    {
        /* 通知MMA开机结果 */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_XSD_QuitFsmL2();

        return;
    }

    /* 初始化PRL表 */
    CNAS_PRL_InitPrlCtx(VOS_FALSE);

    /* 读NV中的PRL */
    if (VOS_TRUE == ucIsReadNvPrlDirectly)
    {
        CNAS_XSD_ReadPrlNvim();
    }

    /* 读默认的PRL */
    if (VOS_TRUE == ucIsReadDefaultPrl)
    {
        CNAS_XSD_ReadDefaultPrl();
    }

    /* 读PRL失败 */
    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* 通知MMA开机结果 */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* 开机完成，退出层二状态机*/
        CNAS_XSD_QuitFsmL2();

        return;
    }

    /* 有卡且NV项不使能时，才从卡中读Home sid和nid */
    if ((VOS_FALSE == ucIsReadNvPrlDirectly)
     && (CNAS_CCB_CARD_STATUS_ABSENT != enCsimCardStatus))
    {
        /* 读取卡中的Home Sid/Nid List */
        CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

        /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF状态 */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* 启动保护定时器TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return;
    }

    /* 通知XCC开机 */
    CNAS_XSD_SndXccStartReq();

    /* 迁移到 CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF状态,并启动保护定时器TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



