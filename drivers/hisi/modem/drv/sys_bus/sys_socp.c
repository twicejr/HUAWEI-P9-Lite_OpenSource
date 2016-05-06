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

#include <product_config.h>
#include "osl_malloc.h"
#include "osl_thread.h"
#include "bsp_socp.h"
#include "sys_socp.h"

extern u32 g_ulThrowout;

bool g_ulpress_start_flag = false;

struct socp_press_case_s g_socp_press = {
        0, 0, SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 0), 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,0,
        NULL, 0xf000,0, NULL, 0xf000, 0,8, 0, 0x20000, 64, NULL, NULL, NULL, 0, 0x1000, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    };


u32 g_ulSocpPressDelay = 500;
u32 g_ulSocpEncSendCnt = 0;
extern s32 socp_get_index(u32 u32Size,u32 *index);
extern s32 socp_soft_free_encdst_chan(u32 u32EncDstChanId);

void socp_press_set_task_delay(u32 para)
{
    g_ulSocpPressDelay = para;
}

void* socp_press_malloc(u32 u32Size)
{
    u8 *pItem= NULL;
    u32 index = 0;

    if(socp_get_index(u32Size,&index))
    {
        return NULL;
    }
    /* ·ÖÅäÄÚ´æ */
    pItem = (u8*)__get_free_pages(GFP_KERNEL,index);
    if(!pItem)
    {
        return NULL;
    }

    return (void*)pItem;
}

void socp_press_setEncDst(struct socp_press_case_s *pCase)
{
    SOCP_CODER_DEST_CHAN_S EncDstAttr;
    u8 *p;

    if(pCase->bDstSet == BSP_TRUE)
    {
        printk("[%s] Enc Dest Set Twice!\n",__FUNCTION__);
        return;
    }

    if(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0))
    {
        printk("[%s] bsp_socp_set_timeout error!~\n",__FUNCTION__);
        return;
    }

    p = (u8*)DDR_SOCP_ADDR;
    pCase->u32OutputSize = DDR_SOCP_SIZE;
    pCase->u32Threshold = ((DDR_SOCP_SIZE>>2)*3)>>10;;

    pCase->u32OutputStart                       = (uintptr_t)p;
    EncDstAttr.sCoderSetDstBuf.pucOutputStart   = p;
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd     = p + pCase->u32OutputSize - 1;
    EncDstAttr.sCoderSetDstBuf.u32Threshold     = pCase->u32Threshold;
    EncDstAttr.u32EncDstThrh                    = pCase->u32EncDstThrh;

    if(BSP_OK != bsp_socp_coder_set_dest_chan_attr(pCase->DstCh, &EncDstAttr))
    {
        printk("set enc dst channel failed!\n");

        return;
    }
    pCase->bDstSet = BSP_TRUE;

    return ;
}

