# Add your debugging flag (or not) to CFLAGS
EXTRA_CFLAGS += -fno-pic
EXTRA_CFLAGS += -Idrivers/vcodec/hi_vcodec/venc/drv/include
EXTRA_CFLAGS += -Idrivers/vcodec/hi_vcodec/venc/include
EXTRA_CFLAGS += -Idrivers/vcodec/hi_vcodec/venc/drv/venc

obj-$(CONFIG_HI_VCODEC) += hi_omxvenc.o
hi_omxvenc-objs :=  venc_regulator.o     \
                    drv_venc_intf.o      \
                    drv_venc_efl.o       \
                    drv_venc_osal.o      \
                    drv_venc.o           \
                    drv_omxvenc.o        \
                    drv_omxvenc_efl.o    \
                    drv_venc_buf_mng.o   \
                    drv_venc_queue_mng.o \
                    drv_venc_proc.o      \
                    hal_venc.o           \
                    hi_drv_mem.o


#obj-m += venc.o
#venc-y :=           venc_regulator.o     \
                    drv_venc_intf.o      \
                    drv_venc_efl.o       \
                    drv_venc_osal.o      \
                    drv_venc.o           \
                    drv_omxvenc.o        \
                    drv_omxvenc_efl.o    \
                    drv_venc_buf_mng.o   \
                    drv_venc_queue_mng.o \
                    drv_venc_proc.o      \
                    hal_venc.o           \
                    hi_drv_mem.o

