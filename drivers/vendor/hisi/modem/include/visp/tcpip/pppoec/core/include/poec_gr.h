/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poec_gr.h
*
*  Project Code: VISP V100R008C02
*   Module Name: PPPOE
*  Date Created: 2010-01-14
*        Author: z00104207
*   Description: 本文件涉及协议保活处理相关的一些定义和声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-01-14   z00104207               Create
*
*******************************************************************************/
#ifndef _POEC_GR_H_
#define _POEC_GR_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* PPPOE的保活状态 */
enum enumPOEC_GR_STATE
{
    POEC_GR_STATE_NORMAL,       /* 0 正常状态 */
    POEC_GR_STATE_SMOOTHING,    /* 1 正在进行平滑处理, 平滑处理完毕后直接进入 0 正常状态 */
    POEC_GR_STATE_RESTORED,     /* 2 已经完成恢复处理, 等待平滑处理 */
    POEC_GR_STATE_RESTORING,    /* 3 正在进行恢复处理 */
    POEC_GR_STATE_KEEPALIVE,    /* 4 保活状态, 等待恢复处理 */
};

typedef enum tagPOEC_DEBUG_TYPE
{
    POEC_GR_DEBUG_DIALERIF_NULL,    /* */
    POEC_GR_DEBUG_ETHIF_STATE,      /* */
    POEC_GR_DEBUG_MODE,             /* */
    POEC_GR_DEBUG_NEGO_CFG,         /* */
    POEC_GR_DEBUG_NEGO_GOT,         /* */
    POEC_GR_DEBUG_GETINFO,          /* */
    POEC_GR_DEBUG_MAC_INVALID,      /* */
    POEC_GR_DEBUG_MAC_DIFF,         /* */
    POEC_GR_DEBUG_CB_NULL,          /* */
    POEC_GR_DEBUG_SESSION_EXIST,    /* */
    POEC_GR_DEBUG_CREATE_VA_FAIL,   /* */
    POEC_GR_DEBUG_ENCAP_VA_FAIL,    /* */
    POEC_GR_DEBUG_NO_PPPINFO,       /* */
    POEC_GR_DEBUG_PPP_NORMAL,       /* */
}POEC_DEBUG_TYPE_E;

extern VOID PPP_GR_DealMsg(UINTPTR aulMsg[4]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _POEC_GR_H_ */

