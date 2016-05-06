#ifndef HI_ARMIP_UART_H
#define HI_ARMIP_UART_H

/*
 * bsp_uart.h -- balong uart driver header for both linux and vxworks
 *
 * Copyright (C) 2012 Huawei Corporation
 * 
 *
*/
/*-----------------------OFFSET OF REGISTER------------------------*/
#define UART_REGOFFSET_RBR			0x00	/*接收数据寄存器*/
#define UART_REGOFFSET_THR			0x00	/*发送数据寄存器*/
#define UART_REGOFFSET_FR			0x18	/*标签寄存器*/
#define UART_REGOFFSET_IBRD			0x24	/*波特率寄存器*/
#define UART_REGOFFSET_FBRD			0x28
#define UART_REGOFFSET_CR			0x30	/*控制寄存器*/
#define UART_REGOFFSET_IFLS			0x34    /*中断fifo level选择寄存器*/
#define UART_REGOFFSET_ICR			0x44	/*中断清除寄存器*/
#define UART_REGOFFSET_LCR_H		0x2C	/*线控寄存器*/
#define UART_REGOFFSET_IMSC			0x38	/*中断屏蔽设置/清除选择寄存器*/
#define UART_REGOFFSET_MIS			0x40	/*屏蔽后的中断状态寄存器*/

#define UART_DR_OE					(1 << 11)
#define UART_DR_BE					(1 << 10)
#define UART_DR_PE					(1 << 9)
#define UART_DR_FE					(1 << 8)
#define UART_DR_ERROR		(UART_DR_OE|UART_DR_BE|UART_DR_PE|UART_DR_FE)

/*-------------------IFLS BITS FIELD-----------------------------*/

#define UART_IFLS_RX_DEF_ONETWO		0x10	/* 接收发送水线为FIFO-1/2 */
#define UART_ARM_LCR_DLS_8BITS      0x60 	/* 数据长度选择,8bits */
/*-------------------IER BITS FIELD-----------------------------*/
#define UART_DISABLE	        	0x00 	/* uart禁能 */
#define UART_ENABLE					0x01 	/* uart使能 */
#define UART_TX_ENABLE      		0x100 	/*发送使能*/
#define UART_RX_ENABLE      		0x200 	/*接收使能*/
#define UART_IRQ_CLR			0xFF 	/*清除所有中断*/

#define UART_LCR_ODD                0x02 	/* 奇校验使能*/
#define UART_LCR_PEN_NONE	 		0x00	/* set no parity */
#define UART_LCR_STOP_1BITS			0x00	/* 停止位个数,1bit */

#define UART_LCR_DEFAULTVALUE       0x00 	/* LCR默认值*/
#define UART_LCR_FIFO_ENABLE	    0x10 	/* Enable both FIFOs */
#define UART_LCR_FIFO_DISABLE	    0x00 	/* Disable both FIFOs */
/*-------------------FR BITS FIELD-----------------------------*/
#define UART_FR_UART_BUSY          	0x08 	/* UART忙标志   */
#define UART_FR_RX_FIFO_EMP			0x10 	/* 接收FIFIO为空 */
#define UART_FR_TX_FIFO_FULL        0x20 	/* 发送FIFO为满标志   */
#define UART_FR_RX_FIFO_FULL      	0x40 	/* 接收FIFO满标志   */
#define UART_FR_TX_FIFO_EMP       	0x80 	/* 发送FIFO空标志   */

/*-------------------IMSC BITS FIELD-----------------------------*/
#define UART_RX_IRQ_ENABLE      	0x10 	/*接收中断使能*/
#define UART_TX_IRQ_ENABLE			0x20 	/*发送中断使能 */
#define UART_TIMEOUT_IRQ_ENABLE		0x40 	/*接收超时中断使能 */
#define UART_ALL_IRQ_DISABLE		0x00

#define UART_RX_IRQ_CLEAR      		0x10 	/*接收中断*/
#define UART_TIMEOUT_IRQ_CLEAR 		0x40 	/*接收超时中断 */

/*-------------------IIR BITS FIELD-----------------------------*/
#define UART_IIR_THR_INTERRUPT      0x20 	/* 发送中断	*/
#define UART_ARMIP_REV_VALID        0x10 	/* 接收线数据有效 */
#define UART_ARMIP_REV_TIMEOUT      0x40 	/* 接收超时    */
#define UART_IRQ_MARK				0xf0	/*中断掩码*/
#endif /* BSP_UART_H */
