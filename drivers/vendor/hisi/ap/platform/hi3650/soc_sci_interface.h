/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_sci_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-23 11:27:34
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月23日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_SCI.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_SCI_INTERFACE_H__
#define __SOC_SCI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) SCI0
 ****************************************************************************/
/* 寄存器说明：SCI数据寄存器，用于发送或接收字符，是SCI与软件的数据接口。
            软件只有在配置SCI_CR1[mode]为1之后，才可对此寄存器进行写操作。当SCI_CR1[mode]为0时，软件会忽略对该寄存器的写操作，即不起作用。
   位域定义UNION结构:  SOC_SCI_DATA_UNION */
#define SOC_SCI_DATA_ADDR(base)                       ((base) + (0x0000))

/* 寄存器说明：SCI控制寄存器，用于控制时钟停止、奇偶校验、传输握手、传输位定义等功能。
   位域定义UNION结构:  SOC_SCI_CR0_UNION */
#define SOC_SCI_CR0_ADDR(base)                        ((base) + (0x0004))

/* 寄存器说明：SCI控制寄存器，用于控制同步/异步卡传输模式、发送接收模式、块超时、ATR超时等功能。
   位域定义UNION结构:  SOC_SCI_CR1_UNION */
#define SOC_SCI_CR1_ADDR(base)                        ((base) + (0x0008))

/* 寄存器说明：SCI控制寄存器。写该寄存器的相应位会触发SCI对卡的激活、释放或软复位操作。当SCI正处于释放卡的状态时，对该寄存器的写操作将被忽略。在其他时候，对SCI_CR2[finish]写1将使SCI立即发送卡释放序列。
            (CH)
            (CL)软件对该寄存器的写操作必须在合适的卡操作阶段进行。不合适的写操作将带来非预期的后果。
            (CL)只有当智能卡被激活之后，软件才能对卡进行软复位操作。
   位域定义UNION结构:  SOC_SCI_CR2_UNION */
#define SOC_SCI_CR2_ADDR(base)                        ((base) + (0x000C))

/* 寄存器说明：智能卡时钟频率寄存器。该寄存器定义了外部智能卡时钟的分频因子。智能卡时钟频率的计算公式为：FSCI_CLK=(FREFCLK)/(clkicc+1)x2 ；其中，FSCI_CLK为时钟频率；FREFCLK为参考时钟频率，clkicc为SCI_CLKICC[clkicc]配置的值。
   位域定义UNION结构:  SOC_SCI_CLKICC_UNION */
#define SOC_SCI_CLKICC_ADDR(base)                     ((base) + (0x0010))

/* 寄存器说明：ETU内SCI_BAUD周期数寄存器，用于计算ETU，可配置为5～255之间的任意值。ETU的计算公式为：Etu=(1+baud) x value；baud为SCI_BAUD[baud]配置的值；value为SCI_VALUE[value]配置的值。
   位域定义UNION结构:  SOC_SCI_VALUE_UNION */
#define SOC_SCI_VALUE_ADDR(base)                      ((base) + (0x0014))

/* 寄存器说明：波特率时钟分频值寄存器，用于计算ETU，可以配置为0x1～0xFFFF之间的任意值。请参见“SCI_VALUE”中ETU的计算公式。
   位域定义UNION结构:  SOC_SCI_BAUD_UNION */
#define SOC_SCI_BAUD_ADDR(base)                       ((base) + (0x0018))

/* 寄存器说明：发送接收FIFO的溢出阈值寄存器。
            (NH)
            (NL)TXFIFO中的字符只有在成功发送后才会被移除。
   位域定义UNION结构:  SOC_SCI_TIDE_UNION */
#define SOC_SCI_TIDE_ADDR(base)                       ((base) + (0x001C))

/* 寄存器说明：DMA控制寄存器，用于控制DMA发送和接收数据。
   位域定义UNION结构:  SOC_SCI_DMACR_UNION */
#define SOC_SCI_DMACR_ADDR(base)                      ((base) + (0x0020))

/* 寄存器说明：智能卡插入稳定时间寄存器。当智能卡检测信号SCI_DETECT信号有效后，需要稳定保持SCI_STABLE寄存器值对应的固定的时间TSTABLE。经过TSTABLE时间（单位为秒）后触发cardinintr中断，表明智能卡已正确插入。
   位域定义UNION结构:  SOC_SCI_STABLE_UNION */
#define SOC_SCI_STABLE_ADDR(base)                     ((base) + (0x0024))

/* 寄存器说明：智能卡激活时间寄存器。该寄存器的[atime]位用于指示卡复位和激活的3个阶段的持续时间。
            (NH)
            (NL)为满足卡复位的要求，SCI_ATIME[atime]至少为40000个接口卡时钟（SCI_CLK）周期。
            (NL)该参数也必须满足智能卡对电源稳定的要求。
   位域定义UNION结构:  SOC_SCI_ATIME_UNION */
#define SOC_SCI_ATIME_ADDR(base)                      ((base) + (0x0028))

/* 寄存器说明：智能卡释放时间寄存器。该寄存器的{dtime]位用于指示卡释放的3个阶段的持续时间，单位为SCI参考时钟周期。
   位域定义UNION结构:  SOC_SCI_DTIME_UNION */
#define SOC_SCI_DTIME_ADDR(base)                      ((base) + (0x002C))

/* 寄存器说明：等待开始接收ATR时间阈值寄存器。根据智能卡时钟定义了从智能卡复位结束到开始接收ATR第一个字符的时间阈值。ATR等待开始接收超时后会触发atrstoutintr中断，将SCI_RIS[atrstoutim]置1。
            (NH)SCI_ATRSTIME[atrstime]必须软件初始化为40000个SCI_CLK接口卡时钟周期。
   位域定义UNION结构:  SOC_SCI_ATRSTIME_UNION */
#define SOC_SCI_ATRSTIME_ADDR(base)                   ((base) + (0x0030))

/* 寄存器说明：接收ATR时间阈值寄存器。SCI在接收ATR过程中（从第一个ATR字符开始接收到最后一个ATR字符接收结束）如果超过该寄存器所定义的时间（以ETU为单位），会触发中断，将SCI_RIS[atrdtoutris]置1。
            (NH)
            (NL)在使用该寄存器之前必须首先配置SCI_CR1[atrden]为1，以使能超时计数机制。
            (NL)根据协议，该寄存器建议配置为19200个ETU，即0x4B00。
   位域定义UNION结构:  SOC_SCI_ATRDTIME_UNION */
#define SOC_SCI_ATRDTIME_ADDR(base)                   ((base) + (0x0034))

/* 寄存器说明：时钟停止时间寄存器。当启动时钟停止时，经过SCI_STOPTIME所定义的时间（单位为SCI接口卡时钟SCI_CLK周期）后，智能卡时钟无效，并触发中断，将SCI_RIS[clkstpris]置1。
            (NH)根据协议，该值最小为1860个SCI时钟周期，即SCI_STOPTIME[stoptime]需要配置为0x744。
   位域定义UNION结构:  SOC_SCI_STOPTIME_UNION */
#define SOC_SCI_STOPTIME_ADDR(base)                   ((base) + (0x0038))

/* 寄存器说明：智能卡时钟恢复时间寄存器。当启动时钟恢复时，经过SCI_STARTTIME所定义的时间（单位为SCI接口卡时钟SCI_CLK周期）后，SCI与智能卡才能进行数据传输，并触发中断，将SCI_RIS[clkactris]置1。
            (NH)根据协议，该值最小应为700个SCI时钟周期，即SCI_STARTTIME[starttimr]至少需要配置为0x2BC。
   位域定义UNION结构:  SOC_SCI_STARTTIME_UNION */
#define SOC_SCI_STARTTIME_ADDR(base)                  ((base) + (0x003C))

/* 寄存器说明：发送接收重试次数寄存器。该寄存器定义了发送或接收允许重传的次数，具体内容为：
            (I)当SCI_CR0[txnak]使能时，SCI检测接收方是否标识校验错误，SCI_RETRY[rxretry]定义出现校验错误后重新传输的最大次数。超出将触发txerrintr中断，将SCI_RIS[txerrris]置1。
            (I)当SCI_CR0[rxnak]使能时，SCI检测收到的数据是否出现校验错误，SCI_RETRY[txretry]定义出现校验错误后重新传输的最大次数。如果超出该次数仍然接收错误，将SCI_DATA[parity]置1。
   位域定义UNION结构:  SOC_SCI_RETRY_UNION */
#define SOC_SCI_RETRY_ADDR(base)                      ((base) + (0x0040))

