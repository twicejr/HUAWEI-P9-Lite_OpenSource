ccflags-y += -Idrivers/media/huawei/camera/sensor
ccflags-y += -Idrivers/media/huawei/camera
ccflags-y += -Idrivers/media/huawei/camera/csi
ccflags-y += -Idrivers/media/huawei/camera/platform

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_FAKE_SENSOR),y) 
	obj-y += fake-sensor.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX135),y)
	obj-n += imx135.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX214),y)
	obj-y += imx214.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX278),y)
	obj-y += imx278.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX278_CARRERA),y)
	obj-y += imx278_carrera.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX278_DAVINCE),y)
	obj-y += imx278_davince.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX214_SUNNY),y)
	obj-y += imx214_sunny.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX328),y)
	obj-y += imx328.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV13850),y)
	obj-y += ov13850.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX179),y)
	obj-y += imx179.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX179_CARRERA),y)
	obj-y += imx179_carrera.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV8865),y)
	obj-y += ov8865.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV5648),y) 
	obj-n += ov5648.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV5648_X1S),y) 
	obj-y += ov5648_x1s.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_S5K4E1GA),y)
	obj-y += s5k4e1ga.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX179_REAR),y)
	obj-n += imx179_rear.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX179_FRONT),y)
	obj-n += imx179_front.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV8865_REAR),y)
	obj-n += ov8865_rear.o
endif
ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX219),y) 
	obj-y += imx219.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV8858),y) 
	obj-y += ov8858.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV8865_CARRERA),y)
	obj-y += ov8865_carrera.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_OV2680),y) 
	obj-y += ov2680.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_MT9D015),y) 
	obj-y += mt9d015.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX179_PLK),y)
	obj-y += imx179_plk.o
endif

ifeq ($(CONFIG_HUAWEI_CAMERA_USE_IMX230_PLK),y)
	obj-y += imx230_plk.o
endif
