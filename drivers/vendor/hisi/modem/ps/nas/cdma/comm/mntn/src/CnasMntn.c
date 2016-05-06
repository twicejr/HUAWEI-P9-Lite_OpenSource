/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasMntn.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月03日
  功能描述   : CNAS的可维可测
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasMntn.h"
#include "mdrv.h"

#include  "xsd_mscc_pif.h"
#include  "CnasCcb.h"
#include  "CnasXsdSndMscc.h"
#include  "msp_diag_comm.h"
#include  "NasOmTrans.h"
/* added by wx270776 for OM融合, 2015-08-21, begin */
#include "msp_diag_comm.h"
/* added by wx270776 for OM融合, 2014-08-21, end */
#include  "Nas_Mem.h"
#include "CnasXsdCtx.h"
#include "CnasXccCtx.h"
#include "CnasXregCtx.h"
#include "CnasHsdCtx.h"
#include "CnasHsmCtx.h"
#include "CnasEhsmCtx.h"
#include "CnasXccFsmMainTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define CNAS_MNTN_BYTE_LEN                      (8)
#define CNAS_TURN_BIT_TO_BYTE_LENGTH(a)         ((a)/CNAS_MNTN_BYTE_LEN)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_MNTN_CTX_STRU                      g_stCnasMntnCtx;

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_MNTN_SetPrintType
 功能描述  : 设置打印类型，默认是SDT打印，可通过此函数设置串口打印
 输入参数  : CNAS_MNTN_PRINT_TYPE_ENUM_UINT32    enPrintType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_SetPrintType(
    CNAS_MNTN_PRINT_TYPE_ENUM_UINT32    enPrintType
)
{
    CNAS_MNTN_PRINT_CTRL_INFO          *pstPrintCtrlInfo = VOS_NULL_PTR;

    pstPrintCtrlInfo = CNAS_MNTN_GetPrintCtrlInfoAddr();

    pstPrintCtrlInfo->enPrintType = enPrintType;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_SetPrintCtrlFlg
 功能描述  : 设置打印级别
 输入参数  : VOS_UINT32                          ulInfoPrintFlg
             VOS_UINT32                          ulNorPrintFlg
             VOS_UINT32                          ulWarnPrintFlg
             VOS_UINT32                          ulErrPrintFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_SetPrintCtrlFlg(
    VOS_UINT32                          ulInfoPrintFlg,
    VOS_UINT32                          ulNorPrintFlg,
    VOS_UINT32                          ulWarnPrintFlg,
    VOS_UINT32                          ulErrPrintFlg
)
{
    CNAS_MNTN_PRINT_CTRL_INFO          *pstPrintCtrlInfo = VOS_NULL_PTR;

    pstPrintCtrlInfo = CNAS_MNTN_GetPrintCtrlInfoAddr();

    pstPrintCtrlInfo->ulInfoPrintFlg = ulInfoPrintFlg;
    pstPrintCtrlInfo->ulNorPrintFlg  = ulNorPrintFlg;
    pstPrintCtrlInfo->ulWarnPrintFlg = ulWarnPrintFlg;
    pstPrintCtrlInfo->ulErrPrintFlg  = ulErrPrintFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_GetPrintCtrlFlg
 功能描述  : 获取打印控制开关
 输入参数  : LOG_LEVEL_EN                        enLevel
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_MNTN_GetPrintCtrlFlg(
    LOG_LEVEL_EN                        enLevel
)
{
    if (LOG_LEVEL_INFO == enLevel)
    {
        return CNAS_MNTN_GetInfoPrintFlg();
    }

    if (LOG_LEVEL_NORMAL == enLevel)
    {
        return CNAS_MNTN_GetNorPrintFlg();
    }

    if (LOG_LEVEL_WARNING == enLevel)
    {
        return CNAS_MNTN_GetWarnPrintFlg();
    }

    if (LOG_LEVEL_ERROR == enLevel)
    {
        return CNAS_MNTN_GetErrPrintFlg();
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_InitPrintMsgBuff
 功能描述  : 初始化需要打印消息的缓存
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_InitPrintMsgBuff(VOS_VOID)
{
    CNAS_MNTN_PRINT_MSG_STRU           *pstPrintMsg = VOS_NULL_PTR;

    pstPrintMsg = CNAS_MNTN_GetPrintMsgAddr();

    pstPrintMsg->ulCnt = 0;

    NAS_MEM_SET_S(pstPrintMsg->astPrintRecord, sizeof(pstPrintMsg->astPrintRecord), 0x00, sizeof(pstPrintMsg->astPrintRecord));
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_InitCtx
 功能描述  : 初始化可维可测上下文
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_InitCtx(VOS_VOID)
{
    /* 设置打印类型，默认输出到SDT */
    CNAS_MNTN_SetPrintType(CNAS_MNTN_PRINT_TYPE_SDT);

    /* 设置打印开关，默认INFO--false，NORMAL--false，WARNING--true，ERROR--true */
    CNAS_MNTN_SetPrintCtrlFlg(VOS_FALSE, VOS_FALSE, VOS_TRUE, VOS_TRUE);

    /* 初始化需要打印消息的缓存 */
    CNAS_MNTN_InitPrintMsgBuff();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_PrintToCom
 功能描述  : 串口打印处理
 输入参数  : LOG_LEVEL_EN                        enLevel
             VOS_CHAR                           *pcString,
             CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_PrintToCom(
    LOG_LEVEL_EN                        enLevel,
    VOS_CHAR                           *pcString,
    CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
)
{
    switch (enLevel)
    {
        case LOG_LEVEL_ERROR :
            vos_printf("\r\nERROR, ");
            break;

        case LOG_LEVEL_WARNING :
            vos_printf("\r\nWARNING, ");
            break;

        case LOG_LEVEL_NORMAL :
            vos_printf("\r\nNORMAL, ");
            break;

        case LOG_LEVEL_INFO :
            vos_printf("\r\nINFO, ");
            break;

        default:
            return;
    }

    switch (pstPara->ulParaNum)
    {
        case 0:
            vos_printf("%s \r\n", pcString);
            break;

        case 1:
            vos_printf("%s, %d \r\n", pcString, pstPara->lPara1);
            break;

        case 2:
            vos_printf("%s, %d, %d \r\n", pcString, pstPara->lPara1, pstPara->lPara2);
            break;

        case 3:
            vos_printf("%s, %d, %d, %d \r\n", pcString, pstPara->lPara1, pstPara->lPara2, pstPara->lPara3);
            break;

        case 4:
            vos_printf("%s, %d, %d, %d, %d \r\n", pcString, pstPara->lPara1, pstPara->lPara2, pstPara->lPara3, pstPara->lPara4);
            break;

        default:
            return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_MNTN_PrintToOm
 功能描述  : log信息输出到OM(SDT中勾消息)
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月07日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_PrintToOm(VOS_VOID)
{
    CNAS_MNTN_PRINT_MSG_STRU           *pstPrintMsg = VOS_NULL_PTR;
    CNAS_MNTN_LOG_MSG_INFO_IND_STRU    *pstMsg      = VOS_NULL_PTR;

    pstPrintMsg = CNAS_MNTN_GetPrintMsgAddr();

    if ((0                           == pstPrintMsg->ulCnt)
     || (CNAS_MNTN_PRINT_MSG_MAX_NUM <  pstPrintMsg->ulCnt))
    {
        pstPrintMsg->ulCnt = 0;

        return;
    }

    pstMsg = (CNAS_MNTN_LOG_MSG_INFO_IND_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                             sizeof(CNAS_MNTN_LOG_MSG_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_MSG_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_MSG_INFO_IND;

    NAS_MEM_CPY_S(&pstMsg->stPrintMsg, sizeof(CNAS_MNTN_PRINT_MSG_STRU), pstPrintMsg, sizeof(CNAS_MNTN_PRINT_MSG_STRU));

    DIAG_TraceReport(pstMsg);

    /* 清空记录 */
    CNAS_MNTN_InitPrintMsgBuff();

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogSave
 功能描述  : 保存打印信息
 输入参数  : VOS_UINT32                          ulPid
             VOS_CHAR                           *pcString
             LOG_LEVEL_EN                        enLevel
             CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogSave(
    VOS_UINT32                          ulPid,
    VOS_CHAR                           *pcString,
    LOG_LEVEL_EN                        enLevel,
    CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
)
{
    CNAS_MNTN_PRINT_MSG_STRU           *pstPrintMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgCnt;
    CNAS_MNTN_PRINT_TYPE_ENUM_UINT32    enPrintType;

    /* 判断对应的控制开关是否打开 */
    if (VOS_TRUE != CNAS_MNTN_GetPrintCtrlFlg(enLevel))
    {
        return;
    }

    /* 获取打印类别 */
    enPrintType = CNAS_MNTN_GetPrintType();

    /* 串口打印 */
    if (CNAS_MNTN_PRINT_TYPE_COM == enPrintType)
    {
        CNAS_MNTN_PrintToCom(enLevel,
                             pcString,
                             pstPara);

        return;
    }

    pstPrintMsg         = CNAS_MNTN_GetPrintMsgAddr();
    ulMsgCnt            = pstPrintMsg->ulCnt;

    /* 记录条数检查，如果大于等于10条，将条数清0 */
    if (ulMsgCnt >= CNAS_MNTN_PRINT_MSG_MAX_NUM)
    {
        /* 清空相应的条数 */
        pstPrintMsg->ulCnt      = 0;
        ulMsgCnt                = 0;
    }

    /* 填写打印信息记录内容 */
	/* Modified by wx270776 for OM融合, 2015-7-24, begin */
    pstPrintMsg->astPrintRecord[ulMsgCnt].ulTick      = VOS_GetTick();
	/* Modified by wx270776 for OM融合, 2015-7-24, end */
    pstPrintMsg->astPrintRecord[ulMsgCnt].enFile      = pstPara->enFile;
    pstPrintMsg->astPrintRecord[ulMsgCnt].ulLine      = pstPara->ulLine;
    pstPrintMsg->astPrintRecord[ulMsgCnt].enLevel     = enLevel;
    pstPrintMsg->astPrintRecord[ulMsgCnt].alPara[0]   = pstPara->lPara1;
    pstPrintMsg->astPrintRecord[ulMsgCnt].alPara[1]   = pstPara->lPara2;
    pstPrintMsg->astPrintRecord[ulMsgCnt].alPara[2]   = pstPara->lPara3;
    pstPrintMsg->astPrintRecord[ulMsgCnt].alPara[3]   = pstPara->lPara4;
    ulMsgCnt++;
    pstPrintMsg->ulCnt++;

    /* 如果记录条数满10条或者当前为ERROR打印，立即发送 */
    if ((ulMsgCnt >= CNAS_MNTN_PRINT_MSG_MAX_NUM)
     || (LOG_LEVEL_ERROR == enLevel))
    {
        CNAS_MNTN_PrintToOm();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogFsmInfo
 功能描述  : 为CNAS各个PID提供的勾状态机信息的函数
 输入参数  : VOS_UINT32                          ulPid
             VOS_UINT32                          ulFsmId
             VOS_UINT32                          ulFsmState
             VOS_UINT8                           ucConnectId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogFsmInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState,
    VOS_UINT8                           ucConnectId
)
{
    CNAS_MNTN_LOG_FSM_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_MNTN_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(CNAS_MNTN_LOG_FSM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_FSM_INFO_IND;
    pstMsg->ulModuleId      = ulPid;
    pstMsg->ulCurFsmId      = ulFsmId;
    pstMsg->ulCurFsmState   = ulFsmState;
    pstMsg->ucConnectId     = ucConnectId;

    NAS_MEM_SET_S(pstMsg->aucReserved, sizeof(pstMsg->aucReserved), 0x00, sizeof(pstMsg->aucReserved));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogReadNVInfo
 功能描述  : 勾取读取的NV信息上报 可维可测
 输入参数  : enNvItem,  nv项
             usNvDataLength,  nv数据长度
             ulPid,
            *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00322978
    修改内容   : 新生成函数
  2.日    期   : 2015年10月08日
    作    者   : t00323010
    修改内容   : DTS2015092201636修改接头体名字

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogReadNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
)
{
    CNAS_DIAG_LOG_NV_INFO_IND_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_DIAG_LOG_NV_INFO_IND_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(CNAS_DIAG_LOG_NV_INFO_IND_STRU) + usNvDataLength - 4);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(CNAS_DIAG_LOG_NV_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH + usNvDataLength - 4;
    pstMsg->enMsgId         = ID_CNAS_DIAG_LOG_READ_NV_INFO_IND;
    pstMsg->enNvItem        = enNvItem;
    pstMsg->usNvDataLength  = usNvDataLength;
    NAS_MEM_CPY_S(pstMsg->aucNvInfo, usNvDataLength, pucData, usNvDataLength);

    DIAG_TraceReport((VOS_VOID *)pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogWriteNVInfo
 功能描述  : 勾取写NV信息上报 可维可测
 输入参数  : enNvItem,  nv项
             usNvDataLength,  nv数据长度
             ulPid,
            *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月8日
    作    者   : t00323010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogWriteNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
)
{
    CNAS_DIAG_LOG_NV_INFO_IND_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_DIAG_LOG_NV_INFO_IND_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(CNAS_DIAG_LOG_NV_INFO_IND_STRU) + usNvDataLength - 4);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(CNAS_DIAG_LOG_NV_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH + usNvDataLength - 4;
    pstMsg->enMsgId         = ID_CNAS_DIAG_LOG_WRITE_NV_INFO_IND;
    pstMsg->enNvItem        = enNvItem;
    pstMsg->usNvDataLength  = usNvDataLength;
    NAS_MEM_CPY_S(pstMsg->aucNvInfo, usNvDataLength, pucData, usNvDataLength);

    DIAG_TraceReport((VOS_VOID *)pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogKeyEvent
 功能描述  : 关键事件上报
 输入参数  : enEvent   事件名称
             ulSendPid  发送pid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogKeyEvent(
    NAS_OM_EVENT_ID_ENUM                enEvent,
    VOS_UINT32                          ulSendPid
)
{
    DIAG_EVENT_IND_STRU                 stEvent;
    DIAG_MODE_TYPE_U32                  enDiagMode;

    NAS_MEM_SET_S(&stEvent, sizeof(stEvent), 0x00, sizeof(stEvent));

    /*EVENT消息赋值*/
    if ((UEPS_PID_HSD == ulSendPid) ||(UEPS_PID_HSM == ulSendPid))
    {
        enDiagMode = DIAG_MODE_HRPD;
    }
    else if (UEPS_PID_XSD == ulSendPid)
    {
        enDiagMode = DIAG_MODE_1X;
    }
    else
    {
        enDiagMode = DIAG_MODE_COMM;
    }
    stEvent.ulModule = DIAG_GEN_MODULE(CNAS_CCB_GetCdmaModeModemId(), enDiagMode);
    stEvent.ulEventId = enEvent;

    stEvent.ulPid     = ulSendPid;
    stEvent.ulEventId = enEvent;

    /*上报空口消息*/
    (VOS_VOID)DIAG_EventReport(&stEvent);
    return;
}


/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogUsimmApiGetFileReq
 功能描述  : 调用API接口USIMM_GetFileReq时，以消息形式在SDT中进行显示
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT32                          ulRslt
             CNAS_MNTN_LOG_GETFILE_INFO_STRU    *pstGetFileInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogUsimmApiGetFileReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulRslt,
    CNAS_MNTN_LOG_GETFILE_INFO_STRU    *pstGetFileInfo
)
{
    CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    if (VOS_NULL_PTR != pstGetFileInfo)
    {
        pstMsg = (CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU*)PS_MEM_ALLOC(ulModuleId,
                              sizeof(CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU));

        if (VOS_NULL_PTR == pstMsg)
        {
            return;
        }

        NAS_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                      sizeof(CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                      0,
                      sizeof(CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

        pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMsg->ulSenderPid     = ulModuleId;
        pstMsg->ulReceiverPid   = WUEPS_PID_USIM;
        pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
        pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ;

        pstMsg->ulRslt                      = ulRslt;
        pstMsg->usFileID                    = pstGetFileInfo->usEfId;
        pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;
        pstMsg->enAppType                   = pstGetFileInfo->enAppType;

        DIAG_TraceReport(pstMsg);

        PS_MEM_FREE(ulModuleId, pstMsg);
    }
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_TraceIntMsg
 功能描述  : CNAS内部模块间消息勾包
 输入参数  : ulSenderPid     申请消息的模块
             *pstSndMsg      消息
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月07日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  CNAS_MNTN_TraceIntMsg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulLength,
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;

    pucData = (VOS_UINT8 *)PS_MEM_ALLOC(ulModuleId, ulLength);

    if (VOS_NULL_PTR == pucData)
    {
        CNAS_ERROR_LOG(ulModuleId, "CNAS_CDMA_TraceIntMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    /* 勾包消息赋值 */
    NAS_MEM_CPY_S(pucData, ulLength, pMsg, ulLength);

    /* 消息勾包 */
    DIAG_TraceReport(pucData);

    PS_MEM_FREE(ulModuleId, pucData);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_TraceTimerMsg
 功能描述  : CNAS内部模块间timer消息勾包
 输入参数  : ulSenderPid     申请消息的模块
             *pstSndMsg      消息
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月07日
    作    者   : y00245242
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_TraceTimerMsg(
    VOS_UINT32                          ulModuleId,
    CNAS_MNTN_TIMER_INFO_STRU          *pstMntnTimerInfo
)
{
    CNAS_MNTN_LOG_TIMER_INFO_IND_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_MNTN_LOG_TIMER_INFO_IND_STRU *)PS_MEM_ALLOC(ulModuleId, sizeof(CNAS_MNTN_LOG_TIMER_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(ulModuleId, "CNAS_MNTN_TraceTimerMsg:ERROR:Alloc Mem Fail!");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = VOS_PID_TIMER;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulModuleId;
    pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_TIMER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_TIMER_INFO_IND;

    pstMsg->ulModuleId      = ulModuleId;
    pstMsg->enTimerAct      = pstMntnTimerInfo->enTimerAct;
    pstMsg->ulTimerId       = pstMntnTimerInfo->ulTimerId;
    pstMsg->ulParam         = pstMntnTimerInfo->ulParam;
    pstMsg->ulTimerLen      = pstMntnTimerInfo->ulTimerLen;

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ulModuleId, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogEncodeAbnormalInfoInd
 功能描述  : 调用encodix编码API进行编码失败，上报可维可测消息
 输入参数  : VOS_UINT32                              ulModuleId,
             VOS_INT32                               lRslt,
             CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enEncodeMsgType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : l00256032
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogEncodeAbnormalInfoInd(
    VOS_UINT32                              ulModuleId,
    VOS_INT32                               lRslt,
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enEncodeMsgType
)
{
    CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU               *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU*)PS_MEM_ALLOC(ulModuleId,
                          sizeof(CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulModuleId;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulModuleId;
    pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND;
    pstMsg->lRslt           = lRslt;
    pstMsg->enEncodeMsgType = enEncodeMsgType;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ulModuleId, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogDecodeAbnormalInfoInd
 功能描述  : 调用encodix编码API进行解码失败，上报可维可测消息
 输入参数  : VOS_UINT32                              ulModuleId,
             VOS_INT32                               lRslt,
             CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enEncodeMsgType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : l00256032
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogDecodeAbnormalInfoInd(
    VOS_UINT32                              ulModuleId,
    VOS_INT32                               lRslt,
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8  enDecodeMsgType
)
{
    CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU               *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU*)PS_MEM_ALLOC(ulModuleId,
                          sizeof(CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulModuleId;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulModuleId;
    pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND;
    pstMsg->lRslt           = lRslt;
    pstMsg->enDecodeMsgType = enDecodeMsgType;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ulModuleId, pstMsg);

    return;
}


VOS_VOID CNAS_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    CNAS_REBOOT_INFO_STRU               stCnasRebootInfo
)
{
    VOS_UINT32                          ulSlice;
    VOS_UINT32                          ulTaskTcb;
    NAS_REBOOT_MOD_ID_ENUM_UINT32       ulModuleId;
    VOS_UINT32                          ulFsmId;
    VOS_UINT32                          ulFsmTopState;
    VOS_UINT8                           ucRebootScene;

    /* Modified by wx270776 for OM融合, 2015-7-23, begin */
    ulSlice   = VOS_GetSlice();
    /* Modified by wx270776 for OM融合, 2015-7-23, end */

    if (UEPS_PID_XSD == stCnasRebootInfo.ulPid)
    {
        ulModuleId = NAS_REBOOT_MOD_ID_XSD;
    }
    else if (UEPS_PID_HSD == stCnasRebootInfo.ulPid)
    {
        ulModuleId = NAS_REBOOT_MOD_ID_HSD;
    }
    else
    {
        ulModuleId = NAS_REBOOT_MOD_ID_BUTT;
    }

    ulTaskTcb = VOS_GetTCBFromPid(stCnasRebootInfo.ulPid);

    ulFsmTopState = stCnasRebootInfo.ulFsmState;
    ulFsmId       = stCnasRebootInfo.ulFsmId;
    ucRebootScene = stCnasRebootInfo.enRebootScene;

    mdrv_om_system_error( (VOS_INT)(ulModuleId | ucRebootScene
                          | (ulFsmTopState << 8) | (ulFsmId << 16)),
                          (VOS_INT)ulTaskTcb,
                          (VOS_INT)((ulFileID << 16) | ulLineNO),
                          (VOS_CHAR *)(&ulSlice),
                          sizeof(ulSlice) );
    return;

}

/*****************************************************************************
 函 数 名  : CNAS_HandsetInfoQry_Proc
 功能描述  : 处理MSCC的手机信息查询请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HandsetInfoQry_Proc(
    VOS_UINT32                          ulInfoType
)
{
    if (CNAS_HANDSET_INFO_TYPE_STATE == ulInfoType)
    {
        CNAS_HandsetStateInfo_Proc(ulInfoType);
    }
    else
    {
        CNAS_HandsetHighVerInfo_Proc(ulInfoType);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HandsetStateInfo_Proc
 功能描述  : 处理MSCC的手机状态信息查询请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HandsetStateInfo_Proc(
    VOS_UINT32                          ulInfoType
)
{
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU                      stHandSetInfo;
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8                        enSta;
    CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8                    enCasSubSta;
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       en1xCallState;
    VOS_UINT8                                               ucSubSta;

    enSta        = CNAS_CCB_GetCasState();

    enCasSubSta  = CNAS_CCB_GetCasSubState();

    /* 尝试读取CAS上报的状态失败后，读取XCC上报的状态 */
    if (((CNAS_CCB_1X_CAS_TCH_STATE              == enSta)
     && (CNAS_CCB_1X_CAS_SUB_STATE_NULL        == enCasSubSta))
     || (CNAS_CCB_1X_CAS_SUB_STATE_ENUM_BUTT    == enCasSubSta))
    {
        en1xCallState  = CNAS_CCB_Get1xVoiceCallState();

        if ((CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ORDER == en1xCallState)
         || (CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER == en1xCallState)
         || (CNAS_CCB_1X_CALL_STATE_CONVERSATION == en1xCallState))
        {
            ucSubSta = (VOS_UINT8)en1xCallState;
        }
        else
        {
            ucSubSta = CNAS_CAS_INVALID_SUBSTA;
        }

    }
    else
    {
        ucSubSta     = (VOS_UINT8)enCasSubSta;
    }

    NAS_MEM_SET_S(&stHandSetInfo, sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU), 0x00, sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU));

    stHandSetInfo.ulInfoType    = ulInfoType;
    stHandSetInfo.ucCasState    = (VOS_UINT8)enSta;
    stHandSetInfo.ucCasSubSta   = ucSubSta;

    CNAS_XSD_SndMsccHandSetInfoCnf(&stHandSetInfo);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HandsetHighVerInfo_Proc
 功能描述  : 处理MSCC的手机的版本信息查询请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : z00316370
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HandsetHighVerInfo_Proc(
    VOS_UINT32                          ulInfoType
)
{
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU  stHandSetInfo;

    NAS_MEM_SET_S(&stHandSetInfo, sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU), 0x00, sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU));

    stHandSetInfo.ulInfoType    = ulInfoType;
    stHandSetInfo.ucHighVer     = (VOS_UINT8)CNAS_CCB_GetHighProRev();

    CNAS_XSD_SndMsccHandSetInfoCnf(&stHandSetInfo);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_LogOmAirMsg
 功能描述  : HRPD空口消息上报 可维可测接口
 输入参数  : ulDir,  消息方向
             ulAirMsgId, 消息id
             ulSendPid, 发送pid
             ulLength,  数据长度
             *pucData   数据码流
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月6日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogOmAirMsg(
    CNAS_HRPD_OM_AIR_MSG_UP_DOWN_ENUM_UINT8                 ulDir,
    VOS_UINT16                                              ulAirMsgId,
    VOS_UINT32                                              ulSendPid,
    VOS_UINT32                                              ulLength,
    VOS_UINT8                                              *pucData
)
{
    DIAG_AIR_IND_STRU                                       stAirMsg;
    NAS_AIR_MSG_STRU                                       *pstNasAirMsg    = VOS_NULL_PTR;
    VOS_UINT32                                              ulNasAirMsgLen;
    VOS_UINT32                                              ulByteLength;

    if ( (0 == ulLength) || (VOS_NULL_PTR == pucData ))
    {
        CNAS_WARNING_LOG(ulSendPid, "CNAS_MNTN_LogOmAirMsg:Input params invalid.");
        return;
    }
    ulByteLength = CNAS_TURN_BIT_TO_BYTE_LENGTH(ulLength);
    ulNasAirMsgLen = sizeof(NAS_AIR_MSG_STRU) + ulByteLength + sizeof(ulByteLength);
    pstNasAirMsg = (NAS_AIR_MSG_STRU*)PS_MEM_ALLOC(ulSendPid, ulNasAirMsgLen);
    if ( VOS_NULL_PTR == pstNasAirMsg )
    {
        CNAS_WARNING_LOG(ulSendPid, "CNAS_MNTN_LogOmAirMsg:WARNING: PS_MEM_ALLOC Failed!");
        return;
    }

    /* 初始化 */
    NAS_MEM_SET_S(pstNasAirMsg, ulNasAirMsgLen, 0x00, ulNasAirMsgLen);

    pstNasAirMsg->usMsgId            = ulAirMsgId;
    pstNasAirMsg->ucUpDown           = ulDir;
    pstNasAirMsg->ucReserve          = 0;
    pstNasAirMsg->ulLengthASN        = ulByteLength + sizeof(ulByteLength);         /* sizeof (bitlength + bitcode) */
    NAS_MEM_CPY_S(pstNasAirMsg->aucNasMsg, sizeof(ulByteLength), &ulByteLength, sizeof(ulByteLength));       /* bitlength value*/
    NAS_MEM_CPY_S(pstNasAirMsg->aucNasMsg + sizeof(ulByteLength), ulByteLength, pucData, ulByteLength);       /* bitcode value*/


    /*空口消息赋值*/
    if(CNAS_HRPD_OM_AIR_MSG_UP == ulDir)
    {
        stAirMsg.ulDirection = DIAG_SIDE_NET;
    }
    else
    {
        stAirMsg.ulDirection = DIAG_SIDE_UE;
    }
    stAirMsg.ulModule   = DIAG_GEN_MODULE(CNAS_CCB_GetCdmaModeModemId(), DIAG_MODE_HRPD);
    stAirMsg.ulPid      = ulSendPid;
    stAirMsg.ulMsgId    = ulAirMsgId;
    stAirMsg.ulLength   = ulNasAirMsgLen - CNAS_MNTN_LOG_AIR_MSG_OFFSET;
    stAirMsg.pData      = (VOS_VOID *)pstNasAirMsg;


    /* wait for debug */
    /*上报空口消息*/
    (VOS_VOID)DIAG_AirMsgReport(&stAirMsg);


    PS_MEM_FREE(ulSendPid, pstNasAirMsg);

    return;
}


/*****************************************************************************
函 数 名  : CNAS_MNTN_AddLogMsgState
功能描述  : 增加stLogMsgState
输入参数  : usSendPid, usMsgName,usReceivePid
输出参数  : 无
修改历史      :
1.日    期   : 2015年7月2日
  作    者   : y00322978
  修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_AddLogMsgState(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulReceivePid,
    VOS_UINT16                          usMsgName
)
{
    CNAS_CCB_LOG_MSG_STATUS_STRU       *pstLogMsgState;
    VOS_UINT32                          ucIndex;

    pstLogMsgState = &(CNAS_CCB_GetCcbCtxAddr()->stMntnInfo.stLogMsgState);

    pstLogMsgState->ucLatestIndex = (pstLogMsgState->ucLatestIndex + 1) % CNAS_CCB_MAX_LOG_MSG_STATE_NUM;

    ucIndex                       = pstLogMsgState->ucLatestIndex;

    NAS_MEM_SET_S(&(pstLogMsgState->stMsgState[ucIndex]), sizeof(CNAS_CCB_MSG_STATE_STRU), 0, sizeof(CNAS_CCB_MSG_STATE_STRU));

    pstLogMsgState->stMsgState[ucIndex].ulReceiveTime = VOS_GetTick();
    pstLogMsgState->stMsgState[ucIndex].usSendPid     = (VOS_UINT16)ulSendPid;
    pstLogMsgState->stMsgState[ucIndex].usReceivePid  = (VOS_UINT16)ulReceivePid;
    pstLogMsgState->stMsgState[ucIndex].usMsgName     = usMsgName;

    if ((UEPS_PID_XSD == ulSendPid)
     || (UEPS_PID_XSD == ulReceivePid))
    {
        pstLogMsgState->stMsgState[ucIndex].ucCnasFsmId = (VOS_UINT8)CNAS_XSD_GetCurrFsmId();
        pstLogMsgState->stMsgState[ucIndex].ucCnasState = (VOS_UINT8)CNAS_XSD_GetFsmTopState();
    }
    else if ((UEPS_PID_XCC == ulSendPid)
          || (UEPS_PID_XCC == ulReceivePid))
    {
        if (VOS_NULL_PTR == CNAS_XCC_GetCtxAddr()->pstCurFsmEntity)
        {
            pstLogMsgState->stMsgState[ucIndex].ucCnasFsmId = (VOS_UINT8)CNAS_XCC_FSM_BUTT;
            pstLogMsgState->stMsgState[ucIndex].ucCnasState = (VOS_UINT8)CNAS_XCC_L1_STA_BUTT;
        }
        else
        {
            pstLogMsgState->stMsgState[ucIndex].ucCnasFsmId = (VOS_UINT8)CNAS_XCC_GetCurrFsmId();
            pstLogMsgState->stMsgState[ucIndex].ucCnasState = (VOS_UINT8)CNAS_XCC_GetFsmTopState();
        }
    }
    else if ((UEPS_PID_XREG == ulSendPid)
          || (UEPS_PID_XREG == ulReceivePid))
    {
        pstLogMsgState->stMsgState[ucIndex].ucCnasFsmId = (VOS_UINT8)CNAS_XREG_GetCurrFsmId();
        pstLogMsgState->stMsgState[ucIndex].ucCnasState = (VOS_UINT8)CNAS_XREG_GetFsmTopState();
    }
    else if ((UEPS_PID_HSD == ulSendPid)
          || (UEPS_PID_HSD == ulReceivePid))
    {
        pstLogMsgState->stMsgState[ucIndex].ucCnasFsmId = (VOS_UINT8)CNAS_HSD_GetCurrFsmId();
        pstLogMsgState->stMsgState[ucIndex].ucCnasState = (VOS_UINT8)CNAS_HSD_GetFsmTopState();
    }
    else if ((UEPS_PID_HSM == ulSendPid)
          || (UEPS_PID_HSM == ulReceivePid))
    {
        /* HSM状态机只有主状态和子状态之分，此时ucCnasFsmId中保存的是hsm模块的主状态，ucCnasState中保存的是子状态 */
        pstLogMsgState->stMsgState[ucIndex].ucCnasFsmId = (VOS_UINT8)CNAS_HSM_GetCurrMainState();
        pstLogMsgState->stMsgState[ucIndex].ucCnasState = (VOS_UINT8)CNAS_HSM_GetCurrSubState();
    }
    else if ((UEPS_PID_EHSM == ulSendPid)
          || (UEPS_PID_EHSM == ulReceivePid))
    {
        pstLogMsgState->stMsgState[ucIndex].ucCnasFsmId = (VOS_UINT8)CNAS_EHSM_GetCurrFsmId();
        pstLogMsgState->stMsgState[ucIndex].ucCnasState = (VOS_UINT8)CNAS_EHSM_GetFsmTopState();
    }
    else if ((UEPS_PID_HLU == ulSendPid)
          || (UEPS_PID_HLU == ulReceivePid))
    {
        /* HLU模块没有状态，不用勾取 */
    }
    else
    {
        /* do nothing */
    }


    return;
}
/*****************************************************************************
 函 数 名  : CNAS_CCB_UpdateExitTime
 功能描述  : 更新消息退出的时间
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_UpdateMsgExitTime( VOS_VOID )
{
    CNAS_CCB_LOG_MSG_STATUS_STRU       *pstLogMsgState;
    VOS_UINT32                          ucIndex;

    pstLogMsgState = &(CNAS_CCB_GetCcbCtxAddr()->stMntnInfo.stLogMsgState);
    ucIndex = pstLogMsgState->ucLatestIndex;

    pstLogMsgState->stMsgState[ucIndex].ulExitTime = VOS_GetTick();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogMsgInfo
 功能描述  : 判断消息是否是定时器发出的，如果是就打印定时器信息，否则打印消
             息信息
 输入参数  : MSG_HEADER_STRU
 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMsgHeader
)
{
    VOS_UINT32                          ulSenderPid;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgName;

    /* 判断发送id是否是定时器 */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        ulSenderPid      =    ((REL_TIMER_MSG*)pstMsgHeader)->ulSenderPid;
        ulReceiverPid    =    ((REL_TIMER_MSG*)pstMsgHeader)->ulReceiverPid;
        ulMsgName        =    ((REL_TIMER_MSG*)pstMsgHeader)->ulName;
    }
    else
    {
        ulSenderPid      =    pstMsgHeader->ulSenderPid;
        ulReceiverPid    =    pstMsgHeader->ulReceiverPid;
        ulMsgName        =    pstMsgHeader->ulMsgName;
    }

    /* 打印消息 */
    CNAS_MNTN_AddLogMsgState(ulSenderPid, ulReceiverPid, (VOS_UINT16)ulMsgName);

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_MNTN_LogCommonStatusInfo
 功能描述  : 勾取公共状态信息(目前仅有卡状态)
 输入参数  : VOS_UINT32                          ulPid,
             VOS_UINT8                           ucCardStatus

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_LogCommonStatusInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT8                           ucCardStatus
)
{
    CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU              *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND;
    pstMsg->ucCsimStatus    = ucCardStatus;

    NAS_MEM_SET_S(pstMsg->aucReserved, sizeof(pstMsg->aucReserved), 0x00, sizeof(pstMsg->aucReserved));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);
}
/*****************************************************************************
 函 数 名  : CNAS_MNTN_Log1xCschDataIndMsg
 功能描述  : 勾取cas发给cnas的csch data ind消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月4日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_MNTN_Log1xCschDataIndMsg(
    VOS_UINT32                                              ulPid,
    VOS_UINT16                                              usMsgDataLen,
    CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enCschMsgType,
    VOS_UINT8                                              *pucData
)
{
    CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU                    *pstMsg = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgByteLen;

    usMsgByteLen = usMsgDataLen/CNAS_CCB_BYTE_LEN_8_BIT + 1;
    pstMsg       = (CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU) + usMsgByteLen - 4);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH + usMsgByteLen - 4;
    pstMsg->enMsgId         = ID_CNAS_MNTN_LOG_1X_CSCH_DATA_IND;
    pstMsg->usMsgDataLen    = usMsgByteLen;
    pstMsg->enCschMsgType   = enCschMsgType;
    pstMsg->ucReserv        = 0;

    NAS_MEM_CPY_S(pstMsg->aucData, usMsgByteLen, pucData, usMsgByteLen);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);
}

VOS_VOID CNAS_MNTN_TestMemSoftReboot()
{
    VOS_UINT8                          *pucMem = VOS_NULL_PTR;

    pucMem = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XCC, 4);

    NAS_MEM_SET_S(pucMem, 4, 0x00, 5);

    PS_MEM_FREE(UEPS_PID_XCC, pucMem);
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



