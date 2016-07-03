/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_sio.h */
/* Version       : 2.0 */
/* Created       : 2013-04-19*/
/* Last Modified : */
/* Description   :  The C union definition file for the module sio*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_SIO_H__
#define __HI_SIO_H__

/*
 * Project: hi
 * Module : sio
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    sio 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_SIO_VERSION_OFFSET                             (0x3C) /* 版本寄存器，用来记录SIO的版本号和进行SIO的自测试。 */
#define    HI_SIO_MODE_OFFSET                                (0x40) /* 模式寄存器，用来对SIO工作的基本模式进行选择：(I)主模式下，CRG送时钟和同步信号给CODEC，同时给SIO。(I)从模式下，时钟和同步信号由外部CODEC送给SIO。I2S或PCM的主从模式选择由系统控制寄存器SC_PERCTRL6设定。 */
#define    HI_SIO_INTSTATUS_OFFSET                           (0x44) /* SIO的中断状态指示寄存器。对于接收中断，当接收FIFO的数据深度大于FIFO阈值时，会一直把高电平锁存到中断状态寄存器中，一直产生中断（即使CPU清一次中断，但中断状态寄存器会在下一个时钟周期再次置位）。因此，建议CPU的处理步骤为：(S)向SIO_CT_CLR[intr_en]写1，关闭全局中断使能。(S)读中断状态寄存器SIO_INTSTATUS。(S)根据中断源进行相应处理。(S)向SIO_INTCLR的相应位写1，清除中断。(S)向写寄存器SIO_CT_SET[intr_en]写1，打开全局中断使能。(SE)发送中断的产生方式与接收中断产生方式相同，因此对于发送中断的处理，建议也采用相同的方式。本寄存器是原始中断状态寄存器。在相应中断位屏蔽的情况下，中断条件满足时，对应中断状态位仍然会置位，但不会触发中断。 */
#define    HI_SIO_INTCLR_OFFSET                              (0x48) /* 中断清除寄存器，可以按位清除。Bit值为0表示不清除中断，为1表示清除中断。 */
#define    HI_SIO_I2S_LEFT_XD_OFFSET                         (0x4C) /* I2S模式下的左声道数据发送寄存器。向寄存器写数据时，有效数据需放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */
#define    HI_SIO_I2S_RIGHT_XD_OFFSET                        (0x50) /* I2S模式下的右声道数据发送寄存器。PCM数据发送寄存器与I2S右声道数据发送寄存器是复用的。向寄存器写数据时，有效数据需放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */
#define    HI_SIO_PCM_XD_OFFSET                              (0x50) /* PCM模式下的数据发送寄存器。PCM数据发送寄存器与I2S右声道数据发送寄存器是复用的。向寄存器写有效数据时，有效数据需放在寄存器的低bit区域。例如，8bit宽度时，bit[7:0]为有效数据，bit[31:8]为无效数据。16bit宽度时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */
#define    HI_SIO_I2S_LEFT_RD_OFFSET                         (0x54) /* I2S左声道数据接收寄存器。SIO模块把接收到的有效数据放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */
#define    HI_SIO_I2S_RIGHT_RD_OFFSET                        (0x58) /* I2S右声道数据接收寄存器。SIO模块把接收到的有效数据放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */
#define    HI_SIO_PCM_RD_OFFSET                              (0x58) /* PCM接收数据寄存器。它与I2S右声道接收寄存器是复用的。SIO模块把接收到的有效数据放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */
#define    HI_SIO_RX_STA_OFFSET                              (0x68) /* SIO接收状态寄存器。 */
#define    HI_SIO_TX_STA_OFFSET                              (0x6C) /* SIO发送状态寄存器。 */
#define    HI_SIO_DATA_WIDTH_SET_OFFSET                      (0x78) /* I2S/PCM模式下的数据宽度配置寄存器。 */
#define    HI_SIO_I2S_START_POS_OFFSET                       (0x7C) /* I2S左右声道起始位置配置控制寄存器。在I2S模式下，左右声道数据操作地址合并使能后，控制起始访问是从左声道开始还是从右声道开始。 */
#define    HI_I2S_POS_FLAG_OFFSET                            (0x80) /* I2S左右声道操作当前位置状态寄存器。在I2S模式下，左右声道数据操作地址合并使能后，指示下一次访问寄存器是从左声道开始还是从右声道开始。 */
#define    HI_SIO_SIGNED_EXT_OFFSET                          (0x84) /* 高位数据符号扩展使能寄存器。该标志只对接收数据有效，对发送数据无效。PCM模式和I2S模式下接收到的数据都支持符号扩展。在接收有效数据位宽为8/16/18/20/24 bit时，如果该标志使能，把接收到的数据转换为32bit数据时，把32bit数据的高位无效比特设置为接收数据最高有效bit对应的值，然后再写入接收FIFO。以16bit位宽为例：if (data_rx[15] == 1 ) data_rx[31:16]=0xffff;elsedata_rx[31:16]=0x0000; */
#define    HI_SIO_I2S_POS_MERGE_EN_OFFSET                    (0x88) /* I2S模式左右声道数据操作地址合并使能寄存器。在I2S模式下，用DMA方式读写SIO的FIFO数据时，因为左右声道数据地址不同，需要CPU不断配置DMA操作的地址，导致CPU效率低。为了提高CPU的效率，提供左右声道数据的读写的统一地址使能控制。使能情况下，读左右声道数据统一使用SIO_I2S_DUAL_RX_CHN寄存器，写左右声道数据统一使用SIO_I2S_DUAL_TX_CHN寄存器。 */
#define    HI_SIO_INTMASK_OFFSET                             (0x8C) /* 中断屏蔽寄存器。 */
#define    HI_SIO_I2S_DUAL_RX_CHN_OFFSET                     (0xA0) /* 读取接收数据寄存器。I2S左右声道操作地址合并使能后，读取接收数据。 */
#define    HI_SIO_I2S_DUAL_TX_CHN_OFFSET                     (0xC0) /* 写发送数据寄存器。I2S左右声道操作地址合并使能后，写发送数据。 */

