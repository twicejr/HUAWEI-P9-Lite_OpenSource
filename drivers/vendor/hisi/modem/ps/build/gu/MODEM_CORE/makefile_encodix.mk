#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore

OBC_LOCAL_MOUDLE_NAME	?=encodix_ccore

#***********************************************************#
# compiler flags
#***********************************************************#
#COMM FLAGS
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_flags.mk

#USER FLAGS
CC_USER_FLAGS   ?=
AS_USER_FLAGS   ?=



ifeq ($(CFG_THUMB_COMPILE),YES)
CC_USER_FLAGS += -mthumb -mthumb-interwork -mlong-calls
endif

CC_USER_FLAGS += -march=armv6

#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=

ifneq ($(INSTANCE_ID) ,)
CC_USER_DEFINES	+=-D$(strip $(INSTANCE_ID) )
endif
				
#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm.inc

#ps common include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/config/log \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
        $(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/gu/phy \
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
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/gu/was \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/gas \
	$(BALONG_TOPDIR)/modem/include/nv/tl/lps \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/taf/acore \
    	$(BALONG_TOPDIR)/modem/include/taf/ccore \
    	$(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/tools \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/visp \
	$(BALONG_TOPDIR)/modem/include/visp/tcpip \
	$(BALONG_TOPDIR)/modem/include/visp/adapter \
	$(BALONG_TOPDIR)/modem/include/visp/security \
	$(BALONG_TOPDIR)/modem/include/visp/security/acl \
	$(BALONG_TOPDIR)/modem/include/visp/security/acl/include \
	$(BALONG_TOPDIR)/modem/include/visp/tcpip/vos/config \
	$(BALONG_TOPDIR)/modem/include/visp/common \
	$(BALONG_TOPDIR)/modem/include/visp/common/visp \
	$(BALONG_TOPDIR)/modem/include/vpp/CRYPTO \
	$(BALONG_TOPDIR)/modem/include/vpp/OSAL \
	$(BALONG_TOPDIR)/modem/include/vpp/PSE \
	$(BALONG_TOPDIR)/modem/include/vpp/SSL

OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004a \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005

OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Inc

#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE :=
ifeq ($(INSTANCE_ID), INSTANCE_0)
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common/ed_lib.c \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common/csn1lib.c \

OBC_LOCAL_SRC_FILE += \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/CSN1DataTypes.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/Downlink_RLC_MAC.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ed_c.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ed_c_known_ie.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ed_c_recog.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/L3Downlink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/L3Uplink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/PLENDownlink.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/ts04.18_support.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/Uplink_RLC_MAC.c\
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/gsm/r9/Src/UserDefinedDataTypes.c
endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
