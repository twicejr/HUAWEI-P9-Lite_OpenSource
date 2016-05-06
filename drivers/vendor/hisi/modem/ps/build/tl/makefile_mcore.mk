# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

MOUDULES:= tlnas tlas ll2 tas lcs_nas

# process
.PHONY: lps tlnas tlas ll2 tas lcs_nas
lps: $(MOUDULES)

tlnas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_tlnas.mk
tlas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_tlas.mk	
ll2:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_ll2.mk
tas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_tas.mk
lcs_nas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_lcs_nas.mk INSTANCE_ID=$(INSTANCE_ID)

CLEAN_MOUDULES:= clean-tlnas clean-tlas clean-ll2 clean-tas clean-lcs_nas

.PHONY: clean clean-tlnas clean-tlas clean-ll2 clean-tas clean-lcs_nas

clean : clean-tlnas clean-tlas clean-ll2 clean-tas clean-lcs_nas

clean-tlnas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_tlnas.mk clean
clean-tlas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_tlas.mk	clean
clean-ll2:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_ll2.mk clean
clean-tas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_tas.mk clean
clean-lcs_nas:
	$(MAKE)  $(OBB_JOBS)  -f MODEM_CORE/makefile_lcs_nas.mk clean INSTANCE_ID=$(INSTANCE_ID)

clean-lps: $(CLEAN_MOUDULES)
