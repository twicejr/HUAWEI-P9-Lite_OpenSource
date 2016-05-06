/*!
 *****************************************************************************
 *
 * @File       page_alloc.h
 * @Title      The Page Allocator user mode API.
 * @Description    This file contains the header file information for the
 *  Page Allocator.
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

#if !defined (__PAGE_ALLOC_H__)
#define __PAGE_ALLOC_H__

#include <img_types.h>
#include <img_defs.h>
#include <system.h>
#include <dq.h>

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef  __RPCCODEGEN__
    #define rpc_prefix      PALLOC
    #define rpc_filename    page_alloc
#endif

/* Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

/*!
******************************************************************************
 This type defines the type for a buffer to be imported
 @brief  Imported buffer type
******************************************************************************/
typedef enum
{
	PALLOC_BUFTYPE_DEFAULT = 0,
    PALLOC_BUFTYPE_USERALLOC = 1,     /*!< Allocated in user mode */
    PALLOC_BUFTYPE_ANDROIDNATIVE = 2, /*!< Android native buffer  */
    PALLOC_BUFTYPE_ANDROIDASHMEM = 3, /*!< Android ashmem buffer  */
    PALLOC_BUFTYPE_DMABUF = 4,
    PALLOC_BUFTYPE_GEMBUF = 5,
    PALLOC_BUFTYPE_MAX = 6,
} PALLOC_eImportBufType;



    /*!
******************************************************************************

 @Function				PALLOC_Initialise
 
 @Description 
 
 This function is used to initialises the Page Allocator component 
 and should be called at start-up.
 
 @Input		None. 

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_RESULT PALLOC_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				PALLOC_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the Page Allocator component and 
 would normally be called at shutdown.
 
 @Input		None. 

 @Return	None.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_VOID PALLOC_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function				PALLOC_AttachToConnection
 
 @Description 
 
 This function is used to attach the Page Allocation to a device 
 connection.
 
 @Input		ui32ConnId :	The connection Id returned by DMAN_OpenDevice()

 @Output	pui32AttachId :	A pointer used to return the attachment	Id.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOC_AttachToConnection(
	IMG_UINT32				ui32ConnId,
	SYSBRG_POINTER_ARG(IMG_UINT32)		pui32AttachId
);


/*!
******************************************************************************

 @Function				PALLOC_Alloc
 
 @Description 
 
 This function is used to allocate a number of memory pages which can be 
 accessed by the devices within the system/SoC.

 NOTE: The pool (eMemPool) can be used when devices share memory, to ensure
 the that allocation is made from memory accessible by the devices sharing the
 allocation.

 @Input		ui32AttachId :	The attachment Id returned by PALLOC_AttachToConnection()

 @Input		ui32Size :		Size of the allocation.

 @Input		eMemAttrib :	The memory attributes.

 @Input		eMemPool :		The pool from which the memory is to be allocated.

 @Output	ppvCpuUmAddr :	A pointer used to return the address of the allocated
						    pages (mapped into user mode).

 @Output	pui32AllocId :	A pointer used to return the Id of the allocated
							memory.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_RESULT PALLOC_Alloc(
	IMG_UINT32 				ui32AttachId,
	IMG_UINT32				ui32Size,
	SYS_eMemAttrib			eMemAttrib,
	IMG_VOID **				ppvCpuUmAddr,
	IMG_UINT32 *			pui32AllocId
);

/*!
******************************************************************************

 @Function				PALLOC_Import
 
 @Description 
 
 This function is used to import a number of memory pages which can be 
 accessed by the devices within the system/SoC.

 NOTE: The pool (eMemPool) can be used when devices share memory, to ensure
 the that allocation is made from memory accessible by the devices sharing the
 allocation.

 @Input		ui32AttachId :	The attachment Id returned by PALLOC_AttachToConnection()

 @Input		ui32Size :		Size of the allocation.

 @Input		hExternalBuf :  Handle to external buffer

 @Input		eImpBufType :	Type of buffer about to be imported

 @Input		eMemAttrib :	The memory attributes.

 @Input		eMemPool :		The pool from which the memory is to be allocated.

 @Output	ppvCpuUmAddr :	A pointer used to return the address of the allocated
						    pages (mapped into user mode).

 @Output	pui32AllocId :	A pointer used to return the Id of the allocated
							memory.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_RESULT PALLOC_Import(
    IMG_UINT32 				ui32AttachId,
    IMG_UINT32				ui32Size,
    IMG_HANDLE              hExternalBuf,
    PALLOC_eImportBufType   eImpBufType,
    SYS_eMemAttrib			eMemAttrib,
    IMG_VOID **				ppvCpuUmAddr,
    IMG_UINT32 *			pui32AllocId
);


/*!
******************************************************************************

 @Function				PALLOC_Free
 
 @Description 
 
 This function is used to free memory.
 
 @Input		ui32AllocId :	The allocation Id returned by PALLOC_Alloc()

 @Return	None.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_VOID PALLOC_Free(
	IMG_UINT32  			ui32AllocId
);
	
/*!
******************************************************************************

 @Function				PALLOC_CpuUmAddrToDevPAddr
 
 @Description 
 
 This function is used to obtain a device physical address for a user mode
 address of an allocation or mapping made through PALLOC.

 @Input		ui32DeviceId :	The DMAN Device Id obtained using DMAN_GetDeviceId().

 @Input		pvCpuUmAddr :	The user mode address.

 @Return	IMG_UINT64 :	The device physical address.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_PHYSADDR PALLOC_CpuUmAddrToDevPAddr(
	IMG_UINT32				ui32DeviceId,
	IMG_VOID *				pvCpuUmAddr
);

#if !defined (DOXYGEN_WILL_SEE_THIS)


/*!
******************************************************************************
 This structure contains information for a given allocation/mapping.
******************************************************************************/
typedef struct
{
	SYSBRG_UINT64			dq_padding[2];				// /*!< reserved space for DQ link  (allows the structure to be part of a DQ list).*/
	IMG_BOOL			bMappingOnly;		//!< IMG_TRUE if this is a mapping rather than an allocation
	IMG_UINT32 			ui32AttachId;		//!< Attachment id used for malloc
	IMG_UINT32			ui32Size;			//!< Size of allocation (in bytes)
	SYSBRG_UPOINTER(IMG_VOID, pvCpuUmAddr);		//!< User mode address of allocation

	IMG_UINT32			ui32DeviceId;		//<! DMAN Device Id
	IMG_UINT32 			ui32AllocId;		//!< Allocation ID returned by malloc
	PALLOC_eImportBufType      eBufType;      /*!< Buffer type                    */

	SYSBRG_UINT64			ui64Offset;		//!< Offset to use for mmap
	SYSBRG_UPOINTER(IMG_PHYSADDR,			ppaDevPAddr);		//!< Array of device physical addresses of the allocation.

} PALLOC_sUmAlloc;

