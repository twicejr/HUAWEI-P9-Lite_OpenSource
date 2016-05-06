/*!
 *****************************************************************************
 *
 * @File       scheduler.c
 * @Title      VDECDD Scheduler.
 * @Description    This file contains the implementation of the VDECDD Scheduler
 *  component.
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

#include "vdecdd.h"
#include "core_api.h"
#include "rman_api.h"
#include "dman_api_km.h"
#include "dbgopt_api_km.h"

#include "resource.h"
#include "scheduler.h"
#include "report_api.h"

#include "img_errors.h"

#include "lst.h"
#include "dq.h"

/*****************************************************************************
 * LOCAL DEFINES
 *****************************************************************************/
#define IS_DECODING(ePlayMode, eDecodeLevel)   (ePlayMode == VDEC_PLAYMODE_NORMAL_DECODE && eDecodeLevel > VDECDD_DECODELEVEL_SCHEDULER)


/*****************************************************************************
 * LOCAL TYPES
 *****************************************************************************/

/*!
******************************************************************************
 This structure contains the Scheduler Context.
 @brief  Scheduler Context
******************************************************************************/
typedef struct scheduler_sContext_tag
{
    IMG_BOOL                bInitialised;        /*!< Indicates whether component is initialised.           */
    IMG_VOID *              pvCompInitUserData;  /*!< Callback user data from component.                    */
    VDECDD_pfnCompCallback  pfnCompCallback;     /*!< Callback from component to return output.             */
    VDECDD_eDecodeLevel     eDecodeLevel;        /*!< Level in system to which decoding should take place.  */
    IMG_BOOL                bAPM;                /*!< We want to do APM                                     */

    LST_T                   sStrCtxList;         /*!< List of stream contexts.                              */

    IMG_HANDLE              hDecCtx;             /*!< Decoder context handle.                               */

} scheduler_sContext;


/*!
******************************************************************************
 This enum lists scopes of errors that can be reported.
 @brief  Error Scope
******************************************************************************/
typedef enum
{
    ERROR_SCOPE_IGNORE = 0,
    ERROR_SCOPE_SEQUENCE,
    ERROR_SCOPE_PICTURE,
    ERROR_SCOPE_OTHER

} scheduler_eErrScope;


/*!
******************************************************************************
 This structure describes behaviour expected when error is encountered
 and its scope.
 @brief  Stream Unit Error Descriptor
******************************************************************************/
typedef struct
{
    IMG_BOOL             bStop;
    scheduler_eErrScope  eErrScope;

} scheduler_sStrUnitErrorDesc;


/*!
******************************************************************************
 This structure contains the Scheduler Stream Context.
 @brief  Scheduler Stream Context
******************************************************************************/
typedef struct scheduler_sStreamCtx_tag
{
    LST_LINK;             /*!< List link (allows the structure to be part of a MeOS list).                            */

    scheduler_sContext *  psSchCtx;             /*!< Scheduler context.                                               */

    VDEC_sStrConfigData   sStreamConfig;        /*!< Stream configuration.                                            */
    IMG_VOID *            pvStreamUserData;     /*!< User data for this stream.                                       */

    VDECDD_sSchStrStatus  sSchStatus;           /*!< Scheduler status.                                                */

    LST_T                 sPictBufferList;      /*!< List of picture buffers.                                         */
    LST_T                 sPictResList;         /*!< List of auxiliary picture resources.                             */
    LST_T                 sSequHdrList;         /*!< List of sequence header information.                             */
    LST_T                 sStrUnitList;         /*!< Queue of stream units to be processed.                           */

    VDEC_ePlayMode        ePlayMode;            /*!<                                                                  */
    VDEC_eStopPoint       eCurrentStopPoint;    /*!< Current stop point for this stream.                              */
    VDEC_sStopInfo        sStopInfo;            /*!< Current status of stop flags (see #VDEC_eStopFlags)
                                                     plus error info.                                                 */
    IMG_UINT32            ui32ActiveStopFlags;  /*!< Active status flags to trigger stop.                             */
    IMG_BOOL              bStopped;             /*!< Scheduler is stopped and does not schedule any coded pictures.   */
    IMG_BOOL              bDecode;              /*!< Stream units are decoded and not skipped.                        */

    VDEC_sComSequHdrInfo  sComSequHdrInfo;      /*!< Latest sequence header information.                              */

    IMG_BOOL              bOutputConfigSet;
    VDECDD_sDdPictBuf     sDispPictBuf;         /*!< Picture buffer layout to use for decoding.                       */
    VDEC_sStrOutputConfig sOutputConfig;        /*!< Output configuration to use for decoding.                        */

    // state that needs to be reviewed.
    IMG_BOOL              bNewSequence;         /*!< New sequence has recently been located (since last picture).     */
    IMG_BOOL              bNewOutputConfig;     /*!< Signaled when playing (decoding) whether the output config
                                                     has changed since last time.                                     */
    IMG_BOOL              bNoPrevRefsUsed;      /*!< Signaled at a closed GOP this flag indicates that no previous
                                                     reference pictures will be used. Cleared after submitting next picture.    */
    IMG_UINT32            ui32MinLoad;          /*!< Min loading of core that supports current picture.               */
    IMG_UINT32            ui32AvailLoad;        /*!< Loading of available core that supports current picture.         */
    IMG_UINT32            ui32Avail;            /*!< Resource availability last time we could not schedule.           */

    scheduler_sStrUnitErrorDesc aStopOnStrUnitError[VDECDD_STRUNIT_MAX];  /*!< Describes how to behave on errors.     */

    IMG_BOOL              bSequInfoLogged;      /*!< Sequence information has been logged for the first (and only time.)*/
    IMG_BOOL              bOutputConfigLogged;  /*!< Output configuration has been logged for the first (and only time.)*/

    IMG_UINT32            ui32StrId;

} scheduler_sStreamCtx;


/*****************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************/

/* This table defines the default behaviour on errors. */
static scheduler_sStrUnitErrorDesc aStopOnStrUnitErrorDefault[VDECDD_STRUNIT_MAX] =
{
        {IMG_FALSE, ERROR_SCOPE_OTHER   }, /* VDECDD_STRUNIT_ANONYMOUS       */
        {IMG_FALSE, ERROR_SCOPE_SEQUENCE}, /* VDECDD_STRUNIT_SEQUENCE_START  */
        {IMG_FALSE, ERROR_SCOPE_SEQUENCE}, /* VDECDD_STRUNIT_CLOSED_GOP      */
        {IMG_FALSE, ERROR_SCOPE_SEQUENCE}, /* VDECDD_STRUNIT_SEQUENCE_END    */
        {IMG_FALSE, ERROR_SCOPE_PICTURE }, /* VDECDD_STRUNIT_PICTURE_PORTENT */
        {IMG_FALSE, ERROR_SCOPE_IGNORE  }, /* VDECDD_STRUNIT_PICTURE_START   */
        {IMG_FALSE, ERROR_SCOPE_IGNORE  }, /* VDECDD_STRUNIT_PICTURE_END   */
        {IMG_FALSE, ERROR_SCOPE_IGNORE  }, /* VDECDD_STRUNIT_PICTURE_FRAG    */
        {IMG_FALSE, ERROR_SCOPE_IGNORE  }, /* VDECDD_STRUNIT_FENCE           */
        {IMG_FALSE, ERROR_SCOPE_IGNORE  }  /* VDECDD_STRUNIT_STOP            */
};


/*****************************************************************************
 * EXTERNAL FUNCTIONS
 *****************************************************************************/

extern IMG_RESULT DECODER_GetLoad(
    IMG_HANDLE          hDecCtx,
    IMG_UINT32          ui32StreamFeature,
    IMG_UINT32        * pui32AvailLoad,
    IMG_UINT32        * pui32MinLoad
);



/*****************************************************************************
 * LOCAL FUNCTIONS
 *****************************************************************************/



