/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phy_abb_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-01-06 10:27:36
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月6日
    作    者   : w00209060
    修改内容   : 从《COMSTARTV100 ABB寄存器描述V1.2(nManager3.1)_11bit.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PHY_ABB_INTERFACE_H__
#define __PHY_ABB_INTERFACE_H__

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
             001：3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      TX通道CFR bypass控制：
             0：不bypass
             1：bypass(默认)
   UNION结构:  ABB_TX_2G_DIG_3_UNION */
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x4)

/* 寄存器说明：CH0 RX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      TX通道CFR bypass控制：
             0：不bypass
             1：bypass(默认)
   UNION结构:  ABB_TX_CH0_3G_DIG_3_UNION */
#define ABB_TX_CH0_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x9)

/* 寄存器说明：CH0 RX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      TX通道CFR bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_CH0_4G_DIG_3_UNION */
#define ABB_TX_CH0_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0xE)

/* 寄存器说明：RX TDS模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SCReserved
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
 bit[7:2]    Reserved
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      TX通道CFR bypass控制：
             0：不bypass
             1：bypass(默认)
   UNION结构:  ABB_TX_TDS_DIG_3_UNION */
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x13)

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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      TX通道CFR bypass控制：
             0：不bypass
             1：bypass(默认)
   UNION结构:  ABB_TX_IDLE_DIG_3_UNION */
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x23)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
             000：4G
             001：3G
             010：3G_DC &amp; TDS
             011：2G(默认)
             100：reserved
             101：CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
   UNION结构:  ABB_RX_2G_ANA_1_UNION */
#define ABB_RX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x24)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
 bit[7:6]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1： CA mode
             0： others
   UNION结构:  ABB_RX_2G_ANA_2_UNION */
#define ABB_RX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x25)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00：5MHz(默认)WSC&amp;GSM&amp;CDMA
             01：10MHz WDC
             10：Reserved
             11：20MHz LTE
 bit[5:4]    TX Mode 时钟控制：
             00：1分频
             01：2分频(默认)
             10：3分频
             11：4分频

 bit[3]      TX_I DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
             000：4G
             001：3G &amp; TDS
             010：reserved
             011：2G(默认)
             1xx：CDMA
   UNION结构:  ABB_TX_2G_ANA_1_UNION */
#define ABB_TX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x26)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr49。
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
 bit[6]      TBD
 bit[5:4]    LPF 运放偏置电流调整
             运放电流：   op1   op2
             00：         10u   10u
             01：         5u    5u
             10：         2.5u  5u
             11：         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 电流模式调整
             00 输出级电流正常
             01 输出级电流加大（适用于5uA偏置）
             10 不建议使用
             11 输出级电流再加大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 电流模式调整
             bit0：
             0： 输出级电流正常
             1： 输出级电流加大（适用于5uA偏置）
             bit1：
             0： miller补偿电容正常
             1： miller补偿电容变大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION结构:  ABB_TX_2G_ANA_2_UNION */
#define ABB_TX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x27)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
             000：4G
             001：3G
             010：3G_DC &amp; TDS
             011：2G(默认)
             100：reserved
             101：CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
   UNION结构:  ABB_RX_CH0_3G_ANA_1_UNION */
#define ABB_RX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x28)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
 bit[7:6]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1： CA mode
             0： others
   UNION结构:  ABB_RX_CH0_3G_ANA_2_UNION */
#define ABB_RX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x29)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00：5MHz(默认)WSC&amp;GSM&amp;CDMA
             01：10MHz WDC
             10：Reserved
             11：20MHz LTE
 bit[5:4]    TX Mode 时钟控制：
             00：1分频
             01：2分频(默认)
             10：3分频
             11：4分频

 bit[3]      TX_I DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
             000：4G &amp; ET &amp; APT
             001：3G &amp; TDS
   UNION结构:  ABB_TX_CH0_3G_ANA_1_UNION */
#define ABB_TX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2A)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr49。
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
 bit[6]      TBD
 bit[5:4]    LPF 运放偏置电流调整
             运放电流：   op1   op2
             00：         10u   10u
             01：         5u    5u
             10：         2.5u  5u
             11：         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 电流模式调整
             00 输出级电流正常
             01 输出级电流加大（适用于5uA偏置）
             10 不建议使用
             11 输出级电流再加大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 电流模式调整
             bit0：
             0： 输出级电流正常
             1： 输出级电流加大（适用于5uA偏置）
             bit1：
             0： miller补偿电容正常
             1： miller补偿电容变大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION结构:  ABB_TX_CH0_3G_ANA_2_UNION */
#define ABB_TX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2B)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
             000：4G
             001：3G
             010：3G_DC &amp; TDS
             011：2G(默认)
             100：reserved
             101：CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
   UNION结构:  ABB_RX_CH0_4G_ANA_1_UNION */
#define ABB_RX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2C)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
 bit[7:6]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1： CA mode
             0： others
   UNION结构:  ABB_RX_CH0_4G_ANA_2_UNION */
#define ABB_RX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2D)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00：5MHz(默认)WSC&amp;GSM&amp;CDMA
             01：10MHz WDC
             10：Reserved
             11：20MHz LTE
 bit[5:4]    TX Mode 时钟控制：
             00：1分频
             01：2分频(默认)
             10：3分频
             11：4分频

 bit[3]      TX_I DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
             000：4G &amp; ET &amp; APT
             001：3G &amp; TDS
             010：CA
             011：2G(默认)
             1xx：CDMA
   UNION结构:  ABB_TX_CH0_4G_ANA_1_UNION */
#define ABB_TX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2E)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr49。
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
 bit[6]      TBD
 bit[5:4]    LPF 运放偏置电流调整
             运放电流：   op1   op2
             00：         10u   10u
             01：         5u    5u
             10：         2.5u  5u
             11：         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 电流模式调整
             00 输出级电流正常
             01 输出级电流加大（适用于5uA偏置）
             10 不建议使用
             11 输出级电流再加大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 电流模式调整
             bit0：
             0： 输出级电流正常
             1： 输出级电流加大（适用于5uA偏置）
             bit1：
             0： miller补偿电容正常
             1： miller补偿电容变大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION结构:  ABB_TX_CH0_4G_ANA_2_UNION */
#define ABB_TX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2F)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
             000：4G
             001：3G
             010：3G_DC &amp; TDS
             011：2G(默认)
             100：reserved
             101：CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
   UNION结构:  ABB_RX_TDS_ANA_1_UNION */
#define ABB_RX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x30)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
 bit[7:6]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1： CA mode
             0： others
   UNION结构:  ABB_RX_TDS_ANA_2_UNION */
#define ABB_RX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x31)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00：5MHz(默认)WSC&amp;GSM&amp;CDMA
             01：10MHz WDC
             10：Reserved
             11：20MHz LTE
 bit[5:4]    TX Mode 时钟控制：
             00：1分频
             01：2分频(默认)
             10：3分频
             11：4分频

 bit[3]      TX_I DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
             000：4G
             001：3G &amp; TDS
             010：CA
             011：2G(默认)
             1xx：CDMA
   UNION结构:  ABB_TX_TDS_ANA_1_UNION */
#define ABB_TX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x32)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr49。
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
 bit[6]      TBD
 bit[5:4]    LPF 运放偏置电流调整
             运放电流：   op1   op2
             00：         10u   10u
             01：         5u    5u
             10：         2.5u  5u
             11：         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 电流模式调整
             00 输出级电流正常
             01 输出级电流加大（适用于5uA偏置）
             10 不建议使用
             11 输出级电流再加大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 电流模式调整
             bit0：
             0： 输出级电流正常
             1： 输出级电流加大（适用于5uA偏置）
             bit1：
             0： miller补偿电容正常
             1： miller补偿电容变大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION结构:  ABB_TX_TDS_ANA_2_UNION */
#define ABB_TX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x33)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
             000：4G
             001：3G
             010：3G_DC &amp; TDS
             011：2G(默认)
             100：reserved
             101：CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
   UNION结构:  ABB_RX_IDLE_ANA_1_UNION */
#define ABB_RX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3C)

/* 寄存器说明：IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr01。
 bit[7:6]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1： CA mode
             0： others
   UNION结构:  ABB_RX_IDLE_ANA_2_UNION */
#define ABB_RX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00：5MHz(默认)WSC&amp;GSM&amp;CDMA
             01：10MHz WDC
             10：Reserved
             11：20MHz LTE
 bit[5:4]    TX Mode 时钟控制：
             00：1分频
             01：2分频(默认)
             10：3分频
             11：4分频

 bit[3]      TX_I DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
             000：4G &amp; ET &amp; APT
             001：3G &amp; TDS
             010：CA
             011：2G(默认)
             1xx：CDMA
   UNION结构:  ABB_TX_IDLE_ANA_1_UNION */
#define ABB_TX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3E)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr49。
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
 bit[6]      TBD
 bit[5:4]    LPF 运放偏置电流调整
             运放电流：   op1   op2
             00：         10u   10u
             01：         5u    5u
             10：         2.5u  5u
             11：         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 电流模式调整
             00 输出级电流正常
             01 输出级电流加大（适用于5uA偏置）
             10 不建议使用
             11 输出级电流再加大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 电流模式调整
             bit0：
             0： 输出级电流正常
             1： 输出级电流加大（适用于5uA偏置）
             bit1：
             0： miller补偿电容正常
             1： miller补偿电容变大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION结构:  ABB_TX_IDLE_ANA_2_UNION */
#define ABB_TX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3F)

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
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0xA2)

/* 寄存器说明：CFR峰值检测窗长寄存器。
 bit[7:4]    CFR削波因子
 bit[3]      Reserved
 bit[2]      CFR滤波器选择：
             0：bypass滤波器
             1：不bypass滤波器
 bit[1:0]    CFR峰值检测方式：
             00：单点提峰
             01：区间提峰
             10：滑窗提峰
             11：全部峰值
   UNION结构:  ABB_CH0_CFR_CTRL_UNION */
#define ABB_CH0_CFR_CTRL_ADDR                         (ABB_BASE_ADDR + 0xA3)

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
 bit[7]      Reserved
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
 bit[7]      Reserved
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
 bit[7]      Reserved
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
 bit[7]      Reserved
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
 bit[7:2]    Reserved
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
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC4)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器1。
   详      述：RXA天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC5)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xC6)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器1。
   详      述：RXB天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC7)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC8)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器1。
   详      述：RXB天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC9)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xCA)

/* 寄存器说明：数字调试寄存器。
 bit[7]      Reserved
 bit[6]      TX通道调制器选择：comstarV520 Reserved
             0：5阶调制器(for V510)
             1：1阶调制器(for V511)
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
 bit[7:4]    Reserved
 bit[3]      WPLL Power Down控制
             0：Power On(默认)
             1：Power Down
 bit[2]      GPLL Power Down控制
             0：Power On
             1：Power Down(默认)
 bit[1]      RXC_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_I_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1时工作，否则关闭
             ComstarV511_Reserved
 bit[0]      RXC_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_Q_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1时工作，否则关闭
             ComstarV511_Reserved
   UNION结构:  ABB_CH0_REG_ANALOG_WR02_UNION */
#define ABB_CH0_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0xD0)

/* 寄存器说明：数模接口时钟控制寄存器。
 bit[7]      Reserved
 bit[6]      CLK_245M Power Down控制
             0：Power On
             1：Power Down(默认)
 bit[5]      CLK_52M Power Down控制
             0：Power On(默认)
             1：Power Down
 bit[4]      CLK_61D44M Power Down控制
             0：Power On(默认)
             1：Power Down
 bit[3]      TX 采样时钟沿选择：
             0：正沿(默认)
             1：反沿
 bit[2]      52M和104M输出选择：
             0：104M
             1：52M
 bit[1:0]    Reserved
   UNION结构:  ABB_CH0_REG_ANALOG_WR03_UNION */
#define ABB_CH0_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0xD1)

/* 寄存器说明：Other控制寄存器。
 bit[7:4]    Reserved
 bit[3]      RX ADC自动tuning控制
             0：手动tuning，tuning选择RX_TUNE1,RX_TUNE2,RX_TUNE3的值(默认)
             1：自动tuning，RX通道的calibration值为CAL_VALUE
 bit[2]      TX ADC自动tuning控制
             0：手动tuning，tuning选择TX_TUNE1,TX_TUNE2,TX_TUNE3的值(默认)
             1：自动tuning，TX通道的calibration值为CAL_VALUE
 bit[1]      Reserved
 bit[0]      Calibration enable(默认为0)
             上升沿启动Calibration过程
   UNION结构:  ABB_CH0_REG_ANALOG_WR04_UNION */
#define ABB_CH0_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0xD2)

/* 寄存器说明：ADC第一级积分器电容tuning寄存器。
 bit[7]      Reserved
 bit[6:0]    ADC第一级积分器电容tuning
   UNION结构:  ABB_CH0_REG_ANALOG_WR05_UNION */
#define ABB_CH0_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0xD3)

/* 寄存器说明：ADC第二级积分器电容tuning寄存器。
 bit[7]      Reserved
 bit[6:0]    ADC第二级积分器电容tuning
   UNION结构:  ABB_CH0_REG_ANALOG_WR06_UNION */
#define ABB_CH0_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0xD4)

/* 寄存器说明：ADC第三级积分器电容tuning寄存器。
 bit[7]      Reserved
 bit[6:0]    ADC第三级积分器电容tuning
   UNION结构:  ABB_CH0_REG_ANALOG_WR07_UNION */
#define ABB_CH0_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0xD5)

/* 寄存器说明：DAC Tuning控制寄存器。
 bit[7]      Reserved
 bit[6:0]    TX_TUNE1控制信号
   UNION结构:  ABB_CH0_REG_ANALOG_WR08_UNION */
#define ABB_CH0_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0xD6)

/* 寄存器说明：DAC Tuning控制寄存器。
 bit[7]      Reserved
 bit[6:0]    TX_TUNE2控制信号
   UNION结构:  ABB_CH0_REG_ANALOG_WR09_UNION */
#define ABB_CH0_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0xD7)

/* 寄存器说明：DAC Tuning控制寄存器。
 bit[7]      Reserved
 bit[6:0]    TX_TUNE3控制信号
   UNION结构:  ABB_CH0_REG_ANALOG_WR10_UNION */
#define ABB_CH0_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0xD8)

/* 寄存器说明：时钟反沿控制寄存器。
 bit[7]      RX_ADC LDO使能控制
             0：Power Down(默认)
             1：Power On
 bit[6]      ADC SYNC信号采样沿控制：
             0：正沿(默认)
             1：反沿
 bit[5]      ADC采样沿控制：
             0：正沿(默认)
             1：反沿
 bit[4:2]    Rx CK LDO电源电压
             000：0.9V(默认)
 bit[1]      Rx CK LDO电源负载调整
             0：不开启(默认)
             1：开启
 bit[0]      ADC量化器校准使能：
             0：Not Cal(默认)
             1：Cal
   UNION结构:  ABB_CH0_REG_ANALOG_WR38_UNION */
#define ABB_CH0_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0xD9)

/* 寄存器说明：DUM控制寄存器。
 bit[7]      RX DEM Mode Selection,bit 2,和ch0_reg_analog_wr00的bit3和bit0组合成3bit，实现如下9种组合：
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
 bit[6:2]    Reserved
 bit[1]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable
 bit[0]      TX Q channel  dummy logic control signal
             1：enable(默认)
             0：disable
   UNION结构:  ABB_CH0_REG_ANALOG_WR39_UNION */
#define ABB_CH0_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0xDA)

/* 寄存器说明：标志位只读寄存器。
 bit[7]      WPLL的LOCK信号
 bit[6]      GPLL的LOCK信号
 bit[5]      RC Calibration Done信号
 bit[4:0]    Reserved
   UNION结构:  ABB_CH0_REG_ANALOG_RO0_UNION */
#define ABB_CH0_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0xDB)

/* 寄存器说明：RC校准只读寄存器。
 bit[7]      Reserved
 bit[6:0]    RC Calibration校准值
   UNION结构:  ABB_CH0_REG_ANALOG_RO1_UNION */
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
 bit[7:6]    GPLL VCO Current控制
             00：X1.2
             01：X1.1(默认)
             10：X1.1
             11：X1.0
 bit[5:4]    PLL鉴频鉴相器控制
             x0：鉴频鉴相器一直输出Up信号
             01：鉴频鉴相器一直输出Down信号
             11：鉴频鉴相器正常工作
 bit[3:1]    工作时钟选择
             001：选择来自于PLL的时钟作为工作时钟
             010：选择来自于CLKIN_SYSTEM的外灌时钟作为工作时钟
             100：选择来自于TCXO_IN的时钟作为工作时钟
 bit[0]      PLL的参考时钟选择
             1：CLKIN_SYSTEM作为PLL的参考时钟
             0：TCXO Buffer输出作为PLL参考时钟
   UNION结构:  ABB_CH0_REG_DEBUG_ANA0_UNION */
#define ABB_CH0_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0xE0)

/* 寄存器说明：PLL LOCK控制寄存器。
 bit[7:6]    WPLL VCO Current控制
             00：X1.2
             01：X1.1(默认)
             10：X1.1
             11：X1.0
 bit[5]      WPLL锁定检测使能
             0：不输出检测信号
             1：输出检测信号
 bit[4]      GPLL锁定检测使能
             0：不输出检测信号
             1：输出检测信号
 bit[3:2]    WPLL锁定Cycle控制
             00：4
             01：8
             10：16(默认)
             11：32
 bit[1:0]    GPLL锁定Cycle控制
             00：4
             01：8
             10：16(默认)
             11：32
   UNION结构:  ABB_CH0_REG_DEBUG_ANA1_UNION */
#define ABB_CH0_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0xE1)

/* 寄存器说明：PLL控制寄存器。
 bit[7]      反相时钟开关
             1：反相时钟打开
             0：反相时钟关闭
 bit[6:2]    Reserved
 bit[1:0]    PLL CP PowerDown控制，测试用
             00：正常工作
             01：PowerDown WPLL CP
             10：PowerDown GPLL CP
             11：PowerDown WPLL CP和GPLL CP
   UNION结构:  ABB_CH0_REG_DEBUG_ANA2_UNION */
#define ABB_CH0_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0xE2)

/* 寄存器说明：PLL控制寄存器。
 bit[7:4]    GPLL电荷泵电流控制(低有效)
             Basic：0.2*Icp
             Bit0： 0.1*Icp
             Bit1： 0.2*Icp
             Bit2： 0.4*Icp
             Bit3： 0.8*Icp
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA3_UNION */
#define ABB_CH0_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0xE3)

/* 寄存器说明：PLL控制寄存器。
 bit[7:4]    WPLL电荷泵电流控制(低有效)
             Basic：0.2*Icp
             Bit0： 0.1*Icp
             Bit1： 0.2*Icp
             Bit2： 0.4*Icp
             Bit3： 0.8*Icp
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA4_UNION */
#define ABB_CH0_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0xE4)

/* 寄存器说明：快速启动控制寄存器。
 bit[7]      ABB_REF_Fast_UP控制
             0：关闭(默认)
             1：开启
 bit[6:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA5_UNION */
#define ABB_CH0_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0xE5)

/* 寄存器说明：Bandgap和TCXO控制寄存器。
 bit[7]      reserved
 bit[6]      TEST CLK INPUT下电控制
             0：开启
             1：关闭
 bit[5:4]    TCXO BUFFER电流设置
             00：1x
             01：2x
             10：3x(默认)
             11：4x
 bit[3:2]    WPLL输入时钟频率选择
             00：76.8M
             01：38.4M
             10：38.4M
             11：19.2M(默认)
 bit[1:0]    GPLL输入时钟频率选择
             00：26M
             01：19.2MM(默认)
             10：52M
             11：38.4M
   UNION结构:  ABB_CH0_REG_DEBUG_ANA6_UNION */
#define ABB_CH0_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0xE6)

/* 寄存器说明：电流控制寄存器。
 bit[7:3]    Reserved
 bit[2:0]    L/W/G 共用ADC 差分Buffer电流调节控制
             000：5u
             001：2u
             010：3u
             011：4u
             100：6u
             101：7u
             110：8u
             111：9u
   UNION结构:  ABB_CH0_REG_DEBUG_ANA7_UNION */
#define ABB_CH0_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0xE7)

/* 寄存器说明：电流控制寄存器。
 bit[7:5]    Reserved
 bit[4:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA8_UNION */
#define ABB_CH0_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0xE8)

/* 寄存器说明：ADC控制寄存器。
 bit[7:5]    Reserved
 bit[4]      LTE ADC模块Tuning码的选择
             0：选择Tuning模块的输出作为LTE ADC的Tuning码
             1：选择寄存器的输出作为LTE ADC的Tuning码
 bit[3]      LTE ADC DEM功能关闭信号
             0：DEM使能
             1：DEM不使能
 bit[2]      Reserved
 bit[1]      LTE ADC模块启动模式选择
             0：自动模式
             1：配置寄存器模式
 bit[0]      RX方向sub_DAC Dummy单元控制，低一位
             0：开启
             1：关闭
   UNION结构:  ABB_CH0_REG_DEBUG_ANA9_UNION */
#define ABB_CH0_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0xE9)

/* 寄存器说明：ADC复位控制寄存器。
 bit[7]      LTE ADC中DAC模块Powerup控制
             0：Powerdown
             1：Powerup
 bit[6]      LTE ADC中OP模块Powerup控制
             0：Powerdown
             1：Powerup
 bit[5]      LTE ADC中CKGEN模块Powerup控制
             0：Powerdown
             1：Powerup
 bit[4]      LTE ADC中第三级积分器电容复位控制
             0：不复位
             1：复位
 bit[3]      LTE ADC中第二级积分器电容复位控制
             0：不复位
             1：复位
 bit[2]      LTE ADC中第一级积分器电容复位控制
             0：不复位
             1：复位
 bit[1:0]    RX方向sub_DAC Dummy单元控制，高两位
             0：开启
             1：关闭
   UNION结构:  ABB_CH0_REG_DEBUG_ANA10_UNION */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xEA)

/* 寄存器说明：ADC控制寄存器。
 bit[7]      0： Reference turn off
             1： BG_OPEN_EN is effective
 bit[6]      0： Reference turn on
             1： BG_OPEN_EN is not effective
 bit[5:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA11_UNION */
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
 bit[7:6]    LTE SYNC时序控制
             00：No delay
             01：250ps delay
             10：500ps delay
             11：1000ps delay
 bit[5:3]    Reserved
 bit[2:0]    LTE Overload模块配置
             00：16个连续最大码或者最小码
             01：8个连续最大码或者最小码
             10：4个连续最大码或者最小码
             11：关闭Overload检测
   UNION结构:  ABB_CH0_REG_DEBUG_ANA14_UNION */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xEE)

/* 寄存器说明：ADC延迟控制寄存器。
   详      述：LTE CLKGEN时序控制
            bit[4:0]：delay为input*40ps(默认480ps)
            bit[5]：  量化器提前关断
            bit[7:6]：DAC dealy input*40ps(默认0)
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xEF)

/* 寄存器说明：ADC控制寄存器。
 bit[7]      Reserved
 bit[6]      RX输出PDM编码控制
             0：adder encoder
             1：de-bubble encoder
 bit[5:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA16_UNION */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xF0)

/* 寄存器说明：PLL测试寄存器。
 bit[7:6]    PLL控制电压测试PAD信号选择
             00：控制电压测试PAD浮空
             01：WPLL输出控制电压到PAD
             10：GPLL输出控制电压到PAD
 bit[5:4]    PLL时钟测试PAD信号选择
             00：时钟测试PAD浮空
             01：WPLL输出时钟到PAD
             10：GPLL输出时钟到PAD
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA17_UNION */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xF1)

/* 寄存器说明：TX手工码寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xF2)

/* 寄存器说明：时钟使能控制寄存器。
 bit[7:6]    Reserved
 bit[5]      PLL模块307.2MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[4]      PLL模块307.2MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[3:2]    Reserved
 bit[1:0]    测试管脚输出时钟频率控制
             00：输出最高时速
             01：WPLL输出半速
             10：GPLL输出半速
             11：WPLL和GPLL输出半速
   UNION结构:  ABB_CH0_REG_DEBUG_ANA19_UNION */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xF3)

/* 寄存器说明：模拟调试寄存器。
 bit[7]      Tuning电路电容选择
             0：大电容
             1：小电容
 bit[6:5]    ADC第三级电容倍乘系数
             00：X1(默认)
             01：X1.5
             10：X1.25
             11：X1.125
 bit[4:3]    Reserved
 bit[2]      PLL时钟基准选择信号
             0: CH0 的TCXO时钟
             1: CH1 的TCXO时钟
 bit[1]      CH0送给CH1的TCXO时钟开关控制
             0：关闭
             1：打开
 bit[0]      TCXO Buffer选择
             0: 单端TCXO Buffer
             1: 双端TCXO Buffer
   UNION结构:  ABB_CH0_REG_DEBUG_ANA20_UNION */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xF4)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xF5)

/* 寄存器说明：模拟调试寄存器。
   详      述：Tuning code配置值
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
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xFA)

/* 寄存器说明：模拟调试只读寄存器。
   详      述：量化器校正是否结束
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0xFB)

/* 寄存器说明：SINE发送寄存器。
 bit[7:4]    正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f
 bit[3:2]    正弦波发送幅度控制
             00：满量程
             01：3/4量程
             10：1/2量程
             11：1/4量程
 bit[1]      正弦波发送通道切换
             0：CH1
             1：CH0
 bit[0]      正弦波发送使能
             0：不发送
             1：发送
   UNION结构:  ABB_SINE_GENERATE_UNION */
#define ABB_SINE_GENERATE_ADDR                        (ABB_BASE_ADDR + 0xFF)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr50。
 bit[7]      TX 采样时钟沿选择：
             0：正沿(默认)
             1：反沿
 bit[6:5]    Reserved


 bit[4]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable


 bit[3]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable
 bit[2:0]    LPF OP1 电流模式调整
             000：5u
             001：4u
             010：3u
             011：2u
             100：9u
             101：7u
             110：6u
             111：5u
   UNION结构:  ABB_TX_2G_ANA_3_UNION */
#define ABB_TX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x100)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x101)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x102)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr53。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC OP3电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC OP1电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_2G_ANA_3_UNION */
#define ABB_RX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x103)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr54。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC 反馈DAC运放电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC QT电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_2G_ANA_4_UNION */
#define ABB_RX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x104)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr55。
 bit[7:5]    Comstarv511_Reserved
 bit[4:3]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_2G_ANA_5_UNION */
#define ABB_RX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x105)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr50。
 bit[7]      TX 采样时钟沿选择：
             0：正沿(默认)
             1：反沿
 bit[6:5]    Reserved


 bit[4]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable


 bit[3]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable
 bit[2:0]    LPF OP1 电流模式调整
             000：5u
             001：4u
             010：3u
             011：2u
             100：9u
             101：7u
             110：6u
             111：5u
   UNION结构:  ABB_TX_CH0_3G_ANA_3_UNION */
#define ABB_TX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x106)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr51。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x107)

/* 寄存器说明：CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr52。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x108)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr53。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC OP3电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC OP1电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_CH0_3G_ANA_3_UNION */
#define ABB_RX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x109)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr54。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC 反馈DAC运放电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC QT电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_CH0_3G_ANA_4_UNION */
#define ABB_RX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10A)

/* 寄存器说明：CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr55。
 bit[7:5]    Comstarv511_Reserved
 bit[4:3]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_CH0_3G_ANA_5_UNION */
#define ABB_RX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10B)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr50。
 bit[7]      TX 采样时钟沿选择：
             0：正沿(默认)
             1：反沿
 bit[6:5]    Reserved


 bit[4]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable


 bit[3]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable
 bit[2:0]    LPF OP1 电流模式调整
             000：5u
             001：4u
             010：3u
             011：2u
             100：9u
             101：7u
             110：6u
             111：5u
   UNION结构:  ABB_TX_CH0_4G_ANA_3_UNION */
