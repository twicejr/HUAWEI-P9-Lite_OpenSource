#***********************************************************#
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name
#***********************************************************#
OBC_LOCAL_MOUDLE_NAME	?=tools_config_tlnas

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

PRJ_COMM_DIR    :=$(BALONG_TOPDIR)/modem/include
PS_DIR			:=$(BALONG_TOPDIR)/modem/ps
PS_AS_SRC_DIR   :=$(PS_DIR)/as
PS_NAS_SRC_DIR  :=$(PS_DIR)/nas

OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/config/osa \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
	$(PRJ_COMM_DIR)/phy/lphy \
	$(PRJ_COMM_DIR)/phy/wphy \
	$(PRJ_COMM_DIR)/phy/gphy \
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
	$(PRJ_COMM_DIR)/nv/gu/codec  \
	$(PRJ_COMM_DIR)/nv/gu/nas  \
	$(PRJ_COMM_DIR)/nv/gu/oam  \
	$(PRJ_COMM_DIR)/ps/tlps/acore  \
	$(PRJ_COMM_DIR)/ps/tlps/ccore  \
	$(PRJ_COMM_DIR)/ps/tlps/common \
	$(PRJ_COMM_DIR)/ps/gups/acore  \
	$(PRJ_COMM_DIR)/ps/gups/ccore  \
	$(PRJ_COMM_DIR)/ps/gups/common \
    $(PRJ_COMM_DIR)/taf/acore \
    $(PRJ_COMM_DIR)/taf/ccore \
    $(PRJ_COMM_DIR)/taf/common \
	$(PRJ_COMM_DIR)/med  \
	$(PS_DIR)/comm/comm/ccore/MEM/Inc \
	$(PS_DIR)/comm/comm/common/STL/Inc \
	$(PS_DIR)/comm/comm/ccore/MEMCTRL/Inc \
	$(PS_DIR)/comm/ccore/MEM/Inc \
	$(PS_DIR)/comm/tl/lte/inc/Comm \
	$(PS_DIR)/comm/tl/lte/inc/Hso \
	$(PS_DIR)/comm/tl/lte/inc/Interface \
	$(PS_DIR)/inc/gu \
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
	$(PS_AS_SRC_DIR)/tl/tds/comm/hl1/include \
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
	$(PS_AS_SRC_DIR)/tl/tds/comm/hl1/include  \
	$(PS_AS_SRC_DIR)/tl/tds/comm/hl1/source  \
	$(PS_AS_SRC_DIR)/tl/tds/rrc/acc/include \
	$(PS_AS_SRC_DIR)/tl/tds/rrc/com/include \
	$(PS_AS_SRC_DIR)/tl/tds/rrc/acc/source \
	$(PS_AS_SRC_DIR)/tl/tds/rrc/asn/source \
	$(PS_AS_SRC_DIR)/tl/tds/rrc/asn/include \
	$(PS_AS_SRC_DIR)/tl/tds/rrc/rrc/include \
	$(PS_AS_SRC_DIR)/tl/tds/rrc/rrc/source \
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
	$(PS_AS_SRC_DIR)/tl/tds/l2/com/source \
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
	$(PS_NAS_SRC_DIR)/tl/lte/IMSA/Inc \
	$(PS_NAS_SRC_DIR)/tl/lte/LPP/INC \
	$(PS_NAS_SRC_DIR)/tl/lte/IP/Src/IPM/Inc \
	$(PS_NAS_SRC_DIR)/tl/lte/MMC/INC \
	$(PS_NAS_SRC_DIR)/tl/lte/PUBM/INC \
	$(PS_NAS_SRC_DIR)/tl/lte/RABM/Inc \
	$(PS_NAS_SRC_DIR)/tl/lte/TC/Inc \
	$(PS_NAS_SRC_DIR)/tl/lte/USIM/Inc \
	$(PS_NAS_SRC_DIR)/gu/src/Mmc/Inc \
	$(PS_NAS_SRC_DIR)/comm/mml/INC

#***********************************************************#
# source files
#***********************************************************#
#注：在这里添加需要编译的源文件
OBC_LOCAL_SRC_FILE := $(BALONG_TOPDIR)/modem/ps/nas/tl/hids_elf_tlnas.c
 
#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
#注：在此添加需要引用的编译脚本
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