static IMG_RESULT
scheduler_PictureAttachResources(
    scheduler_sStreamCtx * psSchStrCtx,
    VDECDD_sStrUnit      * psStrUnit,
    IMG_BOOL               bCheck
)
{
    IMG_UINT32 ui32Result = IMG_SUCCESS;

    /* Take sequence header from cache.
     * Note: sequence header id must be set in PICTURE_START unit
     *       or stored in scheduler. */
    psStrUnit->psSequHdrInfo = RESOURCE_ListGetById(&psSchStrCtx->sSequHdrList,
                                                    psStrUnit->ui32SeqHdrId);

    /* Check is not needed e.g. when freeing resources at stream destroy */
    if (bCheck == IMG_TRUE && psStrUnit->psSequHdrInfo == IMG_NULL)
    {
        REPORT(REPORT_MODULE_SCHEDULER,
               REPORT_ERR,
               "[USERSID=0x%08X] "
               "Sequence header not available for current picture while attaching",
               psSchStrCtx->sStreamConfig.ui32UserStrId);

        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_SEMANTICS_ERROR;
        ui32Result = IMG_ERROR_NOT_SUPPORTED;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              scheduler_FreeStreamUnit

******************************************************************************/
static IMG_RESULT
scheduler_FreeStreamUnit(
    VDECDD_sStrUnit   * psStrUnit,
    IMG_VOID          * pvCbParam
)
{
    scheduler_sStreamCtx * psSchStrCtx = (scheduler_sStreamCtx *) pvCbParam;
    IMG_UINT32             ui32Result = IMG_SUCCESS;

    // Attach picture resources where required.
    if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START)
    {
        /* Do not force attachment because the resources can be unattached yet,
         * e.g. in case of not yet processed picture units */
        scheduler_PictureAttachResources(psSchStrCtx, psStrUnit, IMG_FALSE);
    }

    psStrUnit->bDecode = IMG_FALSE;

    ui32Result = psSchStrCtx->psSchCtx->pfnCompCallback(
                                    SCHEDULER_CB_PROCESS_UNIT,
                                    psSchStrCtx->psSchCtx->pvCompInitUserData,
                                    IMG_NULL,
                                    psSchStrCtx->pvStreamUserData,
                                    psStrUnit);

    return ui32Result;
}



/*!
******************************************************************************

 @Function              scheduler_GetResourceAvailability

******************************************************************************/
static IMG_BOOL
scheduler_GetResourceAvailability(
    scheduler_sStreamCtx *  psSchStrCtx
)
{
    IMG_UINT32 ui32Avail = -1;

    if (RESOURCE_ListGetNumAvail(&psSchStrCtx->sPictBufferList) == 0)
    {
        ui32Avail &= ~SCHEDULER_AVAIL_PICTBUF;
    }

    if (RESOURCE_ListGetNumAvail(&psSchStrCtx->sPictResList) == 0)
    {
        ui32Avail &= ~SCHEDULER_AVAIL_PICTRES;
    }

    // Schedule if this is the best we can do...
    if (psSchStrCtx->ui32AvailLoad == -1 ||
        psSchStrCtx->ui32AvailLoad != psSchStrCtx->ui32MinLoad)
    {
        ui32Avail &= ~SCHEDULER_AVAIL_CORE;
    }

    return ui32Avail;
}



/*!
******************************************************************************

 @Function              scheduler_ReconfigureReconPictBufs

******************************************************************************/
static IMG_RESULT
scheduler_ReconfigureReconPictBufs(
    scheduler_sStreamCtx * psSchStrCtx,
    IMG_BOOL               bNoReferences
)
{
    IMG_UINT32 ui32Result;

    /* Re-configure the internal picture buffers now that none are held. */
    ui32Result = psSchStrCtx->psSchCtx->pfnCompCallback(
        SCHEDULER_CB_STREAM_RECONFIGRE_RECON_PICTBUFS,
        psSchStrCtx->psSchCtx->pvCompInitUserData,
        IMG_NULL,
        psSchStrCtx->pvStreamUserData,
        &bNoReferences);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              scheduler_ValidateNewSequence

******************************************************************************/
static IMG_RESULT
scheduler_ValidateNewSequence(
    scheduler_sStreamCtx        * psSchStrCtx,
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo
)
{
    IMG_RESULT ui32Result;
    VDECDD_sSuppCheck sSupportCheck;
    IMG_UINT32 ui32NumReqBufsPrev, ui32NumReqBufsCur;

#ifdef __RELEASE_RELEASE__
    if (!psSchStrCtx->bSequInfoLogged)
    {
        REPORT(REPORT_MODULE_SCHEDULER,
               REPORT_INFO,
               "[SID=0x%08X] [%s] Prof:%u, Lev:%u, FR:%ufps, BR:%ukbps, AR:%u/%u, Views:%u, IL:%s, OOP:%s, FCMB:%s, PostProc:%s, PixFmt:{%d, %d, %d, %d, %d, %u, %u, %u}, MCS:%ux%u,     Display:(%u,%u)...(%u,%u)",
               psSchStrCtx->ui32StrId,
               "Sequence Header",
               psComSequHdrInfo->ui32CodecProfile,
               psComSequHdrInfo->ui32CodecLevel,
               psComSequHdrInfo->ui32FrameRateDen ? psComSequHdrInfo->ui32FrameRateNum/psComSequHdrInfo->ui32FrameRateDen : 0,
               psComSequHdrInfo->ui32Bitrate,
               psComSequHdrInfo->ui32AspectRatioNum,
               psComSequHdrInfo->ui32AspectRatioDen,
               psComSequHdrInfo->ui32NumViews,
               (psComSequHdrInfo->bInterlacedFrames)  ? "y" : "n",
               (psComSequHdrInfo->bPictureReordering) ? "y" : "n",
               (psComSequHdrInfo->bFieldCodedMBlocks) ? "y" : "n",
               (psComSequHdrInfo->bPostProcessing) ? "y" : "n",
               psComSequHdrInfo->sPixelInfo.ePixelFormat,
               psComSequHdrInfo->sPixelInfo.eChromaInterleaved,
               psComSequHdrInfo->sPixelInfo.bChromaFormat,
               psComSequHdrInfo->sPixelInfo.eMemoryPacking,
               psComSequHdrInfo->sPixelInfo.eChromaFormatIdc,
               psComSequHdrInfo->sPixelInfo.ui32BitDepthY,
               psComSequHdrInfo->sPixelInfo.ui32BitDepthC,
               psComSequHdrInfo->sPixelInfo.ui32NoPlanes,
               psComSequHdrInfo->sMaxFrameSize.ui32Width,
               psComSequHdrInfo->sMaxFrameSize.ui32Height,
               psComSequHdrInfo->sOrigDisplayRegion.ui32LeftOffset,
               psComSequHdrInfo->sOrigDisplayRegion.ui32TopOffset,
               psComSequHdrInfo->sOrigDisplayRegion.ui32LeftOffset + psComSequHdrInfo->sOrigDisplayRegion.ui32Width,
               psComSequHdrInfo->sOrigDisplayRegion.ui32TopOffset + psComSequHdrInfo->sOrigDisplayRegion.ui32Height);

        psSchStrCtx->bSequInfoLogged = IMG_TRUE;
    }

#else

    DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "User stream id: 0x%08X", psSchStrCtx->sStreamConfig.ui32UserStrId);
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "======================================================");
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "Sequence Header");
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "---------------");
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                 "Codec (profile/level):    %d/%d",
                 psComSequHdrInfo->ui32CodecProfile,
                 psComSequHdrInfo->ui32CodecLevel);
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
        "Bitrate:                  %d kbps", psComSequHdrInfo->ui32Bitrate);
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
        "Aspect Ratio:             %d:%d", psComSequHdrInfo->ui32AspectRatioNum, psComSequHdrInfo->ui32AspectRatioDen);
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
        "Interlaced content:       %s", (psComSequHdrInfo->bInterlacedFrames) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
        "Picture re-odering:       %s", (psComSequHdrInfo->bPictureReordering) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
        "Maximum coded frame size: %dx%d",
            psComSequHdrInfo->sMaxFrameSize.ui32Width,
            psComSequHdrInfo->sMaxFrameSize.ui32Height);
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
        "Display Region:           (%d,%d)...(%d,%d)",
        psComSequHdrInfo->sOrigDisplayRegion.ui32LeftOffset,
        psComSequHdrInfo->sOrigDisplayRegion.ui32TopOffset,
        psComSequHdrInfo->sOrigDisplayRegion.ui32LeftOffset + psComSequHdrInfo->sOrigDisplayRegion.ui32Width,
        psComSequHdrInfo->sOrigDisplayRegion.ui32TopOffset + psComSequHdrInfo->sOrigDisplayRegion.ui32Height);
    DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "======================================================");

#endif

    IMG_MEMSET(&sSupportCheck, 0, sizeof(sSupportCheck));

    // Omit picture header from this setup since we can't validate this here.
    sSupportCheck.psComSequHdrInfo = psComSequHdrInfo;

    if (psSchStrCtx->bOutputConfigSet)
    {
        sSupportCheck.psOutputConfig = &psSchStrCtx->sOutputConfig;
        sSupportCheck.psDispPictBuf = &psSchStrCtx->sDispPictBuf;

        ui32Result = VDECDDUTILS_GetMinRequiredNumPicts(&psSchStrCtx->sStreamConfig,
                                                        &psSchStrCtx->sComSequHdrInfo,
                                                        &psSchStrCtx->sOutputConfig,
                                                        &ui32NumReqBufsPrev);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        ui32Result = VDECDDUTILS_GetMinRequiredNumPicts(&psSchStrCtx->sStreamConfig,
                                                        psComSequHdrInfo,
                                                        &psSchStrCtx->sOutputConfig,
                                                        &ui32NumReqBufsCur);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

    }

    /* Clear reconfiguration flag before checking and
       resetting if required for this sequence. */
    psSchStrCtx->sStopInfo.ui32StopFlags &= ~VDEC_STOPSTATUS_RECONFIGURE;
    psSchStrCtx->sStopInfo.ui32StopFlags &=
        ~(VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID |
          VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID |
          VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID);

    /* Check if the output configuration is compatible with new VSH. */
    ui32Result = psSchStrCtx->psSchCtx->pfnCompCallback(
        SCHEDULER_CB_STREAM_CHECK_SUPPORTED,
        psSchStrCtx->psSchCtx->pvCompInitUserData,
        IMG_NULL,
        psSchStrCtx->pvStreamUserData,
        &sSupportCheck);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (sSupportCheck.ui32StopFlags & VDEC_STOPSTATUS_UNSUPPORTED)
    {
       psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_UNSUPPORTED;
    }

    if (psSchStrCtx->bOutputConfigSet && ui32NumReqBufsPrev < ui32NumReqBufsCur)
    {
       psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_MIN_NUM_PICTBUFS_INCREASED;
    }

    // Check for a resolution change.
    if (VDEC_SIZE_NE(psComSequHdrInfo->sOrigDisplayRegion, psSchStrCtx->sComSequHdrInfo.sOrigDisplayRegion))
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_DISPLAY_RESOLUTION_CHANGED;
    }

    // In case of chroma format or bitdepth change, reconfig is required.
    if (psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != psSchStrCtx->sComSequHdrInfo.sPixelInfo.eChromaFormatIdc ||
        psComSequHdrInfo->sPixelInfo.ui32BitDepthY != psSchStrCtx->sComSequHdrInfo.sPixelInfo.ui32BitDepthY ||
        psComSequHdrInfo->sPixelInfo.ui32BitDepthC != psSchStrCtx->sComSequHdrInfo.sPixelInfo.ui32BitDepthC)
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_RECONFIGURE;
    }

    psSchStrCtx->bNewSequence = IMG_TRUE;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              scheduler_ValidateNewPicture