#define ABB_TX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10C)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr51。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10D)

/* 寄存器说明：CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr52。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10E)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr53。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC OP3电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC OP1电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_CH0_4G_ANA_3_UNION */
#define ABB_RX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10F)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr54。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC 反馈DAC运放电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC QT电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_CH0_4G_ANA_4_UNION */
#define ABB_RX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x110)

/* 寄存器说明：CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr55。
 bit[7:5]    Comstarv511_Reserved
 bit[4:3]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_CH0_4G_ANA_5_UNION */
#define ABB_RX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x111)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr50。
 bit[7]      TX 采样时钟沿选择：
             0：正沿(默认)
             1：反沿
 bit[6:5]    Reserved


 bit[4]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable


 bit[3]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable
 bit[2:0]    LPF OP1 电流模式调整
             000：5u
             001：4u
             010：3u
             011：2u
             100：9u
             101：7u
             110：6u
             111：5u
   UNION结构:  ABB_TX_TDS_ANA_3_UNION */
#define ABB_TX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x112)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x113)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x114)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr53。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC OP3电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC OP1电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_TDS_ANA_3_UNION */
#define ABB_RX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x115)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr54。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC 反馈DAC运放电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC QT电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_TDS_ANA_4_UNION */
#define ABB_RX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x116)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr55。
 bit[7:5]    Comstarv511_Reserved
 bit[4:3]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_TDS_ANA_5_UNION */
#define ABB_RX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x117)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr50。
 bit[7]      TX 采样时钟沿选择：
             0：正沿(默认)
             1：反沿
 bit[6:5]    Reserved


 bit[4]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable


 bit[3]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable
 bit[2:0]    LPF OP1 电流模式调整
             000：5u
             001：4u
             010：3u
             011：2u
             100：9u
             101：7u
             110：6u
             111：5u
   UNION结构:  ABB_TX_IDLE_ANA_3_UNION */
#define ABB_TX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12A)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12B)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12C)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr53。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC OP3电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC OP1电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_IDLE_ANA_3_UNION */
#define ABB_RX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12D)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr54。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC 反馈DAC运放电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC QT电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_IDLE_ANA_4_UNION */
#define ABB_RX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12E)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr55。
 bit[7:5]    Comstarv511_Reserved
 bit[4:3]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_IDLE_ANA_5_UNION */
#define ABB_RX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12F)

/* 寄存器说明：模拟调试寄存器。
 bit[7]      Reserved
 bit[6:4]    TBD
 bit[3:2]    TBD
 bit[1:0]    TBD
   UNION结构:  ABB_CH0_REG_DEBUG_ANA27_UNION */
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

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
 bit[7:6]    BWCT_OP1 OP1带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[5:4]    BWCT_OP2 OP2带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[3:2]    BWCT_OP3 OP3带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[1:0]    Reserved
   UNION结构:  ABB_RX_2G_ANA_6_UNION */
#define ABB_RX_2G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x18F)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
 bit[7]      反馈子DAC偏置电流控制
             0 大电流，噪声性能好
             1 小电流，噪声性能差
 bit[6]      反馈子DAC调制深度控制
             0 调制深度0.5
             1 调制深度0.75
 bit[5]      OP3是否使用Gm_bias偏置
             0 gmbias模块不使能，OP3使用电流镜偏置
             1 gmbias模块使能，OP3使用gmbias偏置
 bit[4]      量化器参考电压选择
             0 选择ADC Buffer作为量化器的参考电压源
             1 选择电阻分压作为量化器的参考电压源
 bit[3:0]    Reserved
   UNION结构:  ABB_RX_2G_ANA_7_UNION */
#define ABB_RX_2G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x190)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00： LTE模式
             01： WDC &amp; X &amp; TDS_A模式
             1x： W &amp; G &amp; TDS_B模式
 bit[4:0]    CK_CTRL_DATA
             00000 反馈DAC时序提前量最少
             11111 反馈DAC时序提前量最大
   UNION结构:  ABB_RX_2G_ANA_8_UNION */
#define ABB_RX_2G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x191)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：Reserved
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
 bit[7:6]    BWCT_OP1 OP1带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[5:4]    BWCT_OP2 OP2带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[3:2]    BWCT_OP3 OP3带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[1:0]    Reserved
   UNION结构:  ABB_RX_3G_ANA_6_UNION */
#define ABB_RX_3G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x195)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
 bit[7]      反馈子DAC偏置电流控制
             0 大电流，噪声性能好
             1 小电流，噪声性能差
 bit[6]      反馈子DAC调制深度控制
             0 调制深度0.5
             1 调制深度0.75
 bit[5]      OP3是否使用Gm_bias偏置
             0 gmbias模块不使能，OP3使用电流镜偏置
             1 gmbias模块使能，OP3使用gmbias偏置
 bit[4]      量化器参考电压选择
             0 选择ADC Buffer作为量化器的参考电压源
             1 选择电阻分压作为量化器的参考电压源
 bit[3:0]    Reserved
   UNION结构:  ABB_RX_3G_ANA_7_UNION */
#define ABB_RX_3G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x196)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00： LTE模式
             01： WDC &amp; X &amp; TDS_A模式
             1x： W &amp; G &amp; TDS_B模式
 bit[4:0]    CK_CTRL_DATA
             00000 反馈DAC时序提前量最少
             11111 反馈DAC时序提前量最大
   UNION结构:  ABB_RX_3G_ANA_8_UNION */
#define ABB_RX_3G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x197)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_3G_ANA_9_ADDR                          (ABB_BASE_ADDR + 0x198)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_3G_ANA_10_ADDR                         (ABB_BASE_ADDR + 0x199)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_3G_ANA_11_ADDR                         (ABB_BASE_ADDR + 0x19A)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
 bit[7:6]    BWCT_OP1 OP1带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[5:4]    BWCT_OP2 OP2带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[3:2]    BWCT_OP3 OP3带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[1:0]    Reserved
   UNION结构:  ABB_RX_4G_ANA_6_UNION */
#define ABB_RX_4G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x19B)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
 bit[7]      反馈子DAC偏置电流控制
             0 大电流，噪声性能好
             1 小电流，噪声性能差
 bit[6]      反馈子DAC调制深度控制
             0 调制深度0.5
             1 调制深度0.75
 bit[5]      OP3是否使用Gm_bias偏置
             0 gmbias模块不使能，OP3使用电流镜偏置
             1 gmbias模块使能，OP3使用gmbias偏置
 bit[4]      量化器参考电压选择
             0 选择ADC Buffer作为量化器的参考电压源
             1 选择电阻分压作为量化器的参考电压源
 bit[3:0]    Reserved
   UNION结构:  ABB_RX_4G_ANA_7_UNION */
#define ABB_RX_4G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x19C)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00： LTE模式
             01： WDC &amp; X &amp; TDS_A模式
             1x： W &amp; G &amp; TDS_B模式
 bit[4:0]    CK_CTRL_DATA
             00000 反馈DAC时序提前量最少
             11111 反馈DAC时序提前量最大
   UNION结构:  ABB_RX_4G_ANA_8_UNION */
#define ABB_RX_4G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x19D)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_4G_ANA_9_ADDR                          (ABB_BASE_ADDR + 0x19E)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr60。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_4G_ANA_10_ADDR                         (ABB_BASE_ADDR + 0x19F)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr61。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_RX_4G_ANA_11_ADDR                         (ABB_BASE_ADDR + 0x1A0)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr56。
 bit[7:6]    BWCT_OP1 OP1带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[5:4]    BWCT_OP2 OP2带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[3:2]    BWCT_OP3 OP3带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[1:0]    Reserved
   UNION结构:  ABB_RX_TDS_ANA_6_UNION */
#define ABB_RX_TDS_ANA_6_ADDR                         (ABB_BASE_ADDR + 0x1A1)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr57。
 bit[7]      反馈子DAC偏置电流控制
             0 大电流，噪声性能好
             1 小电流，噪声性能差
 bit[6]      反馈子DAC调制深度控制
             0 调制深度0.5
             1 调制深度0.75
 bit[5]      OP3是否使用Gm_bias偏置
             0 gmbias模块不使能，OP3使用电流镜偏置
             1 gmbias模块使能，OP3使用gmbias偏置
 bit[4]      量化器参考电压选择
             0 选择ADC Buffer作为量化器的参考电压源
             1 选择电阻分压作为量化器的参考电压源
 bit[3:0]    Reserved
   UNION结构:  ABB_RX_TDS_ANA_7_UNION */
#define ABB_RX_TDS_ANA_7_ADDR                         (ABB_BASE_ADDR + 0x1A2)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr58。
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00： LTE模式
             01： WDC &amp; X &amp; TDS_A模式
             1x： W &amp; G &amp; TDS_B模式
 bit[4:0]    CK_CTRL_DATA
             00000 反馈DAC时序提前量最少
             11111 反馈DAC时序提前量最大
   UNION结构:  ABB_RX_TDS_ANA_8_UNION */
#define ABB_RX_TDS_ANA_8_ADDR                         (ABB_BASE_ADDR + 0x1A3)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：Reserved
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
 bit[7:6]    BWCT_OP1 OP1带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[5:4]    BWCT_OP2 OP2带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[3:2]    BWCT_OP3 OP3带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[1:0]    Reserved
   UNION结构:  ABB_RX_IDLE_ANA_6_UNION */
#define ABB_RX_IDLE_ANA_6_ADDR                        (ABB_BASE_ADDR + 0x1A7)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr57。
 bit[7]      反馈子DAC偏置电流控制
             0 大电流，噪声性能好
             1 小电流，噪声性能差
 bit[6]      反馈子DAC调制深度控制
             0 调制深度0.5
             1 调制深度0.75
 bit[5]      OP3是否使用Gm_bias偏置
             0 gmbias模块不使能，OP3使用电流镜偏置
             1 gmbias模块使能，OP3使用gmbias偏置
 bit[4]      量化器参考电压选择
             0 选择ADC Buffer作为量化器的参考电压源
             1 选择电阻分压作为量化器的参考电压源
 bit[3:0]    Reserved
   UNION结构:  ABB_RX_IDLE_ANA_7_UNION */
#define ABB_RX_IDLE_ANA_7_ADDR                        (ABB_BASE_ADDR + 0x1A8)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr58。
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00： LTE模式
             01： WDC &amp; X &amp; TDS_A模式
             1x： W &amp; G &amp; TDS_B模式
 bit[4:0]    CK_CTRL_DATA
             00000 反馈DAC时序提前量最少
             11111 反馈DAC时序提前量最大
   UNION结构:  ABB_RX_IDLE_ANA_8_UNION */
#define ABB_RX_IDLE_ANA_8_ADDR                        (ABB_BASE_ADDR + 0x1A9)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：Reserved
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

/* 寄存器说明：线控强制配置使能。
 bit[7:3]    Reserved
 bit[2]      TX通道线控选择
             0：tie to 0
             1：from line ctrl
 bit[1]      RXB通道线控选择
             0：tie to 0
             1：from line ctrl
 bit[0]      RXA通道线控选择
             0：tie to 0
             1：from line ctrl
   UNION结构:  ABB_CH0_LINE_SEL_UNION */
#define ABB_CH0_LINE_SEL_ADDR                         (ABB_BASE_ADDR + 0x1D0)

/* 寄存器说明：线控强制配置值。
 bit[7]      线控信号CH0_CFR_EN强制配置使能
 bit[6]      线控信号CH0_CFR_EN强制配置值
 bit[5]      线控信号CH0_RXA_BLK_EN, CH0_RXB_BLK_EN强制配置使能
 bit[4]      线控信号CH0_RXA_BLK_EN, CH0_RXB_BLK_EN强制配置值
 bit[3]      线控信号CH0_LINE_CTRL_MODE强制配置使能
 bit[2:0]    线控信号CH0_LINE_CTRL_MODE强制配置值
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
 bit[7:3]    Reserved
 bit[2]      CFR自动门控使能：
             0：使能
             1：不使能
 bit[1]      干扰检测自动门控使能：
             0：使能
             1：不使能
 bit[0]      BLOCKING自动门控使能：
             0：使能
             1：不使能
   UNION结构:  ABB_CH0_CLK_SEL_UNION */
#define ABB_CH0_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1D2)

/* 寄存器说明：线控状态上报寄存器。
 bit[7:3]    Reserved
 bit[2]      TX_EN线控状态上报
 bit[1]      RXB_EN线控状态上报
 bit[0]      RXA_EN线控状态上报
   UNION结构:  ABB_CH0_LINE_RPT0_UNION */
#define ABB_CH0_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1F0)

/* 寄存器说明：线控状态上报寄存器。
 bit[7]      Reserved
 bit[6]      CFR_EN线控状态上报
 bit[5]      RXB_BLK_EN线控状态上报
 bit[4]      RXA_BLK_EN线控状态上报
 bit[3]      Reserved
 bit[2:0]    线控信号ch0_LINE_CTRL_MODE状态上报
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：ET模式
             6：APT模式
             7：CA模式
   UNION结构:  ABB_CH0_LINE_RPT1_UNION */
#define ABB_CH0_LINE_RPT1_ADDR                        (ABB_BASE_ADDR + 0x1F1)

/* 寄存器说明：RX数字工作模式上报寄存器。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SCReserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
             others：reserved
 bit[2]      RX通道半带滤波器bypass控制上报：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制上报：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      RX通道补偿滤波器补偿固定系数选择上报：
             0：固定系数1
             1：固定系数2
   UNION结构:  ABB_CH0_RX_MODE_RPT_UNION */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F2)

/* 寄存器说明：TX数字工作模式上报寄存器。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             Reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制上报：
                  2G,     3G,     4G,      TDS,      CA
                 (78M) (153.6M) (307.2M) (153.6M) (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             3：-------,--------, 7.68MHz,--------,--------
             4：-------,--------, 3.84MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制上报：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认)
 bit[0]      TX通道补偿滤波器bypass控制上报：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_CH0_TX_MODE_RPT_UNION */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F3)

/* 寄存器说明：RX数字工作状态上报寄存器。
 bit[7]      Reserved
 bit[6]      RXB通道数据削顶指示信号
 bit[5]      RXB通道输出数据翻转指示信号
 bit[4]      RXA通道数据削顶指示信号
 bit[3]      RXA通道输出数据翻转指示信号
 bit[2]      RX通道输出数据有效指示信号
 bit[1]      RX通道输出数字随路时钟
 bit[0]      RX通道模拟随路时钟
   UNION结构:  ABB_CH0_RX_STATE_RPT_UNION */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1F4)

/* 寄存器说明：TX数字工作状态上报寄存器。
 bit[7]      TX通道FIFO读空状态
 bit[6]      TX通道FIFO写满状态
 bit[5]      TX通道数据削顶指示信号
 bit[4]      TX通道数据翻转指示信号
 bit[3]      TX通道数字主工作时钟
 bit[2]      TX通输入数据有效指示信号
 bit[1]      TX通道输入数字随路时钟
 bit[0]      TX通道模拟随路时钟
   UNION结构:  ABB_CH0_TX_STATE_RPT_UNION */
#define ABB_CH0_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1F5)

/* 寄存器说明：RXB通道选择。
 bit[7:1]    保留。
 bit[0]      RXB通道选择。
             0：选择CH0；
             1：选择CH1。.
   UNION结构:  ABB_RXB_CH_SEL_UNION */
#define ABB_RXB_CH_SEL_ADDR                           (ABB_BASE_ADDR + 0x1F6)

/* 寄存器说明：通道0 TDS配置寄存器。
 bit[7:3]    保留。
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

/* 寄存器说明：通道0 CFR配置寄存器。
   详      述：通道0 CFR峰值检测门限值低bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_CFR_PDET_THR0_ADDR                    (ABB_BASE_ADDR + 0x201)

/* 寄存器说明：通道0 CFR配置寄存器。
   详      述：通道0 CFR峰值检测门限值低bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_CFR_PDET_THR1_ADDR                    (ABB_BASE_ADDR + 0x202)

/* 寄存器说明：通道0 CFR配置寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0 CFR峰值检测门限值低bit[17:16]。
   UNION结构:  ABB_CH0_CFR_PDET_THR2_UNION */
#define ABB_CH0_CFR_PDET_THR2_ADDR                    (ABB_BASE_ADDR + 0x203)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点A能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EA0_ADDR                        (ABB_BASE_ADDR + 0x204)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点A能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EA1_ADDR                        (ABB_BASE_ADDR + 0x205)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点A能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EA2_ADDR                        (ABB_BASE_ADDR + 0x206)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXA通道I路节点A能量统计值bit[25:24]。
   UNION结构:  ABB_CH0_RXA_I_EA3_UNION */
#define ABB_CH0_RXA_I_EA3_ADDR                        (ABB_BASE_ADDR + 0x207)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点B能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EB0_ADDR                        (ABB_BASE_ADDR + 0x208)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点B能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EB1_ADDR                        (ABB_BASE_ADDR + 0x209)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点B能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EB2_ADDR                        (ABB_BASE_ADDR + 0x20A)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点B能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EB3_ADDR                        (ABB_BASE_ADDR + 0x20B)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点B能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EB4_ADDR                        (ABB_BASE_ADDR + 0x20C)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点C能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EC0_ADDR                        (ABB_BASE_ADDR + 0x20D)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点C能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EC1_ADDR                        (ABB_BASE_ADDR + 0x20E)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点C能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EC2_ADDR                        (ABB_BASE_ADDR + 0x20F)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点C能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EC3_ADDR                        (ABB_BASE_ADDR + 0x210)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点C能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EC4_ADDR                        (ABB_BASE_ADDR + 0x211)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点C能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_EC5_ADDR                        (ABB_BASE_ADDR + 0x212)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXA通道I路节点C能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXA_I_EC6_UNION */
#define ABB_CH0_RXA_I_EC6_ADDR                        (ABB_BASE_ADDR + 0x213)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点D能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_ED0_ADDR                        (ABB_BASE_ADDR + 0x214)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点D能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_ED1_ADDR                        (ABB_BASE_ADDR + 0x215)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点D能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_ED2_ADDR                        (ABB_BASE_ADDR + 0x216)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点D能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_ED3_ADDR                        (ABB_BASE_ADDR + 0x217)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点D能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_ED4_ADDR                        (ABB_BASE_ADDR + 0x218)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道I路节点D能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_ED5_ADDR                        (ABB_BASE_ADDR + 0x219)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXA通道I路节点D能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXA_I_ED6_UNION */
#define ABB_CH0_RXA_I_ED6_ADDR                        (ABB_BASE_ADDR + 0x21A)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点A能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EA0_ADDR                        (ABB_BASE_ADDR + 0x21B)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点A能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EA1_ADDR                        (ABB_BASE_ADDR + 0x21C)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点A能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EA2_ADDR                        (ABB_BASE_ADDR + 0x21D)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXA通道Q路节点A能量统计值bit[25:24]。
   UNION结构:  ABB_CH0_RXA_Q_EA3_UNION */
#define ABB_CH0_RXA_Q_EA3_ADDR                        (ABB_BASE_ADDR + 0x21E)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点B能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EB0_ADDR                        (ABB_BASE_ADDR + 0x21F)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点B能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EB1_ADDR                        (ABB_BASE_ADDR + 0x220)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点B能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EB2_ADDR                        (ABB_BASE_ADDR + 0x221)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点B能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EB3_ADDR                        (ABB_BASE_ADDR + 0x222)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点B能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EB4_ADDR                        (ABB_BASE_ADDR + 0x223)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点C能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EC0_ADDR                        (ABB_BASE_ADDR + 0x224)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点C能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EC1_ADDR                        (ABB_BASE_ADDR + 0x225)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点C能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EC2_ADDR                        (ABB_BASE_ADDR + 0x226)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点C能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EC3_ADDR                        (ABB_BASE_ADDR + 0x227)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点C能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EC4_ADDR                        (ABB_BASE_ADDR + 0x228)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点C能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_EC5_ADDR                        (ABB_BASE_ADDR + 0x229)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXA通道Q路节点C能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXA_Q_EC6_UNION */
#define ABB_CH0_RXA_Q_EC6_ADDR                        (ABB_BASE_ADDR + 0x22A)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点D能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_ED0_ADDR                        (ABB_BASE_ADDR + 0x22B)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点D能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_ED1_ADDR                        (ABB_BASE_ADDR + 0x22C)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点D能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_ED2_ADDR                        (ABB_BASE_ADDR + 0x22D)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点D能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_ED3_ADDR                        (ABB_BASE_ADDR + 0x22E)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点D能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_ED4_ADDR                        (ABB_BASE_ADDR + 0x22F)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXA通道Q路节点D能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_ED5_ADDR                        (ABB_BASE_ADDR + 0x230)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXA通道Q路节点D能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXA_Q_ED6_UNION */
#define ABB_CH0_RXA_Q_ED6_ADDR                        (ABB_BASE_ADDR + 0x231)

/* 寄存器说明：通道0配置寄存器。
   详      述：通道0 flush宽度[7:0]，单位为19.2M时钟周期。
   UNION结构 ：无 */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x232)

/* 寄存器说明：通道0配置寄存器。
 bit[7:3]    通道0 FLUSH值，默认为8。
 bit[2:0]    通道0 flush宽度[10:8]，单位为19.2M时钟周期。
   UNION结构:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x233)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点A能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EA0_ADDR                        (ABB_BASE_ADDR + 0x234)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点A能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EA1_ADDR                        (ABB_BASE_ADDR + 0x235)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点A能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EA2_ADDR                        (ABB_BASE_ADDR + 0x236)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXB通道I路节点A能量统计值bit[25:24]。
   UNION结构:  ABB_CH0_RXB_I_EA3_UNION */
#define ABB_CH0_RXB_I_EA3_ADDR                        (ABB_BASE_ADDR + 0x237)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点B能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EB0_ADDR                        (ABB_BASE_ADDR + 0x238)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点B能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EB1_ADDR                        (ABB_BASE_ADDR + 0x239)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点B能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EB2_ADDR                        (ABB_BASE_ADDR + 0x23A)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点B能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EB3_ADDR                        (ABB_BASE_ADDR + 0x23B)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点B能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EB4_ADDR                        (ABB_BASE_ADDR + 0x23C)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点C能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EC0_ADDR                        (ABB_BASE_ADDR + 0x23D)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点C能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EC1_ADDR                        (ABB_BASE_ADDR + 0x23E)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点C能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EC2_ADDR                        (ABB_BASE_ADDR + 0x23F)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点C能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EC3_ADDR                        (ABB_BASE_ADDR + 0x240)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点C能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EC4_ADDR                        (ABB_BASE_ADDR + 0x241)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点C能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_EC5_ADDR                        (ABB_BASE_ADDR + 0x242)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXB通道I路节点C能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXB_I_EC6_UNION */
#define ABB_CH0_RXB_I_EC6_ADDR                        (ABB_BASE_ADDR + 0x243)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点D能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_ED0_ADDR                        (ABB_BASE_ADDR + 0x244)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点D能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_ED1_ADDR                        (ABB_BASE_ADDR + 0x245)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点D能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_ED2_ADDR                        (ABB_BASE_ADDR + 0x246)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点D能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_ED3_ADDR                        (ABB_BASE_ADDR + 0x247)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点D能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_ED4_ADDR                        (ABB_BASE_ADDR + 0x248)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道I路节点D能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_ED5_ADDR                        (ABB_BASE_ADDR + 0x249)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留。
 bit[1:0]    通道0干扰检测RXB通道I路节点D能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXB_I_ED6_UNION */
#define ABB_CH0_RXB_I_ED6_ADDR                        (ABB_BASE_ADDR + 0x24A)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点A能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EA0_ADDR                        (ABB_BASE_ADDR + 0x24B)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点A能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EA1_ADDR                        (ABB_BASE_ADDR + 0x24C)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点A能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EA2_ADDR                        (ABB_BASE_ADDR + 0x24D)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留
 bit[1:0]    通道0干扰检测RXB通道Q路节点A能量统计值bit[25:24]。
   UNION结构:  ABB_CH0_RXB_Q_EA3_UNION */
#define ABB_CH0_RXB_Q_EA3_ADDR                        (ABB_BASE_ADDR + 0x24E)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点B能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EB0_ADDR                        (ABB_BASE_ADDR + 0x24F)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点B能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EB1_ADDR                        (ABB_BASE_ADDR + 0x250)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点B能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EB2_ADDR                        (ABB_BASE_ADDR + 0x251)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点B能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EB3_ADDR                        (ABB_BASE_ADDR + 0x252)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点B能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EB4_ADDR                        (ABB_BASE_ADDR + 0x253)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点C能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EC0_ADDR                        (ABB_BASE_ADDR + 0x254)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点C能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EC1_ADDR                        (ABB_BASE_ADDR + 0x255)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点C能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EC2_ADDR                        (ABB_BASE_ADDR + 0x256)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点C能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EC3_ADDR                        (ABB_BASE_ADDR + 0x257)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点C能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EC4_ADDR                        (ABB_BASE_ADDR + 0x258)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点C能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_EC5_ADDR                        (ABB_BASE_ADDR + 0x259)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留
 bit[1:0]    通道0干扰检测RXB通道Q路节点C能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXB_Q_EC6_UNION */
#define ABB_CH0_RXB_Q_EC6_ADDR                        (ABB_BASE_ADDR + 0x25A)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点D能量统计值bit[7:0]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_ED0_ADDR                        (ABB_BASE_ADDR + 0x25B)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点D能量统计值bit[15:8]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_ED1_ADDR                        (ABB_BASE_ADDR + 0x25C)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点D能量统计值bit[23:16]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_ED2_ADDR                        (ABB_BASE_ADDR + 0x25D)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点D能量统计值bit[31:24]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_ED3_ADDR                        (ABB_BASE_ADDR + 0x25E)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点D能量统计值bit[39:32]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_ED4_ADDR                        (ABB_BASE_ADDR + 0x25F)

/* 寄存器说明：通道0干扰检测上报寄存器。
   详      述：通道0干扰检测RXB通道Q路节点D能量统计值bit[47:40]。
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_ED5_ADDR                        (ABB_BASE_ADDR + 0x260)

/* 寄存器说明：通道0干扰检测上报寄存器。
 bit[7:2]    保留
 bit[1:0]    通道0干扰检测RXB通道Q路节点D能量统计值bit[49:48]。
   UNION结构:  ABB_CH0_RXB_Q_ED6_UNION */
#define ABB_CH0_RXB_Q_ED6_ADDR                        (ABB_BASE_ADDR + 0x261)

/* 寄存器说明：RX C模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TX通道FLUSH使能：
             0：不使能
             1：使能
 bit[0]      TX通道CFR bypass控制：
             0：不bypass
             1：bypass(默认)
   UNION结构:  ABB_TX_C_DIG_3_UNION */
#define ABB_TX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x404)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
             000：4G
             001：3G
             010：3G_DC &amp; TDS
             011：2G(默认)
             100：reserved
             101：CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000：DWA
             001：CLA1
             010：CLA2
             011：CLA3
             100：CLA4
             101：CLA5
             110：CLA6
             111：CLA7
   UNION结构:  ABB_RX_C_ANA_1_UNION */
#define ABB_RX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x405)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr01。
 bit[7:6]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1： CA mode
             0： others
   UNION结构:  ABB_RX_C_ANA_2_UNION */
#define ABB_RX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x406)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr53。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC OP3电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC OP1电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_C_ANA_3_UNION */
#define ABB_RX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x407)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr54。
 bit[7:6]    Reserved
 bit[5:3]    RX ADC 反馈DAC运放电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
 bit[2:0]    RX ADC QT电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_C_ANA_4_UNION */
