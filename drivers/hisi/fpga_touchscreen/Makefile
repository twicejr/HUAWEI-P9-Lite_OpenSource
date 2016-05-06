# Makefile for the irda drivers.
#

# Each configuration option enables a list of files.

obj-$(CONFIG_HISI_FPGA_TS)  += huawei_touchscreen.o
obj-$(CONFIG_HISI_FPGA_TS) += panel/
obj-$(CONFIG_HISI_FPGA_TS)  += huawei_touchscreen_algo.o
obj-$(CONFIG_HISI_FPGA_TS_TEST)  += huawei_touchscreen_test.o

obj-$(CONFIG_HISI_FPGA_TP_COLOR_INFO) += tp_color.o

ifeq ($(CONFIG_HISI_FPGA_TS_TEST),y)
EXTRA_CFLAGS += -DHUAWEI_TOUCHSCREEN_TEST
endif
EXTRA_CFLAGS += -Idrivers/hisi/tzdriver
