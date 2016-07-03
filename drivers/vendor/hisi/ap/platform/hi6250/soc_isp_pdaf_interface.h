

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_PDAF_INTERFACE_H__
#define __SOC_ISP_PDAF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) PDAF
 ****************************************************************************/
/* 寄存器说明：PDAF control
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_CTRL_UNION */
#define SOC_ISP_PDAF_PDAF_CTRL_ADDR(base)             ((base) + (0x0000))

/* 寄存器说明：red ram address
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_R_TABLE_ADDR_UNION */
#define SOC_ISP_PDAF_PDAF_R_TABLE_ADDR_ADDR(base)     ((base) + (0x0004))

/* 寄存器说明：green-red ram address
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_GR_TABLE_ADDR_UNION */
#define SOC_ISP_PDAF_PDAF_GR_TABLE_ADDR_ADDR(base)    ((base) + (0x0008))

/* 寄存器说明：blue ram address
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_B_TABLE_ADDR_UNION */
#define SOC_ISP_PDAF_PDAF_B_TABLE_ADDR_ADDR(base)     ((base) + (0x000C))

/* 寄存器说明：green-blue ram address
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_GB_TABLE_ADDR_UNION */
#define SOC_ISP_PDAF_PDAF_GB_TABLE_ADDR_ADDR(base)    ((base) + (0x0010))

/* 寄存器说明：Sample table red
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_R_TABLE_DATA_UNION */
#define SOC_ISP_PDAF_PDAF_R_TABLE_DATA_ADDR(base)     ((base) + (0x0014))

/* 寄存器说明：Sample table gren - red
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_UNION */
#define SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_ADDR(base)    ((base) + (0x0018))

/* 寄存器说明：Sample table blue
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_B_TABLE_DATA_UNION */
#define SOC_ISP_PDAF_PDAF_B_TABLE_DATA_ADDR(base)     ((base) + (0x001C))

/* 寄存器说明：Sample table green blue
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_UNION */
#define SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_ADDR(base)    ((base) + (0x0020))

/* 寄存器说明：Gradient table x
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XGRAD_0_1_UNION */
#define SOC_ISP_PDAF_PDAF_XGRAD_0_1_ADDR(base)        ((base) + (0x0024))

/* 寄存器说明：Gradient table x
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XGRAD_2_3_UNION */
#define SOC_ISP_PDAF_PDAF_XGRAD_2_3_ADDR(base)        ((base) + (0x0028))

/* 寄存器说明：Gradient table x
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XGRAD_4_5_UNION */
#define SOC_ISP_PDAF_PDAF_XGRAD_4_5_ADDR(base)        ((base) + (0x002C))

/* 寄存器说明：Gradient table x
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XGRAD_6_7_UNION */
#define SOC_ISP_PDAF_PDAF_XGRAD_6_7_ADDR(base)        ((base) + (0x0030))

/* 寄存器说明：Gradient table x
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XGRAD_8_9_UNION */
#define SOC_ISP_PDAF_PDAF_XGRAD_8_9_ADDR(base)        ((base) + (0x0034))

/* 寄存器说明：Gradient table x
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XGRAD_10_UNION */
#define SOC_ISP_PDAF_PDAF_XGRAD_10_ADDR(base)         ((base) + (0x0038))

/* 寄存器说明：Gradient table y
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YGRAD_0_1_UNION */
#define SOC_ISP_PDAF_PDAF_YGRAD_0_1_ADDR(base)        ((base) + (0x003C))

/* 寄存器说明：Gradient table y
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YGRAD_2_3_UNION */
#define SOC_ISP_PDAF_PDAF_YGRAD_2_3_ADDR(base)        ((base) + (0x0040))

/* 寄存器说明：Gradient table y
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YGRAD_4_5_UNION */
#define SOC_ISP_PDAF_PDAF_YGRAD_4_5_ADDR(base)        ((base) + (0x0044))

