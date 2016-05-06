/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SleepInit.c
  版 本 号   : 初稿
  作    者   : zuowen
  生成日期   : 2005年3月7日
  最近修改   :
  功能描述   : 实现 SLEEP 功能模块的初始化函数
  函数列表   :
  修改历史   :

  1.日    期   : 2005年3月7日
    作    者   : zuowen
    修改内容   : 初始化创建文件

  2.日    期   : 2006年12月14日
    作    者   : x51137
    修改内容   : A32D07808

  3.日    期   : 2007年03月10日
    作    者   : x51137
    修改内容   : A320D09188
******************************************************************************/

#if 0
#include "vos.h"
#include "SleepInit.h"
#include "sleepsleep.h"
#include "mdrv.h"
#include "OamSpecTaskDef.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if 0

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人：h28225；检视人：l46160；原因简述：打点日志文件ID宏定义*/
#define    THIS_FILE_ID        PS_FILE_ID_SLEEP_INIT_C
/*lint +e767 修改人：h28225；检视人：l46160；*/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

/*****************************************************************************
  2 函数声明包含
*****************************************************************************/
extern VOS_VOID SLEEP_Init(VOS_VOID);
extern VOS_VOID SLEEP_SelfTask(VOS_VOID);


DRX_STATE_SLICE_STRU        *g_pstDrxStateSlice         = VOS_NULL_PTR;
LOWPOWER_STATE_STRU         *g_pstLowPowerState         = VOS_NULL_PTR;
HIFI_STATE_STRU             *g_pstHifiStateSlice        = VOS_NULL_PTR;
SLAVE_LOW_POWER_STATE_STRU  *g_pstSlaveLowPowerState    = VOS_NULL_PTR;

/*****************************************************************************
 函 数 名  : WuepsSleepPidInit
 功能描述  : SLEEP PID 初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32 PID 初始化结果
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID Sleep_InitGlobal(VOS_VOID)
{
    VOS_UINT32 ulRecordAddr = VOS_NULL_PTR;

    SLEEP_Init();

    ulRecordAddr = DRV_EXCH_MEM_MALLOC(VOS_DUMP_MEM_TOTAL_SIZE);

    if (VOS_NULL_PTR != ulRecordAddr)
    {
        g_pstDrxStateSlice      = (DRX_STATE_SLICE_STRU*)ulRecordAddr;

        ulRecordAddr += ((PWC_COMM_MODE_GSM + 1)*sizeof(DRX_STATE_SLICE_STRU));

        g_pstLowPowerState      = (LOWPOWER_STATE_STRU*)ulRecordAddr;

        ulRecordAddr += sizeof(LOWPOWER_STATE_STRU);

        g_pstHifiStateSlice     = (HIFI_STATE_STRU*)ulRecordAddr;

        ulRecordAddr += sizeof(HIFI_STATE_STRU);

        g_pstSlaveLowPowerState = (SLAVE_LOW_POWER_STATE_STRU*)ulRecordAddr;
    }
    else
    {
        g_pstDrxStateSlice = (DRX_STATE_SLICE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                ((PWC_COMM_MODE_GSM + 1)*sizeof(DRX_STATE_SLICE_STRU)));

        if (VOS_NULL_PTR == g_pstDrxStateSlice)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc DRX_STATE_SLICE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }

        g_pstLowPowerState = (LOWPOWER_STATE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                sizeof(LOWPOWER_STATE_STRU));

        if (VOS_NULL_PTR == g_pstLowPowerState)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc LOWPOWER_STATE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }

        g_pstHifiStateSlice = (HIFI_STATE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                sizeof(HIFI_STATE_STRU));

        if (VOS_NULL_PTR == g_pstHifiStateSlice)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc HIFI_STATE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }

        g_pstSlaveLowPowerState = (SLAVE_LOW_POWER_STATE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                sizeof(SLAVE_LOW_POWER_STATE_STRU));

        if (VOS_NULL_PTR == g_pstSlaveLowPowerState)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc SLAVE_LOW_POWER_STATE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }
    }

    /*lint -e534*/
    VOS_MemSet(g_pstDrxStateSlice, 0, ((PWC_COMM_MODE_GSM + 1)*sizeof(DRX_STATE_SLICE_STRU)));
    VOS_MemSet(g_pstLowPowerState, 0, sizeof(LOWPOWER_STATE_STRU));
    VOS_MemSet(g_pstHifiStateSlice, 0, sizeof(HIFI_STATE_STRU));
    VOS_MemSet(g_pstSlaveLowPowerState, 0, sizeof(SLAVE_LOW_POWER_STATE_STRU));
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : WuepsSleepFidInit
 功能描述  : SLEEP 模块 FID 的初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32 FID 初始化结果
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32  Sleep_TaskInit(VOS_VOID)
{
    Sleep_InitGlobal();

    if (VOS_NULL_BYTE == VOS_RegisterSelfTaskPrio(WUEPS_FID_OM,
                                               (VOS_TASK_ENTRY_TYPE)SLEEP_SelfTask,
                                               SLEEP_SELFTASK_PRI, WSLEEP_TASK_STACK_SIZE ))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
