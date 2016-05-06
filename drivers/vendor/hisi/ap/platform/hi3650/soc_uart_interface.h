/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_uart_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:23:19
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_UART.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_UART_INTERFACE_H__
#define __SOC_UART_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：数据寄存器。
   位域定义UNION结构:  SOC_UART_UARTDR_UNION */
#define SOC_UART_UARTDR_ADDR(base)                    ((base) + (0x000))

/* 寄存器说明：接收状态寄存器/错误清除寄存器。
   位域定义UNION结构:  SOC_UART_UARTRSR_UARTECR_UNION */
#define SOC_UART_UARTRSR_UARTECR_ADDR(base)           ((base) + (0x004))

/* 寄存器说明：标签寄存器。
   位域定义UNION结构:  SOC_UART_UARTFR_UNION */
#define SOC_UART_UARTFR_ADDR(base)                    ((base) + (0x018))

/* 寄存器说明：IrDA低功耗计数器寄存器。
   位域定义UNION结构:  SOC_UART_UARTLPR_UNION */
#define SOC_UART_UARTLPR_ADDR(base)                   ((base) + (0x020))

/* 寄存器说明：波特率寄存器。
   位域定义UNION结构:  SOC_UART_UARTIBRD_UNION */
#define SOC_UART_UARTIBRD_ADDR(base)                  ((base) + (0x024))

/* 寄存器说明：波特率寄存器。
   位域定义UNION结构:  SOC_UART_UARTFBRD_UNION */
#define SOC_UART_UARTFBRD_ADDR(base)                  ((base) + (0x028))

/* 寄存器说明：线控（line control）寄存器。
   位域定义UNION结构:  SOC_UART_UARTLCR_H_UNION */
#define SOC_UART_UARTLCR_H_ADDR(base)                 ((base) + (0x02C))

/* 寄存器说明：控制寄存器。
   位域定义UNION结构:  SOC_UART_UARTCR_UNION */
#define SOC_UART_UARTCR_ADDR(base)                    ((base) + (0x030))

/* 寄存器说明：中断FIFO level选择寄存器。
            发送FIFO和接收FIFO的深度都是64。
   位域定义UNION结构:  SOC_UART_UARTIFLS_UNION */
#define SOC_UART_UARTIFLS_ADDR(base)                  ((base) + (0x034))

/* 寄存器说明：中断屏蔽的设置/清除选择寄存器。
            值“0”表示中断被屏蔽，值“1”表示中断被启用。
   位域定义UNION结构:  SOC_UART_UARTIMSC_UNION */
#define SOC_UART_UARTIMSC_ADDR(base)                  ((base) + (0x038))

/* 寄存器说明：原始中断状态寄存器。
            复位时除了modem中断（bit[1]）外，其余bit全都清零。modem中断复位后状态不确定。值“0”表示该中断未触发，值“1”表示该中断已触发。
   位域定义UNION结构:  SOC_UART_UARTRIS_UNION */
#define SOC_UART_UARTRIS_ADDR(base)                   ((base) + (0x03C))

/* 寄存器说明：屏蔽后中断状态寄存器。
            复位时除了modem中断（bit[1]）外，其余bit全都清零。modem中断复位后状态不确定。值“0”表示该中断未触发，值“1”表示该中断已触发。
   位域定义UNION结构:  SOC_UART_UARTMIS_UNION */
#define SOC_UART_UARTMIS_ADDR(base)                   ((base) + (0x040))

/* 寄存器说明：中断清除寄存器。
            写“1”清除相应中断，写“0”不起作用。
   位域定义UNION结构:  SOC_UART_UARTICR_UNION */
#define SOC_UART_UARTICR_ADDR(base)                   ((base) + (0x044))

/* 寄存器说明：DMA控制寄存器。
   位域定义UNION结构:  SOC_UART_UARTDMACR_UNION */
#define SOC_UART_UARTDMACR_ADDR(base)                 ((base) + (0x048))





/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/



