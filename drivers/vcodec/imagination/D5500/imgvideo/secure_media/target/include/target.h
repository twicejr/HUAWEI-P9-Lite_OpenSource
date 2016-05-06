/*!
 *****************************************************************************
 *
 * @File       target.h
 * @Description    Target API Header File.
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

#if !defined (__TARGET_H__)
#define __TARGET_H__

#include "img_types.h"
#include "img_defs.h"
#include "lst.h"

//#include "devif_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef DOXYGEN_CREATE_MODULES
/**
* @defgroup Target Abstraction Layer
* @{
*/
/*-------------------------------------------------------------------------
* Following elements are in the Target documentation module
*------------------------------------------------------------------------*/
/**
* @name Target functions
* @{
*/
/*-------------------------------------------------------------------------
* Following elements are in the Target group
*------------------------------------------------------------------------*/
#endif

//These are the flags for the Memspace Info Structure
#define TARGET_DEVFLAG_MEM_ALLOC_MASK             (0x0000000F)  //Memory allocation mask
#define TARGET_DEVFLAG_MEM_ALLOC_SHIFT            (0)           //Memory allocation shift

#define TARGET_DEVFLAG_SEQUENTIAL_ALLOC           (0x0)         //Recommended) Flag for sequential memory allocation
#define TARGET_DEVFLAG_4K_PAGED_ALLOC             (0x1)         //Flag for sequential 4K page memory allocation (SGX535 and SGX530 only)
#define TARGET_DEVFLAG_4K_PAGED_RANDOM_ALLOC      (0x2)         //Flag for random 4K page memory allocation (SGX535 and SGX530 only)
#define TARGET_DEVFLAG_RANDOM_BLOCK_ALLOC         (0x3)         //Flag for random block memory allocation: random block and sequential base address within the block
#define TARGET_DEVFLAG_TOTAL_RANDOM_ALLOC         (0x4)         //Flag for total random memory allocation: random block and random base address within the block
#define TARGET_DEVFLAG_DEV_ALLOC                  (0x5)         //Flag for allocations to happen outside TAL on device or in kernel

#define TARGET_DEVFLAG_SGX_VIRT_MEM_MASK          (0x000000F0)  //SGX virtual memory mask
#define TARGET_DEVFLAG_SGX_VIRT_MEM_SHIFT         (4)           //SGX virtual memory shift

#define TARGET_DEVFLAG_NO_SGX_VIRT_MEMORY         (0x0)         //Recommended) No specific VMem support
#define TARGET_DEVFLAG_SGX535_VIRT_MEMORY         (0x1)         //Virtual Mem support specific to SGX535
#define TARGET_DEVFLAG_SGX530_VIRT_MEMORY         (0x2)         //Virtual Mem support specific to SGX530

#define TARGET_DEVFLAG_STUB_OUT                   (0x00000100)  //Stub out this device
#define TARGET_DEVFLAG_COALESCE_LOADS             (0x00000800)  //Attempt to Coalesce block memory loads to improve speed on some RTL systems

#define TARGET_WRAPFLAG_BURNMEM                   (0x00000001)  //Use burn-mem driver (deprecated)

#define TARGET_WRAPFLAG_SGX_CLKGATECTL_OVERWRITE  (0x00000002)  //Overwrite accesses to SGX CLKGATECTL register
#define TARGET_WRAPFLAG_MSVDX_POL_RENDEC_SPACE    (0x00000004)  //Execute a POL of MSVDX_RENDEC_SPACE on write to RENDEC_WRITE_DATA
#define    TARGET_WRAPFLAG_SIF_BUFFER_DISABLE     (0x00000008)  //Disable Buffering on the socket interface
#define TARGET_WRAPFLAG_MEM_TWIDDLE               (0x00000020)  //Enable twiddling of memory bits to make 32bit mem appear 36bit / 40bit (defined by TARGET_WRAPFLAG_MEM_TWIDDLE_MASK)
#define TARGET_WRAPFLAG_CHECK_MEM_COPY            (0x00000040)  //Enable checks to see memory has been written before continuing
#define TARGET_WRAPFLAG_ADD_DEVMEM_OFFSET_TO_PCI  (0x00000080)  //Include the device memory offset in the calculation of the address sent to PCI

