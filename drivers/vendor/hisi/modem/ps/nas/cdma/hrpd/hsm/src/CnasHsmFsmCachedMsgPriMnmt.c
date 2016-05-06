

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmFsmCachedMsgPriMnmt.h"
#include "hsm_hsd_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_FSM_CACHED_MSG_PRI_MNMT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/
CNAS_HSM_MSG_PRI_STRU g_astCnasHsmFsmCachedMsgPriTbl[] =
{
    /* 最高优先级消息 */
    CNAS_HSM_MSG_PRI_TBL_ITEM( UEPS_PID_HSD,
                               ID_HSD_HSM_SUSPEND_IND,
                               CNAS_HSM_MSG_PRI_LVL_0 ),

    CNAS_HSM_MSG_PRI_TBL_ITEM( UEPS_PID_HSD,
                               ID_HSD_HSM_POWEROFF_REQ,
                               CNAS_HSM_MSG_PRI_LVL_0 ),

    CNAS_HSM_MSG_PRI_TBL_ITEM( UEPS_PID_HSD,
                               ID_HSD_HSM_POWER_SAVE_REQ,
                               CNAS_HSM_MSG_PRI_LVL_0 ),

    CNAS_HSM_MSG_PRI_TBL_ITEM( UEPS_PID_HSD,
                               ID_HSD_HSM_RESUME_IND,
                               CNAS_HSM_MSG_PRI_LVL_0 ),

    /* 默认为最低优先级 CNAS_HSM_MSG_PRI_LVL_2 */
};

/*****************************************************************************
  3 Function Define
*****************************************************************************/

CNAS_HSM_MSG_PRI_ENUM_UINT8 CNAS_HSM_FindMsgPri(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usSize;
    CNAS_HSM_MSG_PRI_ENUM_UINT8         enMsgPri;

    /* 优先级表中找不到则为最低优先级 */
    enMsgPri = CNAS_HSM_MSG_PRI_LVL_2;

    usSize = sizeof(g_astCnasHsmFsmCachedMsgPriTbl) / sizeof(CNAS_HSM_MSG_PRI_STRU);

    for (usLoop = 0 ; usLoop < usSize ; usLoop++)
    {
        if (g_astCnasHsmFsmCachedMsgPriTbl[usLoop].ulEventType == ulEventType)
        {
            enMsgPri = g_astCnasHsmFsmCachedMsgPriTbl[usLoop].enMsgPri;
        }
    }

    return enMsgPri;

}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
