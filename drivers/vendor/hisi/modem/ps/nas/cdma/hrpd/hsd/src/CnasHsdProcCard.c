/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdProcCard.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月12日
  功能描述   : HSD处理卡的读取
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasHsdProcCard.h"
#include  "CnasHsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasHsdFsmSwitchOn.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_PROC_CARD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcCardReadFileCnf
 功能描述  : 从卡中读取卡中各个文件的处理
 输入参数  : pstMsg:struct MsgCB
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
   修改内容   : 新生成函数

  2.日    期   : 2015年3月7日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCardReadFileCnf(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU          *pstFile;
    USIMM_DEF_FILEID_ENUM_UINT32      enEfId;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return;
    }

    switch (enEfId)
    {
        case USIMM_CDMA_EFEPRL_ID:
        case USIMM_CSIM_EFEPRL_ID:
            CNAS_HSD_ProcCardReadFileCnf_EF_EPRL(pstMsg);
            break;

        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_HSD_ProcCardReadFileCnf_EF_PRL(pstMsg);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvCardReadFileCnf:WARNING: File Id Abnormal");
            break;

    }

    return;
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcCardReadFileCnf_EF_EPRL
 功能描述  : 从卡中读取EFEPRL的处理
 输入参数  : pstMsg:struct MsgCB
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年3月7日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCardReadFileCnf_EF_EPRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* 判断文件的读取结果 */
    if (VOS_OK != pstFile->stCmdResult.ulResult)
    {
        CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_RcvCardReadFileCnf_EF_EPRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);
    }
    else
    {
        CNAS_PRL_SetPrlRevInfo(CNAS_PRL_SSPR_P_REV_3);
        ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_3);

        if (VOS_TRUE == ulRslt)
        {
            CNAS_HSD_LogPrlSourceType(CNAS_HSD_PRL_TYPE_EPRL_FILE);
            return;
        }

        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvCardReadFileCnf_EF_EPRL: EPRL Parse Fail!");
    }

    /* EF-EPRL读取失败，读取EF-PRL文件 */
    if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == CNAS_CCB_GetCsimCardStatus())
    {
        CNAS_HSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
    }
    else
    {
        CNAS_HSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
    }

    CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_PRL_FLG);

    /* 启动保护定时器TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN */
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF, TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcCardReadFileCnf_EF_PRL
 功能描述  : 从卡中读取EF-PRL的处理
 输入参数  : pstMsg:struct MsgCB
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月18日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCardReadFileCnf_EF_PRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* 文件的读取失败，返回 */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_ProcCardReadFileCnf_EF_PRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);

        return;
    }

    ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_1);

    if (VOS_TRUE != ulRslt)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ProcCardReadFileCnf_EF_PRL: PRL Parse Fail!");
    }
    else
    {
        CNAS_HSD_LogPrlSourceType(CNAS_HSD_PRL_TYPE_PRL_FILE);
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





