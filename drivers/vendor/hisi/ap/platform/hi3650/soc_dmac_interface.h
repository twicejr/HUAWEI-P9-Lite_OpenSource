/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dmac_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:19:53
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DMAC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DMAC_INTERFACE_H__
#define __SOC_DMAC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_dmac
 ****************************************************************************/
/* 寄存器说明：处理器X的中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_STAT_UNION */
#define SOC_DMAC_INT_STAT_ADDR(base, in)              ((base) + (0x0000+0x40*(in)))

/* 寄存器说明：处理器X的通道传输完成中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_TC1_UNION */
#define SOC_DMAC_INT_TC1_ADDR(base, in)               ((base) + (0x0004+0x40*(in)))

/* 寄存器说明：处理器X的链表节点传输完成中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_TC2_UNION */
#define SOC_DMAC_INT_TC2_ADDR(base, in)               ((base) + (0x0008+0x40*(in)))

/* 寄存器说明：处理器X的配置错误中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR1_UNION */
#define SOC_DMAC_INT_ERR1_ADDR(base, in)              ((base) + (0x000C+0x40*(in)))

/* 寄存器说明：处理器X的数据传输错误中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR2_UNION */
#define SOC_DMAC_INT_ERR2_ADDR(base, in)              ((base) + (0x0010+0x40*(in)))

/* 寄存器说明：处理器X的读链表错误中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR3_UNION */
#define SOC_DMAC_INT_ERR3_ADDR(base, in)              ((base) + (0x0014+0x40*(in)))

/* 寄存器说明：处理器X的通道传输完成中断屏蔽寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_TC1_MASK_UNION */
#define SOC_DMAC_INT_TC1_MASK_ADDR(base, in)          ((base) + (0x0018+0x40*(in)))

/* 寄存器说明：处理器X的链表节点传输完成中断屏蔽寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_TC2_MASK_UNION */
#define SOC_DMAC_INT_TC2_MASK_ADDR(base, in)          ((base) + (0x001C+0x40*(in)))

/* 寄存器说明：处理器X的配置错误中断屏蔽寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR1_MASK_UNION */
#define SOC_DMAC_INT_ERR1_MASK_ADDR(base, in)         ((base) + (0x0020+0x40*(in)))

/* 寄存器说明：处理器X的数据传输错误中断屏蔽寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR2_MASK_UNION */
#define SOC_DMAC_INT_ERR2_MASK_ADDR(base, in)         ((base) + (0x0024+0x40*(in)))

/* 寄存器说明：处理器X的链表读取错误中断屏蔽寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR3_MASK_UNION */
#define SOC_DMAC_INT_ERR3_MASK_ADDR(base, in)         ((base) + (0x0028+0x40*(in)))

/* 寄存器说明：原始通道传输完成中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_TC1_RAW_UNION */
#define SOC_DMAC_INT_TC1_RAW_ADDR(base)               ((base) + (0x0600))

/* 寄存器说明：原始链表节点传输完成中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_TC2_RAW_UNION */
#define SOC_DMAC_INT_TC2_RAW_ADDR(base)               ((base) + (0x0608))

/* 寄存器说明：原始配置错误中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR1_RAW_UNION */
#define SOC_DMAC_INT_ERR1_RAW_ADDR(base)              ((base) + (0x0610))

/* 寄存器说明：原始数据传输错误中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR2_RAW_UNION */
#define SOC_DMAC_INT_ERR2_RAW_ADDR(base)              ((base) + (0x0618))

/* 寄存器说明：原始链表读取错误中断状态寄存器。
   位域定义UNION结构:  SOC_DMAC_INT_ERR3_RAW_UNION */
#define SOC_DMAC_INT_ERR3_RAW_ADDR(base)              ((base) + (0x0620))

/* 寄存器说明：单传输请求寄存器。
   位域定义UNION结构:  SOC_DMAC_SREQ_UNION */
#define SOC_DMAC_SREQ_ADDR(base)                      ((base) + (0x660))

/* 寄存器说明：末次单传输请求寄存器。
   位域定义UNION结构:  SOC_DMAC_LSREQ_UNION */
#define SOC_DMAC_LSREQ_ADDR(base)                     ((base) + (0x664))

/* 寄存器说明：突发传输请求寄存器。
   位域定义UNION结构:  SOC_DMAC_BREQ_UNION */
#define SOC_DMAC_BREQ_ADDR(base)                      ((base) + (0x668))

/* 寄存器说明：末次突发传输请求寄存器。
   位域定义UNION结构:  SOC_DMAC_LBREQ_UNION */
#define SOC_DMAC_LBREQ_ADDR(base)                     ((base) + (0x66C))

/* 寄存器说明：批量传输请求寄存器。
   位域定义UNION结构:  SOC_DMAC_FREQ_UNION */
#define SOC_DMAC_FREQ_ADDR(base)                      ((base) + (0x670))

/* 寄存器说明：末次批量传输请求寄存器。
   位域定义UNION结构:  SOC_DMAC_LFREQ_UNION */
#define SOC_DMAC_LFREQ_ADDR(base)                     ((base) + (0x674))

/* 寄存器说明：优先级控制寄存器。
   位域定义UNION结构:  SOC_DMAC_CH_PRI_UNION */
#define SOC_DMAC_CH_PRI_ADDR(base)                    ((base) + (0x688))

/* 寄存器说明：全局DMA状态寄存器。
   位域定义UNION结构:  SOC_DMAC_CH_STAT_UNION */
#define SOC_DMAC_CH_STAT_ADDR(base)                   ((base) + (0x690))

/* 寄存器说明：DMA全局安全控制寄存器。
   位域定义UNION结构:  SOC_DMAC_SEC_CTRL_UNION */
#define SOC_DMAC_SEC_CTRL_ADDR(base)                  ((base) + (0x0694))

/* 寄存器说明：DMA全局控制寄存器。
   位域定义UNION结构:  SOC_DMAC_DMA_CTRL_UNION */
#define SOC_DMAC_DMA_CTRL_ADDR(base)                  ((base) + (0x0698))

/* 寄存器说明：通道X的三维传输剩余size状态寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CURR_CNT1_UNION */
#define SOC_DMAC_CX_CURR_CNT1_ADDR(base, cn)          ((base) + (0x0700+0x10*(cn)))

