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

#include <linux/clk.h>
#include <of.h>
#include <osl_thread.h>
#include "deflate.h"
#include "socp_balong.h"

struct deflate_ctrl_info g_strDeflateCtrl;
struct deflate_debug_info g_strDeflateDebug;
struct deflate_abort_info g_strDeflateAbort;


#define DEFDST_TASK_PRO  81
/*****************************************************************************
* 函 数 名  : deflate_get_data_buffer
*
* 功能描述  : 获取空闲缓冲区的数据
*
* 输入参数  :  pRingBuffer       待查询的环形buffer
                    pRWBuffer         输出的环形buffer
*
* 输出参数  : 无
*
* 返 回 值  :  无
*****************************************************************************/
void deflate_get_data_buffer(DEFLATE_RING_BUF_STRU *pRingBuffer, DEFLATE_BUFFER_RW_STRU *pRWBuffer)
{
    if(pRingBuffer->u32Read <= pRingBuffer->u32Write)
    {
        /* 写指针大于读指针，直接计算 */
        pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Read);
        pRWBuffer->u32Size = (u32)(pRingBuffer->u32Write - pRingBuffer->u32Read);
        pRWBuffer->pRbBuffer = (char *)DEFLATE_NULL;
        pRWBuffer->u32RbSize = 0;
    }
    else
    {
        /* 读指针大于写指针，需要考虑回卷 */
        pRWBuffer->pBuffer = (char *)((unsigned long)pRingBuffer->u32Read);
        pRWBuffer->u32Size = (u32)(pRingBuffer->u32End - pRingBuffer->u32Read + 1);
        pRWBuffer->pRbBuffer = (char *)((unsigned long)pRingBuffer->u32Start);
        pRWBuffer->u32RbSize = (u32)(pRingBuffer->u32Write - pRingBuffer->u32Start);
    }    
}
/*****************************************************************************
* 函 数 名  : deflate_read_done
*
* 功能描述  : 更新缓冲区的读指针
*
* 输入参数  :  pRingBuffer       待更新的环形buffer
                    u32Size          更新的数据长度
*
* 输出参数  : 无
*
* 返 回 值  :  无
*****************************************************************************/
void deflate_read_done(DEFLATE_RING_BUF_STRU *pRingBuffer, u32 u32Size)
{
    pRingBuffer->u32Read += u32Size;
    if(pRingBuffer->u32Read > pRingBuffer->u32End)
    {
        pRingBuffer->u32Read -= pRingBuffer->u32Length;
    }
}
/*****************************************************************************
* 函 数 名  : deflate_debug
*
* 功能描述  :读取寄存器
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void deflate_debug(void)
{  
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_GLOBALCTRL,g_strDeflateAbort.u32DeflateGlobal);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_IBUFTIMEOUTCFG,g_strDeflateAbort.u32IbufTimeoutConfig);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_RAWINT,g_strDeflateAbort.u32RawInt);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_INT,g_strDeflateAbort.u32IntState);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_INTMASK,g_strDeflateAbort.u32IntMask);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_TFRTIMEOUTCFG,g_strDeflateAbort.u32ThfTimeoutConfig);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_STATE,g_strDeflateAbort.u32DeflateState);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_ABORTSTATERECORD,g_strDeflateAbort.u32AbortStateRecord);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEBUG_CH,g_strDeflateAbort.u32DebugChan);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFREMAINTHCFG,g_strDeflateAbort.u32ObufThrh);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFRPTR,g_strDeflateAbort.u32ReadAddr);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFWPTR,g_strDeflateAbort.u32WriteAddr);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFADDR,g_strDeflateAbort.u32StartAddr);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFDEPTH,g_strDeflateAbort.u32BufSize);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFTHRH,g_strDeflateAbort.u32IntThrh);
    DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFOVFTIMEOUT,g_strDeflateAbort.u32OvfTimeoutEn);
    DEFLATE_REG_READ(SOCP_REG_SOCP_MAX_PKG_BYTE_CFG,g_strDeflateAbort.u32PkgConfig);
    DEFLATE_REG_READ(SOCP_REG_DEFLATE_OBUF_DEBUG,g_strDeflateAbort.u32ObufDebug);   
}
/*****************************************************************************
* 函 数 名   : deflate_set
*
* 功能描述  :deflate配置接口，当配置socp目的端时候调用
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 配置成功与否的标识码
*****************************************************************************/
u32 deflate_set(u32 u32DestChanID, DEFLATE_CHAN_CONFIG_S *pDeflateAttr)
{
    u32 start;
    u32 end;
    u32 bufThreshold;
    u32 buflength;
    u32 u32ChanID;
    u32 u32Thrh;
    struct deflate_ctrl_info * pChan;
     
    /* 判断是否已经初始化 */
    DEFLATE_CHECK_INIT();
    g_strDeflateDebug.u32DeflateDstSetCnt++;
    /* 判断参数有效性 */
    DEFLATE_CHECK_PARA(pDeflateAttr);
    u32ChanID   = DEFLATE_REAL_CHAN_ID(u32DestChanID);
    
    start = (uintptr_t)pDeflateAttr->sCoderSetDstBuf.pucOutputStart;
    end   = (uintptr_t)pDeflateAttr->sCoderSetDstBuf.pucOutputEnd;
    bufThreshold = pDeflateAttr->sCoderSetDstBuf.u32Threshold;
    if(bufThreshold<32*1024)
    {
        bufThreshold =0x17000 ;
    }
    u32Thrh = pDeflateAttr->u32EncDstThrh; 
    if(u32Thrh<32*1024)
    {
        u32Thrh=0x8000;
    }
    DEFLATE_CHECK_PARA(start);
    DEFLATE_CHECK_8BYTESALIGN(start);
    DEFLATE_CHECK_PARA(end);
    DEFLATE_CHECK_BUF_ADDR(start, end);
    DEFLATE_CHECK_PARA(bufThreshold);
    buflength = end - start + 1;
    DEFLATE_CHECK_8BYTESALIGN(buflength);
    
    /* 如果经过配置则不能再次配置 */
    pChan = &g_strDeflateCtrl;      
    if (!pChan->u32SetStat)
    {
        /* 写入起始地址到目的buffer起始地址寄存器*/
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFADDR,start);        
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFRPTR,start);
 	    DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFWPTR,start);
        
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFDEPTH,buflength);
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFREMAINTHCFG,u32Thrh);
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFTHRH,bufThreshold);
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL, 22, 4,u32ChanID);
        
        /* 在g_strDeflateStat中保存参数*/
        pChan->u32ChanID                   = u32DestChanID;
        pChan->u32Thrh                     = u32Thrh;
        pChan->sDeflateDstChan.u32Start    = start;
        pChan->sDeflateDstChan.u32End      = end;
        pChan->sDeflateDstChan.u32Write    = start;
        pChan->sDeflateDstChan.u32Read     = start;
        pChan->sDeflateDstChan.u32Length   = buflength; 
        
        /* 表明该通道已经配置 */
        pChan->u32SetStat = DEFLATE_CHN_SET;     
   }
   else
   {
        deflate_printf("Deflate Set finished!\n");      
   } 
    return DEFLATE_OK;
}
/*****************************************************************************
* 函 数 名   : deflate_clear
*
* 功能描述  :deflate清除配置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 成功标识符
*****************************************************************************/
u32 deflate_clear(void)
{
    /*deflate中断标志初始化*/
    g_strDeflateCtrl.u32IntDeflateDstOvf           =0;
    g_strDeflateCtrl.u32IntDeflateDstTfr           =0;
    g_strDeflateCtrl.u32IntDeflateDstThresholdOvf  =0;
    g_strDeflateCtrl.u32IntDeflateWorkAbort        =0;

    /*deflate目的通道属性初始化*/   
    g_strDeflateCtrl.u32SetStat   =0;
    g_strDeflateCtrl.u32Thrh      =0;
    g_strDeflateCtrl.event_cb     =(socp_event_cb)BSP_NULL;
    g_strDeflateCtrl.read_cb      =(socp_read_cb)BSP_NULL;

    return DEFLATE_OK;
}
/*****************************************************************************
* 函 数 名   : deflate_enable
*
* 功能描述  :deflate使能接口,供SOCP非压缩转压缩调用
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 成功标识符
*****************************************************************************/
u32 deflate_enable(u32 u32DstChanId)
{           
    /* 判断是否已经初始化 */
    DEFLATE_CHECK_INIT();
    if(DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
    {
        /*使能deflate*/
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL, 21, 1, 1);
        /* 清中断，开中断 */
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  2, 1,1); 
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK ,  2, 1,0);
        
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  6, 3,0x07);              
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK ,  6, 3,0);           
    }                 
    else
    {
        deflate_printf("Deflate Enable failed!\n");
        return DEFLATE_ERR_SET_INVALID;
    }     
    return DEFLATE_OK;   
}
/*****************************************************************************
* 函 数 名   : deflate_unable
*
* 功能描述  :deflate不使能接口,供SOCP压缩转非压缩场景调用
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 成功与否标识码
*****************************************************************************/
u32 deflate_disable(u32 u32DstChanId)
{    
    u32 DeflateIdleState;
    u32 start;

    /* 判断是否已经初始化 */
    DEFLATE_CHECK_INIT();
    if(DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)  
    {              
        /*立即压缩*/
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL, 20, 1, 1);         
        /*读deflate全局状态寄存器，获取deflate工作状态*/
        DEFLATE_REG_READ(SOCP_REG_DEFLATE_GLOBALCTRL,DeflateIdleState);        
        while(!(DeflateIdleState & DEFLATE_WORK_STATE))
        {
           DEFLATE_REG_READ(SOCP_REG_DEFLATE_GLOBALCTRL,DeflateIdleState);
           msleep(1);
        }  
        /*停止deflate*/
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL, 21, 1, 0);  
        /*丢弃当前数据，更新读写指针*/
        DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFADDR,start);
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFRPTR,start);
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFWPTR,start);
           
        /*清压缩中断状态，屏蔽中断状态*/
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  2, 1, 1);
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK, 2, 1, 1);
        
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  6, 3,0x07);        
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK, 6, 3, 0x07);
    }                               
    else
    {
        deflate_printf("Deflate Unable failed!\n") ;
        return DEFLATE_ERR_SET_INVALID;
    }       
    return DEFLATE_OK;
 }
