#
# Makefile for DWC_common library
#

EXTRA_CFLAGS	+= -DDWC_LINUX
EXTRA_CFLAGS	+= -DDEBUG
#EXTRA_CFLAGS	+= -DDWC_DEBUG_REGS
#EXTRA_CFLAGS	+= -DDWC_DEBUG_MEMORY

EXTRA_CFLAGS	+= -DDWC_LIBMODULE
EXTRA_CFLAGS	+= -DDWC_CCLIB
#ccflags-y	+= -DDWC_CRYPTOLIB
EXTRA_CFLAGS	+= -DDWC_NOTIFYLIB
EXTRA_CFLAGS	+= -DDWC_UTFLIB

obj-y			 := dwc_common_port_lib.o
dwc_common_port_lib-y := dwc_cc.o
#dwc_common_port_lib-y +=  dwc_modpow.o
dwc_common_port_lib-y += dwc_dh.o
#dwc_common_port_lib-y += dwc_crypto.o
dwc_common_port_lib-y += dwc_notifier.o
dwc_common_port_lib-y += dwc_common_linux.o
dwc_common_port_lib-y += dwc_mem.o

clean:
	rm -rf *.o *.ko .*.cmd *.mod.c .*.o.d .*.o.tmp modules.order Module.markers Module.symvers .tmp_versions/
