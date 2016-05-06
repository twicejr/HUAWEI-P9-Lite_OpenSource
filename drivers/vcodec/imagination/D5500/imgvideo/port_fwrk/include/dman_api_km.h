/*!
 *****************************************************************************
 *
 * @File       dman_api_km.h
 * @Title      The Device Manager kernel mode API.
 * @Description    This file contains the header file information for the
 *  Device Manager Kernel Mode API.
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

#if !defined (__DMAN_API_KM_H__)
#define __DMAN_API_KM_H__

#include "dman_api.h"
#include <img_defs.h>
#include <img_types.h>
#include <sysos_api_km.h>

#if defined(__cplusplus)
extern "C" {
#endif

#include <lst.h>

/*!
******************************************************************************
 This type defines the type of connection.
******************************************************************************/
typedef enum
{
	DMAN_CFLAG_EXCLUSIVE = 0x00000001,	//!< Set to ensure that only one process/application has exclusive use of the device
	DMAN_CFLAG_SHARED	 = 0x00000002,	//!< Set to allow mutiple process/application to access the device

} DMANKM_eConnFlags;


/*!
******************************************************************************
 This type defines the device flags which can be combined.
******************************************************************************/
typedef enum
{
	DMAN_DFLAG_PSEUDO_DEVICE = 0x00000001,	//!< Set for Pseudo Devices - devices known to the Device Manager, but not to the SYSDEVKM API

} DMANKM_eDevFlags;

/*!
******************************************************************************
 This type defines the type of disconnection.
******************************************************************************/
typedef enum
{

	DMAN_DCONN_NORMAL,			/*!< Disconnect caused by normal close from applications					*/
	DMAN_DCONN_ABORT,			/*!< Disconnect caused by the application aborting or some other type of
									 failure which has caused the connection to be broken					 */

} DMANKM_eDisconnType;

/*!
******************************************************************************
 This structure contains information filled in by the #DMANKM_pfnDevRegister
 function.
*/
typedef struct DMANKM_tag_sDevRegister DMANKM_sDevRegister;


/*!
******************************************************************************

 @Function              DMANKM_pfnDevRegister

 @Description

 This is the prototype for the device registration callback function.

 NOTE: When this callback is made the #DMANKM_sDevRegister has set to 0/IMG_NULL.
 The callback should setup the fields within the structure as defined in
 #DMANKM_sDevRegister.  Any callback functions within the structure that are
 not setup will not be called.

 @Input		psDevRegister :		A pointer to the device registration structure
								to be filled in.

 @Return    IMG_RESULT :		This function returns either IMG_SUCCESS or an
								error code.

******************************************************************************/
typedef IMG_RESULT (* DMANKM_pfnDevRegister)(
    DMANKM_sDevRegister	*			psDevRegister
);


/*!
******************************************************************************

 @Function              DMANKM_pfnDevInit

 @Description

 This is the prototype for the device initialisation callback function.  This
 callback is made before the first connection callback is made to
 #DMANKM_pfnDevDeinit and should be used to initialise the device.

 NOTE: When a device is initialised an implicit connection is made that
 is separate form the normal application/process connections.  This connection can be
 used to attach components - resource allocator - where the allocation are
 shared across processes/applications.  This connection is accesible via the
 device handle and passed to the #DMANKM_pfnDevDeinit.

 @Input		hDevHandle :		The DMAN device handle for this instance of the
								device.

 @Input		hInitConnHandle :	The DMAN connection handle for the implicit connection.

 @Output	ppvDevInstanceData : A pointer used to return a device specific
								data structure that will be provided or can
								be accessed in subsequent DMAN device callbacks
								or device APIs via the various DMAN handles.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
								error code.

******************************************************************************/
typedef IMG_RESULT (* DMANKM_pfnDevInit)(
	IMG_HANDLE				hDevHandle,
	IMG_HANDLE				hInitConnHandle,
    IMG_VOID **				ppvDevInstanceData
);