typedef IMG_RESULT (*PALLOC_Allocfn) (
	    PALLOC_sUmAlloc *		psUmAlloc,
	    SYS_eMemAttrib			eMemAttrib
);

typedef IMG_RESULT (*PALLOC_Importfn) (
		IMG_UINT32 ui32AttachId,
		PALLOC_eImportBufType bufType,
		PALLOC_sUmAlloc *psUmAlloc,
		IMG_HANDLE hExternalBuf,
		SYS_eMemAttrib eMemAttrib
);

typedef IMG_RESULT (*PALLOC_Freefn) (
	PALLOC_sUmAlloc *psUmAlloc
);

typedef IMG_PHYSADDR (*PALLOC_CpuUmAddrToDevPAddrfn) (
    IMG_UINT32				ui32DeviceId,
    IMG_VOID *				pvCpuUmAddr
);

typedef struct PALLOC_Heap {
	/* alloc */
	PALLOC_Allocfn alloc;

	/* free */
	PALLOC_Freefn free;

	/* import */
	PALLOC_Importfn import;

	/* cpu um to dev addr */
	PALLOC_CpuUmAddrToDevPAddrfn cpuum_to_devpaddr;
} PALLOC_Heap;

/*!
******************************************************************************

 @Function				PALLOC_Alloc1
 
 @Description 
 
 This function is used to allocate a number of memory pages which can be 
 accessed by the devices within the system/SoC.

 NOTE: The pool (eMemPool) can be used when devices share memory, to ensure
 the that allocation is made from memory accessible by the devices sharing the
 allocation.

 @Input		ui32AttachId :	The attachment Id returned by PALLOC_AttachToConnection()

 @Input		ui32Size :		Size of the allocation.

 @Input		eMemAttrib :	The memory attributes.

 @Input		eMemPool :		The pool from which the memory is to be allocated.

 @Output	psUmAlloc :		A pointer to an allocation structure used to return
						    information about this allocation.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOC_Alloc1(
	IMG_UINT32               ui32AttachId,
	SYS_eMemAttrib           eMemAttrib,
        SYSBRG_POINTER_ARG(PALLOC_sUmAlloc) psUmAlloc
);

/*!
******************************************************************************

 @Function				PALLOC_Import1
 
 @Description 
 
 This function is used to import a number of memory pages which can be 
 accessed by the devices within the system/SoC.

 NOTE: The pool (eMemPool) can be used when devices share memory, to ensure
 the that allocation is made from memory accessible by the devices sharing the
 allocation.

 @Input		ui32AttachId :	The attachment Id returned by PALLOC_AttachToConnection()

 @Input		eMemAttrib :	The memory attributes.

 @Input		eMemPool :		The pool from which the memory is to be allocated.

 @Input		buff_fd :	    File descriptor which represents the buffer in kernel space.
                            If -1, we are importing a user space allocated buffer. The
                            caller must store that address in psUmAlloc->pvCpuUmAddr.

 @Input     psUmAlloc :		A pointer to an allocation structure used to return
						    information about this allocation (input/output). bMappingOnly,
						    ui32AttachId, and ui32Size must be filled by the caller.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOC_Import1(
	IMG_UINT32               ui32AttachId,
	PALLOC_eImportBufType	 bufType,
	SYS_eMemAttrib           eMemAttrib,
	IMG_INT32                buff_fd,
	SYSBRG_POINTER_ARG(PALLOC_sUmAlloc) psUmAlloc
);


/*!
******************************************************************************

 @Function				PALLOC_Free1
 
 @Description 
 
 This function is used to free memory.
 
 @Input		ui32AllocId :	The allocation Id returned by PALLOC_Alloc1()

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOC_Free1(
	IMG_UINT32  			ui32AllocId
);

#endif


#if defined(__cplusplus)
}
#endif
 
#endif /* __PAGE_ALLOC_H__	*/