#define TARGET_WRAPFLAG_IF_MASK                   (0x0000FF00)  //Interface mask
#define TARGET_WRAPFLAG_IF_SHIFT                  (8)           //Interface shift
#define TARGET_WRAPFLAG_PCI_IF                    (0x00)        //Use PIC interface
#define TARGET_WRAPFLAG_BURNMEM_IF                (0x01)        //Use Burn Mem interface
#define TARGET_WRAPFLAG_SOCKET_IF                 (0x02)        //Use socket interface
#define TARGET_WRAPFLAG_PDUMP1_IF                 (0x03)        //Use PDump1 interface
#define TARGET_WRAPFLAG_DASH_IF                   (0x04)        //Use Dash interface
#define TARGET_WRAPFLAG_DIRECT_IF                 (0x05)        //Use Direct connection with device_interface
#define TARGET_WRAPFLAG_TRANSIF_IF                (0x06)        //Use Transif connection with device_interface
#define TARGET_WRAPFLAG_NULL_IF                   (0x07)        //Use the null testing interface
#define TARGET_WRAPFLAG_POSTED_IF                 (0x08)        //Use the posted testing interface
#define TARGET_WRAPFLAG_DUMMY_IF                  (0x09)        //Use the Dummy testing interface

// Selection of customer reserved interface Ids
#define TARGET_WRAPFLAG_RESERVE1_IF               (0x18)        //Reserved for customer use
#define TARGET_WRAPFLAG_RESERVE2_IF               (0x19)        //Reserved for customer use
#define TARGET_WRAPFLAG_RESERVE3_IF               (0x1A)        //Reserved for customer use
#define TARGET_WRAPFLAG_RESERVE4_IF               (0x1B)        //Reserved for customer use
#define TARGET_WRAPFLAG_RESERVE5_IF               (0x1C)        //Reserved for customer use
#define TARGET_WRAPFLAG_RESERVE6_IF               (0x1D)        //Reserved for customer use
#define TARGET_WRAPFLAG_RESERVE7_IF               (0x1E)        //Reserved for customer use
#define TARGET_WRAPFLAG_RESERVE8_IF               (0x1F)        //Reserved for customer use

#define TARGET_WRAPFLAG_MEM_TWIDDLE_MASK          (0xF0000)
#define TARGET_WRAPFLAG_MEM_TWIDDLE_SHIFT         (16)
#define TARGET_WRAPFLAG_MEM_TWIDDLE_36BIT_OLD     (0x0)         //Old 36bit mem twiddle
#define TARGET_WRAPFLAG_MEM_TWIDDLE_36BIT         (0x1)         //36bit mem twiddle algorithm
#define TARGET_WRAPFLAG_MEM_TWIDDLE_40BIT         (0x2)         //40bit mem twiddle algorithm
#define TARGET_WRAPFLAG_MEM_TWIDDLE_DROPTOP32     (0x3)         //Drop top 32bits of address

#define TARGET_NO_IRQ                             (999)         //Interrupt number assigned when no interrupt exists

/*!
******************************************************************************
* The memory space types
******************************************************************************/
typedef enum
{
    TARGET_MEMSPACE_REGISTER,  //Memory space is mapped to device registers
    TARGET_MEMSPACE_MEMORY     //Memory space is mapped to device memory

} TARGET_eMemSpaceType;

/*!
*****************************************************************************
* This structure contains all information about a sub-device
******************************************************************************/
typedef struct TARGET_sSubDevice_tag
{
    struct TARGET_sSubDevice_tag *  psNext;               //Pointer to next sub-device
    IMG_CHAR *                      pszRegName;           //Register Sub-Device Name
    IMG_UINT64                      ui64RegStartAddress;  //Register start address
    IMG_UINT32                      ui32RegSize;          //Register Sub-Device Size
    IMG_CHAR *                      pszMemName;           //Memory Sub-Device Name
    IMG_UINT64                      ui64MemStartAddress;  //Memory start address
    IMG_UINT64                      ui64MemSize;          //Memory Sub-Device Size
    //DEVIF_sDeviceCB                 sDevIfDeviceCB;       //Device control block for devif_api
}TARGET_sSubDevice;