s32 socp_press_encode_task(void *param)
{
    struct socp_press_case_s *pCase = (struct socp_press_case_s*)param;
    int len = pCase->u32DataLen;
    u8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int i = 0;
    SOCP_BD_DATA_STRU stBDData;
    u8* stCoderBuff;
    u32 index;
    s32 ret = 0;

    if(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb))
    {
        printk("%s(%d): bsp_socp_register_event_cb chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        if(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb))
        {
            printk("%s(%d): bsp_socp_register_rd_cb chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
            return -1;
        }
    }
    if(bsp_socp_start(pCase->SrcCh))
    {
        printk("%s(%d): bsp_socp_start chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    if(socp_get_index(len,&index))
    {
        printk("%s(%d): socp_get_index fail \n", __FUNCTION__, __LINE__);
        return -1;
    }
    packet = (u8*)__get_free_pages(GFP_KERNEL,index);
    if(!packet)
    {
        printk("%s(%d): __get_free_pages failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    stBDData.ulDataAddr = (u32)virt_to_phys((void*)packet);
    stBDData.usMsgLen   = len;
    stBDData.enDataType = SOCP_BD_DATA;

    /*buffer*/
    stCoderBuff = kmalloc(pCase->u32InputSize,GFP_KERNEL);
    if(!stCoderBuff)
    {
        free_pages((unsigned long)packet,index);
        printk("%s(%d): malloc faile chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    for(i=0;i<pCase->u32InputSize/sizeof(stBDData);i++)
    {
        memcpy(stCoderBuff+i*sizeof(stBDData),&stBDData,sizeof(stBDData));
    }

    while(g_ulpress_start_flag)
    {
        if(bsp_socp_get_rd_buffer(pCase->SrcCh, &WtBuff))
        {
            ret = 1;
            goto exit;
        }
        if(WtBuff.u32Size + WtBuff.u32RbSize)
        {
            (void)bsp_socp_read_rd_done(pCase->SrcCh, (WtBuff.u32Size + WtBuff.u32RbSize));
        }
        if(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff))
        {
            ret = 2;
            goto exit;
        }
        len = 0;
        if(WtBuff.u32Size + WtBuff.u32RbSize >= 8)
        {
            if(WtBuff.u32Size >= 8)
            {
                memcpy((void *)(phys_to_virt((unsigned long)WtBuff.pBuffer)), stCoderBuff, WtBuff.u32Size);
                len = WtBuff.u32Size;
            }
            if(WtBuff.u32RbSize >= 8)
            {
                memcpy((void *)(phys_to_virt((unsigned long)WtBuff.pBuffer)), stCoderBuff, WtBuff.u32RbSize);
                len += WtBuff.u32RbSize;
            }
            if(len> 8)
            {
                len = len-8;
            }
			if(bsp_socp_write_done(pCase->SrcCh, len))
			{
                ret = 3;
				goto exit;
			}
        }
        else
        {
            msleep(100);
        }

        g_ulSocpEncSendCnt++;
        if(9999 == g_ulSocpEncSendCnt%10000)
        {
            printk("encoder stress send cnt is %d\n",g_ulSocpEncSendCnt);
        }
        if(g_ulSocpEncSendCnt >0xFFFFFFF0)
        {
            g_ulSocpEncSendCnt = 0;
        }
        if(bsp_socp_get_rd_buffer(pCase->SrcCh, &WtBuff))
        {
            ret = 4;
            goto exit;
        }
        if(WtBuff.u32Size + WtBuff.u32RbSize)
        {
            (void)bsp_socp_read_rd_done(pCase->SrcCh, (WtBuff.u32Size + WtBuff.u32RbSize));
        }

        msleep(g_ulSocpPressDelay);
    }
exit:
    kfree(stCoderBuff);
    free_pages((unsigned long)packet,index);
    return ret;
}


void socp_press_setEncSrc(struct socp_press_case_s *pCase)
{
    char task_name[30] = {0};
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    u8 *p;
    u8 *pRd = 0;

    p = (u8*)socp_press_malloc(pCase->u32InputSize);

    if(NULL == p)
    {
        printk("%s[%d] ALLOC ENC SRC FAILED!\n", __FUNCTION__, __LINE__);
        return ;
    }
    pCase->u32InputStart = p;

    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        pRd = (u8*)socp_press_malloc(pCase->u32RDSize);
        if(NULL == pRd)
        {
            printk("%s[%d] ALLOC ENC SRC RD BUF FAILED!\n", __FUNCTION__, __LINE__);
            return ;
        }
        pCase->u32RDStart = pRd;
    }

    pCase->u32InputStart            = p;
    EncSrcAttr.eDataType            = pCase->eDataType;
    EncSrcAttr.eDataTypeEn          = pCase->eDataTypeEn;
    EncSrcAttr.eDebugEn             = pCase->eEncDebugEn;
    EncSrcAttr.eMode                = pCase->eMode;
    EncSrcAttr.ePriority            = pCase->ePriority;
    EncSrcAttr.u32BypassEn          = pCase->u32BypassEn;
    EncSrcAttr.u32DestChanID        = pCase->DstCh;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart    = (u8*)virt_to_phys((void*)p);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd      = (u8*)virt_to_phys((void*)p) + pCase->u32InputSize - 1;
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        EncSrcAttr.sCoderSetSrcBuf.pucRDStart       = (u8*)virt_to_phys((void*)pRd);
        EncSrcAttr.sCoderSetSrcBuf.pucRDEnd         = (u8*)virt_to_phys((void*)pRd) + pCase->u32RDSize - 1;
        EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold   = pCase->u32Threshold;
    }

    if(BSP_OK != bsp_socp_coder_set_src_chan(pCase->SrcCh, &EncSrcAttr))
    {
        printk("alloc enc src channel failed!\n");
        return ;
    }

    snprintf(task_name,30,"socpTest%02d",110);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_press_encode_task, pCase, (OSL_TASK_ID*)&pCase->TaskId))
    {
        return;
    }

    return ;
}

void sys_socp_start(struct master* master)
{
    g_ulThrowout = 0x5a5a5a5a;
    g_ulpress_start_flag = true;

    /*Enc Dst Cfg*/
    socp_press_setEncDst(&g_socp_press);

    /*Enc Src Cfg*/
    socp_press_setEncSrc(&g_socp_press);

}
void sys_socp_stop(struct master* master)
{
    SOCP_BUFFER_RW_STRU WtBuff;
    u32 index;

    if(false == g_ulpress_start_flag)
    {
        printk("[%s] bus stress is stopped or do not start!\n",__FUNCTION__);
        return;
    }

    g_ulpress_start_flag = false;
    g_ulThrowout = 0;

    if(bsp_socp_get_read_buff(g_socp_press.DstCh,&WtBuff))
    {
        printk("[%s] bsp_socp_get_read_buff failed!\n",__FUNCTION__);
        return;
    }

    if((WtBuff.u32RbSize+WtBuff.u32Size) == 0)
    {
        printk("[%s] (WtBuff.u32RbSize+WtBuff.u32Size) ==0 !\n",__FUNCTION__);
        return;
    }

    if(bsp_socp_read_data_done(g_socp_press.DstCh,(WtBuff.u32RbSize+WtBuff.u32Size)))
    {
        printk("[%s] bsp_socp_get_read_buff failed!\n",__FUNCTION__);
        return;
    }

    if(socp_get_index(g_socp_press.u32InputSize,&index))
    {
        printk("[%s] bsp_socp_get_read_buff failed!\n",__FUNCTION__);
        return;
    }
    free_pages((unsigned long)g_socp_press.u32InputStart,index);
    g_socp_press.u32InputStart = NULL;

    if(socp_get_index(g_socp_press.u32RDSize,&index))
    {
        return;
    }
    free_pages((unsigned long)g_socp_press.u32RDStart,index);
    g_socp_press.u32RDStart = NULL;

    g_socp_press.bDstSet = false;
    bsp_socp_stop(g_socp_press.SrcCh);
    bsp_socp_free_channel(g_socp_press.SrcCh);

    socp_soft_free_encdst_chan(g_socp_press.DstCh);
}

void sys_socp_record(struct master* master)
{
}

void sys_socp_report(struct master* master)
{
}

void sys_socp_init(struct master* master)
{
    master->start   = sys_socp_start;
    master->stop    = sys_socp_stop;
    master->record  = sys_socp_record;
    master->report  = sys_socp_report;


    master->init_flag = 1;
}

