ifeq ($(CONFIG_HIFI_MAILBOX), y)
EXTRA_CFLAGS += -I$(srctree)/drivers/hisi/hifi_mailbox/mailbox
EXTRA_CFLAGS += -I$(srctree)/drivers/hisi/hifi_mailbox/ipcm
EXTRA_CFLAGS += -I$(srctree)/drivers/hisi/hifidsp
endif

ifeq ($(CONFIG_HIFI_IPC_3660),y)
EXTRA_CFLAGS += -DHIFI_TCM_208K
endif

EXTRA_CFLAGS +=	-Idrivers/hisi/slimbus/
# HI3630 Platform Support
snd-soc-hi3630-objs := hi3630_sio.o hi6210_pcm.o hi3630_srcup_dsp.o hi3630_asp_common.o hi3630_srcdown.o hi3630_fake_fm.o hi3630_fake_sio.o
snd-soc-hi3650-objs := hi6210_pcm.o hi3630_asp_common.o hi3xxx_asp_dma.o slimbus_dai.o
snd-soc-hi3660-objs := hi6210_pcm.o hi3630_asp_common.o hi3xxx_asp_dma.o slimbus_dai.o

ifeq ($(CONFIG_HDMI_K3), y)
snd-soc-hi3630-objs += hi3630_pcm_hdmi.o hi3630_hdmi_i2s.o
endif
obj-$(CONFIG_SND_SOC_PCM_HI3630) += snd-soc-hi3630.o
obj-$(CONFIG_SND_SOC_PCM_HI3650) += snd-soc-hi3650.o
obj-$(CONFIG_SND_SOC_PCM_HI3660) += snd-soc-hi3660.o



# HI3630-HI6401 Machine Support
snd-soc-hi3630-hi6401-objs := hi3630_hi6401.o

# HI6210 Platform Support
snd-soc-hi6210-objs := hi6210_pcm.o
# HI6210-HISSC Machine Support
snd-soc-hi6210-hissc-objs := hi6210_hissc.o
obj-$(CONFIG_SND_HI3630_HI6401) += snd-soc-hi3630-hi6401.o
obj-$(CONFIG_SND_SOC_PCM_HI6210) += snd-soc-hi6210.o
obj-$(CONFIG_SND_HI6210_HISSC) += snd-soc-hi6210-hissc.o
# HI3630-HI6402 Machine Support
snd-soc-hi3630-hi6402-objs := hi3630_hi6402.o
# HI6250-HI6402 Machine Support
snd-soc-hi6250-hi6402-objs += hi6250_hi6402.o
# HI6250-HI6555c Machine Support
snd-soc-hi6250-hi6555c-objs += hi6250_hi6555c.o
# HI3650-HI6402 Machine Support
snd-soc-hi3650-hi6402-objs := hi3650_hi6402.o
# HI3650-HI6403 Machine Support
snd-soc-hi3650-hi6403-objs := hi3650_hi6403.o

# HI3660-HI6402 Machine Support
snd-soc-hi3660-hi6402-objs := hi3660_hi6402.o
# HI3660-HI6403 Machine Support
snd-soc-hi3660-hi6403-objs := hi3660_hi6403.o

obj-$(CONFIG_SND_HI3630_HI6402) += snd-soc-hi3630-hi6402.o
obj-$(CONFIG_SND_HI3650_HI6402) += snd-soc-hi3650-hi6402.o
obj-$(CONFIG_SND_HI3650_HI6403) += snd-soc-hi3650-hi6403.o
obj-$(CONFIG_SND_HI6250_HI6555C) +=snd-soc-hi6250-hi6555c.o
obj-$(CONFIG_SND_HI6250_HI6402) += snd-soc-hi6250-hi6402.o
obj-$(CONFIG_SND_HI3660_HI6402) += snd-soc-hi3660-hi6402.o
obj-$(CONFIG_SND_HI3660_HI6403) += snd-soc-hi3660-hi6403.o
obj-$(CONFIG_SND_AUTO_TEST) += auto_test/
