/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phy_abb_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-12-09 09:35:19
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年12月9日
    作    者   : w00181973
    修改内容   : 从《ComstarTV310(V7R22) ABB寄存器描述.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __ABB_INTERFACE_TV310_H__
#define __ABB_INTERFACE_TV310_H__

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
                     (1/4) register_define_abb_com
 ***======================================================================***/
/* 寄存器说明：测试模式寄存器。
 bit[7:6]    保留
 bit[5:4]    bit[4:3]测试模式控制：
             00：正常模式(默认)
             01：数字算法逻辑环回模式
             10：RX模拟测试模式(bypass RX数字滤波器)
             11：数字/模拟接口环回
             bit[5] reserved
 bit[3:2]    保留
 bit[1]
 bit[0]
   UNION结构:  ABB_TESTMODE_UNION */
#define ABB_TESTMODE_ADDR                             (ABB_BASE_ADDR + 0x0)

/* 寄存器说明：ATE_TEST_MODE
 bit[7:3]    保留
 bit[2:0]
   UNION结构:  ABB_ATE_TESTMODE_UNION */
#define ABB_ATE_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x1)

/* 寄存器说明：TCXO_RPT
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_TCXO_RPT_UNION */
#define ABB_TCXO_RPT_ADDR                             (ABB_BASE_ADDR + 0x2)

/* 寄存器说明：ABB数字部分复位信号
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_ABB_DIG_PWR_RST_UNION */
#define ABB_ABB_DIG_PWR_RST_ADDR                      (ABB_BASE_ADDR + 0x3)

/* 寄存器说明：数字调试寄存器。
 bit[7:2]    保留
 bit[1:0]    数字调试寄存器
             bit[0]：管脚CH0_CLK_52M输出时钟选择
             1：输出GPLL
             0：输出SCPLL0
   UNION结构:  ABB_CH0_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH0_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x4)

/* 寄存器说明：数字调试寄存器。
 bit[7:2]    保留
 bit[1:0]    数字调试寄存器
             bit[0]：管脚CH1_CLK_52M输出时钟选择
             1：输出GPLL
             0：输出SCPLL1
   UNION结构:  ABB_CH1_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH1_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x5)

/* 寄存器说明：BIST配置寄存器
 bit[7]      bist测试通道线控控制模式：
             0：通道线控bist测试时全部拉高
             1：通道线控bist测试时测试通道拉高，其他拉低。
 bit[6:5]    切换iq及通道时，有30拍随路时钟延时，在此基础上增加的延时Switch_delay的选择信号：
             00：0us；(默认)
             01：20us；
             10：50us；
             11：200us。
 bit[4:3]    延时时间2配置值,信号直流量计算后的稳定时间配置。
             00:20us（默认）
             01:50us
             10:200us
             11:500us
 bit[2:1]    延时时间1配置值,通路使能到测试开始的延时时间选择。
             00:50us（默认）
             01:100us
             10:200us
             11:500us
 bit[0]      BIST使能。
             0：不使能；
             1：使能。
   UNION结构:  ABB_BIST_CFG_1_UNION */
#define ABB_BIST_CFG_1_ADDR                           (ABB_BASE_ADDR + 0x6)

/* 寄存器说明：BIST测试模式bypass寄存器
   详      述：模式bypass信号，每种模式占一个bit
            [0]：1表示G模的BIST被bypass；0表示G模的BIST正常工作。
            [1]：1表示W的BIST被bypass；0表示WCDMA模的BIST正常工作。
            [2]：1表示TDS的BIST被bypass；0表示TDS的BIST正常工作。
            [3]：1表示LTE模的BIST被bypass；0表示LTE模的BIST正常工作。
            [4]：1表示CDMA模的BIST被bypass；0表示CDMA模的BIST正常工作。
            [5]：1表示CA模的BIST被bypass；0表示CA模的BIST正常工作。
            [6]：1表示ET0模的BIST被bypass；0表示ET模的BIST正常工作。
            [7]：1表示ET1模的BIST被bypass；0表示ET模的BIST正常工作。
   UNION结构 ：无 */
#define ABB_BIST_CFG_2_ADDR                           (ABB_BASE_ADDR + 0x7)

/* 寄存器说明：BIST测试通道bypass寄存器
   详      述：Rx的bypass信号：
            [0]：Rx_1的bypass信号，0表示需要做Rx_1的BIST；1表示不做。
            [1]：Rx_2的bypass信号，0表示需要做Rx_2的BIST；1表示不做。
            [2]：Rx_3的bypass信号，0表示需要做Rx_3的BIST；1表示不做。
            [3]：Rx_4的bypass信号，0表示需要做Rx_4的BIST；1表示不做。
            [4]：Rx_5的bypass信号，0表示需要做Rx_5的BIST；1表示不做。
            [5]：Rx_6的bypass信号，0表示需要做Rx_6的BIST；1表示不做。
            [6]：Rx_7的bypass信号，0表示需要做Rx_7的BIST；1表示不做。
            [7]：Rx_8的bypass信号，0表示需要做Rx_8的BIST；1表示不做。
   UNION结构 ：无 */
#define ABB_BIST_CFG_3_ADDR                           (ABB_BASE_ADDR + 0x8)

/* 寄存器说明：BIST测试项目bypass寄存器
 bit[7:6]    保留
 bit[5:0]    测试项bypass信号：
             [0]:1表示DC_I指标bypass；0表示不bypass；
             [1]:1表示DC_Q指标bypass；0表示不bypass；
             [2]:1表示SNDR_I指标bypass；0表示不bypass；
             [3]:1表示SNDR_Q指标bypass；0表示不bypass；
             [4]:1表示GAIN_MISMATCH指标bypass；0表示不bypass；
             [5]:1表示GAIN_ERROR指标bypass；0表示不bypass；
   UNION结构:  ABB_BIST_CFG_4_UNION */
#define ABB_BIST_CFG_4_ADDR                           (ABB_BASE_ADDR + 0x9)

/* 寄存器说明：BIST手动流程配置寄存器
 bit[7:5]    保留
 bit[4]      0：bist时钟受门控控制，bist_en拉高后bist才有时钟。（默认）
             1：bist时钟不受门控控制。
 bit[3:1]    手动测试选择输入数据通道：
             000：RXA（CH0）
             001：RXB（CH0）
             010：RXA（CH1）
             011：RXB（CH1）
             100：RXA（CH2）
             101：RXB（CH2）
             110：RXA（CH3）
             111：RXB（CH3）
 bit[0]      0：自动测试流程
             1：手动测试流程
   UNION结构:  ABB_BIST_CFG_5_UNION */
#define ABB_BIST_CFG_5_ADDR                           (ABB_BASE_ADDR + 0xA)

/* 寄存器说明：BIST完成状态寄存器
 bit[7]      BIST所有启动的测试项是否通过，即未bypass的测试是否全部通过。
             0：未通过；
             1：通过。
 bit[6:1]    保留
 bit[0]      SNDR计算完成状态。
             0：没有完成；
             1：完成。
   UNION结构:  ABB_BIST_RPT_1_UNION */
#define ABB_BIST_RPT_1_ADDR                           (ABB_BASE_ADDR + 0xB)

/* 寄存器说明：BIST结果上报寄存器
 bit[7:6]    保留
 bit[5:0]    每一次计算出的6个参数是否pass：
             [0]:1表示DC_I指标pass；0表示不pass；
             [1]:1表示DC_Q指标pass；0表示不pass；
             [2]:1表示SNDR_I指标pass；0表示不pass；
             [3]:1表示SNDR_Q指标pass；0表示不pass；
             [4]:1表示GAIN_MISMATCH指标pass；0表示不pass；
             [5]:1表示GAIN_ERROR指标pass；0表示不pass；
   UNION结构:  ABB_BIST_RPT_2_UNION */
#define ABB_BIST_RPT_2_ADDR                           (ABB_BASE_ADDR + 0xC)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_1的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_3_ADDR                           (ABB_BASE_ADDR + 0xD)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_2的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_4_ADDR                           (ABB_BASE_ADDR + 0xE)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_3的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_5_ADDR                           (ABB_BASE_ADDR + 0xF)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_4的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_6_ADDR                           (ABB_BASE_ADDR + 0x10)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_5的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_7_ADDR                           (ABB_BASE_ADDR + 0x11)

/* 寄存器说明：BIST结果上报寄存器
 bit[7:3]    保留
 bit[2:0]    I路dc上报值高位。
   UNION结构:  ABB_BIST_RPT_8_UNION */
#define ABB_BIST_RPT_8_ADDR                           (ABB_BASE_ADDR + 0x12)

/* 寄存器说明：BIST结果上报寄存器
   详      述：I路dc上报值低位。
   UNION结构 ：无 */
#define ABB_BIST_RPT_9_ADDR                           (ABB_BASE_ADDR + 0x13)

/* 寄存器说明：BIST结果上报寄存器
 bit[7:3]    保留
 bit[2:0]    Q路dc上报值高位。
   UNION结构:  ABB_BIST_RPT_10_UNION */
#define ABB_BIST_RPT_10_ADDR                          (ABB_BASE_ADDR + 0x14)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Q路dc上报值低位。
   UNION结构 ：无 */
#define ABB_BIST_RPT_11_ADDR                          (ABB_BASE_ADDR + 0x15)

/* 寄存器说明：BIST结果上报寄存器
   详      述：I路信噪比上报高8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_12_ADDR                          (ABB_BASE_ADDR + 0x16)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Q路信噪比上报高8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_13_ADDR                          (ABB_BASE_ADDR + 0x17)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Gain_mismatch上报，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_14_ADDR                          (ABB_BASE_ADDR + 0x18)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Gain_error上报，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_15_ADDR                          (ABB_BASE_ADDR + 0x19)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_6的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_16_ADDR                          (ABB_BASE_ADDR + 0x1A)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_7的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_17_ADDR                          (ABB_BASE_ADDR + 0x1B)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Rx_8的Bist结算结果，每种模式1bit：
            [0]：1表示G模的BIST pass；0表示G模的BIST fail。
            [1]：1表示WCDMA模的BIST pass；0表示WCDMA模SC的BIST fail。
            [2]：1表示TDS的BIST pass；0表示TDS模DC的BIST fail。
            [3]：1表示LTE模的BIST pass；0表示LTE模的BIST fail。
            [4]：1表示CDMA模的BIST pass；0表示CDMA模的BIST fail。
            [5]：1表示CA模的BIST pass；0表示CA模的BIST fail。
            [6]：1表示ET0模的BIST pass；0表示ET模的BIST fail。
            [7]：1表示ET1模的BIST pass；0表示ET模的BIST fail。
   UNION结构 ：无 */
#define ABB_BIST_RPT_18_ADDR                          (ABB_BASE_ADDR + 0x1C)

/* 寄存器说明：BIST结果上报寄存器
   详      述：I路信噪比上报低8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_19_ADDR                          (ABB_BASE_ADDR + 0x1D)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Q路信噪比上报低8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_20_ADDR                          (ABB_BASE_ADDR + 0x1E)

/* 寄存器说明：BIST结果标准寄存器
 bit[7:6]    保留
 bit[5:0]    BIST DC达标下限高6bit，有符号数。
   UNION结构:  ABB_BIST_CFG_6_UNION */
#define ABB_BIST_CFG_6_ADDR                           (ABB_BASE_ADDR + 0x1F)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST DC达标下限低8bit，有符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_7_ADDR                           (ABB_BASE_ADDR + 0x20)

/* 寄存器说明：BIST结果标准寄存器
 bit[7:6]    保留
 bit[5:0]    BIST DC达标上限高6bit，有符号数。
   UNION结构:  ABB_BIST_CFG_8_UNION */
#define ABB_BIST_CFG_8_ADDR                           (ABB_BASE_ADDR + 0x21)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST DC达标上限低8bit，有符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_9_ADDR                           (ABB_BASE_ADDR + 0x22)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain mismatch达标下限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_10_ADDR                          (ABB_BASE_ADDR + 0x23)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain mismatch达标上限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_11_ADDR                          (ABB_BASE_ADDR + 0x24)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain error达标下限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_12_ADDR                          (ABB_BASE_ADDR + 0x25)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain error达标上限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_13_ADDR                          (ABB_BASE_ADDR + 0x26)

/* 寄存器说明：BIST SNDR 2G模式达标值
   详      述：BIST 2G模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_2G_0_ADDR                       (ABB_BASE_ADDR + 0x27)

/* 寄存器说明：BIST SNDR 2G模式达标值
   详      述：BIST 2G模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_2G_1_ADDR                       (ABB_BASE_ADDR + 0x28)

/* 寄存器说明：BIST SNDR 2G模式达标值
   详      述：BIST 2G模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_2G_2_ADDR                       (ABB_BASE_ADDR + 0x29)

/* 寄存器说明：BIST SNDR 3G模式达标值
   详      述：BIST 3G模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_3G_0_ADDR                       (ABB_BASE_ADDR + 0x2A)

/* 寄存器说明：BIST SNDR 3G模式达标值
   详      述：BIST 3G模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_3G_1_ADDR                       (ABB_BASE_ADDR + 0x2B)

/* 寄存器说明：BIST SNDR 3G模式达标值
   详      述：BIST 3G模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_3G_2_ADDR                       (ABB_BASE_ADDR + 0x2C)

/* 寄存器说明：BIST SNDR TDS模式达标值
   详      述：BIST TDS模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_TDS_0_ADDR                      (ABB_BASE_ADDR + 0x2D)

/* 寄存器说明：BIST SNDR TDS模式达标值
   详      述：BIST TDS模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_TDS_1_ADDR                      (ABB_BASE_ADDR + 0x2E)

/* 寄存器说明：BIST SNDR TDS模式达标值
   详      述：BIST TDS模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_TDS_2_ADDR                      (ABB_BASE_ADDR + 0x2F)

/* 寄存器说明：BIST SNDR 4G模式达标值
   详      述：BIST 4G模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_4G_0_ADDR                       (ABB_BASE_ADDR + 0x30)

/* 寄存器说明：BIST SNDR 4G模式达标值
   详      述：BIST 4G模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_4G_1_ADDR                       (ABB_BASE_ADDR + 0x31)

/* 寄存器说明：BIST SNDR 4G模式达标值
   详      述：BIST 4G模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_4G_2_ADDR                       (ABB_BASE_ADDR + 0x32)

/* 寄存器说明：BIST SNDR CDMA模式达标值
   详      述：BIST CDMA模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CDMA_0_ADDR                     (ABB_BASE_ADDR + 0x33)

/* 寄存器说明：BIST SNDR CDMA模式达标值
   详      述：BIST CDMA模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CDMA_1_ADDR                     (ABB_BASE_ADDR + 0x34)

/* 寄存器说明：BIST SNDR CDMA模式达标值
   详      述：BIST CDMA模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CDMA_2_ADDR                     (ABB_BASE_ADDR + 0x35)

/* 寄存器说明：BIST SNDR CA模式达标值
   详      述：BIST CA模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CA_0_ADDR                       (ABB_BASE_ADDR + 0x36)

/* 寄存器说明：BIST SNDR CA模式达标值
   详      述：BIST CA模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CA_1_ADDR                       (ABB_BASE_ADDR + 0x37)

/* 寄存器说明：BIST SNDR CA模式达标值
   详      述：BIST CA模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CA_2_ADDR                       (ABB_BASE_ADDR + 0x38)

/* 寄存器说明：BIST SNDR ET0模式达标值
   详      述：BIST ET0模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET0_0_ADDR                      (ABB_BASE_ADDR + 0x39)

/* 寄存器说明：BIST SNDR ET0模式达标值
   详      述：BIST ET0模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET0_1_ADDR                      (ABB_BASE_ADDR + 0x3A)

/* 寄存器说明：BIST SNDR ET0模式达标值
   详      述：BIST ET0模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET0_2_ADDR                      (ABB_BASE_ADDR + 0x3B)

/* 寄存器说明：BIST SNDR ET1模式达标值
   详      述：BIST ET1模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET1_0_ADDR                      (ABB_BASE_ADDR + 0x3C)

/* 寄存器说明：BIST SNDR ET1模式达标值
   详      述：BIST ET1模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET1_1_ADDR                      (ABB_BASE_ADDR + 0x3D)

/* 寄存器说明：BIST SNDR ET1模式达标值
   详      述：BIST ET1模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET1_2_ADDR                      (ABB_BASE_ADDR + 0x3E)

/* 寄存器说明：BIST_TCXO_SEL
 bit[7:2]    保留
 bit[1:0]    bist_tcxo_sel:
             0:19.2M
             1:20.48M
             2:30.72M
             3:38.74M
   UNION结构:  ABB_BIST_TCXO_SEL_UNION */
#define ABB_BIST_TCXO_SEL_ADDR                        (ABB_BASE_ADDR + 0x3F)

/* 寄存器说明：ABB版本寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

/* 寄存器说明：ABB版本寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)



/***======================================================================***
                     (2/4) register_define_abb_tx
 ***======================================================================***/
/* 寄存器说明：TX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_IDLE_DIG_1_UNION */
#define ABB_TX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x200)

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
#define ABB_TX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x201)

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
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x202)

/* 寄存器说明：TX 2G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认)
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_2G_DIG_1_UNION */
#define ABB_TX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x203)

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
#define ABB_TX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x204)

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
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x205)

/* 寄存器说明：TX C模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate(默认)
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_C_DIG_1_UNION */
#define ABB_TX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x206)

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
#define ABB_TX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x207)

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
#define ABB_TX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x208)

/* 寄存器说明：TX TDS模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器的bypass信号
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_TX_TDS_DIG_1_UNION */
#define ABB_TX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x209)

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
#define ABB_TX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x20A)

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
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x20B)

/* 寄存器说明：TX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_CH0_TX_3G_DIG_1_UNION */
#define ABB_CH0_TX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x210)

/* 寄存器说明：TX 3G模式配置寄存器2，由线控决定是否起作用。
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
   UNION结构:  ABB_CH0_TX_3G_DIG_2_UNION */
#define ABB_CH0_TX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x211)

/* 寄存器说明：TX 3G模式配置寄存器3，由线控决定是否起作用。
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
   UNION结构:  ABB_CH0_TX_3G_DIG_3_UNION */
#define ABB_CH0_TX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x212)

/* 寄存器说明：TX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_CH1_TX_3G_DIG_1_UNION */
#define ABB_CH1_TX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x213)

/* 寄存器说明：TX 3G模式配置寄存器2，由线控决定是否起作用。
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
   UNION结构:  ABB_CH1_TX_3G_DIG_2_UNION */
#define ABB_CH1_TX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x214)

/* 寄存器说明：TX 3G模式配置寄存器3，由线控决定是否起作用。
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
   UNION结构:  ABB_CH1_TX_3G_DIG_3_UNION */
#define ABB_CH1_TX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x215)

/* 寄存器说明：TX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_CH0_TX_4G_DIG_1_UNION */
#define ABB_CH0_TX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x228)

/* 寄存器说明：TX 4G模式配置寄存器2，由线控决定是否起作用。
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
   UNION结构:  ABB_CH0_TX_4G_DIG_2_UNION */
#define ABB_CH0_TX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x229)

/* 寄存器说明：TX 4G模式配置寄存器3，由线控决定是否起作用。
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
   UNION结构:  ABB_CH0_TX_4G_DIG_3_UNION */
#define ABB_CH0_TX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x22A)

/* 寄存器说明：TX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    TX通道模式控制：
             000：2G(默认)
             001：3G
             010：4G
             011：TDS
             100：CDMA
             101：CA
             Others：Reserved
 bit[4:2]    TX通道CIC滤波器输入速率控制：
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
             1：2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
             1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate
 bit[0]      TX通道补偿滤波器bypass控制：
             0：不bypass(默认)
             1：bypass
   UNION结构:  ABB_CH1_TX_4G_DIG_1_UNION */
#define ABB_CH1_TX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x22B)

/* 寄存器说明：TX 4G模式配置寄存器2，由线控决定是否起作用。
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
   UNION结构:  ABB_CH1_TX_4G_DIG_2_UNION */
#define ABB_CH1_TX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x22C)

/* 寄存器说明：TX 4G模式配置寄存器3，由线控决定是否起作用。
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
   UNION结构:  ABB_CH1_TX_4G_DIG_3_UNION */
#define ABB_CH1_TX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x22D)

/* 寄存器说明：测试模式寄存器。
 bit[7:6]    保留
 bit[5:4]    TX算法环回，环回通道选择：
             0：环回CH0 RX
             1：环回CH1 RX
             2：环回CH2 RX
             default：环回CH0 RX
 bit[3:1]    保留
 bit[0]      数字部分TX通道软复位信号：
             0：不复位(默认)
             1：复位
   UNION结构:  ABB_CH0_TX_TESTMODE_UNION */
#define ABB_CH0_TX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x240)

/* 寄存器说明：SINE发送寄存器。
 bit[7:4]    正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f
 bit[3:2]    正弦波发送幅度控制
             00：满量程
             01：3/4量程
             10：1/2量程
             11：1/4量程
 bit[1]      保留
 bit[0]      ch0正弦波发送使能
             0：不发送
             1：发送
   UNION结构:  ABB_CH0_SINE_GENERATE_UNION */
#define ABB_CH0_SINE_GENERATE_ADDR                    (ABB_BASE_ADDR + 0x241)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道I路dc offset设置
   UNION结构 ：无 */
#define ABB_CH0_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x242)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道Q路dc offset设置
   UNION结构 ：无 */
#define ABB_CH0_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x243)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:6]    保留
 bit[5:0]    TX补偿滤波器系数C0,6bit有符号数
   UNION结构:  ABB_CH0_TX_COEF1_UNION */
#define ABB_CH0_TX_COEF1_ADDR                         (ABB_BASE_ADDR + 0x244)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C1,8bit有符号数
   UNION结构 ：无 */
#define ABB_CH0_TX_COEF2_ADDR                         (ABB_BASE_ADDR + 0x245)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C2低8位,10bit有符号数
   UNION结构 ：无 */
#define ABB_CH0_TX_COEF3_ADDR                         (ABB_BASE_ADDR + 0x246)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:2]    保留
 bit[1:0]    TX补偿滤波器系数C2高2位,10bit有符号数
   UNION结构:  ABB_CH0_TX_COEF4_UNION */
#define ABB_CH0_TX_COEF4_ADDR                         (ABB_BASE_ADDR + 0x247)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C3低8位,10bit无符号数
   UNION结构 ：无 */
#define ABB_CH0_TX_COEF5_ADDR                         (ABB_BASE_ADDR + 0x248)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:2]    保留
 bit[1:0]    TX补偿滤波器系数C3高2位,10bit无符号数
   UNION结构:  ABB_CH0_TX_COEF6_UNION */
#define ABB_CH0_TX_COEF6_ADDR                         (ABB_BASE_ADDR + 0x249)

