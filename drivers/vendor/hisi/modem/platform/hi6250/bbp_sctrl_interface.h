

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_SCTRL_INTERFACE_H__
#define __BBP_SCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_BBP_SYSCTRL
 ***======================================================================***/
/* 寄存器说明：BBP电源控制使能(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域上电置位。
             写1置位，写0无效。
 bit[1]      WTC电源域上电置位。
             写1置位，写0无效。
 bit[0]      LTE电源域上电置位。
             写1置位，写0无效。
   UNION结构:  BBPSCTRL_BBP_MTCMOS_SET_UNION */
#define BBPSCTRL_BBP_MTCMOS_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x0)

/* 寄存器说明：BBP电源控制关闭(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域上电清除。
             写1清零，写0无效。
 bit[1]      WTC电源域上电清除。
             写1清零，写0无效。
 bit[0]      LTE电源域上电清除。
             写1清零，写0无效。
   UNION结构:  BBPSCTRL_BBP_MTCMOS_CLR_UNION */
#define BBPSCTRL_BBP_MTCMOS_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x4)

/* 寄存器说明：BBP电源控制状态(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域电源状态。
             1：上电
             0：下电
 bit[1]      WTC电源域电源状态。
             1：上电
             0：下电
 bit[0]      LTE电源域电源状态。
             1：上电
             0：下电
   UNION结构:  BBPSCTRL_BBP_MTCMOS_STATUS_UNION */
#define BBPSCTRL_BBP_MTCMOS_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x8)

/* 寄存器说明：BBP电源隔离控制使能(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域隔离置位。
             写1置位，写0无效。
 bit[1]      WTC电源域隔离置位。
             写1置位，写0无效。
 bit[0]      LTE电源域隔离置位。
             写1置位，写0无效。
   UNION结构:  BBPSCTRL_BBP_ISO_EN_SET_UNION */
#define BBPSCTRL_BBP_ISO_EN_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x10)

/* 寄存器说明：BBP电源隔离控制关闭(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域隔离清除。
             写1清零，写0无效。
 bit[1]      WTC电源域隔离清除。
             写1清零，写0无效。
 bit[0]      LTE电源域隔离清除。
             写1清零，写0无效。
   UNION结构:  BBPSCTRL_BBP_ISO_EN_CLR_UNION */
#define BBPSCTRL_BBP_ISO_EN_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x14)

/* 寄存器说明：BBP电源隔离控制状态(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域隔离状态。
             1：隔离；
             0：解除隔离；
 bit[1]      WTC电源域隔离状态。
             1：隔离；
             0：解除隔离；
 bit[0]      LTE电源域隔离状态。
             1：隔离；
             0：解除隔离；
   UNION结构:  BBPSCTRL_BBP_ISO_EN_STATUS_UNION */
#define BBPSCTRL_BBP_ISO_EN_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x18)

/* 寄存器说明：BBP电源域时钟使能(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域时钟使能。
             写1置位，写0无效。
 bit[1]      WTC电源域时钟使能。
             写1置位，写0无效。
 bit[0]      LTE电源域时钟使能。
             写1置位，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_CLK_SET_UNION */
#define BBPSCTRL_BBP_PD_CLK_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x20)

/* 寄存器说明：BBP电源域时钟关闭(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域时钟关闭。
             写1关闭，写0无效。
 bit[1]      WTC电源域时钟关闭。
             写1关闭，写0无效。
 bit[0]      LTE电源域时钟关闭。
             写1关闭，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_CLK_CLR_UNION */
#define BBPSCTRL_BBP_PD_CLK_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x24)

/* 寄存器说明：BBP电源域时钟门控状态(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域时钟状态。
             1：时钟使能
             0：时钟关闭
 bit[1]      WTC电源域时钟状态。
             1：时钟使能
             0：时钟关闭
 bit[0]      LTE电源域时钟状态。
             1：时钟使能
             0：时钟关闭
   UNION结构:  BBPSCTRL_BBP_PD_CLK_STATUS_UNION */
#define BBPSCTRL_BBP_PD_CLK_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x28)

/* 寄存器说明：BBP电源域复位请求使能(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域复位请求。
             写1复位，写0无效。
 bit[1]      WTC电源域复位请求。
             写1复位，写0无效。
 bit[0]      LTE电源域复位请求。
             写1复位，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_SRST_SET_UNION */
#define BBPSCTRL_BBP_PD_SRST_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x30)

/* 寄存器说明：BBP电源域复位请求关闭(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域复位清除。
             写1解除复位，写0无效。
 bit[1]      WTC电源域复位清除。
             写1解除复位，写0无效。
 bit[0]      LTE电源域复位清除。
             写1解除复位，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_SRST_CLR_UNION */
#define BBPSCTRL_BBP_PD_SRST_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x34)

/* 寄存器说明：BBP电源域复位请求状态(C核)
 bit[31:3]   保留。
 bit[2]      IRM电源域复位状态。
             1：复位；
             0：解除复位；
 bit[1]      WTC电源域复位状态。
             1：复位；
             0：解除复位；
 bit[0]      LTE电源域复位状态。
             1：复位；
             0：解除复位；
   UNION结构:  BBPSCTRL_BBP_PD_SRST_STATUS_UNION */
#define BBPSCTRL_BBP_PD_SRST_STATUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x38)

/* 寄存器说明：BBP电源域各频率时钟使能(lte/wtc/irm)
 bit[31:27]  保留。Debug使用。
 bit[26]     
 bit[25]     
 bit[24]     
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      BLV7R5版本：这信号同时控制LTE PD和IRM PD。
             DALLAS版本：这信号在LTE PD取消不再使用，只作用于IRM PD
 bit[8]      BLV7R5版本：这信号同时控制LTE PD和IRM PD。
             DALLAS版本：这信号在LTE PD取消不再使用，只作用于IRM PD
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_CLK0_SET_UNION */
#define BBPSCTRL_BBP_CLK0_SET_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x40)

/* 寄存器说明：BBP电源域各频率时钟关闭(lte/wtc/irm)
 bit[31:27]  保留。Debug使用。
 bit[26]     
 bit[25]     
 bit[24]     
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      BLV7R5版本：这信号同时控制LTE PD和IRM PD。
             DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效
 bit[8]      BLV7R5版本：这信号同时控制LTE PD和IRM PD。
             DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_CLK0_CLR_UNION */
#define BBPSCTRL_BBP_CLK0_CLR_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x44)

/* 寄存器说明：BBP电源域各频率时钟门控状态(lte/wtc/irm)
 bit[31:27]  保留。Debug使用。
 bit[26]     
 bit[25]     
 bit[24]     
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      BLV7R5版本：这信号同时控制LTE PD和IRM PD。
             DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效
 bit[8]      BLV7R5版本：这信号同时控制LTE PD和IRM PD。
             DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_CLK0_STATUS_UNION */
#define BBPSCTRL_BBP_CLK0_STATUS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x48)

/* 寄存器说明：BBP电源域各频率时钟使能(com)
 bit[31:15]  保留。Debug使用。
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_CLK1_SET_UNION */
#define BBPSCTRL_BBP_CLK1_SET_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x50)

/* 寄存器说明：BBP电源域各频率时钟关闭(com)
 bit[31:15]  保留。Debug使用。
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_CLK1_CLR_UNION */
#define BBPSCTRL_BBP_CLK1_CLR_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x54)

/* 寄存器说明：BBP电源域各频率时钟门控状态(com)
 bit[31:15]  保留。Debug使用。
 bit[14]     
 bit[13]     C2
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      PDF
 bit[6]      ULHB
 bit[5]      PDT
 bit[4]      TDS
 bit[3]      WTC
 bit[2]      G
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_CLK1_STATUS_UNION */
#define BBPSCTRL_BBP_CLK1_STATUS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x58)

/* 寄存器说明：BBP系统控制器6置位(UC2_CLK_EN)
 bit[31:7]   保留。
 bit[6]      UC2的TCXO时钟使能
             写1置位，写0无效。
 bit[5]      UC2的WC模共享245M时钟使能
             写1置位，写0无效。
 bit[4]      UC2的WC模共享122M时钟使能
             写1置位，写0无效。
 bit[3]      UC2的WC模共享122M时钟使能
             写1置位，写0无效。
 bit[2]      UC2的C模122M时钟使能
             写1置位，写0无效。
 bit[1]      UC2的W模122M时钟使能，dallas不需要使能
             写1置位，写0无效。
 bit[0]      UC2的W模61M时钟使能，dallas不需要使能
             写1置位，写0无效。
   UNION结构:  BBPSCTRL_BBP_SCTRL6_SET_UNION */
#define BBPSCTRL_BBP_SCTRL6_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x60)

/* 寄存器说明：BBP系统控制器6清零(UC2_CLK_DIS)
 bit[31:7]   保留。
 bit[6]      UC2的TCXO时钟关闭
             写1关闭，写0无效。
 bit[5]      UC2的WC模共享245M时钟关闭
             写1关闭，写0无效。
 bit[4]      UC2的WC模共享122M时钟关闭
             写1关闭，写0无效。
 bit[3]      UC2的WC模共享122M时钟关闭
             写1关闭，写0无效。
 bit[2]      UC2的C模122M时钟关闭
             写1关闭，写0无效。
 bit[1]      UC2的W模122M时钟关闭
             写1关闭，写0无效。
 bit[0]      UC2的W模61M时钟关闭
             写1关闭，写0无效。
   UNION结构:  BBPSCTRL_BBP_SCTRL6_CLR_UNION */
#define BBPSCTRL_BBP_SCTRL6_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x64)

/* 寄存器说明：BBP系统控制器6状态(UC2_CLK_STATUS)
 bit[31:7]   保留。
 bit[6]      UC2的TCXO时钟状态
             1：时钟使能
             0：时钟关闭
 bit[5]      UC2的WC模共享245M时钟状态
             1：时钟使能
             0：时钟关闭
 bit[4]      UC2的WC模共享122M时钟状态
             1：时钟使能
             0：时钟关闭
 bit[3]      UC2的WC模共享122M时钟状态
             1：时钟使能
             0：时钟关闭
 bit[2]      UC2的C模122M时钟状态
             1：时钟使能
             0：时钟关闭
 bit[1]      UC2的W模122M时钟状态
             1：时钟使能
             0：时钟关闭
 bit[0]      UC2的W模61M时钟状态
             1：时钟使能
             0：时钟关闭
   UNION结构:  BBPSCTRL_BBP_SCTRL6_STSTUS_UNION */
#define BBPSCTRL_BBP_SCTRL6_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x68)

/* 寄存器说明：BBP系统控制器7置位(UC2_RST_REQ)
 bit[31:8]   保留。
 bit[7]      UC2的32K复位请求。
             写1复位，写0无效。
 bit[6]      UC2的TCXO复位请求。
             写1复位，写0无效。
 bit[5]      UC2的WC模共享245M复位请求。
             写1复位，写0无效。
 bit[4]      UC2的WC模共享122M复位请求。
             写1复位，写0无效。
 bit[3]      UC2的WC模共享122M复位请求。
             写1复位，写0无效。
 bit[2]      UC2的C模122M复位请求。
             写1复位，写0无效。
 bit[1]      UC2的W模122M复位请求。
             写1复位，写0无效。
 bit[0]      UC2的W模61M复位请求。
             写1复位，写0无效。
   UNION结构:  BBPSCTRL_BBP_SCTRL7_SET_UNION */
#define BBPSCTRL_BBP_SCTRL7_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x70)

/* 寄存器说明：BBP系统控制器7清零(UC2_RST_CLR)
 bit[31:8]   保留。
 bit[7]      UC2的32K复位清除。
             写1解除复位，写0无效。
 bit[6]      UC2的TCXO复位清除。
             写1解除复位，写0无效。
 bit[5]      UC2的WC模共享245M复位清除。
             写1解除复位，写0无效。
 bit[4]      UC2的WC模共享122M复位清除。
             写1解除复位，写0无效。
 bit[3]      UC2的WC模共享122M复位清除。
             写1解除复位，写0无效。
 bit[2]      UC2的C模122M复位清除。
             写1解除复位，写0无效。
 bit[1]      UC2的W模122M复位清除。
             写1解除复位，写0无效。
 bit[0]      UC2的W模61M复位清除。
             写1解除复位，写0无效。
   UNION结构:  BBPSCTRL_BBP_SCTRL7_CLR_UNION */
#define BBPSCTRL_BBP_SCTRL7_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x74)

/* 寄存器说明：BBP系统控制器7状态(UC2_RST_STATUS)
 bit[31:8]   保留。
 bit[7]      UC2的32K复位状态。
             1：复位；
             0：解除复位；
 bit[6]      UC2的TCXO复位状态。
             1：复位；
             0：解除复位；
 bit[5]      UC2的WC模共享245M复位状态。
             1：复位；
             0：解除复位；
 bit[4]      UC2的WC模共享122M复位状态。
             1：复位；
             0：解除复位；
 bit[3]      UC2的WC模共享122M复位状态。
             1：复位；
             0：解除复位；
 bit[2]      UC2的C模122M复位状态。
             1：复位；
             0：解除复位；
 bit[1]      UC2的W模122M复位状态。
             1：复位；
             0：解除复位；
 bit[0]      UC2的W模61M复位状态。
             1：复位；
             0：解除复位；
   UNION结构:  BBPSCTRL_BBP_SCTRL7_STSTUS_UNION */
#define BBPSCTRL_BBP_SCTRL7_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x78)

/* 寄存器说明：LTE电源域时钟使能
 bit[31:24]  保留。
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     保留。不使用。
 bit[18]     保留。不使用。
 bit[17]     保留。不使用。
 bit[16]     保留。不使用。
 bit[15]     保留。不使用。
 bit[14]     保留。不使用。
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      保留。不使用。
 bit[1]      保留。不使用。
 bit[0]      保留。不使用。
   UNION结构:  BBPSCTRL_LTE_PD_CLK_EN_UNION */
#define BBPSCTRL_LTE_PD_CLK_EN_ADDR                   (SOC_BBP_SCTRL_BASE_ADDR + 0x80)

/* 寄存器说明：LTE电源域时钟关闭
 bit[31:24]  保留。
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_LTE_PD_CLK_DIS_UNION */
#define BBPSCTRL_LTE_PD_CLK_DIS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x84)

/* 寄存器说明：LTE电源域时钟门控状态
 bit[31:24]  保留。
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_LTE_PD_CLK_STSTUS_UNION */
#define BBPSCTRL_LTE_PD_CLK_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x88)

/* 寄存器说明：LTE电源域复位请求使能
 bit[31:24]  保留。
 bit[23]     
 bit[22]     
 bit[21:14]  
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_LTE_PD_SRST_REQ_UNION */
#define BBPSCTRL_LTE_PD_SRST_REQ_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x90)

/* 寄存器说明：LTE电源域复位请求清除
 bit[31:24]  保留。
 bit[23]     
 bit[22]     
 bit[21:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_LTE_PD_SRST_DIS_UNION */
#define BBPSCTRL_LTE_PD_SRST_DIS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x94)

/* 寄存器说明：LTE电源域复位请求状态
 bit[31:24]  保留。
 bit[23]     
 bit[22]     
 bit[21:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_LTE_PD_SRST_STSTUS_UNION */
#define BBPSCTRL_LTE_PD_SRST_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x98)

/* 寄存器说明：WTC电源域时钟使能
 bit[31:15]  保留。
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_WTC_PD_CLK_EN_UNION */
#define BBPSCTRL_WTC_PD_CLK_EN_ADDR                   (SOC_BBP_SCTRL_BASE_ADDR + 0xA0)

/* 寄存器说明：WTC电源域时钟关闭
 bit[31:15]  保留。
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_WTC_PD_CLK_DIS_UNION */
#define BBPSCTRL_WTC_PD_CLK_DIS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0xA4)

/* 寄存器说明：WTC电源域时钟门控状态
 bit[31:15]  保留。
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_WTC_PD_CLK_STSTUS_UNION */
#define BBPSCTRL_WTC_PD_CLK_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0xA8)

/* 寄存器说明：WTC电源域复位请求使能
 bit[31:16]  保留。
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_WTC_PD_SRST_REQ_UNION */
#define BBPSCTRL_WTC_PD_SRST_REQ_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xB0)

/* 寄存器说明：WTC电源域复位请求清除
 bit[31:16]  保留。
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_WTC_PD_SRST_DIS_UNION */
#define BBPSCTRL_WTC_PD_SRST_DIS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xB4)

/* 寄存器说明：WTC电源域复位请求状态
 bit[31:16]  保留。
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_WTC_PD_SRST_STATUS_UNION */
#define BBPSCTRL_WTC_PD_SRST_STATUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0xB8)

/* 寄存器说明：IRM电源域时钟使能
 bit[31:11]  保留。
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_IRM_PD_CLK_EN_UNION */
#define BBPSCTRL_IRM_PD_CLK_EN_ADDR                   (SOC_BBP_SCTRL_BASE_ADDR + 0xC0)

/* 寄存器说明：IRM电源域时钟关闭
 bit[31:11]  保留。
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_IRM_PD_CLK_DIS_UNION */
#define BBPSCTRL_IRM_PD_CLK_DIS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0xC4)

/* 寄存器说明：IRM电源域时钟门控状态
 bit[31:11]  保留。
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_IRM_PD_CLK_STATUS_UNION */
#define BBPSCTRL_IRM_PD_CLK_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0xC8)

/* 寄存器说明：IRM电源域复位请求使能
 bit[31:11]  保留。
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_IRM_PD_SRST_REQ_UNION */
#define BBPSCTRL_IRM_PD_SRST_REQ_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xD0)

/* 寄存器说明：IRM电源域复位请求清除
 bit[31:11]  保留。
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_IRM_PD_SRST_DIS_UNION */
#define BBPSCTRL_IRM_PD_SRST_DIS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xD4)

/* 寄存器说明：IRM电源域复位请求状态
 bit[31:11]  保留。
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_IRM_PD_SRST_STATUS_UNION */
#define BBPSCTRL_IRM_PD_SRST_STATUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0xD8)

/* 寄存器说明：COM时钟使能
 bit[31:27]  保留。
 bit[26]     BBP_COMM_FE中，C模式时钟使能
 bit[25]     BBP_COMM_FE中，T模式时钟使能
 bit[24]     BBP_COMM_FE中，W模式时钟使能。
 bit[23]     GUC DBG时钟使能。
 bit[22]     BBP_COMM_FE中mipi时钟使能。该时钟来自19.2M或者245.76M，选择信号见bbp_clk_ctrl。
 bit[21]     自研ET，W时钟使能
 bit[20]     自研ET，L时钟使能
 bit[19]     自研ET总线时钟使能
 bit[18]     C2模式tx时钟使能。该信号需要同时打开C_SYS_CLK_EN。
 bit[17]     T模式tx时钟使能。该信号需要同时打开T_SYS_CLK_EN。
 bit[16]     W模式tx时钟使能。该信号需要同时打开W_SYS_CLK_EN。
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     该位没有时钟使能。
 bit[11]     该位没有时钟使能。
 bit[10]     
 bit[9]      
 bit[8]      该位没有时钟使能。
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      l sdr模块时钟打开。
             注意，在tl_dbg_clk_en的时候，同样会打开l sdr模块的时钟。
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_COM_CLK_EN_UNION */
#define BBPSCTRL_COM_CLK_EN_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0xE0)

/* 寄存器说明：COM时钟关闭
 bit[31:27]  保留。
 bit[26]     BBP_COMM_FE中，C模式时钟关闭
 bit[25]     BBP_COMM_FE中，T模式时钟关闭
 bit[24]     BBP_COMM_FE中，W模式时钟关闭
 bit[23]     GUC DBG时钟关闭
 bit[22]     BBP_COMM_FE中mipi时钟关闭
 bit[21]     自研ET，W时钟关闭
 bit[20]     自研ET，L时钟关闭
 bit[19]     自研ET总线时钟关闭
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     该位没有时钟使能。
 bit[11]     该位没有时钟使能。
 bit[10]     
 bit[9]      
 bit[8]      该位没有时钟使能。
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_COM_CLK_DIS_UNION */
#define BBPSCTRL_COM_CLK_DIS_ADDR                     (SOC_BBP_SCTRL_BASE_ADDR + 0xE4)

/* 寄存器说明：COM时钟门控状态
 bit[31:27]  保留。
 bit[26]     BBP_COMM_FE中，C模式时钟状态
 bit[25]     BBP_COMM_FE中，T模式时钟状态
 bit[24]     BBP_COMM_FE中，W模式时钟状态
 bit[23]     GUC DBG时钟状态
 bit[22]     BBP_COMM_FE中mipi时钟状态
 bit[21]     自研ET，W时钟状态
 bit[20]     自研ET，L时钟状态
 bit[19]     自研ET总线时钟状态
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     个组合的时钟状态。0xE0/0xE4对应bit位，无时钟使能
 bit[11]     个组合的时钟状态。0xE0/0xE4对应bit位，无时钟使能
 bit[10]     
 bit[9]      
 bit[8]      个组合的时钟状态。0xE0/0xE4对应bit位，无时钟使能
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_COM_CLK_STATUS_UNION */
#define BBPSCTRL_COM_CLK_STATUS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0xE8)

/* 寄存器说明：COM复位请求使能
 bit[31:27]  保留。
 bit[26]     BBP_COMM_FE中，C模式复位请求
 bit[25]     BBP_COMM_FE中，T模式复位请求
 bit[24]     BBP_COMM_FE中，W模式复位请求
 bit[23]     GUC DBG复位请求
 bit[22]     BBP_COMM_FE中mipi时钟域复位，高有效。
 bit[21:20]  保留
 bit[19]     自研ET总线复位
 bit[18:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_COM_SRST_REQ_UNION */
#define BBPSCTRL_COM_SRST_REQ_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0xF0)

/* 寄存器说明：COM复位请求清除
 bit[31:27]  保留。
 bit[26]     BBP_COMM_FE中，C模式复位解除
 bit[25]     BBP_COMM_FE中，T模式复位解除
 bit[24]     BBP_COMM_FE中，W模式复位解除
 bit[23]     GUC DBG复位解除
 bit[22]     BBP_COMM_FE中mipi时钟域解复位。写1清零。
 bit[21:20]  保留
 bit[19]     自研ET总线复位关闭
 bit[18:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_COM_SRST_DIS_UNION */
#define BBPSCTRL_COM_SRST_DIS_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0xF4)

/* 寄存器说明：COM复位请求状态
 bit[31:27]  保留。
 bit[26]     BBP_COMM_FE中，C模式复位状态
 bit[25]     BBP_COMM_FE中，T模式复位状态
 bit[24]     BBP_COMM_FE中，W模式复位状态
 bit[23]     GUC DBG复位状态
 bit[22]     BBP_COMM_FE中mipi时钟域复位状态。高复位，低解复位。
 bit[21:20]  保留
 bit[19]     自研ET总线复位状态
 bit[18:16]  保留
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_COM_SRST_STATUS_UNION */
#define BBPSCTRL_COM_SRST_STATUS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xF8)

/* 寄存器说明：BBP电源控制使能(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域上电置位。
             写1置位，写0无效。
 bit[1]      WTC电源域上电置位。
             写1置位，写0无效。
 bit[0]      LTE电源域上电置位。
             写1置位，写0无效。
   UNION结构:  BBPSCTRL_BBP_MTCMOS_SET_DSP_UNION */
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x100)

/* 寄存器说明：BBP电源控制关闭(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域上电清除。
             写1清零，写0无效。
 bit[1]      WTC电源域上电清除。
             写1清零，写0无效。
 bit[0]      LTE电源域上电清除。
             写1清零，写0无效。
   UNION结构:  BBPSCTRL_BBP_MTCMOS_CLR_DSP_UNION */
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x104)

/* 寄存器说明：BBP电源控制状态(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域电源状态。
             1：上电
             0：下电
 bit[1]      WTC电源域电源状态。
             1：上电
             0：下电
 bit[0]      LTE电源域电源状态。
             1：上电
             0：下电
   UNION结构:  BBPSCTRL_BBP_MTCMOS_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_ADDR           (SOC_BBP_SCTRL_BASE_ADDR + 0x108)

/* 寄存器说明：BBP电源隔离控制使能(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域隔离置位。
             写1置位，写0无效。
 bit[1]      WTC电源域隔离置位。
             写1置位，写0无效。
 bit[0]      LTE电源域隔离置位。
             写1置位，写0无效。
   UNION结构:  BBPSCTRL_BBP_ISO_EN_SET_DSP_UNION */
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x110)

/* 寄存器说明：BBP电源隔离控制关闭(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域隔离清除。
             写1清零，写0无效。
 bit[1]      WTC电源域隔离清除。
             写1清零，写0无效。
 bit[0]      LTE电源域隔离清除。
             写1清零，写0无效。
   UNION结构:  BBPSCTRL_BBP_ISO_EN_CLR_DSP_UNION */
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x114)

/* 寄存器说明：BBP电源隔离控制状态(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域隔离状态。
             1：隔离；
             0：解除隔离；
 bit[1]      WTC电源域隔离状态。
             1：隔离；
             0：解除隔离；
 bit[0]      LTE电源域隔离状态。
             1：隔离；
             0：解除隔离；
   UNION结构:  BBPSCTRL_BBP_ISO_EN_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_ADDR           (SOC_BBP_SCTRL_BASE_ADDR + 0x118)

/* 寄存器说明：BBP电源域时钟使能(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域时钟使能。
             写1置位，写0无效。
 bit[1]      WTC电源域时钟使能。
             写1置位，写0无效。
 bit[0]      LTE电源域时钟使能。
             写1置位，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_CLK_SET_DSP_UNION */
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x120)

/* 寄存器说明：BBP电源域时钟关闭(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域时钟关闭。
             写1关闭，写0无效。
 bit[1]      WTC电源域时钟关闭。
             写1关闭，写0无效。
 bit[0]      LTE电源域时钟关闭。
             写1关闭，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_CLK_CLR_DSP_UNION */
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x124)

/* 寄存器说明：BBP电源域时钟门控状态(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域时钟状态。
             1：时钟使能
             0：时钟关闭
 bit[1]      WTC电源域时钟状态。
             1：时钟使能
             0：时钟关闭
 bit[0]      LTE电源域时钟状态。
             1：时钟使能
             0：时钟关闭
   UNION结构:  BBPSCTRL_BBP_PD_CLK_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_ADDR           (SOC_BBP_SCTRL_BASE_ADDR + 0x128)

/* 寄存器说明：BBP电源域复位请求使能(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域复位请求。
             写1复位，写0无效。
 bit[1]      WTC电源域复位请求。
             写1复位，写0无效。
 bit[0]      LTE电源域复位请求。
             写1复位，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_SRST_SET_DSP_UNION */
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_ADDR             (SOC_BBP_SCTRL_BASE_ADDR + 0x130)

/* 寄存器说明：BBP电源域复位请求关闭(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域复位清除。
             写1解除复位，写0无效。
 bit[1]      WTC电源域复位清除。
             写1解除复位，写0无效。
 bit[0]      LTE电源域复位清除。
             写1解除复位，写0无效。
   UNION结构:  BBPSCTRL_BBP_PD_SRST_CLR_DSP_UNION */
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_ADDR             (SOC_BBP_SCTRL_BASE_ADDR + 0x134)

/* 寄存器说明：BBP电源域复位请求状态(DSP核)
 bit[31:3]   保留。
 bit[2]      IRM电源域复位状态。
             1：复位；
             0：解除复位；
 bit[1]      WTC电源域复位状态。
             1：复位；
             0：解除复位；
 bit[0]      LTE电源域复位状态。
             1：复位；
             0：解除复位；
   UNION结构:  BBPSCTRL_BBP_PD_SRST_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_ADDR          (SOC_BBP_SCTRL_BASE_ADDR + 0x138)

/* 寄存器说明：BBP系统控制器14置位
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL14_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x140)

/* 寄存器说明：BBP系统控制器14清零
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL14_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x144)

/* 寄存器说明：BBP系统控制器14状态
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL14_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x148)

/* 寄存器说明：BBP系统控制器15置位
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL15_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x150)

/* 寄存器说明：BBP系统控制器15清零
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL15_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x154)

/* 寄存器说明：BBP系统控制器15状态
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL15_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x158)

/* 寄存器说明：BBP系统控制器16置位
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL16_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x160)

/* 寄存器说明：BBP系统控制器16清零
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL16_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x164)

/* 寄存器说明：BBP系统控制器16状态
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL16_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x168)

/* 寄存器说明：BBP系统控制器17置位
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL17_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x170)

/* 寄存器说明：BBP系统控制器17清零
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL17_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x174)

/* 寄存器说明：BBP系统控制器17状态
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL17_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x178)

/* 寄存器说明：BBP系统控制器18置位
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL18_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x180)

/* 寄存器说明：BBP系统控制器18清零
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL18_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x184)

/* 寄存器说明：BBP系统控制器18状态
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL18_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x188)

/* 寄存器说明：BBP系统控制器19置位
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL19_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x190)

/* 寄存器说明：BBP系统控制器19清零
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL19_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x194)

/* 寄存器说明：BBP系统控制器19状态
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL19_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x198)

/* 寄存器说明：BBP系统控制器1A置位（UC2 CLK FORCE ENA）
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1a_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1A0)

/* 寄存器说明：BBP系统控制器1A清零
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1a_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1A4)

/* 寄存器说明：BBP系统控制器1A状态
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1a_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1A8)

/* 寄存器说明：BBP系统控制器1B置位(LTE PD CLK FORCE ENA)
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1b_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1B0)

/* 寄存器说明：BBP系统控制器1B清零
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1b_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1B4)

/* 寄存器说明：BBP系统控制器1B状态
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1b_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1B8)

/* 寄存器说明：BBP系统控制器1C置位(WTC PD CLK FORCE ENA)
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1c_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1C0)

/* 寄存器说明：BBP系统控制器1C清零
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1c_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1C4)

/* 寄存器说明：BBP系统控制器1C状态
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1c_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1C8)

/* 寄存器说明：BBP系统控制器1D置位(IRM PD CLK FORCE ENA)
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1d_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1D0)

/* 寄存器说明：BBP系统控制器1D清零
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1d_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1D4)

/* 寄存器说明：BBP系统控制器1D状态
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1d_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1D8)

/* 寄存器说明：BBP系统控制器1E置位(COM CLK FORCE ENA)
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1e_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1E0)

/* 寄存器说明：BBP系统控制器1E清零
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1e_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1E4)

/* 寄存器说明：BBP系统控制器1E状态
   详      述：保留。Debug使用。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1e_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1E8)

/* 寄存器说明：BBP系统控制器1F置位(PD PWR AND PD CLK FORCE ENA)
 bit[31:15]  保留。Debug使用。
 bit[14]     写1，强制解复位。
 bit[13]     写1，强制解复位。
 bit[12]     写1，强制解复位。
 bit[11]     
 bit[10]     写1，强制开钟。
 bit[9]      写1，强制开钟。
 bit[8]      写1，强制开钟。
 bit[7]      
 bit[6]      写1，强制解隔离。
 bit[5]      写1，强制解隔离。
 bit[4]      写1，强制解隔离。
 bit[3]      
 bit[2]      写1，强制上电。
 bit[1]      写1，强制上电。
 bit[0]      写1，强制上电。
   UNION结构:  BBPSCTRL_BBP_SCTRL1f_SET_UNION */
