/*!
 *****************************************************************************
 *
 * @File       bspp_km.h
 * @Title      SecureMedia BSPP KM Interface
 * @Description    This file contains the SecureMedia KM interface to BSPP
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

#if !defined (__BSPP_KM_H__)
#define __BSPP_KM_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_include.h"
#include "bspp.h"
#include "secure_defs.h"

#ifdef SECURE_MEDIA_SUPPORT
	#include "secureapi.h"
#endif

/*! Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

#ifdef  __RPCCODEGEN__
  #define rpc_prefix      BSPP_KM
  #define rpc_filename    bspp_km
#endif


//Wrapper structures for BSPP calls through SecureMedia api
typedef struct
{
	//Input
    VDEC_sStrConfigData   * psStrConfigData;
	BSPP_sDdBufArrayInfo  * psFWSequence;
    BSPP_sDdBufArrayInfo  * psFWPPS;    
	
    //Output
    IMG_HANDLE            * phStrContext;

} BSPP_SECURE_sStreamCreateArgs;

typedef struct
{
	//Input
	IMG_HANDLE                  hStrContext;
    const VDEC_sCodecConfig   * psCodecConfig;

} BSPP_SECURE_sSetCodecConfigArgs;

typedef struct
{
	//Input
    IMG_HANDLE            hStrContext;

} BSPP_SECURE_sStreamDestroyArgs;

typedef struct
{
	//Input
	IMG_HANDLE              hStrContext;
    IMG_UINT32              ui32SequHdrId;
    IMG_UINT32              ui32PPSId;
    IMG_UINT32              ui32SecondPPSId;

} BSPP_SECURE_sSubmitPictureDecodedArgs;

typedef struct
{
	//Input
	IMG_HANDLE                  hStrContext;
    const BSPP_sDdBufInfo     * psDdBufInfo;
	IMG_UINT32                  ui32BufMapId;
    IMG_UINT32                  ui32DataSize;
    VDEC_eBstrElementType       eBstrElementType;
    IMG_VOID                  * pvPictTagParam;

} BSPP_SECURE_sStreamSubmitBufferArgs;

typedef struct
{
	//Input
	IMG_HANDLE              hStrContext;
    LST_T                 * psSegments;
    const BSPP_sDdBufInfo * psContiguousBufInfo;
    IMG_UINT32              ui32ContiguousBufMapId;
	//Output
    BSPP_sPreParsedData   * psPreParsedData;

} BSPP_SECURE_sStreamPreParseBuffersArgs;

/*!
******************************************************************************

 @Function              BSPP_SecureStreamCreate

******************************************************************************/
IMG_RESULT BSPP_SecureStreamCreate(
    const VDEC_sStrConfigData __user * psStrConfigData,
    IMG_HANDLE  __user               * phStrContext,
    BSPP_sDdBufArrayInfo __user      * asFWSequence,
    BSPP_sDdBufArrayInfo __user      * asFWPPS,
	SECURE_HANDLE                      hSecBSPPHandle
);

/*!
******************************************************************************

 @Function              BSPP_SecureSetCodecConfig

******************************************************************************/
IMG_RESULT BSPP_SecureSetCodecConfig(
    IMG_HANDLE                          hStrContext,
    const VDEC_sCodecConfig  __user   * psCodecConfig,
	SECURE_HANDLE                       hSecBSPPHandle
);
/*!
******************************************************************************

 @Function              BSPP_SecureStreamDestroy

******************************************************************************/
IMG_RESULT BSPP_SecureStreamDestroy(
    IMG_HANDLE            hStrContext,
	SECURE_HANDLE         hSecBSPPHandle
);
/*!
******************************************************************************

 @Function              BSPP_SecureStreamSubmitBuffer

******************************************************************************/
IMG_RESULT BSPP_SecureStreamSubmitBuffer(
    IMG_HANDLE                   hStrContext,
    IMG_UINT32                   ui32BufMapId,
    IMG_UINT32                   ui32DataSize,
    VDEC_eBstrElementType        eBstrElementType,
    IMG_VOID                   * pvPictTagParam,
    SECURE_HANDLE                hSecBSPPHandle
);
/*!
******************************************************************************

 @Function              BSPP_SecureSubmitPictureDecoded

 @Description

******************************************************************************/
IMG_RESULT
BSPP_SecureSubmitPictureDecoded(
    IMG_HANDLE              hStrContext,
    IMG_UINT32              ui32SequHdrId,
    IMG_UINT32              ui32PPSId,
    IMG_UINT32              ui32SecondPPSId,
	SECURE_HANDLE           hSecBSPPHandle
);
/*!
******************************************************************************

 @Function              BSPP_SecureStreamPreParseBuffers

 @Description

******************************************************************************/
IMG_RESULT BSPP_SecureStreamPreParseBuffers(
    IMG_HANDLE                      hStrContext,
    IMG_UINT32                      ui32NumOfSegs,
    BSPP_sPreParsedData __user    * psPreParsedData,
    SECURE_HANDLE                   hSecBSPPHandle,
    IMG_UINT32                      ui32ContiguousBufMapId,
    LST_T __user                  * psSegmentList
);

#if defined(__cplusplus)
}
#endif

#endif /* __BSPP_KM_H__ */



