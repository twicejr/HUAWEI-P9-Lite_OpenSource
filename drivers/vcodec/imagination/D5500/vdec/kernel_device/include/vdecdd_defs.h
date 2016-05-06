/*!
 *****************************************************************************
 *
 * @File       vdecdd_defs.h
 * @Title      VDEC Device Driver.
 * @Description    This file contains the header file information for the
 *  VDEC Device User Mode interface.
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

#if !defined (__VDECDD_DEFS_H__)
#define __VDECDD_DEFS_H__

#include <img_defs.h>



#if defined(__cplusplus)
extern "C" {
#endif


/*!
******************************************************************************
 This type defines the VDECDD events.
 @brief  VDECDD Callback Events
******************************************************************************/
typedef enum
{
    VDECDD_EVENT_STREAM_STOPPED,  /*!< The stream has stopped decoding in response to reaching the
                                       stop point defined in the call to a VDEC_StreamPlay() or
                                       a call to VDEC_StreamStop().                                          */

   VDECDD_EVENT_BSTRINTERNAL_EMPTY,  /*!< Used to pass/return internal (belonging to vdec_api) bit stream
                                        buffers when they are empty.
                                        \n NOTE: pvBufCbParam is valid for this event.
                                        \n NOTE: pvParam parameter contains the address of a #VDEC_sDefragmentedBufInfo */

    VDECDD_EVENT_BSTRBUF_EMPTY,   /*!< Used to pass/return a bit stream buffers when they are empty.
                                       \n NOTE: pvBufCbParam is valid for this even.
                                       \n NOTE: pvParam parameter contains the address of a #VDEC_sBufInfo
                                       Information must be copied from this structure before returning
                                       from the callback function.                                           */

    VDECDD_EVENT_PICTBUF_FULL,    /*!< A picture has been decoded and now presented for display.
                                       \n NOTE: pvBufCbParam is valid for this even.
                                       \n NOTE: pvParam paramater contains the address of a #VDEC_sDecPictInfo
                                       Information must be copied from this structure before returning
                                       from the callback function.                                           */

    VDECDD_EVENT_STREAM_FLUSHED,  /*!< The stream has been flushed of all display pictures in response to
                                       asynchronous function VDEC_StreamFlushOutput.                         */

    VDECDD_EVENT_PICTURE_DECODED, /*!< A picture has been decoded, passes info for BSPP                      */

    VDECDD_EVENT_MAX,             /*!< Max. "normal" event.                                                  */

} VDECDD_eEvent;

/*!
******************************************************************************
 This type defines the Bitstream Segment type.
 @brief  Bitstream segment type
******************************************************************************/
typedef enum
{
    VDECDD_BSSEG_LASTINBUFF        = (1<<0),                            /*!< Segment is last in buffer.                                         */
    VDECDD_BSSEG_SKIP              = (1<<1),                            /*!< Skip this segment (i.e. do not pass to the hardware).              */
    VDECDD_BSSEG_INSERTSCP         = (1<<2),                            /*!< Insert SCP before this bitstream segment.                          */
    VDECDD_BSSEG_INSERT_STARTCODE  = (1<<3) | VDECDD_BSSEG_INSERTSCP,   /*!< Insert start code with suffix before this bitstream segment
                                                                             as defined in VDECDD_sBitStrSeg.ui8StartCodeSuffix                 */

} VDECDD_eBitStrSegType;


/*!
******************************************************************************
 This type defines the stream unit type.
 @brief  Stream Unit Type
******************************************************************************/
typedef enum
{
    VDECDD_STRUNIT_ANONYMOUS = 0,   /*!< Arbitrary bitstream data with no specific meaning. Used to propagate buffers 
                                         without any side-effect.                                                           */
    VDECDD_STRUNIT_SEQUENCE_START,  /*!< Video sequence header new/changed.                                                 */
    VDECDD_STRUNIT_CLOSED_GOP,      /*!< Closed GOP: subsequent pictures no longer refer to any previously decoded.         */
    VDECDD_STRUNIT_SEQUENCE_END,    /*!< End of sequence with implicit display/reference list flush. A sequence "ends" when
                                         signalled in bitstream (e.g. closed GOP) or frame properties change such that
                                         references are no longer suitable for future frames.                               */
    VDECDD_STRUNIT_PICTURE_PORTENT, /*!< This stream unit may precede #VDECDD_STRUNIT_PICTURE_START or
                                         #VDECDD_STRUNIT_PICTURE_FRAG unit in case there's any important information about
                                         the following picture to be communicated to the KM before the picture itself
                                         can be processed. This includes info about any BSPP errors encountered in picture
                                         related bitstream units while parsing them.                                        */
    VDECDD_STRUNIT_PICTURE_START,   /*!< Start of picture (new resources required for decode).                              */
    VDECDD_STRUNIT_PICTURE_END,     /*!< End of picture.                                                                    */
    VDECDD_STRUNIT_PICTURE_FRAG,    /*!< Picture fragment. Bitstream data associated with the pending picture marked by 
                                         previous #VDECDD_STRUNIT_PICTURE_START.                                            */
    VDECDD_STRUNIT_FENCE,           /*!< Generates a stop and returns a tag provided to driver by function 
                                         VDEC_StreamInsertFence().                                                          */
    VDECDD_STRUNIT_STOP,            /*!< Used to cause the KM to stop.                                                      */

    VDECDD_STRUNIT_MAX,

} VDECDD_eStrUnitType;


#if defined(__cplusplus)
}
#endif

#endif /* __VDECDD_H__    */

