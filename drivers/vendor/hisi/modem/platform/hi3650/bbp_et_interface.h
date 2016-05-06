/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_et_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-12-10 10:52:10
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月10日
    作    者   : x00217286
    修改内容   : 从《_ET.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_ET_INTERFACE_H__
#define __BBP_ET_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_et
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留。
 bit[0]      et软复位信号。
             1：表示复位
             0：表示清复位
   UNION结构:  ET_ET_SOFT_RST_UNION */
#define ET_ET_SOFT_RST_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0x0)

/* 寄存器说明：
 bit[31:16]  spram mem_ctrl
 bit[15:0]   tpram mem_ctrl
   UNION结构:  ET_ET_RAM_CTRL0_UNION */
#define ET_ET_RAM_CTRL0_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0x4)

/* 寄存器说明：
 bit[31:8]   保留。
 bit[7:6]    PA高档位匹配指示信号。如果线控信号com2et_tx_pa_mode与该字段
             匹配，可以确定PA是工作在高增益模式。
 bit[5:4]    PA中档位匹配指示信号。如果线控信号com2et_tx_pa_mode与dsp_pa_high_ctrl不匹配但与该字段匹配，可以确定PA是工作在中增益模式。
 bit[3:0]    保留。
   UNION结构:  ET_PA_PARA_UNION */
#define ET_PA_PARA_ADDR                               (SOC_BBP_ET_BASE_ADDR + 0x8)

/* 寄存器说明：
 bit[31:9]   保留。
 bit[8:0]    射频数据通路延迟配置值。当com2et_tx_clk时钟频率和数据通路数据率之比为4:1时，取值范围为0~508，当为2:1时，取值范围为0~254，单位为数据通路时钟周期。
             
   UNION结构:  ET_RF_DATA_DLY_UNION */
#define ET_RF_DATA_DLY_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xC)

/* 寄存器说明：
 bit[31:2]   保留。
 bit[1:0]    L/W模式选择，
             01: LTE mode, 
             10: W mode, 
             00: L/W均无效，ET模块无时钟，且自动进入软复位，跳至其他状态时解复位
             11: 无效状态
             
             例如从L模切到W模，lw_mode_sel变化过程2'b01 -> 2'b00（软复位） -> 2'b10
   UNION结构:  ET_LW_MODE_SEL_UNION */
#define ET_LW_MODE_SEL_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0x10)

/* 寄存器说明：
 bit[31:1]   保留。
 bit[0]      软件关闭ET0通道。
             1'b1 : ET0正常工作，默认值；
             1'b0 : ET0关闭，时钟门控，逻辑软复位；
             
             注：关闭此寄存器会影响ET0 tx通路数据发送。
   UNION结构:  ET_SOFT_EN_UNION */
#define ET_SOFT_EN_ADDR                               (SOC_BBP_ET_BASE_ADDR + 0x14)

/* 寄存器说明：
   详      述：该位置包含一块规格为256x32的RAM，用于保存功率电压映射查找表。当通过配置总线访问该RAM时，配置总线数据位和RAM存储单元数据位之间的对应关系如下：
            配置总线数据位    RAM单元数据位
               31:30            N/A
               29:16            29;16
               15:14            N/A
               13:0              13:0
            
            et包络通路工作时，禁止总线读写该表。
   UNION结构 ：无 */
#define ET_PWR_VOLT_LUT_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0x800)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5]      线性转对数和射频功率估算功能bypass信号。
             
             0：不bypass该功能。
             1：bypass该功能。
             
 bit[4]      包络带宽FIR滤波器功能旁路控制。
             
             0：不bypass该功能。
             1：bypass该功能。
             
 bit[3]      群延迟IIR滤波器功能旁路控制。
             
             0：不bypass该功能。
             1：bypass该功能。
             
 bit[2]      电压适配器功能旁路控制。
             
             0：不bypass该功能。
             1：bypass该功能。
             
 bit[1]      线性限摆功能bypass信号。
             0：不bypass该功能。
             1：bypass该功能。
 bit[0]      线性限底功能bypass信号。
             0：不bypass该功能。
             1：bypass该功能。
   UNION结构:  ET_ET_BYPASS_CTRL_UNION */
#define ET_ET_BYPASS_CTRL_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xC00)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      ET功能自动门控旁路信号。
             0：自动门控不旁路；
             1：自动门控旁路。
   UNION结构:  ET_ET_CKG_BYPASS_UNION */
#define ET_ET_CKG_BYPASS_ADDR                         (SOC_BBP_ET_BASE_ADDR + 0xC04)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    ET包络信号通路延迟配置值，延迟配置范围0~254。最小延迟单位为1个随路时钟周期，即122M时钟情况下8.138ns
   UNION结构:  ET_ET_DELAY_PARA_UNION */
#define ET_ET_DELAY_PARA_ADDR                         (SOC_BBP_ET_BASE_ADDR + 0xC08)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件根据数据速率配置上采样选择，
             1'b0: 做2倍上采样；
             1'b1: 不做上采样
   UNION结构:  ET_ET_UPSAMPLE_SEL_UNION */
#define ET_ET_UPSAMPLE_SEL_ADDR                       (SOC_BBP_ET_BASE_ADDR + 0xC18)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:4]    第0组分数延迟滤波器插值中心选择。
             此处不开放给软件使用，只能配默认值2'b01 。
             00：表示插值滤波器中心位于x(n+1)；
             01：表示插值滤波器中心位于x(n)；
             10：表示插值滤波器中心位于x(n-1)；
             11：无效配置。
 bit[3:2]    保留
 bit[1:0]    第1组分数延迟滤波器插值中心选择。
             此处不开放给软件使用，只能配默认值2'b01 。
             00：表示插值滤波器中心位于x(n+1)；
             01：表示插值滤波器中心位于x(n)；
             10：表示插值滤波器中心位于x(n-1)；
             11：无效配置。
   UNION结构:  ET_ET_INT_FILTER_CTRL_UNION */
#define ET_ET_INT_FILTER_CTRL_ADDR                    (SOC_BBP_ET_BASE_ADDR + 0xC1C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器0组系数0，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器0组系数1，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_0DELAY_PARA_0_UNION */
#define ET_ET_FINE_0DELAY_PARA_0_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC20)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器0组系数2，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器0组系数3，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_0DELAY_PARA_1_UNION */
#define ET_ET_FINE_0DELAY_PARA_1_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC24)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器0组系数4，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器0组系数5，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_0DELAY_PARA_2_UNION */
#define ET_ET_FINE_0DELAY_PARA_2_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC28)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器0组系数6，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器0组系数7，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_0DELAY_PARA_3_UNION */
#define ET_ET_FINE_0DELAY_PARA_3_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC2C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器0组系数8，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:0]   保留
   UNION结构:  ET_ET_FINE_0DELAY_PARA_4_UNION */
#define ET_ET_FINE_0DELAY_PARA_4_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC30)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器1组系数0，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器1组系数1，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_1DELAY_PARA_0_UNION */
#define ET_ET_FINE_1DELAY_PARA_0_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC34)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器1组系数2，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器1组系数3，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_1DELAY_PARA_1_UNION */
#define ET_ET_FINE_1DELAY_PARA_1_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC38)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器1组系数4，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器1组系数5，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_1DELAY_PARA_2_UNION */
#define ET_ET_FINE_1DELAY_PARA_2_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC3C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器1组系数6，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:12]  保留
 bit[11:0]   分数延迟滤波器1组系数7，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
   UNION结构:  ET_ET_FINE_1DELAY_PARA_3_UNION */
#define ET_ET_FINE_1DELAY_PARA_3_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC40)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  分数延迟滤波器1组系数8，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。
 bit[15:0]   保留
   UNION结构:  ET_ET_FINE_1DELAY_PARA_4_UNION */
#define ET_ET_FINE_1DELAY_PARA_4_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC44)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    延迟取最大功能的延迟参数，4bit无符号数，取值N在0到15。
   UNION结构:  ET_ET_ENV_PROC_PARA1_UNION */
#define ET_ET_ENV_PROC_PARA1_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC4C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  线性Detrough参数，包络线性限底门限。12bit无符号数。
 bit[15:6]   保留
 bit[5:0]    线性Detrough参数，限底右移乘系数，6bit无符号数。
   UNION结构:  ET_ET_ENV_PROC_PARA2_UNION */
#define ET_ET_ENV_PROC_PARA2_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC50)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:0]   射频包络功率计算参数，包络调节补偿值，14位有符号数，默认值-4840，精度0.0125dB，即-60.5dB。
   UNION结构:  ET_ET_ENV_PROC_PARA3_UNION */
#define ET_ET_ENV_PROC_PARA3_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC54)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      当dsp_pa_ctrl_mode=0时，此时包络检测需要工作在高、中两种增益模式下；
             
             当dsp_pa_ctrl_mode=1时，此时包络检测仅需要工作在高增益模式下，线控信号et_tx_pa_mode应保证与寄存器字段dsp_pa_high_ctrl的值相同。
   UNION结构:  ET_ET_PA_CTRL_UNION */
#define ET_ET_PA_CTRL_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xC58)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  限摆上坡门限，缺省值1600，取值范围0~8191。无符号数
 bit[15:13]  保留
 bit[12:0]   限摆下坡门限，W下默认值1600，LTE下自定义，取值范围0~8191。无符号数
   UNION结构:  ET_ET_LIMIT_ENV_SLEW_PARA_UNION */
#define ET_ET_LIMIT_ENV_SLEW_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xC60)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:13]  天线差损补偿。该字段不开放给软件使用。在写入该寄存器时，应确保该字段始终写入0x000。有符号数。可维可测功能
 bit[12:0]   线性转对数前使用的偏移。13位有符号值。
   UNION结构:  ET_ET_ENV_TOP_EXTRA_PARA_UNION */
#define ET_ET_ENV_TOP_EXTRA_PARA_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC68)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数a11，有符号数。
 bit[15:12]  保留
 bit[11:0]   群延迟均衡器IIR滤波器系数a12，有符号数。
   UNION结构:  ET_ET_IIR_COEF_0_1_PARA_UNION */
#define ET_ET_IIR_COEF_0_1_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC6C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数b11，有符号数。
 bit[15:12]  保留
 bit[11:0]   群延迟均衡器IIR滤波器系数b12，有符号数。
   UNION结构:  ET_ET_IIR_COEF_2_3_PARA_UNION */
#define ET_ET_IIR_COEF_2_3_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC70)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数b13，有符号数。
 bit[15:12]  保留
 bit[11:0]   群延迟均衡器IIR滤波器系数a21，有符号数。
   UNION结构:  ET_ET_IIR_COEF_4_5_PARA_UNION */
