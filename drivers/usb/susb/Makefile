#
# Makefile for DWC_otg Highspeed USB controller driver
#

DWCPATH= drivers/usb/susb/dwc_common_port

ccflags-y	+= -DDEBUG

# Use one of the following flags to compile the software in host-only or
# device-only mode.
#CPPFLAGS        += -DDWC_HOST_ONLY
#CPPFLAGS        += -DDWC_DEVICE_ONLY

ccflags-y	+= -Dlinux -DDWC_HS_ELECT_TST
ccflags-y   += -I$(DWCPATH)
ccflags-y   += -DDWC_LINUX
ccflags-y	+= -DLM_INTERFACE

obj-y	:= dwc_otg.o
obj-y   += dwc_common_port/
dwc_otg-objs	:= dwc_otg_driver.o dwc_otg_attr.o
dwc_otg-objs	+= dwc_otg_cil.o dwc_otg_cil_intr.o 
dwc_otg-objs	+= dwc_otg_pcd_linux.o dwc_otg_pcd.o dwc_otg_pcd_intr.o
dwc_otg-objs	+= dwc_otg_hcd.o dwc_otg_hcd_linux.o dwc_otg_hcd_intr.o dwc_otg_hcd_queue.o dwc_otg_hcd_ddma.o
dwc_otg-objs	+= dwc_otg_adp.o
dwc_otg-objs	+= lm.o
dwc_otg-objs	+= dwc_otg_hicommon.o

ifneq ($(CFI),)
dwc_otg-objs	+= dwc_otg_cfi.o
endif

ifeq ($(CONFIG_HI6250_USB),y)
ccflags-y	+= -DFORCE_ID_STATE
dwc_otg-objs    += dwc_otg_hi6250.o
endif

# Must last compile this module.
dwc_otg-objs	+= hisi_usb_vbus.o