/* 寄存器说明：通道X的一、二维传输剩余size状态寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CURR_CNT0_UNION */
#define SOC_DMAC_CX_CURR_CNT0_ADDR(base, cn)          ((base) + (0x0704+0x10*(cn)))

/* 寄存器说明：通道X的源地址寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CURR_SRC_ADDR_UNION */
#define SOC_DMAC_CX_CURR_SRC_ADDR_ADDR(base, cn)      ((base) + (0x0708+0x10*(cn)))

/* 寄存器说明：通道X的目的地址寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CURR_DES_ADDR_UNION */
#define SOC_DMAC_CX_CURR_DES_ADDR_ADDR(base, cn)      ((base) + (0x070C+0x10*(cn)))

/* 寄存器说明：通道X的链表地址寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_LLI_UNION */
#define SOC_DMAC_CX_LLI_ADDR(base, cn)                ((base) + (0x0800+0x40*(cn)))

/* 寄存器说明：通道X的二维地址偏移量配置寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_BINDX_UNION */
#define SOC_DMAC_CX_BINDX_ADDR(base, cn)              ((base) + (0x0804+0x40*(cn)))

/* 寄存器说明：通道X的三维地址偏移量配置寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CINDX_UNION */
#define SOC_DMAC_CX_CINDX_ADDR(base, cn)              ((base) + (0x0808+0x40*(cn)))

/* 寄存器说明：通道X的传输长度1配置寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CNT1_UNION */
#define SOC_DMAC_CX_CNT1_ADDR(base, cn)               ((base) + (0x080C+0x40*(cn)))

/* 寄存器说明：通道X的传输长度配置寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CNT0_UNION */
#define SOC_DMAC_CX_CNT0_ADDR(base, cn)               ((base) + (0x0810+0x40*(cn)))

/* 寄存器说明：通道X的源地址寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_SRC_ADDR_UNION */
#define SOC_DMAC_CX_SRC_ADDR_ADDR(base, cn)           ((base) + (0x0814+0x40*(cn)))

/* 寄存器说明：通道X的目的地址寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_DES_ADDR_UNION */
#define SOC_DMAC_CX_DES_ADDR_ADDR(base, cn)           ((base) + (0x0818+0x40*(cn)))

/* 寄存器说明：通道X的配置寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_CONFIG_UNION */
#define SOC_DMAC_CX_CONFIG_ADDR(base, cn)             ((base) + (0x081C+0x40*(cn)))

/* 寄存器说明：通道X的AXI特殊操作配置寄存器。
   位域定义UNION结构:  SOC_DMAC_CX_AXI_CONF_UNION */
