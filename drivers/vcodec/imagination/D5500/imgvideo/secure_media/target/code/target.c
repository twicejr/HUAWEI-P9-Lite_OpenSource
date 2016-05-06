/*!
 *****************************************************************************
 *
 * @File       target.c
 * @Description    Dummy Target for PDMUP testing.
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

#include "target.h"
#include "img_errors.h"
#include "img_errors.h"
#include "tal.h"
#include "system.h"

#ifndef TARGET_CONF_BY_HEADER_FILE
    static TARGET_sTargetConfig gsTargetConfig = {
                                            IMG_NULL, //TARGET_sPciCard * psWrapperControl;
                                            IMG_NULL, //TARGET_sPciCard * psPciCard;
                                            IMG_NULL, //TARGET_sPciInterface * psPciInterface;
                                            IMG_NULL, //TARGET_sBurnMem * psBurnMem;
                                            IMG_NULL, //TARGET_sPciDevice * psPciDevice;
                                            IMG_NULL, //TARGET_sPciMemory * psPciMemory;
                                            IMG_NULL, //TARGET_sDeviceIp * psDeviceIp;
                                            IMG_NULL, //TARGET_sDirectIF * psDirectIF;
                                            IMG_NULL, //TARGET_sName * psName;
                                            IMG_NULL, //TARGET_sPDumpIF * psPDumpIF;
                                            IMG_NULL, //TARGET_sDashIF * psDashIF;
                                            IMG_NULL, //TARGET_sPostIF * psPostIF;
                                            IMG_NULL, //IMG_CHAR * pszGetSubDev;
                                            IMG_NULL, //IMG_CHAR * pszConfigFile;
                                 {IMG_NULL,IMG_NULL}, //LST_T lDeviceItem;
                                 {IMG_NULL,IMG_NULL}, //LST_T lMemorySpaceItem;
                                                   0, //IMG_UINT32 ui32LineNo;
                                                   0, //IMG_UINT32 ui32OverrideIf;
                                           IMG_FALSE, //IMG_BOOL bWrapperControl;
                                           IMG_FALSE, //IMG_BOOL bPciCard;
                                           IMG_FALSE, //IMG_BOOL bOverrideWrapper;
                                                   0,
                                            IMG_NULL,
                                                   0,
                                            IMG_NULL,
                                 {IMG_NULL,IMG_NULL}, //LST_T lPdumpCtx
                                        };
    #include "tconf.h"
    #include "tconf_txt.h"
    #include "tal_setup.h"

#endif

#ifndef TARGET_SECURE_TAL
static IMG_BOOL gbConfigLoaded = IMG_FALSE;            //IMG_TRUE when config loaded
static IMG_BOOL gbConfigured = IMG_FALSE;            //IMG_TRUE when target configured
#endif
/*!
******************************************************************************

 @Function                TARGET_LoadConfig

******************************************************************************/
static IMG_RESULT target_LoadConfig(TARGET_sTargetConfig * psTargetConfig)
{
    IMG_UINT32 ui32Result = IMG_SUCCESS;

#ifndef TARGET_SECURE_TAL
    if(IMG_FALSE == gbConfigLoaded)
#endif
    {
#ifdef TARGET_CONF_BY_HEADER_FILE
        IMG_UINT32 ui32Idx = 0;

        //Constructing Device and Memspace Lists from the static config header
        LST_init(&psTargetConfig->lDeviceItem);
        for(ui32Idx = 0; ui32Idx < psTargetConfig->ui32DevNum; ui32Idx++)
        {
            TARGET_sDeviceItem * psDeviceItem = (TARGET_sDeviceItem *)IMG_MALLOC(sizeof(TARGET_sDeviceItem));
            if (psDeviceItem == IMG_NULL)
            {
                return IMG_ERROR_MALLOC_FAILED;
            }
            IMG_MEMCPY(&psDeviceItem->sDevice, &(psTargetConfig->pasDevices[ui32Idx]), sizeof(TARGET_sDevice));
            psDeviceItem->sDevice.pszDeviceName = psTargetConfig->pasDevices[ui32Idx].pszDeviceName;
            LST_add(&psTargetConfig->lDeviceItem, psDeviceItem);
        }
        LST_init(&psTargetConfig->lMemorySpaceItem);
        for(ui32Idx = 0; ui32Idx < psTargetConfig->ui32MemSpceNum; ui32Idx++)
        {
            TARGET_sMemorySpaceItem * psMemorySpaceItem = (TARGET_sMemorySpaceItem *)IMG_MALLOC(sizeof(TARGET_sMemorySpaceItem));
            if (psMemorySpaceItem == IMG_NULL)
            {
                return IMG_ERROR_MALLOC_FAILED;
            }
            IMG_MEMCPY(&psMemorySpaceItem->sMemorySpace, &(psTargetConfig->pasMemSpces[ui32Idx]), sizeof(TARGET_sMemorySpace));
            psMemorySpaceItem->sMemorySpace.pszMemorySpaceName = psTargetConfig->pasMemSpces[ui32Idx].pszMemorySpaceName;
            LST_add(&psTargetConfig->lMemorySpaceItem, psMemorySpaceItem);
        }
        ui32Result = IMG_SUCCESS;
#else
        ui32Result = TCONF_ParseConfigFile(gsTargetConfig.pszConfigFile, &gsTargetConfig);
#endif

#ifndef TARGET_SECURE_TAL
        if(IMG_SUCCESS == ui32Result)
        {
            gbConfigLoaded = IMG_TRUE;
        }
#endif
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_Initialise

 ******************************************************************************/
IMG_RESULT TARGET_Initialise(TARGET_sTargetConfig * psExtTargetConfig)
{
    TARGET_sTargetConfig * psTargetConfig; 
    IMG_UINT32 ui32Result = IMG_SUCCESS;

#ifdef TARGET_CONF_BY_HEADER_FILE
    psTargetConfig = psExtTargetConfig;
#else
    psTargetConfig = &gsTargetConfig;
#endif

#ifdef TARGET_SECURE_TAL
    ui32Result = target_LoadConfig(psTargetConfig);

    if(IMG_SUCCESS == ui32Result)
    {
        TARGET_sDeviceItem      * psDeviceItem;
        TARGET_sMemorySpaceItem * psMemorySpaceItem;

        // Register devices.
        psDeviceItem = LST_first(&psTargetConfig->lDeviceItem);
        while (IMG_NULL != psDeviceItem)
        {
            TAL_DeviceRegister(&psDeviceItem->sDevice);
            psDeviceItem = (TARGET_sDeviceItem*)LST_next(psDeviceItem);
        }

        // Setup TAL Memspaces
        psMemorySpaceItem = LST_first(&psTargetConfig->lMemorySpaceItem);
        while (IMG_NULL != psMemorySpaceItem)
        {
            TAL_MemSpaceRegister(&psMemorySpaceItem->sMemorySpace);
            psMemorySpaceItem = (TARGET_sMemorySpaceItem*)LST_next(psMemorySpaceItem);
        }
    }
#else

    if(IMG_FALSE == gbConfigured)
    {
        if(IMG_FALSE == gbConfigLoaded)
        {
            ui32Result = target_LoadConfig(psTargetConfig);
            if(IMG_SUCCESS == ui32Result)
            {
                gbConfigLoaded = IMG_TRUE;
            }
        }
        if(IMG_TRUE == gbConfigLoaded)
        {
            // Setup TAL Memspaces
            TARGET_sMemorySpaceItem* psMemorySpaceItem = LST_first(&psTargetConfig->lMemorySpaceItem);
            TARGET_sPdumpCtxItem * psPdumpCtx = LST_first(&psTargetConfig->lPdumpCtx);

            while (IMG_NULL != psMemorySpaceItem)
            {
                TALSETUP_MemSpaceRegister(&psMemorySpaceItem->sMemorySpace);
                psMemorySpaceItem = (TARGET_sMemorySpaceItem*)LST_next(psMemorySpaceItem);
            }
            
            while(psPdumpCtx != IMG_NULL)
            {
                //Define the PDUMP context
                TALPDUMP_DefineContext(psPdumpCtx->pszContextName, psPdumpCtx->apszBlockNames);
                psPdumpCtx = LST_next(psPdumpCtx);
            }

            if(IMG_SUCCESS == ui32Result)
            {
                gbConfigured = IMG_TRUE;
            }
        }
    }
#endif

    return ui32Result;
}

IMGVIDEO_EXPORT_SYMBOL(TARGET_Initialise)

/*!
******************************************************************************

 @Function                TARGET_Deinitialise

******************************************************************************/
IMG_RESULT TARGET_Deinitialise(TARGET_sTargetConfig * psExtTargetConfig)
{
    IMG_UINT32 ui32Result = IMG_SUCCESS;
    TARGET_sTargetConfig * psTargetConfig;

#ifdef TARGET_CONF_BY_HEADER_FILE
    psTargetConfig = psExtTargetConfig;
#else
    psTargetConfig = &gsTargetConfig;
#endif

#ifndef TARGET_SECURE_TAL
    if(IMG_TRUE == gbConfigLoaded)
#endif
    {
#ifndef TARGET_CONF_BY_HEADER_FILE
        if (psTargetConfig->pszConfigFile != IMG_NULL)
        {
            IMG_FREE(psTargetConfig->pszConfigFile);
            psTargetConfig->pszConfigFile = IMG_NULL;
        }

        if(IMG_NULL != psTargetConfig->pszGetSubDev)
        {
            IMG_FREE(psTargetConfig->pszGetSubDev);
            psTargetConfig->pszGetSubDev = IMG_NULL;
        }

        //Free TARGET_sWrapperControl
        {
            if (IMG_NULL != psTargetConfig->psWrapperControl)
            {
                IMG_FREE(psTargetConfig->psWrapperControl);
                psTargetConfig->psWrapperControl = IMG_NULL;
            }
        }

        //Free TARGET_sPciInterface
        //Free TARGET_sPciDevice
        //Free TARGET_sPciMemory
        {
            TARGET_sPciInterface * psPciInterface = psTargetConfig->psPciInterface;
            TARGET_sPciDevice * psPciDevice = IMG_NULL;
            TARGET_sPciMemory * psPciMemory = IMG_NULL;
            while (psPciInterface != IMG_NULL)
            {
                //Free PCI card info
                psPciDevice = psPciInterface->psPciDevice;
                if (psPciInterface->psPciCard != IMG_NULL)
                {
                    IMG_FREE(psPciInterface->psPciCard);
                }
                psPciInterface->psPciCard = IMG_NULL;
                psTargetConfig->psPciCard = IMG_NULL;

                //Free PCI device info
                psPciDevice = psPciInterface->psPciDevice;
                while (psPciDevice != IMG_NULL)
                {
                    if(IMG_NULL != psPciDevice->pszDeviceName)
                    {
                        IMG_FREE(psPciDevice->pszDeviceName);
                        psPciDevice->pszDeviceName = IMG_NULL;
                    }
                    psPciDevice = psPciDevice->psNext;
                    IMG_FREE(psPciInterface->psPciDevice);
                    psPciInterface->psPciDevice = psPciDevice;
                }
                psPciInterface->psPciDevice = IMG_NULL;
                psTargetConfig->psPciDevice = IMG_NULL;

                //Free PCI memory info
                psPciMemory = psPciInterface->psPciMemory;
                while (psPciMemory != IMG_NULL)
                {
                    if(IMG_NULL != psPciMemory->pszDeviceName)
                    {
                        IMG_FREE(psPciMemory->pszDeviceName);
                        psPciMemory->pszDeviceName = IMG_NULL;
                    }
                    psPciMemory = psPciMemory->psNext;
                    IMG_FREE(psPciInterface->psPciMemory);
                    psPciInterface->psPciMemory = psPciMemory;
                }
                psPciInterface->psPciMemory = IMG_NULL;
                psTargetConfig->psPciMemory = IMG_NULL;

                if(IMG_NULL != psPciInterface->pszPciInterfaceName)
                {
                    IMG_FREE(psPciInterface->pszPciInterfaceName);
                    psPciInterface->pszPciInterfaceName = IMG_NULL;
                }
                psPciInterface = psPciInterface->psNext;
                IMG_FREE(psTargetConfig->psPciInterface);
                psTargetConfig->psPciInterface = psPciInterface;
            }
            psTargetConfig->psPciInterface = IMG_NULL;
        }

        //Free TARGET_sBurnMem
        {
            TARGET_sBurnMem * psBurnMem = psTargetConfig->psBurnMem;
            while (IMG_NULL != psBurnMem)
            {
                if(IMG_NULL != psBurnMem->pszDeviceName)
                {
                    IMG_FREE(psBurnMem->pszDeviceName);
                    psBurnMem->pszDeviceName = IMG_NULL;
                }
                psBurnMem = psBurnMem->psNext;
                IMG_FREE(psTargetConfig->psBurnMem);
                psTargetConfig->psBurnMem = psBurnMem;
            }
            psTargetConfig->psBurnMem = IMG_NULL;
        }

        //Free TARGET_sDeviceIp
        {
            TARGET_sDeviceIp * psDeviceIp = psTargetConfig->psDeviceIp;
            while (IMG_NULL != psDeviceIp)
            {
                if(IMG_NULL != psDeviceIp->pszDeviceName)
                {
                    IMG_FREE(psDeviceIp->pszDeviceName);
                    psDeviceIp->pszDeviceName = IMG_NULL;
                }
                if(IMG_NULL != psDeviceIp->pszRemoteName)
                {
                    IMG_FREE(psDeviceIp->pszRemoteName);
                    psDeviceIp->pszRemoteName = IMG_NULL;
                }
                psDeviceIp = psDeviceIp->psNext;
                IMG_FREE(psTargetConfig->psDeviceIp);
                psTargetConfig->psDeviceIp = psDeviceIp;
            }
            psTargetConfig->psDeviceIp = IMG_NULL;
        }

        //Free TARGET_sDirectIF
        {
            TARGET_sDirectIF * psDirectIF = psTargetConfig->psDirectIF;
            while (IMG_NULL != psDirectIF)
            {
                if(IMG_NULL != psDirectIF->pszDeviceName)
                {
                    IMG_FREE(psDirectIF->pszDeviceName);
                    psDirectIF->pszDeviceName = IMG_NULL;
                }
                if(IMG_NULL != psDirectIF->psParentDevice)
                {
                    IMG_FREE(psDirectIF->psParentDevice);
                    psDirectIF->psParentDevice = IMG_NULL;
                }
                //if(IMG_NULL != psDirectIF->pDeviceInterface)
                //{
                //    IMG_FREE(psDirectIF->pDeviceInterface);
                //    psDirectIF->pDeviceInterface = IMG_NULL;
                //}
                psDirectIF = psDirectIF->psNext;
                IMG_FREE(psTargetConfig->psDirectIF);
                psTargetConfig->psDirectIF = psDirectIF;
            }
            psTargetConfig->psDirectIF = IMG_NULL;
        }

        //Free TARGET_sName
        {
            TARGET_sName * psName = psTargetConfig->psName;
            while(IMG_NULL != psName)
            {
                if (IMG_NULL != psName->pszMemBaseName)
                {
                    IMG_FREE(psName->pszMemBaseName);
                    psName->pszMemBaseName = IMG_NULL;
                }
                if (IMG_NULL != psName->pszRegBaseName)
                {
                    IMG_FREE(psName->pszRegBaseName);
                    psName->pszRegBaseName = IMG_NULL;
                }
                if (IMG_NULL != psName->pszMemBaseName)
                {
                    IMG_FREE(psName->pszDeviceName);
                    psName->pszDeviceName = IMG_NULL;
                }
                psName = psName->psNext;
                IMG_FREE(psTargetConfig->psName);
                psTargetConfig->psName = psName;
            }
            psTargetConfig->psName = IMG_NULL;
        }

        //Free TARGET_sPDumpIF
        {
            TARGET_sPDumpIF * psPDumpIF = psTargetConfig->psPDumpIF;
            while (IMG_NULL != psPDumpIF)
            {
                if(IMG_NULL != psPDumpIF->pszCommandFile)
                {
                    IMG_FREE(psPDumpIF->pszCommandFile);
                    psPDumpIF->pszCommandFile = IMG_NULL;
                }
                if(IMG_NULL != psPDumpIF->pszInputDirectory)
                {
                    IMG_FREE(psPDumpIF->pszInputDirectory);
                    psPDumpIF->pszInputDirectory = IMG_NULL;
                }
                if(IMG_NULL != psPDumpIF->pszOutputDirectory)
                {
                    IMG_FREE(psPDumpIF->pszOutputDirectory);
                    psPDumpIF->pszOutputDirectory = IMG_NULL;
                }
                if(IMG_NULL != psPDumpIF->pszSendData)
                {
                    IMG_FREE(psPDumpIF->pszSendData);
                    psPDumpIF->pszSendData = IMG_NULL;
                }
                if(IMG_NULL != psPDumpIF->pszReturnData)
                {
                    IMG_FREE(psPDumpIF->pszReturnData);
                    psPDumpIF->pszReturnData = IMG_NULL;
                }
                psPDumpIF = psPDumpIF->psNext;
                IMG_FREE(psTargetConfig->psPDumpIF);
                psTargetConfig->psPDumpIF = psPDumpIF;
            }
            psTargetConfig->psPDumpIF = IMG_NULL;
        }

         //Free TARGET_sDashIF
        {
            TARGET_sDashIF * psDashIF = psTargetConfig->psDashIF;
            while (IMG_NULL != psDashIF)
            {
                if(IMG_NULL != psDashIF->pszDeviceName)
                {
                    IMG_FREE(psDashIF->pszDeviceName);
                    psDashIF->pszDeviceName = IMG_NULL;
                }
                if(IMG_NULL != psDashIF->pszDashName)
                {
                    IMG_FREE(psDashIF->pszDashName);
                    psDashIF->pszDashName = IMG_NULL;
                }
                psDashIF = psDashIF->psNext;
                IMG_FREE(psTargetConfig->psDashIF);
                psTargetConfig->psDashIF = psDashIF;
            }
            psTargetConfig->psDashIF = IMG_NULL;
        }

        //Free TARGET_sPostIF
        {
            TARGET_sPostIF * psPostIF = psTargetConfig->psPostIF;
            while (IMG_NULL != psPostIF)
            {
                if(IMG_NULL != psPostIF->pszDeviceName)
                {
                    IMG_FREE(psPostIF->pszDeviceName);
                    psPostIF->pszDeviceName = IMG_NULL;
                }
                psPostIF = psPostIF->psNext;
                IMG_FREE(psTargetConfig->psPostIF);
                psTargetConfig->psPostIF = psPostIF;
            }
            psTargetConfig->psPostIF = IMG_NULL;
        }

        IMG_ASSERT(IMG_NULL == psTargetConfig->psWrapperControl);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciCard);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciInterface);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psBurnMem);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciDevice);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciMemory);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psDeviceIp);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psDirectIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psName);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPDumpIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psDashIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPostIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig->pszGetSubDev);
        IMG_ASSERT(IMG_NULL == psTargetConfig->pszConfigFile);

        ui32Result = IMG_SUCCESS;
