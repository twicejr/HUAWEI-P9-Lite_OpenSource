/*
 * synopsys_uart.h -- synopsys uart driver
 *
 * Copyright (C) 2014 Huawei Corporation
 *
 *
 */
#ifndef SYNOPSYS_UART_H
#define SYNOPSYS_UART_H

     /*-----------------------OFFSET OF REGISTER------------------------*/
#define	UART_REGOFF_RBR				0x00	/* UART data register (R/W) */
#define UART_REGOFF_DLL				0x00	/*UART Divisor Low bits */
#define UART_REGOFF_THR				0x00	/*UART Transmit Holding */
#define UART_REGOFF_DLH				0x04	/*UART Divisor High bits*/
#define UART_REGOFF_IER				0x04	/*Int Enable register */
#define UART_REGOFF_FCR				0x08	/*Fifo Control register(W)*/
#define UART_REGOFF_IIR				0x08	/*Int Status register(R)*/
#define UART_REGOFF_LCR				0x0C	/*UART Line Control register */
#define UART_REGOFF_MSR				0x18    /*Modem Status Register */
#define UART_REGOFF_USR				0x7C	/*UART Status register */
#define UART_REGOFF_LSR				0x14	/*UART Line Status Register*/
#define UART_FIFO_SIZE 				16  	/* FIFO SIZE*/
#define AMBA_ISR_PASS_LIMIT			128
#define UART_FIFO_MASK 				0x0F	

     /*-------------------LCR BITS FIELD-----------------------------*/
#define UART_LCR_DLS_MASK			0x03	/* 数据长度掩码*/
#define UART_LCR_DLS_5BITS			0x00	/* 数据长度选择,5bits */
#define UART_LCR_DLS_6BITS			0x01	/* 数据长度选择,6bits */
#define UART_LCR_DLS_7BITS			0x02	/* 数据长度选择,7bits */
#define UART_LCR_DLS_8BITS			0x03	/* 数据长度选择,8bits */
#define UART_LCR_STOP_2BITS			0x04	/* 停止位个数,2bits*/
#define UART_LCR_STOP_1BITS			0x00	/* 停止位个数,1bit */
#define UART_LCR_PEN_NONE	 		0x00	/* set no parity */
#define UART_LCR_PEN				0x08	/* 奇偶校验使能*/
#define UART_LCR_EPS				0x10	/* 奇偶校验选择*/
#define UART_LCR_BREAK				0x40	/* 打开BREAK 控制 */
#define UART_LCR_DLAB				0x80	/* 打开DLL/DHL */
#define UART_LCR_DEFAULTVALUE		0x00	/* LCR默认值*/
#define UART_LCR_BC_NORMAL			0x00	/* 暂停控制位 正常*/
#define UART_LCR_BC_UNNORMAL		0x40	/* 暂停控制位 暂停*/
     
     /*-------------------IER BITS FIELD-----------------------------*/
#define UART_IER_IRQ_DISABLE		0x00	/* Disable both FIFOs */
#define UART_IER_LS_IRQ_ENABLE		0x04	/*Line Status Int Enable*/
#define UART_IER_TX_IRQ_ENABLE		0x02	/*Transmitter Int Enable*/
#define UART_IER_RX_IRQ_ENABLE		0x01	/*Receiver Int Enable*/
#define PTIME						(1<<7)
     
     /*-------------------LSR BITS FIELD-----------------------------*/
#define UART_LSR_DR					0x01	/* 数据准备好*/
#define UART_LSR_OE					0x02	/* 溢出标志*/
#define UART_LSR_PE					0x04	/* 奇偶校验错误标志*/
#define UART_LSR_FE					0x08	/* 帧错误标志*/
#define UART_LSR_BI					0x10	/* 中断暂停标志*/
#define UART_LSR_THRE				0x20	/* THR为空*/
#define UART_LSR_TEMT				0x40	/* 发送空标志*/
#define UART_LSR_ERR_ANY (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI)
     
     /*-------------------IIR BITS FIELD-----------------------------*/
#define UART_IIR_REV_STA			0x06	/* 接收线状态中断   */
#define UART_IIR_REV_VALID			0x04	/* 接收线数据有效 */
#define UART_IIR_REV_TIMEOUT		0x0C	/* 接收超时    */
#define UART_IIR_THR_EMPTY			0x02	/* transmit hold reg empty */
#define UART_IIR_NO_INTERRUPT		0x01	/* NO interrupt pending */
#define UART_IIR_MODEM_INTERRUPT	0x00	/* FOURTH modem int    */
     
     /*-------------------USR BITS FIELD-----------------------------*/
#define UART_USR_UART_BUSY			0x01	/* UART忙标志   */
#define UART_USR_FIFO_NOT_FULL		0x02	/* 发送FIFO不满标志   */
#define UART_USR_FIFO_EMP			0x04	/* 发送FIFO为空标志   */
#define UART_USR_FIFO_NOT_EMP		0x08	/* 接收FIFO非空标志   */
#define UART_USR_FIFO_FULL			0x10	/* 接收FIFO满标志   */
     
     /*-------------------FCR BITS FIELD-----------------------------*/
#define UART_FCR_FIFO_ENABLE		0x01	/* Enable both FIFOs */
#define UART_FCR_FIFO_DISABLE		0x00	/* Disable both FIFOs */
#define UART_FCR_DEF_SET			0xB7	/* 使能FIFO,复位接收与发送FIFO，接收发送水线为FIFO-2 */

#endif /* SYNOPSYS_UART_H */


