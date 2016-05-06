/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cs_cti_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-11-20 11:31:00
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月20日
    作    者   : l00352922
    修改内容   : 从《Hi3660V100 SOC寄存器手册_CS_CTI.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CS_CTI_INTERFACE_H__
#define __SOC_CS_CTI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CTI
 ****************************************************************************/
/* 寄存器说明：CTI控制寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_CONTROL_UNION */
#define SOC_CS_CTI_CTI_CONTROL_ADDR(base)             ((base) + (0x000))

/* 寄存器说明：CTI中断确认寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INTACK_UNION */
#define SOC_CS_CTI_CTI_INTACK_ADDR(base)              ((base) + (0x010))

/* 寄存器说明：CTI trigger set寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_APPSET_UNION */
#define SOC_CS_CTI_CTI_APPSET_ADDR(base)              ((base) + (0x014))

/* 寄存器说明：CTI trigger clear寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_APPCLEAR_UNION */
#define SOC_CS_CTI_CTI_APPCLEAR_ADDR(base)            ((base) + (0x018))

/* 寄存器说明：CTI trigger pulse寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_APPPULSE_UNION */
#define SOC_CS_CTI_CTI_APPPULSE_ADDR(base)            ((base) + (0x01C))

/* 寄存器说明：CTI trigger0至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN0_UNION */
#define SOC_CS_CTI_CTI_INEN0_ADDR(base)               ((base) + (0x020))

/* 寄存器说明：CTI trigger1至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN1_UNION */
#define SOC_CS_CTI_CTI_INEN1_ADDR(base)               ((base) + (0x024))

/* 寄存器说明：CTI trigger2至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN2_UNION */
#define SOC_CS_CTI_CTI_INEN2_ADDR(base)               ((base) + (0x028))

/* 寄存器说明：CTI trigger3至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN3_UNION */
#define SOC_CS_CTI_CTI_INEN3_ADDR(base)               ((base) + (0x02C))

/* 寄存器说明：CTI trigger4至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN4_UNION */
#define SOC_CS_CTI_CTI_INEN4_ADDR(base)               ((base) + (0x030))

/* 寄存器说明：CTI trigger5至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN5_UNION */
#define SOC_CS_CTI_CTI_INEN5_ADDR(base)               ((base) + (0x034))

/* 寄存器说明：CTI trigger6至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN6_UNION */
#define SOC_CS_CTI_CTI_INEN6_ADDR(base)               ((base) + (0x038))

/* 寄存器说明：CTI trigger7至channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_INEN7_UNION */
#define SOC_CS_CTI_CTI_INEN7_ADDR(base)               ((base) + (0x03C))

/* 寄存器说明：CTI channel至trigger0使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN0_UNION */
#define SOC_CS_CTI_CTI_OUTEN0_ADDR(base)              ((base) + (0x0A0))

/* 寄存器说明：CTI channel至trigger1使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN1_UNION */
#define SOC_CS_CTI_CTI_OUTEN1_ADDR(base)              ((base) + (0x0A4))

/* 寄存器说明：CTI channel至trigger2使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN2_UNION */
#define SOC_CS_CTI_CTI_OUTEN2_ADDR(base)              ((base) + (0x0A8))

/* 寄存器说明：CTI channel至trigger3使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN3_UNION */
#define SOC_CS_CTI_CTI_OUTEN3_ADDR(base)              ((base) + (0x0AC))

/* 寄存器说明：CTI channel至trigger4使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN4_UNION */
#define SOC_CS_CTI_CTI_OUTEN4_ADDR(base)              ((base) + (0x0B0))

/* 寄存器说明：CTI channel至trigger5使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN5_UNION */
#define SOC_CS_CTI_CTI_OUTEN5_ADDR(base)              ((base) + (0x0B4))

/* 寄存器说明：CTI channel至trigger6使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN6_UNION */
#define SOC_CS_CTI_CTI_OUTEN6_ADDR(base)              ((base) + (0x0B8))

/* 寄存器说明：CTI channel至trigger7使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_OUTEN7_UNION */
#define SOC_CS_CTI_CTI_OUTEN7_ADDR(base)              ((base) + (0x0BC))

/* 寄存器说明：CTI trigger输入状态寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_TRIGINSTATUS_UNION */
#define SOC_CS_CTI_CTI_TRIGINSTATUS_ADDR(base)        ((base) + (0x130))

/* 寄存器说明：CTI trigger输出状态寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_TRIGOUTSTATUS_UNION */
#define SOC_CS_CTI_CTI_TRIGOUTSTATUS_ADDR(base)       ((base) + (0x134))

/* 寄存器说明：CTI channel输入状态寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_CHINSTATUS_UNION */
#define SOC_CS_CTI_CTI_CHINSTATUS_ADDR(base)          ((base) + (0x138))