#define BBPSCTRL_BBP_SCTRL1f_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1F0)

/* 寄存器说明：BBP系统控制器1F清零（解除force)
   详      述：保留。Debug使用。Bit含义与0x1F0对应
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1f_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1F4)

/* 寄存器说明：BBP系统控制器1F状态(force状态)
   详      述：保留。Debug使用。Bit含义与0x1F0对应
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTRL1f_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1F8)

/* 寄存器说明：LBUS防挂死配置
 bit[31:27]  保留。
 bit[26:25]  
 bit[24]     
 bit[23]     
 bit[22:21]  
 bit[20]     
 bit[19]     
 bit[18:17]  
 bit[16]     
 bit[15]     
 bit[14:13]  
 bit[12]     
 bit[11]     
 bit[10:9]   
 bit[8]      
 bit[7]      
 bit[6:5]    
 bit[4]      
 bit[3]      
 bit[2:1]    
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_SCTR20_UNION */
#define BBPSCTRL_BBP_SCTR20_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x200)

/* 寄存器说明：BBP系统控制器21(dw_axi_bbp 配置)
 bit[31:14]  保留。
 bit[13]     
 bit[12:11]  
 bit[10:9]   
 bit[8:7]    
 bit[6:5]    
 bit[4:3]    
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_SCTR21_UNION */
#define BBPSCTRL_BBP_SCTR21_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x204)

/* 寄存器说明：BBP系统控制器22(dw_axi_bbp dlock)
 bit[31:1]   保留。
 bit[0]      寄存器23对应的dlock参数update
   UNION结构:  BBPSCTRL_BBP_SCTR22_UNION */
#define BBPSCTRL_BBP_SCTR22_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x208)

/* 寄存器说明：BBP系统控制器23(dw_axi_bbp_dlock)
 bit[31:16]  调试使用。
 bit[15:8]   保留
 bit[7:0]    调试使用。
   UNION结构:  BBPSCTRL_BBP_SCTR23_UNION */
#define BBPSCTRL_BBP_SCTR23_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x20C)

/* 寄存器说明：BBP系统控制器24(LBUS总线防挂死中断屏蔽)
 bit[31]     保留。
 bit[30]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[29]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[28]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[27]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[26]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[25]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[24]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[23]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[22]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[21]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[20]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[19]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[18]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[17]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[16]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[15]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[14]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[13]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[12]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[11]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[10]     0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[9]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[8]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[7]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[6]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[5]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[4]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[3]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[2]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[1]      0：中断屏蔽无效。
             1：中断屏蔽使能。
 bit[0]      0：中断屏蔽无效。
             1：中断屏蔽使能。
   UNION结构:  BBPSCTRL_BBP_SCTR24_UNION */
#define BBPSCTRL_BBP_SCTR24_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x210)

/* 寄存器说明：BBP系统控制器25(reserved)
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTR25_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x214)

/* 寄存器说明：BBP系统控制器26(reserved)
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTR26_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x218)

/* 寄存器说明：BBP系统控制器27(reserved)
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTR27_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x21C)

/* 寄存器说明：BBP系统控制器28(reserved)
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTR28_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x220)

/* 寄存器说明：BBP系统控制器29(COM2LTE_TBD)
   详      述：COM给LTE的预留ECO接口信号。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTR29_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x224)

/* 寄存器说明：BBP系统控制器2A(BBP时钟选择)
 bit[31:22]  保留。
 bit[21]     0: 选择AP侧的低功耗控制信号(默认，下电、复位后均为该值)。
             1：选择BBP侧的低功耗控制信号。
             Modem使用IRM的时候，需要配置为1. 次
 bit[20]     tdl工作时钟频率120/240MHz还是240/480MHz选择信号,该bit为：
             0：使用本寄存器地址bit【11:10】的软件配置值来选择。（上电复位默认此方式）
             1：tdl逻辑端口选择信号。
 bit[19]     bbp tdl clk使能。该时钟所在电源域为IRM/LTE电源域。
 bit[18:14]  UART的分频参数。
 bit[13:12]  保留
 bit[11]     软值配置时钟频率场景下，ch1 tdl clk分频参数。
             1：ch1主时钟480/240MHz(默认);
             0：ch1主时钟240/120MHz
             注，该参数在本寄存器bit20为0时有效。
 bit[10]     软值配置时钟频率场景下，ch0 tdl clk分频参数。
             1：ch0主时钟480/240MHz(默认);
             0：ch0主时钟240/120MHz
             注，该参数在本寄存器bit20为0时有效。
 bit[9:8]    LTE tx1 clk选择。
             00：选择245M(1分频)
             01：选择122M(2分频）
             10：选择61.44M(4分频)
             11：选择30.72M(8分频)
 bit[7:6]    LTE tx0 clk选择。
             00：选择245M(1分频)
             01：选择122M(2分频）
             10：选择61.44M(4分频)
             11：选择30.72M(8分频)
 bit[5]      pdt clk选择。
             0：选择122M；
             1：选择245M；
 bit[4]      bbp clk选择。
             0：选择122M;
             1：选择245M；
 bit[3]      scpll_uc2_clk选择信号：
             0：表示选择bbppll_clk_sc0
             1：表示选择bbppll_clk_sc1
 bit[2]      scpll_clk选择信号：
             0：表示选择bbppll_clk_sc0
             1：表示选择bbppll_clk_sc1
 bit[1]      mipi时钟来源：
             0：选择 19.2MHz ，注BBP端口输入时钟；
             1：选择 40.96MHz，注BBP内部245MHz分频时钟；
 bit[0]      uart时钟选择。
             1：选择480MHz分频；
             0：选择245MHz分频；
   UNION结构:  BBPSCTRL_BBP_SCTR2A_UNION */
#define BBPSCTRL_BBP_SCTR2A_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x228)

/* 寄存器说明：BBP系统控制器2B(REV)
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTR2B_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x22C)

/* 寄存器说明：BBP系统控制器2C(REV)
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_SCTR2C_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x230)

/* 寄存器说明：BBP系统控制器2D(REV)
 bit[31:4]   保留。
 bit[3]      MST ERR状态中读写地址信息选择。
             0：选择读地址；
             1：选择写地址；
 bit[2]      MST ERR状态中读写地址信息选择。
             0：选择读地址；
             1：选择写地址；
 bit[1]      MST ERR状态中读写地址信息选择。
             0：选择读地址；
             1：选择写地址；
 bit[0]      MST ERR状态中读写地址信息选择。
             0：选择读地址；
             1：选择写地址；
   UNION结构:  BBPSCTRL_BBP_SCTR2D_UNION */
#define BBPSCTRL_BBP_SCTR2D_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x234)

/* 寄存器说明：BBP系统控制器2E（g模总线同步调试）
 bit[31:1]   保留。
 bit[0]      G_LBUS选择。保留，debug使用。
             0：从Arbiter后输出；
             1：从Arbiter前输出；
   UNION结构:  BBPSCTRL_BBP_SCTR2E_UNION */
#define BBPSCTRL_BBP_SCTR2E_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x238)

/* 寄存器说明：BBP系统控制器2F(模式选择)
 bit[31:10]  保留
 bit[9]      W ET选择（芯片版本不支持自研ET，所以该值不需要修改）
             0：第三方ET。
             1：自研ET。
 bit[8]      L ET选择（芯片版本不支持自研ET，所以该值不需要修改）。
             0：第三方ET。
             1：自研ET。
 bit[7]      保留
 bit[6:4]    UC2模式选择，one-hot编码。
             001：WCDMA模式；
             010：保留；
             100：CDMA模式；
             default：CDMA模式。
             其他值：无效，告警。
 bit[3]      保留
 bit[2:0]    WTC模式选择，one-hot编码。
             001：WCDMA模式；
             010：TDS-CDMA模式；
             100：CDMA模式；
             default：TDS_CDMA模式。
             其他值：无效，告警。
   UNION结构:  BBPSCTRL_BBP_SCTR2F_UNION */
#define BBPSCTRL_BBP_SCTR2F_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x23C)

/* 寄存器说明：BBP电源域状态寄存器（mtcmos rdy)
 bit[31:3]   保留。
 bit[2]      IRM电源域上电状态。
             1：上电；
             0：下电
 bit[1]      WTC电源域上电状态。
             1：上电；
             0：下电
 bit[0]      LTE电源域上电状态。
             1：上电；
             0：下电
   UNION结构:  BBPSCTRL_BBP_STAT00_UNION */
#define BBPSCTRL_BBP_STAT00_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x300)

/* 寄存器说明：irm电源域时钟状态(门控后,和0x00C0 IRM PD门控使能信号对应)
   详      述：保留。调试用观测
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT01_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x304)

/* 寄存器说明：lte电源域时钟状态(门控后,和0x0080 LTE PD门控使能信号对应)
   详      述：保留。 调试用观测
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT02_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x308)

/* 寄存器说明：com中时钟状态(门控后,和COM PD  0x00E0 门控使能信号对应)
   详      述：保留。调试用观测
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT03_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x30C)

/* 寄存器说明：BBP各频率时钟状态(LTE/WTC/IRM，与0x0040地址的clk_en对应，门控后)
   详      述：保留。 调试用观测
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT04_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x310)

/* 寄存器说明：BBP各频率时钟状态(COM，与0x0050地址的clk_en对应，门控后)
   详      述：保留。调试用观测
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT05_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x314)

/* 寄存器说明：BBP MST状态寄存器
 bit[31:8]   保留。
 bit[7:0]    bbp中dw_axi_mst的error信号
   UNION结构:  BBPSCTRL_BBP_STAT06_UNION */
#define BBPSCTRL_BBP_STAT06_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x318)

/* 寄存器说明：BBP MST M1读写错误地址寄存器
   详      述：Debug使用。
               需要根据0x234地址的bit0选择读或者写地址。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT07_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x31C)

/* 寄存器说明：BBP MST M2读写错误地址寄存器
   详      述：Debug使用。
               需要根据0x234地址的bit1选择读或者写地址。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT08_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x320)

/* 寄存器说明：BBP MST M3读写错误地址寄存器
   详      述：Debug使用。
               需要根据0x234地址的bit2选择读或者写地址。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT09_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x324)

/* 寄存器说明：BBP MST M4读写错误地址寄存器
   详      述：Debug使用。
               需要根据0x234地址的bit3选择读或者写地址。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT0A_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x328)

/* 寄存器说明：BBP MST DLOCK状态寄存器
 bit[31:12]  保留。
 bit[11]     DLOCK IRQ。
 bit[10]     DLOCK的读写操作。
 bit[9:4]    DLOCK ID。
 bit[3:2]    DLOCK SLV编号。
 bit[1:0]    DLOCK MST编号。
   UNION结构:  BBPSCTRL_BBP_STAT0B_UNION */
#define BBPSCTRL_BBP_STAT0B_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x32C)

/* 寄存器说明：BBP MST DLOCK地址寄存器
   详      述：保留。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT0C_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x330)

/* 寄存器说明：BBP状态寄存器0D(IRM2COM_TBD)
 bit[31:16]  保留。
 bit[15:0]   IRM给COM的预留eco信号。
   UNION结构:  BBPSCTRL_BBP_STAT0D_UNION */
#define BBPSCTRL_BBP_STAT0D_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x334)

/* 寄存器说明：BBP状态寄存器0E(LTE2COM_TBD)
   详      述：LTE给COM的预留ECO信号。
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT0E_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x338)

/* 寄存器说明：BBP状态寄存器0F(LBUS防挂死中断状态)
 bit[31]     0：正常
             1：超时
             正常，不会触发中断。
             其他，会触发中断。
             写该寄存器则对应bite清零。
 bit[30]     0：正常。
             1：超时。
 bit[29]     0：正常。
             1：超时。
 bit[28]     0：正常。
             1：超时。
 bit[27]     0：正常。
             1：超时。
 bit[26]     0：正常。
             1：复位。
 bit[25]     0：正常。
             1：时钟关闭。
 bit[24]     0：正常。
             1：电源关闭。
 bit[23]     0：正常。
             1：超时。
 bit[22]     0：正常。
             1：超时。
 bit[21]     0：正常。
             1：复位。
 bit[20]     0：正常。
             1：时钟关闭。
 bit[19]     0：正常。
             1：超时。
 bit[18]     0：正常。
             1：复位。
 bit[17]     0：正常。
             1：时钟关闭。
 bit[16]     0：正常。
             1：电源关闭。
 bit[15]     0：正常。
             1：超时。
 bit[14]     0：正常。
             1：复位。
 bit[13]     0：正常。
             1：时钟关闭。
 bit[12]     0：正常。
             1：电源关闭。
 bit[11]     0：正常。
             1：超时。
 bit[10]     0：正常。
             1：复位。
 bit[9]      0：正常。
             1：时钟关闭。
 bit[8]      0：正常。
             1：电源关闭。
 bit[7]      0：正常。
             1：超时。
 bit[6]      0：正常。
             1：复位。
 bit[5]      0：正常。
             1：时钟关闭。
 bit[4]      0：正常。
             1：电源关闭。
 bit[3]      0：正常。
             1：超时。
 bit[2]      0：正常。
             1：复位。
 bit[1]      0：正常。
             1：时钟关闭。
 bit[0]      0：正常。
             1：电源关闭。
   UNION结构:  BBPSCTRL_BBP_STAT0F_UNION */
#define BBPSCTRL_BBP_STAT0F_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x33C)

/* 寄存器说明：BBP状态寄存器10(COM中时钟状态，非clk_en对称)
 bit[31:21]  保留。
             这些都是COM_TOP中的时钟状态。
 bit[20]     0：无时钟
             1：有时钟
             WTC 122 LBUS时钟状态
 bit[19]     0：无时钟
             1：有时钟
 bit[18]     0：无时钟
             1：有时钟
 bit[17]     0：无时钟
             1：有时钟
             TDS 245 LBUS时钟状态
 bit[16]     0：无时钟
             1：有时钟
             没有使用。
 bit[15]     0：无时钟
             1：有时钟
 bit[14]     0：无时钟
             1：有时钟
             LTE ULHB LBUS时钟状态
 bit[13]     0：无时钟
             1：有时钟
             LTE PDT LBUS时钟状态。
 bit[12]     0：无时钟
             1：有时钟
             LTE PDF LBUS时钟状态。
 bit[11]     0：无时钟
             1：有时钟
 bit[10]     0：无时钟
             1：有时钟
 bit[9]      0：无时钟
             1：有时钟
             G模公共，G1和GSDR的公共逻辑的104M时钟状态。
 bit[8]      0：无时钟
             1：有时钟
             G模公共，即LBUS时钟状态。
 bit[7]      0：无时钟
             1：有时钟
             G模公共，19.2M时钟的状态
 bit[6]      0：无时钟
             1：有时钟
             G模公共，32K时钟的状态。
 bit[5]      0：无时钟
             1：有时钟
 bit[4]      0：无时钟
             1：有时钟
 bit[3]      保留
 bit[2]      保留
 bit[1]      保留
 bit[0]      保留
   UNION结构:  BBPSCTRL_BBP_STAT10_UNION */
#define BBPSCTRL_BBP_STAT10_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x340)

/* 寄存器说明：BBP状态寄存器11
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT11_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x344)

/* 寄存器说明：BBP状态寄存器12
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT12_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x348)

/* 寄存器说明：BBP状态寄存器13
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT13_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x34C)

/* 寄存器说明：BBP状态寄存器14
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT14_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x350)

/* 寄存器说明：BBP状态寄存器15
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT15_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x354)

/* 寄存器说明：BBP状态寄存器16
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT16_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x358)

/* 寄存器说明：BBP状态寄存器17
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT17_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x35C)

/* 寄存器说明：BBP状态寄存器18
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT18_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x360)

/* 寄存器说明：BBP状态寄存器19
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT19_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x364)

/* 寄存器说明：BBP状态寄存器1A
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT1A_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x368)

/* 寄存器说明：BBP状态寄存器1B
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT1B_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x36C)

/* 寄存器说明：BBP状态寄存器1C
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT1C_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x370)

/* 寄存器说明：BBP状态寄存器1D
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT1D_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x374)

/* 寄存器说明：BBP状态寄存器1E
   详      述：保留
   UNION结构 ：无 */
#define BBPSCTRL_BBP_STAT1E_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x378)

