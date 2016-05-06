
TOP      := drivers/../..
VFMW_DIR := drivers/vcodec/hi_vcodec/vdec/vfmw
 
include $(VFMW_DIR)/vfmw_v4.0/firmware/product/HiVCodecV100/NOR_CFG/vfmw_make.cfg

EXTRA_CFLAGS += -Idrivers/vcodec/hi_vcodec/vdec/include
EXTRA_CFLAGS += $(VFMW_CFLAGS) -fno-pic

#build in
obj-$(CONFIG_HI_VCODEC) += hi_vfmw.o
hi_vfmw-objs := $(VFMW_CFILES)

#module
#obj-m += hi_vfmw.o
#hi_vfmw-y := $(VFMW_CFILES)