/* 寄存器说明：CTI channel输出状态寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_CHOUTSTATUS_UNION */
#define SOC_CS_CTI_CTI_CHOUTSTATUS_ADDR(base)         ((base) + (0x13C))

/* 寄存器说明：CTI channel使能寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_GATE_UNION */
#define SOC_CS_CTI_CTI_GATE_ADDR(base)                ((base) + (0x140))

/* 寄存器说明：CTI锁定访问寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_LAR_UNION */
#define SOC_CS_CTI_CTI_LAR_ADDR(base)                 ((base) + (0xFB0))

/* 寄存器说明：CTI锁定状态寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_LSR_UNION */
#define SOC_CS_CTI_CTI_LSR_ADDR(base)                 ((base) + (0xFB4))

/* 寄存器说明：CTI授权状态寄存器。
   位域定义UNION结构:  SOC_CS_CTI_CTI_AUTHSTATUS_UNION */
#define SOC_CS_CTI_CTI_AUTHSTATUS_ADDR(base)          ((base) + (0xFB8))





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
                     (1/1) CTI
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_CONTROL_UNION
 结构说明  : CTI_CONTROL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: CTI控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glben    : 1;  /* bit[0]   : Enables or disables the CTI.
                                                   0：disabled
                                                   1：enabled */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_CONTROL_UNION;
#endif
#define SOC_CS_CTI_CTI_CONTROL_glben_START     (0)
#define SOC_CS_CTI_CTI_CONTROL_glben_END       (0)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INTACK_UNION
 结构说明  : CTI_INTACK 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: CTI中断确认寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intack   : 8;  /* bit[0-7] : Acknowledges the corresponding ctitrigout output. There is one bit of the register for each ctitrigout 
                                                   output. When a 1 is written to a bit in this register, the corresponding ctitrigout is acknowledged, causing 
                                                   it to be cleared. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INTACK_UNION;
#endif
#define SOC_CS_CTI_CTI_INTACK_intack_START    (0)
#define SOC_CS_CTI_CTI_INTACK_intack_END      (7)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_APPSET_UNION
 结构说明  : CTI_APPSET 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger set寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  appset   : 4;  /* bit[0-3] : Setting a bit HIGH generates a channel event for the selected channel. There is one bit of the 
                                                   register for each channel. 
                                                   Reads as follows: 
                                                   0 Application trigger is inactive.
                                                   1 Application trigger is active.
                                                   Writes as follows: 
                                                   0 No effect.
                                                   1 Generate channel event. */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_APPSET_UNION;
#endif
#define SOC_CS_CTI_CTI_APPSET_appset_START    (0)
#define SOC_CS_CTI_CTI_APPSET_appset_END      (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_APPCLEAR_UNION
 结构说明  : CTI_APPCLEAR 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger clear寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  appclear : 4;  /* bit[0-3] : Sets the corresponding bits in the CTIAPPSET to 0. There is one bit of the register for each 
                                                   channel. On writes, for each bit: 
                                                   0 Has no effect.
                                                   1 Clears the corresponding channel event. */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_APPCLEAR_UNION;
#endif
#define SOC_CS_CTI_CTI_APPCLEAR_appclear_START  (0)
#define SOC_CS_CTI_CTI_APPCLEAR_appclear_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_APPPULSE_UNION
 结构说明  : CTI_APPPULSE 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger pulse寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  appulse  : 4;  /* bit[0-3] : Setting a bit HIGH generates a channel event pulse for the selected channel. There is one bit of the register for each channel. On writes, for each bit:
                                                   0 Has no effect.
                                                   1 Generate an event pulse on the corresponding channel. */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_APPPULSE_UNION;
#endif
#define SOC_CS_CTI_CTI_APPPULSE_appulse_START   (0)
#define SOC_CS_CTI_CTI_APPPULSE_appulse_END     (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN0_UNION
 结构说明  : CTI_INEN0 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger0至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin0事件到相应channel的映射
                                                   0：disable CTITRIGIN[0]到相应channel的映射
                                                   1：enable CTITRIGIN[0]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN0_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN0_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN0_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN1_UNION
 结构说明  : CTI_INEN1 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger1至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin1事件到相应channel的映射
                                                   0：disable CTITRIGIN[1]到相应channel的映射
                                                   1：enable CTITRIGIN[1]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN1_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN1_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN1_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN2_UNION
 结构说明  : CTI_INEN2 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger2至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin2事件到相应channel的映射
                                                   0：disable CTITRIGIN[2]到相应channel的映射
                                                   1：enable CTITRIGIN[2]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN2_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN2_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN2_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN3_UNION
 结构说明  : CTI_INEN3 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger3至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin3事件到相应channel的映射
                                                   0：disable CTITRIGIN[3]到相应channel的映射
                                                   1：enable CTITRIGIN[3]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN3_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN3_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN3_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN4_UNION
 结构说明  : CTI_INEN4 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger4至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin4事件到相应channel的映射
                                                   0：disable CTITRIGIN[4]到相应channel的映射
                                                   1：enable CTITRIGIN[4]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN4_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN4_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN4_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN5_UNION
 结构说明  : CTI_INEN5 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger5至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin5事件到相应channel的映射
                                                   0：disable CTITRIGIN[5]到相应channel的映射
                                                   1：enable CTITRIGIN[5]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN5_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN5_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN5_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN6_UNION
 结构说明  : CTI_INEN6 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger6至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin6事件到相应channel的映射
                                                   0：disable CTITRIGIN[6]到相应channel的映射
                                                   1：enable CTITRIGIN[6]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN6_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN6_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN6_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_INEN7_UNION
 结构说明  : CTI_INEN7 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger7至channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能triggerin7事件到相应channel的映射
                                                   0：disable CTITRIGIN[7]到相应channel的映射
                                                   1：enable CTITRIGIN[7]到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_INEN7_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN7_triginen_START  (0)
