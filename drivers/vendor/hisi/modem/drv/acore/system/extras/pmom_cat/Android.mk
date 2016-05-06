# Copyright 2010 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)

COMMON_SRC_FILES:= tarzip.c dpm_m3pm.c cpufreq_regulator.c ipc_clk.c wakelock_parse.c pm_parse.c bbp_pmu.c icc.c nvim.c rfile.c dsp.c tcxo.c cosa.c

#*****************************org pmom_cat*****************************
include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := libcutils libc libz
LOCAL_SRC_FILES        := $(COMMON_SRC_FILES) pmom_cat.c 

LOCAL_CFLAGS           += -Werror
LOCAL_C_INCLUDES       := external/zlib
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/include/nv/tl/drv
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/drv/common/include
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/include/drv
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/include/drv/common

LOCAL_MODULE      := pmom_cat
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

#*****************************new modem_log_cat*****************************
include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := libcutils libc libz
LOCAL_SRC_FILES        := $(COMMON_SRC_FILES) modem_log_cat.c pm_log_cat.c modem_dmesg_cat.c

LOCAL_CFLAGS           += -Werror
LOCAL_C_INCLUDES       := external/zlib
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/include/nv/tl/drv
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/drv/common/include
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/modem/include/drv
LOCAL_C_INCLUDES       += $(BALONG_TOPDIR)/include/drv/common

LOCAL_MODULE      := modem_log_cat
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
