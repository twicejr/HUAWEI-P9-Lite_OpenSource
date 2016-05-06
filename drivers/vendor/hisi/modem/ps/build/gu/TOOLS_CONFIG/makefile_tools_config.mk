# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MOUDULES :=
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/),)
MOUDULES += gttf wttf
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/gas/),)
MOUDULES += gas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/was/),)
MOUDULES += was
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/nas/comm/),)
MOUDULES += gucnas
endif

# process
.PHONY: all gttf wttf gas was gucnas
all: $(MOUDULES)
gttf:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_gttf.mk
wttf:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_wttf.mk
gas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_gas.mk
was:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_was.mk
gucnas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_gucnas.mk


CLEAN_MOUDULES:= 
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/),)
CLEAN_MOUDULES += clean-gttf clean-wttf
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/gas/),)
CLEAN_MOUDULES += clean-gas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/was/),)
CLEAN_MOUDULES += clean-was
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/nas/comm/),)
CLEAN_MOUDULES += clean-gucnas
endif

# process
.PHONY: clean clean-gttf clean-wttf clean-gas clean-was clean-gucnas
clean: $(CLEAN_MOUDULES)
clean-gttf:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_gttf.mk clean
clean-wttf:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_wttf.mk clean
clean-gas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_gas.mk clean
clean-was:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_was.mk clean
clean-gucnas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_gucnas.mk clean