#define SOC_DMAC_CX_AXI_CONF_ADDR(base, cn)           ((base) + (0x0820+0x40*(cn)))





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
                     (1/1) register_dmac
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DMAC_INT_STAT_UNION
 结构说明  : INT_STAT 寄存器结构定义。地址偏移量:0x0000+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_stat : 16; /* bit[0-15] : DMAC各通道经屏蔽后的中断状态，bit[15:0]分别对应通道15～0。
                                                    0：未产生中断；
                                                    1：已产生中断，该中断请求可能来自该通道的错误中断或传输完成中断。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_STAT_UNION;
#endif
#define SOC_DMAC_INT_STAT_int_stat_START  (0)
#define SOC_DMAC_INT_STAT_int_stat_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_TC1_UNION
 结构说明  : INT_TC1 寄存器结构定义。地址偏移量:0x0004+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的通道传输完成中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc1  : 16; /* bit[0-15] : DMAC各通道经过屏蔽后的通道传输完成中断状态，bit[15:0]分别对应通道15～0。
                                                    0：未产生传输完成中断；
                                                    1：已产生传输完成中断。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_TC1_UNION;
#endif
#define SOC_DMAC_INT_TC1_int_tc1_START   (0)
#define SOC_DMAC_INT_TC1_int_tc1_END     (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_TC2_UNION
 结构说明  : INT_TC2 寄存器结构定义。地址偏移量:0x0008+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的链表节点传输完成中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc2  : 16; /* bit[0-15] : DMAC各通道经过屏蔽后的链表节点传输完成中断状态，bit[15:0]分别对应通道15～0。
                                                    0：未产生传输完成中断；
                                                    1：已产生传输完成中断。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_TC2_UNION;
#endif
#define SOC_DMAC_INT_TC2_int_tc2_START   (0)
#define SOC_DMAC_INT_TC2_int_tc2_END     (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR1_UNION
 结构说明  : INT_ERR1 寄存器结构定义。地址偏移量:0x000C+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的配置错误中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err1 : 16; /* bit[0-15] : DMAC各通道经过屏蔽后的配置错误中断状态，bit[15:0]分别对应通道15～0。
                                                    0：未产生传输错误中断；
                                                    1：产生了传输错误中断。
                                                    该中断可能来自：
                                                    1、配置Acount为0；
                                                    2、通道链接时指向的通道链接号为本通道；
                                                    3、通道链接到不存在的通道（通道数目小于16时才会存在这种情况）；
                                                    4、支持narrow传输时，配置burst size的reserved值；
                                                    5、FIX传输时，配置地址与burst size不对齐。
                                                    6、配置flow_ctrl的reserved值；
                                                    7、配置chain_en的reserved值；
                                                    8、链表节点的配置出现上述情况，也会触发配置错误中断 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR1_UNION;
#endif
#define SOC_DMAC_INT_ERR1_int_err1_START  (0)
#define SOC_DMAC_INT_ERR1_int_err1_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR2_UNION
 结构说明  : INT_ERR2 寄存器结构定义。地址偏移量:0x0010+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的数据传输错误中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err2 : 16; /* bit[0-15] : DMAC各通道经过屏蔽后的数据传输错误中断状态，bit[15:0]分别对应通道15～0。
                                                    0：未产生中断；
                                                    1：已产生中断。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR2_UNION;
#endif
#define SOC_DMAC_INT_ERR2_int_err2_START  (0)
#define SOC_DMAC_INT_ERR2_int_err2_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR3_UNION
 结构说明  : INT_ERR3 寄存器结构定义。地址偏移量:0x0014+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的读链表错误中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err3 : 16; /* bit[0-15] : DMAC各通道经过屏蔽后的读链表错误中断状态，bit[15:0]分别对应通道15～0。
                                                    0：未产生中断；
                                                    1：已产生中断。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR3_UNION;
#endif
#define SOC_DMAC_INT_ERR3_int_err3_START  (0)
#define SOC_DMAC_INT_ERR3_int_err3_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_TC1_MASK_UNION
 结构说明  : INT_TC1_MASK 寄存器结构定义。地址偏移量:0x0018+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的通道传输完成中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc1_mask : 16; /* bit[0-15] : DMAC各通道传输完成中断屏蔽，bit[15:0]分别对应通道15～0。
                                                        0：屏蔽本通道的传输完成中断。
                                                        1：不屏蔽本通道的传输完成中断。 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_TC1_MASK_UNION;
#endif
#define SOC_DMAC_INT_TC1_MASK_int_tc1_mask_START  (0)
#define SOC_DMAC_INT_TC1_MASK_int_tc1_mask_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_TC2_MASK_UNION
 结构说明  : INT_TC2_MASK 寄存器结构定义。地址偏移量:0x001C+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的链表节点传输完成中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc2_mask : 16; /* bit[0-15] : DMAC各通道链表节点传输完成中断屏蔽，bit[15:0]分别对应通道15～0。
                                                        0：屏蔽本通道的链表节点传输完成中断。
                                                        1：不屏蔽本通道的链表节点传输完成中断。 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_TC2_MASK_UNION;
#endif
#define SOC_DMAC_INT_TC2_MASK_int_tc2_mask_START  (0)
#define SOC_DMAC_INT_TC2_MASK_int_tc2_mask_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR1_MASK_UNION
 结构说明  : INT_ERR1_MASK 寄存器结构定义。地址偏移量:0x0020+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的配置错误中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err1_mask : 16; /* bit[0-15] : DMAC各通道配置错误中断屏蔽，bit[15:0]分别对应通道15～0。
                                                         0：屏蔽本通道的配置错误中断。
                                                         1：不屏蔽本通道的配置错误中断。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR1_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR1_MASK_int_err1_mask_START  (0)
#define SOC_DMAC_INT_ERR1_MASK_int_err1_mask_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR2_MASK_UNION
 结构说明  : INT_ERR2_MASK 寄存器结构定义。地址偏移量:0x0024+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的数据传输错误中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err2_mask : 16; /* bit[0-15] : DMAC各数据传输错误中断屏蔽，bit[15:0]分别对应通道15～0。
                                                         0：屏蔽本通道的数据传输错误中断。
                                                         1：不屏蔽本通道的数据传输错误中断。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR2_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR2_MASK_int_err2_mask_START  (0)
#define SOC_DMAC_INT_ERR2_MASK_int_err2_mask_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR3_MASK_UNION
 结构说明  : INT_ERR3_MASK 寄存器结构定义。地址偏移量:0x0028+0x40*(in)，初值:0x00000000，宽度:32
 寄存器说明: 处理器X的链表读取错误中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err3_mask : 16; /* bit[0-15] : DMAC各通道链表读取错误中断屏蔽，bit[15:0]分别对应通道15～0。
                                                         0：屏蔽本通道的链表读取错误中断。
                                                         1：不屏蔽本通道的链表读取错误中断。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR3_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR3_MASK_int_err3_mask_START  (0)
#define SOC_DMAC_INT_ERR3_MASK_int_err3_mask_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_TC1_RAW_UNION
 结构说明  : INT_TC1_RAW 寄存器结构定义。地址偏移量:0x0600，初值:0x00000000，宽度:32
 寄存器说明: 原始通道传输完成中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc1_raw : 16; /* bit[0-15] : 各通道屏蔽前的通道传输完成中断状态，bit[15:0]分别对应通道15～0。
                                                       读:
                                                       0：未产生通道传输完成中断；
                                                       1：产生了通道传输完成中断。
                                                       写:
                                                       1:清除通道传输完成中断。
                                                       0:保持之前的值。 */
        unsigned int  reserved    : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_TC1_RAW_UNION;
#endif
#define SOC_DMAC_INT_TC1_RAW_int_tc1_raw_START  (0)
#define SOC_DMAC_INT_TC1_RAW_int_tc1_raw_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_TC2_RAW_UNION
 结构说明  : INT_TC2_RAW 寄存器结构定义。地址偏移量:0x0608，初值:0x00000000，宽度:32
 寄存器说明: 原始链表节点传输完成中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc2_raw : 16; /* bit[0-15] : 各通道屏蔽前的链表节点传输完成中断状态，bit[15:0]分别对应通道15～0。
                                                       读:
                                                       0：未产生节点完成成中断；
                                                       1：产生了节点完成中断。
                                                       写:
                                                       1:清除节点完成中断。
                                                       0:保持之前的值。 */
        unsigned int  reserved    : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_TC2_RAW_UNION;
