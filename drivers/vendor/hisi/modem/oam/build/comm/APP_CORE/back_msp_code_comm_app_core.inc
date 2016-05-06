# Core information


MSP_INC_DIRS := \
	$(LINUX_KERNEL)/arch/arm/mach-balong/include/mach \
	$(LINUX_KERNEL)/include/linux \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/ \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/include/ \
	$(BALONG_TOPDIR)/modem/config/log \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
	$(BALONG_TOPDIR)/modem/config/nvim/data/comm \
	$(BALONG_TOPDIR)/modem/config/osa \
	$(BALONG_TOPDIR)/modem/config/nvim/include/lt/tlps \
	$(BALONG_TOPDIR)/modem/include/app/ \
	$(BALONG_TOPDIR)/modem/include/drv/ \
	$(BALONG_TOPDIR)/modem/include/drv/common \
	$(BALONG_TOPDIR)/modem/include/drv/ccore \
	$(BALONG_TOPDIR)/modem/include/med/ \
	$(BALONG_TOPDIR)/modem/include/oam/comm/om \
	$(BALONG_TOPDIR)/modem/include/oam/gu/osa \
	$(BALONG_TOPDIR)/modem/include/oam/comm/scm \
	$(BALONG_TOPDIR)/modem/include/oam/gu/si \
	$(BALONG_TOPDIR)/modem/include/oam/comm/socp \
	$(BALONG_TOPDIR)/modem/include/oam/gu/usimm \
	$(BALONG_TOPDIR)/modem/include/oam/comm/errno \
	$(BALONG_TOPDIR)/modem/include/oam/comm/nvim \
	$(BALONG_TOPDIR)/modem/include/oam/gu/log \
	$(BALONG_TOPDIR)/modem/include/oam/gu/om \
	$(BALONG_TOPDIR)/modem/include/nv/gu/oam \
	$(BALONG_TOPDIR)/modem/include/nv/gu/codec \
	$(BALONG_TOPDIR)/modem/include/nv/gu/drv \
	$(BALONG_TOPDIR)/modem/include/nv/gu/gas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/nas \
	$(BALONG_TOPDIR)/modem/include/nv/gu/phy \
	$(BALONG_TOPDIR)/modem/include/nv/gu/tool \
	$(BALONG_TOPDIR)/modem/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/modem/include/nv/gu/was \
	$(BALONG_TOPDIR)/modem/include/oam/gu/nvim \
	$(BALONG_TOPDIR)/modem/include/oam/gu/hpa \
	$(BALONG_TOPDIR)/modem/include/phy/gphy \
	$(BALONG_TOPDIR)/modem/include/phy/wphy \
	$(BALONG_TOPDIR)/modem/include/ps/gups/acore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/gups/common \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/acore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/ccore \
	$(BALONG_TOPDIR)/modem/include/ps/tlps/common \
	$(BALONG_TOPDIR)/modem/include/ps/nas \
	$(BALONG_TOPDIR)/modem/include/taf/acore \
    $(BALONG_TOPDIR)/modem/include/taf/ccore \
    $(BALONG_TOPDIR)/modem/include/taf/common \
	$(BALONG_TOPDIR)/modem/include/tools \
	$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM_HISI_BALONG)/ \


MSP_INC_DIRS += \
	$(BALONG_TOPDIR)/modem/include/oam/lt/common \
	$(BALONG_TOPDIR)/modem/include/oam/lt/acore 

	
MSP_INC_DIRS += \
	$(BALONG_TOPDIR)/modem/oam/inc/comm/ccore/om \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/comm/si \
	$(BALONG_TOPDIR)/modem/oam/inc/comm/comm/nvim \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/ccore/usimm \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/acore/om \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/ccore/hpa \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/ccore/nvim \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/ccore/om \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/ccore/pstool \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/ccore/sc \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/ccore/sleep \
	$(BALONG_TOPDIR)/modem/oam/inc/gu/comm/om \
	
	
MSP_INC_DIRS += \
	$(BALONG_TOPDIR)/modem/taf/inc/acore/ \
    $(BALONG_TOPDIR)/modem/taf/inc/ccore/ \
    $(BALONG_TOPDIR)/modem/taf/inc/common/ \
	$(BALONG_TOPDIR)/modem/taf/comm/src/acore/at/inc/ \
	$(BALONG_TOPDIR)/modem/taf/comm/src/acore/tafapi/inc \
	$(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc/ \
	$(BALONG_TOPDIR)/modem/taf/comm/src/acore/TAFAGENT/Inc/ \
	$(BALONG_TOPDIR)/modem/taf/comm/src/acore/APPVCOM/Inc/ \
	
#	$(BALONG_TOPDIR)/modem/ps/source/inc/gu/ \	
	
