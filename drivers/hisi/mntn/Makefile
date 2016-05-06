ccflags-y += -I$(srctree)/drivers/hisi/secure_boot/inc

obj-$(CONFIG_HISILICON_PLATFORM_MAINTAIN)	+= hisilicon_platform_mntn.o
obj-$(CONFIG_HISILICON_PLATFORM_HISI_EASYSHELL)	+= hisi-easy-shell.o
obj-$(CONFIG_HISI_BOOT_TIME) += boottime.o
obj-$(CONFIG_HISI_BB) += blackbox/
obj-$(CONFIG_HISI_LOWMEM_DBG)	+= lowmem_dbg.o
ifeq ($(TARGET_VERSION_MODE),factory)
obj-$(CONFIG_HISI_VIRT_TO_PHYS) += virt_to_phys.o
endif

hisilicon_platform_mntn-y := util.o dump.o fastbootlog.o mntn_filesys.o hisi_mntn_test.o
subdir-ccflags-$(CONFIG_HISI_BB)               += -Idrivers/hisi/mntn/blackbox/
