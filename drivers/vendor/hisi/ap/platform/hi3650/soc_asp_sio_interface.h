/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_asp_sio_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:16
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ASP_SIO.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ASP_SIO_INTERFACE_H__
#define __SOC_ASP_SIO_INTERFACE_H__

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
/* 寄存器说明：版本寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_VERSION_UNION */
#define SOC_ASP_SIO_SIO_VERSION_ADDR(base)            ((base) + (0x03C))

/* 寄存器说明：模式寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_MODE_UNION */
#define SOC_ASP_SIO_SIO_MODE_ADDR(base)               ((base) + (0x040))

/* 寄存器说明：中断状态寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_INTSTATUS_UNION */
#define SOC_ASP_SIO_SIO_INTSTATUS_ADDR(base)          ((base) + (0x044))

/* 寄存器说明：中断清除寄存器.
   位域定义UNION结构:  SOC_ASP_SIO_SIO_INTCLR_UNION */
#define SOC_ASP_SIO_SIO_INTCLR_ADDR(base)             ((base) + (0x048))

/* 寄存器说明：I2S模式下左声道数据发送寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_LEFT_XD_UNION */
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_ADDR(base)        ((base) + (0x04C))

/* 寄存器说明：I2S模式下右声道数据发送寄存器/PCM模式下的数据发送寄存器SIO_PCM_XD
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_RIGHT_XD_UNION */
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_ADDR(base)       ((base) + (0x050))

/* 寄存器说明：I2S模式下左声道数据接收寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_LEFT_RD_UNION */
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_ADDR(base)        ((base) + (0x054))

/* 寄存器说明：I2S模式下右声道数据接收寄存器/PCM模式下接收数据寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_RIGHT_RD_UNION */
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_ADDR(base)       ((base) + (0x058))

/* 寄存器说明：控制寄存器使能寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_CT_SET_UNION */
#define SOC_ASP_SIO_SIO_CT_SET_ADDR(base)             ((base) + (0x05C))

/* 寄存器说明：控制寄存器清除寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_CT_CLR_UNION */
#define SOC_ASP_SIO_SIO_CT_CLR_ADDR(base)             ((base) + (0x060))

/* 寄存器说明：SIO接收状态寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_RX_STA_UNION */
#define SOC_ASP_SIO_SIO_RX_STA_ADDR(base)             ((base) + (0x068))

/* 寄存器说明：SIO发送状态寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_TX_STA_UNION */
#define SOC_ASP_SIO_SIO_TX_STA_ADDR(base)             ((base) + (0x06C))

/* 寄存器说明：数据宽度寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_DATA_WIDTH_SET_UNION */
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_ADDR(base)     ((base) + (0x078))

/* 寄存器说明：I2S左右声道起始位置配置控制寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_START_POS_UNION */
#define SOC_ASP_SIO_SIO_I2S_START_POS_ADDR(base)      ((base) + (0x07C))

/* 寄存器说明：I2S左右声道操作当前位置状态寄存器
   位域定义UNION结构:  SOC_ASP_SIO_I2S_POS_FLAG_UNION */
#define SOC_ASP_SIO_I2S_POS_FLAG_ADDR(base)           ((base) + (0x080))

/* 寄存器说明：高位数据符号扩展使能寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_SIGNED_EXT_UNION */
#define SOC_ASP_SIO_SIO_SIGNED_EXT_ADDR(base)         ((base) + (0x084))

/* 寄存器说明：I2S左右声道数据合并使能寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_UNION */
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_ADDR(base)   ((base) + (0x088))

/* 寄存器说明：中断屏蔽寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_INTMASK_UNION */
#define SOC_ASP_SIO_SIO_INTMASK_ADDR(base)            ((base) + (0x08C))

/* 寄存器说明：接收合并数据寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_UNION */
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_ADDR(base)    ((base) + (0x0A0))

