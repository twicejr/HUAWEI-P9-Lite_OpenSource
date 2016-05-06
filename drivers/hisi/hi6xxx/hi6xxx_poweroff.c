

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Copyright (C) 2014 Hisilicon Limited
 */

#include <linux/init.h>
#include <linux/cpu_pm.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <linux/of_gpio.h>
#include <linux/err.h>
#include <linux/arm-cci.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/suspend.h>
#include <asm/cacheflush.h>
#include <asm/cputype.h>
#include <asm/psci.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <soc_baseaddr_interface.h>
#include <soc_gpio_interface.h>
#ifdef CONFIG_HISI_BB
#include <platform_ap/rdr_hisi_platform.h>
#include <linux/hisi/rdr_pub.h>
#include <rdr_inner.h>
#endif
#include <linux/jiffies.h>
#include <linux/stat.h>
#include <linux/reboot.h>
#include <asm/system_misc.h>
#include <asm/io.h>

/*soc interface*/
#include <soc_ao_sctrl_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_peri_sctrl_interface.h>
#include <soc_mddrc_dmc_interface.h>
#include <soc_baseaddr_interface.h>
#include <general_sram_map.h>
#include <linux/hisi/pm/pwrctrl_multi_memcfg.h>

#ifdef CONFIG_DEBUG_FS
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/time.h>
#include <linux/tick.h>
#include "soc_smart_interface.h"
#endif




#define HI6XXX_REBOOT_CODE_SRAM_PHYS  ((phys_addr_t)(PWRCTRL_ACPU_REBOOT))
#define HI6XXX_REBOOT_CODE_SIZE       (SZ_512)

#define HI6XXX_REBOOT_FLAG_PHYS       ((phys_addr_t)MEMORY_AXI_SRESET_FLAG_ADDR)

#define HI6XXX_RESET_DEFAULT_VALUE    (0x48698284)
#define HI6XXX_RESET_REGISTER_ADDR    ((phys_addr_t)(SOC_AO_SCTRL_SC_SYS_STAT0_ADDR(SOC_AO_SCTRL_BASE_ADDR)))
#define HI6XXX_DDR_REFRESH_CTRL_ADDR  ((phys_addr_t)(SOC_MDDRC_DMC_DDRC_CTRL_SREF_ADDR(SOC_MDDRC_DMC_BASE_ADDR)))
#define HI6XXX_DDR_REFRESH_STAT_ADDR  ((phys_addr_t)(SOC_MDDRC_DMC_DDRC_CURR_FUNC_ADDR(SOC_MDDRC_DMC_BASE_ADDR)))

static bool reboot_in_sram = true;

static unsigned int  hi6xxx_reset_reg_value = HI6XXX_RESET_DEFAULT_VALUE; /*sctrl register value for reboot */
static void __iomem *hi6xxx_reset_sram_virts = NULL; /*sctrl register address for reboot */
static void __iomem *hi6xxx_reset_reg_virts = NULL; /*sctrl register address for reboot */
static void __iomem *hi6xxx_reset_flag_virts = NULL; /*storage for reboot flag */


static void __iomem *powerhold_gpio_base;
static int g_powerhold_gpio_offset = 0;
static int g_powerhold_no = -1;
#define  POWER_HOLD_GPIO  0



#ifdef CONFIG_DEBUG_FS
static unsigned long hi6xxx_shutdown_time_start = 0;
extern unsigned char hi6xxx_pmic_reg_read (unsigned int reg_addr);
extern void hi6xxx_pmic_reg_write (unsigned int reg_addr, unsigned char regval);
#define	PMU_RSVED7			SOC_SMART_NP_RSVED7_ADDR(0)

static void hi6xxx_save_shutdown_time(void)
{
    unsigned int  save;
    unsigned int  msecs = 0;

    if ( hi6xxx_shutdown_time_start != 0){
        msecs = jiffies_to_msecs(jiffies - hi6xxx_shutdown_time_start);
        save = (unsigned int)(msecs/1000) + 1;
        if(save > 0xff)
	        save = 0xff;
        hi6xxx_pmic_reg_write(PMU_RSVED7,(unsigned char)save);

    } else {
        hi6xxx_pmic_reg_write(PMU_RSVED7, 0x0);
    }
}
#endif




extern void machine_restart(char *cmd);
extern struct cmdword reboot_reason_map[];
static void hisi_power_off(void)
{

#ifdef CONFIG_DEBUG_FS
    hi6xxx_save_shutdown_time();
#endif

	while(1) {
		if (powerhold_gpio_base != NULL) {
			/*printk(KERN_INFO "system power off now\n");*/
			/*set direction*/

			writel((g_powerhold_gpio_offset>>2), SOC_GPIO_GPIODIR_ADDR(powerhold_gpio_base));
			writel(0, (void *)powerhold_gpio_base + g_powerhold_gpio_offset);

			mdelay(1000);

			machine_restart("chargereboot");
		}
	}

}
/* protect gpio0 */
extern void gpio_powerhold_hook_register(void *func);

