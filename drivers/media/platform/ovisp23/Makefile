#
# Makefile for hisilicon camera v4l2 driver
# Author: hefei
#
EXTRA_CFLAGS += -Idrivers/media/platform/ovisp23/camera
EXTRA_CFLAGS += -fno-pic

hisi_camera_all-objs := hisi_cam_module.o \
			sensor/hisi_sensor.o \
			isp/hisi_isp.o  \
			camera/hisi_camera.o \
			vcm/hisi_vcm.o	\
			io/hisi_isp_io.o \
			cci/hisi_cci.o	\
			csi/hisi_csi.o	\
			flash/hisi_flash.o

obj-$(CONFIG_VIDEO_HISI_CAMERA) += hisi_camera_all.o

obj-$(CONFIG_HISI_CAMERA_SENSOR)	+= sensor/
obj-$(CONFIG_HISI_CAMERA_OVISP23)	+= isp/
obj-$(CONFIG_HISI_CAMERA_VCM)	+= vcm/
obj-$(CONFIG_HISI_CAMERA_VIDEO)	+= camera/
obj-$(CONFIG_HISI_CAMERA_FLASH)	+= flash/
