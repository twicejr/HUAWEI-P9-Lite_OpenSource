/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_hkadc_ssi_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:46:09
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_HKADC_SSI.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_HKADC_SSI_INTERFACE_H__
#define __SOC_HKADC_SSI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* 寄存器说明：HKADC启动配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_START_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_START_ADDR(base)      ((base) + (0x0000))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_CFG_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_CFG_ADDR(base)        ((base) + (0x0004))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_WR_NUM_UNION */
#define SOC_HKADC_SSI_HKADC_WR_NUM_ADDR(base)         ((base) + (0x0008))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_ADDR(base)  ((base) + (0x000C))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_UNION */
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_ADDR(base) ((base) + (0x0010))

/* 寄存器说明：HKADC超时上报。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_UNION */
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_ADDR(base)    ((base) + (0x0018))

/* 寄存器说明：HKADC启动清除上报。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_START_CLR_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_ADDR(base)  ((base) + (0x001C))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_WR01_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR01_DATA_ADDR(base)      ((base) + (0x0020))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_WR23_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR23_DATA_ADDR(base)      ((base) + (0x0024))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_WR45_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR45_DATA_ADDR(base)      ((base) + (0x0028))

/* 寄存器说明：HKADC参数配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_WR67_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR67_DATA_ADDR(base)      ((base) + (0x002C))

/* 寄存器说明：HKADC延迟配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DELAY01_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY01_ADDR(base)        ((base) + (0x0030))

/* 寄存器说明：HKADC延迟配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DELAY23_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY23_ADDR(base)        ((base) + (0x0034))

/* 寄存器说明：HKADC延迟配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DELAY45_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY45_ADDR(base)        ((base) + (0x0038))

/* 寄存器说明：HKADC延迟配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DELAY6_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY6_ADDR(base)         ((base) + (0x003C))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_ADDR(base)   ((base) + (0x0040))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_ADDR(base)   ((base) + (0x0044))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_ADDR(base)   ((base) + (0x0048))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_ADDR(base)   ((base) + (0x004C))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_ADDR(base)   ((base) + (0x0050))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_ADDR(base)   ((base) + (0x0054))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_ADDR(base)   ((base) + (0x0058))

/* 寄存器说明：HKADC数据回读。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_ADDR(base)   ((base) + (0x005C))

/* 寄存器说明：HKADC操作间隔时间配置。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_OP_INTERVAL_UNION */
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_ADDR(base)    ((base) + (0x0060))

/* 寄存器说明：HKADC操作间隔时间功能使能。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_UNION */
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_ADDR(base) ((base) + (0x0064))

/* 寄存器说明：HKADC通道使能。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_CHANNEL_EN_UNION */
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_ADDR(base)     ((base) + (0x0068))

/* 寄存器说明：HKADC 测试数据。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_DBG_INFO_UNION */
#define SOC_HKADC_SSI_HKADC_DBG_INFO_ADDR(base)       ((base) + (0x00D0))

/* 寄存器说明：HKADC 操作完成原始中断。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_ADDR(base)  ((base) + (0x0100))

/* 寄存器说明：HKADC操作完成屏蔽后中断。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_ADDR(base)  ((base) + (0x0104))

/* 寄存器说明：HKADC操作完成中断清除。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_ADDR(base)  ((base) + (0x0108))

/* 寄存器说明：HKADC操作完成中断屏蔽。
   位域定义UNION结构:  SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_ADDR(base)  ((base) + (0x010C))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_START_UNION
 结构说明  : HKADC_DSP_START 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: HKADC启动配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_start : 1;  /* bit[0]   : 软件配置HKADC启动信号。
                                                    逻辑自清零。 */
        unsigned int  reserved  : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_START_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_START_dsp_start_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_START_dsp_start_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_CFG_UNION
 结构说明  : HKADC_DSP_CFG 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_cfg  : 20; /* bit[0-19] : master check 读同步位时间和SSI IP超时等待配置 */
        unsigned int  reserved : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_CFG_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_CFG_dsp_cfg_START   (0)
#define SOC_HKADC_SSI_HKADC_DSP_CFG_dsp_cfg_END     (19)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_WR_NUM_UNION
 结构说明  : HKADC_WR_NUM 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_wr_num : 3;  /* bit[0-2] : 软件HKADC寄存器个数 */
        unsigned int  reserved     : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_WR_NUM_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR_NUM_hkadc_wr_num_START  (0)
