# Makefile for the lcd panel drivers.
#

# Each configuration option enables a list of files.

obj-$(CONFIG_HUAWEI_LCD_PANEL)  += hw_lcd_panel.o
obj-$(CONFIG_HUAWEI_LCD_PANEL)  += hw_lcd_debug.o

EXTRA_CFLAGS += -I$(LCD_EFFECT_DIR)/drivers/huawei_platform/lcd \
		-Idrivers/video/hisi/dss \
		-Idrivers/atfdriver \
		-Idrivers/hisi/tzdriver
