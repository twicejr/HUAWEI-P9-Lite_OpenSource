ccflags-y += -Idrivers/media/huawei/camera

ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV100), y)
ccflags-y += -Idrivers/media/huawei/camera/platform/hi3650
obj-y += hi3650/
endif

ifeq ($(CONFIG_HISI_CAMERA_OVISP23), y)
ccflags-y += -Idrivers/media/huawei/camera/platform/hi3635
obj-y += hi3635/
endif

ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV110), y)
ccflags-y += -Idrivers/media/huawei/camera/platform/hi6250
obj-y += hi6250/
endif
