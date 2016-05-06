/*!
 *****************************************************************************
 *
 * @File       sysdev_utils.h
 * @Title      The System Device kernel mode utilities.
 * @Description    This file contains the header file information for the
 *  System Device Kernel Mode Utilities API.
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

#if !defined (__SYSDEV_UTILS_H__)
#define __SYSDEV_UTILS_H__

#include <img_defs.h>
#include <img_mem.h>
#include <dman_api_km.h>
#include <sysos_api_km.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
******************************************************************************
 Macro used to initialise a #SYSDEVU_sDevInfo structure.
******************************************************************************/
#define SYS_DEVICE(name,prefix,subdevice){ name, & prefix##KM_fnDevRegister, subdevice}

/*!
******************************************************************************
 This structure contains information for a device API.

 NOTE: This structure MUST be defined in static memory as it is retained and
 used by the SYSDEV component whilst the system is active.

 NOTE: The order of the items is important - see #SYS_DEVICE.

 @brief		This structure contains information for a SYSDEVKM API.

******************************************************************************/
typedef struct
{
	IMG_CHAR *				pszDeviceName;		//!< The device name
	DMANKM_pfnDevRegister	pfnDevRegister;		//!< Registration function
	IMG_BOOL				bSubDevice;			//!< Used to indicate devices which are a sub-component of some greater
											//!< device, and as such do not have their own PCI base address / socket ID.
} SYSDEVU_sDevInfo;

/*!
******************************************************************************
 This type defines the device region(s).
******************************************************************************/
typedef enum
{
	SYSDEVU_REGID_REGISTERS,			//!< Device registers
	SYSDEVU_REGID_SLAVE_PORT,			//!< Device slave port

} SYSDEVU_eRegionId;

struct SYSDEVU_sInfo;

struct SYSDEV_ops {
	IMG_VOID (*free_device)(struct SYSDEVU_sInfo *);

	// device specific resume hook.
	IMG_VOID (*resume_device)(struct SYSDEVU_sInfo *, IMG_BOOL forAPM);
	// device specific suspend hook.
	IMG_VOID (*suspend_device)(struct SYSDEVU_sInfo *, IMG_BOOL forAPM);

	// convert physical cpu address to device physical address
	IMG_PHYSADDR (*paddr_to_devpaddr)(struct SYSDEVU_sInfo *, IMG_PHYSADDR  paCpuPAddr);
	// convert device physical address to cpu physical address
	IMG_PHYSADDR (*devpaddr_to_paddr)(struct SYSDEVU_sInfo *, IMG_PHYSADDR  paCpuPAddr);
};

/*!
******************************************************************************

 @Function              SYSDEVU_pfnDevKmLisr

 @Description

 This is the prototype for device Kernel Mode LISR callback functions.  This
 function is called when the device interrupt is suspected.

 NOTE: The Kernel Mode LISR should return IMG_FALSE if the device did not
 cause the interrupt. This allows for several devices to share an interrupt
 line.  The Kernel Mode LISR returns IMG_TRUE if the interrupt has been handled.

 NOTE: By convention, further device interrupts are disabled whilst the Kernel
 Mode LISR is active.  Device interrupts must be re-enabled by a synchronous,
 or asynchronous call to SYSDEVKN_EnableDeviceInt().

 @Input		pvParam :		Pointer parameter, defined when the
						    callback was registered.

							NOTE: This pointer must be valid in interrupt
							context.

 @Return	IMG_BOOL :		IMG_TRUE if the interrupt has been handles by the
							Kernel Mode LISR, otherwise IMG_FALSE.

******************************************************************************/
typedef IMG_BOOL ( * SYSDEVU_pfnDevKmLisr) (
    IMG_VOID *                  pvParam
);

