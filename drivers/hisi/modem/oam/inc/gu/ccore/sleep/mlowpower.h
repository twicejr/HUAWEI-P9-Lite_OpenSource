/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : mlowpower.h
  版 本 号   : 初稿
  作    者   : s00207770
  生成日期   : 2015年8月15日
  最近修改   :
  功能描述   : mlowpower.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月15日
    作    者   : s00207770
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MLOWPOWER_H__
#define __MLOWPOWER_H__

#include "vos.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : SLEEP_MODE_INFO_STRU
 结构说明  : GU模当前系统状态
*****************************************************************************/
typedef struct
{
    VOS_INT                             (*bbe16_enable_operator)(BSP_DSP_TYPE_E edsptype);
    VOS_INT                             (*bbe16_disable_operator)(BSP_DSP_TYPE_E edsptype);
    VOS_INT                             (*bbe16_pwrup_operator)(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);
    VOS_INT                             (*bbe16_pwrdown_operator)(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);
    VOS_UINT32                          ulVoteMap;
    VOS_UINT32                          ulState;
    VOS_SPINLOCK                        spinlock;
    VOS_UINT32                          aulEnableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulActualEnableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulEnableSlice[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulDisableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulActualDisableCount[VOS_RATMODE_BUTT];
    VOS_UINT32                          aulDisableSlice[VOS_RATMODE_BUTT];
} MLP_BBE16_OPERATOR_INFO_STRU;

typedef struct
{
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16Load;                        /* BBE16镜像加载 */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16RunStop;                     /* BBE16激活/停止 */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16SysCtrl;                     /* BBE16解复位/复位 */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16SysClock;                    /* BBE16时钟打开/关闭 */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16RestoreBackup;               /* BBE16镜像恢复/备份 */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16WaitRestoreBackup;           /* BBE16等待镜像恢复/备份 */
    MLP_BBE16_OPERATOR_INFO_STRU        stBBE16PowerCtrl;                   /* BBE16上电/下电 */
} MLP_BBE16_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID mlp_dsp_init(VOS_VOID);
VOS_UINT32 mlp_dsp_load( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_run( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_stop( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_unreset( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_reset( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_enable_clock( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_disable_clock( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_restore( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_backup( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_wait_restore( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_wait_backup( VOS_RATMODE_ENUM_UINT32 enMode );
VOS_UINT32 mlp_dsp_pwrup( VOS_RATMODE_ENUM_UINT32 enMode, PWC_COMM_MODEM_E enModemId );
VOS_UINT32 mlp_dsp_pwrdown( VOS_RATMODE_ENUM_UINT32 enMode, PWC_COMM_MODEM_E enModemId );
VOS_VOID mlp_show_counter(VOS_VOID);





#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mlowpoer.h */
