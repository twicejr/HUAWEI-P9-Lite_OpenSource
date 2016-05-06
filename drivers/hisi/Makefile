obj-$(CONFIG_HISILICON_PLATFORM_ADC) += adc/
obj-$(CONFIG_HISILICON_PLATFORM_MISC) += misc/
obj-$(CONFIG_HISILICON_PLATFORM_HI6XXX)	+= hi6xxx/
obj-$(CONFIG_HISILICON_PLATFORM_DDRC)	+= ddrc/
obj-$(CONFIG_HI6402_CODEC) += hi64xx/
obj-$(CONFIG_HI6403_CODEC) += hi64xx/
obj-y += efuse/
obj-y += mntn/

obj-y	+= hifidsp/
obj-y	+= soundtrigger/
obj-$(CONFIG_HIFI_MAILBOX)					+= hifi_mailbox/

obj-$(CONFIG_HISILICON_PLATFORM_MAILBOX)	+= mailbox/
obj-$(CONFIG_HISILICON_PLATFORM_MAINTAIN) += mntn/
obj-$(CONFIG_HISILICON_PLATFORM_KERNELDUMP) += memory_dump/
obj-$(CONFIG_HISILICON_PLATFORM_MUTEX_SERVICE)	+= mutex_service/
obj-$(CONFIG_HISI_NOC)	+= noc/
obj-$(CONFIG_HISILICON_PLATFORM_POWER_CONTROL)	+= pm/
obj-$(CONFIG_HISI_PERF_STAT)+= perf_stat/
obj-$(CONFIG_HISI_PERF_STAT64)+= perf_stat/
obj-$(CONFIG_HISI_AXI)+= axi/
obj-$(CONFIG_HISI_SOCP) += socp/
obj-$(CONFIG_HISILICON_PLATFORM_TELE_MNTN) += tele_mntn/
obj-y += mcushell/
obj-$(CONFIG_HISILICON_PLATFORM_USB)	+= usb/
obj-$(CONFIG_HISILICON_FREQDUMP)	+= freqdump/
obj-$(CONFIG_HISILICON_PLATFORM_HI3XXX)	+= hi3xxx/
ifeq ($(findstring hi6210, $(OBB_PRODUCT_NAME) ),)
obj-$(CONFIG_HISILICON_PLATFORM_SLIMBUS)+= slimbus/
endif
obj-$(CONFIG_HI6421_SPK) += hi6421_spk/
obj-$(CONFIG_HI6402_HIFI_MISC) += hi6402dsp/
obj-$(CONFIG_SUSPEND) += pm_common/
obj-$(CONFIG_HISI_HMPTH_SET) += hmpthresholds/
obj-$(CONFIG_HISI_BALONG_MODEM) += modem/
obj-$(CONFIG_HISI_FPGA_TS) += fpga_touchscreen/

ifneq ($(strip $(CFG_HISI_OPENSOURCE)), true)
obj-y += watchpoint/
endif
ifeq ($(TARGET_VERSION_MODE),factory)
obj-$(CONFIG_HISI_EXMBIST) += exmbist/
endif

obj-$(CONFIG_HISI_FLP)   += flp/

ifeq ($(TARGET_VERSION_MODE),factory)
CFLAGS_KERNEL   += -DCONFIG_FACTORY_MODE
endif


obj-$(CONFIG_HISI_IVP) += ivp/
obj-$(CONFIG_LOAD_IMAGE) += load_image/

obj-$(CONFIG_HISI_HILOG) += hilog/

#obj-$(CONFIG_HI3650_PMU_DUMP) += hiperfdump/
obj-$(CONFIG_HISI_PERFHUB) += perfhub/
ifneq ($(strip $(CFG_HISI_OPENSOURCE)), true)
obj-$(CONFIG_TZDRIVER)          += tzdriver/
endif
obj-$(CONFIG_HISI_CCI_EXTRA) += cci_extra/
