/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_spi_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:23:11
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_SPI.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_SPI_INTERFACE_H__
#define __SOC_SPI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_spi
 ****************************************************************************/
/* 寄存器说明：控制寄存器0。
   位域定义UNION结构:  SOC_SPI_SPICR0_UNION */
#define SOC_SPI_SPICR0_ADDR(base)                     ((base) + (0x000))

/* 寄存器说明：控制寄存器1。
   位域定义UNION结构:  SOC_SPI_SPICR1_UNION */
#define SOC_SPI_SPICR1_ADDR(base)                     ((base) + (0x004))

/* 寄存器说明：数据寄存器。
   位域定义UNION结构:  SOC_SPI_SPIDR_UNION */
#define SOC_SPI_SPIDR_ADDR(base)                      ((base) + (0x008))

/* 寄存器说明：状态寄存器。
   位域定义UNION结构:  SOC_SPI_SPISR_UNION */
#define SOC_SPI_SPISR_ADDR(base)                      ((base) + (0x00C))

/* 寄存器说明：时钟分频寄存器。
   位域定义UNION结构:  SOC_SPI_SPICPSR_UNION */
#define SOC_SPI_SPICPSR_ADDR(base)                    ((base) + (0x010))

/* 寄存器说明：中断屏蔽寄存器。
            值“0”表示屏蔽中断，值“1”表示不屏蔽中断。
   位域定义UNION结构:  SOC_SPI_SPIIMSC_UNION */
#define SOC_SPI_SPIIMSC_ADDR(base)                    ((base) + (0x014))

/* 寄存器说明：原始中断状态寄存器。
            值“0”表示无中断，值“1”表示有中断。
   位域定义UNION结构:  SOC_SPI_SPIRIS_UNION */
#define SOC_SPI_SPIRIS_ADDR(base)                     ((base) + (0x018))

/* 寄存器说明：屏蔽后中断状态寄存器。
            值“0”表示无中断，值“1”表示有中断。
   位域定义UNION结构:  SOC_SPI_SPIMIS_UNION */
#define SOC_SPI_SPIMIS_ADDR(base)                     ((base) + (0x01C))

/* 寄存器说明：中断清除寄存器。
   位域定义UNION结构:  SOC_SPI_SPIICR_UNION */
#define SOC_SPI_SPIICR_ADDR(base)                     ((base) + (0x020))

/* 寄存器说明：DMA控制寄存器。
   位域定义UNION结构:  SOC_SPI_SPIDMACR_UNION */
#define SOC_SPI_SPIDMACR_ADDR(base)                   ((base) + (0x024))

/* 寄存器说明：发送FIFO控制寄存器。
   位域定义UNION结构:  SOC_SPI_SPITXFIFOCR_UNION */
#define SOC_SPI_SPITXFIFOCR_ADDR(base)                ((base) + (0x028))

/* 寄存器说明：接收FIFO控制寄存器。
   位域定义UNION结构:  SOC_SPI_SPIRXFIFOCR_UNION */
