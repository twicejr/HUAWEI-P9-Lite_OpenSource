obj-y += dev_wifi.o

ifneq ($(CONFIG_BCM4334),)
ccflags-y += -DHW_SOFTAP_THROUGHPUT_OPTIMIZE
endif

ifneq ($(CONFIG_BCM43455),)
ccflags-y += -DHW_SOFTAP_THROUGHPUT_OPTIMIZE
endif
