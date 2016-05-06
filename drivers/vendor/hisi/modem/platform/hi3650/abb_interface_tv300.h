/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phy_abb_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-08-06 17:27:13
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月6日
    作    者   : x00347325
    修改内容   : 从《TV300 ABB寄存器描述V1.2(nManager3.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __ABB_INTERFACE_TV300_H__
#define __ABB_INTERFACE_TV300_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define ABB_BASE_ADDR               ( 0x0000 )

/***======================================================================***
                     (1/1) register_define_ssi_reg
 ***======================================================================***/
/* 寄存器说明：RX 2G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             Others：Reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x0)

/* 寄存器说明：RX 2G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass
             1：bypass(默认)
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_2G_DIG_2_UNION */
#define ABB_RX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x1)

/* 寄存器说明：TX 2G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认)
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_2G_DIG_1_UNION */
#define ABB_TX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x2)

/* 寄存器说明：TX 2G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式 (默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_2G_DIG_2_UNION */
#define ABB_TX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x3)

/* 寄存器说明：TX 2G模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_2G_DIG_3_UNION */
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x4)

/* 寄存器说明：CH0 RX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             Others：Reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_CH0_3G_DIG_1_UNION */
#define ABB_RX_CH0_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x5)

/* 寄存器说明：CH0 RX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_CH0_3G_DIG_2_UNION */
#define ABB_RX_CH0_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x6)

/* 寄存器说明：CH0 TX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_CH0_3G_DIG_1_UNION */
#define ABB_TX_CH0_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x7)

/* 寄存器说明：CH0 TX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式(默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_CH0_3G_DIG_2_UNION */
#define ABB_TX_CH0_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x8)

/* 寄存器说明：CH0 TX 3G模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_CH0_3G_DIG_3_UNION */
#define ABB_TX_CH0_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x9)

/* 寄存器说明：CH0 RX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             Others：Reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_CH0_4G_DIG_1_UNION */
#define ABB_RX_CH0_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0xA)

/* 寄存器说明：CH0 RX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_CH0_4G_DIG_2_UNION */
#define ABB_RX_CH0_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0xB)

/* 寄存器说明：CH0 TX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_CH0_4G_DIG_1_UNION */
#define ABB_TX_CH0_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0xC)

/* 寄存器说明：CH0 TX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式(默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_CH0_4G_DIG_2_UNION */
#define ABB_TX_CH0_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0xD)

/* 寄存器说明：CH0 TX 4G模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_CH0_4G_DIG_3_UNION */
#define ABB_TX_CH0_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0xE)

/* 寄存器说明：RX TDS模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             Others：Reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0xF)

/* 寄存器说明：RX TDS模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass
             1：bypass(默认)
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_TDS_DIG_2_UNION */
#define ABB_RX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x10)

/* 寄存器说明：TX TDS模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX模式控制：
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT
             011：TDS(默认)
             Others：CA
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器的bypass信号
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_TDS_DIG_1_UNION */
#define ABB_TX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x11)

/* 寄存器说明：TX TDS模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式(默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_TDS_DIG_2_UNION */
#define ABB_TX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x12)

/* 寄存器说明：TX TDS模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_TDS_DIG_3_UNION */
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x13)

/* 寄存器说明：CH1 RX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             Others：Reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_CH1_4G_DIG_1_UNION */
#define ABB_RX_CH1_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x1A)

/* 寄存器说明：CH1 RX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_CH1_4G_DIG_2_UNION */
#define ABB_RX_CH1_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x1B)

/* 寄存器说明：CH1 TX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_CH1_4G_DIG_1_UNION */
#define ABB_TX_CH1_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x1C)

/* 寄存器说明：CH1 TX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式(默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_CH1_4G_DIG_2_UNION */
#define ABB_TX_CH1_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x1D)

/* 寄存器说明：CH1 TX 4G模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_CH1_4G_DIG_3_UNION */
#define ABB_TX_CH1_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x1E)

/* 寄存器说明：RX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX模式控制：
             000：2G(默认)
             001：3G_SC
             010：4G &amp; ET &amp; APT
             011：3G_DC
             100：TDS
             Others：CA
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x1F)

/* 寄存器说明：RX IDLE模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_IDLE_DIG_2_UNION */
#define ABB_RX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x20)

/* 寄存器说明：TX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_IDLE_DIG_1_UNION */
#define ABB_TX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x21)

/* 寄存器说明：TX IDLE模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式(默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_IDLE_DIG_2_UNION */
#define ABB_TX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x22)

/* 寄存器说明：TX IDLE模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_IDLE_DIG_3_UNION */
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x23)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x24)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x25)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz
            001：28MHz
            010：9.3MHz
            011：18.7MHz
            100：7MHz(默认)
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x26)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x27)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x28)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x29)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz(默认)
            001：28MHz
            010：9.3MHz
            011：18.7MHz
            100：7MHz
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2A)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2B)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2C)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2D)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz
            001：28MHz(默认)
            010：9.3MHz
            011：18.7MHz
            100：7MHz
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2E)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2F)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x30)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x31)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz(默认)
            001：28MHz
            010：9.3MHz
            011：18.7MHz
            100：7MHz
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x32)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x33)

/* 寄存器说明：CH1 RX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x38)

/* 寄存器说明：CH1 RX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x39)

/* 寄存器说明：CH1 TX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz
            001：28MHz(默认)
            010：9.3MHz
            011：18.7MHz
            100：7MHz
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_CH1_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x3A)

/* 寄存器说明：CH1 TX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_CH1_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x3B)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3C)

/* 寄存器说明：IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz
            001：28MHz
            010：9.3MHz
            011：18.7MHz
            100：7MHz(默认)
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3E)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3F)

/* 寄存器说明：version寄存器。
   详      述：由模拟部分决定版本寄存器值
   UNION结构 ：无 */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

/* 寄存器说明：测试模式寄存器。
 bit[7]      数字部分TX通道软复位信号：
             0：不复位(默认)
             1：复位
 bit[6]      数字部分RX通道软复位信号：
             0：不复位(默认)
             1：复位
 bit[5:3]    bit[4:3]测试模式控制：
             00：正常模式(默认)
             01：数字算法逻辑环回模式
             10：RX模拟测试模式(bypass RX数字滤波器)
             11：Reserved
             bit[5]RXC通道测试使能：
             0：正常模式(默认)，RXA通道选择RXA的正常输入数据
             1：RXC通道测试模式(将RXC通道输入数据复用到RXA通道)
 bit[2:1]    RX模拟测试模式下通道选择：
             00：输出RXA I模拟调制器数据(默认)
             01：输出RXA Q模拟调制器数据
             10：输出RXB I模拟调制器数据
             11：输出RXB Q模拟调制器数据
 bit[0]      全局软复位信号：comstarV520 Reserved
             0：不复位(默认)
             1：复位整个数字电路和模拟电路
   UNION结构:  ABB_CH1_TESTMODE_UNION */
#define ABB_CH1_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x41)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      CH1通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
 bit[0]      CH1通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x42)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道I路dc offset设置
   UNION结构 ：无 */
#define ABB_CH1_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x48)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道Q路dc offset设置
   UNION结构 ：无 */
#define ABB_CH1_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x49)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4A)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXA_I_COEF1_UNION */
#define ABB_CH1_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4B)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4C)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXA_I_COEF3_UNION */
#define ABB_CH1_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4E)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4F)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXA_Q_COEF1_UNION */
#define ABB_CH1_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x50)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x51)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXA_Q_COEF3_UNION */
#define ABB_CH1_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x52)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x53)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x54)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXB_I_COEF1_UNION */
#define ABB_CH1_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x55)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x56)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXB_I_COEF3_UNION */
#define ABB_CH1_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x57)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x58)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x59)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXB_Q_COEF1_UNION */
#define ABB_CH1_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x5A)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x5B)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXB_Q_COEF3_UNION */
#define ABB_CH1_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x5C)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x5D)

/* 寄存器说明：RXA通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH1_REG_RXA_DCR_CFG_UNION */
#define ABB_CH1_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x5E)

/* 寄存器说明：RXB通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH1_REG_RXB_DCR_CFG_UNION */
#define ABB_CH1_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x5F)

/* 寄存器说明：BLOCKING DCR功能控制寄存器。
 bit[7:2]    保留
 bit[1]      RXB天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
 bit[0]      RXA天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
   UNION结构:  ABB_CH1_REG_RX_DCR_CTRL_UNION */
#define ABB_CH1_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x60)

/* 寄存器说明：RXA通道BLOCKING上报寄存器。
 bit[7:5]    RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXA天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x61)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXB天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH1_RXB_BLOCKING_UNION */
#define ABB_CH1_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x62)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器1。
   详      述：RXA天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x63)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXA_DC_I_2_UNION */
#define ABB_CH1_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x64)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器1。
   详      述：RXA天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x65)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXA_DC_Q_2_UNION */
#define ABB_CH1_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x66)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器1。
   详      述：RXB天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x67)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXB_DC_I_2_UNION */
#define ABB_CH1_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x68)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器1。
   详      述：RXB天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x69)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXB_DC_Q_2_UNION */
#define ABB_CH1_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x6A)

/* 寄存器说明：数字调试寄存器。
 bit[7]      保留
 bit[6]      TX SD模块主调制器旁路使能：
             0：主调制器不旁路；
             1：主调制器旁路（默认）；
 bit[5]      Tuning code来源选择：
             0：寄存器配置
             1：自动更新（默认）
 bit[4]      TX通道SDM Dither控制：
             0：不使能
             1：使能
 bit[3:2]    TX DEM量化器输入限幅档位。
             00：0.8125
             01：0.796875(默认)
             10：0.765625
             11：0.75
 bit[1]      TX通道DEM校准工作模式
             0：正常工作
             1：校准态，DEM输出为dem_code_man
 bit[0]      TX通道SDM模块异常时复位控制
             0：只复位SDM模块
             1：复位整个TX通道
   UNION结构:  ABB_CH1_REG_DEBUG_DIG0_UNION */
#define ABB_CH1_REG_DEBUG_DIG0_ADDR                   (ABB_BASE_ADDR + 0x6B)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,高位
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_DIG1_ADDR                   (ABB_BASE_ADDR + 0x6C)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,低位
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_DIG2_ADDR                   (ABB_BASE_ADDR + 0x6D)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道SDM模块异常复位计数
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_DIG3_ADDR                   (ABB_BASE_ADDR + 0x6E)

/* 寄存器说明：数字调试寄存器。
   详      述：数字调试寄存器
            bit[7]：模式切换复位长度配置使能
            0：不使能
            1：使能
            bit[6:4]：模式切换复位长度配置值，单位为8 cycles
            bit[3]：Reserved
            bit[2]：TX分频器使能bypass控制
            0：不bypass
            1：bypass
            bit[1]：RX分频器使能bypass控制
            0：不bypass
            1：bypass
            bit[0]：管脚CH1_CLK_52M输出时钟选择
            0：输出CH1_CLK_52M
            1：输出CH1_CLK_61D44M
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0x6F)

/* 寄存器说明：Power Down控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0x70)

/* 寄存器说明：数模接口时钟控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0x71)

/* 寄存器说明：Other控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0x72)

/* 寄存器说明：ADC第一级积分器电容tuning寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0x73)

/* 寄存器说明：ADC第二级积分器电容tuning寄存器。
   详      述：ADC第二级积分器电容tuning
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0x74)

/* 寄存器说明：ADC第三级积分器电容tuning寄存器。
   详      述：ADC第三级积分器电容tuning
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0x75)

/* 寄存器说明：DAC Tuning控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0x76)

/* 寄存器说明：DAC Tuning控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0x77)

/* 寄存器说明：DAC Tuning控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0x78)

/* 寄存器说明：时钟反沿控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0x79)

/* 寄存器说明：DUM控制寄存器。
   详      述：RX DEM Mode Selection,bit 2,和ch0_reg_analog_wr00的bit3和bit0组合成3bit，实现如下9种组合：
            000：DWA
            001：CLA1
            010：CLA2
            011：CLA3
            100：CLA4
            101：CLA5
            110：CLA6
            111：CLA7
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0x7A)

/* 寄存器说明：标志位只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0x7B)

/* 寄存器说明：RC校准只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO1_ADDR                   (ABB_BASE_ADDR + 0x7C)

/* 寄存器说明：模拟只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0x7D)

/* 寄存器说明：模拟只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0x7E)

/* 寄存器说明：模拟只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0x7F)

/* 寄存器说明：模拟调试寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0x80)

/* 寄存器说明：PLL LOCK控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0x81)

/* 寄存器说明：PLL控制寄存器。
   详      述：反相时钟开关
            1：反相时钟打开
            0：反相时钟关闭
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0x82)

/* 寄存器说明：PLL控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0x83)

/* 寄存器说明：PLL控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0x84)

/* 寄存器说明：快速启动控制寄存器。
   详      述：ABB_REF_Fast_UP控制
            0：关闭(默认)
            1：开启
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0x85)

/* 寄存器说明：Bandgap和TCXO控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0x86)

/* 寄存器说明：电流控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0x87)

/* 寄存器说明：电流控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0x88)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0x89)

/* 寄存器说明：ADC复位控制寄存器。
   详      述：ADC中RST_CAP控制
            0：Reset CAP123
            1：不Reset CAP123
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0x8A)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0x8B)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0x8C)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0x8D)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0x8E)

/* 寄存器说明：ADC延迟控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0x8F)

/* 寄存器说明：ADC控制寄存器。
   详      述：RX输出PDM编码控制
            0：adder encoder，加法译码输出
            1：de-bubble encoder，二进制译码输出
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0x90)

/* 寄存器说明：PLL测试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0x91)

/* 寄存器说明：TX手工码寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0x92)

/* 寄存器说明：时钟使能控制寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0x93)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0x94)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0x95)

/* 寄存器说明：模拟调试寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0x96)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0x97)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0x98)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0x99)

/* 寄存器说明：模拟调试寄存器。
   详      述：ADC积分器1电容控制码，为FF Corner准备的额外补充码
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0x9A)

/* 寄存器说明：模拟调试只读寄存器。
   详      述：RXA I通道OP1 Offset校正是否结束标志位
            0：未完成
            1：校准完成
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0x9B)

/* 寄存器说明：version寄存器。
   详      述：由模拟部分决定版本寄存器值
   UNION结构 ：无 */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)

/* 寄存器说明：测试模式寄存器。
 bit[7]      数字部分TX通道软复位信号：
             0：不复位(默认)
             1：复位
 bit[6]      数字部分RX通道软复位信号：
             0：不复位(默认)
             1：复位
 bit[5:3]    bit[4:3]测试模式控制：
             00：正常模式(默认)
             01：数字算法逻辑环回模式
             10：RX模拟测试模式(bypass RX数字滤波器)
             11：数字/模拟接口环回
             bit[5]RXC通道测试使能：（ComstarV510 reserved）
             0：正常模式(默认)，RXA通道选择RXA的正常输入数据
             1：RXC通道测试模式(将RXC通道输入数据复用到RXA通道)
 bit[2:1]    RX模拟测试模式下通道选择：
             00：输出RXA I模拟调制器数据(默认)
             01：输出RXA Q模拟调制器数据
             10：输出RXB I模拟调制器数据
             11：输出RXB Q模拟调制器数据
 bit[0]      全局软复位信号：
             0：不复位(默认)
             1：复位整个数字电路和模拟电路
   UNION结构:  ABB_CH0_TESTMODE_UNION */
#define ABB_CH0_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0xA1)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      CH0通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
 bit[0]      CH0通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0xA2)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道I路dc offset设置
   UNION结构 ：无 */
#define ABB_CH0_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0xA8)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道Q路dc offset设置
   UNION结构 ：无 */
#define ABB_CH0_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0xA9)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0xAA)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXA_I_COEF1_UNION */
#define ABB_CH0_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0xAB)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0xAC)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXA_I_COEF3_UNION */
#define ABB_CH0_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0xAD)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0xAE)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0xAF)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXA_Q_COEF1_UNION */
#define ABB_CH0_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0xB0)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0xB1)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXA_Q_COEF3_UNION */
#define ABB_CH0_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0xB2)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0xB3)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0xB4)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXB_I_COEF1_UNION */
#define ABB_CH0_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0xB5)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0xB6)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXB_I_COEF3_UNION */
#define ABB_CH0_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0xB7)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0xB8)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0xB9)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXB_Q_COEF1_UNION */
#define ABB_CH0_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0xBA)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0xBB)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXB_Q_COEF3_UNION */
#define ABB_CH0_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0xBC)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0xBD)

/* 寄存器说明：RXA通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH0_REG_RXA_DCR_CFG_UNION */
#define ABB_CH0_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0xBE)

/* 寄存器说明：RXB通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH0_REG_RXB_DCR_CFG_UNION */
#define ABB_CH0_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0xBF)

/* 寄存器说明：BLOCKING DCR功能控制寄存器。
 bit[7:2]    保留
 bit[1]      RXB天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
 bit[0]      RXA天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
   UNION结构:  ABB_CH0_REG_RX_DCR_CTRL_UNION */
#define ABB_CH0_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0xC0)

/* 寄存器说明：RXA通道BLOCKING上报寄存器。
 bit[7:5]    RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXA天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0xC1)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXB天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH0_RXB_BLOCKING_UNION */
#define ABB_CH0_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0xC2)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器1。
   详      述：RXA天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC3)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC4)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器1。
   详      述：RXA天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC5)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xC6)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器1。
   详      述：RXB天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC7)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC8)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器1。
   详      述：RXB天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC9)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xCA)

/* 寄存器说明：数字调试寄存器。
 bit[7]      保留
 bit[6]      TX SD模块主调制器旁路使能：
             0：主调制器不旁路；
             1：主调制器旁路（默认）；
 bit[5]      Tuning code来源选择：
             0：寄存器配置
             1：自动更新（默认）
 bit[4]      TX通道SDM Dither控制：
             0：不使能
             1：使能
 bit[3:2]    TX DEM量化器输入限幅档位。
             00：0.8125
             01：0.796875(默认)
             10：0.765625
             11：0.75
 bit[1]      TX通道DEM校准工作模式
             0：正常工作
             1：校准态，DEM输出为dem_code_man
 bit[0]      TX通道SDM模块异常时复位控制
             0：只复位SDM模块
             1：复位整个TX通道
   UNION结构:  ABB_CH0_REG_DEBUG_DIG0_UNION */
#define ABB_CH0_REG_DEBUG_DIG0_ADDR                   (ABB_BASE_ADDR + 0xCB)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,高位
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_DIG1_ADDR                   (ABB_BASE_ADDR + 0xCC)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,低位
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_DIG2_ADDR                   (ABB_BASE_ADDR + 0xCD)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道SDM模块异常复位计数
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_DIG3_ADDR                   (ABB_BASE_ADDR + 0xCE)

/* 寄存器说明：数字调试寄存器。
   详      述：数字调试寄存器
            bit[7]：模式切换复位长度配置使能
            0：不使能
            1：使能
            bit[6:4]：模式切换复位长度配置值，单位为8 cycles
            bit[3]：Reserved
            bit[2]：TX分频器使能bypass控制
            0：不bypass
            1：bypass
            bit[1]：RX分频器使能bypass控制
            0：不bypass
            1：bypass
            bit[0]：管脚CH0_CLK_52M输出时钟选择
            0：输出CH0_CLK_52M
            1：输出CH0_CLK_61D44M
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0xCF)

/* 寄存器说明：Power Down控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0xD0)

/* 寄存器说明：数模接口时钟控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0xD1)

/* 寄存器说明：Other控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0xD2)

/* 寄存器说明：ADC第一级积分器电容tuning寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0xD3)

/* 寄存器说明：ADC第二级积分器电容tuning寄存器。
   详      述：ADC第二级积分器电容tuning
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0xD4)

/* 寄存器说明：ADC第三级积分器电容tuning寄存器。
   详      述：ADC第三级积分器电容tuning
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0xD5)

/* 寄存器说明：DAC Tuning控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0xD6)

/* 寄存器说明：DAC Tuning控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0xD7)

/* 寄存器说明：DAC Tuning控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0xD8)

/* 寄存器说明：时钟反沿控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0xD9)

/* 寄存器说明：DUM控制寄存器。
   详      述：RX DEM Mode Selection,bit 2,和ch0_reg_analog_wr00的bit3和bit0组合成3bit，实现如下9种组合：
            000：DWA
            001：CLA1
            010：CLA2
            011：CLA3
            100：CLA4
            101：CLA5
            110：CLA6
            111：CLA7
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0xDA)

/* 寄存器说明：标志位只读寄存器。
   详      述：WPLL的LOCK信号
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0xDB)

/* 寄存器说明：RC校准只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO1_ADDR                   (ABB_BASE_ADDR + 0xDC)

/* 寄存器说明：模拟只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0xDD)

/* 寄存器说明：模拟只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0xDE)

/* 寄存器说明：模拟只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0xDF)

/* 寄存器说明：模拟调试寄存器。
   详      述：GPLL VCO Current控制
            00：X1.2
            01：X1.1(默认)
            10：X1.1
            11：X1.0
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0xE0)

/* 寄存器说明：PLL LOCK控制寄存器。
   详      述：WPLL VCO Current控制
            00：X0.7
            01：X1(默认)
            10：X1
            11：X1.3
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0xE1)

/* 寄存器说明：PLL控制寄存器。
   详      述：反相时钟开关
            1：反相时钟打开
            0：反相时钟关闭
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0xE2)

/* 寄存器说明：PLL控制寄存器。
   详      述：GPLL电荷泵电流控制(低有效)
            0000：4u
            0001：6u
            0010：8u
            0011：10u(默认)
            0100：12u
            0101：14u
            0110：16u
            0111：18u
            ……
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0xE3)

/* 寄存器说明：PLL控制寄存器。
   详      述：WPLL电荷泵电流控制(低有效)
            0000：4u
            0001：6u
            0010：8u
            0011：10u(默认)
            0100：12u
            0101：14u
            0110：16u
            0111：18u
            ……
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0xE4)

/* 寄存器说明：快速启动控制寄存器。
   详      述：ABB_REF_Fast_UP控制
            0：关闭(默认)
            1：开启
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0xE5)

/* 寄存器说明：Bandgap和TCXO控制寄存器。
   详      述：reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0xE6)

/* 寄存器说明：电流控制寄存器。
   详      述：reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0xE7)

/* 寄存器说明：电流控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0xE8)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0xE9)

/* 寄存器说明：ADC复位控制寄存器。
   详      述：ADC中RST_CAP控制
            0：Reset CAP123
            1：不Reset CAP123
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xEA)

/* 寄存器说明：ADC控制寄存器。
   详      述：Refence分压模块强制PD信号
            0： Reference分压模块状态由BG_EN信号及其它模块PD信号自动控制
            1： Reference分压模块强制Power Down
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xEB)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xEC)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xED)

/* 寄存器说明：ADC控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xEE)

/* 寄存器说明：ADC延迟控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xEF)

/* 寄存器说明：ADC控制寄存器。
   详      述：RX输出PDM编码控制
            0：adder encoder，加法译码输出
            1：de-bubble encoder，二进制译码输出
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xF0)

/* 寄存器说明：PLL测试寄存器。
   详      述：PLL控制电压测试PAD信号选择
            00/11：控制电压测试PAD浮空
            01：GPLL输出控制电压到PAD
            10：WPLL输出控制电压到PAD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xF1)

/* 寄存器说明：TX手工码寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xF2)

/* 寄存器说明：时钟使能控制寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xF3)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xF4)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xF5)

/* 寄存器说明：模拟调试寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xF6)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xF7)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xF8)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xF9)

/* 寄存器说明：模拟调试寄存器。
   详      述：ADC积分器1电容控制码，为FF Corner准备的额外补充码
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xFA)

/* 寄存器说明：模拟调试只读寄存器。
   详      述：RXA I通道OP1 Offset校正是否结束标志位
            0：未完成
            1：校准完成
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0xFB)

/* 寄存器说明：SINE发送寄存器。
 bit[7:4]    正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f
 bit[3:2]    正弦波发送幅度控制
             00：满量程
             01：3/4量程
             10：1/2量程
             11：1/4量程
 bit[1]      ch1正弦波发送使能
             0：不发送
             1：发送
 bit[0]      ch0正弦波发送使能
             0：不发送
             1：发送
   UNION结构:  ABB_SINE_GENERATE_UNION */
#define ABB_SINE_GENERATE_ADDR                        (ABB_BASE_ADDR + 0xFF)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x100)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x101)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x102)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x103)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x104)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x105)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x106)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x107)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x108)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x109)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10A)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10B)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10C)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10D)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10E)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10F)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x110)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x111)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x112)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x113)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x114)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x115)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x116)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x117)

/* 寄存器说明：CH1 TX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_CH1_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x118)

/* 寄存器说明：CH1 TX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH1_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x119)

/* 寄存器说明：CH1 TX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH1_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x11A)

/* 寄存器说明：CH1 RX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x11B)

/* 寄存器说明：CH1 RX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x11C)

/* 寄存器说明：CH1 RX 4G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x11D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12A)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12B)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12C)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12D)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12E)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12F)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0x130)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0x131)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0x132)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0x133)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0x134)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA32_ADDR                  (ABB_BASE_ADDR + 0x135)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA33_ADDR                  (ABB_BASE_ADDR + 0x136)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA34_ADDR                  (ABB_BASE_ADDR + 0x137)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA35_ADDR                  (ABB_BASE_ADDR + 0x138)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA36_ADDR                  (ABB_BASE_ADDR + 0x139)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA37_ADDR                  (ABB_BASE_ADDR + 0x13A)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA38_ADDR                  (ABB_BASE_ADDR + 0x13B)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA39_ADDR                  (ABB_BASE_ADDR + 0x13C)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA40_ADDR                  (ABB_BASE_ADDR + 0x13D)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA41_ADDR                  (ABB_BASE_ADDR + 0x13E)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
            ComstarV511_Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA42_ADDR                  (ABB_BASE_ADDR + 0x13F)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0x140)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0x141)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0x142)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0x143)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0x144)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA32_ADDR                  (ABB_BASE_ADDR + 0x145)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA33_ADDR                  (ABB_BASE_ADDR + 0x146)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA34_ADDR                  (ABB_BASE_ADDR + 0x147)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA35_ADDR                  (ABB_BASE_ADDR + 0x148)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA36_ADDR                  (ABB_BASE_ADDR + 0x149)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA37_ADDR                  (ABB_BASE_ADDR + 0x14A)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA38_ADDR                  (ABB_BASE_ADDR + 0x14B)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA39_ADDR                  (ABB_BASE_ADDR + 0x14C)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA40_ADDR                  (ABB_BASE_ADDR + 0x14D)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA41_ADDR                  (ABB_BASE_ADDR + 0x14E)

/* 寄存器说明：模拟调试寄存器。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA42_ADDR                  (ABB_BASE_ADDR + 0x14F)

/* 寄存器说明：CH1 RX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             Others：Reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_CH1_3G_DIG_1_UNION */
#define ABB_RX_CH1_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x180)

/* 寄存器说明：CH1 RX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_CH1_3G_DIG_2_UNION */
#define ABB_RX_CH1_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x181)

/* 寄存器说明：CH1 TX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_CH1_3G_DIG_1_UNION */
#define ABB_TX_CH1_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x182)

/* 寄存器说明：CH1 TX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式(默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_CH1_3G_DIG_2_UNION */
#define ABB_TX_CH1_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x183)

/* 寄存器说明：CH1 TX 3G模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_CH1_3G_DIG_3_UNION */
#define ABB_TX_CH1_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x184)