/* 寄存器说明：TX数字工作模式上报寄存器。
   详      述：[7:5]：TX通道模式控制：
                    000：2G(默认)
                    001：3G
                    010：4G
                    011：TDS
                    100：CDMA
                    Others：Reserved
            [4:2]：tx rate上报
            [1]  ：tx_hb_bp上报
            [0]  ：tx_comp_hp上报
   UNION结构 ：无 */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x24A)

/* 寄存器说明：TX数字工作状态上报寄存器。
   详      述：[7:4]：保留
            [3]   ：TX通道FIFO写满
            [2]   ：TX通道FIFO读空
            [1]   ：TX通道溢出指示
            [0]   ：TX通道数据翻转指示
   UNION结构 ：无 */
#define ABB_CH0_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x24B)

/* 寄存器说明：数字调试寄存器。
 bit[7]      保留
 bit[6]      TX SD模块主调制器旁路使能：
             0：主调制器不旁路；
             1：主调制器旁路（默认）；
 bit[5]      保留
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
   UNION结构:  ABB_CH0_TX_REG_DEBUG_DIG0_UNION */
#define ABB_CH0_TX_REG_DEBUG_DIG0_ADDR                (ABB_BASE_ADDR + 0x24C)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,高位
   UNION结构 ：无 */
#define ABB_CH0_TX_REG_DEBUG_DIG1_ADDR                (ABB_BASE_ADDR + 0x24D)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,低位
   UNION结构 ：无 */
#define ABB_CH0_TX_REG_DEBUG_DIG2_ADDR                (ABB_BASE_ADDR + 0x24E)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道SDM模块异常复位计数
   UNION结构 ：无 */
#define ABB_CH0_TX_REG_DEBUG_DIG3_ADDR                (ABB_BASE_ADDR + 0x24F)

/* 寄存器说明：数字调试寄存器。
 bit[7]      bit[7]：模式切换复位长度配置使能
             0：不使能
             1：使能
 bit[6:4]    模式切换复位长度配置值，单位为8 cycles
 bit[3:1]    保留
 bit[0]      TX分频器使能bypass控制
             0：不bypass
             1：bypass
   UNION结构:  ABB_CH0_TX_REG_DEBUG_DIG4_UNION */
#define ABB_CH0_TX_REG_DEBUG_DIG4_ADDR                (ABB_BASE_ADDR + 0x250)

/* 寄存器说明：线控强制配置使能。
 bit[7:5]    保留
 bit[4]      TX通道强配线控
 bit[3:1]    保留
 bit[0]      TX通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
   UNION结构:  ABB_CH0_TX_LINE_SEL_UNION */
#define ABB_CH0_TX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x251)

/* 寄存器说明：模式线控强制配置。
 bit[7:4]    保留
 bit[3]      线控信号CH0_TX_LINE_CTRL_MODE强制配置使能
 bit[2:0]    线控信号CH0_TX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模式
   UNION结构:  ABB_CH0_TX_LINE_CFG_UNION */
#define ABB_CH0_TX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x252)

/* 寄存器说明：线控状态上报寄存器。
 bit[7:3]    保留
 bit[2]      CH0_TX_EN线控状态上报
 bit[1:0]    保留
   UNION结构:  ABB_CH0_TX_LINE_RPT0_UNION */
#define ABB_CH0_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x253)

/* 寄存器说明：线控状态上报寄存器。
 bit[7:3]    保留
 bit[2:0]    CH0 TX_LINE_CTRL_MODE状态上报
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模
             others：IDLE
   UNION结构:  ABB_CH0_TX_LINE_RPT1_UNION */
#define ABB_CH0_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x254)

/* 寄存器说明：测试模式寄存器。
 bit[7:6]    保留
 bit[5:4]    TX算法环回，环回通道选择：
             0：环回CH0 RX
             1：环回CH1 RX
             2：环回CH2 RX
             default：环回CH0 RX
 bit[3:1]    保留
 bit[0]      数字部分TX通道软复位信号：
             0：不复位(默认)
             1：复位
   UNION结构:  ABB_CH1_TX_TESTMODE_UNION */
#define ABB_CH1_TX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x260)

/* 寄存器说明：SINE发送寄存器。
 bit[7:4]    正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f
 bit[3:2]    正弦波发送幅度控制
             00：满量程
             01：3/4量程
             10：1/2量程
             11：1/4量程
 bit[1]      保留
 bit[0]      ch0正弦波发送使能
             0：不发送
             1：发送
   UNION结构:  ABB_CH1_SINE_GENERATE_UNION */
#define ABB_CH1_SINE_GENERATE_ADDR                    (ABB_BASE_ADDR + 0x261)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道I路dc offset设置
   UNION结构 ：无 */
#define ABB_CH1_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x262)

/* 寄存器说明：TX通道offset寄存器。
   详      述：TX通道Q路dc offset设置
   UNION结构 ：无 */
#define ABB_CH1_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x263)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:6]    保留
 bit[5:0]    TX补偿滤波器系数C0,6bit有符号数
   UNION结构:  ABB_CH1_TX_COEF1_UNION */
#define ABB_CH1_TX_COEF1_ADDR                         (ABB_BASE_ADDR + 0x264)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C1,8bit有符号数
   UNION结构 ：无 */
#define ABB_CH1_TX_COEF2_ADDR                         (ABB_BASE_ADDR + 0x265)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C2低8位,10bit有符号数
   UNION结构 ：无 */
#define ABB_CH1_TX_COEF3_ADDR                         (ABB_BASE_ADDR + 0x266)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:2]    保留
 bit[1:0]    TX补偿滤波器系数C2高2位,10bit有符号数
   UNION结构:  ABB_CH1_TX_COEF4_UNION */
#define ABB_CH1_TX_COEF4_ADDR                         (ABB_BASE_ADDR + 0x267)

/* 寄存器说明：TX通道补偿系数寄存器。
   详      述：TX补偿滤波器系数C3低8位,10bit无符号数
   UNION结构 ：无 */
#define ABB_CH1_TX_COEF5_ADDR                         (ABB_BASE_ADDR + 0x268)

/* 寄存器说明：TX通道补偿系数寄存器。
 bit[7:2]    保留
 bit[1:0]    TX补偿滤波器系数C3高2位,10bit无符号数
   UNION结构:  ABB_CH1_TX_COEF6_UNION */
#define ABB_CH1_TX_COEF6_ADDR                         (ABB_BASE_ADDR + 0x269)

/* 寄存器说明：TX数字工作模式上报寄存器。
   详      述：[7:5]：TX通道模式控制：
                    000：2G(默认)
                    001：3G
                    010：4G
                    011：TDS
                    100：CDMA
                    Others：Reserved
            [4:2]：tx rate上报
            [1]  ：tx_hb_bp上报
            [0]  ：tx_comp_hp上报
   UNION结构 ：无 */
#define ABB_CH1_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x26A)

/* 寄存器说明：TX数字工作状态上报寄存器。
   详      述：[7:4]：保留
            [3]   ：TX通道FIFO写满
            [2]   ：TX通道FIFO读空
            [1]   ：TX通道溢出指示
            [0]   ：TX通道数据翻转指示
   UNION结构 ：无 */
#define ABB_CH1_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x26B)

/* 寄存器说明：数字调试寄存器。
 bit[7]      保留
 bit[6]      TX SD模块主调制器旁路使能：
             0：主调制器不旁路；
             1：主调制器旁路（默认）；
 bit[5]      保留
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
   UNION结构:  ABB_CH1_TX_REG_DEBUG_DIG0_UNION */
#define ABB_CH1_TX_REG_DEBUG_DIG0_ADDR                (ABB_BASE_ADDR + 0x26C)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,高位
   UNION结构 ：无 */
#define ABB_CH1_TX_REG_DEBUG_DIG1_ADDR                (ABB_BASE_ADDR + 0x26D)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道DEM输出手工配置，只在DEM校准态下起作用,低位
   UNION结构 ：无 */
#define ABB_CH1_TX_REG_DEBUG_DIG2_ADDR                (ABB_BASE_ADDR + 0x26E)

/* 寄存器说明：数字调试寄存器。
   详      述：TX通道SDM模块异常复位计数
   UNION结构 ：无 */
#define ABB_CH1_TX_REG_DEBUG_DIG3_ADDR                (ABB_BASE_ADDR + 0x26F)

/* 寄存器说明：数字调试寄存器。
 bit[7]      bit[7]：模式切换复位长度配置使能
             0：不使能
             1：使能
 bit[6:4]    模式切换复位长度配置值，单位为8 cycles
 bit[3:1]    保留
 bit[0]      TX分频器使能bypass控制
             0：不bypass
             1：bypass
   UNION结构:  ABB_CH1_TX_REG_DEBUG_DIG4_UNION */
#define ABB_CH1_TX_REG_DEBUG_DIG4_ADDR                (ABB_BASE_ADDR + 0x270)

/* 寄存器说明：线控强制配置使能。
 bit[7:5]    保留
 bit[4]      TX通道强配线控
 bit[3:1]    保留
 bit[0]      TX通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
   UNION结构:  ABB_CH1_TX_LINE_SEL_UNION */
#define ABB_CH1_TX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x271)

/* 寄存器说明：模式线控强制配置。
 bit[7:4]    保留
 bit[3]      线控信号CH1_LINE_CTRL_MODE强制配置使能
 bit[2:0]    线控信号CH1_TX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模式
   UNION结构:  ABB_CH1_TX_LINE_CFG_UNION */
#define ABB_CH1_TX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x272)

/* 寄存器说明：线控状态上报寄存器。
 bit[7:3]    保留
 bit[2]      CH1_TX_EN线控状态上报
 bit[1:0]    保留
   UNION结构:  ABB_CH1_TX_LINE_RPT0_UNION */
#define ABB_CH1_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x273)

/* 寄存器说明：线控状态上报寄存器。
 bit[7:3]    保留
 bit[2:0]    CH1 TX_LINE_CTRL_MODE状态上报
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模
             others：IDLE
   UNION结构:  ABB_CH1_TX_LINE_RPT1_UNION */
#define ABB_CH1_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x274)



/***======================================================================***
                     (3/4) register_define_abb_rx
 ***======================================================================***/
/* 寄存器说明：RX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B(默认)
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x400)

/* 寄存器说明：RX IDLE模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
#define ABB_RX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x401)

/* 寄存器说明：RX IDLE模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；

 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_RX_IDLE_DIG_3_UNION */
#define ABB_RX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x402)

/* 寄存器说明：RX 2G模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B(默认)
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x403)

/* 寄存器说明：RX 2G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
#define ABB_RX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x404)

/* 寄存器说明：RX 2G模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；
             101：固定系数5；
             110：固定系数6；
             111：固定系数7。
 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_RX_2G_DIG_3_UNION */
#define ABB_RX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x405)

/* 寄存器说明：RX C模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_RX_C_DIG_1_UNION */
#define ABB_RX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x406)

/* 寄存器说明：RX C模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
#define ABB_RX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x407)

/* 寄存器说明：RX C模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；
             101：固定系数5；
             110：固定系数6；
             111：固定系数7。
 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_RX_C_DIG_3_UNION */
#define ABB_RX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x408)

/* 寄存器说明：RX TDS模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x409)

/* 寄存器说明：RX TDS模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
#define ABB_RX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x40A)

/* 寄存器说明：RX TDS模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；
             101：固定系数5；
             110：固定系数6；
             111：固定系数7。
 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_RX_TDS_DIG_3_UNION */
#define ABB_RX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x40B)

/* 寄存器说明：RX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_CH0_RX_3G_DIG_1_UNION */
#define ABB_CH0_RX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x410)

/* 寄存器说明：RX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
   UNION结构:  ABB_CH0_RX_3G_DIG_2_UNION */
#define ABB_CH0_RX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x411)

/* 寄存器说明：RX 3G模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；
             101：固定系数5；
             110：固定系数6；
             111：固定系数7。
 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_CH0_RX_3G_DIG_3_UNION */
#define ABB_CH0_RX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x412)

/* 寄存器说明：RX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_CH1_RX_3G_DIG_1_UNION */
#define ABB_CH1_RX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x413)

/* 寄存器说明：RX 3G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
   UNION结构:  ABB_CH1_RX_3G_DIG_2_UNION */
#define ABB_CH1_RX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x414)

/* 寄存器说明：RX 3G模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；
             101：固定系数5；
             110：固定系数6；
             111：固定系数7。
 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_CH1_RX_3G_DIG_3_UNION */
#define ABB_CH1_RX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x415)

/* 寄存器说明：RX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_CH0_RX_4G_DIG_1_UNION */
#define ABB_CH0_RX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x440)

/* 寄存器说明：RX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
   UNION结构:  ABB_CH0_RX_4G_DIG_2_UNION */
#define ABB_CH0_RX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x441)

/* 寄存器说明：RX 4G模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；
             101：固定系数5；
             110：固定系数6；
             111：固定系数7。
 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_CH0_RX_4G_DIG_3_UNION */
#define ABB_CH0_RX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x442)

/* 寄存器说明：RX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[3:1]    保留
 bit[0]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
   UNION结构:  ABB_CH1_RX_4G_DIG_1_UNION */
#define ABB_CH1_RX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x443)

/* 寄存器说明：RX 4G模式配置寄存器2，由线控决定是否起作用。
 bit[7]      保留
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
   UNION结构:  ABB_CH1_RX_4G_DIG_2_UNION */
#define ABB_CH1_RX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x444)

/* 寄存器说明：RX 4G模式配置寄存器3，由线控决定是否起作用。
 bit[7]      保留
 bit[6:4]    RX通道补偿滤波器补偿系数固定控制：
             000：系数不固定，由寄存器配置；
             001：固定系数1；
             010：固定系数2；
             011：固定系数3；
             100：固定系数4；
             101：固定系数5；
             110：固定系数6；
             111：固定系数7。
 bit[3:2]    保留
 bit[1:0]    W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
             2'b00：2560chip。(W模默认)
             2'b01：512chip。
             2'b10：1024chip。(X模默认)
             2'b11：2048chip。
   UNION结构:  ABB_CH1_RX_4G_DIG_3_UNION */
#define ABB_CH1_RX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x445)

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
#define ABB_RX_EN_DELAY_ADDR                          (ABB_BASE_ADDR + 0x470)

/* 寄存器说明：模式寄存器
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_COMB_MODE_UNION */
#define ABB_COMB_MODE_ADDR                            (ABB_BASE_ADDR + 0x471)

/* 寄存器说明：测试模式寄存器。
 bit[7:6]    保留
 bit[5:4]
 bit[3:2]
 bit[1]
 bit[0]      数字部分RX通道软复位信号：
             0：不复位(默认)
             1：复位
   UNION结构:  ABB_CH0_RX_TESTMODE_UNION */
#define ABB_CH0_RX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x480)

/* 寄存器说明：PLL选择寄存器
 bit[7:4]    保留
 bit[3]      C1模PLL选择
             0：选择SCPLL1
             1：选择SCPLL0
 bit[2]      WTL模PLL选择
             0：选择SCPLL0
             1：选择SCPLL1
 bit[1:0]    G模PLL选择：
             0：选择GPLL
             1：选择SCPLL0
             2：选择SCPLL1
   UNION结构:  ABB_CH0_PLL_SEL_UNION */
#define ABB_CH0_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x481)

/* 寄存器说明：RX数字工作模式上报寄存器。
   详      述：[8:6]：RX通道模式控制上报：
                    000：2G(默认)
                    001：3G_SC
                    010：4G &amp; ET &amp; APT
                    011：3G_DC
                    100：TDS
                    Others：CA
            [5:3]：rx_comp_sel
            [2]  ：rx_hb_bp
            [1:0]：保留
   UNION结构 ：无 */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x482)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：[7:4]：保留
            [3]  ：b通道 溢出指示
            [2]  ：b通道 数据翻转指示 1表示翻转 0表示不翻转
            [1]  ：a通道 溢出指示
            [0]  ：a通道 数据翻转指示 1表示翻转 0表示不翻转
   UNION结构 ：无 */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x483)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x484)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x485)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH0_RXA_I_COEF2_UNION */
#define ABB_CH0_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x486)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x487)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x488)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x489)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x48A)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x48B)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH0_RXA_Q_COEF2_UNION */
#define ABB_CH0_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x48C)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x48D)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x48E)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x48F)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x490)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x491)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH0_RXB_I_COEF2_UNION */
#define ABB_CH0_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x492)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x493)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x494)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x495)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x496)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x497)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH0_RXB_Q_COEF2_UNION */
#define ABB_CH0_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x498)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x499)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x49A)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x49B)

/* 寄存器说明：RXA通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH0_REG_RXA_DCR_CFG_UNION */
#define ABB_CH0_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x49C)

/* 寄存器说明：RXB通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH0_REG_RXB_DCR_CFG_UNION */
#define ABB_CH0_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x49D)

/* 寄存器说明：BLOCKING DCR功能控制寄存器。
 bit[7:2]    保留
 bit[1]      RXB天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
 bit[0]      RXA天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
   UNION结构:  ABB_CH0_REG_RX_DCR_CTRL_UNION */
#define ABB_CH0_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x49E)

/* 寄存器说明：RXA通道BLOCKING上报寄存器。
 bit[7:5]    RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXA天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x49F)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXB天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH0_RXB_BLOCKING_UNION */
#define ABB_CH0_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4A0)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器1。
   详      述：RXA天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4A1)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4A2)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器1。
   详      述：RXA天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4A3)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A4)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器1。
   详      述：RXB天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4A5)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4A6)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器1。
   详      述：RXB天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4A7)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A8)

/* 寄存器说明：通道0配置寄存器。
   详      述：通道0 flush宽度[7:0]，单位为19.2M时钟周期。
   UNION结构 ：无 */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4A9)

/* 寄存器说明：通道0配置寄存器。
 bit[7:3]    通道0 FLUSH值，默认为8。
 bit[2:0]    通道0 flush宽度[10:8]，单位为19.2M时钟周期。
   UNION结构:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4AA)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
   详      述：CH0通道RXA I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AB)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXAI_HB_GAIN_2_UNION */
#define ABB_CH0_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AC)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
   详      述：CH0通道RXA Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AD)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AE)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
   详      述：CH0通道RXB I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AF)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXBI_HB_GAIN_2_UNION */
#define ABB_CH0_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4B0)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
   详      述：CH0通道RXB Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4B1)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4B2)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      CH0通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
 bit[0]      CH0通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4B3)

/* 寄存器说明：RX线控强制配置使能。
 bit[7]      保留
 bit[6]      保留
 bit[5]      RXB通道强配线控
 bit[4]      RXA通道强配线控
 bit[3]      保留
 bit[2]      保留
 bit[1]      RXB通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
 bit[0]      RXA通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
   UNION结构:  ABB_CH0_RX_LINE_SEL_UNION */
#define ABB_CH0_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4B4)

/* 寄存器说明：RX模式线控强制配置。
 bit[7:4]    保留
 bit[3]      线控信号CH0_RX_LINE_CTRL_MODE强制配置使能
 bit[2:0]    线控信号CH0_RX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模

   UNION结构:  ABB_CH0_RX_LINE_CFG_UNION */
#define ABB_CH0_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4B5)

/* 寄存器说明：blk控制寄存器。
 bit[7:3]    保留
 bit[2]      线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能
 bit[1]      线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值
 bit[0]      保留
   UNION结构:  ABB_CH0_BLK_CFG_UNION */
#define ABB_CH0_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4B6)

/* 寄存器说明：线控状态上报寄存器。
 bit[7:2]    保留
 bit[1]      CH0_RXB_EN线控状态上报
 bit[0]      CH0_RXA_EN线控状态上报
   UNION结构:  ABB_CH0_RX_LINE_RPT0_UNION */
#define ABB_CH0_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4B7)

/* 寄存器说明：线控状态上报寄存器。
 bit[7]      CH0_RXB_BLK_EN线控状态上报
 bit[6]      CH0_RXA_BLK_EN线控状态上报
 bit[5:3]    CH0 RX_LINE_CTRL_MODE状态上报：
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模
             others：IDLE
 bit[2:0]    保留
   UNION结构:  ABB_CH0_RX_LINE_RPT1_UNION */
#define ABB_CH0_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4B8)

/* 寄存器说明：数字调试寄存器。
 bit[7]      bit[7]：模式切换复位长度配置使能
             0：不使能
             1：使能
 bit[6:4]    模式切换复位长度配置值，单位为8 cycles
 bit[3:1]    保留
 bit[0]      RX分频器使能bypass控制
             0：不bypass
             1：bypass
   UNION结构:  ABB_CH0_RX_REG_DEBUG_DIG_UNION */
#define ABB_CH0_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4B9)

/* 寄存器说明：测试模式寄存器。
 bit[7:6]    保留
 bit[5:4]
 bit[3:2]    保留
 bit[1]
 bit[0]      数字部分RX通道软复位信号：
             0：不复位(默认)
             1：复位
   UNION结构:  ABB_CH1_RX_TESTMODE_UNION */
#define ABB_CH1_RX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x4C0)

/* 寄存器说明：PLL选择寄存器
 bit[7:4]    保留
 bit[3]      C1模PLL选择
             0：选择SCPLL1
             1：选择SCPLL0
 bit[2]      WTL模PLL选择
             0：选择SCPLL0
             1：选择SCPLL1
 bit[1:0]    G模PLL选择：
             0：选择GPLL
             1：选择SCPLL0
             2：选择SCPLL1
   UNION结构:  ABB_CH1_PLL_SEL_UNION */
#define ABB_CH1_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x4C1)

/* 寄存器说明：RX数字工作模式上报寄存器。
   详      述：[8:6]：RX通道模式控制上报：
                    000：2G(默认)
                    001：3G_SC
                    010：4G &amp; ET &amp; APT
                    011：3G_DC
                    100：TDS
                    Others：CA
            [5:3]：rx_comp_sel
            [2]  ：rx_hb_bp
            [1:0]：保留
   UNION结构 ：无 */
#define ABB_CH1_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x4C2)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：[7:4]：保留
            [3]  ：b通道 溢出指示
            [2]  ：b通道 数据翻转指示 1表示翻转 0表示不翻转
            [1]  ：a通道 溢出指示
            [0]  ：a通道 数据翻转指示 1表示翻转 0表示不翻转
   UNION结构 ：无 */
#define ABB_CH1_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x4C3)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4C4)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4C5)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH1_RXA_I_COEF2_UNION */
#define ABB_CH1_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4C6)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4C7)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4C8)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4C9)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4CA)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4CB)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH1_RXA_Q_COEF2_UNION */
#define ABB_CH1_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4CC)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4CD)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4CE)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4CF)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4D0)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4D1)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH1_RXB_I_COEF2_UNION */
#define ABB_CH1_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D2)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D3)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4D4)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4D5)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4D6)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4D7)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7:1]    保留
 bit[0]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
   UNION结构:  ABB_CH1_RXB_Q_COEF2_UNION */
