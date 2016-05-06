/*!
 *****************************************************************************
 *
 * @File       tal_old.h
 * @Title      Support for old API for the Target Abstraction Layer.
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

#include <img_types.h>
#include <img_defs.h>
#include <img_errors.h>

#if !defined (__TAL_OLD_H__)
#define __TAL_OLD_H__

#if defined (__cplusplus)
extern "C" {
#endif


/***************************************
		TAL Setup Functions
***************************************/
#define TAL_Initialise													TALSETUP_Initialise
#define TAL_Deinitialise												TALSETUP_Deinitialise
#define TAL_IsInitialised												TALSETUP_IsInitialised
#define TAL_RegisterPollFailFunc										TALSETUP_RegisterPollFailFunc
#define TAL_Reset														TALSETUP_Reset
#define TAL_SetTargetApplicationFlags									TALSETUP_SetTargetApplicationFlags

/***************************************
		TAL Interrupt Functions
***************************************/
#define TAL_UnRegisterCheckInterruptFunc(ui32MemSpaceId)				TALINTERRUPT_UnRegisterCheckFunc((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId)
#define TAL_RegisterCheckInterruptFunc(ui32MemSpaceId,Func,pCBParam)	TALINTERRUPT_RegisterCheckFunc((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,Func,pCBParam)
#define TAL_GetInterruptNumber(ui32MemSpaceId,pui32IntNum)				TALINTERRUPT_GetNumber((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pui32IntNum)
#define TAL_GetInterruptMask(ui32MemSpaceId,aui32IntMasks)				TALINTERRUPT_GetMask((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,aui32IntMasks)

/***************************************
		TAL Register Functions
***************************************/
#define TAL_WriteWord(ui32MemSpaceId,ui32Offset,ui32Value)						TALREG_WriteWord32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32Value)
#define TAL_WriteWords(ui32MemSpaceId,ui32Offset,ui32WordCount,pui32Value)		TALREG_WriteWords32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32WordCount,pui32Value)
#define TAL_WriteWordDefineContext(ui32MemSpaceId,ui32Offset,ui32Value,ui32ContextMemSpaceId)		\
		TALREG_WriteWordDefineContext32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32Value,(IMG_HANDLE)(IMG_UINTPTR)ui32ContextMemSpaceId)
#define TAL_ReadWord(ui32MemSpaceId,ui32Offset,pui32Value)						TALREG_ReadWord32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,pui32Value)
#define TAL_ReadWords(ui32MemSpaceId,ui32Offset,ui32WordCount,pui32Value)		TALREG_ReadWords32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32WordCount,pui32Value)
#define TAL_Poll(ui32MemSpaceId,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut) \
		TALREG_Poll32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut)
#define TAL_PrePoll(ui32MemSpaceId,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut) \
		TALREG_PrePoll32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut)

#define TAL_CircBufPoll(ui32MemSpaceId,ui32Offset,ui32WriteOffsetVal,ui32PacketSize, \
						ui32BufferSize) \
		TALREG_CircBufPoll32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32WriteOffsetVal,ui32PacketSize, \
						ui32BufferSize,0,0)

#define TAL_WriteDeviceMemRef(ui32MemSpaceId,ui32Offset,ui32Mangler,hRefDeviceMem,ui32RefOffset) \
		IMG_ASSERT(ui32Mangler == TAL_NULL_MANGLER_ID), \
		TALREG_WriteDevMemRef32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,hRefDeviceMem,ui32RefOffset)

#define TAL_ReadWordTest(ui32MemSpaceId,ui32Offset,pui32Value) \
		TALREG_ReadWordToSAB32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,pui32Value,gui32TalRdwVerifyPollIter,gui32TalRdwVerifyPollTime)


/***************************************
		TAL Memory Functions
***************************************/

#define TAL_DeviceMemWriteWordDefineContext64(ui32MemSpaceId,hDeviceMem,ui32Offset,ui64Value,ui32ContextMemspaceId) \
		TALMEM_WriteWordDefineContext64(hDeviceMem,ui32Offset,ui64Value,(IMG_HANDLE)(IMG_UINTPTR)ui32ContextMemspaceId)
