/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_gsm_gtc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-09-02 16:48:16
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月2日
    作    者   : h00286049
    修改内容   : 从《芯片编号V3660 BBP寄存器手册_GSM_GTC.xml》自动生成，根据
	             当前的使用情况进行删减

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSM_GTC_INTERFACE_H__
#define __BBP_GSM_GTC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/9) register_define_fe_ctrl_auto
 ***======================================================================***/
/* 寄存器说明：
   详      述：bit7~0：GTC SPI串口待发送数据在SPI DATA RAM中的起始位置.
   UNION结构 ：无 */
#define GBBP_GTC_SPI_RD_START_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA0)

/* 寄存器说明：
 bit[7:5]
 bit[4:0]    bit4~bit0：本次需要发送的SPI串口数据数
             00001 表示1个数据
             10000 表示16个数据
   UNION结构:  GBBP_GTC_SPI_TRANS_DATA_NUM_UNION */
#define GBBP_GTC_SPI_TRANS_DATA_NUM_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA1)

/* 寄存器说明：
 bit[7:1]    
 bit[0]      GTC启动发送SPI数据脉冲
   UNION结构:  GBBP_GTC_SPI_RD_EN_UNION */
#define GBBP_GTC_SPI_RD_EN_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA2)

/* 寄存器说明：
 bit[7:1]    
 bit[0]      切换到G天线，切换到GTC内部寄存器27下的选择5，2M脉冲信号
   UNION结构:  GBBP_GTC_W2G_CTRL_UNION */
#define GBBP_GTC_W2G_CTRL_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB8)

/* 寄存器说明：
   详      述：31bit线控清零脉冲，控制bit[7:0]
               0：表示对应的bit不做处理；
               1：表示对应的bit位清0。
   UNION结构 ：无 */
#define GBBP_GTC_LINE1_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB9)

/* 寄存器说明：
   详      述：31bit线控生效脉冲，控制bit[7:0]
               0：表示对应的bit不做任何处理；
               1：表示对应的bit位置1。
   UNION结构 ：无 */
#define GBBP_GTC_LINE1_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBA)

/* 寄存器说明：
   详      述：31bit线控清零脉冲，控制bit[15:8]
               0：表示对应的bit不做处理；
               1：表示对应的bit位清0。
   UNION结构 ：无 */
#define GBBP_GTC_LINE2_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xEE)

/* 寄存器说明：
   详      述：31bit线控生效脉冲，控制bit[15:8]
               0：表示对应的bit不做任何处理；
               1：表示对应的bit位置1。
   UNION结构 ：无 */
#define GBBP_GTC_LINE2_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xEF)

/* 寄存器说明：
 bit[7:1]    GSM配置MIPI总线写操作时，对应的配置寄存器组起始地址。（注：此信号包含mipi-asm,mipi-pa功能。当G模切天线开关、或GBBP结束W测量回到G切天线开关时需要配置此值）
 bit[0]      GSM配置MIPI总线写操作启动信号，脉冲信号，GTC逻辑自清零
   UNION结构:  GBBP_GTC_MIPI_START_INI_UNION */
#define GBBP_GTC_MIPI_START_INI_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF0)

/* 寄存器说明：
 bit[7]
 bit[6:0]    GSM配置MIPI总线写操作时，本次操作对应的配置个数。
             取值范围：1~63（当使用乒乓配置时，取值范围为：1~31）。
             （注：此信号包含mipi-asm,mipi-pa功能。当G模切天线开关、或GBBP结束W测量回到G切天线开关时需要配置此值）
   UNION结构:  GBBP_GTC_MIPI_NUM_UNION */
#define GBBP_GTC_MIPI_NUM_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF1)

/* 寄存器说明：
   详      述：31bit线控清零脉冲，控制bit[23:16]
               0：表示对应的bit不做处理；
               1：表示对应的bit位清0。
   UNION结构 ：无 */
#define GBBP_GTC_LINE3_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF2)

/* 寄存器说明：
   详      述：31bit线控生效脉冲，控制bit[23:16]
               0：表示对应的bit不做任何处理；
               1：表示对应的bit位置1。
   UNION结构 ：无 */
#define GBBP_GTC_LINE3_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF3)

/* 寄存器说明：
 bit[7]
 bit[6:0]    31bit线控清零脉冲，控制bit[30:24]
             0：表示对应的bit不做处理；
             1：表示对应的bit位清0。
   UNION结构:  GBBP_GTC_LINE4_CTRL_BITWISE_CLR_UNION */
#define GBBP_GTC_LINE4_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF4)

/* 寄存器说明：
 bit[7]
 bit[6:0]    31bit线控生效脉冲，控制bit[30:24]
             0：表示对应的bit不做任何处理；
             1：表示对应的bit位置1。
   UNION结构:  GBBP_GTC_LINE4_CTRL_BITWISE_SET_UNION */
#define GBBP_GTC_LINE4_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF5)

/* 寄存器说明：
 bit[7]
 bit[6]      定向线控gtc_auxdac_en通道设置清零信号
 bit[5]      定向线控gtc_abb_tx_en设置清零信号
 bit[4]      定向线控gtc_abb_rxb_en设置清零信号
 bit[3]      定向线控gtc_abb_rxa_en设置清零信号
 bit[2]      定向线控gtc_flash_ctrl设置清零信号
 bit[1]      定向线控gtc_gps_ctrl设置清零信号
 bit[0]      定向线控gtc_rf_trcv_on设置清零信号
   UNION结构:  GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_UNION */
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_ADDR       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF6)

/* 寄存器说明：
 bit[7]
 bit[6]      定向线控gtc_auxdac_en设置
 bit[5]      定向线控gtc_abb_tx_en设置使能信号
 bit[4]      定向线控gtc_abb_rxb_en设置使能信号
 bit[3]      定向线控gtc_abb_rxa_en设置使能信号
 bit[2]      定向线控gtc_flash_ctrl设置使能信号
 bit[1]      定向线控gtc_gps_ctrl设置使能信号
 bit[0]      定向线控gtc_rf_trcv_on设置使能信号
   UNION结构:  GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_UNION */
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_ADDR       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF7)


/***======================================================================***
                     (2/9) register_define_gtc_dlfe
 ***======================================================================***/
/* 寄存器说明：
 bit[7:2]    
 bit[1]      DAGC处理模式选择，1为搜索模式，0为NB解调模式。该模式信号的切换时间要求在每次搜索启动与解调启动之前配置完毕。
 bit[0]      
   UNION结构:  GBBP_GTC_DAGC_CTRL_UNION */
#define GBBP_GTC_DAGC_CTRL_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA3)

/* 寄存器说明：
 bit[7]      AGC档位配置方式选择。0，由agc_init_gain配置，1，由agc_next_gain配置。
 bit[6]      
 bit[5]      快速AGC测量门限模式选择信号。
             0：快速AGC测量门限采用测量门限A；
             1：快速AGC测量门限采用测量门限B。
             此信号生效与否参见CPU配置信号cpu_fast_threshold_sel，当cpu_fast_threshold_sel=1时，gsp_agc_measure_mode生效。
 bit[4:1]    直流偏置和前向通道增益调整RAM地址区域选择信号。
             由于可能在实际中存在一个TDMA帧切换多个频点的可能，而各个频点的直流偏置值和前向通道增益又有所不同，因此这里通过3bit的选择，选出8组直流偏置粗调值和8组前向通道增益值。
             AGC档位配置方式选择。0，由agc_init_gain配置，1，由agc_next_gain配置。
 bit[0]      AGC模块工作使能信号。
             1：DCR&AGC正常工作；
             0：DCR&AGC停止工作。
             请注意该信号通常情况一直保持为高，除非需要异常终止AGC工作。
             
   UNION结构:  GBBP_GTC_AGC_CTRL1_UNION */
#define GBBP_GTC_AGC_CTRL1_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB4)

/* 寄存器说明：
 bit[7]      时隙前计算直流模式开启。
             1：采用时隙前直流计算模式，该信号必须在正常接收数据时的测量中断之前拉低；
             0：不使用时隙前直流计算模式。
 bit[6]      粗调直流选择。
             1：选择时隙前计算直流，但需要先进行时隙前直流计算，才能使用该功能；
             0：选择NV项配置直流。
 bit[5:4]    AGC三轮能量累加处理长度配置。
             [5:4] 表示能量累加计算时第三轮处理长度，0，16symbol；1，32symbol；2，64symbol；3：128symbol。
 bit[3:2]    AGC三轮能量累加处理长度配置。
             [3:2] 表示能量累加计算时第二轮处理长度，0，16symbol；1，32symbol；2，64symbol；3：128symbol。
 bit[1:0]    AGC三轮能量累加处理长度配置。
             [1:0] 表示能量累加计算时第一轮处理长度，0，16symbol；1，32symbol；2，64symbol；3：128symbol。
   UNION结构:  GBBP_GTC_AGC_CTRL2_UNION */
#define GBBP_GTC_AGC_CTRL2_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB5)

/* 寄存器说明：
 bit[7]      AGC模块快速测量开始指示信号，1个系统周期的脉冲信号。在工作开始指示信号发出之前需要配置好AGC的本时隙的初始档位。快速测量不进行解调与搜索。
 bit[6:5]    AGC模块SSI发送通道指示信号，将此信号拼接到gagc_ssi_data信号的高2bit使用。
 bit[4]      解调与搜索通道直流偏置数字细调环激活，高电平有效。该信号有效时，相当于数字细调环激活，此时无法进行旁路功能。
 bit[3]      时隙前直流计算启动信号。
 bit[2]      时隙前直流累加细调环清零信号
 bit[1]      AGC工作时隙起始档位配置有效指示，1个系统周期的脉冲信号。需提前数据接收时刻100us启动该信号，需与gsp_init_gain和gsp_gain_sel信号配合使用。当该信号有效时，外部agc_init_gain或内部agc_next_gain的档位值才会置入到当前工作档位
 bit[0]      多路数字细调环偏置寄存器清零，1个系统周期的脉冲信号。寄存器内的值需要长期保存，当UE关机时需要放入断电可存储的存储介质当中保存，等到UE再工作时恢复原样。这里提供了一个复位的选择，如果确实需要复位，配置该信号即可，默认情况下无需复位。
   UNION结构:  GBBP_GTC_AGC_START_UNION */
#define GBBP_GTC_AGC_START_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB6)

/* 寄存器说明：
   详      述：当前测量的RSSI对应的频点号低8bit
   UNION结构 ：无 */
#define GBBP_GTC_RSSI_FRQ_LOW_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE3)

/* 寄存器说明：
 bit[7]      
 bit[6:4]    滤波器系数选择信号。
             000：32阶90K无增益固定滤波系数；
             100：32阶可配置滤波系数；
             010：64阶可配置滤波系数；
             011：64阶135K固定滤波器系数；
             101：64阶BPF固定滤波系数，带通范围46.4K~89.7K；
             110：64阶80K固定滤波系数。
 bit[3:0]    当前测量的RSSI对应的频点号高4bit，GSP_RSSI_FRQ_LOW，GSP_RSSI_FRQ_HIGH输出gsp_rssi_frq[11:0]
   UNION结构:  GBBP_GTC_RSSI_FRQ_HIGH_UNION */
#define GBBP_GTC_RSSI_FRQ_HIGH_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE4)

/* 寄存器说明：
 bit[7]      8档射频控制字选择信号，在BBP内部实现两套射频控制字备分，用于实现射频对等功能。
             1:选择寄存器0x5068~5084
             0:选择寄存器0x513c,0x5088~0x50a0
 bit[6]      时隙去直流打开开关，高电平有效,该信号有效时，表示时隙去直流功能可以启动，同时时隙去直流是否启动，还需要参考cpu配置去直流门限cpu_slot_dcr_rssi_threshold
 bit[5:3]    
 bit[2:0]    bit2~0: RF每时隙处理的初始档位。
   UNION结构:  GBBP_GTC_INIT_GAIN_RFIC_UNION */
#define GBBP_GTC_INIT_GAIN_RFIC_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE7)

/* 寄存器说明：
 bit[7:6]    
 bit[5:3]    DAGC测量数字细调环截位位宽，默认值3‘d3。                                        
             3’d0：8；                                  
             3’d1：10；                                  
             3’d2：12；                                  3'd3：14；                                  
             3’d4：4；                                  
             3’d5：6；
             3'd6: 9
bit[2:0]    AGC测量数字细调环截位位宽，默认值3’d3。                                        
             3’d0：8；                                  
             3’d1：10；                                 
             3’d2：12；                                 
             3’d3：14；                                  
             3’d4：4；                                  
             3’d5：6
             3’d6: 9
   UNION结构:  GBBP_GTC_AGC_TRUNC_WIDTH_UNION */
#define GBBP_GTC_AGC_TRUNC_WIDTH_ADDR                 (SOC_BBP_GSM_GTC_BASE_ADDR + 0xED)

/* 寄存器说明：
 bit[7:4]    
 bit[3:1]    IQMismatch模块补偿使能信号，高电平有效。在AGC模块启动前配置。
 bit[0]      RX IQMismatch校准配置参数组号选择信号。用于指示当前时隙使用哪一组相位校准软件配置值（A，P值），参考iq_comp_amp0~ iq_comp_amp4；
   UNION结构:  GBBP_GTC_RX_IQ_COMPL_UNION */
#define GBBP_GTC_RX_IQ_COMPL_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF9)

/* 寄存器说明：
 bit[7:2]    
 bit[1]      当AGC使用3轮快速测量模式时，快速测量的第二轮和第三轮之间不进行档位更新，即第二轮和第三轮的档位保持一致，高电平有效。
 bit[0]      AGC快速测量最后一轮（2轮测量对应第二轮，3轮测量对应第三轮）档位更新模式选择信号，1，表示最后一轮测量采用测量门限采用测量门限A进行档位判决，0表示最后一轮测量采用原快速测量测量门限。
   UNION结构:  GBBP_GTC_FAST_MEAS_SEL_CFG_UNION */
#define GBBP_GTC_FAST_MEAS_SEL_CFG_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xFD)



/***======================================================================***
                     (3/9) register_define_gtc_gsrch
 ***======================================================================***/
/* 寄存器说明：
 bit[7]      软件强制配置DRSSI的使能开关，该使能有效时，软件配置DRSSI值有效。
             CPU接口清零配置参见地址0x01124寄存器配置
             复位默认值为0

 bit[6:4]    CPU对FB搜索的位置的调整，主要为规避设计风险而设计的。
             000:不调整；001：向后调1(symbol)；
             010：向后调2；011：向后调3
             111：向前调1；110：向前调2；
             101：向前调3；100：向前调4
             复位默认值为3’b000
             此数据在搜索模式设置为111和101时有效。即搜索得到的FB位置根据gtc_fb_pos_adj值调整，在下一帧启动sb搜索。

 bit[3:1]    搜索模式配置：
             111(FB+AFC+SB)：则BBP在完成FB搜索后自动启动AFC和SB同步，应用场景为初始小区同步；
			 100（FB搜索）：在FB的搜索窗cpu_fb_peak_window内只进行FB搜索，应用场景为专用态下进行BSIC捕获。
             110(FB+AFC)：进行初始小区同步，完成FB搜索、AFC锁定判决。
			 101(FB+SB)：进行FB搜索和SB搜索，不进行AFC，应用场景为邻小区测量（注：邻区测量也可以用"100+001"模式替代这种模式）；
             001（SB）：则只启动SB同步，不启动FB搜索和AFC，此时gsp_srch_starat的位置需提前按照历史信息（如100模式计算得出的FB位置）推算出来的SB的位置34个符号，以消除FB搜索位置有34个符号的误差带来的影响。应用场景为BSIC认证；
             010：表示只启动AFC，此时gsp_srch_start的位置即为FB的位置，应用场景为IDLE态下的周期性AFC；
             011：则表示只启动AFC和SB，此时gsp_srch_start的位置即为FB的位置，应用场景为NB解调前的AFC和SB同步
             复位默认值为3’b000

 bit[0]      搜索使能信号，在整个搜索期间都保持为高电平。
             CPU接口清零配置寄存器配置
             复位默认值为0
             在搜索过程中，可以将此信号拉低，接收搜索处理。
             亦可由搜索中断拉低该信号
   UNION结构:  GBBP_GTC_SRCH_CFG_UNION */
#define GBBP_GTC_SRCH_CFG_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC3)

/* 寄存器说明：
 bit[7]      1标识当前是邻区搜索，0标识当前是服务区搜索。启动邻区搜索时，必须配置该信号。
 bit[6]      邻区纠偏使能，0表示关闭纠偏，1表示打开。也可以用于对邻区NB纠偏。但是服务区任务时，不能使用纠偏。如果服务区与邻区频点一样，也不能打开纠偏，否则会影响VCTXO。
 bit[5:1]
 bit[0]      cpu对搜索的启动信号，脉冲信号。每次启动搜索时需要置一次，1有效（下同）,GTC模块内部已做处理，使其在需要的qb内的第一个clk_sys处生效,GTC逻辑自清零。当gsp_srch_mod=001时，gsp_srch_start必须提前当前默认的SB位置34个符号产生。
             注：启动搜索时必须配置gsp_nb_afc_en=0。
   UNION结构:  GBBP_GTC_SRCH_START_UNION */
#define GBBP_GTC_SRCH_START_ADDR                      (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC4)

