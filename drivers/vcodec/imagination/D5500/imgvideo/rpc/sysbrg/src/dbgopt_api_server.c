/*!
 *****************************************************************************
 *
 * @File       dbgopt_api_server.c
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
#include "dbgopt_api.h"
#include "dbgopt_api_rpc.h"


IMG_VOID DBGOPTBRG_dispatch(SYSBRG_sPacket *psPacket)
{
	DBGOPTBRG_sCmdMsg sCommandMsg;
	DBGOPTBRG_sRespMsg sResponseMsg;

	if(SYSOSKM_CopyFromUser(&sCommandMsg, psPacket->pvCmdData, sizeof(sCommandMsg)))
		IMG_ASSERT(!"failed to copy from user");

	switch (sCommandMsg.eFuncId)
	{
	
      case DBGOPTBRG_Initialise_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_Initialise");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_Initialise");
#endif
#endif
      
	sResponseMsg.sResp.sDBGOPTBRG_InitialiseResp.xDBGOPTBRG_InitialiseResp =
      		DBGOPTBRG_Initialise(
      
      );
      break;
      
    
      case DBGOPTBRG_Deinitialise_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_Deinitialise");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_Deinitialise");
#endif
#endif
      		DBGOPTBRG_Deinitialise(
      
      );
      break;
      
    
      case DBGOPTBRG_Set_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_Set");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_Set");
#endif
#endif
      
	sResponseMsg.sResp.sDBGOPTBRG_SetResp.xDBGOPTBRG_SetResp =
      		DBGOPTBRG_Set(
      
	  sCommandMsg.sCmd.sDBGOPTBRG_SetCmd.sStrName,
	  sCommandMsg.sCmd.sDBGOPTBRG_SetCmd.eType,
	  sCommandMsg.sCmd.sDBGOPTBRG_SetCmd.sVal
      );
      break;
      
    
      case DBGOPTBRG_Get_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_Get");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_Get");
#endif
#endif
      
	sResponseMsg.sResp.sDBGOPTBRG_GetResp.xDBGOPTBRG_GetResp =
      		DBGOPTBRG_Get(
      
	  sCommandMsg.sCmd.sDBGOPTBRG_GetCmd.sStrName,
	  sCommandMsg.sCmd.sDBGOPTBRG_GetCmd.peType,
	  sCommandMsg.sCmd.sDBGOPTBRG_GetCmd.psVal
      );
      break;
      
    
      case DBGOPTBRG_Clear_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_Clear");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_Clear");
#endif
#endif
      		DBGOPTBRG_Clear(
      
	  sCommandMsg.sCmd.sDBGOPTBRG_ClearCmd.sStrName
      );
      break;
      
    
      case DBGOPTBRG_SetWithKey_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_SetWithKey");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_SetWithKey");
#endif
#endif
      
	sResponseMsg.sResp.sDBGOPTBRG_SetWithKeyResp.xDBGOPTBRG_SetWithKeyResp =
      		DBGOPTBRG_SetWithKey(
      
	  sCommandMsg.sCmd.sDBGOPTBRG_SetWithKeyCmd.i32Key,
	  sCommandMsg.sCmd.sDBGOPTBRG_SetWithKeyCmd.sStrName,
	  sCommandMsg.sCmd.sDBGOPTBRG_SetWithKeyCmd.eType,
	  sCommandMsg.sCmd.sDBGOPTBRG_SetWithKeyCmd.sVal
      );
      break;
      
    
      case DBGOPTBRG_GetWithKey_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_GetWithKey");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_GetWithKey");
#endif
#endif
      
	sResponseMsg.sResp.sDBGOPTBRG_GetWithKeyResp.xDBGOPTBRG_GetWithKeyResp =
      		DBGOPTBRG_GetWithKey(
      
	  sCommandMsg.sCmd.sDBGOPTBRG_GetWithKeyCmd.i32Key,
	  sCommandMsg.sCmd.sDBGOPTBRG_GetWithKeyCmd.sStrName,
	  sCommandMsg.sCmd.sDBGOPTBRG_GetWithKeyCmd.peType,
	  sCommandMsg.sCmd.sDBGOPTBRG_GetWithKeyCmd.psVal
      );
      break;
      
    
      case DBGOPTBRG_ClearWithKey_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_ClearWithKey");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_ClearWithKey");
#endif
#endif
      		DBGOPTBRG_ClearWithKey(
      
	  sCommandMsg.sCmd.sDBGOPTBRG_ClearWithKeyCmd.i32Key,
	  sCommandMsg.sCmd.sDBGOPTBRG_ClearWithKeyCmd.sStrName
      );
      break;
      
    
      case DBGOPTBRG_ClearAll_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "DBGOPTBRG_ClearAll");
#else
      printk("bridge %s %s\n", __FUNCTION__, "DBGOPTBRG_ClearAll");
#endif
#endif
      		DBGOPTBRG_ClearAll(
      
      );
      break;
      
    
	}
	if(SYSOSKM_CopyToUser(psPacket->pvRespData, &sResponseMsg, sizeof(sResponseMsg)))
		IMG_ASSERT(!"failed to copy to user");
}