/*****************************************************************************
* 函 数 名   : deflate_register_read_cb
*
* 功能描述  : deflate 注册读回调接口
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   :成功与否标识码
*****************************************************************************/
 u32 deflate_register_read_cb(u32 u32DstChanId,deflate_read_cb ReadCB)
 {
    /* 判断是否已经初始化 */
    DEFLATE_CHECK_INIT();
    
    /*deflate是否已经配置*/ 
    if(DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
    {
        /* 设置对应通道的回调函数*/
        g_strDeflateCtrl.read_cb = ReadCB;
        g_strDeflateDebug.u32DeflateRegReadCBCnt++;
    }
    else
    {
         deflate_printf("Deflate RegiseEventCB  failed!\n"); 
         return DEFLATE_ERR_SET_INVALID;
    }
    return DEFLATE_OK;

}
/*****************************************************************************
* 函 数 名   : deflate_register_event_cb
*
* 功能描述  :deflate 注册event回调接口
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 成功与否标识码
*****************************************************************************/
 u32 deflate_register_event_cb(u32 u32DstChanId,deflate_event_cb EventCB)
 {
  
    /* 判断是否已经初始化 */
    DEFLATE_CHECK_INIT();
    
   /*deflate是否已经配置*/ 
    if(DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
    {
        /* 设置对应通道的回调函数*/
        g_strDeflateCtrl.event_cb = EventCB;
        g_strDeflateDebug.u32DeflateRegEventCBCnt++;
    }
    else
    {
         deflate_printf("Deflate RegiseEventCB  failed!\n"); 
         return DEFLATE_ERR_SET_INVALID;
    }
    return DEFLATE_OK;
    
 }
/*****************************************************************************
* 函 数 名   : deflate_read_data_done
*
* 功能描述  : deflate read done接口
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 成功与否标识码
*****************************************************************************/
u32 deflate_read_data_done(u32 u32DstChanId,u32 ulDatalen)
{   

    DEFLATE_BUFFER_RW_STRU RwBuff;
    u32  uPAddr;
    unsigned long lock_flag;
    
    /* 判断是否已经初始化 */
    DEFLATE_CHECK_INIT();    
    if(DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
    {          
       g_strDeflateDebug.u32DeflateReaddoneEtrCnt++;          
       if (0 == ulDatalen)
       {
           g_strDeflateDebug.u32DeflateReaddoneZeroCnt++;
       }
       else
       {
            g_strDeflateDebug.u32DeflateReaddoneValidCnt++;
       }
       DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFRPTR, uPAddr);
       g_strDeflateCtrl.sDeflateDstChan.u32Read = uPAddr;
       DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFWPTR, uPAddr);
       g_strDeflateCtrl.sDeflateDstChan.u32Write= uPAddr;
       deflate_get_data_buffer(&g_strDeflateCtrl.sDeflateDstChan, &RwBuff);             
       if(RwBuff.u32Size + RwBuff.u32RbSize < ulDatalen)
       {
            deflate_info("ReadDataDone: deflate dst, too large read size!\n");
            deflate_info("ReadDataDone: deflate dst, write ptr is 0x%x, read ptr is 0x%x\n", g_strDeflateCtrl.sDeflateDstChan.u32Write, g_strDeflateCtrl.sDeflateDstChan.u32Read);
            deflate_info("ReadDataDone: deflate dst, u32Size is 0x%x, u32RbSize is 0x%x\n", RwBuff.u32Size, RwBuff.u32RbSize);
            deflate_info("ReadDataDone: deflate dst, ulDatalen is 0x%x, u32DestChanID is 0x%x\n",ulDatalen , u32DstChanId);

            spin_lock_irqsave(&g_strDeflateCtrl.intSpinLock, lock_flag);
            DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  2, 1,1);
            DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK ,  2, 1,0);
            
            DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  6, 3,0x07);                        
            DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK ,  6, 1,0);           
            spin_unlock_irqrestore(&g_strDeflateCtrl.intSpinLock, lock_flag);
            
            g_strDeflateDebug.u32DeflateReaddoneFailCnt++;
            return DEFLATE_ERR_INVALID_PARA;
       }
        /*更新读指针*/
        deflate_read_done(&g_strDeflateCtrl.sDeflateDstChan,ulDatalen);
        /*写入读指针到读指针寄存器*/
        uPAddr = g_strDeflateCtrl.sDeflateDstChan.u32Read;  
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATEDEST_BUFRPTR, uPAddr); 
        
        spin_lock_irqsave(&g_strDeflateCtrl.intSpinLock, lock_flag);         
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  2, 1,1); 
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK ,  2, 1,0); 
        
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT,  6, 3,0x07);                      
        DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK ,  6, 3,0);            
        spin_unlock_irqrestore(&g_strDeflateCtrl.intSpinLock, lock_flag);
        
        g_strDeflateDebug.u32DeflateReaddoneSucCnt++;
    }
    else
    {
        deflate_printf("Readdatadone failed!\n");
        return DEFLATE_ERR_SET_INVALID;
    }  
     return DEFLATE_OK;
}
/*****************************************************************************
* 函 数 名   : deflate_get_read_buffer
*
* 功能描述  : 获取deflate数据空间
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  :成功与否标识码
*****************************************************************************/
 u32 deflate_get_read_buffer(u32 u32DstChanId,DEFLATE_BUFFER_RW_STRU *pBuff)
 {
 
    u32  uPAddr;

    /* 判断是否已经初始化 */
    DEFLATE_CHECK_INIT();
    /* 判断参数有效性 */
    DEFLATE_CHECK_PARA(pBuff); 
    
    if(DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
    {
        g_strDeflateDebug.u32DeflateGetReadBufEtrCnt++;
        /* 根据读写指针获取buffer */
        DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFRPTR, uPAddr);
        g_strDeflateCtrl.sDeflateDstChan.u32Read = uPAddr;
        
        DEFLATE_REG_READ(SOCP_REG_DEFLATEDEST_BUFWPTR, uPAddr);
        g_strDeflateCtrl.sDeflateDstChan.u32Write= uPAddr;
        
        deflate_get_data_buffer(&g_strDeflateCtrl.sDeflateDstChan, pBuff);             
        g_strDeflateDebug.u32DeflateGetReadBufSucCnt++;        
    }
    else
    {
        deflate_printf("GetReadBuff: deflate set failed!\n");
        return DEFLATE_ERR_SET_INVALID;
    }
    return DEFLATE_OK;
 }