#endif

        //Always freeing the device and memspace lists
#ifndef TARGET_CONF_BY_HEADER_FILE
        {
            TARGET_sPdumpCtxItem * psPdumpCtx = LST_removeHead(&psTargetConfig->lPdumpCtx);
            while(psPdumpCtx != IMG_NULL)
            {
                IMG_UINT32 i = 0;
                while(psPdumpCtx->apszBlockNames[i] != IMG_NULL)
                {
                    IMG_FREE(psPdumpCtx->apszBlockNames[i++]);
                }
                IMG_FREE(psPdumpCtx->apszBlockNames);
                IMG_FREE(psPdumpCtx->pszContextName);
                IMG_FREE(psPdumpCtx);
                psPdumpCtx = LST_removeHead(&psTargetConfig->lPdumpCtx);
            }
        }
#endif
        {
            TARGET_sMemorySpaceItem * psMemorySpaceItem = LST_removeHead(&psTargetConfig->lMemorySpaceItem);
            while (psMemorySpaceItem)
            {
#ifndef TARGET_CONF_BY_HEADER_FILE
                //In the Bridging version, with the static header, the internal members of the structure are statically defined
                //so we only need to free the element from the list, not the memory inside sMemorySpace
                if(IMG_NULL != psMemorySpaceItem->sMemorySpace.pszMemorySpaceName)
                {
                    IMG_FREE(psMemorySpaceItem->sMemorySpace.pszMemorySpaceName);
                    psMemorySpaceItem->sMemorySpace.pszMemorySpaceName = IMG_NULL;
                }
#endif
                //The device is just a pointer, will be freed after clearing the device list

                IMG_FREE(psMemorySpaceItem);
                psMemorySpaceItem = LST_removeHead(&psTargetConfig->lMemorySpaceItem);
            }
            {
                TARGET_sDeviceItem * psDeviceItem = LST_removeHead(&psTargetConfig->lDeviceItem);
#ifndef TARGET_CONF_BY_HEADER_FILE
                TARGET_sSubDevice * psSubDevice = IMG_NULL;
#endif
                while (IMG_NULL != psDeviceItem)
                {
#ifndef TARGET_CONF_BY_HEADER_FILE
                    //In the Bridging version, with the static header, the internal members of the structure are statically defined
                    //so we only need to free the element from the list, not the memory inside sDevice
                    //Free all sub-device blocks
                    psSubDevice = psDeviceItem->sDevice.psSubDevice;
                    while(IMG_NULL != psSubDevice)
                    {
                        if(IMG_NULL != psSubDevice->pszMemName)
                        {
                            IMG_FREE(psSubDevice->pszMemName);
                            psSubDevice->pszMemName = IMG_NULL;
                        }
                        if(IMG_NULL != psSubDevice->pszRegName)
                        {
                            IMG_FREE(psSubDevice->pszRegName);
                            psSubDevice->pszRegName = IMG_NULL;
                        }
                        psSubDevice = psSubDevice->psNext;
                        IMG_FREE(psDeviceItem->sDevice.psSubDevice);
                        psDeviceItem->sDevice.psSubDevice = psSubDevice;
                    }
                    psDeviceItem->sDevice.psSubDevice = IMG_NULL;

                    if(IMG_NULL != psDeviceItem->sDevice.pszDeviceName)
                    {
                        IMG_FREE(psDeviceItem->sDevice.pszDeviceName);
                        psDeviceItem->sDevice.pszDeviceName = IMG_NULL;
                    }
                    if(IMG_NULL != psDeviceItem->sDevice.pszMemArenaName)
                    {
                        IMG_FREE(psDeviceItem->sDevice.pszMemArenaName);
                        psDeviceItem->sDevice.pszMemArenaName = IMG_NULL;
                    }
#endif
                    IMG_FREE(psDeviceItem);
                    psDeviceItem = LST_removeHead(&psTargetConfig->lDeviceItem);
                }
                IMG_ASSERT(LST_empty(&psTargetConfig->lDeviceItem));
            }
            IMG_ASSERT(LST_empty(&psTargetConfig->lMemorySpaceItem));
        }
    }