/* 寄存器说明：CH1 RX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x185)

/* 寄存器说明：CH1 RX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x186)

/* 寄存器说明：CH1 RX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x187)

/* 寄存器说明：CH1 RX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x188)

/* 寄存器说明：CH1 RX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x189)

/* 寄存器说明：CH1 TX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz(默认)
            001：28MHz
            010：9.3MHz
            011：18.7MHz
            100：7MHz
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_CH1_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x18A)

/* 寄存器说明：CH1 RX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_CH1_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x18B)

/* 寄存器说明：CH1 TX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_CH1_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x18C)

/* 寄存器说明：CH1 TX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH1_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x18D)

/* 寄存器说明：CH1 TX 3G配置寄存器，经过线控逻辑后送至ch1_reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_CH1_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x18E)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x18F)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x190)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x191)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_9_ADDR                          (ABB_BASE_ADDR + 0x192)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_10_ADDR                         (ABB_BASE_ADDR + 0x193)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_11_ADDR                         (ABB_BASE_ADDR + 0x194)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x195)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x196)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x197)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x198)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x199)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH0_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x19A)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x19B)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x19C)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x19D)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x19E)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x19F)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH0_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x1A0)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_6_ADDR                         (ABB_BASE_ADDR + 0x1A1)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_7_ADDR                         (ABB_BASE_ADDR + 0x1A2)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_8_ADDR                         (ABB_BASE_ADDR + 0x1A3)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_9_ADDR                         (ABB_BASE_ADDR + 0x1A4)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_10_ADDR                        (ABB_BASE_ADDR + 0x1A5)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_11_ADDR                        (ABB_BASE_ADDR + 0x1A6)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_6_ADDR                        (ABB_BASE_ADDR + 0x1A7)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_7_ADDR                        (ABB_BASE_ADDR + 0x1A8)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_8_ADDR                        (ABB_BASE_ADDR + 0x1A9)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_9_ADDR                        (ABB_BASE_ADDR + 0x1AA)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_10_ADDR                       (ABB_BASE_ADDR + 0x1AB)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_11_ADDR                       (ABB_BASE_ADDR + 0x1AC)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x1AD)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x1AE)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x1AF)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x1B1)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x1B2)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH1_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x1B3)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x1B4)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x1B5)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x1B6)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x1B7)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x1B8)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_CH1_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x1B9)

/* 寄存器说明：线控强制配置使能。
 bit[7]      保留
 bit[6]      TX通道强配线控
 bit[5]      RXB通道强配线控
 bit[4]      RXA通道强配线控
 bit[3]      保留
 bit[2]      TX通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
 bit[1]      RXB通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
 bit[0]      RXA通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
   UNION结构:  ABB_CH1_LINE_SEL_UNION */
#define ABB_CH1_LINE_SEL_ADDR                         (ABB_BASE_ADDR + 0x1C0)

/* 寄存器说明：模式线控强制配置。
 bit[7]      保留
 bit[6]      线控信号CH1_LINE_CTRL_MODE强制配置使能
 bit[5:3]    线控信号CH1_RX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：ET模式
             6：APT模式
             7：CA模式
 bit[2:0]    线控信号CH1_TX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：ET模式
             6：APT模式
             7：CA模式
   UNION结构:  ABB_CH1_LINE_CFG_UNION */
#define ABB_CH1_LINE_CFG_ADDR                         (ABB_BASE_ADDR + 0x1C1)

/* 寄存器说明：时钟门控寄存器。
 bit[7:3]    保留
 bit[2]      线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能
 bit[1]      线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值
 bit[0]      BLOCKING自动门控使能：
             0：使能
             1：不使能
   UNION结构:  ABB_CH1_CLK_SEL_UNION */
#define ABB_CH1_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1C2)

/* 寄存器说明：线控强制配置使能。
 bit[7]      保留
 bit[6]      TX通道强配线控
 bit[5]      RXB通道强配线控
 bit[4]      RXA通道强配线控
 bit[3]      保留
 bit[2]      TX通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
 bit[1]      RXB通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
 bit[0]      RXA通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
   UNION结构:  ABB_CH0_LINE_SEL_UNION */
#define ABB_CH0_LINE_SEL_ADDR                         (ABB_BASE_ADDR + 0x1D0)

/* 寄存器说明：模式线控强制配置。
 bit[7]      保留
 bit[6]      线控信号CH0_LINE_CTRL_MODE强制配置使能
 bit[5:3]    线控信号CH0_RX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：ET模式
             6：APT模式
             7：CA模式
 bit[2:0]    线控信号CH0_TX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：ET模式
             6：APT模式
             7：CA模式
   UNION结构:  ABB_CH0_LINE_CFG_UNION */
#define ABB_CH0_LINE_CFG_ADDR                         (ABB_BASE_ADDR + 0x1D1)

/* 寄存器说明：时钟门控寄存器。
 bit[7:3]    保留
 bit[2]      线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能
 bit[1]      线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值
 bit[0]      BLOCKING自动门控使能：
             0：使能
             1：不使能
   UNION结构:  ABB_CH0_CLK_SEL_UNION */
#define ABB_CH0_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1D2)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1E0)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_LINE_RPT1_ADDR                        (ABB_BASE_ADDR + 0x1E1)

/* 寄存器说明：RX数字工作模式上报寄存器。
   详      述：RX通道模式控制上报：
            000：2G(默认)
            001：3G_SC
            010：4G &amp; ET &amp; APT
            011：3G_DC
            100：TDS
            Others：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1E2)

/* 寄存器说明：TX数字工作模式上报寄存器。
   详      述：TX通道模式控制上报：
            000：2G(默认)
            001：3G
            010：4G &amp; ET &amp; APT
            011：TDS
            Others：CA
   UNION结构 ：无 */
#define ABB_CH1_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1E3)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1E4)

/* 寄存器说明：TX数字工作状态上报寄存器。
   详      述：TX通道FIFO读空状态
   UNION结构 ：无 */
#define ABB_CH1_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1E5)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1F0)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_LINE_RPT1_ADDR                        (ABB_BASE_ADDR + 0x1F1)

/* 寄存器说明：RX数字工作模式上报寄存器。
   详      述：RX通道模式控制：
            000：2G(默认)
            001：3G_SC/TDS_B/4G_C
            010：4G
            011：3G_DC/4G_B
            100：TDS
            101：CDMA
            Others：Reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F2)

/* 寄存器说明：TX数字工作模式上报寄存器。
   详      述：TX通道模式控制：
            000：2G(默认)
            001：3G
            010：4G
            011：TDS
            100：CDMA
            Others：Reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F3)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1F4)

/* 寄存器说明：TX数字工作状态上报寄存器。
   详      述：TX通道FIFO读空状态
   UNION结构 ：无 */
#define ABB_CH0_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1F5)

/* 寄存器说明：RXB通道选择。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RXB_CH_SEL_ADDR                           (ABB_BASE_ADDR + 0x1F6)

/* 寄存器说明：通道0 TDS配置寄存器。
 bit[7:3]    保留
 bit[2:0]    通道0 TDS模式定时调整配置寄存器，配置值和时延关系为
             0: delay 0 chip
             1: delay 4/120 chips
             2: delay 8/120 chips
             3: delay 11/120 chips
             4: delay 15/120 chips
             5: delay 19/120 chips
             6: delay 23/120 chips
             7: delay 26/120 chips
   UNION结构:  ABB_CH0_TDS_RX_DLY_UNION */
#define ABB_CH0_TDS_RX_DLY_ADDR                       (ABB_BASE_ADDR + 0x200)

/* 寄存器说明：通道0配置寄存器。
   详      述：通道0 flush宽度[7:0]，单位为19.2M时钟周期。
   UNION结构 ：无 */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x232)

/* 寄存器说明：通道0配置寄存器。
 bit[7:3]    通道0 FLUSH值，默认为8。
 bit[2:0]    通道0 flush宽度[10:8]，单位为19.2M时钟周期。
   UNION结构:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x233)

/* 寄存器说明：通道1 TDS配置寄存器。
 bit[7:3]    保留
 bit[2:0]    通道1 TDS模式定时调整配置寄存器，配置值和时延关系为
             0: delay 0 chip
             1: delay 4/120 chips
             2: delay 8/120 chips
             3: delay 11/120 chips
             4: delay 15/120 chips
             5: delay 19/120 chips
             6: delay 23/120 chips
             7: delay 26/120 chips
   UNION结构:  ABB_CH1_TDS_RX_DLY_UNION */
#define ABB_CH1_TDS_RX_DLY_ADDR                       (ABB_BASE_ADDR + 0x262)

/* 寄存器说明：通道1配置寄存器。
   详      述：通道1 flush宽度[7:0]，单位为19.2M时钟周期。
   UNION结构 ：无 */
#define ABB_CH1_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x294)

/* 寄存器说明：通道1配置寄存器。
 bit[7:3]    通道1 FLUSH值，默认为8。
 bit[2:0]    通道1 flush宽度[10:8]，单位为19.2M时钟周期。
   UNION结构:  ABB_CH1_FLUSH_CFG1_UNION */
#define ABB_CH1_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x295)

/* 寄存器说明：RX C模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA(默认)
             Others：Reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：reserved。
   UNION结构:  ABB_RX_C_DIG_1_UNION */
#define ABB_RX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x400)

/* 寄存器说明：RX C模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。
 bit[6]      RX通道FLUSH使能：
             0：不使能
             1：使能
 bit[5]      RX通道随路时钟RX_CLK反向使能：
             0：正常
             1：反向
 bit[4]      RX通道补偿滤波器bypass控制：
             0：不bypass
             1：bypass(默认)
 bit[3:2]    RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[1]      RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[0]      RXA通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构:  ABB_RX_C_DIG_2_UNION */
#define ABB_RX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x401)

/* 寄存器说明：TX C模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认)
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_C_DIG_1_UNION */
#define ABB_TX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x402)

/* 寄存器说明：TX C模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式
             1：使用DWA模式 (默认)
 bit[4]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[3:2]    TX通道DEM const系数：
             0：0(默认)
             1：2
             2：4
             3：6
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_C_DIG_2_UNION */
#define ABB_TX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x403)

/* 寄存器说明：TX C模式配置寄存器3，由线控决定是否起作用。
 bit[7:4]    保留
 bit[3:2]    TX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：可配系数。
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      保留
   UNION结构:  ABB_TX_C_DIG_3_UNION */
#define ABB_TX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x404)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr00。
   详      述：RXA_I ADC Power Down控制
            0：Power On
            1：Power Down(默认)
            (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
   UNION结构 ：无 */
#define ABB_RX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x405)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr01。
   详      述：Current Seting For Mode
            1x：LTE mode Current
            01：3G_DC &amp; X mode Current
            00：3G &amp; 2G mode Current
   UNION结构 ：无 */
#define ABB_RX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x406)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr53。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x407)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr54。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x408)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr55。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x409)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr56。
   详      述：BWCT_OP1 OP1带宽控制
            1x： LTE模式
            01： WDC &amp; X 模式
            00： W &amp; G模式
   UNION结构 ：无 */
#define ABB_RX_C_ANA_6_ADDR                           (ABB_BASE_ADDR + 0x40A)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr57。
   详      述：反馈子DAC偏置电流控制
            0 大电流，噪声性能好
            1 小电流，噪声性能差
   UNION结构 ：无 */
#define ABB_RX_C_ANA_7_ADDR                           (ABB_BASE_ADDR + 0x40B)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr58。
   详      述：保留
   UNION结构 ：无 */
#define ABB_RX_C_ANA_8_ADDR                           (ABB_BASE_ADDR + 0x40C)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
            2'b00：2560chip。(W模默认)
            2'b01：512chip。
            2'b10：1024chip。(X模默认)
            2'b11：2048chip。
   UNION结构 ：无 */
#define ABB_RX_C_ANA_9_ADDR                           (ABB_BASE_ADDR + 0x40D)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_C_ANA_10_ADDR                          (ABB_BASE_ADDR + 0x40E)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_C_ANA_11_ADDR                          (ABB_BASE_ADDR + 0x40F)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr48。
   详      述：TX LPF截止频率选择(由tx_XX_ana_2<6>,tx_XX_ana_1<7:6>组成)：
            000：14MHz(默认)
            001：28MHz
            010：9.3MHz
            011：18.7MHz
            100：7MHz
            101：14MHz
            110：28MHz
            111：56MHz
            默认配置方法：
            4G:001   2G:100   Others:000
   UNION结构 ：无 */
#define ABB_TX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x410)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr49。
   详      述：{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
   UNION结构 ：无 */
#define ABB_TX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x411)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr50。
   详      述：TX 采样时钟沿选择：
            0：正沿(默认)
            1：反沿
   UNION结构 ：无 */
#define ABB_TX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x412)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x413)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x414)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:6]    保留
 bit[5:0]    TX补偿滤波器系数C0,6bit有符号数
   UNION结构:  ABB_TX_COEF1_UNION */
#define ABB_TX_COEF1_ADDR                             (ABB_BASE_ADDR + 0x415)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C1,8bit有符号数
   UNION结构 ：无 */
#define ABB_TX_COEF2_ADDR                             (ABB_BASE_ADDR + 0x416)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C2低8位,10bit有符号数
   UNION结构 ：无 */
#define ABB_TX_COEF3_ADDR                             (ABB_BASE_ADDR + 0x417)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:2]    保留
 bit[1:0]    TX补偿滤波器系数C2高2位,10bit有符号数
   UNION结构:  ABB_TX_COEF4_UNION */
#define ABB_TX_COEF4_ADDR                             (ABB_BASE_ADDR + 0x418)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C3低8位,10bit无符号数
   UNION结构 ：无 */
#define ABB_TX_COEF5_ADDR                             (ABB_BASE_ADDR + 0x419)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:2]    保留
 bit[1:0]    TX补偿滤波器系数C3高2位,10bit无符号数
   UNION结构:  ABB_TX_COEF6_UNION */
#define ABB_TX_COEF6_ADDR                             (ABB_BASE_ADDR + 0x41A)

/* 寄存器说明：delay长度选择信号
 bit[7:6]    保留
 bit[5:4]    Delay2的选择信号：
             00：20us；
             01：50us；
             10：200us；
             11：500us。
 bit[3:2]    保留
 bit[1:0]    Delay1的选择信号：
             00：50us；
             01：100us；
             10：200us；
             11：500us。
   UNION结构:  ABB_BIST_DELAY_SEL_UNION */
#define ABB_BIST_DELAY_SEL_ADDR                       (ABB_BASE_ADDR + 0x500)

/* 寄存器说明：模式bypass信号
 bit[7]      保留
 bit[6:0]    模式bypass信号，每种模式占一个bit
             [0]：1表示G模的BIST被bypass；0表示G模的BIST正常工作。
             [1]：1表示WCDMA模SC的BIST被bypass；0表示WCDMA模SC的BIST正常工作。
             [2]：1表示WCDMA模DC的BIST被bypass；0表示WCDMA模DC的BIST正常工作。
             [3]：1表示LTE模的BIST被bypass；0表示LTE模的BIST正常工作。
             [4]：1表示ET模的BIST被bypass；0表示ET模的BIST正常工作。
             [5]：1表示CA模的BIST被bypass；0表示CA模的BIST正常工作。
             [6]：1表示CDMA模的BIST被bypass；0表示CDMA模的BIST正常工作。
   UNION结构:  ABB_BIST_MODE_BYPASS_UNION */
#define ABB_BIST_MODE_BYPASS_ADDR                     (ABB_BASE_ADDR + 0x501)

/* 寄存器说明：Rx的bypass信号
 bit[7:4]    保留
 bit[3:0]    Rx的bypass信号：
             [0]：Rx_1的bypass信号，0表示需要做Rx_1的BIST；1表示不做。
             [1]：Rx_2的bypass信号，0表示需要做Rx_2的BIST；1表示不做。
             [2]：Rx_3的bypass信号，0表示需要做Rx_3的BIST；1表示不做。
             [3]：Rx_4的bypass信号，0表示需要做Rx_4的BIST；1表示不做。
   UNION结构:  ABB_BIST_RX_BYPASS_UNION */
#define ABB_BIST_RX_BYPASS_ADDR                       (ABB_BASE_ADDR + 0x502)

/* 寄存器说明：BIST工作使能信号
 bit[7:2]    保留
 bit[1]      BIST时钟门控使能信号，0表示时钟门控有效；1表示时钟门控旁路。
 bit[0]      BIST工作使能信号，该信号为电平信号。
   UNION结构:  ABB_ABB_BIST_EN_UNION */
#define ABB_ABB_BIST_EN_ADDR                          (ABB_BASE_ADDR + 0x503)

/* 寄存器说明：测试状态
 bit[7:1]    保留
 bit[0]      1：测试结束 0：正在测试（en上升沿清0）
   UNION结构:  ABB_BIST_SNDR_CAL_DONE_UNION */
#define ABB_BIST_SNDR_CAL_DONE_ADDR                   (ABB_BASE_ADDR + 0x504)

/* 寄存器说明：计算出的6个参数是否pass
 bit[7:6]    保留
 bit[5:0]    每一次计算出的6个参数是否pass：
             [0]:1表示DC_I指标pass；0表示不pass；
             [1]:1表示DC_Q指标pass；0表示不pass；
             [2]:1表示SNDR_I指标pass；0表示不pass；
             [3]:1表示SNDR_Q指标pass；0表示不pass；
             [4]:1表示GAIN_MISMATCH指标pass；0表示不pass；
             [5]:1表示GAIN_ERROR指标pass；0表示不pass；
   UNION结构:  ABB_BIST_PARA_PASS_FLAG_UNION */
#define ABB_BIST_PARA_PASS_FLAG_ADDR                  (ABB_BASE_ADDR + 0x505)

/* 寄存器说明：Rx_1的Bist结算结果
 bit[7]      保留
 bit[6:0]    Rx_1的Bist结算结果，每种模式1bit：
             [0]：1表示G模的BIST pass；0表示G模的BIST fail。
             [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
             [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
             [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
             [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
             [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
             [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
   UNION结构:  ABB_ABB_BIST_PASS_FLAG_1_UNION */
#define ABB_ABB_BIST_PASS_FLAG_1_ADDR                 (ABB_BASE_ADDR + 0x506)

/* 寄存器说明：Rx_2的Bist结算结果
 bit[7]      保留
 bit[6:0]    Rx_2的Bist结算结果，每种模式1bit：
             [0]：1表示G模的BIST pass；0表示G模的BIST fail。
             [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
             [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
             [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
             [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
             [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
             [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
   UNION结构:  ABB_ABB_BIST_PASS_FLAG_2_UNION */
#define ABB_ABB_BIST_PASS_FLAG_2_ADDR                 (ABB_BASE_ADDR + 0x507)

/* 寄存器说明：Rx_3的Bist结算结果
 bit[7]      保留
 bit[6:0]    Rx_3的Bist结算结果，每种模式1bit：
             [0]：1表示G模的BIST pass；0表示G模的BIST fail。
             [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
             [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
             [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
             [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
             [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
             [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
   UNION结构:  ABB_ABB_BIST_PASS_FLAG_3_UNION */
#define ABB_ABB_BIST_PASS_FLAG_3_ADDR                 (ABB_BASE_ADDR + 0x508)

/* 寄存器说明：Rx_4的Bist结算结果
 bit[7]      保留
 bit[6:0]    Rx_4的Bist结算结果，每种模式1bit：
             [0]：1表示G模的BIST pass；0表示G模的BIST fail。
             [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
             [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
             [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
             [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
             [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
             [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
   UNION结构:  ABB_ABB_BIST_PASS_FLAG_4_UNION */
#define ABB_ABB_BIST_PASS_FLAG_4_ADDR                 (ABB_BASE_ADDR + 0x509)

/* 寄存器说明：I路DC上报低8位结果
   详      述：I路DC上报低8位，I路DC上报为11bit有符号数。
   UNION结构 ：无 */
#define ABB_BIST_DC_I_1_ADDR                          (ABB_BASE_ADDR + 0x50A)

/* 寄存器说明：I路DC上报高3位结果
 bit[7:3]    保留
 bit[2:0]    I路DC上报高3位，I路DC上报为11bit有符号数。
   UNION结构:  ABB_BIST_DC_I_2_UNION */
#define ABB_BIST_DC_I_2_ADDR                          (ABB_BASE_ADDR + 0x50B)

/* 寄存器说明：Q路DC上报低8位结果
   详      述：Q路DC上报结果，8bit有符号数。
   UNION结构 ：无 */
#define ABB_BIST_DC_Q_1_ADDR                          (ABB_BASE_ADDR + 0x50C)

/* 寄存器说明：Q路DC上报高3位结果
 bit[7:3]    保留
 bit[2:0]    I路DC上报高3位，I路DC上报为11bit有符号数。
   UNION结构:  ABB_BIST_DC_Q_2_UNION */
#define ABB_BIST_DC_Q_2_ADDR                          (ABB_BASE_ADDR + 0x50D)

/* 寄存器说明：i路信噪比输出值
   详      述：i路信噪比输出值, 8bit无符号数。
   UNION结构 ：无 */
#define ABB_BIST_SNDR_I_ADDR                          (ABB_BASE_ADDR + 0x50E)

/* 寄存器说明：q路信噪比输出值
   详      述：q路信噪比输出值, 8bit无符号数。
   UNION结构 ：无 */
#define ABB_BIST_SNDR_Q_ADDR                          (ABB_BASE_ADDR + 0x50F)

/* 寄存器说明：Gain_mismatch输出
   详      述：Gain_mismatch输出,8bit无符号数。
   UNION结构 ：无 */
#define ABB_BIST_GAIN_MISMATCH_ADDR                   (ABB_BASE_ADDR + 0x510)

/* 寄存器说明：Gain_error输出
   详      述：Gain_error输出,8bit无符号数。
   UNION结构 ：无 */
#define ABB_BIST_GAIN_ERROR_ADDR                      (ABB_BASE_ADDR + 0x511)

/* 寄存器说明：GPLL输出时钟门控功能使能
 bit[7:4]    保留
 bit[3]      G模工作PLL选择，
             0：选择GPLL；（单时钟方案默认选择GPLL，双时钟方案默认选择SCPLL）
             1：选择SCPLL。
 bit[2]      G模工作PLL选择
             0：选择GPLL；（单/双时钟方案默认选择GPLL）
             1：选择SCPLL。
 bit[1]      GPLL稳定指示。0表示GPLL未稳定；1表示GPLL稳定。GPLL稳定后有时钟输出。
 bit[0]      GPLL时钟门控功能使能，
             0：gpll时钟门控功能关闭；
             1：gpll时钟门控功能打开。
   UNION结构:  ABB_GPLL_GATE_EN_UNION */
#define ABB_GPLL_GATE_EN_ADDR                         (ABB_BASE_ADDR + 0x602)

/* 寄存器说明：GPLL输出时钟门控时间配置
 bit[7:2]    保留
 bit[1:0]    GPLL时钟稳定等待时间配置，计数时钟为19.2M：
             00：gpll开启5us后稳定；
             01：gpll开启10us后稳定；
             10：gpll开启15us后稳定；
             11：gpll开启20us后稳定；
   UNION结构:  ABB_GPLL_GATE_TIME_UNION */
#define ABB_GPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x603)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7:6]    保留
 bit[5]      SCPLL锁定指示。
 bit[4]      SCPLL稳定指示。0表示SCPLL未稳定；1表示SCPLL稳定。SCPLL稳定后有时钟输出。
 bit[3]      SCPLL门控使能信号。
 bit[2:1]    SCPLL时钟稳定等待时间配置，计数时钟为19.2M：
             00：SCPLL开启75us后时钟稳定；
             01：SCPLL开启100us后时钟稳定；
             10：SCPLL开启115us后时钟稳定；
             11：SCPLL开启125us后时钟稳定；
 bit[0]      SCPLL使能信号。用于通过CFG接口配置打开scpll。
   UNION结构:  ABB_SCPLL_LOCK_CTRL_UNION */
#define ABB_SCPLL_LOCK_CTRL_ADDR                      (ABB_BASE_ADDR + 0x604)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7]:Reserved;
            [6:4]：PLL后分频因子postdiv2；默认值为1。
            [3]:Reserved;
            [2:0]：PLL后分频因子postdiv1；默认值为5。
   UNION结构 ：无 */
#define ABB_SCPLL_POSTDIV_ADDR                        (ABB_BASE_ADDR + 0x605)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7:0]：PLL反馈分频因子fbdiv[11:0]的低8bit；fbdiv[11:0]默认值为64.
   UNION结构 ：无 */
#define ABB_SCPLL_FBDIV_L_ADDR                        (ABB_BASE_ADDR + 0x606)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:4]    保留
 bit[3:0]    PLL反馈分频因子fbdiv[11:0]的高4bit；
   UNION结构:  ABB_SCPLL_FBDIV_H_UNION */
#define ABB_SCPLL_FBDIV_H_ADDR                        (ABB_BASE_ADDR + 0x607)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:6]    保留
 bit[5:0]    PLL参考分频因子refdiv[5:0]，默认值为1。
   UNION结构:  ABB_SCPLL_REFDIV_UNION */
#define ABB_SCPLL_REFDIV_ADDR                         (ABB_BASE_ADDR + 0x608)

/* 寄存器说明：SC_PLL分频器控制寄存器
   详      述：[7:6]：Reserved；
            [5]：DACPD；默认值为0(打开)。
            [4]：PLL FOUT4PHASEPD控制，高有效；默认值1（关闭）。
            [3]：DSMPD；小数模式PD信号，默认值0（打开）。
            [2]：PLL 旁路控制；默认值0（PLL旁路功能bypass）。
            [1]：PLL FOUTPOSTDIVPD控制，高有效；默认值0（打开）。
            [0]：PLL FOUTVCOPD控制，高有效；默认值0（打开）。
   UNION结构 ：无 */
#define ABB_SCPLL_FREQ_CTRL_ADDR                      (ABB_BASE_ADDR + 0x609)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[7:0]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL_FRAC1_ADDR                          (ABB_BASE_ADDR + 0x60A)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[15:8]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL_FRAC2_ADDR                          (ABB_BASE_ADDR + 0x60B)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[23:16]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL_FRAC3_ADDR                          (ABB_BASE_ADDR + 0x60C)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7:1]    保留
 bit[0]      SCPLL参数配置更新指示。
             scpll_en打开后，软件配置完scpll_postdiv，scpll_fbdiv，scpll_frac参数，再配置scpll_sfg_update，参数同时更新；scpll_en不打开时，配置参数立即更新，不需要配置scpll_sfg_update。
   UNION结构:  ABB_SCPLL_CFG_UPDATE_UNION */
#define ABB_SCPLL_CFG_UPDATE_ADDR                     (ABB_BASE_ADDR + 0x60D)

/* 寄存器说明：BBP的245D76M时钟门控寄存器
 bit[7:3]    保留
 bit[2]      给BBP的SCPLL 104M时钟门控信号。0：不输出时钟，时钟输出低电平。1：输出时钟。默认值0（不输出时钟）。
 bit[1]      给BBP的SCPLL 245D76M时钟门控信号。0：不输出时钟，时钟输出低电平。1：输出时钟。默认值0（不输出时钟）。
 bit[0]      给BBP的WPLL 245D76M时钟门控信号。0：不输出时钟，时钟输出低电平。1：输出时钟。默认值0（不输出时钟）。
   UNION结构:  ABB_BBP_SLEEP_EN_UNION */
#define ABB_BBP_SLEEP_EN_ADDR                         (ABB_BASE_ADDR + 0x60E)

/* 寄存器说明：WPLL输出时钟门控功能使能
 bit[7:2]    保留
 bit[1]      WPLL稳定指示。0表示WPLL未稳定；1表示WPLL稳定。WPLL稳定后有时钟输出。
 bit[0]      WPLL时钟门控功能使能，
             0：wpll时钟门控功能关闭；
             1：wpll时钟门控功能打开。
   UNION结构:  ABB_WPLL_GATE_EN_UNION */
#define ABB_WPLL_GATE_EN_ADDR                         (ABB_BASE_ADDR + 0x60F)

/* 寄存器说明：WPLL输出时钟门控时间配置
 bit[7:2]    保留
 bit[1:0]    WPLL时钟稳定等待时间配置，计数时钟为19.2M：
             00：wpll开启5us后稳定；
             01：wpll开启10us后稳定；
             10：wpll开启15us后稳定；
             11：wpll开启20us后稳定；
   UNION结构:  ABB_WPLL_GATE_TIME_UNION */
#define ABB_WPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x610)

/* 寄存器说明：WPLL输出时钟门控时间配置
 bit[7:3]    保留
 bit[2]      G PLL FREF选择：
             0：选ch0 TCXO；（单时钟方案默认选0，双时钟方案默认选1）
             1：选ch1 TCXO；
 bit[1]      W PLL FREF选择：
             0：选ch0 TCXO；（单/双时钟方案默认选0）
             1：选ch1 TCXO；
 bit[0]      SC PLL FREF选择：
             0：选ch0 TCXO；（单/双时钟方案默认选0）
             1：选ch1 TCXO；
   UNION结构:  ABB_PLL_FREF_SEL_UNION */
#define ABB_PLL_FREF_SEL_ADDR                         (ABB_BASE_ADDR + 0x611)

/* 寄存器说明：SOC时钟选择信号
 bit[7:1]    保留
 bit[0]      SOC PLL选择：
             0：SOC时钟选SCPLL；（默认选SCPLL）
             1：SOC时钟选WPLL；
   UNION结构:  ABB_SOC_PLL_SEL_UNION */
#define ABB_SOC_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x612)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
   详      述：CH0通道RXA I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x613)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXAI_HB_GAIN_2_UNION */
#define ABB_CH0_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x614)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
   详      述：CH0通道RXA Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x615)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x616)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
   详      述：CH0通道RXB I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x617)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXBI_HB_GAIN_2_UNION */