static void gpio_powerhold_protect(unsigned gpio)
{
	if(g_powerhold_no == gpio ) {
		printk(KERN_ERR "[ERROR!!] gpio0_0 is used for special ues of powerhold, Error!~~~\n");
#ifdef CONFIG_HISI_BB
        rdr_syserr_process_for_ap(MODID_AP_S_GPIO, 0, 0);
#endif
	}
}

static __init int hisi_poweroff_init(void)
{
	struct device_node *np = NULL;
	int offset = 0;
	int ret = 0;
	enum of_gpio_flags flags;

	np = of_find_compatible_node(NULL, NULL, "hisi,powerhold");
	/* get powerhold gpio */
	if (!np) {
		printk(KERN_ERR "get powerhold np error !\n");
	}

	powerhold_gpio_base = of_iomap(np, 0);
	printk(KERN_INFO "powerhold_gpio_base = 0x%p !\n", powerhold_gpio_base);
	ret = of_property_read_u32(np,"offset", &offset);
	if (ret) {
		printk(KERN_ERR "get offset error !\n");
		powerhold_gpio_base = 0;
	}
	else {
		printk(KERN_INFO "offset = 0x%x !\n", (unsigned int)offset);
		g_powerhold_gpio_offset = offset;
	}

	/* power off function */
	pm_power_off = hisi_power_off;

	g_powerhold_no = of_get_gpio_by_prop(np,"gpio_powerhold", 0, 0, &flags);
	if(POWER_HOLD_GPIO == g_powerhold_no) {
		gpio_powerhold_hook_register(gpio_powerhold_protect);
	}

	return ret;
}







/*MUST NOT use sp and fp, optimize for this*/
#pragma GCC optimize("O3")

static inline void __hi6xxx_reboot_code(void)
{
    /* config ddr refresh mode*/
    do {
        __raw_writel((0x1), (void __iomem *)HI6XXX_DDR_REFRESH_CTRL_ADDR);
    }while((__raw_readl((void __iomem *)HI6XXX_DDR_REFRESH_STAT_ADDR) & 0x1) == 0);

    /* write sctrl reboot register*/
    do {
        __raw_writel(HI6XXX_RESET_DEFAULT_VALUE, (void __iomem *)HI6XXX_RESET_REGISTER_ADDR);
    }while(1);

    return;
}
#pragma GCC reset_options


static void hi6xxx_sram_reboot(void)
{

#ifdef CONFIG_DEBUG_FS
    hi6xxx_save_shutdown_time();
#endif
    memcpy(hi6xxx_reset_sram_virts, (const void *)__hi6xxx_reboot_code, HI6XXX_REBOOT_CODE_SIZE);

    soft_restart(HI6XXX_REBOOT_CODE_SRAM_PHYS);

    return ;
}

static void hi6xxx_normal_reboot(void)
{
    do{
        writel(hi6xxx_reset_reg_value, hi6xxx_reset_reg_virts);
    }while(1);

    return;
}

#define RESET_COLD_FLAG "coldboot"

extern void hisi_usb_soft_disconnect(void);
static void hi6xxx_reset_func(char mode, const char *cmd)
{
    unsigned int i, value;
    unsigned long long pmu_reset_reg = 0;
    unsigned int curr_reboot_type = 0x10;

    hisi_usb_soft_disconnect();

    if (cmd == NULL) {
        cmd = RESET_COLD_FLAG;
        printk(KERN_ERR "cmd is null\n");
    }
    printk("record_exce_type pmu_reset_reg is1\n");
#ifdef CONFIG_HISI_BB
    for (i=0; i<get_reboot_reason_map_size(); i++) {
        if (!strcmp(reboot_reason_map[i].name, cmd)) {
            curr_reboot_type = reboot_reason_map[i].num;
            break;
        }
    }

    pmu_reset_reg = get_pmu_reset_reg();
    printk("record_exce_type pmu_reset_reg is2\n");
    if (pmu_reset_reg) {
        value = readl((char*)pmu_reset_reg);
        value &= (PMU_RESET_REG_MASK);
        value |= curr_reboot_type;
        printk("record_exce_type pmu_reset_reg is %d\n", value);
        writel(value, (char*)pmu_reset_reg);
    }
#endif

     /*reboot by sram code*/
    if (true == reboot_in_sram){
        hi6xxx_sram_reboot();
    }

    hi6xxx_normal_reboot();

    return;
}

