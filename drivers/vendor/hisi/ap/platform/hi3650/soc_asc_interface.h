/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_asc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:04
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ASC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ASC_INTERFACE_H__
#define __SOC_ASC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_ASC
 ****************************************************************************/
/* 寄存器说明：ASC模块使能/Bypass寄存器。
   位域定义UNION结构:  SOC_ASC_EN_UNION */
#define SOC_ASC_EN_ADDR(base)                         ((base) + (0x000))

/* 寄存器说明：regioni安全访问权限配置寄存器。
   位域定义UNION结构:  SOC_ASC_REGION_NON_SECURE_UNION */
#define SOC_ASC_REGION_NON_SECURE_ADDR(base, i)       ((base) + (0x010+0x20*(i)))

/* 寄存器说明：regioni起始地址低位寄存器。
   位域定义UNION结构:  SOC_ASC_REGION_START_ADDR_LOW_UNION */
#define SOC_ASC_REGION_START_ADDR_LOW_ADDR(base, i)   ((base) + (0x014+0x20*(i)))

/* 寄存器说明：regioni起始地址高位寄存器。
   位域定义UNION结构:  SOC_ASC_REGION_START_ADDR_HIGH_UNION */
#define SOC_ASC_REGION_START_ADDR_HIGH_ADDR(base, i)  ((base) + (0x018+0x20*(i)))

/* 寄存器说明：regioni结束地址低32位寄存器。
   位域定义UNION结构:  SOC_ASC_REGION_END_ADDR_LOW_UNION */
#define SOC_ASC_REGION_END_ADDR_LOW_ADDR(base, i)     ((base) + (0x01C+0x20*(i)))

/* 寄存器说明：regioni结束地址高位寄存器。
   位域定义UNION结构:  SOC_ASC_REGION_END_ADDR_HIGH_UNION */
#define SOC_ASC_REGION_END_ADDR_HIGH_ADDR(base, i)    ((base) + (0x020+0x20*(i)))

/* 寄存器说明：中断状态寄存器。
   位域定义UNION结构:  SOC_ASC_INT_STATUS_UNION */
#define SOC_ASC_INT_STATUS_ADDR(base)                 ((base) + (0x120))

/* 寄存器说明：中断清除寄存器。
   位域定义UNION结构:  SOC_ASC_INT_CLEAR_UNION */
#define SOC_ASC_INT_CLEAR_ADDR(base)                  ((base) + (0x124))

/* 寄存器说明：越权操作地址低位寄存器。
   位域定义UNION结构:  SOC_ASC_FAIL_ADDR_LOW_UNION */
#define SOC_ASC_FAIL_ADDR_LOW_ADDR(base)              ((base) + (0x128))

/* 寄存器说明：越权操作地址高位寄存器。
   位域定义UNION结构:  SOC_ASC_FAIL_ADDR_HIGH_UNION */
#define SOC_ASC_FAIL_ADDR_HIGH_ADDR(base)             ((base) + (0x12C))

/* 寄存器说明：越权操作ID寄存器。
   位域定义UNION结构:  SOC_ASC_FAIL_ID_UNION */
#define SOC_ASC_FAIL_ID_ADDR(base)                    ((base) + (0x130))

/* 寄存器说明：越权操作类型寄存器。
   位域定义UNION结构:  SOC_ASC_FAIL_INFO_UNION */
#define SOC_ASC_FAIL_INFO_ADDR(base)                  ((base) + (0x134))





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
                     (1/1) register_ASC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ASC_EN_UNION
 结构说明  : EN 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: ASC模块使能/Bypass寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asc_en   : 1;  /* bit[0]   : 0-asc bypass，default。
                                                   1-asc enable。
                                                   ASC Bypass模式下，ASC模块的AXI Master接口和AXI Slave接口是直通的。
                                                   ASC Enable模式下，ASC模块会检查当前读写地址与对应的PROT[1]信号是否与Region0~Region7的地址和安全属性匹配，如匹配，则将AXI slave接口信号透传给对应的AXI Master接口信号。若不匹配，则根据访问类型将WSTRB置为全零，或将读数据置为全零，并返回ERROR响应，上报中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASC_EN_UNION;
#endif
#define SOC_ASC_EN_asc_en_START    (0)
#define SOC_ASC_EN_asc_en_END      (0)


/*****************************************************************************
 结构名    : SOC_ASC_REGION_NON_SECURE_UNION
 结构说明  : REGION_NON_SECURE 寄存器结构定义。地址偏移量:0x010+0x20*(i)，初值:0x00000000，宽度:32
 寄存器说明: regioni安全访问权限配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  region_non_secure : 1;  /* bit[0]   : regioni安全访问权限配置。
                                                            0-regioni仅允许安全访问。
                                                            1-regioni允许安全访问和非安全访问。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASC_REGION_NON_SECURE_UNION;
#endif
#define SOC_ASC_REGION_NON_SECURE_region_non_secure_START  (0)
#define SOC_ASC_REGION_NON_SECURE_region_non_secure_END    (0)


/*****************************************************************************
 结构名    : SOC_ASC_REGION_START_ADDR_LOW_UNION
 结构说明  : REGION_START_ADDR_LOW 寄存器结构定义。地址偏移量:0x014+0x20*(i)，初值:0x00000000，宽度:32
 寄存器说明: regioni起始地址低位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved              : 12; /* bit[0-11] : 保留。 */
        unsigned int  region_start_addr_low : 20; /* bit[12-31]: regioni起始地址的bit[31:12]。
                                                                 Region首末地址的最小配置粒度为4KB。因此，起始地址的低位bit[11:0]在ASC模块内部接死为0x000。结束地址的低位bit[11:0]在ASC内部接死为0xFFF。 */
    } reg;
} SOC_ASC_REGION_START_ADDR_LOW_UNION;
#endif
#define SOC_ASC_REGION_START_ADDR_LOW_region_start_addr_low_START  (12)
#define SOC_ASC_REGION_START_ADDR_LOW_region_start_addr_low_END    (31)