/* 寄存器说明：
 bit[7:3]    
 bit[2]      并行FB和SB模式使能信号，在搜索结束后自动拉低
 bit[1]      脉冲信号，基于RAM中的数据，启动SB搜索，该信号没有空口延时，有效后，立刻启动001搜索的操作
 bit[0]      软件配置启动SB数据存储的时刻，GTC指令配置。因DAGC数据比空口数据延迟1slot，因此模块内部实际开始存储的时间应延迟1slot。
             注：启动搜索时必须配置gsp_nb_afc_en=0。
   UNION结构:  GBBP_GTC_SB_SAVE_START_UNION */
#define GBBP_GTC_SB_SAVE_START_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD0)

/* 寄存器说明：
   详      述：软件配置存储SB数据的符号数，建议值为156~224之间，需要在gsp_start_save_sb之前配置完成
   UNION结构 ：无 */
#define GBBP_GTC_SB_SAVE_LEN_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD1)



/***======================================================================***
                     (4/9) register_define_gtc_dem
 ***======================================================================***/
/* 寄存器说明：
 bit[7]      1表示非服务小区
             0表示服务小区
             用于TOA值随路上报
 bit[6:4]    启动解调时的时隙号，用于TOA值随路上报
 bit[3:1]    训练序列组号
             000：0组；001：1组；
             010：2组；011：3组；
             100：4组；101：5组；
             110：6组；111：7组
             复位默认值为0
 bit[0]      NB解调使能信号，高电平有效，在NB解调过程中一直为高，在启动译码前也需要将该信号置1
             CPU接口清零配置参见地址0x01124寄存器配置
             注意：在需要NB解调的时候，请关闭gsp_srch_en(清零参见0x01124寄存器)，在连接态时对邻区进行FB/SB搜索时，可以维持gsp_nb_demod_en为高，即搜索的优先级高于解调。
             复位默认值为0
   UNION结构:  GBBP_GTC_DEMOD_PARA1_UNION */
#define GBBP_GTC_DEMOD_PARA1_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB0)

/* 寄存器说明：
 bit[7:3]    PS域DATA业务下
             调制盲检测标志存储位置多时隙的第一,第二，第三，
             第四，第五，第六个时隙的六个BURST调制盲检测标志依次
             存储在3～0，7～4，11～8，15～12，23～20，27～24位置，而每个码块的第一个BURST盲检测标志分别存放在0，4，8，12。20，24位置,每个码块的第二个BURST盲检测标志分别存放在1，5，9，13，21，25位置,下面依次类推
             复位默认值为0
             如果是CS域或者PS固定位置的控制信道，请务必配置为16～19
 bit[2]      LS去直流使能信号，0表示关闭，1表示打开。为保证性能，仅在26M倍频点打开，其他频点需关闭。且打开该功能时，需要同时打开AGC模块的时隙平均去直流。仅对8PSK调制方式有效。
 bit[1:0]    下行调制方式指示 00 GMSK调制 01 8PSK调制,10表示下行调制方式未知，11 无意义；
             由于在同一块中连续两个burst同时被判错的概率非常小，因此如果同一码块的前两个时隙被判为同一种调制模式，则在解调第三和第四个burst时直接配置前两个burst判决的调制方式进行解调；如果前两个时隙检测出的调制方式不同，则需要判决第三个burst，但不需要判决第四个burst，前三个burst中肯定有两个burst是同一种调制模式，则在解调第四个burst时直接配置前三个burst判决结果占两个的调制方式进行解调.
             复位默认值为2’b00
   UNION结构:  GBBP_GTC_DEMOD_PARA2_UNION */
#define GBBP_GTC_DEMOD_PARA2_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB1)

/* 寄存器说明：
 bit[7]      
 bit[6:0]    解调BURST数据存储起始位置指示。如果是CS域业务，起始位置对应为26复帧中映射位置，映射到36～36＋gsp_dl_burst_sav_cycle-1内的编号；如果是EGPRS/GPRS业务，不管是单时隙还是多时隙，时隙配置中的第一个时隙码块解调数据固定存放在0，3，6，9；时隙配置中的第二个时隙码块解调数据固定存放在12，15，18，21；时隙配置中的第三个时隙码块解调数据固定存放在24，27，30，33；时隙配置中的第四个时隙码块解调数据固定存放在36，39，42，45的位置；时隙配置中的第五个时隙码块解调数据固定存放在81，84，87，90；时隙配置中的第六个时隙码块解调数据固定存放在93，96，99，102；。如果是PCCCH，PBCCH或者BCCH，CCCH，SDCCH等，可以存放在68～71，SACCH存放在72～75位置，PTCCH存放在76～79位置；其他控制信道则由软件根据数据域业务的BURST存放循环周期（参见译码的GTC配置，gsp_dl_burst_sav_cycle）来灵活控制；如果是SCH则解调数据存放在80位置。复位默认值为80。
   UNION结构:  GBBP_GTC_DEM_PARA3_UNION */
#define GBBP_GTC_DEM_PARA3_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB2)

/* 寄存器说明：
 bit[7:4]    
 bit[3:2]    滤波器系数选择位
             2’b00：滤波器0，无干扰
             2’b01：滤波器1，+200Khz干扰
             2’b10：滤波器2，-200Khz干扰
             2’b11：滤波器3，
             200Khz干扰
 bit[1]      邻频检测模块使能信号。邻频抑制功能仅针对于NB情况下使用，搜索模式下（FB、SB）不进行邻频检测。
 bit[0]      下行NB解调启动信号，脉冲信号，
             GTC模块内部已做处理，使其在需要的qb内的第一个clk_sys处生效,GTC逻辑自清零
   UNION结构:  GBBP_GTC_DEMOD_START_UNION */
#define GBBP_GTC_DEMOD_START_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB3)

/* 寄存器说明：
 bit[7]      NB-AFC使能信号，1有效。
             默认值为0。
             注：当启动搜索时，此信号必须配置为零，CPU接口清零配置参见地址0x01124寄存器配置。
 bit[6]      解邻区NB时，纠偏使能信号。
             1表示进行纠偏；
             0表示不纠偏
             配置该信号使能时，需同时配置gsp_nco_ini_value
 bit[5]      软件计算当前NB位置的选择信号。
             1’d1：表示选择软件计算的当前NB位置调整值；
             1’d0：表示选择GBBP计算的当前NB位置调整值。正常模式下请务必将该信号配置为0,软件规避模式下需要同时配置gsp_nb_pos参数
             默认值为0
 bit[4]      选择是否在本时隙进行能量Alpha滤波，电平信号。
             1：进行能量Alpha滤波，系数为cpu_alpha_parameter;
             0：不进行能量Alpha滤波。
             默认值为1
 bit[3:0]    软件规避模式下由软件计算的当前NB位置的调整值。正常模式下该信号可以配置为0
             允许的取值范围：-1~7，单位为符号。补码表示。如：
             4’b1111：表示当前的NB位置较当前的时隙头要提前1个符号；
             4’b0000：表示当前的NB位置正好等于当前的时隙头；
             4’b0001：表示当前的NB位置较当前的时隙头要延迟1个符号；
             4’b0010：表示当前的NB位置较当前的时隙头要延迟2个符号；
             。。。。。。
             4’b0111：表示当前的NB位置较当前的时隙头要延迟7个符号。
             
   UNION结构:  GBBP_GTC_TOA_PARA_UNION */
#define GBBP_GTC_TOA_PARA_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBD)

/* 寄存器说明：
   详      述：邻区频偏初值的低8bit。配置方法同GSP_NCO_INI_VALUE_HI。
   UNION结构 ：无 */
#define GBBP_GTC_NCO_INI_VALUE_LOW_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCD)

/* 寄存器说明：
   详      述：邻区频偏初值的高8bit。每次邻区搜索前，PHY需配置该初值。第一次搜索某邻区，则配置为0。
               每次邻区同步完成后，PHY响应搜索中断，读取ncell_nco_cpu，获取最新的频偏，并保存，在下一次搜索同一邻区时，配置给gtc_nco_ini_value_hi。（详见下文参考配置图）
   UNION结构 ：无 */
#define GBBP_GTC_NCO_INI_VALUE_HI_ADDR                (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCE)



/***======================================================================***
                     (5/9) register_define_gtc_gcipher
 ***======================================================================***/
/* 寄存器说明：
 bit[7]      1表示启动上行A5加密。每次有加密操作该信号必须配置。
 bit[6]      
 bit[5:4]    上行帧号调整标志
             11表示输入到加密模块的FN需要做减1操作，01表示输入到加密模块的FN需要做加1操作;
             10，00表示无加，减1操作;
             复位默认值为00，正常使用下应该配置为00；01、11是出错时的规避模式.
 bit[3:1]    上行行A51或者A52,A53算法选择
             gtc_ul_gsm_alg_sel[2:0] =1表示选择A51算法 
             gtc_ul_gsm_alg_sel[2:0] =7表示选择A53算法
 bit[0]      上行解密模块工作模式选择,
             1表示上行发射需要加密
             0表示上行发射不需要
             默认值为0
   UNION结构:  GBBP_GTC_A5_CIPH_CFG_UNION */
#define GBBP_GTC_A5_CIPH_CFG_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC6)

/* 寄存器说明：
 bit[7:6]    
 bit[5:4]    下行帧号调整标志：
             11表示输入到解密模块的FN需要做减1操作，01表示输入到解密模块的FN需要做加1操作；
             10，00表示无加，减1操作；
             复位默认值为00，正常使用下应该配置为00；01、11是出错时的规避模式
 bit[3:1]    下行A51或者A52,A53算法选择：
             gtc_dl_gsm_alg_sel[2:0] =1表示选择A51算法；
             gtc_dl_gsm_alg_sel[2:0] =7表示选择A53算法
 bit[0]      下行解密模块工作模式选择：
             1表示下行需要解密，
             0表示下行不解密，
             默认值为0
             解调PS域业务和SCH的BURST时请配置为0 
   UNION结构:  GBBP_GTC_A5_DECIPH_CFG_UNION */
#define GBBP_GTC_A5_DECIPH_CFG_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC5)



/***======================================================================***
                     (6/9) register_define_gtc_gdec
 ***======================================================================***/
/* 寄存器说明：
 bit[7]      1表示循环上报模式使能，此时单码块完成译码就上报中断；
             0表示缓存上报模式使能，多个码块译码后缓存上报中断。
 bit[6:0]    一般情况下表示下行业务序号.当配置为120～123表示下行业务分类 
             120 表示CS域的AFS业务
             121 表示CS域的AHS业务
             122 表示PS域业务（HARQ初传或者重传）
             123 表示HARQ合并译码
             复位默认值为7’d0
             
   UNION结构:  GBBP_GTC_DL_CB_INDEX_UNION */
#define GBBP_GTC_DL_CB_INDEX_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC7)

/* 寄存器说明：
 bit[7]      1表示处于AMR 的SPEECH态
             0表示处于AMR 的DTX态
             默认值为1
 bit[6:0]    表示待译码码块的第一个BURST在VALPP软值存储RAM中的位置编号。如果是CS域业务，起始位置在36～36＋gsp_dl_burst_sav_cycle-1，由软件根据码块在复帧中映射起始位置配置；如果是在EGPRS/GPRS业务，不管是单时隙还是多时隙，如果对第一个时隙配置的码块译码，则配置为0；如果对第二个时隙配置的码块译码，则配置为12；如果对第三个时隙配置的码块译码，则配置为24；如果对第四个时隙配置的码块译码，则配置为36；如果对第五时隙配置的码块译码，则配置为81；如果对第六个时隙配置的码块译码，则配置为93；对SDCCH，PBCCH，BCCH，CCCH配置为68，对于SACCH配置为72，PTCCH则配置为76。特别注意：如果是半速率业务，假设当前译码启动时配置位置为a，且当当前译码上报译码失败原因为FACCH_H前四个BURST时，在下次启动译码应该将本参数仍然配置为a，在下次译码完成后，启动下下次译码时应该配置为a＋4（gsp_dl_burst_sav_cycle内取模，然后加上36）值。其他未分配位置，由软件根据业务需要灵活配置。复位默认值未80
   UNION结构:  GBBP_GTC_DEC_BURST_POS_UNION */
#define GBBP_GTC_DEC_BURST_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC8)

/* 寄存器说明：
 bit[7]      FACCH译码模式选择，AFS，FS，EFS下1 表示相关译码结果判断是否为FACCH偷帧，如果是,则逻辑启动FACCH译码,如果不是,则逻辑启动其他码块译码；0 表示直接启动FACCH译码根据译码的CRC校验结果判断是否为FACCH偷帧。
             AHS，HS下1 表示相关译码结果判断是否为FACCH偷帧，如果是,则逻辑启动FACCH译码,如果不是,则逻辑启动其他码块译码；0标识直接作为FACCH译码。
             默认值为1
 bit[6:5]    软件配置的历史CMI值
             默认值为0x0
 bit[4]      表示当前帧号的CMI和CMC指示，0表示是CMI帧，1表示是CMC帧。复位默认值为0
 bit[3:2]    
 bit[1:0]    gtc_enhanced_dec_mode[1]＝1表示增强型译码模式使能；0表示采用传统VTB译码模式
             gtc_enhanced_dec_mode[0]＝1表示在增强型译码模式下MCS5-69业务采用传统VTB译码模式；0表示MCS5-69业务采用增强型译码模式。
             MCS7~9初传不支持增强型译码。
             实际使用中：
             1、初传MCS5~9均配置为增强型译码，当判决出业务为MCS7~9时，此时BBP采用传统VTB译码模式，同时cb1_crc_result[7:0]、cb2_crc_result[7:0]、cb3_crc_result[7:0]上报结果均无效。
             
             2、重传MCS7~9配置为增强型译码，此时MCS7~9采用增强型译码，同时cb1_crc_result[7:0]、cb2_crc_result[7:0]、cb3_crc_result[7:0]上报结果均有效。
             默认为2’b10
             
   UNION结构:  GBBP_GTC_DEC_TYPE1_UNION */
#define GBBP_GTC_DEC_TYPE1_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC9)

/* 寄存器说明：
 bit[7]      1表示软件配置HARQ功能使能，0表示该功能屏蔽
             默认值为0
 bit[6]      1表示带内bit ib和ID_MARKER bit参与质量测量统计
             0表示带内bit ib和ID_MARKER bit不参与质量测量统计
             默认值为0
 bit[5]      1表示打开bep统计功能，0表示关闭bep统计功能，默认值为0
 bit[4]      1表示 EDGE业务下USF参与BER和BEP统计，默认值为0
 bit[3:2]    
 bit[1:0]    00 表示在GPRS网络，根据网络分配信息，将CS4和MCS1234区分为CS4
             01 表示在EGPRS网络，据网络分配信息，将CS4和MCS1234区分为MCS1234（该功能请慎用）
             10 表示先做MCS1234的HEADER的译码，如果译码结果的CRC校验正确则判为MCS1234，否则判为CS4
             默认值为0x2
             
   UNION结构:  GBBP_GTC_DEC_TYPE2_UNION */
#define GBBP_GTC_DEC_TYPE2_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCA)

/* 寄存器说明：
 bit[7]      
 bit[6:0]    在HARQ译码过程中表示需要做harq合并的第一个码块的读起始位置；在HARQ软值保存过程中为第一个码块的写起始位置。在Repeat FACCH/SACCH业务，取值只能为0~7。其它业务，取值范围是0~127。（V3R3、V8R1等HARQ外移版本，此配置范围统一改为0~127。）
             默认值为0
   UNION结构:  GBBP_GTC_HARQ_POS1_UNION */
#define GBBP_GTC_HARQ_POS1_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCB)

/* 寄存器说明：
 bit[7]      
 bit[6:0]    在HARQ译码过程中表示需要做harq合并的第二个码块的读起始位置；在HARQ软值保存过程中为第二个码块的写起始位置。
             默认值为1
   UNION结构:  GBBP_GTC_HARQ_POS2_UNION */
#define GBBP_GTC_HARQ_POS2_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCC)

/* 寄存器说明：
 bit[7]      
 bit[6:0]    bit6～bit0：参与HARQ合并译码的任意一个码块（应该为DATA块）的CB_INDEX，复位默认值为7’d52，如果是MCS6，9、MCS5，7合并，那么可以选择任意一个码块（应该为DATA块）的cb_index进行配置
   UNION结构:  GBBP_GTC_HARQ1_CB_INDEX_UNION */
#define GBBP_GTC_HARQ1_CB_INDEX_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCF)

/* 寄存器说明：
 bit[7]      质量测量BER模块使能信号，高电平有效。（必要时关断，以节省功耗）
             默认值为1
 bit[6]      质量测量BLER模块使能信号，高电平有效。（必要时关断，以节省功耗）
             复位默认值为1
             
 bit[5:0]    下行译码存放BURST循环周期（该参数只对CS域业务有效），复位默认值为24，表示周期为24；在22BURST交织的业务下需要根据软件需求配置。
             000000表示周期为0,
             ……
             100000表示周期为32
             最大可配置为44
             复位默认值为6’d24
   UNION结构:  GBBP_GTC_DL_BURST_CYCLE_UNION */
#define GBBP_GTC_DL_BURST_CYCLE_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD2)

/* 寄存器说明：
 bit[7]      接收质量上报BER清零信号，脉冲信号,GTC逻辑自清零
 bit[6]      接收质量上报BLER清零信号，脉冲信号,GTC逻辑自清零
 bit[5]      
 bit[4:2]    本次启动译码时对应的时隙号
 bit[1]      1表示本次译码需要上报中断，该译码中断模式只在gtc_cycle_rpt_en为0才生效
 bit[0]      NB承载业务的译码启动信号,GTC逻辑自清零
   UNION结构:  GBBP_GTC_DEC_START_UNION */
#define GBBP_GTC_DEC_START_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD3)

