

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafMmaFsmSysCfgTbl.h"
#include "TafMmaFsmSysCfg.h"
#include "TafAppMma.h"
#include "TafMmaSndInternalMsg.h"
#include "MmaMsccInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_MMA_FSM_SYS_CFG_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

TAF_FSM_DESC_STRU                       g_stTafMmaSysCfgFsmDesc;

/* TAF_MMA_SYS_CFG_STA_INIT 动作表 */
TAF_ACT_STRU        g_astTafMmaSysCfgInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYS_CFG_SET_REQ,
                      TAF_MMA_RcvSysCfgSetReq_SysCfg_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_SYS_CFG_SET_REQ,
                      TAF_MMA_RcvInterSysCfgSetReq_SysCfg_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ATTACH_REQ,
                      TAF_MMA_RcvAttachReq_SysCfg_Init),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_DETACH_REQ,
                      TAF_MMA_RcvDetachReq_SysCfg_Init),
};

/* TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF 动作表 */
TAF_ACT_STRU        g_astTafMmaSysCfgWaitDetachCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DETACH_CNF,
                      TAF_MMA_RcvDetachCnf_SysCfg_WaitDetachCnf),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_DETACH_CNF,
                      TAF_MMA_RcvTiWaitDetachCnfExpired_SysCfg_WaitDetachCnf),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_ABORT_IND,
                      TAF_MMA_RcvAbortInd_SysCfg_WaitDetachCnf),
};


/* TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF 动作表 */
TAF_ACT_STRU        g_astTafMmaSysCfgWaitAttachCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ATTACH_CNF,
                      TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF,
                      TAF_MMA_RcvTiWaitAttachCnfExpired_SysCfg_WaitAttachCnf),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_ABORT_IND,
                      TAF_MMA_RcvAbortInd_SysCfg_WaitAttachCnf),
};


/* TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF 动作表 */
TAF_ACT_STRU        g_astTafMmaSysCfgWaitSysCfgCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SYS_CFG_CNF,
                      TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF,
                      TAF_MMA_RcvTiWaitSysCfgCnfExpired_SysCfg_WaitSysCfgCnf),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_ABORT_IND,
                      TAF_MMA_RcvAbortInd_SysCfg_WaitSysCfgCnf),
};


/* SYS CFG状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafMmaSysCfgStaTbl[]   =
{
    /* SYS CFG状态机的初始化状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_SYS_CFG_STA_INIT,
                      g_astTafMmaSysCfgInitActTbl ),

    /* SYS CFG状态机的初始化状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF,
                      g_astTafMmaSysCfgWaitDetachCnfActTbl ),

    /* SYS CFG状态机的初始化状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF,
                      g_astTafMmaSysCfgWaitAttachCnfActTbl ),

    /* SYS CFG状态机的初始化状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF,
                      g_astTafMmaSysCfgWaitSysCfgCnfActTbl ),


};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


VOS_UINT32 TAF_MMA_GetSysCfgStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafMmaSysCfgStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_MMA_GetSysCfgFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaSysCfgFsmDesc);
}


/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */






