#
# Makefile for hisilicon camera flash driver
#
EXTRA_CFLAGS += -Idrivers/media/video/hisi/camera/flash
EXTRA_CFLAGS += -fno-pic

obj-$(CONFIG_HISI_CAMERA_FLASH) += hisi_flash_i2c.o

obj-$(CONFIG_HISI_CAMERA_TPS61310) += tps61310.o

obj-$(CONFIG_HISI_CAMERA_LM3642) += lm3642.o

obj-$(CONFIG_HISI_CAMERA_PMU_LED) += pmu_led.o