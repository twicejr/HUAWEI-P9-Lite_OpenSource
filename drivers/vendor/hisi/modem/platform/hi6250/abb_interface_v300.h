

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __ABB_INTERFACE_V300_H__
#define __ABB_INTERFACE_V300_H__

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
             001：3G_SC
             010：4G
             011：3G_DC
             Others：reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,   3G_SC,    4G,   3G_DC,      
             00： 2.167M,15.36M, 61.44M,30.72M(默认)
             01： 4.33MHz,------,30.72M,------
             10： ------, ------,15.36M,------
             11： ------, ------, 7.68M,------
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      Reserved
   UNION结构:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x0)

/* 寄存器说明：RX 2G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
 bit[6]      RX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[5]      Reserved
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
             000：2G
             001：3G(默认)
             010：4G &amp; ET &amp; APT
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
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
             0：DEM MSB 打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      Reserved
 bit[3:2]    TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2)
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
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_2G_DIG_3_UNION */
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x4)

/* 寄存器说明：RX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G
             001：3G_SC(默认)
             010：4G
             011：3G_DC
             Others：reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,   3G_SC,    4G,   3G_DC,      
             00： 2.167M,15.36M, 61.44M,30.72M(默认)
             01： 4.33MHz,------,30.72M,------
             10： ------, ------,15.36M,------
             11： ------, ------, 7.68M,------
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      Reserved
   UNION结构:  ABB_RX_3G_DIG_1_UNION */
#define ABB_RX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x5)

/* 寄存器说明：RX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
 bit[6]      RX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[5]      Reserved
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
   UNION结构:  ABB_RX_3G_DIG_2_UNION */
#define ABB_RX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x6)

/* 寄存器说明：TX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G
             001：3G(默认)
             010：4G &amp; ET &amp; APT
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_3G_DIG_1_UNION */
#define ABB_TX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x7)

/* 寄存器说明：TX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB 打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      Reserved
 bit[3:2]    TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2)
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_3G_DIG_2_UNION */
#define ABB_TX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x8)

/* 寄存器说明：TX 3G模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_3G_DIG_3_UNION */
#define ABB_TX_3G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x9)

/* 寄存器说明：RX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G
             001：3G_SC
             010：4G(默认)
             011：3G_DC
             Others：reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,   3G_SC,    4G,   3G_DC,      
             00： 2.167M,15.36M, 61.44M,30.72M(默认)
             01： 4.33MHz,------,30.72M,------
             10： ------, ------,15.36M,------
             11： ------, ------, 7.68M,------
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      Reserved
   UNION结构:  ABB_RX_4G_DIG_1_UNION */
#define ABB_RX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0xA)

/* 寄存器说明：RX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
 bit[6]      RX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[5]      Reserved
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
   UNION结构:  ABB_RX_4G_DIG_2_UNION */
#define ABB_RX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0xB)

/* 寄存器说明：TX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT(默认)
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_4G_DIG_1_UNION */
#define ABB_TX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0xC)

/* 寄存器说明：TX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB 打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      Reserved
 bit[3:2]    TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2)
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_4G_DIG_2_UNION */
#define ABB_TX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0xD)

/* 寄存器说明：TX 4G模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_4G_DIG_3_UNION */
#define ABB_TX_4G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0xE)

/* 寄存器说明：RX TDS模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    Reserved
 bit[4:3]    Reserved
 bit[2]      Reserved
 bit[1]      Reserved
 bit[0]      Reserved
   UNION结构:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0xF)

/* 寄存器说明：RX TDS模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
 bit[6]      TX通道CFR bypass控制：
             0：不bypass
             1：bypass(默认)
 bit[5]      RX通道补偿滤波器bypass控制：
             0：不bypass
             1：bypass(默认)
 bit[4]      RX通道增益配置选择：
             00：gain为0.5(默认)
             01：gain为0.75
             10：gain为0.85
             11：Reserved
 bit[3:2]    RXB通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭
 bit[1]      
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
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,      TDS,      CA
                 (78M) (153.6M) (307.2M) (153.6M) (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             3：-------,--------, 7.68MHz,--------,--------
             4：-------,--------, 3.84MHz,--------,--------
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
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      TX通道SDM Dither控制：
             0：不使能
             1：使能
 bit[3]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[2]      TX通道DEM const系数：
             0：2(默认)
             1：4
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
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_TDS_DIG_3_UNION */
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x13)

/* 寄存器说明：TX ET模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT(默认)
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_ET_DIG_1_UNION */
#define ABB_TX_ET_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x14)

/* 寄存器说明：TX ET模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB 打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      Reserved
 bit[3:2]    TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2)
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_ET_DIG_2_UNION */
#define ABB_TX_ET_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x15)

/* 寄存器说明：TX ET模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_ET_DIG_3_UNION */
#define ABB_TX_ET_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x16)

/* 寄存器说明：TX APT模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT(默认)
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_APT_DIG_1_UNION */
#define ABB_TX_APT_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x17)

/* 寄存器说明：TX APT模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB 打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      Reserved
 bit[3:2]    TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2)
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_APT_DIG_2_UNION */
#define ABB_TX_APT_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x18)

/* 寄存器说明：TX APT模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_APT_DIG_3_UNION */
#define ABB_TX_APT_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x19)

/* 寄存器说明：RX CA模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G
             001：3G_SC
             010：4G &amp; ET &amp; APT
             011：3G_DC
             100：TDS
             Others：CA(默认)
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,   3G_SC,  4G,  3G_DC,   TDS,   CA
             00： 2.167M,15.36M,61.44M,30.72M,30.72M,122.88M(默认)
             01： ------,------,30.72M,15.36M,10.24M,------
             10： ------,------,15.36M,------,------,------
             11： ------,------, 7.68M,------,------,------
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      RX通道补偿滤波器补偿固定系数选择：
             0：固定系数1
             1：固定系数2
   UNION结构:  ABB_RX_CA_DIG_1_UNION */
#define ABB_RX_CA_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x1A)

/* 寄存器说明：RX CA模式配置寄存器2，由线控决定是否起作用。
 bit[7:6]    保留
 bit[5]      TX通道CFR bypass控制：
             0：不bypass
             1：bypass(默认)
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
   UNION结构:  ABB_RX_CA_DIG_2_UNION */
#define ABB_RX_CA_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x1B)

/* 寄存器说明：TX CA模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT
             011：TDS
             others：CA(默认)
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,      TDS,      CA
                 (78M) (153.6M) (307.2M) (153.6M) (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2：-------,--------,15.36MHz,--------,--------
             3：-------,--------, 7.68MHz,--------,--------
             4：-------,--------, 3.84MHz,--------,--------
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_CA_DIG_1_UNION */
#define ABB_TX_CA_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x1C)

/* 寄存器说明：TX CA模式配置寄存器2，由线控决定是否起作用。
 bit[7]      TX通道DEM MSB bypass：
             0：DEM MSB打开(默认)
             1：DEM MSB bypass
 bit[6]      TX通道DEM LSB bypass：
             0：DEM LSB 打开(默认)
             1：DEM LSB bypass
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      TX通道SDM Dither控制：
             0：不使能
             1：使能
 bit[3]      TX通道DEM UDDWA_DITH模块使能控制：
             0：不使能
             1：使能
 bit[2]      TX通道DEM const系数：
             0：2(默认)
             1：4
 bit[1]      TX通道I路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭
 bit[0]      TX通道Q路CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭
   UNION结构:  ABB_TX_CA_DIG_2_UNION */
#define ABB_TX_CA_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x1D)

/* 寄存器说明：TX CA模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_CA_DIG_3_UNION */
#define ABB_TX_CA_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x1E)

/* 寄存器说明：RX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G(默认)
             001：3G_SC
             010：4G
             011：3G_DC
             Others：reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,   3G_SC,    4G,   3G_DC,      
             00： 2.167M,15.36M, 61.44M,30.72M(默认)
             01： 4.33MHz,------,30.72M,------
             10： ------, ------,15.36M,------
             11： ------, ------, 7.68M,------
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      Reserved
   UNION结构:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x1F)

/* 寄存器说明：RX IDLE模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
 bit[6]      RX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[5]      Reserved
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
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT(默认)
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz(默认)
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
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
 bit[7]      保留
 bit[6]      1'b0：SDR
             1'b1：DDR
 bit[5]      TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式 
 bit[4]      Reserved
 bit[3:2]    TX通道DEM const系数：默认值2(在模块里*2）
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
 bit[7:2]    保留
 bit[1]      TX与DBB数据接口时序配置：
             1'b0：SDR接口；
             1'b1：DDR接口。
 bit[0]      Reserved
   UNION结构:  ABB_TX_IDLE_DIG_3_UNION */
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x23)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      Reserved
 bit[2:1]    模式控制：
             00：4G 
             01：3G
             10：3G_DC
             11：2G(默认)
 bit[0]      Reserved
   UNION结构:  ABB_RX_2G_ANA_1_UNION */
#define ABB_RX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x24)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后后送至reg_analog_wr01。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_RX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x25)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00: 10MHz(默认)
             01: 20MHz;
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode 时钟控制：
             00: 1分频
             01: 2分频
             10: 3分频
             11: 4分频(默认)
 bit[3]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT
             01：3G 
             10：--
             11：2G(默认)
   UNION结构:  ABB_TX_2G_ANA_1_UNION */
#define ABB_TX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x26)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x27)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      Reserved
 bit[2:1]    模式控制：
             00：4G 
             01：3G
             10：3G_DC
             11：2G(默认)
 bit[0]      Reserved
   UNION结构:  ABB_RX_3G_ANA_1_UNION */
#define ABB_RX_3G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x28)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后后送至reg_analog_wr01。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_RX_3G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x29)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00: 10MHz(默认)
             01: 20MHz;
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode 时钟控制：
             00: 1分频
             01: 2分频(默认)
             10: 3分频
             11: 4分频
 bit[3]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT
             01：3G (默认)
             10：--
             11：2G
   UNION结构:  ABB_TX_3G_ANA_1_UNION */
#define ABB_TX_3G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x2A)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_3G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x2B)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      Reserved
 bit[2:1]    模式控制：
             00：4G (默认)
             01：3G
             10：3G_DC
             11：2G
 bit[0]      Reserved
   UNION结构:  ABB_RX_4G_ANA_1_UNION */
#define ABB_RX_4G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x2C)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后后送至reg_analog_wr01。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_RX_4G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x2D)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00: 10MHz;
             01: 20MHz;(默认)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode 时钟控制：
             00: 1分频(默认)
             01: 2分频
             10: 3分频
             11: 4分频
 bit[3]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT(默认)
             01：3G 
             10：--
             11：2G
   UNION结构:  ABB_TX_4G_ANA_1_UNION */
#define ABB_TX_4G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x2E)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_4G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x2F)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[2:1]    模式控制：
             00：4G &amp; ET &amp; APT
             01：3G
             10：3G_DC &amp; TDS(默认)
             11：2G
 bit[0]      RX DEM Mode Selection,bit 0
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
   UNION结构:  ABB_RX_TDS_ANA_1_UNION */
#define ABB_RX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x30)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后后送至reg_analog_wr01。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_RX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x31)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7]      TX filter截止频率选择：
             0: 10MHz
             1: 20MHz(默认)
 bit[6:5]    TX Mode 时钟控制：
             00: 1分频
             01: 2分频(默认)
             10: 3分频
             11: 4分频
 bit[4]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[3]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[2]      Reserved
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT
             01：3G &amp; TDS(默认)
             10：--
             11：2G
   UNION结构:  ABB_TX_TDS_ANA_1_UNION */
#define ABB_TX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x32)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x33)

/* 寄存器说明：TX ET配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00: 10MHz;
             01: 20MHz;(默认)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode 时钟控制：
             00: 1分频(默认)
             01: 2分频
             10: 3分频
             11: 4分频
 bit[3]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|(WG_TX_EN &amp;&amp; WG_LINE_CONTROL_MODE~
             =ET &amp;&amp; WG_LINE_CONTROL_MODE~=APT) = 1时工作，否则关闭
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT(默认)
             01：3G 
             10：--
             11：2G
   UNION结构:  ABB_TX_ET_ANA_1_UNION */
#define ABB_TX_ET_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x34)

/* 寄存器说明：RX ET配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_ET_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x35)

/* 寄存器说明：TX APT配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00: 10MHz;
             01: 20MHz;(默认)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode 时钟控制：
             00: 1分频
             01: 2分频
             10: 3分频
             11: 4分频(默认)
 bit[3]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1时工作，否则关闭
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT(默认)
             01：3G 
             10：--
             11：2G
   UNION结构:  ABB_TX_APT_ANA_1_UNION */
#define ABB_TX_APT_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x36)

/* 寄存器说明：RX APT配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_APT_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x37)

/* 寄存器说明：RX CA配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[6]      RXA_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭
 bit[5]      RXB_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[4]      RXB_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭
 bit[3]      RX DEM Mode Selection,bit 1
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[2:1]    模式控制：
             00：4G &amp; ET &amp; APT(默认)
             01：3G
             10：3G_DC &amp; TDS
             11：2G
 bit[0]      RX DEM Mode Selection,bit 0
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
   UNION结构:  ABB_RX_CA_ANA_1_UNION */
#define ABB_RX_CA_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x38)

/* 寄存器说明：RX CA配置寄存器，经过线控逻辑后后送至reg_analog_wr01。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_RX_CA_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x39)

/* 寄存器说明：TX CA配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7]      TX filter截止频率选择：
             0: 10MHz
             1: 20MHz(默认)
 bit[6:5]    TX Mode 时钟控制：
             00: 1分频
             01: 2分频
             10: 3分频
             11: 4分频(默认)
 bit[4]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1时工作，否则关闭
 bit[3]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1时工作，否则关闭
 bit[2]      Reserved
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT(默认)
             01：3G &amp; TDS
             10：--
             11：2G
   UNION结构:  ABB_TX_CA_ANA_1_UNION */
#define ABB_TX_CA_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x3A)

/* 寄存器说明：RX CA配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_CA_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x3B)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
 bit[7]      RXA_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[6]      RXA_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[5]      RXB_I ADC Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[4]      RXB_Q ADC Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[3]      Reserved
 bit[2:1]    模式控制：
             00：4G (默认)
             01：3G
             10：3G_DC
             11：2G
 bit[0]      Reserved
   UNION结构:  ABB_RX_IDLE_ANA_1_UNION */
#define ABB_RX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3C)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后后送至reg_analog_wr01。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_RX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
 bit[7:6]    TX filter截止频率选择：
             00: 10MHz;
             01: 20MHz;(默认)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode 时钟控制：
             00: 1分频(默认)
             01: 2分频
             10: 3分频
             11: 4分频
 bit[3]      TX_I DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[2]      TX_Q DAC Power Down控制
             0:Power On
             1:Power Down(默认)
             (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭
 bit[1:0]    模式控制：
             00：4G &amp; ET &amp; APT(默认)
             01：3G 
             10：--
             11：2G
   UNION结构:  ABB_TX_IDLE_ANA_1_UNION */
#define ABB_TX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3E)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后后送至reg_analog_wr49。
   详      述：TBD
   UNION结构 ：无 */
#define ABB_TX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3F)

/* 寄存器说明：version寄存器。
   详      述：由模拟部分决定版本寄存器值
   UNION结构 ：无 */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

/* 寄存器说明：测试模式寄存器。
 bit[7]      保留
 bit[6]      配置的软复位信号：
             0：软件不启动软复位(默认)
             1：软件启动软复位
 bit[5:3]    bit[4:3]测试模式控制：
             00：正常模式(默认)
             01：数字算法逻辑环回模式
             10：RX模拟测试模式(bypass RX数字滤波器)
             11：数字接口环回模式
             bit[5]：reserved
 bit[2:1]    RX模拟测试模式下通道选择：
             00：输出RXA I模拟调制器数据(默认)
             01：输出RXA Q模拟调制器数据
             10：输出RXB I模拟调制器数据
             11：输出RXB Q模拟调制器数据
 bit[0]      保留
   UNION结构:  ABB_CH1_TESTMODE_UNION */
#define ABB_CH1_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x41)

/* 寄存器说明：通道控制寄存器。
 bit[7:1]    保留
 bit[0]      ET/APT通道选择：
             0：选择TX通道I路做ET/APT
             1：选择TX通道Q路做ET/APT
   UNION结构:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x42)

/* 寄存器说明：CFR峰值检测窗长寄存器。
 bit[7:4]    CFR削波因子
 bit[3]      保留
 bit[2]      CFR滤波器选择：
             0：bypass滤波器
             1：不bypass滤波器
 bit[1:0]    CFR峰值检测方式：
             00：单点提峰
             01：区间提峰
             10：滑窗提峰
             11：全部峰值
   UNION结构:  ABB_CH1_CFR_CTRL_UNION */
#define ABB_CH1_CFR_CTRL_ADDR                         (ABB_BASE_ADDR + 0x43)

/* 寄存器说明：线控选择。
 bit[7]      选择RXA_EN线控，0: tie to 0(默认）
             1: from line control
 bit[6]      选择RXB_EN线控，0: tie to 0(默认）
             1: from line control
 bit[5]      选择TX_EN线控，0: tie to 0(默认）
             1: from line control
 bit[4]      选择ET线控模式，0: tie to 0(默认）
             1: from line control
 bit[3]      选择APT线控模式，0: tie to 0(默认）
             1: from line control
 bit[2]      选择4G线控模式，0: tie to 0(默认）
             1: from line control
 bit[1]      选择3G线控模式，0: tie to 0(默认）
             1: from line control
 bit[0]      选择2G线控模式，0: tie to 0(默认）
             1: from line control
   UNION结构:  ABB_CH1_LINE_CTRL_SEL_UNION */
#define ABB_CH1_LINE_CTRL_SEL_ADDR                    (ABB_BASE_ADDR + 0x44)

/* 寄存器说明：RX数字工作模式上报寄存器。
 bit[7:5]    RX通道模式控制：
             000：2G
             001：3G_SC
             010：4G
             011：3G_DC
             Others：reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,   3G_SC,    4G,   3G_DC,      
             00： 2.167M,15.36M, 61.44M,30.72M
             01： 4.33MHz,------,30.72M,------
             10： ------, ------,15.36M,------
             11： ------, ------, 7.68M,------
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      Reserved
   UNION结构:  ABB_CH1_RX_DIG_RPT_UNION */
#define ABB_CH1_RX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0x45)

/* 寄存器说明：TX数字工作模式上报寄存器。
 bit[7:5]    TX通道模式控制：
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass
             1：bypass
   UNION结构:  ABB_CH1_TX_DIG_RPT_UNION */
#define ABB_CH1_TX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0x46)

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
 bit[7:5]    RXA天线BLOCKING上报值,能量大小N
 bit[4:0]    RXA天线BLOCKING上报值，系数，2的M次方
   UNION结构:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x61)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值,能量大小N
 bit[4:0]    RXB天线BLOCKING上报值，系数，2的M次方
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
 bit[7:5]    保留
 bit[4]      Reserved
 bit[3:2]    Reserved
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
 bit[7]      div_en控制分频器bypass信号，0：div_en控制分频器；1：div_en不控制分频器，分频器使能始终为1。.
 bit[6]      切换复位bypass信号。1表示切换复位功能旁路。
 bit[5]      切换门控使能bypass信号。1表示门控使能功能旁路。
 bit[4]      RX通道CIC4/CIC6滤波器选择：
             0: 选择CIC4滤波器
             1: 选择CIC6滤波器
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_DEBUG_DIG4_UNION */
#define ABB_CH1_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0x6F)

/* 寄存器说明：Power Down控制寄存器。
 bit[7:4]    Reserved
 bit[3]      PLLV1 Power Down控制
             0:Power On(默认)
             1:Power Down
 bit[2]      PLLV2 Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[1]      Reserved
 bit[0]      Reserved
   UNION结构:  ABB_CH1_REG_ANALOG_WR02_UNION */
#define ABB_CH1_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0x70)

/* 寄存器说明：数模接口时钟控制寄存器。
 bit[7]      Reserved
 bit[6]      245M输出控制：
             0: 不输出
             1: 输出
 bit[5]      CLK_52M Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[4]      CLK_61D44M Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[3]      TX 采样时钟沿选择：
             0: 正沿
             1: 反沿(默认)
 bit[2:0]    Reserved
   UNION结构:  ABB_CH1_REG_ANALOG_WR03_UNION */
#define ABB_CH1_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0x71)

/* 寄存器说明：Other控制寄存器。
 bit[7:4]    Reserved
 bit[3]      RX ADC自动tuning控制
             0：手动tuning，tuning选择RX_TUNE1,RX_TUNE2,RX_TUNE3的值(默认)
             1：自动tuning，RX通道的calibration值为CAL_VALUE
 bit[2]      TX ADC自动tuning控制
             0：手动tuning，tuning选择TX_TUNE1,TX_TUNE2,TX_TUNE3的值(默认)
             1：自动tuning，TX通道的calibration值为CAL_VALUE
 bit[1]      Reserved
 bit[0]      Calibration enable（默认为0）
             上升沿启动Calibration过程
   UNION结构:  ABB_CH1_REG_ANALOG_WR04_UNION */
#define ABB_CH1_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0x72)

/* 寄存器说明：ADC第一级积分器电容tuning寄存器。
 bit[7]      Reserved
 bit[6:0]    ADC第一级积分器电容tuning
   UNION结构:  ABB_CH1_REG_ANALOG_WR05_UNION */
#define ABB_CH1_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0x73)

/* 寄存器说明：ADC第二级积分器电容tuning寄存器。
 bit[7]      Reserved
 bit[6:0]    ADC第二级积分器电容tuning
   UNION结构:  ABB_CH1_REG_ANALOG_WR06_UNION */
#define ABB_CH1_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0x74)

/* 寄存器说明：ADC第三级积分器电容tuning寄存器。
 bit[7]      Reserved
 bit[6:0]    ADC第三级积分器电容tuning
   UNION结构:  ABB_CH1_REG_ANALOG_WR07_UNION */
#define ABB_CH1_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0x75)

/* 寄存器说明：DAC Tuning控制寄存器。
 bit[7]      Reserved
 bit[6:0]    TX_TUNE1控制信号
   UNION结构:  ABB_CH1_REG_ANALOG_WR08_UNION */
#define ABB_CH1_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0x76)

/* 寄存器说明：DAC Tuning控制寄存器。
 bit[7]      Reserved
 bit[6:0]    TX_TUNE2控制信号
   UNION结构:  ABB_CH1_REG_ANALOG_WR09_UNION */
#define ABB_CH1_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0x77)

/* 寄存器说明：DAC Tuning控制寄存器。
 bit[7]      Reserved
 bit[6:0]    TX_TUNE3控制信号
   UNION结构:  ABB_CH1_REG_ANALOG_WR10_UNION */
#define ABB_CH1_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0x78)

/* 寄存器说明：共模电平控制寄存器。
 bit[7]      Reserved
 bit[6:5]    Reserved
 bit[4]      Reserved
 bit[3]      Reserved
 bit[2:0]    Reserved
   UNION结构:  ABB_CH1_REG_ANALOG_WR38_UNION */
#define ABB_CH1_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0x79)

/* 寄存器说明：DUM控制寄存器。
 bit[7]      RX DEM Mode Selection,bit 2
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[6:2]    Reserved
 bit[1]      TX I channel  dummy logic control signal
             1: enable(默认)
             0: disable
 bit[0]      TX Q channel  dummy logic control signal
             1: enable(默认)
             0: disable
   UNION结构:  ABB_CH1_REG_ANALOG_WR39_UNION */
#define ABB_CH1_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0x7A)

/* 寄存器说明：标志位只读寄存器。
 bit[7]      WPLL的LOCK信号
 bit[6]      GPLL的LOCK信号
 bit[5]      RC Calibration Done信号
 bit[4:0]    Reserved
   UNION结构:  ABB_CH1_REG_ANALOG_RO0_UNION */
#define ABB_CH1_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0x7B)

/* 寄存器说明：RC校准只读寄存器。
 bit[7]      Reserved
 bit[6:0]    RC Calibration校准值
   UNION结构:  ABB_CH1_REG_ANALOG_RO1_UNION */
#define ABB_CH1_REG_ANALOG_RO1_ADDR                   (ABB_BASE_ADDR + 0x7C)

