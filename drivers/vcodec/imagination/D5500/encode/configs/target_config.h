/*!
 *****************************************************************************
 *
 * @File       target_config.h
 * @Title      Device Specific memory configuration
 * @Description    This is a configurable header file which sets up the memory
 *  spaces for a fixed device.
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

#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

#include <img_types.h>
#include <img_defs.h>
#include <lst.h>
#include <target.h>

#define TAL_TARGET_NAME         "TOPAZ"
#define TAL_DEVICE_BASE_ADDRESS 0x00000000

static TARGET_sWrapperControl sWrapperControl =
{
    (IMG_UINT32)0,   //IMG_UINT32      ui32HostTargetCycleRatio;   //Host/Target cycle ratio
    (IMG_UINT32)0,   //IMG_UINT32      ui32Flags;	                //Wrapper flags
};

static TARGET_sPciCard sPciCard =
{
    (IMG_UINT32)0x1010,   //IMG_UINT32      ui32VendorId;       //Vendor ID
    (IMG_UINT32)0x1CF2,   //IMG_UINT32      ui32DeviceId;       //Device ID
};

static TARGET_sPciDevice sPciDevice =
{
                  IMG_NULL, //struct TARGET_sPciDevice_tag*psNext;         //Pointer to next element in the list
	              IMG_NULL, //IMG_CHAR *                   pszDeviceName;  //Device name
	         (IMG_UINT32)1, //IMG_UINT32                   ui32Bar;        //PCI Bar Number
	(IMG_UINT32)0x00000000, //IMG_UINT32                   ui32Offset;     //PCI offset
	(IMG_UINT32)0x00020000, //IMG_UINT32                   ui32Size;       //PCI Size
};

static TARGET_sPciMemory sPciMemory =
{
                  IMG_NULL, //struct TARGET_sPciMemory_tag*psNext;         //Pointer to next element in the list
	              IMG_NULL, //IMG_CHAR *                   pszDeviceName;  //Device name
	         (IMG_UINT32)2, //IMG_UINT32                   ui32Bar;        //PCI Bar Number
	(IMG_UINT32)0x00000000, //IMG_UINT32                   ui32Offset;     //PCI offset
	(IMG_UINT32)0x10000000, //IMG_UINT32                   ui32Size;       //PCI Size
	(IMG_UINT64)0x00000000, //IMG_UINT64                   ui64BaseAddr;   //Device Base Address (required for calculation of virtual address)
};

static TARGET_sPciInterface sPciInterface =
{
	     IMG_NULL,      //struct TARGET_sPciInterface_tag *    psNext;             //Pointer to next element in the list
	     "",            //IMG_CHAR *                           pszPciInterfaceName;//PCI Interface name
	     &sPciCard,     //TARGET_sPciCard *                    psPciCard;          //PCI card info structure
	     &sPciMemory,   //TARGET_sPciMemory *                  psPciMemory;        //PCI memory base information
	     &sPciDevice,   //TARGET_sPciDevice *                  psPciDevice;        //PCI device base information
};

static TARGET_sBurnMem sBurnMem =
{
	     IMG_NULL,   //struct TARGET_sPciDevice_tag*psNext;         //Pointer to next element in the list
	     IMG_NULL,   //IMG_CHAR *                   pszDeviceName;  //Device name
	(IMG_UINT32)0,   //IMG_UINT32                   ui32Bar;        //PCI Bar Number
	(IMG_UINT32)0,   //IMG_UINT32                   ui32Offset;     //PCI offset
	(IMG_UINT32)0,   //IMG_UINT32                   ui32Size;       //PCI Size
};

static TARGET_sDeviceIp sDeviceIp =
{
	           IMG_NULL,    //struct TARGET_sDeviceIp_tag *     psNext;	            //Pointer to next element in the list
	           IMG_NULL,    //IMG_CHAR *			            pszDeviceName;      //Device Name
	      (IMG_UINT32)0,    //IMG_UINT32			            ui32PortId;         //Port ID
	      (IMG_UINT32)0,    //IMG_UINT32			            ui32IpAddr1;        //IP address 1
	      (IMG_UINT32)0,    //IMG_UINT32			            ui32IpAddr2;        //IP address 2
	      (IMG_UINT32)0,    //IMG_UINT32			            ui32IpAddr3;        //IP address 3
	      (IMG_UINT32)0,    //IMG_UINT32			            ui32IpAddr4;        //IP address 4
	           IMG_NULL,    //IMG_CHAR *                        pszRemoteName;      //Remote Machine, Host Name (Alternative to IP address)
	           IMG_NULL,    //struct TARGET_sDeviceIp_tag *     psParentDevice;     //Parent Device Name, parent socket on which to start this device
	           IMG_NULL,    //IMG_VOID *			            pDeviceInterface;   //Pointer to Device Interface Class
	(IMG_BOOL)IMG_FALSE,    //IMG_BOOL			                bUseBuffer;         ///Use the socket buffer
};

static TARGET_sDirectIF sDirectIF =
{
	     IMG_NULL,   //struct TARGET_sDirectIF_tag *   psNext;              //Pointer to next element in the list
	     IMG_NULL,   //IMG_CHAR *                      pszDeviceName;       //Device name
	     IMG_NULL,   //IMG_VOID *                      psParentDevice;      //Parent Device Info Struct
	     IMG_NULL,   //IMG_VOID *		               pDeviceInterface;   //Pointer to Device Interface Class
};

static TARGET_sName sName =
{
	     IMG_NULL,   //struct TARGET_sName_tag *    psNext;	            //Pointer to next in the list
	     IMG_NULL,   //IMG_CHAR *                   pszDeviceName;		//Device name
	     IMG_NULL,   //IMG_CHAR *                   pszRegBaseName;		//Register Basename (used in RTL Select Vector)
	     IMG_NULL,   //IMG_CHAR *                   pszMemBaseName;		//Memory Basename (used in RTL Select Vector)
};

static TARGET_sPDumpIF sPDumpIF =
{
	     IMG_NULL,   //struct TARGET_sPDumpIF_tag * psNext;             //Pointer to next element in the list
	     IMG_NULL,   //IMG_CHAR *                   pszDeviceName;      //Device name
	     IMG_NULL,   //IMG_CHAR *                   pszCommandFile;     //File sharing pdump commands
	     IMG_NULL,   //IMG_CHAR *                   pszInputDirectory;  //Directory in which files being read should be
	     IMG_NULL,   //IMG_CHAR *                   pszOutputDirectory; //Directory in which files being written should be
	     IMG_NULL,   //IMG_CHAR *                   pszSendData;        //File for transfer of data between device and host
	     IMG_NULL,   //IMG_CHAR *                   pszReturnData;      //File for returned data/
};

static TARGET_sDashIF sDashIF =
{
	     IMG_NULL,   //struct TARGET_sDashIF_tag *  psNext;     	    //Pointer to next element in the list
	     IMG_NULL,   //IMG_CHAR *                   pszDeviceName;      //Device name
	     IMG_NULL,   //IMG_CHAR *                   pszDashName;        //Dash Name
	(IMG_UINT32)0,   //IMG_UINT32                   ui32DeviceBase;     //Base Address of Device(Regs)
	(IMG_UINT32)0,   //IMG_UINT32                   ui32DeviceSize;     //Size of Device
	(IMG_UINT32)0,   //IMG_UINT32                   ui32MemoryBase;     //Base Address of Memory
	(IMG_UINT32)0,   //IMG_UINT32                   ui32MemorySize;     //Memory Size
};

static TARGET_sPostIF sPostIF =
{
	     IMG_NULL,   //struct TARGET_sPostIF_tag * psNext;			    //Pointer to next element in the list
	     IMG_NULL,   //IMG_CHAR *                  pszDeviceName;       //Device name
	(IMG_UINT32)0,   //IMG_UINT32	               ui32RegBar;          //PCI Bar of Register Bus
	(IMG_UINT32)0,   //IMG_UINT32	               ui32RegBaseAddr;     //Address offset of Registers
	(IMG_UINT32)0,   //IMG_UINT32	               ui32MemBar;          //PCI Bar of Memory Bus
	(IMG_UINT32)0,   //IMG_UINT32	               ui32MemBaseAddr;     //Address offset of Memory
	(IMG_UINT32)0,   //IMG_UINT32	               ui32PostedIfOffset;  //Address offset of posted IF registers
	(IMG_UINT32)0,   //IMG_UINT32	               ui32DeviceId;        //Device Id needed for the reg_io api
	     IMG_NULL,   //IMG_VOID*	               psSubDevice;         //Info on devif on which to call
	(IMG_UINT32)0,   //IMG_UINT32	               ui32BufferSize;      //Size of Command and Read buffers
};


/*****************************************************************************
	DEVICE DEFINITION (Only to use with normal TAL)
	- Device name
	- Base address of the device registers.
	- Base address of the default memory region.
	- Size of the default memory region.
	- Size of the default memory guard band.
	- Device control block for devif_api
	- Name of the memory arena for the device
	- Device Flags
    - ui32HostTargetRatio
    - ui32WrapFlags
	- Sub-Device list
	- Gets set when the device is configured
*****************************************************************************/