/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_UART_UARTDR_UNION
 结构说明  : UARTDR 寄存器结构定义。地址偏移量:0x000，初值:0x0000，宽度:16
 寄存器说明: 数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  data     : 8;  /* bit[0-7]  : 接收和发送的数据。 */
        unsigned short  fe       : 1;  /* bit[8]    : Framing错误。
                                                      0：无意义；
                                                      1：接收到的字符的停止位错误（有效的停止位为1）。
                                                      FIFO模式下，该错误与FIFO顶部的字符相关联。 */
        unsigned short  pe       : 1;  /* bit[9]    : Parity错误。
                                                      0：无意义；
                                                      1：接收数据的校验结果和寄存器UARTLCR_H中的设置不匹配。
                                                      FIFO模式下，该错误与FIFO顶部的字符相关联。 */
        unsigned short  be       : 1;  /* bit[10]   : Break错误。
                                                      0：无意义；
                                                      1：break条件被检测到，接收数据的输入保持低的时间比一个全字传输（定义为start、data、parity和stop bit）时间还要长。
                                                      当break发生时，只有一个0字符存在FIFO中。当数据输入变为1（marking state）且下一个有效的起始位被接收时，下一个字符才被使能。 
                                                      FIFO模式下，该错误与FIFO顶部的字符相关联。 */
        unsigned short  oe       : 1;  /* bit[11]   : Overrun错误。
                                                      0：接收FIFO有空位且有一个新的字符写到FIFO中；
                                                      1：接收FIFO满时，有新数据到达。 */
        unsigned short  reserved : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_UART_UARTDR_UNION;
#endif
#define SOC_UART_UARTDR_data_START      (0)
#define SOC_UART_UARTDR_data_END        (7)
#define SOC_UART_UARTDR_fe_START        (8)
#define SOC_UART_UARTDR_fe_END          (8)
#define SOC_UART_UARTDR_pe_START        (9)
#define SOC_UART_UARTDR_pe_END          (9)
#define SOC_UART_UARTDR_be_START        (10)
#define SOC_UART_UARTDR_be_END          (10)
#define SOC_UART_UARTDR_oe_START        (11)
#define SOC_UART_UARTDR_oe_END          (11)


/*****************************************************************************
 结构名    : SOC_UART_UARTRSR_UARTECR_UNION
 结构说明  : UARTRSR_UARTECR 寄存器结构定义。地址偏移量:0x004，初值:0x0000，宽度:16
 寄存器说明: 接收状态寄存器/错误清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  fe       : 1;  /* bit[0]   : Framing错误。
                                                     0：写寄存器UARTECR；
                                                     1：接收到的字符的停止位错误（有效停止位为1）。 */
        unsigned short  pe       : 1;  /* bit[1]   : Parity错误。
                                                     0：写寄存器UARTECR；
                                                     1：接收数据的校验结果和寄存器UARTLCR_H中的设置不匹配。
                                                     FIFO模式下，该错误与FIFO顶部的字符相关联。 */
        unsigned short  be       : 1;  /* bit[2]   : Break错误。
                                                     0：写寄存器UARTECR；
                                                     1：Break条件被检测到，表示接收数据的输入保持低的时间比一个全字传输（定义了start、data、parity、stop bit）时间还要长。
                                                     当Break发生时，只有一个0字符存在FIFO中。只有当数据输入变为1（marking state）且下一个有效的起始位被接收时，下一个字符才被使能。
                                                     FIFO模式下，该错误与FIFO顶部的字符相关联。 */
        unsigned short  oe       : 1;  /* bit[3]   : Overrun错误。
                                                     0：写寄存器UARTECR；
                                                     1：接收FIFO满且接收了一个数据。
                                                     当FIFO满时，FIFO中的内容保持有效。因为不会有下一个数据写到FIFO中，只是移位寄存器会溢出。CPU必须立刻读数据以腾空FIFO。 */
        unsigned short  reserved_0: 1;  /* bit[4]   : 保留。读时会读出不可预知的数。 */
        unsigned short  cer      : 3;  /* bit[5-7] : 写时清除framing、parity、break和overrun错误（与写入值大小无关）。 */
        unsigned short  reserved_1: 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_UART_UARTRSR_UARTECR_UNION;
#endif
#define SOC_UART_UARTRSR_UARTECR_fe_START        (0)
#define SOC_UART_UARTRSR_UARTECR_fe_END          (0)
#define SOC_UART_UARTRSR_UARTECR_pe_START        (1)
#define SOC_UART_UARTRSR_UARTECR_pe_END          (1)
#define SOC_UART_UARTRSR_UARTECR_be_START        (2)
#define SOC_UART_UARTRSR_UARTECR_be_END          (2)
#define SOC_UART_UARTRSR_UARTECR_oe_START        (3)
#define SOC_UART_UARTRSR_UARTECR_oe_END          (3)
#define SOC_UART_UARTRSR_UARTECR_cer_START       (5)
#define SOC_UART_UARTRSR_UARTECR_cer_END         (7)


