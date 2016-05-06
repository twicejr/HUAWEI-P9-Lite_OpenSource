/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_drc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:34
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_DRC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_DRC_INTERFACE_H__
#define __SOC_ISP_DRC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) DRC
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_DRC_CONFIG_UNION */
#define SOC_ISP_DRC_DRC_CONFIG_ADDR(base)             ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_BLOCKNUM_UNION */
#define SOC_ISP_DRC_BLOCKNUM_ADDR(base)               ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_FIRSTBLOCK_UNION */
#define SOC_ISP_DRC_FIRSTBLOCK_ADDR(base)             ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_PLAINBLOCK_UNION */
#define SOC_ISP_DRC_PLAINBLOCK_ADDR(base)             ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_LASTBLOCK_UNION */
#define SOC_ISP_DRC_LASTBLOCK_ADDR(base)              ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_XSTRIPESTART_END_UNION */
#define SOC_ISP_DRC_XSTRIPESTART_END_ADDR(base)       ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_STRIPE_INFO_UNION */
#define SOC_ISP_DRC_STRIPE_INFO_ADDR(base)            ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_FRAME_INFO_UNION */
#define SOC_ISP_DRC_FRAME_INFO_ADDR(base)             ((base) + (0x001C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_BUFFWINH_UNION */
#define SOC_ISP_DRC_BUFFWINH_ADDR(base, Range3)       ((base) + (0x0020+0x4*(Range3)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_BUFFWINV_UNION */
#define SOC_ISP_DRC_BUFFWINV_ADDR(base, Range3)       ((base) + (0x002C+0x4*(Range3)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DRC_BUFFWINSIZE_UNION */
#define SOC_ISP_DRC_BUFFWINSIZE_ADDR(base, Range6)    ((base) + (0x0038+0x4*(Range6)))

/* 寄存器说明：9 x 8 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_ALPHA_EVEN_0_UNION */
#define SOC_ISP_DRC_ALPHA_EVEN_0_ADDR(base, Range9)   ((base) + (0x0100+0x4*(Range9)))

/* 寄存器说明：9 x 8 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_ALPHA_EVEN_1_UNION */
#define SOC_ISP_DRC_ALPHA_EVEN_1_ADDR(base, Range9)   ((base) + (0x0140+0x4*(Range9)))

/* 寄存器说明：8 x 8 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_ALPHA_ODD_0_UNION */
#define SOC_ISP_DRC_ALPHA_ODD_0_ADDR(base, Range8)    ((base) + (0x0180+0x4*(Range8)))

/* 寄存器说明：8 x 8 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_ALPHA_ODD_1_UNION */
#define SOC_ISP_DRC_ALPHA_ODD_1_ADDR(base, Range8)    ((base) + (0x01C0+0x4*(Range8)))

/* 寄存器说明：9 x 8 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RA_TAB_EVEN_0_UNION */
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ADDR(base, Range9)  ((base) + (0x0200+0x4*(Range9)))

/* 寄存器说明：9 x 8 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RA_TAB_EVEN_1_UNION */
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ADDR(base, Range9)  ((base) + (0x0240+0x4*(Range9)))

/* 寄存器说明：8 x 16 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RA_TAB_ODD_0_UNION */
#define SOC_ISP_DRC_RA_TAB_ODD_0_ADDR(base, Range8)   ((base) + (0x0280+0x4*(Range8)))

/* 寄存器说明：8 x 16 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RA_TAB_ODD_1_UNION */
#define SOC_ISP_DRC_RA_TAB_ODD_1_ADDR(base, Range8)   ((base) + (0x02C0+0x4*(Range8)))

/* 寄存器说明：SRAM 33 x 20 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RAT_TABHL_EVEN_0_UNION */
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_ADDR(base, Range33)  ((base) + (0x0300+0x4*(Range33)))

/* 寄存器说明：SRAM 33 x 20 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RAT_TABHL_EVEN_1_UNION */
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_ADDR(base, Range33)  ((base) + (0x0400+0x4*(Range33)))

