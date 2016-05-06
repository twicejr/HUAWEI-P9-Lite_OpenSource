-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
obj-$(CONFIG_IPF_SUPPORT)           += ipf_balong.o
obj-$(CONFIG_ENABLE_TEST_CODE)   	+= ipf_balong_test.o

ifeq ($(strip $(CFG_CONFIG_MODULE_BUSSTRESS)),YES)
#obj-$(CONFIG_IPF_SUPPORT) 		    += ipf_stress_test.o
endif

