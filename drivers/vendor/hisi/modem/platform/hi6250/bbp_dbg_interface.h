

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "soc_baseaddr_interface.h"

#ifndef __BBP_DBG_INTERFACE_H__
#define __BBP_DBG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_BBP_DBG
 ***======================================================================***/
/* 寄存器说明：软复位寄存器
 bit[31:8]   dbg模块版本号。
             由发布时间表示，bit31~24表示年，bit23~16表示月，bit15~8表示日。如2012年5月20日版本，版本号为：0x120520
 bit[7:2]    保留。
 bit[1]      sdr模块软复位信号。复位SDR通路逻辑电路，包括dbg_reg；
             1：表示复位
             0：表示清复位
 bit[0]      dbg模块软复位信号。复位DBG的tl_dbg模块
             1：表示复位
             0：表示清复位
   UNION结构:  DBG_DBG_SRST_UNION */
#define DBG_DBG_SRST_ADDR                             (SOC_BBP_DBG_BASE_ADDR + 0x4000)

/* 寄存器说明：时钟门控寄存器
 bit[31:13]  保留。
 bit[12]     模块RAM时钟门控选择信号。
             0：时钟门控有效。门控开启；(缺省值)　　
             1：时钟门控无效。门控关闭。　　　　　　　　　　　　　　　
 bit[11:8]   Service ID的GUX SSID信息配置信息。
             配置值为：0xB
 bit[7:5]    保留。
 bit[4]      Bus数据的DMA通道变更的ID选择。
             0：Bus数据的DMA通道ID保持，ID=F8；(缺省值)　　
             1：Bus数据变更为DMA的Data通道ID选择，ID=0xF9。　　　　　　　　　　　　　　　
 bit[3:0]    DBG数据的DMA通道8位ID值的高4位ID指示。
             DBG缺省值=4'hF。
             Bus数据ID=0xF8；
             Dat数据ID=0xF9；
             Log数据ID=0xFA。
   UNION结构:  DBG_DBG_GATE_UNION */
#define DBG_DBG_GATE_ADDR                             (SOC_BBP_DBG_BASE_ADDR + 0x4004)

/* 寄存器说明：HDLC诊断标识寄存器
   详      述：诊断数据标志信息。
               配置值为：0x48495349，显示为："HISI"
   UNION结构 ：无 */
#define DBG_DBG_DIAG_ID_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4008)

/* 寄存器说明：传输帧头配置寄存器
 bit[31:24]  消息类型配置信息。
             配置值为：0x03
 bit[23:16]  Session ID配置信息。
             配置值为：0x01　　　　　　　　　　　
 bit[15:12]  Service ID的LTE SSID信息配置信息。
             配置值为：0x4
 bit[11:8]   Service ID的TDS SSID信息配置信息。
             配置值为：0x8
 bit[7:0]    Service ID的SID信息配置信息。
             配置值为：0x02
   UNION结构:  DBG_DBG_SRV_ID_UNION */
#define DBG_DBG_SRV_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x400C)

/* 寄存器说明：DBG BUS ID寄存器
   详      述：DBG BUS帧头的ID标识。
               缺省配置值为：0x4f008000(融合版本)
   UNION结构 ：无 */
#define DBG_DBG_BUS_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4010)

/* 寄存器说明：传输帧长度寄存器
 bit[31:16]  采样数据帧长配置信息。
             数据帧长包括诊断包头、Service ID等包头信息。单位为byte。
             可选帧长配置值有：
             0x0800(2048byte)(缺省值)；
             0x0200(512byte)；(只支持ASIC版本)
             0x0400(1024byte)(只支持ASIC版本)
 bit[15:0]   BUS读写数据帧长配置信息。
             数据帧长包括诊断包头、Service ID等包头信息。单位为byte。
             可选帧长配置值有：
             0x0800(2048byte)(缺省值)；
             0x0200(512byte)；
             0x0400(1024byte)。　　　　　　　　　　　　
   UNION结构:  DBG_DBG_FRM_LEN_UNION */
#define DBG_DBG_FRM_LEN_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4014)

/* 寄存器说明：LTE BUS采集数据选择寄存器
 bit[31:27]  GSM2模块的BUS数据采集选择信号。
             0：不选择；1：选择。
             bit27：gtc_mem、reg_1模块(0x88_0000~0x88_1fff)；
             bit28：dec_rpt_mem、apc_mem、tsc_mem、ulcode_data_mem、reg_2模块(0x88_2000~0x88_3fff)；
             bit29：reg_3、dldem_mem1、dldem_mem2、dldem_mem3模块(0x88_4000~0x88_5fff)；
             bit30：agc_mem1、agc_mem2、gck_mem模块(0x880_6000~0x88_7fff)；
             bit31：fe_ctrl_mem、fe_ctrl、reg_4模块(0x88_8000~0x88_ffff)。
 bit[26:23]  GSM1模块的BUS数据采集选择信号。
             0：不选择；1：选择。
             bit23：dec_rpt_mem、apc_mem、tsc_mem、ulcode_data_mem、reg_2模块(0x80_2000~0x80_3fff)；
             bit24：reg_3、dldem_mem1、dldem_mem2、dldem_mem3模块(0x80_4000~0x80_5fff)；
             bit25：agc_mem1、agc_mem2、gck_mem模块(0x80_6000~0x80_7fff)；
             bit26：fe_ctrl_mem、fe_ctrl、reg_4模块(0x80_8000~0x80_ffff)。
 bit[22:18]  U1模块的BUS数据采集使能信号。
             0：不使能；1：使能。
             bit18：mp、mp_rpt_mem、cs、cs_rpt_mem、rf_ctrl模块(0x90_2000~0x90_3fff)；
             bit19：dldem、pc模块(0x90_4000~0x90_4fff、0x90_6000~0x90_6fff)；
             bit20：ul、ulcode_para_mem模块(0x90_c000~0x90_cfff、0x90_e000~0x90_efff)；
             bit21：lmmse、lmmse_mem、dldec_dpa、dldec_para_mem、dldec_dbg_rpt_mem、dldec_dpa_rpt_head模块(0x90_8000~0x90_bfff)；
             bit22：dldec_r99_dc、lmmse_dc、lmmse_mem_dc、dldec_dpa_dc、dldec_dbg_rpt_dc_mem、dldec_dpa_rpt_head_dc、ul_dc模块(0x92_7000~0x92_cfff)；
 bit[17:16]  DBG_BUS读写采数屏蔽信号。
             0：使能BUS操作；
             1：屏蔽BUS操作。
             bit16:读操作屏蔽信号；
             bit17:写操作屏蔽信号。
 bit[15]     COM(ctu、irm/gu_bbp_mst、et、abb)模块的BUS数据采集选择信号。
             0：不选择；1：选择。
             地址：0xf8_0000~0xf8_7fff、0xf8_8000~0xf8_ffff、0xf9_0000~0xf9_7fff、0xfa_0000~0xfa_7fff。
 bit[14]     LTE top(int、stu、crg)模块的BUS数据采集选择信号。(0x70_0000~0x7f_ffff)
             0：不选择；1：选择。
 bit[13]     保留(原dbg模块)。
 bit[12]     DMA(sctrl、dbg、dbg_trig、dma)模块的BUS数据采集选择信号。
             0：不选择；1：选择。
             地址：0xfc_0000~0xfc_ffff。
 bit[11]     GSM1模块的BUS数据采集选择信号(原GSM模式)。
             0：不使能；1：使能。
             gtc_mem、reg_1模块(0x80_0000~0x80_1fff)；
 bit[10]     U1模块的BUS数据采集使能信号(原UMST模式)。
             0：不选择；1：选择。
             cm_timing、ck_mem、drx_2ms模块(0x90_1000~0x90_1fff)；
 bit[9:8]    保留。
 bit[7]      LTE tdl模块的BUS数据采集选择信号。(0xc0_0000~0xcf_ffff)
             0：不选择；1：选择。
 bit[6]      LTE pdu模块的BUS数据采集选择信号。(0xb0_0000~0xbf_ffff)
             0：不选择；1：选择。
 bit[5]      LTE vdl模块的BUS数据选择信号。(0x50_0000~0x5f_ffff)
             0：不选择；1：选择。
 bit[4]      LTE cqi模块的BUS数据选择信号。(0xa0_0000~0xaf_ffff)
             0：不选择；1：选择。
 bit[3]      LTE ul模块的BUS数据选择信号。(0x60_0000~0x6f_ffff)
             0：不选择；1：选择。
 bit[2]      LTE fpu模块的BUS数据选择信号。(0x10_0000~0x1f_ffff)
             0：不选择；1：选择。
 bit[1]      LTE rfin模块的BUS数据选择信号。(0x00_0000~0x0f_ffff)
             0：不选择；1：选择。
 bit[0]      LTE pb模块的BUS数据选择信号。(0x40_0000~0x4f_ffff)
             0：不选择；1：选择。
   UNION结构:  DBG_LTE_BUS_SEL_UNION */
#define DBG_LTE_BUS_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4018)

/* 寄存器说明：TDS BUS采集数据选择寄存器
 bit[31:26]  C2模块的BUS数据采集选择信号。
             0：不选择；
             1：选择。
             bit26：glb模块(0x2e_0000~0x2e_0fff)；
             bit27：timing_int模块(0x2e_1000~0x2e_1fff)；
             bit28：mps_cs模块(0x2e_2000~0x2e_2fff)；
             bit29：dldec模块(0x2e_4000~0x2e_4fff)；
             bit30：ulcode模块(0x2e_b000~0x2e_bfff)；
             bit31：fe_ctrl、ssi_mem、mipi_mem、gpio_mem、hkadc_mem模块(0x2e_f000~0x2e_ffff)。
 bit[25]     WTC2 FE模块的BUS数据采集选择信号。
             0：不选择；
             1：选择。
             包括模块：
             dl_fe、dl_fe_dc、dl_fe_mctrl、wc_dump、wc_dump_mem、ul_fe_mem、w_pa_pd、w_pa_pd_mem、ul_fe(0x0x29_0000~0x29_ffff)；
 bit[24]     WTC2 COM模块的BUS数据采集选择信号。
             0：不选择；
             1：选择。
             包括模块：
             int、fe_ctrl_mem、fe_ctrl(0x0x20_0000~0x20_0fff)；
             dldec_r99_para_mem、dldec_r99_reg1、dldec_r99_vtb_head、dldec_r99_vtb_rpt_mem、dldec_r99_turbo_head、dldec_r99_turbo_rpt_mem、dldec_r99_reg2(0x20_7000~0x20_7fff)；
 bit[23:22]  保留。
 bit[21:16]  C1模块的BUS数据采集选择信号。
             0：不选择；
             1：选择。
             bit16：glb模块(0x9e_0000~0x9e_0fff)；
             bit17：timing_int模块(0x9e_1000~0x9e_1fff)；
             bit18：mps_cs模块(0x9e_2000~0x9e_2fff)；
             bit19：dldec模块(0x9e_4000~0x9e_4fff)；
             bit20：ulcode模块(0x9e_b000~0x9e_bfff)；
             bit21：fe_ctrl、ssi_mem、mipi_mem、gpio_mem、hkadc_mem模块(0x9e_f000~0x9e_ffff)。
 bit[15:12]  U2模块的BUS数据采集使能信号。
             0：不使能；1：使能。
             bit12：cm_timing、ck_mem、drx_2ms模块(0x20_1000~0x20_1fff)；
             bit13：mp、mp_rpt_mem、cs、cs_rpt_mem、rf_ctrl模块(0x20_2000~0x20_3fff)；
             bit14：dldem、pc模块(0x20_4000~0x20_4fff、0x20_6000~0x20_6fff)；
             bit15：ul、ulcode_para_mem模块(0x20_c000~0x20_cfff、0x20_e000~0x20_efff)；
 bit[11]     保留。
 bit[10:0]   TDS 模块的BUS数据采集选择信号。
             0：不选择；1：选择。
             bit0：stu模块的BUS采集选择信号；(0xd0_0000~0xd0_3fff)
             bit1：保留；
             bit2：rfc模块的BUS采集选择信号；(0xd0_4000~0xd0_5fff)
             bit3：wtc1_com模块的BUS选择信号(原viterbi模块)；
             int、cpc_drx、fe_ctrl_mem、fe_ctrl(0x0x90_0000~0x90_0fff)；
             dldec_r99_para_mem、dldec_r99_reg1、dldec_r99_vtb_head、dldec_r99_vtb_rpt_mem、dldec_r99_turbo_head、dldec_r99_turbo_rpt_mem、dldec_r99_reg2(0x90_7000~0x90_7fff)；
             bit4：hsupa模块的BUS采集选择信号；(0xe1_0000~0xe1_3fff)
             bit5：turbo模块的BUS采集选择信号；(0xe2_0000~0xe2_7fff)
             bit6：top模块的BUS采集选择信号；(0xe2_8000~0xe2_ffff)
             bit7：harq_reg模块的BUS采集选择信号；(0xe3_0000~0xe3_ffff)
             bit8：wtc1_fe模块的BUS选择信号(原tds agcd(own)模块)；
             dl_fe、dl_fe_dc、dl_fe_mctrl、wc_dump、wc_dump_mem、ul_fe_mem、w_pa_pd、w_pa_pd_mem、ul_fe(0x0x99_0000~0x99_ffff)；
             bit9：保留(原tds agcc(ommon)模块)；
             bit10：保留(原tds agcu(p)模块)；
   UNION结构:  DBG_TDS_BUS_SEL_UNION */
#define DBG_TDS_BUS_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x401C)

/* 寄存器说明：BUS采数使能寄存器
 bit[31:1]   保留。
 bit[0]      BUS数据采数使能信号。
             0：不使能；
             1：使能。
   UNION结构:  DBG_DBG_BUS_EN_UNION */
#define DBG_DBG_BUS_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4020)

/* 寄存器说明：DAT通道选择寄存器
 bit[31:10]  保留。
 bit[9:8]    ABB ch0/1通道选择信号，与ABB数采使能配合使用。
             0：选择ch1通道；
             1：选择ch0通道；
             2：选择ch0/1通道的并发CA，ABB数采选择下行数据
 bit[7]      保留。
 bit[6:4]    TDS数采类型选择寄存器。
             与DAT ID基址配合使用。
             1：下行天线0数据采集，      ID=0x41000801；
             2：下行天线1数据采集，      ID=0x41000802；
             3：下行双天线数据采集，     ID=0x41000803；
             4：上行数据采集，材         ID=0x41000804；
             5：上行+下行天线0数据采集， ID=0x41000805；
             6：上行+下行天线1数据采集， ID=0x41000806；
             7：上行+下行双天线数据采集，ID=0x41000807；
             其它：保留。
 bit[3:0]    DBG模块上报dat数据类型选择。
             0：RFIN上报的dat数据(缺省值)
             1：FPU上报的dat数据
             2：CQI上报的dat数据
             3：PDU上报的dat数据
             4：TDS上报的dat数据
             5：ABB上报下行通道dat数据(不支持FPGA版本)
             6：ABB上报上行通道dat数据(不支持FPGA版本)
             7：ABB上报模拟通道dat数据(不支持FPGA版本)
             8：BBP COMMON上报的dat数据
             15~9：保留
   UNION结构:  DBG_DBG_DAT_SEL_UNION */
#define DBG_DBG_DAT_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4024)

/* 寄存器说明：DAT采数使能寄存器
 bit[31:1]   保留。
 bit[0]      DAT数据采数使能信号。
             0：不使能；
             1：使能。
   UNION结构:  DBG_DBG_DAT_EN_UNION */
#define DBG_DBG_DAT_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4028)

/* 寄存器说明：LOG通道选择寄存器
 bit[31:3]   保留。
 bit[2:0]    DBG模块上报LOG数据类型选择。
             0：保留(缺省值)
             1：FPU上报的log数据
             2：PB上报的log数据
             3：PDU上报的log数据
             4：TDL上报的log数据
             5：TDL2上报的log数据
             7~6：保留　　　　　　　
   UNION结构:  DBG_DBG_LOG_SEL_UNION */
#define DBG_DBG_LOG_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x402C)

/* 寄存器说明：LOG通道使能寄存器
 bit[31:1]   保留。
 bit[0]      L模LOG数据传输使能信号。
             0：不使能；
             1：使能。
   UNION结构:  DBG_DBG_LOG_EN_UNION */
#define DBG_DBG_LOG_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4030)

/* 寄存器说明：DBG采数通信模式选择寄存器
 bit[31:12]  保留。
 bit[11:8]   DBG采数从模时标选择信号。
             0：保留(缺省值)
             1：LTE；
             2：TDS；
             3：UMTS(U1)；
             4：EVDO&1X(X1)；
             5：1X(X2)；
             6：R99(U2)；
             7：GSM1；
             8：GSM2；
             9~15：保留
 bit[7:4]    DBG采数主模时标选择信号。
             0：保留(缺省值)
             1：LTE；
             2：TDS；
             3：UMTS(U1)；
             4：EVDO&1X(X1)；
             5：1X(X2)；
             6：R99(U2)；
             7：GSM1；
             8：GSM2；
             9~15：保留
 bit[3:0]    保留。
   UNION结构:  DBG_DBG_TL_SEL_UNION */
#define DBG_DBG_TL_SEL_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4034)

/* 寄存器说明：DAT/BUS/LOG通道告警寄存器
 bit[31:14]  保留。
 bit[13:12]  BUS通道告警信息。只读，对应位写1清0。
             bit13：burst读数据出错告警信号；
             bit12：通道fifo溢出告警信号。
 bit[11:8]   lte的log包传输告警信息。只读，对应位写1清0。
             bit11：传输帧数据小于设置值且无结束标识的告警；
             bit10：传输帧数据大于设置值的告警；
             bit9：传输帧数据小于设置值的告警；
             bit8：通道fifo溢出告警信号。
 bit[7:5]    保留。
 bit[4:1]    DATA数据接口指示信息。只读，对应位写1清0
             bit4：dat数据结束指示；
             bit3：vld有效指示；
             bit2：eop有效指示；
             bit1：sop有效指示；
 bit[0]      DATA数据帧传输告警信息。只读，对应位写1清0。
             bit0：通道fifo溢出告警信号。
   UNION结构:  DBG_DBG_DIAG_ALARM_UNION */
#define DBG_DBG_DIAG_ALARM_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x403C)

/* 寄存器说明：BUS的通道传输帧计数器
   详      述：BUS数据传输帧计数器。
               只读，32位计数器。通道使能清0，计数满保持；
   UNION结构 ：无 */
#define DBG_DBG_BUS_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4040)

/* 寄存器说明：DAT数据通道传输帧计数器
   详      述：DAT数据传输帧计数器。
               只读，32位计数器。通道使能清0，计数满保持；
   UNION结构 ：无 */
#define DBG_DBG_DAT_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4044)

/* 寄存器说明：LOG通道传输帧计数器
   详      述：LOG数据传输帧计数器。
               只读，32位计数器。通道使能清0，计数满保持；
   UNION结构 ：无 */
#define DBG_DBG_LOG_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4048)

/* 寄存器说明：DBG的DMA请求/响应次数计数器
 bit[31:16]  DBG的DMA接口的gnt响应次数计数器。
             只读，16位计数器。Test_switch开启有效，关闭清0；
 bit[15:0]   DBG的DMA接口的req请求次数计数器。
             只读，16位计数器。Test_switch开启有效，关闭清0；
   UNION结构:  DBG_DBG_DMA_CNT_UNION */
#define DBG_DBG_DMA_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4058)

/* 寄存器说明：dbg帧的sop计数器
 bit[31:24]  dat数据的sop个数计数器。
             只读，8位计数器。对0x003C的bit1写1清0。
 bit[23:10]  保留。
 bit[9:0]    dat_bst模块fifo最大存储数据个数。
             只读，10位计数器，数据范围：0~512。
             对0x003C的bit3写1清0。
   UNION结构:  DBG_DBG_SOP_CNT_UNION */
#define DBG_DBG_SOP_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x405C)

/* 寄存器说明：dbg的ram状态计数器
 bit[31:29]  保留。
 bit[28]     指示DBG通道RAM实时非空状态。
             0：ram为空。1：ram非空；
 bit[27:25]  保留。
 bit[24:16]  指示DBG通道RAM达到最大burst存储个数。
             Test_switch开启有效，关闭清0；
             9位计数器，数据范围：0~256。
 bit[15:13]  保留。
 bit[12:0]   指示DBG通道RAM达到最大存储数据(64bit)个数。
             Test_switch开启有效，关闭清0；
             13位计数器，数据范围：0~4096。
   UNION结构:  DBG_DBG_RAM_CNT_UNION */
#define DBG_DBG_RAM_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4068)

/* 寄存器说明：dbg通道req的响应时间计数器
 bit[31:24]  保留。
 bit[23:0]   指示DBG通道RAM的req/gnt间最大时间计数。
             Test_switch开启有效，关闭清0；
             24位计数器，时间计算与时钟相关。
   UNION结构:  DBG_DBG_TIME_CNT_UNION */
#define DBG_DBG_TIME_CNT_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x406C)

/* 寄存器说明：dbg的通用选择寄存器
 bit[31:9]   保留。
 bit[8]      DBG的BUS与DATA通道交叉传输使能信号。
             0：正常传输(缺省模式)；
             1：交叉使能。
 bit[7:5]    保留。
 bit[4]      定时屏蔽信号。(验证需求功能)
             0：定时信息正常采集与传输；
             1：定时信息被屏蔽，值都为0。
 bit[3:1]    保留。
 bit[0]      BUS采数地址段模式的使能信号。
             0：不使能；
             1：使能。
   UNION结构:  DBG_DBG_GLB_SEL_UNION */
#define DBG_DBG_GLB_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4090)

/* 寄存器说明：bus采数起始地址寄存器
 bit[31:24]  保留。
 bit[23:0]   BUS采数地址段模式的起始地址。选择范围：0~0xffffff
   UNION结构:  DBG_BUS_ADDR_VALUE_UNION */
#define DBG_BUS_ADDR_VALUE_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x4094)

/* 寄存器说明：bus采数地址范围寄存器
 bit[31:24]  保留。
 bit[23:0]   BUS采数地址段模式地址范围(大小)。选择范围：0~0xffffff
   UNION结构:  DBG_BUS_ADDR_SIZE_UNION */
#define DBG_BUS_ADDR_SIZE_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x4098)

/* 寄存器说明：TDS DAT ID寄存器
   详      述：TDS DAT ID基址。
               缺省配置值为：0x41000800(融合版本)
   UNION结构 ：无 */
#define DBG_TDS_DAT_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x40A0)

