#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore
OBC_LOCAL_MOUDLE_NAME	?=cpscomm_ccore

#***********************************************************#
#thumb compile switch:必须放在COMM FLAGS之前
#***********************************************************#

#***********************************************************#
# compiler flags
#***********************************************************#
#COMM FLAGS
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm_flags.mk

#USER FLAGS AND DEFINES
CC_USER_FLAGS   ?= 
AS_USER_FLAGS   ?=

ifeq ($(CFG_THUMB_COMPILE),YES)



CC_USER_FLAGS += -mthumb -mthumb-interwork -mlong-calls

endif 


CC_USER_FLAGS += -march=armv7-a


#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=
CC_USER_DEFINES +=-DWAS_BBIT_SWITCH
				
CC_USER_FLAGS := -g
#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/cdma/modem/ps_comm.inc

#cas include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK\Inc \
        $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LOGFILTER\Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK\Inc \

OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/include/oam/gu/usimm \
    $(BALONG_TOPDIR)/modem/include/oam/comm/nvim \
    $(BALONG_TOPDIR)/modem/config/nvim/include/gu

ifeq ($(CFG_FEATURE_UE_MODE_CDMA),FEATURE_ON)
OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/config/osa \
    $(BALONG_TOPDIR)/modem/include/drv \
    $(BALONG_TOPDIR)/modem/include/drv/common \
    $(BALONG_TOPDIR)/modem/include/drv/ccore \
    $(BALONG_TOPDIR)/modem/include/med \
    $(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
    $(BALONG_TOPDIR)/modem/include/nv/gu/nas \
    $(BALONG_TOPDIR)/modem/include/nv/gu/codec \
    $(BALONG_TOPDIR)/modem/include/nv/gu/oam \
    $(BALONG_TOPDIR)/modem/include/oam/comm/om \
    $(BALONG_TOPDIR)/modem/include/oam/gu/osa \
    $(BALONG_TOPDIR)/modem/include/oam/lt/common \
    $(BALONG_TOPDIR)/modem/include/oam/gu/si \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc \
    $(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
    $(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
    $(BALONG_TOPDIR)/modem/include/taf/acore \
    $(BALONG_TOPDIR)/modem/include/taf/ccore \
    $(BALONG_TOPDIR)/modem/include/taf/common \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/IP/Inc \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma/1x \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma/hrpd \
    $(BALONG_TOPDIR)/modem/ps/inc/gu

OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/vsncp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/stac \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pap \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/mppc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/lcp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ipv6cp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ipcp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/common \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/chap \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ccp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/adapter/spud \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/adapter/spuf \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/util \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/eap

ifeq ($(CFG_FEATURE_HARDWARE_HDLC_ON_CCPU),FEATURE_ON)
OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/PPP \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/PPP/Inc
endif


OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP/dhcpm \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP/dhcpv4c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP/dhcpv4c/include \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP/dhcpv4s \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP/dhcpv6s \

OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/inc
    
endif

#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE :=

ifeq ($(CFG_FEATURE_UE_MODE_CDMA),FEATURE_ON)
OBC_LOCAL_SRC_FILE += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pppc_init.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pppc_pa_agent.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pppc_uim.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_var.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_shel.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_perf.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_fsm.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_dbug.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_dbgcmd.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_cvt.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ppp_core.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/fwd_ppp.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pppc_ctrl.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/sm_simulator_mbuf.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/balong_stub.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/vsncp/vsncp.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/vsncp/vsncp_decode.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/vsncp/vsncp_encode.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/stac/stac.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pap/pap.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pap/pap_dbg.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/mppc/mppc.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/mppc/mppchash.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/lcp/lcp.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ipv6cp/ipv6cp.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ipcp/ipcp.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/chap/chap.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/chap/chap_dbg.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ccp/ccp.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/util/pppc_sha1.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/util/pppc_sha256.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/util/pppc_aes.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/util/pppc_md5.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/eap/pppc_eap_aka.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/eap/pppc_eap.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/eap/pppc_eap_mgr.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/eap/pppc_eap_peer.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/adapter/spud/ppp_task.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/adapter/spuf/ppp_comp.c

ifeq ($(CFG_FEATURE_CHINA_TELECOM_VOICE_ENCRYPT),FEATURE_ON)
OBC_LOCAL_SRC_FILE += \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/eil.c
endif
	
ifeq ($(CFG_FEATURE_HARDWARE_HDLC_ON_CCPU),FEATURE_ON)
OBC_LOCAL_SRC_FILE += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/PPP/Src/hdlc_hardware.c

#***********************************************************
# used for hdlc ST test
#***********************************************************
#OBC_LOCAL_SRC_FILE += $(BALONG_TOPDIR)/llt/cttf/dmt/testcase/PPP/PppcHdlcStTest.c

endif

OBC_LOCAL_SRC_FILE += \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP/DhcpLog.c \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/DHCP/dhcp_adapter.c

endif

#***********************************************************#
# OBJ files
#***********************************************************#
OBC_LOCAL_USER_OBJ_FILE :=

ifeq ($(CFG_FEATURE_UE_MODE_CDMA),FEATURE_ON)

ifeq ($(CFG_FEATURE_CHINA_TELECOM_VOICE_ENCRYPT),FEATURE_ON)

OBC_LOCAL_USER_OBJ_FILE += \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/cryptblock.o \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/EllipticCurve.o \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/Mpi.o \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/Noise.o \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/sm3hash.o \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/SMAlgorithm.o \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/table.o \
    $(BALONG_TOPDIR)/modem/ps/comm/cdma/ecc/src/TrueRandom.o
endif

endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
