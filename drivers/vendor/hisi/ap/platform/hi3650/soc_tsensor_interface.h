/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_tsensor_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:23:15
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_Tsensor.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_TSENSOR_INTERFACE_H__
#define __SOC_TSENSOR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_tsensorc
 ****************************************************************************/
/* 寄存器说明：Tsensor1温度校准寄存器1
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION11_UNION */
#define SOC_Tsensor_CALIBRATION11_ADDR(base)          ((base) + (0x000))

/* 寄存器说明：Tsensor1温度校准寄存器2
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION21_UNION */
#define SOC_Tsensor_CALIBRATION21_ADDR(base)          ((base) + (0x004))

/* 寄存器说明：Tsensor1模式配置寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_CONFIG1_UNION */
#define SOC_Tsensor_TEMP_CONFIG1_ADDR(base)           ((base) + (0x008))

/* 寄存器说明：Tsensor1温度检测使能寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_DET_EN1_UNION */
#define SOC_Tsensor_TEMP_DET_EN1_ADDR(base)           ((base) + (0x00C))

/* 寄存器说明：Tsensor1温度检测去使能等待寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_BYPASS1_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_ADDR(base)      ((base) + (0x010))

/* 寄存器说明：Tsensor1温度检测去使能等待时间寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_TIME1_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME1_ADDR(base)        ((base) + (0x014))

/* 寄存器说明：Tsensor1温度检测当前状态寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_FSMSTAT1_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT1_ADDR(base)          ((base) + (0x018))

/* 寄存器说明：Tsensor1温度检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP1_UNION */
#define SOC_Tsensor_TEMP1_ADDR(base)                  ((base) + (0x01C))

/* 寄存器说明：Tsensor1温度报警门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_TH1_UNION */
#define SOC_Tsensor_TEMP_TH1_ADDR(base)               ((base) + (0x020))

/* 寄存器说明：Tsensor1温度复位门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_TH1_UNION */
#define SOC_Tsensor_TEMP_RST_TH1_ADDR(base)           ((base) + (0x024))

/* 寄存器说明：Tsensor1温度回滞寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_LAG1_UNION */
#define SOC_Tsensor_TEMP_LAG1_ADDR(base)              ((base) + (0x028))

/* 寄存器说明：Tsensor1中断屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_MSK1_UNION */
#define SOC_Tsensor_TEMP_INT_MSK1_ADDR(base)          ((base) + (0x02C))

/* 寄存器说明：Tsensor1中断清除寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_CLR1_UNION */
#define SOC_Tsensor_TEMP_INT_CLR1_ADDR(base)          ((base) + (0x030))

/* 寄存器说明：Tsensor1复位屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_MSK1_UNION */
#define SOC_Tsensor_TEMP_RST_MSK1_ADDR(base)          ((base) + (0x034))

/* 寄存器说明：Tsensor1原始中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RAWINT1_UNION */
#define SOC_Tsensor_TEMP_RAWINT1_ADDR(base)           ((base) + (0x038))

/* 寄存器说明：Tsensor1屏蔽中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_MSKINT1_UNION */
#define SOC_Tsensor_TEMP_MSKINT1_ADDR(base)           ((base) + (0x03C))

/* 寄存器说明：Tsensor2温度校准寄存器1
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION12_UNION */
#define SOC_Tsensor_CALIBRATION12_ADDR(base)          ((base) + (0x040))

/* 寄存器说明：Tsensor2温度校准寄存器2
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION22_UNION */
#define SOC_Tsensor_CALIBRATION22_ADDR(base)          ((base) + (0x044))

/* 寄存器说明：Tsensor2模式配置寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_CONFIG2_UNION */
#define SOC_Tsensor_TEMP_CONFIG2_ADDR(base)           ((base) + (0x048))

/* 寄存器说明：Tsensor2温度检测使能寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_DET_EN2_UNION */
#define SOC_Tsensor_TEMP_DET_EN2_ADDR(base)           ((base) + (0x04C))

/* 寄存器说明：Tsensor2温度检测去使能等待寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_BYPASS2_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_ADDR(base)      ((base) + (0x050))

/* 寄存器说明：Tsensor2温度检测去使能等待时间寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_TIME2_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME2_ADDR(base)        ((base) + (0x054))

/* 寄存器说明：Tsensor2温度检测当前状态寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_FSMSTAT2_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT2_ADDR(base)          ((base) + (0x058))

/* 寄存器说明：Tsensor2温度检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP2_UNION */
#define SOC_Tsensor_TEMP2_ADDR(base)                  ((base) + (0x05C))

/* 寄存器说明：Tsensor2温度报警门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_TH2_UNION */
#define SOC_Tsensor_TEMP_TH2_ADDR(base)               ((base) + (0x060))

/* 寄存器说明：Tsensor2温度复位门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_TH2_UNION */
#define SOC_Tsensor_TEMP_RST_TH2_ADDR(base)           ((base) + (0x064))

/* 寄存器说明：Tsensor2温度回滞寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_LAG2_UNION */
#define SOC_Tsensor_TEMP_LAG2_ADDR(base)              ((base) + (0x068))

/* 寄存器说明：Tsensor2中断屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_MSK2_UNION */
#define SOC_Tsensor_TEMP_INT_MSK2_ADDR(base)          ((base) + (0x06C))

/* 寄存器说明：Tsensor2中断清除寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_CLR2_UNION */
#define SOC_Tsensor_TEMP_INT_CLR2_ADDR(base)          ((base) + (0x070))

/* 寄存器说明：Tsensor2复位屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_MSK2_UNION */
#define SOC_Tsensor_TEMP_RST_MSK2_ADDR(base)          ((base) + (0x074))

/* 寄存器说明：Tsensor2原始中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RAWINT2_UNION */
#define SOC_Tsensor_TEMP_RAWINT2_ADDR(base)           ((base) + (0x078))

/* 寄存器说明：Tsensor2屏蔽中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_MSKINT2_UNION */
#define SOC_Tsensor_TEMP_MSKINT2_ADDR(base)           ((base) + (0x07C))

/* 寄存器说明：Tsensor3温度校准寄存器1
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION13_UNION */
#define SOC_Tsensor_CALIBRATION13_ADDR(base)          ((base) + (0x080))

/* 寄存器说明：Tsensor3温度校准寄存器2
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION23_UNION */
#define SOC_Tsensor_CALIBRATION23_ADDR(base)          ((base) + (0x084))

/* 寄存器说明：Tsensor3模式配置寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_CONFIG3_UNION */
#define SOC_Tsensor_TEMP_CONFIG3_ADDR(base)           ((base) + (0x088))

/* 寄存器说明：Tsensor3温度检测使能寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_DET_EN3_UNION */
#define SOC_Tsensor_TEMP_DET_EN3_ADDR(base)           ((base) + (0x08C))