/* 寄存器说明：各电源域入口时钟的时钟状态，每个PD一个时钟使能，开启后每个PD的入口时钟全部打开。
 bit[31:17]  保留
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION结构:  BBPSCTRL_BBP_STAT1F_UNION */
#define BBPSCTRL_BBP_STAT1F_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x37C)





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
                     (1/1) register_define_BBP_SYSCTRL
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPSCTRL_BBP_MTCMOS_SET_UNION
 结构说明  : BBP_MTCMOS_SET 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: BBP电源控制使能(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_set_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_set : 1;  /* bit[0]   : LTE电源域上电置位。
                                                              写1置位，写0无效。 */
        unsigned int  wtc_mtcmos_ctrl_set : 1;  /* bit[1]   : WTC电源域上电置位。
                                                              写1置位，写0无效。 */
        unsigned int  irm_mtcmos_ctrl_set : 1;  /* bit[2]   : IRM电源域上电置位。
                                                              写1置位，写0无效。 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_MTCMOS_SET_UNION;
#define BBPSCTRL_BBP_MTCMOS_SET_lte_mtcmos_ctrl_set_START  (0)
#define BBPSCTRL_BBP_MTCMOS_SET_lte_mtcmos_ctrl_set_END    (0)
#define BBPSCTRL_BBP_MTCMOS_SET_wtc_mtcmos_ctrl_set_START  (1)
#define BBPSCTRL_BBP_MTCMOS_SET_wtc_mtcmos_ctrl_set_END    (1)
#define BBPSCTRL_BBP_MTCMOS_SET_irm_mtcmos_ctrl_set_START  (2)
#define BBPSCTRL_BBP_MTCMOS_SET_irm_mtcmos_ctrl_set_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_MTCMOS_CLR_UNION
 结构说明  : BBP_MTCMOS_CLR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: BBP电源控制关闭(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_clr_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_clr : 1;  /* bit[0]   : LTE电源域上电清除。
                                                              写1清零，写0无效。 */
        unsigned int  wtc_mtcmos_ctrl_clr : 1;  /* bit[1]   : WTC电源域上电清除。
                                                              写1清零，写0无效。 */
        unsigned int  irm_mtcmos_ctrl_clr : 1;  /* bit[2]   : IRM电源域上电清除。
                                                              写1清零，写0无效。 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_MTCMOS_CLR_UNION;
#define BBPSCTRL_BBP_MTCMOS_CLR_lte_mtcmos_ctrl_clr_START  (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_lte_mtcmos_ctrl_clr_END    (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_wtc_mtcmos_ctrl_clr_START  (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_wtc_mtcmos_ctrl_clr_END    (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_irm_mtcmos_ctrl_clr_START  (2)
#define BBPSCTRL_BBP_MTCMOS_CLR_irm_mtcmos_ctrl_clr_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_MTCMOS_STATUS_UNION
 结构说明  : BBP_MTCMOS_STATUS 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: BBP电源控制状态(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_status_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_status : 1;  /* bit[0]   : LTE电源域电源状态。
                                                                 1：上电
                                                                 0：下电 */
        unsigned int  wtc_mtcmos_ctrl_status : 1;  /* bit[1]   : WTC电源域电源状态。
                                                                 1：上电
                                                                 0：下电 */
        unsigned int  irm_mtcmos_ctrl_status : 1;  /* bit[2]   : IRM电源域电源状态。
                                                                 1：上电
                                                                 0：下电 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_MTCMOS_STATUS_UNION;
#define BBPSCTRL_BBP_MTCMOS_STATUS_lte_mtcmos_ctrl_status_START  (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_lte_mtcmos_ctrl_status_END    (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_wtc_mtcmos_ctrl_status_START  (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_wtc_mtcmos_ctrl_status_END    (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_irm_mtcmos_ctrl_status_START  (2)
#define BBPSCTRL_BBP_MTCMOS_STATUS_irm_mtcmos_ctrl_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_ISO_EN_SET_UNION
 结构说明  : BBP_ISO_EN_SET 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: BBP电源隔离控制使能(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_set_reg;
    struct
    {
        unsigned int  lte_iso_en_set : 1;  /* bit[0]   : LTE电源域隔离置位。
                                                         写1置位，写0无效。 */
        unsigned int  wtc_iso_en_set : 1;  /* bit[1]   : WTC电源域隔离置位。
                                                         写1置位，写0无效。 */
        unsigned int  irm_iso_en_set : 1;  /* bit[2]   : IRM电源域隔离置位。
                                                         写1置位，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_ISO_EN_SET_UNION;
#define BBPSCTRL_BBP_ISO_EN_SET_lte_iso_en_set_START  (0)
#define BBPSCTRL_BBP_ISO_EN_SET_lte_iso_en_set_END    (0)
#define BBPSCTRL_BBP_ISO_EN_SET_wtc_iso_en_set_START  (1)
#define BBPSCTRL_BBP_ISO_EN_SET_wtc_iso_en_set_END    (1)
#define BBPSCTRL_BBP_ISO_EN_SET_irm_iso_en_set_START  (2)
#define BBPSCTRL_BBP_ISO_EN_SET_irm_iso_en_set_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_ISO_EN_CLR_UNION
 结构说明  : BBP_ISO_EN_CLR 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: BBP电源隔离控制关闭(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_clr_reg;
    struct
    {
        unsigned int  lte_iso_en_clr : 1;  /* bit[0]   : LTE电源域隔离清除。
                                                         写1清零，写0无效。 */
        unsigned int  wtc_iso_en_clr : 1;  /* bit[1]   : WTC电源域隔离清除。
                                                         写1清零，写0无效。 */
        unsigned int  irm_iso_en_clr : 1;  /* bit[2]   : IRM电源域隔离清除。
                                                         写1清零，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_ISO_EN_CLR_UNION;
#define BBPSCTRL_BBP_ISO_EN_CLR_lte_iso_en_clr_START  (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_lte_iso_en_clr_END    (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_wtc_iso_en_clr_START  (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_wtc_iso_en_clr_END    (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_irm_iso_en_clr_START  (2)
#define BBPSCTRL_BBP_ISO_EN_CLR_irm_iso_en_clr_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_ISO_EN_STATUS_UNION
 结构说明  : BBP_ISO_EN_STATUS 寄存器结构定义。地址偏移量:0x0018，初值:0x00000007，宽度:32
 寄存器说明: BBP电源隔离控制状态(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_status_reg;
    struct
    {
        unsigned int  lte_iso_en_status : 1;  /* bit[0]   : LTE电源域隔离状态。
                                                            1：隔离；
                                                            0：解除隔离； */
        unsigned int  wtc_iso_en_status : 1;  /* bit[1]   : WTC电源域隔离状态。
                                                            1：隔离；
                                                            0：解除隔离； */
        unsigned int  irm_iso_en_status : 1;  /* bit[2]   : IRM电源域隔离状态。
                                                            1：隔离；
                                                            0：解除隔离； */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_ISO_EN_STATUS_UNION;
#define BBPSCTRL_BBP_ISO_EN_STATUS_lte_iso_en_status_START  (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_lte_iso_en_status_END    (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_wtc_iso_en_status_START  (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_wtc_iso_en_status_END    (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_irm_iso_en_status_START  (2)
#define BBPSCTRL_BBP_ISO_EN_STATUS_irm_iso_en_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_CLK_SET_UNION
 结构说明  : BBP_PD_CLK_SET 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域时钟使能(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_set_reg;
    struct
    {
        unsigned int  lte_pd_clk_ena : 1;  /* bit[0]   : LTE电源域时钟使能。
                                                         写1置位，写0无效。 */
        unsigned int  wtc_pd_clk_ena : 1;  /* bit[1]   : WTC电源域时钟使能。
                                                         写1置位，写0无效。 */
        unsigned int  irm_pd_clk_ena : 1;  /* bit[2]   : IRM电源域时钟使能。
                                                         写1置位，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_CLK_SET_UNION;
#define BBPSCTRL_BBP_PD_CLK_SET_lte_pd_clk_ena_START  (0)
#define BBPSCTRL_BBP_PD_CLK_SET_lte_pd_clk_ena_END    (0)
#define BBPSCTRL_BBP_PD_CLK_SET_wtc_pd_clk_ena_START  (1)
#define BBPSCTRL_BBP_PD_CLK_SET_wtc_pd_clk_ena_END    (1)
#define BBPSCTRL_BBP_PD_CLK_SET_irm_pd_clk_ena_START  (2)
#define BBPSCTRL_BBP_PD_CLK_SET_irm_pd_clk_ena_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_CLK_CLR_UNION
 结构说明  : BBP_PD_CLK_CLR 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域时钟关闭(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_clr_reg;
    struct
    {
        unsigned int  lte_pd_clk_dis : 1;  /* bit[0]   : LTE电源域时钟关闭。
                                                         写1关闭，写0无效。 */
        unsigned int  wtc_pd_clk_dis : 1;  /* bit[1]   : WTC电源域时钟关闭。
                                                         写1关闭，写0无效。 */
        unsigned int  irm_pd_clk_dis : 1;  /* bit[2]   : IRM电源域时钟关闭。
                                                         写1关闭，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_CLK_CLR_UNION;
#define BBPSCTRL_BBP_PD_CLK_CLR_lte_pd_clk_dis_START  (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_lte_pd_clk_dis_END    (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_wtc_pd_clk_dis_START  (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_wtc_pd_clk_dis_END    (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_irm_pd_clk_dis_START  (2)
#define BBPSCTRL_BBP_PD_CLK_CLR_irm_pd_clk_dis_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_CLK_STATUS_UNION
 结构说明  : BBP_PD_CLK_STATUS 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域时钟门控状态(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_status_reg;
    struct
    {
        unsigned int  lte_pd_clk_status : 1;  /* bit[0]   : LTE电源域时钟状态。
                                                            1：时钟使能
                                                            0：时钟关闭 */
        unsigned int  wtc_pd_clk_status : 1;  /* bit[1]   : WTC电源域时钟状态。
                                                            1：时钟使能
                                                            0：时钟关闭 */
        unsigned int  irm_pd_clk_status : 1;  /* bit[2]   : IRM电源域时钟状态。
                                                            1：时钟使能
                                                            0：时钟关闭 */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_CLK_STATUS_UNION;
#define BBPSCTRL_BBP_PD_CLK_STATUS_lte_pd_clk_status_START  (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_lte_pd_clk_status_END    (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_wtc_pd_clk_status_START  (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_wtc_pd_clk_status_END    (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_irm_pd_clk_status_START  (2)
#define BBPSCTRL_BBP_PD_CLK_STATUS_irm_pd_clk_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_SRST_SET_UNION
 结构说明  : BBP_PD_SRST_SET 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域复位请求使能(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_set_reg;
    struct
    {
        unsigned int  lte_pd_srst_req : 1;  /* bit[0]   : LTE电源域复位请求。
                                                          写1复位，写0无效。 */
        unsigned int  wtc_pd_srst_req : 1;  /* bit[1]   : WTC电源域复位请求。
                                                          写1复位，写0无效。 */
        unsigned int  irm_pd_srst_req : 1;  /* bit[2]   : IRM电源域复位请求。
                                                          写1复位，写0无效。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_SRST_SET_UNION;
#define BBPSCTRL_BBP_PD_SRST_SET_lte_pd_srst_req_START  (0)
#define BBPSCTRL_BBP_PD_SRST_SET_lte_pd_srst_req_END    (0)
#define BBPSCTRL_BBP_PD_SRST_SET_wtc_pd_srst_req_START  (1)
#define BBPSCTRL_BBP_PD_SRST_SET_wtc_pd_srst_req_END    (1)
#define BBPSCTRL_BBP_PD_SRST_SET_irm_pd_srst_req_START  (2)
#define BBPSCTRL_BBP_PD_SRST_SET_irm_pd_srst_req_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_SRST_CLR_UNION
 结构说明  : BBP_PD_SRST_CLR 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域复位请求关闭(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_clr_reg;
    struct
    {
        unsigned int  lte_pd_srst_dis : 1;  /* bit[0]   : LTE电源域复位清除。
                                                          写1解除复位，写0无效。 */
        unsigned int  wtc_pd_srst_dis : 1;  /* bit[1]   : WTC电源域复位清除。
                                                          写1解除复位，写0无效。 */
        unsigned int  irm_pd_srst_dis : 1;  /* bit[2]   : IRM电源域复位清除。
                                                          写1解除复位，写0无效。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_SRST_CLR_UNION;
#define BBPSCTRL_BBP_PD_SRST_CLR_lte_pd_srst_dis_START  (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_lte_pd_srst_dis_END    (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_wtc_pd_srst_dis_START  (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_wtc_pd_srst_dis_END    (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_irm_pd_srst_dis_START  (2)
#define BBPSCTRL_BBP_PD_SRST_CLR_irm_pd_srst_dis_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_SRST_STATUS_UNION
 结构说明  : BBP_PD_SRST_STATUS 寄存器结构定义。地址偏移量:0x0038，初值:0x00000007，宽度:32
 寄存器说明: BBP电源域复位请求状态(C核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_status_reg;
    struct
    {
        unsigned int  lte_pd_srst_status : 1;  /* bit[0]   : LTE电源域复位状态。
                                                             1：复位；
                                                             0：解除复位； */
        unsigned int  wtc_pd_srst_status : 1;  /* bit[1]   : WTC电源域复位状态。
                                                             1：复位；
                                                             0：解除复位； */
        unsigned int  irm_pd_srst_status : 1;  /* bit[2]   : IRM电源域复位状态。
                                                             1：复位；
                                                             0：解除复位； */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_SRST_STATUS_UNION;
#define BBPSCTRL_BBP_PD_SRST_STATUS_lte_pd_srst_status_START  (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_lte_pd_srst_status_END    (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_wtc_pd_srst_status_START  (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_wtc_pd_srst_status_END    (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_irm_pd_srst_status_START  (2)
#define BBPSCTRL_BBP_PD_SRST_STATUS_irm_pd_srst_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_CLK0_SET_UNION
 结构说明  : BBP_CLK0_SET 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域各频率时钟使能(lte/wtc/irm)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk0_set_reg;
    struct
    {
        unsigned int  pdlte_32k_clk_en           : 1;  /* bit[0]    :  */
        unsigned int  pdlte_19m_clk_en           : 1;  /* bit[1]    :  */
        unsigned int  pdlte_pdt_122m_clk_en      : 1;  /* bit[2]    :  */
        unsigned int  pdlte_pdt_245m_122m_clk_en : 1;  /* bit[3]    :  */
        unsigned int  pdlte_pdf_245_122m_clk_en  : 1;  /* bit[4]    :  */
        unsigned int  reserved_0                 : 1;  /* bit[5]    :  */
        unsigned int  reserved_1                 : 1;  /* bit[6]    :  */
        unsigned int  reserved_2                 : 1;  /* bit[7]    :  */
        unsigned int  pdlte_lte_abb0_tx_mclk_en  : 1;  /* bit[8]    : BLV7R5版本：这信号同时控制LTE PD和IRM PD。
                                                                      DALLAS版本：这信号在LTE PD取消不再使用，只作用于IRM PD */
        unsigned int  pdlte_lte_abb1_tx_mclk_en  : 1;  /* bit[9]    : BLV7R5版本：这信号同时控制LTE PD和IRM PD。
                                                                      DALLAS版本：这信号在LTE PD取消不再使用，只作用于IRM PD */
        unsigned int  pdlte_axim_clk_en          : 1;  /* bit[10]   :  */
        unsigned int  pdwtc_32k_clk_en           : 1;  /* bit[11]   :  */
        unsigned int  pdwtc_19m_clk_en           : 1;  /* bit[12]   :  */
        unsigned int  pdwtc_61m_clk_en           : 1;  /* bit[13]   :  */
        unsigned int  pdwtc_122m_clk_en          : 1;  /* bit[14]   :  */
        unsigned int  pdwtc_245m_clk_en          : 1;  /* bit[15]   :  */
        unsigned int  reserved_3                 : 1;  /* bit[16]   :  */
        unsigned int  reserved_4                 : 1;  /* bit[17]   :  */
        unsigned int  reserved_5                 : 1;  /* bit[18]   :  */
        unsigned int  pdirm_122m_clk_en          : 1;  /* bit[19]   :  */
        unsigned int  pdirm_245m_clk_en          : 1;  /* bit[20]   :  */
        unsigned int  reserved_6                 : 1;  /* bit[21]   :  */
        unsigned int  pduc2_32k_clk_en           : 1;  /* bit[22]   :  */
        unsigned int  pduc2_19m_clk_en           : 1;  /* bit[23]   :  */
        unsigned int  pduc2_61m_clk_en           : 1;  /* bit[24]   :  */
        unsigned int  pduc2_122m_clk_en          : 1;  /* bit[25]   :  */
        unsigned int  pduc2_245m_clk_en          : 1;  /* bit[26]   :  */
        unsigned int  reserved_7                 : 5;  /* bit[27-31]: 保留。Debug使用。 */
    } reg;
} BBPSCTRL_BBP_CLK0_SET_UNION;
#define BBPSCTRL_BBP_CLK0_SET_pdlte_32k_clk_en_START            (0)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_32k_clk_en_END              (0)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_19m_clk_en_START            (1)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_19m_clk_en_END              (1)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_122m_clk_en_START       (2)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_122m_clk_en_END         (2)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_245m_122m_clk_en_START  (3)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_245m_122m_clk_en_END    (3)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdf_245_122m_clk_en_START   (4)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdf_245_122m_clk_en_END     (4)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb0_tx_mclk_en_START   (8)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb0_tx_mclk_en_END     (8)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb1_tx_mclk_en_START   (9)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb1_tx_mclk_en_END     (9)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_axim_clk_en_START           (10)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_axim_clk_en_END             (10)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_32k_clk_en_START            (11)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_32k_clk_en_END              (11)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_19m_clk_en_START            (12)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_19m_clk_en_END              (12)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_61m_clk_en_START            (13)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_61m_clk_en_END              (13)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_122m_clk_en_START           (14)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_122m_clk_en_END             (14)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_245m_clk_en_START           (15)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_245m_clk_en_END             (15)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_122m_clk_en_START           (19)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_122m_clk_en_END             (19)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_245m_clk_en_START           (20)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_245m_clk_en_END             (20)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_32k_clk_en_START            (22)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_32k_clk_en_END              (22)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_19m_clk_en_START            (23)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_19m_clk_en_END              (23)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_61m_clk_en_START            (24)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_61m_clk_en_END              (24)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_122m_clk_en_START           (25)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_122m_clk_en_END             (25)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_245m_clk_en_START           (26)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_245m_clk_en_END             (26)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_CLK0_CLR_UNION
 结构说明  : BBP_CLK0_CLR 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域各频率时钟关闭(lte/wtc/irm)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk0_clr_reg;
    struct
    {
        unsigned int  pdlte_32k_clk_dis           : 1;  /* bit[0]    :  */
        unsigned int  pdlte_19m_clk_dis           : 1;  /* bit[1]    :  */
        unsigned int  pdlte_pdt_122m_clk_dis      : 1;  /* bit[2]    :  */
        unsigned int  pdlte_pdt_245m_122m_clk_dis : 1;  /* bit[3]    :  */
        unsigned int  pdlte_pdf_245_122m_clk_dis  : 1;  /* bit[4]    :  */
        unsigned int  reserved_0                  : 1;  /* bit[5]    :  */
        unsigned int  reserved_1                  : 1;  /* bit[6]    :  */
        unsigned int  reserved_2                  : 1;  /* bit[7]    :  */
        unsigned int  pdlte_lte_abb0_tx_mclk_dis  : 1;  /* bit[8]    : BLV7R5版本：这信号同时控制LTE PD和IRM PD。
                                                                       DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效 */
        unsigned int  pdlte_lte_abb1_tx_mclk_dis  : 1;  /* bit[9]    : BLV7R5版本：这信号同时控制LTE PD和IRM PD。
                                                                       DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效 */
        unsigned int  pdlte_axim_clk_dis          : 1;  /* bit[10]   :  */
        unsigned int  pdwtc_32k_clk_dis           : 1;  /* bit[11]   :  */
        unsigned int  pdwtc_19m_clk_dis           : 1;  /* bit[12]   :  */
        unsigned int  pdwtc_61m_clk_dis           : 1;  /* bit[13]   :  */
        unsigned int  pdwtc_122m_clk_dis          : 1;  /* bit[14]   :  */
        unsigned int  pdwtc_245m_clk_dis          : 1;  /* bit[15]   :  */
        unsigned int  reserved_3                  : 1;  /* bit[16]   :  */
        unsigned int  reserved_4                  : 1;  /* bit[17]   :  */
        unsigned int  reserved_5                  : 1;  /* bit[18]   :  */
        unsigned int  pdirm_122m_clk_dis          : 1;  /* bit[19]   :  */
        unsigned int  pdirm_245m_clk_dis          : 1;  /* bit[20]   :  */
        unsigned int  reserved_6                  : 1;  /* bit[21]   :  */
        unsigned int  pduc2_32k_clk_dis           : 1;  /* bit[22]   :  */
        unsigned int  pduc2_19m_clk_dis           : 1;  /* bit[23]   :  */
        unsigned int  pduc2_61m_clk_dis           : 1;  /* bit[24]   :  */
        unsigned int  pduc2_122m_clk_dis          : 1;  /* bit[25]   :  */
        unsigned int  pduc2_245m_clk_dis          : 1;  /* bit[26]   :  */
        unsigned int  reserved_7                  : 5;  /* bit[27-31]: 保留。Debug使用。 */
    } reg;
} BBPSCTRL_BBP_CLK0_CLR_UNION;
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_32k_clk_dis_START            (0)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_32k_clk_dis_END              (0)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_19m_clk_dis_START            (1)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_19m_clk_dis_END              (1)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_122m_clk_dis_START       (2)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_122m_clk_dis_END         (2)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_245m_122m_clk_dis_START  (3)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_245m_122m_clk_dis_END    (3)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdf_245_122m_clk_dis_START   (4)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdf_245_122m_clk_dis_END     (4)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb0_tx_mclk_dis_START   (8)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb0_tx_mclk_dis_END     (8)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb1_tx_mclk_dis_START   (9)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb1_tx_mclk_dis_END     (9)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_axim_clk_dis_START           (10)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_axim_clk_dis_END             (10)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_32k_clk_dis_START            (11)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_32k_clk_dis_END              (11)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_19m_clk_dis_START            (12)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_19m_clk_dis_END              (12)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_61m_clk_dis_START            (13)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_61m_clk_dis_END              (13)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_122m_clk_dis_START           (14)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_122m_clk_dis_END             (14)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_245m_clk_dis_START           (15)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_245m_clk_dis_END             (15)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_122m_clk_dis_START           (19)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_122m_clk_dis_END             (19)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_245m_clk_dis_START           (20)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_245m_clk_dis_END             (20)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_32k_clk_dis_START            (22)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_32k_clk_dis_END              (22)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_19m_clk_dis_START            (23)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_19m_clk_dis_END              (23)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_61m_clk_dis_START            (24)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_61m_clk_dis_END              (24)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_122m_clk_dis_START           (25)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_122m_clk_dis_END             (25)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_245m_clk_dis_START           (26)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_245m_clk_dis_END             (26)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_CLK0_STATUS_UNION
 结构说明  : BBP_CLK0_STATUS 寄存器结构定义。地址偏移量:0x0048，初值:0xFFFFFFFF，宽度:32
 寄存器说明: BBP电源域各频率时钟门控状态(lte/wtc/irm)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk0_status_reg;
    struct
    {
        unsigned int  pdlte_32k_clk_status           : 1;  /* bit[0]    :  */
        unsigned int  pdlte_19m_clk_status           : 1;  /* bit[1]    :  */
        unsigned int  pdlte_pdt_122m_clk_status      : 1;  /* bit[2]    :  */
        unsigned int  pdlte_pdt_245m_122m_clk_status : 1;  /* bit[3]    :  */
        unsigned int  pdlte_pdf_245_122m_clk_status  : 1;  /* bit[4]    :  */
        unsigned int  reserved_0                     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1                     : 1;  /* bit[6]    :  */
        unsigned int  reserved_2                     : 1;  /* bit[7]    :  */
        unsigned int  pdlte_lte_abb0_tx_mclk_status  : 1;  /* bit[8]    : BLV7R5版本：这信号同时控制LTE PD和IRM PD。
                                                                          DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效 */
        unsigned int  pdlte_lte_abb1_tx_mclk_status  : 1;  /* bit[9]    : BLV7R5版本：这信号同时控制LTE PD和IRM PD。
                                                                          DALLAS版本：这信号在LTE PD取消不再使用，只在IRM PD有效 */
        unsigned int  pdlte_axim_clk_status          : 1;  /* bit[10]   :  */
        unsigned int  pdwtc_32k_clk_status           : 1;  /* bit[11]   :  */
        unsigned int  pdwtc_19m_clk_status           : 1;  /* bit[12]   :  */
        unsigned int  pdwtc_61m_clk_status           : 1;  /* bit[13]   :  */
        unsigned int  pdwtc_122m_clk_status          : 1;  /* bit[14]   :  */
        unsigned int  pdwtc_245m_clk_status          : 1;  /* bit[15]   :  */
        unsigned int  reserved_3                     : 1;  /* bit[16]   :  */
        unsigned int  reserved_4                     : 1;  /* bit[17]   :  */
        unsigned int  reserved_5                     : 1;  /* bit[18]   :  */
        unsigned int  pdirm_122m_clk_status          : 1;  /* bit[19]   :  */
        unsigned int  pdirm_245m_clk_status          : 1;  /* bit[20]   :  */
        unsigned int  reserved_6                     : 1;  /* bit[21]   :  */
        unsigned int  pduc2_32k_clk_status           : 1;  /* bit[22]   :  */
        unsigned int  pduc2_19m_clk_status           : 1;  /* bit[23]   :  */
        unsigned int  pduc2_61m_clk_status           : 1;  /* bit[24]   :  */
        unsigned int  pduc2_122m_clk_status          : 1;  /* bit[25]   :  */
        unsigned int  pduc2_245m_clk_status          : 1;  /* bit[26]   :  */
        unsigned int  reserved_7                     : 5;  /* bit[27-31]: 保留。Debug使用。 */
    } reg;
} BBPSCTRL_BBP_CLK0_STATUS_UNION;
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_32k_clk_status_START            (0)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_32k_clk_status_END              (0)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_19m_clk_status_START            (1)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_19m_clk_status_END              (1)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_122m_clk_status_START       (2)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_122m_clk_status_END         (2)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_245m_122m_clk_status_START  (3)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_245m_122m_clk_status_END    (3)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdf_245_122m_clk_status_START   (4)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdf_245_122m_clk_status_END     (4)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb0_tx_mclk_status_START   (8)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb0_tx_mclk_status_END     (8)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb1_tx_mclk_status_START   (9)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb1_tx_mclk_status_END     (9)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_axim_clk_status_START           (10)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_axim_clk_status_END             (10)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_32k_clk_status_START            (11)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_32k_clk_status_END              (11)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_19m_clk_status_START            (12)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_19m_clk_status_END              (12)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_61m_clk_status_START            (13)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_61m_clk_status_END              (13)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_122m_clk_status_START           (14)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_122m_clk_status_END             (14)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_245m_clk_status_START           (15)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_245m_clk_status_END             (15)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_122m_clk_status_START           (19)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_122m_clk_status_END             (19)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_245m_clk_status_START           (20)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_245m_clk_status_END             (20)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_32k_clk_status_START            (22)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_32k_clk_status_END              (22)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_19m_clk_status_START            (23)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_19m_clk_status_END              (23)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_61m_clk_status_START            (24)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_61m_clk_status_END              (24)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_122m_clk_status_START           (25)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_122m_clk_status_END             (25)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_245m_clk_status_START           (26)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_245m_clk_status_END             (26)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_CLK1_SET_UNION
 结构说明  : BBP_CLK1_SET 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域各频率时钟使能(com)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk1_set_reg;
    struct
    {
        unsigned int  bbc_19m_clk_en           : 1;  /* bit[0]    :  */
        unsigned int  com_g_32k_clk_en         : 1;  /* bit[1]    :  */
        unsigned int  bbc_g_104m_clk_en        : 1;  /* bit[2]    :  */
        unsigned int  bbc_wtc_122m_clk_en      : 1;  /* bit[3]    :  */
        unsigned int  bbc_wtc_245m_clk_en      : 1;  /* bit[4]    :  */
        unsigned int  com_pdt_122m_clk_en      : 1;  /* bit[5]    :  */
        unsigned int  com_pdt_245m_122m_clk_en : 1;  /* bit[6]    :  */
        unsigned int  com_pdf_245m_122m_clk_en : 1;  /* bit[7]    :  */
        unsigned int  com_wtc_61m_clk_en       : 1;  /* bit[8]    :  */
        unsigned int  com_lte_245m_clk_en      : 1;  /* bit[9]    :  */
        unsigned int  com_wc_abb_122m_clk_en   : 1;  /* bit[10]   :  */
        unsigned int  com_wc_abb_61m_clk_en    : 1;  /* bit[11]   :  */
        unsigned int  com_uc2_61m_clk_en       : 1;  /* bit[12]   :  */
        unsigned int  bbc_uc2_122m_clk_en      : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_245m_clk_en      : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: 保留。Debug使用。 */
    } reg;
} BBPSCTRL_BBP_CLK1_SET_UNION;
#define BBPSCTRL_BBP_CLK1_SET_bbc_19m_clk_en_START            (0)
#define BBPSCTRL_BBP_CLK1_SET_bbc_19m_clk_en_END              (0)
#define BBPSCTRL_BBP_CLK1_SET_com_g_32k_clk_en_START          (1)
#define BBPSCTRL_BBP_CLK1_SET_com_g_32k_clk_en_END            (1)
#define BBPSCTRL_BBP_CLK1_SET_bbc_g_104m_clk_en_START         (2)
#define BBPSCTRL_BBP_CLK1_SET_bbc_g_104m_clk_en_END           (2)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_122m_clk_en_START       (3)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_122m_clk_en_END         (3)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_245m_clk_en_START       (4)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_245m_clk_en_END         (4)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_122m_clk_en_START       (5)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_122m_clk_en_END         (5)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_245m_122m_clk_en_START  (6)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_245m_122m_clk_en_END    (6)
#define BBPSCTRL_BBP_CLK1_SET_com_pdf_245m_122m_clk_en_START  (7)
#define BBPSCTRL_BBP_CLK1_SET_com_pdf_245m_122m_clk_en_END    (7)
#define BBPSCTRL_BBP_CLK1_SET_com_wtc_61m_clk_en_START        (8)
#define BBPSCTRL_BBP_CLK1_SET_com_wtc_61m_clk_en_END          (8)
#define BBPSCTRL_BBP_CLK1_SET_com_lte_245m_clk_en_START       (9)
#define BBPSCTRL_BBP_CLK1_SET_com_lte_245m_clk_en_END         (9)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_122m_clk_en_START    (10)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_122m_clk_en_END      (10)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_61m_clk_en_START     (11)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_61m_clk_en_END       (11)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_61m_clk_en_START        (12)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_61m_clk_en_END          (12)
#define BBPSCTRL_BBP_CLK1_SET_bbc_uc2_122m_clk_en_START       (13)
#define BBPSCTRL_BBP_CLK1_SET_bbc_uc2_122m_clk_en_END         (13)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_245m_clk_en_START       (14)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_245m_clk_en_END         (14)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_CLK1_CLR_UNION
 结构说明  : BBP_CLK1_CLR 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域各频率时钟关闭(com)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk1_clr_reg;
    struct
    {
        unsigned int  bbc_19m_clk_dis           : 1;  /* bit[0]    :  */
        unsigned int  com_g_32k_clk_dis         : 1;  /* bit[1]    :  */
        unsigned int  bbc_g_104m_clk_dis        : 1;  /* bit[2]    :  */
        unsigned int  bbc_wtc_122m_clk_dis      : 1;  /* bit[3]    :  */
        unsigned int  bbc_wtc_245m_clk_dis      : 1;  /* bit[4]    :  */
        unsigned int  com_pdt_122m_clk_dis      : 1;  /* bit[5]    :  */
        unsigned int  com_pdt_245m_122m_clk_dis : 1;  /* bit[6]    :  */
        unsigned int  com_pdf_245m_122m_clk_dis : 1;  /* bit[7]    :  */
        unsigned int  com_wtc_61m_clk_dis       : 1;  /* bit[8]    :  */
        unsigned int  com_lte_245m_clk_dis      : 1;  /* bit[9]    :  */
        unsigned int  com_wc_abb_122m_clk_dis   : 1;  /* bit[10]   :  */
        unsigned int  com_wc_abb_61m_clk_dis    : 1;  /* bit[11]   :  */
        unsigned int  com_uc2_61m_clk_dis       : 1;  /* bit[12]   :  */
        unsigned int  bbc_uc2_122m_clk_dis      : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_245m_clk_dis      : 1;  /* bit[14]   :  */
        unsigned int  reserved                  : 17; /* bit[15-31]: 保留。Debug使用。 */
    } reg;
} BBPSCTRL_BBP_CLK1_CLR_UNION;
#define BBPSCTRL_BBP_CLK1_CLR_bbc_19m_clk_dis_START            (0)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_19m_clk_dis_END              (0)
#define BBPSCTRL_BBP_CLK1_CLR_com_g_32k_clk_dis_START          (1)
#define BBPSCTRL_BBP_CLK1_CLR_com_g_32k_clk_dis_END            (1)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_g_104m_clk_dis_START         (2)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_g_104m_clk_dis_END           (2)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_122m_clk_dis_START       (3)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_122m_clk_dis_END         (3)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_245m_clk_dis_START       (4)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_245m_clk_dis_END         (4)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_122m_clk_dis_START       (5)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_122m_clk_dis_END         (5)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_245m_122m_clk_dis_START  (6)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_245m_122m_clk_dis_END    (6)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdf_245m_122m_clk_dis_START  (7)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdf_245m_122m_clk_dis_END    (7)
#define BBPSCTRL_BBP_CLK1_CLR_com_wtc_61m_clk_dis_START        (8)
#define BBPSCTRL_BBP_CLK1_CLR_com_wtc_61m_clk_dis_END          (8)
#define BBPSCTRL_BBP_CLK1_CLR_com_lte_245m_clk_dis_START       (9)
#define BBPSCTRL_BBP_CLK1_CLR_com_lte_245m_clk_dis_END         (9)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_122m_clk_dis_START    (10)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_122m_clk_dis_END      (10)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_61m_clk_dis_START     (11)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_61m_clk_dis_END       (11)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_61m_clk_dis_START        (12)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_61m_clk_dis_END          (12)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_uc2_122m_clk_dis_START       (13)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_uc2_122m_clk_dis_END         (13)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_245m_clk_dis_START       (14)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_245m_clk_dis_END         (14)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_CLK1_STATUS_UNION
 结构说明  : BBP_CLK1_STATUS 寄存器结构定义。地址偏移量:0x0058，初值:0xFFFFFFFF，宽度:32
 寄存器说明: BBP电源域各频率时钟门控状态(com)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk1_status_reg;
    struct
    {
        unsigned int  bbc_19m_clk_status           : 1;  /* bit[0]    :  */
        unsigned int  com_g_32k_clk_status         : 1;  /* bit[1]    :  */
        unsigned int  bbc_g_104m_clk_status        : 1;  /* bit[2]    : G */
        unsigned int  bbc_wtc_122m_clk_status      : 1;  /* bit[3]    : WTC */
        unsigned int  bbc_wtc_245m_clk_status      : 1;  /* bit[4]    : TDS */
        unsigned int  com_pdt_122m_clk_status      : 1;  /* bit[5]    : PDT */
        unsigned int  com_pdt_245m_122m_clk_status : 1;  /* bit[6]    : ULHB */
        unsigned int  com_pdf_245m_122m_clk_status : 1;  /* bit[7]    : PDF */
        unsigned int  com_wtc_61m_clk_status       : 1;  /* bit[8]    :  */
        unsigned int  com_lte_245m_clk_status      : 1;  /* bit[9]    :  */
        unsigned int  com_wc_abb_122m_clk_status   : 1;  /* bit[10]   :  */
        unsigned int  com_wc_abb_61m_clk_status    : 1;  /* bit[11]   :  */
        unsigned int  com_uc2_61m_clk_status       : 1;  /* bit[12]   :  */
        unsigned int  bbc_uc2_122m_clk_status      : 1;  /* bit[13]   : C2 */
        unsigned int  com_uc2_245m_clk_status      : 1;  /* bit[14]   :  */
        unsigned int  reserved                     : 17; /* bit[15-31]: 保留。Debug使用。 */
    } reg;
} BBPSCTRL_BBP_CLK1_STATUS_UNION;
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_19m_clk_status_START            (0)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_19m_clk_status_END              (0)
#define BBPSCTRL_BBP_CLK1_STATUS_com_g_32k_clk_status_START          (1)
#define BBPSCTRL_BBP_CLK1_STATUS_com_g_32k_clk_status_END            (1)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_g_104m_clk_status_START         (2)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_g_104m_clk_status_END           (2)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_122m_clk_status_START       (3)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_122m_clk_status_END         (3)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_245m_clk_status_START       (4)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_245m_clk_status_END         (4)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_122m_clk_status_START       (5)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_122m_clk_status_END         (5)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_245m_122m_clk_status_START  (6)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_245m_122m_clk_status_END    (6)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdf_245m_122m_clk_status_START  (7)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdf_245m_122m_clk_status_END    (7)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wtc_61m_clk_status_START        (8)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wtc_61m_clk_status_END          (8)
#define BBPSCTRL_BBP_CLK1_STATUS_com_lte_245m_clk_status_START       (9)
#define BBPSCTRL_BBP_CLK1_STATUS_com_lte_245m_clk_status_END         (9)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_122m_clk_status_START    (10)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_122m_clk_status_END      (10)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_61m_clk_status_START     (11)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_61m_clk_status_END       (11)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_61m_clk_status_START        (12)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_61m_clk_status_END          (12)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_uc2_122m_clk_status_START       (13)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_uc2_122m_clk_status_END         (13)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_245m_clk_status_START       (14)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_245m_clk_status_END         (14)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTRL6_SET_UNION
 结构说明  : BBP_SCTRL6_SET 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器6置位(UC2_CLK_EN)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl6_set_reg;
    struct
    {
        unsigned int  clk_61m_r99w2_en      : 1;  /* bit[0]   : UC2的W模61M时钟使能，dallas不需要使能
                                                                写1置位，写0无效。 */
        unsigned int  clk_122m_r99w2_en     : 1;  /* bit[1]   : UC2的W模122M时钟使能，dallas不需要使能
                                                                写1置位，写0无效。 */
        unsigned int  clk_122m_cbbp2_en     : 1;  /* bit[2]   : UC2的C模122M时钟使能
                                                                写1置位，写0无效。 */
        unsigned int  clk_122m_wc2_en       : 1;  /* bit[3]   : UC2的WC模共享122M时钟使能
                                                                写1置位，写0无效。 */
        unsigned int  clk_122m_wc2_turbo_en : 1;  /* bit[4]   : UC2的WC模共享122M时钟使能
                                                                写1置位，写0无效。 */
        unsigned int  clk_245m_wc2_turbo_en : 1;  /* bit[5]   : UC2的WC模共享245M时钟使能
                                                                写1置位，写0无效。 */
        unsigned int  clk_19m_uc2_en        : 1;  /* bit[6]   : UC2的TCXO时钟使能
                                                                写1置位，写0无效。 */
        unsigned int  reserved              : 25; /* bit[7-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTRL6_SET_UNION;
#define BBPSCTRL_BBP_SCTRL6_SET_clk_61m_r99w2_en_START       (0)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_61m_r99w2_en_END         (0)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_r99w2_en_START      (1)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_r99w2_en_END        (1)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_cbbp2_en_START      (2)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_cbbp2_en_END        (2)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_en_START        (3)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_en_END          (3)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_turbo_en_START  (4)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_turbo_en_END    (4)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_245m_wc2_turbo_en_START  (5)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_245m_wc2_turbo_en_END    (5)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_19m_uc2_en_START         (6)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_19m_uc2_en_END           (6)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTRL6_CLR_UNION
 结构说明  : BBP_SCTRL6_CLR 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器6清零(UC2_CLK_DIS)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl6_clr_reg;
    struct
    {
        unsigned int  clk_61m_r99w2_dis      : 1;  /* bit[0]   : UC2的W模61M时钟关闭
                                                                 写1关闭，写0无效。 */
        unsigned int  clk_122m_r99w2_dis     : 1;  /* bit[1]   : UC2的W模122M时钟关闭
                                                                 写1关闭，写0无效。 */
        unsigned int  clk_122m_cbbp2_dis     : 1;  /* bit[2]   : UC2的C模122M时钟关闭
                                                                 写1关闭，写0无效。 */
        unsigned int  clk_122m_wc2_dis       : 1;  /* bit[3]   : UC2的WC模共享122M时钟关闭
                                                                 写1关闭，写0无效。 */
        unsigned int  clk_122m_wc2_turbo_dis : 1;  /* bit[4]   : UC2的WC模共享122M时钟关闭
                                                                 写1关闭，写0无效。 */
        unsigned int  clk_245m_wc2_turbo_dis : 1;  /* bit[5]   : UC2的WC模共享245M时钟关闭
                                                                 写1关闭，写0无效。 */
        unsigned int  clk_19m_uc2_dis        : 1;  /* bit[6]   : UC2的TCXO时钟关闭
                                                                 写1关闭，写0无效。 */
        unsigned int  reserved               : 25; /* bit[7-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTRL6_CLR_UNION;
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_61m_r99w2_dis_START       (0)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_61m_r99w2_dis_END         (0)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_r99w2_dis_START      (1)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_r99w2_dis_END        (1)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_cbbp2_dis_START      (2)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_cbbp2_dis_END        (2)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_dis_START        (3)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_dis_END          (3)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_turbo_dis_START  (4)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_turbo_dis_END    (4)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_245m_wc2_turbo_dis_START  (5)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_245m_wc2_turbo_dis_END    (5)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_19m_uc2_dis_START         (6)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_19m_uc2_dis_END           (6)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTRL6_STSTUS_UNION
 结构说明  : BBP_SCTRL6_STSTUS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器6状态(UC2_CLK_STATUS)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl6_ststus_reg;
    struct
    {
        unsigned int  clk_61m_r99w2_status      : 1;  /* bit[0]   : UC2的W模61M时钟状态
                                                                    1：时钟使能
                                                                    0：时钟关闭 */
        unsigned int  clk_122m_r99w2_status     : 1;  /* bit[1]   : UC2的W模122M时钟状态
                                                                    1：时钟使能
                                                                    0：时钟关闭 */
        unsigned int  clk_122m_cbbp2_status     : 1;  /* bit[2]   : UC2的C模122M时钟状态
                                                                    1：时钟使能
                                                                    0：时钟关闭 */
        unsigned int  clk_122m_wc2_status       : 1;  /* bit[3]   : UC2的WC模共享122M时钟状态
                                                                    1：时钟使能
                                                                    0：时钟关闭 */
        unsigned int  clk_122m_wc2_turbo_status : 1;  /* bit[4]   : UC2的WC模共享122M时钟状态
                                                                    1：时钟使能
                                                                    0：时钟关闭 */
        unsigned int  clk_245m_wc2_turbo_status : 1;  /* bit[5]   : UC2的WC模共享245M时钟状态
                                                                    1：时钟使能
                                                                    0：时钟关闭 */
        unsigned int  clk_19m_uc2_status        : 1;  /* bit[6]   : UC2的TCXO时钟状态
                                                                    1：时钟使能
                                                                    0：时钟关闭 */
        unsigned int  reserved                  : 25; /* bit[7-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTRL6_STSTUS_UNION;
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_61m_r99w2_status_START       (0)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_61m_r99w2_status_END         (0)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_r99w2_status_START      (1)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_r99w2_status_END        (1)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_cbbp2_status_START      (2)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_cbbp2_status_END        (2)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_status_START        (3)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_status_END          (3)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_turbo_status_START  (4)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_turbo_status_END    (4)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_245m_wc2_turbo_status_START  (5)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_245m_wc2_turbo_status_END    (5)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_19m_uc2_status_START         (6)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_19m_uc2_status_END           (6)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTRL7_SET_UNION
 结构说明  : BBP_SCTRL7_SET 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器7置位(UC2_RST_REQ)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl7_set_reg;
    struct
    {
        unsigned int  rst_61m_r99w2_req      : 1;  /* bit[0]   : UC2的W模61M复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  rst_122m_r99w2_req     : 1;  /* bit[1]   : UC2的W模122M复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  rst_122m_cbbp2_req     : 1;  /* bit[2]   : UC2的C模122M复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  rst_122m_wc2_req       : 1;  /* bit[3]   : UC2的WC模共享122M复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  rst_122m_wc2_turbo_req : 1;  /* bit[4]   : UC2的WC模共享122M复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  rst_245m_wc2_turbo_req : 1;  /* bit[5]   : UC2的WC模共享245M复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  rst_19m_uc2_req        : 1;  /* bit[6]   : UC2的TCXO复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  rst_32k_uc2_req        : 1;  /* bit[7]   : UC2的32K复位请求。
                                                                 写1复位，写0无效。 */
        unsigned int  reserved               : 24; /* bit[8-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTRL7_SET_UNION;
#define BBPSCTRL_BBP_SCTRL7_SET_rst_61m_r99w2_req_START       (0)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_61m_r99w2_req_END         (0)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_r99w2_req_START      (1)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_r99w2_req_END        (1)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_cbbp2_req_START      (2)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_cbbp2_req_END        (2)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_req_START        (3)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_req_END          (3)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_turbo_req_START  (4)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_turbo_req_END    (4)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_245m_wc2_turbo_req_START  (5)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_245m_wc2_turbo_req_END    (5)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_19m_uc2_req_START         (6)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_19m_uc2_req_END           (6)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_32k_uc2_req_START         (7)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_32k_uc2_req_END           (7)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTRL7_CLR_UNION
 结构说明  : BBP_SCTRL7_CLR 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器7清零(UC2_RST_CLR)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl7_clr_reg;
    struct
    {
        unsigned int  rst_61m_r99w2_clr      : 1;  /* bit[0]   : UC2的W模61M复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  rst_122m_r99w2_clr     : 1;  /* bit[1]   : UC2的W模122M复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  rst_122m_cbbp2_clr     : 1;  /* bit[2]   : UC2的C模122M复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  rst_122m_wc2_clr       : 1;  /* bit[3]   : UC2的WC模共享122M复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  rst_122m_wc2_turbo_clr : 1;  /* bit[4]   : UC2的WC模共享122M复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  rst_245m_wc2_turbo_clr : 1;  /* bit[5]   : UC2的WC模共享245M复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  rst_19m_uc2_clr        : 1;  /* bit[6]   : UC2的TCXO复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  rst_32k_uc2_clr        : 1;  /* bit[7]   : UC2的32K复位清除。
                                                                 写1解除复位，写0无效。 */
        unsigned int  reserved               : 24; /* bit[8-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTRL7_CLR_UNION;
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_61m_r99w2_clr_START       (0)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_61m_r99w2_clr_END         (0)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_r99w2_clr_START      (1)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_r99w2_clr_END        (1)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_cbbp2_clr_START      (2)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_cbbp2_clr_END        (2)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_clr_START        (3)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_clr_END          (3)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_turbo_clr_START  (4)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_turbo_clr_END    (4)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_245m_wc2_turbo_clr_START  (5)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_245m_wc2_turbo_clr_END    (5)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_19m_uc2_clr_START         (6)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_19m_uc2_clr_END           (6)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_32k_uc2_clr_START         (7)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_32k_uc2_clr_END           (7)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTRL7_STSTUS_UNION
 结构说明  : BBP_SCTRL7_STSTUS 寄存器结构定义。地址偏移量:0x0078，初值:0xFFFFFFFF，宽度:32
 寄存器说明: BBP系统控制器7状态(UC2_RST_STATUS)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl7_ststus_reg;
    struct
    {
        unsigned int  rst_61m_r99w2_status      : 1;  /* bit[0]   : UC2的W模61M复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  rst_122m_r99w2_status     : 1;  /* bit[1]   : UC2的W模122M复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  rst_122m_cbbp2_status     : 1;  /* bit[2]   : UC2的C模122M复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  rst_122m_wc2_status       : 1;  /* bit[3]   : UC2的WC模共享122M复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  rst_122m_wc2_turbo_status : 1;  /* bit[4]   : UC2的WC模共享122M复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  rst_245m_wc2_turbo_status : 1;  /* bit[5]   : UC2的WC模共享245M复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  rst_19m_uc2_status        : 1;  /* bit[6]   : UC2的TCXO复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  rst_32k_uc2_status        : 1;  /* bit[7]   : UC2的32K复位状态。
                                                                    1：复位；
                                                                    0：解除复位； */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTRL7_STSTUS_UNION;
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_61m_r99w2_status_START       (0)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_61m_r99w2_status_END         (0)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_r99w2_status_START      (1)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_r99w2_status_END        (1)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_cbbp2_status_START      (2)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_cbbp2_status_END        (2)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_status_START        (3)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_status_END          (3)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_turbo_status_START  (4)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_turbo_status_END    (4)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_245m_wc2_turbo_status_START  (5)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_245m_wc2_turbo_status_END    (5)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_19m_uc2_status_START         (6)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_19m_uc2_status_END           (6)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_32k_uc2_status_START         (7)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_32k_uc2_status_END           (7)


/*****************************************************************************
 结构名    : BBPSCTRL_LTE_PD_CLK_EN_UNION
 结构说明  : LTE_PD_CLK_EN 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: LTE电源域时钟使能
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_clk_en_reg;
    struct
    {
        unsigned int  lte_sys_clk_en        : 1;  /* bit[0]    : 保留。不使用。 */
        unsigned int  lte_slp_clk_en        : 1;  /* bit[1]    : 保留。不使用。 */
        unsigned int  lte_axim_clk_en       : 1;  /* bit[2]    : 保留。不使用。 */
        unsigned int  lte_pdt_clk_en        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_clk_en       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_clk_en        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_clk_en         : 1;  /* bit[6]    :  */
        unsigned int  lte_ul_clk_x2_en      : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_clk_en        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_clk_en        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_clk_en        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_clk_en         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_clk_en        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_clk_en    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_clk_en : 1;  /* bit[14]   : 保留。不使用。 */
        unsigned int  lte_tdl_ch1_clk_en    : 1;  /* bit[15]   : 保留。不使用。 */
        unsigned int  lte_abb0_rx_clk_en    : 1;  /* bit[16]   : 保留。不使用。 */
        unsigned int  lte_abb1_rx_clk_en    : 1;  /* bit[17]   : 保留。不使用。 */
        unsigned int  lte_abb2_rx_clk_en    : 1;  /* bit[18]   : 保留。不使用。 */
        unsigned int  lte_abb3_rx_clk_en    : 1;  /* bit[19]   : 保留。不使用。 */
        unsigned int  lte_abb0_tx_clk_en    : 1;  /* bit[20]   :  */
        unsigned int  lte_abb1_tx_clk_en    : 1;  /* bit[21]   :  */
        unsigned int  lte_int_clk_en        : 1;  /* bit[22]   :  */
        unsigned int  uart_clk_en           : 1;  /* bit[23]   :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留。 */
    } reg;
} BBPSCTRL_LTE_PD_CLK_EN_UNION;
#define BBPSCTRL_LTE_PD_CLK_EN_lte_sys_clk_en_START         (0)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_sys_clk_en_END           (0)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_slp_clk_en_START         (1)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_slp_clk_en_END           (1)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_axim_clk_en_START        (2)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_axim_clk_en_END          (2)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdt_clk_en_START         (3)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdt_clk_en_END           (3)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_rfin_clk_en_START        (4)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_rfin_clk_en_END          (4)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_fpu_clk_en_START         (5)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_fpu_clk_en_END           (5)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_en_START          (6)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_en_END            (6)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_x2_en_START       (7)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_x2_en_END         (7)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdu_clk_en_START         (8)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdu_clk_en_END           (8)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_cqi_clk_en_START         (9)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_cqi_clk_en_END           (9)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdf_clk_en_START         (10)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdf_clk_en_END           (10)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pb_clk_en_START          (11)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pb_clk_en_END            (11)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_vdl_clk_en_START         (12)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_vdl_clk_en_END           (12)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_clk_en_START     (13)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_clk_en_END       (13)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_2x_clk_en_START  (14)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_2x_clk_en_END    (14)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch1_clk_en_START     (15)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch1_clk_en_END       (15)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_rx_clk_en_START     (16)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_rx_clk_en_END       (16)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_rx_clk_en_START     (17)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_rx_clk_en_END       (17)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb2_rx_clk_en_START     (18)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb2_rx_clk_en_END       (18)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb3_rx_clk_en_START     (19)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb3_rx_clk_en_END       (19)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_tx_clk_en_START     (20)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_tx_clk_en_END       (20)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_tx_clk_en_START     (21)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_tx_clk_en_END       (21)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_int_clk_en_START         (22)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_int_clk_en_END           (22)
#define BBPSCTRL_LTE_PD_CLK_EN_uart_clk_en_START            (23)
#define BBPSCTRL_LTE_PD_CLK_EN_uart_clk_en_END              (23)


