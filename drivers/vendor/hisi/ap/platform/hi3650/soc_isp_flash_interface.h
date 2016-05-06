/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_flash_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:41
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_FLASH.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_FLASH_INTERFACE_H__
#define __SOC_ISP_FLASH_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/2) FLASH
 ****************************************************************************/
/* 寄存器说明：Flash command
   位域定义UNION结构:  SOC_ISP_FLASH_CMD_UNION */
#define SOC_ISP_FLASH_CMD_ADDR(base)                  ((base) + (0x0000))

/* 寄存器说明：Flash configuration
   位域定义UNION结构:  SOC_ISP_FLASH_CONFIG_UNION */
#define SOC_ISP_FLASH_CONFIG_ADDR(base)               ((base) + (0x0004))

/* 寄存器说明：Clock divider
   位域定义UNION结构:  SOC_ISP_FLASH_PREDIV_UNION */
#define SOC_ISP_FLASH_PREDIV_ADDR(base)               ((base) + (0x0008))

/* 寄存器说明：delay
   位域定义UNION结构:  SOC_ISP_FLASH_DELAY_UNION */
#define SOC_ISP_FLASH_DELAY_ADDR(base)                ((base) + (0x000C))

/* 寄存器说明：time
   位域定义UNION结构:  SOC_ISP_FLASH_TIME_UNION */
#define SOC_ISP_FLASH_TIME_ADDR(base)                 ((base) + (0x0010))

/* 寄存器说明：Maximum period
   位域定义UNION结构:  SOC_ISP_FLASH_MAXP_UNION */
#define SOC_ISP_FLASH_MAXP_ADDR(base)                 ((base) + (0x0014))



/****************************************************************************
                     (2/2) STATDIS
 ****************************************************************************/




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
                     (1/2) FLASH
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_FLASH_CMD_UNION
 结构说明  : CMD 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: Flash command
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prelight_on : 1;  /* bit[0]   : prelight on 
                                                      0: prelight is switched off at next trigger event 
                                                      1: prelight is switched on at next trigger event
                                                      Note: This is the command register for flash light and prelight activation. If the "rw" bits (e.g. "fl_cap_del") are re-programmed during operation, the following scheme shall be applied: i) prelight is active (prelight_on = 1 has been set before): Every write access to this register shall use prelight_on = 1 (to prevent undesired switch off of the prelight). ii) prelight is off: Every write access to this register shall use prelight_on = 0 (to prevent undesired switch on of the prelight). */
        unsigned int  flash_on    : 1;  /* bit[1]   : flash on 
                                                      0: no effect 
                                                      1: flash delay counter is started at next trigger event A capture event is signaled to the sensor interface block. */
        unsigned int  preflash_on : 1;  /* bit[2]   : preflash on 
                                                      0: no effect 
                                                      1: flash delay counter is started at next trigger event No capture event is signaled to the sensor interface block. */
        unsigned int  reserved    : 29; /* bit[3-31]: TBD */
    } reg;
} SOC_ISP_FLASH_CMD_UNION;
#endif
#define SOC_ISP_FLASH_CMD_prelight_on_START  (0)
#define SOC_ISP_FLASH_CMD_prelight_on_END    (0)
#define SOC_ISP_FLASH_CMD_flash_on_START     (1)
#define SOC_ISP_FLASH_CMD_flash_on_END       (1)
#define SOC_ISP_FLASH_CMD_preflash_on_START  (2)
#define SOC_ISP_FLASH_CMD_preflash_on_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_FLASH_CONFIG_UNION
 结构说明  : CONFIG 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: Flash configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prelight_mode : 1;  /* bit[0]   : prelight mode 
                                                        0: prelight is switched off at begin of flash 
                                                        1: prelight is switched off at end of flash */
        unsigned int  vs_in_edge    : 1;  /* bit[1]   : VSYNC edge /fl_trig
                                                        0: use negative edge of “vds_vsync” if generating a trigger event 
                                                        1: use positive edge of “vds_vsync” if generating a trigger event */
        unsigned int  fl_pol        : 1;  /* bit[2]   : polarity of flash related signals 
                                                        0: flash_trig, prelight_trig are high active 
                                                        1: flash_trig, prelight_trig are low active */
        unsigned int  fl_trig_sel   : 2;  /* bit[3-4] : trigger source for flash and prelight 
                                                        0: use “vds_vsync” from CSI2IF_A for trigger event (with evaluation of vs_in_edge) 
                                                        1: use “vds_vsync” from CSI2IF_B for trigger event (with evaluation of vs_in_edge) 
                                                        2: use “vds_vsync” from CSI2IF_C for trigger event (with evaluation of vs_in_edge) 
                                                        3: use “fl_trig” for trigger event (positive edge) */
        unsigned int  fl_cap_del    : 4;  /* bit[5-8] : capture delay frame number (0 to 15) to be captured after trigger event */
        unsigned int  reserved      : 23; /* bit[9-31]: TBD */
    } reg;
} SOC_ISP_FLASH_CONFIG_UNION;
#endif
#define SOC_ISP_FLASH_CONFIG_prelight_mode_START  (0)
#define SOC_ISP_FLASH_CONFIG_prelight_mode_END    (0)
#define SOC_ISP_FLASH_CONFIG_vs_in_edge_START     (1)
#define SOC_ISP_FLASH_CONFIG_vs_in_edge_END       (1)
#define SOC_ISP_FLASH_CONFIG_fl_pol_START         (2)
#define SOC_ISP_FLASH_CONFIG_fl_pol_END           (2)
#define SOC_ISP_FLASH_CONFIG_fl_trig_sel_START    (3)
#define SOC_ISP_FLASH_CONFIG_fl_trig_sel_END      (4)
#define SOC_ISP_FLASH_CONFIG_fl_cap_del_START     (5)
#define SOC_ISP_FLASH_CONFIG_fl_cap_del_END       (8)


