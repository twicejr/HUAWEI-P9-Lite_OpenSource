/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  memrepair_debug.c
*
*   作    者    :  x00195528
*
*   描    述    :  本文件主要实现modem memrepair debug
*
*   修改记录 :  2015年10月12日 创建
*************************************************************************/
#include <product_config.h>
#include <securec.h>
#include <osl_types.h>
#include <bsp_sysctrl.h>
#include <bsp_om.h>
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_version.h>
#include <bsp_hw_spinlock.h>
#include <bsp_memrepair.h>

#include <memrepair_balong.h>

#ifdef __OS_RTOSCK__
#define mr_print_dbg SRE_Printf
#else
#define mr_print_dbg(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEMREPAIR, fmt,##__VA_ARGS__))
#endif

#ifdef MODEM_MEM_REPAIR

extern struct memrepair_info g_memrepair;

/*****************************************************************************
* 函 数 : memrepair_log_set
* 功 能 : memrepair 相关打印等级设置
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void memrepair_log_set(u32 level)
{
    /*todo xuwenfang*/
    (void)bsp_mod_level_set(BSP_MODU_MEMREPAIR, level);
    mr_print_dbg("bbp log id=%d, set to level=%d)\n",BSP_MODU_MEMREPAIR,level);
}
/*****************************************************************************
* 函 数 : memrepair_log_get
* 功 能 : 获取memrepair 相关打印等级
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void memrepair_log_get(void)
{
    u32 log_level = 0;

    log_level = bsp_log_module_cfg_get(BSP_MODU_MEMREPAIR);
    mr_print_dbg("bbp log id=%d, level=%d\n",BSP_MODU_MEMREPAIR,log_level);
}

/*****************************************************************************
* 函 数 : memrepair_info_show
* 功 能 : 获取memrepair 的修复次数及修复时间信息
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void memrepair_info_show(void)
{
    int moudle = 0;

    mr_print_dbg("%-10s %-20s %-20s\n","moudle_id","repair_cnts","time_cost");
    for(moudle = MODEM_MEMREPAIR_DSP;moudle < MODEM_MEMREPAIR_BUTT;moudle++)
    {
        mr_print_dbg("%-10d 0x%-20x 0x%-20x\n",moudle,g_memrepair.info[moudle].cnts,g_memrepair.info[moudle].time);
    }
}
/*****************************************************************************
* 函 数 : bad_mem_check
* 功 能 : 坏块检测
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
int bad_mem_check(u32 addr, u32 value, u32 len)
{
    u32 reg_value = 0;
    int iret = 0;
    u32 i = 0;

    (void)memset_s((void *)addr,len,(int)value,len);
    for(i = 0;i < len;)
    {
        reg_value = (u32)readl(addr + i);
        if(reg_value != value)
        {
            mr_print_dbg("bad mem addr 0x%x,value is 0x%x,should be 0x%x. \n",addr+i,reg_value,value);
            iret = -1;
        }
        i+=4;
    }
    /*对value取反，再检测一次*/
    value = ~value;

    (void)memset_s((void *)addr,len,(int)value,len);
    for(i = 0;i < len; )
    {
        reg_value = (u32)readl(addr + i);
        if(reg_value != value)
        {
            mr_print_dbg("bad mem addr 0x%x,value is 0x%x,should be 0x%x. \n",addr+i,reg_value,value);
            iret = -1;
        }
        i+=4;
    }

    mr_print_dbg("mem check finsh.\n");

    return iret;
}
/*****************************************************************************
* 函 数 : module_memrepair_test
* 功 能 : 坏块检测
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void module_memrepair_test(modem_memrepair_ip module,u32 addr, u32 value, u32 len)
{
    int iret = 0;

    /*先检测是否有坏点*/
    iret = bad_mem_check(addr,value,len);
    if(!iret)
    {
        mr_print_dbg("bbp irm memory have no bad mem.\n");
    }
    else
    {
        /*执行memrepair*/
        iret = bsp_modem_memrepair(module);
        if(iret)
        {
            mr_print_dbg("repair error!\n");
        }
        /*重新检测坏点*/
        iret = bad_mem_check(addr,value,len);
        if(iret)
        {
            mr_print_dbg("repair failed,mem still bad!\n");
        }
        else
        {
            mr_print_dbg("repair ok!\n");
        }
    }
}

int bsp_modem_memrepair_test(void)
{
    int iret = 0;

#if 0
    /**/
    iret = module_memrepair_test(MODEM_MEMREPAIR_DSP,);
    iret |= module_memrepair_test(MODEM_MEMREPAIR_BBPIRM,);
    iret |= module_memrepair_test(MODEM_MEMREPAIR_BBPCOM,);
    iret |= module_memrepair_test(MODEM_MEMREPAIR_BBPCS,);
    mr_print_error("test finsh.\n");
#endif
    return iret;
}
/*****************************************************************************
* 函 数 : memrepair_flag_onoff
* 功 能 : 打开memrepair或者不打开
* 输 入 : onoff:0--memrepair;1--not repair
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void memrepair_flag_onoff(int onoff)
{
    g_memrepair.flag = onoff;
}
/*****************************************************************************
* 函 数 : memrepair_help
* 功 能 : 函数说明
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void memrepair_help(void)
{
    mr_print_dbg("show debug info       : memrepair_info_show (void)!\n");
    mr_print_dbg("check mem bad or not  : bad_mem_check (addr,value,len)!\n");
    mr_print_dbg("test module repair    : module_memrepair_test(module,addr,value,len)!\n");
    mr_print_dbg("get_memrepair_bit     : get_memrepair_bit(module)!\n");
    mr_print_dbg("is_need_memrepair     : modem_is_need_memrepair (module)!\n");
    mr_print_dbg("memrepair  func       : bsp_modem_memrepair (module)!\n");
    mr_print_dbg("memrepair  time       : bsp_get_memrepair_time (void)!\n");
    mr_print_dbg("log level  set        : memrepair_log_set (level)!\n");
    mr_print_dbg("log level  get        : memrepair_log_get (void)!\n");
    mr_print_dbg("onoff repair function : memrepair_flag_onoff (onoff)!\n");
}
#endif

