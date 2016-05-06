####################################################################################################
#
####################################################################################################
MSP_SRC_DIR				:=$(BALONG_SRC_PATH)/modem/oam
MSP_INC_DIR				:=$(MSP_SRC_DIR)/inc
PRJ_CONFIG_DIR          :=$(BALONG_SRC_PATH)/modem/config
PRJ_INCLUDE_DIR         :=$(BALONG_SRC_PATH)/modem/include
PRJ_PLATFORM_DIR        :=$(BALONG_SRC_PATH)/modem/platform

####################################################################################################
#Directories for include files
####################################################################################################
vob_include_dirs :=   $(PRJ_CONFIG_DIR)/product/$(PRODUCT_CFG_PRODUCT_FORM)/include \
					  $(PRJ_PLATFORM_DIR)/$(PRODUCT_CFG_PLATFORM_NEW) \
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
					  $(PRJ_INCLUDE_DIR)\taf \
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


vob_include_dirs += \
					  $(PRJ_INCLUDE_DIR)\oam\lt\ccore \
					  $(PRJ_INCLUDE_DIR)\oam\lt\common

					  
					  