/* 寄存器说明：SRAM 32 x 20 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RAT_TABHL_ODD_0_UNION */
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_ADDR(base, Range32)  ((base) + (0x0500+0x4*(Range32)))

/* 寄存器说明：SRAM 32 x 20 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_RAT_TABHL_ODD_1_UNION */
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_ADDR(base, Range32)  ((base) + (0x0600+0x4*(Range32)))

/* 寄存器说明：SRAM 256 x 10 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_AVERMATRIX_0_UNION */
#define SOC_ISP_DRC_AVERMATRIX_0_ADDR(base, Range128)  ((base) + (0x0700+0x4*(Range128)))

/* 寄存器说明：SRAM 256 x 10 - shadowed
   位域定义UNION结构:  SOC_ISP_DRC_AVERMATRIX_1_UNION */
#define SOC_ISP_DRC_AVERMATRIX_1_ADDR(base, Range128)  ((base) + (0x0900+0x4*(Range128)))





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
                     (1/1) DRC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_DRC_DRC_CONFIG_UNION
 结构说明  : DRC_CONFIG 寄存器结构定义。地址偏移量:0x0000，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass                  : 1;  /* bit[0]   : bypass:
                                                                  0: the module is active
                                                                  1: the module is bypassed */
        unsigned int  stat_enable             : 1;  /* bit[1]   : stat_enable:
                                                                  0: DRC Statistic feature is disable
                                                                  1: DRC Statistic feature is enable */
        unsigned int  alpha_table_active      : 1;  /* bit[2]   : alpha_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  ra_tab_table_active     : 1;  /* bit[3]   : ra_tab_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  rat_tabhl_table_active  : 1;  /* bit[4]   : rat_tabhl_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  avermatrix_table_active : 1;  /* bit[5]   : avermatrix_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  reserved                : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_DRC_DRC_CONFIG_UNION;
#endif
#define SOC_ISP_DRC_DRC_CONFIG_bypass_START                   (0)
#define SOC_ISP_DRC_DRC_CONFIG_bypass_END                     (0)
#define SOC_ISP_DRC_DRC_CONFIG_stat_enable_START              (1)
#define SOC_ISP_DRC_DRC_CONFIG_stat_enable_END                (1)
#define SOC_ISP_DRC_DRC_CONFIG_alpha_table_active_START       (2)
#define SOC_ISP_DRC_DRC_CONFIG_alpha_table_active_END         (2)
#define SOC_ISP_DRC_DRC_CONFIG_ra_tab_table_active_START      (3)
#define SOC_ISP_DRC_DRC_CONFIG_ra_tab_table_active_END        (3)
#define SOC_ISP_DRC_DRC_CONFIG_rat_tabhl_table_active_START   (4)
#define SOC_ISP_DRC_DRC_CONFIG_rat_tabhl_table_active_END     (4)
#define SOC_ISP_DRC_DRC_CONFIG_avermatrix_table_active_START  (5)
#define SOC_ISP_DRC_DRC_CONFIG_avermatrix_table_active_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_BLOCKNUM_UNION
 结构说明  : BLOCKNUM 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blocknumv        : 5;  /* bit[0-4]  : VerticalBlock number in frame */
        unsigned int  reserved_0       : 3;  /* bit[5-7]  :  */
        unsigned int  blocknumh        : 5;  /* bit[8-12] : Horizontal block number in frame */
        unsigned int  reserved_1       : 3;  /* bit[13-15]:  */
        unsigned int  blocknumh_stripe : 5;  /* bit[16-20]: Horizontal block number in stripe */
        unsigned int  reserved_2       : 11; /* bit[21-31]:  */
    } reg;
} SOC_ISP_DRC_BLOCKNUM_UNION;
#endif
#define SOC_ISP_DRC_BLOCKNUM_blocknumv_START         (0)
#define SOC_ISP_DRC_BLOCKNUM_blocknumv_END           (4)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_START         (8)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_END           (12)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_stripe_START  (16)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_stripe_END    (20)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_FIRSTBLOCK_UNION
 结构说明  : FIRSTBLOCK 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  firstblockoffh : 10; /* bit[0-9]  : The horizontal offset of the first pixel in current block in stripe */
        unsigned int  reserved_0     : 6;  /* bit[10-15]:  */
        unsigned int  firstblocknumh : 5;  /* bit[16-20]: Left block number of the first pixel in stripe */
        unsigned int  reserved_1     : 11; /* bit[21-31]:  */
    } reg;
} SOC_ISP_DRC_FIRSTBLOCK_UNION;
#endif
#define SOC_ISP_DRC_FIRSTBLOCK_firstblockoffh_START  (0)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblockoffh_END    (9)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblocknumh_START  (16)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblocknumh_END    (20)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_PLAINBLOCK_UNION
 结构说明  : PLAINBLOCK 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blockwinv : 10; /* bit[0-9]  : Plain block height in frame; width x height cannot exceed 0x20000 */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  blockwinh : 10; /* bit[16-25]: Plain block width in frame; width x height cannot exceed 0x20000 */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_PLAINBLOCK_UNION;
