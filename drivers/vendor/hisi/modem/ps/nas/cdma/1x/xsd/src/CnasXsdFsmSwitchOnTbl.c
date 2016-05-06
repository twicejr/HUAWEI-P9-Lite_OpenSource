/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmSwitchOnTbl.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年07月03日
  功能描述   : 1X SD L2开机状态机事件函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXsdFsmSwitchOn.h"
#include "CnasXsdFsmSwitchOnTbl.h"
#include "CnasXsdComFunc.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "xsd_xcc_pif.h"
#include "UsimPsInterface.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SWITCH_ON_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XSD状态机数组:开机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasXsdSwitchOnFsmDesc;

/* CNAS_XSD_SWITCH_ON_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasXsdSwitchOnInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvMsccStartReq_SwitchOn_Init),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvMsccStartReq_SwitchOn_Init),
};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitCardFileCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_XSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CARD_FILE_CNF,
                      CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf)

};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitXccStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_XSD_START_CNF,
                      CNAS_XSD_RcvXccStartCnf_SwitchOn_WaitXccStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_XCC_START_CNF,
                      CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf)
};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitXregStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_XREG_XSD_START_CNF,
                      CNAS_XSD_RcvXregStartCnf_SwitchOn_WaitXregStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_XREG_START_CNF,
                      CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf)
};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF动作表 */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitCasStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_START_CNF,
                      CNAS_XSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_START_CNF,
                      CNAS_XSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf)
};

/* 关机状态机消息 状态表 */
NAS_STA_STRU g_astCnasXsdSwitchOnStaTbl[] =
{
    /*****************定义开机初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_INIT,
                      g_astCnasXsdSwitchOnInitActTbl),

    /*****************定义等待卡文件信息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF,
                      g_astCnasXsdSwitchOnWaitCardFileCnfActTbl ),

    /*****************定义等待XCC开机结果消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF,
                      g_astCnasXsdSwitchOnWaitXccStartCnfActTbl),

    /*****************定义等待XREG开机结果消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF,
                      g_astCnasXsdSwitchOnWaitXregStartCnfActTbl),

    /*****************定义等待CAS开机结果消息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF,
                      g_astCnasXsdSwitchOnWaitCasStartCnfActTbl)

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSwitchOnStaTblSize
 功能描述  : 获取开机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:开机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetSwitchOnStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSwitchOnFsmDescAddr
 功能描述  : 获取开机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向开机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : h00246512
    修改内容   : 新生成函数


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XSD_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdSwitchOnFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