#define ABB_RX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x408)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr55。
 bit[7:5]    Comstarv511_Reserved
 bit[4:3]    Current Seting For Mode
             1x：LTE mode Current
             01：3G_DC &amp; X mode Current
             00：3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2电流控制
             000： 1.0x
             001： 0.8x
             010： 0.6x
             011： 0.4x
             100： 1.8x
             101： 1.6x
             110： 1.4x
             111： 1.2x
   UNION结构:  ABB_RX_C_ANA_5_UNION */
#define ABB_RX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x409)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr56。
 bit[7:6]    BWCT_OP1 OP1带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[5:4]    BWCT_OP2 OP2带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[3:2]    BWCT_OP3 OP3带宽控制
             1x： LTE模式
             01： WDC &amp; X 模式
             00： W &amp; G模式
 bit[1:0]    Reserved
   UNION结构:  ABB_RX_C_ANA_6_UNION */
#define ABB_RX_C_ANA_6_ADDR                           (ABB_BASE_ADDR + 0x40A)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr57。
 bit[7]      反馈子DAC偏置电流控制
             0 大电流，噪声性能好
             1 小电流，噪声性能差
 bit[6]      反馈子DAC调制深度控制
             0 调制深度0.5
             1 调制深度0.75
 bit[5]      OP3是否使用Gm_bias偏置
             0 gmbias模块不使能，OP3使用电流镜偏置
             1 gmbias模块使能，OP3使用gmbias偏置
 bit[4]      量化器参考电压选择
             0 选择ADC Buffer作为量化器的参考电压源
             1 选择电阻分压作为量化器的参考电压源
 bit[3:0]    Reserved
   UNION结构:  ABB_RX_C_ANA_7_UNION */
#define ABB_RX_C_ANA_7_ADDR                           (ABB_BASE_ADDR + 0x40B)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr58。
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00： LTE模式
             01： WDC &amp; X &amp; TDS_A模式
             1x： W &amp; G &amp; TDS_B模式
 bit[4:0]    CK_CTRL_DATA
             00000 反馈DAC时序提前量最少
             11111 反馈DAC时序提前量最大
   UNION结构:  ABB_RX_C_ANA_8_UNION */
#define ABB_RX_C_ANA_8_ADDR                           (ABB_BASE_ADDR + 0x40C)

/* 寄存器说明：RX C配置寄存器，经过线控逻辑后送至reg_analog_wr59。
   详      述：Reserved
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
 bit[7:6]    TX filter截止频率选择：
             00：5MHz(默认)WSC&amp;GSM&amp;CDMA
             01：10MHz WDC
             10：Reserved
             11：20MHz LTE
 bit[5:4]    TX Mode 时钟控制：
             00：1分频
             01：2分频(默认)
             10：3分频
             11：4分频

 bit[3]      TX_I DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0：Power On
             1：Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
             000：4G &amp; ET &amp; APT
             001：3G &amp; TDS
             010：CA
             011：2G(默认)
             1xx：CDMA
   UNION结构:  ABB_TX_C_ANA_1_UNION */
#define ABB_TX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x410)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr49。
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。
 bit[6]      TBD
 bit[5:4]    LPF 运放偏置电流调整
             运放电流：   op1   op2
             00：         10u   10u
             01：         5u    5u
             10：         2.5u  5u
             11：         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 电流模式调整
             00 输出级电流正常
             01 输出级电流加大（适用于5uA偏置）
             10 不建议使用
             11 输出级电流再加大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 电流模式调整
             bit0：
             0： 输出级电流正常
             1： 输出级电流加大（适用于5uA偏置）
             bit1：
             0： miller补偿电容正常
             1： miller补偿电容变大（适用于2.5uA偏置）
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION结构:  ABB_TX_C_ANA_2_UNION */
#define ABB_TX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x411)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr50。
 bit[7]      TX 采样时钟沿选择：
             0：正沿(默认)
             1：反沿
 bit[6:5]    Reserved


 bit[4]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable


 bit[3]      TX I channel  dummy logic control signal
             1：enable(默认)
             0：disable
 bit[2:0]    LPF OP1 电流模式调整
             000：5u
             001：4u
             010：3u
             011：2u
             100：9u
             101：7u
             110：6u
             111：5u
   UNION结构:  ABB_TX_C_ANA_3_UNION */
#define ABB_TX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x412)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr51。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x413)

/* 寄存器说明：TX C配置寄存器，经过线控逻辑后送至reg_analog_wr52。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x414)





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
                                                            001：3G_SCReserved */
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
                                                         Reserved */
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
        unsigned long  tx_cfr_bp_2g   : 1;  /* bit[0]  : TX通道CFR bypass控制：
                                                         0：不bypass
                                                         1：bypass(默认) */
        unsigned long  tx_flush_en_2g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  reserved       : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_START    (0)
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_END      (0)
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_START  (1)
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_END    (1)


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
        unsigned long  rx_comp_sel_b0_3g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                            00：固定系数1；
                                                            01：固定系数2；
                                                            10：固定系数3；
                                                            11：reserved。 */
        unsigned long  rx_comp_fix_3g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                            0：系数不固定，由寄存器配置
                                                            1：系数固定 */
        unsigned long  rx_hb_bp_3g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                            0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                            1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_3g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                            others：reserved */
        unsigned long  rx_mode_dig_3g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                            000：2G(默认)
                                                            001：3G_SCReserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_1_UNION;
#define ABB_RX_CH0_3G_DIG_1_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_CH0_3G_DIG_1_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_CH0_3G_DIG_1_rx_comp_fix_3g_START     (1)
#define ABB_RX_CH0_3G_DIG_1_rx_comp_fix_3g_END       (1)
#define ABB_RX_CH0_3G_DIG_1_rx_hb_bp_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_1_rx_hb_bp_3g_END          (2)
#define ABB_RX_CH0_3G_DIG_1_rx_rate_3g_START         (3)
#define ABB_RX_CH0_3G_DIG_1_rx_rate_3g_END           (4)
#define ABB_RX_CH0_3G_DIG_1_rx_mode_dig_3g_START     (5)
#define ABB_RX_CH0_3G_DIG_1_rx_mode_dig_3g_END       (7)


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
        unsigned long  rxa_pd_3g         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_3g         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_3g       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                            00：gain为0.5(默认)
                                                            01：gain为0.75
                                                            10：gain为0.85
                                                            11：Reserved */
        unsigned long  rx_comp_bp_3g     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                            0：不bypass(默认)
                                                            1：bypass */
        unsigned long  rx_clk_inv_3g     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                            0：正常
                                                            1：反向 */
        unsigned long  rx_flush_en_3g    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                            0：不使能
                                                            1：使能 */
        unsigned long  rx_comp_sel_b1_3g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_2_UNION;
#define ABB_RX_CH0_3G_DIG_2_rxa_pd_3g_START          (0)
#define ABB_RX_CH0_3G_DIG_2_rxa_pd_3g_END            (0)
#define ABB_RX_CH0_3G_DIG_2_rxb_pd_3g_START          (1)
#define ABB_RX_CH0_3G_DIG_2_rxb_pd_3g_END            (1)
#define ABB_RX_CH0_3G_DIG_2_gain_sel_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_2_gain_sel_3g_END          (3)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_bp_3g_START      (4)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_bp_3g_END        (4)
#define ABB_RX_CH0_3G_DIG_2_rx_clk_inv_3g_START      (5)
#define ABB_RX_CH0_3G_DIG_2_rx_clk_inv_3g_END        (5)
#define ABB_RX_CH0_3G_DIG_2_rx_flush_en_3g_START     (6)
#define ABB_RX_CH0_3G_DIG_2_rx_flush_en_3g_END       (6)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_sel_b1_3g_END    (7)


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
        unsigned long  tx_comp_bp_3g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_3g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_3g     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                              2G,     3G,     4G,      TDS,      CDMA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                         0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2：-------,--------,15.36MHz,--------,--------
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_3g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G(默认)
                                                         001：3G
                                                         010：4G
                                                         011：TDS
                                                         Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_1_UNION;
#define ABB_TX_CH0_3G_DIG_1_tx_comp_bp_3g_START   (0)
#define ABB_TX_CH0_3G_DIG_1_tx_comp_bp_3g_END     (0)
#define ABB_TX_CH0_3G_DIG_1_tx_hb_bp_3g_START     (1)
#define ABB_TX_CH0_3G_DIG_1_tx_hb_bp_3g_END       (1)
#define ABB_TX_CH0_3G_DIG_1_tx_rate_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_1_tx_rate_3g_END        (4)
#define ABB_TX_CH0_3G_DIG_1_tx_mode_dig_3g_START  (5)
#define ABB_TX_CH0_3G_DIG_1_tx_mode_dig_3g_END    (7)


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
        unsigned long  tx_q_pd_3g       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_3g       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_3g     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                           0：0(默认)
                                                           1：2
                                                           2：4
                                                           3：6 */
        unsigned long  uddwa_dith_en_3g : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                           0：不使能
                                                           1：使能 */
        unsigned long  dem_dwa_en_3g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                           0：使用CLA模式
                                                           1：使用DWA模式(默认)  */
        unsigned long  dem_lsb_bp_3g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                           0：DEM LSB 打开(默认)
                                                           1：DEM LSB bypass */
        unsigned long  dem_msb_bp_3g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                           0：DEM MSB打开(默认)
                                                           1：DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_2_UNION;
#define ABB_TX_CH0_3G_DIG_2_tx_q_pd_3g_START        (0)
#define ABB_TX_CH0_3G_DIG_2_tx_q_pd_3g_END          (0)
#define ABB_TX_CH0_3G_DIG_2_tx_i_pd_3g_START        (1)
#define ABB_TX_CH0_3G_DIG_2_tx_i_pd_3g_END          (1)
#define ABB_TX_CH0_3G_DIG_2_dem_const_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_2_dem_const_3g_END        (3)
#define ABB_TX_CH0_3G_DIG_2_uddwa_dith_en_3g_START  (4)
#define ABB_TX_CH0_3G_DIG_2_uddwa_dith_en_3g_END    (4)
#define ABB_TX_CH0_3G_DIG_2_dem_dwa_en_3g_START     (5)
#define ABB_TX_CH0_3G_DIG_2_dem_dwa_en_3g_END       (5)
#define ABB_TX_CH0_3G_DIG_2_dem_lsb_bp_3g_START     (6)
#define ABB_TX_CH0_3G_DIG_2_dem_lsb_bp_3g_END       (6)
#define ABB_TX_CH0_3G_DIG_2_dem_msb_bp_3g_START     (7)
#define ABB_TX_CH0_3G_DIG_2_dem_msb_bp_3g_END       (7)


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
        unsigned long  tx_cfr_bp_3g   : 1;  /* bit[0]  : TX通道CFR bypass控制：
                                                         0：不bypass
                                                         1：bypass(默认) */
        unsigned long  tx_flush_en_3g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  reserved       : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_3_UNION;
#define ABB_TX_CH0_3G_DIG_3_tx_cfr_bp_3g_START    (0)
#define ABB_TX_CH0_3G_DIG_3_tx_cfr_bp_3g_END      (0)
#define ABB_TX_CH0_3G_DIG_3_tx_flush_en_3g_START  (1)
#define ABB_TX_CH0_3G_DIG_3_tx_flush_en_3g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_DIG_1_UNION
 结构说明  : rx_ch0_4g_dig_1 寄存器结构定义。地址偏移量:0xA，初值:0x40，宽度:8
 寄存器说明: CH0 RX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_4g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                            00：固定系数1；
                                                            01：固定系数2；
                                                            10：固定系数3；
                                                            11：reserved。 */
        unsigned long  rx_comp_fix_4g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                            0：系数不固定，由寄存器配置
                                                            1：系数固定 */
        unsigned long  rx_hb_bp_4g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                            0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                            1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_4g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                            others：reserved */
        unsigned long  rx_mode_dig_4g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                            000：2G(默认)
                                                            001：3G_SCReserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_1_UNION;
#define ABB_RX_CH0_4G_DIG_1_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_CH0_4G_DIG_1_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_CH0_4G_DIG_1_rx_comp_fix_4g_START     (1)
#define ABB_RX_CH0_4G_DIG_1_rx_comp_fix_4g_END       (1)
#define ABB_RX_CH0_4G_DIG_1_rx_hb_bp_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_1_rx_hb_bp_4g_END          (2)
#define ABB_RX_CH0_4G_DIG_1_rx_rate_4g_START         (3)
#define ABB_RX_CH0_4G_DIG_1_rx_rate_4g_END           (4)
#define ABB_RX_CH0_4G_DIG_1_rx_mode_dig_4g_START     (5)
#define ABB_RX_CH0_4G_DIG_1_rx_mode_dig_4g_END       (7)


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
        unsigned long  rxa_pd_4g         : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_4g         : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_4g       : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                            00：gain为0.5(默认)
                                                            01：gain为0.75
                                                            10：gain为0.85
                                                            11：Reserved */
        unsigned long  rx_comp_bp_4g     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                            0：不bypass(默认)
                                                            1：bypass */
        unsigned long  rx_clk_inv_4g     : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                            0：正常
                                                            1：反向 */
        unsigned long  rx_flush_en_4g    : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                            0：不使能
                                                            1：使能 */
        unsigned long  rx_comp_sel_b1_4g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}组成补偿滤波器系数选择，参考rx_comp_sel_b0说明。 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_2_UNION;
#define ABB_RX_CH0_4G_DIG_2_rxa_pd_4g_START          (0)
#define ABB_RX_CH0_4G_DIG_2_rxa_pd_4g_END            (0)
#define ABB_RX_CH0_4G_DIG_2_rxb_pd_4g_START          (1)
#define ABB_RX_CH0_4G_DIG_2_rxb_pd_4g_END            (1)
#define ABB_RX_CH0_4G_DIG_2_gain_sel_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_2_gain_sel_4g_END          (3)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_bp_4g_START      (4)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_bp_4g_END        (4)
#define ABB_RX_CH0_4G_DIG_2_rx_clk_inv_4g_START      (5)
#define ABB_RX_CH0_4G_DIG_2_rx_clk_inv_4g_END        (5)
#define ABB_RX_CH0_4G_DIG_2_rx_flush_en_4g_START     (6)
#define ABB_RX_CH0_4G_DIG_2_rx_flush_en_4g_END       (6)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_sel_b1_4g_END    (7)


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
        unsigned long  tx_comp_bp_4g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_4g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_4g     : 3;  /* bit[2-4]: TX通道CIC滤波器输入速率控制：
                                                              2G,     3G,     4G,      TDS,      CDMA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                         0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2：-------,--------,15.36MHz,--------,--------
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_4g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G(默认)
                                                         001：3G
                                                         010：4G
                                                         011：TDS
                                                         Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_1_UNION;
#define ABB_TX_CH0_4G_DIG_1_tx_comp_bp_4g_START   (0)
#define ABB_TX_CH0_4G_DIG_1_tx_comp_bp_4g_END     (0)
#define ABB_TX_CH0_4G_DIG_1_tx_hb_bp_4g_START     (1)
#define ABB_TX_CH0_4G_DIG_1_tx_hb_bp_4g_END       (1)
#define ABB_TX_CH0_4G_DIG_1_tx_rate_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_1_tx_rate_4g_END        (4)
#define ABB_TX_CH0_4G_DIG_1_tx_mode_dig_4g_START  (5)
#define ABB_TX_CH0_4G_DIG_1_tx_mode_dig_4g_END    (7)


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
        unsigned long  tx_q_pd_4g       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_4g       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_4g     : 2;  /* bit[2-3]: TX通道DEM const系数：
                                                           0：0(默认)
                                                           1：2
                                                           2：4
                                                           3：6 */
        unsigned long  uddwa_dith_en_4g : 1;  /* bit[4]  : TX通道DEM UDDWA_DITH模块使能控制：
                                                           0：不使能
                                                           1：使能 */
        unsigned long  dem_dwa_en_4g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                           0：使用CLA模式
                                                           1：使用DWA模式(默认)  */
        unsigned long  dem_lsb_bp_4g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                           0：DEM LSB 打开(默认)
                                                           1：DEM LSB bypass */
        unsigned long  dem_msb_bp_4g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                           0：DEM MSB打开(默认)
                                                           1：DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_2_UNION;
#define ABB_TX_CH0_4G_DIG_2_tx_q_pd_4g_START        (0)
#define ABB_TX_CH0_4G_DIG_2_tx_q_pd_4g_END          (0)
#define ABB_TX_CH0_4G_DIG_2_tx_i_pd_4g_START        (1)
#define ABB_TX_CH0_4G_DIG_2_tx_i_pd_4g_END          (1)
#define ABB_TX_CH0_4G_DIG_2_dem_const_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_2_dem_const_4g_END        (3)
#define ABB_TX_CH0_4G_DIG_2_uddwa_dith_en_4g_START  (4)
#define ABB_TX_CH0_4G_DIG_2_uddwa_dith_en_4g_END    (4)
#define ABB_TX_CH0_4G_DIG_2_dem_dwa_en_4g_START     (5)
#define ABB_TX_CH0_4G_DIG_2_dem_dwa_en_4g_END       (5)
#define ABB_TX_CH0_4G_DIG_2_dem_lsb_bp_4g_START     (6)
#define ABB_TX_CH0_4G_DIG_2_dem_lsb_bp_4g_END       (6)
#define ABB_TX_CH0_4G_DIG_2_dem_msb_bp_4g_START     (7)
#define ABB_TX_CH0_4G_DIG_2_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_4G_DIG_3_UNION
 结构说明  : tx_ch0_4g_dig_3 寄存器结构定义。地址偏移量:0xE，初值:0x00，宽度:8
 寄存器说明: CH0 TX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_cfr_bp_4g   : 1;  /* bit[0]  : TX通道CFR bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_flush_en_4g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  reserved       : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_3_UNION;
#define ABB_TX_CH0_4G_DIG_3_tx_cfr_bp_4g_START    (0)
#define ABB_TX_CH0_4G_DIG_3_tx_cfr_bp_4g_END      (0)
#define ABB_TX_CH0_4G_DIG_3_tx_flush_en_4g_START  (1)
#define ABB_TX_CH0_4G_DIG_3_tx_flush_en_4g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_1_UNION
 结构说明  : rx_tds_dig_1 寄存器结构定义。地址偏移量:0xF，初值:0x24，宽度:8
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
                                                             001：3G_SCReserved */
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
 结构说明  : rx_tds_dig_2 寄存器结构定义。地址偏移量:0x10，初值:0x53，宽度:8
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
        unsigned long  tx_cfr_bp_tds   : 1;  /* bit[0]  : TX通道CFR bypass控制：
                                                          0：不bypass
                                                          1：bypass(默认) */
        unsigned long  tx_flush_en_tds : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                          0：不使能
                                                          1：使能 */
        unsigned long  reserved        : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_START    (0)
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_END      (0)
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_START  (1)
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_END    (1)


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
                                                           Reserved */
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
        unsigned long  tx_cfr_bp_idle   : 1;  /* bit[0]  : TX通道CFR bypass控制：
                                                           0：不bypass
                                                           1：bypass(默认) */
        unsigned long  tx_flush_en_idle : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                           0：不使能
                                                           1：使能 */
        unsigned long  reserved         : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_START    (0)
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_END      (0)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_1_UNION
 结构说明  : rx_2g_ana_1 寄存器结构定义。地址偏移量:0x24，初值:0xF6，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_2G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000：DWA
                                                         001：CLA1
                                                         010：CLA2
                                                         011：CLA3
                                                         100：CLA4
                                                         101：CLA5
                                                         110：CLA6
                                                         111：CLA7 */
        unsigned long  RX_MODE_CLK_2G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
                                                         000：4G
                                                         001：3G
                                                         010：3G_DC &amp; TDS
                                                         011：2G(默认)
                                                         100：reserved
                                                         101：CDMA */
        unsigned long  DEM_MOD_B1_2G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000：DWA
                                                         001：CLA1
                                                         010：CLA2
                                                         011：CLA3
                                                         100：CLA4
                                                         101：CLA5
                                                         110：CLA6
                                                         111：CLA7 */
        unsigned long  RXB_Q_PD_2G    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_2G    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_2G    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_2G    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_1_UNION;
#define ABB_RX_2G_ANA_1_DEM_MOD_B0_2G_START   (0)
#define ABB_RX_2G_ANA_1_DEM_MOD_B0_2G_END     (0)
#define ABB_RX_2G_ANA_1_RX_MODE_CLK_2G_START  (1)
#define ABB_RX_2G_ANA_1_RX_MODE_CLK_2G_END    (2)
#define ABB_RX_2G_ANA_1_DEM_MOD_B1_2G_START   (3)
#define ABB_RX_2G_ANA_1_DEM_MOD_B1_2G_END     (3)
#define ABB_RX_2G_ANA_1_RXB_Q_PD_2G_START     (4)
#define ABB_RX_2G_ANA_1_RXB_Q_PD_2G_END       (4)
#define ABB_RX_2G_ANA_1_RXB_I_PD_2G_START     (5)
#define ABB_RX_2G_ANA_1_RXB_I_PD_2G_END       (5)
#define ABB_RX_2G_ANA_1_RXA_Q_PD_2G_START     (6)
#define ABB_RX_2G_ANA_1_RXA_Q_PD_2G_END       (6)
#define ABB_RX_2G_ANA_1_RXA_I_PD_2G_START     (7)
#define ABB_RX_2G_ANA_1_RXA_I_PD_2G_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_2_UNION
 结构说明  : rx_2g_ana_2 寄存器结构定义。地址偏移量:0x25，初值:0x00，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_2G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1： CA mode
                                                       0： others */
        unsigned long  reserved     : 1;  /* bit[1]  : Reserved */
        unsigned long  IBCT_QT_2G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_2G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_2G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_2_UNION;
#define ABB_RX_2G_ANA_2_RX_MODE_C_2G_START  (0)
#define ABB_RX_2G_ANA_2_RX_MODE_C_2G_END    (0)
#define ABB_RX_2G_ANA_2_IBCT_QT_2G_START    (2)
#define ABB_RX_2G_ANA_2_IBCT_QT_2G_END      (3)
#define ABB_RX_2G_ANA_2_IBCT_OP3_2G_START   (4)
#define ABB_RX_2G_ANA_2_IBCT_OP3_2G_END     (5)
#define ABB_RX_2G_ANA_2_IBCT_OP1_2G_START   (6)
#define ABB_RX_2G_ANA_2_IBCT_OP1_2G_END     (7)


/*****************************************************************************
 结构名    : ABB_TX_2G_ANA_1_UNION
 结构说明  : tx_2g_ana_1 寄存器结构定义。地址偏移量:0x26，初值:0x1F，宽度:8
 寄存器说明: TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_2G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
                                                         000：4G
                                                         001：3G &amp; TDS
                                                         010：reserved
                                                         011：2G(默认)
                                                         1xx：CDMA */
        unsigned long  TX_Q_PD_A_2G   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_2G   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_2G : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                         00：1分频
                                                         01：2分频(默认)
                                                         10：3分频
                                                         11：4分频 */
        unsigned long  FC             : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                         00：5MHz(默认)WSC&amp;GSM&amp;CDMA
                                                         01：10MHz WDC
                                                         10：Reserved
                                                         11：20MHz LTE */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_1_UNION;
#define ABB_TX_2G_ANA_1_TX_MODE_CLK_2G_START  (0)
#define ABB_TX_2G_ANA_1_TX_MODE_CLK_2G_END    (1)
#define ABB_TX_2G_ANA_1_TX_Q_PD_A_2G_START    (2)
#define ABB_TX_2G_ANA_1_TX_Q_PD_A_2G_END      (2)
#define ABB_TX_2G_ANA_1_TX_I_PD_A_2G_START    (3)
#define ABB_TX_2G_ANA_1_TX_I_PD_A_2G_END      (3)
#define ABB_TX_2G_ANA_1_TX_DIV_MODE_2G_START  (4)
#define ABB_TX_2G_ANA_1_TX_DIV_MODE_2G_END    (5)
#define ABB_TX_2G_ANA_1_FC_START              (6)
#define ABB_TX_2G_ANA_1_FC_END                (7)


/*****************************************************************************
 结构名    : ABB_TX_2G_ANA_2_UNION
 结构说明  : tx_2g_ana_2 寄存器结构定义。地址偏移量:0x27，初值:0x1A，宽度:8
 寄存器说明: TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr49。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_2G : 2;  /* bit[0-1]: LPF OP1 电流模式调整
                                                              bit0：
                                                              0： 输出级电流正常
                                                              1： 输出级电流加大（适用于5uA偏置）
                                                              bit1：
                                                              0： miller补偿电容正常
                                                              1： miller补偿电容变大（适用于2.5uA偏置）
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_2G : 2;  /* bit[2-3]: LPF OP2 电流模式调整
                                                              00 输出级电流正常
                                                              01 输出级电流加大（适用于5uA偏置）
                                                              10 不建议使用
                                                              11 输出级电流再加大（适用于2.5uA偏置）
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_2G : 2;  /* bit[4-5]: LPF 运放偏置电流调整
                                                              运放电流：   op1   op2
                                                              00：         10u   10u
                                                              01：         5u    5u
                                                              10：         2.5u  5u
                                                              11：         2.5u  2.5u
                                                              LTE:00
                                                              Others:01 */
        unsigned long  reserved            : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_2G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_2_UNION;
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP1_2G_START  (0)
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP1_2G_END    (1)
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP2_2G_START  (2)
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP2_2G_END    (3)
#define ABB_TX_2G_ANA_2_LPF_MODE_CURRENT_2G_START  (4)
#define ABB_TX_2G_ANA_2_LPF_MODE_CURRENT_2G_END    (5)
#define ABB_TX_2G_ANA_2_TX_MODE_CLK_B3_2G_START    (7)
#define ABB_TX_2G_ANA_2_TX_MODE_CLK_B3_2G_END      (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_3G_ANA_1_UNION
 结构说明  : rx_ch0_3g_ana_1 寄存器结构定义。地址偏移量:0x28，初值:0xF2，宽度:8
 寄存器说明: CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_3G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000：DWA
                                                         001：CLA1
                                                         010：CLA2
                                                         011：CLA3
                                                         100：CLA4
                                                         101：CLA5
                                                         110：CLA6
                                                         111：CLA7 */
        unsigned long  RX_MODE_CLK_3G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
                                                         000：4G
                                                         001：3G
                                                         010：3G_DC &amp; TDS
                                                         011：2G(默认)
                                                         100：reserved
                                                         101：CDMA */
        unsigned long  DEM_MOD_B1_3G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000：DWA
                                                         001：CLA1
                                                         010：CLA2
                                                         011：CLA3
                                                         100：CLA4
                                                         101：CLA5
                                                         110：CLA6
                                                         111：CLA7 */
        unsigned long  RXB_Q_PD_3G    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_3G    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_3G    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_3G    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_1_UNION;
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B0_3G_START   (0)
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B0_3G_END     (0)
#define ABB_RX_CH0_3G_ANA_1_RX_MODE_CLK_3G_START  (1)
#define ABB_RX_CH0_3G_ANA_1_RX_MODE_CLK_3G_END    (2)
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B1_3G_START   (3)
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B1_3G_END     (3)
#define ABB_RX_CH0_3G_ANA_1_RXB_Q_PD_3G_START     (4)
#define ABB_RX_CH0_3G_ANA_1_RXB_Q_PD_3G_END       (4)
#define ABB_RX_CH0_3G_ANA_1_RXB_I_PD_3G_START     (5)
#define ABB_RX_CH0_3G_ANA_1_RXB_I_PD_3G_END       (5)
#define ABB_RX_CH0_3G_ANA_1_RXA_Q_PD_3G_START     (6)
#define ABB_RX_CH0_3G_ANA_1_RXA_Q_PD_3G_END       (6)
#define ABB_RX_CH0_3G_ANA_1_RXA_I_PD_3G_START     (7)
#define ABB_RX_CH0_3G_ANA_1_RXA_I_PD_3G_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_3G_ANA_2_UNION
 结构说明  : rx_ch0_3g_ana_2 寄存器结构定义。地址偏移量:0x29，初值:0x0，宽度:8
 寄存器说明: RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_3G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1： CA mode
                                                       0： others */
        unsigned long  reserved     : 1;  /* bit[1]  : Reserved */
        unsigned long  IBCT_QT_3G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_3G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_3G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_2_UNION;