/*!
*****************************************************************************
* This structure contains all information about a device
******************************************************************************/
typedef struct
{
    IMG_CHAR *           pszDeviceName;        //Device name
    IMG_UINT64           ui64DeviceBaseAddr;   //Base address of the device registers.
    IMG_UINT64           ui64MemBaseAddr;      //Base address of the default memory region.
    IMG_UINT64           ui64DefMemSize;       //Size of the default memory region.
    IMG_UINT64           ui64MemGuardBand;     //Size of the default memory guard band.
    IMG_HANDLE           hMemAllocator;        //Handle to the memory allocation context
    IMG_CHAR *           pszMemArenaName;      //Name of the memory arena to which the
    IMG_UINT32           ui32DevFlags;         //Device Flags
    IMG_UINT32           ui32HostTargetRatio;  //Ratio between host and target clock speeds
    IMG_UINT32           ui32WrapFlags;        //Wrapper Flags
    TARGET_sSubDevice *  psSubDevice;          //Sub-Device list
    IMG_BOOL             bConfigured;          //Gets set when the device is configured
    //DEVIF_sDeviceCB      sDevIfDeviceCB;       //Device control block for devif_api


    // Mapping information for the device. This has to be initilised before
    // passing the structure to target.
    IMG_VOID *           pvKmRegBase;          //CPU virtual address of register base 
    IMG_UINT32           ui32RegSize;          //Register base

} TARGET_sDevice;

/*!
*****************************************************************************
* This structure contains all information about a device register
******************************************************************************/
typedef struct
{
    IMG_UINT64  ui64RegBaseAddr;   //Base address of device registers
    IMG_UINT32  ui32RegSize;       //Size of device register block
    IMG_UINT32  ui32InterruptNum;  //The interrupt number

} TARGET_sRegister;

/*!
*****************************************************************************
* This structure contains all information about a device memory region
******************************************************************************/
typedef struct
{
    IMG_UINT64  ui64MemBaseAddr;   //Base address of memory region
    IMG_UINT64  ui64MemSize;       //Size of memory region
    IMG_UINT64  ui64MemGuardBand;  //Memory guard band

} TARGET_sMemoryRegion;

/*!
*****************************************************************************
* This structure contains all information about the device memory space
******************************************************************************/
typedef struct
{
    IMG_CHAR *                pszMemorySpaceName;  //Memory space name
    TARGET_eMemSpaceType      eMemorySpaceType;    //Memory space type
    union
    {
        TARGET_sRegister      sRegister;           //Device register info
        TARGET_sMemoryRegion  sMemoryRegion;       //Device memory region info
    };

    TARGET_sDevice *          psDevice;            //Information about the relevant device

} TARGET_sMemorySpace;

//PCI Card Information
typedef struct
{
    IMG_UINT32      ui32VendorId;       //Vendor ID
    IMG_UINT32      ui32DeviceId;       //Device ID

} TARGET_sPciCard;

//PCI Memory Information
typedef struct TARGET_sPciMemory_tag
{
    struct TARGET_sPciMemory_tag *  psNext;         //Pointer to next element in the list
    IMG_CHAR *                      pszDeviceName;  //Device Name
    IMG_UINT32                      ui32Bar;        //PCI Bar Number
    IMG_UINT32                      ui32Offset;     //PCI offset
    IMG_UINT32                      ui32Size;       //PCI size
    IMG_UINT64                      ui64BaseAddr;   //Device Base Address (required for calculation of virtual address)

} TARGET_sPciMemory;

//PCI Device Information
typedef struct TARGET_sPciDevice_tag
{
    struct TARGET_sPciDevice_tag *  psNext;         //Pointer to next element in the list
    IMG_CHAR *                      pszDeviceName;  //Device name
    IMG_UINT32                      ui32Bar;        //PCI Bar Number
    IMG_UINT32                      ui32Offset;     //PCI offset
    IMG_UINT32                      ui32Size;       //PCI Size

} TARGET_sPciDevice;

//PCI Interface Information
typedef struct TARGET_sPciInterface_tag
{
    struct TARGET_sPciInterface_tag *  psNext;               //Pointer to next element in the list
    IMG_CHAR *                         pszPciInterfaceName;  //PCI Interface name
    TARGET_sPciCard *                  psPciCard;            //PCI card info structure
    TARGET_sPciMemory *                psPciMemory;          //PCI memory base information
    TARGET_sPciDevice *                psPciDevice;          //PCI device base information
} TARGET_sPciInterface;

