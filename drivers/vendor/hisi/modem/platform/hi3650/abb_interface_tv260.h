/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phy_abb_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-09-21 15:03:14
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月21日
    作    者   : x00347325
    修改内容   : 从《ComstarTV260 ABB寄存器描述_合并版.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __ABB_INTERFACE_TV260_H__
#define __ABB_INTERFACE_TV260_H__
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
                     (1/1) register_define_abb
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
#define ABB_SCPLL0_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0x0)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7]:Reserved;
            [6:4]：PLL后分频因子postdiv2；默认值为1。
            [3]:Reserved;
            [2:0]：PLL后分频因子postdiv1；默认值为5。
   UNION结构 ：无 */
#define ABB_SCPLL0_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0x1)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7:0]：PLL反馈分频因子fbdiv[11:0]的低8bit；fbdiv[11:0]默认值为64.
   UNION结构 ：无 */
#define ABB_SCPLL0_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0x2)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:4]    保留
 bit[3:0]    PLL反馈分频因子fbdiv[11:0]的高4bit；
   UNION结构:  ABB_SCPLL0_FBDIV_H_UNION */
#define ABB_SCPLL0_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0x3)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:6]    保留
 bit[5:0]    PLL参考分频因子refdiv[5:0]，默认值为1。
   UNION结构:  ABB_SCPLL0_REFDIV_UNION */
#define ABB_SCPLL0_REFDIV_ADDR                        (ABB_BASE_ADDR + 0x4)

/* 寄存器说明：SC_PLL分频器控制寄存器
   详      述：[7:6]：Reserved；
            [5]：DACPD；默认值为0(打开)。
            [4]：PLL FOUT4PHASEPD控制，高有效；默认值1（关闭）。
            [3]：DSMPD；小数模式PD信号，默认值0（打开）。
            [2]：PLL 旁路控制；默认值0（PLL旁路功能bypass）。
            [1]：PLL FOUTPOSTDIVPD控制，高有效；默认值0（打开）。
            [0]：PLL FOUTVCOPD控制，高有效；默认值0（打开）。
   UNION结构 ：无 */
#define ABB_SCPLL0_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0x5)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[7:0]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL0_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x6)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[15:8]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL0_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x7)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[23:16]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL0_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x8)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7:1]    保留
 bit[0]      SCPLL0参数配置更新指示。
             scpll0_en打开后，软件配置完scpll0_postdiv，scpll0_fbdiv，scpll0_frac参数，再配置scpll0_sfg_update，参数同时更新；scpll0_en不打开时，配置参数立即更新，不需要配置scpll0_sfg_update。
   UNION结构:  ABB_SCPLL0_CFG_UPDATE_UNION */
#define ABB_SCPLL0_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x9)

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
#define ABB_SCPLL1_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0xA)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7]:Reserved;
            [6:4]：PLL后分频因子postdiv2；默认值为1。
            [3]:Reserved;
            [2:0]：PLL后分频因子postdiv1；默认值为5。
   UNION结构 ：无 */
#define ABB_SCPLL1_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0xB)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7:0]：PLL反馈分频因子fbdiv[11:0]的低8bit；fbdiv[11:0]默认值为64.
   UNION结构 ：无 */
#define ABB_SCPLL1_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0xC)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:4]    保留
 bit[3:0]    PLL反馈分频因子fbdiv[11:0]的高4bit；
   UNION结构:  ABB_SCPLL1_FBDIV_H_UNION */
#define ABB_SCPLL1_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0xD)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:6]    保留
 bit[5:0]    PLL参考分频因子refdiv[5:0]，默认值为1。
   UNION结构:  ABB_SCPLL1_REFDIV_UNION */
#define ABB_SCPLL1_REFDIV_ADDR                        (ABB_BASE_ADDR + 0xE)

/* 寄存器说明：SC_PLL分频器控制寄存器
   详      述：[7:6]：Reserved；
            [5]：DACPD；默认值为0(打开)。
            [4]：PLL FOUT4PHASEPD控制，高有效；默认值1（关闭）。
            [3]：DSMPD；小数模式PD信号，默认值0（打开）。
            [2]：PLL 旁路控制；默认值0（PLL旁路功能bypass）。
            [1]：PLL FOUTPOSTDIVPD控制，高有效；默认值0（打开）。
            [0]：PLL FOUTVCOPD控制，高有效；默认值0（打开）。
   UNION结构 ：无 */
#define ABB_SCPLL1_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0xF)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[7:0]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL1_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x10)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[15:8]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL1_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x11)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[23:16]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_SCPLL1_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x12)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7:1]    保留
 bit[0]      SCPLL1参数配置更新指示。
             scpll1_en打开后，软件配置完scpll1_postdiv，scpll1_fbdiv，scpll1_frac参数，再配置scpll1_sfg_update，参数同时更新；scpll1_en不打开时，配置参数立即更新，不需要配置scpll1_sfg_update。
   UNION结构:  ABB_SCPLL1_CFG_UPDATE_UNION */
#define ABB_SCPLL1_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x13)

/* 寄存器说明：GPLL输出时钟门控时间配置
 bit[7:6]    保留
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
             default：100us
 bit[0]
   UNION结构:  ABB_GPLL_GATE_TIME_UNION */
#define ABB_GPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x14)

/* 寄存器说明：WPLL输出时钟门控时间配置
 bit[7:6]    保留
 bit[5]      WPLL稳定指示。0表示WPLL未稳定；1表示WPLL稳定。WPLL稳定后有时钟输出。
 bit[4]      WPLL时钟门控功能使能，
             0：wpll时钟门控功能关闭；
             1：wpll时钟门控功能打开。
 bit[3:1]    WPLL时钟稳定等待时间配置，计数时钟为19.2M：
             000：WPLL开启10us后时钟稳定；
             001：WPLL开启20us后时钟稳定；
             010：WPLL开启50us后时钟稳定；
             011：WPLL开启75us后时钟稳定；
             100：WPLL开启100us后时钟稳定；
             101：WPLL开启115us后时钟稳定；
             110：WPLL1开启125us后时钟稳定；
             default：100us
 bit[0]
   UNION结构:  ABB_WPLL_GATE_TIME_UNION */
#define ABB_WPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x15)

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
#define ABB_TESTMODE_ADDR                             (ABB_BASE_ADDR + 0x16)

/* 寄存器说明：ABB数字部分复位信号
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_ABB_DIG_PWR_RST_UNION */
#define ABB_ABB_DIG_PWR_RST_ADDR                      (ABB_BASE_ADDR + 0x17)

/* 寄存器说明：数字调试寄存器。
 bit[7:2]    保留
 bit[1:0]    数字调试寄存器
             bit[0]：管脚CH0_CLK_52M输出时钟选择
             1：输出GPLL
             0：输出SCPLL0
   UNION结构:  ABB_CH0_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH0_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x18)

/* 寄存器说明：数字调试寄存器。
 bit[7:2]    保留
 bit[1:0]    数字调试寄存器
             bit[0]：管脚CH1_CLK_52M输出时钟选择
             1：输出GPLL
             0：输出SCPLL1
   UNION结构:  ABB_CH1_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH1_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x19)

/* 寄存器说明：ABB版本寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

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
#define ABB_BIST_CFG_1_ADDR                           (ABB_BASE_ADDR + 0x41)

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
#define ABB_BIST_CFG_2_ADDR                           (ABB_BASE_ADDR + 0x42)

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
#define ABB_BIST_CFG_3_ADDR                           (ABB_BASE_ADDR + 0x43)

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
#define ABB_BIST_CFG_4_ADDR                           (ABB_BASE_ADDR + 0x44)

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
#define ABB_BIST_CFG_5_ADDR                           (ABB_BASE_ADDR + 0x45)

/* 寄存器说明：BIST完成状态寄存器
 bit[7]      BIST所有启动的测试项是否通过，即未bypass的测试是否全部通过。
             0：未通过；
             1：通过。
 bit[6:1]    保留
 bit[0]      SNDR计算完成状态。
             0：没有完成；
             1：完成。
   UNION结构:  ABB_BIST_RPT_1_UNION */
#define ABB_BIST_RPT_1_ADDR                           (ABB_BASE_ADDR + 0x46)

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
#define ABB_BIST_RPT_2_ADDR                           (ABB_BASE_ADDR + 0x47)

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
#define ABB_BIST_RPT_3_ADDR                           (ABB_BASE_ADDR + 0x48)

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
#define ABB_BIST_RPT_4_ADDR                           (ABB_BASE_ADDR + 0x49)

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
#define ABB_BIST_RPT_5_ADDR                           (ABB_BASE_ADDR + 0x4A)

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
#define ABB_BIST_RPT_6_ADDR                           (ABB_BASE_ADDR + 0x4B)

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
#define ABB_BIST_RPT_7_ADDR                           (ABB_BASE_ADDR + 0x4C)

/* 寄存器说明：BIST结果上报寄存器
 bit[7:3]    保留
 bit[2:0]    I路dc上报值高位。
   UNION结构:  ABB_BIST_RPT_8_UNION */
#define ABB_BIST_RPT_8_ADDR                           (ABB_BASE_ADDR + 0x4D)

/* 寄存器说明：BIST结果上报寄存器
   详      述：I路dc上报值低位。
   UNION结构 ：无 */
#define ABB_BIST_RPT_9_ADDR                           (ABB_BASE_ADDR + 0x4E)

/* 寄存器说明：BIST结果上报寄存器
 bit[7:3]    保留
 bit[2:0]    Q路dc上报值高位。
   UNION结构:  ABB_BIST_RPT_10_UNION */
#define ABB_BIST_RPT_10_ADDR                          (ABB_BASE_ADDR + 0x4F)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Q路dc上报值低位。
   UNION结构 ：无 */
#define ABB_BIST_RPT_11_ADDR                          (ABB_BASE_ADDR + 0x50)

/* 寄存器说明：BIST结果上报寄存器
   详      述：I路信噪比上报高8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_12_ADDR                          (ABB_BASE_ADDR + 0x51)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Q路信噪比上报高8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_13_ADDR                          (ABB_BASE_ADDR + 0x52)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Gain_mismatch上报，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_14_ADDR                          (ABB_BASE_ADDR + 0x53)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Gain_error上报，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_15_ADDR                          (ABB_BASE_ADDR + 0x54)

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
#define ABB_BIST_RPT_16_ADDR                          (ABB_BASE_ADDR + 0x55)

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
#define ABB_BIST_RPT_17_ADDR                          (ABB_BASE_ADDR + 0x56)

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
#define ABB_BIST_RPT_18_ADDR                          (ABB_BASE_ADDR + 0x57)

/* 寄存器说明：BIST结果上报寄存器
   详      述：I路信噪比上报低8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_19_ADDR                          (ABB_BASE_ADDR + 0x58)

/* 寄存器说明：BIST结果上报寄存器
   详      述：Q路信噪比上报低8bit，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_RPT_20_ADDR                          (ABB_BASE_ADDR + 0x59)

/* 寄存器说明：BIST结果标准寄存器
 bit[7:6]    保留
 bit[5:0]    BIST DC达标下限高6bit，有符号数。
   UNION结构:  ABB_BIST_CFG_6_UNION */
#define ABB_BIST_CFG_6_ADDR                           (ABB_BASE_ADDR + 0x5A)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST DC达标下限低8bit，有符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_7_ADDR                           (ABB_BASE_ADDR + 0x5B)

/* 寄存器说明：BIST结果标准寄存器
 bit[7:6]    保留
 bit[5:0]    BIST DC达标上限高6bit，有符号数。
   UNION结构:  ABB_BIST_CFG_8_UNION */
#define ABB_BIST_CFG_8_ADDR                           (ABB_BASE_ADDR + 0x5C)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST DC达标上限低8bit，有符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_9_ADDR                           (ABB_BASE_ADDR + 0x5D)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain mismatch达标下限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_10_ADDR                          (ABB_BASE_ADDR + 0x5E)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain mismatch达标上限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_11_ADDR                          (ABB_BASE_ADDR + 0x5F)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain error达标下限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_12_ADDR                          (ABB_BASE_ADDR + 0x60)

/* 寄存器说明：BIST结果标准寄存器
   详      述：BIST gain error达标上限，无符号数。
   UNION结构 ：无 */
#define ABB_BIST_CFG_13_ADDR                          (ABB_BASE_ADDR + 0x61)

/* 寄存器说明：BIST SNDR 2G模式达标值
   详      述：BIST 2G模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_2G_0_ADDR                       (ABB_BASE_ADDR + 0x62)

/* 寄存器说明：BIST SNDR 2G模式达标值
   详      述：BIST 2G模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_2G_1_ADDR                       (ABB_BASE_ADDR + 0x63)

/* 寄存器说明：BIST SNDR 2G模式达标值
   详      述：BIST 2G模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_2G_2_ADDR                       (ABB_BASE_ADDR + 0x64)

/* 寄存器说明：BIST SNDR 3G模式达标值
   详      述：BIST 3G模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_3G_0_ADDR                       (ABB_BASE_ADDR + 0x65)

/* 寄存器说明：BIST SNDR 3G模式达标值
   详      述：BIST 3G模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_3G_1_ADDR                       (ABB_BASE_ADDR + 0x66)

/* 寄存器说明：BIST SNDR 3G模式达标值
   详      述：BIST 3G模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_3G_2_ADDR                       (ABB_BASE_ADDR + 0x67)

/* 寄存器说明：BIST SNDR TDS模式达标值
   详      述：BIST TDS模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_TDS_0_ADDR                      (ABB_BASE_ADDR + 0x68)

/* 寄存器说明：BIST SNDR TDS模式达标值
   详      述：BIST TDS模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_TDS_1_ADDR                      (ABB_BASE_ADDR + 0x69)

/* 寄存器说明：BIST SNDR TDS模式达标值
   详      述：BIST TDS模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_TDS_2_ADDR                      (ABB_BASE_ADDR + 0x6A)

/* 寄存器说明：BIST SNDR 4G模式达标值
   详      述：BIST 4G模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_4G_0_ADDR                       (ABB_BASE_ADDR + 0x6B)

/* 寄存器说明：BIST SNDR 4G模式达标值
   详      述：BIST 4G模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_4G_1_ADDR                       (ABB_BASE_ADDR + 0x6C)

/* 寄存器说明：BIST SNDR 4G模式达标值
   详      述：BIST 4G模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_4G_2_ADDR                       (ABB_BASE_ADDR + 0x6D)

/* 寄存器说明：BIST SNDR CDMA模式达标值
   详      述：BIST CDMA模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CDMA_0_ADDR                     (ABB_BASE_ADDR + 0x6E)

/* 寄存器说明：BIST SNDR CDMA模式达标值
   详      述：BIST CDMA模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CDMA_1_ADDR                     (ABB_BASE_ADDR + 0x6F)

/* 寄存器说明：BIST SNDR CDMA模式达标值
   详      述：BIST CDMA模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CDMA_2_ADDR                     (ABB_BASE_ADDR + 0x70)

/* 寄存器说明：BIST SNDR CA模式达标值
   详      述：BIST CA模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CA_0_ADDR                       (ABB_BASE_ADDR + 0x71)

/* 寄存器说明：BIST SNDR CA模式达标值
   详      述：BIST CA模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CA_1_ADDR                       (ABB_BASE_ADDR + 0x72)

/* 寄存器说明：BIST SNDR CA模式达标值
   详      述：BIST CA模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_CA_2_ADDR                       (ABB_BASE_ADDR + 0x73)

/* 寄存器说明：BIST SNDR ET0模式达标值
   详      述：BIST ET0模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET0_0_ADDR                      (ABB_BASE_ADDR + 0x74)

/* 寄存器说明：BIST SNDR ET0模式达标值
   详      述：BIST ET0模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET0_1_ADDR                      (ABB_BASE_ADDR + 0x75)

/* 寄存器说明：BIST SNDR ET0模式达标值
   详      述：BIST ET0模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET0_2_ADDR                      (ABB_BASE_ADDR + 0x76)

/* 寄存器说明：BIST SNDR ET1模式达标值
   详      述：BIST ET1模式 SNDR达标值[7:0]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET1_0_ADDR                      (ABB_BASE_ADDR + 0x77)

/* 寄存器说明：BIST SNDR ET1模式达标值
   详      述：BIST ET1模式 SNDR达标值[15:8]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET1_1_ADDR                      (ABB_BASE_ADDR + 0x78)

/* 寄存器说明：BIST SNDR ET1模式达标值
   详      述：BIST ET1模式 SNDR达标值[23:16]
   UNION结构 ：无 */
#define ABB_BIST_SNDR_ET1_2_ADDR                      (ABB_BASE_ADDR + 0x79)

/* 寄存器说明：IO_CFG寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_IOCG_INPUT_ADDR                           (ABB_BASE_ADDR + 0x7A)

/* 寄存器说明：IO_CFG寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_IOCG_OUTPUT_ADDR                          (ABB_BASE_ADDR + 0x7B)

/* 寄存器说明：IO_CFG寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_IOCG_RX_MCLK_ADDR                         (ABB_BASE_ADDR + 0x7C)

/* 寄存器说明：IO_CFG寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_IOCG_TCXO_ADDR                            (ABB_BASE_ADDR + 0x7D)

/* 寄存器说明：IO_CFG寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_IOCG_SC_CLK_ADDR                          (ABB_BASE_ADDR + 0x7E)

/* 寄存器说明：IO_CFG寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_IOCG_CFG_ADDR                             (ABB_BASE_ADDR + 0x7F)

/* 寄存器说明：ABB版本寄存器
   详      述：
   UNION结构 ：无 */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7]      保留
 bit[6]      ADPLL锁定指示。
 bit[5]      ADPLL稳定指示。0表示ADPLL未稳定；1表示ADPLL稳定。ADPLL稳定后有时钟输出。
 bit[4]      ADPLL门控使能信号。
 bit[3:1]    ADPLL时钟稳定等待时间配置，计数时钟为19.2M：
             000：ADPLL开启10us后时钟稳定；
             001：ADPLL开启20us后时钟稳定；
             010：ADPLL开启50us后时钟稳定；
             011：ADPLL开启75us后时钟稳定；
             100：ADPLL开启100us后时钟稳定；
             101：ADPLL开启115us后时钟稳定；
             110：ADPLL1开启125us后时钟稳定；
             default：100us
 bit[0]      ADPLL使能信号。用于通过CFG接口配置打开adpll。
   UNION结构:  ABB_ADPLL_LOCK_CTRL_UNION */
#define ABB_ADPLL_LOCK_CTRL_ADDR                      (ABB_BASE_ADDR + 0xA1)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7]:Reserved;
            [6:4]：PLL后分频因子postdiv2；默认值为1。
            [3]:Reserved;
            [2:0]：PLL后分频因子postdiv1；默认值为1。
   UNION结构 ：无 */
#define ABB_ADPLL_POSTDIV_ADDR                        (ABB_BASE_ADDR + 0xA2)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
   详      述：[7:0]：PLL反馈分频因子fbdiv[11:0]的低8bit；fbdiv[11:0]默认值为128.
   UNION结构 ：无 */
#define ABB_ADPLL_FBDIV_L_ADDR                        (ABB_BASE_ADDR + 0xA3)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:4]    保留
 bit[3:0]    PLL反馈分频因子fbdiv[11:0]的高4bit；
   UNION结构:  ABB_ADPLL_FBDIV_H_UNION */
#define ABB_ADPLL_FBDIV_H_ADDR                        (ABB_BASE_ADDR + 0xA4)

/* 寄存器说明：SC_PLL分频器因子配置寄存器
 bit[7:6]    保留
 bit[5:0]    PLL参考分频因子refdiv[5:0]，默认值为1。
   UNION结构:  ABB_ADPLL_REFDIV_UNION */
#define ABB_ADPLL_REFDIV_ADDR                         (ABB_BASE_ADDR + 0xA5)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[7:0]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_ADPLL_FRAC1_ADDR                          (ABB_BASE_ADDR + 0xA6)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[15:8]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_ADPLL_FRAC2_ADDR                          (ABB_BASE_ADDR + 0xA7)

/* 寄存器说明：SC_PLL分数因子配置寄存器
   详      述：[7:0]：PLL分数分频因子frac[23:0]的[23:16]位，frac[23:0]默认值0x0；
   UNION结构 ：无 */
#define ABB_ADPLL_FRAC3_ADDR                          (ABB_BASE_ADDR + 0xA8)

/* 寄存器说明：SC_PLL分频器控制寄存器
   详      述：[7:5]：Reserved；
            [4]：PLL FOUT4PHASEPD控制，高有效；默认值1（关闭）。
            [3]：
            [2]：PLL 旁路控制；默认值0（PLL旁路功能bypass）。
            [1]：PLL FOUTPOSTDIVPD控制，高有效；默认值0（打开）。
            [0]：PLL FOUTDCOPD控制，高有效；默认值0（打开）。
   UNION结构 ：无 */
#define ABB_ADPLL_FREQ_CTRL_ADDR                      (ABB_BASE_ADDR + 0xA9)

/* 寄存器说明：SC_PLL锁定控制寄存器
 bit[7:1]    保留
 bit[0]      ADPLL参数配置更新指示。
             adpll_en打开后，软件配置完adpll_postdiv，adpll_fbdiv，adpll_frac参数，再配置adpll_sfg_update，参数同时更新；adpll_en不打开时，配置参数立即更新，不需要配置adpll_sfg_update。
   UNION结构:  ABB_ADPLL_CFG_UPDATE_UNION */
#define ABB_ADPLL_CFG_UPDATE_ADDR                     (ABB_BASE_ADDR + 0xAA)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG0_ADDR                       (ABB_BASE_ADDR + 0xAB)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG1_ADDR                       (ABB_BASE_ADDR + 0xAC)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG2_ADDR                       (ABB_BASE_ADDR + 0xAD)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG3_ADDR                       (ABB_BASE_ADDR + 0xAE)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG4_ADDR                       (ABB_BASE_ADDR + 0xAF)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG5_ADDR                       (ABB_BASE_ADDR + 0xB0)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG6_ADDR                       (ABB_BASE_ADDR + 0xB1)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG7_ADDR                       (ABB_BASE_ADDR + 0xB2)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG8_ADDR                       (ABB_BASE_ADDR + 0xB3)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG9_ADDR                       (ABB_BASE_ADDR + 0xB4)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_GPLLCFG10_ADDR                      (ABB_BASE_ADDR + 0xB5)

/* 寄存器说明：
 bit[7:2]    保留
 bit[1]
 bit[0]
   UNION结构:  ABB_ADPLL_TEST_CFG_UNION */
#define ABB_ADPLL_TEST_CFG_ADDR                       (ABB_BASE_ADDR + 0xB6)

/* 寄存器说明：
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_ADPLL_CLKSSCG_CFG_UNION */
#define ABB_ADPLL_CLKSSCG_CFG_ADDR                    (ABB_BASE_ADDR + 0xB7)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_TEST_WDATA_LSB_ADDR                 (ABB_BASE_ADDR + 0xB8)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_ADPLL_TEST_WDATA_MSB_ADDR                 (ABB_BASE_ADDR + 0xB9)

/* 寄存器说明：TX ET数字配置寄存器1。
 bit[7]      保留
 bit[6]      ET通道降采样bypass信号
             0：不bypass，2倍降采样（默认）；
             1：bypass，不进行降采样。
 bit[5:3]    保留
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
#define ABB_TX_ET_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x100)

/* 寄存器说明：TX ET数字配置寄存器2。
 bit[7]      ET TX通道dem bypass：
             0：DEM打开(默认)
             1：DEM bypass
 bit[6]      保留
 bit[5]      ET TX通道DEM模式控制：
             0：使用CLA模式(默认)
             1：使用DWA模式
 bit[4]      保留
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
#define ABB_TX_ET_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x101)

/* 寄存器说明：TX ET数字配置寄存器3。
   详      述：保留
   UNION结构 ：无 */
#define ABB_TX_ET_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x102)

/* 寄存器说明：TX ET数字配置寄存器4。
 bit[7]
 bit[6]      ET通道算法环回模式使能。该模式使能，将ET TX数据通过CH1 RX通道环回。
             0：不使能；
             1：使能。
 bit[5]      ET通道接口环回模式使能。该模式使能，将ET TX数据通过CH1 RX通道环回。
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
#define ABB_TX_ET_DIG_4_ADDR                          (ABB_BASE_ADDR + 0x103)

/* 寄存器说明：ET通道offset配置寄存器。
   详      述：ET通道offset配置寄存器。
   UNION结构 ：无 */
#define ABB_ET_DC_OFFSET_ADDR                         (ABB_BASE_ADDR + 0x104)

/* 寄存器说明：ET通道状态上报寄存器
 bit[7:3]    保留
 bit[2]      ET HB滤波器溢出指示。
 bit[1]      ET CIC6滤波器溢出指示。
 bit[0]      ET补偿滤波器溢出指示。
   UNION结构:  ABB_ET_STATE_RPT_UNION */
#define ABB_ET_STATE_RPT_ADDR                         (ABB_BASE_ADDR + 0x105)

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
#define ABB_ET_SINE_GENERATE_ADDR                     (ABB_BASE_ADDR + 0x106)

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
   UNION结构:  ABB_TX_3G_DIG_1_UNION */
