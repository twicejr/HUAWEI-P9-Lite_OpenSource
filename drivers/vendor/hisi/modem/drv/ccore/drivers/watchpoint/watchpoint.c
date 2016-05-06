/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  watchpoint.c
*
*   作    者 :  z67193
*
*   描    述 :  临终遗言功能
*
*   修改记录 :  2012年12月11日  v1.00  z67193  创建
*************************************************************************/

#include "osl_malloc.h"
#include "securec.h"
#include "sre_exc.h"
#include "bsp_dump.h"
#include "bsp_dpm.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_nvim.h"
#include "mdrv.h"
#include "watchpoint.h"

wp_ctrl_t   g_wp_ctrl;
wp_reg_back_t   g_wp_backup;

/*lint -save -e123 -e586 */
#define WP_CHECK_INIT() \
    do{\
        if(false == g_wp_ctrl.init_flag)\
        {\
            wp_print("watchpoint not init\n");\
            return BSP_ERROR;\
        }\
    }while(0)

#define WP_CHECK_ID(wp_id) \
    do{\
        if(((u32)wp_id > g_wp_ctrl.wp_cnt - 1) || (g_wp_ctrl.wp_info[wp_id].alloc != WATCHPOINT_ALLOCED))\
        {\
            wp_print("invalid watchpoint id<0x%x>\n", wp_id);\
            return BSP_ERROR;\
        }\
    }while(0)
    
/*****************************************************************************
 函 数 名  : read_wp_reg
 功能描述  : 读取指定watchpoint寄存器
 输入参数  : n，寄存器编号
 输出参数  : 无
 返 回 值  : u32, 读取到寄存器值
*****************************************************************************/
u32 read_wp_reg(int n)
{
	u32 val = 0;

	switch (n)
    {
	    GEN_WP_READ_REG_CASES(ARM_OP2_WVR, val);
	    GEN_WP_READ_REG_CASES(ARM_OP2_WCR, val);
	    default:
		    wp_print("attempt to read from unknown breakpoint register %d\n", n);
	}

	return val;
}

/*****************************************************************************
 函 数 名  : write_wp_reg
 功能描述  : 写入指定watchpoint寄存器
 输入参数  : n，寄存器编号, val, 待写入值
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void write_wp_reg(int n, u32 val)
{
	switch (n)
    {
	    GEN_WP_WRITE_REG_CASES(ARM_OP2_WVR, val);
	    GEN_WP_WRITE_REG_CASES(ARM_OP2_WCR, val);
	    default:
		    wp_print("attempt to write to unknown breakpoint register %d\n", n);
	}
	asm volatile("isb" : : : "memory");
}

/*****************************************************************************
 函 数 名  : encode_ctrl_reg
 功能描述  : 构建WCR
 输入参数  : ctrl, WCR配置
 输出参数  : 无
 返 回 值  : 待写入WCR的值
*****************************************************************************/
u32 wp_encode_ctrl_reg(watchpoint_ctrl ctrl)
{
    return (ctrl.addr_range << 24) | (ctrl.len << 5) | (ctrl.type << 3) | (ctrl.privilege << 1) | ctrl.enabled;
}

/*****************************************************************************
 函 数 名  : get_addr_range
 功能描述  : 根据起始、结束地址，计算WCR地址范围掩码
 输入参数  : start_addr,监控起始地址；end_addr, 监控结束地址
 输出参数  : 无
 返 回 值  : 待写入WCR地址掩码值
*****************************************************************************/
u32 get_addr_range(u32 start_addr, u32 end_addr)
{
    u32 i;
    u32 mask;

    /* 计算start_addr, end_addr公共前缀长度 */
    for(i=0; i<32; i++)
    {
        mask = (u32)1 << (31 - i);
        if((start_addr & mask) != (end_addr & mask))
        {
            break;
        }
    }

    return 32 - i;
}