/*!
******************************************************************************

 @Function              DMANKM_pfnDevDeinit

 @Description

 This is the prototype for the device deinitialise callback function.  This callback
 is made after the last connection has has been severed by a call to
 DMANKM_DevDisconnectComplete().  The functions should deinitialise the device,
 free off any device specific resources not allocated through a resource allocator
 and leave the device in a state where it can be re-initialised via a call
 to the #DMANKM_pfnDevInit callback.

 NOTE: The device componment is responsible for releasing the device specific
 data structures associated with pvDevInstanceData.

 @Input		hDevHandle :		The DMAN device handle for this instance of the
								device.

 @Input		hInitConnHandle :	The DMAN connection handle for this connection -
								see #DMANKM_pfnDevInit.

 @Input		pvDevInstanceData :	A pointer to the device specific data structure
								returned by the #DMANKM_pfnDevInit function.

 @Return    None.

******************************************************************************/
typedef IMG_VOID (* DMANKM_pfnDevDeinit)(
	IMG_HANDLE				hDevHandle,
	IMG_HANDLE				hInitConnHandle,
    IMG_VOID *				pvDevInstanceData
);

/*!
******************************************************************************

 @Function              DMANKM_fnDevConnect

 @Description

 This is the prototype for the device connect/open callback function and is
 called when a connection is made to the device (a call to DMAN_OpenDevice()
 from user mode).

 @Input		hConnHandle :		The DMAN connection handle for this connection.

 @Input		pvDevInstanceData : A pointer to the device instance data structure
								returned by the #DMANKM_pfnDevInit function.

 @Output	ppvDevConnectionData : A pointer used to return a device connection
								data structure that will be provided or can
								be accessed in subsequent DMAN device callbacks
								or device APIs via the various DMAN handles.

 @Return    IMG_RESULT :		This function returns either IMG_SUCCESS or an
								error code.

******************************************************************************/
typedef IMG_RESULT (* DMANKM_fnDevConnect)(
	IMG_HANDLE				hConnHandle,
    IMG_VOID *				pvDevInstanceData,
    IMG_VOID **				ppvDevConnectionData
);

/*!
******************************************************************************

 @Function              DMANKM_pfnDevDisconnect

 @Description

 This is the prototype for the device disconnect/call callback function and is
 called when a connection is made to the device (a call to DMAN_ClosDevice()
 from user mode or the application terminates for some reason).

 NOTE: The device component is responsible for releasing the connection specific
 data structures associated with pvDevConnectionData.

 NOTE: This function should make either a synchronous call to DMANKM_DevDisconnectComplete()
 or call the function asynchronously when the it is safe to free off any
 associated resources - via callbacks to the attached resource allocators.
 Resource allocators are attached to a device connection using DMANKM_AttachComponent().

 @Input		hConnHandle :		The DMAN connection handle for this connection.

 @Input		pvDevInstanceData :	A pointer to the device instance data structure
								returned by the #DMANKM_pfnDevInit function.

 @Input		pvDevConnectionData : A pointer to the device connection data
								structure returned by the #DMANKM_fnDevConnect function.

 @Input		eDisconnType :		The type of disconnection.

 @Return    IMG_RESULT :		This function returns either IMG_SUCCESS or an
								error code.

******************************************************************************/
typedef IMG_RESULT (* DMANKM_pfnDevDisconnect)(
	IMG_HANDLE				hConnHandle,
    IMG_VOID *				pvDevInstanceData,
    IMG_VOID *				pvDevConnectionData,
	DMANKM_eDisconnType		eDisconnType
);

