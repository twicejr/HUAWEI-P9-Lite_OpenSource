#Android makefile to build kernel as a part of Android Build
ifeq ($(BALONG_TOPDIR),)
export BALONG_TOPDIR := $(shell pwd)/vendor/hisi
endif

export SRCHI1101=drivers/misc/hw-drv


#ifeq ($(TARGET_PREBUILT_KERNEL),)

export OBB_PRODUCT_NAME ?= $(HISI_TARGET_PRODUCT)

ifeq ($(strip $(TARGET_BOARD_PLATFORM)), hi3650)
HISI_3650_MODEM_DEFCONFIG := vendor/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/os/acore/hi3650_modem_defconfig
endif

ifeq ($(strip $(TARGET_BOARD_PLATFORM)), hi6250)
HISI_6250_MODEM_DEFCONFIG := vendor/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/os/acore/hi6250_modem_defconfig
endif

ifeq ($(strip $(TARGET_BOARD_PLATFORM)), hi3660)
HISI_3660_MODEM_DEFCONFIG := vendor/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/os/acore/hi3660_modem_defconfig
endif

ifeq ($(OBB_PRINT_CMD), true)
KERNEL_OUT := vendor/hisi/build/delivery/$(OBB_PRODUCT_NAME)/obj/android
else
KERNEL_OUT := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ
endif
KERNEL_CONFIG := $(KERNEL_OUT)/.config

ifeq ($(TARGET_ARM_TYPE), arm64)
KERNEL_ARCH_PREFIX := arm64
CROSS_COMPILE_PREFIX=aarch64-linux-android-
TARGET_PREBUILT_KERNEL := $(KERNEL_OUT)/arch/arm64/boot/Image.gz
else
KERNEL_ARCH_PREFIX := arm
CROSS_COMPILE_PREFIX=arm-linux-gnueabihf-
TARGET_PREBUILT_KERNEL := $(KERNEL_OUT)/arch/arm/boot/zImage
endif

COMMON_HEAD := $(shell pwd)/kernel/drivers/
COMMON_HEAD += $(shell pwd)/kernel/mm/
COMMON_HEAD += $(shell pwd)/kernel/include/hisi/
COMMON_HEAD += $(shell pwd)/vendor/hisi/ap/config/product/$(OBB_PRODUCT_NAME)/include/
COMMON_HEAD += $(shell pwd)/external/efipartition	

ifeq ($(HISI_TARGET_PRODUCT), hi3650)
COMMON_HEAD += $(shell pwd)/vendor/hisi/ap/platform/hi3650/
endif

ifeq ($(HISI_TARGET_PRODUCT), hi6250)
COMMON_HEAD += $(shell pwd)/vendor/hisi/ap/platform/hi6250/
endif

ifeq ($(HISI_TARGET_PRODUCT), hi3660)
COMMON_HEAD += $(shell pwd)/vendor/hisi/ap/platform/hi3660/
endif

ifneq ($(COMMON_HEAD),)
BALONG_INC := $(patsubst %,-I%,$(COMMON_HEAD))
else
BALONG_INC :=
endif

ifeq ($(CFG_CONFIG_HISI_FAMA),true)
BALONG_INC  += -DCONFIG_HISI_FAMA
endif

export BALONG_INC

KERNEL_N_TARGET ?= vmlinux
UT_EXTRA_CONFIG ?=

KERNEL_ARCH_ARM_CONFIGS := $(shell pwd)/kernel/arch/$(KERNEL_ARCH_PREFIX)/configs
KERNEL_GEN_CONFIG_FILE := hw_$(TARGET_PRODUCT)_defconfig
KERNEL_GEN_CONFIG_PATH := $(KERNEL_ARCH_ARM_CONFIGS)/$(KERNEL_GEN_CONFIG_FILE)

KERNEL_COMMON_DEFCONFIG := $(KERNEL_ARCH_ARM_CONFIGS)/$(KERNEL_DEFCONFIG)
KERNEL_PRODUCT_CONFIGS := $(shell pwd)/device/hisi/customize/config/${TARGET_ARM_TYPE}/$(TARGET_DEVICE)/${TARGET_PRODUCT}/product_config/kernel_config
KERNEL_DEBUG_CONFIGS := $(KERNEL_ARCH_ARM_CONFIGS)/eng_defconfig/$(TARGET_BOARD_PLATFORM)

ifeq ($(strip $(TARGET_PRODUCT)), hisi_pilot)
KERNEL_PRODUCT_CONFIGS := $(shell pwd)/device/hisi/customize/config/${TARGET_ARM_TYPE}/hi6220/${TARGET_PRODUCT}/product_config/kernel_config
endif

