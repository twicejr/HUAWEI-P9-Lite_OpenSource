###############################################################################
#
# Copyright (c) Imagination Technologies Ltd.
# 
# The contents of this file are subject to the MIT license as set out below.
# 
# Permission is hereby granted, free of charge, to any person obtaining a 
# copy of this software and associated documentation files (the "Software"), 
# to deal in the Software without restriction, including without limitation 
# the rights to use, copy, modify, merge, publish, distribute, sublicense, 
# and/or sell copies of the Software, and to permit persons to whom the 
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in 
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
# THE SOFTWARE.
# 
# Alternatively, the contents of this file may be used under the terms of the 
# GNU General Public License Version 2 ("GPL")in which case the provisions of
# GPL are applicable instead of those above. 
# 
# If you wish to allow use of your version of this file only under the terms 
# of GPL, and not to allow others to use your version of this file under the 
# terms of the MIT license, indicate your decision by deleting the provisions 
# above and replace them with the notice and other provisions required by GPL 
# as set out in the file called ?GPLHEADER? included in this distribution. If 
# you do not delete the provisions above, a recipient may use your version of 
# this file under the terms of either the MIT license or GPL.
# 
# This License is also included in this distribution in the file called 
# "MIT_COPYING".
#
###############################################################################

#
# kernel makefile template for module vdecdd
#

M ?= drivers/vcodec/imagination

KBUILD_CFLAGS := $(filter-out -Werror,$(KBUILD_CFLAGS))

ifeq ($(M),)
$(error Set $$M to a correct value to represent your path, ex. M := $$(srctree)/drivers/staging/img/)
endif

obj-y := vdecdd.o

ccflags-y += -g  -DVDEC -DUSE_SHARING -DUSE_FW_CTX_TRIMMING -DUSE_FW_RELOC_INFO_PACKING -DH264_ENABLE_MVC -DH264_SECOND_PASS_DEBLOCK -DENABLE_SEPARATE_COLOUR_PLANES -DVDEC_MSVDX_HARDWARE -D__RELEASE__="release" -D__RELEASE_RELEASE__ -DNDEBUG -DVDEC_TARGET_HISI  -DNO_REGIO_CHECK_FIELD_VALUE -D__android__ -D__linux__ -D__ANDROID__ -DANDROID -DFAKE_DEVIF -DENABLE_NULL_DEVIF -DSECURE_USE_SYSOS -DUSE_REAL_FW -DOMX_SHARED -DVDEC_USE_PVDEC -DBUFFER_SHARING -DION_BUFFERS -DVDEC_USE_PVDEC_COMPATIBILITY -D__PORT_FWRK__ -DSYSBRG_BRIDGING -DSEC_USE_REAL_FW -DUSE_MTX_DMA_LOAD -DVXD_BRIDGING -DSECURE_MEDIA_REPORTING -DSEC_USE_FW_RELOC_INFO_PACKING -DSEC_USE_FW_CTX_TRIMMING -DSECURE_TAL -DTARGET_ARM_GOLDFISH -D__TALMMU_USE_SYSAPIS__ -D__TALMMU_NO_TAL__ -DTARGET_HEADER_NAME=\"vxd_pvdec.h\" -DIMG_KERNEL_MODULE
ccflags-y +=  -I$(src)/../vdec/regdefs/pvdec/include -I$(src)/../vdec/kernel_device/libraries/null/../../include -I$(src)/../imgvideo/include -I$(src)/../imgvideo/include/linux-kernel -I$(src)/../imgvideo/system/include -I$(src)/../imgvideo/port_fwrk/include -I$(src)/../imgvideo/list_utils/include -I$(src)/../imgvideo/secure_media/target/include -I$(src)/../vdec/kernel_device/libraries/vdecdd/../../include -I$(src)/../vdec/system/vdec -I$(src)/../vdec/apis/vdec/include -I$(src)/../vdec/platform/include -I$(src)/../vdec/platform -I$(src)/../vdec/apis/vdec/libraries/include -I$(src)/../vdec/firmware/include -I$(src)/../vdec/firmware/share -I$(src)/../vdec/firmware/share/c99 -I$(src)/../imgvideo/imglib/libraries/pixelapi/include -I$(src)/../imgvideo/imglib/libraries/RegDefsUtils/include -I$(src)/../imgvideo/imglib/libraries/listman/include -I$(src)/../imgvideo/imglib/libraries/cbman/include -I$(src)/../vdec/secure_media/secure_img/libraries/bspp/include -I$(src)/../vdec/secure_media/secure_img/libraries/vxd/include -I$(src)/../vdec/secure_media/secure_img/libraries/vxd/../../../include -I$(src)/../imgvideo/kernel_comp/include -I$(src)/../vdec/secure_media/secure_mem/include -I$(src)/../vdec/secure_media/secure_mem/../include -I$(src)/../vdec/secure_media/secure_img/include -I$(src)/../imgvideo/rpc/sysbrg/src -I$(src)/../vdec/kernel_device/libraries/vdecdd/include -I$(src)/../vdec/kernel_device/libraries/vdecdd/libcomp/include -I$(src)/../vdec/firmware_pvdec -I$(src)/../imgvideo/secure_media/tal/include -I$(src)/../vdec/secure_media/secure_img/libraries/device_interface/include -I$(src)/../imgvideo/imglib/libraries/talmmu_api/include -I$(src)/../vdec/secure_media/secure_img/libraries/vxd/include/vxd -I$(src)/../vdec/firmware/bin

