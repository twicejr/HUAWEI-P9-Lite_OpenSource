#
# Makefile for Hisilicon HI3630FPGA line
#
ccflags-$(CONFIG_ARCH_MULTIPLATFORM) := -I$(srctree)/$(src)/include

obj-$(CONFIG_LOCAL_TIMERS)	     += hi6xxx_localtimer.o

obj-$(CONFIG_HI6421_OCP)	+= hisi_hi6421_ocp.o
obj-$(CONFIG_HISI_MAILBOX)	+= hisi_mailbox.o
obj-$(CONFIG_HISI_LPM3)		+= hisi_lowpowerm3.o

obj-$(CONFIG_HISI_UDP_BOARDID)		+= hisi_udp_board_id.o

ifeq ($(CONFIG_SECURE_EXTENSION), y)
obj-$(CONFIG_ARM_PSCI)          += hisi_pm_psci.o
else
obj-$(CONFIG_HI3630_LPM3_IPC)	+= hisi_ipc.o
#obj-$(CONFIG_SMP)		+= hisi_pm.o hisi_pm_setup.o
endif
ifeq ($(CONFIG_TZDRIVER), y)
EXTRA_CFLAGS += -Idrivers/hisi/tzdriver
endif

obj-$(CONFIG_HISI_SR_DEBUG) += hisi_lpregs.o
