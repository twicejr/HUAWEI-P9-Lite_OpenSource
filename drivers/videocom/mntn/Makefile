ifneq ($(filter hi6210sft, $(TARGET_BOARD_PLATFORM)),)
subdir-ccflags-y   			+= -I$(srctree)/drivers/hisi/modem_hi6xxx/include/med/
endif

EXTRA_CFLAGS += -fno-pic
obj-$(CONFIG_MEDIA_VIDEO_MNTN) += media_mntn_kernel.o

obj-$(CONFIG_MEDIA_VIDEO_MNTN) += mntn_log_debugfs.o \
         video_mntn_kernel.o
obj-$(CONFIG_MEDIA_VIDEO_MNTN) += media_mntn_sys_crash.o                                                            
