/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : __DRV_UART_H__
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : __DRV_UART_H__ 的头文件
  函数列表   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _E_UART_CONSUMER_ID_
{
    CBP_UART_PORT_ID = 1,
    UART_CONSUMER_BUTT
}UART_CONSUMER_ID;

/*****************************************************************************
 函 数 名  : DRV_UART_SEND
 功能描述  : UART口发送数据
             本函数只支持任务上下文同步阻塞类数据发送
 输入参数  : uPortNo
             pDataBuffer
             uslength
 输出参数  : 无
 返 回 值  :  0  发送成功;  1  发送失败;
 调用函数  :
 被调函数  :
*****************************************************************************/
extern int uart_core_send(UART_CONSUMER_ID uPortNo, unsigned char * pDataBuffer, unsigned int ulLength);
#define mdrv_dualmodem_send(uPortNo,pDataBuffer,ulLength) \
        uart_core_send(uPortNo,pDataBuffer,ulLength)
     
/*****************************************************************************
 函 数 名  : DRV_UART_RCV_CALLBACK_REGI
 功能描述  : UART口数据接受上层应用回调函数注册接口
 输入参数  : uPortNo
             pCallback

 输出参数  : 无
 返 回 值  :  0 :注册成功;  -1 ：注册失败
 调用函数  :
 被调函数  :
 修改历史      :
*****************************************************************************/
typedef int (*pUARTRecv)(UART_CONSUMER_ID uPortNo,unsigned char * pData, unsigned int ulLength);
extern int uart_core_recv_handler_register(UART_CONSUMER_ID uPortNo, pUARTRecv pCallback);
#define mdrv_dualmodem_register_rcvhook(uPortNo,pCallback)\
        uart_core_recv_handler_register(uPortNo,pCallback)

extern int bsp_dual_modem_drv_init(void);

#define mdrv_dual_modem_init(void)\
		bsp_dual_modem_drv_init(void)

#ifdef __cplusplus
    }
#endif

#endif