/*!
******************************************************************************

 @Function              DMANKM_pfnDevKmHisr

 @Description

 This is the prototype for the device Kernel Mode HISR callback function and is
 called when the HISR is activated using DMANKM_ActivateKmHisr().

 @Input		hDevHandle :		The DMAN device handle for this instance of the
								device.

 @Input		pvDevInstanceData :	A pointer to the device instance data structure
								returned by the #DMANKM_pfnDevInit function.

 @Return    None.

******************************************************************************/
typedef IMG_VOID (* DMANKM_pfnDevKmHisr)(
	IMG_HANDLE				hDevHandle,
    IMG_VOID *				pvDevInstanceData
);

/*!
******************************************************************************

 @Function              DMANKM_pfnDevKmLisr

 @Description

 This is the prototype for the device Kernel Mode LISR callback function and is
 called when a device interrupts occurs.

 @Input		hDevHandle :		The DMAN device handle for this instance of the
								device.

 @Input		pvDevInstanceData :	A pointer to the device instance data structure
								returned by the #DMANKM_pfnDevInit function.

 @Return	IMG_BOOL :		IMG_TRUE if the interrupt has been handles by the
							Kernel Mode LISR, otherwise IMG_FALSE.

******************************************************************************/
typedef IMG_BOOL (* DMANKM_pfnDevKmLisr)(
	IMG_HANDLE				hDevHandle,
    IMG_VOID *				pvDevInstanceData
);

/*!
******************************************************************************

 @Function				DMANKM_KmPowerEvent

 @Description

 This DMAN power evnet callback function that which called
 by the underlying OS when a power state change is being made.

 @Input		ePowerTrans :	Indicates whether the call is before or after
							a state transition.

 @Input		ePowerState :	Indicates the state to which or in which the
							power is.

 @Input		pvParam :	Pointer parameter, defined when the
						callback was registered.

 @Return	None.

******************************************************************************/
extern IMG_VOID DMANKM_KmPowerEvent(
	SYSOSKM_ePowerTrans ePowerTrans,
	SYSOSKM_ePowerState ePowerState,
	IMG_VOID *          pvParam
	);

/*!
******************************************************************************

 @Function              DMANKM_pfnDevPowerPreS5

 @Description

 This is the prototype for the device power management callback function for
 entering S5 (off).

 NOTE: The device driver can assume that the device is powered (on) at all
 times EXCEPT between the return from the callback to #DMANKM_pfnDevPowerPreS5
 and before the subsequent callback to #DMANKM_pfnDevPowerPostS0 and that no
 other Device Manager callbacks are made to the device between these two.
 At the appropriate point the device manager makes call to
 SYSDEVKM_SetPowerState() to enable/disable the device power.

 @Input		hDevHandle :		The DMAN device handle for this instance of the
								device.

 @Input		pvDevInstanceData :	A pointer to the device instance data structure
								returned by the #DMANKM_pfnDevInit function.

 @Return    None.

******************************************************************************/
typedef IMG_VOID (* DMANKM_pfnDevPowerPreS5)(
	IMG_HANDLE					hDevHandle,
    IMG_VOID *					pvDevInstanceData
);

/*!
******************************************************************************

 @Function              DMANKM_pfnDevPowerPostS0

 @Description

 This is the prototype for the device power management callback function for
 entering S0 (working - on). See also #DMANKM_pfnDevPowerPreS5.

 @Input		hDevHandle :		The DMAN device handle for this instance of the
								device.

 @Input		pvDevInstanceData :	A pointer to the device instance data structure
								returned by the #DMANKM_pfnDevInit function.

 @Return    None.

******************************************************************************/
typedef IMG_VOID (* DMANKM_pfnDevPowerPostS0)(
	IMG_HANDLE					hDevHandle,
    IMG_VOID *					pvDevInstanceData
);


/*!
******************************************************************************
 This structure contains information filled in by the #DMANKM_pfnDevRegister
 function.

 NOTE: When this callback is made the #DMANKM_sDevRegister has set to 0/IMG_NULL.
 The callback should setup the fields within the structure as defined in
 #DMANKM_sDevRegister.  Any callback functions within the structure that are
 not setup will not be called.

  @brief	This structure contains information filled in by the #DMANKM_pfnDevRegister
 function.
******************************************************************************/
struct DMANKM_tag_sDevRegister
{
    IMG_UINT32                ui32ConnFlags;      //!< Connection flags - see #DMANKM_eConnFlags (default #DMAN_CFLAG_EXCLUSIVE).