#define SOC_CS_CTI_CTI_INEN7_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN0_UNION
 结构说明  : CTI_OUTEN0 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger0使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout0事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[0]的映射
                                                    1：enable 相应channel到CTITRIGOUT[0]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN0_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN0_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN0_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN1_UNION
 结构说明  : CTI_OUTEN1 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger1使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout1事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[1]的映射
                                                    1：enable 相应channel到CTITRIGOUT[1]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN1_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN1_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN1_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN2_UNION
 结构说明  : CTI_OUTEN2 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger2使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout2事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[2]的映射
                                                    1：enable 相应channel到CTITRIGOUT[2]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN2_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN2_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN2_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN3_UNION
 结构说明  : CTI_OUTEN3 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger3使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout3事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[3]的映射
                                                    1：enable 相应channel到CTITRIGOUT[3]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN3_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN3_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN3_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN4_UNION
 结构说明  : CTI_OUTEN4 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger4使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout4事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[4]的映射
                                                    1：enable 相应channel到CTITRIGOUT[4]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN4_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN4_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN4_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN5_UNION
 结构说明  : CTI_OUTEN5 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger5使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout5事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[5]的映射
                                                    1：enable 相应channel到CTITRIGOUT[5]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN5_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN5_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN5_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN6_UNION
 结构说明  : CTI_OUTEN6 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger6使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout6事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[6]的映射
                                                    1：enable 相应channel到CTITRIGOUT[6]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN6_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN6_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN6_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_OUTEN7_UNION
 结构说明  : CTI_OUTEN7 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: CTI channel至trigger7使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigouten : 4;  /* bit[0-3] : 使能相应channel到triggerout7事件的映射
                                                    0：disable 相应channel到CTITRIGOUT[7]的映射
                                                    1：enable 相应channel到CTITRIGOUT[7]的映射 */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_OUTEN7_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN7_trigouten_START  (0)
#define SOC_CS_CTI_CTI_OUTEN7_trigouten_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_TRIGINSTATUS_UNION
 结构说明  : CTI_TRIGINSTATUS 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger输入状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginstatus : 8;  /* bit[0-7] : Shows the status of the ctitrigin inputs. There is one bit of the field for each trigger input.
                                                       1 ctitrigin is active.
                                                       0 ctitrigin is inactive. */
        unsigned int  reserved     : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_TRIGINSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_TRIGINSTATUS_triginstatus_START  (0)
#define SOC_CS_CTI_CTI_TRIGINSTATUS_triginstatus_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_TRIGOUTSTATUS_UNION
 结构说明  : CTI_TRIGOUTSTATUS 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: CTI trigger输出状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigoutstatus : 8;  /* bit[0-7] : Shows the status of the ctitrigout outputs. There is one bit of the field for each trigger output.
                                                        1 ctitrigout is active.
                                                        0 ctitrigout is inactive */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_TRIGOUTSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_TRIGOUTSTATUS_trigoutstatus_START  (0)
#define SOC_CS_CTI_CTI_TRIGOUTSTATUS_trigoutstatus_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_CHINSTATUS_UNION
 结构说明  : CTI_CHINSTATUS 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: CTI channel输入状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chinstatus : 4;  /* bit[0-3] : Shows the status of the ctichin inputs. There is one bit of the field for each channel input.
                                                     0 ctichin is inactive.
                                                     1 ctichin is active. */
        unsigned int  reserved   : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_CHINSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_CHINSTATUS_chinstatus_START  (0)
