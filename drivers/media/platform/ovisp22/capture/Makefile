#
# Makefile for hisilicon K3 soc camera v4l2 driver
# Author: m55267
#


subdir-ccflags-y += -Idrivers/huawei/camera/mini_isp/
EXTRA_CFLAGS += -Idrivers/media/platform/ovisp22/capture/isp
EXTRA_CFLAGS += -Idrivers/media/platform/ovisp22/capture/isp_for_misp
EXTRA_CFLAGS += -Idrivers/media/platform/ovisp22/capture/common
EXTRA_CFLAGS += -Idrviers/huawei/camera/mini_isp
EXTRA_CFLAGS += -Idrivers/videocom/regops
EXTRA_CFLAGS += -Idrivers/videocom/videoharden
EXTRA_CFLAGS += -Idrivers/videocom/videoconfig
EXTRA_CFLAGS += -fno-pic


k3_capture-objs := isp/cam_util.o \
		   isp/cam_dbg.o \
		   isp/k3_v4l2_capture.o \
		   isp/k3_isp.o \
		   isp/k3_isp_io.o \
		   isp/k3_ispv1.o \
		   isp/k3_ispv1_afae.o \
		   isp/k3_ispv1_tune_ops.o \
		   isp/k3_ispv1_io.o \
		   isp/sensor_common.o \
		   isp/hwa_cam_tune.o \
		   isp/hw_soft_3a.o \
		   isp_module_init.o
mini_isp-objs :=   isp_for_misp/mini_hdr_movie.o \
		   isp_for_misp/mini_cam_util.o \
		   isp_for_misp/mini_cam_dbg.o \
		   isp_for_misp/mini_k3_v4l2_capture.o \
		   isp_for_misp/mini_k3_isp.o \
		   isp_for_misp/mini_k3_isp_io.o \
		   isp_for_misp/mini_k3_ispv1.o \
		   isp_for_misp/mini_k3_ispv1_afae.o \
		   isp_for_misp/mini_k3_ispv1_tune_ops.o \
		   isp_for_misp/mini_k3_ispv1_io.o \
		   isp_for_misp/mini_sensor_common.o \
		   isp_for_misp/mini_hwa_cam_tune.o \
		   isp_for_misp/mini_hw_soft_3a.o 



obj-$(CONFIG_CAMERA_MINI_ISP) += mini_isp.o
obj-$(CONFIG_VIDEO_HI6210_CAMERA) += k3_capture.o
subdir-ccflags-$(CONFIG_HISI_BB)               += -Idrivers/hisi/mntn/blackbox/
#obj-m += k3_capture.o