#define SOC_SPI_SPIRXFIFOCR_ADDR(base)                ((base) + (0x02C))





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
                     (1/1) register_spi
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_SPI_SPICR0_UNION
 结构说明  : SPICR0 寄存器结构定义。地址偏移量:0x000，初值:0x0000，宽度:16
 寄存器说明: 控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dss : 4;  /* bit[0-3] : 设置数据位宽。
                                                0011：4bit； 1000：9bit； 1101：14bit；
                                                0100：5bit； 1001：10bit； 1110：15bit；
                                                0101：6bit； 1010：11bit； 1111：16bit；
                                                0110：7bit； 1011：12bit； 其他：保留。
                                                0111：8bit； 1100：13bit；  */
        unsigned short  frf : 2;  /* bit[4-5] : 帧格式。
                                                00：SPI帧格式；
                                                其他：保留。 */
        unsigned short  spo : 1;  /* bit[6]   : SPICLKOUT极性，具体含义请参见SPI帧格式。 */
        unsigned short  sph : 1;  /* bit[7]   : SPICLKOUT相位含义请参见SPI帧格式。 */
        unsigned short  scr : 8;  /* bit[8-15]: 串行时钟率，取值范围0～255。SCR的值用来产生SPI发送和接收的比特率，公式为FSPICLK/（CPSDVSR×（1+SCR））。
                                                CPSDVSR是一个2～254之间的偶数，由寄存器SPICPSR配置。 */
    } reg;
} SOC_SPI_SPICR0_UNION;
#endif
#define SOC_SPI_SPICR0_dss_START  (0)
#define SOC_SPI_SPICR0_dss_END    (3)
#define SOC_SPI_SPICR0_frf_START  (4)
#define SOC_SPI_SPICR0_frf_END    (5)
#define SOC_SPI_SPICR0_spo_START  (6)
#define SOC_SPI_SPICR0_spo_END    (6)
#define SOC_SPI_SPICR0_sph_START  (7)
#define SOC_SPI_SPICR0_sph_END    (7)
#define SOC_SPI_SPICR0_scr_START  (8)
#define SOC_SPI_SPICR0_scr_END    (15)


/*****************************************************************************
 结构名    : SOC_SPI_SPICR1_UNION
 结构说明  : SPICR1 寄存器结构定义。地址偏移量:0x004，初值:0x0000，宽度:16
 寄存器说明: 控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  lbm      : 1;  /* bit[0]   : 设置环回模式。
                                                     0：正常的串行接口操作使能；
                                                     1：发送串行移位寄存器的输出在内部连接到接收串行移位寄存器的输入上。 */
        unsigned short  sse      : 1;  /* bit[1]   : 设置SPI使能。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned short  ms       : 1;  /* bit[2]   : 设置Master或者Slave模式，此位只能在SPI被禁止时改变。
                                                     0：Master模式（默认）；
                                                     1：保留。 */
        unsigned short  reserved : 13; /* bit[3-15]: 保留。 */
    } reg;
} SOC_SPI_SPICR1_UNION;
#endif
#define SOC_SPI_SPICR1_lbm_START       (0)
#define SOC_SPI_SPICR1_lbm_END         (0)
#define SOC_SPI_SPICR1_sse_START       (1)
#define SOC_SPI_SPICR1_sse_END         (1)
#define SOC_SPI_SPICR1_ms_START        (2)
#define SOC_SPI_SPICR1_ms_END          (2)


/*****************************************************************************
 结构名    : SOC_SPI_SPIDR_UNION
 结构说明  : SPIDR 寄存器结构定义。地址偏移量:0x008，初值:0x0000，宽度:16
 寄存器说明: 数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  data : 16; /* bit[0-15]: 发送/接收FIFO。
                                                 读：接收FIFO；
                                                 写：发送FIFO。
                                                 如果数据比特数少于16则必须右对齐。发送逻辑将忽略高位未使用的比特位，接收逻辑则自动将数据右对齐。 */
    } reg;
} SOC_SPI_SPIDR_UNION;
#endif
#define SOC_SPI_SPIDR_data_START  (0)
#define SOC_SPI_SPIDR_data_END    (15)


