/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cs_top_funnel_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-11-20 11:31:13
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月20日
    作    者   : l00352922
    修改内容   : 从《Hi3660V100 SOC寄存器手册_CS_TOP_FUNNEL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CS_TOP_FUNNEL_INTERFACE_H__
#define __SOC_CS_TOP_FUNNEL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) TOP_FUNNEL
 ****************************************************************************/
/* 寄存器说明：Funnel控制寄存器。
   位域定义UNION结构:  SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_UNION */
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_ADDR(base)  ((base) + (0x000))

/* 寄存器说明：Funnel优先级控制寄存器。
   位域定义UNION结构:  SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_UNION */
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_ADDR(base) ((base) + (0x004))

/* 寄存器说明：Funnel锁定访问寄存器。
   位域定义UNION结构:  SOC_CS_TOP_FUNNEL_FUNNEL_LAR_UNION */
#define SOC_CS_TOP_FUNNEL_FUNNEL_LAR_ADDR(base)       ((base) + (0xFB0))

/* 寄存器说明：Funnel锁定状态寄存器。
   位域定义UNION结构:  SOC_CS_TOP_FUNNEL_FUNNEL_LSR_UNION */
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_ADDR(base)       ((base) + (0xFB4))





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
                     (1/1) TOP_FUNNEL
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_UNION
 结构说明  : FUNNEL_CTRL_REG 寄存器结构定义。地址偏移量:0x000，初值:0x00000300，宽度:32
 寄存器说明: Funnel控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable   : 7;  /* bit[0-6]  : bit[0]~bit[6]分别对应port0~port6。
                                                    0：slave port disabled
                                                    1：slave port enabled
                                                    port对应关系如下，保留端口请勿使能。
                                                    port0:AP
                                                    port1:reserved
                                                    port2:reserved
                                                    port3:modem_a9
                                                    port4:stm-500
                                                    port5:isp_a7
                                                    port6:iomcu_m7 */
        unsigned int  reserved_0: 1;  /* bit[7]    : Reserved */
        unsigned int  holdtime : 4;  /* bit[8-11] : Funnel ATB slave端口一次最少接收的transaction数。设置hold time是为了降低端口频繁切换对trace性能带来的影响。最少接收的transaction数为hold time值加1，取值范围b0000~b1110，b1111保留。 */
        unsigned int  reserved_1: 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_enable_START    (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_enable_END      (6)
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_holdtime_START  (8)
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_holdtime_END    (11)


/*****************************************************************************
 结构名    : SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_UNION
 结构说明  : FUNNEL_PRIORITY_CTRL_REG 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: Funnel优先级控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  priport0 : 3;  /* bit[0-2]  : 端口0优先级设置 */
        unsigned int  priport1 : 3;  /* bit[3-5]  : 端口1优先级设置 */
        unsigned int  priport2 : 3;  /* bit[6-8]  : 端口2优先级设置 */
        unsigned int  priport3 : 3;  /* bit[9-11] : 端口3优先级设置 */
        unsigned int  priport4 : 3;  /* bit[12-14]: 端口4优先级设置 */
        unsigned int  priport5 : 3;  /* bit[15-17]: 端口5优先级设置 */
        unsigned int  priport6 : 3;  /* bit[18-20]: 端口6优先级设置，数值越低，优先级越高；当设置值相同时，编号小的端口优先级较高。可能的取值如下：
                                                    b000：优先级0
                                                    b001：优先级1
                                                    b010：优先级2
                                                    b011：优先级3
                                                    b100：优先级4
                                                    b101：优先级5
                                                    b110：优先级6
                                                    b111：优先级7 */
        unsigned int  reserved : 11; /* bit[21-31]: Reserved */
    } reg;
} SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport0_START  (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport0_END    (2)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport1_START  (3)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport1_END    (5)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport2_START  (6)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport2_END    (8)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport3_START  (9)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport3_END    (11)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport4_START  (12)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport4_END    (14)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport5_START  (15)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport5_END    (17)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport6_START  (18)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport6_END    (20)


/*****************************************************************************
 结构名    : SOC_CS_TOP_FUNNEL_FUNNEL_LAR_UNION
 结构说明  : FUNNEL_LAR 寄存器结构定义。地址偏移量:0xFB0，初值:0x00000000，宽度:32
 寄存器说明: Funnel锁定访问寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: 写入0xC5ACCE55进行解锁，然后才可以正常配置其他寄存器；写入其他任何值后再次锁定。 */
    } reg;
} SOC_CS_TOP_FUNNEL_FUNNEL_LAR_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_LAR_key_START  (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LAR_key_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_FUNNEL_FUNNEL_LSR_UNION
 结构说明  : FUNNEL_LSR 寄存器结构定义。地址偏移量:0xFB4，初值:0x00000003，宽度:32
 寄存器说明: Funnel锁定状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sli      : 1;  /* bit[0]   : 指示期间是否支持锁定机制：
                                                   0：组件不支持锁定机制
                                                   1：组件支持锁定机制 */
        unsigned int  slk      : 1;  /* bit[1]   : 组件的当前锁定状态：
                                                   0：已解锁，允许写操作
                                                   1：已锁定，不允许写操作，可读 */
        unsigned int  ntt      : 1;  /* bit[2]   : 指示锁定访问寄存器为32-bit */
        unsigned int  reserved : 29; /* bit[3-31]: Reserved */
    } reg;
} SOC_CS_TOP_FUNNEL_FUNNEL_LSR_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_sli_START       (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_sli_END         (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_slk_START       (1)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_slk_END         (1)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_ntt_START       (2)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_ntt_END         (2)






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

#endif /* end of soc_cs_top_funnel_interface.h */