/*****************************************************************************
 结构名    : SOC_ISP_FLASH_PREDIV_UNION
 结构说明  : PREDIV 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: Clock divider
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fl_pre_div : 14; /* bit[0-13] : pre-divider for flush/preflash counter */
        unsigned int  reserved   : 18; /* bit[14-31]: TBD */
    } reg;
} SOC_ISP_FLASH_PREDIV_UNION;
#endif
#define SOC_ISP_FLASH_PREDIV_fl_pre_div_START  (0)
#define SOC_ISP_FLASH_PREDIV_fl_pre_div_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_FLASH_DELAY_UNION
 结构说明  : DELAY 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: delay
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fl_delay : 18; /* bit[0-17] : counter value for flash/preflash delay
                                                     open_delay = (fl_delay + 1) * (fl_pre_div+1) / clk_isp 
                                                    fl_delay = (open_delay * clk_isp) / (fl_pre_div+1) - 1
                                                    Note: Example: 
                                                    fl_delay = (10s * 325MHz) / (16383+ 1) – 1 = 183105 */
        unsigned int  reserved : 14; /* bit[18-31]: TBD */
    } reg;
} SOC_ISP_FLASH_DELAY_UNION;
#endif
#define SOC_ISP_FLASH_DELAY_fl_delay_START  (0)
#define SOC_ISP_FLASH_DELAY_fl_delay_END    (17)


/*****************************************************************************
 结构名    : SOC_ISP_FLASH_TIME_UNION
 结构说明  : TIME 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: time
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fl_time  : 8;  /* bit[0-7] : counter value for flash/preflash time 
                                                   open_time = (fl_time + 1) * (fl_pre_div+1) / clk_isp 
                                                   fl_time = (open_time * clk_isp) / (fl_pre_div+1) - 1
                                                   Note: Example: fl_time = (500ms * 325MHz) / (800 + 1) – 1 =202871 */
        unsigned int  reserved : 24; /* bit[8-31]: TBD */
    } reg;
} SOC_ISP_FLASH_TIME_UNION;
#endif
#define SOC_ISP_FLASH_TIME_fl_time_START   (0)
#define SOC_ISP_FLASH_TIME_fl_time_END     (7)


/*****************************************************************************
 结构名    : SOC_ISP_FLASH_MAXP_UNION
 结构说明  : MAXP 寄存器结构定义。地址偏移量:0x0014，初值:0x00000010，宽度:32
 寄存器说明: Maximum period
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fl_mawp  : 8;  /* bit[0-7] : maximum period value for flash or preflash max. 
                                                   flash/preflash period = 214 * (fl_maxp + 1) / clk_isp 
                                                   fl_maxp = (max_period * clk_isp) / 214 - 1 */
        unsigned int  reserved : 24; /* bit[8-31]: TBD */
    } reg;
} SOC_ISP_FLASH_MAXP_UNION;
#endif
#define SOC_ISP_FLASH_MAXP_fl_mawp_START   (0)
#define SOC_ISP_FLASH_MAXP_fl_mawp_END     (7)




/****************************************************************************
                     (2/2) STATDIS
 ****************************************************************************/




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

#endif /* end of soc_isp_flash_interface.h */