	IMG_UINT32				  ui32DevFlags;		  //!< Device flags - see #DMANKM_eDevFlags (default zero)

    DMANKM_pfnDevInit		  pfnDevInit;		  //!< Device initailise function.
    DMANKM_pfnDevDeinit		  pfnDevDeinit;		  //!< Device deinitialise function.

    DMANKM_fnDevConnect		  pfnDevConnect;      //!< Device connect / open function.
    DMANKM_pfnDevDisconnect   pfnDevDisconnect;   //!< Device disconnect / close function.

    DMANKM_pfnDevKmHisr		  pfnDevKmHisr;		  //!< Device Kernel Mode HISR function.
    DMANKM_pfnDevKmLisr		  pfnDevKmLisr;		  //!< Device Kernel Mode LISR function.

	DMANKM_pfnDevPowerPreS5	  pfnDevPowerPreS5;	  //!< Device pre S5 function.
	DMANKM_pfnDevPowerPostS0  pfnDevPowerPostS0;  //!< Device pre S0 function.
};


/*!
******************************************************************************
 This structure contains information filled in by the #DMANKM_pfnCompConnect
 function.
 */
typedef struct DMANKM_tag_sCompAttach DMANKM_sCompAttach;


/*!
******************************************************************************

 @Function              DMANKM_pfnCompAttach

 @Description

 This is the prototype for the component attach callback function.
 This function is called when the component is attached to the a
 device connection using DMANKM_AttachComponent().

 NOTE: When this callback is made the #DMANKM_pfnCompAttach has set to 0/IMG_NULL.
 The callback should setup the fields within the structure as defined in
 #DMANKM_sCompAttach.  Any callback functions within the structure that are
 not setup will not be called.

 @Input     hAttachHandle :     The DMAN connection handle for this attachment.

 @Input     psCompAttach :		A pointer to the component structure
                                to be filled in.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
typedef IMG_RESULT (* DMANKM_pfnCompAttach)(
    IMG_HANDLE				hAttachHandle,
    DMANKM_sCompAttach *	psCompAttach
);


/*!
******************************************************************************

 @Function              DMANKM_pfnCompConnect

 @Description

 This is the prototype for the component connect/open callback function.
 The function is called immediately after the #DMANKM_pfnCompAttach callback.

 NOTE: The two callbacks are to #DMANKM_pfnCompAttach and #DMANKM_pfnCompConnect
 are separated to keep the functional split clean; the first filling in the
 #DMANKM_sCompAttach structure and the second sets up of the component
 information for this connection.

 @Input     hAttachHandle :     The DMAN connection handle for this attachment.

 @Output    ppvCompAttachmentData :  A pointer used to return attachement specific
                                    data structure that will be provided or can
                                    be accessed in subsequent DMAN device callbacks
                                    or device APIs via the various DMAN handles.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
typedef IMG_RESULT (* DMANKM_pfnCompConnect)(
    IMG_HANDLE				hAttachHandle,
    IMG_VOID **             ppvCompAttachmentData
);


/*!
******************************************************************************

 @Function              DMANKM_pfnCompDisconnect

 @Description

 This is the prototype for the componet disconnect/close callback
 function.  This callback is made when the device component signals that the
 disconnect is complete using DMANKM_DevDisconnectComplete().  At this point
 it is safe for the component to free the resources etc. for this connection.

 NOTE: The resource allocator component is responsible for releasing the connection
 specific data structures associated with pvDevConnectionData.

 @Input     hAttachHandle :    The DMAN connection handle for this attachment.

 @Input     pvCompAttachmentData :  A pointer to the connection specific data
                                    structure returned by the #DMANKM_pfnCompConnect
                                    function.

 @Return    IMG_RESULT :		This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
typedef IMG_RESULT (*DMANKM_pfnCompDisconnect)(
    IMG_HANDLE				hAttachHandle,
    IMG_VOID *              pvCompAttachmentData
);


/*!
******************************************************************************
 This structure contains information filled in by the #DMANKM_pfnCompConnect
 function.


 NOTE: When this callback is made the #DMANKM_pfnCompAttach has set to 0/IMG_NULL.
 The callback should setup the fields within the structure as defined in
 #DMANKM_sCompAttach.  Any callback functions within the structure that are
 not setup will not be called.

   @brief	This structure contains information filled in by the #DMANKM_pfnCompConnect
 function.
******************************************************************************/
struct DMANKM_tag_sCompAttach
{
    DMANKM_pfnCompConnect    pfnCompConnect;    //!< Resource allocator connect / open function.
    DMANKM_pfnCompDisconnect pfnCompDisconnect; //!< Resource allocator disconnect / close function.
};


