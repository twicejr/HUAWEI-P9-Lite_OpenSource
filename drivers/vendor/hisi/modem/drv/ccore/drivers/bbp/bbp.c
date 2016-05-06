/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bbp.c
*
*   作    者    :  x00195528
*
*   描    述    :  本文件主要实现BBP 被底软其他模块调用的接口。
*                  BBP模块编译时为实际实现，否则都是打桩。
*
*   修改记录 :  2013年2月20日 创建
*************************************************************************/
/*lint -save -e537*/
#include "product_config.h"
#include <bsp_version.h>
#include "bsp_bbp.h"
#include "bbp_balong.h"

#ifdef CONFIG_BBP
/*底软其他模块调用接口*/
/*****************************************************************************
* 函 数 : bsp_bbp_power_status
* 功 能 : dpm模块调用，用于查看bbp模块上下电状态
* 输 入 : 模式，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return bbp_power_status(enModeId,enModuleId,enModemId);
}
/*****************************************************************************
* 函 数 : bsp_bbp_power_up
* 功 能 : dpm模块调用，用于给bbp模块上电
* 输 入 : 模式，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_up(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return bbp_power_up(enModeId,enModuleId,enModemId);
}
/*****************************************************************************
* 函 数 : bsp_bbp_power_down
* 功 能 : dpm模块调用，用于给bbp模块下电
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_down(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return bbp_power_down(enModeId,enModuleId,enModemId);
}
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_status
* 功 能 : dpm模块调用，用于获取bbp pll 状态
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return PWRCTRL_COMM_ON;
}
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_enable
* 功 能 : dpm模块调用，用于打开bbp pll
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_enable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_disable
* 功 能 : dpm模块调用，用于关闭bbp pll
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_disable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* 函 数 : bsp_bbp_get_wakeup_time
* 功 能 : 被底软低功耗调用，用来查询睡眠超时时刻
* 输 入 : void
* 输 出 : void
* 返 回 : bbp睡眠剩余时间，单位为32.768KHz时钟计数
* 说 明 : 低功耗不关心哪个模还有多长时间被告唤醒，
            只需要返回最小的时间即可
*****************************************************************************/
u32 bsp_bbp_get_wakeup_time(void)
{
    u32 l_time=0;
    u32 t_time=0;

    l_time = bbp_get_wakeup_time(PWC_COMM_MODE_LTE);
    t_time = bbp_get_wakeup_time(PWC_COMM_MODE_TDS);
    return l_time>t_time?t_time:l_time;
}
u32 bsp_bbp_get_gubbp_wakeup_status(void)
{
    return bbp_get_gubbp_wakeup_status();
}
/*****************************************************************************
* 函 数 : bsp_bbp_part_addr_get
* 功 能 : bbp 各模块基地址获取
* 输 入 : void
* 输 出 : void
* 返 回 : 使用bbp空间的模块调用
* 说 明 :
*****************************************************************************/
void* bsp_bbp_part_addr_get(BBP_PART_ID_E part_id)
{
    return bbp_part_addr_get(part_id);
}

/*****************************************************************************
* 函 数 : bsp_bbp_dma_tran
* 功 能 : 使用bbp dma进行数据搬移
* 输 入 : 目标地址、源地址、类型
* 输 出 : vo
* 返 回 :
* 说 明 :
*****************************************************************************/
void bsp_bbp_dma_tran(struct bbp_dma_cfg *dma_config)
{
    bbp_dma_tran(dma_config);
}

/*****************************************************************************
* 函 数 : bsp_bbp_dma_finish
* 功 能 : 等待bbp dma搬移完成
* 输 入 : 目标地址、源地址、类型
* 输 出 : vo
* 返 回 :
* 说 明 :
*****************************************************************************/
void bsp_bbp_dma_finish(struct bbp_dma_cfg *dma_config)
{
    bbp_dma_finish(dma_config);
}
/*****************************************************************************
* 函 数 : bsp_bbp_init
* 功 能 : bbp 初始化
* 输 入 : void
* 输 出 : void
* 返 回 : 启动模块调用
* 说 明 :
*****************************************************************************/
s32 bsp_bbp_init(void)
{
    return bbp_init();
}

/*不编译此模块打桩*/
#else

/*底软其他模块桩接口*/
/*****************************************************************************
* 函 数 : bsp_bbp_power_status
* 功 能 : dpm模块调用，用于查看bbp模块上下电状态
* 输 入 : 模式，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return 0;
}
/*****************************************************************************
* 函 数 : bsp_bbp_power_up
* 功 能 : dpm模块调用，用于给bbp模块上电
* 输 入 : 模式，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_up(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return 0;
}
/*****************************************************************************
* 函 数 : bsp_bbp_power_down
* 功 能 : dpm模块调用，用于给bbp模块下电
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0:成功；非0失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_power_down(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return 0;
}
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_status
* 功 能 : dpm模块调用，用于获取bbp pll 状态
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return PWRCTRL_COMM_ON;
}
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_enable
* 功 能 : dpm模块调用，用于打开bbp pll
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_enable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* 函 数 : bsp_bbp_dfs_disable
* 功 能 : dpm模块调用，用于关闭bbp pll
* 输 入 : 模式，模块，主副卡
* 输 出 : 无
* 返 回 : 0x20:关闭；0x10:开启
* 说 明 :
*****************************************************************************/
int bsp_bbp_dfs_disable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    return BBP_OK;
}
/*****************************************************************************
* 函 数 : bsp_bbp_get_wakeup_time
* 功 能 : 被低功耗调用，用来查询睡眠超时时刻
* 输 入 : void
* 输 出 : void
* 返 回 : bbp睡眠剩余时间，单位为32.768KHz时钟计数
* 说 明 : 低功耗不关心哪个模还有多长时间被告唤醒，
            只需要返回最小的时间即可
*****************************************************************************/
u32 bsp_bbp_get_wakeup_time(void)
{
    return 0xffffffff;
}
u32 bsp_bbp_get_gubbp_wakeup_status(void)
{
    return 0;
}
/*****************************************************************************
* 函 数 : bsp_bbp_part_addr_get
* 功 能 : bbp 各模块基地址获取
* 输 入 : void
* 输 出 : void
* 返 回 : 使用bbp空间的模块调用
* 说 明 :
*****************************************************************************/
void* bsp_bbp_part_addr_get(BBP_PART_ID_E part_id)
{
    return NULL;
}

/*****************************************************************************
* 函 数 : bsp_bbp_dma_tran
* 功 能 : 使用bbp dma进行数据搬移
* 输 入 : 目标地址、源地址、类型
* 输 出 : vo
* 返 回 :
* 说 明 :
*****************************************************************************/
void bsp_bbp_dma_tran(struct bbp_dma_cfg *dma_config)
{
    return;
}

/*****************************************************************************
* 函 数 : bsp_bbp_dma_finish
* 功 能 : 等待bbp dma搬移完成
* 输 入 : 目标地址、源地址、类型
* 输 出 : vo
* 返 回 :
* 说 明 :
*****************************************************************************/
void bsp_bbp_dma_finish(struct bbp_dma_cfg *dma_config)
{
    return;
}
/*****************************************************************************
* 函 数 : bsp_bbp_init
* 功 能 : bbp 初始化
* 输 入 : void
* 输 出 : void
* 返 回 : 模块裁剪时，打桩
* 说 明 :
*****************************************************************************/
s32 bsp_bbp_init(void)
{
    return 0;
}
#endif

/*lint -restore*/