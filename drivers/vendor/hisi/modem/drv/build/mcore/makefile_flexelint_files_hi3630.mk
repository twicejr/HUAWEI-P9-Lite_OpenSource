
include $(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

BSP_DIR := $(BALONG_TOPDIR)/modem/drv

#*******************************************************************
#*******************************************************************

#*******************************************************************
# header file dir
#*******************************************************************
# include
PCLINT_INC_VAR += \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/dpm \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/ipc \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/timer \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/modem \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/start-k3

OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/mcore/kernel/drivers/reset/reset_balong.c \
	$(BSP_DIR)/mcore/kernel/drivers/dpm/dpm_lpm3_k3.c \
	$(BSP_DIR)/mcore/kernel/drivers/ipc/ipc_lpm3_k3.c \
	$(BSP_DIR)/mcore/kernel/drivers/timer/softtimer_lpm3_k3.c 