/*****************************************************************************
 结构名    : SOC_UART_UARTFR_UNION
 结构说明  : UARTFR 寄存器结构定义。地址偏移量:0x018，初值:0x0091，宽度:16
 寄存器说明: 标签寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cts      : 1;  /* bit[0]   : UART 被允许clear to send。
                                                     该位是UART clear to send modem status（nUARTCTS）的取反，即Modem状态的输入为0，该位为1。 */
        unsigned short  reserved_0: 2;  /* bit[1-2] : 保留。 */
        unsigned short  busy     : 1;  /* bit[3]   : UART busy标记。
                                                     0：UART is not busy；
                                                     1：UART正在发送数据。该位一直保持到整个字节（包括所有的停止位）从移位寄存器中发送出去。
                                                     一旦发送FIFO非空，该位就置位，与UART是否使能无关。 */
        unsigned short  rxfe     : 1;  /* bit[4]   : 含义取决于寄存器UARTLCR_H[fen]值。
                                                     l FIFO禁止：当接收保持寄存器空时，该位置位。
                                                     l FIFO使能：当接收FIFO为空时，该位置位。 */
        unsigned short  txff     : 1;  /* bit[5]   : 含义取决于寄存器UARTLCR_H[fen]值。
                                                     l FIFO禁止：当发送保持寄存器满时，该位置位。
                                                     l FIFO使能：当发送FIFO为满时，该位置位。 */
        unsigned short  rxff     : 1;  /* bit[6]   : 含义取决于寄存器UARTLCR_H[fen]值。
                                                     l FIFO禁止：当接收保持寄存器满时，该位置位。
                                                     l FIFO使能：当接收FIFO为满时，该位置位。 */
        unsigned short  txfe     : 1;  /* bit[7]   : 含义取决于寄存器UARTLCR_H[fen]值。
                                                     l FIFO禁止：当发送保持寄存器空时，该位置位。
                                                     l FIFO使能：当发送FIFO为空时，该位置位。 */
        unsigned short  reserved_1: 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_UART_UARTFR_UNION;
#endif
#define SOC_UART_UARTFR_cts_START       (0)
#define SOC_UART_UARTFR_cts_END         (0)
#define SOC_UART_UARTFR_busy_START      (3)
#define SOC_UART_UARTFR_busy_END        (3)
#define SOC_UART_UARTFR_rxfe_START      (4)
#define SOC_UART_UARTFR_rxfe_END        (4)
#define SOC_UART_UARTFR_txff_START      (5)
#define SOC_UART_UARTFR_txff_END        (5)
#define SOC_UART_UARTFR_rxff_START      (6)
#define SOC_UART_UARTFR_rxff_END        (6)
#define SOC_UART_UARTFR_txfe_START      (7)
#define SOC_UART_UARTFR_txfe_END        (7)


/*****************************************************************************
 结构名    : SOC_UART_UARTLPR_UNION
 结构说明  : UARTLPR 寄存器结构定义。地址偏移量:0x020，初值:0x0000，宽度:16
 寄存器说明: IrDA低功耗计数器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  lrda     : 8;  /* bit[0-7] : 8bit低功耗分频值。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_UART_UARTLPR_UNION;
#endif
#define SOC_UART_UARTLPR_lrda_START      (0)
#define SOC_UART_UARTLPR_lrda_END        (7)


/*****************************************************************************
 结构名    : SOC_UART_UARTIBRD_UNION
 结构说明  : UARTIBRD 寄存器结构定义。地址偏移量:0x024，初值:0x0000，宽度:16
 寄存器说明: 波特率寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  baud_divint : 16; /* bit[0-15]: 波特率分频值的整数部分。 */
    } reg;
} SOC_UART_UARTIBRD_UNION;
#endif
#define SOC_UART_UARTIBRD_baud_divint_START  (0)
#define SOC_UART_UARTIBRD_baud_divint_END    (15)


/*****************************************************************************
 结构名    : SOC_UART_UARTFBRD_UNION
 结构说明  : UARTFBRD 寄存器结构定义。地址偏移量:0x028，初值:0x0000，宽度:16
 寄存器说明: 波特率寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  baud_divfrac : 6;  /* bit[0-5] : 波特率分频值的小数部分。 */
        unsigned short  reserved     : 10; /* bit[6-15]: 保留。 */
    } reg;
} SOC_UART_UARTFBRD_UNION;
#endif
#define SOC_UART_UARTFBRD_baud_divfrac_START  (0)
#define SOC_UART_UARTFBRD_baud_divfrac_END    (5)


