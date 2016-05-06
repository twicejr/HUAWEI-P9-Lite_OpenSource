/************************************************************************
*                                                                      *
*                             pppc_pa_agent.c                          *
*                                                                      *
*  Project Code:       X Project                                       *
*  Create Date:        2015/06/05                                      *
*  Author:             Chenxianhua                                     *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           实现PA模块的代理功能                            *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 Balong Team ShangHai Institute HuaWei Tech, Inc.*
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件实现PA模块的代理功能                                       *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "cttf_hrpd_pa_ppp_pif.h"
#include "pppc_pa_agent.h"
#include "cttf_hrpd_sig_public_pif.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_PA_AGENT_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
PA_AGENT_HRPD_CONTEXT_STRU              g_stPaAgentContext;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentInit
功能描述  : 初始化PA AGENT上下文
输入参数  : 无
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentInit(VOS_VOID)
{
    PS_MEM_SET(&g_stPaAgentContext, 0, sizeof(g_stPaAgentContext));

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRlpTimeout
功能描述  : RLP定时器超时处理函数
输入参数  : ulTimerName     标识是哪个定时器
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRlpTimeout(VOS_UINT32 ulTimerName)
{
    PA_AGENT_HRPD_CONTEXT_STRU         *pstPaAgentCont;



    pstPaAgentCont = &g_stPaAgentContext;

    if (ulTimerName >= PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM)
    {
        PPPC_WARNING_LOG1("RLP timer name is invalid!\r\n", ulTimerName);
        return;
    }

    if (VOS_NULL_PTR == pstPaAgentCont->astReservMsgBuff[ulTimerName].pucMsgDataPtr)
    {
        PPPC_WARNING_LOG1("Data ptr is null!\r\n", ulTimerName);
        PS_MEM_SET(&(pstPaAgentCont->astReservMsgBuff[ulTimerName]), 0,
            sizeof(PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU));
        return;
    }

    PA_AGENT_SET_TRANSACTION_ID(pstPaAgentCont->ucReservTransacId,
        pstPaAgentCont->astReservMsgBuff[ulTimerName].pucMsgDataPtr)

    /* CTTF_HRPD_RPA_SendReservationMsgToSnp(pstPaAgentCont->astReservMsgBuff[ulTimerName].pucMsgDataPtr); */

    pstPaAgentCont->ucReservTransacId++;

    PS_MEM_FREE(MSPS_PID_PA_AGENT, pstPaAgentCont->astReservMsgBuff[ulTimerName].pucMsgDataPtr);

    PS_MEM_SET(&(pstPaAgentCont->astReservMsgBuff[ulTimerName]), 0,
        sizeof(PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU));

    return;
}

