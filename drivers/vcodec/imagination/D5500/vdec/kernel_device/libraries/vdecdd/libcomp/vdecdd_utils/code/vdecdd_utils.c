/*!
 *****************************************************************************
 *
 * @File       vdecdd_utils.c
 * @Title      VDEC Utilities
 * @Description    This file contains the VDEC utitlities compiled into user and kernel mode.
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

#include "vdecdd_utils.h"


/*!
******************************************************************************

 @Function              VDECDDUTILS_FreeStrUnit

 ******************************************************************************/
IMG_RESULT VDECDDUTILS_FreeStrUnit(
    VDECDD_sStrUnit * psStrUnit
)
{
    BSPP_sBitStrSeg * psBitStrSeg;

    /* Loop over bit stream segments...*/
    psBitStrSeg = (BSPP_sBitStrSeg *)LST_removeHead(&psStrUnit->sBitStrSegList);
    while (psBitStrSeg != IMG_NULL)
    {
        /* Free segment. */
        IMG_FREE(psBitStrSeg);

        /* Get next segment. */
        psBitStrSeg = (BSPP_sBitStrSeg *)LST_removeHead(&psStrUnit->sBitStrSegList);
    }

    /* Free the sequence header...*/
    if (psStrUnit->psSequHdrInfo != IMG_NULL)
    {
        psStrUnit->psSequHdrInfo->ui32RefCount--;
        if (psStrUnit->psSequHdrInfo->ui32RefCount == 0)
        {
            IMG_FREE(psStrUnit->psSequHdrInfo);
            psStrUnit->psSequHdrInfo = IMG_NULL;
        }
    }

    /* Free the picture header... */
    if (psStrUnit->psPictHdrInfo != IMG_NULL)
    {
        if (psStrUnit->psPictHdrInfo->sPictSgmData.pvData)
        {
            IMG_FREE(psStrUnit->psPictHdrInfo->sPictSgmData.pvData);
            psStrUnit->psPictHdrInfo->sPictSgmData.pvData = IMG_NULL;
        }

        IMG_FREE(psStrUnit->psPictHdrInfo);
        psStrUnit->psPictHdrInfo = IMG_NULL;
    }

    /* Free stream unit. */
    IMG_FREE(psStrUnit);
    psStrUnit = IMG_NULL;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VDECDDUTILS_CreateStrUnit

 @Description           this function allocate a structure for a complete data unit

******************************************************************************/
IMG_RESULT VDECDDUTILS_CreateStrUnit(
    VDECDD_sStrUnit    ** ppsStrUnit,
    LST_T               * sBSList
)
{
    VDECDD_sStrUnit    * psStrUnit;
    BSPP_sBitStrSeg  * psBitStrSeg;

    VDEC_MALLOC(psStrUnit);
    IMG_ASSERT(psStrUnit != IMG_NULL);
    if (psStrUnit == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psStrUnit);
    if (sBSList != IMG_NULL)
    {
        // copy BS list to this list
        LST_init(&psStrUnit->sBitStrSegList);
        for ( psBitStrSeg = LST_first( sBSList); psBitStrSeg != NULL;   psBitStrSeg = LST_first(sBSList) )
        {
            psBitStrSeg = LST_removeHead(sBSList);
            LST_add(&psStrUnit->sBitStrSegList,psBitStrSeg);
        }
    }

    *ppsStrUnit = psStrUnit;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECDDUTILS_CreateStrUnitOld

 @Description           this function allocate a structure for a complete data unit


******************************************************************************/
IMG_RESULT VDECDDUTILS_CreateStrUnitOld(
    VDECDD_sStrUnit    ** ppsStrUnit,
    BSPP_sSequHdrInfo   * psSeqInfo,
    BSPP_sPictHdrInfo   * psPicInfo,
    LST_T               * sBSList
)
{
    VDECDD_sStrUnit    * psStrUnit;
    BSPP_sBitStrSeg  * psBitStrSeg;

    VDEC_MALLOC(psStrUnit);
    IMG_ASSERT(psStrUnit != IMG_NULL);
    if (psStrUnit == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psStrUnit);
    if (sBSList != IMG_NULL)
    {
        // copy BS list to this list
        LST_init(&psStrUnit->sBitStrSegList);
        for ( psBitStrSeg = LST_first( sBSList); psBitStrSeg != NULL;   psBitStrSeg = LST_first(sBSList) )
        {
            psBitStrSeg = LST_removeHead(sBSList);
            LST_add(&psStrUnit->sBitStrSegList,psBitStrSeg);
        }

    }
    if(psSeqInfo !=IMG_NULL)
    {
        psStrUnit->psSequHdrInfo = psSeqInfo;
        psStrUnit->psSequHdrInfo->ui32RefCount = 1;
    }
    psStrUnit->psPictHdrInfo = psPicInfo;
    *ppsStrUnit = psStrUnit;

    return IMG_SUCCESS;
}