/*!
******************************************************************************

 @Function              DMANKM_Initialise

 @Description

 This function is used to initialises the Device Manager Kernel component and
 should be called at start-up.  This function calls the device registration
 functions #DMANKM_pfnDevRegister registered using DMANKM_RegisterDevice().

 NOTE: DMANKM_Initialise() should ONLY be called after all of the devices have
 been registered using DMANKM_RegisterDevice().

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function              DMANKM_Deinitialise

 @Description

 This function is used to deinitialises the Device Manager Kernel component and
 would normally be called at shutdown.

 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function              DMANKM_RegisterDevice

 @Description

 This function is used to register a device at start-up in kernal mode.

 NOTE: DMANKM_RegisterDevice() must be called to register all of the devices
 BEFORE calling DMANKM_Initialise().

 @Input     pszDeviceName :     Device Name.

 @Input     pfnDevRegister :    A pointer to the device registration function.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_RegisterDevice(
    IMG_CHAR *                  pszDeviceName,
    DMANKM_pfnDevRegister       pfnDevRegister
);

extern IMG_RESULT DMANKM_UnRegisterDevice(
	IMG_CHAR *					pszDeviceName
);


/*!
******************************************************************************

 @Function              DMANKM_LocateDevice

 @Description

 This function is used to locate a device.

 @Input     pszDeviceName : Device Name.

 @Output	phDevHandle :	A pointer used to return the device handle.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or
							IMG_ERROR_DEVICE_NOT_FOUND if the device was not found.

******************************************************************************/
extern IMG_RESULT DMANKM_LocateDevice(
    IMG_CHAR *                  pszDeviceName,
	IMG_HANDLE *				phDevHandle
);


/*!
******************************************************************************

 @Function              DMANKM_LockDeviceContext

 @Description

 This function is used to lock a device context - this prevents any other
 process (application) or thread within the current process from accessing
 device context, connections and associated resource allocators.

 NOTE: Device locking is generally used to protect the device and assocaited
 memory structure and to ensure that there coherent.

 @Input     hDevHandle :	The DMAN device handle.

 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_LockDeviceContext(
    IMG_HANDLE             hDevHandle
);


/*!
******************************************************************************

 @Function              DMANKM_UnlockDeviceContext

 @Description

 This function is used to unlock a device context - see DMANKM_LockDeviceContext().

 @Input     hDevHandle :	The DMAN device handle.

 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_UnlockDeviceContext(
    IMG_HANDLE             hDevHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetDevHandleFromConn

 @Description

 This function is used to get the device handle from a connection handle.

 @Input     hConnHandle :	The DMAN connection handle for this connection.

 @Return    IMG_HANDLE :	The DMAN device handle.

******************************************************************************/
extern IMG_HANDLE DMANKM_GetDevHandleFromConn(
    IMG_HANDLE            hConnHandle
);

