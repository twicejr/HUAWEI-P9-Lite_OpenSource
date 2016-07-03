

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_FRAME_MERGER_INTERFACE_H__
#define __SOC_ISP_FRAME_MERGER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) FRAME_MERGER
 ****************************************************************************/
/* 寄存器说明：Configuration register.
   位域定义UNION结构:  SOC_ISP_FRAME_MERGER_CFG_UNION */
#define SOC_ISP_FRAME_MERGER_CFG_ADDR(base)           ((base) + (0x0))

/* 寄存器说明：Debug control register.
   位域定义UNION结构:  SOC_ISP_FRAME_MERGER_DEBUG_CFG_UNION */
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_ADDR(base)     ((base) + (0x4))

/* 寄存器说明：Debug register.
   位域定义UNION结构:  SOC_ISP_FRAME_MERGER_DEBUG_UNION */
#define SOC_ISP_FRAME_MERGER_DEBUG_ADDR(base)         ((base) + (0x8))





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
                     (1/1) FRAME_MERGER
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_FRAME_MERGER_CFG_UNION
 结构说明  : CFG 寄存器结构定义。地址偏移量:0x0，初值:0x00000000，宽度:32
 寄存器说明: Configuration register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : Mode of Operation
                                                   0: normal
                                                   1: interleaved */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_FRAME_MERGER_CFG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_CFG_mode_START      (0)
#define SOC_ISP_FRAME_MERGER_CFG_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_ISP_FRAME_MERGER_DEBUG_CFG_UNION
 结构说明  : DEBUG_CFG 寄存器结构定义。地址偏移量:0x4，初值:0x00000000，宽度:32
 寄存器说明: Debug control register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fe2_fifo_peak_en : 1;  /* bit[0]   : enable the FE2 FIFO peak functionality */
        unsigned int  reserved         : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_FRAME_MERGER_DEBUG_CFG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_fe2_fifo_peak_en_START  (0)
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_fe2_fifo_peak_en_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_FRAME_MERGER_DEBUG_UNION
 结构说明  : DEBUG 寄存器结构定义。地址偏移量:0x8，初值:0x00000000，宽度:32
 寄存器说明: Debug register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fe2_fifo_peak         : 16; /* bit[0-15] : FE2 FIFO level peak */
        unsigned int  fe2_fsm_router        : 5;  /* bit[16-20]: FE2 router FSM state */
        unsigned int  fe2_fsm_pack          : 2;  /* bit[21-22]: FE2 pack FSM state */
        unsigned int  fe2_fsm_unpack        : 2;  /* bit[23-24]: FE2 unpack FSM state */
        unsigned int  fe2_fsm_pressure_mode : 1;  /* bit[25]   : FE2 pressure mode FSM state  */
        unsigned int  reserved              : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_FRAME_MERGER_DEBUG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fifo_peak_START          (0)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fifo_peak_END            (15)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_router_START         (16)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_router_END           (20)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pack_START           (21)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pack_END             (22)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_unpack_START         (23)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_unpack_END           (24)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pressure_mode_START  (25)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pressure_mode_END    (25)






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

#endif /* end of soc_isp_frame_merger_interface.h */