/* 寄存器说明：TDS DAT采集模式选择寄存器
 bit[31:16]  计数模式的DAT采集帧个数。(支持TDS/ABB)
 bit[15:2]   保留。
 bit[1]      TDS/ABB DAT采集模式选择信号。
             0：计数模式，与计数值组合使用；
             1：开关模式。
 bit[0]      保留。
   UNION结构:  DBG_TDS_DAT_MODE_UNION */
#define DBG_TDS_DAT_MODE_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x40A8)

/* 寄存器说明：DAT测试配置寄存器
 bit[31:10]  保留。
 bit[9:8]    DAT测试类型配置信号。
             Bit8：数据替换模式。在实际TDS采数模式下，用确定的测试数据替换DAT接口数据，检验通道传输正确性；
             Bit9：数据测试模式。需要配置为TDS采数模式，内部产生数据进行数采通道与带宽测试；
             配置信息置1有效。
 bit[7:0]    DAT测试数据带宽配置信号。
             其值为时钟计数，如初值=F，则每隔16cycle，采集传输1个64bit数据，如时钟频率=150MHz，则测试数据带宽=600Mbps。
   UNION结构:  DBG_DAT_TEST_UNION */
#define DBG_DAT_TEST_ADDR                             (SOC_BBP_DBG_BASE_ADDR + 0x40AC)

/* 寄存器说明：TDS DAT接口状态寄存器
 bit[31:7]   保留。
 bit[6:4]    TDS DAT接口类型状态指示信号。
             只读，对应位写1清0。
             Bit4：下行单天线数据类型状态指示；
             Bit5：下行双天线数据类型状态指示；
             Bit6：上行数据类型状态指示；
 bit[3:1]    保留。
 bit[0]      TDS DAT类型配置错误指示信号。
             只读，对应位写1清0。
   UNION结构:  DBG_TDS_DAT_STS_UNION */
#define DBG_TDS_DAT_STS_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x40B0)

/* 寄存器说明：DBG BUS采集模式选择寄存器
 bit[31:16]  计数模式的BUS采集帧个数。
 bit[15:2]   保留。
 bit[1]      DBG BUS采集模式选择信号。
             0：计数模式，与计数值组合使用；
             1：开关模式。
 bit[0]      保留。
   UNION结构:  DBG_DBG_BUS_MODE_UNION */
#define DBG_DBG_BUS_MODE_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x40C8)

/* 寄存器说明：DBG BUS测试配置寄存器
 bit[31:9]   保留。
 bit[8]      DBG BUS测试模式。BUS通道与带宽测试
             配置信息置1有效。
 bit[7:0]    DBG BUS测试数据带宽配置信号。
             其值为时钟计数，如初值=0x07，则每隔128cycle(0x7F)，采集传输1个64bit数据，如时钟频率=150MHz，则测试数据带宽=75Mbps。
   UNION结构:  DBG_DBG_BUS_TEST_UNION */
#define DBG_DBG_BUS_TEST_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x40CC)

/* 寄存器说明：SP MEM CTRL配置寄存器
 bit[31:16]  保留。
 bit[15:0]   SPRAM的MEM_CTRL配置。
             缺省值由统一参数提供。
   UNION结构:  DBG_SP_MEM_CTRL_UNION */
#define DBG_SP_MEM_CTRL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x40E0)

/* 寄存器说明：TP MEM CTRL配置寄存器
 bit[31:16]  保留。
 bit[15:0]   TPRAM的MEM_CTRL配置。
             缺省值由统一参数提供。
   UNION结构:  DBG_TP_MEM_CTRL_UNION */
#define DBG_TP_MEM_CTRL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x40E4)

/* 寄存器说明：ARBITER优先级选择配置寄存器
 bit[31:8]   保留。
 bit[7:0]    DDR通路的arbiter优先级选择配置。
             0：低优先级；1：高优先级。
             bit0：sdr通道；
             bit1：dbg_bus通道；
             bit2：dbg_data通道；
             bit3：dbg_log通道。
             其余保留。
   UNION结构:  DBG_ARB_PRIOR_SEL_UNION */
#define DBG_ARB_PRIOR_SEL_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x4100)

/* 寄存器说明：TEST SWITCH配置寄存器
 bit[31:5]   保留。
 bit[4]      Burst接口gnt与rd信号对齐选择。
             0：gnt与rd必须对齐；(缺省配置)
             1：gnt与rd可以不对齐。
 bit[3:1]    保留。
 bit[0]      模块测试功能项选择开关。
             0：测试功能关闭；(缺省配置)
             1：测试功能开启。
   UNION结构:  DBG_TEST_SWITCH_UNION */
#define DBG_TEST_SWITCH_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4104)

/* 寄存器说明：GNT与RD对齐状态寄存器
 bit[31:5]   保留。
 bit[4]      指示DMA的DDR接口gnt信号有效同时无rd信号状态。此位写1清0状态
 bit[3:1]    保留。
 bit[0]      指示DMA的TCM接口gnt信号有效同时无rd信号状态。此位写1清0状态
   UNION结构:  DBG_GNT_RD_STS_UNION */
#define DBG_GNT_RD_STS_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x411C)

/* 寄存器说明：TCM通道的DMA请求/响应次数计数器
 bit[31:16]  TCM的DMA接口的gnt响应次数计数器。
             Test_switch开启有效，关闭清0；
             只读，16位计数器。
 bit[15:0]   TCM的DMA接口的req请求次数计数器。
             Test_switch开启有效，关闭清0；
             只读，16位计数器。
   UNION结构:  DBG_TCM_DMA_CNT_UNION */
#define DBG_TCM_DMA_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4120)

/* 寄存器说明：tcm的ram状态计数器
 bit[31:29]  保留。
 bit[28]     指示TCM通道RAM实时非空状态。
             0：ram为空。1：ram非空；
 bit[27:22]  保留。
 bit[21:16]  指示TCM通道RAM达到最大burst存储个数。
             Test_switch开启有效，关闭清0；
             6位计数器，数据范围：0~32。
 bit[15:10]  保留。
 bit[9:0]    指示TCM通道RAM达到最大存储数据个数。
             Test_switch开启有效，关闭清0；
             10位计数器，数据范围：0~512。
   UNION结构:  DBG_TCM_RAM_CNT_UNION */
#define DBG_TCM_RAM_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4124)

/* 寄存器说明：tcm通道req的响应时间计数器
 bit[31:24]  保留。
 bit[23:0]   指示TCM通道RAM的req/gnt间最大时间计数。
             Test_switch开启有效，关闭清0；
             24位计数器，时间计算与时钟相关。
   UNION结构:  DBG_TCM_TIME_CNT_UNION */
#define DBG_TCM_TIME_CNT_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x4128)

/* 寄存器说明：DBG 采集DAT数据ID类型寄存器
   详      述：DAT数据的ID类型上报指示。
               只读，DBG的DAT采数启动时清0。
   UNION结构 ：无 */
#define DBG_DBG_DAT_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4130)

/* 寄存器说明：DBG 采集LOG数据ID类型寄存器
   详      述：LOG数据的ID类型上报指示。
               只读，DBG的LOG采数启动时清0。
   UNION结构 ：无 */
#define DBG_DBG_LOG_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4134)

/* 寄存器说明：DBG中断状态寄存器
 bit[31:7]   保留。
 bit[6:0]    DBG中断状态指示。
             0：无中断；
             1：有中断；
             bit0：dat数据溢出错误中断；
             bit1：bus数据溢出错误中断；
             bit2：bus数据burst错误中断；
             bit3：log数据溢出错误中断；
             bit4：log数据传输帧数据小于设置值错误中断；
             bit5：log数据传输帧数据大于设置值错误中断；
             bit6：log数据传输帧数据小于设置值且无结束标识错误中断。
   UNION结构:  DBG_DBG_INT_STS_UNION */
#define DBG_DBG_INT_STS_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4140)

/* 寄存器说明：DBG中断清除寄存器
 bit[31:7]   保留。
 bit[6:0]    DBG中断清除，对应位写1清0中断。
             bit0：dat数据溢出错误中断清0；
             bit1：bus数据溢出错误中断清0；
             bit2：bus数据burst错误中断清0；
             bit3：log数据溢出错误中断清0；
             bit4：log数据传输帧数据小于设置值错误中断清0；
             bit5：log数据传输帧数据大于设置值错误中断清0；
             bit6：log数据传输帧数据小于设置值且无结束标识错误中断清0。
   UNION结构:  DBG_DBG_INT_CLR_UNION */
#define DBG_DBG_INT_CLR_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4144)

/* 寄存器说明：DBG中断屏蔽寄存器
 bit[31:7]   保留。
 bit[6:0]    DBG中断屏蔽。
             0：中断屏蔽使能，中断不上报(缺省状态)
             1：中断可上报
             bit0：dat数据溢出错误中断屏蔽位；
             bit1：bus数据溢出错误中断屏蔽位；
             bit2：bus数据burst错误中断屏蔽位；
             bit3：log数据溢出错误中断屏蔽位；
             bit4：log数据传输帧数据小于设置值错误中断屏蔽位；
             bit5：log数据传输帧数据大于设置值错误中断屏蔽位；
             bit6：log数据传输帧数据小于设置值且无结束标识错误中断屏蔽位。
   UNION结构:  DBG_DBG_INT_MSK_UNION */
#define DBG_DBG_INT_MSK_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4148)

/* 寄存器说明：DBG数采类型
 bit[31:2]   保留
 bit[1:0]    模块数采ID间的过滤器，每个bit指示一个ID，例如，bit0，器ID号为dbg_id + 1，bit1，其ID号为dbg_id + 1，依此类推。
             如果bit取值为1，表明该bit对应的ID有效，否则无效：
             0，下行通道2天线数据同时采集
             1，上行发送通道数据采集
             2，下行通道单天线RXA数据采集
             3，下行通道单天线RXB数据采集
   UNION结构:  DBG_RFIN_DBG_FLT_UNION */
#define DBG_RFIN_DBG_FLT_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x4600)

/* 寄存器说明：DBG ID号
   详      述：数采文件中的ID号
   UNION结构 ：无 */
#define DBG_RFIN_DBG_ID_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4604)

/* 寄存器说明：DBG数采选择
 bit[31:18]  保留
 bit[17:16]  上行数采使能，每个bit对应一个上行载波，取值为1表明该载波数采使能：
             [1]：上行载波1数采
             [0]：上行载波0数采
 bit[15:4]   保留
 bit[3:0]    下行数采使能，每个bit对应一个下行载波，取值为1表明该通载波数采使能：
             [3]：下行载波3数采
             [2]：下行载波2数采
             [1]：下行载波1数采
             [0]：下行载波0数采
   UNION结构:  DBG_RFIN_DBG_CH_UNION */
#define DBG_RFIN_DBG_CH_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4608)

/* 寄存器说明：DBG数采模式
 bit[31:16]  数采包的个数
 bit[15:1]   保留
 bit[0]      数采上报模式：
             1'b0，数采功能触发后，采样dbg_pkg_num个数据包后自动结束
             1'b1，只要dbg_en为1就一直采数上报，不受dbg_pkg_num限制
   UNION结构:  DBG_RFIN_DBG_MODE_UNION */
#define DBG_RFIN_DBG_MODE_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x460C)

/* 寄存器说明：DBG数采使能
 bit[31:1]   保留
 bit[0]      数采使能：
             1'b0，数采功能不使能
             1'b1，数采功能使能
   UNION结构:  DBG_RFIN_DBG_EN_UNION */
#define DBG_RFIN_DBG_EN_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4610)

/* 寄存器说明：寄存器。
   详      述：模块LOG ID间过滤器0
               仅以下比特可以配置成1'b1：
               0~4/14/18/22/26/30
   UNION结构 ：无 */
#define DBG_FPU_DBG_LOG_FLT0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8400)

/* 寄存器说明：寄存器。
   详      述：模块LOG ID间过滤器1
               仅以下比特可以配置成1'b1：
               2/6/10/11/14~18/23~25/27
   UNION结构 ：无 */
#define DBG_FPU_DBG_LOG_FLT1_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8404)

/* 寄存器说明：寄存器。
 bit[31:16]  LOG信息可维可测的包个数
 bit[15:1]   保留
 bit[0]      可维可测数据上报模式：
             'b0：触发后继续采样fpu_log_pkg_num个数据包后自动结束；
             'b1：只要fpu_log_en为1就上报，没有上报个数限制。
   UNION结构:  DBG_FPU_DBG_LOG_CFG_UNION */
#define DBG_FPU_DBG_LOG_CFG_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x8408)

/* 寄存器说明：寄存器。
   详      述：前端log起始id号
   UNION结构 ：无 */
#define DBG_FPU_DBG_LOG_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x840C)

/* 寄存器说明：寄存器。
 bit[31:16]  保留
 bit[15:0]   模块DAT ID间过滤器
             [4] cfu调试信号。
             [9] fpu_ls选择信号。
             [11] fpu_lsu选择信号。
             [12] fpu_emu选择信号。
             [13] fpu_tru选择信号。
             其他bit保留
   UNION结构:  DBG_FPU_DBG_DAT_FLT_UNION */
#define DBG_FPU_DBG_DAT_FLT_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x8410)

/* 寄存器说明：寄存器。
 bit[31:16]  保留
 bit[15:3]   保留
 bit[2:1]    可维可测数据上报数据拼接模式：
             'd0：不拼接；
             'd1：保留。
             'd2：接收天线0数据拼接为一个64bit数据 word上报。
             'd3：2天线数据拼接为一个64bit数据 word上报；
 bit[0]      可维可测数据上报模式：
             'b0：触发后继续采样fpu_dbg_pkg_num个数据包后自动结束；
             'b1：只要fpu_dbg_en为1就上报，没有上报个数限制。
   UNION结构:  DBG_FPU_DBG_DAT_CFG0_UNION */
#define DBG_FPU_DBG_DAT_CFG0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8414)

/* 寄存器说明：寄存器。
   详      述：dbg起始id号,调试用
   UNION结构 ：无 */
#define DBG_FPU_DBG_DAT_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8418)

/* 寄存器说明：寄存器。
 bit[31:1]   保留
 bit[0]      LOG上报始能
             1'b1:使能
             1'b0:不使能
   UNION结构:  DBG_FPU_LOG_EN_UNION */
#define DBG_FPU_LOG_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x8424)

/* 寄存器说明：寄存器。
 bit[31:1]   保留
 bit[0]      dbg 上报是否始能
             1'b1:使能
             1'b0:不使能
   UNION结构:  DBG_FPU_DBG_EN_UNION */
#define DBG_FPU_DBG_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x8428)

/* 寄存器说明：寄存器。
 bit[31:4]   保留
 bit[3:2]    0: 选择pcc dbg数据；（保留）
             1：选择cc1 dbg数据；（保留）
             2: 选择cc2 dbg数据；（保留）
             3：选择cc3 dbg数据；（保留）
 bit[1:0]    0: 选择pcc log数据；（保留）
             1：选择cc1 log数据；（保留）
             2: 选择cc2 log数据；（保留）
             3：选择cc3 log数据；（保留）
   UNION结构:  DBG_FPU_LOG_DBG_SEL_UNION */
#define DBG_FPU_LOG_DBG_SEL_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x842C)

/* 寄存器说明：寄存器。
 bit[31:22]  保留
 bit[21:20]  FPU CC内部smu debug信息通道选择(调试用)
             2'b0，上报通道0
             2'b1，上报通道1
             2'b10，上报通道2
             2'b11，上报通道3
             生效时刻：立即生效
 bit[19:18]  保留
 bit[17:16]  FPU CC内部smp debug数据上报模式选择(调试用)
             2'b0，选择上报lsu输出的原始LS数据；
             2'b1，选择上报ls_smp输出的LS数据；
             2'b10，选择上报em_smp输出的emu和路测结果数据；
             2'b11，选择上报tru_smp输出的pdp数据
             生效时刻：立即生效
 bit[15:12]  FPU CC内部debug数据上报模式选择(调试用)
             4'b0，选择上报cfu内部状态信息；
             4'b1，选择上报dfu内部状态信息；
             4'b10，选择上报smu内部状态信息；
             4'b11，选择上报afc内部状态信息；
             4'b100，选择上报tru内部状态信息；
             4'b101，选择上报tau的内部状态信息；
             4'b110，选择上报测量全通路状态信息；
             4'b111，选择上报解调全通路状态信息；
             4'b1000，选择上报smp内部状态信息；
             4'b1001，选择上报cmu_buf内部状态信息。
             生效时刻：立即生效
 bit[11:10]  保留
 bit[9:8]    FPU rfin debug寄存器上报选择信号(调试用)
             2'b0，选择pcc rfin debug数据；
             2'b01，选择cc1 rfin debug数据；
             2'b10，选择cc2 rfin debug数据；
             2'b11，选择cc3 rfin debug数据；
             生效时刻：立即生效
 bit[7]      保留
 bit[6:4]    FPU 各cc通路debug寄存器上报选择信号(调试用)
             3'b0,pcc debug数据；
             3'b1,cc1 debug数据；
             3'b10,cc2 debug数据；
             3'b11,cc3 debug数据；
             3'b100,mlafc debug数据；
             3'b101,csu0 debug数据；
             3'b110,csu1 debug数据；
             其余保留
             生效时刻：立即生效
 bit[3:2]    保留
 bit[1:0]    FPU SMP debug数据采集选择信号(调试用)
             2'b0，选择pcc smp数据；
             2'b01，选择cc1 smp数据；
             2'b10，选择cc2 smp数据；
             2'b11，选择cc3 smp数据；
             生效时刻：立即生效
   UNION结构:  DBG_FPU_DEBUG_CTRL_UNION */
#define DBG_FPU_DEBUG_CTRL_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0xE1138610)

/* 寄存器说明：寄存器。
 bit[31:11]  保留
 bit[10:8]   保留
 bit[7:5]    保留
 bit[4]      保留
 bit[3]      保留
 bit[2:0]    保留
   UNION结构:  DBG_SMU_CC_DEBUG_SEL_UNION */
#define DBG_SMU_CC_DEBUG_SEL_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE1165950)

/* 寄存器说明：寄存器。
 bit[31:11]  保留
 bit[10:8]   保留
 bit[7:5]    保留
 bit[4]      保留
 bit[3]      保留
 bit[2:0]    保留
   UNION结构:  DBG_CC1_SMU_CC_DEBUG_SEL_UNION */
#define DBG_CC1_SMU_CC_DEBUG_SEL_ADDR                 (SOC_BBP_DBG_BASE_ADDR + 0xE1167950)

/* 寄存器说明：寄存器。
 bit[31:11]  保留
 bit[10:8]   保留
 bit[7:5]    保留
 bit[4]      保留
 bit[3]      保留
 bit[2:0]    保留
   UNION结构:  DBG_CC2_SMU_CC_DEBUG_SEL_UNION */
#define DBG_CC2_SMU_CC_DEBUG_SEL_ADDR                 (SOC_BBP_DBG_BASE_ADDR + 0xE1169950)

/* 寄存器说明：寄存器。
 bit[31:11]  保留
 bit[10:8]   保留
 bit[7:5]    保留
 bit[4]      保留
 bit[3]      保留
 bit[2:0]    保留
   UNION结构:  DBG_CC3_SMU_CC_DEBUG_SEL_UNION */
#define DBG_CC3_SMU_CC_DEBUG_SEL_ADDR                 (SOC_BBP_DBG_BASE_ADDR + 0xE116B950)

/* 寄存器说明：模块LOG ID间过滤器
   详      述：模块LOG ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU_DBG_LOG_FLT0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8000)

/* 寄存器说明：模块LOG ID间过滤器
   详      述：模块LOG ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU_DBG_LOG_FLT1_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8004)

/* 寄存器说明：模块LOG 模式寄存器
 bit[31:16]  LOG信息可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             0：触发后继续采样dbg_pkg_num个数据包后自动结束
             1：只要dbg_rpt_en为1就上报，没有上报个数限制。
 bit[0]      保留
   UNION结构:  DBG_PDU_DBG_LOG_MODE_UNION */
#define DBG_PDU_DBG_LOG_MODE_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8008)

/* 寄存器说明：模块LOG EN寄存器
 bit[31:1]   保留
 bit[0]      模块LOG使能                              
             0：可维可测功能不使能                             1：可维可测功能使能
   UNION结构:  DBG_PDU_DBG_LOG_EN_UNION */
#define DBG_PDU_DBG_LOG_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x800C)

/* 寄存器说明：模块LOG ID寄存器
   详      述：可维可测LOG 信息头文件中的ID号基址
   UNION结构 ：无 */
#define DBG_PDU_DBG_LOG_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8010)

/* 寄存器说明：模块DAT ID间过滤器
   详      述：模块DAT ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU_DBG_DAT_FLT0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8014)

/* 寄存器说明：模块DAT ID间过滤器
   详      述：模块DAT ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU_DBG_DAT_FLT1_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8018)

/* 寄存器说明：模块DAT 模式寄存器
 bit[31:16]  DAT信息可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             0：触发后继续采样dbg_pkg_num个数据包后自动结束
             1：只要dbg_rpt_en为1就上报，没有上报个数限制。
 bit[0]      保留
   UNION结构:  DBG_PDU_DBG_DAT_MODE_UNION */
#define DBG_PDU_DBG_DAT_MODE_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x801C)

/* 寄存器说明：模块DAT EN寄存器
 bit[31:1]   保留
 bit[0]      模块DAT使能                              
             0：可维可测功能不使能                             1：可维可测功能使能
   UNION结构:  DBG_PDU_DBG_DAT_EN_UNION */
#define DBG_PDU_DBG_DAT_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8020)

/* 寄存器说明：模块DAT ID寄存器
   详      述：可维可测DAT 信息头文件中的ID号基址
   UNION结构 ：无 */
#define DBG_PDU_DBG_DAT_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8024)

/* 寄存器说明：模块LOG ID间过滤器
   详      述：模块LOG ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU2_DBG_LOG_FLT0_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18000)

/* 寄存器说明：模块LOG ID间过滤器
   详      述：模块LOG ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU2_DBG_LOG_FLT1_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18004)

/* 寄存器说明：模块LOG 模式寄存器
 bit[31:16]  LOG信息可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             0：触发后继续采样dbg_pkg_num个数据包后自动结束
             1：只要dbg_rpt_en为1就上报，没有上报个数限制。
 bit[0]      保留
   UNION结构:  DBG_PDU2_DBG_LOG_MODE_UNION */
#define DBG_PDU2_DBG_LOG_MODE_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18008)

/* 寄存器说明：模块LOG EN寄存器
 bit[31:1]   保留
 bit[0]      模块LOG使能                              
             0：可维可测功能不使能                             1：可维可测功能使能
   UNION结构:  DBG_PDU2_DBG_LOG_EN_UNION */
#define DBG_PDU2_DBG_LOG_EN_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B1800C)

/* 寄存器说明：模块LOG ID寄存器
   详      述：可维可测LOG 信息头文件中的ID号基址
   UNION结构 ：无 */
