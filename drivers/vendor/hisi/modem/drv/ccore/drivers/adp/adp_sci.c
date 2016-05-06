/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 : adp_sci.c
*
*   作    者 :  Y00171698
*
*   描    述 :  本文件命名为"adp_sci.c", 实现SIM/USIM卡驱动功能
*
*   修改记录 :  
*************************************************************************/
#include "product_config.h"
#include "mdrv_sci.h"
#include "bsp_om.h"
#include "bsp_sci.h"

SCI_API_MODE sci_api_mode = SCI_API_NORMAL;


/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_RST
*
* 功能描述  : 本接口用于复位SCI（Smart Card Interface）驱动和USIM（Universal 
*           Subscriber Identity Module）卡
*
* 输入参数  :  无
* 输出参数  : 无
*
* 返 回 值  : OK  复位成功
*
* 修改记录  :  Yangzhi create
*
*****************************************************************************/
int mdrv_sci_reset(RESET_MODE_E rstMode)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
    #if defined(INSTANCE_1)
            return ((int)I1_bsp_sci_reset(rstMode));    
    #elif defined(INSTANCE_2)
            return ((int)I2_bsp_sci_reset(rstMode));
    #else
            return ((int)bsp_sci_reset(rstMode));
    #endif
    }
    else
    {
        return MDRV_ERROR;
    }
}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_GET_CARD_STAU
*
* 功能描述  : 本接口用于获得卡当前的状态
*
* 输入参数  : 无  
* 输出参数  : 无
                 
* 返 回 值  :    卡状态
*           
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_get_cardstatus(BSP_VOID)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    #if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_card_status_get());
    #elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_card_status_get());
    #else
        return ((int)bsp_sci_card_status_get());
    #endif
    }
    else
    {
        return SCI_CARD_STATE_NOCARD;
    }


}

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_SND_DATA
*
* 功能描述  : 本接口用于发送一段数据到USIM卡
*
* 输入参数  : u32 u32DataLength 发送数据的有效长度。取值范围1～256，单位为字节  
*             u8 *pu8DataBuffer 发送数据所在内存的首地址，如是动态分配，调用接口
*                                   后不能立即释放，依赖于硬件发完数据
* 输出参数  : 无
*
* 返 回 值  : OK
*           BSP_ERR_SCI_NOTINIT
*           BSP_ERR_SCI_INVALIDPARA
*           BSP_ERR_SCI_DISABLED
*           BSP_ERR_SCI_NOCARD
*           BSP_ERR_SCI_NODATA
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_send_data(unsigned int u32DataLength,unsigned char * pu8DataBuffer)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
    #if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_data_send(u32DataLength, pu8DataBuffer));
    #elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_data_send(u32DataLength, pu8DataBuffer));
    #else
        return ((int)bsp_sci_data_send(u32DataLength, pu8DataBuffer));
    #endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_RCV
*
* 功能描述  : 本接口用于USIM Manager读取来自SCI Driver的卡返回数据
*             该接口为阻塞接口，只有SCI接收到足够的数据量后才会返回；
*             该接口的超时门限为1s
*
* 输入参数  : u32  u32DataLength USIM Manager欲从SCI Driver读取的数据长度。
* 输出参数  : u8 *pu8DataBuffer USIM Manager指定的Buffer，SCI Driver将数据拷贝到本Buffer。
* 返 回 值  : OK
*             BSP_ERR_SCI_NOTINIT
*             BSP_ERR_SCI_INVALIDPARA
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_recv(unsigned int u32DataLength,unsigned char * pu8DataBuffer)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_data_read_sync(u32DataLength, pu8DataBuffer));
#elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_data_read_sync(u32DataLength, pu8DataBuffer));
#else
        return ((int)bsp_sci_data_read_sync(u32DataLength, pu8DataBuffer));