#define ET_ET_IIR_COEF_4_5_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC74)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数a22，有符号数。
 bit[15:12]  保留
 bit[11:0]   群延迟均衡器IIR滤波器系数b21，有符号数。
   UNION结构:  ET_ET_IIR_COEF_6_7_PARA_UNION */
#define ET_ET_IIR_COEF_6_7_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC78)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数b22，有符号数。
 bit[15:12]  保留
 bit[11:0]   群延迟均衡器IIR滤波器系数b23，有符号数。
   UNION结构:  ET_ET_IIR_COEF_8_9_PARA_UNION */
#define ET_ET_IIR_COEF_8_9_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC7C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数a31，有符号数。
 bit[15:12]  保留
 bit[11:0]   群延迟均衡器IIR滤波器系数a32，有符号数。
   UNION结构:  ET_ET_IIR_COEF_10_11_PARA_UNION */
#define ET_ET_IIR_COEF_10_11_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xC80)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数b31，有符号数。
 bit[15:12]  保留
 bit[11:0]   群延迟均衡器IIR滤波器系数b32，有符号数。
   UNION结构:  ET_ET_IIR_COEF_12_13_PARA_UNION */
#define ET_ET_IIR_COEF_12_13_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xC84)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  群延迟均衡器IIR滤波器系数b33，有符号数。
 bit[15:0]   保留
   UNION结构:  ET_ET_IIR_COEF_14_PARA_UNION */
#define ET_ET_IIR_COEF_14_PARA_ADDR                   (SOC_BBP_ET_BASE_ADDR + 0xC88)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:28]  群延迟均衡器IIR滤波器b33支路算术右移移位次数控制。无符号
             0:9
             1:10
             2:11
             3:12
 bit[27:26]  群延迟均衡器IIR滤波器b32支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[25:24]  群延迟均衡器IIR滤波器b31支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[23:22]  群延迟均衡器IIR滤波器a32支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[21:20]  群延迟均衡器IIR滤波器a31算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[19:18]  群延迟均衡器IIR滤波器b23支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[17:16]  群延迟均衡器IIR滤波器b22支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[15:14]  群延迟均衡器IIR滤波器b21支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[13:12]  群延迟均衡器IIR滤波器a22支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[11:10]  群延迟均衡器IIR滤波器a21支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[9:8]    群延迟均衡器IIR滤波器b13支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[7:6]    群延迟均衡器IIR滤波器b12支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[5:4]    群延迟均衡器IIR滤波器b11支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[3:2]    群延迟均衡器IIR滤波器a12支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
 bit[1:0]    群延迟均衡器IIR滤波器a11支路算术右移移位次数控制。
             0:9
             1:10
             2:11
             3:12
   UNION结构:  ET_ET_IIR_SHIFT_PARA_UNION */
#define ET_ET_IIR_SHIFT_PARA_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC8C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^0的系数（对应数据延迟最小），有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^1的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_0_1_PARA_UNION */
#define ET_ET_FIR_COEF_0_1_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC90)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^2的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^3的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_2_3_PARA_UNION */
#define ET_ET_FIR_COEF_2_3_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC94)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^4的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^5的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_4_5_PARA_UNION */
#define ET_ET_FIR_COEF_4_5_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC98)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^6的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^7的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_6_7_PARA_UNION */
#define ET_ET_FIR_COEF_6_7_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC9C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^8的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^9的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_8_9_PARA_UNION */
#define ET_ET_FIR_COEF_8_9_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xCA0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^10的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^11的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_10_11_PARA_UNION */
#define ET_ET_FIR_COEF_10_11_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCA4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^12的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^13的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_12_13_PARA_UNION */
#define ET_ET_FIR_COEF_12_13_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCA8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^14的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^15的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_14_15_PARA_UNION */
#define ET_ET_FIR_COEF_14_15_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCAC)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^16的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^17的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_16_17_PARA_UNION */
#define ET_ET_FIR_COEF_16_17_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCB0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^18的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^19的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_18_19_PARA_UNION */
#define ET_ET_FIR_COEF_18_19_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCB4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^20的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^21的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_20_21_PARA_UNION */
#define ET_ET_FIR_COEF_20_21_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCB8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^22的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^23的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_22_23_PARA_UNION */
#define ET_ET_FIR_COEF_22_23_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCBC)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^24的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^25的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_24_25_PARA_UNION */
#define ET_ET_FIR_COEF_24_25_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCC0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^26的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^27的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_26_27_PARA_UNION */
#define ET_ET_FIR_COEF_26_27_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCC4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^28的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^29的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_28_29_PARA_UNION */
#define ET_ET_FIR_COEF_28_29_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCC8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^30的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^31的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_30_31_PARA_UNION */
#define ET_ET_FIR_COEF_30_31_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCCC)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^32的系数，有符号数。
 bit[15:12]  保留
 bit[11:0]   包络带宽FIR滤波器抽头(1/z)^33的系数，有符号数。
   UNION结构:  ET_ET_FIR_COEF_32_33_PARA_UNION */
#define ET_ET_FIR_COEF_32_33_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCD0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  包络带宽FIR滤波器抽头(1/z)^34的系数（对应数据延迟最大），有符号数。
 bit[15:0]   保留
   UNION结构:  ET_ET_FIR_COEF_34_PARA_UNION */
#define ET_ET_FIR_COEF_34_PARA_ADDR                   (SOC_BBP_ET_BASE_ADDR + 0xCD4)

/* 寄存器说明：
 bit[31:16]  通道0控制ctrl2proc_et_mode_en下降沿的延迟，无符号数。
             配置延时值不应超过et通路总延时。
 bit[15:0]   t延时单位为随路时钟周期
             各t延时约束关系：
             t3 >= t1 ;
             t4 < t6 ;
             t4+t5 > t6+t7 ;
             
             通道0控制ctrl2swch_et_mode_sel, ctrl2swch_apt_pa_vcc_ind, ctrl2proc_et_mode_en的延迟；
             配置延时值不应超过et通路总延时，下同。
             
             一组t延时参考值：
             若et通路整数延迟寄存器值为x，则t1 = x + 'd51; t2 = 0;
             t3 = x + 'd51; 
             t4 = x + 'd51; t5 = 0; 
             t6 = x + 'd51; t7 = 0; 
             t8 = x + 'd96;
   UNION结构:  ET_ET_CTRL_DELAY0_UNION */
#define ET_ET_CTRL_DELAY0_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCE4)

/* 寄存器说明：
 bit[31:16]  et_ctrl内部使用，延时et_act_en
             
 bit[15:0]   通道0控制et2pad_et_mode_sel的延迟，暂不使用。
   UNION结构:  ET_ET_CTRL_DELAY1_UNION */
#define ET_ET_CTRL_DELAY1_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCE8)

/* 寄存器说明：
 bit[31:16]  通道0控制et2abb_act_en下降沿的延迟
 bit[15:0]   通道0控制et2abb_act_en上升沿的延迟
   UNION结构:  ET_ET_CTRL_DELAY2_UNION */
#define ET_ET_CTRL_DELAY2_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCEC)

/* 寄存器说明：
 bit[31:16]  通道0控制et2abb_et_mode_sel下降沿的延迟
 bit[15:0]   通道0控制et2abb_et_mode_sel上升沿的延迟
   UNION结构:  ET_ET_CTRL_DELAY3_UNION */
#define ET_ET_CTRL_DELAY3_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCF0)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    
             位[2]自研ETM选择，
             0：使用第三方ETM，默认值；
             
             位[1:0]第三方ETM工作模式。
             0：用于R2类型ETM器件，                  
             1：用于TI类型ETM器件模式1。
             2：用于TI类型ETM器件模式2。
             3：用于TI类型ETM器件模式2。
   UNION结构:  ET_ET_CTRL_ETM_MODE_UNION */
#define ET_ET_CTRL_ETM_MODE_ADDR                      (SOC_BBP_ET_BASE_ADDR + 0xCF4)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  该参数表示PA高增益功率电压查找表第0项（在偏移地址0x800处）对应的功率值，该参数为11bit无符号数，单位为0.0125dB，默认值为0。
 bit[15:11]  保留
 bit[10:0]   该参数表示PA中增益功率电压查找表第0项（在偏移地址0xA00处）对应的功率值，该参数为11bit无符号数，单位为0.0125dB，默认值为0。
   UNION结构:  ET_ET_PA_THD_PARA_HIGH_UNION */
#define ET_ET_PA_THD_PARA_HIGH_ADDR                   (SOC_BBP_ET_BASE_ADDR + 0xC5C)

/* 寄存器说明：
 bit[31:1]   保留。
 bit[0]      L/W模式切换自动软复位使能
             1：切模自动软复位
             0：切模不触发复位
             
   UNION结构:  ET_AUTO_RESET_UNION */
#define ET_AUTO_RESET_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xCF8)

/* 寄存器说明：
 bit[31:2]   保留。
 bit[1]      该bit只在APT校准模式下有效
             1'b1: ABB工作在ET模式
             1'b0: ABB工作在APT模式
 bit[0]      1'b1: 选择APT校准模式
             1'b0: 正常工作模式，默认值
   UNION结构:  ET_APT_CALIBRE_MODE_UNION */
#define ET_APT_CALIBRE_MODE_ADDR                      (SOC_BBP_ET_BASE_ADDR + 0xCFC)

/* 寄存器说明：
 bit[31:14]  保留。
 bit[13:0]   输出校准电压，有符号数
   UNION结构:  ET_CALIBRE_VCC_UNION */
#define ET_CALIBRE_VCC_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD00)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      包络通路输出交织顺序选择 
             0: 先奇后偶，默认值  
             1:先偶后奇
   UNION结构:  ET_INTRLV_SEL_UNION */
#define ET_INTRLV_SEL_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xD04)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      包络和射频通路输入数据对齐指示,
             0:对齐
             1:不对齐标志
   UNION结构:  ET_ET_ALIGN_UNION */
#define ET_ET_ALIGN_ADDR                              (SOC_BBP_ET_BASE_ADDR + 0xD08)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:8]   ET模式切APT模式次数
 bit[7:0]    APT模式切ET模式次数
   UNION结构:  ET_ET_STATUS_UNION */
#define ET_ET_STATUS_ADDR                             (SOC_BBP_ET_BASE_ADDR + 0xD0C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      写1'b1，所有上报寄存器清零
   UNION结构:  ET_ET_RPT_CLEAR_UNION */
