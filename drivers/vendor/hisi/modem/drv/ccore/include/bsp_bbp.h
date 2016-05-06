/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_bbp.h
*
*   作    者 :
*
*   描    述 :  本文件主要提供给其他模块(包括上层和底软其他模块)的接口定义
*
*   修改记录 :
*************************************************************************/
#ifndef _BSP_BBP_H_
#define _BSP_BBP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"
#include "mdrv_bbp.h"
#include "mdrv_pm.h"

typedef enum{
    BBP_PART_TOP = 0,
    BBP_DMA = 0,
    BBP_UL,/*1*/
    BBP_INT,/*2*/
    BBP_LSTU,/*3*/
    BBP_TSTU,/*4*/
    BBP_CTU,/*5*/
    BBP_ABB,/*6*/
    BBP_SCTRL,/*7*/
    BBP_LDRX,/*8*/
    BBP_TDRX,/*9*/
    BBP_WBBP,/*10*/
    BBP_CROSS_MIPI_MEM,/*11*/
    BBP_CROSS_MIPI_CTRL,/*12*/
    BBP_CDRX,/*13*/
    BBP_G0BBP,/*14*/
    BBP_G1BBP,/*15*/
    BBP_UCBBP,/*16*/
    BBP_PART_BUTT
}BBP_PART_ID_E;

struct bbp_dma_cfg
{
    u32 chan;/*使用的通道号*/
    u32 bbp_addr;/*需要搬移的起始地址*/
    u32 soc_addr;/*需要搬移的目的地址*/
    u32 size;    /* 需要存储的连续寄存器空间大小，单位为byte */
    u32 type;   /*0:数据从SOC空间搬移到BBP空间，1:从BBP空间搬移到SOC空间*/
};

/*函数声明*/
/*****************************************************************************
* 函 数 : bsp_bbp_power_status
* 功 能 : dpm模块调用，用于查看bbp模块上下电状态
* 输 入 : 模式，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/*****************************************************************************
* 函 数 : bsp_bbp_power_up
* 功 能 : dpm模块调用，用于给bbp模块上电
* 输 入 : 模式，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_up(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/*****************************************************************************
* 函 数 : bsp_bbp_power_down
* 功 能 : dpm模块调用，用于给bbp模块下电
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_down(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_status
* 功 能 : dpm模块调用，用于获取bbp pll 状态
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_enable
* 功 能 : dpm模块调用，用于打开bbp pll
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_enable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_disable
* 功 能 : dpm模块调用，用于关闭bbp pll
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_disable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/***************************************************************************
 函 数 名  : bsp_bbp_enable_bbpclk()
 功能描述  : 打开bbp相关时钟
 输入参数  : enModeId      协议模式
    	     enModuleId    操作模块
    	     enModemId     卡号
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int bsp_bbp_clk_enable (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/***************************************************************************
 函 数 名  : bsp_bbp_clk_disable()
 功能描述  : 通信模块控制BBP模块关钟
 输入参数  : enModeId      协议模式
    	     enModuleId    操作模块
    	     enModemId     卡号
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int bsp_bbp_clk_disable (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/*****************************************************************************
* 函 数 : bsp_bbp_get_wakeup_time
* 功 能 : 被低功耗调用，用来查询睡眠超时时刻
* 输 入 : void
* 输 出 : void
* 返 回 : bbp睡眠剩余时间，单位为32.768KHz时钟计数
* 说 明 : 不关心哪个模还有多长时间被告唤醒，
		    只返回最小的时间
*****************************************************************************/
u32 bsp_bbp_get_wakeup_time(void);
/*****************************************************************************
* 函 数 : bsp_bbp_get_gubbp_wakeup_status
* 功 能 : pm模块调用
* 输 入 : void
* 输 出 : void
* 返 回 : 当前时间
* 说 明 :
*****************************************************************************/
u32 bsp_bbp_get_gubbp_wakeup_status(void);
/*****************************************************************************
* 函 数 : bsp_bbp_part_addr_get
* 功 能 : bbp 各模块基地址获取
* 输 入 : void
* 输 出 : void
* 返 回 : 使用bbp空间的模块调用
* 说 明 :
*****************************************************************************/
void* bsp_bbp_part_addr_get(BBP_PART_ID_E part_id);

/*****************************************************************************
* 函 数 : bsp_bbp_dma_tran
* 功 能 : 使用bbp dma进行数据搬移
* 输 入 : 目标地址、源地址、类型
* 输 出 : vo
* 返 回 :
* 说 明 :
*****************************************************************************/
void bsp_bbp_dma_tran(struct bbp_dma_cfg *dma_config);

/*****************************************************************************
* 函 数 : bsp_bbp_dma_finish
* 功 能 : 等待bbp dma搬移完成
* 输 入 : 目标地址、源地址、类型
* 输 出 : vo
* 返 回 :
* 说 明 :
*****************************************************************************/
void bsp_bbp_dma_finish(struct bbp_dma_cfg *dma_config);

/*****************************************************************************
* 函 数 : bsp_bbp_init
* 功 能 : bbp 初始化
* 输 入 : void
* 输 出 : void
* 返 回 : 启动模块调用
* 说 明 :
*****************************************************************************/
s32 bsp_bbp_init(void);




#ifdef __cplusplus
}
#endif

#endif /*end #ifndef _BSP_BBP_H_*/


