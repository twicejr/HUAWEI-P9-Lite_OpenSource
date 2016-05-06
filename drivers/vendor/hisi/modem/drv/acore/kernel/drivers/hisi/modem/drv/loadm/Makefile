EXTRA_CFLAGS += -Idrivers/hisi/tzdriver \
		-Iscripts/dtc/libfdt

obj-y		    += load_image.o
ifeq ($(strip $(CONFIG_HISI_BALONG_MODEM)),y)
obj-y		    += loadm_phone.o
else
obj-y		    += loadm_mbb.o
endif

subdir-ccflags-y := -Werror
