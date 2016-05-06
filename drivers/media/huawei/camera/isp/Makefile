ccflags-y += -Idrivers/media/huawei/camera

obj-y = hwisp.o hwisp_stream.o

CFLAGS_hwisp_stream.o = -I$(src)

#ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OVISP23),y)
	obj-y += ovisp2.3/
#endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OVISP22),y)
	obj-y += ovisp2.2/
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OVISP20),y)
	obj-y += ovisp2.0/
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_FAKE_ISP),y)
	obj-y += fake/
endif