/* 寄存器说明：
 bit[7:4]    bit3~bit0，分别表示当前精简寻呼译码时有效的BURST是否存在，如0011标识第一个，第二个BURST存在，第三个第四个BURST译码数据补零。
             1100标识第三个，第四个BURST存在，第一个第二个BURST译码数据补零。
             默认值为0xF
 bit[3:2]    
 bit[1]      1表示是增强型译码的UT验证模式，测试用，默认值为0
 bit[0]      1表示译码模式是测试模式，此时译码模块不做帧类型判决
   UNION结构:  GBBP_GTC_DEC_TEST_MODE_EN_UNION */
#define GBBP_GTC_DEC_TEST_MODE_EN_ADDR                (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE0)

/* 寄存器说明：
   详      述：下行译码8个BURST是否需要解调软值在译码过程清零使用配置，bit0～7分别表示BURST0～7的使用配置，0表示解调软值清零使用，1表示使用VALPP RAM中读出的数据（如果有精简寻呼或者盲检测差异导致的软值清零仍然会生效）
               如果不需要启用译码前解调软值清零功能，该参数一定要配置为8’hff，xx1模式搜索启动前该参数也一定要配置为8’hff
   UNION结构 ：无 */
#define GBBP_GTC_DEC_BURST_MAP_INFO_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE8)



/***======================================================================***
                     (7/9) register_define_gtc_gglb
 ***======================================================================***/
/* 寄存器说明：
   详      述：bit7~bit0：表示8个CPU可编程中断,bit位置1的话，表示在当前时刻产生一个可编程中断，最多可以同时有8个可编程中断产生。
   UNION结构 ：无 */
#define GBBP_GTC_CPU_GRM_INT_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBC)

/* 寄存器说明：
   详      述：GRIF模块当前burst长度值低8bit，具体见GTC_RX_LEN_HIGH,复位默认值为8'd0
   UNION结构 ：无 */
#define GBBP_GTC_RX_LEN_LOW_ADDR                      (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC0)

/* 寄存器说明：
   详      述：GRIF模块当前burst长度值高8bit，与低8bit共同表示接收长度，其配置单位为样点，复位默认值为8'd0.
   UNION结构 ：无 */
#define GBBP_GTC_RX_LEN_HIGH_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC1)

/* 寄存器说明：
 bit[7:3]    
 bit[2]      GRIF模块接收停止信号，一个系统时钟周期宽度.当gsp_rx_low_len和gsp_rx_high_len都配置为0时,表示连续接收,此时可以用gsp_rx_stop来停止接收.但是gsp_rx_stop在连续或按长度接收的模式下置1都会导致接收中止
 bit[1]      GRIF模块接收启动信号，一个系统时钟周期宽度
 bit[0]      
   UNION结构:  GBBP_GTC_GRIF_CTRL_UNION */
#define GBBP_GTC_GRIF_CTRL_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC2)



/***======================================================================***
                     (8/9) register_define_gtc_gul
 ***======================================================================***/
/* 寄存器说明：
 bit[7:5]    
 bit[4]      上行ABB内部GAPC DAC控制选择信号。                1：TXAGC DAC；          0：RAMP DAC。             注：当前RF C02版本中，GMSK时配置为0表示爬坡；8psk时配置为1表示爬坡，0表示VBIAS。
 bit[3]      target重配置APC爬坡驱动启动信号。写1启动一次target重配置的APC爬坡驱动（应用于多时隙功率变化），内部产生一个104M脉冲（必需在frac_cnt=46处发出（GTC内部处理））。note：必须在爬坡16点结束后再启动此信号，具体参见下面描述的时序图。
 bit[2]      单次APC驱动启动信号。写1启动目标功率电压值为gsp_pa_init的单次APC驱动，内部产生一个104M脉冲。（逻辑内部一次达到该目标功率电压值），可用该启动信号来配置APC输出TXAGC DAC所需的控制字
 bit[1]      GSP停止APC爬坡驱动的信号。写1停止APC爬坡驱动，内部产生一个104M脉冲。可用该启动信号来配置APC输出RAMP DAC所需的控制字
 bit[0]      GSP启动APC驱动，1个104M高脉冲（必需在frac_cnt=94处发出（GTC内部处理））可用该启动信号来配置APC输出RAMP DAC所需的控制字
   UNION结构:  GBBP_GTC_PA_CTRL_CFG_UNION */
#define GBBP_GTC_PA_CTRL_CFG_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA4)

/* 寄存器说明：
   详      述：APC爬坡驱动持续时间长度，具体指首次上爬坡到目标值gsp_pa_target时开始，到开始下爬坡到初始值的时刻这段时间（具体参见下面时序图该信号的含义）。单位Qb，默认值为4个burst长度。该信号配置的是低8bit
   UNION结构 ：无 */
#define GBBP_GTC_PA_LEN_LOW_CFG_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA5)

/* 寄存器说明：
 bit[7:5]    
 bit[4:0]    APC爬坡驱动持续时间长度，具体指首次上爬坡到目标值gsp_pa_target时开始，到开始下爬坡到初始值的时刻这段时间（具体参见下面时序图该信号的含义）。单位Qb，默认值为4个burst长度。该信号配置的是高5bit
   UNION结构:  GBBP_GTC_PA_LEN_HIGH_CFG_UNION */
#define GBBP_GTC_PA_LEN_HIGH_CFG_ADDR                 (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA6)

/* 寄存器说明：
   详      述：GSP配置APC目标电压值，该信号配置的是低8bit
   UNION结构 ：无 */
#define GBBP_GTC_PA_TARGET_LOW_CFG_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA7)

/* 寄存器说明：
 bit[7:5]    指示本次爬坡的爬坡系数索引号，确保在gsp_pa_start或者gsp_pa_change有效时,此值已经配置。本索引号取值范围是0～3。note：当有gsp_pa_change时，ramp-down的系数gsp_pa_coeff_index[1:0]由gsp_pa_change对应的系数索引号决定，而不是由gsp_pa_start对应的系数gsp_pa_coeff_index[1:0]决定。
 bit[4:2]    
 bit[1:0]    GSP配置APC目标电压值。该信号配置的是高2bit
   UNION结构:  GBBP_GTC_PA_TARGET_HIGH_CFG_UNION */
#define GBBP_GTC_PA_TARGET_HIGH_CFG_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA8)

/* 寄存器说明：
   详      述：APC爬坡初始功率电压值。也可作为单次APC驱动的目标功率电压值。该信号配置的是低8bit,此信号也用于配置Vbias功能的控制电压值。为该信号的低8bit。
   UNION结构 ：无 */
#define GBBP_GTC_PA_INIT_LOW_CFG_ADDR                 (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA9)

/* 寄存器说明：
 bit[7]      
 bit[6:2]    指示当前爬坡的点数，上坡和下坡点数相同。可配范围值：8～16。默认值为16。
 bit[1:0]    APC爬坡初始功率电压值。也可作为单次APC驱动的目标功率电压值。该信号配置的是高2bit
   UNION结构:  GBBP_GTC_PA_INIT_HIGH_CFG_UNION */
#define GBBP_GTC_PA_INIT_HIGH_CFG_ADDR                (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAA)

/* 寄存器说明：
 bit[7]      与gsp_mod_symbol_l_length[7:0]组成9bit的调制长度，该比特为最高位，gsp_mod_symbol_l_length[7:0]为低8bit。循环调制0，输出正弦波信号。只能使用gsp_mod_stop停止。
 bit[6:0]    bit6~0: 该信号表示gsp_mod_start需要在QB内产生位置信息(即是在QB内96拍哪一拍的位置产生)，位置信息配置为0~95(注意该值应该配置为位置减1的值,即是47~0~46),配置gsp_mod_start请先配置该信号(如果位置不变,可以不用配置).复位默认值为77;
   UNION结构:  GBBP_GTC_MOD_START_POS_UNION */
#define GBBP_GTC_MOD_START_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAC)

/* 寄存器说明：
   详      述：调制符号个数(在1个burst调制期间是常数，范围是0～148*2)，当调制时，符号计数大于gtc_mod_symbol_length时，调制模块停止输出。
               当gtc_mod_symbol_length =0时，循环调制0，输出正弦波信号。只能使用gtc_mod_stop停止。
               复位默认值为0，调制过程中，该参数应保持
   UNION结构 ：无 */
#define GBBP_GTC_MOD_SYMBOL_LENGTH_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAD)

/* 寄存器说明：
 bit[7:1]    
 bit[0]      调制类型：1表示8PSK，0表示GMSK。复位默认值为0，调制过程中，该参数应保持。HUASHAN版本请务必配置0
   UNION结构:  GBBP_GTC_MOD_TYPE_UNION */
#define GBBP_GTC_MOD_TYPE_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAE)

/* 寄存器说明：
 bit[7:2]    
 bit[1]      bit1: CPU 配置GTC停止调制，一个脉冲。当gsp_mod_symbol_length=0时，循环调制指定位置，此时只能用gsp_mod_stop停止调制。,GTC逻辑自清零
 bit[0]      bit0: CPU配置GTC启动调制，一个脉冲，连续多时隙时，CPU仍需要每个时隙都启动一次，调制时，逻辑不关心是否是多时隙.建议在配置该指令之前，配置一条延时指令，保证在最后一个QB的前半段时间就开始解析gsp_mod_start指令，从而保证调制数据与下一个BURST的头位置对齐，GTC逻辑自清零。需要考虑预调制长度以及上行通道的延时
   UNION结构:  GBBP_GTC_MOD_CTRL_UNION */
#define GBBP_GTC_MOD_CTRL_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAF)

/* 寄存器说明：
 bit[7]      
 bit[6:0]    上行业务索引号
   UNION结构:  GBBP_UL_CB1_INDEX_UNION */
#define GBBP_UL_CB1_INDEX_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD4)

/* 寄存器说明：
 bit[7:6]    FACCH偷帧标志，           01: 表示当前编码之前启动了一次FACCH/H编码，交织时不能覆盖偷帧位置。         10: 表示当前编码之前启动了一次FACCH/F编码，交织时不能覆盖偷帧位置。      00/11：表示当前编码之前没有启动FACCH编码或者FACCH偷帧对当前编码没有影响，可以正常交织。              注：该标志仅仅针对22个BURST交织深度的数据业务（包括F9.6/F4.8/H4.8/H2.4/F14.4）下，需要配置，其它业务下无需配置；若FACCH与数据业务之间存在SACCH业务（单独存储）时，该偷帧标志在启动数据业务之前必须加以保持
 bit[5:4]    上行待编码码块起始位置指示标志。                   00: 表示码块0的起始位置标志，                     01:表示码块1的起始位置标志，                    10: 表示码块2的起始位置标志。                    11: 表示码块3的起始位置标志。                     复位默认值为2’b00
 bit[3:0]    
   UNION结构:  GBBP_GTC_UL_CB_NUM_UNION */
#define GBBP_GTC_UL_CB_NUM_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD7)

/* 寄存器说明：
 bit[7:6]    [7:6]表示DATA2的打孔方
             00：无
             01：P1
             10：P2
             11：P3
             复位默认值为4’b0000
 bit[5:4]    [5:4]表示DATA1（DATA）的打孔方式；                00：无，                   01：P1，                 10：P2，                11：P3，                 复位默认值为4’b0000。
 bit[3:2]    [3:2]：表示带内比特id1信息，       00:CODEC_MODE_1，01:CODEC_MODE_2，10:CODEC_MODE_3，11:CODEC_MODE_4，        复位默认值为4'b0000，如果协议中没有标明id0,id1,采用的是id标注，那么该id值配置在id0上，即此时是低2bit有效，如果是以标明是id1,那么就配置在id1，此时高2bit有效。
 bit[1:0]    [1:0]：表示带内比特id0信息00:CODEC_MODE_1，01:CODEC_MODE_2，10:CODEC_MODE_3，11:CODEC_MODE_4，    
   UNION结构:  GBBP_GTC_UL_PARA21_UNION */
#define GBBP_GTC_UL_PARA21_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD8)

/* 寄存器说明：
 bit[7:6]    
 bit[5:0]    RACH业务中BS（基站）的BSIC比特，复位默认值为6’b000000，注：BSIC的MSB在bit0,LSB在bit5。
   UNION结构:  GBBP_GTC_RACH_BSIC_UNION */
#define GBBP_GTC_RACH_BSIC_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD9)

/* 寄存器说明：
 bit[7]      
 bit[6:0]    表示当前编码数据第一个BURST在编码存储RAM（ram611x16s）中的位置编号:复位默认值为7’d0。   参考配置如下：0，12，24，36：                      PS域业务：对应于第一个码块，配置为0，此时map后的4个burst依次存放在首地址为0，3，6，9的ram中（为后续的gsp_ map_burst_pos所用）；                   第二个码块配置为12，map后的4个burst依次存放于12，15，18，21；             第三个码块配置为24，map后的4个burst依次存放于24，27，30，33；             第四个码块配置为36，map后的4个burst依次存放于36，39，42，45；36 ～ 59： CS域业务，64 ～ 67： SACCH，68 ～ 71： PTCCH，72 ～ 75：其他控制信道，76      ： RACH，                特别注意：如果是半速率业务，假设当前编码启动时配置位置为a，启动一次FACCH/H编码，需要放弃2个SPEECH的编码，所以下次直接是a+4位置。
   UNION结构:  GBBP_GTC_COD_BURST_POS_UNION */
#define GBBP_GTC_COD_BURST_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDA)

/* 寄存器说明：
 bit[7]      上行编码过程的使能信号。 复位默认值为0
 bit[6]      
 bit[5:0]    上行编码存放BURST循环周期（该参数只对CS域业务有效，即是CS域业务映射的复帧周期）.复位默认值为24。
   UNION结构:  GBBP_GTC_UL_BURST_CYCLE_UNION */
#define GBBP_GTC_UL_BURST_CYCLE_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDB)

/* 寄存器说明：
 bit[7:1]    
 bit[0]      上行编码启动信号，脉冲信号,GTC逻辑自清零
   UNION结构:  GBBP_GTC_UL_COD_START_UNION */
#define GBBP_GTC_UL_COD_START_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDC)

/* 寄存器说明：
 bit[7]      1 表示由CPU来控制调制前RAM数据的写入。0 表示有上行编码来控制调制前RAM数据的写入。复位默认值为0
 bit[6]      
 bit[5:2]    上行NB子集1训练序列组号0000：子集1第0组训练序列0001：子集1第1组训练序列0010：子集1第2组训练序列0011：子集1第3组训练序列0100：子集1第4组训练序列0101：子集1第5组训练序列0110：子集1第6组训练序列0111：子集1第7组训练序列上行NB子集2训练序列组号1000：子集2第0组训练序列1001：子集2第1组训练序列1010：子集2第2组训练序列1011：子集2第3组训练序列1100：子集2第4组训练序列1101：子集2第5组训练序列1110：子集2第6组训练序列1111：子集2第7组训练序列AB复用上面的配置，但是只有0000，0001，0010配置有效复位默认值为4’b0000
 bit[1]      BURST类型标志：1表示NB，0表示AB，复位默认值为0。
 bit[0]      调制类型标志：0表示GMSK调制，1表示8PSK调制。复位默认值为0，HUASHAN版本请务必配置为0。
   UNION结构:  GBBP_GTC_UL_MAP_PARA_UNION */
#define GBBP_GTC_UL_MAP_PARA_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDD)

/* 寄存器说明：
 bit[7]      1表示使能MAP后RAM(调制模块数据输入RAM)乒乓切换使能，0表示调制模块固定读乒RAM(此时CPU写待调制数据RAM也只能写入乒RAM)。复位默认值为1
 bit[6:0]    需要送去成BURST的数据存储位置指示（可选集为编码RAM中每个BURST存储的起始地址，参考gsp_ul_cod_burst_pos[6:0]的位置编号方式，所不同的是：该信号下发的是当前准备调制的BURST位置编号，而不是整个编码码块起始BURST的位置编号。）
             默认值为0
   UNION结构:  GBBP_GTC_MAP_BURST_POS_UNION */
#define GBBP_GTC_MAP_BURST_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDE)

/* 寄存器说明：
 bit[7:1]    
 bit[0]      成BURST映射启动信号，高电平脉冲信号（提前调制启动信号6.25个Symble）,GTC逻辑自清零
   UNION结构:  GBBP_GTC_MAP_START_UNION */
#define GBBP_GTC_MAP_START_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDF)

/* 寄存器说明：
   详      述：bit[0]:测试使能。0为原始设计模式，1为测试模式，bit[2:1]:残留相位控制。0为停止调制（输出0），1为残留最后一个值的状态，2为继续调制全0，3为继续调制全1。 bit[3]:初始相位控制。0为重新从零开始，1为从当前相位开始。                bit[4]:1为校准模式，调制模      块输出受cpu_i_mod_data，cpu_q_mod_data控制。bit[5]:保留字段,其他控制模式。                  bit[6]:长burst模式，1表示支持大于148的burst，0表示burst长度最大为148（不含预调制长度）。 对于短时隙模式，调制长度超过148时，继续调制全0或者全1（由bit[2:1]的控制0或1）bit[7]: 预调制数据选择，1表示GMSK调制全1（8PSK对应001），0表示GMSK调制全0（8PSK对应111）
   UNION结构 ：无 */
#define GBBP_GTC_ULMOD_TEST_MOD_LOW_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE5)

/* 寄存器说明：
 bit[7:4]    
 bit[3:0]    bit[3:0]:预调制长度，0表示不进行预调制，默认值为4，调制过程中，该参数应保持
   UNION结构:  GBBP_GTC_ULMOD_TEST_MOD_HIGH_UNION */
#define GBBP_GTC_ULMOD_TEST_MOD_HIGH_ADDR             (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE6)

