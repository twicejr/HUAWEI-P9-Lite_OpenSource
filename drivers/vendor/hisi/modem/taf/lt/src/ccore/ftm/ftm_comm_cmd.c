/******************************************************************************

                  版权所有 (C), 1998-2012, 华为技术有限公司

******************************************************************************
  文 件 名   : ftm_comm_cmd.c
  版 本 号   : V1.0
  作    者   : l00169177
  生成日期   : 2013-10-12
  功能描述   : 定义通用AT命令 DTS2013102611180

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2013-10-12
    作    者 : l00169177
    修改内容 : 创建文件
******************************************************************************/

#include <ftm_errno.h>
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
/*lint -save -e537*/
#include <AppRrcInterface.h>
#include "TafAppMma.h"
/*lint -restore*/
#include "Tds_ps_at.h"
#include "TPsTMspInterface.h"

/*lint -save -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_COMM_CMD_C
/*lint -restore*/

/*****************************************************************************
 函 数 名  : at_ftm_ltcommcmd_set
 功能描述  : ID_MSG_FTM_SET_LTCOMMCMD_REQ 处理函数
             进行LTE频段切换
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_set(VOS_VOID* pParam)
{
	/*lint -save -e813 -e550 */
    FTM_SET_LTCOMMCMD_CNF_STRU  stCnf = { 0 };
    FTM_SET_LTCOMMCMD_REQ_STRU* pstFtmReq   = (FTM_SET_LTCOMMCMD_REQ_STRU*)pParam;
    FTM_PHY_COMM_CMD_SET_REQ_STRU *pstReqToDsp = NULL;

    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;
	VOS_UINT32 ulLen = 0;

    (VOS_VOID)VOS_MemSet(&ftm_GetMainInfo()->stRdLtCommCmdCnf, 0, sizeof(FTM_RD_LTCOMMCMD_CNF_STRU) + pstFtmReq->ulDataLen);
    ftm_GetMainInfo()->stRdLtCommCmdCnf.ulErrCode = ERR_FTM_SUCCESS;

    ulLen = (sizeof(FTM_PHY_COMM_CMD_SET_REQ_STRU)+MAX_COMM_CMD_LEN);
    pstReqToDsp = (FTM_PHY_COMM_CMD_SET_REQ_STRU *)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT, ulLen);
    if (pstReqToDsp == VOS_NULL) {
        (VOS_VOID)vos_printf("[%s]failed to malloc\n",__FUNCTION__);
        return ERR_FTM_FAILURE;
    }
    pstReqToDsp->ulMsgId   = OM_PHY_COMM_CMD_SET_REQ;
    pstReqToDsp->ulDataLen = pstFtmReq->ulDataLen;
    (VOS_VOID)VOS_MemCpy(pstReqToDsp->cData, pstFtmReq->cData, pstReqToDsp->ulDataLen);

    switch(pstFtmReq->ulCmdDest)
    {
        case EN_LTCOMMCMD_DEST_LDSP_CT:
            ulRet = ftm_mailbox_ltect_write((void *)pstReqToDsp, ulLen);
            break;

        case EN_LTCOMMCMD_DEST_LDSP_BT:
            ulRet = ftm_mailbox_ltebt_write((void *)pstReqToDsp, ulLen);
            break;

        case EN_LTCOMMCMD_DEST_TDSP_CT:
            ulRet = ftm_mailbox_tdsct_write((void *)pstReqToDsp, ulLen);
            break;

        case EN_LTCOMMCMD_DEST_TDSP_BT:
            ulRet = ftm_mailbox_tdsbt_write((void *)pstReqToDsp, ulLen);
            break;

        default:
            ulRet = ERR_FTM_FAILURE;
    }

    (VOS_VOID)VOS_MemFree(WUEPS_PID_AT, pstReqToDsp);
    if (ERR_FTM_SUCCESS != ulRet)
    {
        stCnf.ulErrCode = ERR_FTM_UNKNOWN;
        stCnf.ulDataLen = 0;

        return ftm_comm_send(ID_MSG_FTM_SET_LTCOMMCMD_CNF,
            (VOS_UINT32)&stCnf, sizeof(FTM_SET_LTCOMMCMD_CNF_STRU));
    }
    return ERR_FTM_WAIT_ASYNC;
    /*lint -restore*/
}