//Wrapped PCI memory/device Information
typedef struct
{
    TARGET_sPciMemory  sPciMemory;         //PCI Memory Information
    TARGET_sPciDevice  sPciDevice;         //PCI Device Information
    IMG_UINT32         ui32DevMemoryBase;  //Base address of the device's view of memory

} TARGET_sWrappedPci;

//Device Name Information
typedef struct TARGET_sName_tag
{
    struct TARGET_sName_tag *  psNext;          //Pointer to next in the list
    IMG_CHAR *                 pszDeviceName;   //Device name
    IMG_CHAR *                 pszRegBaseName;  //Register Basename (used in RTL Select Vector)
    IMG_CHAR *                 pszMemBaseName;  //Memory Basename (used in RTL Select Vector)

} TARGET_sName;

//Device IP Information
typedef struct TARGET_sDeviceIp_tag
{
    struct TARGET_sDeviceIp_tag *  psNext;            //Pointer to next element in the list
    IMG_CHAR *                     pszDeviceName;     //Device Name
    IMG_UINT32                     ui32PortId;        //Port ID
    IMG_UINT32                     ui32IpAddr1;       //IP address 1
    IMG_UINT32                     ui32IpAddr2;       //IP address 2
    IMG_UINT32                     ui32IpAddr3;       //IP address 3
    IMG_UINT32                     ui32IpAddr4;       //IP address 4
    IMG_CHAR *                     pszRemoteName;     //Remote Machine, Host Name (Alternative to IP address)
    struct TARGET_sDeviceIp_tag *  psParentDevice;    //Parent Device Name, parent socket on which to start this device
    IMG_VOID *                     pDeviceInterface;  //Pointer to Device Interface Class
    IMG_BOOL                       bUseBuffer;        ///Use the socket buffer

} TARGET_sDeviceIp;

//Direct interface Information
typedef struct TARGET_sDirectIF_tag
{
    struct TARGET_sDirectIF_tag *  psNext;            //Pointer to next element in the list
    IMG_CHAR *                     pszDeviceName;     //Device name
    struct TARGET_sDirectIF_tag *  psParentDevice;    //Parent Device Info Struct
    IMG_VOID *                     pDeviceInterface;  //Pointer to Device Interface Class

} TARGET_sDirectIF;

//Device PDump Feed Information
typedef struct TARGET_sPDumpIF_tag
{
    struct TARGET_sPDumpIF_tag *  psNext;              //Pointer to next element in the list
    IMG_CHAR *                    pszDeviceName;       //Device name
    IMG_CHAR *                    pszCommandFile;      //File sharing pdump commands
    IMG_CHAR *                    pszInputDirectory;   //Directory in which files being read should be
    IMG_CHAR *                    pszOutputDirectory;  //Directory in which files being written should be
    IMG_CHAR *                    pszSendData;         //File for transfer of data between device and host
    IMG_CHAR *                    pszReturnData;       //File for returned data/

} TARGET_sPDumpIF;

//Device dashif Information
typedef struct TARGET_sDashIF_tag
{
    struct TARGET_sDashIF_tag *  psNext;          //Pointer to next element in the list
    IMG_CHAR *                   pszDeviceName;   //Device name
    IMG_CHAR *                   pszDashName;     //Dash Name
    IMG_UINT32                   ui32DeviceBase;  //Base Address of Device(Regs)
    IMG_UINT32                   ui32DeviceSize;  //Size of Device
    IMG_UINT32                   ui32MemoryBase;  //Base Address of Memory
    IMG_UINT32                   ui32MemorySize;  //Memory Size

} TARGET_sDashIF;