/* 寄存器说明：Reserved RO寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0x7D)

/* 寄存器说明：Reserved RO寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0x7E)

/* 寄存器说明：Reserved RO寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0x7F)

/* 寄存器说明：模拟调试寄存器。
 bit[7:6]    Reserved
 bit[5:4]    PLL鉴频鉴相器控制
             x0：鉴频鉴相器一直输出Up信号
             01: 鉴频鉴相器一直输出Down信号
             11：鉴频鉴相器正常工作
 bit[3:1]    工作时钟选择
             001：选择来自于PLL的时钟作为工作时钟
             010：选择来自于CLKIN_SYSTEM的外灌时钟作为工作时钟
             100：选择来自于TCXO_IN的时钟作为工作时钟
 bit[0]      PLL的参考时钟选择
             1: CLKIN_SYSTEM作为PLL的参考时钟
             0: TCXO Buffer输出作为PLL参考时钟
   UNION结构:  ABB_CH1_REG_DEBUG_ANA0_UNION */
#define ABB_CH1_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0x80)

/* 寄存器说明：PLL LOCK控制寄存器。
 bit[7:6]    Reserved
 bit[5]      WPLL锁定检测使能
             0：检测停止
             1：检测开始
 bit[4]      GPLL锁定检测使能
             0：检测停止
             1：检测开始
 bit[3:0]    Reserved
   UNION结构:  ABB_CH1_REG_DEBUG_ANA1_UNION */
#define ABB_CH1_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0x81)

/* 寄存器说明：PLL控制寄存器。
 bit[7]      反相时钟开关
             1: 反相时钟打开
             0: 反相时钟关闭
 bit[6:2]    Reserved
 bit[1:0]    PLL CP PowerDown控制，测试用
             00：正常工作
             01: PowerDown WPLL CP 
             10: PowerDown GPLL CP 
             11: PowerDown WPLL CP和GPLL CP
   UNION结构:  ABB_CH1_REG_DEBUG_ANA2_UNION */
#define ABB_CH1_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0x82)

/* 寄存器说明：PLL控制寄存器。
 bit[7:4]    GPLL电荷泵电流控制(低有效)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION结构:  ABB_CH1_REG_DEBUG_ANA3_UNION */
#define ABB_CH1_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0x83)

/* 寄存器说明：PLL控制寄存器。
 bit[7:4]    WPLL电荷泵电流控制(低有效)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION结构:  ABB_CH1_REG_DEBUG_ANA4_UNION */
#define ABB_CH1_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0x84)

/* 寄存器说明：快速启动控制寄存器。
 bit[7]      0 disable
             1 enable
 bit[6:0]    Reserved
   UNION结构:  ABB_CH1_REG_DEBUG_ANA5_UNION */
#define ABB_CH1_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0x85)

/* 寄存器说明：Bandgap和TCXO控制寄存器。
 bit[7]      Sleep模式时是否保持Bandgap工作的控制信号，它与refgen模块产生的PD_BG信号共同控制Bandgap的状态
             0: Bandgap状态受PD_BG信号控制，当进入Sleep模式时，Bandgap被关闭；否则Bandgap工作
             1: Bandgap始终工作
 bit[6]      TEST CLK INPUT下电控制
             0: 开启
             1: 关闭
 bit[5:4]    TCXO BUFFER电流设置
             00: 1x
             01: 2x
             10: 3x
             11: 4x
 bit[3:1]    Reserved
 bit[0]      GPLL参考频率设置
             1: 19.2MHz参考时钟，工作模式
             0: 26MHz参考时钟，测试模式
   UNION结构:  ABB_CH1_REG_DEBUG_ANA6_UNION */
#define ABB_CH1_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0x86)

/* 寄存器说明：电流控制寄存器。
 bit[7:6]    Reserved
 bit[5:3]    基带参考电流控制
             000：5u
             001：2u
             010：3u
             011：4u
             100：6u
             101：7u
             110：8u
             111：9u
 bit[2:0]    L/W/G 共用ADC 差分Buffer电流调节控制
             000: 1.0x（默认）
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
   UNION结构:  ABB_CH1_REG_DEBUG_ANA7_UNION */
#define ABB_CH1_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0x87)

/* 寄存器说明：电流控制寄存器。
 bit[7:5]    Reserved
 bit[4]      量化器模式选择
 bit[3:0]    基带TX通道LPF电路电流控制
             0000：1.0x
             0001：0.9x
             0010：0.8x
             0011：0.7x
             0100：2.0x
             0101：1.8x
             0110：1.6x
             0111：1.4x
             1xxx：Reserved
   UNION结构:  ABB_CH1_REG_DEBUG_ANA8_UNION */
#define ABB_CH1_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0x88)

/* 寄存器说明：ADC控制寄存器。
 bit[7:5]    RX方向sub_DAC电流控制
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[4]      LTE ADC模块Tuning码的选择
             0：选择Tuning模块的输出作为LTE ADC的Tuning码
             1：选择寄存器的输出作为LTE ADC的Tuning码
 bit[3]      LTE ADC DEM功能关闭信号
             0：DEM使能
             1：DEM不使能
 bit[2]      积分器和量化器的电流是否可调
             0：不可调
             1：可调
 bit[1]      LTE ADC模块启动模式选择
             0：自动模式
             1：配置寄存器模式
 bit[0]      RX方向sub_DAC Dummy单元控制，低一位
             0：开启
             1：关闭
   UNION结构:  ABB_CH1_REG_DEBUG_ANA9_UNION */
#define ABB_CH1_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0x89)

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
             0: 不复位
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
   UNION结构:  ABB_CH1_REG_DEBUG_ANA10_UNION */
#define ABB_CH1_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0x8A)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0x8B)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0x8C)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0x8D)

/* 寄存器说明：ADC控制寄存器。
 bit[7:6]    LTE SYNC时序控制
             00：No delay
             01：250ps delay
             10：500ps delay
             11：1000ps delay
 bit[5:3]    LTE ADC 电流偏置调节
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    LTE Overload模块配置
             00：16个连续最大码或者最小码
             01：8个连续最大码或者最小码
             10：4个连续最大码或者最小码
             11：关闭Overload检测
   UNION结构:  ABB_CH1_REG_DEBUG_ANA14_UNION */
#define ABB_CH1_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0x8E)

/* 寄存器说明：ADC延迟控制寄存器。
   详      述：LTE CLKGEN时序控制
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0x8F)

/* 寄存器说明：ADC控制寄存器。
 bit[7]      G模式电流控制
             0：输出级运放正常
             1：输出级运放增加
 bit[6]      RX输出PDM编码控制
             0：adder encoder
             1：de-bubble encoder
 bit[5:3]    RX ADC Stage 3电流控制
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    RX ADC Stage 12电流控制
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
   UNION结构:  ABB_CH1_REG_DEBUG_ANA16_UNION */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0x90)

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
   UNION结构:  ABB_CH1_REG_DEBUG_ANA17_UNION */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0x91)

/* 寄存器说明：TX手工码寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0x92)

/* 寄存器说明：时钟反沿控制寄存器。
 bit[7:6]    Reserved
 bit[5]      PLL模块307.2MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[4]      PLL模块307.2MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[3]      PLL模块153.6MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[2]      HKADC和Tuning模块时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[1:0]    测试管脚输出时钟频率控制
             00: 输出最高时速
             01：WPLL输出半速
             10：GPLL输出半速
             11：WPLL和GPLL输出半速
   UNION结构:  ABB_CH1_REG_DEBUG_ANA19_UNION */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0x93)

/* 寄存器说明：模拟调试寄存器。
 bit[7]      Tuning电路电容选择
             0: 大电容
             1: 小电容
 bit[6:5]    第三级积分器电容调整
 bit[4]      外部BandGap使能信号
 bit[3:0]    Reserved
   UNION结构:  ABB_CH1_REG_DEBUG_ANA20_UNION */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0x94)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0x95)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0x96)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0x97)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0x98)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0x99)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0x9A)

/* 寄存器说明：模拟调试只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0x9B)

/* 寄存器说明：2g模式RX随路时钟延迟调整。
 bit[7:6]    保留
 bit[5]      rx_clk输出delay bypass开关：
             1'b0：rx_clk 输出delay 不bypass
             1'b1：rx_clk 输出delay bypass
 bit[4]      rx_clk输出反向控制：
             1'b0：rx_clk bypass输出
             1'b1：rx_clk反向输出
 bit[3:0]    RX_MCLK时钟延时选择
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION结构:  ABB_CH1_2G_RX_DELAY_UNION */
#define ABB_CH1_2G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0x9C)

/* 寄存器说明：3g模式RX随路时钟延迟调整。
 bit[7:6]    保留
 bit[5]      rx_clk输出delay bypass开关：
             1'b0：rx_clk 输出delay 不bypass
             1'b1：rx_clk 输出delay bypass
 bit[4]      rx_clk输出反向控制：
             1'b0：rx_clk bypass输出
             1'b1：rx_clk反向输出
 bit[3:0]    RX_MCLK时钟延时选择
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION结构:  ABB_CH1_3G_RX_DELAY_UNION */
#define ABB_CH1_3G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0x9D)

/* 寄存器说明：4g模式RX随路时钟延迟调整。
 bit[7:6]    保留
 bit[5]      rx_clk输出delay bypass开关：
             1'b0：rx_clk 输出delay 不bypass
             1'b1：rx_clk 输出delay bypass
 bit[4]      rx_clk输出反向控制：
             1'b0：rx_clk bypass输出
             1'b1：rx_clk反向输出
 bit[3:0]    RX_MCLK时钟延时选择
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION结构:  ABB_CH1_4G_RX_DELAY_UNION */
#define ABB_CH1_4G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0x9E)

/* 寄存器说明：version寄存器。
   详      述：由模拟部分决定版本寄存器值
   UNION结构 ：无 */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)

/* 寄存器说明：测试模式寄存器。
 bit[7]      保留
 bit[6]      配置的软复位信号：
             0：软件不启动软复位(默认)
             1：软件启动软复位
 bit[5:3]    bit[4:3]测试模式控制：
             00：正常模式(默认)
             01：数字算法逻辑环回模式
             10：RX模拟测试模式(bypass RX数字滤波器)
             11：数字接口环回模式
             bit[5]：reserved
 bit[2:1]    RX模拟测试模式下通道选择：
             00：输出RXA I模拟调制器数据(默认)
             01：输出RXA Q模拟调制器数据
             10：输出RXB I模拟调制器数据
             11：输出RXB Q模拟调制器数据
 bit[0]      保留
   UNION结构:  ABB_CH0_TESTMODE_UNION */
#define ABB_CH0_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0xA1)

/* 寄存器说明：通道控制寄存器。
 bit[7:1]    保留
 bit[0]      ET/APT通道选择：
             0：选择TX通道I路做ET/APT
             1：选择TX通道Q路做ET/APT
   UNION结构:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0xA2)

/* 寄存器说明：CFR峰值检测窗长寄存器。
 bit[7:4]    CFR削波因子
 bit[3]      保留
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

/* 寄存器说明：线控选择。
 bit[7]      选择RXA_EN线控，0: tie to 0(默认）
             1: from line control
 bit[6]      选择RXB_EN线控，0: tie to 0(默认）
             1: from line control
 bit[5]      选择TX_EN线控，0: tie to 0(默认）
             1: from line control
 bit[4]      选择ET线控模式，0: tie to 0(默认）
             1: from line control
 bit[3]      选择APT线控模式，0: tie to 0(默认）
             1: from line control
 bit[2]      选择4G线控模式，0: tie to 0(默认）
             1: from line control
 bit[1]      选择3G线控模式，0: tie to 0(默认）
             1: from line control
 bit[0]      选择2G线控模式，0: tie to 0(默认）
             1: from line control
   UNION结构:  ABB_CH0_LINE_CTRL_SEL_UNION */
#define ABB_CH0_LINE_CTRL_SEL_ADDR                    (ABB_BASE_ADDR + 0xA4)

/* 寄存器说明：RX数字工作模式上报寄存器。
 bit[7:5]    RX通道模式控制：
             000：2G
             001：3G_SC
             010：4G
             011：3G_DC
             Others：reserved
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G,   3G_SC,    4G,   3G_DC,      
             00： 2.167M,15.36M, 61.44M,30.72M
             01： 4.33MHz,------,30.72M,------
             10： ------, ------,15.36M,------
             11： ------, ------, 7.68M,------
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      Reserved
   UNION结构:  ABB_CH0_RX_DIG_RPT_UNION */
#define ABB_CH0_RX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0xA5)

/* 寄存器说明：TX数字工作模式上报寄存器。
 bit[7:5]    TX通道模式控制：
             000：2G
             001：3G
             010：4G &amp; ET &amp; APT
             Others：reserved
 bit[4:2]    TX通道CIC滤波器输出速率控制：
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0：4.33MHz,30.72MHz,61.44MHz
             1：2.16MHz,15.36MHz,30.72MHz
             2：-------,--------,15.36MHz
             3：-------,--------, 7.68MHz
             4：-------,--------, 3.84MHz
             Others：Reserved
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass
             1：bypass
   UNION结构:  ABB_CH0_TX_DIG_RPT_UNION */
#define ABB_CH0_TX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0xA6)

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
 bit[7:5]    RXA天线BLOCKING上报值,能量大小N
 bit[4:0]    RXA天线BLOCKING上报值，系数，2的M次方
   UNION结构:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0xC1)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值,能量大小N
 bit[4:0]    RXB天线BLOCKING上报值，系数，2的M次方
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
 bit[7:5]    保留
 bit[4]      Reserved
 bit[3:2]    Reserved
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
 bit[7]      div_en控制分频器bypass信号，0：div_en控制分频器；1：div_en不控制分频器，分频器使能始终为1。.
 bit[6]      切换复位bypass信号。1表示切换复位功能旁路。
 bit[5]      切换门控使能bypass信号。1表示门控使能功能旁路。
 bit[4]      RX通道CIC4/CIC6滤波器选择：
             0: 选择CIC4滤波器
             1: 选择CIC6滤波器
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_DEBUG_DIG4_UNION */
#define ABB_CH0_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0xCF)

/* 寄存器说明：Power Down控制寄存器。
 bit[7:4]    Reserved
 bit[3]      WPLL Power Down控制
             0:Power On(默认)
             1:Power Down
 bit[2]      GPLL Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[1]      Reserved
 bit[0]      Reserved
   UNION结构:  ABB_CH0_REG_ANALOG_WR02_UNION */
#define ABB_CH0_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0xD0)

/* 寄存器说明：数模接口时钟控制寄存器。
 bit[7]      Reserved
 bit[6]      245M输出控制：
             0: 不输出
             1: 输出
 bit[5]      CLK_52M Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[4]      CLK_61D44M Power Down控制
             0:Power On
             1:Power Down(默认)
 bit[3]      TX 采样时钟沿选择：
             0: 正沿
             1: 反沿(默认)
 bit[2:0]    Reserved
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
 bit[0]      Calibration enable（默认为0）
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

/* 寄存器说明：共模电平控制寄存器。
 bit[7]      Reserved
 bit[6:5]    Reserved
 bit[4]      Reserved
 bit[3]      Reserved
 bit[2:0]    Reserved
   UNION结构:  ABB_CH0_REG_ANALOG_WR38_UNION */
#define ABB_CH0_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0xD9)

/* 寄存器说明：DUM控制寄存器。
 bit[7:5]    RX DEM Mode Selection,bit 2
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[4:2]    Reserved
 bit[1]      TX I channel  dummy logic control signal
             1: enable(默认)
             0: disable
 bit[0]      TX Q channel  dummy logic control signal
             1: enable(默认)
             0: disable
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

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0xDD)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0xDE)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0xDF)

/* 寄存器说明：模拟调试寄存器。
 bit[7:6]    Reserved
 bit[5:4]    PLL鉴频鉴相器控制
             x0：鉴频鉴相器一直输出Up信号
             01: 鉴频鉴相器一直输出Down信号
             11：鉴频鉴相器正常工作
 bit[3:1]    工作时钟选择
             001：选择来自于PLL的时钟作为工作时钟
             010：选择来自于CLKIN_SYSTEM的外灌时钟作为工作时钟
             100：选择来自于TCXO_IN的时钟作为工作时钟
 bit[0]      PLL的参考时钟选择
             1: CLKIN_SYSTEM作为PLL的参考时钟
             0: TCXO Buffer输出作为PLL参考时钟
   UNION结构:  ABB_CH0_REG_DEBUG_ANA0_UNION */
#define ABB_CH0_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0xE0)

/* 寄存器说明：PLL LOCK控制寄存器。
 bit[7:6]    Reserved
 bit[5]      WPLL锁定检测使能
             0：检测停止
             1：检测开始
 bit[4]      GPLL锁定检测使能
             0：检测停止
             1：检测开始
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA1_UNION */
#define ABB_CH0_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0xE1)

/* 寄存器说明：PLL控制寄存器。
 bit[7]      反相时钟开关
             1: 反相时钟打开
             0: 反相时钟关闭
 bit[6:2]    Reserved
 bit[1:0]    PLL CP PowerDown控制，测试用
             00：正常工作
             01: PowerDown WPLL CP 
             10: PowerDown GPLL CP 
             11: PowerDown WPLL CP和GPLL CP
   UNION结构:  ABB_CH0_REG_DEBUG_ANA2_UNION */
#define ABB_CH0_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0xE2)

/* 寄存器说明：PLL控制寄存器。
 bit[7:4]    GPLL电荷泵电流控制(低有效)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA3_UNION */
#define ABB_CH0_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0xE3)

/* 寄存器说明：PLL控制寄存器。
 bit[7:4]    WPLL电荷泵电流控制(低有效)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA4_UNION */
#define ABB_CH0_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0xE4)

/* 寄存器说明：快速启动控制寄存器。
 bit[7]      0 disable
             1 enable
 bit[6:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA5_UNION */
#define ABB_CH0_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0xE5)

/* 寄存器说明：Bandgap和TCXO控制寄存器。
 bit[7]      Sleep模式时是否保持Bandgap工作的控制信号，它与refgen模块产生的PD_BG信号共同控制Bandgap的状态
             0: Bandgap状态受PD_BG信号控制，当进入Sleep模式时，Bandgap被关闭；否则Bandgap工作
             1: Bandgap始终工作
 bit[6]      TEST CLK INPUT下电控制
             0: 开启
             1: 关闭
 bit[5:4]    TCXO BUFFER电流设置
             00: 1x
             01: 2x
             10: 3x
             11: 4x
 bit[3:1]    Reserved
 bit[0]      GPLL参考频率设置
             1: 19.2MHz参考时钟，工作模式
             0: 26MHz参考时钟，测试模式
   UNION结构:  ABB_CH0_REG_DEBUG_ANA6_UNION */
#define ABB_CH0_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0xE6)

/* 寄存器说明：电流控制寄存器。
 bit[7:6]    Reserved
 bit[5:3]    基带参考电流控制
             000：5u
             001：2u
             010：3u
             011：4u
             100：6u
             101：7u
             110：8u
             111：9u
 bit[2:0]    L/W/G 共用ADC 差分Buffer电流调节控制
             000: 1.0x（默认）
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
   UNION结构:  ABB_CH0_REG_DEBUG_ANA7_UNION */
#define ABB_CH0_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0xE7)

/* 寄存器说明：电流控制寄存器。
 bit[7:5]    Reserved
 bit[4]      量化器模式选择
 bit[3:0]    基带TX通道LPF电路电流控制
             0000：1.0x
             0001：0.9x
             0010：0.8x
             0011：0.7x
             0100：2.0x
             0101：1.8x
             0110：1.6x
             0111：1.4x
             1xxx：Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA8_UNION */
#define ABB_CH0_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0xE8)

/* 寄存器说明：ADC控制寄存器。
 bit[7:5]    RX方向sub_DAC电流控制
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[4]      LTE ADC模块Tuning码的选择
             0：选择Tuning模块的输出作为LTE ADC的Tuning码
             1：选择寄存器的输出作为LTE ADC的Tuning码
 bit[3]      LTE ADC DEM功能关闭信号
             0：DEM使能
             1：DEM不使能
 bit[2]      积分器和量化器的电流是否可调
             0：不可调
             1：可调
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
             0: 不复位
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

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xEB)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xEC)

/* 寄存器说明：模拟调试寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xED)

/* 寄存器说明：ADC控制寄存器。
 bit[7:6]    LTE SYNC时序控制
             00：No delay
             01：250ps delay
             10：500ps delay
             11：1000ps delay
 bit[5:3]    量化器电流偏置调节
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    LTE Overload模块配置
             00：16个连续最大码或者最小码
             01：8个连续最大码或者最小码
             10：4个连续最大码或者最小码
             11：关闭Overload检测
   UNION结构:  ABB_CH0_REG_DEBUG_ANA14_UNION */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xEE)

/* 寄存器说明：ADC延迟控制寄存器。
   详      述：LTE CLKGEN时序控制
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xEF)

/* 寄存器说明：ADC控制寄存器。
 bit[7]      G模式电流控制
             0：输出级运放正常
             1：输出级运放增加
 bit[6]      RX输出PDM编码控制
             0：adder encoder
             1：de-bubble encoder
 bit[5:3]    RX ADC Stage 3电流控制
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    RX ADC Stage 12电流控制
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
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

/* 寄存器说明：时钟反沿控制寄存器。
 bit[7:6]    Reserved
 bit[5]      PLL模块307.2MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[4]      PLL模块307.2MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[3]      PLL模块153.6MHz时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[2]      HKADC和Tuning模块时钟使能信号
             0：时钟关闭
             1：时钟使能
 bit[1:0]    测试管脚输出时钟频率控制
             00: 输出最高时速
             01：WPLL输出半速
             10：GPLL输出半速
             11：WPLL和GPLL输出半速
   UNION结构:  ABB_CH0_REG_DEBUG_ANA19_UNION */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xF3)

/* 寄存器说明：模拟调试寄存器。
 bit[7]      Tuning电路电容选择
             0: 大电容
             1: 小电容
 bit[6:5]    第三级积分器电容调整
 bit[4]      外部BandGap使能信号
 bit[3:0]    Reserved
   UNION结构:  ABB_CH0_REG_DEBUG_ANA20_UNION */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xF4)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xF5)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xF6)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xF7)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xF8)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xF9)

/* 寄存器说明：模拟调试寄存器。
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xFA)

/* 寄存器说明：模拟调试只读寄存器。
   详      述：Reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0xFB)

/* 寄存器说明：2g模式RX随路时钟延迟调整。
 bit[7:6]    保留
 bit[5]      rx_clk输出delay bypass开关：
             1'b0：rx_clk 输出delay 不bypass
             1'b1：rx_clk 输出delay bypass
 bit[4]      rx_clk输出反向控制：
             1'b0：rx_clk bypass输出
             1'b1：rx_clk反向输出
 bit[3:0]    RX_MCLK时钟延时选择
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION结构:  ABB_CH0_2G_RX_DELAY_UNION */
#define ABB_CH0_2G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0xFC)

/* 寄存器说明：3g模式RX随路时钟延迟调整。
 bit[7:6]    保留
 bit[5]      rx_clk输出delay bypass开关：
             1'b0：rx_clk 输出delay 不bypass
             1'b1：rx_clk 输出delay bypass
 bit[4]      rx_clk输出反向控制：
             1'b0：rx_clk bypass输出
             1'b1：rx_clk反向输出
 bit[3:0]    RX_MCLK时钟延时选择
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION结构:  ABB_CH0_3G_RX_DELAY_UNION */
#define ABB_CH0_3G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0xFD)

/* 寄存器说明：4g模式RX随路时钟延迟调整。
 bit[7:6]    保留
 bit[5]      rx_clk输出delay bypass开关：
             1'b0：rx_clk 输出delay 不bypass
             1'b1：rx_clk 输出delay bypass
 bit[4]      rx_clk输出反向控制：
             1'b0：rx_clk bypass输出
             1'b1：rx_clk反向输出
 bit[3:0]    RX_MCLK时钟延时选择
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION结构:  ABB_CH0_4G_RX_DELAY_UNION */
#define ABB_CH0_4G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0xFE)

