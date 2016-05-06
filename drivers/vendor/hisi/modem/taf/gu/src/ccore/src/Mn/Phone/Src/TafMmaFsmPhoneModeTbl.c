/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmPhoneModeTbl.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月8日
  最近修改   :
  功能描述   : MMA模块手机模式状态机状态转移表
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月8日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "UsimPsInterface.h"
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafFsm.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "NasComm.h"
#include "TafMmaFsmPhoneMode.h"
#include "MmaMsccInterface.h"
#include "Taf_Tafm_Remote.h"
#include "TafMmaSndInternalMsg.h"
#include "MmaUphyInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_PHONE_MODE_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_FSM_DESC_STRU                       g_stTafMmaPhoneModeFsmDesc;

/**************************************************************************/
/*新增状态动作处理表 */
/**************************************************************************/

/* TAF_MMA_PHONE_MODE_STA_INIT 动作表 */
TAF_ACT_STRU        g_astTafMmaPhoneModeInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_POWER_INIT,
                      TAF_MMA_RcvMmaInterPowerInit_PhoneMode_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_USIM_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SPY,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init ),
    TAF_ACT_TBL_ITEM( CCPU_PID_CBT,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init ),
    /* Modified by s00261364 for L-C互操作项目, 2014-1-26, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvTafPhoneModeSet_PhoneMode_Init ),
    /* Modified by s00261364 for L-C互操作项目, 2014-1-26, end */

};
/* TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT 动作表 */
TAF_ACT_STRU        g_astTafMmaPhoneModeWaitExternalModuleInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitExternalModuleInit ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit ),

    TAF_ACT_TBL_ITEM( DSP_PID_STARTUP,
                      ID_UPHY_MMA_INIT_STATUS_IND,
                      TAF_MMA_RcvUphyInitStatusInd_PhoneMode_WaitExternalModuleInit ),

};



/* TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_START_CNF 动作表 */
TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccStartCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_START_CNF,
                      TAF_MMA_RcvMsccStartCnf_PhoneMode_WaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_START_CNF,
                      TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf ),
};

/* TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_POWER_OFF_CNF 动作表 */
TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccPowerOffCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_POWER_OFF_CNF,
                      TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_WaitMsccPowerOffCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF,
                      TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf ),

};


TAF_ACT_STRU        g_astTafMmaPhoneModeGetGeoWaitMsccStartCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_START_CNF,
                      TAF_MMA_RcvMsccStartCnf_PhoneMode_GetGeoWaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_START_CNF,
                      TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_GetGeoWaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoWaitMsccStartCnf ),
};



TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccGetGeoCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_GET_GEO_CNF,
                      TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccGetGeoCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF,
                      TAF_MMA_RcvTiWaitMsccGetGeoCnfExpired_PhoneMode_WaitMsccGetGeoCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccGetGeoCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitMsccGetGeoCnf ),
};

TAF_ACT_STRU        g_astTafMmaPhoneModeGetGeoCmpWaitUsimStatusIndActTbl[]   =
{
    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoCmpWaitUsimStatusInd ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoCmpWaitUsimStatusInd ),
};

TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccStopGetGeoCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_STOP_GET_GEO_CNF,
                      TAF_MMA_RcvMsccStopGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf ),

    /* 解决对冲的场景:刚下发停止获取国家码的请求，MSCC就将获取国家码的结果上报上来 */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_GET_GEO_CNF,
                      TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccStopGetGeoCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF,
                      TAF_MMA_RcvTiWaitMsccStopGetGeoCnfExpired_PhoneMode_WaitMsccStopGetGeoCnf ),
};

TAF_ACT_STRU        g_astTafMmaPhoneModeGetGeoWaitMsccPowerOffCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_POWER_OFF_CNF,
                      TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_GetGeoWaitMsccPowerOffCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccPowerOffCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF,
                      TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_GetGeoWaitMsccPowerOffCnf ),
};


/* 手机模式状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafMmaPhoneModeStaTbl[]   =
{
    /* 手机模式状态机的初始化状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_INIT,
                       g_astTafMmaPhoneModeInitActTbl ),

    /* 迁移状态到等待初始化完成状态上报 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT,
                      g_astTafMmaPhoneModeWaitExternalModuleInitActTbl ),



    /* 等待MSCC的开机回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_START_CNF,
                      g_astTafMmaPhoneModeWaitMsccStartCnfActTbl ),


    /* 等待MSCC的关机回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_POWER_OFF_CNF,
                      g_astTafMmaPhoneModeWaitMsccPowerOffCnfActTbl ),



    /* 等待MSCC获取地理位置信息的开机回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_START_CNF,
                      g_astTafMmaPhoneModeGetGeoWaitMsccStartCnfActTbl ),

    /* 等待MSCC的获取地理位置信息回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_GET_GEO_CNF,
                      g_astTafMmaPhoneModeWaitMsccGetGeoCnfActTbl ),

    /* 等待MSCC的获取地理位置信息回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_GET_GEO_CMP_WAIT_USIM_STATUS_IND,
                      g_astTafMmaPhoneModeGetGeoCmpWaitUsimStatusIndActTbl ),

    /* 等待MSCC的停止获取地理位置信息回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_STOP_GET_GEO_CNF,
                      g_astTafMmaPhoneModeWaitMsccStopGetGeoCnfActTbl ),

    /* 等待MSCC获取地理位置信息的关机回复状态 */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_POWER_OFF_CNF,
                      g_astTafMmaPhoneModeGetGeoWaitMsccPowerOffCnfActTbl ),

};

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPhoneModeStaTblSize
 功能描述  : 获取MMA模块手机模式状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:MMA模块手机模式状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetPhoneModeStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafMmaPhoneModeStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPhoneModeFsmDescAddr
 功能描述  : 获取MMA模块手机模式状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向MMA模块手机模式状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_MMA_GetPhoneModeFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaPhoneModeFsmDesc);
}






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