/*****************************************************************************
 结构名    : SOC_SPI_SPISR_UNION
 结构说明  : SPISR 寄存器结构定义。地址偏移量:0x00C，初值:0x0003，宽度:16
 寄存器说明: 状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  tfe      : 1;  /* bit[0]   : 发送FIFO是否已空。
                                                     0：未空；
                                                     1：已空。 */
        unsigned short  tnf      : 1;  /* bit[1]   : 发送FIFO是否未满。
                                                     0：已满；
                                                     1：未满。 */
        unsigned short  rne      : 1;  /* bit[2]   : 接收FIFO是否未空。
                                                     0：已空；
                                                     1：未空。 */
        unsigned short  rff      : 1;  /* bit[3]   : 接收FIFO是否已满。
                                                     0：未满；
                                                     1：已满。 */
        unsigned short  bsy      : 1;  /* bit[4]   : SPI忙标记。
                                                     0：空闲；
                                                     1：忙。 */
        unsigned short  reserved : 11; /* bit[5-15]: 保留。 */
    } reg;
} SOC_SPI_SPISR_UNION;
#endif
#define SOC_SPI_SPISR_tfe_START       (0)
#define SOC_SPI_SPISR_tfe_END         (0)
#define SOC_SPI_SPISR_tnf_START       (1)
#define SOC_SPI_SPISR_tnf_END         (1)
#define SOC_SPI_SPISR_rne_START       (2)
#define SOC_SPI_SPISR_rne_END         (2)
#define SOC_SPI_SPISR_rff_START       (3)
#define SOC_SPI_SPISR_rff_END         (3)
#define SOC_SPI_SPISR_bsy_START       (4)
#define SOC_SPI_SPISR_bsy_END         (4)


/*****************************************************************************
 结构名    : SOC_SPI_SPICPSR_UNION
 结构说明  : SPICPSR 寄存器结构定义。地址偏移量:0x010，初值:0x0000，宽度:16
 寄存器说明: 时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cpsdvsr  : 8;  /* bit[0-7] : 时钟分频因子。此值必须是2～254之间的偶数，取决于输入时钟SPICLK的频率。最低位读作“0”。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_SPI_SPICPSR_UNION;
#endif
#define SOC_SPI_SPICPSR_cpsdvsr_START   (0)
#define SOC_SPI_SPICPSR_cpsdvsr_END     (7)


/*****************************************************************************
 结构名    : SOC_SPI_SPIIMSC_UNION
 结构说明  : SPIIMSC 寄存器结构定义。地址偏移量:0x014，初值:0x0000，宽度:16
 寄存器说明: 中断屏蔽寄存器。
            值“0”表示屏蔽中断，值“1”表示不屏蔽中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rorim    : 1;  /* bit[0]   : 接收溢出中断屏蔽。
                                                     0：接收FIFO溢出中断屏蔽；
                                                     1：接收FIFO溢出中断不屏蔽。 */
        unsigned short  rtim     : 1;  /* bit[1]   : 接收超时中断。
                                                     0：接收超时中断屏蔽；
                                                     1：接收超时中断不屏蔽。 */
        unsigned short  rxim     : 1;  /* bit[2]   : 接收FIFO中断屏蔽。
                                                     0：半空或更少情况下中断被屏蔽；
                                                     1：半空或更少情况下中断未被屏蔽。 */
        unsigned short  txim     : 1;  /* bit[3]   : 发送FIFO中断屏蔽。
                                                     0：半空或更少情况下中断被屏蔽；
                                                     1：半空或更少情况下中断未被屏蔽。 */
        unsigned short  reserved : 12; /* bit[4-15]: 保留。 */
    } reg;
} SOC_SPI_SPIIMSC_UNION;
#endif
#define SOC_SPI_SPIIMSC_rorim_START     (0)
#define SOC_SPI_SPIIMSC_rorim_END       (0)
#define SOC_SPI_SPIIMSC_rtim_START      (1)
#define SOC_SPI_SPIIMSC_rtim_END        (1)
#define SOC_SPI_SPIIMSC_rxim_START      (2)
#define SOC_SPI_SPIIMSC_rxim_END        (2)
#define SOC_SPI_SPIIMSC_txim_START      (3)
#define SOC_SPI_SPIIMSC_txim_END        (3)


