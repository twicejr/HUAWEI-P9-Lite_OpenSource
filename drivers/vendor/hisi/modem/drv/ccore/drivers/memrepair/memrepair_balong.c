/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  memrepair_balong.c
*
*   作    者    :  z00228752
*
*   描    述    :  本文件主要实现modem memrepair
*
*   修改记录 :  2014年3月12日 创建
*************************************************************************/
/*lint -save -e801*/
#include <product_config.h>
#include <osl_types.h>
#include <bsp_sysctrl.h>
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_version.h>
#include <bsp_hw_spinlock.h>
#include <bsp_memrepair.h>
#include <memrepair_balong.h>

#ifdef MODEM_MEM_REPAIR
#include <hi_memrepair.h>
#endif


struct memrepair_info g_memrepair;

#ifdef MODEM_MEM_REPAIR
unsigned int get_memrepair_bit(modem_memrepair_ip module)
{
    unsigned int bit;

    switch(module){
        case MODEM_MEMREPAIR_DSP:
            bit = MODEM_MEMREPAIR_DSP_BIT;
            break;
        case MODEM_MEMREPAIR_BBPIRM:
            bit = MODEM_MEMREPAIR_BBPIRM_BIT;
            break;
        case MODEM_MEMREPAIR_BBPCOM:
            bit = MODEM_MEMREPAIR_BBPCOM_BIT;
            break;
        case MODEM_MEMREPAIR_BBPCS:
            bit = MODEM_MEMREPAIR_BBPCS_BIT;
            break;
        default:
            bit = 0xffffffff;
            mr_print_error("not support this mrb %d!\n",module);
            break;
    }

    return bit;
}
bool modem_is_need_memrepair(modem_memrepair_ip module)
{
    unsigned int apsctrl_base = 0;
    u32 reg_value = 0;
    unsigned int bit;

    apsctrl_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_ao);
    reg_value = readl(apsctrl_base+0x34c);

    /*by_pass*/
    if(!(reg_value & (0x01UL << 31)))
    {
        mr_print_info("chip not need memrepair!\n");
        return false;
    }
    else
    {
        bit = get_memrepair_bit(module);
        /*mrb_n*/
        if(!(reg_value & (0x01UL << bit)))
        {
            mr_print_info("mrb not need memrepair!\n");
            return false;
        }
    }

    return true;
}
int modem_memrepair_hi3650(modem_memrepair_ip module)
{
    unsigned int apsctrl_base = 0;
    unsigned int reg_value = 0;
    unsigned int bit;
    unsigned int timestamp;
    unsigned int new_slice;
    int ret = 0;
    /*sram中申请了0x20个字节,modem可能单独复位，故用共享内存flag区分首次上电*/
    //unsigned long mr_poweron_flag_addr= SHM_MEM_MEMREPAIR_ADDR;
    unsigned int mr_poweron_flag_addr = 0;

    apsctrl_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_ao);
    reg_value = readl(apsctrl_base + 0x110);
    reg_value |= 0x1 << 26;
    reg_value |= 0x1 << 10;
    writel(reg_value,apsctrl_base + 0x110);
    udelay(1);//ndelay(50);
    writel(0x1 << 25,apsctrl_base + 0x030);
    udelay(1);
    reg_value = readl(apsctrl_base + 0x20c);
    reg_value &= ~(0x3 << 3);
    writel(reg_value,apsctrl_base + 0x20c);
    /**/
    reg_value = readl(apsctrl_base + 0x204);
    reg_value |= 0x1fffff;
    writel(reg_value,apsctrl_base + 0x204);
    udelay(1);
    /**/
    bit = get_memrepair_bit(module);

    reg_value = readl(apsctrl_base + 0x204);
    reg_value &= ~((u32)0x1<<bit);
    writel(reg_value,apsctrl_base + 0x204);
    udelay(5);

    mr_poweron_flag_addr = (unsigned int)(SHM_MEM_MEMREPAIR_ADDR + module*sizeof(int));
    /*5.若首次上电，则配置SYSCTRL中的SCPERCTRL3 (0x20C) bit4为1,指示修复数据来源EFUSE*/
    if(MR_POWERON_FLAG == readl(mr_poweron_flag_addr)){
        reg_value = readl(apsctrl_base + 0x100);
        reg_value |= (0x1 << 29);
        reg_value &= ~(0x1 << 13);
        writel(reg_value,apsctrl_base + 0x100);
        do
        {
            reg_value = (readl(apsctrl_base + 0x5c) & (0x1<<13));
        }while(!reg_value);

        reg_value = readl(apsctrl_base + 0x20c);
        reg_value |= (0x1 << 4);
        writel(reg_value,apsctrl_base + 0x20c);
        /*set first power on flag*/
        writel(MR_PWRED_FLAG,mr_poweron_flag_addr);
    }
    else if(MR_PWRED_FLAG == readl(mr_poweron_flag_addr)){
    /*6.非首次上电，则配置SYSCTRL中的SCPERCTRL3 (0x20C)bit3为1,指示修复数据来源sram*/
        reg_value = readl(apsctrl_base + 0x100);
        reg_value |= (0x1 << 29);
        reg_value |= (0x1 << 13);
        writel(reg_value,apsctrl_base + 0x100);
        do
        {
            reg_value = (readl(apsctrl_base + 0x5c) & (0x1<<13));
        }while(reg_value);

        reg_value = readl(apsctrl_base + 0x20c);
        reg_value |= (0x1 << 3);
        writel(reg_value,apsctrl_base + 0x20c);
    }
    else{/*内存被踩*/
        g_memrepair.errno |= (0x1 << 0);
        mr_print_error("shared ddr has been trampled!module id is %d\n",module);/*内存被踩，后面流程还要继续走吗?*/
    }

    timestamp = bsp_get_slice_value_hrt();
    do{
        reg_value = (readl(apsctrl_base + 0x228) & ((u32)0x1<<bit));
        new_slice = bsp_get_slice_value_hrt();
    }while((reg_value == 0)&&(get_timer_slice_delta(timestamp, new_slice) < MEMRAIR_START_TIMEOUT_SLICE));/*手册是30us，edit by x00195528*/
    if(reg_value == 0){
        g_memrepair.errno |= (0x1 << 1);
        mr_print_error("module %d memrepair not start, timeout,wait slice is %x\n",module,(new_slice - timestamp));
        /* coverity[no_escape] *//*是死循环，还是modem单独复位，或者可维可测信息?*/
        for(;;) ;
    }

    timestamp = bsp_get_slice_value_hrt();
    do{
        //bus_stat = get_hi_ap_sctrl_scmrbbusystat_mrb_efuse_busy() & (1<<bit);/*304*/
        reg_value = (readl(apsctrl_base + 0x304) & ((u32)0x1<<bit));
        new_slice = bsp_get_slice_value_hrt();
    }while((reg_value != 0)&&(get_timer_slice_delta(timestamp, new_slice) < MEMRAIR_DONE_TIMEOUT_SLICE));/*手册是300us，edit by x00195528*/

    if(reg_value != 0){
        g_memrepair.errno |= (0x1 << 2);
        mr_print_error("module %d wait memrepair busy bit timeout,wait slice is 0x%x\n",module,(new_slice - timestamp));
        /* coverity[no_escape] */
        for(;;) ;
    }

    reg_value = readl(apsctrl_base + 0x220);
    if(reg_value == 0)
    {
        mr_print_info("module %d memrepair done!\n",module);
        /*11. 配置SYSCTRL中的SCPERCTRL3(0x20c)bit 3 bit4为0*/
        reg_value = readl(apsctrl_base + 0x20c);
        reg_value &= ~(0x3 << 3);
        writel(reg_value,apsctrl_base + 0x20c);

        writel((0x1 << 25),apsctrl_base + 0x034);
        udelay(1);

        reg_value = readl(apsctrl_base + 0x110);
        reg_value |= (0x1 << 26);
        reg_value &= ~(0x1 << 10);
        writel(reg_value,apsctrl_base + 0x110);
    }
    else
    {
        g_memrepair.errno |= (0x1 << 3);
        mr_print_error("module %d memrepair failed, err reg value is 0x%x!\n",module,reg_value);
        /* coverity[no_escape] */
        for(;;) ;
    }

    return ret;
}