#endif
    }
    else
    {
        return MDRV_ERROR;
    }


}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_RCV_ALL
*
* 功能描述  : 本接口用于USIM Manager在读数超时的时候，调用本函数，读取接收数据缓冲中的所有数据
*
* 输入参数  : 无  
* 输出参数  : u32 *u32DataLength Driver读取的数据长度，返回给USIM Manager。取值范围1～256，单位是字节
*           u8 * pu8DataBuffer USIM Manager指定的Buffer，SCI Driver将数据拷贝到本Buffer
*
* 返 回 值  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* 修改记录  : 
*
*****************************************************************************/
unsigned int mdrv_sci_recv_all(unsigned int *u32DataLength,unsigned char * pu8DataBuffer)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((unsigned int)I1_bsp_sci_all_data_read(u32DataLength, pu8DataBuffer));
#elif defined(INSTANCE_2)
        return ((unsigned int)I2_bsp_sci_all_data_read(u32DataLength, pu8DataBuffer));
#else
        return ((unsigned int)bsp_sci_all_data_read(u32DataLength, pu8DataBuffer));

#endif
    }
    else
    {
        return MDRV_OK;
    }


}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_GET_ATR
*
* 功能描述  : 本接口用于将Driver层缓存的ATR数据和数据个数返回给USIM Manager层
*
* 输入参数  : void  
* 输出参数  : u8 *u8DataLength  Driver读取的ATR数据长度，返回给USIM Manager。
*                                   取值范围0～32，单位是字节
*           u8 *pu8ATR          USIM Manager指定的Buffer，SCI Driver将ATR
*                                   数据拷贝到本Buffer。一般为操作系统函数动态分配
*                                   或者静态分配的地址
* 
*
* 返 回 值  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_get_atr(unsigned long * u32DataLength, unsigned char * pu8ATR,SCI_ATRINFO_S* stSCIATRInfo)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_atr_get((u8 *)u32DataLength, pu8ATR,stSCIATRInfo));
#elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_atr_get((u8 *)u32DataLength, pu8ATR,stSCIATRInfo));
#else
        return ((int)bsp_sci_atr_get((u8 *)u32DataLength, pu8ATR,stSCIATRInfo));

#endif
    }
    else
    {
        return MDRV_ERROR;
    }


}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_CLASS_SWITCH
*
* 功能描述  : 本接口用于支持PS对卡的电压类型进行切换，从1.8V切换到3V
*
* 输入参数  : BSP_VOID  
* 输出参数  : 无
*
* 返 回 值  :  OK    当前电压不是最高的，进行电压切换操作
*           BSP_ERR_SCI_CURRENT_STATE_ERR 切换失败 current SCI driver state is ready/rx/tx 
*           BSP_ERR_SCI_VLTG_HIGHEST   当前电压已经是最高电压，没有进行电压切换
*           BSP_ERR_SCI_NOTINIT
*           BSP_ERR_SCI_CURRENT_VLTG_ERR 当前电压值异常（非class B或者C）
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
int  mdrv_sci_switch_class(void)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((int)I1_bsp_sci_vltg_class_switch());
#elif defined(INSTANCE_2)
        return ((int)I2_bsp_sci_vltg_class_switch());
#else
        return ((int)bsp_sci_vltg_class_switch());

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_SHOW_VLT
*
* 功能描述  : 本接口用于显示当前SIM卡接口电压
*
* 输入参数  : 无  
* 输出参数  :u32 * pu32Vltgval 当前电压
*
* 返 回 值  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* 修改记录  : 
*
*****************************************************************************/
unsigned int  mdrv_sci_show_voltage(unsigned int* pu32Vltgval)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return ((unsigned int)I1_bsp_sci_show_vltg_val(pu32Vltgval));
#elif defined(INSTANCE_2)
        return ((unsigned int)I2_bsp_sci_show_vltg_val(pu32Vltgval));
#else
        return ((unsigned int)bsp_sci_show_vltg_val(pu32Vltgval));

