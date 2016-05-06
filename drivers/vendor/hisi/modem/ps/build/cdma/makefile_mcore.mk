# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MOUDULES := cpscomm cencodix
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/nas/cdma),)
MOUDULES += cnas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cas),)
MOUDULES += cas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf),)
MOUDULES += cttf
endif

# process
.PHONY: cnas cas cttf cpscomm cencodix 
cps: $(MOUDULES)
cnas:
	$(MAKE)  -f modem/makefile_cnas.mk INSTANCE_ID=$(INSTANCE_ID)
cttf:
	$(MAKE)  -f modem/makefile_cttf.mk INSTANCE_ID=$(INSTANCE_ID)
cas:
	$(MAKE)  -f modem/makefile_cas.mk	INSTANCE_ID=$(INSTANCE_ID)
cpscomm:
	$(MAKE)  -f modem/makefile_cpscomm.mk	INSTANCE_ID=$(INSTANCE_ID)
cencodix:
	$(MAKE)  -f modem/makefile_cencodix.mk	INSTANCE_ID=$(INSTANCE_ID)

# clean
CLEAN_MOUDULES := clean-cpscomm clean-cencodix
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/nas/cdma),)
CLEAN_MOUDULES += clean-cnas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cas),)
CLEAN_MOUDULES += clean-cas
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf),)
CLEAN_MOUDULES += clean-cttf
endif

.PHONY: clean-cps clean-cnas clean-cas clean-cttf clean-cpscomm clean-cencodix

clean-cnas:
	$(MAKE)  -f modem/makefile_cnas.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-cas:
	$(MAKE)  -f modem/makefile_cas.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-cttf:
	$(MAKE)  -f modem/makefile_cttf.mk      clean INSTANCE_ID=$(INSTANCE_ID)
clean-cpscomm:
	$(MAKE)  -f modem/makefile_cpscomm.mk      clean INSTANCE_ID=$(INSTANCE_ID)
clean-cencodix:
	$(MAKE)  -f modem/makefile_cencodix.mk      clean INSTANCE_ID=$(INSTANCE_ID)

clean-cps: $(CLEAN_MOUDULES)