/*****************************************************************************
 结构名    : SOC_UART_UARTLCR_H_UNION
 结构说明  : UARTLCR_H 寄存器结构定义。地址偏移量:0x02C，初值:0x0000，宽度:16
 寄存器说明: 线控（line control）寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  brk      : 1;  /* bit[0]   : Send break。
                                                     0：在完成当前字符的发送后，UART发送端不用连续输出低电平。
                                                     1：在完成当前字符的发送后，UART发送端连续输出低电平。要正确的执行Break命令，软件将该位置“1”的时间必须超过2个完整帧。
                                                     在正常使用中，该位必须清零。 */
        unsigned short  pen      : 1;  /* bit[1]   : 校验使能。
                                                     0：不作校验；
                                                     1：发送方向产生校验，接收方向检查校验。 */
        unsigned short  eps      : 1;  /* bit[2]   : 奇偶校验选择。
                                                     0：在发送和接收过程中生成奇校验或检查奇校验；
                                                     1：在发送和接收过程中生成偶校验或检查偶校验。
                                                     当pen为“0”时，本位不起作用。 */
        unsigned short  stp2     : 1;  /* bit[3]   : 选择2bit的停止位。
                                                     0：发送和接收FIFO禁止；
                                                     1：发送的帧尾有2bit的停止位。
                                                     接收逻辑在接收时不检查2bit的停止位。 */
        unsigned short  fen      : 1;  /* bit[4]   : FIFO使能。
                                                     0：发送和接收FIFO禁止；
                                                     1：发送和接收FIFO使能。 */
        unsigned short  wlen     : 2;  /* bit[5-6] : 发送和接收一帧中数据位的数目。
                                                     00：5bit；
                                                     01：6bit；
                                                     10：7bit；
                                                     11：8bit。 */
        unsigned short  sps      : 1;  /* bit[7]   : Stick parity选择。
                                                     0：bit[1]、bit[2]和bit[7]被置位；
                                                     1：bit[1]和bit[7]被置位，bit[2]为“0”。
                                                     当bit[1]、bit[2]和bit[7]都被清零，则Stick parity禁止。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_UART_UARTLCR_H_UNION;
#endif
#define SOC_UART_UARTLCR_H_brk_START       (0)
#define SOC_UART_UARTLCR_H_brk_END         (0)
#define SOC_UART_UARTLCR_H_pen_START       (1)
#define SOC_UART_UARTLCR_H_pen_END         (1)
#define SOC_UART_UARTLCR_H_eps_START       (2)
#define SOC_UART_UARTLCR_H_eps_END         (2)
#define SOC_UART_UARTLCR_H_stp2_START      (3)
#define SOC_UART_UARTLCR_H_stp2_END        (3)
#define SOC_UART_UARTLCR_H_fen_START       (4)
#define SOC_UART_UARTLCR_H_fen_END         (4)
#define SOC_UART_UARTLCR_H_wlen_START      (5)
#define SOC_UART_UARTLCR_H_wlen_END        (6)
#define SOC_UART_UARTLCR_H_sps_START       (7)
#define SOC_UART_UARTLCR_H_sps_END         (7)


/*****************************************************************************
 结构名    : SOC_UART_UARTCR_UNION
 结构说明  : UARTCR 寄存器结构定义。地址偏移量:0x030，初值:0x0300，宽度:16
 寄存器说明: 控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  uarten   : 1;  /* bit[0]    : 使能UART。
                                                      0：UART不使能。
                                                      1：UART使能。数据通过UART的信号或SIR的信号（取决于[SIREN]的设置）进行发送和接收。
                                                      如果在发送和接收过程中禁止UART，在正常停止之前结束当前字符的传送。 */
        unsigned short  siren    : 1;  /* bit[1]    : 使能IrDA SIR编码。
                                                      0：IrDA SIR编码不使能。
                                                      1：IrDA SIR编码使能，如果UART没有使能，则该位不起作用。
                                                      IrDA SIR编码使能，数据从nSIROUT发送，从SIRIN接收。UARTTXD保持marking state（置为“1”）。在UARTRXD上的信号和modem状态输入不起作用。
                                                      IrDA SIR编码禁止，nSIROUT保持为0（不发送光脉冲），SIRIN输入的信号不起作用。 */
        unsigned short  sirlp    : 1;  /* bit[2]    : SIR低功耗模式，该位选择IrDA的编码模式。
                                                      0：低电平比特以宽度为3/16比特周期的脉冲（高有效）进行发送；
                                                      1：低电平比特以宽度为3倍IrPBaud16周期的脉冲进行发送。
                                                      该位置“1”可以降低功耗，但也会缩短发送的距离。 */
        unsigned short  reserved_0: 4;  /* bit[3-6]  : 保留，勿修改。 */
        unsigned short  lbe      : 1;  /* bit[7]    : 使能Loop Back。
                                                      0：Loop Back不使能。
                                                      1：Loop Back使能。
                                                      复位时该位清零。 */
        unsigned short  txe      : 1;  /* bit[8]    : 使能UART发送。
                                                      0：不使能UART发送。
                                                      1：UART发送使能。UART或SIR（取决于[siren]的设置）开始发送数据。
                                                      在发送过程中如果UART被禁止，则当前字符的发送在正常停止之前结束。 */
        unsigned short  rxe      : 1;  /* bit[9]    : 使能UART接收。
                                                      0：不使能UART接收。
                                                      1：UART接收使能。UART或SIR（取决于[siren]的设置）开始接收数据。
                                                      在接收过程中如果UART被禁止，则当前字符的接收在正常停止之前结束。 */
        unsigned short  reserved_1: 1;  /* bit[10]   : 保留。 */
        unsigned short  rts      : 1;  /* bit[11]   : UART request to Send。
                                                      该位为UART Request to Send modem status信号（nUARTRTS）的取反，即该位为“1”时输出信号为“0”。 */
        unsigned short  reserved_2: 2;  /* bit[12-13]: 保留。 */
        unsigned short  rtsen    : 1;  /* bit[14]   : 使能RTS硬件流控。
                                                      0：不使能RTS硬件流控。
                                                      1：使能RTS硬件流控，只有当接收FIFO有空间时才请求接收数据。 */
        unsigned short  ctsen    : 1;  /* bit[15]   : 使能CTS硬件流控。
                                                      0：不使能CTS硬件流控。
                                                      1：使能CTS硬件流控，只有当nUARTCTS信号有效时才发送数据。 */
    } reg;
} SOC_UART_UARTCR_UNION;
#endif
#define SOC_UART_UARTCR_uarten_START    (0)
#define SOC_UART_UARTCR_uarten_END      (0)
#define SOC_UART_UARTCR_siren_START     (1)
#define SOC_UART_UARTCR_siren_END       (1)
#define SOC_UART_UARTCR_sirlp_START     (2)
#define SOC_UART_UARTCR_sirlp_END       (2)
#define SOC_UART_UARTCR_lbe_START       (7)
#define SOC_UART_UARTCR_lbe_END         (7)
#define SOC_UART_UARTCR_txe_START       (8)
#define SOC_UART_UARTCR_txe_END         (8)
#define SOC_UART_UARTCR_rxe_START       (9)
#define SOC_UART_UARTCR_rxe_END         (9)
#define SOC_UART_UARTCR_rts_START       (11)
#define SOC_UART_UARTCR_rts_END         (11)
#define SOC_UART_UARTCR_rtsen_START     (14)
#define SOC_UART_UARTCR_rtsen_END       (14)
#define SOC_UART_UARTCR_ctsen_START     (15)
#define SOC_UART_UARTCR_ctsen_END       (15)


