include $(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

BSP_DIR := $(BALONG_TOPDIR)/modem/drv
#*******************************************************************
#*******************************************************************
PCLINT_OPTION += -DCONFIG_DEBUG_LOCK_ALLOC


#*******************************************************************
# header file dir
#*******************************************************************
PCLINT_INC_VAR += \
	-I$(BALONG_TOPDIR)/modem/drv/acore/bootable/bootloader/legacy/include/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/bootable/bootloader/legacy/include/balongv7r2/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/bootable/bootloader/legacy/include/balongv7r2/gpio_config/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/include \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/common/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/oms/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/log/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/dump/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/sys_view/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/om/usbtrace/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/socp/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/i2c/busses/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/onoff/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/arch/arm/mach-hi6930/include/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/pmic/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/pmic/hi6551/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/include/linux/emi/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/include/linux/video/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/balong_timer/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/cpufreq/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/arch/arm/mach-hi6930/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/edma/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/usb/susb/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/usb/dwc_common_port/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/usb/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/usb/gadget/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/mtd/nand/ptable \
	-I$(BALONG_TOPDIR)/include/nv/comm/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/nvim/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/bootable/bootloader/legacy/include/balongv7r2/ \
	-I$(CFG_ANDROID_DIR)/kernel/drivers/usb/gadget/ \
	-I$(CFG_ANDROID_DIR)/kernel/drivers/mtd/ \
	-I$(CFG_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc


#*******************************************************************
#*******************************************************************
#/*******************************************bsp1 begin*******************************************/
#/* nvim */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nv_flash.c \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/arch_balongv7r2/nv_boot.c
	
#/* hifimailbox */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/mbxhifi/drv_mailbox.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/mbxhifi/drv_mailbox_debug.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/mbxhifi/drv_mailbox_gut.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/mbxhifi/drv_mailbox_msg.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/mbxhifi/drv_mailbox_port_linux.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/mbxhifi/drv_mailbox_table.c
#/*RTC*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/rtc/rtc_balong/rtc_balong.c
#/*BALONG_TOPDIR/modem/drv/acore/kernel/drivers/rtc/adp_rtc_balong.c*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/rtc/rtc_hi6551/rtc_hi6551.c
#/*log*/

#/*sys_view*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/sys_view/bsp_cpu_view.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/sys_view/bsp_mem_view.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/sys_view/bsp_om_sysview.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/sys_view/bsp_task_view.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/dump/bsp_dump.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/om/usbtrace/utrace_balong.c
#/* socp */
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/modem/socp/socp_balong.c
#/*******************************************bsp1 end*******************************************/

#/*******************************************bsp2 begin*******************************************/
#//bsp2-liuwenhui begin
#// gpio
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/gpio/gpio_balong.c
#// key 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/keyboard/key_balong.c
#// temperature 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/temperature/temperature_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/temperature/tempsys_device.c

#// ios 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/ios/ios_balong.c
#// efuse 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/efuse/efuse_balong.c
#//bsp2-liuwenhui end
#//bsp2-lusuo begin
#// nand 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nand_ids.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_cfg.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_ctrl.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_data.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_host.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_mtd.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_nand.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_native.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/nandc/nandc_v600.c
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/mtd/nand/nand_base.c

#// ptable
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/ptable/ptable_common.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/ptable/ptable_fastboot.c \
	$(BSP_DIR)/acore/kernel/drivers/mtd/nand/ptable/ptable_product.c

#// led
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/leds/ledtrig_breath.c \
	$(BSP_DIR)/acore/kernel/drivers/leds/leds_balong.c

#// efuse_nandc

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/arch_balongv7r2/efuse_nandc.c

#bsp2-lusuo end

#bsp2-zuofenghua begin
#//i2c
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/i2c/busses/i2c_balong.c

#bsp2-zuofenghua end

#bsp2-zhangjingyuan begin
#// loadm
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/modem/loadm/loadm.c
#// DSP
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/dsp/bsp_dsp.c
#// hkadc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/hkadc/bsp_hkadc.c \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/arch_balongv7r2/bsp_hkadc.c
#//onoff

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/onoff/power_exchange.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/onoff/power_off.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/onoff/power_on.c \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/arch_balongv7r2/preboot.c
#bsp2-zhangjingyuan end

#bsp2-xuwenfang begin
#//pmic
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/pmic/hi6551/pmu_hi6551.c
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/pmic/hi6551/pmu_hi6551_test.c
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/pmic/hi6551/dr_hi6551.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/hi6551/common_hi6551.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/hi6551/exc_hi6551.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/hi6551/irq_hi6551.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/hi6551/debug_hi6551.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/hi6551/coul_hi6551.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/pmu_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/pmu_debug.c \
	$(BSP_DIR)/acore/kernel/drivers/pmic/pmu_test.c
#//emi
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/emi/emi_balong.c
#//lcd
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/video/lcdfb_balong_emi.c
#//spi
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/spi/spi_balong.c
#//bsp2-xuwenfang end

#bsp2-haoran begin
#bsp2-haoran end
#*******************************************bsp2 end*******************************************/

#/*******************************************bsp4 begin*******************************************/
#// bsp3-lixiaojie begin
#//ipc
#//timer
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/balong_timer/hardtimer_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/balong_timer/hardtimer_k3.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/balong_timer/hardtimer_balong_test.c
#//sync
#// bsp3-lixiaojie end

#// bsp3-yangqiang begin
#//WDT
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/watchdog/wdt_balong.c
#//regulator   好多lint消不掉
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/regulator/regulator_balong.c
#//cpufreq
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/cpufreq/cpufreq_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/cpufreq/cpufreq_balong_ondemand.c
#// bsp3-yangqiang end

#// bsp3-shangmianyou begin
#/*pm & edma */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/arch/arm/mach-hi6930/pm.c
#/*BALONG_TOPDIR/modem/drv/acore/kernel/arch/arm/mach-hi6930/pm_test.c*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/edma/edma_balong.c
#/*BALONG_TOPDIR/modem/drv/acore/kernel/drivers/edma/edma_balong_test.c*/
#// bsp3-shangmianyou end

#// bsp3-yaoguocai begin
#// icc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/icc/icc_balong_debug.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/icc/icc_balong_test.c

#// bsp3-xujingcui end
#/*clk*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/clk/clock_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/clk/clock_balong_hi6930.c \
	$(BSP_DIR)/acore/kernel/drivers/clk/clock_balong_ops.c \
	$(BSP_DIR)/acore/kernel/drivers/clk/clock_balong_test.c \
	$(BSP_DIR)/acore/kernel/drivers/clk/clock_balong_debug.c

#/*cpuidle*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/arch/arm/mach-hi6930/cpuidle_balong.c

#/*wakelock debug*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/kernel/power/wakelock_debug.c

#/*lowpower_mntn*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/kernel/power/lowpower_mntn_balong.c
#// bsp3-xujingcui end

#// bsp3-wangxiandong end
#//uart-at
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/uartat/at_uart_balong.c
#//cipher
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/cipher/kdf.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/cipher/balong_kdf_ioctrl.c
#//fastboot-uart
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/arch_balongv7r2/serial.c \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/arch_balongv7r2/cipher.c \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/arch_balongv7r2/console.c

#//uart
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/tty/serial/balongv7r2_uart.c
#// bsp3-wangxiandong end
#/*******************************************bsp3   end*******************************************/

#/*******************************************bsp4   begin*******************************************/
#//ipf
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/ipf/ipf_balong.c

#//hsic
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/usb/susb/dwc_otg_hcd_linux.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/susb/dwc_otg_hcd_queue.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/susb/dwc_otg_hcd.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/susb/dwc_otg_driver.c


#/*usb*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/usb/dwc3/dwc3-balong.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/dwc3/gadget.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/dwc3/core.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/dwc3/host.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/dwc3/debugfs.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/dwc3/ep0.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/gadget/f_ecm.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/gadget/f_ncm.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/gadget/f_rndis.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/gadget/ncm_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/gadget/rndis.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/gadget/u_ether.c
#/*acm*/
#/*mass*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/usb/gadget/usb_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/usb/otg/dwc_otg3.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_usb.c

#/*mmc*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/mmc/host/dwc_mmc.c \
	$(BSP_DIR)/acore/kernel/drivers/mmc/host/mshci.c

#/*mmc adp*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_mmc.c
#/*******************************************bsp4 end*******************************************/