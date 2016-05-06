/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregFsmSwitchOnTbl.c
  版 本 号   : 初稿
  作    者   : g0025031
  生成日期   : 2015年01月05日
  功能描述   : 1X XREG L2开机状态机事件函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXregFsmSwitchOn.h"
#include "CnasXregFsmSwitchOnTbl.h"
#include "UsimPsInterface.h"
#include "xsd_xreg_pif.h"
#include "CnasXregTimer.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_SWITCH_ON_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* CNAS XREG状态机数组:开机子状态机名称 */
NAS_FSM_DESC_STRU                       g_stCnasXregSwitchOnFsmDesc;

/* CNAS_XREG_SWITCH_ON_STA_INIT状态下动作表 */
NAS_ACT_STRU g_astCnasXregSwitchOnInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_START_REQ,
                      CNAS_XREG_RcvXsdStartReq_SwitchOn_Init),
};

/* CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF动作表 */
NAS_ACT_STRU g_astCnasXregSwitchOnWaitCardFileCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_XREG_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT,
                      CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf)

};


/* 开机状态机消息 状态表 */
NAS_STA_STRU g_astCnasXregSwitchOnStaTbl[] =
{
    /*****************定义开机初始状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_SWITCH_ON_STA_INIT,
                      g_astCnasXregSwitchOnInitActTbl),

    /*****************定义等待卡文件信息状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF,
                      g_astCnasXregSwitchOnWaitCardFileCnfActTbl )
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_GetSwitchOnStaTblSize
 功能描述  : 获取开机状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:开机状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetSwitchOnStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXregSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 函 数 名  : CNAS_XREG_GetSwitchOnFsmDescAddr
 功能描述  : 获取开机状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向开机状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : g00256031
    修改内容   : 新生成函数


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XREG_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXregSwitchOnFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */