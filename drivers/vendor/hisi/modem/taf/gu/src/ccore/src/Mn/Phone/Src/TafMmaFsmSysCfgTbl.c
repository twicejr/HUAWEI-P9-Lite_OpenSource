/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmSysCfgTbl.c
  版 本 号   : 初稿
  作    者   : l00301449
  生成日期   : 2015年04月07日
  功能描述   : Sys Cfg状态机table表
  函数列表   :
  修改历史   :
  1.日    期   : 2015年04月07日
    作    者   : l00301449
    修改内容   : 创建文件
******************************************************************************/

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

/*****************************************************************************
 函 数 名  : TAF_MMA_GetSysCfgStaTblSize
 功能描述  : 获取MMA模块SYS CFG状态机状态处理表的大小
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetSysCfgStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafMmaSysCfgStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetSysCfgFsmDescAddr
 功能描述  : 获取SYS CFG状态机描述表的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
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