/*****************************************************************************
 结构名    : BBPSCTRL_LTE_PD_CLK_DIS_UNION
 结构说明  : LTE_PD_CLK_DIS 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: LTE电源域时钟关闭
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_clk_dis_reg;
    struct
    {
        unsigned int  lte_sys_clk_dis        : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_clk_dis        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_clk_dis       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_clk_dis        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_clk_dis       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_clk_dis        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_clk_dis         : 1;  /* bit[6]    :  */
        unsigned int  lte_ul_clk_x2_dis      : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_clk_dis        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_clk_dis        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_clk_dis        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_clk_dis         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_clk_dis        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_clk_dis    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_clk_dis : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_clk_dis    : 1;  /* bit[15]   :  */
        unsigned int  lte_abb0_rx_clk_dis    : 1;  /* bit[16]   :  */
        unsigned int  lte_abb1_rx_clk_dis    : 1;  /* bit[17]   :  */
        unsigned int  lte_abb2_rx_clk_dis    : 1;  /* bit[18]   :  */
        unsigned int  lte_abb3_rx_clk_dis    : 1;  /* bit[19]   :  */
        unsigned int  lte_abb0_tx_clk_dis    : 1;  /* bit[20]   :  */
        unsigned int  lte_abb1_tx_clk_dis    : 1;  /* bit[21]   :  */
        unsigned int  lte_int_clk_dis        : 1;  /* bit[22]   :  */
        unsigned int  uart_clk_dis           : 1;  /* bit[23]   :  */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留。 */
    } reg;
} BBPSCTRL_LTE_PD_CLK_DIS_UNION;
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_sys_clk_dis_START         (0)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_sys_clk_dis_END           (0)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_slp_clk_dis_START         (1)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_slp_clk_dis_END           (1)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_axim_clk_dis_START        (2)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_axim_clk_dis_END          (2)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdt_clk_dis_START         (3)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdt_clk_dis_END           (3)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_rfin_clk_dis_START        (4)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_rfin_clk_dis_END          (4)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_fpu_clk_dis_START         (5)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_fpu_clk_dis_END           (5)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_dis_START          (6)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_dis_END            (6)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_x2_dis_START       (7)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_x2_dis_END         (7)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdu_clk_dis_START         (8)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdu_clk_dis_END           (8)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_cqi_clk_dis_START         (9)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_cqi_clk_dis_END           (9)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdf_clk_dis_START         (10)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdf_clk_dis_END           (10)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pb_clk_dis_START          (11)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pb_clk_dis_END            (11)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_vdl_clk_dis_START         (12)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_vdl_clk_dis_END           (12)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_clk_dis_START     (13)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_clk_dis_END       (13)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_2x_clk_dis_START  (14)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_2x_clk_dis_END    (14)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch1_clk_dis_START     (15)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch1_clk_dis_END       (15)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_rx_clk_dis_START     (16)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_rx_clk_dis_END       (16)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_rx_clk_dis_START     (17)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_rx_clk_dis_END       (17)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb2_rx_clk_dis_START     (18)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb2_rx_clk_dis_END       (18)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb3_rx_clk_dis_START     (19)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb3_rx_clk_dis_END       (19)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_tx_clk_dis_START     (20)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_tx_clk_dis_END       (20)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_tx_clk_dis_START     (21)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_tx_clk_dis_END       (21)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_int_clk_dis_START         (22)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_int_clk_dis_END           (22)
#define BBPSCTRL_LTE_PD_CLK_DIS_uart_clk_dis_START            (23)
#define BBPSCTRL_LTE_PD_CLK_DIS_uart_clk_dis_END              (23)


/*****************************************************************************
 结构名    : BBPSCTRL_LTE_PD_CLK_STSTUS_UNION
 结构说明  : LTE_PD_CLK_STSTUS 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: LTE电源域时钟门控状态
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_clk_ststus_reg;
    struct
    {
        unsigned int  lte_sys_clk_status        : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_clk_status        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_clk_status       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_clk_status        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_clk_status       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_clk_status        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_clk_status         : 1;  /* bit[6]    :  */
        unsigned int  lte_ul_clk_x2_status      : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_clk_status        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_clk_status        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_clk_status        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_clk_status         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_clk_status        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_clk_status    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_clk_status : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_clk_status    : 1;  /* bit[15]   :  */
        unsigned int  lte_abb0_rx_clk_status    : 1;  /* bit[16]   :  */
        unsigned int  lte_abb1_rx_clk_status    : 1;  /* bit[17]   :  */
        unsigned int  lte_abb2_rx_clk_status    : 1;  /* bit[18]   :  */
        unsigned int  lte_abb3_rx_clk_status    : 1;  /* bit[19]   :  */
        unsigned int  lte_abb0_tx_clk_status    : 1;  /* bit[20]   :  */
        unsigned int  lte_abb1_tx_clk_status    : 1;  /* bit[21]   :  */
        unsigned int  lte_int_clk_status        : 1;  /* bit[22]   :  */
        unsigned int  uart_clk_status           : 1;  /* bit[23]   :  */
        unsigned int  reserved                  : 8;  /* bit[24-31]: 保留。 */
    } reg;
} BBPSCTRL_LTE_PD_CLK_STSTUS_UNION;
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_sys_clk_status_START         (0)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_sys_clk_status_END           (0)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_slp_clk_status_START         (1)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_slp_clk_status_END           (1)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_axim_clk_status_START        (2)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_axim_clk_status_END          (2)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdt_clk_status_START         (3)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdt_clk_status_END           (3)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_rfin_clk_status_START        (4)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_rfin_clk_status_END          (4)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_fpu_clk_status_START         (5)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_fpu_clk_status_END           (5)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_status_START          (6)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_status_END            (6)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_x2_status_START       (7)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_x2_status_END         (7)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdu_clk_status_START         (8)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdu_clk_status_END           (8)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_cqi_clk_status_START         (9)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_cqi_clk_status_END           (9)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdf_clk_status_START         (10)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdf_clk_status_END           (10)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pb_clk_status_START          (11)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pb_clk_status_END            (11)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_vdl_clk_status_START         (12)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_vdl_clk_status_END           (12)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_clk_status_START     (13)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_clk_status_END       (13)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_2x_clk_status_START  (14)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_2x_clk_status_END    (14)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch1_clk_status_START     (15)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch1_clk_status_END       (15)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_rx_clk_status_START     (16)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_rx_clk_status_END       (16)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_rx_clk_status_START     (17)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_rx_clk_status_END       (17)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb2_rx_clk_status_START     (18)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb2_rx_clk_status_END       (18)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb3_rx_clk_status_START     (19)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb3_rx_clk_status_END       (19)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_tx_clk_status_START     (20)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_tx_clk_status_END       (20)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_tx_clk_status_START     (21)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_tx_clk_status_END       (21)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_int_clk_status_START         (22)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_int_clk_status_END           (22)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_uart_clk_status_START            (23)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_uart_clk_status_END              (23)


/*****************************************************************************
 结构名    : BBPSCTRL_LTE_PD_SRST_REQ_UNION
 结构说明  : LTE_PD_SRST_REQ 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: LTE电源域复位请求使能
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_srst_req_reg;
    struct
    {
        unsigned int  reserved_0           : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_srst_req     : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_srst_req    : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_srst_req     : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_srst_req    : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_srst_req     : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_srst_req      : 1;  /* bit[6]    :  */
        unsigned int  reserved_1           : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_srst_req     : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_srst_req     : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_srst_req     : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_srst_req      : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_srst_req     : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_srst_req : 1;  /* bit[13]   :  */
        unsigned int  reserved_2           : 8;  /* bit[14-21]:  */
        unsigned int  lte_int_srst_req     : 1;  /* bit[22]   :  */
        unsigned int  uart_srst_req        : 1;  /* bit[23]   :  */
        unsigned int  reserved_3           : 8;  /* bit[24-31]: 保留。 */
    } reg;
} BBPSCTRL_LTE_PD_SRST_REQ_UNION;
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_slp_srst_req_START      (1)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_slp_srst_req_END        (1)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_axim_srst_req_START     (2)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_axim_srst_req_END       (2)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdt_srst_req_START      (3)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdt_srst_req_END        (3)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_rfin_srst_req_START     (4)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_rfin_srst_req_END       (4)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_fpu_srst_req_START      (5)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_fpu_srst_req_END        (5)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_ul_srst_req_START       (6)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_ul_srst_req_END         (6)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdu_srst_req_START      (8)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdu_srst_req_END        (8)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_cqi_srst_req_START      (9)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_cqi_srst_req_END        (9)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdf_srst_req_START      (10)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdf_srst_req_END        (10)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pb_srst_req_START       (11)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pb_srst_req_END         (11)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_vdl_srst_req_START      (12)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_vdl_srst_req_END        (12)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_tdl_ch0_srst_req_START  (13)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_tdl_ch0_srst_req_END    (13)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_int_srst_req_START      (22)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_int_srst_req_END        (22)
#define BBPSCTRL_LTE_PD_SRST_REQ_uart_srst_req_START         (23)
#define BBPSCTRL_LTE_PD_SRST_REQ_uart_srst_req_END           (23)


/*****************************************************************************
 结构名    : BBPSCTRL_LTE_PD_SRST_DIS_UNION
 结构说明  : LTE_PD_SRST_DIS 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: LTE电源域复位请求清除
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_srst_dis_reg;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_srst_dis        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_srst_dis       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_srst_dis        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_srst_dis       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_srst_dis        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_srst_dis         : 1;  /* bit[6]    :  */
        unsigned int  reserved_1              : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_srst_dis        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_srst_dis        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_srst_dis        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_srst_dis         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_srst_dis        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_srst_dis    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_srst_dis : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_srst_dis    : 1;  /* bit[15]   :  */
        unsigned int  reserved_2              : 6;  /* bit[16-21]:  */
        unsigned int  lte_int_srst_dis        : 1;  /* bit[22]   :  */
        unsigned int  uart_srst_dis           : 1;  /* bit[23]   :  */
        unsigned int  reserved_3              : 8;  /* bit[24-31]: 保留。 */
    } reg;
} BBPSCTRL_LTE_PD_SRST_DIS_UNION;
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_slp_srst_dis_START         (1)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_slp_srst_dis_END           (1)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_axim_srst_dis_START        (2)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_axim_srst_dis_END          (2)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdt_srst_dis_START         (3)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdt_srst_dis_END           (3)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_rfin_srst_dis_START        (4)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_rfin_srst_dis_END          (4)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_fpu_srst_dis_START         (5)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_fpu_srst_dis_END           (5)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_ul_srst_dis_START          (6)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_ul_srst_dis_END            (6)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdu_srst_dis_START         (8)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdu_srst_dis_END           (8)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_cqi_srst_dis_START         (9)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_cqi_srst_dis_END           (9)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdf_srst_dis_START         (10)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdf_srst_dis_END           (10)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pb_srst_dis_START          (11)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pb_srst_dis_END            (11)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_vdl_srst_dis_START         (12)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_vdl_srst_dis_END           (12)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_srst_dis_START     (13)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_srst_dis_END       (13)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_2x_srst_dis_START  (14)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_2x_srst_dis_END    (14)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch1_srst_dis_START     (15)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch1_srst_dis_END       (15)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_int_srst_dis_START         (22)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_int_srst_dis_END           (22)
#define BBPSCTRL_LTE_PD_SRST_DIS_uart_srst_dis_START            (23)
#define BBPSCTRL_LTE_PD_SRST_DIS_uart_srst_dis_END              (23)


/*****************************************************************************
 结构名    : BBPSCTRL_LTE_PD_SRST_STSTUS_UNION
 结构说明  : LTE_PD_SRST_STSTUS 寄存器结构定义。地址偏移量:0x0098，初值:0xFFFFFFFF，宽度:32
 寄存器说明: LTE电源域复位请求状态
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_srst_ststus_reg;
    struct
    {
        unsigned int  reserved_0                 : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_srst_status        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_srst_status       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_srst_status        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_srst_status       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_srst_status        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_srst_status         : 1;  /* bit[6]    :  */
        unsigned int  reserved_1                 : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_srst_status        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_srst_status        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_srst_status        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_srst_status         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_srst_status        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_srst_status    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_srst_status : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_srst_status    : 1;  /* bit[15]   :  */
        unsigned int  reserved_2                 : 6;  /* bit[16-21]:  */
        unsigned int  lte_int_srst_status        : 1;  /* bit[22]   :  */
        unsigned int  uart_srst_status           : 1;  /* bit[23]   :  */
        unsigned int  reserved_3                 : 8;  /* bit[24-31]: 保留。 */
    } reg;
} BBPSCTRL_LTE_PD_SRST_STSTUS_UNION;
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_slp_srst_status_START         (1)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_slp_srst_status_END           (1)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_axim_srst_status_START        (2)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_axim_srst_status_END          (2)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdt_srst_status_START         (3)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdt_srst_status_END           (3)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_rfin_srst_status_START        (4)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_rfin_srst_status_END          (4)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_fpu_srst_status_START         (5)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_fpu_srst_status_END           (5)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_ul_srst_status_START          (6)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_ul_srst_status_END            (6)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdu_srst_status_START         (8)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdu_srst_status_END           (8)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_cqi_srst_status_START         (9)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_cqi_srst_status_END           (9)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdf_srst_status_START         (10)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdf_srst_status_END           (10)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pb_srst_status_START          (11)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pb_srst_status_END            (11)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_vdl_srst_status_START         (12)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_vdl_srst_status_END           (12)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_srst_status_START     (13)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_srst_status_END       (13)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_2x_srst_status_START  (14)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_2x_srst_status_END    (14)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch1_srst_status_START     (15)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch1_srst_status_END       (15)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_int_srst_status_START         (22)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_int_srst_status_END           (22)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_uart_srst_status_START            (23)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_uart_srst_status_END              (23)


/*****************************************************************************
 结构名    : BBPSCTRL_WTC_PD_CLK_EN_UNION
 结构说明  : WTC_PD_CLK_EN 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: WTC电源域时钟使能
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_clk_en_reg;
    struct
    {
        unsigned int  clk_61m_wbbp_top2_en  : 1;  /* bit[0]    :  */
        unsigned int  clk_122m_wbbp_top2_en : 1;  /* bit[1]    :  */
        unsigned int  clk_245m_wbbp_top2_en : 1;  /* bit[2]    :  */
        unsigned int  clk_122m_tw_en        : 1;  /* bit[3]    :  */
        unsigned int  clk_122m_twc_en       : 1;  /* bit[4]    :  */
        unsigned int  clk_122m_tds_en       : 1;  /* bit[5]    :  */
        unsigned int  clk_245m_tds_en       : 1;  /* bit[6]    :  */
        unsigned int  clk_245m_cbbp_en      : 1;  /* bit[7]    :  */
        unsigned int  clk_61m_wbbp_cs_en    : 1;  /* bit[8]    :  */
        unsigned int  clk_122m_wbbp_cs_en   : 1;  /* bit[9]    :  */
        unsigned int  clk_122m_cbbp_en      : 1;  /* bit[10]   :  */
        unsigned int  clk_122m_wc_en        : 1;  /* bit[11]   :  */
        unsigned int  clk_61m_tw_en         : 1;  /* bit[12]   :  */
        unsigned int  clk_245m_tw_en        : 1;  /* bit[13]   :  */
        unsigned int  clk_19m_cs_en         : 1;  /* bit[14]   :  */
        unsigned int  reserved              : 17; /* bit[15-31]: 保留。 */
    } reg;
} BBPSCTRL_WTC_PD_CLK_EN_UNION;
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_top2_en_START   (0)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_top2_en_END     (0)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_top2_en_START  (1)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_top2_en_END    (1)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_wbbp_top2_en_START  (2)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_wbbp_top2_en_END    (2)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tw_en_START         (3)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tw_en_END           (3)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_twc_en_START        (4)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_twc_en_END          (4)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tds_en_START        (5)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tds_en_END          (5)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tds_en_START        (6)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tds_en_END          (6)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_cbbp_en_START       (7)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_cbbp_en_END         (7)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_cs_en_START     (8)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_cs_en_END       (8)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_cs_en_START    (9)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_cs_en_END      (9)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_cbbp_en_START       (10)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_cbbp_en_END         (10)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wc_en_START         (11)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wc_en_END           (11)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_tw_en_START          (12)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_tw_en_END            (12)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tw_en_START         (13)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tw_en_END           (13)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_19m_cs_en_START          (14)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_19m_cs_en_END            (14)


/*****************************************************************************
 结构名    : BBPSCTRL_WTC_PD_CLK_DIS_UNION
 结构说明  : WTC_PD_CLK_DIS 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
 寄存器说明: WTC电源域时钟关闭
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_clk_dis_reg;
    struct
    {
        unsigned int  clk_61m_wbbp_top2_dis  : 1;  /* bit[0]    :  */
        unsigned int  clk_122m_wbbp_top2_dis : 1;  /* bit[1]    :  */
        unsigned int  clk_245m_wbbp_top2_dis : 1;  /* bit[2]    :  */
        unsigned int  clk_122m_tw_dis        : 1;  /* bit[3]    :  */
        unsigned int  clk_122m_twc_dis       : 1;  /* bit[4]    :  */
        unsigned int  clk_122m_tds_dis       : 1;  /* bit[5]    :  */
        unsigned int  clk_245m_tds_dis       : 1;  /* bit[6]    :  */
        unsigned int  clk_245m_cbbp_dis      : 1;  /* bit[7]    :  */
        unsigned int  clk_61m_wbbp_cs_dis    : 1;  /* bit[8]    :  */
        unsigned int  clk_122m_wbbp_cs_dis   : 1;  /* bit[9]    :  */
        unsigned int  clk_122m_cbbp_dis      : 1;  /* bit[10]   :  */
        unsigned int  clk_122m_wc_dis        : 1;  /* bit[11]   :  */
        unsigned int  clk_61m_tw_dis         : 1;  /* bit[12]   :  */
        unsigned int  clk_245m_tw_dis        : 1;  /* bit[13]   :  */
        unsigned int  clk_19m_cs_dis         : 1;  /* bit[14]   :  */
        unsigned int  reserved               : 17; /* bit[15-31]: 保留。 */
    } reg;
} BBPSCTRL_WTC_PD_CLK_DIS_UNION;
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_top2_dis_START   (0)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_top2_dis_END     (0)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_top2_dis_START  (1)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_top2_dis_END    (1)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_wbbp_top2_dis_START  (2)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_wbbp_top2_dis_END    (2)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tw_dis_START         (3)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tw_dis_END           (3)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_twc_dis_START        (4)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_twc_dis_END          (4)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tds_dis_START        (5)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tds_dis_END          (5)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tds_dis_START        (6)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tds_dis_END          (6)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_cbbp_dis_START       (7)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_cbbp_dis_END         (7)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_cs_dis_START     (8)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_cs_dis_END       (8)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_cs_dis_START    (9)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_cs_dis_END      (9)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_cbbp_dis_START       (10)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_cbbp_dis_END         (10)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wc_dis_START         (11)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wc_dis_END           (11)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_tw_dis_START          (12)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_tw_dis_END            (12)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tw_dis_START         (13)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tw_dis_END           (13)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_19m_cs_dis_START          (14)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_19m_cs_dis_END            (14)


/*****************************************************************************
 结构名    : BBPSCTRL_WTC_PD_CLK_STSTUS_UNION
 结构说明  : WTC_PD_CLK_STSTUS 寄存器结构定义。地址偏移量:0x00A8，初值:0x00000000，宽度:32
 寄存器说明: WTC电源域时钟门控状态
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_clk_ststus_reg;
    struct
    {
        unsigned int  clk_61m_wbbp_top2_status  : 1;  /* bit[0]    :  */
        unsigned int  clk_122m_wbbp_top2_status : 1;  /* bit[1]    :  */
        unsigned int  clk_245m_wbbp_top2_status : 1;  /* bit[2]    :  */
        unsigned int  clk_122m_tw_status        : 1;  /* bit[3]    :  */
        unsigned int  clk_122m_twc_status       : 1;  /* bit[4]    :  */
        unsigned int  clk_122m_tds_status       : 1;  /* bit[5]    :  */
        unsigned int  clk_245m_tds_status       : 1;  /* bit[6]    :  */
        unsigned int  clk_245m_cbbp_status      : 1;  /* bit[7]    :  */
        unsigned int  clk_61m_wbbp_cs_status    : 1;  /* bit[8]    :  */
        unsigned int  clk_122m_wbbp_cs_status   : 1;  /* bit[9]    :  */
        unsigned int  clk_122m_cbbp_status      : 1;  /* bit[10]   :  */
        unsigned int  clk_122m_wc_status        : 1;  /* bit[11]   :  */
        unsigned int  clk_61m_tw_status         : 1;  /* bit[12]   :  */
        unsigned int  clk_245m_tw_status        : 1;  /* bit[13]   :  */
        unsigned int  clk_19m_cs_status         : 1;  /* bit[14]   :  */
        unsigned int  reserved                  : 17; /* bit[15-31]: 保留。 */
    } reg;
} BBPSCTRL_WTC_PD_CLK_STSTUS_UNION;
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_top2_status_START   (0)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_top2_status_END     (0)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_top2_status_START  (1)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_top2_status_END    (1)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_wbbp_top2_status_START  (2)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_wbbp_top2_status_END    (2)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tw_status_START         (3)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tw_status_END           (3)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_twc_status_START        (4)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_twc_status_END          (4)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tds_status_START        (5)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tds_status_END          (5)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tds_status_START        (6)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tds_status_END          (6)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_cbbp_status_START       (7)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_cbbp_status_END         (7)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_cs_status_START     (8)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_cs_status_END       (8)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_cs_status_START    (9)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_cs_status_END      (9)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_cbbp_status_START       (10)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_cbbp_status_END         (10)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wc_status_START         (11)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wc_status_END           (11)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_tw_status_START          (12)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_tw_status_END            (12)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tw_status_START         (13)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tw_status_END           (13)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_19m_cs_status_START          (14)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_19m_cs_status_END            (14)