/* 寄存器说明：Tsensor3温度检测去使能等待寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_BYPASS3_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_ADDR(base)      ((base) + (0x090))

/* 寄存器说明：Tsensor3温度检测去使能等待时间寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_TIME3_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME3_ADDR(base)        ((base) + (0x094))

/* 寄存器说明：Tsensor3温度检测当前状态寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_FSMSTAT3_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT3_ADDR(base)          ((base) + (0x098))

/* 寄存器说明：Tsensor3温度检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP3_UNION */
#define SOC_Tsensor_TEMP3_ADDR(base)                  ((base) + (0x09C))

/* 寄存器说明：Tsensor3温度报警门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_TH3_UNION */
#define SOC_Tsensor_TEMP_TH3_ADDR(base)               ((base) + (0x0A0))

/* 寄存器说明：Tsensor3温度复位门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_TH3_UNION */
#define SOC_Tsensor_TEMP_RST_TH3_ADDR(base)           ((base) + (0x0A4))

/* 寄存器说明：Tsensor3温度回滞寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_LAG3_UNION */
#define SOC_Tsensor_TEMP_LAG3_ADDR(base)              ((base) + (0x0A8))

/* 寄存器说明：Tsensor3中断屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_MSK3_UNION */
#define SOC_Tsensor_TEMP_INT_MSK3_ADDR(base)          ((base) + (0x0AC))

/* 寄存器说明：Tsensor3中断清除寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_CLR3_UNION */
#define SOC_Tsensor_TEMP_INT_CLR3_ADDR(base)          ((base) + (0x0B0))

/* 寄存器说明：Tsensor3复位屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_MSK3_UNION */
#define SOC_Tsensor_TEMP_RST_MSK3_ADDR(base)          ((base) + (0x0B4))

/* 寄存器说明：Tsensor3原始中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RAWINT3_UNION */
#define SOC_Tsensor_TEMP_RAWINT3_ADDR(base)           ((base) + (0x0B8))

/* 寄存器说明：Tsensor3屏蔽中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_MSKINT3_UNION */
#define SOC_Tsensor_TEMP_MSKINT3_ADDR(base)           ((base) + (0x0BC))

/* 寄存器说明：Tsensor4温度校准寄存器1
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION14_UNION */
#define SOC_Tsensor_CALIBRATION14_ADDR(base)          ((base) + (0x0C0))

/* 寄存器说明：Tsensor4温度校准寄存器2
   位域定义UNION结构:  SOC_Tsensor_CALIBRATION24_UNION */
#define SOC_Tsensor_CALIBRATION24_ADDR(base)          ((base) + (0x0C4))

/* 寄存器说明：Tsensor4模式配置寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_CONFIG4_UNION */
#define SOC_Tsensor_TEMP_CONFIG4_ADDR(base)           ((base) + (0x0C8))

/* 寄存器说明：Tsensor4温度检测使能寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_DET_EN4_UNION */
#define SOC_Tsensor_TEMP_DET_EN4_ADDR(base)           ((base) + (0x0CC))

/* 寄存器说明：Tsensor4温度检测去使能等待寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_BYPASS4_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_ADDR(base)      ((base) + (0x0D0))

/* 寄存器说明：Tsensor4温度检测去使能等待时间寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_WAIT_TIME4_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME4_ADDR(base)        ((base) + (0x0D4))

/* 寄存器说明：Tsensor4温度检测当前状态寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_FSMSTAT4_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT4_ADDR(base)          ((base) + (0x0D8))

/* 寄存器说明：Tsensor4温度检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP4_UNION */
#define SOC_Tsensor_TEMP4_ADDR(base)                  ((base) + (0x0DC))

/* 寄存器说明：Tsensor4温度报警门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_TH4_UNION */
#define SOC_Tsensor_TEMP_TH4_ADDR(base)               ((base) + (0x0E0))

/* 寄存器说明：Tsensor4温度复位门限寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_TH4_UNION */
#define SOC_Tsensor_TEMP_RST_TH4_ADDR(base)           ((base) + (0x0E4))

/* 寄存器说明：Tsensor4温度回滞寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_LAG4_UNION */
#define SOC_Tsensor_TEMP_LAG4_ADDR(base)              ((base) + (0x0E8))

/* 寄存器说明：Tsensor4中断屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_MSK4_UNION */
#define SOC_Tsensor_TEMP_INT_MSK4_ADDR(base)          ((base) + (0x0EC))

/* 寄存器说明：Tsensor4中断清除寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_INT_CLR4_UNION */
#define SOC_Tsensor_TEMP_INT_CLR4_ADDR(base)          ((base) + (0x0F0))

/* 寄存器说明：Tsensor4复位屏蔽寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RST_MSK4_UNION */
#define SOC_Tsensor_TEMP_RST_MSK4_ADDR(base)          ((base) + (0x0F4))

/* 寄存器说明：Tsensor4原始中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_RAWINT4_UNION */
#define SOC_Tsensor_TEMP_RAWINT4_ADDR(base)           ((base) + (0x0F8))

/* 寄存器说明：Tsensor4屏蔽中断寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_MSKINT4_UNION */
#define SOC_Tsensor_TEMP_MSKINT4_ADDR(base)           ((base) + (0x0FC))

/* 寄存器说明：Tsensor1软件控制寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_SOFTCTRL1_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL1_ADDR(base)         ((base) + (0x100))

/* 寄存器说明：Tsensor1软件控制检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP1_SOFT_UNION */
#define SOC_Tsensor_TEMP1_SOFT_ADDR(base)             ((base) + (0x104))

/* 寄存器说明：Tsensor2软件控制寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_SOFTCTRL2_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL2_ADDR(base)         ((base) + (0x108))

/* 寄存器说明：Tsensor2软件控制检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP2_SOFT_UNION */
#define SOC_Tsensor_TEMP2_SOFT_ADDR(base)             ((base) + (0x10C))

/* 寄存器说明：Tsensor3软件控制寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_SOFTCTRL3_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL3_ADDR(base)         ((base) + (0x110))

/* 寄存器说明：Tsensor3软件控制检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP3_SOFT_UNION */
#define SOC_Tsensor_TEMP3_SOFT_ADDR(base)             ((base) + (0x114))

/* 寄存器说明：Tsensor4软件控制寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP_SOFTCTRL4_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL4_ADDR(base)         ((base) + (0x118))

/* 寄存器说明：Tsensor4软件控制检测结果寄存器
   位域定义UNION结构:  SOC_Tsensor_TEMP4_SOFT_UNION */
#define SOC_Tsensor_TEMP4_SOFT_ADDR(base)             ((base) + (0x11C))





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
                     (1/1) register_tsensorc
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION11_UNION
 结构说明  : CALIBRATION11 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度校准寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: reserved */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: reserved */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_Tsensor_CALIBRATION11_UNION;
#endif
#define SOC_Tsensor_CALIBRATION11_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION11_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION11_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION11_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION11_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION11_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION11_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION11_remote_sensor3error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION21_UNION
 结构说明  : CALIBRATION21 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度校准寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : reserved */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: reserved */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: reserved */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_Tsensor_CALIBRATION21_UNION;
