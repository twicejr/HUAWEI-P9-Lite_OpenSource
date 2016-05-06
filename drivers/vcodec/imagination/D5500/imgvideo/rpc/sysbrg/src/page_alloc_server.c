/*!
 *****************************************************************************
 *
 * @File       page_alloc_server.c
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
#include "page_alloc.h"
#include "page_alloc_rpc.h"


IMG_VOID PALLOC_dispatch(SYSBRG_sPacket *psPacket)
{
	PALLOC_sCmdMsg sCommandMsg;
	PALLOC_sRespMsg sResponseMsg;

	if(SYSOSKM_CopyFromUser(&sCommandMsg, psPacket->pvCmdData, sizeof(sCommandMsg)))
		IMG_ASSERT(!"failed to copy from user");

	switch (sCommandMsg.eFuncId)
	{
	
      case PALLOC_AttachToConnection_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "PALLOC_AttachToConnection");
#else
      printk("bridge %s %s\n", __FUNCTION__, "PALLOC_AttachToConnection");
#endif
#endif
      
	sResponseMsg.sResp.sPALLOC_AttachToConnectionResp.xPALLOC_AttachToConnectionResp =
      		PALLOC_AttachToConnection(
      
	  sCommandMsg.sCmd.sPALLOC_AttachToConnectionCmd.ui32ConnId,
	  sCommandMsg.sCmd.sPALLOC_AttachToConnectionCmd.pui32AttachId
      );
      break;
      
    
      case PALLOC_Alloc1_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "PALLOC_Alloc1");
#else
      printk("bridge %s %s\n", __FUNCTION__, "PALLOC_Alloc1");
#endif
#endif
      
	sResponseMsg.sResp.sPALLOC_Alloc1Resp.xPALLOC_Alloc1Resp =
      		PALLOC_Alloc1(
      
	  sCommandMsg.sCmd.sPALLOC_Alloc1Cmd.ui32AttachId,
	  sCommandMsg.sCmd.sPALLOC_Alloc1Cmd.eMemAttrib,
	  sCommandMsg.sCmd.sPALLOC_Alloc1Cmd.psUmAlloc
      );
      break;
      
    
      case PALLOC_Import1_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "PALLOC_Import1");
#else
      printk("bridge %s %s\n", __FUNCTION__, "PALLOC_Import1");
#endif
#endif
      
	sResponseMsg.sResp.sPALLOC_Import1Resp.xPALLOC_Import1Resp =
      		PALLOC_Import1(
      
	  sCommandMsg.sCmd.sPALLOC_Import1Cmd.ui32AttachId,
	  sCommandMsg.sCmd.sPALLOC_Import1Cmd.bufType,
	  sCommandMsg.sCmd.sPALLOC_Import1Cmd.eMemAttrib,
	  sCommandMsg.sCmd.sPALLOC_Import1Cmd.buff_fd,
	  sCommandMsg.sCmd.sPALLOC_Import1Cmd.psUmAlloc
      );
      break;
      
    
      case PALLOC_Free1_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "PALLOC_Free1");
#else
      printk("bridge %s %s\n", __FUNCTION__, "PALLOC_Free1");
#endif
#endif
      
	sResponseMsg.sResp.sPALLOC_Free1Resp.xPALLOC_Free1Resp =
      		PALLOC_Free1(
      
	  sCommandMsg.sCmd.sPALLOC_Free1Cmd.ui32AllocId
      );
      break;
      
    
	}
	if(SYSOSKM_CopyToUser(psPacket->pvRespData, &sResponseMsg, sizeof(sResponseMsg)))
		IMG_ASSERT(!"failed to copy to user");
}
