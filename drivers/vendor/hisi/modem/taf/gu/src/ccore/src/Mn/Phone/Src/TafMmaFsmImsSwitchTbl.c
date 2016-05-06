/******************************************************************************

                  版权所有 (C), 2005-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmImsSwitchTbl.c
  版 本 号   : 初稿
  作    者   : f00179208
  生成日期   : 2015年02月04日
  最近修改   :
  功能描述   : MMA模块IMS SWITCH状态机状态转移表
  函数列表   :
  修改历史   :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafFsm.h"
#include "TafAppMma.h"
#include "TafMmaTimerMgmt.h"

#if (FEATURE_IMS == FEATURE_ON)
#include "TafMmaFsmImsSwitch.h"
#include "TafMmaFsmImsSwitchTbl.h"
#include "MmaMsccInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_PHONE_MODE_TBL_C

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_FSM_DESC_STRU                       g_stTafMmaImsSwitchFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* TAF_MMA_IMS_SWITCH_STA_INIT 动作表 */
TAF_ACT_STRU        g_astTafMmaImsSwitchInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SWITCH_SET_REQ,
                      TAF_MMA_RcvTafImsSwitchSet_ImsSwitch_Init ),

};

/* TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_START_CNF 动作表 */
TAF_ACT_STRU        g_astTafMmaImsSwitchWaitImsaStartCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_START_CNF,
                      TAF_MMA_RcvMsccImsStartCnf_ImsSwitch_WaitMsccImsStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF,
                      TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf ),

};

/* TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_STOP_CNF 动作表 */
TAF_ACT_STRU        g_astTafMmaImsSwitchWaitImsaStopCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_STOP_CNF,
                      TAF_MMA_RcvMsccImsStopCnf_ImsSwitch_WaitMsccImsStopCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF,
                      TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf ),

};

/* IMS开关状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafMmaImsSwitchStaTbl[]   =
{
    /* IMS开关状态机的初始化状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_INIT,
                       g_astTafMmaImsSwitchInitActTbl ),

    /* 等待IMSA的开机回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_START_CNF,
                      g_astTafMmaImsSwitchWaitImsaStartCnfActTbl ),

    /* 等待IMSA的关机回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_STOP_CNF,
                      g_astTafMmaImsSwitchWaitImsaStopCnfActTbl ),
};


/*****************************************************************************
 函 数 名  : TAF_MMA_GetImsSwitchStaTblSize
 功能描述  : 获取MMA模块IMS开关状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:MMA模块IMS开关状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetImsSwitchStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafMmaImsSwitchStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetImsSwitchFsmDescAddr
 功能描述  : 获取MMA模块IMS开关状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向MMA模块IMS开关状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_MMA_GetImsSwitchFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaImsSwitchFsmDesc);
}
#endif /* FEATURE_IMS */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