/* 寄存器说明：接收字符间隔超时阈值低16位寄存器。
            SCI_CHTIME寄存器定义从卡接收到的两个连续字符的起始沿之间允许的最大时间间隔（以ETU为单位）。如果接收到的字符间隔超时会触发chtoutintr中断，将SCI_RIS[chtoutris]置1。
            (CH)SCI_CHTIME寄存器是由低16位寄存器SCI_CHTIMELS和高16位寄存器SCI_CHTIMEMS组成。当软件写SCI_CHTIMEMS时，SCI_CHTIME不会立即生效，而写SCI_CHTIMELS时SCI_CHTIME才会生效，因此配置SCI_CHTIME必须先配置高16位，再配置低16位。
   位域定义UNION结构:  SOC_SCI_CHTIMELS_UNION */
#define SOC_SCI_CHTIMELS_ADDR(base)                   ((base) + (0x0044))

/* 寄存器说明：接收字符间隔超时阈值高16位寄存器。
   位域定义UNION结构:  SOC_SCI_CHTIMEMS_UNION */
#define SOC_SCI_CHTIMEMS_ADDR(base)                   ((base) + (0x0048))

/* 寄存器说明：接收块间隔超时阈值低16位寄存器。
            SCI_BLKTIME定义接收块允许的最大时间间隔（以ETU为单位），该时间间隔的起始时刻是最后一个发送到卡的字符的起始沿，结束是第一个从卡返回的接收字符时刻。如果超时会触发blktoutintr中断，将SCI_RIS[blkoutim]置1。
            (CH)SCI_BLKTIME寄存器是由低16位寄存器SCI_BLKTIMELS和高16位寄存器SCI_BLKTIMEMS组成。当软件写SCI_BLKTIMEMS时，SCI_BLKTIME不会立即生效，写SCI_BLKTIMELS时SCI_BLKTIME才会生效，因此配置SCI_BLKTIME必须先配置高16位，再配置低16位。
   位域定义UNION结构:  SOC_SCI_BLKTIMELS_UNION */
#define SOC_SCI_BLKTIMELS_ADDR(base)                  ((base) + (0x004C))

/* 寄存器说明：接收块间隔超时阈值高16位寄存器。
   位域定义UNION结构:  SOC_SCI_BLKTIMEMS_UNION */
#define SOC_SCI_BLKTIMEMS_ADDR(base)                  ((base) + (0x0050))

/* 寄存器说明：字符间保护时间间隔寄存器。该寄存器定义当SCI向卡连续传输字符时，两个连续字符起始沿之间最小间隔的额外保护时间（以ETU为单位）。根据协议中定义的全局接口字节TC1（从ATR序列中得到）决定。
   位域定义UNION结构:  SOC_SCI_CHGUARD_UNION */
#define SOC_SCI_CHGUARD_ADDR(base)                    ((base) + (0x0054))

/* 寄存器说明：块间保护时间间隔寄存器。当两个连续字符的传输方向相反时，其起始沿之间的时间间隔为SCI_BLKGUARD。
   位域定义UNION结构:  SOC_SCI_BLKGUARD_UNION */
#define SOC_SCI_BLKGUARD_ADDR(base)                   ((base) + (0x0058))

/* 寄存器说明：接收FIFO读超时阈值寄存器。当接收FIFO中有字符且超出SCI_RXTIME所定义的时间仍然没有被读出，则触发接收读超时中断scirtout，SCI_RIS[rtoutris]将置1。
            (CH)正常使用接收FIFO读超时中断功能时，SCI_RXTIME[rxtime]不能为0x0000。
   位域定义UNION结构:  SOC_SCI_RXTIME_UNION */
#define SOC_SCI_RXTIME_ADDR(base)                     ((base) + (0x005C))

/* 寄存器说明：FIFO状态寄存器。
   位域定义UNION结构:  SOC_SCI_FIFOSTATUS_UNION */
#define SOC_SCI_FIFOSTATUS_ADDR(base)                 ((base) + (0x0060))

/* 寄存器说明：发送FIFO数据个数寄存器。
            (NH)
            (NL)读该寄存器返回发送FIFO中字符的个数（包括了正在发送的字符）。
            (NL)当发送字符到卡出现错误（T0协议），并且重传次数超过了允许的值（在SCI_RETRY中定义），会触发txerr中断，将SCI_RIS[txerrris]置1。此时在进行下一次传输之前，发送FIFO必须被清空（写该寄存器）。
   位域定义UNION结构:  SOC_SCI_TXCOUNT_UNION */
#define SOC_SCI_TXCOUNT_ADDR(base)                    ((base) + (0x0064))

/* 寄存器说明：接收FIFO数据个数寄存器。
   位域定义UNION结构:  SOC_SCI_RXCOUNT_UNION */
#define SOC_SCI_RXCOUNT_ADDR(base)                    ((base) + (0x0068))

/* 寄存器说明：中断屏蔽寄存器。Bit值为0表示屏蔽，为1表示不屏蔽。
   位域定义UNION结构:  SOC_SCI_IMSC_UNION */
#define SOC_SCI_IMSC_ADDR(base)                       ((base) + (0x006C))

/* 寄存器说明：原始中断寄存器。该寄存器是在中断屏蔽之前的原始中断。Bit值为0表示无中断，为1表示有中断。
   位域定义UNION结构:  SOC_SCI_RIS_UNION */
#define SOC_SCI_RIS_ADDR(base)                        ((base) + (0x0070))

/* 寄存器说明：屏蔽后中断寄存器。该寄存器是初始中断经过屏蔽后的结果。Bit值为0表示无中断，为1表示有中断。
   位域定义UNION结构:  SOC_SCI_MIS_UNION */
#define SOC_SCI_MIS_ADDR(base)                        ((base) + (0x0074))

/* 寄存器说明：中断清除寄存器。Bit值为0表示不清除中断，为1表示清除中断。
   位域定义UNION结构:  SOC_SCI_ICR_UNION */
#define SOC_SCI_ICR_ADDR(base)                        ((base) + (0x0078))

/* 寄存器说明：同步模式激活寄存器。该寄存器用于同步模式下数据使能、时钟使能、复位和电源控制等，并提供状态寄存器，相应的状态位在激活、释放、热复位过程中自动更新。
   位域定义UNION结构:  SOC_SCI_SYNCACT_UNION */
#define SOC_SCI_SYNCACT_ADDR(base)                    ((base) + (0x007C))

/* 寄存器说明：同步模式发送时钟和数据流寄存器。该寄存器用于控制同步模式下发送时钟和数据。
   位域定义UNION结构:  SOC_SCI_SYNCTX_UNION */
#define SOC_SCI_SYNCTX_ADDR(base)                     ((base) + (0x0080))

/* 寄存器说明：同步模式接收时钟和数据流寄存器。该寄存器用于控制同步模式下接收时钟和数据。
   位域定义UNION结构:  SOC_SCI_SYNCRX_UNION */
#define SOC_SCI_SYNCRX_ADDR(base)                     ((base) + (0x0084))





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
                     (1/1) SCI0
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_SCI_DATA_UNION
 结构说明  : DATA 寄存器结构定义。地址偏移量:0x0000，初值:0x0000，宽度:16
 寄存器说明: SCI数据寄存器，用于发送或接收字符，是SCI与软件的数据接口。
            软件只有在配置SCI_CR1[mode]为1之后，才可对此寄存器进行写操作。当SCI_CR1[mode]为0时，软件会忽略对该寄存器的写操作，即不起作用。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  scidata  : 8;  /* bit[0-7] : 8bit字符读写数据。 */
        unsigned short  parity   : 1;  /* bit[8]   : 奇偶校验错误标志位。发送时该位随数据一起发送，接收时软件根据该位判断奇偶校验是否正确。
                                                     0：正确；
                                                     1：错误。 */
        unsigned short  reserved : 7;  /* bit[9-15]: 保留。 */
    } reg;
} SOC_SCI_DATA_UNION;
#endif
#define SOC_SCI_DATA_scidata_START   (0)
#define SOC_SCI_DATA_scidata_END     (7)
#define SOC_SCI_DATA_parity_START    (8)
#define SOC_SCI_DATA_parity_END      (8)