#define ABB_RX_CH0_3G_ANA_2_RX_MODE_C_3G_START  (0)
#define ABB_RX_CH0_3G_ANA_2_RX_MODE_C_3G_END    (0)
#define ABB_RX_CH0_3G_ANA_2_IBCT_QT_3G_START    (2)
#define ABB_RX_CH0_3G_ANA_2_IBCT_QT_3G_END      (3)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP3_3G_START   (4)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP3_3G_END     (5)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP1_3G_START   (6)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP1_3G_END     (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_3G_ANA_1_UNION
 结构说明  : tx_ch0_3g_ana_1 寄存器结构定义。地址偏移量:0x2A，初值:0x1D，宽度:8
 寄存器说明: CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_3G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
                                                         000：4G &amp; ET &amp; APT
                                                         001：3G &amp; TDS */
        unsigned long  TX_Q_PD_A_3G   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_3G   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_3G : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                         00：1分频
                                                         01：2分频(默认)
                                                         10：3分频
                                                         11：4分频 */
        unsigned long  FC_3G          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                         00：5MHz(默认)WSC&amp;GSM&amp;CDMA
                                                         01：10MHz WDC
                                                         10：Reserved
                                                         11：20MHz LTE */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_ANA_1_UNION;
#define ABB_TX_CH0_3G_ANA_1_TX_MODE_CLK_3G_START  (0)
#define ABB_TX_CH0_3G_ANA_1_TX_MODE_CLK_3G_END    (1)
#define ABB_TX_CH0_3G_ANA_1_TX_Q_PD_A_3G_START    (2)
#define ABB_TX_CH0_3G_ANA_1_TX_Q_PD_A_3G_END      (2)
#define ABB_TX_CH0_3G_ANA_1_TX_I_PD_A_3G_START    (3)
#define ABB_TX_CH0_3G_ANA_1_TX_I_PD_A_3G_END      (3)
#define ABB_TX_CH0_3G_ANA_1_TX_DIV_MODE_3G_START  (4)
#define ABB_TX_CH0_3G_ANA_1_TX_DIV_MODE_3G_END    (5)
#define ABB_TX_CH0_3G_ANA_1_FC_3G_START           (6)
#define ABB_TX_CH0_3G_ANA_1_FC_3G_END             (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_3G_ANA_2_UNION
 结构说明  : tx_ch0_3g_ana_2 寄存器结构定义。地址偏移量:0x2B，初值:0x15，宽度:8
 寄存器说明: CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr49。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_3G : 2;  /* bit[0-1]: LPF OP1 电流模式调整
                                                              bit0：
                                                              0： 输出级电流正常
                                                              1： 输出级电流加大（适用于5uA偏置）
                                                              bit1：
                                                              0： miller补偿电容正常
                                                              1： miller补偿电容变大（适用于2.5uA偏置）
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_3G : 2;  /* bit[2-3]: LPF OP2 电流模式调整
                                                              00 输出级电流正常
                                                              01 输出级电流加大（适用于5uA偏置）
                                                              10 不建议使用
                                                              11 输出级电流再加大（适用于2.5uA偏置）
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_3G : 2;  /* bit[4-5]: LPF 运放偏置电流调整
                                                              运放电流：   op1   op2
                                                              00：         10u   10u
                                                              01：         5u    5u
                                                              10：         2.5u  5u
                                                              11：         2.5u  2.5u
                                                              LTE:00
                                                              Others:01 */
        unsigned long  reserved            : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_3G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_ANA_2_UNION;
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP1_3G_START  (0)
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP1_3G_END    (1)
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP2_3G_START  (2)
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP2_3G_END    (3)
#define ABB_TX_CH0_3G_ANA_2_LPF_MODE_CURRENT_3G_START  (4)
#define ABB_TX_CH0_3G_ANA_2_LPF_MODE_CURRENT_3G_END    (5)
#define ABB_TX_CH0_3G_ANA_2_TX_MODE_CLK_B3_3G_START    (7)
#define ABB_TX_CH0_3G_ANA_2_TX_MODE_CLK_B3_3G_END      (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_ANA_1_UNION
 结构说明  : rx_ch0_4g_ana_1 寄存器结构定义。地址偏移量:0x2C，初值:0xF0，宽度:8
 寄存器说明: CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_4G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000：DWA
                                                         001：CLA1
                                                         010：CLA2
                                                         011：CLA3
                                                         100：CLA4
                                                         101：CLA5
                                                         110：CLA6
                                                         111：CLA7 */
        unsigned long  RX_MODE_CLK_4G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
                                                         000：4G
                                                         001：3G
                                                         010：3G_DC &amp; TDS
                                                         011：2G(默认)
                                                         100：reserved
                                                         101：CDMA */
        unsigned long  DEM_MOD_B1_4G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000：DWA
                                                         001：CLA1
                                                         010：CLA2
                                                         011：CLA3
                                                         100：CLA4
                                                         101：CLA5
                                                         110：CLA6
                                                         111：CLA7 */
        unsigned long  RXB_Q_PD_4G    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_4G    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_4G    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_4G    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_1_UNION;
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B0_4G_START   (0)
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B0_4G_END     (0)
#define ABB_RX_CH0_4G_ANA_1_RX_MODE_CLK_4G_START  (1)
#define ABB_RX_CH0_4G_ANA_1_RX_MODE_CLK_4G_END    (2)
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B1_4G_START   (3)
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B1_4G_END     (3)
#define ABB_RX_CH0_4G_ANA_1_RXB_Q_PD_4G_START     (4)
#define ABB_RX_CH0_4G_ANA_1_RXB_Q_PD_4G_END       (4)
#define ABB_RX_CH0_4G_ANA_1_RXB_I_PD_4G_START     (5)
#define ABB_RX_CH0_4G_ANA_1_RXB_I_PD_4G_END       (5)
#define ABB_RX_CH0_4G_ANA_1_RXA_Q_PD_4G_START     (6)
#define ABB_RX_CH0_4G_ANA_1_RXA_Q_PD_4G_END       (6)
#define ABB_RX_CH0_4G_ANA_1_RXA_I_PD_4G_START     (7)
#define ABB_RX_CH0_4G_ANA_1_RXA_I_PD_4G_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_ANA_2_UNION
 结构说明  : rx_ch0_4g_ana_2 寄存器结构定义。地址偏移量:0x2D，初值:0xA8，宽度:8
 寄存器说明: RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_4G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1： CA mode
                                                       0： others */
        unsigned long  reserved     : 1;  /* bit[1]  : Reserved */
        unsigned long  IBCT_QT_4G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_4G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_4G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_2_UNION;
#define ABB_RX_CH0_4G_ANA_2_RX_MODE_C_4G_START  (0)
#define ABB_RX_CH0_4G_ANA_2_RX_MODE_C_4G_END    (0)
#define ABB_RX_CH0_4G_ANA_2_IBCT_QT_4G_START    (2)
#define ABB_RX_CH0_4G_ANA_2_IBCT_QT_4G_END      (3)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP3_4G_START   (4)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP3_4G_END     (5)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP1_4G_START   (6)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP1_4G_END     (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_4G_ANA_1_UNION
 结构说明  : tx_ch0_4g_ana_1 寄存器结构定义。地址偏移量:0x2E，初值:0xCC，宽度:8
 寄存器说明: CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_4G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
                                                         000：4G &amp; ET &amp; APT
                                                         001：3G &amp; TDS
                                                         010：CA
                                                         011：2G(默认)
                                                         1xx：CDMA */
        unsigned long  TX_Q_PD_A_4G   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_4G   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_4G : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                         00：1分频
                                                         01：2分频(默认)
                                                         10：3分频
                                                         11：4分频 */
        unsigned long  FC_4G          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                         00：5MHz(默认)WSC&amp;GSM&amp;CDMA
                                                         01：10MHz WDC
                                                         10：Reserved
                                                         11：20MHz LTE */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_ANA_1_UNION;
#define ABB_TX_CH0_4G_ANA_1_TX_MODE_CLK_4G_START  (0)
#define ABB_TX_CH0_4G_ANA_1_TX_MODE_CLK_4G_END    (1)
#define ABB_TX_CH0_4G_ANA_1_TX_Q_PD_A_4G_START    (2)
#define ABB_TX_CH0_4G_ANA_1_TX_Q_PD_A_4G_END      (2)
#define ABB_TX_CH0_4G_ANA_1_TX_I_PD_A_4G_START    (3)
#define ABB_TX_CH0_4G_ANA_1_TX_I_PD_A_4G_END      (3)
#define ABB_TX_CH0_4G_ANA_1_TX_DIV_MODE_4G_START  (4)
#define ABB_TX_CH0_4G_ANA_1_TX_DIV_MODE_4G_END    (5)
#define ABB_TX_CH0_4G_ANA_1_FC_4G_START           (6)
#define ABB_TX_CH0_4G_ANA_1_FC_4G_END             (7)


