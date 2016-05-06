# Created by zhaijiye/00199916, 2012-03-23
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

RFILE_PTAH := $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system/rfile
CFG_PRODUCT_CFG_KERNEL_ENTRY ?= 0x0

ifeq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
ARCH :=arm64
else
ARCH :=arm
endif

.PHONY:all pre_build bsp_kernel bsp_android bsp_wifi
all: bsp_system_zip
	@echo do [$@]
# nv
pre_build:
	$(Q)tar -cf $(OBB_PRODUCT_DELIVERY_DIR)/lib/scripts.tar  -C $(BALONG_TOPDIR)/modem/drv/common/scripts .
ifneq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
	$(Q)$(MAKE) -C $(CFG_ANDROID_DIR)/bootable/bootloader/legacy/main clean
	$(Q)$(MAKE) -C $(CFG_ANDROID_DIR)/bootable/bootloader/legacy/main
endif

bsp_kernel:pre_build


ifeq ($(strip $(CFG_CONFIG_SLIC)),m)
SLIC_TARGETS := slic_module
ZARLINK_API_PATH :=$(BALONG_TOPDIR)/modem/thirdparty/zarlink/zarlink_api
SLIC_PATH := $(LINUX_KERNEL)/sound/soc/balong
SLIC_OBJ := $(BALONG_TOPDIR)/system/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/obj/KERNEL_OBJ
SLIC_OUT := $(SLIC_OBJ)/sound/soc/balong/slic
SLIC_OUT_DIR := $(SLIC_OUT)/out/slic

