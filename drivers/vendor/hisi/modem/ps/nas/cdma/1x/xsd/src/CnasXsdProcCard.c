/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdProcCard.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年07月08日
  功能描述   : XSD处理卡的读取
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月08日
    作    者   : h00246512
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXsdProcCard.h"
#include  "CnasXsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdFsmSwitchOn.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_PROC_CARD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCardReadFileCnf
 功能描述  : 从卡中读取卡中各个文件的处理
 输入参数  : pstMsg:struct MsgCB
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月8日
   作    者   : h00246512
   修改内容   : 新生成函数
 1.日    期   : 2015年02月05日
   作    者   : h00313353
   修改内容   : Usimm卡接口调整
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          ulEfId;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;
    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &ulEfId))
    {
        return;
    }

    switch (ulEfId)
    {
        case USIMM_CSIM_EFEPRL_ID: /* EF_CUIM_EPRL */
        case USIMM_CDMA_EFEPRL_ID:
            CNAS_XSD_ProcCardReadFileCnf_EF_EPRL(pstMsg);
            break;
        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_XSD_ProcCardReadFileCnf_EF_PRL(pstMsg);
            break;

        case USIMM_CDMA_EFCDMAHOME_ID: /* EF_CUIM_HOME */
        case USIMM_CSIM_EFCDMAHOME_ID:
            CNAS_XSD_ProcCardReadFileCnf_EF_HOME(pstMsg);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCardReadFileCnf:WARNING: File Id Abnormal");
            break;

    }

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCardReadFileCnf_EF_EPRL
 功能描述  : 从卡中读取EFEPRL的处理
 输入参数  : pstMsg:struct MsgCB
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月8日
   作    者   : h00246512
   修改内容   : 新生成函数
 2.日    期   : 2015年02月05日
   作    者   : h00313353
   修改内容   : Usimm卡接口调整
 3.日    期   : 2015年06月30日
   作    者   : z00316370
   修改内容   : Usimm卡状态调整
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf_EF_EPRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU                                *pstFile = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCsimCardStatus;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    /* 判断文件的读取结果 */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_RcvCardReadFileCnf_EF_EPRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);
    }
    else
    {
        /* 使用EPRL格式，解析EPRL */
        CNAS_PRL_SetPrlRevInfo(CNAS_PRL_SSPR_P_REV_3);
        ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_3);

        if (VOS_TRUE == ulRslt)
        {
            CNAS_XSD_LogPrlSourceType(CNAS_XSD_PRL_TYPE_EPRL_FILE);
            return;
        }

        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCardReadFileCnf_EF_EPRL: EPRL Parse Fail!");
    }

    /* EF-EPRL读取失败，读取EF-PRL文件 */
    if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        CNAS_XSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
    }
    else
    {
        CNAS_XSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
    }

    CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_PRL_FLG);

    /* 启动保护定时器TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCardReadFileCnf_EF_PRL
 功能描述  : 从卡中读取EF-PRL的处理
 输入参数  : pstMsg:struct MsgCB
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月11日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年02月05日
   作    者   : h00313353
   修改内容   : Usimm卡接口调整
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf_EF_PRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* 文件的读取失败，返回 */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_ProcCardReadFileCnf_EF_PRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);

        return;
    }

    ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_1);

    if (VOS_TRUE != ulRslt)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ProcCardReadFileCnf_EF_PRL: PRL Parse Fail!");
    }
    else
    {
        CNAS_XSD_LogPrlSourceType(CNAS_XSD_PRL_TYPE_PRL_FILE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCardReadFileCnf_EF_HOME
 功能描述  : 从卡中读取EF-HOME(HOME SID NID LIST)的处理
 输入参数  : pstMsg:struct MsgCB
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月5日
   作    者   : h00246512
   修改内容   : 新生成函数
 2.日    期   : 2015年02月05日
   作    者   : h00313353
   修改内容   : Usimm卡接口调整
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf_EF_HOME(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile             = VOS_NULL_PTR;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList   = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmpdata          = VOS_NULL_PTR;
    VOS_UINT8                           ucRecNum;
    VOS_UINT32                          i;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* 文件的读取失败，返回 */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_ProcCardReadFileCnf_EF_HOME:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);

        return;
    }

    pucTmpdata = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XSD, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN);

    if (VOS_NULL_PTR == pucTmpdata)
    {
        return;
    }

    NAS_MEM_SET_S(pucTmpdata, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN, 0x00, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN);
    NAS_MEM_CPY_S(pucTmpdata, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN, pstFile->aucEf, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN);

    pstHomeSidNidList = CNAS_CCB_GetHomeSidNidList();
    ucRecNum    = (VOS_UINT8)pstFile->ucTotalNum;

    /* 如果长度超过定义的最大个数，则只取最大个数 */
    if (ucRecNum > CNAS_CCB_MAX_HOME_SID_NID_LIST)
    {
         ucRecNum = CNAS_CCB_MAX_HOME_SID_NID_LIST;
    }

    i = 0;
    while (i < ucRecNum)
    {
        /*
          Bytes  Description                M/O     Length
          1 ~ 2  CDMA Home SID (SIDp)       M       2 bytes
          3 ~ 4  CDMA Home NID (NIDp)       M       2 bytes
          5      Band Class                 M       1 byte
          */
        pstHomeSidNidList->astHomeSidNid[i].usSid   = (VOS_UINT16)(pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN] | ((pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_1_OFFSET] & 0x7F) << CNAS_XSD_BIT_LEN_8_BIT));
        pstHomeSidNidList->astHomeSidNid[i].usNid   = (VOS_UINT16)(pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_2_OFFSET] | (pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_3_OFFSET] << CNAS_XSD_BIT_LEN_8_BIT));
        pstHomeSidNidList->astHomeSidNid[i].usBand  = (VOS_UINT16)(pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_4_OFFSET] & 0x1F);
        i++;
    }

    PS_MEM_FREE(UEPS_PID_XSD, pucTmpdata);

    pstHomeSidNidList->ucSysNum = ucRecNum;
    CNAS_XSD_LogHomeSidNidList(pstHomeSidNidList);

    return;
}


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





