#***********************************************************#
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name
#***********************************************************#
OBC_LOCAL_MOUDLE_NAME	?=tools_config_gas

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
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/phy/gphy \
	$(BALONG_TOPDIR)/modem/include/visp \
	$(BALONG_TOPDIR)/modem/include/visp/tcpip \
	$(BALONG_TOPDIR)/modem/include/visp/security \
	$(BALONG_TOPDIR)/modem/ps/as/comm/tools/inc \
	$(BALONG_TOPDIR)/modem/ps/as/gu/inc/Gtf\
	$(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEMCTRL/Inc\
	$(BALONG_TOPDIR)/modem/ps/inc/gu \
	$(BALONG_TOPDIR)/modem/ps/inc/gu/comm/comm/ccore/memctrl/inc\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc\
	$(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/oam/gu/osa \
	$(BALONG_TOPDIR)/modem/include/oam/comm/om \
	$(BALONG_TOPDIR)/modem/config/osa\
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf\
	$(BALONG_TOPDIR)/modem/config/log \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/config/osa \
	$(BALONG_TOPDIR)/modem/include/drv \
	$(BALONG_TOPDIR)/modem/include/drv/common \
	$(BALONG_TOPDIR)/modem/include/drv/ccore \
	$(BALONG_TOPDIR)/modem/include/oam/comm/om \
	$(BALONG_TOPDIR)/modem/include/oam/gu/osa \
	$(BALONG_TOPDIR)/modem/include/oam/comm/scm \
	$(BALONG_TOPDIR)/modem/include/oam/gu/si \
	$(BALONG_TOPDIR)/modem/include/oam/comm/socp \
	$(BALONG_TOPDIR)/modem/include/oam/gu/usimm \
	$(BALONG_TOPDIR)/modem/include/oam/comm/errno \
	$(BALONG_TOPDIR)/modem/include/oam/comm/dms \
	$(BALONG_TOPDIR)/modem/include/oam/comm/nvim \
	$(BALONG_TOPDIR)/modem/include/oam/gu/log \
	$(BALONG_TOPDIR)/modem/include/oam/gu/om \
	$(BALONG_TOPDIR)/modem/include/oam/gu/nvim \
	$(BALONG_TOPDIR)/modem/include/oam/gu/hpa \
	$(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/oam/lt/ccore \
	$(BALONG_TOPDIR)/modem/include/phy/gphy \
	$(BALONG_TOPDIR)/modem/include/phy/wphy \
	$(BALONG_TOPDIR)/modem/include/phy/rcm \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/gas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/was \
	$(BALONG_TOPDIR)/modem/include/nv/gu/phy \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/tl/lps \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/taf/acore \
	$(BALONG_TOPDIR)/modem/include/taf/ccore \
	$(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/tools \
	$(BALONG_TOPDIR)/modem/include/med

OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/inc/gu \
    $(BALONG_TOPDIR)/modem/ps/inc/lt \
    $(BALONG_TOPDIR)/modem/ps/comm/inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LOGFILTER/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/DICC/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/FLOWCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/FLOWCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEMCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/STL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CDS/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/Pstool/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/NFEXT \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/acore/NFEXT \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/IMSNIC/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/acore \
    $(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/comm/RRM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Pscfg \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Comm \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Gtf \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Wtf \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Gas \
    $(BALONG_TOPDIR)/modem/ps/as/gu/inc/Was \
    $(BALONG_TOPDIR)/modem/ps/as/gu/comm/ASN1/Codec \
    $(BALONG_TOPDIR)/modem/ps/as/gu/comm/Cipher/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/comm/Frmwk/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/comm/Pscfg/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/COMMON/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/DATA/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GASM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/GCOMC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/GCOMM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCOM/GCOMSI/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GRR/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/RR/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/GCBS/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/gas/ASN1/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RRC \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SMC \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RB \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CBS \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSELPC \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CSEL \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/CU \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/RM \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/SYSHO \
    $(BALONG_TOPDIR)/modem/ps/as/gu/was/PUBLIC \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/CF/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/IP/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/MUX/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/CST/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/TTFComm/CICOM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/DL/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/GMAC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/GRLC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/GRM/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/LL/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Gtf/SN/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/PDCP/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/SERVICE/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/MAC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/RLC/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/gu/ttf/Wtf/BMC/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/comm/mml/INC \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/lib \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmcomm/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Tc/Inc \
    $(BALONG_TOPDIR)/modem/taf/inc/acore \
    $(BALONG_TOPDIR)/modem/taf/inc/ccore \
    $(BALONG_TOPDIR)/modem/taf/inc/common \
    $(BALONG_TOPDIR)/modem/taf/comm/inc \
    $(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/Lib \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Fsm/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Log \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Call/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Data/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Msg/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Phone/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Sups/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Task/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/VC/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafDrvAgent/Inc\
    $(BALONG_TOPDIR)/modem/ps/as/comm/tools/inc


ifeq ($(CFG_RAT_MODE),RAT_GU)
OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r6/Inc
endif

ifeq ($(CFG_RAT_MODE),RAT_GUL)
OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Inc
endif
#***********************************************************#
# source files
#***********************************************************#
#注：在这里添加需要编译的源文件
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/ps/as/gu/gas/hids_elf_gas.c

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
#注：在此添加需要引用的编译脚本
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