/*****************************************************************************
 结构名    : SOC_SCI_CR0_UNION
 结构说明  : CR0 寄存器结构定义。地址偏移量:0x0004，初值:0x0000，宽度:16
 寄存器说明: SCI控制寄存器，用于控制时钟停止、奇偶校验、传输握手、传输位定义等功能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  sense    : 1;  /* bit[0]   : 数据比特和校验比特检测相位控制。
                                                     0：直接检测；
                                                     1：取反后检测IO线上的数据和校验位。 */
        unsigned short  order    : 1;  /* bit[1]   : 字符的高低位顺序。
                                                     0：起始位（start bit）后先发送/接收最低位；
                                                     1：起始位（start bit）后先发送/接收最高位。 */
        unsigned short  txparity : 1;  /* bit[2]   : 发送模式下的校验方式控制。
                                                     0：偶校验；
                                                     1：奇校验。 */
        unsigned short  txnak    : 1;  /* bit[3]   : 在发送模式下的行为控制。
                                                     0：SCI不检测接收方是否将I/O线拉低；
                                                     1：SCI检测接收方是否将I/O线拉低指示校验错误。 */
        unsigned short  rxparity : 1;  /* bit[4]   : 接收模式下的校验方式控制。
                                                     0：偶校验；
                                                     1：奇校验。 */
        unsigned short  rxnak    : 1;  /* bit[5]   : 在接收模式下的行为控制。
                                                     0：检测到奇偶校验错误时，I/O线不拉低；
                                                     1：检测到奇偶校验错误时，I/O线拉低。 */
        unsigned short  clkdis   : 1;  /* bit[6]   : 时钟的启动和停止控制位。
                                                     0：启动时钟；
                                                     1：停止时钟。 */
        unsigned short  clkval   : 1;  /* bit[7]   : 智能卡时钟保持状态控制。
                                                     0：inactive时，时钟保持低电平；1：inactive时，时钟保持高电平。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_SCI_CR0_UNION;
#endif
#define SOC_SCI_CR0_sense_START     (0)
#define SOC_SCI_CR0_sense_END       (0)
#define SOC_SCI_CR0_order_START     (1)
#define SOC_SCI_CR0_order_END       (1)
#define SOC_SCI_CR0_txparity_START  (2)
#define SOC_SCI_CR0_txparity_END    (2)
#define SOC_SCI_CR0_txnak_START     (3)
#define SOC_SCI_CR0_txnak_END       (3)
#define SOC_SCI_CR0_rxparity_START  (4)
#define SOC_SCI_CR0_rxparity_END    (4)
#define SOC_SCI_CR0_rxnak_START     (5)
#define SOC_SCI_CR0_rxnak_END       (5)
#define SOC_SCI_CR0_clkdis_START    (6)
#define SOC_SCI_CR0_clkdis_END      (6)
#define SOC_SCI_CR0_clkval_START    (7)
#define SOC_SCI_CR0_clkval_END      (7)


/*****************************************************************************
 结构名    : SOC_SCI_CR1_UNION
 结构说明  : CR1 寄存器结构定义。地址偏移量:0x0008，初值:0x0000，宽度:16
 寄存器说明: SCI控制寄存器，用于控制同步/异步卡传输模式、发送接收模式、块超时、ATR超时等功能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atrden   : 1;  /* bit[0]   : ATR timeout使能控制。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  blken    : 1;  /* bit[1]   : Block timeout使能控制。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  mode     : 1;  /* bit[2]   : 发送/接收模式配置。
                                                     0：接收模式；
                                                     1：发送模式。 */
        unsigned short  clkz1    : 1;  /* bit[3]   : SCICLK信号配置模式选择信号。
                                                     1：SCICLK信号配置为下拉（open drain）；
                                                     0：SCICLK信号配置为buffer output。 */
        unsigned short  bgten    : 1;  /* bit[4]   : Block guard timer使能控制。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  exdbnce  : 1;  /* bit[5]   : 卡去抖旁路使能。使用方法请参见SCI_STABLE的说明。
                                                     0：使用整个内部debounce time；
                                                     1：旁路内部debounce time的不可编程部分。 */
        unsigned short  synccard : 1;  /* bit[6]   : 设置同步/异步卡操作模式。
                                                     0：异步模式；
                                                     1：同步模式。 */
        unsigned short  reserved : 9;  /* bit[7-15]: 保留。 */
    } reg;
} SOC_SCI_CR1_UNION;
#endif
#define SOC_SCI_CR1_atrden_START    (0)
#define SOC_SCI_CR1_atrden_END      (0)
#define SOC_SCI_CR1_blken_START     (1)
#define SOC_SCI_CR1_blken_END       (1)
#define SOC_SCI_CR1_mode_START      (2)
#define SOC_SCI_CR1_mode_END        (2)
#define SOC_SCI_CR1_clkz1_START     (3)
#define SOC_SCI_CR1_clkz1_END       (3)
#define SOC_SCI_CR1_bgten_START     (4)
#define SOC_SCI_CR1_bgten_END       (4)
#define SOC_SCI_CR1_exdbnce_START   (5)
#define SOC_SCI_CR1_exdbnce_END     (5)
#define SOC_SCI_CR1_synccard_START  (6)
#define SOC_SCI_CR1_synccard_END    (6)


/*****************************************************************************
 结构名    : SOC_SCI_CR2_UNION
 结构说明  : CR2 寄存器结构定义。地址偏移量:0x000C，初值:0x0000，宽度:16
 寄存器说明: SCI控制寄存器。写该寄存器的相应位会触发SCI对卡的激活、释放或软复位操作。当SCI正处于释放卡的状态时，对该寄存器的写操作将被忽略。在其他时候，对SCI_CR2[finish]写1将使SCI立即发送卡释放序列。
            (CH)
            (CL)软件对该寄存器的写操作必须在合适的卡操作阶段进行。不合适的写操作将带来非预期的后果。
            (CL)只有当智能卡被激活之后，软件才能对卡进行软复位操作。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  startup  : 1;  /* bit[0]   : 激活智能卡操作。
                                                     0：无效；
                                                     1：激活智能卡。
                                                     <B>注意：仅在智能卡被读卡设备检测到后该位可写，否则写无效。</B> */
        unsigned short  finish   : 1;  /* bit[1]   : 释放智能卡操作。
                                                     0：无效；
                                                     1：释放智能卡。
                                                     <B>注意：仅在智能卡被读卡设备检测到后该位可写，否则写无效。</B> */
        unsigned short  wreset   : 1;  /* bit[2]   : 对卡的软复位操作。
                                                     0：无效；
                                                     1：对智能卡进行软复位操作。
                                                     <B>注意：仅在激活序列完成后该位可写，否则写无效。</B> */
        unsigned short  reserved : 13; /* bit[3-15]: 保留。 */
    } reg;
} SOC_SCI_CR2_UNION;
#endif
#define SOC_SCI_CR2_startup_START   (0)
#define SOC_SCI_CR2_startup_END     (0)
#define SOC_SCI_CR2_finish_START    (1)
#define SOC_SCI_CR2_finish_END      (1)
#define SOC_SCI_CR2_wreset_START    (2)
#define SOC_SCI_CR2_wreset_END      (2)


/*****************************************************************************
 结构名    : SOC_SCI_CLKICC_UNION
 结构说明  : CLKICC 寄存器结构定义。地址偏移量:0x0010，初值:0x0000，宽度:16
 寄存器说明: 智能卡时钟频率寄存器。该寄存器定义了外部智能卡时钟的分频因子。智能卡时钟频率的计算公式为：FSCI_CLK=(FREFCLK)/(clkicc+1)x2 ；其中，FSCI_CLK为时钟频率；FREFCLK为参考时钟频率，clkicc为SCI_CLKICC[clkicc]配置的值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clkicc   : 8;  /* bit[0-7] : 智能卡时钟的分频系数（由参考时钟分频得到），可配置为0～255。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_SCI_CLKICC_UNION;
#endif
#define SOC_SCI_CLKICC_clkicc_START    (0)
#define SOC_SCI_CLKICC_clkicc_END      (7)


/*****************************************************************************
 结构名    : SOC_SCI_VALUE_UNION
 结构说明  : VALUE 寄存器结构定义。地址偏移量:0x0014，初值:0x0000，宽度:16
 寄存器说明: ETU内SCI_BAUD周期数寄存器，用于计算ETU，可配置为5～255之间的任意值。ETU的计算公式为：Etu=(1+baud) x value；baud为SCI_BAUD[baud]配置的值；value为SCI_VALUE[value]配置的值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  value    : 8;  /* bit[0-7] : 每个ETU（Elementary Time Unit）的SCIBAUD的周期数目。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_SCI_VALUE_UNION;
#endif
#define SOC_SCI_VALUE_value_START     (0)
#define SOC_SCI_VALUE_value_END       (7)


/*****************************************************************************
 结构名    : SOC_SCI_BAUD_UNION
 结构说明  : BAUD 寄存器结构定义。地址偏移量:0x0018，初值:0x0000，宽度:16
 寄存器说明: 波特率时钟分频值寄存器，用于计算ETU，可以配置为0x1～0xFFFF之间的任意值。请参见“SCI_VALUE”中ETU的计算公式。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  baud : 16; /* bit[0-15]: 波特率的时钟分频值。 */
    } reg;
} SOC_SCI_BAUD_UNION;
#endif
#define SOC_SCI_BAUD_baud_START  (0)
#define SOC_SCI_BAUD_baud_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_TIDE_UNION
 结构说明  : TIDE 寄存器结构定义。地址偏移量:0x001C，初值:0x0000，宽度:16
 寄存器说明: 发送接收FIFO的溢出阈值寄存器。
            (NH)
            (NL)TXFIFO中的字符只有在成功发送后才会被移除。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txtide   : 6;  /* bit[0-5]  : 设置SCITXTIDEINTR中断的触发值。
                                                      TXFIFO中的字符个数小于或等于SCI_TIDE[txtide]时会触发txtideintr中断。 */
        unsigned short  rxtide   : 6;  /* bit[6-11] : 设置SCIRXTIDEINTR中断的触发值。
                                                      RXFIFO中的字符个数大于或等于SCI_TIDE[rxtide]时会触发rxtideintr中断。 */
        unsigned short  reserved : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_SCI_TIDE_UNION;