/* 寄存器说明：
 bit[7:5]    
 bit[4]      IQ数据旁路指示；1表示IQ数据旁路，只输出HD3/HD5计算结果。GTC配置。如果需要旁路HD35功能，则需要配置cpu_hd35_cal_bypass。
 bit[3:1]    去3、5次谐波模块运算使用参数选择信号，GTC配置。为了确保校准参数及时生效，在gsp_mod_start之前配置此选择信号生效。
 bit[0]      去3、5次谐波模块运算使能，GTC配置。在调制启动前配置。
   UNION结构:  GBBP_GTC_HD35_CAL_UNION */
#define GBBP_GTC_HD35_CAL_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xFA)



/***======================================================================***
                     (9/9) register_define_gtc_timing
 ***======================================================================***/
/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define GBBP_TIMING_SLOT_LOW_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBE)

/* 寄存器说明：
 bit[7:2]    
 bit[1:0]    
   UNION结构:  GBBP_TIMING_SLOT_HIGH_UNION */
#define GBBP_TIMING_SLOT_HIGH_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBF)



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
                     (1/9) register_define_fe_ctrl_auto
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_SPI_TRANS_DATA_NUM_UNION
 结构说明  : GTC_SPI_TRANS_DATA_NUM 寄存器结构定义。地址偏移量:0xA1，初值:0x04，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_spi_trans_data_num_reg;
    struct
    {
        unsigned char  gtc_spi_trans_data_num : 5;  /* bit[0-4]: bit4~bit0：本次需要发送的SPI串口数据数
                                                                 00001 表示1个数据
                                                                 10000 表示16个数据 */
        unsigned char  reserved               : 3;  /* bit[5-7]:  */
    } reg;
} GBBP_GTC_SPI_TRANS_DATA_NUM_UNION;
#define GBBP_GTC_SPI_TRANS_DATA_NUM_gtc_spi_trans_data_num_START  (0)
#define GBBP_GTC_SPI_TRANS_DATA_NUM_gtc_spi_trans_data_num_END    (4)


/*****************************************************************************
 结构名    : GBBP_GTC_SPI_RD_EN_UNION
 结构说明  : GTC_SPI_RD_EN 寄存器结构定义。地址偏移量:0xA2，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_spi_rd_en_reg;
    struct
    {
        unsigned char  gtc_spi_rd_en : 1;  /* bit[0]  : GTC启动发送SPI数据脉冲 */
        unsigned char  reserved      : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_SPI_RD_EN_UNION;
#define GBBP_GTC_SPI_RD_EN_gtc_spi_rd_en_START  (0)
#define GBBP_GTC_SPI_RD_EN_gtc_spi_rd_en_END    (0)


/*****************************************************************************
 结构名    : GBBP_GTC_W2G_CTRL_UNION
 结构说明  : GTC_W2G_CTRL 寄存器结构定义。地址偏移量:0xB8，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_w2g_ctrl_reg;
    struct
    {
        unsigned char  gtc_w2g_ctrl : 1;  /* bit[0]  : 切换到G天线，切换到GTC内部寄存器27下的选择5，2M脉冲信号 */
        unsigned char  reserved     : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_W2G_CTRL_UNION;
#define GBBP_GTC_W2G_CTRL_gtc_w2g_ctrl_START  (0)
#define GBBP_GTC_W2G_CTRL_gtc_w2g_ctrl_END    (0)


/*****************************************************************************
 结构名    : GBBP_GTC_MIPI_START_INI_UNION
 结构说明  : GTC_MIPI_START_INI 寄存器结构定义。地址偏移量:0xF0，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mipi_start_ini_reg;
    struct
    {
        unsigned char  gtc_mipi_start_ind : 1;  /* bit[0]  : GSM配置MIPI总线写操作启动信号，脉冲信号，GTC逻辑自清零 */
        unsigned char  gtc_mipi_ini_addr  : 7;  /* bit[1-7]: GSM配置MIPI总线写操作时，对应的配置寄存器组起始地址。（注：此信号包含mipi-asm,mipi-pa功能。当G模切天线开关、或GBBP结束W测量回到G切天线开关时需要配置此值） */
    } reg;
} GBBP_GTC_MIPI_START_INI_UNION;
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_start_ind_START  (0)
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_start_ind_END    (0)
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_ini_addr_START   (1)
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_ini_addr_END     (7)


/*****************************************************************************
 结构名    : GBBP_GTC_MIPI_NUM_UNION
 结构说明  : GTC_MIPI_NUM 寄存器结构定义。地址偏移量:0xF1，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mipi_num_reg;
    struct
    {
        unsigned char  gtc_mipi_ini_num : 6;  /* bit[0-5]: GSM配置MIPI总线写操作时，本次操作对应的配置个数 */
        unsigned char  reserved         : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_MIPI_NUM_UNION;
#define GBBP_GTC_MIPI_NUM_gtc_mipi_ini_num_START  (0)
#define GBBP_GTC_MIPI_NUM_gtc_mipi_ini_num_END    (5)


