ccflags-$(CONFIG_HI6XXX_EFUSE) += -I$(srctree)/drivers/hisi/ipc_hi6xxx
obj-$(CONFIG_HI6XXX_EFUSE)  += hisi_efuse.o
obj-$(CONFIG_HI3XXX_EFUSE)	+= hisi_efuse.o
ifeq ($(CONFIG_ATFDRIVER), y)
EXTRA_CFLAGS += -Idrivers/atfdriver
endif