#define TAL_DeviceMemWriteWordDefineContext32(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32Value,ui32ContextMemspaceId) \
		TALMEM_WriteWordDefineContext32(hDeviceMem,ui32Offset,ui32Value,(IMG_HANDLE)(IMG_UINTPTR)ui32ContextMemspaceId)
#define TAL_DeviceMemWriteWordDefineContext			TAL_DeviceMemWriteWordDefineContext32

#define TAL_DeviceMemWriteWord64(ui32MemSpaceId,hDeviceMem,ui32Offset,ui64Value) \
		TALMEM_WriteWord64(hDeviceMem,ui32Offset,ui64Value)
#define TAL_DeviceMemWriteWord32(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32Value) \
		TALMEM_WriteWord32(hDeviceMem,ui32Offset,ui32Value)
#define TAL_DeviceMemWriteWord(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32Value) \
		TALMEM_WriteWord32(hDeviceMem,ui32Offset,ui32Value)

#define TAL_DeviceMemReadWord64(ui32MemSpaceId,hDeviceMem,ui32Offset,pui64Value) \
		TALMEM_ReadWord64(hDeviceMem,ui32Offset,pui64Value)
#define TAL_DeviceMemReadWord32(ui32MemSpaceId,hDeviceMem,ui32Offset,pui32Value) \
		TALMEM_ReadWord32(hDeviceMem,ui32Offset,pui32Value)
#define TAL_DeviceMemReadWord(ui32MemSpaceId,hDeviceMem,ui32Offset,pui32Value) \
		TALMEM_ReadWord32(hDeviceMem,ui32Offset,pui32Value)

