/*!
 *****************************************************************************
 *
 * @File       dman_api_server.c
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

#include "sysbrg_api.h"
#include "sysbrg_api_km.h"
#include "sysos_api_km.h"
#include "dman_api.h"
#include "dman_api_rpc.h"


IMG_VOID DMAN_dispatch(SYSBRG_sPacket *psPacket)
{
	DMAN_sCmdMsg sCommandMsg;
	DMAN_sRespMsg sResponseMsg;

	if(SYSOSKM_CopyFromUser(&sCommandMsg, psPacket->pvCmdData, sizeof(sCommandMsg)))
		IMG_ASSERT(!"failed to copy from user");

	switch (sCommandMsg.eFuncId)
	{
	
      case DMAN_Initialise_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DMAN_Initialise");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DMAN_Initialise");
#endif
#endif
      
	sResponseMsg.sResp.sDMAN_InitialiseResp.xDMAN_InitialiseResp =
      		DMAN_Initialise(
      
      );
      break;
      
    
      case DMAN_Deinitialise_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DMAN_Deinitialise");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DMAN_Deinitialise");
#endif
#endif
      
	sResponseMsg.sResp.sDMAN_DeinitialiseResp.xDMAN_DeinitialiseResp =
      		DMAN_Deinitialise(
      
      );
      break;
      
    
      case DMAN_CloseDevice_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DMAN_CloseDevice");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DMAN_CloseDevice");
#endif
#endif
      
	sResponseMsg.sResp.sDMAN_CloseDeviceResp.xDMAN_CloseDeviceResp =
      		DMAN_CloseDevice(
      
	  sCommandMsg.sCmd.sDMAN_CloseDeviceCmd.ui32ConnId
      );
      break;
      
    
      case DMAN_GetDeviceId_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DMAN_GetDeviceId");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DMAN_GetDeviceId");
#endif
#endif
      
	sResponseMsg.sResp.sDMAN_GetDeviceIdResp.xDMAN_GetDeviceIdResp =
      		DMAN_GetDeviceId(
      
	  sCommandMsg.sCmd.sDMAN_GetDeviceIdCmd.ui32ConnId,
	  sCommandMsg.sCmd.sDMAN_GetDeviceIdCmd.pui32DeviceId
      );
      break;
      
    
      case DMAN_GetKmBuildFlags_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DMAN_GetKmBuildFlags");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DMAN_GetKmBuildFlags");
#endif
#endif
      
	sResponseMsg.sResp.sDMAN_GetKmBuildFlagsResp.xDMAN_GetKmBuildFlagsResp =
      		DMAN_GetKmBuildFlags(
      
	  sCommandMsg.sCmd.sDMAN_GetKmBuildFlagsCmd.pui32KmBuildFlags
      );
      break;
      
    
      case DMAN_OpenDevice1_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DMAN_OpenDevice1");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DMAN_OpenDevice1");
#endif
#endif
      
	sResponseMsg.sResp.sDMAN_OpenDevice1Resp.xDMAN_OpenDevice1Resp =
      		DMAN_OpenDevice1(
      
	  sCommandMsg.sCmd.sDMAN_OpenDevice1Cmd.pszDevName,
	  sCommandMsg.sCmd.sDMAN_OpenDevice1Cmd.ui32DevNameSize,
	  sCommandMsg.sCmd.sDMAN_OpenDevice1Cmd.eOpenMode,
	  sCommandMsg.sCmd.sDMAN_OpenDevice1Cmd.pui32ConnId
      );
      break;
      
    
	}
	if(SYSOSKM_CopyToUser(psPacket->pvRespData, &sResponseMsg, sizeof(sResponseMsg)))
		IMG_ASSERT(!"failed to copy to user");
}