/*****************************************************************************
* 函 数 名   : deflate_int_handler
*
* 功能描述  :deflate中断处理接口
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 无
*****************************************************************************/
 u32 deflate_int_handler(void)
 {
    u32 bHandle = false;
    u32  intState = 0;
    unsigned long lock_flag;
    u32 mask; 
    
    if(DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
    { 
        DEFLATE_REG_READ(SOCP_REG_DEFLATE_INT, intState);
        /*阈值传输中断*/
        if(intState&DEFLATE_TFR_MASK)
        {
             DEFLATE_REG_READ(SOCP_REG_DEFLATE_INTMASK,mask);
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_INTMASK,intState|mask);             
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_RAWINT,intState);
             g_strDeflateCtrl.u32IntDeflateDstTfr |=  intState;
             bHandle = TRUE;
        }
        /*buffer阈值溢出*/
        else if(intState&DEFLATE_THROVF_MASK) 
        {
             DEFLATE_REG_READ(SOCP_REG_DEFLATE_INTMASK,mask);
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_INTMASK,intState|mask);
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_RAWINT,intState);
             g_strDeflateCtrl.u32IntDeflateDstThresholdOvf |=  intState;
             bHandle = TRUE;
        } 
        /*buffer上溢中断*/
        else if(intState&DEFLATE_OVF_MASK) 
        {
             spin_lock_irqsave(&g_strDeflateCtrl.intSpinLock, lock_flag);
             DEFLATE_REG_READ(SOCP_REG_DEFLATE_INTMASK,mask);
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_INTMASK,intState|mask);
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_RAWINT,intState);
             g_strDeflateCtrl.u32IntDeflateDstOvf |=  intState;
             spin_unlock_irqrestore(&g_strDeflateCtrl.intSpinLock, lock_flag);
             bHandle = TRUE;
        }
        /*异常中断*/
        else if(intState&DEFLATE_WORK_ABORT_MASK) 
        {
             DEFLATE_REG_READ(SOCP_REG_DEFLATE_INTMASK,mask);
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_INTMASK,intState|mask);
             DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_RAWINT,intState);
             g_strDeflateCtrl.u32IntDeflateWorkAbort |=  intState;
             bHandle = TRUE;
        } 
        else
        {
             bHandle = FALSE;
        }
   }        
   if(bHandle)
   {
        osl_sem_up(&g_strDeflateCtrl.task_sem);
   }
   return DEFLATE_OK;
 }

