/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __MDRV_ACORE_DPM_H__
#define __MDRV_ACORE_DPM_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"
#include <mdrv_pm_common.h>

typedef enum tagPWC_COMM_CHANNEL_E
{
	PWC_COMM_CHANNEL_0,
	PWC_COMM_CHANNEL_1,
    PWC_COMM_CHANNEL_2,
    PWC_COMM_CHANNEL_BUTT,
} PWC_COMM_CHANNEL_E;

typedef enum tagPWC_COMM_MODULE_E
{
    PWC_COMM_MODULE_PA,
    PWC_COMM_MODULE_RF,
    PWC_COMM_MODULE_ABB,
    PWC_COMM_MODULE_BBE16,

    PWC_COMM_MODULE_BBP_DRX,  /*W:1A,2A,2C,2D,3*/
    PWC_COMM_MODULE_BBP_DPA,  /*W:1B*/
    PWC_COMM_MODULE_BBP_MEM,  /*W:2B*/

    PWC_COMM_MODULE_BUTT,
}PWC_COMM_MODULE_E;

typedef enum pm_wake_src
{
    PM_WAKE_SRC_UART0 = 0, /*for acore at_uart*/
    PM_WAKE_SRC_SOCP ,     /*for acore sd_log*/
    PM_WAKE_SRC_DRX_TIMER, /*for ccore drx timer*/
    PM_WAKE_SRC_BUT,
}PM_WAKE_SRC_E;


typedef enum tagPWC_COMM_STATUS_E
{
    PWRCTRL_COMM_ON = 0x10,
    PWRCTRL_COMM_OFF = 0x20,
    PWC_COMM_STATUS_BUTT
}PWC_COMM_STATUS_E;

typedef void (*PWC_SLEEP_FUNCPTR)(void);
/******************************************************
 * *睡眠投票ID ,从0开始，最多32个
 * *涉及投票的组件需要在此添加LOCK ID
 * *请同步修改wakelock_balong.c中的debug_wakelock
 * *******************************************************/
typedef enum tagPWC_CLIENT_ID_E
{
    PWRCTRL_SLEEP_TLPS = 0x100,   /*MSP--fuxin*/
    PWRCTRL_SLEEP_PS_G0,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W0,       /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_G1,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W1,       /*GU--ganlan*/
    PWRCTRL_SLEEP_FTM,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_FTM_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_OAM,          /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI0,            /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI1,            /* LTE --yangzhi */
    PWRCTRL_SLEEP_DMA,             /* GU --jinguojun*/
    PWRCTRL_SLEEP_MEM,              /*drv,flash or emmc*/
    PWRCTRL_SLEEP_DSFLOW,          /* NAS --zhangyizhan */
    PWRCTRL_SLEEP_TEST,            /* PM  ---shangmianyou */
    PWRCTRL_SLEEP_UART0,        /*UART0 -zhangliangdong */
    PWRCTRL_SLEEP_TDS,         /*TRRC&TL2----leixiantiao*/

    PWRCTRL_SLEEP_CDMAUART,         /*drv cdma uart 数传*/
    PWRCTRL_SLEEP_USIM,             /*oam*/
    /*以下部分的ID已经不使用了，后期会删除*/
    PWRCTRL_SLEEP_RNIC,
    PWRCTRL_TEST_DEEPSLEEP  = 0x11f,
    LOCK_ID_BOTTOM =0x120
}PWC_CLIENT_ID_E;
typedef enum
{
    DFS_PROFILE_0 = 0,            /*频率级别1*/
    DFS_PROFILE_1 = 1,            /*频率级别2*/
    DFS_PROFILE_2 = 2,            /*频率级别3*/
    DFS_PROFILE_3 = 3,            /*频率级别4*/
    DFS_PROFILE_4 = 4,            /*频率级别5*/
    DFS_PROFILE_BUTT
} PWC_DFS_PROFILE_E;

/*
 *  DFS Device QoS
 */
typedef enum tagDFS_QOS_ID_E
{
    DFS_QOS_ID_ACPU_MINFREQ_E = 0,  /*(0)*/
    DFS_QOS_ID_ACPU_MAXFREQ_E,      /*(1)*/
    DFS_QOS_ID_CCPU_MINFREQ_E,      /*(2)*/
    DFS_QOS_ID_CCPU_MAXFREQ_E,      /*(3)*/
    DFS_QOS_ID_DDR_MINFREQ_E,       /*(4)*/
    DFS_QOS_ID_DDR_MAXFREQ_E,       /*(5)*/
    DFS_QOS_ID_GPU_MINFREQ_E,       /*(6)*/
    DFS_QOS_ID_GPU_MAXFREQ_E,       /*(7)*/
    DFS_QOS_ID_BUS_MINFREQ_E,       /*(8)*/
    DFS_QOS_ID_BUS_MAXFREQ_E        /*(9)*/
}DFS_QOS_ID_E;