/*****************************************************************************
 函 数 名  : wp_alloc_node
 功能描述  : 分配节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回未分配watchpoint id，若已经分配完，返回-1
*****************************************************************************/
s32 wp_alloc_node(void)
{
    unsigned long lock_flag;
    u32 i;

    spin_lock_irqsave(&g_wp_ctrl.lock, lock_flag);
    for(i=0; i<g_wp_ctrl.wp_cnt; i++)
    {
        if(g_wp_ctrl.wp_info[i].alloc == WATCHPOINT_UNALLOC)
        {
            g_wp_ctrl.wp_info[i].alloc = WATCHPOINT_ALLOCED;
            spin_unlock_irqrestore(&g_wp_ctrl.lock, lock_flag);
            return (s32)i;
        }
    }

    spin_unlock_irqrestore(&g_wp_ctrl.lock, lock_flag);
    wp_print("all watchpoint nodes alloced\n");
    return BSP_ERROR;
}

/*****************************************************************************
 函 数 名  : wp_free_node
 功能描述  : 释放节点
 输入参数  : wp_id，watchpoint id
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void wp_free_node(s32 wp_id)
{
    unsigned long lock_flag;

    spin_lock_irqsave(&g_wp_ctrl.lock, lock_flag);
    (void)memset_s(&g_wp_ctrl.wp_info[wp_id], sizeof(wp_info_t), 0, sizeof(wp_info_t));
    spin_unlock_irqrestore(&g_wp_ctrl.lock, lock_flag);
}

/*****************************************************************************
 函 数 名  : wp_exc_callback
 功能描述  : dump异常向量钩子函数，watchpoint异常触发data abort
 输入参数  : exc_info, 异常向量信息
 输出参数  : 无
 返 回 值  : true，退出dump异常向量处理; false, 继续dump异常处理
*****************************************************************************/
bool wp_exc_callback(void * exc_info)
{
    EXC_INFO_S * info = (EXC_INFO_S *)exc_info;
    EXC_REGS_S * regs = (EXC_REGS_S *)&(((EXC_INFO_S *)exc_info)->stRegInfo);
    char data[100];
    unsigned len;
    u32 dfsr = 0;
    u32 fs_bit = 0;

    /* watchpoint触发data abort异常 */
    if(info->uwExcCause != OS_EXCEPT_DATA_ABORT)
    {
        return false;
    }

    /* read data fault status register */
    asm volatile("mrc p15, 0, %0, c5, c0, 0" : "=r" (dfsr));
    /* fs[10], fs[3:0] */
    fs_bit = (dfsr & 0xf) | ((dfsr & (1 << 10)) >> 6);
    /*lint -save -e774 */
    /* debug event encode == 0b00010 */
    if(fs_bit != 2)
    {
        return false;
    }
    /*lint -restore */

    (void)memset_s(data, 100, 0, 100);
    len = (unsigned)sprintf_s(data, 100, "********wachpoint error begin********\n");
    (void)dmesg_write(data, len);

	len = (unsigned)sprintf_s(data, 100, "pc : [<%08lx>]    lr : [<%08lx>]    psr: %08lx\n", regs->uwPC, regs->uwLR, regs->uwCPSR);
    (void)dmesg_write(data, len);

    len = (unsigned)sprintf_s(data, 100, "sp : %08lx  ip : %08lx  fp : %08lx\n", regs->uwSP, regs->uwR12, regs->uwR11);
    (void)dmesg_write(data, len);

	len = (unsigned)sprintf_s(data, 100, "r10: %08lx  r9 : %08lx  r8 : %08lx\n", regs->uwR10, regs->uwR9, regs->uwR8);
    (void)dmesg_write(data, len);

	len = (unsigned)sprintf_s(data, 100, "r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx\n", regs->uwR7, regs->uwR6, regs->uwR5, regs->uwR4);
    (void)dmesg_write(data, len);

	len = (unsigned)sprintf_s(data, 100, "r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx\n", regs->uwR3, regs->uwR2, regs->uwR1, regs->uwR0);
    (void)dmesg_write(data, len);

    len = (unsigned)sprintf_s(data, 100, "********wachpoint error end**********\n");
    (void)dmesg_write(data, len);

    g_wp_ctrl.wp_hit_cnt++;
    system_error(DRV_ERRNO_WATCHPOINT, regs->uwPC, regs->uwLR, 0, 0);
    return true;
}

