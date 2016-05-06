/*!
 *****************************************************************************
 *
 * @File       pvdec_ext_reg.h
 * @Title      Low-level PVDEC interface component
 * @Description    This file contains the interface to communicate with an PVDEC core.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#if !defined (__PVDEC_EXT_REG_H__)
#define __PVDEC_EXT_REG_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_include.h"
#ifdef SECURE_MEDIA_SUPPORT
    #include "secure_defs.h"
    #include "secureapi.h"
#endif

#ifdef SECURE_MEDIA_SUPPORT
    //Using Secure Interface
    #define PVDECIO_WritePipeRegisterXX(h, m, o, v, p)  \
    {                                                   \
        WRITENREGS  sWriteReg;                          \
                                                        \
        sWriteReg.ui32Offset = o;                       \
        sWriteReg.ui32Value = v;                        \
        sWriteReg.ui32ValidMask = -1;                   \
        sWriteReg.ui8Pipe = p;                          \
                                                        \
        SECURE_WriteNRegs(h, 1, m, &sWriteReg);\
    }

    static IMG_UINT32 PVDECIO_ReadPipeRegisterXX(
        IMG_HANDLE          hSecure,
        IMG_UINT32          ui32MemRegion,
        IMG_UINT32          ui32Offset,
        IMG_UINT8           ui8Pipe
    )
    {
        READNREGS  sReadReg;

        sReadReg.ui32Offset = ui32Offset;
        sReadReg.ui8Pipe = ui8Pipe;

        //printf("PVDECIO_ReadRegisterX hSecure = 0x%08x\n",hSecure);
        SECURE_ReadNRegs(hSecure, 1, ui32MemRegion, &sReadReg);

        return sReadReg.ui32Result;
    }

    #define PVDECIO_WriteRegisterX(h, r, o, v)              PVDECIO_WritePipeRegisterXX(h->hDev, r, o, v, 0)
    #define PVDECIO_ReadRegisterX(h, r, o)                  PVDECIO_ReadPipeRegisterXX(h->hDev, r, o, 0)
    #define PVDECIO_WritePipeRegisterX(h, p, r, o, v)       PVDECIO_WritePipeRegisterXX(h->hDev, r, o, v, p)
    #define PVDECIO_ReadPipeRegisterX(h, p, r, o)           PVDECIO_ReadPipeRegisterXX(h->hDev, r, o, p)
#else

    #define PVDECIO_WriteRegisterX(h, r, o, v)              VXDIO_WriteRegister(h->hDev, r, o, v, -1, 0)
    #define PVDECIO_ReadRegisterX(h, r, o)                  VXDIO_ReadRegister(h->hDev, r, o, 0)
    #define PVDECIO_WritePipeRegisterX(h, p, r, o, v)       VXDIO_WriteRegister(h->hDev, r, o, v, -1, p)
    #define PVDECIO_ReadPipeRegisterX(h, p, r, o)           VXDIO_ReadRegister(h->hDev, r, o, p)

#endif


#define PVDEC_PIXEL_WritePipeRegister(h, p, o, v)            PVDECIO_WritePipeRegisterX(h, p, REGION_PVDEC_PIXEL_PIPE_REGSPACE, o, v)
#define PVDEC_PIXEL_ReadPipeRegister(h, p, o)                PVDECIO_ReadPipeRegisterX(h, p, REGION_PVDEC_PIXEL_PIPE_REGSPACE, o)

#define PVDEC_ENTROPY_WritePipeRegister(h, p, o, v)          PVDECIO_WritePipeRegisterX(h, p, REGION_PVDEC_ENTROPY_PIPE_REGSPACE, o, v)
#define PVDEC_ENTROPY_ReadPipeRegister(h, p, o)              PVDECIO_ReadPipeRegisterX(h, p, REGION_PVDEC_ENTROPY_PIPE_REGSPACE, o)

#define PVDEC_CORE_WriteRegister(h, o, v)                    PVDECIO_WriteRegisterX(h, REGION_PVDEC_CORE_REGSPACE, o, v)
#define PVDEC_CORE_ReadRegister(h, o)                        PVDECIO_ReadRegisterX(h, REGION_PVDEC_CORE_REGSPACE, o)

#define IMG_VIDEO_BUS4_MMU_WriteRegister(h, o, v)            PVDECIO_WriteRegisterX(h, REGION_IMG_VIDEO_BUS4_MMU_REGSPACE, o, v)
#define IMG_VIDEO_BUS4_MMU_ReadRegister(h, o)                PVDECIO_ReadRegisterX(h, REGION_IMG_VIDEO_BUS4_MMU_REGSPACE, o)

#define PVDEC_VLR_WriteRegister(h, o, v)                     PVDECIO_WriteRegisterX(h, REGION_PVDEC_VLR_REGSPACE, o, v)
#define PVDEC_VLR_ReadRegister(h, o)                         PVDECIO_ReadRegisterX(h, REGION_PVDEC_VLR_REGSPACE, o)

#define MTX_CORE_WriteRegister(m, o, v)                      PVDECIO_WriteRegisterX(m, REGION_PVDEC_MTX_CORE_REGSPACE, o, v)
#define MTX_CORE_ReadRegister(m, o)                          PVDECIO_ReadRegisterX(m, REGION_PVDEC_MTX_CORE_REGSPACE, o)

#define PVDEC_TEST_WriteRegister(h, o, v)                    PVDECIO_WriteRegisterX(h, REGION_PVDEC_TEST_REGSPACE, o, v)

#if defined(__cplusplus)
}
#endif

#endif /* __PVDEC_EXT_REG_H__ */