#define ABB_CH0_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x618)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
   详      述：CH0通道RXB Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x619)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x61A)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
   详      述：CH1通道RXA I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x61B)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXAI_HB_GAIN_2_UNION */
#define ABB_CH1_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x61C)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
   详      述：CH1通道RXA Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x61D)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x61E)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
   详      述：CH1通道RXB I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x61F)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXBI_HB_GAIN_2_UNION */
#define ABB_CH1_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x620)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
   详      述：CH1通道RXB Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x621)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x622)

/* 寄存器说明：RX时钟门控延迟功能配置。
 bit[7:3]    保留
 bit[2:1]    RX时钟门控延迟的19.2MHz时钟个数。
                 L/CA/X模   W/TDS模  G模
             00：  1          2      32；  (默认)
             01：  2          4      64；
             10：  4          8      128。
             11：  reserved
 bit[0]      RX时钟门控延迟功能使能。该功能打开后，RX的随路工作钟比RX数据和VLD信号延迟关闭。
   UNION结构:  ABB_RX_EN_DELAY_UNION */
#define ABB_RX_EN_DELAY_ADDR                          (ABB_BASE_ADDR + 0x623)

/* 寄存器说明：TX ET数字配置寄存器1。
 bit[7]      选择CH0还是CH1支持ET。
             0：CH0（默认）；
             1：CH1。
 bit[6]      ET通道降采样bypass信号
             0：不bypass，2倍降采样（默认）；
             1：bypass，不进行降采样。
 bit[5:4]    保留
 bit[3]      ET校准模块软复位寄存器。
             0：不复位；
             1：复位。
 bit[2]      ET通道软复位寄存器。
             0：不复位；
             1：复位。
 bit[1]      ET通道半带滤波器的bypass信号
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      ET通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_ET_DIG_1_UNION */
#define ABB_TX_ET_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x700)

/* 寄存器说明：TX ET数字配置寄存器2。
 bit[7]      ET TX通道dem bypass：
             0：DEM打开(默认)
             1：DEM bypass
 bit[6]      ET Calibration通道dem bypass：
             0：DEM打开(默认)
             1：DEM bypass
 bit[5]      ET TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式
 bit[4]      ET Calibration通道dem模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式
 bit[3]      ET LSB最低bit输出值配置
 bit[2:1]    TX通道DEM const系数：
             0：0
             1：2
             2：4(默认)
             3：6
 bit[0]      ET通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!et_gating_en)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_ET_DIG_2_UNION */
#define ABB_TX_ET_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x701)

/* 寄存器说明：TX ET数字配置寄存器3。
 bit[7]      保留
 bit[6]      ET DAC正常工作时，是否使用calibration结果进行校准。
             0：不使能；
             1：使能。
 bit[5]      保留
 bit[4]      ET校准类型配置。ET DAC正常工作时，有两种方法对ET DAC输出进行校准。
             0：打开Calibration DAC，通过Calibration DAC输出对ET DAC输出进行校准；
             1：关闭Calibration DAC，将IREG寄存器结果加权到ET OUT输出进行校准。
 bit[3:2]    进行电流比较时的延时控制。默认采用153.6MHz时钟进行延时。
             00：30个时钟周期；
             01：75个时钟周期；
             10：150个时钟周期；
             11：300个时钟周期。
 bit[1]      ET通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      ET通道calibration使能。软件配置启动，calibration完成后，该bit自动清零。
             0：不使能；
             1：使能。
   UNION结构:  ABB_TX_ET_DIG_3_UNION */
#define ABB_TX_ET_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x702)

/* 寄存器说明：TX ET数字配置寄存器4。
 bit[7]      保留
 bit[6]      ET通道算法环回模式使能。该模式使能，将RX通道数据环回到。通过et_ch_sel选择环回到ch0通道或者ch1通道。
             0：不使能；
             1：使能。
 bit[5]      ET通道接口环回模式使能。该模式使能，将ET TX数据通过RX通道环回。通过et_ch_sel选择环回到ch0通道或者ch1通道。
             0：不使能；
             1：使能。
 bit[4]      ET分频器使能bypass控制
             0：不bypass
             1：bypass
 bit[3]      ET模式强制配置使能。
             0：不使能；
             1：使能。
 bit[2]      ET模式强制配置值。
 bit[1]      ET线控强制配置使能。
             0：不使能；
             1：使能。
 bit[0]      ET线控强制配置值。
   UNION结构:  ABB_TX_ET_DIG_4_UNION */
#define ABB_TX_ET_DIG_4_ADDR                          (ABB_BASE_ADDR + 0x703)

/* 寄存器说明：ET通道offset配置寄存器。
   详      述：ET通道offset配置寄存器。
   UNION结构 ：无 */
#define ABB_ET_DC_OFFSET_ADDR                         (ABB_BASE_ADDR + 0x704)

/* 寄存器说明：ET通道状态上报寄存器
 bit[7]      ET通道校准完成。
 bit[6:3]    保留
 bit[2]      ET HB滤波器溢出指示。
 bit[1]      ET CIC6滤波器溢出指示。
 bit[0]      ET补偿滤波器溢出指示。
   UNION结构:  ABB_ET_STATE_RPT_UNION */
#define ABB_ET_STATE_RPT_ADDR                         (ABB_BASE_ADDR + 0x705)

/* 寄存器说明：ET通道ITEMP校准结果寄存器高位。
 bit[7:2]    保留
 bit[1:0]    ITEMP校准结果高位。
   UNION结构:  ABB_ET_ITEMP_REG_MSB_UNION */
#define ABB_ET_ITEMP_REG_MSB_ADDR                     (ABB_BASE_ADDR + 0x706)

/* 寄存器说明：ET通道ITEMP校准结果寄存器低位。
   详      述：ITEMP校准结果低位。
   UNION结构 ：无 */
#define ABB_ET_ITEMP_REG_LSB_ADDR                     (ABB_BASE_ADDR + 0x707)

/* 寄存器说明：ET通道ICELL1校准结果寄存器。
   详      述：ICELL1校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG1_ADDR                        (ABB_BASE_ADDR + 0x708)

/* 寄存器说明：ET通道ICELL2校准结果寄存器。
   详      述：ICELL2校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG2_ADDR                        (ABB_BASE_ADDR + 0x709)

/* 寄存器说明：ET通道ICELL3校准结果寄存器。
   详      述：ICELL3校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG3_ADDR                        (ABB_BASE_ADDR + 0x70A)

/* 寄存器说明：ET通道ICELL4校准结果寄存器。
   详      述：ICELL4校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG4_ADDR                        (ABB_BASE_ADDR + 0x70B)

/* 寄存器说明：ET通道ICELL5校准结果寄存器。
   详      述：ICELL5校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG5_ADDR                        (ABB_BASE_ADDR + 0x70C)

/* 寄存器说明：ET通道ICELL6校准结果寄存器。
   详      述：ICELL6校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG6_ADDR                        (ABB_BASE_ADDR + 0x70D)

/* 寄存器说明：ET通道ICELL7校准结果寄存器。
   详      述：ICELL7校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG7_ADDR                        (ABB_BASE_ADDR + 0x70E)

/* 寄存器说明：ET通道ICELL8校准结果寄存器。
   详      述：ICELL8校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG8_ADDR                        (ABB_BASE_ADDR + 0x70F)

/* 寄存器说明：ET通道ICELL9校准结果寄存器。
   详      述：ICELL9校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG9_ADDR                        (ABB_BASE_ADDR + 0x710)

/* 寄存器说明：ET通道ICELL10校准结果寄存器。
   详      述：ICELL10校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG10_ADDR                       (ABB_BASE_ADDR + 0x711)

/* 寄存器说明：ET通道ICELL11校准结果寄存器。
   详      述：ICELL11校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG11_ADDR                       (ABB_BASE_ADDR + 0x712)

/* 寄存器说明：ET通道ICELL12校准结果寄存器。
   详      述：ICELL12校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG12_ADDR                       (ABB_BASE_ADDR + 0x713)

/* 寄存器说明：ET通道ICELL13校准结果寄存器。
   详      述：ICELL13校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG13_ADDR                       (ABB_BASE_ADDR + 0x714)

/* 寄存器说明：ET通道ICELL14校准结果寄存器。
   详      述：ICELL14校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG14_ADDR                       (ABB_BASE_ADDR + 0x715)

/* 寄存器说明：ET通道ICELL15校准结果寄存器。
   详      述：ICELL15校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG15_ADDR                       (ABB_BASE_ADDR + 0x716)

/* 寄存器说明：ET通道ICELL16校准结果寄存器。
   详      述：ICELL16校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG16_ADDR                       (ABB_BASE_ADDR + 0x717)

/* 寄存器说明：ET通道ICELL17校准结果寄存器。
   详      述：ICELL17校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG17_ADDR                       (ABB_BASE_ADDR + 0x718)

/* 寄存器说明：ET通道ICELL18校准结果寄存器。
   详      述：ICELL18校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG18_ADDR                       (ABB_BASE_ADDR + 0x719)

/* 寄存器说明：ET通道ICELL19校准结果寄存器。
   详      述：ICELL19校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG19_ADDR                       (ABB_BASE_ADDR + 0x71A)

/* 寄存器说明：ET通道ICELL20校准结果寄存器。
   详      述：ICELL20校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG20_ADDR                       (ABB_BASE_ADDR + 0x71B)

/* 寄存器说明：ET通道ICELL21校准结果寄存器。
   详      述：ICELL21校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG21_ADDR                       (ABB_BASE_ADDR + 0x71C)

/* 寄存器说明：ET通道ICELL22校准结果寄存器。
   详      述：ICELL22校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG22_ADDR                       (ABB_BASE_ADDR + 0x71D)

/* 寄存器说明：ET通道ICELL23校准结果寄存器。
   详      述：ICELL23校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG23_ADDR                       (ABB_BASE_ADDR + 0x71E)

/* 寄存器说明：ET通道ICELL24校准结果寄存器。
   详      述：ICELL24校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG24_ADDR                       (ABB_BASE_ADDR + 0x71F)

/* 寄存器说明：ET通道ICELL25校准结果寄存器。
   详      述：ICELL25校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG25_ADDR                       (ABB_BASE_ADDR + 0x720)

/* 寄存器说明：ET通道ICELL26校准结果寄存器。
   详      述：ICELL26校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG26_ADDR                       (ABB_BASE_ADDR + 0x721)

/* 寄存器说明：ET通道ICELL27校准结果寄存器。
   详      述：ICELL27校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG27_ADDR                       (ABB_BASE_ADDR + 0x722)

/* 寄存器说明：ET通道ICELL28校准结果寄存器。
   详      述：ICELL28校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG28_ADDR                       (ABB_BASE_ADDR + 0x723)

/* 寄存器说明：ET通道ICELL29校准结果寄存器。
   详      述：ICELL29校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG29_ADDR                       (ABB_BASE_ADDR + 0x724)

/* 寄存器说明：ET通道ICELL30校准结果寄存器。
   详      述：ICELL30校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG30_ADDR                       (ABB_BASE_ADDR + 0x725)

/* 寄存器说明：ET通道ICELL31校准结果寄存器。
   详      述：ICELL31校准结果
   UNION结构 ：无 */
#define ABB_ET_ICELL_REG31_ADDR                       (ABB_BASE_ADDR + 0x726)

/* 寄存器说明：ET通道ICELL排序结果结存器1。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器1。
   UNION结构:  ABB_ET_ICELL_SORT1_UNION */
#define ABB_ET_ICELL_SORT1_ADDR                       (ABB_BASE_ADDR + 0x727)

/* 寄存器说明：ET通道ICELL排序结果结存器2。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器2。
   UNION结构:  ABB_ET_ICELL_SORT2_UNION */
#define ABB_ET_ICELL_SORT2_ADDR                       (ABB_BASE_ADDR + 0x728)

/* 寄存器说明：ET通道ICELL排序结果结存器3。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器3。
   UNION结构:  ABB_ET_ICELL_SORT3_UNION */
#define ABB_ET_ICELL_SORT3_ADDR                       (ABB_BASE_ADDR + 0x729)

/* 寄存器说明：ET通道ICELL排序结果结存器4。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器4。
   UNION结构:  ABB_ET_ICELL_SORT4_UNION */
#define ABB_ET_ICELL_SORT4_ADDR                       (ABB_BASE_ADDR + 0x72A)

/* 寄存器说明：ET通道ICELL排序结果结存器5。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器5。
   UNION结构:  ABB_ET_ICELL_SORT5_UNION */
#define ABB_ET_ICELL_SORT5_ADDR                       (ABB_BASE_ADDR + 0x72B)

/* 寄存器说明：ET通道ICELL排序结果结存器6。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器6。
   UNION结构:  ABB_ET_ICELL_SORT6_UNION */
#define ABB_ET_ICELL_SORT6_ADDR                       (ABB_BASE_ADDR + 0x72C)

/* 寄存器说明：ET通道ICELL排序结果结存器7。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器7。
   UNION结构:  ABB_ET_ICELL_SORT7_UNION */
#define ABB_ET_ICELL_SORT7_ADDR                       (ABB_BASE_ADDR + 0x72D)

/* 寄存器说明：ET通道ICELL排序结果结存器8。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器8。
   UNION结构:  ABB_ET_ICELL_SORT8_UNION */
#define ABB_ET_ICELL_SORT8_ADDR                       (ABB_BASE_ADDR + 0x72E)

/* 寄存器说明：ET通道ICELL排序结果结存器9。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器9。
   UNION结构:  ABB_ET_ICELL_SORT9_UNION */
#define ABB_ET_ICELL_SORT9_ADDR                       (ABB_BASE_ADDR + 0x72F)

/* 寄存器说明：ET通道ICELL排序结果结存器10。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器10。
   UNION结构:  ABB_ET_ICELL_SORT10_UNION */
#define ABB_ET_ICELL_SORT10_ADDR                      (ABB_BASE_ADDR + 0x730)

/* 寄存器说明：ET通道ICELL排序结果结存器11。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器11。
   UNION结构:  ABB_ET_ICELL_SORT11_UNION */
#define ABB_ET_ICELL_SORT11_ADDR                      (ABB_BASE_ADDR + 0x731)

/* 寄存器说明：ET通道ICELL排序结果结存器12。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器12。
   UNION结构:  ABB_ET_ICELL_SORT12_UNION */
#define ABB_ET_ICELL_SORT12_ADDR                      (ABB_BASE_ADDR + 0x732)

/* 寄存器说明：ET通道ICELL排序结果结存器13。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器13。
   UNION结构:  ABB_ET_ICELL_SORT13_UNION */
#define ABB_ET_ICELL_SORT13_ADDR                      (ABB_BASE_ADDR + 0x733)

/* 寄存器说明：ET通道ICELL排序结果结存器14。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器14。
   UNION结构:  ABB_ET_ICELL_SORT14_UNION */
#define ABB_ET_ICELL_SORT14_ADDR                      (ABB_BASE_ADDR + 0x734)

/* 寄存器说明：ET通道ICELL排序结果结存器15。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器15。
   UNION结构:  ABB_ET_ICELL_SORT15_UNION */
#define ABB_ET_ICELL_SORT15_ADDR                      (ABB_BASE_ADDR + 0x735)

/* 寄存器说明：ET通道ICELL排序结果结存器16。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器16。
   UNION结构:  ABB_ET_ICELL_SORT16_UNION */
#define ABB_ET_ICELL_SORT16_ADDR                      (ABB_BASE_ADDR + 0x736)

/* 寄存器说明：ET通道ICELL排序结果结存器17。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器17。
   UNION结构:  ABB_ET_ICELL_SORT17_UNION */
#define ABB_ET_ICELL_SORT17_ADDR                      (ABB_BASE_ADDR + 0x737)

/* 寄存器说明：ET通道ICELL排序结果结存器18。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器18。
   UNION结构:  ABB_ET_ICELL_SORT18_UNION */
#define ABB_ET_ICELL_SORT18_ADDR                      (ABB_BASE_ADDR + 0x738)

/* 寄存器说明：ET通道ICELL排序结果结存器19。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器19。
   UNION结构:  ABB_ET_ICELL_SORT19_UNION */
#define ABB_ET_ICELL_SORT19_ADDR                      (ABB_BASE_ADDR + 0x739)

/* 寄存器说明：ET通道ICELL排序结果结存器20。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器20。
   UNION结构:  ABB_ET_ICELL_SORT20_UNION */
#define ABB_ET_ICELL_SORT20_ADDR                      (ABB_BASE_ADDR + 0x73A)

/* 寄存器说明：ET通道ICELL排序结果结存器21。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器21。
   UNION结构:  ABB_ET_ICELL_SORT21_UNION */
#define ABB_ET_ICELL_SORT21_ADDR                      (ABB_BASE_ADDR + 0x73B)

/* 寄存器说明：ET通道ICELL排序结果结存器22。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器22。
   UNION结构:  ABB_ET_ICELL_SORT22_UNION */
#define ABB_ET_ICELL_SORT22_ADDR                      (ABB_BASE_ADDR + 0x73C)

/* 寄存器说明：ET通道ICELL排序结果结存器23。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器23。
   UNION结构:  ABB_ET_ICELL_SORT23_UNION */
#define ABB_ET_ICELL_SORT23_ADDR                      (ABB_BASE_ADDR + 0x73D)

/* 寄存器说明：ET通道ICELL排序结果结存器24。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器24。
   UNION结构:  ABB_ET_ICELL_SORT24_UNION */
#define ABB_ET_ICELL_SORT24_ADDR                      (ABB_BASE_ADDR + 0x73E)

/* 寄存器说明：ET通道ICELL排序结果结存器25。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器25。
   UNION结构:  ABB_ET_ICELL_SORT25_UNION */
#define ABB_ET_ICELL_SORT25_ADDR                      (ABB_BASE_ADDR + 0x73F)

/* 寄存器说明：ET通道ICELL排序结果结存器26。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器26。
   UNION结构:  ABB_ET_ICELL_SORT26_UNION */
#define ABB_ET_ICELL_SORT26_ADDR                      (ABB_BASE_ADDR + 0x740)

/* 寄存器说明：ET通道ICELL排序结果结存器27。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器27。
   UNION结构:  ABB_ET_ICELL_SORT27_UNION */
#define ABB_ET_ICELL_SORT27_ADDR                      (ABB_BASE_ADDR + 0x741)

/* 寄存器说明：ET通道ICELL排序结果结存器28。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器28。
   UNION结构:  ABB_ET_ICELL_SORT28_UNION */
#define ABB_ET_ICELL_SORT28_ADDR                      (ABB_BASE_ADDR + 0x742)

/* 寄存器说明：ET通道ICELL排序结果结存器29。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器29。
   UNION结构:  ABB_ET_ICELL_SORT29_UNION */
#define ABB_ET_ICELL_SORT29_ADDR                      (ABB_BASE_ADDR + 0x743)

/* 寄存器说明：ET通道ICELL排序结果结存器30。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器30。
   UNION结构:  ABB_ET_ICELL_SORT30_UNION */
#define ABB_ET_ICELL_SORT30_ADDR                      (ABB_BASE_ADDR + 0x744)

/* 寄存器说明：ET通道ICELL排序结果结存器31。
 bit[7:5]    保留
 bit[4:0]    ICELL排序结果寄存器31。
   UNION结构:  ABB_ET_ICELL_SORT31_UNION */
#define ABB_ET_ICELL_SORT31_ADDR                      (ABB_BASE_ADDR + 0x745)

/* 寄存器说明：ET通道ICELL寄存器更新
 bit[7:1]    保留
 bit[0]      配置该寄存器，更新寄存器ET_ICELL_REG1~ET_ICELL_SORT31。寄存器更新完成之后，需要配置为0。
   UNION结构:  ABB_ET_ICELL_UPDATE_UNION */
#define ABB_ET_ICELL_UPDATE_ADDR                      (ABB_BASE_ADDR + 0x746)

/* 寄存器说明：ET通道ICELL校准溢出标志寄存器3
   详      述：校准ICELL31~ICELL24溢出标志。
   UNION结构 ：无 */
#define ABB_ET_ICELL_OVERFLOW3_ADDR                   (ABB_BASE_ADDR + 0x747)

/* 寄存器说明：ET通道ICELL校准溢出标志寄存器3
   详      述：校准ICELL23~ICELL16溢出标志。
   UNION结构 ：无 */
#define ABB_ET_ICELL_OVERFLOW2_ADDR                   (ABB_BASE_ADDR + 0x748)

/* 寄存器说明：ET通道ICELL校准溢出标志寄存器1
   详      述：校准ICELL15~ICELL8溢出标志。
   UNION结构 ：无 */
#define ABB_ET_ICELL_OVERFLOW1_ADDR                   (ABB_BASE_ADDR + 0x749)

/* 寄存器说明：ET通道ICELL校准溢出标志寄存器0
   详      述：校准ICELL7~ICELL1和ITEMP溢出标志。
   UNION结构 ：无 */
#define ABB_ET_ICELL_OVERFLOW0_ADDR                   (ABB_BASE_ADDR + 0x74A)

/* 寄存器说明：SINE发送寄存器。
 bit[7:4]    正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f
 bit[3:2]    正弦波发送幅度控制
             00：满量程
             01：3/4量程
             10：1/2量程
             11：1/4量程
 bit[1]      保留
 bit[0]      et通道正弦波发送使能。该位使能，则ET通道发送正弦波信号，且通过sine_sw_req选择CH0或者CH1发送正弦波信号。
             0：不发送
             1：发送
   UNION结构:  ABB_ET_SINE_GENERATE_UNION */
#define ABB_ET_SINE_GENERATE_ADDR                     (ABB_BASE_ADDR + 0x74B)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至et_reg_debug_ana28。
   详      述：选择CH0还是CH1支持ET。
            0：CH0（默认）
            1：CH1。
   UNION结构 ：无 */
#define ABB_ET_ET_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x780)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至et_reg_debug_ana29。
   详      述：ET模式控制寄存器2
   UNION结构 ：无 */
#define ABB_ET_ET_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x781)

/* 寄存器说明：APT模式配置寄存器，经过线控逻辑后送至et_reg_debug_ana28。
   详      述：选择CH0还是CH1支持ET。
            0：CH0（默认）
            1：CH1。
   UNION结构 ：无 */
#define ABB_ET_APT_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x782)

/* 寄存器说明：APT模式配置寄存器，经过线控逻辑后送至et_reg_debug_ana29。
   详      述：ET模式控制寄存器2
   UNION结构 ：无 */
#define ABB_ET_APT_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x783)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至et_reg_debug_ana28。
   详      述：选择CH0还是CH1支持ET。
            0：CH0（默认）
            1：CH1。
   UNION结构 ：无 */
#define ABB_ET_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x784)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至et_reg_debug_ana29。
   详      述：ET模式控制寄存器2
   UNION结构 ：无 */
#define ABB_ET_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x785)





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
                     (1/1) register_define_ssi_reg
 ***======================================================================***/
/*****************************************************************************
 结构名    : ABB_RX_2G_DIG_1_UNION
 结构说明  : rx_2g_dig_1 寄存器结构定义。地址偏移量:0x0，初值:0x00，宽度:8
 寄存器说明: RX 2G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_2g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                            00：固定系数1；
                                                            01：固定系数2；
                                                            10：固定系数3；
                                                            11：reserved。 */
        unsigned long  rx_comp_fix_2g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                            0：系数不固定，由寄存器配置
                                                            1：系数固定 */
        unsigned long  rx_hb_bp_2g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                            0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                            1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_2g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                            others：reserved */
        unsigned long  rx_mode_dig_2g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                            000：2G(默认)
                                                            001：3G_SC/TDS_B/4G_C
                                                            010：4G
                                                            011：3G_DC/4G_B
                                                            100：TDS
                                                            101：CDMA
                                                            Others：Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_1_UNION;
#define ABB_RX_2G_DIG_1_rx_comp_sel_b0_2g_START  (0)
#define ABB_RX_2G_DIG_1_rx_comp_sel_b0_2g_END    (0)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_START     (1)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_END       (1)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_START        (2)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_END          (2)
#define ABB_RX_2G_DIG_1_rx_rate_2g_START         (3)
#define ABB_RX_2G_DIG_1_rx_rate_2g_END           (4)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_START     (5)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_2G_DIG_2_UNION
 结构说明  : rx_2g_dig_2 寄存器结构定义。地址偏移量:0x1，初值:0x13，宽度:8
 寄存器说明: RX 2G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_2g         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_2g         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_2g       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                            00：gain为0.5(默认)
                                                            01：gain为0.75
                                                            10：gain为0.85
                                                            11：Reserved */
        unsigned long  rx_comp_bp_2g     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                            0：不bypass
                                                            1：bypass(默认) */
        unsigned long  rx_clk_inv_2g     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                            0：正常
                                                            1：反向 */
        unsigned long  rx_flush_en_2g    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                            0：不使能
                                                            1：使能 */
        unsigned long  rx_comp_sel_b1_2g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_2_UNION;
#define ABB_RX_2G_DIG_2_rxa_pd_2g_START          (0)
#define ABB_RX_2G_DIG_2_rxa_pd_2g_END            (0)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_START          (1)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_END            (1)
#define ABB_RX_2G_DIG_2_gain_sel_2g_START        (2)
#define ABB_RX_2G_DIG_2_gain_sel_2g_END          (3)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_START      (4)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_END        (4)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_START      (5)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_END        (5)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_START     (6)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_END       (6)
#define ABB_RX_2G_DIG_2_rx_comp_sel_b1_2g_START  (7)
#define ABB_RX_2G_DIG_2_rx_comp_sel_b1_2g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_2G_DIG_1_UNION
 结构说明  : tx_2g_dig_1 寄存器结构定义。地址偏移量:0x2，初值:0x02，宽度:8
 寄存器说明: TX 2G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_2g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_2g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认) */
        unsigned long  tx_rate_2g     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                              2G,     3G,     4G,      TDS,      CDMA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                         0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2：-------,--------,15.36MHz,--------,--------
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_2g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G(默认)
                                                         001：3G
                                                         010：4G
                                                         011：TDS
                                                         100：CDMA
                                                         Others：Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_1_UNION;
#define ABB_TX_2G_DIG_1_tx_comp_bp_2g_START   (0)
#define ABB_TX_2G_DIG_1_tx_comp_bp_2g_END     (0)
#define ABB_TX_2G_DIG_1_tx_hb_bp_2g_START     (1)
#define ABB_TX_2G_DIG_1_tx_hb_bp_2g_END       (1)
#define ABB_TX_2G_DIG_1_tx_rate_2g_START      (2)
#define ABB_TX_2G_DIG_1_tx_rate_2g_END        (4)
#define ABB_TX_2G_DIG_1_tx_mode_dig_2g_START  (5)
#define ABB_TX_2G_DIG_1_tx_mode_dig_2g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_2G_DIG_2_UNION
 结构说明  : tx_2g_dig_2 寄存器结构定义。地址偏移量:0x3，初值:0x23，宽度:8
 寄存器说明: TX 2G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_2g       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_2g       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_2g     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                           0：0(默认)
                                                           1：2
                                                           2：4
                                                           3：6 */
        unsigned long  uddwa_dith_en_2g : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                           0：不使能
                                                           1：使能 */
        unsigned long  dem_dwa_en_2g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                           0：使用CLA模式
                                                           1：使用DWA模式 (默认) */
        unsigned long  dem_lsb_bp_2g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                           0：DEM LSB 打开(默认)
                                                           1：DEM LSB bypass */
        unsigned long  dem_msb_bp_2g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                           0：DEM MSB打开(默认)
                                                           1：DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_2_UNION;