#define ABB_TX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x20C)

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
   UNION结构:  ABB_TX_3G_DIG_2_UNION */
#define ABB_TX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x20D)

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
   UNION结构:  ABB_TX_3G_DIG_3_UNION */
#define ABB_TX_3G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x20E)

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
   UNION结构:  ABB_TX_4G_DIG_1_UNION */
#define ABB_TX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x20F)

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
   UNION结构:  ABB_TX_4G_DIG_2_UNION */
#define ABB_TX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x210)

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
   UNION结构:  ABB_TX_4G_DIG_3_UNION */
#define ABB_TX_4G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x211)

/* 寄存器说明：测试模式寄存器。
 bit[7:1]    保留
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
   详      述：TX通道模式控制：
            000：2G(默认)
            001：3G
            010：4G
            011：TDS
            100：CDMA
            Others：Reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x24A)

/* 寄存器说明：TX数字工作状态上报寄存器。
   详      述：TX通道FIFO读空状态
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
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x253)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x254)

/* 寄存器说明：测试模式寄存器。
 bit[7:1]    保留
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
   详      述：TX通道模式控制上报：
            000：2G(默认)
            001：3G
            010：4G &amp; ET &amp; APT
            011：TDS
            Others：CA
   UNION结构 ：无 */
#define ABB_CH1_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x26A)

/* 寄存器说明：TX数字工作状态上报寄存器。
   详      述：TX通道FIFO读空状态
   UNION结构 ：无 */
#define ABB_CH1_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x26B)

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
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x273)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x274)

/* 寄存器说明：RX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
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
             11：固定系数4。
   UNION结构:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x400)

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
#define ABB_RX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x401)

/* 寄存器说明：RX IDLE模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1:0]
   UNION结构:  ABB_RX_IDLE_DIG_3_UNION */
#define ABB_RX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x402)

/* 寄存器说明：RX 2G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
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
             11：固定系数4。
   UNION结构:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x403)

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
#define ABB_RX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x404)

/* 寄存器说明：RX 2G模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1:0]
   UNION结构:  ABB_RX_2G_DIG_3_UNION */
#define ABB_RX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x405)

/* 寄存器说明：RX C模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
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
             11：固定系数4。
   UNION结构:  ABB_RX_C_DIG_1_UNION */
#define ABB_RX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x406)

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
#define ABB_RX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x407)

/* 寄存器说明：RX C模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1:0]
   UNION结构:  ABB_RX_C_DIG_3_UNION */
#define ABB_RX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x408)

/* 寄存器说明：RX TDS模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
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
             11：固定系数4。
   UNION结构:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x409)

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
#define ABB_RX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x40A)

/* 寄存器说明：RX TDS模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1:0]
   UNION结构:  ABB_RX_TDS_DIG_3_UNION */
#define ABB_RX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x40B)

/* 寄存器说明：RX 3G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
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
             11：固定系数4。
   UNION结构:  ABB_RX_3G_DIG_1_UNION */
#define ABB_RX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x40C)

/* 寄存器说明：RX 3G模式配置寄存器2，由线控决定是否起作用。
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
   UNION结构:  ABB_RX_3G_DIG_2_UNION */
#define ABB_RX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x40D)

/* 寄存器说明：RX 3G模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1:0]
   UNION结构:  ABB_RX_3G_DIG_3_UNION */
#define ABB_RX_3G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x40E)

/* 寄存器说明：RX 4G模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    RX通道CIC滤波器输出速率控制(Hz)：
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
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
             11：固定系数4。
   UNION结构:  ABB_RX_4G_DIG_1_UNION */
#define ABB_RX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x40F)

/* 寄存器说明：RX 4G模式配置寄存器2，由线控决定是否起作用。
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
   UNION结构:  ABB_RX_4G_DIG_2_UNION */
#define ABB_RX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x410)

/* 寄存器说明：RX 4G模式配置寄存器3，由线控决定是否起作用。
 bit[7:2]    保留
 bit[1:0]
   UNION结构:  ABB_RX_4G_DIG_3_UNION */
#define ABB_RX_4G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x411)

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
#define ABB_RX_EN_DELAY_ADDR                          (ABB_BASE_ADDR + 0x420)

/* 寄存器说明：模式寄存器
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_COMB_MODE_UNION */
#define ABB_COMB_MODE_ADDR                            (ABB_BASE_ADDR + 0x421)

/* 寄存器说明：测试模式寄存器。
 bit[7:6]    保留
 bit[5:4]
 bit[3:2]    保留
 bit[1]
 bit[0]      数字部分RX通道软复位信号：
             0：不复位(默认)
             1：复位
   UNION结构:  ABB_CH0_RX_TESTMODE_UNION */
#define ABB_CH0_RX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x480)

/* 寄存器说明：PLL选择寄存器
 bit[7:4]    保留
 bit[3]
 bit[2]
 bit[1:0]
   UNION结构:  ABB_CH0_PLL_SEL_UNION */
#define ABB_CH0_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x481)

/* 寄存器说明：RX数字工作模式上报寄存器。
   详      述：RX通道模式控制上报：
            000：2G(默认)
            001：3G_SC
            010：4G &amp; ET &amp; APT
            011：3G_DC
            100：TDS
            Others：CA
   UNION结构 ：无 */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x482)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x483)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x484)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXA_I_COEF1_UNION */
#define ABB_CH0_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x485)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x486)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXA_I_COEF3_UNION */
#define ABB_CH0_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x487)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x488)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x489)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXA_Q_COEF1_UNION */
#define ABB_CH0_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x48A)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x48B)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXA_Q_COEF3_UNION */
#define ABB_CH0_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x48C)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x48D)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x48E)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXB_I_COEF1_UNION */
#define ABB_CH0_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x48F)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x490)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXB_I_COEF3_UNION */
#define ABB_CH0_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x491)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x492)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x493)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH0_RXB_Q_COEF1_UNION */
#define ABB_CH0_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x494)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x495)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH0_RXB_Q_COEF3_UNION */
#define ABB_CH0_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x496)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH0_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x497)

/* 寄存器说明：RXA通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH0_REG_RXA_DCR_CFG_UNION */
#define ABB_CH0_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x498)

/* 寄存器说明：RXB通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH0_REG_RXB_DCR_CFG_UNION */
#define ABB_CH0_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x499)

/* 寄存器说明：BLOCKING DCR功能控制寄存器。
 bit[7:2]    保留
 bit[1]      RXB天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
 bit[0]      RXA天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
   UNION结构:  ABB_CH0_REG_RX_DCR_CTRL_UNION */
#define ABB_CH0_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x49A)

/* 寄存器说明：RXA通道BLOCKING上报寄存器。
 bit[7:5]    RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXA天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x49B)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXB天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH0_RXB_BLOCKING_UNION */
#define ABB_CH0_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x49C)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器1。
   详      述：RXA天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x49D)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x49E)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器1。
   详      述：RXA天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x49F)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A0)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器1。
   详      述：RXB天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4A1)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4A2)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器1。
   详      述：RXB天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4A3)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A4)

/* 寄存器说明：通道0配置寄存器。
   详      述：通道0 flush宽度[7:0]，单位为19.2M时钟周期。
   UNION结构 ：无 */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4A5)

/* 寄存器说明：通道0配置寄存器。
 bit[7:3]    通道0 FLUSH值，默认为8。
 bit[2:0]    通道0 flush宽度[10:8]，单位为19.2M时钟周期。
   UNION结构:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4A6)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
   详      述：CH0通道RXA I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4A7)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXAI_HB_GAIN_2_UNION */
#define ABB_CH0_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4A8)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
   详      述：CH0通道RXA Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4A9)

/* 寄存器说明：CH0通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AA)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
   详      述：CH0通道RXB I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AB)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXBI_HB_GAIN_2_UNION */
#define ABB_CH0_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AC)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
   详      述：CH0通道RXB Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH0_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AD)

/* 寄存器说明：CH0通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH0_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AE)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      CH0通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
 bit[0]      CH0通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4AF)

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
#define ABB_CH0_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4B0)

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
#define ABB_CH0_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4B1)

/* 寄存器说明：blk控制寄存器。
 bit[7:3]    保留
 bit[2]      线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能
 bit[1]      线控信号CH0_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值
 bit[0]      BLOCKING自动门控使能：
             0：使能
             1：不使能
   UNION结构:  ABB_CH0_BLK_CFG_UNION */
#define ABB_CH0_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4B2)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4B3)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH0_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4B4)

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
#define ABB_CH0_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4B5)

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
 bit[3]
 bit[2]
 bit[1:0]
   UNION结构:  ABB_CH1_PLL_SEL_UNION */
#define ABB_CH1_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x4C1)

/* 寄存器说明：RX数字工作模式上报寄存器。
   详      述：RX通道模式控制上报：
            000：2G(默认)
            001：3G_SC
            010：4G &amp; ET &amp; APT
            011：3G_DC
            100：TDS
            Others：CA
   UNION结构 ：无 */
#define ABB_CH1_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x4C2)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x4C3)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4C4)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXA_I_COEF1_UNION */
#define ABB_CH1_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4C5)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4C6)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXA_I_COEF3_UNION */
#define ABB_CH1_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4C7)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4C8)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4C9)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXA通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXA通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXA_Q_COEF1_UNION */
#define ABB_CH1_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4CA)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4CB)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXA通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXA_Q_COEF3_UNION */
#define ABB_CH1_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4CC)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXA通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4CD)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4CE)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXB_I_COEF1_UNION */
#define ABB_CH1_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4CF)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D0)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXB_I_COEF3_UNION */
#define ABB_CH1_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D1)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4D2)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4D3)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      RXB通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    RXB通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_CH1_RXB_Q_COEF1_UNION */
#define ABB_CH1_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4D4)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D5)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    RXB通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_CH1_RXB_Q_COEF3_UNION */
#define ABB_CH1_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D6)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：RXB通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_CH1_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4D7)

/* 寄存器说明：RXA通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXA天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXA天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH1_REG_RXA_DCR_CFG_UNION */
#define ABB_CH1_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4D8)

/* 寄存器说明：RXB通道BLOCKING DCR配置寄存器。
 bit[7:5]    RXB天线BLOCKING DCR 滤波器收敛速度配置。配置范围0~7，对应表示滤波器中L参数为8~15。取较大系数，需要更长的收敛时间，得到更小的残余DC误差值。
 bit[4:0]    RXB天线BLOCKING DCR功能收敛时间配置，取值范围0~19,表示收敛时间在512~512*20个采样点，步径为512个采样点，每个采样点频率15.36MHz。DRC收敛时间之后，启动Blocking能量计算。
   UNION结构:  ABB_CH1_REG_RXB_DCR_CFG_UNION */
#define ABB_CH1_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4D9)

/* 寄存器说明：BLOCKING DCR功能控制寄存器。
 bit[7:2]    保留
 bit[1]      RXB天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
 bit[0]      RXA天线BLOCKING DCR功能bypass控制。
             0：DCR功能不bypasss；
             1：DCR功能bypass。
   UNION结构:  ABB_CH1_REG_RX_DCR_CTRL_UNION */
#define ABB_CH1_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x4DA)

/* 寄存器说明：RXA通道BLOCKING上报寄存器。
 bit[7:5]    RXA天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXA天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4DB)

/* 寄存器说明：RXB通道BLOCKING上报寄存器。
 bit[7:5]    RXB天线BLOCKING上报值，系数N；BLOCKING上报结果为N*2^M
 bit[4:0]    RXB天线BLOCKING上报值,2的幂次M
   UNION结构:  ABB_CH1_RXB_BLOCKING_UNION */
#define ABB_CH1_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4DC)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器1。
   详      述：RXA天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4DD)

/* 寄存器说明：RXA通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXA_DC_I_2_UNION */
#define ABB_CH1_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4DE)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器1。
   详      述：RXA天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4DF)

/* 寄存器说明：RXA通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXA天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXA_DC_Q_2_UNION */
#define ABB_CH1_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E0)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器1。
   详      述：RXB天线I路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4E1)

/* 寄存器说明：RXB通道I路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线I路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXB_DC_I_2_UNION */
#define ABB_CH1_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4E2)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器1。
   详      述：RXB天线Q路信号BLOCKING DC上报值高8bit
   UNION结构 ：无 */
#define ABB_CH1_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4E3)

/* 寄存器说明：RXB通道Q路BLOCKING DC上报寄存器2。
 bit[7:4]    RXB天线Q路信号BLOCKING DC上报值低4bit
 bit[3:0]    保留
   UNION结构:  ABB_CH1_REG_RXB_DC_Q_2_UNION */
#define ABB_CH1_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E4)

/* 寄存器说明：通道1配置寄存器。
   详      述：通道1 flush宽度[7:0]，单位为19.2M时钟周期。
   UNION结构 ：无 */
#define ABB_CH1_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4E5)

/* 寄存器说明：通道1配置寄存器。
 bit[7:3]    通道1 FLUSH值，默认为8。
 bit[2:0]    通道1 flush宽度[10:8]，单位为19.2M时钟周期。
   UNION结构:  ABB_CH1_FLUSH_CFG1_UNION */
#define ABB_CH1_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4E6)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
   详      述：CH1通道RXA I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4E7)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXA I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXAI_HB_GAIN_2_UNION */
#define ABB_CH1_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4E8)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
   详      述：CH1通道RXA Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4E9)

/* 寄存器说明：CH1通道RXA HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXA Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EA)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
   详      述：CH1通道RXB I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4EB)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXB I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXBI_HB_GAIN_2_UNION */
#define ABB_CH1_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EC)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
   详      述：CH1通道RXB Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_CH1_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4ED)

/* 寄存器说明：CH1通道RXB HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH1通道RXB Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_CH1_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EE)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      CH1通道RXB环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
 bit[0]      CH1通道RXA环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4EF)

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
#define ABB_CH1_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4F0)

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
#define ABB_CH1_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4F1)

/* 寄存器说明：blk控制寄存器。
 bit[7:3]    保留
 bit[2]      线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置使能
 bit[1]      线控信号CH1_RXA_BLK_EN, CH1_RXB_BLK_EN强制配置值
 bit[0]      BLOCKING自动门控使能：
             0：使能
             1：不使能
   UNION结构:  ABB_CH1_BLK_CFG_UNION */
#define ABB_CH1_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4F2)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4F3)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_CH1_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4F4)

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
#define ABB_CH1_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4F5)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_MEM_CTRL_MSB_ADDR                         (ABB_BASE_ADDR + 0x600)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_MEM_CTRL_LSB_ADDR                         (ABB_BASE_ADDR + 0x601)

/* 寄存器说明：
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_DEBUG_RESET_UNION */
#define ABB_DEBUG_RESET_ADDR                          (ABB_BASE_ADDR + 0x602)

/* 寄存器说明：
 bit[7:6]    保留
 bit[5]
 bit[4]
 bit[3:2]
 bit[1:0]
   UNION结构:  ABB_DEBUG_CHANNEL_SEL_UNION */
#define ABB_DEBUG_CHANNEL_SEL_ADDR                    (ABB_BASE_ADDR + 0x603)

/* 寄存器说明：
 bit[7:1]    保留
 bit[0]
   UNION结构:  ABB_DEBUG_RAM_EN_UNION */
#define ABB_DEBUG_RAM_EN_ADDR                         (ABB_BASE_ADDR + 0x604)

/* 寄存器说明：
 bit[7:3]    保留
 bit[2]
 bit[1]
 bit[0]
   UNION结构:  ABB_DEBUG_RAM_CFG_UNION */
#define ABB_DEBUG_RAM_CFG_ADDR                        (ABB_BASE_ADDR + 0x605)

/* 寄存器说明：
 bit[7:3]    保留
 bit[2]
 bit[1]      保留
 bit[0]
   UNION结构:  ABB_DEBUG_RAM_RPT1_UNION */
#define ABB_DEBUG_RAM_RPT1_ADDR                       (ABB_BASE_ADDR + 0x606)

/* 寄存器说明：
 bit[7]      保留
 bit[6:0]
   UNION结构:  ABB_DEBUG_RAM_RPT2_UNION */
#define ABB_DEBUG_RAM_RPT2_ADDR                       (ABB_BASE_ADDR + 0x607)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_DEBUG_RAM_RPT3_ADDR                       (ABB_BASE_ADDR + 0x608)

/* 寄存器说明：
 bit[7]      保留
 bit[6:0]
   UNION结构:  ABB_DEBUG_RAM_RPT4_UNION */
#define ABB_DEBUG_RAM_RPT4_ADDR                       (ABB_BASE_ADDR + 0x609)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define ABB_DEBUG_RAM_RPT5_ADDR                       (ABB_BASE_ADDR + 0x60A)

/* 寄存器说明：RX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    保留
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {sar_comp_sel_b1,sar_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：固定系数4。
   UNION结构:  ABB_SAR_DIG_1_UNION */
#define ABB_SAR_DIG_1_ADDR                            (ABB_BASE_ADDR + 0x680)

/* 寄存器说明：RX IDLE模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {sar_comp_sel_b1,sar_comp_sel_b0}组成补偿滤波器系数选择，参考sar_comp_sel_b0说明。
 bit[6]      保留
 bit[5]      RX通道随路时钟SAR_CLK反向使能：
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
 bit[1]      保留
 bit[0]      SAR通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!sar_pd)|XX_SAR_EN = 1时工作，否则关闭
   UNION结构:  ABB_SAR_DIG_2_UNION */
#define ABB_SAR_DIG_2_ADDR                            (ABB_BASE_ADDR + 0x681)

/* 寄存器说明：测试模式寄存器
 bit[7:2]    保留
 bit[1]
 bit[0]      数字部分RX通道软复位信号：
             0：不复位(默认)
             1：复位
   UNION结构:  ABB_SAR_TESTMODE_UNION */
#define ABB_SAR_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x682)

/* 寄存器说明：PLL选择寄存器
 bit[7:4]    保留
 bit[3]
 bit[2]
 bit[1:0]
   UNION结构:  ABB_SAR_PLL_SEL_UNION */
#define ABB_SAR_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x683)

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
#define ABB_SAR_MODE_RPT_ADDR                         (ABB_BASE_ADDR + 0x684)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_SAR_STATE_RPT_ADDR                        (ABB_BASE_ADDR + 0x685)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：SAR通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_SAR_I_COEF0_ADDR                          (ABB_BASE_ADDR + 0x686)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      SAR通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    SAR通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_SAR_I_COEF1_UNION */
#define ABB_SAR_I_COEF1_ADDR                          (ABB_BASE_ADDR + 0x687)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：SAR通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_SAR_I_COEF2_ADDR                          (ABB_BASE_ADDR + 0x688)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    SAR通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_SAR_I_COEF3_UNION */
#define ABB_SAR_I_COEF3_ADDR                          (ABB_BASE_ADDR + 0x689)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：SAR通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_SAR_I_COEF4_ADDR                          (ABB_BASE_ADDR + 0x68A)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：SAR通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_SAR_Q_COEF0_ADDR                          (ABB_BASE_ADDR + 0x68B)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      SAR通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    SAR通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_SAR_Q_COEF1_UNION */
#define ABB_SAR_Q_COEF1_ADDR                          (ABB_BASE_ADDR + 0x68C)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：SAR通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_SAR_Q_COEF2_ADDR                          (ABB_BASE_ADDR + 0x68D)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    SAR通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_SAR_Q_COEF3_UNION */
#define ABB_SAR_Q_COEF3_ADDR                          (ABB_BASE_ADDR + 0x68E)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：SAR通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_SAR_Q_COEF4_ADDR                          (ABB_BASE_ADDR + 0x68F)

/* 寄存器说明：CH0通道SAR HB滤波器增益。
   详      述：CH0通道SAR I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_SARI_HB_GAIN_1_ADDR                       (ABB_BASE_ADDR + 0x690)

/* 寄存器说明：CH0通道SAR HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道SAR I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_SARI_HB_GAIN_2_UNION */
#define ABB_SARI_HB_GAIN_2_ADDR                       (ABB_BASE_ADDR + 0x691)

/* 寄存器说明：CH0通道SAR HB滤波器增益。
   详      述：CH0通道SAR Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_SARQ_HB_GAIN_1_ADDR                       (ABB_BASE_ADDR + 0x692)

/* 寄存器说明：CH0通道SAR HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道SAR Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_SARQ_HB_GAIN_2_UNION */
#define ABB_SARQ_HB_GAIN_2_ADDR                       (ABB_BASE_ADDR + 0x693)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      保留
 bit[0]      CH0通道SAR环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_SAR_CTRL_UNION */
#define ABB_SAR_CTRL_ADDR                             (ABB_BASE_ADDR + 0x694)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_SAR_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x695)

/* 寄存器说明：数字调试寄存器。
 bit[7]      bit[7]：模式切换复位长度配置使能
             0：不使能
             1：使能
 bit[6:4]    模式切换复位长度配置值，单位为8 cycles
 bit[3:1]    保留
 bit[0]      RX分频器使能bypass控制
             0：不bypass
             1：bypass
   UNION结构:  ABB_SAR_REG_DEBUG_DIG_UNION */
#define ABB_SAR_REG_DEBUG_DIG_ADDR                    (ABB_BASE_ADDR + 0x696)

/* 寄存器说明：RX IDLE模式配置寄存器1，由线控决定是否起作用。
 bit[7:5]    RX通道模式控制：
             000：2G_A(默认)
             001：3G_SC/TDS_B/4G_C
             010：4G
             011：3G_DC/4G_B
             100：TDS
             101：CDMA
             110：CA
             111：2G_B
 bit[4:3]    保留
 bit[2]      RX通道半带滤波器bypass控制：
             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate
 bit[1]      RX通道补偿滤波器补偿系数固定控制：
             0：系数不固定，由寄存器配置
             1：系数固定
 bit[0]      {n50m_comp_sel_b1,n50m_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
             00：固定系数1；
             01：固定系数2；
             10：固定系数3；
             11：固定系数4。
   UNION结构:  ABB_N50M_DIG_1_UNION */
#define ABB_N50M_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x6B0)

/* 寄存器说明：RX IDLE模式配置寄存器2，由线控决定是否起作用。
 bit[7]      {n50m_comp_sel_b1,n50m_comp_sel_b0}组成补偿滤波器系数选择，参考n50m_comp_sel_b0说明。
 bit[6]      保留
 bit[5]      RX通道随路时钟N50M_CLK反向使能：
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
 bit[1]      保留
 bit[0]      N50M通道CLOCK GATING控制：
             0：不CLOCK GATING
             1：CLOCK GATING(默认)
             (!n50m_pd)|XX_N50M_EN = 1时工作，否则关闭
   UNION结构:  ABB_N50M_DIG_2_UNION */
#define ABB_N50M_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x6B1)

/* 寄存器说明：测试模式寄存器
 bit[7:2]    保留
 bit[1]
 bit[0]      数字部分RX通道软复位信号：
             0：不复位(默认)
             1：复位
   UNION结构:  ABB_N50M_TESTMODE_UNION */
#define ABB_N50M_TESTMODE_ADDR                        (ABB_BASE_ADDR + 0x6B2)

/* 寄存器说明：PLL选择寄存器
 bit[7:4]    保留
 bit[3]
 bit[2]
 bit[1:0]
   UNION结构:  ABB_N50M_PLL_SEL_UNION */
#define ABB_N50M_PLL_SEL_ADDR                         (ABB_BASE_ADDR + 0x6B3)

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
#define ABB_N50M_MODE_RPT_ADDR                        (ABB_BASE_ADDR + 0x6B4)

/* 寄存器说明：RX数字工作状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_N50M_STATE_RPT_ADDR                       (ABB_BASE_ADDR + 0x6B5)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：N50M通道I路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_N50M_I_COEF0_ADDR                         (ABB_BASE_ADDR + 0x6B6)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      N50M通道I路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    N50M通道I路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_N50M_I_COEF1_UNION */
#define ABB_N50M_I_COEF1_ADDR                         (ABB_BASE_ADDR + 0x6B7)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：N50M通道I路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_N50M_I_COEF2_ADDR                         (ABB_BASE_ADDR + 0x6B8)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    N50M通道I路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_N50M_I_COEF3_UNION */
#define ABB_N50M_I_COEF3_ADDR                         (ABB_BASE_ADDR + 0x6B9)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：N50M通道I路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_N50M_I_COEF4_ADDR                         (ABB_BASE_ADDR + 0x6BA)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：N50M通道Q路补偿滤波器系数C0,有符号数
   UNION结构 ：无 */
#define ABB_N50M_Q_COEF0_ADDR                         (ABB_BASE_ADDR + 0x6BB)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      N50M通道Q路补偿滤波器系数C3,无符号数,最高位
 bit[6:0]    N50M通道Q路补偿滤波器系数C1,有符号数
   UNION结构:  ABB_N50M_Q_COEF1_UNION */
#define ABB_N50M_Q_COEF1_ADDR                         (ABB_BASE_ADDR + 0x6BC)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：N50M通道Q路补偿滤波器系数C3,无符号数,低8位
   UNION结构 ：无 */
#define ABB_N50M_Q_COEF2_ADDR                         (ABB_BASE_ADDR + 0x6BD)