/*****************************************************************************
 结构名    : BBPSCTRL_WTC_PD_SRST_REQ_UNION
 结构说明  : WTC_PD_SRST_REQ 寄存器结构定义。地址偏移量:0x00B0，初值:0x00000000，宽度:32
 寄存器说明: WTC电源域复位请求使能
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_srst_req_reg;
    struct
    {
        unsigned int  rst_61m_wbbp_top2_req  : 1;  /* bit[0]    :  */
        unsigned int  rst_122m_wbbp_top2_req : 1;  /* bit[1]    :  */
        unsigned int  rst_245m_wbbp_top2_req : 1;  /* bit[2]    :  */
        unsigned int  rst_122m_tw_req        : 1;  /* bit[3]    :  */
        unsigned int  rst_122m_twc_req       : 1;  /* bit[4]    :  */
        unsigned int  rst_122m_tds_req       : 1;  /* bit[5]    :  */
        unsigned int  rst_245m_tds_req       : 1;  /* bit[6]    :  */
        unsigned int  rst_245m_cbbp_req      : 1;  /* bit[7]    :  */
        unsigned int  rst_61m_wbbp_cs_req    : 1;  /* bit[8]    :  */
        unsigned int  rst_122m_wbbp_cs_req   : 1;  /* bit[9]    :  */
        unsigned int  rst_122m_cbbp_req      : 1;  /* bit[10]   :  */
        unsigned int  rst_122m_wc_req        : 1;  /* bit[11]   :  */
        unsigned int  rst_61m_tw_req         : 1;  /* bit[12]   :  */
        unsigned int  rst_245m_tw_req        : 1;  /* bit[13]   :  */
        unsigned int  rst_19m_cs_req         : 1;  /* bit[14]   :  */
        unsigned int  rst_32k_cs_req         : 1;  /* bit[15]   :  */
        unsigned int  reserved               : 16; /* bit[16-31]: 保留。 */
    } reg;
} BBPSCTRL_WTC_PD_SRST_REQ_UNION;
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_top2_req_START   (0)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_top2_req_END     (0)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_top2_req_START  (1)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_top2_req_END    (1)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_wbbp_top2_req_START  (2)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_wbbp_top2_req_END    (2)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tw_req_START         (3)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tw_req_END           (3)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_twc_req_START        (4)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_twc_req_END          (4)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tds_req_START        (5)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tds_req_END          (5)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tds_req_START        (6)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tds_req_END          (6)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_cbbp_req_START       (7)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_cbbp_req_END         (7)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_cs_req_START     (8)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_cs_req_END       (8)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_cs_req_START    (9)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_cs_req_END      (9)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_cbbp_req_START       (10)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_cbbp_req_END         (10)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wc_req_START         (11)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wc_req_END           (11)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_tw_req_START          (12)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_tw_req_END            (12)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tw_req_START         (13)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tw_req_END           (13)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_19m_cs_req_START          (14)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_19m_cs_req_END            (14)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_32k_cs_req_START          (15)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_32k_cs_req_END            (15)


/*****************************************************************************
 结构名    : BBPSCTRL_WTC_PD_SRST_DIS_UNION
 结构说明  : WTC_PD_SRST_DIS 寄存器结构定义。地址偏移量:0x00B4，初值:0x00000000，宽度:32
 寄存器说明: WTC电源域复位请求清除
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_srst_dis_reg;
    struct
    {
        unsigned int  rst_61m_wbbp_top2_dis  : 1;  /* bit[0]    :  */
        unsigned int  rst_122m_wbbp_top2_dis : 1;  /* bit[1]    :  */
        unsigned int  rst_245m_wbbp_top2_dis : 1;  /* bit[2]    :  */
        unsigned int  rst_122m_tw_dis        : 1;  /* bit[3]    :  */
        unsigned int  rst_122m_twc_dis       : 1;  /* bit[4]    :  */
        unsigned int  rst_122m_tds_dis       : 1;  /* bit[5]    :  */
        unsigned int  rst_245m_tds_dis       : 1;  /* bit[6]    :  */
        unsigned int  rst_245m_cbbp_dis      : 1;  /* bit[7]    :  */
        unsigned int  rst_61m_wbbp_cs_dis    : 1;  /* bit[8]    :  */
        unsigned int  rst_122m_wbbp_cs_dis   : 1;  /* bit[9]    :  */
        unsigned int  rst_122m_cbbp_dis      : 1;  /* bit[10]   :  */
        unsigned int  rst_122m_wc_dis        : 1;  /* bit[11]   :  */
        unsigned int  rst_61m_tw_dis         : 1;  /* bit[12]   :  */
        unsigned int  rst_245m_tw_dis        : 1;  /* bit[13]   :  */
        unsigned int  rst_19m_cs_dis         : 1;  /* bit[14]   :  */
        unsigned int  rst_32k_cs_dis         : 1;  /* bit[15]   :  */
        unsigned int  reserved               : 16; /* bit[16-31]: 保留。 */
    } reg;
} BBPSCTRL_WTC_PD_SRST_DIS_UNION;
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_top2_dis_START   (0)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_top2_dis_END     (0)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_top2_dis_START  (1)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_top2_dis_END    (1)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_wbbp_top2_dis_START  (2)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_wbbp_top2_dis_END    (2)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tw_dis_START         (3)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tw_dis_END           (3)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_twc_dis_START        (4)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_twc_dis_END          (4)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tds_dis_START        (5)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tds_dis_END          (5)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tds_dis_START        (6)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tds_dis_END          (6)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_cbbp_dis_START       (7)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_cbbp_dis_END         (7)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_cs_dis_START     (8)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_cs_dis_END       (8)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_cs_dis_START    (9)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_cs_dis_END      (9)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_cbbp_dis_START       (10)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_cbbp_dis_END         (10)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wc_dis_START         (11)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wc_dis_END           (11)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_tw_dis_START          (12)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_tw_dis_END            (12)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tw_dis_START         (13)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tw_dis_END           (13)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_19m_cs_dis_START          (14)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_19m_cs_dis_END            (14)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_32k_cs_dis_START          (15)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_32k_cs_dis_END            (15)


/*****************************************************************************
 结构名    : BBPSCTRL_WTC_PD_SRST_STATUS_UNION
 结构说明  : WTC_PD_SRST_STATUS 寄存器结构定义。地址偏移量:0x00B8，初值:0xFFFFFFFF，宽度:32
 寄存器说明: WTC电源域复位请求状态
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_srst_status_reg;
    struct
    {
        unsigned int  rst_61m_wbbp_top2_status  : 1;  /* bit[0]    :  */
        unsigned int  rst_122m_wbbp_top2_status : 1;  /* bit[1]    :  */
        unsigned int  rst_245m_wbbp_top2_status : 1;  /* bit[2]    :  */
        unsigned int  rst_122m_tw_status        : 1;  /* bit[3]    :  */
        unsigned int  rst_122m_twc_status       : 1;  /* bit[4]    :  */
        unsigned int  rst_122m_tds_status       : 1;  /* bit[5]    :  */
        unsigned int  rst_245m_tds_status       : 1;  /* bit[6]    :  */
        unsigned int  rst_245m_cbbp_status      : 1;  /* bit[7]    :  */
        unsigned int  rst_61m_wbbp_cs_status    : 1;  /* bit[8]    :  */
        unsigned int  rst_122m_wbbp_cs_status   : 1;  /* bit[9]    :  */
        unsigned int  rst_122m_cbbp_status      : 1;  /* bit[10]   :  */
        unsigned int  rst_122m_wc_status        : 1;  /* bit[11]   :  */
        unsigned int  rst_61m_tw_status         : 1;  /* bit[12]   :  */
        unsigned int  rst_245m_tw_status        : 1;  /* bit[13]   :  */
        unsigned int  rst_19m_cs_status         : 1;  /* bit[14]   :  */
        unsigned int  rst_32k_cs_status         : 1;  /* bit[15]   :  */
        unsigned int  reserved                  : 16; /* bit[16-31]: 保留。 */
    } reg;
} BBPSCTRL_WTC_PD_SRST_STATUS_UNION;
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_top2_status_START   (0)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_top2_status_END     (0)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_top2_status_START  (1)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_top2_status_END    (1)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_wbbp_top2_status_START  (2)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_wbbp_top2_status_END    (2)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tw_status_START         (3)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tw_status_END           (3)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_twc_status_START        (4)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_twc_status_END          (4)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tds_status_START        (5)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tds_status_END          (5)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tds_status_START        (6)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tds_status_END          (6)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_cbbp_status_START       (7)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_cbbp_status_END         (7)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_cs_status_START     (8)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_cs_status_END       (8)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_cs_status_START    (9)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_cs_status_END      (9)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_cbbp_status_START       (10)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_cbbp_status_END         (10)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wc_status_START         (11)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wc_status_END           (11)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_tw_status_START          (12)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_tw_status_END            (12)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tw_status_START         (13)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tw_status_END           (13)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_19m_cs_status_START          (14)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_19m_cs_status_END            (14)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_32k_cs_status_START          (15)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_32k_cs_status_END            (15)


/*****************************************************************************
 结构名    : BBPSCTRL_IRM_PD_CLK_EN_UNION
 结构说明  : IRM_PD_CLK_EN 寄存器结构定义。地址偏移量:0x00C0，初值:0x00000000，宽度:32
 寄存器说明: IRM电源域时钟使能
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_clk_en_reg;
    struct
    {
        unsigned int  irm_comm_122m_clk_en   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_clk_en         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_clk_en     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_clk_en     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_clk_en     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_clk_en   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_clk_en : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_clk_en    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_clk_en : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_clk_en    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_clk_en  : 1;  /* bit[10]   :  */
        unsigned int  reserved               : 21; /* bit[11-31]: 保留。 */
    } reg;
} BBPSCTRL_IRM_PD_CLK_EN_UNION;
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_122m_clk_en_START    (0)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_122m_clk_en_END      (0)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_imi_clk_en_START          (1)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_imi_clk_en_END            (1)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch0_clk_en_START      (2)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch0_clk_en_END        (2)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch1_clk_en_START      (3)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch1_clk_en_END        (3)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_mst_ram_clk_en_START      (4)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_mst_ram_clk_en_END        (4)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_245m_clk_en_START    (5)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_245m_clk_en_END      (5)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_2x_clk_en_START  (6)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_2x_clk_en_END    (6)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_clk_en_START     (7)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_clk_en_END       (7)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_2x_clk_en_START  (8)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_2x_clk_en_END    (8)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_clk_en_START     (9)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_clk_en_END       (9)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_soc_ap_ram_clk_en_START   (10)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_soc_ap_ram_clk_en_END     (10)


/*****************************************************************************
 结构名    : BBPSCTRL_IRM_PD_CLK_DIS_UNION
 结构说明  : IRM_PD_CLK_DIS 寄存器结构定义。地址偏移量:0x00C4，初值:0x00000000，宽度:32
 寄存器说明: IRM电源域时钟关闭
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_clk_dis_reg;
    struct
    {
        unsigned int  irm_comm_122m_clk_dis   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_clk_dis         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_clk_dis     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_clk_dis     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_clk_dis     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_clk_dis   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_clk_dis : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_clk_dis    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_clk_dis : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_clk_dis    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_clk_dis  : 1;  /* bit[10]   :  */
        unsigned int  reserved                : 21; /* bit[11-31]: 保留。 */
    } reg;
} BBPSCTRL_IRM_PD_CLK_DIS_UNION;
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_122m_clk_dis_START    (0)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_122m_clk_dis_END      (0)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_imi_clk_dis_START          (1)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_imi_clk_dis_END            (1)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch0_clk_dis_START      (2)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch0_clk_dis_END        (2)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch1_clk_dis_START      (3)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch1_clk_dis_END        (3)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_mst_ram_clk_dis_START      (4)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_mst_ram_clk_dis_END        (4)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_245m_clk_dis_START    (5)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_245m_clk_dis_END      (5)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_2x_clk_dis_START  (6)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_2x_clk_dis_END    (6)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_clk_dis_START     (7)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_clk_dis_END       (7)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_2x_clk_dis_START  (8)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_2x_clk_dis_END    (8)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_clk_dis_START     (9)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_clk_dis_END       (9)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_soc_ap_ram_clk_dis_START   (10)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_soc_ap_ram_clk_dis_END     (10)


/*****************************************************************************
 结构名    : BBPSCTRL_IRM_PD_CLK_STATUS_UNION
 结构说明  : IRM_PD_CLK_STATUS 寄存器结构定义。地址偏移量:0x00C8，初值:0x00000000，宽度:32
 寄存器说明: IRM电源域时钟门控状态
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_clk_status_reg;
    struct
    {
        unsigned int  irm_comm_122m_clk_status   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_clk_status         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_clk_status     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_clk_status     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_clk_status     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_clk_status   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_clk_status : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_clk_status    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_clk_status : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_clk_status    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_clk_status  : 1;  /* bit[10]   :  */
        unsigned int  reserved                   : 21; /* bit[11-31]: 保留。 */
    } reg;
} BBPSCTRL_IRM_PD_CLK_STATUS_UNION;
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_122m_clk_status_START    (0)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_122m_clk_status_END      (0)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_imi_clk_status_START          (1)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_imi_clk_status_END            (1)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch0_clk_status_START      (2)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch0_clk_status_END        (2)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch1_clk_status_START      (3)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch1_clk_status_END        (3)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_mst_ram_clk_status_START      (4)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_mst_ram_clk_status_END        (4)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_245m_clk_status_START    (5)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_245m_clk_status_END      (5)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_2x_clk_status_START  (6)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_2x_clk_status_END    (6)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_clk_status_START     (7)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_clk_status_END       (7)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_2x_clk_status_START  (8)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_2x_clk_status_END    (8)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_clk_status_START     (9)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_clk_status_END       (9)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_soc_ap_ram_clk_status_START   (10)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_soc_ap_ram_clk_status_END     (10)


/*****************************************************************************
 结构名    : BBPSCTRL_IRM_PD_SRST_REQ_UNION
 结构说明  : IRM_PD_SRST_REQ 寄存器结构定义。地址偏移量:0x00D0，初值:0x00000000，宽度:32
 寄存器说明: IRM电源域复位请求使能
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_srst_req_reg;
    struct
    {
        unsigned int  irm_comm_122m_srst_req   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_srst_req         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_srst_req     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_srst_req     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_srst_req     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_srst_req   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_srst_req : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_srst_req    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_srst_req : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_srst_req    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_srst_req  : 1;  /* bit[10]   :  */
        unsigned int  reserved                 : 21; /* bit[11-31]: 保留。 */
    } reg;
} BBPSCTRL_IRM_PD_SRST_REQ_UNION;
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_122m_srst_req_START    (0)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_122m_srst_req_END      (0)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_imi_srst_req_START          (1)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_imi_srst_req_END            (1)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch0_srst_req_START      (2)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch0_srst_req_END        (2)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch1_srst_req_START      (3)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch1_srst_req_END        (3)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_mst_ram_srst_req_START      (4)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_mst_ram_srst_req_END        (4)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_245m_srst_req_START    (5)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_245m_srst_req_END      (5)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_2x_srst_req_START  (6)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_2x_srst_req_END    (6)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_srst_req_START     (7)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_srst_req_END       (7)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_2x_srst_req_START  (8)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_2x_srst_req_END    (8)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_srst_req_START     (9)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_srst_req_END       (9)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_soc_ap_ram_srst_req_START   (10)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_soc_ap_ram_srst_req_END     (10)


/*****************************************************************************
 结构名    : BBPSCTRL_IRM_PD_SRST_DIS_UNION
 结构说明  : IRM_PD_SRST_DIS 寄存器结构定义。地址偏移量:0x00D4，初值:0x00000000，宽度:32
 寄存器说明: IRM电源域复位请求清除
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_srst_dis_reg;
    struct
    {
        unsigned int  irm_comm_122m_srst_dis   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_srst_dis         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_srst_dis     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_srst_dis     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_srst_dis     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_srst_dis   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_srst_dis : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_srst_dis    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_srst_dis : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_srst_dis    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_srst_dis  : 1;  /* bit[10]   :  */
        unsigned int  reserved                 : 21; /* bit[11-31]: 保留。 */
    } reg;
} BBPSCTRL_IRM_PD_SRST_DIS_UNION;
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_122m_srst_dis_START    (0)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_122m_srst_dis_END      (0)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_imi_srst_dis_START          (1)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_imi_srst_dis_END            (1)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch0_srst_dis_START      (2)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch0_srst_dis_END        (2)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch1_srst_dis_START      (3)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch1_srst_dis_END        (3)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_mst_ram_srst_dis_START      (4)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_mst_ram_srst_dis_END        (4)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_245m_srst_dis_START    (5)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_245m_srst_dis_END      (5)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_2x_srst_dis_START  (6)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_2x_srst_dis_END    (6)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_srst_dis_START     (7)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_srst_dis_END       (7)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_2x_srst_dis_START  (8)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_2x_srst_dis_END    (8)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_srst_dis_START     (9)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_srst_dis_END       (9)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_soc_ap_ram_srst_dis_START   (10)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_soc_ap_ram_srst_dis_END     (10)


/*****************************************************************************
 结构名    : BBPSCTRL_IRM_PD_SRST_STATUS_UNION
 结构说明  : IRM_PD_SRST_STATUS 寄存器结构定义。地址偏移量:0x00D8，初值:0xFFFFFFFF，宽度:32
 寄存器说明: IRM电源域复位请求状态
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_srst_status_reg;
    struct
    {
        unsigned int  irm_comm_122m_srst_status   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_srst_status         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_srst_status     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_srst_status     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_srst_status     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_srst_status   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_srst_status : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_srst_status    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_srst_status : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_srst_status    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_srst_status  : 1;  /* bit[10]   :  */
        unsigned int  reserved                    : 21; /* bit[11-31]: 保留。 */
    } reg;
} BBPSCTRL_IRM_PD_SRST_STATUS_UNION;
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_122m_srst_status_START    (0)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_122m_srst_status_END      (0)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_imi_srst_status_START          (1)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_imi_srst_status_END            (1)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch0_srst_status_START      (2)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch0_srst_status_END        (2)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch1_srst_status_START      (3)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch1_srst_status_END        (3)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_mst_ram_srst_status_START      (4)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_mst_ram_srst_status_END        (4)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_245m_srst_status_START    (5)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_245m_srst_status_END      (5)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_2x_srst_status_START  (6)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_2x_srst_status_END    (6)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_srst_status_START     (7)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_srst_status_END       (7)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_2x_srst_status_START  (8)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_2x_srst_status_END    (8)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_srst_status_START     (9)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_srst_status_END       (9)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_soc_ap_ram_srst_status_START   (10)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_soc_ap_ram_srst_status_END     (10)


/*****************************************************************************
 结构名    : BBPSCTRL_COM_CLK_EN_UNION
 结构说明  : COM_CLK_EN 寄存器结构定义。地址偏移量:0x00E0，初值:0x00000000，宽度:32
 寄存器说明: COM时钟使能
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_en_reg;
    struct
    {
        unsigned int  com_g1_clk_en       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_clk_en       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0          : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_clk_en    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_clk_en    : 1;  /* bit[4]    : l sdr模块时钟打开。
                                                               注意，在tl_dbg_clk_en的时候，同样会打开l sdr模块的时钟。 */
        unsigned int  com_tl_dma_clk_en   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_clk_en   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_clk_en   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1          : 1;  /* bit[8]    : 该位没有时钟使能。 */
        unsigned int  com_et_clk_en       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_clk_en       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_clk_en      : 1;  /* bit[11]   : 该位没有时钟使能。 */
        unsigned int  com_lte_cs_clk_en   : 1;  /* bit[12]   : 该位没有时钟使能。 */
        unsigned int  com_wc_clk_en       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_clk_en : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_clk_en : 1;  /* bit[15]   :  */
        unsigned int  com_w_tx_clk_en     : 1;  /* bit[16]   : W模式tx时钟使能。该信号需要同时打开W_SYS_CLK_EN。 */
        unsigned int  com_t_tx_clk_en     : 1;  /* bit[17]   : T模式tx时钟使能。该信号需要同时打开T_SYS_CLK_EN。 */
        unsigned int  com_c_tx_clk_en     : 1;  /* bit[18]   : C2模式tx时钟使能。该信号需要同时打开C_SYS_CLK_EN。 */
        unsigned int  com_et_sub_clk_en   : 1;  /* bit[19]   : 自研ET总线时钟使能 */
        unsigned int  com_l_et_clk_en     : 1;  /* bit[20]   : 自研ET，L时钟使能 */
        unsigned int  com_w_et_clk_en     : 1;  /* bit[21]   : 自研ET，W时钟使能 */
        unsigned int  com_mipi_clk_en     : 1;  /* bit[22]   : BBP_COMM_FE中mipi时钟使能。该时钟来自19.2M或者245.76M，选择信号见bbp_clk_ctrl。 */
        unsigned int  com_guc_dbg_clk_en  : 1;  /* bit[23]   : GUC DBG时钟使能。 */
        unsigned int  com_w_sys_clk_en    : 1;  /* bit[24]   : BBP_COMM_FE中，W模式时钟使能。 */
        unsigned int  com_t_sys_clk_en    : 1;  /* bit[25]   : BBP_COMM_FE中，T模式时钟使能 */
        unsigned int  com_c_sys_clk_en    : 1;  /* bit[26]   : BBP_COMM_FE中，C模式时钟使能 */
        unsigned int  reserved_2          : 5;  /* bit[27-31]: 保留。 */
    } reg;
} BBPSCTRL_COM_CLK_EN_UNION;
#define BBPSCTRL_COM_CLK_EN_com_g1_clk_en_START        (0)
#define BBPSCTRL_COM_CLK_EN_com_g1_clk_en_END          (0)
#define BBPSCTRL_COM_CLK_EN_com_g2_clk_en_START        (1)
#define BBPSCTRL_COM_CLK_EN_com_g2_clk_en_END          (1)
#define BBPSCTRL_COM_CLK_EN_com_g_sdr_clk_en_START     (3)
#define BBPSCTRL_COM_CLK_EN_com_g_sdr_clk_en_END       (3)
#define BBPSCTRL_COM_CLK_EN_com_l_sdr_clk_en_START     (4)
#define BBPSCTRL_COM_CLK_EN_com_l_sdr_clk_en_END       (4)
#define BBPSCTRL_COM_CLK_EN_com_tl_dma_clk_en_START    (5)
#define BBPSCTRL_COM_CLK_EN_com_tl_dma_clk_en_END      (5)
#define BBPSCTRL_COM_CLK_EN_com_tl_dbg_clk_en_START    (6)
#define BBPSCTRL_COM_CLK_EN_com_tl_dbg_clk_en_END      (6)
#define BBPSCTRL_COM_CLK_EN_com_gu_mst_clk_en_START    (7)
#define BBPSCTRL_COM_CLK_EN_com_gu_mst_clk_en_END      (7)
#define BBPSCTRL_COM_CLK_EN_com_et_clk_en_START        (9)
#define BBPSCTRL_COM_CLK_EN_com_et_clk_en_END          (9)
#define BBPSCTRL_COM_CLK_EN_com_cs_clk_en_START        (10)
#define BBPSCTRL_COM_CLK_EN_com_cs_clk_en_END          (10)
#define BBPSCTRL_COM_CLK_EN_com_sys_clk_en_START       (11)
#define BBPSCTRL_COM_CLK_EN_com_sys_clk_en_END         (11)
#define BBPSCTRL_COM_CLK_EN_com_lte_cs_clk_en_START    (12)
#define BBPSCTRL_COM_CLK_EN_com_lte_cs_clk_en_END      (12)
#define BBPSCTRL_COM_CLK_EN_com_wc_clk_en_START        (13)
#define BBPSCTRL_COM_CLK_EN_com_wc_clk_en_END          (13)
#define BBPSCTRL_COM_CLK_EN_com_uc2_122m_clk_en_START  (14)
#define BBPSCTRL_COM_CLK_EN_com_uc2_122m_clk_en_END    (14)
#define BBPSCTRL_COM_CLK_EN_com_dbg_trig_clk_en_START  (15)
#define BBPSCTRL_COM_CLK_EN_com_dbg_trig_clk_en_END    (15)
#define BBPSCTRL_COM_CLK_EN_com_w_tx_clk_en_START      (16)
#define BBPSCTRL_COM_CLK_EN_com_w_tx_clk_en_END        (16)
#define BBPSCTRL_COM_CLK_EN_com_t_tx_clk_en_START      (17)
#define BBPSCTRL_COM_CLK_EN_com_t_tx_clk_en_END        (17)
#define BBPSCTRL_COM_CLK_EN_com_c_tx_clk_en_START      (18)
#define BBPSCTRL_COM_CLK_EN_com_c_tx_clk_en_END        (18)
#define BBPSCTRL_COM_CLK_EN_com_et_sub_clk_en_START    (19)
#define BBPSCTRL_COM_CLK_EN_com_et_sub_clk_en_END      (19)
#define BBPSCTRL_COM_CLK_EN_com_l_et_clk_en_START      (20)
#define BBPSCTRL_COM_CLK_EN_com_l_et_clk_en_END        (20)
#define BBPSCTRL_COM_CLK_EN_com_w_et_clk_en_START      (21)
#define BBPSCTRL_COM_CLK_EN_com_w_et_clk_en_END        (21)
#define BBPSCTRL_COM_CLK_EN_com_mipi_clk_en_START      (22)
#define BBPSCTRL_COM_CLK_EN_com_mipi_clk_en_END        (22)
#define BBPSCTRL_COM_CLK_EN_com_guc_dbg_clk_en_START   (23)
#define BBPSCTRL_COM_CLK_EN_com_guc_dbg_clk_en_END     (23)
#define BBPSCTRL_COM_CLK_EN_com_w_sys_clk_en_START     (24)
#define BBPSCTRL_COM_CLK_EN_com_w_sys_clk_en_END       (24)
#define BBPSCTRL_COM_CLK_EN_com_t_sys_clk_en_START     (25)
#define BBPSCTRL_COM_CLK_EN_com_t_sys_clk_en_END       (25)
#define BBPSCTRL_COM_CLK_EN_com_c_sys_clk_en_START     (26)
#define BBPSCTRL_COM_CLK_EN_com_c_sys_clk_en_END       (26)


/*****************************************************************************
 结构名    : BBPSCTRL_COM_CLK_DIS_UNION
 结构说明  : COM_CLK_DIS 寄存器结构定义。地址偏移量:0x00E4，初值:0x00000000，宽度:32
 寄存器说明: COM时钟关闭
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_dis_reg;
    struct
    {
        unsigned int  com_g1_clk_dis       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_clk_dis       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0           : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_clk_dis    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_clk_dis    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_clk_dis   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_clk_dis   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_clk_dis   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1           : 1;  /* bit[8]    : 该位没有时钟使能。 */
        unsigned int  com_et_clk_dis       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_clk_dis       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_clk_dis      : 1;  /* bit[11]   : 该位没有时钟使能。 */
        unsigned int  com_lte_cs_clk_dis   : 1;  /* bit[12]   : 该位没有时钟使能。 */
        unsigned int  com_wc_clk_dis       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_clk_dis : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_clk_dis : 1;  /* bit[15]   :  */
        unsigned int  com_w_tx_clk_dis     : 1;  /* bit[16]   :  */
        unsigned int  com_t_tx_clk_dis     : 1;  /* bit[17]   :  */
        unsigned int  com_c_tx_clk_dis     : 1;  /* bit[18]   :  */
        unsigned int  com_et_sub_clk_dis   : 1;  /* bit[19]   : 自研ET总线时钟关闭 */
        unsigned int  com_l_et_clk_dis     : 1;  /* bit[20]   : 自研ET，L时钟关闭 */
        unsigned int  com_w_et_clk_dis     : 1;  /* bit[21]   : 自研ET，W时钟关闭 */
        unsigned int  com_mipi_clk_dis     : 1;  /* bit[22]   : BBP_COMM_FE中mipi时钟关闭 */
        unsigned int  com_guc_dbg_clk_dis  : 1;  /* bit[23]   : GUC DBG时钟关闭 */
        unsigned int  com_w_sys_clk_dis    : 1;  /* bit[24]   : BBP_COMM_FE中，W模式时钟关闭 */
        unsigned int  com_t_sys_clk_dis    : 1;  /* bit[25]   : BBP_COMM_FE中，T模式时钟关闭 */
        unsigned int  com_c_sys_clk_dis    : 1;  /* bit[26]   : BBP_COMM_FE中，C模式时钟关闭 */
        unsigned int  reserved_2           : 5;  /* bit[27-31]: 保留。 */
    } reg;
} BBPSCTRL_COM_CLK_DIS_UNION;
#define BBPSCTRL_COM_CLK_DIS_com_g1_clk_dis_START        (0)
#define BBPSCTRL_COM_CLK_DIS_com_g1_clk_dis_END          (0)
#define BBPSCTRL_COM_CLK_DIS_com_g2_clk_dis_START        (1)
#define BBPSCTRL_COM_CLK_DIS_com_g2_clk_dis_END          (1)
#define BBPSCTRL_COM_CLK_DIS_com_g_sdr_clk_dis_START     (3)
#define BBPSCTRL_COM_CLK_DIS_com_g_sdr_clk_dis_END       (3)
#define BBPSCTRL_COM_CLK_DIS_com_l_sdr_clk_dis_START     (4)
#define BBPSCTRL_COM_CLK_DIS_com_l_sdr_clk_dis_END       (4)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dma_clk_dis_START    (5)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dma_clk_dis_END      (5)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dbg_clk_dis_START    (6)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dbg_clk_dis_END      (6)
#define BBPSCTRL_COM_CLK_DIS_com_gu_mst_clk_dis_START    (7)
#define BBPSCTRL_COM_CLK_DIS_com_gu_mst_clk_dis_END      (7)
#define BBPSCTRL_COM_CLK_DIS_com_et_clk_dis_START        (9)
#define BBPSCTRL_COM_CLK_DIS_com_et_clk_dis_END          (9)
#define BBPSCTRL_COM_CLK_DIS_com_cs_clk_dis_START        (10)
#define BBPSCTRL_COM_CLK_DIS_com_cs_clk_dis_END          (10)
#define BBPSCTRL_COM_CLK_DIS_com_sys_clk_dis_START       (11)
#define BBPSCTRL_COM_CLK_DIS_com_sys_clk_dis_END         (11)
#define BBPSCTRL_COM_CLK_DIS_com_lte_cs_clk_dis_START    (12)
#define BBPSCTRL_COM_CLK_DIS_com_lte_cs_clk_dis_END      (12)
#define BBPSCTRL_COM_CLK_DIS_com_wc_clk_dis_START        (13)
#define BBPSCTRL_COM_CLK_DIS_com_wc_clk_dis_END          (13)
#define BBPSCTRL_COM_CLK_DIS_com_uc2_122m_clk_dis_START  (14)
#define BBPSCTRL_COM_CLK_DIS_com_uc2_122m_clk_dis_END    (14)
#define BBPSCTRL_COM_CLK_DIS_com_dbg_trig_clk_dis_START  (15)
#define BBPSCTRL_COM_CLK_DIS_com_dbg_trig_clk_dis_END    (15)
#define BBPSCTRL_COM_CLK_DIS_com_w_tx_clk_dis_START      (16)
#define BBPSCTRL_COM_CLK_DIS_com_w_tx_clk_dis_END        (16)
#define BBPSCTRL_COM_CLK_DIS_com_t_tx_clk_dis_START      (17)
#define BBPSCTRL_COM_CLK_DIS_com_t_tx_clk_dis_END        (17)
#define BBPSCTRL_COM_CLK_DIS_com_c_tx_clk_dis_START      (18)
#define BBPSCTRL_COM_CLK_DIS_com_c_tx_clk_dis_END        (18)
#define BBPSCTRL_COM_CLK_DIS_com_et_sub_clk_dis_START    (19)
#define BBPSCTRL_COM_CLK_DIS_com_et_sub_clk_dis_END      (19)
#define BBPSCTRL_COM_CLK_DIS_com_l_et_clk_dis_START      (20)
#define BBPSCTRL_COM_CLK_DIS_com_l_et_clk_dis_END        (20)
#define BBPSCTRL_COM_CLK_DIS_com_w_et_clk_dis_START      (21)
#define BBPSCTRL_COM_CLK_DIS_com_w_et_clk_dis_END        (21)
#define BBPSCTRL_COM_CLK_DIS_com_mipi_clk_dis_START      (22)
#define BBPSCTRL_COM_CLK_DIS_com_mipi_clk_dis_END        (22)
#define BBPSCTRL_COM_CLK_DIS_com_guc_dbg_clk_dis_START   (23)
#define BBPSCTRL_COM_CLK_DIS_com_guc_dbg_clk_dis_END     (23)
#define BBPSCTRL_COM_CLK_DIS_com_w_sys_clk_dis_START     (24)
#define BBPSCTRL_COM_CLK_DIS_com_w_sys_clk_dis_END       (24)
#define BBPSCTRL_COM_CLK_DIS_com_t_sys_clk_dis_START     (25)
#define BBPSCTRL_COM_CLK_DIS_com_t_sys_clk_dis_END       (25)
#define BBPSCTRL_COM_CLK_DIS_com_c_sys_clk_dis_START     (26)
#define BBPSCTRL_COM_CLK_DIS_com_c_sys_clk_dis_END       (26)


