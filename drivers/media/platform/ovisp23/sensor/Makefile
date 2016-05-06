#
# Makefile for hisilicon camera sensor driver
#
EXTRA_CFLAGS += -Idrivers/media/video/hisi/camera/sensor
EXTRA_CFLAGS += -fno-pic

obj-$(CONFIG_HISI_CAMERA_SENSOR) += sensor_common.o

obj-$(CONFIG_HISI_CAMERA_IMX214) += imx214.o
obj-$(CONFIG_HISI_CAMERA_OV8830) += ov8830.o
obj-$(CONFIG_HISI_CAMERA_IMX135) += imx135.o
obj-$(CONFIG_HISI_CAMERA_OV5648) += ov5648.o
obj-$(CONFIG_HISI_CAMERA_S5K4E1GA) += s5k4e1ga.o
obj-$(CONFIG_HISI_CAMERA_MT9M114) += mt9m114.o