#endif
#define SOC_Tsensor_CALIBRATION21_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION21_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION21_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION21_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION21_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION21_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION21_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION21_remote_sensor7error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_CONFIG1_UNION
 结构说明  : TEMP_CONFIG1 寄存器结构定义。地址偏移量:0x008，初值:0x00002000，宽度:32
 寄存器说明: Tsensor1模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num1 : 3;  /* bit[0-2]  : Tsensor1通道个数选择：
                                                        0：只有LOCAL SENSOR */
        unsigned int  channel_sel1 : 4;  /* bit[3-6]  : Tsensor1通道模式选择：
                                                        0000——选择LOCAL SENSOR的温度值
                                                        0001~1111——保留 */
        unsigned int  temp_mode1   : 2;  /* bit[7-8]  : Tsensor1同一通道温度采样模式选择：
                                                        00——多次采样取均值
                                                        01——保留
                                                        10——保留
                                                        11——保留 */
        unsigned int  sample_num1  : 8;  /* bit[9-16] : Tsensor1同一通道采样次数选择，只支持16的整数倍：16、32、64、128、256
                                                        配置值为N，对应采样2*N
                                                        采样值为16、32、64、128、256对应配置值为8、16、32、64、128 */
        unsigned int  ct_sel_apb1  : 2;  /* bit[17-18]: Tsensor1 HKADC转换时间选择：
                                                        00——0.512ms
                                                        01——0.256ms
                                                        10——1.024ms
                                                        11——2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_CONFIG1_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG1_channel_num1_START  (0)
#define SOC_Tsensor_TEMP_CONFIG1_channel_num1_END    (2)
#define SOC_Tsensor_TEMP_CONFIG1_channel_sel1_START  (3)
#define SOC_Tsensor_TEMP_CONFIG1_channel_sel1_END    (6)
#define SOC_Tsensor_TEMP_CONFIG1_temp_mode1_START    (7)
#define SOC_Tsensor_TEMP_CONFIG1_temp_mode1_END      (8)
#define SOC_Tsensor_TEMP_CONFIG1_sample_num1_START   (9)
#define SOC_Tsensor_TEMP_CONFIG1_sample_num1_END     (16)
#define SOC_Tsensor_TEMP_CONFIG1_ct_sel_apb1_START   (17)
#define SOC_Tsensor_TEMP_CONFIG1_ct_sel_apb1_END     (18)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_DET_EN1_UNION
 结构说明  : TEMP_DET_EN1 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度检测使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en1 : 1;  /* bit[0]   : Tsensor1温度采样使能寄存器：
                                                       0：不使能
                                                       1：使能 */
        unsigned int  calib1       : 1;  /* bit[1]   : Tsensor1校准使能位
                                                       1'b1：不开启校准算法
                                                       1'b0：开启校准算法（默认） */
        unsigned int  calib1_en    : 1;  /* bit[2]   : 使能后，能够通过VCALIB1进行电压方式校准；
                                                       1'b0:disable
                                                       1'b1:表示enable
                                                       缺省为“0”；（高电平0.8V） */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_DET_EN1_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN1_temp_det_en1_START  (0)
#define SOC_Tsensor_TEMP_DET_EN1_temp_det_en1_END    (0)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_START        (1)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_END          (1)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_en_END       (2)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_BYPASS1_UNION
 结构说明  : TEMP_WAIT_BYPASS1 寄存器结构定义。地址偏移量:0x010，初值:0x00000001，宽度:32
 寄存器说明: Tsensor1温度检测去使能等待寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass1 : 1;  /* bit[0]   : Tsensor1去使能后等待寄存器：
                                                            0：去使能后等待，等待时间可配置
                                                            1：去使能后不等待 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS1_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_temp_wait_bypass1_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_temp_wait_bypass1_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_TIME1_UNION
 结构说明  : TEMP_WAIT_TIME1 寄存器结构定义。地址偏移量:0x014，初值:0x000001F4，宽度:32
 寄存器说明: Tsensor1温度检测去使能等待时间寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time1 : 32; /* bit[0-31]: reserved */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME1_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME1_temp_wait_time1_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME1_temp_wait_time1_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_FSMSTAT1_UNION
 结构说明  : TEMP_FSMSTAT1 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度检测当前状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor1 SAMPLE状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor1 TEMPCTL状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT1_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT1_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT1_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT1_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT1_s_fsm_stat_END    (7)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP1_UNION
 结构说明  : TEMP1 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp1    : 10; /* bit[0-9]  : Tsensor1温度检测结果寄存器 */
        unsigned int  reserved : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP1_UNION;
#endif
#define SOC_Tsensor_TEMP1_temp1_START     (0)
#define SOC_Tsensor_TEMP1_temp1_END       (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_TH1_UNION
 结构说明  : TEMP_TH1 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度报警门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th1 : 10; /* bit[0-9]  : Tsensor1温度报警门限0 */
        unsigned int  temp_1th1 : 10; /* bit[10-19]: Tsensor1温度报警门限1 */
        unsigned int  temp_2th1 : 10; /* bit[20-29]: Tsensor1温度报警门限2 */
        unsigned int  reserved  : 2;  /* bit[30-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_TH1_UNION;
#endif
#define SOC_Tsensor_TEMP_TH1_temp_0th1_START  (0)
#define SOC_Tsensor_TEMP_TH1_temp_0th1_END    (9)
#define SOC_Tsensor_TEMP_TH1_temp_1th1_START  (10)
#define SOC_Tsensor_TEMP_TH1_temp_1th1_END    (19)
#define SOC_Tsensor_TEMP_TH1_temp_2th1_START  (20)
#define SOC_Tsensor_TEMP_TH1_temp_2th1_END    (29)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_TH1_UNION
 结构说明  : TEMP_RST_TH1 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度复位门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th1 : 10; /* bit[0-9]  : Tsensor1温度复位门限 */
        unsigned int  reserved     : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_TH1_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH1_temp_rst_th1_START  (0)