//Device posted if Information
typedef struct TARGET_sPostIF_tag
{
    struct TARGET_sPostIF_tag *  psNext;              //Pointer to next element in the list
    IMG_CHAR *                   pszDeviceName;       //Device name
    IMG_UINT32                   ui32RegBar;          //PCI Bar of Register Bus
    IMG_UINT32                   ui32RegBaseAddr;     //Address offset of Registers
    IMG_UINT32                   ui32MemBar;          //PCI Bar of Memory Bus
    IMG_UINT32                   ui32MemBaseAddr;     //Address offset of Memory
    IMG_UINT32                   ui32PostedIfOffset;  //Address offset of posted IF registers
    IMG_UINT32                   ui32DeviceId;        //Device Id needed for the reg_io api
    IMG_VOID*                    psSubDevice;         //Info on devif on which to call
    IMG_UINT32                   ui32BufferSize;      //Size of Command and Read buffers
} TARGET_sPostIF;

//Wrapper control Information
typedef struct
{
    IMG_UINT32  ui32HostTargetCycleRatio;  //Host/Target cycle ratio
    IMG_UINT32  ui32Flags;                 //Wrapper flags

} TARGET_sWrapperControl;

//Burn mem Information
typedef struct  TARGET_sBurnMem_tag
{
    struct TARGET_sBurnMem_tag *  psNext;              //Pointer to next element in the list
    IMG_CHAR *                    pszDeviceName;       //Device name
    IMG_CHAR                      cDeviceId;           //Device id
    IMG_UINT32                    ui32MemStartOffset;  //Memory start offset
    IMG_UINT32                    ui32MemSize;         //Memory size

} TARGET_sBurnMem;

//PCI Information
typedef struct
{
    TARGET_sPciCard     sPciCard;     //PCI Card info
    TARGET_sWrappedPci  sWrappedPci;  //PCI Wrapper info

} TARGET_sPci;

//Full" set of information about the device.
typedef struct
{
    TARGET_sWrapperControl  sWraperControl;  //Wrapper control info
    IMG_UINT32              ui32IfType;      //Derived from the wrapper flags

    union
    {
        TARGET_sPci         sPci;            //PCI Interface Information
        TARGET_sBurnMem     sBurnMem;        //Burnmem Interface Information
        TARGET_sDeviceIp    sDeviceIp;       //IP Interface Information
        TARGET_sDashIF      sDashIF;         //DASH Interface Information
        TARGET_sPDumpIF     sPDumpIF;        //PDUMP1 Interface Information
        TARGET_sPostIF      sPostIF;         //Post Interface Information
    };

} TARGET_sFull;

// Device List
typedef struct
{
    LST_LINK;       //List link (allows the structure to be part of a MeOS list)
    TARGET_sDevice  sDevice;

} TARGET_sDeviceItem;

// Memory Space List
typedef struct
{
    LST_LINK;           //List link (allows the structure to be part of a MeOS list)
    TARGET_sMemorySpace  sMemorySpace;

} TARGET_sMemorySpaceItem;

// Pdump Context List
typedef struct
{
    LST_LINK;
    IMG_CHAR * pszContextName;
    IMG_CHAR ** apszBlockNames;

} TARGET_sPdumpCtxItem;


typedef struct
{
    TARGET_sWrapperControl *  psWrapperControl;
    TARGET_sPciCard *         psPciCard;
    TARGET_sPciInterface *    psPciInterface;
    TARGET_sBurnMem *         psBurnMem;
    TARGET_sPciDevice *       psPciDevice;
    TARGET_sPciMemory *       psPciMemory;
    TARGET_sDeviceIp *        psDeviceIp;
    TARGET_sDirectIF *        psDirectIF;
    TARGET_sName *            psName;
    TARGET_sPDumpIF *         psPDumpIF;
    TARGET_sDashIF *          psDashIF;
    TARGET_sPostIF *          psPostIF;

    IMG_CHAR *                pszGetSubDev;
    IMG_CHAR *                pszConfigFile;

    LST_T                     lDeviceItem;          //List of device items
    LST_T                     lMemorySpaceItem;     //List of memspace items

    IMG_UINT32                ui32LineNo;
    IMG_UINT32                ui32OverrideIf;

    IMG_BOOL                  bWrapperControl;
    IMG_BOOL                  bPciCard;
    IMG_BOOL                  bOverrideWrapper;

    IMG_UINT32                ui32DevNum;
    TARGET_sDevice *          pasDevices;
    IMG_UINT32                ui32MemSpceNum;
    TARGET_sMemorySpace *     pasMemSpces;

    LST_T                     lPdumpCtx;            //List of pdump contexts only used with test config files

} TARGET_sTargetConfig;


