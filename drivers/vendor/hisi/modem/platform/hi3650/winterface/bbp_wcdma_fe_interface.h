/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_wcdma_fe_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-10-28 20:53:44
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月28日
    作    者   : l00165286
    修改内容   : 从《K3V5 MODEM寄存器手册_FE.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_WCDMA_FE_INTERFACE_H__
#define __BBP_WCDMA_FE_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/10) register_define_wt_dlfe
 ***======================================================================***/
/* 寄存器说明：
 bit[31:24]  五档AAGC状态跳转S4->S5的RSSI门限。
             C模不配置。
 bit[23:16]  五档AAGC状态跳转S3->S4的RSSI门限。
             C模不配置。
 bit[15:8]   五档AAGC状态跳转S2->S3的RSSI门限。
             C模不配置。
 bit[7:0]    五档AAGC状态跳转S1->S2的RSSI门限，单位dBm，配置二进制补码值。
             说明：按照S1->S2->S3->S4->S5的顺序，天线口的RSSI递增，AAGC的增益递减。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_5S_INC_TH_UNION */
#define WBBP_AAGC_RSSI_5S_INC_TH_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91200)

/* 寄存器说明：
 bit[31:24]  五档AAGC状态跳转S5->S4的RSSI门限。
             C模不配置。
 bit[23:16]  五档AAGC状态跳转S4->S3的RSSI门限。
             C模不配置。
 bit[15:8]   五档AAGC状态跳转S3->S2的RSSI门限。
             C模不配置。
 bit[7:0]    五档AAGC状态跳转S2->S1的RSSI门限，单位dBm，配置二进制补码值。
             说明：按照S5->S4->S3->S2->S1的顺序，天线口的RSSI递减，AAGC的增益递增。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_5S_DEC_TH_UNION */
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91204)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S1（RF RSSI为-102~-90dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S1_5S_RF_CTRL_AT1_UNION */
#define WBBP_S1_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91208)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S2（RF RSSI为-87~-69dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S2_5S_RF_CTRL_AT1_UNION */
#define WBBP_S2_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9120C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S3（RF RSSI为-66~-54dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S3_5S_RF_CTRL_AT1_UNION */
#define WBBP_S3_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91210)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S4（RF RSSI为-51~-39dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S4_5S_RF_CTRL_AT1_UNION */
#define WBBP_S4_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91214)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S5（RF RSSI为-36~-21dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S5_5S_RF_CTRL_AT1_UNION */
#define WBBP_S5_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9121C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S1（RF RSSI为-102~-90dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S1_5S_RF_CTRL_AT2_UNION */
#define WBBP_S1_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91220)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S2（RF RSSI为-87~-69dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S2_5S_RF_CTRL_AT2_UNION */
#define WBBP_S2_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91224)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S3（RF RSSI为-66~-54dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S3_5S_RF_CTRL_AT2_UNION */
#define WBBP_S3_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91228)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S4（RF RSSI为-51~-39dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S4_5S_RF_CTRL_AT2_UNION */
#define WBBP_S4_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9122C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S5（RF RSSI为-36~-21dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S5_5S_RF_CTRL_AT2_UNION */
#define WBBP_S5_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91230)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29]     DSP控制天线1 DCR启停使能。1，DSP打开DCR；0，DSP关闭DCR，IQ数据直通。
 bit[28]     DSP配置的天线1直流偏置消除模块反馈值选择信号。1，选择dc_offset；0，选择计算获得的反馈值。
 bit[27:16]  天线1接收Q路直流偏置值。
 bit[15:12]  保留
 bit[11:0]   天线1接收I路直流偏置值。
   UNION结构:  WBBP_DC_OFFSET_AT1_UNION */
#define WBBP_DC_OFFSET_AT1_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91234)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29]     DSP控制天线2 DCR启停使能。1，DSP打开DCR；0，DSP关闭DCR，IQ数据直通。
 bit[28]     DSP配置的天线2直流偏置消除模块反馈值选择信号。1，选择dc_offset；0，选择计算获得的反馈值。
 bit[27:16]  天线2接收Q路直流偏置值。
 bit[15:12]  保留
 bit[11:0]   天线2接收I路直流偏置值。
   UNION结构:  WBBP_DC_OFFSET_AT2_UNION */
#define WBBP_DC_OFFSET_AT2_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91238)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     0，档位调整时，DC从0开始重新收敛；1，档位调整时，DC继承先前计算值。
 bit[27:26]  DSP配置天线1异频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。
 bit[25:24]  DSP配置天线1异频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。
 bit[23:18]  保留
 bit[17:16]  DCR算法选择。
             00，表示使用与V2相同的算法；
             01，表示使用V3R1算法；
             11，表示使用V3R2算法。
             1X仅支持V3R2算法；EVDO默认配置为V3R2算法，支持配置为V3R1算法。
 bit[15:12]  保留
 bit[11:8]   增益调整后第一阶段的时间，单位256chip。
             1X下为1536chip，故需配置0x6；EVDO下为2048chip，故需配置为0x8。
 bit[7:6]    保留
 bit[5:4]    增益调整后，不进行DCR计算的时间选择。
             W下：0，表示16chip；1，表示24chip；2，表示32chip；3，表示8chip。
             1X下：0，表示0chip；1，表示8chip。
             1X默认为8chip；EVDO默认24chip。
 bit[3:2]    DSP配置天线1本频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。
 bit[1:0]    DSP配置天线1本频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。
   UNION结构:  WBBP_DC_OFFSET_SHIFT_AT1_UNION */
#define WBBP_DC_OFFSET_SHIFT_AT1_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9123C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     0，档位调整时，DC从0开始重新收敛；1，档位调整时，DC继承先前计算值。
 bit[27:26]  DSP配置天线2异频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。
 bit[25:24]  DSP配置天线2异频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。
 bit[23:18]  保留
 bit[17:16]  DCR算法选择。
             00，表示使用与V2相同的算法；
             01，表示使用V3R1算法；
             11，表示使用V3R2算法。
             1X仅支持V3R2算法；EVDO默认配置为V3R2算法，支持配置为V3R1算法。
 bit[15:12]  保留
 bit[11:8]   增益调整后第一阶段的时间，单位256chip。
             1X下为1536chip，故需配置0x6；EVDO下为2048chip，故需配置为0x8。
 bit[7:6]    保留
 bit[5:4]    增益调整后，不进行DCR计算的时间选择。
             W下：0，表示16chip；1，表示24chip；2，表示32chip；3，表示8chip。
             1X下：0，表示0chip；1，表示8chip。
             1X默认为8chip；EVDO默认24chip。
 bit[3:2]    DSP配置天线2本频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。
 bit[1:0]    DSP配置天线2本频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。
   UNION结构:  WBBP_DC_OFFSET_SHIFT_AT2_UNION */
#define WBBP_DC_OFFSET_SHIFT_AT2_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91240)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6:4]    AAGC统计能量滤波系数。0，表示1；1，表示1/2；2，表示1/4；3，表示1/8；4，表示1/16；5，表示1/32；6，表示1/64。
             C模不配置。
 bit[3]      保留
 bit[2:0]    DAGC统计能量滤波系数。0，表示1；1，表示1/2；2，表示1/4；3，表示1/8；4，表示1/16；5，表示1/32；6，表示1/64。
             C模不配置。
   UNION结构:  WBBP_WAGC_FILTER_CFG_UNION */
#define WBBP_WAGC_FILTER_CFG_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91264)

/* 寄存器说明：
 bit[31:16]  天线2一帧内DAGC IQ数据饱和次数。
             1X和EVDO为150个256chip的时间。
 bit[15:0]   天线1一帧内DAGC IQ数据饱和次数。
             1X和EVDO为150个256chip的时间。
   UNION结构:  WBBP_WAGC_SAT_NUM_UNION */
#define WBBP_WAGC_SAT_NUM_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91268)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:12]  W模AGC增益调整射频反馈预留时间选择。0，预留32chip；1，预留48chip；2，预留64chip。
             1X和EVDO是固定值，无需配置。
 bit[11:8]   保留
 bit[7:6]    异频DAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
             1X和EVDO是固定值，无需配置。
 bit[5:4]    异频AAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
             1X和EVDO是固定值，无需配置。
 bit[3:2]    本频DAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
             1X和EVDO是固定值，无需配置。
 bit[1:0]    本频AAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
             1X和EVDO是固定值，无需配置。
   UNION结构:  WBBP_WAGC_MODE_UNION */
#define WBBP_WAGC_MODE_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9126C)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    纠偏后4bitDAGC统计能量滤波系数。0，表示1，不滤波；1，表示1/2；2，表示1/4；3，表示1/8；4，表示1/16；5，表示1/32。
             C模不配置。
   UNION结构:  WBBP_DAGC_4BIT_FILTER_CFG_UNION */
#define WBBP_DAGC_4BIT_FILTER_CFG_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x91270)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     新DCR算法天线1第一阶段指示。
             1，第一阶段；0，第二阶段。
 bit[27:16]  天线1当前Q路输入直流结果值上报，测试用。
 bit[15:12]  保留
 bit[11:0]   天线1当前I路输入直流结果值上报，测试用。
   UNION结构:  WBBP_WAGC_DCR_RPT_AT1_UNION */
#define WBBP_WAGC_DCR_RPT_AT1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91274)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     新DCR算法天线2第一阶段指示。
             1，第一阶段；0，第二阶段。
 bit[27:16]  天线2当前Q路输入直流结果值上报，测试用。
 bit[15:12]  保留
 bit[11:0]   天线2当前I路输入直流结果值上报，测试用。
   UNION结构:  WBBP_WAGC_DCR_RPT_AT2_UNION */
#define WBBP_WAGC_DCR_RPT_AT2_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91278)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      天线1 IQ Mismatch使能，高电平有效。
 bit[7:1]    保留
 bit[0]      天线1 IQ Mismatch纠正系数选择。0，表示使用IQ Mismatch自己产生；1，表示使用DSP配置值。
   UNION结构:  WBBP_IQ_AK_PK_SEL_ANT1_UNION */
#define WBBP_IQ_AK_PK_SEL_ANT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9127C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  DSP配置的天线1 IQ Mismatch纠正系数Pk。
 bit[15:10]  保留
 bit[9:0]    DSP配置的天线1 IQ Mismatch纠正系数Ak。
   UNION结构:  WBBP_IQ_AK_PK_ANT1_UNION */
#define WBBP_IQ_AK_PK_ANT1_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91280)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      天线2 IQ Mismatch使能，高电平有效。
 bit[7:1]    保留
 bit[0]      天线2 IQ Mismatch纠正系数选择。0，表示使用IQ Mismatch自己产生；1，表示使用DSP配置值。
   UNION结构:  WBBP_IQ_AK_PK_SEL_ANT2_UNION */
#define WBBP_IQ_AK_PK_SEL_ANT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91294)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  DSP配置的天线2 IQ Mismatch纠正系数Pk。
 bit[15:10]  保留
 bit[9:0]    DSP配置的天线2 IQ Mismatch纠正系数Ak。
   UNION结构:  WBBP_IQ_AK_PK_ANT2_UNION */
#define WBBP_IQ_AK_PK_ANT2_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91298)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   天线1档位上报。连续存储10个DRSSI统计周期的档位值，每个档位占3比特，最新的档位放在低3比特。
   UNION结构:  WBBP_AGC_RPT_AT1_UNION */
#define WBBP_AGC_RPT_AT1_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9129C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   天线2档位上报。连续存储10个DRSSI统计周期的档位值，每个档位占3比特，最新的档位放在低3比特。
   UNION结构:  WBBP_AGC_RPT_AT2_UNION */
#define WBBP_AGC_RPT_AT2_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x912A0)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    IQ Mismatch模块预留给RF增益的调整时间。
             W下：0，预留24chip，对应AAGC的32chip；1，预留40chip，对应AAGC的48chip；2，预留56chip，对应AAGC的64chip。
             1X下：0，预留8chip；1，预留16chip；2，预留24chip。
             EVDO下：固定，无需配置。
   UNION结构:  WBBP_IQ_MIS_ADJUST_MODE_UNION */
#define WBBP_IQ_MIS_ADJUST_MODE_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x912AC)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    IQ Mismatch计算周期，需要与AAGC的调整周期一致。0，表示一个单位；1，表示W的一个时隙，或者1X的一个PCG；2，表示2个单位；3，表示4个单位。4，表示6个单位。
             1X：默认值为1。
             EVDO：上述选项无效，为一个时隙的固定值，不需要配置。
             注：单位为256chip。
   UNION结构:  WBBP_IQ_MIS_MODE_UNION */
#define WBBP_IQ_MIS_MODE_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x912B4)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      辅天线采数使，高电平有效。
 bit[8]      主天线采数使能，高电平有效。
 bit[7:5]    保留
 bit[4:0]    基带数据搬运选择，表示采数位置。
             0，ADC输出信号，数据位宽14bit，W和TDS都用；
             1，spmv输输出信号，W和TDS都用；
             2，dcoc输出信号，W和TDS使用；
             3，dgt1输出信号，仅TDS使用；
             4，fir输出信号，仅TDS使用；
             5，rxiq输出信号，W和TDS都用；
             6，dwf的主载波输出信号，W和TDS都用；
             7，主载波fifo输出信号，仅W使用；
             8，主载波sc_filter输出信号，W和TDS都使用；
             9，TDS的rrc输出信号，仅TDS使用；
             10，TDS的dgt2输出信号，仅TDS使用；
             11，W的rrc输出信号，主载波和辅载波分时复用；
             12，W的8bitDAGC输出信号，主载波和辅载波分时复用；
             13，W的4bitDAGC输出信号，主载波和辅载波分时复用；
             14，辅载波dwf输出信号，仅W使用；
             16，辅载波sc_filter输出信号，仅W使用；
             17，幅度为2047的三角波，对应12bits数据；
             18，幅度为127的三角波，对应8bit数据；
             19，频率校正freq_error输出信号，仅W使用；
             20，主载波FIFO输出信号，仅W使用；
             搬运数据格式：
             0：[13:0]为数据；[14]数据符号位；[15]为0表示天线1，为1表示天线2。
             1~20：[11:0]为数据；[12]为0表示主载波，为1表示辅载波，不区分主辅载波的该位为数据符号位；[13]为0表示天线1，为1表示天线2。
   UNION结构:  WBBP_DBG_AGC_DATA_SEL_UNION */
#define WBBP_DBG_AGC_DATA_SEL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x912DC)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:12]  模式选择。0表示W；1表示TDS；2表示cdma 1X；3表示cdma EVDO。
 bit[11:10]  保留
 bit[9]      分集软复位。1表示进入复位状态；0表示退出软复位状态。
             软复位和天线使能配置约束：复位前先关闭本寄存器bit[1]天线使能，然后进行软复位，撤销复位后再打开本寄存器bit[1]天线使能。并且天线使能关闭时间要大于2个符号。
 bit[8]      主集软复位。1表示进入复位状态；0表示退出软复位状态。
             软复位和天线使能配置约束：复位前先关闭本寄存器bit[0]天线使能，然后进行软复位，撤销复位后再打开本寄存器bit[0]天线使能。并且天线使能关闭时间要大于2个符号。
 bit[7]      保留
 bit[6]      0表示IQ Mismatch计算跟AGC内部定时器对齐；1表示IQ Mismatch计算跟DPA时隙头对齐。
             由于不支持DPA模式，请固定使用默认值，不能改配。
             C模不配置。
 bit[5]      0表示RSSI计算和AGC档位调整跟AGC内部定时器对齐；1表示RSSI计算和AGC档位调整跟DPA时隙头对齐。
             由于不支持DPA模式，请固定使用默认值，不能改配。
             C模不配置。
 bit[4]      0表示BLOCK检测和ABB BLOCK控制模块跟AGC内部定时器对齐；1表示BLOCK检测和ABB BLOCK控制模块跟DPA时隙头对齐。
             由于不支持DPA模式，请固定使用默认值，不能改配。
             C模不配置。
 bit[3:2]    0，主辅天线打开按符号同步；1，主辅天线打开按1/4chip同步；2，主辅天线打开按时隙同步。
             C模不配置。
 bit[1]      天线2前端开关。1，表示打开；0，表示关闭。W、TDS和C共用。
 bit[0]      天线1前端开关。1，表示打开；0，表示关闭。W、TDS和C共用。
   UNION结构:  WBBP_WAGC_SWITCH_UNION */
#define WBBP_WAGC_SWITCH_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91400)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:24]  刚刚打开AGC时，BBP使用此值进行自研RF八档增益控制。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
 bit[23]     保留
 bit[22:20]  刚刚打开AGC时，BBP使用此值进行自研RF五档增益控制。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
 bit[19:9]   刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
 bit[8:0]    刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
   UNION结构:  WBBP_INIT_AGC_CFG_AT1_UNION */
#define WBBP_INIT_AGC_CFG_AT1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91404)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:24]  刚刚打开AGC时，BBP使用此值进行自研RF八档增益控制。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
 bit[23]     保留
 bit[22:20]  刚刚打开AGC时，BBP使用此值进行自研RF五档增益控制。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
 bit[19:9]   刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
 bit[8:0]    刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
             C模不配置。
   UNION结构:  WBBP_INIT_AGC_CFG_AT2_UNION */
#define WBBP_INIT_AGC_CFG_AT2_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91408)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:24]  刚刚进入异频GAP时，BBP使用此值进行自研RF八档增益控制。
             C模不配置。
 bit[23]     保留
 bit[22:20]  刚刚进入异频GAP时，BBP使用此值进行自研RF五档增益控制。
             C模不配置。
 bit[19:9]   刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
             C模不配置。
 bit[8:0]    刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。
             C模不配置。
   UNION结构:  WBBP_INTER_AGC_CFG_AT1_UNION */
#define WBBP_INTER_AGC_CFG_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9140C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:24]  刚刚进入异频GAP时，BBP使用此值进行自研RF八档增益控制。
             C模不配置。
 bit[23]     保留
 bit[22:20]  刚刚进入异频GAP时，BBP使用此值进行自研RF五档增益控制。
             C模不配置。
 bit[19:9]   刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
             C模不配置。
 bit[8:0]    刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。
             C模不配置。
   UNION结构:  WBBP_INTER_AGC_CFG_AT2_UNION */
#define WBBP_INTER_AGC_CFG_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91410)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:20]  BBP上报用于控制RF增益的状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[19:9]   BBP上报天线口RSSI值（双载波之和），0.125dB精度。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[8:0]    BBP上报0.25dB精度的DRSSI值（双载波之和），BBP使用此值查表DAGC ROM。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
   UNION结构:  WBBP_INIT_AGC_RPT_AT1_UNION */
#define WBBP_INIT_AGC_RPT_AT1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91414)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:20]  BBP上报用于控制RF增益的状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[19:9]   BBP上报天线口RSSI值（双载波之和），0.125dB精度。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[8:0]    BBP上报0.25dB精度的DRSSI值（双载波之和），BBP使用此值查表DAGC ROM。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
   UNION结构:  WBBP_INIT_AGC_RPT_AT2_UNION */
#define WBBP_INIT_AGC_RPT_AT2_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91418)

/* 寄存器说明：
 bit[31:24]  八档AAGC状态跳转S4->S5的RSSI门限。
             C模不配置。
 bit[23:16]  八档AAGC状态跳转S3->S4的RSSI门限。
             C模不配置。
 bit[15:8]   八档AAGC状态跳转S2->S3的RSSI门限。
             C模不配置。
 bit[7:0]    八档AAGC状态跳转S1->S2的RSSI门限，单位dBm，配置二进制补码值。
             说明：按照S1->S2->S3->S4->S5的顺序，天线口的RSSI递增，AAGC的增益递减。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_8S_INC_TH_UNION */
#define WBBP_AAGC_RSSI_8S_INC_TH_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9141C)

/* 寄存器说明：
 bit[31:24]  八档AAGC状态跳转S5->S4的RSSI门限。
             C模不配置。
 bit[23:16]  八档AAGC状态跳转S4->S3的RSSI门限。
             C模不配置。
 bit[15:8]   八档AAGC状态跳转S3->S2的RSSI门限。
             C模不配置。
 bit[7:0]    八档AAGC状态跳转S2->S1的RSSI门限，单位dBm，配置二进制补码值。
             说明：按照S5->S4->S3->S2->S1的顺序，天线口的RSSI递减，AAGC的增益递增。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_8S_DEC_TH_UNION */
#define WBBP_AAGC_RSSI_8S_DEC_TH_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91420)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S12_INTRA_AT1_UNION */
#define WBBP_RF_8S_GAIN_S12_INTRA_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91424)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S34_INTRA_AT1_UNION */
#define WBBP_RF_8S_GAIN_S34_INTRA_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91428)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S1（RF RSSI为-102~-90dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S1_8S_RF_CTRL_AT1_UNION */
#define WBBP_S1_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9142C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S2（RF RSSI为-87~-69dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S2_8S_RF_CTRL_AT1_UNION */
#define WBBP_S2_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91430)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S3（RF RSSI为-66~-54dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S3_8S_RF_CTRL_AT1_UNION */
#define WBBP_S3_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91434)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S4（RF RSSI为-51~-39dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S4_8S_RF_CTRL_AT1_UNION */
#define WBBP_S4_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91438)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S5（RF RSSI为-36~-21dBm）状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S5_8S_RF_CTRL_AT1_UNION */
#define WBBP_S5_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9143C)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25]     静态DC异频通道选择。1表示天线1和天线2交换。
             C模不配置。
 bit[24]     静态DC本频通道选择。1表示天线1和天线2交换。
             C模不配置。
 bit[23]     rfctrl异频通道选择。1表示天线1和天线2交换。
             C模不配置。
 bit[22]     rfctrl本频通道选择。1表示天线1和天线2交换。
             C模不配置。
 bit[21]     rfgain异频通道选择。1表示天线1和天线2交换。
             C模不配置。
 bit[20]     rfgain本频通道选择。1表示天线1和天线2交换。
             C模不配置。
 bit[19:15]  保留
 bit[14:8]   天线2 Gainfix与Gaindig增益之和，即前端通道中比较固定部分的增益，单位dB。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
 bit[7]      保留
 bit[6:0]    天线1 Gainfix与Gaindig增益之和，即前端通道中比较固定部分的增益，单位dB。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
   UNION结构:  WBBP_CHANNEL_FIX_DIG_GAIN_UNION */
#define WBBP_CHANNEL_FIX_DIG_GAIN_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x91440)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6:4]    DSP控制AAGC状态机。0，表示S1，即AAGC增益为s1_rf_gain；1，表示S2，即AAGC增益为s2_rf_gain；2，表示S3，即AAGC增益为s3_rf_gain；3，表示S4，即AAGC增益为s4_rf_gain；4，表示S5，即AAGC增益为s5_rf_gain；5，表示S6，即AAGC增益为s6_rf_gain；6，表示S7，即AAGC增益为s7_rf_gain；7，表示S8，即AAGC增益为s8_rf_gain。
             C模不配置。
 bit[3:1]    保留
 bit[0]      DSP控制AAGC增益使能。0，表示BBP控制AAGC增益；1，表示DSP控制AAGC增益。
             C模不配置。
   UNION结构:  WBBP_AAGC_CTRL_TEST_UNION */
#define WBBP_AAGC_CTRL_TEST_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91444)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  Block检测检测到干扰时，自研RF -60dBm增益档的RSSI加上此值后，确定增益档位。有符号数，单位dB。
             C模不配置。
 bit[15:14]  保留
 bit[13:8]   自研RF AGC增益档的异频频迟滞时间。时隙调整时，单位为时隙；符号调整时，单位为符号。
             C模不配置。
 bit[7:6]    保留
 bit[5:0]    自研RF AGC增益档的本频迟滞时间。时隙调整时，单位为时隙；符号调整时，单位为符号。
             C模不配置。
   UNION结构:  WBBP_AAGC_GAIN_DELAY_UNION */
#define WBBP_AAGC_GAIN_DELAY_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91448)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S1（RF RSSI为-102~-90dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S1_8S_RF_CTRL_AT2_UNION */
#define WBBP_S1_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9144C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S2（RF RSSI为-87~-69dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S2_8S_RF_CTRL_AT2_UNION */
#define WBBP_S2_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91450)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S3（RF RSSI为-66~-54dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S3_8S_RF_CTRL_AT2_UNION */
#define WBBP_S3_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91454)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S4（RF RSSI为-51~-39dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S4_8S_RF_CTRL_AT2_UNION */
#define WBBP_S4_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91458)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S5（RF RSSI为-36~-21dBm）状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S5_8S_RF_CTRL_AT2_UNION */
#define WBBP_S5_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9145C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_UNION */
#define WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x91460)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S23_INTRA_AT2_UNION */
#define WBBP_RF_8S_GAIN_S23_INTRA_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91464)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S45_INTRA_AT2_UNION */
#define WBBP_RF_8S_GAIN_S45_INTRA_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91468)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S12_INTER_AT1_UNION */
#define WBBP_RF_8S_GAIN_S12_INTER_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x9146C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S34_INTER_AT1_UNION */
#define WBBP_RF_8S_GAIN_S34_INTER_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91470)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_UNION */
#define WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x91474)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      退出cpc_drx状态时，是否启动第一阶段DCR算法，1表示启动，0表示不启动。
             C模不配置。
 bit[7:5]    保留
 bit[4]      退出cpc_drx状态时，RSSI和AGC档位的来源，1表示使用DSP配置的init值，0表示使用进入cpc_drx状态时的保存值。
             C模不配置。
 bit[3:2]    保留
 bit[1]      ABB block检测使能信号。1，BBP会给ABB开窗；0，BBP不给ABB开窗。
 bit[0]      干扰检测使能信号。0，表示不打开干扰检测功能；1，表示打开干扰检测功能。
             说明：此功能仅在D/F态下使用。
             C模不配置。
   UNION结构:  WBBP_BLOCK_DETECT_EN_UNION */
#define WBBP_BLOCK_DETECT_EN_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91478)

/* 寄存器说明：
 bit[31]     关闭Block检测时Block检测默认配置。1，表示使用4阶LPF；0，表示使用2阶LPF。
             C模不配置。
 bit[30]     打开Block检测时Block检测默认配置。1，表示使用4阶LPF；0，表示使用2阶LPF。
             C模不配置。
 bit[29:0]   保留
   UNION结构:  WBBP_BLOCK_LPF_SEL_UNION */
#define WBBP_BLOCK_LPF_SEL_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91480)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  在4阶低通滤波器停留的最短时间，单位slot。
             C模不配置。
 bit[15:14]  保留
 bit[13:8]   Block条件满足次数达到block_hys_th次时，才切换Block控制状态。
             C模不配置。
 bit[7:6]    保留
 bit[5:0]    在2阶低通滤波器停留的最短时间，单位slot。
             C模不配置。
   UNION结构:  WBBP_BLOCK_HYS_SLOT_UNION */
#define WBBP_BLOCK_HYS_SLOT_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91484)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  干扰产生第一种条件中，RRC滤波器前后RSSI差值判断门限，单位dB。
             C模不配置。
 bit[15:14]  保留
 bit[13:8]   干扰产生第二种条件中，RRC滤波器输入端RSSI判断门限，单位dB。
             说明：干扰产生的第二种条件，RRC滤波器之前的RSSI值>=block_gen_rrc_in_2th。
             C模不配置。
 bit[7:6]    保留
 bit[5:0]    干扰产生第一种条件中，RRC滤波器输入端RSSI判断门限，单位dB。
             说明：干扰产生的第一种条件，RRC滤波器之前的RSSI值>=block_gen_rrc_in_th，且RRC前后的RSSI差值>=block_gen_diff_th。
             C模不配置。
   UNION结构:  WBBP_BLOCK_GEN_TH_UNION */
#define WBBP_BLOCK_GEN_TH_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91488)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  干扰消失第一种条件中，RRC滤波器输入端RSSI判断门限，单位dB。
             C模不配置。
 bit[15:6]   保留
 bit[5:0]    干扰消失第一种条件中，RRC滤波器输出端RSSI判断门限，单位dB。
             说明：干扰消失的第一种条件，RRC滤波器之后的RSSI<=block_dis_rrc_out_lth，且RRC滤波器之前的RSSI<=block_dis_rrc_in_th。
             C模不配置。
   UNION结构:  WBBP_BLOCK_DIS_LTH_UNION */
#define WBBP_BLOCK_DIS_LTH_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9148C)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  干扰消失第二种条件中，RRC滤波器前后RSSI差值判断门限，单位dB。
             C模不配置。
 bit[15:6]   保留
 bit[5:0]    干扰消失第二种条件中，RRC滤波器输出端RSSI判断门限，单位dB。
             说明：干扰消失的第二种条件，RRC滤波器之后的RSSI>block_dis_rrc_out_hth，且RRC滤波器前后的RSSI差值<=block_dis_diff_th。
             C模不配置。
   UNION结构:  WBBP_BLOCK_DIS_HTH_UNION */
#define WBBP_BLOCK_DIS_HTH_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91490)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  八档AAGC状态跳转S7->S8的RSSI门限。
             C模不配置。
 bit[15:8]   八档AAGC状态跳转S6->S7的RSSI门限。
             C模不配置。
 bit[7:0]    八档AAGC状态跳转S5->S6的RSSI门限，单位dBm，配置二进制补码值。
             可参考AAGC_RSSI_INC_TH寄存器的说明。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_8S_INC_TH_A20_UNION */
#define WBBP_AAGC_RSSI_8S_INC_TH_A20_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x914AC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  八档AAGC状态跳转S8->S7的RSSI门限。
             C模不配置。
 bit[15:8]   八档AAGC状态跳转S7->S6的RSSI门限。
             C模不配置。
 bit[7:0]    八档AAGC状态跳转S6->S5的RSSI门限，单位dBm，配置二进制补码值。
             可参考AAGC_RSSI_DEC_TH寄存器的说明。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_8S_DEC_TH_A20_UNION */
#define WBBP_AAGC_RSSI_8S_DEC_TH_A20_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x914B0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S6状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S6_8S_RF_CTRL_AT1_UNION */
#define WBBP_S6_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x914B4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S7状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S7_8S_RF_CTRL_AT1_UNION */
#define WBBP_S7_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x914B8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S8状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S8_8S_RF_CTRL_AT1_UNION */
#define WBBP_S8_8S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x914BC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S6状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S6_8S_RF_CTRL_AT2_UNION */
#define WBBP_S6_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x914C0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S7状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S7_8S_RF_CTRL_AT2_UNION */
#define WBBP_S7_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x914C4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   八档AAGC S8状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S8_8S_RF_CTRL_AT2_UNION */
#define WBBP_S8_8S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x914C8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_UNION */
#define WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x914CC)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S8_INTER_AT1_A20_UNION */
#define WBBP_RF_8S_GAIN_S8_INTER_AT1_A20_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x914D0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_UNION */
#define WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x914D4)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S8_INTER_AT2_A20_UNION */
#define WBBP_RF_8S_GAIN_S8_INTER_AT2_A20_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x914D8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_UNION */
#define WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x914DC)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     BBP上报硬件Block检测结果。0，不处于Block；1，处于Block。
 bit[27:26]  保留
 bit[25:16]  RRC滤波器之后统计的DRSSI值，单位0.125dB。
 bit[15:10]  保留
 bit[9:0]    RRC滤波器之前统计的DRSSI值，单位0.125dB。
   UNION结构:  WBBP_BLOCK_RPT_AT1_UNION */
#define WBBP_BLOCK_RPT_AT1_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x914E0)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     BBP上报硬件Block检测结果。0，不处于Block；1，处于Block。
 bit[27:26]  保留
 bit[25:16]  RRC滤波器之后统计的DRSSI值，单位0.125dB。
 bit[15:10]  保留
 bit[9:0]    RRC滤波器之前统计的DRSSI值，单位0.125dB。
   UNION结构:  WBBP_BLOCK_RPT_AT2_UNION */
#define WBBP_BLOCK_RPT_AT2_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x914E4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S23_INTER_AT2_UNION */
#define WBBP_RF_8S_GAIN_S23_INTER_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x914E8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S45_INTER_AT2_UNION */
#define WBBP_RF_8S_GAIN_S45_INTER_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x914EC)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S8_INTRA_AT1_A20_UNION */
#define WBBP_RF_8S_GAIN_S8_INTRA_AT1_A20_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x914F0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_UNION */
#define WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x914F4)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_8S_GAIN_S8_INTRA_AT2_A20_UNION */
#define WBBP_RF_8S_GAIN_S8_INTRA_AT2_A20_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x914F8)

/* 寄存器说明：
 bit[31]     周期配置RF增益控制寄存器的使能。1，表示周期配置RF增益控制寄存器；0，表示只在增益状态跳转时配置RF增益控制寄存器。
             C模不配置。
 bit[30:16]  保留
 bit[15:0]   周期配置RF增益控制寄存器的周期，单位slot。
             C模不配置。
   UNION结构:  WBBP_RF_GAIN_CFG_FREQ_UNION */
#define WBBP_RF_GAIN_CFG_FREQ_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x914FC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S1对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S1_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S1_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91500)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S2对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S2_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S2_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91504)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S3对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S3_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S3_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91508)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S4对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S4_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S4_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9150C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S5对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S5_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S5_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91510)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S6对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S6_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S6_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91514)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S7对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S7_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S7_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91518)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S8对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S8_VBIAS_AT1_UNION */
#define WBBP_RF_5S_S8_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9151C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线BLOCK下S1对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S1_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S1_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91520)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线BLOCK下S2对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S2_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S2_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91524)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线BLOCK下S3对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S3_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S3_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91528)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线BLOCK下S4对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S4_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S4_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9152C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线BLOCK下S5对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S5_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S5_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91530)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线BLOCK下S6对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S6_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S6_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91534)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线BLOCK下S7对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S7_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S7_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91538)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线BLOCK下S8对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_5S_S8_VBIAS_AT2_UNION */
#define WBBP_RF_5S_S8_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9153C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S1对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S1_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S1_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91540)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S2对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S2_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S2_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91544)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S3对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S3_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S3_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91548)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S4对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S4_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S4_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9154C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S5对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S5_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S5_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91550)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S6对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S6_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S6_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91554)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S7对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S7_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S7_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91558)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S8对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S8_VBIAS_AT1_UNION */
#define WBBP_RF_8S_S8_VBIAS_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9155C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主天线非BLOCK下S1对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S1_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S1_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91560)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线非BLOCK下S2对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S2_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S2_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91564)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线非BLOCK下S3对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S3_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S3_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91568)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线非BLOCK下S4对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S4_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S4_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9156C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线非BLOCK下S5对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S5_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S5_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91570)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线非BLOCK下S6对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S6_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S6_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91574)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线非BLOCK下S7对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S7_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S7_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91578)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   辅天线非BLOCK下S8对应VBIAS控制字。
             C模不配置。
   UNION结构:  WBBP_RF_8S_S8_VBIAS_AT2_UNION */
#define WBBP_RF_8S_S8_VBIAS_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9157C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S12_INTRA_AT1_UNION */
#define WBBP_RF_5S_GAIN_S12_INTRA_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91830)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S34_INTRA_AT1_UNION */
#define WBBP_RF_5S_GAIN_S34_INTRA_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91834)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_UNION */
#define WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x91838)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S23_INTRA_AT2_UNION */
#define WBBP_RF_5S_GAIN_S23_INTRA_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x9183C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S45_INTRA_AT2_UNION */
#define WBBP_RF_5S_GAIN_S45_INTRA_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91840)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S12_INTER_AT1_UNION */
#define WBBP_RF_5S_GAIN_S12_INTER_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91844)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S34_INTER_AT1_UNION */
#define WBBP_RF_5S_GAIN_S34_INTER_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91848)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_UNION */
#define WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x9184C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S23_INTER_AT2_UNION */
#define WBBP_RF_5S_GAIN_S23_INTER_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91850)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S45_INTER_AT2_UNION */
#define WBBP_RF_5S_GAIN_S45_INTER_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91854)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  八档AAGC DRSSI迟滞门限。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
 bit[15:8]   八档AAGC DRSSI门限迟滞次数。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
 bit[7:0]    八档AAGC DRSSI门限判断周期，单位为DRSSI统计周期。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
   UNION结构:  WBBP_DRSSI_OVER_CTRL_AT1_UNION */
#define WBBP_DRSSI_OVER_CTRL_AT1_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91858)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  八档AAGC DRSSI迟滞门限。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
 bit[15:8]   八档AAGC DRSSI门限迟滞次数。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
 bit[7:0]    八档AAGC DRSSI门限判断周期，单位为DRSSI统计周期。
             AGC在RF_SC/RF_DC可以分时共用。
             C模不配置。
   UNION结构:  WBBP_DRSSI_OVER_CTRL_AT2_UNION */
#define WBBP_DRSSI_OVER_CTRL_AT2_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9185C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    AAGC状态机选择。0，4阶LPF使用五档状态机，2阶LPF使用八档状态机；1，固定使用五档状态机；2，固定使用八档状态机。
             C模不配置。
   UNION结构:  WBBP_AAGC_STATE_SEL_UNION */
#define WBBP_AAGC_STATE_SEL_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91860)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5]      在软件使能dsp_spur_remove_at1_en有效时，分集始终进行谐波干扰消除的使能信号。此时与档位、RSSI值、本频标志等其他条件无关。1，表示始终进行谐波干扰消除；0，表示由其他条件决定。主要用于调试。
 bit[4]      分集谐波干扰消除使能，高电平有效。
 bit[3:2]    保留
 bit[1]      在软件使能dsp_spur_remove_at1_en有效时，主集始终进行谐波干扰消除的使能信号。此时与档位、RSSI值、本频标志等其他条件无关。1，表示始终进行谐波干扰消除；0，表示由其他条件决定。主要用于调试。
 bit[0]      主集谐波干扰消除使能，高电平有效。
   UNION结构:  WBBP_SPUR_REMOVE_EN_UNION */
#define WBBP_SPUR_REMOVE_EN_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91868)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  主集和分集共用的RSSI门限值。当RSSI值小于该门限值时，进行谐波干扰消除。
 bit[15:9]   保留
 bit[8:0]    主集和分集共用的谐波干扰信号相对于20kHz的频率倍数，有符号数补码表示。取值范围-118~-1、1~118。默认配置1。
   UNION结构:  WBBP_SPUR_CFG_UNION */
#define WBBP_SPUR_CFG_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x9186C)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24:16]  主集上报谐波干扰消除值虚部，用于调试。
 bit[15:9]   保留
 bit[8:0]    主集上报谐波干扰消除值实部，用于调试。
   UNION结构:  WBBP_AT1_SPUR_REMOVED_DSP_UNION */
#define WBBP_AT1_SPUR_REMOVED_DSP_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x91870)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24:16]  分集上报谐波干扰消除值虚部，用于调试。
 bit[15:9]   保留
 bit[8:0]    分集上报谐波干扰消除值实部，用于调试。
   UNION结构:  WBBP_AT2_SPUR_REMOVED_DSP_UNION */
#define WBBP_AT2_SPUR_REMOVED_DSP_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x91874)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S8状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S8_5S_RF_CTRL_AT2_UNION */
#define WBBP_S8_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91878)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
 bit[15:10]  保留
 bit[9:0]    刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
   UNION结构:  WBBP_IQ_AK_PK_INIT_CFG_AT1_UNION */
#define WBBP_IQ_AK_PK_INIT_CFG_AT1_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A00)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
 bit[15:10]  保留
 bit[9:0]    刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
   UNION结构:  WBBP_IQ_AK_PK_INIT_CFG_AT2_UNION */
#define WBBP_IQ_AK_PK_INIT_CFG_AT2_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A04)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12]     AGC所处RF_SC/RF_DC工作状态。0，RF_SC；1，RF_DC。
             C模不配置。
 bit[11:9]   保留
 bit[8]      NCO相位清零脉冲。
             C模不配置。
 bit[7:5]    保留
 bit[4]      NCO模块使能，高电平有效。
             C模不配置。
 bit[3:1]    保留
 bit[0]      下变频模块输出主辅载波信号位置选择，使主载波落在cell1上。0，主载波在低频点；1，主载波在高频点。
             C模不配置。
   UNION结构:  WBBP_HSDPA_DC_CFG_UNION */
#define WBBP_HSDPA_DC_CFG_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91A08)

/* 寄存器说明：
   详      述：NCO输出信号频率。
            C模不配置。
   UNION结构 ：无 */
#define WBBP_NCO_FREQ_CFG_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91A0C)

/* 寄存器说明：
   详      述：NCO输出信号相位。
            C模不配置。
   UNION结构 ：无 */
#define WBBP_NCO_OFFSET_CFG_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91A10)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:12]  RF_DC Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
             C模不配置。
 bit[11:10]  保留
 bit[9:8]    RF_DC非Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
             C模不配置。
 bit[7:6]    保留
 bit[5:4]    RF_SC Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
             C模不配置。
 bit[3:2]    保留
 bit[1:0]    RF_SC非Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
             C模不配置。
   UNION结构:  WBBP_WAGC_IQ_DLY_CTRL_UNION */
#define WBBP_WAGC_IQ_DLY_CTRL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91A18)

/* 寄存器说明：
 bit[31]     保留
 bit[30:28]  RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF八档增益控制。
             C模不配置。
 bit[27]     保留
 bit[26:24]  RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF五档增益控制。
             C模不配置。
 bit[23:11]  保留
 bit[10:0]   RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
             C模不配置。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG0_AT1_UNION */
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x91A1C)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。
             C模不配置。
 bit[23:22]  保留
 bit[21]     RF_SC/RF_DC切换刚刚完成时，DSP配置八档状态机初始值使能。1，DSP配置八档状态机初始值；0，BBP继承以前的值。
             C模不配置。
 bit[20]     RF_SC/RF_DC切换刚刚完成时，DSP配置五档状态机初始值使能。1，DSP配置五档状态机初始值；0，BBP继承以前的值。
             C模不配置。
 bit[19:17]  保留
 bit[16]     RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。
             C模不配置。
 bit[15:9]   保留
 bit[8:0]    RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。
             C模不配置。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG1_AT1_UNION */
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x91A20)

/* 寄存器说明：
 bit[31]     保留
 bit[30:28]  RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF八档增益控制。
             C模不配置。
 bit[27]     保留
 bit[26:24]  RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF五档增益控制。
             C模不配置。
 bit[23:11]  保留
 bit[10:0]   RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
             C模不配置。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG0_AT2_UNION */
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x91A24)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。
             C模不配置。
 bit[23:22]  保留
 bit[21]     RF_SC/RF_DC切换刚刚完成时，DSP配置八档状态机初始值使能。1，DSP配置八档状态机初始值；0，BBP继承以前的值。
             C模不配置。
 bit[20]     RF_SC/RF_DC切换刚刚完成时，DSP配置五档状态机初始值使能。1，DSP配置五档状态机初始值；0，BBP继承以前的值。
             C模不配置。
 bit[19:17]  保留
 bit[16]     RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。
             C模不配置。
 bit[15:9]   保留
 bit[8:0]    RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。
             C模不配置。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG1_AT2_UNION */
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x91A28)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   BBP上报天线口RSSI值（单载波），0.125dB精度。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[8:0]    BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
   UNION结构:  WBBP_INIT_AGC_RPT_CELL_AT1_UNION */
#define WBBP_INIT_AGC_RPT_CELL_AT1_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A2C)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   BBP上报天线口RSSI值（单载波），0.125dB精度。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[8:0]    BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
   UNION结构:  WBBP_INIT_AGC_RPT_CELL_AT2_UNION */
#define WBBP_INIT_AGC_RPT_CELL_AT2_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A30)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   DSP通过配置该时间值，选择在哪一个定时中断读取ABB和BBP上报的用于软件Block判决的信号能量。
             C模不配置。
   UNION结构:  WBBP_SOFT_BLK_CFG_UNION */
#define WBBP_SOFT_BLK_CFG_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91A34)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:4]   DSP读取的BBP上报的用于软件Block判决的信号能量。
 bit[3:1]    保留
 bit[0]      DSP读取的ABB和BBP上报的用于软件Block判决的信号能量有效指示。
   UNION结构:  WBBP_ABB_BLK_RPT_AT1_UNION */
#define WBBP_ABB_BLK_RPT_AT1_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A38)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:28]  RF Block状态SPI控制字通道选择。
             C模不配置。
             00：选择ch0；
             01：选择ch1；
             10：选择ch2；
             11：选择ch3；
 bit[27:25]  保留
 bit[24]     RF Block状态SPI控制字触发脉冲。
             C模不配置。
 bit[23:0]   RF Block状态SPI控制字。
             C模不配置。
   UNION结构:  WBBP_BLK_OUTPUT_UNION */
#define WBBP_BLK_OUTPUT_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91A3C)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:4]   DSP读取的BBP上报的用于软件Block判决的信号能量。
 bit[3:1]    保留
 bit[0]      DSP读取的ABB和BBP上报的用于软件Block判决的信号能量有效指示。
   UNION结构:  WBBP_ABB_BLK_RPT_AT2_UNION */
#define WBBP_ABB_BLK_RPT_AT2_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A40)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:0]   时钟门控旁路寄存器。0，时钟门控使能；1，时钟门控旁路。
             [0] 主天线spur remove模块，
             [1] 主天线rxiq模块
             [2] 主天线下变频模块
             [3] 主天线scfilter模块
             [4] 主天线W辅载波scfilter模块
             [5] 主天线W辅载波其他模块
             [6] 主天线RRC RSSI dcoc， 主辅天线公共base_cnt等模块
             [7] 主天线W专用模块，WC共用模块
             [8] 主天线TDS专用模块，fir和pdgt
             [9] 主天线debug模块
             [10] 主天线freq_error模块
             [11] sc_cal模块（主辅天线公用）
             [12] 主天线fifo模块读写时钟。
             [13] 辅天线spur remove模块，
             [14] 辅天线rxiq模块
             [15] 辅天线下变频模块
             [16] 辅天线scfilter模块
             [17] 辅天线W辅载波scfilter模块
             [18] 辅天线W辅载波其他模块
             [19] 辅天线RRC RSSI dcoc 模块
             [20] 辅天线W专用模块，WC共用模块
             [21] 辅天线TDS专用模块，fir和pdgt
             [22] 辅天线debug模块
             [23] 辅天线freq_error模块
             [24] reserved
             [25] 辅天线fifo模块读写时钟。
   UNION结构:  WBBP_WAGC_CKG_BYPASS_UNION */
#define WBBP_WAGC_CKG_BYPASS_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A44)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      天线1 RX静态DC校准相关测量模块运算完成标志。
   UNION结构:  WBBP_DC_STA_CAL_RPT_AT1_UNION */
#define WBBP_DC_STA_CAL_RPT_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91A48)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      天线2 RX静态DC校准相关测量模块运算完成标志。
   UNION结构:  WBBP_DC_STA_CAL_RPT_AT2_UNION */
#define WBBP_DC_STA_CAL_RPT_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91A4C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      天线1配置DCR RX静态DC校准模式。
             1，DCR处于RX静态DC校准模式；0，DCR处于正常工作模式。
   UNION结构:  WBBP_DC_STA_CRRO_CTRL0_AT1_UNION */
#define WBBP_DC_STA_CRRO_CTRL0_AT1_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A50)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      天线2配置DCR RX静态DC校准模式。
             1，DCR处于RX静态DC校准模式；0，DCR处于正常工作模式。
   UNION结构:  WBBP_DC_STA_CRRO_CTRL0_AT2_UNION */
#define WBBP_DC_STA_CRRO_CTRL0_AT2_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A54)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      天线1 RX静态DC校准相关测量模块完成标志清零脉冲。
   UNION结构:  WBBP_DC_STA_CRRO_CTRL1_AT1_UNION */
#define WBBP_DC_STA_CRRO_CTRL1_AT1_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A58)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      天线2 RX静态DC校准相关测量模块完成标志清零脉冲。
   UNION结构:  WBBP_DC_STA_CRRO_CTRL1_AT2_UNION */
#define WBBP_DC_STA_CRRO_CTRL1_AT2_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91A5C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态1时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A60)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态2时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A64)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态3时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A68)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态4时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A6C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态5时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A70)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态6时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A74)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态7时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A78)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态8时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A7C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态1时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A80)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态2时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A84)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态3时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A88)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态4时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A8C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态5时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A90)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态1时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A94)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态2时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A98)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态3时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91A9C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态4时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AA0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态5时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AA4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态6时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AA8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态7时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AAC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态8时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AB0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态1时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AB4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态2时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AB8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态3时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91ABC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态4时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AC0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态5时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AC4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态1时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AC8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态2时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91ACC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态3时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AD0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态4时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AD4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态5时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AD8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态6时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91ADC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态7时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AE0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态8时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AE4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态1时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AE8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态2时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AEC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态3时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AF0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态4时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AF4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态5时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AF8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态1时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91AFC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态2时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B00)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态3时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B04)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态4时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B08)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态5时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B0C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态6时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B10)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态7时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B14)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   8档AGC状态8时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B18)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态1时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B1C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态2时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B20)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态3时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B24)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态4时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B28)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态5时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91B2C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      静态DC校准值SPI发送使能，高电平有效。
             C模不配置。
   UNION结构:  WBBP_DC_STA_SPI_EN_UNION */
#define WBBP_DC_STA_SPI_EN_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91B30)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:8]   DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。
 bit[7:0]    DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。
   UNION结构:  WBBP_DCR_2ND_CTRL_AT1_UNION */
#define WBBP_DCR_2ND_CTRL_AT1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91B34)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:8]   DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。
 bit[7:0]    DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。
   UNION结构:  WBBP_DCR_2ND_CTRL_AT2_UNION */
#define WBBP_DCR_2ND_CTRL_AT2_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91B38)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:24]  BBP上报用于控制RF增益的8档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。
 bit[23]     保留
 bit[22:20]  BBP上报用于控制RF增益的5档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；
 bit[19:0]   保留
   UNION结构:  WBBP_WAGC_STATE_RPT_AT1_UNION */
#define WBBP_WAGC_STATE_RPT_AT1_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91B3C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:24]  BBP上报用于控制RF增益的8档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。
 bit[23]     保留
 bit[22:20]  BBP上报用于控制RF增益的5档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；
 bit[19:0]   保留
   UNION结构:  WBBP_WAGC_STATE_RPT_AT2_UNION */
#define WBBP_WAGC_STATE_RPT_AT2_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91B40)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      软件配置天线1 BBP异频Block状态。
             1，处于Block状态；0，不处于Block状态。
             C模不配置。
 bit[0]      软件配置天线1 BBP本频Block状态。
             1，处于Block状态；0，不处于Block状态。
             C模不配置。
   UNION结构:  WBBP_DSP_CFG_BBP_BLK_AT1_UNION */
#define WBBP_DSP_CFG_BBP_BLK_AT1_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91B44)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      软件配置天线2 BBP异频Block状态。
             1，处于Block状态；0，不处于Block状态。
             C模不配置。
 bit[0]      软件配置天线2 BBP本频Block状态
             1，处于Block状态；0，不处于Block状态。
             C模不配置。
   UNION结构:  WBBP_DSP_CFG_BBP_BLK_AT2_UNION */
#define WBBP_DSP_CFG_BBP_BLK_AT2_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91B48)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  W和TDS上报IQ Mismatch计算得到的滤波前pk值。
 bit[15:10]  保留
 bit[9:0]    W和TDS上报IQ Mismatch计算得到的滤波前ak值。
   UNION结构:  WBBP_WAGC_IQ_MIS_RPT_AT1_UNION */
#define WBBP_WAGC_IQ_MIS_RPT_AT1_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91B4C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  W和TDS上报IQ Mismatch计算得到的滤波前pk值。
 bit[15:10]  保留
 bit[9:0]    W和TDS上报IQ Mismatch计算得到的滤波前ak值。
   UNION结构:  WBBP_WAGC_IQ_MIS_RPT_AT2_UNION */
#define WBBP_WAGC_IQ_MIS_RPT_AT2_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91B50)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    谐波干扰消除，alpha滤波系数选择。
             3'd0，不进行alpha滤波；
             3'd1，alpha滤波系数为1/2；
             3'd2，alpha滤波系数为1/4；
             3'd3，alpha滤波系数为1/8；
             3'd4，alpha滤波系数为1/16；
             3'd5，alpha滤波系数为1/32。
   UNION结构:  WBBP_SPUR_ALPHA_COE_UNION */
#define WBBP_SPUR_ALPHA_COE_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91B54)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  W、C和TDS上报IQ Mismatch计算得到的滤波后pk值。
 bit[15:10]  保留
 bit[9:0]    W、C和TDS上报IQ Mismatch计算得到的滤波后ak值。
   UNION结构:  WBBP_WAGC_IQ_MIS_POST_RPT_AT1_UNION */
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91B58)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  W、C和TDS上报IQ Mismatch计算得到的滤波后pk值。
 bit[15:10]  保留
 bit[9:0]    W、C和TDS上报IQ Mismatch计算得到的滤波后ak值。
   UNION结构:  WBBP_WAGC_IQ_MIS_POST_RPT_AT2_UNION */
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91B5C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  五档AAGC状态跳转S7->S8的RSSI门限。
             C模不配置。
 bit[15:8]   五档AAGC状态跳转S6->S7的RSSI门限。
             C模不配置。
 bit[7:0]    五档AAGC状态跳转S5->S6的RSSI门限，单位dBm，配置二进制补码值。
             说明：按照S1->S2->S3->S4->S5->S6->S7->S8的顺序，天线口的RSSI递增，AAGC的增益递减。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_5S_INC_TH_ADD_UNION */
#define WBBP_AAGC_RSSI_5S_INC_TH_ADD_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91B9C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  五档AAGC状态跳转S8->S7的RSSI门限。
             C模不配置。
 bit[15:8]   五档AAGC状态跳转S7->S6的RSSI门限。
             C模不配置。
 bit[7:0]    五档AAGC状态跳转S6->S5的RSSI门限，单位dBm，配置二进制补码值。
             说明：按照S8->S7->S6->S5->S4->S3->S2->S1的顺序，天线口的RSSI递减，AAGC的增益递增。
             C模不配置。
   UNION结构:  WBBP_AAGC_RSSI_5S_DEC_TH_ADD_UNION */
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADD_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91BA0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S67_INTRA_AT1_UNION */
#define WBBP_RF_5S_GAIN_S67_INTRA_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91BA4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S8_INTRA_AT12_UNION */
#define WBBP_RF_5S_GAIN_S8_INTRA_AT12_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91BA8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S67_INTRA_AT2_UNION */
#define WBBP_RF_5S_GAIN_S67_INTRA_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91BAC)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S67_INTER_AT1_UNION */
#define WBBP_RF_5S_GAIN_S67_INTER_AT1_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91BB0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S8_INTER_AT12_UNION */
#define WBBP_RF_5S_GAIN_S8_INTER_AT12_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91BB4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
 bit[15:12]  保留
 bit[11:0]   五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
             C模不配置。
   UNION结构:  WBBP_RF_5S_GAIN_S67_INTER_AT2_UNION */
#define WBBP_RF_5S_GAIN_S67_INTER_AT2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91BB8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态6时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BBC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态7时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BC0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态8时，本频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BC4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态6时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BC8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态7时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BCC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态8时，异频下天线1静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT1_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT1_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BD0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态6时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BD4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态7时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BD8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态8时，本频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BDC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态6时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BE0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态7时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BE4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   5档AGC状态8时，异频下天线2静态DC补偿值。
   UNION结构:  WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT2_UNION */
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT2_ADDR     (SOC_BBP_WCDMA_BASE_ADDR + 0x91BE8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S6状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S6_5S_RF_CTRL_AT1_UNION */
#define WBBP_S6_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91BEC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S7状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S7_5S_RF_CTRL_AT1_UNION */
#define WBBP_S7_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91BF0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S8状态时主集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S8_5S_RF_CTRL_AT1_UNION */
#define WBBP_S8_5S_RF_CTRL_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91BF4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S6状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S6_5S_RF_CTRL_AT2_UNION */
#define WBBP_S6_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91BF8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   五档AAGC S7状态时分集RF控制字。
             C模不配置。
   UNION结构:  WBBP_S7_5S_RF_CTRL_AT2_UNION */
#define WBBP_S7_5S_RF_CTRL_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91BFC)

/* 寄存器说明：cordic初始相位
   详      述：配置cordic频偏校正模块的初始相位，有符号数，更新周期大于1时隙。（用NCO模块实现）
            C模不配置。
   UNION结构 ：无 */
#define WBBP_CORDIC_INI_PHASE_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91C00)

/* 寄存器说明：cordic频率
   详      述：配置cordic频偏校正模块的频率，无符号数，更新周期大于1时隙。（用NCO模块实现）
            C模不配置。
   UNION结构 ：无 */
#define WBBP_CORDIC_DELT_PHASE_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91C04)

/* 寄存器说明：初始及间隔相位有效信号
 bit[31:1]   保留
 bit[0]      保留
   UNION结构:  WBBP_CORDIC_PHASE_VLD_UNION */
#define WBBP_CORDIC_PHASE_VLD_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91C08)

/* 寄存器说明：TDS
 bit[31:9]   保留
 bit[8:0]    软件配置TDS采样纠偏值，有符号数。
             C模不配置。
   UNION结构:  WBBP_TDS_SC_OFFSET_UNION */
#define WBBP_TDS_SC_OFFSET_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91C0C)

/* 寄存器说明：tds_fpu内部模块功能开关寄存器
 bit[31:20]  保留
 bit[19]     tds sinc重采样滤波模块处理使能信号。
             1'b0，不使能，旁路；
             1'b1，使能。
             C模不配置。
 bit[18]     tds cordic模块处理使能信号。
             1'b0，不使能，旁路；
             1'b1，使能。
             C模不配置。
 bit[17:13]  保留
 bit[12]     tds dagct2补偿使能信号。
             1'b0，不使能，旁路；
             1'b1，使能。
             C模不配置。
 bit[11]     tds drssi_nb计算使能信号。
             1'b0，不使能；
             1'b1，使能。
             C模不配置。
 bit[10:8]   保留
 bit[7]      tds drssi_wb计算使能信号。
             1'b0，不使能；
             1'b1，使能。
             C模不配置。
 bit[6]      tds rxiq校准因子计算使能信号。
             1'b0，不使能；
             1'b1，使能。
             C模不配置。
 bit[5]      tds rxiq校准因子补偿使能信号。
             1'b0，不使能，旁路；
             1'b1，使能。
             C模不配置。
 bit[4]      保留
 bit[3]      tds tds dagct1补偿使能信号。
             1'b0，不使能，旁路；
             1'b1，使能。
             C模不配置。
 bit[2]      tds dcoc计算dc_est使能信号。
             1'b0，不使能；
             1'b1，使能。
             C模不配置。
 bit[1]      tds dcoc补偿dc_used使能信号。
             1'b0，不使能，旁路；
             1'b1，使能。
             C模不配置。
 bit[0]      tds spmv使能信号。
             1'b0，不使能，旁路；
             1'b1，使能。
             C模不配置。
   UNION结构:  WBBP_TDS_FPU_FUNC_EN_UNION */
#define WBBP_TDS_FPU_FUNC_EN_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91E00)

/* 寄存器说明：下采样模块的抽点选择信号
 bit[31:2]   保留
 bit[1:0]    下采样模块的抽点选择信号。
             上电之后只配置一次，配置范围0~2。
             0，选择下采样滤波器输出的第0、3、6…个数据；
             1，选择下采样滤波器输出的第1、4、7…个数据；
             2，选择下采样滤波器输出的第2、5、8…个数据；
             3，保留。
             C模不配置。
   UNION结构:  WBBP_FIR_SEL_UNION */
#define WBBP_FIR_SEL_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x91E04)

/* 寄存器说明：接收数据抽取选择寄存器
 bit[31:2]   保留
 bit[1:0]    接收滤波后数据选择输出。
             2'b00，选择抽取第1路信号；
             2'b01，选择抽取第2路信号；
             2'b10，选择抽取第3路信号；
             2'b11，选择抽取第4路信号。
   UNION结构:  WBBP_DATA_SEL_UNION */
#define WBBP_DATA_SEL_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x91E0C)

/* 寄存器说明：dcoc是否按样点更新
 bit[31:1]   保留
 bit[0]      TD dcoc是否按样点更新dc_used。
             1'b0，按样点更新；
             1'b1，按时隙更新。
             注意：本寄存器上电配置一次，不支持动态切换的情况。
             C模不配置。
   UNION结构:  WBBP_DCOC_UPDATE_UNION */
#define WBBP_DCOC_UPDATE_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91E20)

/* 寄存器说明：dcoc的天线1的i路和q路数据移位bit数
 bit[31:21]  保留
 bit[20:16]  TD软件配置的天线1的Q路数据移位bit数，配置范围10~19。
             C模不配置。
 bit[15:5]   保留
 bit[4:0]    TD软件配置的天线1的I路数据移位bit数，配置范围10~19。
             C模不配置。
   UNION结构:  WBBP_DCOC_SFTBIT1_UNION */
#define WBBP_DCOC_SFTBIT1_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E24)

/* 寄存器说明：dcoc的天线2的i路和q路数据移位bit数
 bit[31:21]  保留
 bit[20:16]  TD软件配置的天线2的Q路数据移位bit数，配置范围10~19。
             C模不配置。
 bit[15:5]   保留
 bit[4:0]    TD软件配置的天线2的I路数据移位bit数，配置范围10~19。
             C模不配置。
   UNION结构:  WBBP_DCOC_SFTBIT2_UNION */
#define WBBP_DCOC_SFTBIT2_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E28)

/* 寄存器说明：软件配置dcocdc值有效信号
 bit[31:1]   保留
 bit[0]      TD软件配置的dcoc的DC值是否生效标志。
             1'b0，不生效；
             1'b1，生效。
             C模不配置。
   UNION结构:  WBBP_DCOC_CFG_VLD_UNION */
#define WBBP_DCOC_CFG_VLD_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E2C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    下采样滤波器内部累加器移位bit数。
             上电之后只配置一次，配置范围10~13。
             C模不配置。
   UNION结构:  WBBP_FIR_SFT_UNION */
#define WBBP_FIR_SFT_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x91E30)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:4]   ad_on包络个数，可维可测。
 bit[3]      rx_cnt计数使能，高电平有效，低电平时rx_cnt清零。
             C模不配置。
 bit[2:1]    保留
 bit[0]      参数强制生效使能。
             C模不配置。
   UNION结构:  WBBP_RX_CNT_UNION */
#define WBBP_RX_CNT_ADDR                              (SOC_BBP_WCDMA_BASE_ADDR + 0x91E34)

/* 寄存器说明：天线1的pre_dagct增益
 bit[31:10]  保留
 bit[9:0]    TD软件配置的天线1的pre_dagct增益，有符号数，有效范围[-336,336]。
             C模不配置。
   UNION结构:  WBBP_DACGT1_GAIN1_UNION */
#define WBBP_DACGT1_GAIN1_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E40)

/* 寄存器说明：天线2的pre_dagct增益
 bit[31:10]  保留
 bit[9:0]    TD软件配置的天线2的pre_dagct增益，有符号数，有效范围[-336,336]。
             C模不配置。
   UNION结构:  WBBP_DACGT1_GAIN2_UNION */
#define WBBP_DACGT1_GAIN2_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E44)

/* 寄存器说明：天线1的post_dagct增益
 bit[31:10]  保留
 bit[9:0]    TD软件配置的天线1的post_dagct增益，有符号数，有效范围[-336,336]。
             C模不配置。
   UNION结构:  WBBP_DACGT2_GAIN1_UNION */
#define WBBP_DACGT2_GAIN1_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E48)

/* 寄存器说明：天线2的post_dagct增益
 bit[31:10]  保留
 bit[9:0]    TD软件配置的天线2的post_dagct增益，有符号数，有效范围[-336,336]。
             C模不配置。
   UNION结构:  WBBP_DACGT2_GAIN2_UNION */
#define WBBP_DACGT2_GAIN2_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E4C)

/* 寄存器说明：rxiq校准因子更新阈值
 bit[31:6]   保留
 bit[5:0]    W和TD rxiq校准因子更新阈值。取值范围[11,63]。W典型配置0xb。
   UNION结构:  WBBP_RXIQ_THRES_UNION */
#define WBBP_RXIQ_THRES_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91E50)

/* 寄存器说明：天线1的rxiq计算因子的移位的bit数
 bit[31:18]  保留
 bit[17:16]  天线1的rxiq移位的bit数ShiftC。取值范围[0,3]。
 bit[15:12]  保留
 bit[11:8]   天线1的rxiq移位的bit数ShiftB。取值范围[9,15]。
 bit[7:4]    保留
 bit[3:0]    天线1的rxiq移位的bit数ShiftA。取值范围[10,15]。
   UNION结构:  WBBP_RXIQ_SFTBIT0_UNION */
#define WBBP_RXIQ_SFTBIT0_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E54)

/* 寄存器说明：天线2的rxiq计算因子的移位的bit数
 bit[31:18]  保留
 bit[17:16]  天线2的rxiq移位的bit数ShiftC。取值范围[0,3]。
 bit[15:12]  保留
 bit[11:8]   天线2的rxiq移位的bit数ShiftB。取值范围[9,15]。
 bit[7:4]    保留
 bit[3:0]    天线2的rxiq移位的bit数ShiftA。取值范围[10,15]。
   UNION结构:  WBBP_RXIQ_SFTBIT1_UNION */
#define WBBP_RXIQ_SFTBIT1_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91E58)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  pk值幅度限制，无符号数。
 bit[15:9]   保留
 bit[8:0]    ak值幅度限制，无符号数。
   UNION结构:  WBBP_RXIQ_LIMIT_UNION */
#define WBBP_RXIQ_LIMIT_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91E5C)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      TD软件配置的rxiq值是否生效标志。
             1'b0，不生效；
             1'b1，生效。
 bit[3]      保留
 bit[2:0]    AP权重，0~4对应链路16,8,4,2,1。
   UNION结构:  WBBP_RXIQ_WEIGHT_UNION */
#define WBBP_RXIQ_WEIGHT_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91E60)

/* 寄存器说明：rssi移位X的bit数
 bit[31:10]  保留
 bit[9:5]    rssi移位X的bit数。取值范围[3,10]。
             C模不配置。
 bit[4:0]    rssi移位X的bit数。取值范围[3,10]。
             C模不配置。
   UNION结构:  WBBP_RSSI_X_SFTBIT_UNION */
#define WBBP_RSSI_X_SFTBIT_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91E64)

/* 寄存器说明：不同数据速率时rssi移位M的bit数
 bit[31:21]  保留
 bit[20:16]  rssi移位M的bit数。取值范围[6,17]。
             C模不配置。
 bit[15:13]  保留
 bit[12:8]   rssi移位M的bit数。取值范围[6,17]。
             C模不配置。
 bit[7:5]    保留
 bit[4:0]    rssi移位M的bit数。取值范围[6,17]。
             C模不配置。
   UNION结构:  WBBP_RSSI_M_SFTBIT_UNION */
#define WBBP_RSSI_M_SFTBIT_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91E68)

/* 寄存器说明：
   详      述：冗余备份寄存器。
            Bit[0]：X模时隙头旁路。为1时旁路X模时隙头，agc_base_cnt到时隙结束自动循环。
            Bit[16]：wt_abb_data_if中的异步fifo同步使能。为1时waddr_gray_rd选择未经过同步过的信号waddr_gray_dly4；为0时表示选择经过同步的信号waddr_gray_dly4_1ff。
            Bit[17]：wt_abb_data_if中的fifo_rd_cnt信号同步清零使能信号。为1表示清零；为0表示不清零。
            Bit[17:16]建议使用默认值2'b00。
   UNION结构 ：无 */
#define WBBP_REDUNDAN_1_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91E6C)

/* 寄存器说明：
   详      述：冗余备份寄存器。
            Bit[0]:天线打开时，X模异频使能初值，X模本频使能初值为该信号的取反。0表示天线打开时X模下行前端先进入本频(默认)；1表示天线打开是X模下行前端先进入异频。
   UNION结构 ：无 */
#define WBBP_REDUNDAN_2_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91E70)

/* 寄存器说明：
   详      述：冗余备份寄存器。
   UNION结构 ：无 */
#define WBBP_REDUNDAN_3_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91E74)

/* 寄存器说明：
   详      述：冗余备份寄存器。
   UNION结构 ：无 */
#define WBBP_REDUNDAN_4_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91E78)

/* 寄存器说明：
   详      述：冗余备份寄存器。
   UNION结构 ：无 */
#define WBBP_REDUNDAN_5_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91E7C)

/* 寄存器说明：上报的rssi1天线1的统计值
 bit[31:25]  保留
 bit[24:0]   逻辑上报的rssi1天线1的统计值。
   UNION结构:  WBBP_RSSI1_DATA0_UNION */
#define WBBP_RSSI1_DATA0_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91E90)

/* 寄存器说明：上报的rssi1天线2的统计值
 bit[31:25]  保留
 bit[24:0]   逻辑上报的rssi1天线2的统计值。
   UNION结构:  WBBP_RSSI1_DATA1_UNION */
#define WBBP_RSSI1_DATA1_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91E94)

/* 寄存器说明：上报的rssi2天线1的统计值
 bit[31:25]  保留
 bit[24:0]   逻辑上报的rssi2天线1的统计值。
   UNION结构:  WBBP_RSSI2_DATA0_UNION */
#define WBBP_RSSI2_DATA0_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91E98)

/* 寄存器说明：上报的rssi2天线2的统计值
 bit[31:25]  保留
 bit[24:0]   逻辑上报的rssi2天线2的统计值。
   UNION结构:  WBBP_RSSI2_DATA1_UNION */
#define WBBP_RSSI2_DATA1_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91E9C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:0]   AT1 dbg采数上报。
             [11:0] Q路数据
             [23:12] I路数据
             [24] tds_data_vld
             [25] tds_ad_on1
             [26] 天线采数使能
   UNION结构:  WBBP_DBG_RPT_AT1_UNION */
#define WBBP_DBG_RPT_AT1_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91EA0)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:0]   AT2 dbg采数上报。
             [11:0] Q路数据
             [23:12] I路数据
             [24] tds_data_vld
             [25] tds_ad_on1
             [26] 天线采数使能
   UNION结构:  WBBP_DBG_RPT_AT2_UNION */
#define WBBP_DBG_RPT_AT2_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91EA4)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      下行W模和C模sc filter使能信号。0：关闭；1：打开。W模式下dl_c_scfilter_en或者多径的sc_filter使能都能够打开sc filter。
 bit[0]      下行C模模式选择。0，初始模式；1，正常模式。
   UNION结构:  WBBP_C_WORK_MODE_UNION */
#define WBBP_C_WORK_MODE_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91F00)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      C模下天线1档位切换指示脉冲。
   UNION结构:  WBBP_C_AAGC_STATE_CHANGE_AT1_UNION */
#define WBBP_C_AAGC_STATE_CHANGE_AT1_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91F04)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      C模下天线2档位切换指示脉冲。
   UNION结构:  WBBP_C_AAGC_STATE_CHANGE_AT2_UNION */
#define WBBP_C_AAGC_STATE_CHANGE_AT2_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91F08)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    DRSSI 0.25dB值，是DAGC8bit用于查找表求量化步阶MulFactor的ROM地址。AGC刚工作的时候，以此值作为初值。
   UNION结构:  WBBP_C_DRSSI_25DB_AT1_UNION */
#define WBBP_C_DRSSI_25DB_AT1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91F0C)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    DRSSI 0.25dB值，是DAGC8bit用于查找表求量化步阶MulFactor的ROM地址。AGC刚工作的时候，以此值作为初值。
   UNION结构:  WBBP_C_DRSSI_25DB_AT2_UNION */
#define WBBP_C_DRSSI_25DB_AT2_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91F10)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17]     C模本频指示切换控制脉冲。
 bit[16]     本异频切换类型。0，本频切换到异频；1，异频切换到本频。
 bit[15:12]  保留
 bit[11:0]   C模本频指示切换在base_cnt上的时刻，单位为chip。
             注：base_cnt计数从0chip开始记起。
   UNION结构:  WBBP_C_FREQ_SWITCH_CFG_UNION */
#define WBBP_C_FREQ_SWITCH_CFG_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91F14)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:0]   DSP配置RXIQ提前启动时间，用于和后续模块DRSSI在时间上对齐，配置精度为样点的整数倍。W模式要求配置值为17'd32。（V9为固定256个clk）
   UNION结构:  WBBP_DSP_RXIQ_AHEAD_TIME_UNION */
#define WBBP_DSP_RXIQ_AHEAD_TIME_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91F18)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  C模DRSSI统计在PCG或时隙内的结束时刻，单位chip。
             1X配置小于1536(十进制)。
             EVDO建议配置1648(十进制)。
 bit[15:11]  保留
 bit[10:0]   C模DRSSI统计在PCG或时隙内的起始时刻，单位chip。
             1X和EVDO建议配置0。
   UNION结构:  WBBP_C_DRSSI_TIME_UNION */
#define WBBP_C_DRSSI_TIME_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91F1C)

/* 寄存器说明：
   详      述：天线1 DRSSI统计的线性上报值。即一个统计周期内的I^2+Q^2累加值。
   UNION结构 ：无 */
#define WBBP_C_DRSSI_LINEAR_RPT_AT1_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x91F20)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   天线1 DRSSI上报线性值统计长度，单位chip。
   UNION结构:  WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT1_UNION */
#define WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT1_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x91F24)

/* 寄存器说明：
   详      述：天线2 DRSSI统计的线性上报值。即一个统计周期内的I^2+Q^2累加值。
   UNION结构 ：无 */
#define WBBP_C_DRSSI_LINEAR_RPT_AT2_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x91F28)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   天线2 DRSSI上报线性值统计长度，单位chip。
   UNION结构:  WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT2_UNION */
#define WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT2_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x91F2C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      采样纠偏检测步长强配使能，C模和强配功能下使用。
   UNION结构:  WBBP_DSP_TED_STEP_EN_UNION */
#define WBBP_DSP_TED_STEP_EN_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91F30)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      采样纠偏检测步长强配更新指示。
   UNION结构:  WBBP_DSP_TED_STEP_UPDATE_UNION */
#define WBBP_DSP_TED_STEP_UPDATE_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91F34)

/* 寄存器说明：
 bit[31:24]  天线2辅载波采样纠偏检测步长。8bit有符号数。
 bit[23:16]  天线2主载波采样纠偏检测步长。8bit有符号数。
 bit[15:8]   天线1辅载波采样纠偏检测步长。8bit有符号数。
 bit[7:0]    天线1主载波采样纠偏检测步长。8bit有符号数。
   UNION结构:  WBBP_DSP_TED_STEP_UNION */
#define WBBP_DSP_TED_STEP_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91F38)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      DSP强配采样偏差值使能。
   UNION结构:  WBBP_DSP_SC_DSP_CFG_EN_UNION */
#define WBBP_DSP_SC_DSP_CFG_EN_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91F3C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      DSP配置采样偏差值更新脉冲。
   UNION结构:  WBBP_DSP_SC_DSP_CFG_UPDATE_UNION */
#define WBBP_DSP_SC_DSP_CFG_UPDATE_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91F40)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  天线1辅载波DSP配置采样偏差值。
 bit[15:11]  保留
 bit[10:0]   天线1主载波DSP配置采样偏差值。
   UNION结构:  WBBP_DSP_SC_OFFSET_AT1_UNION */
#define WBBP_DSP_SC_OFFSET_AT1_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91F44)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  天线2辅载波DSP配置采样偏差值。
 bit[15:11]  保留
 bit[10:0]   天线2主载波DSP配置采样偏差值。
   UNION结构:  WBBP_DSP_SC_OFFSET_AT2_UNION */
#define WBBP_DSP_SC_OFFSET_AT2_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91F48)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      sc_filter模块的参数来源：
             1'b1：参数来源于sc_cal；
             1'b0：W参数来源于多径或强配，TDS和C模来源于强配。
 bit[7]      下行单TCXO异步fifo使能。
 bit[6]      频偏校正使能。
 bit[5]      频率校正NCO工作使能，TDS模式和非单TCXO模式下需要配置为0。
 bit[4]      强行配置频偏校正所用NCO频率值使能。
 bit[3]      DSP配置AFC频偏值使能。
 bit[2]      采样偏差换算工作使能。
 bit[1]      删加点功能打开标志：0，关闭删加点功能；1，为开启删加点功能，此时sc_cal模块的删加点计算功能打开。
 bit[0]      下行前端纠偏fifo前的base_cnt来源：
             0，选择base_cnt；
             1，选择base_cnt_abb。
             W和C配置1，TDS下必须配置为0。
   UNION结构:  WBBP_DSP_DLFE_SINGLE_TCXO_CFG_UNION */
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91F4C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      DSP配置AFC频偏值更新脉冲，当DSP配置AFC频偏值之后再配置更新脉冲，使频偏配置生效。
   UNION结构:  WBBP_DSP_DLFE_SINGLE_TCXO_UPDATE_UNION */
#define WBBP_DSP_DLFE_SINGLE_TCXO_UPDATE_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x91F50)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      频率校正NCO相位清零脉冲，可维可测使用。
 bit[0]      采样偏差换算积分器清零信号，可维可测使用。
   UNION结构:  WBBP_DSP_DLFE_SINGLE_TCXO_CLR_UNION */
#define WBBP_DSP_DLFE_SINGLE_TCXO_CLR_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x91F54)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   DSP配置AFC频偏值，16bit有符号数。
   UNION结构:  WBBP_DSP_SC_CAL_PARA1_UNION */
#define WBBP_DSP_SC_CAL_PARA1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91F58)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   DSP配置下行前端配置异频相对本频频率比Fc,inter/Fc（其中Fc,inter为异频频率），15bit无符号数。
   UNION结构:  WBBP_DSP_SC_CAL_PARA2_UNION */
#define WBBP_DSP_SC_CAL_PARA2_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91F5C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   DSP配置TCXO电压固定值，16bit无符号数。
   UNION结构:  WBBP_DSP_TCXO_VOL_UNION */
#define WBBP_DSP_TCXO_VOL_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91F60)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   该系数用于计算输入给NCO的输入频率。信号位宽为13U。
             W模式下配置为1118，C模式下配置为3459（W和C下的配置值由k=4计算得出，K改变的话该值需要改变，具体计算公式为k/fs*2^32）。
   UNION结构:  WBBP_DSP_FREQ_ERROR_NCO_FW_CFG_EN_UNION */
#define WBBP_DSP_FREQ_ERROR_NCO_FW_CFG_EN_ADDR        (SOC_BBP_WCDMA_BASE_ADDR + 0x91F64)

/* 寄存器说明：
   详      述：强行配置频偏校正所用NCO频率值。
   UNION结构 ：无 */
#define WBBP_DSP_FREQ_ERROR_NCO_FW_CFG_ADDR           (SOC_BBP_WCDMA_BASE_ADDR + 0x91F68)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:0]   DSP配置下行前端配置本频1/Fc值，18bit无符号数。软件配置公式为：2^29/Fc*K，其中Fc为下行载波频率，K为每bit表示的Hz数（可以是2、4或8）。
   UNION结构:  WBBP_DSP_SC_CAL_PARA3_UNION */
#define WBBP_DSP_SC_CAL_PARA3_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91F6C)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   tds模式下采样调整步长;17bit
   UNION结构:  WBBP_DL_TDS_SC_DLT_FSMP_UNION */
#define WBBP_DL_TDS_SC_DLT_FSMP_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91F70)

/* 寄存器说明：
   详      述：tds模式下采样调整初始偏差值;32bit
   UNION结构 ：无 */
#define WBBP_DL_TDS_SC_INI_FSMP_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91F74)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      dsp配置采样调整步长有效指示,为脉冲信号;
   UNION结构:  WBBP_DL_TDS_SC_DLT_VLD_UNION */
#define WBBP_DL_TDS_SC_DLT_VLD_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91F78)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      dsp配置采样初始偏差值有效指示,为脉冲信号;
   UNION结构:  WBBP_DL_TDS_SC_INI_VLD_UNION */
#define WBBP_DL_TDS_SC_INI_VLD_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91F7C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      dsp配置参数模式:
             1:直接根据vld信号锁存参数;
             0:需要根据ad_on的上升沿与vld信号共同锁存参数;
             默认值为1;
             
   UNION结构:  WBBP_DL_TDS_SC_FSMP_MOD_UNION */
#define WBBP_DL_TDS_SC_FSMP_MOD_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91F80)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      sc_cal模块在fifo几乎空，几乎满的异常删加点使能：
             0：关闭异常删加点功能；
             1：打开异常删加点功能。
             默认打开。
   UNION结构:  WBBP_DL_EN_UNION */
#define WBBP_DL_EN_ADDR                               (SOC_BBP_WCDMA_BASE_ADDR + 0x91F84)

/* 寄存器说明：
   详      述：sc_cal模块上报给dsp计算的采样纠偏值；根据rpt_ch_sel选择需要上报的通道；TDS模式在ad_on下降沿上报；W/X模上报实时值。
   UNION结构 ：无 */
#define WBBP_DL_TDS_SC_FSMP_RPT_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91F88)

/* 寄存器说明：sc_cal可维可测上报逻辑通道选择
 bit[31:2]   保留
 bit[1:0]    SC_CAL可维可测上报通道选择：
             2'b00：通道0（主天线主载波）
             2'b01：通道1（主天线辅载波）
             2'b10：通道2（辅天线主载波）
             2'b11：通道3（辅天线辅载波）
   UNION结构:  WBBP_DL_RPT_CH_SEL_UNION */
#define WBBP_DL_RPT_CH_SEL_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91F8C)

/* 寄存器说明：SC_CAL删加点个数上报
 bit[31:16]  sc_cal模块计算删点个数统计。
 bit[15:0]   sc_cal模块计算加点个数统计。
   UNION结构:  WBBP_DL_SC_CAL_NUM_RPT_UNION */
#define WBBP_DL_SC_CAL_NUM_RPT_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91F90)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      sc_cal模块计算删点个数统计清零。
 bit[0]      sc_cal模块计算加点个数统计清零。
   UNION结构:  WBBP_DL_SC_CAL_NUM_RPT_CLR_UNION */
#define WBBP_DL_SC_CAL_NUM_RPT_CLR_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x91F94)

/* 寄存器说明：通道0（主天线主载波） FIFO 异常空满上报
 bit[31:21]  保留
 bit[20:16]  通道0（主天线主载波） FIFO 读侧剩余数据个数
 bit[15:13]  保留
 bit[12:8]   通道0（主天线主载波） FIFO 写侧剩余数据个数
 bit[7:5]    保留
 bit[4]      通道0 （主天线主载波）FIFO 满标志:
             1'b0:FIFO不满；
             1'b1:FIFO满。
 bit[3:1]    保留
 bit[0]      通道0（主天线主载波） 异常空标志:
             1'b0:FIFO不异常空；
             1'b1:FIFO异常空。
   UNION结构:  WBBP_DL_FIFO0_EMPTY_FULL_RPT_UNION */
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91F98)

/* 寄存器说明：通道0（主天线主载波） FIFO 异常空满次数上报
 bit[31:24]  通道0（主天线主载波） FIFO满次数上报
 bit[23:16]  通道0（主天线主载波） FIFO空次数上报
 bit[15:8]   通道0（主天线主载波） FIFO将满次数上报
 bit[7:0]    通道0（主天线主载波） FIFO将空次数上报
   UNION结构:  WBBP_DL_FIFO0_EMPTY_FULL_NUM_UNION */
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91F9C)

/* 寄存器说明：通道1（主天线辅载波） FIFO 异常空满上报
 bit[31:21]  保留
 bit[20:16]  通道1（主天线辅载波） FIFO 读侧剩余数据个数
 bit[15:13]  保留
 bit[12:8]   通道0（主天线辅载波） FIFO 写侧剩余数据个数
 bit[7:5]    保留
 bit[4]      通道1 （主天线辅载波）FIFO 满标志:
             1'b0:FIFO不满；
             1'b1:FIFO满。
 bit[3:1]    保留
 bit[0]      通道1（主天线辅载波） 异常空标志:
             1'b0:FIFO不异常空；
             1'b1:FIFO异常空。
   UNION结构:  WBBP_DL_FIFO1_EMPTY_FULL_RPT_UNION */
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FA0)

/* 寄存器说明：通道1（主天线辅载波） FIFO 异常空满次数上报
 bit[31:24]  通道1（主天线辅载波） FIFO满次数上报
 bit[23:16]  通道1（主天线辅载波） FIFO空次数上报
 bit[15:8]   通道1（主天线辅载波） FIFO将满次数上报
 bit[7:0]    通道1（主天线辅载波） FIFO将空次数上报
   UNION结构:  WBBP_DL_FIFO1_EMPTY_FULL_NUM_UNION */
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FA4)

/* 寄存器说明：通道2（辅天线主载波） FIFO 异常空满上报
 bit[31:21]  保留
 bit[20:16]  通道2（辅天线主载波） FIFO 读侧剩余数据个数
 bit[15:13]  保留
 bit[12:8]   通道2（辅天线主载波） FIFO 写侧剩余数据个数
 bit[7:5]    保留
 bit[4]      通道2 （辅天线主载波）FIFO 满标志:
             1'b0:FIFO不满；
             1'b1:FIFO满。
 bit[3:1]    保留
 bit[0]      通道2（辅天线主载波） 异常空标志:
             1'b0:FIFO不异常空；
             1'b1:FIFO异常空。
   UNION结构:  WBBP_DL_FIFO2_EMPTY_FULL_RPT_UNION */
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FA8)

/* 寄存器说明：通道2（辅天线主载波） FIFO 异常空满次数上报
 bit[31:24]  通道2（辅天线主载波） FIFO满次数上报
 bit[23:16]  通道2（辅天线主载波） FIFO空次数上报
 bit[15:8]   通道2（辅天线主载波） FIFO将满次数上报
 bit[7:0]    通道2（辅天线主载波） FIFO将空次数上报
   UNION结构:  WBBP_DL_FIFO2_EMPTY_FULL_NUM_UNION */
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FAC)

/* 寄存器说明：通道3（辅天线辅载波） FIFO 异常空满上报
 bit[31:21]  保留
 bit[20:16]  通道3（辅天线辅载波） FIFO 读侧剩余数据个数
 bit[15:13]  保留
 bit[12:8]   通道3（辅天线辅载波） FIFO 写侧剩余数据个数
 bit[7:5]    保留
 bit[4]      通道3（辅天线辅载波）FIFO 满标志:
             1'b0:FIFO不满；
             1'b1:FIFO满。
 bit[3:1]    保留
 bit[0]      通道3（辅天线辅载波） 异常空标志:
             1'b0:FIFO不异常空；
             1'b1:FIFO异常空。
   UNION结构:  WBBP_DL_FIFO3_EMPTY_FULL_RPT_UNION */
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FB0)

/* 寄存器说明：通道3（辅天线辅载波） FIFO 异常空满次数上报
 bit[31:24]  通道3（辅天线辅载波） FIFO满次数上报
 bit[23:16]  通道3（辅天线辅载波） FIFO空次数上报
 bit[15:8]   通道3（辅天线辅载波） FIFO将满次数上报
 bit[7:0]    通道3（辅天线辅载波） FIFO将空次数上报
   UNION结构:  WBBP_DL_FIFO3_EMPTY_FULL_NUM_UNION */
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FB4)

/* 寄存器说明：FIFO清零信号
 bit[31:2]   保留
 bit[1]      FIFO异常空满上报状态清零信号:
             1'b0:FIFO异常空满不清零
             1'b1:FIFO异常空满清零
 bit[0]      FIFO清零电平信号:
             1'b0:FIFO不清零
             1'b1:FIFO清零
   UNION结构:  WBBP_DL_FIFO_CLR_UNION */
#define WBBP_DL_FIFO_CLR_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x91FB8)

/* 寄存器说明：W_BASE_CNT上报
 bit[31:17]  保留
 bit[16:0]   下行前端W_BASE_CNT上报，每个时隙边界后的第二个样点上报。
   UNION结构:  WBBP_W_BASE_CNT_RPT_UNION */
#define WBBP_W_BASE_CNT_RPT_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91FBC)

/* 寄存器说明：W主天线主载波dagc_ctrl上报
 bit[31:28]  保留
 bit[27:16]  W主天线主载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。
 bit[15:0]   W主天线主载波dagc_ctrl上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX1_MC1_DAGC_CTRL_RPT_UNION */
#define WBBP_W_RX1_MC1_DAGC_CTRL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FC0)

/* 寄存器说明：W主天线辅载波dagc_ctrl上报
 bit[31:28]  保留
 bit[27:16]  W主天线辅载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。
 bit[15:0]   W主天线辅载波dagc_ctrl上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX1_MC2_DAGC_CTRL_RPT_UNION */
#define WBBP_W_RX1_MC2_DAGC_CTRL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FC4)

/* 寄存器说明：W辅天线主载波dagc_ctrl上报
 bit[31:28]  保留
 bit[27:16]  W辅天线主载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。
 bit[15:0]   W辅天线主载波dagc_ctrl上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX2_MC1_DAGC_CTRL_RPT_UNION */
#define WBBP_W_RX2_MC1_DAGC_CTRL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FC8)

/* 寄存器说明：W辅天线主载波dagc_ctrl上报
 bit[31:28]  保留
 bit[27:16]  W辅天线辅载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。
 bit[15:0]   W辅天线辅载波dagc_ctrl上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX2_MC2_DAGC_CTRL_RPT_UNION */
#define WBBP_W_RX2_MC2_DAGC_CTRL_RPT_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x91FCC)

/* 寄存器说明：W aagc_ctrl上报
 bit[31:28]  保留
 bit[27:16]  W辅天线aagc_ctrl上报，每个符号边界后的第二个chip上报。
 bit[15:12]  保留
 bit[11:0]   W主天线aagc_ctrl上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_AAGC_CTRL_RPT_UNION */
#define WBBP_W_AAGC_CTRL_RPT_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91FD0)

/* 寄存器说明：W主天线主载波RSSI上报
 bit[31:11]  保留
 bit[10:0]   W主天线主载波rssi上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX1_MC1_RSSI_RPT_UNION */
#define WBBP_W_RX1_MC1_RSSI_RPT_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91FD4)

/* 寄存器说明：W主天线辅载波RSSI上报
 bit[31:11]  保留
 bit[10:0]   W主天线辅载波rssi上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX1_MC2_RSSI_RPT_UNION */
#define WBBP_W_RX1_MC2_RSSI_RPT_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91FD8)

/* 寄存器说明：W辅天线主载波RSSI上报
 bit[31:11]  保留
 bit[10:0]   W辅天线主载波rssi上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX2_MC1_RSSI_RPT_UNION */
#define WBBP_W_RX2_MC1_RSSI_RPT_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91FDC)

/* 寄存器说明：W辅天线主载波RSSI上报
 bit[31:11]  保留
 bit[10:0]   W辅天线辅载波rssi上报，每个符号边界后的第二个chip上报。
   UNION结构:  WBBP_W_RX2_MC2_RSSI_RPT_UNION */
#define WBBP_W_RX2_MC2_RSSI_RPT_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x91FE0)

/* 寄存器说明：W辅天线主载波RSSI上报
 bit[31:16]  保留
 bit[15:0]   WC NCO输入的频偏值上报（该频偏值来自SC CAL模块）
   UNION结构:  WBBP_WC_NCO_RPT_UNION */
#define WBBP_WC_NCO_RPT_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x91FE4)

/* 寄存器说明：W模ssi发送通道选择
 bit[31:14]  保留
 bit[13:12]  W下行辅天线异频SSI控制字通道选择。
             C模不配置。
             00：选择ch0；
             01：选择ch1；
             10：选择ch2；
             11：选择ch3；
 bit[11:10]  保留
 bit[9:8]    W下行辅天线本频SSI控制字通道选择。
             C模不配置。
             00：选择ch0；
             01：选择ch1；
             10：选择ch2；
             11：选择ch3；
 bit[7:6]    保留
 bit[5:4]    W下行主天线异频SSI控制字通道选择。
             C模不配置。
             00：选择ch0；
             01：选择ch1；
             10：选择ch2；
             11：选择ch3；
 bit[3:2]    保留
 bit[1:0]    W下行主天线本频SSI控制字通道选择。
             C模不配置。
             00：选择ch0；
             01：选择ch1；
             10：选择ch2；
             11：选择ch3；
   UNION结构:  WBBP_W_SSI_CH_SEL_UNION */
#define WBBP_W_SSI_CH_SEL_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x91FE8)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S2的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S2的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S1的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S1的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_0_UNION */
#define WBBP_WC_DC_REG_AT1_0_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91600)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S4的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S4的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S3的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S3的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_1_UNION */
#define WBBP_WC_DC_REG_AT1_1_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91604)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S6的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S6的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S5的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S5的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_2_UNION */
#define WBBP_WC_DC_REG_AT1_2_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91608)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S8的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S8的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S7的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S7的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_3_UNION */
#define WBBP_WC_DC_REG_AT1_3_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9160C)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S2的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S2的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S1的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S1的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_4_UNION */
#define WBBP_WC_DC_REG_AT1_4_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91610)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S4的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S4的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S3的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S3的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_5_UNION */
#define WBBP_WC_DC_REG_AT1_5_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91614)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S6的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S6的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S5的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S5的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_6_UNION */
#define WBBP_WC_DC_REG_AT1_6_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91618)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S8的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S8的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S7的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S7的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_7_UNION */
#define WBBP_WC_DC_REG_AT1_7_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9161C)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，8档AAGC S2的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S2的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S1的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S1的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_0_UNION */
#define WBBP_WC_DC_REG_AT2_0_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91620)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，8档AAGC S4的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S4的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S3的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S3的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_1_UNION */
#define WBBP_WC_DC_REG_AT2_1_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91624)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，8档AAGC S6的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S6的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S5的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S5的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_2_UNION */
#define WBBP_WC_DC_REG_AT2_2_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91628)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，8档AAGC S8的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S8的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S7的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S7的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_3_UNION */
#define WBBP_WC_DC_REG_AT2_3_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9162C)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S2的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S2的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S1的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S1的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_4_UNION */
#define WBBP_WC_DC_REG_AT2_4_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91630)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，5档AAGC S4的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，5档AAGC S4的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，5档AAGC S3的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，5档AAGC S3的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_5_UNION */
#define WBBP_WC_DC_REG_AT2_5_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91634)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，5档AAGC S6的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，5档AAGC S6的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，5档AAGC S5的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，5档AAGC S5的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_6_UNION */
#define WBBP_WC_DC_REG_AT2_6_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x91638)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，5档AAGC S8的DC配置值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，5档AAGC S8的DC配置值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，5档AAGC S7的DC配置值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，5档AAGC S7的DC配置值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_7_UNION */
#define WBBP_WC_DC_REG_AT2_7_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9163C)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S2的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S2的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S1的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S1的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_0_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_0_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91640)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S4的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S4的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S3的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S3的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_1_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_1_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91644)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S6的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S6的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S5的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S5的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_2_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_2_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91648)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，8档AAGC S8的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，8档AAGC S8的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，8档AAGC S7的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，8档AAGC S7的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_3_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_3_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9164C)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S2的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S2的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S1的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S1的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_4_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_4_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91650)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S4的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S4的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S3的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S3的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_5_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_5_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91654)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S6的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S6的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S5的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S5的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_6_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_6_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91658)

/* 寄存器说明：
 bit[31:24]  WC模 天线1 Q路，5档AAGC S8的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线1 I路，5档AAGC S8的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线1 Q路，5档AAGC S7的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线1 I路，5档AAGC S7的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT1_RPT_7_UNION */
#define WBBP_WC_DC_REG_AT1_RPT_7_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9165C)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，8档AAGC S2的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S2的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S1的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S1的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_0_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_0_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91660)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，8档AAGC S4的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S4的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S3的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S3的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_1_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_1_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91664)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，8档AAGC S6的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S6的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S5的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S5的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_2_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_2_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91668)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 I路，8档AAGC S8的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，8档AAGC S8的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，8档AAGC S7的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，8档AAGC S7的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_3_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_3_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9166C)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，5档AAGC S2的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，5档AAGC S2的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，5档AAGC S1的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，5档AAGC S1的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_4_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_4_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91670)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，5档AAGC S4的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，5档AAGC S4的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，5档AAGC S3的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，5档AAGC S3的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_5_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_5_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91674)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，5档AAGC S6的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，5档AAGC S6的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，5档AAGC S5的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，5档AAGC S5的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_6_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_6_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x91678)

/* 寄存器说明：
 bit[31:24]  WC模 天线2 Q路，5档AAGC S8的DC上报值，8bit有符号数。
 bit[23:16]  WC模 天线2 I路，5档AAGC S8的DC上报值，8bit有符号数。
 bit[15:8]   WC模 天线2 Q路，5档AAGC S7的DC上报值，8bit有符号数。
 bit[7:0]    WC模 天线2 I路，5档AAGC S7的DC上报值，8bit有符号数。
   UNION结构:  WBBP_WC_DC_REG_AT2_RPT_7_UNION */
#define WBBP_WC_DC_REG_AT2_RPT_7_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9167C)

/* 寄存器说明：WC模快速DC切档功能开关
 bit[31:9]   保留
 bit[8]      WC模软件DC直流初值配置使能。
             0：不使能。DC初值选择硬件根据档位选出的DC值。
             1：使能。DC初值选择软件接口配置的DC值。
             要dsp_dcoc_fast_en有效时，该初值才能生效。
             W模配置为0，C模配置为1，TDS模不涉及。
 bit[7:6]    保留
 bit[5:4]    硬件上报各档位DC直流值频率选择。
             00：按样点更新。
             01：按chip更新。
             10：按符号更新。
             11：reserved。
             W模使用，X模，TDS模不涉及。
 bit[3:1]    保留
 bit[0]      WC模DC快速收敛功能开关。
             0：关闭DC快速收敛功能；
             1：打开DC快速收敛功能，在去直流一阶段重新启动时，DC直流初值为软件配置的DC初始值，或者硬件根据档位选出的DC初始值。
             W模
             TDS模不支持该功能，需要关闭。
   UNION结构:  WBBP_WC_FAST_DC_EN_UNION */
#define WBBP_WC_FAST_DC_EN_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x91680)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      硬件各档位DC_REG加载软件值使能脉冲。
             W模使用，X模，TDS模不涉及。
   UNION结构:  WBBP_DC_REG_LOAD_BP_UNION */
#define WBBP_DC_REG_LOAD_BP_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x91684)

/* 寄存器说明：WC模DC配置值
 bit[31:24]  WC模 天线2 Q路DC配置值，8bit有符号数。
             配置值 = DC直流值/4，并限幅到
             [2^7-1,(-2^7+1)]范围内。
 bit[23:16]  WC模 天线2 I路DC配置值，8bit有符号数。
             配置值 = DC直流值/4，并限幅到
             [2^7-1,(-2^7+1)]范围内。
 bit[15:8]   WC模 天线1 Q路DC配置值，8bit有符号数。
             配置值 = DC直流值/4，并限幅到
             [2^7-1,(-2^7+1)]范围内。
 bit[7:0]    WC模 天线1 I路DC配置值，8bit有符号数。
             配置值 = DC直流值/4，并限幅到
             [2^7-1,(-2^7+1)]范围内。
   UNION结构:  WBBP_WC_DC_FAST_MANUAL_UNION */
#define WBBP_WC_DC_FAST_MANUAL_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x91688)

/* 寄存器说明：WC模快速AGC功能开关
 bit[31:1]   保留
 bit[0]      快速AGC切档使能。
             0：关闭快速AGC切档；
             1：打开快速AGC切档。
             W模使用。C/TDS不涉及。
   UNION结构:  WBBP_WC_FAST_AGC_EN_UNION */
#define WBBP_WC_FAST_AGC_EN_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9168C)

/* 寄存器说明：W模2ms解寻呼寄存器
 bit[31:1]   保留
 bit[0]      WDRX唤醒解寻呼模式下AGC自动打开使能。
             0：AGC只通过软件开关打开。
             1：WDRX唤醒解寻呼模式下，AGC在软件配置开关打开后，延迟等待到BBP自动打开脉冲才启动。
             W模使用。C/TDS不涉及。
   UNION结构:  WBBP_WDRX_AGC_OPEN_EN_UNION */
#define WBBP_WDRX_AGC_OPEN_EN_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x91690)



/***======================================================================***
                     (2/10) register_define_w_dlfe_dcsc
 ***======================================================================***/
/* 寄存器说明：
 bit[31:16]  天线2一帧内DAGC IQ数据饱和次数。
 bit[15:0]   天线1一帧内DAGC IQ数据饱和次数。
   UNION结构:  WBBP_WAGC_SAT_NUM_DCSC_UNION */
#define WBBP_WAGC_SAT_NUM_DCSC_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x92268)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
 bit[8:0]    刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
   UNION结构:  WBBP_INIT_AGC_CFG_AT1_DCSC_UNION */
#define WBBP_INIT_AGC_CFG_AT1_DCSC_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x92404)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
 bit[8:0]    刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
   UNION结构:  WBBP_INIT_AGC_CFG_AT2_DCSC_UNION */
#define WBBP_INIT_AGC_CFG_AT2_DCSC_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x92408)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
 bit[8:0]    刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。
   UNION结构:  WBBP_INTER_AGC_CFG_AT1_DCSC_UNION */
#define WBBP_INTER_AGC_CFG_AT1_DCSC_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x9240C)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
 bit[8:0]    刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。
   UNION结构:  WBBP_INTER_AGC_CFG_AT2_DCSC_UNION */
#define WBBP_INTER_AGC_CFG_AT2_DCSC_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x92410)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG0_AT1_DCSC_UNION */
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_DCSC_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x92A1C)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。
 bit[23:17]  保留
 bit[16]     RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。
 bit[15:9]   保留
 bit[8:0]    RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_UNION */
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x92A20)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG0_AT2_DCSC_UNION */
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_DCSC_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x92A24)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。
 bit[23:17]  保留
 bit[16]     RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。
 bit[15:9]   保留
 bit[8:0]    RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。
   UNION结构:  WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_UNION */
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_ADDR         (SOC_BBP_WCDMA_BASE_ADDR + 0x92A28)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   BBP上报天线口RSSI值（单载波），0.125dB精度。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[8:0]    BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
   UNION结构:  WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_UNION */
#define WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_ADDR          (SOC_BBP_WCDMA_BASE_ADDR + 0x92A2C)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:9]   BBP上报天线口RSSI值（单载波），0.125dB精度。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
 bit[8:0]    BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。
   UNION结构:  WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_UNION */
#define WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_ADDR          (SOC_BBP_WCDMA_BASE_ADDR + 0x92A30)



/***======================================================================***
                     (3/10) register_define_wt_mctrl
 ***======================================================================***/
/* 寄存器说明：DBG数据进行工作使能
 bit[31:5]   保留
 bit[4]      dbg时钟选择
 bit[3:2]    保留
 bit[1]      W模式上、下行数据选择：
             0：选择下行数据；
             1：选择上行数据；
 bit[0]      W模式与TDS模式数据采集使能：
             0：不使能；
             1：使能；
   UNION结构:  WBBP_WT_DBG_EN_UNION */
#define WBBP_WT_DBG_EN_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x96000)

/* 寄存器说明：ZSP1中断标志寄存器
 bit[31:8]   保留
 bit[7]      发送完成中断标志：0此中断未产生；1 此中断产生。
 bit[6]      发送存储器全空中断标志：0此中断未产生；1 此中断产生。
 bit[5]      发送存储器半空中断标志：0此中断未产生；1 此中断产生。
 bit[4]      保留
 bit[3]      AD_STOP中断时，接收数据保存位置：0 前半个FIFO；1 后半个FIFO。
 bit[2]      接收数据存储器完成中断标志，同时是其它模块上报参数有效中断标志：0此中断未产生；1 此中断产生。
 bit[1]      接收数据存储器全满中断标志：0此中断未产生；1 此中断产生。
 bit[0]      接收数据存储器半满中断标志：0此中断未产生；1 此中断产生。
   UNION结构:  WBBP_ZSP_INT_FLAG_UNION */
#define WBBP_ZSP_INT_FLAG_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x96004)

/* 寄存器说明：接收存储器地址寄存器
 bit[31:16]  保留
 bit[15:0]   接收数据存储器地址；当AD接收结束时，指示接收存储器的当前地址。
   UNION结构:  WBBP_RX_ADDR_UNION */
#define WBBP_RX_ADDR_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x96008)

/* 寄存器说明：ZSP1中断屏蔽寄存器
 bit[31:7]   保留
 bit[6]      发送完成中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。
 bit[5]      发送存储器全满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。
 bit[4]      发送存储器半满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。
 bit[3]      保留
 bit[2]      接收完成中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。
 bit[1]      接收存储器全满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。
 bit[0]      接收存储器半满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。
   UNION结构:  WBBP_ZSP_INT_MASK_UNION */
#define WBBP_ZSP_INT_MASK_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x96010)

/* 寄存器说明：接口中断信号清除寄存器
 bit[31:7]   保留
 bit[6]      发送完成中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。
 bit[5]      发送存储器全满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。
 bit[4]      发送存储器半满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。
 bit[3]      保留
 bit[2]      接收完成中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。
 bit[1]      接收存储器全满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。
 bit[0]      接收存储器半满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。
   UNION结构:  WBBP_INT_CLEAR_UNION */
#define WBBP_INT_CLEAR_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x96014)

/* 寄存器说明：接口中断信号告警寄存器
 bit[31:7]   保留
 bit[6]      发送完成中断告警位：
             0不告警此中断；
             1告警此中断。
 bit[5]      发送存储器全满中断告警位：
             0不告警此中断；
             1告警此中断。
 bit[4]      发送存储器半满中断告警位：
             0不告警此中断；
             1告警此中断。
 bit[3]      保留
 bit[2]      接收完成中断告警位：
             0不告警此中断；
             1告警此中断。
 bit[1]      接收存储器全满中断告警位：
             0不告警此中断；
             1告警此中断。
 bit[0]      接收存储器半满中断告警位：
             0不告警此中断；
             1告警此中断。
   UNION结构:  WBBP_INT_ALARM_UNION */
#define WBBP_INT_ALARM_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x96018)

/* 寄存器说明：上行memory和rrc输出信号
 bit[31:16]  [31]为上行W与TDS模式选择信号，0为W，1为TDS;
             [30]为tds输入的da_on信号；
             [29:28]为memory输出的da_on/dvld；
             [27:16]为memory的输出I路数据高12bit；
 bit[15:0]   [15]为下行W与TDS模式选择信号，0为W，1为TDS;
             [14:12]为dlfe输出的ad_on1/ad_on/dvld；
             [11:0]为dlfe输出I路数据的高12bit；
   UNION结构:  WBBP_MEM_RRC_UNION */
#define WBBP_MEM_RRC_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x9601C)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:8]    ABB
 bit[7:5]    保留
 bit[4]      下行采样数据格式标志
             
 bit[3:1]    保留
 bit[0]      上行采样数据格式标志
             
   UNION结构:  WBBP_ABB_CODE_UNION */
#define WBBP_ABB_CODE_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x96030)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:12]  为了调整定时偏差，使
 bit[11:9]   保留
 bit[8]      定时偏差调整功能打开使能，高电平有效。tds 专用。
 bit[7:5]    保留
 bit[4]      定时偏差调整功能通道选择，
 bit[3:1]    保留
 bit[0]      接收通道个数：
             
   UNION结构:  WBBP_ABB_DLY_UNION */
#define WBBP_ABB_DLY_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x96034)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6:4]    ABB
 bit[3:1]    保留
 bit[0]      ABB
   UNION结构:  WBBP_ABB_TRX_LOOP_UNION */
#define WBBP_ABB_TRX_LOOP_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x96038)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12]     RX 
 bit[11:9]   保留
 bit[8]      RX 
 bit[7:5]    保留
 bit[4]      RX 
 bit[3:1]    保留
 bit[0]      RX 
   UNION结构:  WBBP_ABB_FIFO_DBG_UNION */
#define WBBP_ABB_FIFO_DBG_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9603C)

/* 寄存器说明：
 bit[31:16]  U&amp;TDS
 bit[15:0]   
   UNION结构:  WBBP_SHARE_MEM_CTRL_UNION */
#define WBBP_SHARE_MEM_CTRL_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x96060)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U&amp;TDS
 bit[15:0]   U&amp;TDS
   UNION结构:  WBBP_SHARE_ROM_CTRL_UNION */
#define WBBP_SHARE_ROM_CTRL_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x96064)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:12]  IMI ADDR
 bit[11:10]  保留
 bit[9:8]    ULFE
 bit[7:6]    保留
 bit[5:4]    RST
 bit[3]      保留
 bit[2:0]    CLK
   UNION结构:  WBBP_SYS_RST_UNION */
#define WBBP_SYS_RST_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x96068)

/* 寄存器说明：
   详      述：MCTRL
   UNION结构 ：无 */
#define WBBP_MCTR_REDUND1_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9606C)

/* 寄存器说明：
   详      述：MCTRL
   UNION结构 ：无 */
#define WBBP_MCTR_REDUND2_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x96070)

/* 寄存器说明：
   详      述：MCTRL
   UNION结构 ：无 */
#define WBBP_MCTR_REDUND3_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x96074)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6]      FIFO_1
 bit[5]      FIFO_1
 bit[4]      fifo_1
 bit[3]      保留
 bit[2]      FIFO_0
 bit[1]      FIFO_0
 bit[0]      fifo_0
   UNION结构:  WBBP_DATA_FIFO_RST_UNION */
#define WBBP_DATA_FIFO_RST_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x96078)



/***======================================================================***
                     (4/10) register_define_w_ulfe_mem
 ***======================================================================***/
/* 寄存器说明：APT高增益档位功率补偿RAM
 bit[31:24]  保留
 bit[23:16]  每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。
             
 bit[15:8]   保留
 bit[7:0]    每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。
             
   UNION结构:  WBBP_APT_COMP_H_RAM_UNION */
#define WBBP_APT_COMP_H_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C000)
#define WBBP_APT_COMP_H_RAM_MEMDEPTH  (16)

/* 寄存器说明：APT中增益档位功率补偿RAM
 bit[31:24]  保留
 bit[23:16]  每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。
             
 bit[15:8]   保留
 bit[7:0]    每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。
             
   UNION结构:  WBBP_APT_COMP_M_RAM_UNION */
#define WBBP_APT_COMP_M_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C040)
#define WBBP_APT_COMP_M_RAM_MEMDEPTH  (16)

/* 寄存器说明：APT低增益档位功率补偿RAM
 bit[31:24]  保留
 bit[23:16]  每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。
             
 bit[15:8]   保留
 bit[7:0]    每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。
             
   UNION结构:  WBBP_APT_COMP_L_RAM_UNION */
#define WBBP_APT_COMP_L_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C080)
#define WBBP_APT_COMP_L_RAM_MEMDEPTH  (16)

/* 寄存器说明：高增益档位APT控制字RAM
 bit[31:25]  保留
 bit[24:16]  存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。
 bit[15:9]   保留
 bit[8:0]    存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。
   UNION结构:  WBBP_APT_H_RAM_UNION */
#define WBBP_APT_H_RAM_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9C0C0)
#define WBBP_APT_H_RAM_MEMDEPTH  (16)

/* 寄存器说明：中增益档位APT控制字RAM
 bit[31:25]  保留
 bit[24:16]  存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。
 bit[15:9]   保留
 bit[8:0]    存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。
   UNION结构:  WBBP_APT_M_RAM_UNION */
#define WBBP_APT_M_RAM_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9C100)
#define WBBP_APT_M_RAM_MEMDEPTH  (16)

/* 寄存器说明：低增益档位APT控制字RAM
 bit[31:25]  保留
 bit[24:16]  存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。
 bit[15:9]   保留
 bit[8:0]    存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。
   UNION结构:  WBBP_APT_L_RAM_UNION */
#define WBBP_APT_L_RAM_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9C140)
#define WBBP_APT_L_RAM_MEMDEPTH  (16)

/* 寄存器说明：高增益PA VBIAS1控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用)
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用)
             
   UNION结构:  WBBP_PAVBIAS1_H_RAM_UNION */
#define WBBP_PAVBIAS1_H_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C180)
#define WBBP_PAVBIAS1_H_RAM_MEMDEPTH  (16)

/* 寄存器说明：中增益PA VBIAS1控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用)
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用)
             
   UNION结构:  WBBP_PAVBIAS1_M_RAM_UNION */
#define WBBP_PAVBIAS1_M_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C1C0)
#define WBBP_PAVBIAS1_M_RAM_MEMDEPTH  (16)

/* 寄存器说明：低增益PA VBIAS1控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用)
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用)
             
   UNION结构:  WBBP_PAVBIAS1_L_RAM_UNION */
#define WBBP_PAVBIAS1_L_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C200)
#define WBBP_PAVBIAS1_L_RAM_MEMDEPTH  (16)

/* 寄存器说明：高增益PA VBIAS2控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。
             
   UNION结构:  WBBP_PAVBIAS2_H_RAM_UNION */
#define WBBP_PAVBIAS2_H_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C240)
#define WBBP_PAVBIAS2_H_RAM_MEMDEPTH  (16)

/* 寄存器说明：中增益PA VBIAS2控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。
             
   UNION结构:  WBBP_PAVBIAS2_M_RAM_UNION */
#define WBBP_PAVBIAS2_M_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C280)
#define WBBP_PAVBIAS2_M_RAM_MEMDEPTH  (16)

/* 寄存器说明：低增益PA VBIAS2控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。
             
   UNION结构:  WBBP_PAVBIAS2_L_RAM_UNION */
#define WBBP_PAVBIAS2_L_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C2C0)
#define WBBP_PAVBIAS2_L_RAM_MEMDEPTH  (16)

/* 寄存器说明：高增益PA VBIAS3控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。
             
   UNION结构:  WBBP_PAVBIAS3_H_RAM_UNION */
#define WBBP_PAVBIAS3_H_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C300)
#define WBBP_PAVBIAS3_H_RAM_MEMDEPTH  (16)

/* 寄存器说明：中增益PA VBIAS3控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。
             
   UNION结构:  WBBP_PAVBIAS3_M_RAM_UNION */
#define WBBP_PAVBIAS3_M_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C340)
#define WBBP_PAVBIAS3_M_RAM_MEMDEPTH  (16)

/* 寄存器说明：低增益PA VBIAS3控制字RAM
 bit[31:25]  保留
 bit[24:16]  每个地址位宽18比特，用于存放两个PA VBIAS值。
             
 bit[15:9]   保留
 bit[8:0]    每个地址位宽18比特，用于存放两个PA VBIAS值。
             
   UNION结构:  WBBP_PAVBIAS3_L_RAM_UNION */
#define WBBP_PAVBIAS3_L_RAM_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9C380)
#define WBBP_PAVBIAS3_L_RAM_MEMDEPTH  (16)

/* 寄存器说明：高增益PA非线性功率补偿RAM
 bit[31:24]  保留
 bit[23:16]  每个地址位宽16比特，用于存放两个有符号功率值。
             
 bit[15:8]   保留
 bit[7:0]    每个地址位宽16比特，用于存放两个有符号功率值。
             
   UNION结构:  WBBP_PAPOWCOMP_H_RAM_UNION */
#define WBBP_PAPOWCOMP_H_RAM_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9C3C0)
#define WBBP_PAPOWCOMP_H_RAM_MEMDEPTH  (16)

/* 寄存器说明：中增益PA非线性功率补偿RAM
 bit[31:24]  保留
 bit[23:16]  每个地址位宽16比特，用于存放两个有符号功率值。
             
 bit[15:8]   保留
 bit[7:0]    每个地址位宽16比特，用于存放两个有符号功率值。
             
   UNION结构:  WBBP_PAPOWCOMP_M_RAM_UNION */
#define WBBP_PAPOWCOMP_M_RAM_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9C400)
#define WBBP_PAPOWCOMP_M_RAM_MEMDEPTH  (16)

/* 寄存器说明：低增益PA非线性功率补偿RAM
 bit[31:24]  保留
 bit[23:16]  每个地址位宽16比特，用于存放两个有符号功率值。
             
 bit[15:8]   保留
 bit[7:0]    每个地址位宽16比特，用于存放两个有符号功率值。
             
   UNION结构:  WBBP_PAPOWCOMP_L_RAM_UNION */
#define WBBP_PAPOWCOMP_L_RAM_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9C440)
#define WBBP_PAPOWCOMP_L_RAM_MEMDEPTH  (16)

/* 寄存器说明：高增益时RF和DBB回退控制字RAM
 bit[31:28]  保留
 bit[27:24]  对应PA中增益,1控制字温补功率索引值(0~13)
 bit[23:8]   对应PA高增益,16比特RF控制字
 bit[7:0]    对应PA高增益,8比特数字功率回退值
   UNION结构:  WBBP_POW_ATTEN_H_RAM_UNION */
#define WBBP_POW_ATTEN_H_RAM_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9C6C0)
#define WBBP_POW_ATTEN_H_RAM_MEMDEPTH  (88)

/* 寄存器说明：中增益时RF和DBB回退控制字RAM
 bit[31:28]  保留
 bit[27:24]  对应PA中增益,1控制字温补功率索引值(0~13)
 bit[23:8]   对应PA中增益,16比特RF控制字
 bit[7:0]    对应PA中增益,8比特数字功率回退值
   UNION结构:  WBBP_POW_ATTEN_M_RAM_UNION */
#define WBBP_POW_ATTEN_M_RAM_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9C820)
#define WBBP_POW_ATTEN_M_RAM_MEMDEPTH  (88)

/* 寄存器说明：低增益时RF和DBB回退控制字RAM
 bit[31:28]  保留
 bit[27:24]  对应PA低增益,控制字温补功率索引值(0~13)
 bit[23:8]   对应PA低增益,16比特RF控制字
 bit[7:0]    对应PA低增益,8比特数字功率回退值
   UNION结构:  WBBP_POW_ATTEN_L_RAM_UNION */
#define WBBP_POW_ATTEN_L_RAM_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9C980)
#define WBBP_POW_ATTEN_L_RAM_MEMDEPTH  (88)

/* 寄存器说明：DPD补偿表
 bit[31:24]  保留
 bit[23:12]  DPD补偿Q路系数
 bit[11:0]   DPD补偿I路系数
   UNION结构:  WBBP_DPD_RAM1_UNION */
#define WBBP_DPD_RAM1_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x9CAE0)
#define WBBP_DPD_RAM1_MEMDEPTH  (256)



/***======================================================================***
                     (5/10) register_define_w_papd
 ***======================================================================***/
/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    2'b01，DSP强制PA增益为高；2'b10，DSP强制PA增益为中；2'b11，DSP强制PA增益为低；其他，由BBP自行控制。
   UNION结构:  WBBP_DSP_PA_MODEL_UNION */
#define WBBP_DSP_PA_MODEL_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D000)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:12]  PA初始增益控制字，根据射频器件配置。
 bit[11:10]  保留
 bit[9:8]    PA低增益控制字，根据射频器件配置。Infineon低增益为2'b11。
 bit[7:6]    保留
 bit[5:4]    PA中增益控制字，根据射频器件配置。Infineon中增益为2'b01。
 bit[3:2]    保留
 bit[1:0]    PA高增益控制字，根据射频器件配置。Infineon高增益为2'b00。
   UNION结构:  WBBP_PA_CTRL_WORD_UNION */
#define WBBP_PA_CTRL_WORD_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D004)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:18]  当PA处于低增益模式下PA的增益大小，单位0.1dB，无符号数。
 bit[17:9]   当PA处于中增益模式下PA的增益大小，单位0.1dB，无符号数。
 bit[8:0]    当PA处于高增益模式下PA的增益大小，单位0.1dB，无符号数。
   UNION结构:  WBBP_W_TX_PA_GAIN_UNION */
#define WBBP_W_TX_PA_GAIN_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D008)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA从中增益到高增益的切换门限，二进制补码。
 bit[15:11]  保留
 bit[10:0]   PA从高增益到中增益的切换门限，二进制补码。
   UNION结构:  WBBP_PA_HM_THRESHOLD_UNION */
#define WBBP_PA_HM_THRESHOLD_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D00C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA从低增益到中增益的切换门限，二进制补码。支持PA高、中两档模式时配置成0x400。
 bit[15:11]  保留
 bit[10:0]   PA从中增益到低增益的切换门限，二进制补码。支持PA高、中两档模式时配置成0x400。
   UNION结构:  WBBP_PA_ML_THRESHOLD_UNION */
#define WBBP_PA_ML_THRESHOLD_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D010)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA中增益表最小地址对应的功率取负，二进制补码。
 bit[15:11]  保留
 bit[10:0]   PA高增益表最小地址对应的功率取负，二进制补码。
   UNION结构:  WBBP_PA_HM_MODE_UNION */
#define WBBP_PA_HM_MODE_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9D014)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   PA低增益表最小地址对应的功率取负，二进制补码。
   UNION结构:  WBBP_PA_L_MODE_UNION */
#define WBBP_PA_L_MODE_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9D018)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    单板功率频率补偿值，单位0.1dBm。由于单板功率的偏差造成发射功率的偏差。DSP根据当前的单板的频率偏差信息，选择偏差值，配置给BBP；BBP中，与发射功率相加补偿后，查APC表。此值需在对单板进行测试后确定。
   UNION结构:  WBBP_PC_DELTA_POW_FREQ_UNION */
#define WBBP_PC_DELTA_POW_FREQ_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D01C)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      apt强制更新脉冲，仅用于强配APT控制字。每次写1产生一个单时钟脉冲，自清零
 bit[7:5]    保留
 bit[4]      为了提供满足不同PA的APT控制要求，PA电压控制模式可进行选择。0，PDM配置；1，MIPI口配置。
 bit[3:1]    保留
 bit[0]      0，选择PDM控制输出；1，选择PWM控制输出。
   UNION结构:  WBBP_APT_MODE_SEL_UNION */
#define WBBP_APT_MODE_SEL_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D020)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     PA APT功能生效开关，高电平有效，该开关有效时，PA APT功能可以进行正常工作，否则PDM脉冲一直为0。
 bit[15:0]   保留
   UNION结构:  WBBP_DSP_APT_ACTIVE_EN_UNION */
#define WBBP_DSP_APT_ACTIVE_EN_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D024)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      PA供电电压强制配置使能，电平信号，该功能有效时，PA电压控制值由dsp_apt_config_value决定。
 bit[7]      保留
 bit[6:0]    PA供电电压强制配置值，默认值为0。无符号数。
   UNION结构:  WBBP_DSP_APT_CONFIG_UNION */
#define WBBP_DSP_APT_CONFIG_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9D028)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA为高档位时，用于查PA非线性补偿表的offset值，单位0.1dBm，有符号数。
 bit[15:11]  保留
 bit[10:0]   PA为中档位时，用于查PA非线性补偿表的offset值，单位0.1dBm，有符号数。
   UNION结构:  WBBP_PACOMP_OFFSET_HM_UNION */
#define WBBP_PACOMP_OFFSET_HM_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D02C)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   PA为低档位时，用于查PA非线性补偿表的offset值，单位0.1dBm，有符号数。
   UNION结构:  WBBP_PACOMP_OFFSET_L_UNION */
#define WBBP_PACOMP_OFFSET_L_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D030)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   PA工作在高增益模式时的增益补偿值，有符号补码数，单位0.1dB。
             DSP根据当前的频段信息和温度信息，选择偏差值，配置给BBP；BBP将此值与发射功率相加后，查APC表。此值需在不同的工作频段下进行单板测试后确定。
   UNION结构:  WBBP_PA_H_COMP_UNION */
#define WBBP_PA_H_COMP_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9D034)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   PA工作在中增益模式时的增益补偿值，有符号补码数，单位0.1dB。
             DSP根据当前的频段信息和温度信息，选择偏差值，配置给BBP；BBP将此值与发射功率相加后，查APC表。此值需在不同的工作频段下进行单板测试后确定。
   UNION结构:  WBBP_PA_M_COMP_UNION */
#define WBBP_PA_M_COMP_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9D038)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   PA工作在低增益模式时的增益补偿值，有符号补码数，单位0.1dB。
             DSP根据当前的频段信息和温度信息，选择偏差值，配置给BBP；BBP将此值与发射功率相加后，查APC表。此值需在不同的工作频段下进行单板测试后确定。
   UNION结构:  WBBP_PA_L_COMP_UNION */
#define WBBP_PA_L_COMP_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9D03C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA从中增益到高增益的功率补偿，二进制补码。
 bit[15:11]  保留
 bit[10:0]   PA从高增益到中增益的功率补偿，二进制补码。
   UNION结构:  WBBP_DSP_POW_COMP_SLOT1A_UNION */
#define WBBP_DSP_POW_COMP_SLOT1A_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D040)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA从低增益到中增益的功率补偿，二进制补码。
 bit[15:11]  保留
 bit[10:0]   PA从中增益到低增益的功率补偿，二进制补码。
   UNION结构:  WBBP_DSP_POW_COMP_SLOT1B_UNION */
#define WBBP_DSP_POW_COMP_SLOT1B_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D044)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA中切高后第二时隙功率补偿 
 bit[15:11]  保留
 bit[10:0]   PA高切中后第二时隙功率补偿 
   UNION结构:  WBBP_DSP_POW_COMP_SLOT2A_UNION */
#define WBBP_DSP_POW_COMP_SLOT2A_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D048)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA低切中后第二时隙功率补偿 
 bit[15:11]  保留
 bit[10:0]   PA中切低后第二时隙功率补偿 
   UNION结构:  WBBP_DSP_POW_COMP_SLOT2B_UNION */
#define WBBP_DSP_POW_COMP_SLOT2B_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D04C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA中切高后第三时隙功率补偿 
 bit[15:11]  保留
 bit[10:0]   PA高切中后第三时隙功率补偿 
   UNION结构:  WBBP_DSP_POW_COMP_SLOT3A_UNION */
#define WBBP_DSP_POW_COMP_SLOT3A_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D050)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA低切中后第三时隙功率补偿 
 bit[15:11]  保留
 bit[10:0]   PA中切低后第三时隙功率补偿 
   UNION结构:  WBBP_DSP_POW_COMP_SLOT3B_UNION */
#define WBBP_DSP_POW_COMP_SLOT3B_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D054)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA中切高后第四时隙功率补偿 
 bit[15:11]  保留
 bit[10:0]   PA高切中后第四时隙功率补偿 
   UNION结构:  WBBP_DSP_POW_COMP_SLOT4A_UNION */
#define WBBP_DSP_POW_COMP_SLOT4A_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D058)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  PA低切中后第四时隙功率补偿 
 bit[15:11]  保留
 bit[10:0]   PA中切低后第四时隙功率补偿 
   UNION结构:  WBBP_DSP_POW_COMP_SLOT4B_UNION */
#define WBBP_DSP_POW_COMP_SLOT4B_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D05C)

/* 寄存器说明：
 bit[31]     DSP强制衰减使能信号。
 bit[30:23]  保留
 bit[22:16]  DSP强制DBB衰减补偿增益。取值范围[0,80]，超过80按80处理。精度0.1dB。
             0表示数字功率增加1dB，1表示增加0.9dB，以此类推，取值每增加1，功率增加值减少0.1dB，10表示增加0dB，11表示减少0.1dB，……，80表示减少7dB。
 bit[15:0]   DSP强制射频增益衰减控制字。无符号数。
   UNION结构:  WBBP_DSP_W_TX_APC_ATTEN_UNION */
#define WBBP_DSP_W_TX_APC_ATTEN_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D060)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    RFCMOS方案射频增益控制字对应SSI地址。
   UNION结构:  WBBP_W_TX_RF_ATTEN_ADDR_UNION */
#define WBBP_W_TX_RF_ATTEN_ADDR_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D064)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      温度补偿更新指示,当软件刷新PA温补,控制字温补,PD温补寄存器时,先将本比特置1,刷新完成后将本比特置0.
 bit[3:0]    保留
   UNION结构:  WBBP_RF_DC_OFFSET_EN_UNION */
#define WBBP_RF_DC_OFFSET_EN_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D068)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24:23]  PA控制字上报，无符号数
 bit[22:16]  RFCMOS数字回退功率上报，单位0.1dB.取值范围[0,80],对应回退功率范围[增加1dB,减少7dB]
 bit[15:0]   RF控制字上报，无符号数
   UNION结构:  WBBP_W_RF_REPORT_UNION */
#define WBBP_W_RF_REPORT_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9D06C)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     ATTEN控制字温度补偿功率强配使能.
 bit[23]     保留
 bit[22:16]  ATTEN控制字温度补偿功率强配值,有符号数,单位0.1dB
 bit[15:9]   保留
 bit[8]      PA VBIAS控制字强配使能
 bit[7:0]    PA VBIAS控制字强配值
   UNION结构:  WBBP_DSP_PA_VBIAS_CONFIG_UNION */
#define WBBP_DSP_PA_VBIAS_CONFIG_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D070)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:8]   RF控制字温度补偿上报,有符号数,单位0.1dB
 bit[7:0]    PA VBIAS控制字上报,无符号数.
   UNION结构:  WBBP_W_PA_REPORT_UNION */
#define WBBP_W_PA_REPORT_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9D074)

/* 寄存器说明：
 bit[31]     保留
 bit[30:24]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[23]     保留
 bit[22:16]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[15]     保留
 bit[14:8]   RF控制字温度补偿功率,有符号数,0.1dB
 bit[7]      保留
 bit[6:0]    RF控制字温度补偿功率,有符号数,0.1dB
   UNION结构:  WBBP_TEMP_COMP0_3_UNION */
#define WBBP_TEMP_COMP0_3_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D078)

/* 寄存器说明：
 bit[31]     保留
 bit[30:24]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[23]     保留
 bit[22:16]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[15]     保留
 bit[14:8]   RF控制字温度补偿功率,有符号数,0.1dB
 bit[7]      保留
 bit[6:0]    RF控制字温度补偿功率,有符号数,0.1dB
   UNION结构:  WBBP_TEMP_COMP4_7_UNION */
#define WBBP_TEMP_COMP4_7_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D07C)

/* 寄存器说明：
 bit[31]     保留
 bit[30:24]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[23]     保留
 bit[22:16]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[15]     保留
 bit[14:8]   RF控制字温度补偿功率,有符号数,0.1dB
 bit[7]      保留
 bit[6:0]    RF控制字温度补偿功率,有符号数,0.1dB
   UNION结构:  WBBP_TEMP_COMP8_11_UNION */
#define WBBP_TEMP_COMP8_11_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9D080)

/* 寄存器说明：
 bit[31]     保留
 bit[30:24]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[23]     保留
 bit[22:16]  RF控制字温度补偿功率,有符号数,0.1dB
 bit[15]     保留
 bit[14:8]   RF控制字温度补偿功率,有符号数,0.1dB
 bit[7]      保留
 bit[6:0]    RF控制字温度补偿功率,有符号数,0.1dB
   UNION结构:  WBBP_TEMP_COMP12_15_UNION */
#define WBBP_TEMP_COMP12_15_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9D084)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      软件强配dmpr功率使能
 bit[7:6]    保留
 bit[5:0]    软件强配dmpr功率值,有符号数,单位 0.1dB.
   UNION结构:  WBBP_DSP_DMPR_CONFIG_UNION */
#define WBBP_DSP_DMPR_CONFIG_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D088)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    上行通路开关控制。2'b10，表示DSP强制上行通路关闭；2'b11，表示DSP强制上行通路打开；其他，表示上行通路不受DSP控制，而由上行调制模块控制。
             此寄存器同时控制上行PA、RF等的开关。也即如果配置为2'b10，表示上行RF、PA等同时关闭。
   UNION结构:  WBBP_TX_SHDN_CTRL_UNION */
#define WBBP_TX_SHDN_CTRL_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D08C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    上行RF开关控制。2'b10，表示DSP强制上行RF关闭；2'b11，表示DSP强制上行RF打开；其他，表示上行RF不受DSP控制，而由上行调制模块控制。
             此寄存器仅控制上行RF的开关。同时，仅在TX_SHDN_CTRL被配置为非DSP强制控制的情况下上行RF才受此寄存器的控制。
   UNION结构:  WBBP_TX_RF_SHDN_CTRL_UNION */
#define WBBP_TX_RF_SHDN_CTRL_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D090)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    上行PA开关控制。2'b10，表示DSP强制上行PA关闭；2'b11，表示DSP强制上行PA打开；其他，表示上行PA不受DSP控制，而由上行调制模块控制。
             此寄存器仅控制上行PA的开关。同时，仅在TX_SHDN_CTRL被配置为非DSP强制控制的情况下上行PA才受此寄存器的控制。
   UNION结构:  WBBP_TX_PA_SHDN_CTRL_UNION */
#define WBBP_TX_PA_SHDN_CTRL_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D094)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    上行ABB开关控制。2'b10，表示DSP强制上行ABB关闭；2'b11，表示DSP强制上行ABB打开；其他，表示上行ABB不受DSP控制，而由上行调制模块控制。
             此寄存器仅控制上行ABB的开关。同时，仅在TX_SHDN_CTRL被配置为非DSP强制控制的情况下上行ABB才受此寄存器的控制。
   UNION结构:  WBBP_ABB_SHDN_CTRL_UNION */
#define WBBP_ABB_SHDN_CTRL_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9D098)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  APT_ET切换点提前时隙头时间量，单位chip。
 bit[15:14]  保留
 bit[13:12]  2'd10:ET强关，2'd11:ET强开，其它:ET由其它控制。
 bit[11:10]  保留
 bit[9:0]    D态下，APT_ET使能信号生效提前时隙头时间量，单位chip。
   UNION结构:  WBBP_APT_ET_TIMING_UNION */
#define WBBP_APT_ET_TIMING_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9D09C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  提前打开上行RF IDLE状态的chip数。取值范围0~1023。典型值100us等于384chip。
 bit[15:12]  保留
 bit[11:0]   提前打开上行RF的chip数。取值范围0~1023。典型值800us等于3072chip。
   UNION结构:  WBBP_TX_RF_TIME_CTRL_UNION */
#define WBBP_TX_RF_TIME_CTRL_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0A0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  延后关闭上行RF IDLE状态的chip数。
 bit[15:10]  保留
 bit[9:0]    延后关闭上行RF的chip数。
   UNION结构:  WBBP_TX_RF_CLOSE_TIME_CTRL_UNION */
#define WBBP_TX_RF_CLOSE_TIME_CTRL_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0A4)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  延后关闭上行PA的chip数。
 bit[15:11]  保留
 bit[10:0]   提前打开上行PA的chip数。取值范围0~1023。典型值40us等于154chip。
   UNION结构:  WBBP_TX_PA_TIME_CTRL_UNION */
#define WBBP_TX_PA_TIME_CTRL_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0A8)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  延后关闭上行RF增益的chip数。
 bit[15:11]  保留
 bit[10:0]   提前打开上行RF增益的chip数。取值范围0~1023。
   UNION结构:  WBBP_TX_PDM_TIME_CTRL_UNION */
#define WBBP_TX_PDM_TIME_CTRL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0AC)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  延后关闭上行ABB的chip数。
 bit[15:12]  保留
 bit[11:0]   提前打开上行ABB的chip数。取值范围0~1023。
   UNION结构:  WBBP_TX_ABB_TIME_CTRL_UNION */
#define WBBP_TX_ABB_TIME_CTRL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0B0)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    上行发射功率生效时间，单位chip。表示上行发射功率需提前上行时隙头多久时间送至射频器件。由于射频器件有延时，为使上行发射功率在上行时隙头处生效，需提前将上行发射功率计算结果送至射频器件。
   UNION结构:  WBBP_ULPOWER_ACTIVE_TIME_UNION */
#define WBBP_ULPOWER_ACTIVE_TIME_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0B4)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    相位补偿生效时刻相对于时隙边界提前量，单位1/4chip。
   UNION结构:  WBBP_W_TX_PHASE_COMP_TIME_UNION */
#define WBBP_W_TX_PHASE_COMP_TIME_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0B8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    直流补偿生效时刻提前量 
   UNION结构:  WBBP_DCOFFSET_ACTIVE_TIME_UNION */
#define WBBP_DCOFFSET_ACTIVE_TIME_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0BC)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    APT电压生效时刻，默认值为时隙边界提前40chip。
   UNION结构:  WBBP_DSP_VBIAS_ACTIVE_TIME_UNION */
#define WBBP_DSP_VBIAS_ACTIVE_TIME_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0C0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  PA从中增益向高增益切换时提前上行时隙头的时间，单位chip。
 bit[15:10]  保留
 bit[9:0]    PA从高增益向中增益切换时提前上行时隙头的时间，单位chip。
   UNION结构:  WBBP_PA_ACTIVE_TIME_HM_UNION */
#define WBBP_PA_ACTIVE_TIME_HM_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0C4)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  PA从低增益向中增益切换时提前上行时隙头的时间，单位chip。
 bit[15:10]  保留
 bit[9:0]    PA从中增益向低增益切换时提前上行时隙头的时间，单位chip。
   UNION结构:  WBBP_PA_ACTIVE_TIME_ML_UNION */
#define WBBP_PA_ACTIVE_TIME_ML_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0C8)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  PA在中切高档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
             该参数无效，统一用wpavbias_active_time。
 bit[15:10]  保留
 bit[9:0]    PA在高切中档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
             该参数无效，统一用wpavbias_active_time。
   UNION结构:  WBBP_PA_MH_VBIAS_ACTIVE_TIME_UNION */
#define WBBP_PA_MH_VBIAS_ACTIVE_TIME_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0CC)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  PA在低切中档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
             该参数无效，统一用wpavbias_active_time。
 bit[15:10]  保留
 bit[9:0]    PA在中切低档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
             该参数无效，统一用wpavbias_active_time。
   UNION结构:  WBBP_PA_LM_VBIAS_ACTIVE_TIME_UNION */
#define WBBP_PA_LM_VBIAS_ACTIVE_TIME_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0D0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  PAVBIAS提前上行时隙头生效时刻，单位为chip。在MMMB PA和EAGLE PA(第一个控制字)都可使用。
 bit[15:10]  保留
 bit[9:0]    RFVBIAS提前上行时隙头生效时刻，单位为chip。(删除)
   UNION结构:  WBBP_FE_VBIAS_ACTIVE_TIME_UNION */
#define WBBP_FE_VBIAS_ACTIVE_TIME_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0D4)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    上行调制RRC延迟时间，单位chip。
   UNION结构:  WBBP_RRC_DELAY_CHIP_NUM_UNION */
#define WBBP_RRC_DELAY_CHIP_NUM_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0D8)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     天线调谐配置更新标志，脉冲信号。
 bit[15:10]  保留
 bit[9:0]    天线调谐配置提前帧头配置量，当上行打开后，WBBP每次在帧头提前cpu_tx_sw_active_time进行配置，单位为chip，默认值为0。
   UNION结构:  WBBP_CPU_TX_SWC_UNION */
#define WBBP_CPU_TX_SWC_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0DC)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  EAGLE PA 第三个PAVBIAS控制字提前上行时隙头生效时刻，单位为chip。
 bit[15:10]  保留
 bit[9:0]    EAGLE PA 第二个PAVBIAS控制字提前上行时隙头生效时刻，单位为chip。
   UNION结构:  WBBP_WPA_VBIAS_ACTIVE_TIME2_3_UNION */
#define WBBP_WPA_VBIAS_ACTIVE_TIME2_3_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0E0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  EAGLE PA 第四个PAVBIAS控制字(trigger生效)提前上行时隙头生效时刻，单位为chip。
 bit[15:10]  保留
 bit[9:0]    EAGLE PA 第四个PAVBIAS控制字(trigger拉高)提前上行时隙头生效时刻，单位为chip。
   UNION结构:  WBBP_WPA_VBIAS_ACTIVE_TIME4_UNION */
#define WBBP_WPA_VBIAS_ACTIVE_TIME4_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0E4)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  hsdpa信道数字增益回退在上行时隙头后生效时刻。单位1/4chip。
 bit[15:13]  保留
 bit[12]     上下时隙中间HSDPA功率补偿使能，高电平表示在HSDPCCH时隙头位置dbb做补偿。
 bit[11:10]  保留
 bit[9:0]    数字增益回退提前上行时隙头生效时刻。单位1/4chip。
   UNION结构:  WBBP_DBB_ATTEN_ACTIVE_TIME_UNION */
#define WBBP_DBB_ATTEN_ACTIVE_TIME_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0E8)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  上行低功耗控制字2提前上行时隙头生效时刻，单位为chip。
 bit[15:10]  保留
 bit[9:0]    上行低功耗控制字1提前上行时隙头生效时刻，单位为chip。
   UNION结构:  WBBP_TX_LOWPOW_ACTIVE_TIME1_2_UNION */
#define WBBP_TX_LOWPOW_ACTIVE_TIME1_2_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0EC)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  上行低功耗控制字4提前上行时隙头生效时刻，单位为chip。
 bit[15:10]  保留
 bit[9:0]    上行低功耗控制字3提前上行时隙头生效时刻，单位为chip。
   UNION结构:  WBBP_TX_LOWPOW_ACTIVE_TIME3_4_UNION */
#define WBBP_TX_LOWPOW_ACTIVE_TIME3_4_ADDR            (SOC_BBP_WCDMA_BASE_ADDR + 0x9D0F0)

/* 寄存器说明：
 bit[31]     DSP直接使用SPI口的标志信号，高有效。
 bit[30]     读写标志。0，表示写；1，表示读。
 bit[29:16]  保留
 bit[15:0]   DSP直接使用SPI口对HKADC进行读写时的指令寄存器值。高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。
   UNION结构:  WBBP_DSP_SPI_2ABB_UNION */
#define WBBP_DSP_SPI_2ABB_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D200)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      强制功率检测使能。1，表示一次功率检测；0，无效。BBP在功率检测结果输出后进行自清零，软件通过查询此bit可确定功率检测结果是否有效。
   UNION结构:  WBBP_DSP_POW_DET_UNION */
#define WBBP_DSP_POW_DET_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9D204)

/* 寄存器说明：
 bit[31]     保留
 bit[30:28]  HKADC SSI Master释放单线控制权到Master开始检查Slave返回的同步位的时间配置值。 
             延迟=1.5+0.5*Step_num(clk).
             Step_num=0~7
 bit[27:26]  保留
 bit[25:16]  配置ABB从bypass为低到启动start （ABB开始转换）的时间间隔，单位为chip。
 bit[15:0]   1）当使用RFIC-PD方案时，表示：控制海思RF的功率检测器件和AD采样的打开门限。当发射功率超过此门限时，打开RF的功率检测器件与AD。
             说明：V3只使用bit[9:0]；此门限必须小于pow_det_open_threshold，且为正数；
             2）当使用HKADC-PD方案时，表示：通知ABB进行HKADC采样的指令寄存器值，高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。
   UNION结构:  WBBP_POW_DET_START_2ABB_UNION */
#define WBBP_POW_DET_START_2ABB_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D208)

/* 寄存器说明：
 bit[31:16]  配置打开HKADC PD通道的指令寄存器值。BBP从最高位开始发。
 bit[15:0]   1）当使用RFIC-PD方案时，表示：控制海思RF的功率检测器件和AD采样的的关闭门限。当发射功率小于此门限时，关闭RF的功率检测器件与AD。
             说明：V3只使用bit[10:0]；此门限必须小于pow_det_close_threshold；
             2）当使用HKADC-PD方案时，表示：读取ABB中HKADC采样结果第一个寄存器的指令寄存器值，高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。
   UNION结构:  WBBP_POW_DET_READ1_2ABB_UNION */
#define WBBP_POW_DET_READ1_2ABB_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D20C)

/* 寄存器说明：
 bit[31:16]  配置关闭HKADC PD通道的指令寄存器值。BBP从最高位开始发。
 bit[15:0]   读取ABB中HKADC采样结果第二个寄存器的指令寄存器值。高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。
             软件根据实际需要配置，BBP将此信息通过SPI口配置给ABB后，ABB通过此SPI口将结果送给BBP。
             说明：Hi6411V110，此寄存器值需配置16'hce00。
   UNION结构:  WBBP_POW_DET_READ2_2ABB_UNION */
#define WBBP_POW_DET_READ2_2ABB_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D210)

/* 寄存器说明：
 bit[31]     保留
 bit[30]     hkadc状态机复位信号，电平信号。
             1：表示复位hkadc状态机；0表示正常工作。
 bit[29:20]  保留
 bit[19:16]  授权有效到发送HKADC通道控制字时刻间隔,单位chip
 bit[15:14]  配置WHKADC上行每个时隙进行dc offset检测的次数。
             2'd0：4次；
             2'd1：8次；
             2'd2：16次。
 bit[13:12]  配置W上行每个时隙进行PD检测的次数。
             2'd0：4次；
             2'd1：8次；
             2'd2：16次。
 bit[11:10]  保留
 bit[9:0]    HKADC采样信号处理时间，单位chip。具体表示意义请参考《Hi6750V100 芯片WBBP子系统与CPU接口说明书.doc》之16.2.1。
   UNION结构:  WBBP_SAMPLE_TIME_ABB_UNION */
#define WBBP_SAMPLE_TIME_ABB_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D214)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:12]  上报HKADC_PD进行SSI传输的次数。定位用。
 bit[11:10]  保留
 bit[9:0]    功率检测结果。BBP将每次功率检测结果上报软件。所有从ABB读出的结果，通过此寄存器上报。发射功率越高，上报结果越大，呈线性规律。
   UNION结构:  WBBP_POW_DET_RESULT_UNION */
#define WBBP_POW_DET_RESULT_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9D218)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:8]    00:无效值。
             01:6360 RFIC模式，不仲裁，不去直流。
             10:MMMB PA模式，仲裁，不去直流。
             11:6361 RFIC模式，仲裁，去直流。
 bit[7:5]    保留
 bit[4]      AD位宽选择。1，表示8bit；0，表示10bit。
 bit[3:1]    保留
 bit[0]      最大功率限制使能。1，表示有效；0，表示无效。
   UNION结构:  WBBP_PMAX_LIMIT_EN_UNION */
#define WBBP_PMAX_LIMIT_EN_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9D21C)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   发射功率变化后，RF与PA的稳定时间，单位chip。具体表示意义请参考《Hi6750V100 芯片WBBP子系统与CPU接口说明书.doc》之16.2.1。
   UNION结构:  WBBP_RF_PA_STABLE_TIME_UNION */
#define WBBP_RF_PA_STABLE_TIME_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D220)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   功率检测时的频率补偿值，单位0.1dBm。软件根据当前的频点将相应的NV项配置到BBP。
   UNION结构:  WBBP_POW_DET_FREQ_COMP_UNION */
#define WBBP_POW_DET_FREQ_COMP_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D224)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   功率检测时的温度补偿值，单位0.1dBm。软件根据当前的温度将相应的NV项配置到BBP。
   UNION结构:  WBBP_POW_DET_TEMP_COMP_UNION */
#define WBBP_POW_DET_TEMP_COMP_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D228)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    两次功率检测之间的时间间隔，单位chip。
   UNION结构:  WBBP_POW_DET_INTERVAL_UNION */
#define WBBP_POW_DET_INTERVAL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D22C)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  功率检测关闭门限。当上行理论发射功率低于此门限时，BBP关闭功率检测功能。范围0~1023，单位0.1dBm。
             注意：pow_det_close_threshold必须小于pow_det_open_threshold，否则，功率检测功能无法打开。
 bit[15:10]  保留
 bit[9:0]    功率检测打开门限。当上行理论发射功率超过此门限时，BBP打开功率检测功能。范围0~1023，单位0.1dBm。
             说明：根据功率检测总体方案，功率检测范围为10~27dBm，即此寄存器默认值为100。
   UNION结构:  WBBP_POW_DET_THRESHOLD_UNION */
#define WBBP_POW_DET_THRESHOLD_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D230)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  act_nom_error一帧内的平均值。
 bit[15:11]  保留
 bit[10:0]   实际发射功率-理论发射功率，单位0.1dBm。
   UNION结构:  WBBP_ACT_NOM_ERROR_UNION */
#define WBBP_ACT_NOM_ERROR_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9D234)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  每时隙功率测量平均结果上报。查表前的线性值，无符号数。
 bit[15:10]  保留
 bit[9:0]    HKADC每时隙直流测量平均结果上报。查表前的线性值，无符号数。
   UNION结构:  WBBP_DCOFFSET_POW_LINE_VALUE_UNION */
#define WBBP_DCOFFSET_POW_LINE_VALUE_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x9D238)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12]     HKADC非信令下,软件读取PD模式:
             0 表示采样一次dcoffset上报.
             1 表示一个时隙内先采样平均得到dcoffset然后采样平均得到功率检测线性值,最后上报值=功率检测线性值-dcoffset;
 bit[11]     PD关闭时,PD检测误差,1:保持   0:清零
 bit[10]     软件强配HKADC直流使能,高电平有效
 bit[9:0]    软件强配HKADC直流,无符号数
   UNION结构:  WBBP_DSP_CONFIG_PD_DCOFFSET_UNION */
#define WBBP_DSP_CONFIG_PD_DCOFFSET_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x9D23C)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6]      测试模式下，存在R5信道的上行R99时隙是否进行功率检测。bit[6]：1，表示只有存在R5信道的上行R99时隙进行功率检测。
 bit[5]      测试模式下，存在R6信道的上行R99时隙是否进行功率检测。bit[5]：1，表示存在R6信道的上行R99时隙不进行功率检测；0，表示存在R6信道的上行R99时隙进行功率检测。
             
 bit[4]      测试模式下，存在R5信道的上行R99时隙是否进行功率检测。
             bit[4]：1，表示存在R5信道的上行R99时隙不进行功率检测；0，表示存在R5信道的上行R99时隙进行功率检测。（根据总体方案，只有R5信道b值不变的时隙才进行功率检测。）
             
 bit[3:1]    保留
 bit[0]      PD测试模式选择。1，表示测试模式；0，表示正常模式。
   UNION结构:  WBBP_PD_TEST_CTRL_UNION */
#define WBBP_PD_TEST_CTRL_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D240)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:4]   HKADC powerdetct连接上行通道的控制字.
 bit[3]      0:表示不输出PD清零控制字给PD芯片(hi6361方案).
             1:表示输出PD清零控制字给PD芯片(hi6360方案).
 bit[2:1]    保留
 bit[0]      功率检测保持使能信号，用于在功率检测期间需要温度检测的情况。在需要进行温度检测时，软件将此寄存器配置为1，之后，将HKADC通道配置为温度检测，然后软件完成温度检测。温度检测完成后，软件将HKADC通道配置为功率检测后，再将此寄存器配置为0。
   UNION结构:  WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_UNION */
#define WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_ADDR   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D244)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   HKADC powerdetct不连接上行通道的控制字.
   UNION结构:  WBBP_PD_DISCONNECT_CTRL_WORD_UNION */
#define WBBP_PD_DISCONNECT_CTRL_WORD_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x9D248)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:19]  驻波检测时隙前后向功率检测次数，
 bit[18:16]  保留
 bit[15]     驻波检测有效清零信号。
 bit[14:5]   前反向通道切换等待延时，单位为
 bit[4:1]    驻波检测启动时隙号，默认值为6。
 bit[0]      驻波检测启动使能，高电平有效，该信号有效时，驻波检测功能打开。
             
   UNION结构:  WBBP_DSP_TX_SWD_CFG_UNION */
#define WBBP_DSP_TX_SWD_CFG_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9D24C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   前向ssi控制字
   UNION结构:  WBBP_DSP_TX_SWD_FW_SSI_CFG_UNION */
#define WBBP_DSP_TX_SWD_FW_SSI_CFG_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9D250)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   反向ssi控制字
   UNION结构:  WBBP_DSP_TX_SWD_RV_SSI_CFG_UNION */
#define WBBP_DSP_TX_SWD_RV_SSI_CFG_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9D254)

/* 寄存器说明：
 bit[31:30]  反向功率检测结果有效标志，电平信号。低比特为测试位，无需关注。2’b1x表示反向检测功率有效；2’b0x表示反向检测功率无效。dsp_swd_valid_clr为高脉冲时， dsp_swd_valid_flag清零
 bit[29:24]  PD检测功率补偿值，有符号数
 bit[23:22]  保留
 bit[21:12]  反向电压上报值，10bits，无符号数
 bit[11:10]  保留
 bit[9:0]    前向电压上报值，10bits，无符号数
   UNION结构:  WBBP_DSP_TX_SWD_RPT_UNION */
#define WBBP_DSP_TX_SWD_RPT_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9D258)

/* 寄存器说明：
 bit[31:16]  mipi pavbias控制字1地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。
 bit[15:0]   mipi apt控制字地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。
   UNION结构:  WBBP_MIPI_APT_ADDR_UNION */
#define WBBP_MIPI_APT_ADDR_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9D400)

/* 寄存器说明：
 bit[31:16]  mipi pavbias控制字3地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。
 bit[15:0]   mipi pavbias控制字2地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。
   UNION结构:  WBBP_MIPI_PAVBIAS_ADDR_UNION */
#define WBBP_MIPI_PAVBIAS_ADDR_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D404)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     mipi pavbias trigger控制字1发送使能，高电平有效。
 bit[27:25]  保留
 bit[24:0]   mipi pavbias trigger控制字1，高3比特位指令属性(默认为写)，中间13比特位命令帧(地址)，低9比特为数据。
   UNION结构:  WBBP_MIPI_PAVBIAS_TRIGGER1_UNION */
#define WBBP_MIPI_PAVBIAS_TRIGGER1_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9D408)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     mipi pavbias trigger控制字2发送使能，高电平有效。
 bit[27:25]  保留
 bit[24:0]   mipi pavbias trigger控制字2，高3比特位指令属性(默认为写)，中间13比特位命令帧(地址)，低9比特为数据。
   UNION结构:  WBBP_MIPI_PAVBIAS_TRIGGER2_UNION */
#define WBBP_MIPI_PAVBIAS_TRIGGER2_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9D40C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字1(高增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD1_H_UNION */
#define WBBP_LOWPOW_SSI_WORD1_H_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D410)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字1(中增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD1_M_UNION */
#define WBBP_LOWPOW_SSI_WORD1_M_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D414)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字1(低增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD1_L_UNION */
#define WBBP_LOWPOW_SSI_WORD1_L_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D418)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字2(高增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD2_H_UNION */
#define WBBP_LOWPOW_SSI_WORD2_H_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D41C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字2(中增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD2_M_UNION */
#define WBBP_LOWPOW_SSI_WORD2_M_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D420)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字2(低增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD2_L_UNION */
#define WBBP_LOWPOW_SSI_WORD2_L_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D424)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字3(高增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD3_H_UNION */
#define WBBP_LOWPOW_SSI_WORD3_H_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D428)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字3(中增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD3_M_UNION */
#define WBBP_LOWPOW_SSI_WORD3_M_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D42C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字3(低增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD3_L_UNION */
#define WBBP_LOWPOW_SSI_WORD3_L_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D430)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字4(高增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD4_H_UNION */
#define WBBP_LOWPOW_SSI_WORD4_H_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D434)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字4(中增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD4_M_UNION */
#define WBBP_LOWPOW_SSI_WORD4_M_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D438)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   上行低功耗控制字4(低增益)。
   UNION结构:  WBBP_LOWPOW_SSI_WORD4_L_UNION */
#define WBBP_LOWPOW_SSI_WORD4_L_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9D43C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     EAGLE PA第一个VBIAS控制字强配使能。
 bit[27:25]  保留
 bit[24:16]  EAGLE PA第二个VBIAS控制字强配值。
 bit[15:13]  保留
 bit[12]     EAGLE PA第一个VBIAS控制字强配使能。
 bit[11:9]   保留
 bit[8:0]    EAGLE PA第一个VBIAS控制字强配值。
   UNION结构:  WBBP_MIPI_PAVBIAS1_2_CFG_UNION */
#define WBBP_MIPI_PAVBIAS1_2_CFG_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D440)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     PA VBIAS通道选择。
             0：表示MMMB PA，VBIAS通过SSI送给AUXDAC。
             1：表示EAGLE PA，第一个VBIAS控制字走MIPI。
 bit[15:13]  保留
 bit[12]     EAGLE PA第一个VBIAS控制字强配使能。
 bit[11:9]   保留
 bit[8:0]    EAGLE PA第三个VBIAS控制字强配值。
   UNION结构:  WBBP_MIPI_PAVBIAS3_CFG_UNION */
#define WBBP_MIPI_PAVBIAS3_CFG_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D444)

/* 寄存器说明：
 bit[31:9]   PAPD冗余寄存器1
 bit[8:0]    EAGLE PA APT控制字强配值。
   UNION结构:  WBBP_PAPD_REDUND1_UNION */
#define WBBP_PAPD_REDUND1_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D448)

/* 寄存器说明：
 bit[31:25]  普通PA APT控制字上报，无符号数。
 bit[24:0]   PAPD冗余寄存器2
   UNION结构:  WBBP_PAPD_REDUND2_UNION */
#define WBBP_PAPD_REDUND2_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D44C)

/* 寄存器说明：
   详      述：PAPD冗余寄存器3
   UNION结构 ：无 */
#define WBBP_PAPD_REDUND3_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D450)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      apt步长模式选择
             1'b0:0.8step
             1'b1:0.4step
   UNION结构:  WBBP_APT_STEP_MOD_SEL_UNION */
#define WBBP_APT_STEP_MOD_SEL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D454)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:20]  APT MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。
 bit[19]     保留
 bit[18:16]  PA VBIAS1 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。
 bit[15]     保留
 bit[14:12]  PA VBIAS2 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。
 bit[11]     保留
 bit[10:8]   PA VBIAS3 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。
 bit[7]      保留
 bit[6:4]    PA VBIAS TRIGGER1 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。
 bit[3]      保留
 bit[2:0]    PA VBIAS TRIGGER2 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。
   UNION结构:  WBBP_MIPI_CH_EXCHANGE_UNION */
#define WBBP_MIPI_CH_EXCHANGE_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D458)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25]     第三方ET包络增益和偏移强配使能信号。dsp_post_cfg_en==1'b0，选择根据APC Setting选择后的gain；dsp_post_cfg_en==1'b1，选择dsp_post_offset，dsp_post_gain
 bit[24]     dsp_post_gain和dsp_post_offset的有效性指示脉冲信号，高有效。
 bit[23:22]  保留
 bit[21:12]  包络适配使用的偏移
 bit[11:10]  保留
 bit[9:0]    包络适配使用的增益
   UNION结构:  WBBP_COM2ET_CTRL1_UNION */
#define WBBP_COM2ET_CTRL1_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D45C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  上行ET理论发射功率提前上行时隙头生效时刻，单位为chip。
 bit[15:11]  保留
 bit[10:0]   上行ET和APT模式切换提前上行时隙头生效时刻，单位为chip。
   UNION结构:  WBBP_COM2ET_CTRL2_UNION */
#define WBBP_COM2ET_CTRL2_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D460)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   上行ET APT电压控制字上行时隙头生效时刻，单位为chip。
   UNION结构:  WBBP_COM2ET_CTRL3_UNION */
#define WBBP_COM2ET_CTRL3_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D464)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    DPD
   UNION结构:  WBBP_DPD_ACTIVE_TIME_UNION */
#define WBBP_DPD_ACTIVE_TIME_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D468)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   ET
   UNION结构:  WBBP_ET_DELAY_ACTIVE_TIME_UNION */
#define WBBP_ET_DELAY_ACTIVE_TIME_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D46C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    ET数据接口选择信号，扩展位2bit。2'b0:选择CFR之后DPD之前的数据抽点到ET，与V8R1实现一致；2'b1:选择DPD后数据抽点到ET；2'b1X,选择DPC后数据抽点到ET
   UNION结构:  WBBP_TX_ETIF_SEL_UNION */
#define WBBP_TX_ETIF_SEL_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9D470)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    SSI发送通道指示
   UNION结构:  WBBP_TX_RF_SSI_CH_SEL_UNION */
#define WBBP_TX_RF_SSI_CH_SEL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D474)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      APT功率模式选择：1'b0,理论发射功率；1'b1,实际发射功率
   UNION结构:  WBBP_APT_PWR_MOD_SEL_UNION */
#define WBBP_APT_PWR_MOD_SEL_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D478)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    上变频提前上行时隙头生效时刻。单位
   UNION结构:  WBBP_FREQ_CNT_ACTIVE_TIME_UNION */
#define WBBP_FREQ_CNT_ACTIVE_TIME_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D47C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      ET模式选择，1’b0:第三方ET；1’b1:自研ET。默认为0
   UNION结构:  WBBP_ET_MODE_UNION */
#define WBBP_ET_MODE_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x9D480)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  GAIN2对应温补、频补的线性增益值，无符号数
 bit[15:12]  保留
 bit[11:0]   GAIN1对应温补、频补的线性增益值，无符号数
   UNION结构:  WBBP_GAIN_COMPENSATE_UNION */
#define WBBP_GAIN_COMPENSATE_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D484)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN1对应的子表1线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN1对应的子表0线性增益值，无符号数
   UNION结构:  WBBP_GAIN1_CALIBRATION0_1_UNION */
#define WBBP_GAIN1_CALIBRATION0_1_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D488)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN1对应的子表3线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN1对应的子表2线性增益值，无符号数
   UNION结构:  WBBP_GAIN1_CALIBRATION2_3_UNION */
#define WBBP_GAIN1_CALIBRATION2_3_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D48C)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN1对应的子表5线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN1对应的子表4线性增益值，无符号数
   UNION结构:  WBBP_GAIN1_CALIBRATION4_5_UNION */
#define WBBP_GAIN1_CALIBRATION4_5_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D490)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN1对应的子表7线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN1对应的子表6线性增益值，无符号数
   UNION结构:  WBBP_GAIN1_CALIBRATION6_7_UNION */
#define WBBP_GAIN1_CALIBRATION6_7_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D494)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN2对应的子表1线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN2对应的子表0线性增益值，无符号数
   UNION结构:  WBBP_GAIN2_CALIBRATION0_1_UNION */
#define WBBP_GAIN2_CALIBRATION0_1_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D498)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN2对应的子表3线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN2对应的子表2线性增益值，无符号数
   UNION结构:  WBBP_GAIN2_CALIBRATION2_3_UNION */
#define WBBP_GAIN2_CALIBRATION2_3_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D49C)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN2对应的子表5线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN2对应的子表4线性增益值，无符号数
   UNION结构:  WBBP_GAIN2_CALIBRATION4_5_UNION */
#define WBBP_GAIN2_CALIBRATION4_5_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4A0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GAIN2对应的子表7线性增益值，无符号数
 bit[15:10]  保留
 bit[9:0]    GAIN2对应的子表6线性增益值，无符号数
   UNION结构:  WBBP_GAIN2_CALIBRATION6_7_UNION */
#define WBBP_GAIN2_CALIBRATION6_7_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4A4)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   第三方ET温补和频补，功率的db值，有符号数
   UNION结构:  WBBP_ET_TEMP_COMP_UNION */
#define WBBP_ET_TEMP_COMP_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4A8)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:4]    GAIN2四舍五入右移bit选择：2'b0:2bit, 2'b1:3bit, 2'b1X:4bit
 bit[3:2]    保留
 bit[1:0]    GAIN1四舍五入右移bit选择：2'b0:2bit, 2'b1:3bit, 2'b1X:4bit
   UNION结构:  WBBP_ET_GAIN_ROUND_SEL_UNION */
#define WBBP_ET_GAIN_ROUND_SEL_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4AC)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    2'b0，由bbp根据PA档位自动控制；2’b1,软件强制为APT模式；2'b1X,软件强制为ET模式
   UNION结构:  WBBP_APT_ET_MODE_FORCE_UNION */
#define WBBP_APT_ET_MODE_FORCE_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4B0)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1'b0，bbp根据当前是否处于apt模式，确认发送apt控制字；1'b1，代表无论apt或et模式，apt控制字都发送，兼容v8
   UNION结构:  WBBP_ET_APT_WORD_EN_UNION */
#define WBBP_ET_APT_WORD_EN_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4B4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      PA GAIN切换门限更新指示，接口中先完成PA GAIN切换门限的配置，配置全部完成后配置dsp_pa_ud_ready，通知BBP配置结束，逻辑自清零信号
   UNION结构:  WBBP_PA_THRESHOLD_UPDATE_READY_UNION */
#define WBBP_PA_THRESHOLD_UPDATE_READY_ADDR           (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4B8)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:8]   DPD db转线性值rom表地址偏移值，无符号数
 bit[7]      保留
 bit[6:0]    DPC db转线性值rom表地址偏移值，无符号数
   UNION结构:  WBBP_DB2L_ROM_OFFSET_UNION */
#define WBBP_DB2L_ROM_OFFSET_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4BC)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    ET Gain1/Gain2
   UNION结构:  WBBP_ET_GAIN_ACTIVE_TIME_UNION */
#define WBBP_ET_GAIN_ACTIVE_TIME_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4C0)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:8]   DPC db转线性值rom表地址下限，范围0~127，默认为20，兼容v8，无符号数
 bit[7]      保留
 bit[6:0]    DPC db转线性值rom表地址上限，范围0~127，默认为120，兼容v8无符号数
   UNION结构:  WBBP_DBB_DB2L_ROM_THRESHOLD_UNION */
#define WBBP_DBB_DB2L_ROM_THRESHOLD_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4C4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      ET Gain1/Gain2
   UNION结构:  WBBP_ET_GAIN_CFG_EN_UNION */
#define WBBP_ET_GAIN_CFG_EN_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4C8)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:12]  数字 MPR回退值上报
 bit[11:8]   除10后余数部分数字功率回退值上报
 bit[7:0]    8比特数字功率回退值上报
   UNION结构:  WBBP_DBB_ATTEN_VALUE_RPT_UNION */
#define WBBP_DBB_ATTEN_VALUE_RPT_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4CC)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:8]   APT MPR回退值上报
 bit[7:6]    保留
 bit[5:0]    PD MPR回退值上报
   UNION结构:  WBBP_MPR_OUT_RPT_UNION */
#define WBBP_MPR_OUT_RPT_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4D0)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     输出给ET模块的的APT、ET模式选择信号
 bit[27]     保留
 bit[26:16]  输出给ET模块的的绝对发射功率
 bit[15:14]  保留
 bit[13:12]  输出给ET模块的的PA档位控制字
 bit[11:10]  保留
 bit[9:0]    输出给ET模块的的APT控制字
   UNION结构:  WBBP_COM2ET_CTRL_RPT1_UNION */
#define WBBP_COM2ET_CTRL_RPT1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4D4)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:12]  输出给ET模块的包络适配使用的增益
 bit[11:10]  保留
 bit[9:0]    输出给ET模块的包络适配使用的偏移
   UNION结构:  WBBP_COM2ET_CTRL_RPT2_UNION */
#define WBBP_COM2ET_CTRL_RPT2_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9D4D8)



/***======================================================================***
                     (6/10) register_define_w_pd_mem
 ***======================================================================***/
/* 寄存器说明：PD功率表
 bit[31:10]  保留
 bit[9:0]    存储180个功率对应的电压线性值，10比特无符号数，地址单位0.1dBm.
   UNION结构:  WBBP_PD_RAM_UNION */
#define WBBP_PD_RAM_ADDR                              (SOC_BBP_WCDMA_BASE_ADDR + 0x9D800)
#define WBBP_PD_RAM_MEMDEPTH  (180)

/* 寄存器说明：DPD补偿表
 bit[31:24]  保留
 bit[23:12]  DPD补偿Q路系数
 bit[11:0]   DPD补偿I路系数
   UNION结构:  WBBP_DPD_RAM2_UNION */
#define WBBP_DPD_RAM2_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x9DAD0)
#define WBBP_DPD_RAM2_MEMDEPTH  (256)



/***======================================================================***
                     (7/10) register_define_ulfe_wt_share
 ***======================================================================***/
/* 寄存器说明：门控时钟
 bit[31:19]  保留
 bit[18:0]   ULFE自动门控功能使能；1表示对应子模块自动门控功能打开，0表示对应子模块自动门控功能关闭
             bit[0]: 主载波rrc模块自动门控功能使能
             bit[1]: W、C 削波延迟子模块自动门控功能使能
             bit[2]: W、C和TDS FIR/第一级削波子模块自动门控使能
             bit[3]: W和C 第二级削波子模块自动门控使能
             bit[4]: power comp模块自动门控使能
             bit[5]: tx phase comp模块自动门控使能
             bit[6]:txiq 预畸变模块自动门控时钟使能
             bit[7]:txiq 相关计算和单频信号产生模块自动门控时钟使能
             bit[8]: dbg模块自动门控时钟使能
             bit[9]:主载波上变频门控时钟使能
             bit[10]:辅载波rrc和上变频模块门控使能
             bit[11]:sc_cal模块门控使能
             bit[12]:频偏校正模块门控使能
             bit[13]:fe_nco模块门控使能
             bit[14]:W base_cnt_abb模块门控使能；TDS base_cnt_dbb模块门控使能
             bit[15]:DPD模块门控使能
             bit[16]:dc_nco模块门控使能
             bit[17]:dc_add模块门控使能
             bit[18]:单音模块门控使能
   UNION结构:  WBBP_ULFE_CKG_EN_UNION */
#define WBBP_ULFE_CKG_EN_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9E000)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    2'b0：选择W
             2'b1：选择TDS
             2'b10:1X
             2'b11：EVDO
             
             
   UNION结构:  WBBP_ULFE_U_TDS_MOD_SEL_UNION */
#define WBBP_ULFE_U_TDS_MOD_SEL_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9E00C)

/* 寄存器说明：ULFE内部模块功能开关寄存器
 bit[31:21]  保留
 bit[20]     DCUPANCO
 bit[19]     DPD
 bit[18]     base_cnt_abb模块使能信号
             1'b0：W、TDS和C不使能
             1'b1：W、TDS和C使能
 bit[17]     fe_nco模块使能信号
             1'b0：W、TDS和C不使能
             1'b1：W、TDS和C使能
             TDS为0
 bit[16]     fe_sc_cal模块使能信号
             1'b0：W、TDS和C不使能
             1'b1：W、TDS和C使能
 bit[15]     fe_freq_error模块使能信号
             1'b0：W、TDS和C不使能
             1'b1：W、TDS和C使能
 bit[14:13]  保留
 bit[12]     tds_dbg使能信号
             1'b0:W、C不使能，TDS使能；
             1'b1:W、C使能，TDS不使能。
 bit[11:9]   保留
 bit[8]      txiq 预畸变使能信号
             1'b0:W、TDS和C不使能，旁路
             1'b1:W、TDS和C使能
 bit[7:5]    保留
 bit[4]      power comp使能信号
             1'b0:W、TDS和C不使能，旁路
             1'b1:W、TDS和C使能
 bit[3:1]    保留
 bit[0]      tx phase comp使能信号
             1'b0:W、TDS和C不使能；
             1'b1:W、TDS和C使能。
   UNION结构:  WBBP_ULFE_FUNC_EN_UNION */
#define WBBP_ULFE_FUNC_EN_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E010)

/* 寄存器说明：上行发送模式
 bit[31:2]   保留
 bit[1:0]    W、C和TDS上行TX模式控制：
             00：正常工作
             01：测试波形模式，连续循环发送测试波形数据
             1x：保留
   UNION结构:  WBBP_TX_MODE_REG_UNION */
#define WBBP_TX_MODE_REG_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9E014)

/* 寄存器说明：数据发送参数寄存器
 bit[31:10]  保留
 bit[9:8]    W、C和TDS测试波形模式下发送以下样点数据的间隔：
             0：间隔为1（默认值 ）；
             1：间隔为2；
             2：间隔为3；
             3：间隔为4；
 bit[7:6]    保留
 bit[5:0]    W、C和TDS测试波形模式下的波形信号，发送样点数据数目，典型值为16，取值范围1~32
   UNION结构:  WBBP_TX_SEND_NUM_REG_UNION */
#define WBBP_TX_SEND_NUM_REG_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9E018)

/* 寄存器说明：测试发送数据0
 bit[31:24]  保留
 bit[23:12]  W、C和TDS测试波形模式下，第0个数据虚部
 bit[11:0]   W、C和TDS测试波形模式下，第0个数据实部
   UNION结构:  WBBP_TX_SEND_DATA0_UNION */
#define WBBP_TX_SEND_DATA0_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E01C)

/* 寄存器说明：测试发送数据1
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第1个数据虚部
 bit[11:0]   测试波形模式下，第1个数据实部
   UNION结构:  WBBP_TX_SEND_DATA1_UNION */
#define WBBP_TX_SEND_DATA1_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E020)

/* 寄存器说明：测试发送数据2
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第2个数据虚部
 bit[11:0]   测试波形模式下，第2个数据实部
   UNION结构:  WBBP_TX_SEND_DATA2_UNION */
#define WBBP_TX_SEND_DATA2_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E024)

/* 寄存器说明：测试发送数据3
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第3个数据虚部
 bit[11:0]   测试波形模式下，第3个数据实部
   UNION结构:  WBBP_TX_SEND_DATA3_UNION */
#define WBBP_TX_SEND_DATA3_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E028)

/* 寄存器说明：测试发送数据4
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第4个数据虚部
 bit[11:0]   测试波形模式下，第4个数据实部
   UNION结构:  WBBP_TX_SEND_DATA4_UNION */
#define WBBP_TX_SEND_DATA4_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E02C)

/* 寄存器说明：测试发送数据5
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第5个数据虚部
 bit[11:0]   测试波形模式下，第5个数据实部
   UNION结构:  WBBP_TX_SEND_DATA5_UNION */
#define WBBP_TX_SEND_DATA5_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E030)

/* 寄存器说明：测试发送数据6
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第6个数据虚部
 bit[11:0]   测试波形模式下，第6个数据实部
   UNION结构:  WBBP_TX_SEND_DATA6_UNION */
#define WBBP_TX_SEND_DATA6_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E034)

/* 寄存器说明：测试发送数据7
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第7个数据虚部
 bit[11:0]   测试波形模式下，第7个数据实部
   UNION结构:  WBBP_TX_SEND_DATA7_UNION */
#define WBBP_TX_SEND_DATA7_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E038)

/* 寄存器说明：测试发送数据8
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第8个数据虚部
 bit[11:0]   测试波形模式下，第8个数据实部
   UNION结构:  WBBP_TX_SEND_DATA8_UNION */
#define WBBP_TX_SEND_DATA8_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E03C)

/* 寄存器说明：测试发送数据9
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第9个数据虚部
 bit[11:0]   测试波形模式下，第9个数据实部
   UNION结构:  WBBP_TX_SEND_DATA9_UNION */
#define WBBP_TX_SEND_DATA9_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E040)

/* 寄存器说明：测试发送数据10
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第10个数据虚部
 bit[11:0]   测试波形模式下，第10个数据实部
   UNION结构:  WBBP_TX_SEND_DATA10_UNION */
#define WBBP_TX_SEND_DATA10_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E044)

/* 寄存器说明：测试发送数据11
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第11个数据虚部
 bit[11:0]   测试波形模式下，第11个数据实部
   UNION结构:  WBBP_TX_SEND_DATA11_UNION */
#define WBBP_TX_SEND_DATA11_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E048)

/* 寄存器说明：测试发送数据12
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第12个数据虚部
 bit[11:0]   测试波形模式下，第12个数据实部
   UNION结构:  WBBP_TX_SEND_DATA12_UNION */
#define WBBP_TX_SEND_DATA12_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E04C)

/* 寄存器说明：测试发送数据13
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第13个数据虚部
 bit[11:0]   测试波形模式下，第13个数据实部
   UNION结构:  WBBP_TX_SEND_DATA13_UNION */
#define WBBP_TX_SEND_DATA13_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E050)

/* 寄存器说明：测试发送数据14
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第14个数据虚部
 bit[11:0]   测试波形模式下，第14个数据实部
   UNION结构:  WBBP_TX_SEND_DATA14_UNION */
#define WBBP_TX_SEND_DATA14_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E054)

/* 寄存器说明：测试发送数据15
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第15个数据虚部
 bit[11:0]   测试波形模式下，第15个数据实部
   UNION结构:  WBBP_TX_SEND_DATA15_UNION */
#define WBBP_TX_SEND_DATA15_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E058)

/* 寄存器说明：测试发送数据16
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第16个数据虚部
 bit[11:0]   测试波形模式下，第16个数据实部
   UNION结构:  WBBP_TX_SEND_DATA16_UNION */
#define WBBP_TX_SEND_DATA16_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E05C)

/* 寄存器说明：测试发送数据17
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第17个数据虚部
 bit[11:0]   测试波形模式下，第17个数据实部
   UNION结构:  WBBP_TX_SEND_DATA17_UNION */
#define WBBP_TX_SEND_DATA17_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E060)

/* 寄存器说明：测试发送数据18
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第18个数据虚部
 bit[11:0]   测试波形模式下，第18个数据实部
   UNION结构:  WBBP_TX_SEND_DATA18_UNION */
#define WBBP_TX_SEND_DATA18_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E064)

/* 寄存器说明：测试发送数据19
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第19个数据虚部
 bit[11:0]   测试波形模式下，第19个数据实部
   UNION结构:  WBBP_TX_SEND_DATA19_UNION */
#define WBBP_TX_SEND_DATA19_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E068)

/* 寄存器说明：测试发送数据20
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第20个数据虚部
 bit[11:0]   测试波形模式下，第20个数据实部
   UNION结构:  WBBP_TX_SEND_DATA20_UNION */
#define WBBP_TX_SEND_DATA20_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E06C)

/* 寄存器说明：测试发送数据21
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第21个数据虚部
 bit[11:0]   测试波形模式下，第21个数据实部
   UNION结构:  WBBP_TX_SEND_DATA21_UNION */
#define WBBP_TX_SEND_DATA21_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E070)

/* 寄存器说明：测试发送数据22
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第22个数据虚部
 bit[11:0]   测试波形模式下，第22个数据实部
   UNION结构:  WBBP_TX_SEND_DATA22_UNION */
#define WBBP_TX_SEND_DATA22_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E074)

/* 寄存器说明：测试发送数据23
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第23个数据虚部
 bit[11:0]   测试波形模式下，第23个数据实部
   UNION结构:  WBBP_TX_SEND_DATA23_UNION */
#define WBBP_TX_SEND_DATA23_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E078)

/* 寄存器说明：测试发送数据24
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第24个数据虚部
 bit[11:0]   测试波形模式下，第24个数据实部
   UNION结构:  WBBP_TX_SEND_DATA24_UNION */
#define WBBP_TX_SEND_DATA24_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E07C)

/* 寄存器说明：测试发送数据25
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第25个数据虚部
 bit[11:0]   测试波形模式下，第25个数据实部
   UNION结构:  WBBP_TX_SEND_DATA25_UNION */
#define WBBP_TX_SEND_DATA25_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E080)

/* 寄存器说明：测试发送数据26
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第26个数据虚部
 bit[11:0]   测试波形模式下，第26个数据实部
   UNION结构:  WBBP_TX_SEND_DATA26_UNION */
#define WBBP_TX_SEND_DATA26_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E084)

/* 寄存器说明：测试发送数据27
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第27个数据虚部
 bit[11:0]   测试波形模式下，第27个数据实部
   UNION结构:  WBBP_TX_SEND_DATA27_UNION */
#define WBBP_TX_SEND_DATA27_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E088)

/* 寄存器说明：测试发送数据28
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第28个数据虚部
 bit[11:0]   测试波形模式下，第28个数据实部
   UNION结构:  WBBP_TX_SEND_DATA28_UNION */
#define WBBP_TX_SEND_DATA28_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E08C)

/* 寄存器说明：测试发送数据29
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第29个数据虚部
 bit[11:0]   测试波形模式下，第29个数据实部
   UNION结构:  WBBP_TX_SEND_DATA29_UNION */
#define WBBP_TX_SEND_DATA29_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E090)

/* 寄存器说明：测试发送数据30
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第30个数据虚部
 bit[11:0]   测试波形模式下，第30个数据实部
   UNION结构:  WBBP_TX_SEND_DATA30_UNION */
#define WBBP_TX_SEND_DATA30_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E094)

/* 寄存器说明：测试发送数据31
 bit[31:24]  保留
 bit[23:12]  测试波形模式下，第31个数据虚部
 bit[11:0]   测试波形模式下，第31个数据实部
   UNION结构:  WBBP_TX_SEND_DATA31_UNION */
#define WBBP_TX_SEND_DATA31_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E098)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     W、C和TDS TXIQMISMATCH校准使能信号（dsp_wt_tx_ip2_corr_en=0时才有效），0：上行通路为正常工作模式；1：上行产生0.96MHz正交信号。
 bit[15:1]   保留
 bit[0]      W、C和TDS 
             0:Q路
             1:I路
   UNION结构:  WBBP_TX_IQ_CAL_EN_UNION */
#define WBBP_TX_IQ_CAL_EN_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E09C)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     W&amp;TDS IP2校准使能信号0：上行通路为正常工作模式；1：上行产生0.96MHz同相信号。
 bit[15:0]   保留
   UNION结构:  WBBP_W_IP2_COR_EN_UNION */
#define WBBP_W_IP2_COR_EN_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E0A0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  W&amp;TDS TXIQMISMATCH相位校正因子，有符号数。
 bit[15:10]  保留
 bit[9:0]    W&amp;TDS TXIQMISMATCH幅度校正因子，有符号数。
   UNION结构:  WBBP_W_TX_IQ_MISMATCH_COMP_UNION */
#define WBBP_W_TX_IQ_MISMATCH_COMP_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9E0A4)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  W&amp;TDS TXIQMISMATCH Q路直流偏置补偿值，有符号数。
 bit[15:10]  保留
 bit[9:0]    W&amp;TDS TXIQMISMATCH I路直流偏置补偿值，有符号数。
   UNION结构:  WBBP_W_TX_IQ_DC_OFFSET_COMP_UNION */
#define WBBP_W_TX_IQ_DC_OFFSET_COMP_ADDR              (SOC_BBP_WCDMA_BASE_ADDR + 0x9E0A8)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    W&amp;TDS IQMISMATCH相关长度选择：0:256,1:1024,2:2048,3:4096
   UNION结构:  WBBP_IQMISMATCH_CORR_LEN_UNION */
#define WBBP_IQMISMATCH_CORR_LEN_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9E0AC)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     W&amp;TDS TX IQmismatch校准相关模块启动信号，自清零，该信号有效后启动一次相关运算。
 bit[15:1]   保留
 bit[0]      W&amp;TDS TX Iqmismatch校准相关运算结束标志清零信号，自清零。
   UNION结构:  WBBP_TX_IQ_COR_EN_UNION */
#define WBBP_TX_IQ_COR_EN_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E0B0)

/* 寄存器说明：
 bit[31]     W&amp;TDS TX Iqmismatch校准相关运算完成标志，高电平表示相关计算完成。由dsp_tx_iq_corr_clr清零。
 bit[30:29]  保留
 bit[28:16]  W&amp;TDS TX Iqmismatch校准IQ相关值上报。无符号数。
 bit[15:13]  保留
 bit[12:0]   W&amp;TDS TX Iqmismatch载漏相关值上报。无符号数。
   UNION结构:  WBBP_TX_IQ_CAL_RPT_UNION */
#define WBBP_TX_IQ_CAL_RPT_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E0B4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上行发射I/Q路直流偏置补偿值有效使能，高电平有效。有效时对上行I/Q路分别进行直流偏置值补偿。(SiGe 有效，CMOS 无效)
   UNION结构:  WBBP_UL_DC_OFFSET_EN_UNION */
#define WBBP_UL_DC_OFFSET_EN_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9E400)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  上行发射Q路直流偏置补偿值。
 bit[15:12]  保留
 bit[11:0]   上行发射I路直流偏置补偿值。
   UNION结构:  WBBP_RF_DC_OFFSET_UNION */
#define WBBP_RF_DC_OFFSET_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E404)

/* 寄存器说明：
 bit[31:24]  低切中增益时相位补偿值，有符号数。
 bit[23:16]  中切低增益时相位补偿值，有符号数。
 bit[15:8]   高切中增益时相位补偿值，有符号数。
 bit[7:0]    中切高增益时相位补偿值，有符号数。
   UNION结构:  WBBP_W_TX_LMH_PHASE_COMP_UNION */
#define WBBP_W_TX_LMH_PHASE_COMP_ADDR                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9E408)

/* 寄存器说明：
 bit[31]     上行削波bypass标志，高电平有效。复位值为高电平。
             当bypass1为高电平，削波使能关闭，数据无延时直通输出；当bypass1为低电平，bypass2为高电平，削波使能关闭，数据延时16.75chip时间后直接输出；当bypass1和bypass2均为低电平，削波使能打开，削波后数据比原数据延时17.5chip时间输出。
 bit[30]     上行削波bypass标志，高电平有效。复位值为高电平。
             当bypass1为高电平，削波使能关闭，数据无延时直通输出；当bypass1为低电平，bypass2为高电平，削波使能关闭，数据延时16.75chip时间后直接输出；当bypass1和bypass2均为低电平，削波使能打开，削波后数据比原数据延时16.75chip时间输出。
 bit[29:28]  保留
 bit[27:16]  上行削波第一级功率调整增益。当削波使能打开时，对上行RRC滤波后数据进行削波处理。
 bit[15:13]  保留
 bit[12:0]   上行削波第一级生效门限。当削波使能打开时，对上行RRC滤波后数据进行削波处理。可配范围64~8191。
   UNION结构:  WBBP_UL_RF_GATE0_UNION */
#define WBBP_UL_RF_GATE0_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9E410)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  上行削波第二级功率调整增益。当削波使能打开时，对上行RRC滤波后数据进行削波处理。
 bit[15:13]  保留
 bit[12:0]   上行削波第二级生效门限。当削波使能打开时，对上行RRC滤波后数据进行削波处理。可配范围64~8191。
   UNION结构:  WBBP_UL_RF_GATE1_UNION */
#define WBBP_UL_RF_GATE1_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9E414)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上行输出到ABB数据有效位宽指示。0表示12bit输出；1表示10bit输出，在bit[1:0]上固定填0。测试用，默认配置0。
   UNION结构:  WBBP_ABB_DATA_WIDTH_UNION */
#define WBBP_ABB_DATA_WIDTH_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E420)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:8]   测试模式下射频发射数据。
 bit[7:1]    保留
 bit[0]      测试模式下发射数据使能，高电平有效。此时射频发送数据为CPU直接配置的值，未经过调制及RRC滤波。
   UNION结构:  WBBP_RF_SEND_DATA_UNION */
#define WBBP_RF_SEND_DATA_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E424)

/* 寄存器说明：上下采样滤波器内部累加移位bit数
 bit[31:4]   保留
 bit[3:0]    上下采样滤波器内部累加器移位bit数
             上电之后只配置一次，配置范围10~13
   UNION结构:  WBBP_FIR_SFTBIT_UNION */
#define WBBP_FIR_SFTBIT_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9E800)

/* 寄存器说明：配置特殊时隙
 bit[31:1]   保留
 bit[0]      DSP在配置特殊时隙
   UNION结构:  WBBP_UPPTS_FLG_UNION */
#define WBBP_UPPTS_FLG_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9E804)

/* 寄存器说明：上行功率衰减寄存器
 bit[31:29]  保留
 bit[28:24]  上行功控模块乘以衰减因子后的移位比特数，配置范围13~16
 bit[23:17]  保留
 bit[16:0]   上行功控模块的衰减因子值
   UNION结构:  WBBP_PC_GENE_UNION */
#define WBBP_PC_GENE_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x9E808)

/* 寄存器说明：ABB数据接口规格寄存器
 bit[31:16]  正常数据包络发送完成后，输出给DA的冗余0的个数，该功能为保留功能
 bit[15:0]   保留
   UNION结构:  WBBP_ABB_FMT_UNION */
#define WBBP_ABB_FMT_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x9E80C)

/* 寄存器说明：TDS PA档位
 bit[31:3]   保留
 bit[2:0]    TDS PA档位
   UNION结构:  WBBP_TDS_PA_CHANGE_MODE_UNION */
#define WBBP_TDS_PA_CHANGE_MODE_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9E810)

/* 寄存器说明：数采数据选择
 bit[31:3]   保留
 bit[2:0]    dbg数据选择：
             3'd0: RRC数据输出；
             3'd1: CFR/FIR数据输出；
             3'd2: PC数据输出；
             3'd3: phase comp数据输出
             3'd4: Txiq数据输出
             3'd5:FIFO数据输出
             3'd6:sc_filter数据输出
             3'd7:freq_error数据输出；
   UNION结构:  WBBP_DBG_DATA_SEL_UNION */
#define WBBP_DBG_DATA_SEL_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E814)

/* 寄存器说明：可维可测功能
 bit[31:2]   保留
 bit[1]      参数强制锁定
 bit[0]      da_on包络数据统计有效
   UNION结构:  WBBP_DFT_FUNC_UNION */
#define WBBP_DFT_FUNC_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x9E818)

/* 寄存器说明：数据包络统计
 bit[31:16]  da_on包络个数
 bit[15:0]   保留
   UNION结构:  WBBP_TX_RX_CNT_UNION */
#define WBBP_TX_RX_CNT_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9E81C)

/* 寄存器说明：rrc输出信号
 bit[31:14]  保留
 bit[13:0]   [13:12]为rrc输出的da_on/dvld；
             [11:0]为rrc的输出的上行数据；
   UNION结构:  WBBP_RRC_UNION */
#define WBBP_RRC_ADDR                                 (SOC_BBP_WCDMA_BASE_ADDR + 0x9E820)

/* 寄存器说明：上行fir和pc输出信号
 bit[31:30]  保留
 bit[29:16]  [13:12]为fir输出的da_on/dvld；
             [11:0]为fir的输出的上行数据；
 bit[15:14]  保留
 bit[13:0]   [13:12]为pc输出的da_on/dvld；
             [11:0]为pc的输出上行数据；
   UNION结构:  WBBP_FIR_TXIQ_UNION */
#define WBBP_FIR_TXIQ_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x9E828)

/* 寄存器说明：上行txiq输出信号
 bit[31:30]  保留
 bit[29:16]  [29:28]为txiq输出的da_on/dvld；
             [27:16]为txiq的输出上行数据；
 bit[15:0]   保留
   UNION结构:  WBBP_SINC_DAIU_UNION */
#define WBBP_SINC_DAIU_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9E82C)

/* 寄存器说明：
   详      述：默认保留
   UNION结构 ：无 */
#define WBBP_ULFE_RESERVED1_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E840)

/* 寄存器说明：
   详      述：默认保留
   UNION结构 ：无 */
#define WBBP_ULFE_RESERVED2_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E844)

/* 寄存器说明：
   详      述：默认保留
   UNION结构 ：无 */
#define WBBP_ULFE_RESERVED3_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E848)

/* 寄存器说明：FIFO输出信号
 bit[31:14]  保留
 bit[13:0]   W、TDS和C:
             [13:12]为FIFO输出的da_on/dvld；
             [11:0]为FIFO输出的上行数据；
   UNION结构:  WBBP_FIFO_UNION */
#define WBBP_FIFO_ADDR                                (SOC_BBP_WCDMA_BASE_ADDR + 0x9E84C)

/* 寄存器说明：上行采样纠偏和频偏校正输出信号
 bit[31:30]  保留
 bit[29:16]  W、TDS和C:
             [29:28]为采样纠偏滤波器输出的da_on/dvld；
             [27:16]为采样纠偏滤波器输出的上行数据；
 bit[15:14]  保留
 bit[13:0]   W、TDS和C:
             [13:12]为频偏校正输出的da_on/dvld；
             [11:0]为频偏校正输出上行数据；
   UNION结构:  WBBP_SC_FREQ_UNION */
#define WBBP_SC_FREQ_ADDR                             (SOC_BBP_WCDMA_BASE_ADDR + 0x9E850)

/* 寄存器说明：单TCXO使能
 bit[31:1]   保留
 bit[0]      W和C单TCXO使能信号：
             1'b0:单TCXO使能关闭
             1'b1:单TCXO使能打开
             此使能信号只与时钟的选择有关系
   UNION结构:  WBBP_ULFE_TCXO_EN_UNION */
#define WBBP_ULFE_TCXO_EN_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E854)

/* 寄存器说明：dsp强配采样纠偏值
 bit[31:21]  保留
 bit[20:12]  TDS:
             软件强配采样纠偏值，有符号数
 bit[11:1]   W和C:
             双TCXO软件强配采样纠偏值，和下行一致，范围为[-1023,0123]。
 bit[0]      W:
             双TCXO软件强配采样纠偏值使能信号
   UNION结构:  WBBP_SC_FILTER_OFFSET_UNION */
#define WBBP_SC_FILTER_OFFSET_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9E85C)

/* 寄存器说明：dsp强配使能信号
 bit[31:1]   保留
 bit[0]      W和C:
             双TCXO下软件强配采样纠偏值更新脉冲信号
   UNION结构:  WBBP_SC_CFG_IND_UNION */
#define WBBP_SC_CFG_IND_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9E860)

/* 寄存器说明：FIFO清零电平信号
 bit[31:1]   保留
 bit[0]      W和C FIFO清零电平信号:
             1'b0:FIFO不清零
             1'b1:FIFO清零
   UNION结构:  WBBP_FIFO_CLR_EN_UNION */
#define WBBP_FIFO_CLR_EN_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9E864)

/* 寄存器说明：FIFO上报清零信号
 bit[31:1]   保留
 bit[0]      W和C FIFO异常空满上报状态清零信号:
             1'b0:FIFO异常空满不清零
             1'b1:FIFO异常空满清零
   UNION结构:  WBBP_FIFO_RPT_CLR_UNION */
#define WBBP_FIFO_RPT_CLR_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E868)

/* 寄存器说明：C模功率补偿值
 bit[31:12]  保留
 bit[11:0]   C模功率补偿值，无符号数
             
   UNION结构:  WBBP_C_ATTEN_VALUE_UNION */
#define WBBP_C_ATTEN_VALUE_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9E86C)

/* 寄存器说明：FIFO 异常空满上报
 bit[31:21]  保留
 bit[20:16]  W和C FIFO 读侧剩余数据个数
 bit[15:13]  保留
 bit[12:8]   W和C FIFO 写侧剩余数据个数
 bit[7:5]    保留
 bit[4]      W和C FIFO 满标志:
             1'b0:FIFO不满；
             1'b1:FIFO满。
 bit[3:1]    保留
 bit[0]      W和C FIFO 异常空标志:
             1'b0:FIFO不异常空；
             1'b1:FIFO异常空。
   UNION结构:  WBBP_FIFO_EMPTY_FULL_UNION */
#define WBBP_FIFO_EMPTY_FULL_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9E870)

/* 寄存器说明：C模相位补偿值
 bit[31:22]  保留
 bit[21:11]  C模相位补偿值，有符号数
             
 bit[10:0]   C模相位补偿值，有符号数
             
   UNION结构:  WBBP_C_PHASE_COMP_UNION */
#define WBBP_C_PHASE_COMP_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9E874)

/* 寄存器说明：采样纠偏估计清零
 bit[31:1]   保留
 bit[0]      C模在打开上行时，sc_cal模块的积分清零使能信号
             1'b1:在打开上行时，sc_cal模块的积分自动清零；
             1'b0:在打开上行时，sc_cal模块的积分不清零；(W模不需要配置)
   UNION结构:  WBBP_SC_CAL_CLR_UNION */
#define WBBP_SC_CAL_CLR_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9E878)

/* 寄存器说明：采样纠偏估计清零
 bit[31:15]  保留
 bit[14:0]   W和C Fc,up/Fc，无符号数
   UNION结构:  WBBP_SC_CAL_UL_RATIO_UNION */
#define WBBP_SC_CAL_UL_RATIO_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9E880)

/* 寄存器说明：NCO相位累加清零
 bit[31:1]   保留
 bit[0]      W、C和TDS NCO模块在调试或出错的情况下，相位累加值清零脉冲信号
   UNION结构:  WBBP_NCO_PH_CLR_UNION */
#define WBBP_NCO_PH_CLR_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9E884)

/* 寄存器说明：NCO初始相位值
   详      述：TDS NCO初始相位值
   UNION结构 ：无 */
#define WBBP_TDS_NCO_OFFSET_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9E888)

/* 寄存器说明：NCO频偏使能
 bit[31:1]   保留
 bit[0]      W/C NCO模块频偏输入强配使能信号
   UNION结构:  WBBP_NCO_FW_EN_UNION */
#define WBBP_NCO_FW_EN_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9E88C)

/* 寄存器说明：NCO频偏值
   详      述：W、C和TDS NCO模块频偏输入强配值，为无符号数
   UNION结构 ：无 */
#define WBBP_NCO_FW_ADDR                              (SOC_BBP_WCDMA_BASE_ADDR + 0x9E890)

/* 寄存器说明：RRC Q路延时样点数
 bit[31:2]   保留
 bit[1:0]    C RRC Q路延时样点数
             2'b0：不延时
             2'b1：延1样点
             2'b10：延2样点
             2'b11：延3样点
             W/TDS为0
   UNION结构:  WBBP_RRC_Q_DELAY_UNION */
#define WBBP_RRC_Q_DELAY_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9E894)

/* 寄存器说明：IQ 校准使能
 bit[31:1]   保留
 bit[0]      W校准模式选择信号：
             1'b1:校准单音信号立刻生效；
             1'b0:校准单音信号在帧头生效。
   UNION结构:  WBBP_CALBRT_MOD_UNION */
#define WBBP_CALBRT_MOD_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9E898)

/* 寄存器说明：TDS采样调整步长
 bit[31:17]  保留
 bit[16:0]   tds模式下采样调整步长;17bit
   UNION结构:  WBBP_UL_TDS_SC_ULT_FSMP_UNION */
#define WBBP_UL_TDS_SC_ULT_FSMP_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA00)

/* 寄存器说明：TDS采样调整初始偏差值
   详      述：tds模式下采样调整初始偏差值;32bit
   UNION结构 ：无 */
#define WBBP_UL_TDS_SC_INI_FSMP_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA04)

/* 寄存器说明：TDS采样调整步长有效指示
 bit[31:1]   保留
 bit[0]      tds dsp配置采样调整步长有效指示,为脉冲信号;
   UNION结构:  WBBP_UL_TDS_SC_ULT_VLD_UNION */
#define WBBP_UL_TDS_SC_ULT_VLD_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA08)

/* 寄存器说明：TDS采样初始偏差值有效指示
 bit[31:1]   保留
 bit[0]      tds dsp配置采样初始偏差值有效指示,为脉冲信号;
   UNION结构:  WBBP_UL_TDS_SC_INI_VLD_UNION */
#define WBBP_UL_TDS_SC_INI_VLD_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA0C)

/* 寄存器说明：TDS参数立即生效模式
 bit[31:1]   保留
 bit[0]      tds模式下参数立即生效模式：
             0：不立即生效，用da_on上升沿和*vld锁存参数；
             1：立即生效，直接根据*vld去锁存参数； 
             默认值为0。
             (保留)
   UNION结构:  WBBP_UL_TDS_SC_MOD_UNION */
#define WBBP_UL_TDS_SC_MOD_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA10)

/* 寄存器说明：fifo几乎空，几乎满的异常删加点使能
 bit[31:1]   保留
 bit[0]      W、C和TDS sc_cal模块在fifo几乎空，几乎满的异常删加点使能：
             0：关闭异常删加点功能；
             1：打开异常删加点功能。
             默认打开。
   UNION结构:  WBBP_UL_SC_ABN_DEL_EN_UNION */
#define WBBP_UL_SC_ABN_DEL_EN_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA14)

/* 寄存器说明：上报给dsp计算的采样纠偏值
   详      述：W、C和TDS sc_cal模块在da_on下降沿上报给dsp计算的采样纠偏值;
   UNION结构 ：无 */
#define WBBP_UL_TDS_SC_FSMP_RPT_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA18)

/* 寄存器说明：SC_CAL删加点个数上报
 bit[31:16]  W、C和TDS sc_cal模块计算删点次数统计。
 bit[15:0]   W、C和TDS sc_cal模块计算加点次数统计。
   UNION结构:  WBBP_UL_SC_CAL_NUM_RPT_UNION */
#define WBBP_UL_SC_CAL_NUM_RPT_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA1C)

/* 寄存器说明：FIFO 异常空满次数上报
 bit[31:24]  W、C和TDS FIFO满次数上报
 bit[23:16]  W、C和TDS FIFO空次数上报
 bit[15:8]   W、C和TDS FIFO将满次数上报
 bit[7:0]    W、C和TDS FIFO将空次数上报
   UNION结构:  WBBP_UL_FIFO_ABN_NUM_UNION */
#define WBBP_UL_FIFO_ABN_NUM_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA20)

/* 寄存器说明：sc_cal删加点次数统计清零
 bit[31:2]   保留
 bit[1]      W、C和TDS sc_cal模块计算删点次数统计清零。
 bit[0]      W、C和TDS sc_cal模块计算加点次数统计清零。
   UNION结构:  WBBP_UL_SC_CAL_NUM_RPT_CLR_UNION */
#define WBBP_UL_SC_CAL_NUM_RPT_CLR_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA24)

/* 寄存器说明：sc_filter参数来源
 bit[31:1]   保留
 bit[0]      sc_filter模块的参数来源：
             1'b1：参数来源于sc_cal；
             1'b0：W参数来源于多径或强配，TDS和C模来源于强配。
   UNION结构:  WBBP_UL_SC_CAL_PARA_EN_UNION */
#define WBBP_UL_SC_CAL_PARA_EN_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA28)

/* 寄存器说明：sc_cal模块积分功能使能信号
 bit[31:1]   保留
 bit[0]      sc_cal模块积分功能使能信号，使能关闭情况下，删加点和offset都为0：
             1'b0:积分使能关闭；
             1'b1:积分使能打开。
   UNION结构:  WBBP_UL_DEL_ADD_EN_UNION */
#define WBBP_UL_DEL_ADD_EN_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA2C)

/* 寄存器说明：Max_power-2~Max_power-5对应的量化参数step_v
 bit[31:27]  保留
 bit[26:18]  Max_power-3
 bit[17:9]   Max_power-4
 bit[8:0]    Max_power-5
   UNION结构:  WBBP_DPD_STEP1_UNION */
#define WBBP_DPD_STEP1_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA34)

/* 寄存器说明：Max_power-2~Max_power-5对应的量化参数step_v
 bit[31:27]  保留
 bit[26:18]  Max_power
 bit[17:9]   Max_power-1
 bit[8:0]    Max_power-2
   UNION结构:  WBBP_DPD_STEP2_UNION */
#define WBBP_DPD_STEP2_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA38)

/* 寄存器说明：Max_power-2~Max_power-5对应的量化参数step_v
 bit[31:18]  保留
 bit[17:9]   Max_power+1
 bit[8:0]    Max_power+1
   UNION结构:  WBBP_DPD_STEP3_UNION */
#define WBBP_DPD_STEP3_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA3C)

/* 寄存器说明：DPD功率的温补和频补的合并补偿值
 bit[31:11]  保留
 bit[10:0]   DPD
   UNION结构:  WBBP_DPD_COMP_UNION */
#define WBBP_DPD_COMP_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA40)

/* 寄存器说明：DPD ram tabel选择
 bit[31:1]   保留
 bit[0]      DPD
   UNION结构:  WBBP_DPD_RAM_TABLE_SEL_UNION */
#define WBBP_DPD_RAM_TABLE_SEL_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA44)

/* 寄存器说明：CPU接口配置的单音频率选择信号
 bit[31:1]   保留
 bit[0]      CPU
   UNION结构:  WBBP_TX_TONE_FREQ_SEL_UNION */
#define WBBP_TX_TONE_FREQ_SEL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA48)

/* 寄存器说明：上变频NCO累加相位清零
 bit[31:1]   保留
 bit[0]      上变频NCO模块在调试或出错的情况下，相位累加值清零脉冲信号
   UNION结构:  WBBP_DSP_DC_NCO_PH_CLR_UNION */
#define WBBP_DSP_DC_NCO_PH_CLR_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA4C)

/* 寄存器说明：主辅载波共轭选择
 bit[31:1]   保留
 bit[0]      主载波和辅载波上变频共轭选择信号，1'b0:辅载波虚部取反，主载波不取反；1'b1:主载波虚部取反，辅载波不取反
   UNION结构:  WBBP_DSP_CONJU_SEL_UNION */
#define WBBP_DSP_CONJU_SEL_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA50)

/* 寄存器说明：主辅载波上变频选择
 bit[31:5]   保留
 bit[4]      DSP强制配置NCO频点搬移是否随dcupa_active_flag指示生效。为1表示频点搬移受dcupa_active_flag控制，默认为1。
 bit[3:1]    保留
 bit[0]      DCUPA模式下DC/SC切换时上行频点切换模式，1：sc下使用DC搬移频点模式
   UNION结构:  WBBP_DCUPA_SW_UL_FREQ_MOD_UNION */
#define WBBP_DCUPA_SW_UL_FREQ_MOD_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA54)

/* 寄存器说明：DC NCO频偏值
   详      述：W上变频NCO频偏值，为无符号数
   UNION结构 ：无 */
#define WBBP_DC_NCO_FW_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA58)

/* 寄存器说明：DPD bypass
 bit[31:1]   保留
 bit[0]      DPD补偿通路
   UNION结构:  WBBP_DPD_BYPASS_UNION */
#define WBBP_DPD_BYPASS_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA5C)

/* 寄存器说明：DPD LUT寻表方式
 bit[31:1]   保留
 bit[0]      DPD LUT查找表的子表地址映射模式模式选择信号
             1’b0：DPD LUT查找表的8档的8个子表采用绝对发送功率方式查表
             1’b1：DPD LUT查找表的8档的8个子表采用根据射频增益衰减表查表地址值查表。
             
   UNION结构:  WBBP_DPD_LUT_ADDR_SEL_UNION */
#define WBBP_DPD_LUT_ADDR_SEL_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA60)

/* 寄存器说明：DPD LUT门限
 bit[31:27]  保留
 bit[26:16]  DPD生效功率门限1。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
 bit[15:11]  保留
 bit[10:0]   DPD生效功率门限0。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
   UNION结构:  WBBP_DPD_THRESHOLD0_1_UNION */
#define WBBP_DPD_THRESHOLD0_1_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA64)

/* 寄存器说明：DPD LUT门限
 bit[31:27]  保留
 bit[26:16]  DPD生效功率门限3。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
 bit[15:11]  保留
 bit[10:0]   DPD生效功率门限2。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
   UNION结构:  WBBP_DPD_THRESHOLD2_3_UNION */
#define WBBP_DPD_THRESHOLD2_3_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA68)

/* 寄存器说明：DPD LUT门限
 bit[31:27]  保留
 bit[26:16]  DPD生效功率门限5。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
 bit[15:11]  保留
 bit[10:0]   DPD生效功率门限4。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
   UNION结构:  WBBP_DPD_THRESHOLD4_5_UNION */
#define WBBP_DPD_THRESHOLD4_5_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA6C)

/* 寄存器说明：DPD LUT门限
 bit[31:27]  保留
 bit[26:16]  DPD生效功率门限7。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
 bit[15:11]  保留
 bit[10:0]   DPD生效功率门限6。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
   UNION结构:  WBBP_DPD_THRESHOLD6_7_UNION */
#define WBBP_DPD_THRESHOLD6_7_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA70)

/* 寄存器说明：DPD LUT门限
 bit[31:11]  保留
 bit[10:0]   DPD生效功率门限8。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值
   UNION结构:  WBBP_DPD_THRESHOLD8_UNION */
#define WBBP_DPD_THRESHOLD8_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA74)

/* 寄存器说明：单音模块使能
 bit[31:1]   保留
 bit[0]      CFR前单/双音信号发送使能，在上行模式不为TDS-CDMA时配置有效。1’b1:U/X模CFR前单/双音信号发送使能，当该使能有效时，BBP根据软件配置的I/Q和周期点数周期发送单/双音信号。
   UNION结构:  WBBP_COM_CW_EN_UNION */
#define WBBP_COM_CW_EN_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA78)

/* 寄存器说明：单音正（余）弦波周期内的点数
 bit[31:5]   保留
 bit[4:0]    CFR前单/双音信号正（余）弦波周期内的点数，默认为15，采用15.36M/(dsp_com_cw_cnt+1)得到需要发送信号的周期频率，例如默认15.36M/16=0.96M。
   UNION结构:  WBBP_COM_CW_CNT_UNION */
#define WBBP_COM_CW_CNT_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA7C)

/* 寄存器说明：单音模式选择信号
 bit[31:1]   保留
 bit[0]      CFR前单/双音信号发送模式选择信号
             1’b0:按照软件配置的加权系数立即生效的加权模式
             1’b1:BBP自动周期性循环发送模
             。
   UNION结构:  WBBP_COM_CW_TX_MODE_UNION */
#define WBBP_COM_CW_TX_MODE_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA80)

/* 寄存器说明：单音每个周期发送的点数
 bit[31:2]   保留
 bit[1:0]    当发送模式为自动发送时(dsp_cw_tx_mode=1’b1),每个周期发送的点数。
             2’d0：每个周期发送1024个点
             2’d1：每个周期发送2048个点
             2’d2：每个周期发送3072个点
             2’d3：每个周期发送4096个点
             
   UNION结构:  WBBP_COM_CW_TX_PRD_UNION */
#define WBBP_COM_CW_TX_PRD_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA84)

/* 寄存器说明：单音加权系数
 bit[31:24]  保留
 bit[23:0]   单/双音I/Q幅度加权系数，无符号数；
             当dsp_com_cw_tx_mode=1’b0时，配置的补偿系数直接补偿立即生效
             当dsp_com_cw_tx_mode=1’b1时，该系数作为初始发送的起始加权系数。
             [23:12]:Q路的加权系数
             [11:0]:I路的加权系数
             
             
   UNION结构:  WBBP_COM_CW_COEF_UNION */
#define WBBP_COM_CW_COEF_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA88)

/* 寄存器说明：单音加权步长
 bit[31:8]   保留
 bit[7:0]    当dsp_com_cw_tx_mode=1'b1时,每个周期发送结束后将加权系数增加步长后发送下一个周期，无符号数
   UNION结构:  WBBP_COM_CW_STEP_UNION */
#define WBBP_COM_CW_STEP_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA8C)

/* 寄存器说明：nco预充选择
 bit[31:1]   保留
 bit[0]      nco模块da_on选择，用来做nco预充。当dsp_cw_pre_sel==1'b0时，选择rrc da_on信号，正常模式下使用；dsp_cw_pre_sel==1'b1时，选择dsp_nco_en信号，供削波前单音校准时使用。
   UNION结构:  WBBP_CW_PRE_SEL_UNION */
#define WBBP_CW_PRE_SEL_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA90)

/* 寄存器说明：DCUPA激活状态上报
 bit[31:1]   保留
 bit[0]      上行前端dcupa激活状态上报。
   UNION结构:  WBBP_ULFE_DCUPA_EN_RPT_UNION */
#define WBBP_ULFE_DCUPA_EN_RPT_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA94)

/* 寄存器说明：DPD相关状态上报
 bit[31:27]  保留
 bit[26:24]  上行DPD子表选择，范围0~7
 bit[23]     保留
 bit[22:12]  上行最大理论发射功率修正值
 bit[11]     保留
 bit[10:0]   上行理论发射功率
   UNION结构:  WBBP_ULFE_DPD_RPT_UNION */
#define WBBP_ULFE_DPD_RPT_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA98)

/* 寄存器说明：上行前端RF回退索引值上报
 bit[31:9]   保留
 bit[8:0]    上行前端RF回退索引值上报。
   UNION结构:  WBBP_ATTEN_TABLE_ADDR_RPT_UNION */
#define WBBP_ATTEN_TABLE_ADDR_RPT_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x9EA9C)



/***======================================================================***
                     (8/10) register_define_irm_cs
 ***======================================================================***/
/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    用于irm_cs模式选择，影响irm_cs内部时钟切换和模式切换，默认都为0。
             3'b001，UMTS模式（包括均衡，译码R99相关RAM）；
             3'b010，无意义（原为LTE模式上行HARQ部分）；
             3'b100，CDMA模式；
             3'b000，无（default）。
   UNION结构:  WBBP_IRM_CS_RAM_CTRL_UNION */
#define WBBP_IRM_CS_RAM_CTRL_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x97000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      irm_cs模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。
   UNION结构:  WBBP_IRM_CS_CLK_BYPASS_UNION */
#define WBBP_IRM_CS_CLK_BYPASS_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x97004)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  WBBP_MEM_CTRL0_CS_UNION */
#define WBBP_MEM_CTRL0_CS_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9700C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  WBBP_MEM_CTRL1_CS_UNION */
#define WBBP_MEM_CTRL1_CS_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x97010)



/***======================================================================***
                     (9/10) register_define_dump
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      采数模块总使能，并控制时钟门控，无论哪种模式采数，首先要配置此信号有效
   UNION结构:  WBBP_DUMP_EN_W_UNION */
#define WBBP_DUMP_EN_W_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x98140)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      门控bypass，1表示时钟常开，即门控bypass
 bit[1]      门控bypass，1表示时钟常开，即门控bypass
 bit[0]      门控bypass，1表示时钟常开，即门控bypass
   UNION结构:  WBBP_DUMP_CLKGATE_BYPASS_W_UNION */
#define WBBP_DUMP_CLKGATE_BYPASS_W_ADDR               (SOC_BBP_WCDMA_BASE_ADDR + 0x98144)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      采数FIFO初始化清零脉冲
   UNION结构:  WBBP_DUMP_FIFO_CLR_W_UNION */
#define WBBP_DUMP_FIFO_CLR_W_ADDR                     (SOC_BBP_WCDMA_BASE_ADDR + 0x98148)

/* 寄存器说明：
   详      述：采集数据的长度，即需要采集的32bit数据个数，全0表示无限长
   UNION结构 ：无 */
#define WBBP_DUMP_DATA_LENGTH_W_ADDR                  (SOC_BBP_WCDMA_BASE_ADDR + 0x9814C)

/* 寄存器说明：
 bit[31:20]  采数起始位置，32’hffffffff表示立即启动
             [31:20]：CFN位置；
             
             C模下，bit[28:0]表示c_base_cnt上的位置，bit[31:29]配置为0。
 bit[19:16]  采数起始位置，32’hffffffff表示立即启动
             [19:16]：帧内slot位置；
 bit[15:4]   采数起始位置，32’hffffffff表示立即启动
             [15:4]：slot内chip位置；
 bit[3:0]    采数起始位置，32’hffffffff表示立即启动
             [3:0]：chip内clk位置
   UNION结构:  WBBP_DUMP_START_TIME_W_UNION */
#define WBBP_DUMP_START_TIME_W_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x98150)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    0：表示水线深度2；
             1：表示水线深度4；
             2：表示水线深度8；
             3：表示水线深度16；
             4：表示水线深度32；
             5：表示水线深度64；
             6：表示水线深度128；
             
   UNION结构:  WBBP_DUMP_FIFO_WATERMARKER_W_UNION */
#define WBBP_DUMP_FIFO_WATERMARKER_W_ADDR             (SOC_BBP_WCDMA_BASE_ADDR + 0x98154)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件启动数据采集，在dump_en有效的情况下起作用，wclr信号
   UNION结构:  WBBP_DUMP_START_W_UNION */
#define WBBP_DUMP_START_W_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x98158)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件强制结束数据采集，wclr信号
   UNION结构:  WBBP_DUMP_STOP_W_UNION */
#define WBBP_DUMP_STOP_W_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x9815C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      采数FIFO上溢
 bit[0]      采数FIFO下溢
   UNION结构:  WBBP_DUMP_FLOW_UNION */
#define WBBP_DUMP_FLOW_ADDR                           (SOC_BBP_WCDMA_BASE_ADDR + 0x98160)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      采数FIFO溢出清零
   UNION结构:  WBBP_DUMP_FLOW_CLR_UNION */
#define WBBP_DUMP_FLOW_CLR_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x98164)

/* 寄存器说明：
   详      述：
   UNION结构 ：无 */
#define WBBP_DUMP_DMA_RDATA_W_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x9816C)



/***======================================================================***
                     (10/10) register_define_dbg
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      DBG上报使能，1表示打开上报功能，0表示关闭上报功能。完成时钟门控
   UNION结构:  WBBP_BBP_DBG_EN_UNION */
#define WBBP_BBP_DBG_EN_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x99000)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11]     时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[10]     时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[9]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[8]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[7]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[6]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[5]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[4]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[3]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[2]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[1]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
 bit[0]      时钟bypass使能，1表示时钟常开，0表示时钟门控有效
   UNION结构:  WBBP_BBP_DBG_BYPASS_UNION */
#define WBBP_BBP_DBG_BYPASS_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x99004)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    BBP接口选择信号
             0：表示选择LocalBus，即监测所有BBP配置信息
             1：表示选择WBBP IMI接口，即仅监测WBBP配置信息
             2：表示选择GBBP1 IMI接口，即仅监测GBBP配置信息
             3：保留不用
             在V8R1中只有0值才有意义
   UNION结构:  WBBP_BBP_IF_SEL_UNION */
#define WBBP_BBP_IF_SEL_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x99008)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    DDR中DBG空间大小，2Kbyte为单位。如配置为4表示DBG空间为4个2Kbyte。
   UNION结构:  WBBP_DBG_DDR_2K_NO_UNION */
#define WBBP_DBG_DDR_2K_NO_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9900C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    DBG输入时钟选择：
             0：表示使用模式一时钟；
             1：表示使用模式二时钟；
             2：表示使用模式三时钟；
   UNION结构:  WBBP_DBG_CLK_IN_SEL_UNION */
#define WBBP_DBG_CLK_IN_SEL_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x99010)

/* 寄存器说明：
   详      述：软件配置的包头中reserve信息
   UNION结构 ：无 */
#define WBBP_DBG_HEAD_SERVE_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x99014)

/* 寄存器说明：
   详      述：软件配置的包头中RTC信息
   UNION结构 ：无 */
#define WBBP_DBG_HEAD_RTC_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x99018)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:2]    COMM接口信息使用时间戳选择
             0表示使用WBBP定时
             1表示使用GBBP定时
             2 表示使用CBBP定时
 bit[1:0]    COMM信息使用时间戳选择
             0表示使用WBBP定时
             1表示使用GBBP定时
             2 表示使用CBBP定时
   UNION结构:  WBBP_DBG_TIMING_SEL_UNION */
#define WBBP_DBG_TIMING_SEL_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9901C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第一段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报
   UNION结构:  WBBP_MASK_ADDR0_START_UNION */
#define WBBP_MASK_ADDR0_START_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x99020)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第一段屏蔽地址结束位置
   UNION结构:  WBBP_MASK_ADDR0_END_UNION */
#define WBBP_MASK_ADDR0_END_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x99024)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第二段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报
   UNION结构:  WBBP_MASK_ADDR1_START_UNION */
#define WBBP_MASK_ADDR1_START_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x99028)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第二段屏蔽地址结束位置
   UNION结构:  WBBP_MASK_ADDR1_END_UNION */
#define WBBP_MASK_ADDR1_END_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9902C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第三段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报
   UNION结构:  WBBP_MASK_ADDR2_START_UNION */
#define WBBP_MASK_ADDR2_START_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x99030)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第三段屏蔽地址结束位置
   UNION结构:  WBBP_MASK_ADDR2_END_UNION */
#define WBBP_MASK_ADDR2_END_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x99034)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第四段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报
   UNION结构:  WBBP_MASK_ADDR3_START_UNION */
#define WBBP_MASK_ADDR3_START_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x99038)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第四段屏蔽地址结束位置
   UNION结构:  WBBP_MASK_ADDR3_END_UNION */
#define WBBP_MASK_ADDR3_END_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x9903C)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    DBG FIFO水线选择
             0：表示水线为2；
             1：表示水线为4；
             2：表示水线为8；
             3：表示水线为16；
             4：表示水线为32；
             5：表示水线为64；
             
   UNION结构:  WBBP_DBG_FIFO_WATERMARKER_UNION */
#define WBBP_DBG_FIFO_WATERMARKER_ADDR                (SOC_BBP_WCDMA_BASE_ADDR + 0x99040)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    DBG上报信息开关，1表示上报相应信息，0表示不上报相应信息。
             bit[0]：表示w_fe_top信息是否上报；
             bit[1]：表示g_fe_top信息是否上报；
             bit[2]：表示BBP接口信息是否上报；
             bit[3]：表示COMM信息是否上报；
             bit[4]：表示COMM接口信息是否上报；
             
   UNION结构:  WBBP_BBP_DBG_SWITCH_UNION */
#define WBBP_BBP_DBG_SWITCH_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x99044)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      DBG打开信号，Wclr
   UNION结构:  WBBP_BBP_DBG_START_UNION */
#define WBBP_BBP_DBG_START_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x99048)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      DBG停止信号，Wclr
   UNION结构:  WBBP_BBP_DBG_STOP_UNION */
#define WBBP_BBP_DBG_STOP_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9904C)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    DDR空间上报指示，1表示该空间已将上报了DBG信息，bit0表示第一段2K byte空间，bit1表示第二段2K byte空间，以此类推。
   UNION结构:  WBBP_DDR_BIT_INDEX_UNION */
#define WBBP_DDR_BIT_INDEX_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x99050)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    DDR上报空间清零信号，将ddr_bit_index对应bit清零
   UNION结构:  WBBP_DDR_BIT_INDEX_CLR_UNION */
#define WBBP_DDR_BIT_INDEX_CLR_ADDR                   (SOC_BBP_WCDMA_BASE_ADDR + 0x99054)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17]     DBG  FIFO上溢
 bit[16]     DBG   FIFO下溢
 bit[15:10]  保留
 bit[9]      BBP COMM接口  FIFO上溢
 bit[8]      BBP COMM接口   FIFO下溢
 bit[7]      BBP COMM  FIFO上溢
 bit[6]      BBP COMM   FIFO下溢
 bit[5]      BBP接口  FIFO上溢
 bit[4]      BBP接口   FIFO下溢
 bit[3]      G_FE  FIFO上溢
 bit[2]      G_FE  FIFO下溢
 bit[1]      W_FE  FIFO上溢
 bit[0]      W_FE  FIFO下溢
   UNION结构:  WBBP_DBG_FLOW_UNION */
#define WBBP_DBG_FLOW_ADDR                            (SOC_BBP_WCDMA_BASE_ADDR + 0x99058)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     DBG   FIFO溢出清零
 bit[15:9]   保留
 bit[8]      BBP COMM接口 FIFO溢出清零
 bit[7]      保留
 bit[6]      BBP COMM FIFO溢出清零
 bit[5]      保留
 bit[4]      BBP接口 FIFO溢出清零
 bit[3]      保留
 bit[2]      G_FE  FIFO溢出清零
 bit[1]      保留
 bit[0]      W_FE  FIFO溢出清零
   UNION结构:  WBBP_DBG_FLOW_CLR_UNION */
#define WBBP_DBG_FLOW_CLR_ADDR                        (SOC_BBP_WCDMA_BASE_ADDR + 0x9905C)

/* 寄存器说明：
   详      述：DDR空间上报计数器，BBP每上报2K byte信息，此计数器递增循环，
   UNION结构 ：无 */
#define WBBP_DDR_BIT_CNT_ADDR                         (SOC_BBP_WCDMA_BASE_ADDR + 0x99060)

/* 寄存器说明：
   详      述：BBP debug读取数据
   UNION结构 ：无 */
#define WBBP_BBP_DBG_RDATA_ADDR                       (SOC_BBP_WCDMA_BASE_ADDR + 0x9906C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第五段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报
   UNION结构:  WBBP_MASK_ADDR4_START_UNION */
#define WBBP_MASK_ADDR4_START_ADDR                    (SOC_BBP_WCDMA_BASE_ADDR + 0x99070)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第五段屏蔽地址结束位置
   UNION结构:  WBBP_MASK_ADDR4_END_UNION */
#define WBBP_MASK_ADDR4_END_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR + 0x99074)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第六段屏蔽地址，单个地址被屏蔽
   UNION结构:  WBBP_MASK_ADDR5_UNION */
#define WBBP_MASK_ADDR5_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x99078)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   第七段屏蔽地址，单个地址被屏蔽
   UNION结构:  WBBP_MASK_ADDR6_UNION */
#define WBBP_MASK_ADDR6_ADDR                          (SOC_BBP_WCDMA_BASE_ADDR + 0x9907C)





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
                     (1/10) register_define_wt_dlfe
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_5S_INC_TH_UNION
 结构说明  : AAGC_RSSI_5S_INC_TH 寄存器结构定义。地址偏移量:0x200，初值:0xDCCDBEA9，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_5s_inc_th_reg;
    struct
    {
        unsigned long  s1_2s2_5s_th : 8;  /* bit[0-7]  : 五档AAGC状态跳转S1->S2的RSSI门限，单位dBm，配置二进制补码值。
                                                         说明：按照S1->S2->S3->S4->S5的顺序，天线口的RSSI递增，AAGC的增益递减。
                                                         C模不配置。 */
        unsigned long  s2_2s3_5s_th : 8;  /* bit[8-15] : 五档AAGC状态跳转S2->S3的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s3_2s4_5s_th : 8;  /* bit[16-23]: 五档AAGC状态跳转S3->S4的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s4_2s5_5s_th : 8;  /* bit[24-31]: 五档AAGC状态跳转S4->S5的RSSI门限。
                                                         C模不配置。 */
    } reg;
} WBBP_AAGC_RSSI_5S_INC_TH_UNION;
#define WBBP_AAGC_RSSI_5S_INC_TH_s1_2s2_5s_th_START  (0)
#define WBBP_AAGC_RSSI_5S_INC_TH_s1_2s2_5s_th_END    (7)
#define WBBP_AAGC_RSSI_5S_INC_TH_s2_2s3_5s_th_START  (8)
#define WBBP_AAGC_RSSI_5S_INC_TH_s2_2s3_5s_th_END    (15)
#define WBBP_AAGC_RSSI_5S_INC_TH_s3_2s4_5s_th_START  (16)
#define WBBP_AAGC_RSSI_5S_INC_TH_s3_2s4_5s_th_END    (23)
#define WBBP_AAGC_RSSI_5S_INC_TH_s4_2s5_5s_th_START  (24)
#define WBBP_AAGC_RSSI_5S_INC_TH_s4_2s5_5s_th_END    (31)


/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_5S_DEC_TH_UNION
 结构说明  : AAGC_RSSI_5S_DEC_TH 寄存器结构定义。地址偏移量:0x204，初值:0xD9C7BBA6，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_5s_dec_th_reg;
    struct
    {
        unsigned long  s2_2s1_5s_th : 8;  /* bit[0-7]  : 五档AAGC状态跳转S2->S1的RSSI门限，单位dBm，配置二进制补码值。
                                                         说明：按照S5->S4->S3->S2->S1的顺序，天线口的RSSI递减，AAGC的增益递增。
                                                         C模不配置。 */
        unsigned long  s3_2s2_5s_th : 8;  /* bit[8-15] : 五档AAGC状态跳转S3->S2的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s4_2s3_5s_th : 8;  /* bit[16-23]: 五档AAGC状态跳转S4->S3的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s5_2s4_5s_th : 8;  /* bit[24-31]: 五档AAGC状态跳转S5->S4的RSSI门限。
                                                         C模不配置。 */
    } reg;
} WBBP_AAGC_RSSI_5S_DEC_TH_UNION;
#define WBBP_AAGC_RSSI_5S_DEC_TH_s2_2s1_5s_th_START  (0)
#define WBBP_AAGC_RSSI_5S_DEC_TH_s2_2s1_5s_th_END    (7)
#define WBBP_AAGC_RSSI_5S_DEC_TH_s3_2s2_5s_th_START  (8)
#define WBBP_AAGC_RSSI_5S_DEC_TH_s3_2s2_5s_th_END    (15)
#define WBBP_AAGC_RSSI_5S_DEC_TH_s4_2s3_5s_th_START  (16)
#define WBBP_AAGC_RSSI_5S_DEC_TH_s4_2s3_5s_th_END    (23)
#define WBBP_AAGC_RSSI_5S_DEC_TH_s5_2s4_5s_th_START  (24)
#define WBBP_AAGC_RSSI_5S_DEC_TH_s5_2s4_5s_th_END    (31)


/*****************************************************************************
 结构名    : WBBP_S1_5S_RF_CTRL_AT1_UNION
 结构说明  : S1_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s1_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s1_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S1（RF RSSI为-102~-90dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S1_5S_RF_CTRL_AT1_UNION;
#define WBBP_S1_5S_RF_CTRL_AT1_s1_5s_rf_ctrl_at1_START  (0)
#define WBBP_S1_5S_RF_CTRL_AT1_s1_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S2_5S_RF_CTRL_AT1_UNION
 结构说明  : S2_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s2_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s2_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S2（RF RSSI为-87~-69dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S2_5S_RF_CTRL_AT1_UNION;
#define WBBP_S2_5S_RF_CTRL_AT1_s2_5s_rf_ctrl_at1_START  (0)
#define WBBP_S2_5S_RF_CTRL_AT1_s2_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S3_5S_RF_CTRL_AT1_UNION
 结构说明  : S3_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s3_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s3_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S3（RF RSSI为-66~-54dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S3_5S_RF_CTRL_AT1_UNION;
#define WBBP_S3_5S_RF_CTRL_AT1_s3_5s_rf_ctrl_at1_START  (0)
#define WBBP_S3_5S_RF_CTRL_AT1_s3_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S4_5S_RF_CTRL_AT1_UNION
 结构说明  : S4_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s4_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s4_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S4（RF RSSI为-51~-39dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S4_5S_RF_CTRL_AT1_UNION;
#define WBBP_S4_5S_RF_CTRL_AT1_s4_5s_rf_ctrl_at1_START  (0)
#define WBBP_S4_5S_RF_CTRL_AT1_s4_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S5_5S_RF_CTRL_AT1_UNION
 结构说明  : S5_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s5_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s5_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S5（RF RSSI为-36~-21dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S5_5S_RF_CTRL_AT1_UNION;
#define WBBP_S5_5S_RF_CTRL_AT1_s5_5s_rf_ctrl_at1_START  (0)
#define WBBP_S5_5S_RF_CTRL_AT1_s5_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S1_5S_RF_CTRL_AT2_UNION
 结构说明  : S1_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s1_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s1_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S1（RF RSSI为-102~-90dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S1_5S_RF_CTRL_AT2_UNION;
#define WBBP_S1_5S_RF_CTRL_AT2_s1_5s_rf_ctrl_at2_START  (0)
#define WBBP_S1_5S_RF_CTRL_AT2_s1_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S2_5S_RF_CTRL_AT2_UNION
 结构说明  : S2_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s2_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s2_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S2（RF RSSI为-87~-69dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S2_5S_RF_CTRL_AT2_UNION;
#define WBBP_S2_5S_RF_CTRL_AT2_s2_5s_rf_ctrl_at2_START  (0)
#define WBBP_S2_5S_RF_CTRL_AT2_s2_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S3_5S_RF_CTRL_AT2_UNION
 结构说明  : S3_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s3_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s3_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S3（RF RSSI为-66~-54dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S3_5S_RF_CTRL_AT2_UNION;
#define WBBP_S3_5S_RF_CTRL_AT2_s3_5s_rf_ctrl_at2_START  (0)
#define WBBP_S3_5S_RF_CTRL_AT2_s3_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S4_5S_RF_CTRL_AT2_UNION
 结构说明  : S4_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s4_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s4_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S4（RF RSSI为-51~-39dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S4_5S_RF_CTRL_AT2_UNION;
#define WBBP_S4_5S_RF_CTRL_AT2_s4_5s_rf_ctrl_at2_START  (0)
#define WBBP_S4_5S_RF_CTRL_AT2_s4_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S5_5S_RF_CTRL_AT2_UNION
 结构说明  : S5_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s5_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s5_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S5（RF RSSI为-36~-21dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S5_5S_RF_CTRL_AT2_UNION;
#define WBBP_S5_5S_RF_CTRL_AT2_s5_5s_rf_ctrl_at2_START  (0)
#define WBBP_S5_5S_RF_CTRL_AT2_s5_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_OFFSET_AT1_UNION
 结构说明  : DC_OFFSET_AT1 寄存器结构定义。地址偏移量:0x234，初值:0x20000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_offset_at1_reg;
    struct
    {
        unsigned long  dsp_dc_offset_i_at1   : 12; /* bit[0-11] : 天线1接收I路直流偏置值。 */
        unsigned long  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned long  dsp_dc_offset_q_at1   : 12; /* bit[16-27]: 天线1接收Q路直流偏置值。 */
        unsigned long  dsp_dc_offset_sel_at1 : 1;  /* bit[28]   : DSP配置的天线1直流偏置消除模块反馈值选择信号。1，选择dc_offset；0，选择计算获得的反馈值。 */
        unsigned long  dsp_dcr_en_at1        : 1;  /* bit[29]   : DSP控制天线1 DCR启停使能。1，DSP打开DCR；0，DSP关闭DCR，IQ数据直通。 */
        unsigned long  reserved_1            : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_DC_OFFSET_AT1_UNION;
#define WBBP_DC_OFFSET_AT1_dsp_dc_offset_i_at1_START    (0)
#define WBBP_DC_OFFSET_AT1_dsp_dc_offset_i_at1_END      (11)
#define WBBP_DC_OFFSET_AT1_dsp_dc_offset_q_at1_START    (16)
#define WBBP_DC_OFFSET_AT1_dsp_dc_offset_q_at1_END      (27)
#define WBBP_DC_OFFSET_AT1_dsp_dc_offset_sel_at1_START  (28)
#define WBBP_DC_OFFSET_AT1_dsp_dc_offset_sel_at1_END    (28)
#define WBBP_DC_OFFSET_AT1_dsp_dcr_en_at1_START         (29)
#define WBBP_DC_OFFSET_AT1_dsp_dcr_en_at1_END           (29)


/*****************************************************************************
 结构名    : WBBP_DC_OFFSET_AT2_UNION
 结构说明  : DC_OFFSET_AT2 寄存器结构定义。地址偏移量:0x238，初值:0x20000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_offset_at2_reg;
    struct
    {
        unsigned long  dsp_dc_offset_i_at2   : 12; /* bit[0-11] : 天线2接收I路直流偏置值。 */
        unsigned long  reserved_0            : 4;  /* bit[12-15]: 保留 */
        unsigned long  dsp_dc_offset_q_at2   : 12; /* bit[16-27]: 天线2接收Q路直流偏置值。 */
        unsigned long  dsp_dc_offset_sel_at2 : 1;  /* bit[28]   : DSP配置的天线2直流偏置消除模块反馈值选择信号。1，选择dc_offset；0，选择计算获得的反馈值。 */
        unsigned long  dsp_dcr_en_at2        : 1;  /* bit[29]   : DSP控制天线2 DCR启停使能。1，DSP打开DCR；0，DSP关闭DCR，IQ数据直通。 */
        unsigned long  reserved_1            : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_DC_OFFSET_AT2_UNION;
#define WBBP_DC_OFFSET_AT2_dsp_dc_offset_i_at2_START    (0)
#define WBBP_DC_OFFSET_AT2_dsp_dc_offset_i_at2_END      (11)
#define WBBP_DC_OFFSET_AT2_dsp_dc_offset_q_at2_START    (16)
#define WBBP_DC_OFFSET_AT2_dsp_dc_offset_q_at2_END      (27)
#define WBBP_DC_OFFSET_AT2_dsp_dc_offset_sel_at2_START  (28)
#define WBBP_DC_OFFSET_AT2_dsp_dc_offset_sel_at2_END    (28)
#define WBBP_DC_OFFSET_AT2_dsp_dcr_en_at2_START         (29)
#define WBBP_DC_OFFSET_AT2_dsp_dcr_en_at2_END           (29)


/*****************************************************************************
 结构名    : WBBP_DC_OFFSET_SHIFT_AT1_UNION
 结构说明  : DC_OFFSET_SHIFT_AT1 寄存器结构定义。地址偏移量:0x23C，初值:0x01030A11，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_offset_shift_at1_reg;
    struct
    {
        unsigned long  dsp_dcr_acc_sel_1st_intra_at1 : 2;  /* bit[0-1]  : DSP配置天线1本频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。 */
        unsigned long  dsp_dcr_acc_sel_2nd_intra_at1 : 2;  /* bit[2-3]  : DSP配置天线1本频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。 */
        unsigned long  dsp_dcr_dly_sel_at1           : 2;  /* bit[4-5]  : 增益调整后，不进行DCR计算的时间选择。
                                                                          W下：0，表示16chip；1，表示24chip；2，表示32chip；3，表示8chip。
                                                                          1X下：0，表示0chip；1，表示8chip。
                                                                          1X默认为8chip；EVDO默认24chip。 */
        unsigned long  reserved_0                    : 2;  /* bit[6-7]  : 保留 */
        unsigned long  dsp_dcr_period_1st_at1        : 4;  /* bit[8-11] : 增益调整后第一阶段的时间，单位256chip。
                                                                          1X下为1536chip，故需配置0x6；EVDO下为2048chip，故需配置为0x8。 */
        unsigned long  reserved_1                    : 4;  /* bit[12-15]: 保留 */
        unsigned long  dsp_dcr_alg_sel_at1           : 2;  /* bit[16-17]: DCR算法选择。
                                                                          00，表示使用与V2相同的算法；
                                                                          01，表示使用V3R1算法；
                                                                          11，表示使用V3R2算法。
                                                                          1X仅支持V3R2算法；EVDO默认配置为V3R2算法，支持配置为V3R1算法。 */
        unsigned long  reserved_2                    : 6;  /* bit[18-23]: 保留 */
        unsigned long  dsp_dcr_acc_sel_1st_inter_at1 : 2;  /* bit[24-25]: DSP配置天线1异频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。 */
        unsigned long  dsp_dcr_acc_sel_2nd_inter_at1 : 2;  /* bit[26-27]: DSP配置天线1异频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。 */
        unsigned long  dsp_dcr_inherit_at1           : 1;  /* bit[28]   : 0，档位调整时，DC从0开始重新收敛；1，档位调整时，DC继承先前计算值。 */
        unsigned long  reserved_3                    : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_DC_OFFSET_SHIFT_AT1_UNION;
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_1st_intra_at1_START  (0)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_1st_intra_at1_END    (1)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_2nd_intra_at1_START  (2)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_2nd_intra_at1_END    (3)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_dly_sel_at1_START            (4)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_dly_sel_at1_END              (5)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_period_1st_at1_START         (8)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_period_1st_at1_END           (11)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_alg_sel_at1_START            (16)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_alg_sel_at1_END              (17)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_1st_inter_at1_START  (24)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_1st_inter_at1_END    (25)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_2nd_inter_at1_START  (26)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_acc_sel_2nd_inter_at1_END    (27)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_inherit_at1_START            (28)
#define WBBP_DC_OFFSET_SHIFT_AT1_dsp_dcr_inherit_at1_END              (28)


/*****************************************************************************
 结构名    : WBBP_DC_OFFSET_SHIFT_AT2_UNION
 结构说明  : DC_OFFSET_SHIFT_AT2 寄存器结构定义。地址偏移量:0x240，初值:0x01030A11，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_offset_shift_at2_reg;
    struct
    {
        unsigned long  dsp_dcr_acc_sel_1st_intra_at2 : 2;  /* bit[0-1]  : DSP配置天线2本频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。 */
        unsigned long  dsp_dcr_acc_sel_2nd_intra_at2 : 2;  /* bit[2-3]  : DSP配置天线2本频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。 */
        unsigned long  dsp_dcr_dly_sel_at2           : 2;  /* bit[4-5]  : 增益调整后，不进行DCR计算的时间选择。
                                                                          W下：0，表示16chip；1，表示24chip；2，表示32chip；3，表示8chip。
                                                                          1X下：0，表示0chip；1，表示8chip。
                                                                          1X默认为8chip；EVDO默认24chip。 */
        unsigned long  reserved_0                    : 2;  /* bit[6-7]  : 保留 */
        unsigned long  dsp_dcr_period_1st_at2        : 4;  /* bit[8-11] : 增益调整后第一阶段的时间，单位256chip。
                                                                          1X下为1536chip，故需配置0x6；EVDO下为2048chip，故需配置为0x8。 */
        unsigned long  reserved_1                    : 4;  /* bit[12-15]: 保留 */
        unsigned long  dsp_dcr_alg_sel_at2           : 2;  /* bit[16-17]: DCR算法选择。
                                                                          00，表示使用与V2相同的算法；
                                                                          01，表示使用V3R1算法；
                                                                          11，表示使用V3R2算法。
                                                                          1X仅支持V3R2算法；EVDO默认配置为V3R2算法，支持配置为V3R1算法。 */
        unsigned long  reserved_2                    : 6;  /* bit[18-23]: 保留 */
        unsigned long  dsp_dcr_acc_sel_1st_inter_at2 : 2;  /* bit[24-25]: DSP配置天线2异频去直流模块直流偏置值的计算，用于配置增益调整后第一阶段累加值的右移位数。0，右移12位；1，右移11位；2，右移10位；3，右移8位。 */
        unsigned long  dsp_dcr_acc_sel_2nd_inter_at2 : 2;  /* bit[26-27]: DSP配置天线2异频去直流模块直流偏置值的计算，用于配置增益调整后第二阶段累加值的右移位数。0，右移16位；1，右移14位。 */
        unsigned long  dsp_dcr_inherit_at2           : 1;  /* bit[28]   : 0，档位调整时，DC从0开始重新收敛；1，档位调整时，DC继承先前计算值。 */
        unsigned long  reserved_3                    : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_DC_OFFSET_SHIFT_AT2_UNION;
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_1st_intra_at2_START  (0)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_1st_intra_at2_END    (1)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_2nd_intra_at2_START  (2)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_2nd_intra_at2_END    (3)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_dly_sel_at2_START            (4)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_dly_sel_at2_END              (5)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_period_1st_at2_START         (8)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_period_1st_at2_END           (11)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_alg_sel_at2_START            (16)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_alg_sel_at2_END              (17)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_1st_inter_at2_START  (24)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_1st_inter_at2_END    (25)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_2nd_inter_at2_START  (26)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_acc_sel_2nd_inter_at2_END    (27)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_inherit_at2_START            (28)
#define WBBP_DC_OFFSET_SHIFT_AT2_dsp_dcr_inherit_at2_END              (28)


/*****************************************************************************
 结构名    : WBBP_WAGC_FILTER_CFG_UNION
 结构说明  : WAGC_FILTER_CFG 寄存器结构定义。地址偏移量:0x264，初值:0x00000011，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_filter_cfg_reg;
    struct
    {
        unsigned long  dagc_filter_coe : 3;  /* bit[0-2] : DAGC统计能量滤波系数。0，表示1；1，表示1/2；2，表示1/4；3，表示1/8；4，表示1/16；5，表示1/32；6，表示1/64。
                                                           C模不配置。 */
        unsigned long  reserved_0      : 1;  /* bit[3]   : 保留 */
        unsigned long  aagc_filter_coe : 3;  /* bit[4-6] : AAGC统计能量滤波系数。0，表示1；1，表示1/2；2，表示1/4；3，表示1/8；4，表示1/16；5，表示1/32；6，表示1/64。
                                                           C模不配置。 */
        unsigned long  reserved_1      : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_WAGC_FILTER_CFG_UNION;
#define WBBP_WAGC_FILTER_CFG_dagc_filter_coe_START  (0)
#define WBBP_WAGC_FILTER_CFG_dagc_filter_coe_END    (2)
#define WBBP_WAGC_FILTER_CFG_aagc_filter_coe_START  (4)
#define WBBP_WAGC_FILTER_CFG_aagc_filter_coe_END    (6)


/*****************************************************************************
 结构名    : WBBP_WAGC_SAT_NUM_UNION
 结构说明  : WAGC_SAT_NUM 寄存器结构定义。地址偏移量:0x268，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_sat_num_reg;
    struct
    {
        unsigned long  dagc_sat_num_1f_at1 : 16; /* bit[0-15] : 天线1一帧内DAGC IQ数据饱和次数。
                                                                1X和EVDO为150个256chip的时间。 */
        unsigned long  dagc_sat_num_1f_at2 : 16; /* bit[16-31]: 天线2一帧内DAGC IQ数据饱和次数。
                                                                1X和EVDO为150个256chip的时间。 */
    } reg;
} WBBP_WAGC_SAT_NUM_UNION;
#define WBBP_WAGC_SAT_NUM_dagc_sat_num_1f_at1_START  (0)
#define WBBP_WAGC_SAT_NUM_dagc_sat_num_1f_at1_END    (15)
#define WBBP_WAGC_SAT_NUM_dagc_sat_num_1f_at2_START  (16)
#define WBBP_WAGC_SAT_NUM_dagc_sat_num_1f_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WAGC_MODE_UNION
 结构说明  : WAGC_MODE 寄存器结构定义。地址偏移量:0x26C，初值:0x00000055，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_mode_reg;
    struct
    {
        unsigned long  wagc_mode_aagc_intra : 2;  /* bit[0-1]  : 本频AAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
                                                                 1X和EVDO是固定值，无需配置。 */
        unsigned long  wagc_mode_dagc_intra : 2;  /* bit[2-3]  : 本频DAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
                                                                 1X和EVDO是固定值，无需配置。 */
        unsigned long  wagc_mode_aagc_inter : 2;  /* bit[4-5]  : 异频AAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
                                                                 1X和EVDO是固定值，无需配置。 */
        unsigned long  wagc_mode_dagc_inter : 2;  /* bit[6-7]  : 异频DAGC增益调整时间选择。0，表示一个符号调整一次增益；1，表示一个时隙调整一次增益；2，表示2个符号调整一次增益；3，表示4个符号调整一次增益。
                                                                 1X和EVDO是固定值，无需配置。 */
        unsigned long  reserved_0           : 4;  /* bit[8-11] : 保留 */
        unsigned long  wagc_adjust_mode     : 2;  /* bit[12-13]: W模AGC增益调整射频反馈预留时间选择。0，预留32chip；1，预留48chip；2，预留64chip。
                                                                 1X和EVDO是固定值，无需配置。 */
        unsigned long  reserved_1           : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_WAGC_MODE_UNION;
#define WBBP_WAGC_MODE_wagc_mode_aagc_intra_START  (0)
#define WBBP_WAGC_MODE_wagc_mode_aagc_intra_END    (1)
#define WBBP_WAGC_MODE_wagc_mode_dagc_intra_START  (2)
#define WBBP_WAGC_MODE_wagc_mode_dagc_intra_END    (3)
#define WBBP_WAGC_MODE_wagc_mode_aagc_inter_START  (4)
#define WBBP_WAGC_MODE_wagc_mode_aagc_inter_END    (5)
#define WBBP_WAGC_MODE_wagc_mode_dagc_inter_START  (6)
#define WBBP_WAGC_MODE_wagc_mode_dagc_inter_END    (7)
#define WBBP_WAGC_MODE_wagc_adjust_mode_START      (12)
#define WBBP_WAGC_MODE_wagc_adjust_mode_END        (13)


/*****************************************************************************
 结构名    : WBBP_DAGC_4BIT_FILTER_CFG_UNION
 结构说明  : DAGC_4BIT_FILTER_CFG 寄存器结构定义。地址偏移量:0x270，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dagc_4bit_filter_cfg_reg;
    struct
    {
        unsigned long  dagc_4bit_filter_coe : 3;  /* bit[0-2] : 纠偏后4bitDAGC统计能量滤波系数。0，表示1，不滤波；1，表示1/2；2，表示1/4；3，表示1/8；4，表示1/16；5，表示1/32。
                                                                C模不配置。 */
        unsigned long  reserved             : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_DAGC_4BIT_FILTER_CFG_UNION;
#define WBBP_DAGC_4BIT_FILTER_CFG_dagc_4bit_filter_coe_START  (0)
#define WBBP_DAGC_4BIT_FILTER_CFG_dagc_4bit_filter_coe_END    (2)


/*****************************************************************************
 结构名    : WBBP_WAGC_DCR_RPT_AT1_UNION
 结构说明  : WAGC_DCR_RPT_AT1 寄存器结构定义。地址偏移量:0x274，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_dcr_rpt_at1_reg;
    struct
    {
        unsigned long  dc_offset_i_cpu_at1 : 12; /* bit[0-11] : 天线1当前I路输入直流结果值上报，测试用。 */
        unsigned long  reserved_0          : 4;  /* bit[12-15]: 保留 */
        unsigned long  dc_offset_q_cpu_at1 : 12; /* bit[16-27]: 天线1当前Q路输入直流结果值上报，测试用。 */
        unsigned long  dcr_1st_sel_at1     : 1;  /* bit[28]   : 新DCR算法天线1第一阶段指示。
                                                                1，第一阶段；0，第二阶段。 */
        unsigned long  reserved_1          : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_WAGC_DCR_RPT_AT1_UNION;
#define WBBP_WAGC_DCR_RPT_AT1_dc_offset_i_cpu_at1_START  (0)
#define WBBP_WAGC_DCR_RPT_AT1_dc_offset_i_cpu_at1_END    (11)
#define WBBP_WAGC_DCR_RPT_AT1_dc_offset_q_cpu_at1_START  (16)
#define WBBP_WAGC_DCR_RPT_AT1_dc_offset_q_cpu_at1_END    (27)
#define WBBP_WAGC_DCR_RPT_AT1_dcr_1st_sel_at1_START      (28)
#define WBBP_WAGC_DCR_RPT_AT1_dcr_1st_sel_at1_END        (28)


/*****************************************************************************
 结构名    : WBBP_WAGC_DCR_RPT_AT2_UNION
 结构说明  : WAGC_DCR_RPT_AT2 寄存器结构定义。地址偏移量:0x278，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_dcr_rpt_at2_reg;
    struct
    {
        unsigned long  dc_offset_i_cpu_at2 : 12; /* bit[0-11] : 天线2当前I路输入直流结果值上报，测试用。 */
        unsigned long  reserved_0          : 4;  /* bit[12-15]: 保留 */
        unsigned long  dc_offset_q_cpu_at2 : 12; /* bit[16-27]: 天线2当前Q路输入直流结果值上报，测试用。 */
        unsigned long  dcr_1st_sel_at2     : 1;  /* bit[28]   : 新DCR算法天线2第一阶段指示。
                                                                1，第一阶段；0，第二阶段。 */
        unsigned long  reserved_1          : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_WAGC_DCR_RPT_AT2_UNION;
#define WBBP_WAGC_DCR_RPT_AT2_dc_offset_i_cpu_at2_START  (0)
#define WBBP_WAGC_DCR_RPT_AT2_dc_offset_i_cpu_at2_END    (11)
#define WBBP_WAGC_DCR_RPT_AT2_dc_offset_q_cpu_at2_START  (16)
#define WBBP_WAGC_DCR_RPT_AT2_dc_offset_q_cpu_at2_END    (27)
#define WBBP_WAGC_DCR_RPT_AT2_dcr_1st_sel_at2_START      (28)
#define WBBP_WAGC_DCR_RPT_AT2_dcr_1st_sel_at2_END        (28)


/*****************************************************************************
 结构名    : WBBP_IQ_AK_PK_SEL_ANT1_UNION
 结构说明  : IQ_AK_PK_SEL_ANT1 寄存器结构定义。地址偏移量:0x27C，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_ak_pk_sel_ant1_reg;
    struct
    {
        unsigned long  iq_mis_sel_ant1   : 1;  /* bit[0]   : 天线1 IQ Mismatch纠正系数选择。0，表示使用IQ Mismatch自己产生；1，表示使用DSP配置值。 */
        unsigned long  reserved_0        : 7;  /* bit[1-7] : 保留 */
        unsigned long  dsp_iq_mis_en_at1 : 1;  /* bit[8]   : 天线1 IQ Mismatch使能，高电平有效。 */
        unsigned long  reserved_1        : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_IQ_AK_PK_SEL_ANT1_UNION;
#define WBBP_IQ_AK_PK_SEL_ANT1_iq_mis_sel_ant1_START    (0)
#define WBBP_IQ_AK_PK_SEL_ANT1_iq_mis_sel_ant1_END      (0)
#define WBBP_IQ_AK_PK_SEL_ANT1_dsp_iq_mis_en_at1_START  (8)
#define WBBP_IQ_AK_PK_SEL_ANT1_dsp_iq_mis_en_at1_END    (8)


/*****************************************************************************
 结构名    : WBBP_IQ_AK_PK_ANT1_UNION
 结构说明  : IQ_AK_PK_ANT1 寄存器结构定义。地址偏移量:0x280，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_ak_pk_ant1_reg;
    struct
    {
        unsigned long  dsp_iq_ak_ant1 : 10; /* bit[0-9]  : DSP配置的天线1 IQ Mismatch纠正系数Ak。 */
        unsigned long  reserved_0     : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_iq_pk_ant1 : 11; /* bit[16-26]: DSP配置的天线1 IQ Mismatch纠正系数Pk。 */
        unsigned long  reserved_1     : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_IQ_AK_PK_ANT1_UNION;
#define WBBP_IQ_AK_PK_ANT1_dsp_iq_ak_ant1_START  (0)
#define WBBP_IQ_AK_PK_ANT1_dsp_iq_ak_ant1_END    (9)
#define WBBP_IQ_AK_PK_ANT1_dsp_iq_pk_ant1_START  (16)
#define WBBP_IQ_AK_PK_ANT1_dsp_iq_pk_ant1_END    (26)


/*****************************************************************************
 结构名    : WBBP_IQ_AK_PK_SEL_ANT2_UNION
 结构说明  : IQ_AK_PK_SEL_ANT2 寄存器结构定义。地址偏移量:0x294，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_ak_pk_sel_ant2_reg;
    struct
    {
        unsigned long  iq_mis_sel_ant2   : 1;  /* bit[0]   : 天线2 IQ Mismatch纠正系数选择。0，表示使用IQ Mismatch自己产生；1，表示使用DSP配置值。 */
        unsigned long  reserved_0        : 7;  /* bit[1-7] : 保留 */
        unsigned long  dsp_iq_mis_en_at2 : 1;  /* bit[8]   : 天线2 IQ Mismatch使能，高电平有效。 */
        unsigned long  reserved_1        : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_IQ_AK_PK_SEL_ANT2_UNION;
#define WBBP_IQ_AK_PK_SEL_ANT2_iq_mis_sel_ant2_START    (0)
#define WBBP_IQ_AK_PK_SEL_ANT2_iq_mis_sel_ant2_END      (0)
#define WBBP_IQ_AK_PK_SEL_ANT2_dsp_iq_mis_en_at2_START  (8)
#define WBBP_IQ_AK_PK_SEL_ANT2_dsp_iq_mis_en_at2_END    (8)


/*****************************************************************************
 结构名    : WBBP_IQ_AK_PK_ANT2_UNION
 结构说明  : IQ_AK_PK_ANT2 寄存器结构定义。地址偏移量:0x298，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_ak_pk_ant2_reg;
    struct
    {
        unsigned long  dsp_iq_ak_ant2 : 10; /* bit[0-9]  : DSP配置的天线2 IQ Mismatch纠正系数Ak。 */
        unsigned long  reserved_0     : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_iq_pk_ant2 : 11; /* bit[16-26]: DSP配置的天线2 IQ Mismatch纠正系数Pk。 */
        unsigned long  reserved_1     : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_IQ_AK_PK_ANT2_UNION;
#define WBBP_IQ_AK_PK_ANT2_dsp_iq_ak_ant2_START  (0)
#define WBBP_IQ_AK_PK_ANT2_dsp_iq_ak_ant2_END    (9)
#define WBBP_IQ_AK_PK_ANT2_dsp_iq_pk_ant2_START  (16)
#define WBBP_IQ_AK_PK_ANT2_dsp_iq_pk_ant2_END    (26)


/*****************************************************************************
 结构名    : WBBP_AGC_RPT_AT1_UNION
 结构说明  : AGC_RPT_AT1 寄存器结构定义。地址偏移量:0x29C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      agc_rpt_at1_reg;
    struct
    {
        unsigned long  agc_state_rpt_at1 : 30; /* bit[0-29] : 天线1档位上报。连续存储10个DRSSI统计周期的档位值，每个档位占3比特，最新的档位放在低3比特。 */
        unsigned long  reserved          : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_AGC_RPT_AT1_UNION;
#define WBBP_AGC_RPT_AT1_agc_state_rpt_at1_START  (0)
#define WBBP_AGC_RPT_AT1_agc_state_rpt_at1_END    (29)


/*****************************************************************************
 结构名    : WBBP_AGC_RPT_AT2_UNION
 结构说明  : AGC_RPT_AT2 寄存器结构定义。地址偏移量:0x2A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      agc_rpt_at2_reg;
    struct
    {
        unsigned long  agc_state_rpt_at2 : 30; /* bit[0-29] : 天线2档位上报。连续存储10个DRSSI统计周期的档位值，每个档位占3比特，最新的档位放在低3比特。 */
        unsigned long  reserved          : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_AGC_RPT_AT2_UNION;
#define WBBP_AGC_RPT_AT2_agc_state_rpt_at2_START  (0)
#define WBBP_AGC_RPT_AT2_agc_state_rpt_at2_END    (29)


/*****************************************************************************
 结构名    : WBBP_IQ_MIS_ADJUST_MODE_UNION
 结构说明  : IQ_MIS_ADJUST_MODE 寄存器结构定义。地址偏移量:0x2AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_mis_adjust_mode_reg;
    struct
    {
        unsigned long  iq_mis_adjust_mode : 2;  /* bit[0-1] : IQ Mismatch模块预留给RF增益的调整时间。
                                                              W下：0，预留24chip，对应AAGC的32chip；1，预留40chip，对应AAGC的48chip；2，预留56chip，对应AAGC的64chip。
                                                              1X下：0，预留8chip；1，预留16chip；2，预留24chip。
                                                              EVDO下：固定，无需配置。 */
        unsigned long  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_IQ_MIS_ADJUST_MODE_UNION;
#define WBBP_IQ_MIS_ADJUST_MODE_iq_mis_adjust_mode_START  (0)
#define WBBP_IQ_MIS_ADJUST_MODE_iq_mis_adjust_mode_END    (1)


/*****************************************************************************
 结构名    : WBBP_IQ_MIS_MODE_UNION
 结构说明  : IQ_MIS_MODE 寄存器结构定义。地址偏移量:0x2B4，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_mis_mode_reg;
    struct
    {
        unsigned long  iq_mis_mode : 3;  /* bit[0-2] : IQ Mismatch计算周期，需要与AAGC的调整周期一致。0，表示一个单位；1，表示W的一个时隙，或者1X的一个PCG；2，表示2个单位；3，表示4个单位。4，表示6个单位。
                                                       1X：默认值为1。
                                                       EVDO：上述选项无效，为一个时隙的固定值，不需要配置。
                                                       注：单位为256chip。 */
        unsigned long  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_IQ_MIS_MODE_UNION;
#define WBBP_IQ_MIS_MODE_iq_mis_mode_START  (0)
#define WBBP_IQ_MIS_MODE_iq_mis_mode_END    (2)


/*****************************************************************************
 结构名    : WBBP_DBG_AGC_DATA_SEL_UNION
 结构说明  : DBG_AGC_DATA_SEL 寄存器结构定义。地址偏移量:0x2DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_agc_data_sel_reg;
    struct
    {
        unsigned long  dbg_data_sel : 5;  /* bit[0-4]  : 基带数据搬运选择，表示采数位置。
                                                         0，ADC输出信号，数据位宽14bit，W和TDS都用；
                                                         1，spmv输输出信号，W和TDS都用；
                                                         2，dcoc输出信号，W和TDS使用；
                                                         3，dgt1输出信号，仅TDS使用；
                                                         4，fir输出信号，仅TDS使用；
                                                         5，rxiq输出信号，W和TDS都用；
                                                         6，dwf的主载波输出信号，W和TDS都用；
                                                         7，主载波fifo输出信号，仅W使用；
                                                         8，主载波sc_filter输出信号，W和TDS都使用；
                                                         9，TDS的rrc输出信号，仅TDS使用；
                                                         10，TDS的dgt2输出信号，仅TDS使用；
                                                         11，W的rrc输出信号，主载波和辅载波分时复用；
                                                         12，W的8bitDAGC输出信号，主载波和辅载波分时复用；
                                                         13，W的4bitDAGC输出信号，主载波和辅载波分时复用；
                                                         14，辅载波dwf输出信号，仅W使用；
                                                         16，辅载波sc_filter输出信号，仅W使用；
                                                         17，幅度为2047的三角波，对应12bits数据；
                                                         18，幅度为127的三角波，对应8bit数据；
                                                         19，频率校正freq_error输出信号，仅W使用；
                                                         20，主载波FIFO输出信号，仅W使用；
                                                         搬运数据格式：
                                                         0：[13:0]为数据；[14]数据符号位；[15]为0表示天线1，为1表示天线2。
                                                         1~20：[11:0]为数据；[12]为0表示主载波，为1表示辅载波，不区分主辅载波的该位为数据符号位；[13]为0表示天线1，为1表示天线2。 */
        unsigned long  reserved_0   : 3;  /* bit[5-7]  : 保留 */
        unsigned long  at1_dbg_en   : 1;  /* bit[8]    : 主天线采数使能，高电平有效。 */
        unsigned long  at2_dbg_en   : 1;  /* bit[9]    : 辅天线采数使，高电平有效。 */
        unsigned long  reserved_1   : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DBG_AGC_DATA_SEL_UNION;
#define WBBP_DBG_AGC_DATA_SEL_dbg_data_sel_START  (0)
#define WBBP_DBG_AGC_DATA_SEL_dbg_data_sel_END    (4)
#define WBBP_DBG_AGC_DATA_SEL_at1_dbg_en_START    (8)
#define WBBP_DBG_AGC_DATA_SEL_at1_dbg_en_END      (8)
#define WBBP_DBG_AGC_DATA_SEL_at2_dbg_en_START    (9)
#define WBBP_DBG_AGC_DATA_SEL_at2_dbg_en_END      (9)


/*****************************************************************************
 结构名    : WBBP_WAGC_SWITCH_UNION
 结构说明  : WAGC_SWITCH 寄存器结构定义。地址偏移量:0x400，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_switch_reg;
    struct
    {
        unsigned long  dlfe_at1_en               : 1;  /* bit[0]    : 天线1前端开关。1，表示打开；0，表示关闭。W、TDS和C共用。 */
        unsigned long  dlfe_at2_en               : 1;  /* bit[1]    : 天线2前端开关。1，表示打开；0，表示关闭。W、TDS和C共用。 */
        unsigned long  dsp_wagc_switch_sync_mode : 2;  /* bit[2-3]  : 0，主辅天线打开按符号同步；1，主辅天线打开按1/4chip同步；2，主辅天线打开按时隙同步。
                                                                      C模不配置。 */
        unsigned long  dsp_dpa_mode_abb_blk      : 1;  /* bit[4]    : 0表示BLOCK检测和ABB BLOCK控制模块跟AGC内部定时器对齐；1表示BLOCK检测和ABB BLOCK控制模块跟DPA时隙头对齐。
                                                                      由于不支持DPA模式，请固定使用默认值，不能改配。
                                                                      C模不配置。 */
        unsigned long  dsp_dpa_mode_rssi         : 1;  /* bit[5]    : 0表示RSSI计算和AGC档位调整跟AGC内部定时器对齐；1表示RSSI计算和AGC档位调整跟DPA时隙头对齐。
                                                                      由于不支持DPA模式，请固定使用默认值，不能改配。
                                                                      C模不配置。 */
        unsigned long  dsp_dpa_mode_iqmis        : 1;  /* bit[6]    : 0表示IQ Mismatch计算跟AGC内部定时器对齐；1表示IQ Mismatch计算跟DPA时隙头对齐。
                                                                      由于不支持DPA模式，请固定使用默认值，不能改配。
                                                                      C模不配置。 */
        unsigned long  reserved_0                : 1;  /* bit[7]    : 保留 */
        unsigned long  dsp_srst_at1              : 1;  /* bit[8]    : 主集软复位。1表示进入复位状态；0表示退出软复位状态。
                                                                      软复位和天线使能配置约束：复位前先关闭本寄存器bit[0]天线使能，然后进行软复位，撤销复位后再打开本寄存器bit[0]天线使能。并且天线使能关闭时间要大于2个符号。 */
        unsigned long  dsp_srst_at2              : 1;  /* bit[9]    : 分集软复位。1表示进入复位状态；0表示退出软复位状态。
                                                                      软复位和天线使能配置约束：复位前先关闭本寄存器bit[1]天线使能，然后进行软复位，撤销复位后再打开本寄存器bit[1]天线使能。并且天线使能关闭时间要大于2个符号。 */
        unsigned long  reserved_1                : 2;  /* bit[10-11]: 保留 */
        unsigned long  dlfe_mode_sel             : 2;  /* bit[12-13]: 模式选择。0表示W；1表示TDS；2表示cdma 1X；3表示cdma EVDO。 */
        unsigned long  reserved_2                : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_WAGC_SWITCH_UNION;
#define WBBP_WAGC_SWITCH_dlfe_at1_en_START                (0)
#define WBBP_WAGC_SWITCH_dlfe_at1_en_END                  (0)
#define WBBP_WAGC_SWITCH_dlfe_at2_en_START                (1)
#define WBBP_WAGC_SWITCH_dlfe_at2_en_END                  (1)
#define WBBP_WAGC_SWITCH_dsp_wagc_switch_sync_mode_START  (2)
#define WBBP_WAGC_SWITCH_dsp_wagc_switch_sync_mode_END    (3)
#define WBBP_WAGC_SWITCH_dsp_dpa_mode_abb_blk_START       (4)
#define WBBP_WAGC_SWITCH_dsp_dpa_mode_abb_blk_END         (4)
#define WBBP_WAGC_SWITCH_dsp_dpa_mode_rssi_START          (5)
#define WBBP_WAGC_SWITCH_dsp_dpa_mode_rssi_END            (5)
#define WBBP_WAGC_SWITCH_dsp_dpa_mode_iqmis_START         (6)
#define WBBP_WAGC_SWITCH_dsp_dpa_mode_iqmis_END           (6)
#define WBBP_WAGC_SWITCH_dsp_srst_at1_START               (8)
#define WBBP_WAGC_SWITCH_dsp_srst_at1_END                 (8)
#define WBBP_WAGC_SWITCH_dsp_srst_at2_START               (9)
#define WBBP_WAGC_SWITCH_dsp_srst_at2_END                 (9)
#define WBBP_WAGC_SWITCH_dlfe_mode_sel_START              (12)
#define WBBP_WAGC_SWITCH_dlfe_mode_sel_END                (13)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_CFG_AT1_UNION
 结构说明  : INIT_AGC_CFG_AT1 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_cfg_at1_reg;
    struct
    {
        unsigned long  dsp_init_drssi_25db_at1   : 9;  /* bit[0-8]  : 刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  dsp_init_rssi_rf_at1      : 11; /* bit[9-19] : 刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  dsp_init_5s_agc_state_at1 : 3;  /* bit[20-22]: 刚刚打开AGC时，BBP使用此值进行自研RF五档增益控制。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  reserved_0                : 1;  /* bit[23]   : 保留 */
        unsigned long  dsp_init_8s_agc_state_at1 : 3;  /* bit[24-26]: 刚刚打开AGC时，BBP使用此值进行自研RF八档增益控制。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  reserved_1                : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_CFG_AT1_UNION;
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_drssi_25db_at1_START    (0)
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_drssi_25db_at1_END      (8)
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_rssi_rf_at1_START       (9)
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_rssi_rf_at1_END         (19)
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_5s_agc_state_at1_START  (20)
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_5s_agc_state_at1_END    (22)
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_8s_agc_state_at1_START  (24)
#define WBBP_INIT_AGC_CFG_AT1_dsp_init_8s_agc_state_at1_END    (26)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_CFG_AT2_UNION
 结构说明  : INIT_AGC_CFG_AT2 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_cfg_at2_reg;
    struct
    {
        unsigned long  dsp_init_drssi_25db_at2   : 9;  /* bit[0-8]  : 刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  dsp_init_rssi_rf_at2      : 11; /* bit[9-19] : 刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  dsp_init_5s_agc_state_at2 : 3;  /* bit[20-22]: 刚刚打开AGC时，BBP使用此值进行自研RF五档增益控制。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  reserved_0                : 1;  /* bit[23]   : 保留 */
        unsigned long  dsp_init_8s_agc_state_at2 : 3;  /* bit[24-26]: 刚刚打开AGC时，BBP使用此值进行自研RF八档增益控制。
                                                                      说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。
                                                                      C模不配置。 */
        unsigned long  reserved_1                : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_CFG_AT2_UNION;
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_drssi_25db_at2_START    (0)
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_drssi_25db_at2_END      (8)
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_rssi_rf_at2_START       (9)
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_rssi_rf_at2_END         (19)
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_5s_agc_state_at2_START  (20)
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_5s_agc_state_at2_END    (22)
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_8s_agc_state_at2_START  (24)
#define WBBP_INIT_AGC_CFG_AT2_dsp_init_8s_agc_state_at2_END    (26)


/*****************************************************************************
 结构名    : WBBP_INTER_AGC_CFG_AT1_UNION
 结构说明  : INTER_AGC_CFG_AT1 寄存器结构定义。地址偏移量:0x40C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      inter_agc_cfg_at1_reg;
    struct
    {
        unsigned long  dsp_inter_drssi_25db_at1   : 9;  /* bit[0-8]  : 刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                       C模不配置。 */
        unsigned long  dsp_inter_rssi_rf_at1      : 11; /* bit[9-19] : 刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
                                                                       C模不配置。 */
        unsigned long  dsp_inter_5s_agc_state_at1 : 3;  /* bit[20-22]: 刚刚进入异频GAP时，BBP使用此值进行自研RF五档增益控制。
                                                                       C模不配置。 */
        unsigned long  reserved_0                 : 1;  /* bit[23]   : 保留 */
        unsigned long  dsp_inter_8s_agc_state_at1 : 3;  /* bit[24-26]: 刚刚进入异频GAP时，BBP使用此值进行自研RF八档增益控制。
                                                                       C模不配置。 */
        unsigned long  reserved_1                 : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_INTER_AGC_CFG_AT1_UNION;
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_drssi_25db_at1_START    (0)
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_drssi_25db_at1_END      (8)
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_rssi_rf_at1_START       (9)
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_rssi_rf_at1_END         (19)
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_5s_agc_state_at1_START  (20)
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_5s_agc_state_at1_END    (22)
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_8s_agc_state_at1_START  (24)
#define WBBP_INTER_AGC_CFG_AT1_dsp_inter_8s_agc_state_at1_END    (26)


/*****************************************************************************
 结构名    : WBBP_INTER_AGC_CFG_AT2_UNION
 结构说明  : INTER_AGC_CFG_AT2 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      inter_agc_cfg_at2_reg;
    struct
    {
        unsigned long  dsp_inter_drssi_25db_at2   : 9;  /* bit[0-8]  : 刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                       C模不配置。 */
        unsigned long  dsp_inter_rssi_rf_at2      : 11; /* bit[9-19] : 刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
                                                                       C模不配置。 */
        unsigned long  dsp_inter_5s_agc_state_at2 : 3;  /* bit[20-22]: 刚刚进入异频GAP时，BBP使用此值进行自研RF五档增益控制。
                                                                       C模不配置。 */
        unsigned long  reserved_0                 : 1;  /* bit[23]   : 保留 */
        unsigned long  dsp_inter_8s_agc_state_at2 : 3;  /* bit[24-26]: 刚刚进入异频GAP时，BBP使用此值进行自研RF八档增益控制。
                                                                       C模不配置。 */
        unsigned long  reserved_1                 : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_INTER_AGC_CFG_AT2_UNION;
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_drssi_25db_at2_START    (0)
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_drssi_25db_at2_END      (8)
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_rssi_rf_at2_START       (9)
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_rssi_rf_at2_END         (19)
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_5s_agc_state_at2_START  (20)
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_5s_agc_state_at2_END    (22)
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_8s_agc_state_at2_START  (24)
#define WBBP_INTER_AGC_CFG_AT2_dsp_inter_8s_agc_state_at2_END    (26)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_RPT_AT1_UNION
 结构说明  : INIT_AGC_RPT_AT1 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_rpt_at1_reg;
    struct
    {
        unsigned long  dsp_rpt_drssi_25db_at1 : 9;  /* bit[0-8]  : BBP上报0.25dB精度的DRSSI值（双载波之和），BBP使用此值查表DAGC ROM。
                                                                   说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_rssi_rf_at1    : 11; /* bit[9-19] : BBP上报天线口RSSI值（双载波之和），0.125dB精度。
                                                                   说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_agc_state_at1  : 3;  /* bit[20-22]: BBP上报用于控制RF增益的状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。
                                                                   说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  reserved               : 9;  /* bit[23-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_RPT_AT1_UNION;
#define WBBP_INIT_AGC_RPT_AT1_dsp_rpt_drssi_25db_at1_START  (0)
#define WBBP_INIT_AGC_RPT_AT1_dsp_rpt_drssi_25db_at1_END    (8)
#define WBBP_INIT_AGC_RPT_AT1_dsp_rpt_rssi_rf_at1_START     (9)
#define WBBP_INIT_AGC_RPT_AT1_dsp_rpt_rssi_rf_at1_END       (19)
#define WBBP_INIT_AGC_RPT_AT1_dsp_rpt_agc_state_at1_START   (20)
#define WBBP_INIT_AGC_RPT_AT1_dsp_rpt_agc_state_at1_END     (22)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_RPT_AT2_UNION
 结构说明  : INIT_AGC_RPT_AT2 寄存器结构定义。地址偏移量:0x418，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_rpt_at2_reg;
    struct
    {
        unsigned long  dsp_rpt_drssi_25db_at2 : 9;  /* bit[0-8]  : BBP上报0.25dB精度的DRSSI值（双载波之和），BBP使用此值查表DAGC ROM。
                                                                   说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_rssi_rf_at2    : 11; /* bit[9-19] : BBP上报天线口RSSI值（双载波之和），0.125dB精度。
                                                                   说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_agc_state_at2  : 3;  /* bit[20-22]: BBP上报用于控制RF增益的状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。
                                                                   说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  reserved               : 9;  /* bit[23-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_RPT_AT2_UNION;
#define WBBP_INIT_AGC_RPT_AT2_dsp_rpt_drssi_25db_at2_START  (0)
#define WBBP_INIT_AGC_RPT_AT2_dsp_rpt_drssi_25db_at2_END    (8)
#define WBBP_INIT_AGC_RPT_AT2_dsp_rpt_rssi_rf_at2_START     (9)
#define WBBP_INIT_AGC_RPT_AT2_dsp_rpt_rssi_rf_at2_END       (19)
#define WBBP_INIT_AGC_RPT_AT2_dsp_rpt_agc_state_at2_START   (20)
#define WBBP_INIT_AGC_RPT_AT2_dsp_rpt_agc_state_at2_END     (22)


/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_8S_INC_TH_UNION
 结构说明  : AAGC_RSSI_8S_INC_TH 寄存器结构定义。地址偏移量:0x41C，初值:0xCEC8C2BC，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_8s_inc_th_reg;
    struct
    {
        unsigned long  s1_2s2_8s_th : 8;  /* bit[0-7]  : 八档AAGC状态跳转S1->S2的RSSI门限，单位dBm，配置二进制补码值。
                                                         说明：按照S1->S2->S3->S4->S5的顺序，天线口的RSSI递增，AAGC的增益递减。
                                                         C模不配置。 */
        unsigned long  s2_2s3_8s_th : 8;  /* bit[8-15] : 八档AAGC状态跳转S2->S3的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s3_2s4_8s_th : 8;  /* bit[16-23]: 八档AAGC状态跳转S3->S4的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s4_2s5_8s_th : 8;  /* bit[24-31]: 八档AAGC状态跳转S4->S5的RSSI门限。
                                                         C模不配置。 */
    } reg;
} WBBP_AAGC_RSSI_8S_INC_TH_UNION;
#define WBBP_AAGC_RSSI_8S_INC_TH_s1_2s2_8s_th_START  (0)
#define WBBP_AAGC_RSSI_8S_INC_TH_s1_2s2_8s_th_END    (7)
#define WBBP_AAGC_RSSI_8S_INC_TH_s2_2s3_8s_th_START  (8)
#define WBBP_AAGC_RSSI_8S_INC_TH_s2_2s3_8s_th_END    (15)
#define WBBP_AAGC_RSSI_8S_INC_TH_s3_2s4_8s_th_START  (16)
#define WBBP_AAGC_RSSI_8S_INC_TH_s3_2s4_8s_th_END    (23)
#define WBBP_AAGC_RSSI_8S_INC_TH_s4_2s5_8s_th_START  (24)
#define WBBP_AAGC_RSSI_8S_INC_TH_s4_2s5_8s_th_END    (31)


/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_8S_DEC_TH_UNION
 结构说明  : AAGC_RSSI_8S_DEC_TH 寄存器结构定义。地址偏移量:0x420，初值:0xBDB7B1AB，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_8s_dec_th_reg;
    struct
    {
        unsigned long  s2_2s1_8s_th : 8;  /* bit[0-7]  : 八档AAGC状态跳转S2->S1的RSSI门限，单位dBm，配置二进制补码值。
                                                         说明：按照S5->S4->S3->S2->S1的顺序，天线口的RSSI递减，AAGC的增益递增。
                                                         C模不配置。 */
        unsigned long  s3_2s2_8s_th : 8;  /* bit[8-15] : 八档AAGC状态跳转S3->S2的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s4_2s3_8s_th : 8;  /* bit[16-23]: 八档AAGC状态跳转S4->S3的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s5_2s4_8s_th : 8;  /* bit[24-31]: 八档AAGC状态跳转S5->S4的RSSI门限。
                                                         C模不配置。 */
    } reg;
} WBBP_AAGC_RSSI_8S_DEC_TH_UNION;
#define WBBP_AAGC_RSSI_8S_DEC_TH_s2_2s1_8s_th_START  (0)
#define WBBP_AAGC_RSSI_8S_DEC_TH_s2_2s1_8s_th_END    (7)
#define WBBP_AAGC_RSSI_8S_DEC_TH_s3_2s2_8s_th_START  (8)
#define WBBP_AAGC_RSSI_8S_DEC_TH_s3_2s2_8s_th_END    (15)
#define WBBP_AAGC_RSSI_8S_DEC_TH_s4_2s3_8s_th_START  (16)
#define WBBP_AAGC_RSSI_8S_DEC_TH_s4_2s3_8s_th_END    (23)
#define WBBP_AAGC_RSSI_8S_DEC_TH_s5_2s4_8s_th_START  (24)
#define WBBP_AAGC_RSSI_8S_DEC_TH_s5_2s4_8s_th_END    (31)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S12_INTRA_AT1_UNION
 结构说明  : RF_8S_GAIN_S12_INTRA_AT1 寄存器结构定义。地址偏移量:0x424，初值:0x01A001D0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s12_intra_at1_reg;
    struct
    {
        unsigned long  s1_8s_rf_gain_intra_at1 : 12; /* bit[0-11] : 八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s2_8s_rf_gain_intra_at1 : 12; /* bit[16-27]: 八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S12_INTRA_AT1_UNION;
#define WBBP_RF_8S_GAIN_S12_INTRA_AT1_s1_8s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_8S_GAIN_S12_INTRA_AT1_s1_8s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_8S_GAIN_S12_INTRA_AT1_s2_8s_rf_gain_intra_at1_START  (16)
#define WBBP_RF_8S_GAIN_S12_INTRA_AT1_s2_8s_rf_gain_intra_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S34_INTRA_AT1_UNION
 结构说明  : RF_8S_GAIN_S34_INTRA_AT1 寄存器结构定义。地址偏移量:0x428，初值:0x01400170，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s34_intra_at1_reg;
    struct
    {
        unsigned long  s3_8s_rf_gain_intra_at1 : 12; /* bit[0-11] : 八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s4_8s_rf_gain_intra_at1 : 12; /* bit[16-27]: 八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S34_INTRA_AT1_UNION;
#define WBBP_RF_8S_GAIN_S34_INTRA_AT1_s3_8s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_8S_GAIN_S34_INTRA_AT1_s3_8s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_8S_GAIN_S34_INTRA_AT1_s4_8s_rf_gain_intra_at1_START  (16)
#define WBBP_RF_8S_GAIN_S34_INTRA_AT1_s4_8s_rf_gain_intra_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_S1_8S_RF_CTRL_AT1_UNION
 结构说明  : S1_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x42C，初值:0x0054F800，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s1_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s1_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S1（RF RSSI为-102~-90dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S1_8S_RF_CTRL_AT1_UNION;
#define WBBP_S1_8S_RF_CTRL_AT1_s1_8s_rf_ctrl_at1_START  (0)
#define WBBP_S1_8S_RF_CTRL_AT1_s1_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S2_8S_RF_CTRL_AT1_UNION
 结构说明  : S2_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x430，初值:0x0054F400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s2_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s2_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S2（RF RSSI为-87~-69dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S2_8S_RF_CTRL_AT1_UNION;
#define WBBP_S2_8S_RF_CTRL_AT1_s2_8s_rf_ctrl_at1_START  (0)
#define WBBP_S2_8S_RF_CTRL_AT1_s2_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S3_8S_RF_CTRL_AT1_UNION
 结构说明  : S3_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x434，初值:0x0054E400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s3_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s3_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S3（RF RSSI为-66~-54dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S3_8S_RF_CTRL_AT1_UNION;
#define WBBP_S3_8S_RF_CTRL_AT1_s3_8s_rf_ctrl_at1_START  (0)
#define WBBP_S3_8S_RF_CTRL_AT1_s3_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S4_8S_RF_CTRL_AT1_UNION
 结构说明  : S4_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x438，初值:0x0054D400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s4_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s4_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S4（RF RSSI为-51~-39dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S4_8S_RF_CTRL_AT1_UNION;
#define WBBP_S4_8S_RF_CTRL_AT1_s4_8s_rf_ctrl_at1_START  (0)
#define WBBP_S4_8S_RF_CTRL_AT1_s4_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S5_8S_RF_CTRL_AT1_UNION
 结构说明  : S5_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x43C，初值:0x0054C400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s5_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s5_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S5（RF RSSI为-36~-21dBm）状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S5_8S_RF_CTRL_AT1_UNION;
#define WBBP_S5_8S_RF_CTRL_AT1_s5_8s_rf_ctrl_at1_START  (0)
#define WBBP_S5_8S_RF_CTRL_AT1_s5_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_CHANNEL_FIX_DIG_GAIN_UNION
 结构说明  : CHANNEL_FIX_DIG_GAIN 寄存器结构定义。地址偏移量:0x440，初值:0x00003535，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      channel_fix_dig_gain_reg;
    struct
    {
        unsigned long  dsp_channel_gain_at1       : 7;  /* bit[0-6]  : 天线1 Gainfix与Gaindig增益之和，即前端通道中比较固定部分的增益，单位dB。
                                                                       AGC在RF_SC/RF_DC可以分时共用。
                                                                       C模不配置。 */
        unsigned long  reserved_0                 : 1;  /* bit[7]    : 保留 */
        unsigned long  dsp_channel_gain_at2       : 7;  /* bit[8-14] : 天线2 Gainfix与Gaindig增益之和，即前端通道中比较固定部分的增益，单位dB。
                                                                       AGC在RF_SC/RF_DC可以分时共用。
                                                                       C模不配置。 */
        unsigned long  reserved_1                 : 5;  /* bit[15-19]: 保留 */
        unsigned long  dsp_ch_switch_rfgain_intra : 1;  /* bit[20]   : rfgain本频通道选择。1表示天线1和天线2交换。
                                                                       C模不配置。 */
        unsigned long  dsp_ch_switch_rfgain_inter : 1;  /* bit[21]   : rfgain异频通道选择。1表示天线1和天线2交换。
                                                                       C模不配置。 */
        unsigned long  dsp_ch_switch_rfctrl_intra : 1;  /* bit[22]   : rfctrl本频通道选择。1表示天线1和天线2交换。
                                                                       C模不配置。 */
        unsigned long  dsp_ch_switch_rfctrl_inter : 1;  /* bit[23]   : rfctrl异频通道选择。1表示天线1和天线2交换。
                                                                       C模不配置。 */
        unsigned long  dsp_ch_switch_dc_intra     : 1;  /* bit[24]   : 静态DC本频通道选择。1表示天线1和天线2交换。
                                                                       C模不配置。 */
        unsigned long  dsp_ch_switch_dc_inter     : 1;  /* bit[25]   : 静态DC异频通道选择。1表示天线1和天线2交换。
                                                                       C模不配置。 */
        unsigned long  reserved_2                 : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_CHANNEL_FIX_DIG_GAIN_UNION;
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_channel_gain_at1_START        (0)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_channel_gain_at1_END          (6)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_channel_gain_at2_START        (8)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_channel_gain_at2_END          (14)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfgain_intra_START  (20)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfgain_intra_END    (20)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfgain_inter_START  (21)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfgain_inter_END    (21)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfctrl_intra_START  (22)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfctrl_intra_END    (22)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfctrl_inter_START  (23)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_rfctrl_inter_END    (23)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_dc_intra_START      (24)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_dc_intra_END        (24)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_dc_inter_START      (25)
#define WBBP_CHANNEL_FIX_DIG_GAIN_dsp_ch_switch_dc_inter_END        (25)


/*****************************************************************************
 结构名    : WBBP_AAGC_CTRL_TEST_UNION
 结构说明  : AAGC_CTRL_TEST 寄存器结构定义。地址偏移量:0x444，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_ctrl_test_reg;
    struct
    {
        unsigned long  dsp_ctrl_aagc_en    : 1;  /* bit[0]   : DSP控制AAGC增益使能。0，表示BBP控制AAGC增益；1，表示DSP控制AAGC增益。
                                                               C模不配置。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3] : 保留 */
        unsigned long  dsp_ctrl_aagc_state : 3;  /* bit[4-6] : DSP控制AAGC状态机。0，表示S1，即AAGC增益为s1_rf_gain；1，表示S2，即AAGC增益为s2_rf_gain；2，表示S3，即AAGC增益为s3_rf_gain；3，表示S4，即AAGC增益为s4_rf_gain；4，表示S5，即AAGC增益为s5_rf_gain；5，表示S6，即AAGC增益为s6_rf_gain；6，表示S7，即AAGC增益为s7_rf_gain；7，表示S8，即AAGC增益为s8_rf_gain。
                                                               C模不配置。 */
        unsigned long  reserved_1          : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_AAGC_CTRL_TEST_UNION;
#define WBBP_AAGC_CTRL_TEST_dsp_ctrl_aagc_en_START     (0)
#define WBBP_AAGC_CTRL_TEST_dsp_ctrl_aagc_en_END       (0)
#define WBBP_AAGC_CTRL_TEST_dsp_ctrl_aagc_state_START  (4)
#define WBBP_AAGC_CTRL_TEST_dsp_ctrl_aagc_state_END    (6)


/*****************************************************************************
 结构名    : WBBP_AAGC_GAIN_DELAY_UNION
 结构说明  : AAGC_GAIN_DELAY 寄存器结构定义。地址偏移量:0x448，初值:0x00030202，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_gain_delay_reg;
    struct
    {
        unsigned long  aagc_delay_slot_cnt_intra : 6;  /* bit[0-5]  : 自研RF AGC增益档的本频迟滞时间。时隙调整时，单位为时隙；符号调整时，单位为符号。
                                                                      C模不配置。 */
        unsigned long  reserved_0                : 2;  /* bit[6-7]  : 保留 */
        unsigned long  aagc_delay_slot_cnt_inter : 6;  /* bit[8-13] : 自研RF AGC增益档的异频频迟滞时间。时隙调整时，单位为时隙；符号调整时，单位为符号。
                                                                      C模不配置。 */
        unsigned long  reserved_1                : 2;  /* bit[14-15]: 保留 */
        unsigned long  aagc_delay_db             : 6;  /* bit[16-21]: Block检测检测到干扰时，自研RF -60dBm增益档的RSSI加上此值后，确定增益档位。有符号数，单位dB。
                                                                      C模不配置。 */
        unsigned long  reserved_2                : 10; /* bit[22-31]: 保留 */
    } reg;
} WBBP_AAGC_GAIN_DELAY_UNION;
#define WBBP_AAGC_GAIN_DELAY_aagc_delay_slot_cnt_intra_START  (0)
#define WBBP_AAGC_GAIN_DELAY_aagc_delay_slot_cnt_intra_END    (5)
#define WBBP_AAGC_GAIN_DELAY_aagc_delay_slot_cnt_inter_START  (8)
#define WBBP_AAGC_GAIN_DELAY_aagc_delay_slot_cnt_inter_END    (13)
#define WBBP_AAGC_GAIN_DELAY_aagc_delay_db_START              (16)
#define WBBP_AAGC_GAIN_DELAY_aagc_delay_db_END                (21)


/*****************************************************************************
 结构名    : WBBP_S1_8S_RF_CTRL_AT2_UNION
 结构说明  : S1_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x44C，初值:0x0070F800，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s1_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s1_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S1（RF RSSI为-102~-90dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S1_8S_RF_CTRL_AT2_UNION;
#define WBBP_S1_8S_RF_CTRL_AT2_s1_8s_rf_ctrl_at2_START  (0)
#define WBBP_S1_8S_RF_CTRL_AT2_s1_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S2_8S_RF_CTRL_AT2_UNION
 结构说明  : S2_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x450，初值:0x0070F400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s2_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s2_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S2（RF RSSI为-87~-69dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S2_8S_RF_CTRL_AT2_UNION;
#define WBBP_S2_8S_RF_CTRL_AT2_s2_8s_rf_ctrl_at2_START  (0)
#define WBBP_S2_8S_RF_CTRL_AT2_s2_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S3_8S_RF_CTRL_AT2_UNION
 结构说明  : S3_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x454，初值:0x0070E400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s3_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s3_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S3（RF RSSI为-66~-54dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S3_8S_RF_CTRL_AT2_UNION;
#define WBBP_S3_8S_RF_CTRL_AT2_s3_8s_rf_ctrl_at2_START  (0)
#define WBBP_S3_8S_RF_CTRL_AT2_s3_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S4_8S_RF_CTRL_AT2_UNION
 结构说明  : S4_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x458，初值:0x0070D400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s4_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s4_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S4（RF RSSI为-51~-39dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S4_8S_RF_CTRL_AT2_UNION;
#define WBBP_S4_8S_RF_CTRL_AT2_s4_8s_rf_ctrl_at2_START  (0)
#define WBBP_S4_8S_RF_CTRL_AT2_s4_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S5_8S_RF_CTRL_AT2_UNION
 结构说明  : S5_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x45C，初值:0x0070C400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s5_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s5_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S5（RF RSSI为-36~-21dBm）状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S5_8S_RF_CTRL_AT2_UNION;
#define WBBP_S5_8S_RF_CTRL_AT2_s5_8s_rf_ctrl_at2_START  (0)
#define WBBP_S5_8S_RF_CTRL_AT2_s5_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_UNION
 结构说明  : RF_8S_GAIN_S51_INTRA_AT1_AT2 寄存器结构定义。地址偏移量:0x460，初值:0x01D00110，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s51_intra_at1_at2_reg;
    struct
    {
        unsigned long  s5_8s_rf_gain_intra_at1 : 12; /* bit[0-11] : 八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s1_8s_rf_gain_intra_at2 : 12; /* bit[16-27]: 八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_UNION;
#define WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_s5_8s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_s5_8s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_s1_8s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_8S_GAIN_S51_INTRA_AT1_AT2_s1_8s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S23_INTRA_AT2_UNION
 结构说明  : RF_8S_GAIN_S23_INTRA_AT2 寄存器结构定义。地址偏移量:0x464，初值:0x017001A0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s23_intra_at2_reg;
    struct
    {
        unsigned long  s2_8s_rf_gain_intra_at2 : 12; /* bit[0-11] : 八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s3_8s_rf_gain_intra_at2 : 12; /* bit[16-27]: 八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S23_INTRA_AT2_UNION;
#define WBBP_RF_8S_GAIN_S23_INTRA_AT2_s2_8s_rf_gain_intra_at2_START  (0)
#define WBBP_RF_8S_GAIN_S23_INTRA_AT2_s2_8s_rf_gain_intra_at2_END    (11)
#define WBBP_RF_8S_GAIN_S23_INTRA_AT2_s3_8s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_8S_GAIN_S23_INTRA_AT2_s3_8s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S45_INTRA_AT2_UNION
 结构说明  : RF_8S_GAIN_S45_INTRA_AT2 寄存器结构定义。地址偏移量:0x468，初值:0x01100140，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s45_intra_at2_reg;
    struct
    {
        unsigned long  s4_8s_rf_gain_intra_at2 : 12; /* bit[0-11] : 八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s5_8s_rf_gain_intra_at2 : 12; /* bit[16-27]: 八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S45_INTRA_AT2_UNION;
#define WBBP_RF_8S_GAIN_S45_INTRA_AT2_s4_8s_rf_gain_intra_at2_START  (0)
#define WBBP_RF_8S_GAIN_S45_INTRA_AT2_s4_8s_rf_gain_intra_at2_END    (11)
#define WBBP_RF_8S_GAIN_S45_INTRA_AT2_s5_8s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_8S_GAIN_S45_INTRA_AT2_s5_8s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S12_INTER_AT1_UNION
 结构说明  : RF_8S_GAIN_S12_INTER_AT1 寄存器结构定义。地址偏移量:0x46C，初值:0x01A001D0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s12_inter_at1_reg;
    struct
    {
        unsigned long  s1_8s_rf_gain_inter_at1 : 12; /* bit[0-11] : 八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s2_8s_rf_gain_inter_at1 : 12; /* bit[16-27]: 八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S12_INTER_AT1_UNION;
#define WBBP_RF_8S_GAIN_S12_INTER_AT1_s1_8s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_8S_GAIN_S12_INTER_AT1_s1_8s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_8S_GAIN_S12_INTER_AT1_s2_8s_rf_gain_inter_at1_START  (16)
#define WBBP_RF_8S_GAIN_S12_INTER_AT1_s2_8s_rf_gain_inter_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S34_INTER_AT1_UNION
 结构说明  : RF_8S_GAIN_S34_INTER_AT1 寄存器结构定义。地址偏移量:0x470，初值:0x01400170，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s34_inter_at1_reg;
    struct
    {
        unsigned long  s3_8s_rf_gain_inter_at1 : 12; /* bit[0-11] : 八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s4_8s_rf_gain_inter_at1 : 12; /* bit[16-27]: 八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S34_INTER_AT1_UNION;
#define WBBP_RF_8S_GAIN_S34_INTER_AT1_s3_8s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_8S_GAIN_S34_INTER_AT1_s3_8s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_8S_GAIN_S34_INTER_AT1_s4_8s_rf_gain_inter_at1_START  (16)
#define WBBP_RF_8S_GAIN_S34_INTER_AT1_s4_8s_rf_gain_inter_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_UNION
 结构说明  : RF_8S_GAIN_S51_INTER_AT1_AT2 寄存器结构定义。地址偏移量:0x474，初值:0x01D00110，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s51_inter_at1_at2_reg;
    struct
    {
        unsigned long  s5_8s_rf_gain_inter_at1 : 12; /* bit[0-11] : 八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s1_8s_rf_gain_inter_at2 : 12; /* bit[16-27]: 八档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_UNION;
#define WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_s5_8s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_s5_8s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_s1_8s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_8S_GAIN_S51_INTER_AT1_AT2_s1_8s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_BLOCK_DETECT_EN_UNION
 结构说明  : BLOCK_DETECT_EN 寄存器结构定义。地址偏移量:0x478，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_detect_en_reg;
    struct
    {
        unsigned long  dsp_block_detect_en     : 1;  /* bit[0]   : 干扰检测使能信号。0，表示不打开干扰检测功能；1，表示打开干扰检测功能。
                                                                   说明：此功能仅在D/F态下使用。
                                                                   C模不配置。 */
        unsigned long  dsp_abb_blk_en          : 1;  /* bit[1]   : ABB block检测使能信号。1，BBP会给ABB开窗；0，BBP不给ABB开窗。 */
        unsigned long  reserved_0              : 2;  /* bit[2-3] : 保留 */
        unsigned long  dsp_cpc_force_dcr1st_en : 1;  /* bit[4]   : 退出cpc_drx状态时，RSSI和AGC档位的来源，1表示使用DSP配置的init值，0表示使用进入cpc_drx状态时的保存值。
                                                                   C模不配置。 */
        unsigned long  reserved_1              : 3;  /* bit[5-7] : 保留 */
        unsigned long  dsp_cpc_force_agc_en    : 1;  /* bit[8]   : 退出cpc_drx状态时，是否启动第一阶段DCR算法，1表示启动，0表示不启动。
                                                                   C模不配置。 */
        unsigned long  reserved_2              : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_BLOCK_DETECT_EN_UNION;
#define WBBP_BLOCK_DETECT_EN_dsp_block_detect_en_START      (0)
#define WBBP_BLOCK_DETECT_EN_dsp_block_detect_en_END        (0)
#define WBBP_BLOCK_DETECT_EN_dsp_abb_blk_en_START           (1)
#define WBBP_BLOCK_DETECT_EN_dsp_abb_blk_en_END             (1)
#define WBBP_BLOCK_DETECT_EN_dsp_cpc_force_dcr1st_en_START  (4)
#define WBBP_BLOCK_DETECT_EN_dsp_cpc_force_dcr1st_en_END    (4)
#define WBBP_BLOCK_DETECT_EN_dsp_cpc_force_agc_en_START     (8)
#define WBBP_BLOCK_DETECT_EN_dsp_cpc_force_agc_en_END       (8)


/*****************************************************************************
 结构名    : WBBP_BLOCK_LPF_SEL_UNION
 结构说明  : BLOCK_LPF_SEL 寄存器结构定义。地址偏移量:0x480，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_lpf_sel_reg;
    struct
    {
        unsigned long  reserved           : 30; /* bit[0-29]: 保留 */
        unsigned long  block_default_1sel : 1;  /* bit[30]  : 打开Block检测时Block检测默认配置。1，表示使用4阶LPF；0，表示使用2阶LPF。
                                                              C模不配置。 */
        unsigned long  block_default_sel  : 1;  /* bit[31]  : 关闭Block检测时Block检测默认配置。1，表示使用4阶LPF；0，表示使用2阶LPF。
                                                              C模不配置。 */
    } reg;
} WBBP_BLOCK_LPF_SEL_UNION;
#define WBBP_BLOCK_LPF_SEL_block_default_1sel_START  (30)
#define WBBP_BLOCK_LPF_SEL_block_default_1sel_END    (30)
#define WBBP_BLOCK_LPF_SEL_block_default_sel_START   (31)
#define WBBP_BLOCK_LPF_SEL_block_default_sel_END     (31)


/*****************************************************************************
 结构名    : WBBP_BLOCK_HYS_SLOT_UNION
 结构说明  : BLOCK_HYS_SLOT 寄存器结构定义。地址偏移量:0x484，初值:0x000F0202，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_hys_slot_reg;
    struct
    {
        unsigned long  block_2stage_slot : 6;  /* bit[0-5]  : 在2阶低通滤波器停留的最短时间，单位slot。
                                                              C模不配置。 */
        unsigned long  reserved_0        : 2;  /* bit[6-7]  : 保留 */
        unsigned long  block_hys_th      : 6;  /* bit[8-13] : Block条件满足次数达到block_hys_th次时，才切换Block控制状态。
                                                              C模不配置。 */
        unsigned long  reserved_1        : 2;  /* bit[14-15]: 保留 */
        unsigned long  block_4stage_slot : 6;  /* bit[16-21]: 在4阶低通滤波器停留的最短时间，单位slot。
                                                              C模不配置。 */
        unsigned long  reserved_2        : 10; /* bit[22-31]: 保留 */
    } reg;
} WBBP_BLOCK_HYS_SLOT_UNION;
#define WBBP_BLOCK_HYS_SLOT_block_2stage_slot_START  (0)
#define WBBP_BLOCK_HYS_SLOT_block_2stage_slot_END    (5)
#define WBBP_BLOCK_HYS_SLOT_block_hys_th_START       (8)
#define WBBP_BLOCK_HYS_SLOT_block_hys_th_END         (13)
#define WBBP_BLOCK_HYS_SLOT_block_4stage_slot_START  (16)
#define WBBP_BLOCK_HYS_SLOT_block_4stage_slot_END    (21)


/*****************************************************************************
 结构名    : WBBP_BLOCK_GEN_TH_UNION
 结构说明  : BLOCK_GEN_TH 寄存器结构定义。地址偏移量:0x488，初值:0x00063F2A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_gen_th_reg;
    struct
    {
        unsigned long  block_gen_rrc_in_th  : 6;  /* bit[0-5]  : 干扰产生第一种条件中，RRC滤波器输入端RSSI判断门限，单位dB。
                                                                 说明：干扰产生的第一种条件，RRC滤波器之前的RSSI值>=block_gen_rrc_in_th，且RRC前后的RSSI差值>=block_gen_diff_th。
                                                                 C模不配置。 */
        unsigned long  reserved_0           : 2;  /* bit[6-7]  : 保留 */
        unsigned long  block_gen_rrc_in_2th : 6;  /* bit[8-13] : 干扰产生第二种条件中，RRC滤波器输入端RSSI判断门限，单位dB。
                                                                 说明：干扰产生的第二种条件，RRC滤波器之前的RSSI值>=block_gen_rrc_in_2th。
                                                                 C模不配置。 */
        unsigned long  reserved_1           : 2;  /* bit[14-15]: 保留 */
        unsigned long  block_gen_diff_th    : 6;  /* bit[16-21]: 干扰产生第一种条件中，RRC滤波器前后RSSI差值判断门限，单位dB。
                                                                 C模不配置。 */
        unsigned long  reserved_2           : 10; /* bit[22-31]: 保留 */
    } reg;
} WBBP_BLOCK_GEN_TH_UNION;
#define WBBP_BLOCK_GEN_TH_block_gen_rrc_in_th_START   (0)
#define WBBP_BLOCK_GEN_TH_block_gen_rrc_in_th_END     (5)
#define WBBP_BLOCK_GEN_TH_block_gen_rrc_in_2th_START  (8)
#define WBBP_BLOCK_GEN_TH_block_gen_rrc_in_2th_END    (13)
#define WBBP_BLOCK_GEN_TH_block_gen_diff_th_START     (16)
#define WBBP_BLOCK_GEN_TH_block_gen_diff_th_END       (21)


/*****************************************************************************
 结构名    : WBBP_BLOCK_DIS_LTH_UNION
 结构说明  : BLOCK_DIS_LTH 寄存器结构定义。地址偏移量:0x48C，初值:0x00180014，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_dis_lth_reg;
    struct
    {
        unsigned long  block_dis_rrc_out_lth : 6;  /* bit[0-5]  : 干扰消失第一种条件中，RRC滤波器输出端RSSI判断门限，单位dB。
                                                                  说明：干扰消失的第一种条件，RRC滤波器之后的RSSI<=block_dis_rrc_out_lth，且RRC滤波器之前的RSSI<=block_dis_rrc_in_th。
                                                                  C模不配置。 */
        unsigned long  reserved_0            : 10; /* bit[6-15] : 保留 */
        unsigned long  block_dis_rrc_in_th   : 6;  /* bit[16-21]: 干扰消失第一种条件中，RRC滤波器输入端RSSI判断门限，单位dB。
                                                                  C模不配置。 */
        unsigned long  reserved_1            : 10; /* bit[22-31]: 保留 */
    } reg;
} WBBP_BLOCK_DIS_LTH_UNION;
#define WBBP_BLOCK_DIS_LTH_block_dis_rrc_out_lth_START  (0)
#define WBBP_BLOCK_DIS_LTH_block_dis_rrc_out_lth_END    (5)
#define WBBP_BLOCK_DIS_LTH_block_dis_rrc_in_th_START    (16)
#define WBBP_BLOCK_DIS_LTH_block_dis_rrc_in_th_END      (21)


/*****************************************************************************
 结构名    : WBBP_BLOCK_DIS_HTH_UNION
 结构说明  : BLOCK_DIS_HTH 寄存器结构定义。地址偏移量:0x490，初值:0x00020014，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_dis_hth_reg;
    struct
    {
        unsigned long  block_dis_rrc_out_hth : 6;  /* bit[0-5]  : 干扰消失第二种条件中，RRC滤波器输出端RSSI判断门限，单位dB。
                                                                  说明：干扰消失的第二种条件，RRC滤波器之后的RSSI>block_dis_rrc_out_hth，且RRC滤波器前后的RSSI差值<=block_dis_diff_th。
                                                                  C模不配置。 */
        unsigned long  reserved_0            : 10; /* bit[6-15] : 保留 */
        unsigned long  block_dis_diff_th     : 6;  /* bit[16-21]: 干扰消失第二种条件中，RRC滤波器前后RSSI差值判断门限，单位dB。
                                                                  C模不配置。 */
        unsigned long  reserved_1            : 10; /* bit[22-31]: 保留 */
    } reg;
} WBBP_BLOCK_DIS_HTH_UNION;
#define WBBP_BLOCK_DIS_HTH_block_dis_rrc_out_hth_START  (0)
#define WBBP_BLOCK_DIS_HTH_block_dis_rrc_out_hth_END    (5)
#define WBBP_BLOCK_DIS_HTH_block_dis_diff_th_START      (16)
#define WBBP_BLOCK_DIS_HTH_block_dis_diff_th_END        (21)


/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_8S_INC_TH_A20_UNION
 结构说明  : AAGC_RSSI_8S_INC_TH_A20 寄存器结构定义。地址偏移量:0x4AC，初值:0x00E0DAD4，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_8s_inc_th_a20_reg;
    struct
    {
        unsigned long  s5_2s6_8s_th : 8;  /* bit[0-7]  : 八档AAGC状态跳转S5->S6的RSSI门限，单位dBm，配置二进制补码值。
                                                         可参考AAGC_RSSI_INC_TH寄存器的说明。
                                                         C模不配置。 */
        unsigned long  s6_2s7_8s_th : 8;  /* bit[8-15] : 八档AAGC状态跳转S6->S7的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s7_2s8_8s_th : 8;  /* bit[16-23]: 八档AAGC状态跳转S7->S8的RSSI门限。
                                                         C模不配置。 */
        unsigned long  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_AAGC_RSSI_8S_INC_TH_A20_UNION;
#define WBBP_AAGC_RSSI_8S_INC_TH_A20_s5_2s6_8s_th_START  (0)
#define WBBP_AAGC_RSSI_8S_INC_TH_A20_s5_2s6_8s_th_END    (7)
#define WBBP_AAGC_RSSI_8S_INC_TH_A20_s6_2s7_8s_th_START  (8)
#define WBBP_AAGC_RSSI_8S_INC_TH_A20_s6_2s7_8s_th_END    (15)
#define WBBP_AAGC_RSSI_8S_INC_TH_A20_s7_2s8_8s_th_START  (16)
#define WBBP_AAGC_RSSI_8S_INC_TH_A20_s7_2s8_8s_th_END    (23)


/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_8S_DEC_TH_A20_UNION
 结构说明  : AAGC_RSSI_8S_DEC_TH_A20 寄存器结构定义。地址偏移量:0x4B0，初值:0x00D2C9C3，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_8s_dec_th_a20_reg;
    struct
    {
        unsigned long  s6_2s5_8s_th : 8;  /* bit[0-7]  : 八档AAGC状态跳转S6->S5的RSSI门限，单位dBm，配置二进制补码值。
                                                         可参考AAGC_RSSI_DEC_TH寄存器的说明。
                                                         C模不配置。 */
        unsigned long  s7_2s6_8s_th : 8;  /* bit[8-15] : 八档AAGC状态跳转S7->S6的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s8_2s7_8s_th : 8;  /* bit[16-23]: 八档AAGC状态跳转S8->S7的RSSI门限。
                                                         C模不配置。 */
        unsigned long  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_AAGC_RSSI_8S_DEC_TH_A20_UNION;
#define WBBP_AAGC_RSSI_8S_DEC_TH_A20_s6_2s5_8s_th_START  (0)
#define WBBP_AAGC_RSSI_8S_DEC_TH_A20_s6_2s5_8s_th_END    (7)
#define WBBP_AAGC_RSSI_8S_DEC_TH_A20_s7_2s6_8s_th_START  (8)
#define WBBP_AAGC_RSSI_8S_DEC_TH_A20_s7_2s6_8s_th_END    (15)
#define WBBP_AAGC_RSSI_8S_DEC_TH_A20_s8_2s7_8s_th_START  (16)
#define WBBP_AAGC_RSSI_8S_DEC_TH_A20_s8_2s7_8s_th_END    (23)


/*****************************************************************************
 结构名    : WBBP_S6_8S_RF_CTRL_AT1_UNION
 结构说明  : S6_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x4B4，初值:0x00549400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s6_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s6_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S6状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S6_8S_RF_CTRL_AT1_UNION;
#define WBBP_S6_8S_RF_CTRL_AT1_s6_8s_rf_ctrl_at1_START  (0)
#define WBBP_S6_8S_RF_CTRL_AT1_s6_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S7_8S_RF_CTRL_AT1_UNION
 结构说明  : S7_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x4B8，初值:0x00548400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s7_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s7_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S7状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S7_8S_RF_CTRL_AT1_UNION;
#define WBBP_S7_8S_RF_CTRL_AT1_s7_8s_rf_ctrl_at1_START  (0)
#define WBBP_S7_8S_RF_CTRL_AT1_s7_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S8_8S_RF_CTRL_AT1_UNION
 结构说明  : S8_8S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0x4BC，初值:0x00545200，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s8_8s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s8_8s_rf_ctrl_at1 : 24; /* bit[0-23] : 八档AAGC S8状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S8_8S_RF_CTRL_AT1_UNION;
#define WBBP_S8_8S_RF_CTRL_AT1_s8_8s_rf_ctrl_at1_START  (0)
#define WBBP_S8_8S_RF_CTRL_AT1_s8_8s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S6_8S_RF_CTRL_AT2_UNION
 结构说明  : S6_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x4C0，初值:0x00709400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s6_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s6_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S6状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S6_8S_RF_CTRL_AT2_UNION;
#define WBBP_S6_8S_RF_CTRL_AT2_s6_8s_rf_ctrl_at2_START  (0)
#define WBBP_S6_8S_RF_CTRL_AT2_s6_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S7_8S_RF_CTRL_AT2_UNION
 结构说明  : S7_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x4C4，初值:0x00708400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s7_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s7_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S7状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S7_8S_RF_CTRL_AT2_UNION;
#define WBBP_S7_8S_RF_CTRL_AT2_s7_8s_rf_ctrl_at2_START  (0)
#define WBBP_S7_8S_RF_CTRL_AT2_s7_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S8_8S_RF_CTRL_AT2_UNION
 结构说明  : S8_8S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x4C8，初值:0x00705200，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s8_8s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s8_8s_rf_ctrl_at2 : 24; /* bit[0-23] : 八档AAGC S8状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S8_8S_RF_CTRL_AT2_UNION;
#define WBBP_S8_8S_RF_CTRL_AT2_s8_8s_rf_ctrl_at2_START  (0)
#define WBBP_S8_8S_RF_CTRL_AT2_s8_8s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_UNION
 结构说明  : RF_8S_GAIN_S67_INTER_AT1_A20 寄存器结构定义。地址偏移量:0x4CC，初值:0x00B000E0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s67_inter_at1_a20_reg;
    struct
    {
        unsigned long  s6_8s_rf_gain_inter_at1 : 12; /* bit[0-11] : 八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_8s_rf_gain_inter_at1 : 12; /* bit[16-27]: 八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_UNION;
#define WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_s6_8s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_s6_8s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_s7_8s_rf_gain_inter_at1_START  (16)
#define WBBP_RF_8S_GAIN_S67_INTER_AT1_A20_s7_8s_rf_gain_inter_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S8_INTER_AT1_A20_UNION
 结构说明  : RF_8S_GAIN_S8_INTER_AT1_A20 寄存器结构定义。地址偏移量:0x4D0，初值:0x00000068，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s8_inter_at1_a20_reg;
    struct
    {
        unsigned long  s8_8s_rf_gain_inter_at1 : 12; /* bit[0-11] : 八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S8_INTER_AT1_A20_UNION;
#define WBBP_RF_8S_GAIN_S8_INTER_AT1_A20_s8_8s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_8S_GAIN_S8_INTER_AT1_A20_s8_8s_rf_gain_inter_at1_END    (11)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_UNION
 结构说明  : RF_8S_GAIN_S67_INTER_AT2_A20 寄存器结构定义。地址偏移量:0x4D4，初值:0x00B000E0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s67_inter_at2_a20_reg;
    struct
    {
        unsigned long  s6_8s_rf_gain_inter_at2 : 12; /* bit[0-11] : 八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_8s_rf_gain_inter_at2 : 12; /* bit[16-27]: 八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_UNION;
#define WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_s6_8s_rf_gain_inter_at2_START  (0)
#define WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_s6_8s_rf_gain_inter_at2_END    (11)
#define WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_s7_8s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_8S_GAIN_S67_INTER_AT2_A20_s7_8s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S8_INTER_AT2_A20_UNION
 结构说明  : RF_8S_GAIN_S8_INTER_AT2_A20 寄存器结构定义。地址偏移量:0x4D8，初值:0x00000068，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s8_inter_at2_a20_reg;
    struct
    {
        unsigned long  s8_8s_rf_gain_inter_at2 : 12; /* bit[0-11] : 八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S8_INTER_AT2_A20_UNION;
#define WBBP_RF_8S_GAIN_S8_INTER_AT2_A20_s8_8s_rf_gain_inter_at2_START  (0)
#define WBBP_RF_8S_GAIN_S8_INTER_AT2_A20_s8_8s_rf_gain_inter_at2_END    (11)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_UNION
 结构说明  : RF_8S_GAIN_S67_INTRA_AT1_A20 寄存器结构定义。地址偏移量:0x4DC，初值:0x00B000E0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s67_intra_at1_a20_reg;
    struct
    {
        unsigned long  s6_8s_rf_gain_intra_at1 : 12; /* bit[0-11] : 八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_8s_rf_gain_intra_at1 : 12; /* bit[16-27]: 八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_UNION;
#define WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_s6_8s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_s6_8s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_s7_8s_rf_gain_intra_at1_START  (16)
#define WBBP_RF_8S_GAIN_S67_INTRA_AT1_A20_s7_8s_rf_gain_intra_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_BLOCK_RPT_AT1_UNION
 结构说明  : BLOCK_RPT_AT1 寄存器结构定义。地址偏移量:0x4E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_rpt_at1_reg;
    struct
    {
        unsigned long  drssi_125db_rrc_in_at1  : 10; /* bit[0-9]  : RRC滤波器之前统计的DRSSI值，单位0.125dB。 */
        unsigned long  reserved_0              : 6;  /* bit[10-15]: 保留 */
        unsigned long  drssi_125db_rrc_out_at1 : 10; /* bit[16-25]: RRC滤波器之后统计的DRSSI值，单位0.125dB。 */
        unsigned long  reserved_1              : 2;  /* bit[26-27]: 保留 */
        unsigned long  bbp_hw_blk_ind_at1      : 1;  /* bit[28]   : BBP上报硬件Block检测结果。0，不处于Block；1，处于Block。 */
        unsigned long  reserved_2              : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_BLOCK_RPT_AT1_UNION;
#define WBBP_BLOCK_RPT_AT1_drssi_125db_rrc_in_at1_START   (0)
#define WBBP_BLOCK_RPT_AT1_drssi_125db_rrc_in_at1_END     (9)
#define WBBP_BLOCK_RPT_AT1_drssi_125db_rrc_out_at1_START  (16)
#define WBBP_BLOCK_RPT_AT1_drssi_125db_rrc_out_at1_END    (25)
#define WBBP_BLOCK_RPT_AT1_bbp_hw_blk_ind_at1_START       (28)
#define WBBP_BLOCK_RPT_AT1_bbp_hw_blk_ind_at1_END         (28)


/*****************************************************************************
 结构名    : WBBP_BLOCK_RPT_AT2_UNION
 结构说明  : BLOCK_RPT_AT2 寄存器结构定义。地址偏移量:0x4E4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_rpt_at2_reg;
    struct
    {
        unsigned long  drssi_125db_rrc_in_at2  : 10; /* bit[0-9]  : RRC滤波器之前统计的DRSSI值，单位0.125dB。 */
        unsigned long  reserved_0              : 6;  /* bit[10-15]: 保留 */
        unsigned long  drssi_125db_rrc_out_at2 : 10; /* bit[16-25]: RRC滤波器之后统计的DRSSI值，单位0.125dB。 */
        unsigned long  reserved_1              : 2;  /* bit[26-27]: 保留 */
        unsigned long  bbp_hw_blk_ind_at2      : 1;  /* bit[28]   : BBP上报硬件Block检测结果。0，不处于Block；1，处于Block。 */
        unsigned long  reserved_2              : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_BLOCK_RPT_AT2_UNION;
#define WBBP_BLOCK_RPT_AT2_drssi_125db_rrc_in_at2_START   (0)
#define WBBP_BLOCK_RPT_AT2_drssi_125db_rrc_in_at2_END     (9)
#define WBBP_BLOCK_RPT_AT2_drssi_125db_rrc_out_at2_START  (16)
#define WBBP_BLOCK_RPT_AT2_drssi_125db_rrc_out_at2_END    (25)
#define WBBP_BLOCK_RPT_AT2_bbp_hw_blk_ind_at2_START       (28)
#define WBBP_BLOCK_RPT_AT2_bbp_hw_blk_ind_at2_END         (28)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S23_INTER_AT2_UNION
 结构说明  : RF_8S_GAIN_S23_INTER_AT2 寄存器结构定义。地址偏移量:0x4E8，初值:0x017001A0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s23_inter_at2_reg;
    struct
    {
        unsigned long  s2_8s_rf_gain_inter_at2 : 12; /* bit[0-11] : 八档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s3_8s_rf_gain_inter_at2 : 12; /* bit[16-27]: 八档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S23_INTER_AT2_UNION;
#define WBBP_RF_8S_GAIN_S23_INTER_AT2_s2_8s_rf_gain_inter_at2_START  (0)
#define WBBP_RF_8S_GAIN_S23_INTER_AT2_s2_8s_rf_gain_inter_at2_END    (11)
#define WBBP_RF_8S_GAIN_S23_INTER_AT2_s3_8s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_8S_GAIN_S23_INTER_AT2_s3_8s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S45_INTER_AT2_UNION
 结构说明  : RF_8S_GAIN_S45_INTER_AT2 寄存器结构定义。地址偏移量:0x4EC，初值:0x01100140，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s45_inter_at2_reg;
    struct
    {
        unsigned long  s4_8s_rf_gain_inter_at2 : 12; /* bit[0-11] : 八档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s5_8s_rf_gain_inter_at2 : 12; /* bit[16-27]: 八档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S45_INTER_AT2_UNION;
#define WBBP_RF_8S_GAIN_S45_INTER_AT2_s4_8s_rf_gain_inter_at2_START  (0)
#define WBBP_RF_8S_GAIN_S45_INTER_AT2_s4_8s_rf_gain_inter_at2_END    (11)
#define WBBP_RF_8S_GAIN_S45_INTER_AT2_s5_8s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_8S_GAIN_S45_INTER_AT2_s5_8s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S8_INTRA_AT1_A20_UNION
 结构说明  : RF_8S_GAIN_S8_INTRA_AT1_A20 寄存器结构定义。地址偏移量:0x4F0，初值:0x00000068，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s8_intra_at1_a20_reg;
    struct
    {
        unsigned long  s8_8s_rf_gain_intra_at1 : 12; /* bit[0-11] : 八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S8_INTRA_AT1_A20_UNION;
#define WBBP_RF_8S_GAIN_S8_INTRA_AT1_A20_s8_8s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_8S_GAIN_S8_INTRA_AT1_A20_s8_8s_rf_gain_intra_at1_END    (11)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_UNION
 结构说明  : RF_8S_GAIN_S67_INTRA_AT2_A20 寄存器结构定义。地址偏移量:0x4F4，初值:0x00B000E0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s67_intra_at2_a20_reg;
    struct
    {
        unsigned long  s6_8s_rf_gain_intra_at2 : 12; /* bit[0-11] : 八档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_8s_rf_gain_intra_at2 : 12; /* bit[16-27]: 八档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_UNION;
#define WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_s6_8s_rf_gain_intra_at2_START  (0)
#define WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_s6_8s_rf_gain_intra_at2_END    (11)
#define WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_s7_8s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_8S_GAIN_S67_INTRA_AT2_A20_s7_8s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_8S_GAIN_S8_INTRA_AT2_A20_UNION
 结构说明  : RF_8S_GAIN_S8_INTRA_AT2_A20 寄存器结构定义。地址偏移量:0x4F8，初值:0x00000068，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_gain_s8_intra_at2_a20_reg;
    struct
    {
        unsigned long  s8_8s_rf_gain_intra_at2 : 12; /* bit[0-11] : 八档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_RF_8S_GAIN_S8_INTRA_AT2_A20_UNION;
#define WBBP_RF_8S_GAIN_S8_INTRA_AT2_A20_s8_8s_rf_gain_intra_at2_START  (0)
#define WBBP_RF_8S_GAIN_S8_INTRA_AT2_A20_s8_8s_rf_gain_intra_at2_END    (11)


/*****************************************************************************
 结构名    : WBBP_RF_GAIN_CFG_FREQ_UNION
 结构说明  : RF_GAIN_CFG_FREQ 寄存器结构定义。地址偏移量:0x4FC，初值:0x800005DC，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_gain_cfg_freq_reg;
    struct
    {
        unsigned long  rf_cfg_slot_num : 16; /* bit[0-15] : 周期配置RF增益控制寄存器的周期，单位slot。
                                                            C模不配置。 */
        unsigned long  reserved        : 15; /* bit[16-30]: 保留 */
        unsigned long  rf_cfg_slot_en  : 1;  /* bit[31]   : 周期配置RF增益控制寄存器的使能。1，表示周期配置RF增益控制寄存器；0，表示只在增益状态跳转时配置RF增益控制寄存器。
                                                            C模不配置。 */
    } reg;
} WBBP_RF_GAIN_CFG_FREQ_UNION;
#define WBBP_RF_GAIN_CFG_FREQ_rf_cfg_slot_num_START  (0)
#define WBBP_RF_GAIN_CFG_FREQ_rf_cfg_slot_num_END    (15)
#define WBBP_RF_GAIN_CFG_FREQ_rf_cfg_slot_en_START   (31)
#define WBBP_RF_GAIN_CFG_FREQ_rf_cfg_slot_en_END     (31)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S1_VBIAS_AT1_UNION
 结构说明  : RF_5S_S1_VBIAS_AT1 寄存器结构定义。地址偏移量:0x500，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s1_vbias_at1_reg;
    struct
    {
        unsigned long  s1_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S1对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S1_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S1_VBIAS_AT1_s1_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S1_VBIAS_AT1_s1_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S2_VBIAS_AT1_UNION
 结构说明  : RF_5S_S2_VBIAS_AT1 寄存器结构定义。地址偏移量:0x504，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s2_vbias_at1_reg;
    struct
    {
        unsigned long  s2_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S2对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S2_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S2_VBIAS_AT1_s2_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S2_VBIAS_AT1_s2_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S3_VBIAS_AT1_UNION
 结构说明  : RF_5S_S3_VBIAS_AT1 寄存器结构定义。地址偏移量:0x508，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s3_vbias_at1_reg;
    struct
    {
        unsigned long  s3_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S3对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S3_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S3_VBIAS_AT1_s3_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S3_VBIAS_AT1_s3_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S4_VBIAS_AT1_UNION
 结构说明  : RF_5S_S4_VBIAS_AT1 寄存器结构定义。地址偏移量:0x50C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s4_vbias_at1_reg;
    struct
    {
        unsigned long  s4_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S4对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S4_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S4_VBIAS_AT1_s4_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S4_VBIAS_AT1_s4_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S5_VBIAS_AT1_UNION
 结构说明  : RF_5S_S5_VBIAS_AT1 寄存器结构定义。地址偏移量:0x510，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s5_vbias_at1_reg;
    struct
    {
        unsigned long  s5_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S5对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S5_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S5_VBIAS_AT1_s5_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S5_VBIAS_AT1_s5_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S6_VBIAS_AT1_UNION
 结构说明  : RF_5S_S6_VBIAS_AT1 寄存器结构定义。地址偏移量:0x514，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s6_vbias_at1_reg;
    struct
    {
        unsigned long  s6_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S6对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S6_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S6_VBIAS_AT1_s6_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S6_VBIAS_AT1_s6_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S7_VBIAS_AT1_UNION
 结构说明  : RF_5S_S7_VBIAS_AT1 寄存器结构定义。地址偏移量:0x518，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s7_vbias_at1_reg;
    struct
    {
        unsigned long  s7_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S7对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S7_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S7_VBIAS_AT1_s7_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S7_VBIAS_AT1_s7_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S8_VBIAS_AT1_UNION
 结构说明  : RF_5S_S8_VBIAS_AT1 寄存器结构定义。地址偏移量:0x51C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s8_vbias_at1_reg;
    struct
    {
        unsigned long  s8_5s_vbias_at1 : 24; /* bit[0-23] : 主天线BLOCK下S8对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S8_VBIAS_AT1_UNION;
#define WBBP_RF_5S_S8_VBIAS_AT1_s8_5s_vbias_at1_START  (0)
#define WBBP_RF_5S_S8_VBIAS_AT1_s8_5s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S1_VBIAS_AT2_UNION
 结构说明  : RF_5S_S1_VBIAS_AT2 寄存器结构定义。地址偏移量:0x520，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s1_vbias_at2_reg;
    struct
    {
        unsigned long  s1_5s_vbias_at2 : 24; /* bit[0-23] : 主天线BLOCK下S1对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S1_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S1_VBIAS_AT2_s1_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S1_VBIAS_AT2_s1_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S2_VBIAS_AT2_UNION
 结构说明  : RF_5S_S2_VBIAS_AT2 寄存器结构定义。地址偏移量:0x524，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s2_vbias_at2_reg;
    struct
    {
        unsigned long  s2_5s_vbias_at2 : 24; /* bit[0-23] : 辅天线BLOCK下S2对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S2_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S2_VBIAS_AT2_s2_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S2_VBIAS_AT2_s2_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S3_VBIAS_AT2_UNION
 结构说明  : RF_5S_S3_VBIAS_AT2 寄存器结构定义。地址偏移量:0x528，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s3_vbias_at2_reg;
    struct
    {
        unsigned long  s3_5s_vbias_at2 : 24; /* bit[0-23] : 辅天线BLOCK下S3对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S3_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S3_VBIAS_AT2_s3_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S3_VBIAS_AT2_s3_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S4_VBIAS_AT2_UNION
 结构说明  : RF_5S_S4_VBIAS_AT2 寄存器结构定义。地址偏移量:0x52C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s4_vbias_at2_reg;
    struct
    {
        unsigned long  s4_5s_vbias_at2 : 24; /* bit[0-23] : 辅天线BLOCK下S4对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S4_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S4_VBIAS_AT2_s4_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S4_VBIAS_AT2_s4_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S5_VBIAS_AT2_UNION
 结构说明  : RF_5S_S5_VBIAS_AT2 寄存器结构定义。地址偏移量:0x530，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s5_vbias_at2_reg;
    struct
    {
        unsigned long  s5_5s_vbias_at2 : 24; /* bit[0-23] : 辅天线BLOCK下S5对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S5_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S5_VBIAS_AT2_s5_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S5_VBIAS_AT2_s5_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S6_VBIAS_AT2_UNION
 结构说明  : RF_5S_S6_VBIAS_AT2 寄存器结构定义。地址偏移量:0x534，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s6_vbias_at2_reg;
    struct
    {
        unsigned long  s6_5s_vbias_at2 : 24; /* bit[0-23] : 辅天线BLOCK下S6对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S6_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S6_VBIAS_AT2_s6_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S6_VBIAS_AT2_s6_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S7_VBIAS_AT2_UNION
 结构说明  : RF_5S_S7_VBIAS_AT2 寄存器结构定义。地址偏移量:0x538，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s7_vbias_at2_reg;
    struct
    {
        unsigned long  s7_5s_vbias_at2 : 24; /* bit[0-23] : 辅天线BLOCK下S7对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S7_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S7_VBIAS_AT2_s7_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S7_VBIAS_AT2_s7_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_S8_VBIAS_AT2_UNION
 结构说明  : RF_5S_S8_VBIAS_AT2 寄存器结构定义。地址偏移量:0x53C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_s8_vbias_at2_reg;
    struct
    {
        unsigned long  s8_5s_vbias_at2 : 24; /* bit[0-23] : 辅天线BLOCK下S8对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_5S_S8_VBIAS_AT2_UNION;
#define WBBP_RF_5S_S8_VBIAS_AT2_s8_5s_vbias_at2_START  (0)
#define WBBP_RF_5S_S8_VBIAS_AT2_s8_5s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S1_VBIAS_AT1_UNION
 结构说明  : RF_8S_S1_VBIAS_AT1 寄存器结构定义。地址偏移量:0x540，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s1_vbias_at1_reg;
    struct
    {
        unsigned long  s1_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S1对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S1_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S1_VBIAS_AT1_s1_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S1_VBIAS_AT1_s1_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S2_VBIAS_AT1_UNION
 结构说明  : RF_8S_S2_VBIAS_AT1 寄存器结构定义。地址偏移量:0x544，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s2_vbias_at1_reg;
    struct
    {
        unsigned long  s2_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S2对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S2_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S2_VBIAS_AT1_s2_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S2_VBIAS_AT1_s2_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S3_VBIAS_AT1_UNION
 结构说明  : RF_8S_S3_VBIAS_AT1 寄存器结构定义。地址偏移量:0x548，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s3_vbias_at1_reg;
    struct
    {
        unsigned long  s3_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S3对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S3_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S3_VBIAS_AT1_s3_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S3_VBIAS_AT1_s3_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S4_VBIAS_AT1_UNION
 结构说明  : RF_8S_S4_VBIAS_AT1 寄存器结构定义。地址偏移量:0x54C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s4_vbias_at1_reg;
    struct
    {
        unsigned long  s4_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S4对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S4_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S4_VBIAS_AT1_s4_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S4_VBIAS_AT1_s4_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S5_VBIAS_AT1_UNION
 结构说明  : RF_8S_S5_VBIAS_AT1 寄存器结构定义。地址偏移量:0x550，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s5_vbias_at1_reg;
    struct
    {
        unsigned long  s5_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S5对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S5_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S5_VBIAS_AT1_s5_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S5_VBIAS_AT1_s5_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S6_VBIAS_AT1_UNION
 结构说明  : RF_8S_S6_VBIAS_AT1 寄存器结构定义。地址偏移量:0x554，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s6_vbias_at1_reg;
    struct
    {
        unsigned long  s6_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S6对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S6_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S6_VBIAS_AT1_s6_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S6_VBIAS_AT1_s6_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S7_VBIAS_AT1_UNION
 结构说明  : RF_8S_S7_VBIAS_AT1 寄存器结构定义。地址偏移量:0x558，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s7_vbias_at1_reg;
    struct
    {
        unsigned long  s7_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S7对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S7_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S7_VBIAS_AT1_s7_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S7_VBIAS_AT1_s7_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S8_VBIAS_AT1_UNION
 结构说明  : RF_8S_S8_VBIAS_AT1 寄存器结构定义。地址偏移量:0x55C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s8_vbias_at1_reg;
    struct
    {
        unsigned long  s8_8s_vbias_at1 : 24; /* bit[0-23] : 主天线非BLOCK下S8对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S8_VBIAS_AT1_UNION;
#define WBBP_RF_8S_S8_VBIAS_AT1_s8_8s_vbias_at1_START  (0)
#define WBBP_RF_8S_S8_VBIAS_AT1_s8_8s_vbias_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S1_VBIAS_AT2_UNION
 结构说明  : RF_8S_S1_VBIAS_AT2 寄存器结构定义。地址偏移量:0x560，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s1_vbias_at2_reg;
    struct
    {
        unsigned long  s1_8s_vbias_at2 : 24; /* bit[0-23] : 主天线非BLOCK下S1对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S1_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S1_VBIAS_AT2_s1_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S1_VBIAS_AT2_s1_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S2_VBIAS_AT2_UNION
 结构说明  : RF_8S_S2_VBIAS_AT2 寄存器结构定义。地址偏移量:0x564，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s2_vbias_at2_reg;
    struct
    {
        unsigned long  s2_8s_vbias_at2 : 24; /* bit[0-23] : 辅天线非BLOCK下S2对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S2_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S2_VBIAS_AT2_s2_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S2_VBIAS_AT2_s2_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S3_VBIAS_AT2_UNION
 结构说明  : RF_8S_S3_VBIAS_AT2 寄存器结构定义。地址偏移量:0x568，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s3_vbias_at2_reg;
    struct
    {
        unsigned long  s3_8s_vbias_at2 : 24; /* bit[0-23] : 辅天线非BLOCK下S3对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S3_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S3_VBIAS_AT2_s3_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S3_VBIAS_AT2_s3_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S4_VBIAS_AT2_UNION
 结构说明  : RF_8S_S4_VBIAS_AT2 寄存器结构定义。地址偏移量:0x56C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s4_vbias_at2_reg;
    struct
    {
        unsigned long  s4_8s_vbias_at2 : 24; /* bit[0-23] : 辅天线非BLOCK下S4对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S4_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S4_VBIAS_AT2_s4_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S4_VBIAS_AT2_s4_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S5_VBIAS_AT2_UNION
 结构说明  : RF_8S_S5_VBIAS_AT2 寄存器结构定义。地址偏移量:0x570，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s5_vbias_at2_reg;
    struct
    {
        unsigned long  s5_8s_vbias_at2 : 24; /* bit[0-23] : 辅天线非BLOCK下S5对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S5_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S5_VBIAS_AT2_s5_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S5_VBIAS_AT2_s5_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S6_VBIAS_AT2_UNION
 结构说明  : RF_8S_S6_VBIAS_AT2 寄存器结构定义。地址偏移量:0x574，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s6_vbias_at2_reg;
    struct
    {
        unsigned long  s6_8s_vbias_at2 : 24; /* bit[0-23] : 辅天线非BLOCK下S6对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S6_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S6_VBIAS_AT2_s6_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S6_VBIAS_AT2_s6_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S7_VBIAS_AT2_UNION
 结构说明  : RF_8S_S7_VBIAS_AT2 寄存器结构定义。地址偏移量:0x578，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s7_vbias_at2_reg;
    struct
    {
        unsigned long  s7_8s_vbias_at2 : 24; /* bit[0-23] : 辅天线非BLOCK下S7对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S7_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S7_VBIAS_AT2_s7_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S7_VBIAS_AT2_s7_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_8S_S8_VBIAS_AT2_UNION
 结构说明  : RF_8S_S8_VBIAS_AT2 寄存器结构定义。地址偏移量:0x57C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_8s_s8_vbias_at2_reg;
    struct
    {
        unsigned long  s8_8s_vbias_at2 : 24; /* bit[0-23] : 辅天线非BLOCK下S8对应VBIAS控制字。
                                                            C模不配置。 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_RF_8S_S8_VBIAS_AT2_UNION;
#define WBBP_RF_8S_S8_VBIAS_AT2_s8_8s_vbias_at2_START  (0)
#define WBBP_RF_8S_S8_VBIAS_AT2_s8_8s_vbias_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S12_INTRA_AT1_UNION
 结构说明  : RF_5S_GAIN_S12_INTRA_AT1 寄存器结构定义。地址偏移量:0x830，初值:0x018801D0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s12_intra_at1_reg;
    struct
    {
        unsigned long  s1_5s_rf_gain_intra_at1 : 12; /* bit[0-11] : 五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s2_5s_rf_gain_intra_at1 : 12; /* bit[16-27]: 五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S12_INTRA_AT1_UNION;
#define WBBP_RF_5S_GAIN_S12_INTRA_AT1_s1_5s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_5S_GAIN_S12_INTRA_AT1_s1_5s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_5S_GAIN_S12_INTRA_AT1_s2_5s_rf_gain_intra_at1_START  (16)
#define WBBP_RF_5S_GAIN_S12_INTRA_AT1_s2_5s_rf_gain_intra_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S34_INTRA_AT1_UNION
 结构说明  : RF_5S_GAIN_S34_INTRA_AT1 寄存器结构定义。地址偏移量:0x834，初值:0x00C80128，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s34_intra_at1_reg;
    struct
    {
        unsigned long  s3_5s_rf_gain_intra_at1 : 12; /* bit[0-11] : 五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s4_5s_rf_gain_intra_at1 : 12; /* bit[16-27]: 五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S34_INTRA_AT1_UNION;
#define WBBP_RF_5S_GAIN_S34_INTRA_AT1_s3_5s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_5S_GAIN_S34_INTRA_AT1_s3_5s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_5S_GAIN_S34_INTRA_AT1_s4_5s_rf_gain_intra_at1_START  (16)
#define WBBP_RF_5S_GAIN_S34_INTRA_AT1_s4_5s_rf_gain_intra_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_UNION
 结构说明  : RF_5S_GAIN_S51_INTRA_AT1_AT2 寄存器结构定义。地址偏移量:0x838，初值:0x01D00050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s51_intra_at1_at2_reg;
    struct
    {
        unsigned long  s5_5s_rf_gain_intra_at1 : 12; /* bit[0-11] : 五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s1_5s_rf_gain_intra_at2 : 12; /* bit[16-27]: 五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_UNION;
#define WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_s5_5s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_s5_5s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_s1_5s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_5S_GAIN_S51_INTRA_AT1_AT2_s1_5s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S23_INTRA_AT2_UNION
 结构说明  : RF_5S_GAIN_S23_INTRA_AT2 寄存器结构定义。地址偏移量:0x83C，初值:0x01280188，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s23_intra_at2_reg;
    struct
    {
        unsigned long  s2_5s_rf_gain_intra_at2 : 12; /* bit[0-11] : 五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s3_5s_rf_gain_intra_at2 : 12; /* bit[16-27]: 五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S23_INTRA_AT2_UNION;
#define WBBP_RF_5S_GAIN_S23_INTRA_AT2_s2_5s_rf_gain_intra_at2_START  (0)
#define WBBP_RF_5S_GAIN_S23_INTRA_AT2_s2_5s_rf_gain_intra_at2_END    (11)
#define WBBP_RF_5S_GAIN_S23_INTRA_AT2_s3_5s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_5S_GAIN_S23_INTRA_AT2_s3_5s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S45_INTRA_AT2_UNION
 结构说明  : RF_5S_GAIN_S45_INTRA_AT2 寄存器结构定义。地址偏移量:0x840，初值:0x005000C8，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s45_intra_at2_reg;
    struct
    {
        unsigned long  s4_5s_rf_gain_intra_at2 : 12; /* bit[0-11] : 五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s5_5s_rf_gain_intra_at2 : 12; /* bit[16-27]: 五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S45_INTRA_AT2_UNION;
#define WBBP_RF_5S_GAIN_S45_INTRA_AT2_s4_5s_rf_gain_intra_at2_START  (0)
#define WBBP_RF_5S_GAIN_S45_INTRA_AT2_s4_5s_rf_gain_intra_at2_END    (11)
#define WBBP_RF_5S_GAIN_S45_INTRA_AT2_s5_5s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_5S_GAIN_S45_INTRA_AT2_s5_5s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S12_INTER_AT1_UNION
 结构说明  : RF_5S_GAIN_S12_INTER_AT1 寄存器结构定义。地址偏移量:0x844，初值:0x018801D0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s12_inter_at1_reg;
    struct
    {
        unsigned long  s1_5s_rf_gain_inter_at1 : 12; /* bit[0-11] : 五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s2_5s_rf_gain_inter_at1 : 12; /* bit[16-27]: 五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S12_INTER_AT1_UNION;
#define WBBP_RF_5S_GAIN_S12_INTER_AT1_s1_5s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_5S_GAIN_S12_INTER_AT1_s1_5s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_5S_GAIN_S12_INTER_AT1_s2_5s_rf_gain_inter_at1_START  (16)
#define WBBP_RF_5S_GAIN_S12_INTER_AT1_s2_5s_rf_gain_inter_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S34_INTER_AT1_UNION
 结构说明  : RF_5S_GAIN_S34_INTER_AT1 寄存器结构定义。地址偏移量:0x848，初值:0x00C80128，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s34_inter_at1_reg;
    struct
    {
        unsigned long  s3_5s_rf_gain_inter_at1 : 12; /* bit[0-11] : 五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s4_5s_rf_gain_inter_at1 : 12; /* bit[16-27]: 五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S34_INTER_AT1_UNION;
#define WBBP_RF_5S_GAIN_S34_INTER_AT1_s3_5s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_5S_GAIN_S34_INTER_AT1_s3_5s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_5S_GAIN_S34_INTER_AT1_s4_5s_rf_gain_inter_at1_START  (16)
#define WBBP_RF_5S_GAIN_S34_INTER_AT1_s4_5s_rf_gain_inter_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_UNION
 结构说明  : RF_5S_GAIN_S51_INTER_AT1_AT2 寄存器结构定义。地址偏移量:0x84C，初值:0x01D00050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s51_inter_at1_at2_reg;
    struct
    {
        unsigned long  s5_5s_rf_gain_inter_at1 : 12; /* bit[0-11] : 五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s1_5s_rf_gain_inter_at2 : 12; /* bit[16-27]: 五档AAGC S1（RF RSSI为-102~-90dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_UNION;
#define WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_s5_5s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_s5_5s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_s1_5s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_5S_GAIN_S51_INTER_AT1_AT2_s1_5s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S23_INTER_AT2_UNION
 结构说明  : RF_5S_GAIN_S23_INTER_AT2 寄存器结构定义。地址偏移量:0x850，初值:0x01280188，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s23_inter_at2_reg;
    struct
    {
        unsigned long  s2_5s_rf_gain_inter_at2 : 12; /* bit[0-11] : 五档AAGC S2（RF RSSI为-87~-69dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s3_5s_rf_gain_inter_at2 : 12; /* bit[16-27]: 五档AAGC S3（RF RSSI为-66~-54dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S23_INTER_AT2_UNION;
#define WBBP_RF_5S_GAIN_S23_INTER_AT2_s2_5s_rf_gain_inter_at2_START  (0)
#define WBBP_RF_5S_GAIN_S23_INTER_AT2_s2_5s_rf_gain_inter_at2_END    (11)
#define WBBP_RF_5S_GAIN_S23_INTER_AT2_s3_5s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_5S_GAIN_S23_INTER_AT2_s3_5s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S45_INTER_AT2_UNION
 结构说明  : RF_5S_GAIN_S45_INTER_AT2 寄存器结构定义。地址偏移量:0x854，初值:0x005000C8，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s45_inter_at2_reg;
    struct
    {
        unsigned long  s4_5s_rf_gain_inter_at2 : 12; /* bit[0-11] : 五档AAGC S4（RF RSSI为-51~-39dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s5_5s_rf_gain_inter_at2 : 12; /* bit[16-27]: 五档AAGC S5（RF RSSI为-36~-21dBm）状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S45_INTER_AT2_UNION;
#define WBBP_RF_5S_GAIN_S45_INTER_AT2_s4_5s_rf_gain_inter_at2_START  (0)
#define WBBP_RF_5S_GAIN_S45_INTER_AT2_s4_5s_rf_gain_inter_at2_END    (11)
#define WBBP_RF_5S_GAIN_S45_INTER_AT2_s5_5s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_5S_GAIN_S45_INTER_AT2_s5_5s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_DRSSI_OVER_CTRL_AT1_UNION
 结构说明  : DRSSI_OVER_CTRL_AT1 寄存器结构定义。地址偏移量:0x858，初值:0x0070C8FF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drssi_over_ctrl_at1_reg;
    struct
    {
        unsigned long  dsp_drssi_over_win_length_at1 : 8;  /* bit[0-7]  : 八档AAGC DRSSI门限判断周期，单位为DRSSI统计周期。
                                                                          AGC在RF_SC/RF_DC可以分时共用。
                                                                          C模不配置。 */
        unsigned long  dsp_drssi_over_num_at1        : 8;  /* bit[8-15] : 八档AAGC DRSSI门限迟滞次数。
                                                                          AGC在RF_SC/RF_DC可以分时共用。
                                                                          C模不配置。 */
        unsigned long  dsp_drssi_over_threshold_at1  : 10; /* bit[16-25]: 八档AAGC DRSSI迟滞门限。
                                                                          AGC在RF_SC/RF_DC可以分时共用。
                                                                          C模不配置。 */
        unsigned long  reserved                      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_DRSSI_OVER_CTRL_AT1_UNION;
#define WBBP_DRSSI_OVER_CTRL_AT1_dsp_drssi_over_win_length_at1_START  (0)
#define WBBP_DRSSI_OVER_CTRL_AT1_dsp_drssi_over_win_length_at1_END    (7)
#define WBBP_DRSSI_OVER_CTRL_AT1_dsp_drssi_over_num_at1_START         (8)
#define WBBP_DRSSI_OVER_CTRL_AT1_dsp_drssi_over_num_at1_END           (15)
#define WBBP_DRSSI_OVER_CTRL_AT1_dsp_drssi_over_threshold_at1_START   (16)
#define WBBP_DRSSI_OVER_CTRL_AT1_dsp_drssi_over_threshold_at1_END     (25)


/*****************************************************************************
 结构名    : WBBP_DRSSI_OVER_CTRL_AT2_UNION
 结构说明  : DRSSI_OVER_CTRL_AT2 寄存器结构定义。地址偏移量:0x85C，初值:0x0070C8FF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drssi_over_ctrl_at2_reg;
    struct
    {
        unsigned long  dsp_drssi_over_win_length_at2 : 8;  /* bit[0-7]  : 八档AAGC DRSSI门限判断周期，单位为DRSSI统计周期。
                                                                          AGC在RF_SC/RF_DC可以分时共用。
                                                                          C模不配置。 */
        unsigned long  dsp_drssi_over_num_at2        : 8;  /* bit[8-15] : 八档AAGC DRSSI门限迟滞次数。
                                                                          AGC在RF_SC/RF_DC可以分时共用。
                                                                          C模不配置。 */
        unsigned long  dsp_drssi_over_threshold_at2  : 10; /* bit[16-25]: 八档AAGC DRSSI迟滞门限。
                                                                          AGC在RF_SC/RF_DC可以分时共用。
                                                                          C模不配置。 */
        unsigned long  reserved                      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_DRSSI_OVER_CTRL_AT2_UNION;
#define WBBP_DRSSI_OVER_CTRL_AT2_dsp_drssi_over_win_length_at2_START  (0)
#define WBBP_DRSSI_OVER_CTRL_AT2_dsp_drssi_over_win_length_at2_END    (7)
#define WBBP_DRSSI_OVER_CTRL_AT2_dsp_drssi_over_num_at2_START         (8)
#define WBBP_DRSSI_OVER_CTRL_AT2_dsp_drssi_over_num_at2_END           (15)
#define WBBP_DRSSI_OVER_CTRL_AT2_dsp_drssi_over_threshold_at2_START   (16)
#define WBBP_DRSSI_OVER_CTRL_AT2_dsp_drssi_over_threshold_at2_END     (25)


/*****************************************************************************
 结构名    : WBBP_AAGC_STATE_SEL_UNION
 结构说明  : AAGC_STATE_SEL 寄存器结构定义。地址偏移量:0x860，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_state_sel_reg;
    struct
    {
        unsigned long  dsp_aagc_state_sel : 2;  /* bit[0-1] : AAGC状态机选择。0，4阶LPF使用五档状态机，2阶LPF使用八档状态机；1，固定使用五档状态机；2，固定使用八档状态机。
                                                              C模不配置。 */
        unsigned long  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_AAGC_STATE_SEL_UNION;
#define WBBP_AAGC_STATE_SEL_dsp_aagc_state_sel_START  (0)
#define WBBP_AAGC_STATE_SEL_dsp_aagc_state_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_SPUR_REMOVE_EN_UNION
 结构说明  : SPUR_REMOVE_EN 寄存器结构定义。地址偏移量:0x868，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      spur_remove_en_reg;
    struct
    {
        unsigned long  dsp_spur_remove_at1_en   : 1;  /* bit[0]   : 主集谐波干扰消除使能，高电平有效。 */
        unsigned long  dsp_remove_allrun_at1_en : 1;  /* bit[1]   : 在软件使能dsp_spur_remove_at1_en有效时，主集始终进行谐波干扰消除的使能信号。此时与档位、RSSI值、本频标志等其他条件无关。1，表示始终进行谐波干扰消除；0，表示由其他条件决定。主要用于调试。 */
        unsigned long  reserved_0               : 2;  /* bit[2-3] : 保留 */
        unsigned long  dsp_spur_remove_at2_en   : 1;  /* bit[4]   : 分集谐波干扰消除使能，高电平有效。 */
        unsigned long  dsp_remove_allrun_at2_en : 1;  /* bit[5]   : 在软件使能dsp_spur_remove_at1_en有效时，分集始终进行谐波干扰消除的使能信号。此时与档位、RSSI值、本频标志等其他条件无关。1，表示始终进行谐波干扰消除；0，表示由其他条件决定。主要用于调试。 */
        unsigned long  reserved_1               : 26; /* bit[6-31]: 保留 */
    } reg;
} WBBP_SPUR_REMOVE_EN_UNION;
#define WBBP_SPUR_REMOVE_EN_dsp_spur_remove_at1_en_START    (0)
#define WBBP_SPUR_REMOVE_EN_dsp_spur_remove_at1_en_END      (0)
#define WBBP_SPUR_REMOVE_EN_dsp_remove_allrun_at1_en_START  (1)
#define WBBP_SPUR_REMOVE_EN_dsp_remove_allrun_at1_en_END    (1)
#define WBBP_SPUR_REMOVE_EN_dsp_spur_remove_at2_en_START    (4)
#define WBBP_SPUR_REMOVE_EN_dsp_spur_remove_at2_en_END      (4)
#define WBBP_SPUR_REMOVE_EN_dsp_remove_allrun_at2_en_START  (5)
#define WBBP_SPUR_REMOVE_EN_dsp_remove_allrun_at2_en_END    (5)


/*****************************************************************************
 结构名    : WBBP_SPUR_CFG_UNION
 结构说明  : SPUR_CFG 寄存器结构定义。地址偏移量:0x86C，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      spur_cfg_reg;
    struct
    {
        unsigned long  dsp_spur_freq           : 9;  /* bit[0-8]  : 主集和分集共用的谐波干扰信号相对于20kHz的频率倍数，有符号数补码表示。取值范围-118~-1、1~118。默认配置1。 */
        unsigned long  reserved_0              : 7;  /* bit[9-15] : 保留 */
        unsigned long  dsp_rssi_threshold_spur : 11; /* bit[16-26]: 主集和分集共用的RSSI门限值。当RSSI值小于该门限值时，进行谐波干扰消除。 */
        unsigned long  reserved_1              : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_SPUR_CFG_UNION;
#define WBBP_SPUR_CFG_dsp_spur_freq_START            (0)
#define WBBP_SPUR_CFG_dsp_spur_freq_END              (8)
#define WBBP_SPUR_CFG_dsp_rssi_threshold_spur_START  (16)
#define WBBP_SPUR_CFG_dsp_rssi_threshold_spur_END    (26)


/*****************************************************************************
 结构名    : WBBP_AT1_SPUR_REMOVED_DSP_UNION
 结构说明  : AT1_SPUR_REMOVED_DSP 寄存器结构定义。地址偏移量:0x870，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      at1_spur_removed_dsp_reg;
    struct
    {
        unsigned long  at1_removed_i_dsp : 9;  /* bit[0-8]  : 主集上报谐波干扰消除值实部，用于调试。 */
        unsigned long  reserved_0        : 7;  /* bit[9-15] : 保留 */
        unsigned long  at1_removed_q_dsp : 9;  /* bit[16-24]: 主集上报谐波干扰消除值虚部，用于调试。 */
        unsigned long  reserved_1        : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_AT1_SPUR_REMOVED_DSP_UNION;
#define WBBP_AT1_SPUR_REMOVED_DSP_at1_removed_i_dsp_START  (0)
#define WBBP_AT1_SPUR_REMOVED_DSP_at1_removed_i_dsp_END    (8)
#define WBBP_AT1_SPUR_REMOVED_DSP_at1_removed_q_dsp_START  (16)
#define WBBP_AT1_SPUR_REMOVED_DSP_at1_removed_q_dsp_END    (24)


/*****************************************************************************
 结构名    : WBBP_AT2_SPUR_REMOVED_DSP_UNION
 结构说明  : AT2_SPUR_REMOVED_DSP 寄存器结构定义。地址偏移量:0x874，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      at2_spur_removed_dsp_reg;
    struct
    {
        unsigned long  at2_removed_i_dsp : 9;  /* bit[0-8]  : 分集上报谐波干扰消除值实部，用于调试。 */
        unsigned long  reserved_0        : 7;  /* bit[9-15] : 保留 */
        unsigned long  at2_removed_q_dsp : 9;  /* bit[16-24]: 分集上报谐波干扰消除值虚部，用于调试。 */
        unsigned long  reserved_1        : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_AT2_SPUR_REMOVED_DSP_UNION;
#define WBBP_AT2_SPUR_REMOVED_DSP_at2_removed_i_dsp_START  (0)
#define WBBP_AT2_SPUR_REMOVED_DSP_at2_removed_i_dsp_END    (8)
#define WBBP_AT2_SPUR_REMOVED_DSP_at2_removed_q_dsp_START  (16)
#define WBBP_AT2_SPUR_REMOVED_DSP_at2_removed_q_dsp_END    (24)


/*****************************************************************************
 结构名    : WBBP_S8_5S_RF_CTRL_AT2_UNION
 结构说明  : S8_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0x878，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s8_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s8_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S8状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S8_5S_RF_CTRL_AT2_UNION;
#define WBBP_S8_5S_RF_CTRL_AT2_s8_5s_rf_ctrl_at2_START  (0)
#define WBBP_S8_5S_RF_CTRL_AT2_s8_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_IQ_AK_PK_INIT_CFG_AT1_UNION
 结构说明  : IQ_AK_PK_INIT_CFG_AT1 寄存器结构定义。地址偏移量:0xA00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_ak_pk_init_cfg_at1_reg;
    struct
    {
        unsigned long  dsp_init_iq_ak_at1 : 10; /* bit[0-9]  : 刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
                                                               说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_init_iq_pk_at1 : 11; /* bit[16-26]: 刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
                                                               说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_IQ_AK_PK_INIT_CFG_AT1_UNION;
#define WBBP_IQ_AK_PK_INIT_CFG_AT1_dsp_init_iq_ak_at1_START  (0)
#define WBBP_IQ_AK_PK_INIT_CFG_AT1_dsp_init_iq_ak_at1_END    (9)
#define WBBP_IQ_AK_PK_INIT_CFG_AT1_dsp_init_iq_pk_at1_START  (16)
#define WBBP_IQ_AK_PK_INIT_CFG_AT1_dsp_init_iq_pk_at1_END    (26)


/*****************************************************************************
 结构名    : WBBP_IQ_AK_PK_INIT_CFG_AT2_UNION
 结构说明  : IQ_AK_PK_INIT_CFG_AT2 寄存器结构定义。地址偏移量:0xA04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iq_ak_pk_init_cfg_at2_reg;
    struct
    {
        unsigned long  dsp_init_iq_ak_at2 : 10; /* bit[0-9]  : 刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
                                                               说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_init_iq_pk_at2 : 11; /* bit[16-26]: 刚刚打开AGC时，BBP使用此值进行IQ Mismatch校正。
                                                               说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_IQ_AK_PK_INIT_CFG_AT2_UNION;
#define WBBP_IQ_AK_PK_INIT_CFG_AT2_dsp_init_iq_ak_at2_START  (0)
#define WBBP_IQ_AK_PK_INIT_CFG_AT2_dsp_init_iq_ak_at2_END    (9)
#define WBBP_IQ_AK_PK_INIT_CFG_AT2_dsp_init_iq_pk_at2_START  (16)
#define WBBP_IQ_AK_PK_INIT_CFG_AT2_dsp_init_iq_pk_at2_END    (26)


/*****************************************************************************
 结构名    : WBBP_HSDPA_DC_CFG_UNION
 结构说明  : HSDPA_DC_CFG 寄存器结构定义。地址偏移量:0xA08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hsdpa_dc_cfg_reg;
    struct
    {
        unsigned long  dsp_wagc_cell_sel : 1;  /* bit[0]    : 下变频模块输出主辅载波信号位置选择，使主载波落在cell1上。0，主载波在低频点；1，主载波在高频点。
                                                              C模不配置。 */
        unsigned long  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned long  dsp_wagc_nco_en   : 1;  /* bit[4]    : NCO模块使能，高电平有效。
                                                              C模不配置。 */
        unsigned long  reserved_1        : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dsp_ph_acc_clr_en : 1;  /* bit[8]    : NCO相位清零脉冲。
                                                              C模不配置。 */
        unsigned long  reserved_2        : 3;  /* bit[9-11] : 保留 */
        unsigned long  dsp_dl_dc_en      : 1;  /* bit[12]   : AGC所处RF_SC/RF_DC工作状态。0，RF_SC；1，RF_DC。
                                                              C模不配置。 */
        unsigned long  reserved_3        : 19; /* bit[13-31]: 保留 */
    } reg;
} WBBP_HSDPA_DC_CFG_UNION;
#define WBBP_HSDPA_DC_CFG_dsp_wagc_cell_sel_START  (0)
#define WBBP_HSDPA_DC_CFG_dsp_wagc_cell_sel_END    (0)
#define WBBP_HSDPA_DC_CFG_dsp_wagc_nco_en_START    (4)
#define WBBP_HSDPA_DC_CFG_dsp_wagc_nco_en_END      (4)
#define WBBP_HSDPA_DC_CFG_dsp_ph_acc_clr_en_START  (8)
#define WBBP_HSDPA_DC_CFG_dsp_ph_acc_clr_en_END    (8)
#define WBBP_HSDPA_DC_CFG_dsp_dl_dc_en_START       (12)
#define WBBP_HSDPA_DC_CFG_dsp_dl_dc_en_END         (12)


/*****************************************************************************
 结构名    : WBBP_WAGC_IQ_DLY_CTRL_UNION
 结构说明  : WAGC_IQ_DLY_CTRL 寄存器结构定义。地址偏移量:0xA18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_iq_dly_ctrl_reg;
    struct
    {
        unsigned long  dsp_sc_nblk_dly_sel : 2;  /* bit[0-1]  : RF_SC非Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
                                                                C模不配置。 */
        unsigned long  reserved_0          : 2;  /* bit[2-3]  : 保留 */
        unsigned long  dsp_sc_blk_dly_sel  : 2;  /* bit[4-5]  : RF_SC Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
                                                                C模不配置。 */
        unsigned long  reserved_1          : 2;  /* bit[6-7]  : 保留 */
        unsigned long  dsp_dc_nblk_dly_sel : 2;  /* bit[8-9]  : RF_DC非Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
                                                                C模不配置。 */
        unsigned long  reserved_2          : 2;  /* bit[10-11]: 保留 */
        unsigned long  dsp_dc_blk_dly_sel  : 2;  /* bit[12-13]: RF_DC Block下射频通道数字域1/4chip延时。2'd0，延时0/4chip；2'd1，延时1/4chip；2'd2，延时2/4chip；2'd3，延时3/4chip。
                                                                C模不配置。 */
        unsigned long  reserved_3          : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_WAGC_IQ_DLY_CTRL_UNION;
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_sc_nblk_dly_sel_START  (0)
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_sc_nblk_dly_sel_END    (1)
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_sc_blk_dly_sel_START   (4)
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_sc_blk_dly_sel_END     (5)
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_dc_nblk_dly_sel_START  (8)
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_dc_nblk_dly_sel_END    (9)
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_dc_blk_dly_sel_START   (12)
#define WBBP_WAGC_IQ_DLY_CTRL_dsp_dc_blk_dly_sel_END     (13)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG0_AT1_UNION
 结构说明  : INIT_SCDC_AGC_CFG0_AT1 寄存器结构定义。地址偏移量:0xA1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg0_at1_reg;
    struct
    {
        unsigned long  dsp_scdc_rssi_rf_at1  : 11; /* bit[0-10] : RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
                                                                  C模不配置。 */
        unsigned long  reserved_0            : 13; /* bit[11-23]: 保留 */
        unsigned long  dsp_scdc_5s_state_at1 : 3;  /* bit[24-26]: RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF五档增益控制。
                                                                  C模不配置。 */
        unsigned long  reserved_1            : 1;  /* bit[27]   : 保留 */
        unsigned long  dsp_scdc_8s_state_at1 : 3;  /* bit[28-30]: RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF八档增益控制。
                                                                  C模不配置。 */
        unsigned long  reserved_2            : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG0_AT1_UNION;
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_dsp_scdc_rssi_rf_at1_START   (0)
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_dsp_scdc_rssi_rf_at1_END     (10)
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_dsp_scdc_5s_state_at1_START  (24)
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_dsp_scdc_5s_state_at1_END    (26)
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_dsp_scdc_8s_state_at1_START  (28)
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_dsp_scdc_8s_state_at1_END    (30)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG1_AT1_UNION
 结构说明  : INIT_SCDC_AGC_CFG1_AT1 寄存器结构定义。地址偏移量:0xA20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg1_at1_reg;
    struct
    {
        unsigned long  dsp_scdc_drssi_at1            : 9;  /* bit[0-8]  : RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                          C模不配置。 */
        unsigned long  reserved_0                    : 7;  /* bit[9-15] : 保留 */
        unsigned long  dsp_init_scdc_rssi_en_at1     : 1;  /* bit[16]   : RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  reserved_1                    : 3;  /* bit[17-19]: 保留 */
        unsigned long  dsp_init_scdc_5s_state_en_at1 : 1;  /* bit[20]   : RF_SC/RF_DC切换刚刚完成时，DSP配置五档状态机初始值使能。1，DSP配置五档状态机初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  dsp_init_scdc_8s_state_en_at1 : 1;  /* bit[21]   : RF_SC/RF_DC切换刚刚完成时，DSP配置八档状态机初始值使能。1，DSP配置八档状态机初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  reserved_2                    : 2;  /* bit[22-23]: 保留 */
        unsigned long  dsp_init_scdc_drssi_en_at1    : 1;  /* bit[24]   : 刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  reserved_3                    : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG1_AT1_UNION;
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_scdc_drssi_at1_START             (0)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_scdc_drssi_at1_END               (8)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_rssi_en_at1_START      (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_rssi_en_at1_END        (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_5s_state_en_at1_START  (20)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_5s_state_en_at1_END    (20)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_8s_state_en_at1_START  (21)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_8s_state_en_at1_END    (21)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_drssi_en_at1_START     (24)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_dsp_init_scdc_drssi_en_at1_END       (24)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG0_AT2_UNION
 结构说明  : INIT_SCDC_AGC_CFG0_AT2 寄存器结构定义。地址偏移量:0xA24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg0_at2_reg;
    struct
    {
        unsigned long  dsp_scdc_rssi_rf_at2  : 11; /* bit[0-10] : RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。
                                                                  C模不配置。 */
        unsigned long  reserved_0            : 13; /* bit[11-23]: 保留 */
        unsigned long  dsp_scdc_5s_state_at2 : 3;  /* bit[24-26]: RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF五档增益控制。
                                                                  C模不配置。 */
        unsigned long  reserved_1            : 1;  /* bit[27]   : 保留 */
        unsigned long  dsp_scdc_8s_state_at2 : 3;  /* bit[28-30]: RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行自研RF八档增益控制。
                                                                  C模不配置。 */
        unsigned long  reserved_2            : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG0_AT2_UNION;
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_dsp_scdc_rssi_rf_at2_START   (0)
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_dsp_scdc_rssi_rf_at2_END     (10)
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_dsp_scdc_5s_state_at2_START  (24)
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_dsp_scdc_5s_state_at2_END    (26)
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_dsp_scdc_8s_state_at2_START  (28)
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_dsp_scdc_8s_state_at2_END    (30)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG1_AT2_UNION
 结构说明  : INIT_SCDC_AGC_CFG1_AT2 寄存器结构定义。地址偏移量:0xA28，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg1_at2_reg;
    struct
    {
        unsigned long  dsp_scdc_drssi_at2            : 9;  /* bit[0-8]  : RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                          C模不配置。 */
        unsigned long  reserved_0                    : 7;  /* bit[9-15] : 保留 */
        unsigned long  dsp_init_scdc_rssi_en_at2     : 1;  /* bit[16]   : RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  reserved_1                    : 3;  /* bit[17-19]: 保留 */
        unsigned long  dsp_init_scdc_5s_state_en_at2 : 1;  /* bit[20]   : RF_SC/RF_DC切换刚刚完成时，DSP配置五档状态机初始值使能。1，DSP配置五档状态机初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  dsp_init_scdc_8s_state_en_at2 : 1;  /* bit[21]   : RF_SC/RF_DC切换刚刚完成时，DSP配置八档状态机初始值使能。1，DSP配置八档状态机初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  reserved_2                    : 2;  /* bit[22-23]: 保留 */
        unsigned long  dsp_init_scdc_drssi_en_at2    : 1;  /* bit[24]   : 刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。
                                                                          C模不配置。 */
        unsigned long  reserved_3                    : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG1_AT2_UNION;
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_scdc_drssi_at2_START             (0)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_scdc_drssi_at2_END               (8)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_rssi_en_at2_START      (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_rssi_en_at2_END        (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_5s_state_en_at2_START  (20)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_5s_state_en_at2_END    (20)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_8s_state_en_at2_START  (21)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_8s_state_en_at2_END    (21)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_drssi_en_at2_START     (24)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_dsp_init_scdc_drssi_en_at2_END       (24)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_RPT_CELL_AT1_UNION
 结构说明  : INIT_AGC_RPT_CELL_AT1 寄存器结构定义。地址偏移量:0xA2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_rpt_cell_at1_reg;
    struct
    {
        unsigned long  dsp_rpt_cell_drssi_25db_at1 : 9;  /* bit[0-8]  : BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
                                                                        说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_cell_rssi_rf_at1    : 11; /* bit[9-19] : BBP上报天线口RSSI值（单载波），0.125dB精度。
                                                                        说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  reserved                    : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_RPT_CELL_AT1_UNION;
#define WBBP_INIT_AGC_RPT_CELL_AT1_dsp_rpt_cell_drssi_25db_at1_START  (0)
#define WBBP_INIT_AGC_RPT_CELL_AT1_dsp_rpt_cell_drssi_25db_at1_END    (8)
#define WBBP_INIT_AGC_RPT_CELL_AT1_dsp_rpt_cell_rssi_rf_at1_START     (9)
#define WBBP_INIT_AGC_RPT_CELL_AT1_dsp_rpt_cell_rssi_rf_at1_END       (19)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_RPT_CELL_AT2_UNION
 结构说明  : INIT_AGC_RPT_CELL_AT2 寄存器结构定义。地址偏移量:0xA30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_rpt_cell_at2_reg;
    struct
    {
        unsigned long  dsp_rpt_cell_drssi_25db_at2 : 9;  /* bit[0-8]  : BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
                                                                        说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_cell_rssi_rf_at2    : 11; /* bit[9-19] : BBP上报天线口RSSI值（单载波），0.125dB精度。
                                                                        说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  reserved                    : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_RPT_CELL_AT2_UNION;
#define WBBP_INIT_AGC_RPT_CELL_AT2_dsp_rpt_cell_drssi_25db_at2_START  (0)
#define WBBP_INIT_AGC_RPT_CELL_AT2_dsp_rpt_cell_drssi_25db_at2_END    (8)
#define WBBP_INIT_AGC_RPT_CELL_AT2_dsp_rpt_cell_rssi_rf_at2_START     (9)
#define WBBP_INIT_AGC_RPT_CELL_AT2_dsp_rpt_cell_rssi_rf_at2_END       (19)


/*****************************************************************************
 结构名    : WBBP_SOFT_BLK_CFG_UNION
 结构说明  : SOFT_BLK_CFG 寄存器结构定义。地址偏移量:0xA34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      soft_blk_cfg_reg;
    struct
    {
        unsigned long  dsp_blk_start_cnt : 16; /* bit[0-15] : DSP通过配置该时间值，选择在哪一个定时中断读取ABB和BBP上报的用于软件Block判决的信号能量。
                                                              C模不配置。 */
        unsigned long  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} WBBP_SOFT_BLK_CFG_UNION;
#define WBBP_SOFT_BLK_CFG_dsp_blk_start_cnt_START  (0)
#define WBBP_SOFT_BLK_CFG_dsp_blk_start_cnt_END    (15)


/*****************************************************************************
 结构名    : WBBP_ABB_BLK_RPT_AT1_UNION
 结构说明  : ABB_BLK_RPT_AT1 寄存器结构定义。地址偏移量:0xA38，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_blk_rpt_at1_reg;
    struct
    {
        unsigned long  abb_drssi_valid_at1 : 1;  /* bit[0]    : DSP读取的ABB和BBP上报的用于软件Block判决的信号能量有效指示。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  wagc_blk_drssi_at1  : 9;  /* bit[4-12] : DSP读取的BBP上报的用于软件Block判决的信号能量。 */
        unsigned long  reserved_1          : 19; /* bit[13-31]: 保留 */
    } reg;
} WBBP_ABB_BLK_RPT_AT1_UNION;
#define WBBP_ABB_BLK_RPT_AT1_abb_drssi_valid_at1_START  (0)
#define WBBP_ABB_BLK_RPT_AT1_abb_drssi_valid_at1_END    (0)
#define WBBP_ABB_BLK_RPT_AT1_wagc_blk_drssi_at1_START   (4)
#define WBBP_ABB_BLK_RPT_AT1_wagc_blk_drssi_at1_END     (12)


/*****************************************************************************
 结构名    : WBBP_BLK_OUTPUT_UNION
 结构说明  : BLK_OUTPUT 寄存器结构定义。地址偏移量:0xA3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      blk_output_reg;
    struct
    {
        unsigned long  dsp_blk_spi_data    : 24; /* bit[0-23] : RF Block状态SPI控制字。
                                                                C模不配置。 */
        unsigned long  dsp_blk_spi_ind     : 1;  /* bit[24]   : RF Block状态SPI控制字触发脉冲。
                                                                C模不配置。 */
        unsigned long  reserved_0          : 3;  /* bit[25-27]: 保留 */
        unsigned long  dsp_blk_spi_ch_info : 2;  /* bit[28-29]: RF Block状态SPI控制字通道选择。
                                                                C模不配置。
                                                                00：选择ch0；
                                                                01：选择ch1；
                                                                10：选择ch2；
                                                                11：选择ch3； */
        unsigned long  reserved_1          : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_BLK_OUTPUT_UNION;
#define WBBP_BLK_OUTPUT_dsp_blk_spi_data_START     (0)
#define WBBP_BLK_OUTPUT_dsp_blk_spi_data_END       (23)
#define WBBP_BLK_OUTPUT_dsp_blk_spi_ind_START      (24)
#define WBBP_BLK_OUTPUT_dsp_blk_spi_ind_END        (24)
#define WBBP_BLK_OUTPUT_dsp_blk_spi_ch_info_START  (28)
#define WBBP_BLK_OUTPUT_dsp_blk_spi_ch_info_END    (29)


/*****************************************************************************
 结构名    : WBBP_ABB_BLK_RPT_AT2_UNION
 结构说明  : ABB_BLK_RPT_AT2 寄存器结构定义。地址偏移量:0xA40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_blk_rpt_at2_reg;
    struct
    {
        unsigned long  abb_drssi_valid_at2 : 1;  /* bit[0]    : DSP读取的ABB和BBP上报的用于软件Block判决的信号能量有效指示。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  wagc_blk_drssi_at2  : 9;  /* bit[4-12] : DSP读取的BBP上报的用于软件Block判决的信号能量。 */
        unsigned long  reserved_1          : 19; /* bit[13-31]: 保留 */
    } reg;
} WBBP_ABB_BLK_RPT_AT2_UNION;
#define WBBP_ABB_BLK_RPT_AT2_abb_drssi_valid_at2_START  (0)
#define WBBP_ABB_BLK_RPT_AT2_abb_drssi_valid_at2_END    (0)
#define WBBP_ABB_BLK_RPT_AT2_wagc_blk_drssi_at2_START   (4)
#define WBBP_ABB_BLK_RPT_AT2_wagc_blk_drssi_at2_END     (12)


/*****************************************************************************
 结构名    : WBBP_WAGC_CKG_BYPASS_UNION
 结构说明  : WAGC_CKG_BYPASS 寄存器结构定义。地址偏移量:0xA44，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_ckg_bypass_reg;
    struct
    {
        unsigned long  dsp_dlfe_ckg_bypass : 29; /* bit[0-28] : 时钟门控旁路寄存器。0，时钟门控使能；1，时钟门控旁路。
                                                                [0] 主天线spur remove模块，
                                                                [1] 主天线rxiq模块
                                                                [2] 主天线下变频模块
                                                                [3] 主天线scfilter模块
                                                                [4] 主天线W辅载波scfilter模块
                                                                [5] 主天线W辅载波其他模块
                                                                [6] 主天线RRC RSSI dcoc， 主辅天线公共base_cnt等模块
                                                                [7] 主天线W专用模块，WC共用模块
                                                                [8] 主天线TDS专用模块，fir和pdgt
                                                                [9] 主天线debug模块
                                                                [10] 主天线freq_error模块
                                                                [11] sc_cal模块（主辅天线公用）
                                                                [12] 主天线fifo模块读写时钟。
                                                                [13] 辅天线spur remove模块，
                                                                [14] 辅天线rxiq模块
                                                                [15] 辅天线下变频模块
                                                                [16] 辅天线scfilter模块
                                                                [17] 辅天线W辅载波scfilter模块
                                                                [18] 辅天线W辅载波其他模块
                                                                [19] 辅天线RRC RSSI dcoc 模块
                                                                [20] 辅天线W专用模块，WC共用模块
                                                                [21] 辅天线TDS专用模块，fir和pdgt
                                                                [22] 辅天线debug模块
                                                                [23] 辅天线freq_error模块
                                                                [24] reserved
                                                                [25] 辅天线fifo模块读写时钟。 */
        unsigned long  reserved            : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_WAGC_CKG_BYPASS_UNION;
#define WBBP_WAGC_CKG_BYPASS_dsp_dlfe_ckg_bypass_START  (0)
#define WBBP_WAGC_CKG_BYPASS_dsp_dlfe_ckg_bypass_END    (28)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CAL_RPT_AT1_UNION
 结构说明  : DC_STA_CAL_RPT_AT1 寄存器结构定义。地址偏移量:0xA48，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_cal_rpt_at1_reg;
    struct
    {
        unsigned long  sta_dc_cal_finish_cpu_at1 : 1;  /* bit[0]   : 天线1 RX静态DC校准相关测量模块运算完成标志。 */
        unsigned long  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_STA_CAL_RPT_AT1_UNION;
#define WBBP_DC_STA_CAL_RPT_AT1_sta_dc_cal_finish_cpu_at1_START  (0)
#define WBBP_DC_STA_CAL_RPT_AT1_sta_dc_cal_finish_cpu_at1_END    (0)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CAL_RPT_AT2_UNION
 结构说明  : DC_STA_CAL_RPT_AT2 寄存器结构定义。地址偏移量:0xA4C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_cal_rpt_at2_reg;
    struct
    {
        unsigned long  sta_dc_cal_finish_cpu_at2 : 1;  /* bit[0]   : 天线2 RX静态DC校准相关测量模块运算完成标志。 */
        unsigned long  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_STA_CAL_RPT_AT2_UNION;
#define WBBP_DC_STA_CAL_RPT_AT2_sta_dc_cal_finish_cpu_at2_START  (0)
#define WBBP_DC_STA_CAL_RPT_AT2_sta_dc_cal_finish_cpu_at2_END    (0)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CTRL0_AT1_UNION
 结构说明  : DC_STA_CRRO_CTRL0_AT1 寄存器结构定义。地址偏移量:0xA50，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_ctrl0_at1_reg;
    struct
    {
        unsigned long  dsp_sta_dc_cal_en_at1 : 1;  /* bit[0]   : 天线1配置DCR RX静态DC校准模式。
                                                                 1，DCR处于RX静态DC校准模式；0，DCR处于正常工作模式。 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CTRL0_AT1_UNION;
#define WBBP_DC_STA_CRRO_CTRL0_AT1_dsp_sta_dc_cal_en_at1_START  (0)
#define WBBP_DC_STA_CRRO_CTRL0_AT1_dsp_sta_dc_cal_en_at1_END    (0)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CTRL0_AT2_UNION
 结构说明  : DC_STA_CRRO_CTRL0_AT2 寄存器结构定义。地址偏移量:0xA54，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_ctrl0_at2_reg;
    struct
    {
        unsigned long  dsp_sta_dc_cal_en_at2 : 1;  /* bit[0]   : 天线2配置DCR RX静态DC校准模式。
                                                                 1，DCR处于RX静态DC校准模式；0，DCR处于正常工作模式。 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CTRL0_AT2_UNION;
#define WBBP_DC_STA_CRRO_CTRL0_AT2_dsp_sta_dc_cal_en_at2_START  (0)
#define WBBP_DC_STA_CRRO_CTRL0_AT2_dsp_sta_dc_cal_en_at2_END    (0)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CTRL1_AT1_UNION
 结构说明  : DC_STA_CRRO_CTRL1_AT1 寄存器结构定义。地址偏移量:0xA58，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_ctrl1_at1_reg;
    struct
    {
        unsigned long  dsp_sta_dc_cal_clr_at1 : 1;  /* bit[0]   : 天线1 RX静态DC校准相关测量模块完成标志清零脉冲。 */
        unsigned long  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CTRL1_AT1_UNION;
#define WBBP_DC_STA_CRRO_CTRL1_AT1_dsp_sta_dc_cal_clr_at1_START  (0)
#define WBBP_DC_STA_CRRO_CTRL1_AT1_dsp_sta_dc_cal_clr_at1_END    (0)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CTRL1_AT2_UNION
 结构说明  : DC_STA_CRRO_CTRL1_AT2 寄存器结构定义。地址偏移量:0xA5C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_ctrl1_at2_reg;
    struct
    {
        unsigned long  dsp_sta_dc_cal_clr_at2 : 1;  /* bit[0]   : 天线2 RX静态DC校准相关测量模块完成标志清零脉冲。 */
        unsigned long  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CTRL1_AT2_UNION;
#define WBBP_DC_STA_CRRO_CTRL1_AT2_dsp_sta_dc_cal_clr_at2_START  (0)
#define WBBP_DC_STA_CRRO_CTRL1_AT2_dsp_sta_dc_cal_clr_at2_END    (0)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S1_8S_AT1 寄存器结构定义。地址偏移量:0xA60，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s1_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s1_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态1时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT1_dsp_s1_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT1_dsp_s1_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S2_8S_AT1 寄存器结构定义。地址偏移量:0xA64，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s2_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s2_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态2时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT1_dsp_s2_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT1_dsp_s2_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S3_8S_AT1 寄存器结构定义。地址偏移量:0xA68，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s3_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s3_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态3时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT1_dsp_s3_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT1_dsp_s3_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S4_8S_AT1 寄存器结构定义。地址偏移量:0xA6C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s4_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s4_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态4时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT1_dsp_s4_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT1_dsp_s4_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S5_8S_AT1 寄存器结构定义。地址偏移量:0xA70，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s5_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s5_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态5时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT1_dsp_s5_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT1_dsp_s5_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S6_8S_AT1 寄存器结构定义。地址偏移量:0xA74，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s6_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s6_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态6时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT1_dsp_s6_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT1_dsp_s6_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S7_8S_AT1 寄存器结构定义。地址偏移量:0xA78，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s7_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s7_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态7时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT1_dsp_s7_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT1_dsp_s7_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S8_8S_AT1 寄存器结构定义。地址偏移量:0xA7C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s8_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s8_8s_dc_corr_intra_at1 : 24; /* bit[0-23] : 8档AGC状态8时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT1_dsp_s8_8s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT1_dsp_s8_8s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S1_5S_AT1 寄存器结构定义。地址偏移量:0xA80，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s1_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s1_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态1时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT1_dsp_s1_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT1_dsp_s1_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S2_5S_AT1 寄存器结构定义。地址偏移量:0xA84，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s2_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s2_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态2时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT1_dsp_s2_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT1_dsp_s2_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S3_5S_AT1 寄存器结构定义。地址偏移量:0xA88，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s3_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s3_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态3时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT1_dsp_s3_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT1_dsp_s3_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S4_5S_AT1 寄存器结构定义。地址偏移量:0xA8C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s4_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s4_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态4时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT1_dsp_s4_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT1_dsp_s4_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S5_5S_AT1 寄存器结构定义。地址偏移量:0xA90，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s5_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s5_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态5时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT1_dsp_s5_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT1_dsp_s5_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S1_8S_AT1 寄存器结构定义。地址偏移量:0xA94，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s1_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s1_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态1时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT1_dsp_s1_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT1_dsp_s1_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S2_8S_AT1 寄存器结构定义。地址偏移量:0xA98，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s2_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s2_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态2时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT1_dsp_s2_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT1_dsp_s2_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S3_8S_AT1 寄存器结构定义。地址偏移量:0xA9C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s3_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s3_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态3时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT1_dsp_s3_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT1_dsp_s3_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S4_8S_AT1 寄存器结构定义。地址偏移量:0xAA0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s4_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s4_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态4时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT1_dsp_s4_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT1_dsp_s4_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S5_8S_AT1 寄存器结构定义。地址偏移量:0xAA4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s5_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s5_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态5时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT1_dsp_s5_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT1_dsp_s5_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S6_8S_AT1 寄存器结构定义。地址偏移量:0xAA8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s6_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s6_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态6时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT1_dsp_s6_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT1_dsp_s6_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S7_8S_AT1 寄存器结构定义。地址偏移量:0xAAC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s7_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s7_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态7时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT1_dsp_s7_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT1_dsp_s7_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S8_8S_AT1 寄存器结构定义。地址偏移量:0xAB0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s8_8s_at1_reg;
    struct
    {
        unsigned long  dsp_s8_8s_dc_corr_inter_at1 : 24; /* bit[0-23] : 8档AGC状态8时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT1_dsp_s8_8s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT1_dsp_s8_8s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S1_5S_AT1 寄存器结构定义。地址偏移量:0xAB4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s1_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s1_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态1时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT1_dsp_s1_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT1_dsp_s1_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S2_5S_AT1 寄存器结构定义。地址偏移量:0xAB8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s2_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s2_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态2时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT1_dsp_s2_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT1_dsp_s2_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S3_5S_AT1 寄存器结构定义。地址偏移量:0xABC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s3_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s3_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态3时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT1_dsp_s3_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT1_dsp_s3_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S4_5S_AT1 寄存器结构定义。地址偏移量:0xAC0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s4_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s4_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态4时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT1_dsp_s4_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT1_dsp_s4_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S5_5S_AT1 寄存器结构定义。地址偏移量:0xAC4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s5_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s5_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态5时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT1_dsp_s5_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT1_dsp_s5_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S1_8S_AT2 寄存器结构定义。地址偏移量:0xAC8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s1_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s1_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态1时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT2_dsp_s1_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_8S_AT2_dsp_s1_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S2_8S_AT2 寄存器结构定义。地址偏移量:0xACC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s2_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s2_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态2时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT2_dsp_s2_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_8S_AT2_dsp_s2_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S3_8S_AT2 寄存器结构定义。地址偏移量:0xAD0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s3_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s3_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态3时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT2_dsp_s3_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_8S_AT2_dsp_s3_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S4_8S_AT2 寄存器结构定义。地址偏移量:0xAD4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s4_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s4_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态4时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT2_dsp_s4_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_8S_AT2_dsp_s4_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S5_8S_AT2 寄存器结构定义。地址偏移量:0xAD8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s5_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s5_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态5时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT2_dsp_s5_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_8S_AT2_dsp_s5_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S6_8S_AT2 寄存器结构定义。地址偏移量:0xADC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s6_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s6_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态6时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT2_dsp_s6_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_8S_AT2_dsp_s6_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S7_8S_AT2 寄存器结构定义。地址偏移量:0xAE0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s7_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s7_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态7时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT2_dsp_s7_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_8S_AT2_dsp_s7_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S8_8S_AT2 寄存器结构定义。地址偏移量:0xAE4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s8_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s8_8s_dc_corr_intra_at2 : 24; /* bit[0-23] : 8档AGC状态8时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT2_dsp_s8_8s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_8S_AT2_dsp_s8_8s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S1_5S_AT2 寄存器结构定义。地址偏移量:0xAE8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s1_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s1_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态1时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT2_dsp_s1_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S1_5S_AT2_dsp_s1_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S2_5S_AT2 寄存器结构定义。地址偏移量:0xAEC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s2_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s2_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态2时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT2_dsp_s2_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S2_5S_AT2_dsp_s2_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S3_5S_AT2 寄存器结构定义。地址偏移量:0xAF0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s3_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s3_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态3时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT2_dsp_s3_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S3_5S_AT2_dsp_s3_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S4_5S_AT2 寄存器结构定义。地址偏移量:0xAF4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s4_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s4_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态4时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT2_dsp_s4_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S4_5S_AT2_dsp_s4_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S5_5S_AT2 寄存器结构定义。地址偏移量:0xAF8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s5_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s5_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态5时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT2_dsp_s5_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S5_5S_AT2_dsp_s5_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S1_8S_AT2 寄存器结构定义。地址偏移量:0xAFC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s1_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s1_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态1时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT2_dsp_s1_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_8S_AT2_dsp_s1_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S2_8S_AT2 寄存器结构定义。地址偏移量:0xB00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s2_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s2_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态2时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT2_dsp_s2_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_8S_AT2_dsp_s2_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S3_8S_AT2 寄存器结构定义。地址偏移量:0xB04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s3_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s3_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态3时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT2_dsp_s3_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_8S_AT2_dsp_s3_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S4_8S_AT2 寄存器结构定义。地址偏移量:0xB08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s4_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s4_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态4时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT2_dsp_s4_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_8S_AT2_dsp_s4_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S5_8S_AT2 寄存器结构定义。地址偏移量:0xB0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s5_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s5_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态5时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT2_dsp_s5_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_8S_AT2_dsp_s5_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S6_8S_AT2 寄存器结构定义。地址偏移量:0xB10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s6_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s6_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态6时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT2_dsp_s6_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_8S_AT2_dsp_s6_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S7_8S_AT2 寄存器结构定义。地址偏移量:0xB14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s7_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s7_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态7时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT2_dsp_s7_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_8S_AT2_dsp_s7_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S8_8S_AT2 寄存器结构定义。地址偏移量:0xB18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s8_8s_at2_reg;
    struct
    {
        unsigned long  dsp_s8_8s_dc_corr_inter_at2 : 24; /* bit[0-23] : 8档AGC状态8时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT2_dsp_s8_8s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_8S_AT2_dsp_s8_8s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S1_5S_AT2 寄存器结构定义。地址偏移量:0xB1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s1_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s1_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态1时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT2_dsp_s1_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S1_5S_AT2_dsp_s1_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S2_5S_AT2 寄存器结构定义。地址偏移量:0xB20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s2_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s2_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态2时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT2_dsp_s2_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S2_5S_AT2_dsp_s2_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S3_5S_AT2 寄存器结构定义。地址偏移量:0xB24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s3_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s3_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态3时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT2_dsp_s3_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S3_5S_AT2_dsp_s3_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S4_5S_AT2 寄存器结构定义。地址偏移量:0xB28，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s4_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s4_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态4时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT2_dsp_s4_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S4_5S_AT2_dsp_s4_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S5_5S_AT2 寄存器结构定义。地址偏移量:0xB2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s5_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s5_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态5时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT2_dsp_s5_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S5_5S_AT2_dsp_s5_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_SPI_EN_UNION
 结构说明  : DC_STA_SPI_EN 寄存器结构定义。地址偏移量:0xB30，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_spi_en_reg;
    struct
    {
        unsigned long  dsp_sta_dc_spi_en : 1;  /* bit[0]   : 静态DC校准值SPI发送使能，高电平有效。
                                                             C模不配置。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_STA_SPI_EN_UNION;
#define WBBP_DC_STA_SPI_EN_dsp_sta_dc_spi_en_START  (0)
#define WBBP_DC_STA_SPI_EN_dsp_sta_dc_spi_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_DCR_2ND_CTRL_AT1_UNION
 结构说明  : DCR_2ND_CTRL_AT1 寄存器结构定义。地址偏移量:0xB34，初值:0x00000708，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dcr_2nd_ctrl_at1_reg;
    struct
    {
        unsigned long  small_dc_time_at1 : 8;  /* bit[0-7]  : DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。 */
        unsigned long  small_dc_th_at1   : 8;  /* bit[8-15] : DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。 */
        unsigned long  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} WBBP_DCR_2ND_CTRL_AT1_UNION;
#define WBBP_DCR_2ND_CTRL_AT1_small_dc_time_at1_START  (0)
#define WBBP_DCR_2ND_CTRL_AT1_small_dc_time_at1_END    (7)
#define WBBP_DCR_2ND_CTRL_AT1_small_dc_th_at1_START    (8)
#define WBBP_DCR_2ND_CTRL_AT1_small_dc_th_at1_END      (15)


/*****************************************************************************
 结构名    : WBBP_DCR_2ND_CTRL_AT2_UNION
 结构说明  : DCR_2ND_CTRL_AT2 寄存器结构定义。地址偏移量:0xB38，初值:0x00000708，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dcr_2nd_ctrl_at2_reg;
    struct
    {
        unsigned long  small_dc_time_at2 : 8;  /* bit[0-7]  : DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。 */
        unsigned long  small_dc_th_at2   : 8;  /* bit[8-15] : DCR的小残余DC判决，当ΔDC值小于small_dc_th,small_dc_time次时，小残余标志有效。 */
        unsigned long  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} WBBP_DCR_2ND_CTRL_AT2_UNION;
#define WBBP_DCR_2ND_CTRL_AT2_small_dc_time_at2_START  (0)
#define WBBP_DCR_2ND_CTRL_AT2_small_dc_time_at2_END    (7)
#define WBBP_DCR_2ND_CTRL_AT2_small_dc_th_at2_START    (8)
#define WBBP_DCR_2ND_CTRL_AT2_small_dc_th_at2_END      (15)


/*****************************************************************************
 结构名    : WBBP_WAGC_STATE_RPT_AT1_UNION
 结构说明  : WAGC_STATE_RPT_AT1 寄存器结构定义。地址偏移量:0xB3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_state_rpt_at1_reg;
    struct
    {
        unsigned long  reserved_0               : 20; /* bit[0-19] : 保留 */
        unsigned long  dsp_rpt_agc_5s_state_at1 : 3;  /* bit[20-22]: BBP上报用于控制RF增益的5档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5； */
        unsigned long  reserved_1               : 1;  /* bit[23]   : 保留 */
        unsigned long  dsp_rpt_agc_8s_state_at1 : 3;  /* bit[24-26]: BBP上报用于控制RF增益的8档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。 */
        unsigned long  reserved_2               : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_WAGC_STATE_RPT_AT1_UNION;
#define WBBP_WAGC_STATE_RPT_AT1_dsp_rpt_agc_5s_state_at1_START  (20)
#define WBBP_WAGC_STATE_RPT_AT1_dsp_rpt_agc_5s_state_at1_END    (22)
#define WBBP_WAGC_STATE_RPT_AT1_dsp_rpt_agc_8s_state_at1_START  (24)
#define WBBP_WAGC_STATE_RPT_AT1_dsp_rpt_agc_8s_state_at1_END    (26)


/*****************************************************************************
 结构名    : WBBP_WAGC_STATE_RPT_AT2_UNION
 结构说明  : WAGC_STATE_RPT_AT2 寄存器结构定义。地址偏移量:0xB40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_state_rpt_at2_reg;
    struct
    {
        unsigned long  reserved_0               : 20; /* bit[0-19] : 保留 */
        unsigned long  dsp_rpt_agc_5s_state_at2 : 3;  /* bit[20-22]: BBP上报用于控制RF增益的5档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5； */
        unsigned long  reserved_1               : 1;  /* bit[23]   : 保留 */
        unsigned long  dsp_rpt_agc_8s_state_at2 : 3;  /* bit[24-26]: BBP上报用于控制RF增益的8档状态机。0，表示S1；1，表示S2；2，表示S3；3，表示S4；4，表示S5；5，表示S6；6，表示S7；7，表示S8。 */
        unsigned long  reserved_2               : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_WAGC_STATE_RPT_AT2_UNION;
#define WBBP_WAGC_STATE_RPT_AT2_dsp_rpt_agc_5s_state_at2_START  (20)
#define WBBP_WAGC_STATE_RPT_AT2_dsp_rpt_agc_5s_state_at2_END    (22)
#define WBBP_WAGC_STATE_RPT_AT2_dsp_rpt_agc_8s_state_at2_START  (24)
#define WBBP_WAGC_STATE_RPT_AT2_dsp_rpt_agc_8s_state_at2_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_CFG_BBP_BLK_AT1_UNION
 结构说明  : DSP_CFG_BBP_BLK_AT1 寄存器结构定义。地址偏移量:0xB44，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_cfg_bbp_blk_at1_reg;
    struct
    {
        unsigned long  dsp_soft_blk_ind_at1_intra : 1;  /* bit[0]   : 软件配置天线1 BBP本频Block状态。
                                                                      1，处于Block状态；0，不处于Block状态。
                                                                      C模不配置。 */
        unsigned long  dsp_soft_blk_ind_at1_inter : 1;  /* bit[1]   : 软件配置天线1 BBP异频Block状态。
                                                                      1，处于Block状态；0，不处于Block状态。
                                                                      C模不配置。 */
        unsigned long  reserved                   : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DSP_CFG_BBP_BLK_AT1_UNION;
#define WBBP_DSP_CFG_BBP_BLK_AT1_dsp_soft_blk_ind_at1_intra_START  (0)
#define WBBP_DSP_CFG_BBP_BLK_AT1_dsp_soft_blk_ind_at1_intra_END    (0)
#define WBBP_DSP_CFG_BBP_BLK_AT1_dsp_soft_blk_ind_at1_inter_START  (1)
#define WBBP_DSP_CFG_BBP_BLK_AT1_dsp_soft_blk_ind_at1_inter_END    (1)


/*****************************************************************************
 结构名    : WBBP_DSP_CFG_BBP_BLK_AT2_UNION
 结构说明  : DSP_CFG_BBP_BLK_AT2 寄存器结构定义。地址偏移量:0xB48，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_cfg_bbp_blk_at2_reg;
    struct
    {
        unsigned long  dsp_soft_blk_ind_at2_intra : 1;  /* bit[0]   : 软件配置天线2 BBP本频Block状态
                                                                      1，处于Block状态；0，不处于Block状态。
                                                                      C模不配置。 */
        unsigned long  dsp_soft_blk_ind_at2_inter : 1;  /* bit[1]   : 软件配置天线2 BBP异频Block状态。
                                                                      1，处于Block状态；0，不处于Block状态。
                                                                      C模不配置。 */
        unsigned long  reserved                   : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DSP_CFG_BBP_BLK_AT2_UNION;
#define WBBP_DSP_CFG_BBP_BLK_AT2_dsp_soft_blk_ind_at2_intra_START  (0)
#define WBBP_DSP_CFG_BBP_BLK_AT2_dsp_soft_blk_ind_at2_intra_END    (0)
#define WBBP_DSP_CFG_BBP_BLK_AT2_dsp_soft_blk_ind_at2_inter_START  (1)
#define WBBP_DSP_CFG_BBP_BLK_AT2_dsp_soft_blk_ind_at2_inter_END    (1)


/*****************************************************************************
 结构名    : WBBP_WAGC_IQ_MIS_RPT_AT1_UNION
 结构说明  : WAGC_IQ_MIS_RPT_AT1 寄存器结构定义。地址偏移量:0xB4C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_iq_mis_rpt_at1_reg;
    struct
    {
        unsigned long  iq_mis_ak_cpu_at1 : 10; /* bit[0-9]  : W和TDS上报IQ Mismatch计算得到的滤波前ak值。 */
        unsigned long  reserved_0        : 6;  /* bit[10-15]: 保留 */
        unsigned long  iq_mis_pk_cpu_at1 : 11; /* bit[16-26]: W和TDS上报IQ Mismatch计算得到的滤波前pk值。 */
        unsigned long  reserved_1        : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_WAGC_IQ_MIS_RPT_AT1_UNION;
#define WBBP_WAGC_IQ_MIS_RPT_AT1_iq_mis_ak_cpu_at1_START  (0)
#define WBBP_WAGC_IQ_MIS_RPT_AT1_iq_mis_ak_cpu_at1_END    (9)
#define WBBP_WAGC_IQ_MIS_RPT_AT1_iq_mis_pk_cpu_at1_START  (16)
#define WBBP_WAGC_IQ_MIS_RPT_AT1_iq_mis_pk_cpu_at1_END    (26)


/*****************************************************************************
 结构名    : WBBP_WAGC_IQ_MIS_RPT_AT2_UNION
 结构说明  : WAGC_IQ_MIS_RPT_AT2 寄存器结构定义。地址偏移量:0xB50，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_iq_mis_rpt_at2_reg;
    struct
    {
        unsigned long  iq_mis_ak_cpu_at2 : 10; /* bit[0-9]  : W和TDS上报IQ Mismatch计算得到的滤波前ak值。 */
        unsigned long  reserved_0        : 6;  /* bit[10-15]: 保留 */
        unsigned long  iq_mis_pk_cpu_at2 : 11; /* bit[16-26]: W和TDS上报IQ Mismatch计算得到的滤波前pk值。 */
        unsigned long  reserved_1        : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_WAGC_IQ_MIS_RPT_AT2_UNION;
#define WBBP_WAGC_IQ_MIS_RPT_AT2_iq_mis_ak_cpu_at2_START  (0)
#define WBBP_WAGC_IQ_MIS_RPT_AT2_iq_mis_ak_cpu_at2_END    (9)
#define WBBP_WAGC_IQ_MIS_RPT_AT2_iq_mis_pk_cpu_at2_START  (16)
#define WBBP_WAGC_IQ_MIS_RPT_AT2_iq_mis_pk_cpu_at2_END    (26)


/*****************************************************************************
 结构名    : WBBP_SPUR_ALPHA_COE_UNION
 结构说明  : SPUR_ALPHA_COE 寄存器结构定义。地址偏移量:0xB54，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      spur_alpha_coe_reg;
    struct
    {
        unsigned long  dsp_spur_alpha_para : 3;  /* bit[0-2] : 谐波干扰消除，alpha滤波系数选择。
                                                               3'd0，不进行alpha滤波；
                                                               3'd1，alpha滤波系数为1/2；
                                                               3'd2，alpha滤波系数为1/4；
                                                               3'd3，alpha滤波系数为1/8；
                                                               3'd4，alpha滤波系数为1/16；
                                                               3'd5，alpha滤波系数为1/32。 */
        unsigned long  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_SPUR_ALPHA_COE_UNION;
#define WBBP_SPUR_ALPHA_COE_dsp_spur_alpha_para_START  (0)
#define WBBP_SPUR_ALPHA_COE_dsp_spur_alpha_para_END    (2)


/*****************************************************************************
 结构名    : WBBP_WAGC_IQ_MIS_POST_RPT_AT1_UNION
 结构说明  : WAGC_IQ_MIS_POST_RPT_AT1 寄存器结构定义。地址偏移量:0xB58，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_iq_mis_post_rpt_at1_reg;
    struct
    {
        unsigned long  rxiq_est_a_post_at1 : 10; /* bit[0-9]  : W、C和TDS上报IQ Mismatch计算得到的滤波后ak值。 */
        unsigned long  reserved_0          : 6;  /* bit[10-15]: 保留 */
        unsigned long  rxiq_est_p_post_at1 : 11; /* bit[16-26]: W、C和TDS上报IQ Mismatch计算得到的滤波后pk值。 */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_WAGC_IQ_MIS_POST_RPT_AT1_UNION;
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT1_rxiq_est_a_post_at1_START  (0)
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT1_rxiq_est_a_post_at1_END    (9)
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT1_rxiq_est_p_post_at1_START  (16)
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT1_rxiq_est_p_post_at1_END    (26)


/*****************************************************************************
 结构名    : WBBP_WAGC_IQ_MIS_POST_RPT_AT2_UNION
 结构说明  : WAGC_IQ_MIS_POST_RPT_AT2 寄存器结构定义。地址偏移量:0xB5C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_iq_mis_post_rpt_at2_reg;
    struct
    {
        unsigned long  rxiq_est_a_post_at2 : 10; /* bit[0-9]  : W、C和TDS上报IQ Mismatch计算得到的滤波后ak值。 */
        unsigned long  reserved_0          : 6;  /* bit[10-15]: 保留 */
        unsigned long  rxiq_est_p_post_at2 : 11; /* bit[16-26]: W、C和TDS上报IQ Mismatch计算得到的滤波后pk值。 */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_WAGC_IQ_MIS_POST_RPT_AT2_UNION;
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT2_rxiq_est_a_post_at2_START  (0)
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT2_rxiq_est_a_post_at2_END    (9)
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT2_rxiq_est_p_post_at2_START  (16)
#define WBBP_WAGC_IQ_MIS_POST_RPT_AT2_rxiq_est_p_post_at2_END    (26)


/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_5S_INC_TH_ADD_UNION
 结构说明  : AAGC_RSSI_5S_INC_TH_ADD 寄存器结构定义。地址偏移量:0xB9C，初值:0x00FFFAEB，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_5s_inc_th_add_reg;
    struct
    {
        unsigned long  s5_2s6_5s_th : 8;  /* bit[0-7]  : 五档AAGC状态跳转S5->S6的RSSI门限，单位dBm，配置二进制补码值。
                                                         说明：按照S1->S2->S3->S4->S5->S6->S7->S8的顺序，天线口的RSSI递增，AAGC的增益递减。
                                                         C模不配置。 */
        unsigned long  s6_2s7_5s_th : 8;  /* bit[8-15] : 五档AAGC状态跳转S6->S7的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s7_2s8_5s_th : 8;  /* bit[16-23]: 五档AAGC状态跳转S7->S8的RSSI门限。
                                                         C模不配置。 */
        unsigned long  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_AAGC_RSSI_5S_INC_TH_ADD_UNION;
#define WBBP_AAGC_RSSI_5S_INC_TH_ADD_s5_2s6_5s_th_START  (0)
#define WBBP_AAGC_RSSI_5S_INC_TH_ADD_s5_2s6_5s_th_END    (7)
#define WBBP_AAGC_RSSI_5S_INC_TH_ADD_s6_2s7_5s_th_START  (8)
#define WBBP_AAGC_RSSI_5S_INC_TH_ADD_s6_2s7_5s_th_END    (15)
#define WBBP_AAGC_RSSI_5S_INC_TH_ADD_s7_2s8_5s_th_START  (16)
#define WBBP_AAGC_RSSI_5S_INC_TH_ADD_s7_2s8_5s_th_END    (23)


/*****************************************************************************
 结构名    : WBBP_AAGC_RSSI_5S_DEC_TH_ADD_UNION
 结构说明  : AAGC_RSSI_5S_DEC_TH_ADD 寄存器结构定义。地址偏移量:0xBA0，初值:0x00FBF7E8，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      aagc_rssi_5s_dec_th_add_reg;
    struct
    {
        unsigned long  s6_2s5_5s_th : 8;  /* bit[0-7]  : 五档AAGC状态跳转S6->S5的RSSI门限，单位dBm，配置二进制补码值。
                                                         说明：按照S8->S7->S6->S5->S4->S3->S2->S1的顺序，天线口的RSSI递减，AAGC的增益递增。
                                                         C模不配置。 */
        unsigned long  s7_2s6_5s_th : 8;  /* bit[8-15] : 五档AAGC状态跳转S7->S6的RSSI门限。
                                                         C模不配置。 */
        unsigned long  s8_2s7_5s_th : 8;  /* bit[16-23]: 五档AAGC状态跳转S8->S7的RSSI门限。
                                                         C模不配置。 */
        unsigned long  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_AAGC_RSSI_5S_DEC_TH_ADD_UNION;
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADD_s6_2s5_5s_th_START  (0)
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADD_s6_2s5_5s_th_END    (7)
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADD_s7_2s6_5s_th_START  (8)
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADD_s7_2s6_5s_th_END    (15)
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADD_s8_2s7_5s_th_START  (16)
#define WBBP_AAGC_RSSI_5S_DEC_TH_ADD_s8_2s7_5s_th_END    (23)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S67_INTRA_AT1_UNION
 结构说明  : RF_5S_GAIN_S67_INTRA_AT1 寄存器结构定义。地址偏移量:0xBA4，初值:0x01280160，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s67_intra_at1_reg;
    struct
    {
        unsigned long  s6_5s_rf_gain_intra_at1 : 12; /* bit[0-11] : 五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_5s_rf_gain_intra_at1 : 12; /* bit[16-27]: 五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S67_INTRA_AT1_UNION;
#define WBBP_RF_5S_GAIN_S67_INTRA_AT1_s6_5s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_5S_GAIN_S67_INTRA_AT1_s6_5s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_5S_GAIN_S67_INTRA_AT1_s7_5s_rf_gain_intra_at1_START  (16)
#define WBBP_RF_5S_GAIN_S67_INTRA_AT1_s7_5s_rf_gain_intra_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S8_INTRA_AT12_UNION
 结构说明  : RF_5S_GAIN_S8_INTRA_AT12 寄存器结构定义。地址偏移量:0xBA8，初值:0x01080108，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s8_intra_at12_reg;
    struct
    {
        unsigned long  s8_5s_rf_gain_intra_at1 : 12; /* bit[0-11] : 五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s8_5s_rf_gain_intra_at2 : 12; /* bit[16-27]: 五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S8_INTRA_AT12_UNION;
#define WBBP_RF_5S_GAIN_S8_INTRA_AT12_s8_5s_rf_gain_intra_at1_START  (0)
#define WBBP_RF_5S_GAIN_S8_INTRA_AT12_s8_5s_rf_gain_intra_at1_END    (11)
#define WBBP_RF_5S_GAIN_S8_INTRA_AT12_s8_5s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_5S_GAIN_S8_INTRA_AT12_s8_5s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S67_INTRA_AT2_UNION
 结构说明  : RF_5S_GAIN_S67_INTRA_AT2 寄存器结构定义。地址偏移量:0xBAC，初值:0x01280160，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s67_intra_at2_reg;
    struct
    {
        unsigned long  s6_5s_rf_gain_intra_at2 : 12; /* bit[0-11] : 五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_5s_rf_gain_intra_at2 : 12; /* bit[16-27]: 五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S67_INTRA_AT2_UNION;
#define WBBP_RF_5S_GAIN_S67_INTRA_AT2_s6_5s_rf_gain_intra_at2_START  (0)
#define WBBP_RF_5S_GAIN_S67_INTRA_AT2_s6_5s_rf_gain_intra_at2_END    (11)
#define WBBP_RF_5S_GAIN_S67_INTRA_AT2_s7_5s_rf_gain_intra_at2_START  (16)
#define WBBP_RF_5S_GAIN_S67_INTRA_AT2_s7_5s_rf_gain_intra_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S67_INTER_AT1_UNION
 结构说明  : RF_5S_GAIN_S67_INTER_AT1 寄存器结构定义。地址偏移量:0xBB0，初值:0x01280160，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s67_inter_at1_reg;
    struct
    {
        unsigned long  s6_5s_rf_gain_inter_at1 : 12; /* bit[0-11] : 五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_5s_rf_gain_inter_at1 : 12; /* bit[16-27]: 五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S67_INTER_AT1_UNION;
#define WBBP_RF_5S_GAIN_S67_INTER_AT1_s6_5s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_5S_GAIN_S67_INTER_AT1_s6_5s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_5S_GAIN_S67_INTER_AT1_s7_5s_rf_gain_inter_at1_START  (16)
#define WBBP_RF_5S_GAIN_S67_INTER_AT1_s7_5s_rf_gain_inter_at1_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S8_INTER_AT12_UNION
 结构说明  : RF_5S_GAIN_S8_INTER_AT12 寄存器结构定义。地址偏移量:0xBB4，初值:0x01080108，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s8_inter_at12_reg;
    struct
    {
        unsigned long  s8_5s_rf_gain_inter_at1 : 12; /* bit[0-11] : 五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s8_5s_rf_gain_inter_at2 : 12; /* bit[16-27]: 五档AAGC S8状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S8_INTER_AT12_UNION;
#define WBBP_RF_5S_GAIN_S8_INTER_AT12_s8_5s_rf_gain_inter_at1_START  (0)
#define WBBP_RF_5S_GAIN_S8_INTER_AT12_s8_5s_rf_gain_inter_at1_END    (11)
#define WBBP_RF_5S_GAIN_S8_INTER_AT12_s8_5s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_5S_GAIN_S8_INTER_AT12_s8_5s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_RF_5S_GAIN_S67_INTER_AT2_UNION
 结构说明  : RF_5S_GAIN_S67_INTER_AT2 寄存器结构定义。地址偏移量:0xBB8，初值:0x01280160，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_5s_gain_s67_inter_at2_reg;
    struct
    {
        unsigned long  s6_5s_rf_gain_inter_at2 : 12; /* bit[0-11] : 五档AAGC S6状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_0              : 4;  /* bit[12-15]: 保留 */
        unsigned long  s7_5s_rf_gain_inter_at2 : 12; /* bit[16-27]: 五档AAGC S7状态时RF的增益，即LNA、LPF和VGA2增益和。单位0.125dB，配置二进制补码值。
                                                                    C模不配置。 */
        unsigned long  reserved_1              : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_5S_GAIN_S67_INTER_AT2_UNION;
#define WBBP_RF_5S_GAIN_S67_INTER_AT2_s6_5s_rf_gain_inter_at2_START  (0)
#define WBBP_RF_5S_GAIN_S67_INTER_AT2_s6_5s_rf_gain_inter_at2_END    (11)
#define WBBP_RF_5S_GAIN_S67_INTER_AT2_s7_5s_rf_gain_inter_at2_START  (16)
#define WBBP_RF_5S_GAIN_S67_INTER_AT2_s7_5s_rf_gain_inter_at2_END    (27)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S6_5S_AT1 寄存器结构定义。地址偏移量:0xBBC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s6_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s6_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态6时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT1_dsp_s6_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT1_dsp_s6_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S7_5S_AT1 寄存器结构定义。地址偏移量:0xBC0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s7_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s7_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态7时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT1_dsp_s7_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT1_dsp_s7_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S8_5S_AT1 寄存器结构定义。地址偏移量:0xBC4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s8_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s8_5s_dc_corr_intra_at1 : 24; /* bit[0-23] : 5档AGC状态8时，本频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT1_dsp_s8_5s_dc_corr_intra_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT1_dsp_s8_5s_dc_corr_intra_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S6_5S_AT1 寄存器结构定义。地址偏移量:0xBC8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s6_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s6_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态6时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT1_dsp_s6_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT1_dsp_s6_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S7_5S_AT1 寄存器结构定义。地址偏移量:0xBCC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s7_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s7_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态7时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT1_dsp_s7_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT1_dsp_s7_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT1_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S8_5S_AT1 寄存器结构定义。地址偏移量:0xBD0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s8_5s_at1_reg;
    struct
    {
        unsigned long  dsp_s8_5s_dc_corr_inter_at1 : 24; /* bit[0-23] : 5档AGC状态8时，异频下天线1静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT1_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT1_dsp_s8_5s_dc_corr_inter_at1_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT1_dsp_s8_5s_dc_corr_inter_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S6_5S_AT2 寄存器结构定义。地址偏移量:0xBD4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s6_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s6_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态6时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT2_dsp_s6_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S6_5S_AT2_dsp_s6_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S7_5S_AT2 寄存器结构定义。地址偏移量:0xBD8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s7_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s7_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态7时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT2_dsp_s7_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S7_5S_AT2_dsp_s7_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTRA_S8_5S_AT2 寄存器结构定义。地址偏移量:0xBDC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_intra_s8_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s8_5s_dc_corr_intra_at2 : 24; /* bit[0-23] : 5档AGC状态8时，本频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT2_dsp_s8_5s_dc_corr_intra_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTRA_S8_5S_AT2_dsp_s8_5s_dc_corr_intra_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S6_5S_AT2 寄存器结构定义。地址偏移量:0xBE0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s6_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s6_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态6时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT2_dsp_s6_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S6_5S_AT2_dsp_s6_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S7_5S_AT2 寄存器结构定义。地址偏移量:0xBE4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s7_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s7_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态7时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT2_dsp_s7_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S7_5S_AT2_dsp_s7_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT2_UNION
 结构说明  : DC_STA_CRRO_CFG_INTER_S8_5S_AT2 寄存器结构定义。地址偏移量:0xBE8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_sta_crro_cfg_inter_s8_5s_at2_reg;
    struct
    {
        unsigned long  dsp_s8_5s_dc_corr_inter_at2 : 24; /* bit[0-23] : 5档AGC状态8时，异频下天线2静态DC补偿值。 */
        unsigned long  reserved                    : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT2_UNION;
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT2_dsp_s8_5s_dc_corr_inter_at2_START  (0)
#define WBBP_DC_STA_CRRO_CFG_INTER_S8_5S_AT2_dsp_s8_5s_dc_corr_inter_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S6_5S_RF_CTRL_AT1_UNION
 结构说明  : S6_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0xBEC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s6_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s6_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S6状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S6_5S_RF_CTRL_AT1_UNION;
#define WBBP_S6_5S_RF_CTRL_AT1_s6_5s_rf_ctrl_at1_START  (0)
#define WBBP_S6_5S_RF_CTRL_AT1_s6_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S7_5S_RF_CTRL_AT1_UNION
 结构说明  : S7_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0xBF0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s7_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s7_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S7状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S7_5S_RF_CTRL_AT1_UNION;
#define WBBP_S7_5S_RF_CTRL_AT1_s7_5s_rf_ctrl_at1_START  (0)
#define WBBP_S7_5S_RF_CTRL_AT1_s7_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S8_5S_RF_CTRL_AT1_UNION
 结构说明  : S8_5S_RF_CTRL_AT1 寄存器结构定义。地址偏移量:0xBF4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s8_5s_rf_ctrl_at1_reg;
    struct
    {
        unsigned long  s8_5s_rf_ctrl_at1 : 24; /* bit[0-23] : 五档AAGC S8状态时主集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S8_5S_RF_CTRL_AT1_UNION;
#define WBBP_S8_5S_RF_CTRL_AT1_s8_5s_rf_ctrl_at1_START  (0)
#define WBBP_S8_5S_RF_CTRL_AT1_s8_5s_rf_ctrl_at1_END    (23)


/*****************************************************************************
 结构名    : WBBP_S6_5S_RF_CTRL_AT2_UNION
 结构说明  : S6_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0xBF8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s6_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s6_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S6状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S6_5S_RF_CTRL_AT2_UNION;
#define WBBP_S6_5S_RF_CTRL_AT2_s6_5s_rf_ctrl_at2_START  (0)
#define WBBP_S6_5S_RF_CTRL_AT2_s6_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_S7_5S_RF_CTRL_AT2_UNION
 结构说明  : S7_5S_RF_CTRL_AT2 寄存器结构定义。地址偏移量:0xBFC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      s7_5s_rf_ctrl_at2_reg;
    struct
    {
        unsigned long  s7_5s_rf_ctrl_at2 : 24; /* bit[0-23] : 五档AAGC S7状态时分集RF控制字。
                                                              C模不配置。 */
        unsigned long  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_S7_5S_RF_CTRL_AT2_UNION;
#define WBBP_S7_5S_RF_CTRL_AT2_s7_5s_rf_ctrl_at2_START  (0)
#define WBBP_S7_5S_RF_CTRL_AT2_s7_5s_rf_ctrl_at2_END    (23)


/*****************************************************************************
 结构名    : WBBP_CORDIC_PHASE_VLD_UNION
 结构说明  : CORDIC_PHASE_VLD 寄存器结构定义。地址偏移量:0xC08，初值:0x00000000，宽度:32
 寄存器说明: 初始及间隔相位有效信号
*****************************************************************************/
typedef union
{
    unsigned long      cordic_phase_vld_reg;
    struct
    {
        unsigned long  dsp_pha_new_ind : 1;  /* bit[0]   : 保留 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_CORDIC_PHASE_VLD_UNION;
#define WBBP_CORDIC_PHASE_VLD_dsp_pha_new_ind_START  (0)
#define WBBP_CORDIC_PHASE_VLD_dsp_pha_new_ind_END    (0)


/*****************************************************************************
 结构名    : WBBP_TDS_SC_OFFSET_UNION
 结构说明  : TDS_SC_OFFSET 寄存器结构定义。地址偏移量:0xC0C，初值:0x00000000，宽度:32
 寄存器说明: TDS
*****************************************************************************/
typedef union
{
    unsigned long      tds_sc_offset_reg;
    struct
    {
        unsigned long  tds_sc_offset : 9;  /* bit[0-8] : 软件配置TDS采样纠偏值，有符号数。
                                                         C模不配置。 */
        unsigned long  reserved      : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_TDS_SC_OFFSET_UNION;
#define WBBP_TDS_SC_OFFSET_tds_sc_offset_START  (0)
#define WBBP_TDS_SC_OFFSET_tds_sc_offset_END    (8)


/*****************************************************************************
 结构名    : WBBP_TDS_FPU_FUNC_EN_UNION
 结构说明  : TDS_FPU_FUNC_EN 寄存器结构定义。地址偏移量:0xE00，初值:0x000C18EE，宽度:32
 寄存器说明: tds_fpu内部模块功能开关寄存器
*****************************************************************************/
typedef union
{
    unsigned long      tds_fpu_func_en_reg;
    struct
    {
        unsigned long  spmv_en          : 1;  /* bit[0]    : tds spmv使能信号。
                                                             1'b0，不使能，旁路；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  dcoc_comp_en     : 1;  /* bit[1]    : tds dcoc补偿dc_used使能信号。
                                                             1'b0，不使能，旁路；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  dcoc_calc_en     : 1;  /* bit[2]    : tds dcoc计算dc_est使能信号。
                                                             1'b0，不使能；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  dagct1_comp_en   : 1;  /* bit[3]    : tds tds dagct1补偿使能信号。
                                                             1'b0，不使能，旁路；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  reserved_0       : 1;  /* bit[4]    : 保留 */
        unsigned long  rxiq_comp_en     : 1;  /* bit[5]    : tds rxiq校准因子补偿使能信号。
                                                             1'b0，不使能，旁路；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  rxiq_calc_en     : 1;  /* bit[6]    : tds rxiq校准因子计算使能信号。
                                                             1'b0，不使能；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  drssi_wb_calc_en : 1;  /* bit[7]    : tds drssi_wb计算使能信号。
                                                             1'b0，不使能；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  reserved_1       : 3;  /* bit[8-10] : 保留 */
        unsigned long  drssi_nb_calc_en : 1;  /* bit[11]   : tds drssi_nb计算使能信号。
                                                             1'b0，不使能；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  dagct2_comp_en   : 1;  /* bit[12]   : tds dagct2补偿使能信号。
                                                             1'b0，不使能，旁路；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  reserved_2       : 5;  /* bit[13-17]: 保留 */
        unsigned long  codc_comp_en     : 1;  /* bit[18]   : tds cordic模块处理使能信号。
                                                             1'b0，不使能，旁路；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  sinc_comp_en     : 1;  /* bit[19]   : tds sinc重采样滤波模块处理使能信号。
                                                             1'b0，不使能，旁路；
                                                             1'b1，使能。
                                                             C模不配置。 */
        unsigned long  reserved_3       : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_TDS_FPU_FUNC_EN_UNION;
#define WBBP_TDS_FPU_FUNC_EN_spmv_en_START           (0)
#define WBBP_TDS_FPU_FUNC_EN_spmv_en_END             (0)
#define WBBP_TDS_FPU_FUNC_EN_dcoc_comp_en_START      (1)
#define WBBP_TDS_FPU_FUNC_EN_dcoc_comp_en_END        (1)
#define WBBP_TDS_FPU_FUNC_EN_dcoc_calc_en_START      (2)
#define WBBP_TDS_FPU_FUNC_EN_dcoc_calc_en_END        (2)
#define WBBP_TDS_FPU_FUNC_EN_dagct1_comp_en_START    (3)
#define WBBP_TDS_FPU_FUNC_EN_dagct1_comp_en_END      (3)
#define WBBP_TDS_FPU_FUNC_EN_rxiq_comp_en_START      (5)
#define WBBP_TDS_FPU_FUNC_EN_rxiq_comp_en_END        (5)
#define WBBP_TDS_FPU_FUNC_EN_rxiq_calc_en_START      (6)
#define WBBP_TDS_FPU_FUNC_EN_rxiq_calc_en_END        (6)
#define WBBP_TDS_FPU_FUNC_EN_drssi_wb_calc_en_START  (7)
#define WBBP_TDS_FPU_FUNC_EN_drssi_wb_calc_en_END    (7)
#define WBBP_TDS_FPU_FUNC_EN_drssi_nb_calc_en_START  (11)
#define WBBP_TDS_FPU_FUNC_EN_drssi_nb_calc_en_END    (11)
#define WBBP_TDS_FPU_FUNC_EN_dagct2_comp_en_START    (12)
#define WBBP_TDS_FPU_FUNC_EN_dagct2_comp_en_END      (12)
#define WBBP_TDS_FPU_FUNC_EN_codc_comp_en_START      (18)
#define WBBP_TDS_FPU_FUNC_EN_codc_comp_en_END        (18)
#define WBBP_TDS_FPU_FUNC_EN_sinc_comp_en_START      (19)
#define WBBP_TDS_FPU_FUNC_EN_sinc_comp_en_END        (19)


/*****************************************************************************
 结构名    : WBBP_FIR_SEL_UNION
 结构说明  : FIR_SEL 寄存器结构定义。地址偏移量:0xE04，初值:0x00000000，宽度:32
 寄存器说明: 下采样模块的抽点选择信号
*****************************************************************************/
typedef union
{
    unsigned long      fir_sel_reg;
    struct
    {
        unsigned long  fir_sel  : 2;  /* bit[0-1] : 下采样模块的抽点选择信号。
                                                    上电之后只配置一次，配置范围0~2。
                                                    0，选择下采样滤波器输出的第0、3、6…个数据；
                                                    1，选择下采样滤波器输出的第1、4、7…个数据；
                                                    2，选择下采样滤波器输出的第2、5、8…个数据；
                                                    3，保留。
                                                    C模不配置。 */
        unsigned long  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_FIR_SEL_UNION;
#define WBBP_FIR_SEL_fir_sel_START   (0)
#define WBBP_FIR_SEL_fir_sel_END     (1)


/*****************************************************************************
 结构名    : WBBP_DATA_SEL_UNION
 结构说明  : DATA_SEL 寄存器结构定义。地址偏移量:0xE0C，初值:0x00000000，宽度:32
 寄存器说明: 接收数据抽取选择寄存器
*****************************************************************************/
typedef union
{
    unsigned long      data_sel_reg;
    struct
    {
        unsigned long  rrc_sel  : 2;  /* bit[0-1] : 接收滤波后数据选择输出。
                                                    2'b00，选择抽取第1路信号；
                                                    2'b01，选择抽取第2路信号；
                                                    2'b10，选择抽取第3路信号；
                                                    2'b11，选择抽取第4路信号。 */
        unsigned long  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DATA_SEL_UNION;
#define WBBP_DATA_SEL_rrc_sel_START   (0)
#define WBBP_DATA_SEL_rrc_sel_END     (1)


/*****************************************************************************
 结构名    : WBBP_DCOC_UPDATE_UNION
 结构说明  : DCOC_UPDATE 寄存器结构定义。地址偏移量:0xE20，初值:0x00000000，宽度:32
 寄存器说明: dcoc是否按样点更新
*****************************************************************************/
typedef union
{
    unsigned long      dcoc_update_reg;
    struct
    {
        unsigned long  dcoc_update : 1;  /* bit[0]   : TD dcoc是否按样点更新dc_used。
                                                       1'b0，按样点更新；
                                                       1'b1，按时隙更新。
                                                       注意：本寄存器上电配置一次，不支持动态切换的情况。
                                                       C模不配置。 */
        unsigned long  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DCOC_UPDATE_UNION;
#define WBBP_DCOC_UPDATE_dcoc_update_START  (0)
#define WBBP_DCOC_UPDATE_dcoc_update_END    (0)


/*****************************************************************************
 结构名    : WBBP_DCOC_SFTBIT1_UNION
 结构说明  : DCOC_SFTBIT1 寄存器结构定义。地址偏移量:0xE24，初值:0x000E000E，宽度:32
 寄存器说明: dcoc的天线1的i路和q路数据移位bit数
*****************************************************************************/
typedef union
{
    unsigned long      dcoc_sftbit1_reg;
    struct
    {
        unsigned long  dcoc_sftbit_i1 : 5;  /* bit[0-4]  : TD软件配置的天线1的I路数据移位bit数，配置范围10~19。
                                                           C模不配置。 */
        unsigned long  reserved_0     : 11; /* bit[5-15] : 保留 */
        unsigned long  dcoc_sftbit_q1 : 5;  /* bit[16-20]: TD软件配置的天线1的Q路数据移位bit数，配置范围10~19。
                                                           C模不配置。 */
        unsigned long  reserved_1     : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_DCOC_SFTBIT1_UNION;
#define WBBP_DCOC_SFTBIT1_dcoc_sftbit_i1_START  (0)
#define WBBP_DCOC_SFTBIT1_dcoc_sftbit_i1_END    (4)
#define WBBP_DCOC_SFTBIT1_dcoc_sftbit_q1_START  (16)
#define WBBP_DCOC_SFTBIT1_dcoc_sftbit_q1_END    (20)


/*****************************************************************************
 结构名    : WBBP_DCOC_SFTBIT2_UNION
 结构说明  : DCOC_SFTBIT2 寄存器结构定义。地址偏移量:0xE28，初值:0x000E000E，宽度:32
 寄存器说明: dcoc的天线2的i路和q路数据移位bit数
*****************************************************************************/
typedef union
{
    unsigned long      dcoc_sftbit2_reg;
    struct
    {
        unsigned long  dcoc_sftbit_i2 : 5;  /* bit[0-4]  : TD软件配置的天线2的I路数据移位bit数，配置范围10~19。
                                                           C模不配置。 */
        unsigned long  reserved_0     : 11; /* bit[5-15] : 保留 */
        unsigned long  dcoc_sftbit_q2 : 5;  /* bit[16-20]: TD软件配置的天线2的Q路数据移位bit数，配置范围10~19。
                                                           C模不配置。 */
        unsigned long  reserved_1     : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_DCOC_SFTBIT2_UNION;
#define WBBP_DCOC_SFTBIT2_dcoc_sftbit_i2_START  (0)
#define WBBP_DCOC_SFTBIT2_dcoc_sftbit_i2_END    (4)
#define WBBP_DCOC_SFTBIT2_dcoc_sftbit_q2_START  (16)
#define WBBP_DCOC_SFTBIT2_dcoc_sftbit_q2_END    (20)


/*****************************************************************************
 结构名    : WBBP_DCOC_CFG_VLD_UNION
 结构说明  : DCOC_CFG_VLD 寄存器结构定义。地址偏移量:0xE2C，初值:0x00000000，宽度:32
 寄存器说明: 软件配置dcocdc值有效信号
*****************************************************************************/
typedef union
{
    unsigned long      dcoc_cfg_vld_reg;
    struct
    {
        unsigned long  dcoc_adc_vld : 1;  /* bit[0]   : TD软件配置的dcoc的DC值是否生效标志。
                                                        1'b0，不生效；
                                                        1'b1，生效。
                                                        C模不配置。 */
        unsigned long  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DCOC_CFG_VLD_UNION;
#define WBBP_DCOC_CFG_VLD_dcoc_adc_vld_START  (0)
#define WBBP_DCOC_CFG_VLD_dcoc_adc_vld_END    (0)


/*****************************************************************************
 结构名    : WBBP_FIR_SFT_UNION
 结构说明  : FIR_SFT 寄存器结构定义。地址偏移量:0xE30，初值:0x0000000B，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      fir_sft_reg;
    struct
    {
        unsigned long  fir_rx_sftbit : 4;  /* bit[0-3] : 下采样滤波器内部累加器移位bit数。
                                                         上电之后只配置一次，配置范围10~13。
                                                         C模不配置。 */
        unsigned long  reserved      : 28; /* bit[4-31]: 保留 */
    } reg;
} WBBP_FIR_SFT_UNION;
#define WBBP_FIR_SFT_fir_rx_sftbit_START  (0)
#define WBBP_FIR_SFT_fir_rx_sftbit_END    (3)


/*****************************************************************************
 结构名    : WBBP_RX_CNT_UNION
 结构说明  : RX_CNT 寄存器结构定义。地址偏移量:0xE34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rx_cnt_reg;
    struct
    {
        unsigned long  para_force  : 1;  /* bit[0]    : 参数强制生效使能。
                                                        C模不配置。 */
        unsigned long  reserved_0  : 2;  /* bit[1-2]  : 保留 */
        unsigned long  dft_func_en : 1;  /* bit[3]    : rx_cnt计数使能，高电平有效，低电平时rx_cnt清零。
                                                        C模不配置。 */
        unsigned long  rx_cnt      : 16; /* bit[4-19] : ad_on包络个数，可维可测。 */
        unsigned long  reserved_1  : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_RX_CNT_UNION;
#define WBBP_RX_CNT_para_force_START   (0)
#define WBBP_RX_CNT_para_force_END     (0)
#define WBBP_RX_CNT_dft_func_en_START  (3)
#define WBBP_RX_CNT_dft_func_en_END    (3)
#define WBBP_RX_CNT_rx_cnt_START       (4)
#define WBBP_RX_CNT_rx_cnt_END         (19)


/*****************************************************************************
 结构名    : WBBP_DACGT1_GAIN1_UNION
 结构说明  : DACGT1_GAIN1 寄存器结构定义。地址偏移量:0xE40，初值:0x00000000，宽度:32
 寄存器说明: 天线1的pre_dagct增益
*****************************************************************************/
typedef union
{
    unsigned long      dacgt1_gain1_reg;
    struct
    {
        unsigned long  dagct1_gain1 : 10; /* bit[0-9]  : TD软件配置的天线1的pre_dagct增益，有符号数，有效范围[-336,336]。
                                                         C模不配置。 */
        unsigned long  reserved     : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DACGT1_GAIN1_UNION;
#define WBBP_DACGT1_GAIN1_dagct1_gain1_START  (0)
#define WBBP_DACGT1_GAIN1_dagct1_gain1_END    (9)


/*****************************************************************************
 结构名    : WBBP_DACGT1_GAIN2_UNION
 结构说明  : DACGT1_GAIN2 寄存器结构定义。地址偏移量:0xE44，初值:0x00000000，宽度:32
 寄存器说明: 天线2的pre_dagct增益
*****************************************************************************/
typedef union
{
    unsigned long      dacgt1_gain2_reg;
    struct
    {
        unsigned long  dagct1_gain2 : 10; /* bit[0-9]  : TD软件配置的天线2的pre_dagct增益，有符号数，有效范围[-336,336]。
                                                         C模不配置。 */
        unsigned long  reserved     : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DACGT1_GAIN2_UNION;
#define WBBP_DACGT1_GAIN2_dagct1_gain2_START  (0)
#define WBBP_DACGT1_GAIN2_dagct1_gain2_END    (9)


/*****************************************************************************
 结构名    : WBBP_DACGT2_GAIN1_UNION
 结构说明  : DACGT2_GAIN1 寄存器结构定义。地址偏移量:0xE48，初值:0x00000000，宽度:32
 寄存器说明: 天线1的post_dagct增益
*****************************************************************************/
typedef union
{
    unsigned long      dacgt2_gain1_reg;
    struct
    {
        unsigned long  dagct2_gain1 : 10; /* bit[0-9]  : TD软件配置的天线1的post_dagct增益，有符号数，有效范围[-336,336]。
                                                         C模不配置。 */
        unsigned long  reserved     : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DACGT2_GAIN1_UNION;
#define WBBP_DACGT2_GAIN1_dagct2_gain1_START  (0)
#define WBBP_DACGT2_GAIN1_dagct2_gain1_END    (9)


/*****************************************************************************
 结构名    : WBBP_DACGT2_GAIN2_UNION
 结构说明  : DACGT2_GAIN2 寄存器结构定义。地址偏移量:0xE4C，初值:0x00000000，宽度:32
 寄存器说明: 天线2的post_dagct增益
*****************************************************************************/
typedef union
{
    unsigned long      dacgt2_gain2_reg;
    struct
    {
        unsigned long  dagct2_gain2 : 10; /* bit[0-9]  : TD软件配置的天线2的post_dagct增益，有符号数，有效范围[-336,336]。
                                                         C模不配置。 */
        unsigned long  reserved     : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DACGT2_GAIN2_UNION;
#define WBBP_DACGT2_GAIN2_dagct2_gain2_START  (0)
#define WBBP_DACGT2_GAIN2_dagct2_gain2_END    (9)


/*****************************************************************************
 结构名    : WBBP_RXIQ_THRES_UNION
 结构说明  : RXIQ_THRES 寄存器结构定义。地址偏移量:0xE50，初值:0x00000014，宽度:32
 寄存器说明: rxiq校准因子更新阈值
*****************************************************************************/
typedef union
{
    unsigned long      rxiq_thres_reg;
    struct
    {
        unsigned long  rxiq_thres : 6;  /* bit[0-5] : W和TD rxiq校准因子更新阈值。取值范围[11,63]。W典型配置0xb。 */
        unsigned long  reserved   : 26; /* bit[6-31]: 保留 */
    } reg;
} WBBP_RXIQ_THRES_UNION;
#define WBBP_RXIQ_THRES_rxiq_thres_START  (0)
#define WBBP_RXIQ_THRES_rxiq_thres_END    (5)


/*****************************************************************************
 结构名    : WBBP_RXIQ_SFTBIT0_UNION
 结构说明  : RXIQ_SFTBIT0 寄存器结构定义。地址偏移量:0xE54，初值:0x00010B0B，宽度:32
 寄存器说明: 天线1的rxiq计算因子的移位的bit数
*****************************************************************************/
typedef union
{
    unsigned long      rxiq_sftbit0_reg;
    struct
    {
        unsigned long  rxiq_sftbit_a1 : 4;  /* bit[0-3]  : 天线1的rxiq移位的bit数ShiftA。取值范围[10,15]。 */
        unsigned long  reserved_0     : 4;  /* bit[4-7]  : 保留 */
        unsigned long  rxiq_sftbit_b1 : 4;  /* bit[8-11] : 天线1的rxiq移位的bit数ShiftB。取值范围[9,15]。 */
        unsigned long  reserved_1     : 4;  /* bit[12-15]: 保留 */
        unsigned long  rxiq_sftbit_c1 : 2;  /* bit[16-17]: 天线1的rxiq移位的bit数ShiftC。取值范围[0,3]。 */
        unsigned long  reserved_2     : 14; /* bit[18-31]: 保留 */
    } reg;
} WBBP_RXIQ_SFTBIT0_UNION;
#define WBBP_RXIQ_SFTBIT0_rxiq_sftbit_a1_START  (0)
#define WBBP_RXIQ_SFTBIT0_rxiq_sftbit_a1_END    (3)
#define WBBP_RXIQ_SFTBIT0_rxiq_sftbit_b1_START  (8)
#define WBBP_RXIQ_SFTBIT0_rxiq_sftbit_b1_END    (11)
#define WBBP_RXIQ_SFTBIT0_rxiq_sftbit_c1_START  (16)
#define WBBP_RXIQ_SFTBIT0_rxiq_sftbit_c1_END    (17)


/*****************************************************************************
 结构名    : WBBP_RXIQ_SFTBIT1_UNION
 结构说明  : RXIQ_SFTBIT1 寄存器结构定义。地址偏移量:0xE58，初值:0x00010B0B，宽度:32
 寄存器说明: 天线2的rxiq计算因子的移位的bit数
*****************************************************************************/
typedef union
{
    unsigned long      rxiq_sftbit1_reg;
    struct
    {
        unsigned long  rxiq_sftbit_a2 : 4;  /* bit[0-3]  : 天线2的rxiq移位的bit数ShiftA。取值范围[10,15]。 */
        unsigned long  reserved_0     : 4;  /* bit[4-7]  : 保留 */
        unsigned long  rxiq_sftbit_b2 : 4;  /* bit[8-11] : 天线2的rxiq移位的bit数ShiftB。取值范围[9,15]。 */
        unsigned long  reserved_1     : 4;  /* bit[12-15]: 保留 */
        unsigned long  rxiq_sftbit_c2 : 2;  /* bit[16-17]: 天线2的rxiq移位的bit数ShiftC。取值范围[0,3]。 */
        unsigned long  reserved_2     : 14; /* bit[18-31]: 保留 */
    } reg;
} WBBP_RXIQ_SFTBIT1_UNION;
#define WBBP_RXIQ_SFTBIT1_rxiq_sftbit_a2_START  (0)
#define WBBP_RXIQ_SFTBIT1_rxiq_sftbit_a2_END    (3)
#define WBBP_RXIQ_SFTBIT1_rxiq_sftbit_b2_START  (8)
#define WBBP_RXIQ_SFTBIT1_rxiq_sftbit_b2_END    (11)
#define WBBP_RXIQ_SFTBIT1_rxiq_sftbit_c2_START  (16)
#define WBBP_RXIQ_SFTBIT1_rxiq_sftbit_c2_END    (17)


/*****************************************************************************
 结构名    : WBBP_RXIQ_LIMIT_UNION
 结构说明  : RXIQ_LIMIT 寄存器结构定义。地址偏移量:0xE5C，初值:0x03FF01FF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rxiq_limit_reg;
    struct
    {
        unsigned long  dsp_rxiq_a_limit : 9;  /* bit[0-8]  : ak值幅度限制，无符号数。 */
        unsigned long  reserved_0       : 7;  /* bit[9-15] : 保留 */
        unsigned long  dsp_rxiq_p_limit : 10; /* bit[16-25]: pk值幅度限制，无符号数。 */
        unsigned long  reserved_1       : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_RXIQ_LIMIT_UNION;
#define WBBP_RXIQ_LIMIT_dsp_rxiq_a_limit_START  (0)
#define WBBP_RXIQ_LIMIT_dsp_rxiq_a_limit_END    (8)
#define WBBP_RXIQ_LIMIT_dsp_rxiq_p_limit_START  (16)
#define WBBP_RXIQ_LIMIT_dsp_rxiq_p_limit_END    (25)


/*****************************************************************************
 结构名    : WBBP_RXIQ_WEIGHT_UNION
 结构说明  : RXIQ_WEIGHT 寄存器结构定义。地址偏移量:0xE60，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rxiq_weight_reg;
    struct
    {
        unsigned long  dsp_rxiq_ap_weight : 3;  /* bit[0-2] : AP权重，0~4对应链路16,8,4,2,1。 */
        unsigned long  reserved_0         : 1;  /* bit[3]   : 保留 */
        unsigned long  dsp_rxiq_vld       : 1;  /* bit[4]   : TD软件配置的rxiq值是否生效标志。
                                                              1'b0，不生效；
                                                              1'b1，生效。 */
        unsigned long  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} WBBP_RXIQ_WEIGHT_UNION;
#define WBBP_RXIQ_WEIGHT_dsp_rxiq_ap_weight_START  (0)
#define WBBP_RXIQ_WEIGHT_dsp_rxiq_ap_weight_END    (2)
#define WBBP_RXIQ_WEIGHT_dsp_rxiq_vld_START        (4)
#define WBBP_RXIQ_WEIGHT_dsp_rxiq_vld_END          (4)


/*****************************************************************************
 结构名    : WBBP_RSSI_X_SFTBIT_UNION
 结构说明  : RSSI_X_SFTBIT 寄存器结构定义。地址偏移量:0xE64，初值:0x00000004，宽度:32
 寄存器说明: rssi移位X的bit数
*****************************************************************************/
typedef union
{
    unsigned long      rssi_x_sftbit_reg;
    struct
    {
        unsigned long  rssi_xsbit_nb : 5;  /* bit[0-4]  : rssi移位X的bit数。取值范围[3,10]。
                                                          C模不配置。 */
        unsigned long  rssi_xsbit_wb : 5;  /* bit[5-9]  : rssi移位X的bit数。取值范围[3,10]。
                                                          C模不配置。 */
        unsigned long  reserved      : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_RSSI_X_SFTBIT_UNION;
#define WBBP_RSSI_X_SFTBIT_rssi_xsbit_nb_START  (0)
#define WBBP_RSSI_X_SFTBIT_rssi_xsbit_nb_END    (4)
#define WBBP_RSSI_X_SFTBIT_rssi_xsbit_wb_START  (5)
#define WBBP_RSSI_X_SFTBIT_rssi_xsbit_wb_END    (9)


/*****************************************************************************
 结构名    : WBBP_RSSI_M_SFTBIT_UNION
 结构说明  : RSSI_M_SFTBIT 寄存器结构定义。地址偏移量:0xE68，初值:0x000A0806，宽度:32
 寄存器说明: 不同数据速率时rssi移位M的bit数
*****************************************************************************/
typedef union
{
    unsigned long      rssi_m_sftbit_reg;
    struct
    {
        unsigned long  rssi_msbit_128  : 5;  /* bit[0-4]  : rssi移位M的bit数。取值范围[6,17]。
                                                            C模不配置。 */
        unsigned long  reserved_0      : 3;  /* bit[5-7]  : 保留 */
        unsigned long  rssi_msbit_512  : 5;  /* bit[8-12] : rssi移位M的bit数。取值范围[6,17]。
                                                            C模不配置。 */
        unsigned long  reserved_1      : 3;  /* bit[13-15]: 保留 */
        unsigned long  rssi_msbit_1536 : 5;  /* bit[16-20]: rssi移位M的bit数。取值范围[6,17]。
                                                            C模不配置。 */
        unsigned long  reserved_2      : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_RSSI_M_SFTBIT_UNION;
#define WBBP_RSSI_M_SFTBIT_rssi_msbit_128_START   (0)
#define WBBP_RSSI_M_SFTBIT_rssi_msbit_128_END     (4)
#define WBBP_RSSI_M_SFTBIT_rssi_msbit_512_START   (8)
#define WBBP_RSSI_M_SFTBIT_rssi_msbit_512_END     (12)
#define WBBP_RSSI_M_SFTBIT_rssi_msbit_1536_START  (16)
#define WBBP_RSSI_M_SFTBIT_rssi_msbit_1536_END    (20)


/*****************************************************************************
 结构名    : WBBP_RSSI1_DATA0_UNION
 结构说明  : RSSI1_DATA0 寄存器结构定义。地址偏移量:0xE90，初值:0x00000000，宽度:32
 寄存器说明: 上报的rssi1天线1的统计值
*****************************************************************************/
typedef union
{
    unsigned long      rssi1_data0_reg;
    struct
    {
        unsigned long  rssi1_data1 : 25; /* bit[0-24] : 逻辑上报的rssi1天线1的统计值。 */
        unsigned long  reserved    : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_RSSI1_DATA0_UNION;
#define WBBP_RSSI1_DATA0_rssi1_data1_START  (0)
#define WBBP_RSSI1_DATA0_rssi1_data1_END    (24)


/*****************************************************************************
 结构名    : WBBP_RSSI1_DATA1_UNION
 结构说明  : RSSI1_DATA1 寄存器结构定义。地址偏移量:0xE94，初值:0x00000000，宽度:32
 寄存器说明: 上报的rssi1天线2的统计值
*****************************************************************************/
typedef union
{
    unsigned long      rssi1_data1_reg;
    struct
    {
        unsigned long  rssi1_data2 : 25; /* bit[0-24] : 逻辑上报的rssi1天线2的统计值。 */
        unsigned long  reserved    : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_RSSI1_DATA1_UNION;
#define WBBP_RSSI1_DATA1_rssi1_data2_START  (0)
#define WBBP_RSSI1_DATA1_rssi1_data2_END    (24)


/*****************************************************************************
 结构名    : WBBP_RSSI2_DATA0_UNION
 结构说明  : RSSI2_DATA0 寄存器结构定义。地址偏移量:0xE98，初值:0x00000000，宽度:32
 寄存器说明: 上报的rssi2天线1的统计值
*****************************************************************************/
typedef union
{
    unsigned long      rssi2_data0_reg;
    struct
    {
        unsigned long  rssi2_data1 : 25; /* bit[0-24] : 逻辑上报的rssi2天线1的统计值。 */
        unsigned long  reserved    : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_RSSI2_DATA0_UNION;
#define WBBP_RSSI2_DATA0_rssi2_data1_START  (0)
#define WBBP_RSSI2_DATA0_rssi2_data1_END    (24)


/*****************************************************************************
 结构名    : WBBP_RSSI2_DATA1_UNION
 结构说明  : RSSI2_DATA1 寄存器结构定义。地址偏移量:0xE9C，初值:0x00000000，宽度:32
 寄存器说明: 上报的rssi2天线2的统计值
*****************************************************************************/
typedef union
{
    unsigned long      rssi2_data1_reg;
    struct
    {
        unsigned long  rssi2_data2 : 25; /* bit[0-24] : 逻辑上报的rssi2天线2的统计值。 */
        unsigned long  reserved    : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_RSSI2_DATA1_UNION;
#define WBBP_RSSI2_DATA1_rssi2_data2_START  (0)
#define WBBP_RSSI2_DATA1_rssi2_data2_END    (24)


/*****************************************************************************
 结构名    : WBBP_DBG_RPT_AT1_UNION
 结构说明  : DBG_RPT_AT1 寄存器结构定义。地址偏移量:0xEA0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_rpt_at1_reg;
    struct
    {
        unsigned long  at1_dbg_data : 29; /* bit[0-28] : AT1 dbg采数上报。
                                                         [11:0] Q路数据
                                                         [23:12] I路数据
                                                         [24] tds_data_vld
                                                         [25] tds_ad_on1
                                                         [26] 天线采数使能 */
        unsigned long  reserved     : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_DBG_RPT_AT1_UNION;
#define WBBP_DBG_RPT_AT1_at1_dbg_data_START  (0)
#define WBBP_DBG_RPT_AT1_at1_dbg_data_END    (28)


/*****************************************************************************
 结构名    : WBBP_DBG_RPT_AT2_UNION
 结构说明  : DBG_RPT_AT2 寄存器结构定义。地址偏移量:0xEA4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_rpt_at2_reg;
    struct
    {
        unsigned long  at2_dbg_data : 29; /* bit[0-28] : AT2 dbg采数上报。
                                                         [11:0] Q路数据
                                                         [23:12] I路数据
                                                         [24] tds_data_vld
                                                         [25] tds_ad_on1
                                                         [26] 天线采数使能 */
        unsigned long  reserved     : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_DBG_RPT_AT2_UNION;
#define WBBP_DBG_RPT_AT2_at2_dbg_data_START  (0)
#define WBBP_DBG_RPT_AT2_at2_dbg_data_END    (28)


/*****************************************************************************
 结构名    : WBBP_C_WORK_MODE_UNION
 结构说明  : C_WORK_MODE 寄存器结构定义。地址偏移量:0xF00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_work_mode_reg;
    struct
    {
        unsigned long  c_work_mode      : 1;  /* bit[0]   : 下行C模模式选择。0，初始模式；1，正常模式。 */
        unsigned long  dl_c_scfilter_en : 1;  /* bit[1]   : 下行W模和C模sc filter使能信号。0：关闭；1：打开。W模式下dl_c_scfilter_en或者多径的sc_filter使能都能够打开sc filter。 */
        unsigned long  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_C_WORK_MODE_UNION;
#define WBBP_C_WORK_MODE_c_work_mode_START       (0)
#define WBBP_C_WORK_MODE_c_work_mode_END         (0)
#define WBBP_C_WORK_MODE_dl_c_scfilter_en_START  (1)
#define WBBP_C_WORK_MODE_dl_c_scfilter_en_END    (1)


/*****************************************************************************
 结构名    : WBBP_C_AAGC_STATE_CHANGE_AT1_UNION
 结构说明  : C_AAGC_STATE_CHANGE_AT1 寄存器结构定义。地址偏移量:0xF04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_aagc_state_change_at1_reg;
    struct
    {
        unsigned long  c_aagc_state_change_at1 : 1;  /* bit[0]   : C模下天线1档位切换指示脉冲。 */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_C_AAGC_STATE_CHANGE_AT1_UNION;
#define WBBP_C_AAGC_STATE_CHANGE_AT1_c_aagc_state_change_at1_START  (0)
#define WBBP_C_AAGC_STATE_CHANGE_AT1_c_aagc_state_change_at1_END    (0)


/*****************************************************************************
 结构名    : WBBP_C_AAGC_STATE_CHANGE_AT2_UNION
 结构说明  : C_AAGC_STATE_CHANGE_AT2 寄存器结构定义。地址偏移量:0xF08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_aagc_state_change_at2_reg;
    struct
    {
        unsigned long  c_aagc_state_change_at2 : 1;  /* bit[0]   : C模下天线2档位切换指示脉冲。 */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_C_AAGC_STATE_CHANGE_AT2_UNION;
#define WBBP_C_AAGC_STATE_CHANGE_AT2_c_aagc_state_change_at2_START  (0)
#define WBBP_C_AAGC_STATE_CHANGE_AT2_c_aagc_state_change_at2_END    (0)


/*****************************************************************************
 结构名    : WBBP_C_DRSSI_25DB_AT1_UNION
 结构说明  : C_DRSSI_25DB_AT1 寄存器结构定义。地址偏移量:0xF0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_drssi_25db_at1_reg;
    struct
    {
        unsigned long  c_drssi_25db_at1 : 8;  /* bit[0-7] : DRSSI 0.25dB值，是DAGC8bit用于查找表求量化步阶MulFactor的ROM地址。AGC刚工作的时候，以此值作为初值。 */
        unsigned long  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} WBBP_C_DRSSI_25DB_AT1_UNION;
#define WBBP_C_DRSSI_25DB_AT1_c_drssi_25db_at1_START  (0)
#define WBBP_C_DRSSI_25DB_AT1_c_drssi_25db_at1_END    (7)


/*****************************************************************************
 结构名    : WBBP_C_DRSSI_25DB_AT2_UNION
 结构说明  : C_DRSSI_25DB_AT2 寄存器结构定义。地址偏移量:0xF10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_drssi_25db_at2_reg;
    struct
    {
        unsigned long  c_drssi_25db_at2 : 8;  /* bit[0-7] : DRSSI 0.25dB值，是DAGC8bit用于查找表求量化步阶MulFactor的ROM地址。AGC刚工作的时候，以此值作为初值。 */
        unsigned long  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} WBBP_C_DRSSI_25DB_AT2_UNION;
#define WBBP_C_DRSSI_25DB_AT2_c_drssi_25db_at2_START  (0)
#define WBBP_C_DRSSI_25DB_AT2_c_drssi_25db_at2_END    (7)


/*****************************************************************************
 结构名    : WBBP_C_FREQ_SWITCH_CFG_UNION
 结构说明  : C_FREQ_SWITCH_CFG 寄存器结构定义。地址偏移量:0xF14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_freq_switch_cfg_reg;
    struct
    {
        unsigned long  c_freq_switch_time   : 12; /* bit[0-11] : C模本频指示切换在base_cnt上的时刻，单位为chip。
                                                                 注：base_cnt计数从0chip开始记起。 */
        unsigned long  reserved_0           : 4;  /* bit[12-15]: 保留 */
        unsigned long  c_freq_switch_type   : 1;  /* bit[16]   : 本异频切换类型。0，本频切换到异频；1，异频切换到本频。 */
        unsigned long  c_freq_switch_update : 1;  /* bit[17]   : C模本频指示切换控制脉冲。 */
        unsigned long  reserved_1           : 14; /* bit[18-31]: 保留 */
    } reg;
} WBBP_C_FREQ_SWITCH_CFG_UNION;
#define WBBP_C_FREQ_SWITCH_CFG_c_freq_switch_time_START    (0)
#define WBBP_C_FREQ_SWITCH_CFG_c_freq_switch_time_END      (11)
#define WBBP_C_FREQ_SWITCH_CFG_c_freq_switch_type_START    (16)
#define WBBP_C_FREQ_SWITCH_CFG_c_freq_switch_type_END      (16)
#define WBBP_C_FREQ_SWITCH_CFG_c_freq_switch_update_START  (17)
#define WBBP_C_FREQ_SWITCH_CFG_c_freq_switch_update_END    (17)


/*****************************************************************************
 结构名    : WBBP_DSP_RXIQ_AHEAD_TIME_UNION
 结构说明  : DSP_RXIQ_AHEAD_TIME 寄存器结构定义。地址偏移量:0xF18，初值:0x00000020，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_rxiq_ahead_time_reg;
    struct
    {
        unsigned long  dsp_rxiq_ahead_time : 14; /* bit[0-13] : DSP配置RXIQ提前启动时间，用于和后续模块DRSSI在时间上对齐，配置精度为样点的整数倍。W模式要求配置值为17'd32。（V9为固定256个clk） */
        unsigned long  reserved            : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_DSP_RXIQ_AHEAD_TIME_UNION;
#define WBBP_DSP_RXIQ_AHEAD_TIME_dsp_rxiq_ahead_time_START  (0)
#define WBBP_DSP_RXIQ_AHEAD_TIME_dsp_rxiq_ahead_time_END    (13)


/*****************************************************************************
 结构名    : WBBP_C_DRSSI_TIME_UNION
 结构说明  : C_DRSSI_TIME 寄存器结构定义。地址偏移量:0xF1C，初值:0x03FF0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_drssi_time_reg;
    struct
    {
        unsigned long  c_drssi_start_time : 11; /* bit[0-10] : C模DRSSI统计在PCG或时隙内的起始时刻，单位chip。
                                                               1X和EVDO建议配置0。 */
        unsigned long  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned long  c_drssi_stop_time  : 11; /* bit[16-26]: C模DRSSI统计在PCG或时隙内的结束时刻，单位chip。
                                                               1X配置小于1536(十进制)。
                                                               EVDO建议配置1648(十进制)。 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_C_DRSSI_TIME_UNION;
#define WBBP_C_DRSSI_TIME_c_drssi_start_time_START  (0)
#define WBBP_C_DRSSI_TIME_c_drssi_start_time_END    (10)
#define WBBP_C_DRSSI_TIME_c_drssi_stop_time_START   (16)
#define WBBP_C_DRSSI_TIME_c_drssi_stop_time_END     (26)


/*****************************************************************************
 结构名    : WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT1_UNION
 结构说明  : C_DRSSI_LINEAR_CHIP_NUM_AT1 寄存器结构定义。地址偏移量:0xF24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_drssi_linear_chip_num_at1_reg;
    struct
    {
        unsigned long  drssi_linear_chip_num_at1 : 12; /* bit[0-11] : 天线1 DRSSI上报线性值统计长度，单位chip。 */
        unsigned long  reserved                  : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT1_UNION;
#define WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT1_drssi_linear_chip_num_at1_START  (0)
#define WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT1_drssi_linear_chip_num_at1_END    (11)


/*****************************************************************************
 结构名    : WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT2_UNION
 结构说明  : C_DRSSI_LINEAR_CHIP_NUM_AT2 寄存器结构定义。地址偏移量:0xF2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_drssi_linear_chip_num_at2_reg;
    struct
    {
        unsigned long  drssi_linear_chip_num_at2 : 12; /* bit[0-11] : 天线2 DRSSI上报线性值统计长度，单位chip。 */
        unsigned long  reserved                  : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT2_UNION;
#define WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT2_drssi_linear_chip_num_at2_START  (0)
#define WBBP_C_DRSSI_LINEAR_CHIP_NUM_AT2_drssi_linear_chip_num_at2_END    (11)


/*****************************************************************************
 结构名    : WBBP_DSP_TED_STEP_EN_UNION
 结构说明  : DSP_TED_STEP_EN 寄存器结构定义。地址偏移量:0xF30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ted_step_en_reg;
    struct
    {
        unsigned long  dsp_ted_step_en : 1;  /* bit[0]   : 采样纠偏检测步长强配使能，C模和强配功能下使用。 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_TED_STEP_EN_UNION;
#define WBBP_DSP_TED_STEP_EN_dsp_ted_step_en_START  (0)
#define WBBP_DSP_TED_STEP_EN_dsp_ted_step_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_TED_STEP_UPDATE_UNION
 结构说明  : DSP_TED_STEP_UPDATE 寄存器结构定义。地址偏移量:0xF34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ted_step_update_reg;
    struct
    {
        unsigned long  dsp_ted_step_update : 1;  /* bit[0]   : 采样纠偏检测步长强配更新指示。 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_TED_STEP_UPDATE_UNION;
#define WBBP_DSP_TED_STEP_UPDATE_dsp_ted_step_update_START  (0)
#define WBBP_DSP_TED_STEP_UPDATE_dsp_ted_step_update_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_TED_STEP_UNION
 结构说明  : DSP_TED_STEP 寄存器结构定义。地址偏移量:0xF38，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ted_step_reg;
    struct
    {
        unsigned long  dsp_ted_step_rx1_mc1 : 8;  /* bit[0-7]  : 天线1主载波采样纠偏检测步长。8bit有符号数。 */
        unsigned long  dsp_ted_step_rx1_mc2 : 8;  /* bit[8-15] : 天线1辅载波采样纠偏检测步长。8bit有符号数。 */
        unsigned long  dsp_ted_step_rx2_mc1 : 8;  /* bit[16-23]: 天线2主载波采样纠偏检测步长。8bit有符号数。 */
        unsigned long  dsp_ted_step_rx2_mc2 : 8;  /* bit[24-31]: 天线2辅载波采样纠偏检测步长。8bit有符号数。 */
    } reg;
} WBBP_DSP_TED_STEP_UNION;
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx1_mc1_START  (0)
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx1_mc1_END    (7)
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx1_mc2_START  (8)
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx1_mc2_END    (15)
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx2_mc1_START  (16)
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx2_mc1_END    (23)
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx2_mc2_START  (24)
#define WBBP_DSP_TED_STEP_dsp_ted_step_rx2_mc2_END    (31)


/*****************************************************************************
 结构名    : WBBP_DSP_SC_DSP_CFG_EN_UNION
 结构说明  : DSP_SC_DSP_CFG_EN 寄存器结构定义。地址偏移量:0xF3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sc_dsp_cfg_en_reg;
    struct
    {
        unsigned long  dsp_sc_offset_en : 1;  /* bit[0]   : DSP强配采样偏差值使能。 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_SC_DSP_CFG_EN_UNION;
#define WBBP_DSP_SC_DSP_CFG_EN_dsp_sc_offset_en_START  (0)
#define WBBP_DSP_SC_DSP_CFG_EN_dsp_sc_offset_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_SC_DSP_CFG_UPDATE_UNION
 结构说明  : DSP_SC_DSP_CFG_UPDATE 寄存器结构定义。地址偏移量:0xF40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sc_dsp_cfg_update_reg;
    struct
    {
        unsigned long  dsp_sc_offset_update : 1;  /* bit[0]   : DSP配置采样偏差值更新脉冲。 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_SC_DSP_CFG_UPDATE_UNION;
#define WBBP_DSP_SC_DSP_CFG_UPDATE_dsp_sc_offset_update_START  (0)
#define WBBP_DSP_SC_DSP_CFG_UPDATE_dsp_sc_offset_update_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_SC_OFFSET_AT1_UNION
 结构说明  : DSP_SC_OFFSET_AT1 寄存器结构定义。地址偏移量:0xF44，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sc_offset_at1_reg;
    struct
    {
        unsigned long  dsp_sc_offset_rx1_mc1 : 11; /* bit[0-10] : 天线1主载波DSP配置采样偏差值。 */
        unsigned long  reserved_0            : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_sc_offset_rx1_mc2 : 11; /* bit[16-26]: 天线1辅载波DSP配置采样偏差值。 */
        unsigned long  reserved_1            : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_SC_OFFSET_AT1_UNION;
#define WBBP_DSP_SC_OFFSET_AT1_dsp_sc_offset_rx1_mc1_START  (0)
#define WBBP_DSP_SC_OFFSET_AT1_dsp_sc_offset_rx1_mc1_END    (10)
#define WBBP_DSP_SC_OFFSET_AT1_dsp_sc_offset_rx1_mc2_START  (16)
#define WBBP_DSP_SC_OFFSET_AT1_dsp_sc_offset_rx1_mc2_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_SC_OFFSET_AT2_UNION
 结构说明  : DSP_SC_OFFSET_AT2 寄存器结构定义。地址偏移量:0xF48，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sc_offset_at2_reg;
    struct
    {
        unsigned long  dsp_sc_offset_rx2_mc1 : 11; /* bit[0-10] : 天线2主载波DSP配置采样偏差值。 */
        unsigned long  reserved_0            : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_sc_offset_rx2_mc2 : 11; /* bit[16-26]: 天线2辅载波DSP配置采样偏差值。 */
        unsigned long  reserved_1            : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_SC_OFFSET_AT2_UNION;
#define WBBP_DSP_SC_OFFSET_AT2_dsp_sc_offset_rx2_mc1_START  (0)
#define WBBP_DSP_SC_OFFSET_AT2_dsp_sc_offset_rx2_mc1_END    (10)
#define WBBP_DSP_SC_OFFSET_AT2_dsp_sc_offset_rx2_mc2_START  (16)
#define WBBP_DSP_SC_OFFSET_AT2_dsp_sc_offset_rx2_mc2_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_DLFE_SINGLE_TCXO_CFG_UNION
 结构说明  : DSP_DLFE_SINGLE_TCXO_CFG 寄存器结构定义。地址偏移量:0xF4C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_dlfe_single_tcxo_cfg_reg;
    struct
    {
        unsigned long  dsp_dlfe_base_cnt_sel        : 1;  /* bit[0]   : 下行前端纠偏fifo前的base_cnt来源：
                                                                        0，选择base_cnt；
                                                                        1，选择base_cnt_abb。
                                                                        W和C配置1，TDS下必须配置为0。 */
        unsigned long  dsp_dlfe_del_add_en          : 1;  /* bit[1]   : 删加点功能打开标志：0，关闭删加点功能；1，为开启删加点功能，此时sc_cal模块的删加点计算功能打开。 */
        unsigned long  dsp_dlfe_sc_cal_en           : 1;  /* bit[2]   : 采样偏差换算工作使能。 */
        unsigned long  dsp_fw_cfg_en                : 1;  /* bit[3]   : DSP配置AFC频偏值使能。 */
        unsigned long  dsp_freq_error_nco_fw_cfg_en : 1;  /* bit[4]   : 强行配置频偏校正所用NCO频率值使能。 */
        unsigned long  dsp_dlfe_nco_en              : 1;  /* bit[5]   : 频率校正NCO工作使能，TDS模式和非单TCXO模式下需要配置为0。 */
        unsigned long  dsp_dlfe_freq_error_en       : 1;  /* bit[6]   : 频偏校正使能。 */
        unsigned long  dsp_dlfe_fifo_en             : 1;  /* bit[7]   : 下行单TCXO异步fifo使能。 */
        unsigned long  dsp_dl_sc_cal_para_en        : 1;  /* bit[8]   : sc_filter模块的参数来源：
                                                                        1'b1：参数来源于sc_cal；
                                                                        1'b0：W参数来源于多径或强配，TDS和C模来源于强配。 */
        unsigned long  reserved                     : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_DSP_DLFE_SINGLE_TCXO_CFG_UNION;
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_base_cnt_sel_START         (0)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_base_cnt_sel_END           (0)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_del_add_en_START           (1)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_del_add_en_END             (1)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_sc_cal_en_START            (2)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_sc_cal_en_END              (2)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_fw_cfg_en_START                 (3)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_fw_cfg_en_END                   (3)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_freq_error_nco_fw_cfg_en_START  (4)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_freq_error_nco_fw_cfg_en_END    (4)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_nco_en_START               (5)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_nco_en_END                 (5)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_freq_error_en_START        (6)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_freq_error_en_END          (6)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_fifo_en_START              (7)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dlfe_fifo_en_END                (7)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dl_sc_cal_para_en_START         (8)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CFG_dsp_dl_sc_cal_para_en_END           (8)


/*****************************************************************************
 结构名    : WBBP_DSP_DLFE_SINGLE_TCXO_UPDATE_UNION
 结构说明  : DSP_DLFE_SINGLE_TCXO_UPDATE 寄存器结构定义。地址偏移量:0xF50，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_dlfe_single_tcxo_update_reg;
    struct
    {
        unsigned long  dsp_fw_update : 1;  /* bit[0]   : DSP配置AFC频偏值更新脉冲，当DSP配置AFC频偏值之后再配置更新脉冲，使频偏配置生效。 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_DLFE_SINGLE_TCXO_UPDATE_UNION;
#define WBBP_DSP_DLFE_SINGLE_TCXO_UPDATE_dsp_fw_update_START  (0)
#define WBBP_DSP_DLFE_SINGLE_TCXO_UPDATE_dsp_fw_update_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_DLFE_SINGLE_TCXO_CLR_UNION
 结构说明  : DSP_DLFE_SINGLE_TCXO_CLR 寄存器结构定义。地址偏移量:0xF54，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_dlfe_single_tcxo_clr_reg;
    struct
    {
        unsigned long  dsp_sc_cal_clr            : 1;  /* bit[0]   : 采样偏差换算积分器清零信号，可维可测使用。 */
        unsigned long  dsp_freq_error_nco_ph_clr : 1;  /* bit[1]   : 频率校正NCO相位清零脉冲，可维可测使用。 */
        unsigned long  reserved                  : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DSP_DLFE_SINGLE_TCXO_CLR_UNION;
#define WBBP_DSP_DLFE_SINGLE_TCXO_CLR_dsp_sc_cal_clr_START             (0)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CLR_dsp_sc_cal_clr_END               (0)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CLR_dsp_freq_error_nco_ph_clr_START  (1)
#define WBBP_DSP_DLFE_SINGLE_TCXO_CLR_dsp_freq_error_nco_ph_clr_END    (1)


/*****************************************************************************
 结构名    : WBBP_DSP_SC_CAL_PARA1_UNION
 结构说明  : DSP_SC_CAL_PARA1 寄存器结构定义。地址偏移量:0xF58，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sc_cal_para1_reg;
    struct
    {
        unsigned long  dsp_fw_cfg : 16; /* bit[0-15] : DSP配置AFC频偏值，16bit有符号数。 */
        unsigned long  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} WBBP_DSP_SC_CAL_PARA1_UNION;
#define WBBP_DSP_SC_CAL_PARA1_dsp_fw_cfg_START  (0)
#define WBBP_DSP_SC_CAL_PARA1_dsp_fw_cfg_END    (15)


/*****************************************************************************
 结构名    : WBBP_DSP_SC_CAL_PARA2_UNION
 结构说明  : DSP_SC_CAL_PARA2 寄存器结构定义。地址偏移量:0xF5C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sc_cal_para2_reg;
    struct
    {
        unsigned long  dsp_inter_fc_ratio : 15; /* bit[0-14] : DSP配置下行前端配置异频相对本频频率比Fc,inter/Fc（其中Fc,inter为异频频率），15bit无符号数。 */
        unsigned long  reserved           : 17; /* bit[15-31]: 保留 */
    } reg;
} WBBP_DSP_SC_CAL_PARA2_UNION;
#define WBBP_DSP_SC_CAL_PARA2_dsp_inter_fc_ratio_START  (0)
#define WBBP_DSP_SC_CAL_PARA2_dsp_inter_fc_ratio_END    (14)


/*****************************************************************************
 结构名    : WBBP_DSP_TCXO_VOL_UNION
 结构说明  : DSP_TCXO_VOL 寄存器结构定义。地址偏移量:0xF60，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_tcxo_vol_reg;
    struct
    {
        unsigned long  dsp_tcxo_vol : 16; /* bit[0-15] : DSP配置TCXO电压固定值，16bit无符号数。 */
        unsigned long  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} WBBP_DSP_TCXO_VOL_UNION;
#define WBBP_DSP_TCXO_VOL_dsp_tcxo_vol_START  (0)
#define WBBP_DSP_TCXO_VOL_dsp_tcxo_vol_END    (15)


/*****************************************************************************
 结构名    : WBBP_DSP_FREQ_ERROR_NCO_FW_CFG_EN_UNION
 结构说明  : DSP_FREQ_ERROR_NCO_FW_CFG_EN 寄存器结构定义。地址偏移量:0xF64，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_freq_error_nco_fw_cfg_en_reg;
    struct
    {
        unsigned long  dsp_nco_para : 13; /* bit[0-12] : 该系数用于计算输入给NCO的输入频率。信号位宽为13U。
                                                         W模式下配置为1118，C模式下配置为3459（W和C下的配置值由k=4计算得出，K改变的话该值需要改变，具体计算公式为k/fs*2^32）。 */
        unsigned long  reserved     : 19; /* bit[13-31]: 保留 */
    } reg;
} WBBP_DSP_FREQ_ERROR_NCO_FW_CFG_EN_UNION;
#define WBBP_DSP_FREQ_ERROR_NCO_FW_CFG_EN_dsp_nco_para_START  (0)
#define WBBP_DSP_FREQ_ERROR_NCO_FW_CFG_EN_dsp_nco_para_END    (12)


/*****************************************************************************
 结构名    : WBBP_DSP_SC_CAL_PARA3_UNION
 结构说明  : DSP_SC_CAL_PARA3 寄存器结构定义。地址偏移量:0xF6C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sc_cal_para3_reg;
    struct
    {
        unsigned long  dsp_cfg_fc : 18; /* bit[0-17] : DSP配置下行前端配置本频1/Fc值，18bit无符号数。软件配置公式为：2^29/Fc*K，其中Fc为下行载波频率，K为每bit表示的Hz数（可以是2、4或8）。 */
        unsigned long  reserved   : 14; /* bit[18-31]: 保留 */
    } reg;
} WBBP_DSP_SC_CAL_PARA3_UNION;
#define WBBP_DSP_SC_CAL_PARA3_dsp_cfg_fc_START  (0)
#define WBBP_DSP_SC_CAL_PARA3_dsp_cfg_fc_END    (17)


/*****************************************************************************
 结构名    : WBBP_DL_TDS_SC_DLT_FSMP_UNION
 结构说明  : DL_TDS_SC_DLT_FSMP 寄存器结构定义。地址偏移量:0xF70，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dl_tds_sc_dlt_fsmp_reg;
    struct
    {
        unsigned long  dl_tds_sc_dlt_fsmp : 17; /* bit[0-16] : tds模式下采样调整步长;17bit */
        unsigned long  reserved           : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_DL_TDS_SC_DLT_FSMP_UNION;
#define WBBP_DL_TDS_SC_DLT_FSMP_dl_tds_sc_dlt_fsmp_START  (0)
#define WBBP_DL_TDS_SC_DLT_FSMP_dl_tds_sc_dlt_fsmp_END    (16)


/*****************************************************************************
 结构名    : WBBP_DL_TDS_SC_DLT_VLD_UNION
 结构说明  : DL_TDS_SC_DLT_VLD 寄存器结构定义。地址偏移量:0xF78，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dl_tds_sc_dlt_vld_reg;
    struct
    {
        unsigned long  dl_tds_sc_dlt_vld : 1;  /* bit[0]   : dsp配置采样调整步长有效指示,为脉冲信号; */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DL_TDS_SC_DLT_VLD_UNION;
#define WBBP_DL_TDS_SC_DLT_VLD_dl_tds_sc_dlt_vld_START  (0)
#define WBBP_DL_TDS_SC_DLT_VLD_dl_tds_sc_dlt_vld_END    (0)


/*****************************************************************************
 结构名    : WBBP_DL_TDS_SC_INI_VLD_UNION
 结构说明  : DL_TDS_SC_INI_VLD 寄存器结构定义。地址偏移量:0xF7C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dl_tds_sc_ini_vld_reg;
    struct
    {
        unsigned long  dl_tds_sc_ini_vld : 1;  /* bit[0]   : dsp配置采样初始偏差值有效指示,为脉冲信号; */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DL_TDS_SC_INI_VLD_UNION;
#define WBBP_DL_TDS_SC_INI_VLD_dl_tds_sc_ini_vld_START  (0)
#define WBBP_DL_TDS_SC_INI_VLD_dl_tds_sc_ini_vld_END    (0)


/*****************************************************************************
 结构名    : WBBP_DL_TDS_SC_FSMP_MOD_UNION
 结构说明  : DL_TDS_SC_FSMP_MOD 寄存器结构定义。地址偏移量:0xF80，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dl_tds_sc_fsmp_mod_reg;
    struct
    {
        unsigned long  dl_tds_sc_fsmp_mod : 1;  /* bit[0]   : dsp配置参数模式:
                                                              1:直接根据vld信号锁存参数;
                                                              0:需要根据ad_on的上升沿与vld信号共同锁存参数;
                                                              默认值为1; */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DL_TDS_SC_FSMP_MOD_UNION;
#define WBBP_DL_TDS_SC_FSMP_MOD_dl_tds_sc_fsmp_mod_START  (0)
#define WBBP_DL_TDS_SC_FSMP_MOD_dl_tds_sc_fsmp_mod_END    (0)


/*****************************************************************************
 结构名    : WBBP_DL_EN_UNION
 结构说明  : DL_EN 寄存器结构定义。地址偏移量:0xF84，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dl_en_reg;
    struct
    {
        unsigned long  dl_sc_abn_del_en : 1;  /* bit[0]   : sc_cal模块在fifo几乎空，几乎满的异常删加点使能：
                                                            0：关闭异常删加点功能；
                                                            1：打开异常删加点功能。
                                                            默认打开。 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DL_EN_UNION;
#define WBBP_DL_EN_dl_sc_abn_del_en_START  (0)
#define WBBP_DL_EN_dl_sc_abn_del_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_DL_RPT_CH_SEL_UNION
 结构说明  : DL_RPT_CH_SEL 寄存器结构定义。地址偏移量:0xF8C，初值:0x00000000，宽度:32
 寄存器说明: sc_cal可维可测上报逻辑通道选择
*****************************************************************************/
typedef union
{
    unsigned long      dl_rpt_ch_sel_reg;
    struct
    {
        unsigned long  rpt_ch_sel : 2;  /* bit[0-1] : SC_CAL可维可测上报通道选择：
                                                      2'b00：通道0（主天线主载波）
                                                      2'b01：通道1（主天线辅载波）
                                                      2'b10：通道2（辅天线主载波）
                                                      2'b11：通道3（辅天线辅载波） */
        unsigned long  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DL_RPT_CH_SEL_UNION;
#define WBBP_DL_RPT_CH_SEL_rpt_ch_sel_START  (0)
#define WBBP_DL_RPT_CH_SEL_rpt_ch_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_DL_SC_CAL_NUM_RPT_UNION
 结构说明  : DL_SC_CAL_NUM_RPT 寄存器结构定义。地址偏移量:0xF90，初值:0x00000000，宽度:32
 寄存器说明: SC_CAL删加点个数上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_sc_cal_num_rpt_reg;
    struct
    {
        unsigned long  dl_sc_add_num_rpt : 16; /* bit[0-15] : sc_cal模块计算加点个数统计。 */
        unsigned long  dl_sc_del_num_rpt : 16; /* bit[16-31]: sc_cal模块计算删点个数统计。 */
    } reg;
} WBBP_DL_SC_CAL_NUM_RPT_UNION;
#define WBBP_DL_SC_CAL_NUM_RPT_dl_sc_add_num_rpt_START  (0)
#define WBBP_DL_SC_CAL_NUM_RPT_dl_sc_add_num_rpt_END    (15)
#define WBBP_DL_SC_CAL_NUM_RPT_dl_sc_del_num_rpt_START  (16)
#define WBBP_DL_SC_CAL_NUM_RPT_dl_sc_del_num_rpt_END    (31)


/*****************************************************************************
 结构名    : WBBP_DL_SC_CAL_NUM_RPT_CLR_UNION
 结构说明  : DL_SC_CAL_NUM_RPT_CLR 寄存器结构定义。地址偏移量:0xF94，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dl_sc_cal_num_rpt_clr_reg;
    struct
    {
        unsigned long  dl_sc_add_num_clr : 1;  /* bit[0]   : sc_cal模块计算加点个数统计清零。 */
        unsigned long  dl_sc_del_num_clr : 1;  /* bit[1]   : sc_cal模块计算删点个数统计清零。 */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DL_SC_CAL_NUM_RPT_CLR_UNION;
#define WBBP_DL_SC_CAL_NUM_RPT_CLR_dl_sc_add_num_clr_START  (0)
#define WBBP_DL_SC_CAL_NUM_RPT_CLR_dl_sc_add_num_clr_END    (0)
#define WBBP_DL_SC_CAL_NUM_RPT_CLR_dl_sc_del_num_clr_START  (1)
#define WBBP_DL_SC_CAL_NUM_RPT_CLR_dl_sc_del_num_clr_END    (1)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO0_EMPTY_FULL_RPT_UNION
 结构说明  : DL_FIFO0_EMPTY_FULL_RPT 寄存器结构定义。地址偏移量:0xF98，初值:0x00000000，宽度:32
 寄存器说明: 通道0（主天线主载波） FIFO 异常空满上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo0_empty_full_rpt_reg;
    struct
    {
        unsigned long  fifo0_empty_abn_dsp : 1;  /* bit[0]    : 通道0（主天线主载波） 异常空标志:
                                                                1'b0:FIFO不异常空；
                                                                1'b1:FIFO异常空。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  fifo0_full_dsp      : 1;  /* bit[4]    : 通道0 （主天线主载波）FIFO 满标志:
                                                                1'b0:FIFO不满；
                                                                1'b1:FIFO满。 */
        unsigned long  reserved_1          : 3;  /* bit[5-7]  : 保留 */
        unsigned long  fifo0_cnt_a         : 5;  /* bit[8-12] : 通道0（主天线主载波） FIFO 写侧剩余数据个数 */
        unsigned long  reserved_2          : 3;  /* bit[13-15]: 保留 */
        unsigned long  fifo0_cnt_b         : 5;  /* bit[16-20]: 通道0（主天线主载波） FIFO 读侧剩余数据个数 */
        unsigned long  reserved_3          : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_DL_FIFO0_EMPTY_FULL_RPT_UNION;
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_empty_abn_dsp_START  (0)
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_empty_abn_dsp_END    (0)
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_full_dsp_START       (4)
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_full_dsp_END         (4)
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_cnt_a_START          (8)
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_cnt_a_END            (12)
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_cnt_b_START          (16)
#define WBBP_DL_FIFO0_EMPTY_FULL_RPT_fifo0_cnt_b_END            (20)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO0_EMPTY_FULL_NUM_UNION
 结构说明  : DL_FIFO0_EMPTY_FULL_NUM 寄存器结构定义。地址偏移量:0xF9C，初值:0x00000000，宽度:32
 寄存器说明: 通道0（主天线主载波） FIFO 异常空满次数上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo0_empty_full_num_reg;
    struct
    {
        unsigned long  fifo0_alemp_num : 8;  /* bit[0-7]  : 通道0（主天线主载波） FIFO将空次数上报 */
        unsigned long  fifo0_alful_num : 8;  /* bit[8-15] : 通道0（主天线主载波） FIFO将满次数上报 */
        unsigned long  fifo0_emp_num   : 8;  /* bit[16-23]: 通道0（主天线主载波） FIFO空次数上报 */
        unsigned long  fifo0_ful_num   : 8;  /* bit[24-31]: 通道0（主天线主载波） FIFO满次数上报 */
    } reg;
} WBBP_DL_FIFO0_EMPTY_FULL_NUM_UNION;
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_alemp_num_START  (0)
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_alemp_num_END    (7)
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_alful_num_START  (8)
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_alful_num_END    (15)
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_emp_num_START    (16)
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_emp_num_END      (23)
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_ful_num_START    (24)
#define WBBP_DL_FIFO0_EMPTY_FULL_NUM_fifo0_ful_num_END      (31)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO1_EMPTY_FULL_RPT_UNION
 结构说明  : DL_FIFO1_EMPTY_FULL_RPT 寄存器结构定义。地址偏移量:0xFA0，初值:0x00000000，宽度:32
 寄存器说明: 通道1（主天线辅载波） FIFO 异常空满上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo1_empty_full_rpt_reg;
    struct
    {
        unsigned long  fifo1_empty_abn_dsp : 1;  /* bit[0]    : 通道1（主天线辅载波） 异常空标志:
                                                                1'b0:FIFO不异常空；
                                                                1'b1:FIFO异常空。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  fifo1_full_dsp      : 1;  /* bit[4]    : 通道1 （主天线辅载波）FIFO 满标志:
                                                                1'b0:FIFO不满；
                                                                1'b1:FIFO满。 */
        unsigned long  reserved_1          : 3;  /* bit[5-7]  : 保留 */
        unsigned long  fifo1_cnt_a         : 5;  /* bit[8-12] : 通道0（主天线辅载波） FIFO 写侧剩余数据个数 */
        unsigned long  reserved_2          : 3;  /* bit[13-15]: 保留 */
        unsigned long  fifo1_cnt_b         : 5;  /* bit[16-20]: 通道1（主天线辅载波） FIFO 读侧剩余数据个数 */
        unsigned long  reserved_3          : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_DL_FIFO1_EMPTY_FULL_RPT_UNION;
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_empty_abn_dsp_START  (0)
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_empty_abn_dsp_END    (0)
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_full_dsp_START       (4)
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_full_dsp_END         (4)
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_cnt_a_START          (8)
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_cnt_a_END            (12)
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_cnt_b_START          (16)
#define WBBP_DL_FIFO1_EMPTY_FULL_RPT_fifo1_cnt_b_END            (20)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO1_EMPTY_FULL_NUM_UNION
 结构说明  : DL_FIFO1_EMPTY_FULL_NUM 寄存器结构定义。地址偏移量:0xFA4，初值:0x00000000，宽度:32
 寄存器说明: 通道1（主天线辅载波） FIFO 异常空满次数上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo1_empty_full_num_reg;
    struct
    {
        unsigned long  fifo1_alemp_num : 8;  /* bit[0-7]  : 通道1（主天线辅载波） FIFO将空次数上报 */
        unsigned long  fifo1_alful_num : 8;  /* bit[8-15] : 通道1（主天线辅载波） FIFO将满次数上报 */
        unsigned long  fifo1_emp_num   : 8;  /* bit[16-23]: 通道1（主天线辅载波） FIFO空次数上报 */
        unsigned long  fifo1_ful_num   : 8;  /* bit[24-31]: 通道1（主天线辅载波） FIFO满次数上报 */
    } reg;
} WBBP_DL_FIFO1_EMPTY_FULL_NUM_UNION;
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_alemp_num_START  (0)
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_alemp_num_END    (7)
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_alful_num_START  (8)
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_alful_num_END    (15)
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_emp_num_START    (16)
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_emp_num_END      (23)
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_ful_num_START    (24)
#define WBBP_DL_FIFO1_EMPTY_FULL_NUM_fifo1_ful_num_END      (31)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO2_EMPTY_FULL_RPT_UNION
 结构说明  : DL_FIFO2_EMPTY_FULL_RPT 寄存器结构定义。地址偏移量:0xFA8，初值:0x00000000，宽度:32
 寄存器说明: 通道2（辅天线主载波） FIFO 异常空满上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo2_empty_full_rpt_reg;
    struct
    {
        unsigned long  fifo2_empty_abn_dsp : 1;  /* bit[0]    : 通道2（辅天线主载波） 异常空标志:
                                                                1'b0:FIFO不异常空；
                                                                1'b1:FIFO异常空。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  fifo2_full_dsp      : 1;  /* bit[4]    : 通道2 （辅天线主载波）FIFO 满标志:
                                                                1'b0:FIFO不满；
                                                                1'b1:FIFO满。 */
        unsigned long  reserved_1          : 3;  /* bit[5-7]  : 保留 */
        unsigned long  fifo2_cnt_a         : 5;  /* bit[8-12] : 通道2（辅天线主载波） FIFO 写侧剩余数据个数 */
        unsigned long  reserved_2          : 3;  /* bit[13-15]: 保留 */
        unsigned long  fifo2_cnt_b         : 5;  /* bit[16-20]: 通道2（辅天线主载波） FIFO 读侧剩余数据个数 */
        unsigned long  reserved_3          : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_DL_FIFO2_EMPTY_FULL_RPT_UNION;
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_empty_abn_dsp_START  (0)
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_empty_abn_dsp_END    (0)
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_full_dsp_START       (4)
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_full_dsp_END         (4)
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_cnt_a_START          (8)
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_cnt_a_END            (12)
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_cnt_b_START          (16)
#define WBBP_DL_FIFO2_EMPTY_FULL_RPT_fifo2_cnt_b_END            (20)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO2_EMPTY_FULL_NUM_UNION
 结构说明  : DL_FIFO2_EMPTY_FULL_NUM 寄存器结构定义。地址偏移量:0xFAC，初值:0x00000000，宽度:32
 寄存器说明: 通道2（辅天线主载波） FIFO 异常空满次数上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo2_empty_full_num_reg;
    struct
    {
        unsigned long  fifo2_alemp_num : 8;  /* bit[0-7]  : 通道2（辅天线主载波） FIFO将空次数上报 */
        unsigned long  fifo2_alful_num : 8;  /* bit[8-15] : 通道2（辅天线主载波） FIFO将满次数上报 */
        unsigned long  fifo2_emp_num   : 8;  /* bit[16-23]: 通道2（辅天线主载波） FIFO空次数上报 */
        unsigned long  fifo2_ful_num   : 8;  /* bit[24-31]: 通道2（辅天线主载波） FIFO满次数上报 */
    } reg;
} WBBP_DL_FIFO2_EMPTY_FULL_NUM_UNION;
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_alemp_num_START  (0)
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_alemp_num_END    (7)
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_alful_num_START  (8)
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_alful_num_END    (15)
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_emp_num_START    (16)
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_emp_num_END      (23)
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_ful_num_START    (24)
#define WBBP_DL_FIFO2_EMPTY_FULL_NUM_fifo2_ful_num_END      (31)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO3_EMPTY_FULL_RPT_UNION
 结构说明  : DL_FIFO3_EMPTY_FULL_RPT 寄存器结构定义。地址偏移量:0xFB0，初值:0x00000000，宽度:32
 寄存器说明: 通道3（辅天线辅载波） FIFO 异常空满上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo3_empty_full_rpt_reg;
    struct
    {
        unsigned long  fifo3_empty_abn_dsp : 1;  /* bit[0]    : 通道3（辅天线辅载波） 异常空标志:
                                                                1'b0:FIFO不异常空；
                                                                1'b1:FIFO异常空。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  fifo3_full_dsp      : 1;  /* bit[4]    : 通道3（辅天线辅载波）FIFO 满标志:
                                                                1'b0:FIFO不满；
                                                                1'b1:FIFO满。 */
        unsigned long  reserved_1          : 3;  /* bit[5-7]  : 保留 */
        unsigned long  fifo3_cnt_a         : 5;  /* bit[8-12] : 通道3（辅天线辅载波） FIFO 写侧剩余数据个数 */
        unsigned long  reserved_2          : 3;  /* bit[13-15]: 保留 */
        unsigned long  fifo3_cnt_b         : 5;  /* bit[16-20]: 通道3（辅天线辅载波） FIFO 读侧剩余数据个数 */
        unsigned long  reserved_3          : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_DL_FIFO3_EMPTY_FULL_RPT_UNION;
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_empty_abn_dsp_START  (0)
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_empty_abn_dsp_END    (0)
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_full_dsp_START       (4)
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_full_dsp_END         (4)
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_cnt_a_START          (8)
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_cnt_a_END            (12)
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_cnt_b_START          (16)
#define WBBP_DL_FIFO3_EMPTY_FULL_RPT_fifo3_cnt_b_END            (20)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO3_EMPTY_FULL_NUM_UNION
 结构说明  : DL_FIFO3_EMPTY_FULL_NUM 寄存器结构定义。地址偏移量:0xFB4，初值:0x00000000，宽度:32
 寄存器说明: 通道3（辅天线辅载波） FIFO 异常空满次数上报
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo3_empty_full_num_reg;
    struct
    {
        unsigned long  fifo3_alemp_num : 8;  /* bit[0-7]  : 通道3（辅天线辅载波） FIFO将空次数上报 */
        unsigned long  fifo3_alful_num : 8;  /* bit[8-15] : 通道3（辅天线辅载波） FIFO将满次数上报 */
        unsigned long  fifo3_emp_num   : 8;  /* bit[16-23]: 通道3（辅天线辅载波） FIFO空次数上报 */
        unsigned long  fifo3_ful_num   : 8;  /* bit[24-31]: 通道3（辅天线辅载波） FIFO满次数上报 */
    } reg;
} WBBP_DL_FIFO3_EMPTY_FULL_NUM_UNION;
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_alemp_num_START  (0)
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_alemp_num_END    (7)
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_alful_num_START  (8)
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_alful_num_END    (15)
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_emp_num_START    (16)
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_emp_num_END      (23)
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_ful_num_START    (24)
#define WBBP_DL_FIFO3_EMPTY_FULL_NUM_fifo3_ful_num_END      (31)


/*****************************************************************************
 结构名    : WBBP_DL_FIFO_CLR_UNION
 结构说明  : DL_FIFO_CLR 寄存器结构定义。地址偏移量:0xFB8，初值:0x00000000，宽度:32
 寄存器说明: FIFO清零信号
*****************************************************************************/
typedef union
{
    unsigned long      dl_fifo_clr_reg;
    struct
    {
        unsigned long  dsp_dl_fifo_clr_en     : 1;  /* bit[0]   : FIFO清零电平信号:
                                                                  1'b0:FIFO不清零
                                                                  1'b1:FIFO清零 */
        unsigned long  dsp_dl_fifo_rpt_clr_en : 1;  /* bit[1]   : FIFO异常空满上报状态清零信号:
                                                                  1'b0:FIFO异常空满不清零
                                                                  1'b1:FIFO异常空满清零 */
        unsigned long  reserved               : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DL_FIFO_CLR_UNION;
#define WBBP_DL_FIFO_CLR_dsp_dl_fifo_clr_en_START      (0)
#define WBBP_DL_FIFO_CLR_dsp_dl_fifo_clr_en_END        (0)
#define WBBP_DL_FIFO_CLR_dsp_dl_fifo_rpt_clr_en_START  (1)
#define WBBP_DL_FIFO_CLR_dsp_dl_fifo_rpt_clr_en_END    (1)


/*****************************************************************************
 结构名    : WBBP_W_BASE_CNT_RPT_UNION
 结构说明  : W_BASE_CNT_RPT 寄存器结构定义。地址偏移量:0xFBC，初值:0x00000000，宽度:32
 寄存器说明: W_BASE_CNT上报
*****************************************************************************/
typedef union
{
    unsigned long      w_base_cnt_rpt_reg;
    struct
    {
        unsigned long  w_base_cnt_rpt : 17; /* bit[0-16] : 下行前端W_BASE_CNT上报，每个时隙边界后的第二个样点上报。 */
        unsigned long  reserved       : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_W_BASE_CNT_RPT_UNION;
#define WBBP_W_BASE_CNT_RPT_w_base_cnt_rpt_START  (0)
#define WBBP_W_BASE_CNT_RPT_w_base_cnt_rpt_END    (16)


/*****************************************************************************
 结构名    : WBBP_W_RX1_MC1_DAGC_CTRL_RPT_UNION
 结构说明  : W_RX1_MC1_DAGC_CTRL_RPT 寄存器结构定义。地址偏移量:0xFC0，初值:0x00000000，宽度:32
 寄存器说明: W主天线主载波dagc_ctrl上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx1_mc1_dagc_ctrl_rpt_reg;
    struct
    {
        unsigned long  w_rx1_mc1_dagc_ctrl_rpt      : 16; /* bit[0-15] : W主天线主载波dagc_ctrl上报，每个符号边界后的第二个chip上报。 */
        unsigned long  w_rx1_mc1_dagc_ctrl_4bit_rpt : 12; /* bit[16-27]: W主天线主载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved                     : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_W_RX1_MC1_DAGC_CTRL_RPT_UNION;
#define WBBP_W_RX1_MC1_DAGC_CTRL_RPT_w_rx1_mc1_dagc_ctrl_rpt_START       (0)
#define WBBP_W_RX1_MC1_DAGC_CTRL_RPT_w_rx1_mc1_dagc_ctrl_rpt_END         (15)
#define WBBP_W_RX1_MC1_DAGC_CTRL_RPT_w_rx1_mc1_dagc_ctrl_4bit_rpt_START  (16)
#define WBBP_W_RX1_MC1_DAGC_CTRL_RPT_w_rx1_mc1_dagc_ctrl_4bit_rpt_END    (27)


/*****************************************************************************
 结构名    : WBBP_W_RX1_MC2_DAGC_CTRL_RPT_UNION
 结构说明  : W_RX1_MC2_DAGC_CTRL_RPT 寄存器结构定义。地址偏移量:0xFC4，初值:0x00000000，宽度:32
 寄存器说明: W主天线辅载波dagc_ctrl上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx1_mc2_dagc_ctrl_rpt_reg;
    struct
    {
        unsigned long  w_rx1_mc2_dagc_ctrl_rpt      : 16; /* bit[0-15] : W主天线辅载波dagc_ctrl上报，每个符号边界后的第二个chip上报。 */
        unsigned long  w_rx1_mc2_dagc_ctrl_4bit_rpt : 12; /* bit[16-27]: W主天线辅载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved                     : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_W_RX1_MC2_DAGC_CTRL_RPT_UNION;
#define WBBP_W_RX1_MC2_DAGC_CTRL_RPT_w_rx1_mc2_dagc_ctrl_rpt_START       (0)
#define WBBP_W_RX1_MC2_DAGC_CTRL_RPT_w_rx1_mc2_dagc_ctrl_rpt_END         (15)
#define WBBP_W_RX1_MC2_DAGC_CTRL_RPT_w_rx1_mc2_dagc_ctrl_4bit_rpt_START  (16)
#define WBBP_W_RX1_MC2_DAGC_CTRL_RPT_w_rx1_mc2_dagc_ctrl_4bit_rpt_END    (27)


/*****************************************************************************
 结构名    : WBBP_W_RX2_MC1_DAGC_CTRL_RPT_UNION
 结构说明  : W_RX2_MC1_DAGC_CTRL_RPT 寄存器结构定义。地址偏移量:0xFC8，初值:0x00000000，宽度:32
 寄存器说明: W辅天线主载波dagc_ctrl上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx2_mc1_dagc_ctrl_rpt_reg;
    struct
    {
        unsigned long  w_rx2_mc1_dagc_ctrl_rpt      : 16; /* bit[0-15] : W辅天线主载波dagc_ctrl上报，每个符号边界后的第二个chip上报。 */
        unsigned long  w_rx2_mc1_dagc_ctrl_4bit_rpt : 12; /* bit[16-27]: W辅天线主载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved                     : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_W_RX2_MC1_DAGC_CTRL_RPT_UNION;
#define WBBP_W_RX2_MC1_DAGC_CTRL_RPT_w_rx2_mc1_dagc_ctrl_rpt_START       (0)
#define WBBP_W_RX2_MC1_DAGC_CTRL_RPT_w_rx2_mc1_dagc_ctrl_rpt_END         (15)
#define WBBP_W_RX2_MC1_DAGC_CTRL_RPT_w_rx2_mc1_dagc_ctrl_4bit_rpt_START  (16)
#define WBBP_W_RX2_MC1_DAGC_CTRL_RPT_w_rx2_mc1_dagc_ctrl_4bit_rpt_END    (27)


/*****************************************************************************
 结构名    : WBBP_W_RX2_MC2_DAGC_CTRL_RPT_UNION
 结构说明  : W_RX2_MC2_DAGC_CTRL_RPT 寄存器结构定义。地址偏移量:0xFCC，初值:0x00000000，宽度:32
 寄存器说明: W辅天线主载波dagc_ctrl上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx2_mc2_dagc_ctrl_rpt_reg;
    struct
    {
        unsigned long  w_rx2_mc2_dagc_ctrl_rpt      : 16; /* bit[0-15] : W辅天线辅载波dagc_ctrl上报，每个符号边界后的第二个chip上报。 */
        unsigned long  w_rx2_mc2_dagc_ctrl_4bit_rpt : 12; /* bit[16-27]: W辅天线辅载波dagc_ctrl_4bit上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved                     : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_W_RX2_MC2_DAGC_CTRL_RPT_UNION;
#define WBBP_W_RX2_MC2_DAGC_CTRL_RPT_w_rx2_mc2_dagc_ctrl_rpt_START       (0)
#define WBBP_W_RX2_MC2_DAGC_CTRL_RPT_w_rx2_mc2_dagc_ctrl_rpt_END         (15)
#define WBBP_W_RX2_MC2_DAGC_CTRL_RPT_w_rx2_mc2_dagc_ctrl_4bit_rpt_START  (16)
#define WBBP_W_RX2_MC2_DAGC_CTRL_RPT_w_rx2_mc2_dagc_ctrl_4bit_rpt_END    (27)


/*****************************************************************************
 结构名    : WBBP_W_AAGC_CTRL_RPT_UNION
 结构说明  : W_AAGC_CTRL_RPT 寄存器结构定义。地址偏移量:0xFD0，初值:0x00000000，宽度:32
 寄存器说明: W aagc_ctrl上报
*****************************************************************************/
typedef union
{
    unsigned long      w_aagc_ctrl_rpt_reg;
    struct
    {
        unsigned long  w_rx1_aagc_ctrl_rpt : 12; /* bit[0-11] : W主天线aagc_ctrl上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved_0          : 4;  /* bit[12-15]: 保留 */
        unsigned long  w_rx2_aagc_ctrl_rpt : 12; /* bit[16-27]: W辅天线aagc_ctrl上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved_1          : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_W_AAGC_CTRL_RPT_UNION;
#define WBBP_W_AAGC_CTRL_RPT_w_rx1_aagc_ctrl_rpt_START  (0)
#define WBBP_W_AAGC_CTRL_RPT_w_rx1_aagc_ctrl_rpt_END    (11)
#define WBBP_W_AAGC_CTRL_RPT_w_rx2_aagc_ctrl_rpt_START  (16)
#define WBBP_W_AAGC_CTRL_RPT_w_rx2_aagc_ctrl_rpt_END    (27)


/*****************************************************************************
 结构名    : WBBP_W_RX1_MC1_RSSI_RPT_UNION
 结构说明  : W_RX1_MC1_RSSI_RPT 寄存器结构定义。地址偏移量:0xFD4，初值:0x00000000，宽度:32
 寄存器说明: W主天线主载波RSSI上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx1_mc1_rssi_rpt_reg;
    struct
    {
        unsigned long  w_rx1_mc1_rssi_rpt : 11; /* bit[0-10] : W主天线主载波rssi上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved           : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_W_RX1_MC1_RSSI_RPT_UNION;
#define WBBP_W_RX1_MC1_RSSI_RPT_w_rx1_mc1_rssi_rpt_START  (0)
#define WBBP_W_RX1_MC1_RSSI_RPT_w_rx1_mc1_rssi_rpt_END    (10)


/*****************************************************************************
 结构名    : WBBP_W_RX1_MC2_RSSI_RPT_UNION
 结构说明  : W_RX1_MC2_RSSI_RPT 寄存器结构定义。地址偏移量:0xFD8，初值:0x00000000，宽度:32
 寄存器说明: W主天线辅载波RSSI上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx1_mc2_rssi_rpt_reg;
    struct
    {
        unsigned long  w_rx1_mc2_rssi_rpt : 11; /* bit[0-10] : W主天线辅载波rssi上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved           : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_W_RX1_MC2_RSSI_RPT_UNION;
#define WBBP_W_RX1_MC2_RSSI_RPT_w_rx1_mc2_rssi_rpt_START  (0)
#define WBBP_W_RX1_MC2_RSSI_RPT_w_rx1_mc2_rssi_rpt_END    (10)


/*****************************************************************************
 结构名    : WBBP_W_RX2_MC1_RSSI_RPT_UNION
 结构说明  : W_RX2_MC1_RSSI_RPT 寄存器结构定义。地址偏移量:0xFDC，初值:0x00000000，宽度:32
 寄存器说明: W辅天线主载波RSSI上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx2_mc1_rssi_rpt_reg;
    struct
    {
        unsigned long  w_rx2_mc1_rssi_rpt : 11; /* bit[0-10] : W辅天线主载波rssi上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved           : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_W_RX2_MC1_RSSI_RPT_UNION;
#define WBBP_W_RX2_MC1_RSSI_RPT_w_rx2_mc1_rssi_rpt_START  (0)
#define WBBP_W_RX2_MC1_RSSI_RPT_w_rx2_mc1_rssi_rpt_END    (10)


/*****************************************************************************
 结构名    : WBBP_W_RX2_MC2_RSSI_RPT_UNION
 结构说明  : W_RX2_MC2_RSSI_RPT 寄存器结构定义。地址偏移量:0xFE0，初值:0x00000000，宽度:32
 寄存器说明: W辅天线主载波RSSI上报
*****************************************************************************/
typedef union
{
    unsigned long      w_rx2_mc2_rssi_rpt_reg;
    struct
    {
        unsigned long  w_rx2_mc2_rssi_rpt : 11; /* bit[0-10] : W辅天线辅载波rssi上报，每个符号边界后的第二个chip上报。 */
        unsigned long  reserved           : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_W_RX2_MC2_RSSI_RPT_UNION;
#define WBBP_W_RX2_MC2_RSSI_RPT_w_rx2_mc2_rssi_rpt_START  (0)
#define WBBP_W_RX2_MC2_RSSI_RPT_w_rx2_mc2_rssi_rpt_END    (10)


/*****************************************************************************
 结构名    : WBBP_WC_NCO_RPT_UNION
 结构说明  : WC_NCO_RPT 寄存器结构定义。地址偏移量:0xFE4，初值:0x00000000，宽度:32
 寄存器说明: W辅天线主载波RSSI上报
*****************************************************************************/
typedef union
{
    unsigned long      wc_nco_rpt_reg;
    struct
    {
        unsigned long  nco_fw_cfg_rpt : 16; /* bit[0-15] : WC NCO输入的频偏值上报（该频偏值来自SC CAL模块） */
        unsigned long  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} WBBP_WC_NCO_RPT_UNION;
#define WBBP_WC_NCO_RPT_nco_fw_cfg_rpt_START  (0)
#define WBBP_WC_NCO_RPT_nco_fw_cfg_rpt_END    (15)


/*****************************************************************************
 结构名    : WBBP_W_SSI_CH_SEL_UNION
 结构说明  : W_SSI_CH_SEL 寄存器结构定义。地址偏移量:0xFE8，初值:0x00000000，宽度:32
 寄存器说明: W模ssi发送通道选择
*****************************************************************************/
typedef union
{
    unsigned long      w_ssi_ch_sel_reg;
    struct
    {
        unsigned long  wagc0_intra_ssi_ch_sel : 2;  /* bit[0-1]  : W下行主天线本频SSI控制字通道选择。
                                                                   C模不配置。
                                                                   00：选择ch0；
                                                                   01：选择ch1；
                                                                   10：选择ch2；
                                                                   11：选择ch3； */
        unsigned long  reserved_0             : 2;  /* bit[2-3]  : 保留 */
        unsigned long  wagc0_inter_ssi_ch_sel : 2;  /* bit[4-5]  : W下行主天线异频SSI控制字通道选择。
                                                                   C模不配置。
                                                                   00：选择ch0；
                                                                   01：选择ch1；
                                                                   10：选择ch2；
                                                                   11：选择ch3； */
        unsigned long  reserved_1             : 2;  /* bit[6-7]  : 保留 */
        unsigned long  wagc1_intra_ssi_ch_sel : 2;  /* bit[8-9]  : W下行辅天线本频SSI控制字通道选择。
                                                                   C模不配置。
                                                                   00：选择ch0；
                                                                   01：选择ch1；
                                                                   10：选择ch2；
                                                                   11：选择ch3； */
        unsigned long  reserved_2             : 2;  /* bit[10-11]: 保留 */
        unsigned long  wagc1_inter_ssi_ch_sel : 2;  /* bit[12-13]: W下行辅天线异频SSI控制字通道选择。
                                                                   C模不配置。
                                                                   00：选择ch0；
                                                                   01：选择ch1；
                                                                   10：选择ch2；
                                                                   11：选择ch3； */
        unsigned long  reserved_3             : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_W_SSI_CH_SEL_UNION;
#define WBBP_W_SSI_CH_SEL_wagc0_intra_ssi_ch_sel_START  (0)
#define WBBP_W_SSI_CH_SEL_wagc0_intra_ssi_ch_sel_END    (1)
#define WBBP_W_SSI_CH_SEL_wagc0_inter_ssi_ch_sel_START  (4)
#define WBBP_W_SSI_CH_SEL_wagc0_inter_ssi_ch_sel_END    (5)
#define WBBP_W_SSI_CH_SEL_wagc1_intra_ssi_ch_sel_START  (8)
#define WBBP_W_SSI_CH_SEL_wagc1_intra_ssi_ch_sel_END    (9)
#define WBBP_W_SSI_CH_SEL_wagc1_inter_ssi_ch_sel_START  (12)
#define WBBP_W_SSI_CH_SEL_wagc1_inter_ssi_ch_sel_END    (13)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_0_UNION
 结构说明  : WC_DC_REG_AT1_0 寄存器结构定义。地址偏移量:0x600，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_0_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_8s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_8s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S2的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S2的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_0_UNION;
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s1_8s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s1_8s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s1_8s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s1_8s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s2_8s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s2_8s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s2_8s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_0_dsp_dc_reg_s2_8s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_1_UNION
 结构说明  : WC_DC_REG_AT1_1 寄存器结构定义。地址偏移量:0x604，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_1_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_8s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_8s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S4的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S4的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_1_UNION;
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s3_8s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s3_8s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s3_8s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s3_8s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s4_8s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s4_8s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s4_8s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_1_dsp_dc_reg_s4_8s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_2_UNION
 结构说明  : WC_DC_REG_AT1_2 寄存器结构定义。地址偏移量:0x608，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_2_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_8s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_8s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S6的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S6的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_2_UNION;
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s5_8s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s5_8s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s5_8s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s5_8s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s6_8s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s6_8s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s6_8s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_2_dsp_dc_reg_s6_8s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_3_UNION
 结构说明  : WC_DC_REG_AT1_3 寄存器结构定义。地址偏移量:0x60C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_3_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_8s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_8s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S8的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S8的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_3_UNION;
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s7_8s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s7_8s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s7_8s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s7_8s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s8_8s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s8_8s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s8_8s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_3_dsp_dc_reg_s8_8s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_4_UNION
 结构说明  : WC_DC_REG_AT1_4 寄存器结构定义。地址偏移量:0x610，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_4_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_5s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_5s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S2的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S2的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_4_UNION;
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s1_5s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s1_5s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s1_5s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s1_5s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s2_5s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s2_5s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s2_5s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_4_dsp_dc_reg_s2_5s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_5_UNION
 结构说明  : WC_DC_REG_AT1_5 寄存器结构定义。地址偏移量:0x614，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_5_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_5s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_5s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S4的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S4的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_5_UNION;
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s3_5s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s3_5s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s3_5s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s3_5s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s4_5s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s4_5s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s4_5s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_5_dsp_dc_reg_s4_5s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_6_UNION
 结构说明  : WC_DC_REG_AT1_6 寄存器结构定义。地址偏移量:0x618，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_6_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_5s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_5s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S6的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S6的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_6_UNION;
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s5_5s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s5_5s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s5_5s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s5_5s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s6_5s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s6_5s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s6_5s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_6_dsp_dc_reg_s6_5s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_7_UNION
 结构说明  : WC_DC_REG_AT1_7 寄存器结构定义。地址偏移量:0x61C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_7_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_5s_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_5s_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_i_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S8的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_q_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S8的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_7_UNION;
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s7_5s_i_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s7_5s_i_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s7_5s_q_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s7_5s_q_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s8_5s_i_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s8_5s_i_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s8_5s_q_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_7_dsp_dc_reg_s8_5s_q_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_0_UNION
 结构说明  : WC_DC_REG_AT2_0 寄存器结构定义。地址偏移量:0x620，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_0_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_8s_i_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_8s_q_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S2的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，8档AAGC S2的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_0_UNION;
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s1_8s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s1_8s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s1_8s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s1_8s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s2_8s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s2_8s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s2_8s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_0_dsp_dc_reg_s2_8s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_1_UNION
 结构说明  : WC_DC_REG_AT2_1 寄存器结构定义。地址偏移量:0x624，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_1_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_8s_i_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_8s_q_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S4的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，8档AAGC S4的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_1_UNION;
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s3_8s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s3_8s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s3_8s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s3_8s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s4_8s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s4_8s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s4_8s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_1_dsp_dc_reg_s4_8s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_2_UNION
 结构说明  : WC_DC_REG_AT2_2 寄存器结构定义。地址偏移量:0x628，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_2_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_8s_i_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_8s_q_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S6的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，8档AAGC S6的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_2_UNION;
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s5_8s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s5_8s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s5_8s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s5_8s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s6_8s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s6_8s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s6_8s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_2_dsp_dc_reg_s6_8s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_3_UNION
 结构说明  : WC_DC_REG_AT2_3 寄存器结构定义。地址偏移量:0x62C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_3_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_8s_i_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_8s_q_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S8的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，8档AAGC S8的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_3_UNION;
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s7_8s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s7_8s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s7_8s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s7_8s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s8_8s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s8_8s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s8_8s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_3_dsp_dc_reg_s8_8s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_4_UNION
 结构说明  : WC_DC_REG_AT2_4 寄存器结构定义。地址偏移量:0x630，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_4_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_5s_i_at2 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_5s_q_at2 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S1的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_i_at2 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S2的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_q_at2 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S2的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_4_UNION;
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s1_5s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s1_5s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s1_5s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s1_5s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s2_5s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s2_5s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s2_5s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_4_dsp_dc_reg_s2_5s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_5_UNION
 结构说明  : WC_DC_REG_AT2_5 寄存器结构定义。地址偏移量:0x634，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_5_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_5s_i_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，5档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_5s_q_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，5档AAGC S3的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，5档AAGC S4的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，5档AAGC S4的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_5_UNION;
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s3_5s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s3_5s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s3_5s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s3_5s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s4_5s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s4_5s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s4_5s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_5_dsp_dc_reg_s4_5s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_6_UNION
 结构说明  : WC_DC_REG_AT2_6 寄存器结构定义。地址偏移量:0x638，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_6_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_5s_i_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，5档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_5s_q_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，5档AAGC S5的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，5档AAGC S6的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，5档AAGC S6的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_6_UNION;
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s5_5s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s5_5s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s5_5s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s5_5s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s6_5s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s6_5s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s6_5s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_6_dsp_dc_reg_s6_5s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_7_UNION
 结构说明  : WC_DC_REG_AT2_7 寄存器结构定义。地址偏移量:0x63C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_7_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_5s_i_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，5档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_5s_q_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，5档AAGC S7的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，5档AAGC S8的DC配置值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，5档AAGC S8的DC配置值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_7_UNION;
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s7_5s_i_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s7_5s_i_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s7_5s_q_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s7_5s_q_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s8_5s_i_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s8_5s_i_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s8_5s_q_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_7_dsp_dc_reg_s8_5s_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_0_UNION
 结构说明  : WC_DC_REG_AT1_RPT_0 寄存器结构定义。地址偏移量:0x640，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_0_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_8s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_8s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S2的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S2的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_0_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s1_8s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s1_8s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s1_8s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s1_8s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s2_8s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s2_8s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s2_8s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_0_dsp_dc_reg_s2_8s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_1_UNION
 结构说明  : WC_DC_REG_AT1_RPT_1 寄存器结构定义。地址偏移量:0x644，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_1_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_8s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_8s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S4的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S4的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_1_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s3_8s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s3_8s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s3_8s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s3_8s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s4_8s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s4_8s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s4_8s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_1_dsp_dc_reg_s4_8s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_2_UNION
 结构说明  : WC_DC_REG_AT1_RPT_2 寄存器结构定义。地址偏移量:0x648，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_2_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_8s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_8s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S6的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S6的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_2_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s5_8s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s5_8s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s5_8s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s5_8s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s6_8s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s6_8s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s6_8s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_2_dsp_dc_reg_s6_8s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_3_UNION
 结构说明  : WC_DC_REG_AT1_RPT_3 寄存器结构定义。地址偏移量:0x64C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_3_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_8s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，8档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_8s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，8档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，8档AAGC S8的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，8档AAGC S8的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_3_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s7_8s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s7_8s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s7_8s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s7_8s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s8_8s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s8_8s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s8_8s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_3_dsp_dc_reg_s8_8s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_4_UNION
 结构说明  : WC_DC_REG_AT1_RPT_4 寄存器结构定义。地址偏移量:0x650，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_4_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_5s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_5s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S2的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S2的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_4_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s1_5s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s1_5s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s1_5s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s1_5s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s2_5s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s2_5s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s2_5s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_4_dsp_dc_reg_s2_5s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_5_UNION
 结构说明  : WC_DC_REG_AT1_RPT_5 寄存器结构定义。地址偏移量:0x654，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_5_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_5s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_5s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S4的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S4的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_5_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s3_5s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s3_5s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s3_5s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s3_5s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s4_5s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s4_5s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s4_5s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_5_dsp_dc_reg_s4_5s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_6_UNION
 结构说明  : WC_DC_REG_AT1_RPT_6 寄存器结构定义。地址偏移量:0x658，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_6_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_5s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_5s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S6的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S6的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_6_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s5_5s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s5_5s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s5_5s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s5_5s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s6_5s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s6_5s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s6_5s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_6_dsp_dc_reg_s6_5s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT1_RPT_7_UNION
 结构说明  : WC_DC_REG_AT1_RPT_7 寄存器结构定义。地址偏移量:0x65C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at1_rpt_7_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_5s_i_rpt_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路，5档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_5s_q_rpt_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路，5档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_i_rpt_at1 : 8;  /* bit[16-23]: WC模 天线1 I路，5档AAGC S8的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_q_rpt_at1 : 8;  /* bit[24-31]: WC模 天线1 Q路，5档AAGC S8的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT1_RPT_7_UNION;
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s7_5s_i_rpt_at1_START  (0)
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s7_5s_i_rpt_at1_END    (7)
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s7_5s_q_rpt_at1_START  (8)
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s7_5s_q_rpt_at1_END    (15)
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s8_5s_i_rpt_at1_START  (16)
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s8_5s_i_rpt_at1_END    (23)
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s8_5s_q_rpt_at1_START  (24)
#define WBBP_WC_DC_REG_AT1_RPT_7_dsp_dc_reg_s8_5s_q_rpt_at1_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_0_UNION
 结构说明  : WC_DC_REG_AT2_RPT_0 寄存器结构定义。地址偏移量:0x660，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_0_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_8s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_8s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S2的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_8s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，8档AAGC S2的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_0_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s1_8s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s1_8s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s1_8s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s1_8s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s2_8s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s2_8s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s2_8s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_0_dsp_dc_reg_s2_8s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_1_UNION
 结构说明  : WC_DC_REG_AT2_RPT_1 寄存器结构定义。地址偏移量:0x664，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_1_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_8s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_8s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S4的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_8s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，8档AAGC S4的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_1_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s3_8s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s3_8s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s3_8s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s3_8s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s4_8s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s4_8s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s4_8s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_1_dsp_dc_reg_s4_8s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_2_UNION
 结构说明  : WC_DC_REG_AT2_RPT_2 寄存器结构定义。地址偏移量:0x668，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_2_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_8s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_8s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S6的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_8s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，8档AAGC S6的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_2_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s5_8s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s5_8s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s5_8s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s5_8s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s6_8s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s6_8s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s6_8s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_2_dsp_dc_reg_s6_8s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_3_UNION
 结构说明  : WC_DC_REG_AT2_RPT_3 寄存器结构定义。地址偏移量:0x66C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_3_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_8s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，8档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_8s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，8档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，8档AAGC S8的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_8s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 I路，8档AAGC S8的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_3_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s7_8s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s7_8s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s7_8s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s7_8s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s8_8s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s8_8s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s8_8s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_3_dsp_dc_reg_s8_8s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_4_UNION
 结构说明  : WC_DC_REG_AT2_RPT_4 寄存器结构定义。地址偏移量:0x670，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_4_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s1_5s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，5档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s1_5s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，5档AAGC S1的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，5档AAGC S2的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s2_5s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，5档AAGC S2的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_4_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s1_5s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s1_5s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s1_5s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s1_5s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s2_5s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s2_5s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s2_5s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_4_dsp_dc_reg_s2_5s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_5_UNION
 结构说明  : WC_DC_REG_AT2_RPT_5 寄存器结构定义。地址偏移量:0x674，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_5_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s3_5s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，5档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s3_5s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，5档AAGC S3的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，5档AAGC S4的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s4_5s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，5档AAGC S4的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_5_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s3_5s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s3_5s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s3_5s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s3_5s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s4_5s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s4_5s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s4_5s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_5_dsp_dc_reg_s4_5s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_6_UNION
 结构说明  : WC_DC_REG_AT2_RPT_6 寄存器结构定义。地址偏移量:0x678，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_6_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s5_5s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，5档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s5_5s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，5档AAGC S5的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，5档AAGC S6的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s6_5s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，5档AAGC S6的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_6_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s5_5s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s5_5s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s5_5s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s5_5s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s6_5s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s6_5s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s6_5s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_6_dsp_dc_reg_s6_5s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_DC_REG_AT2_RPT_7_UNION
 结构说明  : WC_DC_REG_AT2_RPT_7 寄存器结构定义。地址偏移量:0x67C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_reg_at2_rpt_7_reg;
    struct
    {
        unsigned long  dsp_dc_reg_s7_5s_i_rpt_at2 : 8;  /* bit[0-7]  : WC模 天线2 I路，5档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s7_5s_q_rpt_at2 : 8;  /* bit[8-15] : WC模 天线2 Q路，5档AAGC S7的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_i_rpt_at2 : 8;  /* bit[16-23]: WC模 天线2 I路，5档AAGC S8的DC上报值，8bit有符号数。 */
        unsigned long  dsp_dc_reg_s8_5s_q_rpt_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路，5档AAGC S8的DC上报值，8bit有符号数。 */
    } reg;
} WBBP_WC_DC_REG_AT2_RPT_7_UNION;
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s7_5s_i_rpt_at2_START  (0)
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s7_5s_i_rpt_at2_END    (7)
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s7_5s_q_rpt_at2_START  (8)
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s7_5s_q_rpt_at2_END    (15)
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s8_5s_i_rpt_at2_START  (16)
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s8_5s_i_rpt_at2_END    (23)
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s8_5s_q_rpt_at2_START  (24)
#define WBBP_WC_DC_REG_AT2_RPT_7_dsp_dc_reg_s8_5s_q_rpt_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_FAST_DC_EN_UNION
 结构说明  : WC_FAST_DC_EN 寄存器结构定义。地址偏移量:0x680，初值:0x00000000，宽度:32
 寄存器说明: WC模快速DC切档功能开关
*****************************************************************************/
typedef union
{
    unsigned long      wc_fast_dc_en_reg;
    struct
    {
        unsigned long  dsp_dcoc_fast_en      : 1;  /* bit[0]   : WC模DC快速收敛功能开关。
                                                                 0：关闭DC快速收敛功能；
                                                                 1：打开DC快速收敛功能，在去直流一阶段重新启动时，DC直流初值为软件配置的DC初始值，或者硬件根据档位选出的DC初始值。
                                                                 W模
                                                                 TDS模不支持该功能，需要关闭。 */
        unsigned long  reserved_0            : 3;  /* bit[1-3] : 保留 */
        unsigned long  dsp_dc_reg_rpt_sel    : 2;  /* bit[4-5] : 硬件上报各档位DC直流值频率选择。
                                                                 00：按样点更新。
                                                                 01：按chip更新。
                                                                 10：按符号更新。
                                                                 11：reserved。
                                                                 W模使用，X模，TDS模不涉及。 */
        unsigned long  reserved_1            : 2;  /* bit[6-7] : 保留 */
        unsigned long  dsp_dc_fast_manual_en : 1;  /* bit[8]   : WC模软件DC直流初值配置使能。
                                                                 0：不使能。DC初值选择硬件根据档位选出的DC值。
                                                                 1：使能。DC初值选择软件接口配置的DC值。
                                                                 要dsp_dcoc_fast_en有效时，该初值才能生效。
                                                                 W模配置为0，C模配置为1，TDS模不涉及。 */
        unsigned long  reserved_2            : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_WC_FAST_DC_EN_UNION;
#define WBBP_WC_FAST_DC_EN_dsp_dcoc_fast_en_START       (0)
#define WBBP_WC_FAST_DC_EN_dsp_dcoc_fast_en_END         (0)
#define WBBP_WC_FAST_DC_EN_dsp_dc_reg_rpt_sel_START     (4)
#define WBBP_WC_FAST_DC_EN_dsp_dc_reg_rpt_sel_END       (5)
#define WBBP_WC_FAST_DC_EN_dsp_dc_fast_manual_en_START  (8)
#define WBBP_WC_FAST_DC_EN_dsp_dc_fast_manual_en_END    (8)


/*****************************************************************************
 结构名    : WBBP_DC_REG_LOAD_BP_UNION
 结构说明  : DC_REG_LOAD_BP 寄存器结构定义。地址偏移量:0x684，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dc_reg_load_bp_reg;
    struct
    {
        unsigned long  dsp_dc_reg_load_vld : 1;  /* bit[0]   : 硬件各档位DC_REG加载软件值使能脉冲。
                                                               W模使用，X模，TDS模不涉及。 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DC_REG_LOAD_BP_UNION;
#define WBBP_DC_REG_LOAD_BP_dsp_dc_reg_load_vld_START  (0)
#define WBBP_DC_REG_LOAD_BP_dsp_dc_reg_load_vld_END    (0)


/*****************************************************************************
 结构名    : WBBP_WC_DC_FAST_MANUAL_UNION
 结构说明  : WC_DC_FAST_MANUAL 寄存器结构定义。地址偏移量:0x688，初值:0x00000000，宽度:32
 寄存器说明: WC模DC配置值
*****************************************************************************/
typedef union
{
    unsigned long      wc_dc_fast_manual_reg;
    struct
    {
        unsigned long  dsp_dc_fast_manual_i_at1 : 8;  /* bit[0-7]  : WC模 天线1 I路DC配置值，8bit有符号数。
                                                                     配置值 = DC直流值/4，并限幅到
                                                                     [2^7-1,(-2^7+1)]范围内。 */
        unsigned long  dsp_dc_fast_manual_q_at1 : 8;  /* bit[8-15] : WC模 天线1 Q路DC配置值，8bit有符号数。
                                                                     配置值 = DC直流值/4，并限幅到
                                                                     [2^7-1,(-2^7+1)]范围内。 */
        unsigned long  dsp_dc_fast_manual_i_at2 : 8;  /* bit[16-23]: WC模 天线2 I路DC配置值，8bit有符号数。
                                                                     配置值 = DC直流值/4，并限幅到
                                                                     [2^7-1,(-2^7+1)]范围内。 */
        unsigned long  dsp_dc_fast_manual_q_at2 : 8;  /* bit[24-31]: WC模 天线2 Q路DC配置值，8bit有符号数。
                                                                     配置值 = DC直流值/4，并限幅到
                                                                     [2^7-1,(-2^7+1)]范围内。 */
    } reg;
} WBBP_WC_DC_FAST_MANUAL_UNION;
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_i_at1_START  (0)
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_i_at1_END    (7)
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_q_at1_START  (8)
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_q_at1_END    (15)
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_i_at2_START  (16)
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_i_at2_END    (23)
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_q_at2_START  (24)
#define WBBP_WC_DC_FAST_MANUAL_dsp_dc_fast_manual_q_at2_END    (31)


/*****************************************************************************
 结构名    : WBBP_WC_FAST_AGC_EN_UNION
 结构说明  : WC_FAST_AGC_EN 寄存器结构定义。地址偏移量:0x68C，初值:0x00000000，宽度:32
 寄存器说明: WC模快速AGC功能开关
*****************************************************************************/
typedef union
{
    unsigned long      wc_fast_agc_en_reg;
    struct
    {
        unsigned long  dsp_fast_agc_en : 1;  /* bit[0]   : 快速AGC切档使能。
                                                           0：关闭快速AGC切档；
                                                           1：打开快速AGC切档。
                                                           W模使用。C/TDS不涉及。 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_WC_FAST_AGC_EN_UNION;
#define WBBP_WC_FAST_AGC_EN_dsp_fast_agc_en_START  (0)
#define WBBP_WC_FAST_AGC_EN_dsp_fast_agc_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_WDRX_AGC_OPEN_EN_UNION
 结构说明  : WDRX_AGC_OPEN_EN 寄存器结构定义。地址偏移量:0x690，初值:0x00000000，宽度:32
 寄存器说明: W模2ms解寻呼寄存器
*****************************************************************************/
typedef union
{
    unsigned long      wdrx_agc_open_en_reg;
    struct
    {
        unsigned long  dsp_wdrx_agc_open_en : 1;  /* bit[0]   : WDRX唤醒解寻呼模式下AGC自动打开使能。
                                                                0：AGC只通过软件开关打开。
                                                                1：WDRX唤醒解寻呼模式下，AGC在软件配置开关打开后，延迟等待到BBP自动打开脉冲才启动。
                                                                W模使用。C/TDS不涉及。 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_WDRX_AGC_OPEN_EN_UNION;
#define WBBP_WDRX_AGC_OPEN_EN_dsp_wdrx_agc_open_en_START  (0)
#define WBBP_WDRX_AGC_OPEN_EN_dsp_wdrx_agc_open_en_END    (0)


/***======================================================================***
                     (2/10) register_define_w_dlfe_dcsc
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_WAGC_SAT_NUM_DCSC_UNION
 结构说明  : WAGC_SAT_NUM_DCSC 寄存器结构定义。地址偏移量:0x268，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wagc_sat_num_dcsc_reg;
    struct
    {
        unsigned long  dagc_sat_num_1f_at1_dcsc : 16; /* bit[0-15] : 天线1一帧内DAGC IQ数据饱和次数。 */
        unsigned long  dagc_sat_num_1f_at2_dcsc : 16; /* bit[16-31]: 天线2一帧内DAGC IQ数据饱和次数。 */
    } reg;
} WBBP_WAGC_SAT_NUM_DCSC_UNION;
#define WBBP_WAGC_SAT_NUM_DCSC_dagc_sat_num_1f_at1_dcsc_START  (0)
#define WBBP_WAGC_SAT_NUM_DCSC_dagc_sat_num_1f_at1_dcsc_END    (15)
#define WBBP_WAGC_SAT_NUM_DCSC_dagc_sat_num_1f_at2_dcsc_START  (16)
#define WBBP_WAGC_SAT_NUM_DCSC_dagc_sat_num_1f_at2_dcsc_END    (31)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_CFG_AT1_DCSC_UNION
 结构说明  : INIT_AGC_CFG_AT1_DCSC 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_cfg_at1_dcsc_reg;
    struct
    {
        unsigned long  dsp_init_drssi_25db_at1_dcsc : 9;  /* bit[0-8]  : 刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                         说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  dsp_init_rssi_rf_at1_dcsc    : 11; /* bit[9-19] : 刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
                                                                         说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  reserved                     : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_CFG_AT1_DCSC_UNION;
#define WBBP_INIT_AGC_CFG_AT1_DCSC_dsp_init_drssi_25db_at1_dcsc_START  (0)
#define WBBP_INIT_AGC_CFG_AT1_DCSC_dsp_init_drssi_25db_at1_dcsc_END    (8)
#define WBBP_INIT_AGC_CFG_AT1_DCSC_dsp_init_rssi_rf_at1_dcsc_START     (9)
#define WBBP_INIT_AGC_CFG_AT1_DCSC_dsp_init_rssi_rf_at1_dcsc_END       (19)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_CFG_AT2_DCSC_UNION
 结构说明  : INIT_AGC_CFG_AT2_DCSC 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_cfg_at2_dcsc_reg;
    struct
    {
        unsigned long  dsp_init_drssi_25db_at2_dcsc : 9;  /* bit[0-8]  : 刚刚打开AGC时，BBP使用此值查表DAGC ROM，单位0.25dB。
                                                                         说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  dsp_init_rssi_rf_at2_dcsc    : 11; /* bit[9-19] : 刚刚打开AGC时，BBP使用此值进行能量测量，单位0.125dB。
                                                                         说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。DRX唤醒时，打开AGC之前，软件将之前读取的值配置到此寄存器。 */
        unsigned long  reserved                     : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_CFG_AT2_DCSC_UNION;
#define WBBP_INIT_AGC_CFG_AT2_DCSC_dsp_init_drssi_25db_at2_dcsc_START  (0)
#define WBBP_INIT_AGC_CFG_AT2_DCSC_dsp_init_drssi_25db_at2_dcsc_END    (8)
#define WBBP_INIT_AGC_CFG_AT2_DCSC_dsp_init_rssi_rf_at2_dcsc_START     (9)
#define WBBP_INIT_AGC_CFG_AT2_DCSC_dsp_init_rssi_rf_at2_dcsc_END       (19)


/*****************************************************************************
 结构名    : WBBP_INTER_AGC_CFG_AT1_DCSC_UNION
 结构说明  : INTER_AGC_CFG_AT1_DCSC 寄存器结构定义。地址偏移量:0x40C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      inter_agc_cfg_at1_dcsc_reg;
    struct
    {
        unsigned long  dsp_inter_drssi_25db_at1_dcsc : 9;  /* bit[0-8]  : 刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。 */
        unsigned long  dsp_inter_rssi_rf_at1_dcsc    : 11; /* bit[9-19] : 刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。 */
        unsigned long  reserved                      : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INTER_AGC_CFG_AT1_DCSC_UNION;
#define WBBP_INTER_AGC_CFG_AT1_DCSC_dsp_inter_drssi_25db_at1_dcsc_START  (0)
#define WBBP_INTER_AGC_CFG_AT1_DCSC_dsp_inter_drssi_25db_at1_dcsc_END    (8)
#define WBBP_INTER_AGC_CFG_AT1_DCSC_dsp_inter_rssi_rf_at1_dcsc_START     (9)
#define WBBP_INTER_AGC_CFG_AT1_DCSC_dsp_inter_rssi_rf_at1_dcsc_END       (19)


/*****************************************************************************
 结构名    : WBBP_INTER_AGC_CFG_AT2_DCSC_UNION
 结构说明  : INTER_AGC_CFG_AT2_DCSC 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      inter_agc_cfg_at2_dcsc_reg;
    struct
    {
        unsigned long  dsp_inter_drssi_25db_at2_dcsc : 9;  /* bit[0-8]  : 刚刚进入异频GAP时，BBP使用此值查表DAGC ROM，单位0.25dB。 */
        unsigned long  dsp_inter_rssi_rf_at2_dcsc    : 11; /* bit[9-19] : 刚刚进入异频GAP时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。 */
        unsigned long  reserved                      : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INTER_AGC_CFG_AT2_DCSC_UNION;
#define WBBP_INTER_AGC_CFG_AT2_DCSC_dsp_inter_drssi_25db_at2_dcsc_START  (0)
#define WBBP_INTER_AGC_CFG_AT2_DCSC_dsp_inter_drssi_25db_at2_dcsc_END    (8)
#define WBBP_INTER_AGC_CFG_AT2_DCSC_dsp_inter_rssi_rf_at2_dcsc_START     (9)
#define WBBP_INTER_AGC_CFG_AT2_DCSC_dsp_inter_rssi_rf_at2_dcsc_END       (19)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG0_AT1_DCSC_UNION
 结构说明  : INIT_SCDC_AGC_CFG0_AT1_DCSC 寄存器结构定义。地址偏移量:0xA1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg0_at1_dcsc_reg;
    struct
    {
        unsigned long  dsp_scdc_rssi_rf_at1_dcsc : 11; /* bit[0-10] : RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。 */
        unsigned long  reserved                  : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG0_AT1_DCSC_UNION;
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_DCSC_dsp_scdc_rssi_rf_at1_dcsc_START  (0)
#define WBBP_INIT_SCDC_AGC_CFG0_AT1_DCSC_dsp_scdc_rssi_rf_at1_dcsc_END    (10)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_UNION
 结构说明  : INIT_SCDC_AGC_CFG1_AT1_DCSC 寄存器结构定义。地址偏移量:0xA20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg1_at1_dcsc_reg;
    struct
    {
        unsigned long  dsp_scdc_drssi_at1_dcsc         : 9;  /* bit[0-8]  : RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。 */
        unsigned long  reserved_0                      : 7;  /* bit[9-15] : 保留 */
        unsigned long  dsp_init_scdc_rssi_en_at1_dcsc  : 1;  /* bit[16]   : RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。 */
        unsigned long  reserved_1                      : 7;  /* bit[17-23]: 保留 */
        unsigned long  dsp_init_scdc_drssi_en_at1_dcsc : 1;  /* bit[24]   : 刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。 */
        unsigned long  reserved_2                      : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_UNION;
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_dsp_scdc_drssi_at1_dcsc_START          (0)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_dsp_scdc_drssi_at1_dcsc_END            (8)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_dsp_init_scdc_rssi_en_at1_dcsc_START   (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_dsp_init_scdc_rssi_en_at1_dcsc_END     (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_dsp_init_scdc_drssi_en_at1_dcsc_START  (24)
#define WBBP_INIT_SCDC_AGC_CFG1_AT1_DCSC_dsp_init_scdc_drssi_en_at1_dcsc_END    (24)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG0_AT2_DCSC_UNION
 结构说明  : INIT_SCDC_AGC_CFG0_AT2_DCSC 寄存器结构定义。地址偏移量:0xA24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg0_at2_dcsc_reg;
    struct
    {
        unsigned long  dsp_scdc_rssi_rf_at2_dcsc : 11; /* bit[0-10] : RF_SC/RF_DC切换刚刚完成时，BBP使用此值进行能量测量，需配置二进制补码值，单位0.125dB。 */
        unsigned long  reserved                  : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG0_AT2_DCSC_UNION;
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_DCSC_dsp_scdc_rssi_rf_at2_dcsc_START  (0)
#define WBBP_INIT_SCDC_AGC_CFG0_AT2_DCSC_dsp_scdc_rssi_rf_at2_dcsc_END    (10)


/*****************************************************************************
 结构名    : WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_UNION
 结构说明  : INIT_SCDC_AGC_CFG1_AT2_DCSC 寄存器结构定义。地址偏移量:0xA28，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_scdc_agc_cfg1_at2_dcsc_reg;
    struct
    {
        unsigned long  dsp_scdc_drssi_at2_dcsc         : 9;  /* bit[0-8]  : RF_SC/RF_DC切换刚刚完成时，BBP使用此值查表DAGC ROM，单位0.25dB。 */
        unsigned long  reserved_0                      : 7;  /* bit[9-15] : 保留 */
        unsigned long  dsp_init_scdc_rssi_en_at2_dcsc  : 1;  /* bit[16]   : RF_SC/RF_DC切换刚刚完成时，DSP配置天线口RSSI初始值使能。1，DSP配置天线口RSSI初始值；0，BBP继承以前的值。 */
        unsigned long  reserved_1                      : 7;  /* bit[17-23]: 保留 */
        unsigned long  dsp_init_scdc_drssi_en_at2_dcsc : 1;  /* bit[24]   : 刚刚进入RF_SC时，DSP配置0.25dB精度DRSSI初始值使能。1，DSP配置0.25dB精度DRSSI初始值；0，BBP继承以前的值。 */
        unsigned long  reserved_2                      : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_UNION;
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_dsp_scdc_drssi_at2_dcsc_START          (0)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_dsp_scdc_drssi_at2_dcsc_END            (8)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_dsp_init_scdc_rssi_en_at2_dcsc_START   (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_dsp_init_scdc_rssi_en_at2_dcsc_END     (16)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_dsp_init_scdc_drssi_en_at2_dcsc_START  (24)
#define WBBP_INIT_SCDC_AGC_CFG1_AT2_DCSC_dsp_init_scdc_drssi_en_at2_dcsc_END    (24)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_UNION
 结构说明  : INIT_AGC_RPT_CELL_AT1_DCSC 寄存器结构定义。地址偏移量:0xA2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_rpt_cell_at1_dcsc_reg;
    struct
    {
        unsigned long  dsp_rpt_cell_drssi_25db_at1_dcsc : 9;  /* bit[0-8]  : BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
                                                                             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_cell_rssi_rf_at1_dcsc    : 11; /* bit[9-19] : BBP上报天线口RSSI值（单载波），0.125dB精度。
                                                                             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  reserved                         : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_UNION;
#define WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_dsp_rpt_cell_drssi_25db_at1_dcsc_START  (0)
#define WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_dsp_rpt_cell_drssi_25db_at1_dcsc_END    (8)
#define WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_dsp_rpt_cell_rssi_rf_at1_dcsc_START     (9)
#define WBBP_INIT_AGC_RPT_CELL_AT1_DCSC_dsp_rpt_cell_rssi_rf_at1_dcsc_END       (19)


/*****************************************************************************
 结构名    : WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_UNION
 结构说明  : INIT_AGC_RPT_CELL_AT2_DCSC 寄存器结构定义。地址偏移量:0xA30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      init_agc_rpt_cell_at2_dcsc_reg;
    struct
    {
        unsigned long  dsp_rpt_cell_drssi_25db_at2_dcsc : 9;  /* bit[0-8]  : BBP上报0.25dB精度的DRSSI值（单载波），BBP使用此值查表DAGC ROM。
                                                                             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  dsp_rpt_cell_rssi_rf_at2_dcsc    : 11; /* bit[9-19] : BBP上报天线口RSSI值（单载波），0.125dB精度。
                                                                             说明：主要用于DRX流程。进入DRX睡眠时，软件从BBP读取寄存器获取。 */
        unsigned long  reserved                         : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_UNION;
#define WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_dsp_rpt_cell_drssi_25db_at2_dcsc_START  (0)
#define WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_dsp_rpt_cell_drssi_25db_at2_dcsc_END    (8)
#define WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_dsp_rpt_cell_rssi_rf_at2_dcsc_START     (9)
#define WBBP_INIT_AGC_RPT_CELL_AT2_DCSC_dsp_rpt_cell_rssi_rf_at2_dcsc_END       (19)


/***======================================================================***
                     (3/10) register_define_wt_mctrl
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_WT_DBG_EN_UNION
 结构说明  : WT_DBG_EN 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: DBG数据进行工作使能
*****************************************************************************/
typedef union
{
    unsigned long      wt_dbg_en_reg;
    struct
    {
        unsigned long  wt_dbg_en           : 1;  /* bit[0]   : W模式与TDS模式数据采集使能：
                                                               0：不使能；
                                                               1：使能； */
        unsigned long  w_udl_sel           : 1;  /* bit[1]   : W模式上、下行数据选择：
                                                               0：选择下行数据；
                                                               1：选择上行数据； */
        unsigned long  reserved_0          : 2;  /* bit[2-3] : 保留 */
        unsigned long  dsp2mux_dbg_clk_sel : 1;  /* bit[4]   : dbg时钟选择 */
        unsigned long  reserved_1          : 27; /* bit[5-31]: 保留 */
    } reg;
} WBBP_WT_DBG_EN_UNION;
#define WBBP_WT_DBG_EN_wt_dbg_en_START            (0)
#define WBBP_WT_DBG_EN_wt_dbg_en_END              (0)
#define WBBP_WT_DBG_EN_w_udl_sel_START            (1)
#define WBBP_WT_DBG_EN_w_udl_sel_END              (1)
#define WBBP_WT_DBG_EN_dsp2mux_dbg_clk_sel_START  (4)
#define WBBP_WT_DBG_EN_dsp2mux_dbg_clk_sel_END    (4)


/*****************************************************************************
 结构名    : WBBP_ZSP_INT_FLAG_UNION
 结构说明  : ZSP_INT_FLAG 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: ZSP1中断标志寄存器
*****************************************************************************/
typedef union
{
    unsigned long      zsp_int_flag_reg;
    struct
    {
        unsigned long  rx_half    : 1;  /* bit[0]   : 接收数据存储器半满中断标志：0此中断未产生；1 此中断产生。 */
        unsigned long  rx_full    : 1;  /* bit[1]   : 接收数据存储器全满中断标志：0此中断未产生；1 此中断产生。 */
        unsigned long  rx_finish  : 1;  /* bit[2]   : 接收数据存储器完成中断标志，同时是其它模块上报参数有效中断标志：0此中断未产生；1 此中断产生。 */
        unsigned long  ad_end_flg : 1;  /* bit[3]   : AD_STOP中断时，接收数据保存位置：0 前半个FIFO；1 后半个FIFO。 */
        unsigned long  reserved_0 : 1;  /* bit[4]   : 保留 */
        unsigned long  tx_half    : 1;  /* bit[5]   : 发送存储器半空中断标志：0此中断未产生；1 此中断产生。 */
        unsigned long  tx_full    : 1;  /* bit[6]   : 发送存储器全空中断标志：0此中断未产生；1 此中断产生。 */
        unsigned long  tx_finish  : 1;  /* bit[7]   : 发送完成中断标志：0此中断未产生；1 此中断产生。 */
        unsigned long  reserved_1 : 24; /* bit[8-31]: 保留 */
    } reg;
} WBBP_ZSP_INT_FLAG_UNION;
#define WBBP_ZSP_INT_FLAG_rx_half_START     (0)
#define WBBP_ZSP_INT_FLAG_rx_half_END       (0)
#define WBBP_ZSP_INT_FLAG_rx_full_START     (1)
#define WBBP_ZSP_INT_FLAG_rx_full_END       (1)
#define WBBP_ZSP_INT_FLAG_rx_finish_START   (2)
#define WBBP_ZSP_INT_FLAG_rx_finish_END     (2)
#define WBBP_ZSP_INT_FLAG_ad_end_flg_START  (3)
#define WBBP_ZSP_INT_FLAG_ad_end_flg_END    (3)
#define WBBP_ZSP_INT_FLAG_tx_half_START     (5)
#define WBBP_ZSP_INT_FLAG_tx_half_END       (5)
#define WBBP_ZSP_INT_FLAG_tx_full_START     (6)
#define WBBP_ZSP_INT_FLAG_tx_full_END       (6)
#define WBBP_ZSP_INT_FLAG_tx_finish_START   (7)
#define WBBP_ZSP_INT_FLAG_tx_finish_END     (7)


/*****************************************************************************
 结构名    : WBBP_RX_ADDR_UNION
 结构说明  : RX_ADDR 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 接收存储器地址寄存器
*****************************************************************************/
typedef union
{
    unsigned long      rx_addr_reg;
    struct
    {
        unsigned long  ad_end_addr : 16; /* bit[0-15] : 接收数据存储器地址；当AD接收结束时，指示接收存储器的当前地址。 */
        unsigned long  reserved    : 16; /* bit[16-31]: 保留 */
    } reg;
} WBBP_RX_ADDR_UNION;
#define WBBP_RX_ADDR_ad_end_addr_START  (0)
#define WBBP_RX_ADDR_ad_end_addr_END    (15)


/*****************************************************************************
 结构名    : WBBP_ZSP_INT_MASK_UNION
 结构说明  : ZSP_INT_MASK 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: ZSP1中断屏蔽寄存器
*****************************************************************************/
typedef union
{
    unsigned long      zsp_int_mask_reg;
    struct
    {
        unsigned long  rx_half_mask   : 1;  /* bit[0]   : 接收存储器半满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。 */
        unsigned long  rx_full_mask   : 1;  /* bit[1]   : 接收存储器全满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。 */
        unsigned long  rx_finish_mask : 1;  /* bit[2]   : 接收完成中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。 */
        unsigned long  reserved_0     : 1;  /* bit[3]   : 保留 */
        unsigned long  tx_half_mask   : 1;  /* bit[4]   : 发送存储器半满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。 */
        unsigned long  tx_full_mask   : 1;  /* bit[5]   : 发送存储器全满中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。 */
        unsigned long  tx_finish_mask : 1;  /* bit[6]   : 发送完成中断屏蔽位：1不屏蔽此中断；0屏蔽此中断，相应的中断状态位仍被置位。 */
        unsigned long  reserved_1     : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_ZSP_INT_MASK_UNION;
#define WBBP_ZSP_INT_MASK_rx_half_mask_START    (0)
#define WBBP_ZSP_INT_MASK_rx_half_mask_END      (0)
#define WBBP_ZSP_INT_MASK_rx_full_mask_START    (1)
#define WBBP_ZSP_INT_MASK_rx_full_mask_END      (1)
#define WBBP_ZSP_INT_MASK_rx_finish_mask_START  (2)
#define WBBP_ZSP_INT_MASK_rx_finish_mask_END    (2)
#define WBBP_ZSP_INT_MASK_tx_half_mask_START    (4)
#define WBBP_ZSP_INT_MASK_tx_half_mask_END      (4)
#define WBBP_ZSP_INT_MASK_tx_full_mask_START    (5)
#define WBBP_ZSP_INT_MASK_tx_full_mask_END      (5)
#define WBBP_ZSP_INT_MASK_tx_finish_mask_START  (6)
#define WBBP_ZSP_INT_MASK_tx_finish_mask_END    (6)


/*****************************************************************************
 结构名    : WBBP_INT_CLEAR_UNION
 结构说明  : INT_CLEAR 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 接口中断信号清除寄存器
*****************************************************************************/
typedef union
{
    unsigned long      int_clear_reg;
    struct
    {
        unsigned long  rx_half_clear   : 1;  /* bit[0]   : 接收存储器半满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。 */
        unsigned long  rx_full_clear   : 1;  /* bit[1]   : 接收存储器全满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。 */
        unsigned long  rx_finish_clear : 1;  /* bit[2]   : 接收完成中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。 */
        unsigned long  reserved_0      : 1;  /* bit[3]   : 保留 */
        unsigned long  tx_half_clear   : 1;  /* bit[4]   : 发送存储器半满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。 */
        unsigned long  tx_full_clear   : 1;  /* bit[5]   : 发送存储器全满中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。 */
        unsigned long  tx_finish_clear : 1;  /* bit[6]   : 发送完成中断清除位：0不清除此中断；1清除此中断，相应的中断状态位仍被置位。 */
        unsigned long  reserved_1      : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_INT_CLEAR_UNION;
#define WBBP_INT_CLEAR_rx_half_clear_START    (0)
#define WBBP_INT_CLEAR_rx_half_clear_END      (0)
#define WBBP_INT_CLEAR_rx_full_clear_START    (1)
#define WBBP_INT_CLEAR_rx_full_clear_END      (1)
#define WBBP_INT_CLEAR_rx_finish_clear_START  (2)
#define WBBP_INT_CLEAR_rx_finish_clear_END    (2)
#define WBBP_INT_CLEAR_tx_half_clear_START    (4)
#define WBBP_INT_CLEAR_tx_half_clear_END      (4)
#define WBBP_INT_CLEAR_tx_full_clear_START    (5)
#define WBBP_INT_CLEAR_tx_full_clear_END      (5)
#define WBBP_INT_CLEAR_tx_finish_clear_START  (6)
#define WBBP_INT_CLEAR_tx_finish_clear_END    (6)


/*****************************************************************************
 结构名    : WBBP_INT_ALARM_UNION
 结构说明  : INT_ALARM 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 接口中断信号告警寄存器
*****************************************************************************/
typedef union
{
    unsigned long      int_alarm_reg;
    struct
    {
        unsigned long  rx_half_alarm   : 1;  /* bit[0]   : 接收存储器半满中断告警位：
                                                           0不告警此中断；
                                                           1告警此中断。 */
        unsigned long  rx_full_alarm   : 1;  /* bit[1]   : 接收存储器全满中断告警位：
                                                           0不告警此中断；
                                                           1告警此中断。 */
        unsigned long  rx_finish_alarm : 1;  /* bit[2]   : 接收完成中断告警位：
                                                           0不告警此中断；
                                                           1告警此中断。 */
        unsigned long  reserved_0      : 1;  /* bit[3]   : 保留 */
        unsigned long  tx_half_alarm   : 1;  /* bit[4]   : 发送存储器半满中断告警位：
                                                           0不告警此中断；
                                                           1告警此中断。 */
        unsigned long  tx_full_alarm   : 1;  /* bit[5]   : 发送存储器全满中断告警位：
                                                           0不告警此中断；
                                                           1告警此中断。 */
        unsigned long  tx_finish_alarm : 1;  /* bit[6]   : 发送完成中断告警位：
                                                           0不告警此中断；
                                                           1告警此中断。 */
        unsigned long  reserved_1      : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_INT_ALARM_UNION;
#define WBBP_INT_ALARM_rx_half_alarm_START    (0)
#define WBBP_INT_ALARM_rx_half_alarm_END      (0)
#define WBBP_INT_ALARM_rx_full_alarm_START    (1)
#define WBBP_INT_ALARM_rx_full_alarm_END      (1)
#define WBBP_INT_ALARM_rx_finish_alarm_START  (2)
#define WBBP_INT_ALARM_rx_finish_alarm_END    (2)
#define WBBP_INT_ALARM_tx_half_alarm_START    (4)
#define WBBP_INT_ALARM_tx_half_alarm_END      (4)
#define WBBP_INT_ALARM_tx_full_alarm_START    (5)
#define WBBP_INT_ALARM_tx_full_alarm_END      (5)
#define WBBP_INT_ALARM_tx_finish_alarm_START  (6)
#define WBBP_INT_ALARM_tx_finish_alarm_END    (6)


/*****************************************************************************
 结构名    : WBBP_MEM_RRC_UNION
 结构说明  : MEM_RRC 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 上行memory和rrc输出信号
*****************************************************************************/
typedef union
{
    unsigned long      mem_rrc_reg;
    struct
    {
        unsigned long  mem_in_dl  : 16; /* bit[0-15] : [15]为下行W与TDS模式选择信号，0为W，1为TDS;
                                                       [14:12]为dlfe输出的ad_on1/ad_on/dvld；
                                                       [11:0]为dlfe输出I路数据的高12bit； */
        unsigned long  mem_out_ul : 16; /* bit[16-31]: [31]为上行W与TDS模式选择信号，0为W，1为TDS;
                                                       [30]为tds输入的da_on信号；
                                                       [29:28]为memory输出的da_on/dvld；
                                                       [27:16]为memory的输出I路数据高12bit； */
    } reg;
} WBBP_MEM_RRC_UNION;
#define WBBP_MEM_RRC_mem_in_dl_START   (0)
#define WBBP_MEM_RRC_mem_in_dl_END     (15)
#define WBBP_MEM_RRC_mem_out_ul_START  (16)
#define WBBP_MEM_RRC_mem_out_ul_END    (31)


/*****************************************************************************
 结构名    : WBBP_ABB_CODE_UNION
 结构说明  : ABB_CODE 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_code_reg;
    struct
    {
        unsigned long  dsp_abb_rx_code_sel   : 1;  /* bit[0]    : 上行采样数据格式标志 */
        unsigned long  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned long  dsp_abb_tx_code_sel   : 1;  /* bit[4]    : 下行采样数据格式标志 */
        unsigned long  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dsp_abb_shift_num_sel : 2;  /* bit[8-9]  : ABB */
        unsigned long  reserved_2            : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_ABB_CODE_UNION;
#define WBBP_ABB_CODE_dsp_abb_rx_code_sel_START    (0)
#define WBBP_ABB_CODE_dsp_abb_rx_code_sel_END      (0)
#define WBBP_ABB_CODE_dsp_abb_tx_code_sel_START    (4)
#define WBBP_ABB_CODE_dsp_abb_tx_code_sel_END      (4)
#define WBBP_ABB_CODE_dsp_abb_shift_num_sel_START  (8)
#define WBBP_ABB_CODE_dsp_abb_shift_num_sel_END    (9)


/*****************************************************************************
 结构名    : WBBP_ABB_DLY_UNION
 结构说明  : ABB_DLY 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_dly_reg;
    struct
    {
        unsigned long  dsp_rx_ant_num      : 1;  /* bit[0]    : 接收通道个数： */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  dsp_rx_ant_dly_sel  : 1;  /* bit[4]    : 定时偏差调整功能通道选择， */
        unsigned long  reserved_1          : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dsp_rx_ant_dly_en   : 1;  /* bit[8]    : 定时偏差调整功能打开使能，高电平有效。tds 专用。 */
        unsigned long  reserved_2          : 3;  /* bit[9-11] : 保留 */
        unsigned long  dsp_rx_ant_data_dly : 5;  /* bit[12-16]: 为了调整定时偏差，使 */
        unsigned long  reserved_3          : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_ABB_DLY_UNION;
#define WBBP_ABB_DLY_dsp_rx_ant_num_START       (0)
#define WBBP_ABB_DLY_dsp_rx_ant_num_END         (0)
#define WBBP_ABB_DLY_dsp_rx_ant_dly_sel_START   (4)
#define WBBP_ABB_DLY_dsp_rx_ant_dly_sel_END     (4)
#define WBBP_ABB_DLY_dsp_rx_ant_dly_en_START    (8)
#define WBBP_ABB_DLY_dsp_rx_ant_dly_en_END      (8)
#define WBBP_ABB_DLY_dsp_rx_ant_data_dly_START  (12)
#define WBBP_ABB_DLY_dsp_rx_ant_data_dly_END    (16)


/*****************************************************************************
 结构名    : WBBP_ABB_TRX_LOOP_UNION
 结构说明  : ABB_TRX_LOOP 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_trx_loop_reg;
    struct
    {
        unsigned long  dsp_abb_trx_loop_en       : 1;  /* bit[0]   : ABB */
        unsigned long  reserved_0                : 3;  /* bit[1-3] : 保留 */
        unsigned long  dsp_abb_trx_loop_mode_sel : 3;  /* bit[4-6] : ABB */
        unsigned long  reserved_1                : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_ABB_TRX_LOOP_UNION;
#define WBBP_ABB_TRX_LOOP_dsp_abb_trx_loop_en_START        (0)
#define WBBP_ABB_TRX_LOOP_dsp_abb_trx_loop_en_END          (0)
#define WBBP_ABB_TRX_LOOP_dsp_abb_trx_loop_mode_sel_START  (4)
#define WBBP_ABB_TRX_LOOP_dsp_abb_trx_loop_mode_sel_END    (6)


/*****************************************************************************
 结构名    : WBBP_ABB_FIFO_DBG_UNION
 结构说明  : ABB_FIFO_DBG 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_fifo_dbg_reg;
    struct
    {
        unsigned long  dsp_abb_rx_fifo0_state     : 1;  /* bit[0]    : RX  */
        unsigned long  reserved_0                 : 3;  /* bit[1-3]  : 保留 */
        unsigned long  dsp_abb_rx_fifo1_state     : 1;  /* bit[4]    : RX  */
        unsigned long  reserved_1                 : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dsp_abb_rx_fifo0_state_clr : 1;  /* bit[8]    : RX  */
        unsigned long  reserved_2                 : 3;  /* bit[9-11] : 保留 */
        unsigned long  dsp_abb_rx_fifo1_state_clr : 1;  /* bit[12]   : RX  */
        unsigned long  reserved_3                 : 19; /* bit[13-31]: 保留 */
    } reg;
} WBBP_ABB_FIFO_DBG_UNION;
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo0_state_START      (0)
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo0_state_END        (0)
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo1_state_START      (4)
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo1_state_END        (4)
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo0_state_clr_START  (8)
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo0_state_clr_END    (8)
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo1_state_clr_START  (12)
#define WBBP_ABB_FIFO_DBG_dsp_abb_rx_fifo1_state_clr_END    (12)


/*****************************************************************************
 结构名    : WBBP_SHARE_MEM_CTRL_UNION
 结构说明  : SHARE_MEM_CTRL 寄存器结构定义。地址偏移量:0x060，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      share_mem_ctrl_reg;
    struct
    {
        unsigned long  mem_ctrl_s    : 16; /* bit[0-15] :  */
        unsigned long  mem_ctrl_1w2r : 16; /* bit[16-31]: U&amp;TDS */
    } reg;
} WBBP_SHARE_MEM_CTRL_UNION;
#define WBBP_SHARE_MEM_CTRL_mem_ctrl_s_START     (0)
#define WBBP_SHARE_MEM_CTRL_mem_ctrl_s_END       (15)
#define WBBP_SHARE_MEM_CTRL_mem_ctrl_1w2r_START  (16)
#define WBBP_SHARE_MEM_CTRL_mem_ctrl_1w2r_END    (31)


/*****************************************************************************
 结构名    : WBBP_SHARE_ROM_CTRL_UNION
 结构说明  : SHARE_ROM_CTRL 寄存器结构定义。地址偏移量:0x064，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      share_rom_ctrl_reg;
    struct
    {
        unsigned long  mem_ctrl_1wr2wr : 16; /* bit[0-15] : U&amp;TDS */
        unsigned long  rom_ctrl        : 8;  /* bit[16-23]: U&amp;TDS */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_SHARE_ROM_CTRL_UNION;
#define WBBP_SHARE_ROM_CTRL_mem_ctrl_1wr2wr_START  (0)
#define WBBP_SHARE_ROM_CTRL_mem_ctrl_1wr2wr_END    (15)
#define WBBP_SHARE_ROM_CTRL_rom_ctrl_START         (16)
#define WBBP_SHARE_ROM_CTRL_rom_ctrl_END           (23)


/*****************************************************************************
 结构名    : WBBP_SYS_RST_UNION
 结构说明  : SYS_RST 寄存器结构定义。地址偏移量:0x068，初值:0x00000007，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_rst_reg;
    struct
    {
        unsigned long  clk_rst_ctrl  : 3;  /* bit[0-2]  : CLK */
        unsigned long  reserved_0    : 1;  /* bit[3]    : 保留 */
        unsigned long  sys_rst_ctrl  : 2;  /* bit[4-5]  : RST */
        unsigned long  reserved_1    : 2;  /* bit[6-7]  : 保留 */
        unsigned long  imi_rst_ctrl  : 2;  /* bit[8-9]  : ULFE */
        unsigned long  reserved_2    : 2;  /* bit[10-11]: 保留 */
        unsigned long  imi_addr_ctrl : 2;  /* bit[12-13]: IMI ADDR */
        unsigned long  reserved_3    : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_SYS_RST_UNION;
#define WBBP_SYS_RST_clk_rst_ctrl_START   (0)
#define WBBP_SYS_RST_clk_rst_ctrl_END     (2)
#define WBBP_SYS_RST_sys_rst_ctrl_START   (4)
#define WBBP_SYS_RST_sys_rst_ctrl_END     (5)
#define WBBP_SYS_RST_imi_rst_ctrl_START   (8)
#define WBBP_SYS_RST_imi_rst_ctrl_END     (9)
#define WBBP_SYS_RST_imi_addr_ctrl_START  (12)
#define WBBP_SYS_RST_imi_addr_ctrl_END    (13)


/*****************************************************************************
 结构名    : WBBP_DATA_FIFO_RST_UNION
 结构说明  : DATA_FIFO_RST 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_fifo_rst_reg;
    struct
    {
        unsigned long  data_fifo0_rst       : 1;  /* bit[0]   : fifo_0 */
        unsigned long  data_fifo0_full_rpt  : 1;  /* bit[1]   : FIFO_0 */
        unsigned long  data_fifo0_empty_rpt : 1;  /* bit[2]   : FIFO_0 */
        unsigned long  reserved_0           : 1;  /* bit[3]   : 保留 */
        unsigned long  data_fifo1_rst       : 1;  /* bit[4]   : fifo_1 */
        unsigned long  data_fifo1_full_rpt  : 1;  /* bit[5]   : FIFO_1 */
        unsigned long  data_fifo1_empty_rpt : 1;  /* bit[6]   : FIFO_1 */
        unsigned long  reserved_1           : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_DATA_FIFO_RST_UNION;
#define WBBP_DATA_FIFO_RST_data_fifo0_rst_START        (0)
#define WBBP_DATA_FIFO_RST_data_fifo0_rst_END          (0)
#define WBBP_DATA_FIFO_RST_data_fifo0_full_rpt_START   (1)
#define WBBP_DATA_FIFO_RST_data_fifo0_full_rpt_END     (1)
#define WBBP_DATA_FIFO_RST_data_fifo0_empty_rpt_START  (2)
#define WBBP_DATA_FIFO_RST_data_fifo0_empty_rpt_END    (2)
#define WBBP_DATA_FIFO_RST_data_fifo1_rst_START        (4)
#define WBBP_DATA_FIFO_RST_data_fifo1_rst_END          (4)
#define WBBP_DATA_FIFO_RST_data_fifo1_full_rpt_START   (5)
#define WBBP_DATA_FIFO_RST_data_fifo1_full_rpt_END     (5)
#define WBBP_DATA_FIFO_RST_data_fifo1_empty_rpt_START  (6)
#define WBBP_DATA_FIFO_RST_data_fifo1_empty_rpt_END    (6)


/***======================================================================***
                     (4/10) register_define_w_ulfe_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_APT_COMP_H_RAM_UNION
 结构说明  : APT_COMP_H_RAM 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: APT高增益档位功率补偿RAM
*****************************************************************************/
typedef union
{
    unsigned long      apt_comp_h_ram_reg;
    struct
    {
        unsigned long  apt_h_comp_ram_data_0 : 8;  /* bit[0-7]  : 每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。 */
        unsigned long  reserved_0            : 8;  /* bit[8-15] : 保留 */
        unsigned long  apt_h_comp_ram_data_1 : 8;  /* bit[16-23]: 每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。 */
        unsigned long  reserved_1            : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_APT_COMP_H_RAM_UNION;
#define WBBP_APT_COMP_H_RAM_apt_h_comp_ram_data_0_START  (0)
#define WBBP_APT_COMP_H_RAM_apt_h_comp_ram_data_0_END    (7)
#define WBBP_APT_COMP_H_RAM_apt_h_comp_ram_data_1_START  (16)
#define WBBP_APT_COMP_H_RAM_apt_h_comp_ram_data_1_END    (23)


/*****************************************************************************
 结构名    : WBBP_APT_COMP_M_RAM_UNION
 结构说明  : APT_COMP_M_RAM 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: APT中增益档位功率补偿RAM
*****************************************************************************/
typedef union
{
    unsigned long      apt_comp_m_ram_reg;
    struct
    {
        unsigned long  apt_m_comp_ram_data_0 : 8;  /* bit[0-7]  : 每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。 */
        unsigned long  reserved_0            : 8;  /* bit[8-15] : 保留 */
        unsigned long  apt_m_comp_ram_data_1 : 8;  /* bit[16-23]: 每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。 */
        unsigned long  reserved_1            : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_APT_COMP_M_RAM_UNION;
#define WBBP_APT_COMP_M_RAM_apt_m_comp_ram_data_0_START  (0)
#define WBBP_APT_COMP_M_RAM_apt_m_comp_ram_data_0_END    (7)
#define WBBP_APT_COMP_M_RAM_apt_m_comp_ram_data_1_START  (16)
#define WBBP_APT_COMP_M_RAM_apt_m_comp_ram_data_1_END    (23)


/*****************************************************************************
 结构名    : WBBP_APT_COMP_L_RAM_UNION
 结构说明  : APT_COMP_L_RAM 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: APT低增益档位功率补偿RAM
*****************************************************************************/
typedef union
{
    unsigned long      apt_comp_l_ram_reg;
    struct
    {
        unsigned long  apt_l_comp_ram_data_0 : 8;  /* bit[0-7]  : 每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。 */
        unsigned long  reserved_0            : 8;  /* bit[8-15] : 保留 */
        unsigned long  apt_l_comp_ram_data_1 : 8;  /* bit[16-23]: 每个地址位宽16比特，用于存放两个功率补偿值，高段存comp1[7:0],低段存comp0[7:0]，以此类推。 */
        unsigned long  reserved_1            : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_APT_COMP_L_RAM_UNION;
#define WBBP_APT_COMP_L_RAM_apt_l_comp_ram_data_0_START  (0)
#define WBBP_APT_COMP_L_RAM_apt_l_comp_ram_data_0_END    (7)
#define WBBP_APT_COMP_L_RAM_apt_l_comp_ram_data_1_START  (16)
#define WBBP_APT_COMP_L_RAM_apt_l_comp_ram_data_1_END    (23)


/*****************************************************************************
 结构名    : WBBP_APT_H_RAM_UNION
 结构说明  : APT_H_RAM 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: 高增益档位APT控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      apt_h_ram_reg;
    struct
    {
        unsigned long  apt_h_word_ram_data_0 : 9;  /* bit[0-8]  : 存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。 */
        unsigned long  reserved_0            : 7;  /* bit[9-15] : 保留 */
        unsigned long  apt_h_word_ram_data_1 : 9;  /* bit[16-24]: 存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。 */
        unsigned long  reserved_1            : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_APT_H_RAM_UNION;
#define WBBP_APT_H_RAM_apt_h_word_ram_data_0_START  (0)
#define WBBP_APT_H_RAM_apt_h_word_ram_data_0_END    (8)
#define WBBP_APT_H_RAM_apt_h_word_ram_data_1_START  (16)
#define WBBP_APT_H_RAM_apt_h_word_ram_data_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_APT_M_RAM_UNION
 结构说明  : APT_M_RAM 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: 中增益档位APT控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      apt_m_ram_reg;
    struct
    {
        unsigned long  apt_m_word_ram_data_0 : 9;  /* bit[0-8]  : 存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。 */
        unsigned long  reserved_0            : 7;  /* bit[9-15] : 保留 */
        unsigned long  apt_m_word_ram_data_1 : 9;  /* bit[16-24]: 存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。 */
        unsigned long  reserved_1            : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_APT_M_RAM_UNION;
#define WBBP_APT_M_RAM_apt_m_word_ram_data_0_START  (0)
#define WBBP_APT_M_RAM_apt_m_word_ram_data_0_END    (8)
#define WBBP_APT_M_RAM_apt_m_word_ram_data_1_START  (16)
#define WBBP_APT_M_RAM_apt_m_word_ram_data_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_APT_L_RAM_UNION
 结构说明  : APT_L_RAM 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: 低增益档位APT控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      apt_l_ram_reg;
    struct
    {
        unsigned long  apt_l_word_ram_data_0 : 9;  /* bit[0-8]  : 存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。 */
        unsigned long  reserved_0            : 7;  /* bit[9-15] : 保留 */
        unsigned long  apt_l_word_ram_data_1 : 9;  /* bit[16-24]: 存放APT控制字，每个地址位宽16比特，用于存放两个APT控制字，高段存apt_word1[7:0],低段存apt_word0[7:0]，以此类推（控制字在以前版本7比特基础上高比特加0，扩展成8比特）。 */
        unsigned long  reserved_1            : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_APT_L_RAM_UNION;
#define WBBP_APT_L_RAM_apt_l_word_ram_data_0_START  (0)
#define WBBP_APT_L_RAM_apt_l_word_ram_data_0_END    (8)
#define WBBP_APT_L_RAM_apt_l_word_ram_data_1_START  (16)
#define WBBP_APT_L_RAM_apt_l_word_ram_data_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS1_H_RAM_UNION
 结构说明  : PAVBIAS1_H_RAM 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: 高增益PA VBIAS1控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias1_h_ram_reg;
    struct
    {
        unsigned long  wpavbias1_h_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用) */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias1_h_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用) */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS1_H_RAM_UNION;
#define WBBP_PAVBIAS1_H_RAM_wpavbias1_h_word_0_START  (0)
#define WBBP_PAVBIAS1_H_RAM_wpavbias1_h_word_0_END    (8)
#define WBBP_PAVBIAS1_H_RAM_wpavbias1_h_word_1_START  (16)
#define WBBP_PAVBIAS1_H_RAM_wpavbias1_h_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS1_M_RAM_UNION
 结构说明  : PAVBIAS1_M_RAM 寄存器结构定义。地址偏移量:0x1C0，初值:0x00000000，宽度:32
 寄存器说明: 中增益PA VBIAS1控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias1_m_ram_reg;
    struct
    {
        unsigned long  wpavbias1_m_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用) */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias1_m_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用) */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS1_M_RAM_UNION;
#define WBBP_PAVBIAS1_M_RAM_wpavbias1_m_word_0_START  (0)
#define WBBP_PAVBIAS1_M_RAM_wpavbias1_m_word_0_END    (8)
#define WBBP_PAVBIAS1_M_RAM_wpavbias1_m_word_1_START  (16)
#define WBBP_PAVBIAS1_M_RAM_wpavbias1_m_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS1_L_RAM_UNION
 结构说明  : PAVBIAS1_L_RAM 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: 低增益PA VBIAS1控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias1_l_ram_reg;
    struct
    {
        unsigned long  wpavbias1_l_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用) */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias1_l_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。(MMMB(用低7bit)和EAGLE PA共用) */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS1_L_RAM_UNION;
#define WBBP_PAVBIAS1_L_RAM_wpavbias1_l_word_0_START  (0)
#define WBBP_PAVBIAS1_L_RAM_wpavbias1_l_word_0_END    (8)
#define WBBP_PAVBIAS1_L_RAM_wpavbias1_l_word_1_START  (16)
#define WBBP_PAVBIAS1_L_RAM_wpavbias1_l_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS2_H_RAM_UNION
 结构说明  : PAVBIAS2_H_RAM 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: 高增益PA VBIAS2控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias2_h_ram_reg;
    struct
    {
        unsigned long  wpavbias2_h_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias2_h_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS2_H_RAM_UNION;
#define WBBP_PAVBIAS2_H_RAM_wpavbias2_h_word_0_START  (0)
#define WBBP_PAVBIAS2_H_RAM_wpavbias2_h_word_0_END    (8)
#define WBBP_PAVBIAS2_H_RAM_wpavbias2_h_word_1_START  (16)
#define WBBP_PAVBIAS2_H_RAM_wpavbias2_h_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS2_M_RAM_UNION
 结构说明  : PAVBIAS2_M_RAM 寄存器结构定义。地址偏移量:0x280，初值:0x00000000，宽度:32
 寄存器说明: 中增益PA VBIAS2控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias2_m_ram_reg;
    struct
    {
        unsigned long  wpavbias2_m_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias2_m_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS2_M_RAM_UNION;
#define WBBP_PAVBIAS2_M_RAM_wpavbias2_m_word_0_START  (0)
#define WBBP_PAVBIAS2_M_RAM_wpavbias2_m_word_0_END    (8)
#define WBBP_PAVBIAS2_M_RAM_wpavbias2_m_word_1_START  (16)
#define WBBP_PAVBIAS2_M_RAM_wpavbias2_m_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS2_L_RAM_UNION
 结构说明  : PAVBIAS2_L_RAM 寄存器结构定义。地址偏移量:0x2C0，初值:0x00000000，宽度:32
 寄存器说明: 低增益PA VBIAS2控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias2_l_ram_reg;
    struct
    {
        unsigned long  wpavbias2_l_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias2_l_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS2_L_RAM_UNION;
#define WBBP_PAVBIAS2_L_RAM_wpavbias2_l_word_0_START  (0)
#define WBBP_PAVBIAS2_L_RAM_wpavbias2_l_word_0_END    (8)
#define WBBP_PAVBIAS2_L_RAM_wpavbias2_l_word_1_START  (16)
#define WBBP_PAVBIAS2_L_RAM_wpavbias2_l_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS3_H_RAM_UNION
 结构说明  : PAVBIAS3_H_RAM 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: 高增益PA VBIAS3控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias3_h_ram_reg;
    struct
    {
        unsigned long  wpavbias3_h_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias3_h_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS3_H_RAM_UNION;
#define WBBP_PAVBIAS3_H_RAM_wpavbias3_h_word_0_START  (0)
#define WBBP_PAVBIAS3_H_RAM_wpavbias3_h_word_0_END    (8)
#define WBBP_PAVBIAS3_H_RAM_wpavbias3_h_word_1_START  (16)
#define WBBP_PAVBIAS3_H_RAM_wpavbias3_h_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS3_M_RAM_UNION
 结构说明  : PAVBIAS3_M_RAM 寄存器结构定义。地址偏移量:0x340，初值:0x00000000，宽度:32
 寄存器说明: 中增益PA VBIAS3控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias3_m_ram_reg;
    struct
    {
        unsigned long  wpavbias3_m_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias3_m_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS3_M_RAM_UNION;
#define WBBP_PAVBIAS3_M_RAM_wpavbias3_m_word_0_START  (0)
#define WBBP_PAVBIAS3_M_RAM_wpavbias3_m_word_0_END    (8)
#define WBBP_PAVBIAS3_M_RAM_wpavbias3_m_word_1_START  (16)
#define WBBP_PAVBIAS3_M_RAM_wpavbias3_m_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAVBIAS3_L_RAM_UNION
 结构说明  : PAVBIAS3_L_RAM 寄存器结构定义。地址偏移量:0x380，初值:0x00000000，宽度:32
 寄存器说明: 低增益PA VBIAS3控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pavbias3_l_ram_reg;
    struct
    {
        unsigned long  wpavbias3_l_word_0 : 9;  /* bit[0-8]  : 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_0         : 7;  /* bit[9-15] : 保留 */
        unsigned long  wpavbias3_l_word_1 : 9;  /* bit[16-24]: 每个地址位宽18比特，用于存放两个PA VBIAS值。 */
        unsigned long  reserved_1         : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_PAVBIAS3_L_RAM_UNION;
#define WBBP_PAVBIAS3_L_RAM_wpavbias3_l_word_0_START  (0)
#define WBBP_PAVBIAS3_L_RAM_wpavbias3_l_word_0_END    (8)
#define WBBP_PAVBIAS3_L_RAM_wpavbias3_l_word_1_START  (16)
#define WBBP_PAVBIAS3_L_RAM_wpavbias3_l_word_1_END    (24)


/*****************************************************************************
 结构名    : WBBP_PAPOWCOMP_H_RAM_UNION
 结构说明  : PAPOWCOMP_H_RAM 寄存器结构定义。地址偏移量:0x3C0，初值:0x00000000，宽度:32
 寄存器说明: 高增益PA非线性功率补偿RAM
*****************************************************************************/
typedef union
{
    unsigned long      papowcomp_h_ram_reg;
    struct
    {
        unsigned long  pa_power_comp_h_0 : 8;  /* bit[0-7]  : 每个地址位宽16比特，用于存放两个有符号功率值。 */
        unsigned long  reserved_0        : 8;  /* bit[8-15] : 保留 */
        unsigned long  pa_power_comp_h_1 : 8;  /* bit[16-23]: 每个地址位宽16比特，用于存放两个有符号功率值。 */
        unsigned long  reserved_1        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_PAPOWCOMP_H_RAM_UNION;
#define WBBP_PAPOWCOMP_H_RAM_pa_power_comp_h_0_START  (0)
#define WBBP_PAPOWCOMP_H_RAM_pa_power_comp_h_0_END    (7)
#define WBBP_PAPOWCOMP_H_RAM_pa_power_comp_h_1_START  (16)
#define WBBP_PAPOWCOMP_H_RAM_pa_power_comp_h_1_END    (23)


/*****************************************************************************
 结构名    : WBBP_PAPOWCOMP_M_RAM_UNION
 结构说明  : PAPOWCOMP_M_RAM 寄存器结构定义。地址偏移量:0x400，初值:0x00000000，宽度:32
 寄存器说明: 中增益PA非线性功率补偿RAM
*****************************************************************************/
typedef union
{
    unsigned long      papowcomp_m_ram_reg;
    struct
    {
        unsigned long  pa_power_comp_m_0 : 8;  /* bit[0-7]  : 每个地址位宽16比特，用于存放两个有符号功率值。 */
        unsigned long  reserved_0        : 8;  /* bit[8-15] : 保留 */
        unsigned long  pa_power_comp_m_1 : 8;  /* bit[16-23]: 每个地址位宽16比特，用于存放两个有符号功率值。 */
        unsigned long  reserved_1        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_PAPOWCOMP_M_RAM_UNION;
#define WBBP_PAPOWCOMP_M_RAM_pa_power_comp_m_0_START  (0)
#define WBBP_PAPOWCOMP_M_RAM_pa_power_comp_m_0_END    (7)
#define WBBP_PAPOWCOMP_M_RAM_pa_power_comp_m_1_START  (16)
#define WBBP_PAPOWCOMP_M_RAM_pa_power_comp_m_1_END    (23)


/*****************************************************************************
 结构名    : WBBP_PAPOWCOMP_L_RAM_UNION
 结构说明  : PAPOWCOMP_L_RAM 寄存器结构定义。地址偏移量:0x440，初值:0x00000000，宽度:32
 寄存器说明: 低增益PA非线性功率补偿RAM
*****************************************************************************/
typedef union
{
    unsigned long      papowcomp_l_ram_reg;
    struct
    {
        unsigned long  pa_power_comp_l_0 : 8;  /* bit[0-7]  : 每个地址位宽16比特，用于存放两个有符号功率值。 */
        unsigned long  reserved_0        : 8;  /* bit[8-15] : 保留 */
        unsigned long  pa_power_comp_l_1 : 8;  /* bit[16-23]: 每个地址位宽16比特，用于存放两个有符号功率值。 */
        unsigned long  reserved_1        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_PAPOWCOMP_L_RAM_UNION;
#define WBBP_PAPOWCOMP_L_RAM_pa_power_comp_l_0_START  (0)
#define WBBP_PAPOWCOMP_L_RAM_pa_power_comp_l_0_END    (7)
#define WBBP_PAPOWCOMP_L_RAM_pa_power_comp_l_1_START  (16)
#define WBBP_PAPOWCOMP_L_RAM_pa_power_comp_l_1_END    (23)


/*****************************************************************************
 结构名    : WBBP_POW_ATTEN_H_RAM_UNION
 结构说明  : POW_ATTEN_H_RAM 寄存器结构定义。地址偏移量:0x6C0，初值:0x00000000，宽度:32
 寄存器说明: 高增益时RF和DBB回退控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pow_atten_h_ram_reg;
    struct
    {
        unsigned long  dbb_atten_h_ram_data : 8;  /* bit[0-7]  : 对应PA高增益,8比特数字功率回退值 */
        unsigned long  rf_atten_h_ram_data  : 16; /* bit[8-23] : 对应PA高增益,16比特RF控制字 */
        unsigned long  temp_comp_index_h    : 4;  /* bit[24-27]: 对应PA中增益,1控制字温补功率索引值(0~13) */
        unsigned long  reserved             : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_POW_ATTEN_H_RAM_UNION;
#define WBBP_POW_ATTEN_H_RAM_dbb_atten_h_ram_data_START  (0)
#define WBBP_POW_ATTEN_H_RAM_dbb_atten_h_ram_data_END    (7)
#define WBBP_POW_ATTEN_H_RAM_rf_atten_h_ram_data_START   (8)
#define WBBP_POW_ATTEN_H_RAM_rf_atten_h_ram_data_END     (23)
#define WBBP_POW_ATTEN_H_RAM_temp_comp_index_h_START     (24)
#define WBBP_POW_ATTEN_H_RAM_temp_comp_index_h_END       (27)


/*****************************************************************************
 结构名    : WBBP_POW_ATTEN_M_RAM_UNION
 结构说明  : POW_ATTEN_M_RAM 寄存器结构定义。地址偏移量:0x820，初值:0x00000000，宽度:32
 寄存器说明: 中增益时RF和DBB回退控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pow_atten_m_ram_reg;
    struct
    {
        unsigned long  dbb_atten_m_ram_data : 8;  /* bit[0-7]  : 对应PA中增益,8比特数字功率回退值 */
        unsigned long  rf_atten_m_ram_data  : 16; /* bit[8-23] : 对应PA中增益,16比特RF控制字 */
        unsigned long  temp_comp_index_m    : 4;  /* bit[24-27]: 对应PA中增益,1控制字温补功率索引值(0~13) */
        unsigned long  reserved             : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_POW_ATTEN_M_RAM_UNION;
#define WBBP_POW_ATTEN_M_RAM_dbb_atten_m_ram_data_START  (0)
#define WBBP_POW_ATTEN_M_RAM_dbb_atten_m_ram_data_END    (7)
#define WBBP_POW_ATTEN_M_RAM_rf_atten_m_ram_data_START   (8)
#define WBBP_POW_ATTEN_M_RAM_rf_atten_m_ram_data_END     (23)
#define WBBP_POW_ATTEN_M_RAM_temp_comp_index_m_START     (24)
#define WBBP_POW_ATTEN_M_RAM_temp_comp_index_m_END       (27)


/*****************************************************************************
 结构名    : WBBP_POW_ATTEN_L_RAM_UNION
 结构说明  : POW_ATTEN_L_RAM 寄存器结构定义。地址偏移量:0x980，初值:0x00000000，宽度:32
 寄存器说明: 低增益时RF和DBB回退控制字RAM
*****************************************************************************/
typedef union
{
    unsigned long      pow_atten_l_ram_reg;
    struct
    {
        unsigned long  dbb_atten_l_ram_data : 8;  /* bit[0-7]  : 对应PA低增益,8比特数字功率回退值 */
        unsigned long  rf_atten_l_ram_data  : 16; /* bit[8-23] : 对应PA低增益,16比特RF控制字 */
        unsigned long  temp_comp_index_l    : 4;  /* bit[24-27]: 对应PA低增益,控制字温补功率索引值(0~13) */
        unsigned long  reserved             : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_POW_ATTEN_L_RAM_UNION;
#define WBBP_POW_ATTEN_L_RAM_dbb_atten_l_ram_data_START  (0)
#define WBBP_POW_ATTEN_L_RAM_dbb_atten_l_ram_data_END    (7)
#define WBBP_POW_ATTEN_L_RAM_rf_atten_l_ram_data_START   (8)
#define WBBP_POW_ATTEN_L_RAM_rf_atten_l_ram_data_END     (23)
#define WBBP_POW_ATTEN_L_RAM_temp_comp_index_l_START     (24)
#define WBBP_POW_ATTEN_L_RAM_temp_comp_index_l_END       (27)


/*****************************************************************************
 结构名    : WBBP_DPD_RAM1_UNION
 结构说明  : DPD_RAM1 寄存器结构定义。地址偏移量:0xAE0，初值:0x00000000，宽度:32
 寄存器说明: DPD补偿表
*****************************************************************************/
typedef union
{
    unsigned long      dpd_ram1_reg;
    struct
    {
        unsigned long  dpd_comp_i : 12; /* bit[0-11] : DPD补偿I路系数 */
        unsigned long  dpd_comp_q : 12; /* bit[12-23]: DPD补偿Q路系数 */
        unsigned long  reserved   : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DPD_RAM1_UNION;
#define WBBP_DPD_RAM1_dpd_comp_i_START  (0)
#define WBBP_DPD_RAM1_dpd_comp_i_END    (11)
#define WBBP_DPD_RAM1_dpd_comp_q_START  (12)
#define WBBP_DPD_RAM1_dpd_comp_q_END    (23)


/***======================================================================***
                     (5/10) register_define_w_papd
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_DSP_PA_MODEL_UNION
 结构说明  : DSP_PA_MODEL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pa_model_reg;
    struct
    {
        unsigned long  dsp_pa_mode_ctrl : 2;  /* bit[0-1] : 2'b01，DSP强制PA增益为高；2'b10，DSP强制PA增益为中；2'b11，DSP强制PA增益为低；其他，由BBP自行控制。 */
        unsigned long  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DSP_PA_MODEL_UNION;
#define WBBP_DSP_PA_MODEL_dsp_pa_mode_ctrl_START  (0)
#define WBBP_DSP_PA_MODEL_dsp_pa_mode_ctrl_END    (1)


/*****************************************************************************
 结构名    : WBBP_PA_CTRL_WORD_UNION
 结构说明  : PA_CTRL_WORD 寄存器结构定义。地址偏移量:0x004，初值:0x00003310，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_ctrl_word_reg;
    struct
    {
        unsigned long  dsp_pa_high_ctrl : 2;  /* bit[0-1]  : PA高增益控制字，根据射频器件配置。Infineon高增益为2'b00。 */
        unsigned long  reserved_0       : 2;  /* bit[2-3]  : 保留 */
        unsigned long  dsp_pa_mid_ctrl  : 2;  /* bit[4-5]  : PA中增益控制字，根据射频器件配置。Infineon中增益为2'b01。 */
        unsigned long  reserved_1       : 2;  /* bit[6-7]  : 保留 */
        unsigned long  dsp_pa_low_ctrl  : 2;  /* bit[8-9]  : PA低增益控制字，根据射频器件配置。Infineon低增益为2'b11。 */
        unsigned long  reserved_2       : 2;  /* bit[10-11]: 保留 */
        unsigned long  dsp_pa_init_ctrl : 2;  /* bit[12-13]: PA初始增益控制字，根据射频器件配置。 */
        unsigned long  reserved_3       : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_PA_CTRL_WORD_UNION;
#define WBBP_PA_CTRL_WORD_dsp_pa_high_ctrl_START  (0)
#define WBBP_PA_CTRL_WORD_dsp_pa_high_ctrl_END    (1)
#define WBBP_PA_CTRL_WORD_dsp_pa_mid_ctrl_START   (4)
#define WBBP_PA_CTRL_WORD_dsp_pa_mid_ctrl_END     (5)
#define WBBP_PA_CTRL_WORD_dsp_pa_low_ctrl_START   (8)
#define WBBP_PA_CTRL_WORD_dsp_pa_low_ctrl_END     (9)
#define WBBP_PA_CTRL_WORD_dsp_pa_init_ctrl_START  (12)
#define WBBP_PA_CTRL_WORD_dsp_pa_init_ctrl_END    (13)


/*****************************************************************************
 结构名    : WBBP_W_TX_PA_GAIN_UNION
 结构说明  : W_TX_PA_GAIN 寄存器结构定义。地址偏移量:0x008，初值:0x01E190F0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_tx_pa_gain_reg;
    struct
    {
        unsigned long  dsp_w_pa_high_gain : 9;  /* bit[0-8]  : 当PA处于高增益模式下PA的增益大小，单位0.1dB，无符号数。 */
        unsigned long  dsp_w_pa_mid_gain  : 9;  /* bit[9-17] : 当PA处于中增益模式下PA的增益大小，单位0.1dB，无符号数。 */
        unsigned long  dsp_w_pa_low_gain  : 9;  /* bit[18-26]: 当PA处于低增益模式下PA的增益大小，单位0.1dB，无符号数。 */
        unsigned long  reserved           : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_W_TX_PA_GAIN_UNION;
#define WBBP_W_TX_PA_GAIN_dsp_w_pa_high_gain_START  (0)
#define WBBP_W_TX_PA_GAIN_dsp_w_pa_high_gain_END    (8)
#define WBBP_W_TX_PA_GAIN_dsp_w_pa_mid_gain_START   (9)
#define WBBP_W_TX_PA_GAIN_dsp_w_pa_mid_gain_END     (17)
#define WBBP_W_TX_PA_GAIN_dsp_w_pa_low_gain_START   (18)
#define WBBP_W_TX_PA_GAIN_dsp_w_pa_low_gain_END     (26)


/*****************************************************************************
 结构名    : WBBP_PA_HM_THRESHOLD_UNION
 结构说明  : PA_HM_THRESHOLD 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_hm_threshold_reg;
    struct
    {
        unsigned long  dsp_pa_h2m_threshold : 11; /* bit[0-10] : PA从高增益到中增益的切换门限，二进制补码。 */
        unsigned long  reserved_0           : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_pa_m2h_threshold : 11; /* bit[16-26]: PA从中增益到高增益的切换门限，二进制补码。 */
        unsigned long  reserved_1           : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_PA_HM_THRESHOLD_UNION;
#define WBBP_PA_HM_THRESHOLD_dsp_pa_h2m_threshold_START  (0)
#define WBBP_PA_HM_THRESHOLD_dsp_pa_h2m_threshold_END    (10)
#define WBBP_PA_HM_THRESHOLD_dsp_pa_m2h_threshold_START  (16)
#define WBBP_PA_HM_THRESHOLD_dsp_pa_m2h_threshold_END    (26)


/*****************************************************************************
 结构名    : WBBP_PA_ML_THRESHOLD_UNION
 结构说明  : PA_ML_THRESHOLD 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_ml_threshold_reg;
    struct
    {
        unsigned long  dsp_pa_m2l_threshold : 11; /* bit[0-10] : PA从中增益到低增益的切换门限，二进制补码。支持PA高、中两档模式时配置成0x400。 */
        unsigned long  reserved_0           : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_pa_l2m_threshold : 11; /* bit[16-26]: PA从低增益到中增益的切换门限，二进制补码。支持PA高、中两档模式时配置成0x400。 */
        unsigned long  reserved_1           : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_PA_ML_THRESHOLD_UNION;
#define WBBP_PA_ML_THRESHOLD_dsp_pa_m2l_threshold_START  (0)
#define WBBP_PA_ML_THRESHOLD_dsp_pa_m2l_threshold_END    (10)
#define WBBP_PA_ML_THRESHOLD_dsp_pa_l2m_threshold_START  (16)
#define WBBP_PA_ML_THRESHOLD_dsp_pa_l2m_threshold_END    (26)


/*****************************************************************************
 结构名    : WBBP_PA_HM_MODE_UNION
 结构说明  : PA_HM_MODE 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_hm_mode_reg;
    struct
    {
        unsigned long  dsp_nv_pa_h_mode : 11; /* bit[0-10] : PA高增益表最小地址对应的功率取负，二进制补码。 */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_m_mode : 11; /* bit[16-26]: PA中增益表最小地址对应的功率取负，二进制补码。 */
        unsigned long  reserved_1       : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_PA_HM_MODE_UNION;
#define WBBP_PA_HM_MODE_dsp_nv_pa_h_mode_START  (0)
#define WBBP_PA_HM_MODE_dsp_nv_pa_h_mode_END    (10)
#define WBBP_PA_HM_MODE_dsp_nv_pa_m_mode_START  (16)
#define WBBP_PA_HM_MODE_dsp_nv_pa_m_mode_END    (26)


/*****************************************************************************
 结构名    : WBBP_PA_L_MODE_UNION
 结构说明  : PA_L_MODE 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_l_mode_reg;
    struct
    {
        unsigned long  dsp_nv_pa_l_mode : 11; /* bit[0-10] : PA低增益表最小地址对应的功率取负，二进制补码。 */
        unsigned long  reserved         : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_PA_L_MODE_UNION;
#define WBBP_PA_L_MODE_dsp_nv_pa_l_mode_START  (0)
#define WBBP_PA_L_MODE_dsp_nv_pa_l_mode_END    (10)


/*****************************************************************************
 结构名    : WBBP_PC_DELTA_POW_FREQ_UNION
 结构说明  : PC_DELTA_POW_FREQ 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pc_delta_pow_freq_reg;
    struct
    {
        unsigned long  dsp_delta_pow_freq : 10; /* bit[0-9]  : 单板功率频率补偿值，单位0.1dBm。由于单板功率的偏差造成发射功率的偏差。DSP根据当前的单板的频率偏差信息，选择偏差值，配置给BBP；BBP中，与发射功率相加补偿后，查APC表。此值需在对单板进行测试后确定。 */
        unsigned long  reserved           : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_PC_DELTA_POW_FREQ_UNION;
#define WBBP_PC_DELTA_POW_FREQ_dsp_delta_pow_freq_START  (0)
#define WBBP_PC_DELTA_POW_FREQ_dsp_delta_pow_freq_END    (9)


/*****************************************************************************
 结构名    : WBBP_APT_MODE_SEL_UNION
 结构说明  : APT_MODE_SEL 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_mode_sel_reg;
    struct
    {
        unsigned long  dsp_pa_pwm_sel      : 1;  /* bit[0]   : 0，选择PDM控制输出；1，选择PWM控制输出。 */
        unsigned long  reserved_0          : 3;  /* bit[1-3] : 保留 */
        unsigned long  dsp_apt_ctrl_mode   : 1;  /* bit[4]   : 为了提供满足不同PA的APT控制要求，PA电压控制模式可进行选择。0，PDM配置；1，MIPI口配置。 */
        unsigned long  reserved_1          : 3;  /* bit[5-7] : 保留 */
        unsigned long  dsp_apt_renew_pulse : 1;  /* bit[8]   : apt强制更新脉冲，仅用于强配APT控制字。每次写1产生一个单时钟脉冲，自清零 */
        unsigned long  reserved_2          : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_APT_MODE_SEL_UNION;
#define WBBP_APT_MODE_SEL_dsp_pa_pwm_sel_START       (0)
#define WBBP_APT_MODE_SEL_dsp_pa_pwm_sel_END         (0)
#define WBBP_APT_MODE_SEL_dsp_apt_ctrl_mode_START    (4)
#define WBBP_APT_MODE_SEL_dsp_apt_ctrl_mode_END      (4)
#define WBBP_APT_MODE_SEL_dsp_apt_renew_pulse_START  (8)
#define WBBP_APT_MODE_SEL_dsp_apt_renew_pulse_END    (8)


/*****************************************************************************
 结构名    : WBBP_DSP_APT_ACTIVE_EN_UNION
 结构说明  : DSP_APT_ACTIVE_EN 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_apt_active_en_reg;
    struct
    {
        unsigned long  reserved_0        : 16; /* bit[0-15] : 保留 */
        unsigned long  dsp_apt_active_en : 1;  /* bit[16]   : PA APT功能生效开关，高电平有效，该开关有效时，PA APT功能可以进行正常工作，否则PDM脉冲一直为0。 */
        unsigned long  reserved_1        : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_DSP_APT_ACTIVE_EN_UNION;
#define WBBP_DSP_APT_ACTIVE_EN_dsp_apt_active_en_START  (16)
#define WBBP_DSP_APT_ACTIVE_EN_dsp_apt_active_en_END    (16)


/*****************************************************************************
 结构名    : WBBP_DSP_APT_CONFIG_UNION
 结构说明  : DSP_APT_CONFIG 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_apt_config_reg;
    struct
    {
        unsigned long  dsp_apt_config_value : 7;  /* bit[0-6] : PA供电电压强制配置值，默认值为0。无符号数。 */
        unsigned long  reserved_0           : 1;  /* bit[7]   : 保留 */
        unsigned long  dsp_apt_config_en    : 1;  /* bit[8]   : PA供电电压强制配置使能，电平信号，该功能有效时，PA电压控制值由dsp_apt_config_value决定。 */
        unsigned long  reserved_1           : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_DSP_APT_CONFIG_UNION;
#define WBBP_DSP_APT_CONFIG_dsp_apt_config_value_START  (0)
#define WBBP_DSP_APT_CONFIG_dsp_apt_config_value_END    (6)
#define WBBP_DSP_APT_CONFIG_dsp_apt_config_en_START     (8)
#define WBBP_DSP_APT_CONFIG_dsp_apt_config_en_END       (8)


/*****************************************************************************
 结构名    : WBBP_PACOMP_OFFSET_HM_UNION
 结构说明  : PACOMP_OFFSET_HM 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pacomp_offset_hm_reg;
    struct
    {
        unsigned long  dsp_pacomp_offset_m : 11; /* bit[0-10] : PA为中档位时，用于查PA非线性补偿表的offset值，单位0.1dBm，有符号数。 */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_pacomp_offset_h : 11; /* bit[16-26]: PA为高档位时，用于查PA非线性补偿表的offset值，单位0.1dBm，有符号数。 */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_PACOMP_OFFSET_HM_UNION;
#define WBBP_PACOMP_OFFSET_HM_dsp_pacomp_offset_m_START  (0)
#define WBBP_PACOMP_OFFSET_HM_dsp_pacomp_offset_m_END    (10)
#define WBBP_PACOMP_OFFSET_HM_dsp_pacomp_offset_h_START  (16)
#define WBBP_PACOMP_OFFSET_HM_dsp_pacomp_offset_h_END    (26)


/*****************************************************************************
 结构名    : WBBP_PACOMP_OFFSET_L_UNION
 结构说明  : PACOMP_OFFSET_L 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pacomp_offset_l_reg;
    struct
    {
        unsigned long  dsp_pacomp_offset_l : 11; /* bit[0-10] : PA为低档位时，用于查PA非线性补偿表的offset值，单位0.1dBm，有符号数。 */
        unsigned long  reserved            : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_PACOMP_OFFSET_L_UNION;
#define WBBP_PACOMP_OFFSET_L_dsp_pacomp_offset_l_START  (0)
#define WBBP_PACOMP_OFFSET_L_dsp_pacomp_offset_l_END    (10)


/*****************************************************************************
 结构名    : WBBP_PA_H_COMP_UNION
 结构说明  : PA_H_COMP 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_h_comp_reg;
    struct
    {
        unsigned long  dsp_nv_pa_h_comp : 11; /* bit[0-10] : PA工作在高增益模式时的增益补偿值，有符号补码数，单位0.1dB。
                                                             DSP根据当前的频段信息和温度信息，选择偏差值，配置给BBP；BBP将此值与发射功率相加后，查APC表。此值需在不同的工作频段下进行单板测试后确定。 */
        unsigned long  reserved         : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_PA_H_COMP_UNION;
#define WBBP_PA_H_COMP_dsp_nv_pa_h_comp_START  (0)
#define WBBP_PA_H_COMP_dsp_nv_pa_h_comp_END    (10)


/*****************************************************************************
 结构名    : WBBP_PA_M_COMP_UNION
 结构说明  : PA_M_COMP 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_m_comp_reg;
    struct
    {
        unsigned long  dsp_nv_pa_m_comp : 11; /* bit[0-10] : PA工作在中增益模式时的增益补偿值，有符号补码数，单位0.1dB。
                                                             DSP根据当前的频段信息和温度信息，选择偏差值，配置给BBP；BBP将此值与发射功率相加后，查APC表。此值需在不同的工作频段下进行单板测试后确定。 */
        unsigned long  reserved         : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_PA_M_COMP_UNION;
#define WBBP_PA_M_COMP_dsp_nv_pa_m_comp_START  (0)
#define WBBP_PA_M_COMP_dsp_nv_pa_m_comp_END    (10)


/*****************************************************************************
 结构名    : WBBP_PA_L_COMP_UNION
 结构说明  : PA_L_COMP 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_l_comp_reg;
    struct
    {
        unsigned long  dsp_nv_pa_l_comp : 11; /* bit[0-10] : PA工作在低增益模式时的增益补偿值，有符号补码数，单位0.1dB。
                                                             DSP根据当前的频段信息和温度信息，选择偏差值，配置给BBP；BBP将此值与发射功率相加后，查APC表。此值需在不同的工作频段下进行单板测试后确定。 */
        unsigned long  reserved         : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_PA_L_COMP_UNION;
#define WBBP_PA_L_COMP_dsp_nv_pa_l_comp_START  (0)
#define WBBP_PA_L_COMP_dsp_nv_pa_l_comp_END    (10)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT1A_UNION
 结构说明  : DSP_POW_COMP_SLOT1A 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot1a_reg;
    struct
    {
        unsigned long  dsp_nv_pa_h2m_comp1 : 11; /* bit[0-10] : PA从高增益到中增益的功率补偿，二进制补码。 */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_m2h_comp1 : 11; /* bit[16-26]: PA从中增益到高增益的功率补偿，二进制补码。 */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT1A_UNION;
#define WBBP_DSP_POW_COMP_SLOT1A_dsp_nv_pa_h2m_comp1_START  (0)
#define WBBP_DSP_POW_COMP_SLOT1A_dsp_nv_pa_h2m_comp1_END    (10)
#define WBBP_DSP_POW_COMP_SLOT1A_dsp_nv_pa_m2h_comp1_START  (16)
#define WBBP_DSP_POW_COMP_SLOT1A_dsp_nv_pa_m2h_comp1_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT1B_UNION
 结构说明  : DSP_POW_COMP_SLOT1B 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot1b_reg;
    struct
    {
        unsigned long  dsp_nv_pa_m2l_comp1 : 11; /* bit[0-10] : PA从中增益到低增益的功率补偿，二进制补码。 */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_l2m_comp1 : 11; /* bit[16-26]: PA从低增益到中增益的功率补偿，二进制补码。 */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT1B_UNION;
#define WBBP_DSP_POW_COMP_SLOT1B_dsp_nv_pa_m2l_comp1_START  (0)
#define WBBP_DSP_POW_COMP_SLOT1B_dsp_nv_pa_m2l_comp1_END    (10)
#define WBBP_DSP_POW_COMP_SLOT1B_dsp_nv_pa_l2m_comp1_START  (16)
#define WBBP_DSP_POW_COMP_SLOT1B_dsp_nv_pa_l2m_comp1_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT2A_UNION
 结构说明  : DSP_POW_COMP_SLOT2A 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot2a_reg;
    struct
    {
        unsigned long  dsp_nv_pa_h2m_comp2 : 11; /* bit[0-10] : PA高切中后第二时隙功率补偿  */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_m2h_comp2 : 11; /* bit[16-26]: PA中切高后第二时隙功率补偿  */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT2A_UNION;
#define WBBP_DSP_POW_COMP_SLOT2A_dsp_nv_pa_h2m_comp2_START  (0)
#define WBBP_DSP_POW_COMP_SLOT2A_dsp_nv_pa_h2m_comp2_END    (10)
#define WBBP_DSP_POW_COMP_SLOT2A_dsp_nv_pa_m2h_comp2_START  (16)
#define WBBP_DSP_POW_COMP_SLOT2A_dsp_nv_pa_m2h_comp2_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT2B_UNION
 结构说明  : DSP_POW_COMP_SLOT2B 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot2b_reg;
    struct
    {
        unsigned long  dsp_nv_pa_m2l_comp2 : 11; /* bit[0-10] : PA中切低后第二时隙功率补偿  */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_l2m_comp2 : 11; /* bit[16-26]: PA低切中后第二时隙功率补偿  */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT2B_UNION;
#define WBBP_DSP_POW_COMP_SLOT2B_dsp_nv_pa_m2l_comp2_START  (0)
#define WBBP_DSP_POW_COMP_SLOT2B_dsp_nv_pa_m2l_comp2_END    (10)
#define WBBP_DSP_POW_COMP_SLOT2B_dsp_nv_pa_l2m_comp2_START  (16)
#define WBBP_DSP_POW_COMP_SLOT2B_dsp_nv_pa_l2m_comp2_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT3A_UNION
 结构说明  : DSP_POW_COMP_SLOT3A 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot3a_reg;
    struct
    {
        unsigned long  dsp_nv_pa_h2m_comp3 : 11; /* bit[0-10] : PA高切中后第三时隙功率补偿  */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_m2h_comp3 : 11; /* bit[16-26]: PA中切高后第三时隙功率补偿  */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT3A_UNION;
#define WBBP_DSP_POW_COMP_SLOT3A_dsp_nv_pa_h2m_comp3_START  (0)
#define WBBP_DSP_POW_COMP_SLOT3A_dsp_nv_pa_h2m_comp3_END    (10)
#define WBBP_DSP_POW_COMP_SLOT3A_dsp_nv_pa_m2h_comp3_START  (16)
#define WBBP_DSP_POW_COMP_SLOT3A_dsp_nv_pa_m2h_comp3_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT3B_UNION
 结构说明  : DSP_POW_COMP_SLOT3B 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot3b_reg;
    struct
    {
        unsigned long  dsp_nv_pa_m2l_comp3 : 11; /* bit[0-10] : PA中切低后第三时隙功率补偿  */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_l2m_comp3 : 11; /* bit[16-26]: PA低切中后第三时隙功率补偿  */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT3B_UNION;
#define WBBP_DSP_POW_COMP_SLOT3B_dsp_nv_pa_m2l_comp3_START  (0)
#define WBBP_DSP_POW_COMP_SLOT3B_dsp_nv_pa_m2l_comp3_END    (10)
#define WBBP_DSP_POW_COMP_SLOT3B_dsp_nv_pa_l2m_comp3_START  (16)
#define WBBP_DSP_POW_COMP_SLOT3B_dsp_nv_pa_l2m_comp3_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT4A_UNION
 结构说明  : DSP_POW_COMP_SLOT4A 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot4a_reg;
    struct
    {
        unsigned long  dsp_nv_pa_h2m_comp4 : 11; /* bit[0-10] : PA高切中后第四时隙功率补偿  */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_m2h_comp4 : 11; /* bit[16-26]: PA中切高后第四时隙功率补偿  */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT4A_UNION;
#define WBBP_DSP_POW_COMP_SLOT4A_dsp_nv_pa_h2m_comp4_START  (0)
#define WBBP_DSP_POW_COMP_SLOT4A_dsp_nv_pa_h2m_comp4_END    (10)
#define WBBP_DSP_POW_COMP_SLOT4A_dsp_nv_pa_m2h_comp4_START  (16)
#define WBBP_DSP_POW_COMP_SLOT4A_dsp_nv_pa_m2h_comp4_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_COMP_SLOT4B_UNION
 结构说明  : DSP_POW_COMP_SLOT4B 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_comp_slot4b_reg;
    struct
    {
        unsigned long  dsp_nv_pa_m2l_comp4 : 11; /* bit[0-10] : PA中切低后第四时隙功率补偿  */
        unsigned long  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_nv_pa_l2m_comp4 : 11; /* bit[16-26]: PA低切中后第四时隙功率补偿  */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DSP_POW_COMP_SLOT4B_UNION;
#define WBBP_DSP_POW_COMP_SLOT4B_dsp_nv_pa_m2l_comp4_START  (0)
#define WBBP_DSP_POW_COMP_SLOT4B_dsp_nv_pa_m2l_comp4_END    (10)
#define WBBP_DSP_POW_COMP_SLOT4B_dsp_nv_pa_l2m_comp4_START  (16)
#define WBBP_DSP_POW_COMP_SLOT4B_dsp_nv_pa_l2m_comp4_END    (26)


/*****************************************************************************
 结构名    : WBBP_DSP_W_TX_APC_ATTEN_UNION
 结构说明  : DSP_W_TX_APC_ATTEN 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_w_tx_apc_atten_reg;
    struct
    {
        unsigned long  dsp_w_tx_apc_rf_atten  : 16; /* bit[0-15] : DSP强制射频增益衰减控制字。无符号数。 */
        unsigned long  dsp_w_tx_apc_dbb_atten : 7;  /* bit[16-22]: DSP强制DBB衰减补偿增益。取值范围[0,80]，超过80按80处理。精度0.1dB。
                                                                   0表示数字功率增加1dB，1表示增加0.9dB，以此类推，取值每增加1，功率增加值减少0.1dB，10表示增加0dB，11表示减少0.1dB，……，80表示减少7dB。 */
        unsigned long  reserved               : 8;  /* bit[23-30]: 保留 */
        unsigned long  dsp_w_tx_apc_atten_en  : 1;  /* bit[31]   : DSP强制衰减使能信号。 */
    } reg;
} WBBP_DSP_W_TX_APC_ATTEN_UNION;
#define WBBP_DSP_W_TX_APC_ATTEN_dsp_w_tx_apc_rf_atten_START   (0)
#define WBBP_DSP_W_TX_APC_ATTEN_dsp_w_tx_apc_rf_atten_END     (15)
#define WBBP_DSP_W_TX_APC_ATTEN_dsp_w_tx_apc_dbb_atten_START  (16)
#define WBBP_DSP_W_TX_APC_ATTEN_dsp_w_tx_apc_dbb_atten_END    (22)
#define WBBP_DSP_W_TX_APC_ATTEN_dsp_w_tx_apc_atten_en_START   (31)
#define WBBP_DSP_W_TX_APC_ATTEN_dsp_w_tx_apc_atten_en_END     (31)


/*****************************************************************************
 结构名    : WBBP_W_TX_RF_ATTEN_ADDR_UNION
 结构说明  : W_TX_RF_ATTEN_ADDR 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_tx_rf_atten_addr_reg;
    struct
    {
        unsigned long  dsp_w_tx_ssi_addr : 8;  /* bit[0-7] : RFCMOS方案射频增益控制字对应SSI地址。 */
        unsigned long  reserved          : 24; /* bit[8-31]: 保留 */
    } reg;
} WBBP_W_TX_RF_ATTEN_ADDR_UNION;
#define WBBP_W_TX_RF_ATTEN_ADDR_dsp_w_tx_ssi_addr_START  (0)
#define WBBP_W_TX_RF_ATTEN_ADDR_dsp_w_tx_ssi_addr_END    (7)


/*****************************************************************************
 结构名    : WBBP_RF_DC_OFFSET_EN_UNION
 结构说明  : RF_DC_OFFSET_EN 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_dc_offset_en_reg;
    struct
    {
        unsigned long  reserved_0         : 4;  /* bit[0-3] : 保留 */
        unsigned long  dsp_temp_update_en : 1;  /* bit[4]   : 温度补偿更新指示,当软件刷新PA温补,控制字温补,PD温补寄存器时,先将本比特置1,刷新完成后将本比特置0. */
        unsigned long  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} WBBP_RF_DC_OFFSET_EN_UNION;
#define WBBP_RF_DC_OFFSET_EN_dsp_temp_update_en_START  (4)
#define WBBP_RF_DC_OFFSET_EN_dsp_temp_update_en_END    (4)


/*****************************************************************************
 结构名    : WBBP_W_RF_REPORT_UNION
 结构说明  : W_RF_REPORT 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_rf_report_reg;
    struct
    {
        unsigned long  rf_ctrl_word  : 16; /* bit[0-15] : RF控制字上报，无符号数 */
        unsigned long  dbb_atten_pow : 7;  /* bit[16-22]: RFCMOS数字回退功率上报，单位0.1dB.取值范围[0,80],对应回退功率范围[增加1dB,减少7dB] */
        unsigned long  w_pa_mode     : 2;  /* bit[23-24]: PA控制字上报，无符号数 */
        unsigned long  reserved      : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_W_RF_REPORT_UNION;
#define WBBP_W_RF_REPORT_rf_ctrl_word_START   (0)
#define WBBP_W_RF_REPORT_rf_ctrl_word_END     (15)
#define WBBP_W_RF_REPORT_dbb_atten_pow_START  (16)
#define WBBP_W_RF_REPORT_dbb_atten_pow_END    (22)
#define WBBP_W_RF_REPORT_w_pa_mode_START      (23)
#define WBBP_W_RF_REPORT_w_pa_mode_END        (24)


/*****************************************************************************
 结构名    : WBBP_DSP_PA_VBIAS_CONFIG_UNION
 结构说明  : DSP_PA_VBIAS_CONFIG 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pa_vbias_config_reg;
    struct
    {
        unsigned long  dsp_wpavbias_config_value  : 8;  /* bit[0-7]  : PA VBIAS控制字强配值 */
        unsigned long  dsp_wpavbias_config_en     : 1;  /* bit[8]    : PA VBIAS控制字强配使能 */
        unsigned long  reserved_0                 : 7;  /* bit[9-15] : 保留 */
        unsigned long  dsp_temp_comp_config_value : 7;  /* bit[16-22]: ATTEN控制字温度补偿功率强配值,有符号数,单位0.1dB */
        unsigned long  reserved_1                 : 1;  /* bit[23]   : 保留 */
        unsigned long  dsp_temp_comp_config_en    : 1;  /* bit[24]   : ATTEN控制字温度补偿功率强配使能. */
        unsigned long  reserved_2                 : 7;  /* bit[25-31]: 保留 */
    } reg;
} WBBP_DSP_PA_VBIAS_CONFIG_UNION;
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_wpavbias_config_value_START   (0)
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_wpavbias_config_value_END     (7)
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_wpavbias_config_en_START      (8)
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_wpavbias_config_en_END        (8)
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_temp_comp_config_value_START  (16)
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_temp_comp_config_value_END    (22)
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_temp_comp_config_en_START     (24)
#define WBBP_DSP_PA_VBIAS_CONFIG_dsp_temp_comp_config_en_END       (24)


/*****************************************************************************
 结构名    : WBBP_W_PA_REPORT_UNION
 结构说明  : W_PA_REPORT 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_pa_report_reg;
    struct
    {
        unsigned long  wpavbias_word   : 8;  /* bit[0-7]  : PA VBIAS控制字上报,无符号数. */
        unsigned long  temp_comp_power : 7;  /* bit[8-14] : RF控制字温度补偿上报,有符号数,单位0.1dB */
        unsigned long  reserved        : 17; /* bit[15-31]: 保留 */
    } reg;
} WBBP_W_PA_REPORT_UNION;
#define WBBP_W_PA_REPORT_wpavbias_word_START    (0)
#define WBBP_W_PA_REPORT_wpavbias_word_END      (7)
#define WBBP_W_PA_REPORT_temp_comp_power_START  (8)
#define WBBP_W_PA_REPORT_temp_comp_power_END    (14)


/*****************************************************************************
 结构名    : WBBP_TEMP_COMP0_3_UNION
 结构说明  : TEMP_COMP0_3 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      temp_comp0_3_reg;
    struct
    {
        unsigned long  temp_comp_0power : 7;  /* bit[0-6]  : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_0       : 1;  /* bit[7]    : 保留 */
        unsigned long  temp_comp_1power : 7;  /* bit[8-14] : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_1       : 1;  /* bit[15]   : 保留 */
        unsigned long  temp_comp_2power : 7;  /* bit[16-22]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_2       : 1;  /* bit[23]   : 保留 */
        unsigned long  temp_comp_3power : 7;  /* bit[24-30]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_3       : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_TEMP_COMP0_3_UNION;
#define WBBP_TEMP_COMP0_3_temp_comp_0power_START  (0)
#define WBBP_TEMP_COMP0_3_temp_comp_0power_END    (6)
#define WBBP_TEMP_COMP0_3_temp_comp_1power_START  (8)
#define WBBP_TEMP_COMP0_3_temp_comp_1power_END    (14)
#define WBBP_TEMP_COMP0_3_temp_comp_2power_START  (16)
#define WBBP_TEMP_COMP0_3_temp_comp_2power_END    (22)
#define WBBP_TEMP_COMP0_3_temp_comp_3power_START  (24)
#define WBBP_TEMP_COMP0_3_temp_comp_3power_END    (30)


/*****************************************************************************
 结构名    : WBBP_TEMP_COMP4_7_UNION
 结构说明  : TEMP_COMP4_7 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      temp_comp4_7_reg;
    struct
    {
        unsigned long  temp_comp_4power : 7;  /* bit[0-6]  : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_0       : 1;  /* bit[7]    : 保留 */
        unsigned long  temp_comp_5power : 7;  /* bit[8-14] : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_1       : 1;  /* bit[15]   : 保留 */
        unsigned long  temp_comp_6power : 7;  /* bit[16-22]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_2       : 1;  /* bit[23]   : 保留 */
        unsigned long  temp_comp_7power : 7;  /* bit[24-30]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_3       : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_TEMP_COMP4_7_UNION;
#define WBBP_TEMP_COMP4_7_temp_comp_4power_START  (0)
#define WBBP_TEMP_COMP4_7_temp_comp_4power_END    (6)
#define WBBP_TEMP_COMP4_7_temp_comp_5power_START  (8)
#define WBBP_TEMP_COMP4_7_temp_comp_5power_END    (14)
#define WBBP_TEMP_COMP4_7_temp_comp_6power_START  (16)
#define WBBP_TEMP_COMP4_7_temp_comp_6power_END    (22)
#define WBBP_TEMP_COMP4_7_temp_comp_7power_START  (24)
#define WBBP_TEMP_COMP4_7_temp_comp_7power_END    (30)


/*****************************************************************************
 结构名    : WBBP_TEMP_COMP8_11_UNION
 结构说明  : TEMP_COMP8_11 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      temp_comp8_11_reg;
    struct
    {
        unsigned long  temp_comp_8power  : 7;  /* bit[0-6]  : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_0        : 1;  /* bit[7]    : 保留 */
        unsigned long  temp_comp_9power  : 7;  /* bit[8-14] : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_1        : 1;  /* bit[15]   : 保留 */
        unsigned long  temp_comp_10power : 7;  /* bit[16-22]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_2        : 1;  /* bit[23]   : 保留 */
        unsigned long  temp_comp_11power : 7;  /* bit[24-30]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_3        : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_TEMP_COMP8_11_UNION;
#define WBBP_TEMP_COMP8_11_temp_comp_8power_START   (0)
#define WBBP_TEMP_COMP8_11_temp_comp_8power_END     (6)
#define WBBP_TEMP_COMP8_11_temp_comp_9power_START   (8)
#define WBBP_TEMP_COMP8_11_temp_comp_9power_END     (14)
#define WBBP_TEMP_COMP8_11_temp_comp_10power_START  (16)
#define WBBP_TEMP_COMP8_11_temp_comp_10power_END    (22)
#define WBBP_TEMP_COMP8_11_temp_comp_11power_START  (24)
#define WBBP_TEMP_COMP8_11_temp_comp_11power_END    (30)


/*****************************************************************************
 结构名    : WBBP_TEMP_COMP12_15_UNION
 结构说明  : TEMP_COMP12_15 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      temp_comp12_15_reg;
    struct
    {
        unsigned long  temp_comp_12power : 7;  /* bit[0-6]  : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_0        : 1;  /* bit[7]    : 保留 */
        unsigned long  temp_comp_13power : 7;  /* bit[8-14] : RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_1        : 1;  /* bit[15]   : 保留 */
        unsigned long  temp_comp_14power : 7;  /* bit[16-22]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_2        : 1;  /* bit[23]   : 保留 */
        unsigned long  temp_comp_15power : 7;  /* bit[24-30]: RF控制字温度补偿功率,有符号数,0.1dB */
        unsigned long  reserved_3        : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_TEMP_COMP12_15_UNION;
#define WBBP_TEMP_COMP12_15_temp_comp_12power_START  (0)
#define WBBP_TEMP_COMP12_15_temp_comp_12power_END    (6)
#define WBBP_TEMP_COMP12_15_temp_comp_13power_START  (8)
#define WBBP_TEMP_COMP12_15_temp_comp_13power_END    (14)
#define WBBP_TEMP_COMP12_15_temp_comp_14power_START  (16)
#define WBBP_TEMP_COMP12_15_temp_comp_14power_END    (22)
#define WBBP_TEMP_COMP12_15_temp_comp_15power_START  (24)
#define WBBP_TEMP_COMP12_15_temp_comp_15power_END    (30)


/*****************************************************************************
 结构名    : WBBP_DSP_DMPR_CONFIG_UNION
 结构说明  : DSP_DMPR_CONFIG 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_dmpr_config_reg;
    struct
    {
        unsigned long  dsp_dmpr_config_value : 6;  /* bit[0-5] : 软件强配dmpr功率值,有符号数,单位 0.1dB. */
        unsigned long  reserved_0            : 2;  /* bit[6-7] : 保留 */
        unsigned long  dsp_dmpr_config_en    : 1;  /* bit[8]   : 软件强配dmpr功率使能 */
        unsigned long  reserved_1            : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_DSP_DMPR_CONFIG_UNION;
#define WBBP_DSP_DMPR_CONFIG_dsp_dmpr_config_value_START  (0)
#define WBBP_DSP_DMPR_CONFIG_dsp_dmpr_config_value_END    (5)
#define WBBP_DSP_DMPR_CONFIG_dsp_dmpr_config_en_START     (8)
#define WBBP_DSP_DMPR_CONFIG_dsp_dmpr_config_en_END       (8)


/*****************************************************************************
 结构名    : WBBP_TX_SHDN_CTRL_UNION
 结构说明  : TX_SHDN_CTRL 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_shdn_ctrl_reg;
    struct
    {
        unsigned long  tx_shdn_ctrl : 2;  /* bit[0-1] : 上行通路开关控制。2'b10，表示DSP强制上行通路关闭；2'b11，表示DSP强制上行通路打开；其他，表示上行通路不受DSP控制，而由上行调制模块控制。
                                                        此寄存器同时控制上行PA、RF等的开关。也即如果配置为2'b10，表示上行RF、PA等同时关闭。 */
        unsigned long  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_TX_SHDN_CTRL_UNION;
#define WBBP_TX_SHDN_CTRL_tx_shdn_ctrl_START  (0)
#define WBBP_TX_SHDN_CTRL_tx_shdn_ctrl_END    (1)


/*****************************************************************************
 结构名    : WBBP_TX_RF_SHDN_CTRL_UNION
 结构说明  : TX_RF_SHDN_CTRL 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_rf_shdn_ctrl_reg;
    struct
    {
        unsigned long  rf_tx_shdn_ctrl : 2;  /* bit[0-1] : 上行RF开关控制。2'b10，表示DSP强制上行RF关闭；2'b11，表示DSP强制上行RF打开；其他，表示上行RF不受DSP控制，而由上行调制模块控制。
                                                           此寄存器仅控制上行RF的开关。同时，仅在TX_SHDN_CTRL被配置为非DSP强制控制的情况下上行RF才受此寄存器的控制。 */
        unsigned long  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_TX_RF_SHDN_CTRL_UNION;
#define WBBP_TX_RF_SHDN_CTRL_rf_tx_shdn_ctrl_START  (0)
#define WBBP_TX_RF_SHDN_CTRL_rf_tx_shdn_ctrl_END    (1)


/*****************************************************************************
 结构名    : WBBP_TX_PA_SHDN_CTRL_UNION
 结构说明  : TX_PA_SHDN_CTRL 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_pa_shdn_ctrl_reg;
    struct
    {
        unsigned long  pa_shdn_ctrl : 2;  /* bit[0-1] : 上行PA开关控制。2'b10，表示DSP强制上行PA关闭；2'b11，表示DSP强制上行PA打开；其他，表示上行PA不受DSP控制，而由上行调制模块控制。
                                                        此寄存器仅控制上行PA的开关。同时，仅在TX_SHDN_CTRL被配置为非DSP强制控制的情况下上行PA才受此寄存器的控制。 */
        unsigned long  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_TX_PA_SHDN_CTRL_UNION;
#define WBBP_TX_PA_SHDN_CTRL_pa_shdn_ctrl_START  (0)
#define WBBP_TX_PA_SHDN_CTRL_pa_shdn_ctrl_END    (1)


/*****************************************************************************
 结构名    : WBBP_ABB_SHDN_CTRL_UNION
 结构说明  : ABB_SHDN_CTRL 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_shdn_ctrl_reg;
    struct
    {
        unsigned long  abb_tx_shdn_ctrl : 2;  /* bit[0-1] : 上行ABB开关控制。2'b10，表示DSP强制上行ABB关闭；2'b11，表示DSP强制上行ABB打开；其他，表示上行ABB不受DSP控制，而由上行调制模块控制。
                                                            此寄存器仅控制上行ABB的开关。同时，仅在TX_SHDN_CTRL被配置为非DSP强制控制的情况下上行ABB才受此寄存器的控制。 */
        unsigned long  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_ABB_SHDN_CTRL_UNION;
#define WBBP_ABB_SHDN_CTRL_abb_tx_shdn_ctrl_START  (0)
#define WBBP_ABB_SHDN_CTRL_abb_tx_shdn_ctrl_END    (1)


/*****************************************************************************
 结构名    : WBBP_APT_ET_TIMING_UNION
 结构说明  : APT_ET_TIMING 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_et_timing_reg;
    struct
    {
        unsigned long  dsp_apt_et_active_time : 10; /* bit[0-9]  : D态下，APT_ET使能信号生效提前时隙头时间量，单位chip。 */
        unsigned long  reserved_0             : 2;  /* bit[10-11]: 保留 */
        unsigned long  et_shdn_ctrl           : 2;  /* bit[12-13]: 2'd10:ET强关，2'd11:ET强开，其它:ET由其它控制。 */
        unsigned long  reserved_1             : 2;  /* bit[14-15]: 保留 */
        unsigned long  dsp_tx_pow_time        : 10; /* bit[16-25]: APT_ET切换点提前时隙头时间量，单位chip。 */
        unsigned long  reserved_2             : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_APT_ET_TIMING_UNION;
#define WBBP_APT_ET_TIMING_dsp_apt_et_active_time_START  (0)
#define WBBP_APT_ET_TIMING_dsp_apt_et_active_time_END    (9)
#define WBBP_APT_ET_TIMING_et_shdn_ctrl_START            (12)
#define WBBP_APT_ET_TIMING_et_shdn_ctrl_END              (13)
#define WBBP_APT_ET_TIMING_dsp_tx_pow_time_START         (16)
#define WBBP_APT_ET_TIMING_dsp_tx_pow_time_END           (25)


/*****************************************************************************
 结构名    : WBBP_TX_RF_TIME_CTRL_UNION
 结构说明  : TX_RF_TIME_CTRL 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_rf_time_ctrl_reg;
    struct
    {
        unsigned long  tx_rf_open_time : 12; /* bit[0-11] : 提前打开上行RF的chip数。取值范围0~1023。典型值800us等于3072chip。 */
        unsigned long  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned long  tx_rf_idle_time : 12; /* bit[16-27]: 提前打开上行RF IDLE状态的chip数。取值范围0~1023。典型值100us等于384chip。 */
        unsigned long  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_TX_RF_TIME_CTRL_UNION;
#define WBBP_TX_RF_TIME_CTRL_tx_rf_open_time_START  (0)
#define WBBP_TX_RF_TIME_CTRL_tx_rf_open_time_END    (11)
#define WBBP_TX_RF_TIME_CTRL_tx_rf_idle_time_START  (16)
#define WBBP_TX_RF_TIME_CTRL_tx_rf_idle_time_END    (27)


/*****************************************************************************
 结构名    : WBBP_TX_RF_CLOSE_TIME_CTRL_UNION
 结构说明  : TX_RF_CLOSE_TIME_CTRL 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_rf_close_time_ctrl_reg;
    struct
    {
        unsigned long  tx_rf_close_time      : 10; /* bit[0-9]  : 延后关闭上行RF的chip数。 */
        unsigned long  reserved_0            : 6;  /* bit[10-15]: 保留 */
        unsigned long  tx_rf_idle_close_time : 10; /* bit[16-25]: 延后关闭上行RF IDLE状态的chip数。 */
        unsigned long  reserved_1            : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_TX_RF_CLOSE_TIME_CTRL_UNION;
#define WBBP_TX_RF_CLOSE_TIME_CTRL_tx_rf_close_time_START       (0)
#define WBBP_TX_RF_CLOSE_TIME_CTRL_tx_rf_close_time_END         (9)
#define WBBP_TX_RF_CLOSE_TIME_CTRL_tx_rf_idle_close_time_START  (16)
#define WBBP_TX_RF_CLOSE_TIME_CTRL_tx_rf_idle_close_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_TX_PA_TIME_CTRL_UNION
 结构说明  : TX_PA_TIME_CTRL 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_pa_time_ctrl_reg;
    struct
    {
        unsigned long  tx_pa_open_time  : 11; /* bit[0-10] : 提前打开上行PA的chip数。取值范围0~1023。典型值40us等于154chip。 */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: 保留 */
        unsigned long  tx_pa_close_time : 10; /* bit[16-25]: 延后关闭上行PA的chip数。 */
        unsigned long  reserved_1       : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_TX_PA_TIME_CTRL_UNION;
#define WBBP_TX_PA_TIME_CTRL_tx_pa_open_time_START   (0)
#define WBBP_TX_PA_TIME_CTRL_tx_pa_open_time_END     (10)
#define WBBP_TX_PA_TIME_CTRL_tx_pa_close_time_START  (16)
#define WBBP_TX_PA_TIME_CTRL_tx_pa_close_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_TX_PDM_TIME_CTRL_UNION
 结构说明  : TX_PDM_TIME_CTRL 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_pdm_time_ctrl_reg;
    struct
    {
        unsigned long  tx_pdm_open_time  : 11; /* bit[0-10] : 提前打开上行RF增益的chip数。取值范围0~1023。 */
        unsigned long  reserved_0        : 5;  /* bit[11-15]: 保留 */
        unsigned long  tx_pdm_close_time : 10; /* bit[16-25]: 延后关闭上行RF增益的chip数。 */
        unsigned long  reserved_1        : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_TX_PDM_TIME_CTRL_UNION;
#define WBBP_TX_PDM_TIME_CTRL_tx_pdm_open_time_START   (0)
#define WBBP_TX_PDM_TIME_CTRL_tx_pdm_open_time_END     (10)
#define WBBP_TX_PDM_TIME_CTRL_tx_pdm_close_time_START  (16)
#define WBBP_TX_PDM_TIME_CTRL_tx_pdm_close_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_TX_ABB_TIME_CTRL_UNION
 结构说明  : TX_ABB_TIME_CTRL 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_abb_time_ctrl_reg;
    struct
    {
        unsigned long  tx_abb_open_time  : 12; /* bit[0-11] : 提前打开上行ABB的chip数。取值范围0~1023。 */
        unsigned long  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned long  tx_abb_close_time : 10; /* bit[16-25]: 延后关闭上行ABB的chip数。 */
        unsigned long  reserved_1        : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_TX_ABB_TIME_CTRL_UNION;
#define WBBP_TX_ABB_TIME_CTRL_tx_abb_open_time_START   (0)
#define WBBP_TX_ABB_TIME_CTRL_tx_abb_open_time_END     (11)
#define WBBP_TX_ABB_TIME_CTRL_tx_abb_close_time_START  (16)
#define WBBP_TX_ABB_TIME_CTRL_tx_abb_close_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_ULPOWER_ACTIVE_TIME_UNION
 结构说明  : ULPOWER_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulpower_active_time_reg;
    struct
    {
        unsigned long  ulpower_active_time : 10; /* bit[0-9]  : 上行发射功率生效时间，单位chip。表示上行发射功率需提前上行时隙头多久时间送至射频器件。由于射频器件有延时，为使上行发射功率在上行时隙头处生效，需提前将上行发射功率计算结果送至射频器件。 */
        unsigned long  reserved            : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_ULPOWER_ACTIVE_TIME_UNION;
#define WBBP_ULPOWER_ACTIVE_TIME_ulpower_active_time_START  (0)
#define WBBP_ULPOWER_ACTIVE_TIME_ulpower_active_time_END    (9)


/*****************************************************************************
 结构名    : WBBP_W_TX_PHASE_COMP_TIME_UNION
 结构说明  : W_TX_PHASE_COMP_TIME 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_tx_phase_comp_time_reg;
    struct
    {
        unsigned long  dsp_w_tx_phase_comp_time : 10; /* bit[0-9]  : 相位补偿生效时刻相对于时隙边界提前量，单位1/4chip。 */
        unsigned long  reserved                 : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_W_TX_PHASE_COMP_TIME_UNION;
#define WBBP_W_TX_PHASE_COMP_TIME_dsp_w_tx_phase_comp_time_START  (0)
#define WBBP_W_TX_PHASE_COMP_TIME_dsp_w_tx_phase_comp_time_END    (9)


/*****************************************************************************
 结构名    : WBBP_DCOFFSET_ACTIVE_TIME_UNION
 结构说明  : DCOFFSET_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dcoffset_active_time_reg;
    struct
    {
        unsigned long  dsp_w_dcoffset_active_time : 10; /* bit[0-9]  : 直流补偿生效时刻提前量  */
        unsigned long  reserved                   : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DCOFFSET_ACTIVE_TIME_UNION;
#define WBBP_DCOFFSET_ACTIVE_TIME_dsp_w_dcoffset_active_time_START  (0)
#define WBBP_DCOFFSET_ACTIVE_TIME_dsp_w_dcoffset_active_time_END    (9)


/*****************************************************************************
 结构名    : WBBP_DSP_VBIAS_ACTIVE_TIME_UNION
 结构说明  : DSP_VBIAS_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_vbias_active_time_reg;
    struct
    {
        unsigned long  dsp_vbias_active_time : 10; /* bit[0-9]  : APT电压生效时刻，默认值为时隙边界提前40chip。 */
        unsigned long  reserved              : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DSP_VBIAS_ACTIVE_TIME_UNION;
#define WBBP_DSP_VBIAS_ACTIVE_TIME_dsp_vbias_active_time_START  (0)
#define WBBP_DSP_VBIAS_ACTIVE_TIME_dsp_vbias_active_time_END    (9)


/*****************************************************************************
 结构名    : WBBP_PA_ACTIVE_TIME_HM_UNION
 结构说明  : PA_ACTIVE_TIME_HM 寄存器结构定义。地址偏移量:0x0C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_active_time_hm_reg;
    struct
    {
        unsigned long  cpu_pa_h2m_active_time : 10; /* bit[0-9]  : PA从高增益向中增益切换时提前上行时隙头的时间，单位chip。 */
        unsigned long  reserved_0             : 6;  /* bit[10-15]: 保留 */
        unsigned long  cpu_pa_m2h_active_time : 10; /* bit[16-25]: PA从中增益向高增益切换时提前上行时隙头的时间，单位chip。 */
        unsigned long  reserved_1             : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_PA_ACTIVE_TIME_HM_UNION;
#define WBBP_PA_ACTIVE_TIME_HM_cpu_pa_h2m_active_time_START  (0)
#define WBBP_PA_ACTIVE_TIME_HM_cpu_pa_h2m_active_time_END    (9)
#define WBBP_PA_ACTIVE_TIME_HM_cpu_pa_m2h_active_time_START  (16)
#define WBBP_PA_ACTIVE_TIME_HM_cpu_pa_m2h_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_PA_ACTIVE_TIME_ML_UNION
 结构说明  : PA_ACTIVE_TIME_ML 寄存器结构定义。地址偏移量:0x0C8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_active_time_ml_reg;
    struct
    {
        unsigned long  cpu_pa_m2l_active_time : 10; /* bit[0-9]  : PA从中增益向低增益切换时提前上行时隙头的时间，单位chip。 */
        unsigned long  reserved_0             : 6;  /* bit[10-15]: 保留 */
        unsigned long  cpu_pa_l2m_active_time : 10; /* bit[16-25]: PA从低增益向中增益切换时提前上行时隙头的时间，单位chip。 */
        unsigned long  reserved_1             : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_PA_ACTIVE_TIME_ML_UNION;
#define WBBP_PA_ACTIVE_TIME_ML_cpu_pa_m2l_active_time_START  (0)
#define WBBP_PA_ACTIVE_TIME_ML_cpu_pa_m2l_active_time_END    (9)
#define WBBP_PA_ACTIVE_TIME_ML_cpu_pa_l2m_active_time_START  (16)
#define WBBP_PA_ACTIVE_TIME_ML_cpu_pa_l2m_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_PA_MH_VBIAS_ACTIVE_TIME_UNION
 结构说明  : PA_MH_VBIAS_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_mh_vbias_active_time_reg;
    struct
    {
        unsigned long  pa_h2m_vbias_active_time : 10; /* bit[0-9]  : PA在高切中档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
                                                                     该参数无效，统一用wpavbias_active_time。 */
        unsigned long  reserved_0               : 6;  /* bit[10-15]: 保留 */
        unsigned long  pa_m2h_vbias_active_time : 10; /* bit[16-25]: PA在中切高档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
                                                                     该参数无效，统一用wpavbias_active_time。 */
        unsigned long  reserved_1               : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_PA_MH_VBIAS_ACTIVE_TIME_UNION;
#define WBBP_PA_MH_VBIAS_ACTIVE_TIME_pa_h2m_vbias_active_time_START  (0)
#define WBBP_PA_MH_VBIAS_ACTIVE_TIME_pa_h2m_vbias_active_time_END    (9)
#define WBBP_PA_MH_VBIAS_ACTIVE_TIME_pa_m2h_vbias_active_time_START  (16)
#define WBBP_PA_MH_VBIAS_ACTIVE_TIME_pa_m2h_vbias_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_PA_LM_VBIAS_ACTIVE_TIME_UNION
 结构说明  : PA_LM_VBIAS_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_lm_vbias_active_time_reg;
    struct
    {
        unsigned long  pa_m2l_vbias_active_time : 10; /* bit[0-9]  : PA在中切低档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
                                                                     该参数无效，统一用wpavbias_active_time。 */
        unsigned long  reserved_0               : 6;  /* bit[10-15]: 保留 */
        unsigned long  pa_l2m_vbias_active_time : 10; /* bit[16-25]: PA在低切中档位时，新VBIAS控制字生效时间相对于时隙头的提前量。
                                                                     该参数无效，统一用wpavbias_active_time。 */
        unsigned long  reserved_1               : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_PA_LM_VBIAS_ACTIVE_TIME_UNION;
#define WBBP_PA_LM_VBIAS_ACTIVE_TIME_pa_m2l_vbias_active_time_START  (0)
#define WBBP_PA_LM_VBIAS_ACTIVE_TIME_pa_m2l_vbias_active_time_END    (9)
#define WBBP_PA_LM_VBIAS_ACTIVE_TIME_pa_l2m_vbias_active_time_START  (16)
#define WBBP_PA_LM_VBIAS_ACTIVE_TIME_pa_l2m_vbias_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_FE_VBIAS_ACTIVE_TIME_UNION
 结构说明  : FE_VBIAS_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      fe_vbias_active_time_reg;
    struct
    {
        unsigned long  wrfvbias_active_time : 10; /* bit[0-9]  : RFVBIAS提前上行时隙头生效时刻，单位为chip。(删除) */
        unsigned long  reserved_0           : 6;  /* bit[10-15]: 保留 */
        unsigned long  wpavbias_active_time : 10; /* bit[16-25]: PAVBIAS提前上行时隙头生效时刻，单位为chip。在MMMB PA和EAGLE PA(第一个控制字)都可使用。 */
        unsigned long  reserved_1           : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_FE_VBIAS_ACTIVE_TIME_UNION;
#define WBBP_FE_VBIAS_ACTIVE_TIME_wrfvbias_active_time_START  (0)
#define WBBP_FE_VBIAS_ACTIVE_TIME_wrfvbias_active_time_END    (9)
#define WBBP_FE_VBIAS_ACTIVE_TIME_wpavbias_active_time_START  (16)
#define WBBP_FE_VBIAS_ACTIVE_TIME_wpavbias_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_RRC_DELAY_CHIP_NUM_UNION
 结构说明  : RRC_DELAY_CHIP_NUM 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000011，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rrc_delay_chip_num_reg;
    struct
    {
        unsigned long  rrc_delay_chip_num : 6;  /* bit[0-5] : 上行调制RRC延迟时间，单位chip。 */
        unsigned long  reserved           : 26; /* bit[6-31]: 保留 */
    } reg;
} WBBP_RRC_DELAY_CHIP_NUM_UNION;
#define WBBP_RRC_DELAY_CHIP_NUM_rrc_delay_chip_num_START  (0)
#define WBBP_RRC_DELAY_CHIP_NUM_rrc_delay_chip_num_END    (5)


/*****************************************************************************
 结构名    : WBBP_CPU_TX_SWC_UNION
 结构说明  : CPU_TX_SWC 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_tx_swc_reg;
    struct
    {
        unsigned long  cpu_tx_swc_active_time : 10; /* bit[0-9]  : 天线调谐配置提前帧头配置量，当上行打开后，WBBP每次在帧头提前cpu_tx_sw_active_time进行配置，单位为chip，默认值为0。 */
        unsigned long  reserved_0             : 6;  /* bit[10-15]: 保留 */
        unsigned long  cpu_tx_swc_cfg_flag    : 1;  /* bit[16]   : 天线调谐配置更新标志，脉冲信号。 */
        unsigned long  reserved_1             : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_CPU_TX_SWC_UNION;
#define WBBP_CPU_TX_SWC_cpu_tx_swc_active_time_START  (0)
#define WBBP_CPU_TX_SWC_cpu_tx_swc_active_time_END    (9)
#define WBBP_CPU_TX_SWC_cpu_tx_swc_cfg_flag_START     (16)
#define WBBP_CPU_TX_SWC_cpu_tx_swc_cfg_flag_END       (16)


/*****************************************************************************
 结构名    : WBBP_WPA_VBIAS_ACTIVE_TIME2_3_UNION
 结构说明  : WPA_VBIAS_ACTIVE_TIME2_3 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wpa_vbias_active_time2_3_reg;
    struct
    {
        unsigned long  wpavbias2_active_time : 10; /* bit[0-9]  : EAGLE PA 第二个PAVBIAS控制字提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_0            : 6;  /* bit[10-15]: 保留 */
        unsigned long  wpavbias3_active_time : 10; /* bit[16-25]: EAGLE PA 第三个PAVBIAS控制字提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_1            : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_WPA_VBIAS_ACTIVE_TIME2_3_UNION;
#define WBBP_WPA_VBIAS_ACTIVE_TIME2_3_wpavbias2_active_time_START  (0)
#define WBBP_WPA_VBIAS_ACTIVE_TIME2_3_wpavbias2_active_time_END    (9)
#define WBBP_WPA_VBIAS_ACTIVE_TIME2_3_wpavbias3_active_time_START  (16)
#define WBBP_WPA_VBIAS_ACTIVE_TIME2_3_wpavbias3_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_WPA_VBIAS_ACTIVE_TIME4_UNION
 结构说明  : WPA_VBIAS_ACTIVE_TIME4 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wpa_vbias_active_time4_reg;
    struct
    {
        unsigned long  wpavbias4_active_time       : 10; /* bit[0-9]  : EAGLE PA 第四个PAVBIAS控制字(trigger拉高)提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_0                  : 6;  /* bit[10-15]: 保留 */
        unsigned long  wpavbias4_active_again_time : 10; /* bit[16-25]: EAGLE PA 第四个PAVBIAS控制字(trigger生效)提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_1                  : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_WPA_VBIAS_ACTIVE_TIME4_UNION;
#define WBBP_WPA_VBIAS_ACTIVE_TIME4_wpavbias4_active_time_START        (0)
#define WBBP_WPA_VBIAS_ACTIVE_TIME4_wpavbias4_active_time_END          (9)
#define WBBP_WPA_VBIAS_ACTIVE_TIME4_wpavbias4_active_again_time_START  (16)
#define WBBP_WPA_VBIAS_ACTIVE_TIME4_wpavbias4_active_again_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_DBB_ATTEN_ACTIVE_TIME_UNION
 结构说明  : DBB_ATTEN_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbb_atten_active_time_reg;
    struct
    {
        unsigned long  dbb_active_time          : 10; /* bit[0-9]  : 数字增益回退提前上行时隙头生效时刻。单位1/4chip。 */
        unsigned long  reserved_0               : 2;  /* bit[10-11]: 保留 */
        unsigned long  dsp_dbb_powcomp_flag_en  : 1;  /* bit[12]   : 上下时隙中间HSDPA功率补偿使能，高电平表示在HSDPCCH时隙头位置dbb做补偿。 */
        unsigned long  reserved_1               : 3;  /* bit[13-15]: 保留 */
        unsigned long  dbb_halfslot_active_time : 14; /* bit[16-29]: hsdpa信道数字增益回退在上行时隙头后生效时刻。单位1/4chip。 */
        unsigned long  reserved_2               : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_DBB_ATTEN_ACTIVE_TIME_UNION;
#define WBBP_DBB_ATTEN_ACTIVE_TIME_dbb_active_time_START           (0)
#define WBBP_DBB_ATTEN_ACTIVE_TIME_dbb_active_time_END             (9)
#define WBBP_DBB_ATTEN_ACTIVE_TIME_dsp_dbb_powcomp_flag_en_START   (12)
#define WBBP_DBB_ATTEN_ACTIVE_TIME_dsp_dbb_powcomp_flag_en_END     (12)
#define WBBP_DBB_ATTEN_ACTIVE_TIME_dbb_halfslot_active_time_START  (16)
#define WBBP_DBB_ATTEN_ACTIVE_TIME_dbb_halfslot_active_time_END    (29)


/*****************************************************************************
 结构名    : WBBP_TX_LOWPOW_ACTIVE_TIME1_2_UNION
 结构说明  : TX_LOWPOW_ACTIVE_TIME1_2 寄存器结构定义。地址偏移量:0x0EC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_lowpow_active_time1_2_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow1_active_time : 10; /* bit[0-9]  : 上行低功耗控制字1提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_0                 : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_tx_lowpow2_active_time : 10; /* bit[16-25]: 上行低功耗控制字2提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_1                 : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_TX_LOWPOW_ACTIVE_TIME1_2_UNION;
#define WBBP_TX_LOWPOW_ACTIVE_TIME1_2_dsp_tx_lowpow1_active_time_START  (0)
#define WBBP_TX_LOWPOW_ACTIVE_TIME1_2_dsp_tx_lowpow1_active_time_END    (9)
#define WBBP_TX_LOWPOW_ACTIVE_TIME1_2_dsp_tx_lowpow2_active_time_START  (16)
#define WBBP_TX_LOWPOW_ACTIVE_TIME1_2_dsp_tx_lowpow2_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_TX_LOWPOW_ACTIVE_TIME3_4_UNION
 结构说明  : TX_LOWPOW_ACTIVE_TIME3_4 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_lowpow_active_time3_4_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow3_active_time : 10; /* bit[0-9]  : 上行低功耗控制字3提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_0                 : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_tx_lowpow4_active_time : 10; /* bit[16-25]: 上行低功耗控制字4提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_1                 : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_TX_LOWPOW_ACTIVE_TIME3_4_UNION;
#define WBBP_TX_LOWPOW_ACTIVE_TIME3_4_dsp_tx_lowpow3_active_time_START  (0)
#define WBBP_TX_LOWPOW_ACTIVE_TIME3_4_dsp_tx_lowpow3_active_time_END    (9)
#define WBBP_TX_LOWPOW_ACTIVE_TIME3_4_dsp_tx_lowpow4_active_time_START  (16)
#define WBBP_TX_LOWPOW_ACTIVE_TIME3_4_dsp_tx_lowpow4_active_time_END    (25)


/*****************************************************************************
 结构名    : WBBP_DSP_SPI_2ABB_UNION
 结构说明  : DSP_SPI_2ABB 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_spi_2abb_reg;
    struct
    {
        unsigned long  dsp_spi_2abb_word : 16; /* bit[0-15] : DSP直接使用SPI口对HKADC进行读写时的指令寄存器值。高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。 */
        unsigned long  reserved          : 14; /* bit[16-29]: 保留 */
        unsigned long  dsp_spi_2abb_ren  : 1;  /* bit[30]   : 读写标志。0，表示写；1，表示读。 */
        unsigned long  dsp_spi_2abb_en   : 1;  /* bit[31]   : DSP直接使用SPI口的标志信号，高有效。 */
    } reg;
} WBBP_DSP_SPI_2ABB_UNION;
#define WBBP_DSP_SPI_2ABB_dsp_spi_2abb_word_START  (0)
#define WBBP_DSP_SPI_2ABB_dsp_spi_2abb_word_END    (15)
#define WBBP_DSP_SPI_2ABB_dsp_spi_2abb_ren_START   (30)
#define WBBP_DSP_SPI_2ABB_dsp_spi_2abb_ren_END     (30)
#define WBBP_DSP_SPI_2ABB_dsp_spi_2abb_en_START    (31)
#define WBBP_DSP_SPI_2ABB_dsp_spi_2abb_en_END      (31)


/*****************************************************************************
 结构名    : WBBP_DSP_POW_DET_UNION
 结构说明  : DSP_POW_DET 寄存器结构定义。地址偏移量:0x204，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_pow_det_reg;
    struct
    {
        unsigned long  dsp_pow_det : 1;  /* bit[0]   : 强制功率检测使能。1，表示一次功率检测；0，无效。BBP在功率检测结果输出后进行自清零，软件通过查询此bit可确定功率检测结果是否有效。 */
        unsigned long  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_POW_DET_UNION;
#define WBBP_DSP_POW_DET_dsp_pow_det_START  (0)
#define WBBP_DSP_POW_DET_dsp_pow_det_END    (0)


/*****************************************************************************
 结构名    : WBBP_POW_DET_START_2ABB_UNION
 结构说明  : POW_DET_START_2ABB 寄存器结构定义。地址偏移量:0x208，初值:0x10100000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_start_2abb_reg;
    struct
    {
        unsigned long  pow_det_start_2abb          : 16; /* bit[0-15] : 1）当使用RFIC-PD方案时，表示：控制海思RF的功率检测器件和AD采样的打开门限。当发射功率超过此门限时，打开RF的功率检测器件与AD。
                                                                        说明：V3只使用bit[9:0]；此门限必须小于pow_det_open_threshold，且为正数；
                                                                        2）当使用HKADC-PD方案时，表示：通知ABB进行HKADC采样的指令寄存器值，高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。 */
        unsigned long  dsp_pd_bp_to_start_interval : 10; /* bit[16-25]: 配置ABB从bypass为低到启动start （ABB开始转换）的时间间隔，单位为chip。 */
        unsigned long  reserved_0                  : 2;  /* bit[26-27]: 保留 */
        unsigned long  dsp_hkadc_ssi_clk_cfg       : 3;  /* bit[28-30]: HKADC SSI Master释放单线控制权到Master开始检查Slave返回的同步位的时间配置值。 
                                                                        延迟=1.5+0.5*Step_num(clk).
                                                                        Step_num=0~7 */
        unsigned long  reserved_1                  : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_POW_DET_START_2ABB_UNION;
#define WBBP_POW_DET_START_2ABB_pow_det_start_2abb_START           (0)
#define WBBP_POW_DET_START_2ABB_pow_det_start_2abb_END             (15)
#define WBBP_POW_DET_START_2ABB_dsp_pd_bp_to_start_interval_START  (16)
#define WBBP_POW_DET_START_2ABB_dsp_pd_bp_to_start_interval_END    (25)
#define WBBP_POW_DET_START_2ABB_dsp_hkadc_ssi_clk_cfg_START        (28)
#define WBBP_POW_DET_START_2ABB_dsp_hkadc_ssi_clk_cfg_END          (30)


/*****************************************************************************
 结构名    : WBBP_POW_DET_READ1_2ABB_UNION
 结构说明  : POW_DET_READ1_2ABB 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_read1_2abb_reg;
    struct
    {
        unsigned long  pow_det_read1_2abb       : 16; /* bit[0-15] : 1）当使用RFIC-PD方案时，表示：控制海思RF的功率检测器件和AD采样的的关闭门限。当发射功率小于此门限时，关闭RF的功率检测器件与AD。
                                                                     说明：V3只使用bit[10:0]；此门限必须小于pow_det_close_threshold；
                                                                     2）当使用HKADC-PD方案时，表示：读取ABB中HKADC采样结果第一个寄存器的指令寄存器值，高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。 */
        unsigned long  dsp_abb_pd_bypass_l_word : 16; /* bit[16-31]: 配置打开HKADC PD通道的指令寄存器值。BBP从最高位开始发。 */
    } reg;
} WBBP_POW_DET_READ1_2ABB_UNION;
#define WBBP_POW_DET_READ1_2ABB_pow_det_read1_2abb_START        (0)
#define WBBP_POW_DET_READ1_2ABB_pow_det_read1_2abb_END          (15)
#define WBBP_POW_DET_READ1_2ABB_dsp_abb_pd_bypass_l_word_START  (16)
#define WBBP_POW_DET_READ1_2ABB_dsp_abb_pd_bypass_l_word_END    (31)


/*****************************************************************************
 结构名    : WBBP_POW_DET_READ2_2ABB_UNION
 结构说明  : POW_DET_READ2_2ABB 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_read2_2abb_reg;
    struct
    {
        unsigned long  pow_det_read2_2abb       : 16; /* bit[0-15] : 读取ABB中HKADC采样结果第二个寄存器的指令寄存器值。高8位为指令部分，低8位为数据部分，BBP从最高位开始发送。
                                                                     软件根据实际需要配置，BBP将此信息通过SPI口配置给ABB后，ABB通过此SPI口将结果送给BBP。
                                                                     说明：Hi6411V110，此寄存器值需配置16'hce00。 */
        unsigned long  dsp_abb_pd_bypass_h_word : 16; /* bit[16-31]: 配置关闭HKADC PD通道的指令寄存器值。BBP从最高位开始发。 */
    } reg;
} WBBP_POW_DET_READ2_2ABB_UNION;
#define WBBP_POW_DET_READ2_2ABB_pow_det_read2_2abb_START        (0)
#define WBBP_POW_DET_READ2_2ABB_pow_det_read2_2abb_END          (15)
#define WBBP_POW_DET_READ2_2ABB_dsp_abb_pd_bypass_h_word_START  (16)
#define WBBP_POW_DET_READ2_2ABB_dsp_abb_pd_bypass_h_word_END    (31)


/*****************************************************************************
 结构名    : WBBP_SAMPLE_TIME_ABB_UNION
 结构说明  : SAMPLE_TIME_ABB 寄存器结构定义。地址偏移量:0x214，初值:0x00000030，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sample_time_abb_reg;
    struct
    {
        unsigned long  sample_time_abb         : 10; /* bit[0-9]  : HKADC采样信号处理时间，单位chip。具体表示意义请参考《Hi6750V100 芯片WBBP子系统与CPU接口说明书.doc》之16.2.1。 */
        unsigned long  reserved_0              : 2;  /* bit[10-11]: 保留 */
        unsigned long  dsp_pd_sam_num          : 2;  /* bit[12-13]: 配置W上行每个时隙进行PD检测的次数。
                                                                    2'd0：4次；
                                                                    2'd1：8次；
                                                                    2'd2：16次。 */
        unsigned long  dsp_pd_dcoffset_sam_num : 2;  /* bit[14-15]: 配置WHKADC上行每个时隙进行dc offset检测的次数。
                                                                    2'd0：4次；
                                                                    2'd1：8次；
                                                                    2'd2：16次。 */
        unsigned long  dsp_hkadc_chsel_time    : 4;  /* bit[16-19]: 授权有效到发送HKADC通道控制字时刻间隔,单位chip */
        unsigned long  reserved_1              : 10; /* bit[20-29]: 保留 */
        unsigned long  dsp_hkadc_sm_clr_en     : 1;  /* bit[30]   : hkadc状态机复位信号，电平信号。
                                                                    1：表示复位hkadc状态机；0表示正常工作。 */
        unsigned long  reserved_2              : 1;  /* bit[31]   : 保留 */
    } reg;
} WBBP_SAMPLE_TIME_ABB_UNION;
#define WBBP_SAMPLE_TIME_ABB_sample_time_abb_START          (0)
#define WBBP_SAMPLE_TIME_ABB_sample_time_abb_END            (9)
#define WBBP_SAMPLE_TIME_ABB_dsp_pd_sam_num_START           (12)
#define WBBP_SAMPLE_TIME_ABB_dsp_pd_sam_num_END             (13)
#define WBBP_SAMPLE_TIME_ABB_dsp_pd_dcoffset_sam_num_START  (14)
#define WBBP_SAMPLE_TIME_ABB_dsp_pd_dcoffset_sam_num_END    (15)
#define WBBP_SAMPLE_TIME_ABB_dsp_hkadc_chsel_time_START     (16)
#define WBBP_SAMPLE_TIME_ABB_dsp_hkadc_chsel_time_END       (19)
#define WBBP_SAMPLE_TIME_ABB_dsp_hkadc_sm_clr_en_START      (30)
#define WBBP_SAMPLE_TIME_ABB_dsp_hkadc_sm_clr_en_END        (30)


/*****************************************************************************
 结构名    : WBBP_POW_DET_RESULT_UNION
 结构说明  : POW_DET_RESULT 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_result_reg;
    struct
    {
        unsigned long  pow_det_result_2dsp : 10; /* bit[0-9]  : 功率检测结果。BBP将每次功率检测结果上报软件。所有从ABB读出的结果，通过此寄存器上报。发射功率越高，上报结果越大，呈线性规律。 */
        unsigned long  reserved_0          : 2;  /* bit[10-11]: 保留 */
        unsigned long  pd_ssi_rpt_cpu      : 12; /* bit[12-23]: 上报HKADC_PD进行SSI传输的次数。定位用。 */
        unsigned long  reserved_1          : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_POW_DET_RESULT_UNION;
#define WBBP_POW_DET_RESULT_pow_det_result_2dsp_START  (0)
#define WBBP_POW_DET_RESULT_pow_det_result_2dsp_END    (9)
#define WBBP_POW_DET_RESULT_pd_ssi_rpt_cpu_START       (12)
#define WBBP_POW_DET_RESULT_pd_ssi_rpt_cpu_END         (23)


/*****************************************************************************
 结构名    : WBBP_PMAX_LIMIT_EN_UNION
 结构说明  : PMAX_LIMIT_EN 寄存器结构定义。地址偏移量:0x21C，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pmax_limit_en_reg;
    struct
    {
        unsigned long  pmax_limit_en  : 1;  /* bit[0]    : 最大功率限制使能。1，表示有效；0，表示无效。 */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned long  ad_width_sel   : 1;  /* bit[4]    : AD位宽选择。1，表示8bit；0，表示10bit。 */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dsp_rfic_pd_en : 2;  /* bit[8-9]  : 00:无效值。
                                                           01:6360 RFIC模式，不仲裁，不去直流。
                                                           10:MMMB PA模式，仲裁，不去直流。
                                                           11:6361 RFIC模式，仲裁，去直流。 */
        unsigned long  reserved_2     : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_PMAX_LIMIT_EN_UNION;
#define WBBP_PMAX_LIMIT_EN_pmax_limit_en_START   (0)
#define WBBP_PMAX_LIMIT_EN_pmax_limit_en_END     (0)
#define WBBP_PMAX_LIMIT_EN_ad_width_sel_START    (4)
#define WBBP_PMAX_LIMIT_EN_ad_width_sel_END      (4)
#define WBBP_PMAX_LIMIT_EN_dsp_rfic_pd_en_START  (8)
#define WBBP_PMAX_LIMIT_EN_dsp_rfic_pd_en_END    (9)


/*****************************************************************************
 结构名    : WBBP_RF_PA_STABLE_TIME_UNION
 结构说明  : RF_PA_STABLE_TIME 寄存器结构定义。地址偏移量:0x220，初值:0x0000000A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_pa_stable_time_reg;
    struct
    {
        unsigned long  rf_pa_stable_time : 12; /* bit[0-11] : 发射功率变化后，RF与PA的稳定时间，单位chip。具体表示意义请参考《Hi6750V100 芯片WBBP子系统与CPU接口说明书.doc》之16.2.1。 */
        unsigned long  reserved          : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_RF_PA_STABLE_TIME_UNION;
#define WBBP_RF_PA_STABLE_TIME_rf_pa_stable_time_START  (0)
#define WBBP_RF_PA_STABLE_TIME_rf_pa_stable_time_END    (11)


/*****************************************************************************
 结构名    : WBBP_POW_DET_FREQ_COMP_UNION
 结构说明  : POW_DET_FREQ_COMP 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_freq_comp_reg;
    struct
    {
        unsigned long  pow_det_freq_comp : 11; /* bit[0-10] : 功率检测时的频率补偿值，单位0.1dBm。软件根据当前的频点将相应的NV项配置到BBP。 */
        unsigned long  reserved          : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_POW_DET_FREQ_COMP_UNION;
#define WBBP_POW_DET_FREQ_COMP_pow_det_freq_comp_START  (0)
#define WBBP_POW_DET_FREQ_COMP_pow_det_freq_comp_END    (10)


/*****************************************************************************
 结构名    : WBBP_POW_DET_TEMP_COMP_UNION
 结构说明  : POW_DET_TEMP_COMP 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_temp_comp_reg;
    struct
    {
        unsigned long  pow_det_temp_comp : 11; /* bit[0-10] : 功率检测时的温度补偿值，单位0.1dBm。软件根据当前的温度将相应的NV项配置到BBP。 */
        unsigned long  reserved          : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_POW_DET_TEMP_COMP_UNION;
#define WBBP_POW_DET_TEMP_COMP_pow_det_temp_comp_START  (0)
#define WBBP_POW_DET_TEMP_COMP_pow_det_temp_comp_END    (10)


/*****************************************************************************
 结构名    : WBBP_POW_DET_INTERVAL_UNION
 结构说明  : POW_DET_INTERVAL 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_interval_reg;
    struct
    {
        unsigned long  pow_det_interval : 10; /* bit[0-9]  : 两次功率检测之间的时间间隔，单位chip。 */
        unsigned long  reserved         : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_POW_DET_INTERVAL_UNION;
#define WBBP_POW_DET_INTERVAL_pow_det_interval_START  (0)
#define WBBP_POW_DET_INTERVAL_pow_det_interval_END    (9)


/*****************************************************************************
 结构名    : WBBP_POW_DET_THRESHOLD_UNION
 结构说明  : POW_DET_THRESHOLD 寄存器结构定义。地址偏移量:0x230，初值:0x005A0064，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pow_det_threshold_reg;
    struct
    {
        unsigned long  pow_det_open_threshold  : 10; /* bit[0-9]  : 功率检测打开门限。当上行理论发射功率超过此门限时，BBP打开功率检测功能。范围0~1023，单位0.1dBm。
                                                                    说明：根据功率检测总体方案，功率检测范围为10~27dBm，即此寄存器默认值为100。 */
        unsigned long  reserved_0              : 6;  /* bit[10-15]: 保留 */
        unsigned long  pow_det_close_threshold : 10; /* bit[16-25]: 功率检测关闭门限。当上行理论发射功率低于此门限时，BBP关闭功率检测功能。范围0~1023，单位0.1dBm。
                                                                    注意：pow_det_close_threshold必须小于pow_det_open_threshold，否则，功率检测功能无法打开。 */
        unsigned long  reserved_1              : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_POW_DET_THRESHOLD_UNION;
#define WBBP_POW_DET_THRESHOLD_pow_det_open_threshold_START   (0)
#define WBBP_POW_DET_THRESHOLD_pow_det_open_threshold_END     (9)
#define WBBP_POW_DET_THRESHOLD_pow_det_close_threshold_START  (16)
#define WBBP_POW_DET_THRESHOLD_pow_det_close_threshold_END    (25)


/*****************************************************************************
 结构名    : WBBP_ACT_NOM_ERROR_UNION
 结构说明  : ACT_NOM_ERROR 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      act_nom_error_reg;
    struct
    {
        unsigned long  act_nom_error      : 11; /* bit[0-10] : 实际发射功率-理论发射功率，单位0.1dBm。 */
        unsigned long  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned long  act_nom_error_aver : 11; /* bit[16-26]: act_nom_error一帧内的平均值。 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_ACT_NOM_ERROR_UNION;
#define WBBP_ACT_NOM_ERROR_act_nom_error_START       (0)
#define WBBP_ACT_NOM_ERROR_act_nom_error_END         (10)
#define WBBP_ACT_NOM_ERROR_act_nom_error_aver_START  (16)
#define WBBP_ACT_NOM_ERROR_act_nom_error_aver_END    (26)


/*****************************************************************************
 结构名    : WBBP_DCOFFSET_POW_LINE_VALUE_UNION
 结构说明  : DCOFFSET_POW_LINE_VALUE 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dcoffset_pow_line_value_reg;
    struct
    {
        unsigned long  pd_dcoffset_result : 10; /* bit[0-9]  : HKADC每时隙直流测量平均结果上报。查表前的线性值，无符号数。 */
        unsigned long  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned long  pow_mea_result     : 10; /* bit[16-25]: 每时隙功率测量平均结果上报。查表前的线性值，无符号数。 */
        unsigned long  reserved_1         : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_DCOFFSET_POW_LINE_VALUE_UNION;
#define WBBP_DCOFFSET_POW_LINE_VALUE_pd_dcoffset_result_START  (0)
#define WBBP_DCOFFSET_POW_LINE_VALUE_pd_dcoffset_result_END    (9)
#define WBBP_DCOFFSET_POW_LINE_VALUE_pow_mea_result_START      (16)
#define WBBP_DCOFFSET_POW_LINE_VALUE_pow_mea_result_END        (25)


/*****************************************************************************
 结构名    : WBBP_DSP_CONFIG_PD_DCOFFSET_UNION
 结构说明  : DSP_CONFIG_PD_DCOFFSET 寄存器结构定义。地址偏移量:0x23C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_config_pd_dcoffset_reg;
    struct
    {
        unsigned long  dsp_pd_dcoffset_config_value : 10; /* bit[0-9]  : 软件强配HKADC直流,无符号数 */
        unsigned long  dsp_pd_dcoffset_config_en    : 1;  /* bit[10]   : 软件强配HKADC直流使能,高电平有效 */
        unsigned long  pow_det_error_hold_clr_sel   : 1;  /* bit[11]   : PD关闭时,PD检测误差,1:保持   0:清零 */
        unsigned long  dsp_hkadc_powdet_mode        : 1;  /* bit[12]   : HKADC非信令下,软件读取PD模式:
                                                                         0 表示采样一次dcoffset上报.
                                                                         1 表示一个时隙内先采样平均得到dcoffset然后采样平均得到功率检测线性值,最后上报值=功率检测线性值-dcoffset; */
        unsigned long  reserved                     : 19; /* bit[13-31]: 保留 */
    } reg;
} WBBP_DSP_CONFIG_PD_DCOFFSET_UNION;
#define WBBP_DSP_CONFIG_PD_DCOFFSET_dsp_pd_dcoffset_config_value_START  (0)
#define WBBP_DSP_CONFIG_PD_DCOFFSET_dsp_pd_dcoffset_config_value_END    (9)
#define WBBP_DSP_CONFIG_PD_DCOFFSET_dsp_pd_dcoffset_config_en_START     (10)
#define WBBP_DSP_CONFIG_PD_DCOFFSET_dsp_pd_dcoffset_config_en_END       (10)
#define WBBP_DSP_CONFIG_PD_DCOFFSET_pow_det_error_hold_clr_sel_START    (11)
#define WBBP_DSP_CONFIG_PD_DCOFFSET_pow_det_error_hold_clr_sel_END      (11)
#define WBBP_DSP_CONFIG_PD_DCOFFSET_dsp_hkadc_powdet_mode_START         (12)
#define WBBP_DSP_CONFIG_PD_DCOFFSET_dsp_hkadc_powdet_mode_END           (12)


/*****************************************************************************
 结构名    : WBBP_PD_TEST_CTRL_UNION
 结构说明  : PD_TEST_CTRL 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pd_test_ctrl_reg;
    struct
    {
        unsigned long  pd_test_mode               : 1;  /* bit[0]   : PD测试模式选择。1，表示测试模式；0，表示正常模式。 */
        unsigned long  reserved_0                 : 3;  /* bit[1-3] : 保留 */
        unsigned long  pd_test_pattern_r5_negtive : 1;  /* bit[4]   : 测试模式下，存在R5信道的上行R99时隙是否进行功率检测。
                                                                      bit[4]：1，表示存在R5信道的上行R99时隙不进行功率检测；0，表示存在R5信道的上行R99时隙进行功率检测。（根据总体方案，只有R5信道b值不变的时隙才进行功率检测。） */
        unsigned long  pd_test_pattern_r6         : 1;  /* bit[5]   : 测试模式下，存在R6信道的上行R99时隙是否进行功率检测。bit[5]：1，表示存在R6信道的上行R99时隙不进行功率检测；0，表示存在R6信道的上行R99时隙进行功率检测。 */
        unsigned long  pd_test_pattern_r5         : 1;  /* bit[6]   : 测试模式下，存在R5信道的上行R99时隙是否进行功率检测。bit[6]：1，表示只有存在R5信道的上行R99时隙进行功率检测。 */
        unsigned long  reserved_1                 : 25; /* bit[7-31]: 保留 */
    } reg;
} WBBP_PD_TEST_CTRL_UNION;
#define WBBP_PD_TEST_CTRL_pd_test_mode_START                (0)
#define WBBP_PD_TEST_CTRL_pd_test_mode_END                  (0)
#define WBBP_PD_TEST_CTRL_pd_test_pattern_r5_negtive_START  (4)
#define WBBP_PD_TEST_CTRL_pd_test_pattern_r5_negtive_END    (4)
#define WBBP_PD_TEST_CTRL_pd_test_pattern_r6_START          (5)
#define WBBP_PD_TEST_CTRL_pd_test_pattern_r6_END            (5)
#define WBBP_PD_TEST_CTRL_pd_test_pattern_r5_START          (6)
#define WBBP_PD_TEST_CTRL_pd_test_pattern_r5_END            (6)


/*****************************************************************************
 结构名    : WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_UNION
 结构说明  : PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pmax_hold_en_pd_connect_ctrl_word_reg;
    struct
    {
        unsigned long  pmax_hold_en         : 1;  /* bit[0]    : 功率检测保持使能信号，用于在功率检测期间需要温度检测的情况。在需要进行温度检测时，软件将此寄存器配置为1，之后，将HKADC通道配置为温度检测，然后软件完成温度检测。温度检测完成后，软件将HKADC通道配置为功率检测后，再将此寄存器配置为0。 */
        unsigned long  reserved_0           : 2;  /* bit[1-2]  : 保留 */
        unsigned long  dsp_hkadc_pdclr_en   : 1;  /* bit[3]    : 0:表示不输出PD清零控制字给PD芯片(hi6361方案).
                                                                 1:表示输出PD清零控制字给PD芯片(hi6360方案). */
        unsigned long  pd_connect_ctrl_word : 24; /* bit[4-27] : HKADC powerdetct连接上行通道的控制字. */
        unsigned long  reserved_1           : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_UNION;
#define WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_pmax_hold_en_START          (0)
#define WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_pmax_hold_en_END            (0)
#define WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_dsp_hkadc_pdclr_en_START    (3)
#define WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_dsp_hkadc_pdclr_en_END      (3)
#define WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_pd_connect_ctrl_word_START  (4)
#define WBBP_PMAX_HOLD_EN_PD_CONNECT_CTRL_WORD_pd_connect_ctrl_word_END    (27)


/*****************************************************************************
 结构名    : WBBP_PD_DISCONNECT_CTRL_WORD_UNION
 结构说明  : PD_DISCONNECT_CTRL_WORD 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pd_disconnect_ctrl_word_reg;
    struct
    {
        unsigned long  pd_disconnect_ctrl_word : 24; /* bit[0-23] : HKADC powerdetct不连接上行通道的控制字. */
        unsigned long  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_PD_DISCONNECT_CTRL_WORD_UNION;
#define WBBP_PD_DISCONNECT_CTRL_WORD_pd_disconnect_ctrl_word_START  (0)
#define WBBP_PD_DISCONNECT_CTRL_WORD_pd_disconnect_ctrl_word_END    (23)


/*****************************************************************************
 结构名    : WBBP_DSP_TX_SWD_CFG_UNION
 结构说明  : DSP_TX_SWD_CFG 寄存器结构定义。地址偏移量:0x24C，初值:0x00000A0C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_tx_swd_cfg_reg;
    struct
    {
        unsigned long  dsp_tx_swd_en          : 1;  /* bit[0]    : 驻波检测启动使能，高电平有效，该信号有效时，驻波检测功能打开。 */
        unsigned long  dsp_tx_swd_slot        : 4;  /* bit[1-4]  : 驻波检测启动时隙号，默认值为6。 */
        unsigned long  dsp_tx_swd_stable_time : 10; /* bit[5-14] : 前反向通道切换等待延时，单位为 */
        unsigned long  dsp_swd_valid_clr      : 1;  /* bit[15]   : 驻波检测有效清零信号。 */
        unsigned long  reserved_0             : 3;  /* bit[16-18]: 保留 */
        unsigned long  dsp_rv_pd_sam_num      : 2;  /* bit[19-20]: 驻波检测时隙前后向功率检测次数， */
        unsigned long  reserved_1             : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_DSP_TX_SWD_CFG_UNION;
#define WBBP_DSP_TX_SWD_CFG_dsp_tx_swd_en_START           (0)
#define WBBP_DSP_TX_SWD_CFG_dsp_tx_swd_en_END             (0)
#define WBBP_DSP_TX_SWD_CFG_dsp_tx_swd_slot_START         (1)
#define WBBP_DSP_TX_SWD_CFG_dsp_tx_swd_slot_END           (4)
#define WBBP_DSP_TX_SWD_CFG_dsp_tx_swd_stable_time_START  (5)
#define WBBP_DSP_TX_SWD_CFG_dsp_tx_swd_stable_time_END    (14)
#define WBBP_DSP_TX_SWD_CFG_dsp_swd_valid_clr_START       (15)
#define WBBP_DSP_TX_SWD_CFG_dsp_swd_valid_clr_END         (15)
#define WBBP_DSP_TX_SWD_CFG_dsp_rv_pd_sam_num_START       (19)
#define WBBP_DSP_TX_SWD_CFG_dsp_rv_pd_sam_num_END         (20)


/*****************************************************************************
 结构名    : WBBP_DSP_TX_SWD_FW_SSI_CFG_UNION
 结构说明  : DSP_TX_SWD_FW_SSI_CFG 寄存器结构定义。地址偏移量:0x250，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_tx_swd_fw_ssi_cfg_reg;
    struct
    {
        unsigned long  dsp_tx_swd_fw_ssi_cfg : 24; /* bit[0-23] : 前向ssi控制字 */
        unsigned long  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DSP_TX_SWD_FW_SSI_CFG_UNION;
#define WBBP_DSP_TX_SWD_FW_SSI_CFG_dsp_tx_swd_fw_ssi_cfg_START  (0)
#define WBBP_DSP_TX_SWD_FW_SSI_CFG_dsp_tx_swd_fw_ssi_cfg_END    (23)


/*****************************************************************************
 结构名    : WBBP_DSP_TX_SWD_RV_SSI_CFG_UNION
 结构说明  : DSP_TX_SWD_RV_SSI_CFG 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_tx_swd_rv_ssi_cfg_reg;
    struct
    {
        unsigned long  dsp_tx_swd_rv_ssi_cfg : 24; /* bit[0-23] : 反向ssi控制字 */
        unsigned long  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DSP_TX_SWD_RV_SSI_CFG_UNION;
#define WBBP_DSP_TX_SWD_RV_SSI_CFG_dsp_tx_swd_rv_ssi_cfg_START  (0)
#define WBBP_DSP_TX_SWD_RV_SSI_CFG_dsp_tx_swd_rv_ssi_cfg_END    (23)


/*****************************************************************************
 结构名    : WBBP_DSP_TX_SWD_RPT_UNION
 结构说明  : DSP_TX_SWD_RPT 寄存器结构定义。地址偏移量:0x258，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_tx_swd_rpt_reg;
    struct
    {
        unsigned long  dsp_fw_vlt_value   : 10; /* bit[0-9]  : 前向电压上报值，10bits，无符号数 */
        unsigned long  reserved_0         : 2;  /* bit[10-11]: 保留 */
        unsigned long  dsp_rv_vlt_value   : 10; /* bit[12-21]: 反向电压上报值，10bits，无符号数 */
        unsigned long  reserved_1         : 2;  /* bit[22-23]: 保留 */
        unsigned long  dsp_pd_comp_value  : 6;  /* bit[24-29]: PD检测功率补偿值，有符号数 */
        unsigned long  dsp_swd_valid_flag : 2;  /* bit[30-31]: 反向功率检测结果有效标志，电平信号。低比特为测试位，无需关注。2’b1x表示反向检测功率有效；2’b0x表示反向检测功率无效。dsp_swd_valid_clr为高脉冲时， dsp_swd_valid_flag清零 */
    } reg;
} WBBP_DSP_TX_SWD_RPT_UNION;
#define WBBP_DSP_TX_SWD_RPT_dsp_fw_vlt_value_START    (0)
#define WBBP_DSP_TX_SWD_RPT_dsp_fw_vlt_value_END      (9)
#define WBBP_DSP_TX_SWD_RPT_dsp_rv_vlt_value_START    (12)
#define WBBP_DSP_TX_SWD_RPT_dsp_rv_vlt_value_END      (21)
#define WBBP_DSP_TX_SWD_RPT_dsp_pd_comp_value_START   (24)
#define WBBP_DSP_TX_SWD_RPT_dsp_pd_comp_value_END     (29)
#define WBBP_DSP_TX_SWD_RPT_dsp_swd_valid_flag_START  (30)
#define WBBP_DSP_TX_SWD_RPT_dsp_swd_valid_flag_END    (31)


/*****************************************************************************
 结构名    : WBBP_MIPI_APT_ADDR_UNION
 结构说明  : MIPI_APT_ADDR 寄存器结构定义。地址偏移量:0x400，初值:0x20002000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_apt_addr_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_apt_addr      : 16; /* bit[0-15] : mipi apt控制字地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。 */
        unsigned long  dsp_tx_mipi_pavbias_addr1 : 16; /* bit[16-31]: mipi pavbias控制字1地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。 */
    } reg;
} WBBP_MIPI_APT_ADDR_UNION;
#define WBBP_MIPI_APT_ADDR_dsp_tx_mipi_apt_addr_START       (0)
#define WBBP_MIPI_APT_ADDR_dsp_tx_mipi_apt_addr_END         (15)
#define WBBP_MIPI_APT_ADDR_dsp_tx_mipi_pavbias_addr1_START  (16)
#define WBBP_MIPI_APT_ADDR_dsp_tx_mipi_pavbias_addr1_END    (31)


/*****************************************************************************
 结构名    : WBBP_MIPI_PAVBIAS_ADDR_UNION
 结构说明  : MIPI_PAVBIAS_ADDR 寄存器结构定义。地址偏移量:0x404，初值:0x20002000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_pavbias_addr_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_pavbias_addr2 : 16; /* bit[0-15] : mipi pavbias控制字2地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。 */
        unsigned long  dsp_tx_mipi_pavbias_addr3 : 16; /* bit[16-31]: mipi pavbias控制字3地址，高3比特位指令属性(默认为写)，低13比特位命令帧(地址)。 */
    } reg;
} WBBP_MIPI_PAVBIAS_ADDR_UNION;
#define WBBP_MIPI_PAVBIAS_ADDR_dsp_tx_mipi_pavbias_addr2_START  (0)
#define WBBP_MIPI_PAVBIAS_ADDR_dsp_tx_mipi_pavbias_addr2_END    (15)
#define WBBP_MIPI_PAVBIAS_ADDR_dsp_tx_mipi_pavbias_addr3_START  (16)
#define WBBP_MIPI_PAVBIAS_ADDR_dsp_tx_mipi_pavbias_addr3_END    (31)


/*****************************************************************************
 结构名    : WBBP_MIPI_PAVBIAS_TRIGGER1_UNION
 结构说明  : MIPI_PAVBIAS_TRIGGER1 寄存器结构定义。地址偏移量:0x408，初值:0x00400000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_pavbias_trigger1_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_pavbias_trig_word1 : 25; /* bit[0-24] : mipi pavbias trigger控制字1，高3比特位指令属性(默认为写)，中间13比特位命令帧(地址)，低9比特为数据。 */
        unsigned long  reserved_0                     : 3;  /* bit[25-27]: 保留 */
        unsigned long  dsp_tx_mipi_pavbias_trig_en1   : 1;  /* bit[28]   : mipi pavbias trigger控制字1发送使能，高电平有效。 */
        unsigned long  reserved_1                     : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_MIPI_PAVBIAS_TRIGGER1_UNION;
#define WBBP_MIPI_PAVBIAS_TRIGGER1_dsp_tx_mipi_pavbias_trig_word1_START  (0)
#define WBBP_MIPI_PAVBIAS_TRIGGER1_dsp_tx_mipi_pavbias_trig_word1_END    (24)
#define WBBP_MIPI_PAVBIAS_TRIGGER1_dsp_tx_mipi_pavbias_trig_en1_START    (28)
#define WBBP_MIPI_PAVBIAS_TRIGGER1_dsp_tx_mipi_pavbias_trig_en1_END      (28)


/*****************************************************************************
 结构名    : WBBP_MIPI_PAVBIAS_TRIGGER2_UNION
 结构说明  : MIPI_PAVBIAS_TRIGGER2 寄存器结构定义。地址偏移量:0x40C，初值:0x00400000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_pavbias_trigger2_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_pavbias_trig_word2 : 25; /* bit[0-24] : mipi pavbias trigger控制字2，高3比特位指令属性(默认为写)，中间13比特位命令帧(地址)，低9比特为数据。 */
        unsigned long  reserved_0                     : 3;  /* bit[25-27]: 保留 */
        unsigned long  dsp_tx_mipi_pavbias_trig_en2   : 1;  /* bit[28]   : mipi pavbias trigger控制字2发送使能，高电平有效。 */
        unsigned long  reserved_1                     : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_MIPI_PAVBIAS_TRIGGER2_UNION;
#define WBBP_MIPI_PAVBIAS_TRIGGER2_dsp_tx_mipi_pavbias_trig_word2_START  (0)
#define WBBP_MIPI_PAVBIAS_TRIGGER2_dsp_tx_mipi_pavbias_trig_word2_END    (24)
#define WBBP_MIPI_PAVBIAS_TRIGGER2_dsp_tx_mipi_pavbias_trig_en2_START    (28)
#define WBBP_MIPI_PAVBIAS_TRIGGER2_dsp_tx_mipi_pavbias_trig_en2_END      (28)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD1_H_UNION
 结构说明  : LOWPOW_SSI_WORD1_H 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word1_h_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word1_h : 24; /* bit[0-23] : 上行低功耗控制字1(高增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD1_H_UNION;
#define WBBP_LOWPOW_SSI_WORD1_H_dsp_tx_lowpow_ssi_word1_h_START  (0)
#define WBBP_LOWPOW_SSI_WORD1_H_dsp_tx_lowpow_ssi_word1_h_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD1_M_UNION
 结构说明  : LOWPOW_SSI_WORD1_M 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word1_m_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word1_m : 24; /* bit[0-23] : 上行低功耗控制字1(中增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD1_M_UNION;
#define WBBP_LOWPOW_SSI_WORD1_M_dsp_tx_lowpow_ssi_word1_m_START  (0)
#define WBBP_LOWPOW_SSI_WORD1_M_dsp_tx_lowpow_ssi_word1_m_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD1_L_UNION
 结构说明  : LOWPOW_SSI_WORD1_L 寄存器结构定义。地址偏移量:0x418，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word1_l_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word1_l : 24; /* bit[0-23] : 上行低功耗控制字1(低增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD1_L_UNION;
#define WBBP_LOWPOW_SSI_WORD1_L_dsp_tx_lowpow_ssi_word1_l_START  (0)
#define WBBP_LOWPOW_SSI_WORD1_L_dsp_tx_lowpow_ssi_word1_l_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD2_H_UNION
 结构说明  : LOWPOW_SSI_WORD2_H 寄存器结构定义。地址偏移量:0x41C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word2_h_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word2_h : 24; /* bit[0-23] : 上行低功耗控制字2(高增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD2_H_UNION;
#define WBBP_LOWPOW_SSI_WORD2_H_dsp_tx_lowpow_ssi_word2_h_START  (0)
#define WBBP_LOWPOW_SSI_WORD2_H_dsp_tx_lowpow_ssi_word2_h_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD2_M_UNION
 结构说明  : LOWPOW_SSI_WORD2_M 寄存器结构定义。地址偏移量:0x420，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word2_m_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word2_m : 24; /* bit[0-23] : 上行低功耗控制字2(中增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD2_M_UNION;
#define WBBP_LOWPOW_SSI_WORD2_M_dsp_tx_lowpow_ssi_word2_m_START  (0)
#define WBBP_LOWPOW_SSI_WORD2_M_dsp_tx_lowpow_ssi_word2_m_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD2_L_UNION
 结构说明  : LOWPOW_SSI_WORD2_L 寄存器结构定义。地址偏移量:0x424，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word2_l_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word2_l : 24; /* bit[0-23] : 上行低功耗控制字2(低增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD2_L_UNION;
#define WBBP_LOWPOW_SSI_WORD2_L_dsp_tx_lowpow_ssi_word2_l_START  (0)
#define WBBP_LOWPOW_SSI_WORD2_L_dsp_tx_lowpow_ssi_word2_l_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD3_H_UNION
 结构说明  : LOWPOW_SSI_WORD3_H 寄存器结构定义。地址偏移量:0x428，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word3_h_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word3_h : 24; /* bit[0-23] : 上行低功耗控制字3(高增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD3_H_UNION;
#define WBBP_LOWPOW_SSI_WORD3_H_dsp_tx_lowpow_ssi_word3_h_START  (0)
#define WBBP_LOWPOW_SSI_WORD3_H_dsp_tx_lowpow_ssi_word3_h_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD3_M_UNION
 结构说明  : LOWPOW_SSI_WORD3_M 寄存器结构定义。地址偏移量:0x42C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word3_m_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word3_m : 24; /* bit[0-23] : 上行低功耗控制字3(中增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD3_M_UNION;
#define WBBP_LOWPOW_SSI_WORD3_M_dsp_tx_lowpow_ssi_word3_m_START  (0)
#define WBBP_LOWPOW_SSI_WORD3_M_dsp_tx_lowpow_ssi_word3_m_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD3_L_UNION
 结构说明  : LOWPOW_SSI_WORD3_L 寄存器结构定义。地址偏移量:0x430，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word3_l_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word3_l : 24; /* bit[0-23] : 上行低功耗控制字3(低增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD3_L_UNION;
#define WBBP_LOWPOW_SSI_WORD3_L_dsp_tx_lowpow_ssi_word3_l_START  (0)
#define WBBP_LOWPOW_SSI_WORD3_L_dsp_tx_lowpow_ssi_word3_l_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD4_H_UNION
 结构说明  : LOWPOW_SSI_WORD4_H 寄存器结构定义。地址偏移量:0x434，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word4_h_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word4_h : 24; /* bit[0-23] : 上行低功耗控制字4(高增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD4_H_UNION;
#define WBBP_LOWPOW_SSI_WORD4_H_dsp_tx_lowpow_ssi_word4_h_START  (0)
#define WBBP_LOWPOW_SSI_WORD4_H_dsp_tx_lowpow_ssi_word4_h_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD4_M_UNION
 结构说明  : LOWPOW_SSI_WORD4_M 寄存器结构定义。地址偏移量:0x438，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word4_m_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word4_m : 24; /* bit[0-23] : 上行低功耗控制字4(中增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD4_M_UNION;
#define WBBP_LOWPOW_SSI_WORD4_M_dsp_tx_lowpow_ssi_word4_m_START  (0)
#define WBBP_LOWPOW_SSI_WORD4_M_dsp_tx_lowpow_ssi_word4_m_END    (23)


/*****************************************************************************
 结构名    : WBBP_LOWPOW_SSI_WORD4_L_UNION
 结构说明  : LOWPOW_SSI_WORD4_L 寄存器结构定义。地址偏移量:0x43C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      lowpow_ssi_word4_l_reg;
    struct
    {
        unsigned long  dsp_tx_lowpow_ssi_word4_l : 24; /* bit[0-23] : 上行低功耗控制字4(低增益)。 */
        unsigned long  reserved                  : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_LOWPOW_SSI_WORD4_L_UNION;
#define WBBP_LOWPOW_SSI_WORD4_L_dsp_tx_lowpow_ssi_word4_l_START  (0)
#define WBBP_LOWPOW_SSI_WORD4_L_dsp_tx_lowpow_ssi_word4_l_END    (23)


/*****************************************************************************
 结构名    : WBBP_MIPI_PAVBIAS1_2_CFG_UNION
 结构说明  : MIPI_PAVBIAS1_2_CFG 寄存器结构定义。地址偏移量:0x440，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_pavbias1_2_cfg_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_pavbias1_config_value : 9;  /* bit[0-8]  : EAGLE PA第一个VBIAS控制字强配值。 */
        unsigned long  reserved_0                        : 3;  /* bit[9-11] : 保留 */
        unsigned long  dsp_tx_mipi_pavbias1_config_en    : 1;  /* bit[12]   : EAGLE PA第一个VBIAS控制字强配使能。 */
        unsigned long  reserved_1                        : 3;  /* bit[13-15]: 保留 */
        unsigned long  dsp_tx_mipi_pavbias2_config_value : 9;  /* bit[16-24]: EAGLE PA第二个VBIAS控制字强配值。 */
        unsigned long  reserved_2                        : 3;  /* bit[25-27]: 保留 */
        unsigned long  dsp_tx_mipi_pavbias2_config_en    : 1;  /* bit[28]   : EAGLE PA第一个VBIAS控制字强配使能。 */
        unsigned long  reserved_3                        : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_MIPI_PAVBIAS1_2_CFG_UNION;
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias1_config_value_START  (0)
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias1_config_value_END    (8)
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias1_config_en_START     (12)
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias1_config_en_END       (12)
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias2_config_value_START  (16)
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias2_config_value_END    (24)
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias2_config_en_START     (28)
#define WBBP_MIPI_PAVBIAS1_2_CFG_dsp_tx_mipi_pavbias2_config_en_END       (28)


/*****************************************************************************
 结构名    : WBBP_MIPI_PAVBIAS3_CFG_UNION
 结构说明  : MIPI_PAVBIAS3_CFG 寄存器结构定义。地址偏移量:0x444，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_pavbias3_cfg_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_pavbias3_config_value : 9;  /* bit[0-8]  : EAGLE PA第三个VBIAS控制字强配值。 */
        unsigned long  reserved_0                        : 3;  /* bit[9-11] : 保留 */
        unsigned long  dsp_tx_mipi_pavbias3_config_en    : 1;  /* bit[12]   : EAGLE PA第一个VBIAS控制字强配使能。 */
        unsigned long  reserved_1                        : 3;  /* bit[13-15]: 保留 */
        unsigned long  dsp_pavbias1_mode_sel             : 1;  /* bit[16]   : PA VBIAS通道选择。
                                                                              0：表示MMMB PA，VBIAS通过SSI送给AUXDAC。
                                                                              1：表示EAGLE PA，第一个VBIAS控制字走MIPI。 */
        unsigned long  reserved_2                        : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_MIPI_PAVBIAS3_CFG_UNION;
#define WBBP_MIPI_PAVBIAS3_CFG_dsp_tx_mipi_pavbias3_config_value_START  (0)
#define WBBP_MIPI_PAVBIAS3_CFG_dsp_tx_mipi_pavbias3_config_value_END    (8)
#define WBBP_MIPI_PAVBIAS3_CFG_dsp_tx_mipi_pavbias3_config_en_START     (12)
#define WBBP_MIPI_PAVBIAS3_CFG_dsp_tx_mipi_pavbias3_config_en_END       (12)
#define WBBP_MIPI_PAVBIAS3_CFG_dsp_pavbias1_mode_sel_START              (16)
#define WBBP_MIPI_PAVBIAS3_CFG_dsp_pavbias1_mode_sel_END                (16)


/*****************************************************************************
 结构名    : WBBP_PAPD_REDUND1_UNION
 结构说明  : PAPD_REDUND1 寄存器结构定义。地址偏移量:0x448，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      papd_redund1_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_apt_config_value : 9;  /* bit[0-8] : EAGLE PA APT控制字强配值。 */
        unsigned long  wpapd_redund1                : 23; /* bit[9-31]: PAPD冗余寄存器1 */
    } reg;
} WBBP_PAPD_REDUND1_UNION;
#define WBBP_PAPD_REDUND1_dsp_tx_mipi_apt_config_value_START  (0)
#define WBBP_PAPD_REDUND1_dsp_tx_mipi_apt_config_value_END    (8)
#define WBBP_PAPD_REDUND1_wpapd_redund1_START                 (9)
#define WBBP_PAPD_REDUND1_wpapd_redund1_END                   (31)


/*****************************************************************************
 结构名    : WBBP_PAPD_REDUND2_UNION
 结构说明  : PAPD_REDUND2 寄存器结构定义。地址偏移量:0x44C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      papd_redund2_reg;
    struct
    {
        unsigned long  wpapd_redund2   : 25; /* bit[0-24] : PAPD冗余寄存器2 */
        unsigned long  vbias_ctrl_word : 7;  /* bit[25-31]: 普通PA APT控制字上报，无符号数。 */
    } reg;
} WBBP_PAPD_REDUND2_UNION;
#define WBBP_PAPD_REDUND2_wpapd_redund2_START    (0)
#define WBBP_PAPD_REDUND2_wpapd_redund2_END      (24)
#define WBBP_PAPD_REDUND2_vbias_ctrl_word_START  (25)
#define WBBP_PAPD_REDUND2_vbias_ctrl_word_END    (31)


/*****************************************************************************
 结构名    : WBBP_APT_STEP_MOD_SEL_UNION
 结构说明  : APT_STEP_MOD_SEL 寄存器结构定义。地址偏移量:0x454，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_step_mod_sel_reg;
    struct
    {
        unsigned long  dsp_apt_step_mode_sel : 1;  /* bit[0]   : apt步长模式选择
                                                                 1'b0:0.8step
                                                                 1'b1:0.4step */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_APT_STEP_MOD_SEL_UNION;
#define WBBP_APT_STEP_MOD_SEL_dsp_apt_step_mode_sel_START  (0)
#define WBBP_APT_STEP_MOD_SEL_dsp_apt_step_mode_sel_END    (0)


/*****************************************************************************
 结构名    : WBBP_MIPI_CH_EXCHANGE_UNION
 结构说明  : MIPI_CH_EXCHANGE 寄存器结构定义。地址偏移量:0x458，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_ch_exchange_reg;
    struct
    {
        unsigned long  dsp_tx_mipi_pavbias_trigger2_ch_exchange : 3;  /* bit[0-2]  : PA VBIAS TRIGGER2 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。 */
        unsigned long  reserved_0                               : 1;  /* bit[3]    : 保留 */
        unsigned long  dsp_tx_mipi_pavbias_trigger1_ch_exchange : 3;  /* bit[4-6]  : PA VBIAS TRIGGER1 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。 */
        unsigned long  reserved_1                               : 1;  /* bit[7]    : 保留 */
        unsigned long  dsp_tx_mipi_pavbias3_ch_exchange         : 3;  /* bit[8-10] : PA VBIAS3 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。 */
        unsigned long  reserved_2                               : 1;  /* bit[11]   : 保留 */
        unsigned long  dsp_tx_mipi_pavbias2_ch_exchange         : 3;  /* bit[12-14]: PA VBIAS2 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。 */
        unsigned long  reserved_3                               : 1;  /* bit[15]   : 保留 */
        unsigned long  dsp_tx_mipi_pavbias1_ch_exchange         : 3;  /* bit[16-18]: PA VBIAS1 MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。 */
        unsigned long  reserved_4                               : 1;  /* bit[19]   : 保留 */
        unsigned long  dsp_tx_mipi_apt_ch_exchange              : 3;  /* bit[20-22]: APT MIPI控制字发送通道指示，该参数配置值即为mipi的发送通道编号。 */
        unsigned long  reserved_5                               : 9;  /* bit[23-31]: 保留 */
    } reg;
} WBBP_MIPI_CH_EXCHANGE_UNION;
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias_trigger2_ch_exchange_START  (0)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias_trigger2_ch_exchange_END    (2)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias_trigger1_ch_exchange_START  (4)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias_trigger1_ch_exchange_END    (6)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias3_ch_exchange_START          (8)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias3_ch_exchange_END            (10)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias2_ch_exchange_START          (12)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias2_ch_exchange_END            (14)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias1_ch_exchange_START          (16)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_pavbias1_ch_exchange_END            (18)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_apt_ch_exchange_START               (20)
#define WBBP_MIPI_CH_EXCHANGE_dsp_tx_mipi_apt_ch_exchange_END                 (22)


/*****************************************************************************
 结构名    : WBBP_COM2ET_CTRL1_UNION
 结构说明  : COM2ET_CTRL1 寄存器结构定义。地址偏移量:0x45C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      com2et_ctrl1_reg;
    struct
    {
        unsigned long  dsp_post_gain            : 10; /* bit[0-9]  : 包络适配使用的增益 */
        unsigned long  reserved_0               : 2;  /* bit[10-11]: 保留 */
        unsigned long  dsp_post_offset          : 10; /* bit[12-21]: 包络适配使用的偏移 */
        unsigned long  reserved_1               : 2;  /* bit[22-23]: 保留 */
        unsigned long  dsp_post_gain_offset_ind : 1;  /* bit[24]   : dsp_post_gain和dsp_post_offset的有效性指示脉冲信号，高有效。 */
        unsigned long  dsp_post_cfg_en          : 1;  /* bit[25]   : 第三方ET包络增益和偏移强配使能信号。dsp_post_cfg_en==1'b0，选择根据APC Setting选择后的gain；dsp_post_cfg_en==1'b1，选择dsp_post_offset，dsp_post_gain */
        unsigned long  reserved_2               : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_COM2ET_CTRL1_UNION;
#define WBBP_COM2ET_CTRL1_dsp_post_gain_START             (0)
#define WBBP_COM2ET_CTRL1_dsp_post_gain_END               (9)
#define WBBP_COM2ET_CTRL1_dsp_post_offset_START           (12)
#define WBBP_COM2ET_CTRL1_dsp_post_offset_END             (21)
#define WBBP_COM2ET_CTRL1_dsp_post_gain_offset_ind_START  (24)
#define WBBP_COM2ET_CTRL1_dsp_post_gain_offset_ind_END    (24)
#define WBBP_COM2ET_CTRL1_dsp_post_cfg_en_START           (25)
#define WBBP_COM2ET_CTRL1_dsp_post_cfg_en_END             (25)


/*****************************************************************************
 结构名    : WBBP_COM2ET_CTRL2_UNION
 结构说明  : COM2ET_CTRL2 寄存器结构定义。地址偏移量:0x460，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      com2et_ctrl2_reg;
    struct
    {
        unsigned long  dsp_apt_et_mode_time : 11; /* bit[0-10] : 上行ET和APT模式切换提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_0           : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_et_tx_pwr_time   : 11; /* bit[16-26]: 上行ET理论发射功率提前上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved_1           : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_COM2ET_CTRL2_UNION;
#define WBBP_COM2ET_CTRL2_dsp_apt_et_mode_time_START  (0)
#define WBBP_COM2ET_CTRL2_dsp_apt_et_mode_time_END    (10)
#define WBBP_COM2ET_CTRL2_dsp_et_tx_pwr_time_START    (16)
#define WBBP_COM2ET_CTRL2_dsp_et_tx_pwr_time_END      (26)


/*****************************************************************************
 结构名    : WBBP_COM2ET_CTRL3_UNION
 结构说明  : COM2ET_CTRL3 寄存器结构定义。地址偏移量:0x464，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      com2et_ctrl3_reg;
    struct
    {
        unsigned long  dsp_et_mipi_apt_time : 11; /* bit[0-10] : 上行ET APT电压控制字上行时隙头生效时刻，单位为chip。 */
        unsigned long  reserved             : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_COM2ET_CTRL3_UNION;
#define WBBP_COM2ET_CTRL3_dsp_et_mipi_apt_time_START  (0)
#define WBBP_COM2ET_CTRL3_dsp_et_mipi_apt_time_END    (10)


/*****************************************************************************
 结构名    : WBBP_DPD_ACTIVE_TIME_UNION
 结构说明  : DPD_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x468，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dpd_active_time_reg;
    struct
    {
        unsigned long  dsp_tx_dpd_active_time : 10; /* bit[0-9]  : DPD */
        unsigned long  reserved               : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_DPD_ACTIVE_TIME_UNION;
#define WBBP_DPD_ACTIVE_TIME_dsp_tx_dpd_active_time_START  (0)
#define WBBP_DPD_ACTIVE_TIME_dsp_tx_dpd_active_time_END    (9)


/*****************************************************************************
 结构名    : WBBP_ET_DELAY_ACTIVE_TIME_UNION
 结构说明  : ET_DELAY_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x46C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      et_delay_active_time_reg;
    struct
    {
        unsigned long  dsp_et_delay_active_time : 11; /* bit[0-10] : ET */
        unsigned long  reserved                 : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_ET_DELAY_ACTIVE_TIME_UNION;
#define WBBP_ET_DELAY_ACTIVE_TIME_dsp_et_delay_active_time_START  (0)
#define WBBP_ET_DELAY_ACTIVE_TIME_dsp_et_delay_active_time_END    (10)


/*****************************************************************************
 结构名    : WBBP_TX_ETIF_SEL_UNION
 结构说明  : TX_ETIF_SEL 寄存器结构定义。地址偏移量:0x470，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_etif_sel_reg;
    struct
    {
        unsigned long  dsp_tx_etif_sel : 2;  /* bit[0-1] : ET数据接口选择信号，扩展位2bit。2'b0:选择CFR之后DPD之前的数据抽点到ET，与V8R1实现一致；2'b1:选择DPD后数据抽点到ET；2'b1X,选择DPC后数据抽点到ET */
        unsigned long  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_TX_ETIF_SEL_UNION;
#define WBBP_TX_ETIF_SEL_dsp_tx_etif_sel_START  (0)
#define WBBP_TX_ETIF_SEL_dsp_tx_etif_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_TX_RF_SSI_CH_SEL_UNION
 结构说明  : TX_RF_SSI_CH_SEL 寄存器结构定义。地址偏移量:0x474，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_rf_ssi_ch_sel_reg;
    struct
    {
        unsigned long  dsp_tx_rf_ssi_ch_sel : 2;  /* bit[0-1] : SSI发送通道指示 */
        unsigned long  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_TX_RF_SSI_CH_SEL_UNION;
#define WBBP_TX_RF_SSI_CH_SEL_dsp_tx_rf_ssi_ch_sel_START  (0)
#define WBBP_TX_RF_SSI_CH_SEL_dsp_tx_rf_ssi_ch_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_APT_PWR_MOD_SEL_UNION
 结构说明  : APT_PWR_MOD_SEL 寄存器结构定义。地址偏移量:0x478，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_pwr_mod_sel_reg;
    struct
    {
        unsigned long  dsp_apt_pwr_mod_sel : 1;  /* bit[0]   : APT功率模式选择：1'b0,理论发射功率；1'b1,实际发射功率 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_APT_PWR_MOD_SEL_UNION;
#define WBBP_APT_PWR_MOD_SEL_dsp_apt_pwr_mod_sel_START  (0)
#define WBBP_APT_PWR_MOD_SEL_dsp_apt_pwr_mod_sel_END    (0)


/*****************************************************************************
 结构名    : WBBP_FREQ_CNT_ACTIVE_TIME_UNION
 结构说明  : FREQ_CNT_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x47C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      freq_cnt_active_time_reg;
    struct
    {
        unsigned long  dsp_freq_cvt_active_time : 10; /* bit[0-9]  : 上变频提前上行时隙头生效时刻。单位 */
        unsigned long  reserved                 : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_FREQ_CNT_ACTIVE_TIME_UNION;
#define WBBP_FREQ_CNT_ACTIVE_TIME_dsp_freq_cvt_active_time_START  (0)
#define WBBP_FREQ_CNT_ACTIVE_TIME_dsp_freq_cvt_active_time_END    (9)


/*****************************************************************************
 结构名    : WBBP_ET_MODE_UNION
 结构说明  : ET_MODE 寄存器结构定义。地址偏移量:0x480，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      et_mode_reg;
    struct
    {
        unsigned long  dsp_et_mod : 1;  /* bit[0]   : ET模式选择，1’b0:第三方ET；1’b1:自研ET。默认为0 */
        unsigned long  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ET_MODE_UNION;
#define WBBP_ET_MODE_dsp_et_mod_START  (0)
#define WBBP_ET_MODE_dsp_et_mod_END    (0)


/*****************************************************************************
 结构名    : WBBP_GAIN_COMPENSATE_UNION
 结构说明  : GAIN_COMPENSATE 寄存器结构定义。地址偏移量:0x484，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain_compensate_reg;
    struct
    {
        unsigned long  dsp_gain1_com : 12; /* bit[0-11] : GAIN1对应温补、频补的线性增益值，无符号数 */
        unsigned long  reserved_0    : 4;  /* bit[12-15]: 保留 */
        unsigned long  dsp_gain2_com : 14; /* bit[16-29]: GAIN2对应温补、频补的线性增益值，无符号数 */
        unsigned long  reserved_1    : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_GAIN_COMPENSATE_UNION;
#define WBBP_GAIN_COMPENSATE_dsp_gain1_com_START  (0)
#define WBBP_GAIN_COMPENSATE_dsp_gain1_com_END    (11)
#define WBBP_GAIN_COMPENSATE_dsp_gain2_com_START  (16)
#define WBBP_GAIN_COMPENSATE_dsp_gain2_com_END    (29)


/*****************************************************************************
 结构名    : WBBP_GAIN1_CALIBRATION0_1_UNION
 结构说明  : GAIN1_CALIBRATION0_1 寄存器结构定义。地址偏移量:0x488，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain1_calibration0_1_reg;
    struct
    {
        unsigned long  dsp_gain1_cali0 : 10; /* bit[0-9]  : GAIN1对应的子表0线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain1_cali1 : 10; /* bit[16-25]: GAIN1对应的子表1线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN1_CALIBRATION0_1_UNION;
#define WBBP_GAIN1_CALIBRATION0_1_dsp_gain1_cali0_START  (0)
#define WBBP_GAIN1_CALIBRATION0_1_dsp_gain1_cali0_END    (9)
#define WBBP_GAIN1_CALIBRATION0_1_dsp_gain1_cali1_START  (16)
#define WBBP_GAIN1_CALIBRATION0_1_dsp_gain1_cali1_END    (25)


/*****************************************************************************
 结构名    : WBBP_GAIN1_CALIBRATION2_3_UNION
 结构说明  : GAIN1_CALIBRATION2_3 寄存器结构定义。地址偏移量:0x48C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain1_calibration2_3_reg;
    struct
    {
        unsigned long  dsp_gain1_cali2 : 10; /* bit[0-9]  : GAIN1对应的子表2线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain1_cali3 : 10; /* bit[16-25]: GAIN1对应的子表3线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN1_CALIBRATION2_3_UNION;
#define WBBP_GAIN1_CALIBRATION2_3_dsp_gain1_cali2_START  (0)
#define WBBP_GAIN1_CALIBRATION2_3_dsp_gain1_cali2_END    (9)
#define WBBP_GAIN1_CALIBRATION2_3_dsp_gain1_cali3_START  (16)
#define WBBP_GAIN1_CALIBRATION2_3_dsp_gain1_cali3_END    (25)


/*****************************************************************************
 结构名    : WBBP_GAIN1_CALIBRATION4_5_UNION
 结构说明  : GAIN1_CALIBRATION4_5 寄存器结构定义。地址偏移量:0x490，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain1_calibration4_5_reg;
    struct
    {
        unsigned long  dsp_gain1_cali4 : 10; /* bit[0-9]  : GAIN1对应的子表4线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain1_cali5 : 10; /* bit[16-25]: GAIN1对应的子表5线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN1_CALIBRATION4_5_UNION;
#define WBBP_GAIN1_CALIBRATION4_5_dsp_gain1_cali4_START  (0)
#define WBBP_GAIN1_CALIBRATION4_5_dsp_gain1_cali4_END    (9)
#define WBBP_GAIN1_CALIBRATION4_5_dsp_gain1_cali5_START  (16)
#define WBBP_GAIN1_CALIBRATION4_5_dsp_gain1_cali5_END    (25)


/*****************************************************************************
 结构名    : WBBP_GAIN1_CALIBRATION6_7_UNION
 结构说明  : GAIN1_CALIBRATION6_7 寄存器结构定义。地址偏移量:0x494，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain1_calibration6_7_reg;
    struct
    {
        unsigned long  dsp_gain1_cali6 : 10; /* bit[0-9]  : GAIN1对应的子表6线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain1_cali7 : 10; /* bit[16-25]: GAIN1对应的子表7线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN1_CALIBRATION6_7_UNION;
#define WBBP_GAIN1_CALIBRATION6_7_dsp_gain1_cali6_START  (0)
#define WBBP_GAIN1_CALIBRATION6_7_dsp_gain1_cali6_END    (9)
#define WBBP_GAIN1_CALIBRATION6_7_dsp_gain1_cali7_START  (16)
#define WBBP_GAIN1_CALIBRATION6_7_dsp_gain1_cali7_END    (25)


/*****************************************************************************
 结构名    : WBBP_GAIN2_CALIBRATION0_1_UNION
 结构说明  : GAIN2_CALIBRATION0_1 寄存器结构定义。地址偏移量:0x498，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain2_calibration0_1_reg;
    struct
    {
        unsigned long  dsp_gain2_cali0 : 10; /* bit[0-9]  : GAIN2对应的子表0线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain2_cali1 : 10; /* bit[16-25]: GAIN2对应的子表1线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN2_CALIBRATION0_1_UNION;
#define WBBP_GAIN2_CALIBRATION0_1_dsp_gain2_cali0_START  (0)
#define WBBP_GAIN2_CALIBRATION0_1_dsp_gain2_cali0_END    (9)
#define WBBP_GAIN2_CALIBRATION0_1_dsp_gain2_cali1_START  (16)
#define WBBP_GAIN2_CALIBRATION0_1_dsp_gain2_cali1_END    (25)


/*****************************************************************************
 结构名    : WBBP_GAIN2_CALIBRATION2_3_UNION
 结构说明  : GAIN2_CALIBRATION2_3 寄存器结构定义。地址偏移量:0x49C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain2_calibration2_3_reg;
    struct
    {
        unsigned long  dsp_gain2_cali2 : 10; /* bit[0-9]  : GAIN2对应的子表2线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain2_cali3 : 10; /* bit[16-25]: GAIN2对应的子表3线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN2_CALIBRATION2_3_UNION;
#define WBBP_GAIN2_CALIBRATION2_3_dsp_gain2_cali2_START  (0)
#define WBBP_GAIN2_CALIBRATION2_3_dsp_gain2_cali2_END    (9)
#define WBBP_GAIN2_CALIBRATION2_3_dsp_gain2_cali3_START  (16)
#define WBBP_GAIN2_CALIBRATION2_3_dsp_gain2_cali3_END    (25)


/*****************************************************************************
 结构名    : WBBP_GAIN2_CALIBRATION4_5_UNION
 结构说明  : GAIN2_CALIBRATION4_5 寄存器结构定义。地址偏移量:0x4A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain2_calibration4_5_reg;
    struct
    {
        unsigned long  dsp_gain2_cali4 : 10; /* bit[0-9]  : GAIN2对应的子表4线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain2_cali5 : 10; /* bit[16-25]: GAIN2对应的子表5线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN2_CALIBRATION4_5_UNION;
#define WBBP_GAIN2_CALIBRATION4_5_dsp_gain2_cali4_START  (0)
#define WBBP_GAIN2_CALIBRATION4_5_dsp_gain2_cali4_END    (9)
#define WBBP_GAIN2_CALIBRATION4_5_dsp_gain2_cali5_START  (16)
#define WBBP_GAIN2_CALIBRATION4_5_dsp_gain2_cali5_END    (25)


/*****************************************************************************
 结构名    : WBBP_GAIN2_CALIBRATION6_7_UNION
 结构说明  : GAIN2_CALIBRATION6_7 寄存器结构定义。地址偏移量:0x4A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gain2_calibration6_7_reg;
    struct
    {
        unsigned long  dsp_gain2_cali6 : 10; /* bit[0-9]  : GAIN2对应的子表6线性增益值，无符号数 */
        unsigned long  reserved_0      : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_gain2_cali7 : 10; /* bit[16-25]: GAIN2对应的子表7线性增益值，无符号数 */
        unsigned long  reserved_1      : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_GAIN2_CALIBRATION6_7_UNION;
#define WBBP_GAIN2_CALIBRATION6_7_dsp_gain2_cali6_START  (0)
#define WBBP_GAIN2_CALIBRATION6_7_dsp_gain2_cali6_END    (9)
#define WBBP_GAIN2_CALIBRATION6_7_dsp_gain2_cali7_START  (16)
#define WBBP_GAIN2_CALIBRATION6_7_dsp_gain2_cali7_END    (25)


/*****************************************************************************
 结构名    : WBBP_ET_TEMP_COMP_UNION
 结构说明  : ET_TEMP_COMP 寄存器结构定义。地址偏移量:0x4A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      et_temp_comp_reg;
    struct
    {
        unsigned long  dsp_tem_comp : 11; /* bit[0-10] : 第三方ET温补和频补，功率的db值，有符号数 */
        unsigned long  reserved     : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_ET_TEMP_COMP_UNION;
#define WBBP_ET_TEMP_COMP_dsp_tem_comp_START  (0)
#define WBBP_ET_TEMP_COMP_dsp_tem_comp_END    (10)


/*****************************************************************************
 结构名    : WBBP_ET_GAIN_ROUND_SEL_UNION
 结构说明  : ET_GAIN_ROUND_SEL 寄存器结构定义。地址偏移量:0x4AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      et_gain_round_sel_reg;
    struct
    {
        unsigned long  dsp_gain1_round_sel : 2;  /* bit[0-1] : GAIN1四舍五入右移bit选择：2'b0:2bit, 2'b1:3bit, 2'b1X:4bit */
        unsigned long  reserved_0          : 2;  /* bit[2-3] : 保留 */
        unsigned long  dsp_gain2_round_sel : 2;  /* bit[4-5] : GAIN2四舍五入右移bit选择：2'b0:2bit, 2'b1:3bit, 2'b1X:4bit */
        unsigned long  reserved_1          : 26; /* bit[6-31]: 保留 */
    } reg;
} WBBP_ET_GAIN_ROUND_SEL_UNION;
#define WBBP_ET_GAIN_ROUND_SEL_dsp_gain1_round_sel_START  (0)
#define WBBP_ET_GAIN_ROUND_SEL_dsp_gain1_round_sel_END    (1)
#define WBBP_ET_GAIN_ROUND_SEL_dsp_gain2_round_sel_START  (4)
#define WBBP_ET_GAIN_ROUND_SEL_dsp_gain2_round_sel_END    (5)


/*****************************************************************************
 结构名    : WBBP_APT_ET_MODE_FORCE_UNION
 结构说明  : APT_ET_MODE_FORCE 寄存器结构定义。地址偏移量:0x4B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_et_mode_force_reg;
    struct
    {
        unsigned long  dsp_apt_et_mod_sel : 2;  /* bit[0-1] : 2'b0，由bbp根据PA档位自动控制；2’b1,软件强制为APT模式；2'b1X,软件强制为ET模式 */
        unsigned long  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_APT_ET_MODE_FORCE_UNION;
#define WBBP_APT_ET_MODE_FORCE_dsp_apt_et_mod_sel_START  (0)
#define WBBP_APT_ET_MODE_FORCE_dsp_apt_et_mod_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_ET_APT_WORD_EN_UNION
 结构说明  : ET_APT_WORD_EN 寄存器结构定义。地址偏移量:0x4B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      et_apt_word_en_reg;
    struct
    {
        unsigned long  dsp_et_apt_word_en : 1;  /* bit[0]   : 1'b0，bbp根据当前是否处于apt模式，确认发送apt控制字；1'b1，代表无论apt或et模式，apt控制字都发送，兼容v8 */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ET_APT_WORD_EN_UNION;
#define WBBP_ET_APT_WORD_EN_dsp_et_apt_word_en_START  (0)
#define WBBP_ET_APT_WORD_EN_dsp_et_apt_word_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_PA_THRESHOLD_UPDATE_READY_UNION
 结构说明  : PA_THRESHOLD_UPDATE_READY 寄存器结构定义。地址偏移量:0x4B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      pa_threshold_update_ready_reg;
    struct
    {
        unsigned long  dsp_pa_ud_ready : 1;  /* bit[0]   : PA GAIN切换门限更新指示，接口中先完成PA GAIN切换门限的配置，配置全部完成后配置dsp_pa_ud_ready，通知BBP配置结束，逻辑自清零信号 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_PA_THRESHOLD_UPDATE_READY_UNION;
#define WBBP_PA_THRESHOLD_UPDATE_READY_dsp_pa_ud_ready_START  (0)
#define WBBP_PA_THRESHOLD_UPDATE_READY_dsp_pa_ud_ready_END    (0)


/*****************************************************************************
 结构名    : WBBP_DB2L_ROM_OFFSET_UNION
 结构说明  : DB2L_ROM_OFFSET 寄存器结构定义。地址偏移量:0x4BC，初值:0x00001E1E，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      db2l_rom_offset_reg;
    struct
    {
        unsigned long  dsp_dpc_offset : 7;  /* bit[0-6]  : DPC db转线性值rom表地址偏移值，无符号数 */
        unsigned long  reserved_0     : 1;  /* bit[7]    : 保留 */
        unsigned long  dsp_dpd_offset : 7;  /* bit[8-14] : DPD db转线性值rom表地址偏移值，无符号数 */
        unsigned long  reserved_1     : 17; /* bit[15-31]: 保留 */
    } reg;
} WBBP_DB2L_ROM_OFFSET_UNION;
#define WBBP_DB2L_ROM_OFFSET_dsp_dpc_offset_START  (0)
#define WBBP_DB2L_ROM_OFFSET_dsp_dpc_offset_END    (6)
#define WBBP_DB2L_ROM_OFFSET_dsp_dpd_offset_START  (8)
#define WBBP_DB2L_ROM_OFFSET_dsp_dpd_offset_END    (14)


/*****************************************************************************
 结构名    : WBBP_ET_GAIN_ACTIVE_TIME_UNION
 结构说明  : ET_GAIN_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x4C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      et_gain_active_time_reg;
    struct
    {
        unsigned long  dsp_gain_active_time : 10; /* bit[0-9]  : ET Gain1/Gain2 */
        unsigned long  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_ET_GAIN_ACTIVE_TIME_UNION;
#define WBBP_ET_GAIN_ACTIVE_TIME_dsp_gain_active_time_START  (0)
#define WBBP_ET_GAIN_ACTIVE_TIME_dsp_gain_active_time_END    (9)


/*****************************************************************************
 结构名    : WBBP_DBB_DB2L_ROM_THRESHOLD_UNION
 结构说明  : DBB_DB2L_ROM_THRESHOLD 寄存器结构定义。地址偏移量:0x4C4，初值:0x00001478，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbb_db2l_rom_threshold_reg;
    struct
    {
        unsigned long  dsp_dbb_rom_up_thr  : 7;  /* bit[0-6]  : DPC db转线性值rom表地址上限，范围0~127，默认为120，兼容v8无符号数 */
        unsigned long  reserved_0          : 1;  /* bit[7]    : 保留 */
        unsigned long  dsp_dbb_rom_low_thr : 7;  /* bit[8-14] : DPC db转线性值rom表地址下限，范围0~127，默认为20，兼容v8，无符号数 */
        unsigned long  reserved_1          : 17; /* bit[15-31]: 保留 */
    } reg;
} WBBP_DBB_DB2L_ROM_THRESHOLD_UNION;
#define WBBP_DBB_DB2L_ROM_THRESHOLD_dsp_dbb_rom_up_thr_START   (0)
#define WBBP_DBB_DB2L_ROM_THRESHOLD_dsp_dbb_rom_up_thr_END     (6)
#define WBBP_DBB_DB2L_ROM_THRESHOLD_dsp_dbb_rom_low_thr_START  (8)
#define WBBP_DBB_DB2L_ROM_THRESHOLD_dsp_dbb_rom_low_thr_END    (14)


/*****************************************************************************
 结构名    : WBBP_ET_GAIN_CFG_EN_UNION
 结构说明  : ET_GAIN_CFG_EN 寄存器结构定义。地址偏移量:0x4C8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      et_gain_cfg_en_reg;
    struct
    {
        unsigned long  dsp_et_gain_cfg_en : 1;  /* bit[0]   : ET Gain1/Gain2 */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ET_GAIN_CFG_EN_UNION;
#define WBBP_ET_GAIN_CFG_EN_dsp_et_gain_cfg_en_START  (0)
#define WBBP_ET_GAIN_CFG_EN_dsp_et_gain_cfg_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_DBB_ATTEN_VALUE_RPT_UNION
 结构说明  : DBB_ATTEN_VALUE_RPT 寄存器结构定义。地址偏移量:0x4CC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbb_atten_value_rpt_reg;
    struct
    {
        unsigned long  dbb_table_value_rpt   : 8;  /* bit[0-7]  : 8比特数字功率回退值上报 */
        unsigned long  div_residue_latch_rpt : 4;  /* bit[8-11] : 除10后余数部分数字功率回退值上报 */
        unsigned long  d_mpr_out_sav_rpt     : 6;  /* bit[12-17]: 数字 MPR回退值上报 */
        unsigned long  reserved              : 14; /* bit[18-31]: 保留 */
    } reg;
} WBBP_DBB_ATTEN_VALUE_RPT_UNION;
#define WBBP_DBB_ATTEN_VALUE_RPT_dbb_table_value_rpt_START    (0)
#define WBBP_DBB_ATTEN_VALUE_RPT_dbb_table_value_rpt_END      (7)
#define WBBP_DBB_ATTEN_VALUE_RPT_div_residue_latch_rpt_START  (8)
#define WBBP_DBB_ATTEN_VALUE_RPT_div_residue_latch_rpt_END    (11)
#define WBBP_DBB_ATTEN_VALUE_RPT_d_mpr_out_sav_rpt_START      (12)
#define WBBP_DBB_ATTEN_VALUE_RPT_d_mpr_out_sav_rpt_END        (17)


/*****************************************************************************
 结构名    : WBBP_MPR_OUT_RPT_UNION
 结构说明  : MPR_OUT_RPT 寄存器结构定义。地址偏移量:0x4D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mpr_out_rpt_reg;
    struct
    {
        unsigned long  mpr_out_pd_rpt  : 6;  /* bit[0-5]  : PD MPR回退值上报 */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : 保留 */
        unsigned long  apt_mpr_out_rpt : 6;  /* bit[8-13] : APT MPR回退值上报 */
        unsigned long  reserved_1      : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_MPR_OUT_RPT_UNION;
#define WBBP_MPR_OUT_RPT_mpr_out_pd_rpt_START   (0)
#define WBBP_MPR_OUT_RPT_mpr_out_pd_rpt_END     (5)
#define WBBP_MPR_OUT_RPT_apt_mpr_out_rpt_START  (8)
#define WBBP_MPR_OUT_RPT_apt_mpr_out_rpt_END    (13)


/*****************************************************************************
 结构名    : WBBP_COM2ET_CTRL_RPT1_UNION
 结构说明  : COM2ET_CTRL_RPT1 寄存器结构定义。地址偏移量:0x4D4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      com2et_ctrl_rpt1_reg;
    struct
    {
        unsigned long  com2et_apt_pa_vcc_rpt  : 10; /* bit[0-9]  : 输出给ET模块的的APT控制字 */
        unsigned long  reserved_0             : 2;  /* bit[10-11]: 保留 */
        unsigned long  com2et_w_pa_mode_rpt   : 2;  /* bit[12-13]: 输出给ET模块的的PA档位控制字 */
        unsigned long  reserved_1             : 2;  /* bit[14-15]: 保留 */
        unsigned long  com2et_tx_power_db_rpt : 11; /* bit[16-26]: 输出给ET模块的的绝对发射功率 */
        unsigned long  reserved_2             : 1;  /* bit[27]   : 保留 */
        unsigned long  com2et_apt_et_mode_rpt : 1;  /* bit[28]   : 输出给ET模块的的APT、ET模式选择信号 */
        unsigned long  reserved_3             : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_COM2ET_CTRL_RPT1_UNION;
#define WBBP_COM2ET_CTRL_RPT1_com2et_apt_pa_vcc_rpt_START   (0)
#define WBBP_COM2ET_CTRL_RPT1_com2et_apt_pa_vcc_rpt_END     (9)
#define WBBP_COM2ET_CTRL_RPT1_com2et_w_pa_mode_rpt_START    (12)
#define WBBP_COM2ET_CTRL_RPT1_com2et_w_pa_mode_rpt_END      (13)
#define WBBP_COM2ET_CTRL_RPT1_com2et_tx_power_db_rpt_START  (16)
#define WBBP_COM2ET_CTRL_RPT1_com2et_tx_power_db_rpt_END    (26)
#define WBBP_COM2ET_CTRL_RPT1_com2et_apt_et_mode_rpt_START  (28)
#define WBBP_COM2ET_CTRL_RPT1_com2et_apt_et_mode_rpt_END    (28)


/*****************************************************************************
 结构名    : WBBP_COM2ET_CTRL_RPT2_UNION
 结构说明  : COM2ET_CTRL_RPT2 寄存器结构定义。地址偏移量:0x4D8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      com2et_ctrl_rpt2_reg;
    struct
    {
        unsigned long  com2et_post_offset_rpt : 10; /* bit[0-9]  : 输出给ET模块的包络适配使用的偏移 */
        unsigned long  reserved_0             : 2;  /* bit[10-11]: 保留 */
        unsigned long  com2et_post_gain_rpt   : 10; /* bit[12-21]: 输出给ET模块的包络适配使用的增益 */
        unsigned long  reserved_1             : 10; /* bit[22-31]: 保留 */
    } reg;
} WBBP_COM2ET_CTRL_RPT2_UNION;
#define WBBP_COM2ET_CTRL_RPT2_com2et_post_offset_rpt_START  (0)
#define WBBP_COM2ET_CTRL_RPT2_com2et_post_offset_rpt_END    (9)
#define WBBP_COM2ET_CTRL_RPT2_com2et_post_gain_rpt_START    (12)
#define WBBP_COM2ET_CTRL_RPT2_com2et_post_gain_rpt_END      (21)


/***======================================================================***
                     (6/10) register_define_w_pd_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_PD_RAM_UNION
 结构说明  : PD_RAM 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: PD功率表
*****************************************************************************/
typedef union
{
    unsigned long      pd_ram_reg;
    struct
    {
        unsigned long  pd_ram_data : 10; /* bit[0-9]  : 存储180个功率对应的电压线性值，10比特无符号数，地址单位0.1dBm. */
        unsigned long  reserved    : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_PD_RAM_UNION;
#define WBBP_PD_RAM_pd_ram_data_START  (0)
#define WBBP_PD_RAM_pd_ram_data_END    (9)


/*****************************************************************************
 结构名    : WBBP_DPD_RAM2_UNION
 结构说明  : DPD_RAM2 寄存器结构定义。地址偏移量:0xAD0，初值:0x00000000，宽度:32
 寄存器说明: DPD补偿表
*****************************************************************************/
typedef union
{
    unsigned long      dpd_ram2_reg;
    struct
    {
        unsigned long  dpd_comp_i : 12; /* bit[0-11] : DPD补偿I路系数 */
        unsigned long  dpd_comp_q : 12; /* bit[12-23]: DPD补偿Q路系数 */
        unsigned long  reserved   : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_DPD_RAM2_UNION;
#define WBBP_DPD_RAM2_dpd_comp_i_START  (0)
#define WBBP_DPD_RAM2_dpd_comp_i_END    (11)
#define WBBP_DPD_RAM2_dpd_comp_q_START  (12)
#define WBBP_DPD_RAM2_dpd_comp_q_END    (23)


/***======================================================================***
                     (7/10) register_define_ulfe_wt_share
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_ULFE_CKG_EN_UNION
 结构说明  : ULFE_CKG_EN 寄存器结构定义。地址偏移量:0x000，初值:0x0007FFFF，宽度:32
 寄存器说明: 门控时钟
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_ckg_en_reg;
    struct
    {
        unsigned long  ulfe_ckg_en : 19; /* bit[0-18] : ULFE自动门控功能使能；1表示对应子模块自动门控功能打开，0表示对应子模块自动门控功能关闭
                                                        bit[0]: 主载波rrc模块自动门控功能使能
                                                        bit[1]: W、C 削波延迟子模块自动门控功能使能
                                                        bit[2]: W、C和TDS FIR/第一级削波子模块自动门控使能
                                                        bit[3]: W和C 第二级削波子模块自动门控使能
                                                        bit[4]: power comp模块自动门控使能
                                                        bit[5]: tx phase comp模块自动门控使能
                                                        bit[6]:txiq 预畸变模块自动门控时钟使能
                                                        bit[7]:txiq 相关计算和单频信号产生模块自动门控时钟使能
                                                        bit[8]: dbg模块自动门控时钟使能
                                                        bit[9]:主载波上变频门控时钟使能
                                                        bit[10]:辅载波rrc和上变频模块门控使能
                                                        bit[11]:sc_cal模块门控使能
                                                        bit[12]:频偏校正模块门控使能
                                                        bit[13]:fe_nco模块门控使能
                                                        bit[14]:W base_cnt_abb模块门控使能；TDS base_cnt_dbb模块门控使能
                                                        bit[15]:DPD模块门控使能
                                                        bit[16]:dc_nco模块门控使能
                                                        bit[17]:dc_add模块门控使能
                                                        bit[18]:单音模块门控使能 */
        unsigned long  reserved    : 13; /* bit[19-31]: 保留 */
    } reg;
} WBBP_ULFE_CKG_EN_UNION;
#define WBBP_ULFE_CKG_EN_ulfe_ckg_en_START  (0)
#define WBBP_ULFE_CKG_EN_ulfe_ckg_en_END    (18)


/*****************************************************************************
 结构名    : WBBP_ULFE_U_TDS_MOD_SEL_UNION
 结构说明  : ULFE_U_TDS_MOD_SEL 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_u_tds_mod_sel_reg;
    struct
    {
        unsigned long  ulfe_mode_sel : 2;  /* bit[0-1] : 2'b0：选择W
                                                         2'b1：选择TDS
                                                         2'b10:1X
                                                         2'b11：EVDO */
        unsigned long  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_ULFE_U_TDS_MOD_SEL_UNION;
#define WBBP_ULFE_U_TDS_MOD_SEL_ulfe_mode_sel_START  (0)
#define WBBP_ULFE_U_TDS_MOD_SEL_ulfe_mode_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_ULFE_FUNC_EN_UNION
 结构说明  : ULFE_FUNC_EN 寄存器结构定义。地址偏移量:0x010，初值:0x00000110，宽度:32
 寄存器说明: ULFE内部模块功能开关寄存器
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_func_en_reg;
    struct
    {
        unsigned long  dsp_wt_tx_phase_comp_en : 1;  /* bit[0]    : tx phase comp使能信号
                                                                    1'b0:W、TDS和C不使能；
                                                                    1'b1:W、TDS和C使能。 */
        unsigned long  reserved_0              : 3;  /* bit[1-3]  : 保留 */
        unsigned long  dsp_power_comp_en       : 1;  /* bit[4]    : power comp使能信号
                                                                    1'b0:W、TDS和C不使能，旁路
                                                                    1'b1:W、TDS和C使能 */
        unsigned long  reserved_1              : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dsp_txiq_preabe_en      : 1;  /* bit[8]    : txiq 预畸变使能信号
                                                                    1'b0:W、TDS和C不使能，旁路
                                                                    1'b1:W、TDS和C使能 */
        unsigned long  reserved_2              : 3;  /* bit[9-11] : 保留 */
        unsigned long  dsp_tds_dbg_en          : 1;  /* bit[12]   : tds_dbg使能信号
                                                                    1'b0:W、C不使能，TDS使能；
                                                                    1'b1:W、C使能，TDS不使能。 */
        unsigned long  reserved_3              : 2;  /* bit[13-14]: 保留 */
        unsigned long  dsp_freq_error_en       : 1;  /* bit[15]   : fe_freq_error模块使能信号
                                                                    1'b0：W、TDS和C不使能
                                                                    1'b1：W、TDS和C使能 */
        unsigned long  dsp_sc_cal_en           : 1;  /* bit[16]   : fe_sc_cal模块使能信号
                                                                    1'b0：W、TDS和C不使能
                                                                    1'b1：W、TDS和C使能 */
        unsigned long  dsp_nco_en              : 1;  /* bit[17]   : fe_nco模块使能信号
                                                                    1'b0：W、TDS和C不使能
                                                                    1'b1：W、TDS和C使能
                                                                    TDS为0 */
        unsigned long  dsp_base_cnt_abb_en     : 1;  /* bit[18]   : base_cnt_abb模块使能信号
                                                                    1'b0：W、TDS和C不使能
                                                                    1'b1：W、TDS和C使能 */
        unsigned long  dsp_w_dpd_en            : 1;  /* bit[19]   : DPD */
        unsigned long  dsp_dc_nco_en           : 1;  /* bit[20]   : DCUPANCO */
        unsigned long  reserved_4              : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_ULFE_FUNC_EN_UNION;
#define WBBP_ULFE_FUNC_EN_dsp_wt_tx_phase_comp_en_START  (0)
#define WBBP_ULFE_FUNC_EN_dsp_wt_tx_phase_comp_en_END    (0)
#define WBBP_ULFE_FUNC_EN_dsp_power_comp_en_START        (4)
#define WBBP_ULFE_FUNC_EN_dsp_power_comp_en_END          (4)
#define WBBP_ULFE_FUNC_EN_dsp_txiq_preabe_en_START       (8)
#define WBBP_ULFE_FUNC_EN_dsp_txiq_preabe_en_END         (8)
#define WBBP_ULFE_FUNC_EN_dsp_tds_dbg_en_START           (12)
#define WBBP_ULFE_FUNC_EN_dsp_tds_dbg_en_END             (12)
#define WBBP_ULFE_FUNC_EN_dsp_freq_error_en_START        (15)
#define WBBP_ULFE_FUNC_EN_dsp_freq_error_en_END          (15)
#define WBBP_ULFE_FUNC_EN_dsp_sc_cal_en_START            (16)
#define WBBP_ULFE_FUNC_EN_dsp_sc_cal_en_END              (16)
#define WBBP_ULFE_FUNC_EN_dsp_nco_en_START               (17)
#define WBBP_ULFE_FUNC_EN_dsp_nco_en_END                 (17)
#define WBBP_ULFE_FUNC_EN_dsp_base_cnt_abb_en_START      (18)
#define WBBP_ULFE_FUNC_EN_dsp_base_cnt_abb_en_END        (18)
#define WBBP_ULFE_FUNC_EN_dsp_w_dpd_en_START             (19)
#define WBBP_ULFE_FUNC_EN_dsp_w_dpd_en_END               (19)
#define WBBP_ULFE_FUNC_EN_dsp_dc_nco_en_START            (20)
#define WBBP_ULFE_FUNC_EN_dsp_dc_nco_en_END              (20)


/*****************************************************************************
 结构名    : WBBP_TX_MODE_REG_UNION
 结构说明  : TX_MODE_REG 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 上行发送模式
*****************************************************************************/
typedef union
{
    unsigned long      tx_mode_reg_reg;
    struct
    {
        unsigned long  wt_pc_tx_mode : 2;  /* bit[0-1] : W、C和TDS上行TX模式控制：
                                                         00：正常工作
                                                         01：测试波形模式，连续循环发送测试波形数据
                                                         1x：保留 */
        unsigned long  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_TX_MODE_REG_UNION;
#define WBBP_TX_MODE_REG_wt_pc_tx_mode_START  (0)
#define WBBP_TX_MODE_REG_wt_pc_tx_mode_END    (1)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_NUM_REG_UNION
 结构说明  : TX_SEND_NUM_REG 寄存器结构定义。地址偏移量:0x018，初值:0x00000020，宽度:32
 寄存器说明: 数据发送参数寄存器
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_num_reg_reg;
    struct
    {
        unsigned long  wt_send_num   : 6;  /* bit[0-5]  : W、C和TDS测试波形模式下的波形信号，发送样点数据数目，典型值为16，取值范围1~32 */
        unsigned long  reserved_0    : 2;  /* bit[6-7]  : 保留 */
        unsigned long  wt_delt_index : 2;  /* bit[8-9]  : W、C和TDS测试波形模式下发送以下样点数据的间隔：
                                                          0：间隔为1（默认值 ）；
                                                          1：间隔为2；
                                                          2：间隔为3；
                                                          3：间隔为4； */
        unsigned long  reserved_1    : 22; /* bit[10-31]: 保留 */
    } reg;
} WBBP_TX_SEND_NUM_REG_UNION;
#define WBBP_TX_SEND_NUM_REG_wt_send_num_START    (0)
#define WBBP_TX_SEND_NUM_REG_wt_send_num_END      (5)
#define WBBP_TX_SEND_NUM_REG_wt_delt_index_START  (8)
#define WBBP_TX_SEND_NUM_REG_wt_delt_index_END    (9)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA0_UNION
 结构说明  : TX_SEND_DATA0 寄存器结构定义。地址偏移量:0x01C，初值:0x00400000，宽度:32
 寄存器说明: 测试发送数据0
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data0_reg;
    struct
    {
        unsigned long  wt_send_data_i0 : 12; /* bit[0-11] : W、C和TDS测试波形模式下，第0个数据实部 */
        unsigned long  wt_send_data_q0 : 12; /* bit[12-23]: W、C和TDS测试波形模式下，第0个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA0_UNION;
#define WBBP_TX_SEND_DATA0_wt_send_data_i0_START  (0)
#define WBBP_TX_SEND_DATA0_wt_send_data_i0_END    (11)
#define WBBP_TX_SEND_DATA0_wt_send_data_q0_START  (12)
#define WBBP_TX_SEND_DATA0_wt_send_data_q0_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA1_UNION
 结构说明  : TX_SEND_DATA1 寄存器结构定义。地址偏移量:0x020，初值:0x003EC0C7，宽度:32
 寄存器说明: 测试发送数据1
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data1_reg;
    struct
    {
        unsigned long  wt_send_data_i1 : 12; /* bit[0-11] : 测试波形模式下，第1个数据实部 */
        unsigned long  wt_send_data_q1 : 12; /* bit[12-23]: 测试波形模式下，第1个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA1_UNION;
#define WBBP_TX_SEND_DATA1_wt_send_data_i1_START  (0)
#define WBBP_TX_SEND_DATA1_wt_send_data_i1_END    (11)
#define WBBP_TX_SEND_DATA1_wt_send_data_q1_START  (12)
#define WBBP_TX_SEND_DATA1_wt_send_data_q1_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA2_UNION
 结构说明  : TX_SEND_DATA2 寄存器结构定义。地址偏移量:0x024，初值:0x003B2187，宽度:32
 寄存器说明: 测试发送数据2
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data2_reg;
    struct
    {
        unsigned long  wt_send_data_i2 : 12; /* bit[0-11] : 测试波形模式下，第2个数据实部 */
        unsigned long  wt_send_data_q2 : 12; /* bit[12-23]: 测试波形模式下，第2个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA2_UNION;
#define WBBP_TX_SEND_DATA2_wt_send_data_i2_START  (0)
#define WBBP_TX_SEND_DATA2_wt_send_data_i2_END    (11)
#define WBBP_TX_SEND_DATA2_wt_send_data_q2_START  (12)
#define WBBP_TX_SEND_DATA2_wt_send_data_q2_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA3_UNION
 结构说明  : TX_SEND_DATA3 寄存器结构定义。地址偏移量:0x028，初值:0x00353238，宽度:32
 寄存器说明: 测试发送数据3
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data3_reg;
    struct
    {
        unsigned long  wt_send_data_i3 : 12; /* bit[0-11] : 测试波形模式下，第3个数据实部 */
        unsigned long  wt_send_data_q3 : 12; /* bit[12-23]: 测试波形模式下，第3个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA3_UNION;
#define WBBP_TX_SEND_DATA3_wt_send_data_i3_START  (0)
#define WBBP_TX_SEND_DATA3_wt_send_data_i3_END    (11)
#define WBBP_TX_SEND_DATA3_wt_send_data_q3_START  (12)
#define WBBP_TX_SEND_DATA3_wt_send_data_q3_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA4_UNION
 结构说明  : TX_SEND_DATA4 寄存器结构定义。地址偏移量:0x02C，初值:0x002D42D4，宽度:32
 寄存器说明: 测试发送数据4
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data4_reg;
    struct
    {
        unsigned long  wt_send_data_i4 : 12; /* bit[0-11] : 测试波形模式下，第4个数据实部 */
        unsigned long  wt_send_data_q4 : 12; /* bit[12-23]: 测试波形模式下，第4个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA4_UNION;
#define WBBP_TX_SEND_DATA4_wt_send_data_i4_START  (0)
#define WBBP_TX_SEND_DATA4_wt_send_data_i4_END    (11)
#define WBBP_TX_SEND_DATA4_wt_send_data_q4_START  (12)
#define WBBP_TX_SEND_DATA4_wt_send_data_q4_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA5_UNION
 结构说明  : TX_SEND_DATA5 寄存器结构定义。地址偏移量:0x030，初值:0x00238353，宽度:32
 寄存器说明: 测试发送数据5
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data5_reg;
    struct
    {
        unsigned long  wt_send_data_i5 : 12; /* bit[0-11] : 测试波形模式下，第5个数据实部 */
        unsigned long  wt_send_data_q5 : 12; /* bit[12-23]: 测试波形模式下，第5个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA5_UNION;
#define WBBP_TX_SEND_DATA5_wt_send_data_i5_START  (0)
#define WBBP_TX_SEND_DATA5_wt_send_data_i5_END    (11)
#define WBBP_TX_SEND_DATA5_wt_send_data_q5_START  (12)
#define WBBP_TX_SEND_DATA5_wt_send_data_q5_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA6_UNION
 结构说明  : TX_SEND_DATA6 寄存器结构定义。地址偏移量:0x034，初值:0x001873B2，宽度:32
 寄存器说明: 测试发送数据6
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data6_reg;
    struct
    {
        unsigned long  wt_send_data_i6 : 12; /* bit[0-11] : 测试波形模式下，第6个数据实部 */
        unsigned long  wt_send_data_q6 : 12; /* bit[12-23]: 测试波形模式下，第6个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA6_UNION;
#define WBBP_TX_SEND_DATA6_wt_send_data_i6_START  (0)
#define WBBP_TX_SEND_DATA6_wt_send_data_i6_END    (11)
#define WBBP_TX_SEND_DATA6_wt_send_data_q6_START  (12)
#define WBBP_TX_SEND_DATA6_wt_send_data_q6_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA7_UNION
 结构说明  : TX_SEND_DATA7 寄存器结构定义。地址偏移量:0x038，初值:0x000C73EC，宽度:32
 寄存器说明: 测试发送数据7
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data7_reg;
    struct
    {
        unsigned long  wt_send_data_i7 : 12; /* bit[0-11] : 测试波形模式下，第7个数据实部 */
        unsigned long  wt_send_data_q7 : 12; /* bit[12-23]: 测试波形模式下，第7个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA7_UNION;
#define WBBP_TX_SEND_DATA7_wt_send_data_i7_START  (0)
#define WBBP_TX_SEND_DATA7_wt_send_data_i7_END    (11)
#define WBBP_TX_SEND_DATA7_wt_send_data_q7_START  (12)
#define WBBP_TX_SEND_DATA7_wt_send_data_q7_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA8_UNION
 结构说明  : TX_SEND_DATA8 寄存器结构定义。地址偏移量:0x03C，初值:0x00000400，宽度:32
 寄存器说明: 测试发送数据8
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data8_reg;
    struct
    {
        unsigned long  wt_send_data_i8 : 12; /* bit[0-11] : 测试波形模式下，第8个数据实部 */
        unsigned long  wt_send_data_q8 : 12; /* bit[12-23]: 测试波形模式下，第8个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA8_UNION;
#define WBBP_TX_SEND_DATA8_wt_send_data_i8_START  (0)
#define WBBP_TX_SEND_DATA8_wt_send_data_i8_END    (11)
#define WBBP_TX_SEND_DATA8_wt_send_data_q8_START  (12)
#define WBBP_TX_SEND_DATA8_wt_send_data_q8_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA9_UNION
 结构说明  : TX_SEND_DATA9 寄存器结构定义。地址偏移量:0x040，初值:0x00F383EC，宽度:32
 寄存器说明: 测试发送数据9
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data9_reg;
    struct
    {
        unsigned long  wt_send_data_i9 : 12; /* bit[0-11] : 测试波形模式下，第9个数据实部 */
        unsigned long  wt_send_data_q9 : 12; /* bit[12-23]: 测试波形模式下，第9个数据虚部 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA9_UNION;
#define WBBP_TX_SEND_DATA9_wt_send_data_i9_START  (0)
#define WBBP_TX_SEND_DATA9_wt_send_data_i9_END    (11)
#define WBBP_TX_SEND_DATA9_wt_send_data_q9_START  (12)
#define WBBP_TX_SEND_DATA9_wt_send_data_q9_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA10_UNION
 结构说明  : TX_SEND_DATA10 寄存器结构定义。地址偏移量:0x044，初值:0x00E783B2，宽度:32
 寄存器说明: 测试发送数据10
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data10_reg;
    struct
    {
        unsigned long  wt_send_data_i10 : 12; /* bit[0-11] : 测试波形模式下，第10个数据实部 */
        unsigned long  wt_send_data_q10 : 12; /* bit[12-23]: 测试波形模式下，第10个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA10_UNION;
#define WBBP_TX_SEND_DATA10_wt_send_data_i10_START  (0)
#define WBBP_TX_SEND_DATA10_wt_send_data_i10_END    (11)
#define WBBP_TX_SEND_DATA10_wt_send_data_q10_START  (12)
#define WBBP_TX_SEND_DATA10_wt_send_data_q10_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA11_UNION
 结构说明  : TX_SEND_DATA11 寄存器结构定义。地址偏移量:0x048，初值:0x00DC7353，宽度:32
 寄存器说明: 测试发送数据11
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data11_reg;
    struct
    {
        unsigned long  wt_send_data_i11 : 12; /* bit[0-11] : 测试波形模式下，第11个数据实部 */
        unsigned long  wt_send_data_q11 : 12; /* bit[12-23]: 测试波形模式下，第11个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA11_UNION;
#define WBBP_TX_SEND_DATA11_wt_send_data_i11_START  (0)
#define WBBP_TX_SEND_DATA11_wt_send_data_i11_END    (11)
#define WBBP_TX_SEND_DATA11_wt_send_data_q11_START  (12)
#define WBBP_TX_SEND_DATA11_wt_send_data_q11_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA12_UNION
 结构说明  : TX_SEND_DATA12 寄存器结构定义。地址偏移量:0x04C，初值:0x00D2B2D4，宽度:32
 寄存器说明: 测试发送数据12
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data12_reg;
    struct
    {
        unsigned long  wt_send_data_i12 : 12; /* bit[0-11] : 测试波形模式下，第12个数据实部 */
        unsigned long  wt_send_data_q12 : 12; /* bit[12-23]: 测试波形模式下，第12个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA12_UNION;
#define WBBP_TX_SEND_DATA12_wt_send_data_i12_START  (0)
#define WBBP_TX_SEND_DATA12_wt_send_data_i12_END    (11)
#define WBBP_TX_SEND_DATA12_wt_send_data_q12_START  (12)
#define WBBP_TX_SEND_DATA12_wt_send_data_q12_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA13_UNION
 结构说明  : TX_SEND_DATA13 寄存器结构定义。地址偏移量:0x050，初值:0x00CAC238，宽度:32
 寄存器说明: 测试发送数据13
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data13_reg;
    struct
    {
        unsigned long  wt_send_data_i13 : 12; /* bit[0-11] : 测试波形模式下，第13个数据实部 */
        unsigned long  wt_send_data_q13 : 12; /* bit[12-23]: 测试波形模式下，第13个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA13_UNION;
#define WBBP_TX_SEND_DATA13_wt_send_data_i13_START  (0)
#define WBBP_TX_SEND_DATA13_wt_send_data_i13_END    (11)
#define WBBP_TX_SEND_DATA13_wt_send_data_q13_START  (12)
#define WBBP_TX_SEND_DATA13_wt_send_data_q13_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA14_UNION
 结构说明  : TX_SEND_DATA14 寄存器结构定义。地址偏移量:0x054，初值:0x00C4D187，宽度:32
 寄存器说明: 测试发送数据14
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data14_reg;
    struct
    {
        unsigned long  wt_send_data_i14 : 12; /* bit[0-11] : 测试波形模式下，第14个数据实部 */
        unsigned long  wt_send_data_q14 : 12; /* bit[12-23]: 测试波形模式下，第14个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA14_UNION;
#define WBBP_TX_SEND_DATA14_wt_send_data_i14_START  (0)
#define WBBP_TX_SEND_DATA14_wt_send_data_i14_END    (11)
#define WBBP_TX_SEND_DATA14_wt_send_data_q14_START  (12)
#define WBBP_TX_SEND_DATA14_wt_send_data_q14_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA15_UNION
 结构说明  : TX_SEND_DATA15 寄存器结构定义。地址偏移量:0x058，初值:0x00C130C7，宽度:32
 寄存器说明: 测试发送数据15
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data15_reg;
    struct
    {
        unsigned long  wt_send_data_i15 : 12; /* bit[0-11] : 测试波形模式下，第15个数据实部 */
        unsigned long  wt_send_data_q15 : 12; /* bit[12-23]: 测试波形模式下，第15个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA15_UNION;
#define WBBP_TX_SEND_DATA15_wt_send_data_i15_START  (0)
#define WBBP_TX_SEND_DATA15_wt_send_data_i15_END    (11)
#define WBBP_TX_SEND_DATA15_wt_send_data_q15_START  (12)
#define WBBP_TX_SEND_DATA15_wt_send_data_q15_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA16_UNION
 结构说明  : TX_SEND_DATA16 寄存器结构定义。地址偏移量:0x05C，初值:0x00C00000，宽度:32
 寄存器说明: 测试发送数据16
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data16_reg;
    struct
    {
        unsigned long  wt_send_data_i16 : 12; /* bit[0-11] : 测试波形模式下，第16个数据实部 */
        unsigned long  wt_send_data_q16 : 12; /* bit[12-23]: 测试波形模式下，第16个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA16_UNION;
#define WBBP_TX_SEND_DATA16_wt_send_data_i16_START  (0)
#define WBBP_TX_SEND_DATA16_wt_send_data_i16_END    (11)
#define WBBP_TX_SEND_DATA16_wt_send_data_q16_START  (12)
#define WBBP_TX_SEND_DATA16_wt_send_data_q16_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA17_UNION
 结构说明  : TX_SEND_DATA17 寄存器结构定义。地址偏移量:0x060，初值:0x00C13F38，宽度:32
 寄存器说明: 测试发送数据17
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data17_reg;
    struct
    {
        unsigned long  wt_send_data_i17 : 12; /* bit[0-11] : 测试波形模式下，第17个数据实部 */
        unsigned long  wt_send_data_q17 : 12; /* bit[12-23]: 测试波形模式下，第17个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA17_UNION;
#define WBBP_TX_SEND_DATA17_wt_send_data_i17_START  (0)
#define WBBP_TX_SEND_DATA17_wt_send_data_i17_END    (11)
#define WBBP_TX_SEND_DATA17_wt_send_data_q17_START  (12)
#define WBBP_TX_SEND_DATA17_wt_send_data_q17_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA18_UNION
 结构说明  : TX_SEND_DATA18 寄存器结构定义。地址偏移量:0x064，初值:0x00C4DE78，宽度:32
 寄存器说明: 测试发送数据18
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data18_reg;
    struct
    {
        unsigned long  wt_send_data_i18 : 12; /* bit[0-11] : 测试波形模式下，第18个数据实部 */
        unsigned long  wt_send_data_q18 : 12; /* bit[12-23]: 测试波形模式下，第18个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA18_UNION;
#define WBBP_TX_SEND_DATA18_wt_send_data_i18_START  (0)
#define WBBP_TX_SEND_DATA18_wt_send_data_i18_END    (11)
#define WBBP_TX_SEND_DATA18_wt_send_data_q18_START  (12)
#define WBBP_TX_SEND_DATA18_wt_send_data_q18_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA19_UNION
 结构说明  : TX_SEND_DATA19 寄存器结构定义。地址偏移量:0x068，初值:0x00CACDC7，宽度:32
 寄存器说明: 测试发送数据19
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data19_reg;
    struct
    {
        unsigned long  wt_send_data_i19 : 12; /* bit[0-11] : 测试波形模式下，第19个数据实部 */
        unsigned long  wt_send_data_q19 : 12; /* bit[12-23]: 测试波形模式下，第19个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA19_UNION;
#define WBBP_TX_SEND_DATA19_wt_send_data_i19_START  (0)
#define WBBP_TX_SEND_DATA19_wt_send_data_i19_END    (11)
#define WBBP_TX_SEND_DATA19_wt_send_data_q19_START  (12)
#define WBBP_TX_SEND_DATA19_wt_send_data_q19_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA20_UNION
 结构说明  : TX_SEND_DATA20 寄存器结构定义。地址偏移量:0x06C，初值:0x00D2BD2B，宽度:32
 寄存器说明: 测试发送数据20
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data20_reg;
    struct
    {
        unsigned long  wt_send_data_i20 : 12; /* bit[0-11] : 测试波形模式下，第20个数据实部 */
        unsigned long  wt_send_data_q20 : 12; /* bit[12-23]: 测试波形模式下，第20个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA20_UNION;
#define WBBP_TX_SEND_DATA20_wt_send_data_i20_START  (0)
#define WBBP_TX_SEND_DATA20_wt_send_data_i20_END    (11)
#define WBBP_TX_SEND_DATA20_wt_send_data_q20_START  (12)
#define WBBP_TX_SEND_DATA20_wt_send_data_q20_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA21_UNION
 结构说明  : TX_SEND_DATA21 寄存器结构定义。地址偏移量:0x070，初值:0x00DC7CAC，宽度:32
 寄存器说明: 测试发送数据21
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data21_reg;
    struct
    {
        unsigned long  wt_send_data_i21 : 12; /* bit[0-11] : 测试波形模式下，第21个数据实部 */
        unsigned long  wt_send_data_q21 : 12; /* bit[12-23]: 测试波形模式下，第21个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA21_UNION;
#define WBBP_TX_SEND_DATA21_wt_send_data_i21_START  (0)
#define WBBP_TX_SEND_DATA21_wt_send_data_i21_END    (11)
#define WBBP_TX_SEND_DATA21_wt_send_data_q21_START  (12)
#define WBBP_TX_SEND_DATA21_wt_send_data_q21_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA22_UNION
 结构说明  : TX_SEND_DATA22 寄存器结构定义。地址偏移量:0x074，初值:0x00E78C4D，宽度:32
 寄存器说明: 测试发送数据22
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data22_reg;
    struct
    {
        unsigned long  wt_send_data_i22 : 12; /* bit[0-11] : 测试波形模式下，第22个数据实部 */
        unsigned long  wt_send_data_q22 : 12; /* bit[12-23]: 测试波形模式下，第22个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA22_UNION;
#define WBBP_TX_SEND_DATA22_wt_send_data_i22_START  (0)
#define WBBP_TX_SEND_DATA22_wt_send_data_i22_END    (11)
#define WBBP_TX_SEND_DATA22_wt_send_data_q22_START  (12)
#define WBBP_TX_SEND_DATA22_wt_send_data_q22_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA23_UNION
 结构说明  : TX_SEND_DATA23 寄存器结构定义。地址偏移量:0x078，初值:0x00F38C13，宽度:32
 寄存器说明: 测试发送数据23
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data23_reg;
    struct
    {
        unsigned long  wt_send_data_i23 : 12; /* bit[0-11] : 测试波形模式下，第23个数据实部 */
        unsigned long  wt_send_data_q23 : 12; /* bit[12-23]: 测试波形模式下，第23个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA23_UNION;
#define WBBP_TX_SEND_DATA23_wt_send_data_i23_START  (0)
#define WBBP_TX_SEND_DATA23_wt_send_data_i23_END    (11)
#define WBBP_TX_SEND_DATA23_wt_send_data_q23_START  (12)
#define WBBP_TX_SEND_DATA23_wt_send_data_q23_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA24_UNION
 结构说明  : TX_SEND_DATA24 寄存器结构定义。地址偏移量:0x07C，初值:0x00FFFC00，宽度:32
 寄存器说明: 测试发送数据24
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data24_reg;
    struct
    {
        unsigned long  wt_send_data_i24 : 12; /* bit[0-11] : 测试波形模式下，第24个数据实部 */
        unsigned long  wt_send_data_q24 : 12; /* bit[12-23]: 测试波形模式下，第24个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA24_UNION;
#define WBBP_TX_SEND_DATA24_wt_send_data_i24_START  (0)
#define WBBP_TX_SEND_DATA24_wt_send_data_i24_END    (11)
#define WBBP_TX_SEND_DATA24_wt_send_data_q24_START  (12)
#define WBBP_TX_SEND_DATA24_wt_send_data_q24_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA25_UNION
 结构说明  : TX_SEND_DATA25 寄存器结构定义。地址偏移量:0x080，初值:0x000C7C13，宽度:32
 寄存器说明: 测试发送数据25
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data25_reg;
    struct
    {
        unsigned long  wt_send_data_i25 : 12; /* bit[0-11] : 测试波形模式下，第25个数据实部 */
        unsigned long  wt_send_data_q25 : 12; /* bit[12-23]: 测试波形模式下，第25个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA25_UNION;
#define WBBP_TX_SEND_DATA25_wt_send_data_i25_START  (0)
#define WBBP_TX_SEND_DATA25_wt_send_data_i25_END    (11)
#define WBBP_TX_SEND_DATA25_wt_send_data_q25_START  (12)
#define WBBP_TX_SEND_DATA25_wt_send_data_q25_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA26_UNION
 结构说明  : TX_SEND_DATA26 寄存器结构定义。地址偏移量:0x084，初值:0x00187C4D，宽度:32
 寄存器说明: 测试发送数据26
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data26_reg;
    struct
    {
        unsigned long  wt_send_data_i26 : 12; /* bit[0-11] : 测试波形模式下，第26个数据实部 */
        unsigned long  wt_send_data_q26 : 12; /* bit[12-23]: 测试波形模式下，第26个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA26_UNION;
#define WBBP_TX_SEND_DATA26_wt_send_data_i26_START  (0)
#define WBBP_TX_SEND_DATA26_wt_send_data_i26_END    (11)
#define WBBP_TX_SEND_DATA26_wt_send_data_q26_START  (12)
#define WBBP_TX_SEND_DATA26_wt_send_data_q26_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA27_UNION
 结构说明  : TX_SEND_DATA27 寄存器结构定义。地址偏移量:0x088，初值:0x00238CAC，宽度:32
 寄存器说明: 测试发送数据27
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data27_reg;
    struct
    {
        unsigned long  wt_send_data_i27 : 12; /* bit[0-11] : 测试波形模式下，第27个数据实部 */
        unsigned long  wt_send_data_q27 : 12; /* bit[12-23]: 测试波形模式下，第27个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA27_UNION;
#define WBBP_TX_SEND_DATA27_wt_send_data_i27_START  (0)
#define WBBP_TX_SEND_DATA27_wt_send_data_i27_END    (11)
#define WBBP_TX_SEND_DATA27_wt_send_data_q27_START  (12)
#define WBBP_TX_SEND_DATA27_wt_send_data_q27_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA28_UNION
 结构说明  : TX_SEND_DATA28 寄存器结构定义。地址偏移量:0x08C，初值:0x002D4D2B，宽度:32
 寄存器说明: 测试发送数据28
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data28_reg;
    struct
    {
        unsigned long  wt_send_data_i28 : 12; /* bit[0-11] : 测试波形模式下，第28个数据实部 */
        unsigned long  wt_send_data_q28 : 12; /* bit[12-23]: 测试波形模式下，第28个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA28_UNION;
#define WBBP_TX_SEND_DATA28_wt_send_data_i28_START  (0)
#define WBBP_TX_SEND_DATA28_wt_send_data_i28_END    (11)
#define WBBP_TX_SEND_DATA28_wt_send_data_q28_START  (12)
#define WBBP_TX_SEND_DATA28_wt_send_data_q28_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA29_UNION
 结构说明  : TX_SEND_DATA29 寄存器结构定义。地址偏移量:0x090，初值:0x00353DC7，宽度:32
 寄存器说明: 测试发送数据29
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data29_reg;
    struct
    {
        unsigned long  wt_send_data_i29 : 12; /* bit[0-11] : 测试波形模式下，第29个数据实部 */
        unsigned long  wt_send_data_q29 : 12; /* bit[12-23]: 测试波形模式下，第29个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA29_UNION;
#define WBBP_TX_SEND_DATA29_wt_send_data_i29_START  (0)
#define WBBP_TX_SEND_DATA29_wt_send_data_i29_END    (11)
#define WBBP_TX_SEND_DATA29_wt_send_data_q29_START  (12)
#define WBBP_TX_SEND_DATA29_wt_send_data_q29_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA30_UNION
 结构说明  : TX_SEND_DATA30 寄存器结构定义。地址偏移量:0x094，初值:0x003B2E78，宽度:32
 寄存器说明: 测试发送数据30
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data30_reg;
    struct
    {
        unsigned long  wt_send_data_i30 : 12; /* bit[0-11] : 测试波形模式下，第30个数据实部 */
        unsigned long  wt_send_data_q30 : 12; /* bit[12-23]: 测试波形模式下，第30个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA30_UNION;
#define WBBP_TX_SEND_DATA30_wt_send_data_i30_START  (0)
#define WBBP_TX_SEND_DATA30_wt_send_data_i30_END    (11)
#define WBBP_TX_SEND_DATA30_wt_send_data_q30_START  (12)
#define WBBP_TX_SEND_DATA30_wt_send_data_q30_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_SEND_DATA31_UNION
 结构说明  : TX_SEND_DATA31 寄存器结构定义。地址偏移量:0x098，初值:0x003ECF38，宽度:32
 寄存器说明: 测试发送数据31
*****************************************************************************/
typedef union
{
    unsigned long      tx_send_data31_reg;
    struct
    {
        unsigned long  wt_send_data_i31 : 12; /* bit[0-11] : 测试波形模式下，第31个数据实部 */
        unsigned long  wt_send_data_q31 : 12; /* bit[12-23]: 测试波形模式下，第31个数据虚部 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_TX_SEND_DATA31_UNION;
#define WBBP_TX_SEND_DATA31_wt_send_data_i31_START  (0)
#define WBBP_TX_SEND_DATA31_wt_send_data_i31_END    (11)
#define WBBP_TX_SEND_DATA31_wt_send_data_q31_START  (12)
#define WBBP_TX_SEND_DATA31_wt_send_data_q31_END    (23)


/*****************************************************************************
 结构名    : WBBP_TX_IQ_CAL_EN_UNION
 结构说明  : TX_IQ_CAL_EN 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_iq_cal_en_reg;
    struct
    {
        unsigned long  dsp_wt_tx_mismatch_iqsel : 1;  /* bit[0]    : W、C和TDS 
                                                                     0:Q路
                                                                     1:I路 */
        unsigned long  reserved_0               : 15; /* bit[1-15] : 保留 */
        unsigned long  dsp_wt_tx_mismatch_en    : 1;  /* bit[16]   : W、C和TDS TXIQMISMATCH校准使能信号（dsp_wt_tx_ip2_corr_en=0时才有效），0：上行通路为正常工作模式；1：上行产生0.96MHz正交信号。 */
        unsigned long  reserved_1               : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_TX_IQ_CAL_EN_UNION;
#define WBBP_TX_IQ_CAL_EN_dsp_wt_tx_mismatch_iqsel_START  (0)
#define WBBP_TX_IQ_CAL_EN_dsp_wt_tx_mismatch_iqsel_END    (0)
#define WBBP_TX_IQ_CAL_EN_dsp_wt_tx_mismatch_en_START     (16)
#define WBBP_TX_IQ_CAL_EN_dsp_wt_tx_mismatch_en_END       (16)


/*****************************************************************************
 结构名    : WBBP_W_IP2_COR_EN_UNION
 结构说明  : W_IP2_COR_EN 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_ip2_cor_en_reg;
    struct
    {
        unsigned long  reserved_0            : 16; /* bit[0-15] : 保留 */
        unsigned long  dsp_wt_tx_ip2_corr_en : 1;  /* bit[16]   : W&amp;TDS IP2校准使能信号0：上行通路为正常工作模式；1：上行产生0.96MHz同相信号。 */
        unsigned long  reserved_1            : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_W_IP2_COR_EN_UNION;
#define WBBP_W_IP2_COR_EN_dsp_wt_tx_ip2_corr_en_START  (16)
#define WBBP_W_IP2_COR_EN_dsp_wt_tx_ip2_corr_en_END    (16)


/*****************************************************************************
 结构名    : WBBP_W_TX_IQ_MISMATCH_COMP_UNION
 结构说明  : W_TX_IQ_MISMATCH_COMP 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_tx_iq_mismatch_comp_reg;
    struct
    {
        unsigned long  dsp_wt_tx_amp_comp   : 10; /* bit[0-9]  : W&amp;TDS TXIQMISMATCH幅度校正因子，有符号数。 */
        unsigned long  reserved_0           : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_wt_tx_phase_comp : 10; /* bit[16-25]: W&amp;TDS TXIQMISMATCH相位校正因子，有符号数。 */
        unsigned long  reserved_1           : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_W_TX_IQ_MISMATCH_COMP_UNION;
#define WBBP_W_TX_IQ_MISMATCH_COMP_dsp_wt_tx_amp_comp_START    (0)
#define WBBP_W_TX_IQ_MISMATCH_COMP_dsp_wt_tx_amp_comp_END      (9)
#define WBBP_W_TX_IQ_MISMATCH_COMP_dsp_wt_tx_phase_comp_START  (16)
#define WBBP_W_TX_IQ_MISMATCH_COMP_dsp_wt_tx_phase_comp_END    (25)


/*****************************************************************************
 结构名    : WBBP_W_TX_IQ_DC_OFFSET_COMP_UNION
 结构说明  : W_TX_IQ_DC_OFFSET_COMP 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_tx_iq_dc_offset_comp_reg;
    struct
    {
        unsigned long  dsp_wt_tx_dc_offset_i : 10; /* bit[0-9]  : W&amp;TDS TXIQMISMATCH I路直流偏置补偿值，有符号数。 */
        unsigned long  reserved_0            : 6;  /* bit[10-15]: 保留 */
        unsigned long  dsp_wt_tx_dc_offset_q : 10; /* bit[16-25]: W&amp;TDS TXIQMISMATCH Q路直流偏置补偿值，有符号数。 */
        unsigned long  reserved_1            : 6;  /* bit[26-31]: 保留 */
    } reg;
} WBBP_W_TX_IQ_DC_OFFSET_COMP_UNION;
#define WBBP_W_TX_IQ_DC_OFFSET_COMP_dsp_wt_tx_dc_offset_i_START  (0)
#define WBBP_W_TX_IQ_DC_OFFSET_COMP_dsp_wt_tx_dc_offset_i_END    (9)
#define WBBP_W_TX_IQ_DC_OFFSET_COMP_dsp_wt_tx_dc_offset_q_START  (16)
#define WBBP_W_TX_IQ_DC_OFFSET_COMP_dsp_wt_tx_dc_offset_q_END    (25)


/*****************************************************************************
 结构名    : WBBP_IQMISMATCH_CORR_LEN_UNION
 结构说明  : IQMISMATCH_CORR_LEN 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      iqmismatch_corr_len_reg;
    struct
    {
        unsigned long  dsp_wt_corr_len_sel : 2;  /* bit[0-1] : W&amp;TDS IQMISMATCH相关长度选择：0:256,1:1024,2:2048,3:4096 */
        unsigned long  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_IQMISMATCH_CORR_LEN_UNION;
#define WBBP_IQMISMATCH_CORR_LEN_dsp_wt_corr_len_sel_START  (0)
#define WBBP_IQMISMATCH_CORR_LEN_dsp_wt_corr_len_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_TX_IQ_COR_EN_UNION
 结构说明  : TX_IQ_COR_EN 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_iq_cor_en_reg;
    struct
    {
        unsigned long  dsp_wt_tx_iq_corr_clr   : 1;  /* bit[0]    : W&amp;TDS TX Iqmismatch校准相关运算结束标志清零信号，自清零。 */
        unsigned long  reserved_0              : 15; /* bit[1-15] : 保留 */
        unsigned long  dsp_wt_tx_iq_corr_start : 1;  /* bit[16]   : W&amp;TDS TX IQmismatch校准相关模块启动信号，自清零，该信号有效后启动一次相关运算。 */
        unsigned long  reserved_1              : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_TX_IQ_COR_EN_UNION;
#define WBBP_TX_IQ_COR_EN_dsp_wt_tx_iq_corr_clr_START    (0)
#define WBBP_TX_IQ_COR_EN_dsp_wt_tx_iq_corr_clr_END      (0)
#define WBBP_TX_IQ_COR_EN_dsp_wt_tx_iq_corr_start_START  (16)
#define WBBP_TX_IQ_COR_EN_dsp_wt_tx_iq_corr_start_END    (16)


/*****************************************************************************
 结构名    : WBBP_TX_IQ_CAL_RPT_UNION
 结构说明  : TX_IQ_CAL_RPT 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tx_iq_cal_rpt_reg;
    struct
    {
        unsigned long  wt_tx_iq_corr_dc     : 13; /* bit[0-12] : W&amp;TDS TX Iqmismatch载漏相关值上报。无符号数。 */
        unsigned long  reserved_0           : 3;  /* bit[13-15]: 保留 */
        unsigned long  wt_tx_iq_corr_iq     : 13; /* bit[16-28]: W&amp;TDS TX Iqmismatch校准IQ相关值上报。无符号数。 */
        unsigned long  reserved_1           : 2;  /* bit[29-30]: 保留 */
        unsigned long  wt_tx_iq_corr_finish : 1;  /* bit[31]   : W&amp;TDS TX Iqmismatch校准相关运算完成标志，高电平表示相关计算完成。由dsp_tx_iq_corr_clr清零。 */
    } reg;
} WBBP_TX_IQ_CAL_RPT_UNION;
#define WBBP_TX_IQ_CAL_RPT_wt_tx_iq_corr_dc_START      (0)
#define WBBP_TX_IQ_CAL_RPT_wt_tx_iq_corr_dc_END        (12)
#define WBBP_TX_IQ_CAL_RPT_wt_tx_iq_corr_iq_START      (16)
#define WBBP_TX_IQ_CAL_RPT_wt_tx_iq_corr_iq_END        (28)
#define WBBP_TX_IQ_CAL_RPT_wt_tx_iq_corr_finish_START  (31)
#define WBBP_TX_IQ_CAL_RPT_wt_tx_iq_corr_finish_END    (31)


/*****************************************************************************
 结构名    : WBBP_UL_DC_OFFSET_EN_UNION
 结构说明  : UL_DC_OFFSET_EN 寄存器结构定义。地址偏移量:0x400，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ul_dc_offset_en_reg;
    struct
    {
        unsigned long  dsp_w_ul_dc_offset_en : 1;  /* bit[0]   : 上行发射I/Q路直流偏置补偿值有效使能，高电平有效。有效时对上行I/Q路分别进行直流偏置值补偿。(SiGe 有效，CMOS 无效) */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UL_DC_OFFSET_EN_UNION;
#define WBBP_UL_DC_OFFSET_EN_dsp_w_ul_dc_offset_en_START  (0)
#define WBBP_UL_DC_OFFSET_EN_dsp_w_ul_dc_offset_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_RF_DC_OFFSET_UNION
 结构说明  : RF_DC_OFFSET 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_dc_offset_reg;
    struct
    {
        unsigned long  dsp_w_ul_dc_offset_i : 12; /* bit[0-11] : 上行发射I路直流偏置补偿值。 */
        unsigned long  reserved_0           : 4;  /* bit[12-15]: 保留 */
        unsigned long  dsp_w_ul_dc_offset_q : 12; /* bit[16-27]: 上行发射Q路直流偏置补偿值。 */
        unsigned long  reserved_1           : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_RF_DC_OFFSET_UNION;
#define WBBP_RF_DC_OFFSET_dsp_w_ul_dc_offset_i_START  (0)
#define WBBP_RF_DC_OFFSET_dsp_w_ul_dc_offset_i_END    (11)
#define WBBP_RF_DC_OFFSET_dsp_w_ul_dc_offset_q_START  (16)
#define WBBP_RF_DC_OFFSET_dsp_w_ul_dc_offset_q_END    (27)


/*****************************************************************************
 结构名    : WBBP_W_TX_LMH_PHASE_COMP_UNION
 结构说明  : W_TX_LMH_PHASE_COMP 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      w_tx_lmh_phase_comp_reg;
    struct
    {
        unsigned long  dsp_w_tx_m2h_phase_comp : 8;  /* bit[0-7]  : 中切高增益时相位补偿值，有符号数。 */
        unsigned long  dsp_w_tx_h2m_phase_comp : 8;  /* bit[8-15] : 高切中增益时相位补偿值，有符号数。 */
        unsigned long  dsp_w_tx_m2l_phase_comp : 8;  /* bit[16-23]: 中切低增益时相位补偿值，有符号数。 */
        unsigned long  dsp_w_tx_l2m_phase_comp : 8;  /* bit[24-31]: 低切中增益时相位补偿值，有符号数。 */
    } reg;
} WBBP_W_TX_LMH_PHASE_COMP_UNION;
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_m2h_phase_comp_START  (0)
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_m2h_phase_comp_END    (7)
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_h2m_phase_comp_START  (8)
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_h2m_phase_comp_END    (15)
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_m2l_phase_comp_START  (16)
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_m2l_phase_comp_END    (23)
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_l2m_phase_comp_START  (24)
#define WBBP_W_TX_LMH_PHASE_COMP_dsp_w_tx_l2m_phase_comp_END    (31)


/*****************************************************************************
 结构名    : WBBP_UL_RF_GATE0_UNION
 结构说明  : UL_RF_GATE0 寄存器结构定义。地址偏移量:0x410，初值:0xC0000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ul_rf_gate0_reg;
    struct
    {
        unsigned long  dsp_w_cfr_gate0   : 13; /* bit[0-12] : 上行削波第一级生效门限。当削波使能打开时，对上行RRC滤波后数据进行削波处理。可配范围64~8191。 */
        unsigned long  reserved_0        : 3;  /* bit[13-15]: 保留 */
        unsigned long  dsp_w_cfr_gain0   : 12; /* bit[16-27]: 上行削波第一级功率调整增益。当削波使能打开时，对上行RRC滤波后数据进行削波处理。 */
        unsigned long  reserved_1        : 2;  /* bit[28-29]: 保留 */
        unsigned long  dsp_w_cfr_bypass2 : 1;  /* bit[30]   : 上行削波bypass标志，高电平有效。复位值为高电平。
                                                              当bypass1为高电平，削波使能关闭，数据无延时直通输出；当bypass1为低电平，bypass2为高电平，削波使能关闭，数据延时16.75chip时间后直接输出；当bypass1和bypass2均为低电平，削波使能打开，削波后数据比原数据延时16.75chip时间输出。 */
        unsigned long  dsp_w_cfr_bypass1 : 1;  /* bit[31]   : 上行削波bypass标志，高电平有效。复位值为高电平。
                                                              当bypass1为高电平，削波使能关闭，数据无延时直通输出；当bypass1为低电平，bypass2为高电平，削波使能关闭，数据延时16.75chip时间后直接输出；当bypass1和bypass2均为低电平，削波使能打开，削波后数据比原数据延时17.5chip时间输出。 */
    } reg;
} WBBP_UL_RF_GATE0_UNION;
#define WBBP_UL_RF_GATE0_dsp_w_cfr_gate0_START    (0)
#define WBBP_UL_RF_GATE0_dsp_w_cfr_gate0_END      (12)
#define WBBP_UL_RF_GATE0_dsp_w_cfr_gain0_START    (16)
#define WBBP_UL_RF_GATE0_dsp_w_cfr_gain0_END      (27)
#define WBBP_UL_RF_GATE0_dsp_w_cfr_bypass2_START  (30)
#define WBBP_UL_RF_GATE0_dsp_w_cfr_bypass2_END    (30)
#define WBBP_UL_RF_GATE0_dsp_w_cfr_bypass1_START  (31)
#define WBBP_UL_RF_GATE0_dsp_w_cfr_bypass1_END    (31)


/*****************************************************************************
 结构名    : WBBP_UL_RF_GATE1_UNION
 结构说明  : UL_RF_GATE1 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ul_rf_gate1_reg;
    struct
    {
        unsigned long  dsp_w_cfr_gate1 : 13; /* bit[0-12] : 上行削波第二级生效门限。当削波使能打开时，对上行RRC滤波后数据进行削波处理。可配范围64~8191。 */
        unsigned long  reserved_0      : 3;  /* bit[13-15]: 保留 */
        unsigned long  dsp_w_cfr_gain1 : 12; /* bit[16-27]: 上行削波第二级功率调整增益。当削波使能打开时，对上行RRC滤波后数据进行削波处理。 */
        unsigned long  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} WBBP_UL_RF_GATE1_UNION;
#define WBBP_UL_RF_GATE1_dsp_w_cfr_gate1_START  (0)
#define WBBP_UL_RF_GATE1_dsp_w_cfr_gate1_END    (12)
#define WBBP_UL_RF_GATE1_dsp_w_cfr_gain1_START  (16)
#define WBBP_UL_RF_GATE1_dsp_w_cfr_gain1_END    (27)


/*****************************************************************************
 结构名    : WBBP_ABB_DATA_WIDTH_UNION
 结构说明  : ABB_DATA_WIDTH 寄存器结构定义。地址偏移量:0x420，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      abb_data_width_reg;
    struct
    {
        unsigned long  dsp_w_ul_data_12bit : 1;  /* bit[0]   : 上行输出到ABB数据有效位宽指示。0表示12bit输出；1表示10bit输出，在bit[1:0]上固定填0。测试用，默认配置0。 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ABB_DATA_WIDTH_UNION;
#define WBBP_ABB_DATA_WIDTH_dsp_w_ul_data_12bit_START  (0)
#define WBBP_ABB_DATA_WIDTH_dsp_w_ul_data_12bit_END    (0)


/*****************************************************************************
 结构名    : WBBP_RF_SEND_DATA_UNION
 结构说明  : RF_SEND_DATA 寄存器结构定义。地址偏移量:0x424，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rf_send_data_reg;
    struct
    {
        unsigned long  dsp_w_rf_send_data_en : 1;  /* bit[0]    : 测试模式下发射数据使能，高电平有效。此时射频发送数据为CPU直接配置的值，未经过调制及RRC滤波。 */
        unsigned long  reserved_0            : 7;  /* bit[1-7]  : 保留 */
        unsigned long  dsp_w_rf_send_data    : 12; /* bit[8-19] : 测试模式下射频发射数据。 */
        unsigned long  reserved_1            : 12; /* bit[20-31]: 保留 */
    } reg;
} WBBP_RF_SEND_DATA_UNION;
#define WBBP_RF_SEND_DATA_dsp_w_rf_send_data_en_START  (0)
#define WBBP_RF_SEND_DATA_dsp_w_rf_send_data_en_END    (0)
#define WBBP_RF_SEND_DATA_dsp_w_rf_send_data_START     (8)
#define WBBP_RF_SEND_DATA_dsp_w_rf_send_data_END       (19)


/*****************************************************************************
 结构名    : WBBP_FIR_SFTBIT_UNION
 结构说明  : FIR_SFTBIT 寄存器结构定义。地址偏移量:0x800，初值:0x0000000B，宽度:32
 寄存器说明: 上下采样滤波器内部累加移位bit数
*****************************************************************************/
typedef union
{
    unsigned long      fir_sftbit_reg;
    struct
    {
        unsigned long  dsp_tds_fir_sftbit : 4;  /* bit[0-3] : 上下采样滤波器内部累加器移位bit数
                                                              上电之后只配置一次，配置范围10~13 */
        unsigned long  reserved           : 28; /* bit[4-31]: 保留 */
    } reg;
} WBBP_FIR_SFTBIT_UNION;
#define WBBP_FIR_SFTBIT_dsp_tds_fir_sftbit_START  (0)
#define WBBP_FIR_SFTBIT_dsp_tds_fir_sftbit_END    (3)


/*****************************************************************************
 结构名    : WBBP_UPPTS_FLG_UNION
 结构说明  : UPPTS_FLG 寄存器结构定义。地址偏移量:0x804，初值:0x00000000，宽度:32
 寄存器说明: 配置特殊时隙
*****************************************************************************/
typedef union
{
    unsigned long      uppts_flg_reg;
    struct
    {
        unsigned long  tds_uppts_flg : 1;  /* bit[0]   : DSP在配置特殊时隙 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UPPTS_FLG_UNION;
#define WBBP_UPPTS_FLG_tds_uppts_flg_START  (0)
#define WBBP_UPPTS_FLG_tds_uppts_flg_END    (0)


/*****************************************************************************
 结构名    : WBBP_PC_GENE_UNION
 结构说明  : PC_GENE 寄存器结构定义。地址偏移量:0x808，初值:0x10010000，宽度:32
 寄存器说明: 上行功率衰减寄存器
*****************************************************************************/
typedef union
{
    unsigned long      pc_gene_reg;
    struct
    {
        unsigned long  dsp_tds_pc_gene   : 17; /* bit[0-16] : 上行功控模块的衰减因子值 */
        unsigned long  reserved_0        : 7;  /* bit[17-23]: 保留 */
        unsigned long  dsp_tds_pc_sftbit : 5;  /* bit[24-28]: 上行功控模块乘以衰减因子后的移位比特数，配置范围13~16 */
        unsigned long  reserved_1        : 3;  /* bit[29-31]: 保留 */
    } reg;
} WBBP_PC_GENE_UNION;
#define WBBP_PC_GENE_dsp_tds_pc_gene_START    (0)
#define WBBP_PC_GENE_dsp_tds_pc_gene_END      (16)
#define WBBP_PC_GENE_dsp_tds_pc_sftbit_START  (24)
#define WBBP_PC_GENE_dsp_tds_pc_sftbit_END    (28)


/*****************************************************************************
 结构名    : WBBP_ABB_FMT_UNION
 结构说明  : ABB_FMT 寄存器结构定义。地址偏移量:0x80C，初值:0x00000000，宽度:32
 寄存器说明: ABB数据接口规格寄存器
*****************************************************************************/
typedef union
{
    unsigned long      abb_fmt_reg;
    struct
    {
        unsigned long  reserved           : 16; /* bit[0-15] : 保留 */
        unsigned long  tds_flush_zero_num : 16; /* bit[16-31]: 正常数据包络发送完成后，输出给DA的冗余0的个数，该功能为保留功能 */
    } reg;
} WBBP_ABB_FMT_UNION;
#define WBBP_ABB_FMT_tds_flush_zero_num_START  (16)
#define WBBP_ABB_FMT_tds_flush_zero_num_END    (31)


/*****************************************************************************
 结构名    : WBBP_TDS_PA_CHANGE_MODE_UNION
 结构说明  : TDS_PA_CHANGE_MODE 寄存器结构定义。地址偏移量:0x810，初值:0x00000000，宽度:32
 寄存器说明: TDS PA档位
*****************************************************************************/
typedef union
{
    unsigned long      tds_pa_change_mode_reg;
    struct
    {
        unsigned long  tds_pa_change_mode : 3;  /* bit[0-2] : TDS PA档位 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_TDS_PA_CHANGE_MODE_UNION;
#define WBBP_TDS_PA_CHANGE_MODE_tds_pa_change_mode_START  (0)
#define WBBP_TDS_PA_CHANGE_MODE_tds_pa_change_mode_END    (2)


/*****************************************************************************
 结构名    : WBBP_DBG_DATA_SEL_UNION
 结构说明  : DBG_DATA_SEL 寄存器结构定义。地址偏移量:0x814，初值:0x00000000，宽度:32
 寄存器说明: 数采数据选择
*****************************************************************************/
typedef union
{
    unsigned long      dbg_data_sel_reg;
    struct
    {
        unsigned long  tds_dbg_data_sel : 3;  /* bit[0-2] : dbg数据选择：
                                                            3'd0: RRC数据输出；
                                                            3'd1: CFR/FIR数据输出；
                                                            3'd2: PC数据输出；
                                                            3'd3: phase comp数据输出
                                                            3'd4: Txiq数据输出
                                                            3'd5:FIFO数据输出
                                                            3'd6:sc_filter数据输出
                                                            3'd7:freq_error数据输出； */
        unsigned long  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_DBG_DATA_SEL_UNION;
#define WBBP_DBG_DATA_SEL_tds_dbg_data_sel_START  (0)
#define WBBP_DBG_DATA_SEL_tds_dbg_data_sel_END    (2)


/*****************************************************************************
 结构名    : WBBP_DFT_FUNC_UNION
 结构说明  : DFT_FUNC 寄存器结构定义。地址偏移量:0x818，初值:0x00000000，宽度:32
 寄存器说明: 可维可测功能
*****************************************************************************/
typedef union
{
    unsigned long      dft_func_reg;
    struct
    {
        unsigned long  tds_dft_func_en : 1;  /* bit[0]   : da_on包络数据统计有效 */
        unsigned long  tds_para_force  : 1;  /* bit[1]   : 参数强制锁定 */
        unsigned long  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DFT_FUNC_UNION;
#define WBBP_DFT_FUNC_tds_dft_func_en_START  (0)
#define WBBP_DFT_FUNC_tds_dft_func_en_END    (0)
#define WBBP_DFT_FUNC_tds_para_force_START   (1)
#define WBBP_DFT_FUNC_tds_para_force_END     (1)


/*****************************************************************************
 结构名    : WBBP_TX_RX_CNT_UNION
 结构说明  : TX_RX_CNT 寄存器结构定义。地址偏移量:0x81C，初值:0x00000000，宽度:32
 寄存器说明: 数据包络统计
*****************************************************************************/
typedef union
{
    unsigned long      tx_rx_cnt_reg;
    struct
    {
        unsigned long  reserved : 16; /* bit[0-15] : 保留 */
        unsigned long  tx_cnt   : 16; /* bit[16-31]: da_on包络个数 */
    } reg;
} WBBP_TX_RX_CNT_UNION;
#define WBBP_TX_RX_CNT_tx_cnt_START    (16)
#define WBBP_TX_RX_CNT_tx_cnt_END      (31)


/*****************************************************************************
 结构名    : WBBP_RRC_UNION
 结构说明  : RRC 寄存器结构定义。地址偏移量:0x820，初值:0x00000000，宽度:32
 寄存器说明: rrc输出信号
*****************************************************************************/
typedef union
{
    unsigned long      rrc_reg;
    struct
    {
        unsigned long  tds_rrc_out_ul : 14; /* bit[0-13] : [13:12]为rrc输出的da_on/dvld；
                                                           [11:0]为rrc的输出的上行数据； */
        unsigned long  reserved       : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_RRC_UNION;
#define WBBP_RRC_tds_rrc_out_ul_START  (0)
#define WBBP_RRC_tds_rrc_out_ul_END    (13)


/*****************************************************************************
 结构名    : WBBP_FIR_TXIQ_UNION
 结构说明  : FIR_TXIQ 寄存器结构定义。地址偏移量:0x828，初值:0x00000000，宽度:32
 寄存器说明: 上行fir和pc输出信号
*****************************************************************************/
typedef union
{
    unsigned long      fir_txiq_reg;
    struct
    {
        unsigned long  tds_pc_out_ul  : 14; /* bit[0-13] : [13:12]为pc输出的da_on/dvld；
                                                           [11:0]为pc的输出上行数据； */
        unsigned long  reserved_0     : 2;  /* bit[14-15]: 保留 */
        unsigned long  tds_fir_out_ul : 14; /* bit[16-29]: [13:12]为fir输出的da_on/dvld；
                                                           [11:0]为fir的输出的上行数据； */
        unsigned long  reserved_1     : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_FIR_TXIQ_UNION;
#define WBBP_FIR_TXIQ_tds_pc_out_ul_START   (0)
#define WBBP_FIR_TXIQ_tds_pc_out_ul_END     (13)
#define WBBP_FIR_TXIQ_tds_fir_out_ul_START  (16)
#define WBBP_FIR_TXIQ_tds_fir_out_ul_END    (29)


/*****************************************************************************
 结构名    : WBBP_SINC_DAIU_UNION
 结构说明  : SINC_DAIU 寄存器结构定义。地址偏移量:0x82C，初值:0x00000000，宽度:32
 寄存器说明: 上行txiq输出信号
*****************************************************************************/
typedef union
{
    unsigned long      sinc_daiu_reg;
    struct
    {
        unsigned long  reserved_0      : 16; /* bit[0-15] : 保留 */
        unsigned long  tds_txiq_out_ul : 14; /* bit[16-29]: [29:28]为txiq输出的da_on/dvld；
                                                            [27:16]为txiq的输出上行数据； */
        unsigned long  reserved_1      : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_SINC_DAIU_UNION;
#define WBBP_SINC_DAIU_tds_txiq_out_ul_START  (16)
#define WBBP_SINC_DAIU_tds_txiq_out_ul_END    (29)


/*****************************************************************************
 结构名    : WBBP_FIFO_UNION
 结构说明  : FIFO 寄存器结构定义。地址偏移量:0x84C，初值:0x00000000，宽度:32
 寄存器说明: FIFO输出信号
*****************************************************************************/
typedef union
{
    unsigned long      fifo_reg;
    struct
    {
        unsigned long  tds_fe_sync_fifo_out_ul : 14; /* bit[0-13] : W、TDS和C:
                                                                    [13:12]为FIFO输出的da_on/dvld；
                                                                    [11:0]为FIFO输出的上行数据； */
        unsigned long  reserved                : 18; /* bit[14-31]: 保留 */
    } reg;
} WBBP_FIFO_UNION;
#define WBBP_FIFO_tds_fe_sync_fifo_out_ul_START  (0)
#define WBBP_FIFO_tds_fe_sync_fifo_out_ul_END    (13)


/*****************************************************************************
 结构名    : WBBP_SC_FREQ_UNION
 结构说明  : SC_FREQ 寄存器结构定义。地址偏移量:0x850，初值:0x00000000，宽度:32
 寄存器说明: 上行采样纠偏和频偏校正输出信号
*****************************************************************************/
typedef union
{
    unsigned long      sc_freq_reg;
    struct
    {
        unsigned long  tds_freq_error_out_ul : 14; /* bit[0-13] : W、TDS和C:
                                                                  [13:12]为频偏校正输出的da_on/dvld；
                                                                  [11:0]为频偏校正输出上行数据； */
        unsigned long  reserved_0            : 2;  /* bit[14-15]: 保留 */
        unsigned long  tds_sc_filter_out_ul  : 14; /* bit[16-29]: W、TDS和C:
                                                                  [29:28]为采样纠偏滤波器输出的da_on/dvld；
                                                                  [27:16]为采样纠偏滤波器输出的上行数据； */
        unsigned long  reserved_1            : 2;  /* bit[30-31]: 保留 */
    } reg;
} WBBP_SC_FREQ_UNION;
#define WBBP_SC_FREQ_tds_freq_error_out_ul_START  (0)
#define WBBP_SC_FREQ_tds_freq_error_out_ul_END    (13)
#define WBBP_SC_FREQ_tds_sc_filter_out_ul_START   (16)
#define WBBP_SC_FREQ_tds_sc_filter_out_ul_END     (29)


/*****************************************************************************
 结构名    : WBBP_ULFE_TCXO_EN_UNION
 结构说明  : ULFE_TCXO_EN 寄存器结构定义。地址偏移量:0x854，初值:0x00000000，宽度:32
 寄存器说明: 单TCXO使能
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_tcxo_en_reg;
    struct
    {
        unsigned long  dsp_ulfe_tcxo_en : 1;  /* bit[0]   : W和C单TCXO使能信号：
                                                            1'b0:单TCXO使能关闭
                                                            1'b1:单TCXO使能打开
                                                            此使能信号只与时钟的选择有关系 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ULFE_TCXO_EN_UNION;
#define WBBP_ULFE_TCXO_EN_dsp_ulfe_tcxo_en_START  (0)
#define WBBP_ULFE_TCXO_EN_dsp_ulfe_tcxo_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_SC_FILTER_OFFSET_UNION
 结构说明  : SC_FILTER_OFFSET 寄存器结构定义。地址偏移量:0x85C，初值:0x00000000，宽度:32
 寄存器说明: dsp强配采样纠偏值
*****************************************************************************/
typedef union
{
    unsigned long      sc_filter_offset_reg;
    struct
    {
        unsigned long  dsp_ul_sc_offset_en : 1;  /* bit[0]    : W:
                                                                双TCXO软件强配采样纠偏值使能信号 */
        unsigned long  dsp_sc_offset       : 11; /* bit[1-11] : W和C:
                                                                双TCXO软件强配采样纠偏值，和下行一致，范围为[-1023,0123]。 */
        unsigned long  dsp_td_sc_offset    : 9;  /* bit[12-20]: TDS:
                                                                软件强配采样纠偏值，有符号数 */
        unsigned long  reserved            : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_SC_FILTER_OFFSET_UNION;
#define WBBP_SC_FILTER_OFFSET_dsp_ul_sc_offset_en_START  (0)
#define WBBP_SC_FILTER_OFFSET_dsp_ul_sc_offset_en_END    (0)
#define WBBP_SC_FILTER_OFFSET_dsp_sc_offset_START        (1)
#define WBBP_SC_FILTER_OFFSET_dsp_sc_offset_END          (11)
#define WBBP_SC_FILTER_OFFSET_dsp_td_sc_offset_START     (12)
#define WBBP_SC_FILTER_OFFSET_dsp_td_sc_offset_END       (20)


/*****************************************************************************
 结构名    : WBBP_SC_CFG_IND_UNION
 结构说明  : SC_CFG_IND 寄存器结构定义。地址偏移量:0x860，初值:0x00000000，宽度:32
 寄存器说明: dsp强配使能信号
*****************************************************************************/
typedef union
{
    unsigned long      sc_cfg_ind_reg;
    struct
    {
        unsigned long  dsp_sc_offset_ind : 1;  /* bit[0]   : W和C:
                                                             双TCXO下软件强配采样纠偏值更新脉冲信号 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_SC_CFG_IND_UNION;
#define WBBP_SC_CFG_IND_dsp_sc_offset_ind_START  (0)
#define WBBP_SC_CFG_IND_dsp_sc_offset_ind_END    (0)


/*****************************************************************************
 结构名    : WBBP_FIFO_CLR_EN_UNION
 结构说明  : FIFO_CLR_EN 寄存器结构定义。地址偏移量:0x864，初值:0x00000000，宽度:32
 寄存器说明: FIFO清零电平信号
*****************************************************************************/
typedef union
{
    unsigned long      fifo_clr_en_reg;
    struct
    {
        unsigned long  dsp_fifo_clr_en : 1;  /* bit[0]   : W和C FIFO清零电平信号:
                                                           1'b0:FIFO不清零
                                                           1'b1:FIFO清零 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_FIFO_CLR_EN_UNION;
#define WBBP_FIFO_CLR_EN_dsp_fifo_clr_en_START  (0)
#define WBBP_FIFO_CLR_EN_dsp_fifo_clr_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_FIFO_RPT_CLR_UNION
 结构说明  : FIFO_RPT_CLR 寄存器结构定义。地址偏移量:0x868，初值:0x00000000，宽度:32
 寄存器说明: FIFO上报清零信号
*****************************************************************************/
typedef union
{
    unsigned long      fifo_rpt_clr_reg;
    struct
    {
        unsigned long  dsp_fifo_rpt_clr_en : 1;  /* bit[0]   : W和C FIFO异常空满上报状态清零信号:
                                                               1'b0:FIFO异常空满不清零
                                                               1'b1:FIFO异常空满清零 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_FIFO_RPT_CLR_UNION;
#define WBBP_FIFO_RPT_CLR_dsp_fifo_rpt_clr_en_START  (0)
#define WBBP_FIFO_RPT_CLR_dsp_fifo_rpt_clr_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_C_ATTEN_VALUE_UNION
 结构说明  : C_ATTEN_VALUE 寄存器结构定义。地址偏移量:0x86C，初值:0x00000000，宽度:32
 寄存器说明: C模功率补偿值
*****************************************************************************/
typedef union
{
    unsigned long      c_atten_value_reg;
    struct
    {
        unsigned long  dsp_c_atten_value : 12; /* bit[0-11] : C模功率补偿值，无符号数 */
        unsigned long  reserved          : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_C_ATTEN_VALUE_UNION;
#define WBBP_C_ATTEN_VALUE_dsp_c_atten_value_START  (0)
#define WBBP_C_ATTEN_VALUE_dsp_c_atten_value_END    (11)


/*****************************************************************************
 结构名    : WBBP_FIFO_EMPTY_FULL_UNION
 结构说明  : FIFO_EMPTY_FULL 寄存器结构定义。地址偏移量:0x870，初值:0x00000000，宽度:32
 寄存器说明: FIFO 异常空满上报
*****************************************************************************/
typedef union
{
    unsigned long      fifo_empty_full_reg;
    struct
    {
        unsigned long  fifo_empty_abn_dsp : 1;  /* bit[0]    : W和C FIFO 异常空标志:
                                                               1'b0:FIFO不异常空；
                                                               1'b1:FIFO异常空。 */
        unsigned long  reserved_0         : 3;  /* bit[1-3]  : 保留 */
        unsigned long  fifo_full_dsp      : 1;  /* bit[4]    : W和C FIFO 满标志:
                                                               1'b0:FIFO不满；
                                                               1'b1:FIFO满。 */
        unsigned long  reserved_1         : 3;  /* bit[5-7]  : 保留 */
        unsigned long  fifo_cnt_a         : 5;  /* bit[8-12] : W和C FIFO 写侧剩余数据个数 */
        unsigned long  reserved_2         : 3;  /* bit[13-15]: 保留 */
        unsigned long  fifo_cnt_b         : 5;  /* bit[16-20]: W和C FIFO 读侧剩余数据个数 */
        unsigned long  reserved_3         : 11; /* bit[21-31]: 保留 */
    } reg;
} WBBP_FIFO_EMPTY_FULL_UNION;
#define WBBP_FIFO_EMPTY_FULL_fifo_empty_abn_dsp_START  (0)
#define WBBP_FIFO_EMPTY_FULL_fifo_empty_abn_dsp_END    (0)
#define WBBP_FIFO_EMPTY_FULL_fifo_full_dsp_START       (4)
#define WBBP_FIFO_EMPTY_FULL_fifo_full_dsp_END         (4)
#define WBBP_FIFO_EMPTY_FULL_fifo_cnt_a_START          (8)
#define WBBP_FIFO_EMPTY_FULL_fifo_cnt_a_END            (12)
#define WBBP_FIFO_EMPTY_FULL_fifo_cnt_b_START          (16)
#define WBBP_FIFO_EMPTY_FULL_fifo_cnt_b_END            (20)


/*****************************************************************************
 结构名    : WBBP_C_PHASE_COMP_UNION
 结构说明  : C_PHASE_COMP 寄存器结构定义。地址偏移量:0x874，初值:0x00000000，宽度:32
 寄存器说明: C模相位补偿值
*****************************************************************************/
typedef union
{
    unsigned long      c_phase_comp_reg;
    struct
    {
        unsigned long  dsp_cos_comp : 11; /* bit[0-10] : C模相位补偿值，有符号数 */
        unsigned long  dsp_sin_comp : 11; /* bit[11-21]: C模相位补偿值，有符号数 */
        unsigned long  reserved     : 10; /* bit[22-31]: 保留 */
    } reg;
} WBBP_C_PHASE_COMP_UNION;
#define WBBP_C_PHASE_COMP_dsp_cos_comp_START  (0)
#define WBBP_C_PHASE_COMP_dsp_cos_comp_END    (10)
#define WBBP_C_PHASE_COMP_dsp_sin_comp_START  (11)
#define WBBP_C_PHASE_COMP_dsp_sin_comp_END    (21)


/*****************************************************************************
 结构名    : WBBP_SC_CAL_CLR_UNION
 结构说明  : SC_CAL_CLR 寄存器结构定义。地址偏移量:0x878，初值:0x00000001，宽度:32
 寄存器说明: 采样纠偏估计清零
*****************************************************************************/
typedef union
{
    unsigned long      sc_cal_clr_reg;
    struct
    {
        unsigned long  dsp_ul_sc_cal_clr : 1;  /* bit[0]   : C模在打开上行时，sc_cal模块的积分清零使能信号
                                                             1'b1:在打开上行时，sc_cal模块的积分自动清零；
                                                             1'b0:在打开上行时，sc_cal模块的积分不清零；(W模不需要配置) */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_SC_CAL_CLR_UNION;
#define WBBP_SC_CAL_CLR_dsp_ul_sc_cal_clr_START  (0)
#define WBBP_SC_CAL_CLR_dsp_ul_sc_cal_clr_END    (0)


/*****************************************************************************
 结构名    : WBBP_SC_CAL_UL_RATIO_UNION
 结构说明  : SC_CAL_UL_RATIO 寄存器结构定义。地址偏移量:0x880，初值:0x00000000，宽度:32
 寄存器说明: 采样纠偏估计清零
*****************************************************************************/
typedef union
{
    unsigned long      sc_cal_ul_ratio_reg;
    struct
    {
        unsigned long  dsp_ul_fc_ratio : 15; /* bit[0-14] : W和C Fc,up/Fc，无符号数 */
        unsigned long  reserved        : 17; /* bit[15-31]: 保留 */
    } reg;
} WBBP_SC_CAL_UL_RATIO_UNION;
#define WBBP_SC_CAL_UL_RATIO_dsp_ul_fc_ratio_START  (0)
#define WBBP_SC_CAL_UL_RATIO_dsp_ul_fc_ratio_END    (14)


/*****************************************************************************
 结构名    : WBBP_NCO_PH_CLR_UNION
 结构说明  : NCO_PH_CLR 寄存器结构定义。地址偏移量:0x884，初值:0x00000000，宽度:32
 寄存器说明: NCO相位累加清零
*****************************************************************************/
typedef union
{
    unsigned long      nco_ph_clr_reg;
    struct
    {
        unsigned long  dsp_nco_ph_clr : 1;  /* bit[0]   : W、C和TDS NCO模块在调试或出错的情况下，相位累加值清零脉冲信号 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_NCO_PH_CLR_UNION;
#define WBBP_NCO_PH_CLR_dsp_nco_ph_clr_START  (0)
#define WBBP_NCO_PH_CLR_dsp_nco_ph_clr_END    (0)


/*****************************************************************************
 结构名    : WBBP_NCO_FW_EN_UNION
 结构说明  : NCO_FW_EN 寄存器结构定义。地址偏移量:0x88C，初值:0x00000000，宽度:32
 寄存器说明: NCO频偏使能
*****************************************************************************/
typedef union
{
    unsigned long      nco_fw_en_reg;
    struct
    {
        unsigned long  dsp_nco_fw_cfg_en : 1;  /* bit[0]   : W/C NCO模块频偏输入强配使能信号 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_NCO_FW_EN_UNION;
#define WBBP_NCO_FW_EN_dsp_nco_fw_cfg_en_START  (0)
#define WBBP_NCO_FW_EN_dsp_nco_fw_cfg_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_RRC_Q_DELAY_UNION
 结构说明  : RRC_Q_DELAY 寄存器结构定义。地址偏移量:0x894，初值:0x00000000，宽度:32
 寄存器说明: RRC Q路延时样点数
*****************************************************************************/
typedef union
{
    unsigned long      rrc_q_delay_reg;
    struct
    {
        unsigned long  dsp_c_q_delay_num : 2;  /* bit[0-1] : C RRC Q路延时样点数
                                                             2'b0：不延时
                                                             2'b1：延1样点
                                                             2'b10：延2样点
                                                             2'b11：延3样点
                                                             W/TDS为0 */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_RRC_Q_DELAY_UNION;
#define WBBP_RRC_Q_DELAY_dsp_c_q_delay_num_START  (0)
#define WBBP_RRC_Q_DELAY_dsp_c_q_delay_num_END    (1)


/*****************************************************************************
 结构名    : WBBP_CALBRT_MOD_UNION
 结构说明  : CALBRT_MOD 寄存器结构定义。地址偏移量:0x898，初值:0x00000000，宽度:32
 寄存器说明: IQ 校准使能
*****************************************************************************/
typedef union
{
    unsigned long      calbrt_mod_reg;
    struct
    {
        unsigned long  dsp_calbrt_mod : 1;  /* bit[0]   : W校准模式选择信号：
                                                          1'b1:校准单音信号立刻生效；
                                                          1'b0:校准单音信号在帧头生效。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_CALBRT_MOD_UNION;
#define WBBP_CALBRT_MOD_dsp_calbrt_mod_START  (0)
#define WBBP_CALBRT_MOD_dsp_calbrt_mod_END    (0)


/*****************************************************************************
 结构名    : WBBP_UL_TDS_SC_ULT_FSMP_UNION
 结构说明  : UL_TDS_SC_ULT_FSMP 寄存器结构定义。地址偏移量:0xA00，初值:0x00000000，宽度:32
 寄存器说明: TDS采样调整步长
*****************************************************************************/
typedef union
{
    unsigned long      ul_tds_sc_ult_fsmp_reg;
    struct
    {
        unsigned long  ul_tds_sc_dlt_fsmp : 17; /* bit[0-16] : tds模式下采样调整步长;17bit */
        unsigned long  reserved           : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_UL_TDS_SC_ULT_FSMP_UNION;
#define WBBP_UL_TDS_SC_ULT_FSMP_ul_tds_sc_dlt_fsmp_START  (0)
#define WBBP_UL_TDS_SC_ULT_FSMP_ul_tds_sc_dlt_fsmp_END    (16)


/*****************************************************************************
 结构名    : WBBP_UL_TDS_SC_ULT_VLD_UNION
 结构说明  : UL_TDS_SC_ULT_VLD 寄存器结构定义。地址偏移量:0xA08，初值:0x00000000，宽度:32
 寄存器说明: TDS采样调整步长有效指示
*****************************************************************************/
typedef union
{
    unsigned long      ul_tds_sc_ult_vld_reg;
    struct
    {
        unsigned long  ul_tds_sc_dlt_vld : 1;  /* bit[0]   : tds dsp配置采样调整步长有效指示,为脉冲信号; */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UL_TDS_SC_ULT_VLD_UNION;
#define WBBP_UL_TDS_SC_ULT_VLD_ul_tds_sc_dlt_vld_START  (0)
#define WBBP_UL_TDS_SC_ULT_VLD_ul_tds_sc_dlt_vld_END    (0)


/*****************************************************************************
 结构名    : WBBP_UL_TDS_SC_INI_VLD_UNION
 结构说明  : UL_TDS_SC_INI_VLD 寄存器结构定义。地址偏移量:0xA0C，初值:0x00000000，宽度:32
 寄存器说明: TDS采样初始偏差值有效指示
*****************************************************************************/
typedef union
{
    unsigned long      ul_tds_sc_ini_vld_reg;
    struct
    {
        unsigned long  ul_tds_sc_ini_vld : 1;  /* bit[0]   : tds dsp配置采样初始偏差值有效指示,为脉冲信号; */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UL_TDS_SC_INI_VLD_UNION;
#define WBBP_UL_TDS_SC_INI_VLD_ul_tds_sc_ini_vld_START  (0)
#define WBBP_UL_TDS_SC_INI_VLD_ul_tds_sc_ini_vld_END    (0)


/*****************************************************************************
 结构名    : WBBP_UL_TDS_SC_MOD_UNION
 结构说明  : UL_TDS_SC_MOD 寄存器结构定义。地址偏移量:0xA10，初值:0x00000000，宽度:32
 寄存器说明: TDS参数立即生效模式
*****************************************************************************/
typedef union
{
    unsigned long      ul_tds_sc_mod_reg;
    struct
    {
        unsigned long  dsp_tds_sc_fsmp_mod : 1;  /* bit[0]   : tds模式下参数立即生效模式：
                                                               0：不立即生效，用da_on上升沿和*vld锁存参数；
                                                               1：立即生效，直接根据*vld去锁存参数； 
                                                               默认值为0。
                                                               (保留) */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UL_TDS_SC_MOD_UNION;
#define WBBP_UL_TDS_SC_MOD_dsp_tds_sc_fsmp_mod_START  (0)
#define WBBP_UL_TDS_SC_MOD_dsp_tds_sc_fsmp_mod_END    (0)


/*****************************************************************************
 结构名    : WBBP_UL_SC_ABN_DEL_EN_UNION
 结构说明  : UL_SC_ABN_DEL_EN 寄存器结构定义。地址偏移量:0xA14，初值:0x00000001，宽度:32
 寄存器说明: fifo几乎空，几乎满的异常删加点使能
*****************************************************************************/
typedef union
{
    unsigned long      ul_sc_abn_del_en_reg;
    struct
    {
        unsigned long  ul_sc_abn_del_en : 1;  /* bit[0]   : W、C和TDS sc_cal模块在fifo几乎空，几乎满的异常删加点使能：
                                                            0：关闭异常删加点功能；
                                                            1：打开异常删加点功能。
                                                            默认打开。 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UL_SC_ABN_DEL_EN_UNION;
#define WBBP_UL_SC_ABN_DEL_EN_ul_sc_abn_del_en_START  (0)
#define WBBP_UL_SC_ABN_DEL_EN_ul_sc_abn_del_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_UL_SC_CAL_NUM_RPT_UNION
 结构说明  : UL_SC_CAL_NUM_RPT 寄存器结构定义。地址偏移量:0xA1C，初值:0x00000000，宽度:32
 寄存器说明: SC_CAL删加点个数上报
*****************************************************************************/
typedef union
{
    unsigned long      ul_sc_cal_num_rpt_reg;
    struct
    {
        unsigned long  sc_add_num_rpt : 16; /* bit[0-15] : W、C和TDS sc_cal模块计算加点次数统计。 */
        unsigned long  sc_del_num_rpt : 16; /* bit[16-31]: W、C和TDS sc_cal模块计算删点次数统计。 */
    } reg;
} WBBP_UL_SC_CAL_NUM_RPT_UNION;
#define WBBP_UL_SC_CAL_NUM_RPT_sc_add_num_rpt_START  (0)
#define WBBP_UL_SC_CAL_NUM_RPT_sc_add_num_rpt_END    (15)
#define WBBP_UL_SC_CAL_NUM_RPT_sc_del_num_rpt_START  (16)
#define WBBP_UL_SC_CAL_NUM_RPT_sc_del_num_rpt_END    (31)


/*****************************************************************************
 结构名    : WBBP_UL_FIFO_ABN_NUM_UNION
 结构说明  : UL_FIFO_ABN_NUM 寄存器结构定义。地址偏移量:0xA20，初值:0x00000000，宽度:32
 寄存器说明: FIFO 异常空满次数上报
*****************************************************************************/
typedef union
{
    unsigned long      ul_fifo_abn_num_reg;
    struct
    {
        unsigned long  fifo_alemp_num : 8;  /* bit[0-7]  : W、C和TDS FIFO将空次数上报 */
        unsigned long  fifo_alful_num : 8;  /* bit[8-15] : W、C和TDS FIFO将满次数上报 */
        unsigned long  fifo_emp_num   : 8;  /* bit[16-23]: W、C和TDS FIFO空次数上报 */
        unsigned long  fifo_ful_num   : 8;  /* bit[24-31]: W、C和TDS FIFO满次数上报 */
    } reg;
} WBBP_UL_FIFO_ABN_NUM_UNION;
#define WBBP_UL_FIFO_ABN_NUM_fifo_alemp_num_START  (0)
#define WBBP_UL_FIFO_ABN_NUM_fifo_alemp_num_END    (7)
#define WBBP_UL_FIFO_ABN_NUM_fifo_alful_num_START  (8)
#define WBBP_UL_FIFO_ABN_NUM_fifo_alful_num_END    (15)
#define WBBP_UL_FIFO_ABN_NUM_fifo_emp_num_START    (16)
#define WBBP_UL_FIFO_ABN_NUM_fifo_emp_num_END      (23)
#define WBBP_UL_FIFO_ABN_NUM_fifo_ful_num_START    (24)
#define WBBP_UL_FIFO_ABN_NUM_fifo_ful_num_END      (31)


/*****************************************************************************
 结构名    : WBBP_UL_SC_CAL_NUM_RPT_CLR_UNION
 结构说明  : UL_SC_CAL_NUM_RPT_CLR 寄存器结构定义。地址偏移量:0xA24，初值:0x00000000，宽度:32
 寄存器说明: sc_cal删加点次数统计清零
*****************************************************************************/
typedef union
{
    unsigned long      ul_sc_cal_num_rpt_clr_reg;
    struct
    {
        unsigned long  ul_sc_add_num_clr : 1;  /* bit[0]   : W、C和TDS sc_cal模块计算加点次数统计清零。 */
        unsigned long  ul_sc_del_num_clr : 1;  /* bit[1]   : W、C和TDS sc_cal模块计算删点次数统计清零。 */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_UL_SC_CAL_NUM_RPT_CLR_UNION;
#define WBBP_UL_SC_CAL_NUM_RPT_CLR_ul_sc_add_num_clr_START  (0)
#define WBBP_UL_SC_CAL_NUM_RPT_CLR_ul_sc_add_num_clr_END    (0)
#define WBBP_UL_SC_CAL_NUM_RPT_CLR_ul_sc_del_num_clr_START  (1)
#define WBBP_UL_SC_CAL_NUM_RPT_CLR_ul_sc_del_num_clr_END    (1)


/*****************************************************************************
 结构名    : WBBP_UL_SC_CAL_PARA_EN_UNION
 结构说明  : UL_SC_CAL_PARA_EN 寄存器结构定义。地址偏移量:0xA28，初值:0x00000000，宽度:32
 寄存器说明: sc_filter参数来源
*****************************************************************************/
typedef union
{
    unsigned long      ul_sc_cal_para_en_reg;
    struct
    {
        unsigned long  dsp_sc_cal_para_en : 1;  /* bit[0]   : sc_filter模块的参数来源：
                                                              1'b1：参数来源于sc_cal；
                                                              1'b0：W参数来源于多径或强配，TDS和C模来源于强配。 */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UL_SC_CAL_PARA_EN_UNION;
#define WBBP_UL_SC_CAL_PARA_EN_dsp_sc_cal_para_en_START  (0)
#define WBBP_UL_SC_CAL_PARA_EN_dsp_sc_cal_para_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_UL_DEL_ADD_EN_UNION
 结构说明  : UL_DEL_ADD_EN 寄存器结构定义。地址偏移量:0xA2C，初值:0x00000000，宽度:32
 寄存器说明: sc_cal模块积分功能使能信号
*****************************************************************************/
typedef union
{
    unsigned long      ul_del_add_en_reg;
    struct
    {
        unsigned long  dsp_del_add_en : 1;  /* bit[0]   : sc_cal模块积分功能使能信号，使能关闭情况下，删加点和offset都为0：
                                                          1'b0:积分使能关闭；
                                                          1'b1:积分使能打开。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_UL_DEL_ADD_EN_UNION;
#define WBBP_UL_DEL_ADD_EN_dsp_del_add_en_START  (0)
#define WBBP_UL_DEL_ADD_EN_dsp_del_add_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_DPD_STEP1_UNION
 结构说明  : DPD_STEP1 寄存器结构定义。地址偏移量:0xA34，初值:0x00000000，宽度:32
 寄存器说明: Max_power-2~Max_power-5对应的量化参数step_v
*****************************************************************************/
typedef union
{
    unsigned long      dpd_step1_reg;
    struct
    {
        unsigned long  dsp_dpd_step_v0 : 9;  /* bit[0-8]  : Max_power-5 */
        unsigned long  dsp_dpd_step_v1 : 9;  /* bit[9-17] : Max_power-4 */
        unsigned long  dsp_dpd_step_v2 : 9;  /* bit[18-26]: Max_power-3 */
        unsigned long  reserved        : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DPD_STEP1_UNION;
#define WBBP_DPD_STEP1_dsp_dpd_step_v0_START  (0)
#define WBBP_DPD_STEP1_dsp_dpd_step_v0_END    (8)
#define WBBP_DPD_STEP1_dsp_dpd_step_v1_START  (9)
#define WBBP_DPD_STEP1_dsp_dpd_step_v1_END    (17)
#define WBBP_DPD_STEP1_dsp_dpd_step_v2_START  (18)
#define WBBP_DPD_STEP1_dsp_dpd_step_v2_END    (26)


/*****************************************************************************
 结构名    : WBBP_DPD_STEP2_UNION
 结构说明  : DPD_STEP2 寄存器结构定义。地址偏移量:0xA38，初值:0x00000000，宽度:32
 寄存器说明: Max_power-2~Max_power-5对应的量化参数step_v
*****************************************************************************/
typedef union
{
    unsigned long      dpd_step2_reg;
    struct
    {
        unsigned long  dsp_dpd_step_v3 : 9;  /* bit[0-8]  : Max_power-2 */
        unsigned long  dsp_dpd_step_v4 : 9;  /* bit[9-17] : Max_power-1 */
        unsigned long  dsp_dpd_step_v5 : 9;  /* bit[18-26]: Max_power */
        unsigned long  reserved        : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DPD_STEP2_UNION;
#define WBBP_DPD_STEP2_dsp_dpd_step_v3_START  (0)
#define WBBP_DPD_STEP2_dsp_dpd_step_v3_END    (8)
#define WBBP_DPD_STEP2_dsp_dpd_step_v4_START  (9)
#define WBBP_DPD_STEP2_dsp_dpd_step_v4_END    (17)
#define WBBP_DPD_STEP2_dsp_dpd_step_v5_START  (18)
#define WBBP_DPD_STEP2_dsp_dpd_step_v5_END    (26)


/*****************************************************************************
 结构名    : WBBP_DPD_STEP3_UNION
 结构说明  : DPD_STEP3 寄存器结构定义。地址偏移量:0xA3C，初值:0x00000000，宽度:32
 寄存器说明: Max_power-2~Max_power-5对应的量化参数step_v
*****************************************************************************/
typedef union
{
    unsigned long      dpd_step3_reg;
    struct
    {
        unsigned long  dsp_dpd_step_v6 : 9;  /* bit[0-8]  : Max_power+1 */
        unsigned long  dsp_dpd_step_v7 : 9;  /* bit[9-17] : Max_power+1 */
        unsigned long  reserved        : 14; /* bit[18-31]: 保留 */
    } reg;
} WBBP_DPD_STEP3_UNION;
#define WBBP_DPD_STEP3_dsp_dpd_step_v6_START  (0)
#define WBBP_DPD_STEP3_dsp_dpd_step_v6_END    (8)
#define WBBP_DPD_STEP3_dsp_dpd_step_v7_START  (9)
#define WBBP_DPD_STEP3_dsp_dpd_step_v7_END    (17)


/*****************************************************************************
 结构名    : WBBP_DPD_COMP_UNION
 结构说明  : DPD_COMP 寄存器结构定义。地址偏移量:0xA40，初值:0x00000000，宽度:32
 寄存器说明: DPD功率的温补和频补的合并补偿值
*****************************************************************************/
typedef union
{
    unsigned long      dpd_comp_reg;
    struct
    {
        unsigned long  dsp_dpd_comp : 11; /* bit[0-10] : DPD */
        unsigned long  reserved     : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_DPD_COMP_UNION;
#define WBBP_DPD_COMP_dsp_dpd_comp_START  (0)
#define WBBP_DPD_COMP_dsp_dpd_comp_END    (10)


/*****************************************************************************
 结构名    : WBBP_DPD_RAM_TABLE_SEL_UNION
 结构说明  : DPD_RAM_TABLE_SEL 寄存器结构定义。地址偏移量:0xA44，初值:0x00000000，宽度:32
 寄存器说明: DPD ram tabel选择
*****************************************************************************/
typedef union
{
    unsigned long      dpd_ram_table_sel_reg;
    struct
    {
        unsigned long  dsp_dpd_force_en : 1;  /* bit[0]   : DPD */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DPD_RAM_TABLE_SEL_UNION;
#define WBBP_DPD_RAM_TABLE_SEL_dsp_dpd_force_en_START  (0)
#define WBBP_DPD_RAM_TABLE_SEL_dsp_dpd_force_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_TX_TONE_FREQ_SEL_UNION
 结构说明  : TX_TONE_FREQ_SEL 寄存器结构定义。地址偏移量:0xA48，初值:0x00000000，宽度:32
 寄存器说明: CPU接口配置的单音频率选择信号
*****************************************************************************/
typedef union
{
    unsigned long      tx_tone_freq_sel_reg;
    struct
    {
        unsigned long  dsp_tx_tone_freq_sel : 1;  /* bit[0]   : CPU */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_TX_TONE_FREQ_SEL_UNION;
#define WBBP_TX_TONE_FREQ_SEL_dsp_tx_tone_freq_sel_START  (0)
#define WBBP_TX_TONE_FREQ_SEL_dsp_tx_tone_freq_sel_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_DC_NCO_PH_CLR_UNION
 结构说明  : DSP_DC_NCO_PH_CLR 寄存器结构定义。地址偏移量:0xA4C，初值:0x00000000，宽度:32
 寄存器说明: 上变频NCO累加相位清零
*****************************************************************************/
typedef union
{
    unsigned long      dsp_dc_nco_ph_clr_reg;
    struct
    {
        unsigned long  dsp_dc_nco_ph_clr : 1;  /* bit[0]   : 上变频NCO模块在调试或出错的情况下，相位累加值清零脉冲信号 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_DC_NCO_PH_CLR_UNION;
#define WBBP_DSP_DC_NCO_PH_CLR_dsp_dc_nco_ph_clr_START  (0)
#define WBBP_DSP_DC_NCO_PH_CLR_dsp_dc_nco_ph_clr_END    (0)


/*****************************************************************************
 结构名    : WBBP_DSP_CONJU_SEL_UNION
 结构说明  : DSP_CONJU_SEL 寄存器结构定义。地址偏移量:0xA50，初值:0x00000000，宽度:32
 寄存器说明: 主辅载波共轭选择
*****************************************************************************/
typedef union
{
    unsigned long      dsp_conju_sel_reg;
    struct
    {
        unsigned long  dsp_conju_sel : 1;  /* bit[0]   : 主载波和辅载波上变频共轭选择信号，1'b0:辅载波虚部取反，主载波不取反；1'b1:主载波虚部取反，辅载波不取反 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DSP_CONJU_SEL_UNION;
#define WBBP_DSP_CONJU_SEL_dsp_conju_sel_START  (0)
#define WBBP_DSP_CONJU_SEL_dsp_conju_sel_END    (0)


/*****************************************************************************
 结构名    : WBBP_DCUPA_SW_UL_FREQ_MOD_UNION
 结构说明  : DCUPA_SW_UL_FREQ_MOD 寄存器结构定义。地址偏移量:0xA54，初值:0x00000010，宽度:32
 寄存器说明: 主辅载波上变频选择
*****************************************************************************/
typedef union
{
    unsigned long      dcupa_sw_ul_freq_mod_reg;
    struct
    {
        unsigned long  dsp_dcupa_sw_ul_freq_mod : 1;  /* bit[0]   : DCUPA模式下DC/SC切换时上行频点切换模式，1：sc下使用DC搬移频点模式 */
        unsigned long  reserved_0               : 3;  /* bit[1-3] : 保留 */
        unsigned long  dsp_dcupa_act_disable    : 1;  /* bit[4]   : DSP强制配置NCO频点搬移是否随dcupa_active_flag指示生效。为1表示频点搬移受dcupa_active_flag控制，默认为1。 */
        unsigned long  reserved_1               : 27; /* bit[5-31]: 保留 */
    } reg;
} WBBP_DCUPA_SW_UL_FREQ_MOD_UNION;
#define WBBP_DCUPA_SW_UL_FREQ_MOD_dsp_dcupa_sw_ul_freq_mod_START  (0)
#define WBBP_DCUPA_SW_UL_FREQ_MOD_dsp_dcupa_sw_ul_freq_mod_END    (0)
#define WBBP_DCUPA_SW_UL_FREQ_MOD_dsp_dcupa_act_disable_START     (4)
#define WBBP_DCUPA_SW_UL_FREQ_MOD_dsp_dcupa_act_disable_END       (4)


/*****************************************************************************
 结构名    : WBBP_DPD_BYPASS_UNION
 结构说明  : DPD_BYPASS 寄存器结构定义。地址偏移量:0xA5C，初值:0x00000000，宽度:32
 寄存器说明: DPD bypass
*****************************************************************************/
typedef union
{
    unsigned long      dpd_bypass_reg;
    struct
    {
        unsigned long  dsp_tx_dpd_iqcomp_bypass : 1;  /* bit[0]   : DPD补偿通路 */
        unsigned long  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DPD_BYPASS_UNION;
#define WBBP_DPD_BYPASS_dsp_tx_dpd_iqcomp_bypass_START  (0)
#define WBBP_DPD_BYPASS_dsp_tx_dpd_iqcomp_bypass_END    (0)


/*****************************************************************************
 结构名    : WBBP_DPD_LUT_ADDR_SEL_UNION
 结构说明  : DPD_LUT_ADDR_SEL 寄存器结构定义。地址偏移量:0xA60，初值:0x00000000，宽度:32
 寄存器说明: DPD LUT寻表方式
*****************************************************************************/
typedef union
{
    unsigned long      dpd_lut_addr_sel_reg;
    struct
    {
        unsigned long  dsp_lut_addr_sel : 1;  /* bit[0]   : DPD LUT查找表的子表地址映射模式模式选择信号
                                                            1’b0：DPD LUT查找表的8档的8个子表采用绝对发送功率方式查表
                                                            1’b1：DPD LUT查找表的8档的8个子表采用根据射频增益衰减表查表地址值查表。 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DPD_LUT_ADDR_SEL_UNION;
#define WBBP_DPD_LUT_ADDR_SEL_dsp_lut_addr_sel_START  (0)
#define WBBP_DPD_LUT_ADDR_SEL_dsp_lut_addr_sel_END    (0)


/*****************************************************************************
 结构名    : WBBP_DPD_THRESHOLD0_1_UNION
 结构说明  : DPD_THRESHOLD0_1 寄存器结构定义。地址偏移量:0xA64，初值:0x00000000，宽度:32
 寄存器说明: DPD LUT门限
*****************************************************************************/
typedef union
{
    unsigned long      dpd_threshold0_1_reg;
    struct
    {
        unsigned long  dsp_dpd_threshold0 : 11; /* bit[0-10] : DPD生效功率门限0。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_dpd_threshold1 : 11; /* bit[16-26]: DPD生效功率门限1。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DPD_THRESHOLD0_1_UNION;
#define WBBP_DPD_THRESHOLD0_1_dsp_dpd_threshold0_START  (0)
#define WBBP_DPD_THRESHOLD0_1_dsp_dpd_threshold0_END    (10)
#define WBBP_DPD_THRESHOLD0_1_dsp_dpd_threshold1_START  (16)
#define WBBP_DPD_THRESHOLD0_1_dsp_dpd_threshold1_END    (26)


/*****************************************************************************
 结构名    : WBBP_DPD_THRESHOLD2_3_UNION
 结构说明  : DPD_THRESHOLD2_3 寄存器结构定义。地址偏移量:0xA68，初值:0x00000000，宽度:32
 寄存器说明: DPD LUT门限
*****************************************************************************/
typedef union
{
    unsigned long      dpd_threshold2_3_reg;
    struct
    {
        unsigned long  dsp_dpd_threshold2 : 11; /* bit[0-10] : DPD生效功率门限2。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_dpd_threshold3 : 11; /* bit[16-26]: DPD生效功率门限3。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DPD_THRESHOLD2_3_UNION;
#define WBBP_DPD_THRESHOLD2_3_dsp_dpd_threshold2_START  (0)
#define WBBP_DPD_THRESHOLD2_3_dsp_dpd_threshold2_END    (10)
#define WBBP_DPD_THRESHOLD2_3_dsp_dpd_threshold3_START  (16)
#define WBBP_DPD_THRESHOLD2_3_dsp_dpd_threshold3_END    (26)


/*****************************************************************************
 结构名    : WBBP_DPD_THRESHOLD4_5_UNION
 结构说明  : DPD_THRESHOLD4_5 寄存器结构定义。地址偏移量:0xA6C，初值:0x00000000，宽度:32
 寄存器说明: DPD LUT门限
*****************************************************************************/
typedef union
{
    unsigned long      dpd_threshold4_5_reg;
    struct
    {
        unsigned long  dsp_dpd_threshold4 : 11; /* bit[0-10] : DPD生效功率门限4。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_dpd_threshold5 : 11; /* bit[16-26]: DPD生效功率门限5。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DPD_THRESHOLD4_5_UNION;
#define WBBP_DPD_THRESHOLD4_5_dsp_dpd_threshold4_START  (0)
#define WBBP_DPD_THRESHOLD4_5_dsp_dpd_threshold4_END    (10)
#define WBBP_DPD_THRESHOLD4_5_dsp_dpd_threshold5_START  (16)
#define WBBP_DPD_THRESHOLD4_5_dsp_dpd_threshold5_END    (26)


/*****************************************************************************
 结构名    : WBBP_DPD_THRESHOLD6_7_UNION
 结构说明  : DPD_THRESHOLD6_7 寄存器结构定义。地址偏移量:0xA70，初值:0x00000000，宽度:32
 寄存器说明: DPD LUT门限
*****************************************************************************/
typedef union
{
    unsigned long      dpd_threshold6_7_reg;
    struct
    {
        unsigned long  dsp_dpd_threshold6 : 11; /* bit[0-10] : DPD生效功率门限6。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned long  dsp_dpd_threshold7 : 11; /* bit[16-26]: DPD生效功率门限7。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_DPD_THRESHOLD6_7_UNION;
#define WBBP_DPD_THRESHOLD6_7_dsp_dpd_threshold6_START  (0)
#define WBBP_DPD_THRESHOLD6_7_dsp_dpd_threshold6_END    (10)
#define WBBP_DPD_THRESHOLD6_7_dsp_dpd_threshold7_START  (16)
#define WBBP_DPD_THRESHOLD6_7_dsp_dpd_threshold7_END    (26)


/*****************************************************************************
 结构名    : WBBP_DPD_THRESHOLD8_UNION
 结构说明  : DPD_THRESHOLD8 寄存器结构定义。地址偏移量:0xA74，初值:0x00000000，宽度:32
 寄存器说明: DPD LUT门限
*****************************************************************************/
typedef union
{
    unsigned long      dpd_threshold8_reg;
    struct
    {
        unsigned long  dsp_dpd_threshold8 : 11; /* bit[0-10] : DPD生效功率门限8。当dpd_lut_addr_sel=1’b0时，对应功率门限，单位0.1dBm精度，当dpd_lut_addr_sel=1’b1，对应射频增益衰减表查表地址值 */
        unsigned long  reserved           : 21; /* bit[11-31]: 保留 */
    } reg;
} WBBP_DPD_THRESHOLD8_UNION;
#define WBBP_DPD_THRESHOLD8_dsp_dpd_threshold8_START  (0)
#define WBBP_DPD_THRESHOLD8_dsp_dpd_threshold8_END    (10)


/*****************************************************************************
 结构名    : WBBP_COM_CW_EN_UNION
 结构说明  : COM_CW_EN 寄存器结构定义。地址偏移量:0xA78，初值:0x00000000，宽度:32
 寄存器说明: 单音模块使能
*****************************************************************************/
typedef union
{
    unsigned long      com_cw_en_reg;
    struct
    {
        unsigned long  dsp_com_cw_en : 1;  /* bit[0]   : CFR前单/双音信号发送使能，在上行模式不为TDS-CDMA时配置有效。1’b1:U/X模CFR前单/双音信号发送使能，当该使能有效时，BBP根据软件配置的I/Q和周期点数周期发送单/双音信号。 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_COM_CW_EN_UNION;
#define WBBP_COM_CW_EN_dsp_com_cw_en_START  (0)
#define WBBP_COM_CW_EN_dsp_com_cw_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_COM_CW_CNT_UNION
 结构说明  : COM_CW_CNT 寄存器结构定义。地址偏移量:0xA7C，初值:0x0000000F，宽度:32
 寄存器说明: 单音正（余）弦波周期内的点数
*****************************************************************************/
typedef union
{
    unsigned long      com_cw_cnt_reg;
    struct
    {
        unsigned long  dsp_com_cw_cnt : 5;  /* bit[0-4] : CFR前单/双音信号正（余）弦波周期内的点数，默认为15，采用15.36M/(dsp_com_cw_cnt+1)得到需要发送信号的周期频率，例如默认15.36M/16=0.96M。 */
        unsigned long  reserved       : 27; /* bit[5-31]: 保留 */
    } reg;
} WBBP_COM_CW_CNT_UNION;
#define WBBP_COM_CW_CNT_dsp_com_cw_cnt_START  (0)
#define WBBP_COM_CW_CNT_dsp_com_cw_cnt_END    (4)


/*****************************************************************************
 结构名    : WBBP_COM_CW_TX_MODE_UNION
 结构说明  : COM_CW_TX_MODE 寄存器结构定义。地址偏移量:0xA80，初值:0x00000000，宽度:32
 寄存器说明: 单音模式选择信号
*****************************************************************************/
typedef union
{
    unsigned long      com_cw_tx_mode_reg;
    struct
    {
        unsigned long  dsp_com_cw_tx_mode : 1;  /* bit[0]   : CFR前单/双音信号发送模式选择信号
                                                              1’b0:按照软件配置的加权系数立即生效的加权模式
                                                              1’b1:BBP自动周期性循环发送模
                                                              。 */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_COM_CW_TX_MODE_UNION;
#define WBBP_COM_CW_TX_MODE_dsp_com_cw_tx_mode_START  (0)
#define WBBP_COM_CW_TX_MODE_dsp_com_cw_tx_mode_END    (0)


/*****************************************************************************
 结构名    : WBBP_COM_CW_TX_PRD_UNION
 结构说明  : COM_CW_TX_PRD 寄存器结构定义。地址偏移量:0xA84，初值:0x00000000，宽度:32
 寄存器说明: 单音每个周期发送的点数
*****************************************************************************/
typedef union
{
    unsigned long      com_cw_tx_prd_reg;
    struct
    {
        unsigned long  dsp_com_cw_tx_prd : 2;  /* bit[0-1] : 当发送模式为自动发送时(dsp_cw_tx_mode=1’b1),每个周期发送的点数。
                                                             2’d0：每个周期发送1024个点
                                                             2’d1：每个周期发送2048个点
                                                             2’d2：每个周期发送3072个点
                                                             2’d3：每个周期发送4096个点 */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_COM_CW_TX_PRD_UNION;
#define WBBP_COM_CW_TX_PRD_dsp_com_cw_tx_prd_START  (0)
#define WBBP_COM_CW_TX_PRD_dsp_com_cw_tx_prd_END    (1)


/*****************************************************************************
 结构名    : WBBP_COM_CW_COEF_UNION
 结构说明  : COM_CW_COEF 寄存器结构定义。地址偏移量:0xA88，初值:0x00000000，宽度:32
 寄存器说明: 单音加权系数
*****************************************************************************/
typedef union
{
    unsigned long      com_cw_coef_reg;
    struct
    {
        unsigned long  dsp_com_cw_coef : 24; /* bit[0-23] : 单/双音I/Q幅度加权系数，无符号数；
                                                            当dsp_com_cw_tx_mode=1’b0时，配置的补偿系数直接补偿立即生效
                                                            当dsp_com_cw_tx_mode=1’b1时，该系数作为初始发送的起始加权系数。
                                                            [23:12]:Q路的加权系数
                                                            [11:0]:I路的加权系数 */
        unsigned long  reserved        : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_COM_CW_COEF_UNION;
#define WBBP_COM_CW_COEF_dsp_com_cw_coef_START  (0)
#define WBBP_COM_CW_COEF_dsp_com_cw_coef_END    (23)


/*****************************************************************************
 结构名    : WBBP_COM_CW_STEP_UNION
 结构说明  : COM_CW_STEP 寄存器结构定义。地址偏移量:0xA8C，初值:0x00000000，宽度:32
 寄存器说明: 单音加权步长
*****************************************************************************/
typedef union
{
    unsigned long      com_cw_step_reg;
    struct
    {
        unsigned long  dsp_com_cw_step : 8;  /* bit[0-7] : 当dsp_com_cw_tx_mode=1'b1时,每个周期发送结束后将加权系数增加步长后发送下一个周期，无符号数 */
        unsigned long  reserved        : 24; /* bit[8-31]: 保留 */
    } reg;
} WBBP_COM_CW_STEP_UNION;
#define WBBP_COM_CW_STEP_dsp_com_cw_step_START  (0)
#define WBBP_COM_CW_STEP_dsp_com_cw_step_END    (7)


/*****************************************************************************
 结构名    : WBBP_CW_PRE_SEL_UNION
 结构说明  : CW_PRE_SEL 寄存器结构定义。地址偏移量:0xA90，初值:0x00000000，宽度:32
 寄存器说明: nco预充选择
*****************************************************************************/
typedef union
{
    unsigned long      cw_pre_sel_reg;
    struct
    {
        unsigned long  dsp_cw_pre_sel : 1;  /* bit[0]   : nco模块da_on选择，用来做nco预充。当dsp_cw_pre_sel==1'b0时，选择rrc da_on信号，正常模式下使用；dsp_cw_pre_sel==1'b1时，选择dsp_nco_en信号，供削波前单音校准时使用。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_CW_PRE_SEL_UNION;
#define WBBP_CW_PRE_SEL_dsp_cw_pre_sel_START  (0)
#define WBBP_CW_PRE_SEL_dsp_cw_pre_sel_END    (0)


/*****************************************************************************
 结构名    : WBBP_ULFE_DCUPA_EN_RPT_UNION
 结构说明  : ULFE_DCUPA_EN_RPT 寄存器结构定义。地址偏移量:0xA94，初值:0x00000000，宽度:32
 寄存器说明: DCUPA激活状态上报
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_dcupa_en_rpt_reg;
    struct
    {
        unsigned long  ulfe_dcupa_en_rpt : 1;  /* bit[0]   : 上行前端dcupa激活状态上报。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_ULFE_DCUPA_EN_RPT_UNION;
#define WBBP_ULFE_DCUPA_EN_RPT_ulfe_dcupa_en_rpt_START  (0)
#define WBBP_ULFE_DCUPA_EN_RPT_ulfe_dcupa_en_rpt_END    (0)


/*****************************************************************************
 结构名    : WBBP_ULFE_DPD_RPT_UNION
 结构说明  : ULFE_DPD_RPT 寄存器结构定义。地址偏移量:0xA98，初值:0x00000000，宽度:32
 寄存器说明: DPD相关状态上报
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_dpd_rpt_reg;
    struct
    {
        unsigned long  uplink_tx_power_db_rpt : 11; /* bit[0-10] : 上行理论发射功率 */
        unsigned long  reserved_0             : 1;  /* bit[11]   : 保留 */
        unsigned long  act_nom_error_rpt      : 11; /* bit[12-22]: 上行最大理论发射功率修正值 */
        unsigned long  reserved_1             : 1;  /* bit[23]   : 保留 */
        unsigned long  dpd_table_sel_rpt      : 3;  /* bit[24-26]: 上行DPD子表选择，范围0~7 */
        unsigned long  reserved_2             : 5;  /* bit[27-31]: 保留 */
    } reg;
} WBBP_ULFE_DPD_RPT_UNION;
#define WBBP_ULFE_DPD_RPT_uplink_tx_power_db_rpt_START  (0)
#define WBBP_ULFE_DPD_RPT_uplink_tx_power_db_rpt_END    (10)
#define WBBP_ULFE_DPD_RPT_act_nom_error_rpt_START       (12)
#define WBBP_ULFE_DPD_RPT_act_nom_error_rpt_END         (22)
#define WBBP_ULFE_DPD_RPT_dpd_table_sel_rpt_START       (24)
#define WBBP_ULFE_DPD_RPT_dpd_table_sel_rpt_END         (26)


/*****************************************************************************
 结构名    : WBBP_ATTEN_TABLE_ADDR_RPT_UNION
 结构说明  : ATTEN_TABLE_ADDR_RPT 寄存器结构定义。地址偏移量:0xA9C，初值:0x00000000，宽度:32
 寄存器说明: 上行前端RF回退索引值上报
*****************************************************************************/
typedef union
{
    unsigned long      atten_table_addr_rpt_reg;
    struct
    {
        unsigned long  atten_table_addr_rpt : 9;  /* bit[0-8] : 上行前端RF回退索引值上报。 */
        unsigned long  reserved             : 23; /* bit[9-31]: 保留 */
    } reg;
} WBBP_ATTEN_TABLE_ADDR_RPT_UNION;
#define WBBP_ATTEN_TABLE_ADDR_RPT_atten_table_addr_rpt_START  (0)
#define WBBP_ATTEN_TABLE_ADDR_RPT_atten_table_addr_rpt_END    (8)


/***======================================================================***
                     (8/10) register_define_irm_cs
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_IRM_CS_RAM_CTRL_UNION
 结构说明  : IRM_CS_RAM_CTRL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_cs_ram_ctrl_reg;
    struct
    {
        unsigned long  irm_cs_ram_ctrl : 3;  /* bit[0-2] : 用于irm_cs模式选择，影响irm_cs内部时钟切换和模式切换，默认都为0。
                                                           3'b001，UMTS模式（包括均衡，译码R99相关RAM）；
                                                           3'b010，无意义（原为LTE模式上行HARQ部分）；
                                                           3'b100，CDMA模式；
                                                           3'b000，无（default）。 */
        unsigned long  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_IRM_CS_RAM_CTRL_UNION;
#define WBBP_IRM_CS_RAM_CTRL_irm_cs_ram_ctrl_START  (0)
#define WBBP_IRM_CS_RAM_CTRL_irm_cs_ram_ctrl_END    (2)


/*****************************************************************************
 结构名    : WBBP_IRM_CS_CLK_BYPASS_UNION
 结构说明  : IRM_CS_CLK_BYPASS 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_cs_clk_bypass_reg;
    struct
    {
        unsigned long  irm_cs_clk_bypass : 1;  /* bit[0]   : irm_cs模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_IRM_CS_CLK_BYPASS_UNION;
#define WBBP_IRM_CS_CLK_BYPASS_irm_cs_clk_bypass_START  (0)
#define WBBP_IRM_CS_CLK_BYPASS_irm_cs_clk_bypass_END    (0)


/*****************************************************************************
 结构名    : WBBP_MEM_CTRL0_CS_UNION
 结构说明  : MEM_CTRL0_CS 寄存器结构定义。地址偏移量:0x00C，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl0_cs_reg;
    struct
    {
        unsigned long  mem_ctrl_s_cs      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned long  mem_ctrl_d_1w2r_cs : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} WBBP_MEM_CTRL0_CS_UNION;
#define WBBP_MEM_CTRL0_CS_mem_ctrl_s_cs_START       (0)
#define WBBP_MEM_CTRL0_CS_mem_ctrl_s_cs_END         (15)
#define WBBP_MEM_CTRL0_CS_mem_ctrl_d_1w2r_cs_START  (16)
#define WBBP_MEM_CTRL0_CS_mem_ctrl_d_1w2r_cs_END    (31)


/*****************************************************************************
 结构名    : WBBP_MEM_CTRL1_CS_UNION
 结构说明  : MEM_CTRL1_CS 寄存器结构定义。地址偏移量:0x010，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl1_cs_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_cs : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned long  rom_ctrl_cs          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned long  reserved             : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MEM_CTRL1_CS_UNION;
#define WBBP_MEM_CTRL1_CS_mem_ctrl_d_1rw2rw_cs_START  (0)
#define WBBP_MEM_CTRL1_CS_mem_ctrl_d_1rw2rw_cs_END    (15)
#define WBBP_MEM_CTRL1_CS_rom_ctrl_cs_START           (16)
#define WBBP_MEM_CTRL1_CS_rom_ctrl_cs_END             (23)


/***======================================================================***
                     (9/10) register_define_dump
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_DUMP_EN_W_UNION
 结构说明  : DUMP_EN_W 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_en_w_reg;
    struct
    {
        unsigned long  dump_en_w : 1;  /* bit[0]   : 采数模块总使能，并控制时钟门控，无论哪种模式采数，首先要配置此信号有效 */
        unsigned long  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DUMP_EN_W_UNION;
#define WBBP_DUMP_EN_W_dump_en_w_START  (0)
#define WBBP_DUMP_EN_W_dump_en_w_END    (0)


/*****************************************************************************
 结构名    : WBBP_DUMP_CLKGATE_BYPASS_W_UNION
 结构说明  : DUMP_CLKGATE_BYPASS_W 寄存器结构定义。地址偏移量:0x0144，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_clkgate_bypass_w_reg;
    struct
    {
        unsigned long  dump_bbp_clkgate_bypass_w : 1;  /* bit[0]   : 门控bypass，1表示时钟常开，即门控bypass */
        unsigned long  dump_imi_clkgate_bypass_w : 1;  /* bit[1]   : 门控bypass，1表示时钟常开，即门控bypass */
        unsigned long  dump_axi_clkgate_bypass   : 1;  /* bit[2]   : 门控bypass，1表示时钟常开，即门控bypass */
        unsigned long  reserved                  : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_DUMP_CLKGATE_BYPASS_W_UNION;
#define WBBP_DUMP_CLKGATE_BYPASS_W_dump_bbp_clkgate_bypass_w_START  (0)
#define WBBP_DUMP_CLKGATE_BYPASS_W_dump_bbp_clkgate_bypass_w_END    (0)
#define WBBP_DUMP_CLKGATE_BYPASS_W_dump_imi_clkgate_bypass_w_START  (1)
#define WBBP_DUMP_CLKGATE_BYPASS_W_dump_imi_clkgate_bypass_w_END    (1)
#define WBBP_DUMP_CLKGATE_BYPASS_W_dump_axi_clkgate_bypass_START    (2)
#define WBBP_DUMP_CLKGATE_BYPASS_W_dump_axi_clkgate_bypass_END      (2)


/*****************************************************************************
 结构名    : WBBP_DUMP_FIFO_CLR_W_UNION
 结构说明  : DUMP_FIFO_CLR_W 寄存器结构定义。地址偏移量:0x0148，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_fifo_clr_w_reg;
    struct
    {
        unsigned long  dump_fifo_clr_w : 1;  /* bit[0]   : 采数FIFO初始化清零脉冲 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DUMP_FIFO_CLR_W_UNION;
#define WBBP_DUMP_FIFO_CLR_W_dump_fifo_clr_w_START  (0)
#define WBBP_DUMP_FIFO_CLR_W_dump_fifo_clr_w_END    (0)


/*****************************************************************************
 结构名    : WBBP_DUMP_START_TIME_W_UNION
 结构说明  : DUMP_START_TIME_W 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_start_time_w_reg;
    struct
    {
        unsigned long  dump_start_time_clk_w  : 4;  /* bit[0-3]  : 采数起始位置，32’hffffffff表示立即启动
                                                                   [3:0]：chip内clk位置 */
        unsigned long  dump_start_time_chip_w : 12; /* bit[4-15] : 采数起始位置，32’hffffffff表示立即启动
                                                                   [15:4]：slot内chip位置； */
        unsigned long  dump_start_time_slot_w : 4;  /* bit[16-19]: 采数起始位置，32’hffffffff表示立即启动
                                                                   [19:16]：帧内slot位置； */
        unsigned long  dump_start_time_cfn_w  : 12; /* bit[20-31]: 采数起始位置，32’hffffffff表示立即启动
                                                                   [31:20]：CFN位置；
                                                                   
                                                                   C模下，bit[28:0]表示c_base_cnt上的位置，bit[31:29]配置为0。 */
    } reg;
} WBBP_DUMP_START_TIME_W_UNION;
#define WBBP_DUMP_START_TIME_W_dump_start_time_clk_w_START   (0)
#define WBBP_DUMP_START_TIME_W_dump_start_time_clk_w_END     (3)
#define WBBP_DUMP_START_TIME_W_dump_start_time_chip_w_START  (4)
#define WBBP_DUMP_START_TIME_W_dump_start_time_chip_w_END    (15)
#define WBBP_DUMP_START_TIME_W_dump_start_time_slot_w_START  (16)
#define WBBP_DUMP_START_TIME_W_dump_start_time_slot_w_END    (19)
#define WBBP_DUMP_START_TIME_W_dump_start_time_cfn_w_START   (20)
#define WBBP_DUMP_START_TIME_W_dump_start_time_cfn_w_END     (31)


/*****************************************************************************
 结构名    : WBBP_DUMP_FIFO_WATERMARKER_W_UNION
 结构说明  : DUMP_FIFO_WATERMARKER_W 寄存器结构定义。地址偏移量:0x0154，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_fifo_watermarker_w_reg;
    struct
    {
        unsigned long  dump_fifo_watermarker_w : 3;  /* bit[0-2] : 0：表示水线深度2；
                                                                   1：表示水线深度4；
                                                                   2：表示水线深度8；
                                                                   3：表示水线深度16；
                                                                   4：表示水线深度32；
                                                                   5：表示水线深度64；
                                                                   6：表示水线深度128； */
        unsigned long  reserved                : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_DUMP_FIFO_WATERMARKER_W_UNION;
#define WBBP_DUMP_FIFO_WATERMARKER_W_dump_fifo_watermarker_w_START  (0)
#define WBBP_DUMP_FIFO_WATERMARKER_W_dump_fifo_watermarker_w_END    (2)


/*****************************************************************************
 结构名    : WBBP_DUMP_START_W_UNION
 结构说明  : DUMP_START_W 寄存器结构定义。地址偏移量:0x0158，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_start_w_reg;
    struct
    {
        unsigned long  dump_start_w : 1;  /* bit[0]   : 软件启动数据采集，在dump_en有效的情况下起作用，wclr信号 */
        unsigned long  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DUMP_START_W_UNION;
#define WBBP_DUMP_START_W_dump_start_w_START  (0)
#define WBBP_DUMP_START_W_dump_start_w_END    (0)


/*****************************************************************************
 结构名    : WBBP_DUMP_STOP_W_UNION
 结构说明  : DUMP_STOP_W 寄存器结构定义。地址偏移量:0x015C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_stop_w_reg;
    struct
    {
        unsigned long  dump_stop_w : 1;  /* bit[0]   : 软件强制结束数据采集，wclr信号 */
        unsigned long  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DUMP_STOP_W_UNION;
#define WBBP_DUMP_STOP_W_dump_stop_w_START  (0)
#define WBBP_DUMP_STOP_W_dump_stop_w_END    (0)


/*****************************************************************************
 结构名    : WBBP_DUMP_FLOW_UNION
 结构说明  : DUMP_FLOW 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_flow_reg;
    struct
    {
        unsigned long  dump_underflow : 1;  /* bit[0]   : 采数FIFO下溢 */
        unsigned long  dump_overflow  : 1;  /* bit[1]   : 采数FIFO上溢 */
        unsigned long  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DUMP_FLOW_UNION;
#define WBBP_DUMP_FLOW_dump_underflow_START  (0)
#define WBBP_DUMP_FLOW_dump_underflow_END    (0)
#define WBBP_DUMP_FLOW_dump_overflow_START   (1)
#define WBBP_DUMP_FLOW_dump_overflow_END     (1)


/*****************************************************************************
 结构名    : WBBP_DUMP_FLOW_CLR_UNION
 结构说明  : DUMP_FLOW_CLR 寄存器结构定义。地址偏移量:0x0164，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dump_flow_clr_reg;
    struct
    {
        unsigned long  dump_flow_clr : 1;  /* bit[0]   : 采数FIFO溢出清零 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_DUMP_FLOW_CLR_UNION;
#define WBBP_DUMP_FLOW_CLR_dump_flow_clr_START  (0)
#define WBBP_DUMP_FLOW_CLR_dump_flow_clr_END    (0)


/***======================================================================***
                     (10/10) register_define_dbg
 ***======================================================================***/
/*****************************************************************************
 结构名    : WBBP_BBP_DBG_EN_UNION
 结构说明  : BBP_DBG_EN 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_dbg_en_reg;
    struct
    {
        unsigned long  bbp_dbg_en : 1;  /* bit[0]   : DBG上报使能，1表示打开上报功能，0表示关闭上报功能。完成时钟门控 */
        unsigned long  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_BBP_DBG_EN_UNION;
#define WBBP_BBP_DBG_EN_bbp_dbg_en_START  (0)
#define WBBP_BBP_DBG_EN_bbp_dbg_en_END    (0)


/*****************************************************************************
 结构名    : WBBP_BBP_DBG_BYPASS_UNION
 结构说明  : BBP_DBG_BYPASS 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_dbg_bypass_reg;
    struct
    {
        unsigned long  w_fe_clkgate_bypass    : 1;  /* bit[0]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  g1_fe_clkgate_bypass   : 1;  /* bit[1]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  comm_clkgate_bypass    : 1;  /* bit[2]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  cbbp_clkgate_bypass    : 1;  /* bit[3]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  bbp_if_clkgate_bypass  : 1;  /* bit[4]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  wbbp_clkgate_bypass    : 1;  /* bit[5]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  gbbp1_clkgate_bypass   : 1;  /* bit[6]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  dbg_in_clkgate_bypass  : 1;  /* bit[7]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  dbg_out_clkgate_bypass : 1;  /* bit[8]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  dbg_axi_clkgate_bypass : 1;  /* bit[9]    : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  g2_fe_clkgate_bypass   : 1;  /* bit[10]   : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  gbbp2_clkgate_bypass   : 1;  /* bit[11]   : 时钟bypass使能，1表示时钟常开，0表示时钟门控有效 */
        unsigned long  reserved               : 20; /* bit[12-31]: 保留 */
    } reg;
} WBBP_BBP_DBG_BYPASS_UNION;
#define WBBP_BBP_DBG_BYPASS_w_fe_clkgate_bypass_START     (0)
#define WBBP_BBP_DBG_BYPASS_w_fe_clkgate_bypass_END       (0)
#define WBBP_BBP_DBG_BYPASS_g1_fe_clkgate_bypass_START    (1)
#define WBBP_BBP_DBG_BYPASS_g1_fe_clkgate_bypass_END      (1)
#define WBBP_BBP_DBG_BYPASS_comm_clkgate_bypass_START     (2)
#define WBBP_BBP_DBG_BYPASS_comm_clkgate_bypass_END       (2)
#define WBBP_BBP_DBG_BYPASS_cbbp_clkgate_bypass_START     (3)
#define WBBP_BBP_DBG_BYPASS_cbbp_clkgate_bypass_END       (3)
#define WBBP_BBP_DBG_BYPASS_bbp_if_clkgate_bypass_START   (4)
#define WBBP_BBP_DBG_BYPASS_bbp_if_clkgate_bypass_END     (4)
#define WBBP_BBP_DBG_BYPASS_wbbp_clkgate_bypass_START     (5)
#define WBBP_BBP_DBG_BYPASS_wbbp_clkgate_bypass_END       (5)
#define WBBP_BBP_DBG_BYPASS_gbbp1_clkgate_bypass_START    (6)
#define WBBP_BBP_DBG_BYPASS_gbbp1_clkgate_bypass_END      (6)
#define WBBP_BBP_DBG_BYPASS_dbg_in_clkgate_bypass_START   (7)
#define WBBP_BBP_DBG_BYPASS_dbg_in_clkgate_bypass_END     (7)
#define WBBP_BBP_DBG_BYPASS_dbg_out_clkgate_bypass_START  (8)
#define WBBP_BBP_DBG_BYPASS_dbg_out_clkgate_bypass_END    (8)
#define WBBP_BBP_DBG_BYPASS_dbg_axi_clkgate_bypass_START  (9)
#define WBBP_BBP_DBG_BYPASS_dbg_axi_clkgate_bypass_END    (9)
#define WBBP_BBP_DBG_BYPASS_g2_fe_clkgate_bypass_START    (10)
#define WBBP_BBP_DBG_BYPASS_g2_fe_clkgate_bypass_END      (10)
#define WBBP_BBP_DBG_BYPASS_gbbp2_clkgate_bypass_START    (11)
#define WBBP_BBP_DBG_BYPASS_gbbp2_clkgate_bypass_END      (11)


/*****************************************************************************
 结构名    : WBBP_BBP_IF_SEL_UNION
 结构说明  : BBP_IF_SEL 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_if_sel_reg;
    struct
    {
        unsigned long  bbp_if_sel : 2;  /* bit[0-1] : BBP接口选择信号
                                                      0：表示选择LocalBus，即监测所有BBP配置信息
                                                      1：表示选择WBBP IMI接口，即仅监测WBBP配置信息
                                                      2：表示选择GBBP1 IMI接口，即仅监测GBBP配置信息
                                                      3：保留不用
                                                      在V8R1中只有0值才有意义 */
        unsigned long  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_BBP_IF_SEL_UNION;
#define WBBP_BBP_IF_SEL_bbp_if_sel_START  (0)
#define WBBP_BBP_IF_SEL_bbp_if_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_DBG_DDR_2K_NO_UNION
 结构说明  : DBG_DDR_2K_NO 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_ddr_2k_no_reg;
    struct
    {
        unsigned long  dbg_ddr_2k_no : 4;  /* bit[0-3] : DDR中DBG空间大小，2Kbyte为单位。如配置为4表示DBG空间为4个2Kbyte。 */
        unsigned long  reserved      : 28; /* bit[4-31]: 保留 */
    } reg;
} WBBP_DBG_DDR_2K_NO_UNION;
#define WBBP_DBG_DDR_2K_NO_dbg_ddr_2k_no_START  (0)
#define WBBP_DBG_DDR_2K_NO_dbg_ddr_2k_no_END    (3)


/*****************************************************************************
 结构名    : WBBP_DBG_CLK_IN_SEL_UNION
 结构说明  : DBG_CLK_IN_SEL 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_clk_in_sel_reg;
    struct
    {
        unsigned long  dbg_clk_in_sel : 2;  /* bit[0-1] : DBG输入时钟选择：
                                                          0：表示使用模式一时钟；
                                                          1：表示使用模式二时钟；
                                                          2：表示使用模式三时钟； */
        unsigned long  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} WBBP_DBG_CLK_IN_SEL_UNION;
#define WBBP_DBG_CLK_IN_SEL_dbg_clk_in_sel_START  (0)
#define WBBP_DBG_CLK_IN_SEL_dbg_clk_in_sel_END    (1)


/*****************************************************************************
 结构名    : WBBP_DBG_TIMING_SEL_UNION
 结构说明  : DBG_TIMING_SEL 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_timing_sel_reg;
    struct
    {
        unsigned long  dbg_comm_timing_sel    : 2;  /* bit[0-1] : COMM信息使用时间戳选择
                                                                  0表示使用WBBP定时
                                                                  1表示使用GBBP定时
                                                                  2 表示使用CBBP定时 */
        unsigned long  dbg_comm_if_timing_sel : 2;  /* bit[2-3] : COMM接口信息使用时间戳选择
                                                                  0表示使用WBBP定时
                                                                  1表示使用GBBP定时
                                                                  2 表示使用CBBP定时 */
        unsigned long  reserved               : 28; /* bit[4-31]: 保留 */
    } reg;
} WBBP_DBG_TIMING_SEL_UNION;
#define WBBP_DBG_TIMING_SEL_dbg_comm_timing_sel_START     (0)
#define WBBP_DBG_TIMING_SEL_dbg_comm_timing_sel_END       (1)
#define WBBP_DBG_TIMING_SEL_dbg_comm_if_timing_sel_START  (2)
#define WBBP_DBG_TIMING_SEL_dbg_comm_if_timing_sel_END    (3)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR0_START_UNION
 结构说明  : MASK_ADDR0_START 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr0_start_reg;
    struct
    {
        unsigned long  mask_addr0_start : 24; /* bit[0-23] : 第一段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR0_START_UNION;
#define WBBP_MASK_ADDR0_START_mask_addr0_start_START  (0)
#define WBBP_MASK_ADDR0_START_mask_addr0_start_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR0_END_UNION
 结构说明  : MASK_ADDR0_END 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr0_end_reg;
    struct
    {
        unsigned long  mask_addr0_end : 24; /* bit[0-23] : 第一段屏蔽地址结束位置 */
        unsigned long  reserved       : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR0_END_UNION;
#define WBBP_MASK_ADDR0_END_mask_addr0_end_START  (0)
#define WBBP_MASK_ADDR0_END_mask_addr0_end_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR1_START_UNION
 结构说明  : MASK_ADDR1_START 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr1_start_reg;
    struct
    {
        unsigned long  mask_addr1_start : 24; /* bit[0-23] : 第二段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR1_START_UNION;
#define WBBP_MASK_ADDR1_START_mask_addr1_start_START  (0)
#define WBBP_MASK_ADDR1_START_mask_addr1_start_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR1_END_UNION
 结构说明  : MASK_ADDR1_END 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr1_end_reg;
    struct
    {
        unsigned long  mask_addr1_end : 24; /* bit[0-23] : 第二段屏蔽地址结束位置 */
        unsigned long  reserved       : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR1_END_UNION;
#define WBBP_MASK_ADDR1_END_mask_addr1_end_START  (0)
#define WBBP_MASK_ADDR1_END_mask_addr1_end_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR2_START_UNION
 结构说明  : MASK_ADDR2_START 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr2_start_reg;
    struct
    {
        unsigned long  mask_addr2_start : 24; /* bit[0-23] : 第三段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR2_START_UNION;
#define WBBP_MASK_ADDR2_START_mask_addr2_start_START  (0)
#define WBBP_MASK_ADDR2_START_mask_addr2_start_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR2_END_UNION
 结构说明  : MASK_ADDR2_END 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr2_end_reg;
    struct
    {
        unsigned long  mask_addr2_end : 24; /* bit[0-23] : 第三段屏蔽地址结束位置 */
        unsigned long  reserved       : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR2_END_UNION;
#define WBBP_MASK_ADDR2_END_mask_addr2_end_START  (0)
#define WBBP_MASK_ADDR2_END_mask_addr2_end_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR3_START_UNION
 结构说明  : MASK_ADDR3_START 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr3_start_reg;
    struct
    {
        unsigned long  mask_addr3_start : 24; /* bit[0-23] : 第四段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR3_START_UNION;
#define WBBP_MASK_ADDR3_START_mask_addr3_start_START  (0)
#define WBBP_MASK_ADDR3_START_mask_addr3_start_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR3_END_UNION
 结构说明  : MASK_ADDR3_END 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr3_end_reg;
    struct
    {
        unsigned long  mask_addr3_end : 24; /* bit[0-23] : 第四段屏蔽地址结束位置 */
        unsigned long  reserved       : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR3_END_UNION;
#define WBBP_MASK_ADDR3_END_mask_addr3_end_START  (0)
#define WBBP_MASK_ADDR3_END_mask_addr3_end_END    (23)


/*****************************************************************************
 结构名    : WBBP_DBG_FIFO_WATERMARKER_UNION
 结构说明  : DBG_FIFO_WATERMARKER 寄存器结构定义。地址偏移量:0x040，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_fifo_watermarker_reg;
    struct
    {
        unsigned long  dbg_fifo_watermarker : 3;  /* bit[0-2] : DBG FIFO水线选择
                                                                0：表示水线为2；
                                                                1：表示水线为4；
                                                                2：表示水线为8；
                                                                3：表示水线为16；
                                                                4：表示水线为32；
                                                                5：表示水线为64； */
        unsigned long  reserved             : 29; /* bit[3-31]: 保留 */
    } reg;
} WBBP_DBG_FIFO_WATERMARKER_UNION;
#define WBBP_DBG_FIFO_WATERMARKER_dbg_fifo_watermarker_START  (0)
#define WBBP_DBG_FIFO_WATERMARKER_dbg_fifo_watermarker_END    (2)


/*****************************************************************************
 结构名    : WBBP_BBP_DBG_SWITCH_UNION
 结构说明  : BBP_DBG_SWITCH 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_dbg_switch_reg;
    struct
    {
        unsigned long  bbp_dbg_switch : 5;  /* bit[0-4] : DBG上报信息开关，1表示上报相应信息，0表示不上报相应信息。
                                                          bit[0]：表示w_fe_top信息是否上报；
                                                          bit[1]：表示g_fe_top信息是否上报；
                                                          bit[2]：表示BBP接口信息是否上报；
                                                          bit[3]：表示COMM信息是否上报；
                                                          bit[4]：表示COMM接口信息是否上报； */
        unsigned long  reserved       : 27; /* bit[5-31]: 保留 */
    } reg;
} WBBP_BBP_DBG_SWITCH_UNION;
#define WBBP_BBP_DBG_SWITCH_bbp_dbg_switch_START  (0)
#define WBBP_BBP_DBG_SWITCH_bbp_dbg_switch_END    (4)


/*****************************************************************************
 结构名    : WBBP_BBP_DBG_START_UNION
 结构说明  : BBP_DBG_START 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_dbg_start_reg;
    struct
    {
        unsigned long  bbp_dbg_start : 1;  /* bit[0]   : DBG打开信号，Wclr */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_BBP_DBG_START_UNION;
#define WBBP_BBP_DBG_START_bbp_dbg_start_START  (0)
#define WBBP_BBP_DBG_START_bbp_dbg_start_END    (0)


/*****************************************************************************
 结构名    : WBBP_BBP_DBG_STOP_UNION
 结构说明  : BBP_DBG_STOP 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_dbg_stop_reg;
    struct
    {
        unsigned long  bbp_dbg_stop : 1;  /* bit[0]   : DBG停止信号，Wclr */
        unsigned long  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} WBBP_BBP_DBG_STOP_UNION;
#define WBBP_BBP_DBG_STOP_bbp_dbg_stop_START  (0)
#define WBBP_BBP_DBG_STOP_bbp_dbg_stop_END    (0)


/*****************************************************************************
 结构名    : WBBP_DDR_BIT_INDEX_UNION
 结构说明  : DDR_BIT_INDEX 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ddr_bit_index_reg;
    struct
    {
        unsigned long  ddr_bit_index : 8;  /* bit[0-7] : DDR空间上报指示，1表示该空间已将上报了DBG信息，bit0表示第一段2K byte空间，bit1表示第二段2K byte空间，以此类推。 */
        unsigned long  reserved      : 24; /* bit[8-31]: 保留 */
    } reg;
} WBBP_DDR_BIT_INDEX_UNION;
#define WBBP_DDR_BIT_INDEX_ddr_bit_index_START  (0)
#define WBBP_DDR_BIT_INDEX_ddr_bit_index_END    (7)


/*****************************************************************************
 结构名    : WBBP_DDR_BIT_INDEX_CLR_UNION
 结构说明  : DDR_BIT_INDEX_CLR 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ddr_bit_index_clr_reg;
    struct
    {
        unsigned long  ddr_bit_index_clr : 8;  /* bit[0-7] : DDR上报空间清零信号，将ddr_bit_index对应bit清零 */
        unsigned long  reserved          : 24; /* bit[8-31]: 保留 */
    } reg;
} WBBP_DDR_BIT_INDEX_CLR_UNION;
#define WBBP_DDR_BIT_INDEX_CLR_ddr_bit_index_clr_START  (0)
#define WBBP_DDR_BIT_INDEX_CLR_ddr_bit_index_clr_END    (7)


/*****************************************************************************
 结构名    : WBBP_DBG_FLOW_UNION
 结构说明  : DBG_FLOW 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_flow_reg;
    struct
    {
        unsigned long  w_fe_fifo_underflow    : 1;  /* bit[0]    : W_FE  FIFO下溢 */
        unsigned long  w_fe_fifo_overflow     : 1;  /* bit[1]    : W_FE  FIFO上溢 */
        unsigned long  g_fe_fifo_underflow    : 1;  /* bit[2]    : G_FE  FIFO下溢 */
        unsigned long  g_fe_fifo_overflow     : 1;  /* bit[3]    : G_FE  FIFO上溢 */
        unsigned long  bbp_if_fifo_underflow  : 1;  /* bit[4]    : BBP接口   FIFO下溢 */
        unsigned long  bbp_if_fifo_overflow   : 1;  /* bit[5]    : BBP接口  FIFO上溢 */
        unsigned long  comm_fifo_underflow    : 1;  /* bit[6]    : BBP COMM   FIFO下溢 */
        unsigned long  comm_fifo_overflow     : 1;  /* bit[7]    : BBP COMM  FIFO上溢 */
        unsigned long  comm_if_fifo_underflow : 1;  /* bit[8]    : BBP COMM接口   FIFO下溢 */
        unsigned long  comm_if_fifo_overflow  : 1;  /* bit[9]    : BBP COMM接口  FIFO上溢 */
        unsigned long  reserved_0             : 6;  /* bit[10-15]: 保留 */
        unsigned long  bbp_dbg_fifo_underflow : 1;  /* bit[16]   : DBG   FIFO下溢 */
        unsigned long  bbp_dbg_fifo_overflow  : 1;  /* bit[17]   : DBG  FIFO上溢 */
        unsigned long  reserved_1             : 14; /* bit[18-31]: 保留 */
    } reg;
} WBBP_DBG_FLOW_UNION;
#define WBBP_DBG_FLOW_w_fe_fifo_underflow_START     (0)
#define WBBP_DBG_FLOW_w_fe_fifo_underflow_END       (0)
#define WBBP_DBG_FLOW_w_fe_fifo_overflow_START      (1)
#define WBBP_DBG_FLOW_w_fe_fifo_overflow_END        (1)
#define WBBP_DBG_FLOW_g_fe_fifo_underflow_START     (2)
#define WBBP_DBG_FLOW_g_fe_fifo_underflow_END       (2)
#define WBBP_DBG_FLOW_g_fe_fifo_overflow_START      (3)
#define WBBP_DBG_FLOW_g_fe_fifo_overflow_END        (3)
#define WBBP_DBG_FLOW_bbp_if_fifo_underflow_START   (4)
#define WBBP_DBG_FLOW_bbp_if_fifo_underflow_END     (4)
#define WBBP_DBG_FLOW_bbp_if_fifo_overflow_START    (5)
#define WBBP_DBG_FLOW_bbp_if_fifo_overflow_END      (5)
#define WBBP_DBG_FLOW_comm_fifo_underflow_START     (6)
#define WBBP_DBG_FLOW_comm_fifo_underflow_END       (6)
#define WBBP_DBG_FLOW_comm_fifo_overflow_START      (7)
#define WBBP_DBG_FLOW_comm_fifo_overflow_END        (7)
#define WBBP_DBG_FLOW_comm_if_fifo_underflow_START  (8)
#define WBBP_DBG_FLOW_comm_if_fifo_underflow_END    (8)
#define WBBP_DBG_FLOW_comm_if_fifo_overflow_START   (9)
#define WBBP_DBG_FLOW_comm_if_fifo_overflow_END     (9)
#define WBBP_DBG_FLOW_bbp_dbg_fifo_underflow_START  (16)
#define WBBP_DBG_FLOW_bbp_dbg_fifo_underflow_END    (16)
#define WBBP_DBG_FLOW_bbp_dbg_fifo_overflow_START   (17)
#define WBBP_DBG_FLOW_bbp_dbg_fifo_overflow_END     (17)


/*****************************************************************************
 结构名    : WBBP_DBG_FLOW_CLR_UNION
 结构说明  : DBG_FLOW_CLR 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dbg_flow_clr_reg;
    struct
    {
        unsigned long  w_fe_fifo_flow_clr    : 1;  /* bit[0]    : W_FE  FIFO溢出清零 */
        unsigned long  reserved_0            : 1;  /* bit[1]    : 保留 */
        unsigned long  g_fe_fifo_flow_clr    : 1;  /* bit[2]    : G_FE  FIFO溢出清零 */
        unsigned long  reserved_1            : 1;  /* bit[3]    : 保留 */
        unsigned long  bbp_if_fifo_flow_clr  : 1;  /* bit[4]    : BBP接口 FIFO溢出清零 */
        unsigned long  reserved_2            : 1;  /* bit[5]    : 保留 */
        unsigned long  comm_fifo_flow_clr    : 1;  /* bit[6]    : BBP COMM FIFO溢出清零 */
        unsigned long  reserved_3            : 1;  /* bit[7]    : 保留 */
        unsigned long  comm_if_fifo_flow_clr : 1;  /* bit[8]    : BBP COMM接口 FIFO溢出清零 */
        unsigned long  reserved_4            : 7;  /* bit[9-15] : 保留 */
        unsigned long  bbp_dbg_fifo_flow_clr : 1;  /* bit[16]   : DBG   FIFO溢出清零 */
        unsigned long  reserved_5            : 15; /* bit[17-31]: 保留 */
    } reg;
} WBBP_DBG_FLOW_CLR_UNION;
#define WBBP_DBG_FLOW_CLR_w_fe_fifo_flow_clr_START     (0)
#define WBBP_DBG_FLOW_CLR_w_fe_fifo_flow_clr_END       (0)
#define WBBP_DBG_FLOW_CLR_g_fe_fifo_flow_clr_START     (2)
#define WBBP_DBG_FLOW_CLR_g_fe_fifo_flow_clr_END       (2)
#define WBBP_DBG_FLOW_CLR_bbp_if_fifo_flow_clr_START   (4)
#define WBBP_DBG_FLOW_CLR_bbp_if_fifo_flow_clr_END     (4)
#define WBBP_DBG_FLOW_CLR_comm_fifo_flow_clr_START     (6)
#define WBBP_DBG_FLOW_CLR_comm_fifo_flow_clr_END       (6)
#define WBBP_DBG_FLOW_CLR_comm_if_fifo_flow_clr_START  (8)
#define WBBP_DBG_FLOW_CLR_comm_if_fifo_flow_clr_END    (8)
#define WBBP_DBG_FLOW_CLR_bbp_dbg_fifo_flow_clr_START  (16)
#define WBBP_DBG_FLOW_CLR_bbp_dbg_fifo_flow_clr_END    (16)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR4_START_UNION
 结构说明  : MASK_ADDR4_START 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr4_start_reg;
    struct
    {
        unsigned long  mask_addr4_start : 24; /* bit[0-23] : 第五段屏蔽地址起始位置，被屏蔽地址段内CPU操作不作为DBG信息上报 */
        unsigned long  reserved         : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR4_START_UNION;
#define WBBP_MASK_ADDR4_START_mask_addr4_start_START  (0)
#define WBBP_MASK_ADDR4_START_mask_addr4_start_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR4_END_UNION
 结构说明  : MASK_ADDR4_END 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr4_end_reg;
    struct
    {
        unsigned long  mask_addr4_end : 24; /* bit[0-23] : 第五段屏蔽地址结束位置 */
        unsigned long  reserved       : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR4_END_UNION;
#define WBBP_MASK_ADDR4_END_mask_addr4_end_START  (0)
#define WBBP_MASK_ADDR4_END_mask_addr4_end_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR5_UNION
 结构说明  : MASK_ADDR5 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr5_reg;
    struct
    {
        unsigned long  mask_addr5 : 24; /* bit[0-23] : 第六段屏蔽地址，单个地址被屏蔽 */
        unsigned long  reserved   : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR5_UNION;
#define WBBP_MASK_ADDR5_mask_addr5_START  (0)
#define WBBP_MASK_ADDR5_mask_addr5_END    (23)


/*****************************************************************************
 结构名    : WBBP_MASK_ADDR6_UNION
 结构说明  : MASK_ADDR6 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mask_addr6_reg;
    struct
    {
        unsigned long  mask_addr6 : 24; /* bit[0-23] : 第七段屏蔽地址，单个地址被屏蔽 */
        unsigned long  reserved   : 8;  /* bit[24-31]: 保留 */
    } reg;
} WBBP_MASK_ADDR6_UNION;
#define WBBP_MASK_ADDR6_mask_addr6_START  (0)
#define WBBP_MASK_ADDR6_mask_addr6_END    (23)




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

#endif /* end of bbp_wcdma_fe_interface.h */