#define SOC_CS_CTI_CTI_CHINSTATUS_chinstatus_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_CHOUTSTATUS_UNION
 结构说明  : CTI_CHOUTSTATUS 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: CTI channel输出状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  choutstatus : 4;  /* bit[0-3] : Shows the status of the ctichout outputs. There is one bit of the field for each channel output.
                                                      0 ctichout is inactive.
                                                      1 ctichout is active. */
        unsigned int  reserved    : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_CHOUTSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_CHOUTSTATUS_choutstatus_START  (0)
#define SOC_CS_CTI_CTI_CHOUTSTATUS_choutstatus_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_GATE_UNION
 结构说明  : CTI_GATE 寄存器结构定义。地址偏移量:0x140，初值:0x0000000F，宽度:32
 寄存器说明: CTI channel使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctigateen0 : 1;  /* bit[0]   : 使能通道0
                                                     0：disable CTICHOUT0
                                                     1：enable CTICHOUT0 */
        unsigned int  ctigateen1 : 1;  /* bit[1]   : 使能通道1
                                                     0：disable CTICHOUT1
                                                     1：enable CTICHOUT1 */
        unsigned int  ctigateen2 : 1;  /* bit[2]   : 使能通道2
                                                     0：disable CTICHOUT2
                                                     1：enable CTICHOUT2 */
        unsigned int  ctigateen3 : 1;  /* bit[3]   : 使能通道3
                                                     0：disable CTICHOUT3
                                                     1：enable CTICHOUT3 */
        unsigned int  reserved   : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_GATE_UNION;
#endif
#define SOC_CS_CTI_CTI_GATE_ctigateen0_START  (0)
#define SOC_CS_CTI_CTI_GATE_ctigateen0_END    (0)
#define SOC_CS_CTI_CTI_GATE_ctigateen1_START  (1)
#define SOC_CS_CTI_CTI_GATE_ctigateen1_END    (1)
#define SOC_CS_CTI_CTI_GATE_ctigateen2_START  (2)
#define SOC_CS_CTI_CTI_GATE_ctigateen2_END    (2)
#define SOC_CS_CTI_CTI_GATE_ctigateen3_START  (3)
#define SOC_CS_CTI_CTI_GATE_ctigateen3_END    (3)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_LAR_UNION
 结构说明  : CTI_LAR 寄存器结构定义。地址偏移量:0xFB0，初值:0x00000000，宽度:32
 寄存器说明: CTI锁定访问寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: 写入0xC5ACCE55进行解锁，然后才可以正常配置其他寄存器；写入其他任何值后再次锁定。 */
    } reg;
} SOC_CS_CTI_CTI_LAR_UNION;
#endif
#define SOC_CS_CTI_CTI_LAR_key_START  (0)
#define SOC_CS_CTI_CTI_LAR_key_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_LSR_UNION
 结构说明  : CTI_LSR 寄存器结构定义。地址偏移量:0xFB4，初值:0x00000003，宽度:32
 寄存器说明: CTI锁定状态寄存器。
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
} SOC_CS_CTI_CTI_LSR_UNION;
#endif
#define SOC_CS_CTI_CTI_LSR_sli_START       (0)
#define SOC_CS_CTI_CTI_LSR_sli_END         (0)
#define SOC_CS_CTI_CTI_LSR_slk_START       (1)
#define SOC_CS_CTI_CTI_LSR_slk_END         (1)
#define SOC_CS_CTI_CTI_LSR_ntt_START       (2)
#define SOC_CS_CTI_CTI_LSR_ntt_END         (2)


/*****************************************************************************
 结构名    : SOC_CS_CTI_CTI_AUTHSTATUS_UNION
 结构说明  : CTI_AUTHSTATUS 寄存器结构定义。地址偏移量:0xFB8，初值:0x0000000A，宽度:32
 寄存器说明: CTI授权状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nsid     : 2;  /* bit[0-1] : Indicates the security level for non-secure invasive debug:
                                                   0b10 Disabled.
                                                   0b11 Enabled. */
        unsigned int  nsnid    : 2;  /* bit[2-3] : Indicates the security level for non-secure non-invasive debug:
                                                   0b10 Disabled.
                                                   0b11 Enabled. */
        unsigned int  sid      : 2;  /* bit[4-5] : Always 0b00 Secure invasive debug is not implemented */
        unsigned int  snid     : 2;  /* bit[6-7] : Always 0b00. The security level for secure non-invasive debug is not implemented */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_CTI_CTI_AUTHSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsid_START      (0)
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsid_END        (1)
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsnid_START     (2)
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsnid_END       (3)
#define SOC_CS_CTI_CTI_AUTHSTATUS_sid_START       (4)
#define SOC_CS_CTI_CTI_AUTHSTATUS_sid_END         (5)
#define SOC_CS_CTI_CTI_AUTHSTATUS_snid_START      (6)
#define SOC_CS_CTI_CTI_AUTHSTATUS_snid_END        (7)






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

#endif /* end of soc_cs_cti_interface.h */
