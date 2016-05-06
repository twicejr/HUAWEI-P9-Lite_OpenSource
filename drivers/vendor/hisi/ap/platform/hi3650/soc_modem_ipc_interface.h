/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_modem_ipc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:20
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_MODEM_IPC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_MODEM_IPC_INTERFACE_H__
#define __SOC_MODEM_IPC_INTERFACE_H__

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
/* 寄存器说明：模块版本寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_VERSION_UNION */
#define SOC_MODEM_IPC_IPC_VERSION_ADDR(base)          ((base) + (0x000))

/* 寄存器说明：快速中断原始中断寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_CPU_RAW_INT_UNION */
#define SOC_MODEM_IPC_IPC_CPU_RAW_INT_ADDR(base, i)   ((base) + (0x400+(i)*0x10))

/* 寄存器说明：快速中断掩码寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_CPU_INT_MASK_UNION */
#define SOC_MODEM_IPC_IPC_CPU_INT_MASK_ADDR(base, i)  ((base) + (0x404+(i)*0x10))

/* 寄存器说明：快速中断状态寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_CPU_INT_STAT_UNION */
#define SOC_MODEM_IPC_IPC_CPU_INT_STAT_ADDR(base, i)  ((base) + (0x408+(i)*0x10))

/* 寄存器说明：快速中断清除寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_CPU_INT_CLR_UNION */
#define SOC_MODEM_IPC_IPC_CPU_INT_CLR_ADDR(base, i)   ((base) + (0x40C+(i)*0x10))

/* 寄存器说明：信号量释放原始中断寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_SEM_RAW_INT_UNION */
#define SOC_MODEM_IPC_IPC_SEM_RAW_INT_ADDR(base, j)   ((base) + (0x600+(j)*0x10))

/* 寄存器说明：信号量释放中断掩码寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_SEM_INT_MASK_UNION */
#define SOC_MODEM_IPC_IPC_SEM_INT_MASK_ADDR(base, j)  ((base) + (0x604+(j)*0x10))

/* 寄存器说明：信号量释放中断状态寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_SEM_INT_STAT_UNION */
#define SOC_MODEM_IPC_IPC_SEM_INT_STAT_ADDR(base, j)  ((base) + (0x608+(j)*0x10))

/* 寄存器说明：信号量释放中断清除寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_SEM_INT_CLR_UNION */
#define SOC_MODEM_IPC_IPC_SEM_INT_CLR_ADDR(base, j)   ((base) + (0x60C+(j)*0x10))

/* 寄存器说明：信号量请求寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_HS_CTRL_UNION */
#define SOC_MODEM_IPC_IPC_HS_CTRL_ADDR(base, j, k)    ((base) + (0x800+(j)*0x100+(k)*0x8))

/* 寄存器说明：信号量状态寄存器
   位域定义UNION结构:  SOC_MODEM_IPC_IPC_HS_STAT_UNION */
