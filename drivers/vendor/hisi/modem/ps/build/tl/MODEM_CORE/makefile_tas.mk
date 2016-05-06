# Created by Jeffery.zhai/199916 2012.03.21

#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore
OBC_LOCAL_MOUDLE_NAME	?=tas_ccore

#***********************************************************#
# compiler flags
#***********************************************************#
CC_USER_FLAGS   := -nostdinc  -mlong-calls
CC_USER_DEFINES := -DM1_PORTING -DPEEK_DEBUG  -DUSE_ENODEB_2 -DPROCESS_TRACE -DVOS_OSA_CPU=0 -DBSP_CORE_MODEM
ifeq ($(strip $(CFG_FEATURE_UE_MODE_TDS)),FEATURE_ON)
CC_USER_FLAGS   := -std=gnu89 -Wall -fno-strict-aliasing -fno-builtin -fdollars-in-identifiers -fsigned-char -msoft-float -mlong-calls  
CC_USER_DEFINES := -DMEMO_BLOCK -DYNMIC_LOAD_DSP -DTDSCDMA_ONLY -DRRC_ASN_EXTEND -DBSP_CORE_MODEM
endif #end of CFG_FEATURE_UE_MODE_TDS
ifeq ($(CFG_THUMB_COMPILE),YES)
CC_USER_FLAGS   += -mthumb -mthumb-interwork -mlong-calls
ifeq ($(OBB_MODEM_OS_TYPE),VXWORKS)
CC_USER_FLAGS   += -march=armv6
else
ifeq ($(OBB_MODEM_OS_TYPE), RTOSCK)
CC_USER_FLAGS += -march=armv7-a  
endif
endif #end of OBB_MODEM_OS_TYPE
endif #end of CFG_THUMB_COMPILE

AS_USER_FLAGS   := 

#***********************************************************#
# Source File to compile
#***********************************************************#
PRJ_CONFIG_DIR  :=$(BALONG_TOPDIR)/modem/config
PRJ_COMM_DIR    :=$(BALONG_TOPDIR)/modem/include
PS_DIR			:=$(BALONG_TOPDIR)/modem/ps
PS_COMM_DIR  	:=$(PS_DIR)/comm
PS_INC_DIR    	:=$(PS_DIR)/inc
PS_AS_SRC_DIR   :=$(PS_DIR)/as
PS_NAS_SRC_DIR  :=$(PS_DIR)/nas

PS_TDS_L2_SRC   := $(PS_AS_SRC_DIR)/tl/tds/l2/Mac/Src \
                   $(PS_AS_SRC_DIR)/tl/tds/l2/pdc/source \
                   $(PS_AS_SRC_DIR)/tl/tds/l2/rlc/source \
                   $(PS_AS_SRC_DIR)/tl/tds/l2/hl1/source
				   
PS_TDS_RRC_SRC  := $(PS_AS_SRC_DIR)/tl/tds/rrc/acc/source \
                   $(PS_AS_SRC_DIR)/tl/tds/rrc/asn/source \
				   $(PS_AS_SRC_DIR)/tl/tds/rrc/bmc/source \
				   $(PS_AS_SRC_DIR)/tl/tds/rrc/dum/source \
				   $(PS_AS_SRC_DIR)/tl/tds/rrc/idl/source \
				   $(PS_AS_SRC_DIR)/tl/tds/rrc/rrc/source
			   
PS_TDS_SRC :=      $(PS_TDS_L2_SRC) \
                   $(PS_TDS_RRC_SRC)

OBC_LOCAL_SRC_FILE :=

ifeq ($(strip $(CFG_FEATURE_UE_MODE_TDS)),FEATURE_ON)
OBC_LOCAL_SRC_DIR += $(PS_TDS_SRC)
endif #end of CFG_FEATURE_UE_MODE_TDS