define DTS_PARSE_CONFIG
@echo generating dtsi files, please wait for minutes!
@cd device/hisi/customize/build_script; ./auto_dts_gen.sh > $(ANDROID_BUILD_TOP)/auto_dts_gen.log 2>&1
endef

HI3650_MODEM_DRV_DIR := $(shell pwd)/vendor/hisi/modem/drv/acore/kernel/drivers/hisi/modem/drv
ifeq ($(wildcard $(HI3650_MODEM_DRV_DIR)),)
$(HI3650_MODEM_DRV_DIR):
	@mkdir -p $(HI3650_MODEM_DRV_DIR)
	@touch $(HI3650_MODEM_DRV_DIR)/Makefile
	@touch $(HI3650_MODEM_DRV_DIR)/Kconfig
endif

HISI_PILOT_KERNEL_DIR := $(shell pwd)/kernel/drivers/hisi_pilot/
DEPENDENCY_FILELIST := $(shell find $(ANDROID_BUILD_TOP)/device/hisi/customize/config/$(KERNEL_ARCH_PREFIX)/$(TARGET_BOARD_PLATFORM)/$(TARGET_PRODUCT)/board_config -name config.dts -type f 2>/dev/null | xargs echo)
DEPENDENCY_FILELIST += $(shell find $(ANDROID_BUILD_TOP)/device/hisi/customize/dtsi/$(KERNEL_ARCH_PREFIX)/$(TARGET_BOARD_PLATFORM) -type f 2>/dev/null | xargs echo)
GPIO_DEPENDENCY_FILELIST = $(shell find $(ANDROID_BUILD_TOP)/device/hisi/customize/config/$(KERNEL_ARCH_PREFIX)/$(TARGET_BOARD_PLATFORM)/$(TARGET_PRODUCT)/board_config -name iomux.xml -type f 2>/dev/null | xargs echo)
DEPENDENCY_FILELIST += $(GPIO_DEPENDENCY_FILELIST) $(shell find $(ANDROID_BUILD_TOP)/vendor/huawei/extra/power/batt_raw_data/data/$(TARGET_BOARD_PLATFORM) -name "*.xlsx" -type f 2>/dev/null | xargs echo)
DEPENDENCY_FILELIST += $(shell find $(ANDROID_BUILD_TOP)/vendor/huawei_platform/power/batt_raw_data/data/$(TARGET_BOARD_PLATFORM) -name "*.xlsx" -type f 2>/dev/null | xargs echo)

ifneq ($(filter hi3650 hi3650emulator, $(TARGET_BOARD_PLATFORM)),)
ifeq ($(strip $(CFG_HISI_MINI_AP)), false)
	APPEND_MODEM_DEFCONFIG := cat $(HISI_3650_MODEM_DEFCONFIG) >> $(KERNEL_GEN_CONFIG_PATH)
endif
endif

ifneq ($(filter hi6250, $(TARGET_BOARD_PLATFORM)),)
ifeq ($(strip $(CFG_HISI_MINI_AP)), false)
	APPEND_MODEM_DEFCONFIG := cat $(HISI_6250_MODEM_DEFCONFIG) >> $(KERNEL_GEN_CONFIG_PATH)
endif
endif

ifneq ($(filter hi3660, $(TARGET_BOARD_PLATFORM)),)
ifeq ($(strip $(CFG_HISI_MINI_AP)), false)
	APPEND_MODEM_DEFCONFIG := cat $(HISI_3660_MODEM_DEFCONFIG) >> $(KERNEL_GEN_CONFIG_PATH)
endif
endif

ifneq ($(TARGET_BUILD_VARIANT),eng)
KERNEL_DEBUG_CONFIGFILE := $(KERNEL_COMMON_DEFCONFIG)
KERNEL_TOBECLEAN_CONFIGFILE :=

$(KERNEL_DEBUG_CONFIGFILE):
	echo "will not compile debug modules"

else
KERNEL_DEBUG_CONFIGFILE :=  $(KERNEL_ARCH_ARM_CONFIGS)/hisi_$(TARGET_PRODUCT)_debug_defconfig
KERNEL_TOBECLEAN_CONFIGFILE := $(KERNEL_DEBUG_CONFIGFILE)

