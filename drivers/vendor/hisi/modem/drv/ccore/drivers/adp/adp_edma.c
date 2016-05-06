


#include "bsp_edma.h"
#include "drv_comm.h"


s32 EDMA_NormTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle)
{
	u32 channel_id  = pstDMAHandle->ulChIdx;
    u32 src_addr = pstDMAHandle->u32SrcAddr;
    u32 des_addr = pstDMAHandle->u32DstAddr;
    u32 len = pstDMAHandle->ulLength;

    if(1!=bsp_edma_channel_is_idle(channel_id))
    {
        //logMsg("channel %d is_idle failed in EDMA_NormTaskLaunch",channel_id ,0,0,0,0,0);
    	return EDMA_FAIL;
    }

    if(0!=bsp_edma_channel_set_config(channel_id,EDMA_M2M,EDMA_TRANS_WIDTH_64,EDMA_BUR_LEN_16))
    {
        //logMsg("channel_set_config failed in EDMA_NormTaskLaunch",0 ,0,0,0,0,0);
        return EDMA_FAIL;
    }
    if(0!=bsp_edma_channel_async_start( channel_id, src_addr, des_addr, len))
    {
        //logMsg("channel_start failed in EDMA_NormTaskLaunch",0 ,0,0,0,0,0);
        return EDMA_FAIL;
    }
    return EDMA_SUCCESS;
}

s32 EDMA_2VecTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle)
{
	u32 channel_id  = pstDMAHandle->ulChIdx;
    u32 src_addr = pstDMAHandle->u32SrcAddr;
    u32 des_addr = pstDMAHandle->u32DstAddr;
    u32 len = pstDMAHandle->ulLength;

    if(1!=bsp_edma_channel_is_idle(channel_id))
    {
        //logMsg("channel %d is_idle failed in EDMA_2VecTaskLaunch",channel_id ,0,0,0,0,0);
    	return EDMA_FAIL;
    }
    if(0!=bsp_edma_channel_set_config(channel_id,M2M_CONFIG,EDMA_TRANS_WIDTH_64,EDMA_BUR_LEN_16))
    {
        //logMsg("channel_set_config failed in EDMA_2VecTaskLaunch",0 ,0,0,0,0,0);
        return EDMA_FAIL;
    }
    if(0!=bsp_edma_channel_2vec_start( channel_id,  src_addr,  des_addr,  len,  SZ_8K))
    {
        //logMsg("channel_start failed in EDMA_2VecTaskLaunch",0 ,0,0,0,0,0);
        return EDMA_FAIL;
    }
    return EDMA_SUCCESS;
}

s32 EDMA_QueryCHNLState(u32 u32ChIdx)
{
	u32 ulChan = u32ChIdx;/* 通道号*/
    if(1==bsp_edma_channel_is_idle(ulChan))
    {
    	return EDMA_SUCCESS;
    }
    else
    {
    	return EDMA_FAIL;
    }
}

s32 EDMA_QueryCHNsLState(u32 u32ChIdxMap)
{
    if( 1==bsp_edma_chanmap_is_idle(u32ChIdxMap) )
    {
    	return EDMA_SUCCESS;
    }
    else
    {
    	return EDMA_FAIL;
    }
}
/* end ---- adapt for v7r1 */



/* start---- adapt for v9r1 */
/*******************************************************************************
  函数名:      BSP_S32 balong_dma_init(void)
  功能描述:    DMA初始化程序，挂接中断
  输入参数:    无
  输出参数:    无
  返回值:      0
*******************************************************************************/
BSP_S32 balong_dma_init(void)
{
    return (BSP_S32)bsp_edma_init();
}

unsigned int mdrv_edma_set_config(BALONG_DMA_REQ_E req, unsigned int direction, unsigned int burst_width, unsigned int burst_len)
{
    unsigned int phy_req;

    phy_req = bsp_edma_get_physical_req(req);
    return BALONG_DMA_SET_CONFIG(phy_req, direction, burst_width, burst_len);
}



/*******************************************************************************
  函数名:       int balong_dma_current_transfer_address(UINT32 channel_id)
  函数描述:     获得某通道当前传输的内存地址
  输入参数:     channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
  输出参数:     无
  返回值:       成功：通道当前传输的内存地址
                失败：负数
*******************************************************************************/
int mdrv_edma_get_curr_trans_addr(unsigned int channel_id)
{
    return bsp_edma_current_transfer_address( channel_id);
}

/*******************************************************************************
  函数名:       int balong_dma_channel_stop(UINT32 channel_id)
  函数描述:     停止指定的DMA通道
  输入参数:     channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
  输出参数:     无
  返回值:       成功：通道当前传输的内存地址
                失败：负数
*******************************************************************************/
int mdrv_edma_chan_stop(unsigned int  channel_id)
{
    return bsp_edma_channel_stop( channel_id);
}


