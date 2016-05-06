# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=ccore
ifeq ($(INSTANCE_ID),INSTANCE_0)
OBC_LOCAL_MOUDLE_NAME	?=bsp_ccore
endif

ifeq ($(INSTANCE_ID),INSTANCE_1)
OBC_LOCAL_MOUDLE_NAME	?=bsp_ccore1
endif

ifeq ($(INSTANCE_ID),INSTANCE_2)
OBC_LOCAL_MOUDLE_NAME	?=bsp_ccore2
endif

OBC_LOCAL_USER_OBJ_FILE =

#***********************************************************#
# compiler flags
#***********************************************************#
OBC_CORE_TYPE   =CORE_MODEM
OBC_TMP_CORE_TYPE =BSP_CORE_MODEM
OBC_BUILD_TYPE	=BUILD_ONEBUILDER

CC_USER_DEFINES := -DPRJ_BUILD -D__OS_RTOSCK__
AS_USER_DEFINES := -DPRJ_BUILD -D__OS_RTOSCK__

CC_USER_FLAGS   := -D$(OBC_BUILD_TYPE) -D$(OBC_TMP_CORE_TYPE) -D$(OBC_CORE_TYPE) -DCPU_CORTEXA8 -DARMMMU=ARMMMU_CORTEXA8 \
					-DARMCACHE=ARMCACHE_CORTEXA8 -DIP_PORT_VXWORKS=68 -DINET -DOBC_IMAGE_MODEM

ifneq ($(HUTAF_HLT_COV),true)
CC_USER_FLAGS   += -Werror
endif

AS_USER_FLAGS   := -D$(OBC_BUILD_TYPE) -D$(OBC_TMP_CORE_TYPE) -D$(OBC_CORE_TYPE) -D_WRS_KERNEL -DARMEL -DCPU_CORTEXA8 \
					-DARMMMU=ARMMMU_CORTEXA8 -DARMCACHE=ARMCACHE_CORTEXA8 -DIP_PORT_VXWORKS=68 -DINET -DOBC_IMAGE_MODEM

ifneq ($(INSTANCE_ID) ,)
CC_USER_FLAGS	+=-D$(strip $(INSTANCE_ID) )
endif

ifeq ($(strip $(OBB_SEPARATE)),true)
CC_USER_FLAGS += -DDRV_BUILD_SEPARATE
AS_USER_FLAGS += -DDRV_BUILD_SEPARATE
endif

############
ifeq ($(CFG_CONFIG_HISI_FAMA),true)
AS_USER_FLAGS += -DCONFIG_HISI_FAMA
CC_USER_FLAGS += -DCONFIG_HISI_FAMA
endif

CC_USER_FLAGS += -march=armv7-a


#***********************************************************#
# Source File to compile
#***********************************************************#
BSP_DIR			    :=$(BALONG_TOPDIR)/drv/ccore
OS_SRC_DIR			:=$(OBB_PRODUCT_DELIVERY_DIR)/os/$(OBC_LOCAL_CORE_NAME)
ASIC_DIR_NAME		:=$(CFG_BSP_ASIC_DIR_NAME)

# common file
CORE_INDEX :=1
include makefile_common_files.mk
# include ipcom_ipdomain_inc.mk


# CFG_FEATURE_MULTIMODE_GUL


# CFG_BUILD_SEPARATE


# CFG_ENABLE_TEST_CODE


# CFG_PRODUCT_CFG_ENABLE_BUS_STRESS_TEST_CODE


#CFG_PRODUCT_CFG_ENABLE_GU_BUS_STRESS_TEST_CODE

ifeq ($(strip $(llt_gcov)),y)
CC_USER_FLAGS += -fprofile-arcs -ftest-coverage
CC_USER_FLAGS += -DDRV_BUILD_GCOV
endif
#***********************************************************
#include rules. must be droped at the bottom
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/cc_rtosck_rules.mk

#pclint
PCLINT_SYSTEM_INC_FILE		:=$(BALONG_TOPDIR)/build/tools/pc_lint/lint/vxworks.lnt
PCLINT_INC_VAR				:=$(addsuffix /,$(FULL_SRC_INC_PATH)) -I$(BALONG_TOPDIR)/build/tools/pc_lint/lint/external/
ifeq ($(strip $(CFG_BSP_CONFIG_PHONE_TYPE)),YES)
PCLINT_SRC_PLATFORM_FILE	:=$(BALONG_TOPDIR)/modem/drv/build/ccore/pclint_src_hi3630.lnt
else
PCLINT_SRC_PLATFORM_FILE	:=$(BALONG_TOPDIR)/modem/drv/build/ccore/pclint_src_hi6930.lnt
endif
PCLINT_SRC_FILE				:=$(BALONG_TOPDIR)/modem/drv/build/ccore/pclint_src.lnt
PCLINT_CC_OPTION			:=$(LOCAL_CC_OPTION)

.PHONY: $(maction)
$(maction): do_$(maction)
	@echo ccore $(maction) is ready.
force:
	@echo nothing to be done for [$@]

ifneq ($(strip $(maction)),)
OBC_USE_NEW_PC_LINT            :=true
ifeq ($(strip $(OBC_USE_NEW_PC_LINT)),false)
include $(BALONG_TOPDIR)/build/scripts/rules/pclint_rules.mk
else
include makefile_flexelint_common_files.mk
include makefile_flexelint_files_$(CFG_PLATFORM).mk
include $(BALONG_TOPDIR)/build/scripts/rules/pclint_rules_new.mk
endif
endif