/*!
******************************************************************************
 This structure contains device information.

 #SYSDEVU_sDevInfo MUST be the first element in this structure.
******************************************************************************/
typedef struct SYSDEVU_sInfo
{
	LST_LINK;
	SYSDEVU_sDevInfo		sDevInfo;			//!< #SYS_DEVICE defined part of device info
	IMG_BOOL				bDevLocated;		//!< IMG_TRUE when the device has been located
	SYSDEVU_pfnDevKmLisr	pfnDevKmLisr;		//!< Pointer to any registered Kernel Mode LISR callback

	struct SYSDEV_ops		*ops;

	IMG_VOID *              pvParam;			//!< Pointer to be passed to the Kernel Mode LISR callback
	IMG_VOID *				pvLocParam;			//!< Pointer used to retains "located" information

	IMG_PHYSADDR 			paPhysRegBase;	//!< A pointer to the device registers physical address (or mappable to user mode) - IMG_NULL if not defined
	IMG_UINT32 *			pui32KmRegBase;		//!< A pointer to the device register base in kernel mode - IMG_NULL if not defined
	IMG_UINT32 				ui32RegSize;		//!< The size of the register block (0 if not known)

	IMG_PHYSADDR			paPhysMemBase;
	IMG_UINT32 *			pui32KmMemBase;
	IMG_UINT32 				ui32MemSize;
	IMG_UINT64				pui64DevMemoryBase;

	IMG_UINT32				ui32DeviceId;

	SYS_eMemPool			sMemPool;
	SYS_eMemPool			secureMemPool;

	IMG_VOID *				native_device;
	IMG_VOID *pPrivate;
} SYSDEVU_sInfo;

/*!
******************************************************************************

 @Function				SYSDEVU_ActivateDevKmLisr

 @Description

 This function invokes a device's KM LISR. This can be used to manually invoke
 daisy chained interrupts from a top level ISR.

 @Input		hSysDevHandle :	The device handle returned by SYSDEVU_OpenDevice().

 IMG_RESULT               :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSDEVU_ActivateDevKmLisr(
	IMG_HANDLE				hSysDevHandle
);


extern IMG_RESULT SYSDEVU_RegisterDriver(SYSDEVU_sInfo *);
extern IMG_RESULT SYSDEVU_UnRegisterDriver(SYSDEVU_sInfo *sysdev);

/*!
******************************************************************************

 @Function				SYSDEVU_RegisterDevices

 @Description 
 
 This function is used to register the device with the Device Manager (DMAN).

 @Input		psInfo :		A Device info structure for the device to be registered

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSDEVU_RegisterDevice(
	SYSDEVU_sInfo *			psInfo
);

/*!
******************************************************************************

 @Function				SYSDEVU_UnRegisterDevice

 @Description

 This function is used to unregister the device from the Device Manager (DMAN).

 @Input		psInfo :		A Device info structure for the device to be registered

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSDEVU_UnRegisterDevice(
	SYSDEVU_sInfo *psInfo
);


/*!
******************************************************************************

 @Function				SYSDEVU_Initialise
 
 @Description 
 
 This function is used to initialise the system device component and is 
 called at start-up.

 @Input		None. 

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSDEVU_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSDEVU_Deinitialise
 
 @Description 
 
 This function is used to deinitialises thesystem device component and would 
 normally be called at shutdown.
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSDEVU_Deinitialise(IMG_VOID);

/*!
******************************************************************************

 @Function				SYSDEVU_OpenDevice

 @Description

 This function is used to open a device.

 This function may require enumeration and locating the device over PCI or
 some other form of device enumeration/location which is specific to the system/SoC.

 @Input		pszDeviceName :	The name of the device - should be the same
							as the name used when registering the device
							via DMANKM_RegisterDevice().

 @Output	phSysDevHandle :	A pointer used to return the device handle.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSDEVU_OpenDevice(
	IMG_CHAR *				pszDeviceName,
	SYSDEVU_sInfo **		phSysDevHandle
);


/*!
******************************************************************************

 @Function				SYSDEVU_CloseDevice

 @Description

 This function is used to close a device.

 @Input		hSysDevHandle :	The device handle returned by SYSDEVU_OpenDevice().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSDEVU_CloseDevice(
	SYSDEVU_sInfo *hSysDevHandle
);


/*!
******************************************************************************

 @Function				SYSDEVU_GetCpuKmAddr

 @Description

 This function is used to obtain a kernel mode mapping of the device registers
 etc.

 @Input		hSysDevHandle :	The device handle returned by SYSDEVU_OpenDevice().

 @Input		eRegionId :		The region of the device to be mapped.

 @Output	ppvCpuKmAddr :	A pointer used to return a kernel mode CPU linear
							address for the device region.

 @Output	pui32Size :		A pointer used to return the size of the region mapped.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSDEVU_GetCpuKmAddr(
	SYSDEVU_sInfo *			hSysDevHandle,
	SYSDEVU_eRegionId		eRegionId,
	IMG_VOID **				ppvCpuKmAddr,
	IMG_UINT32 *			pui32Size
);


/*!
******************************************************************************

 @Function				SYSDEVU_CpuPAddrToDevPAddr

 @Description

 This function is used to convert a CPU physical address to a device physical
 address.

 NOTE: The device mapping of physical memory may be different from the CPU's
 mapping of memory, so a level of re-mapping may be required based on the
 device Id. For systems in which the CPU physical address is the same as the
 device physical address this function should just return the CPU physical
 address parameter as provided.

 @Input		hSysDevHandle :	The device handle returned by SYSDEVU_OpenDevice().

 @Input		ui64CpuPAddr :	CPU physical address obtained via SYSDEV_GetCpuPAddrKM().

 @Return	IMG_UINT64 :	The device physical address.

******************************************************************************/
extern IMG_PHYSADDR SYSDEVU_CpuPAddrToDevPAddr(
	IMG_HANDLE				hSysDevHandle,
	IMG_PHYSADDR				paCpuPAddr
);