******************************************************************************/
static IMG_RESULT
scheduler_ValidateNewPicture(
    scheduler_sStreamCtx        * psSchStrCtx,
    const BSPP_sPictHdrInfo     * psPictHdrInfo,
    IMG_UINT32                  * pui32Features
)
{
    IMG_RESULT ui32Result;
    VDECDD_sSuppCheck sSupportCheck;

    VDEC_BZERO(&sSupportCheck);
    sSupportCheck.psComSequHdrInfo = &psSchStrCtx->sComSequHdrInfo;
    sSupportCheck.psPictHdrInfo = psPictHdrInfo;

    // they cannot become invalid during a sequence.
    // However, output configuration may signal something that changes compatibility
    // on a closed GOP within a sequence (e.g. resolution may significantly decrease
    // in a GOP and scaling wouldn't be supported). This resolution shift would not
    // be signalled in the sequence header (since that is the maximum) but only
    // found now when validating the first picture in the GOP.
    if (psSchStrCtx->bOutputConfigSet)
    {
        sSupportCheck.psOutputConfig = &psSchStrCtx->sOutputConfig;
    //    sSupportCheck.psPictRendInfo = &psSchStrCtx->sDispPictRendInfo;
    }

    /* Clear reconfiguration flag before checking and
       resetting if required for this sequence. */
    psSchStrCtx->sStopInfo.ui32StopFlags &= ~VDEC_STOPSTATUS_RECONFIGURE;
    psSchStrCtx->sStopInfo.ui32StopFlags &=
        ~(//VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID |
          //VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID |
          VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID);

    /* Check if the new picture is compatible with the current driver state. */
    ui32Result = psSchStrCtx->psSchCtx->pfnCompCallback(
        SCHEDULER_CB_STREAM_CHECK_SUPPORTED,
        psSchStrCtx->psSchCtx->pvCompInitUserData,
        IMG_NULL,
        psSchStrCtx->pvStreamUserData,
        &sSupportCheck);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Only check if decoding, else clear stop flags */
    if (psSchStrCtx->bDecode)
    {
        if (sSupportCheck.sUnSupportedFlags.ui32StrOutputConfig ||
            sSupportCheck.sUnSupportedFlags.ui32PictHdr)
        {
            return IMG_ERROR_NOT_SUPPORTED;
        }
    }
    else
    {
         psSchStrCtx->sStopInfo.ui32StopFlags = 0;
    }

    // Clear the reconfiguration flags unless triggered by unsupported output config.
    psSchStrCtx->sStopInfo.ui32StopFlags &= ~VDEC_STOPSTATUS_RECONFIGURE;
    psSchStrCtx->sStopInfo.ui32StopFlags &=
        ~(VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID |
          VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID);
    if (psSchStrCtx->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID)
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_RECONFIGURE;
    }

    *pui32Features = sSupportCheck.ui32Features;

    return IMG_SUCCESS;
}


static IMG_RESULT
scheduler_StoreState(
    scheduler_sStreamCtx * psSchStrCtx
)
{
    // Extract any state that is necessary to know for first picture
    if (psSchStrCtx->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_NO_REFERENCE_IMAGES)
    {
        psSchStrCtx->bNoPrevRefsUsed = IMG_TRUE;
    }

    // Clear all stop flags.
    psSchStrCtx->sStopInfo.ui32StopFlags = 0;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              scheduler_PicturePrepare

******************************************************************************/
static IMG_RESULT
scheduler_PicturePrepare(
    scheduler_sStreamCtx * psSchStrCtx,
    VDECDD_sStrUnit      * psStrUnit
)
{
    IMG_RESULT          ui32Result = IMG_SUCCESS;
    VDECDD_sPicture   * psPicture = IMG_NULL;

    /* For normal decode, setup picture data. */
    if (IS_DECODING(psSchStrCtx->ePlayMode, psSchStrCtx->psSchCtx->eDecodeLevel))
    {
        /* Preallocate the picture structure. */
        VDEC_MALLOC(psPicture);
        if (psPicture == IMG_NULL)
        {
            REPORT(REPORT_MODULE_SCHEDULER, REPORT_ERR,
                   "[USERSID=0x%08X] Failed to allocate memory for DD picture structure",
                   psSchStrCtx->sStreamConfig.ui32UserStrId);
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto unwind;
        }
        VDEC_BZERO(psPicture);

        {
            VDECDD_sLoadCheck sLoadCheck;

            VDEC_BZERO(&sLoadCheck);
            sLoadCheck.ui32Features = psStrUnit->ui32Features;

            /* Determine whether the picture can be scheduled. */
            ui32Result = psSchStrCtx->psSchCtx->pfnCompCallback(
                SCHEDULER_CB_STREAM_CHECK_LOAD,
                psSchStrCtx->psSchCtx->pvCompInitUserData,
                IMG_NULL,
                psSchStrCtx->pvStreamUserData,
                &sLoadCheck);
            if (ui32Result != IMG_SUCCESS)
            {
                goto unwind;
            }

            // Load and availability is cached in stream context simply for status reporting.
            psSchStrCtx->ui32AvailLoad = sLoadCheck.ui32AvailLoad;
            psSchStrCtx->ui32MinLoad = sLoadCheck.ui32MinLoad;
            psSchStrCtx->ui32Avail = scheduler_GetResourceAvailability(psSchStrCtx);

            if ((psSchStrCtx->ui32Avail & SCHEDULER_AVAIL_CORE) == 0)
            {
                // Return straight away if the core is not available.
                ui32Result = IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
                goto unwind;
            }
        }

        if (psSchStrCtx->bNewOutputConfig || psSchStrCtx->bNewSequence)
        {
            // Reconstructed buffers should be checked for reconfiguration under these conditions:
            //     1. New output configuration,
            //     2. New sequence.
            // Plant can decide to reset the reconstructed buffer properties if there are
            // no previous reference pictures used (i.e. at a closed GOP).
            // This code must go here because we may not stop when new sequence is found
            // or references become unused.
            ui32Result = scheduler_ReconfigureReconPictBufs(
                psSchStrCtx,
                psSchStrCtx->bNoPrevRefsUsed);
            IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto unwind;
            }
        }

        // Update the display information for this picture.
        ui32Result = VDECUTILS_GetDisplayRegion(
            &psStrUnit->psPictHdrInfo->sCodedFrameSize,
            &psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion,
            &psSchStrCtx->sOutputConfig,
            &psStrUnit->psPictHdrInfo->sDispInfo.sDispRegion);
        IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto unwind;
        }

        // Print display resolution every time sequence or output changes.
        // For some standards the picture display size might change more
        // frequently but this will bloat the logs.
        if (psSchStrCtx->bNewOutputConfig || psSchStrCtx->bNewSequence)
        {
            DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                         "[USERSID=0x%08X] Display picture region:\t(%d...%d),(%d...%d) (pixels)",
                         psSchStrCtx->sStreamConfig.ui32UserStrId,
                         psStrUnit->psPictHdrInfo->sDispInfo.sDispRegion.ui32LeftOffset,
                         psStrUnit->psPictHdrInfo->sDispInfo.sDispRegion.ui32LeftOffset +
                             psStrUnit->psPictHdrInfo->sDispInfo.sDispRegion.ui32Width,
                         psStrUnit->psPictHdrInfo->sDispInfo.sDispRegion.ui32TopOffset,
                         psStrUnit->psPictHdrInfo->sDispInfo.sDispRegion.ui32TopOffset +
                             psStrUnit->psPictHdrInfo->sDispInfo.sDispRegion.ui32Height);
        }

        // Clear internal state.
        psSchStrCtx->bNewSequence = IMG_FALSE;
        psSchStrCtx->bNewOutputConfig = IMG_FALSE;
        psSchStrCtx->bNoPrevRefsUsed = IMG_FALSE;

        // Recalculate this since we might have just created internal resources.
        psSchStrCtx->ui32Avail = scheduler_GetResourceAvailability(psSchStrCtx);

        {
            /* If picture resources were needed for this stream, picture resources list wouldn't be empty */
            IMG_BOOL bNeedPictRes = LST_first(&psSchStrCtx->sPictResList) != IMG_NULL;
            /* If there are resources available... */
            if ((psSchStrCtx->ui32Avail & SCHEDULER_AVAIL_PICTBUF) &&
                (!bNeedPictRes || (psSchStrCtx->ui32Avail & SCHEDULER_AVAIL_PICTRES)))
            {
                /* Pick internal picture resources. */
                if (bNeedPictRes)
                {
                    psPicture->psPictResInt = RESOURCE_ListGetAvail(&psSchStrCtx->sPictResList);
                    IMG_ASSERT(psPicture->psPictResInt);
                    if (psPicture->psPictResInt == IMG_NULL)
                    {
                        ui32Result = IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
                        goto unwind;
                    }
                }

                /* Pick the client image buffer. */
                psPicture->sDisplayPictBuf.psPictBuf = RESOURCE_ListGetAvail(&psSchStrCtx->sPictBufferList);
                IMG_ASSERT(psPicture->sDisplayPictBuf.psPictBuf);
                if (psPicture->sDisplayPictBuf.psPictBuf == IMG_NULL)
                {
                    ui32Result = IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
                    goto unwind;
                }
            }
            else
            {
                /* Need resources to process picture start. */
                ui32Result = IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
                goto unwind;
            }
        }

        /* Ensure that the buffer contains layout information. */
        psPicture->sDisplayPictBuf.sRendInfo = psSchStrCtx->sDispPictBuf.sRendInfo;
        psPicture->sDisplayPictBuf.sBufConfig = psSchStrCtx->sDispPictBuf.sBufConfig;
        psPicture->sOutputConfig = psSchStrCtx->sOutputConfig;
        psPicture->bLastPictInSeq = psStrUnit->bLastPictInSeq;

        psStrUnit->pvDdPictData = psPicture;

        psSchStrCtx->sSchStatus.ui32TotalPictScheduled++;

        // Indicate that all necessary resources
        // are now available.
        if (psSchStrCtx->ui32Avail != -1)
        {
            /*printf("LAST AVAIL: 0x%08X\n",
                psSchStrCtx->ui32Avail); */
            psSchStrCtx->ui32Avail = -1;
        }

        // Avoid NULL dereferencing
        if (psPicture->psPictResInt)
        {
            if (psPicture->psPictResInt->psMBParamBuf)
            {
                DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                    "[USERSID=0x%08X] MB parameter buffer device virtual address: 0x%08X",
                    psSchStrCtx->sStreamConfig.ui32UserStrId,
                    psPicture->psPictResInt->psMBParamBuf->sDdBufInfo.ui32DevVirt);
            }

            if (psPicture->psPictResInt->psDdPictBuf)
            {
                DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                             "[USERSID=0x%08X] Recon picture virtual address: LUMA 0x%08X, CHROMA 0x%08X",
                             psSchStrCtx->sStreamConfig.ui32UserStrId,
                             psPicture->psPictResInt->psDdPictBuf->psPictBuf->sDdBufInfo.ui32DevVirt,
                             psPicture->psPictResInt->psDdPictBuf->psPictBuf->sDdBufInfo.ui32DevVirt +
                             psPicture->psPictResInt->psDdPictBuf->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Offset);
            }

            DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                         "[USERSID=0x%08X] Display picture virtual address: LUMA 0x%08X, CHROMA 0x%08X",
                         psSchStrCtx->sStreamConfig.ui32UserStrId,
                         psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.ui32DevVirt,
                         psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.ui32DevVirt +
                         psPicture->sDisplayPictBuf.sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Offset);
        }
    }

    ui32Result = scheduler_PictureAttachResources(psSchStrCtx, psStrUnit, IMG_TRUE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto unwind;
    }

    return IMG_SUCCESS;


