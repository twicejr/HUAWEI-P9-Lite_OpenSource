/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_efusec_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:27
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_EFUSEC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_EFUSEC_INTERFACE_H__
#define __SOC_EFUSEC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) EFUSEC
 ****************************************************************************/
/* 寄存器说明：配置寄存器，用于使能读/烧写流程，当读完成时，逻辑自动将RDn清除为0。当烧写完成时，逻辑自动将PGEn清除为0。.
   位域定义UNION结构:  SOC_EFUSEC_CFG_UNION */
#define SOC_EFUSEC_CFG_ADDR(base)                     ((base) + (0x000))

/* 寄存器说明：状态寄存器，用于表述读/烧写状态
   位域定义UNION结构:  SOC_EFUSEC_STATUS_UNION */
#define SOC_EFUSEC_STATUS_ADDR(base)                  ((base) + (0x004))

/* 寄存器说明：读取/烧写地址寄存器。将eufse分组，每组为32bit，对efuse进行烧写或者读取的时候，以一个group为单位
   位域定义UNION结构:  SOC_EFUSEC_EFUSE_GROUP_UNION */
#define SOC_EFUSEC_EFUSE_GROUP_ADDR(base)             ((base) + (0x008))

/* 寄存器说明：每次的烧写值寄存器
   位域定义UNION结构:  SOC_EFUSEC_PG_VALUE_UNION */
#define SOC_EFUSEC_PG_VALUE_ADDR(base)                ((base) + (0x00C))

/* 寄存器说明：efuse内部状态跳转计数器值寄存器。同时该值乘以4作为efuse读操作期间strobe信号脉冲宽度计数值
   位域定义UNION结构:  SOC_EFUSEC_COUNT_UNION */
#define SOC_EFUSEC_COUNT_ADDR(base)                   ((base) + (0x010))

/* 寄存器说明：一次烧写期间strobe信号拉高时间计数器
   位域定义UNION结构:  SOC_EFUSEC_PGM_COUNT_UNION */
#define SOC_EFUSEC_PGM_COUNT_ADDR(base)               ((base) + (0x014))

/* 寄存器说明：存放软件从efuse读取的数据寄存器
   位域定义UNION结构:  SOC_EFUSEC_DATA_UNION */
#define SOC_EFUSEC_DATA_ADDR(base)                    ((base) + (0x018))

/* 寄存器说明：存放efuse上电解复位后从group==127读取的数据寄存器，用于启动判断等。初始值由用户通过efuse烧写确定
   位域定义UNION结构:  SOC_EFUSEC_HW_CFG_UNION */
#define SOC_EFUSEC_HW_CFG_ADDR(base)                  ((base) + (0x01C))





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
                     (1/1) EFUSEC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_EFUSEC_CFG_UNION
 结构说明  : CFG 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 配置寄存器，用于使能读/烧写流程，当读完成时，逻辑自动将RDn清除为0。当烧写完成时，逻辑自动将PGEn清除为0。.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgen     : 1;  /* bit[0]   : 烧写使能信号，当一次烧写完成后，逻辑将此为自动清零
                                                   0：不使能
                                                   1：使能 */
        unsigned int  pre_pg   : 1;  /* bit[1]   : 预烧写使能信号，使能后硬件拉低PGENB信号
                                                   0：不使能
                                                   1：使能 */
        unsigned int  rden     : 1;  /* bit[2]   : 读使能信号，当一次读完成后，逻辑将此为自动清零
                                                   0：不使能
                                                   1：使能 */
        unsigned int  aib_sel  : 1;  /* bit[3]   : AIB接口选择信号
                                                   0：选择AIB操作efuse控制器
                                                   1：选择APB操作efuse控制器 */
        unsigned int  reserved_0: 1;  /* bit[4]   : 保留 */
        unsigned int  pd_en    : 1;  /* bit[5]   : efuse power-down控制
                                                   0：不使能
                                                   1：使能 */
        unsigned int  reserved_1: 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_EFUSEC_CFG_UNION;
#endif
#define SOC_EFUSEC_CFG_pgen_START      (0)
#define SOC_EFUSEC_CFG_pgen_END        (0)
#define SOC_EFUSEC_CFG_pre_pg_START    (1)
#define SOC_EFUSEC_CFG_pre_pg_END      (1)
#define SOC_EFUSEC_CFG_rden_START      (2)
#define SOC_EFUSEC_CFG_rden_END        (2)
#define SOC_EFUSEC_CFG_aib_sel_START   (3)
#define SOC_EFUSEC_CFG_aib_sel_END     (3)
#define SOC_EFUSEC_CFG_pd_en_START     (5)
#define SOC_EFUSEC_CFG_pd_en_END       (5)


