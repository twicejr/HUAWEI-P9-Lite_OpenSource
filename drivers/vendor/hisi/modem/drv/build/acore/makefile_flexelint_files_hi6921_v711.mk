include $(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

BSP_DIR := $(BALONG_TOPDIR)/modem/drv
#*******************************************************************
#*******************************************************************
PCLINT_OPTION += -DCONFIG_DEBUG_LOCK_ALLOC


#*******************************************************************
# header file dir
#*******************************************************************
PCLINT_INC_VAR += \
	-I$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/include/ \
	-I$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/include/balong/ \
	-I$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/include/balong/gpio_config/ \
	-I$(OBB_ANDROID_DIR)/kernel/include \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/common/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/oms/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/log/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/dump/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/sys_view/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/usbtrace/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/socp/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/i2c/busses/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/common/ \
	-I$(OBB_ANDROID_DIR)/kernel/arch/arm/mach-balong/include/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/hisi/pmic/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/hisi/pmic/hi6559/ \
	-I$(OBB_ANDROID_DIR)/kernel/include/linux/emi/ \
	-I$(OBB_ANDROID_DIR)/kernel/include/linux/video/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/balong_timer/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/cpufreq/ \
	-I$(OBB_ANDROID_DIR)/kernel/arch/arm/mach-hi6930/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/usb/susb/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/usb/dwc_common_port/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/usb/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/net/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/net/ethernet/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/net/ethernet/stmicro/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/net/ethernet/stmicro/stmmac/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/ptable \
	-I$(BALONG_TOPDIR)/include/nv/comm/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/nvim/ \
	-I$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/include/balong/ \
	-I$(BALONG_TOPDIR)/modem/thirdparty/zarlink/zarlink_api/includes \
	-I$(OBB_ANDROID_DIR)/kernel/include \
	-I$(OBB_ANDROID_DIR)/kernel/include/net/ \
	-I$(OBB_ANDROID_DIR)/kernel/include/net/netfilter \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/mtd/ \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/pci \
	-I$(OBB_ANDROID_DIR)/kernel/sound/soc/balong \
	-I$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/zarlink_api/includes \
	-I$(OBB_ANDROID_DIR)/kernel/drivers/modem/dialup_hsuart
#*******************************************************************
#*******************************************************************
#/*******************************************bsp1 begin*******************************************/
#/* nvim */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/nvim/nv_flash.c \
	$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/arch_balongv7r2/nv_boot.c
	
#/* hifimailbox */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/mbxhifi/drv_mailbox.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/mbxhifi/drv_mailbox_debug.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/mbxhifi/drv_mailbox_gut.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/mbxhifi/drv_mailbox_msg.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/mbxhifi/drv_mailbox_port_linux.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/mbxhifi/drv_mailbox_table.c
#/*RTC*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/rtc/rtc_balong/rtc_balong.c
#/*BALONG_TOPDIR/modem/drv/acore/kernel/drivers/rtc/adp_rtc_balong.c*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/rtc/rtc_hi6559/rtc_hi6559.c
#/*log*/

#/*sys_view*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/sys_view/bsp_cpu_view.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/sys_view/bsp_mem_view.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/sys_view/bsp_om_sysview.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/sys_view/bsp_task_view.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/dump/bsp_dump.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/om/usbtrace/utrace_balong.c
#/* socp */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/socp/socp_balong.c
#/*******************************************bsp1 end*******************************************/

#/*******************************************bsp2 begin*******************************************/
#// bsp2-zhangjingyuan begin
#// PCIe
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/pci/pcie_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/pci/pcie_balong_pm.c
#// bsp2-zhangjingyuan end

#//bsp2-lusuo begin
#// led
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/leds/ledtrig_breath.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/leds/leds_balong.c

#//pmic
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/hi6559/pmu_hi6559.c
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/hi6559/dr_hi6559.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/hi6559/common_hi6559.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/hi6559/exc_hi6559.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/hi6559/irq_hi6559.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/hi6559/debug_hi6559.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/pmu_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/pmic/pmu_debug.c 
#//bsp2-lusuo end
#//bsp2-liuwenhui begin
#// slic
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/sio.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/slic_ctl.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/snd_init.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/snd_machine.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/snd_pcm.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/snd_platform.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/snd_slic.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/spi.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/vp_hal.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/ZLR96621L_SM2_CHINA.c \
	$(OBB_ANDROID_DIR)/kernel/sound/soc/balong/zsi.c

#// gpio
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/gpio/gpio_balong.c
#// key 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/keyboard/key_balong.c
#// temperature 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/temperature/temperature_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/temperature/tempsys_device.c

#// ios 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/ios/ios_balong.c
#// efuse 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/efuse/efuse_balong.c
#//bsp2-liuwenhui end
#// nand 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nand_ids.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_cfg.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_ctrl.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_data.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_host.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_mtd.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_nand.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_native.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/nandc/nandc_v600.c
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/mtd/nand/nand_base.c

#// ptable
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/ptable/ptable_common.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/ptable/ptable_fastboot.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mtd/nand/ptable/ptable_product.c


#// efuse_nandc

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/arch_balongv7r2/efuse_nandc.c


#bsp2-zuofenghua begin
#//i2c
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/i2c/busses/i2c_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/i2c/busses/hisi_i2c_designware.c

#bsp2-zuofenghua end

#bsp2-zhangjingyuan begin
#// loadm
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/modem/loadm/loadm.c
#// DSP
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/dsp/bsp_dsp.c
#// hkadc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/hkadc/bsp_hkadc.c \
	$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/arch_balongv7r2/bsp_hkadc.c
#//onoff

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/onoff/power_exchange.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/onoff/power_off.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/onoff/power_on.c \
	$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/arch_balongv7r2/preboot.c
#bsp2-zhangjingyuan end

#bsp2-xuwenfang begin

#//emi
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/emi/emi_balong.c
#//lcd
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/video/lcdfb_balong_emi.c
#//spi
#//BALONG_TOPDIR/modem/drv/acore/kernel/drivers/spi/spi_balong.c
#*******************************************bsp2 end*******************************************/

#/*******************************************bsp3 begin*******************************************/
#// bsp3-lixiaojie begin
#//ipc
#//timer
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/balong_timer/hardtimer_balong.c 
#//sync
#// bsp3-lixiaojie end

#// bsp3-yangqiang begin
#//WDT
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/watchdog/wdt_balong.c
#//regulator   好多lint消不掉
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/regulator/regulator_balong.c
#//cpufreq
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/cpufreq/cpufreq_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/cpufreq/cpufreq_balong_ondemand.c
#// bsp3-yangqiang end

#// bsp3-shangmianyou begin
#/*pm & edma */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/arch/arm/mach-hi6930/pm.c
#/*BALONG_TOPDIR/modem/drv/acore/kernel/arch/arm/mach-hi6930/pm_test.c*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/edma/edma_balong.c
#/*BALONG_TOPDIR/modem/drv/acore/kernel/drivers/edma/edma_balong_test.c*/
#// bsp3-shangmianyou end

#// bsp3-yaoguocai begin
#// icc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/icc/icc_balong_debug.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/icc/icc_balong_test.c

#// bsp3-xujingcui end
#/*clk*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/clk/clock_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/clk/clock_balong_hi6930.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/clk/clock_balong_ops.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/clk/clock_balong_test.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/clk/clock_balong_debug.c

#/*cpuidle*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/arch/arm/mach-hi6930/cpuidle_balong.c

#/*wakelock debug*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/kernel/power/wakelock_debug.c

#/*lowpower_mntn*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/kernel/power/lowpower_mntn_balong.c
#// bsp3-xujingcui end

#// bsp3-wangxiandong end
#//uart-at
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/uartat/at_uart_balong.c
#//cipher
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/cipher/kdf.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/cipher/balong_kdf_ioctrl.c
#//fastboot-uart
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/arch_balongv7r2/serial.c \
	$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/arch_balongv7r2/cipher.c \
	$(OBB_ANDROID_DIR)/bootable/bootloader/legacy/arch_balongv7r2/console.c

#//uart
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/tty/serial/balongv7r2_uart.c
	
#//at dialup hsuart
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/dialup_hsuart/dialup_hsuart.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/dialup_hsuart/dialup_acshell.c
#// bsp3-wangxiandong end
#/*******************************************bsp3   end*******************************************/

#/*******************************************bsp4   begin*******************************************/
#//ipf
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/ipf/ipf_balong.c

#//hsic
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/susb/dwc_otg_hcd_linux.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/susb/dwc_otg_hcd_queue.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/susb/dwc_otg_hcd.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/susb/dwc_otg_driver.c


#/*usb*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/dwc3/dwc3-balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/dwc3/gadget.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/dwc3/core.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/dwc3/host.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/dwc3/debugfs.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/dwc3/ep0.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/f_ecm.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/f_ncm.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/f_rndis.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/ncm_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/rndis.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/u_ether.c
#/*acm*/
#/*mass*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/gadget/usb_balong.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/usb/otg/dwc_otg3.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/adp/adp_usb.c

#/*mmc*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/mmc/host/dwc_mmc.c \
	$(OBB_ANDROID_DIR)/kernel/drivers/mmc/host/mshci.c

#/*mmc adp*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/modem/adp/adp_mmc.c

	
#/*gmac*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(OBB_ANDROID_DIR)/kernel/drivers/net/ethernet/stmicro/stmmac/stmmac_platform.c
#/*******************************************bsp4 end*******************************************/