# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MOUDULES :=
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/),)
MOUDULES += cas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/),)
MOUDULES += cttf
endif

# process
.PHONY: all cas cttf
all: $(MOUDULES)
cas:
	$(MAKE)  -f tools_config/makefile_tools_config_cas.mk
cttf:
	$(MAKE)  -f tools_config/makefile_tools_config_cttf.mk


CLEAN_MOUDULES:=
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/),)
CLEAN_MOUDULES += clean-cas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/),)
CLEAN_MOUDULES += clean-cttf
endif

# process
.PHONY: clean clean-cas clean-cttf
clean: $(CLEAN_MOUDULES)
clean-cas:
	$(MAKE)  -f tools_config/makefile_tools_config_cas.mk clean
clean-cttf:
	$(MAKE)  -f tools_config/makefile_tools_config_cttf.mk clean