/* 寄存器说明：RX通道补偿系数寄存器。
 bit[7]      保留
 bit[6:0]    N50M通道Q路补偿滤波器系数C5,有符号数
   UNION结构:  ABB_N50M_Q_COEF3_UNION */
#define ABB_N50M_Q_COEF3_ADDR                         (ABB_BASE_ADDR + 0x6BE)

/* 寄存器说明：RX通道补偿系数寄存器。
   详      述：N50M通道Q路补偿滤波器系数C6,有符号数
   UNION结构 ：无 */
#define ABB_N50M_Q_COEF4_ADDR                         (ABB_BASE_ADDR + 0x6BF)

/* 寄存器说明：CH0通道N50M HB滤波器增益。
   详      述：CH0通道N50M I路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_N50MI_HB_GAIN_1_ADDR                      (ABB_BASE_ADDR + 0x6C0)

/* 寄存器说明：CH0通道N50M HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道N50M I路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_N50MI_HB_GAIN_2_UNION */
#define ABB_N50MI_HB_GAIN_2_ADDR                      (ABB_BASE_ADDR + 0x6C1)

/* 寄存器说明：CH0通道N50M HB滤波器增益。
   详      述：CH0通道N50M Q路 HB滤波器增益（10u）的低8bit。增益默认值512。
   UNION结构 ：无 */
#define ABB_N50MQ_HB_GAIN_1_ADDR                      (ABB_BASE_ADDR + 0x6C2)

/* 寄存器说明：CH0通道N50M HB滤波器增益。
 bit[7:2]    保留
 bit[1:0]    CH0通道N50M Q路 HB滤波器增益（10u）的高2bit。增益默认值512。
   UNION结构:  ABB_N50MQ_HB_GAIN_2_UNION */
#define ABB_N50MQ_HB_GAIN_2_ADDR                      (ABB_BASE_ADDR + 0x6C3)

/* 寄存器说明：通道控制寄存器。
 bit[7:2]    保留
 bit[1]      保留
 bit[0]      CH0通道N50M环回输出控制信号，0：环回不输出信号；1：环回同时输出信号；
   UNION结构:  ABB_N50M_CTRL_UNION */
#define ABB_N50M_CTRL_ADDR                            (ABB_BASE_ADDR + 0x6C4)

/* 寄存器说明：线控状态上报寄存器。
   详      述：保留
   UNION结构 ：无 */
#define ABB_N50M_LINE_RPT0_ADDR                       (ABB_BASE_ADDR + 0x6C5)

/* 寄存器说明：数字调试寄存器。
 bit[7]      bit[7]：模式切换复位长度配置使能
             0：不使能
             1：使能
 bit[6:4]    模式切换复位长度配置值，单位为8 cycles
 bit[3:1]    保留
 bit[0]      RX分频器使能bypass控制
             0：不bypass
             1：bypass
   UNION结构:  ABB_N50M_REG_DEBUG_DIG_UNION */
#define ABB_N50M_REG_DEBUG_DIG_ADDR                   (ABB_BASE_ADDR + 0x6C6)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] reserved
            [6] ADPLL_CLK_PAD_EN：adpll1测试时钟使能
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR00_ADDR                      (ABB_BASE_ADDR + 0x800)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:3] reserved
            [2:0] GPLL_SEL：gpll时钟选择
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR01_ADDR                      (ABB_BASE_ADDR + 0x801)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] SC1_245M_SEL：scpll1 245M 时钟选择
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR02_ADDR                      (ABB_BASE_ADDR + 0x802)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5] ADPLL_FREF_SEL：adpll时钟参考选择
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR03_ADDR                      (ABB_BASE_ADDR + 0x803)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] GPLL_CLK104M_PD gpll 245M时钟power down控制
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR04_ADDR                      (ABB_BASE_ADDR + 0x804)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7] WPLL_CLK245M_PD wpll 245M时钟power down控制
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR05_ADDR                      (ABB_BASE_ADDR + 0x805)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5] CH0_DAC_CLK_EN：ch0 dac时钟输出使能
                  0：时钟关闭
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR06_ADDR                      (ABB_BASE_ADDR + 0x806)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5] CH1_DAC_CLK_EN：ch1 dac时钟输出使能
                  0：时钟关闭
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR07_ADDR                      (ABB_BASE_ADDR + 0x807)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] CH1_ADC_CLK_EN：ch1 adc时钟输出使能
                  0：时钟关闭
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR08_ADDR                      (ABB_BASE_ADDR + 0x808)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5] PD_TCXO1：tcxo1 power down控制
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR09_ADDR                      (ABB_BASE_ADDR + 0x809)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] EXCLK_PD：外灌时钟power down控制
                  0：打开外灌时钟模块
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR10_ADDR                      (ABB_BASE_ADDR + 0x80A)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5:4] WG_VCSEL：wpll/gpll vc电压选择
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR11_ADDR                      (ABB_BASE_ADDR + 0x80B)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] REF_FS：ref快速启动控制
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR12_ADDR                      (ABB_BASE_ADDR + 0x80C)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:5] reserved
            [4] RCTUNE_CAP_SEL：rctune电容选择
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR13_ADDR                      (ABB_BASE_ADDR + 0x80D)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:6] reserved
            [5] CH3_SE_VCM_SEL：ch3单端模式共模选择
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR14_ADDR                      (ABB_BASE_ADDR + 0x80E)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR15_ADDR                      (ABB_BASE_ADDR + 0x80F)

/* 寄存器说明：TX RCTUNE配置寄存器
   详      述：[7] reversed
            [6:0] TX_RCTUNE ：TX TUNE RC校准值
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR16_ADDR                      (ABB_BASE_ADDR + 0x810)

/* 寄存器说明：RX RCTUNE配置寄存器
   详      述：[7] reversed
            [6:0] RX_RCTUNE ：RX TUNE RC校准值
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR17_ADDR                      (ABB_BASE_ADDR + 0x811)

/* 寄存器说明：CH3 RX RCTUNE配置寄存器
   详      述：[7] reversed
            [6:0] CH3_RX_RCTUNE ：CH3 RX TUNE RC校准值
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR18_ADDR                      (ABB_BASE_ADDR + 0x812)

/* 寄存器说明：ET RCTUNE配置寄存器
   详      述：[7] reversed
            [6:0] ET_RCTUNE ：ET TUNE RC校准值
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR19_ADDR                      (ABB_BASE_ADDR + 0x813)

/* 寄存器说明：模拟common读写寄存器
 bit[7:5]    保留
 bit[4]
 bit[3]
 bit[2]
 bit[1]
 bit[0]
   UNION结构:  ABB_ANA_COMMON_WR20_UNION */
#define ABB_ANA_COMMON_WR20_ADDR                      (ABB_BASE_ADDR + 0x814)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR21_ADDR                      (ABB_BASE_ADDR + 0x815)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR22_ADDR                      (ABB_BASE_ADDR + 0x816)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR23_ADDR                      (ABB_BASE_ADDR + 0x817)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR24_ADDR                      (ABB_BASE_ADDR + 0x818)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR25_ADDR                      (ABB_BASE_ADDR + 0x819)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR26_ADDR                      (ABB_BASE_ADDR + 0x81A)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR27_ADDR                      (ABB_BASE_ADDR + 0x81B)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR28_ADDR                      (ABB_BASE_ADDR + 0x81C)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR29_ADDR                      (ABB_BASE_ADDR + 0x81D)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR30_ADDR                      (ABB_BASE_ADDR + 0x81E)

/* 寄存器说明：模拟common读写寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_ANA_COMMON_WR31_ADDR                      (ABB_BASE_ADDR + 0x81F)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7:1] reversed
            [0]  RC_TUNE_READY ：RC校准完成信号
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO00_ADDR                      (ABB_BASE_ADDR + 0x830)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7] reversed
            [6:0] RC_TUNE_DOUT ：RC校准值
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO01_ADDR                      (ABB_BASE_ADDR + 0x831)

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
#define ABB_ANA_COMMON_RO02_ADDR                      (ABB_BASE_ADDR + 0x832)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7:6] reserved
            [5] CH3_OPCAL_OK_RXC_Q：ch3 rxc q路op1校准完成信号
            [4] CH3_OPCAL_OK_RXC_I：ch3 rxc i路op1校准完成信号
            [3] CH3_OPCAL_OK_RXB_Q：ch3 rxb q路op1校准完成信号
            [2] CH3_OPCAL_OK_RXB_I：ch3 rxb i路op1校准完成信号
            [1] CH3_OPCAL_OK_RXA_Q：ch3 rxa q路op1校准完成信号
            [0] CH3_OPCAL_OK_RXA_I：ch3 rxa i路op1校准完成信号
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO03_ADDR                      (ABB_BASE_ADDR + 0x833)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7:2] reserved
            [1] WPLL_LOCK_FLAG：wpll锁定信号
            [0] GPLL_LOCK_FLAG：gpll锁定信号
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO04_ADDR                      (ABB_BASE_ADDR + 0x834)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7:0] reserved tielow
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO05_ADDR                      (ABB_BASE_ADDR + 0x835)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7:0] reserved tielow
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO06_ADDR                      (ABB_BASE_ADDR + 0x836)

/* 寄存器说明：模拟common只读寄存器
   详      述：[7:0] reserved tielow
   UNION结构 ：无 */
#define ABB_ANA_COMMON_RO07_ADDR                      (ABB_BASE_ADDR + 0x837)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至
   详      述：[7:6] reserved
            [5]：ET_CLK_SEL：选择CH0还是CH1支持ET。
   UNION结构 ：无 */
#define ABB_ET_ET_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x900)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至
   详      述：[7:1] reserved
            [0]   et_vcm_sel：ET VCM选择
                  0:0.9V      1:0.9V
   UNION结构 ：无 */
#define ABB_ET_ET_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x901)

/* 寄存器说明：APT模式配置寄存器，经过线控逻辑后送至
   详      述：[7:6] reserved
            [5]：ET_CLK_SEL：选择CH0还是CH1支持ET。
   UNION结构 ：无 */
#define ABB_ET_APT_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x902)

/* 寄存器说明：APT模式配置寄存器，经过线控逻辑后送至
   详      述：[7:1] reserved
            [0]   et_vcm_sel：ET VCM选择
                  0:0.9V      1:0.9V
   UNION结构 ：无 */
#define ABB_ET_APT_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x903)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至
   详      述：[7:6] reserved
            [5]：ET_CLK_SEL：选择CH0还是CH1支持ET。
   UNION结构 ：无 */
#define ABB_ET_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x904)

/* 寄存器说明：ET模式配置寄存器，经过线控逻辑后送至
   详      述：[7:1] reserved
            [0]   et_vcm_sel：ET VCM选择
                  0:0.9V      1:0.9V
   UNION结构 ：无 */
#define ABB_ET_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x905)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA00)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH0_TX_FC：ch0 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA01)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA02)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA03)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA04)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA05)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA06)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA07)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA08)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH0_TX_FC：ch0 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA09)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA0A)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA0B)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA0C)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA0D)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA0E)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA0F)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA10)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH0_TX_FC：ch0 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
                  10：10MHz  其他模式
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA11)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA12)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA13)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA14)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA15)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA16)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA17)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA18)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH0_TX_FC：ch0 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA19)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA1A)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA1B)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA1C)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA1D)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA1E)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xA1F)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA20)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH0_TX_FC：ch0 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA21)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA22)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA23)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA24)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA25)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA26)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xA27)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH0_PD_TX_I：ch0 tx i路power down控制
                  0: power ON
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA28)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH0_TX_FC：ch0 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA29)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR02
   详      述：[7] CH0_TX_CLKD_CTRL：ch0 tx反向时钟控制
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA2A)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA2B)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA2C)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA2D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA2E)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_TX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xA2F)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:6] reserved
            [5] CH0_TX_DUM_EN_I：ch0 tx i channel dummy logic control signal
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA00_ADDR                  (ABB_BASE_ADDR + 0xA30)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA01_ADDR                  (ABB_BASE_ADDR + 0xA31)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA02_ADDR                  (ABB_BASE_ADDR + 0xA32)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA03_ADDR                  (ABB_BASE_ADDR + 0xA33)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA04_ADDR                  (ABB_BASE_ADDR + 0xA34)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA05_ADDR                  (ABB_BASE_ADDR + 0xA35)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA06_ADDR                  (ABB_BASE_ADDR + 0xA36)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA07_ADDR                  (ABB_BASE_ADDR + 0xA37)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA08_ADDR                  (ABB_BASE_ADDR + 0xA38)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA09_ADDR                  (ABB_BASE_ADDR + 0xA39)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xA3A)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xA3B)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xA3C)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xA3D)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xA3E)

