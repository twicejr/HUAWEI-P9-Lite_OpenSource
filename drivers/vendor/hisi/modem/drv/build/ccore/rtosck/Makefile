# Created by Jeffery.zhai/199916 2012.03.21

# What are targets ?
$(warning The targets are $(MAKECMDGOALS).)

# guess the Top dir
BALONG_TOPDIR ?= $(patsubst %/modem/drv,%,$(CURDIR))

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
.PHONY:drv ccore ccore1 ccore2 ccore_mini tools_config
drv: ccore ccore1 ccore2 drv_ccore_mini
	@echo do [$@]
	
ccore : 
	$(MAKE)  $(OBB_JOBS)  -f makefile_ccore.mk INSTANCE_ID=INSTANCE_0 $(maction)
ccore1 :
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
	$(MAKE)  -f makefile_ccore.mk INSTANCE_ID=INSTANCE_1
endif
ccore2 :
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON)
ifeq ($(CFG_MULTI_MODEM_NUMBER) ,3)
	$(MAKE)  -f makefile_ccore.mk INSTANCE_ID=INSTANCE_2
endif
endif

tools_config : 
	$(MAKE)  $(OBB_JOBS)  -f makefile_tools_config.mk

ifneq ($(strip $(OBB_LLT_MDRV)), n)
.PHONY: mtp_ccore mtp_clean
LLTMDRV_DIR ?= $(BALONG_TOPDIR)/llt/mdrv
mtp_ccore:
	$(Q)mkdir -p $(LLTMDRV_DIR)/out/ccore_obj
	$(Q)$(MAKE) $(OBB_AKE) $(OBB_JOBS) -C $(LLTMDRV_DIR)/out -f $(LLTMDRV_DIR)/Makefile "llt_core=ccore" \
		"top_srcdir=$(LLTMDRV_DIR)" \
		1>$(OBB_PRODUCT_LOG_DIR)/obuild_$(@).log 2>&1 $(SERIAL_OPTION)
mtp_clean:
	@rm -rf $(LLTMDRV_DIR)/out/ccore_obj
	@rm -rf $(OBB_PRODUCT_DELIVERY_DIR)/lib/llt*.o
	@rm -rf $(OBB_PRODUCT_DELIVERY_DIR)/obj/llt_*
clean: | mtp_clean
endif
#L2cache screening case
ifeq ($(strip $(CFG_FEATURE_BALONG_L2CACHE_SCREENING)),YES)
drv_ccore_mini:
	@echo do [$@]
	$(Q)$(MAKE)  $(OBB_JOBS)  -f makefile_ccore_mini.mk  $(maction)
	$(Q)$(MAKE)  $(OBB_JOBS)  -f make_libs_ccore_mini.mk  $(maction)
else
drv_ccore_mini:
	@echo do [$@]
endif	
# clean
.PHONY: clean clean-tools_config
clean:
	rm -rf $(OBB_PRODUCT_DELIVERY_DIR)/lib/bsp*.o
	rm -rf $(OBB_PRODUCT_DELIVERY_DIR)/obj/bsp_*
ifeq ($(OBB_CORE_NAME),all)
	$(MAKE)  $(OBB_JOBS)  -f makefile_ccore.mk $@ INSTANCE_ID=INSTANCE_0
else
	#$(MAKE)  $(OBB_JOBS)  -f makefile_$(OBB_CORE_NAME).mk $@ INSTANCE_ID=INSTANCE_0
endif
ifeq ($(CFG_FEATURE_MULTI_MODEM) ,FEATURE_ON) 
	$(MAKE)  -f makefile_ccore.mk $@ INSTANCE_ID=INSTANCE_1
ifeq ($(CFG_MULTI_MODEM_NUMBER) ,3) 
	$(MAKE)  -f makefile_ccore.mk $@ INSTANCE_ID=INSTANCE_2
endif
endif

#L2cache screening case
ifeq ($(strip $(CFG_FEATURE_BALONG_L2CACHE_SCREENING)),YES)
	$(Q)$(MAKE)  $(OBB_JOBS)  -f makefile_ccore_mini.mk  $@
	$(Q)$(MAKE)  $(OBB_JOBS)  -f make_libs_ccore_mini.mk  $@
endif
	@echo "drv clean complete."

clean-tools_config :
	$(MAKE)  $(OBB_JOBS)  -f makefile_tools_config.mk clean
	