#define ABB_CH1_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D8)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D9)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4DA)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4DB)

/* 寄存器说明：RXA通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH1_REG_RXA_DCR_CFG_UNION */
#define ABB_CH1_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4DC)

/* 寄存器说明：RXB通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH1_REG_RXB_DCR_CFG_UNION */
#define ABB_CH1_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4DD)

/* 寄存器说明：BLOCKING DCR功能控制寄存器。
 bit[7:2]    保留
 bit[1]      RXB天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
 bit[0]      RXA天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
   UNION结构:  ABB_CH1_REG_RX_DCR_CTRL_UNION */
#define ABB_CH1_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x4DE)

/* 寄存器说明：RXA通道BLOCKING上报寄存器。
 bit[7:5]    RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXA天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4DF)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXB天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH1_RXB_BLOCKING_UNION */
#define ABB_CH1_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4E0)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器1。
   详      述：RXA天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4E1)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXA_DC_I_2_UNION */
#define ABB_CH1_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4E2)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器1。
   详      述：RXA天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4E3)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXA_DC_Q_2_UNION */
#define ABB_CH1_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E4)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器1。
   详      述：RXB天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4E5)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXB_DC_I_2_UNION */
#define ABB_CH1_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4E6)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器1。
   详      述：RXB天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4E7)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXB_DC_Q_2_UNION */
#define ABB_CH1_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E8)

/* 寄存器说明：通道1配置寄存器。
   详      述：通道1 flush宽度[7:0]，单位为19.2M时钟周期。
   UNION结构 ：无 */
#define ABB_CH1_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4E9)

/* 寄存器说明：通道1配置寄存器。
 bit[7:3]    通道1 FLUSH值，默认为8。
 bit[2:0]    通道1 flush宽度[10:8]，单位为19.2M时钟周期。
   UNION结构:  ABB_CH1_FLUSH_CFG1_UNION */
#define ABB_CH1_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4EA)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
   详      述：CH1通道RXA I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4EB)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXAI_HB_GAIN_2_UNION */
#define ABB_CH1_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EC)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
   详      述：CH1通道RXA Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4ED)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EE)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
   详      述：CH1通道RXB I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4EF)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXBI_HB_GAIN_2_UNION */
#define ABB_CH1_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4F0)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
   详      述：CH1通道RXB Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4F1)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4F2)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      CH1通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
 bit[0]      CH1通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4F3)

/* 寄存器说明：线控强制配置使能。
 bit[7:6]    保留
 bit[5]      RXB通道强配线控
 bit[4]      RXA通道强配线控
 bit[3:2]    保留
 bit[1]      RXB通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
 bit[0]      RXA通道线控选择强配使能
             0：选择线控使能
             1：选择强配使能
   UNION结构:  ABB_CH1_RX_LINE_SEL_UNION */
#define ABB_CH1_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4F4)

/* 寄存器说明：模式线控强制配置。
 bit[7:4]    保留
 bit[3]      线控信号CH1_RX_LINE_CTRL_MODE强制配置使能
 bit[2:0]    线控信号CH1_RX_LINE_CTRL_MODE强制配置值
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模
   UNION结构:  ABB_CH1_RX_LINE_CFG_UNION */
#define ABB_CH1_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4F5)

/* 寄存器说明：blk控制寄存器。
 bit[7:3]    保留
 bit[2]      线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能
 bit[1]      线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值
 bit[0]      保留
   UNION结构:  ABB_CH1_BLK_CFG_UNION */
#define ABB_CH1_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4F6)

/* 寄存器说明：线控状态上报寄存器。
 bit[7:2]    保留
 bit[1]      CH1_RXB_EN线控状态上报
 bit[0]      CH1_RXA_EN线控状态上报
   UNION结构:  ABB_CH1_RX_LINE_RPT0_UNION */
#define ABB_CH1_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4F7)

/* 寄存器说明：线控状态上报寄存器。
 bit[7]      CH1_RXB_BLK_EN线控状态上报
 bit[6]      CH1_RXA_BLK_EN线控状态上报
 bit[5:3]    CH1 RX_LINE_CTRL_MODE状态上报：
             0：IDLE
             1：G模
             2：W模
             3：LTE模
             4：TDS模
             5：X模
             others：IDLE
 bit[2:0]    保留
   UNION结构:  ABB_CH1_RX_LINE_RPT1_UNION */
#define ABB_CH1_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4F8)

/* 寄存器说明：数字调试寄存器。
 bit[7]      bit[7]：模式切换复位长度配置使能
             0：不使能
             1：使能
 bit[6:4]    模式切换复位长度配置值，单位为8 cycles
 bit[3:1]    保留
 bit[0]      RX分频器使能bypass控制
             0：不bypass
             1：bypass
   UNION结构:  ABB_CH1_RX_REG_DEBUG_DIG_UNION */
#define ABB_CH1_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4F9)



/***======================================================================***
                     (4/4) register_define_abb_ana
 ***======================================================================***/
/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7]      保留
 bit[6]      SCPLL0锁定指示。
 bit[5]      SCPLL0稳定指示。0表示SCPLL0未稳定；1表示SCPLL0稳定。SCPLL0稳定后有时钟输出。
 bit[4]      SCPLL0门控使能信号。
 bit[3:1]    SCPLL0时钟稳定等待时间配置，计数时钟为19.2M：
             000：SCPLL0开启10us后时钟稳定；
             001：SCPLL0开启20us后时钟稳定；
             010：SCPLL0开启50us后时钟稳定；
             011：SCPLL0开启75us后时钟稳定；
             100：SCPLL0开启100us后时钟稳定；
             101：SCPLL0开启115us后时钟稳定；
             110：SCPLL0开启125us后时钟稳定；
             default：100us
 bit[0]      SCPLL0使能信号。用于通过CFG接口配置打开scpll0。
   UNION结构:  ABB_SCPLL0_LOCK_CTRL_UNION */
#define ABB_SCPLL0_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0x800)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7]:Reserved;
            [5:3]：PLL后分频因子postdiv2；默认值为1。
            [2:0]：PLL后分频因子postdiv1；默认值为5。
   UNION结构 ：无 */
#define ABB_SCPLL0_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0x801)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7:0]：PLL反馈分频因子fbdiv[11:0]的低8bit；fbdiv[11:0]默认值为64.
   UNION结构 ：无 */
#define ABB_SCPLL0_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0x802)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:4]    保留
 bit[3:0]    PLL反馈分频因子fbdiv[11:0]的高4bit；
   UNION结构:  ABB_SCPLL0_FBDIV_H_UNION */
#define ABB_SCPLL0_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0x803)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:6]    保留
 bit[5:0]    PLL参考分频因子refdiv[5:0]，默认值为1。
   UNION结构:  ABB_SCPLL0_REFDIV_UNION */
#define ABB_SCPLL0_REFDIV_ADDR                        (ABB_BASE_ADDR + 0x804)

/* 寄存器说明：SC_PLL分频器控制寄存器
   详      述：[7:6]：Reserved；
            [5]：DACPD；默认值为0(打开)。
            [4]：PLL FOUT4PHASEPD控制，高有效；默认值1（关闭）。
            [3]：DSMPD；小数模式PD信号，默认值0（打开）。
            [2]：PLL 旁路控制；默认值0（PLL旁路功能bypass）。
            [1]：PLL FOUTPOSTDIVPD控制，高有效；默认值0（打开）。
            [0]：PLL FOUTVCOPD控制，高有效；默认值0（打开）。
   UNION结构 ：无 */
#define ABB_SCPLL0_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0x805)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[7:0]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL0_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x806)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[15:8]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL0_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x807)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[23:16]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL0_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x808)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7:1]    保留
 bit[0]      SCPLL0参数配置更新指示。
             scpll0_en打开后，软件配置完scpll0_postdiv，scpll0_fbdiv，scpll0_frac参数，再配置scpll0_sfg_update，参数同时更新；scpll0_en不打开时，配置参数立即更新，不需要配置scpll0_sfg_update。
   UNION结构:  ABB_SCPLL0_CFG_UPDATE_UNION */
#define ABB_SCPLL0_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x809)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7]      保留
 bit[6]      SCPLL1锁定指示。
 bit[5]      SCPLL1稳定指示。0表示SCPLL1未稳定；1表示SCPLL1稳定。SCPLL1稳定后有时钟输出。
 bit[4]      SCPLL1门控使能信号。
 bit[3:1]    SCPLL1时钟稳定等待时间配置，计数时钟为19.2M：
             000：SCPLL1开启10us后时钟稳定；
             001：SCPLL1开启20us后时钟稳定；
             010：SCPLL1开启50us后时钟稳定；
             011：SCPLL1开启75us后时钟稳定；
             100：SCPLL1开启100us后时钟稳定；
             101：SCPLL1开启115us后时钟稳定；
             110：SCPLL1开启125us后时钟稳定；
             default：100us
 bit[0]      SCPLL1使能信号。用于通过CFG接口配置打开scpll1。
   UNION结构:  ABB_SCPLL1_LOCK_CTRL_UNION */
#define ABB_SCPLL1_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0x80A)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7]:Reserved;
            [5:3]：PLL后分频因子postdiv2；默认值为1。
            [2:0]：PLL后分频因子postdiv1；默认值为5。
   UNION结构 ：无 */
#define ABB_SCPLL1_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0x80B)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7:0]：PLL反馈分频因子fbdiv[11:0]的低8bit；fbdiv[11:0]默认值为64.
   UNION结构 ：无 */
#define ABB_SCPLL1_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0x80C)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:4]    保留
 bit[3:0]    PLL反馈分频因子fbdiv[11:0]的高4bit；
   UNION结构:  ABB_SCPLL1_FBDIV_H_UNION */
#define ABB_SCPLL1_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0x80D)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:6]    保留
 bit[5:0]    PLL参考分频因子refdiv[5:0]，默认值为1。
   UNION结构:  ABB_SCPLL1_REFDIV_UNION */
#define ABB_SCPLL1_REFDIV_ADDR                        (ABB_BASE_ADDR + 0x80E)

/* 寄存器说明：SC_PLL分频器控制寄存器
   详      述：[7:6]：Reserved；
            [5]：DACPD；默认值为0(打开)。
            [4]：PLL FOUT4PHASEPD控制，高有效；默认值1（关闭）。
            [3]：DSMPD；小数模式PD信号，默认值0（打开）。
            [2]：PLL 旁路控制；默认值0（PLL旁路功能bypass）。
            [1]：PLL FOUTPOSTDIVPD控制，高有效；默认值0（打开）。
            [0]：PLL FOUTVCOPD控制，高有效；默认值0（打开）。
   UNION结构 ：无 */
#define ABB_SCPLL1_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0x80F)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[7:0]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL1_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x810)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[15:8]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL1_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x811)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[23:16]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL1_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x812)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7:1]    保留
 bit[0]      SCPLL1参数配置更新指示。
             scpll1_en打开后，软件配置完scpll1_postdiv，scpll1_fbdiv，scpll1_frac参数，再配置scpll1_sfg_update，参数同时更新；scpll1_en不打开时，配置参数立即更新，不需要配置scpll1_sfg_update。
   UNION结构:  ABB_SCPLL1_CFG_UPDATE_UNION */
#define ABB_SCPLL1_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x813)

/* 寄存器说明：GPLL输出时钟门控时间配置
 bit[7]      保留
 bit[6]      GPLL锁定指示。
 bit[5]      GPLL稳定指示。0表示GPLL未稳定；1表示GPLL稳定。GPLL稳定后有时钟输出。
 bit[4]      GPLL时钟门控功能使能，
             0：gpll时钟门控功能关闭；
             1：gpll时钟门控功能打开。
 bit[3:1]    GPLL时钟稳定等待时间配置，计数时钟为19.2M：
             000：GPLL开启10us后时钟稳定；
             001：GPLL开启20us后时钟稳定；
             010：GPLL开启50us后时钟稳定；
             011：GPLL开启75us后时钟稳定；
             100：GPLL开启100us后时钟稳定；
             101：GPLL开启115us后时钟稳定；
             110：GPLL1开启125us后时钟稳定；
             default：20us
 bit[0]      GPLL使能
   UNION结构:  ABB_GPLL0_GATE_TIME_UNION */
#define ABB_GPLL0_GATE_TIME_ADDR                      (ABB_BASE_ADDR + 0x814)

/* 寄存器说明：GPLL输出时钟门控时间配置
 bit[7:1]    保留
 bit[0]      GPLL使能副卡
   UNION结构:  ABB_GPL1L_GATE_TIME_UNION */
#define ABB_GPL1L_GATE_TIME_ADDR                      (ABB_BASE_ADDR + 0x815)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] FREF_SEL
                PLL的参考时钟选择
                1：TCXO_INP作为PLL的参考时钟
                0：TCXO Buffer输出作为PLL参考时钟
            [6] reserved
            [5:4] WG_VCSEL
                  PLL控制电压测试PAD信号选择
                  00/11：控制电压测试PAD浮空
                  01：GPLL输出控制电压到PAD
                  10：WPLL输出控制电压到PAD (connect to GND)
            [3:2] WG_CLK_SEL：wpll/gpll 测试时钟选择
                  PLL时钟测试PAD信号选择
                  00/11：时钟测试PAD浮空
                  01：GPLL输出时钟到PAD
                  10：WPLL输出时钟到PAD
            [1:0] CLK_PADF_SEL：测试时钟选择
                  [1] 0：GPLL的测试频率为312M（默认）
                      1：GPLL的测试频率为156M
                  [0] (NC)
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR00_ADDR                      (ABB_BASE_ADDR + 0x880)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] reserved
            [6:4] FN_GPLL_SEL
                  G模工作PLL选择
                  0：选择GPLL；（默认选择GPLL）
                  1：选择SCPLL。
            [3] reserved
            [2:0] FN_WPLL_SEL
                  WPLL和SCPLL选择信号。
                  0：选择SCPLL；（默认）
                  1：选择WPLL。
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR01_ADDR                      (ABB_BASE_ADDR + 0x881)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR02_ADDR                      (ABB_BASE_ADDR + 0x882)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR03_ADDR                      (ABB_BASE_ADDR + 0x883)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] GPLL_CLK104M_PD gpll 104M时钟power down控制
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR04_ADDR                      (ABB_BASE_ADDR + 0x884)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR05_ADDR                      (ABB_BASE_ADDR + 0x885)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5] CH0_DAC_CLK_EN：ch0 dac时钟输出使能
                  0：时钟关闭
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR06_ADDR                      (ABB_BASE_ADDR + 0x886)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5] CH1_DAC_CLK_EN：ch1 dac时钟输出使能
                  0：时钟关闭
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR07_ADDR                      (ABB_BASE_ADDR + 0x887)