#define ABB_CH0_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x108)
#define ABB_CH0_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x109)
#define ABB_CH0_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10A)




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
 结构说明  : rx_2g_dig_1 寄存器结构定义。地址偏移量:0x00，初值:0x02，宽度:8
 寄存器说明: RX 2G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_2g_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_2g : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_2g : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                         0：系数不固定，由寄存器配置
                                                         1：系数固定 */
        unsigned long  rx_hb_bp_2g    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                         1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_2g     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                             2G,   3G_SC,    4G,   3G_DC,      
                                                         00： 2.167M,15.36M, 61.44M,30.72M(默认)
                                                         01： 4.33MHz,------,30.72M,------
                                                         10： ------, ------,15.36M,------
                                                         11： ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_2g : 3;  /* bit[5-7]: RX通道模式控制：
                                                         000：2G(默认)
                                                         001：3G_SC
                                                         010：4G
                                                         011：3G_DC
                                                         Others：reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_1_UNION;
#define ABB_RX_2G_DIG_1_rx_comp_sel_2g_START  (0)
#define ABB_RX_2G_DIG_1_rx_comp_sel_2g_END    (0)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_START  (1)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_END    (1)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_START     (2)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_END       (2)
#define ABB_RX_2G_DIG_1_rx_rate_2g_START      (3)
#define ABB_RX_2G_DIG_1_rx_rate_2g_END        (4)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_START  (5)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_2G_DIG_2_UNION
 结构说明  : rx_2g_dig_2 寄存器结构定义。地址偏移量:0x01，初值:0x13，宽度:8
 寄存器说明: RX 2G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_2g_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_2g     : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_2g     : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_2g   : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                        00：gain为0.5(默认)
                                                        01：gain为0.75
                                                        10：gain为0.85
                                                        11：Reserved */
        unsigned long  rx_comp_bp_2g : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                        0：不bypass
                                                        1：bypass(默认) */
        unsigned long  rx_clk_inv_2g : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_2g : 1;  /* bit[6]  : RX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_2_UNION;
#define ABB_RX_2G_DIG_2_rxa_pd_2g_START      (0)
#define ABB_RX_2G_DIG_2_rxa_pd_2g_END        (0)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_START      (1)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_END        (1)
#define ABB_RX_2G_DIG_2_gain_sel_2g_START    (2)
#define ABB_RX_2G_DIG_2_gain_sel_2g_END      (3)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_START  (4)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_END    (4)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_START  (5)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_END    (5)
#define ABB_RX_2G_DIG_2_rx_ddr_sdr_2g_START  (6)
#define ABB_RX_2G_DIG_2_rx_ddr_sdr_2g_END    (6)


/*****************************************************************************
 结构名    : ABB_TX_2G_DIG_1_UNION
 结构说明  : tx_2g_dig_1 寄存器结构定义。地址偏移量:0x02，初值:0x02，宽度:8
 寄存器说明: TX 2G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_2g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_2g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认) */
        unsigned long  tx_rate_2g     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0：4.33MHz,30.72MHz,61.44MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz
                                                         2：-------,--------,15.36MHz
                                                         3：-------,--------, 7.68MHz
                                                         4：-------,--------, 3.84MHz
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_2g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G
                                                         001：3G(默认)
                                                         010：4G &amp; ET &amp; APT
                                                         Others：reserved */
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
 结构说明  : tx_2g_dig_2 寄存器结构定义。地址偏移量:0x03，初值:0x0B，宽度:8
 寄存器说明: TX 2G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_dig_2_reg;
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
        unsigned long  dem_const_2g     : 2;  /* bit[2-3]: TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2) */
        unsigned long  uddwa_dith_en_2g : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_2g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                           0：使用CLA模式(默认)
                                                           1：使用DWA模式  */
        unsigned long  dem_lsb_bp_2g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                           0：DEM LSB 打开(默认)
                                                           1：DEM LSB bypass */
        unsigned long  dem_msb_bp_2g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                           0：DEM MSB 打开(默认)
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
 结构说明  : tx_2g_dig_3 寄存器结构定义。地址偏移量:0x04，初值:0x00，宽度:8
 寄存器说明: TX 2G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_2g  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_2g : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_START   (0)
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_END     (0)
#define ABB_TX_2G_DIG_3_tx_ddr_sdr_2g_START  (1)
#define ABB_TX_2G_DIG_3_tx_ddr_sdr_2g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_3G_DIG_1_UNION
 结构说明  : rx_3g_dig_1 寄存器结构定义。地址偏移量:0x05，初值:0x26，宽度:8
 寄存器说明: RX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_3g_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_3g : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_3g : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                         0：系数不固定，由寄存器配置
                                                         1：系数固定 */
        unsigned long  rx_hb_bp_3g    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                         1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_3g     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                             2G,   3G_SC,    4G,   3G_DC,      
                                                         00： 2.167M,15.36M, 61.44M,30.72M(默认)
                                                         01： 4.33MHz,------,30.72M,------
                                                         10： ------, ------,15.36M,------
                                                         11： ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_3g : 3;  /* bit[5-7]: RX通道模式控制：
                                                         000：2G
                                                         001：3G_SC(默认)
                                                         010：4G
                                                         011：3G_DC
                                                         Others：reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_1_UNION;
#define ABB_RX_3G_DIG_1_rx_comp_sel_3g_START  (0)
#define ABB_RX_3G_DIG_1_rx_comp_sel_3g_END    (0)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_START  (1)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_END    (1)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_START     (2)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_END       (2)
#define ABB_RX_3G_DIG_1_rx_rate_3g_START      (3)
#define ABB_RX_3G_DIG_1_rx_rate_3g_END        (4)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_START  (5)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_3G_DIG_2_UNION
 结构说明  : rx_3g_dig_2 寄存器结构定义。地址偏移量:0x06，初值:0x03，宽度:8
 寄存器说明: RX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_3g_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_3g     : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_3g     : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_3g   : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                        00：gain为0.5(默认)
                                                        01：gain为0.75
                                                        10：gain为0.85
                                                        11：Reserved */
        unsigned long  rx_comp_bp_3g : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                        0：不bypass(默认)
                                                        1：bypass */
        unsigned long  rx_clk_inv_3g : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_3g : 1;  /* bit[6]  : RX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_2_UNION;
#define ABB_RX_3G_DIG_2_rxa_pd_3g_START      (0)
#define ABB_RX_3G_DIG_2_rxa_pd_3g_END        (0)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_START      (1)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_END        (1)
#define ABB_RX_3G_DIG_2_gain_sel_3g_START    (2)
#define ABB_RX_3G_DIG_2_gain_sel_3g_END      (3)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_START  (4)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_END    (4)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_START  (5)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_END    (5)
#define ABB_RX_3G_DIG_2_rx_ddr_sdr_3g_START  (6)
#define ABB_RX_3G_DIG_2_rx_ddr_sdr_3g_END    (6)


/*****************************************************************************
 结构名    : ABB_TX_3G_DIG_1_UNION
 结构说明  : tx_3g_dig_1 寄存器结构定义。地址偏移量:0x07，初值:0x20，宽度:8
 寄存器说明: TX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_3g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_3g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_3g     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0：4.33MHz,30.72MHz,61.44MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz
                                                         2：-------,--------,15.36MHz
                                                         3：-------,--------, 7.68MHz
                                                         4：-------,--------, 3.84MHz
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_3g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G
                                                         001：3G(默认)
                                                         010：4G &amp; ET &amp; APT
                                                         Others：reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_1_UNION;
#define ABB_TX_3G_DIG_1_tx_comp_bp_3g_START   (0)
#define ABB_TX_3G_DIG_1_tx_comp_bp_3g_END     (0)
#define ABB_TX_3G_DIG_1_tx_hb_bp_3g_START     (1)
#define ABB_TX_3G_DIG_1_tx_hb_bp_3g_END       (1)
#define ABB_TX_3G_DIG_1_tx_rate_3g_START      (2)
#define ABB_TX_3G_DIG_1_tx_rate_3g_END        (4)
#define ABB_TX_3G_DIG_1_tx_mode_dig_3g_START  (5)
#define ABB_TX_3G_DIG_1_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_3G_DIG_2_UNION
 结构说明  : tx_3g_dig_2 寄存器结构定义。地址偏移量:0x08，初值:0x0B，宽度:8
 寄存器说明: TX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_dig_2_reg;
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
        unsigned long  dem_const_3g     : 2;  /* bit[2-3]: TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2) */
        unsigned long  uddwa_dith_en_3g : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_3g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                           0：使用CLA模式(默认)
                                                           1：使用DWA模式  */
        unsigned long  dem_lsb_bp_3g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                           0：DEM LSB 打开(默认)
                                                           1：DEM LSB bypass */
        unsigned long  dem_msb_bp_3g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                           0：DEM MSB 打开(默认)
                                                           1：DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_2_UNION;
#define ABB_TX_3G_DIG_2_tx_q_pd_3g_START        (0)
#define ABB_TX_3G_DIG_2_tx_q_pd_3g_END          (0)
#define ABB_TX_3G_DIG_2_tx_i_pd_3g_START        (1)
#define ABB_TX_3G_DIG_2_tx_i_pd_3g_END          (1)
#define ABB_TX_3G_DIG_2_dem_const_3g_START      (2)
#define ABB_TX_3G_DIG_2_dem_const_3g_END        (3)
#define ABB_TX_3G_DIG_2_uddwa_dith_en_3g_START  (4)
#define ABB_TX_3G_DIG_2_uddwa_dith_en_3g_END    (4)
#define ABB_TX_3G_DIG_2_dem_dwa_en_3g_START     (5)
#define ABB_TX_3G_DIG_2_dem_dwa_en_3g_END       (5)
#define ABB_TX_3G_DIG_2_dem_lsb_bp_3g_START     (6)
#define ABB_TX_3G_DIG_2_dem_lsb_bp_3g_END       (6)
#define ABB_TX_3G_DIG_2_dem_msb_bp_3g_START     (7)
#define ABB_TX_3G_DIG_2_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_3G_DIG_3_UNION
 结构说明  : tx_3g_dig_3 寄存器结构定义。地址偏移量:0x09，初值:0x00，宽度:8
 寄存器说明: TX 3G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_3g  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_3g : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_3_UNION;
#define ABB_TX_3G_DIG_3_tx_cfr_bp_3g_START   (0)
#define ABB_TX_3G_DIG_3_tx_cfr_bp_3g_END     (0)
#define ABB_TX_3G_DIG_3_tx_ddr_sdr_3g_START  (1)
#define ABB_TX_3G_DIG_3_tx_ddr_sdr_3g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_4G_DIG_1_UNION
 结构说明  : rx_4g_dig_1 寄存器结构定义。地址偏移量:0x0A，初值:0x40，宽度:8
 寄存器说明: RX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_4g_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_4g : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_4g : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                         0：系数不固定，由寄存器配置
                                                         1：系数固定 */
        unsigned long  rx_hb_bp_4g    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                         1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_4g     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                             2G,   3G_SC,    4G,   3G_DC,      
                                                         00： 2.167M,15.36M, 61.44M,30.72M(默认)
                                                         01： 4.33MHz,------,30.72M,------
                                                         10： ------, ------,15.36M,------
                                                         11： ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_4g : 3;  /* bit[5-7]: RX通道模式控制：
                                                         000：2G
                                                         001：3G_SC
                                                         010：4G(默认)
                                                         011：3G_DC
                                                         Others：reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_1_UNION;
#define ABB_RX_4G_DIG_1_rx_comp_sel_4g_START  (0)
#define ABB_RX_4G_DIG_1_rx_comp_sel_4g_END    (0)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_START  (1)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_END    (1)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_START     (2)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_END       (2)
#define ABB_RX_4G_DIG_1_rx_rate_4g_START      (3)
#define ABB_RX_4G_DIG_1_rx_rate_4g_END        (4)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_START  (5)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_4G_DIG_2_UNION
 结构说明  : rx_4g_dig_2 寄存器结构定义。地址偏移量:0x0B，初值:0x43，宽度:8
 寄存器说明: RX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_4g_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_4g     : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_4g     : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_4g   : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                        00：gain为0.5(默认)
                                                        01：gain为0.75
                                                        10：gain为0.85
                                                        11：Reserved */
        unsigned long  rx_comp_bp_4g : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                        0：不bypass(默认)
                                                        1：bypass */
        unsigned long  rx_clk_inv_4g : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_4g : 1;  /* bit[6]  : RX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_2_UNION;
#define ABB_RX_4G_DIG_2_rxa_pd_4g_START      (0)
#define ABB_RX_4G_DIG_2_rxa_pd_4g_END        (0)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_START      (1)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_END        (1)
#define ABB_RX_4G_DIG_2_gain_sel_4g_START    (2)
#define ABB_RX_4G_DIG_2_gain_sel_4g_END      (3)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_START  (4)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_END    (4)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_START  (5)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_END    (5)
#define ABB_RX_4G_DIG_2_rx_ddr_sdr_4g_START  (6)
#define ABB_RX_4G_DIG_2_rx_ddr_sdr_4g_END    (6)


/*****************************************************************************
 结构名    : ABB_TX_4G_DIG_1_UNION
 结构说明  : tx_4g_dig_1 寄存器结构定义。地址偏移量:0x0C，初值:0x40，宽度:8
 寄存器说明: TX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_4g  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_4g    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_4g     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0：4.33MHz,30.72MHz,61.44MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz
                                                         2：-------,--------,15.36MHz
                                                         3：-------,--------, 7.68MHz
                                                         4：-------,--------, 3.84MHz
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_4g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G
                                                         001：3G
                                                         010：4G &amp; ET &amp; APT(默认)
                                                         Others：reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_1_UNION;
#define ABB_TX_4G_DIG_1_tx_comp_bp_4g_START   (0)
#define ABB_TX_4G_DIG_1_tx_comp_bp_4g_END     (0)
#define ABB_TX_4G_DIG_1_tx_hb_bp_4g_START     (1)
#define ABB_TX_4G_DIG_1_tx_hb_bp_4g_END       (1)
#define ABB_TX_4G_DIG_1_tx_rate_4g_START      (2)
#define ABB_TX_4G_DIG_1_tx_rate_4g_END        (4)
#define ABB_TX_4G_DIG_1_tx_mode_dig_4g_START  (5)
#define ABB_TX_4G_DIG_1_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_4G_DIG_2_UNION
 结构说明  : tx_4g_dig_2 寄存器结构定义。地址偏移量:0x0D，初值:0x0B，宽度:8
 寄存器说明: TX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_dig_2_reg;
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
        unsigned long  dem_const_4g     : 2;  /* bit[2-3]: TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2) */
        unsigned long  uddwa_dith_en_4g : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_4g    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                           0：使用CLA模式(默认)
                                                           1：使用DWA模式  */
        unsigned long  dem_lsb_bp_4g    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                           0：DEM LSB 打开(默认)
                                                           1：DEM LSB bypass */
        unsigned long  dem_msb_bp_4g    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                           0：DEM MSB 打开(默认)
                                                           1：DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_2_UNION;
#define ABB_TX_4G_DIG_2_tx_q_pd_4g_START        (0)
#define ABB_TX_4G_DIG_2_tx_q_pd_4g_END          (0)
#define ABB_TX_4G_DIG_2_tx_i_pd_4g_START        (1)
#define ABB_TX_4G_DIG_2_tx_i_pd_4g_END          (1)
#define ABB_TX_4G_DIG_2_dem_const_4g_START      (2)
#define ABB_TX_4G_DIG_2_dem_const_4g_END        (3)
#define ABB_TX_4G_DIG_2_uddwa_dith_en_4g_START  (4)
#define ABB_TX_4G_DIG_2_uddwa_dith_en_4g_END    (4)
#define ABB_TX_4G_DIG_2_dem_dwa_en_4g_START     (5)
#define ABB_TX_4G_DIG_2_dem_dwa_en_4g_END       (5)
#define ABB_TX_4G_DIG_2_dem_lsb_bp_4g_START     (6)
#define ABB_TX_4G_DIG_2_dem_lsb_bp_4g_END       (6)
#define ABB_TX_4G_DIG_2_dem_msb_bp_4g_START     (7)
#define ABB_TX_4G_DIG_2_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_4G_DIG_3_UNION
 结构说明  : tx_4g_dig_3 寄存器结构定义。地址偏移量:0x0E，初值:0x02，宽度:8
 寄存器说明: TX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_4g  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_4g : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_3_UNION;
#define ABB_TX_4G_DIG_3_tx_cfr_bp_4g_START   (0)
#define ABB_TX_4G_DIG_3_tx_cfr_bp_4g_END     (0)
#define ABB_TX_4G_DIG_3_tx_ddr_sdr_4g_START  (1)
#define ABB_TX_4G_DIG_3_tx_ddr_sdr_4g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_1_UNION
 结构说明  : rx_tds_dig_1 寄存器结构定义。地址偏移量:0x0F，初值:0x80，宽度:8
 寄存器说明: RX TDS模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_tds_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_tds : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_tds : 1;  /* bit[1]  : Reserved */
        unsigned long  rx_hb_bp_tds    : 1;  /* bit[2]  : Reserved */
        unsigned long  rx_rate_tds     : 2;  /* bit[3-4]: Reserved */
        unsigned long  rx_mode_dig_tds : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_1_UNION;
#define ABB_RX_TDS_DIG_1_rx_comp_sel_tds_START  (0)
#define ABB_RX_TDS_DIG_1_rx_comp_sel_tds_END    (0)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_START  (1)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_END    (1)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_START     (2)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_END       (2)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_START      (3)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_END        (4)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_START  (5)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_2_UNION
 结构说明  : rx_tds_dig_2 寄存器结构定义。地址偏移量:0x10，初值:0x65，宽度:8
 寄存器说明: RX TDS模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_tds_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_2g     : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_2g     : 1;  /* bit[1]  :  */
        unsigned long  gain_sel_2g   : 2;  /* bit[2-3]: RXB通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  rx_comp_bp_2g : 1;  /* bit[4]  : RX通道增益配置选择：
                                                        00：gain为0.5(默认)
                                                        01：gain为0.75
                                                        10：gain为0.85
                                                        11：Reserved */
        unsigned long  tx_cfr_bp_2g  : 1;  /* bit[5]  : RX通道补偿滤波器bypass控制：
                                                        0：不bypass
                                                        1：bypass(默认) */
        unsigned long  rx_ddr_sdr_2g : 1;  /* bit[6]  : TX通道CFR bypass控制：
                                                        0：不bypass
                                                        1：bypass(默认) */
        unsigned long  reserved      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_2_UNION;
#define ABB_RX_TDS_DIG_2_rxa_pd_2g_START      (0)
#define ABB_RX_TDS_DIG_2_rxa_pd_2g_END        (0)
#define ABB_RX_TDS_DIG_2_rxb_pd_2g_START      (1)
#define ABB_RX_TDS_DIG_2_rxb_pd_2g_END        (1)
#define ABB_RX_TDS_DIG_2_gain_sel_2g_START    (2)
#define ABB_RX_TDS_DIG_2_gain_sel_2g_END      (3)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_2g_START  (4)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_2g_END    (4)
#define ABB_RX_TDS_DIG_2_tx_cfr_bp_2g_START   (5)
#define ABB_RX_TDS_DIG_2_tx_cfr_bp_2g_END     (5)
#define ABB_RX_TDS_DIG_2_rx_ddr_sdr_2g_START  (6)
#define ABB_RX_TDS_DIG_2_rx_ddr_sdr_2g_END    (6)


/*****************************************************************************
 结构名    : ABB_TX_TDS_DIG_1_UNION
 结构说明  : tx_tds_dig_1 寄存器结构定义。地址偏移量:0x11，初值:0x60，宽度:8
 寄存器说明: TX TDS模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_tds  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                          0：不bypass(默认)
                                                          1：bypass */
        unsigned long  tx_hb_bp_tds    : 1;  /* bit[1]  : TX通道半带滤波器的bypass信号
                                                          0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                          1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_tds     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                               2G,     3G,     4G,      TDS,      CA
                                                              (78M) (153.6M) (307.2M) (153.6M) (614.4M)
                                                          0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(默认)
                                                          1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                          2：-------,--------,15.36MHz,--------,--------
                                                          3：-------,--------, 7.68MHz,--------,--------
                                                          4：-------,--------, 3.84MHz,--------,--------
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
 结构说明  : tx_tds_dig_2 寄存器结构定义。地址偏移量:0x12，初值:0x03，宽度:8
 寄存器说明: TX TDS模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_tds       : 1;  /* bit[0]: TX通道Q路CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_tds       : 1;  /* bit[1]: TX通道I路CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_tds     : 1;  /* bit[2]: TX通道DEM const系数：
                                                          0：2(默认)
                                                          1：4 */
        unsigned long  uddwa_dith_en_tds : 1;  /* bit[3]: TX通道DEM UDDWA_DITH模块使能控制：
                                                          0：不使能
                                                          1：使能 */
        unsigned long  dither_en_tds     : 1;  /* bit[4]: TX通道SDM Dither控制：
                                                          0：不使能
                                                          1：使能 */
        unsigned long  dem_dwa_en_tds    : 1;  /* bit[5]: TX通道DEM模式控制：
                                                          0：使用CLA模式(默认)
                                                          1：使用DWA模式  */
        unsigned long  dem_lsb_bp_tds    : 1;  /* bit[6]: TX通道DEM LSB bypass：
                                                          0：DEM LSB 打开(默认)
                                                          1：DEM LSB bypass */
        unsigned long  dem_msb_bp_tds    : 1;  /* bit[7]: TX通道DEM MSB bypass：
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
#define ABB_TX_TDS_DIG_2_dem_const_tds_END        (2)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_START  (3)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_END    (3)
#define ABB_TX_TDS_DIG_2_dither_en_tds_START      (4)
#define ABB_TX_TDS_DIG_2_dither_en_tds_END        (4)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_START     (5)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_END       (5)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_START     (6)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_END       (6)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_START     (7)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_TDS_DIG_3_UNION
 结构说明  : tx_tds_dig_3 寄存器结构定义。地址偏移量:0x13，初值:0x00，宽度:8
 寄存器说明: TX TDS模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_tds  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_tds : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                         1'b0：SDR接口；
                                                         1'b1：DDR接口。 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_START   (0)
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_END     (0)
#define ABB_TX_TDS_DIG_3_tx_ddr_sdr_tds_START  (1)
#define ABB_TX_TDS_DIG_3_tx_ddr_sdr_tds_END    (1)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_1_UNION
 结构说明  : tx_et_dig_1 寄存器结构定义。地址偏移量:0x14，初值:0x40，宽度:8
 寄存器说明: TX ET模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_et  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_et    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_et     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0：4.33MHz,30.72MHz,61.44MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz
                                                         2：-------,--------,15.36MHz
                                                         3：-------,--------, 7.68MHz
                                                         4：-------,--------, 3.84MHz
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_et : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G
                                                         001：3G
                                                         010：4G &amp; ET &amp; APT(默认)
                                                         Others：reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_1_UNION;
#define ABB_TX_ET_DIG_1_tx_comp_bp_et_START   (0)
#define ABB_TX_ET_DIG_1_tx_comp_bp_et_END     (0)
#define ABB_TX_ET_DIG_1_tx_hb_bp_et_START     (1)
#define ABB_TX_ET_DIG_1_tx_hb_bp_et_END       (1)
#define ABB_TX_ET_DIG_1_tx_rate_et_START      (2)
#define ABB_TX_ET_DIG_1_tx_rate_et_END        (4)
#define ABB_TX_ET_DIG_1_tx_mode_dig_et_START  (5)
#define ABB_TX_ET_DIG_1_tx_mode_dig_et_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_2_UNION
 结构说明  : tx_et_dig_2 寄存器结构定义。地址偏移量:0x15，初值:0x0B，宽度:8
 寄存器说明: TX ET模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_et       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_et       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_et     : 2;  /* bit[2-3]: TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2) */
        unsigned long  uddwa_dith_en_et : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_et    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                           0：使用CLA模式(默认)
                                                           1：使用DWA模式  */
        unsigned long  dem_lsb_bp_et    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                           0：DEM LSB 打开(默认)
                                                           1：DEM LSB bypass */
        unsigned long  dem_msb_bp_et    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                           0：DEM MSB 打开(默认)
                                                           1：DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_2_UNION;