#endif
#define SOC_DMAC_INT_TC2_RAW_int_tc2_raw_START  (0)
#define SOC_DMAC_INT_TC2_RAW_int_tc2_raw_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR1_RAW_UNION
 结构说明  : INT_ERR1_RAW 寄存器结构定义。地址偏移量:0x0610，初值:0x00000000，宽度:32
 寄存器说明: 原始配置错误中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err1_raw : 16; /* bit[0-15] : 各通道屏蔽前的配置错误中断状态，bit[15:0]分别对应通道15～0。
                                                        0：未产生配置错误中断；
                                                        1：产生了配置错误中断。
                                                        写:
                                                        1:清除配置错误中断。
                                                        0:保持之前的值。 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR1_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR1_RAW_int_err1_raw_START  (0)
#define SOC_DMAC_INT_ERR1_RAW_int_err1_raw_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR2_RAW_UNION
 结构说明  : INT_ERR2_RAW 寄存器结构定义。地址偏移量:0x0618，初值:0x00000000，宽度:32
 寄存器说明: 原始数据传输错误中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err2_raw : 16; /* bit[0-15] : 各通道屏蔽前的数据传输错误中断状态，bit[15:0]分别对应通道15～0。
                                                        0：未产生数据传输错误中断；
                                                        1：产生了数据传输错误中断。
                                                        写:
                                                        1:清除数据传输错误中断。
                                                        0:保持之前的值。 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR2_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR2_RAW_int_err2_raw_START  (0)
#define SOC_DMAC_INT_ERR2_RAW_int_err2_raw_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_INT_ERR3_RAW_UNION
 结构说明  : INT_ERR3_RAW 寄存器结构定义。地址偏移量:0x0620，初值:0x00000000，宽度:32
 寄存器说明: 原始链表读取错误中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err3_raw : 16; /* bit[0-15] : 各通道屏蔽前的链表读取错误中断状态，bit[15:0]分别对应通道15～0。
                                                        0：未产生链表读取错误中断；
                                                        1：产生了链表读取错误中断。
                                                        写:
                                                        1:清除链表读取错误中断。
                                                        0:保持之前的值。 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_INT_ERR3_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR3_RAW_int_err3_raw_START  (0)
#define SOC_DMAC_INT_ERR3_RAW_int_err3_raw_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_SREQ_UNION
 结构说明  : SREQ 寄存器结构定义。地址偏移量:0x660，初值:0x00000000，宽度:32
 寄存器说明: 单传输请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sreq : 32; /* bit[0-31]: 用于软件控制产生DMA single 传输请求。
                                               当写该寄存器时：
                                               0：无影响；
                                               1：产生DMA single 传输请求，当传输结束时该寄存器中的相应位被清零。
                                               当读该寄存器时：
                                               0：对应的请求外设未发出single传输请求；
                                               1：对应的请求外设发出single传输请求。 */
    } reg;
} SOC_DMAC_SREQ_UNION;
#endif
#define SOC_DMAC_SREQ_sreq_START  (0)
#define SOC_DMAC_SREQ_sreq_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_LSREQ_UNION
 结构说明  : LSREQ 寄存器结构定义。地址偏移量:0x664，初值:0x00000000，宽度:32
 寄存器说明: 末次单传输请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lsreq : 32; /* bit[0-31]: 用于软件控制产生DMA last single 传输请求。
                                                当写该寄存器时：
                                                0：无影响；
                                                1：产生DMA last single 传输请求，当传输结束时该寄存器中的相应位被清零。
                                                当读该寄存器时：
                                                0：对应的请求外设未发出last single 传输请求；
                                                1：对应的请求外设发出last single传输请求。 */
    } reg;
} SOC_DMAC_LSREQ_UNION;
#endif
#define SOC_DMAC_LSREQ_lsreq_START  (0)
#define SOC_DMAC_LSREQ_lsreq_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_BREQ_UNION
 结构说明  : BREQ 寄存器结构定义。地址偏移量:0x668，初值:0x00000000，宽度:32
 寄存器说明: 突发传输请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  breq : 32; /* bit[0-31]: 用于软件控制产生DMA burst 传输请求。
                                               当写该寄存器时：
                                               0：无影响；
                                               1：产生DMA burst 传输请求，当传输结束时该寄存器中的相应位被清零。
                                               当读该寄存器时：
                                               0：对应的请求外设未发出burst 传输请求；
                                               1：对应的请求外设发出burst 传输请求。 */
    } reg;
} SOC_DMAC_BREQ_UNION;
#endif
#define SOC_DMAC_BREQ_breq_START  (0)
#define SOC_DMAC_BREQ_breq_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_LBREQ_UNION
 结构说明  : LBREQ 寄存器结构定义。地址偏移量:0x66C，初值:0x00000000，宽度:32
 寄存器说明: 末次突发传输请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lbreq : 32; /* bit[0-31]: 用于软件控制产生DMA last burst 传输请求。
                                                当写该寄存器时：
                                                0：无影响；
                                                1：产生DMA last burst 传输请求，当传输结束时该寄存器中的相应位被清零。
                                                当读该寄存器时：
                                                0：对应的请求外设未发出last burst 传输请求；
                                                1：对应的请求外设发出last burst传输请求。 */
    } reg;
} SOC_DMAC_LBREQ_UNION;
#endif
#define SOC_DMAC_LBREQ_lbreq_START  (0)
#define SOC_DMAC_LBREQ_lbreq_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_FREQ_UNION
 结构说明  : FREQ 寄存器结构定义。地址偏移量:0x670，初值:0x00000000，宽度:32
 寄存器说明: 批量传输请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  freq : 32; /* bit[0-31]: 用于软件控制产生DMA flush 传输请求。
                                               当写该寄存器时：
                                               0：无影响；
                                               1：产生DMA flush 传输请求，当传输结束时该寄存器中的相应位被清零。
                                               当读该寄存器时：
                                               0：对应的请求外设未发出flush 传输请求；
                                               1：对应的请求外设发出 flush 传输请求。 */
    } reg;
} SOC_DMAC_FREQ_UNION;
#endif
#define SOC_DMAC_FREQ_freq_START  (0)
#define SOC_DMAC_FREQ_freq_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_LFREQ_UNION
 结构说明  : LFREQ 寄存器结构定义。地址偏移量:0x674，初值:0x00000000，宽度:32
 寄存器说明: 末次批量传输请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lfreq : 32; /* bit[0-31]: 用于软件控制产生DMA last flush 传输请求。
                                                当写该寄存器时：
                                                0：无影响；
                                                1：产生DMA last flush 传输请求，当传输结束时该寄存器中的相应位被清零。
                                                当读该寄存器时：
                                                0：对应的请求外设未发出last flush 传输请求；
                                                1：对应的请求外设发出last flush 传输请求。 */
    } reg;
} SOC_DMAC_LFREQ_UNION;
#endif
#define SOC_DMAC_LFREQ_lfreq_START  (0)
#define SOC_DMAC_LFREQ_lfreq_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CH_PRI_UNION
 结构说明  : CH_PRI 寄存器结构定义。地址偏移量:0x688，初值:0x00000000，宽度:32
 寄存器说明: 优先级控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_pri  : 2;  /* bit[0-1]  : 通道0优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch1_pri  : 2;  /* bit[2-3]  : 通道1优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch2_pri  : 2;  /* bit[4-5]  : 通道2优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch3_pri  : 2;  /* bit[6-7]  : 通道3优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch4_pri  : 2;  /* bit[8-9]  : 通道4优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch5_pri  : 2;  /* bit[10-11]: 通道5优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch6_pri  : 2;  /* bit[12-13]: 通道6优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch7_pri  : 2;  /* bit[14-15]: 通道7优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch8_pri  : 2;  /* bit[16-17]: 通道8优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch9_pri  : 2;  /* bit[18-19]: 通道9优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch10_pri : 2;  /* bit[20-21]: 通道10优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch11_pri : 2;  /* bit[22-23]: 通道11优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch12_pri : 2;  /* bit[24-25]: 通道12优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch13_pri : 2;  /* bit[26-27]: 通道13优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch14_pri : 2;  /* bit[28-29]: 通道14优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
        unsigned int  ch15_pri : 2;  /* bit[30-31]: 通道15优先级模式配置寄存器。
                                                    2'b00：0优先级（最高）；
                                                    2'b01：1优先级；
                                                    2'b10：2优先级；
                                                    2'b11：3优先级（最低）。 */
    } reg;
} SOC_DMAC_CH_PRI_UNION;
#endif
#define SOC_DMAC_CH_PRI_ch0_pri_START   (0)
#define SOC_DMAC_CH_PRI_ch0_pri_END     (1)
#define SOC_DMAC_CH_PRI_ch1_pri_START   (2)
#define SOC_DMAC_CH_PRI_ch1_pri_END     (3)
#define SOC_DMAC_CH_PRI_ch2_pri_START   (4)
#define SOC_DMAC_CH_PRI_ch2_pri_END     (5)
#define SOC_DMAC_CH_PRI_ch3_pri_START   (6)
#define SOC_DMAC_CH_PRI_ch3_pri_END     (7)
#define SOC_DMAC_CH_PRI_ch4_pri_START   (8)
#define SOC_DMAC_CH_PRI_ch4_pri_END     (9)
#define SOC_DMAC_CH_PRI_ch5_pri_START   (10)
#define SOC_DMAC_CH_PRI_ch5_pri_END     (11)
#define SOC_DMAC_CH_PRI_ch6_pri_START   (12)
#define SOC_DMAC_CH_PRI_ch6_pri_END     (13)
#define SOC_DMAC_CH_PRI_ch7_pri_START   (14)
#define SOC_DMAC_CH_PRI_ch7_pri_END     (15)
#define SOC_DMAC_CH_PRI_ch8_pri_START   (16)
#define SOC_DMAC_CH_PRI_ch8_pri_END     (17)
#define SOC_DMAC_CH_PRI_ch9_pri_START   (18)
#define SOC_DMAC_CH_PRI_ch9_pri_END     (19)
#define SOC_DMAC_CH_PRI_ch10_pri_START  (20)
#define SOC_DMAC_CH_PRI_ch10_pri_END    (21)
#define SOC_DMAC_CH_PRI_ch11_pri_START  (22)
#define SOC_DMAC_CH_PRI_ch11_pri_END    (23)
#define SOC_DMAC_CH_PRI_ch12_pri_START  (24)
#define SOC_DMAC_CH_PRI_ch12_pri_END    (25)
#define SOC_DMAC_CH_PRI_ch13_pri_START  (26)
#define SOC_DMAC_CH_PRI_ch13_pri_END    (27)
#define SOC_DMAC_CH_PRI_ch14_pri_START  (28)
#define SOC_DMAC_CH_PRI_ch14_pri_END    (29)
#define SOC_DMAC_CH_PRI_ch15_pri_START  (30)
#define SOC_DMAC_CH_PRI_ch15_pri_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CH_STAT_UNION
 结构说明  : CH_STAT 寄存器结构定义。地址偏移量:0x690，初值:0x00000000，宽度:32
 寄存器说明: 全局DMA状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_stat  : 16; /* bit[0-15] : DMAC通道使能寄存器。
                                                    1:对应的DMAC通道目前正在工作。
                                                    0:对应的DMAC通道目前没有工作。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_CH_STAT_UNION;
#endif
#define SOC_DMAC_CH_STAT_ch_stat_START   (0)
#define SOC_DMAC_CH_STAT_ch_stat_END     (15)


/*****************************************************************************
 结构名    : SOC_DMAC_SEC_CTRL_UNION
 结构说明  : SEC_CTRL 寄存器结构定义。地址偏移量:0x0694，初值:0x00000002，宽度:32
 寄存器说明: DMA全局安全控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  global_sec    : 1;  /* bit[0]   : 全局寄存器安全控制(只能通过安全操作访问)：
                                                        0：CH_PRI和DMA_CTRL只有安全操作才能访问；
                                                        1：CH_PRI和DMA_CTRL可以受安全和非安全操作访问 */
        unsigned int  intr_sec_ctrl : 1;  /* bit[1]   : 中断安全控制(只能通过安全操作访问)：
                                                        0：安全操作只能访问安全通道的中断信息，安全中断通过dma_intr上报，非安全中断通过dma_intr_ns上报；
                                                        1：安全操作能访问所有通道的信息，安全中断和非安全中断都会通过dma_intr上报，dma_intr_ns只上报非安全中断 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_DMAC_SEC_CTRL_UNION;
#endif
#define SOC_DMAC_SEC_CTRL_global_sec_START     (0)
#define SOC_DMAC_SEC_CTRL_global_sec_END       (0)
#define SOC_DMAC_SEC_CTRL_intr_sec_ctrl_START  (1)
#define SOC_DMAC_SEC_CTRL_intr_sec_ctrl_END    (1)


/*****************************************************************************
 结构名    : SOC_DMAC_DMA_CTRL_UNION
 结构说明  : DMA_CTRL 寄存器结构定义。地址偏移量:0x0698，初值:0x00000000，宽度:32
 寄存器说明: DMA全局控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halt_ack  : 1;  /* bit[0]   : DMA进入HALT状态确认寄存器：
                                                    读：
                                                    1：DMA已经进入了HALT状态
                                                    0：DMA还未进入HALT状态
                                                    写：
                                                    1：解除DMA HALT状态
                                                    0：无影响，保留原值 */
        unsigned int  halt_req  : 1;  /* bit[1]   : DMA HALT请求配置寄存器：
                                                    读：
                                                    1：DMA已经接受了HALT请求但还未进入HALT状态
                                                    0：DMA还没接受HALT请求或者DMA已经进入了HALT状态
                                                    写：
                                                    1：发出DMA HALT请求
                                                    0：无影响，保留原值 */
        unsigned int  reserved_0: 2;  /* bit[2-3] : 保留 */
        unsigned int  conf_out4 : 1;  /* bit[4]   : 当Outstanding数宏定义为8时：
                                                    1：Outstanding数为4；
                                                    0：Outstanding数为8；
                                                    当Outstanding数宏定义为4时，此位不可写，读出位0
                                                    注意：修改Outstanding必须等待所有通道处于IDLE状态时才会有效，对应CH_STAT寄存器全为0，否则修改无效 */
        unsigned int  reserved_1: 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_DMAC_DMA_CTRL_UNION;