/*****************************************************************************
 函 数 名  : wp_register
 功能描述  : watchpoint注册非正式接口，用于串口调用临时使用
 输入参数  : type, 读、写；start_addr, 起始地址；end_addr,结束地址，监控单个地址填0
 输出参数  : 无
 返 回 值  : 成功返回分配的watchpoint id，失败返回-1
*****************************************************************************/
s32 wp_register(u32 type, u32 start_addr, u32 end_addr)
{
    wp_cfg_t cfg;

    cfg.enable = WATCHPOINT_ENABLE;
    cfg.type = type;
    cfg.start_addr = start_addr;
    cfg.end_addr = end_addr;

    return bsp_wp_register(&cfg);
}

/*****************************************************************************
 函 数 名  : bsp_wp_register
 功能描述  : watchpoint注册接口，配置监控地址
 输入参数  : cfg，watchpoint配置信息
 输出参数  : 无
 返 回 值  : 成功返回分配的watchpoint id，失败返回-1
*****************************************************************************/
s32 bsp_wp_register(wp_cfg_t * cfg)
{
    s32 wp_id;
    watchpoint_ctrl ctrl;
    u32 ctrl_reg;

    WP_CHECK_INIT();

    if(NULL == cfg)
    {
        wp_print("input cfg is null\n");
        return BSP_ERROR;
    }

    if((cfg->start_addr & 0x3) != 0)
    {
        wp_print("start addr<0x%x> is not 4 bytes align\n", cfg->start_addr);
        return BSP_ERROR;
    }

    if((cfg->type & WATCHPOINT_RW) == 0)
    {
        wp_print("invalid acceess type<0x%x>\n", cfg->type);
        return BSP_ERROR;
    }

    if((cfg->start_addr > cfg->end_addr) && (cfg->end_addr != 0))
    {
        wp_print("end addr<0x%x> is smaller than start addr<0x%x>\n", cfg->end_addr, cfg->start_addr);
        return BSP_ERROR;
    }

    wp_id = wp_alloc_node();
    if(wp_id == BSP_ERROR)
    {
        wp_print("there's no watchpoint valid\n");
        return BSP_ERROR;
    }
    (void)memcpy_s(&g_wp_ctrl.wp_info[wp_id].cfg, sizeof(wp_cfg_t), cfg, sizeof(wp_cfg_t));

    (void)memset_s(&ctrl, sizeof(watchpoint_ctrl), 0, sizeof(watchpoint_ctrl));
    /* 监控地址写入WVR */
    write_wp_reg(ARM_BASE_WVR + wp_id, cfg->start_addr); 
    /* 监控start addr开始的4字节 */
    if((cfg->end_addr == 0) || (cfg->end_addr - cfg->start_addr < 4))
    {   
        ctrl.addr_range = 0;
    }
    /* 地址范围监控 */
    else
    {
        ctrl.addr_range = get_addr_range(cfg->start_addr, cfg->end_addr);
    }
    ctrl.len = WATCHPOINT_LEN_4;
    ctrl.privilege = WATCHPOINT_PRI;
    ctrl.type = cfg->type & WATCHPOINT_RW;
    ctrl.enabled = cfg->enable;
    ctrl_reg = wp_encode_ctrl_reg(ctrl);
    /* 监控配置写入WCR */
    write_wp_reg(ARM_BASE_WCR + wp_id, ctrl_reg);

    return wp_id;
}