int bsp_modem_memrepair(modem_memrepair_ip module)
{
    int ret = 0;
    int hwspinlock_ret = 0;
    u32 time_begin = 0;
    u32 time_end = 0;

    time_begin = bsp_get_slice_value_hrt();

    if(MODEM_MEMREPAIR_BUTT <= module)
    {
        mr_print_error("not support this mrb %d!\n",module);
        return -1;
    }

    hwspinlock_ret = hwspin_lock_timeout(HW_MEMREPAIR_LOCKID,HW_SPINLOCK_WAIT_FOREVER);
    if( BSP_OK != hwspinlock_ret)
    {
        mr_print_error("module %d hwspin lock timeout !\n",module);
        /*save debug info,continue*/
    }

    if (false == modem_is_need_memrepair(module))
    {
        goto out;
    }

    if(!g_memrepair.flag)
    {
        g_memrepair.info[module].cnts++;

        switch(bsp_get_version_info()->chip_type)
        {
            case CHIP_K3V5:
                ret = modem_memrepair_hi3650(module);
                break;
            default:
                break;
        }
    }

out:
    hwspinlock_ret = hwspin_unlock(HW_MEMREPAIR_LOCKID);
    if(BSP_OK != hwspinlock_ret)
    {
        mr_print_error("module %d hwspin unlock timeout !\n",module);
    }

    time_end = bsp_get_slice_value_hrt();

    g_memrepair.info[module].time = (time_end - time_begin);

    return ret;
}

bool chip_is_need_repair(void)
{
    unsigned int apsctrl_base = 0;
    u32 reg_value = 0;

    apsctrl_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_ao);
    reg_value = readl(apsctrl_base+0x34c);

    /*by_pass*/
    if(!(reg_value & (0x01UL << 31)))
    {
        mr_print_info("chip not need memrepair!\n");
        return false;
    }

    return true;
}

int bsp_get_memrepair_time(void)
{
    if (true == chip_is_need_repair())
        return 900; /* us */
    else
        return 0;
}

#else

int bsp_modem_memrepair(modem_memrepair_ip module){
    return 0;
}

int bsp_get_memrepair_time(void)
{
    return 0;
}
#endif
/*lint -save -e537 -e656 -e801*/