/*!
******************************************************************************

 @Function				SYSDEVU_GetCpuAddrs
 
 @Description 
 
 This function is used to obtains a kernel mode mapping of the device registers
 etc.
 
 @Input		sysdev :	The sysdev handle.
 
 @Input		eRegionId :	The region of the device to be mapped.

 @Output    ppvCpuKmAddr :  A pointer user to return the kernel mode address

 @Output    ppvCpuPhysAddr : A pointer user to return the physical address

 @Output    pui32Size :     A pointer user to return the region size

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
IMG_UINT32 SYSDEVU_GetCpuAddrs(
	SYSDEVU_sInfo *			sysdev,
	SYSDEVU_eRegionId		eRegionId,
	IMG_VOID **             ppvCpuKmAddr,
	IMG_PHYSADDR *          ppaCpuPhysAddr,
	IMG_UINT32 *            pui32Size
);

/*!
******************************************************************************

 @Function				SYSDEVU_HandleSuspend

 @Description

 Invoke the platform specific suspend routine

 @Input		sysdev :	The sysdev handle.

 @Input		forAPM : This will tell the platform specific suspend routine
  	  	  	  whether it should do a suspend for APM or not

******************************************************************************/
extern IMG_VOID SYSDEVU_HandleSuspend(
	SYSDEVU_sInfo *				dev,
	IMG_BOOL					forAPM
);


/*!
******************************************************************************

 @Function				SYSDEVU_HandleResume

 @Description

 Invoke the platform specific resume routine

 @Input		sysdev :	The sysdev handle.

 @Input		forAPM : This will tell the platform specific resume routine
  	  	  	  whether it should do a resume for APM or not

******************************************************************************/
extern IMG_VOID SYSDEVU_HandleResume(
	SYSDEVU_sInfo *				dev,
	IMG_BOOL					forAPM
);

/*!
******************************************************************************

 @Function				SYSDEVU_RegisterDevKmLisr
 
 @Description 
 
 This function is used to register a Kernel Mode Low-level Interrupt Service 
 Routine (LISR) callback function.  This function is called when the device 
 interrupts.

 NOTE: On registering a Kernel Mode LISR for a device the device interrupt 
 is enabled.

 NOTE: A Kernel Mode LISR many be registered multiple times.  However, the 
 registration auguments must be the same for all calls to 
 SYSBRGKM_RegisterDevKmLisr().

 NOTE: Interrupts are disabled when the device is closed using 
 SYSDEVU_CloseDevice() and re-enabled on subsequent calls to
 SYSDEVU_GetDeviceId().
 
 @Input		ui32DeviceId :	The device id returned by SYSDEVU_GetDeviceId().

 @Input		pfnDevKmLisr :	A pointer to the Kernel Mode LISR callback function.

 @Input		pvParam :		An IMG_VOID * value passed to the Kernel Mode LISR
					        function when a device interrupt occurs.

							NOTE: This pointer must be valid in interrupt
							context.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSDEVU_RegisterDevKmLisr(
	IMG_HANDLE					devHandle,
	SYSDEVU_pfnDevKmLisr		pfnDevKmLisr,
    IMG_VOID *                  pvParam
);
	

/*!
******************************************************************************

 @Function				SYSDEVU_RemoveDevKmLisr

 @Description

 This function is used to remove a Kernel Mode Low-level Interrupt Service
 Routine (LISR) callback function.

 NOTE: Removing the Kernel Mode Low-level Interrupt Service
 Routine disables interrupts for the device.

 @Input		hSysDevHandle :	The device handle returned by SYSDEVU_OpenDevice().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSDEVU_RemoveDevKmLisr(
	IMG_HANDLE				hSysDevHandle
);

/*!
******************************************************************************

 @Function				SYSDEVU_InvokeDevKmLisr
 
 @Description 
 
 This function is used to invoke a Kernel Mode Low-level Interrupt Service 
 Routine (LISR) callback function.

 @Input		sysdev		 :	Handle to sysdev

 IMG_RESULT              :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
IMG_RESULT SYSDEVU_InvokeDevKmLisr(
	SYSDEVU_sInfo *sysdev
);


/*!
******************************************************************************

 @Function				SYSDEVU_SetDevMap

 @Description

 Initialize the memory layout for SYSDEV device

 @Input		sysdev : The SYSDEV device handle.

 @Input		physreg_base : The physical base address of the memory mapped registers of this device.

 @Input		kmreg_base : The kernel accessible base address of the memory mapped registers of this device.

 @Input		regsize : The size of the memory mapped registers of this device.

 @Input		physmem_base : The physical base address of the internal memory of this device, if any.

 @Input		kmmem_base : The kernel accessible base address of the internal memory of this device, if any.

 @Input		memsize : The size of the internal memory of this device.

 @Return	None

******************************************************************************/
IMG_VOID SYSDEVU_SetDevMap(
		SYSDEVU_sInfo *sysdev,
		IMG_PHYSADDR physreg_base,
		IMG_UINT32 *kmreg_base,
		IMG_UINT32 regsize,
		IMG_PHYSADDR physmem_base,
		IMG_UINT32 *kmmem_base,
		IMG_UINT32 memsize,
		IMG_UINT64 devmem_base
);


