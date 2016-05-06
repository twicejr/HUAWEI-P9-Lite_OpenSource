EXTRA_CFLAGS += -I$(srctree)/drivers/hisi/hifi_mailbox/ipcm

EXTRA_CFLAGS += -DBSP_CORE_APP
ifdef CONFIG_HIFI_RESET
EXTRA_CFLAGS += -D_HIFI_WD_DEBUG
endif

EXTRA_CFLAGS += -Idrivers/hisi/hifidsp

obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_table.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_gut.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_ifc.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_msg.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_debug.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_port_linux.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox_ifc.o
obj-$(CONFIG_HIFI_MAILBOX)	+= drv_mailbox.o
