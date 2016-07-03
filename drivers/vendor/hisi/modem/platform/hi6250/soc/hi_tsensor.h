/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_tsensor.h */
/* Version       : 2.0 */
/* Created       : 2013-06-28*/
/* Last Modified : */
/* Description   :  The C union definition file for the module tsensor*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_TSENSOR_H__
#define __HI_TSENSOR_H__

/*
 * Project: hi
 * Module : tsensor
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    tsensor 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_TEMP_EN_OFFSET                                 (0x0) /* Tsensor温度检测使能寄存器 */
#define    HI_TEMP_DIS_TIME_OFFSET                           (0x4) /* Tsensor温度检测去使能等待时间寄存器 */
#define    HI_TRIM0_OFFSET                                   (0x8) /* Tsensor温度校准寄存器1 */
#define    HI_TRIM1_OFFSET                                   (0xC) /* Tsensor温度校准寄存器2 */
#define    HI_TEMP_TH_OFFSET                                 (0x10) /* Tsensor温度报警门限寄存器 */
#define    HI_TEMP_B_TH_OFFSET                               (0x14) /* Tsensor温度回滞寄存器 */
#define    HI_TEMP_CONFIG_OFFSET                             (0x18) /* Tsensor模式配置寄存器 */
#define    HI_TEMP_RAWINT_OFFSET                             (0x1C) /* Tsensor原始中断寄存器 */
#define    HI_TEMP_MSKINT_OFFSET                             (0x20) /* Tsensor屏蔽中断寄存器 */
#define    HI_TEMP_STATINT_OFFSET                            (0x24) /* Tsensor中断状态寄存器 */
#define    HI_TEMP_OFFSET                                    (0x28) /* Tsensor温度检测结果寄存器 */
#define    HI_TEMP_TRIM_MODE_OFFSET                          (0x2C) /* Tsensor温度校验模式 */

/********************************************************************************/
/*    tsensor 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    temp_en                    : 1; /* [0..0] Tsensor温度采样使能寄存器：0：不使能1：使能 */
        unsigned int    reserved                   : 31; /* [31..1] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_EN_T;    /* Tsensor温度检测使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    temp_dis_time              : 8; /* [7..0] 等待时间为N个1Mhz周期。N表示此配置值。对接器件要求至少5us，所以默认值设为6。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_DIS_TIME_T;    /* Tsensor温度检测去使能等待时间寄存器 */