#endif
#define SOC_DMAC_DMA_CTRL_halt_ack_START   (0)
#define SOC_DMAC_DMA_CTRL_halt_ack_END     (0)
#define SOC_DMAC_DMA_CTRL_halt_req_START   (1)
#define SOC_DMAC_DMA_CTRL_halt_req_END     (1)
#define SOC_DMAC_DMA_CTRL_conf_out4_START  (4)
#define SOC_DMAC_DMA_CTRL_conf_out4_END    (4)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CURR_CNT1_UNION
 结构说明  : CX_CURR_CNT1 寄存器结构定义。地址偏移量:0x0700+0x10*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的三维传输剩余size状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_c_count : 16; /* bit[0-15] : 通道X当前三维传输剩余的Frame数。 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_CX_CURR_CNT1_UNION;
#endif
#define SOC_DMAC_CX_CURR_CNT1_curr_c_count_START  (0)
#define SOC_DMAC_CX_CURR_CNT1_curr_c_count_END    (15)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CURR_CNT0_UNION
 结构说明  : CX_CURR_CNT0 寄存器结构定义。地址偏移量:0x0704+0x10*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的一、二维传输剩余size状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_a_count : 16; /* bit[0-15] : 通道X当前一维传输剩余的Byte数。 */
        unsigned int  curr_b_count : 16; /* bit[16-31]: 通道X当前二维传输剩余的Array个数。 */
    } reg;
} SOC_DMAC_CX_CURR_CNT0_UNION;
#endif
#define SOC_DMAC_CX_CURR_CNT0_curr_a_count_START  (0)
#define SOC_DMAC_CX_CURR_CNT0_curr_a_count_END    (15)
#define SOC_DMAC_CX_CURR_CNT0_curr_b_count_START  (16)
#define SOC_DMAC_CX_CURR_CNT0_curr_b_count_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CURR_SRC_ADDR_UNION
 结构说明  : CX_CURR_SRC_ADDR 寄存器结构定义。地址偏移量:0x0708+0x10*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的源地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_src_addr : 32; /* bit[0-31]: 通道X当前正在传输的源地址 */
    } reg;
} SOC_DMAC_CX_CURR_SRC_ADDR_UNION;
#endif
#define SOC_DMAC_CX_CURR_SRC_ADDR_curr_src_addr_START  (0)
#define SOC_DMAC_CX_CURR_SRC_ADDR_curr_src_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CURR_DES_ADDR_UNION
 结构说明  : CX_CURR_DES_ADDR 寄存器结构定义。地址偏移量:0x070C+0x10*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的目的地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_des_addr : 32; /* bit[0-31]: 通道X当前正在传输的目的地址 */
    } reg;
} SOC_DMAC_CX_CURR_DES_ADDR_UNION;
#endif
#define SOC_DMAC_CX_CURR_DES_ADDR_curr_des_addr_START  (0)
#define SOC_DMAC_CX_CURR_DES_ADDR_curr_des_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_LLI_UNION
 结构说明  : CX_LLI 寄存器结构定义。地址偏移量:0x0800+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的链表地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chain_en : 2;  /* bit[0-1] : 通道的链接使能:
                                                   00：链表链接使能无效，通道链接使能无效
                                                   01：链表链接使能无效，通道链接使能有效
                                                   10：链表链接使能有效，通道链接使能无效
                                                   11：reserved，配置该reserved值会上报配置错误中断。 */
        unsigned int  reserved : 3;  /* bit[2-4] : 保留。 */
        unsigned int  lli      : 27; /* bit[5-31]: 通道X的下一个链表节点地址的[31:5]位，链表地址始终是256-bit对齐。
                                                   当通道链接使能有效时，[11:8]表示链接的下一个通道的id。 */
    } reg;
} SOC_DMAC_CX_LLI_UNION;
#endif
#define SOC_DMAC_CX_LLI_chain_en_START  (0)
#define SOC_DMAC_CX_LLI_chain_en_END    (1)
#define SOC_DMAC_CX_LLI_lli_START       (5)
#define SOC_DMAC_CX_LLI_lli_END         (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_BINDX_UNION
 结构说明  : CX_BINDX 寄存器结构定义。地址偏移量:0x0804+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的二维地址偏移量配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  des_bindx : 15; /* bit[0-14] : 二维目的地址偏移量配置，指示偏移的绝对值，符号位在bit15指示 */
        unsigned int  des_bsign : 1;  /* bit[15]   : 二维目的地址偏移符号位：
                                                     1：负
                                                     0：正 */
        unsigned int  src_bindx : 15; /* bit[16-30]: 二维源地址偏移量配置，指示偏移的绝对值，符号位在bit31指示 */
        unsigned int  src_bsign : 1;  /* bit[31]   : 二维源地址偏移符号位：
                                                     1：负
                                                     0：正 */
    } reg;
} SOC_DMAC_CX_BINDX_UNION;
#endif
#define SOC_DMAC_CX_BINDX_des_bindx_START  (0)
#define SOC_DMAC_CX_BINDX_des_bindx_END    (14)
#define SOC_DMAC_CX_BINDX_des_bsign_START  (15)
#define SOC_DMAC_CX_BINDX_des_bsign_END    (15)
#define SOC_DMAC_CX_BINDX_src_bindx_START  (16)
#define SOC_DMAC_CX_BINDX_src_bindx_END    (30)
#define SOC_DMAC_CX_BINDX_src_bsign_START  (31)
#define SOC_DMAC_CX_BINDX_src_bsign_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CINDX_UNION
 结构说明  : CX_CINDX 寄存器结构定义。地址偏移量:0x0808+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的三维地址偏移量配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  des_cindx : 15; /* bit[0-14] : 三维目的地址偏移量配置，指示偏移的绝对值，符号位在bit15指示 */
        unsigned int  des_csign : 1;  /* bit[15]   : 三维目的地址偏移符号位：
                                                     1：负
                                                     0：正 */
        unsigned int  src_cindx : 15; /* bit[16-30]: 三维源地址偏移量配置，指示偏移的绝对值，符号位在bit31指示 */
        unsigned int  src_csign : 1;  /* bit[31]   : 三维源地址偏移符号位：
                                                     1：负
                                                     0：正 */
    } reg;
} SOC_DMAC_CX_CINDX_UNION;
#endif
#define SOC_DMAC_CX_CINDX_des_cindx_START  (0)
#define SOC_DMAC_CX_CINDX_des_cindx_END    (14)
#define SOC_DMAC_CX_CINDX_des_csign_START  (15)
#define SOC_DMAC_CX_CINDX_des_csign_END    (15)
#define SOC_DMAC_CX_CINDX_src_cindx_START  (16)
#define SOC_DMAC_CX_CINDX_src_cindx_END    (30)
#define SOC_DMAC_CX_CINDX_src_csign_START  (31)
#define SOC_DMAC_CX_CINDX_src_csign_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CNT1_UNION
 结构说明  : CX_CNT1 寄存器结构定义。地址偏移量:0x080C+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的传输长度1配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  c_count  : 16; /* bit[0-15] : 三维传输长度配置(1～65535)
                                                    即一个Block包含的Frame的个数，0表示没有三维传输。Frame的个数为c_count的个数加1。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_DMAC_CX_CNT1_UNION;
#endif
#define SOC_DMAC_CX_CNT1_c_count_START   (0)
#define SOC_DMAC_CX_CNT1_c_count_END     (15)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CNT0_UNION
 结构说明  : CX_CNT0 寄存器结构定义。地址偏移量:0x0810+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的传输长度配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a_count : 16; /* bit[0-15] : 一维传输长度配置(1～65535)
                                                   即一个Array包含的最小bytes数目。Acount配置为0会触发配置错误中断。 */
        unsigned int  b_count : 16; /* bit[16-31]: 二维传输长度配置(1～65535)
                                                   即一个Frame包含的Array的个数。Frame的array个数为b_count的值加1。 */
    } reg;
} SOC_DMAC_CX_CNT0_UNION;
#endif
#define SOC_DMAC_CX_CNT0_a_count_START  (0)
#define SOC_DMAC_CX_CNT0_a_count_END    (15)
#define SOC_DMAC_CX_CNT0_b_count_START  (16)
#define SOC_DMAC_CX_CNT0_b_count_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_SRC_ADDR_UNION
 结构说明  : CX_SRC_ADDR 寄存器结构定义。地址偏移量:0x0814+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的源地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_addr : 32; /* bit[0-31]: 通道X的源地址 */
    } reg;
} SOC_DMAC_CX_SRC_ADDR_UNION;
#endif
#define SOC_DMAC_CX_SRC_ADDR_src_addr_START  (0)
#define SOC_DMAC_CX_SRC_ADDR_src_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_DES_ADDR_UNION
 结构说明  : CX_DES_ADDR 寄存器结构定义。地址偏移量:0x0818+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的目的地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  des_addr : 32; /* bit[0-31]: 通道X的目的地址 */
    } reg;
} SOC_DMAC_CX_DES_ADDR_UNION;
#endif
#define SOC_DMAC_CX_DES_ADDR_des_addr_START  (0)
#define SOC_DMAC_CX_DES_ADDR_des_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_CONFIG_UNION
 结构说明  : CX_CONFIG 寄存器结构定义。地址偏移量:0x081C+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_en     : 1;  /* bit[0]    : 当前通道使能控制，
                                                     当写该寄存器，控制当前通道的运行：
                                                     0：通道禁能/复位；
                                                     1：通道使能。
                                                     当读该寄存器，显示当前通道的状态：
                                                     0：通道停止中；
                                                     1：通道运行中(链表传输使能时，通道一直使能)。 */
        unsigned int  itc_en    : 1;  /* bit[1]    : 链表节点传输完成中断使能。该位用于配置当前链表节点传输完成后是否触发节点传输完成中断。
                                                     0：当前链表节点传输完成以后不触发链表节点传输完成中断；
                                                     1：当前链表节点传输完成以后触发链表节点传输完成中断，但是最后一个节点传输完成以后，链表节点传输完成中断不会被触发。
                                                     注意：无论该bit配置为0或1，通道所有链表节点传输完成以后均会上报通道传输完成中断。 */
        unsigned int  flow_ctrl : 2;  /* bit[2-3]  : 流控制和传输类型。
                                                     00：存储器和存储器之间传输，DMAC流控；
                                                     01：存储器和外设之间传输，DMAC流控；
                                                     10：存储器和外设之间传输，外设流控；
                                                     11：Reserved；配置reserved值会上报配置错误中断。 */
        unsigned int  peri      : 6;  /* bit[4-9]  : 外设请求号。如果是存储器到存储器，这些位将被忽略。目前最大支持32个外设请求，所以bit9目前不起作用，实际使用的为bit8:bit4。在不同的外设请求宏定义配置下面，peri的有效值会根据外设请求的有效数目变化，比如宏定义只使用16个外设请求，则peri从0到15的值是有效的，更高位的值可以配置，但是会被忽略掉。 */
        unsigned int  reserved_0: 2;  /* bit[10-11]: 保留。 */
        unsigned int  dw        : 3;  /* bit[12-14]: 目的数据宽度。
                                                     000：8bit
                                                     001：16bit
                                                     010：32bit
                                                     011：64bit
                                                     100：128bit
                                                     101：256bit
                                                     110、111：reserved */
        unsigned int  reserved_1: 1;  /* bit[15]   : 保留。 */
        unsigned int  sw        : 3;  /* bit[16-18]: 源数据宽度。
                                                     000：8bit
                                                     001：16bit
                                                     010：32bit
                                                     011：64bit
                                                     100：128bit
                                                     101：256bit
                                                     110、111：reserved */
        unsigned int  reserved_2: 1;  /* bit[19]   : 保留。 */
        unsigned int  dl        : 4;  /* bit[20-23]: 目的传输burst长度。
                                                     0000：burst length为1
                                                     0001：burst length为2
                                                     …
                                                     1111：burst length为16 */
        unsigned int  sl        : 4;  /* bit[24-27]: 源传输burst长度。
                                                     0000：burst length为1
                                                     0001：burst length为2
                                                     …
                                                     1111：burst length为16 */
        unsigned int  dmode     : 1;  /* bit[28]   : 目的地址的递增模式。
                                                     0:A-sync模式，三维的地址偏移是一个frame的最后一个array的首地址到下一个frame的第一个array的首地址间隔。
                                                     1:AB_sync模式，三维的地址偏移是一个frame的第一个array的首地址到下一个frame的第一个array的首地址的间隔。 */
        unsigned int  smode     : 1;  /* bit[29]   : 源地址的递增模式。
                                                     0:A-sync模式，三维的地址偏移是一个frame的最后一个array的首地址到下一个frame的第一个array的首地址间隔。
                                                     1:AB_sync模式，三维的地址偏移是一个frame的第一个array的首地址到下一个frame的第一个array的首地址的间隔。 */
        unsigned int  di        : 1;  /* bit[30]   : 目的地址递增设置。
                                                     0：目的地址不递增；
                                                     1：目的地址每传一个数就递增一次。
                                                     目的设备为外设时目的地址不递增；目的设备为存储器时目的地址递增。 */
        unsigned int  si        : 1;  /* bit[31]   : 源地址递增设置。
                                                     0：源地址不递增；
                                                     1：源地址每传一个数就递增一次。
                                                     源设备为外设时源地址不递增；源设备为存储器时源地址递增。 */
    } reg;
} SOC_DMAC_CX_CONFIG_UNION;
#endif
#define SOC_DMAC_CX_CONFIG_ch_en_START      (0)
#define SOC_DMAC_CX_CONFIG_ch_en_END        (0)
#define SOC_DMAC_CX_CONFIG_itc_en_START     (1)
#define SOC_DMAC_CX_CONFIG_itc_en_END       (1)
#define SOC_DMAC_CX_CONFIG_flow_ctrl_START  (2)
#define SOC_DMAC_CX_CONFIG_flow_ctrl_END    (3)
#define SOC_DMAC_CX_CONFIG_peri_START       (4)
#define SOC_DMAC_CX_CONFIG_peri_END         (9)
#define SOC_DMAC_CX_CONFIG_dw_START         (12)
#define SOC_DMAC_CX_CONFIG_dw_END           (14)
#define SOC_DMAC_CX_CONFIG_sw_START         (16)
#define SOC_DMAC_CX_CONFIG_sw_END           (18)
#define SOC_DMAC_CX_CONFIG_dl_START         (20)
#define SOC_DMAC_CX_CONFIG_dl_END           (23)
#define SOC_DMAC_CX_CONFIG_sl_START         (24)
#define SOC_DMAC_CX_CONFIG_sl_END           (27)
#define SOC_DMAC_CX_CONFIG_dmode_START      (28)
#define SOC_DMAC_CX_CONFIG_dmode_END        (28)
#define SOC_DMAC_CX_CONFIG_smode_START      (29)
#define SOC_DMAC_CX_CONFIG_smode_END        (29)
#define SOC_DMAC_CX_CONFIG_di_START         (30)
#define SOC_DMAC_CX_CONFIG_di_END           (30)
#define SOC_DMAC_CX_CONFIG_si_START         (31)
#define SOC_DMAC_CX_CONFIG_si_END           (31)


