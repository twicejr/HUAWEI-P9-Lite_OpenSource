####################################################################################################
#
####################################################################################################
MSP_SRC_DIR				:=$(BALONG_SRC_PATH)/modem/oam
MSP_INC_DIR			    :=$(MSP_SRC_DIR)/inc
PRJ_CONFIG_DIR          :=$(BALONG_SRC_PATH)/modem/config
PRJ_INCLUDE_DIR         :=$(BALONG_SRC_PATH)/modem/include
PRJ_PLATFORM_DIR        :=$(BALONG_SRC_PATH)/modem/platform

####################################################################################################
#Directories for include files
####################################################################################################
vob_include_dirs :=   $(PRJ_CONFIG_DIR)/product/$(PRODUCT_CFG_PRODUCT_FORM)/include \
					  $(PRJ_PLATFORM_DIR)/$(PRODUCT_CFG_PLATFORM_NEW) \
					  $(PRJ_PLATFORM_DIR)/$(PRODUCT_CFG_PLATFORM_NEW)/soc \
					  $(PRJ_PLATFORM_DIR)/$(PRODUCT_CFG_PLATFORM_NEW)/winterface \
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
					  $(PRJ_INCLUDE_DIR)\phy\cphy \
					  $(PRJ_INCLUDE_DIR)\Med \
					  $(PRJ_INCLUDE_DIR)\tools \
					  $(PRJ_INCLUDE_DIR)\phy\gphy \
					  $(PRJ_INCLUDE_DIR)\ps\nas \
					  $(PRJ_INCLUDE_DIR)\ps\tlps\acore \
					  $(PRJ_INCLUDE_DIR)\ps\tlps\ccore \
					  $(PRJ_INCLUDE_DIR)\ps\tlps\common \
					  $(PRJ_INCLUDE_DIR)\ps\gups\acore \
					  $(PRJ_INCLUDE_DIR)\ps\gups\ccore \
					  $(PRJ_INCLUDE_DIR)\ps\gups\common \
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
					  $(MSP_INC_DIR)\lt\comm\diag
