# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=ccore
OBC_LOCAL_MOUDLE_NAME	?=lmsp_ccore

OBC_LOCAL_USER_OBJ_FILE =

#***********************************************************#
# compiler flags
#***********************************************************#

#CC_USER_FLAGS   := -std=gnu89 -Wall -fno-builtin -fdollars-in-identifiers -fsigned-char -msoft-float -mlong-calls \
#					-Wmissing-declarations -Wmissing-prototypes \
#					-nostdinc  \					
#					-DPROCESS_TRACE -DVOS_OSA_CPU=0 -DPRODUCT_CFG_CORE_TYPE_MCORE \
#					-DVOS_VXWORKS=3 -DVOS_OS_VER=VOS_VXWORKS -DMSP_GUNAS_AT_UNITE \
#					-DVERSION_V7R1_C010 -DBSP_CORE_MODEM

CC_USER_FLAGS   := -g -std=gnu89 -Wall -fno-builtin -fdollars-in-identifiers -fsigned-char -msoft-float -mlong-calls \
					-Wmissing-declarations -Wmissing-prototypes \
					-DPROCESS_TRACE -DVOS_OSA_CPU=0 -DPRODUCT_CFG_CORE_TYPE_MCORE \
					-DVOS_VXWORKS=3 -DVOS_OS_VER=VOS_VXWORKS -DMSP_GUNAS_AT_UNITE \
					-DVERSION_V7R1_C010 -DBSP_CORE_MODEM	

CC_USER_FLAGS += -march=armv7-a  -finline-functions
					
AS_USER_FLAGS   := 

#***********************************************************#
# Source File to compile
#***********************************************************#
MSP_LT_COMM_DIR			:=$(BALONG_TOPDIR)/modem/oam/lt/comm
MSP_COMM_INC_DIR        :=$(BALONG_TOPDIR)/modem/oam/inc/lt/comm
OAM_COMM_INC_DIR        :=$(BALONG_TOPDIR)/modem/oam/inc/gu/comm
MSP_LT_CCORE_DIR   		:=$(BALONG_TOPDIR)/modem/oam/lt/ccore
MSP_CCORE_INC_DIR       :=$(BALONG_TOPDIR)/modem/oam/inc/lt/ccore
TAF_CCORE_COMM_INC_DIR  :=$(BALONG_TOPDIR)/modem/taf/comm
PRJ_INCLUDE_DIR      	:=$(BALONG_TOPDIR)/modem/include
PRJ_CONFIG_DIR          :=$(BALONG_TOPDIR)/modem/config
PRJ_PLATFORM_DIR        :=$(BALONG_TOPDIR)/modem/platform


OBC_LOCAL_SRC_FILE := 
OBC_LOCAL_SRC_DIR :=$(MSP_LT_CCORE_DIR)/diag \
   $(MSP_LT_CCORE_DIR)/debug \
   $(MSP_LT_COMM_DIR)/list \
   $(MSP_LT_COMM_DIR)/sda \
   $(MSP_LT_COMM_DIR)/scm \
   $(MSP_LT_CCORE_DIR)/bbpds \
   $(MSP_LT_CCORE_DIR)/nvim \
   $(MSP_LT_CCORE_DIR)/nvim/XML \
   $(MSP_LT_CCORE_DIR)/sleep \
   $(MSP_LT_CCORE_DIR)/sdm \
   $(TAF_CCORE_DIR)/sym 

OBC_LOCAL_INC_DIR +=$(PRJ_INCLUDE_DIR)/ps/gups/acore \
   $(PRJ_INCLUDE_DIR)/ps/gups/ccore \
   $(PRJ_INCLUDE_DIR)/ps/gups/common \
   $(PRJ_INCLUDE_DIR)/ps/tlps/acore \
   $(PRJ_INCLUDE_DIR)/ps/tlps/ccore \
   $(PRJ_INCLUDE_DIR)/ps/tlps/common \
   $(PRJ_INCLUDE_DIR)/ps/nas \
   $(PRJ_INCLUDE_DIR)/phy/wphy \
   $(PRJ_INCLUDE_DIR)/phy/lphy \
   $(PRJ_INCLUDE_DIR)/phy/lphy/comm/$(CFG_PRODUCT_HISILICON_VERSION)/$(CFG_PRODUCT_HISILICON_RFIC_VERSION) \
   $(PRJ_INCLUDE_DIR)/drv \
   $(PRJ_INCLUDE_DIR)/drv/ccore \
   $(PRJ_INCLUDE_DIR)/drv/common \
   $(PRJ_INCLUDE_DIR)/nv/gu/nas\
   $(PRJ_INCLUDE_DIR)/nv/gu/oam\
   $(PRJ_INCLUDE_DIR)/nv/gu/gas\
   $(PRJ_INCLUDE_DIR)/nv/gu/was\
   $(PRJ_INCLUDE_DIR)/nv/gu/phy\
   $(PRJ_INCLUDE_DIR)/nv/tl/lps \
   $(PRJ_INCLUDE_DIR)/nv/tl/drv \
   $(PRJ_INCLUDE_DIR)/nv/tl/oam \
   $(PRJ_INCLUDE_DIR)/oam/gu/usimm \
   $(PRJ_INCLUDE_DIR)/oam/gu/osa \
   $(PRJ_INCLUDE_DIR)/oam/comm/om \
   $(PRJ_INCLUDE_DIR)/oam/comm/socp \
   $(PRJ_INCLUDE_DIR)/oam/comm/scm \
   $(PRJ_INCLUDE_DIR)/oam/comm/nvim \
   $(PRJ_INCLUDE_DIR)/oam/comm/cpm \
   $(PRJ_INCLUDE_DIR)/oam/comm/errno \
   $(PRJ_INCLUDE_DIR)/oam/lt/ccore \
   $(PRJ_INCLUDE_DIR)/oam/lt/common \
   $(PRJ_INCLUDE_DIR)/oam/gu/log \
   $(PRJ_INCLUDE_DIR)/oam/gu/om \
   $(PRJ_INCLUDE_DIR)/oam/gu/nvim \
   $(PRJ_INCLUDE_DIR)/taf/acore \
   $(PRJ_INCLUDE_DIR)/taf/ccore \
   $(PRJ_INCLUDE_DIR)/taf/common \
   $(BALONG_TOPDIR)/modem/taf/lt/inc/common \
   $(BALONG_TOPDIR)/modem/oam/inc/comm/comm/nvim \
   $(PRJ_PLATFORM_DIR)/$(CFG_PLATFORM_HISI_BALONG)   \
   $(MSP_COMM_INC_DIR)/cfg \
   $(MSP_COMM_INC_DIR)/diag \
   $(MSP_COMM_INC_DIR)/list \
   $(MSP_COMM_INC_DIR)/nvim \
   $(MSP_COMM_INC_DIR)/type \
   $(OAM_COMM_INC_DIR)/om \
   $(MSP_CCORE_INC_DIR)/bbpds \
   $(MSP_CCORE_INC_DIR)/nvim \
   $(MSP_CCORE_INC_DIR)/diag \
   $(MSP_CCORE_INC_DIR)/sleep \
   $(TAF_CCORE_COMM_INC_DIR)/src/acore/at/inc\
   $(PRJ_CONFIG_DIR)/osa \
   $(PRJ_CONFIG_DIR)/log \
   $(PRJ_CONFIG_DIR)/nvim/include/gu \
   $(PRJ_CONFIG_DIR)/nvim/include/tl/tlps \
   $(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/define \
   $(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/config \
   $(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/include


#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