#endif
#define SOC_ISP_DRC_PLAINBLOCK_blockwinv_START  (0)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinv_END    (9)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinh_START  (16)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinh_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_LASTBLOCK_UNION
 结构说明  : LASTBLOCK 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lastwinv        : 10; /* bit[0-9]  : Last block height in frame;width x height cannot exceed 0x20000 */
        unsigned int  lastwinh        : 10; /* bit[10-19]: Last block width in frame; width x height cannot exceed 0x20000 */
        unsigned int  lastwinh_stripe : 10; /* bit[20-29]: Last block width in stripe  */
        unsigned int  reserved        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_DRC_LASTBLOCK_UNION;
#endif
#define SOC_ISP_DRC_LASTBLOCK_lastwinv_START         (0)
#define SOC_ISP_DRC_LASTBLOCK_lastwinv_END           (9)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_START         (10)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_END           (19)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_stripe_START  (20)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_stripe_END    (29)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_XSTRIPESTART_END_UNION
 结构说明  : XSTRIPESTART_END 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  endpoint   : 13; /* bit[0-12] : endpoint of the stripe in the image coordinates */
        unsigned int  reserved_0 : 3;  /* bit[13-15]:  */
        unsigned int  startpoint : 13; /* bit[16-28]: Startpoint of the stripe in the image coordinates */
        unsigned int  reserved_1 : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DRC_XSTRIPESTART_END_UNION;
#endif
#define SOC_ISP_DRC_XSTRIPESTART_END_endpoint_START    (0)
#define SOC_ISP_DRC_XSTRIPESTART_END_endpoint_END      (12)
#define SOC_ISP_DRC_XSTRIPESTART_END_startpoint_START  (16)
#define SOC_ISP_DRC_XSTRIPESTART_END_startpoint_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_STRIPE_INFO_UNION
 结构说明  : STRIPE_INFO 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  khright    : 7;  /* bit[0-6]  : width of the right overlap */
        unsigned int  reserved_0 : 1;  /* bit[7]    :  */
        unsigned int  khleft     : 7;  /* bit[8-14] : width of the left overlap */
        unsigned int  reserved_1 : 1;  /* bit[15]   :  */
        unsigned int  stripewinh : 13; /* bit[16-28]: width minus 1 of a stripe, the actual image width for ISP pipeline. */
        unsigned int  reserved_2 : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DRC_STRIPE_INFO_UNION;
#endif
#define SOC_ISP_DRC_STRIPE_INFO_khright_START     (0)
#define SOC_ISP_DRC_STRIPE_INFO_khright_END       (6)
#define SOC_ISP_DRC_STRIPE_INFO_khleft_START      (8)
#define SOC_ISP_DRC_STRIPE_INFO_khleft_END        (14)
#define SOC_ISP_DRC_STRIPE_INFO_stripewinh_START  (16)
#define SOC_ISP_DRC_STRIPE_INFO_stripewinh_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_FRAME_INFO_UNION
 结构说明  : FRAME_INFO 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_height : 13; /* bit[0-12] : height of frame minus 1; cannot exceed 4992 pixels */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  frame_width  : 13; /* bit[16-28]: width of frame minus 1; cannot exceed 6656 pixels */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DRC_FRAME_INFO_UNION;