/*!
******************************************************************************

 @Function				SYSDEVU_SetDeviceOps

 @Description

 Initialize the SYSDEV device

 @Input		sysdev : The SYSDEV device handle.

 @Input		pfnFreeDevice :	This callback is called when we're about to free SYSDEV device.

 @Input		pfnResumeDevice : This callback is called when we're resuming the device from SUSPENDED state.

 @Input		pfnSuspendDevice :	This callback is called when we're trying to suspend the device.

 @Return	None.

******************************************************************************/
IMG_VOID SYSDEVU_SetDeviceOps(SYSDEVU_sInfo *sysdev, struct SYSDEV_ops *ops);

/*!
******************************************************************************

 @Function				SYSDEVU_SetPowerState

 @Description

 This function is used to set the power state for a device.

 NOTE: The power is state of the device is normally managed by the Device Manager.
 The power is turned on when the first connection is made to the device and off
 when the last connection has been closed and the device driver has signaled the
 disconnect has completed using DMANKM_DevDisconnectComplete().
 The power state may also be changed by the Device Manager in response to power
 transition events signaled via SYSOSKM_pfnKmPowerEvent - for devices that have
 registered power management callback functions such as DMANKM_fnDevPowerPreS5
 and DMANKM_fnDevPowerPostS0.

 @Input		hSysDevHandle :	The device handle returned by SYSDEVU_OpenDevice().

 @Input     ePowerState   : Indicates the state to which the power is to be set.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSDEVU_SetPowerState(
	IMG_HANDLE				hSysDevHandle,
	SYSOSKM_ePowerState     ePowerState,
	IMG_BOOL				forAPM
);

/*!
******************************************************************************

 @Function				SYSDEVU_ApmPpmFlagsReset

 @Description

 This function is used to reset APM PPM flags in device manager.

 @Input		hDevHandle :	The device handle.

 @Return	None.
******************************************************************************/
IMG_VOID SYSDEVU_ApmPpmFlagsReset(
	IMG_HANDLE				hDevHandle
);

/*!
******************************************************************************

 @Function				SYSDEVU_ApmDeviceSuspend

 @Description

 This function is used to suspend the device by APM.

 @Input		hDevHandle :	The device handle.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSDEVU_ApmDeviceSuspend(
	IMG_HANDLE				hDevHandle
);

/*!
******************************************************************************

 @Function				SYSDEVU_ApmDeviceResume

 @Description

 This function is used to resume the device after APM suspend.

 @Input		hDevHandle :	The device handle.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSDEVU_ApmDeviceResume(
	IMG_HANDLE				hDevHandle
);


IMG_VOID SYSDEVU_FreeDevice(
	IMG_HANDLE				hDevHandle
);

	
#if defined(__cplusplus)
}
#endif
 
#endif /* __SYSDEV_UTILS_H__	*/


