include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

BSP_DIR       := $(BALONG_TOPDIR)/modem/drv
#*******************************************************************
#*******************************************************************
PCLINT_OPTION +=

#*******************************************************************
# header file dir
#*******************************************************************
PCLINT_INC_VAR += \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu/hi6559/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/i2c/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pa_rf/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/dump/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/test/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/usbtrace/ \
	-I$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pm

#*******************************************************************
#*******************************************************************
#/*******************************************bsp1 begin*******************************************/
#RTC
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/rtc/rtc_balong.c 
#/* OM */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/om/dump/bsp_dump.c \
	$(BSP_DIR)/ccore/drivers/om/usbtrace/utrace_balong.c
#/*******************************************bsp1 end*******************************************/

#/*******************************************bsp2 begin*******************************************/
#//bsp2-liuwenhui begin
#//bsp2-liuwenhui end

#//bsp2-lusuo begin
#//bsp2-lusuo end

#//bsp2-zuofenghua begin
#//i2c
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/i2c/i2c_balong.c
#//bsp2-zuofenghua end

#//bsp-2 zhangjingyuan begin
#//hkadc
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/hkadc/bsp_hkadc.c
#//onoff
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/onoff/bsp_onoff.c
#//bsp-2 zhangjingyuan end

#//bsp2-xuwenfang begin


#//spi
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/spi/spi_balong.c
#//bsp2-xuwenfang end

#//bsp2-haoran begin
#//bsp2-haoran end
#//bsp2-lusuo begin
#//pa_rf
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/pa_rf/pa_rf_balong.c
	
#//pmu
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/pmu/hi6559/pmu_hi6559.c \
	$(BSP_DIR)/ccore/drivers/pmu/hi6559/common_hi6559.c \
	$(BSP_DIR)/ccore/drivers/pmu/hi6559/debug_hi6559.c \
	$(BSP_DIR)/ccore/drivers/pmu/pmu_balong.c \
	$(BSP_DIR)/ccore/drivers/pmu/pmu_debug.c \
#//bsp2-lusuo end

#/*******************************************bsp2 end*******************************************/


#/*******************************************bsp3 begin*******************************************/
#/*dpm*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/dpm/dpm_balong_test.c \
	$(BSP_DIR)/ccore/drivers/dpm/dpm_balong.c 

#// bsp-3 shangmianyou begin
#/*pm */
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/pm/pm.c
#/*BALONG_TOPDIR/modem/drv/ccore/drivers/pm/pm_test.c*/

#// bsp-3 shangmianyou end

#/*******************************************bsp3 end *******************************************/

#/*******************************************bsp4 start *******************************************/
#/*ipf*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/ccore/drivers/ipf/ipf_balong.c

#/*******************************************bsp4 end *******************************************/