$(SLIC_TARGETS):pre_build 
	$(Q)mkdir -p $(SLIC_OUT)/out
	$(Q)-cp -fr $(SLIC_PATH)/* $(SLIC_OUT)/out
	$(Q)-cp -fr $(ZARLINK_API_PATH) $(SLIC_OUT_DIR)
	$(Q)$(MAKE) -C $(SLIC_OUT_DIR) -f $(SLIC_OUT_DIR)/Makefile "SLIC_PATH=$(SLIC_OUT_DIR)" \
		"KERNEL_OBJ_DIR=$(OUT_KERNEL)" "ARCH=$(ARCH)" "CROSS_COMPILE=$(CROSS_COMPILE)" all
	$(Q)-cp -fr $(SLIC_OUT_DIR)/snd_soc_balong.ko $(SLIC_OUT)/snd_soc_balong.ko
else
SLIC_TARGETS :=
endif

ifeq ($(strip $(CFG_CONFIG_AUDIO)),m)
AUDIO_TARGETS := audio_module
AUDIO_PATH := $(LINUX_KERNEL)/sound/soc/balong
AUDIO_OBJ := $(BALONG_TOPDIR)/system/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/obj/KERNEL_OBJ
AUDIO_OUT := $(AUDIO_OBJ)/sound/soc/balong/audio
AUDIO_OUT_DIR := $(AUDIO_OUT)/out/audio

$(AUDIO_TARGETS):pre_build 
	$(Q)mkdir -p $(AUDIO_OUT)/out
	$(Q)-cp -fr $(AUDIO_PATH)/* $(AUDIO_OUT)/out
	$(Q)$(MAKE) -C $(AUDIO_OUT_DIR) -f $(AUDIO_OUT_DIR)/Makefile "AUDIO_PATH=$(AUDIO_OUT_DIR)" \
		"KERNEL_OBJ_DIR=$(OUT_KERNEL)" "ARCH=$(ARCH)" "CROSS_COMPILE=$(CROSS_COMPILE)" all
	$(Q)-cp -fr $(AUDIO_OUT_DIR)/snd_soc_audio.ko $(AUDIO_OUT)/snd_soc_audio.ko
else
AUDIO_TARGETS :=
endif

ifeq ($(strip $(CFG_CONFIG_OF)),YES)
CFG_DTS_SIZE := $(CFG_DDR_ACORE_DTS_SIZE)

else
CFG_DTS_SIZE := 0
endif

ifneq ($(strip $(OBB_LLT_MDRV)), n)
.PHONY: mtp_acore mtp_clean mtp_pkg mtp_image_check
LLTMDRV_DIR ?= $(BALONG_TOPDIR)/llt/mdrv
mtp_acore:
	$(Q)mkdir -p $(LLTMDRV_DIR)/out && \
		$(Q)$(MAKE) -C $(LLTMDRV_DIR)/out -f $(LLTMDRV_DIR)/Makefile "top_srcdir=$(LLTMDRV_DIR)" \
		"llt_core=acore" "KERNEL_OBJ_DIR=$(OUT_KERNEL)" "LINUX_DIR=$(LINUX_KERNEL)"  all

mtp_clean:
	$(Q)mkdir -p $(LLTMDRV_DIR)/out && \
		$(Q)$(MAKE) -C $(LLTMDRV_DIR)/out -f $(LLTMDRV_DIR)/Makefile "top_srcdir=$(LLTMDRV_DIR)" \
		"llt_core=acore" "KERNEL_OBJ_DIR=$(OUT_KERNEL)" "LINUX_DIR=$(LINUX_KERNEL)" clean

mtp_pkg:
	$(Q)$(MAKE) -C $(LLTMDRV_DIR)/out -f $(LLTMDRV_DIR)/Makefile "top_srcdir=$(LLTMDRV_DIR)" \
	   "DESTDIR=$(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/" \
		"KERNEL_OBJ_DIR=$(OUT_KERNEL)" "LINUX_DIR=$(LINUX_KERNEL)" install
	$(Q)tar -zcf $(OBB_PRODUCT_DELIVERY_DIR)/image/mtp.tar.gz -C \
		$(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME) mtp

do_clean: | mtp_clean
mtp_image_check:
	$(Q)$(MAKE) -C $(LLTMDRV_DIR)/out -f $(LLTMDRV_DIR)/Makefile "top_srcdir=$(LLTMDRV_DIR)" \
	 "LINUX_DIR=$(LINUX_KERNEL)" "KERNEL_OBJ_DIR=$(OUT_KERNEL)" mtp_image_check
endif


bsp_android: bsp_kernel
	MAKEFLAGS= ./build_android.sh $(BALONG_TOPDIR) $(CFG_ANDROID_DIR) $(CFG_OS_ANDROID_PRODUCT_NAME) $(CFG_PRODUCT_CFG_KERNEL_ENTRY)

ifeq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
bsp_system_zip:bsp_android 
	echo do [$@]
	$(Q)mkdir -p $(RFILE_PTAH)

	$(Q)cd $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/ && mkdir -p modem_fs/yaffs0/SC/Pers
	$(Q)$(CFG_ANDROID_DIR)/out/host/linux-x86/bin/make_ext4fs -s -l 12582912 -a modemom $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_fs.img $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_fs 

	$(Q)cd $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/ && mkdir -p modem_nv/modem_nv modem_nv/SC/Pers
	$(Q)$(CFG_ANDROID_DIR)/out/host/linux-x86/bin/make_ext4fs -s -l 8388608 -b 1024 -a modemnv $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_nv.img $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_nv 

ifneq ($(strip $(tiny)),true)
	$(Q)cp -fp $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system.img $(OBB_PRODUCT_DELIVERY_DIR)/image/system.img
endif
else
bsp_system_zip:bsp_android $(SLIC_TARGETS) $(AUDIO_TARGETS) 
	echo do [$@]
	$(Q)mkdir -p $(RFILE_PTAH)
ifeq ($(strip $(CFG_CONFIG_SLIC)),m)
	$(Q)-cp -f $(SLIC_OUT_DIR)/snd_soc_balong.ko $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system/bin/
	$(Q)$(CROSS_COMPILE)strip --strip-unneeded $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system/bin/snd_soc_balong.ko
	$(Q)-rm -fr $(SLIC_OUT)/out
endif

ifeq ($(strip $(CFG_CONFIG_AUDIO)),m)
	$(Q)-cp -f $(AUDIO_OUT_DIR)/snd_soc_audio.ko $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system/bin/
	$(Q)$(CROSS_COMPILE)strip --strip-unneeded $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system/bin/snd_soc_audio.ko
	$(Q)-rm -fr $(AUDIO_OUT)/out
endif

ifneq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
	$(Q)$(CFG_ANDROID_DIR)/out/host/linux-x86/bin/mkyaffs2image -c 2048 -s 16 $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system_2k.img
	$(Q)$(CFG_ANDROID_DIR)/out/host/linux-x86/bin/mkyaffs2image -c 4096 -s 16 $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system_4k.img
endif
ifeq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
	$(Q)cd $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/ && mkdir -p modem_fs/yaffs0/SC/Pers
	$(Q)$(CFG_ANDROID_DIR)/out/host/linux-x86/bin/make_ext4fs -s -l 12582912 -a modemom $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_fs.img $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_fs 
	$(Q)cd $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/ && mkdir -p modem_nv/modem_nv modem_nv/SC/Pers
	$(Q)$(CFG_ANDROID_DIR)/out/host/linux-x86/bin/make_ext4fs -s -l 8388608 -b 1024 -a modemnv $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_nv.img $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/modem_nv 
endif
ifneq ($(strip $(tiny)),true)
	$(Q)cp -fp $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)/system_*.img $(OBB_PRODUCT_DELIVERY_DIR)/image/
endif
endif

	$(Q)-cp -pf $(V) $(ACORE_TARGET_DIR)/*.sh $(OBB_PRODUCT_DELIVERY_DIR)/image
	$(Q)-chmod 777 $(OBB_PRODUCT_DELIVERY_DIR)/image/*.sh


# android independent image
ifeq ($(PCLINT_ENABLE),true)
%image %.img : 
	@echo do [$@]
	MAKEFLAGS= ./build_android.sh $(BALONG_TOPDIR) $(CFG_ANDROID_DIR) $(CFG_OS_ANDROID_PRODUCT_NAME) $(CFG_PRODUCT_CFG_KERNEL_ENTRY) pclint_$@
else
%image %.img : bsp_kernel
	@echo do [$@]
	MAKEFLAGS= ./build_android.sh $(BALONG_TOPDIR) $(CFG_ANDROID_DIR) $(CFG_OS_ANDROID_PRODUCT_NAME) $(CFG_PRODUCT_CFG_KERNEL_ENTRY) $@
endif

ACORE_TARGET_DIR := $(CFG_ANDROID_DIR)/out/target/product/$(CFG_OS_ANDROID_PRODUCT_NAME)

LW_ACORE_TARGET := "secdtimage secbl31image secxloaderimage secxloaderddrtestimage secfastbootimage seclpm3image"
LW_AOCRE_IMG := dt.img kernel bl31.bin sec_bl31.bin sec_fastboot.img fastboot.img fastboot.no_debug.img sec_xloader.img sec_xloader_ddr_test.img xloader.img xloader_ddr_test.img sec_dt.img lpm3.img sec_lpm3.img
LW_AOCRE_IMG_ABS := $(addprefix $(ACORE_TARGET_DIR)/, $(LW_AOCRE_IMG))
LW_AOCRE_LIB := bl31.elf fastboot.elf fastboot.img.elf fastboot.map
LW_AOCRE_LIB_ABS := $(addprefix $(ACORE_TARGET_DIR)/, $(LW_AOCRE_LIB))

lw_acore : bsp_kernel
	@echo do [$@]
	UPDATE_API=false MAKEFLAGS= ./build_android.sh $(BALONG_TOPDIR) $(CFG_ANDROID_DIR) $(CFG_OS_ANDROID_PRODUCT_NAME) $(CFG_PRODUCT_CFG_KERNEL_ENTRY) $(LW_ACORE_TARGET)
	$(Q)cp -pf $(V) $(ACORE_TARGET_DIR)/obj/KERNEL_OBJ/vmlinux $(OBB_PRODUCT_LIB_DIR)
	$(Q)cp -pf $(V) $(LW_AOCRE_IMG_ABS)  $(OBB_PRODUCT_DELIVERY_DIR)/image
	$(Q)cp -pf $(V) $(LW_AOCRE_LIB_ABS)  $(OBB_PRODUCT_LIB_DIR)

%.mk %akefile :
	@echo nothing to be done for [$@]

force:
	@echo nothing to be done for [$@]
# 
%:: bsp_kernel
	$(warning do[$@])
	MAKEFLAGS= ./build_android.sh $(BALONG_TOPDIR) $(CFG_ANDROID_DIR) $(CFG_OS_ANDROID_PRODUCT_NAME) $(CFG_PRODUCT_CFG_KERNEL_ENTRY) $@

.PHONY:clean
clean: do_clean
ifneq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
	$(Q)$(MAKE) -C $(CFG_ANDROID_DIR)/bootable/bootloader/legacy/main clean
ifneq ($(wildcard $(CFG_ANDROID_DIR)/build),)
	$(Q)$(MAKE) -s -C $(CFG_ANDROID_DIR) clean 
endif
else
ifneq ($(wildcard $(CFG_ANDROID_DIR)/build),)
	$(Q)-rm -rf $(CFG_ANDROID_DIR)/out
endif
endif
	$(Q)-rm -f $(OBB_PRODUCT_DELIVERY_DIR)/image/system*.img 
	$(Q)-rm -f $(OBB_PRODUCT_DELIVERY_DIR)/lib/scripts.tar

do_clean:
	@echo nothing to be done for [$@]

#pclint
ifeq ($(strip $(CFG_BSP_CONFIG_PHONE_TYPE)),YES)
PCLINT_SYSTEM_INC_FILE		:=$(BALONG_TOPDIR)/build/tools/pc_lint/lint/android_hi3630.lnt
PCLINT_INC_FILE				:=$(BALONG_TOPDIR)/modem/drv/build/acore/pclint_inc_hi3630.lnt
PCLINT_SRC_PLATFORM_FILE	:=$(BALONG_TOPDIR)/modem/drv/build/acore/pclint_src_hi3630.lnt
else
PCLINT_SYSTEM_INC_FILE		:=$(BALONG_TOPDIR)/build/tools/pc_lint/lint/android.lnt
PCLINT_SRC_PLATFORM_FILE	:=$(BALONG_TOPDIR)/modem/drv/build/acore/pclint_src_hi6930.lnt
PCLINT_INC_FILE				:=$(BALONG_TOPDIR)/modem/drv/build/acore/pclint_inc.lnt
endif
PCLINT_SYSTEM_INC_FILE		:=$(BALONG_TOPDIR)/build/tools/pc_lint/lint/android.lnt
PCLINT_INC_VAR				:=
PCLINT_SRC_FILE				:=$(BALONG_TOPDIR)/modem/drv/build/acore/pclint_src.lnt
PCLINT_CC_OPTION			:=
OBC_LOCAL_MOUDLE_NAME		?=bsp_acore
.PHONY: $(maction)
$(maction) : do_$(maction)
	@echo acore $(maction) is ready.

ifneq ($(strip $(maction)),)
OBC_USE_NEW_PC_LINT            :=true
ifeq ($(strip $(OBC_USE_NEW_PC_LINT)),false)
include $(BALONG_TOPDIR)/build/scripts/rules/pclint_rules.mk
else
PCLINT_SYSTEM_INC_FILE		:=$(BALONG_TOPDIR)/build/tools/pc_lint/lint/android.lnt
include makefile_flexelint_common_files.mk
include makefile_flexelint_files_$(CFG_PLATFORM).mk
include $(BALONG_TOPDIR)/build/scripts/rules/pclint_rules_new.mk
endif
endif