#define SOC_Tsensor_TEMP_RST_TH1_temp_rst_th1_END    (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_LAG1_UNION
 结构说明  : TEMP_LAG1 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1温度回滞寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag1 : 7;  /* bit[0-6] : Tsensor1温度回滞门限 */
        unsigned int  reserved  : 25; /* bit[7-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_LAG1_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG1_temp_lag1_START  (0)
#define SOC_Tsensor_TEMP_LAG1_temp_lag1_END    (6)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_MSK1_UNION
 结构说明  : TEMP_INT_MSK1 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk1 : 1;  /* bit[0]   : Tsensor1中断屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK1_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK1_temp_int_msk1_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK1_temp_int_msk1_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_CLR1_UNION
 结构说明  : TEMP_INT_CLR1 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr1 : 1;  /* bit[0]   : Tsensor1中断清除控制BIT：
                                                        1：清除RAW和MSK中断
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR1_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR1_temp_int_clr1_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR1_temp_int_clr1_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_MSK1_UNION
 结构说明  : TEMP_RST_MSK1 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1复位屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk1 : 1;  /* bit[0]   : Tsensor1复位屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK1_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK1_temp_rst_msk1_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK1_temp_rst_msk1_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RAWINT1_UNION
 结构说明  : TEMP_RAWINT1 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1原始中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint1 : 1;  /* bit[0]   : Tsensor1原始中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RAWINT1_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT1_temp_rawint1_START  (0)
#define SOC_Tsensor_TEMP_RAWINT1_temp_rawint1_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_MSKINT1_UNION
 结构说明  : TEMP_MSKINT1 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1屏蔽中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint1 : 1;  /* bit[0]   : Tsensor1屏蔽中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_MSKINT1_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT1_temp_mskint1_START  (0)
#define SOC_Tsensor_TEMP_MSKINT1_temp_mskint1_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION12_UNION
 结构说明  : CALIBRATION12 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度校准寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
    } reg;
} SOC_Tsensor_CALIBRATION12_UNION;
#endif
#define SOC_Tsensor_CALIBRATION12_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION12_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION12_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION12_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION12_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION12_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION12_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION12_remote_sensor3error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION22_UNION
 结构说明  : CALIBRATION22 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度校准寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
    } reg;
} SOC_Tsensor_CALIBRATION22_UNION;
#endif
#define SOC_Tsensor_CALIBRATION22_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION22_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION22_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION22_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION22_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION22_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION22_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION22_remote_sensor7error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_CONFIG2_UNION
 结构说明  : TEMP_CONFIG2 寄存器结构定义。地址偏移量:0x048，初值:0x00002000，宽度:32
 寄存器说明: Tsensor2模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num2 : 3;  /* bit[0-2]  : Tsensor2通道个数选择：
                                                        0：只有LOCAL SENSOR */
        unsigned int  channel_sel2 : 4;  /* bit[3-6]  : Tsensor2通道模式选择：
                                                        0000——选择LOCAL SENSOR的温度值
                                                        其他——保留 */
        unsigned int  temp_mode2   : 2;  /* bit[7-8]  : Tsensor2同一通道温度采样模式选择：
                                                        00——多次采样取均值
                                                        其他——保留 */
        unsigned int  sample_num2  : 8;  /* bit[9-16] : Tsensor2同一通道采样次数选择，只支持16的整数倍：16、32、64、128、256
                                                        配置值为N，对应采样2*N
                                                        采样值为16、32、64、128、256对应配置值为8、16、32、64、128 */
        unsigned int  ct_sel_apb2  : 2;  /* bit[17-18]: Tsensor2 HKADC转换时间选择：
                                                        00——0.512ms
                                                        01——0.256ms
                                                        10——1.024ms
                                                        11——2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_CONFIG2_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG2_channel_num2_START  (0)
#define SOC_Tsensor_TEMP_CONFIG2_channel_num2_END    (2)
#define SOC_Tsensor_TEMP_CONFIG2_channel_sel2_START  (3)
#define SOC_Tsensor_TEMP_CONFIG2_channel_sel2_END    (6)
#define SOC_Tsensor_TEMP_CONFIG2_temp_mode2_START    (7)
#define SOC_Tsensor_TEMP_CONFIG2_temp_mode2_END      (8)
#define SOC_Tsensor_TEMP_CONFIG2_sample_num2_START   (9)
#define SOC_Tsensor_TEMP_CONFIG2_sample_num2_END     (16)
#define SOC_Tsensor_TEMP_CONFIG2_ct_sel_apb2_START   (17)
#define SOC_Tsensor_TEMP_CONFIG2_ct_sel_apb2_END     (18)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_DET_EN2_UNION
 结构说明  : TEMP_DET_EN2 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度检测使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en2 : 1;  /* bit[0]   : Tsensor2温度采样使能寄存器：
                                                       0：不使能
                                                       1：使能 */
        unsigned int  calib2       : 1;  /* bit[1]   : Tsensor2校准使能位
                                                       1'b1：不开启校准算法
                                                       1'b0：开启校准算法（默认） */
        unsigned int  calib2_en    : 1;  /* bit[2]   : 使能后，能够通过VCALIB1进行电压方式校准；
                                                       1'b0:disable
                                                       1'b1:表示enable
                                                       缺省为“0”；（高电平0.8V） */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_DET_EN2_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN2_temp_det_en2_START  (0)
#define SOC_Tsensor_TEMP_DET_EN2_temp_det_en2_END    (0)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_START        (1)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_END          (1)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_en_END       (2)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_BYPASS2_UNION
 结构说明  : TEMP_WAIT_BYPASS2 寄存器结构定义。地址偏移量:0x050，初值:0x00000001，宽度:32
 寄存器说明: Tsensor2温度检测去使能等待寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass2 : 1;  /* bit[0]   : Tsensor2去使能后等待寄存器：
                                                            0：去使能后等待，等待时间可配置
                                                            1：去使能后不等待 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS2_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_temp_wait_bypass2_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_temp_wait_bypass2_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_TIME2_UNION
 结构说明  : TEMP_WAIT_TIME2 寄存器结构定义。地址偏移量:0x054，初值:0x000001F4，宽度:32
 寄存器说明: Tsensor2温度检测去使能等待时间寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time2 : 32; /* bit[0-31]: 等待时间为N个PCLK周期。N表示此配置值
                                                          默认为500（PCLK为100MHZ时，5us） */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME2_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME2_temp_wait_time2_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME2_temp_wait_time2_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_FSMSTAT2_UNION
 结构说明  : TEMP_FSMSTAT2 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度检测当前状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor2 SAMPLE状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor2 TEMPCTL状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT2_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT2_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT2_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT2_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT2_s_fsm_stat_END    (7)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP2_UNION
 结构说明  : TEMP2 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp2    : 10; /* bit[0-9]  : Tsensor2温度检测结果寄存器 */
        unsigned int  reserved : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP2_UNION;
#endif
#define SOC_Tsensor_TEMP2_temp2_START     (0)
#define SOC_Tsensor_TEMP2_temp2_END       (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_TH2_UNION
 结构说明  : TEMP_TH2 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度报警门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th2 : 10; /* bit[0-9]  : Tsensor2温度报警门限0 */
        unsigned int  temp_1th2 : 10; /* bit[10-19]: Tsensor2温度报警门限1 */
        unsigned int  temp_2th2 : 10; /* bit[20-29]: Tsensor2温度报警门限2 */
        unsigned int  temp_3th2 : 2;  /* bit[30-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_TH2_UNION;
#endif
#define SOC_Tsensor_TEMP_TH2_temp_0th2_START  (0)
#define SOC_Tsensor_TEMP_TH2_temp_0th2_END    (9)
#define SOC_Tsensor_TEMP_TH2_temp_1th2_START  (10)
#define SOC_Tsensor_TEMP_TH2_temp_1th2_END    (19)
#define SOC_Tsensor_TEMP_TH2_temp_2th2_START  (20)
#define SOC_Tsensor_TEMP_TH2_temp_2th2_END    (29)
#define SOC_Tsensor_TEMP_TH2_temp_3th2_START  (30)
#define SOC_Tsensor_TEMP_TH2_temp_3th2_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_TH2_UNION
 结构说明  : TEMP_RST_TH2 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度复位门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th2 : 10; /* bit[0-9]  : Tsensor2温度复位门限 */
        unsigned int  reserved     : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_TH2_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH2_temp_rst_th2_START  (0)
