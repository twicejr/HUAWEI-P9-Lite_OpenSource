
include $(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

BSP_DIR := $(BALONG_TOPDIR)/modem/drv

#*******************************************************************
#*******************************************************************
PCLINT_OPTION += -DCONFIG_SMP \
				"-header($(CFG_ANDROID_DIR)/kernel/include/asm-generic/int-ll64.h)" \
				"-header($(CFG_ANDROID_DIR)/kernel/include/linux/kernel.h)"

#*******************************************************************
# header file dir
#*******************************************************************
PCLINT_INC_VAR += \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/usb/gadget/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/version/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/kernel/drivers/modem/nvim/ \
	-I$(BALONG_TOPDIR)/modem/drv/acore/bootable/bootloader/legacy/modem/ \
	-I$(CFG_ANDROID_DIR)/bootable/bootloader/legacy/include/ \
	-I$(BALONG_TOPDIR)/../../kernel/include/uapi/ \
	-I$(BALONG_TOPDIR)/../../kernel/include/uapi/linux/ \
	-I$(BALONG_TOPDIR)/../../kernel/include/uapi/linux/mmc/ \
	-I$(BALONG_TOPDIR)/../../kernel/include/linux/mmc/


#*******************************************************************
#*******************************************************************
#*******************************************bsp1 begin*******************************************/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/nvim/nv_emmc.c \
	$(BSP_DIR)/acore/bootable/bootloader/legacy/modem/nv_balong.c
#*******************************************bsp1 end*********************************************/




#*******************************************bsp3 begin*******************************************/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/balong_timer/hardtimer_k3.c \

#reset 
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/reset/load_image.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/reset/power_manager_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/reset/reset_balong.c \
	$(BSP_DIR)/acore/kernel/drivers/modem/reset/reset_balong_test.c 

#*******************************************bsp3   end*******************************************/
#*******************************************bsp2 end*******************************************/

#/*******************************************bsp4 begin*******************************************/
#//ipf
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/ipf/ipf_balong.c

#*usb*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_usb_k3.c

#/*mmc adp*/
OBC_LOCAL_PCLINT_SRC_FILE += \
	$(BSP_DIR)/acore/kernel/drivers/modem/adp/adp_mmc.c
#/*******************************************bsp4 end*******************************************/