/*****************************************************************************
 结构名    : SOC_UART_UARTIFLS_UNION
 结构说明  : UARTIFLS 寄存器结构定义。地址偏移量:0x034，初值:0x0092，宽度:16
 寄存器说明: 中断FIFO level选择寄存器。
            发送FIFO和接收FIFO的深度都是64。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txiflsel : 3;  /* bit[0-2] : 发送中断FIFO的level选择，发送中断的触发点如下。
                                                     000：发送FIFO开始?1/8 full；
                                                     001：发送FIFO开始?1/4 full；
                                                     011：发送FIFO开始?3/4 full；
                                                     100：发送FIFO开始?7/8 full；
                                                     101～111：保留。 */
        unsigned short  rxiflsel : 3;  /* bit[3-5] : 接收中断FIFO的level选择，接收中断的触发点如下。
                                                     000：接收FIFO开始|1/8 full；
                                                     001：接收FIFO开始|1/4 full；
                                                     010：接收FIFO开始|1/2 full；
                                                     011：接收FIFO开始|3/4 full；
                                                     100：接收FIFO开始|7/8 full；
                                                     101～111：保留。 */
        unsigned short  rtsflsel : 3;  /* bit[6-8] : RTS流控对应的接收FIFO的level选择，RTS的触发点如下。
                                                     000：接收FIFO开始≥1/8 full；
                                                     001：接收FIFO开始≥1/4 full；
                                                     010：接收FIFO开始≥1/2 full；
                                                     011：接收FIFO开始≥3/4 full；
                                                     100：接收FIFO开始≥7/8 full；
                                                     101：接收FIFO开始≥full-2；
                                                     110～111：保留。
                                                     注意：RTS流控水线配置不能低于接收中断水线；推荐配置为“101”。 */
        unsigned short  reserved : 7;  /* bit[9-15]: 保留。 */
    } reg;
} SOC_UART_UARTIFLS_UNION;
#endif
#define SOC_UART_UARTIFLS_txiflsel_START  (0)
#define SOC_UART_UARTIFLS_txiflsel_END    (2)
#define SOC_UART_UARTIFLS_rxiflsel_START  (3)
#define SOC_UART_UARTIFLS_rxiflsel_END    (5)
#define SOC_UART_UARTIFLS_rtsflsel_START  (6)
#define SOC_UART_UARTIFLS_rtsflsel_END    (8)


