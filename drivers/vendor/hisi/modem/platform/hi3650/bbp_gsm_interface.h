/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_gsm_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-03 15:59:55
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月3日
    作    者   : l00165286
    修改内容   : 从《K3V5 MODEM寄存器手册_GSM.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSM_INTERFACE_H__
#define __BBP_GSM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/9) register_define_gbbp_addr
 ***======================================================================***/
/* 寄存器说明：
 bit[31]     物理层软件计算AFC值使能信号，电平信号，高有效。在此信号为高期间，GBBP不在进行AFC锁定判断，输出给VCO的值由cpu_soft_afc_value[13:0]提供。
 bit[30:14]  保留
 bit[13:0]   物理层软件计算AFC值，在cpu_soft_afc_renew有效时，将此值输出给VCO。
   UNION结构:  GBBP_CPU_SOFT_AFC_VALUE_UNION */
#define GBBP_CPU_SOFT_AFC_VALUE_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      物理层软件启动更新AFC值，脉冲信号。此信号在cpu_soft_afc_en_imi为高时才有效，写1逻辑自清零。
   UNION结构:  GBBP_CPU_SOFT_VALUE_RENEW_UNION */
#define GBBP_CPU_SOFT_VALUE_RENEW_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1004)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  8PSK调制方式下，CI判决门限选择信号，用于筛选nb-afc的输出。小于该门限，afc_valui_i和afc_value_q都输出0，否则输出真实值。
             cpu_gmsk_ci_thres[2:0]=0 C>I
             cpu_gmsk_ci_thres[2:0]=1 C>4I
             cpu_gmsk_ci_thres[2:0]=2 C>8I
             cpu_gmsk_ci_thres[2:0]=3 C>16I
             cpu_gmsk_ci_thres[2:0]=4 C>32I
             cpu_gmsk_ci_thres[2:0]=5 C>64I
             cpu_gmsk_ci_thres[2:0]=6 C>128I
             cpu_gmsk_ci_thres[2:0]=7 不判决，直接输出。
             默认值是3。
 bit[15:3]   保留
 bit[2:0]    GMSK调制方式下，CI判决门限选择信号，用于筛选nb-afc的输出。小于该门限，afc_valui_i和afc_value_q都输出0，否则输出真实值。
             cpu_psk_ci_thres[2:0]=0 C>I
             cpu_psk_ci_thres[2:0]=1 C>4I
             cpu_psk_ci_thres[2:0]=2 C>8I
             cpu_psk_ci_thres[2:0]=3 C>16I
             cpu_psk_ci_thres[2:0]=4 C>32I
             cpu_psk_ci_thres[2:0]=5 C>64I
             cpu_psk_ci_thres[2:0]=6 C>128I
             cpu_psk_ci_thres[2:0]=7 不判决，直接输出。
             默认值是3。
   UNION结构:  GBBP_CPU_CI_THRES_CFG_UNION */
#define GBBP_CPU_CI_THRES_CFG_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1008)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    一阶环用于计算NB-AFC的NB个数选择信号：
             0：表示选择1个NB来计算；
             1：表示选择2个NB来计算；
             2：表示选择4个NB来计算；
             3：表示选择8个NB来计算；
             4：表示选择16个NB来计算；
             5：表示选择32个NB来计算；
             6：表示选择64个NB来计算。
             非DRX期间推荐配置2，DRX期间推荐配置为0。
   UNION结构:  GBBP_CPU_NB_AFC_NUM_UNION */
#define GBBP_CPU_NB_AFC_NUM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x100C)

/* 寄存器说明：
 bit[31]     FB-AFC清零信号，写1生效，逻辑自清零
 bit[30:16]  保留
 bit[15]     AFC初始值写入使能，CPU写1，逻辑自清零。
 bit[14]     保留
 bit[13:0]   G AFC初始值。
             当RFCMOS使用晶体方案时，配置该值为14'h1fff（详见V3R2晶体系统方案）；其他方案时，使用原来的配置值。
   UNION结构:  GBBP_CPU_AFC_CFG_UNION */
#define GBBP_CPU_AFC_CFG_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1010)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   上报的afc实部相关累加值，直接由乘累加模块输出，测试用。
   UNION结构:  GBBP_AFC_VALUE_I_CPU_UNION */
#define GBBP_AFC_VALUE_I_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1014)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   上报的afc虚部相关累加值，直接由乘累加模块输出，测试用。
   UNION结构:  GBBP_AFC_VALUE_Q_CPU_UNION */
#define GBBP_AFC_VALUE_Q_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1018)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    0表示使用10bit的PDM转换模块；
             1表示使用12bit的PDM转换模块；
             2表示使用14bit的PDM转换模块。
   UNION结构:  GBBP_CPU_AFC_PWM_WIDTH_SEL_UNION */
#define GBBP_CPU_AFC_PWM_WIDTH_SEL_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x101C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      表示重新开始统计NB-AFC的NB-BURST个数，cpu写1，逻辑自清零。
             此时不输出当前累计NB个数对应的NB-AFC滤波值。建议先改变cpu_nb_afc_num后配置此值为1。
   UNION结构:  GBBP_CPU_NB_AFC_NUM_CLR_UNION */
#define GBBP_CPU_NB_AFC_NUM_CLR_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1020)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:16]  用于FB-AFC判决的总的FB个数，可配范围为：17~31
             默认配置为：22
 bit[15:0]   保留
   UNION结构:  GBBP_CPU_FB_KP_KINT_UNION */
#define GBBP_CPU_FB_KP_KINT_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1024)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  滞后FB1215QB处timebase的FN模2048计数，计数范围：0~2047测试用。
 bit[15:13]  保留
 bit[12:0]   滞后FB1215QB处timebase的QB计数，测试用。
   UNION结构:  GBBP_FB_TIMEBASE_RPT_UNION */
#define GBBP_FB_TIMEBASE_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1028)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  FB所在帧位置T1计数器上报。
 bit[15:13]  保留
 bit[12:8]   FB所在帧位置T2计数器上报。
 bit[7:6]    保留
 bit[5:0]    FB所在帧位置T3计数器上报。
   UNION结构:  GBBP_FB_FN_RPT_UNION */
#define GBBP_FB_FN_RPT_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x102C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:12]  FB搜索窗的符号个数门限值。
             缺省值为17'd13906（对应11帧+1时隙）。当搜索的时间长度大于该值时，FB搜索结束。
             注：13906=11*1250+156
 bit[11:6]   保留
 bit[5:4]    SB同步失败次数门限。
             2'd0：使用的门限值为1；
             2'd1：使用的门限值为2；
             2'd2：使用的门限值为3；
             其他：无效。
             缺省值为2'd1。
 bit[3:2]    保留
 bit[1:0]    FB同步失败次数门限。
             2'd0：使用的门限值为1；
             2'd1：使用的门限值为2；
             2'd2：使用的门限值为3；
             2'd3：使用的门限值为4。
             缺省值为2'd1。
   UNION结构:  GBBP_CPU_FB_TIMES_THRES_UNION */
#define GBBP_CPU_FB_TIMES_THRES_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1030)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:12]  FB搜索成功的门限，当FB搜索得到的能量的最大值大于该门限时，才认为搜索成功，缺省值为512。
 bit[11:0]   保留
   UNION结构:  GBBP_CPU_FB_ENERG_THRES_UNION */
#define GBBP_CPU_FB_ENERG_THRES_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1034)

/* 寄存器说明：
 bit[31:16]  AFC输出的16比特VCTXO的控制电压信号
 bit[15:14]  保留
 bit[13:0]   AFC输出的VCTXO控制电压。
   UNION结构:  GBBP_AFC_RPT_UNION */
#define GBBP_AFC_RPT_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x1038)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  SB搜索位置相对于FB位置的偏移量
 bit[15:13]  保留
 bit[12:0]   FB搜索得到的FB时隙头位置，相对于gtc_timebase的位置。
   UNION结构:  GBBP_FB_RPT1_UNION */
#define GBBP_FB_RPT1_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x103C)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   本轮FB搜索的最大能量值，测试用。
   UNION结构:  GBBP_FB_RPT2_UNION */
#define GBBP_FB_RPT2_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x1040)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  搜索状态机上报信号，
             0：Idle State；
             1：FB搜索状态；
             2：AFC判断状态；
             3：SB搜索状态。
 bit[15:13]  保留
 bit[12:0]   SB搜索能量最大值相对于timebase的位置，若SB搜索失败，则上报值无效。
   UNION结构:  GBBP_SB_POS_RPT1_UNION */
#define GBBP_SB_POS_RPT1_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1044)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   SB搜索能量值的最大值，测试用。
   UNION结构:  GBBP_SB_SQUARE_RPT1_UNION */
#define GBBP_SB_SQUARE_RPT1_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1048)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   SB搜索能量次大值相对于timebase的位置。
   UNION结构:  GBBP_SB_POS_RPT2_UNION */
#define GBBP_SB_POS_RPT2_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x104C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   SB搜索能量值的次大值，测试用。
   UNION结构:  GBBP_SB_SQUARE_RPT2_UNION */
#define GBBP_SB_SQUARE_RPT2_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1050)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   SB搜索能量第三大值相对于timebase的位置。
   UNION结构:  GBBP_SB_POS_RPT3_UNION */
#define GBBP_SB_POS_RPT3_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1054)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   SB搜索能量值的第三大值，测试用。
   UNION结构:  GBBP_SB_SQUARE_RPT3_UNION */
#define GBBP_SB_SQUARE_RPT3_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1058)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  
 bit[15:12]  保留
 bit[11:8]   搜索中断状态，即反应产生中断的原因。此信号当int_srch_sync_cpu有效后有效，测试用。各bit含义如下，
             C01搜索流程版本：
             4'd0：搜索正常结束；
             4'd1：FB未同步；
             4'd2：AFC未锁定；
             4'd3：SB译码错误；
             4'd5：错误的搜索模式设置，即3'b000；
             4'd6：在正常搜索过程中搜索使能信号gsp_srch_en变低。
             111搜索优化流程版本：
             4'd1：FB未同步；
             4'd7：111搜索模式优化下，当FB-AFC锁定下，SB译码失败超出门限，导致搜索失败；
             4'd8：111搜索模式优化下，当FB-AFC未锁定下，FB-AFC调整次数超出门限，导致搜索失败；
             4'd9：111搜索模式优化下，多次SB译码成功但BSIC值不同，SB译码成功次数超出门限，导致搜索失败；
             测试用。
 bit[7:6]    保留
 bit[5:4]    乘累加模块搜索过程状态上报，测试用。
 bit[3:0]    乘累加状态上报，
             4'd0：空闲状态；
             4'd1：同步搜索状态；
             4'd2：NB盲检测及同步位置更新；
             4'd3：预滤波；
             4'd4：TVB均衡解调；
             4'd5：VALPP软判。
             测试用。
   UNION结构:  GBBP_STATE_RPT_UNION */
#define GBBP_STATE_RPT_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x105C)

/* 寄存器说明：
 bit[31]     当前搜索小区类型上报，
             0：表示服务小区；
             1：表示邻区。
 bit[30:28]  搜索启动时，gsp_srch_mod上报。
 bit[27:19]  保留
 bit[18:16]  搜索中断时，gsp_srch_mod上报。
 bit[15:13]  保留
 bit[12:0]   搜索中断所在gtc_timebase上报。
   UNION结构:  GBBP_SRCH_QB_RPT_UNION */
#define GBBP_SRCH_QB_RPT_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1064)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  搜索中断所在位置的gtc_fn_high上报。
 bit[15:11]  保留
 bit[10:0]   搜索中断所在位置的gtc_fn_low上报。
   UNION结构:  GBBP_SRCH_FN_RPT_UNION */
#define GBBP_SRCH_FN_RPT_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x106C)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    001搜索模式下，SB提前接收符号的个数，即在SB之前多接受cpu_sb_advance_len个符号，可配0~34。
   UNION结构:  GBBP_SB_ADVANCE_LEN_CFG_UNION */
#define GBBP_SB_ADVANCE_LEN_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1070)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  搜索中断时的频点信息上报。
 bit[15:12]  保留
 bit[11:0]   搜索启动时的频点信息上报。
   UNION结构:  GBBP_SRCH_FRQ_RPT_UNION */
#define GBBP_SRCH_FRQ_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x107C)

/* 寄存器说明：
 bit[31]     NB-AFC一阶环与二阶环状态上报。
             0：表示当前处于一阶环；
             1：表示当前处于二阶环。
 bit[30:0]   一阶环当前NB-AFC环路滤波累加器的上报值
   UNION结构:  GBBP_AFC_LOOP1_RPT_UNION */
#define GBBP_AFC_LOOP1_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1078)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   上电后一阶环NB-AFC环路滤波累加器的配置值。
             再配置cpu_afc_init_en为1后生效。
             
   UNION结构:  GBBP_CPU_AFC_LOOP1_CFG_UNION */
#define GBBP_CPU_AFC_LOOP1_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1080)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  邻区频偏状态上报。
 bit[15:0]   邻区频偏检测结果上报。
   UNION结构:  GBBP_NCELL_NCO_RPT_UNION */
#define GBBP_NCELL_NCO_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1084)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  NB-AFC算法相位估计值参考上限，典型值760。
 bit[15:10]  保留
 bit[9:0]    NB-AFC算法相位估计值参考下限，典型值300。
   UNION结构:  GBBP_AFC_PHASE_THRESHOLD_CFG_UNION */
#define GBBP_AFC_PHASE_THRESHOLD_CFG_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x108C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  NB-AFC算法系数fcut的最大值，如果经过α滤波后的相位估计值大于相位估计值的参考上限，则系数fcut的值就等于此最大值。典型值1024。
 bit[15:13]  保留
 bit[12:0]   NB-AFC算法系数fcut的最小值，如果经过α滤波后的相位估计值小雨相位估计值参考下限，则系数fcut的值就等于此最小值。典型值51。
   UNION结构:  GBBP_AFC_FCUT_THRESHOLD_CFG_UNION */
#define GBBP_AFC_FCUT_THRESHOLD_CFG_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1090)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    NB-AFC算法α滤波系数选择：
             0：1/64；
             1：1/32；
             2：1/16；
             3：1/8。
   UNION结构:  GBBP_AFC_ALPHA_SEL_UNION */
#define GBBP_AFC_ALPHA_SEL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1094)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17]     NB解调使能状态上报。
 bit[16]     搜索使能状态上报。
 bit[15:5]   保留
 bit[4]      写1表示产生TOA ALPHA能量累加值的清零信号，逻辑自清零。
 bit[3]      写1表示产生gsp_nb_afc_en清零信号，逻辑自清零。
 bit[2]      写1表示产生gsp_agc_en清零信号，逻辑自清零。
 bit[1]      写1表示产生gsp_nb_demod_en清零信号，逻辑自清零。
 bit[0]      写1表示产生gsp_srch_en清零信号，逻辑自清零。
   UNION结构:  GBBP_CPU_SRCH_EN_CLR_UNION */
#define GBBP_CPU_SRCH_EN_CLR_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1124)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:24]  NB调制方式第一次判决结果上报。
 bit[23:18]  保留
 bit[17:16]  NB调制方式上报，
             0：GMSK调制；
             1：8PSK调制；
             2：DummyBurst。
 bit[15:13]  保留
 bit[12:0]   NB位置更新上报，是读取时刻最后一个解调BURST的位置，其相对于timebase。CPU可以在帧中断中读取。精度2QB。
   UNION结构:  GBBP_NB_POS_RPT_UNION */
#define GBBP_NB_POS_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1060)

/* 寄存器说明：
 bit[31]     1表示打开信道因子优化配置。
 bit[30:2]   保留
 bit[1:0]    8psk均衡解调中求PSP_EN的参数alpha，
             0：对应的值为8；
             1：对应的值为16；
             2：对应的值为24；
             3：无效。
             默认值为1。
   UNION结构:  GBBP_CPU_8PSK_PSP_ALPHA_PARA_UNION */
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1068)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    alpha滤波系数选择：
             0：表示选择系数为1/2；
             1：表示选择系数为1/4；
             2：表示选择系数为1/8；
             3：表示选择系数为1/16；
             4：表示选择系数为1/32。
   UNION结构:  GBBP_CPU_TOA_ALPHA_PARA_UNION */
#define GBBP_CPU_TOA_ALPHA_PARA_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1074)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  白化滤波判决门限，当噪声大于能量的倍数超过该门限，不启动白化滤波。对于NB可配置范围时1~7，表示1~7倍；对于SB，固定配置为5，表示5倍。
 bit[15:8]   保留
 bit[7]      1表示旁路信道估计优化功能；
             0表示打开信道估计优化功能。
 bit[6]      valpp计算PSP更新使能信号，1有效。
 bit[5:3]    保留
 bit[2:0]    信道估计优化噪声系数因子，取值1~5，默认配置2。
   UNION结构:  GBBP_CPU_CH_EST_OPT_UNION */
#define GBBP_CPU_CH_EST_OPT_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1088)

/* 寄存器说明：
 bit[31:16]  bit16~bit31表示多时隙的第一，第二，第三，第四个时隙的四个BURST类型盲检测标志上报，0标识NB，1标识DB。
 bit[15:0]   bit0~bit15表示多时隙的第一，第二，第三，第四个时隙的四个BURST调制盲检测标志上报，0标识GMSK，1标识8PSK。
   UNION结构:  GBBP_NB_MOD_TYPE_RPT_UNION */
#define GBBP_NB_MOD_TYPE_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1098)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  bit16~bit23表示多时隙的第五，第六时隙的两个BURST类型标志上报，0标识NB，1标识DB。
 bit[15:8]   保留
 bit[7:0]    bit0~bit7表示多时隙的第五，第六时隙的两个BURST调制盲检测标志上报，0标识GMSK，1标识8PSK。
   UNION结构:  GBBP_NB_BURST_TYPE_RPT_UNION */
#define GBBP_NB_BURST_TYPE_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x10BC)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第一近的一个BURST解调前粗测C值上报，测试用。
   UNION结构:  GBBP_GROSS_CARRIER_ENERGY1_UNION */
#define GBBP_GROSS_CARRIER_ENERGY1_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x109C)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第一近的一个BURST解调前粗测I值上报，测试用。
   UNION结构:  GBBP_GROSS_INTERFERE_ENERGY1_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY1_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10A0)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第二近的一个BURST解调前粗测C值上报，测试用。
   UNION结构:  GBBP_GROSS_CARRIER_ENERGY2_UNION */
#define GBBP_GROSS_CARRIER_ENERGY2_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x10A4)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第二近的一个BURST解调前粗测I值上报，测试用。
   UNION结构:  GBBP_GROSS_INTERFERE_ENERGY2_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY2_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10A8)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第三近的一个BURST解调前粗测C值上报，测试用。
   UNION结构:  GBBP_GROSS_CARRIER_ENERGY3_UNION */
#define GBBP_GROSS_CARRIER_ENERGY3_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x10AC)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第三近的一个BURST解调前粗测I值上报，测试用。
   UNION结构:  GBBP_GROSS_INTERFERE_ENERGY3_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY3_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10B0)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第四近的一个BURST解调前粗测C值上报，测试用。
   UNION结构:  GBBP_GROSS_CARRIER_ENERGY4_UNION */
#define GBBP_GROSS_CARRIER_ENERGY4_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x10B4)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第四近的一个BURST解调前粗测I值上报，测试用。
   UNION结构:  GBBP_GROSS_INTERFERE_ENERGY4_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY4_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10B8)

/* 寄存器说明：
   详      述：第一近的一个BURST解调前半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENZI1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10C0)

/* 寄存器说明：
   详      述：第一近的一个BURST解调前半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENMU1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10C4)

/* 寄存器说明：
   详      述：第一近的一个BURST解调后半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENZI1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10C8)

/* 寄存器说明：
   详      述：第一近的一个BURST解调后半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENMU1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10CC)

/* 寄存器说明：
   详      述：第二近的一个BURST解调前半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENZI2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10D0)

/* 寄存器说明：
   详      述：第二近的一个BURST解调前半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENMU2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10D4)

/* 寄存器说明：
   详      述：第二近的一个BURST解调后半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENZI2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10D8)

/* 寄存器说明：
   详      述：第二近的一个BURST解调后半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENMU2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10DC)

/* 寄存器说明：
   详      述：第三近的一个BURST解调前半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENZI3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10E0)

/* 寄存器说明：
   详      述：第三近的一个BURST解调前半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENMU3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10E4)

/* 寄存器说明：
   详      述：第三近的一个BURST解调后半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENZI3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10E8)

/* 寄存器说明：
   详      述：第三近的一个BURST解调后半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENMU3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10EC)

/* 寄存器说明：
   详      述：第四近的一个BURST解调前半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENZI4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10F0)

/* 寄存器说明：
   详      述：第四近的一个BURST解调前半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENMU4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10F4)

/* 寄存器说明：
   详      述：第四近的一个BURST解调后半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENZI4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10F8)

/* 寄存器说明：
   详      述：第四近的一个BURST解调后半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENMU4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10FC)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   读取时刻前最近burst对应的载波能量值，无符号数。
   UNION结构:  GBBP_VALPP_CARRIER_ENERGY0_UNION */
#define GBBP_VALPP_CARRIER_ENERGY0_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1100)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   读取时刻前最近burst对应的干扰能量值，无符号数。
   UNION结构:  GBBP_VALPP_INTERFERE_ENERGY0_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY0_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1150)

/* 寄存器说明：
 bit[31]     读取时刻最近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过bit30对该bit清零，指示该信息已经读取。
 bit[30]     对demod_info_valid_flag0清零。写1清零。
 bit[29:28]  读取时刻前的最近BURST对应的一次判决的调制方式，
             0：GMSK调制；
             1：8PSK调制；
             2：DummyBurst。
             该寄存器测试使用。
 bit[27:25]  保留
 bit[24]     读取时刻最近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[23]     保留
 bit[22:20]  读取时刻最近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[19:16]  读取时刻最近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。
 bit[15:14]  读取时刻最近BURST的调制方式，
             0：GSKM；
             1：8PSK；
             2：DummyBurst。
 bit[13:12]  保留
 bit[11:8]   SAIC后TOA五径C值最大值对应径号；
             取值范围0~4。
 bit[7:6]    保留
 bit[5:0]    最近6个时隙的TOA样点选择结果，
             bit0：最近一个burst的选择结果；
             bit1：第二近burst的选择结果，
             其他依次类推。
             0表示选择前半个符号，1表示选择后半个符号，需要在nb_pos_adj的基础上加上2QB。
   UNION结构:  GBBP_VALPP_DEM_TYPE_TOA0_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA0_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1104)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   读取时刻前第二近burst对应的载波能量值，无符号数。
   UNION结构:  GBBP_VALPP_CARRIER_ENERGY1_UNION */
#define GBBP_VALPP_CARRIER_ENERGY1_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1108)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   读取时刻前第二近burst对应的干扰能量值，无符号数。
   UNION结构:  GBBP_VALPP_INTERFERE_ENERGY1_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY1_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1154)

/* 寄存器说明：
 bit[31]     读取时刻第二近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过写bit30对该bit清零，指示该信息已经读取。
 bit[30]     对demod_info_valid_flag1清零。写1清零。
 bit[29:28]  读取时刻前的第二近BURST对应的一次判决的调制方式，
             0：GMSK调制；
             1：8PSK调制；
             2：DummyBurst。
             该寄存器测试使用。
 bit[27:25]  保留
 bit[24]     读取时刻第二近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[23]     保留
 bit[22:20]  读取时刻第二近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[19:16]  读取时刻第二近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。
 bit[15:14]  读取时刻第二近BURST的调制方式，
             0：GSKM；
             1：8PSK；
             2：DummyBurst。
 bit[13:0]   保留
   UNION结构:  GBBP_VALPP_DEM_TYPE_TOA1_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA1_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x110C)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   读取时刻前第三近burst对应的载波能量值，无符号数。
   UNION结构:  GBBP_VALPP_CARRIER_ENERGY2_UNION */
#define GBBP_VALPP_CARRIER_ENERGY2_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1110)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   读取时刻前第三近burst对应的干扰能量值，无符号数。
   UNION结构:  GBBP_VALPP_INTERFERE_ENERGY2_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY2_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1158)

/* 寄存器说明：
 bit[31]     读取时刻第三近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过写bit30对该bit清零，指示该信息已经读取。
 bit[30]     对demod_info_valid_flag2清零。写1清零。
 bit[29:28]  读取时刻前的第三近BURST对应的一次判决的调制方式，
             0：GMSK调制；
             1：8PSK调制；
             2：DummyBurst。
             该寄存器测试使用。
 bit[27:25]  保留
 bit[24]     读取时刻第三近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[23]     保留
 bit[22:20]  读取时刻第三近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[19:16]  读取时刻第三近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。
 bit[15:14]  读取时刻第三近BURST的调制方式，
             0：GSKM；
             1：8PSK；
             2：DummyBurst。
 bit[13:0]   保留
   UNION结构:  GBBP_VALPP_DEM_TYPE_TOA2_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA2_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1114)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   读取时刻前第四近burst对应的载波能量值，无符号数。
   UNION结构:  GBBP_VALPP_CARRIER_ENERGY3_UNION */
#define GBBP_VALPP_CARRIER_ENERGY3_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1118)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   读取时刻前第四近burst对应的干扰能量值，无符号数。
   UNION结构:  GBBP_VALPP_INTERFERE_ENERGY3_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY3_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x115C)

/* 寄存器说明：
 bit[31]     读取时刻第四近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该写bit30对该bit清零，指示该信息已经读取。
 bit[30]     对demod_info_valid_flag3清零。写1清零。
 bit[29:28]  读取时刻前的第四近BURST对应的一次判决的调制方式，
             0：GMSK调制；
             1：8PSK调制；
             2：DummyBurst。
             该寄存器测试使用。
 bit[27:25]  保留
 bit[24]     读取时刻第四近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[23]     保留
 bit[22:20]  读取时刻第四近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[19:16]  读取时刻第四近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。
 bit[15:14]  读取时刻第四近BURST的调制方式，
             0：GSKM；
             1：8PSK；
             2：DummyBurst。
 bit[13:0]   保留
   UNION结构:  GBBP_VALPP_DEM_TYPE_TOA3_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA3_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x111C)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     HARQ译码前数据位宽恢复模式配置
             0:按照解调动态位宽方案恢复数据
             1:不做解调软值位宽恢复操作
             
 bit[15:2]   保留
 bit[1:0]    解调动态位宽配置
             2’d0：动态右移位数为0
             2’d1：动态右移位数为1
             2’d2：动态右移位数为2
             其他：保留
             
   UNION结构:  GBBP_CPU_DEM_WIDTH_CFG_UNION */
#define GBBP_CPU_DEM_WIDTH_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1120)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:16]  Dummy Burst二次判决门限；
             0： threshold_db=4；
             1： threshold_db=6；
             2： threshold_db=8；
             3： threshold_db=9；
             4： threshold_db=10；
             5： threshold_db=11；
             6： threshold_db=12；
             7： threshold_db=14；
             8： threshold_db=16；
             9： threshold_db=20；
             others： 保留
             
             
 bit[15:2]   保留
 bit[1:0]    物理层配置的Dummy 训练序列类型。
             0：Dummy Burst训练序列同NB
             1：Dummy Burst训练序列同C0模式训练序列
             2：Dummy Burst训练序列同NB模式训练序列有固定的映射关系。
             3：保留
             默认值1。
             
   UNION结构:  GBBP_CPU_DB_TYPE_CFG_UNION */
#define GBBP_CPU_DB_TYPE_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1128)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1表示打开解调BEP功能。
             0表示屏蔽解调BEP功能
             
   UNION结构:  GBBP_CPU_DEM_BEP_MODE_EN_UNION */
#define GBBP_CPU_DEM_BEP_MODE_EN_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x112C)

/* 寄存器说明：
 bit[31]     1表示VALPP_RAM 和 CARRY_RAM 数据搬移模式使能，当cpu_valpp_carry_mode配置为1时且cpu_valpp_carry_en配置为1时，解调模块往VALPP RAM写数据的同时，会将解调数据同时保存到CARRY RAM中.
             复位默认值为1
             
 bit[30:26]  保留
 bit[25:24]  表示从CARRY_RAM到VALPP_RAM的一个BURST数据量指示
                      00 ：表示搬移GMSK调制的SB解调数据
                      10 ：表示搬移GMSK调制的NB解调数据
                      11 ：表示搬移8PSK调制的NB解调数据
                      其他：表示搬移GMSK调制的NB解调数据
             复位默认值为2’b10
             
 bit[23:16]  保留
 bit[15]     VALPP_RAM 和 CARRY_RAM 数据搬移方向指示，1表示从VALPP_RAM到CARRY_RAM，0表示从CARRY_RAM到VALPP_RAM,在这种模式下，需要相应的配置cpu_carry_burst_pos作为VALPP_RAM写数据的起始地址.
             复位默认值为1
             
 bit[14:7]   保留
 bit[6:0]    VALPP_RAM 和 CARRY_RAM 数据搬移目标BURST位置(carry to valpp)
   UNION结构:  GBBP_CPU_VALPP_CARRY_CTRL_UNION */
#define GBBP_CPU_VALPP_CARRY_CTRL_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1130)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      VALPP_RAM 和 CARRY_RAM 数据搬移启动信号，只针对从CARRY_RAM到VALPP_RAM模式有效,逻辑自清零
   UNION结构:  GBBP_CPU_VALPP_CARRY_START_UNION */
#define GBBP_CPU_VALPP_CARRY_START_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1134)

/* 寄存器说明：
 bit[31]     1 表示固定选择偶路，0表示选择最佳路 默认值为0。                     此信号用于选择上报的nb_pos_cpu, nb_pos_adj_cpu和C/I等。
 bit[30:27]  保留
 bit[26:24]  case(cpu_cross_delta)
             3’b000: R[i][i] = R[i][i] + (R[i][i] >>8) ;
             3’b001: R[i][i] = R[i][i] + (R[i][i] >>9) ;
             3’b010: R[i][i] = R[i][i] + (R[i][i] >>10) ;
             3’b011: R[i][i] = R[i][i] + (R[i][i] >>11) ;
             3’b100: R[i][i] = R[i][i];
             cpu_cross_delta信号是用于选择对角线元素的处理方式，默认值是3’b010。
 bit[23:22]  保留
 bit[21:20]  GMSK CI测量的调整系数，默认值是15(配置为2’b00)，可选值1和8
             2’b00:15
             2’b01: 8
             2’b10: 1
             默认值为2’b00
 bit[19:18]  保留
 bit[17:16]  PHY在帧头位置配置下帧NB位置的调整量。
             配置值范围－1～1，补码表示。
             2’b11：表示下帧的NB较上帧调前一个符号；
             2’b01：表示下帧的NB较上帧调后一个符号；
             2’b00 ：表示不进行帧间调整。该信号在TDMA帧头后560qb自动清零。
 bit[15:10]  保留
 bit[9:8]    判决反馈后，SAIC滤波输出值的移位值，10～12比特，默认值是2’b01。该值用来调整性能偏差。
             2’b00: 10;
             2’b01: 11;
             2’b10: 12;
 bit[7:2]    保留
 bit[1:0]    判决反馈前，SAIC滤波输出值的移位值，11～13比特，默认值2’b01。该值用来调整性能偏差。
             2’b00: 11
             2’b01: 12
             2’b10: 13
   UNION结构:  GBBP_CPU_SAIC_CTRL_UNION */
#define GBBP_CPU_SAIC_CTRL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1138)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:0]   DummuBurst检测DATA最大能量上报
   UNION结构:  GBBP_MAX_DB_DATA_ENERGY_RPT_UNION */
#define GBBP_MAX_DB_DATA_ENERGY_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x113C)

/* 寄存器说明：
   详      述：DummuBurst检测DB最大能量上报
   UNION结构 ：无 */
#define GBBP_MAX_DB_ENERGY_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1140)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  SB位置计算使用的中心径能量加权值，默认值0
             0表示权值为1；
             1表示权值为65/64；
             2表示权值为33/32；
             3表示权值为17/16；
             4表示权值为9/8；
             5表示权值为5/4；
 bit[15:9]   保留
 bit[8]      解调位置继承使用中心径能量加权算法，1为使用，默认值0
 bit[7:5]    保留
 bit[4]      上报的nb_pos和nb_pos_adj使用中心径能量加权算法，1为使用，默认值0
 bit[3]      保留
 bit[2:0]    NB位置计算使用的中心径能量加权值，默认值0
             含义与sb的权值一致
             
   UNION结构:  GBBP_ENG_WEIGHT_UNION */
#define GBBP_ENG_WEIGHT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1144)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  当前burst直流I路上报
 bit[15:8]   保留
 bit[7:0]    当前burst直流Q路上报
   UNION结构:  GBBP_LS_DC_CPU_UNION */
#define GBBP_LS_DC_CPU_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x1160)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      LS去直流TOA上报使能，0表示关闭，1表示打开。
   UNION结构:  GBBP_LS_TOA_RPT_EN_UNION */
#define GBBP_LS_TOA_RPT_EN_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1164)

/* 寄存器说明：
 bit[31]     保留
 bit[30:13]  据当前时刻第二近的FB周期的FB最大能量
 bit[12:0]   据当前时刻第二近的FB周期的FB位置
   UNION结构:  GBBP_FB_2_POS_ENG_UNION */
#define GBBP_FB_2_POS_ENG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1168)

/* 寄存器说明：
 bit[31]     保留
 bit[30:13]  据当前时刻第三近的FB周期的FB最大能量
 bit[12:0]   据当前时刻第三近的FB周期的FB位置
   UNION结构:  GBBP_FB_3_POS_ENG_UNION */
#define GBBP_FB_3_POS_ENG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x116C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    SB数据保存状态上报,每次gsp_sb_save_start后清零
             00：未启动SB数据存储 
             01：启动SB数据存储，且保存完毕 
             10：启动SB存储，但保存完毕前异常终止（如搜索使能被拉低），数据无效
   UNION结构:  GBBP_SB_SAVE_STATUS_UNION */
#define GBBP_SB_SAVE_STATUS_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1170)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      110/111搜索模式时，AFC叉积长度;
             0表示延迟长度为16，1表示延迟长度为2。
             如果cpu_11x_capt_disable=0，则捕获态延迟长度固定为2，跟踪态固定为16；
 bit[3:1]    保留
 bit[0]      110/111搜索模式时，不进入捕获态，直接进入跟踪态；
   UNION结构:  GBBP_SHORT_11X_CFG_UNION */
#define GBBP_SHORT_11X_CFG_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1174)

/* 寄存器说明：
 bit[31]     快速101模式下是否启动FB和SB距离的判断使能，为1表示当FB与SB距离超过34符号则本次搜索失败
 bit[30:18]  保留
 bit[17:0]   提前启动SB的FB能量门限，当大于等于该门限时，启动SB搜索解调
   UNION结构:  GBBP_FAST_101_CFG_UNION */
#define GBBP_FAST_101_CFG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1178)

/* 寄存器说明：
 bit[31]     严重噪声（噪声超过一定门限）时，停止AFC调整，电平信号
             1：表示噪声过门限时，屏蔽AFC调整；
             0：表示不根据噪声大小屏蔽AFC调整
             
 bit[30:19]  保留
 bit[18:0]   停止AFC调整的噪声门限；当噪声的值大于该门限时，不关CI比值如何，都不调整AFC
   UNION结构:  GBBP_HEAVY_NOISE_CFG_UNION */
#define GBBP_HEAVY_NOISE_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x117C)

/* 寄存器说明：
   详      述：bit31：FB搜索中断，每个FB搜索周期上报一次；
            bit29：解调结束中断；
            bit28：电平测量结束中断;
            bit24:时钟测量中断;
            bit19:可编程中断7请求;
            bit18:可编程中断6请求;
            bit17:可编程中断5请求;
            bit16:可编程中断4请求;
            bit15:可编程中断3请求;
            bit14:可编程中断2请求;
            bit13:可编程中断1请求;
            bit12:可编程中断0请求;
            bit11:时隙7中断请求;
            bit10:时隙6中断请求;
            bit9:时隙5中断请求;
            bit8:时隙4中断请求;
            bit7:时隙3中断请求;
            bit6:时隙2中断请求;
            bit5:时隙1中断请求;
            bit4:时隙0中断请求,1有效;
            bit3:译码数据上报中断请求;
            bit2:同步搜索中断请求;
            bit1:GTC PAGE中断请求;
            bit0:TDMA帧中断请求，1表示中断请求，0表示无中断请求，其他bit描述同此。
   UNION结构 ：无 */
#define GBBP_CPU_INT_STA_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1200)

/* 寄存器说明：
   详      述：bit31：FB搜索中断，每个FB搜索周期上报一次；
            bit29：解调结束中断；
            bit28：电平测量结束中断;
            bit24:时钟测量中断;
            bit19:可编程中断7屏蔽信号;
            bit18:可编程中断6屏蔽信号;
            bit17:可编程中断5屏蔽信号;
            bit16:可编程中断4屏蔽信号;
            bit15:可编程中断3屏蔽信号;
            bit14:可编程中断2屏蔽信号;
            bit13:可编程中断1屏蔽信号;
            bit12:可编程中断0屏蔽信号;
            bit11:时隙7中断屏蔽信号;
            bit10:时隙6中断屏蔽信号;
            bit9:时隙5中断屏蔽信号;
            bit8:时隙4中断屏蔽信号;
            bit7:时隙3中断屏蔽信号;
            bit6:时隙2中断屏蔽信号;
            bit5:时隙1中断屏蔽信号;
            bit4:时隙0中断屏蔽信号,1有效;
            bit3:译码数据上报中断屏蔽信号;
            bit2:同步搜索中断屏蔽信号;
            bit1:GTC PAGE中断屏蔽信号;
            bit0:TDMA帧中断屏蔽信号，1表示中断屏蔽信号屏蔽，0表示中断不屏蔽，其他bit描述同此。
   UNION结构 ：无 */
#define GBBP_CPU_INT_MASK_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1204)

/* 寄存器说明：
   详      述：bit31：FB搜索中断，每个FB搜索周期上报一次；
            bit29：解调结束中断；
            bit28：电平测量结束中断;
            bit24:时钟测量中断;
            bit19:可编程中断7请求清零;
            bit18:可编程中断6请求清零;
            bit17:可编程中断5请求清零;
            bit16:可编程中断4请求清零;
            bit15:可编程中断3请求清零;
            bit14:可编程中断2请求清零;
            bit13:可编程中断1请求清零;
            bit12:可编程中断0请求清零;
            bit11:时隙7中断请求清零;
            bit10:时隙6中断请求清零;
            bit9:时隙5中断请求清零;
            bit8:时隙4中断请求清零;
            bit7:时隙3中断请求清零;
            bit6:时隙2中断请求清零;
            bit5:时隙1中断请求清零;
            bit4:时隙0中断请求清零,1有效;
            bit3:译码数据上报中断请求清零;
            bit2:同步搜索中断请求清零;
            bit1:GTC PAGE中断请求清零;
            bit0:TDMA帧中断清零信号，1表示中断请求清零清除，0表示中断请求清零不清除，其他bit描述同此。
   UNION结构 ：无 */
#define GBBP_CPU_INT_CLR_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1208)

/* 寄存器说明：
   详      述：bit31：FB搜索中断，每个FB搜索周期上报一次；
            bit29：解调结束中断；
            bit28：电平测量结束中断;
            bit27:时钟测量中断;
            bit26:;CTU异系统测量中断2；
            bit25:;CTU异系统测量中断1；
            bit24:;CTU异系统测量中断0；
            bit19:可编程中断7请求;
            bit18:可编程中断6请求;
            bit17:可编程中断5请求;
            bit16:可编程中断4请求;
            bit15:可编程中断3请求;
            bit14:可编程中断2请求;
            bit13:可编程中断1请求;
            bit12:可编程中断0请求;
            bit11:时隙7中断请求;
            bit10:时隙6中断请求;
            bit9:时隙5中断请求;
            bit8:时隙4中断请求;
            bit7:时隙3中断请求;
            bit6:时隙2中断请求;
            bit5:时隙1中断请求;
            bit4:时隙0中断请求,1有效;
            bit3:译码数据上报中断请求;
            bit2:同步搜索中断请求;
            bit1:GTC PAGE中断请求;
            bit0:TDMA帧中断请求，1表示中断请求，0表示无中断请求，其他bit描述同此。
   UNION结构 ：无 */
#define GBBP_DSP_INT_STA_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1210)

/* 寄存器说明：
   详      述：bit31：FB搜索中断屏蔽寄存器，每个FB搜索周期上报一次；
            bit29：解调结束中断屏蔽寄存器；
            bit28：电平测量结束中断屏蔽寄存器;
            bit27:时钟测量中断屏蔽寄存器;
            bit26:;CTU异系统测量中断2屏蔽寄存器；
            bit25:;CTU异系统测量中断1屏蔽寄存器；
            bit24:;CTU异系统测量中断0屏蔽寄存器；
            bit19:可编程中断7屏蔽寄存器;
            bit18:可编程中断6屏蔽寄存器;
            bit17:可编程中断5屏蔽寄存器;
            bit16:可编程中断4屏蔽寄存器;
            bit15:可编程中断3屏蔽寄存器;
            bit14:可编程中断2屏蔽寄存器;
            bit13:可编程中断1屏蔽寄存器;
            bit12:可编程中断0屏蔽寄存器;
            bit11:时隙7中断屏蔽寄存器;
            bit10:时隙6中断屏蔽寄存器;
            bit9:时隙5中断屏蔽寄存器;
            bit8:时隙4中断屏蔽寄存器;
            bit7:时隙3中断屏蔽寄存器;
            bit6:时隙2中断屏蔽寄存器;
            bit5:时隙1中断屏蔽寄存器;
            bit4:时隙0中断屏蔽寄存器,1有效;
            bit3:译码数据上报中断屏蔽寄存器;
            bit2:同步搜索中断屏蔽寄存器;
            bit1:GTC PAGE中断屏蔽寄存器;
            bit0:TDMA帧中断屏蔽寄存器，1表示中断屏蔽寄存器，0表示无中断屏蔽寄存器，其他bit描述同此。
   UNION结构 ：无 */
#define GBBP_DSP_INT_MASK_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1214)

/* 寄存器说明：
   详      述：bit31：FB搜索中断清零信号；
            bit29：解调结束中断清零信号；
            bit28：电平测量结束中断清零信号;
            bit27:时钟测量中断清零信号;
            bit26:;CTU异系统测量中断2清零信号；
            bit25:;CTU异系统测量中断1清零信号；
            bit24:;CTU异系统测量中断0清零信号；
            bit19:可编程中断7清零信号;
            bit18:可编程中断6清零信号;
            bit17:可编程中断5清零信号;
            bit16:可编程中断4清零信号;
            bit15:可编程中断3清零信号;
            bit14:可编程中断2清零信号;
            bit13:可编程中断1清零信号;
            bit12:可编程中断0清零信号;
            bit11:时隙7中断清零信号;
            bit10:时隙6中断清零信号;
            bit9:时隙5中断清零信号;
            bit8:时隙4中断清零信号;
            bit7:时隙3中断清零信号;
            bit6:时隙2中断清零信号;
            bit5:时隙1中断清零信号;
            bit4:时隙0中断清零信号,1有效;
            bit3:译码数据上报中断清零信号;
            bit2:同步搜索中断清零信号;
            bit1:GTC PAGE中断清零信号;
            bit0:TDMA帧中断清零信号，1表示中断清零信号，0表示无中断清零信号，其他bit描述同此。
   UNION结构 ：无 */
#define GBBP_DSP_INT_CLR_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1218)

/* 寄存器说明：
 bit[31:16]  Luise鉴频优化算法计算得到的频偏调整值
 bit[15:9]   保留
 bit[8]      单TCXO使能信号，用于控制搜索前数据是否经过NCO纠偏
 bit[7:1]    保留
 bit[0]      Luise鉴频使能
   UNION结构:  GBBP_ADDR_CPU_LUISE_AFC_UNION */
#define GBBP_ADDR_CPU_LUISE_AFC_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1258)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   定点睡眠模式下，睡眠起始Qb时刻（TDMA）时刻，该参数是基于TDMA时标gtc_tdma_qb的
   UNION结构:  GBBP_ADDR_GDRX_SLEEP_POINT_UNION */
#define GBBP_ADDR_GDRX_SLEEP_POINT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x125C)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    定时信息从ON区传输到OFF区，软件配置的定时信息补偿参数。此值要大于全部数据传输时延，单位QB，默认配置16QB。
   UNION结构:  GBBP_ADDR_CPU_TRANS_COMP_UNION */
#define GBBP_ADDR_CPU_TRANS_COMP_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1260)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  第0组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。
 bit[15:10]  保留
 bit[9:0]    第0组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。
   UNION结构:  GBBP_ADDR_RX_IQ_MISMATCH_REG0_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1270)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  第1组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。
 bit[15:10]  保留
 bit[9:0]    第1组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。
   UNION结构:  GBBP_ADDR_RX_IQ_MISMATCH_REG1_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1274)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  第2组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。
 bit[15:10]  保留
 bit[9:0]    第2组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。
   UNION结构:  GBBP_ADDR_RX_IQ_MISMATCH_REG2_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1278)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  第3组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。
 bit[15:10]  保留
 bit[9:0]    第3组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。
   UNION结构:  GBBP_ADDR_RX_IQ_MISMATCH_REG3_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x127C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  第4组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。
 bit[15:10]  保留
 bit[9:0]    第4组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。
   UNION结构:  GBBP_ADDR_RX_IQ_MISMATCH_REG4_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1280)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:16]  在调制结束后，扩展填充的样点个数
 bit[15:4]   保留
 bit[3:0]    最后一个tx_rrx_data_ind_in与gmod_finish之间的间隔clk数
   UNION结构:  GBBP_ADDR_TX_RRC_EXT_UNION */
#define GBBP_ADDR_TX_RRC_EXT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1284)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   SB最大频偏限幅。默认值为1800MHz的最大频偏760；900MHz时配置380。
   UNION结构:  GBBP_ADDR_MAX_PHI_DEV_UNION */
#define GBBP_ADDR_MAX_PHI_DEV_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1288)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     HD3/5谐波消除功能旁路；0：表示谐波消除功能不旁路，但是否进行谐波消除还需要参考gsp_hd35_cal_en配置情况。1：表示谐波消除功能旁路，与V8R1版本时序完全一致。
 bit[15:1]   保留
 bit[0]      HD3/5初始配置参数配置RAM乒乓访问使能；1表示允许乒乓访问，0表示固定访问乒RAM空间；当该信号为1时，逻辑内部在TDMA帧头自动切换乒乓标志。
   UNION结构:  GBBP_ADDR_HD35_PARA_REG_UNION */
#define GBBP_ADDR_HD35_PARA_REG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1290)

/* 寄存器说明：
 bit[31]     1表示SPI射频控制参数由GTC模块输出，0表示SPI射频控制参数由CPU接口模块输出，默认值为1；该信号只是用于软件规避TA较大时配置RF射频延时问题；正常情况下该信号都应该配置为1
 bit[30:13]  保留
 bit[12:8]   CPU接口配置本次需要发送的SPI串口数据数，00001表示一个数，10000表示16个数，复位默认值为5'b00100
 bit[7:0]    CPU接口配置SPI串口待发数据在SPI DATA RAM的起始位置，复位默认值为8'd0
   UNION结构:  GBBP_CPU_SPI_RF_CFG_UNION */
#define GBBP_CPU_SPI_RF_CFG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1368)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      CPU启动SPI数据发送脉冲
   UNION结构:  GBBP_CPU_SPI_RF_RD_UNION */
#define GBBP_CPU_SPI_RF_RD_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x136C)

/* 寄存器说明：
 bit[31]     28bit公共线控信号CPU写使能指示信号。
 bit[30:0]   公共线控CPU接口配置，具体分配由NV项决定。
   UNION结构:  GBBP_CPU_LINE_CTRL_UNION */
#define GBBP_CPU_LINE_CTRL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1364)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   公共线控实际线控状态，测试用。
   UNION结构:  GBBP_GTC_GSP_LINE_STATE_RPT_UNION */
#define GBBP_GTC_GSP_LINE_STATE_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1384)

/* 寄存器说明：
 bit[31]     最近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。
 bit[30:27]  保留
 bit[26:24]  最近一个时隙AAGC档位上报。
 bit[23:20]  保留
 bit[19:8]   最近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。
 bit[7:3]    保留
 bit[2:0]    最近一个时隙AGC期望控制增益。
   UNION结构:  GBBP_AAGC_GAIN1_CPU_UNION */
#define GBBP_AAGC_GAIN1_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1460)

/* 寄存器说明：
 bit[31]     次近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。
 bit[30:27]  保留
 bit[26:24]  次近一个时隙AAGC档位上报。
 bit[23:20]  保留
 bit[19:8]   次近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。
 bit[7:3]    保留
 bit[2:0]    次近一个时隙AGC期望控制增益。
   UNION结构:  GBBP_AAGC_GAIN2_CPU_UNION */
#define GBBP_AAGC_GAIN2_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1464)

/* 寄存器说明：
 bit[31]     次次近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。
 bit[30:27]  保留
 bit[26:24]  次次近一个时隙AAGC档位上报。
 bit[23:20]  保留
 bit[19:8]   次次近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。
 bit[7:3]    保留
 bit[2:0]    次次近一个时隙AGC期望控制增益。
   UNION结构:  GBBP_AAGC_GAIN3_CPU_UNION */
#define GBBP_AAGC_GAIN3_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1468)

/* 寄存器说明：
 bit[31]     第四近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。
 bit[30:27]  保留
 bit[26:24]  '第四近一个时隙AAGC档位上报。
 bit[23:20]  保留
 bit[19:8]   '第四近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。
 bit[7:3]    保留
 bit[2:0]    '第四近一个时隙AGC期望控制增益。
   UNION结构:  GBBP_AAGC_GAIN4_CPU_UNION */
#define GBBP_AAGC_GAIN4_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x146C)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17]     采数模块软复位信号，写1该模块复位。
 bit[16]     解调预处理模块软复位信号，写1该模块复位。
 bit[15]     GTC定时模块软复位信号，写1该模块复位。
 bit[14]     GTC模块软复位信号，写1该模块复位。
             注意：该复位信号配置后，将会导致专用线控和公共线控均复位至0,。
 bit[13]     上行APC模块软复位信号，写1该模块复位。
 bit[12]     上行调制后处理模块软复位信号，写1该模块复位。
 bit[11]     下行解调模块（包括搜索部分和所有解调相关部分）软复位信号，写1该模块复位。
 bit[10]     下行译码模块中除去bit7、bit8、bit9剩下的其余模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。
 bit[9]      下行译码模块中解调、译码软值存储/读取模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。
 bit[8]      下行译码模块中去交织/交织、去打孔/打孔模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。
 bit[7]      下行译码模块中viterbi模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。
 bit[6]      信道滤波模块软复位信号，写1该模块复位。
 bit[5]      邻频检测模块软复位信号，写1该模块复位。
 bit[4]      自动增益控制模块软复位信号，写1该模块复位。
 bit[3]      上行编码模块中map模块软复位信号，写1该模块复位。
 bit[2]      上行编码模块（除上行编码map模块）软复位信号，写1该模块复位。Bit2与bit3共同构成上行编码模块控制。
 bit[1]      上行调制模块软复位信号，写1该模块复位。
 bit[0]      加解密模块软复位信号，写1该模块复位。
   UNION结构:  GBBP_ADDR_CPU_SOFT_RST_UNION */
#define GBBP_ADDR_CPU_SOFT_RST_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1350)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     解调预处理模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[15]     保留
 bit[14]     GTC模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[13]     上行APC模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[12]     上行调制后处理模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[11]     下行解调模块（包括搜索部分和所有解调相关部分）CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[10]     下行译码模块除了bit7、bit8、bit9剩下模块的CPU控制时钟生效指示，1表示有时钟，0表示没有时钟。
 bit[9]      下行译码模块中的解调、译码软值存储/读取模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[8]      下行译码模块中的交织/去交织、打孔/去打孔模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[7]      下行译码模块中的viterbi模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。bit7、bit8、bit9、bit10构成下行译码模块。
 bit[6]      信道滤波莫开CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[5]      邻频检测模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[4]      自动增益控制模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[3]      上行编码map模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[2]      上行编码模块（除了上行编码map模块）CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。bit2与bit3构成上行编码模块。
 bit[1]      上行调制模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
 bit[0]      加解密模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。
   UNION结构:  GBBP_ADDR_CPU_CLK_CTRL_UNION */
#define GBBP_ADDR_CPU_CLK_CTRL_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1354)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11]     下行解调（包括搜索部分和解调所有相关部分）模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[10]     下行译码模块中除了bit7、bit8、bit9剩下的模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[9]      下行译码模块中解调、译码软值存储/读取模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[8]      下行译码模块中交织/去交织、打孔/去打孔模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[7]      下行译码模块中viterbi模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。bit7、bit8、bit9、bit10构成下行译码模块控制。
 bit[6]      信道滤波模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[5]      邻频检测模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[4]      自动增益控制模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[3]      上行编码map编码模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[2]      上行编码（除了map编码模块）模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。bit2与bit3构成上行编码模块。
 bit[1]      上行调制模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
 bit[0]      加解密模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。
   UNION结构:  GBBP_ADDR_CPU_CLK_MODE_SEL_UNION */
#define GBBP_ADDR_CPU_CLK_MODE_SEL_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1358)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17]     采数模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[16]     下行解调预处理模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[15]     保留
 bit[14]     GTC模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[13]     上行APC模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[12]     上行调制后处理模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[11]     下行解调（包括搜索部分和所有解调相关部分）模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[10]     下行译码模块中除了bit、bit8、bit9剩下的模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[9]      下行译码模块中解调、译码软值存储/读取模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[8]      下行译码模块中交织/去角质、打孔/去打孔模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[7]      下行译码模块中viterbi模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。bit7、bit8、bit9、bit10构成下行译码模块。
 bit[6]      信道滤波模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[5]      邻频检测模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[4]      自动增益控制模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[3]      上行编码模块中map模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[2]      上行编码模块（除去map编码模块）时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。bit2与bit3构成上行编码模块。
 bit[1]      上行调制模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
 bit[0]      加解密模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。
   UNION结构:  GBBP_ADDR_CPU_AUTO_CLK_BYPASS_UNION */
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x135C)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      1表示DRX测试模式使能，此时GTC时钟应不关闭，用于DRX唤醒后的定时维护情况的比对。正常使用下该信号应该被置0，测试用。
 bit[7:5]    保留
 bit[4]      GTC模块工作使能信号，先配置为该信号为高，然后再启动GTC。
 bit[3]      1表示允许修改正在执行的GTC指令页，需要修改时将其置1，修改完成后置0。
 bit[2]      GTC指令在TDMA帧头处自动执行使能，默认为0。
 bit[1]      写1启动指令页执行，内部产生一个104M时钟脉冲，自清零，写0无意义。
 bit[0]      0：不切换指令RAM页，1：乒乓切换指令RAM页。复位后第一次配置时应该切换指令页。
   UNION结构:  GBBP_CPU_GTC_CFG_UNION */
#define GBBP_CPU_GTC_CFG_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1360)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5]      当前GTC指令RAM的乒乓标志上报，测试用。
 bit[4]      GTC指令RAM乒乓切换使能上报，测试用。
 bit[3]      保留
 bit[2]      1：表示GTC处于run运行状态，测试用。
 bit[1]      1：表示GTC处于hold或者start状态，测试用。
 bit[0]      1：表示GTC没有GTC指令执行；0表示GTC正在执行，测试用。
   UNION结构:  GBBP_GTC_STATE_RPT_UNION */
#define GBBP_GTC_STATE_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1374)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   TDMA定时与TimeBase时间偏差，单位qb，若frm_offset为N，则TimeBase计数到N-1且GTC内部计数器frac_cnt计数到95时，下一拍TDMA帧号加1，测试用。
   UNION结构:  GBBP_GTC_FRM_OFFSET_RPT_UNION */
#define GBBP_GTC_FRM_OFFSET_RPT_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x137C)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   帧中断与TimeBase时间偏差，单位qb，测试用。
   UNION结构:  GBBP_GTC_FRM_IT_OFFSET_RPT_UNION */
#define GBBP_GTC_FRM_IT_OFFSET_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1380)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  精简帧号维护机制中的T2初始值，该参数值与cpu_gtc_t1_cnt,cpu_gtc_t2_cnt,cpu_gtc_fn_low,cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效，所以应配置为下一帧的帧号的T1值。
 bit[23:21]  保留
 bit[20:16]  精简帧号维护机制中的T2初始值，该参数值与cpu_gtc_t2_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效，所以应配置为下一帧的帧号的T1值。
 bit[15:11]  保留
 bit[10:0]   精简帧号维护机制中的T1初始值，该参数值与cpu_gtc_t1_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效，所以应配置为下一帧的帧号的T1值。
   UNION结构:  GBBP_CPU_GTC_T1_T2_T3_CNG_UNION */
#define GBBP_CPU_GTC_T1_T2_T3_CNG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1388)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  GTC内部维护的T3计数器上报
 bit[23:21]  保留
 bit[20:16]  GTC内部维护的T2计数器上报
 bit[15:11]  保留
 bit[10:0]   GTC内部维护的T1计数器上报
   UNION结构:  GBBP_GTC_T1_T2_T3_RPT_CPU_UNION */
#define GBBP_GTC_T1_T2_T3_RPT_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x138C)

/* 寄存器说明：
 bit[31]     cpu_gtc_frm_offset
             cpu_gtc_frm_it_offset
             立即生效指示信号，逻辑自清零。
 bit[30:29]  保留
 bit[28:16]  CPU配置的gtc_frm_it_offset参数。
 bit[15:13]  保留
 bit[12:0]   CPU配置的gtc_frm_offset参数。
   UNION结构:  GBBP_CPU_GTC_FRM_OFFSET_CFG_UNION */
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1390)

/* 寄存器说明：
 bit[31]     帧号初始化信号，1有效，逻辑自清零。当T1、T2、T3、fn_low、fn_high、都写入后该信号才可以置1。
 bit[30:27]  保留
 bit[26:16]  CPU配置TDMA帧号高位0~2047，低位计满后，高位加1。CPU配置后，在帧边界处生效，所以应配置为下一帧的帧号。
 bit[15:11]  保留
 bit[10:0]   CPU配置TDMA帧号低位0~26*51-1循环计数，CPU配置后，在帧边界处生效，所以应配置为下一帧的帧号。
   UNION结构:  GBBP_CPU_GTC_FN_CNG_UNION */
#define GBBP_CPU_GTC_FN_CNG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1394)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  GTC此时帧号高位。
 bit[15:11]  保留
 bit[10:0]   GTC此时帧号低位。
   UNION结构:  GBBP_GTC_FN_RPT_UNION */
#define GBBP_GTC_FN_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1398)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  绝对时标QB上报，范围：0~4999，对应一帧的长度，该值只与复位时刻有关，测试用。
 bit[15:13]  保留
 bit[12:0]   当前时刻TDMA的QB计数值，0~4999。
   UNION结构:  GBBP_GTC_QB_RPT_UNION */
#define GBBP_GTC_QB_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x139C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  绝对时标帧号上报，该值变化时刻在gtc_timebase_qb为4999处，计数范围0~26*51-1，测试用。
 bit[15:13]  保留
 bit[12:0]   绝对时标QB上报，范围：0~4999，对应一帧的长度，该值只与复位时刻有关，测试用。
   UNION结构:  GBBP_TIMEBASE_RPT_UNION */
#define GBBP_TIMEBASE_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x13A8)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      BLER统计模式控制，0表示每次译码CRC结果都参与BLER统计（即是HEAD，DATA都统计）
             1表示只统计每次DATA的译码CRC结果BLER值
             
 bit[7:5]    保留
 bit[4]      接收质量上报BER清零信号，脉冲信号，cpu置1，逻辑自清零
 bit[3:1]    保留
 bit[0]      接收质量上报BLER清零信号，脉冲信号，cpu置1逻辑自清零
   UNION结构:  GBBP_CPU_BLER_BER_CLR_UNION */
#define GBBP_CPU_BLER_BER_CLR_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1300)

/* 寄存器说明：
 bit[31]     保留
 bit[30:24]  AMR语音激活集合内codec_mode=11对应的AMR语音帧cb_index
 bit[23]     保留
 bit[22:16]  AMR语音激活集合内codec_mode=10对应的AMR语音帧cb_index
 bit[15]     保留
 bit[14:8]   AMR语音激活集合内codec_mode=01对应的AMR语音帧cb_index
 bit[7]      保留
 bit[6:0]    AMR语音激活集合内codec_mode=00对应的AMR语音帧cb_index
   UNION结构:  GBBP_CPU_AMR_CB_INDEX_UNION */
#define GBBP_CPU_AMR_CB_INDEX_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1304)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     当AMR激活集个数发生变化时，需要配置该信号为1
 bit[15:8]   保留
 bit[7:4]    语音帧BFI相关译码判决门限，配置范围0～8
 bit[3:2]    保留
 bit[1:0]    AMR语音激活集内有效语音帧类型个数
             0 表示1个
             1 表示2个
             2 表示3个
             3 表示4个
             （当业务类型为GMSK WBAMR时，配置范围为0～2）
             
   UNION结构:  GBBP_CPU_AMR_ACTIVE_SET_NUM_UNION */
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1308)

/* 寄存器说明：
   详      述：接收质量上报累计BLER错误数
   UNION结构 ：无 */
#define GBBP_BLER_ERRR_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x130C)

/* 寄存器说明：
   详      述：接收质量上报累计BLER总数
   UNION结构 ：无 */
#define GBBP_BLER_TOTAL_RPT_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1310)

/* 寄存器说明：
   详      述：接收质量上报累计BER错误数
   UNION结构 ：无 */
#define GBBP_BER_ERRR_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1314)

/* 寄存器说明：
   详      述：接收质量上报累计BER总数
   UNION结构 ：无 */
#define GBBP_BER_TOTAL_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1318)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   DummyBurst导致误码计数上报
   UNION结构:  GBBP_DB_BLER_ERR_RPT_UNION */
#define GBBP_DB_BLER_ERR_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1484)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    SB误码计数上报
   UNION结构:  GBBP_SB_BLER_ERR_RPT_UNION */
#define GBBP_SB_BLER_ERR_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1488)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   EDGE业务DATA误码计数上报
   UNION结构:  GBBP_DATA_BLER_ERR_RPT_UNION */
#define GBBP_DATA_BLER_ERR_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x148C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29]     1表示有卷积编码过程，测试用
 bit[28]     打孔方式选择,0表示打孔，1表示不打孔，测试用
 bit[27:26]  码块译码类型，
             00从0状态开始，到0状态结束；
             01从0状态开始，到非0状态结束；
             10从非0状态开始，到0状态结束；
             11非0状态开始，到非0状态结束；
             测试用
             
 bit[25:15]  码块编码后数据长度，测试用
 bit[14:5]   码块译码后数据长度，即编码前数据长度，测试用
 bit[4]      卷积编码记忆深度，0: 4;  1: 6，测试用
 bit[3:0]    卷积编码率指示，
             2=1/2,3=1/3,4=1/4……6=1/6，测试用
   UNION结构:  GBBP_CODEC_PARA_REG1_UNION */
#define GBBP_CODEC_PARA_REG1_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1320)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:28]  CRC预处理业务标志信号
             00 无预处理
             01 重排序
             10 USF预处理_1
             11 USF预处理_2
             ，测试用
             
 bit[27:21]  编码生成多项式3，测试用
 bit[20:14]  编码生成多项式2，测试用
 bit[13:7]   编码生成多项式1，测试用
 bit[6:0]    编码生成多项式0，测试用
   UNION结构:  GBBP_CODEC_PARA_REG2_UNION */
#define GBBP_CODEC_PARA_REG2_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1324)

/* 寄存器说明：
 bit[31:28]  编码生成多项式组合序号，测试用
             
 bit[27:21]  打孔图样的打孔表序号，测试用
 bit[20:14]  分母位置的编码生成多项式，测试用
 bit[13:7]   编码生成多项式5，测试用
 bit[6:0]    编码生成多项式4，测试用
   UNION结构:  GBBP_CODEC_PARA_REG3_UNION */
#define GBBP_CODEC_PARA_REG3_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1328)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     1表示存在CRC校验过程，测试用
 bit[27]     1表示有交织过程，测试用
 bit[26:16]  卷积码块在交织中结束bit序号，测试用
 bit[15:5]   卷积码块在交织中起始bit序号
 bit[4:0]    交织公式序号，测试用
   UNION结构:  GBBP_CODEC_PARA_REG4_UNION */
#define GBBP_CODEC_PARA_REG4_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x132C)

/* 寄存器说明：
 bit[31]     1表示存在尾比特填充操作
             0表示不存在
             ，测试用
             
 bit[30]     保留
 bit[29:26]  CRC长度指示，测试用
 bit[25:23]  尾比特补零处理模式：
             bit25: 1表示存在填零处理
                    0表示不存在填零处理
             bit24～bit23：
             00表示填4个零
             01表示填6个零
             10表示填8个零
             11表示填32个零
             测试用
             
 bit[22:21]  编码业务大类指示
             00 非AFS和AHS的cs业务
             01 AFS或者AHS业务
             10 GPRS业务
             11 EGPRS业务
             测试用
             
 bit[20:12]  CLASS2 bit起始位置，测试用
 bit[11]     1表示存在CLASS2 bit，测试用
 bit[10]     保留
 bit[9:0]    信息bit结束位置，测试用
   UNION结构:  GBBP_CODEC_PARA_REG5_UNION */
#define GBBP_CODEC_PARA_REG5_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1330)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:24]  PS域的HEADER CPSbit 上报，测试用
 bit[23]     保留
 bit[22:20]  PS域USF bit 上报，测试用
 bit[19]     保留
 bit[18:12]  码块序号，测试用
 bit[11:0]   码块打孔信息存放起始位置，测试用
   UNION结构:  GBBP_CODEC_PARA_REG6_UNION */
#define GBBP_CODEC_PARA_REG6_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1334)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  最近的AMR业务上报
 bit[15:4]   保留
 bit[3:0]    最近的PS业务上报
   UNION结构:  GBBP_CODEC_PARA_REG7_UNION */
#define GBBP_CODEC_PARA_REG7_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x123C)

/* 寄存器说明：
 bit[31:27]  PS业务子状态机状态，测试用
 bit[26]     保留
 bit[25:20]  AHS业务子状态机状态，测试用
             
 bit[19:17]  保留
 bit[16:12]  AFS业务子状态机状态，测试用
             
 bit[11]     保留
 bit[10:8]   HARQ合并译码子状态机状态，测试用
 bit[7:4]    业务类型已知子状态机状态，测试用
 bit[3:0]    译码业务大类判断状态机状态，测试用
   UNION结构:  GBBP_DEC_STATE_RPT1_UNION */
#define GBBP_DEC_STATE_RPT1_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1338)

/* 寄存器说明：
 bit[31]     下行译码忙状态，测试用
 bit[30:28]  保留
 bit[27:24]  CCU工作状态，测试用
 bit[23]     保留
 bit[22:20]  去打孔模块工作状态，测试用
 bit[19:16]  交织模块工作状态，测试用
 bit[15:14]  保留
 bit[13:12]  相关译码子状态机状态，测试用
 bit[11:8]   VTB译码子状态机状态，测试用
             
 bit[7:0]    保留
   UNION结构:  GBBP_DEC_STATE_RPT2_UNION */
#define GBBP_DEC_STATE_RPT2_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x133C)

/* 寄存器说明：
   详      述：[5:0] 表示PS，CS域业务的第4个q bit或者偷帧bit 软值
            [13:8] 表示PS，CS域业务的第3个q bit或者偷帧bit 软值
            [21:16] 表示PS，CS域业务的第2个q bit或者偷帧bit 软值
            [27:24] 表示PS，CS域业务的第1个q bit或者偷帧bit 软值
            ，测试用
   UNION结构 ：无 */
#define GBBP_Q_BIT_RPT1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1340)

/* 寄存器说明：
   详      述：[5:0] 表示PS，CS域业务的第8个q bit或者偷帧bit 软值
            [13:8] 表示PS，CS域业务的第7个q bit或者偷帧bit 软值
            [21:16] 表示PS，CS域业务的第6个q bit或者偷帧bit 软值
            [27:24] 表示PS，CS域业务的第5个q bit或者偷帧bit 软值
            ，测试用
   UNION结构 ：无 */
#define GBBP_Q_BIT_RPT2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1344)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:16]  译码启动次数计数器上报
 bit[15:4]   保留
 bit[3:0]    译码中断次数计数器上报
   UNION结构:  GBBP_DEC_INT_TOTAL_UNION */
#define GBBP_DEC_INT_TOTAL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1348)

/* 寄存器说明：
 bit[31]     1标识是语音帧相关判决为BFI；
             0标识是语音帧相关判决不是BFI
             
 bit[30:23]  保留
 bit[22:16]  CS语音的PBER上报
 bit[15:8]   保留
 bit[7:0]    CS语音的RSQ_METRIC上报
   UNION结构:  GBBP_BFI_RSQ_METRIC_RPT_UNION */
#define GBBP_BFI_RSQ_METRIC_RPT_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x134C)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第1个USF 译码前软值
            [13:8] 表示PS域业务的第2个USF 译码前软值
            [21:16] 表示PS域业务的第3个USF 译码前软值
            [27:24] 表示PS域业务的第4个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA1_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1500)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第5个USF 译码前软值
            [13:8] 表示PS域业务的第6个USF 译码前软值
            [21:16] 表示PS域业务的第7个USF 译码前软值
            [27:24] 表示PS域业务的第8个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA2_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1504)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第9个USF 译码前软值
            [13:8] 表示PS域业务的第10个USF 译码前软值
            [21:16] 表示PS域业务的第11个USF 译码前软值
            [27:24] 表示PS域业务的第12个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA3_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1508)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第13个USF 译码前软值
            [13:8] 表示PS域业务的第14个USF 译码前软值
            [21:16] 表示PS域业务的第15个USF 译码前软值
            [27:24] 表示PS域业务的第16个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA4_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x150C)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第17个USF 译码前软值
            [13:8] 表示PS域业务的第18个USF 译码前软值
            [21:16] 表示PS域业务的第19个USF 译码前软值
            [27:24] 表示PS域业务的第20个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA5_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1510)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第21个USF 译码前软值
            [13:8] 表示PS域业务的第22个USF 译码前软值
            [21:16] 表示PS域业务的第23个USF 译码前软值
            [27:24] 表示PS域业务的第24个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA6_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1514)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第25个USF 译码前软值
            [13:8] 表示PS域业务的第26个USF 译码前软值
            [21:16] 表示PS域业务的第27个USF 译码前软值
            [27:24] 表示PS域业务的第28个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA7_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1518)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第29个USF 译码前软值
            [13:8] 表示PS域业务的第30个USF 译码前软值
            [21:16] 表示PS域业务的第31个USF 译码前软值
            [27:24] 表示PS域业务的第32个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA8_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x151C)

/* 寄存器说明：
   详      述：[5:0] 表示PS域业务的第33个USF 译码前软值
            [13:8] 表示PS域业务的第34个USF 译码前软值
            [21:16] 表示PS域业务的第35个USF 译码前软值
            [27:24] 表示PS域业务的第36个USF 译码前软值
   UNION结构 ：无 */
#define GBBP_USF_CORR_SOFTDATA9_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1520)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:4]    00表示IDLE（空闲状态）                                     01表示RECV（接收状态）                                     10表示CHECK（校验状态）                                     11无效状态
             测试用
             
 bit[3:2]    保留
 bit[1:0]    00表示IDLE（空闲状态）                                     01表示INIT（初始化状态）                                     10表示CODE（编码状态）                                     11表示INTE（交织状态）
             测试用
             
   UNION结构:  GBBP_UL_CODE_STATE_RPT_UNION */
#define GBBP_UL_CODE_STATE_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x13B0)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件对编码模块内部RAM（编码交织后存储RAM）清零信号，只需开机后，配置一下即可，逻辑自清零
   UNION结构:  GBBP_UL_CODE_RAM_RST_UNION */
#define GBBP_UL_CODE_RAM_RST_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x13B4)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:16]  清零数据块长度
 bit[15:7]   保留
 bit[6:0]    清零起始块地址
   UNION结构:  GBBP_UL_CODE_RAM_RST_CFG_UNION */
#define GBBP_UL_CODE_RAM_RST_CFG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x13B8)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  DRX唤醒切换时GTC此时gtc_timebase计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用
 bit[15:7]   保留
 bit[6:0]    DRX唤醒切换时GTC此时FRAC计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用
   UNION结构:  GBBP_WAKE_TEST_QB_FRAC_RPT_UNION */
#define GBBP_WAKE_TEST_QB_FRAC_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1224)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  DRX唤醒切换时GTC此时T3计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用
 bit[23:21]  保留
 bit[20:16]  DRX唤醒切换时GTC此时T2计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用
 bit[15:11]  保留
 bit[10:0]   DRX唤醒切换时GTC此时T1计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用
   UNION结构:  GBBP_WAKE_TEST_T1_T2_T3_RPT_UNION */
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1228)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  DRX唤醒切换时，此时GTC的FN_HIGH计数值，用于DRX测试用
 bit[15:11]  保留
 bit[10:0]   DRX唤醒切换时，此时GTC的FN_LOW计数值，用于DRX测试用
   UNION结构:  GBBP_WAKE_GTC_FN_RPT_UNION */
#define GBBP_WAKE_GTC_FN_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x122C)

/* 寄存器说明：
   详      述：A51或A52
            加解密算法所需的Kc值低32bit
   UNION结构 ：无 */
#define GBBP_CPU_A5KC_LOW_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1450)

/* 寄存器说明：
   详      述：A51或A52
            加解密算法所需的Kc值高32bit
   UNION结构 ：无 */
#define GBBP_CPU_A5KC_HIGH_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1454)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      内部A53加密算法bit输出顺序配置，请配置为1
 bit[7:5]    保留
 bit[4]      内部A53解密算法bit输出顺序配置，请配置为0
 bit[3:1]    保留
 bit[0]      内部A53加解密算法bit输出顺序配置，请配置为0
   UNION结构:  GBBP_CPU_A5_LSB_SEQ_SEL_UNION */
#define GBBP_CPU_A5_LSB_SEQ_SEL_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1458)

/* 寄存器说明：
   详      述：最近一次解密时所使用的配置内容，测试用：
            [31]：   gsp_dl_gsm_alg_sel；
            [30:29]：gsp_dl_fn_adj_flag[1:0]；
            [28]：   gsp_dl_deciph_en；
            [27:22]：gtc_t3_cnt[5:0]；
            [21:0]： 解密时用的{t1, t3, t2}。
   UNION结构 ：无 */
#define GBBP_DECIPH_CFG_INFO1_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1470)

/* 寄存器说明：
   详      述：最近一次解密时所使用的配置内容，测试用：
            [31:21]：gtc_t1_cnt [10:0]；
            [20:16]：gtc_t2_cnt [4:0]；
            [15:5] ：解密时用的t1；
            [4:0]  ：解密时用的t2。
   UNION结构 ：无 */
#define GBBP_DECIPH_CFG_INFO2_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1474)

/* 寄存器说明：
   详      述：最近一次加密时所使用的配置内容，测试用：
            [31]：   gsp_ul_gsm_alg_sel；
            [30:29]：gsp_ul_fn_adj_flag[1:0]；
            [28]：   gsp_ul_ciph_en；
            [27:22]：gtc_t3_cnt[5:0]；
            [21:0]： 加密时用的{t1, t3, t2}。
   UNION结构 ：无 */
#define GBBP_CIPH_CFG_INFO1_CPU_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1478)

/* 寄存器说明：
   详      述：最近一次加密时所使用的配置内容，测试用：
            [31:21]：gtc_t1_cnt [10:0]；
            [20:16]：gtc_t2_cnt [4:0]；
            [15:5] ：加密时用的t1；
            [4:0]  ：加密时用的t2。
   UNION结构 ：无 */
#define GBBP_CIPH_CFG_INFO2_CPU_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x147C)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:0]   2G下进行4G测量的GAP长度。单位是QB。
             1，2G为主模时，异系统GAP最大长度为大概13*51-2帧左右，就是3305000Qb。
             2，cpu_2g4_gap_length的配置范围是0~3305000QB。
             3，cpu_2g4_gap_length + cpu_2g4_int0_int1_dist的结果，不应超过23'h7f_ffff。
   UNION结构:  GBBP_CPU_2G4_GAP_LENGTH_UNION */
#define GBBP_CPU_2G4_GAP_LENGTH_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1248)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      如果下一帧需要启动2G测4G，则在当前帧的配置时隙，配置该信号为1，并配置cpu_int0_gen_qb。自清零。
 bit[0]      2G下进行4G测量期间，GPHY提前停止occasion的信号，脉冲信号。GBBP收到该信号后，立即停止gap_cnt计数，并上报int2（出沟中断），并拉高通道控制指示信号wg_intrasys_valid_delay。自清零。
   UNION结构:  GBBP_CPU_2G4_GAP_STOP_UNION */
#define GBBP_CPU_2G4_GAP_STOP_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x124C)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:16]  g_intrasys_valid_delay相对于g_intrasys_valid的延迟时间。支持延迟1~3个SSI写操作周期，保证LTE的最后一个射频数据写完。写入一个SSI字，所需时钟周期是27*52.08 = 1406.16 ns，约1.5QB 。默认值配置3（QB）。
 bit[15:12]  保留
 bit[11:0]   2G测4G时，中断0和中断1的间隔时间。单位是QB。
             默认值是108QB（约100us）
   UNION结构:  GBBP_CPU_2G4_DIST_UNION */
#define GBBP_CPU_2G4_DIST_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1250)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:24]  cpu_2g4_int0_en信号触发的计数器，用于观测cpu_2g4_int0_en信号是否生效，如果生效，则每次该计数器自加1，循环计数
 bit[23:18]  保留
 bit[17:16]  cpu_2g4_gap_stop信号触发的计数器，用于观测cpu_2g4_gap_stop信号是否生效，如果生效，则每次该计数器自加1，循环计数
 bit[15:13]  保留
 bit[12:0]   如果下一帧需要启动2G测4G，则在当前帧的配置时隙，配置该信号，表示在下帧帧头之后cpu_2g4_int0_gen_qb个QB，产生中断0
   UNION结构:  GBBP_CPU_2G4_INT0_GEN_QB_UNION */
#define GBBP_CPU_2G4_INT0_GEN_QB_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1254)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  2G测4G时，中断0对应的FN低11位
 bit[15:13]  保留
 bit[12:0]   2G测4G时，中断0对应的timebase，单位是QB
   UNION结构:  GBBP_CPU_2G4_INT0_TIMING_UNION */
#define GBBP_CPU_2G4_INT0_TIMING_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1240)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  2G测4G时，中断2对应的FN低11位
 bit[15:13]  保留
 bit[12:0]   2G测4G时，中断2对应的timebase，单位是QB
   UNION结构:  GBBP_CPU_2G4_INT2_TIMING_UNION */
#define GBBP_CPU_2G4_INT2_TIMING_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1244)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  FB-AFC算法相位估计值参考上限，典型值760。
 bit[15:10]  保留
 bit[9:0]    FB-AFC算法相位估计值参考下限，典型值500。可配300,400,500。
   UNION结构:  GBBP_FB_AFC_PHASE_THRESHOLD_CFG_UNION */
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_ADDR          (SOC_BBP_GSM_BASE_ADDR + 0x1230)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  FB-AFC算法系数fcut的最大值，如果经过α滤波后的相位估计值大于相位估计值的参考上限，则系数fcut的值就等于此最大值。典型值1023。
 bit[15:10]  保留
 bit[9:0]    FB-AFC算法系数fcut的最小值，如果经过α滤波后的相位估计值小雨相位估计值参考下限，则系数fcut的值就等于此最小值。典型值51。
   UNION结构:  GBBP_FB_FCUT_THRESHOLD_CFG_UNION */
#define GBBP_FB_FCUT_THRESHOLD_CFG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1234)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  一阶环路滤波器初始带宽，典型配置：1023。
 bit[15]     保留
 bit[14:12]  对称右移比特数，可配范围0~7。典型配置：4。
 bit[11:8]   Fcut值固定使用FCutInit的跟踪FB数码。可配范围：5~10。典型配置：10。
 bit[7:2]    保留
 bit[1:0]    FB-AFC算法α滤波系数选择：
             0：1/32；
             1：1/16；
             2：1/8；
             3：1/4。
             典型值1/32。
   UNION结构:  GBBP_FB_AFC_ALPHA_SEL_UNION */
#define GBBP_FB_AFC_ALPHA_SEL_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1238)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  本次SB译码BSIC上报。
 bit[23:18]  保留
 bit[17:16]  111优化算法中允许SB译码CRC但对BSIC值不同的总次数
             0：4次；
             1：5次；
             2：6次；
             3：7次。
 bit[15:6]   保留
 bit[5:4]    111优化算法中FB-AFC锁定下允许SB译码CRC错误的次数，取值范围0~3。
 bit[3:1]    保留
 bit[0]      111搜索优化模式使能，1标志打开优化使能，0标志关闭优化使能，采用001 111搜索。
   UNION结构:  GBBP_SRCH_OPT_CFG_UNION */
#define GBBP_SRCH_OPT_CFG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1480)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  RSSI 两轮门限3，单位dBm，推荐-45
 bit[15:8]   RSSI 两轮门限2，单位dBm，推荐-65
 bit[7:0]    RSSI 两轮门限1，单位dBm，推荐-93
   UNION结构:  GBBP_R2_RSSI1234_THRESHOLD_UNION */
#define GBBP_R2_RSSI1234_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5204)

/* 寄存器说明：
 bit[31:24]  RSSI 两轮门限7，单位dBm，暂不使用，默认值-1
 bit[23:16]  RSSI 两轮门限6，单位dBm，暂不使用，默认值为-1
 bit[15:8]   RSSI 两轮门限5，单位dBm，暂不使用，默认值为-1
 bit[7:0]    RSSI 两轮门限4，单位dBm，暂不使用，默认值为-1
   UNION结构:  GBBP_R2_RSSI4567_THRESHOLD_UNION */
#define GBBP_R2_RSSI4567_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5208)

/* 寄存器说明：
 bit[31]     快速AGC测量模式选择信号
             0：快速AGC测量模式按照测量轮数gsp_fast_agc_mode选择
             1：快速AGC测量模式按照测量门限gsp_agc_measure_mode选择
 bit[30:25]  保留
 bit[24]     解调通道直流偏置数字细调环旁路功能，高电平有效，该信号有效时，表示数字细调环不对接受数据进行反馈处理。
 bit[23:16]  保留
 bit[15:12]  RSSI 磁滞范围，单位dBm，默认3。
 bit[11:9]   保留
 bit[8]      解调与搜索通道直流偏置数字细调环旁路功能，高电平有效，该信号有效时，表示数字细调环不对接受数据进行反馈处理。
 bit[7:5]    保留
 bit[4:0]    快速AGC能量计算每轮之间等待时间，单位symbol，默认8。
   UNION结构:  GBBP_AGC_WAIT_LEN_GTH_UNION */
#define GBBP_AGC_WAIT_LEN_GTH_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x520C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  RSSI 三轮门限3，单位dBm，推荐-45
 bit[15:8]   RSSI 三轮门限2，单位dBm，推荐-65
 bit[7:0]    RSSI 三轮门限1，单位dBm，推荐-93
   UNION结构:  GBBP_R3_RSSI1234_THRESHOLD_UNION */
#define GBBP_R3_RSSI1234_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5210)

/* 寄存器说明：
 bit[31:24]  RSSI 三轮门限7，单位dBm，暂不使用，默认值为-1
 bit[23:16]  RSSI 三轮门限6，单位dBm，暂不使用，默认值为-1
 bit[15:8]   RSSI 三轮门限5，单位dBm，暂不使用，默认值为-1
 bit[7:0]    RSSI 三轮门限4，单位dBm，暂不使用，默认值为-1
   UNION结构:  GBBP_R3_RSSI4567_THRESHOLD_UNION */
#define GBBP_R3_RSSI4567_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x521C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  多路数字细调环偏置寄存器经过截位与限幅后的输出，也就是当前档位的直流输出。其可以作为直流偏置校准的参考值。两个14bit信号分别占用IMI总线的[29:16]和[13:0]，低14bit为I路输出，高14bit为Q路输出。
 bit[15:14]  保留
 bit[13:0]   多路数字细调环偏置寄存器经过截位与限幅后的输出，也就是当前档位的直流输出。其可以作为直流偏置校准的参考值。两个14bit信号分别占用IMI总线的[29:16]和[13:0]，低14bit为I路输出，高14bit为Q路输出。
   UNION结构:  GBBP_DC_IQ_REMOVE_RPT_UNION */
#define GBBP_DC_IQ_REMOVE_RPT_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5220)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  时隙前处理Q路直流偏置上报
 bit[15:14]  保留
 bit[13:0]   时隙前处理I路直流偏置上报
   UNION结构:  GBBP_DC_IQ_BURST_REMOVE_RPT_UNION */
#define GBBP_DC_IQ_BURST_REMOVE_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x5224)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   SB解调前载波能量值上报
   UNION结构:  GBBP_SB_THRES_C_UNION */
#define GBBP_SB_THRES_C_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5230)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   SB解调前噪声能量值上报
   UNION结构:  GBBP_SB_THRES_I_UNION */
#define GBBP_SB_THRES_I_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5234)

/* 寄存器说明：
 bit[31]     快慢速测量标志。1表示当前时快速测量；0表示当前是慢速测量。
 bit[30:27]  保留
 bit[26:24]  当前AAGC档位上报。
 bit[23:20]  保留
 bit[19:8]   RSSI值，单位是0.125dBm，上报给CPU，该值已是空口的RSSI值。
 bit[7:3]    保留
 bit[2:0]    AGC期望控制增益。在快速模式最后一轮和慢速模式下统计结束后上报给CPU。
   UNION结构:  GBBP_AAGC_NEXT_GAIN_UNION */
#define GBBP_AAGC_NEXT_GAIN_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5250)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  当前测量的RSSI对应的频点号，[27:26]为band号，band号与频段的关系由软件自己定义，[25:16]为band内的频点号，该值由GTC指令配置，{GSP_RSSI_FRQ_HIGH_ADDR,GSP_RSSI_FRQ_LOW_ADDR},BBP进行延时后于测量中断一起上报。
 bit[15:13]  保留
 bit[12:0]   测量中断时刻TDMA帧QB值。
   UNION结构:  GBBP_RSSI_QB_FRQ_UNION */
#define GBBP_RSSI_QB_FRQ_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x5254)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:0]   DRSSI求对数运算前数据上报。
   UNION结构:  GBBP_DRSSI_ENERGY_RPT_UNION */
#define GBBP_DRSSI_ENERGY_RPT_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5258)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  RSSI值，单位0.125dBm，其就是空口信号能量，为快速测量第二轮RSSI上报。
 bit[15:12]  保留
 bit[11:0]   RSSI值，单位0.125dBm，其就是空口信号能量，为快速测量第一轮RSSI上报。
   UNION结构:  GBBP_AGC_FAST1_2_RSSI_CPU_UNION */
#define GBBP_AGC_FAST1_2_RSSI_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x525C)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  NB业务译码中断所在TDMA帧号模51计数值
 bit[15:6]   保留
 bit[5:0]    AGC测量中断所在TDMA帧号模51计数值
   UNION结构:  GBBP_AGC_DEC_INT_T3_FN_UNION */
#define GBBP_AGC_DEC_INT_T3_FN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5214)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  解调中断所在TDMA帧号模51计数值
 bit[15:13]  保留
 bit[12:0]   解调中断所在TDMA QB计数值
   UNION结构:  GBBP_DEM_INT_FN_QB_UNION */
#define GBBP_DEM_INT_FN_QB_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x5218)

/* 寄存器说明：
 bit[31]     8bit定向线控信号写使能指示信号
 bit[30:8]   保留
 bit[7:0]    定向线控CPU接口配置，其中
             bit0对应rf_tcvr_on,即射频芯片工作使能信号
             bit1对应rf_tx_en,即射频上行发送工作使能信号
             bit2对应rf_rst_n,即射频复位控制信号
             bit3对应abb_rxa_en,即ABB RXA通道使能信号
             bit4对应abb_rxb_en,即ABB RXB通道使能信号
             bit5对应abb_tx_en,即ABB TX通道使能信号
             bit6对应gapc_en，即Auxdac通道使能信号
   UNION结构:  GBBP_CPU_EXT_LINE_CTRL_UNION */
#define GBBP_CPU_EXT_LINE_CTRL_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5E04)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6:0]    定向线控实际状态，测试用。
             bit0对应rf_tcvr_on,即射频芯片工作使能信号
             bit1对应rf_tx_en,即射频上行发送工作使能信号
             bit2对应rf_rst_n,即射频复位控制信号
             bit3对应abb_rxa_en,即ABB RXA通道使能信号
             bit4对应abb_rxb_en,即ABB RXB通道使能信号
             bit5对应abb_tx_en,即ABB TX通道使能信号
             bit6对应gapc_en，即Auxdac通道使能信号
   UNION结构:  GBBP_CPU_GSP_EXT_LINE_STATE_RPT_UNION */
#define GBBP_CPU_GSP_EXT_LINE_STATE_RPT_ADDR          (SOC_BBP_GSM_BASE_ADDR + 0x5E08)

/* 寄存器说明：
 bit[31]     cpu_line01_sel_ctrl生效出发信号，即当此信号写为1后，cpu_line01_sel_ctrl对应的配置生效，逻辑自清零。
             注：要求bit[3:0]事先配置号。
 bit[30:4]   保留
 bit[3:0]    bit0对应主模MIPI和从模MIPI通道控制选择；
             bit1对应AUXDAC0和AUXDAC1控制选择；
             bit2对应ABB CH0与ABB CH1通道控制选择，由于V9R1不存在两个ABB通道，因此该配置默认配置为0，无需改动；
             bit3对应主模RFIC与从模RFIC通道控制选择。
             G为主模时，配置为4’d0；G为从模时，配置为4’d9。
   UNION结构:  GBBP_CPU_LINE01_SEL_CFG_UNION */
#define GBBP_CPU_LINE01_SEL_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5E0C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    通道选择信号实际状态，测试用。
             bit0：gtc_mipi01_sel；
             bit1：gtc_auxdac01_sel；
             bit2：gtc_abb01_sel；
             bit3：gtc_rf01_sel。
   UNION结构:  GBBP_CPU_LINE01_SEL_STATE_RPT_UNION */
#define GBBP_CPU_LINE01_SEL_STATE_RPT_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x5E10)

/* 寄存器说明：
 bit[31]     AGC模块配置前向通道增益调整值和RXCORR参数存储RAM和DC_OFFSET存储RAM TDMA帧头乒乓切换使能
             1表示允许乒乓切换
             0表示不允许乒乓切换，固定为乒页；当该信号为1时，逻辑内部在TDMA帧头自动切换乒乓标志。
 bit[30:0]   保留
   UNION结构:  GBBP_CPU_OFC_RXCM_REG_UNION */
#define GBBP_CPU_OFC_RXCM_REG_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5360)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12]     测量通道直流偏置数字细调环旁路功能，高电平有效。
             该信号有效时，相当于数字细调环不对接收数据进行反馈处理。
 bit[11:9]   保留
 bit[8]      采样点组选择配置，该信号需要用帧头锁存。
             0：表示选择1个symbol中的1/3样点组；
             1：表示选择1个symbol中的2/4样点组。
 bit[7:6]    保留
 bit[5:4]    bit1:1表示时硬件自判决模式，0表示时软件控制模式。当bit为0时，bit0意义才生效。样点组内奇偶选择信号，0表示选中样点组内偶路数据，1表示选中样点组内奇路数据。用于8PSK解调和搜索。2'b11配置时保留值，请勿配置。在搜索模式下请勿配置为2'bx1模式。
 bit[3:0]    保留
   UNION结构:  GBBP_CPU_SAMPLE_REG_UNION */
#define GBBP_CPU_SAMPLE_REG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x536C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      AGC直流偏执RAM和通道增益RAM手动切换指示信号，该信号为脉冲信号，自清零。
   UNION结构:  GBBP_CPU_AGC_RAM_SWITCH_IND_UNION */
#define GBBP_CPU_AGC_RAM_SWITCH_IND_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x5370)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24:16]  软件强制配置的DRSSI值，单位0.25dBm。
 bit[15:9]   保留
 bit[8:0]    DRSSI值上报，其对应为ABB输出信号的能量，单位0.25dBm。
   UNION结构:  GBBP_DAGC_MULFACTOR_FIX_UNION */
#define GBBP_DAGC_MULFACTOR_FIX_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x537C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第1档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN1_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN1_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5584)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第2档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN2_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN2_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5588)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第3档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN3_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN3_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x558C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第4档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN4_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN4_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5590)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第5档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN5_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN5_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5594)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第6档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN6_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN6_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5598)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第7档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN7_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN7_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x559C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   主集天线控制增益模式下第8档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_MAIN_GAIN8_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN8_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x55A0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第1档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN1_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN1_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55A4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第2档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN2_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN2_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55A8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第3档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN3_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN3_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55AC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第4档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN4_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN4_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55B0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第5档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN5_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN5_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55B4)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第6档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN6_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN6_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55B8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第7档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN7_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN7_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55BC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   分集天线控制增益模式下第8档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。
   UNION结构:  GBBP_CPU_DIV_GAIN8_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN8_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55C0)

/* 寄存器说明：
 bit[31]     NB-AFC控制方式选择。
             0：GTC控制；
             1：CPU控制；
             默认CPU控制。
 bit[30:2]   保留
 bit[1]      二阶环快慢速阶段控制，
             0：表示采用慢速跟踪；
             1：表示采用快速跟踪。
 bit[0]      一阶环与二阶环选择控制信号，
             0：选择一阶环；
             1：选择二阶环。
   UNION结构:  GBBP_NB_AFC_LOOP_SWITCH_UNION */
#define GBBP_NB_AFC_LOOP_SWITCH_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5340)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    AFC K值调整，默认值为10’d84，TCXO方案下保持默认值，DCXO方案下根据实际系统进行调整。
   UNION结构:  GBBP_ADDR_AFC_K_VALUE_UNION */
#define GBBP_ADDR_AFC_K_VALUE_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5E00)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  慢速调整阶段环路滤波器系数Ka。
             0：16'd33141；
             1：16'd22094；
             2：16'd7365；
             3：16'd4419；
             4：16'd3682；
             5：16'd3156；
             6：16'd2455；
             7：16'd2209。
             默认配置：2。
 bit[15]     保留
 bit[14:12]  慢速调整阶段环路滤波器系数Ka的右移位数。
             0：07；
             1：08；
             2：09；
             3：10；
             4：11；
             5：12；
             6：13；
             7：14。
             默认配置：4。
 bit[11]     保留
 bit[10:8]   慢速调整阶段环路滤波器系数Kp的右移位数。
             0:7
             1:6
             2:5
             3:4
             4:3
             5:2
             6:1
             7:0
             默认配置:6
 bit[7]      保留
 bit[6:4]    慢速调整阶段环路滤波器系数Ki的右移位数。
             0:1
             1:2
             2:3
             3:4
             4:5
             5:6
             6:7
             7:8
             默认配置:6
 bit[3:2]    保留
 bit[1:0]    慢速调整阶段环路滤波器系数Kint的右移位数。
             0:8
             1:9
             2:10
             3:11
             默认配置:1
   UNION结构:  GBBP_ADDR_NB_AFC_LOOP_SLOW_UNION */
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5E14)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  快速调整阶段环路滤波器系数Ka。
             0:16’d33141
             1:16’d22094
             2:16’d7365
             3:16’d4419
             4:16’d3682
             5:16’d3156
             6:16’d2455
             7:16’d2209
             默认配置:2
 bit[15]     保留
 bit[14:12]  快速调整阶段环路滤波器系数Ka的右移位数。
             0：07；
             1：08；
             2：09；
             3：10；
             4：11；
             5：12；
             6：13；
             7：14。
             默认配置：3。
 bit[11]     保留
 bit[10:8]   快速调整阶段环路滤波器系数Kp的左移位数。
             0:7
             1:6
             2:5
             3:4
             4:3
             5:2
             6:1
             7:0
             默认配置:6
 bit[7]      保留
 bit[6:4]    快速调整阶段环路滤波器系数Ki的右移位数。
             0:1
             1:2
             2:3
             3:4
             4:5
             5:6
             6:7
             7:8
             默认配置:1
 bit[3:2]    保留
 bit[1:0]    快速调整阶段环路滤波器系数Kint的右移位数。
             0:8
             1:9
             2:10
             3:11
             默认配置:1
   UNION结构:  GBBP_ADDR_NB_AFC_LOOP_FAST_UNION */
#define GBBP_ADDR_NB_AFC_LOOP_FAST_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5E18)

/* 寄存器说明：
   详      述：二阶环当前NB-AFC环路滤波累加器的上报值
   UNION结构 ：无 */
#define GBBP_AFC_LOOP2_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x5E1C)

/* 寄存器说明：
   详      述：上电后二阶环NB-AFC环路滤波累加器的配置值。
            再配置cpu_afc_init_en为1后生效。
   UNION结构 ：无 */
#define GBBP_CPU_AFC_LOOP2_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5E20)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   本次解调中断时刻对应的频点
   UNION结构:  GBBP_ADDR_DEM_INT_FRQ_UNION */
#define GBBP_ADDR_DEM_INT_FRQ_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5E2C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  本次译码中断上报时可对应的TDMA QB信息
 bit[15:12]  保留
 bit[11:0]   本次译码中断上报时刻对应的频点信息
   UNION结构:  GBBP_ADDR_DEC_INT_FREQ_UNION */
#define GBBP_ADDR_DEC_INT_FREQ_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5E30)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  [21:16] 6’b0 RO 本次中断上报时刻对应的TDMA帧号（gtc_t3_cnt）
 bit[15:13]  保留
 bit[12:0]   本次搜索中断上报时刻对应的TDMA QB
   UNION结构:  GBBP_ADDR_SRCH_INT_TDMA_QB_UNION */
#define GBBP_ADDR_SRCH_INT_TDMA_QB_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5E34)

/* 寄存器说明：
   详      述：第五近的一个BURST解调前半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENZI5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x530C)

/* 寄存器说明：
   详      述：第五近的一个BURST解调前半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENMU5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5310)

/* 寄存器说明：
   详      述：第五近的一个BURST解调后半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENZI5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5314)

/* 寄存器说明：
   详      述：第五近的一个BURST解调后半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENMU5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5318)

/* 寄存器说明：
   详      述：第六近的一个BURST解调前半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENZI6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x531C)

/* 寄存器说明：
   详      述：第六近的一个BURST解调前半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ1_FENMU6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5320)

/* 寄存器说明：
   详      述：第六近的一个BURST解调后半个BURST的MQ平方的分子值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENZI6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5324)

/* 寄存器说明：
   详      述：第六近的一个BURST解调后半个BURST的MQ平方的分母值上报，对应BURST为DummyBurst，该上报信息不准确，不能使用。
   UNION结构 ：无 */
#define GBBP_MQ2_FENMU6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5328)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   读取时刻前第五近burst对应的载波能量值，无符号数。
   UNION结构:  GBBP_VALPP_CARRIER_ENERGY4_UNION */
#define GBBP_VALPP_CARRIER_ENERGY4_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x532C)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   读取时刻前第五近burst对应的干扰能量值，无符号数。
   UNION结构:  GBBP_VALPP_INTERFERE_ENERGY4_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY4_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5330)

/* 寄存器说明：
 bit[31]     读取时刻第五近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过写bit30对该bit清零，指示该信息已经读取。
 bit[30]     对demod_info_valid_flag4清零。写1清零。
 bit[29:28]  读取时刻前的第五近BURST对应的一次判决的调制方式，
             0：GMSK调制；
             1：8PSK调制；
             2：DummyBurst。
             该寄存器测试使用。
 bit[27:25]  保留
 bit[24]     读取时刻第五近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[23]     保留
 bit[22:20]  读取时刻第五近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[19:16]  读取时刻第五近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。
 bit[15:14]  读取时刻第五近BURST的调制方式，
             0：GSKM；
             1：8PSK；
             2：DummyBurst。
 bit[13:0]   保留
   UNION结构:  GBBP_VALPP_DEM_TYPE_TOA4_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA4_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5298)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   读取时刻前第六近burst对应的载波能量值，无符号数。
   UNION结构:  GBBP_VALPP_CARRIER_ENERGY5_UNION */
#define GBBP_VALPP_CARRIER_ENERGY5_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5334)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   读取时刻前第六近burst对应的干扰能量值，无符号数。
   UNION结构:  GBBP_VALPP_INTERFERE_ENERGY5_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY5_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5338)

/* 寄存器说明：
 bit[31]     读取时刻第六近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过bit30对该bit清零，指示该信息已经读取。
 bit[30]     对demod_info_valid_flag5清零。写1清零。
 bit[29:28]  读取时刻前的第六近BURST对应的一次判决的调制方式，
             0：GMSK调制；
             1：8PSK调制；
             2：DummyBurst。
             该寄存器测试使用。
 bit[27:25]  保留
 bit[24]     读取时刻第六近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[23]     保留
 bit[22:20]  读取时刻第六近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。
 bit[19:16]  读取时刻第六近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。
 bit[15:14]  读取时刻第六近BURST的调制方式，
             0：GSKM；
             1：8PSK；
             2：DummyBurst。
 bit[13:0]   保留
   UNION结构:  GBBP_VALPP_DEM_TYPE_TOA5_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA5_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x533C)

/* 寄存器说明：
 bit[31]     NB纠偏使能信号，0表示关闭频偏检测及纠偏，1表示打开。默认为0。
 bit[30]     SB纠偏使能信号，0表示关闭频偏检测及纠偏，1表示打开。
             V9R1/V3R3不支持该功能，必须配置为0。
             
 bit[29:24]  保留
 bit[23]     SB频偏值计算因子，0表示系数为1.25，1表示系数为1
 bit[22:11]  保留
 bit[10:8]   解调模块用，纠偏状态第一个子状态，判决是否满足纠偏条件. 对应链路信号名 EnergyThreshold：，默认值12。含义：通过信道估计计算全部能量和部分能量。可选值9,10, 11,12,13,14,15，
             CPU数值对应关系：0-6。
             
 bit[7:3]    保留
 bit[2:0]    该门限用于解调模块内部，判决是否做纠偏 对应链路信号名CIThreshold，默认值10。
             可选值7,8,9,10,11,12,13，
             CPU数值对应关系：0-6。
             
   UNION结构:  GBBP_CPU_JITTER_CORR_CFG1_UNION */
#define GBBP_CPU_JITTER_CORR_CFG1_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53B4)

/* 寄存器说明：
 bit[31]     保留
 bit[30:16]  SB jitterOn算法当前频偏上报
 bit[15]     保留
 bit[14:0]   JITTER ON消除算法当前频偏上报
   UNION结构:  GBBP_PHI_DEV_CPU_UNION */
#define GBBP_PHI_DEV_CPU_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x53B8)

/* 寄存器说明：
 bit[31]     NB频偏校准范围继承使能，默认值是1。
 bit[30:21]  保留
 bit[20:16]  软件和芯片都用，对偏差限幅。对应链路信号 FrOffLim 。默认值20，可选值14,16,18,20,22, 24；
 bit[15:12]  保留
 bit[11:8]   对应于链路中的FrOffLim_STEP，取值范围5 6 7 8 9，默认值是7
 bit[7:3]    保留
 bit[2:0]    对应于链路中的SNR_THRES，用于计算纠偏范围 fr_off_lim_act，以及调整参数, 默认值100, 取值范围90 95 100 105 110,CPU数值对应0～4
   UNION结构:  GBBP_CPU_JITTER_CORR_CFG2_UNION */
#define GBBP_CPU_JITTER_CORR_CFG2_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53BC)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件规避模式下响应解调中断后读取训练序列数据上报RAM的上报机制控制,多时隙下需使用乒乓操作模式
             1表示CPU访问训练序列数据上报RAM采用乒乓RAM访问模式，
             0表示CPU访问训练序列数据上报RAM采用非乒乓RAM访问模式
             
   UNION结构:  GBBP_CPU_TSC_SWITCH_EN_UNION */
#define GBBP_CPU_TSC_SWITCH_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x53C4)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器0，I路参数p1，默认值：14'd0。
 bit[15:14]  保留
 bit[13:0]   滤波器0，I路参数p0，默认值：14'd0。
   UNION结构:  GBBP_CPU_FILTER0_P0_P1_UNION */
#define GBBP_CPU_FILTER0_P0_P1_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5800)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器0，I路参数p3，默认值：14'd0。
 bit[15:14]  保留
 bit[13:0]   滤波器0，I路参数p2，默认值：14'd0。
   UNION结构:  GBBP_CPU_FILTER0_P2_P3_UNION */
#define GBBP_CPU_FILTER0_P2_P3_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5804)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器0，I路参数p5，默认值：14'd4096。
 bit[15:14]  保留
 bit[13:0]   滤波器0，I路参数p4，默认值：14'd0。
   UNION结构:  GBBP_CPU_FILTER0_P4_P5_UNION */
#define GBBP_CPU_FILTER0_P4_P5_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5808)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器3，I路参数p1，默认值：-14'd113。
 bit[15:14]  保留
 bit[13:0]   滤波器3，I路参数p0，默认值：-14'd167。
   UNION结构:  GBBP_CPU_FILTER3_P0_P1_UNION */
#define GBBP_CPU_FILTER3_P0_P1_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x580C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器3，I路参数p3，默认值：14'd1018。
 bit[15:14]  保留
 bit[13:0]   滤波器3，I路参数p2，默认值：-14'd273。
   UNION结构:  GBBP_CPU_FILTER3_P2_P3_UNION */
#define GBBP_CPU_FILTER3_P2_P3_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5810)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器3，I路参数p5，默认值：14'd2228。
 bit[15:14]  保留
 bit[13:0]   滤波器3，I路参数p4，默认值：14'd377。
   UNION结构:  GBBP_CPU_FILTER3_P4_P5_UNION */
#define GBBP_CPU_FILTER3_P4_P5_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5814)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器1，I路参数p1，默认值：14'd168。
 bit[15:14]  保留
 bit[13:0]   滤波器1，I路参数p0，默认值：14'd17。
   UNION结构:  GBBP_CPU_FILTER1_P0_P1_I_UNION */
#define GBBP_CPU_FILTER1_P0_P1_I_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5818)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器1，I路参数p3，默认值：14'd185。
 bit[15:14]  保留
 bit[13:0]   滤波器1，I路参数p2，默认值：14'd22。
   UNION结构:  GBBP_CPU_FILTER1_P2_P3_I_UNION */
#define GBBP_CPU_FILTER1_P2_P3_I_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x581C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器1，I路参数p5，默认值：14'd1738。
 bit[15:14]  保留
 bit[13:0]   滤波器1，I路参数p4，默认值：14'd1116。
   UNION结构:  GBBP_CPU_FILTER1_P4_P5_I_UNION */
#define GBBP_CPU_FILTER1_P4_P5_I_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5820)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器1，Q路参数p1，默认值：14'd219。
 bit[15:14]  保留
 bit[13:0]   滤波器1，Q路参数p0，默认值：14'd6。
   UNION结构:  GBBP_CPU_FILTER1_P0_P1_Q_UNION */
#define GBBP_CPU_FILTER1_P0_P1_Q_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5824)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器1，Q路参数p3，默认值：-14'd377。
 bit[15:14]  保留
 bit[13:0]   滤波器1，Q路参数p2，默认值：14'd219。
   UNION结构:  GBBP_CPU_FILTER1_P2_P3_Q_UNION */
#define GBBP_CPU_FILTER1_P2_P3_Q_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5828)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  滤波器1，Q路参数p5，默认值：14'd0。
 bit[15:14]  保留
 bit[13:0]   滤波器1，Q路参数p4，默认值：-14'd694。
   UNION结构:  GBBP_CPU_FILTER1_P4_P5_Q_UNION */
#define GBBP_CPU_FILTER1_P4_P5_Q_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x582C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1：dagc输入数据不经滤波器处理直接输出
             0：dagc输入数据经滤波器处理后输出
             
   UNION结构:  GBBP_CPU_GACI_DATA_BYPASS_UNION */
#define GBBP_CPU_GACI_DATA_BYPASS_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x5880)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  判决可配置门限
             3’b000:   5
             3’b001:   6
             3’b010:   7
             3’b011:   8
             3’b100:   9
             3’b101:   10
             默认值:   6
             
 bit[15:3]   保留
 bit[2:0]    判决可配置门限
             3’b000:   2
             3’b001:   3
             3’b010:   4
             3’b011:   5
             3’b100:   6
             3’b101:   7
             3’b110:   8
             3’b111:   9
             默认值:   5
             
   UNION结构:  GBBP_CPU_GACI_PARA_UNION */
#define GBBP_CPU_GACI_PARA_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x5884)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    输出邻频检测结果，上报CPU四种可能的干扰状态：
             2’b00：无干扰
             2’b01：+200Khz干扰
             2’b10：-200Khz干扰
             2’b11： 200Khz干扰
             
   UNION结构:  GBBP_GACI_INDEX_CPU_UNION */
#define GBBP_GACI_INDEX_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x58A0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   GACI参数，由ematrix_03_cpu_cpu与ematrix_12_cpu产生
   UNION结构:  GBBP_GACI_RACI_CPU_UNION */
#define GBBP_GACI_RACI_CPU_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x58A4)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   GACI参数，在EMATRIX状态下产生的判决参数，由经过高通后数据求能量产生。
   UNION结构:  GBBP_GACI_RPOWER_CPU_UNION */
#define GBBP_GACI_RPOWER_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x58A8)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   GACI参数，在EMATRIX状态下产生的判决参数，由经过高通后数据求相关产生。
   UNION结构:  GBBP_GACI_EMATRIX_03_CPU_UNION */
#define GBBP_GACI_EMATRIX_03_CPU_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x58AC)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:0]   GACI参数，在EMATRIX状态下产生的判决参数，由经过高通后数据求相关产生。
   UNION结构:  GBBP_GACI_EMATRIX_12_CPU_UNION */
#define GBBP_GACI_EMATRIX_12_CPU_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x58B0)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:0]   GACI未经过高通处理，原输入数据能量，在ENERGY1状态产生
   UNION结构:  GBBP_GACI_AVG_ALL_CPU_UNION */
#define GBBP_GACI_AVG_ALL_CPU_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x58B4)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:0]   GACI经过高通处理，原输入数据能量，在ENERGY2状态产生
   UNION结构:  GBBP_GACI_AVG_HP_CPU_UNION */
#define GBBP_GACI_AVG_HP_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x58B8)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    AMR带内bit优化算法中针对SPEECH CRC的保护次数，配置范围0～3，代表保护次数为1～4，默认值为3
             （当业务类型为GMSK WBAMR时，配置范围为0～2）
             
   UNION结构:  GBBP_CPU_AMR_CRC_PRO_NUM_CFG_UNION */
#define GBBP_CPU_AMR_CRC_PRO_NUM_CFG_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x53CC)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:0]   AMR带内bit优化算法中00对应的先验概率
   UNION结构:  GBBP_CPU_P0_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P0_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53D0)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:0]   AMR带内bit优化算法中01对应的先验概率
   UNION结构:  GBBP_CPU_P1_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P1_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53D4)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:0]   AMR带内bit优化算法中10对应的先验概率
   UNION结构:  GBBP_CPU_P2_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P2_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53D8)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:0]   AMR带内bit优化算法中11对应的先验概率
             AFS下算法推荐配置为-6000，AHS下算法推荐配置为-4000
   UNION结构:  GBBP_CPU_P3_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P3_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53DC)

/* 寄存器说明：
 bit[31:16]  CMI带内bit 1对应的先验概率上报
 bit[15:0]   CMI带内bit 0对应的先验概率上报
   UNION结构:  GBBP_CMI_P01_PRIOR_PRE_RPT_UNION */
#define GBBP_CMI_P01_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5380)

/* 寄存器说明：
 bit[31:16]  CMI带内bit 3对应的先验概率上报
 bit[15:0]   CMI带内bit 2对应的先验概率上报
   UNION结构:  GBBP_CMI_P23_PRIOR_PRE_RPT_UNION */
#define GBBP_CMI_P23_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5384)

/* 寄存器说明：
 bit[31:16]  CMC带内bit 1对应的先验概率上报
 bit[15:0]   CMC带内bit 0对应的先验概率上报
   UNION结构:  GBBP_CMC_P01_PRIOR_PRE_RPT_UNION */
#define GBBP_CMC_P01_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5388)

/* 寄存器说明：
 bit[31:16]  CMC带内bit 3对应的先验概率上报
 bit[15:0]   CMC带内bit 2对应的先验概率上报
   UNION结构:  GBBP_CMC_P23_PRIOR_PRE_RPT_UNION */
#define GBBP_CMC_P23_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x538C)

/* 寄存器说明：
 bit[31:16]  CMC或者CMI 带内bit 1对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率
 bit[15:0]   CMC或者CMI 带内bit 0对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率
   UNION结构:  GBBP_CPU_P01_MAPPRE_CFG_UNION */
#define GBBP_CPU_P01_MAPPRE_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5390)

/* 寄存器说明：
 bit[31:16]  CMC或者CMI 带内bit 3对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率
 bit[15:0]   CMC或者CMI 带内bit 2对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率
   UNION结构:  GBBP_CPU_P23_MAPPRE_CFG_UNION */
#define GBBP_CPU_P23_MAPPRE_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5394)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  AMR判决算法中绝对门限，AFS推荐值为233，AHS推荐值为230
 bit[15:9]   保留
 bit[8]      1标识当前译码中断所在周期是CMC周期
             0标识当前译码中断所在周期是CMI周期。
 bit[7:3]    保留
 bit[2]      1标识采用C02通过状态来判决NODATA的模式
             0标识采用V3 AMR相关译码的判决方式。
 bit[1]      0标识加载CMI的历史先验概率，1标识加载CMC的历史先验概率
 bit[0]      1标识需要做加载CMI或者CMC的历史先验概率，该信号配置之前需要软件先配置CPU_P01_MAPPRE_CFG，CPU_P23_MAPPRE_CFG寄存器
   UNION结构:  GBBP_CPU_CMC_CMI_LOAD_EN_UNION */
#define GBBP_CPU_CMC_CMI_LOAD_EN_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5398)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  AMR相关最大帧类型相关累加和上报
 bit[15:14]  保留
 bit[13:8]   AMR相关最大帧类型上报
 bit[7:6]    保留
 bit[5:0]    AMR译码帧类型上报
   UNION结构:  GBBP_AMR_INFO1_RPT_UNION */
#define GBBP_AMR_INFO1_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x53F8)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      AMR判决算法公式上报
 bit[1]      AMR判决算法公式上报
 bit[0]      AMR判决算法公式上报
   UNION结构:  GBBP_AMR_INFO2_RPT_UNION */
#define GBBP_AMR_INFO2_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x53FC)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    AFS/AHS 相关译码判决公式门限参数，配置范围0～15，推荐配置为10
   UNION结构:  GBBP_CPU_AMR_CORR_COEFF_CFG_UNION */
#define GBBP_CPU_AMR_CORR_COEFF_CFG_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x53E0)

/* 寄存器说明：
 bit[31:16]  VALPP RAM单口访问冲突计数器
             [31:28] DEM和CARRY过程发生读，写冲突
             [27:20]  DEMAP和MAP过程发生读，写冲突
             [23:20] DEMAP和CARRY过程发生读，写冲突
             [19:16] DEMAP和DEM模块发生读，写冲突
             
 bit[15:8]   保留
 bit[7:0]    [3:0] 编码过程中启动了下行译码配置冲突计数器上报
             [7:4]：译码过程中启动了上行编码配置冲突计数器上报
             
   UNION结构:  GBBP_CODEC_WR_CONFLICT_CNT_UNION */
#define GBBP_CODEC_WR_CONFLICT_CNT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5718)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     HARQ外置模式下，是否根据CRC结果对外置DDR进行访问，1表示不管CRC结果，强行将数据存入HARQ MEM，0表示根据CRC结果将数据存入HARQ MEM。
 bit[15:1]   保留
 bit[0]      HARQ内置模式与外置模式选择信号，1表示使用外置模式，0表示使用内置模式。
   UNION结构:  GBBP_ADDR_HARQ_MODE_UNION */
#define GBBP_ADDR_HARQ_MODE_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5A00)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      HARQ外置模式下，异常复位信号，脉冲信号，写1复位。
   UNION结构:  GBBP_ADDR_HARQ_INIT_EN_UNION */
#define GBBP_ADDR_HARQ_INIT_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A04)

/* 寄存器说明：
   详      述：HARQ外置模式下，CPU分配的HARQ DDR写操作基地址。
   UNION结构 ：无 */
#define GBBP_ADDR_HARQ_WR_BASE_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A08)

/* 寄存器说明：
   详      述：HARQ外置模式下，CPU分配的HARQ DDR读操作基地址。
   UNION结构 ：无 */
#define GBBP_ADDR_HARQ_RD_BASE_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A0C)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:16]  HARQ外置模式下，译码中断异常状态上报值。
             1’b1：译码超时
             1’b0：译码未超时
             
 bit[15:4]   保留
 bit[3:0]    HARQ外置模式下，DDR每次写FIFO的burst长度。
   UNION结构:  GBBP_ADDR_DDR_HARQ_CFG_UNION */
#define GBBP_ADDR_DDR_HARQ_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A10)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      数字滤波器使能信号，用来控制调制后数据是否经过16阶数字滤波器；默认值：0。
   UNION结构:  GBBP_ADDR_TX_RRC_PILTER_EN_UNION */
#define GBBP_ADDR_TX_RRC_PILTER_EN_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5A14)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      HARQ外置模式下，Harq Ram写使能超时保护旁路信号。此信号生效表示Harq Ram写使能不做超时保护。默认值为0，表示进行超时保护。
   UNION结构:  GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_UNION */
#define GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_ADDR          (SOC_BBP_GSM_BASE_ADDR + 0x5A18)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     GBBP定时锁定状态清零信号，写1有效，自清零，该信号有效时，timing_get_state状态清零
 bit[15:1]   保留
 bit[0]      GBBP定时锁定启动信号，写1有效，自清零，该信号有效时，GBBP启动定时锁存。
   UNION结构:  GBBP_CPU_TIMING_GET_TRIGGER_UNION */
#define GBBP_CPU_TIMING_GET_TRIGGER_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x5A20)

/* 寄存器说明：
 bit[31]     定时锁定状态上报，当cpu_timing_get_state_clr有效时该比特上报自行清零。
 bit[30:27]  保留
 bit[26:16]  GTC此时实际帧号高位
 bit[15:11]  保留
 bit[10:0]   GTC此时实际帧号低位
   UNION结构:  GBBP_TIMING_GET_FN_RPT_UNION */
#define GBBP_TIMING_GET_FN_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A24)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  绝对时标QB上报，计数范围0~4999，对应一帧的长度。该值只与复位时刻有关，测试用
 bit[15:13]  保留
 bit[12:0]   当前时刻TDMA的QB计数值
   UNION结构:  GBBP_TIMING_GET_TIMEBASE_RPT_UNION */
#define GBBP_TIMING_GET_TIMEBASE_RPT_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5A28)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1标识：LoopC环回时，偷帧bit位置固定返回1’b0。
             0标识：LoopC环回时，偷帧bit位置返回解调软值的符号位。
             
   UNION结构:  GBBP_LOOPC_MODE_CFG_UNION */
#define GBBP_LOOPC_MODE_CFG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x53F0)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:16]  上行编码块的cbindex上报
 bit[15:10]  保留
 bit[9:8]    上行编码块起始位置上报
 bit[7:4]    保留
 bit[3:0]    上行编码次数上报
   UNION结构:  GBBP_COD_CBINDEX_RPT_UNION */
#define GBBP_COD_CBINDEX_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x53F4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  上行发射校准时强制I路调制输出为该配置数据
 bit[15:12]  保留
 bit[11:0]   上行发射校准时强制Q路调制输出为该配置数据
   UNION结构:  GBBP_CPU_IQ_MOD_DTA_UNION */
#define GBBP_CPU_IQ_MOD_DTA_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x53C8)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  8PSK上行调制数据缩放因子，缩放幅度默认约为1023/1024=1。
 bit[15:10]  保留
 bit[9:0]    GMSK上行调制数据缩放因子，缩放幅度默认约为921/1024=0.9。
   UNION结构:  GBBP_TX_DATA_MULFACTOR_UNION */
#define GBBP_TX_DATA_MULFACTOR_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5374)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   时隙去直流启动门限，即时隙去直流是否启动取决于当前时隙的RSSI大小。当大于该门限时，如果配置时隙去直流模式，反之则不启动。默认门限-12'd1200，相当于-150dBm。由于空口接收信号不可能小于该值，相当于默认不屏蔽启动时隙去直流。
   UNION结构:  GBBP_SLOT_DCR_RSSI_THRESHOLD_UNION */
#define GBBP_SLOT_DCR_RSSI_THRESHOLD_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5378)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   GMSK待调制数据（编码后、调制前）上报，0～29比特，顺序为从低到高
   UNION结构:  GBBP_MOD_BIT0_RPT_UNION */
#define GBBP_MOD_BIT0_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53A0)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   GMSK待调制数据（编码后、调制前）上报，30～59比特，顺序为从低到高
   UNION结构:  GBBP_MOD_BIT1_RPT_UNION */
#define GBBP_MOD_BIT1_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53A4)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   GMSK待调制数据（编码后、调制前）上报，60～89比特，顺序为从低到高
   UNION结构:  GBBP_MOD_BIT2_RPT_UNION */
#define GBBP_MOD_BIT2_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53A8)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   GMSK待调制数据（编码后、调制前）上报，90～119比特，顺序为从低到高
   UNION结构:  GBBP_MOD_BIT3_RPT_UNION */
#define GBBP_MOD_BIT3_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53AC)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   GMSK待调制数据（编码后、调制前）上报，120～147比特，顺序为从低到高。编码后最多148比特，[29:27]无意义
   UNION结构:  GBBP_MOD_BIT4_RPT_UNION */
#define GBBP_MOD_BIT4_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53B0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  GSM TX IQ Mismatch相位校正因子，有符号数。
 bit[15:10]  保留
 bit[9:0]    GSM TX IQ Mismatch幅值校正因子，有符号数。
   UNION结构:  GBBP_TX_IQ_MISMATCH_COMP_UNION */
#define GBBP_TX_IQ_MISMATCH_COMP_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x58BC)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM TX IQ Mismatch Q路直流偏置补偿值，有符号数。注：减法处理。
 bit[15:12]  保留
 bit[11:0]   GSM TX IQ Mismatch I路直流偏置补偿值，有符号数。注：减法处理。
   UNION结构:  GBBP_TX_IQ_DC_OFFSET_COMP_UNION */
#define GBBP_TX_IQ_DC_OFFSET_COMP_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x58C0)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  数字爬坡时，下坡结束后的apc_ramp默认值。
             默认值为0。
             调试用。
             
 bit[15:9]   保留
 bit[8]      8psk数字爬坡使能信号。
             1表示8psk使用数字爬坡；0表示8psk不使用数字爬坡。
             默认值为1。
             
 bit[7:1]    保留
 bit[0]      gmsk数字爬坡使能信号。
             1表示gmsk使用数字爬坡；0表示gmsk不使用数字爬坡。
             
   UNION结构:  GBBP_TX_DIG_RMAP_MODE_SEL_UNION */
#define GBBP_TX_DIG_RMAP_MODE_SEL_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x58C4)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25:16]  上行使用的gsp_pa_target值上报
 bit[15:1]   保留
 bit[0]      GAPC爬坡系数配置RAM乒乓访问使能，1表示允许乒乓访问，0表示固定访问帧0系数空间；当该信号为1时，逻辑内部在TDMA帧头自动切换乒乓标志
   UNION结构:  GBBP_CPU_APC_SWITCH_EN_UNION */
#define GBBP_CPU_APC_SWITCH_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x53C0)

/* 寄存器说明：
 bit[31:28]  16组GTC模块的测试引脚选择信号
 bit[27:24]  16组MOD模块的测试引脚选择信号
 bit[23:20]  16组COD模块的测试引脚选择信号
 bit[19:16]  16组DEC模块的测试引脚选择信号
 bit[15:12]  16组VTB_DEM模块的测试选择信号引脚
 bit[11:8]   16组SRCH模块的测试引脚选择信号
 bit[7:4]    16组MAU模块的测试引脚选择信号
 bit[3:0]    16组AGC模块的测试引脚选择信号
   UNION结构:  GBBP_TEST_PIN_SEL_LOW_UNION */
#define GBBP_TEST_PIN_SEL_LOW_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5700)

/* 寄存器说明：
 bit[31:16]  用于TOA计算的13条径能量中，相邻5个能量累加，产生9个累加值。此上报为当前时隙最大累加值。
 bit[15:12]  保留
 bit[11:8]   16组APC模块的测试引脚选择信号
 bit[7:4]    16组PREPROCESS模块的测试引脚选择信号
 bit[3:0]    16组PREFILTER模块的测试引脚选择信号
   UNION结构:  GBBP_TEST_PIN_SEL_HIGH_UNION */
#define GBBP_TEST_PIN_SEL_HIGH_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5704)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:5]    0表示可以选择DAGC输出数据采样的相关控制信号
             1表示可以选择AGC输入数据采样的相关控制信号
             2表示可以选择DAGC输出和解调后软值数据采样的相关控制信号
             3表示可以选择DAGC输出和AGC输入数据采样的相关控制信号
             4表示可以观察解调，译码启动信号和中断信号
             
 bit[4:0]    0：选择AGC模块的测试引脚
             1：选择乘累加模块的测试引脚
             2：选择搜索模块的测试引脚
             3：选择解调模块的测试引脚
             4：选择译码模块的测试引脚
             5：选择编码模块的测试引脚
             6：选择调制模块的测试引脚
             7：选择GTC模块的测试引脚
             8：选择A5 DECIPH模块的测试引脚
             9：选择PREFILTER模块的测试引脚
             10：选择PREPROCESS模块的测试引脚
             11：选择APC模块的测试引脚
             13：选择GRIF模块的测试引脚
             14：选择A5 CIPH模块的测试引脚
             
   UNION结构:  GBBP_TEST_MODULE_SEL_UNION */
#define GBBP_TEST_MODULE_SEL_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x5710)

/* 寄存器说明：
 bit[31:28]  4'd0: gsp_agc_fast_start信号对应的gtc_tdma_qb采样值
             4'd1: gsp_agc_slow_start信号对应的gtc_tdma_qb采样值
             4'd2: gsp_srch_start信号对应的gtc_tdma_qb采样值
             4'd3: gsp_demod_start信号对应的gtc_tdma_qb采样值
             4'd4: gsp_rx_start信号对应的gtc_tdma_qb采样值
             4'd5: gsp_rx_stop信号对应的gtc_tdma_qb采样值
             4'd6: gsp_dec_start信号对应的gtc_tdma_qb采样值
             4'd7: gsp_ul_cod_start信号对应的gtc_tdma_qb采样值
             4'd8: gsp_ul_map_start信号对应的gtc_tdma_qb采样值
             4'd9: gsp_mod_start信号对应的gtc_tdma_qb采样值
             4'd10: gsp_mod_stop信号对应的gtc_tdma_qb采样值
             4'd11: gsp_pa_start信号对应的gtc_tdma_qb采样值
             4'd12: gsp_pa_stop信号对应的gtc_tdma_qb采样值
             4'd13: gsp_pa_single_start信号对应的gtc_tdma_qb采样值
             4'd14: gsp_pa_change信号对应的gtc_tdma_qb采样值
             测试用
 bit[27:13]  保留
 bit[12:0]   对应GTC解析出的各个启动信号所在tdma_qb值上报。
   UNION结构:  GBBP_GSP_START_TDMA_QB_RPT_UNION */
#define GBBP_GSP_START_TDMA_QB_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5714)

/* 寄存器说明：
 bit[31]     TOA Alpha滤波门限使能信号。1表示根据门限判决是否使用Alpha功能。
 bit[30:16]  预留的冗余寄存器。
 bit[15:0]   TOA Alpha滤波门限。默认11'd796，与径能量累加值右移6bit的结果进行比较。
   UNION结构:  GBBP_DSP_DEDICATE_CTRL_REG_UNION */
#define GBBP_DSP_DEDICATE_CTRL_REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5720)

/* 寄存器说明：
   详      述：PHY专用寄存器8
   UNION结构 ：无 */
#define GBBP_DSP_DEDICATE_REG8_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x574C)

/* 寄存器说明：
   详      述：版本寄存器。
   UNION结构 ：无 */
#define GBBP_GBBP_VERSION_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x5760)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      罗分trigger信号，用于平台问题定位使用。
   UNION结构:  GBBP_ERR_TRIG_UNION */
#define GBBP_ERR_TRIG_ADDR                            (SOC_BBP_GSM_BASE_ADDR + 0x5764)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      V2R1版本，该bit必须为1，测试用
   UNION结构:  GBBP_GBBP_EDGE_VERSION_UNION */
#define GBBP_GBBP_EDGE_VERSION_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5768)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第五近的一个BURST解调前粗测C值上报，测试用
   UNION结构:  GBBP_GROSS_CARRIER_ENERGY5_UNION */
#define GBBP_GROSS_CARRIER_ENERGY5_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x529C)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第五近的一个BURST解调前粗测I值上报，测试用
   UNION结构:  GBBP_GROSS_INTERFERE_ENERGY5_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY5_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5300)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第六近的一个BURST解调前粗测C值上报，测试用
   UNION结构:  GBBP_GROSS_CARRIER_ENERGY6_UNION */
#define GBBP_GROSS_CARRIER_ENERGY6_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5304)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:0]   第六近的一个BURST解调前粗测I值上报，测试用
   UNION结构:  GBBP_GROSS_INTERFERE_ENERGY6_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY6_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5308)

/* 寄存器说明：
 bit[31]     第五近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。
 bit[30:27]  保留
 bit[26:24]  第五近一个时隙AAGC档位上报。
 bit[23:20]  保留
 bit[19:8]   第五近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。
 bit[7:3]    保留
 bit[2:0]    第五近一个时隙AGC期望控制增益。
   UNION结构:  GBBP_AAGC_GAIN5_CPU_UNION */
#define GBBP_AAGC_GAIN5_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5290)

/* 寄存器说明：
 bit[31]     最远一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。
 bit[30:27]  保留
 bit[26:24]  最远一个时隙AAGC档位上报。
 bit[23:20]  保留
 bit[19:8]   最远一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。
 bit[7:3]    保留
 bit[2:0]    最远一个时隙AGC期望控制增益。
   UNION结构:  GBBP_AAGC_GAIN6_CPU_UNION */
#define GBBP_AAGC_GAIN6_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5294)

/* 寄存器说明：
   详      述：CPU读取GRIF FIFO数据，具体数据格式请参考采样数据表。
   UNION结构 ：无 */
#define GBBP_CPU_GDUMP_FIFO_RD_ADDR_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0xF000)

/* 寄存器说明：
 bit[31]     采数模块总是能，并控制时钟门控，无论哪种模式采数，首先要配置此信号有效，高电平表示该功能打开。
 bit[30:24]  保留
 bit[23:16]  G上行测试计数器
 bit[15:9]   保留
 bit[8]      采数模块配置类型选择。
             0：选择使用GTC配置接口
             1：选择使用CPU配置接口
             默认配置为0。
 bit[7]      保留
 bit[6:4]    采样数据源选择。
             0：选择采用信道滤波器输入数据；
             1：选择采用信道滤波器输出数据；
             2：选择采用AGC输入数据；
             3：选择采用AGC去直流后且用于测量的数据；
             4：选择采用AGC去直流后且用于解调与搜索的数据；
             5：选择采用DAGC输出数据，仅用于采样待解调数据；
             6：上行发送调制数据；
             7：
 bit[3]      保留
 bit[2:0]    FIFO水线深度选择。
             0：表示水线深度2；
             1：表示水线深度4；
             2：表示水线深度8；
             3：表示水线深度16；
             4：表示水线深度32；
             5：表示水线深度64；
             6：表示水线深度128；
             7：
             SOC水线深度支持1~16
   UNION结构:  GBBP_CPU_GDUMP_GEN_CONFIG_UNION */
#define GBBP_CPU_GDUMP_GEN_CONFIG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF004)

/* 寄存器说明：
   详      述：CPU配置采样数据个数，全0表示采样数据个数无限长。
   UNION结构 ：无 */
#define GBBP_CPU_GDUMP_LEN_CONFIG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF008)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   可配启动时刻采数模式下，采数起始位置，35'h7ffffffff表示立即启动。该配置为35bit中[12:0]，默认值为立即启动模式。
   UNION结构:  GBBP_CPU_GDUMP_SAM_LOW_TIMING_UNION */
#define GBBP_CPU_GDUMP_SAM_LOW_TIMING_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0xF00C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  可配启动时刻采数模式下，采数起始位置，35'h7ffffffff表示立即启动。该配置为35bit中[34:24]，默认值为立即启动模式。
 bit[15:11]  保留
 bit[10:0]   可配启动时刻采数模式下，采数起始位置，35'h7ffffffff表示立即启动。该配置为35bit中[23:13]，默认值为立即启动模式。
   UNION结构:  GBBP_CPU_GDUMP_SAM_HIGH_TIMING_UNION */
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_ADDR           (SOC_BBP_GSM_BASE_ADDR + 0xF010)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     CPU配置异步FIFO清零信号。
 bit[15:9]   保留
 bit[8]      CPU配置采样数据停止信号，当采样数据个数无限长时，用该信号停止采数。
 bit[7:1]    保留
 bit[0]      CPU配置采样数据启动信号。
   UNION结构:  GBBP_CPU_GDUMP_RECV_CONFIG_UNION */
#define GBBP_CPU_GDUMP_RECV_CONFIG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF014)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数1,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数0,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_1REG_UNION */
#define GBBP_ADDR_G_CH_PARA_1REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF294)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数3,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数2,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_2REG_UNION */
#define GBBP_ADDR_G_CH_PARA_2REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF298)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数5,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数4,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_3REG_UNION */
#define GBBP_ADDR_G_CH_PARA_3REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF29C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数7,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数6,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_4REG_UNION */
#define GBBP_ADDR_G_CH_PARA_4REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2A0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数9,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数8,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_5REG_UNION */
#define GBBP_ADDR_G_CH_PARA_5REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2A4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数11,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数10,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_6REG_UNION */
#define GBBP_ADDR_G_CH_PARA_6REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2A8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数13,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数12,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_7REG_UNION */
#define GBBP_ADDR_G_CH_PARA_7REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2AC)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数15,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数14,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_8REG_UNION */
#define GBBP_ADDR_G_CH_PARA_8REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2B0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数17,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数16,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_9REG_UNION */
#define GBBP_ADDR_G_CH_PARA_9REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2B8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数19,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数18,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_10REG_UNION */
#define GBBP_ADDR_G_CH_PARA_10REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2C4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数21,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数20,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_11REG_UNION */
#define GBBP_ADDR_G_CH_PARA_11REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2C8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数23,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数22,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_12REG_UNION */
#define GBBP_ADDR_G_CH_PARA_12REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2CC)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数25,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数24,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_13REG_UNION */
#define GBBP_ADDR_G_CH_PARA_13REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2D0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数27,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数26,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_14REG_UNION */
#define GBBP_ADDR_G_CH_PARA_14REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2D4)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数29,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数28,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_15REG_UNION */
#define GBBP_ADDR_G_CH_PARA_15REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2D8)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行信道滤波配置系数31,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数30,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_16REG_UNION */
#define GBBP_ADDR_G_CH_PARA_16REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2DC)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   GSM下行信道滤波配置系数32,12bit有符号数
   UNION结构:  GBBP_ADDR_G_CH_PARA_17REG_UNION */
#define GBBP_ADDR_G_CH_PARA_17REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2E0)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数1,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数0,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_1REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_1REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF31C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数3,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数2,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_2REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_2REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF320)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数5,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数4,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_3REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_3REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF324)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数7,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数6,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_4REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_4REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF328)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数9,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数8,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_5REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_5REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF32C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数11,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数10,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_6REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_6REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF330)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数13,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数12,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_7REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_7REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF334)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  GSM下行32阶信道滤波配置系数15,12bit有符号数
 bit[15:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数14,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_8REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_8REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF338)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   GSM下行32阶信道滤波配置系数16,12bit有符号数
   UNION结构:  GBBP_ADDR_G_32CH_PARA_9REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_9REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF33C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:28]  ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
 bit[27:26]  保留
 bit[25:24]  ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
 bit[23:22]  保留
 bit[21:20]  ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
 bit[19:18]  保留
 bit[17:16]  ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
 bit[15:14]  保留
 bit[13:12]  ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
 bit[11:10]  保留
 bit[9:8]    ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
 bit[7:6]    保留
 bit[5:4]    ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
 bit[3:2]    保留
 bit[1:0]    ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。
   UNION结构:  GBBP_CLIP_MODE_SEL_UNION */
#define GBBP_CLIP_MODE_SEL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0xF2E8)

/* 寄存器说明：
 bit[31:16]  1w2r双口RAM延时控制
 bit[15:0]   1w2rw双口RAM延时控制
   UNION结构:  GBBP_ADDR_MEM_CTRL1_UNION */
#define GBBP_ADDR_MEM_CTRL1_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0xF018)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  ROM延时控制
 bit[15:0]   单口RAM延时控制
   UNION结构:  GBBP_ADDR_MEM_CTRL2_UNION */
#define GBBP_ADDR_MEM_CTRL2_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0xF01C)



/***======================================================================***
                     (2/9) register_define_sdr_gdrx_guage
 ***======================================================================***/
/* 寄存器说明：
 bit[31]     GDRX停止脉冲，写1停止。自清零，写0无意义。
 bit[30]     时钟校准使能，写1开启。自清零，写0无意义。
 bit[29:17]  保留
 bit[16:0]   时钟校准32KHz时钟个数
   UNION结构:  GBBP_GDRX_GAUGE_EN_CNF_UNION */
#define GBBP_GDRX_GAUGE_EN_CNF_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x7000)

/* 寄存器说明：
 bit[31]     睡眠状态查询。1，正在睡眠。
 bit[30]     测量状态查询。1，正在测量。
 bit[29:28]  保留
 bit[27:0]   时钟校准结果，测量周期内104M钟个数
   UNION结构:  GBBP_GAUGE_RESULT_RPT_UNION */
#define GBBP_GAUGE_RESULT_RPT_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x7004)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   IMI时钟域任何中断上报时GTC的TDMA QB计数，测试用
   UNION结构:  GBBP_IMI_INT_TDMA_QB_UNION */
#define GBBP_IMI_INT_TDMA_QB_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x7008)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   32K时钟中断上报时GTC的TDMA QB计数，测试用
   UNION结构:  GBBP_SLEEP_INT_TDMA_QB_UNION */
#define GBBP_SLEEP_INT_TDMA_QB_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x700C)



/***======================================================================***
                     (3/9) register_define_g_fe_ctrl
 ***======================================================================***/
/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   当RFCMOS使用晶体方案时，软件gdsp配置的校准后温度补偿NV项值。
             该NV项值是开机时，晶体温度对应补偿曲线的补偿值。
   UNION结构:  GBBP_G_AFC_THERM_COM_NV_UNION */
#define GBBP_G_AFC_THERM_COM_NV_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x8600)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:16]  使用晶体AFC方案时输出给RF的AFC控制字值。
 bit[15:12]  保留
 bit[11:4]   选择晶体方案时，配置给RF的TCXO SSI地址bit。
 bit[3:1]    保留
 bit[0:0]    保留
   UNION结构:  GBBP_G_RF_SSI_AFC_UNION */
#define GBBP_G_RF_SSI_AFC_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x8604)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:28]  使用CPU方式将一个RF-SSI配置是否发送至BBP COMM模块的状态信号，测试用。
             0：表示结束，1表示未结束。
 bit[27:25]  保留
 bit[24:24]  GDSP使用CPU方式配置一个RF-SSI的启动信号。
             逻辑自清零。
 bit[23:16]  GDSP使用CPU方式配置一个RF-SSI的寄存器地址。
 bit[15:0]   GDSP使用CPU方式配置一个RF-SSI的寄存器对应的数据。
   UNION结构:  GBBP_G_RF_SSI_WRONE_CFG_UNION */
#define GBBP_G_RF_SSI_WRONE_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x8608)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:16]  读 ssi允许使能信号
 bit[15:13]  保留
 bit[12:12]  写一个rf-ssi允许使能信号
 bit[11:9]   保留
 bit[8:8]    g-afc ssi允许使能信号
 bit[7:5]    保留
 bit[4:4]    g-rf-ram ssi允许使能信号
 bit[3:1]    保留
 bit[0:0]    g-gagc ssi允许使能信号
   UNION结构:  GBBP_G_RF_SSI_REQ_EN_CFG_UNION */
#define GBBP_G_RF_SSI_REQ_EN_CFG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x860C)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:12]  写ssi-ram完成指示信号。
             1：表示正在回读；
             0：表示完成回读操作。
 bit[11:9]   保留
 bit[8:8]    回读完成指示信号。
             1：表示正在回读；
             0：表示完成回读操作。
 bit[7:7]    保留
 bit[6:4]    RF-SSI回读寄存器个数。
             配置值为0~7，对应的回读寄存器个数为1~8。
             （注：配置为0表示回读一个寄存器）
 bit[3:1]    保留
 bit[0:0]    启动RF-SSI寄存器回读。
             逻辑自清零信号。
   UNION结构:  GBBP_G_RF_SSI_RD_CFG_UNION */
#define GBBP_G_RF_SSI_RD_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x8610)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据0。
   UNION结构:  GBBP_G_RF_SSI_RD_0DATA_UNION */
#define GBBP_G_RF_SSI_RD_0DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8614)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据1。
   UNION结构:  GBBP_G_RF_SSI_RD_1DATA_UNION */
#define GBBP_G_RF_SSI_RD_1DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8618)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据2。
   UNION结构:  GBBP_G_RF_SSI_RD_2DATA_UNION */
#define GBBP_G_RF_SSI_RD_2DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x861C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据3。
   UNION结构:  GBBP_G_RF_SSI_RD_3DATA_UNION */
#define GBBP_G_RF_SSI_RD_3DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8620)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据4。
   UNION结构:  GBBP_G_RF_SSI_RD_4DATA_UNION */
#define GBBP_G_RF_SSI_RD_4DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8624)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据5。
   UNION结构:  GBBP_G_RF_SSI_RD_5DATA_UNION */
#define GBBP_G_RF_SSI_RD_5DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8628)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据6。
   UNION结构:  GBBP_G_RF_SSI_RD_6DATA_UNION */
#define GBBP_G_RF_SSI_RD_6DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x862C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   SSI回读配置数据7。
   UNION结构:  GBBP_G_RF_SSI_RD_7DATA_UNION */
#define GBBP_G_RF_SSI_RD_7DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8630)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      GTC方式MIPI客户端工作使能开关，1表示通道打开，0表示通道关闭。
 bit[3:1]    保留
 bit[0]      CPU方式MIPI客户端工作使能开关，1表示通道打开，0表示通道关闭。
   UNION结构:  GBBP_G_MIPI_REQ_EN_CFG_UNION */
#define GBBP_G_MIPI_REQ_EN_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8634)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:16]  软件方式配置MIPI请求时的触发脉冲信号。
 bit[15]     保留
 bit[14:8]   软件方式配置MIPI请求时，配置寄存器的个数。配置范围：1～127。
 bit[7]      保留
 bit[6:0]    软件方式配置MIPI请求时，配置寄存器组的首地址。
   UNION结构:  GBBP_G_MIPI_CMD_CFG_UNION */
#define GBBP_G_MIPI_CMD_CFG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x8638)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     软件配置SSI状态机异常情况的复位脉冲信号。
 bit[15:1]   保留
 bit[0]      软件配置MIPI状态机异常情况的复位脉冲信号。
   UNION结构:  GBBP_G_RF_SSI_MIPI_CLR_REG_UNION */
#define GBBP_G_RF_SSI_MIPI_CLR_REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x863C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      ABB上下行数据自然码、补码模式选择。
             1：表示自然码，0：表示补码，GSM专用。
   UNION结构:  GBBP_G_ABB_CFG_SEL_UNION */
#define GBBP_G_ABB_CFG_SEL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x8644)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0:0]    主模测G的方式选择。
             0：背景搜；
             1：非背景搜。
   UNION结构:  GBBP_G_MASTER_MEA_G_EN_UNION */
#define GBBP_G_MASTER_MEA_G_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8658)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:1]    环回模式使能。
 bit[0:0]    环回模式下，上行通道使能开关。
   UNION结构:  GBBP_G_ABB_TRX_LOOP_EN_UNION */
#define GBBP_G_ABB_TRX_LOOP_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x865C)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define GBBP_G_DBG_REG0_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x8660)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define GBBP_G_DBG_REG1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x8664)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  AuxDAC打开控制字配置，该控制字在gtc_gapc_en线控信号上升沿发送至AuxDAC。
 bit[15:11]  保留
 bit[10:0]   AuxDAC打开控制字配置，该控制字在gtc_gapc_en线控下降沿发送至AuxDAC。
   UNION结构:  GBBP_G_AUXDAC_EN_CFG_UNION */
#define GBBP_G_AUXDAC_EN_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x8690)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:2]    FIFO空信号上报
 bit[1:1]    FIFO满信号上报
 bit[0:0]    fifo复位信号，在FIFO状态异常时，配置为1，进行清零
   UNION结构:  GBBP_DATA_FIFO_RST_UNION */
#define GBBP_DATA_FIFO_RST_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x8694)



/***======================================================================***
                     (4/9) register_define_g_fe_ctrl_mem
 ***======================================================================***/
/* 寄存器说明：g本频或异频H的rfic-ssi RAM
 bit[31:24]  保留
 bit[23:16]  g本频或强配的rfic-ssi RAM。
             数据：
             [23:16]：rfic的寄存器地址；
 bit[15:0]   g本频或强配的rfic-ssi RAM。
             数据
             [15:0]：rfic的寄存器数据。
   UNION结构:  GBBP_G_RFIC_SSI_RAM_UNION */
#define GBBP_G_RFIC_SSI_RAM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x8200)
#define GBBP_G_RFIC_SSI_RAM_MEMDEPTH  (192)

/* 寄存器说明：g本频或异频的mipi RAM
   详      述：g本频或异频的mipi RAM,支持128个指令。
   UNION结构 ：无 */
#define GBBP_G_MIPI_SSI_RAM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x8000)
#define GBBP_G_MIPI_SSI_RAM_MEMDEPTH  (128)



/***======================================================================***
                     (5/9) register_define_gtc_mem
 ***======================================================================***/
/* 寄存器说明：有效地址范围0x0000～0x07FF
 bit[31:16]  保留
 bit[15:0]   GTC指令配置RAM，每个32bit中只有低16bit有效。
   UNION结构:  GBBP_GTC_CFG_RAM_UNION */
#define GBBP_GTC_CFG_RAM_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x0)
#define GBBP_GTC_CFG_RAM_MEMDEPTH  (512)



/***======================================================================***
                     (6/9) register_define_g_addr_2x_mem
 ***======================================================================***/
/* 寄存器说明：有效地址范围0x0000～0x039F
   详      述：译码上报RAM大小为232X32bit
            译码上报ram,格式参见前面的说明
   UNION结构 ：无 */
#define GBBP_DEC_RPT_RAM_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x2000)
#define GBBP_DEC_RPT_RAM_MEMDEPTH  (232)

/* 寄存器说明：有效地址范围0x0800～0x0843
   详      述：软件规避模式下响应解调中断后读取训练序列数据上报RAM数据.
            训练序列数据上报RAM的写数据，该RAM用于存储DAGC之后，解调之前的训练序列软值。其中先后顺序为1+26+7,即是TSC前一个symbol和后7个symbol 采样值经DAGC后输出的IQ数据。每行存放2个符号，格式为{I1,Q1,I0,Q0}，顺序左高右低。
   UNION结构 ：无 */
#define GBBP_TSC_RAM_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x2800)
#define GBBP_TSC_RAM_MEMDEPTH  (16)

/* 寄存器说明：有效地址范围0x0500～0x057F
   详      述：GAPC爬坡系数配置RAM，存储结构见前面的图示
   UNION结构 ：无 */
#define GBBP_CPU_GAPC_CONFIG_RAM_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x2500)
#define GBBP_CPU_GAPC_CONFIG_RAM_MEMDEPTH  (32)

/* 寄存器说明：便于GPHY直接生成代码，单独列出此寄存器
   详      述：NB译码信息上报
   UNION结构 ：无 */
#define GBBP_NB_DEC_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x2004)
#define GBBP_NB_DEC_RPT_MEMDEPTH  (1)

/* 寄存器说明：便于GPHY直接生成代码，单独列出此寄存器
   详      述：SB译码信息上报
   UNION结构 ：无 */
#define GBBP_SB_DEC_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x2398)
#define GBBP_SB_DEC_RPT_MEMDEPTH  (1)



/***======================================================================***
                     (7/9) register_define_g_addr_3x_mem
 ***======================================================================***/
/* 寄存器说明：有效地址范围0x0000～0x027F
   详      述：CPU下发的待编码数据，可以参见待编码数据格式说明
   UNION结构 ：无 */
#define GBBP_UL_CODE_CFG_RAM_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x3000)
#define GBBP_UL_CODE_CFG_RAM_MEMDEPTH  (160)

/* 寄存器说明：有效地址范围0x0300～0x031F
   详      述：CPU接口配置的去3、5次谐波模块参数RAM。接口RAM中预留4组参数，每组参数占用2个地址，分别为3次谐波消除的B参数和5次谐波消除的C参数，可参见数据格式说明。软件看到的访问地址为8个地址，BBP内部控制在帧头乒乓处理。
   UNION结构 ：无 */
#define GBBP_CPU_HD35_CONFIG_RAM_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x3300)
#define GBBP_CPU_HD35_CONFIG_RAM_MEMDEPTH  (8)



/***======================================================================***
                     (8/9) register_define_g_addr_5x_mem
 ***======================================================================***/
/* 寄存器说明：有效地址范围0x0400～0x055B
   详      述：SB,NB解调软值与CPU接口的搬移ram，4个6bit解调软值，依次占用imi_rddata的5～0，13～8，21～16，29～24bit位；
   UNION结构 ：无 */
#define GBBP_CARRY_RAM_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x5400)
#define GBBP_CARRY_RAM_MEMDEPTH  (88)

/* 寄存器说明：有效地址范围0x0600～0x0638
 bit[31:30]  保留
 bit[29:0]   CPU下发的待调制数据，低30bit有效
   UNION结构:  GBBP_UL_MAP_CFG_RAM_UNION */
#define GBBP_UL_MAP_CFG_RAM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5600)
#define GBBP_UL_MAP_CFG_RAM_MEMDEPTH  (15)

/* 寄存器说明：有效地址范围0x08C8～0x09FF
   详      述：为了避免软件无法及时在每时隙的解调中断后读取解调软值，增加本上报RAM。
            从0x5400~0x555b地址中，选取USF bit对应的解调软值上报，每个NB 固定上报13个软值，每帧最多上报78个软值。
            每时隙的软值，依次选取0x5400~0x555b当中的0x00,0x10,0x20,0x30,0x34，0x44,0x54,0x64,0x94,0xa8,0xc0等13个地址的数据。与0x5400的区别在于，本RAM可以存储6个时隙的USF软值，而5400地址，仅能保存1个时隙的软值。
   UNION结构 ：无 */
#define GBBP_USF_VALUE_RPT_RAM_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x58C8)
#define GBBP_USF_VALUE_RPT_RAM_MEMDEPTH  (78)



/***======================================================================***
                     (9/9) register_define_g_addr_6x_mem
 ***======================================================================***/
/* 寄存器说明：直流偏执调整值粗调值存储RAM，到0x00FF结束
 bit[31:30]  保留
 bit[29:16]  直流偏执调整值粗调值存储RAM访问地址，一个地址表示28bit，其中低16bit中的14bit表示I路，高16bit中的14bit为Q路。配置的14bit为有符号数。
 bit[15:14]  保留
 bit[13:0]   直流偏执调整值粗调值存储RAM访问地址，一个地址表示28bit，其中低16bit中的14bit表示I路，高16bit中的14bit为Q路。配置的14bit为有符号数。
   UNION结构:  GBBP_DC_OFFSET_RAM_UNION */
#define GBBP_DC_OFFSET_RAM_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x6000)
#define GBBP_DC_OFFSET_RAM_MEMDEPTH  (64)

/* 寄存器说明：前向通道增益调整值存储RAM，到0x04FF结束
 bit[31:11]  保留
 bit[10:0]   前向通道增益调整值存储RAM。CHANNEL_GAIN参考配置参见表19，此表在实际使用时，需要进行实测后得出。
   UNION结构:  GBBP_CHANNEL_GAIN_RAM_UNION */
#define GBBP_CHANNEL_GAIN_RAM_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x6400)
#define GBBP_CHANNEL_GAIN_RAM_MEMDEPTH  (64)





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
                     (1/9) register_define_gbbp_addr
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_CPU_SOFT_AFC_VALUE_UNION
 结构说明  : CPU_SOFT_AFC_VALUE 寄存器结构定义。地址偏移量:0x1000，初值:0x00002000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_soft_afc_value_reg;
    struct
    {
        unsigned int  cpu_soft_afc_value  : 14; /* bit[0-13] : 物理层软件计算AFC值，在cpu_soft_afc_renew有效时，将此值输出给VCO。 */
        unsigned int  reserved            : 17; /* bit[14-30]: 保留 */
        unsigned int  cpu_soft_afc_en_imi : 1;  /* bit[31]   : 物理层软件计算AFC值使能信号，电平信号，高有效。在此信号为高期间，GBBP不在进行AFC锁定判断，输出给VCO的值由cpu_soft_afc_value[13:0]提供。 */
    } reg;
} GBBP_CPU_SOFT_AFC_VALUE_UNION;
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_value_START   (0)
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_value_END     (13)
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_en_imi_START  (31)
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_en_imi_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_SOFT_VALUE_RENEW_UNION
 结构说明  : CPU_SOFT_VALUE_RENEW 寄存器结构定义。地址偏移量:0x1004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_soft_value_renew_reg;
    struct
    {
        unsigned int  cpu_soft_afc_renew_imi : 1;  /* bit[0]   : 物理层软件启动更新AFC值，脉冲信号。此信号在cpu_soft_afc_en_imi为高时才有效，写1逻辑自清零。 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_SOFT_VALUE_RENEW_UNION;
#define GBBP_CPU_SOFT_VALUE_RENEW_cpu_soft_afc_renew_imi_START  (0)
#define GBBP_CPU_SOFT_VALUE_RENEW_cpu_soft_afc_renew_imi_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_CI_THRES_CFG_UNION
 结构说明  : CPU_CI_THRES_CFG 寄存器结构定义。地址偏移量:0x1008，初值:0x00030003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ci_thres_cfg_reg;
    struct
    {
        unsigned int  cpu_gmsk_ci_thres : 3;  /* bit[0-2]  : GMSK调制方式下，CI判决门限选择信号，用于筛选nb-afc的输出。小于该门限，afc_valui_i和afc_value_q都输出0，否则输出真实值。
                                                             cpu_psk_ci_thres[2:0]=0 C>I
                                                             cpu_psk_ci_thres[2:0]=1 C>4I
                                                             cpu_psk_ci_thres[2:0]=2 C>8I
                                                             cpu_psk_ci_thres[2:0]=3 C>16I
                                                             cpu_psk_ci_thres[2:0]=4 C>32I
                                                             cpu_psk_ci_thres[2:0]=5 C>64I
                                                             cpu_psk_ci_thres[2:0]=6 C>128I
                                                             cpu_psk_ci_thres[2:0]=7 不判决，直接输出。
                                                             默认值是3。 */
        unsigned int  reserved_0        : 13; /* bit[3-15] : 保留 */
        unsigned int  cpu_psk_ci_thres  : 3;  /* bit[16-18]: 8PSK调制方式下，CI判决门限选择信号，用于筛选nb-afc的输出。小于该门限，afc_valui_i和afc_value_q都输出0，否则输出真实值。
                                                             cpu_gmsk_ci_thres[2:0]=0 C>I
                                                             cpu_gmsk_ci_thres[2:0]=1 C>4I
                                                             cpu_gmsk_ci_thres[2:0]=2 C>8I
                                                             cpu_gmsk_ci_thres[2:0]=3 C>16I
                                                             cpu_gmsk_ci_thres[2:0]=4 C>32I
                                                             cpu_gmsk_ci_thres[2:0]=5 C>64I
                                                             cpu_gmsk_ci_thres[2:0]=6 C>128I
                                                             cpu_gmsk_ci_thres[2:0]=7 不判决，直接输出。
                                                             默认值是3。 */
        unsigned int  reserved_1        : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_CPU_CI_THRES_CFG_UNION;
#define GBBP_CPU_CI_THRES_CFG_cpu_gmsk_ci_thres_START  (0)
#define GBBP_CPU_CI_THRES_CFG_cpu_gmsk_ci_thres_END    (2)
#define GBBP_CPU_CI_THRES_CFG_cpu_psk_ci_thres_START   (16)
#define GBBP_CPU_CI_THRES_CFG_cpu_psk_ci_thres_END     (18)


/*****************************************************************************
 结构名    : GBBP_CPU_NB_AFC_NUM_UNION
 结构说明  : CPU_NB_AFC_NUM 寄存器结构定义。地址偏移量:0x100C，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_nb_afc_num_reg;
    struct
    {
        unsigned int  cpu_nb_afc_num : 3;  /* bit[0-2] : 一阶环用于计算NB-AFC的NB个数选择信号：
                                                         0：表示选择1个NB来计算；
                                                         1：表示选择2个NB来计算；
                                                         2：表示选择4个NB来计算；
                                                         3：表示选择8个NB来计算；
                                                         4：表示选择16个NB来计算；
                                                         5：表示选择32个NB来计算；
                                                         6：表示选择64个NB来计算。
                                                         非DRX期间推荐配置2，DRX期间推荐配置为0。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留 */
    } reg;
} GBBP_CPU_NB_AFC_NUM_UNION;
#define GBBP_CPU_NB_AFC_NUM_cpu_nb_afc_num_START  (0)
#define GBBP_CPU_NB_AFC_NUM_cpu_nb_afc_num_END    (2)


/*****************************************************************************
 结构名    : GBBP_CPU_AFC_CFG_UNION
 结构说明  : CPU_AFC_CFG 寄存器结构定义。地址偏移量:0x1010，初值:0x00002000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_afc_cfg_reg;
    struct
    {
        unsigned int  cpu_afc_init        : 14; /* bit[0-13] : G AFC初始值。
                                                               当RFCMOS使用晶体方案时，配置该值为14'h1fff（详见V3R2晶体系统方案）；其他方案时，使用原来的配置值。 */
        unsigned int  reserved_0          : 1;  /* bit[14]   : 保留 */
        unsigned int  cpu_afc_init_en_imi : 1;  /* bit[15]   : AFC初始值写入使能，CPU写1，逻辑自清零。 */
        unsigned int  reserved_1          : 15; /* bit[16-30]: 保留 */
        unsigned int  cpu_fb_afc_clr_imi  : 1;  /* bit[31]   : FB-AFC清零信号，写1生效，逻辑自清零 */
    } reg;
} GBBP_CPU_AFC_CFG_UNION;
#define GBBP_CPU_AFC_CFG_cpu_afc_init_START         (0)
#define GBBP_CPU_AFC_CFG_cpu_afc_init_END           (13)
#define GBBP_CPU_AFC_CFG_cpu_afc_init_en_imi_START  (15)
#define GBBP_CPU_AFC_CFG_cpu_afc_init_en_imi_END    (15)
#define GBBP_CPU_AFC_CFG_cpu_fb_afc_clr_imi_START   (31)
#define GBBP_CPU_AFC_CFG_cpu_fb_afc_clr_imi_END     (31)


/*****************************************************************************
 结构名    : GBBP_AFC_VALUE_I_CPU_UNION
 结构说明  : AFC_VALUE_I_CPU 寄存器结构定义。地址偏移量:0x1014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_value_i_cpu_reg;
    struct
    {
        unsigned int  afc_value_i : 19; /* bit[0-18] : 上报的afc实部相关累加值，直接由乘累加模块输出，测试用。 */
        unsigned int  reserved    : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_AFC_VALUE_I_CPU_UNION;
#define GBBP_AFC_VALUE_I_CPU_afc_value_i_START  (0)
#define GBBP_AFC_VALUE_I_CPU_afc_value_i_END    (18)


/*****************************************************************************
 结构名    : GBBP_AFC_VALUE_Q_CPU_UNION
 结构说明  : AFC_VALUE_Q_CPU 寄存器结构定义。地址偏移量:0x1018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_value_q_cpu_reg;
    struct
    {
        unsigned int  afc_value_q : 19; /* bit[0-18] : 上报的afc虚部相关累加值，直接由乘累加模块输出，测试用。 */
        unsigned int  reserved    : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_AFC_VALUE_Q_CPU_UNION;
#define GBBP_AFC_VALUE_Q_CPU_afc_value_q_START  (0)
#define GBBP_AFC_VALUE_Q_CPU_afc_value_q_END    (18)


/*****************************************************************************
 结构名    : GBBP_CPU_AFC_PWM_WIDTH_SEL_UNION
 结构说明  : CPU_AFC_PWM_WIDTH_SEL 寄存器结构定义。地址偏移量:0x101C，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_afc_pwm_width_sel_reg;
    struct
    {
        unsigned int  cpu_afc_pwm_width_sel : 2;  /* bit[0-1] : 0表示使用10bit的PDM转换模块；
                                                                1表示使用12bit的PDM转换模块；
                                                                2表示使用14bit的PDM转换模块。 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} GBBP_CPU_AFC_PWM_WIDTH_SEL_UNION;
#define GBBP_CPU_AFC_PWM_WIDTH_SEL_cpu_afc_pwm_width_sel_START  (0)
#define GBBP_CPU_AFC_PWM_WIDTH_SEL_cpu_afc_pwm_width_sel_END    (1)


/*****************************************************************************
 结构名    : GBBP_CPU_NB_AFC_NUM_CLR_UNION
 结构说明  : CPU_NB_AFC_NUM_CLR 寄存器结构定义。地址偏移量:0x1020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_nb_afc_num_clr_reg;
    struct
    {
        unsigned int  cpu_nb_afc_num_clr_imi : 1;  /* bit[0]   : 表示重新开始统计NB-AFC的NB-BURST个数，cpu写1，逻辑自清零。
                                                                 此时不输出当前累计NB个数对应的NB-AFC滤波值。建议先改变cpu_nb_afc_num后配置此值为1。 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_NB_AFC_NUM_CLR_UNION;
#define GBBP_CPU_NB_AFC_NUM_CLR_cpu_nb_afc_num_clr_imi_START  (0)
#define GBBP_CPU_NB_AFC_NUM_CLR_cpu_nb_afc_num_clr_imi_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_FB_KP_KINT_UNION
 结构说明  : CPU_FB_KP_KINT 寄存器结构定义。地址偏移量:0x1024，初值:0x00160000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_fb_kp_kint_reg;
    struct
    {
        unsigned int  reserved_0       : 16; /* bit[0-15] : 保留 */
        unsigned int  cpu_afc_maxfbnum : 5;  /* bit[16-20]: 用于FB-AFC判决的总的FB个数，可配范围为：17~31
                                                            默认配置为：22 */
        unsigned int  reserved_1       : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_CPU_FB_KP_KINT_UNION;
#define GBBP_CPU_FB_KP_KINT_cpu_afc_maxfbnum_START  (16)
#define GBBP_CPU_FB_KP_KINT_cpu_afc_maxfbnum_END    (20)


/*****************************************************************************
 结构名    : GBBP_FB_TIMEBASE_RPT_UNION
 结构说明  : FB_TIMEBASE_RPT 寄存器结构定义。地址偏移量:0x1028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_timebase_rpt_reg;
    struct
    {
        unsigned int  fb_timebase_qb_rpt : 13; /* bit[0-12] : 滞后FB1215QB处timebase的QB计数，测试用。 */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: 保留 */
        unsigned int  fb_timebase_fn_rpt : 11; /* bit[16-26]: 滞后FB1215QB处timebase的FN模2048计数，计数范围：0~2047测试用。 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_FB_TIMEBASE_RPT_UNION;
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_qb_rpt_START  (0)
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_qb_rpt_END    (12)
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_fn_rpt_START  (16)
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_fn_rpt_END    (26)


/*****************************************************************************
 结构名    : GBBP_FB_FN_RPT_UNION
 结构说明  : FB_FN_RPT 寄存器结构定义。地址偏移量:0x102C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_fn_rpt_reg;
    struct
    {
        unsigned int  fb_fn_rpt3 : 6;  /* bit[0-5]  : FB所在帧位置T3计数器上报。 */
        unsigned int  reserved_0 : 2;  /* bit[6-7]  : 保留 */
        unsigned int  fb_fn_rpt2 : 5;  /* bit[8-12] : FB所在帧位置T2计数器上报。 */
        unsigned int  reserved_1 : 3;  /* bit[13-15]: 保留 */
        unsigned int  fb_fn_rpt1 : 11; /* bit[16-26]: FB所在帧位置T1计数器上报。 */
        unsigned int  reserved_2 : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_FB_FN_RPT_UNION;
#define GBBP_FB_FN_RPT_fb_fn_rpt3_START  (0)
#define GBBP_FB_FN_RPT_fb_fn_rpt3_END    (5)
#define GBBP_FB_FN_RPT_fb_fn_rpt2_START  (8)
#define GBBP_FB_FN_RPT_fb_fn_rpt2_END    (12)
#define GBBP_FB_FN_RPT_fb_fn_rpt1_START  (16)
#define GBBP_FB_FN_RPT_fb_fn_rpt1_END    (26)


/*****************************************************************************
 结构名    : GBBP_CPU_FB_TIMES_THRES_UNION
 结构说明  : CPU_FB_TIMES_THRES 寄存器结构定义。地址偏移量:0x1030，初值:0x03652011，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_fb_times_thres_reg;
    struct
    {
        unsigned int  cpu_fb_failed_thres : 2;  /* bit[0-1]  : FB同步失败次数门限。
                                                               2'd0：使用的门限值为1；
                                                               2'd1：使用的门限值为2；
                                                               2'd2：使用的门限值为3；
                                                               2'd3：使用的门限值为4。
                                                               缺省值为2'd1。 */
        unsigned int  reserved_0          : 2;  /* bit[2-3]  : 保留 */
        unsigned int  cpu_sb_failed_thres : 2;  /* bit[4-5]  : SB同步失败次数门限。
                                                               2'd0：使用的门限值为1；
                                                               2'd1：使用的门限值为2；
                                                               2'd2：使用的门限值为3；
                                                               其他：无效。
                                                               缺省值为2'd1。 */
        unsigned int  reserved_1          : 6;  /* bit[6-11] : 保留 */
        unsigned int  cpu_fb_peak_window  : 17; /* bit[12-28]: FB搜索窗的符号个数门限值。
                                                               缺省值为17'd13906（对应11帧+1时隙）。当搜索的时间长度大于该值时，FB搜索结束。
                                                               注：13906=11*1250+156 */
        unsigned int  reserved_2          : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_CPU_FB_TIMES_THRES_UNION;
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_failed_thres_START  (0)
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_failed_thres_END    (1)
#define GBBP_CPU_FB_TIMES_THRES_cpu_sb_failed_thres_START  (4)
#define GBBP_CPU_FB_TIMES_THRES_cpu_sb_failed_thres_END    (5)
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_peak_window_START   (12)
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_peak_window_END     (28)


/*****************************************************************************
 结构名    : GBBP_CPU_FB_ENERG_THRES_UNION
 结构说明  : CPU_FB_ENERG_THRES 寄存器结构定义。地址偏移量:0x1034，初值:0x00200000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_fb_energ_thres_reg;
    struct
    {
        unsigned int  reserved_0        : 12; /* bit[0-11] : 保留 */
        unsigned int  cpu_fb_peak_thres : 11; /* bit[12-22]: FB搜索成功的门限，当FB搜索得到的能量的最大值大于该门限时，才认为搜索成功，缺省值为512。 */
        unsigned int  reserved_1        : 9;  /* bit[23-31]: 保留 */
    } reg;
} GBBP_CPU_FB_ENERG_THRES_UNION;
#define GBBP_CPU_FB_ENERG_THRES_cpu_fb_peak_thres_START  (12)
#define GBBP_CPU_FB_ENERG_THRES_cpu_fb_peak_thres_END    (22)


/*****************************************************************************
 结构名    : GBBP_AFC_RPT_UNION
 结构说明  : AFC_RPT 寄存器结构定义。地址偏移量:0x1038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_rpt_reg;
    struct
    {
        unsigned int  afc_vctxo_cpu       : 14; /* bit[0-13] : AFC输出的VCTXO控制电压。 */
        unsigned int  reserved            : 2;  /* bit[14-15]: 保留 */
        unsigned int  afc_vctxo_16bit_cpu : 16; /* bit[16-31]: AFC输出的16比特VCTXO的控制电压信号 */
    } reg;
} GBBP_AFC_RPT_UNION;
#define GBBP_AFC_RPT_afc_vctxo_cpu_START        (0)
#define GBBP_AFC_RPT_afc_vctxo_cpu_END          (13)
#define GBBP_AFC_RPT_afc_vctxo_16bit_cpu_START  (16)
#define GBBP_AFC_RPT_afc_vctxo_16bit_cpu_END    (31)


/*****************************************************************************
 结构名    : GBBP_FB_RPT1_UNION
 结构说明  : FB_RPT1 寄存器结构定义。地址偏移量:0x103C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_rpt1_reg;
    struct
    {
        unsigned int  fb_pos_cpu    : 13; /* bit[0-12] : FB搜索得到的FB时隙头位置，相对于gtc_timebase的位置。 */
        unsigned int  reserved_0    : 3;  /* bit[13-15]: 保留 */
        unsigned int  sb_pos_offset : 8;  /* bit[16-23]: SB搜索位置相对于FB位置的偏移量 */
        unsigned int  reserved_1    : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_FB_RPT1_UNION;
#define GBBP_FB_RPT1_fb_pos_cpu_START     (0)
#define GBBP_FB_RPT1_fb_pos_cpu_END       (12)
#define GBBP_FB_RPT1_sb_pos_offset_START  (16)
#define GBBP_FB_RPT1_sb_pos_offset_END    (23)


/*****************************************************************************
 结构名    : GBBP_FB_RPT2_UNION
 结构说明  : FB_RPT2 寄存器结构定义。地址偏移量:0x1040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_rpt2_reg;
    struct
    {
        unsigned int  fb_square_max_cpu : 19; /* bit[0-18] : 本轮FB搜索的最大能量值，测试用。 */
        unsigned int  reserved          : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_FB_RPT2_UNION;
#define GBBP_FB_RPT2_fb_square_max_cpu_START  (0)
#define GBBP_FB_RPT2_fb_square_max_cpu_END    (18)


/*****************************************************************************
 结构名    : GBBP_SB_POS_RPT1_UNION
 结构说明  : SB_POS_RPT1 寄存器结构定义。地址偏移量:0x1044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_pos_rpt1_reg;
    struct
    {
        unsigned int  sb_pos_cpu   : 13; /* bit[0-12] : SB搜索能量最大值相对于timebase的位置，若SB搜索失败，则上报值无效。 */
        unsigned int  reserved_0   : 3;  /* bit[13-15]: 保留 */
        unsigned int  srch_fsm_cpu : 2;  /* bit[16-17]: 搜索状态机上报信号，
                                                        0：Idle State；
                                                        1：FB搜索状态；
                                                        2：AFC判断状态；
                                                        3：SB搜索状态。 */
        unsigned int  reserved_1   : 14; /* bit[18-31]: 保留 */
    } reg;
} GBBP_SB_POS_RPT1_UNION;
#define GBBP_SB_POS_RPT1_sb_pos_cpu_START    (0)
#define GBBP_SB_POS_RPT1_sb_pos_cpu_END      (12)
#define GBBP_SB_POS_RPT1_srch_fsm_cpu_START  (16)
#define GBBP_SB_POS_RPT1_srch_fsm_cpu_END    (17)


/*****************************************************************************
 结构名    : GBBP_SB_SQUARE_RPT1_UNION
 结构说明  : SB_SQUARE_RPT1 寄存器结构定义。地址偏移量:0x1048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_square_rpt1_reg;
    struct
    {
        unsigned int  sb_square_cpu : 30; /* bit[0-29] : SB搜索能量值的最大值，测试用。 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_SB_SQUARE_RPT1_UNION;
#define GBBP_SB_SQUARE_RPT1_sb_square_cpu_START  (0)
#define GBBP_SB_SQUARE_RPT1_sb_square_cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_SB_POS_RPT2_UNION
 结构说明  : SB_POS_RPT2 寄存器结构定义。地址偏移量:0x104C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_pos_rpt2_reg;
    struct
    {
        unsigned int  sb_max2_pos_cpu : 13; /* bit[0-12] : SB搜索能量次大值相对于timebase的位置。 */
        unsigned int  reserved        : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_SB_POS_RPT2_UNION;
#define GBBP_SB_POS_RPT2_sb_max2_pos_cpu_START  (0)
#define GBBP_SB_POS_RPT2_sb_max2_pos_cpu_END    (12)


/*****************************************************************************
 结构名    : GBBP_SB_SQUARE_RPT2_UNION
 结构说明  : SB_SQUARE_RPT2 寄存器结构定义。地址偏移量:0x1050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_square_rpt2_reg;
    struct
    {
        unsigned int  sb_max2_square_cpu : 30; /* bit[0-29] : SB搜索能量值的次大值，测试用。 */
        unsigned int  reserved           : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_SB_SQUARE_RPT2_UNION;
#define GBBP_SB_SQUARE_RPT2_sb_max2_square_cpu_START  (0)
#define GBBP_SB_SQUARE_RPT2_sb_max2_square_cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_SB_POS_RPT3_UNION
 结构说明  : SB_POS_RPT3 寄存器结构定义。地址偏移量:0x1054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_pos_rpt3_reg;
    struct
    {
        unsigned int  sb_max3_pos_cpu : 13; /* bit[0-12] : SB搜索能量第三大值相对于timebase的位置。 */
        unsigned int  reserved        : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_SB_POS_RPT3_UNION;
#define GBBP_SB_POS_RPT3_sb_max3_pos_cpu_START  (0)
#define GBBP_SB_POS_RPT3_sb_max3_pos_cpu_END    (12)


/*****************************************************************************
 结构名    : GBBP_SB_SQUARE_RPT3_UNION
 结构说明  : SB_SQUARE_RPT3 寄存器结构定义。地址偏移量:0x1058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_square_rpt3_reg;
    struct
    {
        unsigned int  sb_max3_square_cpu : 30; /* bit[0-29] : SB搜索能量值的第三大值，测试用。 */
        unsigned int  reserved           : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_SB_SQUARE_RPT3_UNION;
#define GBBP_SB_SQUARE_RPT3_sb_max3_square_cpu_START  (0)
#define GBBP_SB_SQUARE_RPT3_sb_max3_square_cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_STATE_RPT_UNION
 结构说明  : STATE_RPT 寄存器结构定义。地址偏移量:0x105C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      state_rpt_reg;
    struct
    {
        unsigned int  mau_curr_state      : 4;  /* bit[0-3]  : 乘累加状态上报，
                                                               4'd0：空闲状态；
                                                               4'd1：同步搜索状态；
                                                               4'd2：NB盲检测及同步位置更新；
                                                               4'd3：预滤波；
                                                               4'd4：TVB均衡解调；
                                                               4'd5：VALPP软判。
                                                               测试用。 */
        unsigned int  srch_curr_state     : 2;  /* bit[4-5]  : 乘累加模块搜索过程状态上报，测试用。 */
        unsigned int  reserved_0          : 2;  /* bit[6-7]  : 保留 */
        unsigned int  int_srch_status_cpu : 4;  /* bit[8-11] : 搜索中断状态，即反应产生中断的原因。此信号当int_srch_sync_cpu有效后有效，测试用。各bit含义如下，
                                                               C01搜索流程版本：
                                                               4'd0：搜索正常结束；
                                                               4'd1：FB未同步；
                                                               4'd2：AFC未锁定；
                                                               4'd3：SB译码错误；
                                                               4'd5：错误的搜索模式设置，即3'b000；
                                                               4'd6：在正常搜索过程中搜索使能信号gsp_srch_en变低。
                                                               111搜索优化流程版本：
                                                               4'd1：FB未同步；
                                                               4'd7：111搜索模式优化下，当FB-AFC锁定下，SB译码失败超出门限，导致搜索失败；
                                                               4'd8：111搜索模式优化下，当FB-AFC未锁定下，FB-AFC调整次数超出门限，导致搜索失败；
                                                               4'd9：111搜索模式优化下，多次SB译码成功但BSIC值不同，SB译码成功次数超出门限，导致搜索失败；
                                                               测试用。 */
        unsigned int  reserved_1          : 4;  /* bit[12-15]: 保留 */
        unsigned int  srch_status_cpu     : 3;  /* bit[16-18]:  */
        unsigned int  reserved_2          : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_STATE_RPT_UNION;
#define GBBP_STATE_RPT_mau_curr_state_START       (0)
#define GBBP_STATE_RPT_mau_curr_state_END         (3)
#define GBBP_STATE_RPT_srch_curr_state_START      (4)
#define GBBP_STATE_RPT_srch_curr_state_END        (5)
#define GBBP_STATE_RPT_int_srch_status_cpu_START  (8)
#define GBBP_STATE_RPT_int_srch_status_cpu_END    (11)
#define GBBP_STATE_RPT_srch_status_cpu_START      (16)
#define GBBP_STATE_RPT_srch_status_cpu_END        (18)


/*****************************************************************************
 结构名    : GBBP_SRCH_QB_RPT_UNION
 结构说明  : SRCH_QB_RPT 寄存器结构定义。地址偏移量:0x1064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_qb_rpt_reg;
    struct
    {
        unsigned int  srch_timebase_qb    : 13; /* bit[0-12] : 搜索中断所在gtc_timebase上报。 */
        unsigned int  reserved_0          : 3;  /* bit[13-15]: 保留 */
        unsigned int  srch_int_mod        : 3;  /* bit[16-18]: 搜索中断时，gsp_srch_mod上报。 */
        unsigned int  reserved_1          : 9;  /* bit[19-27]: 保留 */
        unsigned int  srch_start_mod      : 3;  /* bit[28-30]: 搜索启动时，gsp_srch_mod上报。 */
        unsigned int  gsp_ncell_srch_flag : 1;  /* bit[31]   : 当前搜索小区类型上报，
                                                               0：表示服务小区；
                                                               1：表示邻区。 */
    } reg;
} GBBP_SRCH_QB_RPT_UNION;
#define GBBP_SRCH_QB_RPT_srch_timebase_qb_START     (0)
#define GBBP_SRCH_QB_RPT_srch_timebase_qb_END       (12)
#define GBBP_SRCH_QB_RPT_srch_int_mod_START         (16)
#define GBBP_SRCH_QB_RPT_srch_int_mod_END           (18)
#define GBBP_SRCH_QB_RPT_srch_start_mod_START       (28)
#define GBBP_SRCH_QB_RPT_srch_start_mod_END         (30)
#define GBBP_SRCH_QB_RPT_gsp_ncell_srch_flag_START  (31)
#define GBBP_SRCH_QB_RPT_gsp_ncell_srch_flag_END    (31)


/*****************************************************************************
 结构名    : GBBP_SRCH_FN_RPT_UNION
 结构说明  : SRCH_FN_RPT 寄存器结构定义。地址偏移量:0x106C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_fn_rpt_reg;
    struct
    {
        unsigned int  srch_fn_low  : 11; /* bit[0-10] : 搜索中断所在位置的gtc_fn_low上报。 */
        unsigned int  reserved_0   : 5;  /* bit[11-15]: 保留 */
        unsigned int  srch_fn_high : 11; /* bit[16-26]: 搜索中断所在位置的gtc_fn_high上报。 */
        unsigned int  reserved_1   : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_SRCH_FN_RPT_UNION;
#define GBBP_SRCH_FN_RPT_srch_fn_low_START   (0)
#define GBBP_SRCH_FN_RPT_srch_fn_low_END     (10)
#define GBBP_SRCH_FN_RPT_srch_fn_high_START  (16)
#define GBBP_SRCH_FN_RPT_srch_fn_high_END    (26)


/*****************************************************************************
 结构名    : GBBP_SB_ADVANCE_LEN_CFG_UNION
 结构说明  : SB_ADVANCE_LEN_CFG 寄存器结构定义。地址偏移量:0x1070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_advance_len_cfg_reg;
    struct
    {
        unsigned int  cpu_sb_advance_len : 6;  /* bit[0-5] : 001搜索模式下，SB提前接收符号的个数，即在SB之前多接受cpu_sb_advance_len个符号，可配0~34。 */
        unsigned int  reserved           : 26; /* bit[6-31]: 保留 */
    } reg;
} GBBP_SB_ADVANCE_LEN_CFG_UNION;
#define GBBP_SB_ADVANCE_LEN_CFG_cpu_sb_advance_len_START  (0)
#define GBBP_SB_ADVANCE_LEN_CFG_cpu_sb_advance_len_END    (5)


/*****************************************************************************
 结构名    : GBBP_SRCH_FRQ_RPT_UNION
 结构说明  : SRCH_FRQ_RPT 寄存器结构定义。地址偏移量:0x107C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_frq_rpt_reg;
    struct
    {
        unsigned int  srch_start_frq : 12; /* bit[0-11] : 搜索启动时的频点信息上报。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  srch_int_frq   : 12; /* bit[16-27]: 搜索中断时的频点信息上报。 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_SRCH_FRQ_RPT_UNION;
#define GBBP_SRCH_FRQ_RPT_srch_start_frq_START  (0)
#define GBBP_SRCH_FRQ_RPT_srch_start_frq_END    (11)
#define GBBP_SRCH_FRQ_RPT_srch_int_frq_START    (16)
#define GBBP_SRCH_FRQ_RPT_srch_int_frq_END      (27)


/*****************************************************************************
 结构名    : GBBP_AFC_LOOP1_RPT_UNION
 结构说明  : AFC_LOOP1_RPT 寄存器结构定义。地址偏移量:0x1078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_loop1_rpt_reg;
    struct
    {
        unsigned int  nbafc_1loop_cpu   : 31; /* bit[0-30]: 一阶环当前NB-AFC环路滤波累加器的上报值 */
        unsigned int  gsp_nb_afc_switch : 1;  /* bit[31]  : NB-AFC一阶环与二阶环状态上报。
                                                            0：表示当前处于一阶环；
                                                            1：表示当前处于二阶环。 */
    } reg;
} GBBP_AFC_LOOP1_RPT_UNION;
#define GBBP_AFC_LOOP1_RPT_nbafc_1loop_cpu_START    (0)
#define GBBP_AFC_LOOP1_RPT_nbafc_1loop_cpu_END      (30)
#define GBBP_AFC_LOOP1_RPT_gsp_nb_afc_switch_START  (31)
#define GBBP_AFC_LOOP1_RPT_gsp_nb_afc_switch_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_AFC_LOOP1_CFG_UNION
 结构说明  : CPU_AFC_LOOP1_CFG 寄存器结构定义。地址偏移量:0x1080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_afc_loop1_cfg_reg;
    struct
    {
        unsigned int  cpu_nbafc_1loop : 31; /* bit[0-30]: 上电后一阶环NB-AFC环路滤波累加器的配置值。
                                                          再配置cpu_afc_init_en为1后生效。 */
        unsigned int  reserved        : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_CPU_AFC_LOOP1_CFG_UNION;
#define GBBP_CPU_AFC_LOOP1_CFG_cpu_nbafc_1loop_START  (0)
#define GBBP_CPU_AFC_LOOP1_CFG_cpu_nbafc_1loop_END    (30)


/*****************************************************************************
 结构名    : GBBP_NCELL_NCO_RPT_UNION
 结构说明  : NCELL_NCO_RPT 寄存器结构定义。地址偏移量:0x1084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ncell_nco_rpt_reg;
    struct
    {
        unsigned int  ncell_nco_cpu    : 16; /* bit[0-15] : 邻区频偏检测结果上报。 */
        unsigned int  ncell_nco_status : 2;  /* bit[16-17]: 邻区频偏状态上报。 */
        unsigned int  reserved         : 14; /* bit[18-31]: 保留 */
    } reg;
} GBBP_NCELL_NCO_RPT_UNION;
#define GBBP_NCELL_NCO_RPT_ncell_nco_cpu_START     (0)
#define GBBP_NCELL_NCO_RPT_ncell_nco_cpu_END       (15)
#define GBBP_NCELL_NCO_RPT_ncell_nco_status_START  (16)
#define GBBP_NCELL_NCO_RPT_ncell_nco_status_END    (17)


/*****************************************************************************
 结构名    : GBBP_AFC_PHASE_THRESHOLD_CFG_UNION
 结构说明  : AFC_PHASE_THRESHOLD_CFG 寄存器结构定义。地址偏移量:0x108C，初值:0x02F8012C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_phase_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_afc_phase_min : 10; /* bit[0-9]  : NB-AFC算法相位估计值参考下限，典型值300。 */
        unsigned int  reserved_0        : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_afc_phase_max : 10; /* bit[16-25]: NB-AFC算法相位估计值参考上限，典型值760。 */
        unsigned int  reserved_1        : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_AFC_PHASE_THRESHOLD_CFG_UNION;
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_min_START  (0)
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_min_END    (9)
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_max_START  (16)
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_max_END    (25)


/*****************************************************************************
 结构名    : GBBP_AFC_FCUT_THRESHOLD_CFG_UNION
 结构说明  : AFC_FCUT_THRESHOLD_CFG 寄存器结构定义。地址偏移量:0x1090，初值:0x04000033，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_fcut_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_afc_fc_low  : 13; /* bit[0-12] : NB-AFC算法系数fcut的最小值，如果经过α滤波后的相位估计值小雨相位估计值参考下限，则系数fcut的值就等于此最小值。典型值51。 */
        unsigned int  reserved_0      : 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_afc_fc_high : 13; /* bit[16-28]: NB-AFC算法系数fcut的最大值，如果经过α滤波后的相位估计值大于相位估计值的参考上限，则系数fcut的值就等于此最大值。典型值1024。 */
        unsigned int  reserved_1      : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_AFC_FCUT_THRESHOLD_CFG_UNION;
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_low_START   (0)
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_low_END     (12)
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_high_START  (16)
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_high_END    (28)


/*****************************************************************************
 结构名    : GBBP_AFC_ALPHA_SEL_UNION
 结构说明  : AFC_ALPHA_SEL 寄存器结构定义。地址偏移量:0x1094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_alpha_sel_reg;
    struct
    {
        unsigned int  cpu_numerator_sel : 2;  /* bit[0-1] : NB-AFC算法α滤波系数选择：
                                                            0：1/64；
                                                            1：1/32；
                                                            2：1/16；
                                                            3：1/8。 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} GBBP_AFC_ALPHA_SEL_UNION;
#define GBBP_AFC_ALPHA_SEL_cpu_numerator_sel_START  (0)
#define GBBP_AFC_ALPHA_SEL_cpu_numerator_sel_END    (1)


/*****************************************************************************
 结构名    : GBBP_CPU_SRCH_EN_CLR_UNION
 结构说明  : CPU_SRCH_EN_CLR 寄存器结构定义。地址偏移量:0x1124，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_srch_en_clr_reg;
    struct
    {
        unsigned int  cpu_srch_en_clr_imi          : 1;  /* bit[0]    : 写1表示产生gsp_srch_en清零信号，逻辑自清零。 */
        unsigned int  cpu_nb_demod_en_clr_imi      : 1;  /* bit[1]    : 写1表示产生gsp_nb_demod_en清零信号，逻辑自清零。 */
        unsigned int  cpu_agc_en_clr_imi           : 1;  /* bit[2]    : 写1表示产生gsp_agc_en清零信号，逻辑自清零。 */
        unsigned int  cpu_nb_afc_en_clr_imi        : 1;  /* bit[3]    : 写1表示产生gsp_nb_afc_en清零信号，逻辑自清零。 */
        unsigned int  cpu_alpha_toa_energy_clr_imi : 1;  /* bit[4]    : 写1表示产生TOA ALPHA能量累加值的清零信号，逻辑自清零。 */
        unsigned int  reserved_0                   : 11; /* bit[5-15] : 保留 */
        unsigned int  gsp_srch_en                  : 1;  /* bit[16]   : 搜索使能状态上报。 */
        unsigned int  gsp_nb_demod_en              : 1;  /* bit[17]   : NB解调使能状态上报。 */
        unsigned int  reserved_1                   : 14; /* bit[18-31]: 保留 */
    } reg;
} GBBP_CPU_SRCH_EN_CLR_UNION;
#define GBBP_CPU_SRCH_EN_CLR_cpu_srch_en_clr_imi_START           (0)
#define GBBP_CPU_SRCH_EN_CLR_cpu_srch_en_clr_imi_END             (0)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_demod_en_clr_imi_START       (1)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_demod_en_clr_imi_END         (1)
#define GBBP_CPU_SRCH_EN_CLR_cpu_agc_en_clr_imi_START            (2)
#define GBBP_CPU_SRCH_EN_CLR_cpu_agc_en_clr_imi_END              (2)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_afc_en_clr_imi_START         (3)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_afc_en_clr_imi_END           (3)
#define GBBP_CPU_SRCH_EN_CLR_cpu_alpha_toa_energy_clr_imi_START  (4)
#define GBBP_CPU_SRCH_EN_CLR_cpu_alpha_toa_energy_clr_imi_END    (4)
#define GBBP_CPU_SRCH_EN_CLR_gsp_srch_en_START                   (16)
#define GBBP_CPU_SRCH_EN_CLR_gsp_srch_en_END                     (16)
#define GBBP_CPU_SRCH_EN_CLR_gsp_nb_demod_en_START               (17)
#define GBBP_CPU_SRCH_EN_CLR_gsp_nb_demod_en_END                 (17)


/*****************************************************************************
 结构名    : GBBP_NB_POS_RPT_UNION
 结构说明  : NB_POS_RPT 寄存器结构定义。地址偏移量:0x1060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_pos_rpt_reg;
    struct
    {
        unsigned int  nb_pos_cpu         : 13; /* bit[0-12] : NB位置更新上报，是读取时刻最后一个解调BURST的位置，其相对于timebase。CPU可以在帧中断中读取。精度2QB。 */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: 保留 */
        unsigned int  mod_type_cpu       : 2;  /* bit[16-17]: NB调制方式上报，
                                                              0：GMSK调制；
                                                              1：8PSK调制；
                                                              2：DummyBurst。 */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: 保留 */
        unsigned int  mod_type_first_cpu : 2;  /* bit[24-25]: NB调制方式第一次判决结果上报。 */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_NB_POS_RPT_UNION;
#define GBBP_NB_POS_RPT_nb_pos_cpu_START          (0)
#define GBBP_NB_POS_RPT_nb_pos_cpu_END            (12)
#define GBBP_NB_POS_RPT_mod_type_cpu_START        (16)
#define GBBP_NB_POS_RPT_mod_type_cpu_END          (17)
#define GBBP_NB_POS_RPT_mod_type_first_cpu_START  (24)
#define GBBP_NB_POS_RPT_mod_type_first_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_CPU_8PSK_PSP_ALPHA_PARA_UNION
 结构说明  : CPU_8PSK_PSP_ALPHA_PARA 寄存器结构定义。地址偏移量:0x1068，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_8psk_psp_alpha_para_reg;
    struct
    {
        unsigned int  cpu_8psk_psp_alpha_para : 2;  /* bit[0-1] : 8psk均衡解调中求PSP_EN的参数alpha，
                                                                  0：对应的值为8；
                                                                  1：对应的值为16；
                                                                  2：对应的值为24；
                                                                  3：无效。
                                                                  默认值为1。 */
        unsigned int  reserved                : 29; /* bit[2-30]: 保留 */
        unsigned int  cpu_opt_en              : 1;  /* bit[31]  : 1表示打开信道因子优化配置。 */
    } reg;
} GBBP_CPU_8PSK_PSP_ALPHA_PARA_UNION;
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_8psk_psp_alpha_para_START  (0)
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_8psk_psp_alpha_para_END    (1)
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_opt_en_START               (31)
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_opt_en_END                 (31)


/*****************************************************************************
 结构名    : GBBP_CPU_TOA_ALPHA_PARA_UNION
 结构说明  : CPU_TOA_ALPHA_PARA 寄存器结构定义。地址偏移量:0x1074，初值:0x00000004，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_toa_alpha_para_reg;
    struct
    {
        unsigned int  cpu_alpha_parameter : 3;  /* bit[0-2] : alpha滤波系数选择：
                                                              0：表示选择系数为1/2；
                                                              1：表示选择系数为1/4；
                                                              2：表示选择系数为1/8；
                                                              3：表示选择系数为1/16；
                                                              4：表示选择系数为1/32。 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} GBBP_CPU_TOA_ALPHA_PARA_UNION;
#define GBBP_CPU_TOA_ALPHA_PARA_cpu_alpha_parameter_START  (0)
#define GBBP_CPU_TOA_ALPHA_PARA_cpu_alpha_parameter_END    (2)


/*****************************************************************************
 结构名    : GBBP_CPU_CH_EST_OPT_UNION
 结构说明  : CPU_CH_EST_OPT 寄存器结构定义。地址偏移量:0x1088，初值:0x00050042，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ch_est_opt_reg;
    struct
    {
        unsigned int  cpu_ch_est_opt_noise_alpha : 3;  /* bit[0-2]  : 信道估计优化噪声系数因子，取值1~5，默认配置2。 */
        unsigned int  reserved_0                 : 3;  /* bit[3-5]  : 保留 */
        unsigned int  cpu_valpp_opt_en           : 1;  /* bit[6]    : valpp计算PSP更新使能信号，1有效。 */
        unsigned int  cpu_ch_est_opt_bypass      : 1;  /* bit[7]    : 1表示旁路信道估计优化功能；
                                                                      0表示打开信道估计优化功能。 */
        unsigned int  reserved_1                 : 8;  /* bit[8-15] : 保留 */
        unsigned int  cpu_white_filter_thres     : 3;  /* bit[16-18]: 白化滤波判决门限，当噪声大于能量的倍数超过该门限，不启动白化滤波。对于NB可配置范围时1~7，表示1~7倍；对于SB，固定配置为5，表示5倍。 */
        unsigned int  reserved_2                 : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_CPU_CH_EST_OPT_UNION;
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_noise_alpha_START  (0)
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_noise_alpha_END    (2)
#define GBBP_CPU_CH_EST_OPT_cpu_valpp_opt_en_START            (6)
#define GBBP_CPU_CH_EST_OPT_cpu_valpp_opt_en_END              (6)
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_bypass_START       (7)
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_bypass_END         (7)
#define GBBP_CPU_CH_EST_OPT_cpu_white_filter_thres_START      (16)
#define GBBP_CPU_CH_EST_OPT_cpu_white_filter_thres_END        (18)


/*****************************************************************************
 结构名    : GBBP_NB_MOD_TYPE_RPT_UNION
 结构说明  : NB_MOD_TYPE_RPT 寄存器结构定义。地址偏移量:0x1098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_mod_type_rpt_reg;
    struct
    {
        unsigned int  slot_demod_flag_cpu : 16; /* bit[0-15] : bit0~bit15表示多时隙的第一，第二，第三，第四个时隙的四个BURST调制盲检测标志上报，0标识GMSK，1标识8PSK。 */
        unsigned int  slot_burst_flag_cpu : 16; /* bit[16-31]: bit16~bit31表示多时隙的第一，第二，第三，第四个时隙的四个BURST类型盲检测标志上报，0标识NB，1标识DB。 */
    } reg;
} GBBP_NB_MOD_TYPE_RPT_UNION;
#define GBBP_NB_MOD_TYPE_RPT_slot_demod_flag_cpu_START  (0)
#define GBBP_NB_MOD_TYPE_RPT_slot_demod_flag_cpu_END    (15)
#define GBBP_NB_MOD_TYPE_RPT_slot_burst_flag_cpu_START  (16)
#define GBBP_NB_MOD_TYPE_RPT_slot_burst_flag_cpu_END    (31)


/*****************************************************************************
 结构名    : GBBP_NB_BURST_TYPE_RPT_UNION
 结构说明  : NB_BURST_TYPE_RPT 寄存器结构定义。地址偏移量:0x10BC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_burst_type_rpt_reg;
    struct
    {
        unsigned int  slot_demod_flag_high_cpu : 8;  /* bit[0-7]  : bit0~bit7表示多时隙的第五，第六时隙的两个BURST调制盲检测标志上报，0标识GMSK，1标识8PSK。 */
        unsigned int  reserved_0               : 8;  /* bit[8-15] : 保留 */
        unsigned int  slot_burst_flag_high_cpu : 8;  /* bit[16-23]: bit16~bit23表示多时隙的第五，第六时隙的两个BURST类型标志上报，0标识NB，1标识DB。 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_NB_BURST_TYPE_RPT_UNION;
#define GBBP_NB_BURST_TYPE_RPT_slot_demod_flag_high_cpu_START  (0)
#define GBBP_NB_BURST_TYPE_RPT_slot_demod_flag_high_cpu_END    (7)
#define GBBP_NB_BURST_TYPE_RPT_slot_burst_flag_high_cpu_START  (16)
#define GBBP_NB_BURST_TYPE_RPT_slot_burst_flag_high_cpu_END    (23)


/*****************************************************************************
 结构名    : GBBP_GROSS_CARRIER_ENERGY1_UNION
 结构说明  : GROSS_CARRIER_ENERGY1 寄存器结构定义。地址偏移量:0x109C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy1_reg;
    struct
    {
        unsigned int  thres_c_1d : 19; /* bit[0-18] : 第一近的一个BURST解调前粗测C值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY1_UNION;
#define GBBP_GROSS_CARRIER_ENERGY1_thres_c_1d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY1_thres_c_1d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_INTERFERE_ENERGY1_UNION
 结构说明  : GROSS_INTERFERE_ENERGY1 寄存器结构定义。地址偏移量:0x10A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy1_reg;
    struct
    {
        unsigned int  thres_i_1d : 19; /* bit[0-18] : 第一近的一个BURST解调前粗测I值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY1_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY1_thres_i_1d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY1_thres_i_1d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_CARRIER_ENERGY2_UNION
 结构说明  : GROSS_CARRIER_ENERGY2 寄存器结构定义。地址偏移量:0x10A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy2_reg;
    struct
    {
        unsigned int  thres_c_2d : 19; /* bit[0-18] : 第二近的一个BURST解调前粗测C值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY2_UNION;
#define GBBP_GROSS_CARRIER_ENERGY2_thres_c_2d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY2_thres_c_2d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_INTERFERE_ENERGY2_UNION
 结构说明  : GROSS_INTERFERE_ENERGY2 寄存器结构定义。地址偏移量:0x10A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy2_reg;
    struct
    {
        unsigned int  thres_i_2d : 19; /* bit[0-18] : 第二近的一个BURST解调前粗测I值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY2_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY2_thres_i_2d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY2_thres_i_2d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_CARRIER_ENERGY3_UNION
 结构说明  : GROSS_CARRIER_ENERGY3 寄存器结构定义。地址偏移量:0x10AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy3_reg;
    struct
    {
        unsigned int  thres_c_3d : 19; /* bit[0-18] : 第三近的一个BURST解调前粗测C值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY3_UNION;
#define GBBP_GROSS_CARRIER_ENERGY3_thres_c_3d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY3_thres_c_3d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_INTERFERE_ENERGY3_UNION
 结构说明  : GROSS_INTERFERE_ENERGY3 寄存器结构定义。地址偏移量:0x10B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy3_reg;
    struct
    {
        unsigned int  thres_i_3d : 19; /* bit[0-18] : 第三近的一个BURST解调前粗测I值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY3_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY3_thres_i_3d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY3_thres_i_3d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_CARRIER_ENERGY4_UNION
 结构说明  : GROSS_CARRIER_ENERGY4 寄存器结构定义。地址偏移量:0x10B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy4_reg;
    struct
    {
        unsigned int  thres_c_4d : 19; /* bit[0-18] : 第四近的一个BURST解调前粗测C值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY4_UNION;
#define GBBP_GROSS_CARRIER_ENERGY4_thres_c_4d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY4_thres_c_4d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_INTERFERE_ENERGY4_UNION
 结构说明  : GROSS_INTERFERE_ENERGY4 寄存器结构定义。地址偏移量:0x10B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy4_reg;
    struct
    {
        unsigned int  thres_i_4d : 19; /* bit[0-18] : 第四近的一个BURST解调前粗测I值上报，测试用。 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY4_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY4_thres_i_4d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY4_thres_i_4d_END    (18)


/*****************************************************************************
 结构名    : GBBP_VALPP_CARRIER_ENERGY0_UNION
 结构说明  : VALPP_CARRIER_ENERGY0 寄存器结构定义。地址偏移量:0x1100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy0_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_cpu : 31; /* bit[0-30]: 读取时刻前最近burst对应的载波能量值，无符号数。 */
        unsigned int  reserved                 : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY0_UNION;
#define GBBP_VALPP_CARRIER_ENERGY0_valpp_carrier_energy_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY0_valpp_carrier_energy_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_VALPP_INTERFERE_ENERGY0_UNION
 结构说明  : VALPP_INTERFERE_ENERGY0 寄存器结构定义。地址偏移量:0x1150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy0_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_cpu : 26; /* bit[0-25] : 读取时刻前最近burst对应的干扰能量值，无符号数。 */
        unsigned int  reserved                   : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY0_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY0_valpp_interfere_energy_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY0_valpp_interfere_energy_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_VALPP_DEM_TYPE_TOA0_UNION
 结构说明  : VALPP_DEM_TYPE_TOA0 寄存器结构定义。地址偏移量:0x1104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa0_reg;
    struct
    {
        unsigned int  toa_sel_result                 : 6;  /* bit[0-5]  : 最近6个时隙的TOA样点选择结果，
                                                                          bit0：最近一个burst的选择结果；
                                                                          bit1：第二近burst的选择结果，
                                                                          其他依次类推。
                                                                          0表示选择前半个符号，1表示选择后半个符号，需要在nb_pos_adj的基础上加上2QB。 */
        unsigned int  reserved_0                     : 2;  /* bit[6-7]  : 保留 */
        unsigned int  max_sum_index_cpu              : 4;  /* bit[8-11] : SAIC后TOA五径C值最大值对应径号；
                                                                          取值范围0~4。 */
        unsigned int  reserved_1                     : 2;  /* bit[12-13]: 保留 */
        unsigned int  mod_type_1d                    : 2;  /* bit[14-15]: 读取时刻最近BURST的调制方式，
                                                                          0：GSKM；
                                                                          1：8PSK；
                                                                          2：DummyBurst。 */
        unsigned int  nb_pos_adj_cpu_sav0            : 4;  /* bit[16-19]: 读取时刻最近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。 */
        unsigned int  demod_slot_1d                  : 3;  /* bit[20-22]: 读取时刻最近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_2                     : 1;  /* bit[23]   : 保留 */
        unsigned int  nserv_cell_ind_1d              : 1;  /* bit[24]   : 读取时刻最近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_3                     : 3;  /* bit[25-27]: 保留 */
        unsigned int  mod_type_first_1d              : 2;  /* bit[28-29]: 读取时刻前的最近BURST对应的一次判决的调制方式，
                                                                          0：GMSK调制；
                                                                          1：8PSK调制；
                                                                          2：DummyBurst。
                                                                          该寄存器测试使用。 */
        unsigned int  demod_info_valid_flag0_clr_imi : 1;  /* bit[30]   : 对demod_info_valid_flag0清零。写1清零。 */
        unsigned int  demod_info_valid_flag0         : 1;  /* bit[31]   : 读取时刻最近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过bit30对该bit清零，指示该信息已经读取。 */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA0_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA0_toa_sel_result_START                  (0)
#define GBBP_VALPP_DEM_TYPE_TOA0_toa_sel_result_END                    (5)
#define GBBP_VALPP_DEM_TYPE_TOA0_max_sum_index_cpu_START               (8)
#define GBBP_VALPP_DEM_TYPE_TOA0_max_sum_index_cpu_END                 (11)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_1d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_1d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA0_nb_pos_adj_cpu_sav0_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA0_nb_pos_adj_cpu_sav0_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_slot_1d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_slot_1d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA0_nserv_cell_ind_1d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA0_nserv_cell_ind_1d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_first_1d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_first_1d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_END            (31)


/*****************************************************************************
 结构名    : GBBP_VALPP_CARRIER_ENERGY1_UNION
 结构说明  : VALPP_CARRIER_ENERGY1 寄存器结构定义。地址偏移量:0x1108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy1_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_1d_cpu : 31; /* bit[0-30]: 读取时刻前第二近burst对应的载波能量值，无符号数。 */
        unsigned int  reserved                    : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY1_UNION;
#define GBBP_VALPP_CARRIER_ENERGY1_valpp_carrier_energy_1d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY1_valpp_carrier_energy_1d_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_VALPP_INTERFERE_ENERGY1_UNION
 结构说明  : VALPP_INTERFERE_ENERGY1 寄存器结构定义。地址偏移量:0x1154，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy1_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_1d_cpu : 26; /* bit[0-25] : 读取时刻前第二近burst对应的干扰能量值，无符号数。 */
        unsigned int  reserved                      : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY1_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY1_valpp_interfere_energy_1d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY1_valpp_interfere_energy_1d_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_VALPP_DEM_TYPE_TOA1_UNION
 结构说明  : VALPP_DEM_TYPE_TOA1 寄存器结构定义。地址偏移量:0x110C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa1_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : 保留 */
        unsigned int  mod_type_2d                    : 2;  /* bit[14-15]: 读取时刻第二近BURST的调制方式，
                                                                          0：GSKM；
                                                                          1：8PSK；
                                                                          2：DummyBurst。 */
        unsigned int  nb_pos_adj_cpu_sav1            : 4;  /* bit[16-19]: 读取时刻第二近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。 */
        unsigned int  demod_slot_2d                  : 3;  /* bit[20-22]: 读取时刻第二近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : 保留 */
        unsigned int  nserv_cell_ind_2d              : 1;  /* bit[24]   : 读取时刻第二近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: 保留 */
        unsigned int  mod_type_first_2d              : 2;  /* bit[28-29]: 读取时刻前的第二近BURST对应的一次判决的调制方式，
                                                                          0：GMSK调制；
                                                                          1：8PSK调制；
                                                                          2：DummyBurst。
                                                                          该寄存器测试使用。 */
        unsigned int  demod_info_valid_flag1_clr_imi : 1;  /* bit[30]   : 对demod_info_valid_flag1清零。写1清零。 */
        unsigned int  demod_info_valid_flag1         : 1;  /* bit[31]   : 读取时刻第二近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过写bit30对该bit清零，指示该信息已经读取。 */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA1_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_2d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_2d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA1_nb_pos_adj_cpu_sav1_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA1_nb_pos_adj_cpu_sav1_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_slot_2d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_slot_2d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA1_nserv_cell_ind_2d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA1_nserv_cell_ind_2d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_first_2d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_first_2d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_END            (31)


/*****************************************************************************
 结构名    : GBBP_VALPP_CARRIER_ENERGY2_UNION
 结构说明  : VALPP_CARRIER_ENERGY2 寄存器结构定义。地址偏移量:0x1110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy2_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_2d_cpu : 31; /* bit[0-30]: 读取时刻前第三近burst对应的载波能量值，无符号数。 */
        unsigned int  reserved                    : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY2_UNION;
#define GBBP_VALPP_CARRIER_ENERGY2_valpp_carrier_energy_2d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY2_valpp_carrier_energy_2d_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_VALPP_INTERFERE_ENERGY2_UNION
 结构说明  : VALPP_INTERFERE_ENERGY2 寄存器结构定义。地址偏移量:0x1158，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy2_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_2d_cpu : 26; /* bit[0-25] : 读取时刻前第三近burst对应的干扰能量值，无符号数。 */
        unsigned int  reserved                      : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY2_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY2_valpp_interfere_energy_2d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY2_valpp_interfere_energy_2d_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_VALPP_DEM_TYPE_TOA2_UNION
 结构说明  : VALPP_DEM_TYPE_TOA2 寄存器结构定义。地址偏移量:0x1114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa2_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : 保留 */
        unsigned int  mod_type_3d                    : 2;  /* bit[14-15]: 读取时刻第三近BURST的调制方式，
                                                                          0：GSKM；
                                                                          1：8PSK；
                                                                          2：DummyBurst。 */
        unsigned int  nb_pos_adj_cpu_sav2            : 4;  /* bit[16-19]: 读取时刻第三近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。 */
        unsigned int  demod_slot_3d                  : 3;  /* bit[20-22]: 读取时刻第三近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : 保留 */
        unsigned int  nserv_cell_ind_3d              : 1;  /* bit[24]   : 读取时刻第三近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: 保留 */
        unsigned int  mod_type_first_3d              : 2;  /* bit[28-29]: 读取时刻前的第三近BURST对应的一次判决的调制方式，
                                                                          0：GMSK调制；
                                                                          1：8PSK调制；
                                                                          2：DummyBurst。
                                                                          该寄存器测试使用。 */
        unsigned int  demod_info_valid_flag2_clr_imi : 1;  /* bit[30]   : 对demod_info_valid_flag2清零。写1清零。 */
        unsigned int  demod_info_valid_flag2         : 1;  /* bit[31]   : 读取时刻第三近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过写bit30对该bit清零，指示该信息已经读取。 */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA2_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_3d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_3d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA2_nb_pos_adj_cpu_sav2_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA2_nb_pos_adj_cpu_sav2_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_slot_3d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_slot_3d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA2_nserv_cell_ind_3d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA2_nserv_cell_ind_3d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_first_3d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_first_3d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_END            (31)


/*****************************************************************************
 结构名    : GBBP_VALPP_CARRIER_ENERGY3_UNION
 结构说明  : VALPP_CARRIER_ENERGY3 寄存器结构定义。地址偏移量:0x1118，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy3_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_3d_cpu : 31; /* bit[0-30]: 读取时刻前第四近burst对应的载波能量值，无符号数。 */
        unsigned int  reserved                    : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY3_UNION;
#define GBBP_VALPP_CARRIER_ENERGY3_valpp_carrier_energy_3d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY3_valpp_carrier_energy_3d_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_VALPP_INTERFERE_ENERGY3_UNION
 结构说明  : VALPP_INTERFERE_ENERGY3 寄存器结构定义。地址偏移量:0x115C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy3_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_3d_cpu : 26; /* bit[0-25] : 读取时刻前第四近burst对应的干扰能量值，无符号数。 */
        unsigned int  reserved                      : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY3_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY3_valpp_interfere_energy_3d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY3_valpp_interfere_energy_3d_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_VALPP_DEM_TYPE_TOA3_UNION
 结构说明  : VALPP_DEM_TYPE_TOA3 寄存器结构定义。地址偏移量:0x111C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa3_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : 保留 */
        unsigned int  mod_type_4d                    : 2;  /* bit[14-15]: 读取时刻第四近BURST的调制方式，
                                                                          0：GSKM；
                                                                          1：8PSK；
                                                                          2：DummyBurst。 */
        unsigned int  nb_pos_adj_cpu_sav3            : 4;  /* bit[16-19]: 读取时刻第四近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。 */
        unsigned int  demod_slot_4d                  : 3;  /* bit[20-22]: 读取时刻第四近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : 保留 */
        unsigned int  nserv_cell_ind_4d              : 1;  /* bit[24]   : 读取时刻第四近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: 保留 */
        unsigned int  mod_type_first_4d              : 2;  /* bit[28-29]: 读取时刻前的第四近BURST对应的一次判决的调制方式，
                                                                          0：GMSK调制；
                                                                          1：8PSK调制；
                                                                          2：DummyBurst。
                                                                          该寄存器测试使用。 */
        unsigned int  demod_info_valid_flag3_clr_imi : 1;  /* bit[30]   : 对demod_info_valid_flag3清零。写1清零。 */
        unsigned int  demod_info_valid_flag3         : 1;  /* bit[31]   : 读取时刻第四近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该写bit30对该bit清零，指示该信息已经读取。 */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA3_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_4d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_4d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA3_nb_pos_adj_cpu_sav3_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA3_nb_pos_adj_cpu_sav3_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_slot_4d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_slot_4d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA3_nserv_cell_ind_4d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA3_nserv_cell_ind_4d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_first_4d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_first_4d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_END            (31)


/*****************************************************************************
 结构名    : GBBP_CPU_DEM_WIDTH_CFG_UNION
 结构说明  : CPU_DEM_WIDTH_CFG 寄存器结构定义。地址偏移量:0x1120，初值:0x00010000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_dem_width_cfg_reg;
    struct
    {
        unsigned int  cpu_demod_width_adjust : 2;  /* bit[0-1]  : 解调动态位宽配置
                                                                  2’d0：动态右移位数为0
                                                                  2’d1：动态右移位数为1
                                                                  2’d2：动态右移位数为2
                                                                  其他：保留 */
        unsigned int  reserved_0             : 14; /* bit[2-15] : 保留 */
        unsigned int  cpu_harq_width_mode    : 1;  /* bit[16]   : HARQ译码前数据位宽恢复模式配置
                                                                  0:按照解调动态位宽方案恢复数据
                                                                  1:不做解调软值位宽恢复操作 */
        unsigned int  reserved_1             : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_CPU_DEM_WIDTH_CFG_UNION;
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_demod_width_adjust_START  (0)
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_demod_width_adjust_END    (1)
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_harq_width_mode_START     (16)
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_harq_width_mode_END       (16)


/*****************************************************************************
 结构名    : GBBP_CPU_DB_TYPE_CFG_UNION
 结构说明  : CPU_DB_TYPE_CFG 寄存器结构定义。地址偏移量:0x1128，初值:0x00040001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_db_type_cfg_reg;
    struct
    {
        unsigned int  cpu_db_type      : 2;  /* bit[0-1]  : 物理层配置的Dummy 训练序列类型。
                                                            0：Dummy Burst训练序列同NB
                                                            1：Dummy Burst训练序列同C0模式训练序列
                                                            2：Dummy Burst训练序列同NB模式训练序列有固定的映射关系。
                                                            3：保留
                                                            默认值1。 */
        unsigned int  reserved_0       : 14; /* bit[2-15] : 保留 */
        unsigned int  cpu_db_threshold : 4;  /* bit[16-19]: Dummy Burst二次判决门限；
                                                            0： threshold_db=4；
                                                            1： threshold_db=6；
                                                            2： threshold_db=8；
                                                            3： threshold_db=9；
                                                            4： threshold_db=10；
                                                            5： threshold_db=11；
                                                            6： threshold_db=12；
                                                            7： threshold_db=14；
                                                            8： threshold_db=16；
                                                            9： threshold_db=20；
                                                            others： 保留 */
        unsigned int  reserved_1       : 12; /* bit[20-31]: 保留 */
    } reg;
} GBBP_CPU_DB_TYPE_CFG_UNION;
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_type_START       (0)
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_type_END         (1)
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_threshold_START  (16)
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_threshold_END    (19)


/*****************************************************************************
 结构名    : GBBP_CPU_DEM_BEP_MODE_EN_UNION
 结构说明  : CPU_DEM_BEP_MODE_EN 寄存器结构定义。地址偏移量:0x112C，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_dem_bep_mode_en_reg;
    struct
    {
        unsigned int  cpu_dem_bep_mode_en : 1;  /* bit[0]   : 1表示打开解调BEP功能。
                                                              0表示屏蔽解调BEP功能 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_DEM_BEP_MODE_EN_UNION;
#define GBBP_CPU_DEM_BEP_MODE_EN_cpu_dem_bep_mode_en_START  (0)
#define GBBP_CPU_DEM_BEP_MODE_EN_cpu_dem_bep_mode_en_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_VALPP_CARRY_CTRL_UNION
 结构说明  : CPU_VALPP_CARRY_CTRL 寄存器结构定义。地址偏移量:0x1130，初值:0x82008000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_valpp_carry_ctrl_reg;
    struct
    {
        unsigned int  cpu_carry_burst_pos  : 7;  /* bit[0-6]  : VALPP_RAM 和 CARRY_RAM 数据搬移目标BURST位置(carry to valpp) */
        unsigned int  reserved_0           : 8;  /* bit[7-14] : 保留 */
        unsigned int  cpu_valpp_carry_mode : 1;  /* bit[15]   : VALPP_RAM 和 CARRY_RAM 数据搬移方向指示，1表示从VALPP_RAM到CARRY_RAM，0表示从CARRY_RAM到VALPP_RAM,在这种模式下，需要相应的配置cpu_carry_burst_pos作为VALPP_RAM写数据的起始地址.
                                                                复位默认值为1 */
        unsigned int  reserved_1           : 8;  /* bit[16-23]: 保留 */
        unsigned int  cpu_valpp_carry_type : 2;  /* bit[24-25]: 表示从CARRY_RAM到VALPP_RAM的一个BURST数据量指示
                                                                         00 ：表示搬移GMSK调制的SB解调数据
                                                                         10 ：表示搬移GMSK调制的NB解调数据
                                                                         11 ：表示搬移8PSK调制的NB解调数据
                                                                         其他：表示搬移GMSK调制的NB解调数据
                                                                复位默认值为2’b10 */
        unsigned int  reserved_2           : 5;  /* bit[26-30]: 保留 */
        unsigned int  cpu_valpp_carry_en   : 1;  /* bit[31]   : 1表示VALPP_RAM 和 CARRY_RAM 数据搬移模式使能，当cpu_valpp_carry_mode配置为1时且cpu_valpp_carry_en配置为1时，解调模块往VALPP RAM写数据的同时，会将解调数据同时保存到CARRY RAM中.
                                                                复位默认值为1 */
    } reg;
} GBBP_CPU_VALPP_CARRY_CTRL_UNION;
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_carry_burst_pos_START   (0)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_carry_burst_pos_END     (6)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_mode_START  (15)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_mode_END    (15)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_type_START  (24)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_type_END    (25)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_en_START    (31)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_en_END      (31)


/*****************************************************************************
 结构名    : GBBP_CPU_VALPP_CARRY_START_UNION
 结构说明  : CPU_VALPP_CARRY_START 寄存器结构定义。地址偏移量:0x1134，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_valpp_carry_start_reg;
    struct
    {
        unsigned int  cpu_valpp_carry_start_imi : 1;  /* bit[0]   : VALPP_RAM 和 CARRY_RAM 数据搬移启动信号，只针对从CARRY_RAM到VALPP_RAM模式有效,逻辑自清零 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_VALPP_CARRY_START_UNION;
#define GBBP_CPU_VALPP_CARRY_START_cpu_valpp_carry_start_imi_START  (0)
#define GBBP_CPU_VALPP_CARRY_START_cpu_valpp_carry_start_imi_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_SAIC_CTRL_UNION
 结构说明  : CPU_SAIC_CTRL 寄存器结构定义。地址偏移量:0x1138，初值:0x02000101，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_saic_ctrl_reg;
    struct
    {
        unsigned int  cpu_saic_shift_pre   : 2;  /* bit[0-1]  : 判决反馈前，SAIC滤波输出值的移位值，11～13比特，默认值2’b01。该值用来调整性能偏差。
                                                                2’b00: 11
                                                                2’b01: 12
                                                                2’b10: 13 */
        unsigned int  reserved_0           : 6;  /* bit[2-7]  : 保留 */
        unsigned int  cpu_saic_shift_aft   : 2;  /* bit[8-9]  : 判决反馈后，SAIC滤波输出值的移位值，10～12比特，默认值是2’b01。该值用来调整性能偏差。
                                                                2’b00: 10;
                                                                2’b01: 11;
                                                                2’b10: 12; */
        unsigned int  reserved_1           : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_renew_toa_pos    : 2;  /* bit[16-17]: PHY在帧头位置配置下帧NB位置的调整量。
                                                                配置值范围－1～1，补码表示。
                                                                2’b11：表示下帧的NB较上帧调前一个符号；
                                                                2’b01：表示下帧的NB较上帧调后一个符号；
                                                                2’b00 ：表示不进行帧间调整。该信号在TDMA帧头后560qb自动清零。 */
        unsigned int  reserved_2           : 2;  /* bit[18-19]: 保留 */
        unsigned int  cpu_gmsk_ci_beta     : 2;  /* bit[20-21]: GMSK CI测量的调整系数，默认值是15(配置为2’b00)，可选值1和8
                                                                2’b00:15
                                                                2’b01: 8
                                                                2’b10: 1
                                                                默认值为2’b00 */
        unsigned int  reserved_3           : 2;  /* bit[22-23]: 保留 */
        unsigned int  cpu_cross_delta      : 3;  /* bit[24-26]: case(cpu_cross_delta)
                                                                3’b000: R[i][i] = R[i][i] + (R[i][i] >>8) ;
                                                                3’b001: R[i][i] = R[i][i] + (R[i][i] >>9) ;
                                                                3’b010: R[i][i] = R[i][i] + (R[i][i] >>10) ;
                                                                3’b011: R[i][i] = R[i][i] + (R[i][i] >>11) ;
                                                                3’b100: R[i][i] = R[i][i];
                                                                cpu_cross_delta信号是用于选择对角线元素的处理方式，默认值是3’b010。 */
        unsigned int  reserved_4           : 4;  /* bit[27-30]: 保留 */
        unsigned int  cpu_nb_info_rpt_mode : 1;  /* bit[31]   : 1 表示固定选择偶路，0表示选择最佳路 默认值为0。                     此信号用于选择上报的nb_pos_cpu, nb_pos_adj_cpu和C/I等。 */
    } reg;
} GBBP_CPU_SAIC_CTRL_UNION;
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_pre_START    (0)
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_pre_END      (1)
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_aft_START    (8)
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_aft_END      (9)
#define GBBP_CPU_SAIC_CTRL_cpu_renew_toa_pos_START     (16)
#define GBBP_CPU_SAIC_CTRL_cpu_renew_toa_pos_END       (17)
#define GBBP_CPU_SAIC_CTRL_cpu_gmsk_ci_beta_START      (20)
#define GBBP_CPU_SAIC_CTRL_cpu_gmsk_ci_beta_END        (21)
#define GBBP_CPU_SAIC_CTRL_cpu_cross_delta_START       (24)
#define GBBP_CPU_SAIC_CTRL_cpu_cross_delta_END         (26)
#define GBBP_CPU_SAIC_CTRL_cpu_nb_info_rpt_mode_START  (31)
#define GBBP_CPU_SAIC_CTRL_cpu_nb_info_rpt_mode_END    (31)


/*****************************************************************************
 结构名    : GBBP_MAX_DB_DATA_ENERGY_RPT_UNION
 结构说明  : MAX_DB_DATA_ENERGY_RPT 寄存器结构定义。地址偏移量:0x113C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      max_db_data_energy_rpt_reg;
    struct
    {
        unsigned int  max_data_energy_cpu : 22; /* bit[0-21] : DummuBurst检测DATA最大能量上报 */
        unsigned int  reserved            : 10; /* bit[22-31]: 保留 */
    } reg;
} GBBP_MAX_DB_DATA_ENERGY_RPT_UNION;
#define GBBP_MAX_DB_DATA_ENERGY_RPT_max_data_energy_cpu_START  (0)
#define GBBP_MAX_DB_DATA_ENERGY_RPT_max_data_energy_cpu_END    (21)


/*****************************************************************************
 结构名    : GBBP_ENG_WEIGHT_UNION
 结构说明  : ENG_WEIGHT 寄存器结构定义。地址偏移量:0x1144，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      eng_weight_reg;
    struct
    {
        unsigned int  cpu_mid_finger_weight : 3;  /* bit[0-2]  : NB位置计算使用的中心径能量加权值，默认值0
                                                                 含义与sb的权值一致 */
        unsigned int  reserved_0            : 1;  /* bit[3]    : 保留 */
        unsigned int  cpu_rptpos_use_weight : 1;  /* bit[4]    : 上报的nb_pos和nb_pos_adj使用中心径能量加权算法，1为使用，默认值0 */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_dempos_use_weight : 1;  /* bit[8]    : 解调位置继承使用中心径能量加权算法，1为使用，默认值0 */
        unsigned int  reserved_2            : 7;  /* bit[9-15] : 保留 */
        unsigned int  cpu_sb_finger_weight  : 3;  /* bit[16-18]: SB位置计算使用的中心径能量加权值，默认值0
                                                                 0表示权值为1；
                                                                 1表示权值为65/64；
                                                                 2表示权值为33/32；
                                                                 3表示权值为17/16；
                                                                 4表示权值为9/8；
                                                                 5表示权值为5/4； */
        unsigned int  reserved_3            : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_ENG_WEIGHT_UNION;
#define GBBP_ENG_WEIGHT_cpu_mid_finger_weight_START  (0)
#define GBBP_ENG_WEIGHT_cpu_mid_finger_weight_END    (2)
#define GBBP_ENG_WEIGHT_cpu_rptpos_use_weight_START  (4)
#define GBBP_ENG_WEIGHT_cpu_rptpos_use_weight_END    (4)
#define GBBP_ENG_WEIGHT_cpu_dempos_use_weight_START  (8)
#define GBBP_ENG_WEIGHT_cpu_dempos_use_weight_END    (8)
#define GBBP_ENG_WEIGHT_cpu_sb_finger_weight_START   (16)
#define GBBP_ENG_WEIGHT_cpu_sb_finger_weight_END     (18)


/*****************************************************************************
 结构名    : GBBP_LS_DC_CPU_UNION
 结构说明  : LS_DC_CPU 寄存器结构定义。地址偏移量:0x1160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ls_dc_cpu_reg;
    struct
    {
        unsigned int  ls_dc_q_cpu : 8;  /* bit[0-7]  : 当前burst直流Q路上报 */
        unsigned int  reserved_0  : 8;  /* bit[8-15] : 保留 */
        unsigned int  ls_dc_i_cpu : 8;  /* bit[16-23]: 当前burst直流I路上报 */
        unsigned int  reserved_1  : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_LS_DC_CPU_UNION;
#define GBBP_LS_DC_CPU_ls_dc_q_cpu_START  (0)
#define GBBP_LS_DC_CPU_ls_dc_q_cpu_END    (7)
#define GBBP_LS_DC_CPU_ls_dc_i_cpu_START  (16)
#define GBBP_LS_DC_CPU_ls_dc_i_cpu_END    (23)


/*****************************************************************************
 结构名    : GBBP_LS_TOA_RPT_EN_UNION
 结构说明  : LS_TOA_RPT_EN 寄存器结构定义。地址偏移量:0x1164，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ls_toa_rpt_en_reg;
    struct
    {
        unsigned int  cpu_ls_toa_rpt_en : 1;  /* bit[0]   : LS去直流TOA上报使能，0表示关闭，1表示打开。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_LS_TOA_RPT_EN_UNION;
#define GBBP_LS_TOA_RPT_EN_cpu_ls_toa_rpt_en_START  (0)
#define GBBP_LS_TOA_RPT_EN_cpu_ls_toa_rpt_en_END    (0)


/*****************************************************************************
 结构名    : GBBP_FB_2_POS_ENG_UNION
 结构说明  : FB_2_POS_ENG 寄存器结构定义。地址偏移量:0x1168，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_2_pos_eng_reg;
    struct
    {
        unsigned int  fb_pos_2_cpu       : 13; /* bit[0-12] : 据当前时刻第二近的FB周期的FB位置 */
        unsigned int  fb_square_max2_cpu : 18; /* bit[13-30]: 据当前时刻第二近的FB周期的FB最大能量 */
        unsigned int  reserved           : 1;  /* bit[31]   : 保留 */
    } reg;
} GBBP_FB_2_POS_ENG_UNION;
#define GBBP_FB_2_POS_ENG_fb_pos_2_cpu_START        (0)
#define GBBP_FB_2_POS_ENG_fb_pos_2_cpu_END          (12)
#define GBBP_FB_2_POS_ENG_fb_square_max2_cpu_START  (13)
#define GBBP_FB_2_POS_ENG_fb_square_max2_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_FB_3_POS_ENG_UNION
 结构说明  : FB_3_POS_ENG 寄存器结构定义。地址偏移量:0x116C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_3_pos_eng_reg;
    struct
    {
        unsigned int  fb_pos_3_cpu       : 13; /* bit[0-12] : 据当前时刻第三近的FB周期的FB位置 */
        unsigned int  fb_square_max3_cpu : 18; /* bit[13-30]: 据当前时刻第三近的FB周期的FB最大能量 */
        unsigned int  reserved           : 1;  /* bit[31]   : 保留 */
    } reg;
} GBBP_FB_3_POS_ENG_UNION;
#define GBBP_FB_3_POS_ENG_fb_pos_3_cpu_START        (0)
#define GBBP_FB_3_POS_ENG_fb_pos_3_cpu_END          (12)
#define GBBP_FB_3_POS_ENG_fb_square_max3_cpu_START  (13)
#define GBBP_FB_3_POS_ENG_fb_square_max3_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_SB_SAVE_STATUS_UNION
 结构说明  : SB_SAVE_STATUS 寄存器结构定义。地址偏移量:0x1170，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_save_status_reg;
    struct
    {
        unsigned int  sb_save_status_cpu : 2;  /* bit[0-1] : SB数据保存状态上报,每次gsp_sb_save_start后清零
                                                             00：未启动SB数据存储 
                                                             01：启动SB数据存储，且保存完毕 
                                                             10：启动SB存储，但保存完毕前异常终止（如搜索使能被拉低），数据无效 */
        unsigned int  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} GBBP_SB_SAVE_STATUS_UNION;
#define GBBP_SB_SAVE_STATUS_sb_save_status_cpu_START  (0)
#define GBBP_SB_SAVE_STATUS_sb_save_status_cpu_END    (1)


/*****************************************************************************
 结构名    : GBBP_SHORT_11X_CFG_UNION
 结构说明  : SHORT_11X_CFG 寄存器结构定义。地址偏移量:0x1174，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      short_11x_cfg_reg;
    struct
    {
        unsigned int  cpu_11x_capt_disable : 1;  /* bit[0]   : 110/111搜索模式时，不进入捕获态，直接进入跟踪态； */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : 保留 */
        unsigned int  cpu_afc_delay_sel    : 1;  /* bit[4]   : 110/111搜索模式时，AFC叉积长度;
                                                               0表示延迟长度为16，1表示延迟长度为2。
                                                               如果cpu_11x_capt_disable=0，则捕获态延迟长度固定为2，跟踪态固定为16； */
        unsigned int  reserved_1           : 27; /* bit[5-31]: 保留 */
    } reg;
} GBBP_SHORT_11X_CFG_UNION;
#define GBBP_SHORT_11X_CFG_cpu_11x_capt_disable_START  (0)
#define GBBP_SHORT_11X_CFG_cpu_11x_capt_disable_END    (0)
#define GBBP_SHORT_11X_CFG_cpu_afc_delay_sel_START     (4)
#define GBBP_SHORT_11X_CFG_cpu_afc_delay_sel_END       (4)


/*****************************************************************************
 结构名    : GBBP_FAST_101_CFG_UNION
 结构说明  : FAST_101_CFG 寄存器结构定义。地址偏移量:0x1178，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fast_101_cfg_reg;
    struct
    {
        unsigned int  cpu_fast_101_thresh     : 18; /* bit[0-17] : 提前启动SB的FB能量门限，当大于等于该门限时，启动SB搜索解调 */
        unsigned int  reserved                : 13; /* bit[18-30]: 保留 */
        unsigned int  cpu_fast_101_dist_judge : 1;  /* bit[31]   : 快速101模式下是否启动FB和SB距离的判断使能，为1表示当FB与SB距离超过34符号则本次搜索失败 */
    } reg;
} GBBP_FAST_101_CFG_UNION;
#define GBBP_FAST_101_CFG_cpu_fast_101_thresh_START      (0)
#define GBBP_FAST_101_CFG_cpu_fast_101_thresh_END        (17)
#define GBBP_FAST_101_CFG_cpu_fast_101_dist_judge_START  (31)
#define GBBP_FAST_101_CFG_cpu_fast_101_dist_judge_END    (31)


/*****************************************************************************
 结构名    : GBBP_HEAVY_NOISE_CFG_UNION
 结构说明  : HEAVY_NOISE_CFG 寄存器结构定义。地址偏移量:0x117C，初值:0x00007FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      heavy_noise_cfg_reg;
    struct
    {
        unsigned int  cpu_noise_afc_thresh        : 19; /* bit[0-18] : 停止AFC调整的噪声门限；当噪声的值大于该门限时，不关CI比值如何，都不调整AFC */
        unsigned int  reserved                    : 12; /* bit[19-30]: 保留 */
        unsigned int  cpu_heavy_noise_afc_disable : 1;  /* bit[31]   : 严重噪声（噪声超过一定门限）时，停止AFC调整，电平信号
                                                                       1：表示噪声过门限时，屏蔽AFC调整；
                                                                       0：表示不根据噪声大小屏蔽AFC调整 */
    } reg;
} GBBP_HEAVY_NOISE_CFG_UNION;
#define GBBP_HEAVY_NOISE_CFG_cpu_noise_afc_thresh_START         (0)
#define GBBP_HEAVY_NOISE_CFG_cpu_noise_afc_thresh_END           (18)
#define GBBP_HEAVY_NOISE_CFG_cpu_heavy_noise_afc_disable_START  (31)
#define GBBP_HEAVY_NOISE_CFG_cpu_heavy_noise_afc_disable_END    (31)


/*****************************************************************************
 结构名    : GBBP_ADDR_CPU_LUISE_AFC_UNION
 结构说明  : ADDR_CPU_LUISE_AFC 寄存器结构定义。地址偏移量:0x1258，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_luise_afc_reg;
    struct
    {
        unsigned int  cpu_luise_afc_en_imi : 1;  /* bit[0]    : Luise鉴频使能 */
        unsigned int  reserved_0           : 7;  /* bit[1-7]  : 保留 */
        unsigned int  cpu_single_tcxo_en   : 1;  /* bit[8]    : 单TCXO使能信号，用于控制搜索前数据是否经过NCO纠偏 */
        unsigned int  reserved_1           : 7;  /* bit[9-15] : 保留 */
        unsigned int  luise_fed            : 16; /* bit[16-31]: Luise鉴频优化算法计算得到的频偏调整值 */
    } reg;
} GBBP_ADDR_CPU_LUISE_AFC_UNION;
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_luise_afc_en_imi_START  (0)
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_luise_afc_en_imi_END    (0)
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_single_tcxo_en_START    (8)
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_single_tcxo_en_END      (8)
#define GBBP_ADDR_CPU_LUISE_AFC_luise_fed_START             (16)
#define GBBP_ADDR_CPU_LUISE_AFC_luise_fed_END               (31)


/*****************************************************************************
 结构名    : GBBP_ADDR_GDRX_SLEEP_POINT_UNION
 结构说明  : ADDR_GDRX_SLEEP_POINT 寄存器结构定义。地址偏移量:0x125C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_gdrx_sleep_point_reg;
    struct
    {
        unsigned int  gdrx_sleep_point : 13; /* bit[0-12] : 定点睡眠模式下，睡眠起始Qb时刻（TDMA）时刻，该参数是基于TDMA时标gtc_tdma_qb的 */
        unsigned int  reserved         : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_ADDR_GDRX_SLEEP_POINT_UNION;
#define GBBP_ADDR_GDRX_SLEEP_POINT_gdrx_sleep_point_START  (0)
#define GBBP_ADDR_GDRX_SLEEP_POINT_gdrx_sleep_point_END    (12)


/*****************************************************************************
 结构名    : GBBP_ADDR_CPU_TRANS_COMP_UNION
 结构说明  : ADDR_CPU_TRANS_COMP 寄存器结构定义。地址偏移量:0x1260，初值:0x00000010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_trans_comp_reg;
    struct
    {
        unsigned int  cpu_trans_comp : 10; /* bit[0-9]  : 定时信息从ON区传输到OFF区，软件配置的定时信息补偿参数。此值要大于全部数据传输时延，单位QB，默认配置16QB。 */
        unsigned int  reserved       : 22; /* bit[10-31]: 保留 */
    } reg;
} GBBP_ADDR_CPU_TRANS_COMP_UNION;
#define GBBP_ADDR_CPU_TRANS_COMP_cpu_trans_comp_START  (0)
#define GBBP_ADDR_CPU_TRANS_COMP_cpu_trans_comp_END    (9)


/*****************************************************************************
 结构名    : GBBP_ADDR_RX_IQ_MISMATCH_REG0_UNION
 结构说明  : ADDR_RX_IQ_MISMATCH_REG0 寄存器结构定义。地址偏移量:0x1270，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg0_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp0   : 10; /* bit[0-9]  : 第0组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_iq_comp_phase0 : 11; /* bit[16-26]: 第0组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG0_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_amp0_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_amp0_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_phase0_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_phase0_END    (26)


/*****************************************************************************
 结构名    : GBBP_ADDR_RX_IQ_MISMATCH_REG1_UNION
 结构说明  : ADDR_RX_IQ_MISMATCH_REG1 寄存器结构定义。地址偏移量:0x1274，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg1_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp1   : 10; /* bit[0-9]  : 第1组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_iq_comp_phase1 : 11; /* bit[16-26]: 第1组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG1_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_amp1_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_amp1_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_phase1_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_phase1_END    (26)


/*****************************************************************************
 结构名    : GBBP_ADDR_RX_IQ_MISMATCH_REG2_UNION
 结构说明  : ADDR_RX_IQ_MISMATCH_REG2 寄存器结构定义。地址偏移量:0x1278，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg2_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp2   : 10; /* bit[0-9]  : 第2组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_iq_comp_phase2 : 11; /* bit[16-26]: 第2组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG2_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_amp2_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_amp2_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_phase2_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_phase2_END    (26)


/*****************************************************************************
 结构名    : GBBP_ADDR_RX_IQ_MISMATCH_REG3_UNION
 结构说明  : ADDR_RX_IQ_MISMATCH_REG3 寄存器结构定义。地址偏移量:0x127C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg3_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp3   : 10; /* bit[0-9]  : 第3组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_iq_comp_phase3 : 11; /* bit[16-26]: 第3组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG3_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_amp3_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_amp3_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_phase3_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_phase3_END    (26)


/*****************************************************************************
 结构名    : GBBP_ADDR_RX_IQ_MISMATCH_REG4_UNION
 结构说明  : ADDR_RX_IQ_MISMATCH_REG4 寄存器结构定义。地址偏移量:0x1280，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg4_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp4   : 10; /* bit[0-9]  : 第4组幅度校准软件配置值A；10比特有符号数，取值范围-511~511。 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_iq_comp_phase4 : 11; /* bit[16-26]: 第4组相位校准软件配置值P；11比特有符号数，取值范围-1023~1023。 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG4_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_amp4_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_amp4_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_phase4_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_phase4_END    (26)


/*****************************************************************************
 结构名    : GBBP_ADDR_TX_RRC_EXT_UNION
 结构说明  : ADDR_TX_RRC_EXT 寄存器结构定义。地址偏移量:0x1284，初值:0x00040006，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_tx_rrc_ext_reg;
    struct
    {
        unsigned int  cpu_tx_rrc_finish_interval : 4;  /* bit[0-3]  : 最后一个tx_rrx_data_ind_in与gmod_finish之间的间隔clk数 */
        unsigned int  reserved_0                 : 12; /* bit[4-15] : 保留 */
        unsigned int  cpu_tx_rrc_ext_num         : 4;  /* bit[16-19]: 在调制结束后，扩展填充的样点个数 */
        unsigned int  reserved_1                 : 12; /* bit[20-31]: 保留 */
    } reg;
} GBBP_ADDR_TX_RRC_EXT_UNION;
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_finish_interval_START  (0)
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_finish_interval_END    (3)
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_ext_num_START          (16)
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_ext_num_END            (19)


/*****************************************************************************
 结构名    : GBBP_ADDR_MAX_PHI_DEV_UNION
 结构说明  : ADDR_MAX_PHI_DEV 寄存器结构定义。地址偏移量:0x1288，初值:0x000002F8，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_max_phi_dev_reg;
    struct
    {
        unsigned int  cpu_max_phi_dev : 11; /* bit[0-10] : SB最大频偏限幅。默认值为1800MHz的最大频偏760；900MHz时配置380。 */
        unsigned int  reserved        : 21; /* bit[11-31]: 保留 */
    } reg;
} GBBP_ADDR_MAX_PHI_DEV_UNION;
#define GBBP_ADDR_MAX_PHI_DEV_cpu_max_phi_dev_START  (0)
#define GBBP_ADDR_MAX_PHI_DEV_cpu_max_phi_dev_END    (10)


/*****************************************************************************
 结构名    : GBBP_ADDR_HD35_PARA_REG_UNION
 结构说明  : ADDR_HD35_PARA_REG 寄存器结构定义。地址偏移量:0x1290，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_hd35_para_reg_reg;
    struct
    {
        unsigned int  cpu_hd35_page_switch_en : 1;  /* bit[0]    : HD3/5初始配置参数配置RAM乒乓访问使能；1表示允许乒乓访问，0表示固定访问乒RAM空间；当该信号为1时，逻辑内部在TDMA帧头自动切换乒乓标志。 */
        unsigned int  reserved_0              : 15; /* bit[1-15] : 保留 */
        unsigned int  cpu_hd35_cal_bypass     : 1;  /* bit[16]   : HD3/5谐波消除功能旁路；0：表示谐波消除功能不旁路，但是否进行谐波消除还需要参考gsp_hd35_cal_en配置情况。1：表示谐波消除功能旁路，与V8R1版本时序完全一致。 */
        unsigned int  reserved_1              : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_ADDR_HD35_PARA_REG_UNION;
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_page_switch_en_START  (0)
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_page_switch_en_END    (0)
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_cal_bypass_START      (16)
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_cal_bypass_END        (16)


/*****************************************************************************
 结构名    : GBBP_CPU_SPI_RF_CFG_UNION
 结构说明  : CPU_SPI_RF_CFG 寄存器结构定义。地址偏移量:0x1368，初值:0x80000400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_spi_rf_cfg_reg;
    struct
    {
        unsigned int  cpu_spi_rd_start_addr  : 8;  /* bit[0-7]  : CPU接口配置SPI串口待发数据在SPI DATA RAM的起始位置，复位默认值为8'd0 */
        unsigned int  cpu_spi_trans_data_num : 5;  /* bit[8-12] : CPU接口配置本次需要发送的SPI串口数据数，00001表示一个数，10000表示16个数，复位默认值为5'b00100 */
        unsigned int  reserved               : 18; /* bit[13-30]: 保留 */
        unsigned int  spi_gtc_sel            : 1;  /* bit[31]   : 1表示SPI射频控制参数由GTC模块输出，0表示SPI射频控制参数由CPU接口模块输出，默认值为1；该信号只是用于软件规避TA较大时配置RF射频延时问题；正常情况下该信号都应该配置为1 */
    } reg;
} GBBP_CPU_SPI_RF_CFG_UNION;
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_rd_start_addr_START   (0)
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_rd_start_addr_END     (7)
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_trans_data_num_START  (8)
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_trans_data_num_END    (12)
#define GBBP_CPU_SPI_RF_CFG_spi_gtc_sel_START             (31)
#define GBBP_CPU_SPI_RF_CFG_spi_gtc_sel_END               (31)


/*****************************************************************************
 结构名    : GBBP_CPU_SPI_RF_RD_UNION
 结构说明  : CPU_SPI_RF_RD 寄存器结构定义。地址偏移量:0x136C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_spi_rf_rd_reg;
    struct
    {
        unsigned int  cpu_spi_rd_en_imi : 1;  /* bit[0]   : CPU启动SPI数据发送脉冲 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_SPI_RF_RD_UNION;
#define GBBP_CPU_SPI_RF_RD_cpu_spi_rd_en_imi_START  (0)
#define GBBP_CPU_SPI_RF_RD_cpu_spi_rd_en_imi_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_LINE_CTRL_UNION
 结构说明  : CPU_LINE_CTRL 寄存器结构定义。地址偏移量:0x1364，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_line_ctrl_reg;
    struct
    {
        unsigned int  cpu_gtc_line_ctrl           : 31; /* bit[0-30]: 公共线控CPU接口配置，具体分配由NV项决定。 */
        unsigned int  cpu_gtc_line_ctrl_wr_en_imi : 1;  /* bit[31]  : 28bit公共线控信号CPU写使能指示信号。 */
    } reg;
} GBBP_CPU_LINE_CTRL_UNION;
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_START            (0)
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_END              (30)
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_wr_en_imi_START  (31)
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_wr_en_imi_END    (31)


/*****************************************************************************
 结构名    : GBBP_GTC_GSP_LINE_STATE_RPT_UNION
 结构说明  : GTC_GSP_LINE_STATE_RPT 寄存器结构定义。地址偏移量:0x1384，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_gsp_line_state_rpt_reg;
    struct
    {
        unsigned int  gtc_ant_pa_sel : 31; /* bit[0-30]: 公共线控实际线控状态，测试用。 */
        unsigned int  reserved       : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_GTC_GSP_LINE_STATE_RPT_UNION;
#define GBBP_GTC_GSP_LINE_STATE_RPT_gtc_ant_pa_sel_START  (0)
#define GBBP_GTC_GSP_LINE_STATE_RPT_gtc_ant_pa_sel_END    (30)


/*****************************************************************************
 结构名    : GBBP_AAGC_GAIN1_CPU_UNION
 结构说明  : AAGC_GAIN1_CPU 寄存器结构定义。地址偏移量:0x1460，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain1_cpu_reg;
    struct
    {
        unsigned int  next_gain_1d     : 3;  /* bit[0-2]  : 最近一个时隙AGC期望控制增益。 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : 保留 */
        unsigned int  rssi_1d          : 12; /* bit[8-19] : 最近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。 */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: 保留 */
        unsigned int  curr_gain_1d     : 3;  /* bit[24-26]: 最近一个时隙AAGC档位上报。 */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: 保留 */
        unsigned int  agc_fast_flag_1d : 1;  /* bit[31]   : 最近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。 */
    } reg;
} GBBP_AAGC_GAIN1_CPU_UNION;
#define GBBP_AAGC_GAIN1_CPU_next_gain_1d_START      (0)
#define GBBP_AAGC_GAIN1_CPU_next_gain_1d_END        (2)
#define GBBP_AAGC_GAIN1_CPU_rssi_1d_START           (8)
#define GBBP_AAGC_GAIN1_CPU_rssi_1d_END             (19)
#define GBBP_AAGC_GAIN1_CPU_curr_gain_1d_START      (24)
#define GBBP_AAGC_GAIN1_CPU_curr_gain_1d_END        (26)
#define GBBP_AAGC_GAIN1_CPU_agc_fast_flag_1d_START  (31)
#define GBBP_AAGC_GAIN1_CPU_agc_fast_flag_1d_END    (31)


/*****************************************************************************
 结构名    : GBBP_AAGC_GAIN2_CPU_UNION
 结构说明  : AAGC_GAIN2_CPU 寄存器结构定义。地址偏移量:0x1464，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain2_cpu_reg;
    struct
    {
        unsigned int  next_gain_2d     : 3;  /* bit[0-2]  : 次近一个时隙AGC期望控制增益。 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : 保留 */
        unsigned int  rssi_2d          : 12; /* bit[8-19] : 次近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。 */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: 保留 */
        unsigned int  curr_gain_2d     : 3;  /* bit[24-26]: 次近一个时隙AAGC档位上报。 */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: 保留 */
        unsigned int  agc_fast_flag_2d : 1;  /* bit[31]   : 次近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。 */
    } reg;
} GBBP_AAGC_GAIN2_CPU_UNION;
#define GBBP_AAGC_GAIN2_CPU_next_gain_2d_START      (0)
#define GBBP_AAGC_GAIN2_CPU_next_gain_2d_END        (2)
#define GBBP_AAGC_GAIN2_CPU_rssi_2d_START           (8)
#define GBBP_AAGC_GAIN2_CPU_rssi_2d_END             (19)
#define GBBP_AAGC_GAIN2_CPU_curr_gain_2d_START      (24)
#define GBBP_AAGC_GAIN2_CPU_curr_gain_2d_END        (26)
#define GBBP_AAGC_GAIN2_CPU_agc_fast_flag_2d_START  (31)
#define GBBP_AAGC_GAIN2_CPU_agc_fast_flag_2d_END    (31)


/*****************************************************************************
 结构名    : GBBP_AAGC_GAIN3_CPU_UNION
 结构说明  : AAGC_GAIN3_CPU 寄存器结构定义。地址偏移量:0x1468，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain3_cpu_reg;
    struct
    {
        unsigned int  next_gain_3d     : 3;  /* bit[0-2]  : 次次近一个时隙AGC期望控制增益。 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : 保留 */
        unsigned int  rssi_3d          : 12; /* bit[8-19] : 次次近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。 */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: 保留 */
        unsigned int  curr_gain_3d     : 3;  /* bit[24-26]: 次次近一个时隙AAGC档位上报。 */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: 保留 */
        unsigned int  agc_fast_flag_3d : 1;  /* bit[31]   : 次次近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。 */
    } reg;
} GBBP_AAGC_GAIN3_CPU_UNION;
#define GBBP_AAGC_GAIN3_CPU_next_gain_3d_START      (0)
#define GBBP_AAGC_GAIN3_CPU_next_gain_3d_END        (2)
#define GBBP_AAGC_GAIN3_CPU_rssi_3d_START           (8)
#define GBBP_AAGC_GAIN3_CPU_rssi_3d_END             (19)
#define GBBP_AAGC_GAIN3_CPU_curr_gain_3d_START      (24)
#define GBBP_AAGC_GAIN3_CPU_curr_gain_3d_END        (26)
#define GBBP_AAGC_GAIN3_CPU_agc_fast_flag_3d_START  (31)
#define GBBP_AAGC_GAIN3_CPU_agc_fast_flag_3d_END    (31)


/*****************************************************************************
 结构名    : GBBP_AAGC_GAIN4_CPU_UNION
 结构说明  : AAGC_GAIN4_CPU 寄存器结构定义。地址偏移量:0x146C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain4_cpu_reg;
    struct
    {
        unsigned int  next_gain_4d     : 3;  /* bit[0-2]  : '第四近一个时隙AGC期望控制增益。 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : 保留 */
        unsigned int  rssi_4d          : 12; /* bit[8-19] : '第四近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。 */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: 保留 */
        unsigned int  curr_gain_4d     : 3;  /* bit[24-26]: '第四近一个时隙AAGC档位上报。 */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: 保留 */
        unsigned int  agc_fast_flag_4d : 1;  /* bit[31]   : 第四近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。 */
    } reg;
} GBBP_AAGC_GAIN4_CPU_UNION;
#define GBBP_AAGC_GAIN4_CPU_next_gain_4d_START      (0)
#define GBBP_AAGC_GAIN4_CPU_next_gain_4d_END        (2)
#define GBBP_AAGC_GAIN4_CPU_rssi_4d_START           (8)
#define GBBP_AAGC_GAIN4_CPU_rssi_4d_END             (19)
#define GBBP_AAGC_GAIN4_CPU_curr_gain_4d_START      (24)
#define GBBP_AAGC_GAIN4_CPU_curr_gain_4d_END        (26)
#define GBBP_AAGC_GAIN4_CPU_agc_fast_flag_4d_START  (31)
#define GBBP_AAGC_GAIN4_CPU_agc_fast_flag_4d_END    (31)


/*****************************************************************************
 结构名    : GBBP_ADDR_CPU_SOFT_RST_UNION
 结构说明  : ADDR_CPU_SOFT_RST 寄存器结构定义。地址偏移量:0x1350，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_soft_rst_reg;
    struct
    {
        unsigned int  cpu_gcipher_rst          : 1;  /* bit[0]    : 加解密模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gmod_rst             : 1;  /* bit[1]    : 上行调制模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gulcod_rst           : 1;  /* bit[2]    : 上行编码模块（除上行编码map模块）软复位信号，写1该模块复位。Bit2与bit3共同构成上行编码模块控制。 */
        unsigned int  cpu_gulcod_map_rst       : 1;  /* bit[3]    : 上行编码模块中map模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gagc_rst             : 1;  /* bit[4]    : 自动增益控制模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gaci_rst             : 1;  /* bit[5]    : 邻频检测模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gch_rst              : 1;  /* bit[6]    : 信道滤波模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gdldec_vtb_top_rst   : 1;  /* bit[7]    : 下行译码模块中viterbi模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。 */
        unsigned int  cpu_gdldec_int_dpc_rst   : 1;  /* bit[8]    : 下行译码模块中去交织/交织、去打孔/打孔模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。 */
        unsigned int  cpu_gdldec_valpp_ram_rst : 1;  /* bit[9]    : 下行译码模块中解调、译码软值存储/读取模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。 */
        unsigned int  cpu_gdldec_top_rst       : 1;  /* bit[10]   : 下行译码模块中除去bit7、bit8、bit9剩下的其余模块软复位信号，写1该模块复位。bit7与bit8、bit9、bit10共同构成下行译码模块控制。 */
        unsigned int  cpu_gdldem_srch_rst      : 1;  /* bit[11]   : 下行解调模块（包括搜索部分和所有解调相关部分）软复位信号，写1该模块复位。 */
        unsigned int  cpu_gmod_post_rst        : 1;  /* bit[12]   : 上行调制后处理模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gapc_rst             : 1;  /* bit[13]   : 上行APC模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gtc_rst              : 1;  /* bit[14]   : GTC模块软复位信号，写1该模块复位。
                                                                    注意：该复位信号配置后，将会导致专用线控和公共线控均复位至0,。 */
        unsigned int  cpu_gtc_timing_rst       : 1;  /* bit[15]   : GTC定时模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_gdldem_prepro_rst    : 1;  /* bit[16]   : 解调预处理模块软复位信号，写1该模块复位。 */
        unsigned int  cpu_dump_g_rst           : 1;  /* bit[17]   : 采数模块软复位信号，写1该模块复位。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} GBBP_ADDR_CPU_SOFT_RST_UNION;
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gcipher_rst_START           (0)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gcipher_rst_END             (0)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_rst_START              (1)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_rst_END                (1)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_rst_START            (2)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_rst_END              (2)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_map_rst_START        (3)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_map_rst_END          (3)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gagc_rst_START              (4)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gagc_rst_END                (4)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gaci_rst_START              (5)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gaci_rst_END                (5)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gch_rst_START               (6)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gch_rst_END                 (6)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_vtb_top_rst_START    (7)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_vtb_top_rst_END      (7)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_int_dpc_rst_START    (8)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_int_dpc_rst_END      (8)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_valpp_ram_rst_START  (9)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_valpp_ram_rst_END    (9)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_top_rst_START        (10)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_top_rst_END          (10)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_srch_rst_START       (11)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_srch_rst_END         (11)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_post_rst_START         (12)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_post_rst_END           (12)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gapc_rst_START              (13)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gapc_rst_END                (13)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_rst_START               (14)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_rst_END                 (14)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_timing_rst_START        (15)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_timing_rst_END          (15)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_prepro_rst_START     (16)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_prepro_rst_END       (16)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_dump_g_rst_START            (17)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_dump_g_rst_END              (17)


/*****************************************************************************
 结构名    : GBBP_ADDR_CPU_CLK_CTRL_UNION
 结构说明  : ADDR_CPU_CLK_CTRL 寄存器结构定义。地址偏移量:0x1354，初值:0x00017FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_clk_ctrl_reg;
    struct
    {
        unsigned int  cpu_gcipher_clk_ctrl          : 1;  /* bit[0]    : 加解密模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gmod_clk_ctrl             : 1;  /* bit[1]    : 上行调制模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gulcod_clk_ctrl           : 1;  /* bit[2]    : 上行编码模块（除了上行编码map模块）CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。bit2与bit3构成上行编码模块。 */
        unsigned int  cpu_gulcod_map_clk_ctrl       : 1;  /* bit[3]    : 上行编码map模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gagc_clk_ctrl             : 1;  /* bit[4]    : 自动增益控制模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gaci_clk_ctrl             : 1;  /* bit[5]    : 邻频检测模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gch_clk_ctrl              : 1;  /* bit[6]    : 信道滤波莫开CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gdldec_vtb_top_clk_ctrl   : 1;  /* bit[7]    : 下行译码模块中的viterbi模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。bit7、bit8、bit9、bit10构成下行译码模块。 */
        unsigned int  cpu_gdldec_int_dpc_clk_ctrl   : 1;  /* bit[8]    : 下行译码模块中的交织/去交织、打孔/去打孔模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gdldec_valpp_ram_clk_ctrl : 1;  /* bit[9]    : 下行译码模块中的解调、译码软值存储/读取模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gdldec_top_clk_ctrl       : 1;  /* bit[10]   : 下行译码模块除了bit7、bit8、bit9剩下模块的CPU控制时钟生效指示，1表示有时钟，0表示没有时钟。 */
        unsigned int  cpu_gdldem_srch_clk_ctrl      : 1;  /* bit[11]   : 下行解调模块（包括搜索部分和所有解调相关部分）CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gmod_post_clk_ctrl        : 1;  /* bit[12]   : 上行调制后处理模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gapc_clk_ctrl             : 1;  /* bit[13]   : 上行APC模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  cpu_gtc_clk_ctrl              : 1;  /* bit[14]   : GTC模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  reserved_0                    : 1;  /* bit[15]   : 保留 */
        unsigned int  cpu_gdldem_prepro_clk_ctrl    : 1;  /* bit[16]   : 解调预处理模块CPU控制时钟生效指示，1表示有时钟；0表示没有时钟。 */
        unsigned int  reserved_1                    : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_ADDR_CPU_CLK_CTRL_UNION;
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gcipher_clk_ctrl_START           (0)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gcipher_clk_ctrl_END             (0)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_clk_ctrl_START              (1)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_clk_ctrl_END                (1)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_clk_ctrl_START            (2)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_clk_ctrl_END              (2)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_map_clk_ctrl_START        (3)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_map_clk_ctrl_END          (3)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gagc_clk_ctrl_START              (4)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gagc_clk_ctrl_END                (4)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gaci_clk_ctrl_START              (5)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gaci_clk_ctrl_END                (5)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gch_clk_ctrl_START               (6)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gch_clk_ctrl_END                 (6)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_vtb_top_clk_ctrl_START    (7)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_vtb_top_clk_ctrl_END      (7)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_int_dpc_clk_ctrl_START    (8)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_int_dpc_clk_ctrl_END      (8)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_valpp_ram_clk_ctrl_START  (9)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_valpp_ram_clk_ctrl_END    (9)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_top_clk_ctrl_START        (10)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_top_clk_ctrl_END          (10)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_srch_clk_ctrl_START       (11)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_srch_clk_ctrl_END         (11)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_post_clk_ctrl_START         (12)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_post_clk_ctrl_END           (12)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gapc_clk_ctrl_START              (13)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gapc_clk_ctrl_END                (13)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gtc_clk_ctrl_START               (14)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gtc_clk_ctrl_END                 (14)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_prepro_clk_ctrl_START     (16)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_prepro_clk_ctrl_END       (16)


/*****************************************************************************
 结构名    : GBBP_ADDR_CPU_CLK_MODE_SEL_UNION
 结构说明  : ADDR_CPU_CLK_MODE_SEL 寄存器结构定义。地址偏移量:0x1358，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_clk_mode_sel_reg;
    struct
    {
        unsigned int  cpu_gcipher_ckg_mode_sel          : 1;  /* bit[0]    : 加解密模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gmod_ckg_mode_sel             : 1;  /* bit[1]    : 上行调制模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gulcod_ckg_mode_sel           : 1;  /* bit[2]    : 上行编码（除了map编码模块）模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。bit2与bit3构成上行编码模块。 */
        unsigned int  cpu_gulcod_map_ckg_mode_sel       : 1;  /* bit[3]    : 上行编码map编码模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gagc_ckg_mode_sel             : 1;  /* bit[4]    : 自动增益控制模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gaci_ckg_mode_sel             : 1;  /* bit[5]    : 邻频检测模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gch_ckg_mode_sel              : 1;  /* bit[6]    : 信道滤波模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gdldec_vtb_top_ckg_mode_sel   : 1;  /* bit[7]    : 下行译码模块中viterbi模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。bit7、bit8、bit9、bit10构成下行译码模块控制。 */
        unsigned int  cpu_gdldec_int_dpc_ckg_mode_sel   : 1;  /* bit[8]    : 下行译码模块中交织/去交织、打孔/去打孔模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gdldec_valpp_ram_ckg_mode_sel : 1;  /* bit[9]    : 下行译码模块中解调、译码软值存储/读取模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gdldec_top_ckg_mode_sel       : 1;  /* bit[10]   : 下行译码模块中除了bit7、bit8、bit9剩下的模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  cpu_gdldem_srch_ckg_mode_sel      : 1;  /* bit[11]   : 下行解调（包括搜索部分和解调所有相关部分）模块自动时钟门控orCPU时钟门控选择信号，1表示CPU控制门控；0表示自动时钟门控。 */
        unsigned int  reserved                          : 20; /* bit[12-31]: 保留 */
    } reg;
} GBBP_ADDR_CPU_CLK_MODE_SEL_UNION;
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gcipher_ckg_mode_sel_START           (0)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gcipher_ckg_mode_sel_END             (0)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gmod_ckg_mode_sel_START              (1)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gmod_ckg_mode_sel_END                (1)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_ckg_mode_sel_START            (2)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_ckg_mode_sel_END              (2)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_map_ckg_mode_sel_START        (3)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_map_ckg_mode_sel_END          (3)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gagc_ckg_mode_sel_START              (4)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gagc_ckg_mode_sel_END                (4)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gaci_ckg_mode_sel_START              (5)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gaci_ckg_mode_sel_END                (5)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gch_ckg_mode_sel_START               (6)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gch_ckg_mode_sel_END                 (6)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_vtb_top_ckg_mode_sel_START    (7)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_vtb_top_ckg_mode_sel_END      (7)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_int_dpc_ckg_mode_sel_START    (8)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_int_dpc_ckg_mode_sel_END      (8)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_valpp_ram_ckg_mode_sel_START  (9)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_valpp_ram_ckg_mode_sel_END    (9)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_top_ckg_mode_sel_START        (10)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_top_ckg_mode_sel_END          (10)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldem_srch_ckg_mode_sel_START       (11)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldem_srch_ckg_mode_sel_END         (11)


/*****************************************************************************
 结构名    : GBBP_ADDR_CPU_AUTO_CLK_BYPASS_UNION
 结构说明  : ADDR_CPU_AUTO_CLK_BYPASS 寄存器结构定义。地址偏移量:0x135C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_auto_clk_bypass_reg;
    struct
    {
        unsigned int  cpu_gcipher_ckg_bypass          : 1;  /* bit[0]    : 加解密模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gmod_ckg_bypass             : 1;  /* bit[1]    : 上行调制模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gulcod_ckg_bypass           : 1;  /* bit[2]    : 上行编码模块（除去map编码模块）时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。bit2与bit3构成上行编码模块。 */
        unsigned int  cpu_gulcod_map_ckg_bypass       : 1;  /* bit[3]    : 上行编码模块中map模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gagc_ckg_bypass             : 1;  /* bit[4]    : 自动增益控制模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gaci_ckg_bypass             : 1;  /* bit[5]    : 邻频检测模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gch_ckg_bypass              : 1;  /* bit[6]    : 信道滤波模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gdldec_vtb_top_ckg_bypass   : 1;  /* bit[7]    : 下行译码模块中viterbi模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。bit7、bit8、bit9、bit10构成下行译码模块。 */
        unsigned int  cpu_gdldec_int_dpc_ckg_bypass   : 1;  /* bit[8]    : 下行译码模块中交织/去角质、打孔/去打孔模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gdldec_valpp_ram_ckg_bypass : 1;  /* bit[9]    : 下行译码模块中解调、译码软值存储/读取模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gdldec_top_ckg_bypass       : 1;  /* bit[10]   : 下行译码模块中除了bit、bit8、bit9剩下的模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gdldem_srch_ckg_bypass      : 1;  /* bit[11]   : 下行解调（包括搜索部分和所有解调相关部分）模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gmod_post_ckg_bypass        : 1;  /* bit[12]   : 上行调制后处理模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gapc_ckg_bypass             : 1;  /* bit[13]   : 上行APC模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  cpu_gtc_ckg_bypass              : 1;  /* bit[14]   : GTC模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  reserved_0                      : 1;  /* bit[15]   : 保留 */
        unsigned int  cpu_gdldem_prepro_ckg_bypass    : 1;  /* bit[16]   : 下行解调预处理模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  dump_clkgate_bypass_g           : 1;  /* bit[17]   : 采数模块时钟门控功能bypass，1表示时钟常开；0表示使用自动时钟门控或者CPU控制时钟门控。 */
        unsigned int  reserved_1                      : 14; /* bit[18-31]: 保留 */
    } reg;
} GBBP_ADDR_CPU_AUTO_CLK_BYPASS_UNION;
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gcipher_ckg_bypass_START           (0)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gcipher_ckg_bypass_END             (0)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_ckg_bypass_START              (1)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_ckg_bypass_END                (1)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_ckg_bypass_START            (2)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_ckg_bypass_END              (2)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_map_ckg_bypass_START        (3)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_map_ckg_bypass_END          (3)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gagc_ckg_bypass_START              (4)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gagc_ckg_bypass_END                (4)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gaci_ckg_bypass_START              (5)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gaci_ckg_bypass_END                (5)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gch_ckg_bypass_START               (6)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gch_ckg_bypass_END                 (6)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_vtb_top_ckg_bypass_START    (7)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_vtb_top_ckg_bypass_END      (7)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_int_dpc_ckg_bypass_START    (8)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_int_dpc_ckg_bypass_END      (8)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_valpp_ram_ckg_bypass_START  (9)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_valpp_ram_ckg_bypass_END    (9)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_top_ckg_bypass_START        (10)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_top_ckg_bypass_END          (10)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_srch_ckg_bypass_START       (11)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_srch_ckg_bypass_END         (11)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_post_ckg_bypass_START         (12)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_post_ckg_bypass_END           (12)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gapc_ckg_bypass_START              (13)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gapc_ckg_bypass_END                (13)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gtc_ckg_bypass_START               (14)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gtc_ckg_bypass_END                 (14)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_prepro_ckg_bypass_START     (16)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_prepro_ckg_bypass_END       (16)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_dump_clkgate_bypass_g_START            (17)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_dump_clkgate_bypass_g_END              (17)


/*****************************************************************************
 结构名    : GBBP_CPU_GTC_CFG_UNION
 结构说明  : CPU_GTC_CFG 寄存器结构定义。地址偏移量:0x1360，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_cfg_reg;
    struct
    {
        unsigned int  gtc_page_switch_en_imi   : 1;  /* bit[0]   : 0：不切换指令RAM页，1：乒乓切换指令RAM页。复位后第一次配置时应该切换指令页。 */
        unsigned int  cpu_gtc_start_imi        : 1;  /* bit[1]   : 写1启动指令页执行，内部产生一个104M时钟脉冲，自清零，写0无意义。 */
        unsigned int  gtc_auto_run_imi         : 1;  /* bit[2]   : GTC指令在TDMA帧头处自动执行使能，默认为0。 */
        unsigned int  cpu_gtc_hold_page        : 1;  /* bit[3]   : 1表示允许修改正在执行的GTC指令页，需要修改时将其置1，修改完成后置0。 */
        unsigned int  gtc_pro_en_imi           : 1;  /* bit[4]   : GTC模块工作使能信号，先配置为该信号为高，然后再启动GTC。 */
        unsigned int  reserved_0               : 3;  /* bit[5-7] : 保留 */
        unsigned int  cpu_drx_test_mode_en_imi : 1;  /* bit[8]   : 1表示DRX测试模式使能，此时GTC时钟应不关闭，用于DRX唤醒后的定时维护情况的比对。正常使用下该信号应该被置0，测试用。 */
        unsigned int  reserved_1               : 23; /* bit[9-31]: 保留 */
    } reg;
} GBBP_CPU_GTC_CFG_UNION;
#define GBBP_CPU_GTC_CFG_gtc_page_switch_en_imi_START    (0)
#define GBBP_CPU_GTC_CFG_gtc_page_switch_en_imi_END      (0)
#define GBBP_CPU_GTC_CFG_cpu_gtc_start_imi_START         (1)
#define GBBP_CPU_GTC_CFG_cpu_gtc_start_imi_END           (1)
#define GBBP_CPU_GTC_CFG_gtc_auto_run_imi_START          (2)
#define GBBP_CPU_GTC_CFG_gtc_auto_run_imi_END            (2)
#define GBBP_CPU_GTC_CFG_cpu_gtc_hold_page_START         (3)
#define GBBP_CPU_GTC_CFG_cpu_gtc_hold_page_END           (3)
#define GBBP_CPU_GTC_CFG_gtc_pro_en_imi_START            (4)
#define GBBP_CPU_GTC_CFG_gtc_pro_en_imi_END              (4)
#define GBBP_CPU_GTC_CFG_cpu_drx_test_mode_en_imi_START  (8)
#define GBBP_CPU_GTC_CFG_cpu_drx_test_mode_en_imi_END    (8)


/*****************************************************************************
 结构名    : GBBP_GTC_STATE_RPT_UNION
 结构说明  : GTC_STATE_RPT 寄存器结构定义。地址偏移量:0x1374，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_state_rpt_reg;
    struct
    {
        unsigned int  gtc_idle           : 1;  /* bit[0]   : 1：表示GTC没有GTC指令执行；0表示GTC正在执行，测试用。 */
        unsigned int  gtc_wait           : 1;  /* bit[1]   : 1：表示GTC处于hold或者start状态，测试用。 */
        unsigned int  gtc_run            : 1;  /* bit[2]   : 1：表示GTC处于run运行状态，测试用。 */
        unsigned int  reserved_0         : 1;  /* bit[3]   : 保留 */
        unsigned int  gtc_page_switch_en : 1;  /* bit[4]   : GTC指令RAM乒乓切换使能上报，测试用。 */
        unsigned int  gtc_page_sel       : 1;  /* bit[5]   : 当前GTC指令RAM的乒乓标志上报，测试用。 */
        unsigned int  reserved_1         : 26; /* bit[6-31]: 保留 */
    } reg;
} GBBP_GTC_STATE_RPT_UNION;
#define GBBP_GTC_STATE_RPT_gtc_idle_START            (0)
#define GBBP_GTC_STATE_RPT_gtc_idle_END              (0)
#define GBBP_GTC_STATE_RPT_gtc_wait_START            (1)
#define GBBP_GTC_STATE_RPT_gtc_wait_END              (1)
#define GBBP_GTC_STATE_RPT_gtc_run_START             (2)
#define GBBP_GTC_STATE_RPT_gtc_run_END               (2)
#define GBBP_GTC_STATE_RPT_gtc_page_switch_en_START  (4)
#define GBBP_GTC_STATE_RPT_gtc_page_switch_en_END    (4)
#define GBBP_GTC_STATE_RPT_gtc_page_sel_START        (5)
#define GBBP_GTC_STATE_RPT_gtc_page_sel_END          (5)


/*****************************************************************************
 结构名    : GBBP_GTC_FRM_OFFSET_RPT_UNION
 结构说明  : GTC_FRM_OFFSET_RPT 寄存器结构定义。地址偏移量:0x137C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_frm_offset_rpt_reg;
    struct
    {
        unsigned int  gtc_frm_offset : 13; /* bit[0-12] : TDMA定时与TimeBase时间偏差，单位qb，若frm_offset为N，则TimeBase计数到N-1且GTC内部计数器frac_cnt计数到95时，下一拍TDMA帧号加1，测试用。 */
        unsigned int  reserved       : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_GTC_FRM_OFFSET_RPT_UNION;
#define GBBP_GTC_FRM_OFFSET_RPT_gtc_frm_offset_START  (0)
#define GBBP_GTC_FRM_OFFSET_RPT_gtc_frm_offset_END    (12)


/*****************************************************************************
 结构名    : GBBP_GTC_FRM_IT_OFFSET_RPT_UNION
 结构说明  : GTC_FRM_IT_OFFSET_RPT 寄存器结构定义。地址偏移量:0x1380，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_frm_it_offset_rpt_reg;
    struct
    {
        unsigned int  gtc_frm_it_offset : 13; /* bit[0-12] : 帧中断与TimeBase时间偏差，单位qb，测试用。 */
        unsigned int  reserved          : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_GTC_FRM_IT_OFFSET_RPT_UNION;
#define GBBP_GTC_FRM_IT_OFFSET_RPT_gtc_frm_it_offset_START  (0)
#define GBBP_GTC_FRM_IT_OFFSET_RPT_gtc_frm_it_offset_END    (12)


/*****************************************************************************
 结构名    : GBBP_CPU_GTC_T1_T2_T3_CNG_UNION
 结构说明  : CPU_GTC_T1_T2_T3_CNG 寄存器结构定义。地址偏移量:0x1388，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_t1_t2_t3_cng_reg;
    struct
    {
        unsigned int  cpu_gtc_t1_cnt : 11; /* bit[0-10] : 精简帧号维护机制中的T1初始值，该参数值与cpu_gtc_t1_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效，所以应配置为下一帧的帧号的T1值。 */
        unsigned int  reserved_0     : 5;  /* bit[11-15]: 保留 */
        unsigned int  cpu_gtc_t2_cnt : 5;  /* bit[16-20]: 精简帧号维护机制中的T2初始值，该参数值与cpu_gtc_t2_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效，所以应配置为下一帧的帧号的T1值。 */
        unsigned int  reserved_1     : 3;  /* bit[21-23]: 保留 */
        unsigned int  cpu_gtc_t3_cnt : 6;  /* bit[24-29]: 精简帧号维护机制中的T2初始值，该参数值与cpu_gtc_t1_cnt,cpu_gtc_t2_cnt,cpu_gtc_fn_low,cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效，所以应配置为下一帧的帧号的T1值。 */
        unsigned int  reserved_2     : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_GTC_T1_T2_T3_CNG_UNION;
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_START  (0)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_END    (10)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_START  (16)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_END    (20)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_START  (24)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_END    (29)


/*****************************************************************************
 结构名    : GBBP_GTC_T1_T2_T3_RPT_CPU_UNION
 结构说明  : GTC_T1_T2_T3_RPT_CPU 寄存器结构定义。地址偏移量:0x138C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_t1_t2_t3_rpt_cpu_reg;
    struct
    {
        unsigned int  gtc_t1_cnt : 11; /* bit[0-10] : GTC内部维护的T1计数器上报 */
        unsigned int  reserved_0 : 5;  /* bit[11-15]: 保留 */
        unsigned int  gtc_t2_cnt : 5;  /* bit[16-20]: GTC内部维护的T2计数器上报 */
        unsigned int  reserved_1 : 3;  /* bit[21-23]: 保留 */
        unsigned int  gtc_t3_cnt : 6;  /* bit[24-29]: GTC内部维护的T3计数器上报 */
        unsigned int  reserved_2 : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_GTC_T1_T2_T3_RPT_CPU_UNION;
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_START  (0)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_END    (10)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_START  (16)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_END    (20)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_START  (24)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_GTC_FRM_OFFSET_CFG_UNION
 结构说明  : CPU_GTC_FRM_OFFSET_CFG 寄存器结构定义。地址偏移量:0x1390，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_frm_offset_cfg_reg;
    struct
    {
        unsigned int  cpu_gtc_frm_offset           : 13; /* bit[0-12] : CPU配置的gtc_frm_offset参数。 */
        unsigned int  reserved_0                   : 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_gtc_frm_it_offset        : 13; /* bit[16-28]: CPU配置的gtc_frm_it_offset参数。 */
        unsigned int  reserved_1                   : 2;  /* bit[29-30]: 保留 */
        unsigned int  cpu_gtc_frm_offset_wr_en_imi : 1;  /* bit[31]   : cpu_gtc_frm_offset
                                                                        cpu_gtc_frm_it_offset
                                                                        立即生效指示信号，逻辑自清零。 */
    } reg;
} GBBP_CPU_GTC_FRM_OFFSET_CFG_UNION;
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_START            (0)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_END              (12)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_START         (16)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_END           (28)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_imi_START  (31)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_imi_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_GTC_FN_CNG_UNION
 结构说明  : CPU_GTC_FN_CNG 寄存器结构定义。地址偏移量:0x1394，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_fn_cng_reg;
    struct
    {
        unsigned int  cpu_gtc_fn_low       : 11; /* bit[0-10] : CPU配置TDMA帧号低位0~26*51-1循环计数，CPU配置后，在帧边界处生效，所以应配置为下一帧的帧号。 */
        unsigned int  reserved_0           : 5;  /* bit[11-15]: 保留 */
        unsigned int  cpu_gtc_fn_high      : 11; /* bit[16-26]: CPU配置TDMA帧号高位0~2047，低位计满后，高位加1。CPU配置后，在帧边界处生效，所以应配置为下一帧的帧号。 */
        unsigned int  reserved_1           : 4;  /* bit[27-30]: 保留 */
        unsigned int  cpu_gtc_fn_wr_en_imi : 1;  /* bit[31]   : 帧号初始化信号，1有效，逻辑自清零。当T1、T2、T3、fn_low、fn_high、都写入后该信号才可以置1。 */
    } reg;
} GBBP_CPU_GTC_FN_CNG_UNION;
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_low_START        (0)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_low_END          (10)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_high_START       (16)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_high_END         (26)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_wr_en_imi_START  (31)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_wr_en_imi_END    (31)


/*****************************************************************************
 结构名    : GBBP_GTC_FN_RPT_UNION
 结构说明  : GTC_FN_RPT 寄存器结构定义。地址偏移量:0x1398，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_fn_rpt_reg;
    struct
    {
        unsigned int  gtc_fn_low  : 11; /* bit[0-10] : GTC此时帧号低位。 */
        unsigned int  reserved_0  : 5;  /* bit[11-15]: 保留 */
        unsigned int  gtc_fn_high : 11; /* bit[16-26]: GTC此时帧号高位。 */
        unsigned int  reserved_1  : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_GTC_FN_RPT_UNION;
#define GBBP_GTC_FN_RPT_gtc_fn_low_START   (0)
#define GBBP_GTC_FN_RPT_gtc_fn_low_END     (10)
#define GBBP_GTC_FN_RPT_gtc_fn_high_START  (16)
#define GBBP_GTC_FN_RPT_gtc_fn_high_END    (26)


/*****************************************************************************
 结构名    : GBBP_GTC_QB_RPT_UNION
 结构说明  : GTC_QB_RPT 寄存器结构定义。地址偏移量:0x139C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_qb_rpt_reg;
    struct
    {
        unsigned int  gtc_tdma_qb_imi  : 13; /* bit[0-12] : 当前时刻TDMA的QB计数值，0~4999。 */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: 保留 */
        unsigned int  gtc_timebase_imi : 13; /* bit[16-28]: 绝对时标QB上报，范围：0~4999，对应一帧的长度，该值只与复位时刻有关，测试用。 */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_GTC_QB_RPT_UNION;
#define GBBP_GTC_QB_RPT_gtc_tdma_qb_imi_START   (0)
#define GBBP_GTC_QB_RPT_gtc_tdma_qb_imi_END     (12)
#define GBBP_GTC_QB_RPT_gtc_timebase_imi_START  (16)
#define GBBP_GTC_QB_RPT_gtc_timebase_imi_END    (28)


/*****************************************************************************
 结构名    : GBBP_TIMEBASE_RPT_UNION
 结构说明  : TIMEBASE_RPT 寄存器结构定义。地址偏移量:0x13A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      timebase_rpt_reg;
    struct
    {
        unsigned int  gtc_timebase_imi    : 13; /* bit[0-12] : 绝对时标QB上报，范围：0~4999，对应一帧的长度，该值只与复位时刻有关，测试用。 */
        unsigned int  reserved_0          : 3;  /* bit[13-15]: 保留 */
        unsigned int  gtc_timebase_fn_low : 11; /* bit[16-26]: 绝对时标帧号上报，该值变化时刻在gtc_timebase_qb为4999处，计数范围0~26*51-1，测试用。 */
        unsigned int  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_TIMEBASE_RPT_UNION;
#define GBBP_TIMEBASE_RPT_gtc_timebase_imi_START     (0)
#define GBBP_TIMEBASE_RPT_gtc_timebase_imi_END       (12)
#define GBBP_TIMEBASE_RPT_gtc_timebase_fn_low_START  (16)
#define GBBP_TIMEBASE_RPT_gtc_timebase_fn_low_END    (26)


/*****************************************************************************
 结构名    : GBBP_CPU_BLER_BER_CLR_UNION
 结构说明  : CPU_BLER_BER_CLR 寄存器结构定义。地址偏移量:0x1300，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_bler_ber_clr_reg;
    struct
    {
        unsigned int  cpu_bler_clr_imi : 1;  /* bit[0]   : 接收质量上报BLER清零信号，脉冲信号，cpu置1逻辑自清零 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : 保留 */
        unsigned int  cpu_ber_clr_imi  : 1;  /* bit[4]   : 接收质量上报BER清零信号，脉冲信号，cpu置1，逻辑自清零 */
        unsigned int  reserved_1       : 3;  /* bit[5-7] : 保留 */
        unsigned int  cpu_bler_mode    : 1;  /* bit[8]   : BLER统计模式控制，0表示每次译码CRC结果都参与BLER统计（即是HEAD，DATA都统计）
                                                           1表示只统计每次DATA的译码CRC结果BLER值 */
        unsigned int  reserved_2       : 23; /* bit[9-31]: 保留 */
    } reg;
} GBBP_CPU_BLER_BER_CLR_UNION;
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_clr_imi_START  (0)
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_clr_imi_END    (0)
#define GBBP_CPU_BLER_BER_CLR_cpu_ber_clr_imi_START   (4)
#define GBBP_CPU_BLER_BER_CLR_cpu_ber_clr_imi_END     (4)
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_mode_START     (8)
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_mode_END       (8)


/*****************************************************************************
 结构名    : GBBP_CPU_AMR_CB_INDEX_UNION
 结构说明  : CPU_AMR_CB_INDEX 寄存器结构定义。地址偏移量:0x1304，初值:0x0F0E0D0C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_cb_index_reg;
    struct
    {
        unsigned int  cpu_amr0_cb_index : 7;  /* bit[0-6]  : AMR语音激活集合内codec_mode=00对应的AMR语音帧cb_index */
        unsigned int  reserved_0        : 1;  /* bit[7]    : 保留 */
        unsigned int  cpu_amr1_cb_index : 7;  /* bit[8-14] : AMR语音激活集合内codec_mode=01对应的AMR语音帧cb_index */
        unsigned int  reserved_1        : 1;  /* bit[15]   : 保留 */
        unsigned int  cpu_amr2_cb_index : 7;  /* bit[16-22]: AMR语音激活集合内codec_mode=10对应的AMR语音帧cb_index */
        unsigned int  reserved_2        : 1;  /* bit[23]   : 保留 */
        unsigned int  cpu_amr3_cb_index : 7;  /* bit[24-30]: AMR语音激活集合内codec_mode=11对应的AMR语音帧cb_index */
        unsigned int  reserved_3        : 1;  /* bit[31]   : 保留 */
    } reg;
} GBBP_CPU_AMR_CB_INDEX_UNION;
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr0_cb_index_START  (0)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr0_cb_index_END    (6)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr1_cb_index_START  (8)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr1_cb_index_END    (14)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr2_cb_index_START  (16)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr2_cb_index_END    (22)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr3_cb_index_START  (24)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr3_cb_index_END    (30)


/*****************************************************************************
 结构名    : GBBP_CPU_AMR_ACTIVE_SET_NUM_UNION
 结构说明  : CPU_AMR_ACTIVE_SET_NUM 寄存器结构定义。地址偏移量:0x1308，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_active_set_num_reg;
    struct
    {
        unsigned int  cpu_amr_active_set_num            : 2;  /* bit[0-1]  : AMR语音激活集内有效语音帧类型个数
                                                                             0 表示1个
                                                                             1 表示2个
                                                                             2 表示3个
                                                                             3 表示4个
                                                                             （当业务类型为GMSK WBAMR时，配置范围为0～2） */
        unsigned int  reserved_0                        : 2;  /* bit[2-3]  : 保留 */
        unsigned int  cpu_speech_bfi_thres              : 4;  /* bit[4-7]  : 语音帧BFI相关译码判决门限，配置范围0～8 */
        unsigned int  reserved_1                        : 8;  /* bit[8-15] : 保留 */
        unsigned int  cpu_amr_active_set_num_upflag_imi : 1;  /* bit[16]   : 当AMR激活集个数发生变化时，需要配置该信号为1 */
        unsigned int  reserved_2                        : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_CPU_AMR_ACTIVE_SET_NUM_UNION;
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_START             (0)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_END               (1)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_speech_bfi_thres_START               (4)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_speech_bfi_thres_END                 (7)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_upflag_imi_START  (16)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_upflag_imi_END    (16)


/*****************************************************************************
 结构名    : GBBP_DB_BLER_ERR_RPT_UNION
 结构说明  : DB_BLER_ERR_RPT 寄存器结构定义。地址偏移量:0x1484，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      db_bler_err_rpt_reg;
    struct
    {
        unsigned int  rxqual_db_bler_err : 16; /* bit[0-15] : DummyBurst导致误码计数上报 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} GBBP_DB_BLER_ERR_RPT_UNION;
#define GBBP_DB_BLER_ERR_RPT_rxqual_db_bler_err_START  (0)
#define GBBP_DB_BLER_ERR_RPT_rxqual_db_bler_err_END    (15)


/*****************************************************************************
 结构名    : GBBP_SB_BLER_ERR_RPT_UNION
 结构说明  : SB_BLER_ERR_RPT 寄存器结构定义。地址偏移量:0x1488，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_bler_err_rpt_reg;
    struct
    {
        unsigned int  rxqual_sb_bler_err : 8;  /* bit[0-7] : SB误码计数上报 */
        unsigned int  reserved           : 24; /* bit[8-31]: 保留 */
    } reg;
} GBBP_SB_BLER_ERR_RPT_UNION;
#define GBBP_SB_BLER_ERR_RPT_rxqual_sb_bler_err_START  (0)
#define GBBP_SB_BLER_ERR_RPT_rxqual_sb_bler_err_END    (7)


/*****************************************************************************
 结构名    : GBBP_DATA_BLER_ERR_RPT_UNION
 结构说明  : DATA_BLER_ERR_RPT 寄存器结构定义。地址偏移量:0x148C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      data_bler_err_rpt_reg;
    struct
    {
        unsigned int  rxqual_data_bler_err : 16; /* bit[0-15] : EDGE业务DATA误码计数上报 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} GBBP_DATA_BLER_ERR_RPT_UNION;
#define GBBP_DATA_BLER_ERR_RPT_rxqual_data_bler_err_START  (0)
#define GBBP_DATA_BLER_ERR_RPT_rxqual_data_bler_err_END    (15)


/*****************************************************************************
 结构名    : GBBP_CODEC_PARA_REG1_UNION
 结构说明  : CODEC_PARA_REG1 寄存器结构定义。地址偏移量:0x1320，初值:0x10E40000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg1_reg;
    struct
    {
        unsigned int  conv_rate        : 4;  /* bit[0-3]  : 卷积编码率指示，
                                                            2=1/2,3=1/3,4=1/4……6=1/6，测试用 */
        unsigned int  conv_depth       : 1;  /* bit[4]    : 卷积编码记忆深度，0: 4;  1: 6，测试用 */
        unsigned int  vtb_codec_len    : 10; /* bit[5-14] : 码块译码后数据长度，即编码前数据长度，测试用 */
        unsigned int  vtb_cb_coded_len : 11; /* bit[15-25]: 码块编码后数据长度，测试用 */
        unsigned int  codec_type       : 2;  /* bit[26-27]: 码块译码类型，
                                                            00从0状态开始，到0状态结束；
                                                            01从0状态开始，到非0状态结束；
                                                            10从非0状态开始，到0状态结束；
                                                            11非0状态开始，到非0状态结束；
                                                            测试用 */
        unsigned int  punc_means       : 1;  /* bit[28]   : 打孔方式选择,0表示打孔，1表示不打孔，测试用 */
        unsigned int  vtb_codec_en     : 1;  /* bit[29]   : 1表示有卷积编码过程，测试用 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CODEC_PARA_REG1_UNION;
#define GBBP_CODEC_PARA_REG1_conv_rate_START         (0)
#define GBBP_CODEC_PARA_REG1_conv_rate_END           (3)
#define GBBP_CODEC_PARA_REG1_conv_depth_START        (4)
#define GBBP_CODEC_PARA_REG1_conv_depth_END          (4)
#define GBBP_CODEC_PARA_REG1_vtb_codec_len_START     (5)
#define GBBP_CODEC_PARA_REG1_vtb_codec_len_END       (14)
#define GBBP_CODEC_PARA_REG1_vtb_cb_coded_len_START  (15)
#define GBBP_CODEC_PARA_REG1_vtb_cb_coded_len_END    (25)
#define GBBP_CODEC_PARA_REG1_codec_type_START        (26)
#define GBBP_CODEC_PARA_REG1_codec_type_END          (27)
#define GBBP_CODEC_PARA_REG1_punc_means_START        (28)
#define GBBP_CODEC_PARA_REG1_punc_means_END          (28)
#define GBBP_CODEC_PARA_REG1_vtb_codec_en_START      (29)
#define GBBP_CODEC_PARA_REG1_vtb_codec_en_END        (29)


/*****************************************************************************
 结构名    : GBBP_CODEC_PARA_REG2_UNION
 结构说明  : CODEC_PARA_REG2 寄存器结构定义。地址偏移量:0x1324，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg2_reg;
    struct
    {
        unsigned int  g0_poly         : 7;  /* bit[0-6]  : 编码生成多项式0，测试用 */
        unsigned int  g1_poly         : 7;  /* bit[7-13] : 编码生成多项式1，测试用 */
        unsigned int  g2_poly         : 7;  /* bit[14-20]: 编码生成多项式2，测试用 */
        unsigned int  g3_poly         : 7;  /* bit[21-27]: 编码生成多项式3，测试用 */
        unsigned int  crc_handle_flag : 2;  /* bit[28-29]: CRC预处理业务标志信号
                                                           00 无预处理
                                                           01 重排序
                                                           10 USF预处理_1
                                                           11 USF预处理_2
                                                           ，测试用 */
        unsigned int  reserved        : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CODEC_PARA_REG2_UNION;
#define GBBP_CODEC_PARA_REG2_g0_poly_START          (0)
#define GBBP_CODEC_PARA_REG2_g0_poly_END            (6)
#define GBBP_CODEC_PARA_REG2_g1_poly_START          (7)
#define GBBP_CODEC_PARA_REG2_g1_poly_END            (13)
#define GBBP_CODEC_PARA_REG2_g2_poly_START          (14)
#define GBBP_CODEC_PARA_REG2_g2_poly_END            (20)
#define GBBP_CODEC_PARA_REG2_g3_poly_START          (21)
#define GBBP_CODEC_PARA_REG2_g3_poly_END            (27)
#define GBBP_CODEC_PARA_REG2_crc_handle_flag_START  (28)
#define GBBP_CODEC_PARA_REG2_crc_handle_flag_END    (29)


/*****************************************************************************
 结构名    : GBBP_CODEC_PARA_REG3_UNION
 结构说明  : CODEC_PARA_REG3 寄存器结构定义。地址偏移量:0x1328，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg3_reg;
    struct
    {
        unsigned int  g4_poly            : 7;  /* bit[0-6]  : 编码生成多项式4，测试用 */
        unsigned int  g5_poly            : 7;  /* bit[7-13] : 编码生成多项式5，测试用 */
        unsigned int  denominator_g_poly : 7;  /* bit[14-20]: 分母位置的编码生成多项式，测试用 */
        unsigned int  punc_rom_index     : 7;  /* bit[21-27]: 打孔图样的打孔表序号，测试用 */
        unsigned int  g_comb_index       : 4;  /* bit[28-31]: 编码生成多项式组合序号，测试用 */
    } reg;
} GBBP_CODEC_PARA_REG3_UNION;
#define GBBP_CODEC_PARA_REG3_g4_poly_START             (0)
#define GBBP_CODEC_PARA_REG3_g4_poly_END               (6)
#define GBBP_CODEC_PARA_REG3_g5_poly_START             (7)
#define GBBP_CODEC_PARA_REG3_g5_poly_END               (13)
#define GBBP_CODEC_PARA_REG3_denominator_g_poly_START  (14)
#define GBBP_CODEC_PARA_REG3_denominator_g_poly_END    (20)
#define GBBP_CODEC_PARA_REG3_punc_rom_index_START      (21)
#define GBBP_CODEC_PARA_REG3_punc_rom_index_END        (27)
#define GBBP_CODEC_PARA_REG3_g_comb_index_START        (28)
#define GBBP_CODEC_PARA_REG3_g_comb_index_END          (31)


/*****************************************************************************
 结构名    : GBBP_CODEC_PARA_REG4_UNION
 结构说明  : CODEC_PARA_REG4 寄存器结构定义。地址偏移量:0x132C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg4_reg;
    struct
    {
        unsigned int  interleaving_formula_index : 5;  /* bit[0-4]  : 交织公式序号，测试用 */
        unsigned int  vtb_k_start_pos            : 11; /* bit[5-15] : 卷积码块在交织中起始bit序号 */
        unsigned int  vtb_k_end_pos              : 11; /* bit[16-26]: 卷积码块在交织中结束bit序号，测试用 */
        unsigned int  interleave_en              : 1;  /* bit[27]   : 1表示有交织过程，测试用 */
        unsigned int  crc_exist_flag             : 1;  /* bit[28]   : 1表示存在CRC校验过程，测试用 */
        unsigned int  reserved                   : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_CODEC_PARA_REG4_UNION;
#define GBBP_CODEC_PARA_REG4_interleaving_formula_index_START  (0)
#define GBBP_CODEC_PARA_REG4_interleaving_formula_index_END    (4)
#define GBBP_CODEC_PARA_REG4_vtb_k_start_pos_START             (5)
#define GBBP_CODEC_PARA_REG4_vtb_k_start_pos_END               (15)
#define GBBP_CODEC_PARA_REG4_vtb_k_end_pos_START               (16)
#define GBBP_CODEC_PARA_REG4_vtb_k_end_pos_END                 (26)
#define GBBP_CODEC_PARA_REG4_interleave_en_START               (27)
#define GBBP_CODEC_PARA_REG4_interleave_en_END                 (27)
#define GBBP_CODEC_PARA_REG4_crc_exist_flag_START              (28)
#define GBBP_CODEC_PARA_REG4_crc_exist_flag_END                (28)


/*****************************************************************************
 结构名    : GBBP_CODEC_PARA_REG5_UNION
 结构说明  : CODEC_PARA_REG5 寄存器结构定义。地址偏移量:0x1330，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg5_reg;
    struct
    {
        unsigned int  infom_end_pos         : 10; /* bit[0-9]  : 信息bit结束位置，测试用 */
        unsigned int  reserved_0            : 1;  /* bit[10]   : 保留 */
        unsigned int  class2_bit_exist_flag : 1;  /* bit[11]   : 1表示存在CLASS2 bit，测试用 */
        unsigned int  class2_bit_start_pos  : 9;  /* bit[12-20]: CLASS2 bit起始位置，测试用 */
        unsigned int  trch_sort             : 2;  /* bit[21-22]: 编码业务大类指示
                                                                 00 非AFS和AHS的cs业务
                                                                 01 AFS或者AHS业务
                                                                 10 GPRS业务
                                                                 11 EGPRS业务
                                                                 测试用 */
        unsigned int  zero_fill_type        : 3;  /* bit[23-25]: 尾比特补零处理模式：
                                                                 bit25: 1表示存在填零处理
                                                                        0表示不存在填零处理
                                                                 bit24～bit23：
                                                                 00表示填4个零
                                                                 01表示填6个零
                                                                 10表示填8个零
                                                                 11表示填32个零
                                                                 测试用 */
        unsigned int  crc_type              : 4;  /* bit[26-29]: CRC长度指示，测试用 */
        unsigned int  reserved_1            : 1;  /* bit[30]   : 保留 */
        unsigned int  tail_exist_flag       : 1;  /* bit[31]   : 1表示存在尾比特填充操作
                                                                 0表示不存在
                                                                 ，测试用 */
    } reg;
} GBBP_CODEC_PARA_REG5_UNION;
#define GBBP_CODEC_PARA_REG5_infom_end_pos_START          (0)
#define GBBP_CODEC_PARA_REG5_infom_end_pos_END            (9)
#define GBBP_CODEC_PARA_REG5_class2_bit_exist_flag_START  (11)
#define GBBP_CODEC_PARA_REG5_class2_bit_exist_flag_END    (11)
#define GBBP_CODEC_PARA_REG5_class2_bit_start_pos_START   (12)
#define GBBP_CODEC_PARA_REG5_class2_bit_start_pos_END     (20)
#define GBBP_CODEC_PARA_REG5_trch_sort_START              (21)
#define GBBP_CODEC_PARA_REG5_trch_sort_END                (22)
#define GBBP_CODEC_PARA_REG5_zero_fill_type_START         (23)
#define GBBP_CODEC_PARA_REG5_zero_fill_type_END           (25)
#define GBBP_CODEC_PARA_REG5_crc_type_START               (26)
#define GBBP_CODEC_PARA_REG5_crc_type_END                 (29)
#define GBBP_CODEC_PARA_REG5_tail_exist_flag_START        (31)
#define GBBP_CODEC_PARA_REG5_tail_exist_flag_END          (31)


/*****************************************************************************
 结构名    : GBBP_CODEC_PARA_REG6_UNION
 结构说明  : CODEC_PARA_REG6 寄存器结构定义。地址偏移量:0x1334，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg6_reg;
    struct
    {
        unsigned int  punc_rom_base_addr : 12; /* bit[0-11] : 码块打孔信息存放起始位置，测试用 */
        unsigned int  cb_index           : 7;  /* bit[12-18]: 码块序号，测试用 */
        unsigned int  reserved_0         : 1;  /* bit[19]   : 保留 */
        unsigned int  dcu_usf_bit        : 3;  /* bit[20-22]: PS域USF bit 上报，测试用 */
        unsigned int  reserved_1         : 1;  /* bit[23]   : 保留 */
        unsigned int  cps_bit            : 5;  /* bit[24-28]: PS域的HEADER CPSbit 上报，测试用 */
        unsigned int  reserved_2         : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_CODEC_PARA_REG6_UNION;
#define GBBP_CODEC_PARA_REG6_punc_rom_base_addr_START  (0)
#define GBBP_CODEC_PARA_REG6_punc_rom_base_addr_END    (11)
#define GBBP_CODEC_PARA_REG6_cb_index_START            (12)
#define GBBP_CODEC_PARA_REG6_cb_index_END              (18)
#define GBBP_CODEC_PARA_REG6_dcu_usf_bit_START         (20)
#define GBBP_CODEC_PARA_REG6_dcu_usf_bit_END           (22)
#define GBBP_CODEC_PARA_REG6_cps_bit_START             (24)
#define GBBP_CODEC_PARA_REG6_cps_bit_END               (28)


/*****************************************************************************
 结构名    : GBBP_CODEC_PARA_REG7_UNION
 结构说明  : CODEC_PARA_REG7 寄存器结构定义。地址偏移量:0x123C，初值:0x003F000F，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg7_reg;
    struct
    {
        unsigned int  dcu_ps_codec_type  : 4;  /* bit[0-3]  : 最近的PS业务上报 */
        unsigned int  reserved_0         : 12; /* bit[4-15] : 保留 */
        unsigned int  dcu_amr_frame_type : 6;  /* bit[16-21]: 最近的AMR业务上报 */
        unsigned int  reserved_1         : 10; /* bit[22-31]: 保留 */
    } reg;
} GBBP_CODEC_PARA_REG7_UNION;
#define GBBP_CODEC_PARA_REG7_dcu_ps_codec_type_START   (0)
#define GBBP_CODEC_PARA_REG7_dcu_ps_codec_type_END     (3)
#define GBBP_CODEC_PARA_REG7_dcu_amr_frame_type_START  (16)
#define GBBP_CODEC_PARA_REG7_dcu_amr_frame_type_END    (21)


/*****************************************************************************
 结构名    : GBBP_DEC_STATE_RPT1_UNION
 结构说明  : DEC_STATE_RPT1 寄存器结构定义。地址偏移量:0x1338，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dec_state_rpt1_reg;
    struct
    {
        unsigned int  trch_sort_state_cpu : 4;  /* bit[0-3]  : 译码业务大类判断状态机状态，测试用 */
        unsigned int  kn_pro_state_cpu    : 4;  /* bit[4-7]  : 业务类型已知子状态机状态，测试用 */
        unsigned int  harq_pro_state_cpu  : 3;  /* bit[8-10] : HARQ合并译码子状态机状态，测试用 */
        unsigned int  reserved_0          : 1;  /* bit[11]   : 保留 */
        unsigned int  ukn_afs_state_cpu   : 5;  /* bit[12-16]: AFS业务子状态机状态，测试用 */
        unsigned int  reserved_1          : 3;  /* bit[17-19]: 保留 */
        unsigned int  ukn_ahs_state_cpu   : 6;  /* bit[20-25]: AHS业务子状态机状态，测试用 */
        unsigned int  reserved_2          : 1;  /* bit[26]   : 保留 */
        unsigned int  ukn_ps_state_cpu    : 5;  /* bit[27-31]: PS业务子状态机状态，测试用 */
    } reg;
} GBBP_DEC_STATE_RPT1_UNION;
#define GBBP_DEC_STATE_RPT1_trch_sort_state_cpu_START  (0)
#define GBBP_DEC_STATE_RPT1_trch_sort_state_cpu_END    (3)
#define GBBP_DEC_STATE_RPT1_kn_pro_state_cpu_START     (4)
#define GBBP_DEC_STATE_RPT1_kn_pro_state_cpu_END       (7)
#define GBBP_DEC_STATE_RPT1_harq_pro_state_cpu_START   (8)
#define GBBP_DEC_STATE_RPT1_harq_pro_state_cpu_END     (10)
#define GBBP_DEC_STATE_RPT1_ukn_afs_state_cpu_START    (12)
#define GBBP_DEC_STATE_RPT1_ukn_afs_state_cpu_END      (16)
#define GBBP_DEC_STATE_RPT1_ukn_ahs_state_cpu_START    (20)
#define GBBP_DEC_STATE_RPT1_ukn_ahs_state_cpu_END      (25)
#define GBBP_DEC_STATE_RPT1_ukn_ps_state_cpu_START     (27)
#define GBBP_DEC_STATE_RPT1_ukn_ps_state_cpu_END       (31)


/*****************************************************************************
 结构名    : GBBP_DEC_STATE_RPT2_UNION
 结构说明  : DEC_STATE_RPT2 寄存器结构定义。地址偏移量:0x133C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dec_state_rpt2_reg;
    struct
    {
        unsigned int  reserved_0           : 8;  /* bit[0-7]  : 保留 */
        unsigned int  vtb_state_cpu        : 4;  /* bit[8-11] : VTB译码子状态机状态，测试用 */
        unsigned int  corr_state_cpu       : 2;  /* bit[12-13]: 相关译码子状态机状态，测试用 */
        unsigned int  reserved_1           : 2;  /* bit[14-15]: 保留 */
        unsigned int  interleave_state_cpu : 4;  /* bit[16-19]: 交织模块工作状态，测试用 */
        unsigned int  depunc_state_cpu     : 3;  /* bit[20-22]: 去打孔模块工作状态，测试用 */
        unsigned int  reserved_2           : 1;  /* bit[23]   : 保留 */
        unsigned int  ccu_state_cpu        : 4;  /* bit[24-27]: CCU工作状态，测试用 */
        unsigned int  reserved_3           : 3;  /* bit[28-30]: 保留 */
        unsigned int  dec_busy_cpu         : 1;  /* bit[31]   : 下行译码忙状态，测试用 */
    } reg;
} GBBP_DEC_STATE_RPT2_UNION;
#define GBBP_DEC_STATE_RPT2_vtb_state_cpu_START         (8)
#define GBBP_DEC_STATE_RPT2_vtb_state_cpu_END           (11)
#define GBBP_DEC_STATE_RPT2_corr_state_cpu_START        (12)
#define GBBP_DEC_STATE_RPT2_corr_state_cpu_END          (13)
#define GBBP_DEC_STATE_RPT2_interleave_state_cpu_START  (16)
#define GBBP_DEC_STATE_RPT2_interleave_state_cpu_END    (19)
#define GBBP_DEC_STATE_RPT2_depunc_state_cpu_START      (20)
#define GBBP_DEC_STATE_RPT2_depunc_state_cpu_END        (22)
#define GBBP_DEC_STATE_RPT2_ccu_state_cpu_START         (24)
#define GBBP_DEC_STATE_RPT2_ccu_state_cpu_END           (27)
#define GBBP_DEC_STATE_RPT2_dec_busy_cpu_START          (31)
#define GBBP_DEC_STATE_RPT2_dec_busy_cpu_END            (31)


/*****************************************************************************
 结构名    : GBBP_DEC_INT_TOTAL_UNION
 结构说明  : DEC_INT_TOTAL 寄存器结构定义。地址偏移量:0x1348，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dec_int_total_reg;
    struct
    {
        unsigned int  dec_int_cnt : 4;  /* bit[0-3]  : 译码中断次数计数器上报 */
        unsigned int  reserved_0  : 12; /* bit[4-15] : 保留 */
        unsigned int  dec_cnt     : 4;  /* bit[16-19]: 译码启动次数计数器上报 */
        unsigned int  reserved_1  : 12; /* bit[20-31]: 保留 */
    } reg;
} GBBP_DEC_INT_TOTAL_UNION;
#define GBBP_DEC_INT_TOTAL_dec_int_cnt_START  (0)
#define GBBP_DEC_INT_TOTAL_dec_int_cnt_END    (3)
#define GBBP_DEC_INT_TOTAL_dec_cnt_START      (16)
#define GBBP_DEC_INT_TOTAL_dec_cnt_END        (19)


/*****************************************************************************
 结构名    : GBBP_BFI_RSQ_METRIC_RPT_UNION
 结构说明  : BFI_RSQ_METRIC_RPT 寄存器结构定义。地址偏移量:0x134C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bfi_rsq_metric_rpt_reg;
    struct
    {
        unsigned int  amr_rsq_metric         : 8;  /* bit[0-7]  : CS语音的RSQ_METRIC上报 */
        unsigned int  reserved_0             : 8;  /* bit[8-15] : 保留 */
        unsigned int  amr_pber               : 7;  /* bit[16-22]: CS语音的PBER上报 */
        unsigned int  reserved_1             : 8;  /* bit[23-30]: 保留 */
        unsigned int  speech_bfi_corr_result : 1;  /* bit[31]   : 1标识是语音帧相关判决为BFI；
                                                                  0标识是语音帧相关判决不是BFI */
    } reg;
} GBBP_BFI_RSQ_METRIC_RPT_UNION;
#define GBBP_BFI_RSQ_METRIC_RPT_amr_rsq_metric_START          (0)
#define GBBP_BFI_RSQ_METRIC_RPT_amr_rsq_metric_END            (7)
#define GBBP_BFI_RSQ_METRIC_RPT_amr_pber_START                (16)
#define GBBP_BFI_RSQ_METRIC_RPT_amr_pber_END                  (22)
#define GBBP_BFI_RSQ_METRIC_RPT_speech_bfi_corr_result_START  (31)
#define GBBP_BFI_RSQ_METRIC_RPT_speech_bfi_corr_result_END    (31)


/*****************************************************************************
 结构名    : GBBP_UL_CODE_STATE_RPT_UNION
 结构说明  : UL_CODE_STATE_RPT 寄存器结构定义。地址偏移量:0x13B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ul_code_state_rpt_reg;
    struct
    {
        unsigned int  ul_code_state : 2;  /* bit[0-1] : 00表示IDLE（空闲状态）                                     01表示INIT（初始化状态）                                     10表示CODE（编码状态）                                     11表示INTE（交织状态）
                                                        测试用 */
        unsigned int  reserved_0    : 2;  /* bit[2-3] : 保留 */
        unsigned int  ul_crc_state  : 2;  /* bit[4-5] : 00表示IDLE（空闲状态）                                     01表示RECV（接收状态）                                     10表示CHECK（校验状态）                                     11无效状态
                                                        测试用 */
        unsigned int  reserved_1    : 26; /* bit[6-31]: 保留 */
    } reg;
} GBBP_UL_CODE_STATE_RPT_UNION;
#define GBBP_UL_CODE_STATE_RPT_ul_code_state_START  (0)
#define GBBP_UL_CODE_STATE_RPT_ul_code_state_END    (1)
#define GBBP_UL_CODE_STATE_RPT_ul_crc_state_START   (4)
#define GBBP_UL_CODE_STATE_RPT_ul_crc_state_END     (5)


/*****************************************************************************
 结构名    : GBBP_UL_CODE_RAM_RST_UNION
 结构说明  : UL_CODE_RAM_RST 寄存器结构定义。地址偏移量:0x13B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ul_code_ram_rst_reg;
    struct
    {
        unsigned int  cpu_ul_cod_ram_rst_imi : 1;  /* bit[0]   : 软件对编码模块内部RAM（编码交织后存储RAM）清零信号，只需开机后，配置一下即可，逻辑自清零 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_UL_CODE_RAM_RST_UNION;
#define GBBP_UL_CODE_RAM_RST_cpu_ul_cod_ram_rst_imi_START  (0)
#define GBBP_UL_CODE_RAM_RST_cpu_ul_cod_ram_rst_imi_END    (0)


/*****************************************************************************
 结构名    : GBBP_UL_CODE_RAM_RST_CFG_UNION
 结构说明  : UL_CODE_RAM_RST_CFG 寄存器结构定义。地址偏移量:0x13B8，初值:0x004D0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ul_code_ram_rst_cfg_reg;
    struct
    {
        unsigned int  cpu_ul_cod_ram_rst_addr   : 7;  /* bit[0-6]  : 清零起始块地址 */
        unsigned int  reserved_0                : 9;  /* bit[7-15] : 保留 */
        unsigned int  cpu_ul_cod_ram_rst_length : 7;  /* bit[16-22]: 清零数据块长度 */
        unsigned int  reserved_1                : 9;  /* bit[23-31]: 保留 */
    } reg;
} GBBP_UL_CODE_RAM_RST_CFG_UNION;
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_addr_START    (0)
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_addr_END      (6)
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_length_START  (16)
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_length_END    (22)


/*****************************************************************************
 结构名    : GBBP_WAKE_TEST_QB_FRAC_RPT_UNION
 结构说明  : WAKE_TEST_QB_FRAC_RPT 寄存器结构定义。地址偏移量:0x1224，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      wake_test_qb_frac_rpt_reg;
    struct
    {
        unsigned int  gdrx_wake_frac     : 7;  /* bit[0-6]  : DRX唤醒切换时GTC此时FRAC计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用 */
        unsigned int  reserved_0         : 9;  /* bit[7-15] : 保留 */
        unsigned int  gdrx_wake_chip_cnt : 13; /* bit[16-28]: DRX唤醒切换时GTC此时gtc_timebase计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_WAKE_TEST_QB_FRAC_RPT_UNION;
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_frac_START      (0)
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_frac_END        (6)
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_chip_cnt_START  (16)
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_chip_cnt_END    (28)


/*****************************************************************************
 结构名    : GBBP_WAKE_TEST_T1_T2_T3_RPT_UNION
 结构说明  : WAKE_TEST_T1_T2_T3_RPT 寄存器结构定义。地址偏移量:0x1228，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      wake_test_t1_t2_t3_rpt_reg;
    struct
    {
        unsigned int  gdrx_wake_t1_cnt : 11; /* bit[0-10] : DRX唤醒切换时GTC此时T1计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用 */
        unsigned int  reserved_0       : 5;  /* bit[11-15]: 保留 */
        unsigned int  gdrx_wake_t2_cnt : 5;  /* bit[16-20]: DRX唤醒切换时GTC此时T2计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用 */
        unsigned int  reserved_1       : 3;  /* bit[21-23]: 保留 */
        unsigned int  gdrx_wake_t3_cnt : 6;  /* bit[24-29]: DRX唤醒切换时GTC此时T3计数（测试用，104M钟不断，测试GTC计数与DRX计数是否相同），测试用 */
        unsigned int  reserved_2       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_WAKE_TEST_T1_T2_T3_RPT_UNION;
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t1_cnt_START  (0)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t1_cnt_END    (10)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t2_cnt_START  (16)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t2_cnt_END    (20)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t3_cnt_START  (24)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t3_cnt_END    (29)


/*****************************************************************************
 结构名    : GBBP_WAKE_GTC_FN_RPT_UNION
 结构说明  : WAKE_GTC_FN_RPT 寄存器结构定义。地址偏移量:0x122C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      wake_gtc_fn_rpt_reg;
    struct
    {
        unsigned int  gdrx_wake_fn_low  : 11; /* bit[0-10] : DRX唤醒切换时，此时GTC的FN_LOW计数值，用于DRX测试用 */
        unsigned int  reserved_0        : 5;  /* bit[11-15]: 保留 */
        unsigned int  gdrx_wake_fn_high : 11; /* bit[16-26]: DRX唤醒切换时，此时GTC的FN_HIGH计数值，用于DRX测试用 */
        unsigned int  reserved_1        : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_WAKE_GTC_FN_RPT_UNION;
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_low_START   (0)
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_low_END     (10)
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_high_START  (16)
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_high_END    (26)


/*****************************************************************************
 结构名    : GBBP_CPU_A5_LSB_SEQ_SEL_UNION
 结构说明  : CPU_A5_LSB_SEQ_SEL 寄存器结构定义。地址偏移量:0x1458，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_a5_lsb_seq_sel_reg;
    struct
    {
        unsigned int  cpu_a5_sequence_lsb_sel : 1;  /* bit[0]   : 内部A53加解密算法bit输出顺序配置，请配置为0 */
        unsigned int  reserved_0              : 3;  /* bit[1-3] : 保留 */
        unsigned int  cpu_deciph_dir          : 1;  /* bit[4]   : 内部A53解密算法bit输出顺序配置，请配置为0 */
        unsigned int  reserved_1              : 3;  /* bit[5-7] : 保留 */
        unsigned int  cpu_ciph_dir            : 1;  /* bit[8]   : 内部A53加密算法bit输出顺序配置，请配置为1 */
        unsigned int  reserved_2              : 23; /* bit[9-31]: 保留 */
    } reg;
} GBBP_CPU_A5_LSB_SEQ_SEL_UNION;
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_a5_sequence_lsb_sel_START  (0)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_a5_sequence_lsb_sel_END    (0)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_deciph_dir_START           (4)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_deciph_dir_END             (4)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_ciph_dir_START             (8)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_ciph_dir_END               (8)


/*****************************************************************************
 结构名    : GBBP_CPU_2G4_GAP_LENGTH_UNION
 结构说明  : CPU_2G4_GAP_LENGTH 寄存器结构定义。地址偏移量:0x1248，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_gap_length_reg;
    struct
    {
        unsigned int  cpu_2g4_gap_length : 23; /* bit[0-22] : 2G下进行4G测量的GAP长度。单位是QB。
                                                              1，2G为主模时，异系统GAP最大长度为大概13*51-2帧左右，就是3305000Qb。
                                                              2，cpu_2g4_gap_length的配置范围是0~3305000QB。
                                                              3，cpu_2g4_gap_length + cpu_2g4_int0_int1_dist的结果，不应超过23'h7f_ffff。 */
        unsigned int  reserved           : 9;  /* bit[23-31]: 保留 */
    } reg;
} GBBP_CPU_2G4_GAP_LENGTH_UNION;
#define GBBP_CPU_2G4_GAP_LENGTH_cpu_2g4_gap_length_START  (0)
#define GBBP_CPU_2G4_GAP_LENGTH_cpu_2g4_gap_length_END    (22)


/*****************************************************************************
 结构名    : GBBP_CPU_2G4_GAP_STOP_UNION
 结构说明  : CPU_2G4_GAP_STOP 寄存器结构定义。地址偏移量:0x124C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_gap_stop_reg;
    struct
    {
        unsigned int  cpu_2g4_gap_stop_imi : 1;  /* bit[0]   : 2G下进行4G测量期间，GPHY提前停止occasion的信号，脉冲信号。GBBP收到该信号后，立即停止gap_cnt计数，并上报int2（出沟中断），并拉高通道控制指示信号wg_intrasys_valid_delay。自清零。 */
        unsigned int  cpu_2g4_int0_en_imi  : 1;  /* bit[1]   : 如果下一帧需要启动2G测4G，则在当前帧的配置时隙，配置该信号为1，并配置cpu_int0_gen_qb。自清零。 */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} GBBP_CPU_2G4_GAP_STOP_UNION;
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_gap_stop_imi_START  (0)
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_gap_stop_imi_END    (0)
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_int0_en_imi_START   (1)
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_int0_en_imi_END     (1)


/*****************************************************************************
 结构名    : GBBP_CPU_2G4_DIST_UNION
 结构说明  : CPU_2G4_DIST 寄存器结构定义。地址偏移量:0x1250，初值:0x0003006C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_dist_reg;
    struct
    {
        unsigned int  cpu_2g4_int0_int1_dist : 12; /* bit[0-11] : 2G测4G时，中断0和中断1的间隔时间。单位是QB。
                                                                  默认值是108QB（约100us） */
        unsigned int  reserved_0             : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_intrasys_delay   : 4;  /* bit[16-19]: g_intrasys_valid_delay相对于g_intrasys_valid的延迟时间。支持延迟1~3个SSI写操作周期，保证LTE的最后一个射频数据写完。写入一个SSI字，所需时钟周期是27*52.08 = 1406.16 ns，约1.5QB 。默认值配置3（QB）。 */
        unsigned int  reserved_1             : 12; /* bit[20-31]: 保留 */
    } reg;
} GBBP_CPU_2G4_DIST_UNION;
#define GBBP_CPU_2G4_DIST_cpu_2g4_int0_int1_dist_START  (0)
#define GBBP_CPU_2G4_DIST_cpu_2g4_int0_int1_dist_END    (11)
#define GBBP_CPU_2G4_DIST_cpu_g_intrasys_delay_START    (16)
#define GBBP_CPU_2G4_DIST_cpu_g_intrasys_delay_END      (19)


/*****************************************************************************
 结构名    : GBBP_CPU_2G4_INT0_GEN_QB_UNION
 结构说明  : CPU_2G4_INT0_GEN_QB 寄存器结构定义。地址偏移量:0x1254，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_int0_gen_qb_reg;
    struct
    {
        unsigned int  cpu_2g4_int0_gen_qb  : 13; /* bit[0-12] : 如果下一帧需要启动2G测4G，则在当前帧的配置时隙，配置该信号，表示在下帧帧头之后cpu_2g4_int0_gen_qb个QB，产生中断0 */
        unsigned int  reserved_0           : 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_2g4_gap_stop_rpt : 2;  /* bit[16-17]: cpu_2g4_gap_stop信号触发的计数器，用于观测cpu_2g4_gap_stop信号是否生效，如果生效，则每次该计数器自加1，循环计数 */
        unsigned int  reserved_1           : 6;  /* bit[18-23]: 保留 */
        unsigned int  cpu_2g4_int0_rpt     : 2;  /* bit[24-25]: cpu_2g4_int0_en信号触发的计数器，用于观测cpu_2g4_int0_en信号是否生效，如果生效，则每次该计数器自加1，循环计数 */
        unsigned int  reserved_2           : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_CPU_2G4_INT0_GEN_QB_UNION;
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_gen_qb_START   (0)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_gen_qb_END     (12)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_gap_stop_rpt_START  (16)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_gap_stop_rpt_END    (17)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_rpt_START      (24)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_rpt_END        (25)


/*****************************************************************************
 结构名    : GBBP_CPU_2G4_INT0_TIMING_UNION
 结构说明  : CPU_2G4_INT0_TIMING 寄存器结构定义。地址偏移量:0x1240，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_int0_timing_reg;
    struct
    {
        unsigned int  g_int0_timebase_qb : 13; /* bit[0-12] : 2G测4G时，中断0对应的timebase，单位是QB */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: 保留 */
        unsigned int  g_int0_fn          : 11; /* bit[16-26]: 2G测4G时，中断0对应的FN低11位 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_CPU_2G4_INT0_TIMING_UNION;
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_timebase_qb_START  (0)
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_timebase_qb_END    (12)
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_fn_START           (16)
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_fn_END             (26)


/*****************************************************************************
 结构名    : GBBP_CPU_2G4_INT2_TIMING_UNION
 结构说明  : CPU_2G4_INT2_TIMING 寄存器结构定义。地址偏移量:0x1244，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_int2_timing_reg;
    struct
    {
        unsigned int  g_int2_timebase_qb : 13; /* bit[0-12] : 2G测4G时，中断2对应的timebase，单位是QB */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: 保留 */
        unsigned int  g_int2_fn          : 11; /* bit[16-26]: 2G测4G时，中断2对应的FN低11位 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_CPU_2G4_INT2_TIMING_UNION;
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_timebase_qb_START  (0)
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_timebase_qb_END    (12)
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_fn_START           (16)
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_fn_END             (26)


/*****************************************************************************
 结构名    : GBBP_FB_AFC_PHASE_THRESHOLD_CFG_UNION
 结构说明  : FB_AFC_PHASE_THRESHOLD_CFG 寄存器结构定义。地址偏移量:0x1230，初值:0x02F801F4，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_afc_phase_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_fb_afc_phase_min : 10; /* bit[0-9]  : FB-AFC算法相位估计值参考下限，典型值500。可配300,400,500。 */
        unsigned int  reserved_0           : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_fb_afc_phase_max : 10; /* bit[16-25]: FB-AFC算法相位估计值参考上限，典型值760。 */
        unsigned int  reserved_1           : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_FB_AFC_PHASE_THRESHOLD_CFG_UNION;
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_min_START  (0)
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_min_END    (9)
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_max_START  (16)
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_max_END    (25)


/*****************************************************************************
 结构名    : GBBP_FB_FCUT_THRESHOLD_CFG_UNION
 结构说明  : FB_FCUT_THRESHOLD_CFG 寄存器结构定义。地址偏移量:0x1234，初值:0x03FF0033，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_fcut_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_fb_afc_fc_low  : 10; /* bit[0-9]  : FB-AFC算法系数fcut的最小值，如果经过α滤波后的相位估计值小雨相位估计值参考下限，则系数fcut的值就等于此最小值。典型值51。 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_fb_afc_fc_high : 10; /* bit[16-25]: FB-AFC算法系数fcut的最大值，如果经过α滤波后的相位估计值大于相位估计值的参考上限，则系数fcut的值就等于此最大值。典型值1023。 */
        unsigned int  reserved_1         : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_FB_FCUT_THRESHOLD_CFG_UNION;
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_low_START   (0)
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_low_END     (9)
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_high_START  (16)
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_high_END    (25)


/*****************************************************************************
 结构名    : GBBP_FB_AFC_ALPHA_SEL_UNION
 结构说明  : FB_AFC_ALPHA_SEL 寄存器结构定义。地址偏移量:0x1238，初值:0x03FF4A00，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_afc_alpha_sel_reg;
    struct
    {
        unsigned int  cpu_fb_numerator_sel : 2;  /* bit[0-1]  : FB-AFC算法α滤波系数选择：
                                                                0：1/32；
                                                                1：1/16；
                                                                2：1/8；
                                                                3：1/4。
                                                                典型值1/32。 */
        unsigned int  reserved_0           : 6;  /* bit[2-7]  : 保留 */
        unsigned int  cpu_fb_stage_num     : 4;  /* bit[8-11] : Fcut值固定使用FCutInit的跟踪FB数码。可配范围：5~10。典型配置：10。 */
        unsigned int  cpu_fb_rshift_num    : 3;  /* bit[12-14]: 对称右移比特数，可配范围0~7。典型配置：4。 */
        unsigned int  reserved_1           : 1;  /* bit[15]   : 保留 */
        unsigned int  cpu_fcut_init        : 10; /* bit[16-25]: 一阶环路滤波器初始带宽，典型配置：1023。 */
        unsigned int  reserved_2           : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_FB_AFC_ALPHA_SEL_UNION;
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_numerator_sel_START  (0)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_numerator_sel_END    (1)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_stage_num_START      (8)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_stage_num_END        (11)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_rshift_num_START     (12)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_rshift_num_END       (14)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fcut_init_START         (16)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fcut_init_END           (25)


/*****************************************************************************
 结构名    : GBBP_SRCH_OPT_CFG_UNION
 结构说明  : SRCH_OPT_CFG 寄存器结构定义。地址偏移量:0x1480，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_opt_cfg_reg;
    struct
    {
        unsigned int  cpu_srch_opt_en            : 1;  /* bit[0]    : 111搜索优化模式使能，1标志打开优化使能，0标志关闭优化使能，采用001 111搜索。 */
        unsigned int  reserved_0                 : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_sb_lock_fail_threshold : 2;  /* bit[4-5]  : 111优化算法中FB-AFC锁定下允许SB译码CRC错误的次数，取值范围0~3。 */
        unsigned int  reserved_1                 : 10; /* bit[6-15] : 保留 */
        unsigned int  cpu_sb_bsic_threshold      : 2;  /* bit[16-17]: 111优化算法中允许SB译码CRC但对BSIC值不同的总次数
                                                                      0：4次；
                                                                      1：5次；
                                                                      2：6次；
                                                                      3：7次。 */
        unsigned int  reserved_2                 : 6;  /* bit[18-23]: 保留 */
        unsigned int  sb_dec_bsic                : 6;  /* bit[24-29]: 本次SB译码BSIC上报。 */
        unsigned int  reserved_3                 : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_SRCH_OPT_CFG_UNION;
#define GBBP_SRCH_OPT_CFG_cpu_srch_opt_en_START             (0)
#define GBBP_SRCH_OPT_CFG_cpu_srch_opt_en_END               (0)
#define GBBP_SRCH_OPT_CFG_cpu_sb_lock_fail_threshold_START  (4)
#define GBBP_SRCH_OPT_CFG_cpu_sb_lock_fail_threshold_END    (5)
#define GBBP_SRCH_OPT_CFG_cpu_sb_bsic_threshold_START       (16)
#define GBBP_SRCH_OPT_CFG_cpu_sb_bsic_threshold_END         (17)
#define GBBP_SRCH_OPT_CFG_sb_dec_bsic_START                 (24)
#define GBBP_SRCH_OPT_CFG_sb_dec_bsic_END                   (29)


/*****************************************************************************
 结构名    : GBBP_R2_RSSI1234_THRESHOLD_UNION
 结构说明  : R2_RSSI1234_THRESHOLD 寄存器结构定义。地址偏移量:0x5204，初值:0x00D3BFA3，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      r2_rssi1234_threshold_reg;
    struct
    {
        unsigned int  cpu_r2_rssi1_threshold : 8;  /* bit[0-7]  : RSSI 两轮门限1，单位dBm，推荐-93 */
        unsigned int  cpu_r2_rssi2_threshold : 8;  /* bit[8-15] : RSSI 两轮门限2，单位dBm，推荐-65 */
        unsigned int  cpu_r2_rssi3_threshold : 8;  /* bit[16-23]: RSSI 两轮门限3，单位dBm，推荐-45 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_R2_RSSI1234_THRESHOLD_UNION;
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi1_threshold_START  (0)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi1_threshold_END    (7)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi2_threshold_START  (8)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi2_threshold_END    (15)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi3_threshold_START  (16)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi3_threshold_END    (23)


/*****************************************************************************
 结构名    : GBBP_R2_RSSI4567_THRESHOLD_UNION
 结构说明  : R2_RSSI4567_THRESHOLD 寄存器结构定义。地址偏移量:0x5208，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      r2_rssi4567_threshold_reg;
    struct
    {
        unsigned int  cpu_r2_rssi4_threshold : 8;  /* bit[0-7]  : RSSI 两轮门限4，单位dBm，暂不使用，默认值为-1 */
        unsigned int  cpu_r2_rssi5_threshold : 8;  /* bit[8-15] : RSSI 两轮门限5，单位dBm，暂不使用，默认值为-1 */
        unsigned int  cpu_r2_rssi6_threshold : 8;  /* bit[16-23]: RSSI 两轮门限6，单位dBm，暂不使用，默认值为-1 */
        unsigned int  cpu_r2_rssi7_threshold : 8;  /* bit[24-31]: RSSI 两轮门限7，单位dBm，暂不使用，默认值-1 */
    } reg;
} GBBP_R2_RSSI4567_THRESHOLD_UNION;
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi4_threshold_START  (0)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi4_threshold_END    (7)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi5_threshold_START  (8)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi5_threshold_END    (15)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi6_threshold_START  (16)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi6_threshold_END    (23)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi7_threshold_START  (24)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi7_threshold_END    (31)


/*****************************************************************************
 结构名    : GBBP_AGC_WAIT_LEN_GTH_UNION
 结构说明  : AGC_WAIT_LEN_GTH 寄存器结构定义。地址偏移量:0x520C，初值:0x00003008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      agc_wait_len_gth_reg;
    struct
    {
        unsigned int  cpu_agc_wait           : 5;  /* bit[0-4]  : 快速AGC能量计算每轮之间等待时间，单位symbol，默认8。 */
        unsigned int  reserved_0             : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_dcr_recv_bypass    : 1;  /* bit[8]    : 解调与搜索通道直流偏置数字细调环旁路功能，高电平有效，该信号有效时，表示数字细调环不对接受数据进行反馈处理。 */
        unsigned int  reserved_1             : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_rssi_hypersis      : 4;  /* bit[12-15]: RSSI 磁滞范围，单位dBm，默认3。 */
        unsigned int  reserved_2             : 8;  /* bit[16-23]: 保留 */
        unsigned int  cpu_dcr_burst_mode     : 1;  /* bit[24]   : 解调通道直流偏置数字细调环旁路功能，高电平有效，该信号有效时，表示数字细调环不对接受数据进行反馈处理。 */
        unsigned int  reserved_3             : 6;  /* bit[25-30]: 保留 */
        unsigned int  cpu_fast_threshold_sel : 1;  /* bit[31]   : 快速AGC测量模式选择信号
                                                                  0：快速AGC测量模式按照测量轮数gsp_fast_agc_mode选择
                                                                  1：快速AGC测量模式按照测量门限gsp_agc_measure_mode选择 */
    } reg;
} GBBP_AGC_WAIT_LEN_GTH_UNION;
#define GBBP_AGC_WAIT_LEN_GTH_cpu_agc_wait_START            (0)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_agc_wait_END              (4)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_recv_bypass_START     (8)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_recv_bypass_END       (8)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_rssi_hypersis_START       (12)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_rssi_hypersis_END         (15)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_burst_mode_START      (24)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_burst_mode_END        (24)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_fast_threshold_sel_START  (31)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_fast_threshold_sel_END    (31)


/*****************************************************************************
 结构名    : GBBP_R3_RSSI1234_THRESHOLD_UNION
 结构说明  : R3_RSSI1234_THRESHOLD 寄存器结构定义。地址偏移量:0x5210，初值:0x00D3BFA3，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      r3_rssi1234_threshold_reg;
    struct
    {
        unsigned int  cpu_r3_rssi1_threshold : 8;  /* bit[0-7]  : RSSI 三轮门限1，单位dBm，推荐-93 */
        unsigned int  cpu_r3_rssi2_threshold : 8;  /* bit[8-15] : RSSI 三轮门限2，单位dBm，推荐-65 */
        unsigned int  cpu_r3_rssi3_threshold : 8;  /* bit[16-23]: RSSI 三轮门限3，单位dBm，推荐-45 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_R3_RSSI1234_THRESHOLD_UNION;
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi1_threshold_START  (0)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi1_threshold_END    (7)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi2_threshold_START  (8)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi2_threshold_END    (15)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi3_threshold_START  (16)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi3_threshold_END    (23)


/*****************************************************************************
 结构名    : GBBP_R3_RSSI4567_THRESHOLD_UNION
 结构说明  : R3_RSSI4567_THRESHOLD 寄存器结构定义。地址偏移量:0x521C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      r3_rssi4567_threshold_reg;
    struct
    {
        unsigned int  cpu_r3_rssi4_threshold : 8;  /* bit[0-7]  : RSSI 三轮门限4，单位dBm，暂不使用，默认值为-1 */
        unsigned int  cpu_r3_rssi5_threshold : 8;  /* bit[8-15] : RSSI 三轮门限5，单位dBm，暂不使用，默认值为-1 */
        unsigned int  cpu_r3_rssi6_threshold : 8;  /* bit[16-23]: RSSI 三轮门限6，单位dBm，暂不使用，默认值为-1 */
        unsigned int  cpu_r3_rssi7_threshold : 8;  /* bit[24-31]: RSSI 三轮门限7，单位dBm，暂不使用，默认值为-1 */
    } reg;
} GBBP_R3_RSSI4567_THRESHOLD_UNION;
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi4_threshold_START  (0)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi4_threshold_END    (7)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi5_threshold_START  (8)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi5_threshold_END    (15)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi6_threshold_START  (16)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi6_threshold_END    (23)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi7_threshold_START  (24)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi7_threshold_END    (31)


/*****************************************************************************
 结构名    : GBBP_DC_IQ_REMOVE_RPT_UNION
 结构说明  : DC_IQ_REMOVE_RPT 寄存器结构定义。地址偏移量:0x5220，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dc_iq_remove_rpt_reg;
    struct
    {
        unsigned int  dc_iq_remove_rpt_i : 14; /* bit[0-13] : 多路数字细调环偏置寄存器经过截位与限幅后的输出，也就是当前档位的直流输出。其可以作为直流偏置校准的参考值。两个14bit信号分别占用IMI总线的[29:16]和[13:0]，低14bit为I路输出，高14bit为Q路输出。 */
        unsigned int  reserved_0         : 2;  /* bit[14-15]: 保留 */
        unsigned int  dc_iq_remove_rpt_q : 14; /* bit[16-29]: 多路数字细调环偏置寄存器经过截位与限幅后的输出，也就是当前档位的直流输出。其可以作为直流偏置校准的参考值。两个14bit信号分别占用IMI总线的[29:16]和[13:0]，低14bit为I路输出，高14bit为Q路输出。 */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_DC_IQ_REMOVE_RPT_UNION;
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_i_START  (0)
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_i_END    (13)
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_q_START  (16)
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_q_END    (29)


/*****************************************************************************
 结构名    : GBBP_DC_IQ_BURST_REMOVE_RPT_UNION
 结构说明  : DC_IQ_BURST_REMOVE_RPT 寄存器结构定义。地址偏移量:0x5224，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dc_iq_burst_remove_rpt_reg;
    struct
    {
        unsigned int  agc_data_i_dcr_rpt : 14; /* bit[0-13] : 时隙前处理I路直流偏置上报 */
        unsigned int  reserved_0         : 2;  /* bit[14-15]: 保留 */
        unsigned int  agc_data_q_dcr_rpt : 14; /* bit[16-29]: 时隙前处理Q路直流偏置上报 */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_DC_IQ_BURST_REMOVE_RPT_UNION;
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_i_dcr_rpt_START  (0)
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_i_dcr_rpt_END    (13)
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_q_dcr_rpt_START  (16)
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_q_dcr_rpt_END    (29)


/*****************************************************************************
 结构名    : GBBP_SB_THRES_C_UNION
 结构说明  : SB_THRES_C 寄存器结构定义。地址偏移量:0x5230，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_thres_c_reg;
    struct
    {
        unsigned int  sb_thres_c : 19; /* bit[0-18] : SB解调前载波能量值上报 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_SB_THRES_C_UNION;
#define GBBP_SB_THRES_C_sb_thres_c_START  (0)
#define GBBP_SB_THRES_C_sb_thres_c_END    (18)


/*****************************************************************************
 结构名    : GBBP_SB_THRES_I_UNION
 结构说明  : SB_THRES_I 寄存器结构定义。地址偏移量:0x5234，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_thres_i_reg;
    struct
    {
        unsigned int  sb_thres_i : 19; /* bit[0-18] : SB解调前噪声能量值上报 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_SB_THRES_I_UNION;
#define GBBP_SB_THRES_I_sb_thres_i_START  (0)
#define GBBP_SB_THRES_I_sb_thres_i_END    (18)


/*****************************************************************************
 结构名    : GBBP_AAGC_NEXT_GAIN_UNION
 结构说明  : AAGC_NEXT_GAIN 寄存器结构定义。地址偏移量:0x5250，初值:0x01000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_next_gain_reg;
    struct
    {
        unsigned int  aagc_next_gain_cpu : 3;  /* bit[0-2]  : AGC期望控制增益。在快速模式最后一轮和慢速模式下统计结束后上报给CPU。 */
        unsigned int  reserved_0         : 5;  /* bit[3-7]  : 保留 */
        unsigned int  agc_rssi_125db_cpu : 12; /* bit[8-19] : RSSI值，单位是0.125dBm，上报给CPU，该值已是空口的RSSI值。 */
        unsigned int  reserved_1         : 4;  /* bit[20-23]: 保留 */
        unsigned int  aagc_curr_gain     : 3;  /* bit[24-26]: 当前AAGC档位上报。 */
        unsigned int  reserved_2         : 4;  /* bit[27-30]: 保留 */
        unsigned int  agc_fast_cal_flag  : 1;  /* bit[31]   : 快慢速测量标志。1表示当前时快速测量；0表示当前是慢速测量。 */
    } reg;
} GBBP_AAGC_NEXT_GAIN_UNION;
#define GBBP_AAGC_NEXT_GAIN_aagc_next_gain_cpu_START  (0)
#define GBBP_AAGC_NEXT_GAIN_aagc_next_gain_cpu_END    (2)
#define GBBP_AAGC_NEXT_GAIN_agc_rssi_125db_cpu_START  (8)
#define GBBP_AAGC_NEXT_GAIN_agc_rssi_125db_cpu_END    (19)
#define GBBP_AAGC_NEXT_GAIN_aagc_curr_gain_START      (24)
#define GBBP_AAGC_NEXT_GAIN_aagc_curr_gain_END        (26)
#define GBBP_AAGC_NEXT_GAIN_agc_fast_cal_flag_START   (31)
#define GBBP_AAGC_NEXT_GAIN_agc_fast_cal_flag_END     (31)


/*****************************************************************************
 结构名    : GBBP_RSSI_QB_FRQ_UNION
 结构说明  : RSSI_QB_FRQ 寄存器结构定义。地址偏移量:0x5254，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      rssi_qb_frq_reg;
    struct
    {
        unsigned int  rssi_qb  : 13; /* bit[0-12] : 测量中断时刻TDMA帧QB值。 */
        unsigned int  reserved_0: 3;  /* bit[13-15]: 保留 */
        unsigned int  rssi_frq : 12; /* bit[16-27]: 当前测量的RSSI对应的频点号，[27:26]为band号，band号与频段的关系由软件自己定义，[25:16]为band内的频点号，该值由GTC指令配置，{GSP_RSSI_FRQ_HIGH_ADDR,GSP_RSSI_FRQ_LOW_ADDR},BBP进行延时后于测量中断一起上报。 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_RSSI_QB_FRQ_UNION;
#define GBBP_RSSI_QB_FRQ_rssi_qb_START   (0)
#define GBBP_RSSI_QB_FRQ_rssi_qb_END     (12)
#define GBBP_RSSI_QB_FRQ_rssi_frq_START  (16)
#define GBBP_RSSI_QB_FRQ_rssi_frq_END    (27)


/*****************************************************************************
 结构名    : GBBP_DRSSI_ENERGY_RPT_UNION
 结构说明  : DRSSI_ENERGY_RPT 寄存器结构定义。地址偏移量:0x5258，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      drssi_energy_rpt_reg;
    struct
    {
        unsigned int  drssi_energy_report_cpu : 23; /* bit[0-22] : DRSSI求对数运算前数据上报。 */
        unsigned int  reserved                : 9;  /* bit[23-31]: 保留 */
    } reg;
} GBBP_DRSSI_ENERGY_RPT_UNION;
#define GBBP_DRSSI_ENERGY_RPT_drssi_energy_report_cpu_START  (0)
#define GBBP_DRSSI_ENERGY_RPT_drssi_energy_report_cpu_END    (22)


/*****************************************************************************
 结构名    : GBBP_AGC_FAST1_2_RSSI_CPU_UNION
 结构说明  : AGC_FAST1_2_RSSI_CPU 寄存器结构定义。地址偏移量:0x525C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      agc_fast1_2_rssi_cpu_reg;
    struct
    {
        unsigned int  agc_rssi_fast1_125db_cpu : 12; /* bit[0-11] : RSSI值，单位0.125dBm，其就是空口信号能量，为快速测量第一轮RSSI上报。 */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: 保留 */
        unsigned int  agc_rssi_fast2_125db_cpu : 12; /* bit[16-27]: RSSI值，单位0.125dBm，其就是空口信号能量，为快速测量第二轮RSSI上报。 */
        unsigned int  reserved_1               : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_AGC_FAST1_2_RSSI_CPU_UNION;
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast1_125db_cpu_START  (0)
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast1_125db_cpu_END    (11)
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast2_125db_cpu_START  (16)
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast2_125db_cpu_END    (27)


/*****************************************************************************
 结构名    : GBBP_AGC_DEC_INT_T3_FN_UNION
 结构说明  : AGC_DEC_INT_T3_FN 寄存器结构定义。地址偏移量:0x5214，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      agc_dec_int_t3_fn_reg;
    struct
    {
        unsigned int  agc_int_tdma_fn : 6;  /* bit[0-5]  : AGC测量中断所在TDMA帧号模51计数值 */
        unsigned int  reserved_0      : 10; /* bit[6-15] : 保留 */
        unsigned int  dec_int_tdma_fn : 6;  /* bit[16-21]: NB业务译码中断所在TDMA帧号模51计数值 */
        unsigned int  reserved_1      : 10; /* bit[22-31]: 保留 */
    } reg;
} GBBP_AGC_DEC_INT_T3_FN_UNION;
#define GBBP_AGC_DEC_INT_T3_FN_agc_int_tdma_fn_START  (0)
#define GBBP_AGC_DEC_INT_T3_FN_agc_int_tdma_fn_END    (5)
#define GBBP_AGC_DEC_INT_T3_FN_dec_int_tdma_fn_START  (16)
#define GBBP_AGC_DEC_INT_T3_FN_dec_int_tdma_fn_END    (21)


/*****************************************************************************
 结构名    : GBBP_DEM_INT_FN_QB_UNION
 结构说明  : DEM_INT_FN_QB 寄存器结构定义。地址偏移量:0x5218，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dem_int_fn_qb_reg;
    struct
    {
        unsigned int  dem_int_tdma_qb : 13; /* bit[0-12] : 解调中断所在TDMA QB计数值 */
        unsigned int  reserved_0      : 3;  /* bit[13-15]: 保留 */
        unsigned int  dem_int_tdma_fn : 6;  /* bit[16-21]: 解调中断所在TDMA帧号模51计数值 */
        unsigned int  reserved_1      : 10; /* bit[22-31]: 保留 */
    } reg;
} GBBP_DEM_INT_FN_QB_UNION;
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_qb_START  (0)
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_qb_END    (12)
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_fn_START  (16)
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_fn_END    (21)


/*****************************************************************************
 结构名    : GBBP_CPU_EXT_LINE_CTRL_UNION
 结构说明  : CPU_EXT_LINE_CTRL 寄存器结构定义。地址偏移量:0x5E04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ext_line_ctrl_reg;
    struct
    {
        unsigned int  cpu_gtc_ext_line_ctrl           : 8;  /* bit[0-7] : 定向线控CPU接口配置，其中
                                                                          bit0对应rf_tcvr_on,即射频芯片工作使能信号
                                                                          bit1对应rf_tx_en,即射频上行发送工作使能信号
                                                                          bit2对应rf_rst_n,即射频复位控制信号
                                                                          bit3对应abb_rxa_en,即ABB RXA通道使能信号
                                                                          bit4对应abb_rxb_en,即ABB RXB通道使能信号
                                                                          bit5对应abb_tx_en,即ABB TX通道使能信号
                                                                          bit6对应gapc_en，即Auxdac通道使能信号 */
        unsigned int  reserved                        : 23; /* bit[8-30]: 保留 */
        unsigned int  cpu_gtc_ext_line_ctrl_wr_en_imi : 1;  /* bit[31]  : 8bit定向线控信号写使能指示信号 */
    } reg;
} GBBP_CPU_EXT_LINE_CTRL_UNION;
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_START            (0)
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_END              (7)
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_wr_en_imi_START  (31)
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_wr_en_imi_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_GSP_EXT_LINE_STATE_RPT_UNION
 结构说明  : CPU_GSP_EXT_LINE_STATE_RPT 寄存器结构定义。地址偏移量:0x5E08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gsp_ext_line_state_rpt_reg;
    struct
    {
        unsigned int  gtc_gsp_ext_line_ctrl : 7;  /* bit[0-6] : 定向线控实际状态，测试用。
                                                                bit0对应rf_tcvr_on,即射频芯片工作使能信号
                                                                bit1对应rf_tx_en,即射频上行发送工作使能信号
                                                                bit2对应rf_rst_n,即射频复位控制信号
                                                                bit3对应abb_rxa_en,即ABB RXA通道使能信号
                                                                bit4对应abb_rxb_en,即ABB RXB通道使能信号
                                                                bit5对应abb_tx_en,即ABB TX通道使能信号
                                                                bit6对应gapc_en，即Auxdac通道使能信号 */
        unsigned int  reserved              : 25; /* bit[7-31]: 保留 */
    } reg;
} GBBP_CPU_GSP_EXT_LINE_STATE_RPT_UNION;
#define GBBP_CPU_GSP_EXT_LINE_STATE_RPT_gtc_gsp_ext_line_ctrl_START  (0)
#define GBBP_CPU_GSP_EXT_LINE_STATE_RPT_gtc_gsp_ext_line_ctrl_END    (6)


/*****************************************************************************
 结构名    : GBBP_CPU_LINE01_SEL_CFG_UNION
 结构说明  : CPU_LINE01_SEL_CFG 寄存器结构定义。地址偏移量:0x5E0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_line01_sel_cfg_reg;
    struct
    {
        unsigned int  cpu_ext_line01_sel           : 4;  /* bit[0-3] : bit0对应主模MIPI和从模MIPI通道控制选择；
                                                                       bit1对应AUXDAC0和AUXDAC1控制选择；
                                                                       bit2对应ABB CH0与ABB CH1通道控制选择，由于V9R1不存在两个ABB通道，因此该配置默认配置为0，无需改动；
                                                                       bit3对应主模RFIC与从模RFIC通道控制选择。
                                                                       G为主模时，配置为4’d0；G为从模时，配置为4’d9。 */
        unsigned int  reserved                     : 27; /* bit[4-30]: 保留 */
        unsigned int  cpu_ext_line01_sel_wr_en_imi : 1;  /* bit[31]  : cpu_line01_sel_ctrl生效出发信号，即当此信号写为1后，cpu_line01_sel_ctrl对应的配置生效，逻辑自清零。
                                                                       注：要求bit[3:0]事先配置号。 */
    } reg;
} GBBP_CPU_LINE01_SEL_CFG_UNION;
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_START            (0)
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_END              (3)
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_wr_en_imi_START  (31)
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_wr_en_imi_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_LINE01_SEL_STATE_RPT_UNION
 结构说明  : CPU_LINE01_SEL_STATE_RPT 寄存器结构定义。地址偏移量:0x5E10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_line01_sel_state_rpt_reg;
    struct
    {
        unsigned int  gtc_line01_sel_ctrl : 4;  /* bit[0-3] : 通道选择信号实际状态，测试用。
                                                              bit0：gtc_mipi01_sel；
                                                              bit1：gtc_auxdac01_sel；
                                                              bit2：gtc_abb01_sel；
                                                              bit3：gtc_rf01_sel。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} GBBP_CPU_LINE01_SEL_STATE_RPT_UNION;
#define GBBP_CPU_LINE01_SEL_STATE_RPT_gtc_line01_sel_ctrl_START  (0)
#define GBBP_CPU_LINE01_SEL_STATE_RPT_gtc_line01_sel_ctrl_END    (3)


/*****************************************************************************
 结构名    : GBBP_CPU_OFC_RXCM_REG_UNION
 结构说明  : CPU_OFC_RXCM_REG 寄存器结构定义。地址偏移量:0x5360，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ofc_rxcm_reg_reg;
    struct
    {
        unsigned int  reserved               : 31; /* bit[0-30]: 保留 */
        unsigned int  cpu_agc_page_switch_en : 1;  /* bit[31]  : AGC模块配置前向通道增益调整值和RXCORR参数存储RAM和DC_OFFSET存储RAM TDMA帧头乒乓切换使能
                                                                 1表示允许乒乓切换
                                                                 0表示不允许乒乓切换，固定为乒页；当该信号为1时，逻辑内部在TDMA帧头自动切换乒乓标志。 */
    } reg;
} GBBP_CPU_OFC_RXCM_REG_UNION;
#define GBBP_CPU_OFC_RXCM_REG_cpu_agc_page_switch_en_START  (31)
#define GBBP_CPU_OFC_RXCM_REG_cpu_agc_page_switch_en_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_SAMPLE_REG_UNION
 结构说明  : CPU_SAMPLE_REG 寄存器结构定义。地址偏移量:0x536C，初值:0x00000020，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_sample_reg_reg;
    struct
    {
        unsigned int  reserved_0               : 4;  /* bit[0-3]  : 保留 */
        unsigned int  cpu_sample_sel_imi       : 2;  /* bit[4-5]  : bit1:1表示时硬件自判决模式，0表示时软件控制模式。当bit为0时，bit0意义才生效。样点组内奇偶选择信号，0表示选中样点组内偶路数据，1表示选中样点组内奇路数据。用于8PSK解调和搜索。2'b11配置时保留值，请勿配置。在搜索模式下请勿配置为2'bx1模式。 */
        unsigned int  reserved_1               : 2;  /* bit[6-7]  : 保留 */
        unsigned int  cpu_sample_sel_group_imi : 1;  /* bit[8]    : 采样点组选择配置，该信号需要用帧头锁存。
                                                                    0：表示选择1个symbol中的1/3样点组；
                                                                    1：表示选择1个symbol中的2/4样点组。 */
        unsigned int  reserved_2               : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_dcr_bypass           : 1;  /* bit[12]   : 测量通道直流偏置数字细调环旁路功能，高电平有效。
                                                                    该信号有效时，相当于数字细调环不对接收数据进行反馈处理。 */
        unsigned int  reserved_3               : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_CPU_SAMPLE_REG_UNION;
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_imi_START        (4)
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_imi_END          (5)
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_group_imi_START  (8)
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_group_imi_END    (8)
#define GBBP_CPU_SAMPLE_REG_cpu_dcr_bypass_START            (12)
#define GBBP_CPU_SAMPLE_REG_cpu_dcr_bypass_END              (12)


/*****************************************************************************
 结构名    : GBBP_CPU_AGC_RAM_SWITCH_IND_UNION
 结构说明  : CPU_AGC_RAM_SWITCH_IND 寄存器结构定义。地址偏移量:0x5370，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_agc_ram_switch_ind_reg;
    struct
    {
        unsigned int  cpu_agc_ram_switch_ind_imi : 1;  /* bit[0]   : AGC直流偏执RAM和通道增益RAM手动切换指示信号，该信号为脉冲信号，自清零。 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_AGC_RAM_SWITCH_IND_UNION;
#define GBBP_CPU_AGC_RAM_SWITCH_IND_cpu_agc_ram_switch_ind_imi_START  (0)
#define GBBP_CPU_AGC_RAM_SWITCH_IND_cpu_agc_ram_switch_ind_imi_END    (0)


/*****************************************************************************
 结构名    : GBBP_DAGC_MULFACTOR_FIX_UNION
 结构说明  : DAGC_MULFACTOR_FIX 寄存器结构定义。地址偏移量:0x537C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dagc_mulfactor_fix_reg;
    struct
    {
        unsigned int  agc_drssi_25db_cpu      : 9;  /* bit[0-8]  : DRSSI值上报，其对应为ABB输出信号的能量，单位0.25dBm。 */
        unsigned int  reserved_0              : 7;  /* bit[9-15] : 保留 */
        unsigned int  cpu_soft_agc_drssi_25db : 9;  /* bit[16-24]: 软件强制配置的DRSSI值，单位0.25dBm。 */
        unsigned int  reserved_1              : 7;  /* bit[25-31]: 保留 */
    } reg;
} GBBP_DAGC_MULFACTOR_FIX_UNION;
#define GBBP_DAGC_MULFACTOR_FIX_agc_drssi_25db_cpu_START       (0)
#define GBBP_DAGC_MULFACTOR_FIX_agc_drssi_25db_cpu_END         (8)
#define GBBP_DAGC_MULFACTOR_FIX_cpu_soft_agc_drssi_25db_START  (16)
#define GBBP_DAGC_MULFACTOR_FIX_cpu_soft_agc_drssi_25db_END    (24)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN1_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN1_SPI_DATA 寄存器结构定义。地址偏移量:0x5584，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain1_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain1_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第1档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN1_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN1_SPI_DATA_cpu_main_gain1_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN1_SPI_DATA_cpu_main_gain1_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN2_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN2_SPI_DATA 寄存器结构定义。地址偏移量:0x5588，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain2_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain2_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第2档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN2_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN2_SPI_DATA_cpu_main_gain2_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN2_SPI_DATA_cpu_main_gain2_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN3_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN3_SPI_DATA 寄存器结构定义。地址偏移量:0x558C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain3_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain3_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第3档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN3_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN3_SPI_DATA_cpu_main_gain3_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN3_SPI_DATA_cpu_main_gain3_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN4_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN4_SPI_DATA 寄存器结构定义。地址偏移量:0x5590，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain4_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain4_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第4档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN4_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN4_SPI_DATA_cpu_main_gain4_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN4_SPI_DATA_cpu_main_gain4_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN5_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN5_SPI_DATA 寄存器结构定义。地址偏移量:0x5594，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain5_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain5_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第5档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN5_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN5_SPI_DATA_cpu_main_gain5_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN5_SPI_DATA_cpu_main_gain5_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN6_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN6_SPI_DATA 寄存器结构定义。地址偏移量:0x5598，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain6_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain6_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第6档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN6_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN6_SPI_DATA_cpu_main_gain6_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN6_SPI_DATA_cpu_main_gain6_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN7_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN7_SPI_DATA 寄存器结构定义。地址偏移量:0x559C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain7_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain7_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第7档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN7_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN7_SPI_DATA_cpu_main_gain7_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN7_SPI_DATA_cpu_main_gain7_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_MAIN_GAIN8_SPI_DATA_UNION
 结构说明  : CPU_MAIN_GAIN8_SPI_DATA 寄存器结构定义。地址偏移量:0x55A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain8_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain8_spi_data : 24; /* bit[0-23] : 主集天线控制增益模式下第8档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_MAIN_GAIN8_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN8_SPI_DATA_cpu_main_gain8_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN8_SPI_DATA_cpu_main_gain8_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN1_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN1_SPI_DATA 寄存器结构定义。地址偏移量:0x55A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain1_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain1_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第1档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN1_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN1_SPI_DATA_cpu_div_gain1_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN1_SPI_DATA_cpu_div_gain1_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN2_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN2_SPI_DATA 寄存器结构定义。地址偏移量:0x55A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain2_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain2_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第2档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN2_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN2_SPI_DATA_cpu_div_gain2_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN2_SPI_DATA_cpu_div_gain2_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN3_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN3_SPI_DATA 寄存器结构定义。地址偏移量:0x55AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain3_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain3_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第3档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN3_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN3_SPI_DATA_cpu_div_gain3_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN3_SPI_DATA_cpu_div_gain3_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN4_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN4_SPI_DATA 寄存器结构定义。地址偏移量:0x55B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain4_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain4_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第4档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN4_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN4_SPI_DATA_cpu_div_gain4_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN4_SPI_DATA_cpu_div_gain4_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN5_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN5_SPI_DATA 寄存器结构定义。地址偏移量:0x55B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain5_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain5_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第5档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN5_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN5_SPI_DATA_cpu_div_gain5_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN5_SPI_DATA_cpu_div_gain5_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN6_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN6_SPI_DATA 寄存器结构定义。地址偏移量:0x55B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain6_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain6_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第6档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN6_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN6_SPI_DATA_cpu_div_gain6_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN6_SPI_DATA_cpu_div_gain6_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN7_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN7_SPI_DATA 寄存器结构定义。地址偏移量:0x55BC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain7_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain7_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第7档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN7_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN7_SPI_DATA_cpu_div_gain7_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN7_SPI_DATA_cpu_div_gain7_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_CPU_DIV_GAIN8_SPI_DATA_UNION
 结构说明  : CPU_DIV_GAIN8_SPI_DATA 寄存器结构定义。地址偏移量:0x55C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain8_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain8_spi_data : 24; /* bit[0-23] : 分集天线控制增益模式下第8档SPI控制字，具体SPI控制字组合方式请参见相关射频手册。主分集控制字选择请配置gsp_rf_gain_word_sel。 */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_CPU_DIV_GAIN8_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN8_SPI_DATA_cpu_div_gain8_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN8_SPI_DATA_cpu_div_gain8_spi_data_END    (23)


/*****************************************************************************
 结构名    : GBBP_NB_AFC_LOOP_SWITCH_UNION
 结构说明  : NB_AFC_LOOP_SWITCH 寄存器结构定义。地址偏移量:0x5340，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_afc_loop_switch_reg;
    struct
    {
        unsigned int  cpu_nb_afc_switch           : 1;  /* bit[0]   : 一阶环与二阶环选择控制信号，
                                                                      0：选择一阶环；
                                                                      1：选择二阶环。 */
        unsigned int  cpu_nb_afc_slow_fast_switch : 1;  /* bit[1]   : 二阶环快慢速阶段控制，
                                                                      0：表示采用慢速跟踪；
                                                                      1：表示采用快速跟踪。 */
        unsigned int  reserved                    : 29; /* bit[2-30]: 保留 */
        unsigned int  cpu_nb_afc_sel              : 1;  /* bit[31]  : NB-AFC控制方式选择。
                                                                      0：GTC控制；
                                                                      1：CPU控制；
                                                                      默认CPU控制。 */
    } reg;
} GBBP_NB_AFC_LOOP_SWITCH_UNION;
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_switch_START            (0)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_switch_END              (0)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_slow_fast_switch_START  (1)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_slow_fast_switch_END    (1)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_sel_START               (31)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_sel_END                 (31)


/*****************************************************************************
 结构名    : GBBP_ADDR_AFC_K_VALUE_UNION
 结构说明  : ADDR_AFC_K_VALUE 寄存器结构定义。地址偏移量:0x5E00，初值:0x00000054，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_afc_k_value_reg;
    struct
    {
        unsigned int  cpu_afc_k_factor : 10; /* bit[0-9]  : AFC K值调整，默认值为10’d84，TCXO方案下保持默认值，DCXO方案下根据实际系统进行调整。 */
        unsigned int  reserved         : 22; /* bit[10-31]: 保留 */
    } reg;
} GBBP_ADDR_AFC_K_VALUE_UNION;
#define GBBP_ADDR_AFC_K_VALUE_cpu_afc_k_factor_START  (0)
#define GBBP_ADDR_AFC_K_VALUE_cpu_afc_k_factor_END    (9)


/*****************************************************************************
 结构名    : GBBP_ADDR_NB_AFC_LOOP_SLOW_UNION
 结构说明  : ADDR_NB_AFC_LOOP_SLOW 寄存器结构定义。地址偏移量:0x5E14，初值:0x00024661，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_nb_afc_loop_slow_reg;
    struct
    {
        unsigned int  cpu_shiftr_kint_slow : 2;  /* bit[0-1]  : 慢速调整阶段环路滤波器系数Kint的右移位数。
                                                                0:8
                                                                1:9
                                                                2:10
                                                                3:11
                                                                默认配置:1 */
        unsigned int  reserved_0           : 2;  /* bit[2-3]  : 保留 */
        unsigned int  cpu_shiftr_ki_slow   : 3;  /* bit[4-6]  : 慢速调整阶段环路滤波器系数Ki的右移位数。
                                                                0:1
                                                                1:2
                                                                2:3
                                                                3:4
                                                                4:5
                                                                5:6
                                                                6:7
                                                                7:8
                                                                默认配置:6 */
        unsigned int  reserved_1           : 1;  /* bit[7]    : 保留 */
        unsigned int  cpu_shiftl_kp_slow   : 3;  /* bit[8-10] : 慢速调整阶段环路滤波器系数Kp的右移位数。
                                                                0:7
                                                                1:6
                                                                2:5
                                                                3:4
                                                                4:3
                                                                5:2
                                                                6:1
                                                                7:0
                                                                默认配置:6 */
        unsigned int  reserved_2           : 1;  /* bit[11]   : 保留 */
        unsigned int  cpu_shiftr_ka_slow   : 3;  /* bit[12-14]: 慢速调整阶段环路滤波器系数Ka的右移位数。
                                                                0：07；
                                                                1：08；
                                                                2：09；
                                                                3：10；
                                                                4：11；
                                                                5：12；
                                                                6：13；
                                                                7：14。
                                                                默认配置：4。 */
        unsigned int  reserved_3           : 1;  /* bit[15]   : 保留 */
        unsigned int  cpu_ka_slow          : 3;  /* bit[16-18]: 慢速调整阶段环路滤波器系数Ka。
                                                                0：16'd33141；
                                                                1：16'd22094；
                                                                2：16'd7365；
                                                                3：16'd4419；
                                                                4：16'd3682；
                                                                5：16'd3156；
                                                                6：16'd2455；
                                                                7：16'd2209。
                                                                默认配置：2。 */
        unsigned int  reserved_4           : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_ADDR_NB_AFC_LOOP_SLOW_UNION;
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_kint_slow_START  (0)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_kint_slow_END    (1)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ki_slow_START    (4)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ki_slow_END      (6)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftl_kp_slow_START    (8)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftl_kp_slow_END      (10)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ka_slow_START    (12)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ka_slow_END      (14)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_ka_slow_START           (16)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_ka_slow_END             (18)


/*****************************************************************************
 结构名    : GBBP_ADDR_NB_AFC_LOOP_FAST_UNION
 结构说明  : ADDR_NB_AFC_LOOP_FAST 寄存器结构定义。地址偏移量:0x5E18，初值:0x00023651，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_nb_afc_loop_fast_reg;
    struct
    {
        unsigned int  cpu_shiftr_kint_fast : 2;  /* bit[0-1]  : 快速调整阶段环路滤波器系数Kint的右移位数。
                                                                0:8
                                                                1:9
                                                                2:10
                                                                3:11
                                                                默认配置:1 */
        unsigned int  reserved_0           : 2;  /* bit[2-3]  : 保留 */
        unsigned int  cpu_shiftr_ki_fast   : 3;  /* bit[4-6]  : 快速调整阶段环路滤波器系数Ki的右移位数。
                                                                0:1
                                                                1:2
                                                                2:3
                                                                3:4
                                                                4:5
                                                                5:6
                                                                6:7
                                                                7:8
                                                                默认配置:1 */
        unsigned int  reserved_1           : 1;  /* bit[7]    : 保留 */
        unsigned int  cpu_shiftl_kp_fast   : 3;  /* bit[8-10] : 快速调整阶段环路滤波器系数Kp的左移位数。
                                                                0:7
                                                                1:6
                                                                2:5
                                                                3:4
                                                                4:3
                                                                5:2
                                                                6:1
                                                                7:0
                                                                默认配置:6 */
        unsigned int  reserved_2           : 1;  /* bit[11]   : 保留 */
        unsigned int  cpu_shiftr_ka_fast   : 3;  /* bit[12-14]: 快速调整阶段环路滤波器系数Ka的右移位数。
                                                                0：07；
                                                                1：08；
                                                                2：09；
                                                                3：10；
                                                                4：11；
                                                                5：12；
                                                                6：13；
                                                                7：14。
                                                                默认配置：3。 */
        unsigned int  reserved_3           : 1;  /* bit[15]   : 保留 */
        unsigned int  cpu_ka_fast          : 3;  /* bit[16-18]: 快速调整阶段环路滤波器系数Ka。
                                                                0:16’d33141
                                                                1:16’d22094
                                                                2:16’d7365
                                                                3:16’d4419
                                                                4:16’d3682
                                                                5:16’d3156
                                                                6:16’d2455
                                                                7:16’d2209
                                                                默认配置:2 */
        unsigned int  reserved_4           : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_ADDR_NB_AFC_LOOP_FAST_UNION;
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_kint_fast_START  (0)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_kint_fast_END    (1)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ki_fast_START    (4)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ki_fast_END      (6)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftl_kp_fast_START    (8)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftl_kp_fast_END      (10)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ka_fast_START    (12)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ka_fast_END      (14)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_ka_fast_START           (16)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_ka_fast_END             (18)


/*****************************************************************************
 结构名    : GBBP_ADDR_DEM_INT_FRQ_UNION
 结构说明  : ADDR_DEM_INT_FRQ 寄存器结构定义。地址偏移量:0x5E2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_dem_int_frq_reg;
    struct
    {
        unsigned int  dem_int_rssi_frq : 12; /* bit[0-11] : 本次解调中断时刻对应的频点 */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} GBBP_ADDR_DEM_INT_FRQ_UNION;
#define GBBP_ADDR_DEM_INT_FRQ_dem_int_rssi_frq_START  (0)
#define GBBP_ADDR_DEM_INT_FRQ_dem_int_rssi_frq_END    (11)


/*****************************************************************************
 结构名    : GBBP_ADDR_DEC_INT_FREQ_UNION
 结构说明  : ADDR_DEC_INT_FREQ 寄存器结构定义。地址偏移量:0x5E30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_dec_int_freq_reg;
    struct
    {
        unsigned int  dec_int_rssi_frq : 12; /* bit[0-11] : 本次译码中断上报时刻对应的频点信息 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  dec_int_tdma_qb  : 13; /* bit[16-28]: 本次译码中断上报时可对应的TDMA QB信息 */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_ADDR_DEC_INT_FREQ_UNION;
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_rssi_frq_START  (0)
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_rssi_frq_END    (11)
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_tdma_qb_START   (16)
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_tdma_qb_END     (28)


/*****************************************************************************
 结构名    : GBBP_ADDR_SRCH_INT_TDMA_QB_UNION
 结构说明  : ADDR_SRCH_INT_TDMA_QB 寄存器结构定义。地址偏移量:0x5E34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_srch_int_tdma_qb_reg;
    struct
    {
        unsigned int  srch_tdma_qb     : 13; /* bit[0-12] : 本次搜索中断上报时刻对应的TDMA QB */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: 保留 */
        unsigned int  srch_int_tdma_fn : 6;  /* bit[16-21]: [21:16] 6’b0 RO 本次中断上报时刻对应的TDMA帧号（gtc_t3_cnt） */
        unsigned int  reserved_1       : 10; /* bit[22-31]: 保留 */
    } reg;
} GBBP_ADDR_SRCH_INT_TDMA_QB_UNION;
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_tdma_qb_START      (0)
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_tdma_qb_END        (12)
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_int_tdma_fn_START  (16)
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_int_tdma_fn_END    (21)


/*****************************************************************************
 结构名    : GBBP_VALPP_CARRIER_ENERGY4_UNION
 结构说明  : VALPP_CARRIER_ENERGY4 寄存器结构定义。地址偏移量:0x532C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy4_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_4d_cpu : 31; /* bit[0-30]: 读取时刻前第五近burst对应的载波能量值，无符号数。 */
        unsigned int  reserved                    : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY4_UNION;
#define GBBP_VALPP_CARRIER_ENERGY4_valpp_carrier_energy_4d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY4_valpp_carrier_energy_4d_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_VALPP_INTERFERE_ENERGY4_UNION
 结构说明  : VALPP_INTERFERE_ENERGY4 寄存器结构定义。地址偏移量:0x5330，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy4_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_4d_cpu : 26; /* bit[0-25] : 读取时刻前第五近burst对应的干扰能量值，无符号数。 */
        unsigned int  reserved                      : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY4_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY4_valpp_interfere_energy_4d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY4_valpp_interfere_energy_4d_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_VALPP_DEM_TYPE_TOA4_UNION
 结构说明  : VALPP_DEM_TYPE_TOA4 寄存器结构定义。地址偏移量:0x5298，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa4_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : 保留 */
        unsigned int  mod_type_5d                    : 2;  /* bit[14-15]: 读取时刻第五近BURST的调制方式，
                                                                          0：GSKM；
                                                                          1：8PSK；
                                                                          2：DummyBurst。 */
        unsigned int  nb_pos_adj_cpu_sav4            : 4;  /* bit[16-19]: 读取时刻第五近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。 */
        unsigned int  demod_slot_5d                  : 3;  /* bit[20-22]: 读取时刻第五近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : 保留 */
        unsigned int  nserv_cell_ind_5d              : 1;  /* bit[24]   : 读取时刻第五近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: 保留 */
        unsigned int  mod_type_first_5d              : 2;  /* bit[28-29]: 读取时刻前的第五近BURST对应的一次判决的调制方式，
                                                                          0：GMSK调制；
                                                                          1：8PSK调制；
                                                                          2：DummyBurst。
                                                                          该寄存器测试使用。 */
        unsigned int  demod_info_valid_flag4_clr_imi : 1;  /* bit[30]   : 对demod_info_valid_flag4清零。写1清零。 */
        unsigned int  demod_info_valid_flag4         : 1;  /* bit[31]   : 读取时刻第五近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过写bit30对该bit清零，指示该信息已经读取。 */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA4_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_5d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_5d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA4_nb_pos_adj_cpu_sav4_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA4_nb_pos_adj_cpu_sav4_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_slot_5d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_slot_5d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA4_nserv_cell_ind_5d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA4_nserv_cell_ind_5d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_first_5d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_first_5d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_END            (31)


/*****************************************************************************
 结构名    : GBBP_VALPP_CARRIER_ENERGY5_UNION
 结构说明  : VALPP_CARRIER_ENERGY5 寄存器结构定义。地址偏移量:0x5334，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy5_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_5d_cpu : 31; /* bit[0-30]: 读取时刻前第六近burst对应的载波能量值，无符号数。 */
        unsigned int  reserved                    : 1;  /* bit[31]  : 保留 */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY5_UNION;
#define GBBP_VALPP_CARRIER_ENERGY5_valpp_carrier_energy_5d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY5_valpp_carrier_energy_5d_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_VALPP_INTERFERE_ENERGY5_UNION
 结构说明  : VALPP_INTERFERE_ENERGY5 寄存器结构定义。地址偏移量:0x5338，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy5_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_5d_cpu : 26; /* bit[0-25] : 读取时刻前第六近burst对应的干扰能量值，无符号数。 */
        unsigned int  reserved                      : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY5_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY5_valpp_interfere_energy_5d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY5_valpp_interfere_energy_5d_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_VALPP_DEM_TYPE_TOA5_UNION
 结构说明  : VALPP_DEM_TYPE_TOA5 寄存器结构定义。地址偏移量:0x533C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa5_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : 保留 */
        unsigned int  mod_type_6d                    : 2;  /* bit[14-15]: 读取时刻第六近BURST的调制方式，
                                                                          0：GSKM；
                                                                          1：8PSK；
                                                                          2：DummyBurst。 */
        unsigned int  nb_pos_adj_cpu_sav5            : 4;  /* bit[16-19]: 读取时刻第六近解调burst对应的NB位置调整量，是补码表示的有符号数，负数表示向前调整，正数表示向后调整，范围：-4~+4。 */
        unsigned int  demod_slot_6d                  : 3;  /* bit[20-22]: 读取时刻第六近解调burst对应的时隙号，该时隙号由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : 保留 */
        unsigned int  nserv_cell_ind_6d              : 1;  /* bit[24]   : 读取时刻第六近burst是否为非服务区指示，1表示非服务区，0表示服务区，默认值为0。该值由PHY通过GTC指令配置下来，BBP延时至解调中断处进行上报。 */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: 保留 */
        unsigned int  mod_type_first_6d              : 2;  /* bit[28-29]: 读取时刻前的第六近BURST对应的一次判决的调制方式，
                                                                          0：GMSK调制；
                                                                          1：8PSK调制；
                                                                          2：DummyBurst。
                                                                          该寄存器测试使用。 */
        unsigned int  demod_info_valid_flag5_clr_imi : 1;  /* bit[30]   : 对demod_info_valid_flag5清零。写1清零。 */
        unsigned int  demod_info_valid_flag5         : 1;  /* bit[31]   : 读取时刻第六近解调信息有效标志，当完成一次NB解调时，该标志置1,CPU读取完该BURST解调上报信息后，应该通过bit30对该bit清零，指示该信息已经读取。 */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA5_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_6d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_6d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA5_nb_pos_adj_cpu_sav5_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA5_nb_pos_adj_cpu_sav5_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_slot_6d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_slot_6d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA5_nserv_cell_ind_6d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA5_nserv_cell_ind_6d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_first_6d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_first_6d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_END            (31)


/*****************************************************************************
 结构名    : GBBP_CPU_JITTER_CORR_CFG1_UNION
 结构说明  : CPU_JITTER_CORR_CFG1 寄存器结构定义。地址偏移量:0x53B4，初值:0x80000303，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_jitter_corr_cfg1_reg;
    struct
    {
        unsigned int  cpu_jitter_on_ci_thresh : 3;  /* bit[0-2]  : 该门限用于解调模块内部，判决是否做纠偏 对应链路信号名CIThreshold，默认值10。
                                                                   可选值7,8,9,10,11,12,13，
                                                                   CPU数值对应关系：0-6。 */
        unsigned int  reserved_0              : 5;  /* bit[3-7]  : 保留 */
        unsigned int  cpu_energy_thresh       : 3;  /* bit[8-10] : 解调模块用，纠偏状态第一个子状态，判决是否满足纠偏条件. 对应链路信号名 EnergyThreshold：，默认值12。含义：通过信道估计计算全部能量和部分能量。可选值9,10, 11,12,13,14,15，
                                                                   CPU数值对应关系：0-6。 */
        unsigned int  reserved_1              : 12; /* bit[11-22]: 保留 */
        unsigned int  cpu_sin_factor          : 1;  /* bit[23]   : SB频偏值计算因子，0表示系数为1.25，1表示系数为1 */
        unsigned int  reserved_2              : 6;  /* bit[24-29]: 保留 */
        unsigned int  cpu_sb_freq_corr_en     : 1;  /* bit[30]   : SB纠偏使能信号，0表示关闭频偏检测及纠偏，1表示打开。
                                                                   V9R1/V3R3不支持该功能，必须配置为0。 */
        unsigned int  cpu_freq_corr_en        : 1;  /* bit[31]   : NB纠偏使能信号，0表示关闭频偏检测及纠偏，1表示打开。默认为0。 */
    } reg;
} GBBP_CPU_JITTER_CORR_CFG1_UNION;
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_jitter_on_ci_thresh_START  (0)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_jitter_on_ci_thresh_END    (2)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_energy_thresh_START        (8)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_energy_thresh_END          (10)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sin_factor_START           (23)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sin_factor_END             (23)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sb_freq_corr_en_START      (30)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sb_freq_corr_en_END        (30)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_freq_corr_en_START         (31)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_freq_corr_en_END           (31)


/*****************************************************************************
 结构名    : GBBP_PHI_DEV_CPU_UNION
 结构说明  : PHI_DEV_CPU 寄存器结构定义。地址偏移量:0x53B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      phi_dev_cpu_reg;
    struct
    {
        unsigned int  phi_dev_cpu    : 15; /* bit[0-14] : JITTER ON消除算法当前频偏上报 */
        unsigned int  reserved_0     : 1;  /* bit[15]   : 保留 */
        unsigned int  sb_phi_dev_cpu : 15; /* bit[16-30]: SB jitterOn算法当前频偏上报 */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留 */
    } reg;
} GBBP_PHI_DEV_CPU_UNION;
#define GBBP_PHI_DEV_CPU_phi_dev_cpu_START     (0)
#define GBBP_PHI_DEV_CPU_phi_dev_cpu_END       (14)
#define GBBP_PHI_DEV_CPU_sb_phi_dev_cpu_START  (16)
#define GBBP_PHI_DEV_CPU_sb_phi_dev_cpu_END    (30)


/*****************************************************************************
 结构名    : GBBP_CPU_JITTER_CORR_CFG2_UNION
 结构说明  : CPU_JITTER_CORR_CFG2 寄存器结构定义。地址偏移量:0x53BC，初值:0x80140702，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_jitter_corr_cfg2_reg;
    struct
    {
        unsigned int  cpu_snr_thresh     : 3;  /* bit[0-2]  : 对应于链路中的SNR_THRES，用于计算纠偏范围 fr_off_lim_act，以及调整参数, 默认值100, 取值范围90 95 100 105 110,CPU数值对应0～4 */
        unsigned int  reserved_0         : 5;  /* bit[3-7]  : 保留 */
        unsigned int  cpu_froff_lim_step : 4;  /* bit[8-11] : 对应于链路中的FrOffLim_STEP，取值范围5 6 7 8 9，默认值是7 */
        unsigned int  reserved_1         : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_frmoff_lim     : 5;  /* bit[16-20]: 软件和芯片都用，对偏差限幅。对应链路信号 FrOffLim 。默认值20，可选值14,16,18,20,22, 24； */
        unsigned int  reserved_2         : 10; /* bit[21-30]: 保留 */
        unsigned int  cpu_feed_back_en   : 1;  /* bit[31]   : NB频偏校准范围继承使能，默认值是1。 */
    } reg;
} GBBP_CPU_JITTER_CORR_CFG2_UNION;
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_snr_thresh_START      (0)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_snr_thresh_END        (2)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_froff_lim_step_START  (8)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_froff_lim_step_END    (11)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_frmoff_lim_START      (16)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_frmoff_lim_END        (20)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_feed_back_en_START    (31)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_feed_back_en_END      (31)


/*****************************************************************************
 结构名    : GBBP_CPU_TSC_SWITCH_EN_UNION
 结构说明  : CPU_TSC_SWITCH_EN 寄存器结构定义。地址偏移量:0x53C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_tsc_switch_en_reg;
    struct
    {
        unsigned int  cpu_tsc_page_switch_en : 1;  /* bit[0]   : 软件规避模式下响应解调中断后读取训练序列数据上报RAM的上报机制控制,多时隙下需使用乒乓操作模式
                                                                 1表示CPU访问训练序列数据上报RAM采用乒乓RAM访问模式，
                                                                 0表示CPU访问训练序列数据上报RAM采用非乒乓RAM访问模式 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_TSC_SWITCH_EN_UNION;
#define GBBP_CPU_TSC_SWITCH_EN_cpu_tsc_page_switch_en_START  (0)
#define GBBP_CPU_TSC_SWITCH_EN_cpu_tsc_page_switch_en_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER0_P0_P1_UNION
 结构说明  : CPU_FILTER0_P0_P1 寄存器结构定义。地址偏移量:0x5800，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter0_p0_p1_reg;
    struct
    {
        unsigned int  cpu_filter0_p0_i : 14; /* bit[0-13] : 滤波器0，I路参数p0，默认值：14'd0。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter0_p1_i : 14; /* bit[16-29]: 滤波器0，I路参数p1，默认值：14'd0。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER0_P0_P1_UNION;
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p0_i_START  (0)
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p0_i_END    (13)
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p1_i_START  (16)
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p1_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER0_P2_P3_UNION
 结构说明  : CPU_FILTER0_P2_P3 寄存器结构定义。地址偏移量:0x5804，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter0_p2_p3_reg;
    struct
    {
        unsigned int  cpu_filter0_p2_i : 14; /* bit[0-13] : 滤波器0，I路参数p2，默认值：14'd0。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter0_p3_i : 14; /* bit[16-29]: 滤波器0，I路参数p3，默认值：14'd0。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER0_P2_P3_UNION;
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p2_i_START  (0)
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p2_i_END    (13)
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p3_i_START  (16)
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p3_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER0_P4_P5_UNION
 结构说明  : CPU_FILTER0_P4_P5 寄存器结构定义。地址偏移量:0x5808，初值:0x10000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter0_p4_p5_reg;
    struct
    {
        unsigned int  cpu_filter0_p4_i : 14; /* bit[0-13] : 滤波器0，I路参数p4，默认值：14'd0。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter0_p5_i : 14; /* bit[16-29]: 滤波器0，I路参数p5，默认值：14'd4096。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER0_P4_P5_UNION;
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p4_i_START  (0)
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p4_i_END    (13)
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p5_i_START  (16)
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p5_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER3_P0_P1_UNION
 结构说明  : CPU_FILTER3_P0_P1 寄存器结构定义。地址偏移量:0x580C，初值:0x3F8F3F59，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter3_p0_p1_reg;
    struct
    {
        unsigned int  cpu_filter3_p0_i : 14; /* bit[0-13] : 滤波器3，I路参数p0，默认值：-14'd167。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter3_p1_i : 14; /* bit[16-29]: 滤波器3，I路参数p1，默认值：-14'd113。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER3_P0_P1_UNION;
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p0_i_START  (0)
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p0_i_END    (13)
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p1_i_START  (16)
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p1_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER3_P2_P3_UNION
 结构说明  : CPU_FILTER3_P2_P3 寄存器结构定义。地址偏移量:0x5810，初值:0x03FA3EEF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter3_p2_p3_reg;
    struct
    {
        unsigned int  cpu_filter3_p2_i : 14; /* bit[0-13] : 滤波器3，I路参数p2，默认值：-14'd273。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter3_p3_i : 14; /* bit[16-29]: 滤波器3，I路参数p3，默认值：14'd1018。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER3_P2_P3_UNION;
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p2_i_START  (0)
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p2_i_END    (13)
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p3_i_START  (16)
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p3_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER3_P4_P5_UNION
 结构说明  : CPU_FILTER3_P4_P5 寄存器结构定义。地址偏移量:0x5814，初值:0x08B40179，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter3_p4_p5_reg;
    struct
    {
        unsigned int  cpu_filter3_p4_i : 14; /* bit[0-13] : 滤波器3，I路参数p4，默认值：14'd377。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter3_p5_i : 14; /* bit[16-29]: 滤波器3，I路参数p5，默认值：14'd2228。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER3_P4_P5_UNION;
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p4_i_START  (0)
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p4_i_END    (13)
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p5_i_START  (16)
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p5_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER1_P0_P1_I_UNION
 结构说明  : CPU_FILTER1_P0_P1_I 寄存器结构定义。地址偏移量:0x5818，初值:0x00A80011，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p0_p1_i_reg;
    struct
    {
        unsigned int  cpu_filter1_p0_i : 14; /* bit[0-13] : 滤波器1，I路参数p0，默认值：14'd17。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter1_p1_i : 14; /* bit[16-29]: 滤波器1，I路参数p1，默认值：14'd168。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER1_P0_P1_I_UNION;
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p0_i_START  (0)
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p0_i_END    (13)
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p1_i_START  (16)
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p1_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER1_P2_P3_I_UNION
 结构说明  : CPU_FILTER1_P2_P3_I 寄存器结构定义。地址偏移量:0x581C，初值:0x00B90016，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p2_p3_i_reg;
    struct
    {
        unsigned int  cpu_filter1_p2_i : 14; /* bit[0-13] : 滤波器1，I路参数p2，默认值：14'd22。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter1_p3_i : 14; /* bit[16-29]: 滤波器1，I路参数p3，默认值：14'd185。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER1_P2_P3_I_UNION;
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p2_i_START  (0)
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p2_i_END    (13)
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p3_i_START  (16)
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p3_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER1_P4_P5_I_UNION
 结构说明  : CPU_FILTER1_P4_P5_I 寄存器结构定义。地址偏移量:0x5820，初值:0x06CA045C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p4_p5_i_reg;
    struct
    {
        unsigned int  cpu_filter1_p4_i : 14; /* bit[0-13] : 滤波器1，I路参数p4，默认值：14'd1116。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter1_p5_i : 14; /* bit[16-29]: 滤波器1，I路参数p5，默认值：14'd1738。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER1_P4_P5_I_UNION;
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p4_i_START  (0)
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p4_i_END    (13)
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p5_i_START  (16)
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p5_i_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER1_P0_P1_Q_UNION
 结构说明  : CPU_FILTER1_P0_P1_Q 寄存器结构定义。地址偏移量:0x5824，初值:0x00DB0006，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p0_p1_q_reg;
    struct
    {
        unsigned int  cpu_filter1_p0_q : 14; /* bit[0-13] : 滤波器1，Q路参数p0，默认值：14'd6。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter1_p1_q : 14; /* bit[16-29]: 滤波器1，Q路参数p1，默认值：14'd219。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER1_P0_P1_Q_UNION;
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p0_q_START  (0)
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p0_q_END    (13)
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p1_q_START  (16)
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p1_q_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER1_P2_P3_Q_UNION
 结构说明  : CPU_FILTER1_P2_P3_Q 寄存器结构定义。地址偏移量:0x5828，初值:0x3E8700DB，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p2_p3_q_reg;
    struct
    {
        unsigned int  cpu_filter1_p2_q : 14; /* bit[0-13] : 滤波器1，Q路参数p2，默认值：14'd219。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter1_p3_q : 14; /* bit[16-29]: 滤波器1，Q路参数p3，默认值：-14'd377。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER1_P2_P3_Q_UNION;
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p2_q_START  (0)
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p2_q_END    (13)
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p3_q_START  (16)
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p3_q_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_FILTER1_P4_P5_Q_UNION
 结构说明  : CPU_FILTER1_P4_P5_Q 寄存器结构定义。地址偏移量:0x582C，初值:0x00003D4A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p4_p5_q_reg;
    struct
    {
        unsigned int  cpu_filter1_p4_q : 14; /* bit[0-13] : 滤波器1，Q路参数p4，默认值：-14'd694。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_filter1_p5_q : 14; /* bit[16-29]: 滤波器1，Q路参数p5，默认值：14'd0。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_FILTER1_P4_P5_Q_UNION;
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p4_q_START  (0)
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p4_q_END    (13)
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p5_q_START  (16)
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p5_q_END    (29)


/*****************************************************************************
 结构名    : GBBP_CPU_GACI_DATA_BYPASS_UNION
 结构说明  : CPU_GACI_DATA_BYPASS 寄存器结构定义。地址偏移量:0x5880，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gaci_data_bypass_reg;
    struct
    {
        unsigned int  cpu_gaci_data_bypass : 1;  /* bit[0]   : 1：dagc输入数据不经滤波器处理直接输出
                                                               0：dagc输入数据经滤波器处理后输出 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_CPU_GACI_DATA_BYPASS_UNION;
#define GBBP_CPU_GACI_DATA_BYPASS_cpu_gaci_data_bypass_START  (0)
#define GBBP_CPU_GACI_DATA_BYPASS_cpu_gaci_data_bypass_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_GACI_PARA_UNION
 结构说明  : CPU_GACI_PARA 寄存器结构定义。地址偏移量:0x5884，初值:0x00010003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gaci_para_reg;
    struct
    {
        unsigned int  cpu_gaci_tpower : 3;  /* bit[0-2]  : 判决可配置门限
                                                           3’b000:   2
                                                           3’b001:   3
                                                           3’b010:   4
                                                           3’b011:   5
                                                           3’b100:   6
                                                           3’b101:   7
                                                           3’b110:   8
                                                           3’b111:   9
                                                           默认值:   5 */
        unsigned int  reserved_0      : 13; /* bit[3-15] : 保留 */
        unsigned int  cpu_gaci_taci   : 3;  /* bit[16-18]: 判决可配置门限
                                                           3’b000:   5
                                                           3’b001:   6
                                                           3’b010:   7
                                                           3’b011:   8
                                                           3’b100:   9
                                                           3’b101:   10
                                                           默认值:   6 */
        unsigned int  reserved_1      : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_CPU_GACI_PARA_UNION;
#define GBBP_CPU_GACI_PARA_cpu_gaci_tpower_START  (0)
#define GBBP_CPU_GACI_PARA_cpu_gaci_tpower_END    (2)
#define GBBP_CPU_GACI_PARA_cpu_gaci_taci_START    (16)
#define GBBP_CPU_GACI_PARA_cpu_gaci_taci_END      (18)


/*****************************************************************************
 结构名    : GBBP_GACI_INDEX_CPU_UNION
 结构说明  : GACI_INDEX_CPU 寄存器结构定义。地址偏移量:0x58A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_index_cpu_reg;
    struct
    {
        unsigned int  gaci_index_cpu : 2;  /* bit[0-1] : 输出邻频检测结果，上报CPU四种可能的干扰状态：
                                                         2’b00：无干扰
                                                         2’b01：+200Khz干扰
                                                         2’b10：-200Khz干扰
                                                         2’b11： 200Khz干扰 */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} GBBP_GACI_INDEX_CPU_UNION;
#define GBBP_GACI_INDEX_CPU_gaci_index_cpu_START  (0)
#define GBBP_GACI_INDEX_CPU_gaci_index_cpu_END    (1)


/*****************************************************************************
 结构名    : GBBP_GACI_RACI_CPU_UNION
 结构说明  : GACI_RACI_CPU 寄存器结构定义。地址偏移量:0x58A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_raci_cpu_reg;
    struct
    {
        unsigned int  raci_cpu : 26; /* bit[0-25] : GACI参数，由ematrix_03_cpu_cpu与ematrix_12_cpu产生 */
        unsigned int  reserved : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_GACI_RACI_CPU_UNION;
#define GBBP_GACI_RACI_CPU_raci_cpu_START  (0)
#define GBBP_GACI_RACI_CPU_raci_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_GACI_RPOWER_CPU_UNION
 结构说明  : GACI_RPOWER_CPU 寄存器结构定义。地址偏移量:0x58A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_rpower_cpu_reg;
    struct
    {
        unsigned int  rpower_cpu : 26; /* bit[0-25] : GACI参数，在EMATRIX状态下产生的判决参数，由经过高通后数据求能量产生。 */
        unsigned int  reserved   : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_GACI_RPOWER_CPU_UNION;
#define GBBP_GACI_RPOWER_CPU_rpower_cpu_START  (0)
#define GBBP_GACI_RPOWER_CPU_rpower_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_GACI_EMATRIX_03_CPU_UNION
 结构说明  : GACI_EMATRIX_03_CPU 寄存器结构定义。地址偏移量:0x58AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_ematrix_03_cpu_reg;
    struct
    {
        unsigned int  ematrix_03_cpu : 26; /* bit[0-25] : GACI参数，在EMATRIX状态下产生的判决参数，由经过高通后数据求相关产生。 */
        unsigned int  reserved       : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_GACI_EMATRIX_03_CPU_UNION;
#define GBBP_GACI_EMATRIX_03_CPU_ematrix_03_cpu_START  (0)
#define GBBP_GACI_EMATRIX_03_CPU_ematrix_03_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_GACI_EMATRIX_12_CPU_UNION
 结构说明  : GACI_EMATRIX_12_CPU 寄存器结构定义。地址偏移量:0x58B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_ematrix_12_cpu_reg;
    struct
    {
        unsigned int  ematrix_12_cpu : 26; /* bit[0-25] : GACI参数，在EMATRIX状态下产生的判决参数，由经过高通后数据求相关产生。 */
        unsigned int  reserved       : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_GACI_EMATRIX_12_CPU_UNION;
#define GBBP_GACI_EMATRIX_12_CPU_ematrix_12_cpu_START  (0)
#define GBBP_GACI_EMATRIX_12_CPU_ematrix_12_cpu_END    (25)


/*****************************************************************************
 结构名    : GBBP_GACI_AVG_ALL_CPU_UNION
 结构说明  : GACI_AVG_ALL_CPU 寄存器结构定义。地址偏移量:0x58B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_avg_all_cpu_reg;
    struct
    {
        unsigned int  avg_all_cpu : 21; /* bit[0-20] : GACI未经过高通处理，原输入数据能量，在ENERGY1状态产生 */
        unsigned int  reserved    : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_GACI_AVG_ALL_CPU_UNION;
#define GBBP_GACI_AVG_ALL_CPU_avg_all_cpu_START  (0)
#define GBBP_GACI_AVG_ALL_CPU_avg_all_cpu_END    (20)


/*****************************************************************************
 结构名    : GBBP_GACI_AVG_HP_CPU_UNION
 结构说明  : GACI_AVG_HP_CPU 寄存器结构定义。地址偏移量:0x58B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_avg_hp_cpu_reg;
    struct
    {
        unsigned int  avg_hp_cpu : 21; /* bit[0-20] : GACI经过高通处理，原输入数据能量，在ENERGY2状态产生 */
        unsigned int  reserved   : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_GACI_AVG_HP_CPU_UNION;
#define GBBP_GACI_AVG_HP_CPU_avg_hp_cpu_START  (0)
#define GBBP_GACI_AVG_HP_CPU_avg_hp_cpu_END    (20)


/*****************************************************************************
 结构名    : GBBP_CPU_AMR_CRC_PRO_NUM_CFG_UNION
 结构说明  : CPU_AMR_CRC_PRO_NUM_CFG 寄存器结构定义。地址偏移量:0x53CC，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_crc_pro_num_cfg_reg;
    struct
    {
        unsigned int  cpu_amr_crc_prot_num : 2;  /* bit[0-1] : AMR带内bit优化算法中针对SPEECH CRC的保护次数，配置范围0～3，代表保护次数为1～4，默认值为3
                                                               （当业务类型为GMSK WBAMR时，配置范围为0～2） */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} GBBP_CPU_AMR_CRC_PRO_NUM_CFG_UNION;
#define GBBP_CPU_AMR_CRC_PRO_NUM_CFG_cpu_amr_crc_prot_num_START  (0)
#define GBBP_CPU_AMR_CRC_PRO_NUM_CFG_cpu_amr_crc_prot_num_END    (1)


/*****************************************************************************
 结构名    : GBBP_CPU_P0_PRIOR_REG_CFG_UNION
 结构说明  : CPU_P0_PRIOR_REG_CFG 寄存器结构定义。地址偏移量:0x53D0，初值:0x001FFFEB，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p0_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p0_prior : 21; /* bit[0-20] : AMR带内bit优化算法中00对应的先验概率 */
        unsigned int  reserved     : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_CPU_P0_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P0_PRIOR_REG_CFG_cpu_p0_prior_START  (0)
#define GBBP_CPU_P0_PRIOR_REG_CFG_cpu_p0_prior_END    (20)


/*****************************************************************************
 结构名    : GBBP_CPU_P1_PRIOR_REG_CFG_UNION
 结构说明  : CPU_P1_PRIOR_REG_CFG 寄存器结构定义。地址偏移量:0x53D4，初值:0x001FFAA0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p1_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p1_prior : 21; /* bit[0-20] : AMR带内bit优化算法中01对应的先验概率 */
        unsigned int  reserved     : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_CPU_P1_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P1_PRIOR_REG_CFG_cpu_p1_prior_START  (0)
#define GBBP_CPU_P1_PRIOR_REG_CFG_cpu_p1_prior_END    (20)


/*****************************************************************************
 结构名    : GBBP_CPU_P2_PRIOR_REG_CFG_UNION
 结构说明  : CPU_P2_PRIOR_REG_CFG 寄存器结构定义。地址偏移量:0x53D8，初值:0x001FFFD6，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p2_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p2_prior : 21; /* bit[0-20] : AMR带内bit优化算法中10对应的先验概率 */
        unsigned int  reserved     : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_CPU_P2_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P2_PRIOR_REG_CFG_cpu_p2_prior_START  (0)
#define GBBP_CPU_P2_PRIOR_REG_CFG_cpu_p2_prior_END    (20)


/*****************************************************************************
 结构名    : GBBP_CPU_P3_PRIOR_REG_CFG_UNION
 结构说明  : CPU_P3_PRIOR_REG_CFG 寄存器结构定义。地址偏移量:0x53DC，初值:0x001FFAA0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p3_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p3_prior : 21; /* bit[0-20] : AMR带内bit优化算法中11对应的先验概率
                                                        AFS下算法推荐配置为-6000，AHS下算法推荐配置为-4000 */
        unsigned int  reserved     : 11; /* bit[21-31]: 保留 */
    } reg;
} GBBP_CPU_P3_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P3_PRIOR_REG_CFG_cpu_p3_prior_START  (0)
#define GBBP_CPU_P3_PRIOR_REG_CFG_cpu_p3_prior_END    (20)


/*****************************************************************************
 结构名    : GBBP_CMI_P01_PRIOR_PRE_RPT_UNION
 结构说明  : CMI_P01_PRIOR_PRE_RPT 寄存器结构定义。地址偏移量:0x5380，初值:0x00010001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cmi_p01_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_0_cmi : 16; /* bit[0-15] : CMI带内bit 0对应的先验概率上报 */
        unsigned int  mappre_1_cmi : 16; /* bit[16-31]: CMI带内bit 1对应的先验概率上报 */
    } reg;
} GBBP_CMI_P01_PRIOR_PRE_RPT_UNION;
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_0_cmi_START  (0)
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_0_cmi_END    (15)
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_1_cmi_START  (16)
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_1_cmi_END    (31)


/*****************************************************************************
 结构名    : GBBP_CMI_P23_PRIOR_PRE_RPT_UNION
 结构说明  : CMI_P23_PRIOR_PRE_RPT 寄存器结构定义。地址偏移量:0x5384，初值:0x00010001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cmi_p23_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_2_cmi : 16; /* bit[0-15] : CMI带内bit 2对应的先验概率上报 */
        unsigned int  mappre_3_cmi : 16; /* bit[16-31]: CMI带内bit 3对应的先验概率上报 */
    } reg;
} GBBP_CMI_P23_PRIOR_PRE_RPT_UNION;
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_2_cmi_START  (0)
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_2_cmi_END    (15)
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_3_cmi_START  (16)
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_3_cmi_END    (31)


/*****************************************************************************
 结构名    : GBBP_CMC_P01_PRIOR_PRE_RPT_UNION
 结构说明  : CMC_P01_PRIOR_PRE_RPT 寄存器结构定义。地址偏移量:0x5388，初值:0x00010001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cmc_p01_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_0_cmc : 16; /* bit[0-15] : CMC带内bit 0对应的先验概率上报 */
        unsigned int  mappre_1_cmc : 16; /* bit[16-31]: CMC带内bit 1对应的先验概率上报 */
    } reg;
} GBBP_CMC_P01_PRIOR_PRE_RPT_UNION;
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_0_cmc_START  (0)
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_0_cmc_END    (15)
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_1_cmc_START  (16)
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_1_cmc_END    (31)


/*****************************************************************************
 结构名    : GBBP_CMC_P23_PRIOR_PRE_RPT_UNION
 结构说明  : CMC_P23_PRIOR_PRE_RPT 寄存器结构定义。地址偏移量:0x538C，初值:0x00010001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cmc_p23_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_2_cmc : 16; /* bit[0-15] : CMC带内bit 2对应的先验概率上报 */
        unsigned int  mappre_3_cmc : 16; /* bit[16-31]: CMC带内bit 3对应的先验概率上报 */
    } reg;
} GBBP_CMC_P23_PRIOR_PRE_RPT_UNION;
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_2_cmc_START  (0)
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_2_cmc_END    (15)
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_3_cmc_START  (16)
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_3_cmc_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_P01_MAPPRE_CFG_UNION
 结构说明  : CPU_P01_MAPPRE_CFG 寄存器结构定义。地址偏移量:0x5390，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p01_mappre_cfg_reg;
    struct
    {
        unsigned int  cpu_p0_mappre : 16; /* bit[0-15] : CMC或者CMI 带内bit 0对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率 */
        unsigned int  cpu_p1_mappre : 16; /* bit[16-31]: CMC或者CMI 带内bit 1对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率 */
    } reg;
} GBBP_CPU_P01_MAPPRE_CFG_UNION;
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p0_mappre_START  (0)
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p0_mappre_END    (15)
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p1_mappre_START  (16)
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p1_mappre_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_P23_MAPPRE_CFG_UNION
 结构说明  : CPU_P23_MAPPRE_CFG 寄存器结构定义。地址偏移量:0x5394，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p23_mappre_cfg_reg;
    struct
    {
        unsigned int  cpu_p2_mappre : 16; /* bit[0-15] : CMC或者CMI 带内bit 2对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率 */
        unsigned int  cpu_p3_mappre : 16; /* bit[16-31]: CMC或者CMI 带内bit 3对应的历史先验概率值，用于恢复GBBP的CMC或者CMI先验概率 */
    } reg;
} GBBP_CPU_P23_MAPPRE_CFG_UNION;
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p2_mappre_START  (0)
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p2_mappre_END    (15)
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p3_mappre_START  (16)
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p3_mappre_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_CMC_CMI_LOAD_EN_UNION
 结构说明  : CPU_CMC_CMI_LOAD_EN 寄存器结构定义。地址偏移量:0x5398，初值:0x00360000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_cmc_cmi_load_en_reg;
    struct
    {
        unsigned int  cpu_cmi_cmc_mappre_load_en_imi : 1;  /* bit[0]    : 1标识需要做加载CMI或者CMC的历史先验概率，该信号配置之前需要软件先配置CPU_P01_MAPPRE_CFG，CPU_P23_MAPPRE_CFG寄存器 */
        unsigned int  cpu_cmi_cmc_mappre_load_mode   : 1;  /* bit[1]    : 0标识加载CMI的历史先验概率，1标识加载CMC的历史先验概率 */
        unsigned int  cpu_nodata_judge_mode          : 1;  /* bit[2]    : 1标识采用C02通过状态来判决NODATA的模式
                                                                          0标识采用V3 AMR相关译码的判决方式。 */
        unsigned int  reserved_0                     : 5;  /* bit[3-7]  : 保留 */
        unsigned int  dec_cmc_cmi_rpt                : 1;  /* bit[8]    : 1标识当前译码中断所在周期是CMC周期
                                                                          0标识当前译码中断所在周期是CMI周期。 */
        unsigned int  reserved_1                     : 7;  /* bit[9-15] : 保留 */
        unsigned int  cpu_amr_corr_thresh            : 14; /* bit[16-29]: AMR判决算法中绝对门限，AFS推荐值为233，AHS推荐值为230 */
        unsigned int  reserved_2                     : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CPU_CMC_CMI_LOAD_EN_UNION;
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_en_imi_START  (0)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_en_imi_END    (0)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_mode_START    (1)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_mode_END      (1)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_nodata_judge_mode_START           (2)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_nodata_judge_mode_END             (2)
#define GBBP_CPU_CMC_CMI_LOAD_EN_dec_cmc_cmi_rpt_START                 (8)
#define GBBP_CPU_CMC_CMI_LOAD_EN_dec_cmc_cmi_rpt_END                   (8)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_amr_corr_thresh_START             (16)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_amr_corr_thresh_END               (29)


/*****************************************************************************
 结构名    : GBBP_AMR_INFO1_RPT_UNION
 结构说明  : AMR_INFO1_RPT 寄存器结构定义。地址偏移量:0x53F8，初值:0x20003F3F，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      amr_info1_rpt_reg;
    struct
    {
        unsigned int  dcu_amr_frame_type : 6;  /* bit[0-5]  : AMR译码帧类型上报 */
        unsigned int  reserved_0         : 2;  /* bit[6-7]  : 保留 */
        unsigned int  max_sum_frame_type : 6;  /* bit[8-13] : AMR相关最大帧类型上报 */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: 保留 */
        unsigned int  corr_max_sum       : 14; /* bit[16-29]: AMR相关最大帧类型相关累加和上报 */
        unsigned int  reserved_2         : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_AMR_INFO1_RPT_UNION;
#define GBBP_AMR_INFO1_RPT_dcu_amr_frame_type_START  (0)
#define GBBP_AMR_INFO1_RPT_dcu_amr_frame_type_END    (5)
#define GBBP_AMR_INFO1_RPT_max_sum_frame_type_START  (8)
#define GBBP_AMR_INFO1_RPT_max_sum_frame_type_END    (13)
#define GBBP_AMR_INFO1_RPT_corr_max_sum_START        (16)
#define GBBP_AMR_INFO1_RPT_corr_max_sum_END          (29)


/*****************************************************************************
 结构名    : GBBP_AMR_INFO2_RPT_UNION
 结构说明  : AMR_INFO2_RPT 寄存器结构定义。地址偏移量:0x53FC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      amr_info2_rpt_reg;
    struct
    {
        unsigned int  abs_sum_g_corr_max_sum    : 1;  /* bit[0]   : AMR判决算法公式上报 */
        unsigned int  abs_sum_le_corr_rat_sum   : 1;  /* bit[1]   : AMR判决算法公式上报 */
        unsigned int  abs_sum_le_corr_onset_sum : 1;  /* bit[2]   : AMR判决算法公式上报 */
        unsigned int  reserved                  : 29; /* bit[3-31]: 保留 */
    } reg;
} GBBP_AMR_INFO2_RPT_UNION;
#define GBBP_AMR_INFO2_RPT_abs_sum_g_corr_max_sum_START     (0)
#define GBBP_AMR_INFO2_RPT_abs_sum_g_corr_max_sum_END       (0)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_rat_sum_START    (1)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_rat_sum_END      (1)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_onset_sum_START  (2)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_onset_sum_END    (2)


/*****************************************************************************
 结构名    : GBBP_CPU_AMR_CORR_COEFF_CFG_UNION
 结构说明  : CPU_AMR_CORR_COEFF_CFG 寄存器结构定义。地址偏移量:0x53E0，初值:0x0000000A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_corr_coeff_cfg_reg;
    struct
    {
        unsigned int  cpu_amr_corr_coeff : 4;  /* bit[0-3] : AFS/AHS 相关译码判决公式门限参数，配置范围0～15，推荐配置为10 */
        unsigned int  reserved           : 28; /* bit[4-31]: 保留 */
    } reg;
} GBBP_CPU_AMR_CORR_COEFF_CFG_UNION;
#define GBBP_CPU_AMR_CORR_COEFF_CFG_cpu_amr_corr_coeff_START  (0)
#define GBBP_CPU_AMR_CORR_COEFF_CFG_cpu_amr_corr_coeff_END    (3)


/*****************************************************************************
 结构名    : GBBP_CODEC_WR_CONFLICT_CNT_UNION
 结构说明  : CODEC_WR_CONFLICT_CNT 寄存器结构定义。地址偏移量:0x5718，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_wr_conflict_cnt_reg;
    struct
    {
        unsigned int  codec_conflict_cnt_cpu    : 8;  /* bit[0-7]  : [3:0] 编码过程中启动了下行译码配置冲突计数器上报
                                                                     [7:4]：译码过程中启动了上行编码配置冲突计数器上报 */
        unsigned int  reserved                  : 8;  /* bit[8-15] : 保留 */
        unsigned int  valpp_wr_conflict_cnt_cpu : 16; /* bit[16-31]: VALPP RAM单口访问冲突计数器
                                                                     [31:28] DEM和CARRY过程发生读，写冲突
                                                                     [27:20]  DEMAP和MAP过程发生读，写冲突
                                                                     [23:20] DEMAP和CARRY过程发生读，写冲突
                                                                     [19:16] DEMAP和DEM模块发生读，写冲突 */
    } reg;
} GBBP_CODEC_WR_CONFLICT_CNT_UNION;
#define GBBP_CODEC_WR_CONFLICT_CNT_codec_conflict_cnt_cpu_START     (0)
#define GBBP_CODEC_WR_CONFLICT_CNT_codec_conflict_cnt_cpu_END       (7)
#define GBBP_CODEC_WR_CONFLICT_CNT_valpp_wr_conflict_cnt_cpu_START  (16)
#define GBBP_CODEC_WR_CONFLICT_CNT_valpp_wr_conflict_cnt_cpu_END    (31)


/*****************************************************************************
 结构名    : GBBP_ADDR_HARQ_MODE_UNION
 结构说明  : ADDR_HARQ_MODE 寄存器结构定义。地址偏移量:0x5A00，初值:0x00010001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_harq_mode_reg;
    struct
    {
        unsigned int  cpu_harq_external_mode : 1;  /* bit[0]    : HARQ内置模式与外置模式选择信号，1表示使用外置模式，0表示使用内置模式。 */
        unsigned int  reserved_0             : 15; /* bit[1-15] : 保留 */
        unsigned int  cpu_harq_ddr_mode      : 1;  /* bit[16]   : HARQ外置模式下，是否根据CRC结果对外置DDR进行访问，1表示不管CRC结果，强行将数据存入HARQ MEM，0表示根据CRC结果将数据存入HARQ MEM。 */
        unsigned int  reserved_1             : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_ADDR_HARQ_MODE_UNION;
#define GBBP_ADDR_HARQ_MODE_cpu_harq_external_mode_START  (0)
#define GBBP_ADDR_HARQ_MODE_cpu_harq_external_mode_END    (0)
#define GBBP_ADDR_HARQ_MODE_cpu_harq_ddr_mode_START       (16)
#define GBBP_ADDR_HARQ_MODE_cpu_harq_ddr_mode_END         (16)


/*****************************************************************************
 结构名    : GBBP_ADDR_HARQ_INIT_EN_UNION
 结构说明  : ADDR_HARQ_INIT_EN 寄存器结构定义。地址偏移量:0x5A04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_harq_init_en_reg;
    struct
    {
        unsigned int  cpu_harq_init_en : 1;  /* bit[0]   : HARQ外置模式下，异常复位信号，脉冲信号，写1复位。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_ADDR_HARQ_INIT_EN_UNION;
#define GBBP_ADDR_HARQ_INIT_EN_cpu_harq_init_en_START  (0)
#define GBBP_ADDR_HARQ_INIT_EN_cpu_harq_init_en_END    (0)


/*****************************************************************************
 结构名    : GBBP_ADDR_DDR_HARQ_CFG_UNION
 结构说明  : ADDR_DDR_HARQ_CFG 寄存器结构定义。地址偏移量:0x5A10，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_ddr_harq_cfg_reg;
    struct
    {
        unsigned int  g_beat_num       : 4;  /* bit[0-3]  : HARQ外置模式下，DDR每次写FIFO的burst长度。 */
        unsigned int  reserved_0       : 12; /* bit[4-15] : 保留 */
        unsigned int  dec_int_type_cpu : 4;  /* bit[16-19]: HARQ外置模式下，译码中断异常状态上报值。
                                                            1’b1：译码超时
                                                            1’b0：译码未超时 */
        unsigned int  reserved_1       : 12; /* bit[20-31]: 保留 */
    } reg;
} GBBP_ADDR_DDR_HARQ_CFG_UNION;
#define GBBP_ADDR_DDR_HARQ_CFG_g_beat_num_START        (0)
#define GBBP_ADDR_DDR_HARQ_CFG_g_beat_num_END          (3)
#define GBBP_ADDR_DDR_HARQ_CFG_dec_int_type_cpu_START  (16)
#define GBBP_ADDR_DDR_HARQ_CFG_dec_int_type_cpu_END    (19)


/*****************************************************************************
 结构名    : GBBP_ADDR_TX_RRC_PILTER_EN_UNION
 结构说明  : ADDR_TX_RRC_PILTER_EN 寄存器结构定义。地址偏移量:0x5A14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_tx_rrc_pilter_en_reg;
    struct
    {
        unsigned int  cpu_tx_rrc_filter_en : 1;  /* bit[0]   : 数字滤波器使能信号，用来控制调制后数据是否经过16阶数字滤波器；默认值：0。 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_ADDR_TX_RRC_PILTER_EN_UNION;
#define GBBP_ADDR_TX_RRC_PILTER_EN_cpu_tx_rrc_filter_en_START  (0)
#define GBBP_ADDR_TX_RRC_PILTER_EN_cpu_tx_rrc_filter_en_END    (0)


/*****************************************************************************
 结构名    : GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_UNION
 结构说明  : ADDR_HARQ_RAM_WR_EN_BYPASS 寄存器结构定义。地址偏移量:0x5A18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_harq_ram_wr_en_bypass_reg;
    struct
    {
        unsigned int  cpu_harq_ram_wr_en_bypass : 1;  /* bit[0]   : HARQ外置模式下，Harq Ram写使能超时保护旁路信号。此信号生效表示Harq Ram写使能不做超时保护。默认值为0，表示进行超时保护。 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_UNION;
#define GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_cpu_harq_ram_wr_en_bypass_START  (0)
#define GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_cpu_harq_ram_wr_en_bypass_END    (0)


/*****************************************************************************
 结构名    : GBBP_CPU_TIMING_GET_TRIGGER_UNION
 结构说明  : CPU_TIMING_GET_TRIGGER 寄存器结构定义。地址偏移量:0x5A20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_timing_get_trigger_reg;
    struct
    {
        unsigned int  cpu_timing_get_trigger   : 1;  /* bit[0]    : GBBP定时锁定启动信号，写1有效，自清零，该信号有效时，GBBP启动定时锁存。 */
        unsigned int  reserved_0               : 15; /* bit[1-15] : 保留 */
        unsigned int  cpu_timing_get_state_clr : 1;  /* bit[16]   : GBBP定时锁定状态清零信号，写1有效，自清零，该信号有效时，timing_get_state状态清零 */
        unsigned int  reserved_1               : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_CPU_TIMING_GET_TRIGGER_UNION;
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_trigger_START    (0)
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_trigger_END      (0)
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_state_clr_START  (16)
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_state_clr_END    (16)


/*****************************************************************************
 结构名    : GBBP_TIMING_GET_FN_RPT_UNION
 结构说明  : TIMING_GET_FN_RPT 寄存器结构定义。地址偏移量:0x5A24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_fn_rpt_reg;
    struct
    {
        unsigned int  timing_get_fn_low   : 11; /* bit[0-10] : GTC此时实际帧号低位 */
        unsigned int  reserved_0          : 5;  /* bit[11-15]: 保留 */
        unsigned int  timing_get_fn_high  : 11; /* bit[16-26]: GTC此时实际帧号高位 */
        unsigned int  reserved_1          : 4;  /* bit[27-30]: 保留 */
        unsigned int  timing_get_fn_state : 1;  /* bit[31]   : 定时锁定状态上报，当cpu_timing_get_state_clr有效时该比特上报自行清零。 */
    } reg;
} GBBP_TIMING_GET_FN_RPT_UNION;
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_low_START    (0)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_low_END      (10)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_high_START   (16)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_high_END     (26)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_state_START  (31)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_state_END    (31)


/*****************************************************************************
 结构名    : GBBP_TIMING_GET_TIMEBASE_RPT_UNION
 结构说明  : TIMING_GET_TIMEBASE_RPT 寄存器结构定义。地址偏移量:0x5A28，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_timebase_rpt_reg;
    struct
    {
        unsigned int  timing_get_tdma_qb  : 13; /* bit[0-12] : 当前时刻TDMA的QB计数值 */
        unsigned int  reserved_0          : 3;  /* bit[13-15]: 保留 */
        unsigned int  timing_get_timebase : 13; /* bit[16-28]: 绝对时标QB上报，计数范围0~4999，对应一帧的长度。该值只与复位时刻有关，测试用 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_TIMING_GET_TIMEBASE_RPT_UNION;
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_tdma_qb_START   (0)
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_tdma_qb_END     (12)
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_timebase_START  (16)
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_timebase_END    (28)


/*****************************************************************************
 结构名    : GBBP_LOOPC_MODE_CFG_UNION
 结构说明  : LOOPC_MODE_CFG 寄存器结构定义。地址偏移量:0x53F0，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      loopc_mode_cfg_reg;
    struct
    {
        unsigned int  cpu_loopc_mode : 1;  /* bit[0]   : 1标识：LoopC环回时，偷帧bit位置固定返回1’b0。
                                                         0标识：LoopC环回时，偷帧bit位置返回解调软值的符号位。 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_LOOPC_MODE_CFG_UNION;
#define GBBP_LOOPC_MODE_CFG_cpu_loopc_mode_START  (0)
#define GBBP_LOOPC_MODE_CFG_cpu_loopc_mode_END    (0)


/*****************************************************************************
 结构名    : GBBP_COD_CBINDEX_RPT_UNION
 结构说明  : COD_CBINDEX_RPT 寄存器结构定义。地址偏移量:0x53F4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cod_cbindex_rpt_reg;
    struct
    {
        unsigned int  cod_cnt             : 4;  /* bit[0-3]  : 上行编码次数上报 */
        unsigned int  reserved_0          : 4;  /* bit[4-7]  : 保留 */
        unsigned int  gsp_ul_cb_start_pos : 2;  /* bit[8-9]  : 上行编码块起始位置上报 */
        unsigned int  reserved_1          : 6;  /* bit[10-15]: 保留 */
        unsigned int  gsp_ul_cb1_index    : 7;  /* bit[16-22]: 上行编码块的cbindex上报 */
        unsigned int  reserved_2          : 9;  /* bit[23-31]: 保留 */
    } reg;
} GBBP_COD_CBINDEX_RPT_UNION;
#define GBBP_COD_CBINDEX_RPT_cod_cnt_START              (0)
#define GBBP_COD_CBINDEX_RPT_cod_cnt_END                (3)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb_start_pos_START  (8)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb_start_pos_END    (9)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb1_index_START     (16)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb1_index_END       (22)


/*****************************************************************************
 结构名    : GBBP_CPU_IQ_MOD_DTA_UNION
 结构说明  : CPU_IQ_MOD_DTA 寄存器结构定义。地址偏移量:0x53C8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_iq_mod_dta_reg;
    struct
    {
        unsigned int  cpu_q_mod_data : 12; /* bit[0-11] : 上行发射校准时强制Q路调制输出为该配置数据 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_i_mod_data : 12; /* bit[16-27]: 上行发射校准时强制I路调制输出为该配置数据 */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_CPU_IQ_MOD_DTA_UNION;
#define GBBP_CPU_IQ_MOD_DTA_cpu_q_mod_data_START  (0)
#define GBBP_CPU_IQ_MOD_DTA_cpu_q_mod_data_END    (11)
#define GBBP_CPU_IQ_MOD_DTA_cpu_i_mod_data_START  (16)
#define GBBP_CPU_IQ_MOD_DTA_cpu_i_mod_data_END    (27)


/*****************************************************************************
 结构名    : GBBP_TX_DATA_MULFACTOR_UNION
 结构说明  : TX_DATA_MULFACTOR 寄存器结构定义。地址偏移量:0x5374，初值:0x03FF0399，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_data_mulfactor_reg;
    struct
    {
        unsigned int  cpu_gmsk_tx_data_mulfactor : 10; /* bit[0-9]  : GMSK上行调制数据缩放因子，缩放幅度默认约为921/1024=0.9。 */
        unsigned int  reserved_0                 : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_psk_tx_data_mulfactor  : 10; /* bit[16-25]: 8PSK上行调制数据缩放因子，缩放幅度默认约为1023/1024=1。 */
        unsigned int  reserved_1                 : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_TX_DATA_MULFACTOR_UNION;
#define GBBP_TX_DATA_MULFACTOR_cpu_gmsk_tx_data_mulfactor_START  (0)
#define GBBP_TX_DATA_MULFACTOR_cpu_gmsk_tx_data_mulfactor_END    (9)
#define GBBP_TX_DATA_MULFACTOR_cpu_psk_tx_data_mulfactor_START   (16)
#define GBBP_TX_DATA_MULFACTOR_cpu_psk_tx_data_mulfactor_END     (25)


/*****************************************************************************
 结构名    : GBBP_SLOT_DCR_RSSI_THRESHOLD_UNION
 结构说明  : SLOT_DCR_RSSI_THRESHOLD 寄存器结构定义。地址偏移量:0x5378，初值:0x00000B50，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      slot_dcr_rssi_threshold_reg;
    struct
    {
        unsigned int  cpu_slot_dcr_rssi_threshold : 12; /* bit[0-11] : 时隙去直流启动门限，即时隙去直流是否启动取决于当前时隙的RSSI大小。当大于该门限时，如果配置时隙去直流模式，反之则不启动。默认门限-12'd1200，相当于-150dBm。由于空口接收信号不可能小于该值，相当于默认不屏蔽启动时隙去直流。 */
        unsigned int  reserved                    : 20; /* bit[12-31]: 保留 */
    } reg;
} GBBP_SLOT_DCR_RSSI_THRESHOLD_UNION;
#define GBBP_SLOT_DCR_RSSI_THRESHOLD_cpu_slot_dcr_rssi_threshold_START  (0)
#define GBBP_SLOT_DCR_RSSI_THRESHOLD_cpu_slot_dcr_rssi_threshold_END    (11)


/*****************************************************************************
 结构名    : GBBP_MOD_BIT0_RPT_UNION
 结构说明  : MOD_BIT0_RPT 寄存器结构定义。地址偏移量:0x53A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit0_rpt_reg;
    struct
    {
        unsigned int  map_bit_0cpu : 30; /* bit[0-29] : GMSK待调制数据（编码后、调制前）上报，0～29比特，顺序为从低到高 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_MOD_BIT0_RPT_UNION;
#define GBBP_MOD_BIT0_RPT_map_bit_0cpu_START  (0)
#define GBBP_MOD_BIT0_RPT_map_bit_0cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_MOD_BIT1_RPT_UNION
 结构说明  : MOD_BIT1_RPT 寄存器结构定义。地址偏移量:0x53A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit1_rpt_reg;
    struct
    {
        unsigned int  map_bit_1cpu : 30; /* bit[0-29] : GMSK待调制数据（编码后、调制前）上报，30～59比特，顺序为从低到高 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_MOD_BIT1_RPT_UNION;
#define GBBP_MOD_BIT1_RPT_map_bit_1cpu_START  (0)
#define GBBP_MOD_BIT1_RPT_map_bit_1cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_MOD_BIT2_RPT_UNION
 结构说明  : MOD_BIT2_RPT 寄存器结构定义。地址偏移量:0x53A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit2_rpt_reg;
    struct
    {
        unsigned int  map_bit_2cpu : 30; /* bit[0-29] : GMSK待调制数据（编码后、调制前）上报，60～89比特，顺序为从低到高 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_MOD_BIT2_RPT_UNION;
#define GBBP_MOD_BIT2_RPT_map_bit_2cpu_START  (0)
#define GBBP_MOD_BIT2_RPT_map_bit_2cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_MOD_BIT3_RPT_UNION
 结构说明  : MOD_BIT3_RPT 寄存器结构定义。地址偏移量:0x53AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit3_rpt_reg;
    struct
    {
        unsigned int  map_bit_3cpu : 30; /* bit[0-29] : GMSK待调制数据（编码后、调制前）上报，90～119比特，顺序为从低到高 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_MOD_BIT3_RPT_UNION;
#define GBBP_MOD_BIT3_RPT_map_bit_3cpu_START  (0)
#define GBBP_MOD_BIT3_RPT_map_bit_3cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_MOD_BIT4_RPT_UNION
 结构说明  : MOD_BIT4_RPT 寄存器结构定义。地址偏移量:0x53B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit4_rpt_reg;
    struct
    {
        unsigned int  map_bit_4cpu : 30; /* bit[0-29] : GMSK待调制数据（编码后、调制前）上报，120～147比特，顺序为从低到高。编码后最多148比特，[29:27]无意义 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_MOD_BIT4_RPT_UNION;
#define GBBP_MOD_BIT4_RPT_map_bit_4cpu_START  (0)
#define GBBP_MOD_BIT4_RPT_map_bit_4cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_TX_IQ_MISMATCH_COMP_UNION
 结构说明  : TX_IQ_MISMATCH_COMP 寄存器结构定义。地址偏移量:0x58BC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_iq_mismatch_comp_reg;
    struct
    {
        unsigned int  cpu_g_tx_amp_comp   : 10; /* bit[0-9]  : GSM TX IQ Mismatch幅值校正因子，有符号数。 */
        unsigned int  reserved_0          : 6;  /* bit[10-15]: 保留 */
        unsigned int  cpu_g_tx_phase_comp : 10; /* bit[16-25]: GSM TX IQ Mismatch相位校正因子，有符号数。 */
        unsigned int  reserved_1          : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_TX_IQ_MISMATCH_COMP_UNION;
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_amp_comp_START    (0)
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_amp_comp_END      (9)
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_phase_comp_START  (16)
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_phase_comp_END    (25)


/*****************************************************************************
 结构名    : GBBP_TX_IQ_DC_OFFSET_COMP_UNION
 结构说明  : TX_IQ_DC_OFFSET_COMP 寄存器结构定义。地址偏移量:0x58C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_iq_dc_offset_comp_reg;
    struct
    {
        unsigned int  cpu_g_tx_dc_offset_i : 12; /* bit[0-11] : GSM TX IQ Mismatch I路直流偏置补偿值，有符号数。注：减法处理。 */
        unsigned int  reserved_0           : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_tx_dc_offset_q : 12; /* bit[16-27]: GSM TX IQ Mismatch Q路直流偏置补偿值，有符号数。注：减法处理。 */
        unsigned int  reserved_1           : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_TX_IQ_DC_OFFSET_COMP_UNION;
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_i_START  (0)
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_i_END    (11)
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_q_START  (16)
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_q_END    (27)


/*****************************************************************************
 结构名    : GBBP_TX_DIG_RMAP_MODE_SEL_UNION
 结构说明  : TX_DIG_RMAP_MODE_SEL 寄存器结构定义。地址偏移量:0x58C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_dig_rmap_mode_sel_reg;
    struct
    {
        unsigned int  cpu_gmsk_digramp_en    : 1;  /* bit[0]    : gmsk数字爬坡使能信号。
                                                                  1表示gmsk使用数字爬坡；0表示gmsk不使用数字爬坡。 */
        unsigned int  reserved_0             : 7;  /* bit[1-7]  : 保留 */
        unsigned int  cpu_8psk_digramp_en    : 1;  /* bit[8]    : 8psk数字爬坡使能信号。
                                                                  1表示8psk使用数字爬坡；0表示8psk不使用数字爬坡。
                                                                  默认值为1。 */
        unsigned int  reserved_1             : 7;  /* bit[9-15] : 保留 */
        unsigned int  cpu_ramp_default_value : 10; /* bit[16-25]: 数字爬坡时，下坡结束后的apc_ramp默认值。
                                                                  默认值为0。
                                                                  调试用。 */
        unsigned int  reserved_2             : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_TX_DIG_RMAP_MODE_SEL_UNION;
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_gmsk_digramp_en_START     (0)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_gmsk_digramp_en_END       (0)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_8psk_digramp_en_START     (8)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_8psk_digramp_en_END       (8)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_ramp_default_value_START  (16)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_ramp_default_value_END    (25)


/*****************************************************************************
 结构名    : GBBP_CPU_APC_SWITCH_EN_UNION
 结构说明  : CPU_APC_SWITCH_EN 寄存器结构定义。地址偏移量:0x53C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_apc_switch_en_reg;
    struct
    {
        unsigned int  cpu_apc_page_switch_en : 1;  /* bit[0]    : GAPC爬坡系数配置RAM乒乓访问使能，1表示允许乒乓访问，0表示固定访问帧0系数空间；当该信号为1时，逻辑内部在TDMA帧头自动切换乒乓标志 */
        unsigned int  reserved_0             : 15; /* bit[1-15] : 保留 */
        unsigned int  gsp_pa_target          : 10; /* bit[16-25]: 上行使用的gsp_pa_target值上报 */
        unsigned int  reserved_1             : 6;  /* bit[26-31]: 保留 */
    } reg;
} GBBP_CPU_APC_SWITCH_EN_UNION;
#define GBBP_CPU_APC_SWITCH_EN_cpu_apc_page_switch_en_START  (0)
#define GBBP_CPU_APC_SWITCH_EN_cpu_apc_page_switch_en_END    (0)
#define GBBP_CPU_APC_SWITCH_EN_gsp_pa_target_START           (16)
#define GBBP_CPU_APC_SWITCH_EN_gsp_pa_target_END             (25)


/*****************************************************************************
 结构名    : GBBP_TEST_PIN_SEL_LOW_UNION
 结构说明  : TEST_PIN_SEL_LOW 寄存器结构定义。地址偏移量:0x5700，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      test_pin_sel_low_reg;
    struct
    {
        unsigned int  agc_test_pin_sel  : 4;  /* bit[0-3]  : 16组AGC模块的测试引脚选择信号 */
        unsigned int  mau_test_pin_sel  : 4;  /* bit[4-7]  : 16组MAU模块的测试引脚选择信号 */
        unsigned int  srch_test_pin_sel : 4;  /* bit[8-11] : 16组SRCH模块的测试引脚选择信号 */
        unsigned int  dem_test_pin_sel  : 4;  /* bit[12-15]: 16组VTB_DEM模块的测试选择信号引脚 */
        unsigned int  dec_test_pin_sel  : 4;  /* bit[16-19]: 16组DEC模块的测试引脚选择信号 */
        unsigned int  cod_test_pin_sel  : 4;  /* bit[20-23]: 16组COD模块的测试引脚选择信号 */
        unsigned int  mod_test_pin_sel  : 4;  /* bit[24-27]: 16组MOD模块的测试引脚选择信号 */
        unsigned int  gtc_test_pin_sel  : 4;  /* bit[28-31]: 16组GTC模块的测试引脚选择信号 */
    } reg;
} GBBP_TEST_PIN_SEL_LOW_UNION;
#define GBBP_TEST_PIN_SEL_LOW_agc_test_pin_sel_START   (0)
#define GBBP_TEST_PIN_SEL_LOW_agc_test_pin_sel_END     (3)
#define GBBP_TEST_PIN_SEL_LOW_mau_test_pin_sel_START   (4)
#define GBBP_TEST_PIN_SEL_LOW_mau_test_pin_sel_END     (7)
#define GBBP_TEST_PIN_SEL_LOW_srch_test_pin_sel_START  (8)
#define GBBP_TEST_PIN_SEL_LOW_srch_test_pin_sel_END    (11)
#define GBBP_TEST_PIN_SEL_LOW_dem_test_pin_sel_START   (12)
#define GBBP_TEST_PIN_SEL_LOW_dem_test_pin_sel_END     (15)
#define GBBP_TEST_PIN_SEL_LOW_dec_test_pin_sel_START   (16)
#define GBBP_TEST_PIN_SEL_LOW_dec_test_pin_sel_END     (19)
#define GBBP_TEST_PIN_SEL_LOW_cod_test_pin_sel_START   (20)
#define GBBP_TEST_PIN_SEL_LOW_cod_test_pin_sel_END     (23)
#define GBBP_TEST_PIN_SEL_LOW_mod_test_pin_sel_START   (24)
#define GBBP_TEST_PIN_SEL_LOW_mod_test_pin_sel_END     (27)
#define GBBP_TEST_PIN_SEL_LOW_gtc_test_pin_sel_START   (28)
#define GBBP_TEST_PIN_SEL_LOW_gtc_test_pin_sel_END     (31)


/*****************************************************************************
 结构名    : GBBP_TEST_PIN_SEL_HIGH_UNION
 结构说明  : TEST_PIN_SEL_HIGH 寄存器结构定义。地址偏移量:0x5704，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      test_pin_sel_high_reg;
    struct
    {
        unsigned int  prefilter_test_pin_sel  : 4;  /* bit[0-3]  : 16组PREFILTER模块的测试引脚选择信号 */
        unsigned int  preprocess_test_pin_sel : 4;  /* bit[4-7]  : 16组PREPROCESS模块的测试引脚选择信号 */
        unsigned int  gapc_test_pin_sel       : 4;  /* bit[8-11] : 16组APC模块的测试引脚选择信号 */
        unsigned int  reserved                : 4;  /* bit[12-15]: 保留 */
        unsigned int  path_eng_max_sum        : 16; /* bit[16-31]: 用于TOA计算的13条径能量中，相邻5个能量累加，产生9个累加值。此上报为当前时隙最大累加值。 */
    } reg;
} GBBP_TEST_PIN_SEL_HIGH_UNION;
#define GBBP_TEST_PIN_SEL_HIGH_prefilter_test_pin_sel_START   (0)
#define GBBP_TEST_PIN_SEL_HIGH_prefilter_test_pin_sel_END     (3)
#define GBBP_TEST_PIN_SEL_HIGH_preprocess_test_pin_sel_START  (4)
#define GBBP_TEST_PIN_SEL_HIGH_preprocess_test_pin_sel_END    (7)
#define GBBP_TEST_PIN_SEL_HIGH_gapc_test_pin_sel_START        (8)
#define GBBP_TEST_PIN_SEL_HIGH_gapc_test_pin_sel_END          (11)
#define GBBP_TEST_PIN_SEL_HIGH_path_eng_max_sum_START         (16)
#define GBBP_TEST_PIN_SEL_HIGH_path_eng_max_sum_END           (31)


/*****************************************************************************
 结构名    : GBBP_TEST_MODULE_SEL_UNION
 结构说明  : TEST_MODULE_SEL 寄存器结构定义。地址偏移量:0x5710，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      test_module_sel_reg;
    struct
    {
        unsigned int  gbbp_module_test_sel_low  : 5;  /* bit[0-4] : 0：选择AGC模块的测试引脚
                                                                    1：选择乘累加模块的测试引脚
                                                                    2：选择搜索模块的测试引脚
                                                                    3：选择解调模块的测试引脚
                                                                    4：选择译码模块的测试引脚
                                                                    5：选择编码模块的测试引脚
                                                                    6：选择调制模块的测试引脚
                                                                    7：选择GTC模块的测试引脚
                                                                    8：选择A5 DECIPH模块的测试引脚
                                                                    9：选择PREFILTER模块的测试引脚
                                                                    10：选择PREPROCESS模块的测试引脚
                                                                    11：选择APC模块的测试引脚
                                                                    13：选择GRIF模块的测试引脚
                                                                    14：选择A5 CIPH模块的测试引脚 */
        unsigned int  gbbp_module_test_sel_high : 3;  /* bit[5-7] : 0表示可以选择DAGC输出数据采样的相关控制信号
                                                                    1表示可以选择AGC输入数据采样的相关控制信号
                                                                    2表示可以选择DAGC输出和解调后软值数据采样的相关控制信号
                                                                    3表示可以选择DAGC输出和AGC输入数据采样的相关控制信号
                                                                    4表示可以观察解调，译码启动信号和中断信号 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} GBBP_TEST_MODULE_SEL_UNION;
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_low_START   (0)
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_low_END     (4)
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_high_START  (5)
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_high_END    (7)


/*****************************************************************************
 结构名    : GBBP_GSP_START_TDMA_QB_RPT_UNION
 结构说明  : GSP_START_TDMA_QB_RPT 寄存器结构定义。地址偏移量:0x5714，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gsp_start_tdma_qb_rpt_reg;
    struct
    {
        unsigned int  gsp_start_tdma_qb    : 13; /* bit[0-12] : 对应GTC解析出的各个启动信号所在tdma_qb值上报。 */
        unsigned int  reserved             : 15; /* bit[13-27]: 保留 */
        unsigned int  cpu_sample_start_sel : 4;  /* bit[28-31]: 4'd0: gsp_agc_fast_start信号对应的gtc_tdma_qb采样值
                                                                4'd1: gsp_agc_slow_start信号对应的gtc_tdma_qb采样值
                                                                4'd2: gsp_srch_start信号对应的gtc_tdma_qb采样值
                                                                4'd3: gsp_demod_start信号对应的gtc_tdma_qb采样值
                                                                4'd4: gsp_rx_start信号对应的gtc_tdma_qb采样值
                                                                4'd5: gsp_rx_stop信号对应的gtc_tdma_qb采样值
                                                                4'd6: gsp_dec_start信号对应的gtc_tdma_qb采样值
                                                                4'd7: gsp_ul_cod_start信号对应的gtc_tdma_qb采样值
                                                                4'd8: gsp_ul_map_start信号对应的gtc_tdma_qb采样值
                                                                4'd9: gsp_mod_start信号对应的gtc_tdma_qb采样值
                                                                4'd10: gsp_mod_stop信号对应的gtc_tdma_qb采样值
                                                                4'd11: gsp_pa_start信号对应的gtc_tdma_qb采样值
                                                                4'd12: gsp_pa_stop信号对应的gtc_tdma_qb采样值
                                                                4'd13: gsp_pa_single_start信号对应的gtc_tdma_qb采样值
                                                                4'd14: gsp_pa_change信号对应的gtc_tdma_qb采样值
                                                                测试用 */
    } reg;
} GBBP_GSP_START_TDMA_QB_RPT_UNION;
#define GBBP_GSP_START_TDMA_QB_RPT_gsp_start_tdma_qb_START     (0)
#define GBBP_GSP_START_TDMA_QB_RPT_gsp_start_tdma_qb_END       (12)
#define GBBP_GSP_START_TDMA_QB_RPT_cpu_sample_start_sel_START  (28)
#define GBBP_GSP_START_TDMA_QB_RPT_cpu_sample_start_sel_END    (31)


/*****************************************************************************
 结构名    : GBBP_DSP_DEDICATE_CTRL_REG_UNION
 结构说明  : DSP_DEDICATE_CTRL_REG 寄存器结构定义。地址偏移量:0x5720，初值:0x8000031C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dsp_dedicate_ctrl_reg_reg;
    struct
    {
        unsigned int  cpu_alpha_noise_thresh    : 16; /* bit[0-15] : TOA Alpha滤波门限。默认11'd796，与径能量累加值右移6bit的结果进行比较。 */
        unsigned int  gbbp_redudant             : 15; /* bit[16-30]: 预留的冗余寄存器。 */
        unsigned int  cpu_alpha_noise_thresh_en : 1;  /* bit[31]   : TOA Alpha滤波门限使能信号。1表示根据门限判决是否使用Alpha功能。 */
    } reg;
} GBBP_DSP_DEDICATE_CTRL_REG_UNION;
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_START     (0)
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_END       (15)
#define GBBP_DSP_DEDICATE_CTRL_REG_gbbp_redudant_START              (16)
#define GBBP_DSP_DEDICATE_CTRL_REG_gbbp_redudant_END                (30)
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_en_START  (31)
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_en_END    (31)


/*****************************************************************************
 结构名    : GBBP_ERR_TRIG_UNION
 结构说明  : ERR_TRIG 寄存器结构定义。地址偏移量:0x5764，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      err_trig_reg;
    struct
    {
        unsigned int  err_trig : 1;  /* bit[0]   : 罗分trigger信号，用于平台问题定位使用。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_ERR_TRIG_UNION;
#define GBBP_ERR_TRIG_err_trig_START  (0)
#define GBBP_ERR_TRIG_err_trig_END    (0)


/*****************************************************************************
 结构名    : GBBP_GBBP_EDGE_VERSION_UNION
 结构说明  : GBBP_EDGE_VERSION 寄存器结构定义。地址偏移量:0x5768，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gbbp_edge_version_reg;
    struct
    {
        unsigned int  edge_flag : 1;  /* bit[0]   : V2R1版本，该bit必须为1，测试用 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_GBBP_EDGE_VERSION_UNION;
#define GBBP_GBBP_EDGE_VERSION_edge_flag_START  (0)
#define GBBP_GBBP_EDGE_VERSION_edge_flag_END    (0)


/*****************************************************************************
 结构名    : GBBP_GROSS_CARRIER_ENERGY5_UNION
 结构说明  : GROSS_CARRIER_ENERGY5 寄存器结构定义。地址偏移量:0x529C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy5_reg;
    struct
    {
        unsigned int  thres_c_5d : 19; /* bit[0-18] : 第五近的一个BURST解调前粗测C值上报，测试用 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY5_UNION;
#define GBBP_GROSS_CARRIER_ENERGY5_thres_c_5d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY5_thres_c_5d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_INTERFERE_ENERGY5_UNION
 结构说明  : GROSS_INTERFERE_ENERGY5 寄存器结构定义。地址偏移量:0x5300，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy5_reg;
    struct
    {
        unsigned int  thres_i_5d : 19; /* bit[0-18] : 第五近的一个BURST解调前粗测I值上报，测试用 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY5_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY5_thres_i_5d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY5_thres_i_5d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_CARRIER_ENERGY6_UNION
 结构说明  : GROSS_CARRIER_ENERGY6 寄存器结构定义。地址偏移量:0x5304，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy6_reg;
    struct
    {
        unsigned int  thres_c_6d : 19; /* bit[0-18] : 第六近的一个BURST解调前粗测C值上报，测试用 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY6_UNION;
#define GBBP_GROSS_CARRIER_ENERGY6_thres_c_6d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY6_thres_c_6d_END    (18)


/*****************************************************************************
 结构名    : GBBP_GROSS_INTERFERE_ENERGY6_UNION
 结构说明  : GROSS_INTERFERE_ENERGY6 寄存器结构定义。地址偏移量:0x5308，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy6_reg;
    struct
    {
        unsigned int  thres_i_6d : 19; /* bit[0-18] : 第六近的一个BURST解调前粗测I值上报，测试用 */
        unsigned int  reserved   : 13; /* bit[19-31]: 保留 */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY6_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY6_thres_i_6d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY6_thres_i_6d_END    (18)


/*****************************************************************************
 结构名    : GBBP_AAGC_GAIN5_CPU_UNION
 结构说明  : AAGC_GAIN5_CPU 寄存器结构定义。地址偏移量:0x5290，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain5_cpu_reg;
    struct
    {
        unsigned int  next_gain_5d     : 3;  /* bit[0-2]  : 第五近一个时隙AGC期望控制增益。 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : 保留 */
        unsigned int  rssi_5d          : 12; /* bit[8-19] : 第五近一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。 */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: 保留 */
        unsigned int  curr_gain_5d     : 3;  /* bit[24-26]: 第五近一个时隙AAGC档位上报。 */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: 保留 */
        unsigned int  agc_fast_flag_5d : 1;  /* bit[31]   : 第五近一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。 */
    } reg;
} GBBP_AAGC_GAIN5_CPU_UNION;
#define GBBP_AAGC_GAIN5_CPU_next_gain_5d_START      (0)
#define GBBP_AAGC_GAIN5_CPU_next_gain_5d_END        (2)
#define GBBP_AAGC_GAIN5_CPU_rssi_5d_START           (8)
#define GBBP_AAGC_GAIN5_CPU_rssi_5d_END             (19)
#define GBBP_AAGC_GAIN5_CPU_curr_gain_5d_START      (24)
#define GBBP_AAGC_GAIN5_CPU_curr_gain_5d_END        (26)
#define GBBP_AAGC_GAIN5_CPU_agc_fast_flag_5d_START  (31)
#define GBBP_AAGC_GAIN5_CPU_agc_fast_flag_5d_END    (31)


/*****************************************************************************
 结构名    : GBBP_AAGC_GAIN6_CPU_UNION
 结构说明  : AAGC_GAIN6_CPU 寄存器结构定义。地址偏移量:0x5294，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain6_cpu_reg;
    struct
    {
        unsigned int  next_gain_6d     : 3;  /* bit[0-2]  : 最远一个时隙AGC期望控制增益。 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : 保留 */
        unsigned int  rssi_6d          : 12; /* bit[8-19] : 最远一个时隙AGC RSSI值，单位0.125dBm，上报给CPU。该值已是空口的RSSI值。 */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: 保留 */
        unsigned int  curr_gain_6d     : 3;  /* bit[24-26]: 最远一个时隙AAGC档位上报。 */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: 保留 */
        unsigned int  agc_fast_flag_6d : 1;  /* bit[31]   : 最远一个时隙快慢速测量标志上报。1表示当前为快速测量，0表示当前为慢速测量。 */
    } reg;
} GBBP_AAGC_GAIN6_CPU_UNION;
#define GBBP_AAGC_GAIN6_CPU_next_gain_6d_START      (0)
#define GBBP_AAGC_GAIN6_CPU_next_gain_6d_END        (2)
#define GBBP_AAGC_GAIN6_CPU_rssi_6d_START           (8)
#define GBBP_AAGC_GAIN6_CPU_rssi_6d_END             (19)
#define GBBP_AAGC_GAIN6_CPU_curr_gain_6d_START      (24)
#define GBBP_AAGC_GAIN6_CPU_curr_gain_6d_END        (26)
#define GBBP_AAGC_GAIN6_CPU_agc_fast_flag_6d_START  (31)
#define GBBP_AAGC_GAIN6_CPU_agc_fast_flag_6d_END    (31)


/*****************************************************************************
 结构名    : GBBP_CPU_GDUMP_GEN_CONFIG_UNION
 结构说明  : CPU_GDUMP_GEN_CONFIG 寄存器结构定义。地址偏移量:0xf004，初值:0x00000013，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_gen_config_reg;
    struct
    {
        unsigned int  dump_fifo_watermarker_g : 3;  /* bit[0-2]  : FIFO水线深度选择。
                                                                   0：表示水线深度2；
                                                                   1：表示水线深度4；
                                                                   2：表示水线深度8；
                                                                   3：表示水线深度16；
                                                                   4：表示水线深度32；
                                                                   5：表示水线深度64；
                                                                   6：表示水线深度128；
                                                                   7：
                                                                   SOC水线深度支持1~16 */
        unsigned int  reserved_0              : 1;  /* bit[3]    : 保留 */
        unsigned int  cpu_sample_data_sel     : 3;  /* bit[4-6]  : 采样数据源选择。
                                                                   0：选择采用信道滤波器输入数据；
                                                                   1：选择采用信道滤波器输出数据；
                                                                   2：选择采用AGC输入数据；
                                                                   3：选择采用AGC去直流后且用于测量的数据；
                                                                   4：选择采用AGC去直流后且用于解调与搜索的数据；
                                                                   5：选择采用DAGC输出数据，仅用于采样待解调数据；
                                                                   6：上行发送调制数据；
                                                                   7： */
        unsigned int  reserved_1              : 1;  /* bit[7]    : 保留 */
        unsigned int  cpu_sample_config_sel   : 1;  /* bit[8]    : 采数模块配置类型选择。
                                                                   0：选择使用GTC配置接口
                                                                   1：选择使用CPU配置接口
                                                                   默认配置为0。 */
        unsigned int  reserved_2              : 7;  /* bit[9-15] : 保留 */
        unsigned int  tx_test_cnt             : 8;  /* bit[16-23]: G上行测试计数器 */
        unsigned int  reserved_3              : 7;  /* bit[24-30]: 保留 */
        unsigned int  dump_en_g               : 1;  /* bit[31]   : 采数模块总是能，并控制时钟门控，无论哪种模式采数，首先要配置此信号有效，高电平表示该功能打开。 */
    } reg;
} GBBP_CPU_GDUMP_GEN_CONFIG_UNION;
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_fifo_watermarker_g_START  (0)
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_fifo_watermarker_g_END    (2)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_data_sel_START      (4)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_data_sel_END        (6)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_config_sel_START    (8)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_config_sel_END      (8)
#define GBBP_CPU_GDUMP_GEN_CONFIG_tx_test_cnt_START              (16)
#define GBBP_CPU_GDUMP_GEN_CONFIG_tx_test_cnt_END                (23)
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_en_g_START                (31)
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_en_g_END                  (31)


/*****************************************************************************
 结构名    : GBBP_CPU_GDUMP_SAM_LOW_TIMING_UNION
 结构说明  : CPU_GDUMP_SAM_LOW_TIMING 寄存器结构定义。地址偏移量:0xf00C，初值:0x00001FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_sam_low_timing_reg;
    struct
    {
        unsigned int  dump_gtc_tdma_qb : 13; /* bit[0-12] : 可配启动时刻采数模式下，采数起始位置，35'h7ffffffff表示立即启动。该配置为35bit中[12:0]，默认值为立即启动模式。 */
        unsigned int  reserved         : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_CPU_GDUMP_SAM_LOW_TIMING_UNION;
#define GBBP_CPU_GDUMP_SAM_LOW_TIMING_dump_gtc_tdma_qb_START  (0)
#define GBBP_CPU_GDUMP_SAM_LOW_TIMING_dump_gtc_tdma_qb_END    (12)


/*****************************************************************************
 结构名    : GBBP_CPU_GDUMP_SAM_HIGH_TIMING_UNION
 结构说明  : CPU_GDUMP_SAM_HIGH_TIMING 寄存器结构定义。地址偏移量:0xf010，初值:0x07FF07FF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_sam_high_timing_reg;
    struct
    {
        unsigned int  dump_gtc_fn_low  : 11; /* bit[0-10] : 可配启动时刻采数模式下，采数起始位置，35'h7ffffffff表示立即启动。该配置为35bit中[23:13]，默认值为立即启动模式。 */
        unsigned int  reserved_0       : 5;  /* bit[11-15]: 保留 */
        unsigned int  dump_gtc_fn_high : 11; /* bit[16-26]: 可配启动时刻采数模式下，采数起始位置，35'h7ffffffff表示立即启动。该配置为35bit中[34:24]，默认值为立即启动模式。 */
        unsigned int  reserved_1       : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_CPU_GDUMP_SAM_HIGH_TIMING_UNION;
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_low_START   (0)
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_low_END     (10)
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_high_START  (16)
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_high_END    (26)


/*****************************************************************************
 结构名    : GBBP_CPU_GDUMP_RECV_CONFIG_UNION
 结构说明  : CPU_GDUMP_RECV_CONFIG 寄存器结构定义。地址偏移量:0xf014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_recv_config_reg;
    struct
    {
        unsigned int  cpu_rx_start : 1;  /* bit[0]    : CPU配置采样数据启动信号。 */
        unsigned int  reserved_0   : 7;  /* bit[1-7]  : 保留 */
        unsigned int  cpu_rx_stop  : 1;  /* bit[8]    : CPU配置采样数据停止信号，当采样数据个数无限长时，用该信号停止采数。 */
        unsigned int  reserved_1   : 7;  /* bit[9-15] : 保留 */
        unsigned int  cpu_fifo_clr : 1;  /* bit[16]   : CPU配置异步FIFO清零信号。 */
        unsigned int  reserved_2   : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_CPU_GDUMP_RECV_CONFIG_UNION;
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_start_START  (0)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_start_END    (0)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_stop_START   (8)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_stop_END     (8)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_fifo_clr_START  (16)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_fifo_clr_END    (16)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_1REG_UNION
 结构说明  : ADDR_G_CH_PARA_1REG 寄存器结构定义。地址偏移量:0xf294，初值:0x0FFD0001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_1reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h0_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数0,12bit有符号数 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h1_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数1,12bit有符号数 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_1REG_UNION;
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h0_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h0_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h1_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h1_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_2REG_UNION
 结构说明  : ADDR_G_CH_PARA_2REG 寄存器结构定义。地址偏移量:0xf298，初值:0x0FFA0FFA，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_2reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h2_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数2,12bit有符号数 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h3_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数3,12bit有符号数 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_2REG_UNION;
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h2_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h2_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h3_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h3_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_3REG_UNION
 结构说明  : ADDR_G_CH_PARA_3REG 寄存器结构定义。地址偏移量:0xf29C，初值:0x00060FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_3reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h4_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数4,12bit有符号数 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h5_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数5,12bit有符号数 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_3REG_UNION;
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h4_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h4_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h5_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h5_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_4REG_UNION
 结构说明  : ADDR_G_CH_PARA_4REG 寄存器结构定义。地址偏移量:0xf2A0，初值:0x000C000C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_4reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h6_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数6,12bit有符号数 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h7_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数7,12bit有符号数 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_4REG_UNION;
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h6_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h6_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h7_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h7_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_5REG_UNION
 结构说明  : ADDR_G_CH_PARA_5REG 寄存器结构定义。地址偏移量:0xf2A4，初值:0x0FF40002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_5reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h8_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数8,12bit有符号数 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h9_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数9,12bit有符号数 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_5REG_UNION;
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h8_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h8_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h9_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h9_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_6REG_UNION
 结构说明  : ADDR_G_CH_PARA_6REG 寄存器结构定义。地址偏移量:0xf2A8，初值:0x0FEB0FE9，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_6reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h10_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数10,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h11_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数11,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_6REG_UNION;
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h10_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h10_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h11_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h11_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_7REG_UNION
 结构说明  : ADDR_G_CH_PARA_7REG 寄存器结构定义。地址偏移量:0xf2AC，初值:0x00160FFD，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_7reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h12_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数12,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h13_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数13,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_7REG_UNION;
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h12_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h12_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h13_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h13_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_8REG_UNION
 结构说明  : ADDR_G_CH_PARA_8REG 寄存器结构定义。地址偏移量:0xf2B0，初值:0x00220027，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_8reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h14_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数14,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h15_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数15,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_8REG_UNION;
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h14_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h14_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h15_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h15_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_9REG_UNION
 结构说明  : ADDR_G_CH_PARA_9REG 寄存器结构定义。地址偏移量:0xf2B8，初值:0x0FDB0004，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_9reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h16_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数16,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h17_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数17,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_9REG_UNION;
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h16_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h16_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h17_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h17_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_10REG_UNION
 结构说明  : ADDR_G_CH_PARA_10REG 寄存器结构定义。地址偏移量:0xf2C4，初值:0x0FC90FBF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_10reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h18_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数18,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h19_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数19,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_10REG_UNION;
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h18_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h18_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h19_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h19_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_11REG_UNION
 结构说明  : ADDR_G_CH_PARA_11REG 寄存器结构定义。地址偏移量:0xf2C8，初值:0x00400FFC，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_11reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h20_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数20,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h21_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数21,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_11REG_UNION;
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h20_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h20_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h21_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h21_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_12REG_UNION
 结构说明  : ADDR_G_CH_PARA_12REG 寄存器结构定义。地址偏移量:0xf2CC，初值:0x005D006E，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_12reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h22_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数22,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h23_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数23,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_12REG_UNION;
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h22_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h22_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h23_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h23_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_13REG_UNION
 结构说明  : ADDR_G_CH_PARA_13REG 寄存器结构定义。地址偏移量:0xf2D0，初值:0x0F890005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_13reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h24_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数24,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h25_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数25,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_13REG_UNION;
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h24_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h24_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h25_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h25_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_14REG_UNION
 结构说明  : ADDR_G_CH_PARA_14REG 寄存器结构定义。地址偏移量:0xf2D4，初值:0x0F490F31，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_14reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h26_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数26,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h27_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数27,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_14REG_UNION;
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h26_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h26_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h27_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h27_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_15REG_UNION
 结构说明  : ADDR_G_CH_PARA_15REG 寄存器结构定义。地址偏移量:0xf2D8，初值:0x01300FFB，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_15reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h28_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数28,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h29_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数29,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_15REG_UNION;
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h28_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h28_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h29_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h29_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_16REG_UNION
 结构说明  : ADDR_G_CH_PARA_16REG 寄存器结构定义。地址偏移量:0xf2DC，初值:0x03AE0293，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_16reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h30_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数30,12bit有符号数 */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_ch_h31_ext : 12; /* bit[16-27]: GSM下行信道滤波配置系数31,12bit有符号数 */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_16REG_UNION;
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h30_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h30_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h31_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h31_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_CH_PARA_17REG_UNION
 结构说明  : ADDR_G_CH_PARA_17REG 寄存器结构定义。地址偏移量:0xf2E0，初值:0x00000419，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_17reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h32_ext : 12; /* bit[0-11] : GSM下行信道滤波配置系数32,12bit有符号数 */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} GBBP_ADDR_G_CH_PARA_17REG_UNION;
#define GBBP_ADDR_G_CH_PARA_17REG_cpu_g_ch_h32_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_17REG_cpu_g_ch_h32_ext_END    (11)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_1REG_UNION
 结构说明  : ADDR_G_32CH_PARA_1REG 寄存器结构定义。地址偏移量:0xf31C，初值:0x0FD80FEC，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_1reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h0_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数0,12bit有符号数 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h1_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数1,12bit有符号数 */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_1REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h0_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h0_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h1_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h1_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_2REG_UNION
 结构说明  : ADDR_G_32CH_PARA_2REG 寄存器结构定义。地址偏移量:0xf320，初值:0x0FE80FD0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_2reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h2_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数2,12bit有符号数 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h3_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数3,12bit有符号数 */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_2REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h2_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h2_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h3_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h3_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_3REG_UNION
 结构说明  : ADDR_G_32CH_PARA_3REG 寄存器结构定义。地址偏移量:0xf324，初值:0x004C0018，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_3reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h4_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数4,12bit有符号数 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h5_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数5,12bit有符号数 */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_3REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h4_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h4_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h5_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h5_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_4REG_UNION
 结构说明  : ADDR_G_32CH_PARA_4REG 寄存器结构定义。地址偏移量:0xf328，初值:0x0038005C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_4reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h6_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数6,12bit有符号数 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h7_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数7,12bit有符号数 */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_4REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h6_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h6_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h7_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h7_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_5REG_UNION
 结构说明  : ADDR_G_32CH_PARA_5REG 寄存器结构定义。地址偏移量:0xf32C，初值:0x0F780FE0，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_5reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h8_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数8,12bit有符号数 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h9_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数9,12bit有符号数 */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_5REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h8_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h8_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h9_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h9_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_6REG_UNION
 结构说明  : ADDR_G_32CH_PARA_6REG 寄存器结构定义。地址偏移量:0xf330，初值:0x0F700F40，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_6reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h10_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数10,12bit有符号数 */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h11_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数11,12bit有符号数 */
        unsigned int  reserved_1         : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_6REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h10_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h10_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h11_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h11_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_7REG_UNION
 结构说明  : ADDR_G_32CH_PARA_7REG 寄存器结构定义。地址偏移量:0xf334，初值:0x01480028，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_7reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h12_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数12,12bit有符号数 */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h13_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数13,12bit有符号数 */
        unsigned int  reserved_1         : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_7REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h12_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h12_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h13_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h13_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_8REG_UNION
 结构说明  : ADDR_G_32CH_PARA_8REG 寄存器结构定义。地址偏移量:0xf338，初值:0x037C0284，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_8reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h14_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数14,12bit有符号数 */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: 保留 */
        unsigned int  cpu_g_32ch_h15_ext : 12; /* bit[16-27]: GSM下行32阶信道滤波配置系数15,12bit有符号数 */
        unsigned int  reserved_1         : 4;  /* bit[28-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_8REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h14_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h14_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h15_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h15_ext_END    (27)


/*****************************************************************************
 结构名    : GBBP_ADDR_G_32CH_PARA_9REG_UNION
 结构说明  : ADDR_G_32CH_PARA_9REG 寄存器结构定义。地址偏移量:0xf33C，初值:0x000003D8，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_9reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h16_ext : 12; /* bit[0-11] : GSM下行32阶信道滤波配置系数16,12bit有符号数 */
        unsigned int  reserved           : 20; /* bit[12-31]: 保留 */
    } reg;
} GBBP_ADDR_G_32CH_PARA_9REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_9REG_cpu_g_32ch_h16_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_9REG_cpu_g_32ch_h16_ext_END    (11)


/*****************************************************************************
 结构名    : GBBP_CLIP_MODE_SEL_UNION
 结构说明  : CLIP_MODE_SEL 寄存器结构定义。地址偏移量:0xf2E8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      clip_mode_sel_reg;
    struct
    {
        unsigned int  cpu_gain0_clip_mode_sel : 2;  /* bit[0-1]  : ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_0              : 2;  /* bit[2-3]  : 保留 */
        unsigned int  cpu_gain1_clip_mode_sel : 2;  /* bit[4-5]  : ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_1              : 2;  /* bit[6-7]  : 保留 */
        unsigned int  cpu_gain2_clip_mode_sel : 2;  /* bit[8-9]  : ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_2              : 2;  /* bit[10-11]: 保留 */
        unsigned int  cpu_gain3_clip_mode_sel : 2;  /* bit[12-13]: ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_3              : 2;  /* bit[14-15]: 保留 */
        unsigned int  cpu_gain4_clip_mode_sel : 2;  /* bit[16-17]: ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_4              : 2;  /* bit[18-19]: 保留 */
        unsigned int  cpu_gain5_clip_mode_sel : 2;  /* bit[20-21]: ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_5              : 2;  /* bit[22-23]: 保留 */
        unsigned int  cpu_gain6_clip_mode_sel : 2;  /* bit[24-25]: ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_6              : 2;  /* bit[26-27]: 保留 */
        unsigned int  cpu_gain7_clip_mode_sel : 2;  /* bit[28-29]: ABB下行接收滤波器输出数据截位限幅处理模式选择。2'd0：输出数据右移12bit后限幅至14bit；2'd1：输出数据右移11bit后限幅至14bit；2'd2：输出数据右移10bit后限幅至14bit；默认配置2'd1。 */
        unsigned int  reserved_7              : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_CLIP_MODE_SEL_UNION;
#define GBBP_CLIP_MODE_SEL_cpu_gain0_clip_mode_sel_START  (0)
#define GBBP_CLIP_MODE_SEL_cpu_gain0_clip_mode_sel_END    (1)
#define GBBP_CLIP_MODE_SEL_cpu_gain1_clip_mode_sel_START  (4)
#define GBBP_CLIP_MODE_SEL_cpu_gain1_clip_mode_sel_END    (5)
#define GBBP_CLIP_MODE_SEL_cpu_gain2_clip_mode_sel_START  (8)
#define GBBP_CLIP_MODE_SEL_cpu_gain2_clip_mode_sel_END    (9)
#define GBBP_CLIP_MODE_SEL_cpu_gain3_clip_mode_sel_START  (12)
#define GBBP_CLIP_MODE_SEL_cpu_gain3_clip_mode_sel_END    (13)
#define GBBP_CLIP_MODE_SEL_cpu_gain4_clip_mode_sel_START  (16)
#define GBBP_CLIP_MODE_SEL_cpu_gain4_clip_mode_sel_END    (17)
#define GBBP_CLIP_MODE_SEL_cpu_gain5_clip_mode_sel_START  (20)
#define GBBP_CLIP_MODE_SEL_cpu_gain5_clip_mode_sel_END    (21)
#define GBBP_CLIP_MODE_SEL_cpu_gain6_clip_mode_sel_START  (24)
#define GBBP_CLIP_MODE_SEL_cpu_gain6_clip_mode_sel_END    (25)
#define GBBP_CLIP_MODE_SEL_cpu_gain7_clip_mode_sel_START  (28)
#define GBBP_CLIP_MODE_SEL_cpu_gain7_clip_mode_sel_END    (29)


/*****************************************************************************
 结构名    : GBBP_ADDR_MEM_CTRL1_UNION
 结构说明  : ADDR_MEM_CTRL1 寄存器结构定义。地址偏移量:0xf018，初值:0x03500057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_mem_ctrl1_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_w1 : 16; /* bit[0-15] : 1w2rw双口RAM延时控制 */
        unsigned int  mem_ctrl_d_1w2r_w1   : 16; /* bit[16-31]: 1w2r双口RAM延时控制 */
    } reg;
} GBBP_ADDR_MEM_CTRL1_UNION;
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1rw2rw_w1_START  (0)
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1rw2rw_w1_END    (15)
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1w2r_w1_START    (16)
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1w2r_w1_END      (31)


/*****************************************************************************
 结构名    : GBBP_ADDR_MEM_CTRL2_UNION
 结构说明  : ADDR_MEM_CTRL2 寄存器结构定义。地址偏移量:0xf01C，初值:0x00701050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_mem_ctrl2_reg;
    struct
    {
        unsigned int  mem_ctrl_s_w1 : 16; /* bit[0-15] : 单口RAM延时控制 */
        unsigned int  rom_ctrl      : 8;  /* bit[16-23]: ROM延时控制 */
        unsigned int  reserved      : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_ADDR_MEM_CTRL2_UNION;
#define GBBP_ADDR_MEM_CTRL2_mem_ctrl_s_w1_START  (0)
#define GBBP_ADDR_MEM_CTRL2_mem_ctrl_s_w1_END    (15)
#define GBBP_ADDR_MEM_CTRL2_rom_ctrl_START       (16)
#define GBBP_ADDR_MEM_CTRL2_rom_ctrl_END         (23)


/***======================================================================***
                     (2/9) register_define_sdr_gdrx_guage
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GDRX_GAUGE_EN_CNF_UNION
 结构说明  : GDRX_GAUGE_EN_CNF 寄存器结构定义。地址偏移量:0x0000，初值:0x0000000A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gdrx_gauge_en_cnf_reg;
    struct
    {
        unsigned int  gdrx_gauge_len  : 17; /* bit[0-16] : 时钟校准32KHz时钟个数 */
        unsigned int  reserved        : 13; /* bit[17-29]: 保留 */
        unsigned int  gdrx_gauge_en   : 1;  /* bit[30]   : 时钟校准使能，写1开启。自清零，写0无意义。 */
        unsigned int  gdrx_gauge_stop : 1;  /* bit[31]   : GDRX停止脉冲，写1停止。自清零，写0无意义。 */
    } reg;
} GBBP_GDRX_GAUGE_EN_CNF_UNION;
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_START   (0)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_END     (16)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_START    (30)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_END      (30)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_START  (31)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_END    (31)


/*****************************************************************************
 结构名    : GBBP_GAUGE_RESULT_RPT_UNION
 结构说明  : GAUGE_RESULT_RPT 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gauge_result_rpt_reg;
    struct
    {
        unsigned int  gdrx_gauge_result : 28; /* bit[0-27] : 时钟校准结果，测量周期内104M钟个数 */
        unsigned int  reserved          : 2;  /* bit[28-29]: 保留 */
        unsigned int  gdrx_gauge_state  : 1;  /* bit[30]   : 测量状态查询。1，正在测量。 */
        unsigned int  gdrx_sleep_state  : 1;  /* bit[31]   : 睡眠状态查询。1，正在睡眠。 */
    } reg;
} GBBP_GAUGE_RESULT_RPT_UNION;
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_START  (0)
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_END    (27)
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_START   (30)
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_END     (30)
#define GBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_START   (31)
#define GBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_END     (31)


/*****************************************************************************
 结构名    : GBBP_IMI_INT_TDMA_QB_UNION
 结构说明  : IMI_INT_TDMA_QB 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      imi_int_tdma_qb_reg;
    struct
    {
        unsigned int  imi_int_tdma_qb : 13; /* bit[0-12] : IMI时钟域任何中断上报时GTC的TDMA QB计数，测试用 */
        unsigned int  reserved        : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_IMI_INT_TDMA_QB_UNION;
#define GBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_START  (0)
#define GBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_END    (12)


/*****************************************************************************
 结构名    : GBBP_SLEEP_INT_TDMA_QB_UNION
 结构说明  : SLEEP_INT_TDMA_QB 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      sleep_int_tdma_qb_reg;
    struct
    {
        unsigned int  sleep_int_tdma_qb : 13; /* bit[0-12] : 32K时钟中断上报时GTC的TDMA QB计数，测试用 */
        unsigned int  reserved          : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_SLEEP_INT_TDMA_QB_UNION;
#define GBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_START  (0)
#define GBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_END    (12)


/***======================================================================***
                     (3/9) register_define_g_fe_ctrl
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_G_AFC_THERM_COM_NV_UNION
 结构说明  : G_AFC_THERM_COM_NV 寄存器结构定义。地址偏移量:0x0600，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_afc_therm_com_nv_reg;
    struct
    {
        unsigned int  cpu_g_afc_therm_com_nv : 15; /* bit[0-14] : 当RFCMOS使用晶体方案时，软件gdsp配置的校准后温度补偿NV项值。
                                                                  该NV项值是开机时，晶体温度对应补偿曲线的补偿值。 */
        unsigned int  reserved               : 17; /* bit[15-31]: 保留 */
    } reg;
} GBBP_G_AFC_THERM_COM_NV_UNION;
#define GBBP_G_AFC_THERM_COM_NV_cpu_g_afc_therm_com_nv_START  (0)
#define GBBP_G_AFC_THERM_COM_NV_cpu_g_afc_therm_com_nv_END    (14)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_AFC_UNION
 结构说明  : G_RF_SSI_AFC 寄存器结构定义。地址偏移量:0x0604，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_afc_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0-0]  : 保留 */
        unsigned int  reserved_1          : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_rf_afc_reg_addr : 8;  /* bit[4-11] : 选择晶体方案时，配置给RF的TCXO SSI地址bit。 */
        unsigned int  reserved_2          : 4;  /* bit[12-15]: 保留 */
        unsigned int  rf_ssi_afc_data_cpu : 14; /* bit[16-29]: 使用晶体AFC方案时输出给RF的AFC控制字值。 */
        unsigned int  reserved_3          : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_AFC_UNION;
#define GBBP_G_RF_SSI_AFC_cpu_rf_afc_reg_addr_START  (4)
#define GBBP_G_RF_SSI_AFC_cpu_rf_afc_reg_addr_END    (11)
#define GBBP_G_RF_SSI_AFC_rf_ssi_afc_data_cpu_START  (16)
#define GBBP_G_RF_SSI_AFC_rf_ssi_afc_data_cpu_END    (29)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_WRONE_CFG_UNION
 结构说明  : G_RF_SSI_WRONE_CFG 寄存器结构定义。地址偏移量:0x0608，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_wrone_cfg_reg;
    struct
    {
        unsigned int  cpu_rf_ssi_wrone_data    : 16; /* bit[0-15] : GDSP使用CPU方式配置一个RF-SSI的寄存器对应的数据。 */
        unsigned int  cpu_rf_ssi_wrone_addr    : 8;  /* bit[16-23]: GDSP使用CPU方式配置一个RF-SSI的寄存器地址。 */
        unsigned int  cpu_rf_ssi_wrone_ind_imi : 1;  /* bit[24-24]: GDSP使用CPU方式配置一个RF-SSI的启动信号。
                                                                    逻辑自清零。 */
        unsigned int  reserved_0               : 3;  /* bit[25-27]: 保留 */
        unsigned int  rf_ssi_wrone_end_cpu     : 1;  /* bit[28-28]: 使用CPU方式将一个RF-SSI配置是否发送至BBP COMM模块的状态信号，测试用。
                                                                    0：表示结束，1表示未结束。 */
        unsigned int  reserved_1               : 3;  /* bit[29-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_WRONE_CFG_UNION;
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_data_START     (0)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_data_END       (15)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_addr_START     (16)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_addr_END       (23)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_ind_imi_START  (24)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_ind_imi_END    (24)
#define GBBP_G_RF_SSI_WRONE_CFG_rf_ssi_wrone_end_cpu_START      (28)
#define GBBP_G_RF_SSI_WRONE_CFG_rf_ssi_wrone_end_cpu_END        (28)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_REQ_EN_CFG_UNION
 结构说明  : G_RF_SSI_REQ_EN_CFG 寄存器结构定义。地址偏移量:0x060C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_req_en_cfg_reg;
    struct
    {
        unsigned int  cpu_rf_ssi_gagc_en  : 1;  /* bit[0-0]  : g-gagc ssi允许使能信号 */
        unsigned int  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_rf_ssi_wrram_en : 1;  /* bit[4-4]  : g-rf-ram ssi允许使能信号 */
        unsigned int  reserved_1          : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_rf_ssi_afc_en   : 1;  /* bit[8-8]  : g-afc ssi允许使能信号 */
        unsigned int  reserved_2          : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_rf_ssi_wrone_en : 1;  /* bit[12-12]: 写一个rf-ssi允许使能信号 */
        unsigned int  reserved_3          : 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_rf_ssi_rd_en    : 1;  /* bit[16-16]: 读 ssi允许使能信号 */
        unsigned int  reserved_4          : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_REQ_EN_CFG_UNION;
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_gagc_en_START   (0)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_gagc_en_END     (0)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrram_en_START  (4)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrram_en_END    (4)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_afc_en_START    (8)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_afc_en_END      (8)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrone_en_START  (12)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrone_en_END    (12)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_rd_en_START     (16)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_rd_en_END       (16)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_CFG_UNION
 结构说明  : G_RF_SSI_RD_CFG 寄存器结构定义。地址偏移量:0x0610，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_cfg_reg;
    struct
    {
        unsigned int  cpu_rf_ssi_rd_ind_imi : 1;  /* bit[0-0]  : 启动RF-SSI寄存器回读。
                                                                 逻辑自清零信号。 */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_rf_ssi_rd_num     : 3;  /* bit[4-6]  : RF-SSI回读寄存器个数。
                                                                 配置值为0~7，对应的回读寄存器个数为1~8。
                                                                 （注：配置为0表示回读一个寄存器） */
        unsigned int  reserved_1            : 1;  /* bit[7-7]  : 保留 */
        unsigned int  rf_ssi_rd_end_cpu     : 1;  /* bit[8-8]  : 回读完成指示信号。
                                                                 1：表示正在回读；
                                                                 0：表示完成回读操作。 */
        unsigned int  reserved_2            : 3;  /* bit[9-11] : 保留 */
        unsigned int  rf_ssi_wrram_end_cpu  : 1;  /* bit[12-12]: 写ssi-ram完成指示信号。
                                                                 1：表示正在回读；
                                                                 0：表示完成回读操作。 */
        unsigned int  reserved_3            : 19; /* bit[13-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_CFG_UNION;
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_ind_imi_START  (0)
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_ind_imi_END    (0)
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_num_START      (4)
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_num_END        (6)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_rd_end_cpu_START      (8)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_rd_end_cpu_END        (8)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_wrram_end_cpu_START   (12)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_wrram_end_cpu_END     (12)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_0DATA_UNION
 结构说明  : G_RF_SSI_RD_0DATA 寄存器结构定义。地址偏移量:0x0614，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_0data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_0data : 24; /* bit[0-23] : SSI回读配置数据0。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_0DATA_UNION;
#define GBBP_G_RF_SSI_RD_0DATA_cpu_rfic_ssi_rd_0data_START  (0)
#define GBBP_G_RF_SSI_RD_0DATA_cpu_rfic_ssi_rd_0data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_1DATA_UNION
 结构说明  : G_RF_SSI_RD_1DATA 寄存器结构定义。地址偏移量:0x0618，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_1data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_1data : 24; /* bit[0-23] : SSI回读配置数据1。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_1DATA_UNION;
#define GBBP_G_RF_SSI_RD_1DATA_cpu_rfic_ssi_rd_1data_START  (0)
#define GBBP_G_RF_SSI_RD_1DATA_cpu_rfic_ssi_rd_1data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_2DATA_UNION
 结构说明  : G_RF_SSI_RD_2DATA 寄存器结构定义。地址偏移量:0x061C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_2data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_2data : 24; /* bit[0-23] : SSI回读配置数据2。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_2DATA_UNION;
#define GBBP_G_RF_SSI_RD_2DATA_cpu_rfic_ssi_rd_2data_START  (0)
#define GBBP_G_RF_SSI_RD_2DATA_cpu_rfic_ssi_rd_2data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_3DATA_UNION
 结构说明  : G_RF_SSI_RD_3DATA 寄存器结构定义。地址偏移量:0x0620，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_3data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_3data : 24; /* bit[0-23] : SSI回读配置数据3。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_3DATA_UNION;
#define GBBP_G_RF_SSI_RD_3DATA_cpu_rfic_ssi_rd_3data_START  (0)
#define GBBP_G_RF_SSI_RD_3DATA_cpu_rfic_ssi_rd_3data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_4DATA_UNION
 结构说明  : G_RF_SSI_RD_4DATA 寄存器结构定义。地址偏移量:0x0624，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_4data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_4data : 24; /* bit[0-23] : SSI回读配置数据4。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_4DATA_UNION;
#define GBBP_G_RF_SSI_RD_4DATA_cpu_rfic_ssi_rd_4data_START  (0)
#define GBBP_G_RF_SSI_RD_4DATA_cpu_rfic_ssi_rd_4data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_5DATA_UNION
 结构说明  : G_RF_SSI_RD_5DATA 寄存器结构定义。地址偏移量:0x0628，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_5data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_5data : 24; /* bit[0-23] : SSI回读配置数据5。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_5DATA_UNION;
#define GBBP_G_RF_SSI_RD_5DATA_cpu_rfic_ssi_rd_5data_START  (0)
#define GBBP_G_RF_SSI_RD_5DATA_cpu_rfic_ssi_rd_5data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_6DATA_UNION
 结构说明  : G_RF_SSI_RD_6DATA 寄存器结构定义。地址偏移量:0x062C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_6data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_6data : 24; /* bit[0-23] : SSI回读配置数据6。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_6DATA_UNION;
#define GBBP_G_RF_SSI_RD_6DATA_cpu_rfic_ssi_rd_6data_START  (0)
#define GBBP_G_RF_SSI_RD_6DATA_cpu_rfic_ssi_rd_6data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_RD_7DATA_UNION
 结构说明  : G_RF_SSI_RD_7DATA 寄存器结构定义。地址偏移量:0x0630，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_7data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_7data : 24; /* bit[0-23] : SSI回读配置数据7。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_RD_7DATA_UNION;
#define GBBP_G_RF_SSI_RD_7DATA_cpu_rfic_ssi_rd_7data_START  (0)
#define GBBP_G_RF_SSI_RD_7DATA_cpu_rfic_ssi_rd_7data_END    (23)


/*****************************************************************************
 结构名    : GBBP_G_MIPI_REQ_EN_CFG_UNION
 结构说明  : G_MIPI_REQ_EN_CFG 寄存器结构定义。地址偏移量:0x0634，初值:0x00000011，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_mipi_req_en_cfg_reg;
    struct
    {
        unsigned int  cpu_mipi_cmd_cfg_en       : 1;  /* bit[0]   : CPU方式MIPI客户端工作使能开关，1表示通道打开，0表示通道关闭。 */
        unsigned int  reserved_0                : 3;  /* bit[1-3] : 保留 */
        unsigned int  cpu_gtc_mipi_start_cfg_en : 1;  /* bit[4]   : GTC方式MIPI客户端工作使能开关，1表示通道打开，0表示通道关闭。 */
        unsigned int  reserved_1                : 27; /* bit[5-31]: 保留 */
    } reg;
} GBBP_G_MIPI_REQ_EN_CFG_UNION;
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_mipi_cmd_cfg_en_START        (0)
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_mipi_cmd_cfg_en_END          (0)
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_gtc_mipi_start_cfg_en_START  (4)
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_gtc_mipi_start_cfg_en_END    (4)


/*****************************************************************************
 结构名    : GBBP_G_MIPI_CMD_CFG_UNION
 结构说明  : G_MIPI_CMD_CFG 寄存器结构定义。地址偏移量:0x0638，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_mipi_cmd_cfg_reg;
    struct
    {
        unsigned int  cpu_mipi_cmd_ini_addr : 7;  /* bit[0-6]  : 软件方式配置MIPI请求时，配置寄存器组的首地址。 */
        unsigned int  reserved_0            : 1;  /* bit[7]    : 保留 */
        unsigned int  cpu_mipi_cmd_num      : 7;  /* bit[8-14] : 软件方式配置MIPI请求时，配置寄存器的个数。配置范围：1～127。 */
        unsigned int  reserved_1            : 1;  /* bit[15]   : 保留 */
        unsigned int  cpu_mipi_cmd_ind_imi  : 1;  /* bit[16-16]: 软件方式配置MIPI请求时的触发脉冲信号。 */
        unsigned int  reserved_2            : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_G_MIPI_CMD_CFG_UNION;
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ini_addr_START  (0)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ini_addr_END    (6)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_num_START       (8)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_num_END         (14)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ind_imi_START   (16)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ind_imi_END     (16)


/*****************************************************************************
 结构名    : GBBP_G_RF_SSI_MIPI_CLR_REG_UNION
 结构说明  : G_RF_SSI_MIPI_CLR_REG 寄存器结构定义。地址偏移量:0x063C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_mipi_clr_reg_reg;
    struct
    {
        unsigned int  cpu_mipi_clr_ind_imi   : 1;  /* bit[0]    : 软件配置MIPI状态机异常情况的复位脉冲信号。 */
        unsigned int  reserved_0             : 15; /* bit[1-15] : 保留 */
        unsigned int  cpu_rf_ssi_clr_ind_imi : 1;  /* bit[16]   : 软件配置SSI状态机异常情况的复位脉冲信号。 */
        unsigned int  reserved_1             : 15; /* bit[17-31]: 保留 */
    } reg;
} GBBP_G_RF_SSI_MIPI_CLR_REG_UNION;
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_mipi_clr_ind_imi_START    (0)
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_mipi_clr_ind_imi_END      (0)
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_rf_ssi_clr_ind_imi_START  (16)
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_rf_ssi_clr_ind_imi_END    (16)


/*****************************************************************************
 结构名    : GBBP_G_ABB_CFG_SEL_UNION
 结构说明  : G_ABB_CFG_SEL 寄存器结构定义。地址偏移量:0x0644，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_abb_cfg_sel_reg;
    struct
    {
        unsigned int  cpu_abb_code_sel_g : 1;  /* bit[0]   : ABB上下行数据自然码、补码模式选择。
                                                             1：表示自然码，0：表示补码，GSM专用。 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_G_ABB_CFG_SEL_UNION;
#define GBBP_G_ABB_CFG_SEL_cpu_abb_code_sel_g_START  (0)
#define GBBP_G_ABB_CFG_SEL_cpu_abb_code_sel_g_END    (0)


/*****************************************************************************
 结构名    : GBBP_G_MASTER_MEA_G_EN_UNION
 结构说明  : G_MASTER_MEA_G_EN 寄存器结构定义。地址偏移量:0x0658，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_master_mea_g_en_reg;
    struct
    {
        unsigned int  cpu_master_mea_g_en : 1;  /* bit[0-0] : 主模测G的方式选择。
                                                              0：背景搜；
                                                              1：非背景搜。 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} GBBP_G_MASTER_MEA_G_EN_UNION;
#define GBBP_G_MASTER_MEA_G_EN_cpu_master_mea_g_en_START  (0)
#define GBBP_G_MASTER_MEA_G_EN_cpu_master_mea_g_en_END    (0)


/*****************************************************************************
 结构名    : GBBP_G_ABB_TRX_LOOP_EN_UNION
 结构说明  : G_ABB_TRX_LOOP_EN 寄存器结构定义。地址偏移量:0x065C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_abb_trx_loop_en_reg;
    struct
    {
        unsigned int  cpu_gabb_trx_loop_tx_en : 1;  /* bit[0-0] : 环回模式下，上行通道使能开关。 */
        unsigned int  cpu_gabb_trx_loop_en    : 1;  /* bit[1-1] : 环回模式使能。 */
        unsigned int  reserved                : 30; /* bit[2-31]: 保留 */
    } reg;
} GBBP_G_ABB_TRX_LOOP_EN_UNION;
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_tx_en_START  (0)
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_tx_en_END    (0)
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_en_START     (1)
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_en_END       (1)


/*****************************************************************************
 结构名    : GBBP_G_AUXDAC_EN_CFG_UNION
 结构说明  : G_AUXDAC_EN_CFG 寄存器结构定义。地址偏移量:0x0690，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g_auxdac_en_cfg_reg;
    struct
    {
        unsigned int  cpu_g_auxdac_close_cfg : 11; /* bit[0-10] : AuxDAC打开控制字配置，该控制字在gtc_gapc_en线控下降沿发送至AuxDAC。 */
        unsigned int  reserved_0             : 5;  /* bit[11-15]: 保留 */
        unsigned int  cpu_g_auxdac_open_cfg  : 11; /* bit[16-26]: AuxDAC打开控制字配置，该控制字在gtc_gapc_en线控信号上升沿发送至AuxDAC。 */
        unsigned int  reserved_1             : 5;  /* bit[27-31]: 保留 */
    } reg;
} GBBP_G_AUXDAC_EN_CFG_UNION;
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_close_cfg_START  (0)
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_close_cfg_END    (10)
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_open_cfg_START   (16)
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_open_cfg_END     (26)


/*****************************************************************************
 结构名    : GBBP_DATA_FIFO_RST_UNION
 结构说明  : DATA_FIFO_RST 寄存器结构定义。地址偏移量:0x0694，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      data_fifo_rst_reg;
    struct
    {
        unsigned int  data_fifo_rst       : 1;  /* bit[0-0] : fifo复位信号，在FIFO状态异常时，配置为1，进行清零 */
        unsigned int  data_fifo_full_rpt  : 1;  /* bit[1-1] : FIFO满信号上报 */
        unsigned int  data_fifo_empty_rpt : 1;  /* bit[2-2] : FIFO空信号上报 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} GBBP_DATA_FIFO_RST_UNION;
#define GBBP_DATA_FIFO_RST_data_fifo_rst_START        (0)
#define GBBP_DATA_FIFO_RST_data_fifo_rst_END          (0)
#define GBBP_DATA_FIFO_RST_data_fifo_full_rpt_START   (1)
#define GBBP_DATA_FIFO_RST_data_fifo_full_rpt_END     (1)
#define GBBP_DATA_FIFO_RST_data_fifo_empty_rpt_START  (2)
#define GBBP_DATA_FIFO_RST_data_fifo_empty_rpt_END    (2)


/***======================================================================***
                     (4/9) register_define_g_fe_ctrl_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_G_RFIC_SSI_RAM_UNION
 结构说明  : G_RFIC_SSI_RAM 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: g本频或异频H的rfic-ssi RAM
*****************************************************************************/
typedef union
{
    unsigned int      g_rfic_ssi_ram_reg;
    struct
    {
        unsigned int  g_rfic_ssi_ram_data : 16; /* bit[0-15] : g本频或强配的rfic-ssi RAM。
                                                               数据
                                                               [15:0]：rfic的寄存器数据。 */
        unsigned int  g_rfic_ssi_ram_addr : 8;  /* bit[16-23]: g本频或强配的rfic-ssi RAM。
                                                               数据：
                                                               [23:16]：rfic的寄存器地址； */
        unsigned int  reserved            : 8;  /* bit[24-31]: 保留 */
    } reg;
} GBBP_G_RFIC_SSI_RAM_UNION;
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_data_START  (0)
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_data_END    (15)
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_addr_START  (16)
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_addr_END    (23)


/***======================================================================***
                     (5/9) register_define_gtc_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_GTC_CFG_RAM_UNION
 结构说明  : GTC_CFG_RAM 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 有效地址范围0x0000～0x07FF
*****************************************************************************/
typedef union
{
    unsigned int      gtc_cfg_ram_reg;
    struct
    {
        unsigned int  gtc_cfg_data : 16; /* bit[0-15] : GTC指令配置RAM，每个32bit中只有低16bit有效。 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} GBBP_GTC_CFG_RAM_UNION;
#define GBBP_GTC_CFG_RAM_gtc_cfg_data_START  (0)
#define GBBP_GTC_CFG_RAM_gtc_cfg_data_END    (15)


/***======================================================================***
                     (6/9) register_define_g_addr_2x_mem
 ***======================================================================***/
/***======================================================================***
                     (7/9) register_define_g_addr_3x_mem
 ***======================================================================***/
/***======================================================================***
                     (8/9) register_define_g_addr_5x_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_UL_MAP_CFG_RAM_UNION
 结构说明  : UL_MAP_CFG_RAM 寄存器结构定义。地址偏移量:0x0600，初值:0x00000000，宽度:32
 寄存器说明: 有效地址范围0x0600～0x0638
*****************************************************************************/
typedef union
{
    unsigned int      ul_map_cfg_ram_reg;
    struct
    {
        unsigned int  ul_map_cfg_data : 30; /* bit[0-29] : CPU下发的待调制数据，低30bit有效 */
        unsigned int  reserved        : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_UL_MAP_CFG_RAM_UNION;
#define GBBP_UL_MAP_CFG_RAM_ul_map_cfg_data_START  (0)
#define GBBP_UL_MAP_CFG_RAM_ul_map_cfg_data_END    (29)


/***======================================================================***
                     (9/9) register_define_g_addr_6x_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : GBBP_DC_OFFSET_RAM_UNION
 结构说明  : DC_OFFSET_RAM 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 直流偏执调整值粗调值存储RAM，到0x00FF结束
*****************************************************************************/
typedef union
{
    unsigned int      dc_offset_ram_reg;
    struct
    {
        unsigned int  dc_offset_rfic_i : 14; /* bit[0-13] : 直流偏执调整值粗调值存储RAM访问地址，一个地址表示28bit，其中低16bit中的14bit表示I路，高16bit中的14bit为Q路。配置的14bit为有符号数。 */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: 保留 */
        unsigned int  dc_offset_rfic_q : 14; /* bit[16-29]: 直流偏执调整值粗调值存储RAM访问地址，一个地址表示28bit，其中低16bit中的14bit表示I路，高16bit中的14bit为Q路。配置的14bit为有符号数。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留 */
    } reg;
} GBBP_DC_OFFSET_RAM_UNION;
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_i_START  (0)
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_i_END    (13)
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_q_START  (16)
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_q_END    (29)


/*****************************************************************************
 结构名    : GBBP_CHANNEL_GAIN_RAM_UNION
 结构说明  : CHANNEL_GAIN_RAM 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: 前向通道增益调整值存储RAM，到0x04FF结束
*****************************************************************************/
typedef union
{
    unsigned int      channel_gain_ram_reg;
    struct
    {
        unsigned int  channel_gain_rfic : 11; /* bit[0-10] : 前向通道增益调整值存储RAM。CHANNEL_GAIN参考配置参见表19，此表在实际使用时，需要进行实测后得出。 */
        unsigned int  reserved          : 21; /* bit[11-31]: 保留 */
    } reg;
} GBBP_CHANNEL_GAIN_RAM_UNION;
#define GBBP_CHANNEL_GAIN_RAM_channel_gain_rfic_START  (0)
#define GBBP_CHANNEL_GAIN_RAM_channel_gain_rfic_END    (10)




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

#endif /* end of bbp_gsm_interface.h */