/* 寄存器说明：TX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xA3F)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [4] CH1_PD_TX_Q：ch1 tx q路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [3] reserved
            [2:0] CH1_TX_MODE：ch1 tx模式选择
                  000: LTE(614.4M)
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)（默认）
                  100: X(245.76M)
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA40)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH1_TX_FC：ch1 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
                  10：10MHz  其他模式（默认）
                  11：20MHz LTE模式
            [3:2] CH1_TX_DIV_MODE：ch1 tx div模式选择
                  00:1分频（默认）
            [1:0] CH1_TX_LPF_MODE：ch1 tx LPF运放偏置电流调整
                  运放电流：  op1   op2
                  00：        10u   10u   CA模式
                  01：        5u    5u   LTE模式
                  10：        8u    8u
                  11：        3u    3u    其他模式（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA41)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
                  0：正沿(默认)
                  1：反沿
            [6:4] CH1_TX_LPF_CT：ch1 tx lpf电流调整
                 000：5u（默认）
                  001：2u
                  010：3u
                  011：4u
                  100：6u
                  101：7u
                  110：8u
                  111：9u
            [3:0] CH1_TX_LPF_OP_MODE：ch1 tx lpf运放模式选择
                  0101：CA模式
                 1111：LTE模式
                  1010：其他模式
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA42)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA43)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA44)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA45)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA46)

/* 寄存器说明：TX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA47)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [4] CH1_PD_TX_Q：ch1 tx q路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [3] reserved
            [2:0] CH1_TX_MODE：ch1 tx模式选择
                  000: LTE(614.4M)
                  001: 3G(307.2M)（默认）
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA48)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH1_TX_FC：ch1 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
                  10：10MHz  其他模式（默认）
                  11：20MHz LTE模式
            [3:2] CH1_TX_DIV_MODE：ch1 tx div模式选择
                  00:1分频（默认）
            [1:0] CH1_TX_LPF_MODE：ch1 tx LPF运放偏置电流调整
                  运放电流：  op1   op2
                  00：        10u   10u   CA模式
                  01：        5u    5u   LTE模式
                  10：        8u    8u
                  11：        3u    3u    其他模式（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA49)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
                  0：正沿(默认)
                  1：反沿
            [6:4] CH1_TX_LPF_CT：ch1 tx lpf电流调整
                 000：5u（默认）
                  001：2u
                  010：3u
                  011：4u
                  100：6u
                  101：7u
                  110：8u
                  111：9u
            [3:0] CH1_TX_LPF_OP_MODE：ch1 tx lpf运放模式选择
                  0101：CA模式
                 1111：LTE模式
                  1010：其他模式
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA4A)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA4B)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA4C)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA4D)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA4E)

/* 寄存器说明：TX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA4F)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [4] CH1_PD_TX_Q：ch1 tx q路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [3] reserved
            [2:0] CH1_TX_MODE：ch1 tx模式选择
                  000: LTE(614.4M)（默认）
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA50)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH1_TX_FC：ch1 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
                  10：10MHz  其他模式
                  11：20MHz LTE模式 （默认）
            [3:2] CH1_TX_DIV_MODE：ch1 tx div模式选择
                  00:1分频（默认）
            [1:0] CH1_TX_LPF_MODE：ch1 tx LPF运放偏置电流调整
                  运放电流：  op1   op2
                  00：        10u   10u   CA模式
                  01：        5u    5u   LTE模式（默认）
                  10：        8u    8u
                  11：        3u    3u    其他模式
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA51)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
                  0：正沿(默认)
                  1：反沿
            [6:4] CH1_TX_LPF_CT：ch1 tx lpf电流调整
                 000：5u（默认）
                  001：2u
                  010：3u
                  011：4u
                  100：6u
                  101：7u
                  110：8u
                  111：9u
            [3:0] CH1_TX_LPF_OP_MODE：ch1 tx lpf运放模式选择
                  0101：CA模式
                 1111：LTE模式（默认）
                  1010：其他模式
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA52)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA53)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA54)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA55)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA56)

/* 寄存器说明：TX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA57)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [4] CH1_PD_TX_Q：ch1 tx q路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [3] reserved
            [2:0] CH1_TX_MODE：ch1 tx模式选择
                  000: LTE(614.4M)
                  001: 3G(307.2M)（默认）
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA58)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH1_TX_FC：ch1 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
                  10：10MHz  其他模式 （默认）
                  11：20MHz LTE模式
            [3:2] CH1_TX_DIV_MODE：ch1 tx div模式选择
                  00:1分频（默认）
            [1:0] CH1_TX_LPF_MODE：ch1 tx LPF运放偏置电流调整
                  运放电流：  op1   op2
                  00：        10u   10u   CA模式
                  01：        5u    5u   LTE模式
                  10：        8u    8u
                  11：        3u    3u    其他模式（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA59)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
                  0：正沿(默认)
                  1：反沿
            [6:4] CH1_TX_LPF_CT：ch1 tx lpf电流调整
                 000：5u（默认）
                  001：2u
                  010：3u
                  011：4u
                  100：6u
                  101：7u
                  110：8u
                  111：9u
            [3:0] CH1_TX_LPF_OP_MODE：ch1 tx lpf运放模式选择
                  0101：CA模式
                 1111：LTE模式
                  1010：其他模式（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA5A)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA5B)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA5C)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA5D)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA5E)

/* 寄存器说明：TX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xA5F)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [4] CH1_PD_TX_Q：ch1 tx q路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [3] reserved
            [2:0] CH1_TX_MODE：ch1 tx模式选择
                  000: LTE(614.4M)
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA60)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH1_TX_FC：ch1 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
                  10：10MHz  其他模式 （默认）
                  11：20MHz LTE模式
            [3:2] CH1_TX_DIV_MODE：ch1 tx div模式选择
                  00:1分频（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA61)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
                  0：正沿(默认)
                  1：反沿
            [6:4] CH1_TX_LPF_CT：ch1 tx lpf电流调整
                 000：5u（默认）
                  001：2u
                  010：3u
                  011：4u
                  100：6u
                  101：7u
                  110：8u
                  111：9u
            [3:0] CH1_TX_LPF_OP_MODE：ch1 tx lpf运放模式选择
                  0101：CA模式
                 1111：LTE模式
                  1010：其他模式（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA62)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA63)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA64)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA65)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA66)

/* 寄存器说明：TX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xA67)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR00
   详      述：[7:6] reserved
            [5] CH1_PD_TX_I：ch1 tx i路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [4] CH1_PD_TX_Q：ch1 tx q路power down控制
                  0: power ON
                 1: power DOWN（默认）
            [3] reserved
            [2:0] CH1_TX_MODE：ch1 tx模式选择
                  000: LTE(614.4M)
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)（默认）
                  100: X(245.76M)
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA68)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR01
   详      述：[7:6] reserved
            [5:4] CH1_TX_FC：ch1 tx fc选择
                  00：20MHz
                  01：40MHz  CA模式
                  10：10MHz  其他模式（默认）
                  11：20MHz LTE模式
            [3:2] CH1_TX_DIV_MODE：ch1 tx div模式选择
                  00:1分频（默认）
            [1:0] CH1_TX_LPF_MODE：ch1 tx LPF运放偏置电流调整
                  运放电流：  op1   op2
                  00：        10u   10u   CA模式
                  01：        5u    5u   LTE模式
                  10：        8u    8u
                  11：        3u    3u    其他模式（默认）
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA69)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR02
   详      述：[7] CH1_TX_CLKD_CTRL：ch1 tx反向时钟控制
                  0：正沿(默认)
                  1：反沿
            [6:4] CH1_TX_LPF_CT：ch1 tx lpf电流调整
                 000：5u（默认）
                  001：2u
                  010：3u
                  011：4u
                  100：6u
                  101：7u
                  110：8u
                  111：9u
            [3:0] CH1_TX_LPF_OP_MODE：ch1 tx lpf运放模式选择
                  0101：CA模式
                 1111：LTE模式
                  1010：其他模式
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA6A)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR03
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA6B)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR04
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA6C)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR05
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA6D)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR06
   详      述：
            [7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA6E)

/* 寄存器说明：TX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR07
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_TX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xA6F)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:6] reserved
            [5] CH1_TX_DUM_EN_I：ch1 tx i channel dummy logic control signal
                  1：enable(默认)
                  0：disable
            [4] CH1_TX_DUM_EN_Q：ch1 tx q channel dummy logic control signal
                  1：enable(默认)
                  0：disable
            [3] reserved
            [2] CH1_TX_VCM_SEL：ch1 TXDAC LPF共模电压选择：
                  0：VCM=650mV（针对TXDAC输出共模电压为650mV的情况）
                  1：VCM=500mV（针对TXDAC输出共模电压为500mV的情况）(默认)
            [1:0] CH1_TX_VCM_SWITCH：ch1 TX内部通过灌电流调整LPF输入端的共模电压
                  00：共模电压不调整（针对TXDAC输出共模电压为650mV的情况）
                  01：共模电压增加145mV（针对TXDAC输出共模电压为500mV的情况）
                  10：共模电压增加21mV（用于Debug）
                  11：共模电压增加166mV（用于Debug）
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA00_ADDR                  (ABB_BASE_ADDR + 0xA70)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA01_ADDR                  (ABB_BASE_ADDR + 0xA71)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA02_ADDR                  (ABB_BASE_ADDR + 0xA72)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA03_ADDR                  (ABB_BASE_ADDR + 0xA73)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA04_ADDR                  (ABB_BASE_ADDR + 0xA74)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA05_ADDR                  (ABB_BASE_ADDR + 0xA75)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA06_ADDR                  (ABB_BASE_ADDR + 0xA76)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA07_ADDR                  (ABB_BASE_ADDR + 0xA77)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA08_ADDR                  (ABB_BASE_ADDR + 0xA78)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA09_ADDR                  (ABB_BASE_ADDR + 0xA79)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xA7A)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xA7B)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xA7C)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xA7D)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xA7E)

/* 寄存器说明：TX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xA7F)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC00)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT2：ch0 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC01)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7] CH0_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH0_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH0_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH0_MODE_IBCT3：ch0 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC02)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC03)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC04)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC05)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE：ch0 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH0_RX_CAP2_MODE：ch0 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH0_RX_CAP1_MODE：ch0 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC06)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC07)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC08)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH0_MULTI_RATE_CAP2：ch0 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH0_MULTI_RATE_CAP1：ch0 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC09)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC0A)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC0B)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC0C)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC0D)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC0E)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH0_RX_2G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC0F)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC10)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT2：ch0 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC11)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7] CH0_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH0_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH0_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH0_MODE_IBCT3：ch0 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC12)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC13)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC14)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC15)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE：ch0 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH0_RX_CAP2_MODE：ch0 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH0_RX_CAP1_MODE：ch0 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC16)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC17)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC18)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH0_MULTI_RATE_CAP2：ch0 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH0_MULTI_RATE_CAP1：ch0 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC19)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC1A)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC1B)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC1C)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC1D)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC1E)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH0_RX_3G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC1F)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC20)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT2：ch0 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC21)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7] CH0_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH0_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH0_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH0_MODE_IBCT3：ch0 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC22)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC23)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC24)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC25)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE：ch0 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH0_RX_CAP2_MODE：ch0 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH0_RX_CAP1_MODE：ch0 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC26)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC27)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC28)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH0_MULTI_RATE_CAP2：ch0 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH0_MULTI_RATE_CAP1：ch0 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC29)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC2A)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC2B)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC2C)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC2D)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC2E)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH0_RX_4G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC2F)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xC30)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT2：ch0 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xC31)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7] CH0_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH0_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH0_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH0_MODE_IBCT3：ch0 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xC32)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xC33)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xC34)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xC35)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE：ch0 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH0_RX_CAP2_MODE：ch0 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH0_RX_CAP1_MODE：ch0 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xC36)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xC37)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xC38)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH0_MULTI_RATE_CAP2：ch0 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH0_MULTI_RATE_CAP1：ch0 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xC39)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xC3A)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xC3B)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xC3C)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xC3D)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xC3E)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH0_RX_TDS_ANA_16_ADDR                    (ABB_BASE_ADDR + 0xC3F)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xC40)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT2：ch0 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xC41)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7] CH0_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH0_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH0_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH0_MODE_IBCT3：ch0 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xC42)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xC43)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xC44)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xC45)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE：ch0 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH0_RX_CAP2_MODE：ch0 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH0_RX_CAP1_MODE：ch0 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xC46)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xC47)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xC48)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH0_MULTI_RATE_CAP2：ch0 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH0_MULTI_RATE_CAP1：ch0 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xC49)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xC4A)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xC4B)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xC4C)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xC4D)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xC4E)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH0_RX_X_ANA_16_ADDR                      (ABB_BASE_ADDR + 0xC4F)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR08
   详      述：[7] CH0_PD_RXA_I：ch0 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH0_PD_RXA_Q：ch0 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH0_PD_RXB_I：ch0 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH0_PD_RXB_Q：ch0 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH0_RX_MODE：ch0 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xC50)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH0_MODE_IBCT2：ch0 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1：ch0 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xC51)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR10
   详      述：[7] CH0_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH0_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH0_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH0_MODE_IBCT3：ch0 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xC52)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR11
   详      述：[7:6] CH0_CTRL_RFF：ch0 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH0_CTRL_RIN1：ch0 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH0_CTRL_RIN2：ch0 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH0_CTRL_RIN3：ch0 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH0_CTRL_RFB：ch0 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xC53)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH0_CTRL_RSIG：ch0 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH0_CTRL_RZ：ch0 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xC54)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR13
   详      述：[7:6] reserved
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xC55)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE：ch0 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH0_RX_CAP2_MODE：ch0 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH0_RX_CAP1_MODE：ch0 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xC56)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH0_IBCT_OP2：ch0 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP1：ch0 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xC57)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH0_IBCT_DAC：ch0 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP3：ch0 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xC58)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3：ch0 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH0_MULTI_RATE_CAP2：ch0 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH0_MULTI_RATE_CAP1：ch0 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xC59)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR18
   详      述：[7] CH0_RXA_DCLK_INV：ch0 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_RXB_DCLK_INV：ch0 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKDIV2_A2D：ch0 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX：ch0 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH0_DCLK_A2D_INV：ch0 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH0_CLKMUX_CTRL：ch0 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xC5A)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xC5B)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL：ch0 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xC5C)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xC5D)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL：ch0 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xC5E)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH0_REG_ANALOG_WR23
   详      述：[7] CH0_CLKIN3_INV_RXB_Q：ch0 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH0_CLKIN3_INV_RXB_I：ch0 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH0_CLKIN2_INV_RXB_Q：ch0 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH0_CLKIN2_INV_RXB_I：ch0 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH0_CLKIN3_INV_RXA_Q：ch0 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH0_CLKIN3_INV_RXA_I：ch0 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH0_CLKIN2_INV_RXA_Q：ch0 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH0_CLKIN2_INV_RXA_I：ch0 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH0_RX_IDLE_ANA_16_ADDR                   (ABB_BASE_ADDR + 0xC5F)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] CH0_REG_TUNE1：ch0 rx cap1手动配置寄存器
                0100 0000(默认)
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xC60)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] CH0_REG_TUNE2：ch0 rx cap2手动配置寄存器
                0100 0000(默认)
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xC61)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] CH0_REG_TUNE3：ch0 rx cap3手动配置寄存器
                0100 0000(默认)
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xC62)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] CH0_RX_TUNE_SEL
                0：tuning码来自于rctune模块
                1：tuning码来自于寄存器配置
            [6:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xC63)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] reserved
            [6:4] CH0_OL_CTRL：ch0 rx overload控制选择
                000：16个连续最大码或者最小码，同时触发int1，int2，int3（默认）
                001：8个连续最大码或者最小码，同时触发int1，int2，int3
                010：4个连续最大码或者最小码，同时触发int1，int2，int3
                011：关闭Overload检测，同时触发int1，int2，int3
                100：16个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                101：8个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                110：4个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                111：关闭Overload检测，触发顺序为int3-->int2-->int1
            [3:2] reserved
            [1] CH0_PUP_CLK_CTRL：ch0 rx 启动上电时钟控制
                0：上电完成后关闭上电模块的时钟（默认）
                1：上电完成后不关闭上电模块时钟
            [0] CH0_PUP_MODE：ch0 rx 启动上电模式
                0：自动模式（默认）
                1：配置寄存器上电模式
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xC64)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] CH0_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP3
                1：不Reset CAP3
            [6] CH0_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP2
                1：不Reset CAP2
            [5] CH0_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP1
                1：不Reset CAP1
            [4] CH0_PUP_CTRL：配置寄存器上电模式时ADC中OP控制
                0：OP Power Down
                1：OP Power On
            [3] CH0_PUP_CTRL：配置寄存器上电模式时ADC中DAC控制
                0：DAC Power Down
                1：DAC Power On
            [2] CH0_PUP_CTRL：配置寄存器上电模式时ADC中QT校正控制
                0：QT Calibration On
                1：QT Calibration Off
            [1] CH0_PUP_CTRL：配置寄存器上电模式时ADC中CLKGEN控制
                0：CLKGEN Power Down
                1：CLKGEN Power On
            [0] CH0_PUP_CTRL：配置寄存器上电模式时ADC中QT控制
                0：QT Power Down
                1：QT Power On
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xC65)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:6] reserved
            [5] CH0_QT_REF_SEL：ch0 rx qt的ref选择
                0：vrefp/vrefn来自于ref模块（默认）
                1：vrefp/vrefn来自于本地分压
            [4] CH0_EN_QTCAL：ch0 rx qt校准enable
                0：比较器校准Disable（默认）
                1：比较器校准Enable（默认）
            [3] CH0_CAL_SW：ch0 rx op1校准开关控制
                0：默认
                1：调整
            [2] CH0_CAL_TRIM_SW：ch0 rx op1校准trim开关控制
                0：cal trim开关disable（默认）
                1：cal trim开关enable（默认）
            [1] CH0_OPCAL_VCM_SEL：ch0 rx op1校准共模选择
                0：op1校准短接输入端共模Disable（默认）
                1：op1校准短接输入端共模Enable（默认）
            [0] CH0_EN_OPCAL：ch0 rx op1校准enable
                0：op1校准Disable（默认）
                1：op1校准Enable（默认）
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xC66)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] CH0_VCM_PATH_CTRL_Q：ch0 rxb q路环路测试通路选择vcm
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [6] CH0_VCM_PATH_CTRL_I：ch0 rxb i路环路测试通路选择vcm
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [5] CH0_TX_PATH_CTRL_Q：ch0 rxb q路环路测试通路选择tx
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [4] CH0_TX_PATH_CTRL_I：ch0 rxb i路环路测试通路选择tx
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [3] CH0_RXB_PATH_CTRL_Q：ch0 rxb q路环路测试通路选择rxb，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [2] CH0_RXB_PATH_CTRL_I：ch0 rxb i路环路测试通路选择rxb，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [1] CH0_RXA_PATH_CTRL_Q：ch0 rxa q路环路测试通路选择rxa，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [0] CH0_RXA_PATH_CTRL_I：ch0 rxa i路环路测试通路选择rxa，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xC67)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] CH0_RXA_SE_CTRLP_Q：ch0 rxa q路单端模式p输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [6] CH0_RXA_SE_CTRLN_Q：ch0 rxa q路单端模式n输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [5] CH0_RXA_SE_CTRLP_I：ch0 rxa i路单端模式p输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [4] CH0_RXA_SE_CTRLN_I：ch0 rxa i路单端模式n输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [3:2] CH0_RXA_MODE_IBCT_SE：ch0 rxa 单端模式vcm buffer运放模式选择
                11：CA模式
                10：LTE模式
                01：WDC模式
                00：W3G模式
            [1] CH0_RXA_PD_SE_Q：ch0 rxa i路单端模式vcm buffer运放power down控制
                0：power on
                1：power down
            [0] CH0_RXA_PD_SE_I：ch0 rxa q路单端模式vcm buffer运放power down控制
                0：power on
                1：power down
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xC68)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] CH0_RXB_SE_CTRLP_Q：ch0 rxb q路单端模式p输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [6] CH0_RXB_SE_CTRLN_Q：ch0 rxb q路单端模式n输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [5] CH0_RXB_SE_CTRLP_I：ch0 rxb i路单端模式p输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [4] CH0_RXB_SE_CTRLN_I：ch0 rxb i路单端模式n输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [3:2] CH0_RXB_MODE_IBCT_SE：ch0 rxb 单端模式vcm buffer运放模式选择
                11：CA模式
                10：LTE模式
                01：WDC模式
                00：W3G模式
            [1] CH0_RXB_PD_SE_Q：ch0 rxb i路单端模式vcm buffer运放power down控制
                0：power on
                1：power down
            [0] CH0_RXB_PD_SE_I：ch0 rxb q路单端模式vcm buffer运放power down控制
                0：power on
                1：power down
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xC69)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7] reserved
            [6:4] CH0_IBCT_OPS：ch0 rxb 单端模式电流调整
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH0_IBCT_OP4：内部悬空
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
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

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xC6E)

/* 寄存器说明：RX ch0配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH0_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xC6F)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH1_PD_RXA_I：ch1 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH1_PD_RXA_Q：ch1 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH1_PD_RXB_I：ch1 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH1_PD_RXB_Q：ch1 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH1_RX_MODE：ch1 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC80)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH1_MODE_IBCT2：ch1 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1：ch1 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC81)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7] CH1_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH1_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH1_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH1_MODE_IBCT3：ch1 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC82)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH1_CTRL_RFF：ch1 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH1_CTRL_RIN1：ch1 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH1_CTRL_RIN2：ch1 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH1_CTRL_RIN3：ch1 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH1_CTRL_RFB：ch1 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC83)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH1_CTRL_RSIG：ch1 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH1_CTRL_RZ：ch1 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC84)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:6] reserved
            [5] CH1_ADC_CLK_DIV2：ch1 adc输出时钟2分频控制
                  0：1分频 其他模式
                  1：2分频 2GA模式
            [4] CH1_DLY_CTRL2：ch1 0.6ts时钟周期控制选择
                  0：0.5Ts
                  1：0.6Ts
            [3] reserved
            [2] CH1_DCTRL23：ch1 dac23电流模式选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [1:0] CH1_DCTRL1：ch1 dac1电流模式选择
                00：2GA/W3G模式
                01：Reserved
                10：WDC/TDS/X模式
                01：CA/LTE/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC85)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE：ch1 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH1_RX_CAP2_MODE：ch1 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH1_RX_CAP1_MODE：ch1 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC86)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH1_IBCT_OP2：ch1 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP1：ch1 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC87)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH1_IBCT_DAC：ch1 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP3：ch1 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC88)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3：ch1 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH1_MULTI_RATE_CAP2：ch1 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH1_MULTI_RATE_CAP1：ch1 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC89)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH1_RXA_DCLK_INV：ch1 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_RXB_DCLK_INV：ch1 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKDIV2_A2D：ch1 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX：ch1 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH1_DCLK_A2D_INV：ch1 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH1_CLKMUX_CTRL：ch1 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC8A)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC8B)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC8C)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC8D)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC8E)

/* 寄存器说明：RX 2G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH1_CLKIN3_INV_RXB_Q：ch1 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_CLKIN3_INV_RXB_I：ch1 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKIN2_INV_RXB_Q：ch1 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH1_CLKIN2_INV_RXB_I：ch1 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH1_CLKIN3_INV_RXA_Q：ch1 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH1_CLKIN3_INV_RXA_I：ch1 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH1_CLKIN2_INV_RXA_Q：ch1 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH1_CLKIN2_INV_RXA_I：ch1 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH1_RX_2G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC8F)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH1_PD_RXA_I：ch1 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH1_PD_RXA_Q：ch1 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH1_PD_RXB_I：ch1 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH1_PD_RXB_Q：ch1 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH1_RX_MODE：ch1 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC90)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH1_MODE_IBCT2：ch1 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1：ch1 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC91)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7] CH1_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH1_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH1_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH1_MODE_IBCT3：ch1 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC92)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH1_CTRL_RFF：ch1 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH1_CTRL_RIN1：ch1 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH1_CTRL_RIN2：ch1 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH1_CTRL_RIN3：ch1 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH1_CTRL_RFB：ch1 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC93)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH1_CTRL_RSIG：ch1 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH1_CTRL_RZ：ch1 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC94)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:6] reserved
            [5] CH1_ADC_CLK_DIV2：ch1 adc输出时钟2分频控制
                  0：1分频 其他模式
                  1：2分频 2GA模式
            [4] CH1_DLY_CTRL2：ch1 0.6ts时钟周期控制选择
                  0：0.5Ts
                  1：0.6Ts
            [3] reserved
            [2] CH1_DCTRL23：ch1 dac23电流模式选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [1:0] CH1_DCTRL1：ch1 dac1电流模式选择
                00：2GA/W3G模式
                01：Reserved
                10：WDC/TDS/X模式
                01：CA/LTE/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC95)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE：ch1 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH1_RX_CAP2_MODE：ch1 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH1_RX_CAP1_MODE：ch1 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC96)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH1_IBCT_OP2：ch1 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP1：ch1 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC97)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH1_IBCT_DAC：ch1 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP3：ch1 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC98)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3：ch1 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH1_MULTI_RATE_CAP2：ch1 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH1_MULTI_RATE_CAP1：ch1 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC99)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH1_RXA_DCLK_INV：ch1 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_RXB_DCLK_INV：ch1 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKDIV2_A2D：ch1 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX：ch1 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH1_DCLK_A2D_INV：ch1 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH1_CLKMUX_CTRL：ch1 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC9A)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC9B)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC9C)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC9D)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC9E)

/* 寄存器说明：RX 3G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH1_CLKIN3_INV_RXB_Q：ch1 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_CLKIN3_INV_RXB_I：ch1 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKIN2_INV_RXB_Q：ch1 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH1_CLKIN2_INV_RXB_I：ch1 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH1_CLKIN3_INV_RXA_Q：ch1 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH1_CLKIN3_INV_RXA_I：ch1 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH1_CLKIN2_INV_RXA_Q：ch1 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH1_CLKIN2_INV_RXA_I：ch1 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH1_RX_3G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC9F)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH1_PD_RXA_I：ch1 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH1_PD_RXA_Q：ch1 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH1_PD_RXB_I：ch1 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH1_PD_RXB_Q：ch1 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH1_RX_MODE：ch1 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xCA0)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH1_MODE_IBCT2：ch1 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1：ch1 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xCA1)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7] CH1_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH1_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH1_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH1_MODE_IBCT3：ch1 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xCA2)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH1_CTRL_RFF：ch1 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH1_CTRL_RIN1：ch1 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH1_CTRL_RIN2：ch1 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH1_CTRL_RIN3：ch1 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH1_CTRL_RFB：ch1 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xCA3)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH1_CTRL_RSIG：ch1 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH1_CTRL_RZ：ch1 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xCA4)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:6] reserved
            [5] CH1_ADC_CLK_DIV2：ch1 adc输出时钟2分频控制
                  0：1分频 其他模式
                  1：2分频 2GA模式
            [4] CH1_DLY_CTRL2：ch1 0.6ts时钟周期控制选择
                  0：0.5Ts
                  1：0.6Ts
            [3] reserved
            [2] CH1_DCTRL23：ch1 dac23电流模式选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [1:0] CH1_DCTRL1：ch1 dac1电流模式选择
                00：2GA/W3G模式
                01：Reserved
                10：WDC/TDS/X模式
                01：CA/LTE/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xCA5)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE：ch1 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH1_RX_CAP2_MODE：ch1 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH1_RX_CAP1_MODE：ch1 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xCA6)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH1_IBCT_OP2：ch1 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP1：ch1 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xCA7)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH1_IBCT_DAC：ch1 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP3：ch1 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xCA8)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3：ch1 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH1_MULTI_RATE_CAP2：ch1 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH1_MULTI_RATE_CAP1：ch1 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xCA9)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH1_RXA_DCLK_INV：ch1 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_RXB_DCLK_INV：ch1 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKDIV2_A2D：ch1 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX：ch1 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH1_DCLK_A2D_INV：ch1 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH1_CLKMUX_CTRL：ch1 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xCAA)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xCAB)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xCAC)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xCAD)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xCAE)

/* 寄存器说明：RX 4G配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH1_CLKIN3_INV_RXB_Q：ch1 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_CLKIN3_INV_RXB_I：ch1 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKIN2_INV_RXB_Q：ch1 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH1_CLKIN2_INV_RXB_I：ch1 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH1_CLKIN3_INV_RXA_Q：ch1 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH1_CLKIN3_INV_RXA_I：ch1 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH1_CLKIN2_INV_RXA_Q：ch1 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH1_CLKIN2_INV_RXA_I：ch1 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH1_RX_4G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xCAF)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH1_PD_RXA_I：ch1 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH1_PD_RXA_Q：ch1 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH1_PD_RXB_I：ch1 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH1_PD_RXB_Q：ch1 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH1_RX_MODE：ch1 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xCB0)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH1_MODE_IBCT2：ch1 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1：ch1 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xCB1)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7] CH1_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH1_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH1_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH1_MODE_IBCT3：ch1 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xCB2)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH1_CTRL_RFF：ch1 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH1_CTRL_RIN1：ch1 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH1_CTRL_RIN2：ch1 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH1_CTRL_RIN3：ch1 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH1_CTRL_RFB：ch1 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xCB3)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH1_CTRL_RSIG：ch1 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH1_CTRL_RZ：ch1 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xCB4)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:6] reserved
            [5] CH1_ADC_CLK_DIV2：ch1 adc输出时钟2分频控制
                  0：1分频 其他模式
                  1：2分频 2GA模式
            [4] CH1_DLY_CTRL2：ch1 0.6ts时钟周期控制选择
                  0：0.5Ts
                  1：0.6Ts
            [3] reserved
            [2] CH1_DCTRL23：ch1 dac23电流模式选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [1:0] CH1_DCTRL1：ch1 dac1电流模式选择
                00：2GA/W3G模式
                01：Reserved
                10：WDC/TDS/X模式
                01：CA/LTE/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xCB5)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE：ch1 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH1_RX_CAP2_MODE：ch1 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH1_RX_CAP1_MODE：ch1 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xCB6)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH1_IBCT_OP2：ch1 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP1：ch1 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xCB7)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH1_IBCT_DAC：ch1 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP3：ch1 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xCB8)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3：ch1 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH1_MULTI_RATE_CAP2：ch1 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH1_MULTI_RATE_CAP1：ch1 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xCB9)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH1_RXA_DCLK_INV：ch1 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_RXB_DCLK_INV：ch1 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKDIV2_A2D：ch1 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX：ch1 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH1_DCLK_A2D_INV：ch1 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH1_CLKMUX_CTRL：ch1 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xCBA)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xCBB)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xCBC)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xCBD)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xCBE)

/* 寄存器说明：RX TDS配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH1_CLKIN3_INV_RXB_Q：ch1 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_CLKIN3_INV_RXB_I：ch1 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKIN2_INV_RXB_Q：ch1 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH1_CLKIN2_INV_RXB_I：ch1 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH1_CLKIN3_INV_RXA_Q：ch1 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH1_CLKIN3_INV_RXA_I：ch1 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH1_CLKIN2_INV_RXA_Q：ch1 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH1_CLKIN2_INV_RXA_I：ch1 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH1_RX_TDS_ANA_16_ADDR                    (ABB_BASE_ADDR + 0xCBF)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH1_PD_RXA_I：ch1 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH1_PD_RXA_Q：ch1 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH1_PD_RXB_I：ch1 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH1_PD_RXB_Q：ch1 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH1_RX_MODE：ch1 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xCC0)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH1_MODE_IBCT2：ch1 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1：ch1 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xCC1)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7] CH1_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH1_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH1_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH1_MODE_IBCT3：ch1 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xCC2)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH1_CTRL_RFF：ch1 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH1_CTRL_RIN1：ch1 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH1_CTRL_RIN2：ch1 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH1_CTRL_RIN3：ch1 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH1_CTRL_RFB：ch1 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xCC3)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH1_CTRL_RSIG：ch1 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH1_CTRL_RZ：ch1 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xCC4)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:6] reserved
            [5] CH1_ADC_CLK_DIV2：ch1 adc输出时钟2分频控制
                  0：1分频 其他模式
                  1：2分频 2GA模式
            [4] CH1_DLY_CTRL2：ch1 0.6ts时钟周期控制选择
                  0：0.5Ts
                  1：0.6Ts
            [3] reserved
            [2] CH1_DCTRL23：ch1 dac23电流模式选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [1:0] CH1_DCTRL1：ch1 dac1电流模式选择
                00：2GA/W3G模式
                01：Reserved
                10：WDC/TDS/X模式
                01：CA/LTE/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xCC5)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE：ch1 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH1_RX_CAP2_MODE：ch1 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH1_RX_CAP1_MODE：ch1 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xCC6)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH1_IBCT_OP2：ch1 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP1：ch1 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xCC7)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH1_IBCT_DAC：ch1 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP3：ch1 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xCC8)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3：ch1 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH1_MULTI_RATE_CAP2：ch1 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH1_MULTI_RATE_CAP1：ch1 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xCC9)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH1_RXA_DCLK_INV：ch1 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_RXB_DCLK_INV：ch1 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKDIV2_A2D：ch1 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX：ch1 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH1_DCLK_A2D_INV：ch1 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH1_CLKMUX_CTRL：ch1 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xCCA)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xCCB)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xCCC)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xCCD)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xCCE)

/* 寄存器说明：RX X配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH1_CLKIN3_INV_RXB_Q：ch1 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_CLKIN3_INV_RXB_I：ch1 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKIN2_INV_RXB_Q：ch1 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH1_CLKIN2_INV_RXB_I：ch1 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH1_CLKIN3_INV_RXA_Q：ch1 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH1_CLKIN3_INV_RXA_I：ch1 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH1_CLKIN2_INV_RXA_Q：ch1 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH1_CLKIN2_INV_RXA_I：ch1 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH1_RX_X_ANA_16_ADDR                      (ABB_BASE_ADDR + 0xCCF)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR08
   详      述：[7] CH1_PD_RXA_I：ch1 rxa i路power down控制
                0：Power on
                1：Power Down（默认）
            [6] CH1_PD_RXA_Q：ch1 rxa q路power down控制
                0：Power on
                1：Power Down（默认）
            [5] CH1_PD_RXB_I：ch1 rxb i路power down控制
                0：Power on
                1：Power Down（默认）
            [4] CH1_PD_RXB_Q：ch1 rxb q路power down控制
                0：Power on
                1：Power Down（默认）
            [3] reserved
            [2:0] CH1_RX_MODE：ch1 rx模式选择
                000：LTE模式
                001：W3G模式
                010：WDC模式
                011：2GA/2GB模式
                100：CA模式
                101：X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xCD0)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR09
   详      述：[7:6] reserved
            [5:4] CH1_MODE_IBCT2：ch1 op2模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1：ch1 op1模式选择
                00：W3G模式
                01：WDC模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xCD1)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR10
   详      述：[7] CH1_DEM_ENB
                0:DEM Enable(默认)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
            [3] CH1_PDM_CTRL
                0:求和编码(默认)
                1:解码器编码
            [2] CH1_DEM_OUTPUT_SEL
                0:求和编码(默认)
                1:解码器编码
            [1:0] CH1_MODE_IBCT3：ch1 op3模式选择
                00：W3G/2GA模式
                01：WDC/X/2GB模式
                10：LTE模式
                11：CA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xCD2)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR11
   详      述：[7:6] CH1_CTRL_RFF：ch1 前馈电阻rff选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/X/TDS模式
            [5:4] CH1_CTRL_RIN1：ch1 积分器1输入电阻rin1选择
                00：Off
                01：WDC/TDS/X模式
                10：2GA/W3G模式
                11：CA/LTE/2GB模式
            [3:2] CH1_CTRL_RIN2：ch1 积分器2输入电阻rin2选择
                00：Off
                01：2GA/2GB/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X模式
            [1] CH1_CTRL_RIN3：ch1 积分器3输入电阻rin3选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [0] CH1_CTRL_RFB：ch1 积分器反馈电阻rfb选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xCD3)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR12
   详      述：[7:6] reserved
            [5:4] CH1_CTRL_RSIG：ch1 积分器信号前馈电阻rsig选择
                00：Off
                01：2GA/W3G模式
                10：Reserved
                11：CA/LTE/WDC/TDS/X/2GB模式
            [3:0] CH1_CTRL_RZ：ch1 积分器3调零电阻rz选择
                x000：320 ohm
                x100：160 ohm
                x110：80 ohm
                xxx1：0 ohm（默认1111）
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xCD4)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR13
   详      述：[7:6] reserved
            [5] CH1_ADC_CLK_DIV2：ch1 adc输出时钟2分频控制
                  0：1分频 其他模式
                  1：2分频 2GA模式
            [4] CH1_DLY_CTRL2：ch1 0.6ts时钟周期控制选择
                  0：0.5Ts
                  1：0.6Ts
            [3] reserved
            [2] CH1_DCTRL23：ch1 dac23电流模式选择
                0：2GA/W3G模式
                1：CA/LTE/WDC/TDS/X/2GB模式
            [1:0] CH1_DCTRL1：ch1 dac1电流模式选择
                00：2GA/W3G模式
                01：Reserved
                10：WDC/TDS/X模式
                01：CA/LTE/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xCD5)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR14
   详      述：[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE：ch1 积分器3电容cap3模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [3:2] CH1_RX_CAP2_MODE：ch1 积分器2电容cap2模式选择
                00：CA模式
                01：LTE模式
                10：WDC/TDS/X/W3G/2GA/2GB模式
            [1:0] CH1_RX_CAP1_MODE：ch1 积分器1电容cap1模式选择
                01：CA模式
                10：LTE/WDC/TDS/X/W3G/2GA/2GB模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xCD6)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR15
   详      述：[7] reserved
            [6:4] CH1_IBCT_OP2：ch1 rx op2电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP1：ch1 rx op1电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xCD7)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR16
   详      述：[7] reserved
            [6:4] CH1_IBCT_DAC：ch1 rx dac电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
            [3] reserved
            [2:0] CH1_IBCT_OP3：ch1 rx op3电流大小调节
                000：5u（默认）
                001：4u
                010：3u
                011：2u
                100：10u
                101：9u
                110：8u
                111：7u
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xCD8)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR17
   详      述：[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3：ch1 rx积分器3电容cap3乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [3:2] CH1_MULTI_RATE_CAP2：ch1 rx积分器2电容cap2乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
            [1:0] CH1_MULTI_RATE_CAP1：ch1 rx积分器1电容cap1乘积倍数选择
                00：1倍 其他模式
                10：1.25倍 X模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xCD9)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR18
   详      述：[7] CH1_RXA_DCLK_INV：ch1 rxa dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_RXB_DCLK_INV：ch1 rxb dclk反向控制选择
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKDIV2_A2D：ch1 rx a2d clock二分频选择
                0：选择二分频后输出 CA/2GA/2GB模式
                1：不分频输出 LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX：ch1 rx clock二分频选择
                0：选择二分频后输出 W3G模式
                1：不分频输出 其他模式
            [3] CH1_DCLK_A2D_INV：ch1 rx a2d clock反向选择
                0：正沿采样（默认）
                1：反沿采样
            [2:0] CH1_CLKMUX_CTRL：ch1 rx 模式分频时钟选择
               000：8分频 CA模式
               001：4分频 LTE模式
               011：2分频 WDC/TDS/X/2GB模式
               111：1分频 W3G/2GA模式
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xCDA)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR19
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xCDB)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR20
   详      述：[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL：ch1 rxa qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xCDC)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR21
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xCDD)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR22
   详      述：[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL：ch1 rxb qt延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xCDE)

/* 寄存器说明：RX IDLE配置寄存器，经过线控逻辑后送至CH1_REG_ANALOG_WR23
   详      述：[7] CH1_CLKIN3_INV_RXB_Q：ch1 rxb q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [6] CH1_CLKIN3_INV_RXB_I：ch1 rxb i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [5] CH1_CLKIN2_INV_RXB_Q：ch1 rxb q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [4] CH1_CLKIN2_INV_RXB_I：ch1 rxb i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [3] CH1_CLKIN3_INV_RXA_Q：ch1 rxa q路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [2] CH1_CLKIN3_INV_RXA_I：ch1 rxa i路clkin3 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [1] CH1_CLKIN2_INV_RXA_Q：ch1 rxa q路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
            [0] CH1_CLKIN2_INV_RXA_I：ch1 rxa i路clkin2 dff正反沿控制
                0：正沿采样（默认）
                1：反沿采样
   UNION结构 ：无 */
