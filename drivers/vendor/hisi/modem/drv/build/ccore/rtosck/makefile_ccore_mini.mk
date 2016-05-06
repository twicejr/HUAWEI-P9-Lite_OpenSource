# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=ccore
OBC_LOCAL_MOUDLE_NAME	?=ccore_mini
OBC_LOCAL_USER_OBJ_FILE =

#***********************************************************#
# compiler flags
#***********************************************************#
OBC_CORE_TYPE   =CORE_MODEM
OBC_TMP_CORE_TYPE =BSP_CORE_MODEM
OBC_BUILD_TYPE	=BUILD_ONEBUILDER

CC_USER_DEFINES := -DPRJ_BUILD -D__OS_RTOSCK__
AS_USER_DEFINES := -DPRJ_BUILD -D__OS_RTOSCK__

CC_USER_FLAGS   := -D$(OBC_BUILD_TYPE) -D$(OBC_TMP_CORE_TYPE) -D$(OBC_CORE_TYPE)
CC_USER_FLAGS   += -Werror
AS_USER_FLAGS   := -D$(OBC_BUILD_TYPE) -D$(OBC_TMP_CORE_TYPE) -D$(OBC_CORE_TYPE)


CC_USER_FLAGS += -march=armv7-a


#***********************************************************#
# Source File to compile
#***********************************************************#
DRV_DIR                  :=$(BALONG_TOPDIR)/modem/drv
BSP_DIR                  :=$(DRV_DIR)/ccore
OS_SRC_DIR               :=$(BALONG_TOPDIR)/build/delivery/$(OBB_PRODUCT_NAME)/os/$(OBC_LOCAL_CORE_NAME)
ASIC_DIR_NAME            :=$(CFG_BSP_ASIC_DIR_NAME)

CORE_INDEX :=1
# common file src
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/l2cache/head_mini.s \
	$(BSP_DIR)/drivers/l2cache/main_mini.c \
	$(BSP_DIR)/drivers/l2cache/l2cache_screening.c
# include
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/include/drv \
	$(BALONG_TOPDIR)/modem/include/drv/ccore \
	$(BALONG_TOPDIR)/modem/include/drv/common \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/os/ccore

#***********************************************************
#include rules. must be droped at the bottom
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/cc_rtosck_rules.mk

.PHONY: $(maction)
$(maction): do_$(maction)
	@echo ccore $(maction) is ready.
force:
	@echo nothing to be done for [$@]
