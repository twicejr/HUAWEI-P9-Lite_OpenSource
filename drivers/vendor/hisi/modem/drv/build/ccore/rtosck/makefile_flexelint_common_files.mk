
include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

BSP_DIR       := $(BALONG_TOPDIR)/modem/drv
#*******************************************************************
#*******************************************************************
PCLINT_OPTION +=

#*******************************************************************
# header file dir
#*******************************************************************
PCLINT_INC_VAR += \
	-I$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/ \
	-I$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/include_gu/ \
	-I$(BALONG_TOPDIR)/modem/config/nvim/include/gu/ \
	-I$(BALONG_TOPDIR)/modem/include/nv/tl/oam/ \
	-I$(BALONG_TOPDIR)/modem/include/nv/tl/lps/ \
	-I$(BALONG_TOPDIR)/modem/include/phy/lphy/ \
	-I$(BALONG_TOPDIR)/modem/include/nv/tl/drv \
	-I$(BALONG_TOPDIR)/modem/include/drv \
	-I$(BALONG_TOPDIR)/modem/include/med \
	-I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM) \
	-I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc \
	-I$(BALONG_TOPDIR)/modem/drv/common/include/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/edma/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/mipi/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/adp/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu/hi6561/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/version/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/bbp/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/spi/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/mailbox/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/mbxcphy/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/aximonitor/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/common/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/ddm/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/log/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/oms/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/sys_view/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/socp/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/sci/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/mbxhifi \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/misc


#*******************************************************************
#*******************************************************************
#*******************************************bsp3 begin*******************************************
# bsp-3 lixiaojie begin

# sync
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/sync/sync_balong.c

# hadtimer
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/adp/adp_timer.c \
	$(BSP_DIR)/ccore/drivers/balong_timer/hardtimer_balong.c \
	$(BSP_DIR)/ccore/drivers/balong_timer/hardtimer_balong_test.c \
	$(BSP_DIR)/ccore/drivers/balong_timer/softtimer_balong.c \
	$(BSP_DIR)/ccore/drivers/balong_timer/softtimer_balong_test.c

# hwadp
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/hwadp/hwadp_balong.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_int.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_gic_balong.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_sysctrl.c
# ipc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/ipc/ipc_balong.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_ipc.c \
	$(BSP_DIR)/common/osl/osl_wait.c 
#// bsp-3 lixiaojie end

# bsp-3 yangqiang begin
#//wdt
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/watchdog/wdt_balong.c

#regulator
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/regulator/regulator_balong_table.c \
	$(BSP_DIR)/ccore/drivers/regulator/regulator_balong.c
#cpufreq
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/cpufreq/cpufreq_balong.c
# bsp-3 yangqiang end

# bsp-3 xujingcui begin
#wakelock
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/wakelock/wakelock_balong.c

#cpuidle
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/cpuidle/cpuidle_balong.c

#clk
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/clk/clock_balong.c \
	$(BSP_DIR)/ccore/drivers/clk/clock_balong_hi6930.c \
	$(BSP_DIR)/ccore/drivers/clk/clock_balong_ops.c \
	$(BSP_DIR)/ccore/drivers/clk/clock_balong_test.c \
	$(BSP_DIR)/ccore/drivers/clk/clock_balong_debug.c
#adp_dpm
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/adp/adp_dpm.c
#tcxo
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/tcxo/tcxo_balong.c

#lowpower_mntn
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/lowpower_mntn/lowpower_mntn_balong.c
# bsp-3 xujingcui end

# bsp-3 shangmianyou begin
#/* edma */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/edma/edma_interface.c	\
	$(BSP_DIR)/ccore/drivers/edma/edma_core.c \
	$(BSP_DIR)/ccore/drivers/edma/edma_driver.c \
	$(BSP_DIR)/ccore/drivers/edma/edma_device.c
#/*BALONG_TOPDIR/modem/drv/ccore/drivers/edma/edma_balong_test.c*/
# bsp-3 shangmianyou end

# bsp-3 yaoguocai begin
#// icc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/adp/adp_icc.c \
	$(BSP_DIR)/ccore/drivers/icc/icc_balong.c \
	$(BSP_DIR)/ccore/drivers/icc/icc_balong_debug.c \
	$(BSP_DIR)/ccore/drivers/icc/icc_balong_test.c
#//hwadp_memory
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/hwadp/hwadp_memory.c
# bsp-3 yaoguocai end

# bsp-3 wangxiandong begin
#cipher
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/cipher/acc_balong.c \
	$(BSP_DIR)/ccore/drivers/cipher/cipher_balong.c

