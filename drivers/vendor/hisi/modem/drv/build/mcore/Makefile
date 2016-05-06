# Created by Jeffery.zhai/199916 2012.03.21

# What are targets ?
$(warning The targets are $(MAKECMDGOALS).)

# guess the Top dir
BALONG_TOPDIR ?= $(patsubst %/drv/build/mcore,%,$(CURDIR))

# Make sure that there are no spaces in the absolute path; the build system can't deal with them.
ifneq ($(words $(BALONG_TOPDIR)),1)
$(warning ************************************************************)
$(warning You are building in a directory whose absolute path contains a space character)
$(warning "$(BALONG_TOPDIR)")
$(warning Please move your source tree to a path that does not contain any spaces.)
$(warning ************************************************************)
$(error Directory names containing spaces not supported)
endif

# include the define at the top
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

# process
.PHONY:all mcore raminit bootrom bootloader
ifneq ($(strip $(CFG_ATE_VECTOR)),YES)
all: mcore raminit bootrom bootloader
	@echo do [$@]
else
all: raminit bootloader
	@echo do [$@]
endif

mcore :
ifneq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
	$(MAKE)  $(OBB_JOBS)  -f makefile_mcore.mk
endif
$(maction):
	$(MAKE)  $(OBB_JOBS)  -f makefile_mcore.mk $(maction)
	@echo mcore $(maction) end

raminit : 
ifeq ($(strip $(CFG_BSP_USB_BURN)),YES)
	$(MAKE)  $(OBB_JOBS)  -C $(BALONG_TOPDIR)/modem/drv/mcore/ramInit/
endif
bootrom :
	@echo do [$@]

bootloader : 
ifneq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
	$(MAKE)  $(OBB_JOBS)  -f makefile_bootloader.mk
endif

# clean
.PHONY: clean
clean:
	$(MAKE) $(OBB_JOBS) -f makefile_mcore.mk $@
	$(MAKE) $(OBB_JOBS) -f makefile_bootloader.mk $@
	$(Q)echo "COMM_CODE clean complete."