#define ET_ET_RPT_CLEAR_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0xD10)

/* 寄存器说明：
 bit[31:2]   
 bit[1:0]    [1]: force config enable;
             [0]: 1'b1, force select internal logic; 1'b0, force select lbus
   UNION结构:  ET_LUT_RAM_SEL_UNION */
#define ET_LUT_RAM_SEL_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD14)

/* 寄存器说明：
 bit[31:1]   
 bit[0]      调试数据选择，
             1'b0:正常工作模式；
             1'b1:使用dbg调试数据强配；
   UNION结构:  ET_DBG_DAT_SEL_UNION */
#define ET_DBG_DAT_SEL_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD18)

/* 寄存器说明：
 bit[31:10]  
 bit[9:0]    dbg调试数据，用于强配线性转对数索引值。无符号，可维可测
   UNION结构:  ET_DBG_DAT0_UNION */
#define ET_DBG_DAT0_ADDR                              (SOC_BBP_ET_BASE_ADDR + 0xD1C)

/* 寄存器说明：
 bit[31:3]   
 bit[2]      tx整数延迟同步方式：
             1'b0: 定时生效，等待dly_para_ind线控，动态更新时使用。
             1'b1: 立即生效，不做同步，静态配置时使用。（默认值）
 bit[1]      et整数延迟同步方式：
             1'b0: 定时生效，等待dly_para_ind线控，动态更新时使用。
             1'b1: 立即生效，不做同步，静态配置时使用。（默认值）
 bit[0]      usfd分数延迟同步方式：
             1'b0: 定时生效，等待dly_para_ind线控，动态更新时使用。
             1'b1: 立即生效，不做同步，用于静态配置。（默认值）
   UNION结构:  ET_SYNC_BYPASS_UNION */
#define ET_SYNC_BYPASS_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD20)

/* 寄存器说明：
 bit[31:6]   
 bit[5:0]    RAM时钟切换最小间隔cycle数，可维可测，建议使用默认值0x06
   UNION结构:  ET_CK_SWCH_CNT_UNION */
#define ET_CK_SWCH_CNT_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD24)

/* 寄存器说明：
 bit[31:4]   
 bit[3]      tx动态延时减少
             1'b0: 支持动态减少延时，tx整数延时每次动态减少一个样点。
             1'b1: 不支持动态减少延时，默认值。
 bit[2]      tx动态延时增加
             1'b0: 支持动态增加延时，tx整数延时每次动态增加一个样点。
             1'b1: 不支持动态增加延时，默认值。
 bit[1]      et动态延时减少
             1'b0: 支持动态减少延时。
             1'b1: 不支持动态减少延时，默认值。
 bit[0]      et动态延时增加
             1'b0: 支持动态增加延时。
             1'b1: 不支持动态增加延时，默认值。
   UNION结构:  ET_DYM_ADJ_DISABLE_UNION */
#define ET_DYM_ADJ_DISABLE_ADDR                       (SOC_BBP_ET_BASE_ADDR + 0xD28)

/* 寄存器说明：
 bit[31:2]   
 bit[1]      分数延迟定时生效精确对齐使能：
             1'b1: 不做精确对齐（默认值）
             1'b0: 打开精确对齐
 bit[0]      分数延迟定时生效时刻：
             1'b1: 偶数时刻生效
             1'b0: 奇数时刻生效
   UNION结构:  ET_DYM_FRAC_SEL_UNION */
#define ET_DYM_FRAC_SEL_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0xD2C)

/* 寄存器说明：
 bit[31:1]   
 bit[0]      寄存器模块时钟门控屏蔽：
             1'b1: 屏蔽该门控（时钟常开）
             1'b0: 寄存器模块时钟自动门控
   UNION结构:  ET_REG_CK_SEL_UNION */
#define ET_REG_CK_SEL_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xD30)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define ET_ET_RESERVE0_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD34)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define ET_ET_RESERVE1_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD38)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define ET_ET_RESERVE2_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD3C)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define ET_ET_RESERVE3_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD40)





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
                     (1/1) register_define_et
 ***======================================================================***/
/*****************************************************************************
 结构名    : ET_ET_SOFT_RST_UNION
 结构说明  : ET_SOFT_RST 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_soft_rst_reg;
    struct
    {
        unsigned int  et_soft_rst : 1;  /* bit[0]   : et软复位信号。
                                                      1：表示复位
                                                      0：表示清复位 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} ET_ET_SOFT_RST_UNION;
#define ET_ET_SOFT_RST_et_soft_rst_START  (0)
#define ET_ET_SOFT_RST_et_soft_rst_END    (0)


/*****************************************************************************
 结构名    : ET_ET_RAM_CTRL0_UNION
 结构说明  : ET_RAM_CTRL0 寄存器结构定义。地址偏移量:0x004，初值:0x10500350，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ram_ctrl0_reg;
    struct
    {
        unsigned int  et_tpram_ctrl : 16; /* bit[0-15] : tpram mem_ctrl */
        unsigned int  et_spram_ctrl : 16; /* bit[16-31]: spram mem_ctrl */
    } reg;
} ET_ET_RAM_CTRL0_UNION;
#define ET_ET_RAM_CTRL0_et_tpram_ctrl_START  (0)
#define ET_ET_RAM_CTRL0_et_tpram_ctrl_END    (15)
#define ET_ET_RAM_CTRL0_et_spram_ctrl_START  (16)
#define ET_ET_RAM_CTRL0_et_spram_ctrl_END    (31)


/*****************************************************************************
 结构名    : ET_PA_PARA_UNION
 结构说明  : PA_PARA 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      pa_para_reg;
    struct
    {
        unsigned int  reserved_0       : 4;  /* bit[0-3] : 保留。 */
        unsigned int  dsp_pa_mid_ctrl  : 2;  /* bit[4-5] : PA中档位匹配指示信号。如果线控信号com2et_tx_pa_mode与dsp_pa_high_ctrl不匹配但与该字段匹配，可以确定PA是工作在中增益模式。 */
        unsigned int  dsp_pa_high_ctrl : 2;  /* bit[6-7] : PA高档位匹配指示信号。如果线控信号com2et_tx_pa_mode与该字段
                                                           匹配，可以确定PA是工作在高增益模式。 */
        unsigned int  reserved_1       : 24; /* bit[8-31]: 保留。 */
    } reg;
} ET_PA_PARA_UNION;
#define ET_PA_PARA_dsp_pa_mid_ctrl_START   (4)
#define ET_PA_PARA_dsp_pa_mid_ctrl_END     (5)
#define ET_PA_PARA_dsp_pa_high_ctrl_START  (6)
#define ET_PA_PARA_dsp_pa_high_ctrl_END    (7)


/*****************************************************************************
 结构名    : ET_RF_DATA_DLY_UNION
 结构说明  : RF_DATA_DLY 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      rf_data_dly_reg;
    struct
    {
        unsigned int  dsp_tx_dly_num : 9;  /* bit[0-8] : 射频数据通路延迟配置值。当com2et_tx_clk时钟频率和数据通路数据率之比为4:1时，取值范围为0~508，当为2:1时，取值范围为0~254，单位为数据通路时钟周期。 */
        unsigned int  reserved       : 23; /* bit[9-31]: 保留。 */
    } reg;
} ET_RF_DATA_DLY_UNION;
#define ET_RF_DATA_DLY_dsp_tx_dly_num_START  (0)
#define ET_RF_DATA_DLY_dsp_tx_dly_num_END    (8)


/*****************************************************************************
 结构名    : ET_LW_MODE_SEL_UNION
 结构说明  : LW_MODE_SEL 寄存器结构定义。地址偏移量:0x010，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      lw_mode_sel_reg;
    struct
    {
        unsigned int  lw_mode_sel : 2;  /* bit[0-1] : L/W模式选择，
                                                      01: LTE mode, 
                                                      10: W mode, 
                                                      00: L/W均无效，ET模块无时钟，且自动进入软复位，跳至其他状态时解复位
                                                      11: 无效状态
                                                      
                                                      例如从L模切到W模，lw_mode_sel变化过程2'b01 -> 2'b00（软复位） -> 2'b10 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留。 */
    } reg;
} ET_LW_MODE_SEL_UNION;
#define ET_LW_MODE_SEL_lw_mode_sel_START  (0)
#define ET_LW_MODE_SEL_lw_mode_sel_END    (1)


/*****************************************************************************
 结构名    : ET_SOFT_EN_UNION
 结构说明  : SOFT_EN 寄存器结构定义。地址偏移量:0x014，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      soft_en_reg;
    struct
    {
        unsigned int  soft_en  : 1;  /* bit[0]   : 软件关闭ET0通道。
                                                   1'b1 : ET0正常工作，默认值；
                                                   1'b0 : ET0关闭，时钟门控，逻辑软复位；
                                                   
                                                   注：关闭此寄存器会影响ET0 tx通路数据发送。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} ET_SOFT_EN_UNION;
#define ET_SOFT_EN_soft_en_START   (0)
#define ET_SOFT_EN_soft_en_END     (0)


/*****************************************************************************
 结构名    : ET_ET_BYPASS_CTRL_UNION
 结构说明  : ET_BYPASS_CTRL 寄存器结构定义。地址偏移量:0xC00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_bypass_ctrl_reg;
    struct
    {
        unsigned int  et_linear_thd_bp      : 1;  /* bit[0]   : 线性限底功能bypass信号。
                                                                0：不bypass该功能。
                                                                1：bypass该功能。 */
        unsigned int  et_swing_bp           : 1;  /* bit[1]   : 线性限摆功能bypass信号。
                                                                0：不bypass该功能。
                                                                1：bypass该功能。 */
        unsigned int  et_voltage_adapter_bp : 1;  /* bit[2]   : 电压适配器功能旁路控制。
                                                                
                                                                0：不bypass该功能。
                                                                1：bypass该功能。 */
        unsigned int  et_iir_bp             : 1;  /* bit[3]   : 群延迟IIR滤波器功能旁路控制。
                                                                
                                                                0：不bypass该功能。
                                                                1：bypass该功能。 */
        unsigned int  et_fir_bp             : 1;  /* bit[4]   : 包络带宽FIR滤波器功能旁路控制。
                                                                
                                                                0：不bypass该功能。
                                                                1：bypass该功能。 */
        unsigned int  log_calc_bp           : 1;  /* bit[5]   : 线性转对数和射频功率估算功能bypass信号。
                                                                
                                                                0：不bypass该功能。
                                                                1：bypass该功能。 */
        unsigned int  reserved              : 26; /* bit[6-31]: 保留 */
    } reg;
} ET_ET_BYPASS_CTRL_UNION;
#define ET_ET_BYPASS_CTRL_et_linear_thd_bp_START       (0)
#define ET_ET_BYPASS_CTRL_et_linear_thd_bp_END         (0)
#define ET_ET_BYPASS_CTRL_et_swing_bp_START            (1)
#define ET_ET_BYPASS_CTRL_et_swing_bp_END              (1)
#define ET_ET_BYPASS_CTRL_et_voltage_adapter_bp_START  (2)
#define ET_ET_BYPASS_CTRL_et_voltage_adapter_bp_END    (2)
#define ET_ET_BYPASS_CTRL_et_iir_bp_START              (3)
#define ET_ET_BYPASS_CTRL_et_iir_bp_END                (3)
#define ET_ET_BYPASS_CTRL_et_fir_bp_START              (4)
#define ET_ET_BYPASS_CTRL_et_fir_bp_END                (4)
#define ET_ET_BYPASS_CTRL_log_calc_bp_START            (5)
#define ET_ET_BYPASS_CTRL_log_calc_bp_END              (5)