#endif
#define SOC_SCI_TIDE_txtide_START    (0)
#define SOC_SCI_TIDE_txtide_END      (5)
#define SOC_SCI_TIDE_rxtide_START    (6)
#define SOC_SCI_TIDE_rxtide_END      (11)


/*****************************************************************************
 结构名    : SOC_SCI_DMACR_UNION
 结构说明  : DMACR 寄存器结构定义。地址偏移量:0x0020，初值:0x0000，宽度:16
 寄存器说明: DMA控制寄存器，用于控制DMA发送和接收数据。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxdmae   : 1;  /* bit[0]   : 接收FIFO的DAM使能位。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  txdmae   : 1;  /* bit[1]   : 发送FIFO的DMA使能位。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  reserved : 14; /* bit[2-15]: 保留。 */
    } reg;
} SOC_SCI_DMACR_UNION;
#endif
#define SOC_SCI_DMACR_rxdmae_START    (0)
#define SOC_SCI_DMACR_rxdmae_END      (0)
#define SOC_SCI_DMACR_txdmae_START    (1)
#define SOC_SCI_DMACR_txdmae_END      (1)


/*****************************************************************************
 结构名    : SOC_SCI_STABLE_UNION
 结构说明  : STABLE 寄存器结构定义。地址偏移量:0x0024，初值:0x0000，宽度:16
 寄存器说明: 智能卡插入稳定时间寄存器。当智能卡检测信号SCI_DETECT信号有效后，需要稳定保持SCI_STABLE寄存器值对应的固定的时间TSTABLE。经过TSTABLE时间（单位为秒）后触发cardinintr中断，表明智能卡已正确插入。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  stable   : 10; /* bit[0-9]  : 定义卡检测信号保持稳定高电平的时间。 */
        unsigned short  reserved : 6;  /* bit[10-15]: 保留。 */
    } reg;
} SOC_SCI_STABLE_UNION;
#endif
#define SOC_SCI_STABLE_stable_START    (0)
#define SOC_SCI_STABLE_stable_END      (9)


/*****************************************************************************
 结构名    : SOC_SCI_ATIME_UNION
 结构说明  : ATIME 寄存器结构定义。地址偏移量:0x0028，初值:0x0000，宽度:16
 寄存器说明: 智能卡激活时间寄存器。该寄存器的[atime]位用于指示卡复位和激活的3个阶段的持续时间。
            (NH)
            (NL)为满足卡复位的要求，SCI_ATIME[atime]至少为40000个接口卡时钟（SCI_CLK）周期。
            (NL)该参数也必须满足智能卡对电源稳定的要求。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atime : 16; /* bit[0-15]: 定义卡激活序列的3个阶段中，每个阶段的持续时间（SCI接口卡时钟SCI_CLK周期数）。 */
    } reg;
} SOC_SCI_ATIME_UNION;
#endif
#define SOC_SCI_ATIME_atime_START  (0)
#define SOC_SCI_ATIME_atime_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_DTIME_UNION
 结构说明  : DTIME 寄存器结构定义。地址偏移量:0x002C，初值:0x0000，宽度:16
 寄存器说明: 智能卡释放时间寄存器。该寄存器的{dtime]位用于指示卡释放的3个阶段的持续时间，单位为SCI参考时钟周期。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dtime : 16; /* bit[0-15]: 定义卡释放序列的3个阶段中，每个阶段的持续时间（SCI参考时钟周期数）。 */
    } reg;
} SOC_SCI_DTIME_UNION;
#endif
#define SOC_SCI_DTIME_dtime_START  (0)
#define SOC_SCI_DTIME_dtime_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_ATRSTIME_UNION
 结构说明  : ATRSTIME 寄存器结构定义。地址偏移量:0x0030，初值:0x0000，宽度:16
 寄存器说明: 等待开始接收ATR时间阈值寄存器。根据智能卡时钟定义了从智能卡复位结束到开始接收ATR第一个字符的时间阈值。ATR等待开始接收超时后会触发atrstoutintr中断，将SCI_RIS[atrstoutim]置1。
            (NH)SCI_ATRSTIME[atrstime]必须软件初始化为40000个SCI_CLK接口卡时钟周期。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atrstime : 16; /* bit[0-15]: 定义ATR接收启动超时的阈值时间（SCI接口卡时钟SCI_CLK周期数）。 */
    } reg;
} SOC_SCI_ATRSTIME_UNION;
#endif
#define SOC_SCI_ATRSTIME_atrstime_START  (0)
#define SOC_SCI_ATRSTIME_atrstime_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_ATRDTIME_UNION
 结构说明  : ATRDTIME 寄存器结构定义。地址偏移量:0x0034，初值:0x0000，宽度:16
 寄存器说明: 接收ATR时间阈值寄存器。SCI在接收ATR过程中（从第一个ATR字符开始接收到最后一个ATR字符接收结束）如果超过该寄存器所定义的时间（以ETU为单位），会触发中断，将SCI_RIS[atrdtoutris]置1。
            (NH)
            (NL)在使用该寄存器之前必须首先配置SCI_CR1[atrden]为1，以使能超时计数机制。
            (NL)根据协议，该寄存器建议配置为19200个ETU，即0x4B00。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atrdtime : 16; /* bit[0-15]: 定义从第一个ATR字符起始位算起的ATR接收超时的阈值（以ETU为单位）。 */
    } reg;
} SOC_SCI_ATRDTIME_UNION;
#endif
#define SOC_SCI_ATRDTIME_atrdtime_START  (0)
#define SOC_SCI_ATRDTIME_atrdtime_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_STOPTIME_UNION
 结构说明  : STOPTIME 寄存器结构定义。地址偏移量:0x0038，初值:0x0000，宽度:16
 寄存器说明: 时钟停止时间寄存器。当启动时钟停止时，经过SCI_STOPTIME所定义的时间（单位为SCI接口卡时钟SCI_CLK周期）后，智能卡时钟无效，并触发中断，将SCI_RIS[clkstpris]置1。
            (NH)根据协议，该值最小为1860个SCI时钟周期，即SCI_STOPTIME[stoptime]需要配置为0x744。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  stoptime : 12; /* bit[0-11] : 智能卡时钟停止时间（SCI智能卡时钟SCI_CLK周期数）；即从卡时钟停止到变为inactive持续的时间。 */
        unsigned short  reserved : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_SCI_STOPTIME_UNION;
#endif
#define SOC_SCI_STOPTIME_stoptime_START  (0)
#define SOC_SCI_STOPTIME_stoptime_END    (11)


/*****************************************************************************
 结构名    : SOC_SCI_STARTTIME_UNION
 结构说明  : STARTTIME 寄存器结构定义。地址偏移量:0x003C，初值:0x0000，宽度:16
 寄存器说明: 智能卡时钟恢复时间寄存器。当启动时钟恢复时，经过SCI_STARTTIME所定义的时间（单位为SCI接口卡时钟SCI_CLK周期）后，SCI与智能卡才能进行数据传输，并触发中断，将SCI_RIS[clkactris]置1。
            (NH)根据协议，该值最小应为700个SCI时钟周期，即SCI_STARTTIME[starttimr]至少需要配置为0x2BC。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  starttime : 12; /* bit[0-11] : 定义开始启动卡时钟到数据传输能够进行（active）这个过程持续的时间（SCI接口卡时钟SCI_CLK周期数）。 */
        unsigned short  reserved  : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_SCI_STARTTIME_UNION;
