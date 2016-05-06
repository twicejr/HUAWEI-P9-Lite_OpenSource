obj-$(CONFIG_HI3xxx_CLK_CORE)		+= clk-hi3xxx.o clk-hi3716.o
obj-$(CONFIG_HI3620_CLK_MIPI_DSI)	+= clk-hi3620-dsi.o
ifeq ($(CONFIG_HISI_CLK_HI3660),y)
obj-y		+= clk-kirin.o
else
obj-y		+= clk-hi3xxx.o
endif
obj-$(CONFIG_HISI_CLK_MAILBOX_SUPPORT)	+= hisi-clk-mailbox.o
