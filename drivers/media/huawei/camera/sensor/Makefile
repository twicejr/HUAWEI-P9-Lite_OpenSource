ifneq ($(TARGET_BUILD_VARIANT),user)
EXTRA_CFLAGS += -DDEBUG_HISI_CAMERA
endif
ccflags-y += -Idrivers/media/huawei/camera
ccflags-y += -Idrivers/media/huawei/camera/platform

obj-y += hwsensor.o camerafs.o flash/ vcm/ ois/