$(KERNEL_DEBUG_CONFIGFILE):$(KERNEL_COMMON_DEFCONFIG) $(wildcard $(KERNEL_DEBUG_CONFIGS)/*)
	@$(ANDROID_BUILD_TOP)/device/hisi/customize/build_script/kernel-config.sh -f $(KERNEL_COMMON_DEFCONFIG) -d $(KERNEL_DEBUG_CONFIGS) -o $(KERNEL_DEBUG_CONFIGFILE)
endif


GENERATE_DTB := $(KERNEL_OUT)/.timestamp
$(GENERATE_DTB):$(DEPENDENCY_FILELIST)
	$(DTS_PARSE_CONFIG)
	@mkdir -p $(KERNEL_OUT)
	@touch $@

ifeq ($(strip $(llt_gcov)),y)
HISI_MDRV_GCOV_DEFCONFIG := ${KERNEL_ARCH_ARM_CONFIGS}/gcov_defconfig
APPEND_MODEM_GCOV_DEFCONFIG := cat $(HISI_MDRV_GCOV_DEFCONFIG) >> $(KERNEL_GEN_CONFIG_PATH)
endif

$(KERNEL_GEN_CONFIG_PATH): $(KERNEL_DEBUG_CONFIGFILE) $(wildcard $(KERNEL_PRODUCT_CONFIGS)/*)
	$(hide) echo GENERATING $(KERNEL_GEN_CONFIG_FILE) ...
	$(shell $(ANDROID_BUILD_TOP)/device/hisi/customize/build_script/kernel-config.sh -f $(KERNEL_DEBUG_CONFIGFILE) -d $(KERNEL_PRODUCT_CONFIGS) -o $(KERNEL_GEN_CONFIG_PATH))
	$(shell $(APPEND_MODEM_DEFCONFIG))
ifeq ($(strip $(llt_gcov)),y)
	$(shell $(APPEND_MODEM_GCOV_DEFCONFIG))
endif

ifeq ($(OBB_PRINT_CMD), true)
$(KERNEL_CONFIG): MAKEFLAGS :=
$(KERNEL_CONFIG):
	mkdir -p $(KERNEL_OUT)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) hisi_$(TARGET_PRODUCT)_defconfig
else
ifeq ($(HISI_PILOT_LIBS), true)
$(KERNEL_CONFIG): $(KERNEL_GEN_CONFIG_PATH) HISI_PILOT_PREBUILD $(HI3650_MODEM_DRV_DIR)
else
$(KERNEL_CONFIG): $(KERNEL_GEN_CONFIG_PATH) $(HI3650_MODEM_DRV_DIR)
endif
	mkdir -p $(KERNEL_OUT)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) $(KERNEL_GEN_CONFIG_FILE)
endif

########Auto gen lcd effect parameter#######
ifeq ($(strip $(TARGET_BOARD_PLATFORM)), hi6250)
export LCD_EFFECT_DIR := $(shell pwd)/$(KERNEL_OUT)
LCD_EFFECT_TOOLS_PATH = vendor/huawei/extra/kernel/drivers/lcd/tools
LCD_EFFECT_FILE_PATH = $(LCD_EFFECT_DIR)/drivers/huawei_platform/lcd
LCD_EFFECT_FILE := $(LCD_EFFECT_FILE_PATH)/hw_lcd_effects.h
export PERLPATH := $(shell pwd)/vendor/huawei/extra/kernel/drivers/lcd/tools
$(LCD_EFFECT_FILE):
	@mkdir -p $(LCD_EFFECT_FILE_PATH)
	@cd $(LCD_EFFECT_TOOLS_PATH);export PERL5LIB=$(PERLPATH)/localperl/lib/site_perl/5.14.2/x86_64-linux-thread-multi:$(PERLPATH)/localperl/lib/site_perl/5.14.2:$(PERLPATH)/localperl/lib/5.14.2/x86_64-linux-thread-multi:$(PERLPATH)/localperl/lib/5.14.2;\
	./localperl/bin/perl hw_panel_gen_effect_h.pl $(LCD_EFFECT_FILE_PATH)
$(TARGET_PREBUILT_KERNEL): $(LCD_EFFECT_FILE)
endif
############################################

GPIO_IOMUX_FILE := kernel/drivers/hisi/hi3xxx/hisi_gpio_auto_gen.h
$(GPIO_IOMUX_FILE): $(GPIO_DEPENDENCY_FILELIST)
	@cd device/hisi/customize/build_script;perl ./gpio_complete_iomux_entry.pl $(KERNEL_ARCH_PREFIX) $(TARGET_BOARD_PLATFORM) "lp"; \
        python gen_pin_lp_config.py $(KERNEL_ARCH_PREFIX) $(TARGET_BOARD_PLATFORM)

idl_tool_script_path := $(shell pwd)/kernel/scripts/kernel_modem_idl_tool.py
driver_hisi_modem_out_dir := $(shell pwd)/$(KERNEL_OUT)/drivers/hisi/modem
kernel_driver_hisi_dir := $(shell pwd)/kernel/drivers/hisi

$(TARGET_PREBUILT_KERNEL): FORCE  $(GPIO_IOMUX_FILE)  $(GENERATE_DTB) | $(KERNEL_CONFIG)
ifeq ($(OBB_PRINT_CMD), true)
	$(hide) $(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) $(KERNEL_N_TARGET) $(UT_EXTRA_CONFIG)
	touch $(TARGET_PREBUILT_KERNEL)
else
ifeq ($(use_idl),true)
	cp -rf kernel kernel_tmp
	python -B $(idl_tool_script_path)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) modules_prepare
	mkdir -p $(driver_hisi_modem_out_dir)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) M=drivers/hisi/modem
	mv $(driver_hisi_modem_out_dir)/built-in.o $(driver_hisi_modem_out_dir)/kernel_modem.o
	find $(driver_hisi_modem_out_dir)/* -not -name "kernel_modem.o" | xargs rm -rf
	rm -rf kernel
	mv kernel_tmp kernel
	cp -rf $(BALONG_TOPDIR)/modem $(BALONG_TOPDIR)/modem_tmp
	cd $(BALONG_TOPDIR)/modem; find . -name "*.[h|c]" | xargs rm -rf
	cp -rf $(kernel_driver_hisi_dir)/modem $(kernel_driver_hisi_dir)/modem_tmp
	cd $(kernel_driver_hisi_dir)/modem; find . -name "*.[h|c]" | xargs rm -rf
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) KERNEL_MODEM_IDL_SPLIT=true
	rm -rf $(BALONG_TOPDIR)/modem
	mv $(BALONG_TOPDIR)/modem_tmp $(BALONG_TOPDIR)/modem
	rm -rf $(kernel_driver_hisi_dir)/modem
	mv $(kernel_driver_hisi_dir)/modem_tmp $(kernel_driver_hisi_dir)/modem
else
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX)
endif
	touch $(TARGET_PREBUILT_KERNEL)
	@rm -frv $(KERNEL_TOBECLEAN_CONFIGFILE)
	@rm -frv $(KERNEL_GEN_CONFIG_PATH)
endif

HISI_PILOT_PREBUILD:
	$(hide) rm -rf kernel/include/huawei_platform
	$(hide) rm -rf kernel/include/modem
	$(hide) rm -rf kernel/drivers/huawei_platform
	$(hide) rm -rf kernel/drivers/huawei_platform_legacy
	$(hide) rm -rf kernel/drivers/hisi/modem_hi6xxx
	$(hide) rm -rf kernel/drivers/device-depend-arm64
	$(hide) cp -rf $(HISI_PILOT_TOPDIR)kernel/include/huawei_platform kernel/include/.
	$(hide) cp -rf $(HISI_PILOT_TOPDIR)kernel/include/modem kernel/include/.
	$(hide) cp -rf $(HISI_PILOT_TOPDIR)kernel/drivers/huawei_platform kernel/drivers/
	$(hide) cp -rf $(HISI_PILOT_TOPDIR)kernel/drivers/huawei_platform_legacy kernel/drivers/
	$(hide) cp -rf $(HISI_PILOT_TOPDIR)kernel/drivers/hisi/modem_hi6xxx kernel/drivers/hisi/.
	$(hide) cp $(HISI_PILOT_KERNEL_DIR)/Makefile.pilot $(HISI_PILOT_KERNEL_DIR)/Makefile
	$(hide) cp $(HISI_PILOT_KERNEL_DIR)/Kconfig.pilot $(HISI_PILOT_KERNEL_DIR)/Kconfig
ifeq ($(TARGET_VERSION_MODE),factory)
	$(hide) cd kernel/drivers/; ln -s ../../vendor/hisi_pilot/libs_factory/kernel/drivers/device-depend-arm64 device-depend-arm64
else
	$(hide) cd kernel/drivers/; ln -s ../../vendor/hisi_pilot/libs/kernel/drivers/device-depend-arm64 device-depend-arm64
endif

kernelconfig: $(KERNEL_GEN_CONFIG_PATH)
	mkdir -p $(KERNEL_OUT)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) $(KERNEL_GEN_CONFIG_FILE) menuconfig

zImage Image:$(TARGET_PREBUILT_KERNEL)
	@mkdir -p $(dir $(INSTALLED_KERNEL_TARGET))
	@cp -fp $(TARGET_PREBUILT_KERNEL) $(INSTALLED_KERNEL_TARGET)
pclint_kernel: $(KERNEL_CONFIG)
	$(hide) $(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=$(KERNEL_ARCH_PREFIX) CROSS_COMPILE=$(CROSS_COMPILE_PREFIX) pc_lint_all