/* 寄存器说明：Gradient table y
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YGRAD_6_7_UNION */
#define SOC_ISP_PDAF_PDAF_YGRAD_6_7_ADDR(base)        ((base) + (0x0048))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XSIZE_0_1_UNION */
#define SOC_ISP_PDAF_PDAF_XSIZE_0_1_ADDR(base)        ((base) + (0x004C))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XSIZE_2_3_UNION */
#define SOC_ISP_PDAF_PDAF_XSIZE_2_3_ADDR(base)        ((base) + (0x0050))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XSIZE_4_5_UNION */
#define SOC_ISP_PDAF_PDAF_XSIZE_4_5_ADDR(base)        ((base) + (0x0054))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XSIZE_6_7_UNION */
#define SOC_ISP_PDAF_PDAF_XSIZE_6_7_ADDR(base)        ((base) + (0x0058))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XSIZE_8_9_UNION */
#define SOC_ISP_PDAF_PDAF_XSIZE_8_9_ADDR(base)        ((base) + (0x005C))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_XSIZE_10_UNION */
#define SOC_ISP_PDAF_PDAF_XSIZE_10_ADDR(base)         ((base) + (0x0060))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YSIZE_0_1_UNION */
#define SOC_ISP_PDAF_PDAF_YSIZE_0_1_ADDR(base)        ((base) + (0x0064))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YSIZE_2_3_UNION */
#define SOC_ISP_PDAF_PDAF_YSIZE_2_3_ADDR(base)        ((base) + (0x0068))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YSIZE_4_5_UNION */
#define SOC_ISP_PDAF_PDAF_YSIZE_4_5_ADDR(base)        ((base) + (0x006C))

/* 寄存器说明：size table
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_YSIZE_6_7_UNION */
#define SOC_ISP_PDAF_PDAF_YSIZE_6_7_ADDR(base)        ((base) + (0x0070))

/* 寄存器说明：Image location offset in the block that includes the upper left corner of the image
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_UNION */
#define SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_ADDR(base) ((base) + (0x0074))

/* 寄存器说明：Image location offset in the block that includes the upper left corner of the image
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_UNION */
#define SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_ADDR(base)  ((base) + (0x0078))

/* 寄存器说明：Global PDAF configuration register
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_CFG_UNION */
#define SOC_ISP_PDAF_PDAF_CFG_ADDR(base)              ((base) + (0x100))

/* 寄存器说明：Configuration to use when mode=0x2 (Threshold based)
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_SATURATION_CFG_UNION */
#define SOC_ISP_PDAF_PDAF_SATURATION_CFG_ADDR(base)   ((base) + (0x104))

/* 寄存器说明：PDAF Horizontal Region of interest
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_ROI_H_UNION */
#define SOC_ISP_PDAF_PDAF_ROI_H_ADDR(base)            ((base) + (0x108))

/* 寄存器说明：PDAF Vertical Region of interest
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_ROI_V_UNION */
#define SOC_ISP_PDAF_PDAF_ROI_V_ADDR(base)            ((base) + (0x10C))

/* 寄存器说明：PP location
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_LOCATION_UNION */
#define SOC_ISP_PDAF_PDAF_LOCATION_ADDR(base, PP_location_Range)  ((base) + (0x110+0x4*(PP_location_Range)))

/* 寄存器说明：pdaf status
   位域定义UNION结构:  SOC_ISP_PDAF_PDAF_STATUS_UNION */
#define SOC_ISP_PDAF_PDAF_STATUS_ADDR(base)           ((base) + (0x200))





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
                     (1/1) PDAF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_CTRL_UNION
 结构说明  : PDAF_CTRL 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: PDAF control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdaf_en  : 1;  /* bit[0]   : 0: deactivation request for lens shading correction
                                                   1: activation request for lens shading correction  */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_CTRL_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_CTRL_pdaf_en_START   (0)
#define SOC_ISP_PDAF_PDAF_CTRL_pdaf_en_END     (0)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_R_TABLE_ADDR_UNION
 结构说明  : PDAF_R_TABLE_ADDR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: red ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Red color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203 [as a consequence bit 8 shall always be 0].
                                                     
                                                     [Note] on programming sequence: To fill the RED table, first set this base address register and then write in sequence your data in Sample table RED.
                                                     => If another table need to be configured, corresponding base address must be set again [end] */
        unsigned int  reserved   : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_R_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_R_TABLE_ADDR_r_ram_addr_START  (0)
#define SOC_ISP_PDAF_PDAF_R_TABLE_ADDR_r_ram_addr_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_GR_TABLE_ADDR_UNION
 结构说明  : PDAF_GR_TABLE_ADDR 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: green-red ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gr_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Green (Red) color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203 [as a consequence bit 8 shall always be 0].
                                                      
                                                      [Note] on programming sequence: To fill the GREEN-RED table, first set this base address register and then write in sequence your data in Sample table GREEN-RED.
                                                      => If another table need to be configured, corresponding base address must be set again [end] */
        unsigned int  reserved    : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_GR_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_GR_TABLE_ADDR_gr_ram_addr_START  (0)