#define DBG_PDU2_DBG_LOG_ID_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B18010)

/* 寄存器说明：模块DAT ID间过滤器
   详      述：模块DAT ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU2_DBG_DAT_FLT0_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18014)

/* 寄存器说明：模块DAT ID间过滤器
   详      述：模块DAT ID间过滤器
   UNION结构 ：无 */
#define DBG_PDU2_DBG_DAT_FLT1_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18018)

/* 寄存器说明：模块DAT 模式寄存器
 bit[31:16]  DAT信息可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             0：触发后继续采样dbg_pkg_num个数据包后自动结束
             1：只要dbg_rpt_en为1就上报，没有上报个数限制。
 bit[0]      保留
   UNION结构:  DBG_PDU2_DBG_DAT_MODE_UNION */
#define DBG_PDU2_DBG_DAT_MODE_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B1801C)

/* 寄存器说明：模块DAT EN寄存器
 bit[31:1]   保留
 bit[0]      模块DAT使能                              
             0：可维可测功能不使能                             1：可维可测功能使能
   UNION结构:  DBG_PDU2_DBG_DAT_EN_UNION */
#define DBG_PDU2_DBG_DAT_EN_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B18020)

/* 寄存器说明：模块DAT ID寄存器
   详      述：可维可测DAT 信息头文件中的ID号基址
   UNION结构 ：无 */
#define DBG_PDU2_DBG_DAT_ID_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B18024)

/* 寄存器说明：可维可测的开始时间
 bit[31:20]  保留
 bit[19:16]  可维可测启动时间，以系统定时参考，子帧内的符号计数
 bit[15:12]  保留
 bit[11:0]   可维可测启动时间，以系统定时参考，symbol内Ts计数
   UNION结构:  DBG_CQI_DBG_START_TIME_UNION */
#define DBG_CQI_DBG_START_TIME_ADDR                   (SOC_BBP_DBG_BASE_ADDR + 0x7300)

/* 寄存器说明：数采使能寄存器
 bit[31:1]   保留
 bit[0:0]    数据采集使能
             0：数采不使能
             1：数采使能
   UNION结构:  DBG_CQI_DBG_DAT_EN_UNION */
#define DBG_CQI_DBG_DAT_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x7318)

/* 寄存器说明：数采ID号基址
   详      述：CQI 数采信息头文件中的ID号基址。
   UNION结构 ：无 */
#define DBG_CQI_DBG_DAT_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x731C)

/* 寄存器说明：模块LOG ID间过滤器
   详      述：模块LOG ID间过滤器
   UNION结构 ：无 */
#define DBG_PB_DBG_LOG_FLT0_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x5508)

/* 寄存器说明：模块LOG ID间过滤器
   详      述：模块LOG ID间过滤器
   UNION结构 ：无 */
#define DBG_PB_DBG_LOG_FLT1_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x550C)

/* 寄存器说明：LOG信息模式寄存器
 bit[31:16]  LOG信息可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
             'b1：只要dbg_rpt_en为1就上报，没有上报个数限制。
 bit[0]      保留
   UNION结构:  DBG_PB_DBG_LOG_MODE_UNION */
#define DBG_PB_DBG_LOG_MODE_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x5510)

/* 寄存器说明：LOG信息使能寄存器
 bit[31:1]   保留
 bit[0]      模块LOG使能                              
             1'b0：可维可测功能不使能                             1'b1：可维可测功能使能
   UNION结构:  DBG_PB_DBG_LOG_EN_UNION */
#define DBG_PB_DBG_LOG_EN_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x5514)

/* 寄存器说明：可维可测LOG 信息头文件中的ID号基址
   详      述：可维可测LOG 信息头文件中的ID号基址
   UNION结构 ：无 */
#define DBG_PB_DBG_LOG_ID_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x5518)

/* 寄存器说明：可维可测上报LOG ID子类过滤器
 bit[31:4]   保留
 bit[3:0]    可维可测上报数据组类有效指示，[n]对应第n组上报数据，[0]对应第0组上报数据：
             'b1：对应可维可测数据组上报输出；
             'b0：对应可维可测数据组不上报输出。
   UNION结构:  DBG_TDL_DBG_LOG_FLT_UNION */
#define DBG_TDL_DBG_LOG_FLT_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1C040D0)

/* 寄存器说明：可维可测上报控制寄存器
 bit[31:16]  
             LOG信息可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
             'b1：只要dbg_log_en为1就上报，没有上报个数限制。
 bit[0]      保留
   UNION结构:  DBG_TDL_DBG_LOG_MODE_UNION */
#define DBG_TDL_DBG_LOG_MODE_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE1C040D4)

/* 寄存器说明：可维可测上报数据包ID号基址
   详      述：可维可测上报数据包ID号基址。主通道使用0x40007000，辅通道使用0x40007010
   UNION结构 ：无 */
#define DBG_TDL_DBG_LOG_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0xE1C040D8)

/* 寄存器说明：可维可测控制使能寄存器
 bit[31:1]   保留
 bit[0]      可维可测LOG使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
             1'b0：可维可测功能不使能                             1'b1：可维可测功能使能
   UNION结构:  DBG_TDL_DBG_LOG_EN_UNION */
#define DBG_TDL_DBG_LOG_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0xE1C040DC)

/* 寄存器说明：可维可测上报LOG ID子类过滤器
 bit[31:4]   保留
 bit[3:0]    可维可测上报数据组类有效指示，[n]对应第n组上报数据，[0]对应第0组上报数据：
             'b1：对应可维可测数据组上报输出；
             'b0：对应可维可测数据组不上报输出。
   UNION结构:  DBG_TDL2_DBG_LOG_FLT_UNION */
#define DBG_TDL2_DBG_LOG_FLT_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE1C240D0)

/* 寄存器说明：可维可测上报控制寄存器
 bit[31:16]  
             LOG信息可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
             'b1：只要dbg_log_en为1就上报，没有上报个数限制。
 bit[0]      保留
   UNION结构:  DBG_TDL2_DBG_LOG_MODE_UNION */
#define DBG_TDL2_DBG_LOG_MODE_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1C240D4)

/* 寄存器说明：可维可测上报数据包ID号基址
   详      述：可维可测上报数据包ID号基址。主通道使用0x40007000，辅通道使用0x40007010
   UNION结构 ：无 */
#define DBG_TDL2_DBG_LOG_ID_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1C240D8)

/* 寄存器说明：可维可测控制使能寄存器
 bit[31:1]   保留
 bit[0]      可维可测LOG使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
             1'b0：可维可测功能不使能                             1'b1：可维可测功能使能
   UNION结构:  DBG_TDL2_DBG_LOG_EN_UNION */
#define DBG_TDL2_DBG_LOG_EN_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1C240DC)

/* 寄存器说明：可维可测BUS通道buffer地址寄存器
 bit[31:3]   BUS buffer基地址。DMA将数据从可维可测模块搬移到以该地址为起始地址的buffer内。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_BUS_ADDR_UNION */
#define DBG_DMA_DBG_BUS_ADDR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4200)

/* 寄存器说明：可维可测BUS通道写指针寄存器
 bit[31:3]   BUS buffer写指针。软件维护。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_BUS_WPTR_UNION */
#define DBG_DMA_DBG_BUS_WPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4204)

/* 寄存器说明：可维可测BUS通道读指针寄存器
 bit[31:3]   BUS buffer读指针。硬件从SOCP模块读取更新，软件只读。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_BUS_RPTR_UNION */
#define DBG_DMA_DBG_BUS_RPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4208)

/* 寄存器说明：可维可测BUS通道配置寄存器
 bit[31:24]  保留。
 bit[23:3]   BUS buffer长度。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_BUS_CFG_UNION */
#define DBG_DMA_DBG_BUS_CFG_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x420C)

/* 寄存器说明：可维可测LOG通道buffer地址寄存器
 bit[31:3]   LOG buffer基地址。DMA将数据从可维可测模块搬移到以该地址为起始地址的buffer内。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_LOG_ADDR_UNION */
#define DBG_DMA_DBG_LOG_ADDR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4210)

/* 寄存器说明：可维可测LOG通道写指针寄存器
 bit[31:3]   LOG buffer写指针。软件维护。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_LOG_WPTR_UNION */
#define DBG_DMA_DBG_LOG_WPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4214)

/* 寄存器说明：可维可测LOG通道读指针寄存器
 bit[31:3]   LOG buffer读指针。硬件从SOCP模块读取更新，软件只读。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_LOG_RPTR_UNION */
#define DBG_DMA_DBG_LOG_RPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4218)

/* 寄存器说明：可维可测LOG通道配置寄存器
 bit[31:24]  保留。
 bit[23:3]   LOG buffer长度。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_LOG_CFG_UNION */
#define DBG_DMA_DBG_LOG_CFG_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x421C)

/* 寄存器说明：可维可测数采通道buffer地址
 bit[31:3]   可维可测数据采集通道buffer起始地址。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_DS_ADDR_UNION */
#define DBG_DMA_DBG_DS_ADDR_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4280)

/* 寄存器说明：可维可测数采通道写指针寄存器
 bit[31:3]   可维可测数据采集通道写指针。软件维护。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_DS_WPTR_UNION */
#define DBG_DMA_DBG_DS_WPTR_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4284)

/* 寄存器说明：可维可测数采通道读指针寄存器
 bit[31:3]   可维可测数据采集通道读指针。指示软件读操作起始地址。软件维护。8字节对齐。
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_DS_RPTR_UNION */
#define DBG_DMA_DBG_DS_RPTR_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4288)

/* 寄存器说明：可维可测数采通道配置寄存器
 bit[31]     可维可测数据采集通道buffer溢出处理控制。
             0：stop，将当前buffer的后续数据丢弃；
             1：buffer覆盖，回到起始地址写入。
 bit[30]     可维可测数据采集通道buffer溢出状态。
             0：未溢出(ds_overflow_ctrl=0)或未循环覆盖(ds_overflow_ctrl=1)
             1：已溢出(ds_overflow_ctrl=0)或已循环覆盖(ds_overflow_ctrl=1)
 bit[29:28]  保留。
 bit[27:3]   可维可测数据采集通道buffer长度。8字节对齐，必须为包长的整数倍
 bit[2:0]    保留。
   UNION结构:  DBG_DMA_DBG_DS_CFG_UNION */
#define DBG_DMA_DBG_DS_CFG_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x428C)

/* 寄存器说明：可维可测buffer读写指针起始地址寄存器
 bit[31:2]   可维可测通道buffer写指针起始地址。存放的是LOG 0通道的写指针，后面依次按照固定格式存放其它LOG通道和数采通道指针。4字节对齐。
 bit[1:0]    保留。
   UNION结构:  DBG_DMA_DBG_PTR_ADDR_UNION */
#define DBG_DMA_DBG_PTR_ADDR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4290)

/* 寄存器说明：可维可测通道数采使能寄存器
 bit[31:1]   保留。
 bit[0]      数采通道使能。
             0：不使能；
             1：使能。
   UNION结构:  DBG_DMA_DBG_DS_CH_EN_UNION */
#define DBG_DMA_DBG_DS_CH_EN_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4294)

/* 寄存器说明：可维可测通道状态寄存器0
 bit[31:30]  保留。
 bit[29]     数采通道长包异常指示。指示实际包长度大于包头长度域指示的包长。写1清除。
             0：无异常；
             1：异常。
 bit[28:23]  保留。
 bit[22]     LOG1通道长包异常指示。指示实际包长度大于包头长度域指示的包长。写1清除。
             0：无异常；
             1：异常。
 bit[21]     LOG0通道长包异常指示。指示实际包长度大于包头长度域指示的包长。写1清除。
             0：无异常；
             1：异常。
 bit[20]     数采通道包头、包尾指示不匹配。每个数据包都是以包头指示sop开始，以包尾指示eop结束。如果连续收到sop或者eop，该状态会触发。
             0：无异常；
             1：异常。
 bit[19:14]  保留。
 bit[13]     LOG1通道包头、包尾指示不匹配。
             0：无异常；
             1：异常。
 bit[12]     LOG0通道包头、包尾指示不匹配。
             0：无异常；
             1：异常。
 bit[11:2]   保留。
 bit[1]      LOG1通道buffer上溢。
             0：无异常；
             1：异常。
 bit[0]      LOG0通道buffer上溢。
             0：无异常；
             1：异常。
   UNION结构:  DBG_DBG_CH_STS0_UNION */
#define DBG_DBG_CH_STS0_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x429C)

/* 寄存器说明：可维可测LOG通道使能寄存器
 bit[31:1]   保留。
 bit[0]      LOG通道使能寄存器。
             0：不使能；
             1：使能。
   UNION结构:  DBG_DMA_DBG_LOG_CH_EN_UNION */
#define DBG_DMA_DBG_LOG_CH_EN_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0x42B8)

/* 寄存器说明：COM时钟使能
 bit[31:7]   保留
 bit[6]      dbg时钟使能信号。只写信号，写1使能
 bit[5:0]    保留
   UNION结构:  DBG_COM_CLK_EN_UNION */
#define DBG_COM_CLK_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0xE1FC40E0)

/* 寄存器说明：COM复位清除
 bit[31:7]   保留
 bit[6]      dbg复位清除信号。只写信号，写1使能清零
 bit[5]      保留
 bit[4]      sdr复位清除信号。只写信号，写1使能清零
 bit[3:0]    保留
   UNION结构:  DBG_COM_SRST_DIS_UNION */
#define DBG_COM_SRST_DIS_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE1FC40F4)

/* 寄存器说明：RX数采数据选择
 bit[31:10]  保留
 bit[9]      辅天线采数使，高电平有效。
 bit[8]      主天线采数使能，高电平有效。
 bit[7:5]    保留
 bit[4:0]    基带数据搬运选择，表示采数位置。
             0，ADC输出信号，W和TDS都用；
             1，spmv输输出信号，W和TDS都用；
             2，dcoc输出信号，仅TDS使用；
             3，dgt1输出信号，仅TDS使用；
             4，fir输出信号，W和TDS都用；
             5，rxiq输出信号，W和TDS都用；
             6，dwf输出信号，W和TDS都用；
             7，codc输出信号，W和TDS都使用；
             8，sc_filter输出信号，W和TDS都使用；
             9，TDS的rrc输出信号，仅TDS使用；
             10，TDS的dgt2输出信号，仅TDS使用；
             11，W的rrc输出信号，主载波和辅载波分时复用；
             12，W的8bitDAGC输出信号，主载波和辅载波分时复用；
             13，W的4bitDAGC输出信号，主载波和辅载波分时复用；
             14，dwf的辅载波输出信号，仅W使用；
             15，sc_filter的辅载波输入信号，仅W使用；
             16，rrc的辅载波输入信号，仅W使用；
             17，幅度为2047的三角波，对应12bits数据；
             18，幅度为127的三角波，对应8bit数据；
             19，频率校正freq_error输出，低12bit为数据；
             20，主载波FIFO输出，低12bit为数据；
             21，辅载波FIFO输出，低12bit为数据；
             default为去谐波的输入信号。
             搬运数据格式：[11:0]为数据；[12]为0表示主载波，为1表示辅载波；[13]为0表示天线1，为1表示天线2。
   UNION结构:  DBG_DBG_AGC_DATA_SEL_UNION */
#define DBG_DBG_AGC_DATA_SEL_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE19952DC)

/* 寄存器说明：TX数采数据选择
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
   UNION结构:  DBG_DBG_DATA_SEL_UNION */
#define DBG_DBG_DATA_SEL_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE19A2814)

/* 寄存器说明：使能寄存器
 bit[31:16]  可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
             'b1：只要dbg_en为1就上报，没有上报个数限制。
 bit[0]      可维可测使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
             1'b0：可维可测功能不使能1'b1：可维可测功能使能
   UNION结构:  DBG_DBG_EN_UNION */
#define DBG_DBG_EN_ADDR                               (SOC_BBP_DBG_BASE_ADDR + 0x4708)

/* 寄存器说明：ID寄存器
   详      述：可维可测上报数据包ID号基址
   UNION结构 ：无 */
#define DBG_DBG_ID_ADDR                               (SOC_BBP_DBG_BASE_ADDR + 0x470C)

/* 寄存器说明：数据选择寄存器
 bit[31:16]  保留
 bit[15:0]   可维可测内部分组指示：
             1：上报mipi数据
             2：上报ssi数据
             3：其它dbg上报数据
             其它：保留
   UNION结构:  DBG_DBG_FLT_UNION */
#define DBG_DBG_FLT_ADDR                              (SOC_BBP_DBG_BASE_ADDR + 0x4710)

/* 寄存器说明：mipi通道选择寄存器
 bit[31:4]   保留
 bit[3:0]    可维可测mipi采集数据通道屏蔽指示：
             dbg_mipi_ch_mask[X],X=0~3,则：
             0：通道X的mipi数据不采集
             1：采集通道X的mipi数据
   UNION结构:  DBG_DBG_MIPI_CH_MASK_UNION */
#define DBG_DBG_MIPI_CH_MASK_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4714)

/* 寄存器说明：ssi通道选择寄存器
 bit[31:4]   保留
 bit[3:0]    可维可测ssi采集数据通道屏蔽指示：
             dbg_ssi_ch_mask[X],X=0~3,则：
             0：通道X的ssi数据不采集
             1：采集通道X的ssi数据
   UNION结构:  DBG_DBG_SSI_CH_MASK_UNION */
#define DBG_DBG_SSI_CH_MASK_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4718)

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
             11：接口环回
             bit[5]Reserved
 bit[2:1]    RX模拟测试模式下通道选择：
             00：输出RXA I模拟调制器数据(默认)
             01：输出RXA Q模拟调制器数据
             10：输出RXB I模拟调制器数据
             11：输出RXB Q模拟调制器数据
 bit[0]      全局软复位信号：
             0：不复位(默认)
             1：复位整个数字电路和模拟电路
   UNION结构:  DBG_ch1_testmode_UNION */
#define DBG_ch1_testmode_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE1FA4104)

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
             11：接口环回
             bit[5] debug_en：
             1：使能，将debug信号通过管脚复用出去；
             0：不使能。
 bit[2:1]    RX模拟测试模式下通道选择：
             00：输出RXA I模拟调制器数据(默认)
             01：输出RXA Q模拟调制器数据
             10：输出RXB I模拟调制器数据
             11：输出RXB Q模拟调制器数据
 bit[0]      全局软复位信号：
             0：不复位(默认)
             1：复位整个数字电路和模拟电路
   UNION结构:  DBG_ch0_testmode_UNION */
#define DBG_ch0_testmode_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE1FA4284)





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
                     (1/1) register_define_BBP_DBG
 ***======================================================================***/
/*****************************************************************************
 结构名    : DBG_DBG_SRST_UNION
 结构说明  : DBG_SRST 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 软复位寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_srst_reg;
    struct
    {
        unsigned int  dbg_srst    : 1;  /* bit[0]   : dbg模块软复位信号。复位DBG的tl_dbg模块
                                                      1：表示复位
                                                      0：表示清复位 */
        unsigned int  sdr_srst    : 1;  /* bit[1]   : sdr模块软复位信号。复位SDR通路逻辑电路，包括dbg_reg；
                                                      1：表示复位
                                                      0：表示清复位 */
        unsigned int  reserved    : 6;  /* bit[2-7] : 保留。 */
        unsigned int  dbg_ver_num : 24; /* bit[8-31]: dbg模块版本号。
                                                      由发布时间表示，bit31~24表示年，bit23~16表示月，bit15~8表示日。如2012年5月20日版本，版本号为：0x120520 */
    } reg;
} DBG_DBG_SRST_UNION;
#define DBG_DBG_SRST_dbg_srst_START     (0)
#define DBG_DBG_SRST_dbg_srst_END       (0)
#define DBG_DBG_SRST_sdr_srst_START     (1)
#define DBG_DBG_SRST_sdr_srst_END       (1)
#define DBG_DBG_SRST_dbg_ver_num_START  (8)
#define DBG_DBG_SRST_dbg_ver_num_END    (31)


/*****************************************************************************
 结构名    : DBG_DBG_GATE_UNION
 结构说明  : DBG_GATE 寄存器结构定义。地址偏移量:0x004，初值:0x00000B0F，宽度:32
 寄存器说明: 时钟门控寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_gate_reg;
    struct
    {
        unsigned int  dbg_high_id       : 4;  /* bit[0-3]  : DBG数据的DMA通道8位ID值的高4位ID指示。
                                                             DBG缺省值=4'hF。
                                                             Bus数据ID=0xF8；
                                                             Dat数据ID=0xF9；
                                                             Log数据ID=0xFA。 */
        unsigned int  dbg_bus_dmach_sel : 1;  /* bit[4]    : Bus数据的DMA通道变更的ID选择。
                                                             0：Bus数据的DMA通道ID保持，ID=F8；(缺省值)　　
                                                             1：Bus数据变更为DMA的Data通道ID选择，ID=0xF9。　　　　　　　　　　　　　　　 */
        unsigned int  reserved_0        : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  gux_lsrv_id       : 4;  /* bit[8-11] : Service ID的GUX SSID信息配置信息。
                                                             配置值为：0xB */
        unsigned int  dbg_gate_sel      : 1;  /* bit[12]   : 模块RAM时钟门控选择信号。
                                                             0：时钟门控有效。门控开启；(缺省值)　　
                                                             1：时钟门控无效。门控关闭。　　　　　　　　　　　　　　　 */
        unsigned int  reserved_1        : 19; /* bit[13-31]: 保留。 */
    } reg;
} DBG_DBG_GATE_UNION;
#define DBG_DBG_GATE_dbg_high_id_START        (0)
#define DBG_DBG_GATE_dbg_high_id_END          (3)
#define DBG_DBG_GATE_dbg_bus_dmach_sel_START  (4)
#define DBG_DBG_GATE_dbg_bus_dmach_sel_END    (4)
#define DBG_DBG_GATE_gux_lsrv_id_START        (8)
#define DBG_DBG_GATE_gux_lsrv_id_END          (11)
#define DBG_DBG_GATE_dbg_gate_sel_START       (12)
#define DBG_DBG_GATE_dbg_gate_sel_END         (12)


