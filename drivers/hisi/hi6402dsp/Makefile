# hi6402 dsp device driver
EXTRA_CFLAGS += -Idrivers/hisi/hi6402dsp/ap/med/
EXTRA_CFLAGS += -Idrivers/hisi/slimbus/

ifneq ($(TARGET_BUILD_VARIANT),user)
	EXTRA_CFLAGS += -DENABLE_HI6402_HIFI_DEBUG
endif
ifeq ($(CONFIG_HIFI_IPC_3660),y)
	EXTRA_CFLAGS += -DPLATFORM_HI3660
endif
obj-$(CONFIG_HI6402_HIFI_MISC) += hi64xx_hifi_misc.o
obj-$(CONFIG_HI6402_HIFI_MISC) += hi6402_hifi_config.o
obj-$(CONFIG_HI6402_HIFI_MISC) += hi6403_hifi_config.o
obj-$(CONFIG_HI6402_HIFI_MISC) += hi64xx_hifi_img_dl.o