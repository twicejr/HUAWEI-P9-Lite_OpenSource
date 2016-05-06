KBUILD_CPPFLAGS +=	-Idrivers/hisi/modem/drv/om/common \
                    -Idrivers/hisi/modem/drv/om/dump \
                    -Idrivers/hisi/modem/drv/om/oms\
                    -Idrivers/hisi/modem/drv/om/log \
                    -Idrivers/hisi/modem/drv/om/sys_view \
		    -Idrivers/modem/drv/om/usbtrace

obj-$(CONFIG_HW_IP_BASE_ADDR)	+= hwadp_balong.o hwadp_core.o hwadp_debug.o

subdir-ccflags-y := -Werror