#define SOC_Tsensor_TEMP_RST_TH2_temp_rst_th2_END    (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_LAG2_UNION
 结构说明  : TEMP_LAG2 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2温度回滞寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag2 : 7;  /* bit[0-6] : Tsensor2温度回滞门限 */
        unsigned int  reserved  : 25; /* bit[7-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_LAG2_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG2_temp_lag2_START  (0)
#define SOC_Tsensor_TEMP_LAG2_temp_lag2_END    (6)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_MSK2_UNION
 结构说明  : TEMP_INT_MSK2 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk2 : 1;  /* bit[0]   : Tsensor2中断屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK2_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK2_temp_int_msk2_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK2_temp_int_msk2_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_CLR2_UNION
 结构说明  : TEMP_INT_CLR2 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr2 : 1;  /* bit[0]   : Tsensor2中断清除控制BIT：
                                                        1：清除RAW和MSK中断
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR2_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR2_temp_int_clr2_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR2_temp_int_clr2_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_MSK2_UNION
 结构说明  : TEMP_RST_MSK2 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2复位屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk2 : 1;  /* bit[0]   : Tsensor2复位屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK2_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK2_temp_rst_msk2_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK2_temp_rst_msk2_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RAWINT2_UNION
 结构说明  : TEMP_RAWINT2 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2原始中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint2 : 1;  /* bit[0]   : Tsensor2原始中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RAWINT2_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT2_temp_rawint2_START  (0)
#define SOC_Tsensor_TEMP_RAWINT2_temp_rawint2_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_MSKINT2_UNION
 结构说明  : TEMP_MSKINT2 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2屏蔽中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint2 : 1;  /* bit[0]   : Tsensor2屏蔽中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_MSKINT2_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT2_temp_mskint2_START  (0)
#define SOC_Tsensor_TEMP_MSKINT2_temp_mskint2_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION13_UNION
 结构说明  : CALIBRATION13 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度校准寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
    } reg;
} SOC_Tsensor_CALIBRATION13_UNION;
#endif
#define SOC_Tsensor_CALIBRATION13_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION13_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION13_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION13_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION13_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION13_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION13_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION13_remote_sensor3error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION23_UNION
 结构说明  : CALIBRATION23 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度校准寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
    } reg;
} SOC_Tsensor_CALIBRATION23_UNION;
#endif
#define SOC_Tsensor_CALIBRATION23_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION23_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION23_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION23_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION23_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION23_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION23_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION23_remote_sensor7error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_CONFIG3_UNION
 结构说明  : TEMP_CONFIG3 寄存器结构定义。地址偏移量:0x088，初值:0x00002000，宽度:32
 寄存器说明: Tsensor3模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num3 : 3;  /* bit[0-2]  : Tsensor3通道个数选择：
                                                        0：只有LOCAL SENSOR */
        unsigned int  channel_sel3 : 4;  /* bit[3-6]  : Tsensor3通道模式选择：
                                                        0000——选择LOCAL SENSOR的温度值
                                                        其他——保留 */
        unsigned int  temp_mode3   : 2;  /* bit[7-8]  : Tsensor3同一通道温度采样模式选择：
                                                        00——多次采样取均值
                                                        其他——保留 */
        unsigned int  sample_num3  : 8;  /* bit[9-16] : Tsensor3同一通道采样次数选择，只支持16的整数倍：16、32、64、128、256
                                                        配置值为N，对应采样2*N
                                                        采样值为16、32、64、128、256对应配置值为8、16、32、64、128 */
        unsigned int  ct_sel_apb3  : 2;  /* bit[17-18]: Tsensor3 HKADC转换时间选择：
                                                        00——0.512ms
                                                        01——0.256ms
                                                        10——1.024ms
                                                        11——2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_CONFIG3_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG3_channel_num3_START  (0)
#define SOC_Tsensor_TEMP_CONFIG3_channel_num3_END    (2)
#define SOC_Tsensor_TEMP_CONFIG3_channel_sel3_START  (3)
#define SOC_Tsensor_TEMP_CONFIG3_channel_sel3_END    (6)
#define SOC_Tsensor_TEMP_CONFIG3_temp_mode3_START    (7)
#define SOC_Tsensor_TEMP_CONFIG3_temp_mode3_END      (8)
#define SOC_Tsensor_TEMP_CONFIG3_sample_num3_START   (9)
#define SOC_Tsensor_TEMP_CONFIG3_sample_num3_END     (16)
#define SOC_Tsensor_TEMP_CONFIG3_ct_sel_apb3_START   (17)
#define SOC_Tsensor_TEMP_CONFIG3_ct_sel_apb3_END     (18)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_DET_EN3_UNION
 结构说明  : TEMP_DET_EN3 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度检测使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en3 : 1;  /* bit[0]   : Tsensor3温度采样使能寄存器：
                                                       0：不使能
                                                       1：使能 */
        unsigned int  calib3       : 1;  /* bit[1]   : Tsensor3校准使能位
                                                       1'b1：不开启校准算法
                                                       1'b0：开启校准算法（默认） */
        unsigned int  calib3_en    : 1;  /* bit[2]   : 使能后，能够通过VCALIB1进行电压方式校准；
                                                       1'b0:disable
                                                       1'b1:表示enable
                                                       缺省为“0”；（高电平0.8V） */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_DET_EN3_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN3_temp_det_en3_START  (0)
#define SOC_Tsensor_TEMP_DET_EN3_temp_det_en3_END    (0)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_START        (1)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_END          (1)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_en_END       (2)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_BYPASS3_UNION
 结构说明  : TEMP_WAIT_BYPASS3 寄存器结构定义。地址偏移量:0x090，初值:0x00000001，宽度:32
 寄存器说明: Tsensor3温度检测去使能等待寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass3 : 1;  /* bit[0]   : Tsensor3去使能后等待寄存器：
                                                            0：去使能后等待，等待时间可配置
                                                            1：去使能后不等待 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS3_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_temp_wait_bypass3_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_temp_wait_bypass3_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_TIME3_UNION
 结构说明  : TEMP_WAIT_TIME3 寄存器结构定义。地址偏移量:0x094，初值:0x000001F4，宽度:32
 寄存器说明: Tsensor3温度检测去使能等待时间寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time3 : 32; /* bit[0-31]: 等待时间为N个PCLK周期。N表示此配置值
                                                          默认为500（PCLK为100MHZ时，5us） */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME3_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME3_temp_wait_time3_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME3_temp_wait_time3_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_FSMSTAT3_UNION
 结构说明  : TEMP_FSMSTAT3 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度检测当前状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor3 SAMPLE状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor3 TEMPCTL状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT3_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT3_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT3_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT3_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT3_s_fsm_stat_END    (7)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP3_UNION
 结构说明  : TEMP3 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp3    : 10; /* bit[0-9]  : Tsensor3温度检测结果寄存器 */
        unsigned int  reserved : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP3_UNION;