#endif
    }
    else
    {
        return MDRV_OK;
    }

}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_TM_STOP
*
* 功能描述  : 本接口用于支持PS关闭SIM卡时钟
*
* 输入参数  : 
*           SCI_CLK_STOP_TYPE_E enTimeStopCfg 时钟停止模式
*   
* 输出参数  : 无
*
* 返 回 值  : OK - successful completion
*               ERROR - failed
*               BSP_ERR_SCI_NOTINIT
*               BSP_ERR_SCI_INVALIDPARA - invalid mode specified
*               BSP_ERR_SCI_UNSUPPORTED - not support such a operation
* 修改记录  : Yangzhi create
*
*****************************************************************************/
int mdrv_sci_stop_tm(SCI_CLK_STOP_TYPE_E enTimeStopCfg)
{
        
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_clk_status_cfg((u32)enTimeStopCfg);
#elif defined(INSTANCE_2)
        return I2_bsp_sci_clk_status_cfg((u32)enTimeStopCfg);
#else
        return bsp_sci_clk_status_cfg((u32)enTimeStopCfg);

#endif

     }
     else
     {
        return MDRV_ERROR;
     }

}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_DEACT
*
* 功能描述  : 本接口用于对SIM卡的去激活操作
*
* 输入参数  : 无
*   
* 输出参数  : 无
*
* 返 回 值  : OK
*             BSP_ERR_SCI_NOTINIT
* 修改记录  : 
*
*****************************************************************************/
unsigned int mdrv_sci_deact(void)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_deactive();
#elif defined(INSTANCE_2)
        return I2_bsp_sci_deactive();
#else
        return bsp_sci_deactive();

#endif
    }
    else
    {
        return MDRV_OK;
    }


}
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_GET_CLK_STAU
*
* 功能描述  : 本接口用于获取当前SIM卡时钟状态
*
* 输入参数  : u32 *pu32SciClkStatus   变量指针，用于返回SIM卡时钟状态：
*                                       0：时钟已打开；
*                                       1：时钟停止 
* 输出参数  : 无
*
* 返 回 值  : OK    操作成功
*          BSP_ERR_SCI_INVALIDPARA
* 修改记录  : 
*
*****************************************************************************/
unsigned int mdrv_sci_get_clkstat(unsigned int * pu32SciClkStatus)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (unsigned int)I1_bsp_sci_get_clk_status(pu32SciClkStatus);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_bsp_sci_get_clk_status(pu32SciClkStatus);
#else
        return (unsigned int)bsp_sci_get_clk_status(pu32SciClkStatus);

#endif
    }
    else
    {
        return MDRV_OK;
    }

}

/*****************************************************************************
* 函 数 名  : DRV_PCSC_GET_CLK_FREQ
*
* 功能描述  : 本接口用于获取当前SIM卡时钟频率
*
* 输入参数  : 无
*
* 输出参数  : BSP_U32 *pLen   时钟频率数据的长度
*             BSP_U8 *pBuf    时钟频率数据
* 返 回 值  : OK    操作成功
*             BSP_ERR_SCI_INVALIDPARA
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_sci_get_clkfreq(unsigned long * pLen,unsigned char * pBuf)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
#if defined(INSTANCE_1)
        return (unsigned int)I1_appl131_get_clk_freq((u32*)pLen, pBuf);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_appl131_get_clk_freq((u32*)pLen, pBuf);
#else
        return (unsigned int)appl131_get_clk_freq((u32*)pLen, pBuf);

#endif
    }
    else
    {
        return MDRV_OK;
    }
}

/*****************************************************************************
* 函 数 名  : DRV_PCSC_GET_BAUD_RATE
*
* 功能描述  : 本接口用于获取当前SIM卡波特率
*
* 输入参数  : 无
*
* 输出参数  : BSP_U32 *pLen   波特率数据的长度
*             BSP_U8 *pBuf    波特率数据
*
* 返 回 值  : OK    操作成功
*             BSP_ERR_SCI_INVALIDPARA
* 修改记录  : 
*
*****************************************************************************/
unsigned int mdrv_sci_get_baudrate(unsigned long * pLen, unsigned char * pBuf)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
#if defined(INSTANCE_1)
        return (unsigned int)I1_appl131_get_baud_rate((u32*)pLen, pBuf);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_appl131_get_baud_rate((u32*)pLen, pBuf);