# uart
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/uart/sysSerial.c \
	$(BSP_DIR)/ccore/drivers/uart/printksync.c \
	$(BSP_DIR)/ccore/drivers/uart/balongv7r2_uart.c

#cshell
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/cshell/cshell.c
# bsp-3 lixiaojie wangxiandong end
#*******************************************bsp3 end*********************************************

#*******************************************bsp2 begin*******************************************
#bsp-2 liuwenhui begin
#efuse
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/adp/adp_efuse.c
#//BALONG_TOPDIR/modem/drv/ccore/drivers/efuse/efuse_balong.c

#antenna
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/adp/adp_anten.c \
	$(BSP_DIR)/ccore/drivers/anten/anten_balong.c

#gpio
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/adp/adp_gpio.c \
	$(BSP_DIR)/ccore/drivers/gpio/gpio_balong.c
#bsp-2 liuwenhui end

#bsp-2 zuofenghua begin
#mipi
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/mipi/bbp_mipi_balong.c
#pastar

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/pmu/hi6561/pmu_hi6561.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_pmu_hi6561.c
#version
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/version/version_balong.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_version.c
#BBP

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/bbp/bbp_balong.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_bbp_balong.c
#bsp-2 zuofenghua end

#bsp-2 zhangjingyuan begin
#abb
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/abb/bsp_abb.c
#dsp
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/adp/adp_dsp.c \
	$(BSP_DIR)/ccore/drivers/dsp/bsp_dsp.c
#bsp-2 zhangjingyuan end

#bsp-2 xuwenfang begin

OBC_LOCAL_PCLINT_SRC_FILE += \
$(BSP_DIR)/ccore/drivers/spi/spi.c
#bsp-2 xuwenfang end
#*******************************************bsp2   end*******************************************

#/*******************************************bsp1 begin*******************************************/
# mailbox


OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/mailbox/mailbox_commom.c \
	$(BSP_DIR)/ccore/drivers/mailbox/mailbox_commsg.c \
	$(BSP_DIR)/ccore/drivers/mailbox/mailbox_spmsg.c

# cdsp mailbox
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/mbxcphy/xmailbox_commsg.c \
	$(BSP_DIR)/ccore/drivers/mbxcphy/xmailbox_commom.c
#rfile
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/rfile/rfile_balong.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_rfile.c
#MEM
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/mem/mem_balong.c \
#	$(BSP_DIR)/ccore/drivers/mem/mem_balong_test.c
#$(BSP_DIR)/ccore/drivers/mem/adp_mem_balong.c

#ddm
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/om/ddm/ddm_phase.c

#om common


OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/om/common/bsp_dmesg.c \
	$(BSP_DIR)/ccore/drivers/om/common/bsp_om_comm.c \
	$(BSP_DIR)/ccore/drivers/om/common/bsp_om_save.c
#log
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/om/log/bsp_om_log.c

#oms
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/om/oms/bsp_om_server.c
#sys_view
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/om/sys_view/bsp_cpu_view.c \
	$(BSP_DIR)/ccore/drivers/om/sys_view/bsp_mem_view.c \
	$(BSP_DIR)/ccore/drivers/om/sys_view/bsp_om_sysview.c \
	$(BSP_DIR)/ccore/drivers/om/sys_view/bsp_task_view.c \
	$(BSP_DIR)/ccore/drivers/om/aximonitor/amon_balong.c

#socp 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/socp/socp_balong.c

#sci

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/sci/sci_balong.c \
	$(BSP_DIR)/ccore/drivers/sci/sci_pl131.c \
	$(BSP_DIR)/ccore/drivers/sci/sci_debug.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_sci.c \
	$(BSP_DIR)/ccore/drivers/sci/sci_cfg.c

#nvim
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/nvim/nv_base.c \
	$(BSP_DIR)/ccore/drivers/nvim/nv_comm.c \
	$(BSP_DIR)/ccore/drivers/adp/adp_nvim.c

#hifimailbox


OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/mbxhifi/drv_mailbox.c \
	$(BSP_DIR)/ccore/drivers/mbxhifi/drv_mailbox_debug.c \
	$(BSP_DIR)/ccore/drivers/mbxhifi/drv_mailbox_gut.c \
	$(BSP_DIR)/ccore/drivers/mbxhifi/drv_mailbox_msg.c \
	$(BSP_DIR)/ccore/drivers/mbxhifi/drv_mailbox_port_vxworks.c \
	$(BSP_DIR)/ccore/drivers/mbxhifi/drv_mailbox_table.c
#/*******************************************bsp1   end*******************************************/
