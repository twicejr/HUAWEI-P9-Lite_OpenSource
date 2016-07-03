

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_DPCC_INTERFACE_H__
#define __SOC_ISP_DPCC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) DPCC
 ****************************************************************************/
/* 寄存器说明：Mode control for DPC detection unit
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_MODE_UNION */
#define SOC_ISP_DPCC_DPCC_MODE_ADDR(base)             ((base) + (0x0))

/* 寄存器说明：Interpolation mode for correction unit
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_OUTPUT_MODE_UNION */
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_ADDR(base)      ((base) + (0x4))

/* 寄存器说明：Methods set usage for detection
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_SET_USE_UNION */
#define SOC_ISP_DPCC_DPCC_SET_USE_ADDR(base)          ((base) + (0x8))

/* 寄存器说明：Methods enable bits for SET_1
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_METHODS_SET_1_UNION */
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ADDR(base)    ((base) + (0xC))

/* 寄存器说明：Methods enable bits for SET_2
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_METHODS_SET_2_UNION */
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ADDR(base)    ((base) + (0x10))

/* 寄存器说明：Methods enable bits for SET_3
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_METHODS_SET_3_UNION */
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ADDR(base)    ((base) + (0x14))

/* 寄存器说明：Line threshold for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_LINE_THRESH1_UNION */
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_ADDR(base)     ((base) + (0x18))

/* 寄存器说明：Mean Absolute Difference (MAD) factor for Line check for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_UNION */
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_ADDR(base)    ((base) + (0x1C))

/* 寄存器说明：Peak gradient factor for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_PG_FAC1_UNION */
#define SOC_ISP_DPCC_DPCC_PG_FAC1_ADDR(base)          ((base) + (0x20))

/* 寄存器说明：Rank Neighbor Difference threshold for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RND_THRESH1_UNION */
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_ADDR(base)      ((base) + (0x24))

/* 寄存器说明：Rank gradient factor for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RG_FAC1_UNION */
#define SOC_ISP_DPCC_DPCC_RG_FAC1_ADDR(base)          ((base) + (0x28))

/* 寄存器说明：Line threshold for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_LINE_THRESH2_UNION */
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_ADDR(base)     ((base) + (0x2C))

/* 寄存器说明：Mean Absolute Difference (MAD) factor for Line check for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_UNION */
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_ADDR(base)    ((base) + (0x30))

/* 寄存器说明：Peak gradient factor for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_PG_FAC2_UNION */
#define SOC_ISP_DPCC_DPCC_PG_FAC2_ADDR(base)          ((base) + (0x34))

/* 寄存器说明：Rank Neighbor Difference threshold for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RND_THRESH2_UNION */
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_ADDR(base)      ((base) + (0x38))

/* 寄存器说明：Rank gradient factor for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RG_FAC2_UNION */
#define SOC_ISP_DPCC_DPCC_RG_FAC2_ADDR(base)          ((base) + (0x3C))

/* 寄存器说明：Line threshold for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_LINE_THRESH3_UNION */
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_ADDR(base)     ((base) + (0x40))

/* 寄存器说明：Mean Absolute Difference (MAD) factor for Line check for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_UNION */
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_ADDR(base)    ((base) + (0x44))

/* 寄存器说明：Peak gradient factor for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_PG_FAC3_UNION */
#define SOC_ISP_DPCC_DPCC_PG_FAC3_ADDR(base)          ((base) + (0x48))

/* 寄存器说明：Rank Neighbor Difference threshold for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RND_THRESH3_UNION */
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_ADDR(base)      ((base) + (0x4C))

/* 寄存器说明：Rank gradient factor for corresponding SET
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RG_FAC3_UNION */
#define SOC_ISP_DPCC_DPCC_RG_FAC3_ADDR(base)          ((base) + (0x50))

/* 寄存器说明：Rank Order Limits
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RO_LIMITS_UNION */
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ADDR(base)        ((base) + (0x54))

/* 寄存器说明：Differential Rank Offsets for Rank Neighbor Difference
   位域定义UNION结构:  SOC_ISP_DPCC_DPCC_RND_OFFS_UNION */