#else
        return (unsigned int)appl131_get_baud_rate((u32*)pLen, pBuf);

#endif
    }
    else
    {
        return MDRV_OK;
    }
}


/*****************************************************************************
* 函 数 名  : DRV_PCSC_GET_SCI_PARA
*
* 功能描述  : 本接口用于获取当前SIM卡的PCSC相关参数
*
* 输入参数  : 无
*
* 输出参数  : u8 *pBuf    PCSC相关参数
*
* 返 回 值  : OK    操作成功
*             BSP_ERR_SCI_INVALIDPARA
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_sci_get_parameter(unsigned char * pBuf)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
    
#if defined(INSTANCE_1)
        return (unsigned int)I1_appl131_get_pcsc_paremeter(pBuf);
#elif defined(INSTANCE_2)
        return (unsigned int)I2_appl131_get_pcsc_paremeter(pBuf);
#else
        return (unsigned int)appl131_get_pcsc_paremeter(pBuf);

#endif
    }
    else
    {
        return MDRV_OK;
    }

}


/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_FUNC_REGISTER
*
* 功能描述  : 本接口用于注册OAM  回调函数
* 输入参数  : void  
* 输出参数  : 无
*
* 返 回 值  : OK  复位成功
*
* 修改记录  : 
*
*****************************************************************************/
void mdrv_sci_register_callback(OMSCIFUNCPTR omSciFuncPtr)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        I1_bsp_sci_func_register(omSciFuncPtr);
#elif defined(INSTANCE_2)
        I2_bsp_sci_func_register(omSciFuncPtr);
#else
        bsp_sci_func_register(omSciFuncPtr);

#endif
    }

}

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_RECORD_DATA_SAVE
*
* 功能描述  : 本接口可维可测信息记录
* 输入参数  : void  
* 输出参数  : 无
*
* 返 回 值  : OK  成功
*
* 修改记录  : 
*
*****************************************************************************/
void mdrv_sci_save_recorddata(SCI_LOG_MODE log_mode) 
{    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        (void)I1_bsp_sci_record_data_save(log_mode);
#elif defined(INSTANCE_2)
        (void)I2_bsp_sci_record_data_save(log_mode);
#else
        (void)bsp_sci_record_data_save(log_mode);

#endif
    }
}


/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_SETBWT
*
* 功能描述  : 本接口用于配置块等待时间
*
* 输入参数  : BSP_U32 nBWT :配置超时时间为BWT的nBWT倍
*
* 输出参数  : 无
*
* 返 回 值  : OK/ERROR
* 修改记录  : 2013年10月15日   liuyi  creat
*
*****************************************************************************/
int mdrv_sci_set_bwt(unsigned int nBWT)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (int)I1_bsp_sci_set_bwt(nBWT);
#elif defined(INSTANCE_2)
        return (int)I2_bsp_sci_set_bwt(nBWT);
#else
        return (int)bsp_sci_set_bwt(nBWT);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_PROTOCOL_SWITCH
*
* 功能描述  : 本接口用于通知底软进行T=0和T=1协议类型切换
*
* 输入参数  : RESET_MODE enSIMProtocolMode:需要切换为的协议类型
*
* 输出参数  : 无
*
* 返 回 值  : OK/ERROR
* 修改记录  : 2013年10月15日   liuyi  creat
*
*****************************************************************************/
int mdrv_sci_switch_protocol(PROTOCOL_MODE_E enSIMProtocolMode)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (int)I1_bsp_sci_protocol_switch(enSIMProtocolMode);
#elif defined(INSTANCE_2)
        return (int)I2_bsp_sci_protocol_switch(enSIMProtocolMode);
#else
        return (int)bsp_sci_protocol_switch(enSIMProtocolMode);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