/*****************************************************************************
 结构名    : DBG_DBG_SRV_ID_UNION
 结构说明  : DBG_SRV_ID 寄存器结构定义。地址偏移量:0x00C，初值:0x03014802，宽度:32
 寄存器说明: 传输帧头配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_srv_id_reg;
    struct
    {
        unsigned int  hsrv_id     : 8;  /* bit[0-7]  : Service ID的SID信息配置信息。
                                                       配置值为：0x02 */
        unsigned int  tds_lsrv_id : 4;  /* bit[8-11] : Service ID的TDS SSID信息配置信息。
                                                       配置值为：0x8 */
        unsigned int  lte_lsrv_id : 4;  /* bit[12-15]: Service ID的LTE SSID信息配置信息。
                                                       配置值为：0x4 */
        unsigned int  session_id  : 8;  /* bit[16-23]: Session ID配置信息。
                                                       配置值为：0x01　　　　　　　　　　　 */
        unsigned int  msg_type    : 8;  /* bit[24-31]: 消息类型配置信息。
                                                       配置值为：0x03 */
    } reg;
} DBG_DBG_SRV_ID_UNION;
#define DBG_DBG_SRV_ID_hsrv_id_START      (0)
#define DBG_DBG_SRV_ID_hsrv_id_END        (7)
#define DBG_DBG_SRV_ID_tds_lsrv_id_START  (8)
#define DBG_DBG_SRV_ID_tds_lsrv_id_END    (11)
#define DBG_DBG_SRV_ID_lte_lsrv_id_START  (12)
#define DBG_DBG_SRV_ID_lte_lsrv_id_END    (15)
#define DBG_DBG_SRV_ID_session_id_START   (16)
#define DBG_DBG_SRV_ID_session_id_END     (23)
#define DBG_DBG_SRV_ID_msg_type_START     (24)
#define DBG_DBG_SRV_ID_msg_type_END       (31)


/*****************************************************************************
 结构名    : DBG_DBG_FRM_LEN_UNION
 结构说明  : DBG_FRM_LEN 寄存器结构定义。地址偏移量:0x014，初值:0x08000800，宽度:32
 寄存器说明: 传输帧长度寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_frm_len_reg;
    struct
    {
        unsigned int  bus_frm_len  : 16; /* bit[0-15] : BUS读写数据帧长配置信息。
                                                        数据帧长包括诊断包头、Service ID等包头信息。单位为byte。
                                                        可选帧长配置值有：
                                                        0x0800(2048byte)(缺省值)；
                                                        0x0200(512byte)；
                                                        0x0400(1024byte)。　　　　　　　　　　　　 */
        unsigned int  data_frm_len : 16; /* bit[16-31]: 采样数据帧长配置信息。
                                                        数据帧长包括诊断包头、Service ID等包头信息。单位为byte。
                                                        可选帧长配置值有：
                                                        0x0800(2048byte)(缺省值)；
                                                        0x0200(512byte)；(只支持ASIC版本)
                                                        0x0400(1024byte)(只支持ASIC版本) */
    } reg;
} DBG_DBG_FRM_LEN_UNION;
#define DBG_DBG_FRM_LEN_bus_frm_len_START   (0)
#define DBG_DBG_FRM_LEN_bus_frm_len_END     (15)
#define DBG_DBG_FRM_LEN_data_frm_len_START  (16)
#define DBG_DBG_FRM_LEN_data_frm_len_END    (31)


/*****************************************************************************
 结构名    : DBG_LTE_BUS_SEL_UNION
 结构说明  : LTE_BUS_SEL 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: LTE BUS采集数据选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_bus_sel_reg;
    struct
    {
        unsigned int  lte_bus_pb_sel   : 1;  /* bit[0]    : LTE pb模块的BUS数据选择信号。(0x40_0000~0x4f_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  lte_bus_rfin_sel : 1;  /* bit[1]    : LTE rfin模块的BUS数据选择信号。(0x00_0000~0x0f_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  lte_bus_fpu_sel  : 1;  /* bit[2]    : LTE fpu模块的BUS数据选择信号。(0x10_0000~0x1f_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  lte_bus_ul_sel   : 1;  /* bit[3]    : LTE ul模块的BUS数据选择信号。(0x60_0000~0x6f_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  lte_bus_cqi_sel  : 1;  /* bit[4]    : LTE cqi模块的BUS数据选择信号。(0xa0_0000~0xaf_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  lte_bus_vdl_sel  : 1;  /* bit[5]    : LTE vdl模块的BUS数据选择信号。(0x50_0000~0x5f_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  lte_bus_pdu_sel  : 1;  /* bit[6]    : LTE pdu模块的BUS数据采集选择信号。(0xb0_0000~0xbf_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  lte_bus_tdl_sel  : 1;  /* bit[7]    : LTE tdl模块的BUS数据采集选择信号。(0xc0_0000~0xcf_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  reserved         : 2;  /* bit[8-9]  : 保留。 */
        unsigned int  u1_bus_sel       : 1;  /* bit[10]   : U1模块的BUS数据采集使能信号(原UMST模式)。
                                                            0：不选择；1：选择。
                                                            cm_timing、ck_mem、drx_2ms模块(0x90_1000~0x90_1fff)； */
        unsigned int  gsm1_bus_sel     : 1;  /* bit[11]   : GSM1模块的BUS数据采集选择信号(原GSM模式)。
                                                            0：不使能；1：使能。
                                                            gtc_mem、reg_1模块(0x80_0000~0x80_1fff)； */
        unsigned int  bus_dma_sel      : 1;  /* bit[12]   : DMA(sctrl、dbg、dbg_trig、dma)模块的BUS数据采集选择信号。
                                                            0：不选择；1：选择。
                                                            地址：0xfc_0000~0xfc_ffff。 */
        unsigned int  bus_dbg_sel      : 1;  /* bit[13]   : 保留(原dbg模块)。 */
        unsigned int  lte_bus_top_sel  : 1;  /* bit[14]   : LTE top(int、stu、crg)模块的BUS数据采集选择信号。(0x70_0000~0x7f_ffff)
                                                            0：不选择；1：选择。 */
        unsigned int  bus_com_sel      : 1;  /* bit[15]   : COM(ctu、irm/gu_bbp_mst、et、abb)模块的BUS数据采集选择信号。
                                                            0：不选择；1：选择。
                                                            地址：0xf8_0000~0xf8_7fff、0xf8_8000~0xf8_ffff、0xf9_0000~0xf9_7fff、0xfa_0000~0xfa_7fff。 */
        unsigned int  dbg_bus_msk      : 2;  /* bit[16-17]: DBG_BUS读写采数屏蔽信号。
                                                            0：使能BUS操作；
                                                            1：屏蔽BUS操作。
                                                            bit16:读操作屏蔽信号；
                                                            bit17:写操作屏蔽信号。 */
        unsigned int  u1_bus_sel2      : 5;  /* bit[18-22]: U1模块的BUS数据采集使能信号。
                                                            0：不使能；1：使能。
                                                            bit18：mp、mp_rpt_mem、cs、cs_rpt_mem、rf_ctrl模块(0x90_2000~0x90_3fff)；
                                                            bit19：dldem、pc模块(0x90_4000~0x90_4fff、0x90_6000~0x90_6fff)；
                                                            bit20：ul、ulcode_para_mem模块(0x90_c000~0x90_cfff、0x90_e000~0x90_efff)；
                                                            bit21：lmmse、lmmse_mem、dldec_dpa、dldec_para_mem、dldec_dbg_rpt_mem、dldec_dpa_rpt_head模块(0x90_8000~0x90_bfff)；
                                                            bit22：dldec_r99_dc、lmmse_dc、lmmse_mem_dc、dldec_dpa_dc、dldec_dbg_rpt_dc_mem、dldec_dpa_rpt_head_dc、ul_dc模块(0x92_7000~0x92_cfff)； */
        unsigned int  gsm1_bus_sel2    : 4;  /* bit[23-26]: GSM1模块的BUS数据采集选择信号。
                                                            0：不选择；1：选择。
                                                            bit23：dec_rpt_mem、apc_mem、tsc_mem、ulcode_data_mem、reg_2模块(0x80_2000~0x80_3fff)；
                                                            bit24：reg_3、dldem_mem1、dldem_mem2、dldem_mem3模块(0x80_4000~0x80_5fff)；
                                                            bit25：agc_mem1、agc_mem2、gck_mem模块(0x80_6000~0x80_7fff)；
                                                            bit26：fe_ctrl_mem、fe_ctrl、reg_4模块(0x80_8000~0x80_ffff)。 */
        unsigned int  gsm2_bus_sel     : 5;  /* bit[27-31]: GSM2模块的BUS数据采集选择信号。
                                                            0：不选择；1：选择。
                                                            bit27：gtc_mem、reg_1模块(0x88_0000~0x88_1fff)；
                                                            bit28：dec_rpt_mem、apc_mem、tsc_mem、ulcode_data_mem、reg_2模块(0x88_2000~0x88_3fff)；
                                                            bit29：reg_3、dldem_mem1、dldem_mem2、dldem_mem3模块(0x88_4000~0x88_5fff)；
                                                            bit30：agc_mem1、agc_mem2、gck_mem模块(0x880_6000~0x88_7fff)；
                                                            bit31：fe_ctrl_mem、fe_ctrl、reg_4模块(0x88_8000~0x88_ffff)。 */
    } reg;
} DBG_LTE_BUS_SEL_UNION;
#define DBG_LTE_BUS_SEL_lte_bus_pb_sel_START    (0)
#define DBG_LTE_BUS_SEL_lte_bus_pb_sel_END      (0)
#define DBG_LTE_BUS_SEL_lte_bus_rfin_sel_START  (1)
#define DBG_LTE_BUS_SEL_lte_bus_rfin_sel_END    (1)
#define DBG_LTE_BUS_SEL_lte_bus_fpu_sel_START   (2)
#define DBG_LTE_BUS_SEL_lte_bus_fpu_sel_END     (2)
#define DBG_LTE_BUS_SEL_lte_bus_ul_sel_START    (3)
#define DBG_LTE_BUS_SEL_lte_bus_ul_sel_END      (3)
#define DBG_LTE_BUS_SEL_lte_bus_cqi_sel_START   (4)
#define DBG_LTE_BUS_SEL_lte_bus_cqi_sel_END     (4)
#define DBG_LTE_BUS_SEL_lte_bus_vdl_sel_START   (5)
#define DBG_LTE_BUS_SEL_lte_bus_vdl_sel_END     (5)
#define DBG_LTE_BUS_SEL_lte_bus_pdu_sel_START   (6)
#define DBG_LTE_BUS_SEL_lte_bus_pdu_sel_END     (6)
#define DBG_LTE_BUS_SEL_lte_bus_tdl_sel_START   (7)
#define DBG_LTE_BUS_SEL_lte_bus_tdl_sel_END     (7)
#define DBG_LTE_BUS_SEL_u1_bus_sel_START        (10)
#define DBG_LTE_BUS_SEL_u1_bus_sel_END          (10)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel_START      (11)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel_END        (11)
#define DBG_LTE_BUS_SEL_bus_dma_sel_START       (12)
#define DBG_LTE_BUS_SEL_bus_dma_sel_END         (12)
#define DBG_LTE_BUS_SEL_bus_dbg_sel_START       (13)
#define DBG_LTE_BUS_SEL_bus_dbg_sel_END         (13)
#define DBG_LTE_BUS_SEL_lte_bus_top_sel_START   (14)
#define DBG_LTE_BUS_SEL_lte_bus_top_sel_END     (14)
#define DBG_LTE_BUS_SEL_bus_com_sel_START       (15)
#define DBG_LTE_BUS_SEL_bus_com_sel_END         (15)
#define DBG_LTE_BUS_SEL_dbg_bus_msk_START       (16)
#define DBG_LTE_BUS_SEL_dbg_bus_msk_END         (17)
#define DBG_LTE_BUS_SEL_u1_bus_sel2_START       (18)
#define DBG_LTE_BUS_SEL_u1_bus_sel2_END         (22)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel2_START     (23)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel2_END       (26)
#define DBG_LTE_BUS_SEL_gsm2_bus_sel_START      (27)
#define DBG_LTE_BUS_SEL_gsm2_bus_sel_END        (31)


/*****************************************************************************
 结构名    : DBG_TDS_BUS_SEL_UNION
 结构说明  : TDS_BUS_SEL 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: TDS BUS采集数据选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_bus_sel_reg;
    struct
    {
        unsigned int  tds_bus_sel      : 11; /* bit[0-10] : TDS 模块的BUS数据采集选择信号。
                                                            0：不选择；1：选择。
                                                            bit0：stu模块的BUS采集选择信号；(0xd0_0000~0xd0_3fff)
                                                            bit1：保留；
                                                            bit2：rfc模块的BUS采集选择信号；(0xd0_4000~0xd0_5fff)
                                                            bit3：wtc1_com模块的BUS选择信号(原viterbi模块)；
                                                            int、cpc_drx、fe_ctrl_mem、fe_ctrl(0x0x90_0000~0x90_0fff)；
                                                            dldec_r99_para_mem、dldec_r99_reg1、dldec_r99_vtb_head、dldec_r99_vtb_rpt_mem、dldec_r99_turbo_head、dldec_r99_turbo_rpt_mem、dldec_r99_reg2(0x90_7000~0x90_7fff)；
                                                            bit4：hsupa模块的BUS采集选择信号；(0xe1_0000~0xe1_3fff)
                                                            bit5：turbo模块的BUS采集选择信号；(0xe2_0000~0xe2_7fff)
                                                            bit6：top模块的BUS采集选择信号；(0xe2_8000~0xe2_ffff)
                                                            bit7：harq_reg模块的BUS采集选择信号；(0xe3_0000~0xe3_ffff)
                                                            bit8：wtc1_fe模块的BUS选择信号(原tds agcd(own)模块)；
                                                            dl_fe、dl_fe_dc、dl_fe_mctrl、wc_dump、wc_dump_mem、ul_fe_mem、w_pa_pd、w_pa_pd_mem、ul_fe(0x0x99_0000~0x99_ffff)；
                                                            bit9：保留(原tds agcc(ommon)模块)；
                                                            bit10：保留(原tds agcu(p)模块)； */
        unsigned int  reserved_0       : 1;  /* bit[11]   : 保留。 */
        unsigned int  u2_bus_sel       : 4;  /* bit[12-15]: U2模块的BUS数据采集使能信号。
                                                            0：不使能；1：使能。
                                                            bit12：cm_timing、ck_mem、drx_2ms模块(0x20_1000~0x20_1fff)；
                                                            bit13：mp、mp_rpt_mem、cs、cs_rpt_mem、rf_ctrl模块(0x20_2000~0x20_3fff)；
                                                            bit14：dldem、pc模块(0x20_4000~0x20_4fff、0x20_6000~0x20_6fff)；
                                                            bit15：ul、ulcode_para_mem模块(0x20_c000~0x20_cfff、0x20_e000~0x20_efff)； */
        unsigned int  c1_bus_sel       : 6;  /* bit[16-21]: C1模块的BUS数据采集选择信号。
                                                            0：不选择；
                                                            1：选择。
                                                            bit16：glb模块(0x9e_0000~0x9e_0fff)；
                                                            bit17：timing_int模块(0x9e_1000~0x9e_1fff)；
                                                            bit18：mps_cs模块(0x9e_2000~0x9e_2fff)；
                                                            bit19：dldec模块(0x9e_4000~0x9e_4fff)；
                                                            bit20：ulcode模块(0x9e_b000~0x9e_bfff)；
                                                            bit21：fe_ctrl、ssi_mem、mipi_mem、gpio_mem、hkadc_mem模块(0x9e_f000~0x9e_ffff)。 */
        unsigned int  reserved_1       : 2;  /* bit[22-23]: 保留。 */
        unsigned int  wtc2_com_bus_sel : 1;  /* bit[24]   : WTC2 COM模块的BUS数据采集选择信号。
                                                            0：不选择；
                                                            1：选择。
                                                            包括模块：
                                                            int、fe_ctrl_mem、fe_ctrl(0x0x20_0000~0x20_0fff)；
                                                            dldec_r99_para_mem、dldec_r99_reg1、dldec_r99_vtb_head、dldec_r99_vtb_rpt_mem、dldec_r99_turbo_head、dldec_r99_turbo_rpt_mem、dldec_r99_reg2(0x20_7000~0x20_7fff)； */
        unsigned int  wtc2_fe_bus_sel  : 1;  /* bit[25]   : WTC2 FE模块的BUS数据采集选择信号。
                                                            0：不选择；
                                                            1：选择。
                                                            包括模块：
                                                            dl_fe、dl_fe_dc、dl_fe_mctrl、wc_dump、wc_dump_mem、ul_fe_mem、w_pa_pd、w_pa_pd_mem、ul_fe(0x0x29_0000~0x29_ffff)； */
        unsigned int  c2_bus_sel       : 6;  /* bit[26-31]: C2模块的BUS数据采集选择信号。
                                                            0：不选择；
                                                            1：选择。
                                                            bit26：glb模块(0x2e_0000~0x2e_0fff)；
                                                            bit27：timing_int模块(0x2e_1000~0x2e_1fff)；
                                                            bit28：mps_cs模块(0x2e_2000~0x2e_2fff)；
                                                            bit29：dldec模块(0x2e_4000~0x2e_4fff)；
                                                            bit30：ulcode模块(0x2e_b000~0x2e_bfff)；
                                                            bit31：fe_ctrl、ssi_mem、mipi_mem、gpio_mem、hkadc_mem模块(0x2e_f000~0x2e_ffff)。 */
    } reg;
} DBG_TDS_BUS_SEL_UNION;
#define DBG_TDS_BUS_SEL_tds_bus_sel_START       (0)
#define DBG_TDS_BUS_SEL_tds_bus_sel_END         (10)
#define DBG_TDS_BUS_SEL_u2_bus_sel_START        (12)
#define DBG_TDS_BUS_SEL_u2_bus_sel_END          (15)
#define DBG_TDS_BUS_SEL_c1_bus_sel_START        (16)
#define DBG_TDS_BUS_SEL_c1_bus_sel_END          (21)
#define DBG_TDS_BUS_SEL_wtc2_com_bus_sel_START  (24)
#define DBG_TDS_BUS_SEL_wtc2_com_bus_sel_END    (24)
#define DBG_TDS_BUS_SEL_wtc2_fe_bus_sel_START   (25)
#define DBG_TDS_BUS_SEL_wtc2_fe_bus_sel_END     (25)
#define DBG_TDS_BUS_SEL_c2_bus_sel_START        (26)
#define DBG_TDS_BUS_SEL_c2_bus_sel_END          (31)


/*****************************************************************************
 结构名    : DBG_DBG_BUS_EN_UNION
 结构说明  : DBG_BUS_EN 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: BUS采数使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_bus_en_reg;
    struct
    {
        unsigned int  dbg_bus_en : 1;  /* bit[0]   : BUS数据采数使能信号。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留。 */
    } reg;
} DBG_DBG_BUS_EN_UNION;
#define DBG_DBG_BUS_EN_dbg_bus_en_START  (0)
#define DBG_DBG_BUS_EN_dbg_bus_en_END    (0)


/*****************************************************************************
 结构名    : DBG_DBG_DAT_SEL_UNION
 结构说明  : DBG_DAT_SEL 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: DAT通道选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat_sel_reg;
    struct
    {
        unsigned int  dbg_dat_sel  : 4;  /* bit[0-3]  : DBG模块上报dat数据类型选择。
                                                        0：RFIN上报的dat数据(缺省值)
                                                        1：FPU上报的dat数据
                                                        2：CQI上报的dat数据
                                                        3：PDU上报的dat数据
                                                        4：TDS上报的dat数据
                                                        5：ABB上报下行通道dat数据(不支持FPGA版本)
                                                        6：ABB上报上行通道dat数据(不支持FPGA版本)
                                                        7：ABB上报模拟通道dat数据(不支持FPGA版本)
                                                        8：BBP COMMON上报的dat数据
                                                        15~9：保留 */
        unsigned int  tds_type_sel : 3;  /* bit[4-6]  : TDS数采类型选择寄存器。
                                                        与DAT ID基址配合使用。
                                                        1：下行天线0数据采集，      ID=0x41000801；
                                                        2：下行天线1数据采集，      ID=0x41000802；
                                                        3：下行双天线数据采集，     ID=0x41000803；
                                                        4：上行数据采集，材         ID=0x41000804；
                                                        5：上行+下行天线0数据采集， ID=0x41000805；
                                                        6：上行+下行天线1数据采集， ID=0x41000806；
                                                        7：上行+下行双天线数据采集，ID=0x41000807；
                                                        其它：保留。 */
        unsigned int  reserved_0   : 1;  /* bit[7]    : 保留。 */
        unsigned int  dbg_abb_sel  : 2;  /* bit[8-9]  : ABB ch0/1通道选择信号，与ABB数采使能配合使用。
                                                        0：选择ch1通道；
                                                        1：选择ch0通道；
                                                        2：选择ch0/1通道的并发CA，ABB数采选择下行数据 */
        unsigned int  reserved_1   : 22; /* bit[10-31]: 保留。 */
    } reg;
} DBG_DBG_DAT_SEL_UNION;
#define DBG_DBG_DAT_SEL_dbg_dat_sel_START   (0)
#define DBG_DBG_DAT_SEL_dbg_dat_sel_END     (3)
#define DBG_DBG_DAT_SEL_tds_type_sel_START  (4)
#define DBG_DBG_DAT_SEL_tds_type_sel_END    (6)
#define DBG_DBG_DAT_SEL_dbg_abb_sel_START   (8)
#define DBG_DBG_DAT_SEL_dbg_abb_sel_END     (9)


/*****************************************************************************
 结构名    : DBG_DBG_DAT_EN_UNION
 结构说明  : DBG_DAT_EN 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: DAT采数使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat_en_reg;
    struct
    {
        unsigned int  dbg_dat_en : 1;  /* bit[0]   : DAT数据采数使能信号。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留。 */
    } reg;
} DBG_DBG_DAT_EN_UNION;
#define DBG_DBG_DAT_EN_dbg_dat_en_START  (0)
#define DBG_DBG_DAT_EN_dbg_dat_en_END    (0)


/*****************************************************************************
 结构名    : DBG_DBG_LOG_SEL_UNION
 结构说明  : DBG_LOG_SEL 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: LOG通道选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_log_sel_reg;
    struct
    {
        unsigned int  dbg_log_sel : 3;  /* bit[0-2] : DBG模块上报LOG数据类型选择。
                                                      0：保留(缺省值)
                                                      1：FPU上报的log数据
                                                      2：PB上报的log数据
                                                      3：PDU上报的log数据
                                                      4：TDL上报的log数据
                                                      5：TDL2上报的log数据
                                                      7~6：保留　　　　　　　 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留。 */
    } reg;
} DBG_DBG_LOG_SEL_UNION;
#define DBG_DBG_LOG_SEL_dbg_log_sel_START  (0)
#define DBG_DBG_LOG_SEL_dbg_log_sel_END    (2)


