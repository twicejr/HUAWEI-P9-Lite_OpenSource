#***********************************************************#
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name
#***********************************************************#
OBC_LOCAL_MOUDLE_NAME	?=tools_config_taf

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
	$(BALONG_TOPDIR)/modem/config/osa \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
	$(BALONG_TOPDIR)/modem/include/med \
	$(BALONG_TOPDIR)/modem/include/oam/gu/usimm \
	$(BALONG_TOPDIR)/modem/include/oam/gu/osa \
	$(BALONG_TOPDIR)/modem/include/oam/gu/si \
	$(BALONG_TOPDIR)/modem/include/oam/gu/om \
	$(BALONG_TOPDIR)/modem/include/oam/comm/om \
	$(BALONG_TOPDIR)/modem/include/oam/comm/nvim \
	$(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/taf/ccore \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/tl/lps \
	$(BALONG_TOPDIR)/modem/include/taf/acore \
	$(BALONG_TOPDIR)/modem/ps/inc/gu \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/INC \
	$(BALONG_TOPDIR)/modem/ps/nas/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/gu/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/gu/lib \
	$(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc \
	$(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc \
	$(BALONG_TOPDIR)/modem/taf/comm/src/ccore/MTC/Inc \
	$(BALONG_TOPDIR)/modem/taf/inc/ccore \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/CsCall/Comm/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/CsCall/XCall/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/SDC/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Phone/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Task/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Log \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Fsm/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafMta/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Xml/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/VC/Inc \
	$(BALONG_TOPDIR)/modem/taf/comm/src/acore/at/inc \
	$(BALONG_TOPDIR)/modem/taf/comm	
#***********************************************************#
# source files
#***********************************************************#
#注：在这里添加需要编译的源文件
OBC_LOCAL_SRC_FILE := \
	$(BALONG_TOPDIR)/modem/taf/comm/hids_elf_taf.c

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
#注：在此添加需要引用的编译脚本
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