#define ABB_CH1_RX_IDLE_ANA_16_ADDR                   (ABB_BASE_ADDR + 0xCDF)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] CH1_REG_TUNE1：ch1 rx cap1手动配置寄存器
                0100 0000(默认)
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xCE0)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] CH1_REG_TUNE2：ch1 rx cap2手动配置寄存器
                0100 0000(默认)
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xCE1)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] CH1_REG_TUNE3：ch1 rx cap3手动配置寄存器
                0100 0000(默认)
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xCE2)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7] CH1_RX_TUNE_SEL
                0：tuning码来自于rctune模块
                1：tuning码来自于寄存器配置
            [6:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xCE3)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7] reserved
            [6:4] CH1_OL_CTRL：ch1 rx overload控制选择
                000：16个连续最大码或者最小码，同时触发int1，int2，int3（默认）
                001：8个连续最大码或者最小码，同时触发int1，int2，int3
                010：4个连续最大码或者最小码，同时触发int1，int2，int3
                011：关闭Overload检测，同时触发int1，int2，int3
                100：16个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                101：8个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                110：4个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                111：关闭Overload检测，触发顺序为int3-->int2-->int1
            [3:2] reserved
            [1] CH1_PUP_CLK_CTRL：ch1 rx 启动上电时钟控制
                0：上电完成后关闭上电模块的时钟（默认）
                1：上电完成后不关闭上电模块时钟
            [0] CH1_PUP_MODE：ch1 rx 启动上电模式
                0：自动模式（默认）
                1：配置寄存器上电模式
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xCE4)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7] CH1_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP3
                1：不Reset CAP3
            [6] CH1_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP2
                1：不Reset CAP2
            [5] CH1_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP1
                1：不Reset CAP1
            [4] CH1_PUP_CTRL：配置寄存器上电模式时ADC中OP控制
                0：OP Power Down
                1：OP Power On
            [3] CH1_PUP_CTRL：配置寄存器上电模式时ADC中DAC控制
                0：DAC Power Down
                1：DAC Power On
            [2] CH1_PUP_CTRL：配置寄存器上电模式时ADC中QT校正控制
                0：QT Calibration On
                1：QT Calibration Off
            [1] CH1_PUP_CTRL：配置寄存器上电模式时ADC中CLKGEN控制
                0：CLKGEN Power Down
                1：CLKGEN Power On
            [0] CH1_PUP_CTRL：配置寄存器上电模式时ADC中QT控制
                0：QT Power Down
                1：QT Power On
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xCE5)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:6] reserved
            [5] CH1_QT_REF_SEL：ch1 rx qt的ref选择
                0：vrefp/vrefn来自于ref模块（默认）
                1：vrefp/vrefn来自于本地分压
            [4] CH1_EN_QTCAL：ch1 rx qt校准enable
                0：比较器校准Disable（默认）
                1：比较器校准Enable（默认）
            [3] CH1_CAL_SW：ch1 rx op1校准开关控制
                0：默认
                1：调整
            [2] CH1_CAL_TRIM_SW：ch1 rx op1校准trim开关控制
                0：cal trim开关disable（默认）
                1：cal trim开关enable（默认）
            [1] CH1_OPCAL_VCM_SEL：ch1 rx op1校准共模选择
                0：op1校准短接输入端共模Disable（默认）
                1：op1校准短接输入端共模Enable（默认）
            [0] CH1_EN_OPCAL：ch1 rx op1校准enable
                0：op1校准Disable（默认）
                1：op1校准Enable（默认）
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xCE6)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:4] reserved
            [3] CH1_RXB_PATH_CTRL_Q：ch1 rxb q路环路测试通路选择rxb，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [2] CH1_RXB_PATH_CTRL_I：ch1 rxb i路环路测试通路选择rxb，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [1] CH1_RXA_PATH_CTRL_Q：ch1 rxa q路环路测试通路选择rxa，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [0] CH1_RXA_PATH_CTRL_I：ch1 rxa i路环路测试通路选择rxa，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xCE7)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xCE8)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xCE9)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xCEA)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0xCEB)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0xCEC)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0xCED)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xCEE)

/* 寄存器说明：RX ch1配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_CH1_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xCEF)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] reserved
            [5] CH3_PD_RXC_Q：ch3 rxc q路power down控制
            0:Power On
            1:Power Down（默认）
            [4] CH3_PD_RXC_I：ch3 rxc i路power down控制
            0:Power On
            1:Power Down（默认）
            [3] CH3_PD_RXB_Q：ch3 rxb q路power down控制
            0:Power On
            1:Power Down（默认）
            [2] CH3_PD_RXB_I：ch3 rxb i路power down控制
            0:Power On
            1:Power Down（默认）
            [1] CH3_PD_RXA_Q：ch3 rxa q路power down控制
            0:Power On
            1:Power Down（默认）
            [0] CH3_PD_RXA_I：ch3 rxa i路power down控制
            0:Power On
            1:Power Down（默认）
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR26_ADDR                      (ABB_BASE_ADDR + 0xE00)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:3] reserved
            [2:0] CH3_RX_MODE：ch3 rx模式选择
            000：CA模式
            001：3G模式，X模式
            010：3G模式，X模式
            011：2G模式
            100：50M模式
            101：LTE模式
            110：LTE模式
            111：LTE模式
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR27_ADDR                      (ABB_BASE_ADDR + 0xE01)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] reserved
            [5:4] CH3_MODE_IBCT2：ch3 op2电流模式选择
            00：3G模式&amp;2G模式&amp;X模式
            01：LTE模式
            10：CA模式
            11：50M模式
            [3:2] reserved
            [1:0] CH3_MODE_IBCT1：ch3 op1电流模式选择
            00：3G模式&amp;2G模式&amp;X模式
            01：LTE模式
            10：CA模式
            11：50M模式
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR28_ADDR                      (ABB_BASE_ADDR + 0xE02)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] reserved
            [5:4] CH3_MODE_IBCT4：ch3 op4电流模式选择
            00：3G模式&amp;2G模式&amp;X模式
            01：LTE模式
            10：CA模式
            11：50M模式
            [3:2] reserved
            [1:0] CH3_MODE_IBCT3：ch3 op3电流模式选择
            00：3G模式&amp;2G模式&amp;X模式
            01：LTE模式
            10：CA模式
            11：50M模式
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR29_ADDR                      (ABB_BASE_ADDR + 0xE03)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] CH3_CTRL_RFF：ch3 前馈电阻rff选择
            0：LTE模式&amp;3G模式&amp;2G模式&amp;X模式
            1：50M模式&amp;CA模式
            [6:5] CH3_CTRL_RIN1：ch3 积分器1输入电阻rin1选择
            00：50M模式
            01：CA模式
            10：LTE模式
            11：3G模式&amp;2G模式&amp;X模式
            [4] CH3_CTRL_RIN2：ch3 积分器2输入电阻rin2选择
            0：LTE模式&amp;3G模式&amp;2G模式&amp;X模式
            1：50M模式&amp;CA模式
            [3] CH3_CTRL_RIN3：ch3 积分器3输入电阻rin3选择
            0：LTE模式&amp;3G模式&amp;2G模式&amp;X模式
            1：50M模式&amp;CA模式
            [2] CH3_CTRL_RIN4：ch3 积分器4输入电阻rin4选择
            0：LTE模式&amp;3G模式&amp;2G模式&amp;X模式
            1：50M模式&amp;CA模式
            [1:0] CH3_CTRL_RSIG：ch3 积分器信号前馈电阻rsig选择
            00：OFF
            01：LTE模式&amp;3G模式&amp;2G模式&amp;X模式
            10：50M模式&amp;CA模式
            11：50M模式&amp;CA模式
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR30_ADDR                      (ABB_BASE_ADDR + 0xE04)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] CH3_CTRL_RFB1：ch3 积分器反馈电阻rfb1选择
            00：50M模式
            01：CA模式
            10：LTE模式
            11：3G模式&amp;2G模式&amp;X模式
            [5:4] CH3_CTRL_RFB2：ch3 积分器反馈电阻rfb2选择
            00：LTE模式&amp;3G模式&amp;2G模式&amp;X模式(notch2配成40M模式)
            01：LTE模式&amp;3G模式&amp;2G模式&amp;X模式(notch2配成50M模式)
            10：50M模式&amp;CA模式(notch2配成40M模式)
            11：50M模式&amp;CA模式(notch2配成50M模式)
            [3:0] CH3_CTRL_RZ：ch3 积分器3调零电阻rz选择
            1111：所有模式默认为1111
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR31_ADDR                      (ABB_BASE_ADDR + 0xE05)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:4] reserved
            [3] CH3_DCTRL234：ch3 dac234电流模式选择
            0：LTE模式&amp;3G模式&amp;2G模式&amp;X模式
            1：50M模式&amp;CA模式
            [2:0] CH3_DCTRL1：ch3 dac1电流模式选择
            000：不工作
            001：3G模式&amp;2G模式&amp;X模式
            010：LTE模式
            011：CA模式
            111：50M模式
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR32_ADDR                      (ABB_BASE_ADDR + 0xE06)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] reserved
            [5:4] CH3_RX_CAP4_MODE：ch3 积分器4电容cap4模式选择
            00：不用
            01：50M模式&amp;LTE模式，电容*1
            10：CA模式&amp;3G模式&amp;2G模式&amp;X模式，电容*2
            11：不用
            [3:2] CH3_RX_CAP23_MODE：ch3 积分器23电容cap23模式选择
            00：不用
            01：50M模式&amp;LTE模式，电容*1
            10：CA模式&amp;3G模式&amp;2G模式&amp;X模式，电容*2
            11：不用
            [1:0] CH3_RX_CAP1_MODE：ch3 积分器1电容cap1模式选择
            00：不用
            01：50M模式&amp;CA模式&amp;LTE模式&amp;3G模式&amp;2G模式&amp;X模式
            10：不用
            11：不用
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR33_ADDR                      (ABB_BASE_ADDR + 0xE07)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] reserved
            [6:4] CH3_IBCT_OP2：ch3 rx op2电流大小调节
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u
            [3] reserved
            [2:0] CH3_IBCT_OP1：ch3 rx op1电流大小调节
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR34_ADDR                      (ABB_BASE_ADDR + 0xE08)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] reserved
            [6:4] CH3_IBCT_OP4：ch3 rx op4电流大小调节
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u
            [3] reserved
            [2:0] CH3_IBCT_OP3：ch3 rx op3电流大小调节
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR35_ADDR                      (ABB_BASE_ADDR + 0xE09)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] reserved
            [6:4] CH3_IBCT_OPS：ch3 rx 单端模式运放电流大小调节
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u
            [3] reserved
            [2:0] CH3_IBCT_DAC：ch3 rx dac电流大小调节
            000：5u
            001：4u
            010：3u
            011：2u
            100：9u
            101：8u
            110：7u
            111：6u
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR36_ADDR                      (ABB_BASE_ADDR + 0xE0A)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] reserved
            [6:4] CH3_MULTI_RATE_CAP23：ch3 rx积分器23电容cap23乘积倍数选择
            000：X1
            001：X1.5
            010：X1.25
            011：X1.125
            100：X1.0625
            101：X1.5625
            110：X1.3125
            111：X1.1875
            [3] reserved
            [2:0] CH3_MULTI_RATE_CAP1：ch3 rx积分器1电容cap1乘积倍数选择
            000：X1
            001：X1.5
            010：X1.25
            011：X1.125
            100：X1.0625
            101：X1.5625
            110：X1.3125
            111：X1.1875
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR37_ADDR                      (ABB_BASE_ADDR + 0xE0B)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:3] reserved
            [2:0] CH3_MULTI_RATE_CAP4：ch3 rx积分器4电容cap4乘积倍数选择
            000：X1
            001：X1.5
            010：X1.25
            011：X1.125
            100：X1.0625
            101：X1.5625
            110：X1.3125
            111：X1.1875
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR38_ADDR                      (ABB_BASE_ADDR + 0xE0C)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] reserved
            [5] CH3_CLKDIV2_A2D：ch3 rx a2d clock二分频选择
            0：选择2分频
            1：不选择2分频
            [4] CH3_CLKDIV2_RX：ch3 rx clock二分频选择
            0：选择2分频
            1：不选择2分频
            [3] reserved
            [2:0] CH3_CLKMUX_CTRL：ch3 rx 模式分频时钟选择
            000：8分频
            001：4分频
            011：2分频
            111：1分频
            其他不用
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR39_ADDR                      (ABB_BASE_ADDR + 0xE0D)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:4] reserved
            [3] CH3_DCLK_A2D_INV：ch3 dclk反向选择
            0：不反相
            1：反相
            [2] CH3_RXC_DCLK_INV：ch3 rxc sync2dig模块dclk反向选择
            0：采用正沿打拍
            1：采用反沿打拍
            [1] CH3_RXB_DCLK_INV：ch3 rxb sync2dig模块dclk反向选择
            0：采用正沿打拍
            1：采用反沿打拍
            [0] CH3_RXA_DCLK_INV：ch3 rxa sync2dig模块dclk反向选择
            0：采用正沿打拍
            1：采用反沿打拍
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR40_ADDR                      (ABB_BASE_ADDR + 0xE0E)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:5] reserved
            [4:0] CH3_RXA_CLK_DAC3_CTRL：ch3 rxa dac3延时选择
                00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR41_ADDR                      (ABB_BASE_ADDR + 0xE0F)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:5] reserved
            [4:0] CH3_RXA_CLK_DAC3_CTRL：ch3 rxa qt延时选择
            00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR42_ADDR                      (ABB_BASE_ADDR + 0xE10)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:5] reserved
            [4:0] CH3_RXB_CLK_DAC3_CTRL：ch3 rxb dac3延时选择
            00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR43_ADDR                      (ABB_BASE_ADDR + 0xE11)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:5] reserved
            [4:0] CH3_RXB_CLK_DAC3_CTRL：ch3 rxb qt延时选择
            00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR44_ADDR                      (ABB_BASE_ADDR + 0xE12)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:5] reserved
            [4:0] CH3_RXC_CLK_DAC3_CTRL：ch3 rxc dac3延时选择
            00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR45_ADDR                      (ABB_BASE_ADDR + 0xE13)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:5] reserved
            [4:0] CH3_RXC_CLK_DAC3_CTRL：ch3 rxc qt延时选择
            00000：4ps
                00001：25ps
                00010：47ps
                00011：69ps
                00100：90ps
                00101：112ps
                00110：134ps
                00111：156ps
                01000：177ps
                01001：199ps
                01010：222ps
                …
                11110：667ps
                11111：688ps
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR46_ADDR                      (ABB_BASE_ADDR + 0xE14)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] CH3_CLKIN3_INV_RXB_Q：ch3 rxb q路clkin3 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [6] CH3_CLKIN3_INV_RXB_I：ch3 rxb i路clkin3 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [5] CH3_CLKIN2_INV_RXB_Q：ch3 rxb q路clkin2 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [4] CH3_CLKIN2_INV_RXB_I：ch3 rxb i路clkin2 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [3] CH3_CLKIN3_INV_RXA_Q：ch3 rxa q路clkin3 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [2] CH3_CLKIN3_INV_RXA_I：ch3 rxa i路clkin3 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [1] CH3_CLKIN2_INV_RXA_Q：ch3 rxa q路clkin2 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [0] CH3_CLKIN2_INV_RXA_I：ch3 rxa i路clkin2 dff正反沿控制
            0：正沿控制
            1：反沿控制
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR47_ADDR                      (ABB_BASE_ADDR + 0xE15)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:4] reserved
            [3] CH3_CLKIN3_INV_RXA_Q：ch3 rxa q路clkin3 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [2] CH3_CLKIN3_INV_RXA_I：ch3 rxa i路clkin3 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [1] CH3_CLKIN2_INV_RXA_Q：ch3 rxa q路clkin2 dff正反沿控制
            0：正沿控制
            1：反沿控制
            [0] CH3_CLKIN2_INV_RXA_I：ch3 rxa i路clkin2 dff正反沿控制
            0：正沿控制
            1：反沿控制
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR48_ADDR                      (ABB_BASE_ADDR + 0xE16)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR49_ADDR                      (ABB_BASE_ADDR + 0xE17)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR50_ADDR                      (ABB_BASE_ADDR + 0xE18)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:1] reserved
            [0] CH3_RX_TUNE_SEL：ch3 rx tuning码选择
                0：tuning码来自于rctune模块
                1：tuning码来自于寄存器配置
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR51_ADDR                      (ABB_BASE_ADDR + 0xE19)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] CH3_REG_TUNE1：ch3 rx cap1手动配置寄存器
            0100 0000(默认)
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR52_ADDR                      (ABB_BASE_ADDR + 0xE1A)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] CH3_REG_TUNE23：ch3 rx cap23手动配置寄存器
            0100 0000(默认)
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR53_ADDR                      (ABB_BASE_ADDR + 0xE1B)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] CH3_REG_TUNE4：ch3 rx cap4手动配置寄存器
            0100 0000(默认)
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR54_ADDR                      (ABB_BASE_ADDR + 0xE1C)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] reserved
            [6] CH3_PDM_CTRL：ch3 rx pdm码控制选择
                0:求和编码(默认)
                1:解码器编码
            [5] CH3_DEM_OUTPUT_SEL：ch3 rx dem输出模式选择
             0:求和编码(默认)
                1:解码器编码
            [4] CH3_DEM_ENB：ch3 rx dem enable选择
                0:DEM Enable(默认)
                1:DEM Disable
            [3] reserved
            [2:0] CH3_DEM_MODE：ch3 rx dem模式选择
                000:DWA模式（默认）
                001:CLA1模式
                010:CLA2模式
                …
                111:CLA7模式
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR55_ADDR                      (ABB_BASE_ADDR + 0xE1D)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] reserved
            [6:4] CH3_OL_CTRL：ch3 rx overload控制选择
                000：16个连续最大码或者最小码，同时触发int1，int2，int3（默认）
                001：8个连续最大码或者最小码，同时触发int1，int2，int3
                010：4个连续最大码或者最小码，同时触发int1，int2，int3
                011：关闭Overload检测，同时触发int1，int2，int3
                100：16个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                101：8个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                110：4个连续最大码或者最小码，触发顺序为int3-->int2-->int1
                111：关闭Overload检测，触发顺序为int3-->int2-->int1
            [3:2] reserved
            [1] CH3_PUP_CLK_CTRL：ch3 rx 启动上电时钟选择
                0：上电完成后关闭上电模块的时钟（默认）
                1：上电完成后不关闭上电模块时钟
            [0] CH3_PUP_MODE：ch3 rx 启动上电模式
                0：自动模式（默认）
                1：配置寄存器上电模式
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR56_ADDR                      (ABB_BASE_ADDR + 0xE1E)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] CH3_PUP_CTRL：ch3 rx 启动上电控制
            [7] CH3_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP3
                1：不Reset CAP3
            [6] CH3_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP2
                1：不Reset CAP2
            [5] CH3_PUP_CTRL：配置寄存器上电模式时ADC中RST_CAP控制
                0：Reset CAP1
                1：不Reset CAP1
            [4] CH3_PUP_CTRL：配置寄存器上电模式时ADC中OP控制
                0：OP Power Down
                1：OP Power On
            [3] CH3_PUP_CTRL：配置寄存器上电模式时ADC中DAC控制
                0：DAC Power Down
                1：DAC Power On
            [2] CH3_PUP_CTRL：配置寄存器上电模式时ADC中QT校正控制
                0：QT Calibration On
                1：QT Calibration Off
            [1] CH3_PUP_CTRL：配置寄存器上电模式时ADC中CLKGEN控制
                0：CLKGEN Power Down
                1：CLKGEN Power On
            [0] CH3_PUP_CTRL：配置寄存器上电模式时ADC中QT控制
                0：QT Power Down
                1：QT Power On
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR57_ADDR                      (ABB_BASE_ADDR + 0xE1F)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] reserved
            [5] CH3_QT_REF_SEL：ch0 rx qt的ref选择
                0：vrefp/vrefn来自于ref模块（默认）
                1：vrefp/vrefn来自于本地分压
            [4] CH3_EN_QTCAL：ch0 rx qt校准enable
                0：比较器校准Disable（默认）
                1：比较器校准Enable（默认）
            [3] CH3_CAL_SW：ch0 rx op1校准开关控制
                0：默认
                1：调整
            [2] CH3_CAL_TRIM_SW：ch0 rx op1校准trim开关控制
                0：cal trim开关disable（默认）
                1：cal trim开关enable（默认）
            [1] CH3_OPCAL_VCM_SEL：ch0 rx op1校准共模选择
                0：op1校准短接输入端共模Disable（默认）
                1：op1校准短接输入端共模Enable（默认）
            [0] CH3_EN_OPCAL：ch0 rx op1校准enable
                0：op1校准Disable（默认）
                1：op1校准Enable（默认）
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR58_ADDR                      (ABB_BASE_ADDR + 0xE20)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:6] reserved
            [5] CH3_RXC_PATH_CTRL_Q：ch3 rxb q路环路测试通路选择rxc，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [4] CH3_RXC_PATH_CTRL_I：ch3 rxb i路环路测试通路选择rxc，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [3] CH3_RXB_PATH_CTRL_Q：ch3 rxb q路环路测试通路选择rxb，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [2] CH3_RXB_PATH_CTRL_I：ch3 rxb i路环路测试通路选择rxb，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [1] CH3_RXA_PATH_CTRL_Q：ch3 rxa q路环路测试通路选择rxa，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
            [0] CH3_RXA_PATH_CTRL_I：ch3 rxa i路环路测试通路选择rxa，正常工作模式
                0：通路断开，不选择该通路
                1：通路导通，选择该通路
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR59_ADDR                      (ABB_BASE_ADDR + 0xE21)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7] CH3_RXA_SE_CTRLP_Q：ch3 rxa q路单端模式p输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [6] CH3_RXA_SE_CTRLN_Q：ch3 rxa q路单端模式n输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [5] CH3_RXA_SE_CTRLP_I：ch3 rxa i路单端模式p输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [4] CH3_RXA_SE_CTRLN_I：ch3 rxa i路单端模式n输入端控制选择
                0：不导通，将此端反馈dac的输出接固定电平
                1：导通，将此端反馈dac的输出接至运放输入
            [3:2] CH3_RXA_MODE_IBCT_SE：ch3 rxa 单端模式vcm buffer运放模式选择
                11：CA模式
                10：LTE模式
                01：WDC模式
                00：W3G模式
            [1] CH3_RXA_PD_SE_Q：ch3 rxa i路单端模式vcm buffer运放power down控制
                0：power on
                1：power down
            [0] CH3_RXA_PD_SE_I：ch3 rxa q路单端模式vcm buffer运放power down控制
                0：power on
                1：power down
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR60_ADDR                      (ABB_BASE_ADDR + 0xE22)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR61_ADDR                      (ABB_BASE_ADDR + 0xE23)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR62_ADDR                      (ABB_BASE_ADDR + 0xE24)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR63_ADDR                      (ABB_BASE_ADDR + 0xE25)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR64_ADDR                      (ABB_BASE_ADDR + 0xE26)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR65_ADDR                      (ABB_BASE_ADDR + 0xE27)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR66_ADDR                      (ABB_BASE_ADDR + 0xE28)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR67_ADDR                      (ABB_BASE_ADDR + 0xE29)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR68_ADDR                      (ABB_BASE_ADDR + 0xE2A)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR69_ADDR                      (ABB_BASE_ADDR + 0xE2B)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR70_ADDR                      (ABB_BASE_ADDR + 0xE2C)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR71_ADDR                      (ABB_BASE_ADDR + 0xE2D)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR72_ADDR                      (ABB_BASE_ADDR + 0xE2E)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR73_ADDR                      (ABB_BASE_ADDR + 0xE2F)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR74_ADDR                      (ABB_BASE_ADDR + 0xE30)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR75_ADDR                      (ABB_BASE_ADDR + 0xE31)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR76_ADDR                      (ABB_BASE_ADDR + 0xE32)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR77_ADDR                      (ABB_BASE_ADDR + 0xE33)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR78_ADDR                      (ABB_BASE_ADDR + 0xE34)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR79_ADDR                      (ABB_BASE_ADDR + 0xE35)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR80_ADDR                      (ABB_BASE_ADDR + 0xE36)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR81_ADDR                      (ABB_BASE_ADDR + 0xE37)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR82_ADDR                      (ABB_BASE_ADDR + 0xE38)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR83_ADDR                      (ABB_BASE_ADDR + 0xE39)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR84_ADDR                      (ABB_BASE_ADDR + 0xE3A)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR85_ADDR                      (ABB_BASE_ADDR + 0xE3B)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR86_ADDR                      (ABB_BASE_ADDR + 0xE3C)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR87_ADDR                      (ABB_BASE_ADDR + 0xE3D)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR88_ADDR                      (ABB_BASE_ADDR + 0xE3E)

/* 寄存器说明：RX 测试通道配置寄存器
   详      述：[7:0] reserved
   UNION结构 ：无 */