#define ABB_TX_ET_DIG_2_tx_q_pd_et_START        (0)
#define ABB_TX_ET_DIG_2_tx_q_pd_et_END          (0)
#define ABB_TX_ET_DIG_2_tx_i_pd_et_START        (1)
#define ABB_TX_ET_DIG_2_tx_i_pd_et_END          (1)
#define ABB_TX_ET_DIG_2_dem_const_et_START      (2)
#define ABB_TX_ET_DIG_2_dem_const_et_END        (3)
#define ABB_TX_ET_DIG_2_uddwa_dith_en_et_START  (4)
#define ABB_TX_ET_DIG_2_uddwa_dith_en_et_END    (4)
#define ABB_TX_ET_DIG_2_dem_dwa_en_et_START     (5)
#define ABB_TX_ET_DIG_2_dem_dwa_en_et_END       (5)
#define ABB_TX_ET_DIG_2_dem_lsb_bp_et_START     (6)
#define ABB_TX_ET_DIG_2_dem_lsb_bp_et_END       (6)
#define ABB_TX_ET_DIG_2_dem_msb_bp_et_START     (7)
#define ABB_TX_ET_DIG_2_dem_msb_bp_et_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_3_UNION
 结构说明  : tx_et_dig_3 寄存器结构定义。地址偏移量:0x16，初值:0x02，宽度:8
 寄存器说明: TX ET模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_et  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_et : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_3_UNION;
#define ABB_TX_ET_DIG_3_tx_cfr_bp_et_START   (0)
#define ABB_TX_ET_DIG_3_tx_cfr_bp_et_END     (0)
#define ABB_TX_ET_DIG_3_tx_ddr_sdr_et_START  (1)
#define ABB_TX_ET_DIG_3_tx_ddr_sdr_et_END    (1)


/*****************************************************************************
 结构名    : ABB_TX_APT_DIG_1_UNION
 结构说明  : tx_apt_dig_1 寄存器结构定义。地址偏移量:0x17，初值:0x40，宽度:8
 寄存器说明: TX APT模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_apt  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                          0：不bypass(默认)
                                                          1：bypass */
        unsigned long  tx_hb_bp_apt    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                          0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                          1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_apt     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                               2G,     3G,     4G,     
                                                              (78M) (153.6M) (307.2M) 
                                                          0：4.33MHz,30.72MHz,61.44MHz(默认)
                                                          1：2.16MHz,15.36MHz,30.72MHz
                                                          2：-------,--------,15.36MHz
                                                          3：-------,--------, 7.68MHz
                                                          4：-------,--------, 3.84MHz
                                                          Others：Reserved */
        unsigned long  tx_mode_dig_apt : 3;  /* bit[5-7]: TX通道模式控制：
                                                          000：2G
                                                          001：3G
                                                          010：4G &amp; ET &amp; APT(默认)
                                                          Others：reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_DIG_1_UNION;
#define ABB_TX_APT_DIG_1_tx_comp_bp_apt_START   (0)
#define ABB_TX_APT_DIG_1_tx_comp_bp_apt_END     (0)
#define ABB_TX_APT_DIG_1_tx_hb_bp_apt_START     (1)
#define ABB_TX_APT_DIG_1_tx_hb_bp_apt_END       (1)
#define ABB_TX_APT_DIG_1_tx_rate_apt_START      (2)
#define ABB_TX_APT_DIG_1_tx_rate_apt_END        (4)
#define ABB_TX_APT_DIG_1_tx_mode_dig_apt_START  (5)
#define ABB_TX_APT_DIG_1_tx_mode_dig_apt_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_APT_DIG_2_UNION
 结构说明  : tx_apt_dig_2 寄存器结构定义。地址偏移量:0x18，初值:0x0B，宽度:8
 寄存器说明: TX APT模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_apt       : 1;  /* bit[0]  : TX通道Q路CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_apt       : 1;  /* bit[1]  : TX通道I路CLOCK GATING控制：
                                                            0：不CLOCK GATING
                                                            1：CLOCK GATING(默认)
                                                            (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_apt     : 2;  /* bit[2-3]: TX通道DEM const系数：默认值2(在dem模块中的配置值为dem_const_xx * 2) */
        unsigned long  uddwa_dith_en_apt : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_apt    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                            0：使用CLA模式(默认)
                                                            1：使用DWA模式  */
        unsigned long  dem_lsb_bp_apt    : 1;  /* bit[6]  : TX通道DEM LSB bypass：
                                                            0：DEM LSB 打开(默认)
                                                            1：DEM LSB bypass */
        unsigned long  dem_msb_bp_apt    : 1;  /* bit[7]  : TX通道DEM MSB bypass：
                                                            0：DEM MSB 打开(默认)
                                                            1：DEM MSB bypass */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_DIG_2_UNION;
#define ABB_TX_APT_DIG_2_tx_q_pd_apt_START        (0)
#define ABB_TX_APT_DIG_2_tx_q_pd_apt_END          (0)
#define ABB_TX_APT_DIG_2_tx_i_pd_apt_START        (1)
#define ABB_TX_APT_DIG_2_tx_i_pd_apt_END          (1)
#define ABB_TX_APT_DIG_2_dem_const_apt_START      (2)
#define ABB_TX_APT_DIG_2_dem_const_apt_END        (3)
#define ABB_TX_APT_DIG_2_uddwa_dith_en_apt_START  (4)
#define ABB_TX_APT_DIG_2_uddwa_dith_en_apt_END    (4)
#define ABB_TX_APT_DIG_2_dem_dwa_en_apt_START     (5)
#define ABB_TX_APT_DIG_2_dem_dwa_en_apt_END       (5)
#define ABB_TX_APT_DIG_2_dem_lsb_bp_apt_START     (6)
#define ABB_TX_APT_DIG_2_dem_lsb_bp_apt_END       (6)
#define ABB_TX_APT_DIG_2_dem_msb_bp_apt_START     (7)
#define ABB_TX_APT_DIG_2_dem_msb_bp_apt_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_APT_DIG_3_UNION
 结构说明  : tx_apt_dig_3 寄存器结构定义。地址偏移量:0x19，初值:0x02，宽度:8
 寄存器说明: TX APT模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_apt  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_apt : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                         1'b0：SDR接口；
                                                         1'b1：DDR接口。 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_DIG_3_UNION;
#define ABB_TX_APT_DIG_3_tx_cfr_bp_apt_START   (0)
#define ABB_TX_APT_DIG_3_tx_cfr_bp_apt_END     (0)
#define ABB_TX_APT_DIG_3_tx_ddr_sdr_apt_START  (1)
#define ABB_TX_APT_DIG_3_tx_ddr_sdr_apt_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_CA_DIG_1_UNION
 结构说明  : rx_ca_dig_1 寄存器结构定义。地址偏移量:0x1A，初值:0xA0，宽度:8
 寄存器说明: RX CA模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_ca_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_ca : 1;  /* bit[0]  : RX通道补偿滤波器补偿固定系数选择：
                                                         0：固定系数1
                                                         1：固定系数2 */
        unsigned long  rx_comp_fix_ca : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                         0：系数不固定，由寄存器配置
                                                         1：系数固定 */
        unsigned long  rx_hb_bp_ca    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                         1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_ca     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                             2G,   3G_SC,  4G,  3G_DC,   TDS,   CA
                                                         00： 2.167M,15.36M,61.44M,30.72M,30.72M,122.88M(默认)
                                                         01： ------,------,30.72M,15.36M,10.24M,------
                                                         10： ------,------,15.36M,------,------,------
                                                         11： ------,------, 7.68M,------,------,------ */
        unsigned long  rx_mode_dig_ca : 3;  /* bit[5-7]: RX通道模式控制：
                                                         000：2G
                                                         001：3G_SC
                                                         010：4G &amp; ET &amp; APT
                                                         011：3G_DC
                                                         100：TDS
                                                         Others：CA(默认) */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CA_DIG_1_UNION;
#define ABB_RX_CA_DIG_1_rx_comp_sel_ca_START  (0)
#define ABB_RX_CA_DIG_1_rx_comp_sel_ca_END    (0)
#define ABB_RX_CA_DIG_1_rx_comp_fix_ca_START  (1)
#define ABB_RX_CA_DIG_1_rx_comp_fix_ca_END    (1)
#define ABB_RX_CA_DIG_1_rx_hb_bp_ca_START     (2)
#define ABB_RX_CA_DIG_1_rx_hb_bp_ca_END       (2)
#define ABB_RX_CA_DIG_1_rx_rate_ca_START      (3)
#define ABB_RX_CA_DIG_1_rx_rate_ca_END        (4)
#define ABB_RX_CA_DIG_1_rx_mode_dig_ca_START  (5)
#define ABB_RX_CA_DIG_1_rx_mode_dig_ca_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_CA_DIG_2_UNION
 结构说明  : rx_ca_dig_2 寄存器结构定义。地址偏移量:0x1B，初值:0x23，宽度:8
 寄存器说明: RX CA模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_ca_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_ca     : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_ca     : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_ca   : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                        00：gain为0.5(默认)
                                                        01：gain为0.75
                                                        10：gain为0.85
                                                        11：Reserved */
        unsigned long  rx_comp_bp_ca : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                        0：不bypass(默认)
                                                        1：bypass */
        unsigned long  tx_cfr_bp_ca  : 1;  /* bit[5]  : TX通道CFR bypass控制：
                                                        0：不bypass
                                                        1：bypass(默认) */
        unsigned long  reserved      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CA_DIG_2_UNION;
#define ABB_RX_CA_DIG_2_rxa_pd_ca_START      (0)
#define ABB_RX_CA_DIG_2_rxa_pd_ca_END        (0)
#define ABB_RX_CA_DIG_2_rxb_pd_ca_START      (1)
#define ABB_RX_CA_DIG_2_rxb_pd_ca_END        (1)
#define ABB_RX_CA_DIG_2_gain_sel_ca_START    (2)
#define ABB_RX_CA_DIG_2_gain_sel_ca_END      (3)
#define ABB_RX_CA_DIG_2_rx_comp_bp_ca_START  (4)
#define ABB_RX_CA_DIG_2_rx_comp_bp_ca_END    (4)
#define ABB_RX_CA_DIG_2_tx_cfr_bp_ca_START   (5)
#define ABB_RX_CA_DIG_2_tx_cfr_bp_ca_END     (5)


/*****************************************************************************
 结构名    : ABB_TX_CA_DIG_1_UNION
 结构说明  : tx_ca_dig_1 寄存器结构定义。地址偏移量:0x1C，初值:0x80，宽度:8
 寄存器说明: TX CA模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_ca  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                         0：不bypass(默认)
                                                         1：bypass */
        unsigned long  tx_hb_bp_ca    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                         1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_ca     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                              2G,     3G,     4G,      TDS,      CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (614.4M)
                                                         0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2：-------,--------,15.36MHz,--------,--------
                                                         3：-------,--------, 7.68MHz,--------,--------
                                                         4：-------,--------, 3.84MHz,--------,--------
                                                         Others：Reserved */
        unsigned long  tx_mode_dig_ca : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G
                                                         001：3G
                                                         010：4G &amp; ET &amp; APT
                                                         011：TDS
                                                         others：CA(默认) */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_DIG_1_UNION;
#define ABB_TX_CA_DIG_1_tx_comp_bp_ca_START   (0)
#define ABB_TX_CA_DIG_1_tx_comp_bp_ca_END     (0)
#define ABB_TX_CA_DIG_1_tx_hb_bp_ca_START     (1)
#define ABB_TX_CA_DIG_1_tx_hb_bp_ca_END       (1)
#define ABB_TX_CA_DIG_1_tx_rate_ca_START      (2)
#define ABB_TX_CA_DIG_1_tx_rate_ca_END        (4)
#define ABB_TX_CA_DIG_1_tx_mode_dig_ca_START  (5)
#define ABB_TX_CA_DIG_1_tx_mode_dig_ca_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_CA_DIG_2_UNION
 结构说明  : tx_ca_dig_2 寄存器结构定义。地址偏移量:0x1D，初值:0x03，宽度:8
 寄存器说明: TX CA模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_ca       : 1;  /* bit[0]: TX通道Q路CLOCK GATING控制：
                                                         0：不CLOCK GATING
                                                         1：CLOCK GATING(默认)
                                                         (!tx_q_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  tx_i_pd_ca       : 1;  /* bit[1]: TX通道I路CLOCK GATING控制：
                                                         0：不CLOCK GATING
                                                         1：CLOCK GATING(默认)
                                                         (!tx_i_pd)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  dem_const_ca     : 1;  /* bit[2]: TX通道DEM const系数：
                                                         0：2(默认)
                                                         1：4 */
        unsigned long  uddwa_dith_en_ca : 1;  /* bit[3]: TX通道DEM UDDWA_DITH模块使能控制：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  dither_en_ca     : 1;  /* bit[4]: TX通道SDM Dither控制：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  dem_dwa_en_ca    : 1;  /* bit[5]: TX通道DEM模式控制：
                                                         0：使用CLA模式(默认)
                                                         1：使用DWA模式  */
        unsigned long  dem_lsb_bp_ca    : 1;  /* bit[6]: TX通道DEM LSB bypass：
                                                         0：DEM LSB 打开(默认)
                                                         1：DEM LSB bypass */
        unsigned long  dem_msb_bp_ca    : 1;  /* bit[7]: TX通道DEM MSB bypass：
                                                         0：DEM MSB打开(默认)
                                                         1：DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_DIG_2_UNION;
#define ABB_TX_CA_DIG_2_tx_q_pd_ca_START        (0)
#define ABB_TX_CA_DIG_2_tx_q_pd_ca_END          (0)
#define ABB_TX_CA_DIG_2_tx_i_pd_ca_START        (1)
#define ABB_TX_CA_DIG_2_tx_i_pd_ca_END          (1)
#define ABB_TX_CA_DIG_2_dem_const_ca_START      (2)
#define ABB_TX_CA_DIG_2_dem_const_ca_END        (2)
#define ABB_TX_CA_DIG_2_uddwa_dith_en_ca_START  (3)
#define ABB_TX_CA_DIG_2_uddwa_dith_en_ca_END    (3)
#define ABB_TX_CA_DIG_2_dither_en_ca_START      (4)
#define ABB_TX_CA_DIG_2_dither_en_ca_END        (4)
#define ABB_TX_CA_DIG_2_dem_dwa_en_ca_START     (5)
#define ABB_TX_CA_DIG_2_dem_dwa_en_ca_END       (5)
#define ABB_TX_CA_DIG_2_dem_lsb_bp_ca_START     (6)
#define ABB_TX_CA_DIG_2_dem_lsb_bp_ca_END       (6)
#define ABB_TX_CA_DIG_2_dem_msb_bp_ca_START     (7)
#define ABB_TX_CA_DIG_2_dem_msb_bp_ca_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_CA_DIG_3_UNION
 结构说明  : tx_ca_dig_3 寄存器结构定义。地址偏移量:0x1E，初值:0x02，宽度:8
 寄存器说明: TX CA模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_ca  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_ca : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                        1'b0：SDR接口；
                                                        1'b1：DDR接口。 */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_DIG_3_UNION;
#define ABB_TX_CA_DIG_3_tx_cfr_bp_ca_START   (0)
#define ABB_TX_CA_DIG_3_tx_cfr_bp_ca_END     (0)
#define ABB_TX_CA_DIG_3_tx_ddr_sdr_ca_START  (1)
#define ABB_TX_CA_DIG_3_tx_ddr_sdr_ca_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_DIG_1_UNION
 结构说明  : rx_idle_dig_1 寄存器结构定义。地址偏移量:0x1F，初值:0x40，宽度:8
 寄存器说明: RX IDLE模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_idle_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_idle : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_idle : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                           0：系数不固定，由寄存器配置
                                                           1：系数固定 */
        unsigned long  rx_hb_bp_idle    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                           0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                           1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_idle     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                               2G,   3G_SC,    4G,   3G_DC,      
                                                           00： 2.167M,15.36M, 61.44M,30.72M(默认)
                                                           01： 4.33MHz,------,30.72M,------
                                                           10： ------, ------,15.36M,------
                                                           11： ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_idle : 3;  /* bit[5-7]: RX通道模式控制：
                                                           000：2G(默认)
                                                           001：3G_SC
                                                           010：4G
                                                           011：3G_DC
                                                           Others：reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_1_UNION;
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_idle_START  (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_idle_END    (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_START  (1)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_END    (1)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_START     (2)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_END       (2)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_START      (3)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_END        (4)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_START  (5)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_DIG_2_UNION
 结构说明  : rx_idle_dig_2 寄存器结构定义。地址偏移量:0x20，初值:0x43，宽度:8
 寄存器说明: RX IDLE模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      rx_idle_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_idle     : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_idle     : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_idle   : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                          00：gain为0.5(默认)
                                                          01：gain为0.75
                                                          10：gain为0.85
                                                          11：Reserved */
        unsigned long  rx_comp_bp_idle : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                          0：不bypass(默认)
                                                          1：bypass */
        unsigned long  rx_clk_inv_idle : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_idle : 1;  /* bit[6]  : RX与DBB数据接口时序配置：
                                                          1'b0：SDR接口；
                                                          1'b1：DDR接口。 */
        unsigned long  reserved        : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_2_UNION;
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_START      (0)
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_END        (0)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_START      (1)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_END        (1)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_START    (2)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_END      (3)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_START  (4)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_END    (4)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_START  (5)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_END    (5)
#define ABB_RX_IDLE_DIG_2_rx_ddr_sdr_idle_START  (6)
#define ABB_RX_IDLE_DIG_2_rx_ddr_sdr_idle_END    (6)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_DIG_1_UNION
 结构说明  : tx_idle_dig_1 寄存器结构定义。地址偏移量:0x21，初值:0x40，宽度:8
 寄存器说明: TX IDLE模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_idle  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                           0：不bypass(默认)
                                                           1：bypass */
        unsigned long  tx_hb_bp_idle    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                           0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                           1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  tx_rate_idle     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                                2G,     3G,     4G,     
                                                               (78M) (153.6M) (307.2M) 
                                                           0：4.33MHz,30.72MHz,61.44MHz(默认)
                                                           1：2.16MHz,15.36MHz,30.72MHz
                                                           2：-------,--------,15.36MHz
                                                           3：-------,--------, 7.68MHz
                                                           4：-------,--------, 3.84MHz
                                                           Others：Reserved */
        unsigned long  tx_mode_dig_idle : 3;  /* bit[5-7]: TX通道模式控制：
                                                           000：2G
                                                           001：3G
                                                           010：4G &amp; ET &amp; APT(默认)
                                                           Others：reserved */
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
 结构说明  : tx_idle_dig_2 寄存器结构定义。地址偏移量:0x22，初值:0x4B，宽度:8
 寄存器说明: TX IDLE模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_dig_2_reg;
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
        unsigned long  dem_const_idle     : 2;  /* bit[2-3]: TX通道DEM const系数：默认值2(在模块里*2） */
        unsigned long  uddwa_dith_en_idle : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_idle    : 1;  /* bit[5]  : TX通道DEM模式控制：
                                                             0：使用CLA模式(默认)
                                                             1：使用DWA模式  */
        unsigned long  tx_ddr_sdr_idle    : 1;  /* bit[6]  : 1'b0：SDR
                                                             1'b1：DDR */
        unsigned long  reserved           : 1;  /* bit[7]  : 保留 */
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
#define ABB_TX_IDLE_DIG_2_tx_ddr_sdr_idle_START     (6)
#define ABB_TX_IDLE_DIG_2_tx_ddr_sdr_idle_END       (6)


/*****************************************************************************
 结构名    : ABB_TX_IDLE_DIG_3_UNION
 结构说明  : tx_idle_dig_3 寄存器结构定义。地址偏移量:0x23，初值:0x02，宽度:8
 寄存器说明: TX IDLE模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_idle  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_idle : 1;  /* bit[1]  : TX与DBB数据接口时序配置：
                                                          1'b0：SDR接口；
                                                          1'b1：DDR接口。 */
        unsigned long  reserved        : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_START   (0)
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_END     (0)
#define ABB_TX_IDLE_DIG_3_tx_ddr_sdr_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_ddr_sdr_idle_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_2G_ANA_1_UNION
 结构说明  : rx_2g_ana_1 寄存器结构定义。地址偏移量:0x24，初值:0xF6，宽度:8
 寄存器说明: RX 2G配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      rx_2g_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_2G  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_2G : 2;  /* bit[1-2]: 模式控制：
                                                         00：4G 
                                                         01：3G
                                                         10：3G_DC
                                                         11：2G(默认) */
        unsigned long  DEM_MOD_B1_2G  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_2G    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_2G    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_2G    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_2G    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
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
 结构名    : ABB_TX_2G_ANA_1_UNION
 结构说明  : tx_2g_ana_1 寄存器结构定义。地址偏移量:0x26，初值:0x3F，宽度:8
 寄存器说明: TX 2G配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_2G : 2;  /* bit[0-1]: 模式控制：
                                                         00：4G &amp; ET &amp; APT
                                                         01：3G 
                                                         10：--
                                                         11：2G(默认) */
        unsigned long  TX_Q_PD_A_2G   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_2G   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_2G : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                         00: 1分频
                                                         01: 2分频
                                                         10: 3分频
                                                         11: 4分频(默认) */
        unsigned long  FC_2G          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                         00: 10MHz(默认)
                                                         01: 20MHz;
                                                         11:40MHz;
                                                         10:reserved */
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
#define ABB_TX_2G_ANA_1_FC_2G_START           (6)
#define ABB_TX_2G_ANA_1_FC_2G_END             (7)


/*****************************************************************************
 结构名    : ABB_RX_3G_ANA_1_UNION
 结构说明  : rx_3g_ana_1 寄存器结构定义。地址偏移量:0x28，初值:0xF2，宽度:8
 寄存器说明: RX 3G配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      rx_3g_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_3G  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_3G : 2;  /* bit[1-2]: 模式控制：
                                                         00：4G 
                                                         01：3G
                                                         10：3G_DC
                                                         11：2G(默认) */
        unsigned long  DEM_MOD_B1_3G  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_3G    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_3G    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_3G    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_3G    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_1_UNION;
#define ABB_RX_3G_ANA_1_DEM_MOD_B0_3G_START   (0)
#define ABB_RX_3G_ANA_1_DEM_MOD_B0_3G_END     (0)
#define ABB_RX_3G_ANA_1_RX_MODE_CLK_3G_START  (1)
#define ABB_RX_3G_ANA_1_RX_MODE_CLK_3G_END    (2)
#define ABB_RX_3G_ANA_1_DEM_MOD_B1_3G_START   (3)
#define ABB_RX_3G_ANA_1_DEM_MOD_B1_3G_END     (3)
#define ABB_RX_3G_ANA_1_RXB_Q_PD_3G_START     (4)
#define ABB_RX_3G_ANA_1_RXB_Q_PD_3G_END       (4)
#define ABB_RX_3G_ANA_1_RXB_I_PD_3G_START     (5)
#define ABB_RX_3G_ANA_1_RXB_I_PD_3G_END       (5)
#define ABB_RX_3G_ANA_1_RXA_Q_PD_3G_START     (6)
#define ABB_RX_3G_ANA_1_RXA_Q_PD_3G_END       (6)
#define ABB_RX_3G_ANA_1_RXA_I_PD_3G_START     (7)
#define ABB_RX_3G_ANA_1_RXA_I_PD_3G_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_3G_ANA_1_UNION
 结构说明  : tx_3g_ana_1 寄存器结构定义。地址偏移量:0x2A，初值:0x1D，宽度:8
 寄存器说明: TX 3G配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_3G : 2;  /* bit[0-1]: 模式控制：
                                                         00：4G &amp; ET &amp; APT
                                                         01：3G (默认)
                                                         10：--
                                                         11：2G */
        unsigned long  TX_Q_PD_A_3G   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_3G   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_3G : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                         00: 1分频
                                                         01: 2分频(默认)
                                                         10: 3分频
                                                         11: 4分频 */
        unsigned long  FC_3G          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                         00: 10MHz(默认)
                                                         01: 20MHz;
                                                         11:40MHz;
                                                         10:reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_ANA_1_UNION;
#define ABB_TX_3G_ANA_1_TX_MODE_CLK_3G_START  (0)
#define ABB_TX_3G_ANA_1_TX_MODE_CLK_3G_END    (1)
#define ABB_TX_3G_ANA_1_TX_Q_PD_A_3G_START    (2)
#define ABB_TX_3G_ANA_1_TX_Q_PD_A_3G_END      (2)
#define ABB_TX_3G_ANA_1_TX_I_PD_A_3G_START    (3)
#define ABB_TX_3G_ANA_1_TX_I_PD_A_3G_END      (3)
#define ABB_TX_3G_ANA_1_TX_DIV_MODE_3G_START  (4)
#define ABB_TX_3G_ANA_1_TX_DIV_MODE_3G_END    (5)
#define ABB_TX_3G_ANA_1_FC_3G_START           (6)
#define ABB_TX_3G_ANA_1_FC_3G_END             (7)