/*!
******************************************************************************

@Function                TARGET_Initialise

@Description

This function is used to load a TAL config file if required and initialise the
internal structure

@Input        None.

@ReturnIMG_RESULT  : This function returns either IMG_SUCCESS or an
                     error code.

******************************************************************************/
IMG_RESULT TARGET_Initialise(TARGET_sTargetConfig * psTargetConfig);

/*!
******************************************************************************

@Function                TARGET_Deinitialise

@Description

This function is used to de-initialise the target.

Typically this function will cleanup memory allocations

@Return    None.

******************************************************************************/
IMG_RESULT TARGET_Deinitialise(TARGET_sTargetConfig * psTargetConfig);

#ifndef IMG_KERNEL_MODULE

/*!
******************************************************************************

 @Function                TARGET_SaveConfig

 @Description

 This function is used to save a copy of the config file to a given folder.

 @Input        pszFilePath        : A zero terminated string containing the path
                              and name of the target file.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_SaveConfig(const IMG_CHAR * const pszFilePath);

/*!
******************************************************************************

 @Function                TARGET_GetPciInterface

 @Description

 This function is used to get the PCI interface information from the configuration
 file.

 @Input        TARGET_sPciInterface **  : A pointer to a structure in which the interface
                                       information is returned.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetPciInterface(const TARGET_sPciInterface ** ppsPciInterface);

/*!
******************************************************************************

 @Function                TARGET_SetPciInterface

 @Description

 This function is used to set the PCI card, device base, and memory base
 information, from the interface that is being used.

 @Input        TARGET_sPciInterface *  : A pointer to the interface info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_SetPciInterface(const TARGET_sPciInterface * const psPciInterface);

/*!
******************************************************************************

 @Function                TARGET_GetPciCard

 @Description

 This function is used to get the PCI card information from the configuration
 file.

 @Input        None

 @Output    TARGET_sPciCard ** : A pointer to the PciCard info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
 IMG_RESULT TARGET_GetPciCard(const TARGET_sPciCard ** psPciCard);

/*!
******************************************************************************

 @Function                TARGET_GetPciMemory

 @Description

 This function is used to get the PCI memory base information from the
 configuration file.

 @Input        pszDevName         : A pointer to the device name.

 @Output    TARGET_sPciMemory ** : A pointer to the pci memory info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.
******************************************************************************/
 IMG_RESULT TARGET_GetPciMemory(const IMG_CHAR * const pszDevName,
                                const TARGET_sPciMemory ** ppsPciMemory);

/*!
******************************************************************************

 @Function                TARGET_GetPciDevice

 @Description

 This function is used to get the PCI device base information from the
 configuration file.

 @Input        pszDevName         : A pointer to the device name.

 @Output    TARGET_sPciDevice ** : A pointer to the pci device info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.
******************************************************************************/
IMG_RESULT TARGET_GetPciDevice(const IMG_CHAR * const pszDevName,
                               const TARGET_sPciDevice ** ppsPciDevice);