/*****************************************************************************
 结构名    : DBG_DBG_LOG_EN_UNION
 结构说明  : DBG_LOG_EN 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: LOG通道使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : L模LOG数据传输使能信号。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留。 */
    } reg;
} DBG_DBG_LOG_EN_UNION;
#define DBG_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 结构名    : DBG_DBG_TL_SEL_UNION
 结构说明  : DBG_TL_SEL 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: DBG采数通信模式选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_tl_sel_reg;
    struct
    {
        unsigned int  reserved_0     : 4;  /* bit[0-3]  : 保留。 */
        unsigned int  dbg_ptimer_sel : 4;  /* bit[4-7]  : DBG采数主模时标选择信号。
                                                          0：保留(缺省值)
                                                          1：LTE；
                                                          2：TDS；
                                                          3：UMTS(U1)；
                                                          4：EVDO&1X(X1)；
                                                          5：1X(X2)；
                                                          6：R99(U2)；
                                                          7：GSM1；
                                                          8：GSM2；
                                                          9~15：保留 */
        unsigned int  dbg_stimer_sel : 4;  /* bit[8-11] : DBG采数从模时标选择信号。
                                                          0：保留(缺省值)
                                                          1：LTE；
                                                          2：TDS；
                                                          3：UMTS(U1)；
                                                          4：EVDO&1X(X1)；
                                                          5：1X(X2)；
                                                          6：R99(U2)；
                                                          7：GSM1；
                                                          8：GSM2；
                                                          9~15：保留 */
        unsigned int  reserved_1     : 20; /* bit[12-31]: 保留。 */
    } reg;
} DBG_DBG_TL_SEL_UNION;
#define DBG_DBG_TL_SEL_dbg_ptimer_sel_START  (4)
#define DBG_DBG_TL_SEL_dbg_ptimer_sel_END    (7)
#define DBG_DBG_TL_SEL_dbg_stimer_sel_START  (8)
#define DBG_DBG_TL_SEL_dbg_stimer_sel_END    (11)


/*****************************************************************************
 结构名    : DBG_DBG_DIAG_ALARM_UNION
 结构说明  : DBG_DIAG_ALARM 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: DAT/BUS/LOG通道告警寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_diag_alarm_reg;
    struct
    {
        unsigned int  col_data_alarm : 1;  /* bit[0]    : DATA数据帧传输告警信息。只读，对应位写1清0。
                                                          bit0：通道fifo溢出告警信号。 */
        unsigned int  col_dat_sts    : 4;  /* bit[1-4]  : DATA数据接口指示信息。只读，对应位写1清0
                                                          bit4：dat数据结束指示；
                                                          bit3：vld有效指示；
                                                          bit2：eop有效指示；
                                                          bit1：sop有效指示； */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  lte_log_alarm  : 4;  /* bit[8-11] : lte的log包传输告警信息。只读，对应位写1清0。
                                                          bit11：传输帧数据小于设置值且无结束标识的告警；
                                                          bit10：传输帧数据大于设置值的告警；
                                                          bit9：传输帧数据小于设置值的告警；
                                                          bit8：通道fifo溢出告警信号。 */
        unsigned int  bus_alarm      : 2;  /* bit[12-13]: BUS通道告警信息。只读，对应位写1清0。
                                                          bit13：burst读数据出错告警信号；
                                                          bit12：通道fifo溢出告警信号。 */
        unsigned int  reserved_1     : 18; /* bit[14-31]: 保留。 */
    } reg;
} DBG_DBG_DIAG_ALARM_UNION;
#define DBG_DBG_DIAG_ALARM_col_data_alarm_START  (0)
#define DBG_DBG_DIAG_ALARM_col_data_alarm_END    (0)
#define DBG_DBG_DIAG_ALARM_col_dat_sts_START     (1)
#define DBG_DBG_DIAG_ALARM_col_dat_sts_END       (4)
#define DBG_DBG_DIAG_ALARM_lte_log_alarm_START   (8)
#define DBG_DBG_DIAG_ALARM_lte_log_alarm_END     (11)
#define DBG_DBG_DIAG_ALARM_bus_alarm_START       (12)
#define DBG_DBG_DIAG_ALARM_bus_alarm_END         (13)


/*****************************************************************************
 结构名    : DBG_DBG_DMA_CNT_UNION
 结构说明  : DBG_DMA_CNT 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: DBG的DMA请求/响应次数计数器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dma_cnt_reg;
    struct
    {
        unsigned int  dma_req_cnt : 16; /* bit[0-15] : DBG的DMA接口的req请求次数计数器。
                                                       只读，16位计数器。Test_switch开启有效，关闭清0； */
        unsigned int  dma_gnt_cnt : 16; /* bit[16-31]: DBG的DMA接口的gnt响应次数计数器。
                                                       只读，16位计数器。Test_switch开启有效，关闭清0； */
    } reg;
} DBG_DBG_DMA_CNT_UNION;
#define DBG_DBG_DMA_CNT_dma_req_cnt_START  (0)
#define DBG_DBG_DMA_CNT_dma_req_cnt_END    (15)
#define DBG_DBG_DMA_CNT_dma_gnt_cnt_START  (16)
#define DBG_DBG_DMA_CNT_dma_gnt_cnt_END    (31)


/*****************************************************************************
 结构名    : DBG_DBG_SOP_CNT_UNION
 结构说明  : DBG_SOP_CNT 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: dbg帧的sop计数器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_sop_cnt_reg;
    struct
    {
        unsigned int  dat_fifo_max     : 10; /* bit[0-9]  : dat_bst模块fifo最大存储数据个数。
                                                            只读，10位计数器，数据范围：0~512。
                                                            对0x003C的bit3写1清0。 */
        unsigned int  reserved         : 14; /* bit[10-23]: 保留。 */
        unsigned int  col_subframe_cnt : 8;  /* bit[24-31]: dat数据的sop个数计数器。
                                                            只读，8位计数器。对0x003C的bit1写1清0。 */
    } reg;
} DBG_DBG_SOP_CNT_UNION;
#define DBG_DBG_SOP_CNT_dat_fifo_max_START      (0)
#define DBG_DBG_SOP_CNT_dat_fifo_max_END        (9)
#define DBG_DBG_SOP_CNT_col_subframe_cnt_START  (24)
#define DBG_DBG_SOP_CNT_col_subframe_cnt_END    (31)


/*****************************************************************************
 结构名    : DBG_DBG_RAM_CNT_UNION
 结构说明  : DBG_RAM_CNT 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: dbg的ram状态计数器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ram_cnt_reg;
    struct
    {
        unsigned int  dbg_ram_peak_cnt : 13; /* bit[0-12] : 指示DBG通道RAM达到最大存储数据(64bit)个数。
                                                            Test_switch开启有效，关闭清0；
                                                            13位计数器，数据范围：0~4096。 */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: 保留。 */
        unsigned int  dbg_bst_peak_cnt : 9;  /* bit[16-24]: 指示DBG通道RAM达到最大burst存储个数。
                                                            Test_switch开启有效，关闭清0；
                                                            9位计数器，数据范围：0~256。 */
        unsigned int  reserved_1       : 3;  /* bit[25-27]: 保留。 */
        unsigned int  dbg_ram_empty    : 1;  /* bit[28]   : 指示DBG通道RAM实时非空状态。
                                                            0：ram为空。1：ram非空； */
        unsigned int  reserved_2       : 3;  /* bit[29-31]: 保留。 */
    } reg;
} DBG_DBG_RAM_CNT_UNION;
#define DBG_DBG_RAM_CNT_dbg_ram_peak_cnt_START  (0)
#define DBG_DBG_RAM_CNT_dbg_ram_peak_cnt_END    (12)
#define DBG_DBG_RAM_CNT_dbg_bst_peak_cnt_START  (16)
#define DBG_DBG_RAM_CNT_dbg_bst_peak_cnt_END    (24)
#define DBG_DBG_RAM_CNT_dbg_ram_empty_START     (28)
#define DBG_DBG_RAM_CNT_dbg_ram_empty_END       (28)


/*****************************************************************************
 结构名    : DBG_DBG_TIME_CNT_UNION
 结构说明  : DBG_TIME_CNT 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: dbg通道req的响应时间计数器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_time_cnt_reg;
    struct
    {
        unsigned int  dbg_gnt_time_cnt : 24; /* bit[0-23] : 指示DBG通道RAM的req/gnt间最大时间计数。
                                                            Test_switch开启有效，关闭清0；
                                                            24位计数器，时间计算与时钟相关。 */
        unsigned int  reserved         : 8;  /* bit[24-31]: 保留。 */
    } reg;
} DBG_DBG_TIME_CNT_UNION;
#define DBG_DBG_TIME_CNT_dbg_gnt_time_cnt_START  (0)
#define DBG_DBG_TIME_CNT_dbg_gnt_time_cnt_END    (23)


/*****************************************************************************
 结构名    : DBG_DBG_GLB_SEL_UNION
 结构说明  : DBG_GLB_SEL 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: dbg的通用选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_glb_sel_reg;
    struct
    {
        unsigned int  bus_faddr_en       : 1;  /* bit[0]   : BUS采数地址段模式的使能信号。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留。 */
        unsigned int  dbg_tc_msk         : 1;  /* bit[4]   : 定时屏蔽信号。(验证需求功能)
                                                             0：定时信息正常采集与传输；
                                                             1：定时信息被屏蔽，值都为0。 */
        unsigned int  reserved_1         : 3;  /* bit[5-7] : 保留。 */
        unsigned int  dbg_bus_data_exchg : 1;  /* bit[8]   : DBG的BUS与DATA通道交叉传输使能信号。
                                                             0：正常传输(缺省模式)；
                                                             1：交叉使能。 */
        unsigned int  reserved_2         : 23; /* bit[9-31]: 保留。 */
    } reg;
} DBG_DBG_GLB_SEL_UNION;
#define DBG_DBG_GLB_SEL_bus_faddr_en_START        (0)
#define DBG_DBG_GLB_SEL_bus_faddr_en_END          (0)
#define DBG_DBG_GLB_SEL_dbg_tc_msk_START          (4)
#define DBG_DBG_GLB_SEL_dbg_tc_msk_END            (4)
#define DBG_DBG_GLB_SEL_dbg_bus_data_exchg_START  (8)
#define DBG_DBG_GLB_SEL_dbg_bus_data_exchg_END    (8)


/*****************************************************************************
 结构名    : DBG_BUS_ADDR_VALUE_UNION
 结构说明  : BUS_ADDR_VALUE 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: bus采数起始地址寄存器
*****************************************************************************/
typedef union
{
    unsigned int      bus_addr_value_reg;
    struct
    {
        unsigned int  bus_faddr_value : 24; /* bit[0-23] : BUS采数地址段模式的起始地址。选择范围：0~0xffffff */
        unsigned int  reserved        : 8;  /* bit[24-31]: 保留。 */
    } reg;
} DBG_BUS_ADDR_VALUE_UNION;
#define DBG_BUS_ADDR_VALUE_bus_faddr_value_START  (0)
#define DBG_BUS_ADDR_VALUE_bus_faddr_value_END    (23)


/*****************************************************************************
 结构名    : DBG_BUS_ADDR_SIZE_UNION
 结构说明  : BUS_ADDR_SIZE 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: bus采数地址范围寄存器
*****************************************************************************/
typedef union
{
    unsigned int      bus_addr_size_reg;
    struct
    {
        unsigned int  bus_faddr_size : 24; /* bit[0-23] : BUS采数地址段模式地址范围(大小)。选择范围：0~0xffffff */
        unsigned int  reserved       : 8;  /* bit[24-31]: 保留。 */
    } reg;
} DBG_BUS_ADDR_SIZE_UNION;
#define DBG_BUS_ADDR_SIZE_bus_faddr_size_START  (0)
#define DBG_BUS_ADDR_SIZE_bus_faddr_size_END    (23)


/*****************************************************************************
 结构名    : DBG_TDS_DAT_MODE_UNION
 结构说明  : TDS_DAT_MODE 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000002，宽度:32
 寄存器说明: TDS DAT采集模式选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_dat_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : 保留。 */
        unsigned int  tds_dat_mode : 1;  /* bit[1]    : TDS/ABB DAT采集模式选择信号。
                                                        0：计数模式，与计数值组合使用；
                                                        1：开关模式。 */
        unsigned int  reserved_1   : 14; /* bit[2-15] : 保留。 */
        unsigned int  tds_dat_frm  : 16; /* bit[16-31]: 计数模式的DAT采集帧个数。(支持TDS/ABB) */
    } reg;
} DBG_TDS_DAT_MODE_UNION;
#define DBG_TDS_DAT_MODE_tds_dat_mode_START  (1)
#define DBG_TDS_DAT_MODE_tds_dat_mode_END    (1)
#define DBG_TDS_DAT_MODE_tds_dat_frm_START   (16)
#define DBG_TDS_DAT_MODE_tds_dat_frm_END     (31)


/*****************************************************************************
 结构名    : DBG_DAT_TEST_UNION
 结构说明  : DAT_TEST 寄存器结构定义。地址偏移量:0x0AC，初值:0x0000000F，宽度:32
 寄存器说明: DAT测试配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dat_test_reg;
    struct
    {
        unsigned int  dat_test_bandw : 8;  /* bit[0-7]  : DAT测试数据带宽配置信号。
                                                          其值为时钟计数，如初值=F，则每隔16cycle，采集传输1个64bit数据，如时钟频率=150MHz，则测试数据带宽=600Mbps。 */
        unsigned int  dat_test_md    : 2;  /* bit[8-9]  : DAT测试类型配置信号。
                                                          Bit8：数据替换模式。在实际TDS采数模式下，用确定的测试数据替换DAT接口数据，检验通道传输正确性；
                                                          Bit9：数据测试模式。需要配置为TDS采数模式，内部产生数据进行数采通道与带宽测试；
                                                          配置信息置1有效。 */
        unsigned int  reserved       : 22; /* bit[10-31]: 保留。 */
    } reg;
} DBG_DAT_TEST_UNION;
#define DBG_DAT_TEST_dat_test_bandw_START  (0)
#define DBG_DAT_TEST_dat_test_bandw_END    (7)
#define DBG_DAT_TEST_dat_test_md_START     (8)
#define DBG_DAT_TEST_dat_test_md_END       (9)


/*****************************************************************************
 结构名    : DBG_TDS_DAT_STS_UNION
 结构说明  : TDS_DAT_STS 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: TDS DAT接口状态寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_dat_sts_reg;
    struct
    {
        unsigned int  tds_dat_cfg_err : 1;  /* bit[0]   : TDS DAT类型配置错误指示信号。
                                                          只读，对应位写1清0。 */
        unsigned int  reserved_0      : 3;  /* bit[1-3] : 保留。 */
        unsigned int  tds_dat_sts     : 3;  /* bit[4-6] : TDS DAT接口类型状态指示信号。
                                                          只读，对应位写1清0。
                                                          Bit4：下行单天线数据类型状态指示；
                                                          Bit5：下行双天线数据类型状态指示；
                                                          Bit6：上行数据类型状态指示； */
        unsigned int  reserved_1      : 25; /* bit[7-31]: 保留。 */
    } reg;
} DBG_TDS_DAT_STS_UNION;
#define DBG_TDS_DAT_STS_tds_dat_cfg_err_START  (0)
#define DBG_TDS_DAT_STS_tds_dat_cfg_err_END    (0)
#define DBG_TDS_DAT_STS_tds_dat_sts_START      (4)
#define DBG_TDS_DAT_STS_tds_dat_sts_END        (6)


/*****************************************************************************
 结构名    : DBG_DBG_BUS_MODE_UNION
 结构说明  : DBG_BUS_MODE 寄存器结构定义。地址偏移量:0x0C8，初值:0x00000002，宽度:32
 寄存器说明: DBG BUS采集模式选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_bus_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : 保留。 */
        unsigned int  dbg_bus_mode : 1;  /* bit[1]    : DBG BUS采集模式选择信号。
                                                        0：计数模式，与计数值组合使用；
                                                        1：开关模式。 */
        unsigned int  reserved_1   : 14; /* bit[2-15] : 保留。 */
        unsigned int  dbg_bus_frm  : 16; /* bit[16-31]: 计数模式的BUS采集帧个数。 */
    } reg;
} DBG_DBG_BUS_MODE_UNION;
#define DBG_DBG_BUS_MODE_dbg_bus_mode_START  (1)
#define DBG_DBG_BUS_MODE_dbg_bus_mode_END    (1)
#define DBG_DBG_BUS_MODE_dbg_bus_frm_START   (16)
#define DBG_DBG_BUS_MODE_dbg_bus_frm_END     (31)


/*****************************************************************************
 结构名    : DBG_DBG_BUS_TEST_UNION
 结构说明  : DBG_BUS_TEST 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000007，宽度:32
 寄存器说明: DBG BUS测试配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_bus_test_reg;
    struct
    {
        unsigned int  dbg_bus_test_bandw : 8;  /* bit[0-7] : DBG BUS测试数据带宽配置信号。
                                                             其值为时钟计数，如初值=0x07，则每隔128cycle(0x7F)，采集传输1个64bit数据，如时钟频率=150MHz，则测试数据带宽=75Mbps。 */
        unsigned int  dbg_bus_test_md    : 1;  /* bit[8]   : DBG BUS测试模式。BUS通道与带宽测试
                                                             配置信息置1有效。 */
        unsigned int  reserved           : 23; /* bit[9-31]: 保留。 */
    } reg;
} DBG_DBG_BUS_TEST_UNION;
#define DBG_DBG_BUS_TEST_dbg_bus_test_bandw_START  (0)
#define DBG_DBG_BUS_TEST_dbg_bus_test_bandw_END    (7)
#define DBG_DBG_BUS_TEST_dbg_bus_test_md_START     (8)
#define DBG_DBG_BUS_TEST_dbg_bus_test_md_END       (8)


/*****************************************************************************
 结构名    : DBG_SP_MEM_CTRL_UNION
 结构说明  : SP_MEM_CTRL 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: SP MEM CTRL配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      sp_mem_ctrl_reg;
    struct
    {
        unsigned int  sp_mem_ctrl : 16; /* bit[0-15] : SPRAM的MEM_CTRL配置。
                                                       缺省值由统一参数提供。 */
        unsigned int  reserved    : 16; /* bit[16-31]: 保留。 */
    } reg;
} DBG_SP_MEM_CTRL_UNION;
#define DBG_SP_MEM_CTRL_sp_mem_ctrl_START  (0)
#define DBG_SP_MEM_CTRL_sp_mem_ctrl_END    (15)


/*****************************************************************************
 结构名    : DBG_TP_MEM_CTRL_UNION
 结构说明  : TP_MEM_CTRL 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: TP MEM CTRL配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tp_mem_ctrl_reg;
    struct
    {
        unsigned int  tp_mem_ctrl : 16; /* bit[0-15] : TPRAM的MEM_CTRL配置。
                                                       缺省值由统一参数提供。 */
        unsigned int  reserved    : 16; /* bit[16-31]: 保留。 */
    } reg;
} DBG_TP_MEM_CTRL_UNION;
#define DBG_TP_MEM_CTRL_tp_mem_ctrl_START  (0)
#define DBG_TP_MEM_CTRL_tp_mem_ctrl_END    (15)


/*****************************************************************************
 结构名    : DBG_ARB_PRIOR_SEL_UNION
 结构说明  : ARB_PRIOR_SEL 寄存器结构定义。地址偏移量:0x100，初值:0x0000000B，宽度:32
 寄存器说明: ARBITER优先级选择配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      arb_prior_sel_reg;
    struct
    {
        unsigned int  ddr_prior_level : 8;  /* bit[0-7] : DDR通路的arbiter优先级选择配置。
                                                          0：低优先级；1：高优先级。
                                                          bit0：sdr通道；
                                                          bit1：dbg_bus通道；
                                                          bit2：dbg_data通道；
                                                          bit3：dbg_log通道。
                                                          其余保留。 */
        unsigned int  reserved        : 24; /* bit[8-31]: 保留。 */
    } reg;
} DBG_ARB_PRIOR_SEL_UNION;
#define DBG_ARB_PRIOR_SEL_ddr_prior_level_START  (0)
#define DBG_ARB_PRIOR_SEL_ddr_prior_level_END    (7)


/*****************************************************************************
 结构名    : DBG_TEST_SWITCH_UNION
 结构说明  : TEST_SWITCH 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: TEST SWITCH配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      test_switch_reg;
    struct
    {
        unsigned int  test_switch : 1;  /* bit[0]   : 模块测试功能项选择开关。
                                                      0：测试功能关闭；(缺省配置)
                                                      1：测试功能开启。 */
        unsigned int  reserved_0  : 3;  /* bit[1-3] : 保留。 */
        unsigned int  rd_dly_sel  : 1;  /* bit[4]   : Burst接口gnt与rd信号对齐选择。
                                                      0：gnt与rd必须对齐；(缺省配置)
                                                      1：gnt与rd可以不对齐。 */
        unsigned int  reserved_1  : 27; /* bit[5-31]: 保留。 */
    } reg;
} DBG_TEST_SWITCH_UNION;
#define DBG_TEST_SWITCH_test_switch_START  (0)
#define DBG_TEST_SWITCH_test_switch_END    (0)
#define DBG_TEST_SWITCH_rd_dly_sel_START   (4)
#define DBG_TEST_SWITCH_rd_dly_sel_END     (4)


/*****************************************************************************
 结构名    : DBG_GNT_RD_STS_UNION
 结构说明  : GNT_RD_STS 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: GNT与RD对齐状态寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gnt_rd_sts_reg;
    struct
    {
        unsigned int  tcm_gnt_nord : 1;  /* bit[0]   : 指示DMA的TCM接口gnt信号有效同时无rd信号状态。此位写1清0状态 */
        unsigned int  reserved_0   : 3;  /* bit[1-3] : 保留。 */
        unsigned int  ddr_gnt_nord : 1;  /* bit[4]   : 指示DMA的DDR接口gnt信号有效同时无rd信号状态。此位写1清0状态 */
        unsigned int  reserved_1   : 27; /* bit[5-31]: 保留。 */
    } reg;
} DBG_GNT_RD_STS_UNION;
#define DBG_GNT_RD_STS_tcm_gnt_nord_START  (0)
#define DBG_GNT_RD_STS_tcm_gnt_nord_END    (0)
#define DBG_GNT_RD_STS_ddr_gnt_nord_START  (4)
#define DBG_GNT_RD_STS_ddr_gnt_nord_END    (4)


