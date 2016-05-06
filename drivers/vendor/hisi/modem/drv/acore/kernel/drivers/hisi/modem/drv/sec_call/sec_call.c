/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <linux/module.h>
#include <linux/io.h>
#include <osl_common.h>
#include <drv_comm.h>
#include <bsp_sec_call.h>

#define sec_print_err(fmt, ...)   (printk(KERN_ERR "sec_call: %s "fmt, __FUNCTION__, ##__VA_ARGS__))

#ifdef CONFIG_TZDRIVER
#include <teek_client_api.h>
#include <teek_client_id.h>

DEFINE_MUTEX(trans_lock);
typedef enum SVC_SECBOOT_CMD_ID SECBOOT_CMD_ID;

/******************************************************************************
Function:       TEEK_init
Description:    TEEK初始化
Input:          session
                context
Output:         none
Return:         0: OK  其他: ERROR码
******************************************************************************/
static int TEEK_init(TEEC_Session *session, TEEC_Context *context)
{
    TEEC_Result result;
    TEEC_UUID svc_uuid = TEE_SERVICE_SECBOOT;  
    TEEC_Operation operation = {0};
    u8 package_name[] = "sec_boot";
    u32 root_id = 0;

    result = TEEK_InitializeContext(NULL, context);

    if(result != TEEC_SUCCESS) {
        sec_print_err("TEEK_InitializeContext failed,result = 0x%x!\n",result);
        return BSP_ERROR;
    }

    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT);
    operation.params[2].tmpref.buffer = (void *)(&root_id);
    operation.params[2].tmpref.size = sizeof(root_id);
    operation.params[3].tmpref.buffer = (void *)(package_name);
    operation.params[3].tmpref.size = strlen(package_name) + 1;
    result = TEEK_OpenSession(
                context,
                session,
                &svc_uuid,
                TEEC_LOGIN_IDENTIFY,
                NULL,
                &operation,
                NULL);

    if (result != TEEC_SUCCESS) 
    {
        sec_print_err("TEEK_OpenSession failed,result = 0x%x!\n",result);
        TEEK_FinalizeContext(context);
        return BSP_ERROR;
    }  

    return BSP_OK;
}

/******************************************************************************
Function:        TEEK_cmd_session
Description:     传入命令到安全OS
Input:
        cmd_id      - 传送给安全OS的cmd_id
        func_cmd    - 调用函数命令字
        param       - 函数入参

Output:          none
Return:          0: OK  其他: ERROR码
******************************************************************************/
static int TEEK_cmd_session(TEEC_Session   *session,
                            SECBOOT_CMD_ID cmd_id,
                            FUNC_CMD_ID    func_cmd,
                            const unsigned int param)
{
    TEEC_Result result;
    TEEC_Operation operation;
    unsigned int   origin;

    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(
                           TEEC_VALUE_INPUT,
                           TEEC_NONE,
                           TEEC_NONE,
                           TEEC_NONE);
    operation.params[0].value.a = (unsigned int)func_cmd;
    operation.params[0].value.b = param;

    result = TEEK_InvokeCommand(
                           session,
                           cmd_id,
                           &operation,
                           &origin);
    if (result != TEEC_SUCCESS) {
        sec_print_err("invoke failed!result = 0x%x!\n",result);
        result = BSP_ERROR;
    }

    return BSP_OK;
}

int bsp_sec_call(FUNC_CMD_ID func_cmd, unsigned int param)
{
    TEEC_Session session;
    TEEC_Context context;
    int ret = BSP_ERROR;

    mutex_lock(&trans_lock);
    ret = TEEK_init(&session, &context);
    if(BSP_ERROR == ret)
    {
        sec_print_err("TEEK_InitializeContext failed!\n");
        return ret;
    }

    ret = TEEK_cmd_session(&session, SECBOOT_CMD_ID_BSP_SEC_CALL, (FUNC_CMD_ID)func_cmd, param);
    if(BSP_ERROR == ret)
    {
        sec_print_err("TEEK_cmd_session fail!\n");
    }

    TEEK_CloseSession(&session);
    TEEK_FinalizeContext(&context);

    mutex_unlock(&trans_lock);

    return ret;
}

#else
int bsp_sec_call(FUNC_CMD_ID func_cmd, unsigned int param)
{
    sec_print_err("bsp_sec_call is stub\n");
    return BSP_OK;
}
#endif

