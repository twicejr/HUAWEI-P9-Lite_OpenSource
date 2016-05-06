/*!
 *****************************************************************************
 *
 * @File       dbgopt_api_rpc.h
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

#ifndef __DBGOPTBRG_RPC_H__
#define __DBGOPTBRG_RPC_H__

#include "img_defs.h"
#include "sysbrg_api.h"
#include "dbgopt_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	DBGOPTBRG_Initialise_ID,
	DBGOPTBRG_Deinitialise_ID,
	DBGOPTBRG_Set_ID,
	DBGOPTBRG_Get_ID,
	DBGOPTBRG_Clear_ID,
	DBGOPTBRG_SetWithKey_ID,
	DBGOPTBRG_GetWithKey_ID,
	DBGOPTBRG_ClearWithKey_ID,
	DBGOPTBRG_ClearAll_ID,

} DBGOPTBRG_eFuncId;

typedef struct
{
	DBGOPTBRG_eFuncId	eFuncId;
    union
	{
	
		struct
		{
			 DBGOPT_sStrWithLen sStrName;
                          		 DBGOPT_eType eType;
                          		 DBGOPT_sValueBrg sVal;
                          
		} sDBGOPTBRG_SetCmd;
	
		struct
		{
			 DBGOPT_sStrWithLen sStrName;
                          		 sysbrg_user_pointer peType;
                          		 sysbrg_user_pointer psVal;
                          
		} sDBGOPTBRG_GetCmd;
	
		struct
		{
			 DBGOPT_sStrWithLen sStrName;
                          
		} sDBGOPTBRG_ClearCmd;
	
		struct
		{
			 DBGOPT_i32Key i32Key;
                          		 DBGOPT_sStrWithLen sStrName;
                          		 DBGOPT_eType eType;
                          		 DBGOPT_sValueBrg sVal;
                          
		} sDBGOPTBRG_SetWithKeyCmd;
	
		struct
		{
			 DBGOPT_i32Key i32Key;
                          		 DBGOPT_sStrWithLen sStrName;
                          		 sysbrg_user_pointer peType;
                          		 sysbrg_user_pointer psVal;
                          
		} sDBGOPTBRG_GetWithKeyCmd;
	
		struct
		{
			 DBGOPT_i32Key i32Key;
                          		 DBGOPT_sStrWithLen sStrName;
                          
		} sDBGOPTBRG_ClearWithKeyCmd;
	
	} sCmd;
} DBGOPTBRG_sCmdMsg;

typedef struct
{
    union
	{
	
		struct
		{
			IMG_RESULT		xDBGOPTBRG_InitialiseResp;
		} sDBGOPTBRG_InitialiseResp;
            
		struct
		{
			IMG_RESULT		xDBGOPTBRG_SetResp;
		} sDBGOPTBRG_SetResp;
            
		struct
		{
			SYSBRG_UINT64		xDBGOPTBRG_GetResp;
		} sDBGOPTBRG_GetResp;
            
		struct
		{
			IMG_RESULT		xDBGOPTBRG_SetWithKeyResp;
		} sDBGOPTBRG_SetWithKeyResp;
            
		struct
		{
			SYSBRG_UINT64		xDBGOPTBRG_GetWithKeyResp;
		} sDBGOPTBRG_GetWithKeyResp;
            
	} sResp;
} DBGOPTBRG_sRespMsg;



extern IMG_VOID DBGOPTBRG_dispatch(SYSBRG_sPacket __user *psPacket);

#ifdef __cplusplus
}
#endif

#endif