#define ABB_TX_2G_DIG_2_tx_q_pd_2g_START        (0)
#define ABB_TX_2G_DIG_2_tx_q_pd_2g_END          (0)
#define ABB_TX_2G_DIG_2_tx_i_pd_2g_START        (1)
#define ABB_TX_2G_DIG_2_tx_i_pd_2g_END          (1)
#define ABB_TX_2G_DIG_2_dem_const_2g_START      (2)
#define ABB_TX_2G_DIG_2_dem_const_2g_END        (3)
#define ABB_TX_2G_DIG_2_uddwa_dith_en_2g_START  (4)
#define ABB_TX_2G_DIG_2_uddwa_dith_en_2g_END    (4)
#define ABB_TX_2G_DIG_2_dem_dwa_en_2g_START     (5)
#define ABB_TX_2G_DIG_2_dem_dwa_en_2g_END       (5)
#define ABB_TX_2G_DIG_2_dem_lsb_bp_2g_START     (6)
#define ABB_TX_2G_DIG_2_dem_lsb_bp_2g_END       (6)
#define ABB_TX_2G_DIG_2_dem_msb_bp_2g_START     (7)
#define ABB_TX_2G_DIG_2_dem_msb_bp_2g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_2G_DIG_3_UNION
 结构说明  : tx_2g_dig_3 寄存器结构定义。地址偏移量:0x4，初值:0x01，宽度:8
 寄存器说明: TX 2G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : 保留 */
        unsigned long  tx_flush_en_2g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  tx_comp_sel_2g : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                         00：固定系数1；
                                                         01：固定系数2；
                                                         10：固定系数3；
                                                         11：可配系数。 */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_START  (1)
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_END    (1)
#define ABB_TX_2G_DIG_3_tx_comp_sel_2g_START  (2)
#define ABB_TX_2G_DIG_3_tx_comp_sel_2g_END    (3)


/*****************************************************************************
 结构名    : ABB_RX_CH0_3G_DIG_1_UNION
 结构说明  : rx_ch0_3g_dig_1 寄存器结构定义。地址偏移量:0x5，初值:0x26，宽度:8
 寄存器说明: CH0 RX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_b0_3g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                                00：固定系数1；
                                                                01：固定系数2；
                                                                10：固定系数3；
                                                                11：reserved。 */
        unsigned long  ch0_rx_comp_fix_3g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                                0：系数不固定，由寄存器配置
                                                                1：系数固定 */
        unsigned long  ch0_rx_hb_bp_3g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                                0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                                1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch0_rx_rate_3g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                                others：reserved */
        unsigned long  ch0_rx_mode_dig_3g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                                000：2G(默认)
                                                                001：3G_SC/TDS_B/4G_C
                                                                010：4G
                                                                011：3G_DC/4G_B
                                                                100：TDS
                                                                101：CDMA
                                                                Others：Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_1_UNION;
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_fix_3g_START     (1)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_fix_3g_END       (1)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_hb_bp_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_hb_bp_3g_END          (2)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_rate_3g_START         (3)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_rate_3g_END           (4)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_mode_dig_3g_START     (5)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_mode_dig_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_3G_DIG_2_UNION
 结构说明  : rx_ch0_3g_dig_2 寄存器结构定义。地址偏移量:0x6，初值:0x03，宽度:8
 寄存器说明: CH0 RX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_3g         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch0_rxb_pd_3g         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch0_gain_sel_3g       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                                00：gain为0.5(默认)
                                                                01：gain为0.75
                                                                10：gain为0.85
                                                                11：Reserved */
        unsigned long  ch0_rx_comp_bp_3g     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                                0：不bypass(默认)
                                                                1：bypass */
        unsigned long  ch0_rx_clk_inv_3g     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                                0：正常
                                                                1：反向 */
        unsigned long  ch0_rx_flush_en_3g    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                                0：不使能
                                                                1：使能 */
        unsigned long  ch0_rx_comp_sel_b1_3g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_2_UNION;
#define ABB_RX_CH0_3G_DIG_2_ch0_rxa_pd_3g_START          (0)
#define ABB_RX_CH0_3G_DIG_2_ch0_rxa_pd_3g_END            (0)
#define ABB_RX_CH0_3G_DIG_2_ch0_rxb_pd_3g_START          (1)
#define ABB_RX_CH0_3G_DIG_2_ch0_rxb_pd_3g_END            (1)
#define ABB_RX_CH0_3G_DIG_2_ch0_gain_sel_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_2_ch0_gain_sel_3g_END          (3)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_bp_3g_START      (4)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_bp_3g_END        (4)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_clk_inv_3g_START      (5)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_clk_inv_3g_END        (5)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_flush_en_3g_START     (6)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_flush_en_3g_END       (6)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_sel_b1_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_3G_DIG_1_UNION
 结构说明  : tx_ch0_3g_dig_1 寄存器结构定义。地址偏移量:0x7，初值:0x20，宽度:8
 寄存器说明: CH0 TX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_3g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch0_tx_hb_bp_3g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  ch0_tx_rate_3g     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2：-------,--------,15.36MHz,--------,--------
                                                             Others：Reserved */
        unsigned long  ch0_tx_mode_dig_3g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_1_UNION;
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_comp_bp_3g_START   (0)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_comp_bp_3g_END     (0)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_hb_bp_3g_START     (1)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_hb_bp_3g_END       (1)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_rate_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_rate_3g_END        (4)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_mode_dig_3g_START  (5)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_3G_DIG_2_UNION
 结构说明  : tx_ch0_3g_dig_2 寄存器结构定义。地址偏移量:0x8，初值:0x23，宽度:8
 寄存器说明: CH0 TX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_q_pd_3g       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch0_tx_i_pd_3g       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch0_dem_const_3g     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                               0：0(默认)
                                                               1：2
                                                               2：4
                                                               3：6 */
        unsigned long  ch0_uddwa_dith_en_3g : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                               0：不使能
                                                               1：使能 */
        unsigned long  ch0_dem_dwa_en_3g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                               0：使用CLA模式
                                                               1：使用DWA模式(默认)  */
        unsigned long  ch0_dem_lsb_bp_3g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                               0：DEM LSB 打开(默认)
                                                               1：DEM LSB bypass */
        unsigned long  ch0_dem_msb_bp_3g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                               0：DEM MSB打开(默认)
                                                               1：DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_2_UNION;
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_q_pd_3g_START        (0)
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_q_pd_3g_END          (0)
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_i_pd_3g_START        (1)
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_i_pd_3g_END          (1)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_const_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_const_3g_END        (3)
#define ABB_TX_CH0_3G_DIG_2_ch0_uddwa_dith_en_3g_START  (4)
#define ABB_TX_CH0_3G_DIG_2_ch0_uddwa_dith_en_3g_END    (4)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_dwa_en_3g_START     (5)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_dwa_en_3g_END       (5)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_lsb_bp_3g_START     (6)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_lsb_bp_3g_END       (6)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_msb_bp_3g_START     (7)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_3G_DIG_3_UNION
 结构说明  : tx_ch0_3g_dig_3 寄存器结构定义。地址偏移量:0x9，初值:0x01，宽度:8
 寄存器说明: CH0 TX 3G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : 保留 */
        unsigned long  ch0_tx_flush_en_3g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  ch0_tx_comp_sel_3g : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                             00：固定系数1；
                                                             01：固定系数2；
                                                             10：固定系数3；
                                                             11：可配系数。 */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_3_UNION;
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_flush_en_3g_START  (1)
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_flush_en_3g_END    (1)
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_comp_sel_3g_START  (2)
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_DIG_1_UNION
 结构说明  : rx_ch0_4g_dig_1 寄存器结构定义。地址偏移量:0xA，初值:0x42，宽度:8
 寄存器说明: CH0 RX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_b0_4g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                                00：固定系数1；
                                                                01：固定系数2；
                                                                10：固定系数3；
                                                                11：reserved。 */
        unsigned long  ch0_rx_comp_fix_4g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                                0：系数不固定，由寄存器配置
                                                                1：系数固定 */
        unsigned long  ch0_rx_hb_bp_4g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                                0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                                1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch0_rx_rate_4g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                                others：reserved */
        unsigned long  ch0_rx_mode_dig_4g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                                000：2G(默认)
                                                                001：3G_SC/TDS_B/4G_C
                                                                010：4G
                                                                011：3G_DC/4G_B
                                                                100：TDS
                                                                101：CDMA
                                                                Others：Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_1_UNION;
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_fix_4g_START     (1)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_fix_4g_END       (1)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_hb_bp_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_hb_bp_4g_END          (2)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_rate_4g_START         (3)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_rate_4g_END           (4)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_mode_dig_4g_START     (5)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_mode_dig_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_DIG_2_UNION
 结构说明  : rx_ch0_4g_dig_2 寄存器结构定义。地址偏移量:0xB，初值:0x03，宽度:8
 寄存器说明: CH0 RX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_4g         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch0_rxb_pd_4g         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch0_gain_sel_4g       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                                00：gain为0.5(默认)
                                                                01：gain为0.75
                                                                10：gain为0.85
                                                                11：Reserved */
        unsigned long  ch0_rx_comp_bp_4g     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                                0：不bypass(默认)
                                                                1：bypass */
        unsigned long  ch0_rx_clk_inv_4g     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                                0：正常
                                                                1：反向 */
        unsigned long  ch0_rx_flush_en_4g    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                                0：不使能
                                                                1：使能 */
        unsigned long  ch0_rx_comp_sel_b1_4g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_2_UNION;
#define ABB_RX_CH0_4G_DIG_2_ch0_rxa_pd_4g_START          (0)
#define ABB_RX_CH0_4G_DIG_2_ch0_rxa_pd_4g_END            (0)
#define ABB_RX_CH0_4G_DIG_2_ch0_rxb_pd_4g_START          (1)
#define ABB_RX_CH0_4G_DIG_2_ch0_rxb_pd_4g_END            (1)
#define ABB_RX_CH0_4G_DIG_2_ch0_gain_sel_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_2_ch0_gain_sel_4g_END          (3)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_bp_4g_START      (4)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_bp_4g_END        (4)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_clk_inv_4g_START      (5)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_clk_inv_4g_END        (5)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_flush_en_4g_START     (6)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_flush_en_4g_END       (6)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_sel_b1_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_4G_DIG_1_UNION
 结构说明  : tx_ch0_4g_dig_1 寄存器结构定义。地址偏移量:0xC，初值:0x40，宽度:8
 寄存器说明: CH0 TX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_4g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch0_tx_hb_bp_4g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  ch0_tx_rate_4g     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2：-------,--------,15.36MHz,--------,--------
                                                             Others：Reserved */
        unsigned long  ch0_tx_mode_dig_4g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_1_UNION;
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_comp_bp_4g_START   (0)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_comp_bp_4g_END     (0)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_hb_bp_4g_START     (1)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_hb_bp_4g_END       (1)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_rate_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_rate_4g_END        (4)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_mode_dig_4g_START  (5)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_4G_DIG_2_UNION
 结构说明  : tx_ch0_4g_dig_2 寄存器结构定义。地址偏移量:0xD，初值:0x23，宽度:8
 寄存器说明: CH0 TX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_q_pd_4g       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch0_tx_i_pd_4g       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch0_dem_const_4g     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                               0：0(默认)
                                                               1：2
                                                               2：4
                                                               3：6 */
        unsigned long  ch0_uddwa_dith_en_4g : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                               0：不使能
                                                               1：使能 */
        unsigned long  ch0_dem_dwa_en_4g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                               0：使用CLA模式
                                                               1：使用DWA模式(默认)  */
        unsigned long  ch0_dem_lsb_bp_4g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                               0：DEM LSB 打开(默认)
                                                               1：DEM LSB bypass */
        unsigned long  ch0_dem_msb_bp_4g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                               0：DEM MSB打开(默认)
                                                               1：DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_2_UNION;
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_q_pd_4g_START        (0)
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_q_pd_4g_END          (0)
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_i_pd_4g_START        (1)
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_i_pd_4g_END          (1)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_const_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_const_4g_END        (3)
#define ABB_TX_CH0_4G_DIG_2_ch0_uddwa_dith_en_4g_START  (4)
#define ABB_TX_CH0_4G_DIG_2_ch0_uddwa_dith_en_4g_END    (4)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_dwa_en_4g_START     (5)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_dwa_en_4g_END       (5)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_lsb_bp_4g_START     (6)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_lsb_bp_4g_END       (6)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_msb_bp_4g_START     (7)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_4G_DIG_3_UNION
 结构说明  : tx_ch0_4g_dig_3 寄存器结构定义。地址偏移量:0xE，初值:0x01，宽度:8
 寄存器说明: CH0 TX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : 保留 */
        unsigned long  ch0_tx_flush_en_4g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  ch0_tx_comp_sel_4g : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                             00：固定系数1；
                                                             01：固定系数2；
                                                             10：固定系数3；
                                                             11：可配系数。 */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_3_UNION;
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_flush_en_4g_START  (1)
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_flush_en_4g_END    (1)
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_comp_sel_4g_START  (2)
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_1_UNION
 结构说明  : rx_tds_dig_1 寄存器结构定义。地址偏移量:0xF，初值:0x26，宽度:8
 寄存器说明: RX TDS模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_tds : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                             00：固定系数1；
                                                             01：固定系数2；
                                                             10：固定系数3；
                                                             11：reserved。 */
        unsigned long  rx_comp_fix_tds    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                             0：系数不固定，由寄存器配置
                                                             1：系数固定 */
        unsigned long  rx_hb_bp_tds       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_tds        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                       /TDS_B/4G_C,        /4G_B,
                                                             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                             others：reserved */
        unsigned long  rx_mode_dig_tds    : 3;  /* bit[5-7]: RX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G_SC/TDS_B/4G_C
                                                             010：4G
                                                             011：3G_DC/4G_B
                                                             100：TDS
                                                             101：CDMA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_1_UNION;
#define ABB_RX_TDS_DIG_1_rx_comp_sel_b0_tds_START  (0)
#define ABB_RX_TDS_DIG_1_rx_comp_sel_b0_tds_END    (0)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_START     (1)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_END       (1)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_START        (2)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_END          (2)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_START         (3)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_END           (4)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_START     (5)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_2_UNION
 结构说明  : rx_tds_dig_2 寄存器结构定义。地址偏移量:0x10，初值:0xD3，宽度:8
 寄存器说明: RX TDS模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_tds         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_tds         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_tds       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                             00：gain为0.5(默认)
                                                             01：gain为0.75
                                                             10：gain为0.85
                                                             11：Reserved */
        unsigned long  rx_comp_bp_tds     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                             0：不bypass
                                                             1：bypass(默认) */
        unsigned long  rx_clk_inv_tds     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                             0：正常
                                                             1：反向 */
        unsigned long  rx_flush_en_tds    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  rx_comp_sel_b1_tds : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_2_UNION;
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_START          (0)
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_END            (0)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_START          (1)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_END            (1)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_START        (2)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_END          (3)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_START      (4)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_END        (4)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_START      (5)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_END        (5)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_START     (6)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_END       (6)
#define ABB_RX_TDS_DIG_2_rx_comp_sel_b1_tds_START  (7)
#define ABB_RX_TDS_DIG_2_rx_comp_sel_b1_tds_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_TDS_DIG_1_UNION
 结构说明  : tx_tds_dig_1 寄存器结构定义。地址偏移量:0x11，初值:0x60，宽度:8
 寄存器说明: TX TDS模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_tds  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                          0：不bypass(默认)
                                                          1：bypass */
        unsigned long  tx_hb_bp_tds    : 1;  /* bit[1]  : TX通道半带滤波器的bypass信号
                                                          0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                          1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_tds     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                               2G,     3G,     4G,      TDS,      CDMA
                                                              (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                          0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                          1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                          2：-------,--------,15.36MHz,--------,--------
                                                          Others：Reserved */
        unsigned long  tx_mode_dig_tds : 3;  /* bit[5-7]: TX模式控制：
                                                          000：2G
                                                          001：3G
                                                          010：4G &amp; ET &amp; APT
                                                          011：TDS(默认)
                                                          Others：CA */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_1_UNION;
#define ABB_TX_TDS_DIG_1_tx_comp_bp_tds_START   (0)
#define ABB_TX_TDS_DIG_1_tx_comp_bp_tds_END     (0)
#define ABB_TX_TDS_DIG_1_tx_hb_bp_tds_START     (1)
#define ABB_TX_TDS_DIG_1_tx_hb_bp_tds_END       (1)
#define ABB_TX_TDS_DIG_1_tx_rate_tds_START      (2)
#define ABB_TX_TDS_DIG_1_tx_rate_tds_END        (4)
#define ABB_TX_TDS_DIG_1_tx_mode_dig_tds_START  (5)
#define ABB_TX_TDS_DIG_1_tx_mode_dig_tds_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_TDS_DIG_2_UNION
 结构说明  : tx_tds_dig_2 寄存器结构定义。地址偏移量:0x12，初值:0x23，宽度:8
 寄存器说明: TX TDS模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_tds       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_tds       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_tds     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                            0：0(默认)
                                                            1：2
                                                            2：4
                                                            3：6 */
        unsigned long  uddwa_dith_en_tds : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                            0：不使能
                                                            1：使能 */
        unsigned long  dem_dwa_en_tds    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                            0：使用CLA模式
                                                            1：使用DWA模式(默认)  */
        unsigned long  dem_lsb_bp_tds    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                            0：DEM LSB 打开(默认)
                                                            1：DEM LSB bypass */
        unsigned long  dem_msb_bp_tds    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                            0：DEM MSB打开(默认)
                                                            1：DEM MSB bypass */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_2_UNION;
#define ABB_TX_TDS_DIG_2_tx_q_pd_tds_START        (0)
#define ABB_TX_TDS_DIG_2_tx_q_pd_tds_END          (0)
#define ABB_TX_TDS_DIG_2_tx_i_pd_tds_START        (1)
#define ABB_TX_TDS_DIG_2_tx_i_pd_tds_END          (1)
#define ABB_TX_TDS_DIG_2_dem_const_tds_START      (2)
#define ABB_TX_TDS_DIG_2_dem_const_tds_END        (3)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_START  (4)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_END    (4)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_START     (5)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_END       (5)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_START     (6)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_END       (6)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_START     (7)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_TDS_DIG_3_UNION
 结构说明  : tx_tds_dig_3 寄存器结构定义。地址偏移量:0x13，初值:0x01，宽度:8
 寄存器说明: TX TDS模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : 保留 */
        unsigned long  tx_flush_en_tds : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                          0：不使能
                                                          1：使能 */
        unsigned long  tx_comp_sel_tds : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                          00：固定系数1；
                                                          01：固定系数2；
                                                          10：固定系数3；
                                                          11：可配系数。 */
        unsigned long  reserved_1      : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_START  (1)
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_END    (1)
#define ABB_TX_TDS_DIG_3_tx_comp_sel_tds_START  (2)
#define ABB_TX_TDS_DIG_3_tx_comp_sel_tds_END    (3)


/*****************************************************************************
 结构名    : ABB_RX_CH1_4G_DIG_1_UNION
 结构说明  : rx_ch1_4g_dig_1 寄存器结构定义。地址偏移量:0x1A，初值:0x42，宽度:8
 寄存器说明: CH1 RX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_comp_sel_b0_4g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                                00：固定系数1；
                                                                01：固定系数2；
                                                                10：固定系数3；
                                                                11：reserved。 */
        unsigned long  ch1_rx_comp_fix_4g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                                0：系数不固定，由寄存器配置
                                                                1：系数固定 */
        unsigned long  ch1_rx_hb_bp_4g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                                0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                                1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch1_rx_rate_4g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                                others：reserved */
        unsigned long  ch1_rx_mode_dig_4g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                                000：2G(默认)
                                                                001：3G_SC/TDS_B/4G_C
                                                                010：4G
                                                                011：3G_DC/4G_B
                                                                100：TDS
                                                                101：CDMA
                                                                Others：Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_DIG_1_UNION;
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_fix_4g_START     (1)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_fix_4g_END       (1)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_hb_bp_4g_START        (2)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_hb_bp_4g_END          (2)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_rate_4g_START         (3)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_rate_4g_END           (4)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_mode_dig_4g_START     (5)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_mode_dig_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_CH1_4G_DIG_2_UNION
 结构说明  : rx_ch1_4g_dig_2 寄存器结构定义。地址偏移量:0x1B，初值:0x03，宽度:8
 寄存器说明: CH1 RX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_4g         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch1_rxb_pd_4g         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch1_gain_sel_4g       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                                00：gain为0.5(默认)
                                                                01：gain为0.75
                                                                10：gain为0.85
                                                                11：Reserved */
        unsigned long  ch1_rx_comp_bp_4g     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                                0：不bypass(默认)
                                                                1：bypass */
        unsigned long  ch1_rx_clk_inv_4g     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                                0：正常
                                                                1：反向 */
        unsigned long  ch1_rx_flush_en_4g    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                                0：不使能
                                                                1：使能 */
        unsigned long  ch1_rx_comp_sel_b1_4g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_DIG_2_UNION;