/*****************************************************************************
 结构名    : SOC_ASC_REGION_START_ADDR_HIGH_UNION
 结构说明  : REGION_START_ADDR_HIGH 寄存器结构定义。地址偏移量:0x018+0x20*(i)，初值:0x00000000，宽度:32
 寄存器说明: regioni起始地址高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  region_start_addr_high : 32; /* bit[0-31]: regioni起始地址的高位。 */
    } reg;
} SOC_ASC_REGION_START_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_REGION_START_ADDR_HIGH_region_start_addr_high_START  (0)
#define SOC_ASC_REGION_START_ADDR_HIGH_region_start_addr_high_END    (31)


/*****************************************************************************
 结构名    : SOC_ASC_REGION_END_ADDR_LOW_UNION
 结构说明  : REGION_END_ADDR_LOW 寄存器结构定义。地址偏移量:0x01C+0x20*(i)，初值:0x00000FFF，宽度:32
 寄存器说明: regioni结束地址低32位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved            : 12; /* bit[0-11] : 保留。 */
        unsigned int  region_end_addr_low : 20; /* bit[12-31]: regioni结束地址的bit[31:0]。
                                                               Region首末地址的最小配置粒度为4KB。因此，起始地址的低位bit[11:0]在ASC模块内部接死为0x000。结束地址的低位bit[11:0]在ASC内部接死为0xFFF。 */
    } reg;
} SOC_ASC_REGION_END_ADDR_LOW_UNION;
#endif
#define SOC_ASC_REGION_END_ADDR_LOW_region_end_addr_low_START  (12)
#define SOC_ASC_REGION_END_ADDR_LOW_region_end_addr_low_END    (31)


/*****************************************************************************
 结构名    : SOC_ASC_REGION_END_ADDR_HIGH_UNION
 结构说明  : REGION_END_ADDR_HIGH 寄存器结构定义。地址偏移量:0x020+0x20*(i)，初值:0x00000000，宽度:32
 寄存器说明: regioni结束地址高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  region_end_addr_high : 32; /* bit[0-31]: regioni结束地址的高位部分。 */
    } reg;
} SOC_ASC_REGION_END_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_REGION_END_ADDR_HIGH_region_end_addr_high_START  (0)
#define SOC_ASC_REGION_END_ADDR_HIGH_region_end_addr_high_END    (31)


/*****************************************************************************
 结构名    : SOC_ASC_INT_STATUS_UNION
 结构说明  : INT_STATUS 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: 中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_status : 1;  /* bit[0]   : 0-无中断。
                                                     1-越权操作中断。当非安全操作访问仅允许安全访问的region时，该中断有效。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASC_INT_STATUS_UNION;
#endif
#define SOC_ASC_INT_STATUS_int_status_START  (0)
#define SOC_ASC_INT_STATUS_int_status_END    (0)


/*****************************************************************************
 结构名    : SOC_ASC_INT_CLEAR_UNION
 结构说明  : INT_CLEAR 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_clear : 1;  /* bit[0]   : 写1清除对应中断。写0无影响。读总是返回0x0。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ASC_INT_CLEAR_UNION;
#endif
#define SOC_ASC_INT_CLEAR_int_clear_START  (0)
#define SOC_ASC_INT_CLEAR_int_clear_END    (0)


/*****************************************************************************
 结构名    : SOC_ASC_FAIL_ADDR_LOW_UNION
 结构说明  : FAIL_ADDR_LOW 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: 越权操作地址低位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_addr_low : 32; /* bit[0-31]: 发生越权操作的访问地址的低bit[31:0]。 */
    } reg;
} SOC_ASC_FAIL_ADDR_LOW_UNION;
#endif
#define SOC_ASC_FAIL_ADDR_LOW_fail_addr_low_START  (0)
#define SOC_ASC_FAIL_ADDR_LOW_fail_addr_low_END    (31)