/*****************************************************************************
 结构名    : ET_ET_CKG_BYPASS_UNION
 结构说明  : ET_CKG_BYPASS 寄存器结构定义。地址偏移量:0xC04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ckg_bypass_reg;
    struct
    {
        unsigned int  et_ckg_bypass : 1;  /* bit[0]   : ET功能自动门控旁路信号。
                                                        0：自动门控不旁路；
                                                        1：自动门控旁路。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} ET_ET_CKG_BYPASS_UNION;
#define ET_ET_CKG_BYPASS_et_ckg_bypass_START  (0)
#define ET_ET_CKG_BYPASS_et_ckg_bypass_END    (0)


/*****************************************************************************
 结构名    : ET_ET_DELAY_PARA_UNION
 结构说明  : ET_DELAY_PARA 寄存器结构定义。地址偏移量:0xC08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_delay_para_reg;
    struct
    {
        unsigned int  dsp_et_dly_num : 8;  /* bit[0-7] : ET包络信号通路延迟配置值，延迟配置范围0~254。最小延迟单位为1个随路时钟周期，即122M时钟情况下8.138ns */
        unsigned int  reserved       : 24; /* bit[8-31]: 保留 */
    } reg;
} ET_ET_DELAY_PARA_UNION;
#define ET_ET_DELAY_PARA_dsp_et_dly_num_START  (0)
#define ET_ET_DELAY_PARA_dsp_et_dly_num_END    (7)


/*****************************************************************************
 结构名    : ET_ET_UPSAMPLE_SEL_UNION
 结构说明  : ET_UPSAMPLE_SEL 寄存器结构定义。地址偏移量:0xC18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_upsample_sel_reg;
    struct
    {
        unsigned int  et_upsample_sel : 1;  /* bit[0]   : 软件根据数据速率配置上采样选择，
                                                          1'b0: 做2倍上采样；
                                                          1'b1: 不做上采样 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} ET_ET_UPSAMPLE_SEL_UNION;
#define ET_ET_UPSAMPLE_SEL_et_upsample_sel_START  (0)
#define ET_ET_UPSAMPLE_SEL_et_upsample_sel_END    (0)


/*****************************************************************************
 结构名    : ET_ET_INT_FILTER_CTRL_UNION
 结构说明  : ET_INT_FILTER_CTRL 寄存器结构定义。地址偏移量:0xC1C，初值:0x00000011，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_int_filter_ctrl_reg;
    struct
    {
        unsigned int  dsp_int_1filter_center : 2;  /* bit[0-1] : 第1组分数延迟滤波器插值中心选择。
                                                                 此处不开放给软件使用，只能配默认值2'b01 。
                                                                 00：表示插值滤波器中心位于x(n+1)；
                                                                 01：表示插值滤波器中心位于x(n)；
                                                                 10：表示插值滤波器中心位于x(n-1)；
                                                                 11：无效配置。 */
        unsigned int  reserved_0             : 2;  /* bit[2-3] : 保留 */
        unsigned int  dsp_int_0filter_center : 2;  /* bit[4-5] : 第0组分数延迟滤波器插值中心选择。
                                                                 此处不开放给软件使用，只能配默认值2'b01 。
                                                                 00：表示插值滤波器中心位于x(n+1)；
                                                                 01：表示插值滤波器中心位于x(n)；
                                                                 10：表示插值滤波器中心位于x(n-1)；
                                                                 11：无效配置。 */
        unsigned int  reserved_1             : 26; /* bit[6-31]: 保留 */
    } reg;
} ET_ET_INT_FILTER_CTRL_UNION;
#define ET_ET_INT_FILTER_CTRL_dsp_int_1filter_center_START  (0)
#define ET_ET_INT_FILTER_CTRL_dsp_int_1filter_center_END    (1)
#define ET_ET_INT_FILTER_CTRL_dsp_int_0filter_center_START  (4)
#define ET_ET_INT_FILTER_CTRL_dsp_int_0filter_center_END    (5)


/*****************************************************************************
 结构名    : ET_ET_FINE_0DELAY_PARA_0_UNION
 结构说明  : ET_FINE_0DELAY_PARA_0 寄存器结构定义。地址偏移量:0xC20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_0_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_1para : 12; /* bit[0-11] : 分数延迟滤波器0组系数1，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_0delay_0para : 12; /* bit[16-27]: 分数延迟滤波器0组系数0，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_0DELAY_PARA_0_UNION;
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_1para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_1para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_0para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_0para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_0DELAY_PARA_1_UNION
 结构说明  : ET_FINE_0DELAY_PARA_1 寄存器结构定义。地址偏移量:0xC24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_1_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_3para : 12; /* bit[0-11] : 分数延迟滤波器0组系数3，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_0delay_2para : 12; /* bit[16-27]: 分数延迟滤波器0组系数2，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_0DELAY_PARA_1_UNION;
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_3para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_3para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_2para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_2para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_0DELAY_PARA_2_UNION
 结构说明  : ET_FINE_0DELAY_PARA_2 寄存器结构定义。地址偏移量:0xC28，初值:0x07FF0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_2_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_5para : 12; /* bit[0-11] : 分数延迟滤波器0组系数5，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_0delay_4para : 12; /* bit[16-27]: 分数延迟滤波器0组系数4，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_0DELAY_PARA_2_UNION;
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_5para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_5para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_4para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_4para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_0DELAY_PARA_3_UNION
 结构说明  : ET_FINE_0DELAY_PARA_3 寄存器结构定义。地址偏移量:0xC2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_3_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_7para : 12; /* bit[0-11] : 分数延迟滤波器0组系数7，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_0delay_6para : 12; /* bit[16-27]: 分数延迟滤波器0组系数6，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_0DELAY_PARA_3_UNION;
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_7para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_7para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_6para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_6para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_0DELAY_PARA_4_UNION
 结构说明  : ET_FINE_0DELAY_PARA_4 寄存器结构定义。地址偏移量:0xC30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_4_reg;
    struct
    {
        unsigned int  reserved_0            : 16; /* bit[0-15] : 保留 */
        unsigned int  dsp_fine_0delay_8para : 12; /* bit[16-27]: 分数延迟滤波器0组系数8，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_0DELAY_PARA_4_UNION;
#define ET_ET_FINE_0DELAY_PARA_4_dsp_fine_0delay_8para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_4_dsp_fine_0delay_8para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_1DELAY_PARA_0_UNION
 结构说明  : ET_FINE_1DELAY_PARA_0 寄存器结构定义。地址偏移量:0xC34，初值:0x0FE40069，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_0_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_1para : 12; /* bit[0-11] : 分数延迟滤波器1组系数1，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_1delay_0para : 12; /* bit[16-27]: 分数延迟滤波器1组系数0，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_1DELAY_PARA_0_UNION;
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_1para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_1para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_0para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_0para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_1DELAY_PARA_1_UNION
 结构说明  : ET_FINE_1DELAY_PARA_1 寄存器结构定义。地址偏移量:0xC38，初值:0x0ED504A8，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_1_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_3para : 12; /* bit[0-11] : 分数延迟滤波器1组系数3，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_1delay_2para : 12; /* bit[16-27]: 分数延迟滤波器1组系数2，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_1DELAY_PARA_1_UNION;
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_3para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_3para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_2para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_2para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_1DELAY_PARA_2_UNION
 结构说明  : ET_FINE_1DELAY_PARA_2 寄存器结构定义。地址偏移量:0xC3C，初值:0x05180E73，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_2_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_5para : 12; /* bit[0-11] : 分数延迟滤波器1组系数5，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_1delay_4para : 12; /* bit[16-27]: 分数延迟滤波器1组系数4，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_1DELAY_PARA_2_UNION;
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_5para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_5para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_4para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_4para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_1DELAY_PARA_3_UNION
 结构说明  : ET_FINE_1DELAY_PARA_3 寄存器结构定义。地址偏移量:0xC40，初值:0x00B30FB5，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_3_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_7para : 12; /* bit[0-11] : 分数延迟滤波器1组系数7，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsp_fine_1delay_6para : 12; /* bit[16-27]: 分数延迟滤波器1组系数6，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_1DELAY_PARA_3_UNION;
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_7para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_7para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_6para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_6para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FINE_1DELAY_PARA_4_UNION
 结构说明  : ET_FINE_1DELAY_PARA_4 寄存器结构定义。地址偏移量:0xC44，初值:0x00150000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_4_reg;
    struct
    {
        unsigned int  reserved_0            : 16; /* bit[0-15] : 保留 */
        unsigned int  dsp_fine_1delay_8para : 12; /* bit[16-27]: 分数延迟滤波器1组系数8，12bit有符号数，当启动包络检测功能时，该系数需要在上行建链之前完成配置。 */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FINE_1DELAY_PARA_4_UNION;
#define ET_ET_FINE_1DELAY_PARA_4_dsp_fine_1delay_8para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_4_dsp_fine_1delay_8para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_ENV_PROC_PARA1_UNION
 结构说明  : ET_ENV_PROC_PARA1 寄存器结构定义。地址偏移量:0xC4C，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_proc_para1_reg;
    struct
    {
        unsigned int  dsp_delay_max_num : 4;  /* bit[0-3] : 延迟取最大功能的延迟参数，4bit无符号数，取值N在0到15。 */
        unsigned int  reserved          : 28; /* bit[4-31]: 保留 */
    } reg;
} ET_ET_ENV_PROC_PARA1_UNION;
#define ET_ET_ENV_PROC_PARA1_dsp_delay_max_num_START  (0)
#define ET_ET_ENV_PROC_PARA1_dsp_delay_max_num_END    (3)


