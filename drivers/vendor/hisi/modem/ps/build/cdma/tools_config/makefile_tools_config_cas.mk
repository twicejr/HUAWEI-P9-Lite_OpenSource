#***********************************************************#
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name
#***********************************************************#
OBC_LOCAL_MOUDLE_NAME   ?=tools_config_cas

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
    $(BALONG_TOPDIR)/modem/include/oam/gu/osa \
    $(BALONG_TOPDIR)/modem/include/oam/comm/om \
    $(BALONG_TOPDIR)/modem/include/taf/ccore \
    $(BALONG_TOPDIR)/modem/include/med \
    $(BALONG_TOPDIR)/modem/include/ps/gups/acore \
    $(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
    $(BALONG_TOPDIR)/modem/include/ps/gups/common \
    $(BALONG_TOPDIR)/modem/include/nv/gu/codec \
    $(BALONG_TOPDIR)/modem/include/nv/gu/cas \
    $(BALONG_TOPDIR)/modem/include/nv/gu/nas \
    $(BALONG_TOPDIR)/modem/include/oam/lt/common \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_sm \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_cm \
    $(BALONG_TOPDIR)/modem/include/oam/gu/usimm \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_hrpd \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_hrpd_cm \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/cproc/cproc_hrpd_sm \
    $(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
    $(BALONG_TOPDIR)/modem/include/ps/tlps/common \
    $(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/util \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/cch \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/ohm \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/phyitf \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/tch \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/srch \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/meas \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/comm \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/ttfitf \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/usimitf \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/nasitf \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/1x/inc/main \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/util \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/comm \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/inc/util \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/hrpd/scp \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/mac \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/rlp \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac/tx \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac/rx \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/lac \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/mac \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/rlp \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sig \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sps \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005 \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma/1x \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma \
    $(BALONG_TOPDIR)/modem/ps/inc/cdma/hrpd \






OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/include/taf/common \
    $(BALONG_TOPDIR)/modem/include/taf/acore \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/csdr \
    $(BALONG_TOPDIR)/modem/include/phy/cphy/csdr/hrpd \
    $(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
    $(BALONG_TOPDIR)/modem/ps/inc/gu \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/lcp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ipcp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/pap \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/chap \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ccp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/eap \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/ipv6cp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/vsncp \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/stac \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/adapter/spuf \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/adapter/spud \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/common \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/PPP/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/PPPC/util \
    $(BALONG_TOPDIR)/modem/ps/comm/inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/DICC/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/FLOWCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/FLOWCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/LOGFILTER/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEMCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/MEM/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/STL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CDS/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CRC/inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/Pstool/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0004 \
    $(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/common/IP/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/comm/TPE/Inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/mntn/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/lac/utility/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/ctrlext/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/voiceagent/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/loopback/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/markov/utility/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/tdso/utility/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/testso/testsoctrl/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/mntn/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/mac/utility/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/mntn/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/rlp/utility/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/comm/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/comm/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc \
    $(BALONG_TOPDIR)/modem/ps/as/comm/tools/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/frmwk/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/mac \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/rlp \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sig \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/inc/hrpd/sps \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/1x/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/utility/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/mac/mntn/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/mntn/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sig/utility/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/sps/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/rx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/tx/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/mntn/inc \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cttf/hrpd/pa/inc


#***********************************************************#
# source files
#***********************************************************#
#注：在这里添加需要编译的源文件
OBC_LOCAL_SRC_FILE := \
    $(BALONG_TOPDIR)/modem/ps/as/cdma/cas/comm/hids_elf_Cas.c 

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
#注：在此添加需要引用的编译脚本
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