#define    HI_SIO_I2S_CT_SET_OFFSET                     (0x5C) /* SIO 控制寄存器 设置 */
#define    HI_SIO_I2S_CT_CLR_OFFSET                     (0x60) /* SIO 控制寄存器 设置。 */

/********************************************************************************/
/*    sio 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    vesion                     : 8; /* [7..0] SIO的版本号。 */
        unsigned int    sio_loop                   : 1; /* [8..8] 0：正常模式；1：SIO发送和接收数据环回模式，用于SIO的自测试。在该模式下，在SIO的对外接口处，SIO接收串行数据线与SIO发送串行数据线直接相连。 */
        unsigned int    reserved                   : 23; /* [31..9] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_VERSION_T;    /* 版本寄存器，用来记录SIO的版本号和进行SIO的自测试。 */

typedef union
{
    struct
    {
        unsigned int    sio_mode                   : 1; /* [0..0] PCM/I2S模式选择。0：I2S模式；1：PCM模式。 */
        unsigned int    pcm_mode                   : 1; /* [1..1] PCM时序模式。0：标准模式；1：自定义模式。 */
        unsigned int    reserved_1                 : 1; /* [2..2] 保留，必须配置为0 */
        unsigned int    ext_rec_en                 : 1; /* [3..3] 标准模式下，I2S接收两个声道的数据，即左声道和右声道。PCM只接收一个声道的数据。多路接收模式下，对于I2S或PCM，接收通道数可以配置。该模式下，通道的数据宽度必须为8bit或16bit。0：标准的I2S或PCM接收模式；1：扩展的I2S或PCM多路接收模式。 */
        unsigned int    chn_num                    : 2; /* [5..4] 多路接收的通道数选择。00：2 chn；01：4 chn；10：8 chn；11：16 chn */
        unsigned int    clk_edge                   : 1; /* [6..6] PCM多路接收模式下，采样数据时钟边沿选择。0：下降沿有效；1：上升沿有效。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_MODE_T;    /* 模式寄存器，用来对SIO工作的基本模式进行选择：(I)主模式下，CRG送时钟和同步信号给CODEC，同时给SIO。(I)从模式下，时钟和同步信号由外部CODEC送给SIO。I2S或PCM的主从模式选择由系统控制寄存器SC_PERCTRL6设定。 */

typedef union
{
    struct
    {
        unsigned int    rx_intr                    : 1; /* [0..0] 接收FIFO高于阈值中断状态。0：未产生中断；1：已产生中断。 */
        unsigned int    tx_intr                    : 1; /* [1..1] 发送FIFO低于阈值中断状态。0：未产生中断；1：已产生中断。 */
        unsigned int    rx_right_fifo_over         : 1; /* [2..2] I2S模式下，右声道接收FIFO上溢中断状态。PCM模式下，PCM接收FIFO上溢标志。0：未产生中断；1：已产生中断。 */
        unsigned int    rx_left_fifo_over          : 1; /* [3..3] I2S模式下，左声道接收FIFO上溢中断状态。PCM模式下无效。0：未产生中断；1：已产生中断。 */
        unsigned int    tx_right_fifo_under        : 1; /* [4..4] I2S模式下，右声道发送FIFO下溢中断状态。PCM模式下，PCM发送FIFO下溢标志。0：未产生中断；1：已产生中断。 */
        unsigned int    tx_left_fifo_under         : 1; /* [5..5] I2S模式下，左声道发送FIFO下溢中断状态。PCM模式下无效。0：未产生中断；1：已产生中断。 */
        unsigned int    reserved                   : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_INTSTATUS_T;    /* SIO的中断状态指示寄存器。对于接收中断，当接收FIFO的数据深度大于FIFO阈值时，会一直把高电平锁存到中断状态寄存器中，一直产生中断（即使CPU清一次中断，但中断状态寄存器会在下一个时钟周期再次置位）。因此，建议CPU的处理步骤为：(S)向SIO_CT_CLR[intr_en]写1，关闭全局中断使能。(S)读中断状态寄存器SIO_INTSTATUS。(S)根据中断源进行相应处理。(S)向SIO_INTCLR的相应位写1，清除中断。(S)向写寄存器SIO_CT_SET[intr_en]写1，打开全局中断使能。(SE)发送中断的产生方式与接收中断产生方式相同，因此对于发送中断的处理，建议也采用相同的方式。本寄存器是原始中断状态寄存器。在相应中断位屏蔽的情况下，中断条件满足时，对应中断状态位仍然会置位，但不会触发中断。 */

typedef union
{
    struct
    {
        unsigned int    rx_intr                    : 1; /* [0..0] 接收FIFO高于阈值中断清除。 */
        unsigned int    tx_intr                    : 1; /* [1..1] 发送FIFO低于阈值中断清除。 */
        unsigned int    rx_right_fifo_over         : 1; /* [2..2] I2S模式下，右声道接收FIFO上溢中断清除。PCM模式下，PCM接收FIFO上溢中断清除。 */
        unsigned int    rx_left_fifo_over          : 1; /* [3..3] I2S模式下，左声道接收FIFO上溢中断清除。PCM模式下无效。 */
        unsigned int    tx_right_fifo_under        : 1; /* [4..4] I2S模式下，右声道发送FIFO下溢中断清除。PCM模式下，PCM发送FIFO下溢中断清除。 */
        unsigned int    tx_left_fifo_under         : 1; /* [5..5] I2S模式下，左声道发送FIFO下溢中断清除。PCM模式下无效。 */
        unsigned int    reserved                   : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_INTCLR_T;    /* 中断清除寄存器，可以按位清除。Bit值为0表示不清除中断，为1表示清除中断。 */

typedef union
{
    struct
    {
        unsigned int    tx_left_data               : 32; /* [31..0] 左声道发送数据。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_LEFT_XD_T;    /* I2S模式下的左声道数据发送寄存器。向寄存器写数据时，有效数据需放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */

typedef union
{
    struct
    {
        unsigned int    tx_right_data              : 32; /* [31..0] 右声道发送数据。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_RIGHT_XD_T;    /* I2S模式下的右声道数据发送寄存器。PCM数据发送寄存器与I2S右声道数据发送寄存器是复用的。向寄存器写数据时，有效数据需放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */

typedef union
{
    struct
    {
        unsigned int    tx_data                    : 16; /* [15..0] PCM发送数据。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_PCM_XD_T;    /* PCM模式下的数据发送寄存器。PCM数据发送寄存器与I2S右声道数据发送寄存器是复用的。向寄存器写有效数据时，有效数据需放在寄存器的低bit区域。例如，8bit宽度时，bit[7:0]为有效数据，bit[31:8]为无效数据。16bit宽度时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */

typedef union
{
    struct
    {
        unsigned int    rx_left_data               : 32; /* [31..0] I2S左声道接收数据。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_LEFT_RD_T;    /* I2S左声道数据接收寄存器。SIO模块把接收到的有效数据放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */

typedef union
{
    struct
    {
        unsigned int    rx_right_data              : 32; /* [31..0] I2S右声道接收数据。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_RIGHT_RD_T;    /* I2S右声道数据接收寄存器。SIO模块把接收到的有效数据放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */

typedef union
{
    struct
    {
        unsigned int    rx__data                   : 16; /* [15..0] PCM接收数据。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_PCM_RD_T;    /* PCM接收数据寄存器。它与I2S右声道接收寄存器是复用的。SIO模块把接收到的有效数据放在寄存器的低bit区域。例如，数据宽度为8bit时，bit[7:0]为有效数据，bit[31:8]为无效数据；数据宽度为16bit时，bit[15:0]为有效数据，bit[31:16]为无效数据。超出有效数据宽度的bit位由SIO模块自动置0。 */

typedef union
{
    struct
    {
        unsigned int    rx_right_depth             : 5; /* [4..0] I2S模式下，为右声道接收FIFO深度指示。PCM模式下，为PCM接收FIFO深度指示。 */
        unsigned int    rx_left_depth              : 5; /* [9..5] 左声道接收FIFO深度指示。只在I2S模式下有效。 */
        unsigned int    reserved                   : 22; /* [31..10] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_RX_STA_T;    /* SIO接收状态寄存器。 */

typedef union
{
    struct
    {
        unsigned int    tx_right_depth             : 5; /* [4..0] I2S模式下，为右声道发送FIFO深度指示。PCM模式下，为PCM发送FIFO深度指示。 */
        unsigned int    tx_left_depth              : 5; /* [9..5] 左声道发送FIFO深度指示。只在I2S模式下有效。 */
        unsigned int    reserved                   : 22; /* [31..10] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_TX_STA_T;    /* SIO发送状态寄存器。 */

typedef union
{
    struct
    {
        unsigned int    tx_mode                    : 3; /* [2..0] 发送数据长度配置位。对于I2S模式000：保留；001：16bit；010：18bit；011：20bit；100：24bit；101：32bit；110～111：保留。000：8bit001：16bit；010：32bit；011：64bit；100：128bit；101～111：保留。 */
        unsigned int    rx_mode                    : 3; /* [5..3] 接收数据长度配置位。000：8bit；001：16bit；010：18bit；011：20bit；100：24bit；101：32bit；110～111：保留。对于I2S模式，支持16/18/20/24/32bit；对于PCM模式，支持8/16bit；对于多路接收，两种模式只支持8/16bit。 */
        unsigned int    reserved                   : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_DATA_WIDTH_SET_T;    /* I2S/PCM模式下的数据宽度配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    start_pos_read             : 1; /* [0..0] 读接收FIFO时：0：从左声道开始访问；1：从右声道开始访问。 */
        unsigned int    start_pos_write            : 1; /* [1..1] 写发送FIFO时：0：从左声道开始访问；1：从右声道开始访问。 */
        unsigned int    reserved                   : 30; /* [31..2] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_START_POS_T;    /* I2S左右声道起始位置配置控制寄存器。在I2S模式下，左右声道数据操作地址合并使能后，控制起始访问是从左声道开始还是从右声道开始。 */

typedef union
{
    struct
    {
        unsigned int    start_pos_read             : 1; /* [0..0] 读接收FIFO时：0：下一次从左声道开始访问；1：下一次从右声道开始访问。 */
        unsigned int    start_pos_write            : 1; /* [1..1] 写发送FIFO时：0：下一次从左声道开始访问；1：下一次从右声道开始访问。 */
        unsigned int    reserved                   : 30; /* [31..2] 保留。 */
    } bits;
    unsigned int    u32;
}HI_I2S_POS_FLAG_T;    /* I2S左右声道操作当前位置状态寄存器。在I2S模式下，左右声道数据操作地址合并使能后，指示下一次访问寄存器是从左声道开始还是从右声道开始。 */

typedef union
{
    struct
    {
        unsigned int    signed_ext_en              : 1; /* [0..0] 高位数据符号扩展使能。0：不使能；1：使能。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_SIGNED_EXT_T;    /* 高位数据符号扩展使能寄存器。该标志只对接收数据有效，对发送数据无效。PCM模式和I2S模式下接收到的数据都支持符号扩展。在接收有效数据位宽为8/16/18/20/24 bit时，如果该标志使能，把接收到的数据转换为32bit数据时，把32bit数据的高位无效比特设置为接收数据最高有效bit对应的值，然后再写入接收FIFO。以16bit位宽为例：if (data_rx[15] == 1 ) data_rx[31:16]=0xffff;elsedata_rx[31:16]=0x0000; */

typedef union
{
    struct
    {
        unsigned int    merge_en                   : 1; /* [0..0] 在I2S模式下，对左右声道数据的操作地址合并使能。0：不使能；1：使能。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_POS_MERGE_EN_T;    /* I2S模式左右声道数据操作地址合并使能寄存器。在I2S模式下，用DMA方式读写SIO的FIFO数据时，因为左右声道数据地址不同，需要CPU不断配置DMA操作的地址，导致CPU效率低。为了提高CPU的效率，提供左右声道数据的读写的统一地址使能控制。使能情况下，读左右声道数据统一使用SIO_I2S_DUAL_RX_CHN寄存器，写左右声道数据统一使用SIO_I2S_DUAL_TX_CHN寄存器。 */

typedef union
{
    struct
    {
        unsigned int    rx_intr                    : 1; /* [0..0] 接收FIFO高于阈值中断屏蔽。0：不屏蔽该中断；1：屏蔽该中断。 */
        unsigned int    tx_intr                    : 1; /* [1..1] 发送FIFO低于阈值中断屏蔽。0：不屏蔽该中断；1：屏蔽该中断。 */
        unsigned int    rx_right_fifo_over         : 1; /* [2..2] I2S模式下，右声道接收FIFO上溢中断屏蔽。PCM模式下，PCM接收FIFO下溢中断屏蔽。0：不屏蔽该中断；1：屏蔽该中断。 */
        unsigned int    rx_left_fifo_over          : 1; /* [3..3] I2S模式下，左声道接收FIFO上溢中断屏蔽。PCM模式下无效。0：不屏蔽该中断；1：屏蔽该中断。 */
        unsigned int    tx_right_fifo_under        : 1; /* [4..4] I2S模式下，右声道发送FIFO下溢中断屏蔽。PCM模式下，PCM发送FIFO下溢中断屏蔽。0：不屏蔽该中断；1：屏蔽该中断。 */
        unsigned int    tx_left_fifo_under         : 1; /* [5..5] I2S模式下，左声道发送FIFO下溢中断屏蔽。PCM模式下无效。0：不屏蔽该中断；1：屏蔽该中断。 */
        unsigned int    reserved                   : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_SIO_INTMASK_T;    /* 中断屏蔽寄存器。 */

typedef union
{
    struct
    {
        unsigned int    rx_data                    : 32; /* [31..0] 接收到的数据。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_DUAL_RX_CHN_T;    /* 读取接收数据寄存器。I2S左右声道操作地址合并使能后，读取接收数据。 */

typedef union
{
    struct
    {
        unsigned int    tx_data                    : 32; /* [31..0] 发送的数据。 */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_DUAL_TX_CHN_T;    /* 写发送数据寄存器。I2S左右声道操作地址合并使能后，写发送数据。 */

typedef union
{
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : 发送FIFO阈值。
                                                             当tx_right_depth < (tx_fifo_threshold + 1)时，报发送中断和DMA请求。 */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : 接收FIFO阈值。
                                                             当rx_right_depth 3(rx_fifo_threshold + 1)时，报接收中断和DMA请求。 */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : 数据发送合并使能，只在I2S 模式下且数据位宽为16bit时有效。
                                                             0：不使能；
                                                             1：使能。
                                                             &#13;该位为1时，左右声道数据拼成一个32bit数据在FIFO中进行存储，左声道16bit数据占据高16位，右声道16bit数据占据低16位。这样可以提高FIFO的利用率，以提供更长时间的缓冲能力。&#13;在这种情况下，CPU向发送FIFO中写入数据时，按照如下顺序：向左声道FIFO写入一个32bit数据（左右声道各16bit合并成的一个32bit数据），再向右声道FIFO写入一个32bit数据，如此反复。 */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : 数据接收合并使能，只在I2S模式下且数据位宽为16bit时有效。
                                                             0：不使能；
                                                             &#13;1：使能。
                                                             该位为1时，左右声道数据拼成一个32bit数据在FIFO中进行存储，左声道16bit数据占据高16位，右声道16bit数据占据低16位。这样可以提高FIFO的利用率，以提供更长时间的缓冲能力。&#13;CPU从接收FIFO中读数据时，按照如下顺序：从左声道FIFO读出一个32bit数据（左右声道各16bit合并成的一个32bit数据），再从右声道FIFO读出一个32bit数据，如此反复。 */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : 发送FIFO禁止。
                                                             0：使能；
                                                             &#13;1：禁止。 */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : 接收FIFO禁止。
                                                             0：使能；
                                                             &#13;1：禁止。 */
        unsigned int  tx_enable         : 1;  /* bit[12]   : 发送通道使能。
                                                             0：禁止；
                                                             &#13;1：使能。 */
        unsigned int  rx_enable         : 1;  /* bit[13]   : 接收通道使能。
                                                             0：禁止；
                                                             &#13;1：使能。 */
        unsigned int  intr_en           : 1;  /* bit[14]   : 中断全局使能。
                                                             0：禁止；
                                                             &#13;1：使能。 */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCM通道复位，低电平有效。
                                                             它对I2S/PCM接收和发送模块（包括FIFO）进行复位，因此发送和接收FIFO状态寄存器会变为0。但不会复位CPU接口寄存器模块。 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留。 */
    } bits;
    unsigned int      u32;
} HI_SIO_CT_SET_T;

typedef union
{
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : 发送FIFO阈值。
                                                             当tx_right_depth < (tx_fifo_threshold + 1)时，报发送中断和DMA请求。 */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : 接收FIFO阈值。
                                                             当rx_right_depth 3(rx_fifo_threshold + 1)时，报接收中断和DMA请求。 */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : 数据发送合并使能，只在I2S 模式下且数据位宽为16bit时有效。
                                                             0：不使能；
                                                             1：使能。
                                                             &#13;该位为1时，左右声道数据拼成一个32bit数据在FIFO中进行存储，左声道16bit数据占据高16位，右声道16bit数据占据低16位。这样可以提高FIFO的利用率，以提供更长时间的缓冲能力。&#13;在这种情况下，CPU向发送FIFO中写入数据时，按照如下顺序：向左声道FIFO写入一个32bit数据（左右声道各16bit合并成的一个32bit数据），再向右声道FIFO写入一个32bit数据，如此反复。 */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : 数据接收合并使能，只在I2S模式下且数据位宽为16bit时有效。
                                                             0：不使能；
                                                             1：使能。
                                                             该位为1时，左右声道数据拼成一个32bit数据在FIFO中进行存储，左声道16bit数据占据高16位，右声道16bit数据占据低16位。这样可以提高FIFO的利用率，以提供更长时间的缓冲能力。&#13;CPU从接收FIFO中读数据时，按照如下顺序：从左声道FIFO读出一个32bit数据（左右声道各16bit合并成的一个32bit数据），再从右声道FIFO读出一个32bit数据，如此反复。 */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : 发送FIFO禁止。
                                                             0：使能；
                                                             &#13;1：禁止。 */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : 接收FIFO禁止。
                                                             0：使能；
                                                             1：禁止。 */
        unsigned int  tx_enable         : 1;  /* bit[12]   : 发送通道使能。
                                                             0：禁止；
                                                             &#13;1：使能。 */
        unsigned int  rx_enable         : 1;  /* bit[13]   : 接收通道使能。
                                                             0：禁止；
                                                             &#13;1：使能。 */
        unsigned int  intr_en           : 1;  /* bit[14]   : 中断全局使能。
                                                             0：禁止；
                                                             &#13;1：使能。 */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCM通道复位，低电平有效。
                                                             它对I2S/PCM接收和发送模块（包括FIFO）进行复位，因此发送和接收FIFO状态寄存器会变为0。但不会复位CPU接口寄存器模块。 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留。 */
    } bits;
    unsigned int      u32;
} HI_SIO_CT_CLR_T;

/********************************************************************************/
/*    sio 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/

#endif // __HI_SIO_H__

