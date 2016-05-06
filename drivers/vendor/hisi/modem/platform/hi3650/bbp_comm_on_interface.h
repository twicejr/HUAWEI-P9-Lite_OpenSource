/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_comm_on_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-10-30 15:35:10
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月30日
    作    者   : p00277817
    修改内容   : 从《K3V5 MODEM寄存器手册_COMM_ON.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_COMM_ON_INTERFACE_H__
#define __BBP_COMM_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/2) register_define_afc_mix
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      0，表示配置AFC选择PDM输出；
             1，表示配置选择PWM输出
   UNION结构:  BBPCOMM_AFC_PWM_SEL_MIX_UNION */
#define BBPCOMM_AFC_PWM_SEL_MIX_ADDR                  (SOC_BBP_COMM_ON_BASE_ADDR + 0x1000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1，表示配置AFC使能；
             0，表示配置AFC不使能
   UNION结构:  BBPCOMM_AFC_EN_MIX_UNION */
#define BBPCOMM_AFC_EN_MIX_ADDR                       (SOC_BBP_COMM_ON_BASE_ADDR + 0x1004)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   AFC配置值
   UNION结构:  BBPCOMM_AFC_CFG_WIDTH_MIX_UNION */
#define BBPCOMM_AFC_CFG_WIDTH_MIX_ADDR                (SOC_BBP_COMM_ON_BASE_ADDR + 0x1008)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1，表示选择配置AFC值
             0，表示选择BBP产生的AFC值
   UNION结构:  BBPCOMM_AFC_CFG_SEL_MIX_UNION */
#define BBPCOMM_AFC_CFG_SEL_MIX_ADDR                  (SOC_BBP_COMM_ON_BASE_ADDR + 0x100C)



/***======================================================================***
                     (2/2) register_define_afc_mix_ch1
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      0，表示配置AFC选择PDM输出；
             1，表示配置选择PWM输出
   UNION结构:  BBPCOMM_AFC_PWM_SEL_MIX_CH1_UNION */
#define BBPCOMM_AFC_PWM_SEL_MIX_CH1_ADDR              (SOC_BBP_COMM_ON_BASE_ADDR + 0x1200)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1，表示配置AFC使能；
             0，表示配置AFC不使能
   UNION结构:  BBPCOMM_AFC_EN_MIX_CH1_UNION */
#define BBPCOMM_AFC_EN_MIX_CH1_ADDR                   (SOC_BBP_COMM_ON_BASE_ADDR + 0x1204)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   AFC配置值
   UNION结构:  BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_UNION */
#define BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_ADDR            (SOC_BBP_COMM_ON_BASE_ADDR + 0x1208)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1，表示选择配置AFC值
             0，表示选择BBP产生的AFC值
   UNION结构:  BBPCOMM_AFC_CFG_SEL_MIX_CH1_UNION */
#define BBPCOMM_AFC_CFG_SEL_MIX_CH1_ADDR              (SOC_BBP_COMM_ON_BASE_ADDR + 0x120C)





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

/***======================================================================***
                     (1/2) register_define_afc_mix
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_AFC_PWM_SEL_MIX_UNION
 结构说明  : AFC_PWM_SEL_MIX 寄存器结构定义。地址偏移量:0x00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_pwm_sel_mix_reg;
    struct
    {
        unsigned long  afc_pwm_sel : 1;  /* bit[0]   : 0，表示配置AFC选择PDM输出；
                                                       1，表示配置选择PWM输出 */
        unsigned long  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_AFC_PWM_SEL_MIX_UNION;
