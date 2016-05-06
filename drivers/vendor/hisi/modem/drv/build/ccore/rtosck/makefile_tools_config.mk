# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=ccore
OBC_LOCAL_MOUDLE_NAME	?= tools_config_drv

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

CC_USER_FLAGS += -march=armv7-a

ifeq ($(strip $(llt_gcov)),y)
CC_USER_FLAGS += -fprofile-arcs -ftest-coverage
CC_USER_FLAGS += -DDRV_BUILD_GCOV
endif

#***********************************************************#
# Source File to compile
#***********************************************************#
OBC_LOCAL_SRC_FILE += \
    $(BALONG_TOPDIR)/modem/drv/ccore/drivers/tools_elf/hids_elf_drvccore.c

#*******************************************************************
# Include Head Files
#*******************************************************************
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/include/drv \
	$(BALONG_TOPDIR)/modem/include/drv/ccore \
	$(BALONG_TOPDIR)/modem/include/drv/common \
	$(BALONG_TOPDIR)/modem/include/ps/gups \
	$(BALONG_TOPDIR)/modem/include/nv/tl/drv \
	$(BALONG_TOPDIR)/modem/include/nv/gu/drv \
	$(BALONG_TOPDIR)/modem/include/nv/comm \
	$(BALONG_TOPDIR)/modem/include/nv/tl/oam \
	$(BALONG_TOPDIR)/modem/include/phy/lphy \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/os/ccore \
	$(BALONG_TOPDIR)/modem/config/product/nvim/include/gu \
	$(BALONG_TOPDIR)/modem/drv/ccore/sys \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/dynamic_load \
	$(BALONG_TOPDIR)/modem/drv/ccore/modem/include \
	$(BALONG_TOPDIR)/modem/include/nv/tl/drv \
	$(BALONG_TOPDIR)/modem/include/nv/tl/oam \
	$(BALONG_TOPDIR)/modem/include/nv/tl/lps \
    $(BALONG_TOPDIR)/modem/include/nv/tl/phy \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/gic \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/serial \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/systimer \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/ipc \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/icc \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu/hi6551 \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu/hi6552 \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu/hi6559 \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu/hi6561 \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/regulator \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/clk \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/nvim \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/dump \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/log \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/common \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/aximonitor \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/dpm \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/socp \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/i2c \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/wakelock\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/rfile\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/sec\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/udi\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/tcxo\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/bbp\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/gpio\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/ios\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/mem\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/balong_timer\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/mipi \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/rffe \
    $(BALONG_TOPDIR)/modem/drv/ccore/drivers/memrepair \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pmu_new \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/rtc \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/ipf \
    $(BALONG_TOPDIR)/modem/drv/ccore/drivers/busstress/gu \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/board \
	$(BALONG_TOPDIR)/modem/drv/common/include \
    $(BALONG_TOPDIR)/modem/drv/ccore/include \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/om/ddm \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/anten \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/efuse \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/gpio \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/rse \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/ios \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/pintrl \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/cipher \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/temperature \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/cpuidle \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/sys_bus\
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/sys_bus/gu/uft_comm \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/sys_bus/gu/uft_hdlc \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/sys_bus/gu/uft_cicom \
	$(BALONG_TOPDIR)/modem/drv/ccore/drivers/sys_bus/gu/uft_upacc



#***********************************************************
#include rules. must be droped at the bottom
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/cc_rtosck_rules.mk
