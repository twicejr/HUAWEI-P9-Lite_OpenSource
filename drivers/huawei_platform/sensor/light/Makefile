# Makefile for the light drivers.
#

# Each configuration option enables a list of files.

obj-$(CONFIG_HUAWEI_FEATURE_PROXIMITY_APDS990X)  += apds990x.o
obj-$(CONFIG_HUAWEI_FEATURE_PROXIMITY_RPR0521)  += rpr0521_driver.o
ifeq ($(CONFIG_PROXIMITY_LIGHT_DEBUG),y)
EXTRA_CFLAGS += -DDEBUG
endif