#define SOC_ISP_PDAF_PDAF_GR_TABLE_ADDR_gr_ram_addr_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_B_TABLE_ADDR_UNION
 结构说明  : PDAF_B_TABLE_ADDR 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: blue ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Blue color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203 [as a consequence bit 8 shall always be 0].
                                                     
                                                     [Note] on programming sequence: To fill the BLUE table, first set this base address register and then write in sequence your data in Sample table BLUE.
                                                     => If another table need to be configured, corresponding base address must be set again[end] */
        unsigned int  reserved   : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_B_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_B_TABLE_ADDR_b_ram_addr_START  (0)
#define SOC_ISP_PDAF_PDAF_B_TABLE_ADDR_b_ram_addr_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_GB_TABLE_ADDR_UNION
 结构说明  : PDAF_GB_TABLE_ADDR 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: green-blue ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gb_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Green (Blue) color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203 [as a consequence bit 8 shall always be 0].
                                                      
                                                      [Note] on programming sequence: To fill the GREEN-BLUE table, first set this base address register and then write in sequence your data in Sample table GREEN-BLUE.
                                                      => If another table need to be configured, corresponding base address must be set again[end] */
        unsigned int  reserved    : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_GB_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_GB_TABLE_ADDR_gb_ram_addr_START  (0)
#define SOC_ISP_PDAF_PDAF_GB_TABLE_ADDR_gb_ram_addr_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_R_TABLE_DATA_UNION
 结构说明  : PDAF_R_TABLE_DATA 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: Sample table red
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_sample_0 : 13; /* bit[0-12] : [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_0 : 3;  /* bit[13-15]: Reserved */
        unsigned int  r_sample_1 : 13; /* bit[16-28]: [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_1 : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_R_TABLE_DATA_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_R_TABLE_DATA_r_sample_0_START  (0)
#define SOC_ISP_PDAF_PDAF_R_TABLE_DATA_r_sample_0_END    (12)
#define SOC_ISP_PDAF_PDAF_R_TABLE_DATA_r_sample_1_START  (16)
#define SOC_ISP_PDAF_PDAF_R_TABLE_DATA_r_sample_1_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_UNION
 结构说明  : PDAF_GR_TABLE_DATA 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: Sample table gren - red
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gr_sample_0 : 13; /* bit[0-12] : [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_0  : 3;  /* bit[13-15]: Reserved */
        unsigned int  gr_sample_1 : 13; /* bit[16-28]: [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_1  : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_gr_sample_0_START  (0)
#define SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_gr_sample_0_END    (12)
#define SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_gr_sample_1_START  (16)
#define SOC_ISP_PDAF_PDAF_GR_TABLE_DATA_gr_sample_1_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_B_TABLE_DATA_UNION
 结构说明  : PDAF_B_TABLE_DATA 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: Sample table blue
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_sample_0 : 13; /* bit[0-12] : [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_0 : 3;  /* bit[13-15]: Reserved */
        unsigned int  b_sample_1 : 13; /* bit[16-28]: [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_1 : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_B_TABLE_DATA_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_B_TABLE_DATA_b_sample_0_START  (0)
#define SOC_ISP_PDAF_PDAF_B_TABLE_DATA_b_sample_0_END    (12)
#define SOC_ISP_PDAF_PDAF_B_TABLE_DATA_b_sample_1_START  (16)
#define SOC_ISP_PDAF_PDAF_B_TABLE_DATA_b_sample_1_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_UNION
 结构说明  : PDAF_GB_TABLE_DATA 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: Sample table green blue
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gb_sample_0 : 13; /* bit[0-12] : [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_0  : 3;  /* bit[13-15]: Reserved */
        unsigned int  gb_sample_1 : 13; /* bit[16-28]: [Note]correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 0..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).[end] */
        unsigned int  reserved_1  : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_gb_sample_0_START  (0)