/*****************************************************************************
 结构名    : SOC_EFUSEC_STATUS_UNION
 结构说明  : STATUS 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 状态寄存器，用于表述读/烧写状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_status    : 1;  /* bit[0]   : 烧写状态。
                                                       0：未完成
                                                       1：完成 */
        unsigned int  rd_status    : 1;  /* bit[1]   : efuse读状态
                                                       0：未完成
                                                       1：完成一次读操作 */
        unsigned int  pgenb_status : 1;  /* bit[2]   : 预烧写置位完成状态
                                                       0：未完成
                                                       1：完成预烧写置位状态 */
        unsigned int  rd_error     : 1;  /* bit[3]   : efuse当前group地址是否是禁止的
                                                       0：否
                                                       1：是 */
        unsigned int  pd_status    : 1;  /* bit[4]   : power-down状态
                                                       0：正常状态
                                                       1：power-down状态 */
        unsigned int  reserved     : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_EFUSEC_STATUS_UNION;
#endif
#define SOC_EFUSEC_STATUS_pg_status_START     (0)
#define SOC_EFUSEC_STATUS_pg_status_END       (0)
#define SOC_EFUSEC_STATUS_rd_status_START     (1)
#define SOC_EFUSEC_STATUS_rd_status_END       (1)
#define SOC_EFUSEC_STATUS_pgenb_status_START  (2)
#define SOC_EFUSEC_STATUS_pgenb_status_END    (2)
#define SOC_EFUSEC_STATUS_rd_error_START      (3)
#define SOC_EFUSEC_STATUS_rd_error_END        (3)
#define SOC_EFUSEC_STATUS_pd_status_START     (4)
#define SOC_EFUSEC_STATUS_pd_status_END       (4)


/*****************************************************************************
 结构名    : SOC_EFUSEC_EFUSE_GROUP_UNION
 结构说明  : EFUSE_GROUP 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 读取/烧写地址寄存器。将eufse分组，每组为32bit，对efuse进行烧写或者读取的时候，以一个group为单位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efuse_group : 7;  /* bit[0-6] : 读取/烧写地址group, */
        unsigned int  reserved    : 25; /* bit[7-31]: 保留 */
    } reg;
} SOC_EFUSEC_EFUSE_GROUP_UNION;
#endif
#define SOC_EFUSEC_EFUSE_GROUP_efuse_group_START  (0)
#define SOC_EFUSEC_EFUSE_GROUP_efuse_group_END    (6)


/*****************************************************************************
 结构名    : SOC_EFUSEC_PG_VALUE_UNION
 结构说明  : PG_VALUE 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 每次的烧写值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_value : 32; /* bit[0-31]: 一组32bit的烧写信息
                                                   0：不烧写该bit；
                                                   1：烧写该bit； */
    } reg;
} SOC_EFUSEC_PG_VALUE_UNION;
#endif
#define SOC_EFUSEC_PG_VALUE_pg_value_START  (0)
#define SOC_EFUSEC_PG_VALUE_pg_value_END    (31)


/*****************************************************************************
 结构名    : SOC_EFUSEC_COUNT_UNION
 结构说明  : COUNT 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: efuse内部状态跳转计数器值寄存器。同时该值乘以4作为efuse读操作期间strobe信号脉冲宽度计数值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec_count : 8;  /* bit[0-7] : EFUSE内部状态跳转使用的计数值 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_EFUSEC_COUNT_UNION;
#endif
#define SOC_EFUSEC_COUNT_efusec_count_START  (0)
#define SOC_EFUSEC_COUNT_efusec_count_END    (7)


/*****************************************************************************
 结构名    : SOC_EFUSEC_PGM_COUNT_UNION
 结构说明  : PGM_COUNT 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 一次烧写期间strobe信号拉高时间计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgm_count : 16; /* bit[0-15] : 一次烧写期间strobe信号拉高时间计数器（以参考时钟为计数时钟） */
        unsigned int  reserved  : 16; /* bit[16-31]:  */
    } reg;
} SOC_EFUSEC_PGM_COUNT_UNION;
#endif
#define SOC_EFUSEC_PGM_COUNT_pgm_count_START  (0)
#define SOC_EFUSEC_PGM_COUNT_pgm_count_END    (15)


/*****************************************************************************
 结构名    : SOC_EFUSEC_DATA_UNION
 结构说明  : DATA 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 存放软件从efuse读取的数据寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efuse_data : 32; /* bit[0-31]: 存放软件从efuse读取的数据 */
    } reg;
} SOC_EFUSEC_DATA_UNION;
#endif
#define SOC_EFUSEC_DATA_efuse_data_START  (0)
#define SOC_EFUSEC_DATA_efuse_data_END    (31)


/*****************************************************************************
 结构名    : SOC_EFUSEC_HW_CFG_UNION
 结构说明  : HW_CFG 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 存放efuse上电解复位后从group==127读取的数据寄存器，用于启动判断等。初始值由用户通过efuse烧写确定
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec_hw_cfg : 32; /* bit[0-31]: 存放efuse上电解复位后从group==15读取的数据，详细信息见EFUSE信息排布表 */
    } reg;
} SOC_EFUSEC_HW_CFG_UNION;
#endif
#define SOC_EFUSEC_HW_CFG_efusec_hw_cfg_START  (0)
#define SOC_EFUSEC_HW_CFG_efusec_hw_cfg_END    (31)






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

#endif /* end of soc_efusec_interface.h */