/*****************************************************************************
 结构名    : SOC_UART_UARTIMSC_UNION
 结构说明  : UARTIMSC 寄存器结构定义。地址偏移量:0x038，初值:0x0000，宽度:16
 寄存器说明: 中断屏蔽的设置/清除选择寄存器。
            值“0”表示中断被屏蔽，值“1”表示中断被启用。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : 保留。 */
        unsigned short  ctsmim   : 1;  /* bit[1]    : nUARTCTS modem中断的屏蔽状态。 */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : 保留。 */
        unsigned short  rxim     : 1;  /* bit[4]    : 接收中断的屏蔽状态。 */
        unsigned short  txim     : 1;  /* bit[5]    : 发送中断的屏蔽状态。 */
        unsigned short  rtim     : 1;  /* bit[6]    : 接收超时中断的屏蔽状态。 */
        unsigned short  feim     : 1;  /* bit[7]    : Framing错误中断的屏蔽状态。 */
        unsigned short  peim     : 1;  /* bit[8]    : Parity错误中断的屏蔽状态。 */
        unsigned short  beim     : 1;  /* bit[9]    : Break错误中断的屏蔽状态。 */
        unsigned short  oeim     : 1;  /* bit[10]   : Overrun错误中断的屏蔽状态。 */
        unsigned short  reserved_2: 5;  /* bit[11-15]: 保留。 */
    } reg;
} SOC_UART_UARTIMSC_UNION;
#endif
#define SOC_UART_UARTIMSC_ctsmim_START    (1)
#define SOC_UART_UARTIMSC_ctsmim_END      (1)
#define SOC_UART_UARTIMSC_rxim_START      (4)
#define SOC_UART_UARTIMSC_rxim_END        (4)
#define SOC_UART_UARTIMSC_txim_START      (5)
#define SOC_UART_UARTIMSC_txim_END        (5)
#define SOC_UART_UARTIMSC_rtim_START      (6)
#define SOC_UART_UARTIMSC_rtim_END        (6)
#define SOC_UART_UARTIMSC_feim_START      (7)
#define SOC_UART_UARTIMSC_feim_END        (7)
#define SOC_UART_UARTIMSC_peim_START      (8)
#define SOC_UART_UARTIMSC_peim_END        (8)
#define SOC_UART_UARTIMSC_beim_START      (9)
#define SOC_UART_UARTIMSC_beim_END        (9)
#define SOC_UART_UARTIMSC_oeim_START      (10)
#define SOC_UART_UARTIMSC_oeim_END        (10)


