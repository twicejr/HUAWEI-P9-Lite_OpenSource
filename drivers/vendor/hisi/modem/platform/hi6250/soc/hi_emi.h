/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_emi.h */
/* Version       : 2.0 */
/* Created       : 2013-05-24*/
/* Last Modified : */
/* Description   :  The C union definition file for the module emi*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_EMI_H__
#define __HI_EMI_H__

/*
 * Project: hi
 * Module : emi
 */

#ifndef HI_SET_GET

#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif



/********************************************************************************/
/*    emi 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_EMI_SMBIDCYR0_OFFSET                           (0x0) /* Bank0回转时间寄存器。 */
#define    HI_EMI_SMBWST1R0_OFFSET                           (0x4) /* Bank0读访问等待时间寄存器。 */
#define    HI_EMI_SMBWST2R0_OFFSET                           (0x8) /* Bank0写访问等待时间寄存器。 */
#define    HI_EMI_SMBWSTOENR0_OFFSET                         (0xC) /* Bank0读使能延迟时间寄存器。 */
#define    HI_EMI_SMBWSTWENR0_OFFSET                         (0x10) /* Bank0写使能延迟时间寄存器。 */
#define    HI_EMI_SMBCR0_OFFSET                              (0x14) /* Bank0控制寄存器。 */
#define    HI_EMI_SMBSR0_OFFSET                              (0x18) /* Bank0状态寄存器。 */

/********************************************************************************/
/*    emi 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    idcy                       : 4; /* [3..0] 这个字段控制了总线读访问和写访问之间插入的等待周期数目，插入的等待周期时间为(idcy+1)*Thclk。 */
        unsigned int    updlyr_l                   : 7; /* [10..4] 控制读状态PREB信号0变成1相对CS的延迟，延迟时间为(updlyr)*Thclk。此7bit为updlyr的低位比特。 */
        unsigned int    dwndlyr_l                  : 7; /* [17..11] 控制读状态PREB信号1变成0相对CS的延迟，延迟时间为(dwndlyr+1)*Thclk。此7bit为dwndlyr的低位比特。 */
        unsigned int    updlyw_l                   : 7; /* [24..18] 控制写状态PREB信号0变成1相对CS的延迟，延迟时间为(updlyw)*Thclk。此7bit为updlyw的低位比特。 */
        unsigned int    dwndlyw_l                  : 7; /* [31..25] 控制写状态PREB信号1变成0相对CS的延迟，延迟时间为(dwndlyw+1)*Thclk。此7bit为dwndlyw的低位比特。 */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBIDCYR0_T;    /* Bank0回转时间寄存器。 */

