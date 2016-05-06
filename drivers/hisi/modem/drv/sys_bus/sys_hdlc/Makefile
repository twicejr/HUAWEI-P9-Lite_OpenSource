#
# Makefile for the linux kernel.
#
-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
ccflags-y := -Werror
ccflags-y += -Idrivers/hisi/modem/drv/sys_bus -Idrivers/hisi/modem/drv/common/include -Iinclude/linux 
obj-y += sys_hdlc.o mem_fun.o basicfunc.o hdlcv200_frm_def_test_bbit.o 
