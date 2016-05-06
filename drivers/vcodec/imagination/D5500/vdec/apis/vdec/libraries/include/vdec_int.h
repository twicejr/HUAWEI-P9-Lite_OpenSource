/*!
 *****************************************************************************
 *
 * @File       vdec_int.h
 * @Title      VDEC Internal Structures etc.
 * @Description    This file contains the VXD High-Level Decode API internal
 *  structure etc.
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

#ifndef __VDEC_INT_H__
#define __VDEC_INT_H__

#include "img_defs.h"
#include "vdec_api.h"
#include "vdec_params.h"
#include "lst.h"
#include "img_profiles_levels.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VDEC_STREAM_TYPE_ID    (0xA0A00001)    /*!< RMAN type for streams.            */
#define VDEC_BUFMAP_TYPE_ID    (0xA0A00002)    /*!< RMAN type for buffer mappings.    */

/*!
******************************************************************************
 This type defines the stream state.
 @brief  VDEC Stream State
******************************************************************************/
typedef enum
{
    VDEC_STRSTATE_STOPPED = 0x00,  /*!< Stream stopped.     */
    VDEC_STRSTATE_PLAYING,         /*!< Stream playing.     */
    VDEC_STRSTATE_STOPPING,        /*!< Stream stopping.    */

    VDEC_STRSTATE_MAX,             /*!< Max. stream state.  */

} VDEC_eStrState;


/*!
******************************************************************************
 This structure contains the stream context.
 @brief  VDEC Stream Context
 ******************************************************************************/
typedef struct
{
    IMG_UINT32             ui32StrId;            /*!< VDECDD stream id.                                      */

    IMG_HANDLE              hStrAccessMutex;                /*!< API access mutex.                                      */

    VDEC_sStrConfigData     sStrConfigData;                 /*!< Stream config data.                                    */
    VDEC_pfnEventCallback   pfnEventCallback;               /*!< Pointer to the stream callback function.               */
    IMG_VOID *              pvStrCbParam;                   /*!< Callback client defined stream data                    */

    VDEC_eStrState          eStrState;                      /*!< Stream state.                                          */

    IMG_HANDLE              hBsppContext;                   /*!< BSPP context handle.                                   */
    IMG_UINT32              ui32NumBufsInGroup;             /*!< Number of buffers in group to be pre-parsed.           */    
    IMG_UINT32              ui32TotalSizeBufsInGroup;       /*!< Total size of buffers in group to be pre-parsed.       */ 
    IMG_UINT32              ui32MaxNumBstrBuf;              /*!< Maximum number of bitstream buffers in use.            */
 
    IMG_HANDLE              hCbTask;                        /*!< Callback task control block.                           */
    IMG_HANDLE              hCbTaskActiveEvent;             /*!< Callback task active.                                  */
    IMG_BOOL                bCbShutdown;                    /*!< IMG_TRUE when shutting down.                           */

    LST_T                   sBufMapList;                    /*!< List of buffer map structures. See #VDEC_sBufMapInfo.  */

    LST_T                   sDefragFreeBstrBufList;         /*!< List of Free Defragmented bitstream buffers - belongs to 
                                                                 vdec_api, used for VP8, still mapped in sBufMapList    */

    LST_T                   sDefragUsedBstrBufList;         /*!< List of Free Defragmented bitstream buffers - belongs to 
                                                                 vdec_api, used for VP8, still mapped in sBufMapList    */
#ifdef TEST_ONE_DEVICE_ALLOC_SPS
    VDEC_sBufArrayInfo      sFWSequence;                    /*!< Array of Sequence buffers.                             */
#else
    VDEC_sBufArrayInfo      asFWSequence[MAX_SEQUENCES];    /*!< Array of Sequence buffers.                             */
#endif

#ifdef TEST_ONE_DEVICE_ALLOC_PPS
    VDEC_sBufArrayInfo      sFWPPS;                          /*!< Array of PPS buffers.                                  */
#else   
	VDEC_sBufArrayInfo      asFWPPS[MAX_PPSS];              /*!< Array of PPS buffers.                                  */
#endif

} VDEC_sStrContext;


/*!
******************************************************************************
 This structure contains the map information.
 @brief  Map Information
 ******************************************************************************/
typedef struct
{
    SYSBRG_POINTER(IMG_VOID, lst_padding);                 /*!< Reserved space for LST_LINK link  (allows the structure to be part of a LST).*/

    IMG_UINT32          ui32BufMapId;  /*!< The map Id.                                  */
    SYSBRG_UPOINTER(VDEC_sStrContext, psStrContext);       /*!< Pointer to the stream context.               */
    SYSBRG_UPOINTER(IMG_VOID, pvBufCbParam);                 /*!< A pointer to client specific data.           */
    VDEC_eBufType       eBufType;      /*!< Buffer type mapped.                          */
    SYSBRG_HANDLE(hResHandle);                               /*!< Resource handle for this mapping.            */
    VDEC_sBufInfo *     psBufInfo;     /*!< Pointer to client #VDEC_sBufInfo structure.  */

} VDEC_sBufMapInfo;

/*!
******************************************************************************
 This structure contains information relating to a defragmented buffer.
 @brief  Buffer Information
******************************************************************************/
typedef struct
{
    LST_LINK;            /*!< List link (allows the structure to be part of a MeOS list). */

    VDEC_sBufInfo*       psBufInfo;      /*!< Buffer info.         */

} VDEC_sDefragmentedBufInfo;

/*!
******************************************************************************
 This structure contains the memory allocation information.
 @brief  Memory Allocation Information
 ******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32ConnId;       /*!< VDECDD Connection id.              */
    IMG_UINT32  ui32AttachId;     /*!< PALLOC Attachment id.              */
    IMG_UINT32  ui32AllocId;      /*!< The allocation Id.                 */
    IMG_VOID *  pvCpuLinearAddr;  /*!< CPU linear address of the buffer.  */

} VDECEXT_sMallocInfo;


#ifdef __cplusplus
}
#endif

#endif /* __VDEC_INT_H__   */