/*****************************************************************************
 结构名    : ET_ET_ENV_PROC_PARA2_UNION
 结构说明  : ET_ENV_PROC_PARA2 寄存器结构定义。地址偏移量:0xC50，初值:0x00C8003C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_proc_para2_reg;
    struct
    {
        unsigned int  dsp_env_ratio : 6;  /* bit[0-5]  : 线性Detrough参数，限底右移乘系数，6bit无符号数。 */
        unsigned int  reserved_0    : 10; /* bit[6-15] : 保留 */
        unsigned int  dsp_env_knee  : 12; /* bit[16-27]: 线性Detrough参数，包络线性限底门限。12bit无符号数。 */
        unsigned int  reserved_1    : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_ENV_PROC_PARA2_UNION;
#define ET_ET_ENV_PROC_PARA2_dsp_env_ratio_START  (0)
#define ET_ET_ENV_PROC_PARA2_dsp_env_ratio_END    (5)
#define ET_ET_ENV_PROC_PARA2_dsp_env_knee_START   (16)
#define ET_ET_ENV_PROC_PARA2_dsp_env_knee_END     (27)


/*****************************************************************************
 结构名    : ET_ET_ENV_PROC_PARA3_UNION
 结构说明  : ET_ENV_PROC_PARA3 寄存器结构定义。地址偏移量:0xC54，初值:0x00002D18，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_proc_para3_reg;
    struct
    {
        unsigned int  dsp_power_offset_para : 14; /* bit[0-13] : 射频包络功率计算参数，包络调节补偿值，14位有符号数，默认值-4840，精度0.0125dB，即-60.5dB。 */
        unsigned int  reserved              : 18; /* bit[14-31]: 保留 */
    } reg;
} ET_ET_ENV_PROC_PARA3_UNION;
#define ET_ET_ENV_PROC_PARA3_dsp_power_offset_para_START  (0)
#define ET_ET_ENV_PROC_PARA3_dsp_power_offset_para_END    (13)


/*****************************************************************************
 结构名    : ET_ET_PA_CTRL_UNION
 结构说明  : ET_PA_CTRL 寄存器结构定义。地址偏移量:0xC58，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_pa_ctrl_reg;
    struct
    {
        unsigned int  dsp_pa_ctrl_mode : 1;  /* bit[0]   : 当dsp_pa_ctrl_mode=0时，此时包络检测需要工作在高、中两种增益模式下；
                                                           
                                                           当dsp_pa_ctrl_mode=1时，此时包络检测仅需要工作在高增益模式下，线控信号et_tx_pa_mode应保证与寄存器字段dsp_pa_high_ctrl的值相同。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} ET_ET_PA_CTRL_UNION;
#define ET_ET_PA_CTRL_dsp_pa_ctrl_mode_START  (0)
#define ET_ET_PA_CTRL_dsp_pa_ctrl_mode_END    (0)


/*****************************************************************************
 结构名    : ET_ET_LIMIT_ENV_SLEW_PARA_UNION
 结构说明  : ET_LIMIT_ENV_SLEW_PARA 寄存器结构定义。地址偏移量:0xC60，初值:0x06400640，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_limit_env_slew_para_reg;
    struct
    {
        unsigned int  dsp_down_slew_thd : 13; /* bit[0-12] : 限摆下坡门限，W下默认值1600，LTE下自定义，取值范围0~8191。无符号数 */
        unsigned int  reserved_0        : 3;  /* bit[13-15]: 保留 */
        unsigned int  dsp_up_slew_thd   : 13; /* bit[16-28]: 限摆上坡门限，缺省值1600，取值范围0~8191。无符号数 */
        unsigned int  reserved_1        : 3;  /* bit[29-31]: 保留 */
    } reg;
} ET_ET_LIMIT_ENV_SLEW_PARA_UNION;
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_down_slew_thd_START  (0)
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_down_slew_thd_END    (12)
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_up_slew_thd_START    (16)
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_up_slew_thd_END      (28)


