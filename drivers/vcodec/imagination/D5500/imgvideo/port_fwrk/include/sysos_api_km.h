/*!
 *****************************************************************************
 *
 * @File       sysos_api_km.h
 * @Title      The System OS kernel mode API.
 * @Description    This file contains the header file information for the
 *  OS Kernel Mode API.
 *  The implementation of the OS Kernel Mode API is
 *  specific to OS.
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

#if !defined (__SYSOS_API_KM_H__)
#define __SYSOS_API_KM_H__

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>
#ifdef IMG_KERNEL_MODULE
#include <linux/time.h>    // for struct timespec
#else
#include <time.h>
#endif // IMG_KERNEL_MODULE

#if defined(__cplusplus)
extern "C" {
#endif

/* Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

/*!
******************************************************************************
 This type defines the power transition.
******************************************************************************/
typedef enum
{
	SYSOSKM_POWERTRANS_PRE,				//!< Pre state transition
	SYSOSKM_POWERTRANS_POST,			//!< Post state transition

} SYSOSKM_ePowerTrans;

/*!
******************************************************************************
 This type defines the power states - as defined in the ACPI spec.  However,
 only S0 and S5 are currently supported, more states may be added as/when they
 are required.

 NOTE: Not all OS's will support all state or state transitions and not all
 devices can support the subtle differences between the various modes of 
 "sleeping" - which is why only a limited set of states is currently supported.
******************************************************************************/
typedef enum
{
	SYSOSKM_POWERSTATE_S0,			//!< Working:  The normal working state of the computer 
//	SYSOSKM_POWERSTATE_S1,			//!< Sleeping: The most power-hungry of sleep-modes.
//	SYSOSKM_POWERSTATE_S2,			//!<		   A deeper sleep-state than S1
//	SYSOSKM_POWERSTATE_S3,			//!<           Known as suspend to RAM
//	SYSOSKM_POWERSTATE_S4,			//!<		   Hibernation in Windows, Safe Sleep in Mac OS X, also known as Suspend to disk
	SYSOSKM_POWERSTATE_S5,			//!<		   Soft Off

} SYSOSKM_ePowerState;