/* 寄存器说明：模拟common读写寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR08_ADDR                      (ABB_BASE_ADDR + 0x888)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:2] reserved
            [1:0] CH0_TCXO_DRV：ch0 TCXO BUFFER电流设置
                  00：1x
                  01：2x
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR09_ADDR                      (ABB_BASE_ADDR + 0x889)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] EXCLK_PD：外灌时钟power down控制
                  0：打开外灌时钟模块
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR10_ADDR                      (ABB_BASE_ADDR + 0x88A)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] GPLL_LOCK_EN：gpll输出lock信号使能
                  0：不输出检测lock信号
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR11_ADDR                      (ABB_BASE_ADDR + 0x88B)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] REF_FS_EN：ref快速启动控制
                 0：关闭(默认)
                 1：开启
            [3] reserved
            [1] BG_PD：Refence分压模块强制PD信号
                0： Reference分压模块状态由BG_EN信号及其它模块PD信号自动控制
                1： Reference分压模块强制Power Down
            [0] BG_EN：Refence分压模块强制EN信号
                0： Reference分压模块状态由BG_PD信号及其它模块PD信号自动控制
                1： 当BG_EN信号为1时，Reference分压模块强制启动
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR12_ADDR                      (ABB_BASE_ADDR + 0x88C)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] RCTUNE_CAP_SEL：rctune电容选择
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR13_ADDR                      (ABB_BASE_ADDR + 0x88D)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5:4] GFREF_SEL
                  GPLL输入时钟频率选择
                  00：26M
                  01：19.2M(默认)
                  10：52M
                  11：38.4M
            [3:0] CLK_IBIAS_CTRL
                  PLL总电流控制(高有效)
                  0000：1u
                  0001：1.5u
                  0010：2u
                  0011：2.5u
                  0100：3u
                  0101：3.5u
                  0110：4u
                  0111：4.5u
                  1000：5u(默认)
                  ……
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR14_ADDR                      (ABB_BASE_ADDR + 0x88E)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] reserved
            [6:4] ITR_VCM_BIAS:
            L/W/G 共用ADC 差分buffer电流调节控制
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u
            [3] reserved
            [2:0] CH0_ITR_ADC_BUF:
            L/W/G 共用ADC 差分buffer电流调节控制
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u

   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR15_ADDR                      (ABB_BASE_ADDR + 0x88F)

/* 寄存器说明：tuning_val_en
   详      述：[7:1] reversed
            [0] tuning_val_en: Tuning code来源选择
                0：寄存器配置（默认）
                1：自动更新
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR16_ADDR                      (ABB_BASE_ADDR + 0x890)

/* 寄存器说明：RX RCTUNE配置寄存器
   详      述：[7] reversed
            [6:0] RX_RCTUNE ：RX TUNE RC校准值
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR17_ADDR                      (ABB_BASE_ADDR + 0x891)

/* 寄存器说明：模拟common读写寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR18_ADDR                      (ABB_BASE_ADDR + 0x892)

/* 寄存器说明：模拟common读写寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR19_ADDR                      (ABB_BASE_ADDR + 0x893)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7:1] reversed
            [0]  RC_TUNE_READY ：RC校准完成信号
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO00_ADDR                      (ABB_BASE_ADDR + 0x8A0)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7] reversed
            [6:0] RC_TUNE_DOUT ：RC校准值
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO01_ADDR                      (ABB_BASE_ADDR + 0x8A1)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7] CH1_OPCAL_OK_RXB_Q：ch1 rxb q路op1校准完成信号
            [6] CH1_OPCAL_OK_RXB_I：ch1 rxb i路op1校准完成信号
            [5] CH1_OPCAL_OK_RXA_Q：ch1 rxa q路op1校准完成信号
            [4] CH1_OPCAL_OK_RXA_I：ch1 rxa i路op1校准完成信号
            [3] CH0_OPCAL_OK_RXB_Q：ch0 rxb q路op1校准完成信号
            [2] CH0_OPCAL_OK_RXB_I：ch0 rxb i路op1校准完成信号
            [1] CH0_OPCAL_OK_RXA_Q：ch0 rxa q路op1校准完成信号
            [0] CH0_OPCAL_OK_RXA_I：ch0 rxa i路op1校准完成信号
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO02_ADDR                      (ABB_BASE_ADDR + 0x8A2)

/* 寄存器说明：模拟common只读寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO03_ADDR                      (ABB_BASE_ADDR + 0x8A3)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA00)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH0_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH0_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA01)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA02)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA03)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA04)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA05)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA06)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA07)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA08)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH0_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH0_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA09)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA0A)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA0B)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA0C)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA0D)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA0E)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA0F)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA10)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH0_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH0_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA11)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA12)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA13)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA14)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA15)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA16)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA17)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xA18)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH0_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH0_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA19)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA1A)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA1B)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA1C)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA1D)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA1E)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA1F)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xA20)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH0_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH0_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA21)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA22)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA23)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA24)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA25)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA26)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA27)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xA28)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH0_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH0_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA29)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA2A)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA2B)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA2C)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA2D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA2E)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA2F)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA40)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH1_TX_FC：ch1 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH1_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA41)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA42)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA43)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA44)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA45)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA46)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA47)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA48)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH1_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH1_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA49)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA4A)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA4B)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA4C)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA4D)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA4E)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA4F)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA50)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH1_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH1_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA51)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA52)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA53)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA54)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA55)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA56)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA57)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xA58)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH1_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH1_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA59)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA5A)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA5B)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA5C)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA5D)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA5E)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA5F)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xA60)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH1_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH1_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA61)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA62)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA63)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA64)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA65)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA66)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA67)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xA68)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7] reserved
            [6:4] CH1_TX_FC：ch0 tx fc选择
                  000：20MHz
                  001：40MHz
                  010：13.5MHz
                  011：27MHz
                  100：10MHz(默认)
                  101：20MHz
                  110：41MHz
                  111：78MHz
                默认配置方法：
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE：ch0 tx div模式选择
                  00:1分频（默认）
                  01：2分频
                  10：8分频
                  11：4分频
            [1:0] CH1_TX_LPF_MODE：ch0 tx LPF运放偏置电流调整
                  00：   10u
                  01：    8u
                  10：    5u
                  11：    3u
                默认配置方法：
                  CA:00   LTE:10   Others:11
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA69)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA6A)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA6B)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA6C)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA6D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA6E)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA6F)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC00)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC01)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC02)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC03)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC04)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC05)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC06)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC07)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC08)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC09)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC0A)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC0B)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC0C)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC0D)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC0E)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC0F)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G (默认)
                  010：3G_DC &amp; TDS
                  011：2G_A
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC10)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC11)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC12)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC13)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC14)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC15)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC16)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC17)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC18)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC19)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC1A)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC1B)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC1C)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC1D)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC1E)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC1F)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC20)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC21)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC22)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC23)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC24)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC25)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC26)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC27)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC28)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC29)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC2A)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC2B)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC2C)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC2D)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC2E)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC2F)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS (默认)
                  011：2G_A
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xC30)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xC31)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xC32)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xC33)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xC34)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xC35)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xC36)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xC37)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xC38)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xC39)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xC3A)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xC3B)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xC3C)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xC3D)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xC3E)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xC3F)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xC40)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xC41)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xC42)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xC43)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xC44)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xC45)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xC46)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xC47)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xC48)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xC49)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xC4A)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xC4B)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xC4C)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xC4D)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xC4E)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xC4F)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xC50)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xC51)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xC52)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xC53)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xC54)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xC55)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xC56)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xC57)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xC58)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xC59)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xC5A)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xC5B)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xC5C)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xC5D)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xC5E)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xC5F)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] CH0_REG_TUNE1：ch0 rx cap1手动配置寄存器
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xC60)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] CH0_REG_TUNE2：ch0 rx cap2手动配置寄存器
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xC61)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] CH0_REG_TUNE3：ch0 rx cap3手动配置寄存器
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xC62)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] rc tuning 模式选择：0.寄存器手动配置；1.自发
            [6:0]  reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xC63)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] reserved
            [6:4] CH0_OL_CTRL：ch0 rx overload控制选择
                  ADC Overload模块配置
                  00：16个连续最大码或者最小码
                  01：8个连续最大码或者最小码
                  10：4个连续最大码或者最小码
                  11：关闭Overload检测
            [3:2] reserved
            [1] CH0_PUP_CLK_CTRL：ch0 rx 上电模块的时钟控制
                0：上电完成后关闭上电模块的时钟 (default)
                1：上电完成后不关闭上电模块时钟
            [0] CH0_PUP_MODE：ch0 rx 启动上电模式
                ADC模块上电模式选择
                0：自动模式
                1：配置寄存器上电模式
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xC64)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] CH0_PUP_CTRL：ch0 rx 启动上电控制
            [7] 配置寄存器上电模式时ADC中RST_CAP控制
            0：Reset CAP3
            1：不Reset CAP3
            [6]配置寄存器上电模式时ADC中RST_CAP控制
            0：Reset CAP2
            1：不Reset CAP2
            [5]配置寄存器上电模式时ADC中RST_CAP控制
            0：Reset CAP1
            1：不Reset CAP1
            [4]配置寄存器上电模式时ADC中OP控制
            0：OP Power Down
            1：OP Power On
            [3]配置寄存器上电模式时ADC中DAC控制
            0：DAC Power Down
            1：DAC Power On
            [2]配置寄存器上电模式时ADC中QT校正控制
            0：QT Calibration On
            1：QT Calibration Off
            [1]配置寄存器上电模式时ADC中CLKGEN控制
            0：CLKGEN Power Down
            1：CLKGEN Power On
            [0]配置寄存器上电模式时ADC中QT控制
            0：QT Power Down
            1：QT Power On
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xC65)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:6] RX通道OP1校正CAL开关控制
            00：
            01：
            10：
            11：
            [5] CH0_CAL_TRIM_SW：ch0 rx op1校准trim开关控制
                RX通道OP1校正Trim开关
                0：Trim Switch Off
                1：Trim Switch On
            [4] CH0_OPCAL_VCM_SEL：ch0 rx op1校准共模选择
                0：Disable
                1：Enable（短接共模进行OP Calibration）
            [3] CH0_RXB_EN_QTCAL：ch0 rx qt校准enable
            [2] CH0_RXA_EN_QTCAL：ch0 rx qt校准enable
            [1] CH0_RXB_EN_OPCAL：ch0 rx op1校准enable
            [0] CH0_RXA_EN_OPCAL：ch0 rx op1校准enable
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xC66)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] reserved
            [6] RXB_PD_CAL ( NC ）
            [5] RXA_PD_CAL ( NC ）
            [4] RX_VCM_ADJ_CTRL
                输入共模电平选择
                0：0.8V VCM Input
                1：0.5V VCM Input
            [3:1] reserved
            [0] CH0_QT_REF_SEL：ch0 rx qt的ref选择
                RX中QT中VREFP/VREN选择
                0：由ref模块提供
                1：由本地电阻分压提供
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xC67)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xC68)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xC69)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xC6A)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0xC6B)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0xC6C)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0xC6D)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7] TX rc tuning 模式选择：0.寄存器手动配置，1.自发
            [6:0]  reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xC6E)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7]
            [6:0] TX tuning 码配置寄存器
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xC6F)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC80)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC81)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC82)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC83)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC84)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC85)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC86)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC87)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC88)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC89)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC8A)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC8B)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC8C)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC8D)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC8E)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC8F)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC90)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC91)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC92)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC93)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC94)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC95)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC96)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC97)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC98)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC99)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC9A)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC9B)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC9C)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC9D)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC9E)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC9F)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xCA0)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xCA1)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xCA2)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xCA3)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xCA4)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xCA5)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xCA6)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xCA7)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xCA8)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xCA9)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xCAA)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xCAB)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xCAC)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xCAD)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xCAE)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xCAF)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xCB0)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xCB1)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xCB2)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xCB3)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xCB4)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xCB5)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xCB6)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xCB7)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xCB8)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xCB9)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xCBA)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xCBB)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xCBC)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xCBD)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xCBE)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xCBF)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xCC0)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xCC1)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xCC2)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xCC3)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xCC4)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xCC5)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xCC6)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xCC7)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xCC8)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xCC9)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xCCA)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xCCB)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xCCC)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xCCD)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xCCE)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xCCF)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                  000：4G
                  001：3G
                  010：3G_DC &amp; TDS
                  011：2G_A(默认)
                  100：CA
                  101：CDMA
                  110:2G_B
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xCD0)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT3：ch0 op3模式选择
            [3:2] CH0_MODE_IBCT2：ch0 op2模式选择
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                  OP1/OP2/OP3 Current Seting For Mode
                  11：CA mode Current
                  10：LTE mode Current
                  01：DC/TDS/X/2G_B mode Current
                  00：3G/2G_A mode Current
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xCD1)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7:6] reserved
            [5] PDM_CTRL: RX ADC的输出数据模式选择
                1：Binary Encoder
                0：Add Encoder（default）
            [4] DEM_OUTPUT_SEL: DEM输入逻辑类型
                0：DEM_IN ADD
                1：DEM_IN ENC
            [3] DEM_ENB: ADC DEM功能关闭信号
                0：DEM Enable
                1：DEM Disable
            [2:0] DEM mode
                  RX ADC的DAC DEM模式选择
                  000：DWA（default）
                  001：CLA1
                  010：CLA2
                  011：CLA3
                  100：CLA4
                  101：CLA5
                  110：CLA6
                  111：CLA7
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xCD2)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                  RX模式控制积分器前馈电阻RFF
                  1x：4.865K ohm CA/4G/DC/TDS/X
                  01：9.73K ohm 2G_B
                  00：19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                  RX模式控制积分器第一级输入电阻RIN1
                  11：2.8K ohm 2G_B
                  10：5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01：5.6K ohm
                  00：cut off
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                  RX模式控制积分器第二级输入电阻RIN2
                  1x：16.6K ohm CA/4G/DC/TDS/X
                  01：33.2K ohm 2G_B
                  00：66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                RX模式控制积分器第三级输入电阻RIN3
                1：6.93K ohm CA/4G/DC/TDS/X/2G_B
                0：13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                RX模式控制积分器反馈电阻RFB
                1：160K ohm CA/4G/DC/TDS/X/2G_B
                0：320K ohm 3G/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xCD3)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                  RX模式控制积分器信号前馈电阻RSIG
                  1x：46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01：93K ohm 3G/2G_A
                  00：cut off
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                  RX模式控制积分器第三级反馈电容调零电阻RZ
                  x000：500 ohm（default）
                  x100：167 ohm
                  x010：143 ohm
                  x110：90 ohm
                  xxx1：0 ohm
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xCD4)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:3] reserved
            [2] CH0_DLY_CTRL2：ch0 0.6ts时钟周期控制选择
                RX ADC 0.6Ts时序控制
                1：DAC3延时0.6Ts
                0：DAC3延时0.5Ts （default）
            [1] CH0_DCTRL23：ch0 dac23电流模式选择
                RX模式控制DAC23反馈电流调节
                1：Double icell23 current CA/4G/DC/TDS/X/2G_B
                0：Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1：ch0 dac1电流模式选择
                RX模式控制DAC1反馈电流调节
                1：Double icell1 current 2G_B
                0：Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xCD5)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7] reserved
            [6:4] CH0_IBCT_QT：ch0 rx QT电流大小调节
                  RX ADC QT偏置电流控制
                  000： 5u CA
                  001： 4u 4G
                  010： 3u WDC/TDS/2G_B/X
                  011： 2u 3G/2G_A
                  100： 10u
                  101： 9u
                  110： 8u
                  111： 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE：ch0 积分器电容cap模式选择
                  RX Integrator Cap Setting For Mode:
                  1x：DC/TDS/X/2G_B/3G/2G_A
                  01：4G
                  00：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xCD6)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
            RX ADC OP2偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
            RX ADC OP1偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xCD7)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
            RX ADC DAC偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
            RX ADC OP3偏置电流控制
            000： 5u(default)
            001： 4u
            010： 3u
            011： 2u
            100： 10u
            101： 9u
            110： 8u
            111： 7u
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xCD8)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
            RX Integrator Cap3 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
            [1:0] CH0_MULTI_RATE_CAP12：ch0 rx积分器1电容cap1乘积倍数选择
            RX Integrator Cap12 Multi Rate:
            11：x1.125
            10：x1.25 （for X mode）
            01：x1.5
            00：x1
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xCD9)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                输出至RX SYNC模块的时钟的正反沿控制
                0：正沿(default)
                1：反沿
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                输出至数字的时钟MCLK的二分频控制
                0：二分频 CA/2G_A/2G_B
                1：不分频 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                输出给RXADC各通路的时钟的二分频控制
                0：二分频 3G
                1：不分频 CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                输出至数字的时钟MCLK的正反沿控制
                0：正沿(default)
                1：反沿
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
                  提供给上电模块的时钟的分频控制
                  000： CA模式
                  100： 4G模式
                  110： WDC/TDS/2G_B/X模式
                  111:3G/2G_A模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xCDA)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:4] CH0_RXA_CLK_QT_CTRL：ch0 rxa qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xCDB)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:2] reserved
            [1:0] RX_DLY_CTRL：RXA ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xCDC)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:4] CH0_RXB_CLK_QT_CTRL：ch0 rxb qt延时选择
            RX ADC中QT的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
            RX ADC中反馈DAC3的延时控制
            0000：20ps
            0001：40ps
            …
            1000:180ps
            1001:200ps
            …
            1110：300ps
            1111：320ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xCDD)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:2] reserved
            [1:0] RXB ADC中量化器的固定延时控制
                  11：300ps
                  10：200ps
                  01：100ps
                  00：0ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xCDE)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制 0：正沿 1：反沿
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制 0：正沿 1：反沿
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制 0：正沿 1：反沿
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制 0：正沿 1：反沿
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制 0：正沿 1：反沿
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xCDF)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] CH1_REG_TUNE1：ch1 rx cap1手动配置寄存器
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xCE0)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] CH1_REG_TUNE2：ch1 rx cap2手动配置寄存器
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xCE1)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] CH1_REG_TUNE3：ch1 rx cap3手动配置寄存器
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xCE2)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7] rc tuning 模式选择：0.寄存器手动配置；1.自发
            [6:0]  reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xCE3)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7] reserved
            [6:4] CH0_OL_CTRL：ch0 rx overload控制选择
                  ADC Overload模块配置
                  00：16个连续最大码或者最小码
                  01：8个连续最大码或者最小码
                  10：4个连续最大码或者最小码
                  11：关闭Overload检测
            [3:2] reserved
            [1] CH0_PUP_CLK_CTRL：ch0 rx 上电模块的时钟控制
                0：上电完成后关闭上电模块的时钟 (default)
                1：上电完成后不关闭上电模块时钟
            [0] CH0_PUP_MODE：ch0 rx 启动上电模式
                ADC模块上电模式选择
                0：自动模式
                1：配置寄存器上电模式
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xCE4)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] CH0_PUP_CTRL：ch0 rx 启动上电控制
            [7] 配置寄存器上电模式时ADC中RST_CAP控制
            0：Reset CAP3
            1：不Reset CAP3
            [6]配置寄存器上电模式时ADC中RST_CAP控制
            0：Reset CAP2
            1：不Reset CAP2
            [5]配置寄存器上电模式时ADC中RST_CAP控制
            0：Reset CAP1
            1：不Reset CAP1
            [4]配置寄存器上电模式时ADC中OP控制
            0：OP Power Down
            1：OP Power On
            [3]配置寄存器上电模式时ADC中DAC控制
            0：DAC Power Down
            1：DAC Power On
            [2]配置寄存器上电模式时ADC中QT校正控制
            0：QT Calibration On
            1：QT Calibration Off
            [1]配置寄存器上电模式时ADC中CLKGEN控制
            0：CLKGEN Power Down
            1：CLKGEN Power On
            [0]配置寄存器上电模式时ADC中QT控制
            0：QT Power Down
            1：QT Power On
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xCE5)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:6] RX通道OP1校正CAL开关控制
            00：
            01：
            10：
            11：
            [5] CH0_CAL_TRIM_SW：ch0 rx op1校准trim开关控制
                RX通道OP1校正Trim开关
                0：Trim Switch Off
                1：Trim Switch On
            [4] CH0_OPCAL_VCM_SEL：ch0 rx op1校准共模选择
                0：Disable
                1：Enable（短接共模进行OP Calibration）
            [3] CH0_RXB_EN_QTCAL：ch0 rx qt校准enable
            [2] CH0_RXA_EN_QTCAL：ch0 rx qt校准enable
            [1] CH0_RXB_EN_OPCAL：ch0 rx op1校准enable
            [0] CH0_RXA_EN_OPCAL：ch0 rx op1校准enable
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xCE6)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7] reserved
            [6] RXB_PD_CAL ( NC ）
            [5] RXA_PD_CAL ( NC ）
            [4] RX_VCM_ADJ_CTRL
                输入共模电平选择
                0：0.8V VCM Input
                1：0.5V VCM Input
            [3:1] reserved
            [0] CH0_QT_REF_SEL：ch0 rx qt的ref选择
                RX中QT中VREFP/VREN选择
                0：由ref模块提供
                1：由本地电阻分压提供
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xCE7)

/* 寄存器说明：RX ch1配置寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xCE8)

/* 寄存器说明：RX ch1配置寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xCE9)

/* 寄存器说明：RX ch1配置寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xCEA)

/* 寄存器说明：RX ch1配置寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0xCEB)

/* 寄存器说明：RX ch1配置寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0xCEC)

/* 寄存器说明：RX ch1配置寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0xCED)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7] TX rc tuning 模式选择：0.寄存器手动配置，1.自发
            [6:0]  reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xCEE)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7]
            [6:0] TX tuning 码配置寄存器
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xCEF)





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
                     (1/4) register_define_abb_com
 ***======================================================================***/
/*****************************************************************************
 结构名    : ABB_TESTMODE_UNION
 结构说明  : TESTMODE 寄存器结构定义。地址偏移量:0x000，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_iq_chnl_sel : 1;  /* bit[0]  :  */
        unsigned long  rx_ab_chnl_sel : 1;  /* bit[1]  :  */
        unsigned long  reserved_0     : 2;  /* bit[2-3]: 保留 */
        unsigned long  test_mode      : 2;  /* bit[4-5]: bit[4:3]测试模式控制：
                                                         00：正常模式(默认)
                                                         01：数字算法逻辑环回模式
                                                         10：RX模拟测试模式(bypass RX数字滤波器)
                                                         11：数字/模拟接口环回
                                                         bit[5] reserved */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TESTMODE_UNION;
#define ABB_TESTMODE_rx_iq_chnl_sel_START  (0)
#define ABB_TESTMODE_rx_iq_chnl_sel_END    (0)
#define ABB_TESTMODE_rx_ab_chnl_sel_START  (1)
#define ABB_TESTMODE_rx_ab_chnl_sel_END    (1)
#define ABB_TESTMODE_test_mode_START       (4)
#define ABB_TESTMODE_test_mode_END         (5)


/*****************************************************************************
 结构名    : ABB_ATE_TESTMODE_UNION
 结构说明  : ATE_TESTMODE 寄存器结构定义。地址偏移量:0x001，初值:0x00，宽度:8
 寄存器说明: ATE_TEST_MODE
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ate_ch_sel : 3;  /* bit[0-2]:  */
        unsigned long  reserved   : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_ATE_TESTMODE_UNION;
#define ABB_ATE_TESTMODE_ate_ch_sel_START  (0)
#define ABB_ATE_TESTMODE_ate_ch_sel_END    (2)


/*****************************************************************************
 结构名    : ABB_TCXO_RPT_UNION
 结构说明  : TCXO_RPT 寄存器结构定义。地址偏移量:0x002，初值:0x00，宽度:8
 寄存器说明: TCXO_RPT
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tcxo_en  : 1;  /* bit[0]  :  */
        unsigned long  reserved : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TCXO_RPT_UNION;
#define ABB_TCXO_RPT_tcxo_en_START   (0)
#define ABB_TCXO_RPT_tcxo_en_END     (0)


/*****************************************************************************
 结构名    : ABB_ABB_DIG_PWR_RST_UNION
 结构说明  : ABB_DIG_PWR_RST 寄存器结构定义。地址偏移量:0x003，初值:0x00，宽度:8
 寄存器说明: ABB数字部分复位信号
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  abb_sw_rst_en : 1;  /* bit[0]  :  */
        unsigned long  reserved      : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_DIG_PWR_RST_UNION;
#define ABB_ABB_DIG_PWR_RST_abb_sw_rst_en_START  (0)
#define ABB_ABB_DIG_PWR_RST_abb_sw_rst_en_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_COMM_REG_DEBUG_DIG_UNION
 结构说明  : CH0_COMM_REG_DEBUG_DIG 寄存器结构定义。地址偏移量:0x004，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  clk_out_sel0 : 2;  /* bit[0-1]: 数字调试寄存器
                                                       bit[0]：管脚CH0_CLK_52M输出时钟选择
                                                       1：输出GPLL
                                                       0：输出SCPLL0 */
        unsigned long  reserved     : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_COMM_REG_DEBUG_DIG_UNION;
#define ABB_CH0_COMM_REG_DEBUG_DIG_clk_out_sel0_START  (0)
#define ABB_CH0_COMM_REG_DEBUG_DIG_clk_out_sel0_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_COMM_REG_DEBUG_DIG_UNION
 结构说明  : CH1_COMM_REG_DEBUG_DIG 寄存器结构定义。地址偏移量:0x005，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  clk_out_sel1 : 2;  /* bit[0-1]: 数字调试寄存器
                                                       bit[0]：管脚CH1_CLK_52M输出时钟选择
                                                       1：输出GPLL
                                                       0：输出SCPLL1 */
        unsigned long  reserved     : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_COMM_REG_DEBUG_DIG_UNION;
#define ABB_CH1_COMM_REG_DEBUG_DIG_clk_out_sel1_START  (0)
#define ABB_CH1_COMM_REG_DEBUG_DIG_clk_out_sel1_END    (1)


/*****************************************************************************
 结构名    : ABB_BIST_CFG_1_UNION
 结构说明  : BIST_CFG_1 寄存器结构定义。地址偏移量:0x006，初值:0x00，宽度:8
 寄存器说明: BIST配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_en               : 1;  /* bit[0]  : BIST使能。
                                                                0：不使能；
                                                                1：使能。 */
        unsigned long  bist_delay1           : 2;  /* bit[1-2]: 延时时间1配置值,通路使能到测试开始的延时时间选择。
                                                                00:50us（默认）
                                                                01:100us
                                                                10:200us
                                                                11:500us */
        unsigned long  bist_delay2           : 2;  /* bit[3-4]: 延时时间2配置值,信号直流量计算后的稳定时间配置。
                                                                00:20us（默认）
                                                                01:50us
                                                                10:200us
                                                                11:500us */
        unsigned long  bist_switch_delay_sel : 2;  /* bit[5-6]: 切换iq及通道时，有30拍随路时钟延时，在此基础上增加的延时Switch_delay的选择信号：
                                                                00：0us；(默认)
                                                                01：20us；
                                                                10：50us；
                                                                11：200us。 */
        unsigned long  bist_ch_en_ctrl       : 1;  /* bit[7]  : bist测试通道线控控制模式：
                                                                0：通道线控bist测试时全部拉高
                                                                1：通道线控bist测试时测试通道拉高，其他拉低。 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_1_UNION;
#define ABB_BIST_CFG_1_bist_en_START                (0)
#define ABB_BIST_CFG_1_bist_en_END                  (0)
#define ABB_BIST_CFG_1_bist_delay1_START            (1)
#define ABB_BIST_CFG_1_bist_delay1_END              (2)
#define ABB_BIST_CFG_1_bist_delay2_START            (3)
#define ABB_BIST_CFG_1_bist_delay2_END              (4)
#define ABB_BIST_CFG_1_bist_switch_delay_sel_START  (5)
#define ABB_BIST_CFG_1_bist_switch_delay_sel_END    (6)
#define ABB_BIST_CFG_1_bist_ch_en_ctrl_START        (7)
#define ABB_BIST_CFG_1_bist_ch_en_ctrl_END          (7)


/*****************************************************************************
 结构名    : ABB_BIST_CFG_4_UNION
 结构说明  : BIST_CFG_4 寄存器结构定义。地址偏移量:0x009，初值:0x00，宽度:8
 寄存器说明: BIST测试项目bypass寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_test_bypass : 6;  /* bit[0-5]: 测试项bypass信号：
                                                           [0]:1表示DC_I指标bypass；0表示不bypass；
                                                           [1]:1表示DC_Q指标bypass；0表示不bypass；
                                                           [2]:1表示SNDR_I指标bypass；0表示不bypass；
                                                           [3]:1表示SNDR_Q指标bypass；0表示不bypass；
                                                           [4]:1表示GAIN_MISMATCH指标bypass；0表示不bypass；
                                                           [5]:1表示GAIN_ERROR指标bypass；0表示不bypass； */
        unsigned long  reserved         : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_4_UNION;
#define ABB_BIST_CFG_4_bist_test_bypass_START  (0)
#define ABB_BIST_CFG_4_bist_test_bypass_END    (5)


/*****************************************************************************
 结构名    : ABB_BIST_CFG_5_UNION
 结构说明  : BIST_CFG_5 寄存器结构定义。地址偏移量:0x00A，初值:0x00，宽度:8
 寄存器说明: BIST手动流程配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_manual    : 1;  /* bit[0]  : 0：自动测试流程
                                                         1：手动测试流程 */
        unsigned long  bist_rx_ch_sel : 3;  /* bit[1-3]: 手动测试选择输入数据通道：
                                                         000：RXA（CH0）
                                                         001：RXB（CH0）
                                                         010：RXA（CH1）
                                                         011：RXB（CH1）
                                                         100：RXA（CH2）
                                                         101：RXB（CH2）
                                                         110：RXA（CH3）
                                                         111：RXB（CH3） */
        unsigned long  bist_gate_bp   : 1;  /* bit[4]  : 0：bist时钟受门控控制，bist_en拉高后bist才有时钟。（默认）
                                                         1：bist时钟不受门控控制。 */
        unsigned long  reserved       : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_5_UNION;
#define ABB_BIST_CFG_5_bist_manual_START     (0)
#define ABB_BIST_CFG_5_bist_manual_END       (0)
#define ABB_BIST_CFG_5_bist_rx_ch_sel_START  (1)
#define ABB_BIST_CFG_5_bist_rx_ch_sel_END    (3)
#define ABB_BIST_CFG_5_bist_gate_bp_START    (4)
#define ABB_BIST_CFG_5_bist_gate_bp_END      (4)