/*!
******************************************************************************

 @Function              DMANKM_GetConnHandleFromAttach

 @Description

 This function is used to get the connection handle from an attachment handle.

 @Input     hAttachHandle :	The DMAN connection handle for this attachment.

 @Return    IMG_HANDLE :	The DMAN connection handle.

******************************************************************************/
extern IMG_HANDLE DMANKM_GetConnHandleFromAttach(
    IMG_HANDLE          hAttachHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetDevHandleFromAttach

 @Description

 This function is used to get the device handle from an attachment handle.

 @Input     hAttachHandle :	The DMAN connection handle for this attachment.

 @Return    IMG_HANDLE :	The DMAN device handle.

******************************************************************************/
extern IMG_HANDLE DMANKM_GetDevHandleFromAttach(
    IMG_HANDLE          hAttachHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetDeviceName

 @Description

 This function is used to get the device name associate with the
 device.

 @Input     hDevHandle :	The DMAN device handle.

 @Return    IMG_CHAR * :	A pointer to the device device name defined
							when the device was registered using
                            DMANKM_RegisterDevice().

******************************************************************************/
extern IMG_CHAR * DMANKM_GetDeviceName(
    IMG_HANDLE             hDevHandle
);


/*!
******************************************************************************

 @Function              DMANKM_SetDevGlobalData

 @Description

 This function is used to set the device global data associate with the
 device.

 @Input     hDevHandle :		The DMAN device handle.

 @Input		pvDevGlobalData :	A pointer to the device global data.

 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_SetDevGlobalData(
    IMG_HANDLE				hDevHandle,
	IMG_VOID *				pvDevGlobalData
);


/*!
******************************************************************************

 @Function              DMANKM_GetDevGlobalData

 @Description

 This function is used to get the device global data associate with the
 device.

 @Input     hDevHandle :		The DMAN device handle.

 @Return    IMG_VOID * :        The pointer to the device global data set by
                                #DMANKM_pfnDevInit.

******************************************************************************/
extern IMG_VOID * DMANKM_GetDevGlobalData(
    IMG_HANDLE             hDevHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetDevInstanceData

 @Description

 This function is used to get the device instance data associate with the
 device.

 @Input     hDevHandle :        The DMAN device handle.

 @Return    IMG_VOID * :        The pointer to the device instance data set by
                                #DMANKM_pfnDevInit.

******************************************************************************/
extern IMG_VOID * DMANKM_GetDevInstanceData(
    IMG_HANDLE             hDevHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetDevConnectionData

 @Description

 This function is used to get the device connection data associate with the
 connection.

 NOTE: Cannot be called with the implicit connection - see #DMANKM_pfnDevInit.

 @Input     hConnHandle :       The DMAN connection handle.

 @Return    IMG_VOID * :        The pointer to the device conection data set by
                                #DMANKM_pfnDevDeinit.

******************************************************************************/
extern IMG_VOID * DMANKM_GetDevConnectionData(
    IMG_HANDLE            hConnHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetCompAttachmentData

 @Description

 This function is used to get the attachment specific data associate with the
 attachment.

 @Input     hAttachHandle :     The DMAN attachment handle.

 @Return    IMG_VOID * :        The pointer to the device specific data set by
                                #DMANKM_pfnCompConnect.

******************************************************************************/
extern IMG_VOID * DMANKM_GetCompAttachmentData(
    IMG_HANDLE          hAttachHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetConnIdFromHandle

 @Description

 This function is used to get the connection Id from a connection handle.

 @Input     hConnHandle :		The DMAN connection handle.

 @Return    IMG_UINT32 :		The connection Id.

******************************************************************************/
extern IMG_UINT32 DMANKM_GetConnIdFromHandle(
    IMG_HANDLE			hConnHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetConnHandleFromId

 @Description

 This function is used to get the connection handle from a connection Id.

 @Input     ui32ConnId :		The DMAN connection Id.

 @Output    phConnHandle :		A pointer used to return the connection handle.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_GetConnHandleFromId(
    IMG_UINT32          ui32ConnId,
    IMG_HANDLE *		phConnHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetConnProcId

 @Description

 This function is used to get the process Id associated with this connection.

 @Input     hConnHandle :		The DMAN connection handle.

 @Return    IMG_HANDLE :		The process Id.

******************************************************************************/
extern IMG_HANDLE DMANKM_GetConnProcId(
    IMG_HANDLE			hConnHandle
);


/*!
******************************************************************************

 @Function              DMANKM_OpenDevice

 @Description

 This function is used to open a device and connect to it.

 @Input     hDevHandle :        The DMAN device handle.

 @Input		eOpenMode :			Mode in which the device is to be opened.

 @Output    phConnHandle :      Pointer used to return the connection handle.
								IMG_NULL if the handle is not required.

 @Output    pui32ConnId :       Pointer used to return the connection Id.
								IMG_NULL if the Id is not required.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_OpenDevice(
    IMG_HANDLE				hDevHandle,
	DMAN_eOpenMode			eOpenMode,
    IMG_HANDLE *			phConnHandle,
    IMG_UINT32 *			pui32ConnId
);


/*!
******************************************************************************

 @Function              DMANKM_CloseDevice

 @Description

 This function is used to close a device connection.

 NOTE: Cannot be called with the implicit connection - see #DMANKM_pfnDevInit.

 @Input     hDevHandle :        The DMAN device handle.

 @Input     hConnHandle :       The connection handle returned by DMAN_OpenDevice().

 @Input		eDisconnType :		Type of disconnect.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_CloseDevice(
    IMG_HANDLE				hDevHandle,
    IMG_HANDLE				hConnHandle,
	DMANKM_eDisconnType		eDisconnType
);


/*!
******************************************************************************

 @Function              DMANKM_GetDeviceId

 @Description

 This function is used to obtains the DMAN device id.

 @Input     hDevHandle :        The DMAN device handle.

 @Output    pui32DeviceId :     A pointer used to return the device id.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_GetDeviceId(
    IMG_HANDLE				hDevHandle,
	IMG_UINT32 *			pui32DeviceId
);


/*!
******************************************************************************

 @Function              DMANKM_DevDisconnectComplete

 @Description

 This function is used to signal that the disconnect is complete.

 NOTEL: This should ONLY be called from the device component when it is safe
 to free off any associated resources and close the connection.

 @Input     hConnHandle :       The DMAN connection handle for this connection.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_DevDisconnectComplete(
    IMG_HANDLE            hConnHandle
);


/*!
******************************************************************************

 @Function              DMANKM_AttachComponent

 @Description

 This function is used to attach a component in kernel mode.  The component
 is attached to the connection and the components attach function callback
 #DMANKM_pfnCompAttach called.

 NOTE: Components are things such as memory allocators etc.

 NOTE: Components can be attached to both application/process connections
 and to the implicit connection - see #DMANKM_pfnDevInit.

 @Input     hConnHandle :       The DMAN connection handle for this connection.

 @Input     pszCompName :		Component name.

 @Input     pfnCompAttach :		A pointer to the component registration
                                function.

 @Output    phAttachHandle :	A pointer used to return the attachment handle.
								IMG_NULL of the handle is not required.

 @Output    pui32AttachId :		A pointer used to return the attachment Id.
								IMG_NULL of the Id is not required.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_AttachComponent(
    IMG_HANDLE				hConnHandle,
    IMG_CHAR *              pszCompName,
    DMANKM_pfnCompAttach	pfnCompAttach,
    IMG_HANDLE *			phAttachHandle,
    IMG_UINT32 *			pui32AttachId
);


/*!
******************************************************************************

 @Function              DMANKM_GetAttachIdFromHandle

 @Description

 This function is used to get the attachment Id from a attachment handle.

 @Input     hAttachHandle :		The DMAN attachment handle.

 @Return    IMG_UINT32 :		The connection Id.

******************************************************************************/
extern IMG_UINT32 DMANKM_GetAttachIdFromHandle(
    IMG_HANDLE			hAttachHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetAttachHandleFromId

 @Description

 This function is used to get the attachment handle from a attachment Id.

 @Input     ui32AttachId :		The DMAN attachment Id.

 @Output    phAttachHandle :	A pointer used to return the attachment handle.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT DMANKM_GetAttachHandleFromId(
    IMG_UINT32          ui32AttachId,
    IMG_HANDLE *		phAttachHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetAttachResBucket

 @Description

 This function is used to get the resource bucket associated with this attachment.

 @Input     hAttachHandle :		The DMAN attachment handle.

 @Return    IMG_HANDLE :		The resource bucket handle.

******************************************************************************/
extern IMG_HANDLE DMANKM_GetAttachResBucket(
    IMG_HANDLE			hAttachHandle
);


/*!
******************************************************************************

 @Function              DMANKM_GetConnFromAttachHandle

 @Description

 This function is used to get the connection handle from an attachment handle.

 @Input     hAttachHandle :		The DMAN attachment handle.

 @Return    IMG_HANDLE :		The connection handle.

******************************************************************************/
extern IMG_HANDLE DMANKM_GetConnFromAttachHandle(
    IMG_HANDLE			hAttachHandle
);


/*!
******************************************************************************

 @Function				DMANKM_ActivateKmHisr

 @Description

 This function is used to activate a HISR and is normally called
 from a LISR (in interrupt context).

 @Input     hDevHandle :        The DMAN device handle.

 @Return	None.

******************************************************************************/
extern IMG_VOID DMANKM_ActivateKmHisr(
    IMG_HANDLE			hDevHandle
);

/*!
******************************************************************************

 @Function				DMANKM_GetKmBuildFlags

 @Description

 This function is used to obtain kernel mode build flags

 @Output     pui32KmBuildFlags : Pointer to kernel mode build flags

 @Return     IMG_RESULT :   This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
IMG_RESULT DMANKM_GetKmBuildFlags(
	IMG_UINT32 *			pui32KmBuildFlags
	);

/*!
******************************************************************************

 @Function				DMANKM_ResetPowerManagementFlag

 @Description

 This function is used to Reset PowerManagement Flags for the device.

 @Input     hDevHandle :        The DMAN device handle.

 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_ResetPowerManagementFlag(
    IMG_HANDLE             hDevHandle
);

/*!
******************************************************************************

 @Function				DMANKM_SuspendDevice

 @Description

 This function is used to Suspend Device and manage power state transitions

 @Input     hDevHandle :        The DMAN device handle.

 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_SuspendDevice(
    IMG_HANDLE             hDevHandle
);

/*!
******************************************************************************

 @Function				DMANKM_ResumeDevice

 @Description

 This function is used to Resume Device and manage power state transitions

 @Input     hDevHandle :        The DMAN device handle.

 @Input     bEnableLock :        Flag to enable LOCK/UNLOCK. Enabled if IMG_TRUE

 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_ResumeDevice(
    IMG_HANDLE             hDevHandle,
    IMG_BOOL                 bEnableLock
);

/*!
******************************************************************************

 @Function				DMANKM_ReadPpmTurnedOnFlag

 @Description

 This function is used to read whether we have just come out of PPM

 @Input     hDevHandle :        The DMAN device handle.

 @Output    pui8PpmTurnedOn : pointer to ppmturnedon flag
 
 @Return    None.

******************************************************************************/
extern IMG_VOID DMANKM_ReadPpmTurnedOnFlag(
    IMG_HANDLE             hDevHandle,
    IMG_UINT8 *			   pui8PpmTurnedOn
);





#if defined(__cplusplus)
}
#endif

#endif /* __DMAN_API_KM_H__ */
