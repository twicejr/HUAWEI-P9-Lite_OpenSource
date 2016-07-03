#ifndef HI6930_UART_H
#define HI6930_UART_H

#define UART_USE_FLAG               0x112233
#define AT_UART_USE_FLAG            0x116119

#define PRT_FLAG_EN_MAGIC_M         0x24680136  /* M核心按键宏定义*/
#define PRT_FLAG_EN_MAGIC_A         0x24680137  /* A核心按键宏定义*/

#if 1
/*
 * bsp_uart.h -- balong uart driver header for both linux and vxworks
 *
 * Copyright (C) 2012 Huawei Corporation
 * 
 *
*/
#include "soc_memmap.h"
#include "soc_interrupts.h"

#define ARM_UART_PERIPHERAL_ID      0x00041011
#define SYNOPSYS_UART_PERIPHERAL_ID 0x000c21c0

#define MINI_SYSTEM_UART_ADDR		HI_UART1_REGBASE_ADDR

#define UART0_BASE_ADDR             HI_UART0_REGBASE_ADDR
#define UART1_BASE_ADDR             HI_UART1_REGBASE_ADDR
#define UART2_BASE_ADDR             HI_UART2_REGBASE_ADDR
#define UART3_BASE_ADDR             HI_UART_MDM_REGBASE_ADDR
#define UART0_INT_LVL               INT_LVL_UART0
#define UART1_INT_LVL               INT_LVL_UART1
#define UART2_INT_LVL               INT_LVL_UART2
#define UART3_INT_LVL               INT_LVL_UART_MDM
#define UART0_M3_INT                M3_UART0_INT
#define UART1_M3_INT                M3_UART1_INT
#define UART2_M3_INT                M3_UART2_INT
#define UART3_M3_INT                0

#define CCORE_SYS_UART_BASE         0xE0203000
#define CCORE_SYS_UART_INTID        50


#define UART_BALONG_ID              ARM_UART_PERIPHERAL_ID  /* uart id */
#define UART_ID_ARM                 0x00041011
#define UART_BALONG_ID_MASK         0x000fffff 
#define UART_PRIMCELL_CLOCK         19200000
#define UART_BAUDRATE               115200

/*-----------------------OFFSET OF REGISTER------------------------*/
#define UART_REGOFFSET_RBR			0x00	/*接收数据寄存器*/
#define UART_REGOFFSET_THR			0x00	/*发送数据寄存器*/
#define UART_REGOFFSET_RSR_ECR		0x04	/*接收状态寄存器/错误清除寄存器*/
#define UART_REGOFFSET_FR			0x18	/*标签寄存器*/
#define UART_REGOFFSET_IBRD			0x24	/*波特率寄存器*/
#define UART_REGOFFSET_FBRD			0x28
#define UART_REGOFFSET_LCR_H		0x2C	/*线控寄存器*/
#define UART_REGOFFSET_CR			0x30	/*控制寄存器*/
#define UART_REGOFFSET_IFLS			0x34	/*中断fifo level选择寄存器*/
#define UART_REGOFFSET_IMSC			0x38	/*中断屏蔽的设置/清除选择寄存器*/
#define UART_REGOFFSET_MIS			0x40	/*屏蔽后的中断状态寄存器*/
#define UART_REGOFFSET_ICR			0x44	/*中断清除寄存器*/
#define UART_REGOFFSET_DMACR		0x48	/*DMA控制寄存器*/

#define UART_FIFO_SIZE              32      /* FIFO SIZE*/
#define UART_FIFO_MASK              0xF0

#define PTIME       (1<<7)

#define UART_LCR_BC_NORMAL          0x00 /* 暂停控制位 正常*/
#define UART_LCR_BC_UNNORMAL        0x01 /* 暂停控制位 暂停*/
/*-------------------IFLS BITS FIELD-----------------------------*/