/*******************************************************************************
  函数名:      BALONG_DMA_CB *balong_dma_channel_get_lli_addr(UINT32 channel_id)
  函数描述:    获取指定DMA通道的链表控制块的起始地址
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
BALONG_DMA_CB_S * mdrv_edma_chan_get_lli_addr (unsigned int channel_id)

{
    return (BALONG_DMA_CB_S *)bsp_edma_channel_get_lli_addr((u32) channel_id);
}


/******************************************************************************
  函数名:      int balong_dma_channel_init (BALONG_DMA_REQ req,
                  channel_isr pFunc, UINT32 channel_arg, UINT32 int_flag)
  函数描述:    根据外设号分配通道，注册通道中断回调函数、初始化传输完成信号量、
               将外设号写入config寄存器
  输入参数:    req : 外设请求号
               pFunc : 上层模块注册的DMA通道中断处理函数，NULL时表明不注册
               channel_arg : pFunc的入参1，
                             pFunc为NULL，不需要设置这个参数
               int_flag : pFunc的入参2, 产生的中断类型，取值范围为
                        BALONG_DMA_INT_DONE、BALONG_DMA_INT_LLT_DONE、
                      ALONG_DMA_INT_CONFIG_ERR、BALONG_DMA_INT_TRANSFER_ERR、
                        BALONG_DMA_INT_READ_ERR之一，或者组合。
                        pFunc为NULL，不需要设置这个参数
  输出参数:    无
  返回值:      成功：通道号
               失败：负数
*******************************************************************************/
int mdrv_edma_chan_init (BALONG_DMA_REQ_E req, channel_isr pFunc, unsigned int channel_arg, unsigned int int_flag)

{
    return bsp_edma_channel_init(req, pFunc, (u32) channel_arg, (u32) int_flag);
}

/*******************************************************************************
  函数名:      int balong_dma_channel_set_config (UINT32 channel_id,
                       UINT32 direction, UINT32 burst_width, UINT32 burst_len)
  函数描述:    非链式DMA传输时，调用本函数配置通道参数
               链式DMA传输时，不需要使用本函数。
  输入参数:    channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
               direction : DMA传输方向, 取值为BALONG_DMA_P2M、BALONG_DMA_M2P、
                           BALONG_DMA_M2M之一
               burst_width：取值为0、1、2、3，表示的burst位宽为8、16、32、64bit
               burst_len：取值范围0~15，表示的burst长度为1~16
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
int mdrv_edma_chan_config (unsigned int channel_id, unsigned int direction,unsigned int burst_width, unsigned int burst_len)
{
    return bsp_edma_channel_set_config((u32) channel_id, (u32) direction, (u32) burst_width, (u32) burst_len);
}

/* /// 为联调适配 ccore*/
int mdrv_edma_chan_dest_config(unsigned int channel_id, unsigned int dest_width, unsigned int dest_len)

{
    return bsp_edma_channel_dest_set_config((u32) channel_id, (u32) dest_width, (u32) dest_width);
}

/*******************************************************************************
  函数名:      int balong_dma_channel_start (UINT32 channel_id, UINT32 src_addr,
                       UINT32 des_addr, UINT32 len)
  函数描述:    启动一次同步DMA传输, DMA传输完成后，才返回
               使用本函数时，不需要注册中断处理函数
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
               src_addr：数据传输源地址，必须是物理地址
               des_addr：数据传输目的地址，必须是物理地址
               len：数据传输长度，单位：字节；一次传输数据的最大长度是65535字节
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
int mdrv_edma_chan_start(unsigned int channel_id, unsigned int src_addr, unsigned int des_addr, unsigned int len)
{
    return bsp_edma_channel_start((u32) channel_id, (u32) src_addr, (u32) des_addr, (u32) len);
}

/*******************************************************************************
  函数名:      int balong_dma_channel_async_start (UINT32 channel_id,
                unsigned int src_addr, unsigned int des_addr, unsigned int len)
  函数描述:    启动一次异步DMA传输。启动DMA传输后，就返回。不等待DMA传输完成。
               使用本函数时，注册中断处理函数，中断处理函数中处理DMA
传输完成事件
               或者，不注册中断处理函数，使用balong_dma_channel_is_idle函数查询
               DMA传输是否完成
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
               src_addr：数据传输源地址，必须是物理地址
               des_addr：数据传输目的地址，必须是物理地址
               len：数据传输长度，单位：字节；一次传输数据的最大长度是65535字节
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
int mdrv_edma_chan_async_start(unsigned int channel_id, unsigned int src_addr, unsigned int des_addr, unsigned int len)
{
    return bsp_edma_channel_async_start((u32) channel_id, (u32) src_addr, (u32) des_addr, (u32) len);
}

/*******************************************************************************
  函数名:      int balong_dma_channel_lli_start (UINT32 channel_id)
  函数描述:    启动链式DMA传输。在链式DMA的所有节点传输都全部完成后才返回。
               链式DMA的每个节点的数据最大传输长度为65535字节。
               注意：调用此函数前，必须设置好链表控制块。
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
int mdrv_edma_chan_lli_start(unsigned int channel_id)
{
    return (BSP_S32)bsp_edma_channel_lli_start((u32) channel_id);
}

/*******************************************************************************
  函数名:      int balong_dma_channel_lli_start (UINT32 channel_id)
  函数描述:    启动链式DMA传输，然后立即返回，不等待DMA传输完成。
               链式DMA的每个节点的数据最大传输长度为65535字节。
               注意：调用此函数前，必须设置好链表控制块。
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
int mdrv_edma_chan_lli_async_start(unsigned int channel_id)
{
    return (BSP_S32)bsp_edma_channel_lli_async_start((u32) channel_id);
}

/******************************************************************************
*
  函数名:       int balong_dma_channel_is_idle (UINT32 channel_id)
  函数描述:     查询DMA通道是否空闲
  输入参数:     channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
  输出参数:     无
  返回值:       0 : 通道忙碌
                1 : 通道空闲
                负数 : 失败
*******************************************************************************/
int mdrv_edma_chan_is_idle(unsigned int channel_id)
{
    return (BSP_S32)bsp_edma_channel_is_idle((u32) channel_id);
}
/* end ---- adapt for v9r1 */



