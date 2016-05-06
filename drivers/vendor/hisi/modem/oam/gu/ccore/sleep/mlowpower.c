/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : mlowpower.c
  版 本 号   : 初稿
  作    者   : s00207770
  生成日期   : 2015年8月15日
  最近修改   :
  功能描述   : GUTL多模低功耗控制模块
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月15日
    作    者   : s00207770
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "v_private.h"
#include "omprivate.h"
#include "mlowpower.h"

#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_M_LOWPOWER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
MLP_BBE16_INFO_STRU                     g_stmlpBBE16Handle;
NV_SLEEP_BBE16_CTRL_STRU                g_stSleepBBE16Ctrl;

#ifndef MLP_BIT_N
#define MLP_BIT_N(num)                  (0x01 << (num))
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : mlp_dsp_load
 功能描述  : BBE16加载接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_load( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16Load.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16Load.aulEnableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16Load.aulEnableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (!(g_stmlpBBE16Handle.stBBE16Load.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode))))
    {
        g_stmlpBBE16Handle.stBBE16Load.ulVoteMap |= ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16Load.ulVoteMap != 0)
        && (g_stmlpBBE16Handle.stBBE16Load.ulState == 0))
    {
        if (g_stmlpBBE16Handle.stBBE16Load.bbe16_enable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16Load.bbe16_enable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16Load.ulState   = VOS_TRUE;
            g_stmlpBBE16Handle.stBBE16Load.aulActualEnableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16Load.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_run
 功能描述  : BBE16激活接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_run( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16RunStop.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16RunStop.aulEnableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16RunStop.aulEnableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (!(g_stmlpBBE16Handle.stBBE16RunStop.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode))))
    {
        g_stmlpBBE16Handle.stBBE16RunStop.ulVoteMap |= ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16RunStop.ulVoteMap != 0)
        && (g_stmlpBBE16Handle.stBBE16RunStop.ulState == VOS_FALSE))
    {
        if (g_stmlpBBE16Handle.stBBE16RunStop.bbe16_enable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16RunStop.bbe16_enable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16RunStop.ulState   = VOS_TRUE;
            g_stmlpBBE16Handle.stBBE16RunStop.aulActualEnableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16RunStop.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_stop
 功能描述  : BBE16停止接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_stop( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16RunStop.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16RunStop.aulDisableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16RunStop.aulDisableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (g_stmlpBBE16Handle.stBBE16RunStop.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode)))
    {
        g_stmlpBBE16Handle.stBBE16RunStop.ulVoteMap &= ~ ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16RunStop.ulVoteMap == 0)
        && (g_stmlpBBE16Handle.stBBE16RunStop.ulState == VOS_TRUE))
    {
        if (g_stmlpBBE16Handle.stBBE16RunStop.bbe16_disable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16RunStop.bbe16_disable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16RunStop.ulState   = VOS_FALSE;
            g_stmlpBBE16Handle.stBBE16RunStop.aulActualDisableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16RunStop.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_unreset
 功能描述  : BBE16解复位接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_unreset( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16SysCtrl.spinlock, ulLockLevel);

    g_stmlpBBE16Handle.stBBE16SysCtrl.aulEnableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16SysCtrl.aulEnableSlice[enMode] = VOS_GetSlice();

    /* 维测 */
    /*lint -e701*/
    if (!(g_stmlpBBE16Handle.stBBE16SysCtrl.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode))))
    {
        g_stmlpBBE16Handle.stBBE16SysCtrl.ulVoteMap |= ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16SysCtrl.ulVoteMap != 0)
        && (g_stmlpBBE16Handle.stBBE16SysCtrl.ulState == VOS_FALSE))
    {
        if (g_stmlpBBE16Handle.stBBE16SysCtrl.bbe16_enable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16SysCtrl.bbe16_enable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16SysCtrl.ulState   = VOS_TRUE;
            g_stmlpBBE16Handle.stBBE16SysCtrl.aulActualEnableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16SysCtrl.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_reset
 功能描述  : BBE16复位接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_reset( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    if (VOS_FALSE == g_stSleepBBE16Ctrl.ulSleepBBE16Switch)
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16SysCtrl.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16SysCtrl.aulDisableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16SysCtrl.aulDisableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (g_stmlpBBE16Handle.stBBE16SysCtrl.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode)))
    {
        g_stmlpBBE16Handle.stBBE16SysCtrl.ulVoteMap &= ~ ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16SysCtrl.ulVoteMap == 0)
        && (g_stmlpBBE16Handle.stBBE16SysCtrl.ulState == VOS_TRUE))
    {
        if (g_stmlpBBE16Handle.stBBE16SysCtrl.bbe16_disable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16SysCtrl.bbe16_disable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16SysCtrl.ulState   = VOS_FALSE;
            g_stmlpBBE16Handle.stBBE16SysCtrl.aulActualDisableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16SysCtrl.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_enable_clk
 功能描述  : BBE16时钟打开接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_enable_clock( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16SysClock.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16SysClock.aulEnableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16SysClock.aulEnableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (!(g_stmlpBBE16Handle.stBBE16SysClock.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode))))
    {
        g_stmlpBBE16Handle.stBBE16SysClock.ulVoteMap |= ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16SysClock.ulVoteMap != 0)
        && (g_stmlpBBE16Handle.stBBE16SysClock.ulState == VOS_FALSE))
    {
        if (g_stmlpBBE16Handle.stBBE16SysClock.bbe16_enable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16SysClock.bbe16_enable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16SysClock.ulState   = VOS_TRUE;
            g_stmlpBBE16Handle.stBBE16SysClock.aulActualEnableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16SysClock.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_disable_clk
 功能描述  : BBE16时钟关闭接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_disable_clock( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    if (VOS_FALSE == g_stSleepBBE16Ctrl.ulSleepBBE16Switch)
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16SysClock.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16SysClock.aulDisableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16SysClock.aulDisableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (g_stmlpBBE16Handle.stBBE16SysClock.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode)))
    {
        g_stmlpBBE16Handle.stBBE16SysClock.ulVoteMap &= ~ ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16SysClock.ulVoteMap == 0)
        && (g_stmlpBBE16Handle.stBBE16SysClock.ulState == VOS_TRUE))
    {
        if (g_stmlpBBE16Handle.stBBE16SysClock.bbe16_disable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16SysClock.bbe16_disable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16SysClock.ulState   = VOS_FALSE;
            g_stmlpBBE16Handle.stBBE16SysClock.aulActualDisableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16SysCtrl.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_resume
 功能描述  : BBE16镜像恢复接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_restore( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16RestoreBackup.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16RestoreBackup.aulEnableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16RestoreBackup.aulEnableSlice[enMode] = VOS_GetSlice();

    /* 投票 */
    /*lint -e701*/
    if (!(g_stmlpBBE16Handle.stBBE16RestoreBackup.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode))))
    {
        g_stmlpBBE16Handle.stBBE16RestoreBackup.ulVoteMap |= ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    /* 如果有票，并且恢复状态为FALSE，做恢复处理，恢复状态变为TRUE */
    if ((g_stmlpBBE16Handle.stBBE16RestoreBackup.ulVoteMap != 0)
        && (g_stmlpBBE16Handle.stBBE16RestoreBackup.ulState == VOS_FALSE))
    {
        if (g_stmlpBBE16Handle.stBBE16RestoreBackup.bbe16_enable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16RestoreBackup.bbe16_enable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16RestoreBackup.ulState   = VOS_TRUE;
            g_stmlpBBE16Handle.stBBE16RestoreBackup.aulActualEnableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16ResumeBackup.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_backup
 功能描述  : BBE16镜像备份接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_backup( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    if (VOS_FALSE == g_stSleepBBE16Ctrl.ulSleepBBE16Switch)
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16RestoreBackup.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16RestoreBackup.aulDisableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16RestoreBackup.aulDisableSlice[enMode] = VOS_GetSlice();

    /* 销票 */
    /*lint -e701*/
    if (g_stmlpBBE16Handle.stBBE16RestoreBackup.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode)))
    {
        g_stmlpBBE16Handle.stBBE16RestoreBackup.ulVoteMap &= ~ ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    /* 如果没票，并且恢复状态为TRUE，做备份处理，恢复状态变为FALSE */
    if ((g_stmlpBBE16Handle.stBBE16RestoreBackup.ulVoteMap == 0)
        && (g_stmlpBBE16Handle.stBBE16RestoreBackup.ulState == VOS_TRUE))
    {
        if (g_stmlpBBE16Handle.stBBE16RestoreBackup.bbe16_disable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16RestoreBackup.bbe16_disable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16RestoreBackup.ulState   = VOS_FALSE;
            g_stmlpBBE16Handle.stBBE16RestoreBackup.aulActualDisableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16RestoreBackup.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_resume
 功能描述  : BBE16等待镜像恢复接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_wait_restore( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.aulEnableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.aulEnableSlice[enMode] = VOS_GetSlice();

    /* 投票 */
    /*lint -e701*/
    if (!(g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode))))
    {
        g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulVoteMap |= ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    /* 如果有票 */
    if ((g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulVoteMap != 0)
        && (g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulState == VOS_FALSE))
    {
        if (g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.bbe16_enable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.bbe16_enable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulState   = VOS_TRUE;
            g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.aulActualEnableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_backup
 功能描述  : BBE16等待镜像备份接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_wait_backup( VOS_RATMODE_ENUM_UINT32 enMode )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    if (VOS_FALSE == g_stSleepBBE16Ctrl.ulSleepBBE16Switch)
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.spinlock, ulLockLevel);

    g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.aulDisableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.aulDisableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode)))
    {
        g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulVoteMap &= ~ ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulVoteMap == 0)
        && (g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulState == VOS_TRUE))
    {
        if (g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.bbe16_disable_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.bbe16_disable_operator(BSP_DSP_CBBE);
            g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulState   = VOS_FALSE;
            g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.aulActualDisableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_resume
 功能描述  : BBE16等待镜像恢复接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_pwrup( VOS_RATMODE_ENUM_UINT32 enMode, PWC_COMM_MODEM_E enModemId )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16PowerCtrl.spinlock, ulLockLevel);

    /* 维测 */
    g_stmlpBBE16Handle.stBBE16PowerCtrl.aulEnableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16PowerCtrl.aulEnableSlice[enMode] = VOS_GetSlice();

    /* 投票 */
    /*lint -e701*/
    if (!(g_stmlpBBE16Handle.stBBE16PowerCtrl.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode))))
    {
        g_stmlpBBE16Handle.stBBE16PowerCtrl.ulVoteMap |= ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    /* 如果有票 */
    if ((g_stmlpBBE16Handle.stBBE16PowerCtrl.ulVoteMap != 0)
        && (g_stmlpBBE16Handle.stBBE16PowerCtrl.ulState == VOS_FALSE))
    {
        if (g_stmlpBBE16Handle.stBBE16PowerCtrl.bbe16_pwrup_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16PowerCtrl.bbe16_pwrup_operator((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_CBBE16, enModemId, PWC_COMM_CHANNEL_0);
            g_stmlpBBE16Handle.stBBE16PowerCtrl.ulState   = VOS_TRUE;
            g_stmlpBBE16Handle.stBBE16PowerCtrl.aulActualEnableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16PowerCtrl.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_backup
 功能描述  : BBE16等待镜像备份接口
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 mlp_dsp_pwrdown( VOS_RATMODE_ENUM_UINT32 enMode, PWC_COMM_MODEM_E enModemId )
{
    VOS_ULONG                           ulLockLevel;

    /* 只支持1x和hrpd */
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return VOS_ERR;
    }

    if (VOS_FALSE == g_stSleepBBE16Ctrl.ulSleepBBE16Switch)
    {
        return VOS_ERR;
    }

    VOS_SpinLockIntLock(&g_stmlpBBE16Handle.stBBE16PowerCtrl.spinlock, ulLockLevel);

    g_stmlpBBE16Handle.stBBE16PowerCtrl.aulDisableCount[enMode]++;
    g_stmlpBBE16Handle.stBBE16PowerCtrl.aulDisableSlice[enMode] = VOS_GetSlice();

    /*lint -e701*/
    if (g_stmlpBBE16Handle.stBBE16PowerCtrl.ulVoteMap & ((VOS_UINT32)MLP_BIT_N(enMode)))
    {
        g_stmlpBBE16Handle.stBBE16PowerCtrl.ulVoteMap &= ~ ((VOS_UINT32)MLP_BIT_N(enMode));
    }
    /*lint +e701*/

    if ((g_stmlpBBE16Handle.stBBE16PowerCtrl.ulVoteMap == 0)
        && (g_stmlpBBE16Handle.stBBE16PowerCtrl.ulState == VOS_TRUE))
    {
        if (g_stmlpBBE16Handle.stBBE16PowerCtrl.bbe16_pwrdown_operator != VOS_NULL_PTR)
        {
            (VOS_VOID)g_stmlpBBE16Handle.stBBE16PowerCtrl.bbe16_pwrdown_operator((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_CBBE16, enModemId, PWC_COMM_CHANNEL_0);
            g_stmlpBBE16Handle.stBBE16PowerCtrl.ulState   = VOS_FALSE;
            g_stmlpBBE16Handle.stBBE16PowerCtrl.aulActualDisableCount[enMode]++;
        }
    }

    VOS_SpinUnlockIntUnlock(&g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.spinlock, ulLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : mlp_dsp_init
 功能描述  : BBE16低功耗接口初始化
 输入参数  : VOS_RATMODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID mlp_dsp_init(VOS_VOID)
{
    (VOS_VOID)VOS_MemSet(&g_stmlpBBE16Handle, 0, sizeof(g_stmlpBBE16Handle));

    g_stmlpBBE16Handle.stBBE16Load.bbe16_enable_operator                = mdrv_dsp_load;
    g_stmlpBBE16Handle.stBBE16Load.ulState                              = VOS_FALSE;

    g_stmlpBBE16Handle.stBBE16RunStop.bbe16_enable_operator             = mdrv_dsp_run;
    g_stmlpBBE16Handle.stBBE16RunStop.bbe16_disable_operator            = mdrv_dsp_stop;
    g_stmlpBBE16Handle.stBBE16RunStop.ulState                           = VOS_TRUE;

    g_stmlpBBE16Handle.stBBE16SysCtrl.bbe16_enable_operator             = mdrv_dsp_unreset;
    g_stmlpBBE16Handle.stBBE16SysCtrl.bbe16_disable_operator            = mdrv_dsp_reset;
    g_stmlpBBE16Handle.stBBE16SysCtrl.ulState                           = VOS_TRUE;

    g_stmlpBBE16Handle.stBBE16SysClock.bbe16_enable_operator            = mdrv_dsp_enable_clock;
    g_stmlpBBE16Handle.stBBE16SysClock.bbe16_disable_operator           = mdrv_dsp_disable_clock;
    g_stmlpBBE16Handle.stBBE16SysClock.ulState                          = VOS_TRUE;

    g_stmlpBBE16Handle.stBBE16RestoreBackup.bbe16_enable_operator       = mdrv_dsp_restore;
    g_stmlpBBE16Handle.stBBE16RestoreBackup.bbe16_disable_operator      = mdrv_dsp_backup;
    g_stmlpBBE16Handle.stBBE16RestoreBackup.ulState                     = VOS_TRUE;

    g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.bbe16_enable_operator   = mdrv_dsp_wait_restore_over;
    g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.bbe16_disable_operator  = mdrv_dsp_wait_backup_over;
    g_stmlpBBE16Handle.stBBE16WaitRestoreBackup.ulState                 = VOS_TRUE;

    g_stmlpBBE16Handle.stBBE16PowerCtrl.bbe16_pwrup_operator            = mdrv_pm_pwrup;
    g_stmlpBBE16Handle.stBBE16PowerCtrl.bbe16_pwrdown_operator          = mdrv_pm_pwrdown;
    g_stmlpBBE16Handle.stBBE16PowerCtrl.ulState                         = VOS_TRUE;

    /* 读取低功耗 NV开关 */
    if(NV_OK != NV_Read(en_NV_Item_SLEEP_BBE16_CTRL, &g_stSleepBBE16Ctrl, sizeof(NV_SLEEP_BBE16_CTRL_STRU)))
    {
        g_stSleepBBE16Ctrl.ulSleepBBE16Switch                           = VOS_FALSE;
        return;
    }

    return;
}

VOS_VOID mlp_show_counter(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("nv switch:%d\r\n", g_stSleepBBE16Ctrl.ulSleepBBE16Switch);

    vos_printf("powup count:%d\r\n", g_stmlpBBE16Handle.stBBE16PowerCtrl.aulEnableCount[VOS_RATMODE_1X]);
    vos_printf("powup actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16PowerCtrl.aulActualEnableCount[VOS_RATMODE_1X]);
    vos_printf("powdown count:%d\r\n", g_stmlpBBE16Handle.stBBE16PowerCtrl.aulDisableCount[VOS_RATMODE_1X]);
    vos_printf("powdown actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16PowerCtrl.aulActualDisableCount[VOS_RATMODE_1X]);

    vos_printf("run count:%d\r\n", g_stmlpBBE16Handle.stBBE16RunStop.aulEnableCount[VOS_RATMODE_1X]);
    vos_printf("run actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16RunStop.aulActualEnableCount[VOS_RATMODE_1X]);
    vos_printf("stop count:%d\r\n", g_stmlpBBE16Handle.stBBE16RunStop.aulDisableCount[VOS_RATMODE_1X]);
    vos_printf("stop actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16RunStop.aulActualDisableCount[VOS_RATMODE_1X]);

    vos_printf("unreset count:%d\r\n", g_stmlpBBE16Handle.stBBE16SysCtrl.aulEnableCount[VOS_RATMODE_1X]);
    vos_printf("unreset actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16SysCtrl.aulActualEnableCount[VOS_RATMODE_1X]);
    vos_printf("reset count:%d\r\n", g_stmlpBBE16Handle.stBBE16SysCtrl.aulDisableCount[VOS_RATMODE_1X]);
    vos_printf("reset actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16SysCtrl.aulActualDisableCount[VOS_RATMODE_1X]);

    vos_printf("restore count:%d\r\n", g_stmlpBBE16Handle.stBBE16RestoreBackup.aulEnableCount[VOS_RATMODE_1X]);
    vos_printf("restore actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16RestoreBackup.aulActualEnableCount[VOS_RATMODE_1X]);
    vos_printf("backup count:%d\r\n", g_stmlpBBE16Handle.stBBE16RestoreBackup.aulDisableCount[VOS_RATMODE_1X]);
    vos_printf("backup actual count:%d\r\n", g_stmlpBBE16Handle.stBBE16RestoreBackup.aulActualDisableCount[VOS_RATMODE_1X]);
    /*lint +e534*/

    return;
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