#define SOC_MODEM_IPC_IPC_HS_STAT_ADDR(base, j, k)    ((base) + (0x804+(j)*0x100+(k)*0x8))





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
 结构名    : SOC_MODEM_IPC_IPC_VERSION_UNION
 结构说明  : IPC_VERSION 寄存器结构定义。地址偏移量:0x000，初值:0x67560100，宽度:32
 寄存器说明: 模块版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_version : 32; /* bit[0-31]: IPC 模块版本寄存器。 */
    } reg;
} SOC_MODEM_IPC_IPC_VERSION_UNION;
#endif
#define SOC_MODEM_IPC_IPC_VERSION_ipc_version_START  (0)
#define SOC_MODEM_IPC_IPC_VERSION_ipc_version_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_CPU_RAW_INT_UNION
 结构说明  : IPC_CPU_RAW_INT 寄存器结构定义。地址偏移量:0x400+(i)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 快速中断原始中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_raw_int : 32; /* bit[0-31]: 快速中断原始中断寄存器。地址[7:4]用于区分产生中断的信号线。
                                                          每1Bit代表1个独立的原始中断。写1产生中断，写0无效。
                                                          1'b0: 无中断；
                                                          1'b1: 有中断。 */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_RAW_INT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_RAW_INT_ipc_cpu_raw_int_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_RAW_INT_ipc_cpu_raw_int_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_CPU_INT_MASK_UNION
 结构说明  : IPC_CPU_INT_MASK 寄存器结构定义。地址偏移量:0x404+(i)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 快速中断掩码寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_int_mask : 32; /* bit[0-31]: 快速中断掩码寄存器寄存器。地址[7:4]用于区分产生中断的信号线。
                                                           每1Bit对应1个独立的中断掩码。
                                                           1'b0: 中断屏蔽；
                                                           1'b1: 中断使能。 */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_INT_MASK_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_INT_MASK_ipc_cpu_int_mask_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_INT_MASK_ipc_cpu_int_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_CPU_INT_STAT_UNION
 结构说明  : IPC_CPU_INT_STAT 寄存器结构定义。地址偏移量:0x408+(i)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 快速中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_int_stat : 32; /* bit[0-31]: 屏蔽后的快速中断状态寄存器。地址[7:4]用于区分产生中断的信号线。
                                                           为ipc_cpu_raw_int和ipc_cpu_int_mask的按位与。
                                                           1'b0: 无中断；
                                                           1'b1: 有中断。 */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_INT_STAT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_INT_STAT_ipc_cpu_int_stat_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_INT_STAT_ipc_cpu_int_stat_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_CPU_INT_CLR_UNION
 结构说明  : IPC_CPU_INT_CLR 寄存器结构定义。地址偏移量:0x40C+(i)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 快速中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_cpu_int_clr : 32; /* bit[0-31]: 快速中断清除寄存器。地址[7:4]用于区分产生中断的信号线。
                                                          每1Bit对应1个独立的中断清除。向某Bit写1'b1将导致ipc_cpu_raw_int中的对应Bit清零，写1'b0无效。 */
    } reg;
} SOC_MODEM_IPC_IPC_CPU_INT_CLR_UNION;
#endif
#define SOC_MODEM_IPC_IPC_CPU_INT_CLR_ipc_cpu_int_clr_START  (0)
#define SOC_MODEM_IPC_IPC_CPU_INT_CLR_ipc_cpu_int_clr_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_SEM_RAW_INT_UNION
 结构说明  : IPC_SEM_RAW_INT 寄存器结构定义。地址偏移量:0x600+(j)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 信号量释放原始中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_raw_int : 32; /* bit[0-31]: 信号量释放原始中断。地址[6:4]用于区分产生中断的信号线。
                                                          每1Bit代表1个独立的原始中断。
                                                          1'b0: 无中断；
                                                          1'b1: 有中断。 */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_RAW_INT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_RAW_INT_ipc_sem_raw_int_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_RAW_INT_ipc_sem_raw_int_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_SEM_INT_MASK_UNION
 结构说明  : IPC_SEM_INT_MASK 寄存器结构定义。地址偏移量:0x604+(j)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 信号量释放中断掩码寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_int_mask : 32; /* bit[0-31]: 信号量释放中断掩码寄存器。地址[6:4]用于区分产生中断的信号线。
                                                           每1Bit对应1个独立的中断掩码。
                                                           1'b0: 中断屏蔽；
                                                           1'b1: 中断使能。 */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_INT_MASK_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_INT_MASK_ipc_sem_int_mask_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_INT_MASK_ipc_sem_int_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_SEM_INT_STAT_UNION
 结构说明  : IPC_SEM_INT_STAT 寄存器结构定义。地址偏移量:0x608+(j)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 信号量释放中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_int_stat : 32; /* bit[0-31]: 屏蔽后的信号量释放中断状态寄存器。地址[6:4]用于区分产生中断的信号线。
                                                           为ipc_sem_raw_int和ipc_sem_int_mask的按位与。
                                                           1'b0: 无中断
                                                           1'b1: 有中断 */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_INT_STAT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_INT_STAT_ipc_sem_int_stat_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_INT_STAT_ipc_sem_int_stat_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_SEM_INT_CLR_UNION
 结构说明  : IPC_SEM_INT_CLR 寄存器结构定义。地址偏移量:0x60C+(j)*0x10，初值:0x00000000，宽度:32
 寄存器说明: 信号量释放中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipc_sem_int_clr : 32; /* bit[0-31]: 信号量释放中断清除寄存器。地址[6:4]用于区分产生中断的信号线。
                                                          每1Bit对应1个独立的中断清除。向某Bit写1'b1将导致ipc_sem_raw_int中的对应Bit清零，写1'b0无效。 */
    } reg;
} SOC_MODEM_IPC_IPC_SEM_INT_CLR_UNION;
#endif
#define SOC_MODEM_IPC_IPC_SEM_INT_CLR_ipc_sem_int_clr_START  (0)
#define SOC_MODEM_IPC_IPC_SEM_INT_CLR_ipc_sem_int_clr_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_HS_CTRL_UNION
 结构说明  : IPC_HS_CTRL 寄存器结构定义。地址偏移量:0x800+(j)*0x100+(k)*0x8，初值:0x00000000，宽度:32
 寄存器说明: 信号量请求寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_ctrl_id   : 3;  /* bit[0-2] : 信号量占用处理器ID寄存器。地址[10:8]用于区分不同的处理器访问。
                                                       当读返回hs_ctrl_lock有效时，hs_ctrl_id表示占有该信号量的处理器ID号。 */
        unsigned int  hs_ctrl_lock : 1;  /* bit[3]   : 信号量请求占用寄存器。地址[10:8]用于区分不同的处理器访问。
                                                       读该寄存器，返回1'b0表示该信号量占用成功；返回1'b1表示该信号量申请占用失败。
                                                       写该寄存器，写1'b0表示释放该信号量，写1'b1无效。 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留位。 */
    } reg;
} SOC_MODEM_IPC_IPC_HS_CTRL_UNION;
#endif
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_id_START    (0)
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_id_END      (2)
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_lock_START  (3)
#define SOC_MODEM_IPC_IPC_HS_CTRL_hs_ctrl_lock_END    (3)


/*****************************************************************************
 结构名    : SOC_MODEM_IPC_IPC_HS_STAT_UNION
 结构说明  : IPC_HS_STAT 寄存器结构定义。地址偏移量:0x804+(j)*0x100+(k)*0x8，初值:0x00000000，宽度:32
 寄存器说明: 信号量状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_status_id   : 3;  /* bit[0-2] : 信号量占用处理器ID寄存器。地址[10:8]用于区分不同的处理器访问。
                                                         当读返回hs_status_lock有效时，hs_status_id表示占有该信号量的处理器ID号。 */
        unsigned int  hs_status_lock : 1;  /* bit[3]   : 信号量占用状态寄存器。地址[10:8]用于区分不同的处理器访问。
                                                         读该寄存器，返回1'b0表示该信号量空闲，返回1'b1表示该信号量已被占用。 */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留位。 */
    } reg;
} SOC_MODEM_IPC_IPC_HS_STAT_UNION;
#endif
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_id_START    (0)
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_id_END      (2)
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_lock_START  (3)
#define SOC_MODEM_IPC_IPC_HS_STAT_hs_status_lock_END    (3)






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

#endif /* end of soc_modem_ipc_interface.h */
