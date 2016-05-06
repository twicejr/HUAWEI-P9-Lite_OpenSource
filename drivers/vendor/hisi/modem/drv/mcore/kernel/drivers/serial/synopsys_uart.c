
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_irq.h>
#include <osl_malloc.h>
#include <irq.h>
#include "serial_core.h"
#include "synopsys_uart.h"

static struct uart_port *uap;

/*****************************************************************************
* 函 数 名  :  synopsys_uart_stop_tx
*
* 功能描述  :  停止发送
*
* 输入参数  :  uart_port

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void synopsys_uart_stop_tx(struct uart_port *port)
{
    unsigned int ier;

    ier = readl(port->base_addr + UART_REGOFF_IER);
    ier &= ~(PTIME | UART_IER_TX_IRQ_ENABLE);
    writel(ier, port->base_addr + UART_REGOFF_IER);
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_start_tx
*
* 功能描述  :  开始发送串口数据
*
* 输入参数  :  uart_port

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void synopsys_uart_start_tx(struct uart_port *port)
{
    unsigned int ier;

    ier = readl(port->base_addr + UART_REGOFF_IER);
    ier |= UART_IER_TX_IRQ_ENABLE;
    writel(ier, port->base_addr + UART_REGOFF_IER);
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_get_char
*
* 功能描述  :  接收串口数据
*
* 输入参数  :  uart_port

* 输出参数  :  无
*
* 返 回 值  :  串口data
*
* 修改记录  :
*****************************************************************************/
static int synopsys_uart_get_char(struct uart_port *port)
{	
    if (!(readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_EMP))
        return -1;

    /* if there is not emp in the FIFO */
    return (int)readl(port->base_addr + UART_REGOFF_RBR);
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_put_char
*
* 功能描述  :  发送串口数据
*
* 输入参数  :  uart_port，char

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void synopsys_uart_put_char(struct uart_port *port, unsigned char ch)
{
    /* Wait until there is space in the FIFO */
    while (0 == (readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_FULL)){}

    /* Send the character */
    writel(ch, port->base_addr + UART_REGOFF_RBR);
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_wait_idle
*
* 功能描述  :  等待串口传输完成
*
* 输入参数  :  uart_port  :对应通道

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static inline void synopsys_uart_wait_idle(struct uart_port *port)
{
    while(readl(port->base_addr + UART_REGOFF_USR) & UART_USR_UART_BUSY) {
        if(readl(port->base_addr + UART_REGOFF_LSR) & UART_LSR_DR)
            (void)readl(port->base_addr + UART_REGOFF_RBR);
    }
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_tx_int_proc
*
* 功能描述  :  串口发送中断处理函数
*
* 输入参数  :  uart_port  :对应通道
* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void synopsys_uart_tx_int_proc(struct uart_port *port)
{
    int pass_counter = UART_FIFO_SIZE;
    char ch;

    do {
        /* there is space in the FIFO */
        if (UART_USR_FIFO_NOT_FULL == (readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_FULL))
        {
            if (*port->ldisc->tx_chars && ((*port->ldisc->tx_chars)(&ch) != 0))
                writel((unsigned char)ch, port->base_addr + UART_REGOFF_RBR);
            else {/* disable transmit interrupt */
                synopsys_uart_stop_tx(port);
                break;
            }
        }
        else
        {
            break;
        }
    }while(--pass_counter > 0);

    /* clear trans interrupt */
    (void)readl(port->base_addr + UART_REGOFF_IIR);
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_rx_int_proc
*
* 功能描述  :  串口接收中断处理函数
*
* 输入参数  :  uart_port  :对应通道
* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void synopsys_uart_rx_int_proc(struct uart_port *port)
{
    int pass_counter = UART_FIFO_SIZE;
    char ch;

    do {
        /* if there is not emp in the FIFO */
        if (readl(port->base_addr + UART_REGOFF_USR) & UART_USR_FIFO_NOT_EMP) {
            ch = (char)readl(port->base_addr + UART_REGOFF_RBR);
            if (*port->ldisc->rx_chars)
                (void)(*port->ldisc->rx_chars)(&ch);
            }
        else
            break;
    }while(--pass_counter > 0);
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_int_handle
*
* 功能描述  :  串口中断响应函数
*
* 输入参数  :  irq :中断号 dev_id:设备ID

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static irqreturn_t synopsys_uart_int_handle(int irq, void *dev_id)
{
    unsigned long interrupt_flg;
    unsigned int status;
    irqreturn_t handled = IRQ_NONE;

    local_irq_save(interrupt_flg);
    status = readl(uap->base_addr + UART_REGOFF_IIR) & 0x0f;

    /*if is "no interrupt pending" dap*/
    if (status != UART_IIR_NO_INTERRUPT) {
        /* receive interrupt */
        if ((status == UART_IIR_REV_VALID)||(status == UART_IIR_REV_TIMEOUT))
            synopsys_uart_rx_int_proc(uap);

        /* transmit interrupt */
        else if (status == UART_IIR_THR_EMPTY)
            synopsys_uart_tx_int_proc(uap);

        /* clear other interrupt status. */
        else {
            (void)readl(uap->base_addr + UART_REGOFF_LSR);
            (void)readl(uap->base_addr + UART_REGOFF_USR);
            (void)readl(uap->base_addr + UART_REGOFF_MSR);
        }
        handled = IRQ_HANDLED;
    }

    local_irq_restore(interrupt_flg);

    return handled;
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_set_termios
*
* 功能描述  :  设置串口参数
*
* 输入参数  :  uart_port

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void synopsys_uart_set_termios(struct uart_port *port)
{
    unsigned int quot;
    unsigned int ul_divisor_high, ul_divisor_low;

    quot = port->uartclk / (16 * port->baudrate);
    ul_divisor_high = (quot & 0xFF00) >> 8;
    ul_divisor_low = quot & 0xFF;

    /*config baudrate: uart must be idle */
    /*config baudrate: enable access DLL and DLH */
    do {
        (void)readl(port->base_addr + UART_REGOFF_USR);
        writel(UART_FCR_DEF_SET, port->base_addr + UART_REGOFF_FCR);
        writel(UART_LCR_DLAB,port->base_addr + UART_REGOFF_LCR);
    }while(!(UART_LCR_DLAB & readl(port->base_addr + UART_REGOFF_LCR)));

    /* Set baud rate */
    writel(ul_divisor_high, port->base_addr + UART_REGOFF_DLH);
    writel(ul_divisor_low, port->base_addr + UART_REGOFF_DLL);

    do {
        (void)readl(port->base_addr + UART_REGOFF_USR);
        writel(UART_FCR_DEF_SET, port->base_addr + UART_REGOFF_FCR);
        writel(UART_LCR_DEFAULTVALUE,port->base_addr + UART_REGOFF_LCR);
    }while(UART_LCR_DLAB & readl(port->base_addr + UART_REGOFF_LCR));

    /* 配置外围发送和接收数据的数目为8bit,1停止位,无校验位,disable DLL&DLH */
    writel((UART_LCR_PEN_NONE | UART_LCR_STOP_1BITS | UART_LCR_DLS_8BITS), port->base_addr + UART_REGOFF_LCR);
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_startup
*
* 功能描述  :  启动串口端口，在打开该设备是会调用，设置中断等工作
*
* 输入参数  :  uart_port  :对应通道

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static int synopsys_uart_startup(struct uart_port *port)
{
    static int flag = 0;
    int retval;
    unsigned long interrupt_flg; 

    local_irq_save(interrupt_flg);

    /* disable FIFO and interrupt */
    writel(UART_IER_IRQ_DISABLE, port->base_addr + UART_REGOFF_IER);
    writel(UART_FCR_FIFO_DISABLE, port->base_addr + UART_REGOFF_FCR);

    /*
     * Allocate the IRQ
     */
    if (((*port->ldisc->rx_chars) || (*port->ldisc->tx_chars)) && (flag == 0)) {
        uap = port;
        retval = request_irq(port->irq, synopsys_uart_int_handle, 0, "synopsys-uart", port);
        if (retval) {
            local_irq_restore(interrupt_flg);
            return retval;
        }
        else
            flag = 1;
    }

    /* enable FIFO */
    writel(UART_FCR_DEF_SET, port->base_addr + UART_REGOFF_FCR);

    /* clear interrupt status */
    (void)readl(port->base_addr + UART_REGOFF_LSR);
    (void)readl(port->base_addr + UART_REGOFF_IIR);
    (void)readl(port->base_addr + UART_REGOFF_USR);
    (void)readl(port->base_addr + UART_REGOFF_RBR);

    synopsys_uart_set_termios(port);

    /*Receiver Int Enable*/
    if (*port->ldisc->rx_chars)
        writel(UART_IER_RX_IRQ_ENABLE, port->base_addr + UART_REGOFF_IER);

    local_irq_restore(interrupt_flg);

    return 0;

}

#if 0
/*****************************************************************************
* 函 数 名  :  synopsys_uart_shutdown
*
* 功能描述  :  关闭串口，在关闭该设备时调用，释放中断等
*
* 输入参数  :  uart_port  :对应通道

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static void synopsys_uart_shutdown(struct uart_port *port)
{
    unsigned long val;
    unsigned long interrupt_flg;

    local_irq_save(interrupt_flg);

    /*
     * disable/clear all interrupts
    */
    writel(UART_IER_IRQ_DISABLE, port->base_addr + UART_REGOFF_IER);
    (void)readl(port->base_addr + UART_REGOFF_LSR);

    local_irq_restore(interrupt_flg);

    /*
     * Free the interrupt
     */
    free_irq(port->irq, port);

    synopsys_uart_wait_idle(port);
    val = readl(port->base_addr + UART_REGOFF_LCR);
    val &= ~(UART_LCR_BREAK);/* [false alarm]:误报 */
    writel(val, port->base_addr + UART_REGOFF_LCR);

    /* disable fifo*/
    writel(UART_FCR_FIFO_DISABLE, port->base_addr + UART_REGOFF_FCR);

}
#endif

/*****************************************************************************
* 函 数 名  :  synopsys_uart_suspend
*
* 功能描述  :  串口挂起
*
* 输入参数  :  无

* 输出参数  :  无
*
* 返 回 值  :  0 : OK
*              1 : ERR
*
* 修改记录  :
*****************************************************************************/
static int synopsys_uart_suspend(struct uart_port *port)
{  
    /* disable FIFO */
    writel(UART_FCR_DEF_SET & ~0x1, port->base_addr + UART_REGOFF_FCR);

    /* disable interrupt */
    disable_irq(port->irq);

    return 0;
}

/*****************************************************************************
* 函 数 名  :  synopsys_uart_resume
*
* 功能描述  :  串口恢复
*
* 输入参数  :  无

* 输出参数  :  无
*
* 返 回 值  :  无
*
* 修改记录  :
*****************************************************************************/
static int synopsys_uart_resume(struct uart_port *port)
{
    int ret;

    ret = synopsys_uart_startup(port);
    if (ret)
        return ret;

    enable_irq(port->irq);

    return 0;
}

static struct uart_ops synopsys_uart_pops = {
    .stop_tx	    = synopsys_uart_stop_tx,      /* stop transmit           */
    .start_tx	    = synopsys_uart_start_tx,     /* start transmit           */
    .startup	    = synopsys_uart_startup,      /* start uart receive/transmit    */
    //.shutdown	    = synopsys_uart_shutdown,     /* shut down uart           */
    .set_termios	= synopsys_uart_set_termios,  /* set termios            */
    .get_char       = synopsys_uart_get_char,
    .put_char       = synopsys_uart_put_char,
    .suspend        = synopsys_uart_suspend,
    .resume         = synopsys_uart_resume,
};

static struct uart_driver synopsys_driver = {
    .ops = &synopsys_uart_pops,
    .periphid = 0x000c21c0,
    .driver_name = "synopsys_uart", 
};

int synopsys_uart_drv_init(void)
{
    int ret = 0;

    ret = uart_register_driver(&synopsys_driver);

    return ret;
}

