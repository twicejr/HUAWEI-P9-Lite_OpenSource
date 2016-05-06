#***********************************************************#
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name
#***********************************************************#
OBC_LOCAL_MOUDLE_NAME	?=tools_config_gumsp

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
MSP_SRC_DIR				:=$(BALONG_TOPDIR)/modem/oam
MSP_INC_DIR			    :=$(MSP_SRC_DIR)/inc
PRJ_CONFIG_DIR          :=$(BALONG_TOPDIR)/modem/config
PRJ_INCLUDE_DIR         :=$(BALONG_TOPDIR)/modem/include
PRJ_PLATFORM_DIR        :=$(BALONG_TOPDIR)/modem/platform

OBC_LOCAL_INC_DIR += \
        $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config \
        $(PRJ_CONFIG_DIR)\log \
        $(PRJ_CONFIG_DIR)\nvim\include\gu \
        $(PRJ_CONFIG_DIR)\osa \
        $(PRJ_INCLUDE_DIR)\app \
        $(PRJ_INCLUDE_DIR)\drv \
        $(PRJ_INCLUDE_DIR)\drv\common \
        $(PRJ_INCLUDE_DIR)\drv\ccore \
        $(PRJ_INCLUDE_DIR)\med \
        $(PRJ_INCLUDE_DIR)\oam\comm\om \
        $(PRJ_INCLUDE_DIR)\oam\gu\osa \
        $(PRJ_INCLUDE_DIR)\oam\comm\scm \
        $(PRJ_INCLUDE_DIR)\oam\gu\si \
        $(PRJ_INCLUDE_DIR)\oam\comm\socp \
        $(PRJ_INCLUDE_DIR)\oam\gu\usimm \
        $(PRJ_INCLUDE_DIR)\oam\comm\errno \
        $(PRJ_INCLUDE_DIR)\oam\comm\dms \
        $(PRJ_INCLUDE_DIR)\oam\comm\nvim \
        $(PRJ_INCLUDE_DIR)\oam\gu\log \
        $(PRJ_INCLUDE_DIR)\oam\gu\om \
        $(PRJ_INCLUDE_DIR)\oam\gu\nvim \
        $(PRJ_INCLUDE_DIR)\oam\gu\hpa \
        $(PRJ_INCLUDE_DIR)\nv\gu\oam \
        $(PRJ_INCLUDE_DIR)\nv\gu\codec \
        $(PRJ_INCLUDE_DIR)\nv\gu\drv \
        $(PRJ_INCLUDE_DIR)\nv\gu\gas \
        $(PRJ_INCLUDE_DIR)\nv\gu\nas \
        $(PRJ_INCLUDE_DIR)\nv\gu\phy \
        $(PRJ_INCLUDE_DIR)\nv\gu\tool \
        $(PRJ_INCLUDE_DIR)\nv\gu\ttf \
        $(PRJ_INCLUDE_DIR)\nv\gu\was \
        $(PRJ_INCLUDE_DIR)\nv\gu\cas \
        $(PRJ_INCLUDE_DIR)\nv\tl\oam \
        $(PRJ_INCLUDE_DIR)\phy\wphy \
        $(PRJ_INCLUDE_DIR)\phy\cphy\csdr \
        $(PRJ_INCLUDE_DIR)\phy\cphy\cproc\
        $(PRJ_INCLUDE_DIR)\phy\cphy\cproc\cproc_cm \
        $(PRJ_INCLUDE_DIR)\phy\cphy\comm \
        $(PRJ_INCLUDE_DIR)\Med \
        $(PRJ_INCLUDE_DIR)\tools \
        $(PRJ_INCLUDE_DIR)\phy\gphy \
        $(PRJ_INCLUDE_DIR)\ps\nas \
        $(PRJ_INCLUDE_DIR)\ps\tlps \
        $(PRJ_INCLUDE_DIR)\ps\gups \
        $(PRJ_INCLUDE_DIR)\taf\acore \
        $(PRJ_INCLUDE_DIR)\taf\ccore \
        $(PRJ_INCLUDE_DIR)\taf\common \
        $(MSP_INC_DIR)\comm\acore\dms \
        $(MSP_INC_DIR)\comm\acore\om \
        $(MSP_INC_DIR)\comm\ccore\om \
        $(MSP_INC_DIR)\comm\comm\om \
        $(MSP_INC_DIR)\gu\ccore\usimm \
        $(MSP_INC_DIR)\gu\comm\si \
        $(MSP_INC_DIR)\gu\acore\om \
        $(MSP_INC_DIR)\gu\ccore\hpa \
        $(MSP_INC_DIR)\gu\ccore\om \
        $(MSP_INC_DIR)\gu\ccore\pstool \
        $(MSP_INC_DIR)\gu\ccore\sc \
        $(MSP_INC_DIR)\gu\ccore\sleep \
        $(MSP_INC_DIR)\gu\comm\sc \
        $(MSP_INC_DIR)\gu\ccore\xml \
        $(MSP_INC_DIR)\gu\comm\om \
        $(MSP_INC_DIR)\gu\comm\bbplog \
        $(MSP_INC_DIR)\gu\comm\cbtfun \
        $(MSP_INC_DIR)\lt\comm\diag\
        $(PRJ_CONFIG_DIR)\log \
        $(PRJ_CONFIG_DIR)\nvim\include\gu \
        $(PRJ_CONFIG_DIR)\nvim\data\comm \
        $(PRJ_CONFIG_DIR)\osa \
        $(PRJ_INCLUDE_DIR)\app \
        $(PRJ_INCLUDE_DIR)\drv \
        $(PRJ_INCLUDE_DIR)\drv\ccore \
        $(PRJ_INCLUDE_DIR)\med \
        $(PRJ_INCLUDE_DIR)\oam\comm\om \
        $(PRJ_INCLUDE_DIR)\oam\gu\osa \
        $(PRJ_INCLUDE_DIR)\oam\comm\scm \
        $(PRJ_INCLUDE_DIR)\oam\gu\si \
        $(PRJ_INCLUDE_DIR)\oam\comm\socp \
        $(PRJ_INCLUDE_DIR)\oam\gu\usimm \
        $(PRJ_INCLUDE_DIR)\oam\comm\errno \
        $(PRJ_INCLUDE_DIR)\oam\comm\dms \
        $(PRJ_INCLUDE_DIR)\oam\comm\nvim \
        $(PRJ_INCLUDE_DIR)\oam\gu\cbpa \
        $(PRJ_INCLUDE_DIR)\oam\comm\cpm \
        $(PRJ_INCLUDE_DIR)\oam\gu\log \
        $(PRJ_INCLUDE_DIR)\oam\gu\om \
        $(PRJ_INCLUDE_DIR)\nv\gu\oam \
        $(PRJ_INCLUDE_DIR)\nv\gu\codec \
        $(PRJ_INCLUDE_DIR)\nv\gu\drv \
        $(PRJ_INCLUDE_DIR)\nv\gu\gas \
        $(PRJ_INCLUDE_DIR)\nv\gu\nas \
        $(PRJ_INCLUDE_DIR)\nv\gu\phy \
        $(PRJ_INCLUDE_DIR)\nv\gu\ttf \
        $(PRJ_INCLUDE_DIR)\nv\gu\was \
        $(PRJ_INCLUDE_DIR)\nv\gu\tool \
        $(PRJ_INCLUDE_DIR)\phy\wphy \
        $(PRJ_INCLUDE_DIR)\ps\nas \
        $(PRJ_INCLUDE_DIR)\taf\ccore \
        $(PRJ_INCLUDE_DIR)\taf\common \
        $(MSP_INC_DIR)\gu\ccore\usimm \
        $(MSP_INC_DIR)\gu\ccore\cbpa \
        $(MSP_INC_DIR)\gu\comm\si \
        $(MSP_INC_DIR)\comm\comm\nvim \
        $(MSP_INC_DIR)\comm\comm\ppm \
        $(MSP_INC_DIR)\comm\ccore\nvim \
        $(MSP_INC_DIR)\gu\ccore\dh \
        $(MSP_INC_DIR)\gu\acore\om \
        $(MSP_INC_DIR)\gu\acore\cbtcpm \
        $(MSP_INC_DIR)\gu\acore\cbtfun \
        $(MSP_INC_DIR)\gu\acore\cbtppm \
        $(MSP_INC_DIR)\gu\ccore\hpa \
        $(MSP_INC_DIR)\gu\ccore\om \
        $(MSP_INC_DIR)\gu\ccore\pstool \
        $(MSP_INC_DIR)\gu\ccore\sc \
        $(MSP_INC_DIR)\gu\ccore\sleep \
        $(MSP_INC_DIR)\gu\comm\om \
        $(MSP_INC_DIR)\gu\comm\cbtfun \
        $(PRJ_INCLUDE_DIR)\oam\lt\ccore \
        $(PRJ_INCLUDE_DIR)\oam\lt\common\
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
        $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CRC/inc \
        $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/cdma/cs0005 \
        $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/encodix/common \
        $(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
        $(BALONG_TOPDIR)/modem/ps/nas/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/fsm/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/mml/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/gu/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/gu/lib \
        $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/ccb/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/mntn/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/prl/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/task/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/comm/timer/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xsd/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xreg/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/xcc/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hlu/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsd/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/hsm/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/hrpd/ehsm/inc \
        $(BALONG_TOPDIR)/modem/ps/as/tl/tds/comm/tgl_ps/include \
        $(BALONG_TOPDIR)/modem/ps/inc/cdma \
        $(BALONG_TOPDIR)/modem/ps/inc/1x \
        $(BALONG_TOPDIR)/modem/ps/inc/cdma/hrpd \
        $(BALONG_TOPDIR)/modem/taf/inc/acore \
        $(BALONG_TOPDIR)/modem/taf/inc/ccore \
        $(BALONG_TOPDIR)/modem/taf/inc/common \
        $(BALONG_TOPDIR)/modem/taf/comm/inc \
        $(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/Lib \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn\Xsms\Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Xpds/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Fsm/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Xml/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Log \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Call/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Data/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Msg/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Phone/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Sups/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Task/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/VC/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafDrvAgent/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/CBA/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/SDC/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafMta/Inc \
        $(BALONG_TOPDIR)/modem/config/log \
        $(BALONG_TOPDIR)/modem/config/nvim/include/gu \
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
        $(BALONG_TOPDIR)/modem/include/oam/lt/ccore \
        $(BALONG_TOPDIR)/modem/include/oam/lt/common \
        $(BALONG_TOPDIR)/modem/include/phy/gphy \
        $(BALONG_TOPDIR)/modem/include/phy/wphy \
        $(BALONG_TOPDIR)/modem/include/ps/gups \
        $(BALONG_TOPDIR)/modem/include/ps/tlps \
        $(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
        $(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
        $(BALONG_TOPDIR)/modem/include/ps/tlps/common \
        $(BALONG_TOPDIR)/modem/include/ps/nas \
        $(BALONG_TOPDIR)/modem/include/taf/ccore \
        $(BALONG_TOPDIR)/modem/include/taf/common \
        $(BALONG_TOPDIR)/modem/include/tools \
        $(BALONG_TOPDIR)/modem/include/med \
        $(BALONG_TOPDIR)/modem/include/nv/gu/codec \
        $(BALONG_TOPDIR)/modem/include/nv/gu/nas \
        $(BALONG_TOPDIR)/modem/include/nv/gu/gas \
        $(BALONG_TOPDIR)/modem/include/nv/gu/was \
        $(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
        $(BALONG_TOPDIR)/modem/include/nv/gu/oam \
        $(BALONG_TOPDIR)/modem/include/nv/gu/codec \
        $(BALONG_TOPDIR)/modem/include/nv/tl/lps \
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
        $(BALONG_TOPDIR)/modem/ps/comm/comm/ccore/CRC/inc \
        $(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
        $(BALONG_TOPDIR)/modem/ps/nas/inc \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/fsm/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/mml/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/NASUSIMMAPI/INC \
        $(BALONG_TOPDIR)/modem/ps/nas/comm/mscc/inc \
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
        $(BALONG_TOPDIR)/modem/ps/nas/cdma/1x/inc \
        $(BALONG_TOPDIR)/modem/taf/inc/ccore \
        $(BALONG_TOPDIR)/modem/taf/inc/common \
        $(BALONG_TOPDIR)/modem/taf/comm/inc \
        $(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/Lib \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Fsm/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Xml/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Log \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Call/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Data/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Msg/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Phone/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Sups/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Task/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/VC/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafDrvAgent/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/CBA/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/SDC/Inc \
        $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafMta/Inc

#***********************************************************#
# source files
#***********************************************************#
#注：在这里添加需要编译的源文件
OBC_LOCAL_SRC_FILE := $(BALONG_TOPDIR)/modem/oam/gu/comm/tools/hids_elf_pam.c

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
#注：在此添加需要引用的编译脚本
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_rtosck_rules.mk
