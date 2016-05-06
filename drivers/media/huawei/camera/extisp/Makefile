ccflags-y += -Idrivers/media/huawei/camera
ccflags-y += -Idrivers/media/huawei/camera/platform

obj-y = hwextisp.o 

obj-y += altek6045/

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_ALTEK6045),y)
	obj-y += altek6045/
endif

