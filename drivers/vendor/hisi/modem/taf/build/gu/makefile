# What are targets ?
$(warning The targets are $(MAKECMDGOALS).)

# guess the Top dir
BALONG_TOPDIR ?= $(patsubst %modem/taf,%,$(CURDIR))

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
.PHONY:all mcore mcore1 mcore2 tools_config
all: mcore mcore1 mcore2
	@echo do [$@]
	
mcore : 
	$(MAKE) -f makefile_mcore.mk INSTANCE_ID=INSTANCE_0

mcore1 :
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
	$(MAKE) -f makefile_mcore.mk INSTANCE_ID=INSTANCE_1
endif	
mcore2 :
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
ifeq ($(CFG_MULTI_MODEM_NUMBER) ,3)
	$(MAKE) -f makefile_mcore.mk INSTANCE_ID=INSTANCE_2
endif	
endif	

tools_config :
	$(MAKE) -f makefile_tools_config.mk
# clean
.PHONY: clean clean-tools_config
clean:
	$(MAKE) -f makefile_mcore.mk clean INSTANCE_ID=INSTANCE_0
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
	$(MAKE) -f makefile_mcore.mk clean INSTANCE_ID=INSTANCE_1
ifeq ($(CFG_MULTI_MODEM_NUMBER) ,3)
	$(MAKE) -f makefile_mcore.mk clean INSTANCE_ID=INSTANCE_2
endif
endif
	@echo "taf clean complete."

clean-tools_config:
	$(MAKE) -f makefile_tools_config.mk clean