/*****************************************************************************
 结构名    : DBG_TCM_DMA_CNT_UNION
 结构说明  : TCM_DMA_CNT 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: TCM通道的DMA请求/响应次数计数器
*****************************************************************************/
typedef union
{
    unsigned int      tcm_dma_cnt_reg;
    struct
    {
        unsigned int  tcm_req_cnt : 16; /* bit[0-15] : TCM的DMA接口的req请求次数计数器。
                                                       Test_switch开启有效，关闭清0；
                                                       只读，16位计数器。 */
        unsigned int  tcm_gnt_cnt : 16; /* bit[16-31]: TCM的DMA接口的gnt响应次数计数器。
                                                       Test_switch开启有效，关闭清0；
                                                       只读，16位计数器。 */
    } reg;
} DBG_TCM_DMA_CNT_UNION;
#define DBG_TCM_DMA_CNT_tcm_req_cnt_START  (0)
#define DBG_TCM_DMA_CNT_tcm_req_cnt_END    (15)
#define DBG_TCM_DMA_CNT_tcm_gnt_cnt_START  (16)
#define DBG_TCM_DMA_CNT_tcm_gnt_cnt_END    (31)


/*****************************************************************************
 结构名    : DBG_TCM_RAM_CNT_UNION
 结构说明  : TCM_RAM_CNT 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: tcm的ram状态计数器
*****************************************************************************/
typedef union
{
    unsigned int      tcm_ram_cnt_reg;
    struct
    {
        unsigned int  tcm_ram_peak_cnt : 10; /* bit[0-9]  : 指示TCM通道RAM达到最大存储数据个数。
                                                            Test_switch开启有效，关闭清0；
                                                            10位计数器，数据范围：0~512。 */
        unsigned int  reserved_0       : 6;  /* bit[10-15]: 保留。 */
        unsigned int  tcm_bst_peak_cnt : 6;  /* bit[16-21]: 指示TCM通道RAM达到最大burst存储个数。
                                                            Test_switch开启有效，关闭清0；
                                                            6位计数器，数据范围：0~32。 */
        unsigned int  reserved_1       : 6;  /* bit[22-27]: 保留。 */
        unsigned int  tcm_ram_empty    : 1;  /* bit[28]   : 指示TCM通道RAM实时非空状态。
                                                            0：ram为空。1：ram非空； */
        unsigned int  reserved_2       : 3;  /* bit[29-31]: 保留。 */
    } reg;
} DBG_TCM_RAM_CNT_UNION;
#define DBG_TCM_RAM_CNT_tcm_ram_peak_cnt_START  (0)
#define DBG_TCM_RAM_CNT_tcm_ram_peak_cnt_END    (9)
#define DBG_TCM_RAM_CNT_tcm_bst_peak_cnt_START  (16)
#define DBG_TCM_RAM_CNT_tcm_bst_peak_cnt_END    (21)
#define DBG_TCM_RAM_CNT_tcm_ram_empty_START     (28)
#define DBG_TCM_RAM_CNT_tcm_ram_empty_END       (28)


/*****************************************************************************
 结构名    : DBG_TCM_TIME_CNT_UNION
 结构说明  : TCM_TIME_CNT 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: tcm通道req的响应时间计数器
*****************************************************************************/
typedef union
{
    unsigned int      tcm_time_cnt_reg;
    struct
    {
        unsigned int  tcm_gnt_time_cnt : 24; /* bit[0-23] : 指示TCM通道RAM的req/gnt间最大时间计数。
                                                            Test_switch开启有效，关闭清0；
                                                            24位计数器，时间计算与时钟相关。 */
        unsigned int  reserved         : 8;  /* bit[24-31]: 保留。 */
    } reg;
} DBG_TCM_TIME_CNT_UNION;
#define DBG_TCM_TIME_CNT_tcm_gnt_time_cnt_START  (0)
#define DBG_TCM_TIME_CNT_tcm_gnt_time_cnt_END    (23)


/*****************************************************************************
 结构名    : DBG_DBG_INT_STS_UNION
 结构说明  : DBG_INT_STS 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: DBG中断状态寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_int_sts_reg;
    struct
    {
        unsigned int  dbg_int_sts : 7;  /* bit[0-6] : DBG中断状态指示。
                                                      0：无中断；
                                                      1：有中断；
                                                      bit0：dat数据溢出错误中断；
                                                      bit1：bus数据溢出错误中断；
                                                      bit2：bus数据burst错误中断；
                                                      bit3：log数据溢出错误中断；
                                                      bit4：log数据传输帧数据小于设置值错误中断；
                                                      bit5：log数据传输帧数据大于设置值错误中断；
                                                      bit6：log数据传输帧数据小于设置值且无结束标识错误中断。 */
        unsigned int  reserved    : 25; /* bit[7-31]: 保留。 */
    } reg;
} DBG_DBG_INT_STS_UNION;
#define DBG_DBG_INT_STS_dbg_int_sts_START  (0)
#define DBG_DBG_INT_STS_dbg_int_sts_END    (6)


/*****************************************************************************
 结构名    : DBG_DBG_INT_CLR_UNION
 结构说明  : DBG_INT_CLR 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: DBG中断清除寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_int_clr_reg;
    struct
    {
        unsigned int  dbg_int_clr : 7;  /* bit[0-6] : DBG中断清除，对应位写1清0中断。
                                                      bit0：dat数据溢出错误中断清0；
                                                      bit1：bus数据溢出错误中断清0；
                                                      bit2：bus数据burst错误中断清0；
                                                      bit3：log数据溢出错误中断清0；
                                                      bit4：log数据传输帧数据小于设置值错误中断清0；
                                                      bit5：log数据传输帧数据大于设置值错误中断清0；
                                                      bit6：log数据传输帧数据小于设置值且无结束标识错误中断清0。 */
        unsigned int  reserved    : 25; /* bit[7-31]: 保留。 */
    } reg;
} DBG_DBG_INT_CLR_UNION;
#define DBG_DBG_INT_CLR_dbg_int_clr_START  (0)
#define DBG_DBG_INT_CLR_dbg_int_clr_END    (6)


/*****************************************************************************
 结构名    : DBG_DBG_INT_MSK_UNION
 结构说明  : DBG_INT_MSK 寄存器结构定义。地址偏移量:0x148，初值:0x00000000，宽度:32
 寄存器说明: DBG中断屏蔽寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_int_msk_reg;
    struct
    {
        unsigned int  dbg_int_msk : 7;  /* bit[0-6] : DBG中断屏蔽。
                                                      0：中断屏蔽使能，中断不上报(缺省状态)
                                                      1：中断可上报
                                                      bit0：dat数据溢出错误中断屏蔽位；
                                                      bit1：bus数据溢出错误中断屏蔽位；
                                                      bit2：bus数据burst错误中断屏蔽位；
                                                      bit3：log数据溢出错误中断屏蔽位；
                                                      bit4：log数据传输帧数据小于设置值错误中断屏蔽位；
                                                      bit5：log数据传输帧数据大于设置值错误中断屏蔽位；
                                                      bit6：log数据传输帧数据小于设置值且无结束标识错误中断屏蔽位。 */
        unsigned int  reserved    : 25; /* bit[7-31]: 保留。 */
    } reg;
} DBG_DBG_INT_MSK_UNION;
#define DBG_DBG_INT_MSK_dbg_int_msk_START  (0)
#define DBG_DBG_INT_MSK_dbg_int_msk_END    (6)


/*****************************************************************************
 结构名    : DBG_RFIN_DBG_FLT_UNION
 结构说明  : RFIN_DBG_FLT 寄存器结构定义。地址偏移量:0x00600，初值:0x00000000，宽度:32
 寄存器说明: DBG数采类型
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_flt_reg;
    struct
    {
        unsigned int  dbg_flt  : 2;  /* bit[0-1] : 模块数采ID间的过滤器，每个bit指示一个ID，例如，bit0，器ID号为dbg_id + 1，bit1，其ID号为dbg_id + 1，依此类推。
                                                   如果bit取值为1，表明该bit对应的ID有效，否则无效：
                                                   0，下行通道2天线数据同时采集
                                                   1，上行发送通道数据采集
                                                   2，下行通道单天线RXA数据采集
                                                   3，下行通道单天线RXB数据采集 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} DBG_RFIN_DBG_FLT_UNION;
#define DBG_RFIN_DBG_FLT_dbg_flt_START   (0)
#define DBG_RFIN_DBG_FLT_dbg_flt_END     (1)


/*****************************************************************************
 结构名    : DBG_RFIN_DBG_CH_UNION
 结构说明  : RFIN_DBG_CH 寄存器结构定义。地址偏移量:0x00608，初值:0x00000000，宽度:32
 寄存器说明: DBG数采选择
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_ch_reg;
    struct
    {
        unsigned int  dbg_dl_sel : 4;  /* bit[0-3]  : 下行数采使能，每个bit对应一个下行载波，取值为1表明该通载波数采使能：
                                                      [3]：下行载波3数采
                                                      [2]：下行载波2数采
                                                      [1]：下行载波1数采
                                                      [0]：下行载波0数采 */
        unsigned int  reserved_0 : 12; /* bit[4-15] : 保留 */
        unsigned int  dbg_ul_sel : 2;  /* bit[16-17]: 上行数采使能，每个bit对应一个上行载波，取值为1表明该载波数采使能：
                                                      [1]：上行载波1数采
                                                      [0]：上行载波0数采 */
        unsigned int  reserved_1 : 14; /* bit[18-31]: 保留 */
    } reg;
} DBG_RFIN_DBG_CH_UNION;
#define DBG_RFIN_DBG_CH_dbg_dl_sel_START  (0)
#define DBG_RFIN_DBG_CH_dbg_dl_sel_END    (3)
#define DBG_RFIN_DBG_CH_dbg_ul_sel_START  (16)
#define DBG_RFIN_DBG_CH_dbg_ul_sel_END    (17)


/*****************************************************************************
 结构名    : DBG_RFIN_DBG_MODE_UNION
 结构说明  : RFIN_DBG_MODE 寄存器结构定义。地址偏移量:0x0060C，初值:0x00000001，宽度:32
 寄存器说明: DBG数采模式
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_mode_reg;
    struct
    {
        unsigned int  dbg_rpt_mode : 1;  /* bit[0]    : 数采上报模式：
                                                        1'b0，数采功能触发后，采样dbg_pkg_num个数据包后自动结束
                                                        1'b1，只要dbg_en为1就一直采数上报，不受dbg_pkg_num限制 */
        unsigned int  reserved     : 15; /* bit[1-15] : 保留 */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: 数采包的个数 */
    } reg;
} DBG_RFIN_DBG_MODE_UNION;
#define DBG_RFIN_DBG_MODE_dbg_rpt_mode_START  (0)
#define DBG_RFIN_DBG_MODE_dbg_rpt_mode_END    (0)
#define DBG_RFIN_DBG_MODE_dbg_pkg_num_START   (16)
#define DBG_RFIN_DBG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 结构名    : DBG_RFIN_DBG_EN_UNION
 结构说明  : RFIN_DBG_EN 寄存器结构定义。地址偏移量:0x00610，初值:0x00000000，宽度:32
 寄存器说明: DBG数采使能
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_en_reg;
    struct
    {
        unsigned int  dbg_en   : 1;  /* bit[0]   : 数采使能：
                                                   1'b0，数采功能不使能
                                                   1'b1，数采功能使能 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_RFIN_DBG_EN_UNION;
#define DBG_RFIN_DBG_EN_dbg_en_START    (0)
#define DBG_RFIN_DBG_EN_dbg_en_END      (0)


/*****************************************************************************
 结构名    : DBG_FPU_DBG_LOG_CFG_UNION
 结构说明  : FPU_DBG_LOG_CFG 寄存器结构定义。地址偏移量:0x4408，初值:0x00000001，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_log_cfg_reg;
    struct
    {
        unsigned int  fpu_log_rpt_mode : 1;  /* bit[0]    : 可维可测数据上报模式：
                                                            'b0：触发后继续采样fpu_log_pkg_num个数据包后自动结束；
                                                            'b1：只要fpu_log_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved         : 15; /* bit[1-15] : 保留 */
        unsigned int  fpu_log_pkg_num  : 16; /* bit[16-31]: LOG信息可维可测的包个数 */
    } reg;
} DBG_FPU_DBG_LOG_CFG_UNION;
#define DBG_FPU_DBG_LOG_CFG_fpu_log_rpt_mode_START  (0)
#define DBG_FPU_DBG_LOG_CFG_fpu_log_rpt_mode_END    (0)
#define DBG_FPU_DBG_LOG_CFG_fpu_log_pkg_num_START   (16)
#define DBG_FPU_DBG_LOG_CFG_fpu_log_pkg_num_END     (31)


/*****************************************************************************
 结构名    : DBG_FPU_DBG_DAT_FLT_UNION
 结构说明  : FPU_DBG_DAT_FLT 寄存器结构定义。地址偏移量:0x4410，初值:0x00000010，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_dat_flt_reg;
    struct
    {
        unsigned int  fpu_dbg_filtrat : 16; /* bit[0-15] : 模块DAT ID间过滤器
                                                           [4] cfu调试信号。
                                                           [9] fpu_ls选择信号。
                                                           [11] fpu_lsu选择信号。
                                                           [12] fpu_emu选择信号。
                                                           [13] fpu_tru选择信号。
                                                           其他bit保留 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} DBG_FPU_DBG_DAT_FLT_UNION;
#define DBG_FPU_DBG_DAT_FLT_fpu_dbg_filtrat_START  (0)
#define DBG_FPU_DBG_DAT_FLT_fpu_dbg_filtrat_END    (15)


/*****************************************************************************
 结构名    : DBG_FPU_DBG_DAT_CFG0_UNION
 结构说明  : FPU_DBG_DAT_CFG0 寄存器结构定义。地址偏移量:0x4414，初值:0x03C00007，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_dat_cfg0_reg;
    struct
    {
        unsigned int  fpu_dbg_rpt_mode     : 1;  /* bit[0]    : 可维可测数据上报模式：
                                                                'b0：触发后继续采样fpu_dbg_pkg_num个数据包后自动结束；
                                                                'b1：只要fpu_dbg_en为1就上报，没有上报个数限制。 */
        unsigned int  fpu_FPU_DBG_comp_mod : 2;  /* bit[1-2]  : 可维可测数据上报数据拼接模式：
                                                                'd0：不拼接；
                                                                'd1：保留。
                                                                'd2：接收天线0数据拼接为一个64bit数据 word上报。
                                                                'd3：2天线数据拼接为一个64bit数据 word上报； */
        unsigned int  reserved             : 13; /* bit[3-15] : 保留 */
        unsigned int  fpu_dbg_pkg_num      : 16; /* bit[16-31]: 保留 */
    } reg;
} DBG_FPU_DBG_DAT_CFG0_UNION;
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_rpt_mode_START      (0)
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_rpt_mode_END        (0)
#define DBG_FPU_DBG_DAT_CFG0_fpu_FPU_DBG_comp_mod_START  (1)
#define DBG_FPU_DBG_DAT_CFG0_fpu_FPU_DBG_comp_mod_END    (2)
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_pkg_num_START       (16)
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_pkg_num_END         (31)


/*****************************************************************************
 结构名    : DBG_FPU_LOG_EN_UNION
 结构说明  : FPU_LOG_EN 寄存器结构定义。地址偏移量:0x4424，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      fpu_log_en_reg;
    struct
    {
        unsigned int  fpu_log_en : 1;  /* bit[0]   : LOG上报始能
                                                     1'b1:使能
                                                     1'b0:不使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_FPU_LOG_EN_UNION;
#define DBG_FPU_LOG_EN_fpu_log_en_START  (0)
#define DBG_FPU_LOG_EN_fpu_log_en_END    (0)


/*****************************************************************************
 结构名    : DBG_FPU_DBG_EN_UNION
 结构说明  : FPU_DBG_EN 寄存器结构定义。地址偏移量:0x4428，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_en_reg;
    struct
    {
        unsigned int  fpu_dbg_en : 1;  /* bit[0]   : dbg 上报是否始能
                                                     1'b1:使能
                                                     1'b0:不使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_FPU_DBG_EN_UNION;
#define DBG_FPU_DBG_EN_fpu_dbg_en_START  (0)
#define DBG_FPU_DBG_EN_fpu_dbg_en_END    (0)


/*****************************************************************************
 结构名    : DBG_FPU_LOG_DBG_SEL_UNION
 结构说明  : FPU_LOG_DBG_SEL 寄存器结构定义。地址偏移量:0x442C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      fpu_log_dbg_sel_reg;
    struct
    {
        unsigned int  fpu_cc_log_sel : 2;  /* bit[0-1] : 0: 选择pcc log数据；（保留）
                                                         1：选择cc1 log数据；（保留）
                                                         2: 选择cc2 log数据；（保留）
                                                         3：选择cc3 log数据；（保留） */
        unsigned int  fpu_cc_dbg_sel : 2;  /* bit[2-3] : 0: 选择pcc dbg数据；（保留）
                                                         1：选择cc1 dbg数据；（保留）
                                                         2: 选择cc2 dbg数据；（保留）
                                                         3：选择cc3 dbg数据；（保留） */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留 */
    } reg;
} DBG_FPU_LOG_DBG_SEL_UNION;
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_log_sel_START  (0)
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_log_sel_END    (1)
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_dbg_sel_START  (2)
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_dbg_sel_END    (3)


/*****************************************************************************
 结构名    : DBG_FPU_DEBUG_CTRL_UNION
 结构说明  : FPU_DEBUG_CTRL 寄存器结构定义。地址偏移量:0xE1134610，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      fpu_debug_ctrl_reg;
    struct
    {
        unsigned int  fpu_smp_dbg_sel    : 2;  /* bit[0-1]  : FPU SMP debug数据采集选择信号(调试用)
                                                              2'b0，选择pcc smp数据；
                                                              2'b01，选择cc1 smp数据；
                                                              2'b10，选择cc2 smp数据；
                                                              2'b11，选择cc3 smp数据；
                                                              生效时刻：立即生效 */
        unsigned int  reserved_0         : 2;  /* bit[2-3]  : 保留 */
        unsigned int  fpu_dbg_sel        : 3;  /* bit[4-6]  : FPU 各cc通路debug寄存器上报选择信号(调试用)
                                                              3'b0,pcc debug数据；
                                                              3'b1,cc1 debug数据；
                                                              3'b10,cc2 debug数据；
                                                              3'b11,cc3 debug数据；
                                                              3'b100,mlafc debug数据；
                                                              3'b101,csu0 debug数据；
                                                              3'b110,csu1 debug数据；
                                                              其余保留
                                                              生效时刻：立即生效 */
        unsigned int  reserved_1         : 1;  /* bit[7]    : 保留 */
        unsigned int  fpu_rfin_dbg_sel   : 2;  /* bit[8-9]  : FPU rfin debug寄存器上报选择信号(调试用)
                                                              2'b0，选择pcc rfin debug数据；
                                                              2'b01，选择cc1 rfin debug数据；
                                                              2'b10，选择cc2 rfin debug数据；
                                                              2'b11，选择cc3 rfin debug数据；
                                                              生效时刻：立即生效 */
        unsigned int  reserved_2         : 2;  /* bit[10-11]: 保留 */
        unsigned int  fpu_cc_dbg_mode    : 4;  /* bit[12-15]: FPU CC内部debug数据上报模式选择(调试用)
                                                              4'b0，选择上报cfu内部状态信息；
                                                              4'b1，选择上报dfu内部状态信息；
                                                              4'b10，选择上报smu内部状态信息；
                                                              4'b11，选择上报afc内部状态信息；
                                                              4'b100，选择上报tru内部状态信息；
                                                              4'b101，选择上报tau的内部状态信息；
                                                              4'b110，选择上报测量全通路状态信息；
                                                              4'b111，选择上报解调全通路状态信息；
                                                              4'b1000，选择上报smp内部状态信息；
                                                              4'b1001，选择上报cmu_buf内部状态信息。
                                                              生效时刻：立即生效 */
        unsigned int  fpu_cc_smp_dbg_sel : 2;  /* bit[16-17]: FPU CC内部smp debug数据上报模式选择(调试用)
                                                              2'b0，选择上报lsu输出的原始LS数据；
                                                              2'b1，选择上报ls_smp输出的LS数据；
                                                              2'b10，选择上报em_smp输出的emu和路测结果数据；
                                                              2'b11，选择上报tru_smp输出的pdp数据
                                                              生效时刻：立即生效 */
        unsigned int  reserved_3         : 2;  /* bit[18-19]: 保留 */
        unsigned int  fpu_smu_dbg_ch_sel : 2;  /* bit[20-21]: FPU CC内部smu debug信息通道选择(调试用)
                                                              2'b0，上报通道0
                                                              2'b1，上报通道1
                                                              2'b10，上报通道2
                                                              2'b11，上报通道3
                                                              生效时刻：立即生效 */
        unsigned int  reserved_4         : 10; /* bit[22-31]: 保留 */
    } reg;
} DBG_FPU_DEBUG_CTRL_UNION;
#define DBG_FPU_DEBUG_CTRL_fpu_smp_dbg_sel_START     (0)
#define DBG_FPU_DEBUG_CTRL_fpu_smp_dbg_sel_END       (1)
#define DBG_FPU_DEBUG_CTRL_fpu_dbg_sel_START         (4)
#define DBG_FPU_DEBUG_CTRL_fpu_dbg_sel_END           (6)
#define DBG_FPU_DEBUG_CTRL_fpu_rfin_dbg_sel_START    (8)
#define DBG_FPU_DEBUG_CTRL_fpu_rfin_dbg_sel_END      (9)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_dbg_mode_START     (12)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_dbg_mode_END       (15)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_smp_dbg_sel_START  (16)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_smp_dbg_sel_END    (17)
#define DBG_FPU_DEBUG_CTRL_fpu_smu_dbg_ch_sel_START  (20)
#define DBG_FPU_DEBUG_CTRL_fpu_smu_dbg_ch_sel_END    (21)


/*****************************************************************************
 结构名    : DBG_SMU_CC_DEBUG_SEL_UNION
 结构说明  : SMU_CC_DEBUG_SEL 寄存器结构定义。地址偏移量:0xE1161950，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  smu_cc_debug_sel : 3;  /* bit[0-2]  : 保留 */
        unsigned int  reserved_0       : 1;  /* bit[3]    : 保留 */
        unsigned int  smu_cc_debug_en  : 1;  /* bit[4]    : 保留 */
        unsigned int  reserved_1       : 3;  /* bit[5-7]  : 保留 */
        unsigned int  smu_ila_sel      : 3;  /* bit[8-10] : 保留 */
        unsigned int  reserved_2       : 21; /* bit[11-31]: 保留 */
    } reg;
} DBG_SMU_CC_DEBUG_SEL_UNION;
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_sel_START  (0)
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_sel_END    (2)
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_en_START   (4)
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_en_END     (4)
#define DBG_SMU_CC_DEBUG_SEL_smu_ila_sel_START       (8)
#define DBG_SMU_CC_DEBUG_SEL_smu_ila_sel_END         (10)