/*****************************************************************************
 结构名    : ET_ET_ENV_TOP_EXTRA_PARA_UNION
 结构说明  : ET_ENV_TOP_EXTRA_PARA 寄存器结构定义。地址偏移量:0xC68，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_top_extra_para_reg;
    struct
    {
        unsigned int  pre_offset         : 13; /* bit[0-12] : 线性转对数前使用的偏移。13位有符号值。 */
        unsigned int  dbb_tx_power_atten : 10; /* bit[13-22]: 天线差损补偿。该字段不开放给软件使用。在写入该寄存器时，应确保该字段始终写入0x000。有符号数。可维可测功能 */
        unsigned int  reserved           : 9;  /* bit[23-31]: 保留 */
    } reg;
} ET_ET_ENV_TOP_EXTRA_PARA_UNION;
#define ET_ET_ENV_TOP_EXTRA_PARA_pre_offset_START          (0)
#define ET_ET_ENV_TOP_EXTRA_PARA_pre_offset_END            (12)
#define ET_ET_ENV_TOP_EXTRA_PARA_dbb_tx_power_atten_START  (13)
#define ET_ET_ENV_TOP_EXTRA_PARA_dbb_tx_power_atten_END    (22)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_0_1_PARA_UNION
 结构说明  : ET_IIR_COEF_0_1_PARA 寄存器结构定义。地址偏移量:0xC6C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_0_1_para_reg;
    struct
    {
        unsigned int  iir_coef1_para : 12; /* bit[0-11] : 群延迟均衡器IIR滤波器系数a12，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  iir_coef0_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数a11，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_0_1_PARA_UNION;
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef1_para_START  (0)
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef1_para_END    (11)
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef0_para_START  (16)
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef0_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_2_3_PARA_UNION
 结构说明  : ET_IIR_COEF_2_3_PARA 寄存器结构定义。地址偏移量:0xC70，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_2_3_para_reg;
    struct
    {
        unsigned int  iir_coef3_para : 12; /* bit[0-11] : 群延迟均衡器IIR滤波器系数b12，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  iir_coef2_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数b11，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_2_3_PARA_UNION;
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef3_para_START  (0)
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef3_para_END    (11)
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef2_para_START  (16)
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef2_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_4_5_PARA_UNION
 结构说明  : ET_IIR_COEF_4_5_PARA 寄存器结构定义。地址偏移量:0xC74，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_4_5_para_reg;
    struct
    {
        unsigned int  iir_coef5_para : 12; /* bit[0-11] : 群延迟均衡器IIR滤波器系数a21，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  iir_coef4_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数b13，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_4_5_PARA_UNION;
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef5_para_START  (0)
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef5_para_END    (11)
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef4_para_START  (16)
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef4_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_6_7_PARA_UNION
 结构说明  : ET_IIR_COEF_6_7_PARA 寄存器结构定义。地址偏移量:0xC78，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_6_7_para_reg;
    struct
    {
        unsigned int  iir_coef7_para : 12; /* bit[0-11] : 群延迟均衡器IIR滤波器系数b21，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  iir_coef6_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数a22，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_6_7_PARA_UNION;
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef7_para_START  (0)
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef7_para_END    (11)
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef6_para_START  (16)
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef6_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_8_9_PARA_UNION
 结构说明  : ET_IIR_COEF_8_9_PARA 寄存器结构定义。地址偏移量:0xC7C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_8_9_para_reg;
    struct
    {
        unsigned int  iir_coef9_para : 12; /* bit[0-11] : 群延迟均衡器IIR滤波器系数b23，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  iir_coef8_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数b22，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_8_9_PARA_UNION;
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef9_para_START  (0)
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef9_para_END    (11)
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef8_para_START  (16)
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef8_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_10_11_PARA_UNION
 结构说明  : ET_IIR_COEF_10_11_PARA 寄存器结构定义。地址偏移量:0xC80，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_10_11_para_reg;
    struct
    {
        unsigned int  iir_coef11_para : 12; /* bit[0-11] : 群延迟均衡器IIR滤波器系数a32，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  iir_coef10_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数a31，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_10_11_PARA_UNION;
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef11_para_START  (0)
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef11_para_END    (11)
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef10_para_START  (16)
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef10_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_12_13_PARA_UNION
 结构说明  : ET_IIR_COEF_12_13_PARA 寄存器结构定义。地址偏移量:0xC84，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_12_13_para_reg;
    struct
    {
        unsigned int  iir_coef13_para : 12; /* bit[0-11] : 群延迟均衡器IIR滤波器系数b32，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  iir_coef12_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数b31，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_12_13_PARA_UNION;
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef13_para_START  (0)
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef13_para_END    (11)
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef12_para_START  (16)
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef12_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_COEF_14_PARA_UNION
 结构说明  : ET_IIR_COEF_14_PARA 寄存器结构定义。地址偏移量:0xC88，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_14_para_reg;
    struct
    {
        unsigned int  reserved_0      : 16; /* bit[0-15] : 保留 */
        unsigned int  iir_coef14_para : 12; /* bit[16-27]: 群延迟均衡器IIR滤波器系数b33，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_IIR_COEF_14_PARA_UNION;
#define ET_ET_IIR_COEF_14_PARA_iir_coef14_para_START  (16)
#define ET_ET_IIR_COEF_14_PARA_iir_coef14_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_IIR_SHIFT_PARA_UNION
 结构说明  : ET_IIR_SHIFT_PARA 寄存器结构定义。地址偏移量:0xC8C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_shift_para_reg;
    struct
    {
        unsigned int  iir_shift0_para  : 2;  /* bit[0-1]  : 群延迟均衡器IIR滤波器a11支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift1_para  : 2;  /* bit[2-3]  : 群延迟均衡器IIR滤波器a12支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift2_para  : 2;  /* bit[4-5]  : 群延迟均衡器IIR滤波器b11支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift3_para  : 2;  /* bit[6-7]  : 群延迟均衡器IIR滤波器b12支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift4_para  : 2;  /* bit[8-9]  : 群延迟均衡器IIR滤波器b13支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift5_para  : 2;  /* bit[10-11]: 群延迟均衡器IIR滤波器a21支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift6_para  : 2;  /* bit[12-13]: 群延迟均衡器IIR滤波器a22支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift7_para  : 2;  /* bit[14-15]: 群延迟均衡器IIR滤波器b21支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift8_para  : 2;  /* bit[16-17]: 群延迟均衡器IIR滤波器b22支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift9_para  : 2;  /* bit[18-19]: 群延迟均衡器IIR滤波器b23支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift10_para : 2;  /* bit[20-21]: 群延迟均衡器IIR滤波器a31算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift11_para : 2;  /* bit[22-23]: 群延迟均衡器IIR滤波器a32支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift12_para : 2;  /* bit[24-25]: 群延迟均衡器IIR滤波器b31支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift13_para : 2;  /* bit[26-27]: 群延迟均衡器IIR滤波器b32支路算术右移移位次数控制。
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift14_para : 2;  /* bit[28-29]: 群延迟均衡器IIR滤波器b33支路算术右移移位次数控制。无符号
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} ET_ET_IIR_SHIFT_PARA_UNION;
#define ET_ET_IIR_SHIFT_PARA_iir_shift0_para_START   (0)
#define ET_ET_IIR_SHIFT_PARA_iir_shift0_para_END     (1)
#define ET_ET_IIR_SHIFT_PARA_iir_shift1_para_START   (2)
#define ET_ET_IIR_SHIFT_PARA_iir_shift1_para_END     (3)
#define ET_ET_IIR_SHIFT_PARA_iir_shift2_para_START   (4)
#define ET_ET_IIR_SHIFT_PARA_iir_shift2_para_END     (5)
#define ET_ET_IIR_SHIFT_PARA_iir_shift3_para_START   (6)
#define ET_ET_IIR_SHIFT_PARA_iir_shift3_para_END     (7)
#define ET_ET_IIR_SHIFT_PARA_iir_shift4_para_START   (8)
#define ET_ET_IIR_SHIFT_PARA_iir_shift4_para_END     (9)
#define ET_ET_IIR_SHIFT_PARA_iir_shift5_para_START   (10)
#define ET_ET_IIR_SHIFT_PARA_iir_shift5_para_END     (11)
#define ET_ET_IIR_SHIFT_PARA_iir_shift6_para_START   (12)
#define ET_ET_IIR_SHIFT_PARA_iir_shift6_para_END     (13)
#define ET_ET_IIR_SHIFT_PARA_iir_shift7_para_START   (14)
#define ET_ET_IIR_SHIFT_PARA_iir_shift7_para_END     (15)
#define ET_ET_IIR_SHIFT_PARA_iir_shift8_para_START   (16)
#define ET_ET_IIR_SHIFT_PARA_iir_shift8_para_END     (17)
#define ET_ET_IIR_SHIFT_PARA_iir_shift9_para_START   (18)
#define ET_ET_IIR_SHIFT_PARA_iir_shift9_para_END     (19)
#define ET_ET_IIR_SHIFT_PARA_iir_shift10_para_START  (20)
#define ET_ET_IIR_SHIFT_PARA_iir_shift10_para_END    (21)
#define ET_ET_IIR_SHIFT_PARA_iir_shift11_para_START  (22)
#define ET_ET_IIR_SHIFT_PARA_iir_shift11_para_END    (23)
#define ET_ET_IIR_SHIFT_PARA_iir_shift12_para_START  (24)
#define ET_ET_IIR_SHIFT_PARA_iir_shift12_para_END    (25)
#define ET_ET_IIR_SHIFT_PARA_iir_shift13_para_START  (26)
#define ET_ET_IIR_SHIFT_PARA_iir_shift13_para_END    (27)
#define ET_ET_IIR_SHIFT_PARA_iir_shift14_para_START  (28)
#define ET_ET_IIR_SHIFT_PARA_iir_shift14_para_END    (29)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_0_1_PARA_UNION
 结构说明  : ET_FIR_COEF_0_1_PARA 寄存器结构定义。地址偏移量:0xC90，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_0_1_para_reg;
    struct
    {
        unsigned int  fir_coef1_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^1的系数，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef0_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^0的系数（对应数据延迟最小），有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_0_1_PARA_UNION;
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef1_para_START  (0)
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef1_para_END    (11)
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef0_para_START  (16)
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef0_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_2_3_PARA_UNION
 结构说明  : ET_FIR_COEF_2_3_PARA 寄存器结构定义。地址偏移量:0xC94，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_2_3_para_reg;
    struct
    {
        unsigned int  fir_coef3_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^3的系数，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef2_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^2的系数，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_2_3_PARA_UNION;
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef3_para_START  (0)
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef3_para_END    (11)
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef2_para_START  (16)
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef2_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_4_5_PARA_UNION
 结构说明  : ET_FIR_COEF_4_5_PARA 寄存器结构定义。地址偏移量:0xC98，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_4_5_para_reg;
    struct
    {
        unsigned int  fir_coef5_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^5的系数，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef4_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^4的系数，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_4_5_PARA_UNION;
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef5_para_START  (0)
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef5_para_END    (11)
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef4_para_START  (16)
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef4_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_6_7_PARA_UNION
 结构说明  : ET_FIR_COEF_6_7_PARA 寄存器结构定义。地址偏移量:0xC9C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_6_7_para_reg;
    struct
    {
        unsigned int  fir_coef7_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^7的系数，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef6_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^6的系数，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_6_7_PARA_UNION;
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef7_para_START  (0)
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef7_para_END    (11)
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef6_para_START  (16)
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef6_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_8_9_PARA_UNION
 结构说明  : ET_FIR_COEF_8_9_PARA 寄存器结构定义。地址偏移量:0xCA0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_8_9_para_reg;
    struct
    {
        unsigned int  fir_coef9_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^9的系数，有符号数。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef8_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^8的系数，有符号数。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_8_9_PARA_UNION;
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef9_para_START  (0)
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef9_para_END    (11)
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef8_para_START  (16)
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef8_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_10_11_PARA_UNION
 结构说明  : ET_FIR_COEF_10_11_PARA 寄存器结构定义。地址偏移量:0xCA4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_10_11_para_reg;
    struct
    {
        unsigned int  fir_coef11_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^11的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef10_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^10的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_10_11_PARA_UNION;
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef11_para_START  (0)
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef11_para_END    (11)
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef10_para_START  (16)
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef10_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_12_13_PARA_UNION
 结构说明  : ET_FIR_COEF_12_13_PARA 寄存器结构定义。地址偏移量:0xCA8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_12_13_para_reg;
    struct
    {
        unsigned int  fir_coef13_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^13的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef12_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^12的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_12_13_PARA_UNION;
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef13_para_START  (0)
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef13_para_END    (11)
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef12_para_START  (16)
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef12_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_14_15_PARA_UNION
 结构说明  : ET_FIR_COEF_14_15_PARA 寄存器结构定义。地址偏移量:0xCAC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_14_15_para_reg;
    struct
    {
        unsigned int  fir_coef15_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^15的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef14_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^14的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_14_15_PARA_UNION;
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef15_para_START  (0)
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef15_para_END    (11)
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef14_para_START  (16)
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef14_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_16_17_PARA_UNION
 结构说明  : ET_FIR_COEF_16_17_PARA 寄存器结构定义。地址偏移量:0xCB0，初值:0x000007FF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_16_17_para_reg;
    struct
    {
        unsigned int  fir_coef17_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^17的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef16_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^16的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_16_17_PARA_UNION;
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef17_para_START  (0)
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef17_para_END    (11)
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef16_para_START  (16)
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef16_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_18_19_PARA_UNION
 结构说明  : ET_FIR_COEF_18_19_PARA 寄存器结构定义。地址偏移量:0xCB4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_18_19_para_reg;
    struct
    {
        unsigned int  fir_coef19_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^19的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef18_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^18的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_18_19_PARA_UNION;
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef19_para_START  (0)
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef19_para_END    (11)
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef18_para_START  (16)
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef18_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_20_21_PARA_UNION
 结构说明  : ET_FIR_COEF_20_21_PARA 寄存器结构定义。地址偏移量:0xCB8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_20_21_para_reg;
    struct
    {
        unsigned int  fir_coef21_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^21的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef20_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^20的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_20_21_PARA_UNION;
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef21_para_START  (0)
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef21_para_END    (11)
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef20_para_START  (16)
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef20_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_22_23_PARA_UNION
 结构说明  : ET_FIR_COEF_22_23_PARA 寄存器结构定义。地址偏移量:0xCBC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_22_23_para_reg;
    struct
    {
        unsigned int  fir_coef23_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^23的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef22_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^22的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_22_23_PARA_UNION;
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef23_para_START  (0)
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef23_para_END    (11)
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef22_para_START  (16)
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef22_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_24_25_PARA_UNION
 结构说明  : ET_FIR_COEF_24_25_PARA 寄存器结构定义。地址偏移量:0xCC0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_24_25_para_reg;
    struct
    {
        unsigned int  fir_coef25_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^25的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef24_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^24的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_24_25_PARA_UNION;
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef25_para_START  (0)
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef25_para_END    (11)
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef24_para_START  (16)
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef24_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_26_27_PARA_UNION
 结构说明  : ET_FIR_COEF_26_27_PARA 寄存器结构定义。地址偏移量:0xCC4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_26_27_para_reg;
    struct
    {
        unsigned int  fir_coef27_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^27的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef26_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^26的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_26_27_PARA_UNION;
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef27_para_START  (0)
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef27_para_END    (11)
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef26_para_START  (16)
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef26_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_28_29_PARA_UNION
 结构说明  : ET_FIR_COEF_28_29_PARA 寄存器结构定义。地址偏移量:0xCC8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_28_29_para_reg;
    struct
    {
        unsigned int  fir_coef29_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^29的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef28_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^28的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_28_29_PARA_UNION;
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef29_para_START  (0)
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef29_para_END    (11)
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef28_para_START  (16)
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef28_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_30_31_PARA_UNION
 结构说明  : ET_FIR_COEF_30_31_PARA 寄存器结构定义。地址偏移量:0xCCC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_30_31_para_reg;
    struct
    {
        unsigned int  fir_coef31_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^31的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef30_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^30的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_30_31_PARA_UNION;
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef31_para_START  (0)
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef31_para_END    (11)
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef30_para_START  (16)
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef30_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_32_33_PARA_UNION
 结构说明  : ET_FIR_COEF_32_33_PARA 寄存器结构定义。地址偏移量:0xCD0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_32_33_para_reg;
    struct
    {
        unsigned int  fir_coef33_para : 12; /* bit[0-11] : 包络带宽FIR滤波器抽头(1/z)^33的系数，有符号数。 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  fir_coef32_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^32的系数，有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_32_33_PARA_UNION;
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef33_para_START  (0)
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef33_para_END    (11)
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef32_para_START  (16)
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef32_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_FIR_COEF_34_PARA_UNION
 结构说明  : ET_FIR_COEF_34_PARA 寄存器结构定义。地址偏移量:0xCD4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_34_para_reg;
    struct
    {
        unsigned int  reserved_0      : 16; /* bit[0-15] : 保留 */
        unsigned int  fir_coef34_para : 12; /* bit[16-27]: 包络带宽FIR滤波器抽头(1/z)^34的系数（对应数据延迟最大），有符号数。 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} ET_ET_FIR_COEF_34_PARA_UNION;
#define ET_ET_FIR_COEF_34_PARA_fir_coef34_para_START  (16)
#define ET_ET_FIR_COEF_34_PARA_fir_coef34_para_END    (27)


/*****************************************************************************
 结构名    : ET_ET_CTRL_DELAY0_UNION
 结构说明  : ET_CTRL_DELAY0 寄存器结构定义。地址偏移量:0xCE4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay0_reg;
    struct
    {
        unsigned int  ctrl_dly_t1 : 16; /* bit[0-15] : t延时单位为随路时钟周期
                                                       各t延时约束关系：
                                                       t3 >= t1 ;
                                                       t4 < t6 ;
                                                       t4+t5 > t6+t7 ;
                                                       
                                                       通道0控制ctrl2swch_et_mode_sel, ctrl2swch_apt_pa_vcc_ind, ctrl2proc_et_mode_en的延迟；
                                                       配置延时值不应超过et通路总延时，下同。
                                                       
                                                       一组t延时参考值：
                                                       若et通路整数延迟寄存器值为x，则t1 = x + 'd51; t2 = 0;
                                                       t3 = x + 'd51; 
                                                       t4 = x + 'd51; t5 = 0; 
                                                       t6 = x + 'd51; t7 = 0; 
                                                       t8 = x + 'd96; */
        unsigned int  ctrl_dly_t2 : 16; /* bit[16-31]: 通道0控制ctrl2proc_et_mode_en下降沿的延迟，无符号数。
                                                       配置延时值不应超过et通路总延时。 */
    } reg;
} ET_ET_CTRL_DELAY0_UNION;
#define ET_ET_CTRL_DELAY0_ctrl_dly_t1_START  (0)
#define ET_ET_CTRL_DELAY0_ctrl_dly_t1_END    (15)
#define ET_ET_CTRL_DELAY0_ctrl_dly_t2_START  (16)
#define ET_ET_CTRL_DELAY0_ctrl_dly_t2_END    (31)


