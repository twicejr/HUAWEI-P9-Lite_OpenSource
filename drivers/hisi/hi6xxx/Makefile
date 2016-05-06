ccflags-y += -I$(srctree)/drivers/mmc/host
ccflags-y += -I$(srctree)/drivers/hisi/mntn

obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX_IOMAP)	+= hi6xxx-io.o
obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX_SOC)		+= hi6xxx-config.o
obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX_BOARDID)	+= hi6xxx-boardid.o
obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX_BOOTCMD)	+= hi6xxx-bootcmd.o
#obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX_EFUSE)	+= hi6xxx-efuse.o
#obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX_MODEM)	+= hi6xxx-modem.o
obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX_IPC)		+= hi6xxx-ipc.o
#obj-y						+= hi6xxx_loadmodem.o
obj-y						+= hi6xxx-lcd_type.o
obj-y                       += hi6xxx-memsetdev.o
obj-y                       += hi6xxx_poweroff.o
#obj-y	                    += hi6xxx-power.o
obj-y	                    += hi6xxx_sim.o
obj-$(CONFIG_HI6XXX_SR) +=hi6xxx-pm-64.o
subdir-ccflags-$(CONFIG_HISI_BB)               += -Idrivers/hisi/mntn/blackbox/
