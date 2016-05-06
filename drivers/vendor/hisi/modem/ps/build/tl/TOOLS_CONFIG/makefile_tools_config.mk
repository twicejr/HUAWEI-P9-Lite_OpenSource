# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MOUDULES :=
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/tl/),)
MOUDULES += tlas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/nas/tl/),)
MOUDULES += tlnas
endif

# process
.PHONY: all tlas tlnas
all: $(MOUDULES)
tlas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_tlas.mk
tlnas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_tlnas.mk

#clean
CLEAN_MOUDULES:= 
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/tl/),)
CLEAN_MOUDULES += clean-tlas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/nas/tl/),)
CLEAN_MOUDULES += clean-tlnas
endif

# process
.PHONY: clean clean-tlas clean-tlnas
clean: $(CLEAN_MOUDULES)
clean-tlas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_tlas.mk clean
clean-tlnas:
	$(MAKE)  -f TOOLS_CONFIG/makefile_tools_config_tlnas.mk clean