#define ABB_REG_ANALOG_WR89_ADDR                      (ABB_BASE_ADDR + 0xE3F)





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
                     (1/1) register_define_abb
 ***======================================================================***/
/*****************************************************************************
 结构名    : ABB_SCPLL0_LOCK_CTRL_UNION
 结构说明  : SCPLL0_LOCK_CTRL 寄存器结构定义。地址偏移量:0x000，初值:0x18，宽度:8
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
 结构说明  : SCPLL0_FBDIV_H 寄存器结构定义。地址偏移量:0x003，初值:0x00，宽度:8
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
 结构说明  : SCPLL0_REFDIV 寄存器结构定义。地址偏移量:0x004，初值:0x01，宽度:8
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
 结构说明  : SCPLL0_CFG_UPDATE 寄存器结构定义。地址偏移量:0x009，初值:0x00，宽度:8
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
 结构说明  : SCPLL1_LOCK_CTRL 寄存器结构定义。地址偏移量:0x00A，初值:0x18，宽度:8
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
 结构说明  : SCPLL1_FBDIV_H 寄存器结构定义。地址偏移量:0x00D，初值:0x00，宽度:8
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
 结构说明  : SCPLL1_REFDIV 寄存器结构定义。地址偏移量:0x00E，初值:0x01，宽度:8
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
 结构说明  : SCPLL1_CFG_UPDATE 寄存器结构定义。地址偏移量:0x013，初值:0x00，宽度:8
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
 结构名    : ABB_GPLL_GATE_TIME_UNION
 结构说明  : GPLL_GATE_TIME 寄存器结构定义。地址偏移量:0x014，初值:0x12，宽度:8
 寄存器说明: GPLL输出时钟门控时间配置
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll_en      : 1;  /* bit[0]  :  */
        unsigned long  gpll_time    : 3;  /* bit[1-3]: GPLL时钟稳定等待时间配置，计数时钟为19.2M：
                                                       000：GPLL开启10us后时钟稳定；
                                                       001：GPLL开启20us后时钟稳定；
                                                       010：GPLL开启50us后时钟稳定；
                                                       011：GPLL开启75us后时钟稳定；
                                                       100：GPLL开启100us后时钟稳定；
                                                       101：GPLL开启115us后时钟稳定；
                                                       110：GPLL1开启125us后时钟稳定；
                                                       default：100us */
        unsigned long  gpll_gate_en : 1;  /* bit[4]  : GPLL时钟门控功能使能，
                                                       0：gpll时钟门控功能关闭；
                                                       1：gpll时钟门控功能打开。 */
        unsigned long  gpll_timeout : 1;  /* bit[5]  : GPLL稳定指示。0表示GPLL未稳定；1表示GPLL稳定。GPLL稳定后有时钟输出。 */
        unsigned long  reserved     : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPLL_GATE_TIME_UNION;
#define ABB_GPLL_GATE_TIME_gpll_en_START       (0)
#define ABB_GPLL_GATE_TIME_gpll_en_END         (0)
#define ABB_GPLL_GATE_TIME_gpll_time_START     (1)
#define ABB_GPLL_GATE_TIME_gpll_time_END       (3)
#define ABB_GPLL_GATE_TIME_gpll_gate_en_START  (4)
#define ABB_GPLL_GATE_TIME_gpll_gate_en_END    (4)
#define ABB_GPLL_GATE_TIME_gpll_timeout_START  (5)
#define ABB_GPLL_GATE_TIME_gpll_timeout_END    (5)


/*****************************************************************************
 结构名    : ABB_WPLL_GATE_TIME_UNION
 结构说明  : WPLL_GATE_TIME 寄存器结构定义。地址偏移量:0x015，初值:0x12，宽度:8
 寄存器说明: WPLL输出时钟门控时间配置
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_en      : 1;  /* bit[0]  :  */
        unsigned long  wpll_time    : 3;  /* bit[1-3]: WPLL时钟稳定等待时间配置，计数时钟为19.2M：
                                                       000：WPLL开启10us后时钟稳定；
                                                       001：WPLL开启20us后时钟稳定；
                                                       010：WPLL开启50us后时钟稳定；
                                                       011：WPLL开启75us后时钟稳定；
                                                       100：WPLL开启100us后时钟稳定；
                                                       101：WPLL开启115us后时钟稳定；
                                                       110：WPLL1开启125us后时钟稳定；
                                                       default：100us */
        unsigned long  wpll_gate_en : 1;  /* bit[4]  : WPLL时钟门控功能使能，
                                                       0：wpll时钟门控功能关闭；
                                                       1：wpll时钟门控功能打开。 */
        unsigned long  wpll_timeout : 1;  /* bit[5]  : WPLL稳定指示。0表示WPLL未稳定；1表示WPLL稳定。WPLL稳定后有时钟输出。 */
        unsigned long  reserved     : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_WPLL_GATE_TIME_UNION;
#define ABB_WPLL_GATE_TIME_wpll_en_START       (0)
#define ABB_WPLL_GATE_TIME_wpll_en_END         (0)
#define ABB_WPLL_GATE_TIME_wpll_time_START     (1)
#define ABB_WPLL_GATE_TIME_wpll_time_END       (3)
#define ABB_WPLL_GATE_TIME_wpll_gate_en_START  (4)
#define ABB_WPLL_GATE_TIME_wpll_gate_en_END    (4)
#define ABB_WPLL_GATE_TIME_wpll_timeout_START  (5)
#define ABB_WPLL_GATE_TIME_wpll_timeout_END    (5)


/*****************************************************************************
 结构名    : ABB_TESTMODE_UNION
 结构说明  : TESTMODE 寄存器结构定义。地址偏移量:0x016，初值:0x00，宽度:8
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
 结构名    : ABB_ABB_DIG_PWR_RST_UNION
 结构说明  : ABB_DIG_PWR_RST 寄存器结构定义。地址偏移量:0x017，初值:0x00，宽度:8
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
 结构说明  : CH0_COMM_REG_DEBUG_DIG 寄存器结构定义。地址偏移量:0x018，初值:0x00，宽度:8
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
 结构说明  : CH1_COMM_REG_DEBUG_DIG 寄存器结构定义。地址偏移量:0x019，初值:0x00，宽度:8
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
 结构说明  : BIST_CFG_1 寄存器结构定义。地址偏移量:0x041，初值:0x00，宽度:8
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
 结构说明  : BIST_CFG_4 寄存器结构定义。地址偏移量:0x044，初值:0x00，宽度:8
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
 结构说明  : BIST_CFG_5 寄存器结构定义。地址偏移量:0x045，初值:0x00，宽度:8
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
 结构说明  : BIST_RPT_1 寄存器结构定义。地址偏移量:0x046，初值:0x00，宽度:8
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
 结构说明  : BIST_RPT_2 寄存器结构定义。地址偏移量:0x047，初值:0x00，宽度:8
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
 结构说明  : BIST_RPT_8 寄存器结构定义。地址偏移量:0x04D，初值:0x00，宽度:8
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
 结构说明  : BIST_RPT_10 寄存器结构定义。地址偏移量:0x04F，初值:0x00，宽度:8
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
 结构说明  : BIST_CFG_6 寄存器结构定义。地址偏移量:0x05A，初值:0x3E，宽度:8
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
 结构说明  : BIST_CFG_8 寄存器结构定义。地址偏移量:0x05C，初值:0x01，宽度:8
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
 结构名    : ABB_ADPLL_LOCK_CTRL_UNION
 结构说明  : ADPLL_LOCK_CTRL 寄存器结构定义。地址偏移量:0x0A1，初值:0x18，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_en      : 1;  /* bit[0]  : ADPLL使能信号。用于通过CFG接口配置打开adpll。 */
        unsigned long  adpll_time    : 3;  /* bit[1-3]: ADPLL时钟稳定等待时间配置，计数时钟为19.2M：
                                                        000：ADPLL开启10us后时钟稳定；
                                                        001：ADPLL开启20us后时钟稳定；
                                                        010：ADPLL开启50us后时钟稳定；
                                                        011：ADPLL开启75us后时钟稳定；
                                                        100：ADPLL开启100us后时钟稳定；
                                                        101：ADPLL开启115us后时钟稳定；
                                                        110：ADPLL1开启125us后时钟稳定；
                                                        default：100us */
        unsigned long  adpll_gate_en : 1;  /* bit[4]  : ADPLL门控使能信号。 */
        unsigned long  adpll_timeout : 1;  /* bit[5]  : ADPLL稳定指示。0表示ADPLL未稳定；1表示ADPLL稳定。ADPLL稳定后有时钟输出。 */
        unsigned long  adpll_lock    : 1;  /* bit[6]  : ADPLL锁定指示。 */
        unsigned long  reserved      : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_LOCK_CTRL_UNION;
#define ABB_ADPLL_LOCK_CTRL_adpll_en_START       (0)
#define ABB_ADPLL_LOCK_CTRL_adpll_en_END         (0)
#define ABB_ADPLL_LOCK_CTRL_adpll_time_START     (1)
#define ABB_ADPLL_LOCK_CTRL_adpll_time_END       (3)
#define ABB_ADPLL_LOCK_CTRL_adpll_gate_en_START  (4)
#define ABB_ADPLL_LOCK_CTRL_adpll_gate_en_END    (4)
#define ABB_ADPLL_LOCK_CTRL_adpll_timeout_START  (5)
#define ABB_ADPLL_LOCK_CTRL_adpll_timeout_END    (5)
#define ABB_ADPLL_LOCK_CTRL_adpll_lock_START     (6)
#define ABB_ADPLL_LOCK_CTRL_adpll_lock_END       (6)


/*****************************************************************************
 结构名    : ABB_ADPLL_FBDIV_H_UNION
 结构说明  : ADPLL_FBDIV_H 寄存器结构定义。地址偏移量:0x0A4，初值:0x00，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_fbdiv_h : 4;  /* bit[0-3]: PLL反馈分频因子fbdiv[11:0]的高4bit； */
        unsigned long  reserved      : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_FBDIV_H_UNION;
#define ABB_ADPLL_FBDIV_H_adpll_fbdiv_h_START  (0)
#define ABB_ADPLL_FBDIV_H_adpll_fbdiv_h_END    (3)


/*****************************************************************************
 结构名    : ABB_ADPLL_REFDIV_UNION
 结构说明  : ADPLL_REFDIV 寄存器结构定义。地址偏移量:0x0A5，初值:0x01，宽度:8
 寄存器说明: SC_PLL分频器因子配置寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_refdiv : 6;  /* bit[0-5]: PLL参考分频因子refdiv[5:0]，默认值为1。 */
        unsigned long  reserved     : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_REFDIV_UNION;
#define ABB_ADPLL_REFDIV_adpll_refdiv_START  (0)
#define ABB_ADPLL_REFDIV_adpll_refdiv_END    (5)


/*****************************************************************************
 结构名    : ABB_ADPLL_CFG_UPDATE_UNION
 结构说明  : ADPLL_CFG_UPDATE 寄存器结构定义。地址偏移量:0x0AA，初值:0x00，宽度:8
 寄存器说明: SC_PLL锁定控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_cfg_update : 1;  /* bit[0]  : ADPLL参数配置更新指示。
                                                           adpll_en打开后，软件配置完adpll_postdiv，adpll_fbdiv，adpll_frac参数，再配置adpll_sfg_update，参数同时更新；adpll_en不打开时，配置参数立即更新，不需要配置adpll_sfg_update。 */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_CFG_UPDATE_UNION;
#define ABB_ADPLL_CFG_UPDATE_adpll_cfg_update_START  (0)
#define ABB_ADPLL_CFG_UPDATE_adpll_cfg_update_END    (0)


/*****************************************************************************
 结构名    : ABB_ADPLL_TEST_CFG_UNION
 结构说明  : ADPLL_TEST_CFG 寄存器结构定义。地址偏移量:0x0B6，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_dcodiv2    : 1;  /* bit[0]  :  */
        unsigned long  adpll_fast_start : 1;  /* bit[1]  :  */
        unsigned long  reserved         : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_TEST_CFG_UNION;
#define ABB_ADPLL_TEST_CFG_adpll_dcodiv2_START     (0)
#define ABB_ADPLL_TEST_CFG_adpll_dcodiv2_END       (0)
#define ABB_ADPLL_TEST_CFG_adpll_fast_start_START  (1)
#define ABB_ADPLL_TEST_CFG_adpll_fast_start_END    (1)


/*****************************************************************************
 结构名    : ABB_ADPLL_CLKSSCG_CFG_UNION
 结构说明  : ADPLL_CLKSSCG_CFG 寄存器结构定义。地址偏移量:0x0B7，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_clksscg_en : 1;  /* bit[0]  :  */
        unsigned long  reserved         : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_CLKSSCG_CFG_UNION;
#define ABB_ADPLL_CLKSSCG_CFG_adpll_clksscg_en_START  (0)
#define ABB_ADPLL_CLKSSCG_CFG_adpll_clksscg_en_END    (0)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_1_UNION
 结构说明  : TX_ET_DIG_1 寄存器结构定义。地址偏移量:0x100，初值:0x40，宽度:8
 寄存器说明: TX ET数字配置寄存器1。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_comp_bp : 1;  /* bit[0]  : ET通道补偿滤波器bypass控制：
                                                     0：不bypass(默认)
                                                     1：bypass */
        unsigned long  et_hb_bp   : 1;  /* bit[1]  : ET通道半带滤波器的bypass信号
                                                     0：不bypass半带滤波器,TX通道输出data rate 为TX CIC rate/2(默认)
                                                     1：bypass半带滤波器,TX通道输出data rate 为TX CIC rate */
        unsigned long  et_sw_rst  : 1;  /* bit[2]  : ET通道软复位寄存器。
                                                     0：不复位；
                                                     1：复位。 */
        unsigned long  reserved_0 : 3;  /* bit[3-5]: 保留 */
        unsigned long  et_ds_bp   : 1;  /* bit[6]  : ET通道降采样bypass信号
                                                     0：不bypass，2倍降采样（默认）；
                                                     1：bypass，不进行降采样。 */
        unsigned long  reserved_1 : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_1_UNION;
#define ABB_TX_ET_DIG_1_et_comp_bp_START  (0)
#define ABB_TX_ET_DIG_1_et_comp_bp_END    (0)
#define ABB_TX_ET_DIG_1_et_hb_bp_START    (1)
#define ABB_TX_ET_DIG_1_et_hb_bp_END      (1)
#define ABB_TX_ET_DIG_1_et_sw_rst_START   (2)
#define ABB_TX_ET_DIG_1_et_sw_rst_END     (2)
#define ABB_TX_ET_DIG_1_et_ds_bp_START    (6)
#define ABB_TX_ET_DIG_1_et_ds_bp_END      (6)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_2_UNION
 结构说明  : TX_ET_DIG_2 寄存器结构定义。地址偏移量:0x101，初值:0x05，宽度:8
 寄存器说明: TX ET数字配置寄存器2。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_gating_en : 1;  /* bit[0]  : ET通道CLOCK GATING控制：
                                                       0：不CLOCK GATING
                                                       1：CLOCK GATING(默认)
                                                       (!et_gating_en)|XX_TX_EN = 1时工作，否则关闭 */
        unsigned long  et_con       : 2;  /* bit[1-2]: TX通道DEM const系数：
                                                       0：0
                                                       1：2
                                                       2：4(默认)
                                                       3：6 */
        unsigned long  et_lsb_value : 1;  /* bit[3]  : ET LSB最低bit输出值配置 */
        unsigned long  reserved_0   : 1;  /* bit[4]  : 保留 */
        unsigned long  et_tx_dwa_en : 1;  /* bit[5]  : ET TX通道DEM模式控制：
                                                       0：使用CLA模式(默认)
                                                       1：使用DWA模式  */
        unsigned long  reserved_1   : 1;  /* bit[6]  : 保留 */
        unsigned long  et_tx_dem_bp : 1;  /* bit[7]  : ET TX通道dem bypass：
                                                       0：DEM打开(默认)
                                                       1：DEM bypass */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_2_UNION;
#define ABB_TX_ET_DIG_2_et_gating_en_START  (0)
#define ABB_TX_ET_DIG_2_et_gating_en_END    (0)
#define ABB_TX_ET_DIG_2_et_con_START        (1)
#define ABB_TX_ET_DIG_2_et_con_END          (2)
#define ABB_TX_ET_DIG_2_et_lsb_value_START  (3)
#define ABB_TX_ET_DIG_2_et_lsb_value_END    (3)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_START  (5)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_END    (5)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_START  (7)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_END    (7)


/*****************************************************************************
 结构名    : ABB_TX_ET_DIG_4_UNION
 结构说明  : TX_ET_DIG_4 寄存器结构定义。地址偏移量:0x103，初值:0x00，宽度:8
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
        unsigned long  et_dig_loop  : 1;  /* bit[5]: ET通道接口环回模式使能。该模式使能，将ET TX数据通过CH1 RX通道环回。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned long  et_alg_loop  : 1;  /* bit[6]: ET通道算法环回模式使能。该模式使能，将ET TX数据通过CH1 RX通道环回。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned long  et_ch_sel    : 1;  /* bit[7]:  */
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
#define ABB_TX_ET_DIG_4_et_ch_sel_START     (7)
#define ABB_TX_ET_DIG_4_et_ch_sel_END       (7)


/*****************************************************************************
 结构名    : ABB_ET_STATE_RPT_UNION
 结构说明  : ET_STATE_RPT 寄存器结构定义。地址偏移量:0x105，初值:0x00，宽度:8
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
        unsigned long  reserved         : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ET_STATE_RPT_UNION;
#define ABB_ET_STATE_RPT_et_comp_overflow_START  (0)
#define ABB_ET_STATE_RPT_et_comp_overflow_END    (0)
#define ABB_ET_STATE_RPT_et_cic6_overflow_START  (1)
#define ABB_ET_STATE_RPT_et_cic6_overflow_END    (1)
#define ABB_ET_STATE_RPT_et_hb_overflow_START    (2)
#define ABB_ET_STATE_RPT_et_hb_overflow_END      (2)


/*****************************************************************************
 结构名    : ABB_ET_SINE_GENERATE_UNION
 结构说明  : ET_SINE_GENERATE 寄存器结构定义。地址偏移量:0x106，初值:0x10，宽度:8
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
 结构说明  : tx_idle_dig_2 寄存器结构定义。地址偏移量:0x201，初值:0x23，宽度:8
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
 结构说明  : tx_idle_dig_3 寄存器结构定义。地址偏移量:0x202，初值:0x01，宽度:8
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
 结构说明  : tx_2g_dig_2 寄存器结构定义。地址偏移量:0x204，初值:0x23，宽度:8
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
 结构说明  : tx_2g_dig_3 寄存器结构定义。地址偏移量:0x205，初值:0x01，宽度:8
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
 结构说明  : tx_c_dig_2 寄存器结构定义。地址偏移量:0x207，初值:0x23，宽度:8
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
 结构说明  : tx_c_dig_3 寄存器结构定义。地址偏移量:0x208，初值:0x09，宽度:8
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
 结构说明  : tx_tds_dig_2 寄存器结构定义。地址偏移量:0x20A，初值:0x23，宽度:8
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
 结构说明  : tx_tds_dig_3 寄存器结构定义。地址偏移量:0x20B，初值:0x01，宽度:8
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
 结构名    : ABB_TX_3G_DIG_1_UNION
 结构说明  : tx_3g_dig_1 寄存器结构定义。地址偏移量:0x20C，初值:0x20，宽度:8
 寄存器说明: TX 3G模式配置寄存器1，由线控决定是否起作用。
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
                                                              2G,     3G,     4G,      TDS,      CDMA,    CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                         0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_3g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G(默认)
                                                         001：3G
                                                         010：4G
                                                         011：TDS
                                                         100：CDMA
                                                         101：CA
                                                         Others：Reserved */
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
 结构说明  : tx_3g_dig_2 寄存器结构定义。地址偏移量:0x20D，初值:0x23，宽度:8
 寄存器说明: TX 3G模式配置寄存器2，由线控决定是否起作用。
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
 结构说明  : tx_3g_dig_3 寄存器结构定义。地址偏移量:0x20E，初值:0x01，宽度:8
 寄存器说明: TX 3G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : 保留 */
        unsigned long  tx_flush_en_3g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  tx_comp_sel_3g : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                         00：固定系数1；
                                                         01：固定系数2；
                                                         10：固定系数3；
                                                         11：可配系数。 */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_3_UNION;
#define ABB_TX_3G_DIG_3_tx_flush_en_3g_START  (1)
#define ABB_TX_3G_DIG_3_tx_flush_en_3g_END    (1)
#define ABB_TX_3G_DIG_3_tx_comp_sel_3g_START  (2)
#define ABB_TX_3G_DIG_3_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 结构名    : ABB_TX_4G_DIG_1_UNION
 结构说明  : tx_4g_dig_1 寄存器结构定义。地址偏移量:0x20F，初值:0x40，宽度:8
 寄存器说明: TX 4G模式配置寄存器1，由线控决定是否起作用。
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
                                                              2G,     3G,     4G,      TDS,      CDMA,    CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                         0：4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(默认)
                                                         1：2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_4g : 3;  /* bit[5-7]: TX通道模式控制：
                                                         000：2G(默认)
                                                         001：3G
                                                         010：4G
                                                         011：TDS
                                                         100：CDMA
                                                         101：CA
                                                         Others：Reserved */
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
 结构说明  : tx_4g_dig_2 寄存器结构定义。地址偏移量:0x210，初值:0x23，宽度:8
 寄存器说明: TX 4G模式配置寄存器2，由线控决定是否起作用。
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
 结构说明  : tx_4g_dig_3 寄存器结构定义。地址偏移量:0x211，初值:0x01，宽度:8
 寄存器说明: TX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : 保留 */
        unsigned long  tx_flush_en_4g : 1;  /* bit[1]  : TX通道FLUSH使能：
                                                         0：不使能
                                                         1：使能 */
        unsigned long  tx_comp_sel_4g : 2;  /* bit[2-3]: TX通道补偿滤波器补偿固定系数选择：
                                                         00：固定系数1；
                                                         01：固定系数2；
                                                         10：固定系数3；
                                                         11：可配系数。 */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_3_UNION;
