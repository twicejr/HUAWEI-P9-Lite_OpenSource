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

#ifdef __cplusplus
extern "C" {
#endif


#if defined(__KERNEL__)
/*lint -save -e537*/
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
/*lint -restore +e537*/
#endif
#include "osl_types.h"
#include "bsp_rfile.h"
#include "bsp_icc.h"
#include "bsp_hardtimer.h"
#include "socp_balong.h"
#include "osl_sem.h"
#include "osl_thread.h"

#define SOCP_ROOT_PATH          "/modem_log/socp/"


extern SOCP_DEBUG_INFO_S g_stSocpDebugInfo;


struct socp_debug_icc_stru
{
    char OpsCmd[32];
};


typedef void (*socp_debug_ops)(void);

struct socp_debug_proc{
    char OpsCmd[32];
    socp_debug_ops OpsFunc;
};

struct socp_debug_ctrl_stru{
    osl_sem_id      task_sem;
    OSL_TASK_ID     task_id;
};
struct socp_debug_ctrl_stru g_stSocpDebugCtrl;


void socp_debug_help(void)
{
#if defined(__KERNEL__)
    socp_printf("请执行 echo <command> > /proc/socpProc \n");
#endif
    socp_printf("<command>           :说明(接口)\n");
    socp_printf("****************************************\n");
    socp_printf("help                :帮助(socp_debug_help)\n");
    socp_printf("ap_count_clean      :计数清零(socp_debug_ApCountclean)\n");
    socp_printf("ap_count_store      :计数保存(socp_debug_ApCountStore)\n");
    socp_printf("cp_count_store      :cp 计数保存(socp_debug_CpCountStore)\n");
    socp_printf("cp_count_clean      :cp 计数清零(socp_debug_CpCountClean)\n");
    socp_printf("count_print         :打印计数(socp_debug_PrintCount)\n");
    socp_printf("reg_store           :保存寄存器(socp_debug_RegStore)\n");
    socp_printf("all_store           :保存所有寄存器及计数(socp_debug_AllStore)\n");
    socp_printf("all_clean           :清除所有计数(socp_debug_AllClean)\n");
}

void socp_debug_sendCmd(char* cmd)
{
    struct socp_debug_icc_stru icc_req;
    int ret;
    u32 channel_id = ICC_CHN_ACORE_CCORE_MIN <<16 | IFC_RECV_FUNC_SOCP_DEBUG;
    u32 cpu_id;

#if defined(__KERNEL__)
    cpu_id = (u32)ICC_CPU_MODEM;
#else
    cpu_id = (u32)ICC_CPU_APP;
#endif

    Socp_Memset(icc_req.OpsCmd,0,sizeof(icc_req.OpsCmd));
    Socp_Memcpy(icc_req.OpsCmd, cmd, strlen(cmd));/*lint !e666*/
    socp_printf("enter here %s  %d\n",__FUNCTION__,__LINE__);
    ret = bsp_icc_send(cpu_id,channel_id, (u8*)&icc_req,sizeof(icc_req));
    if(ret != (int)sizeof(icc_req))
    {
        socp_printf("bsp_icc_send failed! ret 0x%x\n",ret);
    }
    return;
}
void socp_debug_ApCountclean(void)
{
#ifdef __KERNEL__
    Socp_Memset(&g_stSocpDebugInfo,0x00,sizeof(g_stSocpDebugInfo));
#else
    socp_debug_sendCmd("ap_count_clean");
#endif
}

void socp_debug_CountStore(char* p,int len)
{
    /* [false alarm]:alarm */
    char path[128];
    /* [false alarm]:alarm */
    int fd = -1;
    /* [false alarm]:alarm */
    int ret;


    Socp_Memset(path,0,sizeof(path));

#if defined(__OS_RTOSCK__)
    (void)sprintf_s(path,128,"%s%s%d.bin",SOCP_ROOT_PATH,p,bsp_get_slice_value());
#else
    snprintf(path,128,"%s%s%d.bin",SOCP_ROOT_PATH,p,bsp_get_slice_value());
#endif
    /* [false alarm]:alarm */
    fd = bsp_open((s8*)path, RFILE_RDWR|RFILE_CREAT, 0660);
    /* [false alarm]:alarm */
    if(fd<0){
        socp_printf("create %s error,save failed!\n",path);
        return;
    }
    /* [false alarm]:alarm */
    ret = bsp_write((u32)fd,(s8*)&g_stSocpDebugInfo,sizeof(g_stSocpDebugInfo));
    /* [false alarm]:alarm */
    if(ret != (int)sizeof(g_stSocpDebugInfo)){
        socp_printf("write %s error,save failed!\n",path);
        (void)bsp_close((u32)fd);
        return;
    }
    (void)bsp_close((u32)fd);
    return;
}
void socp_debug_ApCountStore(void)
{
#ifdef __KERNEL__
    char p[] = "ApCount_";
    socp_debug_CountStore(p,strlen(p));
#else
    socp_debug_sendCmd("ap_count_store");
#endif
}
void socp_debug_RegStore(void)
{
    /* [false alarm]:alarm */
    char path[128];
    /* [false alarm]:alarm */
    char p[] = "Reg_";
    /* [false alarm]:alarm */
    int fd = -1;
    /* [false alarm]:alarm */
    int ret;


    Socp_Memset(path,0,sizeof(path));

#if defined(__OS_RTOSCK__)
    (void)sprintf_s(path,128,"%s%s%d.bin",SOCP_ROOT_PATH,p,bsp_get_slice_value());
#else
    snprintf(path,128,"%s%s%d.bin",SOCP_ROOT_PATH,p,bsp_get_slice_value());
#endif
    /* [false alarm]:alarm */
    fd = bsp_open((s8*)path, RFILE_RDWR|RFILE_CREAT, 0660);
    /* [false alarm]:alarm */
    if(fd<0){
        socp_printf("create %s error,save failed!\n",path);
        return;
    }
    /* [false alarm]:alarm */
    ret = bsp_write((u32)fd,(s8*)g_strSocpStat.baseAddr,4096);
    /* [false alarm]:alarm */
    if(ret != (int)4096){
        socp_printf("write %s error | 0x%x,save failed!\n",path,ret);
        (void)bsp_close((u32)fd);
        return;
    }
    (void)bsp_close((u32)fd);
    return;
}
void socp_debug_CpCountStore(void)
{
#ifndef __KERNEL__
    char p[] = "CpCount_";
    socp_debug_CountStore(p,(int)strlen(p));
#else
    socp_debug_sendCmd("cp_count_store");
#endif
}
void socp_debug_CpCountClean(void)
{
#ifndef __KERNEL__
    Socp_Memset(&g_stSocpDebugInfo,0x00,sizeof(g_stSocpDebugInfo));
#else
    socp_debug_sendCmd("cp_count_clean");
#endif
}
void socp_debug_PrintCount(void)
{
    socp_help();
}

void socp_debug_AllStore(void)
{
    socp_debug_ApCountStore();
    socp_debug_CpCountStore();
    socp_debug_RegStore();
}

void socp_debug_AllClean(void)
{
    socp_debug_ApCountclean();
    socp_debug_CpCountClean();
}

struct socp_debug_proc g_strSocpOps[] = {
    {"help"                 ,socp_debug_help},
    {"ap_count_clean"       ,socp_debug_ApCountclean},
    {"ap_count_store"       ,socp_debug_ApCountStore},
    {"reg_store"            ,socp_debug_RegStore},
    {"cp_count_store"       ,socp_debug_CpCountStore},
    {"cp_count_clean"       ,socp_debug_CpCountClean},
    {"count_print"          ,socp_debug_PrintCount},
    {"all_store"            ,socp_debug_AllStore},
    {"all_clean"            ,socp_debug_AllClean},
};

int socp_debug_icc_msg_callback(u32 chanid ,u32 len,void* pdata)
{
    u32 channel_id = ICC_CHN_ACORE_CCORE_MIN <<16 | IFC_RECV_FUNC_SOCP_DEBUG;
    if(channel_id != chanid)
        return 0;

    socp_printf("enter here %s  %d\n",__FUNCTION__,__LINE__);

    osl_sem_up(&g_stSocpDebugCtrl.task_sem);
    return 0;
}
int socp_debug_icc_task(void* para)
{
    int ret;
    u32 i;
    u32 chanid = ICC_CHN_ACORE_CCORE_MIN <<16 | IFC_RECV_FUNC_SOCP_DEBUG;
    u8  p[32];
    while(1)
    {
        osl_sem_down(&g_stSocpDebugCtrl.task_sem);

        ret = bsp_icc_read(chanid,p, sizeof(p));
        if(ret< (int)0 || ret > (int)sizeof(p))
        {
            socp_printf("enter here %s  %d\n",__FUNCTION__,__LINE__);
            continue;
        }
        socp_printf("%s :%s\n",__FUNCTION__,p);
        for(i = 0;i<sizeof(g_strSocpOps)/sizeof(g_strSocpOps[0]);i++)
        {
            if(!strncmp(g_strSocpOps[i].OpsCmd,(char*)p,strlen(g_strSocpOps[i].OpsCmd))){
                g_strSocpOps[i].OpsFunc();
            }
        }
    }
}

#if defined(__KERNEL__)
/*lint -save -e26*/
static ssize_t socp_read(struct file *file,char __user *buf, size_t len, loff_t *ppos)
{
    socp_debug_help();
    return len;
}
/*lint -restore +e26*/
static ssize_t socp_write(struct file *file,const char __user *buf, size_t len, loff_t *ppos)
{
    int i;
    char* p = NULL;
    if(len == 0){
        socp_debug_help();
        return len;
    }

    if(len >= 32)
    {
        socp_debug_help();
        return len;
    }
    
    p = kmalloc((len+1),GFP_KERNEL);
    if(NULL == p){
        socp_printf("kmalloc failed ,len = 0x%x\n",len);
        return 1;
    }
    if(copy_from_user(p,buf,len)){
        kfree(p);
        return 2;
    }

    for(i = 0;i<sizeof(g_strSocpOps)/sizeof(g_strSocpOps[0]);i++)
    {
        if(!strncmp(g_strSocpOps[i].OpsCmd,p,strlen(g_strSocpOps[i].OpsCmd))){
            g_strSocpOps[i].OpsFunc();
            kfree(p);
            return len;
        }
    }
    socp_printf("Input Error Command,Please input again!\n");
    socp_debug_help();
    kfree(p);

    return len;
}
static const struct file_operations g_strSocpProc ={
    .owner    = THIS_MODULE,
    .read     = socp_read,
    .write    = socp_write,
};
#endif

/*lint -save -e745*/
int socp_debug_init(void)
{
    u32 channel_id = ICC_CHN_ACORE_CCORE_MIN <<16 | IFC_RECV_FUNC_SOCP_DEBUG;

    osl_sem_init(0, &g_stSocpDebugCtrl.task_sem);
#if defined(__KERNEL__)
    if(NULL == proc_create("socpProc", 0660, NULL, &g_strSocpProc))
    {
        return -1;
    }
#endif
    (void)osl_task_init("socpProc",30, 1024, (OSL_TASK_FUNC)socp_debug_icc_task,NULL, &g_stSocpDebugCtrl.task_id);

    (void)bsp_icc_event_register(channel_id, (read_cb_func)socp_debug_icc_msg_callback,NULL,NULL,NULL);

    return 0;
}

#if defined(__KERNEL__)
module_init(socp_debug_init);
#endif



#ifdef __cplusplus
}
#endif