/*!
******************************************************************************

 @Function                TARGET_GetPostIF

 @Description

 This function is used to get the Posted interface information from the configuration
 file.

 @Input        TARGET_sPciInterface **  : A pointer to a stucture in which the interface
                                       information is returned.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetPostIF(const IMG_CHAR * const pszDeviceName,
                            const TARGET_sPostIF ** ppsPostIF);

/*!
******************************************************************************

 @Function                TARGET_GetBurnMem

 @Description

 This function is used to get the burn mem information from the
 configuration file.

 @Input        pszDevName       : A pointer to the device name.

 @Output    TARGET_sBurnMem ** : A pointer to the device burn mem info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetBurnMem(const IMG_CHAR * const pszDevName,
                             const TARGET_sBurnMem ** ppsBurnMem);

/*!
******************************************************************************

 @Function                TARGET_GetDeviceIp

 @Description

 This function is used to get the device ip information from the
 configuration file.

 @Input        pszDevName        : A pointer to the device name.

 @Output    TARGET_sDeviceIp ** : A pointer to the device ip info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetDeviceIp(const IMG_CHAR * const pszDevName,
                              const TARGET_sDeviceIp ** ppsDeviceIp);

/*!
******************************************************************************

 @Function                TARGET_GetDirectIF

 @Description

 This function is used to get the Direct Interface information from the
 configuration file.

 @Input        pszDevName        : A pointer to the device name.

 @Output    TARGET_sDeviceIp ** : A pointer to the device ip info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetDirectIF(const IMG_CHAR * const pszDevName,
                              const TARGET_sDirectIF ** ppsDirectIF);

/*!
******************************************************************************

 @Function                TARGET_GetName

 @Description

 This function is used to get the Name information from the
 configuration file, used only against RTL Simulation.

 @Input        pszDevName        : A pointer to the device name.

 @Output    TARGET_sDeviceIp ** : A pointer to the device ip info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetName(const IMG_CHAR * const pszDevName,
                          const TARGET_sName ** ppsName);

/*!
******************************************************************************

 @Function                TARGET_GetDashIF

 @Description

 This function is used to get the DashIF information from the
 configuration file.

 @Input        pszDevName  : A pointer to the device name.

 @Output    TARGET_sDashIF ** : A pointer to the DashIF info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetDashIF(const IMG_CHAR * const pszDevName,
                            const TARGET_sDashIF ** ppsDashIF);

/*!
******************************************************************************

 @Function                TARGET_GetPDumpIF

 @Description

 This function is used to get the PDumpIF information from the
 configuration file.

 @Input        pszDevName        : A pointer to the device name.

 @Output    TARGET_sPDumpIF ** : A pointer to the PDumpIF info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetPDumpIF(const IMG_CHAR * const pszDevName,
                             const TARGET_sPDumpIF ** ppsPDumpIF);

/*!
******************************************************************************

 @Function                TARGET_GetPostedIF

 @Description

 This function is used to get the Posted Interface information from the
 configuration file.

 @Input        pszDevName      : A pointer to the device name.

 @Output    TARGET_sPostIF ** : A pointer to the PDumpIF info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetPostedIF(const IMG_CHAR * const pszDevName,
                              const TARGET_sPostIF ** ppsPostIF);

/*!
******************************************************************************

 @Function                TARGET_GetFull

 @Description

 This function is used to get the fulls set of device information from the
 configuration file.

 @Input        pszDevName        : A pointer to the device name.

 @Output     TARGET_sFull **      : A pointer to the Full info.

******************************************************************************/
IMG_RESULT TARGET_GetFull(const IMG_CHAR * const pszDeviceName,
                          TARGET_sFull * const psFull);

/*!
******************************************************************************

 @Function                TARGET_GetWrapperControl

 @Description

 This function is used to get the wrapper control information from the
 configuration file.

 @Input        None:

 @Output    TARGET_sWrapperControl ** : A pointer to the pci Wrapper Control info.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
IMG_RESULT TARGET_GetWrapperControl(const TARGET_sWrapperControl ** psWrapperControl);

/*!
******************************************************************************

 @Function                TARGET_OverrideWrapper

 @Description

 This function overrides the wrapper setup in the config file

 @Input        pcArgs        :    command line arguements

 @Return    IMG_UINT32    :    new position in command line parameters, 0 for failure

 Syntax:

 SocketIF: s \<device name> \<port> [ \<hostname> ]

 ******************************************************************************/
IMG_BOOL TARGET_OverrideWrapper(const IMG_CHAR * const pcArgs);

/*!
******************************************************************************

@Function  TARGET_SetConfigFile

@Description

The default target config file location is hard-coded. This function will
override the hard-coded value if it is called prior to TARGET_Initialise().

@Input pszFilePath : Path and file name of the target config file.

@Returnnone.

******************************************************************************/
IMG_RESULT TARGET_SetConfigFile(const IMG_CHAR * const pszFilePath);

#endif /* NOT IMG_KERNEL_MODULE */

#ifdef DOXYGEN_CREATE_MODULES
/**
* @}
*/
/*-------------------------------------------------------------------------
* end of the Target group
*------------------------------------------------------------------------*/
/**
* @}
*/
/*-------------------------------------------------------------------------
* end of the Target documentation module
*------------------------------------------------------------------------*/
#endif

#if defined(__cplusplus)
}
#endif

#endif /* __TARGET_H__    */


