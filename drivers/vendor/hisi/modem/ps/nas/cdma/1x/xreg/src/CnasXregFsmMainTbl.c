/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregFsmMainTbl.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月03日
  功能描述   : XREG L1主状态机table表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregFsmMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "xsd_xreg_pif.h"
#include  "CnasXregTimer.h"
#include  "CnasXregProcess.h"
#include  "CnasXregSndInternalMsg.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XREG 主状态机 */
NAS_FSM_DESC_STRU                       g_stCnasXregL1MainFsmDesc;

/* XREG L1 FSM null状态下事件处理表 */
NAS_ACT_STRU                            g_astCnasXregNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_START_REQ,
                      CNAS_XREG_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF,
                      CNAS_XREG_RcvSwitchOnRslt_Null),

};

/* XREG L1 FSM unreg状态下事件处理表 */
NAS_ACT_STRU                            g_astCnasXregUnRegActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_START_REQ,
                      CNAS_XREG_RcvStartReq_UnReg),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      CNAS_XREG_RcvRegedDataInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_MSG_ACCESS_RSLT_IND,
                      CNAS_XREG_RcvAccessInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_REQ,
                      CNAS_XREG_RcvRegReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_CNF,
                      CNAS_XREG_RcvRegCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_L1Main),
};

/* XREG L1 FSM reged状态下事件处理表 */
NAS_ACT_STRU                            g_astCnasXregRegedActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      CNAS_XREG_RcvRegedDataInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_MSG_ACCESS_RSLT_IND,
                      CNAS_XREG_RcvAccessInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_REQ,
                      CNAS_XREG_RcvRegReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_CNF,
                      CNAS_XREG_RcvRegCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_L1Main),
};

/* XREG L1 主状态机状态处理表 */
NAS_STA_STRU                            g_astCnasXregL1MainStaTbl[] =
{
    /*****************定义初始化状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_NULL,
                      g_astCnasXregNullActTbl ),

    /*****************定义开机未注册状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_UNREG,
                      g_astCnasXregUnRegActTbl ),

    /*****************定义已经注册状态转移表**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_REGED,
                      g_astCnasXregRegedActTbl ),
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XREG_GetMainFsmDescAddr
 功能描述  : 1X XREG L1主状态机地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XREG_GetMainFsmDescAddr(VOS_VOID)
{
    return &g_stCnasXregL1MainFsmDesc;
}


/*****************************************************************************
 函 数 名  : CNAS_XREG_GetL1MainStaTblSize
 功能描述  : 获取1X XREG L1主状态机状态表大小
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetL1MainStaTblSize(VOS_VOID)
{
    return sizeof(g_astCnasXregL1MainStaTbl)/sizeof(NAS_STA_STRU);
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