/*****************************************************************************
 结构名    : SOC_UART_UARTRIS_UNION
 结构说明  : UARTRIS 寄存器结构定义。地址偏移量:0x03C，初值:0x0000，宽度:16
 寄存器说明: 原始中断状态寄存器。
            复位时除了modem中断（bit[1]）外，其余bit全都清零。modem中断复位后状态不确定。值“0”表示该中断未触发，值“1”表示该中断已触发。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : 保留。 */
        unsigned short  ctsmris  : 1;  /* bit[1]    : 原始的nUARTCTS modem中断状态。 */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : 保留。 */
        unsigned short  rxris    : 1;  /* bit[4]    : 原始的接收中断状态。 */
        unsigned short  txris    : 1;  /* bit[5]    : 原始的发送中断状态。 */
        unsigned short  rtris    : 1;  /* bit[6]    : 原始的接收超时中断状态。 */
        unsigned short  feris    : 1;  /* bit[7]    : 原始的Framing错误中断状态。 */
        unsigned short  peris    : 1;  /* bit[8]    : 原始的Parity错误中断状态。 */
        unsigned short  beris    : 1;  /* bit[9]    : 原始的Break错误中断状态。 */
        unsigned short  oeris    : 1;  /* bit[10]   : 原始的Overrun错误中断状态。 */
        unsigned short  reserved_2: 5;  /* bit[11-15]: 保留。 */
    } reg;
} SOC_UART_UARTRIS_UNION;
#endif
#define SOC_UART_UARTRIS_ctsmris_START   (1)
#define SOC_UART_UARTRIS_ctsmris_END     (1)
#define SOC_UART_UARTRIS_rxris_START     (4)
#define SOC_UART_UARTRIS_rxris_END       (4)
#define SOC_UART_UARTRIS_txris_START     (5)
#define SOC_UART_UARTRIS_txris_END       (5)
#define SOC_UART_UARTRIS_rtris_START     (6)
#define SOC_UART_UARTRIS_rtris_END       (6)
#define SOC_UART_UARTRIS_feris_START     (7)
#define SOC_UART_UARTRIS_feris_END       (7)
#define SOC_UART_UARTRIS_peris_START     (8)
#define SOC_UART_UARTRIS_peris_END       (8)
#define SOC_UART_UARTRIS_beris_START     (9)
#define SOC_UART_UARTRIS_beris_END       (9)
#define SOC_UART_UARTRIS_oeris_START     (10)
#define SOC_UART_UARTRIS_oeris_END       (10)


/*****************************************************************************
 结构名    : SOC_UART_UARTMIS_UNION
 结构说明  : UARTMIS 寄存器结构定义。地址偏移量:0x040，初值:0x0000，宽度:16
 寄存器说明: 屏蔽后中断状态寄存器。
            复位时除了modem中断（bit[1]）外，其余bit全都清零。modem中断复位后状态不确定。值“0”表示该中断未触发，值“1”表示该中断已触发。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : 保留。 */
        unsigned short  ctsmmis  : 1;  /* bit[1]    : 屏蔽后的nUARTCTS modem中断状态。 */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : 保留。 */
        unsigned short  rxmis    : 1;  /* bit[4]    : 屏蔽后的接收中断状态。 */
        unsigned short  txmis    : 1;  /* bit[5]    : 屏蔽后的发送中断状态。 */
        unsigned short  rtmis    : 1;  /* bit[6]    : 屏蔽后的接收超时中断状态。 */
        unsigned short  femis    : 1;  /* bit[7]    : 屏蔽后的Framing错误中断状态。 */
        unsigned short  pemis    : 1;  /* bit[8]    : 屏蔽后的Parity错误中断状态。 */
        unsigned short  bemis    : 1;  /* bit[9]    : 屏蔽后的Break错误中断状态。 */
        unsigned short  oemis    : 1;  /* bit[10]   : 屏蔽后的Overrun错误中断状态。 */
        unsigned short  reserved_2: 5;  /* bit[11-15]: 保留。 */
    } reg;
} SOC_UART_UARTMIS_UNION;
#endif
#define SOC_UART_UARTMIS_ctsmmis_START   (1)
#define SOC_UART_UARTMIS_ctsmmis_END     (1)
#define SOC_UART_UARTMIS_rxmis_START     (4)
#define SOC_UART_UARTMIS_rxmis_END       (4)
#define SOC_UART_UARTMIS_txmis_START     (5)
#define SOC_UART_UARTMIS_txmis_END       (5)
#define SOC_UART_UARTMIS_rtmis_START     (6)
#define SOC_UART_UARTMIS_rtmis_END       (6)
#define SOC_UART_UARTMIS_femis_START     (7)
#define SOC_UART_UARTMIS_femis_END       (7)
#define SOC_UART_UARTMIS_pemis_START     (8)
#define SOC_UART_UARTMIS_pemis_END       (8)
#define SOC_UART_UARTMIS_bemis_START     (9)
#define SOC_UART_UARTMIS_bemis_END       (9)
#define SOC_UART_UARTMIS_oemis_START     (10)
#define SOC_UART_UARTMIS_oemis_END       (10)


