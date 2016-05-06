# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MOUDULES := pscomm nas encodix
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/was),)
ifeq ($(INSTANCE_ID),INSTANCE_0)
MOUDULES += gas was_public was_private gttf wttf_public wttf_private ascomm
endif
ifeq ($(INSTANCE_ID),INSTANCE_1)
MOUDULES +=  gas  ascomm gttf
ifeq ($(CFG_FEATURE_MODEM1_SUPPORT_WCDMA) ,FEATURE_ON)
MOUDULES += was_public was_private wttf_public wttf_private
endif
endif
ifeq ($(INSTANCE_ID),INSTANCE_2)
MOUDULES +=  gas  ascomm gttf
endif
endif
ifeq ($(CFG_FEATURE_BASTET), FEATURE_ON)
MOUDULES += bastet
MOUDULES += bstopenssl
endif

# process
.PHONY: gups nas gas was_public was_private gttf wttf_public wttf_private pscomm ascomm bastet bstopenssl encodix
gups: $(MOUDULES)

nas:
	$(MAKE)  -f MODEM_CORE/makefile_nas.mk INSTANCE_ID=$(INSTANCE_ID)
	$(MAKE)  -f MODEM_CORE/makefile_rabm.mk INSTANCE_ID=$(INSTANCE_ID)
gas:
	$(MAKE)  -f MODEM_CORE/makefile_gas.mk	INSTANCE_ID=$(INSTANCE_ID)
was_public:
	$(MAKE)  -f MODEM_CORE/makefile_was_public.mk	INSTANCE_ID=$(INSTANCE_ID)
was_private:
	$(MAKE)  -f MODEM_CORE/makefile_was_private.mk	INSTANCE_ID=$(INSTANCE_ID)	
gttf:
	$(MAKE)  -f MODEM_CORE/makefile_gttf.mk INSTANCE_ID=$(INSTANCE_ID)
wttf_public:
	$(MAKE)  -f MODEM_CORE/makefile_wttf_public.mk INSTANCE_ID=$(INSTANCE_ID)
wttf_private:
	$(MAKE)  -f MODEM_CORE/makefile_wttf_private.mk INSTANCE_ID=$(INSTANCE_ID)
ascomm:
	$(MAKE)  -f MODEM_CORE/makefile_ascomm.mk INSTANCE_ID=$(INSTANCE_ID)
pscomm:
	$(MAKE)  -f MODEM_CORE/makefile_pscomm.mk INSTANCE_ID=$(INSTANCE_ID)
bastet:
	$(MAKE)  -f MODEM_CORE/makefile_bastet.mk
bstopenssl:
	$(MAKE)  -f MODEM_CORE/makefile_bstopenssl.mk
encodix:
	$(MAKE)  -f MODEM_CORE/makefile_encodix.mk INSTANCE_ID=$(INSTANCE_ID)
	
CLEAN_MOUDULES:= clean-nas clean-pscomm clean-encodix
ifeq ($(CFG_FEATURE_BASTET), FEATURE_ON)
CLEAN_MOUDULES += clean-bastet
CLEAN_MOUDULES += clean-bstopenssl
endif
ifneq ($(wildcard $(BALONG_TOPDIR)/modem/ps/as/gu/was),)
ifeq ($(INSTANCE_ID),INSTANCE_0)
CLEAN_MOUDULES += clean-gas clean-was_public clean-was_private clean-gttf clean-wttf_public clean-wttf_private clean-ascomm
endif
ifeq ($(INSTANCE_ID),INSTANCE_1)
CLEAN_MOUDULES += clean-gas clean-ascomm clean-gttf
ifeq ($(CFG_FEATURE_MODEM1_SUPPORT_WCDMA) ,FEATURE_ON)
CLEAN_MOUDULES += clean-was_public clean-was_private clean-wttf_public clean-wttf_private
endif
endif
ifeq ($(INSTANCE_ID),INSTANCE_2)
CLEAN_MOUDULES += clean-gas clean-ascomm clean-gttf
endif
endif

.PHONY: clean-gups clean-nas clean-gas clean-was_public clean-was_private clean-gttf clean-wttf_public clean-wttf_private clean-pscomm clean-ascomm clean-bastet clean-bstopenssl clean-encodix

clean-nas:
	$(MAKE)  -f MODEM_CORE/makefile_nas.mk clean INSTANCE_ID=$(INSTANCE_ID)
	$(MAKE)  -f MODEM_CORE/makefile_rabm.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-gas:
	$(MAKE)  -f MODEM_CORE/makefile_gas.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-was_pulibc:
	$(MAKE)  -f MODEM_CORE/makefile_was_public.mk	clean INSTANCE_ID=$(INSTANCE_ID)
clean-was_private:
	$(MAKE)  -f MODEM_CORE/makefile_was_private.mk	clean INSTANCE_ID=$(INSTANCE_ID)	
clean-gttf:
	$(MAKE)  -f MODEM_CORE/makefile_gttf.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-wttf_public:
	$(MAKE)  -f MODEM_CORE/makefile_wttf_public.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-wttf_private:
	$(MAKE)  -f MODEM_CORE/makefile_wttf_private.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-ascomm:
	$(MAKE)  -f MODEM_CORE/makefile_ascomm.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-pscomm:
	$(MAKE)  -f MODEM_CORE/makefile_pscomm.mk clean INSTANCE_ID=$(INSTANCE_ID)
clean-bastet:
	$(MAKE)  -f MODEM_CORE/makefile_bastet.mk clean
clean-bstopenssl:
	$(MAKE)  -f MODEM_CORE/makefile_bstopenssl.mk clean

clean-encodix:
	$(MAKE)  -f MODEM_CORE/makefile_encodix.mk clean  INSTANCE_ID=$(INSTANCE_ID)

clean-gups: $(CLEAN_MOUDULES)