/*****************************************************************************
 结构名    : GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_UNION
 结构说明  : GTC_EXT_LINE_CTRL_BITWISE_CLR 寄存器结构定义。地址偏移量:0xF6，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ext_line_ctrl_bitwise_clr_reg;
    struct
    {
        unsigned char  gtc_rf_trcv_on_clr : 1;  /* bit[0]: 定向线控gtc_rf_trcv_on设置清零信号 */
        unsigned char  gtc_gps_ctrl_clr   : 1;  /* bit[1]: 定向线控gtc_gps_ctrl设置清零信号 */
        unsigned char  gtc_flash_ctrl_clr : 1;  /* bit[2]: 定向线控gtc_flash_ctrl设置清零信号 */
        unsigned char  gtc_abb_rxa_en_clr : 1;  /* bit[3]: 定向线控gtc_abb_rxa_en设置清零信号 */
        unsigned char  gtc_abb_rxb_en_clr : 1;  /* bit[4]: 定向线控gtc_abb_rxb_en设置清零信号 */
        unsigned char  gtc_abb_tx_en_clr  : 1;  /* bit[5]: 定向线控gtc_abb_tx_en设置清零信号 */
        unsigned char  gtc_auxdac_en_clr  : 1;  /* bit[6]: 定向线控gtc_auxdac_en设置清零信号 */
        unsigned char  reserved           : 1;  /* bit[7]:  */
    } reg;
} GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_UNION;
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_rf_trcv_on_clr_START  (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_rf_trcv_on_clr_END    (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_gps_ctrl_clr_START    (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_gps_ctrl_clr_END      (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_flash_ctrl_clr_START  (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_flash_ctrl_clr_END    (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxa_en_clr_START  (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxa_en_clr_END    (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxb_en_clr_START  (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxb_en_clr_END    (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_tx_en_clr_START   (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_tx_en_clr_END     (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_auxdac_en_clr_START   (6)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_auxdac_en_clr_END     (6)


/*****************************************************************************
 结构名    : GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_UNION
 结构说明  : GTC_EXT_LINE_CTRL_BITWISE_SET 寄存器结构定义。地址偏移量:0xF7，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ext_line_ctrl_bitwise_set_reg;
    struct
    {
        unsigned char  gtc_rf_trcv_on_set : 1;  /* bit[0]: 定向线控gtc_rf_trcv_on设置使能信号 */
        unsigned char  gtc_gps_ctrl_set   : 1;  /* bit[1]: 定向线控gtc_gps_ctrl设置使能信号 */
        unsigned char  gtc_flash_ctrl_set : 1;  /* bit[2]: 定向线控gtc_flash_ctrl设置使能信号 */
        unsigned char  gtc_abb_rxa_en_set : 1;  /* bit[3]: 定向线控gtc_abb_rxa_en设置使能信号 */
        unsigned char  gtc_abb_rxb_en_set : 1;  /* bit[4]: 定向线控gtc_abb_rxb_en设置使能信号 */
        unsigned char  gtc_abb_tx_en_set  : 1;  /* bit[5]: 定向线控gtc_abb_tx_en设置使能信号 */
        unsigned char  gtc_auxdac_en_set  : 1;  /* bit[6]: 定向线控gtc_auxdac_en设置 */
        unsigned char  reserved           : 1;  /* bit[7]:  */
    } reg;
} GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_UNION;
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_rf_trcv_on_set_START  (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_rf_trcv_on_set_END    (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_gps_ctrl_set_START    (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_gps_ctrl_set_END      (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_flash_ctrl_set_START  (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_flash_ctrl_set_END    (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxa_en_set_START  (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxa_en_set_END    (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxb_en_set_START  (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxb_en_set_END    (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_tx_en_set_START   (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_tx_en_set_END     (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_auxdac_en_set_START   (6)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_auxdac_en_set_END     (6)


/***======================================================================***
                     (2/9) register_define_gtc_dlfe
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_DAGC_CTRL_UNION
 结构说明  : GTC_DAGC_CTRL 寄存器结构定义。地址偏移量:0xA3，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dagc_ctrl_reg;
    struct
    {
        unsigned char  reserved_0           : 1;  /* bit[0]  :  */
        unsigned char  gtc_dagc_process_sel : 1;  /* bit[1]  : DAGC处理模式选择，1为搜索模式，0为NB解调模式。该模式信号的切换时间要求在每次搜索启动与解调启动之前配置完毕。 */
        unsigned char  reserved_1           : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_GTC_DAGC_CTRL_UNION;
#define GBBP_GTC_DAGC_CTRL_gtc_dagc_process_sel_START  (1)
#define GBBP_GTC_DAGC_CTRL_gtc_dagc_process_sel_END    (1)


/*****************************************************************************
 结构名    : GBBP_GTC_AGC_CTRL1_UNION
 结构说明  : GTC_AGC_CTRL1 寄存器结构定义。地址偏移量:0xB4，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_ctrl1_reg;
    struct
    {
        unsigned char  gtc_agc_en           : 1;  /* bit[0]  : AGC模块工作使能信号。
                                                               1：DCR&AGC正常工作；
                                                               0：DCR&AGC停止工作。
                                                               请注意该信号通常情况一直保持为高，除非需要异常终止AGC工作。 */
        unsigned char  gtc_frq_sel          : 3;  /* bit[1-3]: 直流偏置和前向通道增益调整RAM地址区域选择信号。
                                                               由于可能在实际中存在一个TDMA帧切换多个频点的可能，而各个频点的直流偏置值和前向通道增益又有所不同，因此这里通过3bit的选择，选出8组直流偏置粗调值和8组前向通道增益值。
                                                               AGC档位配置方式选择。0，由agc_init_gain配置，1，由agc_next_gain配置。 */
        unsigned char  reserved             : 1;  /* bit[4]  :  */
        unsigned char  gtc_agc_measure_mode : 1;  /* bit[5]  : 快速AGC测量门限模式选择信号。
                                                               0：快速AGC测量门限采用测量门限A；
                                                               1：快速AGC测量门限采用测量门限B。
                                                               此信号生效与否参见CPU配置信号cpu_fast_threshold_sel，当cpu_fast_threshold_sel=1时，gsp_agc_measure_mode生效。 */
        unsigned char  gtc_fast_agc_mode    : 1;  /* bit[6]  : 快速AGC测量时间模式选择信号。
                                                               0：快速AGC测量采用3轮模式；
                                                               1：快速AGC测量采用2轮模式，其相当于3轮模式的第1轮与第3轮。当配置gsp_agc_average_time[5:0]时，需要配置其中的[1:0]和[5:4]，即如果采用2轮模式32＋64，则需要配置gsp_agc_average_time[5:0]为6’b10xx01，其中xx表示可以任意配置。 */
        unsigned char  gtc_gain_sel         : 1;  /* bit[7]  : AGC档位配置方式选择。0，由agc_init_gain配置，1，由agc_next_gain配置。 */
    } reg;
} GBBP_GTC_AGC_CTRL1_UNION;
#define GBBP_GTC_AGC_CTRL1_gtc_agc_en_START            (0)
#define GBBP_GTC_AGC_CTRL1_gtc_agc_en_END              (0)
#define GBBP_GTC_AGC_CTRL1_gtc_frq_sel_START           (1)
#define GBBP_GTC_AGC_CTRL1_gtc_frq_sel_END             (3)
#define GBBP_GTC_AGC_CTRL1_gtc_agc_measure_mode_START  (5)
#define GBBP_GTC_AGC_CTRL1_gtc_agc_measure_mode_END    (5)
#define GBBP_GTC_AGC_CTRL1_gtc_fast_agc_mode_START     (6)
#define GBBP_GTC_AGC_CTRL1_gtc_fast_agc_mode_END       (6)
#define GBBP_GTC_AGC_CTRL1_gtc_gain_sel_START          (7)
#define GBBP_GTC_AGC_CTRL1_gtc_gain_sel_END            (7)


/*****************************************************************************
 结构名    : GBBP_GTC_AGC_CTRL2_UNION
 结构说明  : GTC_AGC_CTRL2 寄存器结构定义。地址偏移量:0xB5，初值:0x03，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_ctrl2_reg;
    struct
    {
        unsigned char  gtc_agc_average_time_round1 : 2;  /* bit[0-1]: AGC三轮能量累加处理长度配置。
                                                                      [1:0] 表示能量累加计算时第一轮处理长度，0，16symbol；1，32symbol；2，64symbol；3：128symbol。 */
        unsigned char  gtc_agc_average_time_round2 : 2;  /* bit[2-3]: AGC三轮能量累加处理长度配置。
                                                                      [3:2] 表示能量累加计算时第二轮处理长度，0，16symbol；1，32symbol；2，64symbol；3：128symbol。 */
        unsigned char  gtc_agc_average_time_round3 : 2;  /* bit[4-5]: AGC三轮能量累加处理长度配置。
                                                                      [5:4] 表示能量累加计算时第三轮处理长度，0，16symbol；1，32symbol；2，64symbol；3：128symbol。 */
        unsigned char  gtc_dcr_nv_sel              : 1;  /* bit[6]  : 粗调直流选择。
                                                                      1：选择时隙前计算直流，但需要先进行时隙前直流计算，才能使用该功能；
                                                                      0：选择NV项配置直流。 */
        unsigned char  gtc_slot_dcr_mode           : 1;  /* bit[7]  : 时隙前计算直流模式开启。
                                                                      1：采用时隙前直流计算模式，该信号必须在正常接收数据时的测量中断之前拉低；
                                                                      0：不使用时隙前直流计算模式。 */
    } reg;
} GBBP_GTC_AGC_CTRL2_UNION;
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round1_START  (0)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round1_END    (1)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round2_START  (2)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round2_END    (3)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round3_START  (4)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round3_END    (5)
#define GBBP_GTC_AGC_CTRL2_gtc_dcr_nv_sel_START               (6)
#define GBBP_GTC_AGC_CTRL2_gtc_dcr_nv_sel_END                 (6)
#define GBBP_GTC_AGC_CTRL2_gtc_slot_dcr_mode_START            (7)
#define GBBP_GTC_AGC_CTRL2_gtc_slot_dcr_mode_END              (7)


/*****************************************************************************
 结构名    : GBBP_GTC_AGC_START_UNION
 结构说明  : GTC_AGC_START 寄存器结构定义。地址偏移量:0xB6，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_start_reg;
    struct
    {
        unsigned char  gtc_register_clr       : 1;  /* bit[0]  : 多路数字细调环偏置寄存器清零，1个系统周期的脉冲信号。寄存器内的值需要长期保存，当UE关机时需要放入断电可存储的存储介质当中保存，等到UE再工作时恢复原样。这里提供了一个复位的选择，如果确实需要复位，配置该信号即可，默认情况下无需复位。 */
        unsigned char  gtc_init_gain_en       : 1;  /* bit[1]  : AGC工作时隙起始档位配置有效指示，1个系统周期的脉冲信号。需提前数据接收时刻100us启动该信号，需与gsp_init_gain和gsp_gain_sel信号配合使用。当该信号有效时，外部agc_init_gain或内部agc_next_gain的档位值才会置入到当前工作档位 */
        unsigned char  gtc_burst_register_clr : 1;  /* bit[2]  : 时隙前直流累加细调环清零信号 */
        unsigned char  gtc_dc_cal_start       : 1;  /* bit[3]  : 时隙前直流计算启动信号。 */
        unsigned char  gtc_dcr_recv_active    : 1;  /* bit[4]  : 解调与搜索通道直流偏置数字细调环激活，高电平有效。该信号有效时，相当于数字细调环激活，此时无法进行旁路功能。 */
        unsigned char  gtc_rf_ssi_ch_sel      : 2;  /* bit[5-6]: AGC模块SSI发送通道指示信号，将此信号拼接到gagc_ssi_data信号的高2bit使用。 */
        unsigned char  gtc_agc_fast_start     : 1;  /* bit[7]  : AGC模块快速测量开始指示信号，1个系统周期的脉冲信号。在工作开始指示信号发出之前需要配置好AGC的本时隙的初始档位。快速测量不进行解调与搜索。 */
    } reg;
} GBBP_GTC_AGC_START_UNION;
#define GBBP_GTC_AGC_START_gtc_register_clr_START        (0)
#define GBBP_GTC_AGC_START_gtc_register_clr_END          (0)
#define GBBP_GTC_AGC_START_gtc_init_gain_en_START        (1)
#define GBBP_GTC_AGC_START_gtc_init_gain_en_END          (1)
#define GBBP_GTC_AGC_START_gtc_burst_register_clr_START  (2)
#define GBBP_GTC_AGC_START_gtc_burst_register_clr_END    (2)
#define GBBP_GTC_AGC_START_gtc_dc_cal_start_START        (3)
#define GBBP_GTC_AGC_START_gtc_dc_cal_start_END          (3)
#define GBBP_GTC_AGC_START_gtc_dcr_recv_active_START     (4)
#define GBBP_GTC_AGC_START_gtc_dcr_recv_active_END       (4)
#define GBBP_GTC_AGC_START_gtc_rf_ssi_ch_sel_START       (5)
#define GBBP_GTC_AGC_START_gtc_rf_ssi_ch_sel_END         (6)
#define GBBP_GTC_AGC_START_gtc_agc_fast_start_START      (7)
#define GBBP_GTC_AGC_START_gtc_agc_fast_start_END        (7)


/*****************************************************************************
 结构名    : GBBP_GTC_RSSI_FRQ_HIGH_UNION
 结构说明  : GTC_RSSI_FRQ_HIGH 寄存器结构定义。地址偏移量:0xE4，初值:0x40，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_rssi_frq_high_reg;
    struct
    {
        unsigned char  gtc_rssi_frq_high       : 4;  /* bit[0-3]: 当前测量的RSSI对应的频点号高4bit，GSP_RSSI_FRQ_LOW，GSP_RSSI_FRQ_HIGH输出gsp_rssi_frq[11:0] */
        unsigned char  gtc_rrc_filter_para_sel : 3;  /* bit[4-6]: 滤波器系数选择信号。
                                                                  000：32阶90K无增益固定滤波系数；
                                                                  100：32阶可配置滤波系数；
                                                                  010：64阶可配置滤波系数；
                                                                  011：64阶135K固定滤波器系数；
                                                                  101：64阶BPF固定滤波系数，带通范围46.4K~89.7K；
                                                                  110：64阶80K固定滤波系数。 */
        unsigned char  reserved                : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_RSSI_FRQ_HIGH_UNION;
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rssi_frq_high_START        (0)
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rssi_frq_high_END          (3)
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rrc_filter_para_sel_START  (4)
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rrc_filter_para_sel_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_INIT_GAIN_RFIC_UNION
 结构说明  : GTC_INIT_GAIN_RFIC 寄存器结构定义。地址偏移量:0xE7，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_init_gain_rfic_reg;
    struct
    {
        unsigned char  gtc_init_gain        : 3;  /* bit[0-2]: bit2~0: RF每时隙处理的初始档位。 */
        unsigned char  reserved             : 3;  /* bit[3-5]:  */
        unsigned char  gtc_dcr_burst_mode   : 1;  /* bit[6]  : 时隙去直流打开开关，高电平有效,该信号有效时，表示时隙去直流功能可以启动，同时时隙去直流是否启动，还需要参考cpu配置去直流门限cpu_slot_dcr_rssi_threshold */
        unsigned char  gtc_rf_gain_word_sel : 1;  /* bit[7]  : 8档射频控制字选择信号，在BBP内部实现两套射频控制字备分，用于实现射频对等功能。
                                                               1:选择寄存器0x5068~5084
                                                               0:选择寄存器0x513c,0x5088~0x50a0 */
    } reg;
} GBBP_GTC_INIT_GAIN_RFIC_UNION;
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_init_gain_START         (0)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_init_gain_END           (2)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_dcr_burst_mode_START    (6)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_dcr_burst_mode_END      (6)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_rf_gain_word_sel_START  (7)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_rf_gain_word_sel_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_AGC_TRUNC_WIDTH_UNION
 结构说明  : GTC_AGC_TRUNC_WIDTH 寄存器结构定义。地址偏移量:0xED，初值:0x1B，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_trunc_width_reg;
    struct
    {
        unsigned char  gtc_agc_trunc_width  : 3;  /* bit[0-2]: AGC测量数字细调环截位位宽，默认值3’d3。                                        
                                                               3’d0：8；                                  
                                                               3’d1：10；                                 
                                                               3’d2：12；                                 
                                                               3’d3：14；                                  
                                                               3’d4：4；                                  
                                                               3’d5：6
                                                               3’d6: 9 */
        unsigned char  gtc_dagc_trunc_width : 3;  /* bit[3-5]: DAGC测量数字细调环截位位宽，默认值3‘d3。                                        
                                                               3’d0：8；                                  
                                                               3’d1：10；                                  
                                                               3’d2：12；                                  3'd3：14；                                  
                                                               3’d4：4；                                  
                                                               3’d5：6；
                                                               3'd6: 9 */
        unsigned char  reserved             : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_AGC_TRUNC_WIDTH_UNION;
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_agc_trunc_width_START   (0)
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_agc_trunc_width_END     (2)
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_dagc_trunc_width_START  (3)
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_dagc_trunc_width_END    (5)


/*****************************************************************************
 结构名    : GBBP_GTC_RX_IQ_COMPL_UNION
 结构说明  : GTC_RX_IQ_COMPL 寄存器结构定义。地址偏移量:0xF9，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_rx_iq_compl_reg;
    struct
    {
        unsigned char  gtc_iq_comp_en  : 1;  /* bit[0]  : RX IQMismatch校准配置参数组号选择信号。用于指示当前时隙使用哪一组相位校准软件配置值（A，P值），参考iq_comp_amp0~ iq_comp_amp4； */
        unsigned char  gtc_iq_comp_sel : 3;  /* bit[1-3]: IQMismatch模块补偿使能信号，高电平有效。在AGC模块启动前配置。 */
        unsigned char  reserved        : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_RX_IQ_COMPL_UNION;
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_en_START   (0)
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_en_END     (0)
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_sel_START  (1)
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_sel_END    (3)


/*****************************************************************************
 结构名    : GBBP_GTC_FAST_MEAS_SEL_CFG_UNION
 结构说明  : GTC_FAST_MEAS_SEL_CFG 寄存器结构定义。地址偏移量:0xFD，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_fast_meas_sel_cfg_reg;
    struct
    {
        unsigned char  gtc_rx_fast_gain_sel    : 1;  /* bit[0]  : AGC快速测量最后一轮（2轮测量对应第二轮，3轮测量对应第三轮）档位更新模式选择信号，1，表示最后一轮测量采用测量门限采用测量门限A进行档位判决，0表示最后一轮测量采用原快速测量测量门限。 */
        unsigned char  gtc_agc_r23_gain_no_upd : 1;  /* bit[1]  : 当AGC使用3轮快速测量模式时，快速测量的第二轮和第三轮之间不进行档位更新，即第二轮和第三轮的档位保持一致，高电平有效。 */
        unsigned char  reserved                : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_GTC_FAST_MEAS_SEL_CFG_UNION;
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_rx_fast_gain_sel_START     (0)
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_rx_fast_gain_sel_END       (0)
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_agc_r23_gain_no_upd_START  (1)
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_agc_r23_gain_no_upd_END    (1)


/***======================================================================***
                     (3/9) register_define_gtc_gsrch
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_SRCH_CFG_UNION
 结构说明  : GTC_SRCH_CFG 寄存器结构定义。地址偏移量:0xC3，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_srch_cfg_reg;
    struct
    {
        unsigned char  gtc_srch_en                : 1;  /* bit[0]  : 搜索使能信号，在整个搜索期间都保持为高电平。
                                                                     CPU接口清零配置寄存器配置
                                                                     复位默认值为0
                                                                     在搜索过程中，可以将此信号拉低，接收搜索处理。
                                                                     亦可由搜索中断拉低该信号 */
        unsigned char  gtc_srch_mod               : 3;  /* bit[1-3]: 搜索模式配置：
                                                                     111(FB+AFC+SB)：则BBP在完成FB搜索后自动启动AFC和SB同步，应用场景为初始小区同步；
			                                                         100（FB搜索）：在FB的搜索窗cpu_fb_peak_window内只进行FB搜索，应用场景为专用态下进行BSIC捕获。
                                                                     110(FB+AFC)：进行初始小区同步，完成FB搜索、AFC锁定判决。
			                                                         101(FB+SB)：进行FB搜索和SB搜索，不进行AFC，应用场景为邻小区测量（注：邻区测量也可以用"100+001"模式替代这种模式）；
                                                                     001（SB）：则只启动SB同步，不启动FB搜索和AFC，此时gsp_srch_starat的位置需提前按照历史信息（如100模式计算得出的FB位置）推算出来的SB的位置34个符号，以消除FB搜索位置有34个符号的误差带来的影响。应用场景为BSIC认证；
                                                                     010：表示只启动AFC，此时gsp_srch_start的位置即为FB的位置，应用场景为IDLE态下的周期性AFC；
                                                                     011：则表示只启动AFC和SB，此时gsp_srch_start的位置即为FB的位置，应用场景为NB解调前的AFC和SB同步
                                                                     复位默认值为3’b000 */
		unsigned char  gtc_fb_pos_adj             : 3;  /* bit[4-6]: CPU对FB搜索的位置的调整，主要为规避设计风险而设计的。
                                                                     000:不调整；001：向后调1(symbol)；
                                                                     010：向后调2；011：向后调3
                                                                     111：向前调1；110：向前调2；
                                                                     101：向前调3；100：向前调4
                                                                     复位默认值为3’b000
                                                                     此数据在搜索模式设置为111和101时有效。即搜索得到的FB位置根据gtc_fb_pos_adj值调整，在下一帧启动sb搜索。*/
		unsigned char  gtc_soft_agc_drssi_25db_en : 1;  /* bit[7]   : 软件强制配置DRSSI的使能开关，该使能有效时，软件配置DRSSI值有效 */
    } reg;
} GBBP_GTC_SRCH_CFG_UNION;
#define GBBP_GTC_SRCH_CFG_gtc_srch_en_START                 (0)
#define GBBP_GTC_SRCH_CFG_gtc_srch_en_END                   (0)
#define GBBP_GTC_SRCH_CFG_gtc_srch_mod_START                (1)
#define GBBP_GTC_SRCH_CFG_gtc_srch_mod_END                  (3)
#define GBBP_GTC_SRCH_CFG_gtc_fb_pos_adj_START              (4)
#define GBBP_GTC_SRCH_CFG_gtc_fb_pos_adj_END                (6)
#define GBBP_GTC_SRCH_CFG_gtc_soft_agc_drssi_25db_en_START  (7)
#define GBBP_GTC_SRCH_CFG_gtc_soft_agc_drssi_25db_en_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_SRCH_START_UNION
 结构说明  : GTC_SRCH_START 寄存器结构定义。地址偏移量:0xC4，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_srch_start_reg;
    struct
    {
        unsigned char  gtc_srch_start      : 1;  /* bit[0]  : 搜索的启动信号，脉冲信号。每次启动搜索时需要置一次，1有效（下同）,GTC模块内部已做处理，使其在需要的qb内的第一个clk_sys处生效,GTC逻辑自清零。当gsp_srch_mod=001时，gsp_srch_start必须提前当前默认的SB位置34个符号产生。
                                                              注：启动搜索时必须配置 */
        unsigned char  reserved            : 5;  /* bit[1-5]:  */
		unsigned char  gtc_nco_en          : 1;  /* bit[6]  : 邻区纠偏使能，0表示关闭纠偏，1表示打开。也可以用于对邻区NB纠偏。但是服务区任务时，不能使用纠偏。如果服务区与邻区频点一样，也不能打开纠偏，否则会影响VCTXO。 */
		unsigned char  gtc_ncell_srch_flag : 1;  /* bit[7]  : 1标识当前是邻区搜索，0标识当前是服务区搜索。启动邻区搜索时，必须配置该信号。 */
    } reg;
} GBBP_GTC_SRCH_START_UNION;
#define GBBP_GTC_SRCH_START_gtc_srch_start_START       (0)
#define GBBP_GTC_SRCH_START_gtc_srch_start_END         (0)
#define GBBP_GTC_SRCH_START_gtc_nco_en_START           (6)
#define GBBP_GTC_SRCH_START_gtc_nco_en_END             (6)
#define GBBP_GTC_SRCH_START_gtc_ncell_srch_flag_START  (7)
#define GBBP_GTC_SRCH_START_gtc_ncell_srch_flag_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_SB_SAVE_START_UNION
 结构说明  : GTC_SB_SAVE_START 寄存器结构定义。地址偏移量:0xD0，初值:0x00，宽度:8
 寄存器说明:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_sb_save_start_reg;
    struct
    {
        unsigned char  gtc_sb_save_start     : 1;  /* bit[0]  : 软件配置启动SB数据存储的时刻，GTC指令配置。因DAGC数据比空口数据延迟1slot，因此模块内部实际开始存储的时间应延迟1slot。
                                                                注：启动搜索时必须配置gsp_nb_afc_en=0。 */
        unsigned char  gtc_sb_start_from_ram : 1;  /* bit[1]  : 脉冲信号，基于RAM中的数据，启动SB搜索，该信号没有空口延时，有效后，立刻启动001搜索的操作 */
        unsigned char  gtc_fast_101_en       : 1;  /* bit[2]  : 并行FB和SB模式使能信号，在搜索结束后自动拉低 */
        unsigned char  reserved              : 5;  /* bit[3-7]:  */
    } reg;
} GBBP_GTC_SB_SAVE_START_UNION;
#define GBBP_GTC_SB_SAVE_START_gtc_sb_save_start_START      (0)
#define GBBP_GTC_SB_SAVE_START_gtc_sb_save_start_END        (0)
#define GBBP_GTC_SB_SAVE_START_gtc_sb_start_from_ram_START  (1)
#define GBBP_GTC_SB_SAVE_START_gtc_sb_start_from_ram_END    (1)
#define GBBP_GTC_SB_SAVE_START_gtc_fast_101_en_START        (2)
#define GBBP_GTC_SB_SAVE_START_gtc_fast_101_en_END          (2)


/***======================================================================***
                     (4/9) register_define_gtc_dem
 ***======================================================================***/
 /*****************************************************************************
 结构名    : GBBP_GTC_DEMOD_PARA1_UNION
 结构说明  : GTC_DEMOD_PARA1 寄存器结构定义。地址偏移量:0xB0，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_demod_para1_reg;
    struct
    {
        unsigned char  gtc_nb_demod_en           : 1;  /* bit[0]  : NB解调使能信号，高电平有效，在NB解调过程中一直为高，在启动译码前也需要将该信号置1
                                                                    CPU接口清零配置参见地址0x01124寄存器配置
                                                                    注意：在需要NB解调的时候，请关闭gsp_srch_en(清零参见0x01124寄存器)，在连接态时对邻区进行FB/SB搜索时，可以维持gsp_nb_demod_en为高，即搜索的优先级高于解调。
                                                                    复位默认值为0 */
        unsigned char  gtc_dl_tsc_group_num_3pre : 3;  /* bit[1-3]: 训练序列组号
                                                                    000：0组；001：1组；
                                                                    010：2组；011：3组；
                                                                    100：4组；101：5组；
                                                                    110：6组；111：7组
                                                                    复位默认值为0 */
        unsigned char  gtc_demod_slot_3pre       : 3;  /* bit[4-6]: 启动解调时的时隙号，用于TOA值随路上报 */
        unsigned char  gtc_nserv_cell_ind_3pre   : 1;  /* bit[7]  : 1表示非服务小区
                                                                    0表示服务小区
                                                                    用于TOA值随路上报 */
    } reg;
} GBBP_GTC_DEMOD_PARA1_UNION;
#define GBBP_GTC_DEMOD_PARA1_gtc_nb_demod_en_START            (0)
#define GBBP_GTC_DEMOD_PARA1_gtc_nb_demod_en_END              (0)
#define GBBP_GTC_DEMOD_PARA1_gtc_dl_tsc_group_num_3pre_START  (1)
#define GBBP_GTC_DEMOD_PARA1_gtc_dl_tsc_group_num_3pre_END    (3)
#define GBBP_GTC_DEMOD_PARA1_gtc_demod_slot_3pre_START        (4)
#define GBBP_GTC_DEMOD_PARA1_gtc_demod_slot_3pre_END          (6)
#define GBBP_GTC_DEMOD_PARA1_gtc_nserv_cell_ind_3pre_START    (7)
#define GBBP_GTC_DEMOD_PARA1_gtc_nserv_cell_ind_3pre_END      (7)


/*****************************************************************************
 结构名    : GBBP_GTC_DEMOD_PARA2_UNION
 结构说明  : GTC_DEMOD_PARA2 寄存器结构定义。地址偏移量:0xB1，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_demod_para2_reg;
    struct
    {
        unsigned char  gtc_demod_type_3pre         : 2;  /* bit[0-1]: 下行调制方式指示 00 GMSK调制 01 8PSK调制,10表示下行调制方式未知，11 无意义；
                                                                      由于在同一块中连续两个burst同时被判错的概率非常小，因此如果同一码块的前两个时隙被判为同一种调制模式，则在解调第三和第四个burst时直接配置前两个burst判决的调制方式进行解调；如果前两个时隙检测出的调制方式不同，则需要判决第三个burst，但不需要判决第四个burst，前三个burst中肯定有两个burst是同一种调制模式，则在解调第四个burst时直接配置前三个burst判决结果占两个的调制方式进行解调.
                                                                      复位默认值为2’b00 */
        unsigned char  gtc_ls_dcr_en_3pre          : 1;  /* bit[2]  : LS去直流使能信号，0表示关闭，1表示打开。为保证性能，仅在26M倍频点打开，其他频点需关闭。且打开该功能时，需要同时打开AGC模块的时隙平均去直流。仅对8PSK调制方式有效。 */
        unsigned char  gtc_demod_flag_sav_pos_3pre : 5;  /* bit[3-7]: PS域DATA业务下
                                                                      调制盲检测标志存储位置多时隙的第一,第二，第三，
                                                                      第四，第五，第六个时隙的六个BURST调制盲检测标志依次
                                                                      存储在3～0，7～4，11～8，15～12，23～20，27～24位置，而每个码块的第一个BURST盲检测标志分别存放在0，4，8，12。20，24位置,每个码块的第二个BURST盲检测标志分别存放在1，5，9，13，21，25位置,下面依次类推
                                                                      复位默认值为0
                                                                      如果是CS域或者PS固定位置的控制信道，请务必配置为16～19 */
    } reg;
} GBBP_GTC_DEMOD_PARA2_UNION;
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_type_3pre_START          (0)
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_type_3pre_END            (1)
#define GBBP_GTC_DEMOD_PARA2_gtc_ls_dcr_en_3pre_START           (2)
#define GBBP_GTC_DEMOD_PARA2_gtc_ls_dcr_en_3pre_END             (2)
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_flag_sav_pos_3pre_START  (3)
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_flag_sav_pos_3pre_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_DEM_PARA3_UNION
 结构说明  : GTC_DEM_PARA3 寄存器结构定义。地址偏移量:0xB2，初值:0x50，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dem_para3_reg;
    struct
    {
        unsigned char  gtc_dem_burst_pos_3pre : 7;  /* bit[0-6]: 解调BURST数据存储起始位置指示。如果是CS域业务，起始位置对应为26复帧中映射位置，映射到36～36＋gsp_dl_burst_sav_cycle-1内的编号；如果是EGPRS/GPRS业务，不管是单时隙还是多时隙，时隙配置中的第一个时隙码块解调数据固定存放在0，3，6，9；时隙配置中的第二个时隙码块解调数据固定存放在12，15，18，21；时隙配置中的第三个时隙码块解调数据固定存放在24，27，30，33；时隙配置中的第四个时隙码块解调数据固定存放在36，39，42，45的位置；时隙配置中的第五个时隙码块解调数据固定存放在81，84，87，90；时隙配置中的第六个时隙码块解调数据固定存放在93，96，99，102；。如果是PCCCH，PBCCH或者BCCH，CCCH，SDCCH等，可以存放在68～71，SACCH存放在72～75位置，PTCCH存放在76～79位置；其他控制信道则由软件根据数据域业务的BURST存放循环周期（参见译码的GTC配置，gsp_dl_burst_sav_cycle）来灵活控制；如果是SCH则解调数据存放在80位置。复位默认值为80。 */
        unsigned char  reserved               : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_DEM_PARA3_UNION;
#define GBBP_GTC_DEM_PARA3_gtc_dem_burst_pos_3pre_START  (0)
#define GBBP_GTC_DEM_PARA3_gtc_dem_burst_pos_3pre_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_DEMOD_START_UNION
 结构说明  : GTC_DEMOD_START 寄存器结构定义。地址偏移量:0xB3，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_demod_start_reg;
    struct
    {
        unsigned char  gtc_demod_start     : 1;  /* bit[0]  : 下行NB解调启动信号，脉冲信号，
                                                              GTC模块内部已做处理，使其在需要的qb内的第一个clk_sys处生效,GTC逻辑自清零 */
        unsigned char  gtc_gaci_en_2pre    : 1;  /* bit[1]  : 邻频检测模块使能信号。邻频抑制功能仅针对于NB情况下使用，搜索模式下（FB、SB）不进行邻频检测。 */
        unsigned char  gtc_gaci_index_2pre : 2;  /* bit[2-3]: 滤波器系数选择位
                                                              2’b00：滤波器0，无干扰
                                                              2’b01：滤波器1，+200Khz干扰
                                                              2’b10：滤波器2，-200Khz干扰
                                                              2’b11：滤波器3，
                                                              200Khz干扰 */
        unsigned char  reserved            : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_DEMOD_START_UNION;
#define GBBP_GTC_DEMOD_START_gtc_demod_start_START      (0)
#define GBBP_GTC_DEMOD_START_gtc_demod_start_END        (0)
#define GBBP_GTC_DEMOD_START_gtc_gaci_en_2pre_START     (1)
#define GBBP_GTC_DEMOD_START_gtc_gaci_en_2pre_END       (1)
#define GBBP_GTC_DEMOD_START_gtc_gaci_index_2pre_START  (2)
#define GBBP_GTC_DEMOD_START_gtc_gaci_index_2pre_END    (3)


/*****************************************************************************
 结构名    : GBBP_GTC_TOA_PARA_UNION
 结构说明  : GTC_TOA_PARA 寄存器结构定义。地址偏移量:0xBD，初值:0x10，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_toa_para_reg;
    struct
    {
        unsigned char  gtc_nb_pos_3pre           : 4;  /* bit[0-3]: 软件规避模式下由软件计算的当前NB位置的调整值。正常模式下该信号可以配置为0
                                                                    允许的取值范围：-1~7，单位为符号。补码表示。如：
                                                                    4’b1111：表示当前的NB位置较当前的时隙头要提前1个符号；
                                                                    4’b0000：表示当前的NB位置正好等于当前的时隙头；
                                                                    4’b0001：表示当前的NB位置较当前的时隙头要延迟1个符号；
                                                                    4’b0010：表示当前的NB位置较当前的时隙头要延迟2个符号；
                                                                    。。。。。。
                                                                    4’b0111：表示当前的NB位置较当前的时隙头要延迟7个符号。 */
        unsigned char  gtc_nb_toa_alpha_sel_3pre : 1;  /* bit[4]  : 选择是否在本时隙进行能量Alpha滤波，电平信号。
                                                                    1：进行能量Alpha滤波，系数为cpu_alpha_parameter;
                                                                    0：不进行能量Alpha滤波。
                                                                    默认值为1 */
        unsigned char  gtc_nb_pos_sel_3pre       : 1;  /* bit[5]  : 软件计算当前NB位置的选择信号。
                                                                    1’d1：表示选择软件计算的当前NB位置调整值；
                                                                    1’d0：表示选择GBBP计算的当前NB位置调整值。正常模式下请务必将该信号配置为0,软件规避模式下需要同时配置gsp_nb_pos参数
                                                                    默认值为0 */
        unsigned char  gtc_nb_nco_en_2pre        : 1;  /* bit[6]  : 解邻区NB时，纠偏使能信号。
                                                                    1表示进行纠偏；
                                                                    0表示不纠偏
                                                                    配置该信号使能时，需同时配置gsp_nco_ini_value */
        unsigned char  gtc_nb_afc_en_3pre        : 1;  /* bit[7]  : NB-AFC使能信号，1有效。
                                                                    默认值为0。
                                                                    注：当启动搜索时，此信号必须配置为零，CPU接口清零配置参见地址0x01124寄存器配置。 */
    } reg;
} GBBP_GTC_TOA_PARA_UNION;
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_3pre_START            (0)
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_3pre_END              (3)
#define GBBP_GTC_TOA_PARA_gtc_nb_toa_alpha_sel_3pre_START  (4)
#define GBBP_GTC_TOA_PARA_gtc_nb_toa_alpha_sel_3pre_END    (4)
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_sel_3pre_START        (5)
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_sel_3pre_END          (5)
#define GBBP_GTC_TOA_PARA_gtc_nb_nco_en_2pre_START         (6)
#define GBBP_GTC_TOA_PARA_gtc_nb_nco_en_2pre_END           (6)
#define GBBP_GTC_TOA_PARA_gtc_nb_afc_en_3pre_START         (7)
#define GBBP_GTC_TOA_PARA_gtc_nb_afc_en_3pre_END           (7)


/***======================================================================***
                     (5/9) register_define_gtc_gcipher
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_A5_CIPH_CFG_UNION
 结构说明  : GTC_A5_CIPH_CFG 寄存器结构定义。地址偏移量:0xC6，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_a5_ciph_cfg_reg;
    struct
    {
        unsigned char  gtc_ul_ciph_en       : 1;  /* bit[0]  : 上行解密模块工作模式选择,
                                                               1表示上行发射需要加密
                                                               0表示上行发射不需要
                                                               默认值为0 */
        unsigned char  gtc_ul_gsm_alg_sel   : 3;  /* bit[1-3]: 上行行A51或者A52,A53算法选择
                                                               gtc_ul_gsm_alg_sel[2:0] =1表示选择A51算法 
                                                               gtc_ul_gsm_alg_sel[2:0] =7表示选择A53算法 */
        unsigned char  gtc_ul_fn_adj_flag   : 2;  /* bit[4-5]: 上行帧号调整标志
                                                               11表示输入到加密模块的FN需要做减1操作，01表示输入到加密模块的FN需要做加1操作;
                                                               10，00表示无加，减1操作;
                                                               复位默认值为00，正常使用下应该配置为00；01、11是出错时的规避模式. */
        unsigned char  reserved             : 1;  /* bit[6]  :  */
        unsigned char  gtc_ul_a5_ciph_start : 1;  /* bit[7]  : 1表示启动上行A5加密。每次有加密操作该信号必须配置。 */
    } reg;
} GBBP_GTC_A5_CIPH_CFG_UNION;
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_ciph_en_START        (0)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_ciph_en_END          (0)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_gsm_alg_sel_START    (1)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_gsm_alg_sel_END      (3)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_fn_adj_flag_START    (4)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_fn_adj_flag_END      (5)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_a5_ciph_start_START  (7)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_a5_ciph_start_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_A5_DECIPH_CFG_UNION
 结构说明  : GTC_A5_DECIPH_CFG 寄存器结构定义。地址偏移量:0xC5，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_a5_deciph_cfg_reg;
    struct
    {
        unsigned char  gtc_dl_deciph_en_3pre   : 1;  /* bit[0]  : 下行解密模块工作模式选择：
                                                                  1表示下行需要解密，
                                                                  0表示下行不解密，
                                                                  默认值为0
                                                                  解调PS域业务和SCH的BURST时请配置为0  */
        unsigned char  gtc_dl_gsm_alg_sel_3pre : 3;  /* bit[1-3]: 下行A51或者A52,A53算法选择：
                                                                  gtc_dl_gsm_alg_sel[2:0] =1表示选择A51算法；
                                                                  gtc_dl_gsm_alg_sel[2:0] =7表示选择A53算法 */
        unsigned char  gtc_dl_fn_adj_flag_3pre : 2;  /* bit[4-5]: 下行帧号调整标志：
                                                                  11表示输入到解密模块的FN需要做减1操作，01表示输入到解密模块的FN需要做加1操作；
                                                                  10，00表示无加，减1操作；
                                                                  复位默认值为00，正常使用下应该配置为00；01、11是出错时的规避模式 */
        unsigned char  reserved                : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_A5_DECIPH_CFG_UNION;
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_deciph_en_3pre_START    (0)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_deciph_en_3pre_END      (0)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_gsm_alg_sel_3pre_START  (1)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_gsm_alg_sel_3pre_END    (3)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_fn_adj_flag_3pre_START  (4)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_fn_adj_flag_3pre_END    (5)


/***======================================================================***
                     (6/9) register_define_gtc_gdec
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_DL_CB_INDEX_UNION
 结构说明  : GTC_DL_CB_INDEX 寄存器结构定义。地址偏移量:0xC7，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dl_cb_index_reg;
    struct
    {
        unsigned char  gtc_dl_cb_index  : 7;  /* bit[0-6]: 一般情况下表示下行业务序号.当配置为120～123表示下行业务分类 
                                                           120 表示CS域的AFS业务
                                                           121 表示CS域的AHS业务
                                                           122 表示PS域业务（HARQ初传或者重传）
                                                           123 表示HARQ合并译码
                                                           复位默认值为7’d0 */
        unsigned char  gtc_cycle_rpt_en : 1;  /* bit[7]  : 1表示循环上报模式使能，此时单码块完成译码就上报中断；
                                                           0表示缓存上报模式使能，多个码块译码后缓存上报中断。 */
    } reg;
} GBBP_GTC_DL_CB_INDEX_UNION;
#define GBBP_GTC_DL_CB_INDEX_gtc_dl_cb_index_START   (0)
#define GBBP_GTC_DL_CB_INDEX_gtc_dl_cb_index_END     (6)
#define GBBP_GTC_DL_CB_INDEX_gtc_cycle_rpt_en_START  (7)
#define GBBP_GTC_DL_CB_INDEX_gtc_cycle_rpt_en_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_DEC_BURST_POS_UNION
 结构说明  : GTC_DEC_BURST_POS 寄存器结构定义。地址偏移量:0xC8，初值:0xD0，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_burst_pos_reg;
    struct
    {
        unsigned char  gtc_dec_burst_pos  : 7;  /* bit[0-6]: 表示待译码码块的第一个BURST在VALPP软值存储RAM中的位置编号。如果是CS域业务，起始位置在36～36＋gsp_dl_burst_sav_cycle-1，由软件根据码块在复帧中映射起始位置配置；如果是在EGPRS/GPRS业务，不管是单时隙还是多时隙，如果对第一个时隙配置的码块译码，则配置为0；如果对第二个时隙配置的码块译码，则配置为12；如果对第三个时隙配置的码块译码，则配置为24；如果对第四个时隙配置的码块译码，则配置为36；如果对第五时隙配置的码块译码，则配置为81；如果对第六个时隙配置的码块译码，则配置为93；对SDCCH，PBCCH，BCCH，CCCH配置为68，对于SACCH配置为72，PTCCH则配置为76。特别注意：如果是半速率业务，假设当前译码启动时配置位置为a，且当当前译码上报译码失败原因为FACCH_H前四个BURST时，在下次启动译码应该将本参数仍然配置为a，在下次译码完成后，启动下下次译码时应该配置为a＋4（gsp_dl_burst_sav_cycle内取模，然后加上36）值。其他未分配位置，由软件根据业务需要灵活配置。复位默认值未80 */
        unsigned char  gtc_amr_state_flag : 1;  /* bit[7]  : 1表示处于AMR 的SPEECH态
                                                             0表示处于AMR 的DTX态
                                                             默认值为1 */
    } reg;
} GBBP_GTC_DEC_BURST_POS_UNION;
#define GBBP_GTC_DEC_BURST_POS_gtc_dec_burst_pos_START   (0)
#define GBBP_GTC_DEC_BURST_POS_gtc_dec_burst_pos_END     (6)
#define GBBP_GTC_DEC_BURST_POS_gtc_amr_state_flag_START  (7)
#define GBBP_GTC_DEC_BURST_POS_gtc_amr_state_flag_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_DEC_TYPE1_UNION
 结构说明  : GTC_DEC_TYPE1 寄存器结构定义。地址偏移量:0xC9，初值:0x82，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_type1_reg;
    struct
    {
        unsigned char  gtc_enhanced_dec_mode : 2;  /* bit[0-1]: gtc_enhanced_dec_mode[1]＝1表示增强型译码模式使能；0表示采用传统VTB译码模式
                                                                gtc_enhanced_dec_mode[0]＝1表示在增强型译码模式下MCS5-69业务采用传统VTB译码模式；0表示MCS5-69业务采用增强型译码模式。
                                                                MCS7~9初传不支持增强型译码。
                                                                实际使用中：
                                                                1、初传MCS5~9均配置为增强型译码，当判决出业务为MCS7~9时，此时BBP采用传统VTB译码模式，同时cb1_crc_result[7:0]、cb2_crc_result[7:0]、cb3_crc_result[7:0]上报结果均无效。
                                                                
                                                                2、重传MCS7~9配置为增强型译码，此时MCS7~9采用增强型译码，同时cb1_crc_result[7:0]、cb2_crc_result[7:0]、cb3_crc_result[7:0]上报结果均有效。
                                                                默认为2’b10 */
        unsigned char  reserved              : 2;  /* bit[2-3]:  */
        unsigned char  gtc_dl_amr_cmc_frame  : 1;  /* bit[4]  : 表示当前帧号的CMI和CMC指示，0表示是CMI帧，1表示是CMC帧。复位默认值为0 */
        unsigned char  gtc_dl_amr_cmi_value  : 2;  /* bit[5-6]: 软件配置的历史CMI值
                                                                默认值为0x0 */
        unsigned char  gtc_facch_dec_mode    : 1;  /* bit[7]  : FACCH译码模式选择，AFS，FS，EFS下1 表示相关译码结果判断是否为FACCH偷帧，如果是,则逻辑启动FACCH译码,如果不是,则逻辑启动其他码块译码；0 表示直接启动FACCH译码根据译码的CRC校验结果判断是否为FACCH偷帧。
                                                                AHS，HS下1 表示相关译码结果判断是否为FACCH偷帧，如果是,则逻辑启动FACCH译码,如果不是,则逻辑启动其他码块译码；0标识直接作为FACCH译码。
                                                                默认值为1 */
    } reg;
} GBBP_GTC_DEC_TYPE1_UNION;
#define GBBP_GTC_DEC_TYPE1_gtc_enhanced_dec_mode_START  (0)
#define GBBP_GTC_DEC_TYPE1_gtc_enhanced_dec_mode_END    (1)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmc_frame_START   (4)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmc_frame_END     (4)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmi_value_START   (5)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmi_value_END     (6)
#define GBBP_GTC_DEC_TYPE1_gtc_facch_dec_mode_START     (7)
#define GBBP_GTC_DEC_TYPE1_gtc_facch_dec_mode_END       (7)


/*****************************************************************************
 结构名    : GBBP_GTC_DEC_TYPE2_UNION
 结构说明  : GTC_DEC_TYPE2 寄存器结构定义。地址偏移量:0xCA，初值:0x02，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_type2_reg;
    struct
    {
        unsigned char  gtc_cs4_judge_mode     : 2;  /* bit[0-1]: 00 表示在GPRS网络，根据网络分配信息，将CS4和MCS1234区分为CS4
                                                                 01 表示在EGPRS网络，据网络分配信息，将CS4和MCS1234区分为MCS1234（该功能请慎用）
                                                                 10 表示先做MCS1234的HEADER的译码，如果译码结果的CRC校验正确则判为MCS1234，否则判为CS4
                                                                 默认值为0x2 */
        unsigned char  reserved               : 2;  /* bit[2-3]:  */
        unsigned char  gtc_edge_usf_rxqual_en : 1;  /* bit[4]  : 1表示 EDGE业务下USF参与BER和BEP统计，默认值为0 */
        unsigned char  gtc_bep_en             : 1;  /* bit[5]  : 1表示打开bep统计功能，0表示关闭bep统计功能，默认值为0 */
        unsigned char  gtc_ib_im_rxqual_en    : 1;  /* bit[6]  : 1表示带内bit ib和ID_MARKER bit参与质量测量统计
                                                                 0表示带内bit ib和ID_MARKER bit不参与质量测量统计
                                                                 默认值为0 */
        unsigned char  gtc_harq_func_en       : 1;  /* bit[7]  : 1表示软件配置HARQ功能使能，0表示该功能屏蔽
                                                                 默认值为0 */
    } reg;
} GBBP_GTC_DEC_TYPE2_UNION;
#define GBBP_GTC_DEC_TYPE2_gtc_cs4_judge_mode_START      (0)
#define GBBP_GTC_DEC_TYPE2_gtc_cs4_judge_mode_END        (1)
#define GBBP_GTC_DEC_TYPE2_gtc_edge_usf_rxqual_en_START  (4)
#define GBBP_GTC_DEC_TYPE2_gtc_edge_usf_rxqual_en_END    (4)
#define GBBP_GTC_DEC_TYPE2_gtc_bep_en_START              (5)
#define GBBP_GTC_DEC_TYPE2_gtc_bep_en_END                (5)
#define GBBP_GTC_DEC_TYPE2_gtc_ib_im_rxqual_en_START     (6)
#define GBBP_GTC_DEC_TYPE2_gtc_ib_im_rxqual_en_END       (6)
#define GBBP_GTC_DEC_TYPE2_gtc_harq_func_en_START        (7)
#define GBBP_GTC_DEC_TYPE2_gtc_harq_func_en_END          (7)


/*****************************************************************************
 结构名    : GBBP_GTC_HARQ_POS1_UNION
 结构说明  : GTC_HARQ_POS1 寄存器结构定义。地址偏移量:0xCB，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_harq_pos1_reg;
    struct
    {
        unsigned char  gtc_harq1_pos : 7;  /* bit[0-6]: 在HARQ译码过程中表示需要做harq合并的第一个码块的读起始位置；在HARQ软值保存过程中为第一个码块的写起始位置。在Repeat FACCH/SACCH业务，取值只能为0~7。其它业务，取值范围是0~127。（V3R3、V8R1等HARQ外移版本，此配置范围统一改为0~127。）
                                                        默认值为0 */
        unsigned char  reserved      : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_HARQ_POS1_UNION;
#define GBBP_GTC_HARQ_POS1_gtc_harq1_pos_START  (0)
#define GBBP_GTC_HARQ_POS1_gtc_harq1_pos_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_HARQ_POS2_UNION
 结构说明  : GTC_HARQ_POS2 寄存器结构定义。地址偏移量:0xCC，初值:0x01，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_harq_pos2_reg;
    struct
    {
        unsigned char  gtc_harq2_pos : 7;  /* bit[0-6]: 在HARQ译码过程中表示需要做harq合并的第二个码块的读起始位置；在HARQ软值保存过程中为第二个码块的写起始位置。
                                                        默认值为1 */
        unsigned char  reserved      : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_HARQ_POS2_UNION;
#define GBBP_GTC_HARQ_POS2_gtc_harq2_pos_START  (0)
#define GBBP_GTC_HARQ_POS2_gtc_harq2_pos_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_HARQ1_CB_INDEX_UNION
 结构说明  : GTC_HARQ1_CB_INDEX 寄存器结构定义。地址偏移量:0xCF，初值:0x34，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_harq1_cb_index_reg;
    struct
    {
        unsigned char  gtc_harq1_cb_index : 7;  /* bit[0-6]: bit6～bit0：参与HARQ合并译码的任意一个码块（应该为DATA块）的CB_INDEX，复位默认值为7’d52，如果是MCS6，9、MCS5，7合并，那么可以选择任意一个码块（应该为DATA块）的cb_index进行配置 */
        unsigned char  reserved           : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_HARQ1_CB_INDEX_UNION;
#define GBBP_GTC_HARQ1_CB_INDEX_gtc_harq1_cb_index_START  (0)
#define GBBP_GTC_HARQ1_CB_INDEX_gtc_harq1_cb_index_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_DL_BURST_CYCLE_UNION
 结构说明  : GTC_DL_BURST_CYCLE 寄存器结构定义。地址偏移量:0xD2，初值:0xD8，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dl_burst_cycle_reg;
    struct
    {
        unsigned char  gtc_dl_burst_sav_cycle : 6;  /* bit[0-5]: 下行译码存放BURST循环周期（该参数只对CS域业务有效），复位默认值为24，表示周期为24；在22BURST交织的业务下需要根据软件需求配置。
                                                                 000000表示周期为0,
                                                                 ……
                                                                 100000表示周期为32
                                                                 最大可配置为44
                                                                 复位默认值为6’d24 */
        unsigned char  gtc_bler_en            : 1;  /* bit[6]  : 质量测量BLER模块使能信号，高电平有效。（必要时关断，以节省功耗）
                                                                 复位默认值为1 */
        unsigned char  gtc_ber_en             : 1;  /* bit[7]  : 质量测量BER模块使能信号，高电平有效。（必要时关断，以节省功耗）
                                                                 默认值为1 */
    } reg;
} GBBP_GTC_DL_BURST_CYCLE_UNION;
#define GBBP_GTC_DL_BURST_CYCLE_gtc_dl_burst_sav_cycle_START  (0)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_dl_burst_sav_cycle_END    (5)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_bler_en_START             (6)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_bler_en_END               (6)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_ber_en_START              (7)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_ber_en_END                (7)


/*****************************************************************************
 结构名    : GBBP_GTC_DEC_START_UNION
 结构说明  : GTC_DEC_START 寄存器结构定义。地址偏移量:0xD3，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_start_reg;
    struct
    {
        unsigned char  gtc_dec_start     : 1;  /* bit[0]  : NB承载业务的译码启动信号,GTC逻辑自清零 */
        unsigned char  gtc_last_dec_flag : 1;  /* bit[1]  : 1表示本次译码需要上报中断，该译码中断模式只在gtc_cycle_rpt_en为0才生效 */
        unsigned char  gtc_dec_slot      : 3;  /* bit[2-4]: 本次启动译码时对应的时隙号 */
        unsigned char  reserved          : 1;  /* bit[5]  :  */
        unsigned char  gtc_bler_clr      : 1;  /* bit[6]  : 接收质量上报BLER清零信号，脉冲信号,GTC逻辑自清零 */
        unsigned char  gtc_ber_clr       : 1;  /* bit[7]  : 接收质量上报BER清零信号，脉冲信号,GTC逻辑自清零 */
    } reg;
} GBBP_GTC_DEC_START_UNION;
#define GBBP_GTC_DEC_START_gtc_dec_start_START      (0)
#define GBBP_GTC_DEC_START_gtc_dec_start_END        (0)
#define GBBP_GTC_DEC_START_gtc_last_dec_flag_START  (1)
#define GBBP_GTC_DEC_START_gtc_last_dec_flag_END    (1)
#define GBBP_GTC_DEC_START_gtc_dec_slot_START       (2)
#define GBBP_GTC_DEC_START_gtc_dec_slot_END         (4)
#define GBBP_GTC_DEC_START_gtc_bler_clr_START       (6)
#define GBBP_GTC_DEC_START_gtc_bler_clr_END         (6)
#define GBBP_GTC_DEC_START_gtc_ber_clr_START        (7)
#define GBBP_GTC_DEC_START_gtc_ber_clr_END          (7)


