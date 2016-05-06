-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
ifeq ($(strip $(CFG_CONFIG_MODULE_IPC)),YES)
obj-$(CONFIG_IPC_DRIVER)	+= ipc_balong.o
obj-$(CONFIG_ENABLE_TEST_CODE) += ipc_balong_test.o
endif

subdir-ccflags-y := -Werror
