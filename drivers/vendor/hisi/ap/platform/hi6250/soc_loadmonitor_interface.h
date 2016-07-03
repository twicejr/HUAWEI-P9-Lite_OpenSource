

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_LOADMONITOR_INTERFACE_H__
#define __SOC_LOADMONITOR_INTERFACE_H__

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
/* 寄存器说明：LOADMONITOR控制器使能寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_CTRL_EN_UNION */
#define SOC_LOADMONITOR_MONITOR_CTRL_EN_ADDR(base)    ((base) + (0x000))

/* 寄存器说明：LOADMONITOR控制器监测时间配置寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_CFG_TIME_UNION */
#define SOC_LOADMONITOR_MONITOR_CFG_TIME_ADDR(base)   ((base) + (0x004))

/* 寄存器说明：LOADMONITOR监测器使能寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_SENSOR_EN_UNION */
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_ADDR(base)  ((base) + (0x008))

/* 寄存器说明：LOADMONITOR监测器去使能寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_SENSOR_DIS_UNION */
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_ADDR(base) ((base) + (0x00C))

/* 寄存器说明：LOADMONITOR监测器使能状态寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_SENSOR_STAT_UNION */
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_ADDR(base) ((base) + (0x010))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD0_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD0_ADDR(base)      ((base) + (0x014))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD1_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD1_ADDR(base)      ((base) + (0x018))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD2_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD2_ADDR(base)      ((base) + (0x01C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD3_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD3_ADDR(base)      ((base) + (0x020))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD4_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD4_ADDR(base)      ((base) + (0x024))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD5_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD5_ADDR(base)      ((base) + (0x028))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD6_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD6_ADDR(base)      ((base) + (0x02C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD7_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD7_ADDR(base)      ((base) + (0x030))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD8_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD8_ADDR(base)      ((base) + (0x034))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD9_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD9_ADDR(base)      ((base) + (0x038))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD10_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD10_ADDR(base)     ((base) + (0x03C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD11_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD11_ADDR(base)     ((base) + (0x040))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD12_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD12_ADDR(base)     ((base) + (0x044))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD13_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD13_ADDR(base)     ((base) + (0x048))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD14_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD14_ADDR(base)     ((base) + (0x04C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD15_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD15_ADDR(base)     ((base) + (0x050))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD16_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD16_ADDR(base)     ((base) + (0x054))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD17_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD17_ADDR(base)     ((base) + (0x058))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD18_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD18_ADDR(base)     ((base) + (0x05C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD19_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD19_ADDR(base)     ((base) + (0x060))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD20_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD20_ADDR(base)     ((base) + (0x064))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD21_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD21_ADDR(base)     ((base) + (0x068))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD22_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD22_ADDR(base)     ((base) + (0x06C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD23_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD23_ADDR(base)     ((base) + (0x070))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD24_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD24_ADDR(base)     ((base) + (0x074))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD25_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD25_ADDR(base)     ((base) + (0x078))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD26_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD26_ADDR(base)     ((base) + (0x07C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD27_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD27_ADDR(base)     ((base) + (0x080))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD28_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD28_ADDR(base)     ((base) + (0x084))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD29_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD29_ADDR(base)     ((base) + (0x088))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD30_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD30_ADDR(base)     ((base) + (0x08C))

/* 寄存器说明：LOADMONITOR负载寄存器
   位域定义UNION结构:  SOC_LOADMONITOR_MONITOR_LOAD31_UNION */
#define SOC_LOADMONITOR_MONITOR_LOAD31_ADDR(base)     ((base) + (0x090))





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
 结构名    : SOC_LOADMONITOR_MONITOR_CTRL_EN_UNION
 结构说明  : MONITOR_CTRL_EN 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR控制器使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_ctrl_en : 1;  /* bit[0]   : LOADMONITOR控制器使能：
                                                          0：控制器不使能；
                                                          1：控制器使能。 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_LOADMONITOR_MONITOR_CTRL_EN_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_CTRL_EN_monitor_ctrl_en_START  (0)
#define SOC_LOADMONITOR_MONITOR_CTRL_EN_monitor_ctrl_en_END    (0)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_CFG_TIME_UNION
 结构说明  : MONITOR_CFG_TIME 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR控制器监测时间配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cfg_time : 32; /* bit[0-31]: 控制器监测时间配置寄存器，计数周期为60MHz时钟 */
    } reg;
} SOC_LOADMONITOR_MONITOR_CFG_TIME_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_CFG_TIME_monitor_cfg_time_START  (0)
#define SOC_LOADMONITOR_MONITOR_CFG_TIME_monitor_cfg_time_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_SENSOR_EN_UNION
 结构说明  : MONITOR_SENSOR_EN 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR监测器使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_sensor0_en  : 1;  /* bit[0] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor1_en  : 1;  /* bit[1] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor2_en  : 1;  /* bit[2] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor3_en  : 1;  /* bit[3] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor4_en  : 1;  /* bit[4] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor5_en  : 1;  /* bit[5] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor6_en  : 1;  /* bit[6] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor7_en  : 1;  /* bit[7] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor8_en  : 1;  /* bit[8] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor9_en  : 1;  /* bit[9] : LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor10_en : 1;  /* bit[10]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor11_en : 1;  /* bit[11]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor12_en : 1;  /* bit[12]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor13_en : 1;  /* bit[13]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor14_en : 1;  /* bit[14]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor15_en : 1;  /* bit[15]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor16_en : 1;  /* bit[16]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor17_en : 1;  /* bit[17]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor18_en : 1;  /* bit[18]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor19_en : 1;  /* bit[19]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor20_en : 1;  /* bit[20]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor21_en : 1;  /* bit[21]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor22_en : 1;  /* bit[22]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor23_en : 1;  /* bit[23]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor24_en : 1;  /* bit[24]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor25_en : 1;  /* bit[25]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor26_en : 1;  /* bit[26]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor27_en : 1;  /* bit[27]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor28_en : 1;  /* bit[28]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor29_en : 1;  /* bit[29]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor30_en : 1;  /* bit[30]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
        unsigned int  monitor_sensor31_en : 1;  /* bit[31]: LOADMONITOR监测器使能：
                                                            写0：无效果；
                                                            写1：使能监测器 */
    } reg;
} SOC_LOADMONITOR_MONITOR_SENSOR_EN_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor0_en_START   (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor0_en_END     (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor1_en_START   (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor1_en_END     (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor2_en_START   (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor2_en_END     (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor3_en_START   (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor3_en_END     (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor4_en_START   (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor4_en_END     (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor5_en_START   (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor5_en_END     (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor6_en_START   (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor6_en_END     (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor7_en_START   (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor7_en_END     (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor8_en_START   (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor8_en_END     (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor9_en_START   (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor9_en_END     (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor10_en_START  (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor10_en_END    (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor11_en_START  (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor11_en_END    (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor12_en_START  (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor12_en_END    (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor13_en_START  (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor13_en_END    (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor14_en_START  (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor14_en_END    (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor15_en_START  (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor15_en_END    (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor16_en_START  (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor16_en_END    (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor17_en_START  (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor17_en_END    (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor18_en_START  (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor18_en_END    (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor19_en_START  (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor19_en_END    (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor20_en_START  (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor20_en_END    (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor21_en_START  (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor21_en_END    (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor22_en_START  (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor22_en_END    (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor23_en_START  (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor23_en_END    (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor24_en_START  (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor24_en_END    (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor25_en_START  (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor25_en_END    (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor26_en_START  (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor26_en_END    (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor27_en_START  (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor27_en_END    (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor28_en_START  (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor28_en_END    (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor29_en_START  (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor29_en_END    (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor30_en_START  (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor30_en_END    (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor31_en_START  (31)
#define SOC_LOADMONITOR_MONITOR_SENSOR_EN_monitor_sensor31_en_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_SENSOR_DIS_UNION
 结构说明  : MONITOR_SENSOR_DIS 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR监测器去使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_sensor0_dis  : 1;  /* bit[0] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor1_dis  : 1;  /* bit[1] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor2_dis  : 1;  /* bit[2] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor3_dis  : 1;  /* bit[3] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor4_dis  : 1;  /* bit[4] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor5_dis  : 1;  /* bit[5] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor6_dis  : 1;  /* bit[6] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor7_dis  : 1;  /* bit[7] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor8_dis  : 1;  /* bit[8] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor9_dis  : 1;  /* bit[9] : LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor10_dis : 1;  /* bit[10]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor11_dis : 1;  /* bit[11]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor12_dis : 1;  /* bit[12]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor13_dis : 1;  /* bit[13]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor14_dis : 1;  /* bit[14]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor15_dis : 1;  /* bit[15]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor16_dis : 1;  /* bit[16]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor17_dis : 1;  /* bit[17]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor18_dis : 1;  /* bit[18]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor19_dis : 1;  /* bit[19]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor20_dis : 1;  /* bit[20]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor21_dis : 1;  /* bit[21]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor22_dis : 1;  /* bit[22]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor23_dis : 1;  /* bit[23]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor24_dis : 1;  /* bit[24]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor25_dis : 1;  /* bit[25]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor26_dis : 1;  /* bit[26]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor27_dis : 1;  /* bit[27]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor28_dis : 1;  /* bit[28]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor29_dis : 1;  /* bit[29]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor30_dis : 1;  /* bit[30]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
        unsigned int  monitor_sensor31_dis : 1;  /* bit[31]: LOADMONITOR监测器去使能：
                                                             写0：无效果；
                                                             写1：去使能监测器 */
    } reg;
} SOC_LOADMONITOR_MONITOR_SENSOR_DIS_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor0_dis_START   (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor0_dis_END     (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor1_dis_START   (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor1_dis_END     (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor2_dis_START   (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor2_dis_END     (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor3_dis_START   (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor3_dis_END     (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor4_dis_START   (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor4_dis_END     (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor5_dis_START   (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor5_dis_END     (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor6_dis_START   (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor6_dis_END     (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor7_dis_START   (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor7_dis_END     (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor8_dis_START   (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor8_dis_END     (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor9_dis_START   (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor9_dis_END     (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor10_dis_START  (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor10_dis_END    (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor11_dis_START  (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor11_dis_END    (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor12_dis_START  (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor12_dis_END    (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor13_dis_START  (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor13_dis_END    (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor14_dis_START  (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor14_dis_END    (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor15_dis_START  (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor15_dis_END    (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor16_dis_START  (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor16_dis_END    (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor17_dis_START  (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor17_dis_END    (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor18_dis_START  (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor18_dis_END    (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor19_dis_START  (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor19_dis_END    (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor20_dis_START  (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor20_dis_END    (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor21_dis_START  (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor21_dis_END    (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor22_dis_START  (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor22_dis_END    (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor23_dis_START  (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor23_dis_END    (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor24_dis_START  (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor24_dis_END    (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor25_dis_START  (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor25_dis_END    (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor26_dis_START  (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor26_dis_END    (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor27_dis_START  (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor27_dis_END    (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor28_dis_START  (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor28_dis_END    (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor29_dis_START  (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor29_dis_END    (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor30_dis_START  (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor30_dis_END    (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor31_dis_START  (31)
#define SOC_LOADMONITOR_MONITOR_SENSOR_DIS_monitor_sensor31_dis_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_SENSOR_STAT_UNION
 结构说明  : MONITOR_SENSOR_STAT 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR监测器使能状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_sensor0_stat  : 1;  /* bit[0] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor1_stat  : 1;  /* bit[1] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor2_stat  : 1;  /* bit[2] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor3_stat  : 1;  /* bit[3] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor4_stat  : 1;  /* bit[4] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor5_stat  : 1;  /* bit[5] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor6_stat  : 1;  /* bit[6] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor7_stat  : 1;  /* bit[7] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor8_stat  : 1;  /* bit[8] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor9_stat  : 1;  /* bit[9] : LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor10_stat : 1;  /* bit[10]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor11_stat : 1;  /* bit[11]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor12_stat : 1;  /* bit[12]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor13_stat : 1;  /* bit[13]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor14_stat : 1;  /* bit[14]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor15_stat : 1;  /* bit[15]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor16_stat : 1;  /* bit[16]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor17_stat : 1;  /* bit[17]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor18_stat : 1;  /* bit[18]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor19_stat : 1;  /* bit[19]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor20_stat : 1;  /* bit[20]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor21_stat : 1;  /* bit[21]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor22_stat : 1;  /* bit[22]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor23_stat : 1;  /* bit[23]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor24_stat : 1;  /* bit[24]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor25_stat : 1;  /* bit[25]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor26_stat : 1;  /* bit[26]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor27_stat : 1;  /* bit[27]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor28_stat : 1;  /* bit[28]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor29_stat : 1;  /* bit[29]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor30_stat : 1;  /* bit[30]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
        unsigned int  monitor_sensor31_stat : 1;  /* bit[31]: LOADMONITOR监测器使能状态：
                                                              0：不使能；
                                                              1：使能 */
    } reg;
} SOC_LOADMONITOR_MONITOR_SENSOR_STAT_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor0_stat_START   (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor0_stat_END     (0)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor1_stat_START   (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor1_stat_END     (1)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor2_stat_START   (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor2_stat_END     (2)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor3_stat_START   (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor3_stat_END     (3)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor4_stat_START   (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor4_stat_END     (4)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor5_stat_START   (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor5_stat_END     (5)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor6_stat_START   (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor6_stat_END     (6)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor7_stat_START   (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor7_stat_END     (7)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor8_stat_START   (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor8_stat_END     (8)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor9_stat_START   (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor9_stat_END     (9)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor10_stat_START  (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor10_stat_END    (10)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor11_stat_START  (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor11_stat_END    (11)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor12_stat_START  (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor12_stat_END    (12)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor13_stat_START  (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor13_stat_END    (13)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor14_stat_START  (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor14_stat_END    (14)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor15_stat_START  (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor15_stat_END    (15)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor16_stat_START  (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor16_stat_END    (16)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor17_stat_START  (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor17_stat_END    (17)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor18_stat_START  (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor18_stat_END    (18)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor19_stat_START  (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor19_stat_END    (19)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor20_stat_START  (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor20_stat_END    (20)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor21_stat_START  (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor21_stat_END    (21)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor22_stat_START  (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor22_stat_END    (22)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor23_stat_START  (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor23_stat_END    (23)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor24_stat_START  (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor24_stat_END    (24)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor25_stat_START  (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor25_stat_END    (25)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor26_stat_START  (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor26_stat_END    (26)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor27_stat_START  (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor27_stat_END    (27)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor28_stat_START  (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor28_stat_END    (28)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor29_stat_START  (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor29_stat_END    (29)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor30_stat_START  (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor30_stat_END    (30)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor31_stat_START  (31)
#define SOC_LOADMONITOR_MONITOR_SENSOR_STAT_monitor_sensor31_stat_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD0_UNION
 结构说明  : MONITOR_LOAD0 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load0 : 32; /* bit[0-31]: 第0路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD0_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD0_monitor_cnt_load0_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD0_monitor_cnt_load0_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD1_UNION
 结构说明  : MONITOR_LOAD1 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load1 : 32; /* bit[0-31]: 第1路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD1_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD1_monitor_cnt_load1_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD1_monitor_cnt_load1_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD2_UNION
 结构说明  : MONITOR_LOAD2 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load2 : 32; /* bit[0-31]: 第2路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD2_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD2_monitor_cnt_load2_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD2_monitor_cnt_load2_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD3_UNION
 结构说明  : MONITOR_LOAD3 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load3 : 32; /* bit[0-31]: 第3路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD3_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD3_monitor_cnt_load3_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD3_monitor_cnt_load3_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD4_UNION
 结构说明  : MONITOR_LOAD4 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load4 : 32; /* bit[0-31]: 第4路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD4_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD4_monitor_cnt_load4_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD4_monitor_cnt_load4_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD5_UNION
 结构说明  : MONITOR_LOAD5 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load5 : 32; /* bit[0-31]: 第5路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD5_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD5_monitor_cnt_load5_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD5_monitor_cnt_load5_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD6_UNION
 结构说明  : MONITOR_LOAD6 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load6 : 32; /* bit[0-31]: 第6路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD6_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD6_monitor_cnt_load6_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD6_monitor_cnt_load6_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD7_UNION
 结构说明  : MONITOR_LOAD7 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load7 : 32; /* bit[0-31]: 第7路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD7_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD7_monitor_cnt_load7_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD7_monitor_cnt_load7_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD8_UNION
 结构说明  : MONITOR_LOAD8 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load8 : 32; /* bit[0-31]: 第8路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD8_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD8_monitor_cnt_load8_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD8_monitor_cnt_load8_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD9_UNION
 结构说明  : MONITOR_LOAD9 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load9 : 32; /* bit[0-31]: 第9路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD9_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD9_monitor_cnt_load9_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD9_monitor_cnt_load9_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD10_UNION
 结构说明  : MONITOR_LOAD10 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load10 : 32; /* bit[0-31]: 第10路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD10_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD10_monitor_cnt_load10_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD10_monitor_cnt_load10_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD11_UNION
 结构说明  : MONITOR_LOAD11 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load11 : 32; /* bit[0-31]: 第11路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD11_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD11_monitor_cnt_load11_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD11_monitor_cnt_load11_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD12_UNION
 结构说明  : MONITOR_LOAD12 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load12 : 32; /* bit[0-31]: 第12路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD12_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD12_monitor_cnt_load12_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD12_monitor_cnt_load12_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD13_UNION
 结构说明  : MONITOR_LOAD13 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load13 : 32; /* bit[0-31]: 第13路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD13_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD13_monitor_cnt_load13_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD13_monitor_cnt_load13_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD14_UNION
 结构说明  : MONITOR_LOAD14 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load14 : 32; /* bit[0-31]: 第14路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD14_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD14_monitor_cnt_load14_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD14_monitor_cnt_load14_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD15_UNION
 结构说明  : MONITOR_LOAD15 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load15 : 32; /* bit[0-31]: 第15路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD15_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD15_monitor_cnt_load15_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD15_monitor_cnt_load15_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD16_UNION
 结构说明  : MONITOR_LOAD16 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load16 : 32; /* bit[0-31]: 第16路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD16_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD16_monitor_cnt_load16_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD16_monitor_cnt_load16_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD17_UNION
 结构说明  : MONITOR_LOAD17 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load17 : 32; /* bit[0-31]: 第17路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD17_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD17_monitor_cnt_load17_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD17_monitor_cnt_load17_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD18_UNION
 结构说明  : MONITOR_LOAD18 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load18 : 32; /* bit[0-31]: 第18路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD18_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD18_monitor_cnt_load18_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD18_monitor_cnt_load18_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD19_UNION
 结构说明  : MONITOR_LOAD19 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load19 : 32; /* bit[0-31]: 第19路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD19_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD19_monitor_cnt_load19_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD19_monitor_cnt_load19_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD20_UNION
 结构说明  : MONITOR_LOAD20 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load20 : 32; /* bit[0-31]: 第20路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD20_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD20_monitor_cnt_load20_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD20_monitor_cnt_load20_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD21_UNION
 结构说明  : MONITOR_LOAD21 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load21 : 32; /* bit[0-31]: 第21路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD21_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD21_monitor_cnt_load21_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD21_monitor_cnt_load21_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD22_UNION
 结构说明  : MONITOR_LOAD22 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load22 : 32; /* bit[0-31]: 第22路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD22_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD22_monitor_cnt_load22_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD22_monitor_cnt_load22_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD23_UNION
 结构说明  : MONITOR_LOAD23 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load23 : 32; /* bit[0-31]: 第23路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD23_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD23_monitor_cnt_load23_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD23_monitor_cnt_load23_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD24_UNION
 结构说明  : MONITOR_LOAD24 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load24 : 32; /* bit[0-31]: 第24路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD24_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD24_monitor_cnt_load24_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD24_monitor_cnt_load24_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD25_UNION
 结构说明  : MONITOR_LOAD25 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load25 : 32; /* bit[0-31]: 第25路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD25_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD25_monitor_cnt_load25_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD25_monitor_cnt_load25_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD26_UNION
 结构说明  : MONITOR_LOAD26 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load26 : 32; /* bit[0-31]: 第26路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD26_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD26_monitor_cnt_load26_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD26_monitor_cnt_load26_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD27_UNION
 结构说明  : MONITOR_LOAD27 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load27 : 32; /* bit[0-31]: 第27路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD27_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD27_monitor_cnt_load27_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD27_monitor_cnt_load27_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD28_UNION
 结构说明  : MONITOR_LOAD28 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load28 : 32; /* bit[0-31]: 第28路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD28_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD28_monitor_cnt_load28_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD28_monitor_cnt_load28_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD29_UNION
 结构说明  : MONITOR_LOAD29 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load29 : 32; /* bit[0-31]: 第29路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD29_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD29_monitor_cnt_load29_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD29_monitor_cnt_load29_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD30_UNION
 结构说明  : MONITOR_LOAD30 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load30 : 32; /* bit[0-31]: 第30路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD30_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD30_monitor_cnt_load30_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD30_monitor_cnt_load30_END    (31)


/*****************************************************************************
 结构名    : SOC_LOADMONITOR_MONITOR_LOAD31_UNION
 结构说明  : MONITOR_LOAD31 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: LOADMONITOR负载寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_cnt_load31 : 32; /* bit[0-31]: 第31路负载 */
    } reg;
} SOC_LOADMONITOR_MONITOR_LOAD31_UNION;
#endif
#define SOC_LOADMONITOR_MONITOR_LOAD31_monitor_cnt_load31_START  (0)
#define SOC_LOADMONITOR_MONITOR_LOAD31_monitor_cnt_load31_END    (31)






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

#endif /* end of soc_loadmonitor_interface.h */