#define ABB_RX_CH1_4G_DIG_2_ch1_rxa_pd_4g_START          (0)
#define ABB_RX_CH1_4G_DIG_2_ch1_rxa_pd_4g_END            (0)
#define ABB_RX_CH1_4G_DIG_2_ch1_rxb_pd_4g_START          (1)
#define ABB_RX_CH1_4G_DIG_2_ch1_rxb_pd_4g_END            (1)
#define ABB_RX_CH1_4G_DIG_2_ch1_gain_sel_4g_START        (2)
#define ABB_RX_CH1_4G_DIG_2_ch1_gain_sel_4g_END          (3)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_bp_4g_START      (4)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_bp_4g_END        (4)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_clk_inv_4g_START      (5)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_clk_inv_4g_END        (5)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_flush_en_4g_START     (6)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_flush_en_4g_END       (6)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_sel_b1_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH1_4G_DIG_1_UNION
 结构说明  : tx_ch1_4g_dig_1 寄存器结构定义。地址偏移量:0x1C，初值:0x40，宽度:8
 寄存器说明: CH1 TX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_bp_4g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch1_tx_hb_bp_4g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  ch1_tx_rate_4g     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2：-------,--------,15.36MHz,--------,--------
                                                             Others：Reserved */
        unsigned long  ch1_tx_mode_dig_4g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_DIG_1_UNION;
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_comp_bp_4g_START   (0)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_comp_bp_4g_END     (0)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_hb_bp_4g_START     (1)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_hb_bp_4g_END       (1)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_rate_4g_START      (2)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_rate_4g_END        (4)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_mode_dig_4g_START  (5)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH1_4G_DIG_2_UNION
 结构说明  : tx_ch1_4g_dig_2 寄存器结构定义。地址偏移量:0x1D，初值:0x23，宽度:8
 寄存器说明: CH1 TX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_q_pd_4g       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch1_tx_i_pd_4g       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch1_dem_const_4g     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                               0：0(默认)
                                                               1：2
                                                               2：4
                                                               3：6 */
        unsigned long  ch1_uddwa_dith_en_4g : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                               0：不使能
                                                               1：使能 */
        unsigned long  ch1_dem_dwa_en_4g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                               0：使用CLA模式
                                                               1：使用DWA模式(默认)  */
        unsigned long  ch1_dem_lsb_bp_4g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                               0：DEM LSB 打开(默认)
                                                               1：DEM LSB bypass */
        unsigned long  ch1_dem_msb_bp_4g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                               0：DEM MSB打开(默认)
                                                               1：DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_DIG_2_UNION;
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_q_pd_4g_START        (0)
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_q_pd_4g_END          (0)
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_i_pd_4g_START        (1)
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_i_pd_4g_END          (1)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_const_4g_START      (2)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_const_4g_END        (3)
#define ABB_TX_CH1_4G_DIG_2_ch1_uddwa_dith_en_4g_START  (4)
#define ABB_TX_CH1_4G_DIG_2_ch1_uddwa_dith_en_4g_END    (4)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_dwa_en_4g_START     (5)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_dwa_en_4g_END       (5)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_lsb_bp_4g_START     (6)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_lsb_bp_4g_END       (6)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_msb_bp_4g_START     (7)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_CH1_4G_DIG_3_UNION
 结构说明  : tx_ch1_4g_dig_3 寄存器结构定义。地址偏移量:0x1E，初值:0x01，宽度:8
 寄存器说明: CH1 TX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : 保留 */
        unsigned long  ch1_tx_flush_en_4g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  ch1_tx_comp_sel_4g : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                             00：固定系数1；
                                                             01：固定系数2；
                                                             10：固定系数3；
                                                             11：可配系数。 */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_DIG_3_UNION;
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_flush_en_4g_START  (1)
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_flush_en_4g_END    (1)
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_comp_sel_4g_START  (2)
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_DIG_1_UNION
 结构说明  : rx_idle_dig_1 寄存器结构定义。地址偏移量:0x1F，初值:0x00，宽度:8
 寄存器说明: RX IDLE模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_idle : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                              00：固定系数1；
                                                              01：固定系数2；
                                                              10：固定系数3；
                                                              11：reserved。 */
        unsigned long  rx_comp_fix_idle    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                              0：系数不固定，由寄存器配置
                                                              1：系数固定 */
        unsigned long  rx_hb_bp_idle       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                              0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                              1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_idle        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                  2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                        /TDS_B/4G_C,        /4G_B,
                                                              00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                              others：reserved */
        unsigned long  rx_mode_dig_idle    : 3;  /* bit[5-7]: RX模式控制：
                                                              000：2G(默认)
                                                              001：3G_SC
                                                              010：4G &amp; ET &amp; APT
                                                              011：3G_DC
                                                              100：TDS
                                                              Others：CA */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_1_UNION;
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_b0_idle_START  (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_b0_idle_END    (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_START     (1)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_END       (1)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_START        (2)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_END          (2)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_START         (3)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_END           (4)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_START     (5)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_DIG_2_UNION
 结构说明  : rx_idle_dig_2 寄存器结构定义。地址偏移量:0x20，初值:0x13，宽度:8
 寄存器说明: RX IDLE模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_idle         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                              0：不CLOCK GATING
                                                              1：CLOCK GATING(默认)
                                                              (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_idle         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                              0：不CLOCK GATING
                                                              1：CLOCK GATING(默认)
                                                              (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_idle       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                              00：gain为0.5(默认)
                                                              01：gain为0.75
                                                              10：gain为0.85
                                                              11：Reserved */
        unsigned long  rx_comp_bp_idle     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                              0：不bypass(默认)
                                                              1：bypass */
        unsigned long  rx_clk_inv_idle     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                              0：正常
                                                              1：反向 */
        unsigned long  rx_flush_en_idle    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                              0：不使能
                                                              1：使能 */
        unsigned long  rx_comp_sel_b1_idle : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_2_UNION;
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_START          (0)
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_END            (0)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_START          (1)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_END            (1)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_START        (2)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_END          (3)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_START      (4)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_END        (4)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_START      (5)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_END        (5)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_START     (6)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_END       (6)
#define ABB_RX_IDLE_DIG_2_rx_comp_sel_b1_idle_START  (7)
#define ABB_RX_IDLE_DIG_2_rx_comp_sel_b1_idle_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_DIG_1_UNION
 结构说明  : tx_idle_dig_1 寄存器结构定义。地址偏移量:0x21，初值:0x02，宽度:8
 寄存器说明: TX IDLE模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_idle  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                           0：不bypass(默认)
                                                           1：bypass */
        unsigned long  tx_hb_bp_idle    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                           0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                           1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_idle     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                                2G,     3G,     4G,      TDS,      CDMA
                                                               (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                           0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                           1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                           2：-------,--------,15.36MHz,--------,--------
                                                           Others：Reserved */
        unsigned long  tx_mode_dig_idle : 3;  /* bit[5-7]: TX通道模式控制：
                                                           000：2G(默认)
                                                           001：3G
                                                           010：4G
                                                           011：TDS
                                                           100：CDMA
                                                           Others：Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_1_UNION;
#define ABB_TX_IDLE_DIG_1_tx_comp_bp_idle_START   (0)
#define ABB_TX_IDLE_DIG_1_tx_comp_bp_idle_END     (0)
#define ABB_TX_IDLE_DIG_1_tx_hb_bp_idle_START     (1)
#define ABB_TX_IDLE_DIG_1_tx_hb_bp_idle_END       (1)
#define ABB_TX_IDLE_DIG_1_tx_rate_idle_START      (2)
#define ABB_TX_IDLE_DIG_1_tx_rate_idle_END        (4)
#define ABB_TX_IDLE_DIG_1_tx_mode_dig_idle_START  (5)
#define ABB_TX_IDLE_DIG_1_tx_mode_dig_idle_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_DIG_2_UNION
 结构说明  : tx_idle_dig_2 寄存器结构定义。地址偏移量:0x22，初值:0x23，宽度:8
 寄存器说明: TX IDLE模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_idle       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_idle       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_idle     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                             0：0(默认)
                                                             1：2
                                                             2：4
                                                             3：6 */
        unsigned long  uddwa_dith_en_idle : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  dem_dwa_en_idle    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                             0：使用CLA模式
                                                             1：使用DWA模式(默认)  */
        unsigned long  dem_lsb_bp_idle    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                             0：DEM LSB 打开(默认)
                                                             1：DEM LSB bypass */
        unsigned long  dem_msb_bp_idle    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                             0：DEM MSB打开(默认)
                                                             1：DEM MSB bypass */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_2_UNION;
#define ABB_TX_IDLE_DIG_2_tx_q_pd_idle_START        (0)
#define ABB_TX_IDLE_DIG_2_tx_q_pd_idle_END          (0)
#define ABB_TX_IDLE_DIG_2_tx_i_pd_idle_START        (1)
#define ABB_TX_IDLE_DIG_2_tx_i_pd_idle_END          (1)
#define ABB_TX_IDLE_DIG_2_dem_const_idle_START      (2)
#define ABB_TX_IDLE_DIG_2_dem_const_idle_END        (3)
#define ABB_TX_IDLE_DIG_2_uddwa_dith_en_idle_START  (4)
#define ABB_TX_IDLE_DIG_2_uddwa_dith_en_idle_END    (4)
#define ABB_TX_IDLE_DIG_2_dem_dwa_en_idle_START     (5)
#define ABB_TX_IDLE_DIG_2_dem_dwa_en_idle_END       (5)
#define ABB_TX_IDLE_DIG_2_dem_lsb_bp_idle_START     (6)
#define ABB_TX_IDLE_DIG_2_dem_lsb_bp_idle_END       (6)
#define ABB_TX_IDLE_DIG_2_dem_msb_bp_idle_START     (7)
#define ABB_TX_IDLE_DIG_2_dem_msb_bp_idle_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_DIG_3_UNION
 结构说明  : tx_idle_dig_3 寄存器结构定义。地址偏移量:0x23，初值:0x01，宽度:8
 寄存器说明: TX IDLE模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0       : 1;  /* bit[0]  : 保留 */
        unsigned long  tx_flush_en_idle : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                           0：不使能
                                                           1：使能 */
        unsigned long  tx_comp_sel_idle : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                           00：固定系数1；
                                                           01：固定系数2；
                                                           10：固定系数3；
                                                           11：可配系数。 */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_END    (1)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_START  (2)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_TESTMODE_UNION
 结构说明  : ch1_testmode 寄存器结构定义。地址偏移量:0x41，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_pwr_on_rst  : 1;  /* bit[0]  : 全局软复位信号：comstarV520 Reserved
                                                          0：不复位(默认)
                                                          1：复位整个数字电路和模拟电路 */
        unsigned long  ch1_rx_chnl_sel : 2;  /* bit[1-2]: RX模拟测试模式下通道选择：
                                                          00：输出RXA I模拟调制器数据(默认)
                                                          01：输出RXA Q模拟调制器数据
                                                          10：输出RXB I模拟调制器数据
                                                          11：输出RXB Q模拟调制器数据 */
        unsigned long  ch1_test_mode   : 3;  /* bit[3-5]: bit[4:3]测试模式控制：
                                                          00：正常模式(默认)
                                                          01：数字算法逻辑环回模式
                                                          10：RX模拟测试模式(bypass RX数字滤波器)
                                                          11：Reserved
                                                          bit[5]RXC通道测试使能：
                                                          0：正常模式(默认)，RXA通道选择RXA的正常输入数据
                                                          1：RXC通道测试模式(将RXC通道输入数据复用到RXA通道) */
        unsigned long  ch1_rx_sw_rst   : 1;  /* bit[6]  : 数字部分RX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  ch1_tx_sw_rst   : 1;  /* bit[7]  : 数字部分TX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TESTMODE_UNION;
#define ABB_CH1_TESTMODE_ch1_pwr_on_rst_START   (0)
#define ABB_CH1_TESTMODE_ch1_pwr_on_rst_END     (0)
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_START  (1)
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_END    (2)
#define ABB_CH1_TESTMODE_ch1_test_mode_START    (3)
#define ABB_CH1_TESTMODE_ch1_test_mode_END      (5)
#define ABB_CH1_TESTMODE_ch1_rx_sw_rst_START    (6)
#define ABB_CH1_TESTMODE_ch1_rx_sw_rst_END      (6)
#define ABB_CH1_TESTMODE_ch1_tx_sw_rst_START    (7)
#define ABB_CH1_TESTMODE_ch1_tx_sw_rst_END      (7)


/*****************************************************************************
 结构名    : ABB_CH1_CTRL_UNION
 结构说明  : ch1_ctrl 寄存器结构定义。地址偏移量:0x42，初值:0x03，宽度:8
 寄存器说明: 通道控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_loop_out : 1;  /* bit[0]  : CH1通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号； */
        unsigned long  ch1_rxb_loop_out : 1;  /* bit[1]  : CH1通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号； */
        unsigned long  reserved         : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CTRL_UNION;
#define ABB_CH1_CTRL_ch1_rxa_loop_out_START  (0)
#define ABB_CH1_CTRL_ch1_rxa_loop_out_END    (0)
#define ABB_CH1_CTRL_ch1_rxb_loop_out_START  (1)
#define ABB_CH1_CTRL_ch1_rxb_loop_out_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_I_COEF1_UNION
 结构说明  : ch1_rxa_i_coef1 寄存器结构定义。地址偏移量:0x4B，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_i_c1     : 7;  /* bit[0-6]: RXA通道I路补偿滤波器系数C1,有符号数 */
        unsigned long  ch1_rxa_i_c3_msb : 1;  /* bit[7]  : RXA通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF1_UNION;
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c1_START      (0)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c1_END        (6)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c3_msb_START  (7)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_I_COEF3_UNION
 结构说明  : ch1_rxa_i_coef3 寄存器结构定义。地址偏移量:0x4D，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_i_c5 : 7;  /* bit[0-6]: RXA通道I路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF3_UNION;
#define ABB_CH1_RXA_I_COEF3_ch1_rxa_i_c5_START  (0)
#define ABB_CH1_RXA_I_COEF3_ch1_rxa_i_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_Q_COEF1_UNION
 结构说明  : ch1_rxa_q_coef1 寄存器结构定义。地址偏移量:0x50，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_q_c1     : 7;  /* bit[0-6]: RXA通道Q路补偿滤波器系数C1,有符号数 */
        unsigned long  ch1_rxa_q_c3_msb : 1;  /* bit[7]  : RXA通道Q路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF1_UNION;
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c1_START      (0)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c1_END        (6)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c3_msb_START  (7)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_Q_COEF3_UNION
 结构说明  : ch1_rxa_q_coef3 寄存器结构定义。地址偏移量:0x52，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_q_c5 : 7;  /* bit[0-6]: RXA通道Q路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF3_UNION;
#define ABB_CH1_RXA_Q_COEF3_ch1_rxa_q_c5_START  (0)
#define ABB_CH1_RXA_Q_COEF3_ch1_rxa_q_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RXB_I_COEF1_UNION
 结构说明  : ch1_rxb_i_coef1 寄存器结构定义。地址偏移量:0x55，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_i_c1     : 7;  /* bit[0-6]: RXB通道I路补偿滤波器系数C1,有符号数 */
        unsigned long  ch1_rxb_i_c3_msb : 1;  /* bit[7]  : RXB通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF1_UNION;
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c1_START      (0)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c1_END        (6)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c3_msb_START  (7)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_RXB_I_COEF3_UNION
 结构说明  : ch1_rxb_i_coef3 寄存器结构定义。地址偏移量:0x57，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_i_c5 : 7;  /* bit[0-6]: RXB通道I路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF3_UNION;
#define ABB_CH1_RXB_I_COEF3_ch1_rxb_i_c5_START  (0)
#define ABB_CH1_RXB_I_COEF3_ch1_rxb_i_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RXB_Q_COEF1_UNION
 结构说明  : ch1_rxb_q_coef1 寄存器结构定义。地址偏移量:0x5A，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_q_c1     : 7;  /* bit[0-6]: RXB通道Q路补偿滤波器系数C1,有符号数 */
        unsigned long  ch1_rxb_q_c3_msb : 1;  /* bit[7]  : RXB通道Q路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF1_UNION;
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c1_START      (0)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c1_END        (6)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c3_msb_START  (7)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_RXB_Q_COEF3_UNION
 结构说明  : ch1_rxb_q_coef3 寄存器结构定义。地址偏移量:0x5C，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_q_c5 : 7;  /* bit[0-6]: RXB通道Q路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF3_UNION;
#define ABB_CH1_RXB_Q_COEF3_ch1_rxb_q_c5_START  (0)
#define ABB_CH1_RXB_Q_COEF3_ch1_rxb_q_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RXA_DCR_CFG_UNION
 结构说明  : ch1_reg_rxa_dcr_cfg 寄存器结构定义。地址偏移量:0x5E，初值:0x46，宽度:8
 寄存器说明: RXA通道BLOCKING DCR配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_cfg_rxa_dcr_dly    : 5;  /* bit[0-4]: RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。 */
        unsigned long  ch1_cfg_rxa_dcr_l_para : 3;  /* bit[5-7]: RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DCR_CFG_UNION;
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_dly_START     (0)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_dly_END       (4)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_l_para_START  (5)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_l_para_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RXB_DCR_CFG_UNION
 结构说明  : ch1_reg_rxb_dcr_cfg 寄存器结构定义。地址偏移量:0x5F，初值:0x46，宽度:8
 寄存器说明: RXB通道BLOCKING DCR配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_cfg_rxb_dcr_dly    : 5;  /* bit[0-4]: RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。 */
        unsigned long  ch1_cfg_rxb_dcr_l_para : 3;  /* bit[5-7]: RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DCR_CFG_UNION;
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_dly_START     (0)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_dly_END       (4)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_l_para_START  (5)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_l_para_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RX_DCR_CTRL_UNION
 结构说明  : ch1_reg_rx_dcr_ctrl 寄存器结构定义。地址偏移量:0x60，初值:0x00，宽度:8
 寄存器说明: BLOCKING DCR功能控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_cfg_rxa_dcr_bypass : 1;  /* bit[0]  : RXA天线BLOCKING DCR功能bypass控制。
                                                                 0：DCR功能不bypasss；
                                                                 1：DCR功能bypass。 */
        unsigned long  ch1_cfg_rxb_dcr_bypass : 1;  /* bit[1]  : RXB天线BLOCKING DCR功能bypass控制。
                                                                 0：DCR功能不bypasss；
                                                                 1：DCR功能bypass。 */
        unsigned long  reserved               : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RX_DCR_CTRL_UNION;
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxa_dcr_bypass_START  (0)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxa_dcr_bypass_END    (0)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxb_dcr_bypass_START  (1)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxb_dcr_bypass_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_BLOCKING_UNION
 结构说明  : ch1_rxa_blocking 寄存器结构定义。地址偏移量:0x61，初值:0x00，宽度:8
 寄存器说明: RXA通道BLOCKING上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_blk_coeff : 5;  /* bit[0-4]: RXA天线BLOCKING上报值,2的幂次M */
        unsigned long  ch1_rxa_blk_power : 3;  /* bit[5-7]: RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_BLOCKING_UNION;
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_START  (0)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_END    (4)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_START  (5)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_RXB_BLOCKING_UNION
 结构说明  : ch1_rxb_blocking 寄存器结构定义。地址偏移量:0x62，初值:0x00，宽度:8
 寄存器说明: RXB通道BLOCKING上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_blk_coeff : 5;  /* bit[0-4]: RXB天线BLOCKING上报值,2的幂次M */
        unsigned long  ch1_rxb_blk_power : 3;  /* bit[5-7]: RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_BLOCKING_UNION;
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_START  (0)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_END    (4)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_START  (5)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RXA_DC_I_2_UNION
 结构说明  : ch1_reg_rxa_dc_i_2 寄存器结构定义。地址偏移量:0x64，初值:0x00，宽度:8
 寄存器说明: RXA通道I路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch1_rxa_dc_i_2 : 4;  /* bit[4-7]: RXA天线I路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DC_I_2_UNION;
#define ABB_CH1_REG_RXA_DC_I_2_ch1_rxa_dc_i_2_START  (4)
#define ABB_CH1_REG_RXA_DC_I_2_ch1_rxa_dc_i_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RXA_DC_Q_2_UNION
 结构说明  : ch1_reg_rxa_dc_q_2 寄存器结构定义。地址偏移量:0x66，初值:0x00，宽度:8
 寄存器说明: RXA通道Q路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch1_rxa_dc_q_2 : 4;  /* bit[4-7]: RXA天线Q路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DC_Q_2_UNION;
#define ABB_CH1_REG_RXA_DC_Q_2_ch1_rxa_dc_q_2_START  (4)
#define ABB_CH1_REG_RXA_DC_Q_2_ch1_rxa_dc_q_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RXB_DC_I_2_UNION
 结构说明  : ch1_reg_rxb_dc_i_2 寄存器结构定义。地址偏移量:0x68，初值:0x00，宽度:8
 寄存器说明: RXB通道I路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch1_rxb_dc_i_2 : 4;  /* bit[4-7]: RXB天线I路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DC_I_2_UNION;
#define ABB_CH1_REG_RXB_DC_I_2_ch1_rxb_dc_i_2_START  (4)
#define ABB_CH1_REG_RXB_DC_I_2_ch1_rxb_dc_i_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RXB_DC_Q_2_UNION
 结构说明  : ch1_reg_rxb_dc_q_2 寄存器结构定义。地址偏移量:0x6A，初值:0x00，宽度:8
 寄存器说明: RXB通道Q路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch1_rxb_dc_q_2 : 4;  /* bit[4-7]: RXB天线Q路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DC_Q_2_UNION;
#define ABB_CH1_REG_RXB_DC_Q_2_ch1_rxb_dc_q_2_START  (4)
#define ABB_CH1_REG_RXB_DC_Q_2_ch1_rxb_dc_q_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_DIG0_UNION
 结构说明  : ch1_reg_debug_dig0 寄存器结构定义。地址偏移量:0x6B，初值:0x64，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_sdm_rst_ctrl  : 1;  /* bit[0]  : TX通道SDM模块异常时复位控制
                                                            0：只复位SDM模块
                                                            1：复位整个TX通道 */
        unsigned long  ch1_dem_mode      : 1;  /* bit[1]  : TX通道DEM校准工作模式
                                                            0：正常工作
                                                            1：校准态，DEM输出为dem_code_man */
        unsigned long  ch1_tx_dem_sat    : 2;  /* bit[2-3]: TX DEM量化器输入限幅档位。
                                                            00：0.8125
                                                            01：0.796875(默认)
                                                            10：0.765625
                                                            11：0.75 */
        unsigned long  ch1_dither_en     : 1;  /* bit[4]  : TX通道SDM Dither控制：
                                                            0：不使能
                                                            1：使能 */
        unsigned long  ch1_tuning_val_en : 1;  /* bit[5]  : Tuning code来源选择：
                                                            0：寄存器配置
                                                            1：自动更新（默认） */
        unsigned long  ch1_tx_main_sd_bp : 1;  /* bit[6]  : TX SD模块主调制器旁路使能：
                                                            0：主调制器不旁路；
                                                            1：主调制器旁路（默认）； */
        unsigned long  reserved          : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_DIG0_UNION;
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_START   (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_END     (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_START       (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_END         (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_START     (2)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_END       (3)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_START      (4)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_END        (4)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tuning_val_en_START  (5)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tuning_val_en_END    (5)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_START  (6)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_TESTMODE_UNION
 结构说明  : ch0_testmode 寄存器结构定义。地址偏移量:0xA1，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_pwr_on_rst  : 1;  /* bit[0]  : 全局软复位信号：
                                                          0：不复位(默认)
                                                          1：复位整个数字电路和模拟电路 */
        unsigned long  ch0_rx_chnl_sel : 2;  /* bit[1-2]: RX模拟测试模式下通道选择：
                                                          00：输出RXA I模拟调制器数据(默认)
                                                          01：输出RXA Q模拟调制器数据
                                                          10：输出RXB I模拟调制器数据
                                                          11：输出RXB Q模拟调制器数据 */
        unsigned long  ch0_test_mode   : 3;  /* bit[3-5]: bit[4:3]测试模式控制：
                                                          00：正常模式(默认)
                                                          01：数字算法逻辑环回模式
                                                          10：RX模拟测试模式(bypass RX数字滤波器)
                                                          11：数字/模拟接口环回
                                                          bit[5]RXC通道测试使能：（ComstarV510 reserved）
                                                          0：正常模式(默认)，RXA通道选择RXA的正常输入数据
                                                          1：RXC通道测试模式(将RXC通道输入数据复用到RXA通道) */
        unsigned long  ch0_rx_sw_rst   : 1;  /* bit[6]  : 数字部分RX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  ch0_tx_sw_rst   : 1;  /* bit[7]  : 数字部分TX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TESTMODE_UNION;
#define ABB_CH0_TESTMODE_ch0_pwr_on_rst_START   (0)
#define ABB_CH0_TESTMODE_ch0_pwr_on_rst_END     (0)
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_START  (1)
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_END    (2)
#define ABB_CH0_TESTMODE_ch0_test_mode_START    (3)
#define ABB_CH0_TESTMODE_ch0_test_mode_END      (5)
#define ABB_CH0_TESTMODE_ch0_rx_sw_rst_START    (6)
#define ABB_CH0_TESTMODE_ch0_rx_sw_rst_END      (6)
#define ABB_CH0_TESTMODE_ch0_tx_sw_rst_START    (7)
#define ABB_CH0_TESTMODE_ch0_tx_sw_rst_END      (7)


/*****************************************************************************
 结构名    : ABB_CH0_CTRL_UNION
 结构说明  : ch0_ctrl 寄存器结构定义。地址偏移量:0xA2，初值:0x03，宽度:8
 寄存器说明: 通道控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_loop_out : 1;  /* bit[0]  : CH0通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号； */
        unsigned long  ch0_rxb_loop_out : 1;  /* bit[1]  : CH0通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号； */
        unsigned long  reserved         : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CTRL_UNION;
#define ABB_CH0_CTRL_ch0_rxa_loop_out_START  (0)
#define ABB_CH0_CTRL_ch0_rxa_loop_out_END    (0)
#define ABB_CH0_CTRL_ch0_rxb_loop_out_START  (1)
#define ABB_CH0_CTRL_ch0_rxb_loop_out_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_I_COEF1_UNION
 结构说明  : ch0_rxa_i_coef1 寄存器结构定义。地址偏移量:0xAB，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_c1     : 7;  /* bit[0-6]: RXA通道I路补偿滤波器系数C1,有符号数 */
        unsigned long  ch0_rxa_i_c3_msb : 1;  /* bit[7]  : RXA通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF1_UNION;
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c1_START      (0)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c1_END        (6)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c3_msb_START  (7)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_I_COEF3_UNION
 结构说明  : ch0_rxa_i_coef3 寄存器结构定义。地址偏移量:0xAD，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_c5 : 7;  /* bit[0-6]: RXA通道I路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF3_UNION;
#define ABB_CH0_RXA_I_COEF3_ch0_rxa_i_c5_START  (0)
#define ABB_CH0_RXA_I_COEF3_ch0_rxa_i_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_Q_COEF1_UNION
 结构说明  : ch0_rxa_q_coef1 寄存器结构定义。地址偏移量:0xB0，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_c1     : 7;  /* bit[0-6]: RXA通道Q路补偿滤波器系数C1,有符号数 */
        unsigned long  ch0_rxa_q_c3_msb : 1;  /* bit[7]  : RXA通道Q路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF1_UNION;
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c1_START      (0)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c1_END        (6)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c3_msb_START  (7)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_Q_COEF3_UNION
 结构说明  : ch0_rxa_q_coef3 寄存器结构定义。地址偏移量:0xB2，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_c5 : 7;  /* bit[0-6]: RXA通道Q路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF3_UNION;
#define ABB_CH0_RXA_Q_COEF3_ch0_rxa_q_c5_START  (0)
#define ABB_CH0_RXA_Q_COEF3_ch0_rxa_q_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_I_COEF1_UNION
 结构说明  : ch0_rxb_i_coef1 寄存器结构定义。地址偏移量:0xB5，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_c1     : 7;  /* bit[0-6]: RXB通道I路补偿滤波器系数C1,有符号数 */
        unsigned long  ch0_rxb_i_c3_msb : 1;  /* bit[7]  : RXB通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF1_UNION;
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c1_START      (0)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c1_END        (6)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c3_msb_START  (7)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_I_COEF3_UNION
 结构说明  : ch0_rxb_i_coef3 寄存器结构定义。地址偏移量:0xB7，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_c5 : 7;  /* bit[0-6]: RXB通道I路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF3_UNION;
#define ABB_CH0_RXB_I_COEF3_ch0_rxb_i_c5_START  (0)
#define ABB_CH0_RXB_I_COEF3_ch0_rxb_i_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_Q_COEF1_UNION
 结构说明  : ch0_rxb_q_coef1 寄存器结构定义。地址偏移量:0xBA，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_c1     : 7;  /* bit[0-6]: RXB通道Q路补偿滤波器系数C1,有符号数 */
        unsigned long  ch0_rxb_q_c3_msb : 1;  /* bit[7]  : RXB通道Q路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF1_UNION;
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c1_START      (0)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c1_END        (6)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c3_msb_START  (7)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_Q_COEF3_UNION
 结构说明  : ch0_rxb_q_coef3 寄存器结构定义。地址偏移量:0xBC，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_c5 : 7;  /* bit[0-6]: RXB通道Q路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF3_UNION;
#define ABB_CH0_RXB_Q_COEF3_ch0_rxb_q_c5_START  (0)
#define ABB_CH0_RXB_Q_COEF3_ch0_rxb_q_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RXA_DCR_CFG_UNION
 结构说明  : ch0_reg_rxa_dcr_cfg 寄存器结构定义。地址偏移量:0xBE，初值:0x46，宽度:8
 寄存器说明: RXA通道BLOCKING DCR配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfg_rxa_dcr_dly    : 5;  /* bit[0-4]: RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。 */
        unsigned long  ch0_cfg_rxa_dcr_l_para : 3;  /* bit[5-7]: RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DCR_CFG_UNION;
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_dly_START     (0)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_dly_END       (4)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_l_para_START  (5)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_l_para_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RXB_DCR_CFG_UNION
 结构说明  : ch0_reg_rxb_dcr_cfg 寄存器结构定义。地址偏移量:0xBF，初值:0x46，宽度:8
 寄存器说明: RXB通道BLOCKING DCR配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfg_rxb_dcr_dly    : 5;  /* bit[0-4]: RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。 */
        unsigned long  ch0_cfg_rxb_dcr_l_para : 3;  /* bit[5-7]: RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DCR_CFG_UNION;
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_dly_START     (0)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_dly_END       (4)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_l_para_START  (5)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_l_para_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RX_DCR_CTRL_UNION
 结构说明  : ch0_reg_rx_dcr_ctrl 寄存器结构定义。地址偏移量:0xC0，初值:0x00，宽度:8
 寄存器说明: BLOCKING DCR功能控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfg_rxa_dcr_bypass : 1;  /* bit[0]  : RXA天线BLOCKING DCR功能bypass控制。
                                                                 0：DCR功能不bypasss；
                                                                 1：DCR功能bypass。 */
        unsigned long  ch0_cfg_rxb_dcr_bypass : 1;  /* bit[1]  : RXB天线BLOCKING DCR功能bypass控制。
                                                                 0：DCR功能不bypasss；
                                                                 1：DCR功能bypass。 */
        unsigned long  reserved               : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RX_DCR_CTRL_UNION;
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxa_dcr_bypass_START  (0)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxa_dcr_bypass_END    (0)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxb_dcr_bypass_START  (1)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxb_dcr_bypass_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_BLOCKING_UNION
 结构说明  : ch0_rxa_blocking 寄存器结构定义。地址偏移量:0xC1，初值:0x00，宽度:8
 寄存器说明: RXA通道BLOCKING上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_blk_coeff : 5;  /* bit[0-4]: RXA天线BLOCKING上报值,2的幂次M */
        unsigned long  ch0_rxa_blk_power : 3;  /* bit[5-7]: RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_BLOCKING_UNION;
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_START  (0)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_END    (4)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_START  (5)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_BLOCKING_UNION
 结构说明  : ch0_rxb_blocking 寄存器结构定义。地址偏移量:0xC2，初值:0x00，宽度:8
 寄存器说明: RXB通道BLOCKING上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_blk_coeff : 5;  /* bit[0-4]: RXB天线BLOCKING上报值,2的幂次M */
        unsigned long  ch0_rxb_blk_power : 3;  /* bit[5-7]: RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_BLOCKING_UNION;
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_START  (0)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_END    (4)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_START  (5)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RXA_DC_I_2_UNION
 结构说明  : ch0_reg_rxa_dc_i_2 寄存器结构定义。地址偏移量:0xC4，初值:0x00，宽度:8
 寄存器说明: RXA通道I路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch0_rxa_dc_i_2 : 4;  /* bit[4-7]: RXA天线I路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DC_I_2_UNION;
#define ABB_CH0_REG_RXA_DC_I_2_ch0_rxa_dc_i_2_START  (4)
#define ABB_CH0_REG_RXA_DC_I_2_ch0_rxa_dc_i_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RXA_DC_Q_2_UNION
 结构说明  : ch0_reg_rxa_dc_q_2 寄存器结构定义。地址偏移量:0xC6，初值:0x00，宽度:8
 寄存器说明: RXA通道Q路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch0_rxa_dc_q_2 : 4;  /* bit[4-7]: RXA天线Q路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DC_Q_2_UNION;
#define ABB_CH0_REG_RXA_DC_Q_2_ch0_rxa_dc_q_2_START  (4)
#define ABB_CH0_REG_RXA_DC_Q_2_ch0_rxa_dc_q_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RXB_DC_I_2_UNION
 结构说明  : ch0_reg_rxb_dc_i_2 寄存器结构定义。地址偏移量:0xC8，初值:0x00，宽度:8
 寄存器说明: RXB通道I路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch0_rxb_dc_i_2 : 4;  /* bit[4-7]: RXB天线I路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DC_I_2_UNION;
#define ABB_CH0_REG_RXB_DC_I_2_ch0_rxb_dc_i_2_START  (4)
#define ABB_CH0_REG_RXB_DC_I_2_ch0_rxb_dc_i_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RXB_DC_Q_2_UNION
 结构说明  : ch0_reg_rxb_dc_q_2 寄存器结构定义。地址偏移量:0xCA，初值:0x00，宽度:8
 寄存器说明: RXB通道Q路BLOCKING DC上报寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch0_rxb_dc_q_2 : 4;  /* bit[4-7]: RXB天线Q路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DC_Q_2_UNION;
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_START  (4)
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_DIG0_UNION
 结构说明  : ch0_reg_debug_dig0 寄存器结构定义。地址偏移量:0xCB，初值:0x64，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_sdm_rst_ctrl  : 1;  /* bit[0]  : TX通道SDM模块异常时复位控制
                                                            0：只复位SDM模块
                                                            1：复位整个TX通道 */
        unsigned long  ch0_dem_mode      : 1;  /* bit[1]  : TX通道DEM校准工作模式
                                                            0：正常工作
                                                            1：校准态，DEM输出为dem_code_man */
        unsigned long  ch0_tx_dem_sat    : 2;  /* bit[2-3]: TX DEM量化器输入限幅档位。
                                                            00：0.8125
                                                            01：0.796875(默认)
                                                            10：0.765625
                                                            11：0.75 */
        unsigned long  ch0_dither_en     : 1;  /* bit[4]  : TX通道SDM Dither控制：
                                                            0：不使能
                                                            1：使能 */
        unsigned long  ch0_tuning_val_en : 1;  /* bit[5]  : Tuning code来源选择：
                                                            0：寄存器配置
                                                            1：自动更新（默认） */
        unsigned long  ch0_tx_main_sd_bp : 1;  /* bit[6]  : TX SD模块主调制器旁路使能：
                                                            0：主调制器不旁路；
                                                            1：主调制器旁路（默认）； */
        unsigned long  reserved          : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_DIG0_UNION;
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_START   (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_END     (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_START       (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_END         (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_START     (2)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_END       (3)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_START      (4)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_END        (4)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tuning_val_en_START  (5)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tuning_val_en_END    (5)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_START  (6)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_END    (6)


/*****************************************************************************
 结构名    : ABB_SINE_GENERATE_UNION
 结构说明  : sine_generate 寄存器结构定义。地址偏移量:0xFF，初值:0x10，宽度:8
 寄存器说明: SINE发送寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_sine_enable : 1;  /* bit[0]  : ch0正弦波发送使能
                                                          0：不发送
                                                          1：发送 */
        unsigned long  ch1_sine_enable : 1;  /* bit[1]  : ch1正弦波发送使能
                                                          0：不发送
                                                          1：发送 */
        unsigned long  sine_amp        : 2;  /* bit[2-3]: 正弦波发送幅度控制
                                                          00：满量程
                                                          01：3/4量程
                                                          10：1/2量程
                                                          11：1/4量程 */
        unsigned long  sine_freq       : 4;  /* bit[4-7]: 正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SINE_GENERATE_UNION;
#define ABB_SINE_GENERATE_ch0_sine_enable_START  (0)
#define ABB_SINE_GENERATE_ch0_sine_enable_END    (0)
#define ABB_SINE_GENERATE_ch1_sine_enable_START  (1)
#define ABB_SINE_GENERATE_ch1_sine_enable_END    (1)
#define ABB_SINE_GENERATE_sine_amp_START         (2)
#define ABB_SINE_GENERATE_sine_amp_END           (3)
#define ABB_SINE_GENERATE_sine_freq_START        (4)
#define ABB_SINE_GENERATE_sine_freq_END          (7)


/*****************************************************************************
 结构名    : ABB_RX_CH1_3G_DIG_1_UNION
 结构说明  : rx_ch1_3g_dig_1 寄存器结构定义。地址偏移量:0x180，初值:0x26，宽度:8
 寄存器说明: CH1 RX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_comp_sel_b0_3g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                                00：固定系数1；
                                                                01：固定系数2；
                                                                10：固定系数3；
                                                                11：reserved。 */
        unsigned long  ch1_rx_comp_fix_3g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                                0：系数不固定，由寄存器配置
                                                                1：系数固定 */
        unsigned long  ch1_rx_hb_bp_3g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                                0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                                1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch1_rx_rate_3g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                                others：reserved */
        unsigned long  ch1_rx_mode_dig_3g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                                000：2G(默认)
                                                                001：3G_SC/TDS_B/4G_C
                                                                010：4G
                                                                011：3G_DC/4G_B
                                                                100：TDS
                                                                101：CDMA
                                                                Others：Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_DIG_1_UNION;
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_fix_3g_START     (1)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_fix_3g_END       (1)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_hb_bp_3g_START        (2)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_hb_bp_3g_END          (2)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_rate_3g_START         (3)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_rate_3g_END           (4)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_mode_dig_3g_START     (5)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_mode_dig_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_CH1_3G_DIG_2_UNION
 结构说明  : rx_ch1_3g_dig_2 寄存器结构定义。地址偏移量:0x181，初值:0x03，宽度:8
 寄存器说明: CH1 RX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_3g         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch1_rxb_pd_3g         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                                0：不CLOCK GATING
                                                                1：CLOCK GATING(默认)
                                                                (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch1_gain_sel_3g       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                                00：gain为0.5(默认)
                                                                01：gain为0.75
                                                                10：gain为0.85
                                                                11：Reserved */
        unsigned long  ch1_rx_comp_bp_3g     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                                0：不bypass(默认)
                                                                1：bypass */
        unsigned long  ch1_rx_clk_inv_3g     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                                0：正常
                                                                1：反向 */
        unsigned long  ch1_rx_flush_en_3g    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                                0：不使能
                                                                1：使能 */
        unsigned long  ch1_rx_comp_sel_b1_3g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_DIG_2_UNION;
#define ABB_RX_CH1_3G_DIG_2_ch1_rxa_pd_3g_START          (0)
#define ABB_RX_CH1_3G_DIG_2_ch1_rxa_pd_3g_END            (0)
#define ABB_RX_CH1_3G_DIG_2_ch1_rxb_pd_3g_START          (1)
#define ABB_RX_CH1_3G_DIG_2_ch1_rxb_pd_3g_END            (1)
#define ABB_RX_CH1_3G_DIG_2_ch1_gain_sel_3g_START        (2)
#define ABB_RX_CH1_3G_DIG_2_ch1_gain_sel_3g_END          (3)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_bp_3g_START      (4)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_bp_3g_END        (4)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_clk_inv_3g_START      (5)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_clk_inv_3g_END        (5)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_flush_en_3g_START     (6)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_flush_en_3g_END       (6)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_sel_b1_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH1_3G_DIG_1_UNION
 结构说明  : tx_ch1_3g_dig_1 寄存器结构定义。地址偏移量:0x182，初值:0x20，宽度:8
 寄存器说明: CH1 TX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_bp_3g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch1_tx_hb_bp_3g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  ch1_tx_rate_3g     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2：-------,--------,15.36MHz,--------,--------
                                                             Others：Reserved */
        unsigned long  ch1_tx_mode_dig_3g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_DIG_1_UNION;
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_comp_bp_3g_START   (0)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_comp_bp_3g_END     (0)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_hb_bp_3g_START     (1)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_hb_bp_3g_END       (1)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_rate_3g_START      (2)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_rate_3g_END        (4)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_mode_dig_3g_START  (5)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CH1_3G_DIG_2_UNION
 结构说明  : tx_ch1_3g_dig_2 寄存器结构定义。地址偏移量:0x183，初值:0x23，宽度:8
 寄存器说明: CH1 TX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_q_pd_3g       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch1_tx_i_pd_3g       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                               0：不CLOCK GATING
                                                               1：CLOCK GATING(默认)
                                                               (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  ch1_dem_const_3g     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                               0：0(默认)
                                                               1：2
                                                               2：4
                                                               3：6 */
        unsigned long  ch1_uddwa_dith_en_3g : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                               0：不使能
                                                               1：使能 */
        unsigned long  ch1_dem_dwa_en_3g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                               0：使用CLA模式
                                                               1：使用DWA模式(默认)  */
        unsigned long  ch1_dem_lsb_bp_3g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                               0：DEM LSB 打开(默认)
                                                               1：DEM LSB bypass */
        unsigned long  ch1_dem_msb_bp_3g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                               0：DEM MSB打开(默认)
                                                               1：DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_DIG_2_UNION;
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_q_pd_3g_START        (0)
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_q_pd_3g_END          (0)
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_i_pd_3g_START        (1)
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_i_pd_3g_END          (1)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_const_3g_START      (2)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_const_3g_END        (3)
#define ABB_TX_CH1_3G_DIG_2_ch1_uddwa_dith_en_3g_START  (4)
#define ABB_TX_CH1_3G_DIG_2_ch1_uddwa_dith_en_3g_END    (4)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_dwa_en_3g_START     (5)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_dwa_en_3g_END       (5)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_lsb_bp_3g_START     (6)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_lsb_bp_3g_END       (6)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_msb_bp_3g_START     (7)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_CH1_3G_DIG_3_UNION
 结构说明  : tx_ch1_3g_dig_3 寄存器结构定义。地址偏移量:0x184，初值:0x01，宽度:8
 寄存器说明: CH1 TX 3G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : 保留 */
        unsigned long  ch1_tx_flush_en_3g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  ch1_tx_comp_sel_3g : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                             00：固定系数1；
                                                             01：固定系数2；
                                                             10：固定系数3；
                                                             11：可配系数。 */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_DIG_3_UNION;
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_flush_en_3g_START  (1)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_flush_en_3g_END    (1)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_comp_sel_3g_START  (2)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_LINE_SEL_UNION
 结构说明  : ch1_line_sel 寄存器结构定义。地址偏移量:0x1C0，初值:0x00，宽度:8
 寄存器说明: 线控强制配置使能。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_sel : 1;  /* bit[0]: RXA通道线控选择强配使能
                                                       0：选择线控使能
                                                       1：选择强配使能 */
        unsigned long  ch1_rxb_en_sel : 1;  /* bit[1]: RXB通道线控选择强配使能
                                                       0：选择线控使能
                                                       1：选择强配使能 */
        unsigned long  ch1_tx_en_sel  : 1;  /* bit[2]: TX通道线控选择强配使能
                                                       0：选择线控使能
                                                       1：选择强配使能 */
        unsigned long  reserved_0     : 1;  /* bit[3]: 保留 */
        unsigned long  ch1_rxa_en_cfg : 1;  /* bit[4]: RXA通道强配线控 */
        unsigned long  ch1_rxb_en_cfg : 1;  /* bit[5]: RXB通道强配线控 */
        unsigned long  ch1_tx_en_cfg  : 1;  /* bit[6]: TX通道强配线控 */
        unsigned long  reserved_1     : 1;  /* bit[7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_SEL_UNION;
#define ABB_CH1_LINE_SEL_ch1_rxa_en_sel_START  (0)
#define ABB_CH1_LINE_SEL_ch1_rxa_en_sel_END    (0)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_sel_START  (1)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_sel_END    (1)
#define ABB_CH1_LINE_SEL_ch1_tx_en_sel_START   (2)
#define ABB_CH1_LINE_SEL_ch1_tx_en_sel_END     (2)
#define ABB_CH1_LINE_SEL_ch1_rxa_en_cfg_START  (4)
#define ABB_CH1_LINE_SEL_ch1_rxa_en_cfg_END    (4)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_cfg_START  (5)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_cfg_END    (5)
#define ABB_CH1_LINE_SEL_ch1_tx_en_cfg_START   (6)
#define ABB_CH1_LINE_SEL_ch1_tx_en_cfg_END     (6)


/*****************************************************************************
 结构名    : ABB_CH1_LINE_CFG_UNION
 结构说明  : ch1_line_cfg 寄存器结构定义。地址偏移量:0x1C1，初值:0x00，宽度:8
 寄存器说明: 模式线控强制配置。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: 线控信号CH1_TX_LINE_CTRL_MODE强制配置值
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：ET模式
                                                                    6：APT模式
                                                                    7：CA模式 */
        unsigned long  ch1_rx_line_ctrl_mode_cfg : 3;  /* bit[3-5]: 线控信号CH1_RX_LINE_CTRL_MODE强制配置值
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：ET模式
                                                                    6：APT模式
                                                                    7：CA模式 */
        unsigned long  ch1_line_ctrl_mode_sel    : 1;  /* bit[6]  : 线控信号CH1_LINE_CTRL_MODE强制配置使能 */
        unsigned long  reserved                  : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_CFG_UNION;
#define ABB_CH1_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH1_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH1_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_START  (3)
#define ABB_CH1_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_END    (5)
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_sel_START     (6)
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_sel_END       (6)


/*****************************************************************************
 结构名    : ABB_CH1_CLK_SEL_UNION
 结构说明  : ch1_clk_sel 寄存器结构定义。地址偏移量:0x1C2，初值:0x00，宽度:8
 寄存器说明: 时钟门控寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_blk_clk_sel : 1;  /* bit[0]  : BLOCKING自动门控使能：
                                                          0：使能
                                                          1：不使能 */
        unsigned long  ch1_blk_en_cfg  : 1;  /* bit[1]  : 线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值 */
        unsigned long  ch1_blk_en_sel  : 1;  /* bit[2]  : 线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能 */
        unsigned long  reserved        : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CLK_SEL_UNION;
#define ABB_CH1_CLK_SEL_ch1_blk_clk_sel_START  (0)
#define ABB_CH1_CLK_SEL_ch1_blk_clk_sel_END    (0)
#define ABB_CH1_CLK_SEL_ch1_blk_en_cfg_START   (1)
#define ABB_CH1_CLK_SEL_ch1_blk_en_cfg_END     (1)
#define ABB_CH1_CLK_SEL_ch1_blk_en_sel_START   (2)
#define ABB_CH1_CLK_SEL_ch1_blk_en_sel_END     (2)


/*****************************************************************************
 结构名    : ABB_CH0_LINE_SEL_UNION
 结构说明  : ch0_line_sel 寄存器结构定义。地址偏移量:0x1D0，初值:0x00，宽度:8
 寄存器说明: 线控强制配置使能。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_sel : 1;  /* bit[0]: RXA通道线控选择强配使能
                                                       0：选择线控使能
                                                       1：选择强配使能 */
        unsigned long  ch0_rxb_en_sel : 1;  /* bit[1]: RXB通道线控选择强配使能
                                                       0：选择线控使能
                                                       1：选择强配使能 */
        unsigned long  ch0_tx_en_sel  : 1;  /* bit[2]: TX通道线控选择强配使能
                                                       0：选择线控使能
                                                       1：选择强配使能 */
        unsigned long  reserved_0     : 1;  /* bit[3]: 保留 */
        unsigned long  ch0_rxa_en_cfg : 1;  /* bit[4]: RXA通道强配线控 */
        unsigned long  ch0_rxb_en_cfg : 1;  /* bit[5]: RXB通道强配线控 */
        unsigned long  ch0_tx_en_cfg  : 1;  /* bit[6]: TX通道强配线控 */
        unsigned long  reserved_1     : 1;  /* bit[7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_SEL_UNION;
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_START  (0)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_END    (0)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_START  (1)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_END    (1)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_START   (2)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_END     (2)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_cfg_START  (4)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_cfg_END    (4)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_cfg_START  (5)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_cfg_END    (5)
#define ABB_CH0_LINE_SEL_ch0_tx_en_cfg_START   (6)
#define ABB_CH0_LINE_SEL_ch0_tx_en_cfg_END     (6)


/*****************************************************************************
 结构名    : ABB_CH0_LINE_CFG_UNION
 结构说明  : ch0_line_cfg 寄存器结构定义。地址偏移量:0x1D1，初值:0x00，宽度:8
 寄存器说明: 模式线控强制配置。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: 线控信号CH0_TX_LINE_CTRL_MODE强制配置值
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：ET模式
                                                                    6：APT模式
                                                                    7：CA模式 */
        unsigned long  ch0_rx_line_ctrl_mode_cfg : 3;  /* bit[3-5]: 线控信号CH0_RX_LINE_CTRL_MODE强制配置值
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：ET模式
                                                                    6：APT模式
                                                                    7：CA模式 */
        unsigned long  ch0_line_ctrl_mode_sel    : 1;  /* bit[6]  : 线控信号CH0_LINE_CTRL_MODE强制配置使能 */
        unsigned long  reserved                  : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_CFG_UNION;
#define ABB_CH0_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_START  (3)
#define ABB_CH0_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_END    (5)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_START     (6)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_END       (6)


/*****************************************************************************
 结构名    : ABB_CH0_CLK_SEL_UNION
 结构说明  : ch0_clk_sel 寄存器结构定义。地址偏移量:0x1D2，初值:0x00，宽度:8
 寄存器说明: 时钟门控寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_blk_clk_sel : 1;  /* bit[0]  : BLOCKING自动门控使能：
                                                          0：使能
                                                          1：不使能 */
        unsigned long  ch0_blk_en_cfg  : 1;  /* bit[1]  : 线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值 */
        unsigned long  ch0_blk_en_sel  : 1;  /* bit[2]  : 线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能 */
        unsigned long  reserved        : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CLK_SEL_UNION;
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_START  (0)
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_END    (0)
#define ABB_CH0_CLK_SEL_ch0_blk_en_cfg_START   (1)
#define ABB_CH0_CLK_SEL_ch0_blk_en_cfg_END     (1)
#define ABB_CH0_CLK_SEL_ch0_blk_en_sel_START   (2)
#define ABB_CH0_CLK_SEL_ch0_blk_en_sel_END     (2)


/*****************************************************************************
 结构名    : ABB_CH0_TDS_RX_DLY_UNION
 结构说明  : CH0_TDS_RX_DLY 寄存器结构定义。地址偏移量:0x200，初值:0x00，宽度:8
 寄存器说明: 通道0 TDS配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tds_rx_dly : 3;  /* bit[0-2]: 通道0 TDS模式定时调整配置寄存器，配置值和时延关系为
                                                         0: delay 0 chip
                                                         1: delay 4/120 chips
                                                         2: delay 8/120 chips
                                                         3: delay 11/120 chips
                                                         4: delay 15/120 chips
                                                         5: delay 19/120 chips
                                                         6: delay 23/120 chips
                                                         7: delay 26/120 chips */
        unsigned long  reserved       : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TDS_RX_DLY_UNION;
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_START  (0)
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_END    (2)


/*****************************************************************************
 结构名    : ABB_CH0_FLUSH_CFG1_UNION
 结构说明  : CH0_FLUSH_CFG1 寄存器结构定义。地址偏移量:0x233，初值:0x40，宽度:8
 寄存器说明: 通道0配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_flush_width_msb : 3;  /* bit[0-2]: 通道0 flush宽度[10:8]，单位为19.2M时钟周期。 */
        unsigned long  ch0_flush_value     : 5;  /* bit[3-7]: 通道0 FLUSH值，默认为8。 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_FLUSH_CFG1_UNION;
#define ABB_CH0_FLUSH_CFG1_ch0_flush_width_msb_START  (0)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_width_msb_END    (2)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_value_START      (3)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_value_END        (7)


/*****************************************************************************
 结构名    : ABB_CH1_TDS_RX_DLY_UNION
 结构说明  : CH1_TDS_RX_DLY 寄存器结构定义。地址偏移量:0x262，初值:0x00，宽度:8
 寄存器说明: 通道1 TDS配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tds_rx_dly : 3;  /* bit[0-2]: 通道1 TDS模式定时调整配置寄存器，配置值和时延关系为
                                                         0: delay 0 chip
                                                         1: delay 4/120 chips
                                                         2: delay 8/120 chips
                                                         3: delay 11/120 chips
                                                         4: delay 15/120 chips
                                                         5: delay 19/120 chips
                                                         6: delay 23/120 chips
                                                         7: delay 26/120 chips */
        unsigned long  reserved       : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TDS_RX_DLY_UNION;
#define ABB_CH1_TDS_RX_DLY_ch1_tds_rx_dly_START  (0)
#define ABB_CH1_TDS_RX_DLY_ch1_tds_rx_dly_END    (2)


/*****************************************************************************
 结构名    : ABB_CH1_FLUSH_CFG1_UNION
 结构说明  : CH1_FLUSH_CFG1 寄存器结构定义。地址偏移量:0x295，初值:0x40，宽度:8
 寄存器说明: 通道1配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_flush_width_msb : 3;  /* bit[0-2]: 通道1 flush宽度[10:8]，单位为19.2M时钟周期。 */
        unsigned long  ch1_flush_value     : 5;  /* bit[3-7]: 通道1 FLUSH值，默认为8。 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_FLUSH_CFG1_UNION;
#define ABB_CH1_FLUSH_CFG1_ch1_flush_width_msb_START  (0)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_width_msb_END    (2)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_value_START      (3)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_value_END        (7)


/*****************************************************************************
 结构名    : ABB_RX_C_DIG_1_UNION
 结构说明  : rx_c_dig_1 寄存器结构定义。地址偏移量:0x400，初值:0xA6，宽度:8
 寄存器说明: RX C模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_c : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                           00：固定系数1；
                                                           01：固定系数2；
                                                           10：固定系数3；
                                                           11：reserved。 */
        unsigned long  rx_comp_fix_c    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                           0：系数不固定，由寄存器配置
                                                           1：系数固定 */
        unsigned long  rx_hb_bp_c       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                           0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                           1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_c        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                               2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                     /TDS_B/4G_C,        /4G_B,
                                                           00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                           others：reserved */
        unsigned long  rx_mode_dig_c    : 3;  /* bit[5-7]: RX通道模式控制：
                                                           000：2G
                                                           001：3G_SC/TDS_B/4G_C
                                                           010：4G
                                                           011：3G_DC/4G_B
                                                           100：TDS
                                                           101：CDMA(默认)
                                                           Others：Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_1_UNION;
#define ABB_RX_C_DIG_1_rx_comp_sel_b0_c_START  (0)
#define ABB_RX_C_DIG_1_rx_comp_sel_b0_c_END    (0)
#define ABB_RX_C_DIG_1_rx_comp_fix_c_START     (1)
#define ABB_RX_C_DIG_1_rx_comp_fix_c_END       (1)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_START        (2)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_END          (2)
#define ABB_RX_C_DIG_1_rx_rate_c_START         (3)
#define ABB_RX_C_DIG_1_rx_rate_c_END           (4)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_START     (5)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_C_DIG_2_UNION
 结构说明  : rx_c_dig_2 寄存器结构定义。地址偏移量:0x401，初值:0x93，宽度:8
 寄存器说明: RX C模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_c         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_c         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_c       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                           00：gain为0.5(默认)
                                                           01：gain为0.75
                                                           10：gain为0.85
                                                           11：Reserved */
        unsigned long  rx_comp_bp_c     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                           0：不bypass
                                                           1：bypass(默认) */
        unsigned long  rx_clk_inv_c     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                           0：正常
                                                           1：反向 */
        unsigned long  rx_flush_en_c    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                           0：不使能
                                                           1：使能 */
        unsigned long  rx_comp_sel_b1_c : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_2_UNION;
#define ABB_RX_C_DIG_2_rxa_pd_c_START          (0)
#define ABB_RX_C_DIG_2_rxa_pd_c_END            (0)
#define ABB_RX_C_DIG_2_rxb_pd_c_START          (1)
#define ABB_RX_C_DIG_2_rxb_pd_c_END            (1)
#define ABB_RX_C_DIG_2_gain_sel_c_START        (2)
#define ABB_RX_C_DIG_2_gain_sel_c_END          (3)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_START      (4)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_END        (4)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_START      (5)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_END        (5)
#define ABB_RX_C_DIG_2_rx_flush_en_c_START     (6)
#define ABB_RX_C_DIG_2_rx_flush_en_c_END       (6)
#define ABB_RX_C_DIG_2_rx_comp_sel_b1_c_START  (7)
#define ABB_RX_C_DIG_2_rx_comp_sel_b1_c_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_C_DIG_1_UNION
 结构说明  : tx_c_dig_1 寄存器结构定义。地址偏移量:0x402，初值:0x82，宽度:8
 寄存器说明: TX C模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_c  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                        0：不bypass(默认)
                                                        1：bypass */
        unsigned long  tx_hb_bp_c    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                        0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
                                                        1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认) */
        unsigned long  tx_rate_c     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                             2G,     3G,     4G,      TDS,      CDMA
                                                            (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                        0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                        1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                        2：-------,--------,15.36MHz,--------,--------
                                                        Others：Reserved */
        unsigned long  tx_mode_dig_c : 3;  /* bit[5-7]: TX通道模式控制：
                                                        000：2G(默认)
                                                        001：3G
                                                        010：4G
                                                        011：TDS
                                                        100：CDMA
                                                        Others：Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_1_UNION;
#define ABB_TX_C_DIG_1_tx_comp_bp_c_START   (0)
#define ABB_TX_C_DIG_1_tx_comp_bp_c_END     (0)
#define ABB_TX_C_DIG_1_tx_hb_bp_c_START     (1)
#define ABB_TX_C_DIG_1_tx_hb_bp_c_END       (1)
#define ABB_TX_C_DIG_1_tx_rate_c_START      (2)
#define ABB_TX_C_DIG_1_tx_rate_c_END        (4)
#define ABB_TX_C_DIG_1_tx_mode_dig_c_START  (5)
#define ABB_TX_C_DIG_1_tx_mode_dig_c_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_C_DIG_2_UNION
 结构说明  : tx_c_dig_2 寄存器结构定义。地址偏移量:0x403，初值:0x23，宽度:8
 寄存器说明: TX C模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_c       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_c       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_c     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                          0：0(默认)
                                                          1：2
                                                          2：4
                                                          3：6 */
        unsigned long  uddwa_dith_en_c : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                          0：不使能
                                                          1：使能 */
        unsigned long  dem_dwa_en_c    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                          0：使用CLA模式
                                                          1：使用DWA模式 (默认) */
        unsigned long  dem_lsb_bp_c    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                          0：DEM LSB 打开(默认)
                                                          1：DEM LSB bypass */
        unsigned long  dem_msb_bp_c    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                          0：DEM MSB打开(默认)
                                                          1：DEM MSB bypass */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_2_UNION;
#define ABB_TX_C_DIG_2_tx_q_pd_c_START        (0)
#define ABB_TX_C_DIG_2_tx_q_pd_c_END          (0)
#define ABB_TX_C_DIG_2_tx_i_pd_c_START        (1)
#define ABB_TX_C_DIG_2_tx_i_pd_c_END          (1)
#define ABB_TX_C_DIG_2_dem_const_c_START      (2)
#define ABB_TX_C_DIG_2_dem_const_c_END        (3)
#define ABB_TX_C_DIG_2_uddwa_dith_en_c_START  (4)
#define ABB_TX_C_DIG_2_uddwa_dith_en_c_END    (4)
#define ABB_TX_C_DIG_2_dem_dwa_en_c_START     (5)
#define ABB_TX_C_DIG_2_dem_dwa_en_c_END       (5)
#define ABB_TX_C_DIG_2_dem_lsb_bp_c_START     (6)
#define ABB_TX_C_DIG_2_dem_lsb_bp_c_END       (6)
#define ABB_TX_C_DIG_2_dem_msb_bp_c_START     (7)
#define ABB_TX_C_DIG_2_dem_msb_bp_c_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_C_DIG_3_UNION
 结构说明  : tx_c_dig_3 寄存器结构定义。地址偏移量:0x404，初值:0x09，宽度:8
 寄存器说明: TX C模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0    : 1;  /* bit[0]  : 保留 */
        unsigned long  tx_flush_en_c : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                        0：不使能
                                                        1：使能 */
        unsigned long  tx_comp_sel_c : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                        00：固定系数1；
                                                        01：固定系数2；
                                                        10：固定系数3；
                                                        11：可配系数。 */
        unsigned long  reserved_1    : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_3_UNION;
#define ABB_TX_C_DIG_3_tx_flush_en_c_START  (1)
#define ABB_TX_C_DIG_3_tx_flush_en_c_END    (1)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_START  (2)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_END    (3)


/*****************************************************************************
 结构名    : ABB_TX_COEF1_UNION
 结构说明  : tx_coef1 寄存器结构定义。地址偏移量:0x415，初值:0x3B，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_c0 : 6;  /* bit[0-5]: TX补偿滤波器系数C0,6bit有符号数 */
        unsigned long  reserved   : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_COEF1_UNION;
#define ABB_TX_COEF1_tx_comp_c0_START  (0)
#define ABB_TX_COEF1_tx_comp_c0_END    (5)


/*****************************************************************************
 结构名    : ABB_TX_COEF4_UNION
 结构说明  : tx_coef4 寄存器结构定义。地址偏移量:0x418，初值:0x03，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_c2_msb : 2;  /* bit[0-1]: TX补偿滤波器系数C2高2位,10bit有符号数 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_COEF4_UNION;
#define ABB_TX_COEF4_tx_comp_c2_msb_START  (0)
#define ABB_TX_COEF4_tx_comp_c2_msb_END    (1)


/*****************************************************************************
 结构名    : ABB_TX_COEF6_UNION
 结构说明  : tx_coef6 寄存器结构定义。地址偏移量:0x41A，初值:0x02，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_c3_msb : 2;  /* bit[0-1]: TX补偿滤波器系数C3高2位,10bit无符号数 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_COEF6_UNION;
#define ABB_TX_COEF6_tx_comp_c3_msb_START  (0)
#define ABB_TX_COEF6_tx_comp_c3_msb_END    (1)


/*****************************************************************************
 结构名    : ABB_BIST_DELAY_SEL_UNION
 结构说明  : bist_delay_sel 寄存器结构定义。地址偏移量:0x500，初值:0x00，宽度:8
 寄存器说明: delay长度选择信号
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_delay1_sel : 2;  /* bit[0-1]: Delay1的选择信号：
                                                          00：50us；
                                                          01：100us；
                                                          10：200us；
                                                          11：500us。 */
        unsigned long  reserved_0      : 2;  /* bit[2-3]: 保留 */
        unsigned long  bist_delay2_sel : 2;  /* bit[4-5]: Delay2的选择信号：
                                                          00：20us；
                                                          01：50us；
                                                          10：200us；
                                                          11：500us。 */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_DELAY_SEL_UNION;
#define ABB_BIST_DELAY_SEL_bist_delay1_sel_START  (0)
#define ABB_BIST_DELAY_SEL_bist_delay1_sel_END    (1)
#define ABB_BIST_DELAY_SEL_bist_delay2_sel_START  (4)
#define ABB_BIST_DELAY_SEL_bist_delay2_sel_END    (5)


/*****************************************************************************
 结构名    : ABB_BIST_MODE_BYPASS_UNION
 结构说明  : bist_mode_bypass 寄存器结构定义。地址偏移量:0x501，初值:0x00，宽度:8
 寄存器说明: 模式bypass信号
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_mode_bypass : 7;  /* bit[0-6]: 模式bypass信号，每种模式占一个bit
                                                           [0]：1表示G模的BIST被bypass；0表示G模的BIST正常工作。
                                                           [1]：1表示WCDMA模SC的BIST被bypass；0表示WCDMA模SC的BIST正常工作。
                                                           [2]：1表示WCDMA模DC的BIST被bypass；0表示WCDMA模DC的BIST正常工作。
                                                           [3]：1表示LTE模的BIST被bypass；0表示LTE模的BIST正常工作。
                                                           [4]：1表示ET模的BIST被bypass；0表示ET模的BIST正常工作。
                                                           [5]：1表示CA模的BIST被bypass；0表示CA模的BIST正常工作。
                                                           [6]：1表示CDMA模的BIST被bypass；0表示CDMA模的BIST正常工作。 */
        unsigned long  reserved         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_MODE_BYPASS_UNION;
#define ABB_BIST_MODE_BYPASS_bist_mode_bypass_START  (0)
#define ABB_BIST_MODE_BYPASS_bist_mode_bypass_END    (6)


/*****************************************************************************
 结构名    : ABB_BIST_RX_BYPASS_UNION
 结构说明  : bist_rx_bypass 寄存器结构定义。地址偏移量:0x502，初值:0x00，宽度:8
 寄存器说明: Rx的bypass信号
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_rx_bypass : 4;  /* bit[0-3]: Rx的bypass信号：
                                                         [0]：Rx_1的bypass信号，0表示需要做Rx_1的BIST；1表示不做。
                                                         [1]：Rx_2的bypass信号，0表示需要做Rx_2的BIST；1表示不做。
                                                         [2]：Rx_3的bypass信号，0表示需要做Rx_3的BIST；1表示不做。
                                                         [3]：Rx_4的bypass信号，0表示需要做Rx_4的BIST；1表示不做。 */
        unsigned long  reserved       : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RX_BYPASS_UNION;
#define ABB_BIST_RX_BYPASS_bist_rx_bypass_START  (0)
#define ABB_BIST_RX_BYPASS_bist_rx_bypass_END    (3)


/*****************************************************************************
 结构名    : ABB_ABB_BIST_EN_UNION
 结构说明  : abb_bist_en 寄存器结构定义。地址偏移量:0x503，初值:0x00，宽度:8
 寄存器说明: BIST工作使能信号
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_en      : 1;  /* bit[0]  : BIST工作使能信号，该信号为电平信号。 */
        unsigned long  bist_gate_bp : 1;  /* bit[1]  : BIST时钟门控使能信号，0表示时钟门控有效；1表示时钟门控旁路。 */
        unsigned long  reserved     : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_EN_UNION;
#define ABB_ABB_BIST_EN_bist_en_START       (0)
#define ABB_ABB_BIST_EN_bist_en_END         (0)
#define ABB_ABB_BIST_EN_bist_gate_bp_START  (1)
#define ABB_ABB_BIST_EN_bist_gate_bp_END    (1)


/*****************************************************************************
 结构名    : ABB_BIST_SNDR_CAL_DONE_UNION
 结构说明  : bist_sndr_cal_done 寄存器结构定义。地址偏移量:0x504，初值:0x00，宽度:8
 寄存器说明: 测试状态
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sndr_cal_done : 1;  /* bit[0]  : 1：测试结束 0：正在测试（en上升沿清0） */
        unsigned long  reserved      : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_SNDR_CAL_DONE_UNION;
#define ABB_BIST_SNDR_CAL_DONE_sndr_cal_done_START  (0)
#define ABB_BIST_SNDR_CAL_DONE_sndr_cal_done_END    (0)


/*****************************************************************************
 结构名    : ABB_BIST_PARA_PASS_FLAG_UNION
 结构说明  : bist_para_pass_flag 寄存器结构定义。地址偏移量:0x505，初值:0x00，宽度:8
 寄存器说明: 计算出的6个参数是否pass
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  para_pass_flag : 6;  /* bit[0-5]: 每一次计算出的6个参数是否pass：
                                                         [0]:1表示DC_I指标pass；0表示不pass；
                                                         [1]:1表示DC_Q指标pass；0表示不pass；
                                                         [2]:1表示SNDR_I指标pass；0表示不pass；
                                                         [3]:1表示SNDR_Q指标pass；0表示不pass；
                                                         [4]:1表示GAIN_MISMATCH指标pass；0表示不pass；
                                                         [5]:1表示GAIN_ERROR指标pass；0表示不pass； */
        unsigned long  reserved       : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_PARA_PASS_FLAG_UNION;
#define ABB_BIST_PARA_PASS_FLAG_para_pass_flag_START  (0)
#define ABB_BIST_PARA_PASS_FLAG_para_pass_flag_END    (5)


/*****************************************************************************
 结构名    : ABB_ABB_BIST_PASS_FLAG_1_UNION
 结构说明  : abb_bist_pass_flag_1 寄存器结构定义。地址偏移量:0x506，初值:0x00，宽度:8
 寄存器说明: Rx_1的Bist结算结果
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_1 : 7;  /* bit[0-6]: Rx_1的Bist结算结果，每种模式1bit：
                                                           [0]：1表示G模的BIST pass；0表示G模的BIST fail。
                                                           [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
                                                           [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
                                                           [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
                                                           [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
                                                           [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
                                                           [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。 */
        unsigned long  reserved         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_1_UNION;
#define ABB_ABB_BIST_PASS_FLAG_1_bist_pass_flag_1_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_1_bist_pass_flag_1_END    (6)


/*****************************************************************************
 结构名    : ABB_ABB_BIST_PASS_FLAG_2_UNION
 结构说明  : abb_bist_pass_flag_2 寄存器结构定义。地址偏移量:0x507，初值:0x00，宽度:8
 寄存器说明: Rx_2的Bist结算结果
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_2 : 7;  /* bit[0-6]: Rx_2的Bist结算结果，每种模式1bit：
                                                           [0]：1表示G模的BIST pass；0表示G模的BIST fail。
                                                           [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
                                                           [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
                                                           [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
                                                           [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
                                                           [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
                                                           [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。 */
        unsigned long  reserved         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_2_UNION;
#define ABB_ABB_BIST_PASS_FLAG_2_bist_pass_flag_2_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_2_bist_pass_flag_2_END    (6)


/*****************************************************************************
 结构名    : ABB_ABB_BIST_PASS_FLAG_3_UNION
 结构说明  : abb_bist_pass_flag_3 寄存器结构定义。地址偏移量:0x508，初值:0x00，宽度:8
 寄存器说明: Rx_3的Bist结算结果
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_3 : 7;  /* bit[0-6]: Rx_3的Bist结算结果，每种模式1bit：
                                                           [0]：1表示G模的BIST pass；0表示G模的BIST fail。
                                                           [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
                                                           [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
                                                           [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
                                                           [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
                                                           [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
                                                           [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。 */
        unsigned long  reserved         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_3_UNION;
#define ABB_ABB_BIST_PASS_FLAG_3_bist_pass_flag_3_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_3_bist_pass_flag_3_END    (6)


/*****************************************************************************
 结构名    : ABB_ABB_BIST_PASS_FLAG_4_UNION
 结构说明  : abb_bist_pass_flag_4 寄存器结构定义。地址偏移量:0x509，初值:0x00，宽度:8
 寄存器说明: Rx_4的Bist结算结果
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_4 : 7;  /* bit[0-6]: Rx_4的Bist结算结果，每种模式1bit：
                                                           [0]：1表示G模的BIST pass；0表示G模的BIST fail。
                                                           [1]：1表示WCDMA模SC的BIST pass；0表示WCDMA模SC的BIST fail。
                                                           [2]：1表示WCDMA模DC的BIST pass；0表示WCDMA模DC的BIST fail。
                                                           [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
                                                           [4]：1表示ET模的BIST pass；0表示ET模的BIST fail。
                                                           [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
                                                           [6]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。 */
        unsigned long  reserved         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_4_UNION;
#define ABB_ABB_BIST_PASS_FLAG_4_bist_pass_flag_4_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_4_bist_pass_flag_4_END    (6)


/*****************************************************************************
 结构名    : ABB_BIST_DC_I_2_UNION
 结构说明  : BIST_DC_I_2 寄存器结构定义。地址偏移量:0x50B，初值:0x00，宽度:8
 寄存器说明: I路DC上报高3位结果
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_i_high : 3;  /* bit[0-2]: I路DC上报高3位，I路DC上报为11bit有符号数。 */
        unsigned long  reserved  : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_DC_I_2_UNION;
#define ABB_BIST_DC_I_2_dc_i_high_START  (0)
#define ABB_BIST_DC_I_2_dc_i_high_END    (2)


/*****************************************************************************
 结构名    : ABB_BIST_DC_Q_2_UNION
 结构说明  : BIST_DC_Q_2 寄存器结构定义。地址偏移量:0x50D，初值:0x00，宽度:8
 寄存器说明: Q路DC上报高3位结果
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_q_high : 3;  /* bit[0-2]: I路DC上报高3位，I路DC上报为11bit有符号数。 */
        unsigned long  reserved  : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_DC_Q_2_UNION;
#define ABB_BIST_DC_Q_2_dc_q_high_START  (0)
#define ABB_BIST_DC_Q_2_dc_q_high_END    (2)


/*****************************************************************************
 结构名    : ABB_GPLL_GATE_EN_UNION
 结构说明  : GPLL_GATE_EN 寄存器结构定义。地址偏移量:0x602，初值:0x01，宽度:8
 寄存器说明: GPLL输出时钟门控功能使能
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll_gate_en : 1;  /* bit[0]  : GPLL时钟门控功能使能，
                                                       0：gpll时钟门控功能关闭；
                                                       1：gpll时钟门控功能打开。 */
        unsigned long  gpll_timeout : 1;  /* bit[1]  : GPLL稳定指示。0表示GPLL未稳定；1表示GPLL稳定。GPLL稳定后有时钟输出。 */
        unsigned long  ch1_gpll_sel : 1;  /* bit[2]  : G模工作PLL选择
                                                       0：选择GPLL；（单/双时钟方案默认选择GPLL）
                                                       1：选择SCPLL。 */
        unsigned long  ch0_gpll_sel : 1;  /* bit[3]  : G模工作PLL选择，
                                                       0：选择GPLL；（单时钟方案默认选择GPLL，双时钟方案默认选择SCPLL）
                                                       1：选择SCPLL。 */
        unsigned long  reserved     : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPLL_GATE_EN_UNION;
#define ABB_GPLL_GATE_EN_gpll_gate_en_START  (0)
#define ABB_GPLL_GATE_EN_gpll_gate_en_END    (0)
#define ABB_GPLL_GATE_EN_gpll_timeout_START  (1)
#define ABB_GPLL_GATE_EN_gpll_timeout_END    (1)
#define ABB_GPLL_GATE_EN_ch1_gpll_sel_START  (2)
#define ABB_GPLL_GATE_EN_ch1_gpll_sel_END    (2)
#define ABB_GPLL_GATE_EN_ch0_gpll_sel_START  (3)
#define ABB_GPLL_GATE_EN_ch0_gpll_sel_END    (3)


/*****************************************************************************
 结构名    : ABB_GPLL_GATE_TIME_UNION
 结构说明  : GPLL_GATE_TIME 寄存器结构定义。地址偏移量:0x603，初值:0x03，宽度:8
 寄存器说明: GPLL输出时钟门控时间配置
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll_gate_time_sel : 2;  /* bit[0-1]: GPLL时钟稳定等待时间配置，计数时钟为19.2M：
                                                             00：gpll开启5us后稳定；
                                                             01：gpll开启10us后稳定；
                                                             10：gpll开启15us后稳定；
                                                             11：gpll开启20us后稳定； */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_GPLL_GATE_TIME_UNION;
#define ABB_GPLL_GATE_TIME_gpll_gate_time_sel_START  (0)
#define ABB_GPLL_GATE_TIME_gpll_gate_time_sel_END    (1)


/*****************************************************************************
 结构名    : ABB_SCPLL_LOCK_CTRL_UNION
 结构说明  : SCPLL_LOCK_CTRL 寄存器结构定义。地址偏移量:0x604，初值:0x0A，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_en      : 1;  /* bit[0]  : SCPLL使能信号。用于通过CFG接口配置打开scpll。 */
        unsigned long  scpll_time    : 2;  /* bit[1-2]: SCPLL时钟稳定等待时间配置，计数时钟为19.2M：
                                                        00：SCPLL开启75us后时钟稳定；
                                                        01：SCPLL开启100us后时钟稳定；
                                                        10：SCPLL开启115us后时钟稳定；
                                                        11：SCPLL开启125us后时钟稳定； */
        unsigned long  scpll_gate_en : 1;  /* bit[3]  : SCPLL门控使能信号。 */
        unsigned long  scpll_timeout : 1;  /* bit[4]  : SCPLL稳定指示。0表示SCPLL未稳定；1表示SCPLL稳定。SCPLL稳定后有时钟输出。 */
        unsigned long  scpll_lock    : 1;  /* bit[5]  : SCPLL锁定指示。 */
        unsigned long  reserved      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_LOCK_CTRL_UNION;
#define ABB_SCPLL_LOCK_CTRL_scpll_en_START       (0)
#define ABB_SCPLL_LOCK_CTRL_scpll_en_END         (0)
#define ABB_SCPLL_LOCK_CTRL_scpll_time_START     (1)
#define ABB_SCPLL_LOCK_CTRL_scpll_time_END       (2)
#define ABB_SCPLL_LOCK_CTRL_scpll_gate_en_START  (3)
#define ABB_SCPLL_LOCK_CTRL_scpll_gate_en_END    (3)
#define ABB_SCPLL_LOCK_CTRL_scpll_timeout_START  (4)
#define ABB_SCPLL_LOCK_CTRL_scpll_timeout_END    (4)
#define ABB_SCPLL_LOCK_CTRL_scpll_lock_START     (5)
#define ABB_SCPLL_LOCK_CTRL_scpll_lock_END       (5)


/*****************************************************************************
 结构名    : ABB_SCPLL_FBDIV_H_UNION
 结构说明  : SCPLL_FBDIV_H 寄存器结构定义。地址偏移量:0x607，初值:0x00，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_fbdiv_h : 4;  /* bit[0-3]: PLL反馈分频因子fbdiv[11:0]的高4bit； */
        unsigned long  reserved      : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_FBDIV_H_UNION;
#define ABB_SCPLL_FBDIV_H_scpll_fbdiv_h_START  (0)
#define ABB_SCPLL_FBDIV_H_scpll_fbdiv_h_END    (3)


/*****************************************************************************
 结构名    : ABB_SCPLL_REFDIV_UNION
 结构说明  : SCPLL_REFDIV 寄存器结构定义。地址偏移量:0x608，初值:0x01，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_refdiv : 6;  /* bit[0-5]: PLL参考分频因子refdiv[5:0]，默认值为1。 */
        unsigned long  reserved     : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_REFDIV_UNION;
#define ABB_SCPLL_REFDIV_scpll_refdiv_START  (0)
#define ABB_SCPLL_REFDIV_scpll_refdiv_END    (5)


/*****************************************************************************
 结构名    : ABB_SCPLL_CFG_UPDATE_UNION
 结构说明  : SCPLL_CFG_UPDATE 寄存器结构定义。地址偏移量:0x60D，初值:0x00，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_cfg_update : 1;  /* bit[0]  : SCPLL参数配置更新指示。
                                                           scpll_en打开后，软件配置完scpll_postdiv，scpll_fbdiv，scpll_frac参数，再配置scpll_sfg_update，参数同时更新；scpll_en不打开时，配置参数立即更新，不需要配置scpll_sfg_update。 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_CFG_UPDATE_UNION;
#define ABB_SCPLL_CFG_UPDATE_scpll_cfg_update_START  (0)
#define ABB_SCPLL_CFG_UPDATE_scpll_cfg_update_END    (0)


/*****************************************************************************
 结构名    : ABB_BBP_SLEEP_EN_UNION
 结构说明  : BBP_SLEEP_EN 寄存器结构定义。地址偏移量:0x60E，初值:0x00，宽度:8
 寄存器说明: BBP的245D76M时钟门控寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wbbp_sleep_en       : 1;  /* bit[0]  : 给BBP的WPLL 245D76M时钟门控信号。0：不输出时钟，时钟输出低电平。1：输出时钟。默认值0（不输出时钟）。 */
        unsigned long  scbbp_245m_sleep_en : 1;  /* bit[1]  : 给BBP的SCPLL 245D76M时钟门控信号。0：不输出时钟，时钟输出低电平。1：输出时钟。默认值0（不输出时钟）。 */
        unsigned long  scbbp_104m_sleep_en : 1;  /* bit[2]  : 给BBP的SCPLL 104M时钟门控信号。0：不输出时钟，时钟输出低电平。1：输出时钟。默认值0（不输出时钟）。 */
        unsigned long  reserved            : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_BBP_SLEEP_EN_UNION;
#define ABB_BBP_SLEEP_EN_wbbp_sleep_en_START        (0)
#define ABB_BBP_SLEEP_EN_wbbp_sleep_en_END          (0)
#define ABB_BBP_SLEEP_EN_scbbp_245m_sleep_en_START  (1)
#define ABB_BBP_SLEEP_EN_scbbp_245m_sleep_en_END    (1)
#define ABB_BBP_SLEEP_EN_scbbp_104m_sleep_en_START  (2)
#define ABB_BBP_SLEEP_EN_scbbp_104m_sleep_en_END    (2)


/*****************************************************************************
 结构名    : ABB_WPLL_GATE_EN_UNION
 结构说明  : WPLL_GATE_EN 寄存器结构定义。地址偏移量:0x60F，初值:0x01，宽度:8
 寄存器说明: WPLL输出时钟门控功能使能
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_gate_en : 1;  /* bit[0]  : WPLL时钟门控功能使能，
                                                       0：wpll时钟门控功能关闭；
                                                       1：wpll时钟门控功能打开。 */
        unsigned long  wpll_timeout : 1;  /* bit[1]  : WPLL稳定指示。0表示WPLL未稳定；1表示WPLL稳定。WPLL稳定后有时钟输出。 */
        unsigned long  reserved     : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_WPLL_GATE_EN_UNION;
#define ABB_WPLL_GATE_EN_wpll_gate_en_START  (0)
#define ABB_WPLL_GATE_EN_wpll_gate_en_END    (0)
#define ABB_WPLL_GATE_EN_wpll_timeout_START  (1)
#define ABB_WPLL_GATE_EN_wpll_timeout_END    (1)


/*****************************************************************************
 结构名    : ABB_WPLL_GATE_TIME_UNION
 结构说明  : WPLL_GATE_TIME 寄存器结构定义。地址偏移量:0x610，初值:0x03，宽度:8
 寄存器说明: WPLL输出时钟门控时间配置
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_gate_time_sel : 2;  /* bit[0-1]: WPLL时钟稳定等待时间配置，计数时钟为19.2M：
                                                             00：wpll开启5us后稳定；
                                                             01：wpll开启10us后稳定；
                                                             10：wpll开启15us后稳定；
                                                             11：wpll开启20us后稳定； */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_WPLL_GATE_TIME_UNION;
#define ABB_WPLL_GATE_TIME_wpll_gate_time_sel_START  (0)
#define ABB_WPLL_GATE_TIME_wpll_gate_time_sel_END    (1)


/*****************************************************************************
 结构名    : ABB_PLL_FREF_SEL_UNION
 结构说明  : PLL_FREF_SEL 寄存器结构定义。地址偏移量:0x611，初值:0x00，宽度:8
 寄存器说明: WPLL输出时钟门控时间配置
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_fref_sel : 1;  /* bit[0]  : SC PLL FREF选择：
                                                         0：选ch0 TCXO；（单/双时钟方案默认选0）
                                                         1：选ch1 TCXO； */
        unsigned long  wpll_fref_sel  : 1;  /* bit[1]  : W PLL FREF选择：
                                                         0：选ch0 TCXO；（单/双时钟方案默认选0）
                                                         1：选ch1 TCXO； */
        unsigned long  gpll_fref_sel  : 1;  /* bit[2]  : G PLL FREF选择：
                                                         0：选ch0 TCXO；（单时钟方案默认选0，双时钟方案默认选1）
                                                         1：选ch1 TCXO； */
        unsigned long  reserved       : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_PLL_FREF_SEL_UNION;
#define ABB_PLL_FREF_SEL_scpll_fref_sel_START  (0)
#define ABB_PLL_FREF_SEL_scpll_fref_sel_END    (0)
#define ABB_PLL_FREF_SEL_wpll_fref_sel_START   (1)
#define ABB_PLL_FREF_SEL_wpll_fref_sel_END     (1)
#define ABB_PLL_FREF_SEL_gpll_fref_sel_START   (2)
#define ABB_PLL_FREF_SEL_gpll_fref_sel_END     (2)


/*****************************************************************************
 结构名    : ABB_SOC_PLL_SEL_UNION
 结构说明  : SOC_PLL_SEL 寄存器结构定义。地址偏移量:0x612，初值:0x00，宽度:8
 寄存器说明: SOC时钟选择信号
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  soc_pll_sel : 1;  /* bit[0]  : SOC PLL选择：
                                                      0：SOC时钟选SCPLL；（默认选SCPLL）
                                                      1：SOC时钟选WPLL； */
        unsigned long  reserved    : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SOC_PLL_SEL_UNION;
#define ABB_SOC_PLL_SEL_soc_pll_sel_START  (0)
#define ABB_SOC_PLL_SEL_soc_pll_sel_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_RXAI_HB_GAIN_2_UNION
 结构说明  : CH0_RXAI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x614，初值:0x02，宽度:8
 寄存器说明: CH0通道RXA HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxai_hb_gain_h : 2;  /* bit[0-1]: CH0通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXAI_HB_GAIN_2_UNION;
#define ABB_CH0_RXAI_HB_GAIN_2_ch0_rxai_hb_gain_h_START  (0)
#define ABB_CH0_RXAI_HB_GAIN_2_ch0_rxai_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXAQ_HB_GAIN_2_UNION
 结构说明  : CH0_RXAQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x616，初值:0x02，宽度:8
 寄存器说明: CH0通道RXA HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxaq_hb_gain_h : 2;  /* bit[0-1]: CH0通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXAQ_HB_GAIN_2_UNION;
#define ABB_CH0_RXAQ_HB_GAIN_2_ch0_rxaq_hb_gain_h_START  (0)
#define ABB_CH0_RXAQ_HB_GAIN_2_ch0_rxaq_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXBI_HB_GAIN_2_UNION
 结构说明  : CH0_RXBI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x618，初值:0x02，宽度:8
 寄存器说明: CH0通道RXB HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxbi_hb_gain_h : 2;  /* bit[0-1]: CH0通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXBI_HB_GAIN_2_UNION;
#define ABB_CH0_RXBI_HB_GAIN_2_ch0_rxbi_hb_gain_h_START  (0)
#define ABB_CH0_RXBI_HB_GAIN_2_ch0_rxbi_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXBQ_HB_GAIN_2_UNION
 结构说明  : CH0_RXBQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x61A，初值:0x02，宽度:8
 寄存器说明: CH0通道RXB HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxbq_hb_gain_h : 2;  /* bit[0-1]: CH0通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXBQ_HB_GAIN_2_UNION;
#define ABB_CH0_RXBQ_HB_GAIN_2_ch0_rxbq_hb_gain_h_START  (0)
#define ABB_CH0_RXBQ_HB_GAIN_2_ch0_rxbq_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_RXAI_HB_GAIN_2_UNION
 结构说明  : CH1_RXAI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x61C，初值:0x02，宽度:8
 寄存器说明: CH1通道RXA HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxai_hb_gain_h : 2;  /* bit[0-1]: CH1通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXAI_HB_GAIN_2_UNION;
#define ABB_CH1_RXAI_HB_GAIN_2_ch1_rxai_hb_gain_h_START  (0)
#define ABB_CH1_RXAI_HB_GAIN_2_ch1_rxai_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_RXAQ_HB_GAIN_2_UNION
 结构说明  : CH1_RXAQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x61E，初值:0x02，宽度:8
 寄存器说明: CH1通道RXA HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxaq_hb_gain_h : 2;  /* bit[0-1]: CH1通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXAQ_HB_GAIN_2_UNION;
#define ABB_CH1_RXAQ_HB_GAIN_2_ch1_rxaq_hb_gain_h_START  (0)
#define ABB_CH1_RXAQ_HB_GAIN_2_ch1_rxaq_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_RXBI_HB_GAIN_2_UNION
 结构说明  : CH1_RXBI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x620，初值:0x02，宽度:8
 寄存器说明: CH1通道RXB HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxbi_hb_gain_h : 2;  /* bit[0-1]: CH1通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXBI_HB_GAIN_2_UNION;
#define ABB_CH1_RXBI_HB_GAIN_2_ch1_rxbi_hb_gain_h_START  (0)
#define ABB_CH1_RXBI_HB_GAIN_2_ch1_rxbi_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_RXBQ_HB_GAIN_2_UNION
 结构说明  : CH1_RXBQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x622，初值:0x02，宽度:8
 寄存器说明: CH1通道RXB HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxbq_hb_gain_h : 2;  /* bit[0-1]: CH1通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXBQ_HB_GAIN_2_UNION;
#define ABB_CH1_RXBQ_HB_GAIN_2_ch1_rxbq_hb_gain_h_START  (0)
#define ABB_CH1_RXBQ_HB_GAIN_2_ch1_rxbq_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_EN_DELAY_UNION
 结构说明  : RX_EN_DELAY 寄存器结构定义。地址偏移量:0x623，初值:0x01，宽度:8
 寄存器说明: RX时钟门控延迟功能配置。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_en_dly_enable : 1;  /* bit[0]  : RX时钟门控延迟功能使能。该功能打开后，RX的随路工作钟比RX数据和VLD信号延迟关闭。 */
        unsigned long  rx_en_dly_cycle  : 2;  /* bit[1-2]: RX时钟门控延迟的19.2MHz时钟个数。
                                                               L/CA/X模   W/TDS模  G模
                                                           00：  1          2      32；  (默认)
                                                           01：  2          4      64；
                                                           10：  4          8      128。
                                                           11：  reserved  */
        unsigned long  reserved         : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_EN_DELAY_UNION;
#define ABB_RX_EN_DELAY_rx_en_dly_enable_START  (0)
#define ABB_RX_EN_DELAY_rx_en_dly_enable_END    (0)
#define ABB_RX_EN_DELAY_rx_en_dly_cycle_START   (1)
#define ABB_RX_EN_DELAY_rx_en_dly_cycle_END     (2)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_1_UNION
 结构说明  : TX_ET_DIG_1 寄存器结构定义。地址偏移量:0x700，初值:0x00，宽度:8
 寄存器说明: TX ET数字配置寄存器1。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_comp_bp    : 1;  /* bit[0]  : ET通道补偿滤波器bypass控制：
                                                        0：不bypass(默认)
                                                        1：bypass */
        unsigned long  et_hb_bp      : 1;  /* bit[1]  : ET通道半带滤波器的bypass信号
                                                        0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                        1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  et_sw_rst     : 1;  /* bit[2]  : ET通道软复位寄存器。
                                                        0：不复位；
                                                        1：复位。 */
        unsigned long  et_cal_sw_rst : 1;  /* bit[3]  : ET校准模块软复位寄存器。
                                                        0：不复位；
                                                        1：复位。 */
        unsigned long  reserved      : 2;  /* bit[4-5]: 保留 */
        unsigned long  et_ds_bp      : 1;  /* bit[6]  : ET通道降采样bypass信号
                                                        0：不bypass，2倍降采样（默认）；
                                                        1：bypass，不进行降采样。 */
        unsigned long  et_ch_sel     : 1;  /* bit[7]  : 选择CH0还是CH1支持ET。
                                                        0：CH0（默认）；
                                                        1：CH1。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_1_UNION;
#define ABB_TX_ET_DIG_1_et_comp_bp_START     (0)
#define ABB_TX_ET_DIG_1_et_comp_bp_END       (0)
#define ABB_TX_ET_DIG_1_et_hb_bp_START       (1)
#define ABB_TX_ET_DIG_1_et_hb_bp_END         (1)
#define ABB_TX_ET_DIG_1_et_sw_rst_START      (2)
#define ABB_TX_ET_DIG_1_et_sw_rst_END        (2)
#define ABB_TX_ET_DIG_1_et_cal_sw_rst_START  (3)
#define ABB_TX_ET_DIG_1_et_cal_sw_rst_END    (3)
#define ABB_TX_ET_DIG_1_et_ds_bp_START       (6)
#define ABB_TX_ET_DIG_1_et_ds_bp_END         (6)
#define ABB_TX_ET_DIG_1_et_ch_sel_START      (7)
#define ABB_TX_ET_DIG_1_et_ch_sel_END        (7)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_2_UNION
 结构说明  : TX_ET_DIG_2 寄存器结构定义。地址偏移量:0x701，初值:0x45，宽度:8
 寄存器说明: TX ET数字配置寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_gating_en  : 1;  /* bit[0]  : ET通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!et_gating_en)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  et_con        : 2;  /* bit[1-2]: TX通道DEM const系数：
                                                        0：0
                                                        1：2
                                                        2：4(默认)
                                                        3：6 */
        unsigned long  et_lsb_value  : 1;  /* bit[3]  : ET LSB最低bit输出值配置 */
        unsigned long  et_cal_dwa_en : 1;  /* bit[4]  : ET Calibration通道dem模式控制：
                                                        0：使用CLA模式(默认)
                                                        1：使用DWA模式  */
        unsigned long  et_tx_dwa_en  : 1;  /* bit[5]  : ET TX通道DEM模式控制：
                                                        0：使用CLA模式(默认)
                                                        1：使用DWA模式  */
        unsigned long  et_cal_dem_bp : 1;  /* bit[6]  : ET Calibration通道dem bypass：
                                                        0：DEM打开(默认)
                                                        1：DEM bypass */
        unsigned long  et_tx_dem_bp  : 1;  /* bit[7]  : ET TX通道dem bypass：
                                                        0：DEM打开(默认)
                                                        1：DEM bypass */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_2_UNION;
#define ABB_TX_ET_DIG_2_et_gating_en_START   (0)
#define ABB_TX_ET_DIG_2_et_gating_en_END     (0)
#define ABB_TX_ET_DIG_2_et_con_START         (1)
#define ABB_TX_ET_DIG_2_et_con_END           (2)
#define ABB_TX_ET_DIG_2_et_lsb_value_START   (3)
#define ABB_TX_ET_DIG_2_et_lsb_value_END     (3)
#define ABB_TX_ET_DIG_2_et_cal_dwa_en_START  (4)
#define ABB_TX_ET_DIG_2_et_cal_dwa_en_END    (4)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_START   (5)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_END     (5)
#define ABB_TX_ET_DIG_2_et_cal_dem_bp_START  (6)
#define ABB_TX_ET_DIG_2_et_cal_dem_bp_END    (6)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_START   (7)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_END     (7)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_3_UNION
 结构说明  : TX_ET_DIG_3 寄存器结构定义。地址偏移量:0x702，初值:0x00，宽度:8
 寄存器说明: TX ET数字配置寄存器3。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_cal_en   : 1;  /* bit[0]  : ET通道calibration使能。软件配置启动，calibration完成后，该bit自动清零。
                                                      0：不使能；
                                                      1：使能。 */
        unsigned long  et_flush_en : 1;  /* bit[1]  : ET通道FLUSH使能：
                                                      0：不使能
                                                      1：使能 */
        unsigned long  delay_cnt   : 2;  /* bit[2-3]: 进行电流比较时的延时控制。默认采用153.6MHz时钟进行延时。
                                                      00：30个时钟周期；
                                                      01：75个时钟周期；
                                                      10：150个时钟周期；
                                                      11：300个时钟周期。 */
        unsigned long  et_cal_type : 1;  /* bit[4]  : ET校准类型配置。ET DAC正常工作时，有两种方法对ET DAC输出进行校准。
                                                      0：打开Calibration DAC，通过Calibration DAC输出对ET DAC输出进行校准；
                                                      1：关闭Calibration DAC，将IREG寄存器结果加权到ET OUT输出进行校准。 */
        unsigned long  reserved_0  : 1;  /* bit[5]  : 保留 */
        unsigned long  et_crec_en  : 1;  /* bit[6]  : ET DAC正常工作时，是否使用calibration结果进行校准。
                                                      0：不使能；
                                                      1：使能。 */
        unsigned long  reserved_1  : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_3_UNION;
#define ABB_TX_ET_DIG_3_et_cal_en_START    (0)
#define ABB_TX_ET_DIG_3_et_cal_en_END      (0)
#define ABB_TX_ET_DIG_3_et_flush_en_START  (1)
#define ABB_TX_ET_DIG_3_et_flush_en_END    (1)
#define ABB_TX_ET_DIG_3_delay_cnt_START    (2)
#define ABB_TX_ET_DIG_3_delay_cnt_END      (3)
#define ABB_TX_ET_DIG_3_et_cal_type_START  (4)
#define ABB_TX_ET_DIG_3_et_cal_type_END    (4)
#define ABB_TX_ET_DIG_3_et_crec_en_START   (6)
#define ABB_TX_ET_DIG_3_et_crec_en_END     (6)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_4_UNION
 结构说明  : TX_ET_DIG_4 寄存器结构定义。地址偏移量:0x703，初值:0x00，宽度:8
 寄存器说明: TX ET数字配置寄存器4。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_tx_en_cfg : 1;  /* bit[0]: ET线控强制配置值。 */
        unsigned long  et_tx_en_sel : 1;  /* bit[1]: ET线控强制配置使能。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned long  et_apt_cfg   : 1;  /* bit[2]: ET模式强制配置值。 */
        unsigned long  et_apt_sel   : 1;  /* bit[3]: ET模式强制配置使能。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned long  et_div_bp    : 1;  /* bit[4]: ET分频器使能bypass控制
                                                     0：不bypass
                                                     1：bypass */
        unsigned long  et_dig_loop  : 1;  /* bit[5]: ET通道接口环回模式使能。该模式使能，将ET TX数据通过RX通道环回。通过et_ch_sel选择环回到ch0通道或者ch1通道。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned long  et_alg_loop  : 1;  /* bit[6]: ET通道算法环回模式使能。该模式使能，将RX通道数据环回到。通过et_ch_sel选择环回到ch0通道或者ch1通道。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned long  reserved     : 1;  /* bit[7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_4_UNION;
#define ABB_TX_ET_DIG_4_et_tx_en_cfg_START  (0)
#define ABB_TX_ET_DIG_4_et_tx_en_cfg_END    (0)
#define ABB_TX_ET_DIG_4_et_tx_en_sel_START  (1)
#define ABB_TX_ET_DIG_4_et_tx_en_sel_END    (1)
#define ABB_TX_ET_DIG_4_et_apt_cfg_START    (2)
#define ABB_TX_ET_DIG_4_et_apt_cfg_END      (2)
#define ABB_TX_ET_DIG_4_et_apt_sel_START    (3)
#define ABB_TX_ET_DIG_4_et_apt_sel_END      (3)
#define ABB_TX_ET_DIG_4_et_div_bp_START     (4)
#define ABB_TX_ET_DIG_4_et_div_bp_END       (4)
#define ABB_TX_ET_DIG_4_et_dig_loop_START   (5)
#define ABB_TX_ET_DIG_4_et_dig_loop_END     (5)
#define ABB_TX_ET_DIG_4_et_alg_loop_START   (6)
#define ABB_TX_ET_DIG_4_et_alg_loop_END     (6)


/*****************************************************************************
 结构名    : ABB_ET_STATE_RPT_UNION
 结构说明  : ET_STATE_RPT 寄存器结构定义。地址偏移量:0x705，初值:0x00，宽度:8
 寄存器说明: ET通道状态上报寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_comp_overflow : 1;  /* bit[0]  : ET补偿滤波器溢出指示。 */
        unsigned long  et_cic6_overflow : 1;  /* bit[1]  : ET CIC6滤波器溢出指示。 */
        unsigned long  et_hb_overflow   : 1;  /* bit[2]  : ET HB滤波器溢出指示。 */
        unsigned long  reserved         : 4;  /* bit[3-6]: 保留 */
        unsigned long  et_cal_done      : 1;  /* bit[7]  : ET通道校准完成。 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ET_STATE_RPT_UNION;
#define ABB_ET_STATE_RPT_et_comp_overflow_START  (0)
#define ABB_ET_STATE_RPT_et_comp_overflow_END    (0)
#define ABB_ET_STATE_RPT_et_cic6_overflow_START  (1)
#define ABB_ET_STATE_RPT_et_cic6_overflow_END    (1)
#define ABB_ET_STATE_RPT_et_hb_overflow_START    (2)
#define ABB_ET_STATE_RPT_et_hb_overflow_END      (2)
#define ABB_ET_STATE_RPT_et_cal_done_START       (7)
#define ABB_ET_STATE_RPT_et_cal_done_END         (7)


/*****************************************************************************
 结构名    : ABB_ET_ITEMP_REG_MSB_UNION
 结构说明  : ET_ITEMP_REG_MSB 寄存器结构定义。地址偏移量:0x706，初值:0x00，宽度:8
 寄存器说明: ET通道ITEMP校准结果寄存器高位。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_itemp_reg_msb : 2;  /* bit[0-1]: ITEMP校准结果高位。 */
        unsigned long  reserved         : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ITEMP_REG_MSB_UNION;
#define ABB_ET_ITEMP_REG_MSB_et_itemp_reg_msb_START  (0)
#define ABB_ET_ITEMP_REG_MSB_et_itemp_reg_msb_END    (1)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT1_UNION
 结构说明  : ET_ICELL_SORT1 寄存器结构定义。地址偏移量:0x727，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器1。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort1 : 5;  /* bit[0-4]: ICELL排序结果寄存器1。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT1_UNION;
#define ABB_ET_ICELL_SORT1_et_icell_sort1_START  (0)
#define ABB_ET_ICELL_SORT1_et_icell_sort1_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT2_UNION
 结构说明  : ET_ICELL_SORT2 寄存器结构定义。地址偏移量:0x728，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort2 : 5;  /* bit[0-4]: ICELL排序结果寄存器2。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT2_UNION;
#define ABB_ET_ICELL_SORT2_et_icell_sort2_START  (0)
#define ABB_ET_ICELL_SORT2_et_icell_sort2_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT3_UNION
 结构说明  : ET_ICELL_SORT3 寄存器结构定义。地址偏移量:0x729，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器3。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort3 : 5;  /* bit[0-4]: ICELL排序结果寄存器3。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT3_UNION;
#define ABB_ET_ICELL_SORT3_et_icell_sort3_START  (0)
#define ABB_ET_ICELL_SORT3_et_icell_sort3_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT4_UNION
 结构说明  : ET_ICELL_SORT4 寄存器结构定义。地址偏移量:0x72A，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器4。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort4 : 5;  /* bit[0-4]: ICELL排序结果寄存器4。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT4_UNION;
#define ABB_ET_ICELL_SORT4_et_icell_sort4_START  (0)
#define ABB_ET_ICELL_SORT4_et_icell_sort4_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT5_UNION
 结构说明  : ET_ICELL_SORT5 寄存器结构定义。地址偏移量:0x72B，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器5。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort5 : 5;  /* bit[0-4]: ICELL排序结果寄存器5。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT5_UNION;
#define ABB_ET_ICELL_SORT5_et_icell_sort5_START  (0)
#define ABB_ET_ICELL_SORT5_et_icell_sort5_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT6_UNION
 结构说明  : ET_ICELL_SORT6 寄存器结构定义。地址偏移量:0x72C，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器6。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort6 : 5;  /* bit[0-4]: ICELL排序结果寄存器6。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT6_UNION;
#define ABB_ET_ICELL_SORT6_et_icell_sort6_START  (0)
#define ABB_ET_ICELL_SORT6_et_icell_sort6_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT7_UNION
 结构说明  : ET_ICELL_SORT7 寄存器结构定义。地址偏移量:0x72D，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器7。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort7 : 5;  /* bit[0-4]: ICELL排序结果寄存器7。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT7_UNION;
#define ABB_ET_ICELL_SORT7_et_icell_sort7_START  (0)
#define ABB_ET_ICELL_SORT7_et_icell_sort7_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT8_UNION
 结构说明  : ET_ICELL_SORT8 寄存器结构定义。地址偏移量:0x72E，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器8。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort8 : 5;  /* bit[0-4]: ICELL排序结果寄存器8。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT8_UNION;
#define ABB_ET_ICELL_SORT8_et_icell_sort8_START  (0)
#define ABB_ET_ICELL_SORT8_et_icell_sort8_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT9_UNION
 结构说明  : ET_ICELL_SORT9 寄存器结构定义。地址偏移量:0x72F，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器9。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort9 : 5;  /* bit[0-4]: ICELL排序结果寄存器9。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT9_UNION;
#define ABB_ET_ICELL_SORT9_et_icell_sort9_START  (0)
#define ABB_ET_ICELL_SORT9_et_icell_sort9_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT10_UNION
 结构说明  : ET_ICELL_SORT10 寄存器结构定义。地址偏移量:0x730，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器10。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort10 : 5;  /* bit[0-4]: ICELL排序结果寄存器10。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT10_UNION;
#define ABB_ET_ICELL_SORT10_et_icell_sort10_START  (0)
#define ABB_ET_ICELL_SORT10_et_icell_sort10_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT11_UNION
 结构说明  : ET_ICELL_SORT11 寄存器结构定义。地址偏移量:0x731，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器11。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort11 : 5;  /* bit[0-4]: ICELL排序结果寄存器11。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT11_UNION;
#define ABB_ET_ICELL_SORT11_et_icell_sort11_START  (0)
#define ABB_ET_ICELL_SORT11_et_icell_sort11_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT12_UNION
 结构说明  : ET_ICELL_SORT12 寄存器结构定义。地址偏移量:0x732，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器12。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort12 : 5;  /* bit[0-4]: ICELL排序结果寄存器12。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT12_UNION;
#define ABB_ET_ICELL_SORT12_et_icell_sort12_START  (0)
#define ABB_ET_ICELL_SORT12_et_icell_sort12_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT13_UNION
 结构说明  : ET_ICELL_SORT13 寄存器结构定义。地址偏移量:0x733，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器13。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort13 : 5;  /* bit[0-4]: ICELL排序结果寄存器13。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT13_UNION;
#define ABB_ET_ICELL_SORT13_et_icell_sort13_START  (0)
#define ABB_ET_ICELL_SORT13_et_icell_sort13_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT14_UNION
 结构说明  : ET_ICELL_SORT14 寄存器结构定义。地址偏移量:0x734，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器14。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort14 : 5;  /* bit[0-4]: ICELL排序结果寄存器14。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT14_UNION;
#define ABB_ET_ICELL_SORT14_et_icell_sort14_START  (0)
#define ABB_ET_ICELL_SORT14_et_icell_sort14_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT15_UNION
 结构说明  : ET_ICELL_SORT15 寄存器结构定义。地址偏移量:0x735，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器15。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort15 : 5;  /* bit[0-4]: ICELL排序结果寄存器15。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT15_UNION;
#define ABB_ET_ICELL_SORT15_et_icell_sort15_START  (0)
#define ABB_ET_ICELL_SORT15_et_icell_sort15_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT16_UNION
 结构说明  : ET_ICELL_SORT16 寄存器结构定义。地址偏移量:0x736，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器16。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort16 : 5;  /* bit[0-4]: ICELL排序结果寄存器16。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT16_UNION;
#define ABB_ET_ICELL_SORT16_et_icell_sort16_START  (0)
#define ABB_ET_ICELL_SORT16_et_icell_sort16_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT17_UNION
 结构说明  : ET_ICELL_SORT17 寄存器结构定义。地址偏移量:0x737，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器17。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort17 : 5;  /* bit[0-4]: ICELL排序结果寄存器17。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT17_UNION;
#define ABB_ET_ICELL_SORT17_et_icell_sort17_START  (0)
#define ABB_ET_ICELL_SORT17_et_icell_sort17_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT18_UNION
 结构说明  : ET_ICELL_SORT18 寄存器结构定义。地址偏移量:0x738，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器18。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort18 : 5;  /* bit[0-4]: ICELL排序结果寄存器18。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT18_UNION;
#define ABB_ET_ICELL_SORT18_et_icell_sort18_START  (0)
#define ABB_ET_ICELL_SORT18_et_icell_sort18_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT19_UNION
 结构说明  : ET_ICELL_SORT19 寄存器结构定义。地址偏移量:0x739，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器19。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort19 : 5;  /* bit[0-4]: ICELL排序结果寄存器19。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT19_UNION;
#define ABB_ET_ICELL_SORT19_et_icell_sort19_START  (0)
#define ABB_ET_ICELL_SORT19_et_icell_sort19_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT20_UNION
 结构说明  : ET_ICELL_SORT20 寄存器结构定义。地址偏移量:0x73A，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器20。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort20 : 5;  /* bit[0-4]: ICELL排序结果寄存器20。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT20_UNION;
#define ABB_ET_ICELL_SORT20_et_icell_sort20_START  (0)
#define ABB_ET_ICELL_SORT20_et_icell_sort20_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT21_UNION
 结构说明  : ET_ICELL_SORT21 寄存器结构定义。地址偏移量:0x73B，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器21。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort21 : 5;  /* bit[0-4]: ICELL排序结果寄存器21。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT21_UNION;
#define ABB_ET_ICELL_SORT21_et_icell_sort21_START  (0)
#define ABB_ET_ICELL_SORT21_et_icell_sort21_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT22_UNION
 结构说明  : ET_ICELL_SORT22 寄存器结构定义。地址偏移量:0x73C，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器22。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort22 : 5;  /* bit[0-4]: ICELL排序结果寄存器22。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT22_UNION;
#define ABB_ET_ICELL_SORT22_et_icell_sort22_START  (0)
#define ABB_ET_ICELL_SORT22_et_icell_sort22_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT23_UNION
 结构说明  : ET_ICELL_SORT23 寄存器结构定义。地址偏移量:0x73D，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器23。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort23 : 5;  /* bit[0-4]: ICELL排序结果寄存器23。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT23_UNION;
#define ABB_ET_ICELL_SORT23_et_icell_sort23_START  (0)
#define ABB_ET_ICELL_SORT23_et_icell_sort23_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT24_UNION
 结构说明  : ET_ICELL_SORT24 寄存器结构定义。地址偏移量:0x73E，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器24。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort24 : 5;  /* bit[0-4]: ICELL排序结果寄存器24。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT24_UNION;
#define ABB_ET_ICELL_SORT24_et_icell_sort24_START  (0)
#define ABB_ET_ICELL_SORT24_et_icell_sort24_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT25_UNION
 结构说明  : ET_ICELL_SORT25 寄存器结构定义。地址偏移量:0x73F，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器25。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort25 : 5;  /* bit[0-4]: ICELL排序结果寄存器25。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT25_UNION;
#define ABB_ET_ICELL_SORT25_et_icell_sort25_START  (0)
#define ABB_ET_ICELL_SORT25_et_icell_sort25_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT26_UNION
 结构说明  : ET_ICELL_SORT26 寄存器结构定义。地址偏移量:0x740，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器26。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort26 : 5;  /* bit[0-4]: ICELL排序结果寄存器26。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT26_UNION;
#define ABB_ET_ICELL_SORT26_et_icell_sort26_START  (0)
#define ABB_ET_ICELL_SORT26_et_icell_sort26_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT27_UNION
 结构说明  : ET_ICELL_SORT27 寄存器结构定义。地址偏移量:0x741，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器27。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort27 : 5;  /* bit[0-4]: ICELL排序结果寄存器27。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT27_UNION;
#define ABB_ET_ICELL_SORT27_et_icell_sort27_START  (0)
#define ABB_ET_ICELL_SORT27_et_icell_sort27_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT28_UNION
 结构说明  : ET_ICELL_SORT28 寄存器结构定义。地址偏移量:0x742，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器28。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort28 : 5;  /* bit[0-4]: ICELL排序结果寄存器28。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT28_UNION;
#define ABB_ET_ICELL_SORT28_et_icell_sort28_START  (0)
#define ABB_ET_ICELL_SORT28_et_icell_sort28_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT29_UNION
 结构说明  : ET_ICELL_SORT29 寄存器结构定义。地址偏移量:0x743，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器29。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort29 : 5;  /* bit[0-4]: ICELL排序结果寄存器29。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT29_UNION;
#define ABB_ET_ICELL_SORT29_et_icell_sort29_START  (0)
#define ABB_ET_ICELL_SORT29_et_icell_sort29_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT30_UNION
 结构说明  : ET_ICELL_SORT30 寄存器结构定义。地址偏移量:0x744，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器30。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort30 : 5;  /* bit[0-4]: ICELL排序结果寄存器30。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT30_UNION;
#define ABB_ET_ICELL_SORT30_et_icell_sort30_START  (0)
#define ABB_ET_ICELL_SORT30_et_icell_sort30_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_SORT31_UNION
 结构说明  : ET_ICELL_SORT31 寄存器结构定义。地址偏移量:0x745，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL排序结果结存器31。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort31 : 5;  /* bit[0-4]: ICELL排序结果寄存器31。 */
        unsigned long  reserved        : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT31_UNION;
#define ABB_ET_ICELL_SORT31_et_icell_sort31_START  (0)
#define ABB_ET_ICELL_SORT31_et_icell_sort31_END    (4)


/*****************************************************************************
 结构名    : ABB_ET_ICELL_UPDATE_UNION
 结构说明  : ET_ICELL_UPDATE 寄存器结构定义。地址偏移量:0x746，初值:0x00，宽度:8
 寄存器说明: ET通道ICELL寄存器更新
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_update : 1;  /* bit[0]  : 配置该寄存器，更新寄存器ET_ICELL_REG1~ET_ICELL_SORT31。寄存器更新完成之后，需要配置为0。 */
        unsigned long  reserved        : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_UPDATE_UNION;
#define ABB_ET_ICELL_UPDATE_et_icell_update_START  (0)
#define ABB_ET_ICELL_UPDATE_et_icell_update_END    (0)


/*****************************************************************************
 结构名    : ABB_ET_SINE_GENERATE_UNION
 结构说明  : ET_SINE_GENERATE 寄存器结构定义。地址偏移量:0x74B，初值:0x10，宽度:8
 寄存器说明: SINE发送寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_sine_enable : 1;  /* bit[0]  : et通道正弦波发送使能。该位使能，则ET通道发送正弦波信号，且通过sine_sw_req选择CH0或者CH1发送正弦波信号。
                                                         0：不发送
                                                         1：发送 */
        unsigned long  reserved       : 1;  /* bit[1]  : 保留 */
        unsigned long  et_sine_amp    : 2;  /* bit[2-3]: 正弦波发送幅度控制
                                                         00：满量程
                                                         01：3/4量程
                                                         10：1/2量程
                                                         11：1/4量程 */
        unsigned long  et_sine_freq   : 4;  /* bit[4-7]: 正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_SINE_GENERATE_UNION;
#define ABB_ET_SINE_GENERATE_et_sine_enable_START  (0)
#define ABB_ET_SINE_GENERATE_et_sine_enable_END    (0)
#define ABB_ET_SINE_GENERATE_et_sine_amp_START     (2)
#define ABB_ET_SINE_GENERATE_et_sine_amp_END       (3)
#define ABB_ET_SINE_GENERATE_et_sine_freq_START    (4)
#define ABB_ET_SINE_GENERATE_et_sine_freq_END      (7)

/*****************************************************************************
 结构名    : ABB_CH0_LINE_RPT1_UNION
 结构说明  : CH0_LINE_RPT1 寄存器结构定义。地址偏移量:0x254，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: 线控信号LINE_CTRL_MODE状态上报
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  ch0_reserved_1            : 1;  /* bit[3]  : Reserved */
        unsigned long  ch0_rxa_blk_en_rpt        : 1;  /* bit[4]  : RXA_BLK_EN线控状态上报 */
        unsigned long  ch0_rxb_blk_en_rpt        : 1;  /* bit[5]  : RXB_BLK_EN线控状态上报 */
        unsigned long  ch0_reserved_0            : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT1_UNION;

/*****************************************************************************
 结构名    : ABB_CH1_LINE_RPT1_UNION
 结构说明  : CH1_LINE_RPT1 寄存器结构定义。地址偏移量:0x454，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: 线控信号LINE_CTRL_MODE状态上报
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  ch1_reserved_1            : 1;  /* bit[3]  : Reserved */
        unsigned long  ch1_rxa_blk_en_rpt        : 1;  /* bit[4]  : RXA_BLK_EN线控状态上报 */
        unsigned long  ch1_rxb_blk_en_rpt        : 1;  /* bit[5]  : RXB_BLK_EN线控状态上报 */
        unsigned long  ch1_reserved_0            : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT1_UNION;

/*****************************************************************************
 结构名    : ABB_CH0_RX_3G_DIG_1_UNION
 结构说明  : CH0_RX_3G_DIG_1 寄存器结构定义。地址偏移量:0x206，初值:0x2C，宽度:8
 寄存器说明: RX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_3g : 3;  /* bit[0-2]: RX通道补偿滤波器补偿系数固定控制：
                                                             000：系数不固定，由寄存器配置；
                                                             001：固定系数1；
                                                             010：固定系数2；
                                                             011：固定系数3；
                                                             100：固定系数4；
                                                             101：固定系数5；
                                                             110：固定系数6；
                                                             111：固定系数7。 */
        unsigned long  ch0_rx_hb_bp_3g    : 1;  /* bit[3]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch0_rx_rate_3g     : 1;  /* bit[4]  : RX通道CIC滤波器输出速率控制(MHz)：
                                                                   2G,   3G_SC&amp;4G_5M, 4G_20M, 3G_DC&amp;TDS&amp;4G_10M,   CA,   CDMA
                                                             0： 2.167,     15.36,    61.44,      30.72,       122.88, 4.9152
                                                             others：reserved */
        unsigned long  ch0_rx_mode_dig_3g : 3;  /* bit[5-7]: RX通道模式控制：
                                                             000：2G
                                                             001：3G_SC&amp;4G_5M(默认)
                                                             010：4G_20M
                                                             011：3G_DC&amp;4G_10M
                                                             100：TDS
                                                             101：CA
                                                             Others：CDMA */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_1_UNION;

/*****************************************************************************
 结构名    : ABB_CH1_RX_3G_DIG_1_UNION
 结构说明  : CH1_RX_3G_DIG_1 寄存器结构定义。地址偏移量:0x406，初值:0x2C，宽度:8
 寄存器说明: RX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_comp_sel_3g : 3;  /* bit[0-2]: RX通道补偿滤波器补偿系数固定控制：
                                                             000：系数不固定，由寄存器配置；
                                                             001：固定系数1；
                                                             010：固定系数2；
                                                             011：固定系数3；
                                                             100：固定系数4；
                                                             101：固定系数5；
                                                             110：固定系数6；
                                                             111：固定系数7。 */
        unsigned long  ch1_rx_hb_bp_3g    : 1;  /* bit[3]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch1_rx_rate_3g     : 1;  /* bit[4]  : RX通道CIC滤波器输出速率控制(MHz)：
                                                                   2G,   3G_SC&amp;4G_5M, 4G_20M, 3G_DC&amp;TDS&amp;4G_10M,   CA,   CDMA
                                                             0： 2.167,     15.36,    61.44,      30.72,       122.88, 4.9152
                                                             others：reserved */
        unsigned long  ch1_rx_mode_dig_3g : 3;  /* bit[5-7]: RX通道模式控制：
                                                             000：2G
                                                             001：3G_SC&amp;4G_5M(默认)
                                                             010：4G_20M
                                                             011：3G_DC&amp;4G_10M
                                                             100：TDS
                                                             101：CA
                                                             Others：CDMA */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_1_UNION;

/*****************************************************************************
 结构名    : ABB_CH0_LINE_RPT0_UNION
 结构说明  : CH0_LINE_RPT0 寄存器结构定义。地址偏移量:0x253，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_rpt            : 1;  /* bit[0]  : RXA_EN线控状态上报 */
        unsigned long  ch0_rxb_en_rpt            : 1;  /* bit[1]  : RXB_EN线控状态上报 */
        unsigned long  ch0_tx_en_rpt             : 1;  /* bit[2]  : TX_EN线控状态上报 */
        unsigned long  ch0_tx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: 线控信号LINE_CTRL_MODE状态上报
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  ch0_reserved              : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT0_UNION;

/*****************************************************************************
 结构名    : ABB_CH1_LINE_RPT0_UNION
 结构说明  : CH1_LINE_RPT0 寄存器结构定义。地址偏移量:0x453，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_rpt            : 1;  /* bit[0]  : RXA_EN线控状态上报 */
        unsigned long  ch1_rxb_en_rpt            : 1;  /* bit[1]  : RXB_EN线控状态上报 */
        unsigned long  ch1_tx_en_rpt             : 1;  /* bit[2]  : TX_EN线控状态上报 */
        unsigned long  ch1_tx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: 线控信号LINE_CTRL_MODE状态上报
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  ch1_reserved              : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT0_UNION;

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

#endif /* end of phy_abb_interface.h */

