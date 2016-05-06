#modem fastboot code
-include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
	modem.c \
	nv_boot.c \
	nv_xml_dec.c \
	nv_emmc.c \
	version_balong.c \
	pintrl_balong.c \
	temperature_balong.c \
	param_cfg_to_sec.c

ifeq ($(strip $(CFG_CONFIG_PM_OM)),YES)
LOCAL_SRC_FILES += \
	pm_om_smem.c
else
LOCAL_SRC_FILES += \
	adp_pm_om.c
endif

ifneq ($(strip $(CFG_BALONG_MODEM)),true)
LOCAL_SRC_FILES := 	dummy.c 
endif

LOCAL_C_INCLUDES := $(call include-path-for, legacy)

LOCAL_C_INCLUDES +=\
    bootable/bootloader/legacy/include\


LOCAL_C_INCLUDES += $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config \
                    $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/include_gu \
                    $(BALONG_TOPDIR)/modem/config/nvim/include/gu \
                    $(BALONG_TOPDIR)/modem/include/drv \
                    $(BALONG_TOPDIR)/modem/include/nv/tl/drv \
                    $(BALONG_TOPDIR)/modem/include/nv/tl/oam \
                    $(BALONG_TOPDIR)/modem/include/nv/tl/lps \
                    $(BALONG_TOPDIR)/modem/include/phy/lphy \
                    $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM) \
                    $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc \
                    $(BALONG_TOPDIR)/modem/drv/common/include \
					$(BALONG_TOPDIR)/modem/include/drv/acore \
					$(BALONG_TOPDIR)/modem/include/drv/ccore \
					$(BALONG_TOPDIR)/modem/include/drv/common

LOCAL_CFLAGS := $(COMMON_CFLAGS)
LOCAL_ASFLAGS := $(COMMON_ASFLAGS)


LOCAL_MODULE := lib_modem
LOCAL_MODULE_TAGS := optional
include $(BUILD_RAW_STATIC_LIBRARY)