/*****************************************************************************
 结构名    : BBPSCTRL_COM_CLK_STATUS_UNION
 结构说明  : COM_CLK_STATUS 寄存器结构定义。地址偏移量:0x00E8，初值:0x00000000，宽度:32
 寄存器说明: COM时钟门控状态
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_status_reg;
    struct
    {
        unsigned int  com_g1_clk_status       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_clk_status       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0              : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_clk_status    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_clk_status    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_clk_status   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_clk_status   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_clk_status   : 1;  /* bit[7]    :  */
        unsigned int  wcs_245_clk_status      : 1;  /* bit[8]    : 个组合的时钟状态。0xE0/0xE4对应bit位，无时钟使能 */
        unsigned int  com_et_clk_status       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_clk_status       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_clk_status      : 1;  /* bit[11]   : 个组合的时钟状态。0xE0/0xE4对应bit位，无时钟使能 */
        unsigned int  com_lte_cs_clk_status   : 1;  /* bit[12]   : 个组合的时钟状态。0xE0/0xE4对应bit位，无时钟使能 */
        unsigned int  com_wc_clk_status       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_clk_status : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_clk_status : 1;  /* bit[15]   :  */
        unsigned int  com_w_tx_clk_status     : 1;  /* bit[16]   :  */
        unsigned int  com_t_tx_clk_status     : 1;  /* bit[17]   :  */
        unsigned int  com_c_tx_clk_status     : 1;  /* bit[18]   :  */
        unsigned int  com_et_sub_clk_status   : 1;  /* bit[19]   : 自研ET总线时钟状态 */
        unsigned int  com_l_et_clk_status     : 1;  /* bit[20]   : 自研ET，L时钟状态 */
        unsigned int  com_w_et_clk_status     : 1;  /* bit[21]   : 自研ET，W时钟状态 */
        unsigned int  com_mipi_clk_status     : 1;  /* bit[22]   : BBP_COMM_FE中mipi时钟状态 */
        unsigned int  com_guc_dbg_clk_status  : 1;  /* bit[23]   : GUC DBG时钟状态 */
        unsigned int  com_w_sys_clk_status    : 1;  /* bit[24]   : BBP_COMM_FE中，W模式时钟状态 */
        unsigned int  com_t_sys_clk_status    : 1;  /* bit[25]   : BBP_COMM_FE中，T模式时钟状态 */
        unsigned int  com_c_sys_clk_status    : 1;  /* bit[26]   : BBP_COMM_FE中，C模式时钟状态 */
        unsigned int  reserved_1              : 5;  /* bit[27-31]: 保留。 */
    } reg;
} BBPSCTRL_COM_CLK_STATUS_UNION;
#define BBPSCTRL_COM_CLK_STATUS_com_g1_clk_status_START        (0)
#define BBPSCTRL_COM_CLK_STATUS_com_g1_clk_status_END          (0)
#define BBPSCTRL_COM_CLK_STATUS_com_g2_clk_status_START        (1)
#define BBPSCTRL_COM_CLK_STATUS_com_g2_clk_status_END          (1)
#define BBPSCTRL_COM_CLK_STATUS_com_g_sdr_clk_status_START     (3)
#define BBPSCTRL_COM_CLK_STATUS_com_g_sdr_clk_status_END       (3)
#define BBPSCTRL_COM_CLK_STATUS_com_l_sdr_clk_status_START     (4)
#define BBPSCTRL_COM_CLK_STATUS_com_l_sdr_clk_status_END       (4)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dma_clk_status_START    (5)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dma_clk_status_END      (5)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dbg_clk_status_START    (6)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dbg_clk_status_END      (6)
#define BBPSCTRL_COM_CLK_STATUS_com_gu_mst_clk_status_START    (7)
#define BBPSCTRL_COM_CLK_STATUS_com_gu_mst_clk_status_END      (7)
#define BBPSCTRL_COM_CLK_STATUS_wcs_245_clk_status_START       (8)
#define BBPSCTRL_COM_CLK_STATUS_wcs_245_clk_status_END         (8)
#define BBPSCTRL_COM_CLK_STATUS_com_et_clk_status_START        (9)
#define BBPSCTRL_COM_CLK_STATUS_com_et_clk_status_END          (9)
#define BBPSCTRL_COM_CLK_STATUS_com_cs_clk_status_START        (10)
#define BBPSCTRL_COM_CLK_STATUS_com_cs_clk_status_END          (10)
#define BBPSCTRL_COM_CLK_STATUS_com_sys_clk_status_START       (11)
#define BBPSCTRL_COM_CLK_STATUS_com_sys_clk_status_END         (11)
#define BBPSCTRL_COM_CLK_STATUS_com_lte_cs_clk_status_START    (12)
#define BBPSCTRL_COM_CLK_STATUS_com_lte_cs_clk_status_END      (12)
#define BBPSCTRL_COM_CLK_STATUS_com_wc_clk_status_START        (13)
#define BBPSCTRL_COM_CLK_STATUS_com_wc_clk_status_END          (13)
#define BBPSCTRL_COM_CLK_STATUS_com_uc2_122m_clk_status_START  (14)
#define BBPSCTRL_COM_CLK_STATUS_com_uc2_122m_clk_status_END    (14)
#define BBPSCTRL_COM_CLK_STATUS_com_dbg_trig_clk_status_START  (15)
#define BBPSCTRL_COM_CLK_STATUS_com_dbg_trig_clk_status_END    (15)
#define BBPSCTRL_COM_CLK_STATUS_com_w_tx_clk_status_START      (16)
#define BBPSCTRL_COM_CLK_STATUS_com_w_tx_clk_status_END        (16)
#define BBPSCTRL_COM_CLK_STATUS_com_t_tx_clk_status_START      (17)
#define BBPSCTRL_COM_CLK_STATUS_com_t_tx_clk_status_END        (17)
#define BBPSCTRL_COM_CLK_STATUS_com_c_tx_clk_status_START      (18)
#define BBPSCTRL_COM_CLK_STATUS_com_c_tx_clk_status_END        (18)
#define BBPSCTRL_COM_CLK_STATUS_com_et_sub_clk_status_START    (19)
#define BBPSCTRL_COM_CLK_STATUS_com_et_sub_clk_status_END      (19)
#define BBPSCTRL_COM_CLK_STATUS_com_l_et_clk_status_START      (20)
#define BBPSCTRL_COM_CLK_STATUS_com_l_et_clk_status_END        (20)
#define BBPSCTRL_COM_CLK_STATUS_com_w_et_clk_status_START      (21)
#define BBPSCTRL_COM_CLK_STATUS_com_w_et_clk_status_END        (21)
#define BBPSCTRL_COM_CLK_STATUS_com_mipi_clk_status_START      (22)
#define BBPSCTRL_COM_CLK_STATUS_com_mipi_clk_status_END        (22)
#define BBPSCTRL_COM_CLK_STATUS_com_guc_dbg_clk_status_START   (23)
#define BBPSCTRL_COM_CLK_STATUS_com_guc_dbg_clk_status_END     (23)
#define BBPSCTRL_COM_CLK_STATUS_com_w_sys_clk_status_START     (24)
#define BBPSCTRL_COM_CLK_STATUS_com_w_sys_clk_status_END       (24)
#define BBPSCTRL_COM_CLK_STATUS_com_t_sys_clk_status_START     (25)
#define BBPSCTRL_COM_CLK_STATUS_com_t_sys_clk_status_END       (25)
#define BBPSCTRL_COM_CLK_STATUS_com_c_sys_clk_status_START     (26)
#define BBPSCTRL_COM_CLK_STATUS_com_c_sys_clk_status_END       (26)


/*****************************************************************************
 结构名    : BBPSCTRL_COM_SRST_REQ_UNION
 结构说明  : COM_SRST_REQ 寄存器结构定义。地址偏移量:0x00F0，初值:0x00000000，宽度:32
 寄存器说明: COM复位请求使能
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_req_reg;
    struct
    {
        unsigned int  com_g1_srst_req       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_srst_req       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0            : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_srst_req    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_srst_req    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_srst_req   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_srst_req   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_srst_req   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1            : 1;  /* bit[8]    :  */
        unsigned int  com_et_srst_req       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_srst_req       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_srst_req      : 1;  /* bit[11]   :  */
        unsigned int  com_lte_cs_srst_req   : 1;  /* bit[12]   :  */
        unsigned int  com_wc_srst_req       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_srst_req : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_srst_req : 1;  /* bit[15]   :  */
        unsigned int  reserved_2            : 3;  /* bit[16-18]:  */
        unsigned int  com_et_sub_srst_req   : 1;  /* bit[19]   : 自研ET总线复位 */
        unsigned int  reserved_3            : 2;  /* bit[20-21]: 保留 */
        unsigned int  com_mipi_srst_req     : 1;  /* bit[22]   : BBP_COMM_FE中mipi时钟域复位，高有效。 */
        unsigned int  com_guc_dbg_srst_req  : 1;  /* bit[23]   : GUC DBG复位请求 */
        unsigned int  com_w_sys_srst_req    : 1;  /* bit[24]   : BBP_COMM_FE中，W模式复位请求 */
        unsigned int  com_t_sys_srst_req    : 1;  /* bit[25]   : BBP_COMM_FE中，T模式复位请求 */
        unsigned int  com_c_sys_srst_req    : 1;  /* bit[26]   : BBP_COMM_FE中，C模式复位请求 */
        unsigned int  reserved_4            : 5;  /* bit[27-31]: 保留。 */
    } reg;
} BBPSCTRL_COM_SRST_REQ_UNION;
#define BBPSCTRL_COM_SRST_REQ_com_g1_srst_req_START        (0)
#define BBPSCTRL_COM_SRST_REQ_com_g1_srst_req_END          (0)
#define BBPSCTRL_COM_SRST_REQ_com_g2_srst_req_START        (1)
#define BBPSCTRL_COM_SRST_REQ_com_g2_srst_req_END          (1)
#define BBPSCTRL_COM_SRST_REQ_com_g_sdr_srst_req_START     (3)
#define BBPSCTRL_COM_SRST_REQ_com_g_sdr_srst_req_END       (3)
#define BBPSCTRL_COM_SRST_REQ_com_l_sdr_srst_req_START     (4)
#define BBPSCTRL_COM_SRST_REQ_com_l_sdr_srst_req_END       (4)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dma_srst_req_START    (5)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dma_srst_req_END      (5)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dbg_srst_req_START    (6)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dbg_srst_req_END      (6)
#define BBPSCTRL_COM_SRST_REQ_com_gu_mst_srst_req_START    (7)
#define BBPSCTRL_COM_SRST_REQ_com_gu_mst_srst_req_END      (7)
#define BBPSCTRL_COM_SRST_REQ_com_et_srst_req_START        (9)
#define BBPSCTRL_COM_SRST_REQ_com_et_srst_req_END          (9)
#define BBPSCTRL_COM_SRST_REQ_com_cs_srst_req_START        (10)
#define BBPSCTRL_COM_SRST_REQ_com_cs_srst_req_END          (10)
#define BBPSCTRL_COM_SRST_REQ_com_sys_srst_req_START       (11)
#define BBPSCTRL_COM_SRST_REQ_com_sys_srst_req_END         (11)
#define BBPSCTRL_COM_SRST_REQ_com_lte_cs_srst_req_START    (12)
#define BBPSCTRL_COM_SRST_REQ_com_lte_cs_srst_req_END      (12)
#define BBPSCTRL_COM_SRST_REQ_com_wc_srst_req_START        (13)
#define BBPSCTRL_COM_SRST_REQ_com_wc_srst_req_END          (13)
#define BBPSCTRL_COM_SRST_REQ_com_uc2_122m_srst_req_START  (14)
#define BBPSCTRL_COM_SRST_REQ_com_uc2_122m_srst_req_END    (14)
#define BBPSCTRL_COM_SRST_REQ_com_dbg_trig_srst_req_START  (15)
#define BBPSCTRL_COM_SRST_REQ_com_dbg_trig_srst_req_END    (15)
#define BBPSCTRL_COM_SRST_REQ_com_et_sub_srst_req_START    (19)
#define BBPSCTRL_COM_SRST_REQ_com_et_sub_srst_req_END      (19)
#define BBPSCTRL_COM_SRST_REQ_com_mipi_srst_req_START      (22)
#define BBPSCTRL_COM_SRST_REQ_com_mipi_srst_req_END        (22)
#define BBPSCTRL_COM_SRST_REQ_com_guc_dbg_srst_req_START   (23)
#define BBPSCTRL_COM_SRST_REQ_com_guc_dbg_srst_req_END     (23)
#define BBPSCTRL_COM_SRST_REQ_com_w_sys_srst_req_START     (24)
#define BBPSCTRL_COM_SRST_REQ_com_w_sys_srst_req_END       (24)
#define BBPSCTRL_COM_SRST_REQ_com_t_sys_srst_req_START     (25)
#define BBPSCTRL_COM_SRST_REQ_com_t_sys_srst_req_END       (25)
#define BBPSCTRL_COM_SRST_REQ_com_c_sys_srst_req_START     (26)
#define BBPSCTRL_COM_SRST_REQ_com_c_sys_srst_req_END       (26)


/*****************************************************************************
 结构名    : BBPSCTRL_COM_SRST_DIS_UNION
 结构说明  : COM_SRST_DIS 寄存器结构定义。地址偏移量:0x00F4，初值:0x00000000，宽度:32
 寄存器说明: COM复位请求清除
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_dis_reg;
    struct
    {
        unsigned int  com_g1_srst_dis       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_srst_dis       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0            : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_srst_dis    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_srst_dis    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_srst_dis   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_srst_dis   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_srst_dis   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1            : 1;  /* bit[8]    :  */
        unsigned int  com_et_srst_dis       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_srst_dis       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_srst_dis      : 1;  /* bit[11]   :  */
        unsigned int  com_lte_cs_srst_dis   : 1;  /* bit[12]   :  */
        unsigned int  com_wc_srst_dis       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_srst_dis : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_srst_dis : 1;  /* bit[15]   :  */
        unsigned int  reserved_2            : 3;  /* bit[16-18]:  */
        unsigned int  com_et_sub_srst_dis   : 1;  /* bit[19]   : 自研ET总线复位关闭 */
        unsigned int  reserved_3            : 2;  /* bit[20-21]: 保留 */
        unsigned int  com_mipi_srst_dis     : 1;  /* bit[22]   : BBP_COMM_FE中mipi时钟域解复位。写1清零。 */
        unsigned int  com_guc_dbg_srst_dis  : 1;  /* bit[23]   : GUC DBG复位解除 */
        unsigned int  com_w_sys_srst_dis    : 1;  /* bit[24]   : BBP_COMM_FE中，W模式复位解除 */
        unsigned int  com_t_sys_srst_dis    : 1;  /* bit[25]   : BBP_COMM_FE中，T模式复位解除 */
        unsigned int  com_c_sys_srst_dis    : 1;  /* bit[26]   : BBP_COMM_FE中，C模式复位解除 */
        unsigned int  reserved_4            : 5;  /* bit[27-31]: 保留。 */
    } reg;
} BBPSCTRL_COM_SRST_DIS_UNION;
#define BBPSCTRL_COM_SRST_DIS_com_g1_srst_dis_START        (0)
#define BBPSCTRL_COM_SRST_DIS_com_g1_srst_dis_END          (0)
#define BBPSCTRL_COM_SRST_DIS_com_g2_srst_dis_START        (1)
#define BBPSCTRL_COM_SRST_DIS_com_g2_srst_dis_END          (1)
#define BBPSCTRL_COM_SRST_DIS_com_g_sdr_srst_dis_START     (3)
#define BBPSCTRL_COM_SRST_DIS_com_g_sdr_srst_dis_END       (3)
#define BBPSCTRL_COM_SRST_DIS_com_l_sdr_srst_dis_START     (4)
#define BBPSCTRL_COM_SRST_DIS_com_l_sdr_srst_dis_END       (4)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dma_srst_dis_START    (5)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dma_srst_dis_END      (5)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dbg_srst_dis_START    (6)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dbg_srst_dis_END      (6)
#define BBPSCTRL_COM_SRST_DIS_com_gu_mst_srst_dis_START    (7)
#define BBPSCTRL_COM_SRST_DIS_com_gu_mst_srst_dis_END      (7)
#define BBPSCTRL_COM_SRST_DIS_com_et_srst_dis_START        (9)
#define BBPSCTRL_COM_SRST_DIS_com_et_srst_dis_END          (9)
#define BBPSCTRL_COM_SRST_DIS_com_cs_srst_dis_START        (10)
#define BBPSCTRL_COM_SRST_DIS_com_cs_srst_dis_END          (10)
#define BBPSCTRL_COM_SRST_DIS_com_sys_srst_dis_START       (11)
#define BBPSCTRL_COM_SRST_DIS_com_sys_srst_dis_END         (11)
#define BBPSCTRL_COM_SRST_DIS_com_lte_cs_srst_dis_START    (12)
#define BBPSCTRL_COM_SRST_DIS_com_lte_cs_srst_dis_END      (12)
#define BBPSCTRL_COM_SRST_DIS_com_wc_srst_dis_START        (13)
#define BBPSCTRL_COM_SRST_DIS_com_wc_srst_dis_END          (13)
#define BBPSCTRL_COM_SRST_DIS_com_uc2_122m_srst_dis_START  (14)
#define BBPSCTRL_COM_SRST_DIS_com_uc2_122m_srst_dis_END    (14)
#define BBPSCTRL_COM_SRST_DIS_com_dbg_trig_srst_dis_START  (15)
#define BBPSCTRL_COM_SRST_DIS_com_dbg_trig_srst_dis_END    (15)
#define BBPSCTRL_COM_SRST_DIS_com_et_sub_srst_dis_START    (19)
#define BBPSCTRL_COM_SRST_DIS_com_et_sub_srst_dis_END      (19)
#define BBPSCTRL_COM_SRST_DIS_com_mipi_srst_dis_START      (22)
#define BBPSCTRL_COM_SRST_DIS_com_mipi_srst_dis_END        (22)
#define BBPSCTRL_COM_SRST_DIS_com_guc_dbg_srst_dis_START   (23)
#define BBPSCTRL_COM_SRST_DIS_com_guc_dbg_srst_dis_END     (23)
#define BBPSCTRL_COM_SRST_DIS_com_w_sys_srst_dis_START     (24)
#define BBPSCTRL_COM_SRST_DIS_com_w_sys_srst_dis_END       (24)
#define BBPSCTRL_COM_SRST_DIS_com_t_sys_srst_dis_START     (25)
#define BBPSCTRL_COM_SRST_DIS_com_t_sys_srst_dis_END       (25)
#define BBPSCTRL_COM_SRST_DIS_com_c_sys_srst_dis_START     (26)
#define BBPSCTRL_COM_SRST_DIS_com_c_sys_srst_dis_END       (26)


