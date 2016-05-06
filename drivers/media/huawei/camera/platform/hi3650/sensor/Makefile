ifneq ($(TARGET_BUILD_VARIANT),user)
EXTRA_CFLAGS += -DDEBUG_HISI_CAMERA
endif
ccflags-y += -Idrivers/media/huawei/camera/sensor
ccflags-y += -Idrivers/media/huawei/camera
ccflags-y += -Idrivers/media/huawei/camera/csi
ccflags-y += -Idrivers/media/huawei/camera/platform

obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX214) += imx214.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX230) += imx230.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX278) += imx278.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX179) += imx179.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX298) += imx298.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX214DUAL) += imx214dual.o
obj-y += imx286dual.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX179) += imx179_eva.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX179) += imx179_vienna.o
obj-y += imx214dual_knt.o
obj-y += imx286dual_knt.o
#obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX286DUAL_GAL) += imx286dual_gal.o
obj-y += imx286dual_gal.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX179) += imx179_knt.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_OV8865) += ov8865.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_HI843) += hi843.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_OV8856) += ov8856.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_IMX219) += imx219.o
obj-$(CONFIG_HUAWEI_CAMERA_USE_OV8865) += ov8865_knt.o