typedef union
{
    struct
    {
        unsigned int    wst1                       : 10; /* [9..0] Wait State 1。字段控制了总线读访问等待状态的数目。Wait state time=wst1*Thclk。 */
        unsigned int    updlyr_h                   : 3; /* [12..10] 控制读状态PREB信号0变成1相对CS的延迟，延迟时间为(updlyr)*Thclk。此3bit为updlyr的高位比特。 */
        unsigned int    dwndlyr_h                  : 3; /* [15..13] 控制读状态PREB信号1变成0相对CS的延迟，延迟时间为(dwndlyr+1)*Thclk。此3bit为dwndlyr的高位比特。 */
        unsigned int    updlyw_h                   : 3; /* [18..16] 控制写状态PREB信号0变成1相对CS的延迟，延迟时间为(updlyw)*Thclk。此3bit为updlyw的高位比特。 */
        unsigned int    dwndlyw_h                  : 3; /* [21..19] 控制写状态PREB信号1变成0相对CS的延迟，延迟时间为(dwndlyw+1)*Thclk。此3bit为dwndlyw的高位比特。 */
        unsigned int    reserved                   : 10; /* [31..22] 保留。 */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWST1R0_T;    /* Bank0读访问等待时间寄存器。 */

typedef union
{
    struct
    {
        unsigned int    wst2                       : 10; /* [9..0] Wait State 2。字段控制了总线写访问等待状态的数目。Wait state time=wst2*Thclk。 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留。 */
        unsigned int    wst3                       : 8; /* [23..16] Wait State 3。字段控制了两次读访问间或者两次写访问间插入的等待周期数。Wait state time=wst3*Thclk。 */
        unsigned int    reserved_0                 : 8; /* [31..24] 保留。 */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWST2R0_T;    /* Bank0写访问等待时间寄存器。 */

typedef union
{
    struct
    {
        unsigned int    wstoen                     : 4; /* [3..0] 读使能有效相对于片选有效的延迟周期控制。Output Enable Delay time=wstoen*Thclk。 */
        unsigned int    oendisable                 : 1; /* [4..4] 为1的时候，读使能信号始终为高，为0的时候读使能信号有效，按照WSTOEN配置变化。 */
        unsigned int    oendly                     : 2; /* [6..5] 读使能无效信号到片选无效信号的延迟，oendly*Thclk。 */
        unsigned int    reserved                   : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWSTOENR0_T;    /* Bank0读使能延迟时间寄存器。 */

typedef union
{
    struct
    {
        unsigned int    wstwen                     : 4; /* [3..0] 写使能有效相对于片选有效的延迟周期控制。Write Enable Delay time=wstwen*Thclk。 */
        unsigned int    wendly                     : 2; /* [5..4] 写使能无效相对于片选无效的延迟周期控制。Write Enable Delay time=wendly*Thclk。 */
        unsigned int    wenclocksel                : 1; /* [6..6] 写控制信号输出跳变时钟边沿选择。0：下降沿；1：上升沿。<B>说明：Hi6755中只能配置为上升延才能正常工作。</B> */
        unsigned int    ebictrl                    : 1; /* [7..7] 为1时候，模拟EBI接口，让GRANT信号在REQ信号有（无）效一个时钟周期后有（无）效。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBWSTWENR0_T;    /* Bank0写使能延迟时间寄存器。 */

typedef union
{
    struct
    {
        unsigned int    rble                       : 1; /* [0..0] Read bye lane enable。0：nSMBL[1:0]在读操作全部过程中全部为高。这种情况针对于由8bit器件构成一个bank，bye lane enable信号被连接到Memory器件的写使能，所以在读操作的时候必须为高；1：nSMBL[1:0]在读操作全部过程中全部为低。这种情况针对于由16bit器件构成一个bank，分开的写使能（nSMWEN）被使用，bye lane enable信号在读的过程中必须被hold。所以在读操作的时候必须为高。如果系统在上电后，从Bank1 boot（remap为1），RBLE的设置由pin SMRBLECS1决定。 */
        unsigned int    cspol                      : 1; /* [1..1] 片选信号极性选择信号。0：片选信号低有效；1：片选信号高有效。如果器件的输出使能与片选信号相连，一定要确保该位的正确设置。如果不正确的极性被设置，器件可能连续驱动数据输出。 */
        unsigned int    wp                         : 1; /* [2..2] 器件写保护使能。0：没有写保护；1：器件被写保护。 */
        unsigned int    mw                         : 2; /* [4..3] 外接Memory宽度。00：8bit；01：16bit；10：保留；11：保留。 */
        unsigned int    addr_cnt                   : 1; /* [5..5] 当设置为1时候，如果是16bit的bank，bit[0]代表半字地址（16bit）。当设置为0的时候，如果是16bit的bank，bit[1]代表半字地址（16bit）。 */
        unsigned int    reserved                   : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBCR0_T;    /* Bank0控制寄存器。 */

typedef union
{
    struct
    {
        unsigned int    hsizeerr                   : 1; /* [0..0] Bus transfer size错误状态标志。从该位读：0：No error；1：Bus transfer size错误。向该位写：0：无效；1：清写保护状态标志。 */
        unsigned int    writeproerr                : 1; /* [1..1] 写保护错误状态标志。从该位读：0：No error；1：写保护错误。向该位写：0：无效；1：清写保护状态标志。 */
        unsigned int    reserved                   : 30; /* [31..2] 保留。 */
    } bits;
    unsigned int    u32;
}HI_EMI_SMBSR0_T;    /* Bank0状态寄存器。 */


/********************************************************************************/
/*    emi 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_emi_smbidcyr0_idcy,idcy,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_updlyr_l,updlyr_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_dwndlyr_l,dwndlyr_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_updlyw_l,updlyw_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_dwndlyw_l,dwndlyw_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_wst1,wst1,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_updlyr_h,updlyr_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_dwndlyr_h,dwndlyr_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_updlyw_h,updlyw_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_dwndlyw_h,dwndlyw_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_reserved,reserved,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_wst2,wst2,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_reserved_1,reserved_1,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_wst3,wst3,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_reserved_0,reserved_0,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_wstoen,wstoen,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_oendisable,oendisable,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_oendly,oendly,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_reserved,reserved,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wstwen,wstwen,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wendly,wendly,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wenclocksel,wenclocksel,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_ebictrl,ebictrl,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_reserved,reserved,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_rble,rble,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_cspol,cspol,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_wp,wp,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_mw,mw,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_addr_cnt,addr_cnt,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_reserved,reserved,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_hsizeerr,hsizeerr,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_writeproerr,writeproerr,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_reserved,reserved,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)

#endif // __HI_EMI_H__