unwind:
    if (psPicture)
    {
        if (psPicture->psPictResInt)
        {
            RESOURCE_ItemReturn(&psPicture->psPictResInt->ui32RefCount);
            psPicture->psPictResInt = IMG_NULL;
        }

        if (psPicture->sDisplayPictBuf.psPictBuf)
        {
            RESOURCE_ItemReturn(&psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.ui32RefCount);
            psPicture->sDisplayPictBuf.psPictBuf = IMG_NULL;
        }

        IMG_FREE(psPicture);
    }

    return ui32Result;
}



/*!
******************************************************************************

 @Function              scheduler_UpdateStopFlags

******************************************************************************/
static IMG_RESULT
scheduler_SetStopInfo(
    scheduler_sStreamCtx * psSchStrCtx,
    VDECDD_sStrUnit *      psStrUnit
)
{
    IMG_RESULT eResult = IMG_SUCCESS;

    /* Ensure that the stream unit is valid. */
    IMG_ASSERT(psStrUnit);
    if (psStrUnit == IMG_NULL ||
        psStrUnit->eStrUnitType >= VDECDD_STRUNIT_MAX)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* If stopping on bitstream errors for this stream unit is required... */
    if (psSchStrCtx->aStopOnStrUnitError[psStrUnit->eStrUnitType].bStop)
    {
        /* ...check for errors (ignoring AUX errors)... */
        if (VDEC_ERROR_NONE != psStrUnit->ui32ErrorFlags )
        {
            /* ...and set the stopped on error flag. */
            psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_BITSTREAM_ERROR;

            /* Also pass on errors. */
            switch (psSchStrCtx->aStopOnStrUnitError[psStrUnit->eStrUnitType].eErrScope)
            {
                case ERROR_SCOPE_SEQUENCE:
                    psSchStrCtx->sStopInfo.sBitstreamErrorInfo.ui32SequenceError = psStrUnit->ui32ErrorFlags;
                    break;

                case ERROR_SCOPE_PICTURE:
                    psSchStrCtx->sStopInfo.sBitstreamErrorInfo.ui32PictureError = psStrUnit->ui32ErrorFlags;
                    break;

                case ERROR_SCOPE_OTHER:
                    psSchStrCtx->sStopInfo.sBitstreamErrorInfo.ui32OtherError = psStrUnit->ui32ErrorFlags;
                    break;

                default:
                    IMG_ASSERT(0);
                    break;
            }
        }
    }

    if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_SEQUENCE_START)
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_SEQUENCE_START;
        if (psStrUnit->bClosedGOP)
        {
            psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_CLOSED_GOP;
            psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_NO_REFERENCE_IMAGES;
        }

        psSchStrCtx->sStopInfo.ui32StopFlags &= ~VDEC_STOPSTATUS_SEQUENCE_END;
    }
    else if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_CLOSED_GOP)
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_CLOSED_GOP;
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_NO_REFERENCE_IMAGES;
    }
    else if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_SEQUENCE_END)
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_SEQUENCE_END;
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_NO_REFERENCE_IMAGES;
    }
    else if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_FENCE)
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_FENCE;
    }
    else if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_END)
    {
        psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_PICTURE_END;
    }

    return eResult;
}



