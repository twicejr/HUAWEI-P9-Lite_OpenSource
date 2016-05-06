/*
 * arm_uart.h -- arm uart driver
 *
 * Copyright (C) 2014 Huawei Corporation
 *
 *
 */
#ifndef ARM_UART_H
#define ARM_UART_H

     /*-----------------------OFFSET OF REGISTER------------------------*/
#define UART_REGOFF_DR			0x00	/* Data read or written from the interface. */
#define UART_REGOFF_RSR			0x04	/* Receive status register (Read). */
#define UART_REGOFF_FR			0x18	/* Flag register (Read only). */
#define UART_REGOFF_IBRD		0x24	/* Integer baud rate divisor register. */
#define UART_REGOFF_FBRD		0x28	/* Fractional baud rate divisor register. */
#define UART_REGOFF_LCRH		0x2c	/* Line control register. */
#define UART_REGOFF_CR			0x30	/* Control register. */
#define UART_REGOFF_IFLS		0x34	/* Interrupt fifo level select. */
#define UART_REGOFF_IMSC		0x38	/* Interrupt mask. */
#define UART_REGOFF_RIS			0x3c	/* Raw interrupt status. */
#define UART_REGOFF_MIS			0x40	/* Masked interrupt status. */
#define UART_REGOFF_ICR			0x44	/* Interrupt clear register. */
#define UART_REGOFF_DMACR		0x48	/* DMA control register. */

#define UART_FIFO_SIZE			32		/* FIFO SIZE*/
#define AMBA_ISR_PASS_LIMIT		256

     /*-------------------IFLS BITS FIELD-----------------------------*/    
#define UART_IFLS_DEF_SET		0x12 	/* 接收水位1/2full 发送水线为3/4full*/

     /*-------------------CR BITS FIELD-----------------------------*/
#define UART_CR_CTSEN			0x8000	/* CTS hardware flow control */
#define UART_CR_RTSEN			0x4000	/* RTS hardware flow control */
#define UART_CR_OUT2			0x2000	/* OUT2 */
#define UART_CR_OUT1			0x1000	/* OUT1 */
#define UART_CR_RTS				0x0800	/* RTS */
#define UART_CR_DTR				0x0400	/* DTR */
#define UART_CR_RXE				0x0200	/* receive enable */
#define UART_CR_TXE				0x0100	/* transmit enable */
#define UART_CR_LBE				0x0080	/* loopback enable */
#define UART_CR_IIRLP			0x0004	/* SIR low power mode */
#define UART_CR_SIREN			0x0002	/* SIR enable */
#define UART_CR_UARTEN			0x0001	/* UART enable */
#define UART_CR_UARTDIS			0x0000 	/* uart disable*/

     /*-------------------LCRH BITS FIELD-----------------------------*/
#define UART_LCRH_DLS_MASK		0x03	/* 数据长度掩码*/
#define UART_LCRH_DLS_5BITS		0x00	/* 数据长度选择,5bits */
#define UART_LCRH_DLS_6BITS		0x20	/* 数据长度选择,6bits */
#define UART_LCRH_DLS_7BITS		0x40	/* 数据长度选择,7bits */
#define UART_LCRH_DLS_8BITS		0x60	/* 数据长度选择,8bits */
#define UART_LCRH_SPS			0x80
#define UART_LCRH_STP2			0x08
#define UART_LCRH_STP1			0x00	/* 停止位个数,1bit */
#define UART_LCRH_EPS			0x04
#define UART_LCRH_PEN			0x02
#define UART_LCRH_PEN_NONE		0x00	/* set no parity */
#define UART_LCRH_BRK			0x01
#define UART_LCRH_FIFO_ENABLE	0x10	/* Enable both FIFOs */
#define UART_LCRH_FIFO_DISABLE	0x00	/* Disable both FIFOs */

     /*-------------------FR BITS FIELD-----------------------------*/
#define UART_FR_UART_BUSY		0x08	/* UART忙标志   */
#define UART_FR_RX_FIFO_EMP		0x10	/* 接收FIFIO为空 */
#define UART_FR_TX_FIFO_FULL	0x20	/* 发送FIFO为满标志   */
#define UART_FR_RX_FIFO_FULL	0x40	/* 接收FIFO满标志   */
#define UART_FR_TX_FIFO_EMP		0x80	/* 发送FIFO空标志   */
     
     /*-------------------IMSC BITS FIELD-----------------------------*/
#define UART_IMSC_OEIM			(1 << 10)	/* overrun error interrupt mask */
#define UART_IMSC_BEIM			(1 << 9)	/* break error interrupt mask */
#define UART_IMSC_PEIM			(1 << 8)	/* parity error interrupt mask */
#define UART_IMSC_FEIM			(1 << 7)	/* framing error interrupt mask */
#define UART_IMSC_RTIM			(1 << 6)	/* receive timeout interrupt mask */
#define UART_IMSC_TXIM			(1 << 5)	/* transmit interrupt mask */
#define UART_IMSC_RXIM			(1 << 4)	/* receive interrupt mask */
#define UART_IMSC_DSRMIM		(1 << 3)	/* DSR interrupt mask */
#define UART_IMSC_DCDMIM		(1 << 2)	/* DCD interrupt mask */
#define UART_IMSC_CTSMIM		(1 << 1)	/* CTS interrupt mask */
#define UART_IMSC_RIMIM			(1 << 0)	/* RI interrupt mask */

    /*-------------------MIS BITS FIELD-----------------------------*/
#define UART_MIS_OEIS			(1 << 10)	/* overrun error interrupt status */
#define UART_MIS_BEIS			(1 << 9)	/* break error interrupt status */
#define UART_MIS_PEIS			(1 << 8)	/* parity error interrupt status */
#define UART_MIS_FEIS			(1 << 7)	/* framing error interrupt status */
#define UART_MIS_RTIS			(1 << 6)	/* receive timeout interrupt status */
#define UART_MIS_TXIS			(1 << 5)	/* transmit interrupt status */
#define UART_MIS_RXIS			(1 << 4)	/* receive interrupt status */
#define UART_MIS_DSRMIS			(1 << 3)	/* DSR interrupt status */
#define UART_MIS_DCDMIS			(1 << 2)	/* DCD interrupt status */
#define UART_MIS_CTSMIS			(1 << 1)	/* CTS interrupt status */
#define UART_MIS_RIMIS			(1 << 0)	/* RI interrupt status */

    /*-------------------ICR BITS FIELD-----------------------------*/
#define UART_ICR_OEIS			(1 << 10)	/* overrun error interrupt status */
#define UART_ICR_BEIS			(1 << 9)	/* break error interrupt status */
#define UART_ICR_PEIS			(1 << 8)	/* parity error interrupt status */
#define UART_ICR_FEIS			(1 << 7)	/* framing error interrupt status */
#define UART_ICR_RTIS			(1 << 6)	/* receive timeout interrupt status */
#define UART_ICR_TXIS			(1 << 5)	/* transmit interrupt status */
#define UART_ICR_RXIS			(1 << 4)	/* receive interrupt status */
#define UART_ICR_DSRMIS			(1 << 3)	/* DSR interrupt status */
#define UART_ICR_DCDMIS			(1 << 2)	/* DCD interrupt status */
#define UART_ICR_CTSMIS			(1 << 1)	/* CTS interrupt status */
#define UART_ICR_RIMIS			(1 << 0)	/* RI interrupt status */

#endif /* ARM_UART_H */