/*****************************************************************************
 结构名    : ABB_BIST_RPT_1_UNION
 结构说明  : BIST_RPT_1 寄存器结构定义。地址偏移量:0x00B，初值:0x00，宽度:8
 寄存器说明: BIST完成状态寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_done : 1;  /* bit[0]  : SNDR计算完成状态。
                                                    0：没有完成；
                                                    1：完成。 */
        unsigned long  reserved  : 6;  /* bit[1-6]: 保留 */
        unsigned long  bist_pass : 1;  /* bit[7]  : BIST所有启动的测试项是否通过，即未bypass的测试是否全部通过。
                                                    0：未通过；
                                                    1：通过。 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RPT_1_UNION;
#define ABB_BIST_RPT_1_bist_done_START  (0)
#define ABB_BIST_RPT_1_bist_done_END    (0)
#define ABB_BIST_RPT_1_bist_pass_START  (7)
#define ABB_BIST_RPT_1_bist_pass_END    (7)


/*****************************************************************************
 结构名    : ABB_BIST_RPT_2_UNION
 结构说明  : BIST_RPT_2 寄存器结构定义。地址偏移量:0x00C，初值:0x00，宽度:8
 寄存器说明: BIST结果上报寄存器
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
} ABB_BIST_RPT_2_UNION;
#define ABB_BIST_RPT_2_para_pass_flag_START  (0)
#define ABB_BIST_RPT_2_para_pass_flag_END    (5)


/*****************************************************************************
 结构名    : ABB_BIST_RPT_8_UNION
 结构说明  : BIST_RPT_8 寄存器结构定义。地址偏移量:0x012，初值:0x00，宽度:8
 寄存器说明: BIST结果上报寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_dc_i_msb : 3;  /* bit[0-2]: I路dc上报值高位。 */
        unsigned long  reserved      : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RPT_8_UNION;
#define ABB_BIST_RPT_8_bist_dc_i_msb_START  (0)
#define ABB_BIST_RPT_8_bist_dc_i_msb_END    (2)


/*****************************************************************************
 结构名    : ABB_BIST_RPT_10_UNION
 结构说明  : BIST_RPT_10 寄存器结构定义。地址偏移量:0x014，初值:0x00，宽度:8
 寄存器说明: BIST结果上报寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_dc_q_msb : 3;  /* bit[0-2]: Q路dc上报值高位。 */
        unsigned long  reserved      : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RPT_10_UNION;
#define ABB_BIST_RPT_10_bist_dc_q_msb_START  (0)
#define ABB_BIST_RPT_10_bist_dc_q_msb_END    (2)


/*****************************************************************************
 结构名    : ABB_BIST_CFG_6_UNION
 结构说明  : BIST_CFG_6 寄存器结构定义。地址偏移量:0x01F，初值:0x3E，宽度:8
 寄存器说明: BIST结果标准寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_min_msb : 6;  /* bit[0-5]: BIST DC达标下限高6bit，有符号数。 */
        unsigned long  reserved   : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_6_UNION;
#define ABB_BIST_CFG_6_dc_min_msb_START  (0)
#define ABB_BIST_CFG_6_dc_min_msb_END    (5)


/*****************************************************************************
 结构名    : ABB_BIST_CFG_8_UNION
 结构说明  : BIST_CFG_8 寄存器结构定义。地址偏移量:0x021，初值:0x01，宽度:8
 寄存器说明: BIST结果标准寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_max_msb : 6;  /* bit[0-5]: BIST DC达标上限高6bit，有符号数。 */
        unsigned long  reserved   : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_8_UNION;
#define ABB_BIST_CFG_8_dc_max_msb_START  (0)
#define ABB_BIST_CFG_8_dc_max_msb_END    (5)


/*****************************************************************************
 结构名    : ABB_BIST_TCXO_SEL_UNION
 结构说明  : BIST_TCXO_SEL 寄存器结构定义。地址偏移量:0x03F，初值:0x00，宽度:8
 寄存器说明: BIST_TCXO_SEL
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_tcxo_sel : 2;  /* bit[0-1]: bist_tcxo_sel:
                                                        0:19.2M
                                                        1:20.48M
                                                        2:30.72M
                                                        3:38.74M */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_TCXO_SEL_UNION;
#define ABB_BIST_TCXO_SEL_bist_tcxo_sel_START  (0)
#define ABB_BIST_TCXO_SEL_bist_tcxo_sel_END    (1)


/***======================================================================***
                     (2/4) register_define_abb_tx
 ***======================================================================***/
/*****************************************************************************
 结构名    : ABB_TX_IDLE_DIG_1_UNION
 结构说明  : tx_idle_dig_1 寄存器结构定义。地址偏移量:0x200，初值:0x02，宽度:8
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
                                                                2G,     3G,     4G,      TDS,      CDMA,    CA
                                                               (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                           0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                           1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_idle : 3;  /* bit[5-7]: TX通道模式控制：
                                                           000：2G(默认)
                                                           001：3G
                                                           010：4G
                                                           011：TDS
                                                           100：CDMA
                                                           101：CA
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
 结构说明  : tx_idle_dig_2 寄存器结构定义。地址偏移量:0x201，初值:0x2B，宽度:8
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
 结构说明  : tx_idle_dig_3 寄存器结构定义。地址偏移量:0x202，初值:0x00，宽度:8
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
 结构名    : ABB_TX_2G_DIG_1_UNION
 结构说明  : tx_2g_dig_1 寄存器结构定义。地址偏移量:0x203，初值:0x02，宽度:8
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
                                                              2G,     3G,     4G,      TDS,      CDMA,    CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                         0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_2g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G(默认)
                                                         001：3G
                                                         010：4G
                                                         011：TDS
                                                         100：CDMA
                                                         101：CA
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
 结构说明  : tx_2g_dig_2 寄存器结构定义。地址偏移量:0x204，初值:0x2B，宽度:8
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
 结构说明  : tx_2g_dig_3 寄存器结构定义。地址偏移量:0x205，初值:0x00，宽度:8
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
 结构名    : ABB_TX_C_DIG_1_UNION
 结构说明  : tx_c_dig_1 寄存器结构定义。地址偏移量:0x206，初值:0x82，宽度:8
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
                                                             2G,     3G,     4G,      TDS,      CDMA,    CA
                                                            (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                        0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                        1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_c : 3;  /* bit[5-7]: TX通道模式控制：
                                                        000：2G(默认)
                                                        001：3G
                                                        010：4G
                                                        011：TDS
                                                        100：CDMA
                                                        101：CA
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
 结构说明  : tx_c_dig_2 寄存器结构定义。地址偏移量:0x207，初值:0x2B，宽度:8
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
 结构说明  : tx_c_dig_3 寄存器结构定义。地址偏移量:0x208，初值:0x08，宽度:8
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
 结构名    : ABB_TX_TDS_DIG_1_UNION
 结构说明  : tx_tds_dig_1 寄存器结构定义。地址偏移量:0x209，初值:0x60，宽度:8
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
                                                               2G,     3G,     4G,      TDS,      CDMA,    CA
                                                              (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                          0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                          1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_tds : 3;  /* bit[5-7]: TX通道模式控制：
                                                          000：2G(默认)
                                                          001：3G
                                                          010：4G
                                                          011：TDS
                                                          100：CDMA
                                                          101：CA
                                                          Others：Reserved */
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
 结构说明  : tx_tds_dig_2 寄存器结构定义。地址偏移量:0x20A，初值:0x2B，宽度:8
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
 结构说明  : tx_tds_dig_3 寄存器结构定义。地址偏移量:0x20B，初值:0x00，宽度:8
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
 结构名    : ABB_CH0_TX_3G_DIG_1_UNION
 结构说明  : ch0_tx_3g_dig_1 寄存器结构定义。地址偏移量:0x210，初值:0x20，宽度:8
 寄存器说明: TX 3G模式配置寄存器1，由线控决定是否起作用。
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
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch0_tx_mode_dig_3g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             101：CA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_3G_DIG_1_UNION;
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_comp_bp_3g_START   (0)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_comp_bp_3g_END     (0)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_hb_bp_3g_START     (1)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_hb_bp_3g_END       (1)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_rate_3g_START      (2)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_rate_3g_END        (4)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_mode_dig_3g_START  (5)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_3G_DIG_2_UNION
 结构说明  : ch0_tx_3g_dig_2 寄存器结构定义。地址偏移量:0x211，初值:0x2B，宽度:8
 寄存器说明: TX 3G模式配置寄存器2，由线控决定是否起作用。
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
} ABB_CH0_TX_3G_DIG_2_UNION;
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_q_pd_3g_START        (0)
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_q_pd_3g_END          (0)
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_i_pd_3g_START        (1)
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_i_pd_3g_END          (1)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_const_3g_START      (2)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_const_3g_END        (3)
#define ABB_CH0_TX_3G_DIG_2_ch0_uddwa_dith_en_3g_START  (4)
#define ABB_CH0_TX_3G_DIG_2_ch0_uddwa_dith_en_3g_END    (4)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_dwa_en_3g_START     (5)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_dwa_en_3g_END       (5)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_lsb_bp_3g_START     (6)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_lsb_bp_3g_END       (6)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_msb_bp_3g_START     (7)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_3G_DIG_3_UNION
 结构说明  : ch0_tx_3g_dig_3 寄存器结构定义。地址偏移量:0x212，初值:0x00，宽度:8
 寄存器说明: TX 3G模式配置寄存器3，由线控决定是否起作用。
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
} ABB_CH0_TX_3G_DIG_3_UNION;
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_flush_en_3g_START  (1)
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_flush_en_3g_END    (1)
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_comp_sel_3g_START  (2)
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_TX_3G_DIG_1_UNION
 结构说明  : ch1_tx_3g_dig_1 寄存器结构定义。地址偏移量:0x213，初值:0x20，宽度:8
 寄存器说明: TX 3G模式配置寄存器1，由线控决定是否起作用。
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
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch1_tx_mode_dig_3g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             101：CA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_3G_DIG_1_UNION;
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_comp_bp_3g_START   (0)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_comp_bp_3g_END     (0)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_hb_bp_3g_START     (1)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_hb_bp_3g_END       (1)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_rate_3g_START      (2)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_rate_3g_END        (4)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_mode_dig_3g_START  (5)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_TX_3G_DIG_2_UNION
 结构说明  : ch1_tx_3g_dig_2 寄存器结构定义。地址偏移量:0x214，初值:0x2B，宽度:8
 寄存器说明: TX 3G模式配置寄存器2，由线控决定是否起作用。
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
} ABB_CH1_TX_3G_DIG_2_UNION;
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_q_pd_3g_START        (0)
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_q_pd_3g_END          (0)
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_i_pd_3g_START        (1)
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_i_pd_3g_END          (1)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_const_3g_START      (2)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_const_3g_END        (3)
#define ABB_CH1_TX_3G_DIG_2_ch1_uddwa_dith_en_3g_START  (4)
#define ABB_CH1_TX_3G_DIG_2_ch1_uddwa_dith_en_3g_END    (4)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_dwa_en_3g_START     (5)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_dwa_en_3g_END       (5)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_lsb_bp_3g_START     (6)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_lsb_bp_3g_END       (6)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_msb_bp_3g_START     (7)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_CH1_TX_3G_DIG_3_UNION
 结构说明  : ch1_tx_3g_dig_3 寄存器结构定义。地址偏移量:0x215，初值:0x00，宽度:8
 寄存器说明: TX 3G模式配置寄存器3，由线控决定是否起作用。
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
} ABB_CH1_TX_3G_DIG_3_UNION;
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_flush_en_3g_START  (1)
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_flush_en_3g_END    (1)
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_comp_sel_3g_START  (2)
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 结构名    : ABB_CH0_TX_4G_DIG_1_UNION
 结构说明  : ch0_tx_4g_dig_1 寄存器结构定义。地址偏移量:0x228，初值:0x40，宽度:8
 寄存器说明: TX 4G模式配置寄存器1，由线控决定是否起作用。
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
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch0_tx_mode_dig_4g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             101：CA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_4G_DIG_1_UNION;
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_comp_bp_4g_START   (0)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_comp_bp_4g_END     (0)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_hb_bp_4g_START     (1)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_hb_bp_4g_END       (1)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_rate_4g_START      (2)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_rate_4g_END        (4)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_mode_dig_4g_START  (5)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_4G_DIG_2_UNION
 结构说明  : ch0_tx_4g_dig_2 寄存器结构定义。地址偏移量:0x229，初值:0x2B，宽度:8
 寄存器说明: TX 4G模式配置寄存器2，由线控决定是否起作用。
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
} ABB_CH0_TX_4G_DIG_2_UNION;
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_q_pd_4g_START        (0)
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_q_pd_4g_END          (0)
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_i_pd_4g_START        (1)
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_i_pd_4g_END          (1)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_const_4g_START      (2)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_const_4g_END        (3)
#define ABB_CH0_TX_4G_DIG_2_ch0_uddwa_dith_en_4g_START  (4)
#define ABB_CH0_TX_4G_DIG_2_ch0_uddwa_dith_en_4g_END    (4)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_dwa_en_4g_START     (5)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_dwa_en_4g_END       (5)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_lsb_bp_4g_START     (6)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_lsb_bp_4g_END       (6)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_msb_bp_4g_START     (7)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_4G_DIG_3_UNION
 结构说明  : ch0_tx_4g_dig_3 寄存器结构定义。地址偏移量:0x22A，初值:0x00，宽度:8
 寄存器说明: TX 4G模式配置寄存器3，由线控决定是否起作用。
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
} ABB_CH0_TX_4G_DIG_3_UNION;
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_flush_en_4g_START  (1)
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_flush_en_4g_END    (1)
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_comp_sel_4g_START  (2)
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_TX_4G_DIG_1_UNION
 结构说明  : ch1_tx_4g_dig_1 寄存器结构定义。地址偏移量:0x22B，初值:0x40，宽度:8
 寄存器说明: TX 4G模式配置寄存器1，由线控决定是否起作用。
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
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                             1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch1_tx_mode_dig_4g : 3;  /* bit[5-7]: TX通道模式控制：
                                                             000：2G(默认)
                                                             001：3G
                                                             010：4G
                                                             011：TDS
                                                             100：CDMA
                                                             101：CA
                                                             Others：Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_4G_DIG_1_UNION;
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_comp_bp_4g_START   (0)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_comp_bp_4g_END     (0)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_hb_bp_4g_START     (1)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_hb_bp_4g_END       (1)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_rate_4g_START      (2)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_rate_4g_END        (4)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_mode_dig_4g_START  (5)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_TX_4G_DIG_2_UNION
 结构说明  : ch1_tx_4g_dig_2 寄存器结构定义。地址偏移量:0x22C，初值:0x2B，宽度:8
 寄存器说明: TX 4G模式配置寄存器2，由线控决定是否起作用。
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
} ABB_CH1_TX_4G_DIG_2_UNION;
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_q_pd_4g_START        (0)
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_q_pd_4g_END          (0)
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_i_pd_4g_START        (1)
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_i_pd_4g_END          (1)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_const_4g_START      (2)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_const_4g_END        (3)
#define ABB_CH1_TX_4G_DIG_2_ch1_uddwa_dith_en_4g_START  (4)
#define ABB_CH1_TX_4G_DIG_2_ch1_uddwa_dith_en_4g_END    (4)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_dwa_en_4g_START     (5)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_dwa_en_4g_END       (5)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_lsb_bp_4g_START     (6)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_lsb_bp_4g_END       (6)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_msb_bp_4g_START     (7)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_CH1_TX_4G_DIG_3_UNION
 结构说明  : ch1_tx_4g_dig_3 寄存器结构定义。地址偏移量:0x22D，初值:0x00，宽度:8
 寄存器说明: TX 4G模式配置寄存器3，由线控决定是否起作用。
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
} ABB_CH1_TX_4G_DIG_3_UNION;
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_flush_en_4g_START  (1)
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_flush_en_4g_END    (1)
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_comp_sel_4g_START  (2)
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 结构名    : ABB_CH0_TX_TESTMODE_UNION
 结构说明  : CH0_TX_TESTMODE 寄存器结构定义。地址偏移量:0x240，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_sw_rst   : 1;  /* bit[0]  : 数字部分TX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  reserved_0      : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch0_tx_loop_sel : 2;  /* bit[4-5]: TX算法环回，环回通道选择：
                                                          0：环回CH0 RX
                                                          1：环回CH1 RX
                                                          2：环回CH2 RX
                                                          default：环回CH0 RX */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_TESTMODE_UNION;
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_START    (0)
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_END      (0)
#define ABB_CH0_TX_TESTMODE_ch0_tx_loop_sel_START  (4)
#define ABB_CH0_TX_TESTMODE_ch0_tx_loop_sel_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_SINE_GENERATE_UNION
 结构说明  : CH0_SINE_GENERATE 寄存器结构定义。地址偏移量:0x241，初值:0x10，宽度:8
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
        unsigned long  reserved        : 1;  /* bit[1]  : 保留 */
        unsigned long  ch0_sine_amp    : 2;  /* bit[2-3]: 正弦波发送幅度控制
                                                          00：满量程
                                                          01：3/4量程
                                                          10：1/2量程
                                                          11：1/4量程 */
        unsigned long  ch0_sine_freq   : 4;  /* bit[4-7]: 正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_SINE_GENERATE_UNION;
#define ABB_CH0_SINE_GENERATE_ch0_sine_enable_START  (0)
#define ABB_CH0_SINE_GENERATE_ch0_sine_enable_END    (0)
#define ABB_CH0_SINE_GENERATE_ch0_sine_amp_START     (2)
#define ABB_CH0_SINE_GENERATE_ch0_sine_amp_END       (3)
#define ABB_CH0_SINE_GENERATE_ch0_sine_freq_START    (4)
#define ABB_CH0_SINE_GENERATE_ch0_sine_freq_END      (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_COEF1_UNION
 结构说明  : ch0_tx_coef1 寄存器结构定义。地址偏移量:0x244，初值:0x3B，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_c0 : 6;  /* bit[0-5]: TX补偿滤波器系数C0,6bit有符号数 */
        unsigned long  reserved       : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_COEF1_UNION;
#define ABB_CH0_TX_COEF1_ch0_tx_comp_c0_START  (0)
#define ABB_CH0_TX_COEF1_ch0_tx_comp_c0_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_TX_COEF4_UNION
 结构说明  : ch0_tx_coef4 寄存器结构定义。地址偏移量:0x247，初值:0x03，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_c2_msb : 2;  /* bit[0-1]: TX补偿滤波器系数C2高2位,10bit有符号数 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_COEF4_UNION;
#define ABB_CH0_TX_COEF4_ch0_tx_comp_c2_msb_START  (0)
#define ABB_CH0_TX_COEF4_ch0_tx_comp_c2_msb_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_TX_COEF6_UNION
 结构说明  : ch0_tx_coef6 寄存器结构定义。地址偏移量:0x249，初值:0x02，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_c3_msb : 2;  /* bit[0-1]: TX补偿滤波器系数C3高2位,10bit无符号数 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_COEF6_UNION;
#define ABB_CH0_TX_COEF6_ch0_tx_comp_c3_msb_START  (0)
#define ABB_CH0_TX_COEF6_ch0_tx_comp_c3_msb_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_TX_REG_DEBUG_DIG0_UNION
 结构说明  : ch0_tx_reg_debug_dig0 寄存器结构定义。地址偏移量:0x24C，初值:0x64，宽度:8
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
        unsigned long  reserved_0        : 1;  /* bit[5]  : 保留 */
        unsigned long  ch0_tx_main_sd_bp : 1;  /* bit[6]  : TX SD模块主调制器旁路使能：
                                                            0：主调制器不旁路；
                                                            1：主调制器旁路（默认）； */
        unsigned long  reserved_1        : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_REG_DEBUG_DIG0_UNION;
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_START   (0)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_END     (0)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dem_mode_START       (1)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dem_mode_END         (1)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_dem_sat_START     (2)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_dem_sat_END       (3)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dither_en_START      (4)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dither_en_END        (4)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_START  (6)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_TX_REG_DEBUG_DIG4_UNION
 结构说明  : ch0_tx_reg_debug_dig4 寄存器结构定义。地址偏移量:0x250，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_div_en_bp      : 1;  /* bit[0]  : TX分频器使能bypass控制
                                                                0：不bypass
                                                                1：bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch0_tx_sw_rst_num_cfg : 3;  /* bit[4-6]: 模式切换复位长度配置值，单位为8 cycles */
        unsigned long  ch0_tx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]：模式切换复位长度配置使能
                                                                0：不使能
                                                                1：使能 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_REG_DEBUG_DIG4_UNION;
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_div_en_bp_START       (0)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_div_en_bp_END         (0)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_cfg_START  (4)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_cfg_END    (6)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_sel_START  (7)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_sel_END    (7)


/*****************************************************************************
 结构名    : ABB_CH0_TX_LINE_SEL_UNION
 结构说明  : CH0_TX_LINE_SEL 寄存器结构定义。地址偏移量:0x251，初值:0x00，宽度:8
 寄存器说明: 线控强制配置使能。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_en_sel : 1;  /* bit[0]  : TX通道线控选择强配使能
                                                        0：选择线控使能
                                                        1：选择强配使能 */
        unsigned long  reserved_0    : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch0_tx_en_cfg : 1;  /* bit[4]  : TX通道强配线控 */
        unsigned long  reserved_1    : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_SEL_UNION;
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_sel_START  (0)
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_sel_END    (0)
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_cfg_START  (4)
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_cfg_END    (4)


/*****************************************************************************
 结构名    : ABB_CH0_TX_LINE_CFG_UNION
 结构说明  : ch0_tx_line_cfg 寄存器结构定义。地址偏移量:0x252，初值:0x00，宽度:8
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
                                                                    5：X模式 */
        unsigned long  ch0_tx_line_ctrl_mode_sel : 1;  /* bit[3]  : 线控信号CH0_TX_LINE_CTRL_MODE强制配置使能 */
        unsigned long  reserved                  : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_CFG_UNION;
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_sel_START  (3)
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 结构名    : ABB_CH0_TX_LINE_RPT0_UNION
 结构说明  : ch0_tx_line_rpt0 寄存器结构定义。地址偏移量:0x253，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0    : 2;  /* bit[0-1]: 保留 */
        unsigned long  ch0_tx_en_rpt : 1;  /* bit[2]  : CH0_TX_EN线控状态上报 */
        unsigned long  reserved_1    : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_RPT0_UNION;
#define ABB_CH0_TX_LINE_RPT0_ch0_tx_en_rpt_START  (2)
#define ABB_CH0_TX_LINE_RPT0_ch0_tx_en_rpt_END    (2)


