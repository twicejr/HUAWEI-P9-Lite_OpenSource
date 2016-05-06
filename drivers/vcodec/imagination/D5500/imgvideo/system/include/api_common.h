/*!
 *****************************************************************************
 *
 * @File       api_common.h
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

#if !defined (__API_COMMON_H__)
#define __API_COMMON_H__

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
******************************************************************************

This type defines the API Ids for remote callbacks.

******************************************************************************/
typedef enum
{
    API_ID_TEST = 0x01,             //!< TEST is a dummy API used by tests to log events
    API_ID_BFM,                     //!< BFM API Id
    API_ID_SMDEC,                   //!< SMDEC API Id
	API_ID_SMHDP,                   //!< SMHDP API Id
    API_ID_SMADEC,                  //!< SMADEC API Id
    API_ID_SMVDEC,                  //!< SMVDEC API Id
    API_ID_SMVOUT,                  //!< SMVOUT API Id
    API_ID_SMAOUT,                  //!< SMAOUT API Id
    API_ID_TSD,                     //!< TSD API Id
    API_ID_RCBA,                    //!< RCBA API Id
    API_ID_RCBB,                    //!< RCBB API Id
    API_ID_RCBC,                    //!< RCBB API Id
    API_ID_RMEM,                    //!< RMEM API Id
    API_ID_ITC,                     //!< ITC API Id
    API_ID_ISR,                     //!< ISR API Id
    API_ID_ENDDRV,                  //!< ENDDRV API Id
    API_ID_MEOSAL,                  //!< MEOSAL API Id
    API_ID_AUD,                     //!< AUD API Id
    API_ID_DIGO,                    //!< DIGO API Id
    API_ID_VPIN,                    //!< VPIN API Id
    API_ID_PDP,						//!< PDP API Id
#ifdef __ITC_TEST__
    API_ID_thread3,                  //!< thread3 Id
    API_ID_thread2,                  //!< thread2 Id
#endif
	API_ID_SCB,						//!< SCB API Id
	API_ID_BLIT,					//!< BLIT API Id
	API_ID_DEVIO,					//!< DEVIO Id
    API_ID_MPM,                     //!< MPM API Id
    API_ID_SPIS,					//!< SPI slave API Id
    API_ID_DMAC,					//!< DMAC API Id
    API_ID_DMAC_PERIP,
    API_ID_DMAN,					//!< DMAN API
    API_ID_DMANKM,					//!< DMANKM API
    API_ID_MSVDXDEVICE,				//!< MSVDX Device
    API_ID_TOPAZDEVICE,				//!< TOPAZ Device
    API_ID_PALLOC,					//!< PALLOC API
    API_ID_WRAPU,					//!< WRAPU API
    API_ID_SYSBRG,					//!< SYSBRG API
    API_ID_UMP,						//!< UMP API

	API_ID_IPC_UM,					//!< IPC_UM API
	API_ID_PDUMP_CMDS,				//!< PDUMP_CMDS API
	API_ID_DEVICEIO,				//!< DEVICEIO API
	API_ID_DMACDD,					//!< DMAC DEVICE DRIVER API

	API_ID_GDMA,					//!< GDMA API

	API_ID_FAKEDEVICE,              //!< FAKE Device API Id

	API_ID_VDECDD,					//!< VDEC Device Driver API Id
	
	API_ID_BSPP_KM,                 //!< BSPP Id

	API_ID_MEMMGR,
	API_ID_HOSTUTILS,

	API_ID_PFTAL,					//!< Portablity Framework TAL

    API_ID_XBUF,					//!< XBUF Component
    API_ID_IBUF,					//!< IBUF Component
	API_ID_PDPDEVICE,				//!< PDP device API id

    API_ID_DBGOPTBRG,               //!< DBGOPTBRG API
    API_ID_DBGOPTKM,                //!< DBGOPTKM API

    API_ID_DBGEVENT,				//!< DBGEVENT API
    API_ID_DBGEVENTKM,				//!< DBGEVENTKM API

    API_ID_MAX                      //!< Max. API Id.

} SYS_eApiId;

#ifdef __cplusplus
}
#endif

#endif /* __API_COMMON_H__ */