/*****************************************************************************
 结构名    : DBG_CC1_SMU_CC_DEBUG_SEL_UNION
 结构说明  : CC1_SMU_CC_DEBUG_SEL 寄存器结构定义。地址偏移量:0xE1163950，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      cc1_smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  cc1_smu_cc_debug_sel : 3;  /* bit[0-2]  : 保留 */
        unsigned int  reserved_0           : 1;  /* bit[3]    : 保留 */
        unsigned int  cc1_smu_cc_debug_en  : 1;  /* bit[4]    : 保留 */
        unsigned int  reserved_1           : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cc1_smu_ila_sel      : 3;  /* bit[8-10] : 保留 */
        unsigned int  reserved_2           : 21; /* bit[11-31]: 保留 */
    } reg;
} DBG_CC1_SMU_CC_DEBUG_SEL_UNION;
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_sel_START  (0)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_sel_END    (2)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_en_START   (4)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_en_END     (4)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_ila_sel_START       (8)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_ila_sel_END         (10)


/*****************************************************************************
 结构名    : DBG_CC2_SMU_CC_DEBUG_SEL_UNION
 结构说明  : CC2_SMU_CC_DEBUG_SEL 寄存器结构定义。地址偏移量:0xE1165950，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      cc2_smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  cc2_smu_cc_debug_sel : 3;  /* bit[0-2]  : 保留 */
        unsigned int  reserved_0           : 1;  /* bit[3]    : 保留 */
        unsigned int  cc2_smu_cc_debug_en  : 1;  /* bit[4]    : 保留 */
        unsigned int  reserved_1           : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cc2_smu_ila_sel      : 3;  /* bit[8-10] : 保留 */
        unsigned int  reserved_2           : 21; /* bit[11-31]: 保留 */
    } reg;
} DBG_CC2_SMU_CC_DEBUG_SEL_UNION;
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_sel_START  (0)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_sel_END    (2)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_en_START   (4)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_en_END     (4)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_ila_sel_START       (8)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_ila_sel_END         (10)


/*****************************************************************************
 结构名    : DBG_CC3_SMU_CC_DEBUG_SEL_UNION
 结构说明  : CC3_SMU_CC_DEBUG_SEL 寄存器结构定义。地址偏移量:0xE1167950，初值:0x00000000，宽度:32
 寄存器说明: 寄存器。
*****************************************************************************/
typedef union
{
    unsigned int      cc3_smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  cc3_smu_cc_debug_sel : 3;  /* bit[0-2]  : 保留 */
        unsigned int  reserved_0           : 1;  /* bit[3]    : 保留 */
        unsigned int  cc3_smu_cc_debug_en  : 1;  /* bit[4]    : 保留 */
        unsigned int  reserved_1           : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cc3_smu_ila_sel      : 3;  /* bit[8-10] : 保留 */
        unsigned int  reserved_2           : 21; /* bit[11-31]: 保留 */
    } reg;
} DBG_CC3_SMU_CC_DEBUG_SEL_UNION;
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_sel_START  (0)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_sel_END    (2)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_en_START   (4)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_en_END     (4)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_ila_sel_START       (8)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_ila_sel_END         (10)


/*****************************************************************************
 结构名    : DBG_PDU_DBG_LOG_MODE_UNION
 结构说明  : PDU_DBG_LOG_MODE 寄存器结构定义。地址偏移量:0x4008，初值:0x00000002，宽度:32
 寄存器说明: 模块LOG 模式寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : 保留 */
        unsigned int  cr2dbg_log_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                               0：触发后继续采样dbg_pkg_num个数据包后自动结束
                                                               1：只要dbg_rpt_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved_1          : 14; /* bit[2-15] : 保留 */
        unsigned int  cr2dbg_log_pkt_num  : 16; /* bit[16-31]: LOG信息可维可测的包个数 */
    } reg;
} DBG_PDU_DBG_LOG_MODE_UNION;
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_rpt_mode_START  (1)
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_rpt_mode_END    (1)
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_pkt_num_START   (16)
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_pkt_num_END     (31)


/*****************************************************************************
 结构名    : DBG_PDU_DBG_LOG_EN_UNION
 结构说明  : PDU_DBG_LOG_EN 寄存器结构定义。地址偏移量:0x400C，初值:0x00000000，宽度:32
 寄存器说明: 模块LOG EN寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_log_en_reg;
    struct
    {
        unsigned int  cr2dbg_log_en : 1;  /* bit[0]   : 模块LOG使能                              
                                                        0：可维可测功能不使能                             1：可维可测功能使能 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_PDU_DBG_LOG_EN_UNION;
#define DBG_PDU_DBG_LOG_EN_cr2dbg_log_en_START  (0)
#define DBG_PDU_DBG_LOG_EN_cr2dbg_log_en_END    (0)


/*****************************************************************************
 结构名    : DBG_PDU_DBG_DAT_MODE_UNION
 结构说明  : PDU_DBG_DAT_MODE 寄存器结构定义。地址偏移量:0x401C，初值:0x00000002，宽度:32
 寄存器说明: 模块DAT 模式寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_dat_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : 保留 */
        unsigned int  cr2dbg_dat_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                               0：触发后继续采样dbg_pkg_num个数据包后自动结束
                                                               1：只要dbg_rpt_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved_1          : 14; /* bit[2-15] : 保留 */
        unsigned int  cr2dbg_dat_pkt_num  : 16; /* bit[16-31]: DAT信息可维可测的包个数 */
    } reg;
} DBG_PDU_DBG_DAT_MODE_UNION;
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_START  (1)
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_END    (1)
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_pkt_num_START   (16)
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_pkt_num_END     (31)


/*****************************************************************************
 结构名    : DBG_PDU_DBG_DAT_EN_UNION
 结构说明  : PDU_DBG_DAT_EN 寄存器结构定义。地址偏移量:0x4020，初值:0x00000000，宽度:32
 寄存器说明: 模块DAT EN寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_dat_en_reg;
    struct
    {
        unsigned int  cr2dbg_dat_en : 1;  /* bit[0]   : 模块DAT使能                              
                                                        0：可维可测功能不使能                             1：可维可测功能使能 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_PDU_DBG_DAT_EN_UNION;
#define DBG_PDU_DBG_DAT_EN_cr2dbg_dat_en_START  (0)
#define DBG_PDU_DBG_DAT_EN_cr2dbg_dat_en_END    (0)


/*****************************************************************************
 结构名    : DBG_PDU2_DBG_LOG_MODE_UNION
 结构说明  : PDU2_DBG_LOG_MODE 寄存器结构定义。地址偏移量:0xE1B14008，初值:0x00000002，宽度:32
 寄存器说明: 模块LOG 模式寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : 保留 */
        unsigned int  cr2dbg_log_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                               0：触发后继续采样dbg_pkg_num个数据包后自动结束
                                                               1：只要dbg_rpt_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved_1          : 14; /* bit[2-15] : 保留 */
        unsigned int  cr2dbg_log_pkt_num  : 16; /* bit[16-31]: LOG信息可维可测的包个数 */
    } reg;
} DBG_PDU2_DBG_LOG_MODE_UNION;
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_rpt_mode_START  (1)
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_rpt_mode_END    (1)
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_pkt_num_START   (16)
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_pkt_num_END     (31)


/*****************************************************************************
 结构名    : DBG_PDU2_DBG_LOG_EN_UNION
 结构说明  : PDU2_DBG_LOG_EN 寄存器结构定义。地址偏移量:0xE1B1400C，初值:0x00000000，宽度:32
 寄存器说明: 模块LOG EN寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_log_en_reg;
    struct
    {
        unsigned int  cr2dbg_log_en : 1;  /* bit[0]   : 模块LOG使能                              
                                                        0：可维可测功能不使能                             1：可维可测功能使能 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_PDU2_DBG_LOG_EN_UNION;
#define DBG_PDU2_DBG_LOG_EN_cr2dbg_log_en_START  (0)
#define DBG_PDU2_DBG_LOG_EN_cr2dbg_log_en_END    (0)


/*****************************************************************************
 结构名    : DBG_PDU2_DBG_DAT_MODE_UNION
 结构说明  : PDU2_DBG_DAT_MODE 寄存器结构定义。地址偏移量:0xE1B1401C，初值:0x00000002，宽度:32
 寄存器说明: 模块DAT 模式寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_dat_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : 保留 */
        unsigned int  cr2dbg_dat_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                               0：触发后继续采样dbg_pkg_num个数据包后自动结束
                                                               1：只要dbg_rpt_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved_1          : 14; /* bit[2-15] : 保留 */
        unsigned int  cr2dbg_dat_pkt_num  : 16; /* bit[16-31]: DAT信息可维可测的包个数 */
    } reg;
} DBG_PDU2_DBG_DAT_MODE_UNION;
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_START  (1)
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_END    (1)
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_pkt_num_START   (16)
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_pkt_num_END     (31)


/*****************************************************************************
 结构名    : DBG_PDU2_DBG_DAT_EN_UNION
 结构说明  : PDU2_DBG_DAT_EN 寄存器结构定义。地址偏移量:0xE1B14020，初值:0x00000000，宽度:32
 寄存器说明: 模块DAT EN寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_dat_en_reg;
    struct
    {
        unsigned int  cr2dbg_dat_en : 1;  /* bit[0]   : 模块DAT使能                              
                                                        0：可维可测功能不使能                             1：可维可测功能使能 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_PDU2_DBG_DAT_EN_UNION;
#define DBG_PDU2_DBG_DAT_EN_cr2dbg_dat_en_START  (0)
#define DBG_PDU2_DBG_DAT_EN_cr2dbg_dat_en_END    (0)


/*****************************************************************************
 结构名    : DBG_CQI_DBG_START_TIME_UNION
 结构说明  : CQI_DBG_START_TIME 寄存器结构定义。地址偏移量:0x3300，初值:0x00000000，宽度:32
 寄存器说明: 可维可测的开始时间
*****************************************************************************/
typedef union
{
    unsigned int      cqi_dbg_start_time_reg;
    struct
    {
        unsigned int  dbg_at_ts_num  : 12; /* bit[0-11] : 可维可测启动时间，以系统定时参考，symbol内Ts计数 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  dbg_at_sym_num : 4;  /* bit[16-19]: 可维可测启动时间，以系统定时参考，子帧内的符号计数 */
        unsigned int  reserved_1     : 12; /* bit[20-31]: 保留 */
    } reg;
} DBG_CQI_DBG_START_TIME_UNION;
#define DBG_CQI_DBG_START_TIME_dbg_at_ts_num_START   (0)
#define DBG_CQI_DBG_START_TIME_dbg_at_ts_num_END     (11)
#define DBG_CQI_DBG_START_TIME_dbg_at_sym_num_START  (16)
#define DBG_CQI_DBG_START_TIME_dbg_at_sym_num_END    (19)


/*****************************************************************************
 结构名    : DBG_CQI_DBG_DAT_EN_UNION
 结构说明  : CQI_DBG_DAT_EN 寄存器结构定义。地址偏移量:0x3318，初值:0x00000000，宽度:32
 寄存器说明: 数采使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cqi_dbg_dat_en_reg;
    struct
    {
        unsigned int  dbg_dat_en : 1;  /* bit[0-0] : 数据采集使能
                                                     0：数采不使能
                                                     1：数采使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_CQI_DBG_DAT_EN_UNION;
#define DBG_CQI_DBG_DAT_EN_dbg_dat_en_START  (0)
#define DBG_CQI_DBG_DAT_EN_dbg_dat_en_END    (0)


/*****************************************************************************
 结构名    : DBG_PB_DBG_LOG_MODE_UNION
 结构说明  : PB_DBG_LOG_MODE 寄存器结构定义。地址偏移量:0x1510，初值:0x00000002，宽度:32
 寄存器说明: LOG信息模式寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pb_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : 保留 */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                        'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
                                                        'b1：只要dbg_rpt_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved_1   : 14; /* bit[2-15] : 保留 */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: LOG信息可维可测的包个数 */
    } reg;
} DBG_PB_DBG_LOG_MODE_UNION;
#define DBG_PB_DBG_LOG_MODE_dbg_rpt_mode_START  (1)
#define DBG_PB_DBG_LOG_MODE_dbg_rpt_mode_END    (1)
#define DBG_PB_DBG_LOG_MODE_dbg_pkg_num_START   (16)
#define DBG_PB_DBG_LOG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 结构名    : DBG_PB_DBG_LOG_EN_UNION
 结构说明  : PB_DBG_LOG_EN 寄存器结构定义。地址偏移量:0x1514，初值:0x00000000，宽度:32
 寄存器说明: LOG信息使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pb_dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : 模块LOG使能                              
                                                     1'b0：可维可测功能不使能                             1'b1：可维可测功能使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_PB_DBG_LOG_EN_UNION;
#define DBG_PB_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_PB_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 结构名    : DBG_TDL_DBG_LOG_FLT_UNION
 结构说明  : TDL_DBG_LOG_FLT 寄存器结构定义。地址偏移量:0xE1C000D0，初值:0x0000000F，宽度:32
 寄存器说明: 可维可测上报LOG ID子类过滤器
*****************************************************************************/
typedef union
{
    unsigned int      tdl_dbg_log_flt_reg;
    struct
    {
        unsigned int  dbg_log_flt : 4;  /* bit[0-3] : 可维可测上报数据组类有效指示，[n]对应第n组上报数据，[0]对应第0组上报数据：
                                                      'b1：对应可维可测数据组上报输出；
                                                      'b0：对应可维可测数据组不上报输出。 */
        unsigned int  reserved    : 28; /* bit[4-31]: 保留 */
    } reg;
} DBG_TDL_DBG_LOG_FLT_UNION;
#define DBG_TDL_DBG_LOG_FLT_dbg_log_flt_START  (0)
#define DBG_TDL_DBG_LOG_FLT_dbg_log_flt_END    (3)


/*****************************************************************************
 结构名    : DBG_TDL_DBG_LOG_MODE_UNION
 结构说明  : TDL_DBG_LOG_MODE 寄存器结构定义。地址偏移量:0xE1C000D4，初值:0x00000002，宽度:32
 寄存器说明: 可维可测上报控制寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tdl_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : 保留 */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                        'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
                                                        'b1：只要dbg_log_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved_1   : 14; /* bit[2-15] : 保留 */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: 
                                                        LOG信息可维可测的包个数 */
    } reg;
} DBG_TDL_DBG_LOG_MODE_UNION;
#define DBG_TDL_DBG_LOG_MODE_dbg_rpt_mode_START  (1)
#define DBG_TDL_DBG_LOG_MODE_dbg_rpt_mode_END    (1)
#define DBG_TDL_DBG_LOG_MODE_dbg_pkg_num_START   (16)
#define DBG_TDL_DBG_LOG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 结构名    : DBG_TDL_DBG_LOG_EN_UNION
 结构说明  : TDL_DBG_LOG_EN 寄存器结构定义。地址偏移量:0xE1C000DC，初值:0x00000000，宽度:32
 寄存器说明: 可维可测控制使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tdl_dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : 可维可测LOG使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
                                                     1'b0：可维可测功能不使能                             1'b1：可维可测功能使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_TDL_DBG_LOG_EN_UNION;
#define DBG_TDL_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_TDL_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 结构名    : DBG_TDL2_DBG_LOG_FLT_UNION
 结构说明  : TDL2_DBG_LOG_FLT 寄存器结构定义。地址偏移量:0xE1C200D0，初值:0x0000000F，宽度:32
 寄存器说明: 可维可测上报LOG ID子类过滤器
*****************************************************************************/
typedef union
{
    unsigned int      tdl2_dbg_log_flt_reg;
    struct
    {
        unsigned int  dbg_log_flt : 4;  /* bit[0-3] : 可维可测上报数据组类有效指示，[n]对应第n组上报数据，[0]对应第0组上报数据：
                                                      'b1：对应可维可测数据组上报输出；
                                                      'b0：对应可维可测数据组不上报输出。 */
        unsigned int  reserved    : 28; /* bit[4-31]: 保留 */
    } reg;
} DBG_TDL2_DBG_LOG_FLT_UNION;
#define DBG_TDL2_DBG_LOG_FLT_dbg_log_flt_START  (0)
#define DBG_TDL2_DBG_LOG_FLT_dbg_log_flt_END    (3)


/*****************************************************************************
 结构名    : DBG_TDL2_DBG_LOG_MODE_UNION
 结构说明  : TDL2_DBG_LOG_MODE 寄存器结构定义。地址偏移量:0xE1C200D4，初值:0x00000002，宽度:32
 寄存器说明: 可维可测上报控制寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tdl2_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : 保留 */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                        'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
                                                        'b1：只要dbg_log_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved_1   : 14; /* bit[2-15] : 保留 */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: 
                                                        LOG信息可维可测的包个数 */
    } reg;
} DBG_TDL2_DBG_LOG_MODE_UNION;
#define DBG_TDL2_DBG_LOG_MODE_dbg_rpt_mode_START  (1)
#define DBG_TDL2_DBG_LOG_MODE_dbg_rpt_mode_END    (1)
#define DBG_TDL2_DBG_LOG_MODE_dbg_pkg_num_START   (16)
#define DBG_TDL2_DBG_LOG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 结构名    : DBG_TDL2_DBG_LOG_EN_UNION
 结构说明  : TDL2_DBG_LOG_EN 寄存器结构定义。地址偏移量:0xE1C200DC，初值:0x00000000，宽度:32
 寄存器说明: 可维可测控制使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tdl2_dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : 可维可测LOG使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
                                                     1'b0：可维可测功能不使能                             1'b1：可维可测功能使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_TDL2_DBG_LOG_EN_UNION;