#endif
#define SOC_SCI_STARTTIME_starttime_START  (0)
#define SOC_SCI_STARTTIME_starttime_END    (11)


/*****************************************************************************
 结构名    : SOC_SCI_RETRY_UNION
 结构说明  : RETRY 寄存器结构定义。地址偏移量:0x0040，初值:0x0000，宽度:16
 寄存器说明: 发送接收重试次数寄存器。该寄存器定义了发送或接收允许重传的次数，具体内容为：
            (I)当SCI_CR0[txnak]使能时，SCI检测接收方是否标识校验错误，SCI_RETRY[rxretry]定义出现校验错误后重新传输的最大次数。超出将触发txerrintr中断，将SCI_RIS[txerrris]置1。
            (I)当SCI_CR0[rxnak]使能时，SCI检测收到的数据是否出现校验错误，SCI_RETRY[txretry]定义出现校验错误后重新传输的最大次数。如果超出该次数仍然接收错误，将SCI_DATA[parity]置1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txretry  : 3;  /* bit[0-2] : 定义当发送出现校验错误时，最大的发送重试次数。 */
        unsigned short  rxretry  : 3;  /* bit[3-5] : 定义当接收出现校验错误时，最大的接收重试次数。 */
        unsigned short  reserved : 10; /* bit[6-15]: 保留。 */
    } reg;
} SOC_SCI_RETRY_UNION;
#endif
#define SOC_SCI_RETRY_txretry_START   (0)
#define SOC_SCI_RETRY_txretry_END     (2)
#define SOC_SCI_RETRY_rxretry_START   (3)
#define SOC_SCI_RETRY_rxretry_END     (5)


/*****************************************************************************
 结构名    : SOC_SCI_CHTIMELS_UNION
 结构说明  : CHTIMELS 寄存器结构定义。地址偏移量:0x0044，初值:0x0000，宽度:16
 寄存器说明: 接收字符间隔超时阈值低16位寄存器。
            SCI_CHTIME寄存器定义从卡接收到的两个连续字符的起始沿之间允许的最大时间间隔（以ETU为单位）。如果接收到的字符间隔超时会触发chtoutintr中断，将SCI_RIS[chtoutris]置1。
            (CH)SCI_CHTIME寄存器是由低16位寄存器SCI_CHTIMELS和高16位寄存器SCI_CHTIMEMS组成。当软件写SCI_CHTIMEMS时，SCI_CHTIME不会立即生效，而写SCI_CHTIMELS时SCI_CHTIME才会生效，因此配置SCI_CHTIME必须先配置高16位，再配置低16位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  chtimels : 16; /* bit[0-15]: 定义接收字符间隔超时阈值寄存器SCICHTIME的低16位。 */
    } reg;
} SOC_SCI_CHTIMELS_UNION;
#endif
#define SOC_SCI_CHTIMELS_chtimels_START  (0)
#define SOC_SCI_CHTIMELS_chtimels_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_CHTIMEMS_UNION
 结构说明  : CHTIMEMS 寄存器结构定义。地址偏移量:0x0048，初值:0x0000，宽度:16
 寄存器说明: 接收字符间隔超时阈值高16位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  chtimems : 16; /* bit[0-15]: 定义接收字符间隔超时阈值寄存器SCICHTIME的高16位。 */
    } reg;
} SOC_SCI_CHTIMEMS_UNION;
#endif
#define SOC_SCI_CHTIMEMS_chtimems_START  (0)
#define SOC_SCI_CHTIMEMS_chtimems_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_BLKTIMELS_UNION
 结构说明  : BLKTIMELS 寄存器结构定义。地址偏移量:0x004C，初值:0x0000，宽度:16
 寄存器说明: 接收块间隔超时阈值低16位寄存器。
            SCI_BLKTIME定义接收块允许的最大时间间隔（以ETU为单位），该时间间隔的起始时刻是最后一个发送到卡的字符的起始沿，结束是第一个从卡返回的接收字符时刻。如果超时会触发blktoutintr中断，将SCI_RIS[blkoutim]置1。
            (CH)SCI_BLKTIME寄存器是由低16位寄存器SCI_BLKTIMELS和高16位寄存器SCI_BLKTIMEMS组成。当软件写SCI_BLKTIMEMS时，SCI_BLKTIME不会立即生效，写SCI_BLKTIMELS时SCI_BLKTIME才会生效，因此配置SCI_BLKTIME必须先配置高16位，再配置低16位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  blktimels : 16; /* bit[0-15]: 定义接收块间隔超时阈值寄存器SCIBLKTIME的低16位。 */
    } reg;
} SOC_SCI_BLKTIMELS_UNION;
#endif
#define SOC_SCI_BLKTIMELS_blktimels_START  (0)
#define SOC_SCI_BLKTIMELS_blktimels_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_BLKTIMEMS_UNION
 结构说明  : BLKTIMEMS 寄存器结构定义。地址偏移量:0x0050，初值:0x0000，宽度:16
 寄存器说明: 接收块间隔超时阈值高16位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  blktimems : 16; /* bit[0-15]: 定义接收块间隔超时阈值寄存器SCIBLKTIME器的高16位。 */
    } reg;
} SOC_SCI_BLKTIMEMS_UNION;
#endif
#define SOC_SCI_BLKTIMEMS_blktimems_START  (0)
#define SOC_SCI_BLKTIMEMS_blktimems_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_CHGUARD_UNION
 结构说明  : CHGUARD 寄存器结构定义。地址偏移量:0x0054，初值:0x0000，宽度:16
 寄存器说明: 字符间保护时间间隔寄存器。该寄存器定义当SCI向卡连续传输字符时，两个连续字符起始沿之间最小间隔的额外保护时间（以ETU为单位）。根据协议中定义的全局接口字节TC1（从ATR序列中得到）决定。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  scichguard : 8;  /* bit[0-7] : 字符间保护时间间隔（以ETU为单位），即两个连续字符起始位之间的最短时间。 */
        unsigned short  reserved   : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_SCI_CHGUARD_UNION;
#endif
#define SOC_SCI_CHGUARD_scichguard_START  (0)
#define SOC_SCI_CHGUARD_scichguard_END    (7)


/*****************************************************************************
 结构名    : SOC_SCI_BLKGUARD_UNION
 结构说明  : BLKGUARD 寄存器结构定义。地址偏移量:0x0058，初值:0x0000，宽度:16
 寄存器说明: 块间保护时间间隔寄存器。当两个连续字符的传输方向相反时，其起始沿之间的时间间隔为SCI_BLKGUARD。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  sciblkguard : 8;  /* bit[0-7] : 定义两个连续的相反方向字符之间的最短时间（以ETU为单位）。 */
        unsigned short  reserved    : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_SCI_BLKGUARD_UNION;
#endif
#define SOC_SCI_BLKGUARD_sciblkguard_START  (0)
#define SOC_SCI_BLKGUARD_sciblkguard_END    (7)


/*****************************************************************************
 结构名    : SOC_SCI_RXTIME_UNION
 结构说明  : RXTIME 寄存器结构定义。地址偏移量:0x005C，初值:0x0000，宽度:16
 寄存器说明: 接收FIFO读超时阈值寄存器。当接收FIFO中有字符且超出SCI_RXTIME所定义的时间仍然没有被读出，则触发接收读超时中断scirtout，SCI_RIS[rtoutris]将置1。
            (CH)正常使用接收FIFO读超时中断功能时，SCI_RXTIME[rxtime]不能为0x0000。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxtime : 16; /* bit[0-15]: 接收读超时时间值（SCI接口卡时钟SCI_CLK周期数）。 */
    } reg;
} SOC_SCI_RXTIME_UNION;
#endif
#define SOC_SCI_RXTIME_rxtime_START  (0)
#define SOC_SCI_RXTIME_rxtime_END    (15)


