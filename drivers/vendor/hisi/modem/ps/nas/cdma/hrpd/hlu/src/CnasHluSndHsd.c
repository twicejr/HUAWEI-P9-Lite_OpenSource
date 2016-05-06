/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluSndHsd.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年12月16日
  最近修改   :
  功能描述   : HLU发送给HSD的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : Y00213812
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "hsd_hlu_pif.h"
#include "PsCommonDef.h"
#include "CnasHluComm.h"
#include "CnasMain.h"
#include "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_SND_HSD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_HLU_SndHsdStartCnf(VOS_VOID)
{
    HLU_HSD_START_CNF_STRU *pstInternalMsg;

#if defined(DMT)
    pstInternalMsg = (HLU_HSD_START_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU,
                                                sizeof(HLU_HSD_START_CNF_STRU));
#else
    /* alloc message memory*/
    pstInternalMsg = (HLU_HSD_START_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HLU,
                                                sizeof(HLU_HSD_START_CNF_STRU));
#endif

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_SndHsdStartCnf:memory allocation failure.");
        return;
    }

    NAS_MEM_SET_S((VOS_VOID*)pstInternalMsg, sizeof(HLU_HSD_START_CNF_STRU), 0, sizeof(HLU_HSD_START_CNF_STRU));

    CNAS_HLU_FILL_MSG_HDR(pstInternalMsg, UEPS_PID_HLU, UEPS_PID_HSD);

    /* set message */
    pstInternalMsg->enMsgId             = ID_HLU_HSD_START_CNF;
    pstInternalMsg->ulLength            = sizeof(HLU_HSD_START_CNF_STRU)
                                            - VOS_MSG_HEAD_LENGTH;

#if defined (DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstInternalMsg);
#else
    /* send message */
    (VOS_VOID)CNAS_SndInternalMsg(pstInternalMsg);
#endif

    return;
}



VOS_VOID CNAS_HLU_SndHsdPowerOffCnf(VOS_VOID)
{
    HLU_HSD_POWER_OFF_CNF_STRU *pstInternalMsg;

#if defined(DMT)
    pstInternalMsg = (HLU_HSD_POWER_OFF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU,
                                            sizeof(HLU_HSD_POWER_OFF_CNF_STRU));
#else
    /* alloc message memory*/
    pstInternalMsg = (HLU_HSD_POWER_OFF_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HLU,
                                            sizeof(HLU_HSD_POWER_OFF_CNF_STRU));
#endif

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_SndHsdPowerOffCnf:memory allocation failure.");
        return;
    }

    NAS_MEM_SET_S((VOS_VOID*)pstInternalMsg, sizeof(HLU_HSD_POWER_OFF_CNF_STRU), 0, sizeof(HLU_HSD_POWER_OFF_CNF_STRU));

    CNAS_HLU_FILL_MSG_HDR(pstInternalMsg, UEPS_PID_HLU, UEPS_PID_HSD);

    /* set message */
    pstInternalMsg->enMsgId             = ID_HLU_HSD_POWER_OFF_CNF;
    pstInternalMsg->ulLength            = sizeof(HLU_HSD_POWER_OFF_CNF_STRU)
                                            - VOS_MSG_HEAD_LENGTH;

#if defined (DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HLU, pstInternalMsg);
#else
    /* send message */
    (VOS_VOID)CNAS_SndInternalMsg(pstInternalMsg);
#endif

    return;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