#define ABB_TX_4G_DIG_3_tx_flush_en_4g_START  (1)
#define ABB_TX_4G_DIG_3_tx_flush_en_4g_END    (1)
#define ABB_TX_4G_DIG_3_tx_comp_sel_4g_START  (2)
#define ABB_TX_4G_DIG_3_tx_comp_sel_4g_END    (3)


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
        unsigned long  ch0_tx_sw_rst : 1;  /* bit[0]  : 数字部分TX通道软复位信号：
                                                        0：不复位(默认)
                                                        1：复位 */
        unsigned long  reserved      : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_TESTMODE_UNION;
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_START  (0)
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_END    (0)


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
 结构名    : ABB_CH1_TX_TESTMODE_UNION
 结构说明  : CH1_TX_TESTMODE 寄存器结构定义。地址偏移量:0x260，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_sw_rst : 1;  /* bit[0]  : 数字部分TX通道软复位信号：
                                                        0：不复位(默认)
                                                        1：复位 */
        unsigned long  reserved      : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_TESTMODE_UNION;
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_START  (0)
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_END    (0)


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
 结构说明  : CH1_TX_REG_DEBUG_DIG0 寄存器结构定义。地址偏移量:0x26C，初值:0x64，宽度:8
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
} ABB_CH1_TX_REG_DEBUG_DIG0_UNION;
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_START   (0)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_END     (0)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dem_mode_START       (1)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dem_mode_END         (1)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_dem_sat_START     (2)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_dem_sat_END       (3)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dither_en_START      (4)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dither_en_END        (4)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tuning_val_en_START  (5)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tuning_val_en_END    (5)
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
 结构名    : ABB_RX_IDLE_DIG_1_UNION
 结构说明  : rx_idle_dig_1 寄存器结构定义。地址偏移量:0x400，初值:0x00，宽度:8
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
                                                              11：固定系数4。 */
        unsigned long  rx_comp_fix_idle    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                              0：系数不固定，由寄存器配置
                                                              1：系数固定 */
        unsigned long  rx_hb_bp_idle       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                              0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                              1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_idle        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                  2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                        /TDS_B/4G_C,        /4G_B,
                                                              00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
                                                              others：reserved */
        unsigned long  rx_mode_dig_idle    : 3;  /* bit[5-7]: RX通道模式控制：
                                                              000：2G_A(默认)
                                                              001：3G_SC/TDS_B/4G_C
                                                              010：4G
                                                              011：3G_DC/4G_B
                                                              100：TDS
                                                              101：CDMA
                                                              110：CA
                                                              111：2G_B */
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
 结构说明  : rx_idle_dig_2 寄存器结构定义。地址偏移量:0x401，初值:0x13，宽度:8
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
 结构名    : ABB_RX_IDLE_DIG_3_UNION
 结构说明  : rx_idle_dig_3 寄存器结构定义。地址偏移量:0x402，初值:0x00，宽度:8
 寄存器说明: RX IDLE模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_idle : 2;  /* bit[0-1]:  */
        unsigned long  reserved         : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_3_UNION;
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_START  (0)
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_2G_DIG_1_UNION
 结构说明  : rx_2g_dig_1 寄存器结构定义。地址偏移量:0x403，初值:0x00，宽度:8
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
                                                            11：固定系数4。 */
        unsigned long  rx_comp_fix_2g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                            0：系数不固定，由寄存器配置
                                                            1：系数固定 */
        unsigned long  rx_hb_bp_2g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                            0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                            1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_2g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
                                                            others：reserved */
        unsigned long  rx_mode_dig_2g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                            000：2G_A(默认)
                                                            001：3G_SC/TDS_B/4G_C
                                                            010：4G
                                                            011：3G_DC/4G_B
                                                            100：TDS
                                                            101：CDMA
                                                            110：CA
                                                            111：2G_B */
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
 结构说明  : rx_2g_dig_2 寄存器结构定义。地址偏移量:0x404，初值:0x13，宽度:8
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
 结构名    : ABB_RX_2G_DIG_3_UNION
 结构说明  : rx_2g_dig_3 寄存器结构定义。地址偏移量:0x405，初值:0x00，宽度:8
 寄存器说明: RX 2G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_2g : 2;  /* bit[0-1]:  */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_3_UNION;
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_START  (0)
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_C_DIG_1_UNION
 结构说明  : rx_c_dig_1 寄存器结构定义。地址偏移量:0x406，初值:0xA6，宽度:8
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
                                                           11：固定系数4。 */
        unsigned long  rx_comp_fix_c    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                           0：系数不固定，由寄存器配置
                                                           1：系数固定 */
        unsigned long  rx_hb_bp_c       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                           0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                           1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_c        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                               2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                     /TDS_B/4G_C,        /4G_B,
                                                           00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
                                                           others：reserved */
        unsigned long  rx_mode_dig_c    : 3;  /* bit[5-7]: RX通道模式控制：
                                                           000：2G_A(默认)
                                                           001：3G_SC/TDS_B/4G_C
                                                           010：4G
                                                           011：3G_DC/4G_B
                                                           100：TDS
                                                           101：CDMA
                                                           110：CA
                                                           111：2G_B */
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
 结构说明  : rx_c_dig_2 寄存器结构定义。地址偏移量:0x407，初值:0x93，宽度:8
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
 结构名    : ABB_RX_C_DIG_3_UNION
 结构说明  : rx_c_dig_3 寄存器结构定义。地址偏移量:0x408，初值:0x00，宽度:8
 寄存器说明: RX C模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_c : 2;  /* bit[0-1]:  */
        unsigned long  reserved      : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_3_UNION;
#define ABB_RX_C_DIG_3_blk_len_sel_c_START  (0)
#define ABB_RX_C_DIG_3_blk_len_sel_c_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_TDS_DIG_1_UNION
 结构说明  : rx_tds_dig_1 寄存器结构定义。地址偏移量:0x409，初值:0x26，宽度:8
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
                                                             11：固定系数4。 */
        unsigned long  rx_comp_fix_tds    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                             0：系数不固定，由寄存器配置
                                                             1：系数固定 */
        unsigned long  rx_hb_bp_tds       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                             0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                             1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_tds        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                       /TDS_B/4G_C,        /4G_B,
                                                             00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
                                                             others：reserved */
        unsigned long  rx_mode_dig_tds    : 3;  /* bit[5-7]: RX通道模式控制：
                                                             000：2G_A(默认)
                                                             001：3G_SC/TDS_B/4G_C
                                                             010：4G
                                                             011：3G_DC/4G_B
                                                             100：TDS
                                                             101：CDMA
                                                             110：CA
                                                             111：2G_B */
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
 结构说明  : rx_tds_dig_2 寄存器结构定义。地址偏移量:0x40A，初值:0xD3，宽度:8
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
 结构名    : ABB_RX_TDS_DIG_3_UNION
 结构说明  : rx_tds_dig_3 寄存器结构定义。地址偏移量:0x40B，初值:0x00，宽度:8
 寄存器说明: RX TDS模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_tds : 2;  /* bit[0-1]:  */
        unsigned long  reserved        : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_3_UNION;
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_START  (0)
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_3G_DIG_1_UNION
 结构说明  : rx_3g_dig_1 寄存器结构定义。地址偏移量:0x40C，初值:0x26，宽度:8
 寄存器说明: RX 3G模式配置寄存器1，由线控决定是否起作用。
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
                                                            11：固定系数4。 */
        unsigned long  rx_comp_fix_3g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                            0：系数不固定，由寄存器配置
                                                            1：系数固定 */
        unsigned long  rx_hb_bp_3g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                            0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                            1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_3g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
                                                            others：reserved */
        unsigned long  rx_mode_dig_3g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                            000：2G_A(默认)
                                                            001：3G_SC/TDS_B/4G_C
                                                            010：4G
                                                            011：3G_DC/4G_B
                                                            100：TDS
                                                            101：CDMA
                                                            110：CA
                                                            111：2G_B */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_1_UNION;
#define ABB_RX_3G_DIG_1_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_3G_DIG_1_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_START     (1)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_END       (1)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_START        (2)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_END          (2)
#define ABB_RX_3G_DIG_1_rx_rate_3g_START         (3)
#define ABB_RX_3G_DIG_1_rx_rate_3g_END           (4)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_START     (5)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_3G_DIG_2_UNION
 结构说明  : rx_3g_dig_2 寄存器结构定义。地址偏移量:0x40D，初值:0x03，宽度:8
 寄存器说明: RX 3G模式配置寄存器2，由线控决定是否起作用。
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
} ABB_RX_3G_DIG_2_UNION;
#define ABB_RX_3G_DIG_2_rxa_pd_3g_START          (0)
#define ABB_RX_3G_DIG_2_rxa_pd_3g_END            (0)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_START          (1)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_END            (1)
#define ABB_RX_3G_DIG_2_gain_sel_3g_START        (2)
#define ABB_RX_3G_DIG_2_gain_sel_3g_END          (3)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_START      (4)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_END        (4)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_START      (5)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_END        (5)
#define ABB_RX_3G_DIG_2_rx_flush_en_3g_START     (6)
#define ABB_RX_3G_DIG_2_rx_flush_en_3g_END       (6)
#define ABB_RX_3G_DIG_2_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_3G_DIG_2_rx_comp_sel_b1_3g_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_3G_DIG_3_UNION
 结构说明  : rx_3g_dig_3 寄存器结构定义。地址偏移量:0x40E，初值:0x00，宽度:8
 寄存器说明: RX 3G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_3g : 2;  /* bit[0-1]:  */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_3_UNION;
#define ABB_RX_3G_DIG_3_blk_len_sel_3g_START  (0)
#define ABB_RX_3G_DIG_3_blk_len_sel_3g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_4G_DIG_1_UNION
 结构说明  : rx_4g_dig_1 寄存器结构定义。地址偏移量:0x40F，初值:0x42，宽度:8
 寄存器说明: RX 4G模式配置寄存器1，由线控决定是否起作用。
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
                                                            11：固定系数4。 */
        unsigned long  rx_comp_fix_4g    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                            0：系数不固定，由寄存器配置
                                                            1：系数固定 */
        unsigned long  rx_hb_bp_4g       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                            0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                            1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  rx_rate_4g        : 2;  /* bit[3-4]: RX通道CIC滤波器输出速率控制(Hz)：
                                                                2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00：2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(默认),122.88M,2.167M,
                                                            others：reserved */
        unsigned long  rx_mode_dig_4g    : 3;  /* bit[5-7]: RX通道模式控制：
                                                            000：2G_A(默认)
                                                            001：3G_SC/TDS_B/4G_C
                                                            010：4G
                                                            011：3G_DC/4G_B
                                                            100：TDS
                                                            101：CDMA
                                                            110：CA
                                                            111：2G_B */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_1_UNION;
#define ABB_RX_4G_DIG_1_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_4G_DIG_1_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_START     (1)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_END       (1)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_START        (2)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_END          (2)
#define ABB_RX_4G_DIG_1_rx_rate_4g_START         (3)
#define ABB_RX_4G_DIG_1_rx_rate_4g_END           (4)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_START     (5)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_END       (7)


/*****************************************************************************
 结构名    : ABB_RX_4G_DIG_2_UNION
 结构说明  : rx_4g_dig_2 寄存器结构定义。地址偏移量:0x410，初值:0x03，宽度:8
 寄存器说明: RX 4G模式配置寄存器2，由线控决定是否起作用。
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
} ABB_RX_4G_DIG_2_UNION;
#define ABB_RX_4G_DIG_2_rxa_pd_4g_START          (0)
#define ABB_RX_4G_DIG_2_rxa_pd_4g_END            (0)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_START          (1)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_END            (1)
#define ABB_RX_4G_DIG_2_gain_sel_4g_START        (2)
#define ABB_RX_4G_DIG_2_gain_sel_4g_END          (3)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_START      (4)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_END        (4)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_START      (5)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_END        (5)
#define ABB_RX_4G_DIG_2_rx_flush_en_4g_START     (6)
#define ABB_RX_4G_DIG_2_rx_flush_en_4g_END       (6)
#define ABB_RX_4G_DIG_2_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_4G_DIG_2_rx_comp_sel_b1_4g_END    (7)


/*****************************************************************************
 结构名    : ABB_RX_4G_DIG_3_UNION
 结构说明  : rx_4g_dig_3 寄存器结构定义。地址偏移量:0x411，初值:0x00，宽度:8
 寄存器说明: RX 4G模式配置寄存器3，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_4g : 2;  /* bit[0-1]:  */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_3_UNION;
#define ABB_RX_4G_DIG_3_blk_len_sel_4g_START  (0)
#define ABB_RX_4G_DIG_3_blk_len_sel_4g_END    (1)


/*****************************************************************************
 结构名    : ABB_RX_EN_DELAY_UNION
 结构说明  : RX_EN_DELAY 寄存器结构定义。地址偏移量:0x420，初值:0x01，宽度:8
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
 结构说明  : COMB_MODE 寄存器结构定义。地址偏移量:0x421，初值:0x00，宽度:8
 寄存器说明: 模式寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  comb_mode : 1;  /* bit[0]  :  */
        unsigned long  reserved  : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_COMB_MODE_UNION;