/*****************************************************************************
* 函 数 名  : mdrv_pm_pwrup
*
* 功能描述  : 通信模块控制电源上电接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_pwrup (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_pwrdown
*
* 功能描述  : 通信模块控制电源下电接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_pwrdown (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_get_pwrstatus
*
* 功能描述  : 通信模块控制电源查询接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : PWRCTRL_COMM_ON 外设模块已经上电
*             PWRCTRL_COMM_OFF 外设模块已经下电
*             其他，错误
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_pwrstatus(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_enable_pllclk
*
* 功能描述  : DRX PLL使能时钟
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  :  0，执行成功；-1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_enable_pllclk (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_disable_pllclk
*
* 功能描述  : DRX PLL关闭时钟
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : 0，执行成功；-1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_disable_pllclk (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_get_pllclk_status
*
* 功能描述  : DRX PLL查询时钟
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : PWRCTRL_COMM_ON         时钟打开
*             PWRCTRL_COMM_OFF        时钟关闭
*             -1                      查询失败
*
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_pllclk_status (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem,PWC_COMM_CHANNEL_E enChannel);

typedef unsigned int (*PWRCTRLFUNCPTR)(unsigned int arg);
/*****************************************************************************
* 函 数 名  : mdrv_pm_register_ccpuload_cb
*
* 功能描述  : 提供给TTF的回调函数
*
* 输入参数  : PWRCTRLFUNCPTR pFunc
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
void mdrv_pm_register_ccpuload_cb(PWRCTRLFUNCPTR pFunc );

/*****************************************************************************
* 函 数 名  : mdrv_pm_get_ccpuload
*
* 功能描述  : 返回当前的cpu占有率
*
* 输入参数  : 指向容纳返回值当的指针
* 输出参数  :-1，表示获取值失败；0，表示获取成功，百分比通过入参返回。
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_ccpuload(unsigned int *ptrCCpuLoad);


/*****************************************************************************
* 函 数 名  : mdrv_pm_dfs_qos_get
*
* 功能描述  : 低功耗调频，申请投票接口。
*
* 输入参数  : int qos_id     投票模块ID 需要使用枚举DFS_QOS_ID_E中的值
*             unsigned int req_value  投票频率值：如DDR频率800M等，单位KHZ
*             int* req_id    该投票接口申请到的投票ID（比如不同组件投票），动态值，可能每次不一样
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_dfs_qos_get(int qos_id, unsigned int req_value, int* req_id);

/*****************************************************************************
* 函 数 名  : mdrv_pm_dfs_qos_put
*
* 功能描述  : 低功耗调频，投票释放接口
*
* 输入参数  : int qos_id   投票模块ID，如总线频率，ACPU频率等
*             需要使用枚举DFS_QOS_ID_E中的值
*             int* req_id  mdrv_pm_dfs_qos_get申请投票接口获取的投票ID
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_dfs_qos_put(int qos_id, int* req_id);

/*****************************************************************************
* 函 数 名  : mdrv_pm_dfs_qos_update
*
* 功能描述  : 低功耗调频，更新投票值接口
*
* 输入参数  : int qos_id    投票模块ID，如总线频率，ACPU频率等
*             需要使用枚举DFS_QOS_ID_E中的值
*             int req_id    mdrv_pm_dfs_qos_get申请投票接口获取到的投票ID
*             unsigned int req_value 投票频率值：如DDR频率800M等
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_dfs_qos_update(int qos_id, int req_id, unsigned int req_value);


/*****************************************************************************
* 函 数 名  : mdrv_pm_get_tcxo_status
*
* 功能描述  : 获取TCXO的状态
*
* 输入参数  : PWC_COMM_MODEM_E enModemId
* 输出参数  :
*
* 返 回 值  : PWRCTRL_COMM_ON 使能
*             PWRCTRL_COMM_OFF 禁止
*             其他，异常
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
* 函 数 名  : mdrv_pm_enable_tcxo
*
* 功能描述  : 打开TCXO
*
* 输入参数  : PWC_COMM_MODEM_E  enModemId 卡号
*             PWC_COMM_MODE_E enModeType  协议模式
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_enable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);


/*****************************************************************************
* 函 数 名  : mdrv_pm_disable_tcxo
*
* 功能描述  : 关闭TCXO
*
* 输入参数  : PWC_COMM_MODEM_E  enModemId  卡号
*             PWC_COMM_MODE_E enModeType   协议模式
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_disable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);

/*****************************************************************************
* 函 数 名  : mdrv_pm_start_tcxo_timer
*
* 功能描述  : 启动专用于TCXO的定时器
*
* 输入参数  : PWC_COMM_MODEM_E  enModemId 卡号
*             PWC_COMM_MODE_E enModeType  协议模式
*             PWC_TCXO_FUNCPTR routine   回调函数
*             int arg                    回调函数传回的参数
*             unsigned int timerValue    定时器时间(单位：ms)
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
typedef int (*PWC_TCXO_FUNCPTR)(int);
int mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_TCXO_FUNCPTR routine,int arg, unsigned int timerValue);

/*****************************************************************************
* 函 数 名  : mdrv_pm_get_tcxo_rfclk_status
*
* 功能描述  : 查询RF CLK状态
*
* 输入参数  : PWC_COMM_CHANNEL_E enChannel  channel ID
* 输出参数  :
*
* 返 回 值  : PWRCTRL_COMM_ON 打开状态
*             PWRCTRL_COMM_OFF 关闭状态
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_tcxo_rfclk_status (PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_enable_tcxo_rfclk
*
* 功能描述  : 打开RF CLK
*
* 输入参数  : PWC_COMM_MODEM_E  enModemId  卡号
*             PWC_COMM_MODE_E enModeType    模式
*             PWC_COMM_CHANNEL_E enChannel  channel ID
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_enable_tcxo_rfclk (PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_disable_tcxo_rfclk
*
* 功能描述  : 关闭RF CLK
*
* 输入参数  : PWC_COMM_MODEM_E  enModemId  卡号
*             PWC_COMM_MODE_E enModeType    模式
*             PWC_COMM_CHANNEL_E enChannel  channel ID
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_disable_tcxo_rfclk (PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_get_dfs_profile
*
* 功能描述  : 获取当前的profile值
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 当前处于哪个profile
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_dfs_profile(void);

/*****************************************************************************
* 函 数 名  : mdrv_pm_set_dfs_profile
*
* 功能描述  : 设置要调整的目标profile
*
* 输入参数  : int profile  需要设定的profile值
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_set_dfs_profile(int profile);

/*****************************************************************************
* 函 数 名  : mdrv_pm_set_dfs_baseprofile
*
* 功能描述  : 设置调频profile值下限
*
* 输入参数  : int profile  需要设定的profile下限值
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_set_dfs_baseprofile(int profile);


/*****************************************************************************
* 函 数 名  : mdrv_pm_lock_dfs
*
* 功能描述  : 锁定cpufreq主动调频功能
*
* 输入参数  : bool lock Lock=0 锁定调频功能;Lock=1 解锁调频功能
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
void mdrv_pm_lock_dfs(unsigned int lock);

/*****************************************************************************
* 函 数 名  : mdrv_pm_set_dfs_target
*
* 功能描述  : 设置要调整的频率值
*
* 输入参数  : int a9freq   需要设定的cpu频率值
*             int ddrfreq  需要设定的ddr频率值
*             int slowfreq 需要设定的slowbus频率
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_set_dfs_target(int a9freq, int ddrfreq, int slowfreq);

/*****************************************************************************
* 函 数 名  : mdrv_pm_enable_bbpclk
*
* 功能描述  : 通信模块控制BBP时钟使能接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号

* 输出参数  :
*
* 返 回 值  :  0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_enable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_disable_bbpclk
*
* 功能描述  : 通信模块控制BBP时钟关闭接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_disable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* 函 数 名  : mdrv_pm_set_wakesrc
*
* 功能描述  : 设置某个中断为唤醒源中断
*
* 输入参数  : PM_WAKE_SRC_E wake_src 需要设置的唤醒源
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
void mdrv_pm_set_wakesrc(PM_WAKE_SRC_E wake_src);

/*****************************************************************************
* 函 数 名  : mdrv_pm_clear_wakesrc
*
* 功能描述  : 取消设置某个中断为唤醒源中断
*
* 输入参数  : PM_WAKE_SRC_E wake_src 需要设置的唤醒源
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
void mdrv_pm_clear_wakesrc(PM_WAKE_SRC_E wake_src);

/*****************************************************************************
 *  函 数 名  : mdrv_pm_wake_lock
 *  功能描述  : 外设允许睡眠投票接口。
 *  输入参数  : lock_id id
 *  输出参数  : None
 *  返 回 值  : 无
 ******************************************************************************/
unsigned int mdrv_pm_wake_lock(PWC_CLIENT_ID_E id);

/*****************************************************************************
 *  函 数 名  : mdrv_pm_wake_unlock
 *  功能描述  : 外设允许睡眠投票接口。
 *  输入参数  : lock_id id
 *  输出参数  : None
 *  返 回 值  : 无
 ******************************************************************************/
unsigned int mdrv_pm_wake_unlock(PWC_CLIENT_ID_E id);

/*****************************************************************************
* 函 数 名  : mdrv_pm_register_sleep_ops
*
* 功能描述  : 提供给上层注册回调函数，在系统睡眠/唤醒时调用。
*
* 输入参数  : 
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_register_sleep_ops(unsigned char* pname,PWC_SLEEP_FUNCPTR suspend,PWC_SLEEP_FUNCPTR resume);
/*****************************************************************************
* 函 数 名  : mdrv_pm_unregister_sleep_ops
*
* 功能描述  : 取消回调的注册(该接口暂不要调用)
*
* 输入参数  : 
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_unregister_sleep_ops(unsigned char* pname);
#ifdef __cplusplus
}
#endif
#endif
