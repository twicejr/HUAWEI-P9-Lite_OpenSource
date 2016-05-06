-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
ifeq ($(strip $(CFG_CONFIG_MODULE_TIMER)),YES)
	obj-y	+= timer_slice.o
	obj-y	+= hardtimer_arm.o
	obj-y	+= hardtimer_synopsis.o
	obj-y	+= hardtimer_core.o
	obj-y	+= softtimer_balong.o
	obj-y	+= hardtimer_balong_test.o
endif
	