/*****************************************************************************
 结构名    : GBBP_GTC_DEC_TEST_MODE_EN_UNION
 结构说明  : GTC_DEC_TEST_MODE_EN 寄存器结构定义。地址偏移量:0xE0，初值:0xF0，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_test_mode_en_reg;
    struct
    {
        unsigned char  gtc_dec_test_mode_en : 1;  /* bit[0]  : 1表示译码模式是测试模式，此时译码模块不做帧类型判决 */
        unsigned char  gtc_enhanced_ut_en   : 1;  /* bit[1]  : 1表示是增强型译码的UT验证模式，测试用，默认值为0 */
        unsigned char  reserved             : 2;  /* bit[2-3]:  */
        unsigned char  gtc_reduce_page_mode : 4;  /* bit[4-7]: bit3~bit0，分别表示当前精简寻呼译码时有效的BURST是否存在，如0011标识第一个，第二个BURST存在，第三个第四个BURST译码数据补零。
                                                               1100标识第三个，第四个BURST存在，第一个第二个BURST译码数据补零。
                                                               默认值为0xF */
    } reg;
} GBBP_GTC_DEC_TEST_MODE_EN_UNION;
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_dec_test_mode_en_START  (0)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_dec_test_mode_en_END    (0)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_enhanced_ut_en_START    (1)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_enhanced_ut_en_END      (1)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_reduce_page_mode_START  (4)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_reduce_page_mode_END    (7)