#define ABB_COMB_MODE_comb_mode_START  (0)
#define ABB_COMB_MODE_comb_mode_END    (0)


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
        unsigned long  reserved_0      : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch0_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_TESTMODE_UNION;
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_START    (0)
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_END      (0)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_START  (1)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_END    (1)
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
        unsigned long  ch0_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  ch0_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  ch0_c1_pll_sel  : 1;  /* bit[3]  :  */
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
 结构名    : ABB_CH0_RXA_I_COEF1_UNION
 结构说明  : ch0_rxa_i_coef1 寄存器结构定义。地址偏移量:0x485，初值:0xC1，宽度:8
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
 结构说明  : ch0_rxa_i_coef3 寄存器结构定义。地址偏移量:0x487，初值:0x41，宽度:8
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
 结构说明  : ch0_rxa_q_coef1 寄存器结构定义。地址偏移量:0x48A，初值:0xC1，宽度:8
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
 结构说明  : ch0_rxa_q_coef3 寄存器结构定义。地址偏移量:0x48C，初值:0x41，宽度:8
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
 结构说明  : ch0_rxb_i_coef1 寄存器结构定义。地址偏移量:0x48F，初值:0xC1，宽度:8
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
 结构说明  : ch0_rxb_i_coef3 寄存器结构定义。地址偏移量:0x491，初值:0x41，宽度:8
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
 结构说明  : ch0_rxb_q_coef1 寄存器结构定义。地址偏移量:0x494，初值:0xC1，宽度:8
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
 结构说明  : ch0_rxb_q_coef3 寄存器结构定义。地址偏移量:0x496，初值:0x41，宽度:8
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
 结构说明  : ch0_reg_rxa_dcr_cfg 寄存器结构定义。地址偏移量:0x498，初值:0x46，宽度:8
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
 结构说明  : ch0_reg_rxb_dcr_cfg 寄存器结构定义。地址偏移量:0x499，初值:0x46，宽度:8
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
 结构说明  : ch0_reg_rx_dcr_ctrl 寄存器结构定义。地址偏移量:0x49A，初值:0x00，宽度:8
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
 结构说明  : ch0_rxa_blocking 寄存器结构定义。地址偏移量:0x49B，初值:0x00，宽度:8
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
 结构说明  : ch0_rxb_blocking 寄存器结构定义。地址偏移量:0x49C，初值:0x00，宽度:8
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
 结构说明  : ch0_reg_rxa_dc_i_2 寄存器结构定义。地址偏移量:0x49E，初值:0x00，宽度:8
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
 结构说明  : ch0_reg_rxa_dc_q_2 寄存器结构定义。地址偏移量:0x4A0，初值:0x00，宽度:8
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
 结构说明  : ch0_reg_rxb_dc_i_2 寄存器结构定义。地址偏移量:0x4A2，初值:0x00，宽度:8
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
 结构说明  : ch0_reg_rxb_dc_q_2 寄存器结构定义。地址偏移量:0x4A4，初值:0x00，宽度:8
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
 结构说明  : CH0_FLUSH_CFG1 寄存器结构定义。地址偏移量:0x4A6，初值:0x40，宽度:8
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
 结构说明  : CH0_RXAI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4A8，初值:0x02，宽度:8
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
 结构说明  : CH0_RXAQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4AA，初值:0x02，宽度:8
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
 结构说明  : CH0_RXBI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4AC，初值:0x02，宽度:8
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
 结构说明  : CH0_RXBQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4AE，初值:0x02，宽度:8
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
 结构说明  : ch0_ctrl 寄存器结构定义。地址偏移量:0x4AF，初值:0x03，宽度:8
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
 结构说明  : ch0_rx_line_sel 寄存器结构定义。地址偏移量:0x4B0，初值:0x00，宽度:8
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
 结构说明  : ch0_rx_line_cfg 寄存器结构定义。地址偏移量:0x4B1，初值:0x00，宽度:8
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
 结构说明  : ch0_blk_cfg 寄存器结构定义。地址偏移量:0x4B2，初值:0x00，宽度:8
 寄存器说明: blk控制寄存器。
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
} ABB_CH0_BLK_CFG_UNION;
#define ABB_CH0_BLK_CFG_ch0_blk_clk_sel_START  (0)
#define ABB_CH0_BLK_CFG_ch0_blk_clk_sel_END    (0)
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_START   (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_END     (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_START   (2)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_END     (2)


/*****************************************************************************
 结构名    : ABB_CH0_RX_REG_DEBUG_DIG_UNION
 结构说明  : ch0_rx_reg_debug_dig 寄存器结构定义。地址偏移量:0x4B5，初值:0x00，宽度:8
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
 结构说明  : CH1_RX_TESTMODE 寄存器结构定义。地址偏移量:0x4C0，初值:0x00，宽度:8
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
        unsigned long  reserved_0      : 2;  /* bit[2-3]: 保留 */
        unsigned long  ch1_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_TESTMODE_UNION;
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_START    (0)
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_END      (0)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_START  (1)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_END    (1)
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
        unsigned long  ch1_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  ch1_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  ch1_c1_pll_sel  : 1;  /* bit[3]  :  */
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
 结构名    : ABB_CH1_RXA_I_COEF1_UNION
 结构说明  : ch1_rxa_i_coef1 寄存器结构定义。地址偏移量:0x4C5，初值:0xC1，宽度:8
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
 结构说明  : ch1_rxa_i_coef3 寄存器结构定义。地址偏移量:0x4C7，初值:0x41，宽度:8
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
 结构说明  : ch1_rxa_q_coef1 寄存器结构定义。地址偏移量:0x4CA，初值:0xC1，宽度:8
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
 结构说明  : ch1_rxa_q_coef3 寄存器结构定义。地址偏移量:0x4CC，初值:0x41，宽度:8
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
 结构说明  : ch1_rxb_i_coef1 寄存器结构定义。地址偏移量:0x4CF，初值:0xC1，宽度:8
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
 结构说明  : ch1_rxb_i_coef3 寄存器结构定义。地址偏移量:0x4D1，初值:0x41，宽度:8
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
 结构说明  : ch1_rxb_q_coef1 寄存器结构定义。地址偏移量:0x4D4，初值:0xC1，宽度:8
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
 结构说明  : ch1_rxb_q_coef3 寄存器结构定义。地址偏移量:0x4D6，初值:0x41，宽度:8
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
 结构说明  : ch1_reg_rxa_dcr_cfg 寄存器结构定义。地址偏移量:0x4D8，初值:0x46，宽度:8
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
 结构说明  : ch1_reg_rxb_dcr_cfg 寄存器结构定义。地址偏移量:0x4D9，初值:0x46，宽度:8
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
 结构说明  : ch1_reg_rx_dcr_ctrl 寄存器结构定义。地址偏移量:0x4DA，初值:0x00，宽度:8
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
 结构说明  : ch1_rxa_blocking 寄存器结构定义。地址偏移量:0x4DB，初值:0x00，宽度:8
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
 结构说明  : ch1_rxb_blocking 寄存器结构定义。地址偏移量:0x4DC，初值:0x00，宽度:8
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
 结构说明  : ch1_reg_rxa_dc_i_2 寄存器结构定义。地址偏移量:0x4DE，初值:0x00，宽度:8
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
 结构说明  : ch1_reg_rxa_dc_q_2 寄存器结构定义。地址偏移量:0x4E0，初值:0x00，宽度:8
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
 结构说明  : ch1_reg_rxb_dc_i_2 寄存器结构定义。地址偏移量:0x4E2，初值:0x00，宽度:8
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
 结构说明  : ch1_reg_rxb_dc_q_2 寄存器结构定义。地址偏移量:0x4E4，初值:0x00，宽度:8
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
 结构说明  : CH1_FLUSH_CFG1 寄存器结构定义。地址偏移量:0x4E6，初值:0x40，宽度:8
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
 结构说明  : CH1_RXAI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4E8，初值:0x02，宽度:8
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
 结构说明  : CH1_RXAQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4EA，初值:0x02，宽度:8
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
 结构说明  : CH1_RXBI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4EC，初值:0x02，宽度:8
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
 结构说明  : CH1_RXBQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x4EE，初值:0x02，宽度:8
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
 结构说明  : ch1_ctrl 寄存器结构定义。地址偏移量:0x4EF，初值:0x03，宽度:8
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
 结构说明  : ch1_rx_line_sel 寄存器结构定义。地址偏移量:0x4F0，初值:0x00，宽度:8
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
 结构说明  : ch1_rx_line_cfg 寄存器结构定义。地址偏移量:0x4F1，初值:0x00，宽度:8
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
 结构说明  : ch1_blk_cfg 寄存器结构定义。地址偏移量:0x4F2，初值:0x00，宽度:8
 寄存器说明: blk控制寄存器。
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
} ABB_CH1_BLK_CFG_UNION;
#define ABB_CH1_BLK_CFG_ch1_blk_clk_sel_START  (0)
#define ABB_CH1_BLK_CFG_ch1_blk_clk_sel_END    (0)
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_START   (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_END     (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_START   (2)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_END     (2)


/*****************************************************************************
 结构名    : ABB_CH1_RX_REG_DEBUG_DIG_UNION
 结构说明  : ch1_rx_reg_debug_dig 寄存器结构定义。地址偏移量:0x4F5，初值:0x00，宽度:8
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


/*****************************************************************************
 结构名    : ABB_DEBUG_RESET_UNION
 结构说明  : DEBUG_RESET 寄存器结构定义。地址偏移量:0x602，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dbg_sw_rst : 1;  /* bit[0]  :  */
        unsigned long  reserved   : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RESET_UNION;
#define ABB_DEBUG_RESET_dbg_sw_rst_START  (0)
#define ABB_DEBUG_RESET_dbg_sw_rst_END    (0)


/*****************************************************************************
 结构名    : ABB_DEBUG_CHANNEL_SEL_UNION
 结构说明  : DEBUG_CHANNEL_SEL 寄存器结构定义。地址偏移量:0x603，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  cpu_rx_ch3_sel        : 2;  /* bit[0-1]:  */
        unsigned long  cpu_rx_dbg_adc_sel    : 2;  /* bit[2-3]:  */
        unsigned long  cpu_rx_dbg_chab_sel   : 1;  /* bit[4]  :  */
        unsigned long  cpu_rx_dbg_pdm_hb_sel : 1;  /* bit[5]  :  */
        unsigned long  reserved              : 2;  /* bit[6-7]: 保留 */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_CHANNEL_SEL_UNION;
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_ch3_sel_START         (0)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_ch3_sel_END           (1)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_adc_sel_START     (2)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_adc_sel_END       (3)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_chab_sel_START    (4)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_chab_sel_END      (4)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_pdm_hb_sel_START  (5)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_pdm_hb_sel_END    (5)


/*****************************************************************************
 结构名    : ABB_DEBUG_RAM_EN_UNION
 结构说明  : DEBUG_RAM_EN 寄存器结构定义。地址偏移量:0x604，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  cpu_rx_dbg_en : 1;  /* bit[0]  :  */
        unsigned long  reserved      : 7;  /* bit[1-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_EN_UNION;
#define ABB_DEBUG_RAM_EN_cpu_rx_dbg_en_START  (0)
#define ABB_DEBUG_RAM_EN_cpu_rx_dbg_en_END    (0)


/*****************************************************************************
 结构名    : ABB_DEBUG_RAM_CFG_UNION
 结构说明  : DEBUG_RAM_CFG 寄存器结构定义。地址偏移量:0x605，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  cpu_rx_ram_wr_start : 1;  /* bit[0]  :  */
        unsigned long  cpu_rx_ram_wr_clr   : 1;  /* bit[1]  :  */
        unsigned long  cpu_rx_ram_rd_clr   : 1;  /* bit[2]  :  */
        unsigned long  reserved            : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_CFG_UNION;
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_start_START  (0)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_start_END    (0)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_clr_START    (1)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_clr_END      (1)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_rd_clr_START    (2)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_rd_clr_END      (2)


/*****************************************************************************
 结构名    : ABB_DEBUG_RAM_RPT1_UNION
 结构说明  : DEBUG_RAM_RPT1 寄存器结构定义。地址偏移量:0x606，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_ram_wr_en_cpu : 1;  /* bit[0]  :  */
        unsigned long  reserved_0       : 1;  /* bit[1]  : 保留 */
        unsigned long  rx_ram_rd_en_cpu : 1;  /* bit[2]  :  */
        unsigned long  reserved_1       : 5;  /* bit[3-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_RPT1_UNION;
#define ABB_DEBUG_RAM_RPT1_rx_ram_wr_en_cpu_START  (0)
#define ABB_DEBUG_RAM_RPT1_rx_ram_wr_en_cpu_END    (0)
#define ABB_DEBUG_RAM_RPT1_rx_ram_rd_en_cpu_START  (2)
#define ABB_DEBUG_RAM_RPT1_rx_ram_rd_en_cpu_END    (2)


/*****************************************************************************
 结构名    : ABB_DEBUG_RAM_RPT2_UNION
 结构说明  : DEBUG_RAM_RPT2 寄存器结构定义。地址偏移量:0x607，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_ram_wr_addr_cpu_msb : 7;  /* bit[0-6]:  */
        unsigned long  reserved               : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_RPT2_UNION;
#define ABB_DEBUG_RAM_RPT2_rx_ram_wr_addr_cpu_msb_START  (0)
#define ABB_DEBUG_RAM_RPT2_rx_ram_wr_addr_cpu_msb_END    (6)


/*****************************************************************************
 结构名    : ABB_DEBUG_RAM_RPT4_UNION
 结构说明  : DEBUG_RAM_RPT4 寄存器结构定义。地址偏移量:0x609，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_ram_rd_addr_cpu_msb : 7;  /* bit[0-6]:  */
        unsigned long  reserved               : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_RPT4_UNION;
#define ABB_DEBUG_RAM_RPT4_rx_ram_rd_addr_cpu_msb_START  (0)
#define ABB_DEBUG_RAM_RPT4_rx_ram_rd_addr_cpu_msb_END    (6)


/*****************************************************************************
 结构名    : ABB_SAR_DIG_1_UNION
 结构说明  : sar_dig_1 寄存器结构定义。地址偏移量:0x680，初值:0x00，宽度:8
 寄存器说明: RX IDLE模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_comp_sel_b0 : 1;  /* bit[0]  : {sar_comp_sel_b1,sar_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                          00：固定系数1；
                                                          01：固定系数2；
                                                          10：固定系数3；
                                                          11：固定系数4。 */
        unsigned long  sar_comp_fix    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                          0：系数不固定，由寄存器配置
                                                          1：系数固定 */
        unsigned long  sar_hb_bp       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                          0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                          1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved        : 2;  /* bit[3-4]: 保留 */
        unsigned long  sar_mode        : 3;  /* bit[5-7]: RX通道模式控制：
                                                          000：2G_A(默认)
                                                          001：3G_SC/TDS_B/4G_C
                                                          010：4G
                                                          011：3G_DC/4G_B
                                                          100：TDS
                                                          101：CDMA
                                                          110：CA
                                                          111：2G_B */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_DIG_1_UNION;
#define ABB_SAR_DIG_1_sar_comp_sel_b0_START  (0)
#define ABB_SAR_DIG_1_sar_comp_sel_b0_END    (0)
#define ABB_SAR_DIG_1_sar_comp_fix_START     (1)
#define ABB_SAR_DIG_1_sar_comp_fix_END       (1)
#define ABB_SAR_DIG_1_sar_hb_bp_START        (2)
#define ABB_SAR_DIG_1_sar_hb_bp_END          (2)
#define ABB_SAR_DIG_1_sar_mode_START         (5)
#define ABB_SAR_DIG_1_sar_mode_END           (7)


/*****************************************************************************
 结构名    : ABB_SAR_DIG_2_UNION
 结构说明  : sar_dig_2 寄存器结构定义。地址偏移量:0x681，初值:0x12，宽度:8
 寄存器说明: RX IDLE模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_en          : 1;  /* bit[0]  : SAR通道CLOCK GATING控制：
                                                          0：不CLOCK GATING
                                                          1：CLOCK GATING(默认)
                                                          (!sar_pd)|XX_SAR_EN = 1时工作，否则关闭 */
        unsigned long  reserved_0      : 1;  /* bit[1]  : 保留 */
        unsigned long  sar_gain_sel    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                          00：gain为0.5(默认)
                                                          01：gain为0.75
                                                          10：gain为0.85
                                                          11：Reserved */
        unsigned long  sar_comp_bp     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                          0：不bypass(默认)
                                                          1：bypass */
        unsigned long  sar_clk_inv     : 1;  /* bit[5]  : RX通道随路时钟SAR_CLK反向使能：
                                                          0：正常
                                                          1：反向 */
        unsigned long  reserved_1      : 1;  /* bit[6]  : 保留 */
        unsigned long  sar_comp_sel_b1 : 1;  /* bit[7]  : {sar_comp_sel_b1,sar_comp_sel_b0}组成补偿滤波器系数选择，参考sar_comp_sel_b0说明。 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_DIG_2_UNION;
#define ABB_SAR_DIG_2_sar_en_START           (0)
#define ABB_SAR_DIG_2_sar_en_END             (0)
#define ABB_SAR_DIG_2_sar_gain_sel_START     (2)
#define ABB_SAR_DIG_2_sar_gain_sel_END       (3)
#define ABB_SAR_DIG_2_sar_comp_bp_START      (4)
#define ABB_SAR_DIG_2_sar_comp_bp_END        (4)
#define ABB_SAR_DIG_2_sar_clk_inv_START      (5)
#define ABB_SAR_DIG_2_sar_clk_inv_END        (5)
#define ABB_SAR_DIG_2_sar_comp_sel_b1_START  (7)
#define ABB_SAR_DIG_2_sar_comp_sel_b1_END    (7)


/*****************************************************************************
 结构名    : ABB_SAR_TESTMODE_UNION
 结构说明  : SAR_TESTMODE 寄存器结构定义。地址偏移量:0x682，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_sw_rst      : 1;  /* bit[0]  : 数字部分RX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned long  sar_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  reserved        : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_TESTMODE_UNION;
#define ABB_SAR_TESTMODE_sar_sw_rst_START       (0)
#define ABB_SAR_TESTMODE_sar_sw_rst_END         (0)
#define ABB_SAR_TESTMODE_sar_cic_gate_en_START  (1)
#define ABB_SAR_TESTMODE_sar_cic_gate_en_END    (1)


/*****************************************************************************
 结构名    : ABB_SAR_PLL_SEL_UNION
 结构说明  : SAR_PLL_SEL 寄存器结构定义。地址偏移量:0x683，初值:0x00，宽度:8
 寄存器说明: PLL选择寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  sar_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  sar_c1_pll_sel  : 1;  /* bit[3]  :  */
        unsigned long  reserved        : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_PLL_SEL_UNION;
#define ABB_SAR_PLL_SEL_sar_g_pll_sel_START    (0)
#define ABB_SAR_PLL_SEL_sar_g_pll_sel_END      (1)
#define ABB_SAR_PLL_SEL_sar_wtl_pll_sel_START  (2)
#define ABB_SAR_PLL_SEL_sar_wtl_pll_sel_END    (2)
#define ABB_SAR_PLL_SEL_sar_c1_pll_sel_START   (3)
#define ABB_SAR_PLL_SEL_sar_c1_pll_sel_END     (3)


/*****************************************************************************
 结构名    : ABB_SAR_I_COEF1_UNION
 结构说明  : sar_i_coef1 寄存器结构定义。地址偏移量:0x687，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_i_c1     : 7;  /* bit[0-6]: SAR通道I路补偿滤波器系数C1,有符号数 */
        unsigned long  sar_i_c3_msb : 1;  /* bit[7]  : SAR通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_I_COEF1_UNION;
#define ABB_SAR_I_COEF1_sar_i_c1_START      (0)
#define ABB_SAR_I_COEF1_sar_i_c1_END        (6)
#define ABB_SAR_I_COEF1_sar_i_c3_msb_START  (7)
#define ABB_SAR_I_COEF1_sar_i_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_SAR_I_COEF3_UNION
 结构说明  : sar_i_coef3 寄存器结构定义。地址偏移量:0x689，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_i_c5 : 7;  /* bit[0-6]: SAR通道I路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_I_COEF3_UNION;
#define ABB_SAR_I_COEF3_sar_i_c5_START  (0)
#define ABB_SAR_I_COEF3_sar_i_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_SAR_Q_COEF1_UNION
 结构说明  : sar_q_coef1 寄存器结构定义。地址偏移量:0x68C，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_q_c1     : 7;  /* bit[0-6]: SAR通道Q路补偿滤波器系数C1,有符号数 */
        unsigned long  sar_q_c3_msb : 1;  /* bit[7]  : SAR通道Q路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_Q_COEF1_UNION;
#define ABB_SAR_Q_COEF1_sar_q_c1_START      (0)
#define ABB_SAR_Q_COEF1_sar_q_c1_END        (6)
#define ABB_SAR_Q_COEF1_sar_q_c3_msb_START  (7)
#define ABB_SAR_Q_COEF1_sar_q_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_SAR_Q_COEF3_UNION
 结构说明  : sar_q_coef3 寄存器结构定义。地址偏移量:0x68E，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_q_c5 : 7;  /* bit[0-6]: SAR通道Q路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_Q_COEF3_UNION;
#define ABB_SAR_Q_COEF3_sar_q_c5_START  (0)
#define ABB_SAR_Q_COEF3_sar_q_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_SARI_HB_GAIN_2_UNION
 结构说明  : SARI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x691，初值:0x02，宽度:8
 寄存器说明: CH0通道SAR HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sari_hb_gain_h : 2;  /* bit[0-1]: CH0通道SAR I路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SARI_HB_GAIN_2_UNION;
#define ABB_SARI_HB_GAIN_2_sari_hb_gain_h_START  (0)
#define ABB_SARI_HB_GAIN_2_sari_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_SARQ_HB_GAIN_2_UNION
 结构说明  : SARQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x693，初值:0x02，宽度:8
 寄存器说明: CH0通道SAR HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sarq_hb_gain_h : 2;  /* bit[0-1]: CH0通道SAR Q路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved       : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SARQ_HB_GAIN_2_UNION;
#define ABB_SARQ_HB_GAIN_2_sarq_hb_gain_h_START  (0)
#define ABB_SARQ_HB_GAIN_2_sarq_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_SAR_CTRL_UNION
 结构说明  : sar_ctrl 寄存器结构定义。地址偏移量:0x694，初值:0x03，宽度:8
 寄存器说明: 通道控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_loop_out : 1;  /* bit[0]  : CH0通道SAR环回输出控制信号，0：环回不输出信号；1：环回同时输出信号； */
        unsigned long  reserved_0   : 1;  /* bit[1]  : 保留 */
        unsigned long  reserved_1   : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_CTRL_UNION;
#define ABB_SAR_CTRL_sar_loop_out_START  (0)
#define ABB_SAR_CTRL_sar_loop_out_END    (0)


/*****************************************************************************
 结构名    : ABB_SAR_REG_DEBUG_DIG_UNION
 结构说明  : sar_reg_debug_dig 寄存器结构定义。地址偏移量:0x696，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_div_en_bp      : 1;  /* bit[0]  : RX分频器使能bypass控制
                                                             0：不bypass
                                                             1：bypass */
        unsigned long  reserved           : 3;  /* bit[1-3]: 保留 */
        unsigned long  sar_sw_rst_num_cfg : 3;  /* bit[4-6]: 模式切换复位长度配置值，单位为8 cycles */
        unsigned long  sar_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]：模式切换复位长度配置使能
                                                             0：不使能
                                                             1：使能 */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_REG_DEBUG_DIG_UNION;
#define ABB_SAR_REG_DEBUG_DIG_sar_div_en_bp_START       (0)
#define ABB_SAR_REG_DEBUG_DIG_sar_div_en_bp_END         (0)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_cfg_START  (4)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_cfg_END    (6)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_sel_START  (7)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_sel_END    (7)


/*****************************************************************************
 结构名    : ABB_N50M_DIG_1_UNION
 结构说明  : n50m_dig_1 寄存器结构定义。地址偏移量:0x6B0，初值:0x00，宽度:8
 寄存器说明: RX IDLE模式配置寄存器1，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_comp_sel_b0 : 1;  /* bit[0]  : {n50m_comp_sel_b1,n50m_comp_sel_b0}组成补偿滤波器系数选择，RX通道补偿滤波器补偿固定系数选择：
                                                           00：固定系数1；
                                                           01：固定系数2；
                                                           10：固定系数3；
                                                           11：固定系数4。 */
        unsigned long  n50m_comp_fix    : 1;  /* bit[1]  : RX通道补偿滤波器补偿系数固定控制：
                                                           0：系数不固定，由寄存器配置
                                                           1：系数固定 */
        unsigned long  n50m_hb_bp       : 1;  /* bit[2]  : RX通道半带滤波器bypass控制：
                                                           0：不bypass半带滤波器,rx通道输出data rate 为RX CIC rate/2(默认)
                                                           1：bypass半带滤波器,rx通道输出data rate 为RX CIC rate */
        unsigned long  reserved         : 2;  /* bit[3-4]: 保留 */
        unsigned long  n50m_mode        : 3;  /* bit[5-7]: RX通道模式控制：
                                                           000：2G_A(默认)
                                                           001：3G_SC/TDS_B/4G_C
                                                           010：4G
                                                           011：3G_DC/4G_B
                                                           100：TDS
                                                           101：CDMA
                                                           110：CA
                                                           111：2G_B */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_DIG_1_UNION;
#define ABB_N50M_DIG_1_n50m_comp_sel_b0_START  (0)
#define ABB_N50M_DIG_1_n50m_comp_sel_b0_END    (0)
#define ABB_N50M_DIG_1_n50m_comp_fix_START     (1)
#define ABB_N50M_DIG_1_n50m_comp_fix_END       (1)
#define ABB_N50M_DIG_1_n50m_hb_bp_START        (2)
#define ABB_N50M_DIG_1_n50m_hb_bp_END          (2)
#define ABB_N50M_DIG_1_n50m_mode_START         (5)
#define ABB_N50M_DIG_1_n50m_mode_END           (7)


/*****************************************************************************
 结构名    : ABB_N50M_DIG_2_UNION
 结构说明  : n50m_dig_2 寄存器结构定义。地址偏移量:0x6B1，初值:0x12，宽度:8
 寄存器说明: RX IDLE模式配置寄存器2，由线控决定是否起作用。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_en          : 1;  /* bit[0]  : N50M通道CLOCK GATING控制：
                                                           0：不CLOCK GATING
                                                           1：CLOCK GATING(默认)
                                                           (!n50m_pd)|XX_N50M_EN = 1时工作，否则关闭 */
        unsigned long  reserved_0       : 1;  /* bit[1]  : 保留 */
        unsigned long  n50m_gain_sel    : 2;  /* bit[2-3]: RX通道增益配置选择：
                                                           00：gain为0.5(默认)
                                                           01：gain为0.75
                                                           10：gain为0.85
                                                           11：Reserved */
        unsigned long  n50m_comp_bp     : 1;  /* bit[4]  : RX通道补偿滤波器bypass控制：
                                                           0：不bypass(默认)
                                                           1：bypass */
        unsigned long  n50m_clk_inv     : 1;  /* bit[5]  : RX通道随路时钟N50M_CLK反向使能：
                                                           0：正常
                                                           1：反向 */
        unsigned long  reserved_1       : 1;  /* bit[6]  : 保留 */
        unsigned long  n50m_comp_sel_b1 : 1;  /* bit[7]  : {n50m_comp_sel_b1,n50m_comp_sel_b0}组成补偿滤波器系数选择，参考n50m_comp_sel_b0说明。 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_DIG_2_UNION;
#define ABB_N50M_DIG_2_n50m_en_START           (0)
#define ABB_N50M_DIG_2_n50m_en_END             (0)
#define ABB_N50M_DIG_2_n50m_gain_sel_START     (2)
#define ABB_N50M_DIG_2_n50m_gain_sel_END       (3)
#define ABB_N50M_DIG_2_n50m_comp_bp_START      (4)
#define ABB_N50M_DIG_2_n50m_comp_bp_END        (4)
#define ABB_N50M_DIG_2_n50m_clk_inv_START      (5)
#define ABB_N50M_DIG_2_n50m_clk_inv_END        (5)
#define ABB_N50M_DIG_2_n50m_comp_sel_b1_START  (7)
#define ABB_N50M_DIG_2_n50m_comp_sel_b1_END    (7)


/*****************************************************************************
 结构名    : ABB_N50M_TESTMODE_UNION
 结构说明  : N50M_TESTMODE 寄存器结构定义。地址偏移量:0x6B2，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_sw_rst      : 1;  /* bit[0]  : 数字部分RX通道软复位信号：
                                                           0：不复位(默认)
                                                           1：复位 */
        unsigned long  n50m_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  reserved         : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_TESTMODE_UNION;
#define ABB_N50M_TESTMODE_n50m_sw_rst_START       (0)
#define ABB_N50M_TESTMODE_n50m_sw_rst_END         (0)
#define ABB_N50M_TESTMODE_n50m_cic_gate_en_START  (1)
#define ABB_N50M_TESTMODE_n50m_cic_gate_en_END    (1)


/*****************************************************************************
 结构名    : ABB_N50M_PLL_SEL_UNION
 结构说明  : N50M_PLL_SEL 寄存器结构定义。地址偏移量:0x6B3，初值:0x00，宽度:8
 寄存器说明: PLL选择寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  n50m_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  n50m_c1_pll_sel  : 1;  /* bit[3]  :  */
        unsigned long  reserved         : 4;  /* bit[4-7]: 保留 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_PLL_SEL_UNION;
#define ABB_N50M_PLL_SEL_n50m_g_pll_sel_START    (0)
#define ABB_N50M_PLL_SEL_n50m_g_pll_sel_END      (1)
#define ABB_N50M_PLL_SEL_n50m_wtl_pll_sel_START  (2)
#define ABB_N50M_PLL_SEL_n50m_wtl_pll_sel_END    (2)
#define ABB_N50M_PLL_SEL_n50m_c1_pll_sel_START   (3)
#define ABB_N50M_PLL_SEL_n50m_c1_pll_sel_END     (3)


/*****************************************************************************
 结构名    : ABB_N50M_I_COEF1_UNION
 结构说明  : n50m_i_coef1 寄存器结构定义。地址偏移量:0x6B7，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_i_c1     : 7;  /* bit[0-6]: N50M通道I路补偿滤波器系数C1,有符号数 */
        unsigned long  n50m_i_c3_msb : 1;  /* bit[7]  : N50M通道I路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_I_COEF1_UNION;
#define ABB_N50M_I_COEF1_n50m_i_c1_START      (0)
#define ABB_N50M_I_COEF1_n50m_i_c1_END        (6)
#define ABB_N50M_I_COEF1_n50m_i_c3_msb_START  (7)
#define ABB_N50M_I_COEF1_n50m_i_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_N50M_I_COEF3_UNION
 结构说明  : n50m_i_coef3 寄存器结构定义。地址偏移量:0x6B9，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_i_c5 : 7;  /* bit[0-6]: N50M通道I路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved  : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_N50M_I_COEF3_UNION;
#define ABB_N50M_I_COEF3_n50m_i_c5_START  (0)
#define ABB_N50M_I_COEF3_n50m_i_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_N50M_Q_COEF1_UNION
 结构说明  : n50m_q_coef1 寄存器结构定义。地址偏移量:0x6BC，初值:0xC1，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_q_c1     : 7;  /* bit[0-6]: N50M通道Q路补偿滤波器系数C1,有符号数 */
        unsigned long  n50m_q_c3_msb : 1;  /* bit[7]  : N50M通道Q路补偿滤波器系数C3,无符号数,最高位 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_Q_COEF1_UNION;
#define ABB_N50M_Q_COEF1_n50m_q_c1_START      (0)
#define ABB_N50M_Q_COEF1_n50m_q_c1_END        (6)
#define ABB_N50M_Q_COEF1_n50m_q_c3_msb_START  (7)
#define ABB_N50M_Q_COEF1_n50m_q_c3_msb_END    (7)


/*****************************************************************************
 结构名    : ABB_N50M_Q_COEF3_UNION
 结构说明  : n50m_q_coef3 寄存器结构定义。地址偏移量:0x6BE，初值:0x41，宽度:8
 寄存器说明: RX通道补偿系数寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_q_c5 : 7;  /* bit[0-6]: N50M通道Q路补偿滤波器系数C5,有符号数 */
        unsigned long  reserved  : 1;  /* bit[7]  : 保留 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_N50M_Q_COEF3_UNION;
#define ABB_N50M_Q_COEF3_n50m_q_c5_START  (0)
#define ABB_N50M_Q_COEF3_n50m_q_c5_END    (6)


/*****************************************************************************
 结构名    : ABB_N50MI_HB_GAIN_2_UNION
 结构说明  : N50MI_HB_GAIN_2 寄存器结构定义。地址偏移量:0x6C1，初值:0x02，宽度:8
 寄存器说明: CH0通道N50M HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50mi_hb_gain_h : 2;  /* bit[0-1]: CH0通道N50M I路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved        : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_N50MI_HB_GAIN_2_UNION;
#define ABB_N50MI_HB_GAIN_2_n50mi_hb_gain_h_START  (0)
#define ABB_N50MI_HB_GAIN_2_n50mi_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_N50MQ_HB_GAIN_2_UNION
 结构说明  : N50MQ_HB_GAIN_2 寄存器结构定义。地址偏移量:0x6C3，初值:0x02，宽度:8
 寄存器说明: CH0通道N50M HB滤波器增益。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50mq_hb_gain_h : 2;  /* bit[0-1]: CH0通道N50M Q路 HB滤波器增益（10u）的高2bit。增益默认值512。 */
        unsigned long  reserved        : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_N50MQ_HB_GAIN_2_UNION;
#define ABB_N50MQ_HB_GAIN_2_n50mq_hb_gain_h_START  (0)
#define ABB_N50MQ_HB_GAIN_2_n50mq_hb_gain_h_END    (1)


/*****************************************************************************
 结构名    : ABB_N50M_CTRL_UNION
 结构说明  : n50m_ctrl 寄存器结构定义。地址偏移量:0x6C4，初值:0x03，宽度:8
 寄存器说明: 通道控制寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_loop_out : 1;  /* bit[0]  : CH0通道N50M环回输出控制信号，0：环回不输出信号；1：环回同时输出信号； */
        unsigned long  reserved_0    : 1;  /* bit[1]  : 保留 */
        unsigned long  reserved_1    : 6;  /* bit[2-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_CTRL_UNION;
#define ABB_N50M_CTRL_n50m_loop_out_START  (0)
#define ABB_N50M_CTRL_n50m_loop_out_END    (0)


/*****************************************************************************
 结构名    : ABB_N50M_REG_DEBUG_DIG_UNION
 结构说明  : n50m_reg_debug_dig 寄存器结构定义。地址偏移量:0x6C6，初值:0x00，宽度:8
 寄存器说明: 数字调试寄存器。
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_div_en_bp      : 1;  /* bit[0]  : RX分频器使能bypass控制
                                                              0：不bypass
                                                              1：bypass */
        unsigned long  reserved            : 3;  /* bit[1-3]: 保留 */
        unsigned long  n50m_sw_rst_num_cfg : 3;  /* bit[4-6]: 模式切换复位长度配置值，单位为8 cycles */
        unsigned long  n50m_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]：模式切换复位长度配置使能
                                                              0：不使能
                                                              1：使能 */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_REG_DEBUG_DIG_UNION;
#define ABB_N50M_REG_DEBUG_DIG_n50m_div_en_bp_START       (0)
#define ABB_N50M_REG_DEBUG_DIG_n50m_div_en_bp_END         (0)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_cfg_START  (4)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_cfg_END    (6)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_sel_START  (7)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_sel_END    (7)


/*****************************************************************************
 结构名    : ABB_ANA_COMMON_WR20_UNION
 结构说明  : ANA_COMMON_WR20 寄存器结构定义。地址偏移量:0x814，初值:0x1F，宽度:8
 寄存器说明: 模拟common读写寄存器
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_AUTO_TUNE  : 1;  /* bit[0]  :  */
        unsigned long  RX_AUTO_TUNE  : 1;  /* bit[1]  :  */
        unsigned long  ET_AUTO_TUNE  : 1;  /* bit[2]  :  */
        unsigned long  CH3_AUTO_TUNE : 1;  /* bit[3]  :  */
        unsigned long  TUNING_VAL_EN : 1;  /* bit[4]  :  */
        unsigned long  reserved      : 3;  /* bit[5-7]: 保留 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ANA_COMMON_WR20_UNION;
#define ABB_ANA_COMMON_WR20_TX_AUTO_TUNE_START   (0)
#define ABB_ANA_COMMON_WR20_TX_AUTO_TUNE_END     (0)
#define ABB_ANA_COMMON_WR20_RX_AUTO_TUNE_START   (1)
#define ABB_ANA_COMMON_WR20_RX_AUTO_TUNE_END     (1)
#define ABB_ANA_COMMON_WR20_ET_AUTO_TUNE_START   (2)
#define ABB_ANA_COMMON_WR20_ET_AUTO_TUNE_END     (2)
#define ABB_ANA_COMMON_WR20_CH3_AUTO_TUNE_START  (3)
#define ABB_ANA_COMMON_WR20_CH3_AUTO_TUNE_END    (3)
#define ABB_ANA_COMMON_WR20_TUNING_VAL_EN_START  (4)
#define ABB_ANA_COMMON_WR20_TUNING_VAL_EN_END    (4)

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