#endif
#define SOC_Tsensor_TEMP3_temp3_START     (0)
#define SOC_Tsensor_TEMP3_temp3_END       (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_TH3_UNION
 结构说明  : TEMP_TH3 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度报警门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th3 : 10; /* bit[0-9]  : Tsensor3温度报警门限0 */
        unsigned int  temp_1th3 : 10; /* bit[10-19]: Tsensor3温度报警门限1 */
        unsigned int  temp_2th3 : 10; /* bit[20-29]: Tsensor3温度报警门限2 */
        unsigned int  temp_3th3 : 2;  /* bit[30-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_TH3_UNION;
#endif
#define SOC_Tsensor_TEMP_TH3_temp_0th3_START  (0)
#define SOC_Tsensor_TEMP_TH3_temp_0th3_END    (9)
#define SOC_Tsensor_TEMP_TH3_temp_1th3_START  (10)
#define SOC_Tsensor_TEMP_TH3_temp_1th3_END    (19)
#define SOC_Tsensor_TEMP_TH3_temp_2th3_START  (20)
#define SOC_Tsensor_TEMP_TH3_temp_2th3_END    (29)
#define SOC_Tsensor_TEMP_TH3_temp_3th3_START  (30)
#define SOC_Tsensor_TEMP_TH3_temp_3th3_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_TH3_UNION
 结构说明  : TEMP_RST_TH3 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度复位门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th3 : 10; /* bit[0-9]  : Tsensor3温度复位门限 */
        unsigned int  reserved     : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_TH3_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH3_temp_rst_th3_START  (0)
#define SOC_Tsensor_TEMP_RST_TH3_temp_rst_th3_END    (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_LAG3_UNION
 结构说明  : TEMP_LAG3 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3温度回滞寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag3 : 7;  /* bit[0-6] : Tsensor3温度回滞门限 */
        unsigned int  reserved  : 25; /* bit[7-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_LAG3_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG3_temp_lag3_START  (0)
#define SOC_Tsensor_TEMP_LAG3_temp_lag3_END    (6)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_MSK3_UNION
 结构说明  : TEMP_INT_MSK3 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk3 : 1;  /* bit[0]   : Tsensor3中断屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK3_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK3_temp_int_msk3_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK3_temp_int_msk3_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_CLR3_UNION
 结构说明  : TEMP_INT_CLR3 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr3 : 1;  /* bit[0]   : Tsensor3中断清除控制BIT：
                                                        1：清除RAW和MSK中断
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR3_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR3_temp_int_clr3_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR3_temp_int_clr3_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_MSK3_UNION
 结构说明  : TEMP_RST_MSK3 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3复位屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk3 : 1;  /* bit[0]   : Tsensor3复位屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK3_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK3_temp_rst_msk3_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK3_temp_rst_msk3_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RAWINT3_UNION
 结构说明  : TEMP_RAWINT3 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3原始中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint3 : 1;  /* bit[0]   : Tsensor3原始中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RAWINT3_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT3_temp_rawint3_START  (0)
#define SOC_Tsensor_TEMP_RAWINT3_temp_rawint3_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_MSKINT3_UNION
 结构说明  : TEMP_MSKINT3 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3屏蔽中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint3 : 1;  /* bit[0]   : Tsensor3屏蔽中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_MSKINT3_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT3_temp_mskint3_START  (0)
#define SOC_Tsensor_TEMP_MSKINT3_temp_mskint3_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION14_UNION
 结构说明  : CALIBRATION14 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度校准寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
    } reg;
} SOC_Tsensor_CALIBRATION14_UNION;
#endif
#define SOC_Tsensor_CALIBRATION14_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION14_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION14_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION14_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION14_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION14_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION14_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION14_remote_sensor3error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_CALIBRATION24_UNION
 结构说明  : CALIBRATION24 寄存器结构定义。地址偏移量:0x0C4，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度校准寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: ATE 温度校准误差信息，最高位表示符号：
                                                               1：采样温度减去校准误差
                                                               0：采样温度加上校准误差 */
    } reg;
} SOC_Tsensor_CALIBRATION24_UNION;
#endif
#define SOC_Tsensor_CALIBRATION24_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION24_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION24_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION24_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION24_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION24_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION24_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION24_remote_sensor7error_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_CONFIG4_UNION
 结构说明  : TEMP_CONFIG4 寄存器结构定义。地址偏移量:0x0C8，初值:0x00002000，宽度:32
 寄存器说明: Tsensor4模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num4 : 3;  /* bit[0-2]  : Tsensor4通道个数选择：
                                                        0：只有LOCAL SENSOR */
        unsigned int  channel_sel4 : 4;  /* bit[3-6]  : Tsensor4通道模式选择：
                                                        其他——保留 */
        unsigned int  temp_mode4   : 2;  /* bit[7-8]  : Tsensor4同一通道温度采样模式选择：
                                                        00——多次采样取均值
                                                        其他——保留 */
        unsigned int  sample_num4  : 8;  /* bit[9-16] : Tsensor4同一通道采样次数选择，只支持16的整数倍：16、32、64、128、256
                                                        配置值为N，对应采样2*N
                                                        采样值为16、32、64、128、256对应配置值为8、16、32、64、128 */
        unsigned int  ct_sel_apb4  : 2;  /* bit[17-18]: Tsensor4 HKADC转换时间选择：
                                                        00——0.512ms
                                                        01——0.256ms
                                                        10——1.024ms
                                                        11——2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_CONFIG4_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG4_channel_num4_START  (0)
#define SOC_Tsensor_TEMP_CONFIG4_channel_num4_END    (2)
#define SOC_Tsensor_TEMP_CONFIG4_channel_sel4_START  (3)
#define SOC_Tsensor_TEMP_CONFIG4_channel_sel4_END    (6)
#define SOC_Tsensor_TEMP_CONFIG4_temp_mode4_START    (7)
#define SOC_Tsensor_TEMP_CONFIG4_temp_mode4_END      (8)
#define SOC_Tsensor_TEMP_CONFIG4_sample_num4_START   (9)
#define SOC_Tsensor_TEMP_CONFIG4_sample_num4_END     (16)
#define SOC_Tsensor_TEMP_CONFIG4_ct_sel_apb4_START   (17)
#define SOC_Tsensor_TEMP_CONFIG4_ct_sel_apb4_END     (18)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_DET_EN4_UNION
 结构说明  : TEMP_DET_EN4 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度检测使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en4 : 1;  /* bit[0]   : Tsensor4温度采样使能寄存器：
                                                       0：不使能
                                                       1：使能 */
        unsigned int  calib4       : 1;  /* bit[1]   : Tsensor4校准使能位
                                                       1'b1：不开启校准算法
                                                       1'b0：开启校准算法（默认） */
        unsigned int  calib4_en    : 1;  /* bit[2]   : 使能后，能够通过VCALIB1进行电压方式校准；
                                                       1'b0:disable
                                                       1'b1:表示enable
                                                       缺省为“0”；（高电平0.8V） */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_DET_EN4_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN4_temp_det_en4_START  (0)