/*****************************************************************************
 结构名    : ET_ET_CTRL_DELAY1_UNION
 结构说明  : ET_CTRL_DELAY1 寄存器结构定义。地址偏移量:0xCE8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay1_reg;
    struct
    {
        unsigned int  ctrl_dly_t3 : 16; /* bit[0-15] : 通道0控制et2pad_et_mode_sel的延迟，暂不使用。 */
        unsigned int  ctrl_dly_t8 : 16; /* bit[16-31]: et_ctrl内部使用，延时et_act_en */
    } reg;
} ET_ET_CTRL_DELAY1_UNION;
#define ET_ET_CTRL_DELAY1_ctrl_dly_t3_START  (0)
#define ET_ET_CTRL_DELAY1_ctrl_dly_t3_END    (15)
#define ET_ET_CTRL_DELAY1_ctrl_dly_t8_START  (16)
#define ET_ET_CTRL_DELAY1_ctrl_dly_t8_END    (31)


/*****************************************************************************
 结构名    : ET_ET_CTRL_DELAY2_UNION
 结构说明  : ET_CTRL_DELAY2 寄存器结构定义。地址偏移量:0xCEC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay2_reg;
    struct
    {
        unsigned int  ctrl_dly_t5 : 16; /* bit[0-15] : 通道0控制et2abb_act_en上升沿的延迟 */
        unsigned int  ctrl_dly_t4 : 16; /* bit[16-31]: 通道0控制et2abb_act_en下降沿的延迟 */
    } reg;
} ET_ET_CTRL_DELAY2_UNION;
#define ET_ET_CTRL_DELAY2_ctrl_dly_t5_START  (0)
#define ET_ET_CTRL_DELAY2_ctrl_dly_t5_END    (15)
#define ET_ET_CTRL_DELAY2_ctrl_dly_t4_START  (16)
#define ET_ET_CTRL_DELAY2_ctrl_dly_t4_END    (31)


/*****************************************************************************
 结构名    : ET_ET_CTRL_DELAY3_UNION
 结构说明  : ET_CTRL_DELAY3 寄存器结构定义。地址偏移量:0xCF0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay3_reg;
    struct
    {
        unsigned int  ctrl_dly_t6 : 16; /* bit[0-15] : 通道0控制et2abb_et_mode_sel上升沿的延迟 */
        unsigned int  ctrl_dly_t7 : 16; /* bit[16-31]: 通道0控制et2abb_et_mode_sel下降沿的延迟 */
    } reg;
} ET_ET_CTRL_DELAY3_UNION;
#define ET_ET_CTRL_DELAY3_ctrl_dly_t6_START  (0)
#define ET_ET_CTRL_DELAY3_ctrl_dly_t6_END    (15)
#define ET_ET_CTRL_DELAY3_ctrl_dly_t7_START  (16)
#define ET_ET_CTRL_DELAY3_ctrl_dly_t7_END    (31)


/*****************************************************************************
 结构名    : ET_ET_CTRL_ETM_MODE_UNION
 结构说明  : ET_CTRL_ETM_MODE 寄存器结构定义。地址偏移量:0xCF4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_etm_mode_reg;
    struct
    {
        unsigned int  ctrl_etm_mode : 3;  /* bit[0-2] : 
                                                        位[2]自研ETM选择，
                                                        0：使用第三方ETM，默认值；
                                                        
                                                        位[1:0]第三方ETM工作模式。
                                                        0：用于R2类型ETM器件，                  
                                                        1：用于TI类型ETM器件模式1。
                                                        2：用于TI类型ETM器件模式2。
                                                        3：用于TI类型ETM器件模式2。 */
        unsigned int  reserved      : 29; /* bit[3-31]: 保留 */
    } reg;
} ET_ET_CTRL_ETM_MODE_UNION;
#define ET_ET_CTRL_ETM_MODE_ctrl_etm_mode_START  (0)
#define ET_ET_CTRL_ETM_MODE_ctrl_etm_mode_END    (2)


/*****************************************************************************
 结构名    : ET_ET_PA_THD_PARA_HIGH_UNION
 结构说明  : ET_PA_THD_PARA_HIGH 寄存器结构定义。地址偏移量:0xC5C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_pa_thd_para_high_reg;
    struct
    {
        unsigned int  dsp_pa_mid_table_offset  : 11; /* bit[0-10] : 该参数表示PA中增益功率电压查找表第0项（在偏移地址0xA00处）对应的功率值，该参数为11bit无符号数，单位为0.0125dB，默认值为0。 */
        unsigned int  reserved_0               : 5;  /* bit[11-15]: 保留 */
        unsigned int  dsp_pa_high_table_offset : 11; /* bit[16-26]: 该参数表示PA高增益功率电压查找表第0项（在偏移地址0x800处）对应的功率值，该参数为11bit无符号数，单位为0.0125dB，默认值为0。 */
        unsigned int  reserved_1               : 5;  /* bit[27-31]: 保留 */
    } reg;
} ET_ET_PA_THD_PARA_HIGH_UNION;
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_mid_table_offset_START   (0)
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_mid_table_offset_END     (10)
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_high_table_offset_START  (16)
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_high_table_offset_END    (26)


/*****************************************************************************
 结构名    : ET_AUTO_RESET_UNION
 结构说明  : AUTO_RESET 寄存器结构定义。地址偏移量:0xCF8，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      auto_reset_reg;
    struct
    {
        unsigned int  mode_auto_reset_en : 1;  /* bit[0]   : L/W模式切换自动软复位使能
                                                             1：切模自动软复位
                                                             0：切模不触发复位 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留。 */
    } reg;
} ET_AUTO_RESET_UNION;
#define ET_AUTO_RESET_mode_auto_reset_en_START  (0)
#define ET_AUTO_RESET_mode_auto_reset_en_END    (0)


/*****************************************************************************
 结构名    : ET_APT_CALIBRE_MODE_UNION
 结构说明  : APT_CALIBRE_MODE 寄存器结构定义。地址偏移量:0xCFC，初值:0x0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      apt_calibre_mode_reg;
    struct
    {
        unsigned int  calibre_sel          : 1;  /* bit[0]   : 1'b1: 选择APT校准模式
                                                               1'b0: 正常工作模式，默认值 */
        unsigned int  calibre_abb_mode_sel : 1;  /* bit[1]   : 该bit只在APT校准模式下有效
                                                               1'b1: ABB工作在ET模式
                                                               1'b0: ABB工作在APT模式 */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留。 */
    } reg;
} ET_APT_CALIBRE_MODE_UNION;
#define ET_APT_CALIBRE_MODE_calibre_sel_START           (0)
#define ET_APT_CALIBRE_MODE_calibre_sel_END             (0)
#define ET_APT_CALIBRE_MODE_calibre_abb_mode_sel_START  (1)
#define ET_APT_CALIBRE_MODE_calibre_abb_mode_sel_END    (1)


/*****************************************************************************
 结构名    : ET_CALIBRE_VCC_UNION
 结构说明  : CALIBRE_VCC 寄存器结构定义。地址偏移量:0xD00，初值:0x0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      calibre_vcc_reg;
    struct
    {
        unsigned int  calibre_vcc : 14; /* bit[0-13] : 输出校准电压，有符号数 */
        unsigned int  reserved    : 18; /* bit[14-31]: 保留。 */
    } reg;
} ET_CALIBRE_VCC_UNION;
#define ET_CALIBRE_VCC_calibre_vcc_START  (0)
#define ET_CALIBRE_VCC_calibre_vcc_END    (13)


