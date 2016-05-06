#***********************************************************#
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name
#***********************************************************#
OBC_LOCAL_MOUDLE_NAME	?=tools_config_lmsp

#***********************************************************#
# compiler flags
#***********************************************************#
CC_USER_FLAGS   ?= 
AS_USER_FLAGS   ?=

#***********************************************************#
# compiler defines
#***********************************************************#
CC_USER_DEFINES ?=
AS_USER_DEFINES ?=

#***********************************************************#
# include Directories
#***********************************************************#
#注：在这里添加编译的头文件
PRJ_COMM_DIR      :=$(BALONG_TOPDIR)/modem/include
MSP_COMM_INC_DIR  :=$(BALONG_TOPDIR)/modem/oam/inc/lt/comm
MSP_CCORE_INC_DIR :=$(BALONG_TOPDIR)/modem/oam/inc/lt/ccore
PRJ_CONFIG_DIR    :=$(BALONG_TOPDIR)/modem/config
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += $(vob_include_dirs)
OBC_LOCAL_INC_DIR += \
    $(PRJ_COMM_DIR)/drv \
    $(PRJ_COMM_DIR)/drv/ccore \
    $(PRJ_COMM_DIR)/drv/common \
    $(PRJ_COMM_DIR)/phy/lphy \
    $(PRJ_COMM_DIR)/nv/gu/nas\
    $(PRJ_COMM_DIR)/nv/gu/oam\
    $(PRJ_COMM_DIR)/nv/gu/gas\
    $(PRJ_COMM_DIR)/nv/gu/was\
    $(PRJ_COMM_DIR)/nv/gu/phy\
    $(PRJ_COMM_DIR)/nv/tl/lps \
    $(PRJ_COMM_DIR)/nv/tl/drv \
    $(PRJ_COMM_DIR)/nv/tl/oam \
    $(PRJ_COMM_DIR)/oam/gu/usimm \
    $(PRJ_COMM_DIR)/oam/gu/osa \
    $(PRJ_COMM_DIR)/oam/comm/socp \
    $(PRJ_COMM_DIR)/oam/comm/scm \
    $(PRJ_COMM_DIR)/oam/comm/nvim \
    $(PRJ_COMM_DIR)/oam/comm/cpm \
    $(PRJ_COMM_DIR)/oam/comm/errno \
    $(PRJ_COMM_DIR)/oam/comm/om \
    $(PRJ_COMM_DIR)/oam/lt/ccore \
    $(PRJ_COMM_DIR)/oam/lt/common \
    $(PRJ_COMM_DIR)/oam/gu/log \
    $(PRJ_COMM_DIR)/oam/gu/om \
    $(PRJ_COMM_DIR)/oam/gu/nvim \
    $(PRJ_COMM_DIR)/ps/tlps/ccore \
    $(PRJ_COMM_DIR)/ps/tlps/common \
    $(MSP_COMM_INC_DIR)/cfg \
    $(MSP_COMM_INC_DIR)/diag \
    $(MSP_COMM_INC_DIR)/list \
    $(MSP_COMM_INC_DIR)/nvim \
    $(MSP_COMM_INC_DIR)/type \
    $(MSP_COMM_INC_DIR)/drx \
    $(MSP_CCORE_INC_DIR)/bbpds \
    $(MSP_CCORE_INC_DIR)/nvim \
    $(MSP_CCORE_INC_DIR)/diag \
    $(MSP_CCORE_INC_DIR)/sleep \
    $(MSP_CCORE_INC_DIR)/ftm \
    $(PRJ_CONFIG_DIR)/osa \
    $(PRJ_CONFIG_DIR)/log \
    $(PRJ_CONFIG_DIR)/nvim/include/gu \
    $(PRJ_CONFIG_DIR)/nvim/include/tl/tlps \
    $(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/define \
    $(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/config \
    $(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/include

#***********************************************************#
# source files
#***********************************************************#
#注：在这里添加需要编译的源文件
OBC_LOCAL_SRC_FILE := \
    $(BALONG_TOPDIR)/modem/oam/lt/comm/tools_elf/hids_elf_tlmsp.c

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
#注：在此添加需要引用的编译脚本
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
