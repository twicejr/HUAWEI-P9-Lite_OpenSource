
include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
#//-IBALONG_TOPDIR/modem/drv/mcore/kernel/drivers/dpm
BSP_DIR := $(BALONG_TOPDIR)/modem/drv
PCLINT_CC_OPTION += 

#*******************************************************************
#*******************************************************************

#*******************************************************************
# header file dir
#*******************************************************************
# include
PCLINT_INC_VAR += \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/pmu/ \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/pm/ \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/edma/ \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/aximonitor \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/socp

#*******************************************bsp1 begin*******************************************
#/*m3_dump,bsp_trace*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/om/m3_dump.c \
	$(BSP_DIR)/mcore/kernel/drivers/om/om_balong.c

#/*axi monitor*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/aximonitor/amon_balong.c

#/* socp */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/socp/socp_balong.c

#/*nvim*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/nvim/nv_base.c \
	$(BSP_DIR)/mcore/kernel/drivers/nvim/nv_comm.c
#/*******************************************bsp1   end*******************************************/

#/*******************************************bsp2 begin*******************************************/
#// bsp-2 liuwenhui begin
#// tem
OBC_LOCAL_PCLINT_SRC_FILE += \
    $(BSP_DIR)/mcore/kernel/drivers/temperature/temperature.c
#// ios
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/ios/ios_list.c
#// tsens
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/tsensor/tsensor_balong.c \
	$(BSP_DIR)/mcore/kernel/drivers/ios/ios_pd.c
#// bsp-2 liuwenhui end

#// bsp-2 zuofenghua begin
#//mipi
#//-IBALONG_TOPDIR/modem/drv/mcore/kernel/drivers/mipi
#//BALONG_TOPDIR/modem/drv/mcore/kernel/drivers/mipi/bbp_mipi_balong.c
#//pastar
#//-IBALONG_TOPDIR/modem/drv/mcore/kernel/drivers/pmu/hi6561
#//BALONG_TOPDIR/modem/drv/mcore/kernel/drivers/pmu/hi6561/pmu_hi6561.c

#// bsp-2 zuofenghua end


#//bsp-2 zhangjingyuan begin
#//hkadc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/hkadc/bsp_hkadc.c
#//hifi
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/hifi/bsp_hifi.c
#//bsp-2 zhangjingyuan end

#//bsp-2 xuwenfang begin
#//pmu

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/pmu/pmu.c
#//bsp-2 xuwenfang end
#//bsp-2 haoran begin
#//bsp-2 haoran end
#/*******************************************bsp2 end*******************************************/

#/*******************************************bsp3 begin*******************************************/
#/* pm */

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/pm/m3_cpufreq.c \
	$(BSP_DIR)/mcore/kernel/drivers/pm/m3_pm.c \
	$(BSP_DIR)/mcore/kernel/drivers/pm/$(CFG_PLATFORM)/pm_api.c
#/* start */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/start/ccpu_start.c
#// bsp-3 lixiaojie begin
#//ipc typedef Symbol 'funcptr' redeclared 是否有问题？
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/ipc/ipc_balong.c \
	$(BSP_DIR)/mcore/kernel/drivers/ipc/ipc_balong_test.c
#//dpm
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/dpm/dpm_balong.c
#//softtimer
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/timer/softtimer_balong.c
#// bsp-3 lixiaojie end

#// bsp-3 yaoguocai begin
#//icc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/icc/icc_balong.c \
	$(BSP_DIR)/mcore/kernel/drivers/icc/icc_balong_debug.c
#//console
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/serial/console.c
#//icc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/icc/icc_balong_test.c
#// bsp-3 yaoguocai end

#//bsp-3 xujingcui begin
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/lowpower_mntn/lowpower_mntn_balong.c 
#//bsp-3 xujingcui end

#// bsp-3 shangmianyou begin
#/* edma */

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/edma/edma_balong.c
#	$(BSP_DIR)/mcore/kernel/drivers/edma/edma_balong_test.c*/
#// bsp-3 shangmianyou end

#// bsp-3 yangqiang begin
#//WDT
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/watchdog/wdt_balong.c 
#// bsp-3 yangqiang end

#// bsp-3 wangxiandong begin
#//serial
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/serial/printk.c \
	$(BSP_DIR)/mcore/kernel/drivers/serial/symbol.c \
	$(BSP_DIR)/mcore/kernel/drivers/serial/symbol_dummy.c \
	$(BSP_DIR)/mcore/kernel/drivers/serial/uart.c
#// bsp-3 wangxiandong end
#/*******************************************bsp3   end*******************************************/
#/*******************************************bsp4   start*******************************************/
#//ipf

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/ipf/ipf_balong_pm.c
#/*******************************************bsp4   end*******************************************/