ifeq ($(wildcard drivers/staging/android/ion/ion.h),)
ccflags-y += -DIMG_KERNEL_ION_HEADER="<linux/ion.h>"
else
ccflags-y += -DIMG_KERNEL_ION_HEADER="<$(srctree)/drivers/staging/android/ion/ion.h>"
endif

ifneq ( ,$(findstring arm64,$(ARCH)))
ccflags-y += -fno-pic
endif
vdecdd-objs :=  kernel_device/libraries/null/code/null_device_km.o kernel_device/libraries/vdecdd/libcomp/decoder/code/decoder.o kernel_device/libraries/vdecdd/libcomp/decoder/code/hwctrl_api.o kernel_device/libraries/vdecdd/libcomp/decoder/code/translation_api.o kernel_device/libraries/vdecdd/libcomp/decoder/code/scaler_setup.o kernel_device/libraries/vdecdd/libcomp/decoder/code/dec_resources.o kernel_device/libraries/vdecdd/libcomp/decoder/code/vxd_int.o kernel_device/libraries/vdecdd/libcomp/decoder/code/pvdec_int.o kernel_device/libraries/vdecdd/libcomp/decoder/code/pvdec_msg.o kernel_device/libraries/vdecdd/libcomp/decoder/code/h264_vlc.o kernel_device/libraries/vdecdd/libcomp/decoder/code/h264_idx.o kernel_device/libraries/vdecdd/libcomp/decoder/code/mpeg4_vlc.o kernel_device/libraries/vdecdd/libcomp/decoder/code/mpeg4_idx.o kernel_device/libraries/vdecdd/libcomp/decoder/code/vp8_vlc.o kernel_device/libraries/vdecdd/libcomp/decoder/code/vp8_idx.o kernel_device/libraries/vdecdd/libcomp/decoder/code/vp6_vlc.o kernel_device/libraries/vdecdd/libcomp/decoder/code/vp6_idx.o kernel_device/libraries/vdecdd/libcomp/decoder/code/mpeg2_vlc.o kernel_device/libraries/vdecdd/libcomp/decoder/code/mpeg2_idx.o kernel_device/libraries/vdecdd/libcomp/decoder/code/vc1_vlc.o kernel_device/libraries/vdecdd/libcomp/decoder/code/vc1_idx.o kernel_device/libraries/vdecdd/code/core_api.o kernel_device/libraries/vdecdd/code/plant.o kernel_device/libraries/vdecdd/code/resource.o kernel_device/libraries/vdecdd/code/scheduler.o kernel_device/libraries/vdecdd/code/vdecdd_mmu.o kernel_device/libraries/vdecdd/code/vdecdd_km.o kernel_device/libraries/vdecdd/libcomp/vdecdd_utils/code/vdecdd_utils.o kernel_device/libraries/vdecdd/libcomp/vdecdd_utils/code/vdecdd_utils_buf.o secure_media/secure_img/libraries/vxd/code/vxd_io.o secure_media/secure_img/libraries/vxd/code/pvdec_io.o secure_media/secure_img/libraries/vxd/code/devaio.o secure_media/secure_img/libraries/device_interface/code/secdev_default.o platform/hisi/sysdev.o firmware/bin/vdecfw_bin.o ../imgvideo/rpc/sysbrg/src/vdecdd_server.o