/***======================================================================***
                     (7/9) register_define_gtc_gglb
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_GRIF_CTRL_UNION
 结构说明  : GTC_GRIF_CTRL 寄存器结构定义。地址偏移量:0xC2，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_grif_ctrl_reg;
    struct
    {
        unsigned char  reserved_0   : 1;  /* bit[0]  :  */
        unsigned char  gtc_rx_start : 1;  /* bit[1]  : GRIF模块接收启动信号，一个系统时钟周期宽度 */
        unsigned char  gtc_rx_stop  : 1;  /* bit[2]  : GRIF模块接收停止信号，一个系统时钟周期宽度.当gsp_rx_low_len和gsp_rx_high_len都配置为0时,表示连续接收,此时可以用gsp_rx_stop来停止接收.但是gsp_rx_stop在连续或按长度接收的模式下置1都会导致接收中止 */
        unsigned char  reserved_1   : 5;  /* bit[3-7]:  */
    } reg;
} GBBP_GTC_GRIF_CTRL_UNION;
#define GBBP_GTC_GRIF_CTRL_gtc_rx_start_START  (1)
#define GBBP_GTC_GRIF_CTRL_gtc_rx_start_END    (1)
#define GBBP_GTC_GRIF_CTRL_gtc_rx_stop_START   (2)
#define GBBP_GTC_GRIF_CTRL_gtc_rx_stop_END     (2)


/***======================================================================***
                     (8/9) register_define_gtc_gul
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_PA_CTRL_CFG_UNION
 结构说明  : GTC_PA_CTRL_CFG 寄存器结构定义。地址偏移量:0xA4，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_ctrl_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_start        : 1;  /* bit[0]  : GSP启动APC驱动，1个104M高脉冲（必需在frac_cnt=94处发出（GTC内部处理））可用该启动信号来配置APC输出RAMP DAC所需的控制字 */
        unsigned char  gtc_pa_stop         : 1;  /* bit[1]  : GSP停止APC爬坡驱动的信号。写1停止APC爬坡驱动，内部产生一个104M脉冲。可用该启动信号来配置APC输出RAMP DAC所需的控制字 */
        unsigned char  gtc_pa_single_start : 1;  /* bit[2]  : 单次APC驱动启动信号。写1启动目标功率电压值为gsp_pa_init的单次APC驱动，内部产生一个104M脉冲。（逻辑内部一次达到该目标功率电压值），可用该启动信号来配置APC输出TXAGC DAC所需的控制字 */
        unsigned char  gtc_pa_change       : 1;  /* bit[3]  : target重配置APC爬坡驱动启动信号。写1启动一次target重配置的APC爬坡驱动（应用于多时隙功率变化），内部产生一个104M脉冲（必需在frac_cnt=46处发出（GTC内部处理））。note：必须在爬坡16点结束后再启动此信号，具体参见下面描述的时序图。 */
        unsigned char  gtc_pa_dac_sel_pre  : 1;  /* bit[4]  : 上行ABB内部GAPC DAC控制选择信号。                1：TXAGC DAC；          0：RAMP DAC。             注：当前RF C02版本中，GMSK时配置为0表示爬坡；8psk时配置为1表示爬坡，0表示VBIAS。 */
        unsigned char  reserved            : 3;  /* bit[5-7]:  */
    } reg;
} GBBP_GTC_PA_CTRL_CFG_UNION;
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_start_START         (0)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_start_END           (0)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_stop_START          (1)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_stop_END            (1)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_single_start_START  (2)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_single_start_END    (2)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_change_START        (3)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_change_END          (3)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_dac_sel_pre_START   (4)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_dac_sel_pre_END     (4)


/*****************************************************************************
 结构名    : GBBP_GTC_PA_LEN_HIGH_CFG_UNION
 结构说明  : GTC_PA_LEN_HIGH_CFG 寄存器结构定义。地址偏移量:0xA6，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_len_high_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_len_high : 5;  /* bit[0-4]: APC爬坡驱动持续时间长度，具体指首次上爬坡到目标值gsp_pa_target时开始，到开始下爬坡到初始值的时刻这段时间（具体参见下面时序图该信号的含义）。单位Qb，默认值为4个burst长度。该信号配置的是高5bit */
        unsigned char  reserved        : 3;  /* bit[5-7]:  */
    } reg;
} GBBP_GTC_PA_LEN_HIGH_CFG_UNION;
#define GBBP_GTC_PA_LEN_HIGH_CFG_gtc_pa_len_high_START  (0)
#define GBBP_GTC_PA_LEN_HIGH_CFG_gtc_pa_len_high_END    (4)


/*****************************************************************************
 结构名    : GBBP_GTC_PA_TARGET_HIGH_CFG_UNION
 结构说明  : GTC_PA_TARGET_HIGH_CFG 寄存器结构定义。地址偏移量:0xA8，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_target_high_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_target_high : 2;  /* bit[0-1]: GSP配置APC目标电压值。该信号配置的是高2bit */
        unsigned char  reserved_0         : 3;  /* bit[2-4]:  */
        unsigned char  gtc_pa_coeff_index : 2;  /* bit[5-6]: 指示本次爬坡的爬坡系数索引号，确保在gsp_pa_start或者gsp_pa_change有效时,此值已经配置。本索引号取值范围是0～3。note：当有gsp_pa_change时，ramp-down的系数gsp_pa_coeff_index[1:0]由gsp_pa_change对应的系数索引号决定，而不是由gsp_pa_start对应的系数gsp_pa_coeff_index[1:0]决定。 */
        unsigned char  reserved_1         : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_PA_TARGET_HIGH_CFG_UNION;
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_target_high_START  (0)
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_target_high_END    (1)
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_coeff_index_START  (5)
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_coeff_index_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_PA_INIT_HIGH_CFG_UNION
 结构说明  : GTC_PA_INIT_HIGH_CFG 寄存器结构定义。地址偏移量:0xAA，初值:0x40，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_init_high_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_init_high : 2;  /* bit[0-1]: APC爬坡初始功率电压值。也可作为单次APC驱动的目标功率电压值。该信号配置的是高2bit */
        unsigned char  gtc_ramp_point   : 5;  /* bit[2-6]: 指示当前爬坡的点数，上坡和下坡点数相同。可配范围值：8～16。默认值为16。 */
        unsigned char  reserved         : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_PA_INIT_HIGH_CFG_UNION;
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_pa_init_high_START  (0)
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_pa_init_high_END    (1)
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_ramp_point_START    (2)
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_ramp_point_END      (6)