static TARGET_sDevice asDevice[] =
{
	{
		TAL_TARGET_NAME,
		TAL_DEVICE_BASE_ADDRESS,
		0x00000000,
		0x10000000,
		0x00000000,
		IMG_NULL,
		IMG_NULL,
		0x00000000,
		1000,
		0x00000000,
		IMG_NULL,
		IMG_FALSE
	}
};

static TARGET_sMemorySpace asMemorySpace[] =
{
	// Multicore sync RAM
	{ "REG_TOPAZHP_MULTICORE",			TARGET_MEMSPACE_REGISTER,      {{0x00000000,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_DMAC",               		TARGET_MEMSPACE_REGISTER,      {{0x00000400,     0x000000ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0] },
	{ "REG_COMMS",               		TARGET_MEMSPACE_REGISTER,      {{0x00000500,     0x000000ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0] },
	{ "REG_MTX",              			TARGET_MEMSPACE_REGISTER,      {{0x00000800,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_MMU",              			TARGET_MEMSPACE_REGISTER,      {{0x00000C00,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_TEST",            	TARGET_MEMSPACE_REGISTER,      {{0xFFFF0000,     0x000001ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REGMTXRAM",              		TARGET_MEMSPACE_REGISTER,      {{0x80000000,     0x0000ffff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },


#if defined(HW_3_X)
	{ "REG_TOPAZHP_CORE_0",           	TARGET_MEMSPACE_REGISTER,      {{0x00001000,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_0",			TARGET_MEMSPACE_REGISTER,      {{0x00001400,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_0",	TARGET_MEMSPACE_REGISTER,      {{0x00001800,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_COREEXT_0",			TARGET_MEMSPACE_REGISTER,      {{0x00001C00,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },

	{ "REG_TOPAZHP_CORE_1",				TARGET_MEMSPACE_REGISTER,      {{0x00002000,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_1",			TARGET_MEMSPACE_REGISTER,      {{0x00002400,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_1",	TARGET_MEMSPACE_REGISTER,      {{0x00002800,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_COREEXT_1",			TARGET_MEMSPACE_REGISTER,      {{0x00002C00,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },

	{ "REG_TOPAZHP_CORE_2",				TARGET_MEMSPACE_REGISTER,      {{0x00003000,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_2",			TARGET_MEMSPACE_REGISTER,      {{0x00003400,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_2",	TARGET_MEMSPACE_REGISTER,      {{0x00003800,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_COREEXT_2",			TARGET_MEMSPACE_REGISTER,      {{0x00003C00,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },

	{ "REG_TOPAZHP_CORE_3",				TARGET_MEMSPACE_REGISTER,      {{0x00004000,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_3",			TARGET_MEMSPACE_REGISTER,      {{0x00004400,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_3",	TARGET_MEMSPACE_REGISTER,      {{0x00004800,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_COREEXT_3",			TARGET_MEMSPACE_REGISTER,      {{0x00004C00,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
#endif
#if defined(HW_4_0)
	{ "REG_TOPAZHP_CORE_0",           	TARGET_MEMSPACE_REGISTER,      {{0x00001000,     0x000007ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_0",			TARGET_MEMSPACE_REGISTER,      {{0x00001800,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_0",	TARGET_MEMSPACE_REGISTER,      {{0x00001c00,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },

	{ "REG_TOPAZHP_CORE_1",				TARGET_MEMSPACE_REGISTER,      {{0x00002000,     0x000007ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_1",			TARGET_MEMSPACE_REGISTER,      {{0x00002800,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_1",	TARGET_MEMSPACE_REGISTER,      {{0x00002c00,     0x000003ff,	TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },

	{ "REG_TOPAZHP_CORE_2",				TARGET_MEMSPACE_REGISTER,      {{0x00003000,     0x000007ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_2",			TARGET_MEMSPACE_REGISTER,      {{0x00003800,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_2",	TARGET_MEMSPACE_REGISTER,      {{0x00003c00,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },

	{ "REG_TOPAZHP_CORE_3",				TARGET_MEMSPACE_REGISTER,      {{0x00004000,     0x000007ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_VLC_CORE_3",			TARGET_MEMSPACE_REGISTER,      {{0x00004800,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
	{ "REG_TOPAZHP_DEBLOCKER_CORE_3",	TARGET_MEMSPACE_REGISTER,      {{0x00004c00,     0x000003ff,   TARGET_NO_IRQ}}, (TARGET_sDevice *)&asDevice[0]  },
#endif
	{ "FW",								TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0x00800000, 0         }}, (TARGET_sDevice *)&asDevice[0]  },
	{ "SYSMEM",							TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0,          0         }}, (TARGET_sDevice *)&asDevice[0]  },
	{ "MEMSYSMEM",						TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0,          0         }}, (TARGET_sDevice *)&asDevice[0]  },
	{ "MEM",							TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0,          0         }}, (TARGET_sDevice *)&asDevice[0]  },
	{ "FB",                     		TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0,          0         }}, (TARGET_sDevice *)&asDevice[0]  },
	{ "MEMDMAC_00",                     TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0,          0         }}, (TARGET_sDevice *)&asDevice[0]  },
	{ "MEMDMAC_01",                     TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0,          0         }}, (TARGET_sDevice *)&asDevice[0]  },
	{ "MEMDMAC_02",                     TARGET_MEMSPACE_MEMORY,        {{0x00000000,     0,          0         }}, (TARGET_sDevice *)&asDevice[0]  },
};

#define MEMORYSPACES_NUM (sizeof(asMemorySpace)/sizeof(TARGET_sMemorySpace))
#define DEVICES_NUM (sizeof(asDevice)/sizeof(TARGET_sDevice))

#define LINE_NUMBER      (0x00)
#define OVERRIDE_IF      (0x00)
#define WRAPPER_CONTROL  (IMG_FALSE)
#define PCI_CARD         (IMG_FALSE)
#define OVERRIDE_WRAPPER (IMG_FALSE)

static TARGET_sTargetConfig gsTargetConfig =
{
    &sWrapperControl,
    &sPciCard,
    &sPciInterface,
    &sBurnMem,
    &sPciDevice,
    &sPciMemory,
    &sDeviceIp,
    &sDirectIF,
    &sName,
    &sPDumpIF,
    &sDashIF,
    &sPostIF,

    IMG_NULL,
    IMG_NULL,

    {IMG_NULL,IMG_NULL},
    {IMG_NULL,IMG_NULL},

    LINE_NUMBER,
    OVERRIDE_IF,

    WRAPPER_CONTROL,
    PCI_CARD,
    OVERRIDE_WRAPPER,

    DEVICES_NUM,
    &asDevice[0],
    MEMORYSPACES_NUM,
    &asMemorySpace[0]
};


#endif