/*****************************************************************************
 结构名    : ABB_TX_CH0_4G_ANA_2_UNION
 结构说明  : tx_ch0_4g_ana_2 寄存器结构定义。地址偏移量:0x2F，初值:0x0，宽度:8
 寄存器说明: CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr49。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_4G : 2;  /* bit[0-1]: LPF OP1 电流模式调整
                                                              bit0：
                                                              0： 输出级电流正常
                                                              1： 输出级电流加大（适用于5uA偏置）
                                                              bit1：
                                                              0： miller补偿电容正常
                                                              1： miller补偿电容变大（适用于2.5uA偏置）
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_4G : 2;  /* bit[2-3]: LPF OP2 电流模式调整
                                                              00 输出级电流正常
                                                              01 输出级电流加大（适用于5uA偏置）
                                                              10 不建议使用
                                                              11 输出级电流再加大（适用于2.5uA偏置）
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_4G : 2;  /* bit[4-5]: LPF 运放偏置电流调整
                                                              运放电流：   op1   op2
                                                              00：         10u   10u
                                                              01：         5u    5u
                                                              10：         2.5u  5u
                                                              11：         2.5u  2.5u
                                                              LTE:00
                                                              Others:01 */
        unsigned long  reserved            : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_4G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_ANA_2_UNION;
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP1_4G_START  (0)
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP1_4G_END    (1)
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP2_4G_START  (2)
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP2_4G_END    (3)
#define ABB_TX_CH0_4G_ANA_2_LPF_MODE_CURRENT_4G_START  (4)
#define ABB_TX_CH0_4G_ANA_2_LPF_MODE_CURRENT_4G_END    (5)
#define ABB_TX_CH0_4G_ANA_2_TX_MODE_CLK_B3_4G_START    (7)
#define ABB_TX_CH0_4G_ANA_2_TX_MODE_CLK_B3_4G_END      (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_1_UNION
 结构说明  : rx_tds_ana_1 寄存器结构定义。地址偏移量:0x30，初值:0xF2，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_TDS  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                          000：DWA
                                                          001：CLA1
                                                          010：CLA2
                                                          011：CLA3
                                                          100：CLA4
                                                          101：CLA5
                                                          110：CLA6
                                                          111：CLA7 */
        unsigned long  RX_MODE_CLK_TDS : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
                                                          000：4G
                                                          001：3G
                                                          010：3G_DC &amp; TDS
                                                          011：2G(默认)
                                                          100：reserved
                                                          101：CDMA */
        unsigned long  DEM_MOD_B1_TDS  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                          000：DWA
                                                          001：CLA1
                                                          010：CLA2
                                                          011：CLA3
                                                          100：CLA4
                                                          101：CLA5
                                                          110：CLA6
                                                          111：CLA7 */
        unsigned long  RXB_Q_PD_TDS    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                          0：Power On
                                                          1：Power Down(默认)
                                                          (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_TDS    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                          0：Power On
                                                          1：Power Down(默认)
                                                          (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_TDS    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                          0：Power On
                                                          1：Power Down(默认)
                                                          (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_TDS    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                          0：Power On
                                                          1：Power Down(默认)
                                                          (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_1_UNION;
#define ABB_RX_TDS_ANA_1_DEM_MOD_B0_TDS_START   (0)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B0_TDS_END     (0)
#define ABB_RX_TDS_ANA_1_RX_MODE_CLK_TDS_START  (1)
#define ABB_RX_TDS_ANA_1_RX_MODE_CLK_TDS_END    (2)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B1_TDS_START   (3)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B1_TDS_END     (3)
#define ABB_RX_TDS_ANA_1_RXB_Q_PD_TDS_START     (4)
#define ABB_RX_TDS_ANA_1_RXB_Q_PD_TDS_END       (4)
#define ABB_RX_TDS_ANA_1_RXB_I_PD_TDS_START     (5)
#define ABB_RX_TDS_ANA_1_RXB_I_PD_TDS_END       (5)
#define ABB_RX_TDS_ANA_1_RXA_Q_PD_TDS_START     (6)
#define ABB_RX_TDS_ANA_1_RXA_Q_PD_TDS_END       (6)
#define ABB_RX_TDS_ANA_1_RXA_I_PD_TDS_START     (7)
#define ABB_RX_TDS_ANA_1_RXA_I_PD_TDS_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_2_UNION
 结构说明  : rx_tds_ana_2 寄存器结构定义。地址偏移量:0x31，初值:0x00，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr01。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_TDS : 1;  /* bit[0]  : Mode setting for ADC
                                                        1： CA mode
                                                        0： others */
        unsigned long  reserved      : 1;  /* bit[1]  : Reserved */
        unsigned long  IBCT_QT_TDS   : 2;  /* bit[2-3]: Current Seting For Mode
                                                        1x：LTE mode Current
                                                        01：3G_DC &amp; X mode Current
                                                        00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_TDS  : 2;  /* bit[4-5]: Current Seting For Mode
                                                        1x：LTE mode Current
                                                        01：3G_DC &amp; X mode Current
                                                        00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_TDS  : 2;  /* bit[6-7]: Current Seting For Mode
                                                        1x：LTE mode Current
                                                        01：3G_DC &amp; X mode Current
                                                        00：3G &amp; 2G mode Current */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_2_UNION;
#define ABB_RX_TDS_ANA_2_RX_MODE_C_TDS_START  (0)
#define ABB_RX_TDS_ANA_2_RX_MODE_C_TDS_END    (0)
#define ABB_RX_TDS_ANA_2_IBCT_QT_TDS_START    (2)
#define ABB_RX_TDS_ANA_2_IBCT_QT_TDS_END      (3)
#define ABB_RX_TDS_ANA_2_IBCT_OP3_TDS_START   (4)
#define ABB_RX_TDS_ANA_2_IBCT_OP3_TDS_END     (5)
#define ABB_RX_TDS_ANA_2_IBCT_OP1_TDS_START   (6)
#define ABB_RX_TDS_ANA_2_IBCT_OP1_TDS_END     (7)


/*****************************************************************************
 结构名    : ABB_TX_TDS_ANA_1_UNION
 结构说明  : tx_tds_ana_1 寄存器结构定义。地址偏移量:0x32，初值:0x5D，宽度:8
 寄存器说明: TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_TDS : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
                                                          000：4G
                                                          001：3G &amp; TDS
                                                          010：CA
                                                          011：2G(默认)
                                                          1xx：CDMA */
        unsigned long  TX_Q_PD_A_TDS   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                          0：Power On
                                                          1：Power Down(默认)
                                                          (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_TDS   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                          0：Power On
                                                          1：Power Down(默认)
                                                          (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_TDS : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                          00：1分频
                                                          01：2分频(默认)
                                                          10：3分频
                                                          11：4分频 */
        unsigned long  FC_TDS          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                          00：5MHz(默认)WSC&amp;GSM&amp;CDMA
                                                          01：10MHz WDC
                                                          10：Reserved
                                                          11：20MHz LTE */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_1_UNION;
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_START  (0)
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_END    (1)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_START    (2)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_END      (2)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_START    (3)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_END      (3)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_START  (4)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_END    (5)
#define ABB_TX_TDS_ANA_1_FC_TDS_START           (6)
#define ABB_TX_TDS_ANA_1_FC_TDS_END             (7)


/*****************************************************************************
 结构名    : ABB_TX_TDS_ANA_2_UNION
 结构说明  : tx_tds_ana_2 寄存器结构定义。地址偏移量:0x33，初值:0x15，宽度:8
 寄存器说明: TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr49。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_TDS : 2;  /* bit[0-1]: LPF OP1 电流模式调整
                                                               bit0：
                                                               0： 输出级电流正常
                                                               1： 输出级电流加大（适用于5uA偏置）
                                                               bit1：
                                                               0： miller补偿电容正常
                                                               1： miller补偿电容变大（适用于2.5uA偏置）
                                                               LTE:00
                                                               WDC:01
                                                               SC:01
                                                               CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_TDS : 2;  /* bit[2-3]: LPF OP2 电流模式调整
                                                               00 输出级电流正常
                                                               01 输出级电流加大（适用于5uA偏置）
                                                               10 不建议使用
                                                               11 输出级电流再加大（适用于2.5uA偏置）
                                                               LTE:00
                                                               WDC:01
                                                               SC:01
                                                               CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_TDS         : 2;  /* bit[4-5]: LPF 运放偏置电流调整
                                                               运放电流：   op1   op2
                                                               00：         10u   10u
                                                               01：         5u    5u
                                                               10：         2.5u  5u
                                                               11：         2.5u  2.5u
                                                               LTE:00
                                                               Others:01 */
        unsigned long  reserved             : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_TDS   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。 */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_2_UNION;
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP1_TDS_START  (0)
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP1_TDS_END    (1)
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP2_TDS_START  (2)
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP2_TDS_END    (3)
#define ABB_TX_TDS_ANA_2_LPF_MODE_TDS_START          (4)
#define ABB_TX_TDS_ANA_2_LPF_MODE_TDS_END            (5)
#define ABB_TX_TDS_ANA_2_TX_MODE_CLK_B3_TDS_START    (7)
#define ABB_TX_TDS_ANA_2_TX_MODE_CLK_B3_TDS_END      (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_1_UNION
 结构说明  : rx_idle_ana_1 寄存器结构定义。地址偏移量:0x3C，初值:0xF6，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_IDLE  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                           000：DWA
                                                           001：CLA1
                                                           010：CLA2
                                                           011：CLA3
                                                           100：CLA4
                                                           101：CLA5
                                                           110：CLA6
                                                           111：CLA7 */
        unsigned long  RX_MODE_CLK_IDLE : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
                                                           000：4G
                                                           001：3G
                                                           010：3G_DC &amp; TDS
                                                           011：2G(默认)
                                                           100：reserved
                                                           101：CDMA */
        unsigned long  DEM_MOD_B1_IDLE  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                           000：DWA
                                                           001：CLA1
                                                           010：CLA2
                                                           011：CLA3
                                                           100：CLA4
                                                           101：CLA5
                                                           110：CLA6
                                                           111：CLA7 */
        unsigned long  RXB_Q_PD_IDLE    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                           0：Power On
                                                           1：Power Down(默认)
                                                           (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_IDLE    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                           0：Power On
                                                           1：Power Down(默认)
                                                           (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_IDLE    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                           0：Power On
                                                           1：Power Down(默认)
                                                           (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_IDLE    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                           0：Power On
                                                           1：Power Down(默认)
                                                           (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_1_UNION;
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B0_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B0_IDLE_END     (0)
#define ABB_RX_IDLE_ANA_1_RX_MODE_CLK_IDLE_START  (1)
#define ABB_RX_IDLE_ANA_1_RX_MODE_CLK_IDLE_END    (2)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B1_IDLE_START   (3)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B1_IDLE_END     (3)
#define ABB_RX_IDLE_ANA_1_RXB_Q_PD_IDLE_START     (4)
#define ABB_RX_IDLE_ANA_1_RXB_Q_PD_IDLE_END       (4)
#define ABB_RX_IDLE_ANA_1_RXB_I_PD_IDLE_START     (5)
#define ABB_RX_IDLE_ANA_1_RXB_I_PD_IDLE_END       (5)
#define ABB_RX_IDLE_ANA_1_RXA_Q_PD_IDLE_START     (6)
#define ABB_RX_IDLE_ANA_1_RXA_Q_PD_IDLE_END       (6)
#define ABB_RX_IDLE_ANA_1_RXA_I_PD_IDLE_START     (7)
#define ABB_RX_IDLE_ANA_1_RXA_I_PD_IDLE_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_2_UNION
 结构说明  : rx_idle_ana_2 寄存器结构定义。地址偏移量:0x3D，初值:0x00，宽度:8
 寄存器说明: IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr01。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_IDLE : 1;  /* bit[0]  : Mode setting for ADC
                                                         1： CA mode
                                                         0： others */
        unsigned long  reserved       : 1;  /* bit[1]  : Reserved */
        unsigned long  IBCT_QT_IDLE   : 2;  /* bit[2-3]: Current Seting For Mode
                                                         1x：LTE mode Current
                                                         01：3G_DC &amp; X mode Current
                                                         00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_IDLE  : 2;  /* bit[4-5]: Current Seting For Mode
                                                         1x：LTE mode Current
                                                         01：3G_DC &amp; X mode Current
                                                         00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_IDLE  : 2;  /* bit[6-7]: Current Seting For Mode
                                                         1x：LTE mode Current
                                                         01：3G_DC &amp; X mode Current
                                                         00：3G &amp; 2G mode Current */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_2_UNION;
#define ABB_RX_IDLE_ANA_2_RX_MODE_C_IDLE_START  (0)
#define ABB_RX_IDLE_ANA_2_RX_MODE_C_IDLE_END    (0)
#define ABB_RX_IDLE_ANA_2_IBCT_QT_IDLE_START    (2)
#define ABB_RX_IDLE_ANA_2_IBCT_QT_IDLE_END      (3)
#define ABB_RX_IDLE_ANA_2_IBCT_OP3_IDLE_START   (4)
#define ABB_RX_IDLE_ANA_2_IBCT_OP3_IDLE_END     (5)
#define ABB_RX_IDLE_ANA_2_IBCT_OP1_IDLE_START   (6)
#define ABB_RX_IDLE_ANA_2_IBCT_OP1_IDLE_END     (7)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_ANA_1_UNION
 结构说明  : tx_idle_ana_1 寄存器结构定义。地址偏移量:0x3E，初值:0x1F，宽度:8
 寄存器说明: TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_IDLE : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
                                                           000：4G &amp; ET &amp; APT
                                                           001：3G &amp; TDS
                                                           010：CA
                                                           011：2G(默认)
                                                           1xx：CDMA */
        unsigned long  TX_Q_PD_A_IDLE   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                           0：Power On
                                                           1：Power Down(默认)
                                                           (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_IDLE   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                           0：Power On
                                                           1：Power Down(默认)
                                                           (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_IDLE : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                           00：1分频
                                                           01：2分频(默认)
                                                           10：3分频
                                                           11：4分频 */
        unsigned long  FC_IDLE          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                           00：5MHz(默认)WSC&amp;GSM&amp;CDMA
                                                           01：10MHz WDC
                                                           10：Reserved
                                                           11：20MHz LTE */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_1_UNION;
#define ABB_TX_IDLE_ANA_1_TX_MODE_CLK_IDLE_START  (0)
#define ABB_TX_IDLE_ANA_1_TX_MODE_CLK_IDLE_END    (1)
#define ABB_TX_IDLE_ANA_1_TX_Q_PD_A_IDLE_START    (2)
#define ABB_TX_IDLE_ANA_1_TX_Q_PD_A_IDLE_END      (2)
#define ABB_TX_IDLE_ANA_1_TX_I_PD_A_IDLE_START    (3)
#define ABB_TX_IDLE_ANA_1_TX_I_PD_A_IDLE_END      (3)
#define ABB_TX_IDLE_ANA_1_TX_DIV_MODE_IDLE_START  (4)
#define ABB_TX_IDLE_ANA_1_TX_DIV_MODE_IDLE_END    (5)
#define ABB_TX_IDLE_ANA_1_FC_IDLE_START           (6)
#define ABB_TX_IDLE_ANA_1_FC_IDLE_END             (7)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_ANA_2_UNION
 结构说明  : tx_idle_ana_2 寄存器结构定义。地址偏移量:0x3F，初值:0x1A，宽度:8
 寄存器说明: TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr49。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_IDLE : 2;  /* bit[0-1]: LPF OP1 电流模式调整
                                                                bit0：
                                                                0： 输出级电流正常
                                                                1： 输出级电流加大（适用于5uA偏置）
                                                                bit1：
                                                                0： miller补偿电容正常
                                                                1： miller补偿电容变大（适用于2.5uA偏置）
                                                                LTE:00
                                                                WDC:01
                                                                SC:01
                                                                CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_IDLE : 2;  /* bit[2-3]: LPF OP2 电流模式调整
                                                                00 输出级电流正常
                                                                01 输出级电流加大（适用于5uA偏置）
                                                                10 不建议使用
                                                                11 输出级电流再加大（适用于2.5uA偏置）
                                                                LTE:00
                                                                WDC:01
                                                                SC:01
                                                                CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_IDLE : 2;  /* bit[4-5]: LPF 运放偏置电流调整
                                                                运放电流：   op1   op2
                                                                00：         10u   10u
                                                                01：         5u    5u
                                                                10：         2.5u  5u
                                                                11：         2.5u  2.5u
                                                                LTE:00
                                                                Others:01 */
        unsigned long  reserved              : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_IDLE   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_2_UNION;
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP1_IDLE_START  (0)
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP1_IDLE_END    (1)
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP2_IDLE_START  (2)
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP2_IDLE_END    (3)
#define ABB_TX_IDLE_ANA_2_LPF_MODE_CURRENT_IDLE_START  (4)
#define ABB_TX_IDLE_ANA_2_LPF_MODE_CURRENT_IDLE_END    (5)
#define ABB_TX_IDLE_ANA_2_TX_MODE_CLK_B3_IDLE_START    (7)
#define ABB_TX_IDLE_ANA_2_TX_MODE_CLK_B3_IDLE_END      (7)


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
 结构名    : ABB_CH0_CFR_CTRL_UNION
 结构说明  : ch0_cfr_ctrl 寄存器结构定义。地址偏移量:0xA3，初值:0x44，宽度:8
 寄存器说明: CFR峰值检测窗长寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfr_pdet_sel : 2;  /* bit[0-1]: CFR峰值检测方式：
                                                           00：单点提峰
                                                           01：区间提峰
                                                           10：滑窗提峰
                                                           11：全部峰值 */
        unsigned long  ch0_cfr_fir_sel  : 1;  /* bit[2]  : CFR滤波器选择：
                                                           0：bypass滤波器
                                                           1：不bypass滤波器 */
        unsigned long  reserved         : 1;  /* bit[3]  : Reserved */
        unsigned long  ch0_cfr_fir_fac  : 4;  /* bit[4-7]: CFR削波因子 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CFR_CTRL_UNION;
#define ABB_CH0_CFR_CTRL_ch0_cfr_pdet_sel_START  (0)
#define ABB_CH0_CFR_CTRL_ch0_cfr_pdet_sel_END    (1)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_sel_START   (2)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_sel_END     (2)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_fac_START   (4)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_fac_END     (7)


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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved               : 6;  /* bit[2-7]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
        unsigned long  ch0_rxb_dc_q_2 : 4;  /* bit[4-7]: RXB天线Q路信号BLOCKING DC上报值低4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DC_Q_2_UNION;
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_START  (4)
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_DIG0_UNION
 结构说明  : ch0_reg_debug_dig0 寄存器结构定义。地址偏移量:0xCB，初值:0x24，宽度:8
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
        unsigned long  ch0_sdm_sel       : 1;  /* bit[6]  : TX通道调制器选择：comstarV520 Reserved
                                                            0：5阶调制器(for V510)
                                                            1：1阶调制器(for V511) */
        unsigned long  reserved          : 1;  /* bit[7]  : Reserved */
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
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_sel_START        (6)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_sel_END          (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR02_UNION
 结构说明  : ch0_reg_analog_wr02 寄存器结构定义。地址偏移量:0xD0，初值:0x0F，宽度:8
 寄存器说明: Power Down控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RXC_Q_PD   : 1;  /* bit[0]  : RXC_Q ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXA_Q_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1时工作，否则关闭
                                                         ComstarV511_Reserved */
        unsigned long  CH0_RXC_I_PD   : 1;  /* bit[1]  : RXC_I ADC Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认)
                                                         (!RXA_I_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1时工作，否则关闭
                                                         ComstarV511_Reserved */
        unsigned long  CH0_PLL624_PD  : 1;  /* bit[2]  : GPLL Power Down控制
                                                         0：Power On
                                                         1：Power Down(默认) */
        unsigned long  CH0_PLL6144_PD : 1;  /* bit[3]  : WPLL Power Down控制
                                                         0：Power On(默认)
                                                         1：Power Down */
        unsigned long  reserved       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR02_UNION;
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_Q_PD_START    (0)
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_Q_PD_END      (0)
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_I_PD_START    (1)
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_I_PD_END      (1)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_START   (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_END     (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_START  (3)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_END    (3)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR03_UNION
 结构说明  : ch0_reg_analog_wr03 寄存器结构定义。地址偏移量:0xD1，初值:0x40，宽度:8
 寄存器说明: 数模接口时钟控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0        : 2;  /* bit[0-1]: Reserved */
        unsigned long  CH0_104M_52M_SEL  : 1;  /* bit[2]  : 52M和104M输出选择：
                                                            0：104M
                                                            1：52M */
        unsigned long  CH0_TX_CLKD_CTRL  : 1;  /* bit[3]  : TX 采样时钟沿选择：
                                                            0：正沿(默认)
                                                            1：反沿 */
        unsigned long  CH0_CLK_61D44M_PD : 1;  /* bit[4]  : CLK_61D44M Power Down控制
                                                            0：Power On(默认)
                                                            1：Power Down */
        unsigned long  CH0_CLK_52M_PD    : 1;  /* bit[5]  : CLK_52M Power Down控制
                                                            0：Power On(默认)
                                                            1：Power Down */
        unsigned long  CH0_CLK_245M_PD   : 1;  /* bit[6]  : CLK_245M Power Down控制
                                                            0：Power On
                                                            1：Power Down(默认) */
        unsigned long  reserved_1        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR03_UNION;
#define ABB_CH0_REG_ANALOG_WR03_CH0_104M_52M_SEL_START   (2)
#define ABB_CH0_REG_ANALOG_WR03_CH0_104M_52M_SEL_END     (2)
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_START   (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_END     (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_START  (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_END    (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_START     (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_END       (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_245M_PD_START    (6)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_245M_PD_END      (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR04_UNION
 结构说明  : ch0_reg_analog_wr04 寄存器结构定义。地址偏移量:0xD2，初值:0x0C，宽度:8
 寄存器说明: Other控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_EN_CAL       : 1;  /* bit[0]  : Calibration enable(默认为0)
                                                           上升沿启动Calibration过程 */
        unsigned long  reserved_0       : 1;  /* bit[1]  : Reserved */
        unsigned long  CH0_TX_AUTO_TUNE : 1;  /* bit[2]  : TX ADC自动tuning控制
                                                           0：手动tuning，tuning选择TX_TUNE1,TX_TUNE2,TX_TUNE3的值(默认)
                                                           1：自动tuning，TX通道的calibration值为CAL_VALUE */
        unsigned long  CH0_RX_AUTO_TUNE : 1;  /* bit[3]  : RX ADC自动tuning控制
                                                           0：手动tuning，tuning选择RX_TUNE1,RX_TUNE2,RX_TUNE3的值(默认)
                                                           1：自动tuning，RX通道的calibration值为CAL_VALUE */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR04_UNION;
#define ABB_CH0_REG_ANALOG_WR04_CH0_EN_CAL_START        (0)
#define ABB_CH0_REG_ANALOG_WR04_CH0_EN_CAL_END          (0)
#define ABB_CH0_REG_ANALOG_WR04_CH0_TX_AUTO_TUNE_START  (2)
#define ABB_CH0_REG_ANALOG_WR04_CH0_TX_AUTO_TUNE_END    (2)
#define ABB_CH0_REG_ANALOG_WR04_CH0_RX_AUTO_TUNE_START  (3)
#define ABB_CH0_REG_ANALOG_WR04_CH0_RX_AUTO_TUNE_END    (3)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR05_UNION
 结构说明  : ch0_reg_analog_wr05 寄存器结构定义。地址偏移量:0xD3，初值:0x40，宽度:8
 寄存器说明: ADC第一级积分器电容tuning寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_TUNE1 : 7;  /* bit[0-6]: ADC第一级积分器电容tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR05_UNION;
#define ABB_CH0_REG_ANALOG_WR05_CH0_RX_TUNE1_START  (0)
#define ABB_CH0_REG_ANALOG_WR05_CH0_RX_TUNE1_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR06_UNION
 结构说明  : ch0_reg_analog_wr06 寄存器结构定义。地址偏移量:0xD4，初值:0x40，宽度:8
 寄存器说明: ADC第二级积分器电容tuning寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_TUNE2 : 7;  /* bit[0-6]: ADC第二级积分器电容tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR06_UNION;
#define ABB_CH0_REG_ANALOG_WR06_CH0_RX_TUNE2_START  (0)
#define ABB_CH0_REG_ANALOG_WR06_CH0_RX_TUNE2_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR07_UNION
 结构说明  : ch0_reg_analog_wr07 寄存器结构定义。地址偏移量:0xD5，初值:0x40，宽度:8
 寄存器说明: ADC第三级积分器电容tuning寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_TUNE3 : 7;  /* bit[0-6]: ADC第三级积分器电容tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR07_UNION;
#define ABB_CH0_REG_ANALOG_WR07_CH0_RX_TUNE3_START  (0)
#define ABB_CH0_REG_ANALOG_WR07_CH0_RX_TUNE3_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR08_UNION
 结构说明  : ch0_reg_analog_wr08 寄存器结构定义。地址偏移量:0xD6，初值:0x40，宽度:8
 寄存器说明: DAC Tuning控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_TX_TUNE1 : 7;  /* bit[0-6]: TX_TUNE1控制信号 */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR08_UNION;
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE1_START  (0)
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE1_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR09_UNION
 结构说明  : ch0_reg_analog_wr09 寄存器结构定义。地址偏移量:0xD7，初值:0x40，宽度:8
 寄存器说明: DAC Tuning控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_TX_TUNE2 : 7;  /* bit[0-6]: TX_TUNE2控制信号 */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR09_UNION;
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE2_START  (0)
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE2_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR10_UNION
 结构说明  : ch0_reg_analog_wr10 寄存器结构定义。地址偏移量:0xD8，初值:0x40，宽度:8
 寄存器说明: DAC Tuning控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_TX_TUNE3 : 7;  /* bit[0-6]: TX_TUNE3控制信号 */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR10_UNION;
#define ABB_CH0_REG_ANALOG_WR10_CH0_TX_TUNE3_START  (0)
#define ABB_CH0_REG_ANALOG_WR10_CH0_TX_TUNE3_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR38_UNION
 结构说明  : ch0_reg_analog_wr38 寄存器结构定义。地址偏移量:0xD9，初值:0x00，宽度:8
 寄存器说明: 时钟反沿控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_ADC_QUANTIZER_CAL_CTRL : 1;  /* bit[0]  : ADC量化器校准使能：
                                                                        0：Not Cal(默认)
                                                                        1：Cal */
        unsigned long  CH0_RX_LDO_LOAD               : 1;  /* bit[1]  : Rx CK LDO电源负载调整
                                                                        0：不开启(默认)
                                                                        1：开启 */
        unsigned long  CH0_RX_LDO_VDD                : 3;  /* bit[2-4]: Rx CK LDO电源电压
                                                                        000：0.9V(默认) */
        unsigned long  CH0_RX_CLK2D_CTRL             : 1;  /* bit[5]  : ADC采样沿控制：
                                                                        0：正沿(默认)
                                                                        1：反沿 */
        unsigned long  CH0_RX_SYN2D_CTRL             : 1;  /* bit[6]  : ADC SYNC信号采样沿控制：
                                                                        0：正沿(默认)
                                                                        1：反沿 */
        unsigned long  CH0_RX_ADC_LDO_CTRL           : 1;  /* bit[7]  : RX_ADC LDO使能控制
                                                                        0：Power Down(默认)
                                                                        1：Power On */
        unsigned long  reserved_butt                 : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR38_UNION;
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_QUANTIZER_CAL_CTRL_START  (0)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_QUANTIZER_CAL_CTRL_END    (0)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_LOAD_START                (1)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_LOAD_END                  (1)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_VDD_START                 (2)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_VDD_END                   (4)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_CLK2D_CTRL_START              (5)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_CLK2D_CTRL_END                (5)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_SYN2D_CTRL_START              (6)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_SYN2D_CTRL_END                (6)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_LDO_CTRL_START            (7)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_LDO_CTRL_END              (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR39_UNION
 结构说明  : ch0_reg_analog_wr39 寄存器结构定义。地址偏移量:0xDA，初值:0x03，宽度:8
 寄存器说明: DUM控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_DUM_EN_Q : 1;  /* bit[0]  : TX Q channel  dummy logic control signal
                                                       1：enable(默认)
                                                       0：disable */
        unsigned long  CH0_DUM_EN_I : 1;  /* bit[1]  : TX I channel  dummy logic control signal
                                                       1：enable(默认)
                                                       0：disable */
        unsigned long  reserved     : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_DEM_MOD  : 1;  /* bit[7]  : RX DEM Mode Selection,bit 2,和ch0_reg_analog_wr00的bit3和bit0组合成3bit，实现如下9种组合：
                                                       000：DWA
                                                       001：CLA1
                                                       010：CLA2
                                                       011：CLA3
                                                       100：CLA4
                                                       101：CLA5
                                                       110：CLA6
                                                       111：CLA7 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR39_UNION;
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_START  (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_END    (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_START  (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_END    (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_START   (7)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_END     (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_RO0_UNION
 结构说明  : ch0_reg_analog_ro0 寄存器结构定义。地址偏移量:0xDB，初值:0x00，宽度:8
 寄存器说明: 标志位只读寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 5;  /* bit[0-4]: Reserved */
        unsigned long  CH0_CAL_DONE : 1;  /* bit[5]  : RC Calibration Done信号 */
        unsigned long  CH0_LOCK2    : 1;  /* bit[6]  : GPLL的LOCK信号 */
        unsigned long  CH0_LOCK1    : 1;  /* bit[7]  : WPLL的LOCK信号 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_RO0_UNION;
#define ABB_CH0_REG_ANALOG_RO0_CH0_CAL_DONE_START  (5)
#define ABB_CH0_REG_ANALOG_RO0_CH0_CAL_DONE_END    (5)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK2_START     (6)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK2_END       (6)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK1_START     (7)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK1_END       (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_RO1_UNION
 结构说明  : ch0_reg_analog_ro1 寄存器结构定义。地址偏移量:0xDC，初值:0x00，宽度:8
 寄存器说明: RC校准只读寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_CAL_VALUE : 7;  /* bit[0-6]: RC Calibration校准值 */
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_RO1_UNION;
#define ABB_CH0_REG_ANALOG_RO1_CH0_RX_CAL_VALUE_START  (0)
#define ABB_CH0_REG_ANALOG_RO1_CH0_RX_CAL_VALUE_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA0_UNION
 结构说明  : ch0_reg_debug_ana0 寄存器结构定义。地址偏移量:0xE0，初值:0x72，宽度:8
 寄存器说明: 模拟调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_CLK_REF_SEL  : 1;  /* bit[0]  : PLL的参考时钟选择
                                                           1：CLKIN_SYSTEM作为PLL的参考时钟
                                                           0：TCXO Buffer输出作为PLL参考时钟 */
        unsigned long  CH0_PLL_OCLK_SEL : 3;  /* bit[1-3]: 工作时钟选择
                                                           001：选择来自于PLL的时钟作为工作时钟
                                                           010：选择来自于CLKIN_SYSTEM的外灌时钟作为工作时钟
                                                           100：选择来自于TCXO_IN的时钟作为工作时钟 */
        unsigned long  CH0_PLL_PFD_CTRL : 2;  /* bit[4-5]: PLL鉴频鉴相器控制
                                                           x0：鉴频鉴相器一直输出Up信号
                                                           01：鉴频鉴相器一直输出Down信号
                                                           11：鉴频鉴相器正常工作 */
        unsigned long  CH0_GVCO_CR      : 2;  /* bit[6-7]: GPLL VCO Current控制
                                                           00：X1.2
                                                           01：X1.1(默认)
                                                           10：X1.1
                                                           11：X1.0 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA0_UNION;
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_START   (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_END     (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_START  (1)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_END    (5)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_GVCO_CR_START       (6)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_GVCO_CR_END         (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA1_UNION
 结构说明  : ch0_reg_debug_ana1 寄存器结构定义。地址偏移量:0xE1，初值:0x7A，宽度:8
 寄存器说明: PLL LOCK控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_GPLL_LK_CTRL : 2;  /* bit[0-1]: GPLL锁定Cycle控制
                                                           00：4
                                                           01：8
                                                           10：16(默认)
                                                           11：32 */
        unsigned long  CH0_WPLL_LK_CTRL : 2;  /* bit[2-3]: WPLL锁定Cycle控制
                                                           00：4
                                                           01：8
                                                           10：16(默认)
                                                           11：32 */
        unsigned long  CH0_GPLL_LK_EN   : 1;  /* bit[4]  : GPLL锁定检测使能
                                                           0：不输出检测信号
                                                           1：输出检测信号 */
        unsigned long  CH0_WPLL_LK_EN   : 1;  /* bit[5]  : WPLL锁定检测使能
                                                           0：不输出检测信号
                                                           1：输出检测信号 */
        unsigned long  CH0_WVCO_CR      : 2;  /* bit[6-7]: WPLL VCO Current控制
                                                           00：X1.2
                                                           01：X1.1(默认)
                                                           10：X1.1
                                                           11：X1.0 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA1_UNION;
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_CTRL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_CTRL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_CTRL_START  (2)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_CTRL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_START    (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_END      (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_START    (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_END      (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WVCO_CR_START       (6)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WVCO_CR_END         (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA2_UNION
 结构说明  : ch0_reg_debug_ana2 寄存器结构定义。地址偏移量:0xE2，初值:0x00，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_PLL_CP_PD : 2;  /* bit[0-1]: PLL CP PowerDown控制，测试用
                                                        00：正常工作
                                                        01：PowerDown WPLL CP
                                                        10：PowerDown GPLL CP
                                                        11：PowerDown WPLL CP和GPLL CP */
        unsigned long  reserved      : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_CLKN_EN   : 1;  /* bit[7]  : 反相时钟开关
                                                        1：反相时钟打开
                                                        0：反相时钟关闭 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA2_UNION;
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_START  (0)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_END    (1)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_START    (7)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_END      (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA3_UNION
 结构说明  : ch0_reg_debug_ana3 寄存器结构定义。地址偏移量:0xE3，初值:0x70，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_GPLL_CP_CTRL : 4;  /* bit[4-7]: GPLL电荷泵电流控制(低有效)
                                                           Basic：0.2*Icp
                                                           Bit0： 0.1*Icp
                                                           Bit1： 0.2*Icp
                                                           Bit2： 0.4*Icp
                                                           Bit3： 0.8*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA3_UNION;
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA4_UNION
 结构说明  : ch0_reg_debug_ana4 寄存器结构定义。地址偏移量:0xE4，初值:0x70，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_WPLL_CP_CTRL : 4;  /* bit[4-7]: WPLL电荷泵电流控制(低有效)
                                                           Basic：0.2*Icp
                                                           Bit0： 0.1*Icp
                                                           Bit1： 0.2*Icp
                                                           Bit2： 0.4*Icp
                                                           Bit3： 0.8*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA4_UNION;
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WPLL_CP_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WPLL_CP_CTRL_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA5_UNION
 结构说明  : ch0_reg_debug_ana5 寄存器结构定义。地址偏移量:0xE5，初值:0x00，宽度:8
 寄存器说明: 快速启动控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH0_ABB_REF_FS : 1;  /* bit[7]  : ABB_REF_Fast_UP控制
                                                         0：关闭(默认)
                                                         1：开启 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA5_UNION;
#define ABB_CH0_REG_DEBUG_ANA5_CH0_ABB_REF_FS_START  (7)
#define ABB_CH0_REG_DEBUG_ANA5_CH0_ABB_REF_FS_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA6_UNION
 结构说明  : ch0_reg_debug_ana6 寄存器结构定义。地址偏移量:0xE6，初值:0x6D，宽度:8
 寄存器说明: Bandgap和TCXO控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_GLLFREQ_SEL  : 2;  /* bit[0-1]: GPLL输入时钟频率选择
                                                           00：26M
                                                           01：19.2MM(默认)
                                                           10：52M
                                                           11：38.4M */
        unsigned long  CH0_WPLLFREQ_SEL : 2;  /* bit[2-3]: WPLL输入时钟频率选择
                                                           00：76.8M
                                                           01：38.4M
                                                           10：38.4M
                                                           11：19.2M(默认) */
        unsigned long  CH0_TCXO_DRV     : 2;  /* bit[4-5]: TCXO BUFFER电流设置
                                                           00：1x
                                                           01：2x
                                                           10：3x(默认)
                                                           11：4x */
        unsigned long  CH0_CLKIN_PD     : 1;  /* bit[6]  : TEST CLK INPUT下电控制
                                                           0：开启
                                                           1：关闭 */
        unsigned long  reserved         : 1;  /* bit[7]  : reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA6_UNION;
#define ABB_CH0_REG_DEBUG_ANA6_CH0_GLLFREQ_SEL_START   (0)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_GLLFREQ_SEL_END     (1)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_WPLLFREQ_SEL_START  (2)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_WPLLFREQ_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_START      (4)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_END        (5)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_START      (6)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_END        (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA7_UNION
 结构说明  : ch0_reg_debug_ana7 寄存器结构定义。地址偏移量:0xE7，初值:0x00，宽度:8
 寄存器说明: 电流控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_DRVBUF_CT : 3;  /* bit[0-2]: L/W/G 共用ADC 差分Buffer电流调节控制
                                                        000：5u
                                                        001：2u
                                                        010：3u
                                                        011：4u
                                                        100：6u
                                                        101：7u
                                                        110：8u
                                                        111：9u */
        unsigned long  reserved      : 5;  /* bit[3-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA7_UNION;
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_END    (2)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA8_UNION
 结构说明  : ch0_reg_debug_ana8 寄存器结构定义。地址偏移量:0xE8，初值:0x00，宽度:8
 寄存器说明: 电流控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0   : 5;  /* bit[0-4]: Reserved */
        unsigned long  reserved_1   : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA8_UNION;


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA9_UNION
 结构说明  : ch0_reg_debug_ana9 寄存器结构定义。地址偏移量:0xE9，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_DAC_DUM_B0   : 1;  /* bit[0]  : RX方向sub_DAC Dummy单元控制，低一位
                                                           0：开启
                                                           1：关闭 */
        unsigned long  CH0_L_PUP_MODE   : 1;  /* bit[1]  : LTE ADC模块启动模式选择
                                                           0：自动模式
                                                           1：配置寄存器模式 */
        unsigned long  reserved_0       : 1;  /* bit[2]  : Reserved */
        unsigned long  CH0_L_DEM_PD     : 1;  /* bit[3]  : LTE ADC DEM功能关闭信号
                                                           0：DEM使能
                                                           1：DEM不使能 */
        unsigned long  CH0_L_TUNING_SEL : 1;  /* bit[4]  : LTE ADC模块Tuning码的选择
                                                           0：选择Tuning模块的输出作为LTE ADC的Tuning码
                                                           1：选择寄存器的输出作为LTE ADC的Tuning码 */
        unsigned long  reserved_1       : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA9_UNION;
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_START    (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_END      (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_START    (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_END      (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_START      (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_END        (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_END    (4)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA10_UNION
 结构说明  : ch0_reg_debug_ana10 寄存器结构定义。地址偏移量:0xEA，初值:0x00，宽度:8
 寄存器说明: ADC复位控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_DAC_DUM_B2B1 : 2;  /* bit[0-1]: RX方向sub_DAC Dummy单元控制，高两位
                                                           0：开启
                                                           1：关闭 */
        unsigned long  CH0_L_PUP_CTRL0  : 1;  /* bit[2]  : LTE ADC中第一级积分器电容复位控制
                                                           0：不复位
                                                           1：复位 */
        unsigned long  CH0_L_PUP_CTRL1  : 1;  /* bit[3]  : LTE ADC中第二级积分器电容复位控制
                                                           0：不复位
                                                           1：复位 */
        unsigned long  CH0_L_PUP_CTRL2  : 1;  /* bit[4]  : LTE ADC中第三级积分器电容复位控制
                                                           0：不复位
                                                           1：复位 */
        unsigned long  CH0_L_PUP_CTRL3  : 1;  /* bit[5]  : LTE ADC中CKGEN模块Powerup控制
                                                           0：Powerdown
                                                           1：Powerup */
        unsigned long  CH0_L_PUP_CTRL4  : 1;  /* bit[6]  : LTE ADC中OP模块Powerup控制
                                                           0：Powerdown
                                                           1：Powerup */
        unsigned long  CH0_L_PUP_CTRL5  : 1;  /* bit[7]  : LTE ADC中DAC模块Powerup控制
                                                           0：Powerdown
                                                           1：Powerup */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA10_UNION;
#define ABB_CH0_REG_DEBUG_ANA10_CH0_DAC_DUM_B2B1_START  (0)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_DAC_DUM_B2B1_END    (1)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL0_START   (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL0_END     (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL1_START   (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL1_END     (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL2_START   (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL2_END     (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL3_START   (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL3_END     (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL4_START   (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL4_END     (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL5_START   (7)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL5_END     (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA11_UNION
 结构说明  : ch0_reg_debug_ana11 寄存器结构定义。地址偏移量:0xEB，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 6;  /* bit[0-5]: Reserved */
        unsigned long  CH0_BG_OPEN_EN : 1;  /* bit[6]  : 0： Reference turn on
                                                         1： BG_OPEN_EN is not effective */
        unsigned long  CH0_BG_DOWN_PD : 1;  /* bit[7]  : 0： Reference turn off
                                                         1： BG_OPEN_EN is effective */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA11_UNION;
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_OPEN_EN_START  (6)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_OPEN_EN_END    (6)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_DOWN_PD_START  (7)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_DOWN_PD_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA14_UNION
 结构说明  : ch0_reg_debug_ana14 寄存器结构定义。地址偏移量:0xEE，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_L_OL_CT : 3;  /* bit[0-2]: LTE Overload模块配置
                                                      00：16个连续最大码或者最小码
                                                      01：8个连续最大码或者最小码
                                                      10：4个连续最大码或者最小码
                                                      11：关闭Overload检测 */
        unsigned long  reserved    : 3;  /* bit[3-5]: Reserved */
        unsigned long  CH0_L_CK_CT : 2;  /* bit[6-7]: LTE SYNC时序控制
                                                      00：No delay
                                                      01：250ps delay
                                                      10：500ps delay
                                                      11：1000ps delay */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA14_UNION;
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_END    (2)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_START  (6)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA16_UNION
 结构说明  : ch0_reg_debug_ana16 寄存器结构定义。地址偏移量:0xF0，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0   : 6;  /* bit[0-5]: Reserved */
        unsigned long  CH0_PDM_CTRL : 1;  /* bit[6]  : RX输出PDM编码控制
                                                       0：adder encoder
                                                       1：de-bubble encoder */
        unsigned long  reserved_1   : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA16_UNION;
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_START  (6)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA17_UNION
 结构说明  : ch0_reg_debug_ana17 寄存器结构定义。地址偏移量:0xF1，初值:0x00，宽度:8
 寄存器说明: PLL测试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_PLL1_CLK_TEST : 2;  /* bit[4-5]: PLL时钟测试PAD信号选择
                                                            00：时钟测试PAD浮空
                                                            01：WPLL输出时钟到PAD
                                                            10：GPLL输出时钟到PAD */
        unsigned long  CH0_PLL1_ANA_TEST : 2;  /* bit[6-7]: PLL控制电压测试PAD信号选择
                                                            00：控制电压测试PAD浮空
                                                            01：WPLL输出控制电压到PAD
                                                            10：GPLL输出控制电压到PAD */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA17_UNION;
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_CLK_TEST_START  (4)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_CLK_TEST_END    (5)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_ANA_TEST_START  (6)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_ANA_TEST_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA19_UNION
 结构说明  : ch0_reg_debug_ana19 寄存器结构定义。地址偏移量:0xF3，初值:0x30，宽度:8
 寄存器说明: 时钟使能控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_CLK_PADF_SEL : 2;  /* bit[0-1]: 测试管脚输出时钟频率控制
                                                           00：输出最高时速
                                                           01：WPLL输出半速
                                                           10：GPLL输出半速
                                                           11：WPLL和GPLL输出半速 */
        unsigned long  reserved_0       : 2;  /* bit[2-3]: Reserved */
        unsigned long  CH0_DAC_CLK_EN   : 1;  /* bit[4]  : PLL模块307.2MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  CH0_ADC_CLK_EN   : 1;  /* bit[5]  : PLL模块307.2MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  reserved_1       : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA19_UNION;
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_START    (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_END      (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_START    (5)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_END      (5)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA20_UNION
 结构说明  : ch0_reg_debug_ana20 寄存器结构定义。地址偏移量:0xF4，初值:0x40，宽度:8
 寄存器说明: 模拟调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_TCXO_BUF_SEL      : 1;  /* bit[0]  : TCXO Buffer选择
                                                                0: 单端TCXO Buffer
                                                                1: 双端TCXO Buffer */
        unsigned long  CH0_TCXO_OUT_CTRL     : 1;  /* bit[1]  : CH0送给CH1的TCXO时钟开关控制
                                                                0：关闭
                                                                1：打开 */
        unsigned long  CH0_TCXO_SEL          : 1;  /* bit[2]  : PLL时钟基准选择信号
                                                                0: CH0 的TCXO时钟
                                                                1: CH1 的TCXO时钟 */
        unsigned long  reserved              : 2;  /* bit[3-4]: Reserved */
        unsigned long  CH0_ADC_ST3_CAP_MULTI : 2;  /* bit[5-6]: ADC第三级电容倍乘系数
                                                                00：X1(默认)
                                                                01：X1.5
                                                                10：X1.25
                                                                11：X1.125 */
        unsigned long  CH0_CAP_SEL           : 1;  /* bit[7]  : Tuning电路电容选择
                                                                0：大电容
                                                                1：小电容 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA20_UNION;
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_BUF_SEL_START       (0)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_BUF_SEL_END         (0)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_OUT_CTRL_START      (1)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_OUT_CTRL_END        (1)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_SEL_START           (2)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_SEL_END             (2)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_ADC_ST3_CAP_MULTI_START  (5)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_ADC_ST3_CAP_MULTI_END    (6)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_START            (7)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_END              (7)


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
        unsigned long  sine_enable : 1;  /* bit[0]  : 正弦波发送使能
                                                      0：不发送
                                                      1：发送 */
        unsigned long  sine_sw_req : 1;  /* bit[1]  : 正弦波发送通道切换
                                                      0：CH1
                                                      1：CH0 */
        unsigned long  sine_amp    : 2;  /* bit[2-3]: 正弦波发送幅度控制
                                                      00：满量程
                                                      01：3/4量程
                                                      10：1/2量程
                                                      11：1/4量程 */
        unsigned long  sine_freq   : 4;  /* bit[4-7]: 正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SINE_GENERATE_UNION;
#define ABB_SINE_GENERATE_sine_enable_START  (0)
#define ABB_SINE_GENERATE_sine_enable_END    (0)
#define ABB_SINE_GENERATE_sine_sw_req_START  (1)
#define ABB_SINE_GENERATE_sine_sw_req_END    (1)
#define ABB_SINE_GENERATE_sine_amp_START     (2)
#define ABB_SINE_GENERATE_sine_amp_END       (3)
#define ABB_SINE_GENERATE_sine_freq_START    (4)
#define ABB_SINE_GENERATE_sine_freq_END      (7)


/*****************************************************************************
 结构名    : ABB_TX_2G_ANA_3_UNION
 结构说明  : tx_2g_ana_3 寄存器结构定义。地址偏移量:0x100，初值:0x18，宽度:8
 寄存器说明: TX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr50。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_2G     : 3;  /* bit[0-2]: LPF OP1 电流模式调整
                                                          000：5u
                                                          001：4u
                                                          010：3u
                                                          011：2u
                                                          100：9u
                                                          101：7u
                                                          110：6u
                                                          111：5u */
        unsigned long  DUM_EN_Q_2G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1：enable(默认)
                                                          0：disable */
        unsigned long  DUM_EN_I_2G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1：enable(默认)
                                                          0：disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: Reserved */
        unsigned long  TX_CLKD_CTRL_2G : 1;  /* bit[7]  : TX 采样时钟沿选择：
                                                          0：正沿(默认)
                                                          1：反沿 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_3_UNION;
#define ABB_TX_2G_ANA_3_TXLPF_CT_2G_START      (0)
#define ABB_TX_2G_ANA_3_TXLPF_CT_2G_END        (2)
#define ABB_TX_2G_ANA_3_DUM_EN_Q_2G_START      (3)
#define ABB_TX_2G_ANA_3_DUM_EN_Q_2G_END        (3)
#define ABB_TX_2G_ANA_3_DUM_EN_I_2G_START      (4)
#define ABB_TX_2G_ANA_3_DUM_EN_I_2G_END        (4)
#define ABB_TX_2G_ANA_3_TX_CLKD_CTRL_2G_START  (7)
#define ABB_TX_2G_ANA_3_TX_CLKD_CTRL_2G_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_3_UNION
 结构说明  : rx_2g_ana_3 寄存器结构定义。地址偏移量:0x103，初值:0x00，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr53。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_2G : 3;  /* bit[0-2]: RX ADC OP1电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  ITR_OP3_2G : 3;  /* bit[3-5]: RX ADC OP3电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_3_UNION;
#define ABB_RX_2G_ANA_3_ITR_OP1_2G_START  (0)
#define ABB_RX_2G_ANA_3_ITR_OP1_2G_END    (2)
#define ABB_RX_2G_ANA_3_ITR_OP3_2G_START  (3)
#define ABB_RX_2G_ANA_3_ITR_OP3_2G_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_4_UNION
 结构说明  : rx_2g_ana_4 寄存器结构定义。地址偏移量:0x104，初值:0x00，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr54。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_2G  : 3;  /* bit[0-2]: RX ADC QT电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  ITR_DAC_2G : 3;  /* bit[3-5]: RX ADC 反馈DAC运放电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_4_UNION;
#define ABB_RX_2G_ANA_4_ITR_QT_2G_START   (0)
#define ABB_RX_2G_ANA_4_ITR_QT_2G_END     (2)
#define ABB_RX_2G_ANA_4_ITR_DAC_2G_START  (3)
#define ABB_RX_2G_ANA_4_ITR_DAC_2G_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_5_UNION
 结构说明  : rx_2g_ana_5 寄存器结构定义。地址偏移量:0x105，初值:0x00，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr55。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_2G  : 3;  /* bit[0-2]: RX ADC OP2电流控制
                                                      000： 1.0x
                                                      001： 0.8x
                                                      010： 0.6x
                                                      011： 0.4x
                                                      100： 1.8x
                                                      101： 1.6x
                                                      110： 1.4x
                                                      111： 1.2x */
        unsigned long  IBCT_OP2_2G : 2;  /* bit[3-4]: Current Seting For Mode
                                                      1x：LTE mode Current
                                                      01：3G_DC &amp; X mode Current
                                                      00：3G &amp; 2G mode Current */
        unsigned long  reserved    : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_5_UNION;
#define ABB_RX_2G_ANA_5_ITR_OP2_2G_START   (0)
#define ABB_RX_2G_ANA_5_ITR_OP2_2G_END     (2)
#define ABB_RX_2G_ANA_5_IBCT_OP2_2G_START  (3)
#define ABB_RX_2G_ANA_5_IBCT_OP2_2G_END    (4)


/*****************************************************************************
 结构名    : ABB_TX_CH0_3G_ANA_3_UNION
 结构说明  : tx_ch0_3g_ana_3 寄存器结构定义。地址偏移量:0x106，初值:0x18，宽度:8
 寄存器说明: CH0 TX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr50。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_3G     : 3;  /* bit[0-2]: LPF OP1 电流模式调整
                                                          000：5u
                                                          001：4u
                                                          010：3u
                                                          011：2u
                                                          100：9u
                                                          101：7u
                                                          110：6u
                                                          111：5u */
        unsigned long  DUM_EN_Q_3G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1：enable(默认)
                                                          0：disable */
        unsigned long  DUM_EN_I_3G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1：enable(默认)
                                                          0：disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: Reserved */
        unsigned long  TX_CLKD_CTRL_3G : 1;  /* bit[7]  : TX 采样时钟沿选择：
                                                          0：正沿(默认)
                                                          1：反沿 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_ANA_3_UNION;
#define ABB_TX_CH0_3G_ANA_3_TXLPF_CT_3G_START      (0)
#define ABB_TX_CH0_3G_ANA_3_TXLPF_CT_3G_END        (2)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_Q_3G_START      (3)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_Q_3G_END        (3)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_I_3G_START      (4)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_I_3G_END        (4)
#define ABB_TX_CH0_3G_ANA_3_TX_CLKD_CTRL_3G_START  (7)
#define ABB_TX_CH0_3G_ANA_3_TX_CLKD_CTRL_3G_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_3G_ANA_3_UNION
 结构说明  : rx_ch0_3g_ana_3 寄存器结构定义。地址偏移量:0x109，初值:0x00，宽度:8
 寄存器说明: CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr53。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_3G : 3;  /* bit[0-2]: RX ADC OP1电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  ITR_OP3_3G : 3;  /* bit[3-5]: RX ADC OP3电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_3_UNION;
#define ABB_RX_CH0_3G_ANA_3_ITR_OP1_3G_START  (0)
#define ABB_RX_CH0_3G_ANA_3_ITR_OP1_3G_END    (2)
#define ABB_RX_CH0_3G_ANA_3_ITR_OP3_3G_START  (3)
#define ABB_RX_CH0_3G_ANA_3_ITR_OP3_3G_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_CH0_3G_ANA_4_UNION
 结构说明  : rx_ch0_3g_ana_4 寄存器结构定义。地址偏移量:0x10A，初值:0x00，宽度:8
 寄存器说明: CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr54。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_3G  : 3;  /* bit[0-2]: RX ADC QT电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  ITR_DAC_3G : 3;  /* bit[3-5]: RX ADC 反馈DAC运放电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_4_UNION;
#define ABB_RX_CH0_3G_ANA_4_ITR_QT_3G_START   (0)
#define ABB_RX_CH0_3G_ANA_4_ITR_QT_3G_END     (2)
#define ABB_RX_CH0_3G_ANA_4_ITR_DAC_3G_START  (3)
#define ABB_RX_CH0_3G_ANA_4_ITR_DAC_3G_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_CH0_3G_ANA_5_UNION
 结构说明  : rx_ch0_3g_ana_5 寄存器结构定义。地址偏移量:0x10B，初值:0x00，宽度:8
 寄存器说明: CH0 RX 3G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr55。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_3G  : 3;  /* bit[0-2]: RX ADC OP2电流控制
                                                      000： 1.0x
                                                      001： 0.8x
                                                      010： 0.6x
                                                      011： 0.4x
                                                      100： 1.8x
                                                      101： 1.6x
                                                      110： 1.4x
                                                      111： 1.2x */
        unsigned long  IBCT_OP2_3G : 2;  /* bit[3-4]: Current Seting For Mode
                                                      1x：LTE mode Current
                                                      01：3G_DC &amp; X mode Current
                                                      00：3G &amp; 2G mode Current */
        unsigned long  reserved    : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_5_UNION;
#define ABB_RX_CH0_3G_ANA_5_ITR_OP2_3G_START   (0)
#define ABB_RX_CH0_3G_ANA_5_ITR_OP2_3G_END     (2)
#define ABB_RX_CH0_3G_ANA_5_IBCT_OP2_3G_START  (3)
#define ABB_RX_CH0_3G_ANA_5_IBCT_OP2_3G_END    (4)


/*****************************************************************************
 结构名    : ABB_TX_CH0_4G_ANA_3_UNION
 结构说明  : tx_ch0_4g_ana_3 寄存器结构定义。地址偏移量:0x10C，初值:0x18，宽度:8
 寄存器说明: CH0 TX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr50。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_4G     : 3;  /* bit[0-2]: LPF OP1 电流模式调整
                                                          000：5u
                                                          001：4u
                                                          010：3u
                                                          011：2u
                                                          100：9u
                                                          101：7u
                                                          110：6u
                                                          111：5u */
        unsigned long  DUM_EN_Q_4G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1：enable(默认)
                                                          0：disable */
        unsigned long  DUM_EN_I_4G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1：enable(默认)
                                                          0：disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: Reserved */
        unsigned long  TX_CLKD_CTRL_4G : 1;  /* bit[7]  : TX 采样时钟沿选择：
                                                          0：正沿(默认)
                                                          1：反沿 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_ANA_3_UNION;
#define ABB_TX_CH0_4G_ANA_3_TXLPF_CT_4G_START      (0)
#define ABB_TX_CH0_4G_ANA_3_TXLPF_CT_4G_END        (2)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_Q_4G_START      (3)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_Q_4G_END        (3)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_I_4G_START      (4)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_I_4G_END        (4)
#define ABB_TX_CH0_4G_ANA_3_TX_CLKD_CTRL_4G_START  (7)
#define ABB_TX_CH0_4G_ANA_3_TX_CLKD_CTRL_4G_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_ANA_3_UNION
 结构说明  : rx_ch0_4g_ana_3 寄存器结构定义。地址偏移量:0x10F，初值:0x00，宽度:8
 寄存器说明: CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr53。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_4G : 3;  /* bit[0-2]: RX ADC OP1电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  ITR_OP3_4G : 3;  /* bit[3-5]: RX ADC OP3电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_3_UNION;
#define ABB_RX_CH0_4G_ANA_3_ITR_OP1_4G_START  (0)
#define ABB_RX_CH0_4G_ANA_3_ITR_OP1_4G_END    (2)
#define ABB_RX_CH0_4G_ANA_3_ITR_OP3_4G_START  (3)
#define ABB_RX_CH0_4G_ANA_3_ITR_OP3_4G_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_ANA_4_UNION
 结构说明  : rx_ch0_4g_ana_4 寄存器结构定义。地址偏移量:0x110，初值:0x00，宽度:8
 寄存器说明: CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr54。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_4G  : 3;  /* bit[0-2]: RX ADC QT电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  ITR_DAC_4G : 3;  /* bit[3-5]: RX ADC 反馈DAC运放电流控制
                                                     000： 1.0x
                                                     001： 0.8x
                                                     010： 0.6x
                                                     011： 0.4x
                                                     100： 1.8x
                                                     101： 1.6x
                                                     110： 1.4x
                                                     111： 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_4_UNION;
#define ABB_RX_CH0_4G_ANA_4_ITR_QT_4G_START   (0)
#define ABB_RX_CH0_4G_ANA_4_ITR_QT_4G_END     (2)
#define ABB_RX_CH0_4G_ANA_4_ITR_DAC_4G_START  (3)
#define ABB_RX_CH0_4G_ANA_4_ITR_DAC_4G_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_CH0_4G_ANA_5_UNION
 结构说明  : rx_ch0_4g_ana_5 寄存器结构定义。地址偏移量:0x111，初值:0x10，宽度:8
 寄存器说明: CH0 RX 4G配置寄存器，经过线控逻辑后送至ch0_reg_analog_wr55。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_4G  : 3;  /* bit[0-2]: RX ADC OP2电流控制
                                                      000： 1.0x
                                                      001： 0.8x
                                                      010： 0.6x
                                                      011： 0.4x
                                                      100： 1.8x
                                                      101： 1.6x
                                                      110： 1.4x
                                                      111： 1.2x */
        unsigned long  IBCT_OP2_4G : 2;  /* bit[3-4]: Current Seting For Mode
                                                      1x：LTE mode Current
                                                      01：3G_DC &amp; X mode Current
                                                      00：3G &amp; 2G mode Current */
        unsigned long  reserved    : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_5_UNION;
#define ABB_RX_CH0_4G_ANA_5_ITR_OP2_4G_START   (0)
#define ABB_RX_CH0_4G_ANA_5_ITR_OP2_4G_END     (2)
#define ABB_RX_CH0_4G_ANA_5_IBCT_OP2_4G_START  (3)
#define ABB_RX_CH0_4G_ANA_5_IBCT_OP2_4G_END    (4)


/*****************************************************************************
 结构名    : ABB_TX_TDS_ANA_3_UNION
 结构说明  : tx_tds_ana_3 寄存器结构定义。地址偏移量:0x112，初值:0x18，宽度:8
 寄存器说明: TX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr50。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_TDS     : 3;  /* bit[0-2]: LPF OP1 电流模式调整
                                                           000：5u
                                                           001：4u
                                                           010：3u
                                                           011：2u
                                                           100：9u
                                                           101：7u
                                                           110：6u
                                                           111：5u */
        unsigned long  DUM_EN_Q_TDS     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                           1：enable(默认)
                                                           0：disable */
        unsigned long  DUM_EN_I_TDS     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                           1：enable(默认)
                                                           0：disable */
        unsigned long  reserved         : 2;  /* bit[5-6]: Reserved */
        unsigned long  TX_CLKD_CTRL_TDS : 1;  /* bit[7]  : TX 采样时钟沿选择：
                                                           0：正沿(默认)
                                                           1：反沿 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_3_UNION;
#define ABB_TX_TDS_ANA_3_TXLPF_CT_TDS_START      (0)
#define ABB_TX_TDS_ANA_3_TXLPF_CT_TDS_END        (2)
#define ABB_TX_TDS_ANA_3_DUM_EN_Q_TDS_START      (3)
#define ABB_TX_TDS_ANA_3_DUM_EN_Q_TDS_END        (3)
#define ABB_TX_TDS_ANA_3_DUM_EN_I_TDS_START      (4)
#define ABB_TX_TDS_ANA_3_DUM_EN_I_TDS_END        (4)
#define ABB_TX_TDS_ANA_3_TX_CLKD_CTRL_TDS_START  (7)
#define ABB_TX_TDS_ANA_3_TX_CLKD_CTRL_TDS_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_3_UNION
 结构说明  : rx_tds_ana_3 寄存器结构定义。地址偏移量:0x115，初值:0x00，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr53。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_TDS : 3;  /* bit[0-2]: RX ADC OP1电流控制
                                                      000： 1.0x
                                                      001： 0.8x
                                                      010： 0.6x
                                                      011： 0.4x
                                                      100： 1.8x
                                                      101： 1.6x
                                                      110： 1.4x
                                                      111： 1.2x */
        unsigned long  ITR_OP3_TDS : 3;  /* bit[3-5]: RX ADC OP3电流控制
                                                      000： 1.0x
                                                      001： 0.8x
                                                      010： 0.6x
                                                      011： 0.4x
                                                      100： 1.8x
                                                      101： 1.6x
                                                      110： 1.4x
                                                      111： 1.2x */
        unsigned long  reserved    : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_3_UNION;
#define ABB_RX_TDS_ANA_3_ITR_OP1_TDS_START  (0)
#define ABB_RX_TDS_ANA_3_ITR_OP1_TDS_END    (2)
#define ABB_RX_TDS_ANA_3_ITR_OP3_TDS_START  (3)
#define ABB_RX_TDS_ANA_3_ITR_OP3_TDS_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_4_UNION
 结构说明  : rx_tds_ana_4 寄存器结构定义。地址偏移量:0x116，初值:0x00，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr54。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_TDS  : 3;  /* bit[0-2]: RX ADC QT电流控制
                                                      000： 1.0x
                                                      001： 0.8x
                                                      010： 0.6x
                                                      011： 0.4x
                                                      100： 1.8x
                                                      101： 1.6x
                                                      110： 1.4x
                                                      111： 1.2x */
        unsigned long  ITR_DAC_TDS : 3;  /* bit[3-5]: RX ADC 反馈DAC运放电流控制
                                                      000： 1.0x
                                                      001： 0.8x
                                                      010： 0.6x
                                                      011： 0.4x
                                                      100： 1.8x
                                                      101： 1.6x
                                                      110： 1.4x
                                                      111： 1.2x */
        unsigned long  reserved    : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_4_UNION;
#define ABB_RX_TDS_ANA_4_ITR_QT_TDS_START   (0)
#define ABB_RX_TDS_ANA_4_ITR_QT_TDS_END     (2)
#define ABB_RX_TDS_ANA_4_ITR_DAC_TDS_START  (3)
#define ABB_RX_TDS_ANA_4_ITR_DAC_TDS_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_5_UNION
 结构说明  : rx_tds_ana_5 寄存器结构定义。地址偏移量:0x117，初值:0x00，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr55。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_TDS  : 3;  /* bit[0-2]: RX ADC OP2电流控制
                                                       000： 1.0x
                                                       001： 0.8x
                                                       010： 0.6x
                                                       011： 0.4x
                                                       100： 1.8x
                                                       101： 1.6x
                                                       110： 1.4x
                                                       111： 1.2x */
        unsigned long  IBCT_OP2_TDS : 2;  /* bit[3-4]: Current Seting For Mode
                                                       1x：LTE mode Current
                                                       01：3G_DC &amp; X mode Current
                                                       00：3G &amp; 2G mode Current */
        unsigned long  reserved     : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_5_UNION;
#define ABB_RX_TDS_ANA_5_ITR_OP2_TDS_START   (0)
#define ABB_RX_TDS_ANA_5_ITR_OP2_TDS_END     (2)
#define ABB_RX_TDS_ANA_5_IBCT_OP2_TDS_START  (3)
#define ABB_RX_TDS_ANA_5_IBCT_OP2_TDS_END    (4)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_ANA_3_UNION
 结构说明  : tx_idle_ana_3 寄存器结构定义。地址偏移量:0x12A，初值:0x00，宽度:8
 寄存器说明: TX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr50。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_IDLE     : 3;  /* bit[0-2]: LPF OP1 电流模式调整
                                                            000：5u
                                                            001：4u
                                                            010：3u
                                                            011：2u
                                                            100：9u
                                                            101：7u
                                                            110：6u
                                                            111：5u */
        unsigned long  DUM_EN_Q_IDLE     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                            1：enable(默认)
                                                            0：disable */
        unsigned long  DUM_EN_I_IDLE     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                            1：enable(默认)
                                                            0：disable */
        unsigned long  reserved          : 2;  /* bit[5-6]: Reserved */
        unsigned long  TX_CLKD_CTRL_IDLE : 1;  /* bit[7]  : TX 采样时钟沿选择：
                                                            0：正沿(默认)
                                                            1：反沿 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_3_UNION;
#define ABB_TX_IDLE_ANA_3_TXLPF_CT_IDLE_START      (0)
#define ABB_TX_IDLE_ANA_3_TXLPF_CT_IDLE_END        (2)
#define ABB_TX_IDLE_ANA_3_DUM_EN_Q_IDLE_START      (3)
#define ABB_TX_IDLE_ANA_3_DUM_EN_Q_IDLE_END        (3)
#define ABB_TX_IDLE_ANA_3_DUM_EN_I_IDLE_START      (4)
#define ABB_TX_IDLE_ANA_3_DUM_EN_I_IDLE_END        (4)
#define ABB_TX_IDLE_ANA_3_TX_CLKD_CTRL_IDLE_START  (7)
#define ABB_TX_IDLE_ANA_3_TX_CLKD_CTRL_IDLE_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_3_UNION
 结构说明  : rx_idle_ana_3 寄存器结构定义。地址偏移量:0x12D，初值:0x00，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr53。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_IDLE : 3;  /* bit[0-2]: RX ADC OP1电流控制
                                                       000： 1.0x
                                                       001： 0.8x
                                                       010： 0.6x
                                                       011： 0.4x
                                                       100： 1.8x
                                                       101： 1.6x
                                                       110： 1.4x
                                                       111： 1.2x */
        unsigned long  ITR_OP3_IDLE : 3;  /* bit[3-5]: RX ADC OP3电流控制
                                                       000： 1.0x
                                                       001： 0.8x
                                                       010： 0.6x
                                                       011： 0.4x
                                                       100： 1.8x
                                                       101： 1.6x
                                                       110： 1.4x
                                                       111： 1.2x */
        unsigned long  reserved     : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_3_UNION;
#define ABB_RX_IDLE_ANA_3_ITR_OP1_IDLE_START  (0)
#define ABB_RX_IDLE_ANA_3_ITR_OP1_IDLE_END    (2)
#define ABB_RX_IDLE_ANA_3_ITR_OP3_IDLE_START  (3)
#define ABB_RX_IDLE_ANA_3_ITR_OP3_IDLE_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_4_UNION
 结构说明  : rx_idle_ana_4 寄存器结构定义。地址偏移量:0x12E，初值:0x00，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr54。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_IDLE  : 3;  /* bit[0-2]: RX ADC QT电流控制
                                                       000： 1.0x
                                                       001： 0.8x
                                                       010： 0.6x
                                                       011： 0.4x
                                                       100： 1.8x
                                                       101： 1.6x
                                                       110： 1.4x
                                                       111： 1.2x */
        unsigned long  ITR_DAC_IDLE : 3;  /* bit[3-5]: RX ADC 反馈DAC运放电流控制
                                                       000： 1.0x
                                                       001： 0.8x
                                                       010： 0.6x
                                                       011： 0.4x
                                                       100： 1.8x
                                                       101： 1.6x
                                                       110： 1.4x
                                                       111： 1.2x */
        unsigned long  reserved     : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_4_UNION;
#define ABB_RX_IDLE_ANA_4_ITR_QT_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_4_ITR_QT_IDLE_END     (2)
#define ABB_RX_IDLE_ANA_4_ITR_DAC_IDLE_START  (3)
#define ABB_RX_IDLE_ANA_4_ITR_DAC_IDLE_END    (5)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_5_UNION
 结构说明  : rx_idle_ana_5 寄存器结构定义。地址偏移量:0x12F，初值:0x00，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr55。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_IDLE  : 3;  /* bit[0-2]: RX ADC OP2电流控制
                                                        000： 1.0x
                                                        001： 0.8x
                                                        010： 0.6x
                                                        011： 0.4x
                                                        100： 1.8x
                                                        101： 1.6x
                                                        110： 1.4x
                                                        111： 1.2x */
        unsigned long  IBCT_OP2_IDLE : 2;  /* bit[3-4]: Current Seting For Mode
                                                        1x：LTE mode Current
                                                        01：3G_DC &amp; X mode Current
                                                        00：3G &amp; 2G mode Current */
        unsigned long  reserved      : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_5_UNION;
#define ABB_RX_IDLE_ANA_5_ITR_OP2_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_5_ITR_OP2_IDLE_END     (2)
#define ABB_RX_IDLE_ANA_5_IBCT_OP2_IDLE_START  (3)
#define ABB_RX_IDLE_ANA_5_IBCT_OP2_IDLE_END    (4)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA27_UNION
 结构说明  : ch0_reg_debug_ana27 寄存器结构定义。地址偏移量:0x140，初值:0x00，宽度:8
 寄存器说明: 模拟调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RXC_IBCT2 : 2;  /* bit[0-1]: TBD */
        unsigned long  CH0_RXC_IBCT1 : 2;  /* bit[2-3]: TBD */
        unsigned long  CH0_RXC_MODE  : 3;  /* bit[4-6]: TBD */
        unsigned long  reserved      : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA27_UNION;
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT2_START  (0)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT2_END    (1)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT1_START  (2)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT1_END    (3)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_MODE_START   (4)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_MODE_END     (6)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_6_UNION
 结构说明  : rx_2g_ana_6 寄存器结构定义。地址偏移量:0x18F，初值:0x00，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3_2G : 2;  /* bit[2-3]: BWCT_OP3 OP3带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  BWCT_OP2_2G : 2;  /* bit[4-5]: BWCT_OP2 OP2带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  BWCT_OP1_2G : 2;  /* bit[6-7]: BWCT_OP1 OP1带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_6_UNION;
#define ABB_RX_2G_ANA_6_BWCT_OP3_2G_START  (2)
#define ABB_RX_2G_ANA_6_BWCT_OP3_2G_END    (3)
#define ABB_RX_2G_ANA_6_BWCT_OP2_2G_START  (4)
#define ABB_RX_2G_ANA_6_BWCT_OP2_2G_END    (5)
#define ABB_RX_2G_ANA_6_BWCT_OP1_2G_START  (6)
#define ABB_RX_2G_ANA_6_BWCT_OP1_2G_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_7_UNION
 结构说明  : rx_2g_ana_7 寄存器结构定义。地址偏移量:0x190，初值:0x00，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved           : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL_2G      : 1;  /* bit[4]  : 量化器参考电压选择
                                                             0 选择ADC Buffer作为量化器的参考电压源
                                                             1 选择电阻分压作为量化器的参考电压源 */
        unsigned long  GMBIAS_EN_2G       : 1;  /* bit[5]  : OP3是否使用Gm_bias偏置
                                                             0 gmbias模块不使能，OP3使用电流镜偏置
                                                             1 gmbias模块使能，OP3使用gmbias偏置 */
        unsigned long  MODU_DEPTH_CTRL_2G : 1;  /* bit[6]  : 反馈子DAC调制深度控制
                                                             0 调制深度0.5
                                                             1 调制深度0.75 */
        unsigned long  RX_DAC_LP_CTRL_2G  : 1;  /* bit[7]  : 反馈子DAC偏置电流控制
                                                             0 大电流，噪声性能好
                                                             1 小电流，噪声性能差 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_7_UNION;
#define ABB_RX_2G_ANA_7_QT_REF_SEL_2G_START       (4)
#define ABB_RX_2G_ANA_7_QT_REF_SEL_2G_END         (4)
#define ABB_RX_2G_ANA_7_GMBIAS_EN_2G_START        (5)
#define ABB_RX_2G_ANA_7_GMBIAS_EN_2G_END          (5)
#define ABB_RX_2G_ANA_7_MODU_DEPTH_CTRL_2G_START  (6)
#define ABB_RX_2G_ANA_7_MODU_DEPTH_CTRL_2G_END    (6)
#define ABB_RX_2G_ANA_7_RX_DAC_LP_CTRL_2G_START   (7)
#define ABB_RX_2G_ANA_7_RX_DAC_LP_CTRL_2G_END     (7)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_8_UNION
 结构说明  : rx_2g_ana_8 寄存器结构定义。地址偏移量:0x191，初值:0x50，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_2G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 反馈DAC时序提前量最少
                                                          11111 反馈DAC时序提前量最大 */
        unsigned long  CK_CTRL_MODE_2G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00： LTE模式
                                                          01： WDC &amp; X &amp; TDS_A模式
                                                          1x： W &amp; G &amp; TDS_B模式 */
        unsigned long  reserved        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_8_UNION;
#define ABB_RX_2G_ANA_8_CK_CTRL_DATA_2G_START  (0)
#define ABB_RX_2G_ANA_8_CK_CTRL_DATA_2G_END    (4)
#define ABB_RX_2G_ANA_8_CK_CTRL_MODE_2G_START  (5)
#define ABB_RX_2G_ANA_8_CK_CTRL_MODE_2G_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_3G_ANA_6_UNION
 结构说明  : rx_3g_ana_6 寄存器结构定义。地址偏移量:0x195，初值:0x00，宽度:8
 寄存器说明: RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3_3G : 2;  /* bit[2-3]: BWCT_OP3 OP3带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  BWCT_OP2_3G : 2;  /* bit[4-5]: BWCT_OP2 OP2带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  BWCT_OP1_3G : 2;  /* bit[6-7]: BWCT_OP1 OP1带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_6_UNION;
#define ABB_RX_3G_ANA_6_BWCT_OP3_3G_START  (2)
#define ABB_RX_3G_ANA_6_BWCT_OP3_3G_END    (3)
#define ABB_RX_3G_ANA_6_BWCT_OP2_3G_START  (4)
#define ABB_RX_3G_ANA_6_BWCT_OP2_3G_END    (5)
#define ABB_RX_3G_ANA_6_BWCT_OP1_3G_START  (6)
#define ABB_RX_3G_ANA_6_BWCT_OP1_3G_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_3G_ANA_7_UNION
 结构说明  : rx_3g_ana_7 寄存器结构定义。地址偏移量:0x196，初值:0x00，宽度:8
 寄存器说明: RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved           : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL_3G      : 1;  /* bit[4]  : 量化器参考电压选择
                                                             0 选择ADC Buffer作为量化器的参考电压源
                                                             1 选择电阻分压作为量化器的参考电压源 */
        unsigned long  GMBIAS_EN_3G       : 1;  /* bit[5]  : OP3是否使用Gm_bias偏置
                                                             0 gmbias模块不使能，OP3使用电流镜偏置
                                                             1 gmbias模块使能，OP3使用gmbias偏置 */
        unsigned long  MODU_DEPTH_CTRL_3G : 1;  /* bit[6]  : 反馈子DAC调制深度控制
                                                             0 调制深度0.5
                                                             1 调制深度0.75 */
        unsigned long  RX_DAC_LP_CTRL_3G  : 1;  /* bit[7]  : 反馈子DAC偏置电流控制
                                                             0 大电流，噪声性能好
                                                             1 小电流，噪声性能差 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_7_UNION;
#define ABB_RX_3G_ANA_7_QT_REF_SEL_3G_START       (4)
#define ABB_RX_3G_ANA_7_QT_REF_SEL_3G_END         (4)
#define ABB_RX_3G_ANA_7_GMBIAS_EN_3G_START        (5)
#define ABB_RX_3G_ANA_7_GMBIAS_EN_3G_END          (5)
#define ABB_RX_3G_ANA_7_MODU_DEPTH_CTRL_3G_START  (6)
#define ABB_RX_3G_ANA_7_MODU_DEPTH_CTRL_3G_END    (6)
#define ABB_RX_3G_ANA_7_RX_DAC_LP_CTRL_3G_START   (7)
#define ABB_RX_3G_ANA_7_RX_DAC_LP_CTRL_3G_END     (7)


/*****************************************************************************
 结构名    : ABB_RX_3G_ANA_8_UNION
 结构说明  : rx_3g_ana_8 寄存器结构定义。地址偏移量:0x197，初值:0x50，宽度:8
 寄存器说明: RX 3G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_3G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 反馈DAC时序提前量最少
                                                          11111 反馈DAC时序提前量最大 */
        unsigned long  CK_CTRL_MODE_3G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00： LTE模式
                                                          01： WDC &amp; X &amp; TDS_A模式
                                                          1x： W &amp; G &amp; TDS_B模式 */
        unsigned long  reserved        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_8_UNION;
#define ABB_RX_3G_ANA_8_CK_CTRL_DATA_3G_START  (0)
#define ABB_RX_3G_ANA_8_CK_CTRL_DATA_3G_END    (4)
#define ABB_RX_3G_ANA_8_CK_CTRL_MODE_3G_START  (5)
#define ABB_RX_3G_ANA_8_CK_CTRL_MODE_3G_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_4G_ANA_6_UNION
 结构说明  : rx_4g_ana_6 寄存器结构定义。地址偏移量:0x19B，初值:0xA8，宽度:8
 寄存器说明: RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr56。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3_4G : 2;  /* bit[2-3]: BWCT_OP3 OP3带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  BWCT_OP2_4G : 2;  /* bit[4-5]: BWCT_OP2 OP2带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  BWCT_OP1_4G : 2;  /* bit[6-7]: BWCT_OP1 OP1带宽控制
                                                      1x： LTE模式
                                                      01： WDC &amp; X 模式
                                                      00： W &amp; G模式 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_6_UNION;
#define ABB_RX_4G_ANA_6_BWCT_OP3_4G_START  (2)
#define ABB_RX_4G_ANA_6_BWCT_OP3_4G_END    (3)
#define ABB_RX_4G_ANA_6_BWCT_OP2_4G_START  (4)
#define ABB_RX_4G_ANA_6_BWCT_OP2_4G_END    (5)
#define ABB_RX_4G_ANA_6_BWCT_OP1_4G_START  (6)
#define ABB_RX_4G_ANA_6_BWCT_OP1_4G_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_4G_ANA_7_UNION
 结构说明  : rx_4g_ana_7 寄存器结构定义。地址偏移量:0x19C，初值:0x00，宽度:8
 寄存器说明: RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr57。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved           : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL_4G      : 1;  /* bit[4]  : 量化器参考电压选择
                                                             0 选择ADC Buffer作为量化器的参考电压源
                                                             1 选择电阻分压作为量化器的参考电压源 */
        unsigned long  GMBIAS_EN_4G       : 1;  /* bit[5]  : OP3是否使用Gm_bias偏置
                                                             0 gmbias模块不使能，OP3使用电流镜偏置
                                                             1 gmbias模块使能，OP3使用gmbias偏置 */
        unsigned long  MODU_DEPTH_CTRL_4G : 1;  /* bit[6]  : 反馈子DAC调制深度控制
                                                             0 调制深度0.5
                                                             1 调制深度0.75 */
        unsigned long  RX_DAC_LP_CTRL_4G  : 1;  /* bit[7]  : 反馈子DAC偏置电流控制
                                                             0 大电流，噪声性能好
                                                             1 小电流，噪声性能差 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_7_UNION;
#define ABB_RX_4G_ANA_7_QT_REF_SEL_4G_START       (4)
#define ABB_RX_4G_ANA_7_QT_REF_SEL_4G_END         (4)
#define ABB_RX_4G_ANA_7_GMBIAS_EN_4G_START        (5)
#define ABB_RX_4G_ANA_7_GMBIAS_EN_4G_END          (5)
#define ABB_RX_4G_ANA_7_MODU_DEPTH_CTRL_4G_START  (6)
#define ABB_RX_4G_ANA_7_MODU_DEPTH_CTRL_4G_END    (6)
#define ABB_RX_4G_ANA_7_RX_DAC_LP_CTRL_4G_START   (7)
#define ABB_RX_4G_ANA_7_RX_DAC_LP_CTRL_4G_END     (7)


/*****************************************************************************
 结构名    : ABB_RX_4G_ANA_8_UNION
 结构说明  : rx_4g_ana_8 寄存器结构定义。地址偏移量:0x19D，初值:0x10，宽度:8
 寄存器说明: RX 4G配置寄存器，经过线控逻辑后送至reg_analog_wr58。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_4G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 反馈DAC时序提前量最少
                                                          11111 反馈DAC时序提前量最大 */
        unsigned long  CK_CTRL_MODE_4G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00： LTE模式
                                                          01： WDC &amp; X &amp; TDS_A模式
                                                          1x： W &amp; G &amp; TDS_B模式 */
        unsigned long  reserved        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_8_UNION;
#define ABB_RX_4G_ANA_8_CK_CTRL_DATA_4G_START  (0)
#define ABB_RX_4G_ANA_8_CK_CTRL_DATA_4G_END    (4)
#define ABB_RX_4G_ANA_8_CK_CTRL_MODE_4G_START  (5)
#define ABB_RX_4G_ANA_8_CK_CTRL_MODE_4G_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_6_UNION
 结构说明  : rx_tds_ana_6 寄存器结构定义。地址偏移量:0x1A1，初值:0x00，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr56。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3_TDS : 2;  /* bit[2-3]: BWCT_OP3 OP3带宽控制
                                                       1x： LTE模式
                                                       01： WDC &amp; X 模式
                                                       00： W &amp; G模式 */
        unsigned long  BWCT_OP2_TDS : 2;  /* bit[4-5]: BWCT_OP2 OP2带宽控制
                                                       1x： LTE模式
                                                       01： WDC &amp; X 模式
                                                       00： W &amp; G模式 */
        unsigned long  BWCT_OP1_TDS : 2;  /* bit[6-7]: BWCT_OP1 OP1带宽控制
                                                       1x： LTE模式
                                                       01： WDC &amp; X 模式
                                                       00： W &amp; G模式 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_6_UNION;
#define ABB_RX_TDS_ANA_6_BWCT_OP3_TDS_START  (2)
#define ABB_RX_TDS_ANA_6_BWCT_OP3_TDS_END    (3)
#define ABB_RX_TDS_ANA_6_BWCT_OP2_TDS_START  (4)
#define ABB_RX_TDS_ANA_6_BWCT_OP2_TDS_END    (5)
#define ABB_RX_TDS_ANA_6_BWCT_OP1_TDS_START  (6)
#define ABB_RX_TDS_ANA_6_BWCT_OP1_TDS_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_7_UNION
 结构说明  : rx_tds_ana_7 寄存器结构定义。地址偏移量:0x1A2，初值:0x00，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr57。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved            : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL_TDS      : 1;  /* bit[4]  : 量化器参考电压选择
                                                              0 选择ADC Buffer作为量化器的参考电压源
                                                              1 选择电阻分压作为量化器的参考电压源 */
        unsigned long  GMBIAS_EN_TDS       : 1;  /* bit[5]  : OP3是否使用Gm_bias偏置
                                                              0 gmbias模块不使能，OP3使用电流镜偏置
                                                              1 gmbias模块使能，OP3使用gmbias偏置 */
        unsigned long  MODU_DEPTH_CTRL_TDS : 1;  /* bit[6]  : 反馈子DAC调制深度控制
                                                              0 调制深度0.5
                                                              1 调制深度0.75 */
        unsigned long  RX_DAC_LP_CTRL_TDS  : 1;  /* bit[7]  : 反馈子DAC偏置电流控制
                                                              0 大电流，噪声性能好
                                                              1 小电流，噪声性能差 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_7_UNION;
#define ABB_RX_TDS_ANA_7_QT_REF_SEL_TDS_START       (4)
#define ABB_RX_TDS_ANA_7_QT_REF_SEL_TDS_END         (4)
#define ABB_RX_TDS_ANA_7_GMBIAS_EN_TDS_START        (5)
#define ABB_RX_TDS_ANA_7_GMBIAS_EN_TDS_END          (5)
#define ABB_RX_TDS_ANA_7_MODU_DEPTH_CTRL_TDS_START  (6)
#define ABB_RX_TDS_ANA_7_MODU_DEPTH_CTRL_TDS_END    (6)
#define ABB_RX_TDS_ANA_7_RX_DAC_LP_CTRL_TDS_START   (7)
#define ABB_RX_TDS_ANA_7_RX_DAC_LP_CTRL_TDS_END     (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_8_UNION
 结构说明  : rx_tds_ana_8 寄存器结构定义。地址偏移量:0x1A3，初值:0x50，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后送至reg_analog_wr58。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_TDS : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                           00000 反馈DAC时序提前量最少
                                                           11111 反馈DAC时序提前量最大 */
        unsigned long  CK_CTRL_MODE_TDS : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                           00： LTE模式
                                                           01： WDC &amp; X &amp; TDS_A模式
                                                           1x： W &amp; G &amp; TDS_B模式 */
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_8_UNION;
#define ABB_RX_TDS_ANA_8_CK_CTRL_DATA_TDS_START  (0)
#define ABB_RX_TDS_ANA_8_CK_CTRL_DATA_TDS_END    (4)
#define ABB_RX_TDS_ANA_8_CK_CTRL_MODE_TDS_START  (5)
#define ABB_RX_TDS_ANA_8_CK_CTRL_MODE_TDS_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_6_UNION
 结构说明  : rx_idle_ana_6 寄存器结构定义。地址偏移量:0x1A7，初值:0x00，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr56。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved      : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3_IDLE : 2;  /* bit[2-3]: BWCT_OP3 OP3带宽控制
                                                        1x： LTE模式
                                                        01： WDC &amp; X 模式
                                                        00： W &amp; G模式 */
        unsigned long  BWCT_OP2_IDLE : 2;  /* bit[4-5]: BWCT_OP2 OP2带宽控制
                                                        1x： LTE模式
                                                        01： WDC &amp; X 模式
                                                        00： W &amp; G模式 */
        unsigned long  BWCT_OP1_IDLE : 2;  /* bit[6-7]: BWCT_OP1 OP1带宽控制
                                                        1x： LTE模式
                                                        01： WDC &amp; X 模式
                                                        00： W &amp; G模式 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_6_UNION;
#define ABB_RX_IDLE_ANA_6_BWCT_OP3_IDLE_START  (2)
#define ABB_RX_IDLE_ANA_6_BWCT_OP3_IDLE_END    (3)
#define ABB_RX_IDLE_ANA_6_BWCT_OP2_IDLE_START  (4)
#define ABB_RX_IDLE_ANA_6_BWCT_OP2_IDLE_END    (5)
#define ABB_RX_IDLE_ANA_6_BWCT_OP1_IDLE_START  (6)
#define ABB_RX_IDLE_ANA_6_BWCT_OP1_IDLE_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_7_UNION
 结构说明  : rx_idle_ana_7 寄存器结构定义。地址偏移量:0x1A8，初值:0x00，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr57。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved             : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL_IDLE      : 1;  /* bit[4]  : 量化器参考电压选择
                                                               0 选择ADC Buffer作为量化器的参考电压源
                                                               1 选择电阻分压作为量化器的参考电压源 */
        unsigned long  GMBIAS_EN_IDLE       : 1;  /* bit[5]  : OP3是否使用Gm_bias偏置
                                                               0 gmbias模块不使能，OP3使用电流镜偏置
                                                               1 gmbias模块使能，OP3使用gmbias偏置 */
        unsigned long  MODU_DEPTH_CTRL_IDLE : 1;  /* bit[6]  : 反馈子DAC调制深度控制
                                                               0 调制深度0.5
                                                               1 调制深度0.75 */
        unsigned long  RX_DAC_LP_CTRL_IDLE  : 1;  /* bit[7]  : 反馈子DAC偏置电流控制
                                                               0 大电流，噪声性能好
                                                               1 小电流，噪声性能差 */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_7_UNION;
#define ABB_RX_IDLE_ANA_7_QT_REF_SEL_IDLE_START       (4)
#define ABB_RX_IDLE_ANA_7_QT_REF_SEL_IDLE_END         (4)
#define ABB_RX_IDLE_ANA_7_GMBIAS_EN_IDLE_START        (5)
#define ABB_RX_IDLE_ANA_7_GMBIAS_EN_IDLE_END          (5)
#define ABB_RX_IDLE_ANA_7_MODU_DEPTH_CTRL_IDLE_START  (6)
#define ABB_RX_IDLE_ANA_7_MODU_DEPTH_CTRL_IDLE_END    (6)
#define ABB_RX_IDLE_ANA_7_RX_DAC_LP_CTRL_IDLE_START   (7)
#define ABB_RX_IDLE_ANA_7_RX_DAC_LP_CTRL_IDLE_END     (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_8_UNION
 结构说明  : rx_idle_ana_8 寄存器结构定义。地址偏移量:0x1A9，初值:0x50，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后送至reg_analog_wr58。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_IDLE : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                            00000 反馈DAC时序提前量最少
                                                            11111 反馈DAC时序提前量最大 */
        unsigned long  CK_CTRL_MODE_IDLE : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                            00： LTE模式
                                                            01： WDC &amp; X &amp; TDS_A模式
                                                            1x： W &amp; G &amp; TDS_B模式 */
        unsigned long  reserved          : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_8_UNION;
#define ABB_RX_IDLE_ANA_8_CK_CTRL_DATA_IDLE_START  (0)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_DATA_IDLE_END    (4)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_MODE_IDLE_START  (5)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_MODE_IDLE_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_LINE_SEL_UNION
 结构说明  : ch0_line_sel 寄存器结构定义。地址偏移量:0x1D0，初值:0x07，宽度:8
 寄存器说明: 线控强制配置使能。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_sel : 1;  /* bit[0]  : RXA通道线控选择
                                                         0：tie to 0
                                                         1：from line ctrl */
        unsigned long  ch0_rxb_en_sel : 1;  /* bit[1]  : RXB通道线控选择
                                                         0：tie to 0
                                                         1：from line ctrl */
        unsigned long  ch0_tx_en_sel  : 1;  /* bit[2]  : TX通道线控选择
                                                         0：tie to 0
                                                         1：from line ctrl */
        unsigned long  reserved       : 5;  /* bit[3-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_SEL_UNION;
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_START  (0)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_END    (0)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_START  (1)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_END    (1)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_START   (2)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_END     (2)


/*****************************************************************************
 结构名    : ABB_CH0_LINE_CFG_UNION
 结构说明  : ch0_line_cfg 寄存器结构定义。地址偏移量:0x1D1，初值:0x00，宽度:8
 寄存器说明: 线控强制配置值。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_line_ctrl_mode_cfg : 3;  /* bit[0-2]: 线控信号CH0_LINE_CTRL_MODE强制配置值
                                                                 0：IDLE
                                                                 1：G模
                                                                 2：W模
                                                                 3：LTE模
                                                                 4：TDS模
                                                                 5：ET模式
                                                                 6：APT模式
                                                                 7：CA模式 */
        unsigned long  ch0_line_ctrl_mode_sel : 1;  /* bit[3]  : 线控信号CH0_LINE_CTRL_MODE强制配置使能 */
        unsigned long  ch0_blk_en_cfg         : 1;  /* bit[4]  : 线控信号CH0_RXA_BLK_EN, CH0_RXB_BLK_EN强制配置值 */
        unsigned long  ch0_blk_en_sel         : 1;  /* bit[5]  : 线控信号CH0_RXA_BLK_EN, CH0_RXB_BLK_EN强制配置使能 */
        unsigned long  ch0_cfr_en_cfg         : 1;  /* bit[6]  : 线控信号CH0_CFR_EN强制配置值 */
        unsigned long  ch0_cfr_en_sel         : 1;  /* bit[7]  : 线控信号CH0_CFR_EN强制配置使能 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_CFG_UNION;
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_START  (3)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_END    (3)
#define ABB_CH0_LINE_CFG_ch0_blk_en_cfg_START          (4)
#define ABB_CH0_LINE_CFG_ch0_blk_en_cfg_END            (4)
#define ABB_CH0_LINE_CFG_ch0_blk_en_sel_START          (5)
#define ABB_CH0_LINE_CFG_ch0_blk_en_sel_END            (5)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_cfg_START          (6)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_cfg_END            (6)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_sel_START          (7)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_sel_END            (7)


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
        unsigned long  ch0_ee_clk_sel  : 1;  /* bit[1]  : 干扰检测自动门控使能：
                                                          0：使能
                                                          1：不使能 */
        unsigned long  ch0_cfr_clk_sel : 1;  /* bit[2]  : CFR自动门控使能：
                                                          0：使能
                                                          1：不使能 */
        unsigned long  reserved        : 5;  /* bit[3-7]: Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CLK_SEL_UNION;
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_START  (0)
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_END    (0)
#define ABB_CH0_CLK_SEL_ch0_ee_clk_sel_START   (1)
#define ABB_CH0_CLK_SEL_ch0_ee_clk_sel_END     (1)
#define ABB_CH0_CLK_SEL_ch0_cfr_clk_sel_START  (2)
#define ABB_CH0_CLK_SEL_ch0_cfr_clk_sel_END    (2)


/*****************************************************************************
 结构名    : ABB_CH0_LINE_RPT0_UNION
 结构说明  : ch0_line_rpt0 寄存器结构定义。地址偏移量:0x1F0，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_rpt : 1;  /* bit[0]  : RXA_EN线控状态上报 */
        unsigned long  ch0_rxb_en_rpt : 1;  /* bit[1]  : RXB_EN线控状态上报 */
        unsigned long  ch0_tx_en_rpt  : 1;  /* bit[2]  : TX_EN线控状态上报 */
        unsigned long  reserved       : 5;  /* bit[3-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT0_UNION;
#define ABB_CH0_LINE_RPT0_ch0_rxa_en_rpt_START  (0)
#define ABB_CH0_LINE_RPT0_ch0_rxa_en_rpt_END    (0)
#define ABB_CH0_LINE_RPT0_ch0_rxb_en_rpt_START  (1)
#define ABB_CH0_LINE_RPT0_ch0_rxb_en_rpt_END    (1)
#define ABB_CH0_LINE_RPT0_ch0_tx_en_rpt_START   (2)
#define ABB_CH0_LINE_RPT0_ch0_tx_en_rpt_END     (2)


/*****************************************************************************
 结构名    : ABB_CH0_LINE_RPT1_UNION
 结构说明  : ch0_line_rpt1 寄存器结构定义。地址偏移量:0x1F1，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_line_ctrl_mode_rpt : 3;  /* bit[0-2]: 线控信号ch0_LINE_CTRL_MODE状态上报
                                                                 0：IDLE
                                                                 1：G模
                                                                 2：W模
                                                                 3：LTE模
                                                                 4：TDS模
                                                                 5：ET模式
                                                                 6：APT模式
                                                                 7：CA模式 */
        unsigned long  reserved_0             : 1;  /* bit[3]  : Reserved */
        unsigned long  ch0_rxa_blk_en_rpt     : 1;  /* bit[4]  : RXA_BLK_EN线控状态上报 */
        unsigned long  ch0_rxb_blk_en_rpt     : 1;  /* bit[5]  : RXB_BLK_EN线控状态上报 */
        unsigned long  ch0_cfr_en_rpt         : 1;  /* bit[6]  : CFR_EN线控状态上报 */
        unsigned long  reserved_1             : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT1_UNION;
#define ABB_CH0_LINE_RPT1_ch0_line_ctrl_mode_rpt_START  (0)
#define ABB_CH0_LINE_RPT1_ch0_line_ctrl_mode_rpt_END    (2)
#define ABB_CH0_LINE_RPT1_ch0_rxa_blk_en_rpt_START      (4)
#define ABB_CH0_LINE_RPT1_ch0_rxa_blk_en_rpt_END        (4)
#define ABB_CH0_LINE_RPT1_ch0_rxb_blk_en_rpt_START      (5)
#define ABB_CH0_LINE_RPT1_ch0_rxb_blk_en_rpt_END        (5)
#define ABB_CH0_LINE_RPT1_ch0_cfr_en_rpt_START          (6)
#define ABB_CH0_LINE_RPT1_ch0_cfr_en_rpt_END            (6)


/*****************************************************************************
 结构名    : ABB_CH0_RX_MODE_RPT_UNION
 结构说明  : ch0_rx_mode_rpt 寄存器结构定义。地址偏移量:0x1F2，初值:0x00，宽度:8
 寄存器说明: RX数字工作模式上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_rpt : 1;  /* bit[0]  : RX通道补偿滤波器补偿固定系数选择上报：
                                                              0：固定系数1
                                                              1：固定系数2 */
        unsigned long  ch0_rx_comp_fix_rpt : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制上报：
                                                              0：系数不固定，由寄存器配置
                                                              1：系数固定 */
        unsigned long  ch0_rx_hb_bp_rpt    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制上报：
                                                              0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                              1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch0_rx_rate_rpt     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                  2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                        /TDS_B/4G_C,        /4G_B,
                                                              00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认)
                                                              others：reserved */
        unsigned long  ch0_rx_mode_dig_rpt : 3;  /* bit[5-7]: RX通道模式控制：
                                                              000：2G(默认)
                                                              001：3G_SCReserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_MODE_RPT_UNION;
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_sel_rpt_START  (0)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_sel_rpt_END    (0)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_fix_rpt_START  (1)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_fix_rpt_END    (1)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_hb_bp_rpt_START     (2)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_hb_bp_rpt_END       (2)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_rate_rpt_START      (3)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_rate_rpt_END        (4)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_mode_dig_rpt_START  (5)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_mode_dig_rpt_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_MODE_RPT_UNION
 结构说明  : ch0_tx_mode_rpt 寄存器结构定义。地址偏移量:0x1F3，初值:0x02，宽度:8
 寄存器说明: TX数字工作模式上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_rpt  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制上报：
                                                              0：不bypass(默认)
                                                              1：bypass */
        unsigned long  ch0_tx_hb_bp_rpt    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制上报：
                                                              0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
                                                              1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认) */
        unsigned long  ch0_tx_rate_rpt     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制上报：
                                                                   2G,     3G,     4G,      TDS,      CA
                                                                  (78M) (153.6M) (307.2M) (153.6M) (614.4M)
                                                              0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(默认)
                                                              1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                              2：-------,--------,15.36MHz,--------,--------
                                                              3：-------,--------, 7.68MHz,--------,--------
                                                              4：-------,--------, 3.84MHz,--------,--------
                                                              Others：Reserved */
        unsigned long  ch0_tx_mode_dig_rpt : 3;  /* bit[5-7]: TX通道模式控制：
                                                              000：2G(默认)
                                                              001：3G
                                                              010：4G
                                                              011：TDS
                                                              Reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_MODE_RPT_UNION;
#define ABB_CH0_TX_MODE_RPT_ch0_tx_comp_bp_rpt_START   (0)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_comp_bp_rpt_END     (0)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_hb_bp_rpt_START     (1)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_hb_bp_rpt_END       (1)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_rate_rpt_START      (2)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_rate_rpt_END        (4)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_mode_dig_rpt_START  (5)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_mode_dig_rpt_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_RX_STATE_RPT_UNION
 结构说明  : ch0_rx_state_rpt 寄存器结构定义。地址偏移量:0x1F4，初值:0x00，宽度:8
 寄存器说明: RX数字工作状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_aclk_rpt      : 1;  /* bit[0]: RX通道模拟随路时钟 */
        unsigned long  ch0_rx_clk_rpt       : 1;  /* bit[1]: RX通道输出数字随路时钟 */
        unsigned long  ch0_rx_vld_rpt       : 1;  /* bit[2]: RX通道输出数据有效指示信号 */
        unsigned long  ch0_rxa_data_rpt     : 1;  /* bit[3]: RXA通道输出数据翻转指示信号 */
        unsigned long  ch0_rxa_overflow_rpt : 1;  /* bit[4]: RXA通道数据削顶指示信号 */
        unsigned long  ch0_rxb_data_rpt     : 1;  /* bit[5]: RXB通道输出数据翻转指示信号 */
        unsigned long  ch0_rxb_overflow_rpt : 1;  /* bit[6]: RXB通道数据削顶指示信号 */
        unsigned long  reserved             : 1;  /* bit[7]: Reserved */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_STATE_RPT_UNION;
#define ABB_CH0_RX_STATE_RPT_ch0_rx_aclk_rpt_START       (0)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_aclk_rpt_END         (0)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_clk_rpt_START        (1)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_clk_rpt_END          (1)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_vld_rpt_START        (2)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_vld_rpt_END          (2)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_data_rpt_START      (3)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_data_rpt_END        (3)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_overflow_rpt_START  (4)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_overflow_rpt_END    (4)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_data_rpt_START      (5)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_data_rpt_END        (5)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_overflow_rpt_START  (6)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_overflow_rpt_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_TX_STATE_RPT_UNION
 结构说明  : ch0_tx_state_rpt 寄存器结构定义。地址偏移量:0x1F5，初值:0x00，宽度:8
 寄存器说明: TX数字工作状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_aclk_rpt     : 1;  /* bit[0]: TX通道模拟随路时钟 */
        unsigned long  ch0_tx_dclk_rpt     : 1;  /* bit[1]: TX通道输入数字随路时钟 */
        unsigned long  ch0_tx_vld_rpt      : 1;  /* bit[2]: TX通输入数据有效指示信号 */
        unsigned long  ch0_tx_clk_rpt      : 1;  /* bit[3]: TX通道数字主工作时钟 */
        unsigned long  ch0_tx_data_rpt     : 1;  /* bit[4]: TX通道数据翻转指示信号 */
        unsigned long  ch0_tx_overflow_rpt : 1;  /* bit[5]: TX通道数据削顶指示信号 */
        unsigned long  ch0_tx_fifo_wfull   : 1;  /* bit[6]: TX通道FIFO写满状态 */
        unsigned long  ch0_tx_fifo_rempty  : 1;  /* bit[7]: TX通道FIFO读空状态 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_STATE_RPT_UNION;
#define ABB_CH0_TX_STATE_RPT_ch0_tx_aclk_rpt_START      (0)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_aclk_rpt_END        (0)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_dclk_rpt_START      (1)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_dclk_rpt_END        (1)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_vld_rpt_START       (2)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_vld_rpt_END         (2)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_clk_rpt_START       (3)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_clk_rpt_END         (3)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_data_rpt_START      (4)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_data_rpt_END        (4)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_overflow_rpt_START  (5)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_overflow_rpt_END    (5)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_wfull_START    (6)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_wfull_END      (6)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_rempty_START   (7)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_rempty_END     (7)


/*****************************************************************************
 结构名    : ABB_RXB_CH_SEL_UNION
 结构说明  : RXB_CH_SEL 寄存器结构定义。地址偏移量:0x1F6，初值:0x00，宽度:8
 寄存器说明: RXB通道选择。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxb_ch_sel : 1;  /* bit[0]  : RXB通道选择。
                                                     0：选择CH0；
                                                     1：选择CH1。. */
        unsigned long  reserved   : 7;  /* bit[1-7]: 保留。 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RXB_CH_SEL_UNION;
#define ABB_RXB_CH_SEL_rxb_ch_sel_START  (0)
#define ABB_RXB_CH_SEL_rxb_ch_sel_END    (0)


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
        unsigned long  reserved       : 5;  /* bit[3-7]: 保留。 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TDS_RX_DLY_UNION;
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_START  (0)
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_END    (2)


/*****************************************************************************
 结构名    : ABB_CH0_CFR_PDET_THR2_UNION
 结构说明  : CH0_CFR_PDET_THR2 寄存器结构定义。地址偏移量:0x203，初值:0x00，宽度:8
 寄存器说明: 通道0 CFR配置寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfr_pdet_thr2 : 2;  /* bit[0-1]: 通道0 CFR峰值检测门限值低bit[17:16]。 */
        unsigned long  reserved          : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CFR_PDET_THR2_UNION;
#define ABB_CH0_CFR_PDET_THR2_ch0_cfr_pdet_thr2_START  (0)
#define ABB_CH0_CFR_PDET_THR2_ch0_cfr_pdet_thr2_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_I_EA3_UNION
 结构说明  : CH0_RXA_I_EA3 寄存器结构定义。地址偏移量:0x207，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_ea3 : 2;  /* bit[0-1]: 通道0干扰检测RXA通道I路节点A能量统计值bit[25:24]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_EA3_UNION;
#define ABB_CH0_RXA_I_EA3_ch0_rxa_i_ea3_START  (0)
#define ABB_CH0_RXA_I_EA3_ch0_rxa_i_ea3_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_I_EC6_UNION
 结构说明  : CH0_RXA_I_EC6 寄存器结构定义。地址偏移量:0x213，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_ec6 : 2;  /* bit[0-1]: 通道0干扰检测RXA通道I路节点C能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_EC6_UNION;
#define ABB_CH0_RXA_I_EC6_ch0_rxa_i_ec6_START  (0)
#define ABB_CH0_RXA_I_EC6_ch0_rxa_i_ec6_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_I_ED6_UNION
 结构说明  : CH0_RXA_I_ED6 寄存器结构定义。地址偏移量:0x21A，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_ed6 : 2;  /* bit[0-1]: 通道0干扰检测RXA通道I路节点D能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_ED6_UNION;
#define ABB_CH0_RXA_I_ED6_ch0_rxa_i_ed6_START  (0)
#define ABB_CH0_RXA_I_ED6_ch0_rxa_i_ed6_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_Q_EA3_UNION
 结构说明  : CH0_RXA_Q_EA3 寄存器结构定义。地址偏移量:0x21E，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_ea3 : 2;  /* bit[0-1]: 通道0干扰检测RXA通道Q路节点A能量统计值bit[25:24]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_EA3_UNION;
#define ABB_CH0_RXA_Q_EA3_ch0_rxa_q_ea3_START  (0)
#define ABB_CH0_RXA_Q_EA3_ch0_rxa_q_ea3_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_Q_EC6_UNION
 结构说明  : CH0_RXA_Q_EC6 寄存器结构定义。地址偏移量:0x22A，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_ec6 : 2;  /* bit[0-1]: 通道0干扰检测RXA通道Q路节点C能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_EC6_UNION;
#define ABB_CH0_RXA_Q_EC6_ch0_rxa_q_ec6_START  (0)
#define ABB_CH0_RXA_Q_EC6_ch0_rxa_q_ec6_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_Q_ED6_UNION
 结构说明  : CH0_RXA_Q_ED6 寄存器结构定义。地址偏移量:0x231，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_ed6 : 2;  /* bit[0-1]: 通道0干扰检测RXA通道Q路节点D能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_ED6_UNION;
#define ABB_CH0_RXA_Q_ED6_ch0_rxa_q_ed6_START  (0)
#define ABB_CH0_RXA_Q_ED6_ch0_rxa_q_ed6_END    (1)


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
 结构名    : ABB_CH0_RXB_I_EA3_UNION
 结构说明  : CH0_RXB_I_EA3 寄存器结构定义。地址偏移量:0x237，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_ea3 : 2;  /* bit[0-1]: 通道0干扰检测RXB通道I路节点A能量统计值bit[25:24]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_EA3_UNION;
#define ABB_CH0_RXB_I_EA3_ch0_rxb_i_ea3_START  (0)
#define ABB_CH0_RXB_I_EA3_ch0_rxb_i_ea3_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_I_EC6_UNION
 结构说明  : CH0_RXB_I_EC6 寄存器结构定义。地址偏移量:0x243，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_ec6 : 2;  /* bit[0-1]: 通道0干扰检测RXB通道I路节点C能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_EC6_UNION;
#define ABB_CH0_RXB_I_EC6_ch0_rxb_i_ec6_START  (0)
#define ABB_CH0_RXB_I_EC6_ch0_rxb_i_ec6_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_I_ED6_UNION
 结构说明  : CH0_RXB_I_ED6 寄存器结构定义。地址偏移量:0x24A，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_ed6 : 2;  /* bit[0-1]: 通道0干扰检测RXB通道I路节点D能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留。 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_ED6_UNION;
#define ABB_CH0_RXB_I_ED6_ch0_rxb_i_ed6_START  (0)
#define ABB_CH0_RXB_I_ED6_ch0_rxb_i_ed6_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_Q_EA3_UNION
 结构说明  : CH0_RXB_Q_EA3 寄存器结构定义。地址偏移量:0x24E，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_ea3 : 2;  /* bit[0-1]: 通道0干扰检测RXB通道Q路节点A能量统计值bit[25:24]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_EA3_UNION;
#define ABB_CH0_RXB_Q_EA3_ch0_rxb_q_ea3_START  (0)
#define ABB_CH0_RXB_Q_EA3_ch0_rxb_q_ea3_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_Q_EC6_UNION
 结构说明  : CH0_RXB_Q_EC6 寄存器结构定义。地址偏移量:0x25A，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_ec6 : 2;  /* bit[0-1]: 通道0干扰检测RXB通道Q路节点C能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_EC6_UNION;
#define ABB_CH0_RXB_Q_EC6_ch0_rxb_q_ec6_START  (0)
#define ABB_CH0_RXB_Q_EC6_ch0_rxb_q_ec6_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_Q_ED6_UNION
 结构说明  : CH0_RXB_Q_ED6 寄存器结构定义。地址偏移量:0x261，初值:0x00，宽度:8
 寄存器说明: 通道0干扰检测上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_ed6 : 2;  /* bit[0-1]: 通道0干扰检测RXB通道Q路节点D能量统计值bit[49:48]。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_ED6_UNION;
#define ABB_CH0_RXB_Q_ED6_ch0_rxb_q_ed6_START  (0)
#define ABB_CH0_RXB_Q_ED6_ch0_rxb_q_ed6_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_C_DIG_1_UNION
 结构说明  : rx_c_dig_1 寄存器结构定义。地址偏移量:0x400，初值:0x04，宽度:8
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
                                                           000：2G(默认)
                                                           001：3G_SCReserved */
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
 结构说明  : rx_c_dig_2 寄存器结构定义。地址偏移量:0x401，初值:0x13，宽度:8
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
 结构说明  : tx_c_dig_1 寄存器结构定义。地址偏移量:0x402，初值:0x02，宽度:8
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
                                                        Reserved */
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
 结构说明  : tx_c_dig_3 寄存器结构定义。地址偏移量:0x404，初值:0x01，宽度:8
 寄存器说明: TX C模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_cfr_bp_c   : 1;  /* bit[0]  : TX通道CFR bypass控制：
                                                        0：不bypass
                                                        1：bypass(默认) */
        unsigned long  tx_flush_en_c : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                        0：不使能
                                                        1：使能 */
        unsigned long  reserved      : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_3_UNION;
#define ABB_TX_C_DIG_3_tx_cfr_bp_c_START    (0)
#define ABB_TX_C_DIG_3_tx_cfr_bp_c_END      (0)
#define ABB_TX_C_DIG_3_tx_flush_en_c_START  (1)
#define ABB_TX_C_DIG_3_tx_flush_en_c_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_1_UNION
 结构说明  : rx_c_ana_1 寄存器结构定义。地址偏移量:0x405，初值:0xF2，宽度:8
 寄存器说明: RX C配置寄存器，经过线控逻辑后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_C  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                        000：DWA
                                                        001：CLA1
                                                        010：CLA2
                                                        011：CLA3
                                                        100：CLA4
                                                        101：CLA5
                                                        110：CLA6
                                                        111：CLA7 */
        unsigned long  RX_MODE_CLK_C : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}组成联合的模式控制：
                                                        000：4G
                                                        001：3G
                                                        010：3G_DC &amp; TDS
                                                        011：2G(默认)
                                                        100：reserved
                                                        101：CDMA */
        unsigned long  DEM_MOD_B1_C  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                        000：DWA
                                                        001：CLA1
                                                        010：CLA2
                                                        011：CLA3
                                                        100：CLA4
                                                        101：CLA5
                                                        110：CLA6
                                                        111：CLA7 */
        unsigned long  RXB_Q_PD_C    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                        0：Power On
                                                        1：Power Down(默认)
                                                        (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_C    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                        0：Power On
                                                        1：Power Down(默认)
                                                        (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_C    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                        0：Power On
                                                        1：Power Down(默认)
                                                        (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_C    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                        0：Power On
                                                        1：Power Down(默认)
                                                        (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_1_UNION;
#define ABB_RX_C_ANA_1_DEM_MOD_B0_C_START   (0)
#define ABB_RX_C_ANA_1_DEM_MOD_B0_C_END     (0)
#define ABB_RX_C_ANA_1_RX_MODE_CLK_C_START  (1)
#define ABB_RX_C_ANA_1_RX_MODE_CLK_C_END    (2)
#define ABB_RX_C_ANA_1_DEM_MOD_B1_C_START   (3)
#define ABB_RX_C_ANA_1_DEM_MOD_B1_C_END     (3)
#define ABB_RX_C_ANA_1_RXB_Q_PD_C_START     (4)
#define ABB_RX_C_ANA_1_RXB_Q_PD_C_END       (4)
#define ABB_RX_C_ANA_1_RXB_I_PD_C_START     (5)
#define ABB_RX_C_ANA_1_RXB_I_PD_C_END       (5)
#define ABB_RX_C_ANA_1_RXA_Q_PD_C_START     (6)
#define ABB_RX_C_ANA_1_RXA_Q_PD_C_END       (6)
#define ABB_RX_C_ANA_1_RXA_I_PD_C_START     (7)
#define ABB_RX_C_ANA_1_RXA_I_PD_C_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_2_UNION
 结构说明  : rx_c_ana_2 寄存器结构定义。地址偏移量:0x406，初值:0xA9，宽度:8
 寄存器说明: RX C配置寄存器，经过线控逻辑后送至reg_analog_wr01。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C : 1;  /* bit[0]  : Mode setting for ADC
                                                    1： CA mode
                                                    0： others */
        unsigned long  reserved  : 1;  /* bit[1]  : Reserved */
        unsigned long  IBCT_QT   : 2;  /* bit[2-3]: Current Seting For Mode
                                                    1x：LTE mode Current
                                                    01：3G_DC &amp; X mode Current
                                                    00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3  : 2;  /* bit[4-5]: Current Seting For Mode
                                                    1x：LTE mode Current
                                                    01：3G_DC &amp; X mode Current
                                                    00：3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1  : 2;  /* bit[6-7]: Current Seting For Mode
                                                    1x：LTE mode Current
                                                    01：3G_DC &amp; X mode Current
                                                    00：3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_2_UNION;
#define ABB_RX_C_ANA_2_RX_MODE_C_START  (0)
#define ABB_RX_C_ANA_2_RX_MODE_C_END    (0)
#define ABB_RX_C_ANA_2_IBCT_QT_START    (2)
#define ABB_RX_C_ANA_2_IBCT_QT_END      (3)
#define ABB_RX_C_ANA_2_IBCT_OP3_START   (4)
#define ABB_RX_C_ANA_2_IBCT_OP3_END     (5)
#define ABB_RX_C_ANA_2_IBCT_OP1_START   (6)
#define ABB_RX_C_ANA_2_IBCT_OP1_END     (7)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_3_UNION
 结构说明  : rx_c_ana_3 寄存器结构定义。地址偏移量:0x407，初值:0x00，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后送至reg_analog_wr53。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1  : 3;  /* bit[0-2]: RX ADC OP1电流控制
                                                   000： 1.0x
                                                   001： 0.8x
                                                   010： 0.6x
                                                   011： 0.4x
                                                   100： 1.8x
                                                   101： 1.6x
                                                   110： 1.4x
                                                   111： 1.2x */
        unsigned long  ITR_OP3  : 3;  /* bit[3-5]: RX ADC OP3电流控制
                                                   000： 1.0x
                                                   001： 0.8x
                                                   010： 0.6x
                                                   011： 0.4x
                                                   100： 1.8x
                                                   101： 1.6x
                                                   110： 1.4x
                                                   111： 1.2x */
        unsigned long  reserved : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_3_UNION;
#define ABB_RX_C_ANA_3_ITR_OP1_START   (0)
#define ABB_RX_C_ANA_3_ITR_OP1_END     (2)
#define ABB_RX_C_ANA_3_ITR_OP3_START   (3)
#define ABB_RX_C_ANA_3_ITR_OP3_END     (5)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_4_UNION
 结构说明  : rx_c_ana_4 寄存器结构定义。地址偏移量:0x408，初值:0x00，宽度:8
 寄存器说明: RX C配置寄存器，经过线控逻辑后送至reg_analog_wr54。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT   : 3;  /* bit[0-2]: RX ADC QT电流控制
                                                   000： 1.0x
                                                   001： 0.8x
                                                   010： 0.6x
                                                   011： 0.4x
                                                   100： 1.8x
                                                   101： 1.6x
                                                   110： 1.4x
                                                   111： 1.2x */
        unsigned long  ITR_DAC  : 3;  /* bit[3-5]: RX ADC 反馈DAC运放电流控制
                                                   000： 1.0x
                                                   001： 0.8x
                                                   010： 0.6x
                                                   011： 0.4x
                                                   100： 1.8x
                                                   101： 1.6x
                                                   110： 1.4x
                                                   111： 1.2x */
        unsigned long  reserved : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_4_UNION;
#define ABB_RX_C_ANA_4_ITR_QT_START    (0)
#define ABB_RX_C_ANA_4_ITR_QT_END      (2)
#define ABB_RX_C_ANA_4_ITR_DAC_START   (3)
#define ABB_RX_C_ANA_4_ITR_DAC_END     (5)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_5_UNION
 结构说明  : rx_c_ana_5 寄存器结构定义。地址偏移量:0x409，初值:0x00，宽度:8
 寄存器说明: RX C配置寄存器，经过线控逻辑后送至reg_analog_wr55。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2  : 3;  /* bit[0-2]: RX ADC OP2电流控制
                                                   000： 1.0x
                                                   001： 0.8x
                                                   010： 0.6x
                                                   011： 0.4x
                                                   100： 1.8x
                                                   101： 1.6x
                                                   110： 1.4x
                                                   111： 1.2x */
        unsigned long  IBCT_OP2 : 2;  /* bit[3-4]: Current Seting For Mode
                                                   1x：LTE mode Current
                                                   01：3G_DC &amp; X mode Current
                                                   00：3G &amp; 2G mode Current */
        unsigned long  reserved : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_5_UNION;
#define ABB_RX_C_ANA_5_ITR_OP2_START   (0)
#define ABB_RX_C_ANA_5_ITR_OP2_END     (2)
#define ABB_RX_C_ANA_5_IBCT_OP2_START  (3)
#define ABB_RX_C_ANA_5_IBCT_OP2_END    (4)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_6_UNION
 结构说明  : rx_c_ana_6 寄存器结构定义。地址偏移量:0x40A，初值:0x44，宽度:8
 寄存器说明: RX C配置寄存器，经过线控逻辑后送至reg_analog_wr56。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3 : 2;  /* bit[2-3]: BWCT_OP3 OP3带宽控制
                                                   1x： LTE模式
                                                   01： WDC &amp; X 模式
                                                   00： W &amp; G模式 */
        unsigned long  BWCT_OP2 : 2;  /* bit[4-5]: BWCT_OP2 OP2带宽控制
                                                   1x： LTE模式
                                                   01： WDC &amp; X 模式
                                                   00： W &amp; G模式 */
        unsigned long  BWCT_OP1 : 2;  /* bit[6-7]: BWCT_OP1 OP1带宽控制
                                                   1x： LTE模式
                                                   01： WDC &amp; X 模式
                                                   00： W &amp; G模式 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_6_UNION;
#define ABB_RX_C_ANA_6_BWCT_OP3_START  (2)
#define ABB_RX_C_ANA_6_BWCT_OP3_END    (3)
#define ABB_RX_C_ANA_6_BWCT_OP2_START  (4)
#define ABB_RX_C_ANA_6_BWCT_OP2_END    (5)
#define ABB_RX_C_ANA_6_BWCT_OP1_START  (6)
#define ABB_RX_C_ANA_6_BWCT_OP1_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_7_UNION
 结构说明  : rx_c_ana_7 寄存器结构定义。地址偏移量:0x40B，初值:0x00，宽度:8
 寄存器说明: RX C配置寄存器，经过线控逻辑后送至reg_analog_wr57。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved        : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL      : 1;  /* bit[4]  : 量化器参考电压选择
                                                          0 选择ADC Buffer作为量化器的参考电压源
                                                          1 选择电阻分压作为量化器的参考电压源 */
        unsigned long  GMBIAS_EN       : 1;  /* bit[5]  : OP3是否使用Gm_bias偏置
                                                          0 gmbias模块不使能，OP3使用电流镜偏置
                                                          1 gmbias模块使能，OP3使用gmbias偏置 */
        unsigned long  MODU_DEPTH_CTRL : 1;  /* bit[6]  : 反馈子DAC调制深度控制
                                                          0 调制深度0.5
                                                          1 调制深度0.75 */
        unsigned long  RX_DAC_LP_CTRL  : 1;  /* bit[7]  : 反馈子DAC偏置电流控制
                                                          0 大电流，噪声性能好
                                                          1 小电流，噪声性能差 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_7_UNION;
#define ABB_RX_C_ANA_7_QT_REF_SEL_START       (4)
#define ABB_RX_C_ANA_7_QT_REF_SEL_END         (4)
#define ABB_RX_C_ANA_7_GMBIAS_EN_START        (5)
#define ABB_RX_C_ANA_7_GMBIAS_EN_END          (5)
#define ABB_RX_C_ANA_7_MODU_DEPTH_CTRL_START  (6)
#define ABB_RX_C_ANA_7_MODU_DEPTH_CTRL_END    (6)
#define ABB_RX_C_ANA_7_RX_DAC_LP_CTRL_START   (7)
#define ABB_RX_C_ANA_7_RX_DAC_LP_CTRL_END     (7)


/*****************************************************************************
 结构名    : ABB_RX_C_ANA_8_UNION
 结构说明  : rx_c_ana_8 寄存器结构定义。地址偏移量:0x40C，初值:0x30，宽度:8
 寄存器说明: RX C配置寄存器，经过线控逻辑后送至reg_analog_wr58。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                       00000 反馈DAC时序提前量最少
                                                       11111 反馈DAC时序提前量最大 */
        unsigned long  CK_CTRL_MODE : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                       00： LTE模式
                                                       01： WDC &amp; X &amp; TDS_A模式
                                                       1x： W &amp; G &amp; TDS_B模式 */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_8_UNION;
#define ABB_RX_C_ANA_8_CK_CTRL_DATA_START  (0)
#define ABB_RX_C_ANA_8_CK_CTRL_DATA_END    (4)
#define ABB_RX_C_ANA_8_CK_CTRL_MODE_START  (5)
#define ABB_RX_C_ANA_8_CK_CTRL_MODE_END    (6)


/*****************************************************************************
 结构名    : ABB_TX_C_ANA_1_UNION
 结构说明  : tx_c_ana_1 寄存器结构定义。地址偏移量:0x410，初值:0x1C，宽度:8
 寄存器说明: TX C配置寄存器，经过线控逻辑后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制：
                                                      000：4G &amp; ET &amp; APT
                                                      001：3G &amp; TDS
                                                      010：CA
                                                      011：2G(默认)
                                                      1xx：CDMA */
        unsigned long  TX_Q_PD_A   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                      0：Power On
                                                      1：Power Down(默认)
                                                      (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                      0：Power On
                                                      1：Power Down(默认)
                                                      (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                      00：1分频
                                                      01：2分频(默认)
                                                      10：3分频
                                                      11：4分频 */
        unsigned long  FC          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                      00：5MHz(默认)WSC&amp;GSM&amp;CDMA
                                                      01：10MHz WDC
                                                      10：Reserved
                                                      11：20MHz LTE */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_ANA_1_UNION;
#define ABB_TX_C_ANA_1_TX_MODE_CLK_START  (0)
#define ABB_TX_C_ANA_1_TX_MODE_CLK_END    (1)
#define ABB_TX_C_ANA_1_TX_Q_PD_A_START    (2)
#define ABB_TX_C_ANA_1_TX_Q_PD_A_END      (2)
#define ABB_TX_C_ANA_1_TX_I_PD_A_START    (3)
#define ABB_TX_C_ANA_1_TX_I_PD_A_END      (3)
#define ABB_TX_C_ANA_1_TX_DIV_MODE_START  (4)
#define ABB_TX_C_ANA_1_TX_DIV_MODE_END    (5)
#define ABB_TX_C_ANA_1_FC_START           (6)
#define ABB_TX_C_ANA_1_FC_END             (7)


/*****************************************************************************
 结构名    : ABB_TX_C_ANA_2_UNION
 结构说明  : tx_c_ana_2 寄存器结构定义。地址偏移量:0x411，初值:0x9A，宽度:8
 寄存器说明: TX C配置寄存器，经过线控逻辑后送至reg_analog_wr49。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1 : 2;  /* bit[0-1]: LPF OP1 电流模式调整
                                                           bit0：
                                                           0： 输出级电流正常
                                                           1： 输出级电流加大（适用于5uA偏置）
                                                           bit1：
                                                           0： miller补偿电容正常
                                                           1： miller补偿电容变大（适用于2.5uA偏置）
                                                           LTE:00
                                                           WDC:01
                                                           SC:01
                                                           CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2 : 2;  /* bit[2-3]: LPF OP2 电流模式调整
                                                           00 输出级电流正常
                                                           01 输出级电流加大（适用于5uA偏置）
                                                           10 不建议使用
                                                           11 输出级电流再加大（适用于2.5uA偏置）
                                                           LTE:00
                                                           WDC:01
                                                           SC:01
                                                           CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT : 2;  /* bit[4-5]: LPF 运放偏置电流调整
                                                           运放电流：   op1   op2
                                                           00：         10u   10u
                                                           01：         5u    5u
                                                           10：         2.5u  5u
                                                           11：         2.5u  2.5u
                                                           LTE:00
                                                           Others:01 */
        unsigned long  reserved         : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}组成联合的模式控制,参见TX_MODE_CLK说明。 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_ANA_2_UNION;
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP1_START  (0)
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP1_END    (1)
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP2_START  (2)
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP2_END    (3)
#define ABB_TX_C_ANA_2_LPF_MODE_CURRENT_START  (4)
#define ABB_TX_C_ANA_2_LPF_MODE_CURRENT_END    (5)
#define ABB_TX_C_ANA_2_TX_MODE_CLK_B3_START    (7)
#define ABB_TX_C_ANA_2_TX_MODE_CLK_B3_END      (7)


/*****************************************************************************
 结构名    : ABB_TX_C_ANA_3_UNION
 结构说明  : tx_c_ana_3 寄存器结构定义。地址偏移量:0x412，初值:0x18，宽度:8
 寄存器说明: TX C配置寄存器，经过线控逻辑后送至reg_analog_wr50。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT     : 3;  /* bit[0-2]: LPF OP1 电流模式调整
                                                       000：5u
                                                       001：4u
                                                       010：3u
                                                       011：2u
                                                       100：9u
                                                       101：7u
                                                       110：6u
                                                       111：5u */
        unsigned long  DUM_EN_Q     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                       1：enable(默认)
                                                       0：disable */
        unsigned long  DUM_EN_I     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                       1：enable(默认)
                                                       0：disable */
        unsigned long  reserved     : 2;  /* bit[5-6]: Reserved */
        unsigned long  TX_CLKD_CTRL : 1;  /* bit[7]  : TX 采样时钟沿选择：
                                                       0：正沿(默认)
                                                       1：反沿 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_ANA_3_UNION;
#define ABB_TX_C_ANA_3_TXLPF_CT_START      (0)
#define ABB_TX_C_ANA_3_TXLPF_CT_END        (2)
#define ABB_TX_C_ANA_3_DUM_EN_Q_START      (3)
#define ABB_TX_C_ANA_3_DUM_EN_Q_END        (3)
#define ABB_TX_C_ANA_3_DUM_EN_I_START      (4)
#define ABB_TX_C_ANA_3_DUM_EN_I_END        (4)
#define ABB_TX_C_ANA_3_TX_CLKD_CTRL_START  (7)
#define ABB_TX_C_ANA_3_TX_CLKD_CTRL_END    (7)




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
