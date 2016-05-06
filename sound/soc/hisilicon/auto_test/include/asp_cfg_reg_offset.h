//****************************************************************************** 
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  asp_cfg_reg_offset.h
// Author        :  huangji
// Version       :  1.0 
// Date          :  2014-09-17
// Description   :  Define all registers/tables for hiaspv300
// Others        :  Generated automatically by nManager V4.0 
// History       :  huangji 2014-09-17 Create file
//******************************************************************************

#ifndef __ASP_CFG_REG_OFFSET_H__
#define __ASP_CFG_REG_OFFSET_H__

/* ASP_CFG Base address of Module's Register */
#define HI3650_ASP_CFG_BASE                       (0xe804e000)

/******************************************************************************/
/*                      hiaspv300 ASP_CFG Registers' Definitions                            */
/******************************************************************************/

#define HI3650_ASP_CFG_R_RST_CTRLEN_REG                         (0 + 0x0)   /* 外设软复位使能寄存器 */                    
#define HI3650_ASP_CFG_R_RST_CTRLDIS_REG                        (0 + 0x4)   /* 外设软复位撤离寄存器 */                    
#define HI3650_ASP_CFG_R_RST_CTRLSTAT_REG                       (0 + 0x8)   /* 外设软复位状态寄存器 */                    
#define HI3650_ASP_CFG_R_GATE_EN_REG                            (0 + 0xC)   /* 时钟使能寄存器 */                       
#define HI3650_ASP_CFG_R_GATE_DIS_REG                           (0 + 0x10)  /* 时钟禁止寄存器 */                       
#define HI3650_ASP_CFG_R_GATE_CLKEN_REG                         (0 + 0x14)  /* 时钟使能状态寄存器 */                     
#define HI3650_ASP_CFG_R_GATE_CLKSTAT_REG                       (0 + 0x18)  /* 时钟最终状态寄存器 */                     
#define HI3650_ASP_CFG_R_GATE_CLKDIV_EN_REG                     (0 + 0x1C)  /* 时钟分频器门控使能寄存器 */                  
#define HI3650_ASP_CFG_R_CLK1_DIV_REG                           (0 + 0x20)  /* 分频比控制寄存器1 */                     
#define HI3650_ASP_CFG_R_CLK2_DIV_REG                           (0 + 0x24)  /* 分频比控制寄存器2 */                     
#define HI3650_ASP_CFG_R_CLK3_DIV_REG                           (0 + 0x28)  /* 分频比控制寄存器3 */                     
#define HI3650_ASP_CFG_R_CLK4_DIV_REG                           (0 + 0x2C)  /* 分频比控制寄存器4 */                     
#define HI3650_ASP_CFG_R_CLK5_DIV_REG                           (0 + 0x30)  /* 分频比控制寄存器5 */                     
#define HI3650_ASP_CFG_R_CLK6_DIV_REG                           (0 + 0x34)  /* 分频比控制寄存器6 */                     
#define HI3650_ASP_CFG_R_CLK_SEL_REG                            (0 + 0x38)  /* 时钟选择寄存器 */                       
#define HI3650_ASP_CFG_R_DSP_NMI_REG                            (0 + 0x3C)  /* DSP NMI中断产生寄存器 */                
#define HI3650_ASP_CFG_R_DSP_PRID_REG                           (0 + 0x40)  /* DSP PRID设置寄存器 */                 
#define HI3650_ASP_CFG_R_DSP_RUNSTALL_REG                       (0 + 0x44)  /* DSP RUNSTALL设置寄存器 */             
#define HI3650_ASP_CFG_R_DSP_STATVECTORSEL_REG                  (0 + 0x48)  /* DSP STATVECTORSEL设置寄存器 */        
#define HI3650_ASP_CFG_R_DSP_OCDHALTONRESET_REG                 (0 + 0x4C)  /* DSP OCDHALTONRESET设置寄存器 */       
#define HI3650_ASP_CFG_R_DSP_STATUS_REG                         (0 + 0x50)  /* DSP 状态寄存器 */                     
#define HI3650_ASP_CFG_R_DMAC_SEL_REG                           (0 + 0x54)  /* DMAC通道选择寄存器 */                   
#define HI3650_ASP_CFG_R_BUS_PRIORITY_REG                       (0 + 0x58)  /* 总线优先级配置寄存器 */                    
#define HI3650_ASP_CFG_R_CG_EN_REG                              (0 + 0x5C)  /* 自动门控使能寄存器 */                     
#define HI3650_ASP_CFG_R_OCRAM_RET_REG                          (0 + 0x60)  /* ocram低功耗配置寄存器 */                 
#define HI3650_ASP_CFG_R_INTR_NS_INI_REG                        (0 + 0x64)  /* 非安全中断原始状态寄存器 */                  
#define HI3650_ASP_CFG_R_INTR_NS_EN_REG                         (0 + 0x68)  /* 非安全中断使能寄存器 */                    
#define HI3650_ASP_CFG_R_INTR_NS_MASK_REG                       (0 + 0x6C)  /* 非安全中断屏蔽后状态寄存器 */                 
#define HI3650_ASP_CFG_R_DBG_SET_AHB2AXI_REG                    (0 + 0x70)  /* 付强桥DBG信号设置寄存器 */                 
#define HI3650_ASP_CFG_R_DBG_STATUS_AHB2AXI_REG                 (0 + 0x74)  /* 付强桥DBG信号状态寄存器 */                 
#define HI3650_ASP_CFG_R_DLOCK_BP_REG                           (0 + 0x78)  /* 总线防挂死bypass寄存器 */                
#define HI3650_ASP_CFG_R_DSP_BINTERRUPT_REG                     (0 + 0x7C)  /* 上报到hifi dsp的中断信号只读寄存器 */         
#define HI3650_ASP_CFG_R_DSP_RAM_RET_REG                        (0 + 0x84)  
#define HI3650_ASP_CFG_R_TZ_SECURE_N_REG                        (0 + 0x100) 
#define HI3650_ASP_CFG_R_OCRAM_R0SIZE_REG                       (0 + 0x104) 
#define HI3650_ASP_CFG_R_SIO_LOOP_SECURE_N_REG                  (0 + 0x108) 
#define HI3650_ASP_CFG_R_INTR_S_INI_REG                         (0 + 0x10C) /* 安全中断原始状态寄存器 */                   
#define HI3650_ASP_CFG_R_INTR_S_EN_REG                          (0 + 0x110) /* 安全中断使能寄存器 */                     
#define HI3650_ASP_CFG_R_INTR_S_MASK_REG                        (0 + 0x114) /* 安全中断屏蔽后状态寄存器 */                  
#define HI3650_ASP_CFG_R_DSP_REMAPPING_EN_REG                   (0 + 0x118) /* dsp地址重映射使能寄存器 */                 
#define HI3650_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_REG        (0 + 0x11C) /* DSP 地址重映射寄存器 */                  
#define HI3650_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_REG        (0 + 0x120) /* DSP 地址重映射寄存器 */                  
#define HI3650_ASP_CFG_R_DDR_HARQ_REMAP_EN_REG                  (0 + 0x124) /* DDR与Harq Memory remap控制寄存器 */    
#define HI3650_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_REG       (0 + 0x128) /* DDR与Harq Memory remap源基地址寄存器 */  
#define HI3650_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_REG       (0 + 0x12C) /* DDR与Harq Memory remap目标基地址寄存器 */ 
#define HI3650_ASP_CFG_R_DDR_MMBUF_REMAP_EN_REG                 (0 + 0x130) /* DDR与MMBUF remap控制寄存器 */          
#define HI3650_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_REG      (0 + 0x134) /* DDR与MMBUF remap源基地址寄存器 */        
#define HI3650_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_REG      (0 + 0x138) /* DDR与MMBUF remap目标基地址寄存器 */       
#define HI3650_ASP_CFG_R_DDR_OCRAM_REMAP_EN_REG                 (0 + 0x13C) /* DDR与OCRAM remap控制寄存器 */          
#define HI3650_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_REG      (0 + 0x140) /* DDR与OCRAM remap源基地址寄存器 */        
#define HI3650_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_REG      (0 + 0x144) /* DDR与OCRAM remap目标基地址寄存器 */       
#define HI3650_ASP_CFG_R_MMBUF_CTRL_REG                         (0 + 0x148) /* MMBUF CTRL配置寄存器 */               
#define HI3650_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_REG               (0 + 0x14C) /* HIFIDSP时钟频率自动调频配置寄存器 */          
#define HI3650_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_REG               (0 + 0x150) /* 频偏记录模块配置寄存器 */                   
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_REG        (0 + 0x160) /* 内存监控模块使能配置寄存器 */                 
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_REG  (0 + 0x164) /* 内存监控模块中断清零配置寄存器 */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_REG   (0 + 0x168) /* 内存监控模块中断使能配置寄存器 */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_REG (0 + 0x16C) /* 内存监控模块中断状态寄存器 */                 
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_REG     (0 + 0x170) /* 内存监控模块0基地址配置寄存器 */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_REG      (0 + 0x174) /* 内存监控模块0地址长度配置寄存器 */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_REG    (0 + 0x178) /* 内存监控模块0越界的写地址记录寄存器 */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_REG    (0 + 0x17C) /* 内存监控模块0越界的读地址记录寄存器 */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_REG     (0 + 0x180) /* 内存监控模块1基地址配置寄存器 */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_REG      (0 + 0x184) /* 内存监控模块1地址长度配置寄存器 */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_REG    (0 + 0x188) /* 内存监控模块1越界的写地址记录寄存器 */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_REG    (0 + 0x18C) /* 内存监控模块1越界的读地址记录寄存器 */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_REG     (0 + 0x190) /* 内存监控模块2基地址配置寄存器 */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_REG      (0 + 0x194) /* 内存监控模块2地址长度配置寄存器 */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_REG    (0 + 0x198) /* 内存监控模块2越界的写地址记录寄存器 */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_REG    (0 + 0x19C) /* 内存监控模块2越界的读地址记录寄存器 */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_REG     (0 + 0x1A0) /* 内存监控模块3基地址配置寄存器 */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_REG      (0 + 0x1A4) /* 内存监控模块3地址长度配置寄存器 */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_REG    (0 + 0x1A8) /* 内存监控模块3越界的写地址记录寄存器 */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_REG    (0 + 0x1AC) /* 内存监控模块3越界的读地址记录寄存器 */            
#define HI3650_ASP_CFG_R_MEMORY_CTRL_REG                        (0 + 0x1B0) /* memory控制配置寄存器 */                 
#define HI3650_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_REG               (0 + 0x1B4) /* slimbus primary配置寄存器 */          
#define HI3650_ASP_CFG_R_SLIMBUS_ID_ADDR_REG                    (0 + 0x1B8) /* slimbus id配置寄存器 */               
#define HI3650_ASP_CFG_R_SECURE_AUTHORITY_EN_REG                (0 + 0x200) /* 安全访问属性控制寄存器 */                   

#endif // __ASP_CFG_REG_OFFSET_H__
