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

#include "bsp_socp.h"
#include "bsp_slice.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef ENABLE_BUILD_SOCP /* do not build socp, stub */
/*****************************************************************************
* 函 数 名  : DRV_SOCP_INIT
*
* 功能描述  : 模块初始化函数
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 初始化成功的标识码
*****************************************************************************/
int DRV_SOCP_INIT()
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_CORDER_SET_SRC_CHAN
 功能描述  : 此接口完成SOCP编码器源通道的分配，根据编码器源通道参数设置通道属性，连接目标通道，返回函数执行结果。
 输入参数  : pSrcAttr:编码器源通道参数结构体指针。
             pSrcChanID:申请到的源通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码源通道分配成功。
             SOCP_ERROR:编码源通道分配失败。
*****************************************************************************/
int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : mdrv_socp_coder_set_dest_chan_attr
 功能描述  : 此接口完成某一编码目标通道的配置，返回函数执行的结果。
 输入参数  : u32DestChanID:SOCP编码器的目标通道ID。
             pDestAttr:SOCP编码器目标通道参数结构体指针。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码目的通道设置成功。
             SOCP_ERROR:编码目的通道设置失败。
*****************************************************************************/
int mdrv_socp_coder_set_dest_chan_attr(unsigned int u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_DECODER_SET_DEST_CHAN
 功能描述  : 此接口完成SOCP解码器目标通道的分配，
             根据解码目标通道参数设置通道属性，
             并连接源通道，返回函数执行结果。
 输入参数  : pAttr:解码器目标通道参数结构体指针
             pDestChanID:申请到的目标通道ID
 输出参数  : 无。
 返 回 值  : SOCP_OK:解码目的通道分配成功。
             SOCP_ERROR:解码目的通道设置失败。
*****************************************************************************/
int DRV_SOCP_DECODER_SET_DEST_CHAN(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_STRU *pAttr)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR
 功能描述  : 此接口完成某一解码源通道的配置，返回函数执行的结果。
 输入参数  : u32SrcChanID:解码器源通道ID
             pInputAttr:解码器源通道参数结构体指针
 输出参数  : 无。
 返 回 值  : SOCP_OK:解码源通道设置成功
             SOCP_ERROR:解码源通道设置失败
*****************************************************************************/
int DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR ( unsigned int u32SrcChanID,SOCP_DECODER_SRC_CHAN_STRU *pInputAttr)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_DECODER_GET_ERR_CNT
 功能描述  :此接口给出解码通道中四种异常情况的计数值。
 输入参数  : u32ChanID:解码器通道ID
                         pErrCnt:解码器异常计数结构体指针
 输出参数  : 无。
 返 回 值      : SOCP_OK:返回异常计数成功
                             SOCP_ERROR:返回异常计数失败
*****************************************************************************/
int DRV_SOCP_DECODER_GET_ERR_CNT (unsigned int u32ChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_FREE_CHANNEL
 功能描述  : 此接口根据通道ID释放分配的编解码通道。
 输入参数  : u32ChanID:通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:通道释放成功。
             SOCP_ERROR:通道释放失败。
*****************************************************************************/
int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID)
{
    return 0;
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
* 功能描述  : 清空编码源通道，同步V9 SOCP接口
*
* 输入参数  : enSrcChanID       编码通道号
*
* 输出参数  : 无
*
* 返 回 值  : BSP_OK
*****************************************************************************/
unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_REGISTER_EVENT_CB
 功能描述  : 此接口为给定通道注册事件回调函数。
 输入参数  : u32ChanID:通道ID。
             EventCB:事件回调函数，参考socp_event_cb函数定义
 输出参数  : 无。
 返 回 值  : SOCP_OK:注册事件回调函数成功。
             SOCP_ERROR:注册事件回调函数失败。
*****************************************************************************/
int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_START
 功能描述  : 此接口用于源通道，启动编码或者解码。
 输入参数  : u32SrcChanID:源通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码或解码启动成功。
             SOCP_ERROR:编码或解码启动失败。
*****************************************************************************/
int mdrv_socp_start(unsigned int u32SrcChanID)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : mdrv_socp_stop
 功能描述  : 此接口用于源通道，停止编码或者解码。
 输入参数  : u32SrcChanID:源通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码或解码停止成功。
             SOCP_ERROR:编码或解码停止失败。
*****************************************************************************/
int mdrv_socp_stop(unsigned int u32SrcChanID)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_TIMEOUT
 功能描述  : 此接口设置超时阈值。
 输入参数  : u32Timeout:超时阈值

 输出参数  : 无。
 返 回 值  : SOCP_OK:设置超时时间阈值成功。
             SOCP_ERROR:设置超时时间阈值失败
*****************************************************************************/
int DRV_SOCP_SET_TIMEOUT (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, unsigned int u32Timeout)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_DEC_PKT_LGTH
 功能描述  : 设置解码包长度极限值
 输入参数  : pPktlgth:解码包长度极值

 输出参数  : 无。
 返 回 值  : SOCP_OK:设置成功。
             其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_DEC_PKT_LGTH(SOCP_DEC_PKTLGTH_STRU *pPktlgth)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_DEBUG
 功能描述  : 设置解码源通道的debug模式
 输入参数  : u32ChanID:通道ID
             u32DebugEn: debug标识
 输出参数  : 无。
 返 回 值  : SOCP_OK:设置成功。
             其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_DEBUG(unsigned int u32DestChanID, unsigned int u32DebugEn)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_GET_WRITE_BUFF
 功能描述  : 此接口用于获取写数据buffer。
 输入参数  : u32SrcChanID:源通道ID
             pBuff:           :写数据buffer

 输出参数  : 无。
 返 回 值  : SOCP_OK:获取写数据buffer成功。
             SOCP_ERROR:获取写数据buffer失败
*****************************************************************************/
int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : mdrv_socp_write_done
 功能描述  : 该接口用于数据的写操作，提供写入数据的长度。
 输入参数  : u32SrcChanID:源通道ID
             u32WrtSize:   已写入数据的长度
 输出参数  : 无。
 返 回 值  : SOCP_OK:写入数据成功。
             SOCP_ERROR:写入数据失败
*****************************************************************************/
int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_REGISTER_RD_CB
 功能描述  : 该接口用于注册从RD缓冲区中读取数据的回调函数。
 输入参数  : u32SrcChanID:源通道ID
             RdCB:  事件回调函数
 输出参数  : 无。
 返 回 值  : SOCP_OK:注册RD环形缓冲区读数据回调函数成功。
             SOCP_ERROR:注册RD环形缓冲区读数据回调函数失败
*****************************************************************************/
int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : mdrv_socp_get_rd_buffer
 功能描述  : 该此接口用于获取RD buffer的数据指针。
 输入参数  : u32SrcChanID:源通道ID
             pBuff:  RD buffer
 输出参数  : 无。
 返 回 值  : SOCP_OK:获取RD环形缓冲区成功
             SOCP_ERROR:获取RD环形缓冲区失败
*****************************************************************************/
int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : bsp_socp_read_rd_done
 功能描述  : 此接口用于上层通知SOCP驱动，从RD buffer中实际读取的数据。
 输入参数  : u32SrcChanID:源通道ID
             u32RDSize:  从RD buffer中实际读取的数据长度
 输出参数  : 无。
 返 回 值  : SOCP_OK:读取RDbuffer中的数据成功
             SOCP_ERROR:读取RDbuffer中的数据失败
*****************************************************************************/
int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : bsp_socp_register_read_cb
 功能描述  : 该接口用于注册读数据的回调函数。
 输入参数  : u32DestChanID:目标通道ID
             ReadCB: 事件回调函数
 输出参数  : 无。
 返 回 值  : SOCP_OK:注册读数据回调函数成功
             SOCP_ERROR:注册读数据回调函数失败
*****************************************************************************/
int DRV_SOCP_REGISTER_READ_CB( unsigned int u32DestChanID, socp_read_cb ReadCB)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_GET_READ_BUFF
 功能描述  : 该此接口用于获取读数据缓冲区指针。
 输入参数  : u32DestChanID:目标通道ID
             ReadCB: 读数据buffer
 输出参数  : 无。
 返 回 值  : SOCP_OK:获取读数据缓冲区成功。
             SOCP_ERROR:获取读数据缓冲区成功。
*****************************************************************************/
int DRV_SOCP_GET_READ_BUFF(unsigned int u32DestChanID,SOCP_BUFFER_RW_STRU *pBuffer)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_READ_DATA_DONE
 功能描述  : 该接口用于上层告诉SOCP驱动，从目标通道中读走的实际数据。
 输入参数  : u32DestChanID:目标通道ID
             u32ReadSize: 已读出数据的长度
 输出参数  : 无。
 返 回 值  : SOCP_OK:读数据成功。
             SOCP_ERROR:读数据失败
*****************************************************************************/
int DRV_SOCP_READ_DATA_DONE(unsigned int u32DestChanID,unsigned int u32ReadSize)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_BBP_ENABLE
 功能描述  : 使能或停止BBP通道。
 输入参数  : bEnable:通道ID
 输出参数  : 无。
 返 回 值      : SOCP_OK:设置成功。
                   其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_BBP_ENABLE(int bEnable)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_BBP_DS_MODE
 功能描述  : 设置BBP DS通道数据溢出处理模式。
 输入参数  : eDsMode:DS通道数据溢出时处理模式设置
 输出参数  : 无。
 返 回 值      : SOCP_OK:设置成功。
                   其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_BBP_DS_MODE(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode)
{
    return 0;
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_GET_STATE
*
* 功能描述  : 获取SOCP状态
*
* 返 回 值  : SOCP_IDLE    空闲
*             SOCP_BUSY    忙碌
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 DRV_SOCP_GET_STATE()
{
    return 0;
}


/*****************************************************************************
* 函 数 名  : DRV_SOCP_VOTE
* 功能描述  : SOCP投票接口，根据投票结果决定SOCP是否睡眠，该接口只在A核提供
* 输入参数  : id --- 投票组件ID，type --- 投票类型
* 输出参数  : 无
* 返 回 值  : int 0 --- 投票成功，0xFFFFFFFF --- 投票失败
*****************************************************************************/
int DRV_SOCP_VOTE(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type)
{
    return 0;
}


/*****************************************************************************
* 函 数 名  : mdrv_socp_get_sd_logcfg
*
* 功能描述  : 查询刷新后LOG2.0 SOCP超时配置信息
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : SOCP_ENC_DST_BUF_LOG_CFG_STRU指针
*****************************************************************************/
unsigned int mdrv_socp_get_sd_logcfg(SOCP_ENC_DST_BUF_LOG_CFG_STRU* cfg)
{
    return 0;
}
/*****************************************************************************
* 函 数 名  : mdrv_socp_set_log_int_timeout
*
* 功能描述  : 使用CMD LINE中的超时时间来设置LOG2.0 SOCP超时配置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_set_log_int_timeout(void)
{
    return;
}
/*****************************************************************************
* 函 数 名  : mdrv_socp_set_log_int_default_timeout
*
* 功能描述  : 使用默认的超时时间来设置LOG2.0 SOCP超时配置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_set_log_int_default_timeout(void)
{
    return;
}

/*****************************************************************************
* 函 数 名  : mdrv_socp_set_autodiv_enalbe
*
* 功能描述  : 使能SOCP的自动降频
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_enalbe_dfs(void)
{
    return;
}

/*****************************************************************************
* 函 数 名  : mdrv_socp_set_autodiv_disalbe
*
* 功能描述  : 去使能SOCP的自动降频
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_disalbe_dfs(void)
{
    return;
}
/*****************************************************************************
* 函 数 名  : mdrv_socp_compress_enable
* 功能描述  :此接口用于使能deflate压缩
* 输入参数  : u32SrcChanID:源通道ID。
* 输出参数  : 无
* 返 回 值  : SOCP_OK:使能deflate压缩成功
     SOCP_ERROR:使能deflate压缩失败
*****************************************************************************/

int mdrv_socp_compress_enable(unsigned int u32DestChanID)
{
    return 0;
}

/*****************************************************************************
* 函 数 名  : mdrv_socp_compress_unable
* 功能描述  :此接口用于停止deflate压缩
* 输入参数  : u32SrcChanID:源通道ID。
* 输出参数  : 无
* 返 回 值  : SOCP_OK:停止deflate压缩成功
     SOCP_ERROR:停止deflate压缩失败
*****************************************************************************/

int mdrv_socp_compress_disable(unsigned int u32DestChanID)
{
    return 0;
}
#else

typedef struct tagSOCP_ADP_DEBUG_INFO_S
{
    unsigned int        u32TimeoutTimes;
    unsigned int        u32TimeoutSlice;
    unsigned int        u32DefaultTimes;
    unsigned int        u32DefaultSlice;
}SOCP_ADP_DEBUG_INFO_S;

SOCP_ADP_DEBUG_INFO_S g_SocpDebugInfo = {0};

void DRV_SOCP_SHOW_DEBUG_INFO(void)
{
    printk(KERN_ERR"u32TimeoutTimes %d, u32TimeoutSlice 0x%x, u32DefaultTimes %d, u32DefaultSlice 0x%x.\n", 
        g_SocpDebugInfo.u32TimeoutTimes, g_SocpDebugInfo.u32TimeoutSlice,
        g_SocpDebugInfo.u32DefaultTimes, g_SocpDebugInfo.u32DefaultSlice);
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_INIT
*
* 功能描述  : 模块初始化函数
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 初始化成功的标识码
*****************************************************************************/
int DRV_SOCP_INIT()
{
    return socp_init();
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_CORDER_SET_SRC_CHAN
 功能描述  : 此接口完成SOCP编码器源通道的分配，根据编码器源通道参数设置通道属性，连接目标通道，返回函数执行结果。
 输入参数  : pSrcAttr:编码器源通道参数结构体指针。
             pSrcChanID:申请到的源通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码源通道分配成功。
             SOCP_ERROR:编码源通道分配失败。
*****************************************************************************/
int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr)
{
    return bsp_socp_coder_set_src_chan(enSrcChanID, pSrcAttr);
}

/*****************************************************************************
 函 数 名  : mdrv_socp_coder_set_dest_chan_attr
 功能描述  : 此接口完成某一编码目标通道的配置，返回函数执行的结果。
 输入参数  : u32DestChanID:SOCP编码器的目标通道ID。
             pDestAttr:SOCP编码器目标通道参数结构体指针。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码目的通道设置成功。
             SOCP_ERROR:编码目的通道设置失败。
*****************************************************************************/
int mdrv_socp_coder_set_dest_chan_attr(unsigned int u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr)
{
    return bsp_socp_coder_set_dest_chan_attr(u32DestChanID, pDestAttr);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_DECODER_SET_DEST_CHAN
 功能描述  : 此接口完成SOCP解码器目标通道的分配，
             根据解码目标通道参数设置通道属性，
             并连接源通道，返回函数执行结果。
 输入参数  : pAttr:解码器目标通道参数结构体指针
             pDestChanID:申请到的目标通道ID
 输出参数  : 无。
 返 回 值  : SOCP_OK:解码目的通道分配成功。
             SOCP_ERROR:解码目的通道设置失败。
*****************************************************************************/
int DRV_SOCP_DECODER_SET_DEST_CHAN(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_STRU *pAttr)
{
    return bsp_socp_decoder_set_dest_chan(enDestChanID, pAttr);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR
 功能描述  : 此接口完成某一解码源通道的配置，返回函数执行的结果。
 输入参数  : u32SrcChanID:解码器源通道ID
             pInputAttr:解码器源通道参数结构体指针
 输出参数  : 无。
 返 回 值  : SOCP_OK:解码源通道设置成功
             SOCP_ERROR:解码源通道设置失败
*****************************************************************************/
int DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR ( unsigned int u32SrcChanID,SOCP_DECODER_SRC_CHAN_STRU *pInputAttr)
{
    return bsp_socp_decoder_set_src_chan_attr(u32SrcChanID, pInputAttr);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_DECODER_GET_ERR_CNT
 功能描述  :此接口给出解码通道中四种异常情况的计数值。
 输入参数  : u32ChanID:解码器通道ID
                         pErrCnt:解码器异常计数结构体指针
 输出参数  : 无。
 返 回 值      : SOCP_OK:返回异常计数成功
                             SOCP_ERROR:返回异常计数失败
*****************************************************************************/
int DRV_SOCP_DECODER_GET_ERR_CNT (unsigned int u32ChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt)
{
    return bsp_socp_decoder_get_err_cnt(u32ChanID, pErrCnt);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_FREE_CHANNEL
 功能描述  : 此接口根据通道ID释放分配的编解码通道。
 输入参数  : u32ChanID:通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:通道释放成功。
             SOCP_ERROR:通道释放失败。
*****************************************************************************/
int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID)
{
    return bsp_socp_free_channel(u32ChanID);
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
* 功能描述  : 清空编码源通道，同步V9 SOCP接口
*
* 输入参数  : enSrcChanID       编码通道号
*
* 输出参数  : 无
*
* 返 回 值  : BSP_OK
*****************************************************************************/
unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID)
{
    return bsp_socp_clean_encsrc_chan(enSrcChanID);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_REGISTER_EVENT_CB
 功能描述  : 此接口为给定通道注册事件回调函数。
 输入参数  : u32ChanID:通道ID。
             EventCB:事件回调函数，参考socp_event_cb函数定义
 输出参数  : 无。
 返 回 值  : SOCP_OK:注册事件回调函数成功。
             SOCP_ERROR:注册事件回调函数失败。
*****************************************************************************/
int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB)
{
    return bsp_socp_register_event_cb(u32ChanID, EventCB);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_START
 功能描述  : 此接口用于源通道，启动编码或者解码。
 输入参数  : u32SrcChanID:源通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码或解码启动成功。
             SOCP_ERROR:编码或解码启动失败。
*****************************************************************************/
int mdrv_socp_start(unsigned int u32SrcChanID)
{
    return bsp_socp_start(u32SrcChanID);
}

/*****************************************************************************
 函 数 名  : mdrv_socp_stop
 功能描述  : 此接口用于源通道，停止编码或者解码。
 输入参数  : u32SrcChanID:源通道ID。
 输出参数  : 无。
 返 回 值  : SOCP_OK:编码或解码停止成功。
             SOCP_ERROR:编码或解码停止失败。
*****************************************************************************/
int mdrv_socp_stop(unsigned int u32SrcChanID)
{
    return bsp_socp_stop(u32SrcChanID);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_TIMEOUT
 功能描述  : 此接口设置超时阈值。
 输入参数  : u32Timeout:超时阈值

 输出参数  : 无。
 返 回 值  : SOCP_OK:设置超时时间阈值成功。
             SOCP_ERROR:设置超时时间阈值失败
*****************************************************************************/
int DRV_SOCP_SET_TIMEOUT (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, unsigned int u32Timeout)
{
    return bsp_socp_set_timeout(eTmOutEn, u32Timeout);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_DEC_PKT_LGTH
 功能描述  : 设置解码包长度极限值
 输入参数  : pPktlgth:解码包长度极值

 输出参数  : 无。
 返 回 值  : SOCP_OK:设置成功。
             其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_DEC_PKT_LGTH(SOCP_DEC_PKTLGTH_STRU *pPktlgth)
{
    return bsp_socp_set_dec_pkt_lgth(pPktlgth);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_DEBUG
 功能描述  : 设置解码源通道的debug模式
 输入参数  : u32ChanID:通道ID
             u32DebugEn: debug标识
 输出参数  : 无。
 返 回 值  : SOCP_OK:设置成功。
             其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_DEBUG(unsigned int u32DestChanID, unsigned int u32DebugEn)
{
    return bsp_socp_set_debug(u32DestChanID, u32DebugEn);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_GET_WRITE_BUFF
 功能描述  : 此接口用于获取写数据buffer。
 输入参数  : u32SrcChanID:源通道ID
             pBuff:           :写数据buffer

 输出参数  : 无。
 返 回 值  : SOCP_OK:获取写数据buffer成功。
             SOCP_ERROR:获取写数据buffer失败
*****************************************************************************/
int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff)
{
    return bsp_socp_get_write_buff(u32SrcChanID, pBuff);
}

/*****************************************************************************
 函 数 名  : mdrv_socp_write_done
 功能描述  : 该接口用于数据的写操作，提供写入数据的长度。
 输入参数  : u32SrcChanID:源通道ID
             u32WrtSize:   已写入数据的长度
 输出参数  : 无。
 返 回 值  : SOCP_OK:写入数据成功。
             SOCP_ERROR:写入数据失败
*****************************************************************************/
int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize)
{
    return bsp_socp_write_done(u32SrcChanID, u32WrtSize);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_REGISTER_RD_CB
 功能描述  : 该接口用于注册从RD缓冲区中读取数据的回调函数。
 输入参数  : u32SrcChanID:源通道ID
             RdCB:  事件回调函数
 输出参数  : 无。
 返 回 值  : SOCP_OK:注册RD环形缓冲区读数据回调函数成功。
             SOCP_ERROR:注册RD环形缓冲区读数据回调函数失败
*****************************************************************************/
int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB)
{
    return bsp_socp_register_rd_cb(u32SrcChanID, RdCB);
}

/*****************************************************************************
 函 数 名  : mdrv_socp_get_rd_buffer
 功能描述  : 该此接口用于获取RD buffer的数据指针。
 输入参数  : u32SrcChanID:源通道ID
             pBuff:  RD buffer
 输出参数  : 无。
 返 回 值  : SOCP_OK:获取RD环形缓冲区成功
             SOCP_ERROR:获取RD环形缓冲区失败
*****************************************************************************/
int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff)
{
    return bsp_socp_get_rd_buffer(u32SrcChanID, pBuff);
}

/*****************************************************************************
 函 数 名  : bsp_socp_read_rd_done
 功能描述  : 此接口用于上层通知SOCP驱动，从RD buffer中实际读取的数据。
 输入参数  : u32SrcChanID:源通道ID
             u32RDSize:  从RD buffer中实际读取的数据长度
 输出参数  : 无。
 返 回 值  : SOCP_OK:读取RDbuffer中的数据成功
             SOCP_ERROR:读取RDbuffer中的数据失败
*****************************************************************************/
int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize)
{
    return bsp_socp_read_rd_done(u32SrcChanID, u32RDSize);
}

/*****************************************************************************
 函 数 名  : bsp_socp_register_read_cb
 功能描述  : 该接口用于注册读数据的回调函数。
 输入参数  : u32DestChanID:目标通道ID
             ReadCB: 事件回调函数
 输出参数  : 无。
 返 回 值  : SOCP_OK:注册读数据回调函数成功
             SOCP_ERROR:注册读数据回调函数失败
*****************************************************************************/
int DRV_SOCP_REGISTER_READ_CB( unsigned int u32DestChanID, socp_read_cb ReadCB)
{
    return bsp_socp_register_read_cb(u32DestChanID, ReadCB);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_GET_READ_BUFF
 功能描述  : 该此接口用于获取读数据缓冲区指针。
 输入参数  : u32DestChanID:目标通道ID
             ReadCB: 读数据buffer
 输出参数  : 无。
 返 回 值  : SOCP_OK:获取读数据缓冲区成功。
             SOCP_ERROR:获取读数据缓冲区成功。
*****************************************************************************/
int DRV_SOCP_GET_READ_BUFF(unsigned int u32DestChanID,SOCP_BUFFER_RW_STRU *pBuffer)
{
    return bsp_socp_get_read_buff(u32DestChanID, pBuffer);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_READ_DATA_DONE
 功能描述  : 该接口用于上层告诉SOCP驱动，从目标通道中读走的实际数据。
 输入参数  : u32DestChanID:目标通道ID
             u32ReadSize: 已读出数据的长度
 输出参数  : 无。
 返 回 值  : SOCP_OK:读数据成功。
             SOCP_ERROR:读数据失败
*****************************************************************************/
int DRV_SOCP_READ_DATA_DONE(unsigned int u32DestChanID,unsigned int u32ReadSize)
{
    return bsp_socp_read_data_done(u32DestChanID, u32ReadSize);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_BBP_ENABLE
 功能描述  : 使能或停止BBP通道。
 输入参数  : bEnable:通道ID
 输出参数  : 无。
 返 回 值      : SOCP_OK:设置成功。
                   其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_BBP_ENABLE(int bEnable)
{
    return bsp_socp_set_bbp_enable(bEnable);
}

/*****************************************************************************
 函 数 名  : DRV_SOCP_SET_BBP_DS_MODE
 功能描述  : 设置BBP DS通道数据溢出处理模式。
 输入参数  : eDsMode:DS通道数据溢出时处理模式设置
 输出参数  : 无。
 返 回 值      : SOCP_OK:设置成功。
                   其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_BBP_DS_MODE(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode)
{
    return bsp_socp_set_bbp_ds_mode(eDsMode);
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_GET_STATE
*
* 功能描述  : 获取SOCP状态
*
* 返 回 值  : SOCP_IDLE    空闲
*             SOCP_BUSY    忙碌
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 DRV_SOCP_GET_STATE()
{
    return bsp_socp_get_state();
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_VOTE
* 功能描述  : SOCP投票接口，根据投票结果决定SOCP是否睡眠，该接口只在A核提供
* 输入参数  : id --- 投票组件ID，type --- 投票类型
* 输出参数  : 无
* 返 回 值  : int 0 --- 投票成功，0xFFFFFFFF --- 投票失败
*****************************************************************************/
int DRV_SOCP_VOTE(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    return bsp_socp_vote(id, type);
#else
    return 0;
#endif
}


/*****************************************************************************
* 函 数 名  : mdrv_socp_get_sd_logcfg
*
* 功能描述  : 查询刷新后LOG2.0 SOCP超时配置信息
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : SOCP_ENC_DST_BUF_LOG_CFG_STRU指针
*****************************************************************************/
unsigned int mdrv_socp_get_sd_logcfg(SOCP_ENC_DST_BUF_LOG_CFG_STRU* cfg)
{
    struct socp_enc_dst_log_cfg* LogCfg;

    if(NULL == cfg)
        return BSP_ERR_SOCP_INVALID_PARA;

    LogCfg = bsp_socp_get_log_cfg();

    if(SOCP_DST_CHAN_DELAY == LogCfg->logOnFlag)
    {
        cfg->logOnFlag = SOCP_DST_CHAN_DELAY;
        cfg->BufferSize= LogCfg->BufferSize;
        cfg->overTime  = LogCfg->overTime;
        cfg->pVirBuffer= LogCfg->pVirBuffer;
        cfg->ulCurTimeout = LogCfg->ulCurTimeout;
        cfg->ulPhyBufferAddr = LogCfg->ulPhyBufferAddr;
    }

    return 0;
}
/*****************************************************************************
* 函 数 名  : mdrv_socp_set_log_int_timeout
*
* 功能描述  : 使用CMD LINE中的超时时间来设置LOG2.0 SOCP超时配置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_set_log_int_timeout(void)
{
    struct socp_enc_dst_log_cfg* LogCfg;
    unsigned int time;

    g_SocpDebugInfo.u32TimeoutTimes++;
    g_SocpDebugInfo.u32TimeoutSlice = bsp_get_slice_value();

    printk(KERN_ERR"mdrv_socp_set_log_int_timeout.\n");

    LogCfg = bsp_socp_get_log_cfg();

    if(SOCP_DST_CHAN_DELAY == LogCfg->logOnFlag)
    {
        /* LogCfg->overTime最大为1200000ms，LogCfg->overTime * 2289结果最大为32位数据，故可以采用如下算法计算 */
        time = (LogCfg->overTime * 2289)/1000;
        (void)bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, time);
        LogCfg->ulCurTimeout = LogCfg->overTime;
        bsp_socp_set_enc_dst_threshold(TRUE,SOCP_CODER_DST_OM_IND);
    }

    return;
}
/*****************************************************************************
* 函 数 名  : mdrv_socp_set_log_int_default_timeout
*
* 功能描述  : 使用默认的超时时间来设置LOG2.0 SOCP超时配置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_set_log_int_default_timeout(void)
{
    struct socp_enc_dst_log_cfg* LogCfg;

    g_SocpDebugInfo.u32DefaultTimes++;
    g_SocpDebugInfo.u32DefaultTimes = bsp_get_slice_value();
    
    LogCfg = bsp_socp_get_log_cfg();

    if(SOCP_DST_CHAN_DELAY == LogCfg->logOnFlag)
    {
        (void)bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, 0x17);
        LogCfg->ulCurTimeout = 10;
        bsp_socp_set_enc_dst_threshold(FALSE,SOCP_CODER_DST_OM_IND);
    }

    return;
}

/*****************************************************************************
* 函 数 名  : mdrv_socp_set_autodiv_enalbe
*
* 功能描述  : 使能SOCP的自动降频
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_enalbe_dfs(void)
{
    return bsp_socp_set_clk_autodiv_enable();
}

/*****************************************************************************
* 函 数 名  : mdrv_socp_set_autodiv_disalbe
*
* 功能描述  : 去使能SOCP的自动降频
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_disalbe_dfs(void)
{
    return bsp_socp_set_clk_autodiv_disable();
}
#ifdef CONFIG_DEFLATE
/*****************************************************************************
* 函 数 名  : mdrv_socp_compress_enable
* 功能描述  :此接口用于使能deflate压缩
* 输入参数  : u32SrcChanID:源通道ID。
* 输出参数  : 无
* 返 回 值  : SOCP_OK:使能deflate压缩成功
     SOCP_ERROR:使能deflate压缩失败
*****************************************************************************/

int mdrv_socp_compress_enable(unsigned int u32DestChanID)
{
    return bsp_socp_compress_enable(u32DestChanID);
}

/*****************************************************************************
* 函 数 名  : mdrv_socp_compress_disable
* 功能描述  :此接口用于停止deflate压缩
* 输入参数  : u32SrcChanID:源通道ID。
* 输出参数  : 无
* 返 回 值  : SOCP_OK:停止deflate压缩成功
     SOCP_ERROR:停止deflate压缩失败
*****************************************************************************/

int mdrv_socp_compress_disable(unsigned int u32DestChanID)
{
    return bsp_socp_compress_disable(u32DestChanID);
}
#else
/*****************************************************************************
* 函 数 名  : mdrv_socp_compress_enable
* 功能描述  :此接口用于使能deflate压缩
* 输入参数  : u32SrcChanID:源通道ID。
* 输出参数  : 无
* 返 回 值  : SOCP_OK:使能deflate压缩成功
     SOCP_ERROR:使能deflate压缩失败
*****************************************************************************/

int mdrv_socp_compress_enable(unsigned int u32DestChanID)
{
    return 0;
}

/*****************************************************************************
* 函 数 名  : mdrv_socp_compress_unable
* 功能描述  :此接口用于停止deflate压缩
* 输入参数  : u32SrcChanID:源通道ID。
* 输出参数  : 无
* 返 回 值  : SOCP_OK:停止deflate压缩成功
     SOCP_ERROR:停止deflate压缩失败
*****************************************************************************/

int mdrv_socp_compress_disable(unsigned int u32DestChanID)
{
    return 0;
}
#endif
#endif /* ENABLE_BUILD_SOCP */

BSP_VOID BSP_SOCP_RefreshSDLogCfg(unsigned int ulTimerLen)
{
	return;
}


#ifdef __cplusplus
}
#endif