#endif
#define SOC_ISP_DRC_FRAME_INFO_frame_height_START  (0)
#define SOC_ISP_DRC_FRAME_INFO_frame_height_END    (12)
#define SOC_ISP_DRC_FRAME_INFO_frame_width_START   (16)
#define SOC_ISP_DRC_FRAME_INFO_frame_width_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_BUFFWINH_UNION
 结构说明  : BUFFWINH 寄存器结构定义。地址偏移量:0x0020+0x4*(Range3)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffwinh : 16; /* bit[0-15] : 3 different part width for biliresizer */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DRC_BUFFWINH_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINH_buffwinh_START  (0)
#define SOC_ISP_DRC_BUFFWINH_buffwinh_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_BUFFWINV_UNION
 结构说明  : BUFFWINV 寄存器结构定义。地址偏移量:0x002C+0x4*(Range3)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffwinv : 16; /* bit[0-15] : 3 different part height for biliresizer */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DRC_BUFFWINV_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINV_buffwinv_START  (0)
#define SOC_ISP_DRC_BUFFWINV_buffwinv_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_BUFFWINSIZE_UNION
 结构说明  : BUFFWINSIZE 寄存器结构定义。地址偏移量:0x0038+0x4*(Range6)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffwinsize : 26; /* bit[0-25] : 6 different block size in stripe */
        unsigned int  reserved    : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_BUFFWINSIZE_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINSIZE_buffwinsize_START  (0)
#define SOC_ISP_DRC_BUFFWINSIZE_buffwinsize_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_ALPHA_EVEN_0_UNION
 结构说明  : ALPHA_EVEN_0 寄存器结构定义。地址偏移量:0x0100+0x4*(Range9)，初值:0x00000000，宽度:32
 寄存器说明: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_even_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_EVEN_0_alpha_even_0_START  (0)
#define SOC_ISP_DRC_ALPHA_EVEN_0_alpha_even_0_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_ALPHA_EVEN_1_UNION
 结构说明  : ALPHA_EVEN_1 寄存器结构定义。地址偏移量:0x0140+0x4*(Range9)，初值:0x00000000，宽度:32
 寄存器说明: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_even_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_EVEN_1_alpha_even_1_START  (0)
#define SOC_ISP_DRC_ALPHA_EVEN_1_alpha_even_1_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_ALPHA_ODD_0_UNION
 结构说明  : ALPHA_ODD_0 寄存器结构定义。地址偏移量:0x0180+0x4*(Range8)，初值:0x00000000，宽度:32
 寄存器说明: 8 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_odd_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_ODD_0_alpha_odd_0_START  (0)
#define SOC_ISP_DRC_ALPHA_ODD_0_alpha_odd_0_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_ALPHA_ODD_1_UNION
 结构说明  : ALPHA_ODD_1 寄存器结构定义。地址偏移量:0x01C0+0x4*(Range8)，初值:0x00000000，宽度:32
 寄存器说明: 8 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_odd_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_ODD_1_alpha_odd_1_START  (0)
#define SOC_ISP_DRC_ALPHA_ODD_1_alpha_odd_1_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RA_TAB_EVEN_0_UNION
 结构说明  : RA_TAB_EVEN_0 寄存器结构定义。地址偏移量:0x0200+0x4*(Range9)，初值:0x00000000，宽度:32
 寄存器说明: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_even_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ra_tab_even_0_START  (0)
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ra_tab_even_0_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RA_TAB_EVEN_1_UNION
 结构说明  : RA_TAB_EVEN_1 寄存器结构定义。地址偏移量:0x0240+0x4*(Range9)，初值:0x00000000，宽度:32
 寄存器说明: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_even_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ra_tab_even_1_START  (0)
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ra_tab_even_1_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RA_TAB_ODD_0_UNION
 结构说明  : RA_TAB_ODD_0 寄存器结构定义。地址偏移量:0x0280+0x4*(Range8)，初值:0x00000000，宽度:32
 寄存器说明: 8 x 16 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_odd_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_ODD_0_ra_tab_odd_0_START  (0)