#define TAL_MallocNamedDeviceMem(ui32MemSpaceId,pHostMem,ui32Size,ui64Alignment,phDeviceMem,bUpdateDevice,pszMemName) \
		TALMEM_Malloc((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pHostMem,ui32Size,ui64Alignment,phDeviceMem,bUpdateDevice,pszMemName)
#define TAL_MapDeviceMem(ui32MemSpaceId,pHostMem,ui64DeviceAddr,ui64Size,ui64Alignment,phDeviceMem) \
		TALMEM_Map((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pHostMem,ui64DeviceAddr,ui64Size,ui64Alignment,phDeviceMem)
#define TAL_FreeDeviceMem							TALMEM_Free
#define TAL_ReadMemoryUsingBlocks					TALMEM_ReadFromAddress

#define TAL_CopyHostToDeviceMem(ui32MemSpaceId,hDeviceMem) \
		TALMEM_UpdateDevice(hDeviceMem)
#define TAL_CopyDeviceToHostMem(ui32MemSpaceId,hDeviceMem) \
		TALMEM_UpdateHost(hDeviceMem)
#define TAL_CopyHostToDeviceMemRegion(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32Size) \
		TALMEM_UpdateDeviceRegion(hDeviceMem,ui32Offset,ui32Size)
#define TAL_CopyDeviceToHostMemRegion(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32Size) \
		TALMEM_UpdateHostRegion(hDeviceMem,ui32Offset,ui32Size)
#define TAL_DumpImageDevMem(ui32MemSpaceId,psImageHeaderInfo,psImageFilename,hDeviceMem1,ui32Offset1,ui32Size1, \
							hDeviceMem2,ui32Offset2,ui32Size2,hDeviceMem3,ui32Offset3,ui32Size3) \
		TALMEM_DumpImage(psImageHeaderInfo,psImageFilename,hDeviceMem1,ui32Offset1,ui32Size1, \
							hDeviceMem2,ui32Offset2,ui32Size2,hDeviceMem3,ui32Offset3,ui32Size3)
#define TAL_PrePollDeviceMem(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut) \
		TALMEM_Poll32(hDeviceMem,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut)
#define TAL_PollDeviceMem(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut) \
		TALMEM_Poll32(hDeviceMem,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut)

#define TAL_CircBufPollDeviceMem(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32WriteOffsetVal,ui32PacketSize,ui32BufferSize) \
		TALMEM_CircBufPoll32(hDeviceMem,ui32Offset,ui32WriteOffsetVal,ui32PacketSize,ui32BufferSize,0,0)
#define TAL_CircBufPrePollDeviceMem(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32WriteOffsetVal,ui32PacketSize,ui32BufferSize) \
		TALMEM_CircBufPoll32(hDeviceMem,ui32Offset,ui32WriteOffsetVal,ui32PacketSize,ui32BufferSize,0,0)

#define TAL_MallocDeviceMem(ui32MemSpaceId,pHostMem,ui32Size,ui32Alignment,phDeviceMem,bUpdateDevice) \
		TALMEM_Malloc((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pHostMem,ui32Size,ui32Alignment,phDeviceMem,bUpdateDevice,IMG_NULL)
#define TAL_DeviceMemWriteDeviceMemRef32(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32ManglerFuncId,hRefDeviceMem,ui32RefOffset) \
		(IMG_ASSERT(ui32ManglerFuncId == TAL_NULL_MANGLER_ID), \
		TALMEM_WriteDevMemRef32(hDeviceMem,ui32Offset,hRefDeviceMem,ui32RefOffset))
#define TAL_DeviceMemWriteDeviceMemRef64(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32ManglerFuncId,hRefDeviceMem,ui32RefOffset) \
		(IMG_ASSERT(ui32ManglerFuncId == TAL_NULL_MANGLER_ID), \
		TALMEM_WriteDevMemRef64(hDeviceMem,ui32Offset,hRefDeviceMem,ui32RefOffset))
#define TAL_DeviceMemWriteDeviceMemRef				TAL_DeviceMemWriteDeviceMemRef32



/***************************************
	TAL Virtual Memory Functions
***************************************/
#define TAL_MmuSetContext(ui32MemSpaceId,ui32MmuContextId,ui32MmuType,hDeviceMem) \
		TALVMEM_SetContext((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32MmuContextId,ui32MmuType,hDeviceMem)
#define TAL_MmuClearContext(ui32MemSpaceId,ui32MmuContextId) \
		TALVMEM_ClearContext((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32MmuContextId)
#define TAL_MmuSetTiledRegion(ui32MemSpaceId,ui32MmuContextId,ui32TiledRegionNo,ui64DevVirtAddr,ui32Size,ui32XTileStride) \
		TALVMEM_SetTiledRegion((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32MmuContextId,ui32TiledRegionNo,ui64DevVirtAddr,ui32Size,ui32XTileStride)
#define TAL_MmuClearTiledRegion(ui32MemSpaceId,ui32MmuContextId,ui32TiledRegionNo) \
		TALVMEM_ClearTiledRegion((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32MmuContextId,ui32TiledRegionNo)
#define TAL_PollDeviceVirtMem(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut) \
		TALVMEM_Poll((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32PollCount,ui32TimeOut,TAL_WORD_FLAGS_32BIT)
#define TAL_CircBufPollDeviceVirtMem(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32WriteOffsetVal,ui32PacketSize,ui32BufferSize) \
		TALVMEM_CircBufPoll32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32WriteOffsetVal,ui32PacketSize,ui32BufferSize,0,0)
#define TAL_CopyDeviceVirtToHostMemRegion(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui64Size,pvHostBuf) \
		TALVMEM_UpdateHost((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui64Size,pvHostBuf)
#define TAL_DumpImageDevVirt(ui32MemSpaceId,psImageHeaderInfo,psImageFilename,ui64DevVirtAddr1,ui32MmuContextId1,ui64Size1,pvHostBuf1,ui64DevVirtAddr2, \
							ui32MmuContextId2,ui64Size2,pvHostBuf2,ui64DevVirtAddr3,ui32MmuContextId3,ui64Size3,pvHostBuf3) \
		TALVMEM_DumpImage((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,psImageHeaderInfo,psImageFilename,ui64DevVirtAddr1,ui32MmuContextId1,ui64Size1,pvHostBuf1,ui64DevVirtAddr2, \
							ui32MmuContextId2,ui64Size2,pvHostBuf2,ui64DevVirtAddr3,ui32MmuContextId3,ui64Size3,pvHostBuf3)


/***************************************
	Other TAL Functions
***************************************/

#define TAL_CheckEnable(ui32MemSpaceId)			TAL_CheckMemSpaceEnable((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId)

#define TAL_MemSpaceGetId(psMemSpaceName,pui32MemSpaceId) \
{ \
	IMG_HANDLE hMemspace = TAL_GetMemSpaceHandle(psMemSpaceName); \
	*(pui32MemSpaceId) = IMG_UINT64_TO_UINT32((IMG_UINT64)(IMG_UINTPTR)hMemspace); \
}

#define TAL_Idle(ui32MemSpaceId,ui32Time)		TAL_Wait((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Time)

/***************************************
	TAL Loop Functions
***************************************/

#define TAL_LoopOpen(ui32MemSpaceId,phLoop)					TALLOOP_Open((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,phLoop)
#define TAL_LoopStart(ui32MemSpaceId,hLoop)					TALLOOP_Start(hLoop)
#define TAL_LoopTestRegister(hLoop,ui32MemSpaceId,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32LoopCount,ui32Delay) \
			TALLOOP_TestRegister(hLoop,(IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32LoopCount)
#define TAL_LoopTestMemory(hLoop,ui32MemSpaceId,hDevMem,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32LoopCount,ui32Delay) \
			TALLOOP_TestMemory(hLoop,hDevMem,ui32Offset,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32LoopCount)
#define TAL_LoopTestInternalReg(hLoop,ui32MemSpaceId,ui32IntRegId,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32LoopCount,ui32Delay) \
			TALLOOP_TestInternalReg(hLoop,(IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32IntRegId,ui32CheckFuncIdExt,ui32RequValue,ui32Enable,ui32LoopCount)
#define TAL_LoopEnd(ui32MemSpaceId,hLoop,peLoopControl)		TALLOOP_End(hLoop,peLoopControl)
#define TAL_LoopClose(ui32MemSpaceId,hLoop)					TALLOOP_Close((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,hLoop)



/***************************************
	TAL Internal Variable Functions
***************************************/
#define TAL_GetInternalRegValue(ui32MemSpaceId,ui32InternalVarId)					TALINTVAR_GetValue((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32InternalVarId)
#define TAL_DeviceMemRefToInternalReg(ui32MemSpaceId,hRefDeviceMem,ui32RefOffset,ui32SoftRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_WriteMemRef(hRefDeviceMem,ui32RefOffset,(IMG_HANDLE)(IMG_UINTPTR)ui32SoftRegMemSpaceId,ui32InternalVarId)
#define TAL_DeviceMemReadToInternalReg32(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32IntRegMemSpaceId,ui32InternalRegId) \
		TALINTVAR_ReadFromMem32(hDeviceMem,ui32Offset,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalRegId)
#define TAL_DeviceMemReadToInternalReg64(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32IntRegMemSpaceId,ui32InternalRegId) \
		TALINTVAR_ReadFromMem64(hDeviceMem,ui32Offset,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalRegId)
#define TAL_DeviceMemReadToInternalReg(ui32MemSpaceId,hDeviceMem,ui64Offset,ui32IntRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_ReadFromMem32(hDeviceMem,ui64Offset,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalVarId)
#define TAL_DeviceVirtMemWriteFromInternalReg32(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32IntRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_WriteToVirtMem((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalVarId,TAL_WORD_FLAGS_32BIT)
#define TAL_DeviceVirtMemWriteFromInternalReg TAL_DeviceVirtMemWriteFromInternalReg32
#define TAL_DeviceVirtMemWriteFromInternalReg64(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32IntRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_WriteToVirtMem((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalVarId,TAL_WORD_FLAGS_64BIT)
#define TAL_DeviceVirtMemReadToInternalReg(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32IntRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_ReadFromVirtMem32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalVarId)
#define TAL_DeviceVirtMemReadToInternalReg32(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32IntRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_ReadFromVirtMem32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalVarId)
#define TAL_DeviceVirtMemReadToInternalReg64(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32IntRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_ReadFromVirtMem64((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalVarId)
#define TAL_DeviceVirtMemRefToInternalReg(ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,ui32IntRegMemSpaceId,ui32InternalVarId) \
		TALINTVAR_WriteVirtMemReference((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui64DevVirtAddr,ui32MmuContextId,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalVarId)
#define TAL_DeviceMemWriteFromInternalReg32(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32IntRegMemSpaceId,ui32InternalRegId) \
		TALINTVAR_WriteToMem32(hDeviceMem,ui32Offset,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalRegId)
#define TAL_DeviceMemWriteFromInternalReg64(ui32MemSpaceId,hDeviceMem,ui32Offset,ui32IntRegMemSpaceId,ui32InternalRegId) \
		TALINTVAR_WriteToMem64(hDeviceMem,ui32Offset,(IMG_HANDLE)(IMG_UINTPTR)ui32IntRegMemSpaceId,ui32InternalRegId)
#define TAL_DeviceMemWriteFromInternalReg			TAL_DeviceMemWriteFromInternalReg32
#define TAL_ReadWordToInternalReg(ui32MemSpaceId,ui32Offset,ui32IntVarMemSpace,ui32InternalVarId)	\
		TALINTVAR_ReadFromReg32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,(IMG_HANDLE)(IMG_UINTPTR)ui32IntVarMemSpace,ui32InternalVarId)
#define TAL_WriteWordFromInternalReg(ui32MemSpaceId,ui32Offset,ui32IntVarMemSpace,ui32InternalVarId) \
		TALINTVAR_WriteToReg32((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Offset,(IMG_HANDLE)(IMG_UINTPTR)ui32IntVarMemSpace,ui32InternalVarId)
#define TAL_InternalRegCommand(ui32CommandId,ui32DestRegMemSpace,ui32DestRegId,ui32OpRegMemSpace,ui32OpRegId,ui32LastOpMemSpace,ui64LastOperand,bIsRegisterLastOperand) \
		TALINTVAR_RunCommand(ui32CommandId,(IMG_HANDLE)(IMG_UINTPTR)ui32DestRegMemSpace,ui32DestRegId,(IMG_HANDLE)(IMG_UINTPTR)ui32OpRegMemSpace,ui32OpRegId, \
							(IMG_HANDLE)(IMG_UINTPTR)ui32LastOpMemSpace,ui64LastOperand,bIsRegisterLastOperand)

/***************************************
	TAL Debug Functions
***************************************/
#define TAL_DeviceComment(ui32MemSpaceId,pszComment)		TALDEBUG_DevComment((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pszComment)
#define TAL_DevicePrint(ui32MemSpaceId,pszPrintText)		TALDEBUG_DevPrint((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pszPrintText)
#if !defined WIN32
#define _MSC_VER 1400 // to avoid warnings _MSC_VER
#endif

#if _MSC_VER >= 1400 || !defined WIN32
#define TAL_DevicePrintf(ui32MemSpaceId,pszPrintText,...)	TALDEBUG_DevPrintf((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pszPrintText,__VA_ARGS__)
#else
#define TAL_DevicePrintf									TAL_Deprecated
#endif

#if !defined WIN32
#undef _MSC_VER 
#endif

#define TAL_GetDeviceTime(ui32MemSpaceId,pui64Time)			TALDEBUG_GetDevTime((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pui64Time)
#define TAL_AutoIdle(ui32MemSpaceId,ui32Time)				TALDEBUG_AutoIdle((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32Time)
#define TAL_GetDeviceMemoryAddress(ui32MemSpaceId,hDeviceMem) \
		TALDEBUG_GetDevMemAddress(hDeviceMem)
#define TAL_GetHostMemoryAddress							TALDEBUG_GetHostMemAddress
#define TAL_ReadMemory										TALDEBUG_ReadMem

/***************************************
	TAL Pdump Functions
***************************************/

#if !defined(SYSBRG_NO_BRIDGING)
#define TAL_NULL_MANGLER_ID (0xFFFFFFFF)
#endif

#if defined(SYSBRG_NO_BRIDGING)
#define TAL_PdumpComment(ui32MemSpaceId,psCommentText)							TALPDUMP_Comment((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,psCommentText)
#define TAL_CaptureMemSpaceEnable(ui32MemSpaceId,bEnable,pbPrevState)			TALPDUMP_MemSpceCaptureEnable((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,bEnable,pbPrevState)
#define TAL_CaptureStart(dir)													TALPDUMP_CaptureStart(dir)
#define TAL_PdumpConsoleMessage													TALPDUMP_ConsoleMessage
#define TAL_PdumpMiscOutput(x, y)												TALPDUMP_MiscOutput((IMG_HANDLE)(IMG_UINTPTR)x, y)
#else
#define TAL_PdumpComment(ui32MemSpaceId,psCommentText)
#define TALPDUMP_Comment(ui32MemSpaceId,psCommentText)
#define TAL_CaptureMemSpaceEnable(ui32MemSpaceId,bEnable,pbPrevState)
#define TALPDUMP_MemSpceCaptureEnable(ui32MemSpaceId,bEnable,pbPrevState)
#define TAL_CaptureStart(dir)
#define TALPDUMP_CaptureStart(dir)
#define TAL_PdumpConsoleMessage(memspace, text)
#define TALPDUMP_ConsoleMessage(memspace, text)
#define TAL_PdumpMiscOutput(x, y)
#define TALPDUMP_MiscOutput(x, y)
#endif

#if 0
#if defined(SYSBRG_NO_BRIDGING)
#define TAL_SetPdump1MemName													TALPDUMP_SetPdump1MemName
#define TAL_PdumpComment(ui32MemSpaceId,psCommentText)							TALPDUMP_Comment((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,psCommentText)
#define TAL_PdumpConsoleMessage													TALPDUMP_ConsoleMessage
#define TAL_PdumpMiscOutput(x, y)												TALPDUMP_MiscOutput((IMG_HANDLE)(IMG_UINTPTR)x, y)
#define TAL_SetPdumpConversionSourceData										TALPDUMP_SetConversionSourceData
#define TAL_CaptureMemSpaceEnable(ui32MemSpaceId,bEnable,pbPrevState)			TALPDUMP_MemSpceCaptureEnable((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,bEnable,pbPrevState)
#define TAL_CaptureDisableCmds													TALPDUMP_DisableCmds
#define TAL_CaptureStartBinary													TAL_CaptureStartPdumpLite
#define TAL_CaptureStartPdumpLite(dir)											TALPDUMP_SetFlags(TAL_PDUMP_FLAGS_BINLITE), \
																				TALPDUMP_ClearFlags(TAL_PDUMP_FLAGS_RES & TAL_PDUMP_FLAGS_PRM), \
																				TALPDUMP_CaptureStart(dir)
#define TAL_SetPdumpFlags														TALPDUMP_SetFlags
#define TAL_ClearPdumpFlags														TALPDUMP_ClearFlags
#define TAL_GetPdumpFlags														TALPDUMP_GetFlags
#define TAL_CaptureEnableResAndPrm(bRes,bPrm)									TALPDUMP_SetFlags((bRes ? TAL_PDUMP_FLAGS_RES : 0) | (bPrm ? TAL_PDUMP_FLAGS_PRM : 0))
#define TAL_CaptureEnableOutputFormats(bPdump1,bPdump2)							TALPDUMP_SetFlags((bPdump1 ? TAL_PDUMP_FLAGS_PDUMP1 : 0) | (bPdump2 ? TAL_PDUMP_FLAGS_PDUMP2 : 0))
#define TAL_CaptureSetFilename(ui32MemSpaceId,eSetFilename,psFileName)			TALPDUMP_SetFilename((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,eSetFilename,psFileName)
#define TAL_CaptureGetFilename(ui32MemSpaceId,eSetFilename)						TALPDUMP_GetFilename((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,eSetFilename)
#define TAL_CaptureSetFileoffset(ui32MemSpaceId,eSetFilename,ui64FileOffset)	TALPDUMP_SetFileoffset((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,eSetFilename,ui64FileOffset)
#define TAL_DefinePdumpContext													TALPDUMP_DefineContext
#define TAL_CaptureEnablePdumpContext											TALPDUMP_EnableContextCapture
#define TAL_GetNoPdumpContexts													TALPDUMP_GetNoContexts
#define TAL_AddSyncToTDF(ui32SyncId,ui32MemSpaceId)								TALPDUMP_AddSyncToTDF((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32SyncId)
#define TAL_AddCommentToTDF														TALPDUMP_AddCommentToTDF
#define TAL_AddTargetConfigToTDF												TALPDUMP_AddTargetConfigToTDF
#define TAL_GenerateTDF															TALPDUMP_GenerateTDF
#define TAL_CaptureStart														TALPDUMP_CaptureStart
#define TAL_CaptureStop															TALPDUMP_CaptureStop
#define TAL_ChangeResFileName(ui32MemSpaceId,sFileName)							TALPDUMP_ChangeResFileName((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,sFileName)
#define TAL_ChangePrmFileName(ui32MemSpaceId,sFileName)							TALPDUMP_ChangePrmFileName((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,sFileName)
#define TAL_ResetResFileName(ui32MemSpaceId)									TALPDUMP_ResetResFileName((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId)
#define TAL_ResetPrmFileName(ui32MemSpaceId)									TALPDUMP_ResetPrmFileName((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId)
#define TAL_IsCaptureEnabled													TALPDUMP_IsCaptureEnabled
#define TAL_GetSemaphoreId(SrcMemSp,DestMemSp)									TALPDUMP_GetSemaphoreId((IMG_HANDLE)(IMG_UINTPTR)SrcMemSp,(IMG_HANDLE)(IMG_UINTPTR)DestMemSp)
#define TAL_Lock(ui32MemSpaceId,ui32SemaId)										TALPDUMP_Lock((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32SemaId)
#define TAL_Unlock(ui32MemSpaceId,ui32SemaId)									TALPDUMP_Unlock((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32SemaId)
#define TAL_SyncWithId(ui32MemSpaceId,ui32SyncId)								TALPDUMP_SyncWithId((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,ui32SyncId)
#define TAL_Sync(ui32MemSpaceId)												TALPDUMP_Sync((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId)
#define TAL_If(ui32MemSpaceId,pszDefStr)										TALPDUMP_If((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId,pszDefStr)
#define TAL_Else(ui32MemSpaceId)												TALPDUMP_Else((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId)
#define TAL_EndIf(ui32MemSpaceId)												TALPDUMP_EndIf((IMG_HANDLE)(IMG_UINTPTR)ui32MemSpaceId)
#define TAL_SetDefineStrings													TALPDUMP_SetDefineStrings
#else
#define TAL_SetPdump1MemName
#define TAL_PdumpComment(ui32MemSpaceId,psCommentText)
#define TAL_PdumpConsoleMessage
#define TAL_PdumpMiscOutput(x, y)
#define TAL_SetPdumpConversionSourceData
#define TAL_CaptureMemSpaceEnable(ui32MemSpaceId,bEnable,pbPrevState)
#define TAL_CaptureDisableCmds
#define TAL_CaptureStartBinary
#define TAL_CaptureStartPdumpLite(dir)
#define TAL_SetPdumpFlags
#define TAL_ClearPdumpFlags
#define TAL_GetPdumpFlags
#define TAL_CaptureEnableResAndPrm(bRes,bPrm)
#define TAL_CaptureEnableOutputFormats(bPdump1,bPdump2)
#define TAL_CaptureSetFilename(ui32MemSpaceId,eSetFilename,psFileName)
#define TAL_CaptureGetFilename(ui32MemSpaceId,eSetFilename)
#define TAL_CaptureSetFileoffset(ui32MemSpaceId,eSetFilename,ui64FileOffset)
#define TAL_DefinePdumpContext
#define TAL_CaptureEnablePdumpContext
#define TAL_GetNoPdumpContexts
#define TAL_AddSyncToTDF(ui32SyncId,ui32MemSpaceId)
#define TAL_AddCommentToTDF
#define TAL_AddTargetConfigToTDF
#define TAL_GenerateTDF
#define TAL_CaptureStart
#define TAL_CaptureStop
#define TAL_ChangeResFileName(ui32MemSpaceId,sFileName)
#define TAL_ChangePrmFileName(ui32MemSpaceId,sFileName)
#define TAL_ResetResFileName(ui32MemSpaceId)
#define TAL_ResetPrmFileName(ui32MemSpaceId)
#define TAL_IsCaptureEnabled
#define TAL_GetSemaphoreId(SrcMemSp,DestMemSp)									TALPDUMP_GetSemaphoreId((IMG_HANDLE)(IMG_UINTPTR)SrcMemSp,(IMG_HANDLE)(IMG_UINTPTR)DestMemSp)
#define TAL_Lock(ui32MemSpaceId,ui32SemaId)
#define TAL_Unlock(ui32MemSpaceId,ui32SemaId)
#define TAL_SyncWithId(ui32MemSpaceId,ui32SyncId)
#define TAL_Sync(ui32MemSpaceId)
#define TAL_If(ui32MemSpaceId,pszDefStr)
#define TAL_Else(ui32MemSpaceId)
#define TAL_EndIf(ui32MemSpaceId)
#define TAL_SetDefineStrings
#endif
#endif
/***************************************
	TAL Deprecated Functions
***************************************/
#define TAL_Deprecated this_function_is_deprecated

#define TAL_GetManglerId								TAL_Deprecated
#define TAL_GetManglerFunc								TAL_Deprecated
#define TAL_WriteDeviceMemRefWithBitPattern				TAL_Deprecated
#define TAL_GetCheckFuncId								TAL_Deprecated
#define TAL_GetCheckFunc								TAL_Deprecated
#define TAL_DeviceMemWriteDeviceMemRefWithBitPattern32	TAL_Deprecated
#define TAL_GetCheckFuncPtr								TAL_Deprecated
#define TAL_RegisterFilterWriteFunc						TAL_Deprecated
#define TAL_Pdump1MiscOutput							TAL_Deprecated
#define TAL_Pdump2MiscOutput							TAL_Deprecated
#define TAL_ChangePdumpContext							TAL_Deprecated
#define TAL_ForceSinglePdumpContext						TAL_Deprecated
#define TAL_MemSpaceGetFlags							TAL_Deprecated
#define TAL_GetMemorySpace								TAL_Deprecated
#define TAL_GetRegspaceBaseAddress						TAL_Deprecated
#define TAL_MemSpaceRegister							TAL_Deprecated // Replaced with TALSETUP_MemSpaceRegister, but new parameters are not backwards compatible
	


/*****************************************************************************
 Even older function names:
******************************************************************************/
#define TAL_MemSpacePDUMPCommentLine					TAL_PdumpComment
#define TAL_MemSpacePDUMPMiscLine						TAL_PdumpMiscOutput
#define TAL_MemSpaceGetInterruptMask					TAL_GetInterruptMask
#define TAL_MemSpaceGetInterruptNumber					TAL_GetInterruptNumber
#define TAL_MemSpaceRegisterCheckInterruptFunc			TAL_RegisterCheckInterruptFunc
#define TAL_MemSpaceGetManglerId						TAL_GetManglerId
#define	TAL_MemSpaceGetManglerFunc						TAL_GetManglerFunc
#define TAL_MemSpaceWriteWord							TAL_WriteWord
#define TAL_MemSpaceWriteWords							TAL_WriteWords
#define TAL_MemSpaceWriteShadowMemRef					TAL_WriteDeviceMemRef
#define TAL_MemSpaceReadWord							TAL_ReadWord
#define	TAL_MemSpaceReadWords							TAL_ReadWords
#define TAL_MemSpaceReadWordVerify						TAL_ReadWordVerify
#define TAL_MemSpaceGetCheckFunc						TAL_GetCheckFunc
#define TAL_MemSpacePollWord							TAL_Poll
#define TAL_PeripheralSync								TAL_Sync
#define TAL_MemSpaceShadowMemMalloc						TAL_MallocDeviceMem
#define TAL_MemSpaceShadowMemFree						TAL_FreeDeviceMem
#define TAL_MemSpaceShadowMemUpdateTarget				TAL_CopyHostToDeviceMem
#define TAL_MemSpaceShadowMemUpdateTargetRegion			TAL_CopyHostToDeviceMemRegion
#define TAL_MemSpaceShadowMemUpdateHost					TAL_CopyDeviceToHostMem
#define TAL_MemSpaceShadowMemUpdateHostRegion			TAL_CopyDeviceToHostMemRegion
#define TAL_MemSpaceShadowMemShadowMemRef				TAL_DeviceMemWriteDeviceMemRef
#define TAL_MemSpaceShadowMemShadowMemRefWithBitPattern	TAL_DeviceMemWriteDeviceMemRefWithBitPattern

#if defined (__cplusplus)
}
#endif

#endif // __TAL_OLD_H__