/*****************************************************************************
* 函 数 名   : deflate_task
*
* 功能描述  : deflate 任务处理接口
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 无
*****************************************************************************/
 s32 deflate_task(s32 parm)
 {
  
    u32 IntTfrState = 0;
    u32 IntOvfState = 0;
    u32 IntThresholdOvfState = 0;
    u32 IntWorkAortState =0;
    unsigned long lock_flag;

    while(1)
    {
        osl_sem_down(&g_strDeflateCtrl.task_sem);
        spin_lock_irqsave(&g_strDeflateCtrl.intSpinLock, lock_flag);
        
        IntTfrState = g_strDeflateCtrl.u32IntDeflateDstTfr;
        g_strDeflateCtrl.u32IntDeflateDstTfr = 0;        
               
        IntThresholdOvfState = g_strDeflateCtrl.u32IntDeflateDstThresholdOvf;
        g_strDeflateCtrl.u32IntDeflateDstThresholdOvf = 0;

        IntOvfState = g_strDeflateCtrl.u32IntDeflateDstOvf;
        g_strDeflateCtrl.u32IntDeflateDstOvf = 0;
        
        IntWorkAortState = g_strDeflateCtrl.u32IntDeflateWorkAbort;
        g_strDeflateCtrl.u32IntDeflateWorkAbort = 0;
        
        spin_unlock_irqrestore(&g_strDeflateCtrl.intSpinLock, lock_flag);  

        /* 处理传输中断*/
        if (IntTfrState)
        {
            deflate_printf("compress!\n");
             /* 检测通道是否配置*/
            if (DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
            {              
                if (g_strDeflateCtrl.read_cb)
                {
                    g_strDeflateDebug.u32DeflateTskTrfCbOriCnt++;               
                    (void)g_strDeflateCtrl.read_cb(g_strDeflateCtrl.u32ChanID);        
                    g_strDeflateDebug.u32DeflateTskTrfCbCnt++;
                }          
            }
        }
        /* 处理目的 buffer 阈值溢出中断*/
        if (IntThresholdOvfState)
        {
            /* 检测通道是否配置*/
            if (DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
            {
                if (g_strDeflateCtrl.event_cb)
                {
                    g_strDeflateDebug.u32DeflateTskThresholdOvfCbOriCnt++; 
                    (void)g_strDeflateCtrl.event_cb(g_strDeflateCtrl.u32ChanID,DEFLATE_EVENT_THRESHOLD_OVERFLOW,0);
                    g_strDeflateDebug.u32DeflateTskThresholdOvfCbCnt++;
                 }
                if (g_strDeflateCtrl.read_cb)
                {
                   g_strDeflateDebug.u32DeflateTskThresholdOvfCbOriCnt++;
                   (void)g_strDeflateCtrl.read_cb(g_strDeflateCtrl.u32ChanID);
                   g_strDeflateDebug.u32DeflateTskThresholdOvfCbCnt++;                    
                 }               
            }
        } 
        /*处理buffer上溢中断*/
        if (IntOvfState)
        {
            /* 检测通道是否配置*/
            if (DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
            {
                if (g_strDeflateCtrl.event_cb)
                {
                    g_strDeflateDebug.u32DeflateTskOvfCbOriCnt++;                       
                    (void)g_strDeflateCtrl.event_cb(g_strDeflateCtrl.u32ChanID,DEFLATE_EVENT_OVERFLOW,0);
                    g_strDeflateDebug.u32DeflateTskOvfCbCnt++;
                }
                if (g_strDeflateCtrl.read_cb)
                {
                    g_strDeflateDebug.u32DeflateTskOvfCbOriCnt++;                  
                    (void)g_strDeflateCtrl.read_cb(g_strDeflateCtrl.u32ChanID);
                    g_strDeflateDebug.u32DeflateTskTrfCbCnt++;                   
                }               
            }
        }
       /*处理异常中断*/
       if (IntWorkAortState)
       {              
           /* 检测通道是否配置*/
           if (DEFLATE_CHN_SET == g_strDeflateCtrl.u32SetStat)
           {
                if (g_strDeflateCtrl.event_cb)
                {
                     g_strDeflateDebug.u32DeflateTskIntWorkAortCbOriCnt++;                           
                     (void)g_strDeflateCtrl.event_cb(g_strDeflateCtrl.u32ChanID, DEFLATE_EVENT_WORK_ABORT,0);
                     deflate_debug();
                     g_strDeflateDebug.u32DeflateTskIntWorkAortCbCnt++;
                 }
                       
          }
      }
  }
      return DEFLATE_OK;
}
/*****************************************************************************
* 函 数 名   : deflate_init
*
* 功能描述  :deflate 初始化接口
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 无
*****************************************************************************/
s32 deflate_init(void)
{
    s32 ret;
    struct clk  *cSocp=NULL;
    struct device_node* dev = NULL;
    struct socp_enc_dst_log_cfg *cDeflateConfig =NULL ; 
    socp_compress_ops_stru ops;
    
    if(BSP_TRUE == g_strDeflateCtrl.initFlag)
    {
        return DEFLATE_OK;
    }  
    spin_lock_init(&g_strDeflateCtrl.intSpinLock);
    osl_sem_init(0, &g_strDeflateCtrl.task_sem);
    
    /*解析dts,获取deflate基地址，并映射*/
    dev = of_find_compatible_node(NULL,NULL,"hisilicon,deflate_balong_app");
    if(NULL == dev)
    {
        deflate_printf("Socpdeflate dev find failed!\n");
        return DEFLATE_ERROR;
    }
    g_strDeflateCtrl.baseAddr = (void*)of_iomap(dev,0);
    if(NULL == g_strDeflateCtrl.baseAddr)
    {
        deflate_printf("base addr is error!\n");
        return DEFLATE_ERROR; 
    }      
    /*deflate中断标志初始化*/
    g_strDeflateCtrl.u32IntDeflateDstOvf    =0;
    g_strDeflateCtrl.u32IntDeflateDstTfr    =0;
    g_strDeflateCtrl.u32IntDeflateDstThresholdOvf  =0;
    g_strDeflateCtrl.u32IntDeflateWorkAbort  =0 ;

    /*deflate目的通道属性初始化*/   
    g_strDeflateCtrl.u32SetStat   =0;
    g_strDeflateCtrl.u32Thrh      =0;
    g_strDeflateCtrl.event_cb     =(socp_event_cb)BSP_NULL;
    g_strDeflateCtrl.read_cb      =(socp_read_cb)BSP_NULL;
    
    /* 打开defalte时钟 */ 
	cSocp = clk_get(NULL, "deflate_clk");
    if(IS_ERR(cSocp))
    {
        deflate_printf("Socpdeflate clk get failed!\n");       
    }
    else
    {
        clk_prepare(cSocp);
    	if(BSP_OK !=clk_enable(cSocp))
    	{
    		deflate_printf("Socpdeflate clk open failed!\n");
    		return DEFLATE_ERROR;
    	}    
    }
    /*创建deflate任务 */
    ret = osl_task_init("deflateProc",DEFDST_TASK_PRO, 4096, (OSL_TASK_FUNC) deflate_task,NULL, &g_strDeflateCtrl.taskid);
    if (BSP_OK != ret)
    {
        deflate_printf("create task failed!\n");
        return DEFLATE_ERROR;
    }
    /*deflate软复位*/
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL, 1, 1, 1);
    
    /*如果配置延时上报，需要配置超时寄存器*/
    cDeflateConfig=bsp_socp_get_log_cfg();
    if(true == cDeflateConfig->logOnFlag)
    {
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_TFRTIMEOUTCFG, (cDeflateConfig->overTime*2289/1000));
    }
    else
    {
        DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_TFRTIMEOUTCFG, DEFLATE_TRANS_TIMEOUT_DEFAULT);
    }
    /*设置buffer溢出不丢数*/
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATEDEST_BUFOVFTIMEOUT, 31, 1, 0);
    /*使能255包压缩场景*/
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL, 10, 8, 0x5);
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL, 18, 1, 0);
    /*bypass 模式*/
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_GLOBALCTRL,  0, 1, 0);
    /*ibuf超时配置*/
    DEFLATE_REG_WRITE(SOCP_REG_DEFLATE_IBUFTIMEOUTCFG,0xFFFFFFFF);
    /* 清中断，屏蔽中断 */
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT, 1, 2, 0x03);
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK, 1, 2,0x03 );  
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT, 4, 1, 1);
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK, 4, 1, 1);
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_RAWINT, 6, 3, 0x07);
    DEFLATE_REG_SETBITS(SOCP_REG_DEFLATE_INTMASK, 6, 3, 0x07);

    ops.isr                 = deflate_int_handler;
    ops.register_Eventcb    = deflate_register_event_cb;
    ops.register_Readcb     = deflate_register_read_cb;
    ops.enable              = deflate_enable;
    ops.disable             = deflate_disable;
    ops.set                 = deflate_set;
    ops.getbuffer           = deflate_get_read_buffer;
    ops.readdone            = deflate_read_data_done;
    ops.clear               = deflate_clear;
    bsp_socp_register_compress(&ops);
    
    /* 设置初始化状态 */
    g_strDeflateCtrl.initFlag = BSP_TRUE;
    deflate_printf("Deflate init succeed, base addr=0x%p!\n", (void*)(g_strDeflateCtrl.baseAddr));
    return DEFLATE_OK;
}