OBC_LOCAL_INC_DIR :=\
        $(PRJ_COMM_DIR)/drv \
        $(PRJ_COMM_DIR)/drv/ccore \
        $(PRJ_COMM_DIR)/drv/common \
        $(PRJ_COMM_DIR)/oam/comm \
		$(PRJ_COMM_DIR)/oam/lt/ccore \
		$(PRJ_COMM_DIR)/oam/lt/common \
		$(PRJ_COMM_DIR)/oam/gu/om \
		$(PRJ_COMM_DIR)/oam/gu/log \
		$(PRJ_COMM_DIR)/oam/gu/nvim\
        $(PRJ_COMM_DIR)/oam/comm/om \
		$(PRJ_COMM_DIR)/oam/comm/nvim \
		$(PRJ_COMM_DIR)/oam/gu/usimm \
		$(PRJ_COMM_DIR)/oam/comm/errno \
		$(PRJ_COMM_DIR)/oam/gu/osa\
		$(PRJ_COMM_DIR)/oam/gu/si\
		$(PRJ_COMM_DIR)/nv/tl/lps \
		$(PRJ_COMM_DIR)/nv/tl/phy \
		$(PRJ_COMM_DIR)/nv/tl/phy/$(CFG_PRODUCT_HISILICON_VERSION)/$(CFG_PRODUCT_HISILICON_RFIC_VERSION) \
		$(PRJ_COMM_DIR)/nv/gu/gas \
		$(PRJ_COMM_DIR)/nv/gu/ttf \
		$(PRJ_COMM_DIR)/nv/gu/was \
		$(PRJ_COMM_DIR)/nv/gu/nas \
		$(PRJ_COMM_DIR)/nv/gu/phy \
		$(PRJ_COMM_DIR)/phy/lphy \
		$(PRJ_COMM_DIR)/phy/tphy \
		$(PRJ_COMM_DIR)/phy/lphy/om/$(CFG_PRODUCT_HISILICON_VERSION)/$(CFG_PRODUCT_HISILICON_RFIC_VERSION) \
		$(PRJ_COMM_DIR)/phy/tphy/om/$(CFG_PRODUCT_HISILICON_VERSION)/$(CFG_PRODUCT_HISILICON_RFIC_VERSION) \
        $(PRJ_COMM_DIR)/ps/gups/acore  \
		$(PRJ_COMM_DIR)/ps/gups/ccore  \
		$(PRJ_COMM_DIR)/ps/gups/common \
		$(PRJ_COMM_DIR)/ps/tlps/acore \
		$(PRJ_COMM_DIR)/ps/tlps/ccore \
		$(PRJ_COMM_DIR)/ps/tlps/common \
		$(PRJ_COMM_DIR)/phy/wphy \
		$(PRJ_COMM_DIR)/med \
		$(PRJ_COMM_DIR)/ps/nas \
        $(PRJ_COMM_DIR)/taf/acore \
        $(PRJ_COMM_DIR)/taf/ccore \
        $(PRJ_COMM_DIR)/taf/common \
		$(PRJ_COMM_DIR)/nv/gu/codec \
		$(PRJ_COMM_DIR)/nv/gu/oam \
		$(PRJ_COMM_DIR)/tools \
	    	$(PS_COMM_DIR)/comm/ccore/CDS/Inc \
		$(PS_COMM_DIR)/comm/ccore/ND/NDCLIENT/Inc \
		$(PS_COMM_DIR)/comm/common/ND/IPCOMM/Inc \
		$(PS_COMM_DIR)/comm/common/LINK/Inc \
		$(PS_COMM_DIR)/comm/ccore/LINK/Inc \
        	$(PS_COMM_DIR)/comm/common/STL/Inc \
                $(PS_COMM_DIR)/comm/common/LOGFILTER/Inc \
		$(PS_COMM_DIR)/comm/ccore/MEM/Inc \
		$(PS_COMM_DIR)/tl/lte/inc/Comm \
		$(PS_COMM_DIR)/tl/lte/inc/Hso \
		$(PS_COMM_DIR)/tl/lte/inc/Interface \
		$(PRJ_CONFIG_DIR)/osa \
		$(PRJ_CONFIG_DIR)/log \
		$(PRJ_CONFIG_DIR)/nvim/include/tl/LPHY \
		$(PRJ_CONFIG_DIR)/nvim/include/tl/tlps \
		$(PRJ_CONFIG_DIR)/nvim/include/tl/MSP \
		$(PRJ_CONFIG_DIR)/nvim/include/gu \
		$(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/include \
		$(PRJ_CONFIG_DIR)/product/$(OBB_PRODUCT_NAME)/config \
		$(PS_INC_DIR)/gu \
		$(PS_INC_DIR)/tl \
		$(PS_INC_DIR)/cdma \
		$(PS_AS_SRC_DIR)/tl/lte/comm/HPA/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/comm/PSOM/Inc \
        $(PS_AS_SRC_DIR)/tl/lte/rrc/Rrc/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Csel/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Cmm/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Inc \
        $(PS_AS_SRC_DIR)/tl/lte/rrc/Main/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Smc/Inc \
        $(PS_AS_SRC_DIR)/tl/lte/rrc/Sib/Inc \
        $(PS_AS_SRC_DIR)/tl/lte/rrc/Reest/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Cselpc/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Cselbg/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Rb/Inc \
	    $(PS_AS_SRC_DIR)/tl/lte/rrc/Itf/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/rrc/Asn1/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/l2/mac/Inc \
        $(PS_AS_SRC_DIR)/tl/lte/l2/rlc/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/l2/rohc/inc \
		$(PS_AS_SRC_DIR)/tl/lte/l2/com/Inc \
		$(PS_AS_SRC_DIR)/tl/lte/l2/pdcp/Inc \
	    $(PS_AS_SRC_DIR)/tl/lte/l2/inc \
	    $(PS_NAS_SRC_DIR)/inc \
	    $(PS_NAS_SRC_DIR)/tl/lte/Inc \
	    $(PS_NAS_SRC_DIR)/tl/lte/COMM/INC \
        $(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/ATTACH/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/TAU/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/SECU/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/PUBU/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/GUTI/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/MRRC/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/PLMN/INC \
        $(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/IDEN/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/DETACH/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/EMM/SRC/SERVICE/INC \
        $(PS_NAS_SRC_DIR)/tl/lte/ESM/Inc \
		$(PS_NAS_SRC_DIR)/tl/lte/IP/Inc \
		$(PS_NAS_SRC_DIR)/tl/lte/IP/Src/IPM/Inc \
		$(PS_NAS_SRC_DIR)/tl/lte/MMC/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/PUBM/INC \
		$(PS_NAS_SRC_DIR)/tl/lte/RABM/Inc \
		$(PS_NAS_SRC_DIR)/tl/lte/TC/Inc \
		$(PS_NAS_SRC_DIR)/tl/lte/USIM/Inc \
		$(PS_NAS_SRC_DIR)/gu/src/Mmc/Inc \
		$(PS_NAS_SRC_DIR)/comm/mml/INC  \
		$(PS_AS_SRC_DIR)/tl/tds/l2/hl1/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/rtos_ps/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl_pa_pf/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl_ps/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl_ps/source \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl_ps_pa/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl_ps_pf/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl_ps_pf/source \
		$(PS_AS_SRC_DIR)/tl/tds/comm/rtos_ps/include \
		$(PS_AS_SRC_DIR)/tl/tds/comm/rtos_ps/source \
		$(PS_AS_SRC_DIR)/tl/tds/comm/tgl/source \
		$(PS_AS_SRC_DIR)/tl/tds/l2/hl1/source  \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/acc/include \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/acc/source \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/asn/source \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/asn/include \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/rrc/include \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/rrc/source \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/com/include \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/idl/include \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/idl/source \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/dum/source \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/dum/include \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/bmc/source \
		$(PS_AS_SRC_DIR)/tl/tds/rrc/bmc/include \
		$(PS_AS_SRC_DIR)/tl/tds/l2/pdc/include \
		$(PS_AS_SRC_DIR)/tl/tds/l2/pdc/source \
		$(PS_AS_SRC_DIR)/tl/tds/l2/Mac/Inc \
		$(PS_AS_SRC_DIR)/tl/tds/l2/Mac/Src \
		$(PS_AS_SRC_DIR)/tl/tds/l2/rlc/include \
		$(PS_AS_SRC_DIR)/tl/tds/l2/rlc/source \
		$(PS_AS_SRC_DIR)/tl/tds/l2/com/include \
		$(PS_AS_SRC_DIR)/tl/tds/Stub/Pcstub \
		$(PS_AS_SRC_DIR)/tl/tds/l2/com/source 
#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
ifeq ($(OBB_MODEM_OS_TYPE), VXWORKS)
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_vxworks6.8_rules.mk
else
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
endif
