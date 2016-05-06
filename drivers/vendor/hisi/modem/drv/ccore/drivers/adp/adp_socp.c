/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_socp.c
*
*   作    者 :  z00212940
*
*   描    述 :  SOCP模块用户头文件
*
*   修改记录 :  2013年02月04日  v1.00  z00212940  创建
*
*************************************************************************/

#include "bsp_socp.h"

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
int socp_init(void)
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
* 函 数 名  : DRV_SOCP_GET_STATE
*
* 功能描述  : 获取SOCP状态
*
* 返 回 值  : SOCP_IDLE    空闲
*             SOCP_BUSY    忙碌
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 DRV_SOCP_GET_STATE(void)
{
    return 0;
}

unsigned int  DRV_SOCP_INIT_LTE_DSP(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return 0;
}

unsigned int  DRV_SOCP_INIT_LTE_BBP_LOG(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return 0;
}

unsigned int  DRV_SOCP_INIT_LTE_BBP_DS(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return 0;
}

void DRV_SOCP_ENABLE_LTE_BBP_DSP(unsigned int ulChanId)
{
    return;
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_VOTE_TO_MCORE
* 功能描述  : SOCP投票接口，该接口只在C核提供，适配LDSP首次加载的SOCP上电需求
* 输入参数  : type --- 投票类型
* 输出参数  : 无
* 返 回 值  : int 0 --- 投票成功，0xFFFFFFFF --- 投票失败
*****************************************************************************/
int DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type)
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

#else
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
* 函 数 名  : DRV_SOCP_GET_STATE
*
* 功能描述  : 获取SOCP状态
*
* 返 回 值  : SOCP_IDLE    空闲
*             SOCP_BUSY    忙碌
*****************************************************************************/
SOCP_STATE_ENUM_UINT32 DRV_SOCP_GET_STATE(void)
{
    return bsp_socp_get_state();
}

extern unsigned int bsp_socp_init_lte_dsp(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
unsigned int DRV_SOCP_INIT_LTE_DSP(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return bsp_socp_init_lte_dsp(ulChanId,ulPhyAddr,ulSize);
}

extern unsigned int bsp_socp_init_lte_bbp_log(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
unsigned int DRV_SOCP_INIT_LTE_BBP_LOG(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return bsp_socp_init_lte_bbp_log(ulChanId,ulPhyAddr,ulSize);
}

extern unsigned int bsp_socp_int_lte_bbp_ds(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
unsigned int DRV_SOCP_INIT_LTE_BBP_DS(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize)
{
    return bsp_socp_int_lte_bbp_ds(ulChanId,ulPhyAddr,ulSize);
}

extern void bsp_socp_enable_lte_dsp_bbp(u32 ulChanId);
void DRV_SOCP_ENABLE_LTE_BBP_DSP(unsigned int ulChanId)
{
    bsp_socp_enable_lte_dsp_bbp(ulChanId);
}

/*****************************************************************************
* 函 数 名  : DRV_SOCP_VOTE_TO_MCORE
* 功能描述  : SOCP投票接口，该接口只在C核提供，适配LDSP首次加载的SOCP上电需求
* 输入参数  : type --- 投票类型
* 输出参数  : 无
* 返 回 值  : int 0 --- 投票成功，0xFFFFFFFF --- 投票失败
*****************************************************************************/
int DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    return bsp_socp_vote_to_mcore(type);
#else
    return 0;
#endif
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


#endif /* ENABLE_BUILD_SOCP */

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


#ifdef __cplusplus
}
#endif

