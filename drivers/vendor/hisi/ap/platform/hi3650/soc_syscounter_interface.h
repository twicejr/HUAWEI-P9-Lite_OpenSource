/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_syscounter_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:23:13
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_SYSCOUNTER.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_SYSCOUNTER_INTERFACE_H__
#define __SOC_SYSCOUNTER_INTERFACE_H__

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
/* 寄存器说明：计数器控制寄存器（需要在安全模式下进行写访问操作）
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTCR_UNION */
#define SOC_SYSCOUNTER_CNTCR_ADDR(base)               ((base) + (0x0000))

/* 寄存器说明：计数器状态寄存器。
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTSR_UNION */
#define SOC_SYSCOUNTER_CNTSR_ADDR(base)               ((base) + (0x0004))

/* 寄存器说明：计数器计数值低32位寄存器（需要在安全模式下进行写访问操作）
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTCV_L32_UNION */
#define SOC_SYSCOUNTER_CNTCV_L32_ADDR(base)           ((base) + (0x0008))

/* 寄存器说明：计数器计数值高32位寄存器（需要在安全模式下进行写访问操作）
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTCV_H32_UNION */
#define SOC_SYSCOUNTER_CNTCV_H32_ADDR(base)           ((base) + (0x000C))

/* 寄存器说明：频率模式0（需要在安全模式下进行写访问操作）
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTFID0_UNION */
#define SOC_SYSCOUNTER_CNTFID0_ADDR(base)             ((base) + (0x0020))

/* 寄存器说明：频率模式1（需要在安全模式下进行写访问操作）
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTFID1_UNION */
#define SOC_SYSCOUNTER_CNTFID1_ADDR(base)             ((base) + (0x0024))

/* 寄存器说明：频率模式2（需要在安全模式下进行写访问操作）
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTFID2_UNION */
#define SOC_SYSCOUNTER_CNTFID2_ADDR(base)             ((base) + (0x0028))

/* 寄存器说明：计数器计数值低32位寄存器
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTCV_L32_NS_UNION */
#define SOC_SYSCOUNTER_CNTCV_L32_NS_ADDR(base)        ((base) + (0x1008))

/* 寄存器说明：计数器计数值高32位寄存器
   位域定义UNION结构:  SOC_SYSCOUNTER_CNTCV_H32_NS_UNION */
