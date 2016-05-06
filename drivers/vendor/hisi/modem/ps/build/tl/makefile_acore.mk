# Created by Jeffery.zhai/199916 2012.03.21

# include the define at the top
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

# Variable Definition(used in cc_linux_acore.rules)
OBC_LOCAL_CORE_NAME		:=acore
OBC_LOCAL_MOUDLE_NAME	:=lps_acore

OBC_SHELL_FUNC_NAME  :=  lps
OBC_SYNC_INCLUDE_DIRS := COMM_CODE/ \
						COMM_CODE_GU/ \
						PS_CODE/ \

OBC_SYNC_EXCLUDE_DIRS := *.dll *.exe *.lib *.exp *.ilk *.dsp *.doc *.xls *.rar *.ncb *.bat *.chm *.d *.o *.ko *.bat *.gz *.zip \
					.svn/*** \
					.git/*** \
					COMM_CODE/lost+found/*** \
					COMM_CODE/DOC/*** \
					COMM_CODE/Balong_Drv/***\
					COMM_CODE/Balong_GU_Inc/*** \
					COMM_CODE/Balong_LTE_Inc/LPS/config/***\
					COMM_CODE/ProductConfig/Product/***\					 \
					 \
					COMM_CODE_GU/Balong_GU_Inc/DOC/*** \
					COMM_CODE_GU/lost+found/*** \
					COMM_CODE_GU/ProductConfig/Product/***\
					 \
					PS_CODE/Build/*** \
					PS_CODE/GU_CODE/***\
					PS_CODE/lost+found/*** \
					PS_CODE/LTE_CODE/*** \
					 \
					COMM_CODE/*** \
					DRV_CODE/*** \
					DRV_CODE_GU/***\
					DSP_CODE_GU/*** \
					PHY_CODE/*** \
					MSP_CODE/*** \
					MSP_CODE_GU/*** \
					PS_CODE_GU/*** \
					TARGET/*** \

OBC_SERVER_CLEAN_DIRS :=PS_CODE 
OBC_SERVER_TARGETS :=bin/LPS.o  log/lps_acore_linux.log
OBC_LOCAL_CLEAN_FILES :=lib/LPS.o log/lps_acore_linux.log

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_linux_rules.mk