#define SOC_Tsensor_TEMP_DET_EN4_temp_det_en4_END    (0)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_START        (1)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_END          (1)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_en_END       (2)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_BYPASS4_UNION
 结构说明  : TEMP_WAIT_BYPASS4 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000001，宽度:32
 寄存器说明: Tsensor4温度检测去使能等待寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass4 : 1;  /* bit[0]   : Tsensor4去使能后等待寄存器：
                                                            0：去使能后等待，等待时间可配置
                                                            1：去使能后不等待 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS4_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_temp_wait_bypass4_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_temp_wait_bypass4_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_WAIT_TIME4_UNION
 结构说明  : TEMP_WAIT_TIME4 寄存器结构定义。地址偏移量:0x0D4，初值:0x000001F4，宽度:32
 寄存器说明: Tsensor4温度检测去使能等待时间寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time4 : 32; /* bit[0-31]: 等待时间为N个PCLK周期。N表示此配置值
                                                          默认为500（PCLK为100MHZ时，5us） */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME4_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME4_temp_wait_time4_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME4_temp_wait_time4_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_FSMSTAT4_UNION
 结构说明  : TEMP_FSMSTAT4 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度检测当前状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor4 SAMPLE状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor4 TEMPCTL状态机当前状态
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT4_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT4_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT4_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT4_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT4_s_fsm_stat_END    (7)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP4_UNION
 结构说明  : TEMP4 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp4    : 10; /* bit[0-9]  : Tsensor4温度检测结果寄存器 */
        unsigned int  reserved : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP4_UNION;
#endif
#define SOC_Tsensor_TEMP4_temp4_START     (0)
#define SOC_Tsensor_TEMP4_temp4_END       (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_TH4_UNION
 结构说明  : TEMP_TH4 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度报警门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th4 : 10; /* bit[0-9]  : Tsensor4温度报警门限0 */
        unsigned int  temp_1th4 : 10; /* bit[10-19]: Tsensor4温度报警门限1 */
        unsigned int  temp_2th4 : 10; /* bit[20-29]: Tsensor4温度报警门限2 */
        unsigned int  temp_3th4 : 2;  /* bit[30-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_TH4_UNION;
#endif
#define SOC_Tsensor_TEMP_TH4_temp_0th4_START  (0)
#define SOC_Tsensor_TEMP_TH4_temp_0th4_END    (9)
#define SOC_Tsensor_TEMP_TH4_temp_1th4_START  (10)
#define SOC_Tsensor_TEMP_TH4_temp_1th4_END    (19)
#define SOC_Tsensor_TEMP_TH4_temp_2th4_START  (20)
#define SOC_Tsensor_TEMP_TH4_temp_2th4_END    (29)
#define SOC_Tsensor_TEMP_TH4_temp_3th4_START  (30)
#define SOC_Tsensor_TEMP_TH4_temp_3th4_END    (31)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_TH4_UNION
 结构说明  : TEMP_RST_TH4 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度复位门限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th4 : 10; /* bit[0-9]  : Tsensor4温度复位门限 */
        unsigned int  reserved     : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_TH4_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH4_temp_rst_th4_START  (0)
#define SOC_Tsensor_TEMP_RST_TH4_temp_rst_th4_END    (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_LAG4_UNION
 结构说明  : TEMP_LAG4 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4温度回滞寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag4 : 7;  /* bit[0-6] : Tsensor4温度回滞门限 */
        unsigned int  reserved  : 25; /* bit[7-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_LAG4_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG4_temp_lag4_START  (0)
#define SOC_Tsensor_TEMP_LAG4_temp_lag4_END    (6)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_MSK4_UNION
 结构说明  : TEMP_INT_MSK4 寄存器结构定义。地址偏移量:0x0EC，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk4 : 1;  /* bit[0]   : Tsensor4中断屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK4_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK4_temp_int_msk4_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK4_temp_int_msk4_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_INT_CLR4_UNION
 结构说明  : TEMP_INT_CLR4 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr4 : 1;  /* bit[0]   : Tsensor4中断清除控制BIT：
                                                        1：清除RAW和MSK中断
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR4_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR4_temp_int_clr4_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR4_temp_int_clr4_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RST_MSK4_UNION
 结构说明  : TEMP_RST_MSK4 寄存器结构定义。地址偏移量:0x0F4，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4复位屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk4 : 1;  /* bit[0]   : Tsensor4复位屏蔽控制BIT：
                                                        1：不屏蔽
                                                        0：屏蔽 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK4_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK4_temp_rst_msk4_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK4_temp_rst_msk4_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_RAWINT4_UNION
 结构说明  : TEMP_RAWINT4 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4原始中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint4 : 1;  /* bit[0]   : Tsensor4原始中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_RAWINT4_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT4_temp_rawint4_START  (0)
#define SOC_Tsensor_TEMP_RAWINT4_temp_rawint4_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_MSKINT4_UNION
 结构说明  : TEMP_MSKINT4 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4屏蔽中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint4 : 1;  /* bit[0]   : Tsensor4屏蔽中断：
                                                       1：有中断
                                                       0：无中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_MSKINT4_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT4_temp_mskint4_START  (0)
#define SOC_Tsensor_TEMP_MSKINT4_temp_mskint4_END    (0)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_SOFTCTRL1_UNION
 结构说明  : TEMP_SOFTCTRL1 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1软件控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft1      : 1;  /* bit[0]    : Tsensor1软件控制选择：
                                                          1：软件控制
                                                          0：状态机控制 */
        unsigned int  temp_en1_soft  : 1;  /* bit[1]    : Tsensor1软件控制使能：
                                                          1：使能
                                                          0：不使能 */
        unsigned int  ct_sel1_soft   : 2;  /* bit[2-3]  : Tsensor1软件控制转换速率：
                                                          00——0.512ms
                                                          01——0.256ms
                                                          10——1.024ms
                                                          11——2.048ms */
        unsigned int  test1_soft     : 8;  /* bit[4-11] : Tsensor1软件控制通道选择（只看最低3bit）：
                                                          000：local sensor （default） */
        unsigned int  calib1_soft    : 1;  /* bit[12]   : Tsensor1软件校准使能位
                                                          1'b1：不开启校准算法
                                                          1'b0：开启校准算法（默认） */
        unsigned int  calib1_en_soft : 1;  /* bit[13]   : 软件使能位，使能后，能够通过VCALIB1进行电压方式校准；
                                                          1'b0:disable
                                                          1'b1:表示enable
                                                          缺省为“0”；（高电平0.8V） */
        unsigned int  reserved       : 18; /* bit[14-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL1_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL1_sel_soft1_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL1_sel_soft1_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL1_temp_en1_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL1_temp_en1_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL1_ct_sel1_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL1_ct_sel1_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL1_test1_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL1_test1_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_en_soft_END    (13)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP1_SOFT_UNION
 结构说明  : TEMP1_SOFT 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: Tsensor1软件控制检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp1_soft : 10; /* bit[0-9]  : Tsensor1软件控制温度检测结果寄存器 */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP1_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP1_SOFT_temp1_soft_START  (0)