* 函 数 名  : BSP_SCI_BLK_Receive
* 功能描述  : 本接口用于在T=1时USIM Manager读取来自SCI Driver的卡返回数据；
*             如果出现BWT超时，在数据读取时返回一个超时的值SCI_TIMEOUT
*
* 输入参数  : 无
* 输出参数  : BSP_U8 *pu8Data USIM Manager指定的Buffer，SCI Driver将数据拷贝到本Buffer。
              BSP_U32 *pulLength SCI Driver接收到的数据长度。

* 返 回 值  : OK : 0
              ERROR : -1
              SCI_TIMEOUT : 1
*
* 修改记录  : 2013年10月15日   liuyi  creat
*
*****************************************************************************/
int mdrv_sci_rcv_blk(unsigned char *pu8Data, unsigned int *pulLength)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return (int)I1_bsp_sci_blk_rcv(pu8Data, pulLength);
#elif defined(INSTANCE_2)
        return (int)I2_bsp_sci_blk_rcv(pu8Data, pulLength);
#else
        return (int)bsp_sci_blk_rcv(pu8Data, pulLength);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }
}

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_RECORDLOG_READ
*
* 功能描述  : 本接口获取sim卡异常时定位信息
* 输入参数  : pucDataBuff: 获取定位信息的buffer
              ulMaxLength: 最大值，判断使用
*
* 返 回 值  : pulLength: 获取数据长度
*
* 返 回 值  : 无
*
* 修改记录  : 

*
* 修改记录  : 
*
*****************************************************************************/
int  mdrv_sci_read_recordlog(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_record_log_read(pucDataBuff, pulLength, ulMaxLength);
#elif defined(INSTANCE_2)
        return I2_bsp_sci_record_log_read(pucDataBuff, pulLength, ulMaxLength);
#else
        return bsp_sci_record_log_read(pucDataBuff, pulLength, ulMaxLength);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_GET_ERRNO
*
* 功能描述  : 本接口获取接口调用返回的错误码
* 输入参数  :  无
* 输出参数  :  无
*
* 返 回 值  : 错误码
*
* 修改记录  : 
*
*****************************************************************************/
int mdrv_sci_get_errno(void) 
{
	return BSP_OK;
}

/*****************************************************************************
 * 函 数 名  : mdrv_sci_slot_switch
 *
 * 功能描述  : 切换卡与卡槽的对应关系
 * 输入参数  : sci_slot0 卡槽0期望的状态
 *                           sci_slot1 卡槽1期望的状态
 *
 * 返 回 值  : 切换结果
 *
 *
 * 返 回 值  : 无
 *
 * 修改记录  :
 *
 *****************************************************************************/
int mdrv_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2)
{
    
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
        return I1_bsp_sci_slot_switch(sci_slot0,sci_slot1,sci_slot2);
#elif defined(INSTANCE_2)
        return I2_bsp_sci_slot_switch(sci_slot0,sci_slot1,sci_slot2);
#else
        return bsp_sci_slot_switch(sci_slot0,sci_slot1,sci_slot2);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }

}

/*****************************************************************************
 * 函 数 名  : mdrv_sci_get_slot_state
 *
 * 功能描述  : 获取卡槽的对应关系
 * 输入参数  : sci_slot0 卡槽0的状态
 *                           sci_slot1 卡槽1的状态
 *
 * 返 回 值  : 切换结果
 *
 *
 * 返 回 值  : 无
 *
 * 修改记录  :
 *
 *****************************************************************************/

int mdrv_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2)
{
    if(sci_api_mode == SCI_API_NORMAL)
    {
#if defined(INSTANCE_1)
            return I1_bsp_sci_get_slot_state(sci_slot0,sci_slot1,sci_slot2);
#elif defined(INSTANCE_2)
            return I2_bsp_sci_get_slot_state(sci_slot0,sci_slot1,sci_slot2);
#else
            return bsp_sci_get_slot_state(sci_slot0,sci_slot1,sci_slot2);

#endif
    }
    else
    {
        return MDRV_ERROR;
    }


}