/* 寄存器说明：发送合并数据寄存器
   位域定义UNION结构:  SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_UNION */
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_ADDR(base)    ((base) + (0x0C0))





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
 结构名    : SOC_ASP_SIO_SIO_VERSION_UNION
 结构说明  : SIO_VERSION 寄存器结构定义。地址偏移量:0x03C，初值:0x00000013，宽度:32
 寄存器说明: 版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version  : 8;  /* bit[0-7] : sio的版本号 */
        unsigned int  sio_loop : 1;  /* bit[8]   : SIO循环和正常模式选择。
                                                   0：正常模式；
                                                   1：SIO发送和接收数据环回模式。用于SIO的自测试。在该模式下，在SIO的对外接口处，SIO接收串行数据线与SIO发送串行数据线直接相连。 */
        unsigned int  reserved : 23; /* bit[9-31]: 版本寄存器，用来记录SIO的版本号和进行SIO的 */
    } reg;
} SOC_ASP_SIO_SIO_VERSION_UNION;
#endif
#define SOC_ASP_SIO_SIO_VERSION_version_START   (0)
#define SOC_ASP_SIO_SIO_VERSION_version_END     (7)
#define SOC_ASP_SIO_SIO_VERSION_sio_loop_START  (8)
#define SOC_ASP_SIO_SIO_VERSION_sio_loop_END    (8)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_MODE_UNION
 结构说明  : SIO_MODE 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 模式寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio_mode   : 1;  /* bit[0]   : PCM/I2S模式选择。
                                                     0：I2S模式；
                                                     1：PCM模式。 */
        unsigned int  pcm_mode   : 1;  /* bit[1]   : PCM时序模式。
                                                     0：标准模式；
                                                     1：自定义模式。 */
        unsigned int  reserved_0 : 1;  /* bit[2]   : 保留，必须配置为0。 */
        unsigned int  ext_rec_en : 1;  /* bit[3]   : 标准模式下，I2S接收两个声道的数据，即左声道和右声道。PCM只接收一个声道的数据。
                                                     多路接收模式下，对于I2S或PCM，接收通道数可以配置。该模式下，通道的数据宽度必须为8bit或16bit。
                                                     0：标准的I2S或PCM接收模式；
                                                     1：扩展的I2S或PCM多路接收模式。 */
        unsigned int  chn_num    : 2;  /* bit[4-5] : 多路接收的通道数选择。
                                                     00：2 chn；
                                                     01：4 chn；
                                                     10：8 chn；
                                                     11：16 chn。. */
        unsigned int  clk_edge   : 1;  /* bit[6]   : PCM多路接收模式下，采样数据时钟边沿选择。
                                                     0：下降沿有效；
                                                     1：上升沿有效。 */
        unsigned int  reserved_1 : 25; /* bit[7-31]: 用来选择SIO的工作模式 */
    } reg;
} SOC_ASP_SIO_SIO_MODE_UNION;
#endif
#define SOC_ASP_SIO_SIO_MODE_sio_mode_START    (0)
#define SOC_ASP_SIO_SIO_MODE_sio_mode_END      (0)
#define SOC_ASP_SIO_SIO_MODE_pcm_mode_START    (1)
#define SOC_ASP_SIO_SIO_MODE_pcm_mode_END      (1)
#define SOC_ASP_SIO_SIO_MODE_ext_rec_en_START  (3)
#define SOC_ASP_SIO_SIO_MODE_ext_rec_en_END    (3)
#define SOC_ASP_SIO_SIO_MODE_chn_num_START     (4)
#define SOC_ASP_SIO_SIO_MODE_chn_num_END       (5)
#define SOC_ASP_SIO_SIO_MODE_clk_edge_START    (6)
#define SOC_ASP_SIO_SIO_MODE_clk_edge_END      (6)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_INTSTATUS_UNION
 结构说明  : SIO_INTSTATUS 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : 接收FIFO低于阈值中断清除 0：未产生中断； 1：已产生中断； */
        unsigned int  tx_intr             : 1;  /* bit[1]   : 发送FIFO低于阈值中断清除 0：未产生中断； 1：已产生中断； */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2S模式下，左声道发送FIFO上溢中断，PCM模式下无效 0：未产生中断； 1：已产生中断； */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2S模式下，左声道发送FIFO上溢中断，PCM模式下无效 0：未产生中断； 1：已产生中断； */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2S模式下，右声道发送FIFO下溢中断，PCM模式下无效 0：未产生中断； 1：已产生中断； */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2S模式下，左声道发送FIFO下溢中断，PCM模式下无效 0：未产生中断； 1：已产生中断； */
        unsigned int  reserved            : 26; /* bit[6-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_INTSTATUS_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_intr_START              (0)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_intr_END                (0)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_intr_START              (1)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_intr_END                (1)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_right_fifo_over_START   (2)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_right_fifo_over_END     (2)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_left_fifo_over_START    (3)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_left_fifo_over_END      (3)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_right_fifo_under_START  (4)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_right_fifo_under_END    (4)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_left_fifo_under_START   (5)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_left_fifo_under_END     (5)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_INTCLR_UNION
 结构说明  : SIO_INTCLR 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : 接收FIFO低于阈值中断清除 */
        unsigned int  tx_intr             : 1;  /* bit[1]   : 发送FIFO低于阈值中断清除 */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2S模式下，左声道发送FIFO上溢中断，PCM模式下无效 */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2S模式下，左声道发送FIFO上溢中断，PCM模式下无效 */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2S模式下，右声道发送FIFO下溢中断，PCM模式下无效 */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2S模式下，左声道发送FIFO下溢中断，PCM模式下无效 */
        unsigned int  reserved            : 26; /* bit[6-31]: 按位清除寄存器 */
    } reg;
} SOC_ASP_SIO_SIO_INTCLR_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTCLR_rx_intr_START              (0)
#define SOC_ASP_SIO_SIO_INTCLR_rx_intr_END                (0)
#define SOC_ASP_SIO_SIO_INTCLR_tx_intr_START              (1)
#define SOC_ASP_SIO_SIO_INTCLR_tx_intr_END                (1)
#define SOC_ASP_SIO_SIO_INTCLR_rx_right_fifo_over_START   (2)
#define SOC_ASP_SIO_SIO_INTCLR_rx_right_fifo_over_END     (2)
#define SOC_ASP_SIO_SIO_INTCLR_rx_left_fifo_over_START    (3)
#define SOC_ASP_SIO_SIO_INTCLR_rx_left_fifo_over_END      (3)
#define SOC_ASP_SIO_SIO_INTCLR_tx_right_fifo_under_START  (4)
#define SOC_ASP_SIO_SIO_INTCLR_tx_right_fifo_under_END    (4)
#define SOC_ASP_SIO_SIO_INTCLR_tx_left_fifo_under_START   (5)
#define SOC_ASP_SIO_SIO_INTCLR_tx_left_fifo_under_END     (5)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_LEFT_XD_UNION
 结构说明  : SIO_I2S_LEFT_XD 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: I2S模式下左声道数据发送寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_left_data : 32; /* bit[0-31]: I2S模式下左声道数据发送寄存器，有效数据放在寄存器的低bit区域，超出有效宽度的bit位由SIO模块自动置0。 */
    } reg;
} SOC_ASP_SIO_SIO_I2S_LEFT_XD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_tx_left_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_tx_left_data_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_RIGHT_XD_UNION
 结构说明  : SIO_I2S_RIGHT_XD 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: I2S模式下右声道数据发送寄存器/PCM模式下的数据发送寄存器SIO_PCM_XD
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_right_data : 32; /* bit[0-31]: I2S模式下右声道数据发送寄存器，有效数据放在寄存器的低bit区域，超出有效宽度的bit位由SIO模块自动置0；PCM模式下数据发送寄存器，只有[15:0]有效作为信号tx_data */
    } reg;
} SOC_ASP_SIO_SIO_I2S_RIGHT_XD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_tx_right_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_tx_right_data_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_LEFT_RD_UNION
 结构说明  : SIO_I2S_LEFT_RD 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: I2S模式下左声道数据接收寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_left_data : 32; /* bit[0-31]: I2S左声道数据接收寄存器，有效数据放在寄存器的低bit区域，超出有效数据宽度的bit位自动置0 */
    } reg;
} SOC_ASP_SIO_SIO_I2S_LEFT_RD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_rx_left_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_rx_left_data_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_RIGHT_RD_UNION
 结构说明  : SIO_I2S_RIGHT_RD 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: I2S模式下右声道数据接收寄存器/PCM模式下接收数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_right_data : 32; /* bit[0-31]: I2S右声道数据接收寄存器，有效数据放在寄存器的低bit区域，超出有效数据宽度的bit位自动置0；PCM模式下数据接收寄存器，只有[15:0]有效作为信号rx_data */
    } reg;
} SOC_ASP_SIO_SIO_I2S_RIGHT_RD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_rx_right_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_rx_right_data_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_CT_SET_UNION
 结构说明  : SIO_CT_SET 寄存器结构定义。地址偏移量:0x05C，初值:0x00008000，宽度:32
 寄存器说明: 控制寄存器使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : 发送FIFO阈值，超过阈值会报发送中断和DMA请求 */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : 接收FIFO阈值，超过阈值会报接收中断和DMA请求 */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : I2S模式下发送的数据合并使能，仅限16bit位宽 0：禁止 1：左右声道合并成一个32bit数据存在FIFO中，左声道占据高16bit */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : I2S模式下接收的数据合并使能，仅限16bit位宽 0：禁止 1：左右声道合并成一个32bit数据存在FIFO中，左声道占据高16bit */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : 发送FIFO禁止 0：使能，1：禁止 */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : 接收FIFO禁止 0：使能，1：禁止 */
        unsigned int  tx_enable         : 1;  /* bit[12]   : 发送通道使能 0：禁止，1：使能 */
        unsigned int  rx_enable         : 1;  /* bit[13]   : 接收通道使能 0：禁止，1：使能 */
        unsigned int  intr_en           : 1;  /* bit[14]   : 中断全局使能 0：禁止，1：使能 */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCM通道复位，低电平有效（不会复位CPU接口寄存器） */
        unsigned int  reserved          : 16; /* bit[16-31]: SIO控制寄存器，与SIO清除寄存器的控制对象一致 */
    } reg;
} SOC_ASP_SIO_SIO_CT_SET_UNION;
#endif
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_threshold_START  (0)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_threshold_END    (3)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_threshold_START  (4)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_threshold_END    (7)
#define SOC_ASP_SIO_SIO_CT_SET_tx_data_merge_en_START   (8)
#define SOC_ASP_SIO_SIO_CT_SET_tx_data_merge_en_END     (8)
#define SOC_ASP_SIO_SIO_CT_SET_rx_data_merge_en_START   (9)
#define SOC_ASP_SIO_SIO_CT_SET_rx_data_merge_en_END     (9)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_disable_START    (10)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_disable_END      (10)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_disable_START    (11)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_disable_END      (11)
#define SOC_ASP_SIO_SIO_CT_SET_tx_enable_START          (12)
#define SOC_ASP_SIO_SIO_CT_SET_tx_enable_END            (12)
#define SOC_ASP_SIO_SIO_CT_SET_rx_enable_START          (13)
#define SOC_ASP_SIO_SIO_CT_SET_rx_enable_END            (13)
#define SOC_ASP_SIO_SIO_CT_SET_intr_en_START            (14)
#define SOC_ASP_SIO_SIO_CT_SET_intr_en_END              (14)
#define SOC_ASP_SIO_SIO_CT_SET_rst_n_START              (15)
#define SOC_ASP_SIO_SIO_CT_SET_rst_n_END                (15)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_CT_CLR_UNION
 结构说明  : SIO_CT_CLR 寄存器结构定义。地址偏移量:0x060，初值:0x00008000，宽度:32
 寄存器说明: 控制寄存器清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : 发送FIFO阈值，超过阈值会报发送中断和DMA请求 */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : 接收FIFO阈值，超过阈值会报接收中断和DMA请求 */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : I2S模式下发送的数据合并使能，仅限16bit位宽 0：禁止 1：左右声道合并成一个32bit数据存在FIFO中，左声道占据高16bit */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : I2S模式下接收的数据合并使能，仅限16bit位宽 0：禁止 1：左右声道合并成一个32bit数据存在FIFO中，左声道占据高16bit */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : 发送FIFO禁止 0：使能，1：禁止 */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : 接收FIFO禁止 0：使能，1：禁止 */
        unsigned int  tx_enable         : 1;  /* bit[12]   : 发送通道使能 0：禁止，1：使能 */
        unsigned int  rx_enable         : 1;  /* bit[13]   : 接收通道使能 0：禁止，1：使能 */
        unsigned int  intr_en           : 1;  /* bit[14]   : 中断全局使能 0：禁止，1：使能 */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCM通道复位，低电平有效（不会复位CPU接口寄存器） */
        unsigned int  reserved          : 16; /* bit[16-31]: SIO清除寄存器，与SIO控制寄存器的控制对象一致 */
    } reg;
} SOC_ASP_SIO_SIO_CT_CLR_UNION;
#endif
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_threshold_START  (0)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_threshold_END    (3)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_threshold_START  (4)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_threshold_END    (7)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_data_merge_en_START   (8)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_data_merge_en_END     (8)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_data_merge_en_START   (9)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_data_merge_en_END     (9)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_disable_START    (10)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_disable_END      (10)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_disable_START    (11)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_disable_END      (11)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_enable_START          (12)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_enable_END            (12)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_enable_START          (13)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_enable_END            (13)
#define SOC_ASP_SIO_SIO_CT_CLR_intr_en_START            (14)
#define SOC_ASP_SIO_SIO_CT_CLR_intr_en_END              (14)
#define SOC_ASP_SIO_SIO_CT_CLR_rst_n_START              (15)
#define SOC_ASP_SIO_SIO_CT_CLR_rst_n_END                (15)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_RX_STA_UNION
 结构说明  : SIO_RX_STA 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: SIO接收状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_right_depth : 5;  /* bit[0-4]  : RX右声道FIFO深度 */
        unsigned int  rx_left_depth  : 5;  /* bit[5-9]  : RX左声道FIFO深度 */
        unsigned int  reserved       : 22; /* bit[10-31]: RX左右声道FIFO深度指示寄存器，FIFO深度为32 */
    } reg;
} SOC_ASP_SIO_SIO_RX_STA_UNION;
#endif
#define SOC_ASP_SIO_SIO_RX_STA_rx_right_depth_START  (0)
#define SOC_ASP_SIO_SIO_RX_STA_rx_right_depth_END    (4)
#define SOC_ASP_SIO_SIO_RX_STA_rx_left_depth_START   (5)
#define SOC_ASP_SIO_SIO_RX_STA_rx_left_depth_END     (9)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_TX_STA_UNION
 结构说明  : SIO_TX_STA 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: SIO发送状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_right_depth : 5;  /* bit[0-4]  : TX右声道FIFO深度 */
        unsigned int  tx_left_depth  : 5;  /* bit[5-9]  : TX左声道FIFO深度 */
        unsigned int  reserved       : 22; /* bit[10-31]: TX左右声道FIFO深度指示寄存器，FIFO深度为32 */
    } reg;
} SOC_ASP_SIO_SIO_TX_STA_UNION;
#endif
#define SOC_ASP_SIO_SIO_TX_STA_tx_right_depth_START  (0)
#define SOC_ASP_SIO_SIO_TX_STA_tx_right_depth_END    (4)
#define SOC_ASP_SIO_SIO_TX_STA_tx_left_depth_START   (5)
#define SOC_ASP_SIO_SIO_TX_STA_tx_left_depth_END     (9)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_DATA_WIDTH_SET_UNION
 结构说明  : SIO_DATA_WIDTH_SET 寄存器结构定义。地址偏移量:0x078，初值:0x00000009，宽度:32
 寄存器说明: 数据宽度寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_mode  : 3;  /* bit[0-2] : 发送数据长度配置位，对于I2S模式： 000保留； 001:16bit； 010:18bit； 011:20bit； 100:24bit； 101:32bit； 110-111保留 对于PCM模式： 000:8bit； 001:16bit； 010:32bit； 011:64bit； 100:128bit； 101-111保留  */
        unsigned int  rx_mode  : 3;  /* bit[3-5] : 接收数据长度配置位： 000:8bit； 001:16bit； 010:18bit； 011:20bit； 100:24bit； 101:32bit； 110-111保留 I2S模式不支持8bit，PCM模式只支持8bit和16bit */
        unsigned int  reserved_0: 2;  /* bit[6-7] :  */
        unsigned int  reserved_1: 24; /* bit[8-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_DATA_WIDTH_SET_UNION;
#endif
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_tx_mode_START   (0)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_tx_mode_END     (2)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_rx_mode_START   (3)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_rx_mode_END     (5)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_START_POS_UNION
 结构说明  : SIO_I2S_START_POS 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: I2S左右声道起始位置配置控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_pos_read  : 1;  /* bit[0]   : 读发送FIFO时由哪个声道开始访问： 0：左声道；1：右声道 */
        unsigned int  start_pos_write : 1;  /* bit[1]   : 写发送FIFO时由哪个声道开始访问： 0：左声道；1：右声道 */
        unsigned int  reserved        : 30; /* bit[2-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_I2S_START_POS_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_read_START   (0)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_read_END     (0)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_write_START  (1)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_write_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_I2S_POS_FLAG_UNION
 结构说明  : I2S_POS_FLAG 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: I2S左右声道操作当前位置状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_pos_read  : 1;  /* bit[0]   : 下一次读发送FIFO时由哪个声道开始访问：0：左声道；1：右声道 */
        unsigned int  start_pos_write : 1;  /* bit[1]   : 下一次写发送FIFO时由哪个声道开始访问：0：左声道；1：右声道 */
        unsigned int  reserved        : 30; /* bit[2-31]:  */
    } reg;
} SOC_ASP_SIO_I2S_POS_FLAG_UNION;
#endif
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_read_START   (0)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_read_END     (0)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_write_START  (1)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_write_END    (1)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_SIGNED_EXT_UNION
 结构说明  : SIO_SIGNED_EXT 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: 高位数据符号扩展使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  signed_ext_en : 1;  /* bit[0]   : 高位数据符号扩展： 0：禁止； 1：使能； */
        unsigned int  reserved      : 31; /* bit[1-31]: 符号位扩展只对接收数据有效，对发送数据无效，PCM模式和I2S模式下都支持该扩展，支持除32bit外其他位宽 */
    } reg;
} SOC_ASP_SIO_SIO_SIGNED_EXT_UNION;
#endif
#define SOC_ASP_SIO_SIO_SIGNED_EXT_signed_ext_en_START  (0)
#define SOC_ASP_SIO_SIO_SIGNED_EXT_signed_ext_en_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_UNION
 结构说明  : SIO_I2S_POS_MERGE_EN 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: I2S左右声道数据合并使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merge_on : 1;  /* bit[0]   : I2S模式下，左右声道数据操作地址合并 0：禁止； 1：使能； */
        unsigned int  reserved : 31; /* bit[1-31]: I2S模式下，左右声道数据操作地址合并使能 */
    } reg;
} SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_merge_on_START  (0)
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_merge_on_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_INTMASK_UNION
 结构说明  : SIO_INTMASK 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : 接收FIFO高于阈值中断屏蔽： 0：不屏蔽； 1：屏蔽； */
        unsigned int  tx_intr             : 1;  /* bit[1]   : 发送FIFO低于阈值中断屏蔽： 0：不屏蔽； 1：屏蔽； */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2S模式下，右声道接收FIFO上溢中断屏蔽，PCM模式下无效： 0：不屏蔽； 1：屏蔽； */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2S模式下，左声道接收FIFO上溢中断屏蔽，PCM模式下无效： 0：不屏蔽； 1：屏蔽； */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2S模式下，右声道发送FIFO下溢中断屏蔽，PCM模式下无效： 0：不屏蔽； 1：屏蔽； */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2S模式下，左声道发送FIFO下溢中断屏蔽，PCM模式下无效： 0：不屏蔽； 1：屏蔽； */
        unsigned int  reserved            : 26; /* bit[6-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_INTMASK_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTMASK_rx_intr_START              (0)
#define SOC_ASP_SIO_SIO_INTMASK_rx_intr_END                (0)
#define SOC_ASP_SIO_SIO_INTMASK_tx_intr_START              (1)
#define SOC_ASP_SIO_SIO_INTMASK_tx_intr_END                (1)
#define SOC_ASP_SIO_SIO_INTMASK_rx_right_fifo_over_START   (2)
#define SOC_ASP_SIO_SIO_INTMASK_rx_right_fifo_over_END     (2)
#define SOC_ASP_SIO_SIO_INTMASK_rx_left_fifo_over_START    (3)
#define SOC_ASP_SIO_SIO_INTMASK_rx_left_fifo_over_END      (3)
#define SOC_ASP_SIO_SIO_INTMASK_tx_right_fifo_under_START  (4)
#define SOC_ASP_SIO_SIO_INTMASK_tx_right_fifo_under_END    (4)
#define SOC_ASP_SIO_SIO_INTMASK_tx_left_fifo_under_START   (5)
#define SOC_ASP_SIO_SIO_INTMASK_tx_left_fifo_under_END     (5)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_UNION
 结构说明  : SIO_I2S_DUAL_RX_CHN 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: 接收合并数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_data : 32; /* bit[0-31]: 在I2S模式左右声道操作地址合并使能的条件下，作为读取接收数据的寄存器 */
    } reg;
} SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_rx_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_rx_data_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_UNION
 结构说明  : SIO_I2S_DUAL_TX_CHN 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: 发送合并数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_data : 32; /* bit[0-31]: 在I2S模式左右声道操作地址合并使能的条件下，作为写出发送数据的寄存器 */
    } reg;
} SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_tx_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_tx_data_END    (31)






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

#endif /* end of soc_asp_sio_interface.h */
