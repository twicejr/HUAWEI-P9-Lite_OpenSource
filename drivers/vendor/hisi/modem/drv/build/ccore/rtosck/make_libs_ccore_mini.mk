# Created by Jeffery.zhai/199916 2012.03.21

include $(BALONG_TOPDIR)/build/scripts/make_base.mk
#*********************************************** 
# obc define
#*********************************************** 
OBC_LOCAL_CORE_NAME		:=ccore
OBC_LOCAL_MOUDLE_NAME	:=balong_modem_mini

#LIB
OBC_LOCAL_LIB_FILE		:= ccore_mini.o
OBC_LOCAL_LIB_FILE		:=$(addprefix $(OBB_PRODUCT_DELIVERY_DIR)/lib/,$(OBC_LOCAL_LIB_FILE))

#ld
OBC_LD_SCRIPT_FILE	    :=$(BALONG_TOPDIR)/build/scripts/rules/ld_rtosck_link.ld

OBC_LD_RAM_LOW_ADDR		:=$(CFG_MCORE_TEXT_START_ADDR)
OBC_LD_VX_START_ADDR	:=$(OBC_LD_RAM_LOW_ADDR)
OBC_LOCAL_CLEAN_DIRS    :=
OBC_LOCAL_CLEAN_FILES	:= 

#*****************************************************************************
# input parameters
#*****************************************************************************
OBC_LOCAL_LIB_DIR		?=

OBC_LOCAL_CORE_NAME		?=
OBC_LOCAL_MOUDLE_NAME	        ?=

OBC_LD_RAM_LOW_ADDR		?=
OBC_LD_RAM_HIGH_ADDR	        ?=
OBC_LD_VX_START_ADDR	        ?=$(OBC_LD_RAM_LOW_ADDR)

OBC_LD_DEFINES			:= -defsym _VX_DATA_ALIGN=0x1

#*****************************************************************************
# complier config
#*****************************************************************************
TCLSH					:=$(BALONG_TOPDIR)/build/tools/utility/tools/tcl/bin/tclsh
TCL_SCRIPTS_PATH		:=$(BALONG_TOPDIR)/build/tools/utility/tools/tcl/scripts
OBJDUMP_PATH            := $(HCC_HOME)/bin/arm-none-eabi-objdump

CC						:= arm-none-eabi-gcc
CC_FLAGS				:= -c -fdollars-in-identifiers -O2 -fno-builtin  -fno-short-enums -fno-short-wchar
AR						:= arm-none-eabi-ld
AR_FLAGS				:= -r 
LD						:= arm-none-eabi-ld

LD_FLAGS				:= -X -N -EL -e osResetVector -Ttext $(OBC_LD_VX_START_ADDR) 
LD_FLAGS				+= -L$(OBB_PRODUCT_DELIVERY_DIR)/lib 
SIZE					?= arm-none-eabi-size

#********************************************************
# Dirs and Targets define
#********************************************************
LIB_LIBRARY_FILE       :=$(OBB_PRODUCT_DELIVERY_DIR)/lib/$(OBC_LOCAL_MOUDLE_NAME)
IMAGE_TARGET_FILE      :=$(OBB_PRODUCT_DELIVERY_DIR)/lib/$(OBC_LOCAL_MOUDLE_NAME)
PRJ_OBJ_PATH           :=$(OBB_PRODUCT_DELIVERY_DIR)/obj/

# pre link
PRELINK_OBJ_PATH :=$(OBB_PRODUCT_DELIVERY_DIR)/obj/prelink_$(OBC_LOCAL_CORE_NAME)
PRELINK_LIB_TARGET ?=$(OBB_PRODUCT_DELIVERY_DIR)/lib/prelink_$(OBC_LOCAL_CORE_NAME).o
PRELINK_PATH :=$(RTOSCK_OS_PATH)/prelink
OS_LIB_PATH := -L$(RTOSCK_OS_PATH)/lib
OS_LIB_PATH += -L$(HCC_BASE)/lib
OS_LIB_PATH += -L$(HCC_HOME)/lib/gcc/arm-none-eabi/4.7.1
OS_LIB_PATH += -lstdc++
OS_LIB_INC  += $(OS_LIB_PATH)

# mini OS dependency Libs
LOCAL_OS_LIBS  := -lCortexAXsec_c -lc -lgcc -lm

# LD Lib define
LIB_FILES       := $(foreach val,$(OBC_LOCAL_LIB_DIR),$(wildcard $(val)/*.o $(val)/*.a) $(val)/*.lib) 
LOCAL_USER_LIBS := $(LIB_FILES) $(OBC_LOCAL_LIB_FILE)
FULL_LIB_PATH     := $(foreach lib_path, $(LOCAL_LIB_DIR), -L$(lib_path))
DELIVERY_LIB_DIR      := $(OBB_PRODUCT_DELIVERY_DIR)/lib
#*************************************************************************
# rules
#*************************************************************************
.PHONY: all pre_link do_link do_img post_link do_all_before
all: pre_link do_link do_img post_link do_all_before
	@echo - do [$@]

### Rules order
do_all_before :post_link
post_link :do_img
do_img : do_link
do_link : pre_link
pre_link :
### Rules order end

#
# pre_link
#
pre_link: $(PRELINK_LIB_TARGET)
	@echo do [$@]

$(PRELINK_LIB_TARGET): $(LOCAL_USER_LIBS)
	echo $(LOCAL_USER_LIBS)
	$(Q)mkdir -p $(PRELINK_OBJ_PATH)

# Image file (.elf) to generate
do_link:$(LIB_LIBRARY_FILE).elf
	@echo do [$@]

$(LIB_LIBRARY_FILE).elf :  $(LOCAL_USER_LIBS) $(OBC_LD_SCRIPT_FILE) $(PRELINK_LIB_TARGET) | pre_link
	@echo [LD] $@
	$(Q)$(LD) $(LD_FLAGS)  $(LOCAL_BOOT_OBJS) \
	$(LOCAL_USER_LIBS)  $(OBC_LD_DEFINES) -T $(OBC_LD_SCRIPT_FILE) --start-group $(OS_LIB_INC) $(LOCAL_OS_LIBS) \
	--end-group -o $(LIB_LIBRARY_FILE).elf
	$(Q)$(SIZE) -v $(OBC_LD_RAM_HIGH_ADDR) $(OBC_LD_RAM_LOW_ADDR) $(LIB_LIBRARY_FILE).elf

# Bin file (.bin)
post_link:$(IMAGE_TARGET_FILE).bin
	@echo do [$@]
	
$(IMAGE_TARGET_FILE).bin: $(LIB_LIBRARY_FILE).elf | do_link
	@echo [BIN] $@
	$(Q)arm-none-eabi-objcopy -O binary -R .bss $(LIB_LIBRARY_FILE).elf $(IMAGE_TARGET_FILE).bin
	$(Q)-rm -rf $(OBC_LOCAL_LIB_FILE)

.PHONY: clean
clean:
	@echo -  do [$@]
	$(Q)-rm -f $(LIB_LIBRARY_FILE).elf $(IMAGE_TARGET_FILE).bin
	$(Q)-rm -rf $(PRELINK_OBJ_PATH)
	$(Q)-rm -rf $(OBC_LOCAL_CLEAN_DIRS)