#define SOC_ISP_DPCC_DPCC_RND_OFFS_ADDR(base)         ((base) + (0x58))





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
                     (1/1) DPCC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_MODE_UNION
 结构说明  : DPCC_MODE 寄存器结构定义。地址偏移量:0x0，初值:0x00000004，宽度:32
 寄存器说明: Mode control for DPC detection unit
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpc_enable    : 1;  /* bit[0]   : Enable bit
                                                        1: enable DPC 
                                                        0: bypass DPC */
        unsigned int  reserved_0    : 1;  /* bit[1]   : reserved */
        unsigned int  stage1_enable : 1;  /* bit[2]   : Stage1 enable
                                                        1: enable stage1
                                                        0: bypass stage1 */
        unsigned int  reserved_1    : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_MODE_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_MODE_dpc_enable_START     (0)
#define SOC_ISP_DPCC_DPCC_MODE_dpc_enable_END       (0)
#define SOC_ISP_DPCC_DPCC_MODE_stage1_enable_START  (2)
#define SOC_ISP_DPCC_DPCC_MODE_stage1_enable_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_OUTPUT_MODE_UNION
 结构说明  : DPCC_OUTPUT_MODE 寄存器结构定义。地址偏移量:0x4，初值:0x00000000，宽度:32
 寄存器说明: Interpolation mode for correction unit
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stage1_incl_green_center : 1;  /* bit[0]   : 1: stage1 include center pixel for green output median 2x2+1 
                                                                   0: stage1 do not include center pixel for green output median 2x2 */
        unsigned int  stage1_incl_rb_center    : 1;  /* bit[1]   : 1: stage1 include center pixel for red/blue output median 2x2+1 
                                                                   0: stage1 do not include center pixel for red/blue output median 2x2 */
        unsigned int  stage1_g_3x3             : 1;  /* bit[2]   : 1: stage1 green 9 pixel (3x3) output median 
                                                                   0: stage1 green 4 or 5 pixel output median */
        unsigned int  stage1_rb_3x3            : 1;  /* bit[3]   : 1: stage1 red/blue 9 pixel (3x3) output median 
                                                                   0: stage1 red/blue 4 or 5 pixel output median */
        unsigned int  reserved                 : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_OUTPUT_MODE_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_green_center_START  (0)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_green_center_END    (0)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_rb_center_START     (1)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_rb_center_END       (1)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_g_3x3_START              (2)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_g_3x3_END                (2)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_rb_3x3_START             (3)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_rb_3x3_END               (3)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_SET_USE_UNION
 结构说明  : DPCC_SET_USE 寄存器结构定义。地址偏移量:0x8，初值:0x00000001，宽度:32
 寄存器说明: Methods set usage for detection
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stage1_use_set1    : 1;  /* bit[0]   : 1: stage1 use methods set 1 
                                                             0: stage1 do not use methods set 1 */
        unsigned int  stage1_use_set2    : 1;  /* bit[1]   : 1: stage1 use methods set 2 
                                                             0: stage1 do not use methods set 2 */
        unsigned int  stage1_use_set3    : 1;  /* bit[2]   : 1: stage1 use methods set 3 
                                                             0: stage1 do not use methods set 3 */
        unsigned int  stage1_use_fix_set : 1;  /* bit[3]   : 1: stage1 use hard coded methods set
                                                             0: stage1 do not use hard coded methods set */
        unsigned int  reserved           : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_SET_USE_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set1_START     (0)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set1_END       (0)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set2_START     (1)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set2_END       (1)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set3_START     (2)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set3_END       (2)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_fix_set_START  (3)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_fix_set_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_METHODS_SET_1_UNION
 结构说明  : DPCC_METHODS_SET_1 寄存器结构定义。地址偏移量:0xC，初值:0x00001D1D，宽度:32
 寄存器说明: Methods enable bits for SET_1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_green1_enable     : 1;  /* bit[0]    : 1: enable Peak Gradient check for green
                                                                0: bypass Peak Gradient check for green */
        unsigned int  lc_green1_enable     : 1;  /* bit[1]    : 1: enable Line check for green
                                                                0: bypass Line check for green */
        unsigned int  ro_green1_enable     : 1;  /* bit[2]    : 1: enable Rank Order check for green
                                                                0: bypass Rank Order check for green */
        unsigned int  rnd_green1_enable    : 1;  /* bit[3]    : 1: enable Rank Neighbor Difference check for green
                                                                0: bypass Rank Neighbor Difference check for green */
        unsigned int  rg_green1_enable     : 1;  /* bit[4]    : 1: enable Rank Gradient check for green
                                                                0: bypass Rank Gradient check for green */
        unsigned int  reserved_0           : 3;  /* bit[5-7]  : reserved */
        unsigned int  pg_red_blue1_enable  : 1;  /* bit[8]    : 1: enable Peak Gradient check for red_blue
                                                                0: bypass Peak Gradient check for red_blue */
        unsigned int  lc_red_blue1_enable  : 1;  /* bit[9]    : 1: enable Line check for red_blue
                                                                0: bypass Line check for red_blue */
        unsigned int  ro_red_blue1_enable  : 1;  /* bit[10]   : 1: enable Rank Order check for red_blue
                                                                0: bypass Rank Order check for red_blue */
        unsigned int  rnd_red_blue1_enable : 1;  /* bit[11]   : 1: enable Rank Neighbor Difference check for red_blue
                                                                0: bypass Rank Neighbor Difference check for red_blue */
        unsigned int  rg_red_blue1_enable  : 1;  /* bit[12]   : 1: enable Rank Gradient check for red_blue
                                                                0: bypass Rank Gradient check for red_blue */
        unsigned int  reserved_1           : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_METHODS_SET_1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_green1_enable_START      (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_green1_enable_END        (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_green1_enable_START      (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_green1_enable_END        (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_green1_enable_START      (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_green1_enable_END        (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_green1_enable_START     (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_green1_enable_END       (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_green1_enable_START      (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_green1_enable_END        (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_red_blue1_enable_START   (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_red_blue1_enable_END     (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_red_blue1_enable_START   (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_red_blue1_enable_END     (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_red_blue1_enable_START   (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_red_blue1_enable_END     (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_red_blue1_enable_START  (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_red_blue1_enable_END    (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_red_blue1_enable_START   (12)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_red_blue1_enable_END     (12)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_METHODS_SET_2_UNION
 结构说明  : DPCC_METHODS_SET_2 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: Methods enable bits for SET_2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_green2_enable     : 1;  /* bit[0]    : 1: enable Peak Gradient check for green
                                                                0: bypass Peak Gradient check for green */
        unsigned int  lc_green2_enable     : 1;  /* bit[1]    : 1: enable Line check for green
                                                                0: bypass Line check for green */
        unsigned int  ro_green2_enable     : 1;  /* bit[2]    : 1: enable Rank Order check for green
                                                                0: bypass Rank Order check for green */
        unsigned int  rnd_green2_enable    : 1;  /* bit[3]    : 1: enable Rank Neighbor Difference check for green
                                                                0: bypass Rank Neighbor Difference check for green */
        unsigned int  rg_green2_enable     : 1;  /* bit[4]    : 1: enable Rank Gradient check for green
                                                                0: bypass Rank Gradient check for green */
        unsigned int  reserved_0           : 3;  /* bit[5-7]  : reserved */
        unsigned int  pg_red_blue2_enable  : 1;  /* bit[8]    : 1: enable Peak Gradient check for red_blue
                                                                0: bypass Peak Gradient check for red_blue */
        unsigned int  lc_red_blue2_enable  : 1;  /* bit[9]    : 1: enable Line check for red_blue
                                                                0: bypass Line check for red_blue */
        unsigned int  ro_red_blue2_enable  : 1;  /* bit[10]   : 1: enable Rank Order check for red_blue
                                                                0: bypass Rank Order check for red_blue */
        unsigned int  rnd_red_blue2_enable : 1;  /* bit[11]   : 1: enable Rank Neighbor Difference check for red_blue
                                                                0: bypass Rank Neighbor Difference check for red_blue */
        unsigned int  rg_red_blue2_enable  : 1;  /* bit[12]   : 1: enable Rank Gradient check for red_blue
                                                                0: bypass Rank Gradient check for red_blue */
        unsigned int  reserved_1           : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_METHODS_SET_2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_green2_enable_START      (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_green2_enable_END        (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_green2_enable_START      (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_green2_enable_END        (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_green2_enable_START      (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_green2_enable_END        (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_green2_enable_START     (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_green2_enable_END       (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_green2_enable_START      (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_green2_enable_END        (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_red_blue2_enable_START   (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_red_blue2_enable_END     (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_red_blue2_enable_START   (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_red_blue2_enable_END     (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_red_blue2_enable_START   (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_red_blue2_enable_END     (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_red_blue2_enable_START  (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_red_blue2_enable_END    (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_red_blue2_enable_START   (12)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_red_blue2_enable_END     (12)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_METHODS_SET_3_UNION
 结构说明  : DPCC_METHODS_SET_3 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: Methods enable bits for SET_3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_green3_enable     : 1;  /* bit[0]    : 1: enable Peak Gradient check for green
                                                                0: bypass Peak Gradient check for green */
        unsigned int  lc_green3_enable     : 1;  /* bit[1]    : 1: enable Line check for green
                                                                0: bypass Line check for green */
        unsigned int  ro_green3_enable     : 1;  /* bit[2]    : 1: enable Rank Order check for green
                                                                0: bypass Rank Order check for green */
        unsigned int  rnd_green3_enable    : 1;  /* bit[3]    : 1: enable Rank Neighbor Difference check for green
                                                                0: bypass Rank Neighbor Difference check for green */
        unsigned int  rg_green3_enable     : 1;  /* bit[4]    : 1: enable Rank Gradient check for green
                                                                0: bypass Rank Gradient check for green */
        unsigned int  reserved_0           : 3;  /* bit[5-7]  : reserved */
        unsigned int  pg_red_blue3_enable  : 1;  /* bit[8]    : 1: enable Peak Gradient check for red_blue
                                                                0: bypass Peak Gradient check for red_blue */
        unsigned int  lc_red_blue3_enable  : 1;  /* bit[9]    : 1: enable Line check for red_blue
                                                                0: bypass Line check for red_blue */
        unsigned int  ro_red_blue3_enable  : 1;  /* bit[10]   : 1: enable Rank Order check for red_blue
                                                                0: bypass Rank Order check for red_blue */
        unsigned int  rnd_red_blue3_enable : 1;  /* bit[11]   : 1: enable Rank Neighbor Difference check for red_blue
                                                                0: bypass Rank Neighbor Difference check for red_blue */
        unsigned int  rg_red_blue3_enable  : 1;  /* bit[12]   : 1: enable Rank Gradient check for red_blue
                                                                0: bypass Rank Gradient check for red_blue */
        unsigned int  reserved_1           : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_METHODS_SET_3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_green3_enable_START      (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_green3_enable_END        (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_green3_enable_START      (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_green3_enable_END        (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_green3_enable_START      (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_green3_enable_END        (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_green3_enable_START     (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_green3_enable_END       (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_green3_enable_START      (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_green3_enable_END        (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_red_blue3_enable_START   (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_red_blue3_enable_END     (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_red_blue3_enable_START   (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_red_blue3_enable_END     (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_red_blue3_enable_START   (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_red_blue3_enable_END     (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_red_blue3_enable_START  (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_red_blue3_enable_END    (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_red_blue3_enable_START   (12)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_red_blue3_enable_END     (12)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_LINE_THRESH1_UNION
 结构说明  : DPCC_LINE_THRESH1 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: Line threshold for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_thr1_g  : 8;  /* bit[0-7]  : line threshold for green */
        unsigned int  line_thr1_rb : 8;  /* bit[8-15] : line threshold for red/blue */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_THRESH1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_g_START   (0)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_g_END     (7)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_rb_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_UNION
 结构说明  : DPCC_LINE_MAD_FAC1 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: Mean Absolute Difference (MAD) factor for Line check for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_mad_fac_1_g  : 6;  /* bit[0-5]  : line MAD factor for green - Range: 1..63 */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : reserved */
        unsigned int  line_mad_fac_1_rb : 6;  /* bit[8-13] : line MAD factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1        : 18; /* bit[14-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_g_START   (0)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_g_END     (5)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_PG_FAC1_UNION
 结构说明  : DPCC_PG_FAC1 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: Peak gradient factor for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_fac_1_g  : 6;  /* bit[0-5]  : Peak gradient factor for green - Range: 1..63 */
        unsigned int  reserved_0  : 2;  /* bit[6-7]  : reserved */
        unsigned int  pg_fac_1_rb : 6;  /* bit[8-13] : Peak gradient factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1  : 18; /* bit[14-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_PG_FAC1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_g_START   (0)
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_g_END     (5)
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RND_THRESH1_UNION
 结构说明  : DPCC_RND_THRESH1 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: Rank Neighbor Difference threshold for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnd_thr1_g  : 8;  /* bit[0-7]  : Rank Neighbor Difference threshold for green */
        unsigned int  rnd_thr1_rb : 8;  /* bit[8-15] : Rank Neighbor Difference threshold for red/blue */
        unsigned int  reserved    : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_RND_THRESH1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_g_END     (7)
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_rb_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RG_FAC1_UNION
 结构说明  : DPCC_RG_FAC1 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: Rank gradient factor for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rg_fac_1_g  : 6;  /* bit[0-5]  : Rank gradient factor for green - Range: 1..63 */
        unsigned int  reserved_0  : 2;  /* bit[6-7]  : reserved */
        unsigned int  rg_fac_1_rb : 6;  /* bit[8-13] : Rank gradient factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1  : 18; /* bit[14-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_RG_FAC1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_g_END     (5)
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_LINE_THRESH2_UNION
 结构说明  : DPCC_LINE_THRESH2 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: Line threshold for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_thr2_g  : 8;  /* bit[0-7]  : line threshold for green */
        unsigned int  line_thr2_rb : 8;  /* bit[8-15] : line threshold for red/blue */
        unsigned int  reserved     : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_THRESH2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_g_START   (0)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_g_END     (7)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_rb_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_UNION
 结构说明  : DPCC_LINE_MAD_FAC2 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: Mean Absolute Difference (MAD) factor for Line check for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_mad_fac_2_g  : 6;  /* bit[0-5]  : line MAD factor for green - Range: 1..63 */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : reserved */
        unsigned int  line_mad_fac_2_rb : 6;  /* bit[8-13] : line MAD factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1        : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_g_START   (0)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_g_END     (5)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_PG_FAC2_UNION
 结构说明  : DPCC_PG_FAC2 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: Peak gradient factor for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_fac_2_g  : 6;  /* bit[0-5]  : Peak gradient factor for green - Range: 1..63 */
        unsigned int  reserved_0  : 2;  /* bit[6-7]  : reserved */
        unsigned int  pg_fac_2_rb : 6;  /* bit[8-13] : Peak gradient factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_PG_FAC2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_g_START   (0)
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_g_END     (5)
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RND_THRESH2_UNION
 结构说明  : DPCC_RND_THRESH2 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: Rank Neighbor Difference threshold for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnd_thr2_g  : 8;  /* bit[0-7]  : Rank Neighbor Difference threshold for green */
        unsigned int  rnd_thr2_rb : 8;  /* bit[8-15] : Rank Neighbor Difference threshold for red/blue */
        unsigned int  reserved    : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_RND_THRESH2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_g_END     (7)
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_rb_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RG_FAC2_UNION
 结构说明  : DPCC_RG_FAC2 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: Rank gradient factor for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rg_fac_2_g  : 6;  /* bit[0-5]  : Rank gradient factor for green - Range: 1..63 */
        unsigned int  reserved_0  : 2;  /* bit[6-7]  : reserved */
        unsigned int  rg_fac_2_rb : 6;  /* bit[8-13] : Rank gradient factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_RG_FAC2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_g_END     (5)
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_LINE_THRESH3_UNION
 结构说明  : DPCC_LINE_THRESH3 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: Line threshold for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_thr3_g  : 8;  /* bit[0-7]  : line threshold for green */
        unsigned int  line_thr3_rb : 8;  /* bit[8-15] : line threshold for red/blue */
        unsigned int  reserved     : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_THRESH3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_g_START   (0)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_g_END     (7)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_rb_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_UNION
 结构说明  : DPCC_LINE_MAD_FAC3 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: Mean Absolute Difference (MAD) factor for Line check for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_mad_fac_3_g  : 6;  /* bit[0-5]  : line MAD factor for green - Range: 1..63 */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : reserved */
        unsigned int  line_mad_fac_3_rb : 6;  /* bit[8-13] : line MAD factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1        : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_g_START   (0)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_g_END     (5)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_PG_FAC3_UNION
 结构说明  : DPCC_PG_FAC3 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: Peak gradient factor for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_fac_3_g  : 6;  /* bit[0-5]  : Peak gradient factor for green - Range: 1..63 */
        unsigned int  reserved_0  : 2;  /* bit[6-7]  : reserved */
        unsigned int  pg_fac_3_rb : 6;  /* bit[8-13] : Peak gradient factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_PG_FAC3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_g_START   (0)
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_g_END     (5)
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RND_THRESH3_UNION
 结构说明  : DPCC_RND_THRESH3 寄存器结构定义。地址偏移量:0x4C，初值:0x00000000，宽度:32
 寄存器说明: Rank Neighbor Difference threshold for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnd_thr3_g  : 8;  /* bit[0-7]  : Rank Neighbor Difference threshold for green */
        unsigned int  rnd_thr3_rb : 8;  /* bit[8-15] : Rank Neighbor Difference threshold for red/blue */
        unsigned int  reserved    : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_RND_THRESH3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_g_END     (7)
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_rb_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RG_FAC3_UNION
 结构说明  : DPCC_RG_FAC3 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: Rank gradient factor for corresponding SET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rg_fac_3_g  : 6;  /* bit[0-5]  : Rank gradient factor for green - Range: 1..63 */
        unsigned int  reserved_0  : 2;  /* bit[6-7]  : reserved */
        unsigned int  rg_fac_3_rb : 6;  /* bit[8-13] : Rank gradient factor for red/blue - Range: 1..63 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_DPCC_DPCC_RG_FAC3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_g_END     (5)
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_rb_START  (8)
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_rb_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RO_LIMITS_UNION
 结构说明  : DPCC_RO_LIMITS 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: Rank Order Limits
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ro_lim_1_g  : 2;  /* bit[0-1]  : Rank order limit for set 1 green - Range: 1..3 */
        unsigned int  ro_lim_1_rb : 2;  /* bit[2-3]  : Rank order limit for set 1 red/blue - Range: 1..3 */
        unsigned int  ro_lim_2_g  : 2;  /* bit[4-5]  : Rank order limit for set 2 green - Range: 1..3 */
        unsigned int  ro_lim_2_rb : 2;  /* bit[6-7]  : Rank order limit for set 2 red/blue - Range: 1..3 */
        unsigned int  ro_lim_3_g  : 2;  /* bit[8-9]  : Rank order limit for set 3 green - Range: 1..3 */
        unsigned int  ro_lim_3_rb : 2;  /* bit[10-11]: Rank order limit for set 3 red/blue - Range: 1..3 */
        unsigned int  reserved    : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_RO_LIMITS_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_g_END     (1)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_rb_START  (2)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_rb_END    (3)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_g_START   (4)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_g_END     (5)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_rb_START  (6)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_rb_END    (7)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_g_START   (8)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_g_END     (9)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_rb_START  (10)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_rb_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_DPCC_DPCC_RND_OFFS_UNION
 结构说明  : DPCC_RND_OFFS 寄存器结构定义。地址偏移量:0x58，初值:0x00000000，宽度:32
 寄存器说明: Differential Rank Offsets for Rank Neighbor Difference
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnd_offs_1_g  : 2;  /* bit[0-1]  : Rank Offset to Neighbor for set 1 green - Range: 1..3 */
        unsigned int  rnd_offs_1_rb : 2;  /* bit[2-3]  : Rank Offset to Neighbor for set 1 red/blue - Range: 1..3 */
        unsigned int  rnd_offs_2_g  : 2;  /* bit[4-5]  : Rank Offset to Neighbor for set 2 green - Range: 1..3 */
        unsigned int  rnd_offs_2_rb : 2;  /* bit[6-7]  : Rank Offset to Neighbor for set 2 red/blue - Range: 1..3 */
        unsigned int  rnd_offs_3_g  : 2;  /* bit[8-9]  : Rank Offset to Neighbor for set 3 green - Range: 1..3 */
        unsigned int  rnd_offs_3_rb : 2;  /* bit[10-11]: Rank Offset to Neighbor for set 3 red/blue - Range: 1..3 */
        unsigned int  reserved      : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_ISP_DPCC_DPCC_RND_OFFS_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_g_START   (0)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_g_END     (1)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_rb_START  (2)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_rb_END    (3)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_g_START   (4)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_g_END     (5)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_rb_START  (6)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_rb_END    (7)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_g_START   (8)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_g_END     (9)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_rb_START  (10)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_rb_END    (11)






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

#endif /* end of soc_isp_dpcc_interface.h */