/*****************************************************************************
 结构名    : ABB_CH0_TX_LINE_RPT1_UNION
 结构说明  : ch0_tx_line_rpt1 寄存器结构定义。地址偏移量:0x254，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: CH0 TX_LINE_CTRL_MODE状态上报
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  reserved                  : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_RPT1_UNION;
#define ABB_CH0_TX_LINE_RPT1_ch0_tx_line_ctrl_mode_rpt_START  (0)
#define ABB_CH0_TX_LINE_RPT1_ch0_tx_line_ctrl_mode_rpt_END    (2)


/*****************************************************************************
 结构名    : ABB_CH1_TX_TESTMODE_UNION
 结构说明  : CH1_TX_TESTMODE 寄存器结构定义。地址偏移量:0x260，初值:0x10，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_sw_rst   : 1;  /* bit[0]  : 数字部分TX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  reserved_0      : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch1_tx_loop_sel : 2;  /* bit[4-5]: TX算法环回，环回通道选择：
                                                          0：环回CH0 RX
                                                          1：环回CH1 RX
                                                          2：环回CH2 RX
                                                          default：环回CH0 RX */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_TESTMODE_UNION;
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_START    (0)
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_END      (0)
#define ABB_CH1_TX_TESTMODE_ch1_tx_loop_sel_START  (4)
#define ABB_CH1_TX_TESTMODE_ch1_tx_loop_sel_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_SINE_GENERATE_UNION
 结构说明  : CH1_SINE_GENERATE 寄存器结构定义。地址偏移量:0x261，初值:0x10，宽度:8
 寄存器说明: SINE发送寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_sine_enable : 1;  /* bit[0]  : ch0正弦波发送使能
                                                          0：不发送
                                                          1：发送 */
        unsigned long  reserved        : 1;  /* bit[1]  : 保留 */
        unsigned long  ch1_sine_amp    : 2;  /* bit[2-3]: 正弦波发送幅度控制
                                                          00：满量程
                                                          01：3/4量程
                                                          10：1/2量程
                                                          11：1/4量程 */
        unsigned long  ch1_sine_freq   : 4;  /* bit[4-7]: 正弦波发送频率控制，单位(freq of tx_hb_clk)/32，可配范围为1~f */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_SINE_GENERATE_UNION;
#define ABB_CH1_SINE_GENERATE_ch1_sine_enable_START  (0)
#define ABB_CH1_SINE_GENERATE_ch1_sine_enable_END    (0)
#define ABB_CH1_SINE_GENERATE_ch1_sine_amp_START     (2)
#define ABB_CH1_SINE_GENERATE_ch1_sine_amp_END       (3)
#define ABB_CH1_SINE_GENERATE_ch1_sine_freq_START    (4)
#define ABB_CH1_SINE_GENERATE_ch1_sine_freq_END      (7)


/*****************************************************************************
 结构名    : ABB_CH1_TX_COEF1_UNION
 结构说明  : ch1_tx_coef1 寄存器结构定义。地址偏移量:0x264，初值:0x3B，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_c0 : 6;  /* bit[0-5]: TX补偿滤波器系数C0,6bit有符号数 */
        unsigned long  reserved       : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_COEF1_UNION;
#define ABB_CH1_TX_COEF1_ch1_tx_comp_c0_START  (0)
#define ABB_CH1_TX_COEF1_ch1_tx_comp_c0_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_TX_COEF4_UNION
 结构说明  : ch1_tx_coef4 寄存器结构定义。地址偏移量:0x267，初值:0x03，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_c2_msb : 2;  /* bit[0-1]: TX补偿滤波器系数C2高2位,10bit有符号数 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_COEF4_UNION;
#define ABB_CH1_TX_COEF4_ch1_tx_comp_c2_msb_START  (0)
#define ABB_CH1_TX_COEF4_ch1_tx_comp_c2_msb_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_TX_COEF6_UNION
 结构说明  : ch1_tx_coef6 寄存器结构定义。地址偏移量:0x269，初值:0x02，宽度:8
 寄存器说明: TX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_c3_msb : 2;  /* bit[0-1]: TX补偿滤波器系数C3高2位,10bit无符号数 */
        unsigned long  reserved           : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_COEF6_UNION;
#define ABB_CH1_TX_COEF6_ch1_tx_comp_c3_msb_START  (0)
#define ABB_CH1_TX_COEF6_ch1_tx_comp_c3_msb_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_TX_REG_DEBUG_DIG0_UNION
 结构说明  : CH1_TX_REG_DEBUG_DIG0 寄存器结构定义。地址偏移量:0x26C，初值:0x44，宽度:8
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
        unsigned long  reserved_0        : 1;  /* bit[5]  : 保留 */
        unsigned long  ch1_tx_main_sd_bp : 1;  /* bit[6]  : TX SD模块主调制器旁路使能：
                                                            0：主调制器不旁路；
                                                            1：主调制器旁路（默认）； */
        unsigned long  reserved_1        : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_REG_DEBUG_DIG0_UNION;
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_START   (0)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_END     (0)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dem_mode_START       (1)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dem_mode_END         (1)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_dem_sat_START     (2)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_dem_sat_END       (3)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dither_en_START      (4)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dither_en_END        (4)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_START  (6)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_TX_REG_DEBUG_DIG4_UNION
 结构说明  : ch1_tx_reg_debug_dig4 寄存器结构定义。地址偏移量:0x270，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_div_en_bp      : 1;  /* bit[0]  : TX分频器使能bypass控制
                                                                0：不bypass
                                                                1：bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch1_tx_sw_rst_num_cfg : 3;  /* bit[4-6]: 模式切换复位长度配置值，单位为8 cycles */
        unsigned long  ch1_tx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]：模式切换复位长度配置使能
                                                                0：不使能
                                                                1：使能 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_REG_DEBUG_DIG4_UNION;
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_div_en_bp_START       (0)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_div_en_bp_END         (0)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_cfg_START  (4)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_cfg_END    (6)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_sel_START  (7)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_sel_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_TX_LINE_SEL_UNION
 结构说明  : CH1_TX_LINE_SEL 寄存器结构定义。地址偏移量:0x271，初值:0x00，宽度:8
 寄存器说明: 线控强制配置使能。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_en_sel : 1;  /* bit[0]  : TX通道线控选择强配使能
                                                        0：选择线控使能
                                                        1：选择强配使能 */
        unsigned long  reserved_0    : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch1_tx_en_cfg : 1;  /* bit[4]  : TX通道强配线控 */
        unsigned long  reserved_1    : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_SEL_UNION;
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_sel_START  (0)
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_sel_END    (0)
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_cfg_START  (4)
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_cfg_END    (4)


/*****************************************************************************
 结构名    : ABB_CH1_TX_LINE_CFG_UNION
 结构说明  : ch1_tx_line_cfg 寄存器结构定义。地址偏移量:0x272，初值:0x00，宽度:8
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
                                                                    5：X模式 */
        unsigned long  ch1_tx_line_ctrl_mode_sel : 1;  /* bit[3]  : 线控信号CH1_LINE_CTRL_MODE强制配置使能 */
        unsigned long  reserved                  : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_CFG_UNION;
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_sel_START  (3)
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_TX_LINE_RPT0_UNION
 结构说明  : ch1_tx_line_rpt0 寄存器结构定义。地址偏移量:0x273，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0    : 2;  /* bit[0-1]: 保留 */
        unsigned long  ch1_tx_en_rpt : 1;  /* bit[2]  : CH1_TX_EN线控状态上报 */
        unsigned long  reserved_1    : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_RPT0_UNION;
#define ABB_CH1_TX_LINE_RPT0_ch1_tx_en_rpt_START  (2)
#define ABB_CH1_TX_LINE_RPT0_ch1_tx_en_rpt_END    (2)


/*****************************************************************************
 结构名    : ABB_CH1_TX_LINE_RPT1_UNION
 结构说明  : ch1_tx_line_rpt1 寄存器结构定义。地址偏移量:0x274，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: CH1 TX_LINE_CTRL_MODE状态上报
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  reserved                  : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_RPT1_UNION;
#define ABB_CH1_TX_LINE_RPT1_ch1_tx_line_ctrl_mode_rpt_START  (0)
#define ABB_CH1_TX_LINE_RPT1_ch1_tx_line_ctrl_mode_rpt_END    (2)


/***======================================================================***
                     (3/4) register_define_abb_rx
 ***======================================================================***/