/*****************************************************************************
 结构名    : SOC_SCI_FIFOSTATUS_UNION
 结构说明  : FIFOSTATUS 寄存器结构定义。地址偏移量:0x0060，初值:0x000A，宽度:16
 寄存器说明: FIFO状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txff     : 1;  /* bit[0]   : 发送FIFO满状态。
                                                     0：未满；
                                                     1：满。 */
        unsigned short  txfe     : 1;  /* bit[1]   : 发送FIFO空状态。
                                                     0：非空；
                                                     1：空。 */
        unsigned short  rxff     : 1;  /* bit[2]   : 接收FIFO满状态。
                                                     0：未满；
                                                     1：满。 */
        unsigned short  rxfe     : 1;  /* bit[3]   : 接收FIFO空状态。
                                                     0：非空；
                                                     1：空。 */
        unsigned short  reserved : 12; /* bit[4-15]: 保留。 */
    } reg;
} SOC_SCI_FIFOSTATUS_UNION;
#endif
#define SOC_SCI_FIFOSTATUS_txff_START      (0)
#define SOC_SCI_FIFOSTATUS_txff_END        (0)
#define SOC_SCI_FIFOSTATUS_txfe_START      (1)
#define SOC_SCI_FIFOSTATUS_txfe_END        (1)
#define SOC_SCI_FIFOSTATUS_rxff_START      (2)
#define SOC_SCI_FIFOSTATUS_rxff_END        (2)
#define SOC_SCI_FIFOSTATUS_rxfe_START      (3)
#define SOC_SCI_FIFOSTATUS_rxfe_END        (3)


/*****************************************************************************
 结构名    : SOC_SCI_TXCOUNT_UNION
 结构说明  : TXCOUNT 寄存器结构定义。地址偏移量:0x0064，初值:0x0000，宽度:16
 寄存器说明: 发送FIFO数据个数寄存器。
            (NH)
            (NL)读该寄存器返回发送FIFO中字符的个数（包括了正在发送的字符）。
            (NL)当发送字符到卡出现错误（T0协议），并且重传次数超过了允许的值（在SCI_RETRY中定义），会触发txerr中断，将SCI_RIS[txerrris]置1。此时在进行下一次传输之前，发送FIFO必须被清空（写该寄存器）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txcount  : 6;  /* bit[0-5] : 读该寄存器返回发送FIFO中的字符数，写该寄存器（任意值）将清空发送FIFO。 */
        unsigned short  reserved : 10; /* bit[6-15]: 保留。 */
    } reg;
} SOC_SCI_TXCOUNT_UNION;
#endif
#define SOC_SCI_TXCOUNT_txcount_START   (0)
#define SOC_SCI_TXCOUNT_txcount_END     (5)


/*****************************************************************************
 结构名    : SOC_SCI_RXCOUNT_UNION
 结构说明  : RXCOUNT 寄存器结构定义。地址偏移量:0x0068，初值:0x0000，宽度:16
 寄存器说明: 接收FIFO数据个数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxcount  : 6;  /* bit[0-5] : 读该寄存器返回接收FIFO中的字符数，写该寄存器（任意值）将清空接收FIFO。 */
        unsigned short  reserved : 10; /* bit[6-15]: 保留。 */
    } reg;
} SOC_SCI_RXCOUNT_UNION;
#endif
#define SOC_SCI_RXCOUNT_rxcount_START   (0)
#define SOC_SCI_RXCOUNT_rxcount_END     (5)


/*****************************************************************************
 结构名    : SOC_SCI_IMSC_UNION
 结构说明  : IMSC 寄存器结构定义。地址偏移量:0x006C，初值:0x0000，宽度:16
 寄存器说明: 中断屏蔽寄存器。Bit值为0表示屏蔽，为1表示不屏蔽。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinim   : 1;  /* bit[0] : 智能卡插入中断屏蔽。 */
        unsigned short  cardoutim  : 1;  /* bit[1] : 智能卡拔出中断屏蔽。 */
        unsigned short  cardupim   : 1;  /* bit[2] : 智能卡激活中断屏蔽。 */
        unsigned short  carddnim   : 1;  /* bit[3] : 智能卡释放中断屏蔽。 */
        unsigned short  txerrim    : 1;  /* bit[4] : 发送错误中断屏蔽。 */
        unsigned short  atrstoutim : 1;  /* bit[5] : ATR等待超时中断屏蔽。 */
        unsigned short  atrdtoutim : 1;  /* bit[6] : ATR接收超时中断屏蔽。 */
        unsigned short  blktoutim  : 1;  /* bit[7] : 块间隔超时中断屏蔽。 */
        unsigned short  chtoutim   : 1;  /* bit[8] : 字符间隔超时中断屏蔽。 */
        unsigned short  rtoutim    : 1;  /* bit[9] : 读超时中断屏蔽。 */
        unsigned short  rorim      : 1;  /* bit[10]: 接收过载中断屏蔽。 */
        unsigned short  clkstpim   : 1;  /* bit[11]: 智能卡时钟停止中断屏蔽。 */
        unsigned short  clkactim   : 1;  /* bit[12]: 智能卡时钟恢复中断屏蔽。 */
        unsigned short  rxtideim   : 1;  /* bit[13]: 接收FIFO溢出中断屏蔽。 */
        unsigned short  txtideim   : 1;  /* bit[14]: 发送FIFO溢出中断屏蔽。 */
        unsigned short  reserved   : 1;  /* bit[15]: 保留。 */
    } reg;
} SOC_SCI_IMSC_UNION;
#endif
#define SOC_SCI_IMSC_cardinim_START    (0)
#define SOC_SCI_IMSC_cardinim_END      (0)
#define SOC_SCI_IMSC_cardoutim_START   (1)
#define SOC_SCI_IMSC_cardoutim_END     (1)
#define SOC_SCI_IMSC_cardupim_START    (2)
#define SOC_SCI_IMSC_cardupim_END      (2)
#define SOC_SCI_IMSC_carddnim_START    (3)
#define SOC_SCI_IMSC_carddnim_END      (3)
#define SOC_SCI_IMSC_txerrim_START     (4)
#define SOC_SCI_IMSC_txerrim_END       (4)
#define SOC_SCI_IMSC_atrstoutim_START  (5)
#define SOC_SCI_IMSC_atrstoutim_END    (5)
#define SOC_SCI_IMSC_atrdtoutim_START  (6)
#define SOC_SCI_IMSC_atrdtoutim_END    (6)
#define SOC_SCI_IMSC_blktoutim_START   (7)
#define SOC_SCI_IMSC_blktoutim_END     (7)
#define SOC_SCI_IMSC_chtoutim_START    (8)
#define SOC_SCI_IMSC_chtoutim_END      (8)
#define SOC_SCI_IMSC_rtoutim_START     (9)
#define SOC_SCI_IMSC_rtoutim_END       (9)
#define SOC_SCI_IMSC_rorim_START       (10)
#define SOC_SCI_IMSC_rorim_END         (10)
#define SOC_SCI_IMSC_clkstpim_START    (11)
#define SOC_SCI_IMSC_clkstpim_END      (11)
#define SOC_SCI_IMSC_clkactim_START    (12)
#define SOC_SCI_IMSC_clkactim_END      (12)
#define SOC_SCI_IMSC_rxtideim_START    (13)
#define SOC_SCI_IMSC_rxtideim_END      (13)
#define SOC_SCI_IMSC_txtideim_START    (14)
#define SOC_SCI_IMSC_txtideim_END      (14)