/*****************************************************************************
 结构名    : SOC_SPI_SPIRIS_UNION
 结构说明  : SPIRIS 寄存器结构定义。地址偏移量:0x018，初值:0x0008，宽度:16
 寄存器说明: 原始中断状态寄存器。
            值“0”表示无中断，值“1”表示有中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rorris   : 1;  /* bit[0]   : 接收溢出中断的原始中断状态。 */
        unsigned short  rtris    : 1;  /* bit[1]   : 接收超时中断的原始中断状态。 */
        unsigned short  rxris    : 1;  /* bit[2]   : 接收FIFO中断的原始中断状态。 */
        unsigned short  txris    : 1;  /* bit[3]   : 发送FIFO中断的原始中断状态。 */
        unsigned short  reserved : 12; /* bit[4-15]: 保留。 */
    } reg;
} SOC_SPI_SPIRIS_UNION;
#endif
#define SOC_SPI_SPIRIS_rorris_START    (0)
#define SOC_SPI_SPIRIS_rorris_END      (0)
#define SOC_SPI_SPIRIS_rtris_START     (1)
#define SOC_SPI_SPIRIS_rtris_END       (1)
#define SOC_SPI_SPIRIS_rxris_START     (2)
#define SOC_SPI_SPIRIS_rxris_END       (2)
#define SOC_SPI_SPIRIS_txris_START     (3)
#define SOC_SPI_SPIRIS_txris_END       (3)


/*****************************************************************************
 结构名    : SOC_SPI_SPIMIS_UNION
 结构说明  : SPIMIS 寄存器结构定义。地址偏移量:0x01C，初值:0x0000，宽度:16
 寄存器说明: 屏蔽后中断状态寄存器。
            值“0”表示无中断，值“1”表示有中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rormis   : 1;  /* bit[0]   : 接收溢出中断屏蔽后的状态。 */
        unsigned short  rtmis    : 1;  /* bit[1]   : 接收超时中断屏蔽后的状态。 */
        unsigned short  rxmis    : 1;  /* bit[2]   : 接收FIFO中断屏蔽后的状态。 */
        unsigned short  txmis    : 1;  /* bit[3]   : 发送FIFO中断屏蔽后的状态。 */
        unsigned short  reserved : 12; /* bit[4-15]: 保留。 */
    } reg;
} SOC_SPI_SPIMIS_UNION;
#endif
#define SOC_SPI_SPIMIS_rormis_START    (0)
#define SOC_SPI_SPIMIS_rormis_END      (0)
#define SOC_SPI_SPIMIS_rtmis_START     (1)
#define SOC_SPI_SPIMIS_rtmis_END       (1)
#define SOC_SPI_SPIMIS_rxmis_START     (2)
#define SOC_SPI_SPIMIS_rxmis_END       (2)
#define SOC_SPI_SPIMIS_txmis_START     (3)
#define SOC_SPI_SPIMIS_txmis_END       (3)


/*****************************************************************************
 结构名    : SOC_SPI_SPIICR_UNION
 结构说明  : SPIICR 寄存器结构定义。地址偏移量:0x020，初值:0x0000，宽度:16
 寄存器说明: 中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  roric    : 1;  /* bit[0]   : 清除接收溢出中断。 */
        unsigned short  rtic     : 1;  /* bit[1]   : 清除接收超时中断。 */
        unsigned short  reserved : 14; /* bit[2-15]: 保留。 */
    } reg;
} SOC_SPI_SPIICR_UNION;
#endif
#define SOC_SPI_SPIICR_roric_START     (0)
#define SOC_SPI_SPIICR_roric_END       (0)
#define SOC_SPI_SPIICR_rtic_START      (1)
#define SOC_SPI_SPIICR_rtic_END        (1)


