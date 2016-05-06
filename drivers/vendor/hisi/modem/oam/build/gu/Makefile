# Created by Jeffery.zhai/199916 2012.03.21

# What are targets ?
$(warning The targets are $(MAKECMDGOALS).)

# guess the Top dir
BALONG_TOPDIR ?= $(patsubst %modem/oam,%,$(CURDIR))

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
.PHONY:all mcore mcore1 mcore2 acore bootrom bootloader tools_config
all: mcore mcore1 mcore2 acore bootrom bootloader
	@echo do [$@]
	
mcore : 
	$(MAKE)   -f makefile_mcore.mk INSTANCE_ID=INSTANCE_0
mcore1 :
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
	$(MAKE)  -f makefile_mcore.mk INSTANCE_ID=INSTANCE_1
endif
mcore2 :
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
ifeq ($(CFG_MULTI_MODEM_NUMBER) ,3)
	$(MAKE)  -f makefile_mcore.mk INSTANCE_ID=INSTANCE_2
endif
endif
	
tools_config :
	$(MAKE)  $(OBB_JOBS) -f makefile_tools_config.mk 
	
bootrom : 
	@echo do [$@]

acore : 
	#$(MAKE) -f makefile_acore.mk

bootloader : 
	@echo do [$@]

# clean
.PHONY: clean clean-tools_config
clean:
ifeq ($(OBB_CORE_NAME),all)
	$(MAKE)   -f makefile_mcore.mk $@ INSTANCE_ID=INSTANCE_0
	#$(MAKE) -f makefile_acore.mk $@
else
	$(MAKE)   -f makefile_$(OBB_CORE_NAME).mk $@ INSTANCE_ID=INSTANCE_0
endif

ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
	$(MAKE)   -f makefile_mcore.mk $@ INSTANCE_ID=INSTANCE_1
ifeq ($(CFG_MULTI_MODEM_NUMBER) ,3)
	$(MAKE)   -f makefile_mcore.mk $@ INSTANCE_ID=INSTANCE_2
endif
endif
	@echo "DRV_CODE clean complete."

clean-tools_config:
	$(MAKE) -f  makefile_tools_config.mk clean