/*****************************************************************************
 结构名    : SOC_SCI_RIS_UNION
 结构说明  : RIS 寄存器结构定义。地址偏移量:0x0070，初值:0x0000，宽度:16
 寄存器说明: 原始中断寄存器。该寄存器是在中断屏蔽之前的原始中断。Bit值为0表示无中断，为1表示有中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinris   : 1;  /* bit[0] : 智能卡插入原始中断状态。 */
        unsigned short  cardoutris  : 1;  /* bit[1] : 智能卡拔出原始中断状态。 */
        unsigned short  cardupris   : 1;  /* bit[2] : 智能卡激活原始中断状态。 */
        unsigned short  carddnris   : 1;  /* bit[3] : 智能卡释放原始中断状态。 */
        unsigned short  txerrris    : 1;  /* bit[4] : 发送错误原始中断状态。当发送字符出现错误，重传次数达到了预设值但仍报错时置1。 */
        unsigned short  atrstoutris : 1;  /* bit[5] : ATR等待超时原始中断状态。 */
        unsigned short  atrdtoutris : 1;  /* bit[6] : ATR接收超时原始中断状态。 */
        unsigned short  blktoutris  : 1;  /* bit[7] : 块间隔超时原始中断状态。 */
        unsigned short  chtoutris   : 1;  /* bit[8] : 字符间隔超时原始中断状态。 */
        unsigned short  rtoutris    : 1;  /* bit[9] : 读超时原始中断状态。当接收FIFO有数据，但CPU在预定时间内没有取走时置1。 */
        unsigned short  rorris      : 1;  /* bit[10]: 接收过载原始中断状态。当接收FIFO处于满状态，又接收了新的字符时置1。 */
        unsigned short  clkstpris   : 1;  /* bit[11]: 智能卡时钟停止原始中断状态。 */
        unsigned short  clkactris   : 1;  /* bit[12]: 智能卡时钟恢复原始中断状态。 */
        unsigned short  rxtideris   : 1;  /* bit[13]: 接收FIFO溢出原始中断状态。当接收FIFO中字符的个数大于或等于阈值时置1。 */
        unsigned short  txtideris   : 1;  /* bit[14]: 发送FIFO溢出原始中断状态。当发送FIFO中字符的个数少于或等于阈值时置1。 */
        unsigned short  reserved    : 1;  /* bit[15]: 保留。 */
    } reg;
} SOC_SCI_RIS_UNION;
#endif
#define SOC_SCI_RIS_cardinris_START    (0)
#define SOC_SCI_RIS_cardinris_END      (0)
#define SOC_SCI_RIS_cardoutris_START   (1)
#define SOC_SCI_RIS_cardoutris_END     (1)
#define SOC_SCI_RIS_cardupris_START    (2)
#define SOC_SCI_RIS_cardupris_END      (2)
#define SOC_SCI_RIS_carddnris_START    (3)
#define SOC_SCI_RIS_carddnris_END      (3)
#define SOC_SCI_RIS_txerrris_START     (4)
#define SOC_SCI_RIS_txerrris_END       (4)
#define SOC_SCI_RIS_atrstoutris_START  (5)
#define SOC_SCI_RIS_atrstoutris_END    (5)
#define SOC_SCI_RIS_atrdtoutris_START  (6)
#define SOC_SCI_RIS_atrdtoutris_END    (6)
#define SOC_SCI_RIS_blktoutris_START   (7)
#define SOC_SCI_RIS_blktoutris_END     (7)
#define SOC_SCI_RIS_chtoutris_START    (8)
#define SOC_SCI_RIS_chtoutris_END      (8)
#define SOC_SCI_RIS_rtoutris_START     (9)
#define SOC_SCI_RIS_rtoutris_END       (9)
#define SOC_SCI_RIS_rorris_START       (10)
#define SOC_SCI_RIS_rorris_END         (10)
#define SOC_SCI_RIS_clkstpris_START    (11)
#define SOC_SCI_RIS_clkstpris_END      (11)
#define SOC_SCI_RIS_clkactris_START    (12)
#define SOC_SCI_RIS_clkactris_END      (12)
#define SOC_SCI_RIS_rxtideris_START    (13)
#define SOC_SCI_RIS_rxtideris_END      (13)
#define SOC_SCI_RIS_txtideris_START    (14)
#define SOC_SCI_RIS_txtideris_END      (14)


/*****************************************************************************
 结构名    : SOC_SCI_MIS_UNION
 结构说明  : MIS 寄存器结构定义。地址偏移量:0x0074，初值:0x0000，宽度:16
 寄存器说明: 屏蔽后中断寄存器。该寄存器是初始中断经过屏蔽后的结果。Bit值为0表示无中断，为1表示有中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinmis   : 1;  /* bit[0] : 智能卡插入屏蔽后中断状态。 */
        unsigned short  cardoutmis  : 1;  /* bit[1] : 智能卡拔出屏蔽后中断状态。 */
        unsigned short  cardupmis   : 1;  /* bit[2] : 智能卡激活屏蔽后中断状态。 */
        unsigned short  carddnmis   : 1;  /* bit[3] : 智能卡释放屏蔽后中断状态。 */
        unsigned short  txerrmis    : 1;  /* bit[4] : 发送错误屏蔽后中断状态。 */
        unsigned short  atrstoutim  : 1;  /* bit[5] : ATR等待超时屏蔽后中断状态。 */
        unsigned short  atrdtoutmis : 1;  /* bit[6] : ATR接收超时屏蔽后中断状态。 */
        unsigned short  blktoutmis  : 1;  /* bit[7] : 块间隔超时屏蔽后中断状态。 */
        unsigned short  chtoutmis   : 1;  /* bit[8] : 字符间隔超时屏蔽后中断状态。 */
        unsigned short  rtoutmis    : 1;  /* bit[9] : 读超时屏蔽后中断状态。 */
        unsigned short  rormis      : 1;  /* bit[10]: 接收过载屏蔽后中断状态。 */
        unsigned short  clkstpmis   : 1;  /* bit[11]: 智能卡时钟停止屏蔽后中断状态。 */
        unsigned short  clkactmis   : 1;  /* bit[12]: 智能卡时钟恢复屏蔽后中断状态。 */
        unsigned short  rxtidemis   : 1;  /* bit[13]: 接收FIFO溢出屏蔽后中断状态。 */
        unsigned short  txtidemis   : 1;  /* bit[14]: 发送FIFO溢出屏蔽后中断状态。 */
        unsigned short  reserved    : 1;  /* bit[15]: 保留。 */
    } reg;
} SOC_SCI_MIS_UNION;
#endif
#define SOC_SCI_MIS_cardinmis_START    (0)
#define SOC_SCI_MIS_cardinmis_END      (0)
#define SOC_SCI_MIS_cardoutmis_START   (1)
#define SOC_SCI_MIS_cardoutmis_END     (1)
#define SOC_SCI_MIS_cardupmis_START    (2)
#define SOC_SCI_MIS_cardupmis_END      (2)
#define SOC_SCI_MIS_carddnmis_START    (3)
#define SOC_SCI_MIS_carddnmis_END      (3)
#define SOC_SCI_MIS_txerrmis_START     (4)
#define SOC_SCI_MIS_txerrmis_END       (4)
#define SOC_SCI_MIS_atrstoutim_START   (5)
#define SOC_SCI_MIS_atrstoutim_END     (5)
#define SOC_SCI_MIS_atrdtoutmis_START  (6)
#define SOC_SCI_MIS_atrdtoutmis_END    (6)
#define SOC_SCI_MIS_blktoutmis_START   (7)
#define SOC_SCI_MIS_blktoutmis_END     (7)
#define SOC_SCI_MIS_chtoutmis_START    (8)
#define SOC_SCI_MIS_chtoutmis_END      (8)
#define SOC_SCI_MIS_rtoutmis_START     (9)
#define SOC_SCI_MIS_rtoutmis_END       (9)
#define SOC_SCI_MIS_rormis_START       (10)
#define SOC_SCI_MIS_rormis_END         (10)
#define SOC_SCI_MIS_clkstpmis_START    (11)
#define SOC_SCI_MIS_clkstpmis_END      (11)
#define SOC_SCI_MIS_clkactmis_START    (12)
#define SOC_SCI_MIS_clkactmis_END      (12)
#define SOC_SCI_MIS_rxtidemis_START    (13)
#define SOC_SCI_MIS_rxtidemis_END      (13)
#define SOC_SCI_MIS_txtidemis_START    (14)
#define SOC_SCI_MIS_txtidemis_END      (14)