static int __init hi6xxx_reset_probe_of(struct platform_device *pdev)
{
    struct device_node *np = pdev->dev.of_node;
    u32 val = 0;

    if (of_property_read_u32(np, "sctrl-value", &val)) {
        printk(KERN_ERR "%s : no reboot register value configured !\r\n", __FUNCTION__);
        hi6xxx_reset_reg_value = HI6XXX_RESET_DEFAULT_VALUE;
    }else{
        hi6xxx_reset_reg_value = val;
    }

    return 0;
}

static int __init hi6xxx_reset_probe(struct platform_device *pdev)
{
    void __iomem *addr;

    hi6xxx_reset_probe_of(pdev);

    addr = ioremap(HI6XXX_RESET_REGISTER_ADDR, sizeof(unsigned int));
    if (!addr){
        printk(KERN_ERR "%s failed to ioremap reset flag !\n", __FUNCTION__);
    }
    hi6xxx_reset_reg_virts = addr;

    addr = ioremap_wc(HI6XXX_REBOOT_FLAG_PHYS, sizeof(unsigned int));
    if (!addr){
        printk(KERN_ERR "%s failed to ioremap reset flag !\n", __FUNCTION__);
    }
    hi6xxx_reset_flag_virts = addr;

    addr = ioremap_wc(HI6XXX_REBOOT_CODE_SRAM_PHYS, HI6XXX_REBOOT_CODE_SIZE);
    if (!addr){
        printk(KERN_EMERG "%s failed to ioremap reboot code sram buffer\n", __FUNCTION__);
        reboot_in_sram = false;
    }
    hi6xxx_reset_sram_virts = addr;

    arm_pm_restart = hi6xxx_reset_func;

    return 0;
}

static struct of_device_id hi6xxx_reset_of_match[] = {
	{
		.compatible = "hisilicon,hi6xxx-reset",
		.data = NULL,
	},
	{}
};

static struct platform_driver hi6xxx_reset_driver = {
	.probe = hi6xxx_reset_probe,
	.driver = {
		.name = "hi6xxx-reset",
		.of_match_table = hi6xxx_reset_of_match,
	},
};







#ifdef CONFIG_DEBUG_FS

static ssize_t shutdown_dbgfs_write(struct file *fp, const char __user *ubuf,
					size_t cnt, loff_t *ppos)
{

    unsigned char buf[4] = {0};

    if(copy_from_user(buf,(void __user *) ubuf, sizeof(buf))){
        printk(KERN_ERR"shutdown_dbgfs_write failed\n");
        return -1;
    }

	if(buf[0]!=0){
	    hi6xxx_shutdown_time_start = jiffies;
        return cnt;
    }

    return cnt;
}


static struct dentry *shutdown_debugfs;


static int shutdown_recored_time_show(struct seq_file *m, void *unused)
{

    unsigned char record_time = 0;

    record_time = hi6xxx_pmic_reg_read(PMU_RSVED7);
    seq_printf(m, "%u\n",(unsigned int)record_time);

    return 0;
}


static int shutdown_recored_time_open(struct inode *inode, struct file *file)
{
	return single_open(file, shutdown_recored_time_show, NULL);
}


static const struct file_operations shutdown_save_fops = {
	.owner = THIS_MODULE,
	.open = shutdown_recored_time_open,
	.read = seq_read,
	.write = shutdown_dbgfs_write,
	.llseek = seq_lseek,
	.release = single_release,
};


static int __init shutdown_debugfs_init(void)
{

    struct dentry *shutdown_file;
    printk(KERN_INFO "shutdown_debugfs_init\n");

	shutdown_debugfs = debugfs_create_dir("shutdown_debugfs", NULL);
	if (!shutdown_debugfs){
        return -ENOENT;
    }

    shutdown_file = debugfs_create_file("shutdown_time_save", 0660, shutdown_debugfs, NULL, &shutdown_save_fops);
    if (!shutdown_file)
        goto Fail;

    return 0;
Fail:
    debugfs_remove_recursive(shutdown_debugfs);
    shutdown_debugfs = NULL;
    printk(KERN_ERR "create shutdown_debugfs file fail\n");
    return -ENOENT;
}

static void __exit shutdown_debugfs_exit(void)
{

    printk(KERN_INFO "shutdown_debugfs_exit\n");
    debugfs_remove_recursive(shutdown_debugfs);

    return;
}
module_init(shutdown_debugfs_init);
module_exit(shutdown_debugfs_exit);

#endif

static int __init hi6xxx_reset_init(void)
{
	return platform_driver_register(&hi6xxx_reset_driver);
}

module_init(hi6xxx_reset_init);

late_initcall(hisi_poweroff_init);