/*****************************************************************************
 结构名    : SOC_DMAC_CX_AXI_CONF_UNION
 结构说明  : CX_AXI_CONF 寄存器结构定义。地址偏移量:0x0820+0x40*(cn)，初值:0x00000000，宽度:32
 寄存器说明: 通道X的AXI特殊操作配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aruser   : 5;  /* bit[0-4]  : bit[4]：DMAC走线及读一致性操作控制
                                                    0：DMAC走SYS_BUS，不进行读一致性操作；
                                                    1：DMAC走CCI_BUS，进行读一致性操作；
                                                    bit[3:0]:DMAC通道号控制
                                                    0-15：表示DMAC 16个通道 */
        unsigned int  arprot   : 3;  /* bit[5-7]  : 配置AXI总线读命令保护类型，遵循AXI总线协议。当awprot[18]&arprot[6]=1的时候，表示当前DMA逻辑通道为非安全，其余情况为安全。arprot只有安全可配。 */
        unsigned int  arcache  : 4;  /* bit[8-11] : 配置AXI总线读命令cache的类型，遵循AXI总线协议 */
        unsigned int  awuser   : 5;  /* bit[12-16]: bit[16]：DMAC走线及写一致性操作控制
                                                    0：DMAC走SYS_BUS，不进行写一致性操作；
                                                    1：DMAC走CCI_BUS，进行写一致性操作；
                                                    bit[15:12]:DMAC通道号控制
                                                    0-15：表示DMAC 16个通道 */
        unsigned int  awprot   : 3;  /* bit[17-19]: 配置AXI总线写命令保护类型，遵循AXI总线协议。当awprot[18]&arprot[6]=1的时候，表示当前DMA逻辑通道为非安全，其余情况为安全。awprot只有安全可配。 */
        unsigned int  awcache  : 4;  /* bit[20-23]: 配置AXI总线写命令cache的类型，遵循AXI总线协议 */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_DMAC_CX_AXI_CONF_UNION;
#endif
#define SOC_DMAC_CX_AXI_CONF_aruser_START    (0)
#define SOC_DMAC_CX_AXI_CONF_aruser_END      (4)
#define SOC_DMAC_CX_AXI_CONF_arprot_START    (5)
#define SOC_DMAC_CX_AXI_CONF_arprot_END      (7)
#define SOC_DMAC_CX_AXI_CONF_arcache_START   (8)
#define SOC_DMAC_CX_AXI_CONF_arcache_END     (11)
#define SOC_DMAC_CX_AXI_CONF_awuser_START    (12)
#define SOC_DMAC_CX_AXI_CONF_awuser_END      (16)
#define SOC_DMAC_CX_AXI_CONF_awprot_START    (17)
#define SOC_DMAC_CX_AXI_CONF_awprot_END      (19)
#define SOC_DMAC_CX_AXI_CONF_awcache_START   (20)
#define SOC_DMAC_CX_AXI_CONF_awcache_END     (23)






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

#endif /* end of soc_dmac_interface.h */