/*****************************************************************************
 结构名    : ET_INTRLV_SEL_UNION
 结构说明  : INTRLV_SEL 寄存器结构定义。地址偏移量:0xD04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      intrlv_sel_reg;
    struct
    {
        unsigned int  interleave_sel : 1;  /* bit[0]   : 包络通路输出交织顺序选择 
                                                         0: 先奇后偶，默认值  
                                                         1:先偶后奇 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} ET_INTRLV_SEL_UNION;
#define ET_INTRLV_SEL_interleave_sel_START  (0)
#define ET_INTRLV_SEL_interleave_sel_END    (0)


/*****************************************************************************
 结构名    : ET_ET_ALIGN_UNION
 结构说明  : ET_ALIGN 寄存器结构定义。地址偏移量:0xD08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_align_reg;
    struct
    {
        unsigned int  et_rf_align : 1;  /* bit[0]   : 包络和射频通路输入数据对齐指示,
                                                      0:对齐
                                                      1:不对齐标志 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} ET_ET_ALIGN_UNION;
#define ET_ET_ALIGN_et_rf_align_START  (0)
#define ET_ET_ALIGN_et_rf_align_END    (0)


/*****************************************************************************
 结构名    : ET_ET_STATUS_UNION
 结构说明  : ET_STATUS 寄存器结构定义。地址偏移量:0xD0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_status_reg;
    struct
    {
        unsigned int  apt2et_cnt : 8;  /* bit[0-7]  : APT模式切ET模式次数 */
        unsigned int  et2apt_cnt : 8;  /* bit[8-15] : ET模式切APT模式次数 */
        unsigned int  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} ET_ET_STATUS_UNION;
#define ET_ET_STATUS_apt2et_cnt_START  (0)
#define ET_ET_STATUS_apt2et_cnt_END    (7)
#define ET_ET_STATUS_et2apt_cnt_START  (8)
#define ET_ET_STATUS_et2apt_cnt_END    (15)


/*****************************************************************************
 结构名    : ET_ET_RPT_CLEAR_UNION
 结构说明  : ET_RPT_CLEAR 寄存器结构定义。地址偏移量:0xD10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      et_rpt_clear_reg;
    struct
    {
        unsigned int  et_rpt_clear : 1;  /* bit[0]   : 写1'b1，所有上报寄存器清零 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} ET_ET_RPT_CLEAR_UNION;
#define ET_ET_RPT_CLEAR_et_rpt_clear_START  (0)
#define ET_ET_RPT_CLEAR_et_rpt_clear_END    (0)


/*****************************************************************************
 结构名    : ET_LUT_RAM_SEL_UNION
 结构说明  : LUT_RAM_SEL 寄存器结构定义。地址偏移量:0xD14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      lut_ram_sel_reg;
    struct
    {
        unsigned int  lut_ram_sel : 2;  /* bit[0-1] : [1]: force config enable;
                                                      [0]: 1'b1, force select internal logic; 1'b0, force select lbus */
        unsigned int  reserved    : 30; /* bit[2-31]:  */
    } reg;
} ET_LUT_RAM_SEL_UNION;
#define ET_LUT_RAM_SEL_lut_ram_sel_START  (0)
#define ET_LUT_RAM_SEL_lut_ram_sel_END    (1)


/*****************************************************************************
 结构名    : ET_DBG_DAT_SEL_UNION
 结构说明  : DBG_DAT_SEL 寄存器结构定义。地址偏移量:0xD18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat_sel_reg;
    struct
    {
        unsigned int  dbg_dat_sel : 1;  /* bit[0]   : 调试数据选择，
                                                      1'b0:正常工作模式；
                                                      1'b1:使用dbg调试数据强配； */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} ET_DBG_DAT_SEL_UNION;
#define ET_DBG_DAT_SEL_dbg_dat_sel_START  (0)
#define ET_DBG_DAT_SEL_dbg_dat_sel_END    (0)


/*****************************************************************************
 结构名    : ET_DBG_DAT0_UNION
 结构说明  : DBG_DAT0 寄存器结构定义。地址偏移量:0xD1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat0_reg;
    struct
    {
        unsigned int  dbg_log_dat : 10; /* bit[0-9]  : dbg调试数据，用于强配线性转对数索引值。无符号，可维可测 */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} ET_DBG_DAT0_UNION;
#define ET_DBG_DAT0_dbg_log_dat_START  (0)
#define ET_DBG_DAT0_dbg_log_dat_END    (9)


/*****************************************************************************
 结构名    : ET_SYNC_BYPASS_UNION
 结构说明  : SYNC_BYPASS 寄存器结构定义。地址偏移量:0xD20，初值:0x00000007，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sync_bypass_reg;
    struct
    {
        unsigned int  usfd_sync_bp   : 1;  /* bit[0]   : usfd分数延迟同步方式：
                                                         1'b0: 定时生效，等待dly_para_ind线控，动态更新时使用。
                                                         1'b1: 立即生效，不做同步，用于静态配置。（默认值） */
        unsigned int  et_dly_sync_bp : 1;  /* bit[1]   : et整数延迟同步方式：
                                                         1'b0: 定时生效，等待dly_para_ind线控，动态更新时使用。
                                                         1'b1: 立即生效，不做同步，静态配置时使用。（默认值） */
        unsigned int  tx_dly_sync_bp : 1;  /* bit[2]   : tx整数延迟同步方式：
                                                         1'b0: 定时生效，等待dly_para_ind线控，动态更新时使用。
                                                         1'b1: 立即生效，不做同步，静态配置时使用。（默认值） */
        unsigned int  reserved       : 29; /* bit[3-31]:  */
    } reg;
} ET_SYNC_BYPASS_UNION;
#define ET_SYNC_BYPASS_usfd_sync_bp_START    (0)
#define ET_SYNC_BYPASS_usfd_sync_bp_END      (0)
#define ET_SYNC_BYPASS_et_dly_sync_bp_START  (1)
#define ET_SYNC_BYPASS_et_dly_sync_bp_END    (1)
#define ET_SYNC_BYPASS_tx_dly_sync_bp_START  (2)
#define ET_SYNC_BYPASS_tx_dly_sync_bp_END    (2)


/*****************************************************************************
 结构名    : ET_CK_SWCH_CNT_UNION
 结构说明  : CK_SWCH_CNT 寄存器结构定义。地址偏移量:0xD24，初值:0x00000006，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ck_swch_cnt_reg;
    struct
    {
        unsigned int  ck_swch_cnt_num : 6;  /* bit[0-5] : RAM时钟切换最小间隔cycle数，可维可测，建议使用默认值0x06 */
        unsigned int  reserved        : 26; /* bit[6-31]:  */
    } reg;
} ET_CK_SWCH_CNT_UNION;
#define ET_CK_SWCH_CNT_ck_swch_cnt_num_START  (0)
#define ET_CK_SWCH_CNT_ck_swch_cnt_num_END    (5)


/*****************************************************************************
 结构名    : ET_DYM_ADJ_DISABLE_UNION
 结构说明  : DYM_ADJ_DISABLE 寄存器结构定义。地址偏移量:0xD28，初值:0x0000000f，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dym_adj_disable_reg;
    struct
    {
        unsigned int  et_dym_inc_disable : 1;  /* bit[0]   : et动态延时增加
                                                             1'b0: 支持动态增加延时。
                                                             1'b1: 不支持动态增加延时，默认值。 */
        unsigned int  et_dym_dec_disable : 1;  /* bit[1]   : et动态延时减少
                                                             1'b0: 支持动态减少延时。
                                                             1'b1: 不支持动态减少延时，默认值。 */
        unsigned int  tx_dym_inc_disable : 1;  /* bit[2]   : tx动态延时增加
                                                             1'b0: 支持动态增加延时，tx整数延时每次动态增加一个样点。
                                                             1'b1: 不支持动态增加延时，默认值。 */
        unsigned int  tx_dym_dec_disable : 1;  /* bit[3]   : tx动态延时减少
                                                             1'b0: 支持动态减少延时，tx整数延时每次动态减少一个样点。
                                                             1'b1: 不支持动态减少延时，默认值。 */
        unsigned int  reserved           : 28; /* bit[4-31]:  */
    } reg;
} ET_DYM_ADJ_DISABLE_UNION;
#define ET_DYM_ADJ_DISABLE_et_dym_inc_disable_START  (0)
#define ET_DYM_ADJ_DISABLE_et_dym_inc_disable_END    (0)
#define ET_DYM_ADJ_DISABLE_et_dym_dec_disable_START  (1)
#define ET_DYM_ADJ_DISABLE_et_dym_dec_disable_END    (1)
#define ET_DYM_ADJ_DISABLE_tx_dym_inc_disable_START  (2)
#define ET_DYM_ADJ_DISABLE_tx_dym_inc_disable_END    (2)
#define ET_DYM_ADJ_DISABLE_tx_dym_dec_disable_START  (3)
#define ET_DYM_ADJ_DISABLE_tx_dym_dec_disable_END    (3)


/*****************************************************************************
 结构名    : ET_DYM_FRAC_SEL_UNION
 结构说明  : DYM_FRAC_SEL 寄存器结构定义。地址偏移量:0xD2C，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dym_frac_sel_reg;
    struct
    {
        unsigned int  dym_frac_sel    : 1;  /* bit[0]   : 分数延迟定时生效时刻：
                                                          1'b1: 偶数时刻生效
                                                          1'b0: 奇数时刻生效 */
        unsigned int  dym_frac_sel_bp : 1;  /* bit[1]   : 分数延迟定时生效精确对齐使能：
                                                          1'b1: 不做精确对齐（默认值）
                                                          1'b0: 打开精确对齐 */
        unsigned int  reserved        : 30; /* bit[2-31]:  */
    } reg;
} ET_DYM_FRAC_SEL_UNION;
#define ET_DYM_FRAC_SEL_dym_frac_sel_START     (0)
#define ET_DYM_FRAC_SEL_dym_frac_sel_END       (0)
#define ET_DYM_FRAC_SEL_dym_frac_sel_bp_START  (1)
#define ET_DYM_FRAC_SEL_dym_frac_sel_bp_END    (1)


/*****************************************************************************
 结构名    : ET_REG_CK_SEL_UNION
 结构说明  : REG_CK_SEL 寄存器结构定义。地址偏移量:0xD30，初值:0x0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      reg_ck_sel_reg;
    struct
    {
        unsigned int  reg_ck_sel : 1;  /* bit[0]   : 寄存器模块时钟门控屏蔽：
                                                     1'b1: 屏蔽该门控（时钟常开）
                                                     1'b0: 寄存器模块时钟自动门控 */
        unsigned int  reserved   : 31; /* bit[1-31]:  */
    } reg;
} ET_REG_CK_SEL_UNION;
#define ET_REG_CK_SEL_reg_ck_sel_START  (0)
#define ET_REG_CK_SEL_reg_ck_sel_END    (0)




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

#endif /* end of bbp_et_interface.h */