/*****************************************************************************
 结构名    : ABB_RX_4G_ANA_1_UNION
 结构说明  : rx_4g_ana_1 寄存器结构定义。地址偏移量:0x2C，初值:0xF0，宽度:8
 寄存器说明: RX 4G配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      rx_4g_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_4G  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_4G : 2;  /* bit[1-2]: 模式控制：
                                                         00：4G (默认)
                                                         01：3G
                                                         10：3G_DC
                                                         11：2G */
        unsigned long  DEM_MOD_B1_4G  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_4G    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_4G    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_4G    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_4G    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_1_UNION;
#define ABB_RX_4G_ANA_1_DEM_MOD_B0_4G_START   (0)
#define ABB_RX_4G_ANA_1_DEM_MOD_B0_4G_END     (0)
#define ABB_RX_4G_ANA_1_RX_MODE_CLK_4G_START  (1)
#define ABB_RX_4G_ANA_1_RX_MODE_CLK_4G_END    (2)
#define ABB_RX_4G_ANA_1_DEM_MOD_B1_4G_START   (3)
#define ABB_RX_4G_ANA_1_DEM_MOD_B1_4G_END     (3)
#define ABB_RX_4G_ANA_1_RXB_Q_PD_4G_START     (4)
#define ABB_RX_4G_ANA_1_RXB_Q_PD_4G_END       (4)
#define ABB_RX_4G_ANA_1_RXB_I_PD_4G_START     (5)
#define ABB_RX_4G_ANA_1_RXB_I_PD_4G_END       (5)
#define ABB_RX_4G_ANA_1_RXA_Q_PD_4G_START     (6)
#define ABB_RX_4G_ANA_1_RXA_Q_PD_4G_END       (6)
#define ABB_RX_4G_ANA_1_RXA_I_PD_4G_START     (7)
#define ABB_RX_4G_ANA_1_RXA_I_PD_4G_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_4G_ANA_1_UNION
 结构说明  : tx_4g_ana_1 寄存器结构定义。地址偏移量:0x2E，初值:0x4C，宽度:8
 寄存器说明: TX 4G配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_4G : 2;  /* bit[0-1]: 模式控制：
                                                         00：4G &amp; ET &amp; APT(默认)
                                                         01：3G 
                                                         10：--
                                                         11：2G */
        unsigned long  TX_Q_PD_A_4G   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_4G   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_4G : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                         00: 1分频(默认)
                                                         01: 2分频
                                                         10: 3分频
                                                         11: 4分频 */
        unsigned long  FC_4G          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                         00: 10MHz;
                                                         01: 20MHz;(默认)
                                                         11:40MHz;
                                                         10:reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_ANA_1_UNION;
#define ABB_TX_4G_ANA_1_TX_MODE_CLK_4G_START  (0)
#define ABB_TX_4G_ANA_1_TX_MODE_CLK_4G_END    (1)
#define ABB_TX_4G_ANA_1_TX_Q_PD_A_4G_START    (2)
#define ABB_TX_4G_ANA_1_TX_Q_PD_A_4G_END      (2)
#define ABB_TX_4G_ANA_1_TX_I_PD_A_4G_START    (3)
#define ABB_TX_4G_ANA_1_TX_I_PD_A_4G_END      (3)
#define ABB_TX_4G_ANA_1_TX_DIV_MODE_4G_START  (4)
#define ABB_TX_4G_ANA_1_TX_DIV_MODE_4G_END    (5)
#define ABB_TX_4G_ANA_1_FC_4G_START           (6)
#define ABB_TX_4G_ANA_1_FC_4G_END             (7)