/*****************************************************************************
 结构名    : SOC_SCI_ICR_UNION
 结构说明  : ICR 寄存器结构定义。地址偏移量:0x0078，初值:0x0000，宽度:16
 寄存器说明: 中断清除寄存器。Bit值为0表示不清除中断，为1表示清除中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinic   : 1;  /* bit[0]    : 智能卡插入中断清除。 */
        unsigned short  cardoutic  : 1;  /* bit[1]    : 智能卡拔出中断清除。 */
        unsigned short  cardupic   : 1;  /* bit[2]    : 智能卡激活中断清除。 */
        unsigned short  carddnic   : 1;  /* bit[3]    : 智能卡释放中断清除。 */
        unsigned short  txerric    : 1;  /* bit[4]    : 发送错误中断清除。 */
        unsigned short  atrstoutic : 1;  /* bit[5]    : ATR等待超时中断清除。 */
        unsigned short  atrdtoutic : 1;  /* bit[6]    : ATR接收超时中断清除。 */
        unsigned short  blktoutic  : 1;  /* bit[7]    : 块间隔超时中断清除。 */
        unsigned short  chtoutic   : 1;  /* bit[8]    : 字符间隔超时中断清除。 */
        unsigned short  rtoutic    : 1;  /* bit[9]    : 读超时中断清除。 */
        unsigned short  roric      : 1;  /* bit[10]   : 接收过载中断清除。 */
        unsigned short  clkstpic   : 1;  /* bit[11]   : 智能卡时钟停止中断清除。 */
        unsigned short  clkactic   : 1;  /* bit[12]   : 智能卡时钟恢复中断清除。 */
        unsigned short  reserved   : 3;  /* bit[13-15]: 保留。 */
    } reg;
} SOC_SCI_ICR_UNION;
#endif
#define SOC_SCI_ICR_cardinic_START    (0)
#define SOC_SCI_ICR_cardinic_END      (0)
#define SOC_SCI_ICR_cardoutic_START   (1)
#define SOC_SCI_ICR_cardoutic_END     (1)
#define SOC_SCI_ICR_cardupic_START    (2)
#define SOC_SCI_ICR_cardupic_END      (2)
#define SOC_SCI_ICR_carddnic_START    (3)
#define SOC_SCI_ICR_carddnic_END      (3)
#define SOC_SCI_ICR_txerric_START     (4)
#define SOC_SCI_ICR_txerric_END       (4)
#define SOC_SCI_ICR_atrstoutic_START  (5)
#define SOC_SCI_ICR_atrstoutic_END    (5)
#define SOC_SCI_ICR_atrdtoutic_START  (6)
#define SOC_SCI_ICR_atrdtoutic_END    (6)
#define SOC_SCI_ICR_blktoutic_START   (7)
#define SOC_SCI_ICR_blktoutic_END     (7)
#define SOC_SCI_ICR_chtoutic_START    (8)
#define SOC_SCI_ICR_chtoutic_END      (8)
#define SOC_SCI_ICR_rtoutic_START     (9)
#define SOC_SCI_ICR_rtoutic_END       (9)
#define SOC_SCI_ICR_roric_START       (10)
#define SOC_SCI_ICR_roric_END         (10)
#define SOC_SCI_ICR_clkstpic_START    (11)
#define SOC_SCI_ICR_clkstpic_END      (11)
#define SOC_SCI_ICR_clkactic_START    (12)
#define SOC_SCI_ICR_clkactic_END      (12)


/*****************************************************************************
 结构名    : SOC_SCI_SYNCACT_UNION
 结构说明  : SYNCACT 寄存器结构定义。地址偏移量:0x007C，初值:0x0000，宽度:16
 寄存器说明: 同步模式激活寄存器。该寄存器用于同步模式下数据使能、时钟使能、复位和电源控制等，并提供状态寄存器，相应的状态位在激活、释放、热复位过程中自动更新。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  power         : 1;  /* bit[0]    : 控制卡电源（VCC）使能。
                                                           0：使能：
                                                           1：禁止。 */
        unsigned short  creset        : 1;  /* bit[1]    : 卡复位信号控制使能。
                                                           0：使能：
                                                           1：禁止。 */
        unsigned short  clken         : 1;  /* bit[2]    : SCI时钟输出使能。
                                                           0：禁止；
                                                           1：使能。 */
        unsigned short  dataen        : 1;  /* bit[3]    : SCI数据输出使能。
                                                           0：禁止；
                                                           1：使能。 */
        unsigned short  reserved_0    : 1;  /* bit[4]    : 保留。 */
        unsigned short  nsciclkouten  : 1;  /* bit[5]    : 数据buffer的三态控制使能。
                                                           0：使能；
                                                           1：禁止。 */
        unsigned short  nsciclken     : 1;  /* bit[6]    : 时钟的外部offchip buffer的三态控制使能。
                                                           0：使能；
                                                           1：禁止。 */
        unsigned short  sciclkout     : 1;  /* bit[7]    : SCI时钟输出使能。
                                                           0：使能；
                                                           1：禁止。 */
        unsigned short  nscidataouten : 1;  /* bit[8]    : 数据buffer的三态控制使能。
                                                           0：使能；
                                                           1：禁止。 */
        unsigned short  nscidataen    : 1;  /* bit[9]    : 数据的外部offchip buffer的三态控制使能。
                                                           0：使能；
                                                           1：禁止。 */
        unsigned short  cardpresent   : 1;  /* bit[10]   : 智能卡存在状态位。
                                                           0：无智能卡；
                                                           1：有智能卡。 */
        unsigned short  reserved_1    : 5;  /* bit[11-15]: 保留。 */
    } reg;
} SOC_SCI_SYNCACT_UNION;
#endif
#define SOC_SCI_SYNCACT_power_START          (0)
#define SOC_SCI_SYNCACT_power_END            (0)
#define SOC_SCI_SYNCACT_creset_START         (1)
#define SOC_SCI_SYNCACT_creset_END           (1)
#define SOC_SCI_SYNCACT_clken_START          (2)
#define SOC_SCI_SYNCACT_clken_END            (2)
#define SOC_SCI_SYNCACT_dataen_START         (3)
#define SOC_SCI_SYNCACT_dataen_END           (3)
#define SOC_SCI_SYNCACT_nsciclkouten_START   (5)
#define SOC_SCI_SYNCACT_nsciclkouten_END     (5)
#define SOC_SCI_SYNCACT_nsciclken_START      (6)
#define SOC_SCI_SYNCACT_nsciclken_END        (6)
#define SOC_SCI_SYNCACT_sciclkout_START      (7)
#define SOC_SCI_SYNCACT_sciclkout_END        (7)
#define SOC_SCI_SYNCACT_nscidataouten_START  (8)
#define SOC_SCI_SYNCACT_nscidataouten_END    (8)
#define SOC_SCI_SYNCACT_nscidataen_START     (9)
#define SOC_SCI_SYNCACT_nscidataen_END       (9)
#define SOC_SCI_SYNCACT_cardpresent_START    (10)
#define SOC_SCI_SYNCACT_cardpresent_END      (10)


/*****************************************************************************
 结构名    : SOC_SCI_SYNCTX_UNION
 结构说明  : SYNCTX 寄存器结构定义。地址偏移量:0x0080，初值:0x0000，宽度:16
 寄存器说明: 同步模式发送时钟和数据流寄存器。该寄存器用于控制同步模式下发送时钟和数据。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  wdata    : 1;  /* bit[0]   : 同步模式下SCI数据使能。
                                                     0：使能；
                                                     1：禁止。 */
        unsigned short  wclk     : 1;  /* bit[1]   : 同步模式下SCI时钟使能。
                                                     0：使能；
                                                     1：禁止。 */
        unsigned short  wdataen  : 1;  /* bit[2]   : 同步模式下，该位为SCI数据输出使能。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  wclken   : 1;  /* bit[3]   : 同步模式下，该位为时钟的外部off chip buffer的三态使能控制。
                                                     0：使能；
                                                     1：禁止。 */
        unsigned short  wrst     : 1;  /* bit[4]   : 同步模式下，该位为卡复位信号使能。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  reserved_0: 1;  /* bit[5]   : 保留。 */
        unsigned short  reserved_1: 10; /* bit[6-15]: 保留。 */
    } reg;
} SOC_SCI_SYNCTX_UNION;
#endif
#define SOC_SCI_SYNCTX_wdata_START     (0)
#define SOC_SCI_SYNCTX_wdata_END       (0)
#define SOC_SCI_SYNCTX_wclk_START      (1)
#define SOC_SCI_SYNCTX_wclk_END        (1)
#define SOC_SCI_SYNCTX_wdataen_START   (2)
#define SOC_SCI_SYNCTX_wdataen_END     (2)
#define SOC_SCI_SYNCTX_wclken_START    (3)
#define SOC_SCI_SYNCTX_wclken_END      (3)
#define SOC_SCI_SYNCTX_wrst_START      (4)
#define SOC_SCI_SYNCTX_wrst_END        (4)


/*****************************************************************************
 结构名    : SOC_SCI_SYNCRX_UNION
 结构说明  : SYNCRX 寄存器结构定义。地址偏移量:0x0084，初值:0x0000，宽度:16
 寄存器说明: 同步模式接收时钟和数据流寄存器。该寄存器用于控制同步模式下接收时钟和数据。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rdata    : 1;  /* bit[0]   : 数据原始值。 */
        unsigned short  rclk     : 1;  /* bit[1]   : 时钟原始值。 */
        unsigned short  reserved : 14; /* bit[2-15]: 保留。 */
    } reg;
} SOC_SCI_SYNCRX_UNION;
#endif
#define SOC_SCI_SYNCRX_rdata_START     (0)
#define SOC_SCI_SYNCRX_rdata_END       (0)
#define SOC_SCI_SYNCRX_rclk_START      (1)
#define SOC_SCI_SYNCRX_rclk_END        (1)






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

#endif /* end of soc_sci_interface.h */