typedef union
{
    struct
    {
        unsigned int    local_sensor_trim          : 8; /* [7..0] ATE remote sensor4温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
        unsigned int    remote_sensor1_trim        : 8; /* [15..8] ATE remote sensor5温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
        unsigned int    remote_sensor2_trim        : 8; /* [23..16] ATE remote sensor6温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
        unsigned int    remote_sensor3_trim        : 8; /* [31..24] ATE remote sensor7温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
    } bits;
    unsigned int    u32;
}HI_TRIM0_T;    /* Tsensor温度校准寄存器1 */

typedef union
{
    struct
    {
        unsigned int    remote_sensor4_trim        : 8; /* [7..0] ATE local sensor温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
        unsigned int    remote_sensor5_trim        : 8; /* [15..8] ATE remote sensor1温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
        unsigned int    remote_sensor6_trim        : 8; /* [23..16] ATE remote sensor2温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
        unsigned int    remote_sensor7_trim        : 8; /* [31..24] ATE remote sensor3温度校准误差信息，最高位表示符号：1：采样温度减去校准误差0：采样温度加上校准误差 */
    } bits;
    unsigned int    u32;
}HI_TRIM1_T;    /* Tsensor温度校准寄存器2 */

typedef union
{
    struct
    {
        unsigned int    temp_0th                   : 8; /* [7..0] Tsensor温度报警门限0 */
        unsigned int    temp_1th                   : 8; /* [15..8] Tsensor温度报警门限1 */
        unsigned int    temp_2th                   : 8; /* [23..16] Tsensor温度报警门限2 */
        unsigned int    temp_3th                   : 8; /* [31..24] Tsensor温度报警门限3 */
    } bits;
    unsigned int    u32;
}HI_TEMP_TH_T;    /* Tsensor温度报警门限寄存器 */

typedef union
{
    struct
    {
        unsigned int    temp_b_th                  : 5; /* [4..0] Tsensor温度回滞门限 */
        unsigned int    reserved                   : 27; /* [31..5] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_B_TH_T;    /* Tsensor温度回滞寄存器 */

typedef union
{
    struct
    {
        unsigned int    ct_sel                     : 2; /* [1..0] 对于输入1M精准时钟情况下Tsensor HKADC转换时间选择：00-----0.768ms；01-----6.144ms；10-----49.152ms；11-----393.216ms； */
        unsigned int    test                       : 3; /* [4..2] Tsensor通道模式选择：000——选择LOCAL SENSOR的温度值001——选择REMOTE SENSOR1的温度值010——选择REMOTE SENSOR2的温度值011——选择REMOTE SENSOR3的温度值100——选择REMOTE SENSOR4的温度值101——选择REMOTE SENSOR5的温度值110——选择REMOTE SENSOR6的温度值111——选择REMOTE SENSOR7的温度值 */
        unsigned int    sample_mode                : 2; /* [6..5] Tsensor同一通道温度采样模式选择：00——多次采样最后一次值01——多次采样取最大值10——多次采样取均值11——多次采样取最小值 */
        unsigned int    sample_num                 : 3; /* [9..7] Tsensor同一通道采样次数选择，只支持2的N次方：1、2、4、8~128 */
        unsigned int    reserved                   : 22; /* [31..10] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_CONFIG_T;    /* Tsensor模式配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    temp_rawint                : 1; /* [0..0] Tsensor原始中断，写1清：1：有中断0：无中断 */
        unsigned int    reserved                   : 31; /* [31..1] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_RAWINT_T;    /* Tsensor原始中断寄存器 */

typedef union
{
    struct
    {
        unsigned int    temp_maskint               : 1; /* [0..0] Tsensor屏蔽中断使能：1：屏蔽中断0：不屏蔽 */
        unsigned int    reserved                   : 31; /* [31..1] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_MSKINT_T;    /* Tsensor屏蔽中断寄存器 */

typedef union
{
    struct
    {
        unsigned int    temp_statint               : 1; /* [0..0] Tsensor中断状态：1：有中断0：无中断 */
        unsigned int    reserved                   : 31; /* [31..1] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_STATINT_T;    /* Tsensor中断状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    temp                       : 8; /* [7..0] Tsensor温度检测结果寄存器8 Bits温度区间BIN码输出；00000000……-40℃；………………………00110011……-4℃；………………………01100111……44℃；………………………10101010……80℃；………………………11101110……128℃；………………………11111111……140℃；注：若供电无1.8V模拟电源但有0.9V，8bit输出为不定态 */
        unsigned int    reserved                   : 24; /* [31..8] 温度检测结果寄存器 */
    } bits;
    unsigned int    u32;
}HI_TEMP_T;    /* Tsensor温度检测结果寄存器 */

typedef union
{
    struct
    {
        unsigned int    temp_trim_mode             : 1; /* [0..0] Tsensor温度检验模式：0：软件校验1：控制器直接用二进制温度码校验 */
        unsigned int    reserved                   : 31; /* [31..1] 保留位 */
    } bits;
    unsigned int    u32;
}HI_TEMP_TRIM_MODE_T;    /* Tsensor温度校验模式 */


/********************************************************************************/
/*    tsensor 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_temp_en_temp_en,temp_en,HI_TEMP_EN_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_EN_OFFSET)
HI_SET_GET(hi_temp_en_reserved,reserved,HI_TEMP_EN_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_EN_OFFSET)
HI_SET_GET(hi_temp_dis_time_temp_dis_time,temp_dis_time,HI_TEMP_DIS_TIME_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_DIS_TIME_OFFSET)
HI_SET_GET(hi_temp_dis_time_reserved,reserved,HI_TEMP_DIS_TIME_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_DIS_TIME_OFFSET)
HI_SET_GET(hi_trim0_local_sensor_trim,local_sensor_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor1_trim,remote_sensor1_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor2_trim,remote_sensor2_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor3_trim,remote_sensor3_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor4_trim,remote_sensor4_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor5_trim,remote_sensor5_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor6_trim,remote_sensor6_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor7_trim,remote_sensor7_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_temp_th_temp_0th,temp_0th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_1th,temp_1th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_2th,temp_2th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_3th,temp_3th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_b_th_temp_b_th,temp_b_th,HI_TEMP_B_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_B_TH_OFFSET)
HI_SET_GET(hi_temp_b_th_reserved,reserved,HI_TEMP_B_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_B_TH_OFFSET)
HI_SET_GET(hi_temp_config_ct_sel,ct_sel,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_test,test,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_sample_mode,sample_mode,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_sample_num,sample_num,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_reserved,reserved,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_rawint_temp_rawint,temp_rawint,HI_TEMP_RAWINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_RAWINT_OFFSET)
HI_SET_GET(hi_temp_rawint_reserved,reserved,HI_TEMP_RAWINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_RAWINT_OFFSET)
HI_SET_GET(hi_temp_mskint_temp_maskint,temp_maskint,HI_TEMP_MSKINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_MSKINT_OFFSET)
HI_SET_GET(hi_temp_mskint_reserved,reserved,HI_TEMP_MSKINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_MSKINT_OFFSET)
HI_SET_GET(hi_temp_statint_temp_statint,temp_statint,HI_TEMP_STATINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_STATINT_OFFSET)
HI_SET_GET(hi_temp_statint_reserved,reserved,HI_TEMP_STATINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_STATINT_OFFSET)
HI_SET_GET(hi_temp_temp,temp,HI_TEMP_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_OFFSET)
HI_SET_GET(hi_temp_reserved,reserved,HI_TEMP_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_OFFSET)
HI_SET_GET(hi_temp_trim_mode_temp_trim_mode,temp_trim_mode,HI_TEMP_TRIM_MODE_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TRIM_MODE_OFFSET)
HI_SET_GET(hi_temp_trim_mode_reserved,reserved,HI_TEMP_TRIM_MODE_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TRIM_MODE_OFFSET)

#endif // __HI_TSENSOR_H__