/*****************************************************************************
 结构名    : ABB_RX_TDS_ANA_1_UNION
 结构说明  : rx_tds_ana_1 寄存器结构定义。地址偏移量:0x30，初值:0xF4，宽度:8
 寄存器说明: RX TDS配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      rx_tds_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_TDS  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                          000: DWA
                                                          001: CLA1
                                                          010: CLA2
                                                          011: CLA3
                                                          100: CLA4
                                                          101: CLA5
                                                          110: CLA6
                                                          111: CLA7 */
        unsigned long  RX_MODE_CLK_TDS : 2;  /* bit[1-2]: 模式控制：
                                                          00：4G &amp; ET &amp; APT
                                                          01：3G
                                                          10：3G_DC &amp; TDS(默认)
                                                          11：2G */
        unsigned long  DEM_MOD_B1_TDS  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                          000: DWA
                                                          001: CLA1
                                                          010: CLA2
                                                          011: CLA3
                                                          100: CLA4
                                                          101: CLA5
                                                          110: CLA6
                                                          111: CLA7 */
        unsigned long  RXB_Q_PD_TDS    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
                                                          (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_TDS    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
                                                          (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_TDS    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
                                                          (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_TDS    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
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
 结构名    : ABB_TX_TDS_ANA_1_UNION
 结构说明  : tx_tds_ana_1 寄存器结构定义。地址偏移量:0x32，初值:0x39，宽度:8
 寄存器说明: TX TDS配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_TDS : 2;  /* bit[0-1]: 模式控制：
                                                          00：4G &amp; ET &amp; APT
                                                          01：3G &amp; TDS(默认)
                                                          10：--
                                                          11：2G */
        unsigned long  reserved        : 1;  /* bit[2]  : Reserved */
        unsigned long  TX_Q_PD_A_TDS   : 1;  /* bit[3]  : TX_Q DAC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
                                                          (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_TDS   : 1;  /* bit[4]  : TX_I DAC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
                                                          (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_TDS : 2;  /* bit[5-6]: TX Mode 时钟控制：
                                                          00: 1分频
                                                          01: 2分频(默认)
                                                          10: 3分频
                                                          11: 4分频 */
        unsigned long  FC_TDS          : 1;  /* bit[7]  : TX filter截止频率选择：
                                                          0: 10MHz
                                                          1: 20MHz(默认) */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_1_UNION;
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_START  (0)
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_END    (1)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_START    (3)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_END      (3)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_START    (4)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_END      (4)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_START  (5)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_END    (6)
#define ABB_TX_TDS_ANA_1_FC_TDS_START           (7)
#define ABB_TX_TDS_ANA_1_FC_TDS_END             (7)


/*****************************************************************************
 结构名    : ABB_TX_ET_ANA_1_UNION
 结构说明  : tx_et_ana_1 寄存器结构定义。地址偏移量:0x34，初值:0x4C，宽度:8
 寄存器说明: TX ET配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_ET : 2;  /* bit[0-1]: 模式控制：
                                                         00：4G &amp; ET &amp; APT(默认)
                                                         01：3G 
                                                         10：--
                                                         11：2G */
        unsigned long  TX_Q_PD_A_ET   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_Q_PD)|(WG_TX_EN &amp;&amp; WG_LINE_CONTROL_MODE~
                                                         =ET &amp;&amp; WG_LINE_CONTROL_MODE~=APT) = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_ET   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_I_PD)|WG_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_ET : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                         00: 1分频(默认)
                                                         01: 2分频
                                                         10: 3分频
                                                         11: 4分频 */
        unsigned long  FC_ET          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                         00: 10MHz;
                                                         01: 20MHz;(默认)
                                                         11:40MHz;
                                                         10:reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_ANA_1_UNION;
#define ABB_TX_ET_ANA_1_TX_MODE_CLK_ET_START  (0)
#define ABB_TX_ET_ANA_1_TX_MODE_CLK_ET_END    (1)
#define ABB_TX_ET_ANA_1_TX_Q_PD_A_ET_START    (2)
#define ABB_TX_ET_ANA_1_TX_Q_PD_A_ET_END      (2)
#define ABB_TX_ET_ANA_1_TX_I_PD_A_ET_START    (3)
#define ABB_TX_ET_ANA_1_TX_I_PD_A_ET_END      (3)
#define ABB_TX_ET_ANA_1_TX_DIV_MODE_ET_START  (4)
#define ABB_TX_ET_ANA_1_TX_DIV_MODE_ET_END    (5)
#define ABB_TX_ET_ANA_1_FC_ET_START           (6)
#define ABB_TX_ET_ANA_1_FC_ET_END             (7)


/*****************************************************************************
 结构名    : ABB_TX_APT_ANA_1_UNION
 结构说明  : tx_apt_ana_1 寄存器结构定义。地址偏移量:0x36，初值:0x7C，宽度:8
 寄存器说明: TX APT配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_APT : 2;  /* bit[0-1]: 模式控制：
                                                          00：4G &amp; ET &amp; APT(默认)
                                                          01：3G 
                                                          10：--
                                                          11：2G */
        unsigned long  TX_Q_PD_A_APT   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
                                                          (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_APT   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                          0:Power On
                                                          1:Power Down(默认)
                                                          (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_APT : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                          00: 1分频
                                                          01: 2分频
                                                          10: 3分频
                                                          11: 4分频(默认) */
        unsigned long  FC_APT          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                          00: 10MHz;
                                                          01: 20MHz;(默认)
                                                          11:40MHz;
                                                          10:reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_ANA_1_UNION;
#define ABB_TX_APT_ANA_1_TX_MODE_CLK_APT_START  (0)
#define ABB_TX_APT_ANA_1_TX_MODE_CLK_APT_END    (1)
#define ABB_TX_APT_ANA_1_TX_Q_PD_A_APT_START    (2)
#define ABB_TX_APT_ANA_1_TX_Q_PD_A_APT_END      (2)
#define ABB_TX_APT_ANA_1_TX_I_PD_A_APT_START    (3)
#define ABB_TX_APT_ANA_1_TX_I_PD_A_APT_END      (3)
#define ABB_TX_APT_ANA_1_TX_DIV_MODE_APT_START  (4)
#define ABB_TX_APT_ANA_1_TX_DIV_MODE_APT_END    (5)
#define ABB_TX_APT_ANA_1_FC_APT_START           (6)
#define ABB_TX_APT_ANA_1_FC_APT_END             (7)


/*****************************************************************************
 结构名    : ABB_RX_CA_ANA_1_UNION
 结构说明  : rx_ca_ana_1 寄存器结构定义。地址偏移量:0x38，初值:0xF0，宽度:8
 寄存器说明: RX CA配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      rx_ca_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_CA  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000: DWA
                                                         001: CLA1
                                                         010: CLA2
                                                         011: CLA3
                                                         100: CLA4
                                                         101: CLA5
                                                         110: CLA6
                                                         111: CLA7 */
        unsigned long  RX_MODE_CLK_CA : 2;  /* bit[1-2]: 模式控制：
                                                         00：4G &amp; ET &amp; APT(默认)
                                                         01：3G
                                                         10：3G_DC &amp; TDS
                                                         11：2G */
        unsigned long  DEM_MOD_B1_CA  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000: DWA
                                                         001: CLA1
                                                         010: CLA2
                                                         011: CLA3
                                                         100: CLA4
                                                         101: CLA5
                                                         110: CLA6
                                                         111: CLA7 */
        unsigned long  RXB_Q_PD_CA    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_Q_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXB_I_PD_CA    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  RXA_Q_PD_CA    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXA_Q_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  RXA_I_PD_CA    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CA_ANA_1_UNION;
#define ABB_RX_CA_ANA_1_DEM_MOD_B0_CA_START   (0)
#define ABB_RX_CA_ANA_1_DEM_MOD_B0_CA_END     (0)
#define ABB_RX_CA_ANA_1_RX_MODE_CLK_CA_START  (1)
#define ABB_RX_CA_ANA_1_RX_MODE_CLK_CA_END    (2)
#define ABB_RX_CA_ANA_1_DEM_MOD_B1_CA_START   (3)
#define ABB_RX_CA_ANA_1_DEM_MOD_B1_CA_END     (3)
#define ABB_RX_CA_ANA_1_RXB_Q_PD_CA_START     (4)
#define ABB_RX_CA_ANA_1_RXB_Q_PD_CA_END       (4)
#define ABB_RX_CA_ANA_1_RXB_I_PD_CA_START     (5)
#define ABB_RX_CA_ANA_1_RXB_I_PD_CA_END       (5)
#define ABB_RX_CA_ANA_1_RXA_Q_PD_CA_START     (6)
#define ABB_RX_CA_ANA_1_RXA_Q_PD_CA_END       (6)
#define ABB_RX_CA_ANA_1_RXA_I_PD_CA_START     (7)
#define ABB_RX_CA_ANA_1_RXA_I_PD_CA_END       (7)


/*****************************************************************************
 结构名    : ABB_TX_CA_ANA_1_UNION
 结构说明  : tx_ca_ana_1 寄存器结构定义。地址偏移量:0x3A，初值:0xF8，宽度:8
 寄存器说明: TX CA配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_CA : 2;  /* bit[0-1]: 模式控制：
                                                         00：4G &amp; ET &amp; APT(默认)
                                                         01：3G &amp; TDS
                                                         10：--
                                                         11：2G */
        unsigned long  reserved       : 1;  /* bit[2]  : Reserved */
        unsigned long  TX_Q_PD_A_CA   : 1;  /* bit[3]  : TX_Q DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_CA   : 1;  /* bit[4]  : TX_I DAC Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认)
                                                         (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_CA : 2;  /* bit[5-6]: TX Mode 时钟控制：
                                                         00: 1分频
                                                         01: 2分频
                                                         10: 3分频
                                                         11: 4分频(默认) */
        unsigned long  FC_CA          : 1;  /* bit[7]  : TX filter截止频率选择：
                                                         0: 10MHz
                                                         1: 20MHz(默认) */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_ANA_1_UNION;
#define ABB_TX_CA_ANA_1_TX_MODE_CLK_CA_START  (0)
#define ABB_TX_CA_ANA_1_TX_MODE_CLK_CA_END    (1)
#define ABB_TX_CA_ANA_1_TX_Q_PD_A_CA_START    (3)
#define ABB_TX_CA_ANA_1_TX_Q_PD_A_CA_END      (3)
#define ABB_TX_CA_ANA_1_TX_I_PD_A_CA_START    (4)
#define ABB_TX_CA_ANA_1_TX_I_PD_A_CA_END      (4)
#define ABB_TX_CA_ANA_1_TX_DIV_MODE_CA_START  (5)
#define ABB_TX_CA_ANA_1_TX_DIV_MODE_CA_END    (6)
#define ABB_TX_CA_ANA_1_FC_CA_START           (7)
#define ABB_TX_CA_ANA_1_FC_CA_END             (7)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_ANA_1_UNION
 结构说明  : rx_idle_ana_1 寄存器结构定义。地址偏移量:0x3C，初值:0xF0，宽度:8
 寄存器说明: RX IDLE配置寄存器，经过线控逻辑后后送至reg_analog_wr00。
*****************************************************************************/
typedef union
{
    unsigned long      rx_idle_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_IDLE  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_IDLE : 2;  /* bit[1-2]: 模式控制：
                                                           00：4G (默认)
                                                           01：3G
                                                           10：3G_DC
                                                           11：2G */
        unsigned long  DEM_MOD_B1_IDLE  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_IDLE    : 1;  /* bit[4]  : RXB_Q ADC Power Down控制
                                                           0:Power On
                                                           1:Power Down(默认) */
        unsigned long  RXB_I_PD_IDLE    : 1;  /* bit[5]  : RXB_I ADC Power Down控制
                                                           0:Power On
                                                           1:Power Down(默认) */
        unsigned long  RXA_Q_PD_IDLE    : 1;  /* bit[6]  : RXA_Q ADC Power Down控制
                                                           0:Power On
                                                           1:Power Down(默认) */
        unsigned long  RXA_I_PD_IDLE    : 1;  /* bit[7]  : RXA_I ADC Power Down控制
                                                           0:Power On
                                                           1:Power Down(默认) */
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
 结构名    : ABB_TX_IDLE_ANA_1_UNION
 结构说明  : tx_idle_ana_1 寄存器结构定义。地址偏移量:0x3E，初值:0x4C，宽度:8
 寄存器说明: TX IDLE配置寄存器，经过线控逻辑后后送至reg_analog_wr48。
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_IDLE : 2;  /* bit[0-1]: 模式控制：
                                                           00：4G &amp; ET &amp; APT(默认)
                                                           01：3G 
                                                           10：--
                                                           11：2G */
        unsigned long  TX_Q_PD_A_IDLE   : 1;  /* bit[2]  : TX_Q DAC Power Down控制
                                                           0:Power On
                                                           1:Power Down(默认)
                                                           (!TX_Q_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_I_PD_A_IDLE   : 1;  /* bit[3]  : TX_I DAC Power Down控制
                                                           0:Power On
                                                           1:Power Down(默认)
                                                           (!TX_I_PD)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  TX_DIV_MODE_IDLE : 2;  /* bit[4-5]: TX Mode 时钟控制：
                                                           00: 1分频(默认)
                                                           01: 2分频
                                                           10: 3分频
                                                           11: 4分频 */
        unsigned long  FC_IDLE          : 2;  /* bit[6-7]: TX filter截止频率选择：
                                                           00: 10MHz;
                                                           01: 20MHz;(默认)
                                                           11:40MHz;
                                                           10:reserved */
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
 结构名    : ABB_CH1_TESTMODE_UNION
 结构说明  : ch1_testmode 寄存器结构定义。地址偏移量:0x41，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_testmode_reg;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : 保留 */
        unsigned long  ch1_rx_chnl_sel : 2;  /* bit[1-2]: RX模拟测试模式下通道选择：
                                                          00：输出RXA I模拟调制器数据(默认)
                                                          01：输出RXA Q模拟调制器数据
                                                          10：输出RXB I模拟调制器数据
                                                          11：输出RXB Q模拟调制器数据 */
        unsigned long  ch1_test_mode   : 3;  /* bit[3-5]: bit[4:3]测试模式控制：
                                                          00：正常模式(默认)
                                                          01：数字算法逻辑环回模式
                                                          10：RX模拟测试模式(bypass RX数字滤波器)
                                                          11：数字接口环回模式
                                                          bit[5]：reserved */
        unsigned long  ch1_sw_rst      : 1;  /* bit[6]  : 配置的软复位信号：
                                                          0：软件不启动软复位(默认)
                                                          1：软件启动软复位 */
        unsigned long  reserved_1      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TESTMODE_UNION;
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_START  (1)
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_END    (2)
#define ABB_CH1_TESTMODE_ch1_test_mode_START    (3)
#define ABB_CH1_TESTMODE_ch1_test_mode_END      (5)
#define ABB_CH1_TESTMODE_ch1_sw_rst_START       (6)
#define ABB_CH1_TESTMODE_ch1_sw_rst_END         (6)


/*****************************************************************************
 结构名    : ABB_CH1_CTRL_UNION
 结构说明  : ch1_ctrl 寄存器结构定义。地址偏移量:0x42，初值:0x00，宽度:8
 寄存器说明: 通道控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_ctrl_reg;
    struct
    {
        unsigned long  ch1_et_sel : 1;  /* bit[0]  : ET/APT通道选择：
                                                     0：选择TX通道I路做ET/APT
                                                     1：选择TX通道Q路做ET/APT */
        unsigned long  reserved   : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CTRL_UNION;
#define ABB_CH1_CTRL_ch1_et_sel_START  (0)
#define ABB_CH1_CTRL_ch1_et_sel_END    (0)


/*****************************************************************************
 结构名    : ABB_CH1_CFR_CTRL_UNION
 结构说明  : ch1_cfr_ctrl 寄存器结构定义。地址偏移量:0x43，初值:0x44，宽度:8
 寄存器说明: CFR峰值检测窗长寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_cfr_ctrl_reg;
    struct
    {
        unsigned long  ch1_cfr_pdet_sel : 2;  /* bit[0-1]: CFR峰值检测方式：
                                                           00：单点提峰
                                                           01：区间提峰
                                                           10：滑窗提峰
                                                           11：全部峰值 */
        unsigned long  ch1_cfr_fir_sel  : 1;  /* bit[2]  : CFR滤波器选择：
                                                           0：bypass滤波器
                                                           1：不bypass滤波器 */
        unsigned long  reserved         : 1;  /* bit[3]  : 保留 */
        unsigned long  ch1_cfr_fir_fac  : 4;  /* bit[4-7]: CFR削波因子 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CFR_CTRL_UNION;
#define ABB_CH1_CFR_CTRL_ch1_cfr_pdet_sel_START  (0)
#define ABB_CH1_CFR_CTRL_ch1_cfr_pdet_sel_END    (1)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_sel_START   (2)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_sel_END     (2)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_fac_START   (4)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_fac_END     (7)


/*****************************************************************************
 结构名    : ABB_CH1_LINE_CTRL_SEL_UNION
 结构说明  : ch1_line_ctrl_sel 寄存器结构定义。地址偏移量:0x44，初值:0xFF，宽度:8
 寄存器说明: 线控选择。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_line_ctrl_sel_reg;
    struct
    {
        unsigned long  ch1_line_ctrl_2g_sel  : 1;  /* bit[0]: 选择2G线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_3g_sel  : 1;  /* bit[1]: 选择3G线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_4g_sel  : 1;  /* bit[2]: 选择4G线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_apt_sel : 1;  /* bit[3]: 选择APT线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_et_sel  : 1;  /* bit[4]: 选择ET线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_tx_sel  : 1;  /* bit[5]: 选择TX_EN线控，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_rxb_sel : 1;  /* bit[6]: 选择RXB_EN线控，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_rxa_en  : 1;  /* bit[7]: 选择RXA_EN线控，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_CTRL_SEL_UNION;
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_2g_sel_START   (0)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_2g_sel_END     (0)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_3g_sel_START   (1)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_3g_sel_END     (1)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_4g_sel_START   (2)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_4g_sel_END     (2)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_apt_sel_START  (3)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_apt_sel_END    (3)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_et_sel_START   (4)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_et_sel_END     (4)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_tx_sel_START   (5)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_tx_sel_END     (5)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxb_sel_START  (6)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxb_sel_END    (6)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxa_en_START   (7)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxa_en_END     (7)


/*****************************************************************************
 结构名    : ABB_CH1_RX_DIG_RPT_UNION
 结构说明  : ch1_rx_dig_rpt 寄存器结构定义。地址偏移量:0x45，初值:0x00，宽度:8
 寄存器说明: RX数字工作模式上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rx_dig_rpt_reg;
    struct
    {
        unsigned long  ch1_rx_comp_sel_rpt : 1;  /* bit[0]  : Reserved */
        unsigned long  ch1_rx_comp_fix_rpt : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                              0：系数不固定，由寄存器配置
                                                              1：系数固定 */
        unsigned long  ch1_rx_hb_bp_rpt    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                              0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2
                                                              1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch1_rx_rate_rpt     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                  2G,   3G_SC,    4G,   3G_DC,      
                                                              00： 2.167M,15.36M, 61.44M,30.72M
                                                              01： 4.33MHz,------,30.72M,------
                                                              10： ------, ------,15.36M,------
                                                              11： ------, ------, 7.68M,------ */
        unsigned long  ch1_rx_mode_dig_rpt : 3;  /* bit[5-7]: RX通道模式控制：
                                                              000：2G
                                                              001：3G_SC
                                                              010：4G
                                                              011：3G_DC
                                                              Others：reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_DIG_RPT_UNION;
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_sel_rpt_START  (0)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_sel_rpt_END    (0)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_fix_rpt_START  (1)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_fix_rpt_END    (1)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_hb_bp_rpt_START     (2)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_hb_bp_rpt_END       (2)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_rate_rpt_START      (3)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_rate_rpt_END        (4)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_mode_dig_rpt_START  (5)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_mode_dig_rpt_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_TX_DIG_RPT_UNION
 结构说明  : ch1_tx_dig_rpt 寄存器结构定义。地址偏移量:0x46，初值:0x02，宽度:8
 寄存器说明: TX数字工作模式上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_tx_dig_rpt_reg;
    struct
    {
        unsigned long  ch1_tx_comp_bp_tpr  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                              0：不bypass
                                                              1：bypass */
        unsigned long  ch1_tx_hb_bp_rpt    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                              0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
                                                              1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  ch1_tx_rate_rpt     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                                   2G,     3G,     4G,     
                                                                  (78M) (153.6M) (307.2M) 
                                                              0：4.33MHz,30.72MHz,61.44MHz
                                                              1：2.16MHz,15.36MHz,30.72MHz
                                                              2：-------,--------,15.36MHz
                                                              3：-------,--------, 7.68MHz
                                                              4：-------,--------, 3.84MHz
                                                              Others：Reserved */
        unsigned long  ch1_tx_mode_dig_rpt : 3;  /* bit[5-7]: TX通道模式控制：
                                                              000：2G
                                                              001：3G
                                                              010：4G &amp; ET &amp; APT
                                                              Others：reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_DIG_RPT_UNION;
#define ABB_CH1_TX_DIG_RPT_ch1_tx_comp_bp_tpr_START   (0)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_comp_bp_tpr_END     (0)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_hb_bp_rpt_START     (1)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_hb_bp_rpt_END       (1)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_rate_rpt_START      (2)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_rate_rpt_END        (4)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_mode_dig_rpt_START  (5)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_mode_dig_rpt_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_I_COEF1_UNION
 结构说明  : ch1_rxa_i_coef1 寄存器结构定义。地址偏移量:0x4B，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_i_coef1_reg;
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
 结构说明  : ch1_rxa_i_coef3 寄存器结构定义。地址偏移量:0x4D，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_i_coef3_reg;
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
 结构说明  : ch1_rxa_q_coef1 寄存器结构定义。地址偏移量:0x50，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_q_coef1_reg;
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
 结构说明  : ch1_rxa_q_coef3 寄存器结构定义。地址偏移量:0x52，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_q_coef3_reg;
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
 结构说明  : ch1_rxb_i_coef1 寄存器结构定义。地址偏移量:0x55，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_i_coef1_reg;
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
 结构说明  : ch1_rxb_i_coef3 寄存器结构定义。地址偏移量:0x57，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_i_coef3_reg;
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
 结构说明  : ch1_rxb_q_coef1 寄存器结构定义。地址偏移量:0x5A，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_q_coef1_reg;
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
 结构说明  : ch1_rxb_q_coef3 寄存器结构定义。地址偏移量:0x5C，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_q_coef3_reg;
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
    unsigned long      ch1_reg_rxa_dcr_cfg_reg;
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
    unsigned long      ch1_reg_rxb_dcr_cfg_reg;
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
    unsigned long      ch1_reg_rx_dcr_ctrl_reg;
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
    unsigned long      ch1_rxa_blocking_reg;
    struct
    {
        unsigned long  ch1_rxa_blk_coeff : 5;  /* bit[0-4]: RXA天线BLOCKING上报值，系数，2的M次方 */
        unsigned long  ch1_rxa_blk_power : 3;  /* bit[5-7]: RXA天线BLOCKING上报值,能量大小N */
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
    unsigned long      ch1_rxb_blocking_reg;
    struct
    {
        unsigned long  ch1_rxb_blk_coeff : 5;  /* bit[0-4]: RXB天线BLOCKING上报值，系数，2的M次方 */
        unsigned long  ch1_rxb_blk_power : 3;  /* bit[5-7]: RXB天线BLOCKING上报值,能量大小N */
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
    unsigned long      ch1_reg_rxa_dc_i_2_reg;
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
    unsigned long      ch1_reg_rxa_dc_q_2_reg;
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
    unsigned long      ch1_reg_rxb_dc_i_2_reg;
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
    unsigned long      ch1_reg_rxb_dc_q_2_reg;
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
 结构说明  : ch1_reg_debug_dig0 寄存器结构定义。地址偏移量:0x6B，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_dig0_reg;
    struct
    {
        unsigned long  ch1_sdm_rst_ctrl : 1;  /* bit[0]  : TX通道SDM模块异常时复位控制
                                                           0：只复位SDM模块
                                                           1：复位整个TX通道 */
        unsigned long  ch1_dem_mode     : 1;  /* bit[1]  : TX通道DEM校准工作模式
                                                           0：正常工作
                                                           1：校准态，DEM输出为dem_code_man */
        unsigned long  ch1_tx_dem_sat   : 2;  /* bit[2-3]: Reserved */
        unsigned long  ch1_dither_en    : 1;  /* bit[4]  : Reserved */
        unsigned long  reserved         : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_DIG0_UNION;
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_START  (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_END    (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_START      (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_END        (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_START    (2)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_END      (3)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_START     (4)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_END       (4)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_DIG4_UNION
 结构说明  : ch1_reg_debug_dig4 寄存器结构定义。地址偏移量:0x6F，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_dig4_reg;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch1_cic4_cic6_sel : 1;  /* bit[4]  : RX通道CIC4/CIC6滤波器选择：
                                                            0: 选择CIC4滤波器
                                                            1: 选择CIC6滤波器 */
        unsigned long  ch1_sw_gate_bp    : 1;  /* bit[5]  : 切换门控使能bypass信号。1表示门控使能功能旁路。 */
        unsigned long  ch1_cic_rst_bp    : 1;  /* bit[6]  : 切换复位bypass信号。1表示切换复位功能旁路。 */
        unsigned long  ch1_div_en_bp     : 1;  /* bit[7]  : div_en控制分频器bypass信号，0：div_en控制分频器；1：div_en不控制分频器，分频器使能始终为1。. */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_DIG4_UNION;
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic4_cic6_sel_START  (4)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic4_cic6_sel_END    (4)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_sw_gate_bp_START     (5)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_sw_gate_bp_END       (5)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic_rst_bp_START     (6)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic_rst_bp_END       (6)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_div_en_bp_START      (7)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_div_en_bp_END        (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR02_UNION
 结构说明  : ch1_reg_analog_wr02 寄存器结构定义。地址偏移量:0x70，初值:0x0F，宽度:8
 寄存器说明: Power Down控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr02_reg;
    struct
    {
        unsigned long  CH1_RXC_Q_PD   : 1;  /* bit[0]  : Reserved */
        unsigned long  CH1_RXC_I_PD   : 1;  /* bit[1]  : Reserved */
        unsigned long  CH1_PLL624_PD  : 1;  /* bit[2]  : PLLV2 Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认) */
        unsigned long  CH1_PLL6144_PD : 1;  /* bit[3]  : PLLV1 Power Down控制
                                                         0:Power On(默认)
                                                         1:Power Down */
        unsigned long  reserved       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR02_UNION;
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_Q_PD_START    (0)
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_Q_PD_END      (0)
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_I_PD_START    (1)
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_I_PD_END      (1)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL624_PD_START   (2)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL624_PD_END     (2)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL6144_PD_START  (3)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL6144_PD_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR03_UNION
 结构说明  : ch1_reg_analog_wr03 寄存器结构定义。地址偏移量:0x71，初值:0x30，宽度:8
 寄存器说明: 数模接口时钟控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr03_reg;
    struct
    {
        unsigned long  reserved_0        : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH1_TX_CLKD_CTRL  : 1;  /* bit[3]  : TX 采样时钟沿选择：
                                                            0: 正沿
                                                            1: 反沿(默认) */
        unsigned long  CH1_CLK_61D44M_PD : 1;  /* bit[4]  : CLK_61D44M Power Down控制
                                                            0:Power On
                                                            1:Power Down(默认) */
        unsigned long  CH1_CLK_52M_PD    : 1;  /* bit[5]  : CLK_52M Power Down控制
                                                            0:Power On
                                                            1:Power Down(默认) */
        unsigned long  CH1_245M_EN       : 1;  /* bit[6]  : 245M输出控制：
                                                            0: 不输出
                                                            1: 输出 */
        unsigned long  reserved_1        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR03_UNION;
#define ABB_CH1_REG_ANALOG_WR03_CH1_TX_CLKD_CTRL_START   (3)
#define ABB_CH1_REG_ANALOG_WR03_CH1_TX_CLKD_CTRL_END     (3)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_61D44M_PD_START  (4)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_61D44M_PD_END    (4)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_52M_PD_START     (5)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_52M_PD_END       (5)
#define ABB_CH1_REG_ANALOG_WR03_CH1_245M_EN_START        (6)
#define ABB_CH1_REG_ANALOG_WR03_CH1_245M_EN_END          (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR04_UNION
 结构说明  : ch1_reg_analog_wr04 寄存器结构定义。地址偏移量:0x72，初值:0x0C，宽度:8
 寄存器说明: Other控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr04_reg;
    struct
    {
        unsigned long  CH1_EN_CAL       : 1;  /* bit[0]  : Calibration enable（默认为0）
                                                           上升沿启动Calibration过程 */
        unsigned long  reserved_0       : 1;  /* bit[1]  : Reserved */
        unsigned long  CH1_TX_AUTO_TUNE : 1;  /* bit[2]  : TX ADC自动tuning控制
                                                           0：手动tuning，tuning选择TX_TUNE1,TX_TUNE2,TX_TUNE3的值(默认)
                                                           1：自动tuning，TX通道的calibration值为CAL_VALUE */
        unsigned long  CH1_RX_AUTO_TUNE : 1;  /* bit[3]  : RX ADC自动tuning控制
                                                           0：手动tuning，tuning选择RX_TUNE1,RX_TUNE2,RX_TUNE3的值(默认)
                                                           1：自动tuning，RX通道的calibration值为CAL_VALUE */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR04_UNION;
#define ABB_CH1_REG_ANALOG_WR04_CH1_EN_CAL_START        (0)
#define ABB_CH1_REG_ANALOG_WR04_CH1_EN_CAL_END          (0)
#define ABB_CH1_REG_ANALOG_WR04_CH1_TX_AUTO_TUNE_START  (2)
#define ABB_CH1_REG_ANALOG_WR04_CH1_TX_AUTO_TUNE_END    (2)
#define ABB_CH1_REG_ANALOG_WR04_CH1_RX_AUTO_TUNE_START  (3)
#define ABB_CH1_REG_ANALOG_WR04_CH1_RX_AUTO_TUNE_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR05_UNION
 结构说明  : ch1_reg_analog_wr05 寄存器结构定义。地址偏移量:0x73，初值:0x40，宽度:8
 寄存器说明: ADC第一级积分器电容tuning寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr05_reg;
    struct
    {
        unsigned long  CH1_RX_TUNE1 : 7;  /* bit[0-6]: ADC第一级积分器电容tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR05_UNION;
#define ABB_CH1_REG_ANALOG_WR05_CH1_RX_TUNE1_START  (0)
#define ABB_CH1_REG_ANALOG_WR05_CH1_RX_TUNE1_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR06_UNION
 结构说明  : ch1_reg_analog_wr06 寄存器结构定义。地址偏移量:0x74，初值:0x40，宽度:8
 寄存器说明: ADC第二级积分器电容tuning寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr06_reg;
    struct
    {
        unsigned long  CH1_RX_TUNE2 : 7;  /* bit[0-6]: ADC第二级积分器电容tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR06_UNION;
#define ABB_CH1_REG_ANALOG_WR06_CH1_RX_TUNE2_START  (0)
#define ABB_CH1_REG_ANALOG_WR06_CH1_RX_TUNE2_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR07_UNION
 结构说明  : ch1_reg_analog_wr07 寄存器结构定义。地址偏移量:0x75，初值:0x40，宽度:8
 寄存器说明: ADC第三级积分器电容tuning寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr07_reg;
    struct
    {
        unsigned long  CH1_RX_TUNE3 : 7;  /* bit[0-6]: ADC第三级积分器电容tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR07_UNION;
#define ABB_CH1_REG_ANALOG_WR07_CH1_RX_TUNE3_START  (0)
#define ABB_CH1_REG_ANALOG_WR07_CH1_RX_TUNE3_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR08_UNION
 结构说明  : ch1_reg_analog_wr08 寄存器结构定义。地址偏移量:0x76，初值:0x40，宽度:8
 寄存器说明: DAC Tuning控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr08_reg;
    struct
    {
        unsigned long  CH1_TX_TUNE1 : 7;  /* bit[0-6]: TX_TUNE1控制信号 */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR08_UNION;
#define ABB_CH1_REG_ANALOG_WR08_CH1_TX_TUNE1_START  (0)
#define ABB_CH1_REG_ANALOG_WR08_CH1_TX_TUNE1_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR09_UNION
 结构说明  : ch1_reg_analog_wr09 寄存器结构定义。地址偏移量:0x77，初值:0x40，宽度:8
 寄存器说明: DAC Tuning控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr09_reg;
    struct
    {
        unsigned long  CH1_TX_TUNE2 : 7;  /* bit[0-6]: TX_TUNE2控制信号 */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR09_UNION;
#define ABB_CH1_REG_ANALOG_WR09_CH1_TX_TUNE2_START  (0)
#define ABB_CH1_REG_ANALOG_WR09_CH1_TX_TUNE2_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR10_UNION
 结构说明  : ch1_reg_analog_wr10 寄存器结构定义。地址偏移量:0x78，初值:0x40，宽度:8
 寄存器说明: DAC Tuning控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr10_reg;
    struct
    {
        unsigned long  CH1_TX_TUNE3 : 7;  /* bit[0-6]: TX_TUNE3控制信号 */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR10_UNION;
#define ABB_CH1_REG_ANALOG_WR10_CH1_TX_TUNE3_START  (0)
#define ABB_CH1_REG_ANALOG_WR10_CH1_TX_TUNE3_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR38_UNION
 结构说明  : ch1_reg_analog_wr38 寄存器结构定义。地址偏移量:0x79，初值:0x60，宽度:8
 寄存器说明: 共模电平控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr38_reg;
    struct
    {
        unsigned long  reserved              : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH1_OFFSET_CAL_DAC_EN : 1;  /* bit[3]  : Reserved */
        unsigned long  CH1_SARADC_REF_RANGE  : 1;  /* bit[4]  : Reserved */
        unsigned long  CH1_TX_CM_CON_MODE    : 2;  /* bit[5-6]: Reserved */
        unsigned long  CH1_RX_ADC_CM_CON_EN  : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR38_UNION;
#define ABB_CH1_REG_ANALOG_WR38_CH1_OFFSET_CAL_DAC_EN_START  (3)
#define ABB_CH1_REG_ANALOG_WR38_CH1_OFFSET_CAL_DAC_EN_END    (3)
#define ABB_CH1_REG_ANALOG_WR38_CH1_SARADC_REF_RANGE_START   (4)
#define ABB_CH1_REG_ANALOG_WR38_CH1_SARADC_REF_RANGE_END     (4)
#define ABB_CH1_REG_ANALOG_WR38_CH1_TX_CM_CON_MODE_START     (5)
#define ABB_CH1_REG_ANALOG_WR38_CH1_TX_CM_CON_MODE_END       (6)
#define ABB_CH1_REG_ANALOG_WR38_CH1_RX_ADC_CM_CON_EN_START   (7)
#define ABB_CH1_REG_ANALOG_WR38_CH1_RX_ADC_CM_CON_EN_END     (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_WR39_UNION
 结构说明  : ch1_reg_analog_wr39 寄存器结构定义。地址偏移量:0x7A，初值:0x03，宽度:8
 寄存器说明: DUM控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr39_reg;
    struct
    {
        unsigned long  CH1_DUM_EN_Q   : 1;  /* bit[0]  : TX Q channel  dummy logic control signal
                                                         1: enable(默认)
                                                         0: disable */
        unsigned long  CH1_DUM_EN_I   : 1;  /* bit[1]  : TX I channel  dummy logic control signal
                                                         1: enable(默认)
                                                         0: disable */
        unsigned long  reserved       : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH1_DEM_MOD_B2 : 1;  /* bit[7]  : RX DEM Mode Selection,bit 2
                                                         000: DWA
                                                         001: CLA1
                                                         010: CLA2
                                                         011: CLA3
                                                         100: CLA4
                                                         101: CLA5
                                                         110: CLA6
                                                         111: CLA7 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR39_UNION;
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_Q_START    (0)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_Q_END      (0)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_I_START    (1)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_I_END      (1)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DEM_MOD_B2_START  (7)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DEM_MOD_B2_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_RO0_UNION
 结构说明  : ch1_reg_analog_ro0 寄存器结构定义。地址偏移量:0x7B，初值:0x00，宽度:8
 寄存器说明: 标志位只读寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_ro0_reg;
    struct
    {
        unsigned long  reserved     : 5;  /* bit[0-4]: Reserved */
        unsigned long  CH1_CAL_DONE : 1;  /* bit[5]  : RC Calibration Done信号 */
        unsigned long  CH1_LOCK2    : 1;  /* bit[6]  : GPLL的LOCK信号 */
        unsigned long  CH1_LOCK1    : 1;  /* bit[7]  : WPLL的LOCK信号 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_RO0_UNION;
#define ABB_CH1_REG_ANALOG_RO0_CH1_CAL_DONE_START  (5)
#define ABB_CH1_REG_ANALOG_RO0_CH1_CAL_DONE_END    (5)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK2_START     (6)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK2_END       (6)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK1_START     (7)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK1_END       (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_ANALOG_RO1_UNION
 结构说明  : ch1_reg_analog_ro1 寄存器结构定义。地址偏移量:0x7C，初值:0x00，宽度:8
 寄存器说明: RC校准只读寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_ro1_reg;
    struct
    {
        unsigned long  CH1_RX_CAL_VALUE : 7;  /* bit[0-6]: RC Calibration校准值 */
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_RO1_UNION;
#define ABB_CH1_REG_ANALOG_RO1_CH1_RX_CAL_VALUE_START  (0)
#define ABB_CH1_REG_ANALOG_RO1_CH1_RX_CAL_VALUE_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA0_UNION
 结构说明  : ch1_reg_debug_ana0 寄存器结构定义。地址偏移量:0x80，初值:0x32，宽度:8
 寄存器说明: 模拟调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana0_reg;
    struct
    {
        unsigned long  CH1_CLK_REF_SEL  : 1;  /* bit[0]  : PLL的参考时钟选择
                                                           1: CLKIN_SYSTEM作为PLL的参考时钟
                                                           0: TCXO Buffer输出作为PLL参考时钟 */
        unsigned long  CH1_PLL_OCLK_SEL : 3;  /* bit[1-3]: 工作时钟选择
                                                           001：选择来自于PLL的时钟作为工作时钟
                                                           010：选择来自于CLKIN_SYSTEM的外灌时钟作为工作时钟
                                                           100：选择来自于TCXO_IN的时钟作为工作时钟 */
        unsigned long  CH1_PLL_PFD_CTRL : 2;  /* bit[4-5]: PLL鉴频鉴相器控制
                                                           x0：鉴频鉴相器一直输出Up信号
                                                           01: 鉴频鉴相器一直输出Down信号
                                                           11：鉴频鉴相器正常工作 */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA0_UNION;
#define ABB_CH1_REG_DEBUG_ANA0_CH1_CLK_REF_SEL_START   (0)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_CLK_REF_SEL_END     (0)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_OCLK_SEL_START  (1)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_OCLK_SEL_END    (3)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_PFD_CTRL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_PFD_CTRL_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA1_UNION
 结构说明  : ch1_reg_debug_ana1 寄存器结构定义。地址偏移量:0x81，初值:0x00，宽度:8
 寄存器说明: PLL LOCK控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana1_reg;
    struct
    {
        unsigned long  reserved_0     : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_GPLL_LK_EN : 1;  /* bit[4]  : GPLL锁定检测使能
                                                         0：检测停止
                                                         1：检测开始 */
        unsigned long  CH1_WPLL_LK_EN : 1;  /* bit[5]  : WPLL锁定检测使能
                                                         0：检测停止
                                                         1：检测开始 */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA1_UNION;
#define ABB_CH1_REG_DEBUG_ANA1_CH1_GPLL_LK_EN_START  (4)
#define ABB_CH1_REG_DEBUG_ANA1_CH1_GPLL_LK_EN_END    (4)
#define ABB_CH1_REG_DEBUG_ANA1_CH1_WPLL_LK_EN_START  (5)
#define ABB_CH1_REG_DEBUG_ANA1_CH1_WPLL_LK_EN_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA2_UNION
 结构说明  : ch1_reg_debug_ana2 寄存器结构定义。地址偏移量:0x82，初值:0x80，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana2_reg;
    struct
    {
        unsigned long  CH1_PLL_CP_PD : 2;  /* bit[0-1]: PLL CP PowerDown控制，测试用
                                                        00：正常工作
                                                        01: PowerDown WPLL CP 
                                                        10: PowerDown GPLL CP 
                                                        11: PowerDown WPLL CP和GPLL CP */
        unsigned long  reserved      : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH1_CLKN_EN   : 1;  /* bit[7]  : 反相时钟开关
                                                        1: 反相时钟打开
                                                        0: 反相时钟关闭 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA2_UNION;
#define ABB_CH1_REG_DEBUG_ANA2_CH1_PLL_CP_PD_START  (0)
#define ABB_CH1_REG_DEBUG_ANA2_CH1_PLL_CP_PD_END    (1)
#define ABB_CH1_REG_DEBUG_ANA2_CH1_CLKN_EN_START    (7)
#define ABB_CH1_REG_DEBUG_ANA2_CH1_CLKN_EN_END      (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA3_UNION
 结构说明  : ch1_reg_debug_ana3 寄存器结构定义。地址偏移量:0x83，初值:0x80，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana3_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_GPLL_CP_CTRL : 4;  /* bit[4-7]: GPLL电荷泵电流控制(低有效)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA3_UNION;
#define ABB_CH1_REG_DEBUG_ANA3_CH1_GPLL_CP_CTRL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA3_CH1_GPLL_CP_CTRL_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA4_UNION
 结构说明  : ch1_reg_debug_ana4 寄存器结构定义。地址偏移量:0x84，初值:0x80，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana4_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_WPLL_CP_CTRL : 4;  /* bit[4-7]: WPLL电荷泵电流控制(低有效)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA4_UNION;
#define ABB_CH1_REG_DEBUG_ANA4_CH1_WPLL_CP_CTRL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA4_CH1_WPLL_CP_CTRL_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA5_UNION
 结构说明  : ch1_reg_debug_ana5 寄存器结构定义。地址偏移量:0x85，初值:0x00，宽度:8
 寄存器说明: 快速启动控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana5_reg;
    struct
    {
        unsigned long  reserved         : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH1_BG_FASTUP_EN : 1;  /* bit[7]  : 0 disable
                                                           1 enable */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA5_UNION;
#define ABB_CH1_REG_DEBUG_ANA5_CH1_BG_FASTUP_EN_START  (7)
#define ABB_CH1_REG_DEBUG_ANA5_CH1_BG_FASTUP_EN_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA6_UNION
 结构说明  : ch1_reg_debug_ana6 寄存器结构定义。地址偏移量:0x86，初值:0x41，宽度:8
 寄存器说明: Bandgap和TCXO控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana6_reg;
    struct
    {
        unsigned long  CH1_G_FREF_SEL : 1;  /* bit[0]  : GPLL参考频率设置
                                                         1: 19.2MHz参考时钟，工作模式
                                                         0: 26MHz参考时钟，测试模式 */
        unsigned long  reserved       : 3;  /* bit[1-3]: Reserved */
        unsigned long  CH1_TCXO_DRV   : 2;  /* bit[4-5]: TCXO BUFFER电流设置
                                                         00: 1x
                                                         01: 2x
                                                         10: 3x
                                                         11: 4x */
        unsigned long  CH1_CLKIN_PD   : 1;  /* bit[6]  : TEST CLK INPUT下电控制
                                                         0: 开启
                                                         1: 关闭 */
        unsigned long  CH1_HOLD_BG    : 1;  /* bit[7]  : Sleep模式时是否保持Bandgap工作的控制信号，它与refgen模块产生的PD_BG信号共同控制Bandgap的状态
                                                         0: Bandgap状态受PD_BG信号控制，当进入Sleep模式时，Bandgap被关闭；否则Bandgap工作
                                                         1: Bandgap始终工作 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA6_UNION;
#define ABB_CH1_REG_DEBUG_ANA6_CH1_G_FREF_SEL_START  (0)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_G_FREF_SEL_END    (0)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_TCXO_DRV_START    (4)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_TCXO_DRV_END      (5)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_CLKIN_PD_START    (6)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_CLKIN_PD_END      (6)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_HOLD_BG_START     (7)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_HOLD_BG_END       (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA7_UNION
 结构说明  : ch1_reg_debug_ana7 寄存器结构定义。地址偏移量:0x87，初值:0x00，宽度:8
 寄存器说明: 电流控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana7_reg;
    struct
    {
        unsigned long  CH1_DRVBUF_CT : 3;  /* bit[0-2]: L/W/G 共用ADC 差分Buffer电流调节控制
                                                        000: 1.0x（默认）
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH1_IREF_CTRL : 3;  /* bit[3-5]: 基带参考电流控制
                                                        000：5u
                                                        001：2u
                                                        010：3u
                                                        011：4u
                                                        100：6u
                                                        101：7u
                                                        110：8u
                                                        111：9u */
        unsigned long  reserved      : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA7_UNION;
#define ABB_CH1_REG_DEBUG_ANA7_CH1_DRVBUF_CT_START  (0)
#define ABB_CH1_REG_DEBUG_ANA7_CH1_DRVBUF_CT_END    (2)
#define ABB_CH1_REG_DEBUG_ANA7_CH1_IREF_CTRL_START  (3)
#define ABB_CH1_REG_DEBUG_ANA7_CH1_IREF_CTRL_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA8_UNION
 结构说明  : ch1_reg_debug_ana8 寄存器结构定义。地址偏移量:0x88，初值:0x00，宽度:8
 寄存器说明: 电流控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana8_reg;
    struct
    {
        unsigned long  CH1_TX_CURRENT : 4;  /* bit[0-3]: 基带TX通道LPF电路电流控制
                                                         0000：1.0x
                                                         0001：0.9x
                                                         0010：0.8x
                                                         0011：0.7x
                                                         0100：2.0x
                                                         0101：1.8x
                                                         0110：1.6x
                                                         0111：1.4x
                                                         1xxx：Reserved */
        unsigned long  CH1_QU_MODE    : 1;  /* bit[4]  : 量化器模式选择 */
        unsigned long  reserved       : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA8_UNION;
#define ABB_CH1_REG_DEBUG_ANA8_CH1_TX_CURRENT_START  (0)
#define ABB_CH1_REG_DEBUG_ANA8_CH1_TX_CURRENT_END    (3)
#define ABB_CH1_REG_DEBUG_ANA8_CH1_QU_MODE_START     (4)
#define ABB_CH1_REG_DEBUG_ANA8_CH1_QU_MODE_END       (4)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA9_UNION
 结构说明  : ch1_reg_debug_ana9 寄存器结构定义。地址偏移量:0x89，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana9_reg;
    struct
    {
        unsigned long  CH1_DAC_DUM_B0   : 1;  /* bit[0]  : RX方向sub_DAC Dummy单元控制，低一位
                                                           0：开启
                                                           1：关闭 */
        unsigned long  CH1_L_PUP_MODE   : 1;  /* bit[1]  : LTE ADC模块启动模式选择
                                                           0：自动模式
                                                           1：配置寄存器模式 */
        unsigned long  CH1_IB_SEL       : 1;  /* bit[2]  : 积分器和量化器的电流是否可调
                                                           0：不可调
                                                           1：可调 */
        unsigned long  CH1_L_DEM_PD     : 1;  /* bit[3]  : LTE ADC DEM功能关闭信号
                                                           0：DEM使能
                                                           1：DEM不使能 */
        unsigned long  CH1_L_TUNING_SEL : 1;  /* bit[4]  : LTE ADC模块Tuning码的选择
                                                           0：选择Tuning模块的输出作为LTE ADC的Tuning码
                                                           1：选择寄存器的输出作为LTE ADC的Tuning码 */
        unsigned long  CH1_RX_IBCT_DAC  : 3;  /* bit[5-7]: RX方向sub_DAC电流控制
                                                           000: 1.0x
                                                           001: 0.2x
                                                           010: 0.6x
                                                           011: 0.3x
                                                           100: 0.4x
                                                           101: 0.8x
                                                           110: 1.4x
                                                           111: 1.6x */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA9_UNION;
#define ABB_CH1_REG_DEBUG_ANA9_CH1_DAC_DUM_B0_START    (0)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_DAC_DUM_B0_END      (0)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_PUP_MODE_START    (1)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_PUP_MODE_END      (1)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_IB_SEL_START        (2)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_IB_SEL_END          (2)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_DEM_PD_START      (3)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_DEM_PD_END        (3)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_TUNING_SEL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_TUNING_SEL_END    (4)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_RX_IBCT_DAC_START   (5)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_RX_IBCT_DAC_END     (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA10_UNION
 结构说明  : ch1_reg_debug_ana10 寄存器结构定义。地址偏移量:0x8A，初值:0x00，宽度:8
 寄存器说明: ADC复位控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana10_reg;
    struct
    {
        unsigned long  CH1_DAC_DUM_B2B1 : 2;  /* bit[0-1]: RX方向sub_DAC Dummy单元控制，高两位
                                                           0：开启
                                                           1：关闭 */
        unsigned long  CH1_L_PUP_CTRL0  : 1;  /* bit[2]  : LTE ADC中第一级积分器电容复位控制
                                                           0：不复位
                                                           1：复位 */
        unsigned long  CH1_L_PUP_CTRL1  : 1;  /* bit[3]  : LTE ADC中第二级积分器电容复位控制
                                                           0：不复位
                                                           1：复位 */
        unsigned long  CH1_L_PUP_CTRL2  : 1;  /* bit[4]  : LTE ADC中第三级积分器电容复位控制
                                                           0: 不复位
                                                           1：复位 */
        unsigned long  CH1_L_PUP_CTRL3  : 1;  /* bit[5]  : LTE ADC中CKGEN模块Powerup控制
                                                           0：Powerdown
                                                           1：Powerup */
        unsigned long  CH1_L_PUP_CTRL4  : 1;  /* bit[6]  : LTE ADC中OP模块Powerup控制
                                                           0：Powerdown
                                                           1：Powerup */
        unsigned long  CH1_L_PUP_CTRL5  : 1;  /* bit[7]  : LTE ADC中DAC模块Powerup控制
                                                           0：Powerdown
                                                           1：Powerup */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA10_UNION;
#define ABB_CH1_REG_DEBUG_ANA10_CH1_DAC_DUM_B2B1_START  (0)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_DAC_DUM_B2B1_END    (1)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL0_START   (2)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL0_END     (2)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL1_START   (3)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL1_END     (3)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL2_START   (4)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL2_END     (4)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL3_START   (5)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL3_END     (5)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL4_START   (6)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL4_END     (6)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL5_START   (7)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL5_END     (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA14_UNION
 结构说明  : ch1_reg_debug_ana14 寄存器结构定义。地址偏移量:0x8E，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana14_reg;
    struct
    {
        unsigned long  CH1_L_OL_CT   : 3;  /* bit[0-2]: LTE Overload模块配置
                                                        00：16个连续最大码或者最小码
                                                        01：8个连续最大码或者最小码
                                                        10：4个连续最大码或者最小码
                                                        11：关闭Overload检测 */
        unsigned long  CH1_L_ADC_ICT : 3;  /* bit[3-5]: LTE ADC 电流偏置调节
                                                        000: 1.0x
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH1_L_CK_CT   : 2;  /* bit[6-7]: LTE SYNC时序控制
                                                        00：No delay
                                                        01：250ps delay
                                                        10：500ps delay
                                                        11：1000ps delay */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA14_UNION;
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_OL_CT_START    (0)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_OL_CT_END      (2)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_ADC_ICT_START  (3)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_ADC_ICT_END    (5)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_CK_CT_START    (6)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_CK_CT_END      (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA16_UNION
 结构说明  : ch1_reg_debug_ana16 寄存器结构定义。地址偏移量:0x90，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana16_reg;
    struct
    {
        unsigned long  CH1_IBCT_STG12 : 3;  /* bit[0-2]: RX ADC Stage 12电流控制
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH1_IBCT_STG3  : 3;  /* bit[3-5]: RX ADC Stage 3电流控制
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH1_PDM_CTRL   : 1;  /* bit[6]  : RX输出PDM编码控制
                                                         0：adder encoder
                                                         1：de-bubble encoder */
        unsigned long  CH1_G_I_CTRL   : 1;  /* bit[7]  : G模式电流控制
                                                         0：输出级运放正常
                                                         1：输出级运放增加 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA16_UNION;
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG12_START  (0)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG12_END    (2)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG3_START   (3)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG3_END     (5)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_PDM_CTRL_START    (6)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_PDM_CTRL_END      (6)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_G_I_CTRL_START    (7)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_G_I_CTRL_END      (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA17_UNION
 结构说明  : ch1_reg_debug_ana17 寄存器结构定义。地址偏移量:0x91，初值:0x00，宽度:8
 寄存器说明: PLL测试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana17_reg;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_PLL1_CLK_TEST : 2;  /* bit[4-5]: PLL时钟测试PAD信号选择
                                                            00：时钟测试PAD浮空
                                                            01：WPLL输出时钟到PAD
                                                            10：GPLL输出时钟到PAD */
        unsigned long  CH1_PLL1_ANA_TEST : 2;  /* bit[6-7]: PLL控制电压测试PAD信号选择
                                                            00：控制电压测试PAD浮空
                                                            01：WPLL输出控制电压到PAD
                                                            10：GPLL输出控制电压到PAD */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA17_UNION;
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_CLK_TEST_START  (4)
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_CLK_TEST_END    (5)
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_ANA_TEST_START  (6)
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_ANA_TEST_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA19_UNION
 结构说明  : ch1_reg_debug_ana19 寄存器结构定义。地址偏移量:0x93，初值:0x3C，宽度:8
 寄存器说明: 时钟反沿控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana19_reg;
    struct
    {
        unsigned long  CH1_CLK_PADF_SEL : 2;  /* bit[0-1]: 测试管脚输出时钟频率控制
                                                           00: 输出最高时速
                                                           01：WPLL输出半速
                                                           10：GPLL输出半速
                                                           11：WPLL和GPLL输出半速 */
        unsigned long  CH1_HK_CLK_EN    : 1;  /* bit[2]  : HKADC和Tuning模块时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  CH1_AUX_CLK_EN   : 1;  /* bit[3]  : PLL模块153.6MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  CH1_DAC_CLK_EN   : 1;  /* bit[4]  : PLL模块307.2MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  CH1_ADC_CLK_EN   : 1;  /* bit[5]  : PLL模块307.2MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA19_UNION;
#define ABB_CH1_REG_DEBUG_ANA19_CH1_CLK_PADF_SEL_START  (0)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_CLK_PADF_SEL_END    (1)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_HK_CLK_EN_START     (2)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_HK_CLK_EN_END       (2)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_AUX_CLK_EN_START    (3)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_AUX_CLK_EN_END      (3)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_DAC_CLK_EN_START    (4)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_DAC_CLK_EN_END      (4)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_ADC_CLK_EN_START    (5)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_ADC_CLK_EN_END      (5)


/*****************************************************************************
 结构名    : ABB_CH1_REG_DEBUG_ANA20_UNION
 结构说明  : ch1_reg_debug_ana20 寄存器结构定义。地址偏移量:0x94，初值:0x20，宽度:8
 寄存器说明: 模拟调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana20_reg;
    struct
    {
        unsigned long  reserved      : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_EXT_BG_EN : 1;  /* bit[4]  : 外部BandGap使能信号 */
        unsigned long  CH1_CAP_MULT  : 2;  /* bit[5-6]: 第三级积分器电容调整 */
        unsigned long  CH1_CAP_SEL   : 1;  /* bit[7]  : Tuning电路电容选择
                                                        0: 大电容
                                                        1: 小电容 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA20_UNION;
#define ABB_CH1_REG_DEBUG_ANA20_CH1_EXT_BG_EN_START  (4)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_EXT_BG_EN_END    (4)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_MULT_START   (5)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_MULT_END     (6)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_SEL_START    (7)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_SEL_END      (7)


/*****************************************************************************
 结构名    : ABB_CH1_2G_RX_DELAY_UNION
 结构说明  : ch1_2g_rx_delay 寄存器结构定义。地址偏移量:0x9C，初值:0x20，宽度:8
 寄存器说明: 2g模式RX随路时钟延迟调整。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_2g_rx_delay_reg;
    struct
    {
        unsigned long  ch1_rx_delay        : 4;  /* bit[0-3]: RX_MCLK时钟延时选择
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch1_rx_clk_inv      : 1;  /* bit[4]  : rx_clk输出反向控制：
                                                              1'b0：rx_clk bypass输出
                                                              1'b1：rx_clk反向输出 */
        unsigned long  ch1_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk输出delay bypass开关：
                                                              1'b0：rx_clk 输出delay 不bypass
                                                              1'b1：rx_clk 输出delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_2G_RX_DELAY_UNION;
#define ABB_CH1_2G_RX_DELAY_ch1_rx_delay_START         (0)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_delay_END           (3)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_inv_START       (4)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_inv_END         (4)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_delay_bp_START  (5)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_3G_RX_DELAY_UNION
 结构说明  : ch1_3g_rx_delay 寄存器结构定义。地址偏移量:0x9D，初值:0x20，宽度:8
 寄存器说明: 3g模式RX随路时钟延迟调整。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_3g_rx_delay_reg;
    struct
    {
        unsigned long  ch1_rx_delay        : 4;  /* bit[0-3]: RX_MCLK时钟延时选择
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch1_rx_clk_inv      : 1;  /* bit[4]  : rx_clk输出反向控制：
                                                              1'b0：rx_clk bypass输出
                                                              1'b1：rx_clk反向输出 */
        unsigned long  ch1_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk输出delay bypass开关：
                                                              1'b0：rx_clk 输出delay 不bypass
                                                              1'b1：rx_clk 输出delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_3G_RX_DELAY_UNION;
#define ABB_CH1_3G_RX_DELAY_ch1_rx_delay_START         (0)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_delay_END           (3)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_inv_START       (4)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_inv_END         (4)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_delay_bp_START  (5)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_4G_RX_DELAY_UNION
 结构说明  : ch1_4g_rx_delay 寄存器结构定义。地址偏移量:0x9E，初值:0x30，宽度:8
 寄存器说明: 4g模式RX随路时钟延迟调整。
*****************************************************************************/
typedef union
{
    unsigned long      ch1_4g_rx_delay_reg;
    struct
    {
        unsigned long  ch1_rx_delay        : 4;  /* bit[0-3]: RX_MCLK时钟延时选择
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch1_rx_clk_inv      : 1;  /* bit[4]  : rx_clk输出反向控制：
                                                              1'b0：rx_clk bypass输出
                                                              1'b1：rx_clk反向输出 */
        unsigned long  ch1_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk输出delay bypass开关：
                                                              1'b0：rx_clk 输出delay 不bypass
                                                              1'b1：rx_clk 输出delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_4G_RX_DELAY_UNION;
#define ABB_CH1_4G_RX_DELAY_ch1_rx_delay_START         (0)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_delay_END           (3)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_inv_START       (4)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_inv_END         (4)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_delay_bp_START  (5)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_TESTMODE_UNION
 结构说明  : ch0_testmode 寄存器结构定义。地址偏移量:0xA1，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_testmode_reg;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : 保留 */
        unsigned long  ch0_rx_chnl_sel : 2;  /* bit[1-2]: RX模拟测试模式下通道选择：
                                                          00：输出RXA I模拟调制器数据(默认)
                                                          01：输出RXA Q模拟调制器数据
                                                          10：输出RXB I模拟调制器数据
                                                          11：输出RXB Q模拟调制器数据 */
        unsigned long  ch0_test_mode   : 3;  /* bit[3-5]: bit[4:3]测试模式控制：
                                                          00：正常模式(默认)
                                                          01：数字算法逻辑环回模式
                                                          10：RX模拟测试模式(bypass RX数字滤波器)
                                                          11：数字接口环回模式
                                                          bit[5]：reserved */
        unsigned long  ch0_sw_rst      : 1;  /* bit[6]  : 配置的软复位信号：
                                                          0：软件不启动软复位(默认)
                                                          1：软件启动软复位 */
        unsigned long  reserved_1      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TESTMODE_UNION;
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_START  (1)
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_END    (2)
#define ABB_CH0_TESTMODE_ch0_test_mode_START    (3)
#define ABB_CH0_TESTMODE_ch0_test_mode_END      (5)
#define ABB_CH0_TESTMODE_ch0_sw_rst_START       (6)
#define ABB_CH0_TESTMODE_ch0_sw_rst_END         (6)


/*****************************************************************************
 结构名    : ABB_CH0_CTRL_UNION
 结构说明  : ch0_ctrl 寄存器结构定义。地址偏移量:0xA2，初值:0x00，宽度:8
 寄存器说明: 通道控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_ctrl_reg;
    struct
    {
        unsigned long  ch0_et_sel : 1;  /* bit[0]  : ET/APT通道选择：
                                                     0：选择TX通道I路做ET/APT
                                                     1：选择TX通道Q路做ET/APT */
        unsigned long  reserved   : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CTRL_UNION;
#define ABB_CH0_CTRL_ch0_et_sel_START  (0)
#define ABB_CH0_CTRL_ch0_et_sel_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_CFR_CTRL_UNION
 结构说明  : ch0_cfr_ctrl 寄存器结构定义。地址偏移量:0xA3，初值:0x44，宽度:8
 寄存器说明: CFR峰值检测窗长寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_cfr_ctrl_reg;
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
        unsigned long  reserved         : 1;  /* bit[3]  : 保留 */
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
 结构名    : ABB_CH0_LINE_CTRL_SEL_UNION
 结构说明  : ch0_line_ctrl_sel 寄存器结构定义。地址偏移量:0xA4，初值:0x00，宽度:8
 寄存器说明: 线控选择。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_line_ctrl_sel_reg;
    struct
    {
        unsigned long  ch0_line_ctrl_2g_sel  : 1;  /* bit[0]: 选择2G线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_3g_sel  : 1;  /* bit[1]: 选择3G线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_4g_sel  : 1;  /* bit[2]: 选择4G线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_apt_sel : 1;  /* bit[3]: 选择APT线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_et_sel  : 1;  /* bit[4]: 选择ET线控模式，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_tx_sel  : 1;  /* bit[5]: 选择TX_EN线控，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_rxb_sel : 1;  /* bit[6]: 选择RXB_EN线控，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_rxa_en  : 1;  /* bit[7]: 选择RXA_EN线控，0: tie to 0(默认）
                                                              1: from line control */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_CTRL_SEL_UNION;
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_2g_sel_START   (0)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_2g_sel_END     (0)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_3g_sel_START   (1)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_3g_sel_END     (1)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_4g_sel_START   (2)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_4g_sel_END     (2)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_apt_sel_START  (3)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_apt_sel_END    (3)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_et_sel_START   (4)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_et_sel_END     (4)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_tx_sel_START   (5)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_tx_sel_END     (5)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxb_sel_START  (6)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxb_sel_END    (6)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxa_en_START   (7)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxa_en_END     (7)


/*****************************************************************************
 结构名    : ABB_CH0_RX_DIG_RPT_UNION
 结构说明  : ch0_rx_dig_rpt 寄存器结构定义。地址偏移量:0xA5，初值:0x00，宽度:8
 寄存器说明: RX数字工作模式上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rx_dig_rpt_reg;
    struct
    {
        unsigned long  ch0_rx_comp_sel_rpt : 1;  /* bit[0]  : Reserved */
        unsigned long  ch0_rx_comp_fix_rpt : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                              0：系数不固定，由寄存器配置
                                                              1：系数固定 */
        unsigned long  ch0_rx_hb_bp_rpt    : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                              0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2
                                                              1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  ch0_rx_rate_rpt     : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                  2G,   3G_SC,    4G,   3G_DC,      
                                                              00： 2.167M,15.36M, 61.44M,30.72M
                                                              01： 4.33MHz,------,30.72M,------
                                                              10： ------, ------,15.36M,------
                                                              11： ------, ------, 7.68M,------ */
        unsigned long  ch0_rx_mode_dig_rpt : 3;  /* bit[5-7]: RX通道模式控制：
                                                              000：2G
                                                              001：3G_SC
                                                              010：4G
                                                              011：3G_DC
                                                              Others：reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_DIG_RPT_UNION;
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_sel_rpt_START  (0)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_sel_rpt_END    (0)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_fix_rpt_START  (1)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_fix_rpt_END    (1)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_hb_bp_rpt_START     (2)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_hb_bp_rpt_END       (2)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_rate_rpt_START      (3)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_rate_rpt_END        (4)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_mode_dig_rpt_START  (5)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_mode_dig_rpt_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_DIG_RPT_UNION
 结构说明  : ch0_tx_dig_rpt 寄存器结构定义。地址偏移量:0xA6，初值:0x02，宽度:8
 寄存器说明: TX数字工作模式上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_tx_dig_rpt_reg;
    struct
    {
        unsigned long  ch0_tx_comp_bp_tpr  : 1;  /* bit[0]  : TX通道补偿滤波器bypass控制：
                                                              0：不bypass
                                                              1：bypass */
        unsigned long  ch0_tx_hb_bp_rpt    : 1;  /* bit[1]  : TX通道半带滤波器bypass控制：
                                                              0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
                                                              1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  ch0_tx_rate_rpt     : 3;  /* bit[2-4]: TX通道CIC滤波器输出速率控制：
                                                                   2G,     3G,     4G,     
                                                                  (78M) (153.6M) (307.2M) 
                                                              0：4.33MHz,30.72MHz,61.44MHz
                                                              1：2.16MHz,15.36MHz,30.72MHz
                                                              2：-------,--------,15.36MHz
                                                              3：-------,--------, 7.68MHz
                                                              4：-------,--------, 3.84MHz
                                                              Others：Reserved */
        unsigned long  ch0_tx_mode_dig_rpt : 3;  /* bit[5-7]: TX通道模式控制：
                                                              000：2G
                                                              001：3G
                                                              010：4G &amp; ET &amp; APT
                                                              Others：reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_DIG_RPT_UNION;
#define ABB_CH0_TX_DIG_RPT_ch0_tx_comp_bp_tpr_START   (0)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_comp_bp_tpr_END     (0)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_hb_bp_rpt_START     (1)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_hb_bp_rpt_END       (1)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_rate_rpt_START      (2)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_rate_rpt_END        (4)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_mode_dig_rpt_START  (5)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_mode_dig_rpt_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_I_COEF1_UNION
 结构说明  : ch0_rxa_i_coef1 寄存器结构定义。地址偏移量:0xAB，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_i_coef1_reg;
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
 结构说明  : ch0_rxa_i_coef3 寄存器结构定义。地址偏移量:0xAD，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_i_coef3_reg;
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
 结构说明  : ch0_rxa_q_coef1 寄存器结构定义。地址偏移量:0xB0，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_q_coef1_reg;
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
 结构说明  : ch0_rxa_q_coef3 寄存器结构定义。地址偏移量:0xB2，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_q_coef3_reg;
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
 结构说明  : ch0_rxb_i_coef1 寄存器结构定义。地址偏移量:0xB5，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_i_coef1_reg;
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
 结构说明  : ch0_rxb_i_coef3 寄存器结构定义。地址偏移量:0xB7，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_i_coef3_reg;
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
 结构说明  : ch0_rxb_q_coef1 寄存器结构定义。地址偏移量:0xBA，初值:0xF4，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_q_coef1_reg;
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
 结构说明  : ch0_rxb_q_coef3 寄存器结构定义。地址偏移量:0xBC，初值:0x74，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_q_coef3_reg;
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
    unsigned long      ch0_reg_rxa_dcr_cfg_reg;
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
    unsigned long      ch0_reg_rxb_dcr_cfg_reg;
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
    unsigned long      ch0_reg_rx_dcr_ctrl_reg;
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
    unsigned long      ch0_rxa_blocking_reg;
    struct
    {
        unsigned long  ch0_rxa_blk_coeff : 5;  /* bit[0-4]: RXA天线BLOCKING上报值，系数，2的M次方 */
        unsigned long  ch0_rxa_blk_power : 3;  /* bit[5-7]: RXA天线BLOCKING上报值,能量大小N */
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
    unsigned long      ch0_rxb_blocking_reg;
    struct
    {
        unsigned long  ch0_rxb_blk_coeff : 5;  /* bit[0-4]: RXB天线BLOCKING上报值，系数，2的M次方 */
        unsigned long  ch0_rxb_blk_power : 3;  /* bit[5-7]: RXB天线BLOCKING上报值,能量大小N */
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
    unsigned long      ch0_reg_rxa_dc_i_2_reg;
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
    unsigned long      ch0_reg_rxa_dc_q_2_reg;
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
    unsigned long      ch0_reg_rxb_dc_i_2_reg;
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
    unsigned long      ch0_reg_rxb_dc_q_2_reg;
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
 结构说明  : ch0_reg_debug_dig0 寄存器结构定义。地址偏移量:0xCB，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_dig0_reg;
    struct
    {
        unsigned long  ch0_sdm_rst_ctrl : 1;  /* bit[0]  : TX通道SDM模块异常时复位控制
                                                           0：只复位SDM模块
                                                           1：复位整个TX通道 */
        unsigned long  ch0_dem_mode     : 1;  /* bit[1]  : TX通道DEM校准工作模式
                                                           0：正常工作
                                                           1：校准态，DEM输出为dem_code_man */
        unsigned long  ch0_tx_dem_sat   : 2;  /* bit[2-3]: Reserved */
        unsigned long  ch0_dither_en    : 1;  /* bit[4]  : Reserved */
        unsigned long  reserved         : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_DIG0_UNION;
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_START  (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_END    (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_START      (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_END        (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_START    (2)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_END      (3)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_START     (4)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_END       (4)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_DIG4_UNION
 结构说明  : ch0_reg_debug_dig4 寄存器结构定义。地址偏移量:0xCF，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_dig4_reg;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: 保留 */
        unsigned long  ch0_cic4_cic6_sel : 1;  /* bit[4]  : RX通道CIC4/CIC6滤波器选择：
                                                            0: 选择CIC4滤波器
                                                            1: 选择CIC6滤波器 */
        unsigned long  ch0_sw_gate_bp    : 1;  /* bit[5]  : 切换门控使能bypass信号。1表示门控使能功能旁路。 */
        unsigned long  ch0_cic_rst_bp    : 1;  /* bit[6]  : 切换复位bypass信号。1表示切换复位功能旁路。 */
        unsigned long  ch0_div_en_bp     : 1;  /* bit[7]  : div_en控制分频器bypass信号，0：div_en控制分频器；1：div_en不控制分频器，分频器使能始终为1。. */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_DIG4_UNION;
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic4_cic6_sel_START  (4)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic4_cic6_sel_END    (4)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_sw_gate_bp_START     (5)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_sw_gate_bp_END       (5)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic_rst_bp_START     (6)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic_rst_bp_END       (6)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_div_en_bp_START      (7)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_div_en_bp_END        (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR02_UNION
 结构说明  : ch0_reg_analog_wr02 寄存器结构定义。地址偏移量:0xD0，初值:0x0F，宽度:8
 寄存器说明: Power Down控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr02_reg;
    struct
    {
        unsigned long  CH1_RXC_Q_PD   : 1;  /* bit[0]  : Reserved */
        unsigned long  CH1_RXC_I_PD   : 1;  /* bit[1]  : Reserved */
        unsigned long  CH0_PLL624_PD  : 1;  /* bit[2]  : GPLL Power Down控制
                                                         0:Power On
                                                         1:Power Down(默认) */
        unsigned long  CH0_PLL6144_PD : 1;  /* bit[3]  : WPLL Power Down控制
                                                         0:Power On(默认)
                                                         1:Power Down */
        unsigned long  reserved       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR02_UNION;
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_Q_PD_START    (0)
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_Q_PD_END      (0)
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_I_PD_START    (1)
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_I_PD_END      (1)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_START   (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_END     (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_START  (3)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_END    (3)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR03_UNION
 结构说明  : ch0_reg_analog_wr03 寄存器结构定义。地址偏移量:0xD1，初值:0x30，宽度:8
 寄存器说明: 数模接口时钟控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr03_reg;
    struct
    {
        unsigned long  reserved_0        : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH0_TX_CLKD_CTRL  : 1;  /* bit[3]  : TX 采样时钟沿选择：
                                                            0: 正沿
                                                            1: 反沿(默认) */
        unsigned long  CH0_CLK_61D44M_PD : 1;  /* bit[4]  : CLK_61D44M Power Down控制
                                                            0:Power On
                                                            1:Power Down(默认) */
        unsigned long  CH0_CLK_52M_PD    : 1;  /* bit[5]  : CLK_52M Power Down控制
                                                            0:Power On
                                                            1:Power Down(默认) */
        unsigned long  CH0_245M_EN       : 1;  /* bit[6]  : 245M输出控制：
                                                            0: 不输出
                                                            1: 输出 */
        unsigned long  reserved_1        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR03_UNION;
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_START   (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_END     (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_START  (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_END    (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_START     (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_END       (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_245M_EN_START        (6)
#define ABB_CH0_REG_ANALOG_WR03_CH0_245M_EN_END          (6)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR04_UNION
 结构说明  : ch0_reg_analog_wr04 寄存器结构定义。地址偏移量:0xD2，初值:0x0C，宽度:8
 寄存器说明: Other控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr04_reg;
    struct
    {
        unsigned long  CH0_EN_CAL       : 1;  /* bit[0]  : Calibration enable（默认为0）
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
    unsigned long      ch0_reg_analog_wr05_reg;
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
    unsigned long      ch0_reg_analog_wr06_reg;
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
    unsigned long      ch0_reg_analog_wr07_reg;
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
    unsigned long      ch0_reg_analog_wr08_reg;
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
    unsigned long      ch0_reg_analog_wr09_reg;
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
    unsigned long      ch0_reg_analog_wr10_reg;
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
 结构说明  : ch0_reg_analog_wr38 寄存器结构定义。地址偏移量:0xD9，初值:0x60，宽度:8
 寄存器说明: 共模电平控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr38_reg;
    struct
    {
        unsigned long  reserved              : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH0_OFFSET_CAL_DAC_EN : 1;  /* bit[3]  : Reserved */
        unsigned long  CH0_SARADC_REF_RANGE  : 1;  /* bit[4]  : Reserved */
        unsigned long  CH0_TX_CM_CON_MODE    : 2;  /* bit[5-6]: Reserved */
        unsigned long  CH0_RX_ADC_CM_CON_EN  : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR38_UNION;
#define ABB_CH0_REG_ANALOG_WR38_CH0_OFFSET_CAL_DAC_EN_START  (3)
#define ABB_CH0_REG_ANALOG_WR38_CH0_OFFSET_CAL_DAC_EN_END    (3)
#define ABB_CH0_REG_ANALOG_WR38_CH0_SARADC_REF_RANGE_START   (4)
#define ABB_CH0_REG_ANALOG_WR38_CH0_SARADC_REF_RANGE_END     (4)
#define ABB_CH0_REG_ANALOG_WR38_CH0_TX_CM_CON_MODE_START     (5)
#define ABB_CH0_REG_ANALOG_WR38_CH0_TX_CM_CON_MODE_END       (6)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_CM_CON_EN_START   (7)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_CM_CON_EN_END     (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_WR39_UNION
 结构说明  : ch0_reg_analog_wr39 寄存器结构定义。地址偏移量:0xDA，初值:0x03，宽度:8
 寄存器说明: DUM控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr39_reg;
    struct
    {
        unsigned long  CH0_DUM_EN_Q : 1;  /* bit[0]  : TX Q channel  dummy logic control signal
                                                       1: enable(默认)
                                                       0: disable */
        unsigned long  CH0_DUM_EN_I : 1;  /* bit[1]  : TX I channel  dummy logic control signal
                                                       1: enable(默认)
                                                       0: disable */
        unsigned long  reserved     : 3;  /* bit[2-4]: Reserved */
        unsigned long  CH0_DEM_MOD  : 3;  /* bit[5-7]: RX DEM Mode Selection,bit 2
                                                       000: DWA
                                                       001: CLA1
                                                       010: CLA2
                                                       011: CLA3
                                                       100: CLA4
                                                       101: CLA5
                                                       110: CLA6
                                                       111: CLA7 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR39_UNION;
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_START  (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_END    (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_START  (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_END    (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_START   (5)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_END     (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_ANALOG_RO0_UNION
 结构说明  : ch0_reg_analog_ro0 寄存器结构定义。地址偏移量:0xDB，初值:0x00，宽度:8
 寄存器说明: 标志位只读寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_ro0_reg;
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
    unsigned long      ch0_reg_analog_ro1_reg;
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
 结构说明  : ch0_reg_debug_ana0 寄存器结构定义。地址偏移量:0xE0，初值:0x32，宽度:8
 寄存器说明: 模拟调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana0_reg;
    struct
    {
        unsigned long  CH0_CLK_REF_SEL  : 1;  /* bit[0]  : PLL的参考时钟选择
                                                           1: CLKIN_SYSTEM作为PLL的参考时钟
                                                           0: TCXO Buffer输出作为PLL参考时钟 */
        unsigned long  CH0_PLL_OCLK_SEL : 3;  /* bit[1-3]: 工作时钟选择
                                                           001：选择来自于PLL的时钟作为工作时钟
                                                           010：选择来自于CLKIN_SYSTEM的外灌时钟作为工作时钟
                                                           100：选择来自于TCXO_IN的时钟作为工作时钟 */
        unsigned long  CH0_PLL_PFD_CTRL : 2;  /* bit[4-5]: PLL鉴频鉴相器控制
                                                           x0：鉴频鉴相器一直输出Up信号
                                                           01: 鉴频鉴相器一直输出Down信号
                                                           11：鉴频鉴相器正常工作 */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA0_UNION;
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_START   (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_END     (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_START  (1)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA1_UNION
 结构说明  : ch0_reg_debug_ana1 寄存器结构定义。地址偏移量:0xE1，初值:0x00，宽度:8
 寄存器说明: PLL LOCK控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana1_reg;
    struct
    {
        unsigned long  reserved_0     : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_GPLL_LK_EN : 1;  /* bit[4]  : GPLL锁定检测使能
                                                         0：检测停止
                                                         1：检测开始 */
        unsigned long  CH0_WPLL_LK_EN : 1;  /* bit[5]  : WPLL锁定检测使能
                                                         0：检测停止
                                                         1：检测开始 */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA1_UNION;
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_START  (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_END    (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_START  (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA2_UNION
 结构说明  : ch0_reg_debug_ana2 寄存器结构定义。地址偏移量:0xE2，初值:0x80，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana2_reg;
    struct
    {
        unsigned long  CH0_PLL_CP_PD : 2;  /* bit[0-1]: PLL CP PowerDown控制，测试用
                                                        00：正常工作
                                                        01: PowerDown WPLL CP 
                                                        10: PowerDown GPLL CP 
                                                        11: PowerDown WPLL CP和GPLL CP */
        unsigned long  reserved      : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_CLKN_EN   : 1;  /* bit[7]  : 反相时钟开关
                                                        1: 反相时钟打开
                                                        0: 反相时钟关闭 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA2_UNION;
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_START  (0)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_END    (1)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_START    (7)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_END      (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA3_UNION
 结构说明  : ch0_reg_debug_ana3 寄存器结构定义。地址偏移量:0xE3，初值:0x80，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana3_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_GPLL_CP_CTRL : 4;  /* bit[4-7]: GPLL电荷泵电流控制(低有效)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA3_UNION;
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA4_UNION
 结构说明  : ch0_reg_debug_ana4 寄存器结构定义。地址偏移量:0xE4，初值:0x80，宽度:8
 寄存器说明: PLL控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana4_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_WPLL_CP_CTRL : 4;  /* bit[4-7]: WPLL电荷泵电流控制(低有效)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
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
    unsigned long      ch0_reg_debug_ana5_reg;
    struct
    {
        unsigned long  reserved         : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH0_BG_FASTUP_EN : 1;  /* bit[7]  : 0 disable
                                                           1 enable */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA5_UNION;
#define ABB_CH0_REG_DEBUG_ANA5_CH0_BG_FASTUP_EN_START  (7)
#define ABB_CH0_REG_DEBUG_ANA5_CH0_BG_FASTUP_EN_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA6_UNION
 结构说明  : ch0_reg_debug_ana6 寄存器结构定义。地址偏移量:0xE6，初值:0x41，宽度:8
 寄存器说明: Bandgap和TCXO控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana6_reg;
    struct
    {
        unsigned long  CH0_G_FREF_SEL : 1;  /* bit[0]  : GPLL参考频率设置
                                                         1: 19.2MHz参考时钟，工作模式
                                                         0: 26MHz参考时钟，测试模式 */
        unsigned long  reserved       : 3;  /* bit[1-3]: Reserved */
        unsigned long  CH0_TCXO_DRV   : 2;  /* bit[4-5]: TCXO BUFFER电流设置
                                                         00: 1x
                                                         01: 2x
                                                         10: 3x
                                                         11: 4x */
        unsigned long  CH0_CLKIN_PD   : 1;  /* bit[6]  : TEST CLK INPUT下电控制
                                                         0: 开启
                                                         1: 关闭 */
        unsigned long  CH0_HOLD_BG    : 1;  /* bit[7]  : Sleep模式时是否保持Bandgap工作的控制信号，它与refgen模块产生的PD_BG信号共同控制Bandgap的状态
                                                         0: Bandgap状态受PD_BG信号控制，当进入Sleep模式时，Bandgap被关闭；否则Bandgap工作
                                                         1: Bandgap始终工作 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA6_UNION;
#define ABB_CH0_REG_DEBUG_ANA6_CH0_G_FREF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_G_FREF_SEL_END    (0)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_START    (4)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_END      (5)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_START    (6)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_END      (6)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_HOLD_BG_START     (7)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_HOLD_BG_END       (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA7_UNION
 结构说明  : ch0_reg_debug_ana7 寄存器结构定义。地址偏移量:0xE7，初值:0x00，宽度:8
 寄存器说明: 电流控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana7_reg;
    struct
    {
        unsigned long  CH0_DRVBUF_CT : 3;  /* bit[0-2]: L/W/G 共用ADC 差分Buffer电流调节控制
                                                        000: 1.0x（默认）
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH0_IREF_CTRL : 3;  /* bit[3-5]: 基带参考电流控制
                                                        000：5u
                                                        001：2u
                                                        010：3u
                                                        011：4u
                                                        100：6u
                                                        101：7u
                                                        110：8u
                                                        111：9u */
        unsigned long  reserved      : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA7_UNION;
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_END    (2)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_IREF_CTRL_START  (3)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_IREF_CTRL_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA8_UNION
 结构说明  : ch0_reg_debug_ana8 寄存器结构定义。地址偏移量:0xE8，初值:0x00，宽度:8
 寄存器说明: 电流控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana8_reg;
    struct
    {
        unsigned long  CH0_TX_CURRENT : 4;  /* bit[0-3]: 基带TX通道LPF电路电流控制
                                                         0000：1.0x
                                                         0001：0.9x
                                                         0010：0.8x
                                                         0011：0.7x
                                                         0100：2.0x
                                                         0101：1.8x
                                                         0110：1.6x
                                                         0111：1.4x
                                                         1xxx：Reserved */
        unsigned long  CH0_QU_MODE    : 1;  /* bit[4]  : 量化器模式选择 */
        unsigned long  reserved       : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA8_UNION;
#define ABB_CH0_REG_DEBUG_ANA8_CH0_TX_CURRENT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA8_CH0_TX_CURRENT_END    (3)
#define ABB_CH0_REG_DEBUG_ANA8_CH0_QU_MODE_START     (4)
#define ABB_CH0_REG_DEBUG_ANA8_CH0_QU_MODE_END       (4)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA9_UNION
 结构说明  : ch0_reg_debug_ana9 寄存器结构定义。地址偏移量:0xE9，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana9_reg;
    struct
    {
        unsigned long  CH0_DAC_DUM_B0   : 1;  /* bit[0]  : RX方向sub_DAC Dummy单元控制，低一位
                                                           0：开启
                                                           1：关闭 */
        unsigned long  CH0_L_PUP_MODE   : 1;  /* bit[1]  : LTE ADC模块启动模式选择
                                                           0：自动模式
                                                           1：配置寄存器模式 */
        unsigned long  CH0_IB_SEL       : 1;  /* bit[2]  : 积分器和量化器的电流是否可调
                                                           0：不可调
                                                           1：可调 */
        unsigned long  CH0_L_DEM_PD     : 1;  /* bit[3]  : LTE ADC DEM功能关闭信号
                                                           0：DEM使能
                                                           1：DEM不使能 */
        unsigned long  CH0_L_TUNING_SEL : 1;  /* bit[4]  : LTE ADC模块Tuning码的选择
                                                           0：选择Tuning模块的输出作为LTE ADC的Tuning码
                                                           1：选择寄存器的输出作为LTE ADC的Tuning码 */
        unsigned long  CH0_RX_IBCT_DAC  : 3;  /* bit[5-7]: RX方向sub_DAC电流控制
                                                           000: 1.0x
                                                           001: 0.2x
                                                           010: 0.6x
                                                           011: 0.3x
                                                           100: 0.4x
                                                           101: 0.8x
                                                           110: 1.4x
                                                           111: 1.6x */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA9_UNION;
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_START    (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_END      (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_START    (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_END      (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_IB_SEL_START        (2)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_IB_SEL_END          (2)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_START      (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_END        (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_END    (4)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_RX_IBCT_DAC_START   (5)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_RX_IBCT_DAC_END     (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA10_UNION
 结构说明  : ch0_reg_debug_ana10 寄存器结构定义。地址偏移量:0xEA，初值:0x00，宽度:8
 寄存器说明: ADC复位控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana10_reg;
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
                                                           0: 不复位
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
 结构名    : ABB_CH0_REG_DEBUG_ANA14_UNION
 结构说明  : ch0_reg_debug_ana14 寄存器结构定义。地址偏移量:0xEE，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana14_reg;
    struct
    {
        unsigned long  CH0_L_OL_CT   : 3;  /* bit[0-2]: LTE Overload模块配置
                                                        00：16个连续最大码或者最小码
                                                        01：8个连续最大码或者最小码
                                                        10：4个连续最大码或者最小码
                                                        11：关闭Overload检测 */
        unsigned long  CH0_L_ADC_ICT : 3;  /* bit[3-5]: 量化器电流偏置调节
                                                        000: 1.0x
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH0_L_CK_CT   : 2;  /* bit[6-7]: LTE SYNC时序控制
                                                        00：No delay
                                                        01：250ps delay
                                                        10：500ps delay
                                                        11：1000ps delay */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA14_UNION;
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_START    (0)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_END      (2)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_ADC_ICT_START  (3)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_ADC_ICT_END    (5)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_START    (6)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_END      (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA16_UNION
 结构说明  : ch0_reg_debug_ana16 寄存器结构定义。地址偏移量:0xF0，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana16_reg;
    struct
    {
        unsigned long  CH0_IBCT_STG12 : 3;  /* bit[0-2]: RX ADC Stage 12电流控制
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH0_IBCT_STG3  : 3;  /* bit[3-5]: RX ADC Stage 3电流控制
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH0_PDM_CTRL   : 1;  /* bit[6]  : RX输出PDM编码控制
                                                         0：adder encoder
                                                         1：de-bubble encoder */
        unsigned long  CH0_G_I_CTRL   : 1;  /* bit[7]  : G模式电流控制
                                                         0：输出级运放正常
                                                         1：输出级运放增加 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA16_UNION;
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG12_START  (0)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG12_END    (2)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG3_START   (3)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG3_END     (5)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_START    (6)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_END      (6)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_G_I_CTRL_START    (7)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_G_I_CTRL_END      (7)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA17_UNION
 结构说明  : ch0_reg_debug_ana17 寄存器结构定义。地址偏移量:0xF1，初值:0x00，宽度:8
 寄存器说明: PLL测试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana17_reg;
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
 结构说明  : ch0_reg_debug_ana19 寄存器结构定义。地址偏移量:0xF3，初值:0x3C，宽度:8
 寄存器说明: 时钟反沿控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana19_reg;
    struct
    {
        unsigned long  CH0_CLK_PADF_SEL : 2;  /* bit[0-1]: 测试管脚输出时钟频率控制
                                                           00: 输出最高时速
                                                           01：WPLL输出半速
                                                           10：GPLL输出半速
                                                           11：WPLL和GPLL输出半速 */
        unsigned long  CH0_HK_CLK_EN    : 1;  /* bit[2]  : HKADC和Tuning模块时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  CH0_AUX_CLK_EN   : 1;  /* bit[3]  : PLL模块153.6MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  CH0_DAC_CLK_EN   : 1;  /* bit[4]  : PLL模块307.2MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  CH0_ADC_CLK_EN   : 1;  /* bit[5]  : PLL模块307.2MHz时钟使能信号
                                                           0：时钟关闭
                                                           1：时钟使能 */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA19_UNION;
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_HK_CLK_EN_START     (2)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_HK_CLK_EN_END       (2)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_AUX_CLK_EN_START    (3)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_AUX_CLK_EN_END      (3)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_START    (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_END      (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_START    (5)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_END      (5)


/*****************************************************************************
 结构名    : ABB_CH0_REG_DEBUG_ANA20_UNION
 结构说明  : ch0_reg_debug_ana20 寄存器结构定义。地址偏移量:0xF4，初值:0x20，宽度:8
 寄存器说明: 模拟调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana20_reg;
    struct
    {
        unsigned long  reserved      : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_EXT_BG_EN : 1;  /* bit[4]  : 外部BandGap使能信号 */
        unsigned long  CH0_CAP_MULT  : 2;  /* bit[5-6]: 第三级积分器电容调整 */
        unsigned long  CH0_CAP_SEL   : 1;  /* bit[7]  : Tuning电路电容选择
                                                        0: 大电容
                                                        1: 小电容 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA20_UNION;
#define ABB_CH0_REG_DEBUG_ANA20_CH0_EXT_BG_EN_START  (4)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_EXT_BG_EN_END    (4)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_MULT_START   (5)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_MULT_END     (6)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_START    (7)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_END      (7)


/*****************************************************************************
 结构名    : ABB_CH0_2G_RX_DELAY_UNION
 结构说明  : ch0_2g_rx_delay 寄存器结构定义。地址偏移量:0xFC，初值:0x20，宽度:8
 寄存器说明: 2g模式RX随路时钟延迟调整。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_2g_rx_delay_reg;
    struct
    {
        unsigned long  ch0_rx_delay        : 4;  /* bit[0-3]: RX_MCLK时钟延时选择
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch0_rx_clk_inv      : 1;  /* bit[4]  : rx_clk输出反向控制：
                                                              1'b0：rx_clk bypass输出
                                                              1'b1：rx_clk反向输出 */
        unsigned long  ch0_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk输出delay bypass开关：
                                                              1'b0：rx_clk 输出delay 不bypass
                                                              1'b1：rx_clk 输出delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_2G_RX_DELAY_UNION;
#define ABB_CH0_2G_RX_DELAY_ch0_rx_delay_START         (0)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_delay_END           (3)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_inv_START       (4)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_inv_END         (4)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_delay_bp_START  (5)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_3G_RX_DELAY_UNION
 结构说明  : ch0_3g_rx_delay 寄存器结构定义。地址偏移量:0xFD，初值:0x20，宽度:8
 寄存器说明: 3g模式RX随路时钟延迟调整。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_3g_rx_delay_reg;
    struct
    {
        unsigned long  ch0_rx_delay        : 4;  /* bit[0-3]: RX_MCLK时钟延时选择
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch0_rx_clk_inv      : 1;  /* bit[4]  : rx_clk输出反向控制：
                                                              1'b0：rx_clk bypass输出
                                                              1'b1：rx_clk反向输出 */
        unsigned long  ch0_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk输出delay bypass开关：
                                                              1'b0：rx_clk 输出delay 不bypass
                                                              1'b1：rx_clk 输出delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_3G_RX_DELAY_UNION;
#define ABB_CH0_3G_RX_DELAY_ch0_rx_delay_START         (0)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_delay_END           (3)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_inv_START       (4)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_inv_END         (4)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_delay_bp_START  (5)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_4G_RX_DELAY_UNION
 结构说明  : ch0_4g_rx_delay 寄存器结构定义。地址偏移量:0xFE，初值:0x20，宽度:8
 寄存器说明: 4g模式RX随路时钟延迟调整。
*****************************************************************************/
typedef union
{
    unsigned long      ch0_4g_rx_delay_reg;
    struct
    {
        unsigned long  ch0_rx_delay        : 4;  /* bit[0-3]: RX_MCLK时钟延时选择
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch0_rx_clk_inv      : 1;  /* bit[4]  : rx_clk输出反向控制：
                                                              1'b0：rx_clk bypass输出
                                                              1'b1：rx_clk反向输出 */
        unsigned long  ch0_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk输出delay bypass开关：
                                                              1'b0：rx_clk 输出delay 不bypass
                                                              1'b1：rx_clk 输出delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_4G_RX_DELAY_UNION;
#define ABB_CH0_4G_RX_DELAY_ch0_rx_delay_START         (0)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_delay_END           (3)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_inv_START       (4)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_inv_END         (4)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_delay_bp_START  (5)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_delay_bp_END    (5)




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

