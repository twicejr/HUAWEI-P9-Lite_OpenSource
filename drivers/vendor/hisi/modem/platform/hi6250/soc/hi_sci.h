/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_SCI.h */
/* Version       : 2.0 */
/* Created       : 2013-02-08*/
/* Last Modified : */
/* Description   :  The C union definition file for the module SCI*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_SCI_H__
#define __HI_SCI_H__

/*
 * Project: hi
 * Module : SCI
 */

/********************************************************************************/
/*    SCI 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_SCI_SCI_DATA_OFFSET                            (0x0) /* SCI数据寄存器，用于发送或接收字符，是SCI与软件的数据接口。软件只有在配置SCI_CR1[mode]为1之后，才可对此寄存器进行写操作。当SCI_CR1[mode]为0时，软件会忽略对该寄存器的写操作，即不起作用。 */
#define    HI_SCI_SCI_CR0_OFFSET                             (0x4) /* SCI控制寄存器，用于控制时钟停止、奇偶校验、传输握手、传输位定义等功能。 */
#define    HI_SCI_SCI_CR1_OFFSET                             (0x8) /* SCI控制寄存器，用于控制同步/异步卡传输模式、发送接收模式、块超时、ATR超时等功能。 */
#define    HI_SCI_SCI_CR2_OFFSET                             (0xC) /* SCI控制寄存器。写该寄存器的相应位会触发SCI对卡的激活、释放或软复位操作。当SCI正处于释放卡的状态时，对该寄存器的写操作将被忽略。在其他时候，对SCI_CR2[finish]写1将使SCI立即发送卡释放序列。(CH)(CL)软件对该寄存器的写操作必须在合适的卡操作阶段进行。不合适的写操作将带来非预期的后果。(CL)只有当智能卡被激活之后，软件才能对卡进行软复位操作。 */
#define    HI_SCI_SCI_CLKICC_OFFSET                          (0x10) /* 智能卡时钟频率寄存器。该寄存器定义了外部智能卡时钟的分频因子。智能卡时钟频率的计算公式为：FSCI_CLK=(FREFCLK)/(clkicc+1)x2 ；其中，FSCI_CLK为时钟频率；FREFCLK为参考时钟频率，clkicc为SCI_CLKICC[clkicc]配置的值。 */
#define    HI_SCI_SCI_VALUE_OFFSET                           (0x14) /* ETU内SCI_BAUD周期数寄存器，用于计算ETU，可配置为5～255之间的任意值。ETU的计算公式为：Etu=(1+baud) x value；baud为SCI_BAUD[baud]配置的值；value为SCI_VALUE[value]配置的值。 */
#define    HI_SCI_SCI_BAUD_OFFSET                            (0x18) /* 波特率时钟分频值寄存器，用于计算ETU，可以配置为0x1～0xFFFF之间的任意值。请参见“SCI_VALUE”中ETU的计算公式。 */
#define    HI_SCI_SCI_TIDE_OFFSET                            (0x1C) /* 发送接收FIFO的溢出阈值寄存器。(NH)(NL)TXFIFO中的字符只有在成功发送后才会被移除。 */
#define    HI_SCI_SCI_DMACR_OFFSET                           (0x20) /* DMA控制寄存器，用于控制DMA发送和接收数据。 */
#define    HI_SCI_SCI_STABLE_OFFSET                          (0x24) /* 智能卡插入稳定时间寄存器。当智能卡检测信号SCI_DETECT信号有效后，需要稳定保持SCI_STABLE寄存器值对应的固定的时间TSTABLE。经过TSTABLE时间（单位为秒）后触发cardinintr中断，表明智能卡已正确插入。 */
#define    HI_SCI_SCI_ATIME_OFFSET                           (0x28) /* 智能卡激活时间寄存器。该寄存器的[atime]位用于指示卡复位和激活的3个阶段的持续时间。(NH)(NL)为满足卡复位的要求，SCI_ATIME[atime]至少为40000个接口卡时钟（SCI_CLK）周期。(NL)该参数也必须满足智能卡对电源稳定的要求。 */
#define    HI_SCI_SCI_DTIME_OFFSET                           (0x2C) /* 智能卡释放时间寄存器。该寄存器的{dtime]位用于指示卡释放的3个阶段的持续时间，单位为SCI参考时钟周期。 */
#define    HI_SCI_SCI_ATRSTIME_OFFSET                        (0x30) /* 等待开始接收ATR时间阈值寄存器。根据智能卡时钟定义了从智能卡复位结束到开始接收ATR第一个字符的时间阈值。ATR等待开始接收超时后会触发atrstoutintr中断，将SCI_RIS[atrstoutim]置1。(NH)SCI_ATRSTIME[atrstime]必须软件初始化为40000个SCI_CLK接口卡时钟周期。 */
#define    HI_SCI_SCI_ATRDTIME_OFFSET                        (0x34) /* 接收ATR时间阈值寄存器。SCI在接收ATR过程中（从第一个ATR字符开始接收到最后一个ATR字符接收结束）如果超过该寄存器所定义的时间（以ETU为单位），会触发中断，将SCI_RIS[atrdtoutris]置1。(NH)(NL)在使用该寄存器之前必须首先配置SCI_CR1[atrden]为1，以使能超时计数机制。(NL)根据协议，该寄存器建议配置为19200个ETU，即0x4B00。 */
#define    HI_SCI_SCI_STOPTIME_OFFSET                        (0x38) /* 时钟停止时间寄存器。当启动时钟停止时，经过SCI_STOPTIME所定义的时间（单位为SCI接口卡时钟SCI_CLK周期）后，智能卡时钟无效，并触发中断，将SCI_RIS[clkstpris]置1。(NH)根据协议，该值最小为1860个SCI时钟周期，即SCI_STOPTIME[stoptime]需要配置为0x744。 */
#define    HI_SCI_SCI_STARTTIME_OFFSET                       (0x3C) /* 智能卡时钟恢复时间寄存器。当启动时钟恢复时，经过SCI_STARTTIME所定义的时间（单位为SCI接口卡时钟SCI_CLK周期）后，SCI与智能卡才能进行数据传输，并触发中断，将SCI_RIS[clkactris]置1。(NH)根据协议，该值最小应为700个SCI时钟周期，即SCI_STARTTIME[starttimr]至少需要配置为0x2BC。 */
#define    HI_SCI_SCI_RETRY_OFFSET                           (0x40) /* 发送接收重试次数寄存器。该寄存器定义了发送或接收允许重传的次数，具体内容为：(I)当SCI_CR0[txnak]使能时，SCI检测接收方是否标识校验错误，SCI_RETRY[rxretry]定义出现校验错误后重新传输的最大次数。超出将触发txerrintr中断，将SCI_RIS[txerrris]置1。(I)当SCI_CR0[rxnak]使能时，SCI检测收到的数据是否出现校验错误，SCI_RETRY[txretry]定义出现校验错误后重新传输的最大次数。如果超出该次数仍然接收错误，将SCI_DATA[parity]置1。 */
#define    HI_SCI_SCI_CHTIMELS_OFFSET                        (0x44) /* 接收字符间隔超时阈值低16位寄存器。SCI_CHTIME寄存器定义从卡接收到的两个连续字符的起始沿之间允许的最大时间间隔（以ETU为单位）。如果接收到的字符间隔超时会触发chtoutintr中断，将SCI_RIS[chtoutris]置1。(CH)SCI_CHTIME寄存器是由低16位寄存器SCI_CHTIMELS和高16位寄存器SCI_CHTIMEMS组成。当软件写SCI_CHTIMEMS时，SCI_CHTIME不会立即生效，而写SCI_CHTIMELS时SCI_CHTIME才会生效，因此配置SCI_CHTIME必须先配置高16位，再配置低16位。 */
#define    HI_SCI_SCI_CHTIMEMS_OFFSET                        (0x48) /* 接收字符间隔超时阈值高16位寄存器。 */
#define    HI_SCI_SCI_BLKTIMELS_OFFSET                       (0x4C) /* 接收块间隔超时阈值低16位寄存器。SCI_BLKTIME定义接收块允许的最大时间间隔（以ETU为单位），该时间间隔的起始时刻是最后一个发送到卡的字符的起始沿，结束是第一个从卡返回的接收字符时刻。如果超时会触发blktoutintr中断，将SCI_RIS[blkoutim]置1。(CH)SCI_BLKTIME寄存器是由低16位寄存器SCI_BLKTIMELS和高16位寄存器SCI_BLKTIMEMS组成。当软件写SCI_BLKTIMEMS时，SCI_BLKTIME不会立即生效，写SCI_BLKTIMELS时SCI_BLKTIME才会生效，因此配置SCI_BLKTIME必须先配置高16位，再配置低16位。 */
#define    HI_SCI_SCI_BLKTIMEMS_OFFSET                       (0x50) /* 接收块间隔超时阈值高16位寄存器。 */
#define    HI_SCI_SCI_CHGUARD_OFFSET                         (0x54) /* 字符间保护时间间隔寄存器。该寄存器定义当SCI向卡连续传输字符时，两个连续字符起始沿之间最小间隔的额外保护时间（以ETU为单位）。根据协议中定义的全局接口字节TC1（从ATR序列中得到）决定。 */
#define    HI_SCI_SCI_BLKGUARD_OFFSET                        (0x58) /* 块间保护时间间隔寄存器。当两个连续字符的传输方向相反时，其起始沿之间的时间间隔为SCI_BLKGUARD。 */
#define    HI_SCI_SCI_RXTIME_OFFSET                          (0x5C) /* 接收FIFO读超时阈值寄存器。当接收FIFO中有字符且超出SCI_RXTIME所定义的时间仍然没有被读出，则触发接收读超时中断scirtout，SCI_RIS[rtoutris]将置1。(CH)正常使用接收FIFO读超时中断功能时，SCI_RXTIME[rxtime]不能为0x0000。 */
#define    HI_SCI_SCI_FIFOSTATUS_OFFSET                      (0x60) /* FIFO状态寄存器。 */
#define    HI_SCI_SCI_TXCOUNT_OFFSET                         (0x64) /* 发送FIFO数据个数寄存器。(NH)(NL)读该寄存器返回发送FIFO中字符的个数（包括了正在发送的字符）。(NL)当发送字符到卡出现错误（T0协议），并且重传次数超过了允许的值（在SCI_RETRY中定义），会触发txerr中断，将SCI_RIS[txerrris]置1。此时在进行下一次传输之前，发送FIFO必须被清空（写该寄存器）。 */
#define    HI_SCI_SCI_RXCOUNT_OFFSET                         (0x68) /* 接收FIFO数据个数寄存器。 */
#define    HI_SCI_SCI_IMSC_OFFSET                            (0x6C) /* 中断屏蔽寄存器。Bit值为0表示屏蔽，为1表示不屏蔽。 */
#define    HI_SCI_SCI_RIS_OFFSET                             (0x70) /* 原始中断寄存器。该寄存器是在中断屏蔽之前的原始中断。Bit值为0表示无中断，为1表示有中断。 */
#define    HI_SCI_SCI_MIS_OFFSET                             (0x74) /* 屏蔽后中断寄存器。该寄存器是初始中断经过屏蔽后的结果。Bit值为0表示无中断，为1表示有中断。 */
#define    HI_SCI_SCI_ICR_OFFSET                             (0x78) /* 中断清除寄存器。Bit值为0表示不清除中断，为1表示清除中断。 */
#define    HI_SCI_SCI_SYNCACT_OFFSET                         (0x7C) /* 同步模式激活寄存器。该寄存器用于同步模式下数据使能、时钟使能、复位和电源控制等，并提供状态寄存器，相应的状态位在激活、释放、热复位过程中自动更新。 */
#define    HI_SCI_SCI_SYNCTX_OFFSET                          (0x80) /* 同步模式发送时钟和数据流寄存器。该寄存器用于控制同步模式下发送时钟和数据。 */
#define    HI_SCI_SCI_SYNCRX_OFFSET                          (0x84) /* 同步模式接收时钟和数据流寄存器。该寄存器用于控制同步模式下接收时钟和数据。 */

#endif // __HI_SCI_H__