/*****************************************************************************
 结构名    : ABB_RX_IDLE_DIG_1_UNION
 结构说明  : RX_IDLE_DIG_1 寄存器结构定义。地址偏移量:0x400，初值:0x70，宽度:8
 寄存器说明: RX IDLE模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_idle    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                           0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                           1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0       : 3;  /* bit[1-3]: 保留 */
        unsigned long  rx_mode_dig_idle : 3;  /* bit[4-6]: RX通道模式控制：
                                                           000：2G_A
                                                           001：3G_SC/TDS_B/4G_C
                                                           010：4G
                                                           011：3G_DC/4G_B
                                                           100：TDS
                                                           101：CDMA
                                                           110：CA
                                                           111：2G_B(默认) */
        unsigned long  reserved_1       : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_1_UNION;
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_START     (0)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_END       (0)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_START  (4)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_DIG_2_UNION
 结构说明  : RX_IDLE_DIG_2 寄存器结构定义。地址偏移量:0x401，初值:0x03，宽度:8
 寄存器说明: RX IDLE模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_idle      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_idle      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_idle    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                           00：gain为0.5(默认)
                                                           01：gain为0.75
                                                           10：gain为0.85
                                                           11：Reserved */
        unsigned long  rx_comp_bp_idle  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                           0：不bypass(默认)
                                                           1：bypass */
        unsigned long  rx_clk_inv_idle  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                           0：正常
                                                           1：反向 */
        unsigned long  rx_flush_en_idle : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                           0：不使能
                                                           1：使能 */
        unsigned long  reserved         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_2_UNION;
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_START       (0)
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_END         (0)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_START       (1)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_END         (1)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_START     (2)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_END       (3)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_START   (4)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_END     (4)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_START   (5)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_END     (5)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_START  (6)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_IDLE_DIG_3_UNION
 结构说明  : RX_IDLE_DIG_3 寄存器结构定义。地址偏移量:0x402，初值:0x10，宽度:8
 寄存器说明: RX IDLE模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_idle : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                           2'b00：2560chip。(W模默认)
                                                           2'b01：512chip。
                                                           2'b10：1024chip。(X模默认)
                                                           2'b11：2048chip。 */
        unsigned long  reserved_0       : 2;  /* bit[2-3]: 保留 */
        unsigned long  rx_comp_sel_idle : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                           000：系数不固定，由寄存器配置；
                                                           001：固定系数1；
                                                           010：固定系数2；
                                                           011：固定系数3；
                                                           100：固定系数4； */
        unsigned long  reserved_1       : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_3_UNION;
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_START  (0)
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_END    (1)
#define ABB_RX_IDLE_DIG_3_rx_comp_sel_idle_START  (4)
#define ABB_RX_IDLE_DIG_3_rx_comp_sel_idle_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_2G_DIG_1_UNION
 结构说明  : RX_2G_DIG_1 寄存器结构定义。地址偏移量:0x403，初值:0x00，宽度:8
 寄存器说明: RX 2G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_2g    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                         0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                         1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0     : 3;  /* bit[1-3]: 保留 */
        unsigned long  rx_mode_dig_2g : 3;  /* bit[4-6]: RX通道模式控制：
                                                         000：2G_A
                                                         001：3G_SC/TDS_B/4G_C
                                                         010：4G
                                                         011：3G_DC/4G_B
                                                         100：TDS
                                                         101：CDMA
                                                         110：CA
                                                         111：2G_B(默认) */
        unsigned long  reserved_1     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_1_UNION;
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_START     (0)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_END       (0)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_START  (4)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_2G_DIG_2_UNION
 结构说明  : RX_2G_DIG_2 寄存器结构定义。地址偏移量:0x404，初值:0x13，宽度:8
 寄存器说明: RX 2G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_2g      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                         0：不CLOCK GATING
                                                         1：CLOCK GATING(默认)
                                                         (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_2g      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                         0：不CLOCK GATING
                                                         1：CLOCK GATING(默认)
                                                         (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_2g    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                         00：gain为0.5(默认)
                                                         01：gain为0.75
                                                         10：gain为0.85
                                                         11：Reserved */
        unsigned long  rx_comp_bp_2g  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                         0：不bypass
                                                         1：bypass(默认) */
        unsigned long  rx_clk_inv_2g  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                         0：正常
                                                         1：反向 */
        unsigned long  rx_flush_en_2g : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  reserved       : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_2_UNION;
#define ABB_RX_2G_DIG_2_rxa_pd_2g_START       (0)
#define ABB_RX_2G_DIG_2_rxa_pd_2g_END         (0)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_START       (1)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_END         (1)
#define ABB_RX_2G_DIG_2_gain_sel_2g_START     (2)
#define ABB_RX_2G_DIG_2_gain_sel_2g_END       (3)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_START   (4)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_END     (4)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_START   (5)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_END     (5)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_START  (6)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_2G_DIG_3_UNION
 结构说明  : RX_2G_DIG_3 寄存器结构定义。地址偏移量:0x405，初值:0x00，宽度:8
 寄存器说明: RX 2G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_2g : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                         2'b00：2560chip。(W模默认)
                                                         2'b01：512chip。
                                                         2'b10：1024chip。(X模默认)
                                                         2'b11：2048chip。 */
        unsigned long  reserved_0     : 2;  /* bit[2-3]: 保留 */
        unsigned long  rx_comp_sel_2g : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                         000：系数不固定，由寄存器配置；
                                                         001：固定系数1；
                                                         010：固定系数2；
                                                         011：固定系数3；
                                                         100：固定系数4；
                                                         101：固定系数5；
                                                         110：固定系数6；
                                                         111：固定系数7。 */
        unsigned long  reserved_1     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_3_UNION;
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_START  (0)
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_END    (1)
#define ABB_RX_2G_DIG_3_rx_comp_sel_2g_START  (4)
#define ABB_RX_2G_DIG_3_rx_comp_sel_2g_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_C_DIG_1_UNION
 结构说明  : RX_C_DIG_1 寄存器结构定义。地址偏移量:0x406，初值:0x51，宽度:8
 寄存器说明: RX C模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_c    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                        0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                        1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0    : 3;  /* bit[1-3]: 保留 */
        unsigned long  rx_mode_dig_c : 3;  /* bit[4-6]: RX通道模式控制：
                                                        000：2G_A(默认)
                                                        001：3G_SC/TDS_B/4G_C
                                                        010：4G
                                                        011：3G_DC/4G_B
                                                        100：TDS
                                                        101：CDMA
                                                        110：CA
                                                        111：2G_B */
        unsigned long  reserved_1    : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_1_UNION;
#define ABB_RX_C_DIG_1_rx_hb_bp_c_START     (0)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_END       (0)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_START  (4)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_C_DIG_2_UNION
 结构说明  : RX_C_DIG_2 寄存器结构定义。地址偏移量:0x407，初值:0x03，宽度:8
 寄存器说明: RX C模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_c      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_c      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                        0：不CLOCK GATING
                                                        1：CLOCK GATING(默认)
                                                        (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_c    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                        00：gain为0.5(默认)
                                                        01：gain为0.75
                                                        10：gain为0.85
                                                        11：Reserved */
        unsigned long  rx_comp_bp_c  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                        0：不bypass
                                                        1：bypass(默认) */
        unsigned long  rx_clk_inv_c  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                        0：正常
                                                        1：反向 */
        unsigned long  rx_flush_en_c : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                        0：不使能
                                                        1：使能 */
        unsigned long  reserved      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_2_UNION;
#define ABB_RX_C_DIG_2_rxa_pd_c_START       (0)
#define ABB_RX_C_DIG_2_rxa_pd_c_END         (0)
#define ABB_RX_C_DIG_2_rxb_pd_c_START       (1)
#define ABB_RX_C_DIG_2_rxb_pd_c_END         (1)
#define ABB_RX_C_DIG_2_gain_sel_c_START     (2)
#define ABB_RX_C_DIG_2_gain_sel_c_END       (3)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_START   (4)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_END     (4)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_START   (5)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_END     (5)
#define ABB_RX_C_DIG_2_rx_flush_en_c_START  (6)
#define ABB_RX_C_DIG_2_rx_flush_en_c_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_C_DIG_3_UNION
 结构说明  : RX_C_DIG_3 寄存器结构定义。地址偏移量:0x408，初值:0x12，宽度:8
 寄存器说明: RX C模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_c : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                        2'b00：2560chip。(W模默认)
                                                        2'b01：512chip。
                                                        2'b10：1024chip。(X模默认)
                                                        2'b11：2048chip。 */
        unsigned long  reserved_0    : 2;  /* bit[2-3]: 保留 */
        unsigned long  rx_comp_sel_c : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                        000：系数不固定，由寄存器配置；
                                                        001：固定系数1；
                                                        010：固定系数2；
                                                        011：固定系数3；
                                                        100：固定系数4；
                                                        101：固定系数5；
                                                        110：固定系数6；
                                                        111：固定系数7。 */
        unsigned long  reserved_1    : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_3_UNION;
#define ABB_RX_C_DIG_3_blk_len_sel_c_START  (0)
#define ABB_RX_C_DIG_3_blk_len_sel_c_END    (1)
#define ABB_RX_C_DIG_3_rx_comp_sel_c_START  (4)
#define ABB_RX_C_DIG_3_rx_comp_sel_c_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_1_UNION
 结构说明  : RX_TDS_DIG_1 寄存器结构定义。地址偏移量:0x409，初值:0x11，宽度:8
 寄存器说明: RX TDS模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_tds    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                          0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                          1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0      : 3;  /* bit[1-3]: 保留 */
        unsigned long  rx_mode_dig_tds : 3;  /* bit[4-6]: RX通道模式控制：
                                                          000：2G_A(默认)
                                                          001：3G_SC/TDS_B/4G_C
                                                          010：4G
                                                          011：3G_DC/4G_B
                                                          100：TDS
                                                          101：CDMA
                                                          110：CA
                                                          111：2G_B */
        unsigned long  reserved_1      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_1_UNION;
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_START     (0)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_END       (0)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_START  (4)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_2_UNION
 结构说明  : RX_TDS_DIG_2 寄存器结构定义。地址偏移量:0x40A，初值:0xD3，宽度:8
 寄存器说明: RX TDS模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_tds      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  rxb_pd_tds      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  gain_sel_tds    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                          00：gain为0.5(默认)
                                                          01：gain为0.75
                                                          10：gain为0.85
                                                          11：Reserved */
        unsigned long  rx_comp_bp_tds  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                          0：不bypass
                                                          1：bypass(默认) */
        unsigned long  rx_clk_inv_tds  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                          0：正常
                                                          1：反向 */
        unsigned long  rx_flush_en_tds : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                          0：不使能
                                                          1：使能 */
        unsigned long  reserved        : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_2_UNION;
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_START       (0)
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_END         (0)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_START       (1)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_END         (1)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_START     (2)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_END       (3)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_START   (4)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_END     (4)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_START   (5)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_END     (5)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_START  (6)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_3_UNION
 结构说明  : RX_TDS_DIG_3 寄存器结构定义。地址偏移量:0x40B，初值:0x10，宽度:8
 寄存器说明: RX TDS模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_tds : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                          2'b00：2560chip。(W模默认)
                                                          2'b01：512chip。
                                                          2'b10：1024chip。(X模默认)
                                                          2'b11：2048chip。 */
        unsigned long  reserved_0      : 2;  /* bit[2-3]: 保留 */
        unsigned long  rx_comp_sel_tds : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                          000：系数不固定，由寄存器配置；
                                                          001：固定系数1；
                                                          010：固定系数2；
                                                          011：固定系数3；
                                                          100：固定系数4；
                                                          101：固定系数5；
                                                          110：固定系数6；
                                                          111：固定系数7。 */
        unsigned long  reserved_1      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_3_UNION;
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_START  (0)
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_END    (1)
#define ABB_RX_TDS_DIG_3_rx_comp_sel_tds_START  (4)
#define ABB_RX_TDS_DIG_3_rx_comp_sel_tds_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RX_3G_DIG_1_UNION
 结构说明  : CH0_RX_3G_DIG_1 寄存器结构定义。地址偏移量:0x410，初值:0x11，宽度:8
 寄存器说明: RX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_hb_bp_3g    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch0_rx_mode_dig_3g : 3;  /* bit[4-6]: RX通道模式控制：
                                                             000：2G_A(默认)
                                                             001：3G_SC/TDS_B/4G_C
                                                             010：4G
                                                             011：3G_DC/4G_B
                                                             100：TDS
                                                             101：CDMA
                                                             110：CA
                                                             111：2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_1_UNION;
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_hb_bp_3g_START     (0)
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_hb_bp_3g_END       (0)
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_mode_dig_3g_START  (4)
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_mode_dig_3g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RX_3G_DIG_2_UNION
 结构说明  : CH0_RX_3G_DIG_2 寄存器结构定义。地址偏移量:0x411，初值:0x03，宽度:8
 寄存器说明: RX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_3g      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch0_rxb_pd_3g      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch0_gain_sel_3g    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                             00：gain为0.5(默认)
                                                             01：gain为0.75
                                                             10：gain为0.85
                                                             11：Reserved */
        unsigned long  ch0_rx_comp_bp_3g  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch0_rx_clk_inv_3g  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                             0：正常
                                                             1：反向 */
        unsigned long  ch0_rx_flush_en_3g : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  reserved           : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_2_UNION;
#define ABB_CH0_RX_3G_DIG_2_ch0_rxa_pd_3g_START       (0)
#define ABB_CH0_RX_3G_DIG_2_ch0_rxa_pd_3g_END         (0)
#define ABB_CH0_RX_3G_DIG_2_ch0_rxb_pd_3g_START       (1)
#define ABB_CH0_RX_3G_DIG_2_ch0_rxb_pd_3g_END         (1)
#define ABB_CH0_RX_3G_DIG_2_ch0_gain_sel_3g_START     (2)
#define ABB_CH0_RX_3G_DIG_2_ch0_gain_sel_3g_END       (3)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_comp_bp_3g_START   (4)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_comp_bp_3g_END     (4)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_clk_inv_3g_START   (5)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_clk_inv_3g_END     (5)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_flush_en_3g_START  (6)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_flush_en_3g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RX_3G_DIG_3_UNION
 结构说明  : CH0_RX_3G_DIG_3 寄存器结构定义。地址偏移量:0x412，初值:0x10，宽度:8
 寄存器说明: RX 3G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_blk_len_sel_3g : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                             2'b00：2560chip。(W模默认)
                                                             2'b01：512chip。
                                                             2'b10：1024chip。(X模默认)
                                                             2'b11：2048chip。 */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch0_rx_comp_sel_3g : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                             000：系数不固定，由寄存器配置；
                                                             001：固定系数1；
                                                             010：固定系数2；
                                                             011：固定系数3；
                                                             100：固定系数4；
                                                             101：固定系数5；
                                                             110：固定系数6；
                                                             111：固定系数7。 */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_3_UNION;
#define ABB_CH0_RX_3G_DIG_3_ch0_blk_len_sel_3g_START  (0)
#define ABB_CH0_RX_3G_DIG_3_ch0_blk_len_sel_3g_END    (1)
#define ABB_CH0_RX_3G_DIG_3_ch0_rx_comp_sel_3g_START  (4)
#define ABB_CH0_RX_3G_DIG_3_ch0_rx_comp_sel_3g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RX_3G_DIG_1_UNION
 结构说明  : CH1_RX_3G_DIG_1 寄存器结构定义。地址偏移量:0x413，初值:0x11，宽度:8
 寄存器说明: RX 3G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_hb_bp_3g    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch1_rx_mode_dig_3g : 3;  /* bit[4-6]: RX通道模式控制：
                                                             000：2G_A(默认)
                                                             001：3G_SC/TDS_B/4G_C
                                                             010：4G
                                                             011：3G_DC/4G_B
                                                             100：TDS
                                                             101：CDMA
                                                             110：CA
                                                             111：2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_1_UNION;
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_hb_bp_3g_START     (0)
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_hb_bp_3g_END       (0)
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_mode_dig_3g_START  (4)
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_mode_dig_3g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RX_3G_DIG_2_UNION
 结构说明  : CH1_RX_3G_DIG_2 寄存器结构定义。地址偏移量:0x414，初值:0x03，宽度:8
 寄存器说明: RX 3G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_3g      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch1_rxb_pd_3g      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch1_gain_sel_3g    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                             00：gain为0.5(默认)
                                                             01：gain为0.75
                                                             10：gain为0.85
                                                             11：Reserved */
        unsigned long  ch1_rx_comp_bp_3g  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch1_rx_clk_inv_3g  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                             0：正常
                                                             1：反向 */
        unsigned long  ch1_rx_flush_en_3g : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  reserved           : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_2_UNION;
#define ABB_CH1_RX_3G_DIG_2_ch1_rxa_pd_3g_START       (0)
#define ABB_CH1_RX_3G_DIG_2_ch1_rxa_pd_3g_END         (0)
#define ABB_CH1_RX_3G_DIG_2_ch1_rxb_pd_3g_START       (1)
#define ABB_CH1_RX_3G_DIG_2_ch1_rxb_pd_3g_END         (1)
#define ABB_CH1_RX_3G_DIG_2_ch1_gain_sel_3g_START     (2)
#define ABB_CH1_RX_3G_DIG_2_ch1_gain_sel_3g_END       (3)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_comp_bp_3g_START   (4)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_comp_bp_3g_END     (4)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_clk_inv_3g_START   (5)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_clk_inv_3g_END     (5)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_flush_en_3g_START  (6)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_flush_en_3g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RX_3G_DIG_3_UNION
 结构说明  : CH1_RX_3G_DIG_3 寄存器结构定义。地址偏移量:0x415，初值:0x10，宽度:8
 寄存器说明: RX 3G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_blk_len_sel_3g : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                             2'b00：2560chip。(W模默认)
                                                             2'b01：512chip。
                                                             2'b10：1024chip。(X模默认)
                                                             2'b11：2048chip。 */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch1_rx_comp_sel_3g : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                             000：系数不固定，由寄存器配置；
                                                             001：固定系数1；
                                                             010：固定系数2；
                                                             011：固定系数3；
                                                             100：固定系数4；
                                                             101：固定系数5；
                                                             110：固定系数6；
                                                             111：固定系数7。 */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_3_UNION;
#define ABB_CH1_RX_3G_DIG_3_ch1_blk_len_sel_3g_START  (0)
#define ABB_CH1_RX_3G_DIG_3_ch1_blk_len_sel_3g_END    (1)
#define ABB_CH1_RX_3G_DIG_3_ch1_rx_comp_sel_3g_START  (4)
#define ABB_CH1_RX_3G_DIG_3_ch1_rx_comp_sel_3g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RX_4G_DIG_1_UNION
 结构说明  : CH0_RX_4G_DIG_1 寄存器结构定义。地址偏移量:0x440，初值:0x20，宽度:8
 寄存器说明: RX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_hb_bp_4g    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch0_rx_mode_dig_4g : 3;  /* bit[4-6]: RX通道模式控制：
                                                             000：2G_A(默认)
                                                             001：3G_SC/TDS_B/4G_C
                                                             010：4G
                                                             011：3G_DC/4G_B
                                                             100：TDS
                                                             101：CDMA
                                                             110：CA
                                                             111：2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_4G_DIG_1_UNION;
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_hb_bp_4g_START     (0)
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_hb_bp_4g_END       (0)
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_mode_dig_4g_START  (4)
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_mode_dig_4g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RX_4G_DIG_2_UNION
 结构说明  : CH0_RX_4G_DIG_2 寄存器结构定义。地址偏移量:0x441，初值:0x03，宽度:8
 寄存器说明: RX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_4g      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch0_rxb_pd_4g      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch0_gain_sel_4g    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                             00：gain为0.5(默认)
                                                             01：gain为0.75
                                                             10：gain为0.85
                                                             11：Reserved */
        unsigned long  ch0_rx_comp_bp_4g  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch0_rx_clk_inv_4g  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                             0：正常
                                                             1：反向 */
        unsigned long  ch0_rx_flush_en_4g : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  reserved           : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_4G_DIG_2_UNION;
#define ABB_CH0_RX_4G_DIG_2_ch0_rxa_pd_4g_START       (0)
#define ABB_CH0_RX_4G_DIG_2_ch0_rxa_pd_4g_END         (0)
#define ABB_CH0_RX_4G_DIG_2_ch0_rxb_pd_4g_START       (1)
#define ABB_CH0_RX_4G_DIG_2_ch0_rxb_pd_4g_END         (1)
#define ABB_CH0_RX_4G_DIG_2_ch0_gain_sel_4g_START     (2)
#define ABB_CH0_RX_4G_DIG_2_ch0_gain_sel_4g_END       (3)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_comp_bp_4g_START   (4)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_comp_bp_4g_END     (4)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_clk_inv_4g_START   (5)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_clk_inv_4g_END     (5)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_flush_en_4g_START  (6)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_flush_en_4g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH0_RX_4G_DIG_3_UNION
 结构说明  : CH0_RX_4G_DIG_3 寄存器结构定义。地址偏移量:0x442，初值:0x10，宽度:8
 寄存器说明: RX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_blk_len_sel_4g : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                             2'b00：2560chip。(W模默认)
                                                             2'b01：512chip。
                                                             2'b10：1024chip。(X模默认)
                                                             2'b11：2048chip。 */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch0_rx_comp_sel_4g : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                             000：系数不固定，由寄存器配置；
                                                             001：固定系数1；
                                                             010：固定系数2；
                                                             011：固定系数3；
                                                             100：固定系数4；
                                                             101：固定系数5；
                                                             110：固定系数6；
                                                             111：固定系数7。 */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_4G_DIG_3_UNION;
#define ABB_CH0_RX_4G_DIG_3_ch0_blk_len_sel_4g_START  (0)
#define ABB_CH0_RX_4G_DIG_3_ch0_blk_len_sel_4g_END    (1)
#define ABB_CH0_RX_4G_DIG_3_ch0_rx_comp_sel_4g_START  (4)
#define ABB_CH0_RX_4G_DIG_3_ch0_rx_comp_sel_4g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RX_4G_DIG_1_UNION
 结构说明  : CH1_RX_4G_DIG_1 寄存器结构定义。地址偏移量:0x443，初值:0x20，宽度:8
 寄存器说明: RX 4G模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_hb_bp_4g    : 1;  /* bit[0]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch1_rx_mode_dig_4g : 3;  /* bit[4-6]: RX通道模式控制：
                                                             000：2G_A(默认)
                                                             001：3G_SC/TDS_B/4G_C
                                                             010：4G
                                                             011：3G_DC/4G_B
                                                             100：TDS
                                                             101：CDMA
                                                             110：CA
                                                             111：2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_4G_DIG_1_UNION;
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_hb_bp_4g_START     (0)
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_hb_bp_4g_END       (0)
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_mode_dig_4g_START  (4)
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_mode_dig_4g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RX_4G_DIG_2_UNION
 结构说明  : CH1_RX_4G_DIG_2 寄存器结构定义。地址偏移量:0x444，初值:0x03，宽度:8
 寄存器说明: RX 4G模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_4g      : 1;  /* bit[0]  : RXA通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxa_pd)|XX_RXA_EN = 1时工作，否则关闭 */
        unsigned long  ch1_rxb_pd_4g      : 1;  /* bit[1]  : RXB通道CLOCK GATING控制：
                                                             0：不CLOCK GATING
                                                             1：CLOCK GATING(默认)
                                                             (!rxb_pd)|XX_RXB_EN = 1时工作，否则关闭 */
        unsigned long  ch1_gain_sel_4g    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                             00：gain为0.5(默认)
                                                             01：gain为0.75
                                                             10：gain为0.85
                                                             11：Reserved */
        unsigned long  ch1_rx_comp_bp_4g  : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                             0：不bypass(默认)
                                                             1：bypass */
        unsigned long  ch1_rx_clk_inv_4g  : 1;  /* bit[5]  : RX通道随路时钟RX_CLK反向使能：
                                                             0：正常
                                                             1：反向 */
        unsigned long  ch1_rx_flush_en_4g : 1;  /* bit[6]  : RX通道FLUSH使能：
                                                             0：不使能
                                                             1：使能 */
        unsigned long  reserved           : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_4G_DIG_2_UNION;
#define ABB_CH1_RX_4G_DIG_2_ch1_rxa_pd_4g_START       (0)
#define ABB_CH1_RX_4G_DIG_2_ch1_rxa_pd_4g_END         (0)
#define ABB_CH1_RX_4G_DIG_2_ch1_rxb_pd_4g_START       (1)
#define ABB_CH1_RX_4G_DIG_2_ch1_rxb_pd_4g_END         (1)
#define ABB_CH1_RX_4G_DIG_2_ch1_gain_sel_4g_START     (2)
#define ABB_CH1_RX_4G_DIG_2_ch1_gain_sel_4g_END       (3)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_comp_bp_4g_START   (4)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_comp_bp_4g_END     (4)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_clk_inv_4g_START   (5)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_clk_inv_4g_END     (5)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_flush_en_4g_START  (6)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_flush_en_4g_END    (6)


/*****************************************************************************
 结构名    : ABB_CH1_RX_4G_DIG_3_UNION
 结构说明  : CH1_RX_4G_DIG_3 寄存器结构定义。地址偏移量:0x445，初值:0x10，宽度:8
 寄存器说明: RX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_blk_len_sel_4g : 2;  /* bit[0-1]: W/X模Block检测测量时间。（除W/X模外，其他模式该寄存器不生效）
                                                             2'b00：2560chip。(W模默认)
                                                             2'b01：512chip。
                                                             2'b10：1024chip。(X模默认)
                                                             2'b11：2048chip。 */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch1_rx_comp_sel_4g : 3;  /* bit[4-6]: RX通道补偿滤波器补偿系数固定控制：
                                                             000：系数不固定，由寄存器配置；
                                                             001：固定系数1；
                                                             010：固定系数2；
                                                             011：固定系数3；
                                                             100：固定系数4；
                                                             101：固定系数5；
                                                             110：固定系数6；
                                                             111：固定系数7。 */
        unsigned long  reserved_1         : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_4G_DIG_3_UNION;
#define ABB_CH1_RX_4G_DIG_3_ch1_blk_len_sel_4g_START  (0)
#define ABB_CH1_RX_4G_DIG_3_ch1_blk_len_sel_4g_END    (1)
#define ABB_CH1_RX_4G_DIG_3_ch1_rx_comp_sel_4g_START  (4)
#define ABB_CH1_RX_4G_DIG_3_ch1_rx_comp_sel_4g_END    (6)


/*****************************************************************************
 结构名    : ABB_RX_EN_DELAY_UNION
 结构说明  : RX_EN_DELAY 寄存器结构定义。地址偏移量:0x470，初值:0x01，宽度:8
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
 结构名    : ABB_COMB_MODE_UNION
 结构说明  : COMB_MODE 寄存器结构定义。地址偏移量:0x471，初值:0x00，宽度:8
 寄存器说明: 模式寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_comb_mode : 1;  /* bit[0]  :  */
        unsigned long  reserved      : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_COMB_MODE_UNION;
#define ABB_COMB_MODE_ch0_comb_mode_START  (0)
#define ABB_COMB_MODE_ch0_comb_mode_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_RX_TESTMODE_UNION
 结构说明  : CH0_RX_TESTMODE 寄存器结构定义。地址偏移量:0x480，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_sw_rst   : 1;  /* bit[0]  : 数字部分RX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  ch0_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  ch0_rx_loop_sel : 2;  /* bit[2-3]:  */
        unsigned long  ch0_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved        : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_TESTMODE_UNION;
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_START    (0)
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_END      (0)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_START  (1)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_END    (1)
#define ABB_CH0_RX_TESTMODE_ch0_rx_loop_sel_START  (2)
#define ABB_CH0_RX_TESTMODE_ch0_rx_loop_sel_END    (3)
#define ABB_CH0_RX_TESTMODE_ch0_out_sel_START      (4)
#define ABB_CH0_RX_TESTMODE_ch0_out_sel_END        (5)


/*****************************************************************************
 结构名    : ABB_CH0_PLL_SEL_UNION
 结构说明  : CH0_PLL_SEL 寄存器结构定义。地址偏移量:0x481，初值:0x00，宽度:8
 寄存器说明: PLL选择寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_g_pll_sel   : 2;  /* bit[0-1]: G模PLL选择：
                                                          0：选择GPLL
                                                          1：选择SCPLL0
                                                          2：选择SCPLL1 */
        unsigned long  ch0_wtl_pll_sel : 1;  /* bit[2]  : WTL模PLL选择
                                                          0：选择SCPLL0
                                                          1：选择SCPLL1 */
        unsigned long  ch0_c1_pll_sel  : 1;  /* bit[3]  : C1模PLL选择
                                                          0：选择SCPLL1
                                                          1：选择SCPLL0 */
        unsigned long  reserved        : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_PLL_SEL_UNION;
#define ABB_CH0_PLL_SEL_ch0_g_pll_sel_START    (0)
#define ABB_CH0_PLL_SEL_ch0_g_pll_sel_END      (1)
#define ABB_CH0_PLL_SEL_ch0_wtl_pll_sel_START  (2)
#define ABB_CH0_PLL_SEL_ch0_wtl_pll_sel_END    (2)
#define ABB_CH0_PLL_SEL_ch0_c1_pll_sel_START   (3)
#define ABB_CH0_PLL_SEL_ch0_c1_pll_sel_END     (3)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_I_COEF2_UNION
 结构说明  : CH0_RXA_I_COEF2 寄存器结构定义。地址偏移量:0x486，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_c3_msb : 1;  /* bit[0]  : RXA通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF2_UNION;
#define ABB_CH0_RXA_I_COEF2_ch0_rxa_i_c3_msb_START  (0)
#define ABB_CH0_RXA_I_COEF2_ch0_rxa_i_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_RXA_Q_COEF2_UNION
 结构说明  : CH0_RXA_Q_COEF2 寄存器结构定义。地址偏移量:0x48C，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_c3_msb : 1;  /* bit[0]  : RXA通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF2_UNION;
#define ABB_CH0_RXA_Q_COEF2_ch0_rxa_q_c3_msb_START  (0)
#define ABB_CH0_RXA_Q_COEF2_ch0_rxa_q_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_I_COEF2_UNION
 结构说明  : CH0_RXB_I_COEF2 寄存器结构定义。地址偏移量:0x492，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_c3_msb : 1;  /* bit[0]  : RXB通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF2_UNION;
#define ABB_CH0_RXB_I_COEF2_ch0_rxb_i_c3_msb_START  (0)
#define ABB_CH0_RXB_I_COEF2_ch0_rxb_i_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_RXB_Q_COEF2_UNION
 结构说明  : CH0_RXB_Q_COEF2 寄存器结构定义。地址偏移量:0x498，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_c3_msb : 1;  /* bit[0]  : RXB通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF2_UNION;
#define ABB_CH0_RXB_Q_COEF2_ch0_rxb_q_c3_msb_START  (0)
#define ABB_CH0_RXB_Q_COEF2_ch0_rxb_q_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH0_REG_RXA_DCR_CFG_UNION
 结构说明  : CH0_REG_RXA_DCR_CFG 寄存器结构定义。地址偏移量:0x49C，初值:0x46，宽度:8
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
 结构说明  : CH0_REG_RXB_DCR_CFG 寄存器结构定义。地址偏移量:0x49D，初值:0x46，宽度:8
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
 结构说明  : CH0_REG_RX_DCR_CTRL 寄存器结构定义。地址偏移量:0x49E，初值:0x00，宽度:8
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
 结构说明  : CH0_RXA_BLOCKING 寄存器结构定义。地址偏移量:0x49F，初值:0x00，宽度:8
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
 结构说明  : CH0_RXB_BLOCKING 寄存器结构定义。地址偏移量:0x4A0，初值:0x00，宽度:8
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
 结构说明  : CH0_REG_RXA_DC_I_2 寄存器结构定义。地址偏移量:0x4A2，初值:0x00，宽度:8
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
 结构说明  : CH0_REG_RXA_DC_Q_2 寄存器结构定义。地址偏移量:0x4A4，初值:0x00，宽度:8
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
 结构说明  : CH0_REG_RXB_DC_I_2 寄存器结构定义。地址偏移量:0x4A6，初值:0x00，宽度:8
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
 结构说明  : CH0_REG_RXB_DC_Q_2 寄存器结构定义。地址偏移量:0x4A8，初值:0x00，宽度:8
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
 结构名    : ABB_CH0_FLUSH_CFG1_UNION
 结构说明  : CH0_FLUSH_CFG1 寄存器结构定义。地址偏移量:0x4AA，初值:0x40，宽度:8
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
 结构名    : ABB_CH0_RXAI_HB_GAIN_2_UNION
 结构说明  : CH0_RXAI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4AC，初值:0x02，宽度:8
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
 结构说明  : CH0_RXAQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4AE，初值:0x02，宽度:8
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
 结构说明  : CH0_RXBI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4B0，初值:0x02，宽度:8
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
 结构说明  : CH0_RXBQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4B2，初值:0x02，宽度:8
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
 结构名    : ABB_CH0_CTRL_UNION
 结构说明  : CH0_CTRL 寄存器结构定义。地址偏移量:0x4B3，初值:0x03，宽度:8
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
 结构名    : ABB_CH0_RX_LINE_SEL_UNION
 结构说明  : CH0_RX_LINE_SEL 寄存器结构定义。地址偏移量:0x4B4，初值:0x00，宽度:8
 寄存器说明: RX线控强制配置使能。
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
        unsigned long  reserved_0     : 1;  /* bit[2]: 保留 */
        unsigned long  reserved_1     : 1;  /* bit[3]: 保留 */
        unsigned long  ch0_rxa_en_cfg : 1;  /* bit[4]: RXA通道强配线控 */
        unsigned long  ch0_rxb_en_cfg : 1;  /* bit[5]: RXB通道强配线控 */
        unsigned long  reserved_2     : 1;  /* bit[6]: 保留 */
        unsigned long  reserved_3     : 1;  /* bit[7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_SEL_UNION;
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_sel_START  (0)
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_sel_END    (0)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_sel_START  (1)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_sel_END    (1)
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_cfg_START  (4)
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_cfg_END    (4)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_cfg_START  (5)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_cfg_END    (5)


/*****************************************************************************
 结构名    : ABB_CH0_RX_LINE_CFG_UNION
 结构说明  : CH0_RX_LINE_CFG 寄存器结构定义。地址偏移量:0x4B5，初值:0x00，宽度:8
 寄存器说明: RX模式线控强制配置。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: 线控信号CH0_RX_LINE_CTRL_MODE强制配置值
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模 */
        unsigned long  ch0_rx_line_ctrl_mode_sel : 1;  /* bit[3]  : 线控信号CH0_RX_LINE_CTRL_MODE强制配置使能 */
        unsigned long  reserved                  : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_CFG_UNION;
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_sel_START  (3)
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 结构名    : ABB_CH0_BLK_CFG_UNION
 结构说明  : CH0_BLK_CFG 寄存器结构定义。地址偏移量:0x4B6，初值:0x00，宽度:8
 寄存器说明: blk控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : 保留 */
        unsigned long  ch0_blk_en_cfg : 1;  /* bit[1]  : 线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值 */
        unsigned long  ch0_blk_en_sel : 1;  /* bit[2]  : 线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能 */
        unsigned long  reserved_1     : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_BLK_CFG_UNION;
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_START  (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_END    (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_START  (2)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_END    (2)


/*****************************************************************************
 结构名    : ABB_CH0_RX_LINE_RPT0_UNION
 结构说明  : CH0_RX_LINE_RPT0 寄存器结构定义。地址偏移量:0x4B7，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_rpt : 1;  /* bit[0]  : CH0_RXA_EN线控状态上报 */
        unsigned long  ch0_rxb_en_rpt : 1;  /* bit[1]  : CH0_RXB_EN线控状态上报 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_RPT0_UNION;
#define ABB_CH0_RX_LINE_RPT0_ch0_rxa_en_rpt_START  (0)
#define ABB_CH0_RX_LINE_RPT0_ch0_rxa_en_rpt_END    (0)
#define ABB_CH0_RX_LINE_RPT0_ch0_rxb_en_rpt_START  (1)
#define ABB_CH0_RX_LINE_RPT0_ch0_rxb_en_rpt_END    (1)


/*****************************************************************************
 结构名    : ABB_CH0_RX_LINE_RPT1_UNION
 结构说明  : CH0_RX_LINE_RPT1 寄存器结构定义。地址偏移量:0x4B8，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved                  : 3;  /* bit[0-2]: 保留 */
        unsigned long  ch0_rx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: CH0 RX_LINE_CTRL_MODE状态上报：
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  ch0_rxa_blk_en_rpt        : 1;  /* bit[6]  : CH0_RXA_BLK_EN线控状态上报 */
        unsigned long  ch0_rxb_blk_en_rpt        : 1;  /* bit[7]  : CH0_RXB_BLK_EN线控状态上报 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_RPT1_UNION;
#define ABB_CH0_RX_LINE_RPT1_ch0_rx_line_ctrl_mode_rpt_START  (3)
#define ABB_CH0_RX_LINE_RPT1_ch0_rx_line_ctrl_mode_rpt_END    (5)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxa_blk_en_rpt_START         (6)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxa_blk_en_rpt_END           (6)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxb_blk_en_rpt_START         (7)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxb_blk_en_rpt_END           (7)


/*****************************************************************************
 结构名    : ABB_CH0_RX_REG_DEBUG_DIG_UNION
 结构说明  : CH0_RX_REG_DEBUG_DIG 寄存器结构定义。地址偏移量:0x4B9，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_div_en_bp      : 1;  /* bit[0]  : RX分频器使能bypass控制
                                                                0：不bypass
                                                                1：bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch0_rx_sw_rst_num_cfg : 3;  /* bit[4-6]: 模式切换复位长度配置值，单位为8 cycles */
        unsigned long  ch0_rx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]：模式切换复位长度配置使能
                                                                0：不使能
                                                                1：使能 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_REG_DEBUG_DIG_UNION;
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_div_en_bp_START       (0)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_div_en_bp_END         (0)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_cfg_START  (4)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_cfg_END    (6)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_sel_START  (7)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_sel_END    (7)


/*****************************************************************************
 结构名    : ABB_CH1_RX_TESTMODE_UNION
 结构说明  : CH1_RX_TESTMODE 寄存器结构定义。地址偏移量:0x4C0，初值:0x04，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_sw_rst   : 1;  /* bit[0]  : 数字部分RX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  ch1_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  ch1_rx_loop_sel : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch1_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved        : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_TESTMODE_UNION;
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_START    (0)
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_END      (0)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_START  (1)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_END    (1)
#define ABB_CH1_RX_TESTMODE_ch1_rx_loop_sel_START  (2)
#define ABB_CH1_RX_TESTMODE_ch1_rx_loop_sel_END    (3)
#define ABB_CH1_RX_TESTMODE_ch1_out_sel_START      (4)
#define ABB_CH1_RX_TESTMODE_ch1_out_sel_END        (5)


/*****************************************************************************
 结构名    : ABB_CH1_PLL_SEL_UNION
 结构说明  : CH1_PLL_SEL 寄存器结构定义。地址偏移量:0x4C1，初值:0x00，宽度:8
 寄存器说明: PLL选择寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_g_pll_sel   : 2;  /* bit[0-1]: G模PLL选择：
                                                          0：选择GPLL
                                                          1：选择SCPLL0
                                                          2：选择SCPLL1 */
        unsigned long  ch1_wtl_pll_sel : 1;  /* bit[2]  : WTL模PLL选择
                                                          0：选择SCPLL0
                                                          1：选择SCPLL1 */
        unsigned long  ch1_c1_pll_sel  : 1;  /* bit[3]  : C1模PLL选择
                                                          0：选择SCPLL1
                                                          1：选择SCPLL0 */
        unsigned long  reserved        : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_PLL_SEL_UNION;
#define ABB_CH1_PLL_SEL_ch1_g_pll_sel_START    (0)
#define ABB_CH1_PLL_SEL_ch1_g_pll_sel_END      (1)
#define ABB_CH1_PLL_SEL_ch1_wtl_pll_sel_START  (2)
#define ABB_CH1_PLL_SEL_ch1_wtl_pll_sel_END    (2)
#define ABB_CH1_PLL_SEL_ch1_c1_pll_sel_START   (3)
#define ABB_CH1_PLL_SEL_ch1_c1_pll_sel_END     (3)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_I_COEF2_UNION
 结构说明  : CH1_RXA_I_COEF2 寄存器结构定义。地址偏移量:0x4C6，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_i_c3_msb : 1;  /* bit[0]  : RXA通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF2_UNION;
#define ABB_CH1_RXA_I_COEF2_ch1_rxa_i_c3_msb_START  (0)
#define ABB_CH1_RXA_I_COEF2_ch1_rxa_i_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH1_RXA_Q_COEF2_UNION
 结构说明  : CH1_RXA_Q_COEF2 寄存器结构定义。地址偏移量:0x4CC，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_q_c3_msb : 1;  /* bit[0]  : RXA通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF2_UNION;
#define ABB_CH1_RXA_Q_COEF2_ch1_rxa_q_c3_msb_START  (0)
#define ABB_CH1_RXA_Q_COEF2_ch1_rxa_q_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH1_RXB_I_COEF2_UNION
 结构说明  : CH1_RXB_I_COEF2 寄存器结构定义。地址偏移量:0x4D2，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_i_c3_msb : 1;  /* bit[0]  : RXB通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF2_UNION;
#define ABB_CH1_RXB_I_COEF2_ch1_rxb_i_c3_msb_START  (0)
#define ABB_CH1_RXB_I_COEF2_ch1_rxb_i_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH1_RXB_Q_COEF2_UNION
 结构说明  : CH1_RXB_Q_COEF2 寄存器结构定义。地址偏移量:0x4D8，初值:0x01，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_q_c3_msb : 1;  /* bit[0]  : RXB通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF2_UNION;
#define ABB_CH1_RXB_Q_COEF2_ch1_rxb_q_c3_msb_START  (0)
#define ABB_CH1_RXB_Q_COEF2_ch1_rxb_q_c3_msb_END    (0)


/*****************************************************************************
 结构名    : ABB_CH1_REG_RXA_DCR_CFG_UNION
 结构说明  : CH1_REG_RXA_DCR_CFG 寄存器结构定义。地址偏移量:0x4DC，初值:0x46，宽度:8
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
 结构说明  : CH1_REG_RXB_DCR_CFG 寄存器结构定义。地址偏移量:0x4DD，初值:0x46，宽度:8
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
 结构说明  : CH1_REG_RX_DCR_CTRL 寄存器结构定义。地址偏移量:0x4DE，初值:0x00，宽度:8
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
 结构说明  : CH1_RXA_BLOCKING 寄存器结构定义。地址偏移量:0x4DF，初值:0x00，宽度:8
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
 结构说明  : CH1_RXB_BLOCKING 寄存器结构定义。地址偏移量:0x4E0，初值:0x00，宽度:8
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
 结构说明  : CH1_REG_RXA_DC_I_2 寄存器结构定义。地址偏移量:0x4E2，初值:0x00，宽度:8
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
 结构说明  : CH1_REG_RXA_DC_Q_2 寄存器结构定义。地址偏移量:0x4E4，初值:0x00，宽度:8
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
 结构说明  : CH1_REG_RXB_DC_I_2 寄存器结构定义。地址偏移量:0x4E6，初值:0x00，宽度:8
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
 结构说明  : CH1_REG_RXB_DC_Q_2 寄存器结构定义。地址偏移量:0x4E8，初值:0x00，宽度:8
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
 结构名    : ABB_CH1_FLUSH_CFG1_UNION
 结构说明  : CH1_FLUSH_CFG1 寄存器结构定义。地址偏移量:0x4EA，初值:0x40，宽度:8
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
 结构名    : ABB_CH1_RXAI_HB_GAIN_2_UNION
 结构说明  : CH1_RXAI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4EC，初值:0x02，宽度:8
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
 结构说明  : CH1_RXAQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4EE，初值:0x02，宽度:8
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
 结构说明  : CH1_RXBI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4F0，初值:0x02，宽度:8
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
 结构说明  : CH1_RXBQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4F2，初值:0x02，宽度:8
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
 结构名    : ABB_CH1_CTRL_UNION
 结构说明  : CH1_CTRL 寄存器结构定义。地址偏移量:0x4F3，初值:0x03，宽度:8
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
 结构名    : ABB_CH1_RX_LINE_SEL_UNION
 结构说明  : CH1_RX_LINE_SEL 寄存器结构定义。地址偏移量:0x4F4，初值:0x00，宽度:8
 寄存器说明: 线控强制配置使能。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_sel : 1;  /* bit[0]  : RXA通道线控选择强配使能
                                                         0：选择线控使能
                                                         1：选择强配使能 */
        unsigned long  ch1_rxb_en_sel : 1;  /* bit[1]  : RXB通道线控选择强配使能
                                                         0：选择线控使能
                                                         1：选择强配使能 */
        unsigned long  reserved_0     : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch1_rxa_en_cfg : 1;  /* bit[4]  : RXA通道强配线控 */
        unsigned long  ch1_rxb_en_cfg : 1;  /* bit[5]  : RXB通道强配线控 */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_SEL_UNION;
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_sel_START  (0)
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_sel_END    (0)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_sel_START  (1)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_sel_END    (1)
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_cfg_START  (4)
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_cfg_END    (4)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_cfg_START  (5)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_cfg_END    (5)


/*****************************************************************************
 结构名    : ABB_CH1_RX_LINE_CFG_UNION
 结构说明  : CH1_RX_LINE_CFG 寄存器结构定义。地址偏移量:0x4F5，初值:0x00，宽度:8
 寄存器说明: 模式线控强制配置。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: 线控信号CH1_RX_LINE_CTRL_MODE强制配置值
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模 */
        unsigned long  ch1_rx_line_ctrl_mode_sel : 1;  /* bit[3]  : 线控信号CH1_RX_LINE_CTRL_MODE强制配置使能 */
        unsigned long  reserved                  : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_CFG_UNION;
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_sel_START  (3)
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 结构名    : ABB_CH1_BLK_CFG_UNION
 结构说明  : CH1_BLK_CFG 寄存器结构定义。地址偏移量:0x4F6，初值:0x00，宽度:8
 寄存器说明: blk控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : 保留 */
        unsigned long  ch1_blk_en_cfg : 1;  /* bit[1]  : 线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值 */
        unsigned long  ch1_blk_en_sel : 1;  /* bit[2]  : 线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能 */
        unsigned long  reserved_1     : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_BLK_CFG_UNION;
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_START  (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_END    (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_START  (2)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_END    (2)


/*****************************************************************************
 结构名    : ABB_CH1_RX_LINE_RPT0_UNION
 结构说明  : CH1_RX_LINE_RPT0 寄存器结构定义。地址偏移量:0x4F7，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_rpt : 1;  /* bit[0]  : CH1_RXA_EN线控状态上报 */
        unsigned long  ch1_rxb_en_rpt : 1;  /* bit[1]  : CH1_RXB_EN线控状态上报 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_RPT0_UNION;
#define ABB_CH1_RX_LINE_RPT0_ch1_rxa_en_rpt_START  (0)
#define ABB_CH1_RX_LINE_RPT0_ch1_rxa_en_rpt_END    (0)
#define ABB_CH1_RX_LINE_RPT0_ch1_rxb_en_rpt_START  (1)
#define ABB_CH1_RX_LINE_RPT0_ch1_rxb_en_rpt_END    (1)


/*****************************************************************************
 结构名    : ABB_CH1_RX_LINE_RPT1_UNION
 结构说明  : CH1_RX_LINE_RPT1 寄存器结构定义。地址偏移量:0x4F8，初值:0x00，宽度:8
 寄存器说明: 线控状态上报寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved                  : 3;  /* bit[0-2]: 保留 */
        unsigned long  ch1_rx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: CH1 RX_LINE_CTRL_MODE状态上报：
                                                                    0：IDLE
                                                                    1：G模
                                                                    2：W模
                                                                    3：LTE模
                                                                    4：TDS模
                                                                    5：X模
                                                                    others：IDLE */
        unsigned long  ch1_rxa_blk_en_rpt        : 1;  /* bit[6]  : CH1_RXA_BLK_EN线控状态上报 */
        unsigned long  ch1_rxb_blk_en_rpt        : 1;  /* bit[7]  : CH1_RXB_BLK_EN线控状态上报 */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_RPT1_UNION;
#define ABB_CH1_RX_LINE_RPT1_ch1_rx_line_ctrl_mode_rpt_START  (3)
#define ABB_CH1_RX_LINE_RPT1_ch1_rx_line_ctrl_mode_rpt_END    (5)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxa_blk_en_rpt_START         (6)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxa_blk_en_rpt_END           (6)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxb_blk_en_rpt_START         (7)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxb_blk_en_rpt_END           (7)


/*****************************************************************************
 结构名    : ABB_CH1_RX_REG_DEBUG_DIG_UNION
 结构说明  : CH1_RX_REG_DEBUG_DIG 寄存器结构定义。地址偏移量:0x4F9，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_div_en_bp      : 1;  /* bit[0]  : RX分频器使能bypass控制
                                                                0：不bypass
                                                                1：bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: 保留 */
        unsigned long  ch1_rx_sw_rst_num_cfg : 3;  /* bit[4-6]: 模式切换复位长度配置值，单位为8 cycles */
        unsigned long  ch1_rx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]：模式切换复位长度配置使能
                                                                0：不使能
                                                                1：使能 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_REG_DEBUG_DIG_UNION;
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_div_en_bp_START       (0)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_div_en_bp_END         (0)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_cfg_START  (4)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_cfg_END    (6)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_sel_START  (7)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_sel_END    (7)


/***======================================================================***
                     (4/4) register_define_abb_ana
 ***======================================================================***/
/*****************************************************************************
 结构名    : ABB_SCPLL0_LOCK_CTRL_UNION
 结构说明  : SCPLL0_LOCK_CTRL 寄存器结构定义。地址偏移量:0x800，初值:0x18，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_en      : 1;  /* bit[0]  : SCPLL0使能信号。用于通过CFG接口配置打开scpll0。 */
        unsigned long  scpll0_time    : 3;  /* bit[1-3]: SCPLL0时钟稳定等待时间配置，计数时钟为19.2M：
                                                         000：SCPLL0开启10us后时钟稳定；
                                                         001：SCPLL0开启20us后时钟稳定；
                                                         010：SCPLL0开启50us后时钟稳定；
                                                         011：SCPLL0开启75us后时钟稳定；
                                                         100：SCPLL0开启100us后时钟稳定；
                                                         101：SCPLL0开启115us后时钟稳定；
                                                         110：SCPLL0开启125us后时钟稳定；
                                                         default：100us */
        unsigned long  scpll0_gate_en : 1;  /* bit[4]  : SCPLL0门控使能信号。 */
        unsigned long  scpll0_timeout : 1;  /* bit[5]  : SCPLL0稳定指示。0表示SCPLL0未稳定；1表示SCPLL0稳定。SCPLL0稳定后有时钟输出。 */
        unsigned long  scpll0_lock    : 1;  /* bit[6]  : SCPLL0锁定指示。 */
        unsigned long  reserved       : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_LOCK_CTRL_UNION;
#define ABB_SCPLL0_LOCK_CTRL_scpll0_en_START       (0)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_en_END         (0)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_time_START     (1)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_time_END       (3)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_gate_en_START  (4)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_gate_en_END    (4)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_timeout_START  (5)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_timeout_END    (5)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_lock_START     (6)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_lock_END       (6)


/*****************************************************************************
 结构名    : ABB_SCPLL0_FBDIV_H_UNION
 结构说明  : SCPLL0_FBDIV_H 寄存器结构定义。地址偏移量:0x803，初值:0x00，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_fbdiv_h : 4;  /* bit[0-3]: PLL反馈分频因子fbdiv[11:0]的高4bit； */
        unsigned long  reserved       : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_FBDIV_H_UNION;
#define ABB_SCPLL0_FBDIV_H_scpll0_fbdiv_h_START  (0)
#define ABB_SCPLL0_FBDIV_H_scpll0_fbdiv_h_END    (3)


/*****************************************************************************
 结构名    : ABB_SCPLL0_REFDIV_UNION
 结构说明  : SCPLL0_REFDIV 寄存器结构定义。地址偏移量:0x804，初值:0x01，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_refdiv : 6;  /* bit[0-5]: PLL参考分频因子refdiv[5:0]，默认值为1。 */
        unsigned long  reserved      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_REFDIV_UNION;
#define ABB_SCPLL0_REFDIV_scpll0_refdiv_START  (0)
#define ABB_SCPLL0_REFDIV_scpll0_refdiv_END    (5)


/*****************************************************************************
 结构名    : ABB_SCPLL0_CFG_UPDATE_UNION
 结构说明  : SCPLL0_CFG_UPDATE 寄存器结构定义。地址偏移量:0x809，初值:0x00，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_cfg_update : 1;  /* bit[0]  : SCPLL0参数配置更新指示。
                                                            scpll0_en打开后，软件配置完scpll0_postdiv，scpll0_fbdiv，scpll0_frac参数，再配置scpll0_sfg_update，参数同时更新；scpll0_en不打开时，配置参数立即更新，不需要配置scpll0_sfg_update。 */
        unsigned long  reserved          : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_CFG_UPDATE_UNION;
#define ABB_SCPLL0_CFG_UPDATE_scpll0_cfg_update_START  (0)
#define ABB_SCPLL0_CFG_UPDATE_scpll0_cfg_update_END    (0)


/*****************************************************************************
 结构名    : ABB_SCPLL1_LOCK_CTRL_UNION
 结构说明  : SCPLL1_LOCK_CTRL 寄存器结构定义。地址偏移量:0x80A，初值:0x18，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_en      : 1;  /* bit[0]  : SCPLL1使能信号。用于通过CFG接口配置打开scpll1。 */
        unsigned long  scpll1_time    : 3;  /* bit[1-3]: SCPLL1时钟稳定等待时间配置，计数时钟为19.2M：
                                                         000：SCPLL1开启10us后时钟稳定；
                                                         001：SCPLL1开启20us后时钟稳定；
                                                         010：SCPLL1开启50us后时钟稳定；
                                                         011：SCPLL1开启75us后时钟稳定；
                                                         100：SCPLL1开启100us后时钟稳定；
                                                         101：SCPLL1开启115us后时钟稳定；
                                                         110：SCPLL1开启125us后时钟稳定；
                                                         default：100us */
        unsigned long  scpll1_gate_en : 1;  /* bit[4]  : SCPLL1门控使能信号。 */
        unsigned long  scpll1_timeout : 1;  /* bit[5]  : SCPLL1稳定指示。0表示SCPLL1未稳定；1表示SCPLL1稳定。SCPLL1稳定后有时钟输出。 */
        unsigned long  scpll1_lock    : 1;  /* bit[6]  : SCPLL1锁定指示。 */
        unsigned long  reserved       : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_LOCK_CTRL_UNION;
#define ABB_SCPLL1_LOCK_CTRL_scpll1_en_START       (0)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_en_END         (0)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_time_START     (1)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_time_END       (3)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_gate_en_START  (4)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_gate_en_END    (4)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_timeout_START  (5)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_timeout_END    (5)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_lock_START     (6)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_lock_END       (6)


/*****************************************************************************
 结构名    : ABB_SCPLL1_FBDIV_H_UNION
 结构说明  : SCPLL1_FBDIV_H 寄存器结构定义。地址偏移量:0x80D，初值:0x00，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_fbdiv_h : 4;  /* bit[0-3]: PLL反馈分频因子fbdiv[11:0]的高4bit； */
        unsigned long  reserved       : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_FBDIV_H_UNION;
#define ABB_SCPLL1_FBDIV_H_scpll1_fbdiv_h_START  (0)
#define ABB_SCPLL1_FBDIV_H_scpll1_fbdiv_h_END    (3)


/*****************************************************************************
 结构名    : ABB_SCPLL1_REFDIV_UNION
 结构说明  : SCPLL1_REFDIV 寄存器结构定义。地址偏移量:0x80E，初值:0x01，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_refdiv : 6;  /* bit[0-5]: PLL参考分频因子refdiv[5:0]，默认值为1。 */
        unsigned long  reserved      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_REFDIV_UNION;
#define ABB_SCPLL1_REFDIV_scpll1_refdiv_START  (0)
#define ABB_SCPLL1_REFDIV_scpll1_refdiv_END    (5)


/*****************************************************************************
 结构名    : ABB_SCPLL1_CFG_UPDATE_UNION
 结构说明  : SCPLL1_CFG_UPDATE 寄存器结构定义。地址偏移量:0x813，初值:0x00，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_cfg_update : 1;  /* bit[0]  : SCPLL1参数配置更新指示。
                                                            scpll1_en打开后，软件配置完scpll1_postdiv，scpll1_fbdiv，scpll1_frac参数，再配置scpll1_sfg_update，参数同时更新；scpll1_en不打开时，配置参数立即更新，不需要配置scpll1_sfg_update。 */
        unsigned long  reserved          : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_CFG_UPDATE_UNION;
#define ABB_SCPLL1_CFG_UPDATE_scpll1_cfg_update_START  (0)
#define ABB_SCPLL1_CFG_UPDATE_scpll1_cfg_update_END    (0)


/*****************************************************************************
 结构名    : ABB_GPLL0_GATE_TIME_UNION
 结构说明  : GPLL0_GATE_TIME 寄存器结构定义。地址偏移量:0x814，初值:0x12，宽度:8
 寄存器说明: GPLL输出时钟门控时间配置
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll0_en     : 1;  /* bit[0]  : GPLL使能 */
        unsigned long  gpll_time    : 3;  /* bit[1-3]: GPLL时钟稳定等待时间配置，计数时钟为19.2M：
                                                       000：GPLL开启10us后时钟稳定；
                                                       001：GPLL开启20us后时钟稳定；
                                                       010：GPLL开启50us后时钟稳定；
                                                       011：GPLL开启75us后时钟稳定；
                                                       100：GPLL开启100us后时钟稳定；
                                                       101：GPLL开启115us后时钟稳定；
                                                       110：GPLL1开启125us后时钟稳定；
                                                       default：20us */
        unsigned long  gpll_gate_en : 1;  /* bit[4]  : GPLL时钟门控功能使能，
                                                       0：gpll时钟门控功能关闭；
                                                       1：gpll时钟门控功能打开。 */
        unsigned long  gpll_timeout : 1;  /* bit[5]  : GPLL稳定指示。0表示GPLL未稳定；1表示GPLL稳定。GPLL稳定后有时钟输出。 */
        unsigned long  gpll_lock    : 1;  /* bit[6]  : GPLL锁定指示。 */
        unsigned long  reserved     : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPLL0_GATE_TIME_UNION;
#define ABB_GPLL0_GATE_TIME_gpll0_en_START      (0)
#define ABB_GPLL0_GATE_TIME_gpll0_en_END        (0)
#define ABB_GPLL0_GATE_TIME_gpll_time_START     (1)
#define ABB_GPLL0_GATE_TIME_gpll_time_END       (3)
#define ABB_GPLL0_GATE_TIME_gpll_gate_en_START  (4)
#define ABB_GPLL0_GATE_TIME_gpll_gate_en_END    (4)
#define ABB_GPLL0_GATE_TIME_gpll_timeout_START  (5)
#define ABB_GPLL0_GATE_TIME_gpll_timeout_END    (5)
#define ABB_GPLL0_GATE_TIME_gpll_lock_START     (6)
#define ABB_GPLL0_GATE_TIME_gpll_lock_END       (6)


/*****************************************************************************
 结构名    : ABB_GPL1L_GATE_TIME_UNION
 结构说明  : GPL1L_GATE_TIME 寄存器结构定义。地址偏移量:0x815，初值:0x00，宽度:8
 寄存器说明: GPLL输出时钟门控时间配置
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll1_en : 1;  /* bit[0]  : GPLL使能副卡 */
        unsigned long  reserved : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPL1L_GATE_TIME_UNION;
#define ABB_GPL1L_GATE_TIME_gpll1_en_START  (0)
#define ABB_GPL1L_GATE_TIME_gpll1_en_END    (0)




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