/*****************************************************************************
 结构名    : SOC_SPI_SPIDMACR_UNION
 结构说明  : SPIDMACR 寄存器结构定义。地址偏移量:0x024，初值:0x0000，宽度:16
 寄存器说明: DMA控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxdmae   : 1;  /* bit[0]   : DMA接收FIFO使能寄存器。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  txdmae   : 1;  /* bit[1]   : DMA发送FIFO使能寄存器。
                                                     0：禁止；
                                                     1：使能。 */
        unsigned short  reserved : 14; /* bit[2-15]: 保留。 */
    } reg;
} SOC_SPI_SPIDMACR_UNION;
#endif
#define SOC_SPI_SPIDMACR_rxdmae_START    (0)
#define SOC_SPI_SPIDMACR_rxdmae_END      (0)
#define SOC_SPI_SPIDMACR_txdmae_START    (1)
#define SOC_SPI_SPIDMACR_txdmae_END      (1)


/*****************************************************************************
 结构名    : SOC_SPI_SPITXFIFOCR_UNION
 结构说明  : SPITXFIFOCR 寄存器结构定义。地址偏移量:0x028，初值:0x0009，宽度:16
 寄存器说明: 发送FIFO控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dmatxbrsize : 3;  /* bit[0-2] : 配置发送FIFO请求DMA进行burst传输的水线。即，发送FIFO中数据数目小于或等于dmatxbrsize所配置的字数时，DMATXBREQ有效。
                                                        000：255；
                                                        001：252；
                                                        010：248；
                                                        011：240；
                                                        100：224；
                                                        101：192；
                                                        110：192；
                                                        111：192。 */
        unsigned short  txintsize   : 3;  /* bit[3-5] : 配置发送FIFO请求中断的水线。即，发送FIFO中数据数目小于或等于TXINTSize所配置的字数时，TXRIS有效。
                                                        000：1；
                                                        001：4；
                                                        010：8；
                                                        011：16；
                                                        100：32；
                                                        101：64；
                                                        110：128；
                                                        111：128。 */
        unsigned short  reserved    : 10; /* bit[6-15]: 保留。 */
    } reg;
} SOC_SPI_SPITXFIFOCR_UNION;
#endif
#define SOC_SPI_SPITXFIFOCR_dmatxbrsize_START  (0)
#define SOC_SPI_SPITXFIFOCR_dmatxbrsize_END    (2)
#define SOC_SPI_SPITXFIFOCR_txintsize_START    (3)
#define SOC_SPI_SPITXFIFOCR_txintsize_END      (5)


/*****************************************************************************
 结构名    : SOC_SPI_SPIRXFIFOCR_UNION
 结构说明  : SPIRXFIFOCR 寄存器结构定义。地址偏移量:0x02C，初值:0x0009，宽度:16
 寄存器说明: 接收FIFO控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dmarxbrsize : 3;  /* bit[0-2] : 配置接收FIFO请求DMA进行burst传输的水线。即，接收FIFO中数据数目大于或等于dmarxbrsize所配置的字数时，DMARXBREQ有效，此处字长是16位。
                                                        000：1；
                                                        001：4；
                                                        010：8；
                                                        011：16；
                                                        100：32；
                                                        101：64；
                                                        110：64；
                                                        111：64。 */
        unsigned short  rxintsize   : 3;  /* bit[3-5] : 配置接收FIFO请求中断的水线。即，接收FIFO中数据数目大于或等于rxintsize所配置的字数时，RXRIS有效。
                                                        000：255；
                                                        001：252；
                                                        010：248；
                                                        011：240；
                                                        100：224；
                                                        101：192；
                                                        110：128；
                                                        111：32。 */
        unsigned short  reserved    : 10; /* bit[6-15]: 保留。 */
    } reg;
} SOC_SPI_SPIRXFIFOCR_UNION;
#endif
#define SOC_SPI_SPIRXFIFOCR_dmarxbrsize_START  (0)
#define SOC_SPI_SPIRXFIFOCR_dmarxbrsize_END    (2)
#define SOC_SPI_SPIRXFIFOCR_rxintsize_START    (3)
#define SOC_SPI_SPIRXFIFOCR_rxintsize_END      (5)






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

#endif /* end of soc_spi_interface.h */