/*****************************************************************************
函 数 名  : PA_AGENT_HRPD_SetMaxReservNum
功能描述  : 设置最大Reservation个数
输入参数  : 无
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PA_AGENT_HRPD_SetMaxReservNum
(
    CTTF_PPP_HRPD_RESERVATIONS_IND_STRU    *pstReservationsInd
)
{
    PA_AGENT_HRPD_CONTEXT_STRU             *pstPaAgentCont;


    /* 内部调用，保证指针非空 */

    pstPaAgentCont  = &g_stPaAgentContext;

    if ((pstReservationsInd->ucMaxNumReservationsFwd < pstReservationsInd->ucMaxNumOpenReservationsFwd)
        || (pstReservationsInd->ucMaxNumReservationsRev < pstReservationsInd->ucMaxNumOpenReservationsRev))
    {
        PPPC_WARNING_LOG4("No more space to store!\r\n",
            pstReservationsInd->ucMaxNumReservationsFwd,
            pstReservationsInd->ucMaxNumOpenReservationsFwd,
            pstReservationsInd->ucMaxNumReservationsRev,
            pstReservationsInd->ucMaxNumOpenReservationsRev);
        return;
    }

    pstPaAgentCont->stReservMntn.ucMaxNumOpenReservFwd
                    = pstReservationsInd->ucMaxNumOpenReservationsFwd;
    pstPaAgentCont->stReservMntn.ucMaxNumOpenReservRev
                    = pstReservationsInd->ucMaxNumOpenReservationsRev;
    pstPaAgentCont->stReservMntn.ucMaxNumReservFwd
                    = pstReservationsInd->ucMaxNumReservationsFwd;
    pstPaAgentCont->stReservMntn.ucMaxNumReservRev
                    = pstReservationsInd->ucMaxNumReservationsRev;

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentGetResvLabel
功能描述  : Reverse方向的Reservation迁移到OPEN状态
输入参数  : pucData        Reservation信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 PPPC_HRPD_PaAgentGetResvLabel
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType
)
{
    if ((CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_SN == enAppType)
        || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_SN == enAppType))
    {
        /* TODO:根据应用类型及Reservation状态信息获取,由于缺少应用信息直接使用0xff */
        return PPPC_HRPD_PA_BEST_EFFORT;
    }
    else
    {
        return PPPC_HRPD_PA_BEST_EFFORT;
    }
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRevReservTransferToOpenState
功能描述  : Reverse方向的Reservation迁移到OPEN状态
输入参数  : pucData        Reservation信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRevReservTransferToOpenState
(
    VOS_UINT8                          *pucData
)
{
    PA_AGENT_HRPD_CONTEXT_STRU         *pstPaAgentCont;
    VOS_UINT8                          *pucReservInfoData;
    VOS_UINT8                           ucReservCnt;
    VOS_UINT8                           ucReservLabel;
    VOS_UINT32                          ulOpenIndx;
    VOS_UINT32                          ulStoreIndx;
    VOS_UINT32                          ulFinalIdleIndx;
    PS_BOOL_ENUM_UINT8                  enIsFindFlag;
    PA_AGENT_HRPD_RESERV_STATE_STRU    *pstRevReservState;
    PA_AGENT_HRPD_RESERV_STATE_MNTN_STRU *pstReservMntn;

    pucReservInfoData = pucData;

    pstPaAgentCont  = &g_stPaAgentContext;
    pstReservMntn   = &(pstPaAgentCont->stReservMntn);

    /* 取出Reservation数目 */
    PA_AGENT_GETCHAR(ucReservCnt, pucReservInfoData);

    /* 处理每一个Reservation */
    for (ulOpenIndx = 0; ulOpenIndx < ucReservCnt; ulOpenIndx++)
    {
        PA_AGENT_GETCHAR(ucReservLabel, pucReservInfoData)

        /* 遍历查询前设置标志位 */
        enIsFindFlag    = PS_FALSE;
        ulFinalIdleIndx = 0xff;

        /* 找到最后一个空闲的位置，遍历查询是否已经有相同的Label存在 */
        for (ulStoreIndx = 0; ulStoreIndx < PA_AGENT_MAX_RESERVATION_NUM; ulStoreIndx++)
        {
            pstRevReservState = &(pstReservMntn->astRevReservState[ulStoreIndx]);

            if (PS_FALSE == pstRevReservState->enIsValid)
            {
                /* 刷新空闲位置标记 */
                ulFinalIdleIndx = ulStoreIndx;
            }
            else
            {
                if (ucReservLabel == pstRevReservState->ucReservLabel)
                {
                    /* 已经有相同的Label存在 */
                    enIsFindFlag    = PS_TRUE;
                    break;
                }
            }
        }

        if (PS_FALSE == enIsFindFlag)
        {
            /* 如果遍历一次没有一个空位可供存储，退出 */
            if (0xff == ulFinalIdleIndx)
            {
                PPPC_WARNING_LOG4("No more space to store!\r\n", ulStoreIndx,
                    ulOpenIndx, ucReservCnt, ucReservLabel);
                return;
            }

            /* 没有找到，且还有空位可以填入 */
            pstRevReservState = &(pstReservMntn->astRevReservState[ulFinalIdleIndx]);

            pstRevReservState->enIsValid     = PS_TRUE;
            pstRevReservState->ucReservLabel = ucReservLabel;
            (pstReservMntn->ucRevReervOpenNum)++;
        }

        /* 如果已找到，不用插入，continue */
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRevReservTransferToCloseState
功能描述  : Reverse方向的Reservation迁移到CLOSE状态
输入参数  : pMsg        Reservation信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRevReservTransferToCloseState(VOS_UINT8 *pucReservInfoData)
{
    PA_AGENT_HRPD_CONTEXT_STRU         *pstPaAgentCont;
    VOS_UINT8                           ucReservCnt;
    VOS_UINT8                           ucReservLabel;
    VOS_UINT32                          ulOpenIndx;
    VOS_UINT32                          ulStoreIndx;
    PA_AGENT_HRPD_RESERV_STATE_STRU    *pstRevReservState;

    pstPaAgentCont  = &g_stPaAgentContext;

    /* 取出Reservation数目 */
    PA_AGENT_GETCHAR(ucReservCnt, pucReservInfoData);

    /* 处理每一个Reservation */
    for (ulOpenIndx = 0; ulOpenIndx < ucReservCnt; ulOpenIndx++)
    {
        PA_AGENT_GETCHAR(ucReservLabel, pucReservInfoData)

        /* 找到符合条件的Label，并清除信息 */
        for (ulStoreIndx = 0; ulStoreIndx < PA_AGENT_MAX_RESERVATION_NUM; ulStoreIndx++)
        {
            pstRevReservState = &(pstPaAgentCont->stReservMntn.astRevReservState[ulStoreIndx]);

            if ((PS_TRUE == pstRevReservState->enIsValid)
                && (ucReservLabel == pstRevReservState->ucReservLabel))
            {
                pstRevReservState->enIsValid     = PS_FALSE;
                pstRevReservState->ucReservLabel = 0;

                (pstPaAgentCont->stReservMntn.ucRevReervOpenNum)--;

                break;
            }
        }
    }

    return;
}


/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentFwdReservTransferToOpenState
功能描述  : Forward方向的Reservation迁移到OPEN状态
输入参数  : pMsg        Reservation信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentFwdReservTransferToOpenState(VOS_UINT8 *pucReservInfoData)
{
    PA_AGENT_HRPD_CONTEXT_STRU         *pstPaAgentCont;
    VOS_UINT8                           ucReservCnt;
    VOS_UINT8                           ucReservLabel;
    VOS_UINT32                          ulOpenIndx;
    VOS_UINT32                          ulStoreIndx;
    VOS_UINT32                          ulFinalIdleIndx;
    PS_BOOL_ENUM_UINT8                  enIsFindFlag;
    PA_AGENT_HRPD_RESERV_STATE_STRU    *pstFwdReservState;
    PA_AGENT_HRPD_RESERV_STATE_MNTN_STRU *pstReservMntn;

    pstPaAgentCont  = &g_stPaAgentContext;
    pstReservMntn   = &(pstPaAgentCont->stReservMntn);

    /* 取出Reservation数目 */
    PA_AGENT_GETCHAR(ucReservCnt, pucReservInfoData);

    /* 处理每一个Reservation */
    for (ulOpenIndx = 0; ulOpenIndx < ucReservCnt; ulOpenIndx++)
    {
        PA_AGENT_GETCHAR(ucReservLabel, pucReservInfoData)

        /* 遍历查询前设置标志位 */
        enIsFindFlag    = PS_FALSE;
        ulFinalIdleIndx = 0xff;

        /* 找到最后一个空闲的位置，遍历查询是否已经有相同的Label存在 */
        for (ulStoreIndx = 0; ulStoreIndx < PA_AGENT_MAX_RESERVATION_NUM; ulStoreIndx++)
        {
            pstFwdReservState = &(pstReservMntn->astFwdReservState[ulStoreIndx]);

            if (PS_FALSE == pstFwdReservState->enIsValid)
            {
                /* 刷新空闲位置标记 */
                ulFinalIdleIndx = ulStoreIndx;
            }
            else
            {
                if (ucReservLabel == pstFwdReservState->ucReservLabel)
                {
                    /* 已经有相同的Label存在 */
                    enIsFindFlag    = PS_TRUE;
                    break;
                }
            }
        }

        if (PS_FALSE == enIsFindFlag)
        {
            /* 如果遍历一次没有一个空位可供存储，退出 */
            if (0xff == ulFinalIdleIndx)
            {
                PPPC_WARNING_LOG4("No more space to store!\r\n", ulStoreIndx,
                    ulOpenIndx, ucReservCnt, ucReservLabel);
                return;
            }

            /* 没有找到，且还有空位可以填入 */
            pstFwdReservState = &(pstReservMntn->astFwdReservState[ulFinalIdleIndx]);

            pstFwdReservState->enIsValid     = PS_TRUE;
            pstFwdReservState->ucReservLabel = ucReservLabel;
            (pstReservMntn->ucFwdReervOpenNum)++;
        }

        /* 如果已找到，不用插入，continue */
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentFwdReservTransferToCloseState
功能描述  : Forward方向的Reservation迁移到CLOSE状态
输入参数  : pucReservInfoData        Reservation信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentFwdReservTransferToCloseState(VOS_UINT8 *pucReservInfoData)
{
    PA_AGENT_HRPD_CONTEXT_STRU         *pstPaAgentCont;
    VOS_UINT8                           ucReservCnt;
    VOS_UINT8                           ucReservLabel;
    VOS_UINT32                          ulOpenIndx;
    VOS_UINT32                          ulStoreIndx;
    PA_AGENT_HRPD_RESERV_STATE_STRU    *pstFwdReservState;

    pstPaAgentCont = &g_stPaAgentContext;

    /* 取出Reservation数目 */
    PA_AGENT_GETCHAR(ucReservCnt, pucReservInfoData)

    /* 处理每一个Reservation */
    for (ulOpenIndx = 0; ulOpenIndx < ucReservCnt; ulOpenIndx++)
    {
        PA_AGENT_GETCHAR(ucReservLabel, pucReservInfoData)

        /* 找到符合条件的Label，并清除信息 */
        for (ulStoreIndx = 0; ulStoreIndx < PA_AGENT_MAX_RESERVATION_NUM; ulStoreIndx++)
        {
            pstFwdReservState = &(pstPaAgentCont->stReservMntn.astFwdReservState[ulStoreIndx]);

            if ((PS_TRUE == pstFwdReservState->enIsValid)
                && (ucReservLabel == pstFwdReservState->ucReservLabel))
            {
                pstFwdReservState->enIsValid     = PS_FALSE;
                pstFwdReservState->ucReservLabel = 0;

                (pstPaAgentCont->stReservMntn.ucFwdReervOpenNum)--;

                break;
            }
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentCalReservOnMsgBitLen
功能描述  : 计算ReservationOnReq消息的bit长度
输入参数  : 无
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 PPPC_HRPD_PaAgentCalReservOnMsgBitLen
(
    PA_AGENT_HRPD_RESERV_CTRL_STRU     *pstReservInfo
)
{
    VOS_UINT16                          usMsgBitLen;
    /* 包含Msg Id,Transaction Id,Reservation Count3个字段 */
    VOS_UINT16                          usReservMsgHeadByteLen = 3;
    /* 包含ReservationLabel和Linkg共9个bit */
    VOS_UINT16                          usCntBaseBitLen        = 9;


    /* 内部调用，保证指针非空 */

    /* 参考协议C.S0063-A, 2.5.4.4.7ReservationOnReq章节介绍 */

    usMsgBitLen  = (VOS_UINT16)TTF_BYTE2BIT(usReservMsgHeadByteLen);
    usMsgBitLen += (VOS_UINT16)(pstReservInfo->ucReservationCount * usCntBaseBitLen);

    /* 如果是Emergency类型，需要包含Emergency指示 */
    if (0 != pstReservInfo->ucIsEmergencyReserv)
    {
        usMsgBitLen++;
    }

    /* Reservation msg如果不是字节对齐，自动按照向上对齐 */
    usMsgBitLen = ((usMsgBitLen + 7) >> 3) << 3;

    return usMsgBitLen;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentCalReservOffMsgBitLen
功能描述  : 计算ReservationOffReq消息的bit长度
输入参数  : 无
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 PPPC_HRPD_PaAgentCalReservOffMsgBitLen
(
    PA_AGENT_HRPD_RESERV_CTRL_STRU     *pstReservInfo
)
{
    VOS_UINT16                          usMsgBitLen;
    /* 包含Msg Id,Transaction Id,Reservation Count3个字段 */
    VOS_UINT16                          usReservMsgHeadByteLen   = 3;
    /* 包含ReservationLabel和Linkg共9个bit */
    VOS_UINT16                          usCntBaseBitLen         = 9;


    /* 内部调用，保证指针非空 */

    /* 参考协议C.S0063-A, 2.5.4.4.8ReservationOffReq章节介绍 */

    usMsgBitLen  = (VOS_UINT16)TTF_BYTE2BIT(usReservMsgHeadByteLen);
    usMsgBitLen += (VOS_UINT16)(pstReservInfo->ucReservationCount * usCntBaseBitLen);

    /* Reservation msg如果不是字节对齐，自动按照向上对齐 */
    usMsgBitLen = ((usMsgBitLen + 7) >> 3) << 3;

    return usMsgBitLen;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentSetReservLabelField
功能描述  : 填充reservation label域和link域
输入参数  : pucData         数据
            pstReservInfo   应用信息
输出参数  : 无
返 回 值  : VOS_UINT8       bit偏移信息
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 PPPC_HRPD_PaAgentSetReservLabelField
(
    VOS_UINT8                              *pucData,
    PA_AGENT_HRPD_RESERV_CTRL_STRU         *pstReservInfo
)
{
    VOS_UINT8                           ucOffset = 0;
    VOS_UINT8                           ucSubOffset = 0;
    VOS_UINT32                          ulIndx;
    VOS_UINT8                           ucLink;
    VOS_UINT8                           ucReservLabel;
    VOS_UINT32                          ulTempData;

    /* 内部调用，保证指针非空 */

    /* 循环填充每一个Reservation */
    for (ulIndx = 0; ulIndx < pstReservInfo->ucReservationCount; ulIndx++)
    {
        /* 取出link域并放入码流 */
        ucLink = pstReservInfo->astReservInfo[ulIndx].ucLink;

        ucSubOffset = (VOS_UINT8)(PA_AGENT_MOVE_7_BIT - ucOffset);

        if (PS_TRUE == ucLink)
        {
            ulTempData = *pucData;
            TTF_SET_A_BIT(ulTempData, ucSubOffset);
            *pucData = (VOS_UINT8)ulTempData;
        }
        else
        {
            TTF_CLEAR_A_BIT(*pucData, ucSubOffset);
        }

        ucOffset  = (ucOffset + 1) % PA_AGENT_8_BIT;

        /* 取出Label域并放入码流 */
        ucReservLabel = pstReservInfo->astReservInfo[ulIndx].ucReservLabel;

        if (0 == ucOffset)
        {
            /* 如果刚好在字节边界，直接队reservation label复制 */
            pucData++;
            *pucData = ucReservLabel;
            pucData++;
        }
        else
        {
            /* 不在字节对齐的边界，先把label右移填充上一个字节，再左移填充下一个字节 */
            /* reservation label的长度是8字节，偏移之后此处必然被拆到两个字节中 */
            (*pucData) |= (ucReservLabel >> ucOffset);
            pucData++;
            (*pucData) |= (VOS_UINT8)((VOS_UINT32)ucReservLabel << (PA_AGENT_8_BIT - ucOffset));
        }
    }

    return ucOffset;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentGetReservLabelInof
功能描述  : PA AGENT提取Reservation信息
输入参数  : pucData          原始数据,从ReservationCount开始
            pstReservInfo    APP信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_HRPD_PaAgentGetReservLabelInof
(
    VOS_UINT8                          *pucData,
    PA_AGENT_HRPD_RESERV_INFO_STRU     *pstReservInfo
)
{
    VOS_UINT8                           ucBitOffset     = 0;
    VOS_UINT8                           ucMoveOffset    = 0;
    VOS_UINT8                           ucResvCnt       = 0;
    VOS_UINT8                           ucLink;
    VOS_UINT32                          ulIndx;
    VOS_UINT32                          ulRevIndx = 0;
    VOS_UINT32                          ulFwdIndx = 0;


    if ((VOS_NULL_PTR == pucData) || (VOS_NULL_PTR == pstReservInfo))
    {
        PPPC_WARNING_LOG("Input param is null!\r\n");
        return VOS_ERR;
    }

    PA_AGENT_GETCHAR(ucResvCnt, pucData)

    if (0 == ucResvCnt)
    {
        PPPC_WARNING_LOG1("Resv num is 0!\r\n", ucResvCnt);
        return VOS_ERR;
    }

    for (ulIndx = 0; ulIndx < ucResvCnt; ulIndx++)
    {
        ucBitOffset = TTF_MOD_GET(ucBitOffset, PA_AGENT_8_BIT);

        ucMoveOffset = PA_AGENT_MOVE_7_BIT - ucBitOffset;

        ucLink = TTF_GET_A_BIT(*pucData, ucMoveOffset);
        ucBitOffset++;
        if (PA_AGENT_REV_LINK == ucLink)
        {
            (pstReservInfo->ucRevResvCnt)++;
            pstReservInfo->aucRevReservLabel[ulRevIndx]
                = (VOS_UINT8)(((VOS_UINT32)(*pucData) << ucBitOffset) | (*(pucData+1) >> (PA_AGENT_8_BIT - ucBitOffset)));

            ulRevIndx++;
        }
        else
        {
            (pstReservInfo->ucFwdResvCnt)++;
            pstReservInfo->aucFwdReservLabel[ulFwdIndx]
                = (VOS_UINT8)(((VOS_UINT32)(*pucData) << ucBitOffset) | (*(pucData+1) >> (PA_AGENT_8_BIT - ucBitOffset)));

            ulFwdIndx++;
        }

        if (PA_AGENT_8_BIT > ucBitOffset)
        {
            pucData += 1;
        }
        else
        {
            pucData += 2;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentResvStateTrans
功能描述  : 根据从ReservationReject消息中过滤出的信息迁移状态
输入参数  : ulMsgBufferIndx    储存的消息位置
            pstResvInfo        消息中的Reservation信息
            enMsgType          On/Off消息
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentResvStateTrans
(
    VOS_UINT32                              ulMsgBufferIndx,
    PA_AGENT_HRPD_RESERV_INFO_STRU         *pstResvInfo,
    PA_AGENT_HRPD_RESERVATION_MSG_TYPE_ENUM_UINT8 enMsgType
)
{
    VOS_UINT32                          ulFwdAllocLen;
    VOS_UINT32                          ulRevAllocLen;
    VOS_UINT8                          *pucFwdResvData  = VOS_NULL_PTR;
    VOS_UINT8                          *pucRevResvData  = VOS_NULL_PTR;
    VOS_UINT8                          *pucDataOp       = VOS_NULL_PTR;


    if (0 != pstResvInfo->ucFwdResvCnt)
    {
        /* ReservationLabel的个数再加上1个字节的ReservationCount */
        ulFwdAllocLen  = pstResvInfo->ucFwdResvCnt + 1;

        pucFwdResvData = PS_MEM_ALLOC(MSPS_PID_PA_AGENT, ulFwdAllocLen);
        if (VOS_NULL_PTR != pucFwdResvData)
        {
            *pucFwdResvData = pstResvInfo->ucFwdResvCnt;
            PS_MEM_CPY(pucFwdResvData + 1, pstResvInfo->aucFwdReservLabel,
                pstResvInfo->ucFwdResvCnt);
            pucDataOp = pucFwdResvData;

            if (PA_AGENT_HRPD_RESERVATION_ON_REQ == enMsgType)
            {
                PPPC_HRPD_PaAgentFwdReservTransferToOpenState(pucDataOp);
            }
            else if (PA_AGENT_HRPD_RESERVATION_OFF_REQ == enMsgType)
            {
                PPPC_HRPD_PaAgentFwdReservTransferToCloseState(pucDataOp);
            }
            else
            {
                PPPC_WARNING_LOG1("Invalid msg type!\r\n", enMsgType);
            }

            PS_MEM_FREE(MSPS_PID_PA_AGENT, pucFwdResvData);
        }
        else
        {
            PPPC_WARNING_LOG("Alloc mem fail!\r\n");
        }
    }

    if (0 != pstResvInfo->ucRevResvCnt)
    {
        /* ReservationLabel的个数再加上1个字节的ReservationCount */
        ulRevAllocLen  = pstResvInfo->ucRevResvCnt + 1;

        pucRevResvData = PS_MEM_ALLOC(MSPS_PID_PA_AGENT, ulRevAllocLen);
        if (VOS_NULL_PTR != pucRevResvData)
        {
            *pucRevResvData = pstResvInfo->ucRevResvCnt;
            PS_MEM_CPY(pucRevResvData + 1, pstResvInfo->aucRevReservLabel,
                pstResvInfo->ucRevResvCnt);
            pucDataOp = pucRevResvData;

            if (PA_AGENT_HRPD_RESERVATION_ON_REQ == enMsgType)
            {
                PPPC_HRPD_PaAgentRevReservTransferToOpenState(pucDataOp);
            }
            else if (PA_AGENT_HRPD_RESERVATION_OFF_REQ == enMsgType)
            {
                PPPC_HRPD_PaAgentRevReservTransferToCloseState(pucDataOp);
            }
            else
            {
                PPPC_WARNING_LOG1("Invalid msg type!\r\n", enMsgType);
            }

            PS_MEM_FREE(MSPS_PID_PA_AGENT, pucRevResvData);
        }
        else
        {
            PPPC_WARNING_LOG("Alloc mem fail!\r\n");
        }
    }
}
/*lint -e593*/
/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentSndReservOnReq
功能描述  : PA AGENT调用PA提供的接口发送ReservationOnReq到SNP
输入参数  : pstReservInfo    APP信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentSndReservOnReq
(
    PA_AGENT_HRPD_RESERV_CTRL_STRU     *pstReservInfo
)
{
    SNPITF_MSG_DATA_STRU               *pstMsgData;
    VOS_UINT8                          *pucMsgData;
    VOS_UINT8                           ucOffset;
    VOS_UINT8                           ucSubOffset = 0;
    VOS_UINT16                          usAllocLen;
    VOS_UINT16                          usReservOnReqBitLen;
    VOS_UINT32                          ulIndx;
    VOS_UINT32                          ulTempData;


    if (VOS_NULL_PTR == pstReservInfo)
    {
        PPPC_WARNING_LOG("Input parameter is null!\r\n");
        return;
    }

    usReservOnReqBitLen   = PPPC_HRPD_PaAgentCalReservOnMsgBitLen(pstReservInfo);

    if (TTF_BIT2BYTE(usReservOnReqBitLen)
        >= (sizeof(SNPITF_MSG_DATA_STRU) - PA_AGENT_SNP_MSG_DATA_OFFSET_LEN))
    {
        usAllocLen        = TTF_BIT2BYTE(usReservOnReqBitLen) + PA_AGENT_SNP_MSG_DATA_OFFSET_LEN;
    }
    else
    {
        usAllocLen        = sizeof(SNPITF_MSG_DATA_STRU);
    }

    pstMsgData            = PS_MEM_ALLOC(MSPS_PID_PA_AGENT, usAllocLen);
    if (VOS_NULL_PTR == pstMsgData)
    {
        PPPC_WARNING_LOG("No memory to alloc!\r\n");
        return;
    }

    PS_MEM_SET(pstMsgData, 0, usAllocLen);
    pucMsgData  = pstMsgData->aucMsgData;

    /* C.S0063-A, 2.5.4.4.7 ReservationOnReq */

    pstMsgData->usMsgBitLen = usReservOnReqBitLen;

    /* 填充msg id */
    PA_AGENT_PUTCHAR(PA_AGENT_HRPD_RESERVATION_ON_REQ, pucMsgData)

    /* 填充transaction id */
    PA_AGENT_PUTCHAR(g_stPaAgentContext.ucReservTransacId, pucMsgData)

    /* 填充reservation count */
    PA_AGENT_PUTCHAR(pstReservInfo->ucReservationCount, pucMsgData);

    /* 填充reservation label域和link域 */
    ucOffset = PPPC_HRPD_PaAgentSetReservLabelField(pucMsgData, pstReservInfo);

    /* 填充emergency域 */
    if (0 != pstReservInfo->ucIsEmergencyReserv)
    {
        ucSubOffset = (VOS_UINT8)(PA_AGENT_MOVE_7_BIT - ucOffset);
        ulTempData  = *pucMsgData;
        TTF_SET_A_BIT(ulTempData, ucSubOffset);
        *pucMsgData = (VOS_UINT8)ulTempData;
    }

    for (ulIndx = 0; ulIndx < PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM; ulIndx++)
    {
        if (PS_FALSE == g_stPaAgentContext.astReservMsgBuff[ulIndx].enIsValid)
        {
            g_stPaAgentContext.astReservMsgBuff[ulIndx].enIsValid = PS_TRUE;
            g_stPaAgentContext.astReservMsgBuff[ulIndx].ucTimerId = (VOS_UINT8)ulIndx;
            g_stPaAgentContext.astReservMsgBuff[ulIndx].pucMsgDataPtr = (VOS_UINT8 *)pstMsgData;

            break;
        }
    }

    if (PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM <= ulIndx)
    {
        PPPC_WARNING_LOG("Can't add more timer!\r\n");
        (VOS_VOID)pstMsgData;
        return;
    }

    /* CTTF_HRPD_RPA_SendReservationMsgToSnp(pstMsgData); */

    (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(g_stPaAgentContext.astReservMsgBuff[ulIndx].hRlpRespTimer),
                MSPS_PID_PA_AGENT, PA_AGENT_TIMER_RLP_RESPONSE, ulIndx,
                PPPC_HRPD_PA_AGENT_RLP_RSP_TIMER, VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

    /* transaction id域最大为255，使用UINT8类型不需要再取模 */
    g_stPaAgentContext.ucReservTransacId++;
    (VOS_VOID)pstMsgData;
    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentSndReservOffReq
功能描述  : PA AGENT调用PA提供的接口发送ReservationOffReq到SNP
输入参数  : pstReservInfo    APP信息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentSndReservOffReq
(
    PA_AGENT_HRPD_RESERV_CTRL_STRU     *pstReservInfo
)
{
    SNPITF_MSG_DATA_STRU               *pstMsgData;
    VOS_UINT8                          *pucMsgData;
    VOS_UINT16                          usAllocLen;
    VOS_UINT16                          usReservOffReqBitLen;
    VOS_UINT32                          ulIndx;


    if (VOS_NULL_PTR == pstReservInfo)
    {
        PPPC_WARNING_LOG("Input parameter is null!\r\n");
        return;
    }

    usReservOffReqBitLen  = PPPC_HRPD_PaAgentCalReservOffMsgBitLen(pstReservInfo);

    if (TTF_BIT2BYTE(usReservOffReqBitLen)
        >= (sizeof(SNPITF_MSG_DATA_STRU) - PA_AGENT_SNP_MSG_DATA_OFFSET_LEN))
    {
        usAllocLen        = TTF_BIT2BYTE(usReservOffReqBitLen) + PA_AGENT_SNP_MSG_DATA_OFFSET_LEN;
    }
    else
    {
        usAllocLen        = sizeof(SNPITF_MSG_DATA_STRU);
    }

    pstMsgData            = PS_MEM_ALLOC(MSPS_PID_PA_AGENT, usAllocLen);
    if (VOS_NULL_PTR == pstMsgData)
    {
        PPPC_WARNING_LOG("No memory to alloc!\r\n");
        return;
    }

    PS_MEM_SET(pstMsgData, 0, usAllocLen);
    pucMsgData  = pstMsgData->aucMsgData;

    /* C.S0063-A, 2.5.4.4.7 ReservationOnReq */

    pstMsgData->usMsgBitLen = usReservOffReqBitLen;

    /* 填充msg id */
    PA_AGENT_PUTCHAR(PA_AGENT_HRPD_RESERVATION_OFF_REQ, pucMsgData)

    /* 填充transaction id */
    PA_AGENT_PUTCHAR(g_stPaAgentContext.ucReservTransacId, pucMsgData)

    /* 填充reservation count */
    PA_AGENT_PUTCHAR(pstReservInfo->ucReservationCount, pucMsgData);

    /* 填充reservation label域和link域 */
    (VOS_VOID)PPPC_HRPD_PaAgentSetReservLabelField(pucMsgData, pstReservInfo);

    for (ulIndx = 0; ulIndx < PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM; ulIndx++)
    {
        if (PS_FALSE == g_stPaAgentContext.astReservMsgBuff[ulIndx].enIsValid)
        {
            g_stPaAgentContext.astReservMsgBuff[ulIndx].enIsValid = PS_TRUE;
            g_stPaAgentContext.astReservMsgBuff[ulIndx].ucTimerId = (VOS_UINT8)ulIndx;
            g_stPaAgentContext.astReservMsgBuff[ulIndx].pucMsgDataPtr = (VOS_UINT8 *)pstMsgData;

            break;
        }
    }

    if (PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM <= ulIndx)
    {
        PPPC_WARNING_LOG("Can't add more timer!\r\n");
        (VOS_VOID)pstMsgData;
        return;
    }

    /* CTTF_HRPD_RPA_SendReservationMsgToSnp(pstMsgData); */

    (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(g_stPaAgentContext.astReservMsgBuff[ulIndx].hRlpRespTimer),
         MSPS_PID_PA_AGENT, PA_AGENT_TIMER_RLP_RESPONSE, ulIndx,
         PPPC_HRPD_PA_AGENT_RLP_RSP_TIMER, VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

    /* transaction id域最大为255，使用UINT8类型不需要再模 */
    g_stPaAgentContext.ucReservTransacId++;
    (VOS_VOID)pstMsgData;
    return;
}
/*lint +e593*/
/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRcvRevReservOnProc
功能描述  : PA AGENT收到PA的RevReservationOn消息
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRcvRevReservOnProc(VOS_UINT8 *pucData)
{
    VOS_UINT8                          *pucMsgData;
    VOS_UINT8                           ucReservCnt;
    SNPITF_MSG_DATA_STRU                stSnpMsgData;
    PA_AGENT_HRPD_CONTEXT_STRU         *pstPaAgentCont;


    /* 内部调用，保证指针非空 */

    pstPaAgentCont  = &g_stPaAgentContext;

    pucMsgData      = &(pucData[1]);

    PS_MEM_SET(&stSnpMsgData, 0, sizeof(stSnpMsgData));

    stSnpMsgData.aucMsgData[0]  = PA_AGENT_HRPD_RESERVATION_ACCEPT;
    PA_AGENT_GETCHAR(stSnpMsgData.aucMsgData[1], pucMsgData);

    /* AT and AN shall not perform any actions that will result in the number
    of Reverse Link Reservations int open state exceed the value expecified by
    MaxNumOpenReservationsRev.AT and AN shall not perform any actions that will
    result in the number of Forward Link Reservations int open state exceed the
    value expecified by MaxNumOpenReservationsFwd. C.S0063-A,chapter 2.5.4.2.1.1*/

    PA_AGENT_GETCHAR(ucReservCnt, pucMsgData);

    if ((pstPaAgentCont->stReservMntn.ucRevReervOpenNum + ucReservCnt)
        > pstPaAgentCont->stReservMntn.ucMaxNumOpenReservRev)
    {
        PPPC_WARNING_LOG3("Exceed to the max open num!\r\n", ucReservCnt,
                    pstPaAgentCont->stReservMntn.ucRevReervOpenNum,
                    pstPaAgentCont->stReservMntn.ucMaxNumOpenReservRev);
        return;
    }

    /* CTTF_HRPD_RPA_SendReservationMsgToSnp(&stSnpMsgData); */

    PPPC_HRPD_PaAgentRevReservTransferToOpenState(&pucData[2]);

    (VOS_VOID)pucMsgData;
    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRcvRevReservOffProc
功能描述  : PA AGENT收到PA的RevReservationOff消息
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRcvRevReservOffProc(VOS_UINT8 *pucData)
{
    VOS_UINT8                          *pucMsgData;
    SNPITF_MSG_DATA_STRU                stSnpMsgData;


    /* 内部调用，保证指针非空 */

    pucMsgData      = &(pucData[1]);

    PS_MEM_SET(&stSnpMsgData, 0, sizeof(stSnpMsgData));

    stSnpMsgData.aucMsgData[0]  = PA_AGENT_HRPD_RESERVATION_ACCEPT;
    PA_AGENT_GETCHAR(stSnpMsgData.aucMsgData[1], pucMsgData);

    /* CTTF_HRPD_RPA_SendReservationMsgToSnp(&stSnpMsgData); */

    PPPC_HRPD_PaAgentRevReservTransferToCloseState(&pucData[2]);

    (VOS_VOID)pucMsgData;
    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRcvFwdReservOnProc
功能描述  : PA AGENT收到PA的FwdReservationOn消息
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRcvFwdReservOnProc(VOS_UINT8 *pucData)
{
    VOS_UINT8                          *pucMsgData;
    VOS_UINT8                           ucReservCnt;
    SNPITF_MSG_DATA_STRU                stSnpMsgData;
    PA_AGENT_HRPD_CONTEXT_STRU         *pstPaAgentCont;


    /* 内部调用，保证指针非空 */

    pstPaAgentCont  = &g_stPaAgentContext;

    pucMsgData      = &(pucData[1]);

    PS_MEM_SET(&stSnpMsgData, 0, sizeof(stSnpMsgData));

    stSnpMsgData.aucMsgData[0]  = PA_AGENT_HRPD_FWD_RESERVATION_ACK;
    PA_AGENT_GETCHAR(stSnpMsgData.aucMsgData[1], pucMsgData);

    /* AT and AN shall not perform any actions that will result in the number
    of Reverse Link Reservations int open state exceed the value expecified by
    MaxNumOpenReservationsRev.AT and AN shall not perform any actions that will
    result in the number of Forward Link Reservations int open state exceed the
    value expecified by MaxNumOpenReservationsFwd. C.S0063-A,chapter 2.5.4.2.1.1*/

    PA_AGENT_GETCHAR(ucReservCnt, pucMsgData);

    if ((pstPaAgentCont->stReservMntn.ucFwdReervOpenNum + ucReservCnt)
        > pstPaAgentCont->stReservMntn.ucMaxNumOpenReservFwd)
    {
        PPPC_WARNING_LOG3("Exceed to the max open num!\r\n", ucReservCnt,
                    pstPaAgentCont->stReservMntn.ucRevReervOpenNum,
                    pstPaAgentCont->stReservMntn.ucMaxNumOpenReservRev);
        return;
    }

    /* CTTF_HRPD_RPA_SendReservationMsgToSnp(&stSnpMsgData); */

    PPPC_HRPD_PaAgentFwdReservTransferToOpenState(&pucData[2]);

    (VOS_VOID)pucMsgData;
    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRcvFwdReservOffProc
功能描述  : PA AGENT收到PA的FwdReservationOn消息
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRcvFwdReservOffProc(VOS_UINT8 *pucData)
{
    VOS_UINT8                          *pucMsgData;
    SNPITF_MSG_DATA_STRU                stSnpMsgData;


    /* 内部调用，保证指针非空 */

    pucMsgData      = &(pucData[1]);

    PS_MEM_SET(&stSnpMsgData, 0, sizeof(stSnpMsgData));

    stSnpMsgData.aucMsgData[0]  = PA_AGENT_HRPD_FWD_RESERVATION_ACK;
    PA_AGENT_GETCHAR(stSnpMsgData.aucMsgData[1], pucMsgData);

    /* CTTF_HRPD_RPA_SendReservationMsgToSnp(&stSnpMsgData); */

    PPPC_HRPD_PaAgentFwdReservTransferToCloseState(&pucData[2]);

    (VOS_VOID)pucMsgData;
    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRcvReservRejectProc
功能描述  : PA AGENT收到ReservationReject消息处理
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRcvReservRejectProc(VOS_UINT8 *pucData)
{
    VOS_UINT8                           ucNewTransactionId;
    VOS_UINT8                           ucStoredTransactionId;
    VOS_UINT8                          *pucTmpData;

    /* 需要偏移msg id和transaction id共两个字节 */
    VOS_UINT8                           ucResvCntOffset = 2;
    VOS_UINT32                          ulIndx;
    VOS_UINT32                          ulRet;
    PA_AGENT_HRPD_RESERV_INFO_STRU      stRejectReserv;
    PA_AGENT_HRPD_RESERVATION_MSG_TYPE_ENUM_UINT8 enMsgType;
    PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU     *pstMsgBuff;


    PS_MEM_SET((VOS_VOID *)&stRejectReserv, 0x0,
                    sizeof(PA_AGENT_HRPD_RESERV_INFO_STRU));

    ulRet = PPPC_HRPD_PaAgentGetReservLabelInof(pucData + ucResvCntOffset, &stRejectReserv);

    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get reject reserv info fail!\r\n", ulRet);
        return;
    }

    PA_AGENT_GET_TRANSACTION_ID(ucNewTransactionId, pucData)
    for (ulIndx = 0; ulIndx < PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM; ulIndx++)
    {
        /* 获取缓存的消息信息 */
        pstMsgBuff  = &(g_stPaAgentContext.astReservMsgBuff[ulIndx]);
        pucTmpData  = pstMsgBuff->pucMsgDataPtr;

        if ((PS_TRUE == pstMsgBuff->enIsValid) && (VOS_NULL_PTR != pucTmpData))
        {
            PA_AGENT_GETCHAR(enMsgType, pucTmpData)
            PA_AGENT_GETCHAR(ucStoredTransactionId, pucTmpData)

            /* 处理对应的消息:停定时器、清除消息缓存、切状态 */
            if (ucNewTransactionId == ucStoredTransactionId)
            {
                PPPC_HRPD_PaAgentResvStateTrans(ulIndx, &stRejectReserv, enMsgType);

                (VOS_VOID)VOS_StopRelTimer((HTIMER*)&(g_stPaAgentContext.astReservMsgBuff[ulIndx].hRlpRespTimer));

                PS_MEM_FREE(MSPS_PID_PA_AGENT, pstMsgBuff->pucMsgDataPtr);

                PS_MEM_SET(&(g_stPaAgentContext.astReservMsgBuff[ulIndx]), 0,
                sizeof(PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU));

                return;
            }
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRcvReservAcceptProc
功能描述  : PA AGENT收到ReservationAccept消息处理
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRcvReservAcceptProc(VOS_UINT8 *pucData)
{
    VOS_UINT8                           ucNewTransactionId;
    VOS_UINT8                           ucStoredTransactionId;
    VOS_UINT8                          *pucTmpData;
    VOS_UINT32                          ulIndx;
    VOS_UINT32                          ulRet;
    PA_AGENT_HRPD_RESERVATION_MSG_TYPE_ENUM_UINT8 enMsgType;
    PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU     *pstMsgBuff;
    PA_AGENT_HRPD_RESERV_INFO_STRU                stReservInfo;


    PA_AGENT_GET_TRANSACTION_ID(ucNewTransactionId, pucData)
    for (ulIndx = 0; ulIndx < PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM; ulIndx++)
    {
        /* 获取缓存的消息信息 */
        pstMsgBuff  = &(g_stPaAgentContext.astReservMsgBuff[ulIndx]);
        pucTmpData  = pstMsgBuff->pucMsgDataPtr;

        if ((PS_TRUE == pstMsgBuff->enIsValid) && (VOS_NULL_PTR != pucTmpData))
        {
            PA_AGENT_GETCHAR(enMsgType, pucTmpData)
            PA_AGENT_GETCHAR(ucStoredTransactionId, pucTmpData)

            /* 处理对应的消息:停定时器、清除消息缓存、切状态 */
            if (ucNewTransactionId == ucStoredTransactionId)
            {
                PS_MEM_SET((VOS_VOID *)&stReservInfo, 0x0,
                    sizeof(PA_AGENT_HRPD_RESERV_INFO_STRU));

                ulRet = PPPC_HRPD_PaAgentGetReservLabelInof(pucTmpData, &stReservInfo);

                if (VOS_OK != ulRet)
                {
                    PPPC_WARNING_LOG1("Get sent reserv info fail!\r\n", ulRet);
                }
                else
                {
                    PPPC_HRPD_PaAgentResvStateTrans(ulIndx, &stReservInfo, enMsgType);
                }

                (VOS_VOID)VOS_StopRelTimer((HTIMER *)&(g_stPaAgentContext.astReservMsgBuff[ulIndx].hRlpRespTimer));

                PS_MEM_FREE(MSPS_PID_PA_AGENT, pstMsgBuff->pucMsgDataPtr);

                PS_MEM_SET(&(g_stPaAgentContext.astReservMsgBuff[ulIndx]), 0,
                sizeof(PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU));

                return;
            }
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HRPD_PaAgentRcvReservDlMsgProc
功能描述  : PA AGENT收到PA的下行消息处理
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentRcvReservDlMsgProc(struct MsgCB * pMsg)
{
    PA_AGENT_HRPD_RESERVATION_MSG_TYPE_ENUM_UINT8   enMsgType;
    CTTF_PPP_HRPD_RESERVATION_DL_MSG_STRU          *pstReservDlMsg;
    VOS_UINT8                                       ucResvCnt;


    pstReservDlMsg  = (CTTF_PPP_HRPD_RESERVATION_DL_MSG_STRU *)pMsg;
    enMsgType       = pstReservDlMsg->aucData[0];

    if (PA_AGENT_HRPD_RESERVATION_ACCEPT != enMsgType)
    {
        PA_AGENT_GET_RESERVATION_COUNT(ucResvCnt, pstReservDlMsg->aucData);
        if (pstReservDlMsg->usMsgLen < PA_AGENT_DL_RESERV_MSG_LEN(ucResvCnt))
        {
            PPPC_WARNING_LOG2("Invalid msg length!\r\n",
                pstReservDlMsg->usMsgLen, ucResvCnt);
            return;
        }
    }

    switch (enMsgType)
    {
        case PA_AGENT_HRPD_REV_RESERVATION_ON:

            PPPC_HRPD_PaAgentRcvRevReservOnProc(pstReservDlMsg->aucData);

            break;

        case PA_AGENT_HRPD_REV_RESERVATION_OFF:

            PPPC_HRPD_PaAgentRcvRevReservOffProc(pstReservDlMsg->aucData);

            break;

        case PA_AGENT_HRPD_FWD_RESERVATION_ON:

            PPPC_HRPD_PaAgentRcvFwdReservOnProc(pstReservDlMsg->aucData);

            break;

        case PA_AGENT_HRPD_FWD_RESERVATION_OFF:

            PPPC_HRPD_PaAgentRcvFwdReservOffProc(pstReservDlMsg->aucData);

            break;

        case PA_AGENT_HRPD_RESERVATION_ACCEPT:

            PPPC_HRPD_PaAgentRcvReservAcceptProc(pstReservDlMsg->aucData);

            break;

        case PA_AGENT_HRPD_RESERVATION_REJECT:

            PPPC_HRPD_PaAgentRcvReservRejectProc(pstReservDlMsg->aucData);

            break;

        default:

            PPPC_WARNING_LOG1("RLP timer name is invalid!\r\n", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_HrpdPaAgentRcvOpenReservProc
功能描述  : PA AGENT收到PA的Open Reservation指示
输入参数  : pMsg    发自PA的Reservation消息
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-06-03
作    者   : c00184031
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_HrpdPaAgentRcvOpenReservProc(struct MsgCB * pMsg)
{
    CTTF_PPP_HRPD_OPEN_RESERVATION_IND_STRU    *pstResvOpenInd;
    VOS_UINT8                                  *pucData;
    VOS_UINT32                                  ulAllocLen;
    VOS_UINT32                                  ulIndx;
    PA_AGENT_HRPD_RESERV_STATE_MNTN_STRU       *pstResvInfo;


    pstResvInfo     = &g_stPaAgentContext.stReservMntn;


    pstResvOpenInd  = (CTTF_PPP_HRPD_OPEN_RESERVATION_IND_STRU *)pMsg;

    /* 超过能Open的上限，啥也不做 */
    if ((pstResvOpenInd->ucNumRevReservToOpen + pstResvInfo->ucRevReervOpenNum)
        > pstResvInfo->ucMaxNumOpenReservRev)
    {
        PPPC_WARNING_LOG3("Can't open more resv!\r\n", pstResvOpenInd->ucNumRevReservToOpen,
            pstResvInfo->ucRevReervOpenNum, pstResvInfo->ucMaxNumOpenReservRev);

        return;
    }

    ulAllocLen  = pstResvOpenInd->ucNumRevReservToOpen + 1;

    pucData = PS_MEM_ALLOC(MSPS_PID_PA_AGENT, ulAllocLen);
    if (VOS_NULL_PTR == pucData)
    {
        PPPC_WARNING_LOG("Alloc mem fail!\r\n");
        return;
    }

    /* 构造状态迁移函数的入参 */
    *pucData  = pstResvOpenInd->ucNumRevReservToOpen;
    for (ulIndx = 1; ulIndx <= pstResvOpenInd->ucNumRevReservToOpen; ulIndx++)
    {
        *(pucData + ulIndx) = pstResvOpenInd->aucRevReservationLabel[ulIndx - 1];
    }

    PPPC_HRPD_PaAgentRevReservTransferToOpenState(pucData);

    PS_MEM_FREE(MSPS_PID_PA_AGENT, pucData);

    return;
}

 /*****************************************************************************
 函 数 名  : PPPC_HrpdPaAgentRcvCloseReservProc
 功能描述  : PA AGENT收到PA的Close Reservation指示
 输入参数  : pMsg    发自PA的Reservation消息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015-06-03
 作    者   : c00184031
 修改内容   : 新生成函数
 *****************************************************************************/
 VOS_VOID PPPC_HrpdPaAgentRcvCloseReservProc(struct MsgCB * pMsg)
 {
     CTTF_PPP_HRPD_CLOSE_RESERVATIONS_IND_STRU  *pstResvCloseInd;
     VOS_UINT8                                  *pucData;
     VOS_UINT32                                  ulAllocLen;
     VOS_UINT32                                  ulIndx;


     pstResvCloseInd = (CTTF_PPP_HRPD_CLOSE_RESERVATIONS_IND_STRU *)pMsg;

     ulAllocLen  = pstResvCloseInd->ucNumRevReservToClose + 1;

     pucData = PS_MEM_ALLOC(MSPS_PID_PA_AGENT, ulAllocLen);
     if (VOS_NULL_PTR == pucData)
     {
         PPPC_WARNING_LOG("Alloc mem fail!\r\n");
         return;
     }

     /* 构造状态迁移函数的入参 */
     *pucData  = pstResvCloseInd->ucNumRevReservToClose;
     for (ulIndx = 1; ulIndx <= pstResvCloseInd->ucNumRevReservToClose; ulIndx++)
     {
         *(pucData + ulIndx) = pstResvCloseInd->aucRevReservationLabel[ulIndx - 1];
     }

     PPPC_HRPD_PaAgentRevReservTransferToCloseState(pucData);

     PS_MEM_FREE(MSPS_PID_PA_AGENT, pucData);

     return;
 }


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