#ifndef TARGET_SECURE_TAL
    gbConfigured = IMG_FALSE;
    gbConfigLoaded = IMG_FALSE;
#endif
    return ui32Result;
}

IMGVIDEO_EXPORT_SYMBOL(TARGET_Deinitialise)
//The following function are only needed for NO_BRIDGING (for the device interface, setting and parsing the config file)
#ifndef TARGET_CONF_BY_HEADER_FILE

/*!
******************************************************************************

 @Function              TARGET_SetConfigFile

******************************************************************************/
IMG_RESULT TARGET_SetConfigFile(const IMG_CHAR * const pszFilePath)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;

    if(IMG_NULL != pszFilePath)
    {
        if(IMG_NULL != psTargetConfig->pszConfigFile)
        {
            IMG_FREE(psTargetConfig->pszConfigFile);
            psTargetConfig->pszConfigFile = IMG_NULL;
        }

        IMG_ASSERT(IMG_NULL == psTargetConfig->psWrapperControl);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciCard);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciInterface);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psBurnMem);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciDevice);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPciMemory);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psDeviceIp);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psDirectIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psName);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPDumpIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psDashIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig->psPostIF);
        IMG_ASSERT(IMG_NULL == psTargetConfig-> pszGetSubDev);
        IMG_ASSERT(LST_empty(&psTargetConfig->lDeviceItem));
        IMG_ASSERT(LST_empty(&psTargetConfig->lMemorySpaceItem));
        psTargetConfig->pszConfigFile = IMG_STRDUP(pszFilePath);
        if (IMG_NULL == psTargetConfig->pszConfigFile)
        {
            return IMG_ERROR_MALLOC_FAILED;
        }
        ui32Result = IMG_SUCCESS;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                target_FindSocketDevice