#define SOC_ISP_DRC_RA_TAB_ODD_0_ra_tab_odd_0_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RA_TAB_ODD_1_UNION
 结构说明  : RA_TAB_ODD_1 寄存器结构定义。地址偏移量:0x02C0+0x4*(Range8)，初值:0x00000000，宽度:32
 寄存器说明: 8 x 16 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_odd_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_ODD_1_ra_tab_odd_1_START  (0)
#define SOC_ISP_DRC_RA_TAB_ODD_1_ra_tab_odd_1_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RAT_TABHL_EVEN_0_UNION
 结构说明  : RAT_TABHL_EVEN_0 寄存器结构定义。地址偏移量:0x0300+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: SRAM 33 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_even_0 : 20; /* bit[0-19] :  */
        unsigned int  reserved         : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_rat_tabhl_even_0_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_rat_tabhl_even_0_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RAT_TABHL_EVEN_1_UNION
 结构说明  : RAT_TABHL_EVEN_1 寄存器结构定义。地址偏移量:0x0400+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: SRAM 33 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_even_1 : 20; /* bit[0-19] :  */
        unsigned int  reserved         : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_rat_tabhl_even_1_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_rat_tabhl_even_1_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RAT_TABHL_ODD_0_UNION
 结构说明  : RAT_TABHL_ODD_0 寄存器结构定义。地址偏移量:0x0500+0x4*(Range32)，初值:0x00000000，宽度:32
 寄存器说明: SRAM 32 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_odd_0 : 20; /* bit[0-19] :  */
        unsigned int  reserved        : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_rat_tabhl_odd_0_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_rat_tabhl_odd_0_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_RAT_TABHL_ODD_1_UNION
 结构说明  : RAT_TABHL_ODD_1 寄存器结构定义。地址偏移量:0x0600+0x4*(Range32)，初值:0x00000000，宽度:32
 寄存器说明: SRAM 32 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_odd_1 : 20; /* bit[0-19] :  */
        unsigned int  reserved        : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_rat_tabhl_odd_1_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_rat_tabhl_odd_1_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_AVERMATRIX_0_UNION
 结构说明  : AVERMATRIX_0 寄存器结构定义。地址偏移量:0x0700+0x4*(Range128)，初值:0x00000000，宽度:32
 寄存器说明: SRAM 256 x 10 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  avermatrix_odd_0  : 10; /* bit[0-9]  : odd part */
        unsigned int  reserved_0        : 6;  /* bit[10-15]:  */
        unsigned int  avermatrix_even_0 : 10; /* bit[16-25]: even part */
        unsigned int  reserved_1        : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_AVERMATRIX_0_UNION;
#endif
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_odd_0_START   (0)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_odd_0_END     (9)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_even_0_START  (16)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_even_0_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_DRC_AVERMATRIX_1_UNION
 结构说明  : AVERMATRIX_1 寄存器结构定义。地址偏移量:0x0900+0x4*(Range128)，初值:0x00000000，宽度:32
 寄存器说明: SRAM 256 x 10 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  avermatrix_odd_1  : 10; /* bit[0-9]  : odd part */
        unsigned int  reserved_0        : 6;  /* bit[10-15]:  */
        unsigned int  avermatrix_even_1 : 10; /* bit[16-25]: even part */
        unsigned int  reserved_1        : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_AVERMATRIX_1_UNION;
#endif
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_odd_1_START   (0)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_odd_1_END     (9)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_even_1_START  (16)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_even_1_END    (25)






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

#endif /* end of soc_isp_drc_interface.h */
