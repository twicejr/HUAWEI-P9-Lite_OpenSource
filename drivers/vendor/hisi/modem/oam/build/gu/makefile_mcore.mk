# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore

ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_MOUDLE_NAME	?=gumsp_mcore
endif

ifeq ($(INSTANCE_ID) ,INSTANCE_1)
OBC_LOCAL_MOUDLE_NAME	?=gumsp1_mcore
endif

ifeq ($(INSTANCE_ID) ,INSTANCE_2)
OBC_LOCAL_MOUDLE_NAME	?=gumsp2_mcore
endif

#***********************************************************#
# 从原始makefile中
#***********************************************************#
# ================ link为o文件选项 ================
ARFLAG=-r -o

# ================ make命令选项 ================
MK_OPTION=--jobs=32 -f 

# ================ COMM的镜像文件名 ================
GU_MSP_IMAGE_FILE=gumsp_modem

# ================ 产品形态 (移到build/Script  调用脚本中定义)================
# PRODUCT=GUL_ASIC 

# ================ 平台名称 ================

# ================ CPU名称 ================
VOS_CFG=CCPU_VOS_CFG

# ================ FILE_ID路径名称 ================
FILE_ID=FILE_ID

# ================ NV_ID路径名称 ================
NV_ID=NV_ID

# ================ VERSION名称 ================
PRODUCT_VER=V7R1

#***********************************************************#
# compiler flags
#***********************************************************#
PLAT_FORM_FALG=-DBOARD_$(CFG_BOARD)
CHIP_BB_TYPE_FALG=-DCHIP_BB_$(CFG_CHIP_BB)
PRODUCT=$(OBB_PRODUCT_NAME)

CC_USER_FLAGS   := ${PLAT_FORM_FALG} ${CHIP_BB_TYPE_FALG} -DUSP_2_0 -DWTTF_CIPHER_PIPELINE -D__LOG_RELEASE__  \
					-DVOS_HARDWARE_PLATFORM=8 -DVOS_CPU_TYPE=8 -DVOS_DISPATCHING_MODE=0  -DV2R1_USIM -DUSB_MODEM -DOM_V2R1  \
					-DVOS_OSA_CPU=OSA_CPU_CCPU -DBALONG_PHY_V200=2 -DBALONG_PHY_V300=3 -DBALONG_PHY_VER=BALONG_PHY_V300 \
					-DBALONG_CHIP_V200=2 -DBALONG_CHIP_V300=3 -DBALONG_CHIP_V500=4 -DBALONG_CHIP_VER=BALONG_CHIP_V500 -DDSP_A17_ENABLE \
					-D__HISI_RF__ -DVERSION_V3R2_C00 -DVERSION_V3R2  -DBSP_CORE_MODEM -D__LDF_FUNCTION__ -DFEATURE_DSP2ARM -DBSP_CORE_MODEM \
					-DWTTF_CIPHER_PIPELINE -DVOS_DISPATCHING_MODE=0 -DUSB_MODEM -DOM_V2R1 -DBALONG_PHY_V200=2 -DBALONG_PHY_V300=3 -DBALONG_PHY_VER=BALONG_PHY_V300 \
					-DFEATURE_DSP2ARM

CC_USER_FLAGS += -g -mlong-calls -fsigned-char  -fno-strict-aliasing					





AR_USER_FLAGS   :=-r -o

ifneq ($(INSTANCE_ID) ,)
CC_USER_FLAGS	+=-D$(strip $(INSTANCE_ID) )
endif


CC_USER_FLAGS += -march=armv7-a  -finline-functions


#***********************************************************#
# Source File to compile
#***********************************************************#
GUMSP_DIR :=$(BALONG_TOPDIR)/modem/oam
BALONG_SRC_PATH :=$(BALONG_TOPDIR)
PRODUCT_CFG_PLATFORM_NEW=$(CFG_PLATFORM_HISI_BALONG)
PRODUCT_CFG_PRODUCT_FORM=$(OBB_PRODUCT_NAME)

include $(GUMSP_DIR)/build/comm/MODEM_CORE/msp_code_comm_modem_core.inc
OBC_LOCAL_INC_DIR :=$(vob_include_dirs)

include $(GUMSP_DIR)/build/gu/MODEM_CORE/msp_code_gu_modem_core.inc
OBC_LOCAL_INC_DIR +=$(vob_include_dirs)

include $(GUMSP_DIR)/build/comm/MODEM_CORE/msp_code_comm_modem_core.mk
OBC_LOCAL_SRC_FILE :=$(vob_src_files)
CC_USER_FLAGS += $(USER_CCFLAGS)
AS_USER_FLAGS += $(USER_ASFLAGS)

include $(GUMSP_DIR)/build/gu/MODEM_CORE/msp_code_gu_modem_core.mk
OBC_LOCAL_SRC_FILE +=$(vob_src_files)
CC_USER_FLAGS += $(USER_CCFLAGS)
AS_USER_FLAGS += $(USER_ASFLAGS)

OBC_CC_OPTION   :=$(CC_USER_FLAGS)

OBC_LOCAL_USER_OBJ_FILE := $(GUMSP_DIR)/build/comm/MODEM_CORE/Lib/Omdsate680_MD5_eabi5.o 

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
