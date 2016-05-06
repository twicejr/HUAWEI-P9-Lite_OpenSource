
#############################################
# Building the omxvenc

LOCAL_PATH := $(call my-dir)

# Building the omxcore
include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)             \
		    $(LOCAL_PATH)/../include  \
		    $(LOCAL_PATH)/../../include

LOCAL_SRC_FILES := $(LOCAL_PATH)/drv_venc.c           \
		   $(LOCAL_PATH)/drv_omxvenc.c        \
		   $(LOCAL_PATH)/drv_omxvenc_efl.c    \
		   $(LOCAL_PATH)/drv_venc_buf_mng.c   \
		   $(LOCAL_PATH)/drv_venc_efl.c       \
		   $(LOCAL_PATH)/drv_venc_intf.c      \
		   $(LOCAL_PATH)/drv_venc_osal.c      \
		   $(LOCAL_PATH)/drv_venc_proc.c      \
		   $(LOCAL_PATH)/drv_venc_queue_mng.c \
		   $(LOCAL_PATH)/hal_venc.c

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := omxdrv

include $(BUILD_SHARED_LIBRARY)