******************************************************************************/
static TARGET_sDeviceIp * target_FindSocketDevice(const IMG_CHAR * const pszDeviceName)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sDeviceIp* psDeviceIp = IMG_NULL;
    if (IMG_NULL != psTargetConfig->psDeviceIp && IMG_NULL != pszDeviceName)
    {
        IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
        psDeviceIp = psTargetConfig->psDeviceIp;
        while(IMG_NULL != psDeviceIp)
        {
            if(strlen(psDeviceIp->pszDeviceName) == ui32DeviceNameLen)
            {
                if(0 == IMG_MEMCMP(psDeviceIp->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                {
                    break;
                }
            }
            psDeviceIp = psDeviceIp->psNext;
        }
    }
    return psDeviceIp;
}

/*!
******************************************************************************

 @Function                target_FindDirectIF

******************************************************************************/
static TARGET_sDirectIF * target_FindDirectIF(const IMG_CHAR * const pszDeviceName)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sDirectIF* psDirectIF = IMG_NULL;
    if (IMG_NULL != psTargetConfig->psDirectIF && IMG_NULL != pszDeviceName)
    {
        IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
        psDirectIF = psTargetConfig->psDirectIF;
        while(IMG_NULL != psDirectIF)
        {
            if(IMG_NULL != psDirectIF->pszDeviceName)
            {
                if(strlen(psDirectIF->pszDeviceName) == ui32DeviceNameLen)
                {
                    if(0 == IMG_MEMCMP(psDirectIF->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                    {
                        break;
                    }
                }
            }
            psDirectIF = psDirectIF->psNext;
        }
    }
    return psDirectIF;
}

/*!
******************************************************************************

 @Function                target_FindName

******************************************************************************/
static IS_NOT_USED TARGET_sName * target_FindName(const IMG_CHAR * const pszDeviceName)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sName* psName = IMG_NULL;
    if (IMG_NULL != psTargetConfig->psName && IMG_NULL != pszDeviceName)
    {
        IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
        psName = psTargetConfig->psName;
        while(IMG_NULL != psName)
        {
            if(strlen(psName->pszDeviceName) == ui32DeviceNameLen)
            {
                if(0 == IMG_MEMCMP(psName->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                {
                    break;
                }
            }
            psName = psName->psNext;
        }
    }
    return psName;
}

/*!
******************************************************************************

 @Function                TARGET_GetPciInterface

******************************************************************************/
IMG_RESULT TARGET_GetPciInterface(const TARGET_sPciInterface ** ppsPciInterface)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsPciInterface)
    {
        if (IMG_TRUE == psTargetConfig->bPciCard)
        {
            *ppsPciInterface = psTargetConfig->psPciInterface;
        }
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_SetPciInterface

******************************************************************************/
IMG_RESULT TARGET_SetPciInterface(const TARGET_sPciInterface * const psPciInterface)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;

    if(IMG_NULL != psPciInterface)
    {
        if(IMG_NULL != psPciInterface->psPciCard)
        {
            IMG_ASSERT(IMG_NULL == psTargetConfig->psPciCard);
            psTargetConfig->psPciCard = psPciInterface->psPciCard;
        }
        if(IMG_NULL != psPciInterface->psPciDevice)
        {
            IMG_ASSERT(IMG_NULL == psTargetConfig->psPciDevice);
            psTargetConfig->psPciDevice = psPciInterface->psPciDevice;
        }
        if(IMG_NULL != psPciInterface->psPciMemory)
        {
            IMG_ASSERT(IMG_NULL == psTargetConfig->psPciMemory);
            psTargetConfig->psPciMemory = psPciInterface->psPciMemory;
        }
    }

    return IMG_SUCCESS;

}

/*!
******************************************************************************

 @Function                TARGET_GetPciCard

******************************************************************************/
IMG_RESULT TARGET_GetPciCard(const TARGET_sPciCard ** ppsPciCard)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    if(IMG_NULL != ppsPciCard)
    {
        if (IMG_TRUE == psTargetConfig->bPciCard)
        {
            *ppsPciCard = psTargetConfig->psPciCard;
            ui32Result = IMG_SUCCESS;
        }
    }
    return ui32Result;
}
/*!
******************************************************************************

 @Function                TARGET_GetPciMemory

******************************************************************************/
IMG_RESULT TARGET_GetPciMemory(const IMG_CHAR * const pszDeviceName,
                               const TARGET_sPciMemory ** ppsPciMemory
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    const TARGET_sPciMemory * psPciMemory = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    if(IMG_NULL != ppsPciMemory && IMG_NULL != pszDeviceName)
    {
        if (psTargetConfig->psPciMemory != IMG_NULL)
        {
            const TARGET_sPciMemory * psDefaultPciMemory = IMG_NULL;
            psPciMemory = psTargetConfig->psPciMemory;
            while (psPciMemory != IMG_NULL)
            {
                //If this is the default device base
                if (strcmp(psPciMemory->pszDeviceName, "") == 0)
                {
                    psDefaultPciMemory = psPciMemory;
                }
                else
                {
                    if (strcmp(psPciMemory->pszDeviceName, pszDeviceName) == 0)
                    {
                        ui32Result = IMG_SUCCESS;
                        break;
                    }
                }
                psPciMemory = psPciMemory->psNext;
            }
            if ((psPciMemory != IMG_NULL) || (psDefaultPciMemory != IMG_NULL))
            {
                //If no device spcific then set default
                if (psPciMemory == IMG_NULL)
                {
                    psPciMemory = psDefaultPciMemory;
                }
            }
        }
        *ppsPciMemory = psPciMemory;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetPciDevice

******************************************************************************/
IMG_RESULT TARGET_GetPciDevice(const IMG_CHAR * const pszDeviceName,
                               const TARGET_sPciDevice ** ppsPciDevice
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    const TARGET_sPciDevice * psPciDevice = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsPciDevice && IMG_NULL != pszDeviceName)
    {
        if(IMG_NULL != psTargetConfig->psPciDevice)
        {
            const TARGET_sPciDevice * psDefaultPciDeviceBaseInfo = IMG_NULL;

            psPciDevice = psTargetConfig->psPciDevice;
            while (IMG_NULL != psPciDevice)
            {
                //If this is the default device base
                if (strcmp(psPciDevice->pszDeviceName, "") == 0)
                {
                    psDefaultPciDeviceBaseInfo = psPciDevice;
                }
                else
                {
                    if (strcmp(psPciDevice->pszDeviceName, pszDeviceName) == 0)
                    {
                        ui32Result = IMG_SUCCESS;
                        break;
                    }
                }
                psPciDevice = psPciDevice->psNext;
            }

            //If no device spcific then set default
            if (psPciDevice == IMG_NULL)
            {
                IMG_ASSERT(psDefaultPciDeviceBaseInfo != IMG_NULL);
                psPciDevice = psDefaultPciDeviceBaseInfo;
            }
        }
    }
    *ppsPciDevice = psPciDevice;
    return ui32Result;
}


/*!
******************************************************************************

 @Function                TARGET_GetWrapperControl

******************************************************************************/
IMG_RESULT TARGET_GetWrapperControl(const TARGET_sWrapperControl ** ppsWrapperControl)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sWrapperControl * psWrapperControl = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsWrapperControl)
    {
        if (IMG_TRUE == psTargetConfig->bWrapperControl)
        {
            psWrapperControl = psTargetConfig->psWrapperControl;
            ui32Result = IMG_SUCCESS;
        }
        *ppsWrapperControl = psWrapperControl;
    }
    return ui32Result;
}