/*****************************************************************************
 结构名    : GBBP_GTC_MOD_START_POS_UNION
 结构说明  : GTC_MOD_START_POS 寄存器结构定义。地址偏移量:0xAC，初值:0x4D，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mod_start_pos_reg;
    struct
    {
        unsigned char  gtc_mod_start_pos          : 7;  /* bit[0-6]: bit6~0: 该信号表示gsp_mod_start需要在QB内产生位置信息(即是在QB内96拍哪一拍的位置产生)，位置信息配置为0~95(注意该值应该配置为位置减1的值,即是47~0~46),配置gsp_mod_start请先配置该信号(如果位置不变,可以不用配置).复位默认值为77; */
        unsigned char  gtc_mod_symbol_length_high : 1;  /* bit[7]  : 与gsp_mod_symbol_l_length[7:0]组成9bit的调制长度，该比特为最高位，gsp_mod_symbol_l_length[7:0]为低8bit。循环调制0，输出正弦波信号。只能使用gsp_mod_stop停止。 */
    } reg;
} GBBP_GTC_MOD_START_POS_UNION;
#define GBBP_GTC_MOD_START_POS_gtc_mod_start_pos_START           (0)
#define GBBP_GTC_MOD_START_POS_gtc_mod_start_pos_END             (6)
#define GBBP_GTC_MOD_START_POS_gtc_mod_symbol_length_high_START  (7)
#define GBBP_GTC_MOD_START_POS_gtc_mod_symbol_length_high_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_MOD_TYPE_UNION
 结构说明  : GTC_MOD_TYPE 寄存器结构定义。地址偏移量:0xAE，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mod_type_reg;
    struct
    {
        unsigned char  gtc_mod_type : 1;  /* bit[0]  : 调制类型：1表示8PSK，0表示GMSK。复位默认值为0，调制过程中，该参数应保持。HUASHAN版本请务必配置0 */
        unsigned char  reserved     : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_MOD_TYPE_UNION;
#define GBBP_GTC_MOD_TYPE_gtc_mod_type_START  (0)
#define GBBP_GTC_MOD_TYPE_gtc_mod_type_END    (0)


/*****************************************************************************
 结构名    : GBBP_GTC_MOD_CTRL_UNION
 结构说明  : GTC_MOD_CTRL 寄存器结构定义。地址偏移量:0xAF，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mod_ctrl_reg;
    struct
    {
        unsigned char  gtc_mod_start : 1;  /* bit[0]  : bit0: CPU配置GTC启动调制，一个脉冲，连续多时隙时，CPU仍需要每个时隙都启动一次，调制时，逻辑不关心是否是多时隙.建议在配置该指令之前，配置一条延时指令，保证在最后一个QB的前半段时间就开始解析gsp_mod_start指令，从而保证调制数据与下一个BURST的头位置对齐，GTC逻辑自清零。需要考虑预调制长度以及上行通道的延时 */
        unsigned char  gtc_mod_stop  : 1;  /* bit[1]  : bit1: CPU 配置GTC停止调制，一个脉冲。当gsp_mod_symbol_length=0时，循环调制指定位置，此时只能用gsp_mod_stop停止调制。,GTC逻辑自清零 */
        unsigned char  reserved      : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_GTC_MOD_CTRL_UNION;
#define GBBP_GTC_MOD_CTRL_gtc_mod_start_START  (0)
#define GBBP_GTC_MOD_CTRL_gtc_mod_start_END    (0)
#define GBBP_GTC_MOD_CTRL_gtc_mod_stop_START   (1)
#define GBBP_GTC_MOD_CTRL_gtc_mod_stop_END     (1)


/*****************************************************************************
 结构名    : GBBP_UL_CB1_INDEX_UNION
 结构说明  : UL_CB1_INDEX 寄存器结构定义。地址偏移量:0xD4，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      ul_cb1_index_reg;
    struct
    {
        unsigned char  gtc_ul_cb1_index : 7;  /* bit[0-6]: 上行业务索引号 */
        unsigned char  reserved         : 1;  /* bit[7]  :  */
    } reg;
} GBBP_UL_CB1_INDEX_UNION;
#define GBBP_UL_CB1_INDEX_gtc_ul_cb1_index_START  (0)
#define GBBP_UL_CB1_INDEX_gtc_ul_cb1_index_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_UL_CB_NUM_UNION
 结构说明  : GTC_UL_CB_NUM 寄存器结构定义。地址偏移量:0xD7，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_cb_num_reg;
    struct
    {
        unsigned char  reserved              : 4;  /* bit[0-3]:  */
        unsigned char  gtc_ul_cb_start_pos   : 2;  /* bit[4-5]: 上行待编码码块起始位置指示标志。                   00: 表示码块0的起始位置标志，                     01:表示码块1的起始位置标志，                    10: 表示码块2的起始位置标志。                    11: 表示码块3的起始位置标志。                     复位默认值为2’b00 */
        unsigned char  gtc_facch_stolen_flag : 2;  /* bit[6-7]: FACCH偷帧标志，           01: 表示当前编码之前启动了一次FACCH/H编码，交织时不能覆盖偷帧位置。         10: 表示当前编码之前启动了一次FACCH/F编码，交织时不能覆盖偷帧位置。      00/11：表示当前编码之前没有启动FACCH编码或者FACCH偷帧对当前编码没有影响，可以正常交织。              注：该标志仅仅针对22个BURST交织深度的数据业务（包括F9.6/F4.8/H4.8/H2.4/F14.4）下，需要配置，其它业务下无需配置；若FACCH与数据业务之间存在SACCH业务（单独存储）时，该偷帧标志在启动数据业务之前必须加以保持 */
    } reg;
} GBBP_GTC_UL_CB_NUM_UNION;
#define GBBP_GTC_UL_CB_NUM_gtc_ul_cb_start_pos_START    (4)
#define GBBP_GTC_UL_CB_NUM_gtc_ul_cb_start_pos_END      (5)
#define GBBP_GTC_UL_CB_NUM_gtc_facch_stolen_flag_START  (6)
#define GBBP_GTC_UL_CB_NUM_gtc_facch_stolen_flag_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_UL_PARA21_UNION
 结构说明  : GTC_UL_PARA21 寄存器结构定义。地址偏移量:0xD8，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_para21_reg;
    struct
    {
        unsigned char  gtc_ul_in_band_data_id0 : 2;  /* bit[0-1]: [1:0]：表示带内比特id0信息00:CODEC_MODE_1，01:CODEC_MODE_2，10:CODEC_MODE_3，11:CODEC_MODE_4，     */
        unsigned char  gtc_ul_in_band_data_id1 : 2;  /* bit[2-3]: [3:2]：表示带内比特id1信息，       00:CODEC_MODE_1，01:CODEC_MODE_2，10:CODEC_MODE_3，11:CODEC_MODE_4，        复位默认值为4'b0000，如果协议中没有标明id0,id1,采用的是id标注，那么该id值配置在id0上，即此时是低2bit有效，如果是以标明是id1,那么就配置在id1，此时高2bit有效。 */
        unsigned char  gtc_punc_index1         : 2;  /* bit[4-5]: [5:4]表示DATA1（DATA）的打孔方式；                00：无，                   01：P1，                 10：P2，                11：P3，                 复位默认值为4’b0000。 */
        unsigned char  gtc_punc_index2         : 2;  /* bit[6-7]: [7:6]表示DATA2的打孔方
                                                                  00：无
                                                                  01：P1
                                                                  10：P2
                                                                  11：P3
                                                                  复位默认值为4’b0000 */
    } reg;
} GBBP_GTC_UL_PARA21_UNION;
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id0_START  (0)
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id0_END    (1)
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id1_START  (2)
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id1_END    (3)
#define GBBP_GTC_UL_PARA21_gtc_punc_index1_START          (4)
#define GBBP_GTC_UL_PARA21_gtc_punc_index1_END            (5)
#define GBBP_GTC_UL_PARA21_gtc_punc_index2_START          (6)
#define GBBP_GTC_UL_PARA21_gtc_punc_index2_END            (7)


/*****************************************************************************
 结构名    : GBBP_GTC_RACH_BSIC_UNION
 结构说明  : GTC_RACH_BSIC 寄存器结构定义。地址偏移量:0xD9，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_rach_bsic_reg;
    struct
    {
        unsigned char  gtc_rach_bsic_data : 6;  /* bit[0-5]: RACH业务中BS（基站）的BSIC比特，复位默认值为6’b000000，注：BSIC的MSB在bit0,LSB在bit5。 */
        unsigned char  reserved           : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_RACH_BSIC_UNION;
#define GBBP_GTC_RACH_BSIC_gtc_rach_bsic_data_START  (0)
#define GBBP_GTC_RACH_BSIC_gtc_rach_bsic_data_END    (5)


/*****************************************************************************
 结构名    : GBBP_GTC_COD_BURST_POS_UNION
 结构说明  : GTC_COD_BURST_POS 寄存器结构定义。地址偏移量:0xDA，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_cod_burst_pos_reg;
    struct
    {
        unsigned char  gtc_cod_burst_pos : 7;  /* bit[0-6]: 表示当前编码数据第一个BURST在编码存储RAM（ram611x16s）中的位置编号:复位默认值为7’d0。   参考配置如下：0，12，24，36：                      PS域业务：对应于第一个码块，配置为0，此时map后的4个burst依次存放在首地址为0，3，6，9的ram中（为后续的gsp_ map_burst_pos所用）；                   第二个码块配置为12，map后的4个burst依次存放于12，15，18，21；             第三个码块配置为24，map后的4个burst依次存放于24，27，30，33；             第四个码块配置为36，map后的4个burst依次存放于36，39，42，45；36 ～ 59： CS域业务，64 ～ 67： SACCH，68 ～ 71： PTCCH，72 ～ 75：其他控制信道，76      ： RACH，                特别注意：如果是半速率业务，假设当前编码启动时配置位置为a，启动一次FACCH/H编码，需要放弃2个SPEECH的编码，所以下次直接是a+4位置。 */
        unsigned char  reserved          : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_COD_BURST_POS_UNION;
#define GBBP_GTC_COD_BURST_POS_gtc_cod_burst_pos_START  (0)
#define GBBP_GTC_COD_BURST_POS_gtc_cod_burst_pos_END    (6)


/*****************************************************************************
 结构名    : GBBP_GTC_UL_BURST_CYCLE_UNION
 结构说明  : GTC_UL_BURST_CYCLE 寄存器结构定义。地址偏移量:0xDB，初值:0x18，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_burst_cycle_reg;
    struct
    {
        unsigned char  gtc_ul_burst_sav_cycle : 6;  /* bit[0-5]: 上行编码存放BURST循环周期（该参数只对CS域业务有效，即是CS域业务映射的复帧周期）.复位默认值为24。 */
        unsigned char  reserved               : 1;  /* bit[6]  :  */
        unsigned char  gtc_ul_cod_en          : 1;  /* bit[7]  : 上行编码过程的使能信号。 复位默认值为0 */
    } reg;
} GBBP_GTC_UL_BURST_CYCLE_UNION;
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_burst_sav_cycle_START  (0)
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_burst_sav_cycle_END    (5)
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_cod_en_START           (7)
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_cod_en_END             (7)


/*****************************************************************************
 结构名    : GBBP_GTC_UL_COD_START_UNION
 结构说明  : GTC_UL_COD_START 寄存器结构定义。地址偏移量:0xDC，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_cod_start_reg;
    struct
    {
        unsigned char  gtc_ul_cod_start : 1;  /* bit[0]  : 上行编码启动信号，脉冲信号,GTC逻辑自清零 */
        unsigned char  reserved         : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_UL_COD_START_UNION;
#define GBBP_GTC_UL_COD_START_gtc_ul_cod_start_START  (0)
#define GBBP_GTC_UL_COD_START_gtc_ul_cod_start_END    (0)


/*****************************************************************************
 结构名    : GBBP_GTC_UL_MAP_PARA_UNION
 结构说明  : GTC_UL_MAP_PARA 寄存器结构定义。地址偏移量:0xDD，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_map_para_reg;
    struct
    {
        unsigned char  gtc_ul_mod_type        : 1;  /* bit[0]  : 调制类型标志：0表示GMSK调制，1表示8PSK调制。复位默认值为0，HUASHAN版本请务必配置为0。 */
        unsigned char  gtc_ul_burst_type      : 1;  /* bit[1]  : BURST类型标志：1表示NB，0表示AB，复位默认值为0。 */
        unsigned char  gtc_ul_tsc_group_num   : 4;  /* bit[2-5]: 上行NB子集1训练序列组号0000：子集1第0组训练序列0001：子集1第1组训练序列0010：子集1第2组训练序列0011：子集1第3组训练序列0100：子集1第4组训练序列0101：子集1第5组训练序列0110：子集1第6组训练序列0111：子集1第7组训练序列上行NB子集2训练序列组号1000：子集2第0组训练序列1001：子集2第1组训练序列1010：子集2第2组训练序列1011：子集2第3组训练序列1100：子集2第4组训练序列1101：子集2第5组训练序列1110：子集2第6组训练序列1111：子集2第7组训练序列AB复用上面的配置，但是只有0000，0001，0010配置有效复位默认值为4’b0000 */
        unsigned char  gtc_demod_loop_mode_en : 1;  /* bit[6]  : 1表示是下行解调环回测试模式，0表示是正常的上行调制和下行解调工作模式
                                                                 该信号由软件针对下行解调环回测试灵活配置，在译码环回测试模式该值应该配置为0,即译码数据通过软件配置到上行编码实现环回 */
        unsigned char  gtc_cpu_wrte_mod_pre   : 1;  /* bit[7]  : 1 表示由CPU来控制调制前RAM数据的写入。0 表示有上行编码来控制调制前RAM数据的写入。复位默认值为0 */
    } reg;
} GBBP_GTC_UL_MAP_PARA_UNION;
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_mod_type_START          (0)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_mod_type_END            (0)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_burst_type_START        (1)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_burst_type_END          (1)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_tsc_group_num_START     (2)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_tsc_group_num_END       (5)
#define GBBP_GTC_DEC_MAP_PARA_gtc_demod_loop_mode_en_START  (6)
#define GBBP_GTC_DEC_MAP_PARA_gtc_demod_loop_mode_en_END    (6)
#define GBBP_GTC_UL_MAP_PARA_gtc_cpu_wrte_mod_pre_START     (7)
#define GBBP_GTC_UL_MAP_PARA_gtc_cpu_wrte_mod_pre_END       (7)


/*****************************************************************************
 结构名    : GBBP_GTC_MAP_BURST_POS_UNION
 结构说明  : GTC_MAP_BURST_POS 寄存器结构定义。地址偏移量:0xDE，初值:0x80，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_map_burst_pos_reg;
    struct
    {
        unsigned char  gtc_map_burst_pos     : 7;  /* bit[0-6]: 需要送去成BURST的数据存储位置指示（可选集为编码RAM中每个BURST存储的起始地址，参考gsp_ul_cod_burst_pos[6:0]的位置编号方式，所不同的是：该信号下发的是当前准备调制的BURST位置编号，而不是整个编码码块起始BURST的位置编号。）
                                                                默认值为0 */
        unsigned char  gtc_map_ram_switch_en : 1;  /* bit[7]  : 1表示使能MAP后RAM(调制模块数据输入RAM)乒乓切换使能，0表示调制模块固定读乒RAM(此时CPU写待调制数据RAM也只能写入乒RAM)。复位默认值为1 */
    } reg;
} GBBP_GTC_MAP_BURST_POS_UNION;
#define GBBP_GTC_MAP_BURST_POS_gtc_map_burst_pos_START      (0)
#define GBBP_GTC_MAP_BURST_POS_gtc_map_burst_pos_END        (6)
#define GBBP_GTC_MAP_BURST_POS_gtc_map_ram_switch_en_START  (7)
#define GBBP_GTC_MAP_BURST_POS_gtc_map_ram_switch_en_END    (7)


/*****************************************************************************
 结构名    : GBBP_GTC_MAP_START_UNION
 结构说明  : GTC_MAP_START 寄存器结构定义。地址偏移量:0xDF，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_map_start_reg;
    struct
    {
        unsigned char  gtc_ul_map_start : 1;  /* bit[0]  : 成BURST映射启动信号，高电平脉冲信号（提前调制启动信号6.25个Symble）,GTC逻辑自清零 */
        unsigned char  reserved         : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_MAP_START_UNION;
#define GBBP_GTC_MAP_START_gtc_ul_map_start_START  (0)
#define GBBP_GTC_MAP_START_gtc_ul_map_start_END    (0)


/*****************************************************************************
 结构名    : GBBP_GTC_ULMOD_TEST_MOD_HIGH_UNION
 结构说明  : GTC_ULMOD_TEST_MOD_HIGH 寄存器结构定义。地址偏移量:0xE6，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ulmod_test_mod_high_reg;
    struct
    {
        unsigned char  gtc_ulmod_test_mod_high : 4;  /* bit[0-3]: bit[3:0]:预调制长度，0表示不进行预调制，默认值为4，调制过程中，该参数应保持 */
        unsigned char  reserved                : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_ULMOD_TEST_MOD_HIGH_UNION;
#define GBBP_GTC_ULMOD_TEST_MOD_HIGH_gtc_ulmod_test_mod_high_START  (0)
#define GBBP_GTC_ULMOD_TEST_MOD_HIGH_gtc_ulmod_test_mod_high_END    (3)


/*****************************************************************************
 结构名    : GBBP_GTC_HD35_CAL_UNION
 结构说明  : GTC_HD35_CAL 寄存器结构定义。地址偏移量:0xFA，初值:0x80，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_hd35_cal_reg;
    struct
    {
        unsigned char  gtc_hd35_cal_en         : 1;  /* bit[0]  : 去3、5次谐波模块运算使能，GTC配置。在调制启动前配置。 */
        unsigned char  gtc_hd35_cal_sel        : 2;  /* bit[1-2]: 去3、5次谐波模块运算使用参数选择信号，GTC配置。为了确保校准参数及时生效，在gsp_mod_start之前配置此选择信号生效。 */
        unsigned char  gtc_hd35_data_iq_bypass : 1;  /* bit[3]  : IQ数据旁路指示；1表示IQ数据旁路，只输出HD3/HD5计算结果。GTC配置。如果需要旁路HD35功能，则需要配置cpu_hd35_cal_bypass。 */
        unsigned char  reserved                : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_HD35_CAL_UNION;
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_en_START          (0)
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_en_END            (0)
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_sel_START         (1)
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_sel_END           (2)
#define GBBP_GTC_HD35_CAL_gtc_hd35_data_iq_bypass_START  (3)
#define GBBP_GTC_HD35_CAL_gtc_hd35_data_iq_bypass_END    (3)


/***======================================================================***
                     (9/9) register_define_gtc_timing
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_TIMING_SLOT_HIGH_UNION
 结构说明  : TIMING_SLOT_HIGH 寄存器结构定义。地址偏移量:0xBF，初值:0x00，宽度:8
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned char      timing_slot_high_reg;
    struct
    {
        unsigned char  tdma_slot_int_offset_high : 2;  /* bit[0-1]:  */
        unsigned char  reserved                  : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_TIMING_SLOT_HIGH_UNION;
#define GBBP_TIMING_SLOT_HIGH_tdma_slot_int_offset_high_START  (0)
#define GBBP_TIMING_SLOT_HIGH_tdma_slot_int_offset_high_END    (1)




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

#endif /* end of bbp_gsm_gtc_interface.h */
