# Created by Jeffery.zhai/199916 2012.03.21

# What are targets ?
$(warning The targets are $(MAKECMDGOALS).)

# guess the Top dir
BALONG_TOPDIR ?= $(patsubst %modem/ps,%,$(CURDIR))

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
.PHONY:all mcore acore bootrom bootloader tools_config
all: mcore acore bootrom bootloader
	@echo do [$@]
	
mcore :
	$(MAKE) $(OBB_JOBS) -f makefile_mcore.mk $(MODULE) INSTANCE_ID=INSTANCE_0
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
	$(MAKE) $(OBB_JOBS) -f makefile_mcore.mk $(MODULE) INSTANCE_ID=INSTANCE_1
ifeq ($(CFG_MULTI_MODEM_NUMBER) ,3) 
	$(MAKE) $(OBB_JOBS) -f makefile_mcore.mk $(MODULE) INSTANCE_ID=INSTANCE_2
endif
endif

bootrom : 
	@echo do [$@]

acore : 
#	$(MAKE)  $(OBB_JOBS)  -f makefile_acore.mk

tools_config :
	$(MAKE)  $(OBB_JOBS) -f TOOLS_CONFIG/makefile_tools_config.mk 

bootloader : 
	@echo do [$@]

# clean
.PHONY: clean clean-tools_config
clean:
ifeq ($(OBB_CORE_NAME),all)
	$(MAKE)  $(OBB_JOBS)  -f makefile_mcore.mk $@
#	$(MAKE)  $(OBB_JOBS)  -f makefile_acore.mk $@
else
	$(MAKE)  $(OBB_JOBS)  -f makefile_$(OBB_CORE_NAME).mk $@
endif
	
	@echo "PS_CODE clean complete."

clean-tools_config :
	$(MAKE) $(OBB_JOBS) -f TOOLS_CONFIG/makefile_tools_config.mk clean