#define UART_IFLS_DEF_SET           0x12 	/* 接收水位1/2full 发送水线为3/4full*/
/*-------------------IER BITS FIELD-----------------------------*/
#define UART_DISABLE	        	0x00 	/* uart禁能 */
#define UART_ENABLE					0x01 	/* uart使能 */
#define UART_TX_ENABLE      		0x100 	/*发送使能*/
#define UART_RX_ENABLE      		0x200 	/*接收使能*/
#define UART_IER_IRQ_CLR			0xFFFF 	/*清除所有中断*/
/*-------------------LCR BITS FIELD-----------------------------*/
#define UART_LCR_DLS_MASK           0x03 	/* 数据长度掩码*/
#define UART_LCR_DLS_5BITS          0x00 	/* 数据长度选择,5bits */
#define UART_LCR_DLS_6BITS          0x20 	/* 数据长度选择,6bits */
#define UART_LCR_DLS_7BITS          0x40 	/* 数据长度选择,7bits */
#define UART_LCR_DLS_8BITS          0x60 	/* 数据长度选择,8bits */

#define UART_LCR_STOP_2BITS         0x08 	/* 停止位个数,2bits*/
#define UART_LCR_STOP_1BITS         0x00 	/* 停止位个数,1bit */
#define UART_LCR_PEN_NONE	        0x00 	/* set no parity */

#define UART_LCR_ODD                0x02 	/* 奇校验使能*/
#define UART_LCR_EPS                0x06 	/* 偶校验使能*/

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
/*-------------------IIR BITS FIELD-----------------------------*/
#define UART_IIR_REV_VALID          0x10 	/* 接收线数据有效 */
#define UART_IIR_THR_INTERRUPT      0x20 	/* 发送中断	*/
#define UART_IIR_REV_TIMEOUT        0x40	/* 接收超时    */


/******************* uart print macro definition ********************/
#ifndef __ASSEMBLY__
struct uart_info{
	unsigned int uart_base_addr;
	unsigned int uart_intid;
};

extern struct uart_info g_uart_info;

static inline void print_info(const char *buffer)
{
    int loop;
    volatile unsigned int status = 0;
    while (*buffer != '\0')
    {
        /* wait for the tx fifo is empty and the uart is idle */
        loop = 0x10000;
        while ((status != 0x10) && loop--)
        {
            status = *(volatile unsigned *)(HI_UART0_REGBASE_ADDR + UART_REGOFFSET_FR) & 0x18;
        }
		*(volatile unsigned *)(HI_UART0_REGBASE_ADDR + UART_REGOFFSET_RBR) = (unsigned int)(*buffer);
        buffer++;
    }
}
#endif
static inline void modem_uart_gpio_config(void)
{
	/*设置GPIO 20 配置uart6为modem 使用--K3V5 SFT*/
	*(volatile unsigned *)(0xE8A1F400) = (unsigned int)(0xFF);
	*(volatile unsigned *)(0xE8A1F3FC) = (unsigned int)(0x20);
}
#define print_uart_m3boot(value)\
	ldr r1, =HI_UART0_REGBASE_ADDR;\
	ldr r2, =value;\
	ldr r3, =UART_REGOFFSET_THR;\
	str r2, [r1,r3]
            
#define uart_init_m3boot \
	ldr r1, =HI_UART0_REGBASE_ADDR;\
	ldr r2, =0xE0;\
	ldr r3, =UART_REGOFFSET_RSR_ECR;\
	str r2, [r1, r3];\
	ldr r2, =0x0;\
	ldr r3, =UART_REGOFFSET_IMSC;\
	str r2, [r1, r3];\
	ldr r2, =0xFFFF;\
	ldr r3, =UART_REGOFFSET_ICR;\
	str r2, [r1, r3];\
	ldr r2, =0x1A;\
	ldr r3, =UART_REGOFFSET_IBRD;\
	str r2, [r1, r3];\
	ldr r2, =0x3;\
	ldr r3, =UART_REGOFFSET_FBRD;\
	str r2, [r1, r3];\
	ldr r2, =0x70;\
	ldr r3, =UART_REGOFFSET_LCR_H;\
	str r2, [r1, r3];\
	ldr r2, =0x164;\
	ldr r3, =UART_REGOFFSET_IFLS;\
	str r2, [r1, r3];\
	ldr r2, =0x0;\
	ldr r3, =UART_REGOFFSET_DMACR;\
	str r2, [r1, r3];\
	ldr r2, =0x301;\
	ldr r3, =UART_REGOFFSET_CR;\
	str r2, [r1, r3];\
	bx lr
#endif
#endif /* BSP_UART_H */