/*****************************************************************************
* 函 数 名   : deflate_help
*
* 功能描述  :deflate 打印信息
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值   : 无
*****************************************************************************/
 void deflate_help(void)
 {
   deflate_printf("\r deflate_show_debug_gbl       : 查看全局统计信息:通道申请、配置和中断总计数\n"); 
   deflate_printf("\r deflate_show_dest_chan_cur   : 查看压缩目的通道信息\n"); 
 }
void deflate_show_debug_gbl(void)
{   
    deflate_printf("\r DEFLATE 全局状态维护信息:\n");
    deflate_printf("\r deflate基地址:                                            : 0x%x\n",
           (s32)g_strDeflateCtrl.baseAddr);
    deflate_printf("\r deflate配置编码目的通道的次数                             : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateDstSetCnt);
    deflate_printf("\r deflate配置编码目的通道成功的次数                         : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateDstSetSucCnt); 
    deflate_printf("\r deflate注册deflate目的通道读数据回调函数次数              : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateRegReadCBCnt); 
    deflate_printf("\r deflate注册deflate目的通道异常事件回调函数次数            : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateRegEventCBCnt);
    deflate_printf("\r deflate尝试获取deflate目的buffer次数                      : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateGetReadBufEtrCnt);
    deflate_printf("\r deflate获取deflate目的buffer成功次数                      : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateGetReadBufSucCnt);
    deflate_printf("\r deflate尝试读取deflate目的数据次数                        : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateReaddoneEtrCnt);
    deflate_printf("\r deflate尝试读取deflate目的数据长度等于0次数               : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateReaddoneZeroCnt);
    deflate_printf("\r deflate读取deflate目的数据长度不等于0次数                 : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateReaddoneValidCnt);
    deflate_printf("\r deflate读取deflate目的数据失败的次数                      : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateReaddoneFailCnt);
    deflate_printf("\r deflate读取deflate目的数据成功的次数                      : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateReaddoneSucCnt);
    deflate_printf("\r deflate处理传输中断任务的次数                             : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskTrfCbOriCnt);
    deflate_printf("\r deflate处理完传输中断任务的次数                           : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskTrfCbCnt);
    deflate_printf("\r deflate处理上溢中断的次数                                 : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskOvfCbOriCnt);
    deflate_printf("\r deflate处理完上溢中断的次数*                              : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskOvfCbCnt);
    deflate_printf("\r deflate处理阈值溢出的次数                                 : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskThresholdOvfCbOriCnt);
    deflate_printf("\r deflate处理完阈值溢出的次数                               : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskThresholdOvfCbCnt);
    deflate_printf("\r deflate处理异常的次数                                     : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskIntWorkAortCbOriCnt);
    deflate_printf("\r deflate处理完异常的次数                                   : 0x%x\n",
           (s32)g_strDeflateDebug.u32DeflateTskIntWorkAortCbCnt);                        
}   
u32 deflate_show_dest_chan_cur(void)
{  
    deflate_printf("通道ID                                                    :0x%x\n", 
           g_strDeflateCtrl.u32ChanID);
    deflate_printf(" 通道配置状态                                             :%d\n", 
           g_strDeflateCtrl.u32SetStat);
    deflate_printf("通道buffer 起始地址                                       :0x%x\n", 
           g_strDeflateCtrl.sDeflateDstChan.u32Start);
    deflate_printf("通道buffer 结束地址                                       :0x%x\n", 
           g_strDeflateCtrl.sDeflateDstChan.u32End);
    deflate_printf("通道buffer 读指针                                         :0x%x\n", 
           g_strDeflateCtrl.sDeflateDstChan.u32Read);
    deflate_printf("通道buffer 写指针                                         :0x%x\n",
           g_strDeflateCtrl.sDeflateDstChan.u32Write);
    deflate_printf("通道buffer 长度                                           :0x%x\n", 
           g_strDeflateCtrl.sDeflateDstChan.u32Length);
    return BSP_OK;
}

module_init(deflate_init);

