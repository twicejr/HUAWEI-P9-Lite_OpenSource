

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_AWBGAIN_INTERFACE_H__
#define __SOC_ISP_AWBGAIN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) AWBGAIN
 ****************************************************************************/
/* 寄存器说明：Auto white balance gain green
   位域定义UNION结构:  SOC_ISP_AWBGAIN_AWBGAIN_GR_UNION */
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_ADDR(base)         ((base) + (0x0000))

/* 寄存器说明：Auto white balance properties
   位域定义UNION结构:  SOC_ISP_AWBGAIN_AWBGAIN_RB_UNION */
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_ADDR(base)         ((base) + (0x0004))





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
                     (1/1) AWBGAIN
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_AWBGAIN_AWBGAIN_GR_UNION
 结构说明  : AWBGAIN_GR 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: Auto white balance gain green
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awb_gain_gb : 12; /* bit[0-11] : gain value for green component in blue line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: reserved */
        unsigned int  awb_gain_gr : 12; /* bit[16-27]: gain value for green component in red line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_1  : 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_AWBGAIN_AWBGAIN_GR_UNION;
#endif
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gb_START  (0)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gb_END    (11)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gr_START  (16)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gr_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_AWBGAIN_AWBGAIN_RB_UNION
 结构说明  : AWBGAIN_RB 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: Auto white balance properties
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awb_gain_b : 12; /* bit[0-11] : gain value for green component in blue line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_0 : 4;  /* bit[12-15]: reserved */
        unsigned int  awb_gain_r : 12; /* bit[16-27]: gain value for green component in red line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_1 : 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_AWBGAIN_AWBGAIN_RB_UNION;
#endif
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_b_START  (0)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_b_END    (11)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_r_START  (16)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_r_END    (27)






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

#endif /* end of soc_isp_awbgain_interface.h */