#define BBPCOMM_AFC_PWM_SEL_MIX_afc_pwm_sel_START  (0)
#define BBPCOMM_AFC_PWM_SEL_MIX_afc_pwm_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_EN_MIX_UNION
 结构说明  : AFC_EN_MIX 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_en_mix_reg;
    struct
    {
        unsigned long  afc_en   : 1;  /* bit[0]   : 1，表示配置AFC使能；
                                                    0，表示配置AFC不使能 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_AFC_EN_MIX_UNION;
#define BBPCOMM_AFC_EN_MIX_afc_en_START    (0)
#define BBPCOMM_AFC_EN_MIX_afc_en_END      (0)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CFG_WIDTH_MIX_UNION
 结构说明  : AFC_CFG_WIDTH_MIX 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_width_mix_reg;
    struct
    {
        unsigned long  afc_cfg_width : 12; /* bit[0-11] : AFC配置值 */
        unsigned long  reserved      : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CFG_WIDTH_MIX_UNION;
#define BBPCOMM_AFC_CFG_WIDTH_MIX_afc_cfg_width_START  (0)
#define BBPCOMM_AFC_CFG_WIDTH_MIX_afc_cfg_width_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CFG_SEL_MIX_UNION
 结构说明  : AFC_CFG_SEL_MIX 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_sel_mix_reg;
    struct
    {
        unsigned long  afc_cfg_sel : 1;  /* bit[0]   : 1，表示选择配置AFC值
                                                       0，表示选择BBP产生的AFC值 */
        unsigned long  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CFG_SEL_MIX_UNION;
#define BBPCOMM_AFC_CFG_SEL_MIX_afc_cfg_sel_START  (0)
#define BBPCOMM_AFC_CFG_SEL_MIX_afc_cfg_sel_END    (0)


/***======================================================================***
                     (2/2) register_define_afc_mix_ch1
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_AFC_PWM_SEL_MIX_CH1_UNION
 结构说明  : AFC_PWM_SEL_MIX_CH1 寄存器结构定义。地址偏移量:0x00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_pwm_sel_mix_ch1_reg;
    struct
    {
        unsigned long  afc_pwm_sel_ch1 : 1;  /* bit[0]   : 0，表示配置AFC选择PDM输出；
                                                           1，表示配置选择PWM输出 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_AFC_PWM_SEL_MIX_CH1_UNION;
#define BBPCOMM_AFC_PWM_SEL_MIX_CH1_afc_pwm_sel_ch1_START  (0)
#define BBPCOMM_AFC_PWM_SEL_MIX_CH1_afc_pwm_sel_ch1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_EN_MIX_CH1_UNION
 结构说明  : AFC_EN_MIX_CH1 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_en_mix_ch1_reg;
    struct
    {
        unsigned long  afc_en_ch1 : 1;  /* bit[0]   : 1，表示配置AFC使能；
                                                      0，表示配置AFC不使能 */
        unsigned long  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_AFC_EN_MIX_CH1_UNION;
#define BBPCOMM_AFC_EN_MIX_CH1_afc_en_ch1_START  (0)
#define BBPCOMM_AFC_EN_MIX_CH1_afc_en_ch1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_UNION
 结构说明  : AFC_CFG_WIDTH_MIX_CH1 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_width_mix_ch1_reg;
    struct
    {
        unsigned long  afc_cfg_width_ch1 : 12; /* bit[0-11] : AFC配置值 */
        unsigned long  reserved          : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_UNION;
#define BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_afc_cfg_width_ch1_START  (0)
#define BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_afc_cfg_width_ch1_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CFG_SEL_MIX_CH1_UNION
 结构说明  : AFC_CFG_SEL_MIX_CH1 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_sel_mix_ch1_reg;
    struct
    {
        unsigned long  afc_cfg_sel_ch1 : 1;  /* bit[0]   : 1，表示选择配置AFC值
                                                           0，表示选择BBP产生的AFC值 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CFG_SEL_MIX_CH1_UNION;
#define BBPCOMM_AFC_CFG_SEL_MIX_CH1_afc_cfg_sel_ch1_START  (0)
#define BBPCOMM_AFC_CFG_SEL_MIX_CH1_afc_cfg_sel_ch1_END    (0)




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

#endif /* end of bbp_comm_on_interface.h */