/*!
******************************************************************************

 @Function				SYSOSKM_Initialise
 
 @Description 
 
 This function is used to initialise the kernel OS component and is called at
 start-up.
 
 @Input		None. 

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSOSKM_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSOSKM_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the kernel OS component and would 
 normally be called at shutdown.
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSOSKM_GetProcessId
 
 @Description 
 
 This function is used to obtain the current process Id.
 
 @Input		None.

 @Return	IMG_HANDLE :	A handle that uniquely identifies the process.

******************************************************************************/
extern IMG_HANDLE SYSOSKM_GetProcessId(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSOSKM_DisableInt
 
 @Description 
 
 This function is used to disable interrupts.

 NOTE: Each call to SYSOSKM_DisableInt() should be matched by a call to 
 SYSOSKM_EnableInt() - only when the last SYSOSKM_EnableInt() call is made
 are interrupts re-enabled.

 NOTE: Should be used sparingly.
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_DisableInt(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSOSKM_EnableInt
 
 @Description 
 
 This function is used to enable interrupts - see SYSOSKM_DisableInt().
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_EnableInt(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSOSKM_CreateMutex
 
 @Description 
 
 This function is used to create a mutex.
 
 @Output	phMutexHandle :	A pointer used to return the mutex handle.

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSOSKM_CreateMutex(
	IMG_HANDLE *			phMutexHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_DestroyMutex
 
 @Description 
 
 This function is used to destroy a mutex.
 
 @Input		hMutexHandle :	The mutex handle returned by SYSOSKM_CreateMutex().

 @Return	None.

******************************************************************************/
extern  IMG_VOID SYSOSKM_DestroyMutex(
    IMG_HANDLE			hMutexHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_LockMutex
 
 @Description 
 
 This function is used to lock a mutex.

 NOTE: Providing the lock requirements are met (correct process/thread etc) then
 then the mutex may be locked multiple times.
 
 NOTE: Each call to SYSOSKM_LockMutex() should be matched by a call to 
 SYSOSKM_UnlockMutex() - only when the last SYSOSKM_UnlockMutex() call is made
 is the mutex free to be locked by some other process and/or thread.

 @Input		hMutexHandle :	The mutex handle returned by SYSOSKM_CreateMutex().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_LockMutex(
    IMG_HANDLE			hMutexHandle
);

IMG_RESULT SYSOSKM_LockMutex_Interruptible(
    IMG_HANDLE  hMutexHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_UnlockMutex
 
 @Description 
 
 This function is used to unlock a mutex.
 
 @Input		hMutexHandle:	The mutex handle returned by SYSOSKM_CreateMutex().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_UnlockMutex(
    IMG_HANDLE			hMutexHandle
);


/*!
******************************************************************************

 @Function                SYSOSKM_CreateAtomic

 @Description

 Create an atomic handle.

 @Output	atomic :	A pointer used to return the atomic handle.

 @Return	IMG_RESULT: IMG_SUCCESS on success

******************************************************************************/
IMG_RESULT SYSOSKM_CreateAtomic(IMG_HANDLE *atomic);


/*!
******************************************************************************

 @Function                SYSOSKM_DestroyAtomic

 @Description

 Free the atomic handle.

 @Input		atomic:	The atomic handle returned by SYSOSKM_CreateAtomic().

 @Return	None.

******************************************************************************/
IMG_VOID SYSOSKM_DestroyAtomic(IMG_HANDLE atomic);


/*!
******************************************************************************

 @Function                SYSOSKM_ReadAtomic

 @Description

 Read the value of the atomic handle.

 @Input		atomic:	The atomic handle returned by SYSOSKM_CreateAtomic().

 @Return	the value of the atomic handle.

******************************************************************************/
IMG_INT SYSOSKM_ReadAtomic(IMG_HANDLE atomic);


/*!
******************************************************************************

 @Function                SYSOSKM_SetAtomic

 @Description

 Set the value of the atomic handle.

 @Input		atomic:	The atomic handle returned by SYSOSKM_CreateAtomic().

 @Input		value: the new value of atomic handle.

 @Return	None.

******************************************************************************/
IMG_VOID SYSOSKM_SetAtomic(IMG_HANDLE atomic, IMG_INT value);

/*!
******************************************************************************

 @Function                SYSOSKM_IncrementReturnAtomic

 @Description

 Increment the value and return the new value atomically.

 @Input		atomic:	The atomic handle returned by SYSOSKM_CreateAtomic().

 @Input		value: the new value of atomic handle.

 @Return	IMG_INT: the atomic value after it was incremented.

******************************************************************************/
IMG_INT SYSOSKM_IncrementReturnAtomic(IMG_HANDLE atomic);


/*!
******************************************************************************

 @Function                SYSOSKM_DecrementReturnAtomic

 @Description

 Decrement the value and return the new value atomically.

 @Input		atomic:	The atomic handle returned by SYSOSKM_CreateAtomic().

 @Input		value: the new value of atomic handle.

 @Return	IMG_INT: the atomic value after it was incremented.

******************************************************************************/
IMG_INT SYSOSKM_DecrementReturnAtomic(IMG_HANDLE atomic);



/*!
******************************************************************************

 @Function				SYSOSKM_CreateEventObject
 
 @Description 
 
 This function is used to create a event object.
 
 @Output	phEventHandle :	A pointer used to return the event object handle.

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSOSKM_CreateEventObject(
	IMG_HANDLE *		phEventHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_DestroyEventObject
 
 @Description 
 
 This function is used to destroy a event object.
 
 @Input		hEventHandle :	The event object handle returned by 
							SYSOSKM_CreateEventObject().

 @Return	None.

******************************************************************************/
extern  IMG_VOID SYSOSKM_DestroyEventObject(
    IMG_HANDLE			hEventHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_WaitEventObject
 
 @Description 
 
 This function is used to wait for an event on a event object.

 NOTE: Because Linux may "interrupt" the wait and require a return to user mode 
 (this happens when using gdb/ddd to debug user mode application that are using 
 the Portability Framework) then IMG_ERROR_INTERRUPTED may be returned by 
 SYSOSKM_WaitEventObject(). The calling code should detect this return to user 
 mode before re-initiate the command and waiting for the event to complete normally.

 @Input		hEventHandle : 	The event object handle returned by 
							SYSOSKM_CreateEventObject().
 @Input     bUninterruptible : The wait is not interruptible. *Warning*: select interruptible if waiting for
                             a hardware event or any event which might not happen. 

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or IMG_ERROR_INTERRUPTED 
                            or an error code.

******************************************************************************/
extern IMG_RESULT SYSOSKM_WaitEventObject(
    IMG_HANDLE			hEventHandle,
    IMG_BOOL            bUninterruptible
);


/*!
******************************************************************************

 @Function				SYSOSKM_SignalEventObject
 
 @Description 
 
 This function is used to signal an event via a event object.
 
 @Input		hEventHandle :	The sync object handle returned by 
							SYSOSKM_CreateEventObject().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_SignalEventObject(
    IMG_HANDLE			hEventHandle
);


/*!
******************************************************************************

 @Function              SYSOSKM_pfnTimer

 @Description

 This is the prototype for tiemr callback functions.  This function is called 
 when the specified time period has elapsed.

 NOTE: The timer should return IMG_FALSE if the timer is not to rescheduled.
 IMG_TRUE if the timer is to be reset/rescheduled for the timeout period
 defined when the timer was created using SYSOSKM_CreateTimer();

 @Input		pvParam :		Pointer parameter, defined when the
						    callback was created.

							NOTE: This pointer must be valid in interrupt
							context.

 @Return	IMG_BOOL :		IMG_TRUE to reset/reschedule the rimer, 
							otherwise IMG_FALSE.

******************************************************************************/
typedef IMG_BOOL ( * SYSOSKM_pfnTimer) (
    IMG_VOID *                  pvParam
);


/*!
******************************************************************************

 @Function				SYSOSKM_CreateTimer
 
 @Description 
 
 This function is used to create a event object.
 
 @Input		pfnTimer :		A pointer to the timer callback function.

 @Input		pvParam :		An IMG_VOID * value passed to the timer function
							when the timeout occurs.

							NOTE: This pointer must be valid in interrupt
							context.

 @Input		ui32TimeOut :	Timer period (in milli-seconds).

 @Output	phTimerHandle :	A pointer used to return the timer object handle.

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSOSKM_CreateTimer(
	SYSOSKM_pfnTimer			pfnTimer,
    IMG_VOID *                  pvParam,
    IMG_UINT32                  ui32TimeOut,
	IMG_HANDLE *				phTimerHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_DestroyTimer
 
 @Description 
 
 This function is used to destroy a event object.
 
 @Input		hTimerHandle :	The timer object handle returned by 
							SYSOSKM_CreateTimer().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_DestroyTimer(
    IMG_HANDLE			hTimerHandle
);


/*!
******************************************************************************

 @Function              SYSOSKM_pfnDevKmHisr

 @Description

 This is the prototype a HISR callback function which is called when it is
 activated using SYSOSKM_ActivateKmHisr().

 Note that Hisr is considered to be like an interrupt. Interrupts are not queued.
 So, in order to avoid race conditions, this function should service
 all pending events. It will not be called once for every Hisr event. 

 @Input		pvParam :		Pointer parameter, defined when the
						    callback was registered.

 @Return	None.

******************************************************************************/
typedef IMG_VOID ( * SYSOSKM_pfnDevKmHisr) (
    IMG_VOID *                  pvParam
);



/*!
******************************************************************************

 @Function				SYSOSKM_CreateKmHisr
 
 @Description 
 
 This function is used to create a HISR object.
 
 @Input		pfnDevKmHisr :	A pointer to the HISR callback function.


 @Input		pvParam :		An IMG_VOID * value passed to the timer function
							when the timeout occurs.

							NOTE: This pointer must be valid in the HISR context.

 @Output	phHISRHandle :	A pointer used to return the HISR object handle.

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSOSKM_CreateKmHisr(
	SYSOSKM_pfnDevKmHisr		pfnDevKmHisr,
    IMG_VOID *                  pvParam,
    IMG_HANDLE *				phHISRHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_DestroyKmHisr
 
 @Description 
 
 This function is used to destroy a HISR object.
 
 @Input		hHISRHandle :	The HISR object handle returned by 
							SYSOSKM_CreateKmHisr().

 @Return	None.

******************************************************************************/
extern  IMG_VOID SYSOSKM_DestroyKmHisr(
    IMG_HANDLE			hHISRHandle
);


/*!
******************************************************************************

 @Function				SYSOSKM_ActivateKmHisr
 
 @Description 
 
 This function is used to activate a HISR and is normally called
 from a LISR (in interrupt context).
 
 @Input		hHISRHandle :	The HISR object handle returned by 
							SYSOSKM_CreateKmHisr().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_ActivateKmHisr(
    IMG_HANDLE			hHISRHandle
);

	

/*!
******************************************************************************

 @Function				SYSOSVKM_GetBoolEnvVar
 
 @Description 
 
 This function is used to obtain the current setting on an 
 environement variable. 

 NOTE: If the variable is not define then IMG_FALSE is returned.
 
 @Input		pszName :		A pointer to the name of the valiable.

 @Return	IMG_BOOL :		IMG_TRUE or IMG_FALSE.

******************************************************************************/
extern IMG_BOOL SYSOSVKM_GetBoolEnvVar(
	IMG_CHAR *			pszName
);
	

/*!
******************************************************************************

 @Function				SYSOSKM_GetIntEnvVar
 
 @Description 
 
 This function is used to obtain the current setting on an 
 environement variable. 

 NOTE: If the variable is not define then 0 is returned.
 
 @Input		pszName :		A pointer to the name of the valiable.

 @Return	IMG_INT32 :		The variable setting.

******************************************************************************/
extern IMG_INT32 SYSOSKM_GetIntEnvVar(
	IMG_CHAR *			pszName
);
	

/*!
******************************************************************************

 @Function				SYSOSKM_GetStrEnvVar
 
 @Description 
 
 This function is used to obtain the current setting on an 
 environement variable. 

 NOTE: If the variable is not define then IMG_NULL is returned.
 
 @Input		pszName :		A pointer to the name of the valiable.

 @Return	IMG_CHAR * :		The variable setting.

******************************************************************************/
extern IMG_CHAR * SYSOSKM_GetStrEnvVar(
	IMG_CHAR *			pszName
);
	

/*!
******************************************************************************

 @Function				SYSOSKM_GetSymbolAddr
 
 @Description 
 
 This function is used to obtain the address of a symbol.  If the symbol
 is correctly defined then it can be used to obtain the address of an
 external function, table etc. 

 NOTE: If the symbol is not define or is unknown then IMG_NULL is returned.
 
 @Input		pszName :		A pointer to the name of the symbol.

 @Return	IMG_VOID * :		The variable setting.

******************************************************************************/
extern IMG_VOID * SYSOSKM_GetSymbolAddr(
	IMG_CHAR *			pszName
);

/*!
******************************************************************************

 @Function              SYSOSKM_pfnKmPowerEvent

 @Description

 This is the prototype for the power event callback function that is called
 by the underlying OS when a power state change is being made.

 @Input		ePowerTrans :	Indicates whether the call is before or after
							a state transition.

 @Input		ePowerState :	Indicates the state to which or in which the
							power is.

 @Input		pvParam :	Pointer parameter, defined when the
						callback was registered.

 @Return	None.

******************************************************************************/
typedef IMG_VOID ( * SYSOSKM_pfnKmPowerEvent) (
	SYSOSKM_ePowerTrans			ePowerTrans,
	SYSOSKM_ePowerState			ePowerState,
    IMG_VOID *                  pvParam
);

/*!
******************************************************************************

 @Function				SYSOSKM_RegisterKmPowerEventCb
 
 @Description 
 
 This function is used to register a power event callback function.  This 
 function is called when the power state is to be changed.

 @Input		pfnKmPowerEvent :	A pointer to the power event callback function.

 @Input		pvParam :		An IMG_VOID * value passed to the power event callback
					        function when a power event.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_RegisterKmPowerEventCb(
	SYSOSKM_pfnKmPowerEvent		pfnKmPowerEvent,
    IMG_VOID *                  pvParam
);


/*!
******************************************************************************

 @Function				SYSOSKM_RemoveKmPowerEventCb
 
 @Description 
 
 This function is used to remove the power event callback function.
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSOSKM_RemoveKmPowerEventCb(IMG_VOID);

/*!
****************************************************************************** 
 @Function              SYSOSKM_CopyFromUser
 @Description 
 This function is used to copy data from user space into kernel space.
 This is important in Linux, because the kernel does not guarantee that
 user space data is resident when accessed from kernel mode. 
 @Input     pvToCpuKmAddr :     destination address in kernel space
 @Input     pvFromCpuUmAddr :   source address in user space
 @Input     ui32NumBytes :      byte count
 @Return    IMG_SUCCESS if successful
******************************************************************************/
#define SYSOSKM_CopyFromUser(pvToCpuKmAddr, pvFromCpuAddr, stNumBytes) \
    SYSOSKM_CopyFromUserRaw((pvToCpuKmAddr), SYSBRG_POINTER_FROM_USER(pvFromCpuAddr), (stNumBytes))
extern IMG_RESULT SYSOSKM_CopyFromUserRaw(
    IMG_VOID *       pvToCpuKmAddr,
    const IMG_VOID __user * pvFromCpuUmAddr,
    IMG_SIZE       stNumBytes
);
/*!
****************************************************************************** 
 @Function              SYSOSKM_CopyToUser
 @Description 
 This function is used to copy data to user space from kernel space.
 This is important in Linux, because the kernel does not guarantee that
 user space data is resident when accessed from kernel mode. 
 @Input     pvToCpuUmAddr :    destination address in user space
 @Input     pvFromCpuKmAddr :  source address in kernel space
 @Input     ui32NumByte :      byte counts
 @Return    IMG_SUCCESS if successful
******************************************************************************/
#define SYSOSKM_CopyToUser(pvToCpuUmAddr, pvFromCpuKmAddr, stNumBytes) \
    SYSOSKM_CopyToUserRaw(SYSBRG_POINTER_FROM_USER(pvToCpuUmAddr), (pvFromCpuKmAddr), (stNumBytes))
extern IMG_RESULT SYSOSKM_CopyToUserRaw(
    IMG_VOID __user * pvToCpuUmAddr,
    const IMG_VOID * pvFromCpuKmAddr,
    IMG_SIZE       stNumBytes
); 

/*!
****************************************************************************** 
 @Function              SYSOSKM_CpuUmAddrToCpuPAddrArray
 @Description 
 Locks memory reserved in user space to physical addresses and returns and
 array with the physical addresses
 @Input     pvCpuUmAddr :    CPU user mode address (page aligned)
 @Output    pPhysAddrArray : Array of physical addresses
 @Input     numPages :       Number of pages reserved
 @Output    ppvKernAddr :    Pointer to the KM address of the first physical page
 @Return    IMG_SUCCESS if successful
******************************************************************************/
extern IMG_RESULT SYSOSKM_CpuUmAddrToCpuPAddrArray(
    const IMG_VOID __user *pvCpuUmAddr,
    IMG_PHYSADDR *ppaPhysAddrArray,
    IMG_UINT numPages,
    IMG_PVOID *ppvKernAddr
);

/*!
******************************************************************************
 @Function              SYSOSKM_ReleaseCpuPAddrArray
 @Description 
 Releases physical memory reserved by SYSOSKM_CpuUmAddrToCpuPAddrArray
 @Input    pvKernAddr : Kernel address
 @Input    pvUmAddr : User mode address
 @Input    pPhysAddrArray : Array of physical addresses
 @Input    numPages :       Number of elements in array
 @Return   IMG_SUCCESS if successful
******************************************************************************/
extern IMG_RESULT SYSOSKM_ReleaseCpuPAddrArray(
    IMG_PVOID pvKernAddr,
    IMG_HANDLE pvUmAddr,
    const IMG_PHYSADDR *ppaPhysAddrArray,
    IMG_UINT numPages
);

/*!
******************************************************************************
 @Function				SYSOSKM_PowerEventStateNotify
 
 @Description 
 
 This function is used to notify the sysoskm layer o any changes to the 
 power state. The new state could, for example, be presented to the user
 as a system variable. 
 
 @Input		None.

 @Return	None.
******************************************************************************/
extern IMG_VOID SYSOSKM_PowerEventStateNotify(const char * new_state);

/*!
******************************************************************************

 @Function				SYSOSKM_ResumeDevice
 
 @Description 
 
 This function is used to Resume the power of Device.
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_RESULT SYSOSKM_ResumeDevice(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSOSKM_SuspendDevice
 
 @Description 
 
 This function is used to Suspend the power of Device.
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_RESULT SYSOSKM_SuspendDevice(IMG_VOID);

 /*!
******************************************************************************
 Prototype for function to write to a debug file
******************************************************************************/
typedef int (*debug_printf_t)(void *, const char *, ...);

/*!
******************************************************************************
 Prototype for callback used in SYSOSKM_CreateDebugFile. The input parameters
 are the data provided in SYSOSKM_CreateDebugFile, the function for writing
 into the file and the first parameter that must be passed to that function.
******************************************************************************/
typedef void (*debug_open_callback_t)(
    void *data,               //<! 
    debug_printf_t pfnPrintf, //<! printf function for writing to file
    void *print_data
    );

/*!
******************************************************************************

 @Function              SYSOSKM_CreateDebugFile

 @Description

 Creates a debug file in Linux debug file system

 @Input     name :	        Name for the file in \<debugfs\>/\<device\>/
 @Input     data :	        Data that will be passed back in the callback
 @Input     pfnOpenFileCb : Function called whenever the device is opened
 @Return    Handle to debug file

******************************************************************************/
extern IMG_HANDLE SYSOSKM_CreateDebugFile(
    const char* name, 
    void *data,
    debug_open_callback_t pfnOpenFileCb
);

/*!
******************************************************************************

 @Function              SYSOSKM_RemoveDebugFile

 @Description

 Removes a file previously created by SYSOSKM_CreateDebugFile

 @Input     hDebugFile :	Handle to debug file

******************************************************************************/
extern IMG_VOID SYSOSKM_RemoveDebugFile(
    IMG_HANDLE hDebugFile
);

/*!
******************************************************************************

 @Function              SYSOSKM_GetTimeOfDay

 @Description

get absolute time of day, in seconds and nanoseconds

 @Output psTimespec : current time of day
 @Return IMG_SUCCESS or an error value

******************************************************************************/
extern IMG_RESULT SYSOSKM_GetTimeOfDay(
    struct timespec * psTimespec
);
#if defined(__cplusplus)
}
#endif
#endif /* __SYSOS_API_KM_H__	*/