/*!
******************************************************************************

 @Function                TARGET_GetBurnMem

******************************************************************************/
IMG_RESULT TARGET_GetBurnMem(const IMG_CHAR * const pszDeviceName,
                             const TARGET_sBurnMem ** ppsBurnMem
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sBurnMem * psBurnMem = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsBurnMem && IMG_NULL != pszDeviceName)
    {
        if (IMG_NULL != psTargetConfig->psBurnMem)
        {
            IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
            psBurnMem = psTargetConfig->psBurnMem;
            while(IMG_NULL != psBurnMem)
            {
                if(strlen(psBurnMem->pszDeviceName) == ui32DeviceNameLen)
                {
                    if(0 == IMG_MEMCMP(psBurnMem->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                    {
                        ui32Result = IMG_SUCCESS;
                        break;
                    }
                }
                psBurnMem = psBurnMem->psNext;
            }
        }
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetDeviceIp

******************************************************************************/
IMG_RESULT TARGET_GetDeviceIp(const IMG_CHAR * const pszDeviceName,
                              const TARGET_sDeviceIp ** ppsDeviceIp
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sDeviceIp * psDeviceIp = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsDeviceIp && IMG_NULL != pszDeviceName)
    {
        if (IMG_NULL != psTargetConfig->psDeviceIp)
        {
            TARGET_sDirectIF * psDirectIF = target_FindDirectIF(pszDeviceName);
            psDeviceIp = target_FindSocketDevice(pszDeviceName);
            if(IMG_NULL != psDeviceIp)
            {
                if (IMG_NULL != psDirectIF &&
                    IMG_NULL != psDirectIF->psParentDevice &&
                    IMG_NULL == psDeviceIp->psParentDevice)
                {
                    // Use the direct parent device if there isn't one defined for this interface
                    psDeviceIp->psParentDevice = target_FindSocketDevice(pszDeviceName);
                }
                *ppsDeviceIp = psDeviceIp;
                ui32Result = IMG_SUCCESS;
            }
        }
        *ppsDeviceIp = psDeviceIp;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetDirectIF

******************************************************************************/
IMG_RESULT TARGET_GetDirectIF(const IMG_CHAR * const pszDeviceName,
                              const TARGET_sDirectIF ** ppsDirectIF
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    TARGET_sDeviceIp * psDeviceIp = target_FindSocketDevice(pszDeviceName);
    TARGET_sDirectIF * psDirectIF = target_FindDirectIF(pszDeviceName);
    if(IMG_NULL != ppsDirectIF && IMG_NULL != pszDeviceName)
    {
        if (IMG_NULL == psDirectIF)
        {
            psDirectIF = (TARGET_sDirectIF *)IMG_MALLOC(sizeof(TARGET_sDirectIF));
            if (IMG_NULL == psDirectIF)
            {
                ui32Result = IMG_ERROR_MALLOC_FAILED;
            }

            psDirectIF->pszDeviceName = IMG_STRDUP(pszDeviceName);
            if (IMG_NULL == psDirectIF->pszDeviceName)
            {
               IMG_FREE(psDirectIF);
               ui32Result = IMG_ERROR_MALLOC_FAILED;
            }
            psDirectIF->psNext = psTargetConfig->psDirectIF;
            psTargetConfig->psDirectIF = psDirectIF;
            *ppsDirectIF = psDirectIF;
            ui32Result = IMG_SUCCESS;
        }

        if (IMG_NULL != psDeviceIp)
        {
            if (IMG_NULL != psDeviceIp->psParentDevice && IMG_NULL == psDirectIF->psParentDevice)
            {
                // Use the socket parent device if there isn't one defined for this interface
                psDirectIF->psParentDevice = target_FindDirectIF(psDeviceIp->psParentDevice->pszDeviceName);
            }
            *ppsDirectIF = psDirectIF;
            ui32Result = IMG_SUCCESS;
        }
        *ppsDirectIF = psDirectIF;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetName


******************************************************************************/
IMG_RESULT TARGET_GetName(const IMG_CHAR * const pszDeviceName,
                          const TARGET_sName ** ppsName
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sName * psName = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsName && IMG_NULL != pszDeviceName)
    {
        if (IMG_NULL != psTargetConfig->psName)
        {
            IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
            psName = psTargetConfig->psName;
            while(IMG_NULL != psName)
            {
                if(IMG_NULL != psName->pszDeviceName)
                {
                    if(strlen(psName->pszDeviceName) == ui32DeviceNameLen)
                    {
                        if(0 == IMG_MEMCMP(psName->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                        {
                            ui32Result = IMG_SUCCESS;
                            break;
                        }
                    }
                }
                psName = psName->psNext;
            }
        }
        *ppsName = psName;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetPDumpIF

******************************************************************************/
IMG_RESULT TARGET_GetPDumpIF(const IMG_CHAR * const pszDeviceName,
                             const TARGET_sPDumpIF ** ppsPDumpIF
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sPDumpIF * psPDumpIF = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsPDumpIF && IMG_NULL != pszDeviceName)
    {
        if (IMG_NULL != psTargetConfig->psPostIF)
        {
            IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
            psPDumpIF = psTargetConfig->psPDumpIF;
            while(IMG_NULL != psPDumpIF)
            {
                if(strlen(psPDumpIF->pszDeviceName) == ui32DeviceNameLen)
                {
                    if(0 == IMG_MEMCMP(psPDumpIF->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                    {
                        ui32Result = IMG_SUCCESS;
                        break;
                    }
                }
                psPDumpIF = psPDumpIF->psNext;
            }
        }
        *ppsPDumpIF = psPDumpIF;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetPostIF

******************************************************************************/
IMG_RESULT TARGET_GetPostIF(const IMG_CHAR * const pszDeviceName,
                            const TARGET_sPostIF ** ppsPostIF
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sPostIF * psPostIF = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsPostIF && IMG_NULL != pszDeviceName)
    {
        if (IMG_NULL != psTargetConfig->psPostIF)
        {
            IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
            psPostIF = psTargetConfig->psPostIF;
            while(IMG_NULL != psPostIF)
            {
                if(strlen(psPostIF->pszDeviceName) == ui32DeviceNameLen)
                {
                    if(0 == IMG_MEMCMP(psPostIF->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                    {
                        ui32Result = IMG_SUCCESS;
                        break;
                    }
                }
                psPostIF = psPostIF->psNext;
            }
        }
        *ppsPostIF = psPostIF;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetDashIF

******************************************************************************/
IMG_RESULT TARGET_GetDashIF(const IMG_CHAR * const pszDeviceName,
                            const TARGET_sDashIF ** ppsDashIF
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    TARGET_sDashIF * psDashIF = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    if(IMG_NULL != ppsDashIF && IMG_NULL != pszDeviceName)
    {
        if (IMG_NULL != psTargetConfig->psDashIF)
        {
            IMG_UINT32 ui32DeviceNameLen = strlen(pszDeviceName);
            psDashIF = psTargetConfig->psDashIF;
            while(IMG_NULL != psDashIF)
            {
                if(strlen(psDashIF->pszDeviceName) == ui32DeviceNameLen)
                {
                    if(0 == IMG_MEMCMP(psDashIF->pszDeviceName, pszDeviceName, ui32DeviceNameLen))
                    {
                        ui32Result = IMG_SUCCESS;
                        break;
                    }
                }
                psDashIF = psDashIF->psNext;
            }
        }
        *ppsDashIF = psDashIF;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_GetFull

******************************************************************************/
IMG_RESULT TARGET_GetFull(const IMG_CHAR * const pszDeviceName,
                          TARGET_sFull * const psFull
)
{
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    IMG_UINT32 ui32IfType;
    const TARGET_sPciMemory * psPciMemory;
    const TARGET_sPciDevice *    psPciDevice;
    const TARGET_sBurnMem * psBurnMem;
    const TARGET_sDeviceIp * psDeviceIp;
    const TARGET_sPDumpIF * psPDumpIF;
    const TARGET_sDashIF * psDashIF;
    const TARGET_sWrapperControl* psWrapperControl;
    IMG_UINT32 ui32Result = IMG_SUCCESS;

    IMG_MEMSET(psFull, 0x00, sizeof(TARGET_sFull));

    if(IMG_NULL != psFull && IMG_NULL != pszDeviceName)
    {
        //Get device  and wrapper control
        TARGET_GetWrapperControl(&psWrapperControl);
        if(psWrapperControl)
        {
            psFull->sWraperControl = *psWrapperControl;
        }

        //Get interface type
        ui32IfType = ((psFull->sWraperControl.ui32Flags  & TARGET_WRAPFLAG_IF_MASK) >> TARGET_WRAPFLAG_IF_SHIFT);

        //Handle depricated type
        if ((ui32IfType == 0) && ((psFull->sWraperControl.ui32Flags & TARGET_WRAPFLAG_BURNMEM) != 0))
        {
            ui32IfType = TARGET_WRAPFLAG_BURNMEM_IF;
        }

        //Save the derived type
        psFull->ui32IfType = ui32IfType;

        //Branch according to type
        switch (ui32IfType)
        {
        case TARGET_WRAPFLAG_PCI_IF:
            if (!psTargetConfig->bPciCard)
            {
                ui32Result = IMG_ERROR_FATAL;
            }
            else
            {
                const TARGET_sPciCard *psPciCard = IMG_NULL;
                TARGET_SetPciInterface(psTargetConfig->psPciInterface);
                TARGET_GetPciCard(&psPciCard);
                if(psPciCard)
                {
                    psFull->sPci.sPciCard = *psPciCard;
                }
                TARGET_GetPciMemory(pszDeviceName, &psPciMemory);
                psFull->sPci.sWrappedPci.sPciMemory = *psPciMemory;
                TARGET_GetPciDevice(pszDeviceName, &psPciDevice);
                psFull->sPci.sWrappedPci.sPciDevice = *psPciDevice;
            }
            break;

        case TARGET_WRAPFLAG_BURNMEM_IF:
            TARGET_GetBurnMem(pszDeviceName, &psBurnMem);
            psFull->sBurnMem = *psBurnMem;
            break;

        case TARGET_WRAPFLAG_SOCKET_IF:
            TARGET_GetDeviceIp(pszDeviceName, &psDeviceIp);
            psFull->sDeviceIp = *psDeviceIp;
            break;

        case TARGET_WRAPFLAG_DASH_IF:
            TARGET_GetDashIF(pszDeviceName, &psDashIF);
            psFull->sDashIF = *psDashIF;
            break;

        case TARGET_WRAPFLAG_PDUMP1_IF:
            TARGET_GetPDumpIF(pszDeviceName, &psPDumpIF);
            psFull->sPDumpIF = *psPDumpIF;
            break;

        case TARGET_WRAPFLAG_NULL_IF:
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
        }
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TARGET_SaveConfig

******************************************************************************/
IMG_RESULT TARGET_SaveConfig(const IMG_CHAR * const pszFilePath)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
#ifndef TARGET_SECURE_TAL
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;
    FILE* pFileSource;
    FILE* pFileTarget;

    IMG_CHAR szNewFile[256];
    IMG_UINT32 ui32DirLen = 0;
    IMG_CHAR * pszConfigFile = IMG_NULL;
    IMG_CHAR * pszFileName  = IMG_NULL;
    IMG_CHAR * pszStr = IMG_NULL;
    IMG_CHAR * pszSubStr = IMG_NULL;
    IMG_CHAR * psFilename = IMG_NULL;

    pszConfigFile = IMG_STRDUP(psTargetConfig->pszConfigFile);

    if(IMG_NULL != pszFilePath)
    {
        pszStr = IMG_STRDUP(pszConfigFile);
        pszSubStr = strtok(pszStr, "\\/");
        while (pszSubStr != IMG_NULL)
        {
            psFilename = pszSubStr;
            pszSubStr = strtok(IMG_NULL, "\\/");
        }
        ui32DirLen = (IMG_UINT32)strlen(pszConfigFile) - (IMG_UINT32)strlen(psFilename);
        IMG_FREE(pszStr);
        //In case original pszConfigFile was a filename without "\\/" delimiters, ui32DirLen is now 0.
        //Avoid writing outside string array in this case (brn28580).
        if(ui32DirLen > 0)
        {
            pszConfigFile[ui32DirLen- 1]= 0;
        }
        pszFileName = pszConfigFile + ui32DirLen;

        sprintf(szNewFile, "%s/%s", pszFilePath, pszFileName);

        //Open source file
        pFileSource = fopen(psTargetConfig->pszConfigFile, "rb");

        //Open destination file
        pFileTarget = fopen(szNewFile, "wb");

        if(IMG_NULL != pFileSource && IMG_NULL != pFileTarget)
        {
            IMG_CHAR ch;
            while ((ch = fgetc(pFileSource)) != EOF)
            {
                fputc(ch, pFileTarget);
            }
        }

        // Close Files
        if(IMG_NULL != pFileSource)
        {
            fclose(pFileSource);
        }
        if(IMG_NULL != pFileTarget)
        {
            fclose(pFileTarget);
        }

        TALPDUMP_AddTargetConfigToTDF(pszFileName);

        ui32Result = IMG_SUCCESS;
    }
#endif
    return ui32Result;
}

/*!
******************************************************************************

@Function TARGET_OverrideWrapper

*****************************************************************************/
IMG_BOOL TARGET_OverrideWrapper(const IMG_CHAR * const pcArgs)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
#ifndef TARGET_SECURE_TAL
    TARGET_sTargetConfig * psTargetConfig = &gsTargetConfig;

    //Ensure Target Config is loaded
    target_LoadConfig(psTargetConfig);
    ui32Result = TCONF_TXT_OverrideWrapper(psTargetConfig, pcArgs);
#endif
    return ui32Result;
}

#endif /* NOT TARGET_CONF_BY_HEADER_FILE */

