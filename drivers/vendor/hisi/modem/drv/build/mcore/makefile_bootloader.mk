
#***********************************************************
# include the define at the top
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************
# root dir 
#***********************************************************
OBC_LOCAL_MOUDLE_NAME ?=m3boot
BSP_DIR             :=$(BALONG_TOPDIR)/modem/drv
BSP_MCORE_DIR       :=$(BALONG_TOPDIR)/modem/drv/mcore


#*************************************************************************
# Compilter-Specific flags & Configuration
#*************************************************************************
M3_CROSS_COMPILE    ?=$(CFG_ANDROID_DIR)/prebuilts/gcc/linux-x86/arm/arm-eabi-4.7/bin/arm-eabi-
CC                  :=$(M3_CROSS_COMPILE)gcc
AS                  :=$(M3_CROSS_COMPILE)as
AR                  :=$(M3_CROSS_COMPILE)ar
LD                  :=$(M3_CROSS_COMPILE)ld
OBJDUMP             :=$(M3_CROSS_COMPILE)objdump
OBJCOPY             :=$(M3_CROSS_COMPILE)objcopy
SIZE                :=$(M3_CROSS_COMPILE)size

USER_AS_DEFINES     :=
USER_AS_FLAGS       :=-mcpu=cortex-m3 -mthumb -D__ASSEMBLY__ -x assembler-with-cpp -MD -c -D__CMSIS_RTOS -D__M3_OS__ -D__M3BOOT__
USER_AS_OPTIM_FLAGS :=
USER_C_FLAGS        :=-mcpu=cortex-m3 -mthumb -MD -c -D__CMSIS_RTOS -D__M3BOOT__
USER_LD_FLAGS       :=-X -EL -N 
LINKER_SCRIPT_SRC   :=$(BSP_DIR)/build/mcore/boot.ld.S
LINKER_SCRIPT       :=$(BSP_DIR)/build/mcore/boot.ld

ifeq ($(strip $(OBB_BUILD_TYPE)),RELEASE)
USER_C_OPTIM_FLAGS  :=-Os
USER_AS_OPTIM_FLAGS :=
else
USER_C_OPTIM_FLAGS  := -g -Os
USER_AS_OPTIM_FLAGS :=
endif 

#***********************************************************
# source files
#***********************************************************
# startup
OBC_LOCAL_SRC_FILE := \
	$(BSP_MCORE_DIR)/boot/m3boot.S \
	$(BSP_MCORE_DIR)/boot/bsp_sec_m3boot.c \
	$(BSP_MCORE_DIR)/boot/lib.c \
	$(BSP_MCORE_DIR)/boot/nand.c 

