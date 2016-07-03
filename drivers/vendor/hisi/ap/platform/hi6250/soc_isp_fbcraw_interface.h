

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_FBCRAW_INTERFACE_H__
#define __SOC_ISP_FBCRAW_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) FBCRAW
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_FBCRAW_FBC_CFG1_UNION */
#define SOC_ISP_FBCRAW_FBC_CFG1_ADDR(base)            ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_FBCRAW_FBC_CFG2_UNION */
#define SOC_ISP_FBCRAW_FBC_CFG2_ADDR(base)            ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_FBCRAW_FBC_CFG3_UNION */
#define SOC_ISP_FBCRAW_FBC_CFG3_ADDR(base)            ((base) + (0x0008))





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
                     (1/1) FBCRAW
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_FBCRAW_FBC_CFG1_UNION
 结构说明  : FBC_CFG1 寄存器结构定义。地址偏移量:0x0000，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass       : 1;  /* bit[0-0]  : Bypass:
                                                        0: the module is active
                                                        1: the module is bypassed */
        unsigned int  reserved_0   : 1;  /* bit[1-1]  :  */
        unsigned int  pix_size     : 2;  /* bit[2-3]  : 0: 10bits
                                                        others: 12bits */
        unsigned int  reserved_1   : 4;  /* bit[4-7]  :  */
        unsigned int  extra_budget : 6;  /* bit[8-13] : encoding extra budget for full line (in D64) */
        unsigned int  reserved_2   : 2;  /* bit[14-15]:  */
        unsigned int  line_width   : 13; /* bit[16-28]: Line width must be even.
                                                        Line width-1
                                                        (max = 5360-1
                                                         min = 192 -1) */
        unsigned int  reserved_3   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_FBCRAW_FBC_CFG1_UNION;
#endif
#define SOC_ISP_FBCRAW_FBC_CFG1_bypass_START        (0)
#define SOC_ISP_FBCRAW_FBC_CFG1_bypass_END          (0)
#define SOC_ISP_FBCRAW_FBC_CFG1_pix_size_START      (2)
#define SOC_ISP_FBCRAW_FBC_CFG1_pix_size_END        (3)
#define SOC_ISP_FBCRAW_FBC_CFG1_extra_budget_START  (8)
#define SOC_ISP_FBCRAW_FBC_CFG1_extra_budget_END    (13)
#define SOC_ISP_FBCRAW_FBC_CFG1_line_width_START    (16)
#define SOC_ISP_FBCRAW_FBC_CFG1_line_width_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_FBCRAW_FBC_CFG2_UNION
 结构说明  : FBC_CFG2 寄存器结构定义。地址偏移量:0x0004，初值:0x00460020，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initqp    : 6;  /* bit[0-5]  : The initial QP used for the first segment, can be set in the FW. No need to change. */
        unsigned int  reserved_0: 10; /* bit[6-15] :  */
        unsigned int  bit_thres : 8;  /* bit[16-23]: Internal threshold, can be set in the FW. No need to change. */
        unsigned int  reserved_1: 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_FBCRAW_FBC_CFG2_UNION;
#endif
#define SOC_ISP_FBCRAW_FBC_CFG2_initqp_START     (0)
#define SOC_ISP_FBCRAW_FBC_CFG2_initqp_END       (5)
#define SOC_ISP_FBCRAW_FBC_CFG2_bit_thres_START  (16)
#define SOC_ISP_FBCRAW_FBC_CFG2_bit_thres_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_FBCRAW_FBC_CFG3_UNION
 结构说明  : FBC_CFG3 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  step_size      : 7;  /* bit[0-6]  : step size between RST markers (in number of segment = 64 pixels) and 0< step_size*64 <= line_width. */
        unsigned int  reserved_0     : 1;  /* bit[7]    :  */
        unsigned int  nb_rstmkr      : 6;  /* bit[8-13] : Number of RST marker.
                                                          Firmware must compute this parameter as follows: ceil ((line_width+1) / (step_size<<6))
                                                          MAX:
                                                          35 if supporting line up to 5360
                                                          21 if supporting line up to 2304 */
        unsigned int  reserved_1     : 2;  /* bit[14-15]:  */
        unsigned int  encoding_width : 13; /* bit[16-28]: Number of pixels to be encoded per RST Marker=encodingwidth +1.
                                                          Must be even and step_size*64 <= encoding_width+1 <= line_width+1. */
        unsigned int  reserved_2     : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_FBCRAW_FBC_CFG3_UNION;
#endif
#define SOC_ISP_FBCRAW_FBC_CFG3_step_size_START       (0)
#define SOC_ISP_FBCRAW_FBC_CFG3_step_size_END         (6)
#define SOC_ISP_FBCRAW_FBC_CFG3_nb_rstmkr_START       (8)
#define SOC_ISP_FBCRAW_FBC_CFG3_nb_rstmkr_END         (13)
#define SOC_ISP_FBCRAW_FBC_CFG3_encoding_width_START  (16)
#define SOC_ISP_FBCRAW_FBC_CFG3_encoding_width_END    (28)






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

#endif /* end of soc_isp_fbcraw_interface.h */