#define DBG_TDL2_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_TDL2_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_BUS_ADDR_UNION
 结构说明  : DMA_DBG_BUS_ADDR 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 可维可测BUS通道buffer地址寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_addr_reg;
    struct
    {
        unsigned int  reserved      : 3;  /* bit[0-2] : 保留。 */
        unsigned int  dma_bus_baddr : 29; /* bit[3-31]: BUS buffer基地址。DMA将数据从可维可测模块搬移到以该地址为起始地址的buffer内。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_BUS_ADDR_UNION;
#define DBG_DMA_DBG_BUS_ADDR_dma_bus_baddr_START  (3)
#define DBG_DMA_DBG_BUS_ADDR_dma_bus_baddr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_BUS_WPTR_UNION
 结构说明  : DMA_DBG_BUS_WPTR 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: 可维可测BUS通道写指针寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_wptr_reg;
    struct
    {
        unsigned int  reserved     : 3;  /* bit[0-2] : 保留。 */
        unsigned int  dma_bus_wptr : 29; /* bit[3-31]: BUS buffer写指针。软件维护。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_BUS_WPTR_UNION;
#define DBG_DMA_DBG_BUS_WPTR_dma_bus_wptr_START  (3)
#define DBG_DMA_DBG_BUS_WPTR_dma_bus_wptr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_BUS_RPTR_UNION
 结构说明  : DMA_DBG_BUS_RPTR 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: 可维可测BUS通道读指针寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_rptr_reg;
    struct
    {
        unsigned int  reserved     : 3;  /* bit[0-2] : 保留。 */
        unsigned int  dma_bus_rptr : 29; /* bit[3-31]: BUS buffer读指针。硬件从SOCP模块读取更新，软件只读。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_BUS_RPTR_UNION;
#define DBG_DMA_DBG_BUS_RPTR_dma_bus_rptr_START  (3)
#define DBG_DMA_DBG_BUS_RPTR_dma_bus_rptr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_BUS_CFG_UNION
 结构说明  : DMA_DBG_BUS_CFG 寄存器结构定义。地址偏移量:0x020C，初值:0x00000008，宽度:32
 寄存器说明: 可维可测BUS通道配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_cfg_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : 保留。 */
        unsigned int  dma_bus_buf_len : 21; /* bit[3-23] : BUS buffer长度。8字节对齐。 */
        unsigned int  reserved_1      : 8;  /* bit[24-31]: 保留。 */
    } reg;
} DBG_DMA_DBG_BUS_CFG_UNION;
#define DBG_DMA_DBG_BUS_CFG_dma_bus_buf_len_START  (3)
#define DBG_DMA_DBG_BUS_CFG_dma_bus_buf_len_END    (23)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_LOG_ADDR_UNION
 结构说明  : DMA_DBG_LOG_ADDR 寄存器结构定义。地址偏移量:0x0210，初值:0x00000000，宽度:32
 寄存器说明: 可维可测LOG通道buffer地址寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_addr_reg;
    struct
    {
        unsigned int  reserved  : 3;  /* bit[0-2] : 保留。 */
        unsigned int  log_baddr : 29; /* bit[3-31]: LOG buffer基地址。DMA将数据从可维可测模块搬移到以该地址为起始地址的buffer内。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_LOG_ADDR_UNION;
#define DBG_DMA_DBG_LOG_ADDR_log_baddr_START  (3)
#define DBG_DMA_DBG_LOG_ADDR_log_baddr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_LOG_WPTR_UNION
 结构说明  : DMA_DBG_LOG_WPTR 寄存器结构定义。地址偏移量:0x0214，初值:0x00000000，宽度:32
 寄存器说明: 可维可测LOG通道写指针寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_wptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : 保留。 */
        unsigned int  log_wptr : 29; /* bit[3-31]: LOG buffer写指针。软件维护。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_LOG_WPTR_UNION;
#define DBG_DMA_DBG_LOG_WPTR_log_wptr_START  (3)
#define DBG_DMA_DBG_LOG_WPTR_log_wptr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_LOG_RPTR_UNION
 结构说明  : DMA_DBG_LOG_RPTR 寄存器结构定义。地址偏移量:0x0218，初值:0x00000000，宽度:32
 寄存器说明: 可维可测LOG通道读指针寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_rptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : 保留。 */
        unsigned int  log_rptr : 29; /* bit[3-31]: LOG buffer读指针。硬件从SOCP模块读取更新，软件只读。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_LOG_RPTR_UNION;
#define DBG_DMA_DBG_LOG_RPTR_log_rptr_START  (3)
#define DBG_DMA_DBG_LOG_RPTR_log_rptr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_LOG_CFG_UNION
 结构说明  : DMA_DBG_LOG_CFG 寄存器结构定义。地址偏移量:0x021C，初值:0x00000008，宽度:32
 寄存器说明: 可维可测LOG通道配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_cfg_reg;
    struct
    {
        unsigned int  reserved_0  : 3;  /* bit[0-2]  : 保留。 */
        unsigned int  log_buf_len : 21; /* bit[3-23] : LOG buffer长度。8字节对齐。 */
        unsigned int  reserved_1  : 8;  /* bit[24-31]: 保留。 */
    } reg;
} DBG_DMA_DBG_LOG_CFG_UNION;
#define DBG_DMA_DBG_LOG_CFG_log_buf_len_START  (3)
#define DBG_DMA_DBG_LOG_CFG_log_buf_len_END    (23)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_DS_ADDR_UNION
 结构说明  : DMA_DBG_DS_ADDR 寄存器结构定义。地址偏移量:0x0280，初值:0x00000000，宽度:32
 寄存器说明: 可维可测数采通道buffer地址
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_addr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : 保留。 */
        unsigned int  ds_baddr : 29; /* bit[3-31]: 可维可测数据采集通道buffer起始地址。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_DS_ADDR_UNION;
#define DBG_DMA_DBG_DS_ADDR_ds_baddr_START  (3)
#define DBG_DMA_DBG_DS_ADDR_ds_baddr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_DS_WPTR_UNION
 结构说明  : DMA_DBG_DS_WPTR 寄存器结构定义。地址偏移量:0x0284，初值:0x00000000，宽度:32
 寄存器说明: 可维可测数采通道写指针寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_wptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : 保留。 */
        unsigned int  ds_wptr  : 29; /* bit[3-31]: 可维可测数据采集通道写指针。软件维护。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_DS_WPTR_UNION;
#define DBG_DMA_DBG_DS_WPTR_ds_wptr_START   (3)
#define DBG_DMA_DBG_DS_WPTR_ds_wptr_END     (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_DS_RPTR_UNION
 结构说明  : DMA_DBG_DS_RPTR 寄存器结构定义。地址偏移量:0x0288，初值:0x00000000，宽度:32
 寄存器说明: 可维可测数采通道读指针寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_rptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : 保留。 */
        unsigned int  ds_rptr  : 29; /* bit[3-31]: 可维可测数据采集通道读指针。指示软件读操作起始地址。软件维护。8字节对齐。 */
    } reg;
} DBG_DMA_DBG_DS_RPTR_UNION;
#define DBG_DMA_DBG_DS_RPTR_ds_rptr_START   (3)
#define DBG_DMA_DBG_DS_RPTR_ds_rptr_END     (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_DS_CFG_UNION
 结构说明  : DMA_DBG_DS_CFG 寄存器结构定义。地址偏移量:0x028C，初值:0x00000008，宽度:32
 寄存器说明: 可维可测数采通道配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_cfg_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留。 */
        unsigned int  ds_buf_len       : 25; /* bit[3-27] : 可维可测数据采集通道buffer长度。8字节对齐，必须为包长的整数倍 */
        unsigned int  reserved_1       : 2;  /* bit[28-29]: 保留。 */
        unsigned int  ds_overflow_sts  : 1;  /* bit[30]   : 可维可测数据采集通道buffer溢出状态。
                                                            0：未溢出(ds_overflow_ctrl=0)或未循环覆盖(ds_overflow_ctrl=1)
                                                            1：已溢出(ds_overflow_ctrl=0)或已循环覆盖(ds_overflow_ctrl=1) */
        unsigned int  ds_overflow_ctrl : 1;  /* bit[31]   : 可维可测数据采集通道buffer溢出处理控制。
                                                            0：stop，将当前buffer的后续数据丢弃；
                                                            1：buffer覆盖，回到起始地址写入。 */
    } reg;
} DBG_DMA_DBG_DS_CFG_UNION;
#define DBG_DMA_DBG_DS_CFG_ds_buf_len_START        (3)
#define DBG_DMA_DBG_DS_CFG_ds_buf_len_END          (27)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_sts_START   (30)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_sts_END     (30)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_ctrl_START  (31)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_ctrl_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_PTR_ADDR_UNION
 结构说明  : DMA_DBG_PTR_ADDR 寄存器结构定义。地址偏移量:0x0290，初值:0x00000000，宽度:32
 寄存器说明: 可维可测buffer读写指针起始地址寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ptr_addr_reg;
    struct
    {
        unsigned int  reserved : 2;  /* bit[0-1] : 保留。 */
        unsigned int  ptr_addr : 30; /* bit[2-31]: 可维可测通道buffer写指针起始地址。存放的是LOG 0通道的写指针，后面依次按照固定格式存放其它LOG通道和数采通道指针。4字节对齐。 */
    } reg;
} DBG_DMA_DBG_PTR_ADDR_UNION;
#define DBG_DMA_DBG_PTR_ADDR_ptr_addr_START  (2)
#define DBG_DMA_DBG_PTR_ADDR_ptr_addr_END    (31)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_DS_CH_EN_UNION
 结构说明  : DMA_DBG_DS_CH_EN 寄存器结构定义。地址偏移量:0x0294，初值:0x00000000，宽度:32
 寄存器说明: 可维可测通道数采使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_ch_en_reg;
    struct
    {
        unsigned int  ds_ch_en : 1;  /* bit[0]   : 数采通道使能。
                                                   0：不使能；
                                                   1：使能。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} DBG_DMA_DBG_DS_CH_EN_UNION;
#define DBG_DMA_DBG_DS_CH_EN_ds_ch_en_START  (0)
#define DBG_DMA_DBG_DS_CH_EN_ds_ch_en_END    (0)


/*****************************************************************************
 结构名    : DBG_DBG_CH_STS0_UNION
 结构说明  : DBG_CH_STS0 寄存器结构定义。地址偏移量:0x029C，初值:0x00000000，宽度:32
 寄存器说明: 可维可测通道状态寄存器0
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ch_sts0_reg;
    struct
    {
        unsigned int  log0_overflow : 1;  /* bit[0]    : LOG0通道buffer上溢。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  log1_overflow : 1;  /* bit[1]    : LOG1通道buffer上溢。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  reserved_0    : 10; /* bit[2-11] : 保留。 */
        unsigned int  log0_unmtch   : 1;  /* bit[12]   : LOG0通道包头、包尾指示不匹配。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  log1_unmtch   : 1;  /* bit[13]   : LOG1通道包头、包尾指示不匹配。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  reserved_1    : 6;  /* bit[14-19]: 保留。 */
        unsigned int  ds_unmtch     : 1;  /* bit[20]   : 数采通道包头、包尾指示不匹配。每个数据包都是以包头指示sop开始，以包尾指示eop结束。如果连续收到sop或者eop，该状态会触发。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  log0_long_pkt : 1;  /* bit[21]   : LOG0通道长包异常指示。指示实际包长度大于包头长度域指示的包长。写1清除。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  log1_long_pkt : 1;  /* bit[22]   : LOG1通道长包异常指示。指示实际包长度大于包头长度域指示的包长。写1清除。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  reserved_2    : 6;  /* bit[23-28]: 保留。 */
        unsigned int  ds_long_pkt   : 1;  /* bit[29]   : 数采通道长包异常指示。指示实际包长度大于包头长度域指示的包长。写1清除。
                                                         0：无异常；
                                                         1：异常。 */
        unsigned int  reserved_3    : 2;  /* bit[30-31]: 保留。 */
    } reg;
} DBG_DBG_CH_STS0_UNION;
#define DBG_DBG_CH_STS0_log0_overflow_START  (0)
#define DBG_DBG_CH_STS0_log0_overflow_END    (0)
#define DBG_DBG_CH_STS0_log1_overflow_START  (1)
#define DBG_DBG_CH_STS0_log1_overflow_END    (1)
#define DBG_DBG_CH_STS0_log0_unmtch_START    (12)
#define DBG_DBG_CH_STS0_log0_unmtch_END      (12)
#define DBG_DBG_CH_STS0_log1_unmtch_START    (13)
#define DBG_DBG_CH_STS0_log1_unmtch_END      (13)
#define DBG_DBG_CH_STS0_ds_unmtch_START      (20)
#define DBG_DBG_CH_STS0_ds_unmtch_END        (20)
#define DBG_DBG_CH_STS0_log0_long_pkt_START  (21)
#define DBG_DBG_CH_STS0_log0_long_pkt_END    (21)
#define DBG_DBG_CH_STS0_log1_long_pkt_START  (22)
#define DBG_DBG_CH_STS0_log1_long_pkt_END    (22)
#define DBG_DBG_CH_STS0_ds_long_pkt_START    (29)
#define DBG_DBG_CH_STS0_ds_long_pkt_END      (29)


/*****************************************************************************
 结构名    : DBG_DMA_DBG_LOG_CH_EN_UNION
 结构说明  : DMA_DBG_LOG_CH_EN 寄存器结构定义。地址偏移量:0x02B8，初值:0x00000000，宽度:32
 寄存器说明: 可维可测LOG通道使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_ch_en_reg;
    struct
    {
        unsigned int  log_ch_en : 1;  /* bit[0]   : LOG通道使能寄存器。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。 */
    } reg;
} DBG_DMA_DBG_LOG_CH_EN_UNION;
#define DBG_DMA_DBG_LOG_CH_EN_log_ch_en_START  (0)
#define DBG_DMA_DBG_LOG_CH_EN_log_ch_en_END    (0)


/*****************************************************************************
 结构名    : DBG_COM_CLK_EN_UNION
 结构说明  : COM_CLK_EN 寄存器结构定义。地址偏移量:0xE1FC00E0，初值:0x00000000，宽度:32
 寄存器说明: COM时钟使能
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_en_reg;
    struct
    {
        unsigned int  reserved_0        : 6;  /* bit[0-5] : 保留 */
        unsigned int  com_tl_dbg_clk_en : 1;  /* bit[6]   : dbg时钟使能信号。只写信号，写1使能 */
        unsigned int  reserved_1        : 25; /* bit[7-31]: 保留 */
    } reg;
} DBG_COM_CLK_EN_UNION;
#define DBG_COM_CLK_EN_com_tl_dbg_clk_en_START  (6)
#define DBG_COM_CLK_EN_com_tl_dbg_clk_en_END    (6)


/*****************************************************************************
 结构名    : DBG_COM_SRST_DIS_UNION
 结构说明  : COM_SRST_DIS 寄存器结构定义。地址偏移量:0xE1FC00F4，初值:0x00000000，宽度:32
 寄存器说明: COM复位清除
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_dis_reg;
    struct
    {
        unsigned int  reserved_0          : 4;  /* bit[0-3] : 保留 */
        unsigned int  com_l_sdr_srst_dis  : 1;  /* bit[4]   : sdr复位清除信号。只写信号，写1使能清零 */
        unsigned int  reserved_1          : 1;  /* bit[5]   : 保留 */
        unsigned int  com_tl_dbg_srst_dis : 1;  /* bit[6]   : dbg复位清除信号。只写信号，写1使能清零 */
        unsigned int  reserved_2          : 25; /* bit[7-31]: 保留 */
    } reg;
} DBG_COM_SRST_DIS_UNION;
#define DBG_COM_SRST_DIS_com_l_sdr_srst_dis_START   (4)
#define DBG_COM_SRST_DIS_com_l_sdr_srst_dis_END     (4)
#define DBG_COM_SRST_DIS_com_tl_dbg_srst_dis_START  (6)
#define DBG_COM_SRST_DIS_com_tl_dbg_srst_dis_END    (6)


/*****************************************************************************
 结构名    : DBG_DBG_AGC_DATA_SEL_UNION
 结构说明  : DBG_AGC_DATA_SEL 寄存器结构定义。地址偏移量:0xE19912DC，初值:0x00000000，宽度:32
 寄存器说明: RX数采数据选择
*****************************************************************************/
typedef union
{
    unsigned int      dbg_agc_data_sel_reg;
    struct
    {
        unsigned int  dbg_data_sel : 5;  /* bit[0-4]  : 基带数据搬运选择，表示采数位置。
                                                        0，ADC输出信号，W和TDS都用；
                                                        1，spmv输输出信号，W和TDS都用；
                                                        2，dcoc输出信号，仅TDS使用；
                                                        3，dgt1输出信号，仅TDS使用；
                                                        4，fir输出信号，W和TDS都用；
                                                        5，rxiq输出信号，W和TDS都用；
                                                        6，dwf输出信号，W和TDS都用；
                                                        7，codc输出信号，W和TDS都使用；
                                                        8，sc_filter输出信号，W和TDS都使用；
                                                        9，TDS的rrc输出信号，仅TDS使用；
                                                        10，TDS的dgt2输出信号，仅TDS使用；
                                                        11，W的rrc输出信号，主载波和辅载波分时复用；
                                                        12，W的8bitDAGC输出信号，主载波和辅载波分时复用；
                                                        13，W的4bitDAGC输出信号，主载波和辅载波分时复用；
                                                        14，dwf的辅载波输出信号，仅W使用；
                                                        15，sc_filter的辅载波输入信号，仅W使用；
                                                        16，rrc的辅载波输入信号，仅W使用；
                                                        17，幅度为2047的三角波，对应12bits数据；
                                                        18，幅度为127的三角波，对应8bit数据；
                                                        19，频率校正freq_error输出，低12bit为数据；
                                                        20，主载波FIFO输出，低12bit为数据；
                                                        21，辅载波FIFO输出，低12bit为数据；
                                                        default为去谐波的输入信号。
                                                        搬运数据格式：[11:0]为数据；[12]为0表示主载波，为1表示辅载波；[13]为0表示天线1，为1表示天线2。 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  : 保留 */
        unsigned int  at1_dbg_en   : 1;  /* bit[8]    : 主天线采数使能，高电平有效。 */
        unsigned int  at2_dbg_en   : 1;  /* bit[9]    : 辅天线采数使，高电平有效。 */
        unsigned int  reserved_1   : 22; /* bit[10-31]: 保留 */
    } reg;
} DBG_DBG_AGC_DATA_SEL_UNION;
#define DBG_DBG_AGC_DATA_SEL_dbg_data_sel_START  (0)
#define DBG_DBG_AGC_DATA_SEL_dbg_data_sel_END    (4)
#define DBG_DBG_AGC_DATA_SEL_at1_dbg_en_START    (8)
#define DBG_DBG_AGC_DATA_SEL_at1_dbg_en_END      (8)
#define DBG_DBG_AGC_DATA_SEL_at2_dbg_en_START    (9)
#define DBG_DBG_AGC_DATA_SEL_at2_dbg_en_END      (9)


/*****************************************************************************
 结构名    : DBG_DBG_DATA_SEL_UNION
 结构说明  : DBG_DATA_SEL 寄存器结构定义。地址偏移量:0xE199E814，初值:0x00000000，宽度:32
 寄存器说明: TX数采数据选择
*****************************************************************************/
typedef union
{
    unsigned int      dbg_data_sel_reg;
    struct
    {
        unsigned int  tds_dbg_data_sel : 3;  /* bit[0-2] : dbg数据选择：
                                                           3'd0: RRC数据输出；
                                                           3'd1: CFR/FIR数据输出；
                                                           3'd2: PC数据输出；
                                                           3'd3: phase comp数据输出
                                                           3'd4: Txiq数据输出
                                                           3'd5:FIFO数据输出
                                                           3'd6:sc_filter数据输出
                                                           3'd7:freq_error数据输出； */
        unsigned int  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} DBG_DBG_DATA_SEL_UNION;
#define DBG_DBG_DATA_SEL_tds_dbg_data_sel_START  (0)
#define DBG_DBG_DATA_SEL_tds_dbg_data_sel_END    (2)


/*****************************************************************************
 结构名    : DBG_DBG_EN_UNION
 结构说明  : DBG_EN 寄存器结构定义。地址偏移量:0x0708，初值:0x00000002，宽度:32
 寄存器说明: 使能寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_en_reg;
    struct
    {
        unsigned int  dbg_en       : 1;  /* bit[0]    : 可维可测使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
                                                        1'b0：可维可测功能不使能1'b1：可维可测功能使能 */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                        'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
                                                        'b1：只要dbg_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved     : 14; /* bit[2-15] : 保留 */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: 可维可测的包个数 */
    } reg;
} DBG_DBG_EN_UNION;
#define DBG_DBG_EN_dbg_en_START        (0)
#define DBG_DBG_EN_dbg_en_END          (0)
#define DBG_DBG_EN_dbg_rpt_mode_START  (1)
#define DBG_DBG_EN_dbg_rpt_mode_END    (1)
#define DBG_DBG_EN_dbg_pkg_num_START   (16)
#define DBG_DBG_EN_dbg_pkg_num_END     (31)


/*****************************************************************************
 结构名    : DBG_DBG_FLT_UNION
 结构说明  : DBG_FLT 寄存器结构定义。地址偏移量:0x0710，初值:0x00000000，宽度:32
 寄存器说明: 数据选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_flt_reg;
    struct
    {
        unsigned int  dbg_flt  : 16; /* bit[0-15] : 可维可测内部分组指示：
                                                    1：上报mipi数据
                                                    2：上报ssi数据
                                                    3：其它dbg上报数据
                                                    其它：保留 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} DBG_DBG_FLT_UNION;
#define DBG_DBG_FLT_dbg_flt_START   (0)
#define DBG_DBG_FLT_dbg_flt_END     (15)


/*****************************************************************************
 结构名    : DBG_DBG_MIPI_CH_MASK_UNION
 结构说明  : DBG_MIPI_CH_MASK 寄存器结构定义。地址偏移量:0x0714，初值:0x00000000，宽度:32
 寄存器说明: mipi通道选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_mipi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_mipi_ch_mask : 4;  /* bit[0-3] : 可维可测mipi采集数据通道屏蔽指示：
                                                           dbg_mipi_ch_mask[X],X=0~3,则：
                                                           0：通道X的mipi数据不采集
                                                           1：采集通道X的mipi数据 */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留 */
    } reg;
} DBG_DBG_MIPI_CH_MASK_UNION;
#define DBG_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_START  (0)
#define DBG_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_END    (3)


/*****************************************************************************
 结构名    : DBG_DBG_SSI_CH_MASK_UNION
 结构说明  : DBG_SSI_CH_MASK 寄存器结构定义。地址偏移量:0x0718，初值:0x00000000，宽度:32
 寄存器说明: ssi通道选择寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ssi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_ssi_ch_mask : 4;  /* bit[0-3] : 可维可测ssi采集数据通道屏蔽指示：
                                                          dbg_ssi_ch_mask[X],X=0~3,则：
                                                          0：通道X的ssi数据不采集
                                                          1：采集通道X的ssi数据 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留 */
    } reg;
} DBG_DBG_SSI_CH_MASK_UNION;
#define DBG_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_START  (0)
#define DBG_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_END    (3)


/*****************************************************************************
 结构名    : DBG_ch1_testmode_UNION
 结构说明  : ch1_testmode 寄存器结构定义。地址偏移量:0xE1FA0104，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned char      ch1_testmode_reg;
    struct
    {
        unsigned char  ch1_pwr_on_rst  : 1;  /* bit[0]  : 全局软复位信号：
                                                          0：不复位(默认)
                                                          1：复位整个数字电路和模拟电路 */
        unsigned char  ch1_rx_chnl_sel : 2;  /* bit[1-2]: RX模拟测试模式下通道选择：
                                                          00：输出RXA I模拟调制器数据(默认)
                                                          01：输出RXA Q模拟调制器数据
                                                          10：输出RXB I模拟调制器数据
                                                          11：输出RXB Q模拟调制器数据 */
        unsigned char  ch1_test_mode   : 3;  /* bit[3-5]: bit[4:3]测试模式控制：
                                                          00：正常模式(默认)
                                                          01：数字算法逻辑环回模式
                                                          10：RX模拟测试模式(bypass RX数字滤波器)
                                                          11：接口环回
                                                          bit[5]Reserved */
        unsigned char  ch1_rx_sw_rst   : 1;  /* bit[6]  : 数字部分RX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned char  ch1_tx_sw_rst   : 1;  /* bit[7]  : 数字部分TX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
    } reg;
} DBG_ch1_testmode_UNION;
#define DBG_ch1_testmode_ch1_pwr_on_rst_START   (0)
#define DBG_ch1_testmode_ch1_pwr_on_rst_END     (0)
#define DBG_ch1_testmode_ch1_rx_chnl_sel_START  (1)
#define DBG_ch1_testmode_ch1_rx_chnl_sel_END    (2)
#define DBG_ch1_testmode_ch1_test_mode_START    (3)
#define DBG_ch1_testmode_ch1_test_mode_END      (5)
#define DBG_ch1_testmode_ch1_rx_sw_rst_START    (6)
#define DBG_ch1_testmode_ch1_rx_sw_rst_END      (6)
#define DBG_ch1_testmode_ch1_tx_sw_rst_START    (7)
#define DBG_ch1_testmode_ch1_tx_sw_rst_END      (7)


/*****************************************************************************
 结构名    : DBG_ch0_testmode_UNION
 结构说明  : ch0_testmode 寄存器结构定义。地址偏移量:0xE1FA0284，初值:0x00，宽度:8
 寄存器说明: 测试模式寄存器。
*****************************************************************************/
typedef union
{
    unsigned char      ch0_testmode_reg;
    struct
    {
        unsigned char  ch0_pwr_on_rst  : 1;  /* bit[0]  : 全局软复位信号：
                                                          0：不复位(默认)
                                                          1：复位整个数字电路和模拟电路 */
        unsigned char  ch0_rx_chnl_sel : 2;  /* bit[1-2]: RX模拟测试模式下通道选择：
                                                          00：输出RXA I模拟调制器数据(默认)
                                                          01：输出RXA Q模拟调制器数据
                                                          10：输出RXB I模拟调制器数据
                                                          11：输出RXB Q模拟调制器数据 */
        unsigned char  ch0_test_mode   : 3;  /* bit[3-5]: bit[4:3]测试模式控制：
                                                          00：正常模式(默认)
                                                          01：数字算法逻辑环回模式
                                                          10：RX模拟测试模式(bypass RX数字滤波器)
                                                          11：接口环回
                                                          bit[5] debug_en：
                                                          1：使能，将debug信号通过管脚复用出去；
                                                          0：不使能。 */
        unsigned char  ch0_rx_sw_rst   : 1;  /* bit[6]  : 数字部分RX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
        unsigned char  ch0_tx_sw_rst   : 1;  /* bit[7]  : 数字部分TX通道软复位信号：
                                                          0：不复位(默认)
                                                          1：复位 */
    } reg;
} DBG_ch0_testmode_UNION;
#define DBG_ch0_testmode_ch0_pwr_on_rst_START   (0)
#define DBG_ch0_testmode_ch0_pwr_on_rst_END     (0)
#define DBG_ch0_testmode_ch0_rx_chnl_sel_START  (1)
#define DBG_ch0_testmode_ch0_rx_chnl_sel_END    (2)
#define DBG_ch0_testmode_ch0_test_mode_START    (3)
#define DBG_ch0_testmode_ch0_test_mode_END      (5)
#define DBG_ch0_testmode_ch0_rx_sw_rst_START    (6)
#define DBG_ch0_testmode_ch0_rx_sw_rst_END      (6)
#define DBG_ch0_testmode_ch0_tx_sw_rst_START    (7)
#define DBG_ch0_testmode_ch0_tx_sw_rst_END      (7)




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

#endif /* end of bbp_dbg_interface.h */