/*!
******************************************************************************

 @Function              scheduler_StreamStop

******************************************************************************/
static IMG_RESULT
scheduler_StreamStop(
    scheduler_sStreamCtx  * psSchStrCtx,
    const IMG_VOID        * pvTag
)
{
    scheduler_sContext * psSchCtx = psSchStrCtx->psSchCtx;
    VDECDD_sStrUnit * psStopUnit;
    IMG_RESULT eResult = IMG_SUCCESS;

    VDEC_MALLOC(psStopUnit);
    if(IMG_NULL == psStopUnit)
    {
        REPORT(REPORT_MODULE_SCHEDULER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to allocate memory for stop unit",
               psSchStrCtx->sStreamConfig.ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psStopUnit);

    psStopUnit->eStrUnitType = VDECDD_STRUNIT_STOP;
    psStopUnit->pvDdData = IMG_MALLOC(sizeof(VDEC_sStopInfo));
    if(IMG_NULL == psStopUnit->pvDdData)
    {
        IMG_FREE(psStopUnit);
        REPORT(REPORT_MODULE_SCHEDULER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to allocate memory for stop info",
               psSchStrCtx->sStreamConfig.ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    *((VDEC_sStopInfo*)psStopUnit->pvDdData) = psSchStrCtx->sStopInfo;
    psStopUnit->pvStrUnitTag = (IMG_VOID *)pvTag;

    psStopUnit->bDecode = IMG_TRUE;

    eResult = psSchCtx->pfnCompCallback(
        SCHEDULER_CB_PROCESS_UNIT,
        psSchCtx->pvCompInitUserData,
        IMG_NULL,
        psSchStrCtx->pvStreamUserData,
        psStopUnit);
    IMG_ASSERT(eResult == IMG_SUCCESS);
    if (eResult != IMG_SUCCESS)
    {
        IMG_FREE(psStopUnit->pvDdData);
        IMG_FREE(psStopUnit);
        return eResult;
    }

    psSchStrCtx->eCurrentStopPoint = VDEC_STOPPOINT_UNDEFINED;
    psSchStrCtx->bStopped = IMG_TRUE;

    return eResult;
}



/*!
******************************************************************************

 @Function              scheduler_SetActiveStopFlags

******************************************************************************/
static IMG_VOID
scheduler_SetActiveStopFlags(
    IMG_BOOL                    bDecoding,
    VDEC_eStopPoint             eStopPoint,
    scheduler_sStrUnitErrorDesc aStopOnStrUnitError[],
    IMG_UINT32                * pui32ActiveStopFlags
)
{
    VDECDD_eStrUnitType eStrUnitType = VDECDD_STRUNIT_ANONYMOUS;
    IMG_UINT32          ui32ActiveStopFlags;

    /* 1. Set the active stop flags from requested stop point. */
    ui32ActiveStopFlags = VDEC_STOPSTATUS_FENCE |
                          VDEC_STOPSTATUS_UNSUPPORTED |
                          VDEC_STOPSTATUS_SEMANTICS_ERROR;

    if (eStopPoint == VDEC_STOPPOINT_SEQUENCE_START)
    {
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_SEQUENCE_START;
    }
    else if (eStopPoint == VDEC_STOPPOINT_CLOSED_GOP)
    {
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_CLOSED_GOP;
    }
    else if (eStopPoint == VDEC_STOPPOINT_NEW_DISPLAY_RESOLUTION)
    {
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_DISPLAY_RESOLUTION_CHANGED;
    }
    else if (eStopPoint == VDEC_STOPPOINT_SEQUENCE_END)
    {
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_SEQUENCE_END;
    }
    else if (eStopPoint == VDEC_STOPPOINT_PICTURE_END)
    {
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_PICTURE_END;
    }

    /* 2. Set the active stop flags for when client intervention is required. */
    if (bDecoding)
    {
        /* If decoding an implicit stop is required for client intervention to reconfigure. */
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_RECONFIGURE;
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_PICTBUF_NUM_MAPPED_INVALID;
        ui32ActiveStopFlags |= VDEC_STOPSTATUS_MIN_NUM_PICTBUFS_INCREASED;
    }

    /* Check if to stop on any errors. */
    while (eStrUnitType < VDECDD_STRUNIT_MAX)
    {
        if (aStopOnStrUnitError[eStrUnitType].bStop)
        {
            ui32ActiveStopFlags |= VDEC_STOPSTATUS_BITSTREAM_ERROR;
            break;
        }
        eStrUnitType++;
    }

    *pui32ActiveStopFlags = ui32ActiveStopFlags;
}



/*!
******************************************************************************

 @Function              scheduler_PrepareToPlay

******************************************************************************/
static IMG_RESULT
scheduler_PrepareToPlay(
    scheduler_sStreamCtx  * psSchStrCtx
)
{
    VDECDD_sSuppCheck sSupportCheck;
    IMG_RESULT ui32Result;

    VDEC_BZERO(&sSupportCheck);

    if (VDEC_SIZE_NZ(psSchStrCtx->sComSequHdrInfo.sMaxFrameSize))
    {
        sSupportCheck.psComSequHdrInfo = &psSchStrCtx->sComSequHdrInfo;
    }

    if (psSchStrCtx->bOutputConfigSet)
    {
        sSupportCheck.psOutputConfig = &psSchStrCtx->sOutputConfig;
        sSupportCheck.psDispPictBuf = &psSchStrCtx->sDispPictBuf;
    }

    /* Clear reconfiguration flag before checking and
       resetting if required for this sequence. */
    psSchStrCtx->sStopInfo.ui32StopFlags &= ~VDEC_STOPSTATUS_RECONFIGURE;
    psSchStrCtx->sStopInfo.ui32StopFlags &=
        ~(VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID |
          VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID |
          VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID);

    /* Check if the output configuration is compatible with new VSH. */
    ui32Result = psSchStrCtx->psSchCtx->pfnCompCallback(
        SCHEDULER_CB_STREAM_CHECK_SUPPORTED,
        psSchStrCtx->psSchCtx->pvCompInitUserData,
        IMG_NULL,
        psSchStrCtx->pvStreamUserData,
        &sSupportCheck);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (psSchStrCtx->bDecode)
    {
#ifdef __RELEASE_RELEASE__
        if (!psSchStrCtx->bOutputConfigLogged)
        {
            REPORT(REPORT_MODULE_SCHEDULER,
                   REPORT_INFO,
                   "[SID=0x%08X] [%s] PixFmt:{%d, %d, %d, %d, %d, %u, %u, %u}, IDC:%s, Planes:%u, CO:%s, MemPack:%s, LumaBD:%u, ChromaBD:%u, Rot:%s, Scale:%ux%u, ForceOOLD:%s",
                   psSchStrCtx->ui32StrId,
                   "Output Configuration",
                   psSchStrCtx->sOutputConfig.sPixelInfo.ePixelFormat,
                   psSchStrCtx->sOutputConfig.sPixelInfo.eChromaInterleaved,
                   psSchStrCtx->sOutputConfig.sPixelInfo.bChromaFormat,
                   psSchStrCtx->sOutputConfig.sPixelInfo.eMemoryPacking,
                   psSchStrCtx->sOutputConfig.sPixelInfo.eChromaFormatIdc,
                   psSchStrCtx->sOutputConfig.sPixelInfo.ui32BitDepthY,
                   psSchStrCtx->sOutputConfig.sPixelInfo.ui32BitDepthC,
                   psSchStrCtx->sOutputConfig.sPixelInfo.ui32NoPlanes,
                   acPixelFormatIdcNames[psSchStrCtx->sOutputConfig.sPixelInfo.eChromaFormatIdc],
                   psSchStrCtx->sOutputConfig.sPixelInfo.ui32NoPlanes,
                   acPixelChromaInterleavedNames[psSchStrCtx->sOutputConfig.sPixelInfo.eChromaInterleaved & 0x03],
                   acPixelMemoryPackingNames[psSchStrCtx->sOutputConfig.sPixelInfo.eMemoryPacking],
                   psSchStrCtx->sOutputConfig.sPixelInfo.ui32BitDepthY,
                   psSchStrCtx->sOutputConfig.sPixelInfo.ui32BitDepthC,
                   (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_0) ? "None" :
                     (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_90) ? "90" :
                     (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_180) ? "180" :
                     (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_270) ? "270" : "Invalid",
                   psSchStrCtx->sOutputConfig.bScale ? psSchStrCtx->sOutputConfig.sScaledPictSize.ui32Width : 0,
                   psSchStrCtx->sOutputConfig.bScale ? psSchStrCtx->sOutputConfig.sScaledPictSize.ui32Height : 0,
                   psSchStrCtx->sOutputConfig.bForceOold ? "y" : "n");

            psSchStrCtx->bOutputConfigLogged = IMG_TRUE;
        }
#else
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "User stream id: 0x%08X", psSchStrCtx->sStreamConfig.ui32UserStrId);
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "======================================================");
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "Output Configuration");
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "---------------------");
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Pixel Format:      %s",
                     (psSchStrCtx->sOutputConfig.sPixelInfo.ePixelFormat == IMG_PIXFMT_420PL12YUV8)
                         ? "IMG_PIXFMT_420PL12YUV8" : "No Name");
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "IDC:               %s",
                     acPixelFormatIdcNames[psSchStrCtx->sOutputConfig.sPixelInfo.eChromaFormatIdc]);
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Planes:            %d",
                     psSchStrCtx->sOutputConfig.sPixelInfo.ui32NoPlanes);
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Chroma order:      %s",
                     acPixelChromaInterleavedNames[psSchStrCtx->sOutputConfig.sPixelInfo.eChromaInterleaved & 0x03]);
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Memory Packing:    %s",
                     acPixelMemoryPackingNames[psSchStrCtx->sOutputConfig.sPixelInfo.eMemoryPacking]);
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Luma Bit depth:    %d",
                     psSchStrCtx->sOutputConfig.sPixelInfo.ui32BitDepthY);
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Chroma Bit depth:  %d",
                     psSchStrCtx->sOutputConfig.sPixelInfo.ui32BitDepthC);
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Rotation (angle):  %s",
                     (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_0) ? "None" :
                     (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_90) ? "90" :
                     (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_180) ? "180" :
                     (psSchStrCtx->sOutputConfig.eRotMode == VDEC_ROTATE_270) ? "270" : "Invalid");
        if (psSchStrCtx->sOutputConfig.bScale)
        {
            DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                         "Scaling:           %dx%d",
                         psSchStrCtx->sOutputConfig.sScaledPictSize.ui32Width,
                         psSchStrCtx->sOutputConfig.sScaledPictSize.ui32Height);
        }
        else
        {
            DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                         "Scaling:           None");
        }
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER,
                     "Force OOLD:        %s",
                     psSchStrCtx->sOutputConfig.bForceOold ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_SCHEDULER, "======================================================");
#endif
    }
    else
    {
        psSchStrCtx->sStopInfo.ui32StopFlags = 0;
    }

    return IMG_SUCCESS;
}



/*****************************************************************************
 * GLOBAL FUNCTIONS
 *****************************************************************************/


