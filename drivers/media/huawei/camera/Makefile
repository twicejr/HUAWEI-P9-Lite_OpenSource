ifneq ($(TARGET_BUILD_VARIANT),user)
EXTRA_CFLAGS += -DDEBUG_HISI_CAMERA
endif


obj-y += hwcam_usrdev.o hwcam_cfgdev.o hwcam_cfgpipeline.o hwcam_cfgstream.o hwcam_compat32.o

CFLAGS_hwcam_cfgdev.o = -I$(src)


obj-y += sensor/

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_EXTISP),y)
	obj-y += extisp/
endif

obj-y += depthisp/
obj-y += isp/
obj-y += hisp/
obj-y += cci/
obj-y += csi/
obj-y += io/
obj-y += pmic/
obj-y += platform/
obj-y += laser/