/*****************************************************************************
 结构名    : SOC_UART_UARTICR_UNION
 结构说明  : UARTICR 寄存器结构定义。地址偏移量:0x044，初值:0x0000，宽度:16
 寄存器说明: 中断清除寄存器。
            写“1”清除相应中断，写“0”不起作用。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : 保留。 */
        unsigned short  ctsic    : 1;  /* bit[1]    : 清除nUARTCTS modem中断。 */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : 保留。 */
        unsigned short  rxic     : 1;  /* bit[4]    : 清除接收中断。 */
        unsigned short  txic     : 1;  /* bit[5]    : 清除发送中断。 */
        unsigned short  rtic     : 1;  /* bit[6]    : 清除接收超时中断。 */
        unsigned short  feic     : 1;  /* bit[7]    : 清除Framing错误中断。 */
        unsigned short  peic     : 1;  /* bit[8]    : 清除Parity错误中断。 */
        unsigned short  beic     : 1;  /* bit[9]    : 清除Break错误中断。 */
        unsigned short  oeic     : 1;  /* bit[10]   : 清除Overrun错误中断。 */
        unsigned short  reserved_2: 5;  /* bit[11-15]: 保留。 */
    } reg;
} SOC_UART_UARTICR_UNION;
#endif
#define SOC_UART_UARTICR_ctsic_START     (1)
#define SOC_UART_UARTICR_ctsic_END       (1)
#define SOC_UART_UARTICR_rxic_START      (4)
#define SOC_UART_UARTICR_rxic_END        (4)
#define SOC_UART_UARTICR_txic_START      (5)
#define SOC_UART_UARTICR_txic_END        (5)
#define SOC_UART_UARTICR_rtic_START      (6)
#define SOC_UART_UARTICR_rtic_END        (6)
#define SOC_UART_UARTICR_feic_START      (7)
#define SOC_UART_UARTICR_feic_END        (7)
#define SOC_UART_UARTICR_peic_START      (8)
#define SOC_UART_UARTICR_peic_END        (8)
#define SOC_UART_UARTICR_beic_START      (9)
#define SOC_UART_UARTICR_beic_END        (9)
#define SOC_UART_UARTICR_oeic_START      (10)
#define SOC_UART_UARTICR_oeic_END        (10)


/*****************************************************************************
 结构名    : SOC_UART_UARTDMACR_UNION
 结构说明  : UARTDMACR 寄存器结构定义。地址偏移量:0x048，初值:0x0000，宽度:16
 寄存器说明: DMA控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxdmae   : 1;  /* bit[0]   : 接收FIFO的DMA使能。
                                                     0：不使能接收FIFO的DMA。
                                                     1：使能接收FIFO的DMA。 */
        unsigned short  txdmae   : 1;  /* bit[1]   : 发送FIFO的DMA使能。
                                                     0：不使能发送FIFO的DMA。
                                                     1：使能发送FIFO的DMA。 */
        unsigned short  dmaonerr : 1;  /* bit[2]   : DMA on Error。
                                                     0：当UART错误中断有效时，DMA的请求输出（UARTRXDMASREQ或UARTRXDMABREQ）使能。
                                                     1：当UART错误中断有效时，DMA的请求输出（UARTRXDMASREQ或UARTRXDMABREQ）不使能。 */
        unsigned short  reserved : 13; /* bit[3-15]: 保留。 */
    } reg;
} SOC_UART_UARTDMACR_UNION;
#endif
#define SOC_UART_UARTDMACR_rxdmae_START    (0)
#define SOC_UART_UARTDMACR_rxdmae_END      (0)
#define SOC_UART_UARTDMACR_txdmae_START    (1)
#define SOC_UART_UARTDMACR_txdmae_END      (1)
#define SOC_UART_UARTDMACR_dmaonerr_START  (2)
#define SOC_UART_UARTDMACR_dmaonerr_END    (2)






/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_uart_interface.h */