/*!
******************************************************************************

 @Function              SCHEDULER_Initialise

******************************************************************************/
IMG_RESULT
SCHEDULER_Initialise(
    IMG_VOID *              pvInitUserData,
    VDECDD_pfnCompCallback  pfnCallback,
    VDECDD_eDecodeLevel     eDecodeLevel,
    IMG_BOOL                bAPM,
    IMG_HANDLE              hDecCtx,
    IMG_HANDLE *            phSchCtx
)
{
    scheduler_sContext * psSchCtx = (scheduler_sContext*)*phSchCtx;

    IMG_ASSERT(IMG_NULL != hDecCtx);

    if (psSchCtx == IMG_NULL)
    {
        VDEC_MALLOC(psSchCtx);
        if(IMG_NULL == psSchCtx)
        {
            REPORT(REPORT_MODULE_SCHEDULER, REPORT_ERR, "Failed to allocate memory for Scheduler context");
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        VDEC_BZERO(psSchCtx);

        *phSchCtx = psSchCtx;
    }

    if (!psSchCtx->bInitialised)
    {
        /* Check input parameters. */
        IMG_ASSERT(IMG_NULL != pfnCallback);

        /* Store the input data. */
        psSchCtx->pvCompInitUserData = pvInitUserData;
        psSchCtx->pfnCompCallback = pfnCallback;
        psSchCtx->eDecodeLevel = eDecodeLevel;
        psSchCtx->hDecCtx = hDecCtx;

        // APM is always the default behaviour. Debug Options can ba used to turn it off/on.
        psSchCtx->bAPM = bAPM;

        /* Initialise the context lists. */
        LST_init(&psSchCtx->sStrCtxList);

        /* Mark as initialised. */
        psSchCtx->bInitialised = IMG_TRUE;
    }
    else
    {
        REPORT(REPORT_MODULE_SCHEDULER, REPORT_WARNING,
               "Scheduler already initialised");
        return IMG_ERROR_ALREADY_INITIALISED;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_Deinitialise

******************************************************************************/
IMG_RESULT
SCHEDULER_Deinitialise(
    IMG_HANDLE  hSchCtx
)
{
    scheduler_sContext * psSchCtx = (scheduler_sContext*)hSchCtx;

    /* Check input params. */
    if (psSchCtx && psSchCtx->bInitialised)
    {
        /* Check status of the module. */
        IMG_ASSERT(LST_empty(&psSchCtx->sStrCtxList));

        /* Mark as deinitialised. */
        psSchCtx->bInitialised = IMG_FALSE;

        IMG_FREE(psSchCtx);
    }
    else
    {
        REPORT(REPORT_MODULE_SCHEDULER, REPORT_WARNING,
               "Scheduler not initialised and therefore cannot deinitialise");
        return IMG_ERROR_NOT_INITIALISED;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              SCHEDULER_Run

******************************************************************************/
IMG_RESULT
SCHEDULER_Run(
    IMG_HANDLE      hSchCtx,
    IMG_VOID     ** ppvStrUserIntData
)
{
    scheduler_sContext * psSchCtx;
    scheduler_sStreamCtx * psSchStrCtx;
    VDECDD_sStrUnit * psStrUnit;
    IMG_UINT32 ui32Result = IMG_SUCCESS;
    IMG_BOOL bScheduled = IMG_FALSE;
    IMG_BOOL bOverwriteTag = IMG_FALSE;
    IMG_UINT32 ui32TagValue = 0;

    IMG_ASSERT(IMG_NULL != hSchCtx);
    if(hSchCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psSchCtx = (scheduler_sContext *)hSchCtx;

    /* Loop over all the stream contexts. */
    psSchStrCtx = LST_first(&psSchCtx->sStrCtxList);
    while (psSchStrCtx)
    {
        if (ppvStrUserIntData)
        {
            *ppvStrUserIntData = psSchStrCtx->pvStreamUserData;
        }

        /* Loop over all stream units until cannot/have nothing to schedule. */
        psStrUnit = RESOURCE_ListPeekHead(&psSchStrCtx->sStrUnitList);
        while (!psSchStrCtx->bStopped && psStrUnit)
        {
            VDECDD_sStrUnit * psProcStrUnit;
            IMG_BOOL          bProcessStrUnit = IMG_TRUE;
            const IMG_VOID  * pvTag = IMG_NULL;

            // Clear the stop flags here because any user intervention
            // would have been checked before re-starting playing.
            ui32Result = scheduler_StoreState(psSchStrCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            switch (psStrUnit->eStrUnitType)
            {
            case VDECDD_STRUNIT_SEQUENCE_START:
                if (psStrUnit->psSequHdrInfo)
                {
                    /* Add sequence header to cache. */
                    ui32Result = RESOURCE_ListReplace(
                        &psSchStrCtx->sSequHdrList,
                        psStrUnit->psSequHdrInfo,
                        psStrUnit->psSequHdrInfo->ui32SequHdrId,
                        &psStrUnit->psSequHdrInfo->ui32RefCount,
                        IMG_NULL,
                        IMG_NULL);

                    if (IMG_SUCCESS != ui32Result)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                               "[USERSID=0x%08X] Failed to replace resource",
                               psSchStrCtx->sStreamConfig.ui32UserStrId);
                    }
                }
                else
                {
                    /* ...or take from cache. */
                    psStrUnit->psSequHdrInfo =
                        RESOURCE_ListGetById(&psSchStrCtx->sSequHdrList,
                        psStrUnit->ui32SeqHdrId);
                }

                IMG_ASSERT(psStrUnit->psSequHdrInfo);
                if (psStrUnit->psSequHdrInfo == IMG_NULL)
                {
                    REPORT(REPORT_MODULE_SCHEDULER, REPORT_ERR,
                           "Sequence header information not available for current picture");

                    psSchStrCtx->sStopInfo.ui32StopFlags |= VDEC_STOPSTATUS_SEMANTICS_ERROR;
                    bProcessStrUnit = IMG_FALSE;
                }
                else
                {
                    // Check that this latest sequence header information is compatible with current state and
                    // then if no errors store as current.
                    ui32Result = scheduler_ValidateNewSequence(psSchStrCtx,
                                                               &psStrUnit->psSequHdrInfo->sComSequHdrInfo);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }
                    // Only copy SequHdrInfo if supported, otherwise keep the previous one
                    if (!(psSchStrCtx->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_UNSUPPORTED))
                    {
                        psSchStrCtx->sComSequHdrInfo = psStrUnit->psSequHdrInfo->sComSequHdrInfo;
                    }
                }
                break;

            case VDECDD_STRUNIT_PICTURE_START:

                if (IS_DECODING(psSchStrCtx->ePlayMode, psSchStrCtx->psSchCtx->eDecodeLevel))
                {
                    // Check that the picture configuration is compatible with the current state.
                    ui32Result = scheduler_ValidateNewPicture(psSchStrCtx,
                                                              psStrUnit->psPictHdrInfo,
                                                              &psStrUnit->ui32Features);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        if (ui32Result == IMG_ERROR_NOT_SUPPORTED)
                        {
                            // Do not process stream unit since there is something
                            // unsupported.
                            bProcessStrUnit = IMG_FALSE;
                            break;
                        }
                        else
                        {
                            return ui32Result;
                        }
                    }
                }

                // Prepare picture for decoding.
                ui32Result = scheduler_PicturePrepare(psSchStrCtx, psStrUnit);
                if (ui32Result != IMG_SUCCESS)
                {
                    if (ui32Result == IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE ||
                        ui32Result == IMG_ERROR_NOT_SUPPORTED)
                    {
                        // Do not process stream unit since there is something
                        // unsupported or resources are not available.
                        bProcessStrUnit = IMG_FALSE;
                        break;
                    }
                    else
                    {
                        return ui32Result;
                    }
                }

                /* Overwrite pvTag for random scale test. */
                {
                    DBGOPT_sValue sVal;
                    if (DBGOPTKM_GetSize("ScaleTest", DBGOPT_TYPE_BOOL) &&
                        DBGOPTKM_Get("ScaleTest", IMG_NULL, &sVal))
                    {
                        if(sVal.bVal)
                        {
                            bOverwriteTag = IMG_TRUE;
                            ui32TagValue = psStrUnit->psPictHdrInfo->bField;
                        }
                    }
                }
                break;

            default:
                /* Sequence/picture headers should only be attached to corresponding units. */
                IMG_ASSERT(psStrUnit->psSequHdrInfo == IMG_NULL);
                IMG_ASSERT(psStrUnit->psPictHdrInfo == IMG_NULL);
                break;
            }

            if (bProcessStrUnit)
            {
                // Commit to processing this stream unit by removing it from the pending list.
                psProcStrUnit = RESOURCE_ListRemoveHead(&psSchStrCtx->sStrUnitList);
                IMG_ASSERT(psProcStrUnit == psStrUnit);
                if (psProcStrUnit != psStrUnit)
                {
                    return IMG_ERROR_UNEXPECTED_STATE;
                }

                psSchStrCtx->sSchStatus.eNextStrUnitType = psProcStrUnit->eStrUnitType;

                /* Update stop flags with the current stream unit information
                   and stop point requests.
                   NOTE: this must be done before processing unit since it
                   might be freed before returning from the callback. */
                ui32Result = scheduler_SetStopInfo(psSchStrCtx, psProcStrUnit);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (psSchStrCtx->sStopInfo.ui32StopFlags)
                {
                    /* Extract the tag from the stream unit for use in the stop. */
                    pvTag = psProcStrUnit->pvStrUnitTag;
                }

                psProcStrUnit->bDecode = psSchStrCtx->bDecode;

                ui32Result = psSchCtx->pfnCompCallback(
                    SCHEDULER_CB_PROCESS_UNIT,
                    psSchCtx->pvCompInitUserData,
                    IMG_NULL,
                    psSchStrCtx->pvStreamUserData,
                    psProcStrUnit);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
                bScheduled = IMG_TRUE;
            }

            if (psSchStrCtx->sStopInfo.ui32StopFlags & psSchStrCtx->ui32ActiveStopFlags)
            {
                IMG_RESULT ui32LocalResult;

                /* Overwrite pvTag for random scale test. */
                if(bOverwriteTag)
                {
                    pvTag = (IMG_PVOID)(IMG_UINTPTR)ui32TagValue;
                    bOverwriteTag = IMG_FALSE;
                }

                ui32LocalResult = scheduler_StreamStop(psSchStrCtx, pvTag);
                IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
                if (ui32LocalResult != IMG_SUCCESS)
                {
                    return ui32LocalResult;
                }
            }

            if (ui32Result == IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE ||
                ui32Result == IMG_ERROR_NOT_SUPPORTED)
            {
                // Resources are not available or unsupported.
                // Try another stream without carrying result forward.
                ui32Result = IMG_SUCCESS;
                break;
            }

            psStrUnit = RESOURCE_ListPeekHead(&psSchStrCtx->sStrUnitList);
        }

        psSchStrCtx = LST_next(psSchStrCtx);
    }

    // Do APM if nothing was Scheduled
    // through the streams, and see if anything was scheduled at all. If nothing was scheduled on any stream
    // we try to shutdown cores with nothing in their pending queues.
    if(!bScheduled && psSchCtx->bAPM)
    {
        /* Try to do active power management by turning off cores with no queues of pending pictures. */
        ui32Result = psSchCtx->pfnCompCallback(
            SCHEDULER_CB_ACTIVE_POWER_DOWN,
            psSchCtx->pvCompInitUserData,
            IMG_NULL,
            IMG_NULL,
            IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    return ui32Result;
}



/*!
******************************************************************************

 @Function              SCHEDULER_StreamCreate

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamCreate(
    IMG_HANDLE             hSchCtx,
    IMG_UINT32             ui32StrId,
    VDEC_sStrConfigData *  psStrConfig,
    IMG_VOID *             pvStrUserData,
    IMG_HANDLE *           phSchStrCtx
)
{
    scheduler_sContext * psSchCtx = (scheduler_sContext*)hSchCtx;
    scheduler_sStreamCtx *  psSchStrCtx = IMG_NULL;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != hSchCtx);
    IMG_ASSERT(IMG_NULL != psStrConfig);
    IMG_ASSERT(IMG_NULL != phSchStrCtx);

    if(hSchCtx == IMG_NULL ||
        psStrConfig == IMG_NULL ||
        phSchStrCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Allocate the new stream context. */
    VDEC_MALLOC(psSchStrCtx);
    if(IMG_NULL == psSchStrCtx)
    {
        REPORT(REPORT_MODULE_SCHEDULER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to allocate memory for Scheduler stream context",
               psStrConfig->ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psSchStrCtx);

    /* Setup the stream context. */
    psSchStrCtx->pvStreamUserData = pvStrUserData;
    psSchStrCtx->sStreamConfig = *psStrConfig;
    psSchStrCtx->ui32StrId = ui32StrId;
    psSchStrCtx->psSchCtx = psSchCtx;

    /* Initialise all the lists. */
    LST_init(&psSchStrCtx->sPictBufferList);
    LST_init(&psSchStrCtx->sPictResList);
    LST_init(&psSchStrCtx->sSequHdrList);
    LST_init(&psSchStrCtx->sStrUnitList);

    /* Set the default behaviour on errors. */
    IMG_MEMCPY(psSchStrCtx->aStopOnStrUnitError,
               aStopOnStrUnitErrorDefault,
               sizeof(psSchStrCtx->aStopOnStrUnitError));

    /* Start scheduler in the stopped state. */
    psSchStrCtx->bStopped = IMG_TRUE;

    /* Add the stream context to the list. */
    LST_add(&psSchCtx->sStrCtxList, (IMG_VOID *)psSchStrCtx);

    *phSchStrCtx = psSchStrCtx;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamDestroy

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamDestroy(
    IMG_HANDLE  hSchStrCtx
)
{
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;
    IMG_UINT32              ui32Result;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    if(psSchStrCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (!LST_empty(&psSchStrCtx->sStrUnitList))
    {
        // Try and empty the list. Since this function is tearing down the Scheduler stream,
        // test result using assert and continue to tidy-up as much as possible.
        ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sStrUnitList,
                                        IMG_FALSE,
                                        (RESOURCE_pfnFreeItem)scheduler_FreeStreamUnit,
                                        psSchStrCtx);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    if (!LST_empty(&psSchStrCtx->sPictBufferList))
    {
        // Try and empty the list. Since this function is tearing down the Scheduler stream,
        // test result using assert and continue to tidy-up as much as possible.
        ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sPictBufferList, IMG_TRUE, IMG_NULL, IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    if (!LST_empty(&psSchStrCtx->sPictResList))
    {
        // Try and empty the list. Since this function is tearing down the Scheduler stream,
        // test result using assert and continue to tidy-up as much as possible.
        ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sPictResList, IMG_TRUE, IMG_NULL, IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    if (!LST_empty(&psSchStrCtx->sSequHdrList))
    {
        // Try and empty the list. Since this function is tearing down the Scheduler stream,
        // test result using assert and continue to tidy-up as much as possible.
        ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sSequHdrList, IMG_FALSE, IMG_NULL, IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    /* Remove the stream context from the list. */
    LST_remove(&psSchStrCtx->psSchCtx->sStrCtxList, (IMG_VOID *)psSchStrCtx);

    /* Free the stream context. */
    IMG_FREE(psSchStrCtx);

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              SCHEDULER_StreamPlay

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamPlay(
    IMG_HANDLE                    hSchStrCtx,
    VDEC_ePlayMode                ePlayMode,
    VDEC_eStopPoint               eStopPoint,
    const VDECDD_sDdPictBuf     * psDispPictBuf,
    const VDEC_sStrOutputConfig * psOutputConfig
)
{
    scheduler_sStreamCtx * psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;
    scheduler_sContext * psSchCtx;
    IMG_RESULT ui32Result;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    if(psSchStrCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(eStopPoint < VDEC_STOPPOINT_MAX);

    psSchCtx = psSchStrCtx->psSchCtx;

    // Update the stop stop for this stream.
    psSchStrCtx->eCurrentStopPoint = eStopPoint;

    if (!psSchStrCtx->bStopped)
    {
        /* Update the sensitivity to stop conditions every time. */
        scheduler_SetActiveStopFlags(
            IS_DECODING(psSchStrCtx->ePlayMode, psSchCtx->eDecodeLevel),
            eStopPoint,
            psSchStrCtx->aStopOnStrUnitError,
            &psSchStrCtx->ui32ActiveStopFlags);
    }
    else
    {
        // Can only change the play mode when stopped.
        psSchStrCtx->ePlayMode = ePlayMode;

        psSchStrCtx->bDecode = IMG_FALSE;
        if (IS_DECODING(psSchStrCtx->ePlayMode, psSchCtx->eDecodeLevel))
        {
            psSchStrCtx->bDecode = IMG_TRUE;
        }

        // Only when stopped take the latest output configuration.
        if (psDispPictBuf && psOutputConfig)
        {
            IMG_ASSERT(psDispPictBuf->psPictBuf == IMG_NULL);

            if (IMG_MEMCMP(&psSchStrCtx->sOutputConfig, psOutputConfig, sizeof(psSchStrCtx->sOutputConfig)) ||
                IMG_MEMCMP(&psSchStrCtx->sDispPictBuf, psDispPictBuf, sizeof(psSchStrCtx->sDispPictBuf)))
            {
                psSchStrCtx->bNewOutputConfig = IMG_TRUE;
            }

            psSchStrCtx->sDispPictBuf = *psDispPictBuf;
            psSchStrCtx->sOutputConfig = *psOutputConfig;

            psSchStrCtx->bOutputConfigSet = IMG_TRUE;
        }
        else
        {
            psSchStrCtx->bOutputConfigSet = IMG_FALSE;

            // Must not be decoding without output configuration.
            IMG_ASSERT(ePlayMode == VDEC_PLAYMODE_PARSE_ONLY);
        }

        ui32Result = scheduler_StoreState(psSchStrCtx);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        /* Prepare to resume processing bitstream by performing any
           outstanding operations and updating the stop status. */
        ui32Result = scheduler_PrepareToPlay(psSchStrCtx);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        /* Update the sensitivity to stop conditions every time. */
        scheduler_SetActiveStopFlags(
            psSchStrCtx->bDecode,
            eStopPoint,
            psSchStrCtx->aStopOnStrUnitError,
            &psSchStrCtx->ui32ActiveStopFlags);

        // Check for any outstanding stop status which might prevent playing.
        if (psSchStrCtx->sStopInfo.ui32StopFlags & psSchStrCtx->ui32ActiveStopFlags)
        {
            ui32Result = scheduler_StreamStop(psSchStrCtx, IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
        else
        {
            if ((psSchStrCtx->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_FENCE) == 0)
            {
                IMG_ASSERT((psSchStrCtx->sStopInfo.ui32StopFlags & psSchStrCtx->ui32ActiveStopFlags) == 0);
            }

            /* If the stop condition has not been determined. */
            if (eStopPoint != VDEC_STOPPOINT_NOW)
            {
                /* ...change the status of the stream. */
                psSchStrCtx->bStopped = IMG_FALSE;

                // Schedule the next stream unit.
                ui32Result = SCHEDULER_Run((IMG_HANDLE)psSchCtx, IMG_NULL);
                IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
            }
        }
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamStop

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamStop(
    IMG_HANDLE       hSchStrCtx,
    VDEC_eStopPoint  eStopPoint,
    IMG_UINT32       ui32Error
)
{
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;
    IMG_RESULT eResult;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    if(psSchStrCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(eStopPoint < VDEC_STOPPOINT_MAX);

    if (!psSchStrCtx->bStopped)
    {
        psSchStrCtx->eCurrentStopPoint = eStopPoint;

        scheduler_SetActiveStopFlags(psSchStrCtx->bDecode,
                                     eStopPoint,
                                     psSchStrCtx->aStopOnStrUnitError,
                                     &psSchStrCtx->ui32ActiveStopFlags);

        if (psSchStrCtx->eCurrentStopPoint == VDEC_STOPPOINT_NOW)
        {
            psSchStrCtx->sStopInfo.ui32Error = ui32Error;

            eResult = scheduler_StreamStop(psSchStrCtx, IMG_NULL);
            IMG_ASSERT_TESTED(eResult == IMG_SUCCESS);
            if (eResult != IMG_SUCCESS)
            {
                return eResult;
            }
        }
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamSignalStopStatus

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamSignalStopStatus(
    IMG_HANDLE      hSchStrCtx,
    IMG_UINT32      ui32StopFlags,
    IMG_UINT32    * pui32StopFlags
)
{
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    if(psSchStrCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (pui32StopFlags)
    {
        // Check that external stop flags are in sync with those in Scheduler.
        IMG_ASSERT(*pui32StopFlags == psSchStrCtx->sStopInfo.ui32StopFlags);
    }

    psSchStrCtx->sStopInfo.ui32StopFlags |= ui32StopFlags;

    if (pui32StopFlags)
    {
        *pui32StopFlags = psSchStrCtx->sStopInfo.ui32StopFlags;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamAddUnit

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamAddUnit(
    IMG_HANDLE         hSchStrCtx,
    VDECDD_sStrUnit *  psStrUnit
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    IMG_ASSERT(IMG_NULL != psStrUnit);

    if(psSchStrCtx == IMG_NULL ||
        psStrUnit == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Add the stream unit in the input queue. */
    ui32Result = RESOURCE_ListAdd(
        &psSchStrCtx->sStrUnitList,
        psStrUnit,
        0,
        IMG_NULL);

    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to add resource",
               psSchStrCtx->sStreamConfig.ui32UserStrId);
        return ui32Result;
    }

    ui32Result = SCHEDULER_Run((IMG_HANDLE)psSchStrCtx->psSchCtx, IMG_NULL);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);

    return ui32Result;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamAddPictureBuffer

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamAddPictureBuffer(
    IMG_HANDLE              hSchStrCtx,
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    IMG_ASSERT(IMG_NULL != psDdBufMapInfo);
    
    if (psSchStrCtx == IMG_NULL ||
        psDdBufMapInfo == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Add the image buffer to the list. */
    ui32Result = RESOURCE_ListAdd(
        &psSchStrCtx->sPictBufferList,
        psDdBufMapInfo,
        0,
        &psDdBufMapInfo->sDdBufInfo.ui32RefCount);

    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to add resource",
               psSchStrCtx->sStreamConfig.ui32UserStrId);
    }

    SCHEDULER_Run((IMG_HANDLE)psSchStrCtx->psSchCtx, IMG_NULL);

    return ui32Result;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamAddPictureResource

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamAddPictureResource(
    IMG_HANDLE            hSchStrCtx,
    VDECDD_sPictResInt *  psPictResInt
)
{
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    IMG_ASSERT(IMG_NULL != psPictResInt);
    if (psSchStrCtx == IMG_NULL ||
        psPictResInt == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Add the internal picture resources to the list. */
    ui32Result = RESOURCE_ListAdd(
        &psSchStrCtx->sPictResList,
        psPictResInt,
        0,
        &psPictResInt->ui32RefCount);

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to add resource",
               psSchStrCtx->sStreamConfig.ui32UserStrId);

        return ui32Result;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamRemovePictureBuffer

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamRemovePictureBuffer(
    IMG_HANDLE              hSchStrCtx,
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo
)
{
    IMG_RESULT ui32Result;
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    IMG_ASSERT(IMG_NULL != psDdBufMapInfo);
    if (psSchStrCtx == IMG_NULL ||
        psDdBufMapInfo == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Remove picture buffer from the list. */
    ui32Result = RESOURCE_ListRemove(
        &psSchStrCtx->sPictBufferList,
        psDdBufMapInfo);

    //IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE is a valid return code
    //e.g. during reconfigure we are clearing the sPictBufferList list
    //and then try to remove the buffers again from the same list (empty now)
    //though core UNMAP_BUF messages
    if(IMG_SUCCESS != ui32Result && IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to remove picture buffer",
               psSchStrCtx->sStreamConfig.ui32UserStrId);
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamRemovePictureResource

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamRemovePictureResource(
    IMG_HANDLE            hSchStrCtx,
    VDECDD_sPictResInt *  psPictResInt
)
{
    IMG_UINT32 ui32Result;
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    IMG_ASSERT(IMG_NULL != psPictResInt);

    if (psSchStrCtx == IMG_NULL ||
        psPictResInt == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Remove picture resource from the list. */
    ui32Result = RESOURCE_ListRemove(
        &psSchStrCtx->sPictResList,
        psPictResInt);

    //IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE is a valid return code
    //e.g. during reconfigure we are clearing the sPictBufferList list
    //and then try to remove the buffers again from the same list (empty now)
    //though core UNMAP_BUF messages
    if(IMG_SUCCESS != ui32Result && IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to remove picture resource",
               psSchStrCtx->sStreamConfig.ui32UserStrId);
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamReleaseBuffers

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamReleaseBuffers(
    IMG_HANDLE     hSchStrCtx,
    VDEC_eBufType  eBufType
)
{
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;
    IMG_UINT32              ui32Result = IMG_SUCCESS;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psSchStrCtx);
    IMG_ASSERT(eBufType < VDEC_BUFTYPE_MAX);
    if (psSchStrCtx == IMG_NULL ||
        eBufType >= VDEC_BUFTYPE_MAX)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    switch(eBufType)
    {
        case VDEC_BUFTYPE_PICTURE:
        {
            /* Empty all the decoded picture related buffer lists. */
            ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sPictBufferList, IMG_TRUE, IMG_NULL, IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            break;
        }
        case VDEC_BUFTYPE_BITSTREAM:
        {
            /* Empty the stream unit queue. */
            ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sStrUnitList,
                                            IMG_FALSE,
                                            (RESOURCE_pfnFreeItem)scheduler_FreeStreamUnit,
                                            psSchStrCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            break;
        }
        case VDEC_BUFTYPE_ALL:
        {
            /* Empty all the decoded picture related buffer lists. */
            ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sPictBufferList, IMG_TRUE, IMG_NULL, IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);

            /* Empty the stream unit queue. */
            ui32Result = RESOURCE_ListEmpty(&psSchStrCtx->sStrUnitList,
                                            IMG_FALSE,
                                            (RESOURCE_pfnFreeItem)scheduler_FreeStreamUnit,
                                            psSchStrCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            break;
        }
        default:
        {
            ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            IMG_ASSERT(IMG_FALSE);
            break;
        }
    }

error:
    return ui32Result;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamSetBehaviourOnErrors

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamSetBehaviourOnErrors(
    IMG_HANDLE           hSchStrCtx,
    VDEC_eErrorHandling  eErrorHandling
)
{
    scheduler_sStreamCtx * psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;
    IMG_UINT32 ui32I;

    IMG_ASSERT(hSchStrCtx);
    if (hSchStrCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (VDEC_ERROR_HANDLING_IGNORE_ALL == eErrorHandling)
    {
        /* Set all the errors to be ignored. */
        for (ui32I = 0; ui32I < VDECDD_STRUNIT_MAX; ui32I++)
        {
            psSchStrCtx->aStopOnStrUnitError[ui32I].bStop = IMG_FALSE;
        }
    }
    else if (VDEC_ERROR_HANDLING_STOP_ON_ALL & eErrorHandling)
    {
        /* Configure to stop on all errors. */
        for (ui32I = 0; ui32I < VDECDD_STRUNIT_MAX; ui32I++)
        {
            psSchStrCtx->aStopOnStrUnitError[ui32I].bStop = IMG_TRUE;
        }
    }
    else
    {
        if (VDEC_ERROR_HANDLING_STOP_ON_SEQUENCE & eErrorHandling)
        {
            /* Configure to stop on sequence errors. */
            for (ui32I = 0; ui32I < VDECDD_STRUNIT_MAX; ui32I++)
            {
                if (ERROR_SCOPE_SEQUENCE == psSchStrCtx->aStopOnStrUnitError[ui32I].eErrScope)
                {
                    psSchStrCtx->aStopOnStrUnitError[ui32I].bStop = IMG_TRUE;
                }
            }
        }
        if (VDEC_ERROR_HANDLING_STOP_ON_PICTURE & eErrorHandling)
        {
            /* Configure to stop on picture errors. */
            for (ui32I = 0; ui32I < VDECDD_STRUNIT_MAX; ui32I++)
            {
                if (ERROR_SCOPE_PICTURE == psSchStrCtx->aStopOnStrUnitError[ui32I].eErrScope)
                {
                    psSchStrCtx->aStopOnStrUnitError[ui32I].bStop = IMG_TRUE;
                }
            }
        }
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamGetStatus

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamGetStatus(
    IMG_HANDLE              hSchStrCtx,
    VDECDD_sSchStrStatus *  psSchStrStatus
)
{
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;
    VDECDD_sStrUnit * psStrUnit;

    IMG_ASSERT(hSchStrCtx);
    IMG_ASSERT(psSchStrStatus);
    if (hSchStrCtx == IMG_NULL ||
        psSchStrStatus == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psSchStrCtx->sSchStatus.bCanSchedule = IMG_FALSE;

    psStrUnit = RESOURCE_ListPeekHead(&psSchStrCtx->sStrUnitList);
    if (psStrUnit)
    {
        psSchStrCtx->ui32Avail = scheduler_GetResourceAvailability(psSchStrCtx);

        if (psStrUnit->eStrUnitType != VDECDD_STRUNIT_PICTURE_START ||
            psSchStrCtx->ePlayMode == VDEC_PLAYMODE_PARSE_ONLY ||
            psSchStrCtx->psSchCtx->eDecodeLevel <= VDECDD_DECODELEVEL_SCHEDULER ||
                ((psSchStrCtx->ui32Avail & SCHEDULER_AVAIL_CORE) &&
                    (((psSchStrCtx->ui32Avail & SCHEDULER_AVAIL_PICTBUF) &&
                      (psSchStrCtx->ui32Avail & SCHEDULER_AVAIL_PICTRES)))))
        {
            psSchStrCtx->sSchStatus.bCanSchedule = (psSchStrCtx->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_RECONFIGURE) ? IMG_FALSE : IMG_TRUE;
        }

        // If there is a picture that cannot be decoded at the moment.
        if (psStrUnit->ui32Features)
        {
            IMG_UINT32 ui32Result;

            // Obtain the avail/min load of cores that can decode the stream with the current features
            ui32Result = DECODER_GetLoad(psSchStrCtx->psSchCtx->hDecCtx,
                                         psStrUnit->ui32Features,
                                         &psSchStrCtx->sSchStatus.ui32MinAvailLoad,
                                         &psSchStrCtx->sSchStatus.ui32MinLoad);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            psSchStrCtx->sSchStatus.ui32Features = psStrUnit->ui32Features;
        }
    }

    /* Update status from other stream state. */
    psSchStrCtx->sSchStatus.ui32NumPict                   = RESOURCE_GetNumPict(&psSchStrCtx->sStrUnitList);
    psSchStrCtx->sSchStatus.ui32NumAvailImageBuffers      = RESOURCE_ListGetNumAvail(&psSchStrCtx->sPictBufferList);
    psSchStrCtx->sSchStatus.ui32NumImageBuffers           = RESOURCE_ListGetNum(&psSchStrCtx->sPictBufferList);
    psSchStrCtx->sSchStatus.ui32NumAvailInternalResources = RESOURCE_ListGetNumAvail(&psSchStrCtx->sPictResList);
    psSchStrCtx->sSchStatus.ui32NumInternalResources      = RESOURCE_ListGetNum(&psSchStrCtx->sPictResList);
    if (psStrUnit)
    {
        psSchStrCtx->sSchStatus.eNextStrUnitType = psStrUnit->eStrUnitType;
    }
    else
    {
        psSchStrCtx->sSchStatus.eNextStrUnitType = VDECDD_STRUNIT_MAX;
    }
    psSchStrCtx->sSchStatus.ePlayMode         = psSchStrCtx->ePlayMode;
    psSchStrCtx->sSchStatus.eCurrentStopPoint = psSchStrCtx->eCurrentStopPoint;
    psSchStrCtx->sSchStatus.bStopped          = psSchStrCtx->bStopped;
    psSchStrCtx->sSchStatus.ui32StopFlags     = psSchStrCtx->sStopInfo.ui32StopFlags;
    psSchStrCtx->sSchStatus.bConfigured       = (psSchStrCtx->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_RECONFIGURE) ? IMG_FALSE : IMG_TRUE;

    psSchStrCtx->sSchStatus.ui32Avail = psSchStrCtx->ui32Avail;

    *psSchStrStatus = psSchStrCtx->sSchStatus;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              SCHEDULER_StreamGetPictBufNum

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamGetNumImageBuffers(
    IMG_HANDLE    hSchStrCtx,
    IMG_UINT32 *  pui32NumImageBuffers
)
{
    scheduler_sStreamCtx *  psSchStrCtx = (scheduler_sStreamCtx *)hSchStrCtx;

    *pui32NumImageBuffers = RESOURCE_ListGetNum(&psSchStrCtx->sPictBufferList);

    return IMG_SUCCESS;
}

