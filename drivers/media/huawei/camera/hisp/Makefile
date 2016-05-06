ccflags-y += -Idrivers/media/huawei/camera
ccflags-y += -Idrivers/rpmsg

obj-y += hisp.o


ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV100), y)
	obj-y += hisp100/
endif

ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV110), y)
	obj-y += hisp110/
endif

ifneq ($(CONFIG_RPMSG),y)
	obj-y += fakefw/
endif