ifeq ($(strip $(CFG_BSP_CONFIG_P531_ASIC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_p531_asic.S \
	$(BSP_MCORE_DIR)/boot/mddrc_p531_asic_333.c
endif

ifeq ($(strip $(CFG_BSP_CONFIG_V7R2_SFT)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v7r2_porting.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v7r2_porting.c
endif

ifeq ($(strip $(CFG_BSP_CONFIG_V711_PORTING)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v711_porting.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v711_porting.c \
	$(BSP_MCORE_DIR)/boot/tsensor_balong.c \
	$(BSP_MCORE_DIR)/boot/pmu.c \
	$(BSP_MCORE_DIR)/boot/boosting_v711.c
endif

ifeq ($(strip $(CFG_BSP_CONFIG_V711_ASIC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/tsensor_balong.c \
	$(BSP_MCORE_DIR)/boot/pmu.c \
	$(BSP_MCORE_DIR)/boot/boosting_v711.c

ifeq ($(strip $(CFG_BSP_CONFIG_EMU)),NO)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v711_asic.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v711_asic.c
else
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v711_emu.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v711_emu.c
endif # end of CFG_BSP_CONFIG_EMU

endif # end of CFG_BSP_CONFIG_V711_ASIC

ifeq ($(strip $(CFG_BSP_CONFIG_V7R2_ASIC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v7r2_asic.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v7r2_asic.c \
	$(BSP_MCORE_DIR)/boot/tsensor_balong.c \
	$(BSP_MCORE_DIR)/boot/pmu.c \
	$(BSP_MCORE_DIR)/boot/boosting_v7r2.c
endif
ifeq ($(strip $(CFG_BSP_CONFIG_P532_ASIC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_p532_asic_533.S \
	$(BSP_MCORE_DIR)/boot/mddrc_p532_asic_533.c \
		$(BSP_MCORE_DIR)/boot/boosting.c
endif

ifeq ($(strip $(CFG_BSP_CONFIG_HI6950)),YES)

ifneq ($(strip $(CFG_BSP_CONFIG_SFT)),YES)
ifneq ($(strip $(CFG_BSP_CONFIG_EMU_PALADIN)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v7r5_asic.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v7r5_asic.c \
	$(BSP_MCORE_DIR)/boot/tsensor_balong.c 
ifeq ($(strip $(CFG_ATE_VECTOR)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/ddr_ate_test.c
endif
endif
endif

ifeq ($(strip $(CFG_BSP_CONFIG_SFT)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v7r5_porting.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v7r5_porting.c
endif

ifeq ($(strip $(CFG_BSP_CONFIG_EMU_PALADIN)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v7r5_porting.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v7r5_porting.c
endif

endif

ifeq ($(strip $(CFG_ATE_VECTOR)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/ate_vector.c
endif

# start of CFG_BSP_CONFIG_HI6932
ifeq ($(strip $(CFG_BSP_CONFIG_HI6932)),YES)
ifneq ($(strip $(CFG_BSP_CONFIG_SFT)),YES)
ifneq ($(strip $(CFG_BSP_CONFIG_EMU_PALADIN)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v722_asic.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v722_asic.c  \
	$(BSP_MCORE_DIR)/boot/ddr_exmbist_v722.c 
ifeq ($(strip $(CFG_ATE_VECTOR)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/ddr_ate_test_v722.c
endif
endif
endif

ifeq ($(strip $(CFG_BSP_CONFIG_SFT)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v722_porting.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v722_porting.c
endif

ifeq ($(strip $(CFG_BSP_CONFIG_EMU_PALADIN)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/sysctrl_v722_porting.S \
	$(BSP_MCORE_DIR)/boot/mddrc_v722_porting.c
endif

endif
# end of CFG_BSP_CONFIG_HI6932


ifeq ($(strip $(CFG_CONFIG_DDR_SECURITY)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_MCORE_DIR)/boot/mddrc_sec_cfg.c
endif


CMSIS_RTOS_RTX_DIR :=$(BALONG_TOPDIR)/modem/system/cmsis/cmsis_rtos_rtx_v4p70
CMSIS_ORG_DIR :=$(BALONG_TOPDIR)/modem/system/cmsis/CMSIS-SP-00300-r3p2-00rel1
CMSIS_INC_PATH      :=$(CMSIS_RTOS_RTX_DIR)/INC $(CMSIS_RTOS_RTX_DIR)/SRC $(CMSIS_ORG_DIR)/CMSIS/Include

OBC_LOCAL_INC_DIR  := \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config \
	$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc \
	$(BALONG_TOPDIR)/modem/include/drv/common \
	$(BALONG_TOPDIR)/modem/drv/common/include \
	$(BSP_MCORE_DIR)/boot \
	$(BSP_MCORE_DIR)/kernel/libc \
	$(BSP_MCORE_DIR)/kernel/sys \
	$(BSP_MCORE_DIR)/kernel/include \
	$(BSP_MCORE_DIR)/kernel/drivers/serial \
	$(BSP_MCORE_DIR)/kernel/drivers/om \
	$(CMSIS_INC_PATH)

#object 
LOCAL_OBJ_PATH      := $(OBB_PRODUCT_DELIVERY_DIR)/obj/$(OBC_LOCAL_MOUDLE_NAME)
LOCAL_LIBRARY       := $(OBB_PRODUCT_DELIVERY_DIR)/lib/$(OBC_LOCAL_MOUDLE_NAME).elf
LOCAL_IMAGE_FILE    := $(OBB_PRODUCT_DELIVERY_DIR)/lib/$(OBC_LOCAL_MOUDLE_NAME).bin
CODE_SIZE_FILE      := $(LOCAL_OBJ_PATH)/$(OBC_LOCAL_MOUDLE_NAME).code.size
OBJ_LIST_FILE       := $(LOCAL_OBJ_PATH)/$(OBC_LOCAL_MOUDLE_NAME).obj.list
# include path
FULL_SRC_INC_PATH  := $(foreach lib_inc_path, $(OBC_LOCAL_INC_DIR), -I$(lib_inc_path))

# as files process 
FULL_AS_SRCS       := $(filter %.S,$(OBC_LOCAL_SRC_FILE))
FULL_AS_OBJS       := $(patsubst $(BALONG_TOPDIR)/%.S,$(LOCAL_OBJ_PATH)/%.o, $(subst \,/,$(FULL_AS_SRCS)))
FULL_AS_DEPENDS     := $(patsubst %.o,%.d,$(FULL_AS_OBJS))
FULL_C_SRCS        := $(filter %.c,$(OBC_LOCAL_SRC_FILE))
FULL_C_OBJS        := $(patsubst $(BALONG_TOPDIR)/%.c,$(LOCAL_OBJ_PATH)/%.o, $(subst \,/,$(FULL_C_SRCS)))
FULL_C_DEPENDS      := $(patsubst %.o,%.d,$(FULL_C_OBJS))
OBJ_AS_DIRS        := $(sort $(dir $(FULL_AS_OBJS)))
OBJ_AS_DIRS        := $(patsubst %/,%,$(OBJ_AS_DIRS))

.PHONY: all do_pre_build do_build do_lib_before do_lib do_post_build_before do_post_build
all: do_pre_build do_build do_lib_before do_lib do_post_build_before do_post_build
	@echo - do [$@]
do_post_build: do_post_build_before
do_post_build_before: do_lib
do_lib: do_lib_before
do_lib_before: do_build
do_build: do_pre_build

do_pre_build:
	@echo -  do [$@]
ifneq ($(strip $(OBJ_AS_DIRS)),)
	$(Q)mkdir -p $(OBJ_AS_DIRS)
endif

do_build : $(FULL_AS_OBJS) $(FULL_C_OBJS)
	@echo do [$@]
ifneq ($(strip $(FULL_AS_OBJS)),)
ifneq ($(MAKECMDGOALS),clean)
sinclude $(FULL_AS_DEPENDS)
endif

$(FULL_AS_OBJS): $(LOCAL_OBJ_PATH)/%.o :$(BALONG_TOPDIR)/%.S | do_pre_build
	@echo [AS] $@
	$(CC) $(USER_AS_FLAGS) $(FULL_SRC_INC_PATH) $< -o $@ 
endif
ifneq ($(strip $(FULL_C_OBJS)),)
ifneq ($(MAKECMDGOALS),clean)
sinclude $(FULL_C_DEPENDS)
endif

$(FULL_C_OBJS): $(LOCAL_OBJ_PATH)/%.o :$(BALONG_TOPDIR)/%.c | do_pre_build
	$(CC) $(USER_C_FLAGS) $(USER_C_OPTIM_FLAGS) $(FULL_SRC_INC_PATH) $< -o $@
endif

do_lib_before : FORCE
	@echo do [$@]
	$(Q)$(CC) $(USER_C_FLAGS) $(USER_C_OPTIM_FLAGS) $(FULL_SRC_INC_PATH) -P -E -o $(LINKER_SCRIPT) $(LINKER_SCRIPT_SRC)

do_lib : $(LOCAL_LIBRARY)
	@echo do [$@]

$(LOCAL_LIBRARY): $(FULL_AS_OBJS)  | do_lib_before
	$(Q)echo $(FULL_AS_OBJS)  > $(OBJ_LIST_FILE)

	@echo [LD] $(LOCAL_LIBRARY)
	$(Q)$(LD) $(USER_LD_FLAGS) $(FULL_AS_OBJS) $(FULL_C_OBJS) -Map $(basename $@).map -T $(LINKER_SCRIPT)  -o $@

do_post_build: $(LOCAL_IMAGE_FILE)
$(LOCAL_IMAGE_FILE) : $(LOCAL_LIBRARY) | do_post_build_before
	@echo [BIN] $@
	$(Q)$(OBJCOPY) -O binary -S $(LOCAL_LIBRARY) $@
	$(Q)$(OBJDUMP) -S $(LOCAL_LIBRARY) > $(basename $@).asm
	-$(Q)$(SIZE) -t $(LOCAL_LIBRARY) > $(CODE_SIZE_FILE)

#***********************************************************
# Clean up 
#***********************************************************
.PHONY: FORCE
FORCE:

.PHONY: clean
clean:
	@echo -  do [$@]
	$(Q)-rm -f *.d *.ld
	$(Q)-rm -rf $(LOCAL_OBJ_PATH)
	$(Q)-rm -f $(OBJ_LIST_FILE) $(CODE_SIZE_FILE) $(basename $(LOCAL_LIBRARY)).* $(basename $(LOCAL_IMAGE_FILE)).*