/*****************************************************************************
 函 数 名  : at_ftm_ltcommcmd_read
 功能描述  : ID_MSG_FTM_RD_LTCOMMCMD_REQ 处理函数
 输入参数  : 无
 输出参数  : 无s
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_read(VOS_VOID* pParam)
{
    FTM_RD_LTCOMMCMD_CNF_STRU* pstFtmCnf = (FTM_RD_LTCOMMCMD_CNF_STRU *)&ftm_GetMainInfo()->stRdLtCommCmdCnf;

    return ftm_comm_send(ID_MSG_FTM_RD_LTCOMMCMD_CNF, (VOS_UINT32)pstFtmCnf, sizeof(FTM_RD_LTCOMMCMD_CNF_STRU) + pstFtmCnf->ulDataLen);
}

/*****************************************************************************
 函 数 名  : at_ftm_ltcommcmd_timeout
 功能描述  : 超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_timeout(VOS_VOID)
{
	/*lint -save -e813 -e550 */
	FTM_SET_LTCOMMCMD_CNF_STRU  stCnf = { 0 };

    stCnf.ulErrCode = ERR_FTM_TIME_OUT;
    stCnf.ulDataLen = 0;

   return ftm_comm_send(ID_MSG_FTM_SET_LTCOMMCMD_CNF,
            (VOS_UINT32)&stCnf, sizeof(FTM_SET_LTCOMMCMD_CNF_STRU));
    /*lint -restore*/
}

/*****************************************************************************
 函 数 名  : at_ftm_ltcommcmd_dspcnf
 功能描述  : DSP原语PHY_OM_COMM_CMD_SET_CNF处理函数
 输入参数  : pParam PHY_OM_COMM_CMD_SET_CNF_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_dspcnf(VOS_VOID* pParam)
{
    PHY_FTM_COMM_CMD_SET_CNF_STRU* pDspCnf = (PHY_FTM_COMM_CMD_SET_CNF_STRU*)pParam;
	/*lint -save -e813*/
    FTM_SET_LTCOMMCMD_CNF_STRU    *pstSetLtCommCmdCnf  = NULL;
	/*lint -restore*/
    VOS_UINT32 ulRet = 0;

    pstSetLtCommCmdCnf = (FTM_SET_LTCOMMCMD_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT,
        sizeof(FTM_SET_LTCOMMCMD_CNF_STRU) + pDspCnf->ulDataLen);

    if (pstSetLtCommCmdCnf == VOS_NULL){
        (VOS_VOID)vos_printf("[%s]failed to malloc\n",__FUNCTION__);
        return ERR_FTM_FAILURE;
    }
    pstSetLtCommCmdCnf->ulErrCode = ERR_FTM_SUCCESS;
    pstSetLtCommCmdCnf->ulDataLen = pDspCnf->ulDataLen;
    (VOS_VOID)VOS_MemCpy(pstSetLtCommCmdCnf->cData, pDspCnf->cData, pstSetLtCommCmdCnf->ulDataLen);

    ulRet = ftm_comm_send(ID_MSG_FTM_SET_LTCOMMCMD_CNF,
        (VOS_UINT32)pstSetLtCommCmdCnf,
        sizeof(FTM_SET_LTCOMMCMD_CNF_STRU) + pstSetLtCommCmdCnf->ulDataLen);
    (VOS_VOID)VOS_MemFree(WUEPS_PID_AT, pstSetLtCommCmdCnf);
    return ulRet;

}

/*****************************************************************************
 函 数 名  : at_ftm_ltcommcmd_dspind
 功能描述  : DSP原语PHY_OM_COMM_CMD_IND处理函数
 输入参数  : pParam PHY_OM_COMM_CMD_IND_STRU指针
 输出参数  : 无
 返 回 值  : 成功返回ERR_FTM_SUCCESS, 否则返回其他结果
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_dspind(VOS_VOID* pParam)
{
    PHY_FTM_COMM_CMD_IND_STRU* pDspInd    = (PHY_FTM_COMM_CMD_IND_STRU*)pParam;
    FTM_RD_LTCOMMCMD_CNF_STRU* pstFtmCnf = (FTM_RD_LTCOMMCMD_CNF_STRU *)&ftm_GetMainInfo()->stRdLtCommCmdCnf;

    (VOS_VOID)VOS_MemSet(pstFtmCnf, 0, sizeof(FTM_RD_LTCOMMCMD_CNF_STRU) + pDspInd->ulDataLen);
    pstFtmCnf->ulErrCode = ERR_FTM_SUCCESS;
    pstFtmCnf->ulDataLen = pDspInd->ulDataLen;
    (VOS_VOID)VOS_MemCpy(pstFtmCnf->cData, pDspInd->cData, pstFtmCnf->ulDataLen);

    return ERR_FTM_SUCCESS;
}