#define SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_gb_sample_0_END    (12)
#define SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_gb_sample_1_START  (16)
#define SOC_ISP_PDAF_PDAF_GB_TABLE_DATA_gb_sample_1_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XGRAD_0_1_UNION
 结构说明  : PDAF_XGRAD_0_1 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_0  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 0. 
                                                    [Note]: x_grad_0 must be equal to 2**15 / x_sect_size_0[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_1  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 1. 
                                                    [Note]: x_grad_1 must be equal to 2**15 / x_sect_size_1[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XGRAD_0_1_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XGRAD_0_1_xgrad_0_START   (0)
#define SOC_ISP_PDAF_PDAF_XGRAD_0_1_xgrad_0_END     (11)
#define SOC_ISP_PDAF_PDAF_XGRAD_0_1_xgrad_1_START   (16)
#define SOC_ISP_PDAF_PDAF_XGRAD_0_1_xgrad_1_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XGRAD_2_3_UNION
 结构说明  : PDAF_XGRAD_2_3 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_2  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 2. 
                                                    [Note]: x_grad_2 must be equal to 2**15 / x_sect_size_2[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_3  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 3. 
                                                    [Note]: x_grad_3 must be equal to 2**15 / x_sect_size_3[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XGRAD_2_3_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XGRAD_2_3_xgrad_2_START   (0)
#define SOC_ISP_PDAF_PDAF_XGRAD_2_3_xgrad_2_END     (11)
#define SOC_ISP_PDAF_PDAF_XGRAD_2_3_xgrad_3_START   (16)
#define SOC_ISP_PDAF_PDAF_XGRAD_2_3_xgrad_3_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XGRAD_4_5_UNION
 结构说明  : PDAF_XGRAD_4_5 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_4  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 4. 
                                                    [Note]: x_grad_4 must be equal to 2**15 / x_sect_size_4[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_5  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 5. 
                                                    [Note]: x_grad_5 must be equal to 2**15 / x_sect_size_5[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XGRAD_4_5_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XGRAD_4_5_xgrad_4_START   (0)
#define SOC_ISP_PDAF_PDAF_XGRAD_4_5_xgrad_4_END     (11)
#define SOC_ISP_PDAF_PDAF_XGRAD_4_5_xgrad_5_START   (16)
#define SOC_ISP_PDAF_PDAF_XGRAD_4_5_xgrad_5_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XGRAD_6_7_UNION
 结构说明  : PDAF_XGRAD_6_7 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_6  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 6. 
                                                    [Note]: x_grad_6 must be equal to 2**15 / x_sect_size_6[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_7  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 7. 
                                                    [Note]: x_grad_7 must be equal to 2**15 / x_sect_size_7[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XGRAD_6_7_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XGRAD_6_7_xgrad_6_START   (0)
#define SOC_ISP_PDAF_PDAF_XGRAD_6_7_xgrad_6_END     (11)
#define SOC_ISP_PDAF_PDAF_XGRAD_6_7_xgrad_7_START   (16)
#define SOC_ISP_PDAF_PDAF_XGRAD_6_7_xgrad_7_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XGRAD_8_9_UNION
 结构说明  : PDAF_XGRAD_8_9 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_8  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 8. 
                                                    [Note]: x_grad_8 must be equal to 2**15 / x_sect_size_8[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_9  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 9. 
                                                    [Note]: x_grad_9 must be equal to 2**15 / x_sect_size_9[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XGRAD_8_9_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XGRAD_8_9_xgrad_8_START   (0)
#define SOC_ISP_PDAF_PDAF_XGRAD_8_9_xgrad_8_END     (11)
#define SOC_ISP_PDAF_PDAF_XGRAD_8_9_xgrad_9_START   (16)
#define SOC_ISP_PDAF_PDAF_XGRAD_8_9_xgrad_9_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XGRAD_10_UNION
 结构说明  : PDAF_XGRAD_10 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_10 : 12; /* bit[0-11] : factor for x-gradient calculation of sector 10. 
                                                    [Note]: x_grad_10 must be equal to 2**15 / x_sect_size_10[end] */
        unsigned int  reserved : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XGRAD_10_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XGRAD_10_xgrad_10_START  (0)
#define SOC_ISP_PDAF_PDAF_XGRAD_10_xgrad_10_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YGRAD_0_1_UNION
 结构说明  : PDAF_YGRAD_0_1 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_0  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 0.
                                                    [Note]: y_grad_0 must be equal to 2**15 / y_sect_size_0[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_1  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 1. 
                                                    [Note]: y_grad_1 must be equal to 2**15 / y_sect_size_1[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_YGRAD_0_1_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YGRAD_0_1_ygrad_0_START   (0)
#define SOC_ISP_PDAF_PDAF_YGRAD_0_1_ygrad_0_END     (11)
#define SOC_ISP_PDAF_PDAF_YGRAD_0_1_ygrad_1_START   (16)
#define SOC_ISP_PDAF_PDAF_YGRAD_0_1_ygrad_1_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YGRAD_2_3_UNION
 结构说明  : PDAF_YGRAD_2_3 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_2  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 2. 
                                                    [Note]: y_grad_2 must be equal to 2**15 / y_sect_size_2[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_3  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 3. 
                                                    [Note]: y_grad_3 must be equal to 2**15 / y_sect_size_3[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_YGRAD_2_3_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YGRAD_2_3_ygrad_2_START   (0)
#define SOC_ISP_PDAF_PDAF_YGRAD_2_3_ygrad_2_END     (11)
#define SOC_ISP_PDAF_PDAF_YGRAD_2_3_ygrad_3_START   (16)
#define SOC_ISP_PDAF_PDAF_YGRAD_2_3_ygrad_3_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YGRAD_4_5_UNION
 结构说明  : PDAF_YGRAD_4_5 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_4  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 4. 
                                                    [Note]: y_grad_4 must be equal to 2**15 / y_sect_size_4[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_5  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 5. 
                                                    [Note]: y_grad_5 must be equal to 2**15 / y_sect_size_5[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_YGRAD_4_5_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YGRAD_4_5_ygrad_4_START   (0)
#define SOC_ISP_PDAF_PDAF_YGRAD_4_5_ygrad_4_END     (11)
#define SOC_ISP_PDAF_PDAF_YGRAD_4_5_ygrad_5_START   (16)
#define SOC_ISP_PDAF_PDAF_YGRAD_4_5_ygrad_5_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YGRAD_6_7_UNION
 结构说明  : PDAF_YGRAD_6_7 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_6  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 6. 
                                                    [Note]: y_grad_6 must be equal to 2**15 / y_sect_size_6[end] */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_7  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 7. 
                                                    [Note]: y_grad_7 must be equal to 2**15 / y_sect_size_7[end] */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_YGRAD_6_7_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YGRAD_6_7_ygrad_6_START   (0)
#define SOC_ISP_PDAF_PDAF_YGRAD_6_7_ygrad_6_END     (11)
#define SOC_ISP_PDAF_PDAF_YGRAD_6_7_ygrad_7_START   (16)
#define SOC_ISP_PDAF_PDAF_YGRAD_6_7_ygrad_7_END     (27)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XSIZE_0_1_UNION
 结构说明  : PDAF_XSIZE_0_1 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_0 : 10; /* bit[0-9]  : sector size in x-direction. 
                                                         [Note]:The sector size in x-direction must be greater than 12 pixels.
                                                         The sector size must be even number[end] */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_1 : 10; /* bit[16-25]: please refer to x_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XSIZE_0_1_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XSIZE_0_1_x_sect_size_0_START  (0)
#define SOC_ISP_PDAF_PDAF_XSIZE_0_1_x_sect_size_0_END    (9)
#define SOC_ISP_PDAF_PDAF_XSIZE_0_1_x_sect_size_1_START  (16)
#define SOC_ISP_PDAF_PDAF_XSIZE_0_1_x_sect_size_1_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XSIZE_2_3_UNION
 结构说明  : PDAF_XSIZE_2_3 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_2 : 10; /* bit[0-9]  : please refer to x_sec_size_0 description */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_3 : 10; /* bit[16-25]: please refer to x_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XSIZE_2_3_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XSIZE_2_3_x_sect_size_2_START  (0)
#define SOC_ISP_PDAF_PDAF_XSIZE_2_3_x_sect_size_2_END    (9)
#define SOC_ISP_PDAF_PDAF_XSIZE_2_3_x_sect_size_3_START  (16)
#define SOC_ISP_PDAF_PDAF_XSIZE_2_3_x_sect_size_3_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XSIZE_4_5_UNION
 结构说明  : PDAF_XSIZE_4_5 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_4 : 10; /* bit[0-9]  : please refer to x_sec_size_0 description */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_5 : 10; /* bit[16-25]: please refer to x_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XSIZE_4_5_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XSIZE_4_5_x_sect_size_4_START  (0)
#define SOC_ISP_PDAF_PDAF_XSIZE_4_5_x_sect_size_4_END    (9)
#define SOC_ISP_PDAF_PDAF_XSIZE_4_5_x_sect_size_5_START  (16)
#define SOC_ISP_PDAF_PDAF_XSIZE_4_5_x_sect_size_5_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XSIZE_6_7_UNION
 结构说明  : PDAF_XSIZE_6_7 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_6 : 10; /* bit[0-9]  : please refer to x_sec_size_0 description */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_7 : 10; /* bit[16-25]: please refer to x_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XSIZE_6_7_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XSIZE_6_7_x_sect_size_6_START  (0)
#define SOC_ISP_PDAF_PDAF_XSIZE_6_7_x_sect_size_6_END    (9)
#define SOC_ISP_PDAF_PDAF_XSIZE_6_7_x_sect_size_7_START  (16)
#define SOC_ISP_PDAF_PDAF_XSIZE_6_7_x_sect_size_7_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XSIZE_8_9_UNION
 结构说明  : PDAF_XSIZE_8_9 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_8 : 10; /* bit[0-9]  : please refer to x_sec_size_0 description */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_9 : 10; /* bit[16-25]: please refer to x_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XSIZE_8_9_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XSIZE_8_9_x_sect_size_8_START  (0)
#define SOC_ISP_PDAF_PDAF_XSIZE_8_9_x_sect_size_8_END    (9)
#define SOC_ISP_PDAF_PDAF_XSIZE_8_9_x_sect_size_9_START  (16)
#define SOC_ISP_PDAF_PDAF_XSIZE_8_9_x_sect_size_9_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_XSIZE_10_UNION
 结构说明  : PDAF_XSIZE_10 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_10 : 10; /* bit[0-9]  : please refer to x_sec_size_0 description */
        unsigned int  reserved       : 22; /* bit[10-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_XSIZE_10_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_XSIZE_10_x_sect_size_10_START  (0)
#define SOC_ISP_PDAF_PDAF_XSIZE_10_x_sect_size_10_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YSIZE_0_1_UNION
 结构说明  : PDAF_YSIZE_0_1 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_0 : 10; /* bit[0-9]  : sector size in y-direction. 
                                                         [Note]:minimum sector size is 8 in y direction.[end]
                                                         The sector size should be an even number to avoid FW complexity */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  y_sect_size_1 : 10; /* bit[16-25]: please refer to y_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_PDAF_PDAF_YSIZE_0_1_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YSIZE_0_1_y_sect_size_0_START  (0)
#define SOC_ISP_PDAF_PDAF_YSIZE_0_1_y_sect_size_0_END    (9)
#define SOC_ISP_PDAF_PDAF_YSIZE_0_1_y_sect_size_1_START  (16)
#define SOC_ISP_PDAF_PDAF_YSIZE_0_1_y_sect_size_1_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YSIZE_2_3_UNION
 结构说明  : PDAF_YSIZE_2_3 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_2 : 10; /* bit[0-9]  : please refer to y_sec_size_0 description */
        unsigned int  reserved_0    : 6;  /* bit[10-15]:  */
        unsigned int  y_sect_size_3 : 10; /* bit[16-25]: please refer to y_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_YSIZE_2_3_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YSIZE_2_3_y_sect_size_2_START  (0)
#define SOC_ISP_PDAF_PDAF_YSIZE_2_3_y_sect_size_2_END    (9)
#define SOC_ISP_PDAF_PDAF_YSIZE_2_3_y_sect_size_3_START  (16)
#define SOC_ISP_PDAF_PDAF_YSIZE_2_3_y_sect_size_3_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YSIZE_4_5_UNION
 结构说明  : PDAF_YSIZE_4_5 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_4 : 10; /* bit[0-9]  : please refer to y_sec_size_0 description */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  y_sect_size_5 : 10; /* bit[16-25]: please refer to y_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_YSIZE_4_5_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YSIZE_4_5_y_sect_size_4_START  (0)
#define SOC_ISP_PDAF_PDAF_YSIZE_4_5_y_sect_size_4_END    (9)
#define SOC_ISP_PDAF_PDAF_YSIZE_4_5_y_sect_size_5_START  (16)
#define SOC_ISP_PDAF_PDAF_YSIZE_4_5_y_sect_size_5_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_YSIZE_6_7_UNION
 结构说明  : PDAF_YSIZE_6_7 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_6 : 10; /* bit[0-9]  : please refer to y_sec_size_0 description */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  y_sect_size_7 : 10; /* bit[16-25]: please refer to y_sec_size_0 description */
        unsigned int  reserved_1    : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_YSIZE_6_7_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_YSIZE_6_7_y_sect_size_6_START  (0)
#define SOC_ISP_PDAF_PDAF_YSIZE_6_7_y_sect_size_6_END    (9)
#define SOC_ISP_PDAF_PDAF_YSIZE_6_7_y_sect_size_7_START  (16)
#define SOC_ISP_PDAF_PDAF_YSIZE_6_7_y_sect_size_7_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_UNION
 结构说明  : PDAF_IMAGE_BLOCK_OFFSET 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: Image location offset in the block that includes the upper left corner of the image
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_start_offset : 10; /* bit[0-9]  : Horizontal Offset from the left side of the block that includes the left side of the processed image to the left side of the processed image
                                                          [Note] the offset cannot be greater or equal to the block width where is located the image start and shall be even number [end] */
        unsigned int  reserved_0     : 6;  /* bit[10-15]:  */
        unsigned int  y_start_offset : 10; /* bit[16-25]: Vertical Offset from the top of the block that includes the top of the processed image to the top of the processed image
                                                          [Note] the offset cannot be greater or equal to the block height where is located the image start [end] */
        unsigned int  reserved_1     : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_x_start_offset_START  (0)
#define SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_x_start_offset_END    (9)
#define SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_y_start_offset_START  (16)
#define SOC_ISP_PDAF_PDAF_IMAGE_BLOCK_OFFSET_y_start_offset_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_UNION
 结构说明  : PDAF_START_BLOCK_LOC 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: Image location offset in the block that includes the upper left corner of the image
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_start_block : 5;  /* bit[0-4]  : Horizontal start block location in the grid in pixel [0:21]
                                                         [note] note that the image can not be outside of the grid [end] */
        unsigned int  reserved_0    : 11; /* bit[5-15] :  */
        unsigned int  y_start_block : 4;  /* bit[16-19]: Vertical start block location in the grid in pixel [0:15]
                                                         [note] note that the image can not be outside of the grid [end] */
        unsigned int  reserved_1    : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_x_start_block_START  (0)
#define SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_x_start_block_END    (4)
#define SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_y_start_block_START  (16)
#define SOC_ISP_PDAF_PDAF_START_BLOCK_LOC_y_start_block_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_CFG_UNION
 结构说明  : PDAF_CFG 寄存器结构定义。地址偏移量:0x100，初值:0x00000100，宽度:32
 寄存器说明: Global PDAF configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdaf_vsize      : 8;  /* bit[0-7]  : Vertical size of the PDAF kernel:
                                                           0: 1 line
                                                           ..
                                                           255: 256 lines */
        unsigned int  pdaf_hsize      : 6;  /* bit[8-13] : Horizontal size of the PDAF kernel.
                                                           0: 1 pixel
                                                           ..
                                                           63: 64 pixels
                                                           [note] pdaf_hsize shall be configured to be an even number of pixels, so allowed configured values are 1,3,5 …,63[end] */
        unsigned int  reserved        : 16; /* bit[14-29]:  */
        unsigned int  pdaf_lut_select : 1;  /* bit[30]   : select bit useful in 2 LUT mode 
                                                           0: next active tables set is RGr
                                                           1: next active tables set is GbB
                                                           Table selection is object of a shadowing mechnism.
                                                           Next value is reflected in this register.
                                                           The current status is visible at PDAF_STATUS::pdaf_active_table.
                                                           It is SW decision to notify which LUT to use, same LUTs can be used for several frames. */
        unsigned int  pdaf_lut_cfg    : 1;  /* bit[31]   : LUT configuration mode
                                                           0: 2 LUTs are used at a time: RGr used by the hardware when pdaf_lut_select=0, GbB used by the hardware when pdaf_lut_select=1. This mode is used to shadow the content of the LUT (SONY/OVT support)
                                                           1: the 4 available LUTs are used (RGrGbB pattern) - LUT Shadowing is not possible in this mode, but still SW can modify the content of the memories at any time (Opened configuration for more advanced corrections) */
    } reg;
} SOC_ISP_PDAF_PDAF_CFG_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_vsize_START       (0)
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_vsize_END         (7)
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_hsize_START       (8)
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_hsize_END         (13)
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_lut_select_START  (30)
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_lut_select_END    (30)
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_lut_cfg_START     (31)
#define SOC_ISP_PDAF_PDAF_CFG_pdaf_lut_cfg_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_SATURATION_CFG_UNION
 结构说明  : PDAF_SATURATION_CFG 寄存器结构定义。地址偏移量:0x104，初值:0x00100010，宽度:32
 寄存器说明: Configuration to use when mode=0x2 (Threshold based)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdaf_saturation_threshold_0 : 14; /* bit[0-13] : Threshold to be used when threshold 0 method is required */
        unsigned int  reserved_0                  : 2;  /* bit[14-15]:  */
        unsigned int  pdaf_saturation_threshold_1 : 14; /* bit[16-29]: Threshold to be used when threshold 1 method is required */
        unsigned int  reserved_1                  : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_SATURATION_CFG_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_SATURATION_CFG_pdaf_saturation_threshold_0_START  (0)
#define SOC_ISP_PDAF_PDAF_SATURATION_CFG_pdaf_saturation_threshold_0_END    (13)
#define SOC_ISP_PDAF_PDAF_SATURATION_CFG_pdaf_saturation_threshold_1_START  (16)
#define SOC_ISP_PDAF_PDAF_SATURATION_CFG_pdaf_saturation_threshold_1_END    (29)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_ROI_H_UNION
 结构说明  : PDAF_ROI_H 寄存器结构定义。地址偏移量:0x108，初值:0x00010000，宽度:32
 寄存器说明: PDAF Horizontal Region of interest
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdaf_ihleft  : 13; /* bit[0-12] : Indicate position of first pixel on the left for the region of interest window.
                                                        Value 0 is the first pixel of the line 
                                                        [note] value can only be even number [end] */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  pdaf_ihright : 13; /* bit[16-28]: Indicate position of last pixel on the right for the region of interest window.
                                                        [note] value can only be odd number, and shall be greater than pdaf_ihleft [end] */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_ROI_H_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_ROI_H_pdaf_ihleft_START   (0)
#define SOC_ISP_PDAF_PDAF_ROI_H_pdaf_ihleft_END     (12)
#define SOC_ISP_PDAF_PDAF_ROI_H_pdaf_ihright_START  (16)
#define SOC_ISP_PDAF_PDAF_ROI_H_pdaf_ihright_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_ROI_V_UNION
 结构说明  : PDAF_ROI_V 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: PDAF Vertical Region of interest
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdaf_ivtop    : 13; /* bit[0-12] : indicates position of first line on the top for the region of interest window. 
                                                         Value 0 is the first line of the frame
                                                         [note] it is assumed that the PDAF module receives an even number of lines. [end] */
        unsigned int  reserved_0    : 3;  /* bit[13-15]:  */
        unsigned int  pdaf_ivbottom : 13; /* bit[16-28]: indicates position of last line on the bottom for the region of interest window. 
                                                         [note] value shall be greater or equal than pdaf_ivtop [end] */
        unsigned int  reserved_1    : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_ROI_V_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_ROI_V_pdaf_ivtop_START     (0)
#define SOC_ISP_PDAF_PDAF_ROI_V_pdaf_ivtop_END       (12)
#define SOC_ISP_PDAF_PDAF_ROI_V_pdaf_ivbottom_START  (16)
#define SOC_ISP_PDAF_PDAF_ROI_V_pdaf_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_LOCATION_UNION
 结构说明  : PDAF_LOCATION 寄存器结构定义。地址偏移量:0x110+0x4*(PP_location_Range)，初值:0x000000FF，宽度:32
 寄存器说明: PP location
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdaf_vpos       : 8;  /* bit[0-7]  : Vertical position of the pixel to correct */
        unsigned int  pdaf_hpos       : 6;  /* bit[8-13] : Horizontal position of the pixel to correct */
        unsigned int  reserved_0      : 2;  /* bit[14-15]:  */
        unsigned int  pdaf_saturation : 2;  /* bit[16-17]: PP pixel saturation to apply. This modification is done after the PP correction defined into pdaf_correction register.
                                                           0: no correction
                                                           1: saturation threshold 0 method used
                                                           2: saturation threshold 1 method used
                                                           3: NA
                                                           [note] This register does not impact the video port 1 since saturation is not possible on this output [end] */
        unsigned int  pdaf_correction : 3;  /* bit[18-20]: PP pixel correction to apply when in LUT mode (impacts video port 1 and 2)
                                                           0: no correction
                                                           1: correction based on previous value provided by PDAF (HW will use the next value if this is defined on the first 2 pixels of the line)
                                                           2: correction based on current value provided by PDAF
                                                           3: correction based on next value provided by PDAF (HW will use the previous value if this is defined on the last 2 pixels of the line)
                                                           4: interpolation method to be applied between left and right pixels (this method can not be used if the pixel is one of the 2 first or the 2 last pixel of the line, on these cases, the pixels are just copied since interpolation is not possible)
                                                           5-7: NA */
        unsigned int  reserved_1      : 11; /* bit[21-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_LOCATION_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_vpos_START        (0)
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_vpos_END          (7)
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_hpos_START        (8)
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_hpos_END          (13)
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_saturation_START  (16)
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_saturation_END    (17)
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_correction_START  (18)
#define SOC_ISP_PDAF_PDAF_LOCATION_pdaf_correction_END    (20)


/*****************************************************************************
 结构名    : SOC_ISP_PDAF_PDAF_STATUS_UNION
 结构说明  : PDAF_STATUS 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: pdaf status
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdaf_active_table : 1;  /* bit[0]   : This gives information on the current LUT used by the hardware available in any mode of operation, SW know which one can be reconfigured.
                                                            0: currently active tables are RGr
                                                            1: currently active tables are GbB */
        unsigned int  reserved          : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_PDAF_PDAF_STATUS_UNION;
#endif
#define SOC_ISP_PDAF_PDAF_STATUS_pdaf_active_table_START  (0)
#define SOC_ISP_PDAF_PDAF_STATUS_pdaf_active_table_END    (0)






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

#endif /* end of soc_isp_pdaf_interface.h */