/*****************************************************************************
 函 数 名  : bsp_wp_enable
 功能描述  : 使能watchpoint
 输入参数  : wp_id, bsp_wp_register获取到的watchpoint id
 输出参数  : 无
 返 回 值  : 成功返回0，失败返回-1
*****************************************************************************/
s32 bsp_wp_enable(s32 wp_id)
{
    u32 ctrl_reg;

    WP_CHECK_INIT();
    WP_CHECK_ID(wp_id);

    ctrl_reg = read_wp_reg(ARM_BASE_WCR + wp_id);
    /* WCR bit0:enable */
    ctrl_reg = ctrl_reg | (1 << 0);
    write_wp_reg(ARM_BASE_WCR + wp_id, ctrl_reg);
    g_wp_ctrl.wp_info[wp_id].cfg.enable = WATCHPOINT_ENABLE;

    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : bsp_wp_disable
 功能描述  : 去使能watchpoint
 输入参数  : wp_id, bsp_wp_register获取到的watchpoint id
 输出参数  : 无
 返 回 值  : 成功返回0，失败返回-1
*****************************************************************************/
s32 bsp_wp_disable(s32 wp_id)
{
    u32 ctrl_reg;

    WP_CHECK_INIT();
    WP_CHECK_ID(wp_id);

    ctrl_reg = read_wp_reg(ARM_BASE_WCR + wp_id);
    /* WCR bit0:enable */
    ctrl_reg = ctrl_reg & ~(1 << 0);
    write_wp_reg(ARM_BASE_WCR + wp_id, ctrl_reg);
    g_wp_ctrl.wp_info[wp_id].cfg.enable = WATCHPOINT_DISABLE;

    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : bsp_wp_unregister
 功能描述  : 释放watchpoint
 输入参数  : wp_id, bsp_wp_register获取到的watchpoint id
 输出参数  : 无
 返 回 值  : 成功返回0，失败返回-1
*****************************************************************************/
s32 bsp_wp_unregister(s32 wp_id)
{
    WP_CHECK_INIT();
    WP_CHECK_ID(wp_id);

    if(g_wp_ctrl.wp_info[wp_id].cfg.enable == WATCHPOINT_ENABLE)
    {
        (void)bsp_wp_disable(wp_id);
    }

    wp_free_node(wp_id);
    return BSP_OK;
}

#ifdef CONFIG_CCORE_PM
int wp_suspend(struct dpm_device *dev)
{
    u32 i;

    if(g_wp_ctrl.init_flag != true)
    {
        return BSP_OK;
    }

    for(i=0; i<g_wp_ctrl.wp_cnt; i++)
    {
        g_wp_backup.wvr_reg[i] = read_wp_reg((int)(ARM_BASE_WVR + i));
        g_wp_backup.wcr_reg[i] = read_wp_reg((int)(ARM_BASE_WCR + i));
    }

    WP_DBG_READ(c1, 0, g_wp_backup.dscr);

    return BSP_OK;
}

int wp_resume(struct dpm_device *dev)
{
    u32 i;

    if(g_wp_ctrl.init_flag != true)
    {
        return BSP_OK;
    }

    WP_DBG_WRITE(c2, 2, g_wp_backup.dscr);

    for(i=0; i<g_wp_ctrl.wp_cnt; i++)
    {
        write_wp_reg((int)(ARM_BASE_WVR + i), g_wp_backup.wvr_reg[i]);
        write_wp_reg((int)(ARM_BASE_WCR + i), g_wp_backup.wcr_reg[i]);
    }
  
    return BSP_OK;
}

struct dpm_device g_wp_dpm_dev ={
    .device_name = "watchpoint_dpm",
    .suspend_late = wp_suspend,
    .resume_early = wp_resume,
};
#endif

/*lint -save -e438 -e830 */
/*****************************************************************************
 函 数 名  : wp_init
 功能描述  : watchpoint模块初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回0，失败返回-1
*****************************************************************************/
s32 bsp_wp_init(void)
{
    u32 wp_count = 0;
    void * wp_cfg;
    u32 wp_size;
    u32 dscr = 0;
    u32 i;
    DRV_WATCHPOINT_CFG_STRU cfg;

    if(g_wp_ctrl.init_flag == true)
    {
        return BSP_OK;
    }

    /* read from DBGDIDR */
    WP_DBG_READ(c0, 0, wp_count);
    /* DBGDIDR bit31~28, wrp count */
    wp_count = ((wp_count >> 28) & 0xF) + 1;

    g_wp_ctrl.wp_cnt = wp_count;
    wp_size = sizeof(wp_info_t) * wp_count;
    wp_cfg = osl_malloc(wp_size);
    if(NULL == wp_cfg)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }
    (void)memset_s(wp_cfg, wp_size, 0, wp_size);
    g_wp_ctrl.wp_info = (wp_info_t *)wp_cfg;
    spin_lock_init(&g_wp_ctrl.lock);

    /* enable monitor mode, clear halting mode */
    WP_DBG_READ(c1, 0, dscr);
    dscr = dscr | ARM_DSCR_MDBGEN;
    dscr = dscr & ~(ARM_DSCR_HDBGEN);
    WP_DBG_WRITE(c2, 2, dscr);

    (void)dump_exc_register(wp_exc_callback);

#ifdef CONFIG_CCORE_PM
    if(BSP_OK != bsp_device_pm_add(&g_wp_dpm_dev))
    {
        wp_print("regiser dpm fail\n");
        return BSP_ERROR;
    }
#endif

    g_wp_ctrl.wp_hit_cnt = 0;
    g_wp_ctrl.init_flag  = true;

    /* 读取NV初始配置 */
    if(BSP_OK != bsp_nvm_read(NV_ID_DRV_WATCHPOINT, (u8 *)&cfg, sizeof(DRV_WATCHPOINT_CFG_STRU)))
    {
        wp_print("read nv 0x%x error\n", NV_ID_DRV_WATCHPOINT);
        return MDRV_ERROR;
    }

    for(i=0; i<4; i++)
    {
        if(i >= g_wp_ctrl.wp_cnt)
        {
            break;
        }

        if(cfg.cp_cfg[i].enable == WATCHPOINT_ENABLE)
        {
            g_wp_ctrl.wp_info[i].cfg.enable = WATCHPOINT_ENABLE;
            g_wp_ctrl.wp_info[i].cfg.type   = cfg.cp_cfg[i].type;
            g_wp_ctrl.wp_info[i].cfg.start_addr = cfg.cp_cfg[i].start_addr;
            g_wp_ctrl.wp_info[i].cfg.end_addr   = cfg.cp_cfg[i].end_addr;
            (void)bsp_wp_register(&(g_wp_ctrl.wp_info[i].cfg));
        }
    }

    wp_print("watchpoint init ok\n");
    return BSP_OK;
}

/* clear halting mode */
void wp_clr_hdbg(void)
{
    u32 dscr = 0;

    WP_DBG_READ(c1, 0, dscr);
    dscr = dscr & ~(ARM_DSCR_HDBGEN);
    WP_DBG_WRITE(c2, 2, dscr);
}
/*lint -restore */

void wp_show(void)
{
    u32 i;
    u32 wvr_reg;
    u32 wcr_reg;

    wp_print("**********wachpoint info**********\n");
    for(i=0; i<g_wp_ctrl.wp_cnt; i++)
    {
        wvr_reg = read_wp_reg((int)(ARM_BASE_WVR + i));
        wcr_reg = read_wp_reg((int)(ARM_BASE_WCR + i));
        wp_print("ID      : %u\n", i);
        wp_print("USAGE   : %s\n", (g_wp_ctrl.wp_info[i].alloc == WATCHPOINT_ALLOCED) ? "ALLOCED" : "UNALLOC");
        wp_print("STATUS  : %s\n", (g_wp_ctrl.wp_info[i].cfg.enable == WATCHPOINT_ENABLE) ? "ENABLE" : "DISABLE");
        wp_print("TYPE    : %s%s\n", (g_wp_ctrl.wp_info[i].cfg.type & WATCHPOINT_R) ? "<READ>" : "", (g_wp_ctrl.wp_info[i].cfg.type & WATCHPOINT_W) ? "<WRITE>" : "");
        wp_print("START   : 0x%x\n", g_wp_ctrl.wp_info[i].cfg.start_addr);
        wp_print("END     : 0x%x\n", g_wp_ctrl.wp_info[i].cfg.end_addr);
        wp_print("WVR     : 0x%x\n", wvr_reg);
        wp_print("WCR     : 0x%x\n", wcr_reg);
        wp_print("--------------------------\n");
    }
}

void wp_debug(void)
{
    u32 dscr = 0;

    WP_DBG_READ(c1, 0, dscr);
    wp_print("INIT STATUS       : %s\n", (g_wp_ctrl.init_flag == true) ? "INITED" : "NOT INIT");
    wp_print("VALID WP COUNT    : %u\n", g_wp_ctrl.wp_cnt);
    wp_print("WP HIT COUNT      : %u\n", g_wp_ctrl.wp_hit_cnt);
    wp_print("DSCR REG          : 0x%x(%s %s)\n", dscr, (dscr & ARM_DSCR_MDBGEN) ? "MDBG EN" : "MDBG DIS", (dscr & ARM_DSCR_HDBGEN) ? "HDBG EN" : "HDBG DIS");
}
/*lint -restore */


