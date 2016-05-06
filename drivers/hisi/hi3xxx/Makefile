EXTRA_CFLAGS 	+= -Idrivers/hisi/mntn/blackbox/platform_lpm3

obj-$(CONFIG_HI3XXX_IRQ_AFFINITY)			+= hi3xxx_irq_affinity.o
obj-$(CONFIG_HI3XXX_IRQ_AFFINITY_DEBUGFS)	+= irq_affinity_debugfs.o
obj-$(CONFIG_HI3XXX_POWER_OFF)				+= hi3xxx_poweroff.o
obj-$(CONFIG_HI3XXX_CMDLINE_PARSE)  += hi3xxx_cmdline_parse.o
obj-$(CONFIG_HISI_SR)    += pm.o
obj-$(CONFIG_HISI_SR_DEBUG) 				+= hisi_lpregs.o
obj-$(CONFIG_HISI_LPM3_DEBUG)		+= hisi_lpm3_debug.o
obj-$(CONFIG_HI3XXX_MODEM_ETB)		+= hi3xxx_modem_etb.o
obj-$(CONFIG_HISI_BOOST5V_CONTROL)  += hisi_boost5v_control.o
obj-$(CONFIG_HISI_HISEE)  += hisee.o
subdir-ccflags-$(CONFIG_HISI_BB)		+= -Idrivers/hisi/mntn/blackbox/

