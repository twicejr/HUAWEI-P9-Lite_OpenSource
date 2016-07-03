ifeq ($(CONFIG_HISI_FB_3650),y)
obj-$(CONFIG_HISI_FB_3650) := hisifb.o
endif

ifeq ($(CONFIG_HISI_FB_6250),y)
obj-$(CONFIG_HISI_FB_6250) := hisifb.o
endif

ifeq ($(CONFIG_HISI_FB_3660),y)
obj-$(CONFIG_HISI_FB_3660) := hisifb.o
endif

hisifb-objs := \
	hisi_mipi_dsi_host.o \
	hisi_mipi_dsi.o \
	hisi_pwm.o \
	hisi_blpwm.o \
	hisi_sensorhub_blpwm.o \
	hisi_dpe.o \
	hisi_fb_panel.o \
	hisi_fb_isr.o \
	hisi_fb_vsync.o \
	hisi_fb_esd.o \
	hisi_fb_buf_sync.o \
	hisi_fb_bl.o \
	hisi_fb_utils.o \
	hisi_fb.o \
	hisi_overlay_utils.o \
	hisi_overlay_online.o \
	hisi_overlay_offline.o \
	hisi_block_algorithm.o \
	hisi_overlay_cmdlist_utils.o \
	hisi_offlinecomposer_panel.o

ifeq ($(CONFIG_HISI_FB_3650),y)
hisifb-objs += \
	hisi_dpe_utils_hi3650.o \
	hisi_display_effect_hi3650.o \
	hisi_overlay_utils_hi3650.o \
	hisi_fb_secure.o \
	hisi_rgb2mipi.o \
	hisi_fb_spi.o \
	hisi_cfg_sbl.o \
	panel/mipi_tianma_OTM9608A.o \
	panel/mipi_jdi_OTM1902B.o \
	panel/mipi_jdi_NT35695.o \
	panel/mipi_qunchuang_ER63419.o \
	panel/mipi_auo_NT35597.o \
	panel/mipi_jdi_OTM1906A.o \
	panel/mipi_lg_eR69006A.o \
	panel/mipi_lg_ER69006_5p7.o \
	panel/mipi_boe_ER69006_5p7.o \
	panel/mipi_jdi_NT35695_cut2_5.o \
	panel/mipi_jdi_NT35695_cut3_1.o \
	panel/mipi_jdi_NT36850.o \
	panel/mipi_sharp_NT35597.o \
	panel/mipi_lg_R69006_5p2.o \
	panel/mipi_lg_R69006_5p5.o \
	panel/mipi_sharp_NT35695_5p2.o \
	panel/mipi_sharp_NT35695_5p5.o \
	panel/mipi_lg_ER69007_5p7.o \
	panel/mipi_sharp_NT35597_5p7.o\
	panel/mipi_jdi_R63450_5p7.o \
	panel/mipi_jdi_R63452_5p2.o \
	panel/mipi_jdi_R63452_5p5.o \
	panel/mipi_jdi_R63452_5p7.o \
	panel/mipi_sharp_NT35695_5p7.o\
	panel/mipi_samsung_D53G6EA8064T.o \
	panel/mipi_samsung_S6E3HA3X01.o \
	panel/mipi_samsung_S6E3HA3X02.o \
	panel/mipi_lcd_external_panel.o \
	backlight/lm36923.o
endif

ifeq ($(CONFIG_HISI_FB_6250),y)
hisifb-objs += \
	hisi_dpe_utils_hi3650.o \
	hisi_display_effect_hi3650.o \
	hisi_overlay_utils_hi6250.o \
	hisi_fb_secure.o \
	hisi_rgb2mipi.o \
	hisi_fb_spi.o \
	hisi_cfg_sbl.o \
	panel/mipi_lcd_external_panel.o \
	panel/mipi_auo_OTM1901A.o
endif

ifeq ($(CONFIG_HISI_FB_3660),y)
hisifb-objs += \
	hisi_dpe_utils_hi3660.o \
	hisi_display_effect_hi3660.o \
	hisi_overlay_utils_hi3660.o \
	panel/mipi_cmi_NT35521.o\
	panel/mipi_lcd_external_panel_chicago.o
endif

hisifb-objs += \
	panel/lcdc_fake_panel.o \
	panel/mipi_fake_panel.o \
	panel/hdmi_fake_panel.o 


hisifb-objs += voltage/tps65132.o
hisifb-objs += voltage/ina231.o



EXTRA_CFLAGS += -Idrivers/video/hisi/dss \
		-Idrivers/video/hisi/panel \
		-Idrivers/video/hisi \
		-Idrivers/atfdriver \
		-Idrivers/hisi/tzdriver

clean:
	rm *.o .*cmd
