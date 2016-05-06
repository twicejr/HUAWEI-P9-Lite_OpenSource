#
# Makefile for the accelerometer drivers.
#
#sensor unification for differ platform
# Each configuration option enables a list of files.
obj-$(CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_ST_LIS3XH)	+= lis3dh_acc.o
obj-$(CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_ROHM_KX023)	+= gs_rohm_kx023.o
ifeq ($(CONFIG_GSENSOR_DEBUG),y)
EXTRA_CFLAGS += -DDEBUG
endif