#define SOC_HKADC_SSI_HKADC_WR_NUM_hkadc_wr_num_END    (2)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_UNION
 结构说明  : HKADC_DSP_WAIT_TIME 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wait_time : 32; /* bit[0-31]: 软件HKADC请求超时时间长度 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_dsp_wait_time_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_dsp_wait_time_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_UNION
 结构说明  : HKADC_TIMEOUT_ERR_CLR 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  time_out_err_clr : 1;  /* bit[0]   : 超时清除 */
        unsigned int  reserved         : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_time_out_err_clr_START  (0)
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_time_out_err_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_UNION
 结构说明  : HKADC_TIMEOUT_ERR 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: HKADC超时上报。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeout_err : 1;  /* bit[0]   : 软件HKADC请求超时状态指示 */
        unsigned int  reserved    : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_timeout_err_START  (0)
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_timeout_err_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_START_CLR_UNION
 结构说明  : HKADC_DSP_START_CLR 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: HKADC启动清除上报。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_start_clr : 1;  /* bit[0]   : HKADC读写完成状态信号 */
        unsigned int  reserved      : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_START_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_dsp_start_clr_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_dsp_start_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_WR01_DATA_UNION
 结构说明  : HKADC_WR01_DATA 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr0_cfg : 16; /* bit[0-15] : HKADC寄存器读写配置：
                                                       15：读写指示：0：写，1：读
                                                       14-8：读写地址
                                                       7-0：读写数据 */
        unsigned int  dsp_wr1_cfg : 16; /* bit[16-31]: HKADC寄存器读写配置：
                                                       31：读写指示：0：写，1：读
                                                       30-24：读写地址
                                                       23-16：读写数据 */
    } reg;
} SOC_HKADC_SSI_HKADC_WR01_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr0_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr0_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr1_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr1_cfg_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_WR23_DATA_UNION
 结构说明  : HKADC_WR23_DATA 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr2_cfg : 16; /* bit[0-15] : HKADC寄存器读写配置：
                                                       15：读写指示：0：写，1：读
                                                       14-8：读写地址
                                                       7-0：读写数据 */
        unsigned int  dsp_wr3_cfg : 16; /* bit[16-31]: HKADC寄存器读写配置：
                                                       31：读写指示：0：写，1：读
                                                       30-24：读写地址
                                                       23-16：读写数据 */
    } reg;
} SOC_HKADC_SSI_HKADC_WR23_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr2_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr2_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr3_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr3_cfg_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_WR45_DATA_UNION
 结构说明  : HKADC_WR45_DATA 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr4_cfg : 16; /* bit[0-15] : HKADC寄存器读写配置：
                                                       15：读写指示：0：写，1：读
                                                       14-8：读写地址
                                                       7-0：读写数据 */
        unsigned int  dsp_wr5_cfg : 16; /* bit[16-31]: HKADC寄存器读写配置：
                                                       31：读写指示：0：写，1：读
                                                       30-24：读写地址
                                                       23-16：读写数据 */
    } reg;
} SOC_HKADC_SSI_HKADC_WR45_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr4_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr4_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr5_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr5_cfg_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_WR67_DATA_UNION
 结构说明  : HKADC_WR67_DATA 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: HKADC参数配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr6_cfg : 16; /* bit[0-15] : HKADC寄存器读写配置：
                                                       15：读写指示：0：写，1：读
                                                       14-8：读写地址
                                                       7-0：读写数据 */
        unsigned int  dsp_wr7_cfg : 16; /* bit[16-31]: HKADC寄存器读写配置：
                                                       31：读写指示：0：写，1：读
                                                       30-24：读写地址
                                                       23-16：读写数据 */
    } reg;
} SOC_HKADC_SSI_HKADC_WR67_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr6_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr6_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr7_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr7_cfg_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DELAY01_UNION
 结构说明  : HKADC_DELAY01 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: HKADC延迟配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay0 : 16; /* bit[0-15] : HKADC读写寄存器0和寄存器1之间操作间隔延时，单位1 cycle */
        unsigned int  dsp_delay1 : 16; /* bit[16-31]: HKADC读写寄存器1和寄存器2之间操作间隔延时，单位1 cycle */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY01_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay0_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay0_END    (15)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay1_START  (16)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay1_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DELAY23_UNION
 结构说明  : HKADC_DELAY23 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: HKADC延迟配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay2 : 16; /* bit[0-15] : HKADC读写寄存器2和寄存器3之间操作间隔延时，单位1 cycle */
        unsigned int  dsp_delay3 : 16; /* bit[16-31]: HKADC读写寄存器3和寄存器4之间操作间隔延时，单位1 cycle */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY23_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay2_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay2_END    (15)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay3_START  (16)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay3_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DELAY45_UNION
 结构说明  : HKADC_DELAY45 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: HKADC延迟配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay4 : 16; /* bit[0-15] : HKADC读写寄存器4和寄存器5之间操作间隔延时，单位1 cycle */
        unsigned int  dsp_delay5 : 16; /* bit[16-31]: HKADC读写寄存器5和寄存器6之间操作间隔延时，单位1 cycle */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY45_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay4_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay4_END    (15)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay5_START  (16)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay5_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DELAY6_UNION
 结构说明  : HKADC_DELAY6 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: HKADC延迟配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay6 : 16; /* bit[0-15] : HKADC读写寄存器6和寄存器7之间操作间隔延时，单位1 cycle */
        unsigned int  reserved   : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY6_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY6_dsp_delay6_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY6_dsp_delay6_END    (15)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_UNION
 结构说明  : HKADC_DSP_RD0_DATA 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd0_data : 32; /* bit[0-31]: HKADC寄存器0回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_dsp_rd0_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_dsp_rd0_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_UNION
 结构说明  : HKADC_DSP_RD1_DATA 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd1_data : 32; /* bit[0-31]: HKADC寄存器1回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_dsp_rd1_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_dsp_rd1_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_UNION
 结构说明  : HKADC_DSP_RD2_DATA 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd2_data : 32; /* bit[0-31]: HKADC寄存器2回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_dsp_rd2_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_dsp_rd2_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_UNION
 结构说明  : HKADC_DSP_RD3_DATA 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd3_data : 32; /* bit[0-31]: HKADC寄存器3回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_dsp_rd3_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_dsp_rd3_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_UNION
 结构说明  : HKADC_DSP_RD4_DATA 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd4_data : 32; /* bit[0-31]: HKADC寄存器4回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_dsp_rd4_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_dsp_rd4_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_UNION
 结构说明  : HKADC_DSP_RD5_DATA 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd5_data : 32; /* bit[0-31]: HKADC寄存器5回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_dsp_rd5_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_dsp_rd5_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_UNION
 结构说明  : HKADC_DSP_RD6_DATA 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd6_data : 32; /* bit[0-31]: HKADC寄存器6回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_dsp_rd6_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_dsp_rd6_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_UNION
 结构说明  : HKADC_DSP_RD7_DATA 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: HKADC数据回读。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd7_data : 32; /* bit[0-31]: HKADC寄存器7回读值 */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_dsp_rd7_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_dsp_rd7_data_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_OP_INTERVAL_UNION
 结构说明  : HKADC_OP_INTERVAL 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: HKADC操作间隔时间配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_op_interval : 32; /* bit[0-31]: HKADC软件操作间隔时间配置 */
    } reg;
} SOC_HKADC_SSI_HKADC_OP_INTERVAL_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_hkadc_op_interval_START  (0)
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_hkadc_op_interval_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_UNION
 结构说明  : HKADC_OP_INTERVAL_BYPASS 寄存器结构定义。地址偏移量:0x0064，初值:0x00000001，宽度:32
 寄存器说明: HKADC操作间隔时间功能使能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  op_interval_bypass_en : 1;  /* bit[0]   : op_interval功能bypass使能：
                                                                0：使用op_interval功能
                                                                1：bypass op_interval功能 */
        unsigned int  reserved              : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_op_interval_bypass_en_START  (0)
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_op_interval_bypass_en_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_CHANNEL_EN_UNION
 结构说明  : HKADC_CHANNEL_EN 寄存器结构定义。地址偏移量:0x0068，初值:0x00000007，宽度:32
 寄存器说明: HKADC通道使能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_channel_en_sft : 1;  /* bit[0]   : 软件通道使能（主要调试使用）：
                                                               0：关闭通道
                                                               1：打开通道 */
        unsigned int  hkadc_channel_en_hd0 : 1;  /* bit[1]   : 硬件channel0通道使能（主要调试使用）：
                                                               0：关闭通道
                                                               1：打开通道 */
        unsigned int  hkadc_channel_en_hd1 : 1;  /* bit[2]   : 硬件channel1通道使能（主要调试使用）：
                                                               0：关闭通道
                                                               1：打开通道 */
        unsigned int  reserved             : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_CHANNEL_EN_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_sft_START  (0)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_sft_END    (0)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd0_START  (1)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd0_END    (1)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd1_START  (2)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd1_END    (2)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_DBG_INFO_UNION
 结构说明  : HKADC_DBG_INFO 寄存器结构定义。地址偏移量:0x00D0，初值:0x00000000，宽度:32
 寄存器说明: HKADC 测试数据。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arb_info : 32; /* bit[0-31]: 状态信号组合的上报寄存器 */
    } reg;
} SOC_HKADC_SSI_HKADC_DBG_INFO_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DBG_INFO_arb_info_START  (0)
#define SOC_HKADC_SSI_HKADC_DBG_INFO_arb_info_END    (31)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_UNION
 结构说明  : HKADC_FINSH_RAW_INT 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: HKADC 操作完成原始中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_raw_int : 1;  /* bit[0]   : hkadc操作完成原始中断 */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_hkadc_finish_raw_int_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_hkadc_finish_raw_int_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_UNION
 结构说明  : HKADC_FINSH_MSK_INT 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: HKADC操作完成屏蔽后中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_msk_int : 1;  /* bit[0]   : hkadc操作完成屏蔽后中断 */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_hkadc_finish_msk_int_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_hkadc_finish_msk_int_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_UNION
 结构说明  : HKADC_FINSH_INT_CLR 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: HKADC操作完成中断清除。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_int_clr : 1;  /* bit[0]   : hkadc操作完成中断清除 */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_hkadc_finish_int_clr_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_hkadc_finish_int_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_UNION
 结构说明  : HKADC_FINSH_INT_MSK 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: HKADC操作完成中断屏蔽。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_int_msk : 1;  /* bit[0]   : hkadc操作完成中断屏蔽 */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_hkadc_finish_int_msk_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_hkadc_finish_int_msk_END    (0)






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

#endif /* end of soc_hkadc_ssi_interface.h */
