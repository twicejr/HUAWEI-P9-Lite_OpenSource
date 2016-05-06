#
# Main Makefile for building the corresponding module functioned target
#
#
#
# set the coorespondig path to the project root directory
# DO NOT change the variable value, or else if YOU know what you are changing
export ROOT_DEPTH=../../../..


DMAC_SCRDIR=$(WIFI_SRCDIR)\DMAC
export DRV_TEST_DIR=$(WIFI_SRCDIR)\DRV_TEST\DMAC
# set the default make target
# NOTICE: make sure that the target name here is same with the module
# build target defined at the bottom
.PHONY:module_build

# include the config file to setup the compiling environment
#include $(PWD)/$(ROOT_DEPTH)/Script/Build/1151_Host_WiFi/env.config

# set the module objects files
obj-m :=dmac.o
dmac-objs := $(DMAC_SCRDIR)\dmac_main.o $(DMAC_SCRDIR)\dmac_mgmt_classifier.o $(DMAC_SCRDIR)\dmac_psm_ap.o $(DMAC_SCRDIR)\dmac_rx_data.o $(DMAC_SCRDIR)\dmac_tid.o $(DMAC_SCRDIR)\dmac_tx_bss_comm.o				\
			 $(DMAC_SCRDIR)\dmac_11w.o $(DMAC_SCRDIR)\dmac_tx_complete.o $(DMAC_SCRDIR)\dmac_user.o $(DMAC_SCRDIR)\dmac_vap.o $(DMAC_SCRDIR)\mac_device.o $(DMAC_SCRDIR)\mac_frame.o $(DMAC_SCRDIR)\mac_user.o		\
			 $(DMAC_SCRDIR)\mac_vap.o $(DMAC_SCRDIR)\dmac_data_acq.o $(DMAC_SCRDIR)\mac_ie.o $(DMAC_SCRDIR)\dmac_uapsd.o $(DMAC_SCRDIR)\dmac_mgmt_bss_comm.o $(DMAC_SCRDIR)\dmac_beacon.o $(DMAC_SCRDIR)\dmac_alg.o	\
			 $(DMAC_SCRDIR)\dmac_blockack.o $(DMAC_SCRDIR)\mac_resource.o $(DMAC_SCRDIR)\dmac_mgmt_ap.o $(DMAC_SCRDIR)\dmac_mgmt_sta.o $(DMAC_SCRDIR)\dmac_wep.o $(DMAC_SCRDIR)\dmac_11i.o	\
			 $(DMAC_SCRDIR)\mac_regdomain.o $(DMAC_SCRDIR)\dmac_scan.o $(DMAC_SCRDIR)\dmac_dfx.o $(DMAC_SCRDIR)\dmac_reset.o $(DMAC_SCRDIR)\dmac_config.o $(DMAC_SCRDIR)\dmac_stat.o $(DMAC_SCRDIR)\dmac_fcs.o \
			 $(DMAC_SCRDIR)\dmac_acs.o $(DMAC_SCRDIR)\dmac_chan_mgmt.o $(DMAC_SCRDIR)\dmac_user_track.o $(DMAC_SCRDIR)\dmac_rx_filter.o $(DMAC_SCRDIR)\dmac_txopps.o	\
			 $(DMAC_SCRDIR)\dmac_dft.o $(DMAC_SCRDIR)\dmac_device.o $(DMAC_SCRDIR)\dmac_resource.o $(DMAC_SCRDIR)\dmac_ap_pm.o $(DMAC_SCRDIR)\mac_pm.o  $(DMAC_SCRDIR)\dmac_hcc_adapt.o $(DMAC_SCRDIR)\mac_board.o $(DMAC_SCRDIR)\mac_data.o $(DMAC_SCRDIR)\dmac_psm_sta.o $(DMAC_SCRDIR)\dmac_sta_pm.o
dmac-objs += $(DMAC_SCRDIR)\dmac_p2p.o $(DMAC_SCRDIR)\dmac_uapsd_sta.o $(DMAC_SCRDIR)\dmac_pm_sta.o
dmac-objs += $(DMAC_SCRDIR)\dmac_btcoex.o $(DMAC_SCRDIR)\dmac_ltecoex_verify.o $(DMAC_SCRDIR)\dmac_arp_offload.o $(DMAC_SCRDIR)\dmac_auto_adjust_freq.o
dmac-dump-objs := $(dmac-objs)

#dmac-objs += $(DRV_TEST_DIR)\dmac_test_sch.o
#dmac-objs += $(DRV_TEST_DIR)\dmac_test_main.o \
#	     $(DRV_TEST_DIR)\dmac_lpm_test.o \
#	     $(DRV_TEST_DIR)\dmac_frame_filter_test.o \
#		 $(DRV_TEST_DIR)\dmac_wmm_test.o  \
#		 $(DRV_TEST_DIR)\dmac_dfs_test.o  \
#		 $(DRV_TEST_DIR)\dmac_scan_test.o \
#		 $(DRV_TEST_DIR)\dmac_acs_test.o
dmac_dump_objs += dmac_test_main.o dmac_lpm_test.o dmac_frame_filter_test.o dmac_test_sch.o dmac_wmm_test.o

# set the feature options
#include $(PWD)/$(ROOT_DEPTH)/Script/Build/1151_Host_WiFi/caps.config

# for example:
# ifeq ($(SUPPORT_VIDEO_OPTIMIZE),1)
#	alg-objs += alg_video.o
# endif

# set the module name
MODULE_NAME=$(subst .o,.ko,$(obj-m))

BACKUP_OBJFILE_FOLDER=$(strip $(subst .o,,$(obj-m)))_objfile

BACKUP_OBJFILE_DIR=$(PWD)/$(BACKUP_OBJFILE_FOLDER)

OBJDUMP_FILE=$(subst .o,.objdump,$(obj-m))
OBJDUMP_TXT_FILE=$(subst .o,.txt,$(obj-m))

# module's elf header file name
MODULE_ELF_HEADER_FILE=$(subst .o,.elf_header,$(obj-m))
