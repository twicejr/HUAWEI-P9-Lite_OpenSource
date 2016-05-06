/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmSwitchOnTbl.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月12日
  功能描述   : HRPD L2开机状态机事件函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasHsdFsmSwitchOn.h"
#include "CnasHsdFsmSwitchOnTbl.h"
#include "CnasHsdComFunc.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "hsm_hsd_pif.h"
#include "UsimPsInterface.h"
#include "hsd_hlu_pif.h"
#include "ehsm_hsd_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_SWITCH_ON_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS HSD状态机数组:开机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasHsdSwitchOnFsmDesc;

/* CNAS_HSD_SWITCH_ON_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasHsdSwitchOnInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvMsccStartReq_SwitchOn_Init),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvMsccStartReq_SwitchOn_Init),
};

/* CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdSwitchOnWaitCardFileCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_HSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CARD_FILE_CNF,
                      CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf)
};

/* CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdSwitchOnWaitCasStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_START_CNF,
                      CNAS_HSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_START_CNF,
                      CNAS_HSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf)
};

/* CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdSwitchOnWaitHsmStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_START_CNF,
                      CNAS_HSD_RcvHsmStartCnf_SwitchOn_WaitHsmStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HSM_START_CNF,
                      CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf)
};

/* CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdSwitchOnWaitEhsmStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSD_START_CNF,
                      CNAS_HSD_RcvEhsmStartCnf_SwitchOn_WaitEhsmStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_EHSM_START_CNF,
                      CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf)
};

/* CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF动作表 */
NAS_ACT_STRU g_astCnasHsdSwitchOnWaitHluStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HLU,
                      ID_HLU_HSD_START_CNF,
                      CNAS_HSD_RcvHluStartCnf_SwitchOn_WaitHluStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HLU_START_CNF,
                      CNAS_HSD_RcvTiHluStartCnfExpired_SwitchOn_WaitHluStartCnf)
};

/* 开机状态机消息 状态表 */
NAS_STA_STRU g_astCnasHsdSwitchOnStaTbl[] =
{
    /*****************定义开机初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SWITCH_ON_STA_INIT,
                      g_astCnasHsdSwitchOnInitActTbl),

    /*****************定义等待卡文件信息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF,
                      g_astCnasHsdSwitchOnWaitCardFileCnfActTbl ),

    /*****************定义等待CAS开机结果消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF,
                      g_astCnasHsdSwitchOnWaitCasStartCnfActTbl),

    /*****************定义等待HSM开机结果消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF,
                      g_astCnasHsdSwitchOnWaitHsmStartCnfActTbl),

    /*****************定义等待HSM开机结果消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF,
                      g_astCnasHsdSwitchOnWaitEhsmStartCnfActTbl),

    /*****************定义等待HLU开机结果消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF,
                      g_astCnasHsdSwitchOnWaitHluStartCnfActTbl),
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSwitchOnStaTblSize
 功能描述  : 获取开机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:开机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetSwitchOnStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSwitchOnFsmDescAddr
 功能描述  : 获取开机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向开机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdSwitchOnFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