/*****************************************************************************
 结构名    : BBPSCTRL_COM_SRST_STATUS_UNION
 结构说明  : COM_SRST_STATUS 寄存器结构定义。地址偏移量:0x00F8，初值:0xFFFFFFFF，宽度:32
 寄存器说明: COM复位请求状态
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_status_reg;
    struct
    {
        unsigned int  com_g1_srst_status       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_srst_status       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0               : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_srst_status    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_srst_status    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_srst_status   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_srst_status   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_srst_status   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1               : 1;  /* bit[8]    :  */
        unsigned int  com_et_srst_status       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_srst_status       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_srst_status      : 1;  /* bit[11]   :  */
        unsigned int  com_lte_cs_srst_status   : 1;  /* bit[12]   :  */
        unsigned int  com_wc_srst_status       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_srst_status : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_srst_status : 1;  /* bit[15]   :  */
        unsigned int  reserved_2               : 3;  /* bit[16-18]: 保留 */
        unsigned int  com_et_sub_srst_status   : 1;  /* bit[19]   : 自研ET总线复位状态 */
        unsigned int  reserved_3               : 2;  /* bit[20-21]: 保留 */
        unsigned int  com_mipi_srst_status     : 1;  /* bit[22]   : BBP_COMM_FE中mipi时钟域复位状态。高复位，低解复位。 */
        unsigned int  com_guc_dbg_srst_status  : 1;  /* bit[23]   : GUC DBG复位状态 */
        unsigned int  com_w_sys_srst_status    : 1;  /* bit[24]   : BBP_COMM_FE中，W模式复位状态 */
        unsigned int  com_t_sys_srst_status    : 1;  /* bit[25]   : BBP_COMM_FE中，T模式复位状态 */
        unsigned int  com_c_sys_srst_status    : 1;  /* bit[26]   : BBP_COMM_FE中，C模式复位状态 */
        unsigned int  reserved_4               : 5;  /* bit[27-31]: 保留。 */
    } reg;
} BBPSCTRL_COM_SRST_STATUS_UNION;
#define BBPSCTRL_COM_SRST_STATUS_com_g1_srst_status_START        (0)
#define BBPSCTRL_COM_SRST_STATUS_com_g1_srst_status_END          (0)
#define BBPSCTRL_COM_SRST_STATUS_com_g2_srst_status_START        (1)
#define BBPSCTRL_COM_SRST_STATUS_com_g2_srst_status_END          (1)
#define BBPSCTRL_COM_SRST_STATUS_com_g_sdr_srst_status_START     (3)
#define BBPSCTRL_COM_SRST_STATUS_com_g_sdr_srst_status_END       (3)
#define BBPSCTRL_COM_SRST_STATUS_com_l_sdr_srst_status_START     (4)
#define BBPSCTRL_COM_SRST_STATUS_com_l_sdr_srst_status_END       (4)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dma_srst_status_START    (5)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dma_srst_status_END      (5)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dbg_srst_status_START    (6)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dbg_srst_status_END      (6)
#define BBPSCTRL_COM_SRST_STATUS_com_gu_mst_srst_status_START    (7)
#define BBPSCTRL_COM_SRST_STATUS_com_gu_mst_srst_status_END      (7)
#define BBPSCTRL_COM_SRST_STATUS_com_et_srst_status_START        (9)
#define BBPSCTRL_COM_SRST_STATUS_com_et_srst_status_END          (9)
#define BBPSCTRL_COM_SRST_STATUS_com_cs_srst_status_START        (10)
#define BBPSCTRL_COM_SRST_STATUS_com_cs_srst_status_END          (10)
#define BBPSCTRL_COM_SRST_STATUS_com_sys_srst_status_START       (11)
#define BBPSCTRL_COM_SRST_STATUS_com_sys_srst_status_END         (11)
#define BBPSCTRL_COM_SRST_STATUS_com_lte_cs_srst_status_START    (12)
#define BBPSCTRL_COM_SRST_STATUS_com_lte_cs_srst_status_END      (12)
#define BBPSCTRL_COM_SRST_STATUS_com_wc_srst_status_START        (13)
#define BBPSCTRL_COM_SRST_STATUS_com_wc_srst_status_END          (13)
#define BBPSCTRL_COM_SRST_STATUS_com_uc2_122m_srst_status_START  (14)
#define BBPSCTRL_COM_SRST_STATUS_com_uc2_122m_srst_status_END    (14)
#define BBPSCTRL_COM_SRST_STATUS_com_dbg_trig_srst_status_START  (15)
#define BBPSCTRL_COM_SRST_STATUS_com_dbg_trig_srst_status_END    (15)
#define BBPSCTRL_COM_SRST_STATUS_com_et_sub_srst_status_START    (19)
#define BBPSCTRL_COM_SRST_STATUS_com_et_sub_srst_status_END      (19)
#define BBPSCTRL_COM_SRST_STATUS_com_mipi_srst_status_START      (22)
#define BBPSCTRL_COM_SRST_STATUS_com_mipi_srst_status_END        (22)
#define BBPSCTRL_COM_SRST_STATUS_com_guc_dbg_srst_status_START   (23)
#define BBPSCTRL_COM_SRST_STATUS_com_guc_dbg_srst_status_END     (23)
#define BBPSCTRL_COM_SRST_STATUS_com_w_sys_srst_status_START     (24)
#define BBPSCTRL_COM_SRST_STATUS_com_w_sys_srst_status_END       (24)
#define BBPSCTRL_COM_SRST_STATUS_com_t_sys_srst_status_START     (25)
#define BBPSCTRL_COM_SRST_STATUS_com_t_sys_srst_status_END       (25)
#define BBPSCTRL_COM_SRST_STATUS_com_c_sys_srst_status_START     (26)
#define BBPSCTRL_COM_SRST_STATUS_com_c_sys_srst_status_END       (26)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_MTCMOS_SET_DSP_UNION
 结构说明  : BBP_MTCMOS_SET_DSP 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: BBP电源控制使能(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_set_dsp_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_set : 1;  /* bit[0]   : LTE电源域上电置位。
                                                              写1置位，写0无效。 */
        unsigned int  wtc_mtcmos_ctrl_set : 1;  /* bit[1]   : WTC电源域上电置位。
                                                              写1置位，写0无效。 */
        unsigned int  irm_mtcmos_ctrl_set : 1;  /* bit[2]   : IRM电源域上电置位。
                                                              写1置位，写0无效。 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_MTCMOS_SET_DSP_UNION;
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_lte_mtcmos_ctrl_set_START  (0)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_lte_mtcmos_ctrl_set_END    (0)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_wtc_mtcmos_ctrl_set_START  (1)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_wtc_mtcmos_ctrl_set_END    (1)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_irm_mtcmos_ctrl_set_START  (2)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_irm_mtcmos_ctrl_set_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_MTCMOS_CLR_DSP_UNION
 结构说明  : BBP_MTCMOS_CLR_DSP 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: BBP电源控制关闭(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_clr_dsp_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_clr : 1;  /* bit[0]   : LTE电源域上电清除。
                                                              写1清零，写0无效。 */
        unsigned int  wtc_mtcmos_ctrl_clr : 1;  /* bit[1]   : WTC电源域上电清除。
                                                              写1清零，写0无效。 */
        unsigned int  irm_mtcmos_ctrl_clr : 1;  /* bit[2]   : IRM电源域上电清除。
                                                              写1清零，写0无效。 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_MTCMOS_CLR_DSP_UNION;
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_lte_mtcmos_ctrl_clr_START  (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_lte_mtcmos_ctrl_clr_END    (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_wtc_mtcmos_ctrl_clr_START  (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_wtc_mtcmos_ctrl_clr_END    (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_irm_mtcmos_ctrl_clr_START  (2)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_irm_mtcmos_ctrl_clr_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_MTCMOS_STATUS_DSP_UNION
 结构说明  : BBP_MTCMOS_STATUS_DSP 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: BBP电源控制状态(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_status_dsp_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_status : 1;  /* bit[0]   : LTE电源域电源状态。
                                                                 1：上电
                                                                 0：下电 */
        unsigned int  wtc_mtcmos_ctrl_status : 1;  /* bit[1]   : WTC电源域电源状态。
                                                                 1：上电
                                                                 0：下电 */
        unsigned int  irm_mtcmos_ctrl_status : 1;  /* bit[2]   : IRM电源域电源状态。
                                                                 1：上电
                                                                 0：下电 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_MTCMOS_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_lte_mtcmos_ctrl_status_START  (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_lte_mtcmos_ctrl_status_END    (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_wtc_mtcmos_ctrl_status_START  (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_wtc_mtcmos_ctrl_status_END    (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_irm_mtcmos_ctrl_status_START  (2)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_irm_mtcmos_ctrl_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_ISO_EN_SET_DSP_UNION
 结构说明  : BBP_ISO_EN_SET_DSP 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: BBP电源隔离控制使能(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_set_dsp_reg;
    struct
    {
        unsigned int  lte_iso_en_set : 1;  /* bit[0]   : LTE电源域隔离置位。
                                                         写1置位，写0无效。 */
        unsigned int  wtc_iso_en_set : 1;  /* bit[1]   : WTC电源域隔离置位。
                                                         写1置位，写0无效。 */
        unsigned int  irm_iso_en_set : 1;  /* bit[2]   : IRM电源域隔离置位。
                                                         写1置位，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_ISO_EN_SET_DSP_UNION;
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_lte_iso_en_set_START  (0)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_lte_iso_en_set_END    (0)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_wtc_iso_en_set_START  (1)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_wtc_iso_en_set_END    (1)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_irm_iso_en_set_START  (2)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_irm_iso_en_set_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_ISO_EN_CLR_DSP_UNION
 结构说明  : BBP_ISO_EN_CLR_DSP 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: BBP电源隔离控制关闭(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_clr_dsp_reg;
    struct
    {
        unsigned int  lte_iso_en_clr : 1;  /* bit[0]   : LTE电源域隔离清除。
                                                         写1清零，写0无效。 */
        unsigned int  wtc_iso_en_clr : 1;  /* bit[1]   : WTC电源域隔离清除。
                                                         写1清零，写0无效。 */
        unsigned int  irm_iso_en_clr : 1;  /* bit[2]   : IRM电源域隔离清除。
                                                         写1清零，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_ISO_EN_CLR_DSP_UNION;
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_lte_iso_en_clr_START  (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_lte_iso_en_clr_END    (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_wtc_iso_en_clr_START  (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_wtc_iso_en_clr_END    (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_irm_iso_en_clr_START  (2)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_irm_iso_en_clr_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_ISO_EN_STATUS_DSP_UNION
 结构说明  : BBP_ISO_EN_STATUS_DSP 寄存器结构定义。地址偏移量:0x0118，初值:0x0000003F，宽度:32
 寄存器说明: BBP电源隔离控制状态(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_status_dsp_reg;
    struct
    {
        unsigned int  lte_iso_en_status : 1;  /* bit[0]   : LTE电源域隔离状态。
                                                            1：隔离；
                                                            0：解除隔离； */
        unsigned int  wtc_iso_en_status : 1;  /* bit[1]   : WTC电源域隔离状态。
                                                            1：隔离；
                                                            0：解除隔离； */
        unsigned int  irm_iso_en_status : 1;  /* bit[2]   : IRM电源域隔离状态。
                                                            1：隔离；
                                                            0：解除隔离； */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_ISO_EN_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_lte_iso_en_status_START  (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_lte_iso_en_status_END    (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_wtc_iso_en_status_START  (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_wtc_iso_en_status_END    (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_irm_iso_en_status_START  (2)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_irm_iso_en_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_CLK_SET_DSP_UNION
 结构说明  : BBP_PD_CLK_SET_DSP 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域时钟使能(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_set_dsp_reg;
    struct
    {
        unsigned int  lte_pd_clk_ena : 1;  /* bit[0]   : LTE电源域时钟使能。
                                                         写1置位，写0无效。 */
        unsigned int  wtc_pd_clk_ena : 1;  /* bit[1]   : WTC电源域时钟使能。
                                                         写1置位，写0无效。 */
        unsigned int  irm_pd_clk_ena : 1;  /* bit[2]   : IRM电源域时钟使能。
                                                         写1置位，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_CLK_SET_DSP_UNION;
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_lte_pd_clk_ena_START  (0)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_lte_pd_clk_ena_END    (0)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_wtc_pd_clk_ena_START  (1)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_wtc_pd_clk_ena_END    (1)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_irm_pd_clk_ena_START  (2)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_irm_pd_clk_ena_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_CLK_CLR_DSP_UNION
 结构说明  : BBP_PD_CLK_CLR_DSP 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域时钟关闭(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_clr_dsp_reg;
    struct
    {
        unsigned int  lte_pd_clk_dis : 1;  /* bit[0]   : LTE电源域时钟关闭。
                                                         写1关闭，写0无效。 */
        unsigned int  wtc_pd_clk_dis : 1;  /* bit[1]   : WTC电源域时钟关闭。
                                                         写1关闭，写0无效。 */
        unsigned int  irm_pd_clk_dis : 1;  /* bit[2]   : IRM电源域时钟关闭。
                                                         写1关闭，写0无效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_CLK_CLR_DSP_UNION;
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_lte_pd_clk_dis_START  (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_lte_pd_clk_dis_END    (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_wtc_pd_clk_dis_START  (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_wtc_pd_clk_dis_END    (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_irm_pd_clk_dis_START  (2)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_irm_pd_clk_dis_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_CLK_STATUS_DSP_UNION
 结构说明  : BBP_PD_CLK_STATUS_DSP 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域时钟门控状态(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_status_dsp_reg;
    struct
    {
        unsigned int  lte_pd_clk_status : 1;  /* bit[0]   : LTE电源域时钟状态。
                                                            1：时钟使能
                                                            0：时钟关闭 */
        unsigned int  wtc_pd_clk_status : 1;  /* bit[1]   : WTC电源域时钟状态。
                                                            1：时钟使能
                                                            0：时钟关闭 */
        unsigned int  irm_pd_clk_status : 1;  /* bit[2]   : IRM电源域时钟状态。
                                                            1：时钟使能
                                                            0：时钟关闭 */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_CLK_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_lte_pd_clk_status_START  (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_lte_pd_clk_status_END    (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_wtc_pd_clk_status_START  (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_wtc_pd_clk_status_END    (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_irm_pd_clk_status_START  (2)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_irm_pd_clk_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_SRST_SET_DSP_UNION
 结构说明  : BBP_PD_SRST_SET_DSP 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域复位请求使能(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_set_dsp_reg;
    struct
    {
        unsigned int  lte_pd_srst_req : 1;  /* bit[0]   : LTE电源域复位请求。
                                                          写1复位，写0无效。 */
        unsigned int  wtc_pd_srst_req : 1;  /* bit[1]   : WTC电源域复位请求。
                                                          写1复位，写0无效。 */
        unsigned int  irm_pd_srst_req : 1;  /* bit[2]   : IRM电源域复位请求。
                                                          写1复位，写0无效。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_SRST_SET_DSP_UNION;
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_lte_pd_srst_req_START  (0)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_lte_pd_srst_req_END    (0)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_wtc_pd_srst_req_START  (1)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_wtc_pd_srst_req_END    (1)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_irm_pd_srst_req_START  (2)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_irm_pd_srst_req_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_SRST_CLR_DSP_UNION
 结构说明  : BBP_PD_SRST_CLR_DSP 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域复位请求关闭(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_clr_dsp_reg;
    struct
    {
        unsigned int  lte_pd_srst_dis : 1;  /* bit[0]   : LTE电源域复位清除。
                                                          写1解除复位，写0无效。 */
        unsigned int  wtc_pd_srst_dis : 1;  /* bit[1]   : WTC电源域复位清除。
                                                          写1解除复位，写0无效。 */
        unsigned int  irm_pd_srst_dis : 1;  /* bit[2]   : IRM电源域复位清除。
                                                          写1解除复位，写0无效。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_SRST_CLR_DSP_UNION;
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_lte_pd_srst_dis_START  (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_lte_pd_srst_dis_END    (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_wtc_pd_srst_dis_START  (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_wtc_pd_srst_dis_END    (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_irm_pd_srst_dis_START  (2)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_irm_pd_srst_dis_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_PD_SRST_STATUS_DSP_UNION
 结构说明  : BBP_PD_SRST_STATUS_DSP 寄存器结构定义。地址偏移量:0x0138，初值:0x00000007，宽度:32
 寄存器说明: BBP电源域复位请求状态(DSP核)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_status_dsp_reg;
    struct
    {
        unsigned int  lte_pd_srst_status : 1;  /* bit[0]   : LTE电源域复位状态。
                                                             1：复位；
                                                             0：解除复位； */
        unsigned int  wtc_pd_srst_status : 1;  /* bit[1]   : WTC电源域复位状态。
                                                             1：复位；
                                                             0：解除复位； */
        unsigned int  irm_pd_srst_status : 1;  /* bit[2]   : IRM电源域复位状态。
                                                             1：复位；
                                                             0：解除复位； */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_PD_SRST_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_lte_pd_srst_status_START  (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_lte_pd_srst_status_END    (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_wtc_pd_srst_status_START  (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_wtc_pd_srst_status_END    (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_irm_pd_srst_status_START  (2)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_irm_pd_srst_status_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTRL1f_SET_UNION
 结构说明  : BBP_SCTRL1f_SET 寄存器结构定义。地址偏移量:0x01F0，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器1F置位(PD PWR AND PD CLK FORCE ENA)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl1f_set_reg;
    struct
    {
        unsigned int  lte_pd_pwr_force_ena : 1;  /* bit[0]    : 写1，强制上电。 */
        unsigned int  wtc_pd_pwr_force_ena : 1;  /* bit[1]    : 写1，强制上电。 */
        unsigned int  irm_pd_pwr_force_ena : 1;  /* bit[2]    : 写1，强制上电。 */
        unsigned int  reserved_0           : 1;  /* bit[3]    :  */
        unsigned int  lte_pd_iso_force_dis : 1;  /* bit[4]    : 写1，强制解隔离。 */
        unsigned int  wtc_pd_iso_force_dis : 1;  /* bit[5]    : 写1，强制解隔离。 */
        unsigned int  irm_pd_iso_force_dis : 1;  /* bit[6]    : 写1，强制解隔离。 */
        unsigned int  reserved_1           : 1;  /* bit[7]    :  */
        unsigned int  wtc_pd_clk_force_ena : 1;  /* bit[8]    : 写1，强制开钟。 */
        unsigned int  lte_pd_clk_force_ena : 1;  /* bit[9]    : 写1，强制开钟。 */
        unsigned int  irm_pd_clk_force_ena : 1;  /* bit[10]   : 写1，强制开钟。 */
        unsigned int  reserved_2           : 1;  /* bit[11]   :  */
        unsigned int  lte_pd_rst_force_ena : 1;  /* bit[12]   : 写1，强制解复位。 */
        unsigned int  wtc_pd_rst_force_ena : 1;  /* bit[13]   : 写1，强制解复位。 */
        unsigned int  irm_pd_rst_force_ena : 1;  /* bit[14]   : 写1，强制解复位。 */
        unsigned int  reserved_3           : 17; /* bit[15-31]: 保留。Debug使用。 */
    } reg;
} BBPSCTRL_BBP_SCTRL1f_SET_UNION;
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_pwr_force_ena_START  (0)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_pwr_force_ena_END    (0)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_pwr_force_ena_START  (1)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_pwr_force_ena_END    (1)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_pwr_force_ena_START  (2)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_pwr_force_ena_END    (2)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_iso_force_dis_START  (4)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_iso_force_dis_END    (4)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_iso_force_dis_START  (5)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_iso_force_dis_END    (5)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_iso_force_dis_START  (6)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_iso_force_dis_END    (6)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_clk_force_ena_START  (8)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_clk_force_ena_END    (8)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_clk_force_ena_START  (9)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_clk_force_ena_END    (9)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_clk_force_ena_START  (10)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_clk_force_ena_END    (10)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_rst_force_ena_START  (12)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_rst_force_ena_END    (12)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_rst_force_ena_START  (13)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_rst_force_ena_END    (13)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_rst_force_ena_START  (14)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_rst_force_ena_END    (14)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR20_UNION
 结构说明  : BBP_SCTR20 寄存器结构定义。地址偏移量:0x0200，初值:0x02222222，宽度:32
 寄存器说明: LBUS防挂死配置
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr20_reg;
    struct
    {
        unsigned int  ulhb_bypass       : 1;  /* bit[0]    :  */
        unsigned int  ulhb_rd_prot      : 2;  /* bit[1-2]  :  */
        unsigned int  reserved_0        : 1;  /* bit[3]    :  */
        unsigned int  pdf_bypas         : 1;  /* bit[4]    :  */
        unsigned int  pdf_rd_prot       : 2;  /* bit[5-6]  :  */
        unsigned int  reserved_1        : 1;  /* bit[7]    :  */
        unsigned int  pdt_bypass        : 1;  /* bit[8]    :  */
        unsigned int  pdt_rd_prot       : 2;  /* bit[9-10] :  */
        unsigned int  reserved_2        : 1;  /* bit[11]   :  */
        unsigned int  tds245_bypass     : 1;  /* bit[12]   :  */
        unsigned int  tds245_rd_prot    : 2;  /* bit[13-14]:  */
        unsigned int  reserved_3        : 1;  /* bit[15]   :  */
        unsigned int  ux_tds122_bypass  : 1;  /* bit[16]   :  */
        unsigned int  ux_tds122_rd_prot : 2;  /* bit[17-18]:  */
        unsigned int  reserved_4        : 1;  /* bit[19]   :  */
        unsigned int  g_bypass          : 1;  /* bit[20]   :  */
        unsigned int  g_rd_prot         : 2;  /* bit[21-22]:  */
        unsigned int  reserved_5        : 1;  /* bit[23]   :  */
        unsigned int  uc2_bypass        : 1;  /* bit[24]   :  */
        unsigned int  uc2_rd_prot       : 2;  /* bit[25-26]:  */
        unsigned int  reserved_6        : 5;  /* bit[27-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTR20_UNION;
#define BBPSCTRL_BBP_SCTR20_ulhb_bypass_START        (0)
#define BBPSCTRL_BBP_SCTR20_ulhb_bypass_END          (0)
#define BBPSCTRL_BBP_SCTR20_ulhb_rd_prot_START       (1)
#define BBPSCTRL_BBP_SCTR20_ulhb_rd_prot_END         (2)
#define BBPSCTRL_BBP_SCTR20_pdf_bypas_START          (4)
#define BBPSCTRL_BBP_SCTR20_pdf_bypas_END            (4)
#define BBPSCTRL_BBP_SCTR20_pdf_rd_prot_START        (5)
#define BBPSCTRL_BBP_SCTR20_pdf_rd_prot_END          (6)
#define BBPSCTRL_BBP_SCTR20_pdt_bypass_START         (8)
#define BBPSCTRL_BBP_SCTR20_pdt_bypass_END           (8)
#define BBPSCTRL_BBP_SCTR20_pdt_rd_prot_START        (9)
#define BBPSCTRL_BBP_SCTR20_pdt_rd_prot_END          (10)
#define BBPSCTRL_BBP_SCTR20_tds245_bypass_START      (12)
#define BBPSCTRL_BBP_SCTR20_tds245_bypass_END        (12)
#define BBPSCTRL_BBP_SCTR20_tds245_rd_prot_START     (13)
#define BBPSCTRL_BBP_SCTR20_tds245_rd_prot_END       (14)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_bypass_START   (16)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_bypass_END     (16)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_rd_prot_START  (17)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_rd_prot_END    (18)
#define BBPSCTRL_BBP_SCTR20_g_bypass_START           (20)
#define BBPSCTRL_BBP_SCTR20_g_bypass_END             (20)
#define BBPSCTRL_BBP_SCTR20_g_rd_prot_START          (21)
#define BBPSCTRL_BBP_SCTR20_g_rd_prot_END            (22)
#define BBPSCTRL_BBP_SCTR20_uc2_bypass_START         (24)
#define BBPSCTRL_BBP_SCTR20_uc2_bypass_END           (24)
#define BBPSCTRL_BBP_SCTR20_uc2_rd_prot_START        (25)
#define BBPSCTRL_BBP_SCTR20_uc2_rd_prot_END          (26)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR21_UNION
 结构说明  : BBP_SCTR21 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器21(dw_axi_bbp 配置)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr21_reg;
    struct
    {
        unsigned int  mst_priority_update  : 1;  /* bit[0]    :  */
        unsigned int  xdcdr_sel            : 1;  /* bit[1]    :  */
        unsigned int  mst_err_srst_req     : 1;  /* bit[2]    :  */
        unsigned int  slv_active           : 2;  /* bit[3-4]  :  */
        unsigned int  mst_priority_m1      : 2;  /* bit[5-6]  :  */
        unsigned int  mst_priority_m2      : 2;  /* bit[7-8]  :  */
        unsigned int  mst_priority_m3      : 2;  /* bit[9-10] :  */
        unsigned int  mst_priority_m4      : 2;  /* bit[11-12]:  */
        unsigned int  dw_axi_gatedclock_en : 1;  /* bit[13]   :  */
        unsigned int  reserved             : 18; /* bit[14-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTR21_UNION;
#define BBPSCTRL_BBP_SCTR21_mst_priority_update_START   (0)
#define BBPSCTRL_BBP_SCTR21_mst_priority_update_END     (0)
#define BBPSCTRL_BBP_SCTR21_xdcdr_sel_START             (1)
#define BBPSCTRL_BBP_SCTR21_xdcdr_sel_END               (1)
#define BBPSCTRL_BBP_SCTR21_mst_err_srst_req_START      (2)
#define BBPSCTRL_BBP_SCTR21_mst_err_srst_req_END        (2)
#define BBPSCTRL_BBP_SCTR21_slv_active_START            (3)
#define BBPSCTRL_BBP_SCTR21_slv_active_END              (4)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m1_START       (5)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m1_END         (6)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m2_START       (7)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m2_END         (8)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m3_START       (9)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m3_END         (10)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m4_START       (11)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m4_END         (12)
#define BBPSCTRL_BBP_SCTR21_dw_axi_gatedclock_en_START  (13)
#define BBPSCTRL_BBP_SCTR21_dw_axi_gatedclock_en_END    (13)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR22_UNION
 结构说明  : BBP_SCTR22 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器22(dw_axi_bbp dlock)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr22_reg;
    struct
    {
        unsigned int  dlock_cnt_update : 1;  /* bit[0]   : 寄存器23对应的dlock参数update */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTR22_UNION;
#define BBPSCTRL_BBP_SCTR22_dlock_cnt_update_START  (0)
#define BBPSCTRL_BBP_SCTR22_dlock_cnt_update_END    (0)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR23_UNION
 结构说明  : BBP_SCTR23 寄存器结构定义。地址偏移量:0x020C，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器23(dw_axi_bbp_dlock)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr23_reg;
    struct
    {
        unsigned int  dlock_cnt_clk_div_num : 8;  /* bit[0-7]  : 调试使用。 */
        unsigned int  reserved              : 8;  /* bit[8-15] : 保留 */
        unsigned int  dlock_cnt_max         : 16; /* bit[16-31]: 调试使用。 */
    } reg;
} BBPSCTRL_BBP_SCTR23_UNION;
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_clk_div_num_START  (0)
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_clk_div_num_END    (7)
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_max_START          (16)
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_max_END            (31)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR24_UNION
 结构说明  : BBP_SCTR24 寄存器结构定义。地址偏移量:0x0210，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器24(LBUS总线防挂死中断屏蔽)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr24_reg;
    struct
    {
        unsigned int  ulhb_err_power_int_mask           : 1;  /* bit[0] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  ulhb_err_clk_int_mask             : 1;  /* bit[1] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  ulhb_err_rst_int_mask             : 1;  /* bit[2] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  ulhb_err_rd_timeout_int_mask      : 1;  /* bit[3] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdf_err_power_int_mask            : 1;  /* bit[4] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdf_err_clk_int_mask              : 1;  /* bit[5] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdf_err_rst_int_mask              : 1;  /* bit[6] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdf_err_rd_timeout_int_mask       : 1;  /* bit[7] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdt_err_power_int_mask            : 1;  /* bit[8] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdt_err_clk_int_mask              : 1;  /* bit[9] : 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdt_err_rst_int_mask              : 1;  /* bit[10]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  pdt_err_rd_timeout_int_mask       : 1;  /* bit[11]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  tds245_err_power_int_mask         : 1;  /* bit[12]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  tds245_err_clk_int_mask           : 1;  /* bit[13]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  tds245_err_rst_int_mask           : 1;  /* bit[14]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  tds245_err_rd_timeout_int_mask    : 1;  /* bit[15]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  ux_tds122_err_power_int_mask      : 1;  /* bit[16]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  ux_tds122_err_clk_int_mask        : 1;  /* bit[17]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  ux_tds122_err_rst_int_mask        : 1;  /* bit[18]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  ux_tds122_err_rd_timeout_int_mask : 1;  /* bit[19]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  g_err_clk_int_mask                : 1;  /* bit[20]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  g_err_rst_int_mask                : 1;  /* bit[21]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  g_err_rd_timeout_int_mask         : 1;  /* bit[22]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  b2s_err_rd_timeout_int_mask       : 1;  /* bit[23]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  uc2_err_power_int_mask            : 1;  /* bit[24]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  uc2_err_clk_int_mask              : 1;  /* bit[25]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  uc2_err_rst_int_mask              : 1;  /* bit[26]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  uc2_err_rd_timeout_int_mask       : 1;  /* bit[27]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  axi_arb_overtime_int_mask         : 1;  /* bit[28]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  dma_arb_overtime_int_mask         : 1;  /* bit[29]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  dbgtrig_arb_overtime_int_mask     : 1;  /* bit[30]: 0：中断屏蔽无效。
                                                                          1：中断屏蔽使能。 */
        unsigned int  reserved                          : 1;  /* bit[31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTR24_UNION;
#define BBPSCTRL_BBP_SCTR24_ulhb_err_power_int_mask_START            (0)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_power_int_mask_END              (0)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_clk_int_mask_START              (1)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_clk_int_mask_END                (1)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rst_int_mask_START              (2)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rst_int_mask_END                (2)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rd_timeout_int_mask_START       (3)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rd_timeout_int_mask_END         (3)
#define BBPSCTRL_BBP_SCTR24_pdf_err_power_int_mask_START             (4)
#define BBPSCTRL_BBP_SCTR24_pdf_err_power_int_mask_END               (4)
#define BBPSCTRL_BBP_SCTR24_pdf_err_clk_int_mask_START               (5)
#define BBPSCTRL_BBP_SCTR24_pdf_err_clk_int_mask_END                 (5)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rst_int_mask_START               (6)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rst_int_mask_END                 (6)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rd_timeout_int_mask_START        (7)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rd_timeout_int_mask_END          (7)
#define BBPSCTRL_BBP_SCTR24_pdt_err_power_int_mask_START             (8)
#define BBPSCTRL_BBP_SCTR24_pdt_err_power_int_mask_END               (8)
#define BBPSCTRL_BBP_SCTR24_pdt_err_clk_int_mask_START               (9)
#define BBPSCTRL_BBP_SCTR24_pdt_err_clk_int_mask_END                 (9)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rst_int_mask_START               (10)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rst_int_mask_END                 (10)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rd_timeout_int_mask_START        (11)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rd_timeout_int_mask_END          (11)
#define BBPSCTRL_BBP_SCTR24_tds245_err_power_int_mask_START          (12)
#define BBPSCTRL_BBP_SCTR24_tds245_err_power_int_mask_END            (12)
#define BBPSCTRL_BBP_SCTR24_tds245_err_clk_int_mask_START            (13)
#define BBPSCTRL_BBP_SCTR24_tds245_err_clk_int_mask_END              (13)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rst_int_mask_START            (14)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rst_int_mask_END              (14)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rd_timeout_int_mask_START     (15)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rd_timeout_int_mask_END       (15)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_power_int_mask_START       (16)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_power_int_mask_END         (16)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_clk_int_mask_START         (17)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_clk_int_mask_END           (17)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rst_int_mask_START         (18)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rst_int_mask_END           (18)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rd_timeout_int_mask_START  (19)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rd_timeout_int_mask_END    (19)
#define BBPSCTRL_BBP_SCTR24_g_err_clk_int_mask_START                 (20)
#define BBPSCTRL_BBP_SCTR24_g_err_clk_int_mask_END                   (20)
#define BBPSCTRL_BBP_SCTR24_g_err_rst_int_mask_START                 (21)
#define BBPSCTRL_BBP_SCTR24_g_err_rst_int_mask_END                   (21)
#define BBPSCTRL_BBP_SCTR24_g_err_rd_timeout_int_mask_START          (22)
#define BBPSCTRL_BBP_SCTR24_g_err_rd_timeout_int_mask_END            (22)
#define BBPSCTRL_BBP_SCTR24_b2s_err_rd_timeout_int_mask_START        (23)
#define BBPSCTRL_BBP_SCTR24_b2s_err_rd_timeout_int_mask_END          (23)
#define BBPSCTRL_BBP_SCTR24_uc2_err_power_int_mask_START             (24)
#define BBPSCTRL_BBP_SCTR24_uc2_err_power_int_mask_END               (24)
#define BBPSCTRL_BBP_SCTR24_uc2_err_clk_int_mask_START               (25)
#define BBPSCTRL_BBP_SCTR24_uc2_err_clk_int_mask_END                 (25)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rst_int_mask_START               (26)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rst_int_mask_END                 (26)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rd_timeout_int_mask_START        (27)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rd_timeout_int_mask_END          (27)
#define BBPSCTRL_BBP_SCTR24_axi_arb_overtime_int_mask_START          (28)
#define BBPSCTRL_BBP_SCTR24_axi_arb_overtime_int_mask_END            (28)
#define BBPSCTRL_BBP_SCTR24_dma_arb_overtime_int_mask_START          (29)
#define BBPSCTRL_BBP_SCTR24_dma_arb_overtime_int_mask_END            (29)
#define BBPSCTRL_BBP_SCTR24_dbgtrig_arb_overtime_int_mask_START      (30)
#define BBPSCTRL_BBP_SCTR24_dbgtrig_arb_overtime_int_mask_END        (30)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR2A_UNION
 结构说明  : BBP_SCTR2A 寄存器结构定义。地址偏移量:0x0228，初值:0x0000C148，宽度:32
 寄存器说明: BBP系统控制器2A(BBP时钟选择)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2a_reg;
    struct
    {
        unsigned int  uart_clk_sel           : 1;  /* bit[0]    : uart时钟选择。
                                                                  1：选择480MHz分频；
                                                                  0：选择245MHz分频； */
        unsigned int  mipi_clk_sel           : 1;  /* bit[1]    : mipi时钟来源：
                                                                  0：选择 19.2MHz ，注BBP端口输入时钟；
                                                                  1：选择 40.96MHz，注BBP内部245MHz分频时钟； */
        unsigned int  scpll_sel              : 1;  /* bit[2]    : scpll_clk选择信号：
                                                                  0：表示选择bbppll_clk_sc0
                                                                  1：表示选择bbppll_clk_sc1 */
        unsigned int  scpll_uc2_sel          : 1;  /* bit[3]    : scpll_uc2_clk选择信号：
                                                                  0：表示选择bbppll_clk_sc0
                                                                  1：表示选择bbppll_clk_sc1 */
        unsigned int  pdt_clk_sel            : 1;  /* bit[4]    : bbp clk选择。
                                                                  0：选择122M;
                                                                  1：选择245M； */
        unsigned int  pdf_clk_sel            : 1;  /* bit[5]    : pdt clk选择。
                                                                  0：选择122M；
                                                                  1：选择245M； */
        unsigned int  tx0_clk_sel            : 2;  /* bit[6-7]  : LTE tx0 clk选择。
                                                                  00：选择245M(1分频)
                                                                  01：选择122M(2分频）
                                                                  10：选择61.44M(4分频)
                                                                  11：选择30.72M(8分频) */
        unsigned int  tx1_clk_sel            : 2;  /* bit[8-9]  : LTE tx1 clk选择。
                                                                  00：选择245M(1分频)
                                                                  01：选择122M(2分频）
                                                                  10：选择61.44M(4分频)
                                                                  11：选择30.72M(8分频) */
        unsigned int  ch0_tdl_clk_div_sel    : 1;  /* bit[10]   : 软值配置时钟频率场景下，ch0 tdl clk分频参数。
                                                                  1：ch0主时钟480/240MHz(默认);
                                                                  0：ch0主时钟240/120MHz
                                                                  注，该参数在本寄存器bit20为0时有效。 */
        unsigned int  ch1_tdl_clk_div_sel    : 1;  /* bit[11]   : 软值配置时钟频率场景下，ch1 tdl clk分频参数。
                                                                  1：ch1主时钟480/240MHz(默认);
                                                                  0：ch1主时钟240/120MHz
                                                                  注，该参数在本寄存器bit20为0时有效。 */
        unsigned int  reserved_0             : 2;  /* bit[12-13]: 保留 */
        unsigned int  uart_clk_div_sel       : 5;  /* bit[14-18]: UART的分频参数。 */
        unsigned int  bbp_tdl_clk_lte_irm_en : 1;  /* bit[19]   : bbp tdl clk使能。该时钟所在电源域为IRM/LTE电源域。 */
        unsigned int  tdl_clk_div_ctrl_sw_en : 1;  /* bit[20]   : tdl工作时钟频率120/240MHz还是240/480MHz选择信号,该bit为：
                                                                  0：使用本寄存器地址bit【11:10】的软件配置值来选择。（上电复位默认此方式）
                                                                  1：tdl逻辑端口选择信号。 */
        unsigned int  bbp_irm_ps_ctrl_sel    : 1;  /* bit[21]   : 0: 选择AP侧的低功耗控制信号(默认，下电、复位后均为该值)。
                                                                  1：选择BBP侧的低功耗控制信号。
                                                                  Modem使用IRM的时候，需要配置为1. 次 */
        unsigned int  reserved_1             : 10; /* bit[22-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTR2A_UNION;
#define BBPSCTRL_BBP_SCTR2A_uart_clk_sel_START            (0)
#define BBPSCTRL_BBP_SCTR2A_uart_clk_sel_END              (0)
#define BBPSCTRL_BBP_SCTR2A_mipi_clk_sel_START            (1)
#define BBPSCTRL_BBP_SCTR2A_mipi_clk_sel_END              (1)
#define BBPSCTRL_BBP_SCTR2A_scpll_sel_START               (2)
#define BBPSCTRL_BBP_SCTR2A_scpll_sel_END                 (2)
#define BBPSCTRL_BBP_SCTR2A_scpll_uc2_sel_START           (3)
#define BBPSCTRL_BBP_SCTR2A_scpll_uc2_sel_END             (3)
#define BBPSCTRL_BBP_SCTR2A_pdt_clk_sel_START             (4)
#define BBPSCTRL_BBP_SCTR2A_pdt_clk_sel_END               (4)
#define BBPSCTRL_BBP_SCTR2A_pdf_clk_sel_START             (5)
#define BBPSCTRL_BBP_SCTR2A_pdf_clk_sel_END               (5)
#define BBPSCTRL_BBP_SCTR2A_tx0_clk_sel_START             (6)
#define BBPSCTRL_BBP_SCTR2A_tx0_clk_sel_END               (7)
#define BBPSCTRL_BBP_SCTR2A_tx1_clk_sel_START             (8)
#define BBPSCTRL_BBP_SCTR2A_tx1_clk_sel_END               (9)
#define BBPSCTRL_BBP_SCTR2A_ch0_tdl_clk_div_sel_START     (10)
#define BBPSCTRL_BBP_SCTR2A_ch0_tdl_clk_div_sel_END       (10)
#define BBPSCTRL_BBP_SCTR2A_ch1_tdl_clk_div_sel_START     (11)
#define BBPSCTRL_BBP_SCTR2A_ch1_tdl_clk_div_sel_END       (11)
#define BBPSCTRL_BBP_SCTR2A_uart_clk_div_sel_START        (14)
#define BBPSCTRL_BBP_SCTR2A_uart_clk_div_sel_END          (18)
#define BBPSCTRL_BBP_SCTR2A_bbp_tdl_clk_lte_irm_en_START  (19)
#define BBPSCTRL_BBP_SCTR2A_bbp_tdl_clk_lte_irm_en_END    (19)
#define BBPSCTRL_BBP_SCTR2A_tdl_clk_div_ctrl_sw_en_START  (20)
#define BBPSCTRL_BBP_SCTR2A_tdl_clk_div_ctrl_sw_en_END    (20)
#define BBPSCTRL_BBP_SCTR2A_bbp_irm_ps_ctrl_sel_START     (21)
#define BBPSCTRL_BBP_SCTR2A_bbp_irm_ps_ctrl_sel_END       (21)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR2D_UNION
 结构说明  : BBP_SCTR2D 寄存器结构定义。地址偏移量:0x0234，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器2D(REV)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2d_reg;
    struct
    {
        unsigned int  m1_mst_err_sel : 1;  /* bit[0]   : MST ERR状态中读写地址信息选择。
                                                         0：选择读地址；
                                                         1：选择写地址； */
        unsigned int  m2_mst_err_sel : 1;  /* bit[1]   : MST ERR状态中读写地址信息选择。
                                                         0：选择读地址；
                                                         1：选择写地址； */
        unsigned int  m3_mst_err_sel : 1;  /* bit[2]   : MST ERR状态中读写地址信息选择。
                                                         0：选择读地址；
                                                         1：选择写地址； */
        unsigned int  m4_mst_err_sel : 1;  /* bit[3]   : MST ERR状态中读写地址信息选择。
                                                         0：选择读地址；
                                                         1：选择写地址； */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTR2D_UNION;
#define BBPSCTRL_BBP_SCTR2D_m1_mst_err_sel_START  (0)
#define BBPSCTRL_BBP_SCTR2D_m1_mst_err_sel_END    (0)
#define BBPSCTRL_BBP_SCTR2D_m2_mst_err_sel_START  (1)
#define BBPSCTRL_BBP_SCTR2D_m2_mst_err_sel_END    (1)
#define BBPSCTRL_BBP_SCTR2D_m3_mst_err_sel_START  (2)
#define BBPSCTRL_BBP_SCTR2D_m3_mst_err_sel_END    (2)
#define BBPSCTRL_BBP_SCTR2D_m4_mst_err_sel_START  (3)
#define BBPSCTRL_BBP_SCTR2D_m4_mst_err_sel_END    (3)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR2E_UNION
 结构说明  : BBP_SCTR2E 寄存器结构定义。地址偏移量:0x0238，初值:0x00000000，宽度:32
 寄存器说明: BBP系统控制器2E（g模总线同步调试）
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2e_reg;
    struct
    {
        unsigned int  g_mode_lbus_sel : 1;  /* bit[0]   : G_LBUS选择。保留，debug使用。
                                                          0：从Arbiter后输出；
                                                          1：从Arbiter前输出； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_SCTR2E_UNION;
#define BBPSCTRL_BBP_SCTR2E_g_mode_lbus_sel_START  (0)
#define BBPSCTRL_BBP_SCTR2E_g_mode_lbus_sel_END    (0)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_SCTR2F_UNION
 结构说明  : BBP_SCTR2F 寄存器结构定义。地址偏移量:0x023C，初值:0x00000042，宽度:32
 寄存器说明: BBP系统控制器2F(模式选择)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2f_reg;
    struct
    {
        unsigned int  wtc_mode_sel : 3;  /* bit[0-2]  : WTC模式选择，one-hot编码。
                                                        001：WCDMA模式；
                                                        010：TDS-CDMA模式；
                                                        100：CDMA模式；
                                                        default：TDS_CDMA模式。
                                                        其他值：无效，告警。 */
        unsigned int  reserved_0   : 1;  /* bit[3]    : 保留 */
        unsigned int  uc2_mode_sel : 3;  /* bit[4-6]  : UC2模式选择，one-hot编码。
                                                        001：WCDMA模式；
                                                        010：保留；
                                                        100：CDMA模式；
                                                        default：CDMA模式。
                                                        其他值：无效，告警。 */
        unsigned int  reserved_1   : 1;  /* bit[7]    : 保留 */
        unsigned int  l_et_sel     : 1;  /* bit[8]    : L ET选择（芯片版本不支持自研ET，所以该值不需要修改）。
                                                        0：第三方ET。
                                                        1：自研ET。 */
        unsigned int  w_et_sel     : 1;  /* bit[9]    : W ET选择（芯片版本不支持自研ET，所以该值不需要修改）
                                                        0：第三方ET。
                                                        1：自研ET。 */
        unsigned int  reserved_2   : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPSCTRL_BBP_SCTR2F_UNION;
#define BBPSCTRL_BBP_SCTR2F_wtc_mode_sel_START  (0)
#define BBPSCTRL_BBP_SCTR2F_wtc_mode_sel_END    (2)
#define BBPSCTRL_BBP_SCTR2F_uc2_mode_sel_START  (4)
#define BBPSCTRL_BBP_SCTR2F_uc2_mode_sel_END    (6)
#define BBPSCTRL_BBP_SCTR2F_l_et_sel_START      (8)
#define BBPSCTRL_BBP_SCTR2F_l_et_sel_END        (8)
#define BBPSCTRL_BBP_SCTR2F_w_et_sel_START      (9)
#define BBPSCTRL_BBP_SCTR2F_w_et_sel_END        (9)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_STAT00_UNION
 结构说明  : BBP_STAT00 寄存器结构定义。地址偏移量:0x0300，初值:0x00000000，宽度:32
 寄存器说明: BBP电源域状态寄存器（mtcmos rdy)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat00_reg;
    struct
    {
        unsigned int  lte_mtcmos_rdy : 1;  /* bit[0]   : LTE电源域上电状态。
                                                         1：上电；
                                                         0：下电 */
        unsigned int  wtc_mtcmos_rdy : 1;  /* bit[1]   : WTC电源域上电状态。
                                                         1：上电；
                                                         0：下电 */
        unsigned int  irm_mtcmos_rdy : 1;  /* bit[2]   : IRM电源域上电状态。
                                                         1：上电；
                                                         0：下电 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_STAT00_UNION;
#define BBPSCTRL_BBP_STAT00_lte_mtcmos_rdy_START  (0)
#define BBPSCTRL_BBP_STAT00_lte_mtcmos_rdy_END    (0)
#define BBPSCTRL_BBP_STAT00_wtc_mtcmos_rdy_START  (1)
#define BBPSCTRL_BBP_STAT00_wtc_mtcmos_rdy_END    (1)
#define BBPSCTRL_BBP_STAT00_irm_mtcmos_rdy_START  (2)
#define BBPSCTRL_BBP_STAT00_irm_mtcmos_rdy_END    (2)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_STAT06_UNION
 结构说明  : BBP_STAT06 寄存器结构定义。地址偏移量:0x0318，初值:0x00000000，宽度:32
 寄存器说明: BBP MST状态寄存器
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat06_reg;
    struct
    {
        unsigned int  mst_err  : 8;  /* bit[0-7] : bbp中dw_axi_mst的error信号 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_STAT06_UNION;
#define BBPSCTRL_BBP_STAT06_mst_err_START   (0)
#define BBPSCTRL_BBP_STAT06_mst_err_END     (7)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_STAT0B_UNION
 结构说明  : BBP_STAT0B 寄存器结构定义。地址偏移量:0x032C，初值:0x00000000，宽度:32
 寄存器说明: BBP MST DLOCK状态寄存器
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat0b_reg;
    struct
    {
        unsigned int  dlock_mst : 2;  /* bit[0-1]  : DLOCK MST编号。 */
        unsigned int  dlock_slv : 2;  /* bit[2-3]  : DLOCK SLV编号。 */
        unsigned int  dlock_id  : 6;  /* bit[4-9]  : DLOCK ID。 */
        unsigned int  dlock_wr  : 1;  /* bit[10]   : DLOCK的读写操作。 */
        unsigned int  dlock_irq : 1;  /* bit[11]   : DLOCK IRQ。 */
        unsigned int  reserved  : 20; /* bit[12-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_STAT0B_UNION;
#define BBPSCTRL_BBP_STAT0B_dlock_mst_START  (0)
#define BBPSCTRL_BBP_STAT0B_dlock_mst_END    (1)
#define BBPSCTRL_BBP_STAT0B_dlock_slv_START  (2)
#define BBPSCTRL_BBP_STAT0B_dlock_slv_END    (3)
#define BBPSCTRL_BBP_STAT0B_dlock_id_START   (4)
#define BBPSCTRL_BBP_STAT0B_dlock_id_END     (9)
#define BBPSCTRL_BBP_STAT0B_dlock_wr_START   (10)
#define BBPSCTRL_BBP_STAT0B_dlock_wr_END     (10)
#define BBPSCTRL_BBP_STAT0B_dlock_irq_START  (11)
#define BBPSCTRL_BBP_STAT0B_dlock_irq_END    (11)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_STAT0D_UNION
 结构说明  : BBP_STAT0D 寄存器结构定义。地址偏移量:0x0334，初值:0x00000000，宽度:32
 寄存器说明: BBP状态寄存器0D(IRM2COM_TBD)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat0d_reg;
    struct
    {
        unsigned int  irm2com_tbd : 16; /* bit[0-15] : IRM给COM的预留eco信号。 */
        unsigned int  reserved    : 16; /* bit[16-31]: 保留。 */
    } reg;
} BBPSCTRL_BBP_STAT0D_UNION;
#define BBPSCTRL_BBP_STAT0D_irm2com_tbd_START  (0)
#define BBPSCTRL_BBP_STAT0D_irm2com_tbd_END    (15)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_STAT0F_UNION
 结构说明  : BBP_STAT0F 寄存器结构定义。地址偏移量:0x033C，初值:0x00000000，宽度:32
 寄存器说明: BBP状态寄存器0F(LBUS防挂死中断状态)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat0f_reg;
    struct
    {
        unsigned int  ulhb_err_power_int_status           : 1;  /* bit[0] : 0：正常。
                                                                            1：电源关闭。 */
        unsigned int  ulhb_err_clk_int_status             : 1;  /* bit[1] : 0：正常。
                                                                            1：时钟关闭。 */
        unsigned int  ulhb_err_rst_int_status             : 1;  /* bit[2] : 0：正常。
                                                                            1：复位。 */
        unsigned int  ulhb_err_rd_timeout_int_status      : 1;  /* bit[3] : 0：正常。
                                                                            1：超时。 */
        unsigned int  pdf_err_power_int_status            : 1;  /* bit[4] : 0：正常。
                                                                            1：电源关闭。 */
        unsigned int  pdf_err_clk_int_status              : 1;  /* bit[5] : 0：正常。
                                                                            1：时钟关闭。 */
        unsigned int  pdf_err_rst_int_status              : 1;  /* bit[6] : 0：正常。
                                                                            1：复位。 */
        unsigned int  pdf_err_rd_timeout_int_status       : 1;  /* bit[7] : 0：正常。
                                                                            1：超时。 */
        unsigned int  pdt_err_power_int_status            : 1;  /* bit[8] : 0：正常。
                                                                            1：电源关闭。 */
        unsigned int  pdt_err_clk_int_status              : 1;  /* bit[9] : 0：正常。
                                                                            1：时钟关闭。 */
        unsigned int  pdt_err_rst_int_status              : 1;  /* bit[10]: 0：正常。
                                                                            1：复位。 */
        unsigned int  pdt_err_rd_timeout_int_status       : 1;  /* bit[11]: 0：正常。
                                                                            1：超时。 */
        unsigned int  tds245_err_power_int_status         : 1;  /* bit[12]: 0：正常。
                                                                            1：电源关闭。 */
        unsigned int  tds245_err_clk_int_status           : 1;  /* bit[13]: 0：正常。
                                                                            1：时钟关闭。 */
        unsigned int  tds245_err_rst_int_status           : 1;  /* bit[14]: 0：正常。
                                                                            1：复位。 */
        unsigned int  tds245_err_rd_timeout_int_status    : 1;  /* bit[15]: 0：正常。
                                                                            1：超时。 */
        unsigned int  ux_tds122_err_power_int_status      : 1;  /* bit[16]: 0：正常。
                                                                            1：电源关闭。 */
        unsigned int  ux_tds122_err_clk_int_status        : 1;  /* bit[17]: 0：正常。
                                                                            1：时钟关闭。 */
        unsigned int  ux_tds122_err_rst_int_status        : 1;  /* bit[18]: 0：正常。
                                                                            1：复位。 */
        unsigned int  ux_tds122_err_rd_timeout_int_status : 1;  /* bit[19]: 0：正常。
                                                                            1：超时。 */
        unsigned int  g_err_clk_int_status                : 1;  /* bit[20]: 0：正常。
                                                                            1：时钟关闭。 */
        unsigned int  g_err_rst_int_status                : 1;  /* bit[21]: 0：正常。
                                                                            1：复位。 */
        unsigned int  g_err_rd_timeout_int_status         : 1;  /* bit[22]: 0：正常。
                                                                            1：超时。 */
        unsigned int  b2s_err_rd_timeout_int_status       : 1;  /* bit[23]: 0：正常。
                                                                            1：超时。 */
        unsigned int  uc2_err_power_int_status            : 1;  /* bit[24]: 0：正常。
                                                                            1：电源关闭。 */
        unsigned int  uc2_err_clk_int_status              : 1;  /* bit[25]: 0：正常。
                                                                            1：时钟关闭。 */
        unsigned int  uc2_err_rst_int_status              : 1;  /* bit[26]: 0：正常。
                                                                            1：复位。 */
        unsigned int  uc2_err_rd_timeout_int_status       : 1;  /* bit[27]: 0：正常。
                                                                            1：超时。 */
        unsigned int  axi_arb_overtime_int_status         : 1;  /* bit[28]: 0：正常。
                                                                            1：超时。 */
        unsigned int  dma_arb_overtime_int_status         : 1;  /* bit[29]: 0：正常。
                                                                            1：超时。 */
        unsigned int  dbgtrig_arb_overtime_int_status     : 1;  /* bit[30]: 0：正常。
                                                                            1：超时。 */
        unsigned int  reserved                            : 1;  /* bit[31]: 0：正常
                                                                            1：超时
                                                                            正常，不会触发中断。
                                                                            其他，会触发中断。
                                                                            写该寄存器则对应bite清零。 */
    } reg;
} BBPSCTRL_BBP_STAT0F_UNION;
#define BBPSCTRL_BBP_STAT0F_ulhb_err_power_int_status_START            (0)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_power_int_status_END              (0)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_clk_int_status_START              (1)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_clk_int_status_END                (1)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rst_int_status_START              (2)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rst_int_status_END                (2)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rd_timeout_int_status_START       (3)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rd_timeout_int_status_END         (3)
#define BBPSCTRL_BBP_STAT0F_pdf_err_power_int_status_START             (4)
#define BBPSCTRL_BBP_STAT0F_pdf_err_power_int_status_END               (4)
#define BBPSCTRL_BBP_STAT0F_pdf_err_clk_int_status_START               (5)
#define BBPSCTRL_BBP_STAT0F_pdf_err_clk_int_status_END                 (5)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rst_int_status_START               (6)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rst_int_status_END                 (6)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rd_timeout_int_status_START        (7)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rd_timeout_int_status_END          (7)
#define BBPSCTRL_BBP_STAT0F_pdt_err_power_int_status_START             (8)
#define BBPSCTRL_BBP_STAT0F_pdt_err_power_int_status_END               (8)
#define BBPSCTRL_BBP_STAT0F_pdt_err_clk_int_status_START               (9)
#define BBPSCTRL_BBP_STAT0F_pdt_err_clk_int_status_END                 (9)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rst_int_status_START               (10)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rst_int_status_END                 (10)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rd_timeout_int_status_START        (11)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rd_timeout_int_status_END          (11)
#define BBPSCTRL_BBP_STAT0F_tds245_err_power_int_status_START          (12)
#define BBPSCTRL_BBP_STAT0F_tds245_err_power_int_status_END            (12)
#define BBPSCTRL_BBP_STAT0F_tds245_err_clk_int_status_START            (13)
#define BBPSCTRL_BBP_STAT0F_tds245_err_clk_int_status_END              (13)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rst_int_status_START            (14)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rst_int_status_END              (14)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rd_timeout_int_status_START     (15)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rd_timeout_int_status_END       (15)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_power_int_status_START       (16)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_power_int_status_END         (16)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_clk_int_status_START         (17)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_clk_int_status_END           (17)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rst_int_status_START         (18)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rst_int_status_END           (18)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rd_timeout_int_status_START  (19)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rd_timeout_int_status_END    (19)
#define BBPSCTRL_BBP_STAT0F_g_err_clk_int_status_START                 (20)
#define BBPSCTRL_BBP_STAT0F_g_err_clk_int_status_END                   (20)
#define BBPSCTRL_BBP_STAT0F_g_err_rst_int_status_START                 (21)
#define BBPSCTRL_BBP_STAT0F_g_err_rst_int_status_END                   (21)
#define BBPSCTRL_BBP_STAT0F_g_err_rd_timeout_int_status_START          (22)
#define BBPSCTRL_BBP_STAT0F_g_err_rd_timeout_int_status_END            (22)
#define BBPSCTRL_BBP_STAT0F_b2s_err_rd_timeout_int_status_START        (23)
#define BBPSCTRL_BBP_STAT0F_b2s_err_rd_timeout_int_status_END          (23)
#define BBPSCTRL_BBP_STAT0F_uc2_err_power_int_status_START             (24)
#define BBPSCTRL_BBP_STAT0F_uc2_err_power_int_status_END               (24)
#define BBPSCTRL_BBP_STAT0F_uc2_err_clk_int_status_START               (25)
#define BBPSCTRL_BBP_STAT0F_uc2_err_clk_int_status_END                 (25)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rst_int_status_START               (26)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rst_int_status_END                 (26)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rd_timeout_int_status_START        (27)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rd_timeout_int_status_END          (27)
#define BBPSCTRL_BBP_STAT0F_axi_arb_overtime_int_status_START          (28)
#define BBPSCTRL_BBP_STAT0F_axi_arb_overtime_int_status_END            (28)
#define BBPSCTRL_BBP_STAT0F_dma_arb_overtime_int_status_START          (29)
#define BBPSCTRL_BBP_STAT0F_dma_arb_overtime_int_status_END            (29)
#define BBPSCTRL_BBP_STAT0F_dbgtrig_arb_overtime_int_status_START      (30)
#define BBPSCTRL_BBP_STAT0F_dbgtrig_arb_overtime_int_status_END        (30)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_STAT10_UNION
 结构说明  : BBP_STAT10 寄存器结构定义。地址偏移量:0x0340，初值:0x00000000，宽度:32
 寄存器说明: BBP状态寄存器10(COM中时钟状态，非clk_en对称)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat10_reg;
    struct
    {
        unsigned int  reserved_0                     : 1;  /* bit[0]    : 保留 */
        unsigned int  reserved_1                     : 1;  /* bit[1]    : 保留 */
        unsigned int  reserved_2                     : 1;  /* bit[2]    : 保留 */
        unsigned int  reserved_3                     : 1;  /* bit[3]    : 保留 */
        unsigned int  com_g12com_abb0_tx_mclk_status : 1;  /* bit[4]    : 0：无时钟
                                                                          1：有时钟 */
        unsigned int  com_g22com_abb0_tx_mclk_status : 1;  /* bit[5]    : 0：无时钟
                                                                          1：有时钟 */
        unsigned int  com_g_sleep_clk_status         : 1;  /* bit[6]    : 0：无时钟
                                                                          1：有时钟
                                                                          G模公共，32K时钟的状态。 */
        unsigned int  com_g_sys_clk_status           : 1;  /* bit[7]    : 0：无时钟
                                                                          1：有时钟
                                                                          G模公共，19.2M时钟的状态 */
        unsigned int  com_g_com_clk_status           : 1;  /* bit[8]    : 0：无时钟
                                                                          1：有时钟
                                                                          G模公共，即LBUS时钟状态。 */
        unsigned int  com_g1_sdr_com_clk_status      : 1;  /* bit[9]    : 0：无时钟
                                                                          1：有时钟
                                                                          G模公共，G1和GSDR的公共逻辑的104M时钟状态。 */
        unsigned int  com_l2com_abb0_tx_mclk_status  : 1;  /* bit[10]   : 0：无时钟
                                                                          1：有时钟 */
        unsigned int  com_l2com_abb1_tx_mclk_status  : 1;  /* bit[11]   : 0：无时钟
                                                                          1：有时钟 */
        unsigned int  com_lte_pdf_clk_status         : 1;  /* bit[12]   : 0：无时钟
                                                                          1：有时钟
                                                                          LTE PDF LBUS时钟状态。 */
        unsigned int  com_lte_pdt_clk_status         : 1;  /* bit[13]   : 0：无时钟
                                                                          1：有时钟
                                                                          LTE PDT LBUS时钟状态。 */
        unsigned int  com_lte_ulhb_clk_status        : 1;  /* bit[14]   : 0：无时钟
                                                                          1：有时钟
                                                                          LTE ULHB LBUS时钟状态 */
        unsigned int  com_axim_clk_status            : 1;  /* bit[15]   : 0：无时钟
                                                                          1：有时钟 */
        unsigned int  com_tds_122_clk_status         : 1;  /* bit[16]   : 0：无时钟
                                                                          1：有时钟
                                                                          没有使用。 */
        unsigned int  com_tds_245_clk_status         : 1;  /* bit[17]   : 0：无时钟
                                                                          1：有时钟
                                                                          TDS 245 LBUS时钟状态 */
        unsigned int  com_tds_dbg_clk_status         : 1;  /* bit[18]   : 0：无时钟
                                                                          1：有时钟 */
        unsigned int  com_tl_dbg_sys_clk_status      : 1;  /* bit[19]   : 0：无时钟
                                                                          1：有时钟 */
        unsigned int  com_wtc_122_clk_status         : 1;  /* bit[20]   : 0：无时钟
                                                                          1：有时钟
                                                                          WTC 122 LBUS时钟状态 */
        unsigned int  reserved_4                     : 11; /* bit[21-31]: 保留。
                                                                          这些都是COM_TOP中的时钟状态。 */
    } reg;
} BBPSCTRL_BBP_STAT10_UNION;
#define BBPSCTRL_BBP_STAT10_com_g12com_abb0_tx_mclk_status_START  (4)
#define BBPSCTRL_BBP_STAT10_com_g12com_abb0_tx_mclk_status_END    (4)
#define BBPSCTRL_BBP_STAT10_com_g22com_abb0_tx_mclk_status_START  (5)
#define BBPSCTRL_BBP_STAT10_com_g22com_abb0_tx_mclk_status_END    (5)
#define BBPSCTRL_BBP_STAT10_com_g_sleep_clk_status_START          (6)
#define BBPSCTRL_BBP_STAT10_com_g_sleep_clk_status_END            (6)
#define BBPSCTRL_BBP_STAT10_com_g_sys_clk_status_START            (7)
#define BBPSCTRL_BBP_STAT10_com_g_sys_clk_status_END              (7)
#define BBPSCTRL_BBP_STAT10_com_g_com_clk_status_START            (8)
#define BBPSCTRL_BBP_STAT10_com_g_com_clk_status_END              (8)
#define BBPSCTRL_BBP_STAT10_com_g1_sdr_com_clk_status_START       (9)
#define BBPSCTRL_BBP_STAT10_com_g1_sdr_com_clk_status_END         (9)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb0_tx_mclk_status_START   (10)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb0_tx_mclk_status_END     (10)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb1_tx_mclk_status_START   (11)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb1_tx_mclk_status_END     (11)
#define BBPSCTRL_BBP_STAT10_com_lte_pdf_clk_status_START          (12)
#define BBPSCTRL_BBP_STAT10_com_lte_pdf_clk_status_END            (12)
#define BBPSCTRL_BBP_STAT10_com_lte_pdt_clk_status_START          (13)
#define BBPSCTRL_BBP_STAT10_com_lte_pdt_clk_status_END            (13)
#define BBPSCTRL_BBP_STAT10_com_lte_ulhb_clk_status_START         (14)
#define BBPSCTRL_BBP_STAT10_com_lte_ulhb_clk_status_END           (14)
#define BBPSCTRL_BBP_STAT10_com_axim_clk_status_START             (15)
#define BBPSCTRL_BBP_STAT10_com_axim_clk_status_END               (15)
#define BBPSCTRL_BBP_STAT10_com_tds_122_clk_status_START          (16)
#define BBPSCTRL_BBP_STAT10_com_tds_122_clk_status_END            (16)
#define BBPSCTRL_BBP_STAT10_com_tds_245_clk_status_START          (17)
#define BBPSCTRL_BBP_STAT10_com_tds_245_clk_status_END            (17)
#define BBPSCTRL_BBP_STAT10_com_tds_dbg_clk_status_START          (18)
#define BBPSCTRL_BBP_STAT10_com_tds_dbg_clk_status_END            (18)
#define BBPSCTRL_BBP_STAT10_com_tl_dbg_sys_clk_status_START       (19)
#define BBPSCTRL_BBP_STAT10_com_tl_dbg_sys_clk_status_END         (19)
#define BBPSCTRL_BBP_STAT10_com_wtc_122_clk_status_START          (20)
#define BBPSCTRL_BBP_STAT10_com_wtc_122_clk_status_END            (20)


/*****************************************************************************
 结构名    : BBPSCTRL_BBP_STAT1F_UNION
 结构说明  : BBP_STAT1F 寄存器结构定义。地址偏移量:0x037C，初值:0x00000000，宽度:32
 寄存器说明: 各电源域入口时钟的时钟状态，每个PD一个时钟使能，开启后每个PD的入口时钟全部打开。
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat1f_reg;
    struct
    {
        unsigned int  bbc_104m_clk_pstat        : 1;  /* bit[0]    :  */
        unsigned int  bbc_19m_clk_pstat         : 1;  /* bit[1]    :  */
        unsigned int  bbc_32k_clk_pstat         : 1;  /* bit[2]    :  */
        unsigned int  bbc_scpll_uc2_clk_pstat   : 1;  /* bit[3]    :  */
        unsigned int  bbc_scpll_clk_pstat       : 1;  /* bit[4]    :  */
        unsigned int  pd3gp_19m_clk_pstat       : 1;  /* bit[5]    :  */
        unsigned int  pd3gp_32k_clk_pstat       : 1;  /* bit[6]    :  */
        unsigned int  pd3gp_scpll_uc2_clk_pstat : 1;  /* bit[7]    :  */
        unsigned int  pd3gp_scpll_clk_pstat     : 1;  /* bit[8]    :  */
        unsigned int  pdirm_axis_clk_pstat      : 1;  /* bit[9]    :  */
        unsigned int  pdirm_scpll_clk_pstat     : 1;  /* bit[10]   :  */
        unsigned int  pdirm_tdl_clk_pstat       : 1;  /* bit[11]   :  */
        unsigned int  pdlte_19m_clk_pstat       : 1;  /* bit[12]   :  */
        unsigned int  pdlte_32k_clk_pstat       : 1;  /* bit[13]   :  */
        unsigned int  pdlte_axim_clk_pstat      : 1;  /* bit[14]   :  */
        unsigned int  pdlte_scpll_clk_pstat     : 1;  /* bit[15]   :  */
        unsigned int  pdlte_tdl_clk_pstat       : 1;  /* bit[16]   :  */
        unsigned int  reserved                  : 15; /* bit[17-31]: 保留 */
    } reg;
} BBPSCTRL_BBP_STAT1F_UNION;
#define BBPSCTRL_BBP_STAT1F_bbc_104m_clk_pstat_START         (0)
#define BBPSCTRL_BBP_STAT1F_bbc_104m_clk_pstat_END           (0)
#define BBPSCTRL_BBP_STAT1F_bbc_19m_clk_pstat_START          (1)
#define BBPSCTRL_BBP_STAT1F_bbc_19m_clk_pstat_END            (1)
#define BBPSCTRL_BBP_STAT1F_bbc_32k_clk_pstat_START          (2)
#define BBPSCTRL_BBP_STAT1F_bbc_32k_clk_pstat_END            (2)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_uc2_clk_pstat_START    (3)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_uc2_clk_pstat_END      (3)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_clk_pstat_START        (4)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_clk_pstat_END          (4)
#define BBPSCTRL_BBP_STAT1F_pd3gp_19m_clk_pstat_START        (5)
#define BBPSCTRL_BBP_STAT1F_pd3gp_19m_clk_pstat_END          (5)
#define BBPSCTRL_BBP_STAT1F_pd3gp_32k_clk_pstat_START        (6)
#define BBPSCTRL_BBP_STAT1F_pd3gp_32k_clk_pstat_END          (6)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_uc2_clk_pstat_START  (7)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_uc2_clk_pstat_END    (7)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_clk_pstat_START      (8)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_clk_pstat_END        (8)
#define BBPSCTRL_BBP_STAT1F_pdirm_axis_clk_pstat_START       (9)
#define BBPSCTRL_BBP_STAT1F_pdirm_axis_clk_pstat_END         (9)
#define BBPSCTRL_BBP_STAT1F_pdirm_scpll_clk_pstat_START      (10)
#define BBPSCTRL_BBP_STAT1F_pdirm_scpll_clk_pstat_END        (10)
#define BBPSCTRL_BBP_STAT1F_pdirm_tdl_clk_pstat_START        (11)
#define BBPSCTRL_BBP_STAT1F_pdirm_tdl_clk_pstat_END          (11)
#define BBPSCTRL_BBP_STAT1F_pdlte_19m_clk_pstat_START        (12)
#define BBPSCTRL_BBP_STAT1F_pdlte_19m_clk_pstat_END          (12)
#define BBPSCTRL_BBP_STAT1F_pdlte_32k_clk_pstat_START        (13)
#define BBPSCTRL_BBP_STAT1F_pdlte_32k_clk_pstat_END          (13)
#define BBPSCTRL_BBP_STAT1F_pdlte_axim_clk_pstat_START       (14)
#define BBPSCTRL_BBP_STAT1F_pdlte_axim_clk_pstat_END         (14)
#define BBPSCTRL_BBP_STAT1F_pdlte_scpll_clk_pstat_START      (15)
#define BBPSCTRL_BBP_STAT1F_pdlte_scpll_clk_pstat_END        (15)
#define BBPSCTRL_BBP_STAT1F_pdlte_tdl_clk_pstat_START        (16)
#define BBPSCTRL_BBP_STAT1F_pdlte_tdl_clk_pstat_END          (16)




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

#endif /* end of bbp_sctrl_interface.h */