#define SOC_SYSCOUNTER_CNTCV_H32_NS_ADDR(base)        ((base) + (0x100C))





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
 结构名    : SOC_SYSCOUNTER_CNTCR_UNION
 结构说明  : CNTCR 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 计数器控制寄存器（需要在安全模式下进行写访问操作）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]    : 使能计数器：
                                                    0：系统计数器关闭不工作；
                                                    1：系统计数器使能工作。 */
        unsigned int  hdbg     : 1;  /* bit[1]    : Halt-on-Debug。控制Halt-On-Debug信号是否暂停系统计数器更新。
                                                    0：系统计数器忽略Halt-on-debug信号；
                                                    1：当有效Halt-On-Debug信号时，暂停系统计数器更新。 */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留。 */
        unsigned int  fcreq    : 3;  /* bit[8-10] : 频率模式表项选择，只有其中的1bit可以设置为1。修改其中的bit控制选择对应的计数频率。更新这个值将改变系统计数器的反转频率。
                                                    0b001：选择基准频率；
                                                    0b010：选择基准频率2；
                                                    0b100：选择基准频率3；
                                                    其他值：无效。 */
        unsigned int  reserved_1: 21; /* bit[11-31]: 保留。 */
    } reg;
} SOC_SYSCOUNTER_CNTCR_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCR_en_START        (0)
#define SOC_SYSCOUNTER_CNTCR_en_END          (0)
#define SOC_SYSCOUNTER_CNTCR_hdbg_START      (1)
#define SOC_SYSCOUNTER_CNTCR_hdbg_END        (1)
#define SOC_SYSCOUNTER_CNTCR_fcreq_START     (8)
#define SOC_SYSCOUNTER_CNTCR_fcreq_END       (10)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTSR_UNION
 结构说明  : CNTSR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 计数器状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]    : 保留。 */
        unsigned int  dbgh     : 1;  /* bit[1]    : 指示计数器是否由于Halt-on-debug信号被暂停工作；
                                                    0：计数器未被暂停；
                                                    1：计数器被暂停。 */
        unsigned int  reserved_1: 6;  /* bit[2-7]  : 保留。 */
        unsigned int  fcack    : 3;  /* bit[8-10] : 频率改变确认，指示当前工作的频率模式表项。 */
        unsigned int  reserved_2: 21; /* bit[11-31]: 保留。 */
    } reg;
} SOC_SYSCOUNTER_CNTSR_UNION;
#endif
#define SOC_SYSCOUNTER_CNTSR_dbgh_START      (1)
#define SOC_SYSCOUNTER_CNTSR_dbgh_END        (1)
#define SOC_SYSCOUNTER_CNTSR_fcack_START     (8)
#define SOC_SYSCOUNTER_CNTSR_fcack_END       (10)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTCV_L32_UNION
 结构说明  : CNTCV_L32 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 计数器计数值低32位寄存器（需要在安全模式下进行写访问操作）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_l32 : 32; /* bit[0-31]: 计数器计数值的低32位寄存器。
                                                    注意：系统计数器实现原子操作机制。其实现机制是：一次全新的访问，如果访问低32位计数值后，则同时将高32位保存在模块内部，在下次访问高32位数据时，就返回高位数据；如果继续访问低位数据，则使用更新的低位数据。在一次连续的低32位和高32位被访问之后，则认为本次访问操作结束。 */
    } reg;
} SOC_SYSCOUNTER_CNTCV_L32_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_L32_cntcv_l32_START  (0)
#define SOC_SYSCOUNTER_CNTCV_L32_cntcv_l32_END    (31)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTCV_H32_UNION
 结构说明  : CNTCV_H32 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 计数器计数值高32位寄存器（需要在安全模式下进行写访问操作）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_h32 : 32; /* bit[0-31]: 计数器计数值的高32位寄存器。原子访问工作模式见CNTCV_L32。 */
    } reg;
} SOC_SYSCOUNTER_CNTCV_H32_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_H32_cntcv_h32_START  (0)
#define SOC_SYSCOUNTER_CNTCV_H32_cntcv_h32_END    (31)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTFID0_UNION
 结构说明  : CNTFID0 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 频率模式0（需要在安全模式下进行写访问操作）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntfid0 : 32; /* bit[0-31]: 频率模式0。对应于系统计数器工作的基准频率。 */
    } reg;
} SOC_SYSCOUNTER_CNTFID0_UNION;
#endif
#define SOC_SYSCOUNTER_CNTFID0_cntfid0_START  (0)
#define SOC_SYSCOUNTER_CNTFID0_cntfid0_END    (31)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTFID1_UNION
 结构说明  : CNTFID1 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 频率模式1（需要在安全模式下进行写访问操作）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntfid1 : 32; /* bit[0-31]: 频率模式1。对应于系统计数器可选工作频率1。 */
    } reg;
} SOC_SYSCOUNTER_CNTFID1_UNION;
#endif
#define SOC_SYSCOUNTER_CNTFID1_cntfid1_START  (0)
#define SOC_SYSCOUNTER_CNTFID1_cntfid1_END    (31)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTFID2_UNION
 结构说明  : CNTFID2 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 频率模式2（需要在安全模式下进行写访问操作）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntfid2 : 32; /* bit[0-31]: 频率模式2。对应于系统计数器可选工作频率2。 */
    } reg;
} SOC_SYSCOUNTER_CNTFID2_UNION;
#endif
#define SOC_SYSCOUNTER_CNTFID2_cntfid2_START  (0)
#define SOC_SYSCOUNTER_CNTFID2_cntfid2_END    (31)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTCV_L32_NS_UNION
 结构说明  : CNTCV_L32_NS 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
 寄存器说明: 计数器计数值低32位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_l32_ns : 32; /* bit[0-31]: 计数器计数值的低32位寄存器。位于非安全的地址空间。工作方式见CNTCV_L32。 */
    } reg;
} SOC_SYSCOUNTER_CNTCV_L32_NS_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_L32_NS_cntcv_l32_ns_START  (0)
#define SOC_SYSCOUNTER_CNTCV_L32_NS_cntcv_l32_ns_END    (31)


/*****************************************************************************
 结构名    : SOC_SYSCOUNTER_CNTCV_H32_NS_UNION
 结构说明  : CNTCV_H32_NS 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
 寄存器说明: 计数器计数值高32位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_h32_ns : 32; /* bit[0-31]: 计数器计数值的高32位寄存器。位于非安全的地址空间。原子访问工作模式见CNTCV_H32。 */
    } reg;
} SOC_SYSCOUNTER_CNTCV_H32_NS_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_H32_NS_cntcv_h32_ns_START  (0)
#define SOC_SYSCOUNTER_CNTCV_H32_NS_cntcv_h32_ns_END    (31)






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

#endif /* end of soc_syscounter_interface.h */