#define SOC_Tsensor_TEMP1_SOFT_temp1_soft_END    (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_SOFTCTRL2_UNION
 结构说明  : TEMP_SOFTCTRL2 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2软件控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft2      : 1;  /* bit[0]    : Tsensor2软件控制选择：
                                                          1：软件控制
                                                          0：状态机控制 */
        unsigned int  temp_en2_soft  : 1;  /* bit[1]    : Tsensor2软件控制使能：
                                                          1：使能
                                                          0：不使能 */
        unsigned int  ct_sel2_soft   : 2;  /* bit[2-3]  : Tsensor2软件控制转换速率：
                                                          00——0.512ms
                                                          01——0.256ms
                                                          10——1.024ms
                                                          11——2.048ms */
        unsigned int  test2_soft     : 8;  /* bit[4-11] : Tsensor2软件控制通道选择（只看最低3bit）：
                                                          000：local sensor （default） */
        unsigned int  calib2_soft    : 1;  /* bit[12]   : Tsensor2校准使能位
                                                          1'b1：不开启校准算法
                                                          1'b0：开启校准算法（默认） */
        unsigned int  calib2_en_soft : 1;  /* bit[13]   : 软件使能位，使能后，能够通过VCALIB1进行电压方式校准；
                                                          1'b0:disable
                                                          1'b1:表示enable
                                                          缺省为“0”；（高电平0.8V） */
        unsigned int  reserved       : 18; /* bit[14-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL2_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL2_sel_soft2_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL2_sel_soft2_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL2_temp_en2_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL2_temp_en2_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL2_ct_sel2_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL2_ct_sel2_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL2_test2_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL2_test2_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_en_soft_END    (13)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP2_SOFT_UNION
 结构说明  : TEMP2_SOFT 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor2软件控制检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp2_soft : 10; /* bit[0-9]  : Tsensor2软件控制温度检测结果寄存器 */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP2_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP2_SOFT_temp2_soft_START  (0)
#define SOC_Tsensor_TEMP2_SOFT_temp2_soft_END    (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_SOFTCTRL3_UNION
 结构说明  : TEMP_SOFTCTRL3 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3软件控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft3      : 1;  /* bit[0]    : Tsensor3软件控制选择：
                                                          1：软件控制
                                                          0：状态机控制 */
        unsigned int  temp_en3_soft  : 1;  /* bit[1]    : Tsensor3软件控制使能：
                                                          1：使能
                                                          0：不使能 */
        unsigned int  ct_sel3_soft   : 2;  /* bit[2-3]  : Tsensor3软件控制转换速率：
                                                          00——0.512ms
                                                          01——0.256ms
                                                          10——1.024ms
                                                          11——2.048ms */
        unsigned int  test3_soft     : 8;  /* bit[4-11] : Tsensor3软件控制通道选择（只看最低3bit）：
                                                          000：local sensor （default） */
        unsigned int  calib3_soft    : 1;  /* bit[12]   : Tsensor3校准使能位
                                                          1'b1：不开启校准算法
                                                          1'b0：开启校准算法（默认） */
        unsigned int  calib3_en_soft : 1;  /* bit[13]   : 软件使能位，使能后，能够通过VCALIB1进行电压方式校准；
                                                          1'b0:disable
                                                          1'b1:表示enable
                                                          缺省为“0”；（高电平0.8V） */
        unsigned int  reserved       : 18; /* bit[14-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL3_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL3_sel_soft3_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL3_sel_soft3_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL3_temp_en3_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL3_temp_en3_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL3_ct_sel3_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL3_ct_sel3_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL3_test3_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL3_test3_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_en_soft_END    (13)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP3_SOFT_UNION
 结构说明  : TEMP3_SOFT 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: Tsensor3软件控制检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp3_soft : 10; /* bit[0-9]  : Tsensor3软件控制温度检测结果寄存器 */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP3_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP3_SOFT_temp3_soft_START  (0)
#define SOC_Tsensor_TEMP3_SOFT_temp3_soft_END    (9)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP_SOFTCTRL4_UNION
 结构说明  : TEMP_SOFTCTRL4 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4软件控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft4      : 1;  /* bit[0]    : Tsensor4软件控制选择：
                                                          1：软件控制
                                                          0：状态机控制 */
        unsigned int  temp_en4_soft  : 1;  /* bit[1]    : Tsensor4软件控制使能：
                                                          1：使能
                                                          0：不使能 */
        unsigned int  ct_sel4_soft   : 2;  /* bit[2-3]  : Tsensor4软件控制转换速率：
                                                          00——0.512ms
                                                          01——0.256ms
                                                          10——1.024ms
                                                          11——2.048ms */
        unsigned int  test4_soft     : 8;  /* bit[4-11] : Tsensor4软件控制通道选择（只看最低3bit）：
                                                          000：local sensor （default） */
        unsigned int  calib4_soft    : 1;  /* bit[12]   : Tsensor4校准使能位
                                                          1'b1：不开启校准算法
                                                          1'b0：开启校准算法（默认） */
        unsigned int  calib4_en_soft : 1;  /* bit[13]   : 软件使能位，使能后，能够通过VCALIB1进行电压方式校准；
                                                          1'b0:disable
                                                          1'b1:表示enable
                                                          缺省为“0”；（高电平0.8V） */
        unsigned int  reserved       : 18; /* bit[14-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL4_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL4_sel_soft4_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL4_sel_soft4_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL4_temp_en4_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL4_temp_en4_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL4_ct_sel4_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL4_ct_sel4_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL4_test4_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL4_test4_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_en_soft_END    (13)


/*****************************************************************************
 结构名    : SOC_Tsensor_TEMP4_SOFT_UNION
 结构说明  : TEMP4_SOFT 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: Tsensor4软件控制检测结果寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp4_soft : 10; /* bit[0-9]  : Tsensor4软件控制温度检测结果寄存器 */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留位 */
    } reg;
} SOC_Tsensor_TEMP4_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP4_SOFT_temp4_soft_START  (0)
#define SOC_Tsensor_TEMP4_SOFT_temp4_soft_END    (9)






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

#endif /* end of soc_tsensor_interface.h */