/*****************************************************************************
 结构名    : SOC_ASC_FAIL_ADDR_HIGH_UNION
 结构说明  : FAIL_ADDR_HIGH 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: 越权操作地址高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_addr_high : 32; /* bit[0-31]: 发生越权操作的访问地址的高位部分。 */
    } reg;
} SOC_ASC_FAIL_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_FAIL_ADDR_HIGH_fail_addr_high_START  (0)
#define SOC_ASC_FAIL_ADDR_HIGH_fail_addr_high_END    (31)


/*****************************************************************************
 结构名    : SOC_ASC_FAIL_ID_UNION
 结构说明  : FAIL_ID 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: 越权操作ID寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_id  : 24; /* bit[0-23] : 发生越权操作的ID值。 */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_ASC_FAIL_ID_UNION;
#endif
#define SOC_ASC_FAIL_ID_fail_id_START   (0)
#define SOC_ASC_FAIL_ID_fail_id_END     (23)


/*****************************************************************************
 结构名    : SOC_ASC_FAIL_INFO_UNION
 结构说明  : FAIL_INFO 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: 越权操作类型寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_wr    : 1;  /* bit[0]    : 发生越权写操作。
                                                      0-没有越权写访问。
                                                      1-发生越权写访问。 */
        unsigned int  fail_rd    : 1;  /* bit[1]    : 发生越权读操作。
                                                      0-没有越权读访问。
                                                      1-发生越权读访问。 */
        unsigned int  fail_len   : 4;  /* bit[2-5]  : 发生越权操作的LEN信号值。
                                                      如果是越权读操作，返回AXI SLAVE接口的ARLEN信号值。
                                                      如果是越权写操作，返回AXI SLAVE接口的AWLEN信号值。 */
        unsigned int  fail_size  : 3;  /* bit[6-8]  : 发生越权操作的SIZE信号值。
                                                      如果是越权读操作，返回AXI SLAVE接口的ARSIZE信号值。
                                                      如果是越权写操作，返回AXI SLAVE接口的AWSIZE信号值。 */
        unsigned int  fail_burst : 2;  /* bit[9-10] : 发生越权操作的BURST信号值。
                                                      如果是越权读操作，返回AXI SLAVE接口的ARBURST信号值。
                                                      如果是越权写操作，返回AXI SLAVE接口的AWBURST信号值。 */
        unsigned int  fail_lock  : 2;  /* bit[11-12]: 发生越权操作的LOCK信号值。
                                                      如果是越权读操作，返回AXI SLAVE接口的ARLOCK信号值。
                                                      如果是越权写操作，返回AXI SLAVE接口的AWLOCK信号值。 */
        unsigned int  fail_cache : 4;  /* bit[13-16]: 发生越权操作的CACHE信号值。
                                                      如果是越权读操作，返回AXI SLAVE接口的ARCACHE信号值。
                                                      如果是越权写操作，返回AXI SLAVE接口的AWCACHE信号值。 */
        unsigned int  fail_prot  : 3;  /* bit[17-19]: 发生越权操作的PROT信号值。
                                                      如果是越权读操作，返回AXI SLAVE接口的ARPROT信号值。
                                                      如果是越权写操作，返回AXI SLAVE接口的AWPROT信号值。 */
        unsigned int  reserved   : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_ASC_FAIL_INFO_UNION;
#endif
#define SOC_ASC_FAIL_INFO_fail_wr_START     (0)
#define SOC_ASC_FAIL_INFO_fail_wr_END       (0)
#define SOC_ASC_FAIL_INFO_fail_rd_START     (1)
#define SOC_ASC_FAIL_INFO_fail_rd_END       (1)
#define SOC_ASC_FAIL_INFO_fail_len_START    (2)
#define SOC_ASC_FAIL_INFO_fail_len_END      (5)
#define SOC_ASC_FAIL_INFO_fail_size_START   (6)
#define SOC_ASC_FAIL_INFO_fail_size_END     (8)
#define SOC_ASC_FAIL_INFO_fail_burst_START  (9)
#define SOC_ASC_FAIL_INFO_fail_burst_END    (10)
#define SOC_ASC_FAIL_INFO_fail_lock_START   (11)
#define SOC_ASC_FAIL_INFO_fail_lock_END     (12)
#define SOC_ASC_FAIL_INFO_fail_cache_START  (13)
#define SOC_ASC_FAIL_INFO_fail_cache_END    (16)
#define SOC_ASC_FAIL_INFO_fail_prot_START   (17)
#define SOC_ASC_FAIL_INFO_fail_prot_END     (19)






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

#endif /* end of soc_asc_interface.h */
