/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_usb3otg_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-15 11:19:52
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月15日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_USB3OTG.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_USB3OTG_INTERFACE_H__
#define __SOC_USB3OTG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：功能寄存器长度
   位域定义UNION结构:  SOC_USB3OTG_CAPLENGTH_UNION */
#define SOC_USB3OTG_CAPLENGTH_ADDR(base)              ((base) + (0x0000))

/* 寄存器说明：结构参数1
   位域定义UNION结构:  SOC_USB3OTG_HCSPARAMS1_UNION */
#define SOC_USB3OTG_HCSPARAMS1_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：结构参数2
   位域定义UNION结构:  SOC_USB3OTG_HCSPARAMS2_UNION */
#define SOC_USB3OTG_HCSPARAMS2_ADDR(base)             ((base) + (0x0008))

/* 寄存器说明：结构参数3
   位域定义UNION结构:  SOC_USB3OTG_HCSPARAMS3_UNION */
#define SOC_USB3OTG_HCSPARAMS3_ADDR(base)             ((base) + (0x000C))

/* 寄存器说明：功能特性参数
   位域定义UNION结构:  SOC_USB3OTG_HCCPARAMS_UNION */
#define SOC_USB3OTG_HCCPARAMS_ADDR(base)              ((base) + (0x0010))

/* 寄存器说明：Doorbell Array偏移地址
   位域定义UNION结构:  SOC_USB3OTG_DBOFF_UNION */
#define SOC_USB3OTG_DBOFF_ADDR(base)                  ((base) + (0x0014))

/* 寄存器说明：RunTimer空间偏移地址
   位域定义UNION结构:  SOC_USB3OTG_RTSOFF_UNION */
#define SOC_USB3OTG_RTSOFF_ADDR(base)                 ((base) + (0x0018))

/* 寄存器说明：命令寄存器
   位域定义UNION结构:  SOC_USB3OTG_USBCMD_UNION */
#define SOC_USB3OTG_USBCMD_ADDR(base)                 ((base) + (0x0020))

/* 寄存器说明：状态寄存器
   位域定义UNION结构:  SOC_USB3OTG_USBSTS_UNION */
#define SOC_USB3OTG_USBSTS_ADDR(base)                 ((base) + (0x0024))

/* 寄存器说明：页大小寄存器
   位域定义UNION结构:  SOC_USB3OTG_PAGESIZE_UNION */
#define SOC_USB3OTG_PAGESIZE_ADDR(base)               ((base) + (0x0028))

/* 寄存器说明：
   位域定义UNION结构:  SOC_USB3OTG_DNCTRL_UNION */
#define SOC_USB3OTG_DNCTRL_ADDR(base)                 ((base) + (0x0034))

/* 寄存器说明：Command Ring Control寄存器低32位
   位域定义UNION结构:  SOC_USB3OTG_CRCR_L_UNION */
#define SOC_USB3OTG_CRCR_L_ADDR(base)                 ((base) + (0x0038))

/* 寄存器说明：Command Ring Control寄存器高32位
   位域定义UNION结构:  SOC_USB3OTG_CRCR_H_UNION */
#define SOC_USB3OTG_CRCR_H_ADDR(base)                 ((base) + (0x003C))

/* 寄存器说明：Device Context Basic Address Array Pointer低32位
   位域定义UNION结构:  SOC_USB3OTG_DCBAAP_L_UNION */
#define SOC_USB3OTG_DCBAAP_L_ADDR(base)               ((base) + (0x0050))

/* 寄存器说明：Device Context Basic Address Array Pointer高32位
   位域定义UNION结构:  SOC_USB3OTG_DCBAAP_H_UNION */
#define SOC_USB3OTG_DCBAAP_H_ADDR(base)               ((base) + (0x0054))

/* 寄存器说明：配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_CONFIG_UNION */
#define SOC_USB3OTG_CONFIG_ADDR(base)                 ((base) + (0x0058))

/* 寄存器说明：端口控制和状态寄存器
   位域定义UNION结构:  SOC_USB3OTG_PORTSC_UNION */
#define SOC_USB3OTG_PORTSC_ADDR(base)                 ((base) + (0x0420))

/* 寄存器说明：端口功耗控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_PORTPMSC_20_UNION */
#define SOC_USB3OTG_PORTPMSC_20_ADDR(base)            ((base) + (0x0424))

/* 寄存器说明：Port Link Information寄存器
   位域定义UNION结构:  SOC_USB3OTG_PORTLI_UNION */
#define SOC_USB3OTG_PORTLI_ADDR(base)                 ((base) + (0x0428))

/* 寄存器说明：端口LPM控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_PORTHLPMC_20_UNION */
#define SOC_USB3OTG_PORTHLPMC_20_ADDR(base)           ((base) + (0x042C))

/* 寄存器说明：MicroFrame Index寄存器
   位域定义UNION结构:  SOC_USB3OTG_MFINDEX_UNION */
#define SOC_USB3OTG_MFINDEX_ADDR(base)                ((base) + (0x440))

/* 寄存器说明：Interrupter Management寄存器
   位域定义UNION结构:  SOC_USB3OTG_IMAN_UNION */
#define SOC_USB3OTG_IMAN_ADDR(base)                   ((base) + (0x460))

/* 寄存器说明：Interrupt Moderation寄存器
   位域定义UNION结构:  SOC_USB3OTG_IMOD_UNION */
#define SOC_USB3OTG_IMOD_ADDR(base)                   ((base) + (0x464))

/* 寄存器说明：Event Ring Segment Table Size寄存器
   位域定义UNION结构:  SOC_USB3OTG_ERSTSZ_UNION */
#define SOC_USB3OTG_ERSTSZ_ADDR(base)                 ((base) + (0x468))

/* 寄存器说明：Event Ring Segment Table基地址低位寄存器
   位域定义UNION结构:  SOC_USB3OTG_ERSTBA_L_UNION */
#define SOC_USB3OTG_ERSTBA_L_ADDR(base)               ((base) + (0x470))

/* 寄存器说明：Event Ring Segment Table基地址高位寄存器
   位域定义UNION结构:  SOC_USB3OTG_ERSTBA_H_UNION */
#define SOC_USB3OTG_ERSTBA_H_ADDR(base)               ((base) + (0x474))

/* 寄存器说明：Event Ring Dequeue Pointer低位寄存器
   位域定义UNION结构:  SOC_USB3OTG_ERDP_L_UNION */
#define SOC_USB3OTG_ERDP_L_ADDR(base)                 ((base) + (0x478))

/* 寄存器说明：Event Ring Dequeue Pointer高位寄存器
   位域定义UNION结构:  SOC_USB3OTG_ERDP_H_UNION */
#define SOC_USB3OTG_ERDP_H_ADDR(base)                 ((base) + (0x47C))

/* 寄存器说明：Doorbell寄存器
   位域定义UNION结构:  SOC_USB3OTG_DB_UNION */
#define SOC_USB3OTG_DB_ADDR(base)                     ((base) + (0x480))

/* 寄存器说明：USB Legacy Support Capability寄存器
   位域定义UNION结构:  SOC_USB3OTG_USBLEGSUP_UNION */
#define SOC_USB3OTG_USBLEGSUP_ADDR(base)              ((base) + (0x8A0))

/* 寄存器说明：USB legavy support control/status寄存器
   位域定义UNION结构:  SOC_USB3OTG_USBLEGCTLSTS_UNION */
#define SOC_USB3OTG_USBLEGCTLSTS_ADDR(base)           ((base) + (0x8A4))

/* 寄存器说明：SOC总线配置寄存器0
   位域定义UNION结构:  SOC_USB3OTG_GSBUSCFG0_UNION */
#define SOC_USB3OTG_GSBUSCFG0_ADDR(base)              ((base) + (0xC100))

/* 寄存器说明：SOC总线配置寄存器1
   位域定义UNION结构:  SOC_USB3OTG_GSBUSCFG1_UNION */
#define SOC_USB3OTG_GSBUSCFG1_ADDR(base)              ((base) + (0xC104))

/* 寄存器说明：发送水线控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_GTXTHRCFG_UNION */
#define SOC_USB3OTG_GTXTHRCFG_ADDR(base)              ((base) + (0xC108))

/* 寄存器说明：接收水线控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_GRXTHRCFG_UNION */
#define SOC_USB3OTG_GRXTHRCFG_ADDR(base)              ((base) + (0xC10C))

/* 寄存器说明：全局控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_GCTL_UNION */
#define SOC_USB3OTG_GCTL_ADDR(base)                   ((base) + (0xC110))

/* 寄存器说明：全局电源管理状态寄存器
   位域定义UNION结构:  SOC_USB3OTG_GPMSTS_UNION */
#define SOC_USB3OTG_GPMSTS_ADDR(base)                 ((base) + (0xC114))

/* 寄存器说明：全局状态寄存器
   位域定义UNION结构:  SOC_USB3OTG_GSTS_UNION */
#define SOC_USB3OTG_GSTS_ADDR(base)                   ((base) + (0xC118))

/* 寄存器说明：用户控制寄存器1
   位域定义UNION结构:  SOC_USB3OTG_GUCTL1_UNION */
#define SOC_USB3OTG_GUCTL1_ADDR(base)                 ((base) + (0xC11C))

/* 寄存器说明：控制器版本寄存器
   位域定义UNION结构:  SOC_USB3OTG_GSNPSID_UNION */
#define SOC_USB3OTG_GSNPSID_ADDR(base)                ((base) + (0xC120))

/* 寄存器说明：用户控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_GUCTL_UNION */
#define SOC_USB3OTG_GUCTL_ADDR(base)                  ((base) + (0xC12C))

/* 寄存器说明：总线错误地址寄存器L
   位域定义UNION结构:  SOC_USB3OTG_GBUSERRADDRL_UNION */
#define SOC_USB3OTG_GBUSERRADDRL_ADDR(base)           ((base) + (0xC130))

/* 寄存器说明：总线错误地址寄存器H
   位域定义UNION结构:  SOC_USB3OTG_GBUSERRADDRH_UNION */
#define SOC_USB3OTG_GBUSERRADDRH_ADDR(base)           ((base) + (0xC134))

/* 寄存器说明：硬件参数寄存器0
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS0_UNION */
#define SOC_USB3OTG_GHWPARAMS0_ADDR(base)             ((base) + (0xC140))

/* 寄存器说明：硬件参数寄存器1
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS1_UNION */
#define SOC_USB3OTG_GHWPARAMS1_ADDR(base)             ((base) + (0xC144))

/* 寄存器说明：硬件参数寄存器2
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS2_UNION */
#define SOC_USB3OTG_GHWPARAMS2_ADDR(base)             ((base) + (0xC148))

/* 寄存器说明：硬件参数寄存器3
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS3_UNION */
#define SOC_USB3OTG_GHWPARAMS3_ADDR(base)             ((base) + (0xC14C))

/* 寄存器说明：硬件参数寄存器4
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS4_UNION */
#define SOC_USB3OTG_GHWPARAMS4_ADDR(base)             ((base) + (0xC150))

/* 寄存器说明：硬件参数寄存器5
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS5_UNION */
#define SOC_USB3OTG_GHWPARAMS5_ADDR(base)             ((base) + (0xC154))

/* 寄存器说明：硬件参数寄存器6
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS6_UNION */
#define SOC_USB3OTG_GHWPARAMS6_ADDR(base)             ((base) + (0xC158))

/* 寄存器说明：硬件参数寄存器7
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS7_UNION */
#define SOC_USB3OTG_GHWPARAMS7_ADDR(base)             ((base) + (0xC15C))

/* 寄存器说明：硬件参数寄存器8
   位域定义UNION结构:  SOC_USB3OTG_GHWPARAMS8_UNION */
#define SOC_USB3OTG_GHWPARAMS8_ADDR(base)             ((base) + (0xC600))

/* 寄存器说明：Queue/FIFO剩余空间debug寄存器
   位域定义UNION结构:  SOC_USB3OTG_GDBGFIFOSPACE_UNION */
#define SOC_USB3OTG_GDBGFIFOSPACE_ADDR(base)          ((base) + (0xC160))

/* 寄存器说明：LTSSM debug寄存器
   位域定义UNION结构:  SOC_USB3OTG_GDBGLTSSM_UNION */
#define SOC_USB3OTG_GDBGLTSSM_ADDR(base)              ((base) + (0xC164))

/* 寄存器说明：LNMCC debug寄存器
   位域定义UNION结构:  SOC_USB3OTG_GDBGLNMCC_UNION */
#define SOC_USB3OTG_GDBGLNMCC_ADDR(base)              ((base) + (0xC168))

/* 寄存器说明：BMU debug寄存器
   位域定义UNION结构:  SOC_USB3OTG_GCBGBMU_UNION */
#define SOC_USB3OTG_GCBGBMU_ADDR(base)                ((base) + (0xC16C))

/* 寄存器说明：LSPMUX debug寄存器
   位域定义UNION结构:  SOC_USB3OTG_GDBGLSPMUX_UNION */
#define SOC_USB3OTG_GDBGLSPMUX_ADDR(base)             ((base) + (0xC170))

/* 寄存器说明：LSP debug寄存器
   位域定义UNION结构:  SOC_USB3OTG_GDBGLSP_UNION */
#define SOC_USB3OTG_GDBGLSP_ADDR(base)                ((base) + (0xC174))

/* 寄存器说明：endpoint debug寄存器0
   位域定义UNION结构:  SOC_USB3OTG_GDBGEPINFO0_UNION */
#define SOC_USB3OTG_GDBGEPINFO0_ADDR(base)            ((base) + (0xC178))

/* 寄存器说明：endpoint debug寄存器1
   位域定义UNION结构:  SOC_USB3OTG_GDBGEPINFO1_UNION */
#define SOC_USB3OTG_GDBGEPINFO1_ADDR(base)            ((base) + (0xC17C))

/* 寄存器说明：USB2 PHY配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_GUSB2PHYCFG_UNION */
#define SOC_USB3OTG_GUSB2PHYCFG_ADDR(base)            ((base) + (0xC200))

/* 寄存器说明：USB3 PIPE控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_GUSB3PIPECTL_UNION */
#define SOC_USB3OTG_GUSB3PIPECTL_ADDR(base)           ((base) + (0xC2C0))

/* 寄存器说明：发送FIFOm大小配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_GTXFIFOSIZm_UNION */
#define SOC_USB3OTG_GTXFIFOSIZm_ADDR(base)            ((base) + (0xC300+m*0x4))

/* 寄存器说明：接收FIFOn大小配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_GRXFIFOSIZn_UNION */
#define SOC_USB3OTG_GRXFIFOSIZn_ADDR(base, n)         ((base) + (0xC380+(n)*0x4))

/* 寄存器说明：事件buffer地址低32位
   位域定义UNION结构:  SOC_USB3OTG_GEVNTADRLo_UNION */
#define SOC_USB3OTG_GEVNTADRLo_ADDR(base)             ((base) + (0xC400))

/* 寄存器说明：事件buffer地址高32位
   位域定义UNION结构:  SOC_USB3OTG_GEVNTADRHi_UNION */
#define SOC_USB3OTG_GEVNTADRHi_ADDR(base)             ((base) + (0xC404))

/* 寄存器说明：事件buffer大小寄存器
   位域定义UNION结构:  SOC_USB3OTG_GEVNTSIZ_UNION */
#define SOC_USB3OTG_GEVNTSIZ_ADDR(base)               ((base) + (0xC408))

/* 寄存器说明：事件数目寄存器
   位域定义UNION结构:  SOC_USB3OTG_GEVNTCOUNT_UNION */
#define SOC_USB3OTG_GEVNTCOUNT_ADDR(base)             ((base) + (0xC40C))

/* 寄存器说明：Device发送FIFO优先级
   位域定义UNION结构:  SOC_USB3OTG_GTXFIFOPRIDEV_UNION */
#define SOC_USB3OTG_GTXFIFOPRIDEV_ADDR(base)          ((base) + (0xC610))

/* 寄存器说明：Host发送FIFO优先级
   位域定义UNION结构:  SOC_USB3OTG_GTXFIFOPRIHST_UNION */
#define SOC_USB3OTG_GTXFIFOPRIHST_ADDR(base)          ((base) + (0xC618))

/* 寄存器说明：Host接收FIFO优先级
   位域定义UNION结构:  SOC_USB3OTG_GRXFIFOPRIHST_UNION */
#define SOC_USB3OTG_GRXFIFOPRIHST_ADDR(base)          ((base) + (0xC61C))

/* 寄存器说明：Host高低优先级权重配置
   位域定义UNION结构:  SOC_USB3OTG_GDMAHLRATIO_UNION */
#define SOC_USB3OTG_GDMAHLRATIO_ADDR(base)            ((base) + (0xC624))

/* 寄存器说明：帧长度调整寄存器
   位域定义UNION结构:  SOC_USB3OTG_GFLADJ_UNION */
#define SOC_USB3OTG_GFLADJ_ADDR(base)                 ((base) + (0xC630))

/* 寄存器说明：device配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_DCFG_UNION */
#define SOC_USB3OTG_DCFG_ADDR(base)                   ((base) + (0xC700))

/* 寄存器说明：device控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_DCTL_UNION */
#define SOC_USB3OTG_DCTL_ADDR(base)                   ((base) + (0xC704))

/* 寄存器说明：device事件使能寄存器
   位域定义UNION结构:  SOC_USB3OTG_DEVNTEN_UNION */
#define SOC_USB3OTG_DEVNTEN_ADDR(base)                ((base) + (0xC708))

/* 寄存器说明：Device状态寄存器
   位域定义UNION结构:  SOC_USB3OTG_DSTS_UNION */
#define SOC_USB3OTG_DSTS_ADDR(base)                   ((base) + (0xC70C))

/* 寄存器说明：一般命令参数寄存器
   位域定义UNION结构:  SOC_USB3OTG_DGCMDPAR_UNION */
#define SOC_USB3OTG_DGCMDPAR_ADDR(base)               ((base) + (0xC710))

/* 寄存器说明：一般命令控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_DGCMD_UNION */
#define SOC_USB3OTG_DGCMD_ADDR(base)                  ((base) + (0xC714))

/* 寄存器说明：端点激活寄存器
   位域定义UNION结构:  SOC_USB3OTG_DALEPENA_UNION */
#define SOC_USB3OTG_DALEPENA_ADDR(base)               ((base) + (0xC720))

/* 寄存器说明：端点m命令参数寄存器2
   位域定义UNION结构:  SOC_USB3OTG_DEPCMDPAR2m_UNION */
#define SOC_USB3OTG_DEPCMDPAR2m_ADDR(base)            ((base) + (0xC800+m*0x10))

/* 寄存器说明：端点m命令参数寄存器1
   位域定义UNION结构:  SOC_USB3OTG_DEPCMDPAR1m_UNION */
#define SOC_USB3OTG_DEPCMDPAR1m_ADDR(base)            ((base) + (0xC804+m*0x10))

/* 寄存器说明：端点m命令参数寄存器0
   位域定义UNION结构:  SOC_USB3OTG_DEPCMDPAR0m_UNION */
#define SOC_USB3OTG_DEPCMDPAR0m_ADDR(base)            ((base) + (0xC808+m*0x10))

/* 寄存器说明：端点m命令寄存器
   位域定义UNION结构:  SOC_USB3OTG_DEPCMDm_UNION */
#define SOC_USB3OTG_DEPCMDm_ADDR(base)                ((base) + (0xC80C+m*0x10))

/* 寄存器说明：OTG配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_OCFG_UNION */
#define SOC_USB3OTG_OCFG_ADDR(base)                   ((base) + (0xCC00))

/* 寄存器说明：OTG控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_OCTL_UNION */
#define SOC_USB3OTG_OCTL_ADDR(base)                   ((base) + (0xCC04))

/* 寄存器说明：OTG事件寄存器
   位域定义UNION结构:  SOC_USB3OTG_OEVNT_UNION */
#define SOC_USB3OTG_OEVNT_ADDR(base)                  ((base) + (0xCC08))

/* 寄存器说明：OTG事件使能寄存器
   位域定义UNION结构:  SOC_USB3OTG_OEVNTEN_UNION */
#define SOC_USB3OTG_OEVNTEN_ADDR(base)                ((base) + (0xCC0C))

/* 寄存器说明：OTG状态寄存器
   位域定义UNION结构:  SOC_USB3OTG_OSTS_UNION */
#define SOC_USB3OTG_OSTS_ADDR(base)                   ((base) + (0xCC10))

/* 寄存器说明：ADP配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_ADPCFG_UNION */
#define SOC_USB3OTG_ADPCFG_ADDR(base)                 ((base) + (0xCC20))

/* 寄存器说明：ADP控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_ADPCTL_UNION */
#define SOC_USB3OTG_ADPCTL_ADDR(base)                 ((base) + (0xCC24))

/* 寄存器说明：ADP事件寄存器
   位域定义UNION结构:  SOC_USB3OTG_ADPEVNT_UNION */
#define SOC_USB3OTG_ADPEVNT_ADDR(base)                ((base) + (0xCC28))

/* 寄存器说明：ADP事件寄存器
   位域定义UNION结构:  SOC_USB3OTG_ADPEVNTEN_UNION */
#define SOC_USB3OTG_ADPEVNTEN_ADDR(base)              ((base) + (0xCC28))

/* 寄存器说明：BC配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_BCFG_UNION */
#define SOC_USB3OTG_BCFG_ADDR(base)                   ((base) + (0xCC30))

/* 寄存器说明：BC事件寄存器
   位域定义UNION结构:  SOC_USB3OTG_BCEVT_UNION */
#define SOC_USB3OTG_BCEVT_ADDR(base)                  ((base) + (0xCC38))

/* 寄存器说明：BC事件使能寄存器
   位域定义UNION结构:  SOC_USB3OTG_BCEVTEN_UNION */
#define SOC_USB3OTG_BCEVTEN_ADDR(base)                ((base) + (0xCC3C))





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

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_USB3OTG_CAPLENGTH_UNION
 结构说明  : CAPLENGTH 寄存器结构定义。地址偏移量:0x0000，初值:0x01000020，宽度:32
 寄存器说明: 功能寄存器长度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CAPLENGTH  : 8;  /* bit[0-7]  : 指示操作寄存器地址偏移量 */
        unsigned int  reserved   : 8;  /* bit[8-15] : 保留。 */
        unsigned int  HCIVERSION : 16; /* bit[16-31]: 指示xHCI协议版本号 */
    } reg;
} SOC_USB3OTG_CAPLENGTH_UNION;
#endif
#define SOC_USB3OTG_CAPLENGTH_CAPLENGTH_START   (0)
#define SOC_USB3OTG_CAPLENGTH_CAPLENGTH_END     (7)
#define SOC_USB3OTG_CAPLENGTH_HCIVERSION_START  (16)
#define SOC_USB3OTG_CAPLENGTH_HCIVERSION_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_HCSPARAMS1_UNION
 结构说明  : HCSPARAMS1 寄存器结构定义。地址偏移量:0x0004，初值:0x0200017F，宽度:32
 寄存器说明: 结构参数1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MaxSlots : 8;  /* bit[0-7]  : 指示Host控制器所支持的最大Device Context数据结构数量和Doorbell Array entry数量。有效数据1~255。数据0被保留。 */
        unsigned int  MaxIntrs : 11; /* bit[8-18] : 指示HOST控制器可以提供多少个中断给SOC。
                                                    该数值同时决定在Runtime寄存器空间会有多少个中断寄存器。有效数值范围：0x1~0x400.数值0无意义。 */
        unsigned int  reserved : 5;  /* bit[19-23]: 保留。 */
        unsigned int  MaxPorts : 8;  /* bit[24-31]: 指示HOST控制器所支持的最大port数量。同时该数值决定在Operational寄存器空间内，Port配置寄存器个数。数值的有效范围0x1~0xFF。 */
    } reg;
} SOC_USB3OTG_HCSPARAMS1_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS1_MaxSlots_START  (0)
#define SOC_USB3OTG_HCSPARAMS1_MaxSlots_END    (7)
#define SOC_USB3OTG_HCSPARAMS1_MaxIntrs_START  (8)
#define SOC_USB3OTG_HCSPARAMS1_MaxIntrs_END    (18)
#define SOC_USB3OTG_HCSPARAMS1_MaxPorts_START  (24)
#define SOC_USB3OTG_HCSPARAMS1_MaxPorts_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_HCSPARAMS2_UNION
 结构说明  : HCSPARAMS2 寄存器结构定义。地址偏移量:0x0008，初值:0x040000F1，宽度:32
 寄存器说明: 结构参数2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IST                   : 4;  /* bit[0-3]  : 待确认 */
        unsigned int  ERST_Max              : 4;  /* bit[4-7]  : 指示Event Ring Segment Table entry数量:2ERST_Max个。ERST_Max的有效数值为0~15。 */
        unsigned int  reserved              : 13; /* bit[8-20] : 保留。 */
        unsigned int  Max_Scratchpad_Bufs_H : 5;  /* bit[21-25]: 指示software需要保留多少Scratchpad Buffer给xHC。有效数值0~31. */
        unsigned int  SPR                   : 1;  /* bit[26]   :  */
        unsigned int  Max_Scratchpad_Bufs_L : 5;  /* bit[27-31]: 指示software需要保留多少Scratchpad Buffer给xHC。有效数值0~31. */
    } reg;
} SOC_USB3OTG_HCSPARAMS2_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS2_IST_START                    (0)
#define SOC_USB3OTG_HCSPARAMS2_IST_END                      (3)
#define SOC_USB3OTG_HCSPARAMS2_ERST_Max_START               (4)
#define SOC_USB3OTG_HCSPARAMS2_ERST_Max_END                 (7)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_H_START  (21)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_H_END    (25)
#define SOC_USB3OTG_HCSPARAMS2_SPR_START                    (26)
#define SOC_USB3OTG_HCSPARAMS2_SPR_END                      (26)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_L_START  (27)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_L_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_HCSPARAMS3_UNION
 结构说明  : HCSPARAMS3 寄存器结构定义。地址偏移量:0x000C，初值:0x07FF0000，宽度:32
 寄存器说明: 结构参数3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  U1_Exit_Latency : 8;  /* bit[0-7]  : root hub Port Link State从U1到U0的最大延时时间。允许的有效数值8'h0~8'h0A，其它数值为保留。 */
        unsigned int  reserved        : 8;  /* bit[8-15] : 保留。 */
        unsigned int  U2_Exit_Latency : 16; /* bit[16-31]: root hub Port Link State从U2到U0的最大延时时间。允许的有效数值16'h0~16'h07FF，其它数值为保留。 */
    } reg;
} SOC_USB3OTG_HCSPARAMS3_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS3_U1_Exit_Latency_START  (0)
#define SOC_USB3OTG_HCSPARAMS3_U1_Exit_Latency_END    (7)
#define SOC_USB3OTG_HCSPARAMS3_U2_Exit_Latency_START  (16)
#define SOC_USB3OTG_HCSPARAMS3_U2_Exit_Latency_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_HCCPARAMS_UNION
 结构说明  : HCCPARAMS 寄存器结构定义。地址偏移量:0x0010，初值:0x0220F06C，宽度:32
 寄存器说明: 功能特性参数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  AC64       : 1;  /* bit[0]    : 指示访问系统内存的能力。
                                                      0:32bit系统内存地址范围；
                                                      1:64bit系统内存地址范围。 */
        unsigned int  BNC        : 1;  /* bit[1]    : HOST控制器是否执行Bandwidth Negotiation。
                                                      0：不执行；
                                                      1：执行。 */
        unsigned int  CSZ        : 1;  /* bit[2]    : HOST控制器使用的Context数据结构大小。
                                                      0：使用32 Byte大小的Context数据结构；
                                                      1：使用64 Byte大小的Context数据结构。 */
        unsigned int  PPC        : 1;  /* bit[3]    : 指示HOST控制器是否包含Port Power Switches。
                                                      0：不包含；
                                                      1：包含。 */
        unsigned int  PIND       : 1;  /* bit[4]    : 指示HOST控制器的root hub ports是否支持port indicator control。当为1时，在HOST的状态与控制寄存器中存在一个RW的bit，用于控制port indicator的状态。
                                                      0：不支持；
                                                      1：支持。 */
        unsigned int  LHRC       : 1;  /* bit[5]    : 指示HOST控制器是否支持Light Host Controller Reset。该位影响USBCMD的LHCRST位的功能。
                                                      0：不支持；
                                                      1：支持。 */
        unsigned int  LTC        : 1;  /* bit[6]    : 指示是否支持Latency Tolerance Messaging特性。
                                                      0：不支持；
                                                      1：支持。 */
        unsigned int  NSS        : 1;  /* bit[7]    : 指示是否支持Secondary Stream IDs。
                                                      0：支持；
                                                      1：不支持。 */
        unsigned int  PAE        : 1;  /* bit[8]    : 待定 */
        unsigned int  reserved   : 3;  /* bit[9-11] : 保留 */
        unsigned int  MaxPSASize : 4;  /* bit[12-15]: 指示所支持的最大Primary Stream Array大小。计算方法：2MaxPSASize+1。数值有效范围1~15。 */
        unsigned int  xECP       : 16; /* bit[16-31]: 指示extended capability的存在地址。该数值用于计算第1个extended capabitity的起始地址，方法如下：
                                                      BASE+(xECP<<2)，BASE代表控制器寄存器的基地址。 */
    } reg;
} SOC_USB3OTG_HCCPARAMS_UNION;
#endif
#define SOC_USB3OTG_HCCPARAMS_AC64_START        (0)
#define SOC_USB3OTG_HCCPARAMS_AC64_END          (0)
#define SOC_USB3OTG_HCCPARAMS_BNC_START         (1)
#define SOC_USB3OTG_HCCPARAMS_BNC_END           (1)
#define SOC_USB3OTG_HCCPARAMS_CSZ_START         (2)
#define SOC_USB3OTG_HCCPARAMS_CSZ_END           (2)
#define SOC_USB3OTG_HCCPARAMS_PPC_START         (3)
#define SOC_USB3OTG_HCCPARAMS_PPC_END           (3)
#define SOC_USB3OTG_HCCPARAMS_PIND_START        (4)
#define SOC_USB3OTG_HCCPARAMS_PIND_END          (4)
#define SOC_USB3OTG_HCCPARAMS_LHRC_START        (5)
#define SOC_USB3OTG_HCCPARAMS_LHRC_END          (5)
#define SOC_USB3OTG_HCCPARAMS_LTC_START         (6)
#define SOC_USB3OTG_HCCPARAMS_LTC_END           (6)
#define SOC_USB3OTG_HCCPARAMS_NSS_START         (7)
#define SOC_USB3OTG_HCCPARAMS_NSS_END           (7)
#define SOC_USB3OTG_HCCPARAMS_PAE_START         (8)
#define SOC_USB3OTG_HCCPARAMS_PAE_END           (8)
#define SOC_USB3OTG_HCCPARAMS_MaxPSASize_START  (12)
#define SOC_USB3OTG_HCCPARAMS_MaxPSASize_END    (15)
#define SOC_USB3OTG_HCCPARAMS_xECP_START        (16)
#define SOC_USB3OTG_HCCPARAMS_xECP_END          (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DBOFF_UNION
 结构说明  : DBOFF 寄存器结构定义。地址偏移量:0x0014，初值:0x00001280，宽度:32
 寄存器说明: Doorbell Array偏移地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved              : 2;  /* bit[0-1] : 保留 */
        unsigned int  Doorbell_Array_Offset : 30; /* bit[2-31]: 定义了Doorbell Array的偏移地址。该数值通常是32bit对齐的，如果控制器支持virtualization，那么就是以PAGESIZE对齐。 */
    } reg;
} SOC_USB3OTG_DBOFF_UNION;
#endif
#define SOC_USB3OTG_DBOFF_Doorbell_Array_Offset_START  (2)
#define SOC_USB3OTG_DBOFF_Doorbell_Array_Offset_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_RTSOFF_UNION
 结构说明  : RTSOFF 寄存器结构定义。地址偏移量:0x0018，初值:0x00008800，宽度:32
 寄存器说明: RunTimer空间偏移地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                      : 5;  /* bit[0-4] : 保留 */
        unsigned int  Runtime_Register_Space_Offset : 27; /* bit[5-31]: Runtime寄存器空间的偏移地址。 */
    } reg;
} SOC_USB3OTG_RTSOFF_UNION;
#endif
#define SOC_USB3OTG_RTSOFF_Runtime_Register_Space_Offset_START  (5)
#define SOC_USB3OTG_RTSOFF_Runtime_Register_Space_Offset_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_USBCMD_UNION
 结构说明  : USBCMD 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 命令寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Run_Stop : 1;  /* bit[0]    : 当配置为1，xHC继续执行操作，当清除为0，xHC停止任何的操作，进去halts。
                                                    0：STOP；
                                                    1：RUN。 */
        unsigned int  HCRST    : 1;  /* bit[1]    : 软件用于对xHC进行复位操作。当软件配置为1时，USB2下行端口不会发起USB reset操作，但会在USB3 Root Hub下行端口发起Hot或Warm Reset操作。并且当reset process完成后，控制器会自动将其清0。
                                                    0：复位操作结束；
                                                    1：执行复位操作。 */
        unsigned int  INTE     : 1;  /* bit[2]    : HOST系统的中断使能位。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  HSEE     : 1;  /* bit[3]    : host系统错误使能。当该bit为1，并且USBSTS寄存器的HSE位也为1时，那么xHC就会发起一个out-of-band的错误信号给host。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  reserved_0: 3;  /* bit[4-6]  : 保留。 */
        unsigned int  LHCRST   : 1;  /* bit[7]    : 当HCCPARAMS的LHRC位为1是，那么允许驱动对xHC进行复位操作，但是不会影响ports的状态，并且所有Auxiliary内的寄存器保持数值不变。
                                                    0：复位操作已经完成；
                                                    1：复位操作还在进行。 */
        unsigned int  CSS      : 1;  /* bit[8]    : 控制器Save状态。当HCH位为1，软件配置该位为1时，那么xHC就会内部的任何状态，而这些状态是用于xHC用于Restore操作使用。但是软件配置该bit为0，或者当HCH为0时配置该bit为1，那么不会发起Save的操作。
                                                    0：不执行Save操作；
                                                    1：配合HCH状态发起Save操作。 */
        unsigned int  CRS      : 1;  /* bit[9]    : 控制器的Restore状态。当该bit配置为1，且HCH为1时，发起Restore操作。但是当该bit为1且Run/Stop位也为1，或者HCH为0，或者该位为0时，都不会发起Restore操作。
                                                    0：不发起Restore操作；
                                                    1：配合Run/Stop和HCH，发起Restore操作。 */
        unsigned int  EWE      : 1;  /* bit[10]   : 当为1，且MFINDEX寄存器从0x03FFF到0x0时，就会发起一个MFINDEX Wrap Event。为0时不发起。 */
        unsigned int  EU3S     : 1;  /* bit[11]   : 当为1，且处于U3，disconnect，disabled或者powered-off状态时，停止MFINDEX寄存器记数。当为0，且处于disconnect，disabled或者powered-off状态时，停止MFINDEX寄存器记数。 */
        unsigned int  reserved_1: 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_USB3OTG_USBCMD_UNION;
#endif
#define SOC_USB3OTG_USBCMD_Run_Stop_START  (0)
#define SOC_USB3OTG_USBCMD_Run_Stop_END    (0)
#define SOC_USB3OTG_USBCMD_HCRST_START     (1)
#define SOC_USB3OTG_USBCMD_HCRST_END       (1)
#define SOC_USB3OTG_USBCMD_INTE_START      (2)
#define SOC_USB3OTG_USBCMD_INTE_END        (2)
#define SOC_USB3OTG_USBCMD_HSEE_START      (3)
#define SOC_USB3OTG_USBCMD_HSEE_END        (3)
#define SOC_USB3OTG_USBCMD_LHCRST_START    (7)
#define SOC_USB3OTG_USBCMD_LHCRST_END      (7)
#define SOC_USB3OTG_USBCMD_CSS_START       (8)
#define SOC_USB3OTG_USBCMD_CSS_END         (8)
#define SOC_USB3OTG_USBCMD_CRS_START       (9)
#define SOC_USB3OTG_USBCMD_CRS_END         (9)
#define SOC_USB3OTG_USBCMD_EWE_START       (10)
#define SOC_USB3OTG_USBCMD_EWE_END         (10)
#define SOC_USB3OTG_USBCMD_EU3S_START      (11)
#define SOC_USB3OTG_USBCMD_EU3S_END        (11)


/*****************************************************************************
 结构名    : SOC_USB3OTG_USBSTS_UNION
 结构说明  : USBSTS 寄存器结构定义。地址偏移量:0x0024，初值:0x00000801，宽度:32
 寄存器说明: 状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HCH      : 1;  /* bit[0]    : 指示是否进入Halted状态。
                                                    0：没有进入Halted状态；
                                                    1：进入Halted状态。 */
        unsigned int  reserved_0: 1;  /* bit[1]    : 保留 */
        unsigned int  HSE      : 1;  /* bit[2]    : HOST系统错误指示。
                                                    0：正常；
                                                    1：有错误。 */
        unsigned int  EINT     : 1;  /* bit[3]    : Event中断指示。
                                                    0：没有Interrupt Pending中断从0到1的过程；
                                                    1：有Interrupt Pending中断从0到1的过程。 */
        unsigned int  PCD      : 1;  /* bit[4]    : 端口变化检测。
                                                    0：port没有变化；
                                                    1：port有变化。 */
        unsigned int  reserved_1: 3;  /* bit[5-7]  : 保留 */
        unsigned int  SSS      : 1;  /* bit[8]    : Save State Status指示位。
                                                    0：Save操作完成；
                                                    1：USBCMD的CSS为1，且发起了Save操作。 */
        unsigned int  RSS      : 1;  /* bit[9]    : Restore State Status指示位。
                                                    0：Restore操作完成；
                                                    1：USBCMD的CRS为1，且发起了Restore操作。 */
        unsigned int  SRE      : 1;  /* bit[10]   : 指示Save或Restore操作是否发生了错误。
                                                    0：没有；
                                                    1：有。 */
        unsigned int  CNR      : 1;  /* bit[11]   : 指示控制器是否已经准备好。当没有准备好，软件不能进行Doorbell和Operation寄存器的操作。当发起了Hardware复位，该值为1，指导可以接受寄存器操作后控制器将其清0。
                                                    0：ready；
                                                    1：not ready。 */
        unsigned int  HCE      : 1;  /* bit[12]   : xHC内部有错误指示。当有错误时，软件需要重新复位和配置xHC。
                                                    0：没有错误；
                                                    1：产生了错误。 */
        unsigned int  reserved_2: 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_USB3OTG_USBSTS_UNION;
#endif
#define SOC_USB3OTG_USBSTS_HCH_START       (0)
#define SOC_USB3OTG_USBSTS_HCH_END         (0)
#define SOC_USB3OTG_USBSTS_HSE_START       (2)
#define SOC_USB3OTG_USBSTS_HSE_END         (2)
#define SOC_USB3OTG_USBSTS_EINT_START      (3)
#define SOC_USB3OTG_USBSTS_EINT_END        (3)
#define SOC_USB3OTG_USBSTS_PCD_START       (4)
#define SOC_USB3OTG_USBSTS_PCD_END         (4)
#define SOC_USB3OTG_USBSTS_SSS_START       (8)
#define SOC_USB3OTG_USBSTS_SSS_END         (8)
#define SOC_USB3OTG_USBSTS_RSS_START       (9)
#define SOC_USB3OTG_USBSTS_RSS_END         (9)
#define SOC_USB3OTG_USBSTS_SRE_START       (10)
#define SOC_USB3OTG_USBSTS_SRE_END         (10)
#define SOC_USB3OTG_USBSTS_CNR_START       (11)
#define SOC_USB3OTG_USBSTS_CNR_END         (11)
#define SOC_USB3OTG_USBSTS_HCE_START       (12)
#define SOC_USB3OTG_USBSTS_HCE_END         (12)


/*****************************************************************************
 结构名    : SOC_USB3OTG_PAGESIZE_UNION
 结构说明  : PAGESIZE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000001，宽度:32
 寄存器说明: 页大小寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_size : 16; /* bit[0-15] : 用于计算xHC支持的page大小。计算方法：2(page_size+12)。 */
        unsigned int  reserved  : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_USB3OTG_PAGESIZE_UNION;
#endif
#define SOC_USB3OTG_PAGESIZE_page_size_START  (0)
#define SOC_USB3OTG_PAGESIZE_page_size_END    (15)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DNCTRL_UNION
 结构说明  : DNCTRL 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  notification_enable : 16; /* bit[0-15] : 待定 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_USB3OTG_DNCTRL_UNION;
#endif
#define SOC_USB3OTG_DNCTRL_notification_enable_START  (0)
#define SOC_USB3OTG_DNCTRL_notification_enable_END    (15)


/*****************************************************************************
 结构名    : SOC_USB3OTG_CRCR_L_UNION
 结构说明  : CRCR_L 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: Command Ring Control寄存器低32位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RCS                  : 1;  /* bit[0]   : Ring Cycle State。该位等同于xHC的Consumer Cycle State(CCS)状态。当Command Ring Running(CRR)为1时，写该bit无效。 */
        unsigned int  CS                   : 1;  /* bit[1]   : Command Stop。当配置为1时，在完成当前正在执行的command后停止Command Ring的操作，并设置Command Ring Stopped产生Command Completion Event，Command TRB指针配置为Command Ring Dequeue Pointer的数值。
                                                               当下次填写DB Reasion时，填写restart the command Ring operation。
                                                               当CRR为0时，该bit写无效。 */
        unsigned int  CA                   : 1;  /* bit[2]   : Command Abort。当配置为1时，立即终止当前的正在执行的command，停止Command Ring，设置Command Ring Stopped产生Command Completion Event。
                                                               当下次填写DB Reasion时，填写restart the command Ring operation。
                                                               当CRR为0时，该bit写无效。 */
        unsigned int  CRR                  : 1;  /* bit[3]   : Command Ring Running。当R/S位为1，且Doorbell寄存器的DB Reasion域为Controller Command时，该bit置1。当CS或CA为1，或者R/S为0时，该bit清0. */
        unsigned int  reserved             : 2;  /* bit[4-5] : 保留 */
        unsigned int  command_ring_pointor : 26; /* bit[6-31]: 与CRCR_H一起指定Command Ring数据结构的基地址（64 Byte对齐）。当CRR=1时，该bit写无效，读永远返回0. */
    } reg;
} SOC_USB3OTG_CRCR_L_UNION;
#endif
#define SOC_USB3OTG_CRCR_L_RCS_START                   (0)
#define SOC_USB3OTG_CRCR_L_RCS_END                     (0)
#define SOC_USB3OTG_CRCR_L_CS_START                    (1)
#define SOC_USB3OTG_CRCR_L_CS_END                      (1)
#define SOC_USB3OTG_CRCR_L_CA_START                    (2)
#define SOC_USB3OTG_CRCR_L_CA_END                      (2)
#define SOC_USB3OTG_CRCR_L_CRR_START                   (3)
#define SOC_USB3OTG_CRCR_L_CRR_END                     (3)
#define SOC_USB3OTG_CRCR_L_command_ring_pointor_START  (6)
#define SOC_USB3OTG_CRCR_L_command_ring_pointor_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_CRCR_H_UNION
 结构说明  : CRCR_H 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: Command Ring Control寄存器高32位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  command_ring_pointor : 32; /* bit[0-31]: 与CRCR_L[31：6]一起定义了Command Ring数据结构的基地址。当CRR=1时，该bit写无效，读永远返回0. */
    } reg;
} SOC_USB3OTG_CRCR_H_UNION;
#endif
#define SOC_USB3OTG_CRCR_H_command_ring_pointor_START  (0)
#define SOC_USB3OTG_CRCR_H_command_ring_pointor_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DCBAAP_L_UNION
 结构说明  : DCBAAP_L 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: Device Context Basic Address Array Pointer低32位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 6;  /* bit[0-5] : 保留 */
        unsigned int  DCBAAR_point : 26; /* bit[6-31]: 和DCBAAP_H一起定义Device Context Basic Address Array数据机构的基地址。 */
    } reg;
} SOC_USB3OTG_DCBAAP_L_UNION;
#endif
#define SOC_USB3OTG_DCBAAP_L_DCBAAR_point_START  (6)
#define SOC_USB3OTG_DCBAAP_L_DCBAAR_point_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DCBAAP_H_UNION
 结构说明  : DCBAAP_H 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: Device Context Basic Address Array Pointer高32位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DCBAAR_point : 32; /* bit[0-31]: 和DCBAAP_L[31：6]一起定义Device Context Basic Address Array数据机构的基地址。 */
    } reg;
} SOC_USB3OTG_DCBAAP_H_UNION;
#endif
#define SOC_USB3OTG_DCBAAP_H_DCBAAR_point_START  (0)
#define SOC_USB3OTG_DCBAAP_H_DCBAAR_point_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_CONFIG_UNION
 结构说明  : CONFIG 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MaxSlotsEn : 8;  /* bit[0-7] : 指定使能的最大的Device Slots。有效数值范围0~MaxSlots.0表示关闭所有的Device Slots。 */
        unsigned int  reserved   : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_USB3OTG_CONFIG_UNION;
#endif
#define SOC_USB3OTG_CONFIG_MaxSlotsEn_START  (0)
#define SOC_USB3OTG_CONFIG_MaxSlotsEn_END    (7)


/*****************************************************************************
 结构名    : SOC_USB3OTG_PORTSC_UNION
 结构说明  : PORTSC 寄存器结构定义。地址偏移量:0x0420，初值:0x000002A0，宽度:32
 寄存器说明: 端口控制和状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CCS       : 1;  /* bit[0]    : 指示当前连接状态。当PP=0时，该bit为0。
                                                     0：有设备连接；
                                                     1：没有设备连接。 */
        unsigned int  PED       : 1;  /* bit[1]    : 端口使能与关闭。该位只能由xHC使能该bit。当关闭端口时，处理reset外，其他任何的数据传输都在该port被阻塞。
                                                     对于USB2协议端口：当端口关闭后，软件需要reset该端口(PR=1)，从而PED=1端口使能。
                                                     对于USB3协议端口：
                                                     当端口处于Polling状态，端口应该自动使能并且在成功完成link training后将PED=1。当端口关闭时，软件需要配置PLS为5，从而端口进入disconnect状态。
                                                     当PR=1时，PED被清除为0，reset完成后，当PR从1变为0，PED置1。
                                                     0：端口关闭；
                                                     1：端口使能。 */
        unsigned int  reserved_0: 1;  /* bit[2]    : 保留 */
        unsigned int  OCA       : 1;  /* bit[3]    : Over-current Active。指示端口是否过电流，并且过电流条件去除后，能够自动清0。
                                                     0：端口没有过电流；
                                                     1：端口产生了过电流。 */
        unsigned int  PR        : 1;  /* bit[4]    : Port Reset。当软件配置该bit为1时，USB总线发起reset队列。PR一直保持为1直到reset过程完成。当PP为0时，该bit为0。
                                                     0：端口没有在复位中；
                                                     1：端口复位。 */
        unsigned int  PLS       : 4;  /* bit[5-8]  : Port Link State指示。
                                                     0：U0状态；
                                                     1：U1状态；
                                                     2：U2状态；
                                                     3：U3状态；
                                                     4：Disable状态；
                                                     5：RxDelect状态；
                                                     6：Inactive状态；
                                                     7：Polling状态；
                                                     8：Recovery状态；
                                                     9：Hot Reset状态；
                                                     10：Compliance Mode状态；
                                                     11：Test Mode状态；
                                                     12~14：保留；
                                                     15：Resume状态。 */
        unsigned int  PP        : 1;  /* bit[9]    : Port Power指示。当PPC=1，xHC含有电源控制开关，并且该bit能够反映该开关的状态(0=off, 1=on)。当PPC=0，xHC不含有电源控制开关，每个端口都硬性连接电源。
                                                     0：端口处于Powered-off状态；
                                                     1：端口不处于Powered-off状态。 */
        unsigned int  PortSpeed : 4;  /* bit[10-13]: 指示attached设备速度。该域只有在CCS=1时才有意义。
                                                     0：没有定义的速度；
                                                     1-15：Protocol Speed ID(PSI)。 */
        unsigned int  PIC       : 2;  /* bit[14-15]: Port Indicator Control。当PIND=0时，配置该域不起作用。
                                                     0：OFF；
                                                     1：Amber；
                                                     2：Green。
                                                     当PP=0，该域为0。 */
        unsigned int  LWS       : 1;  /* bit[16]   : Port Link State Write Strobe。当该bit为1，允许向PLS域写数值，否则向PLS写入的数值无效。 */
        unsigned int  CSC       : 1;  /* bit[17]   : Connect Status Change。指示CCS或Cold Attach Status(CAS)是否有变化。当软件配置PP=0使CCS变换，或者软件配置WPR=1使CAS变化时，该bit不能置1。当CSC已经为1，软件还没有进行清除操作，任何的端口设备连接状态发生变化，xHC都会将该bit置1。 */
        unsigned int  PEC       : 1;  /* bit[18]   : Port Enable/Disable Change指示。但是由于PP=0引起的PED变化不能将该bit置1。对于USB2协议端口，只有在port disable条件下才写1。对于USB3协议端口，该bit不能写1。
                                                     0：PED没有变化；
                                                     1：PED有变化。 */
        unsigned int  WRC       : 1;  /* bit[19]   : Warm Port Reset Change指示。当Warm Reset过程完成后，该bit置1。但是由于PP=0或PED=0而强制发起的Warm Reset不能将该bit置1。该bit只对USB3协议端口有用，USB2协议端口为保留。
                                                     0：no change；
                                                     1：Wram Reset Complete。 */
        unsigned int  OCC       : 1;  /* bit[20]   : Over-current Change指示。当OCA从0到1，或者从1到0，都会引起该bit置1。 */
        unsigned int  PRC       : 1;  /* bit[21]   : Port Reset Change指示。当PR从1到0时，该bit置1.但是由于PP=0或PED=0强制复位停止，不能将该bit置1.
                                                     0：on change;
                                                     1：reset complete。 */
        unsigned int  PLC       : 1;  /* bit[22]   : Port Link State Change指示。当如下的PLS变化时，该bit置1：
                                                     U3 -> Resume;
                                                     Resume -> Recovery -> U0;
                                                     Resume -> U0;
                                                     U3 -> Recovery -> U0;
                                                     U3 -> U0;
                                                     U2 -> U0;
                                                     U1 -> U0;
                                                     Any state -> Inactive.
                                                     0：no change;
                                                     1：Link state change. */
        unsigned int  CEC       : 1;  /* bit[23]   : Port Config Error Change。指示端口在配置link partner时失败。该bit只对USB3协议端口有效，USB2协议端口该bit为保留。
                                                     0：no change；
                                                     1：Port config error detected。 */
        unsigned int  CAS       : 1;  /* bit[24]   : Cold Attach Status. */
        unsigned int  WCE       : 1;  /* bit[25]   : Wake on Connect Enale.将该bit置1，使能端口将设备connect作为一个wake-up event。 */
        unsigned int  WDE       : 1;  /* bit[26]   : Wake on Disconnect Enable。将该bit置1，使能端口将设备disconnect作为一个wake-up event。 */
        unsigned int  WOE       : 1;  /* bit[27]   : Wake on Over-current Enable.将该bit置1，使能端口将over-current作为一个wake-up event。 */
        unsigned int  reserved_1: 2;  /* bit[28-29]: 保留 */
        unsigned int  DR        : 1;  /* bit[30]   : Device Removable.指示对接的设备是否可移除。
                                                     0：对接设备可移除；
                                                     1：对接设备不可移除。 */
        unsigned int  WPR       : 1;  /* bit[31]   : Warm Port Reset指示。当软件配置为1，发起Warm Reset操作。该bit只对USB协议端口有效，USB2端口保留。 */
    } reg;
} SOC_USB3OTG_PORTSC_UNION;
#endif
#define SOC_USB3OTG_PORTSC_CCS_START        (0)
#define SOC_USB3OTG_PORTSC_CCS_END          (0)
#define SOC_USB3OTG_PORTSC_PED_START        (1)
#define SOC_USB3OTG_PORTSC_PED_END          (1)
#define SOC_USB3OTG_PORTSC_OCA_START        (3)
#define SOC_USB3OTG_PORTSC_OCA_END          (3)
#define SOC_USB3OTG_PORTSC_PR_START         (4)
#define SOC_USB3OTG_PORTSC_PR_END           (4)
#define SOC_USB3OTG_PORTSC_PLS_START        (5)
#define SOC_USB3OTG_PORTSC_PLS_END          (8)
#define SOC_USB3OTG_PORTSC_PP_START         (9)
#define SOC_USB3OTG_PORTSC_PP_END           (9)
#define SOC_USB3OTG_PORTSC_PortSpeed_START  (10)
#define SOC_USB3OTG_PORTSC_PortSpeed_END    (13)
#define SOC_USB3OTG_PORTSC_PIC_START        (14)
#define SOC_USB3OTG_PORTSC_PIC_END          (15)
#define SOC_USB3OTG_PORTSC_LWS_START        (16)
#define SOC_USB3OTG_PORTSC_LWS_END          (16)
#define SOC_USB3OTG_PORTSC_CSC_START        (17)
#define SOC_USB3OTG_PORTSC_CSC_END          (17)
#define SOC_USB3OTG_PORTSC_PEC_START        (18)
#define SOC_USB3OTG_PORTSC_PEC_END          (18)
#define SOC_USB3OTG_PORTSC_WRC_START        (19)
#define SOC_USB3OTG_PORTSC_WRC_END          (19)
#define SOC_USB3OTG_PORTSC_OCC_START        (20)
#define SOC_USB3OTG_PORTSC_OCC_END          (20)
#define SOC_USB3OTG_PORTSC_PRC_START        (21)
#define SOC_USB3OTG_PORTSC_PRC_END          (21)
#define SOC_USB3OTG_PORTSC_PLC_START        (22)
#define SOC_USB3OTG_PORTSC_PLC_END          (22)
#define SOC_USB3OTG_PORTSC_CEC_START        (23)
#define SOC_USB3OTG_PORTSC_CEC_END          (23)
#define SOC_USB3OTG_PORTSC_CAS_START        (24)
#define SOC_USB3OTG_PORTSC_CAS_END          (24)
#define SOC_USB3OTG_PORTSC_WCE_START        (25)
#define SOC_USB3OTG_PORTSC_WCE_END          (25)
#define SOC_USB3OTG_PORTSC_WDE_START        (26)
#define SOC_USB3OTG_PORTSC_WDE_END          (26)
#define SOC_USB3OTG_PORTSC_WOE_START        (27)
#define SOC_USB3OTG_PORTSC_WOE_END          (27)
#define SOC_USB3OTG_PORTSC_DR_START         (30)
#define SOC_USB3OTG_PORTSC_DR_END           (30)
#define SOC_USB3OTG_PORTSC_WPR_START        (31)
#define SOC_USB3OTG_PORTSC_WPR_END          (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_PORTPMSC_20_UNION
 结构说明  : PORTPMSC_20 寄存器结构定义。地址偏移量:0x0424，初值:0x00000000，宽度:32
 寄存器说明: 端口功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  L1S               : 3;  /* bit[0-2]  : L1 Status.软件从此得知L1-based suspend请求是否成功：
                                                             0：Invalid；
                                                             1：Success；
                                                             2：Not Yet;
                                                             3：not supported;
                                                             4：timeout/Error;
                                                             5-7：reserved。 */
        unsigned int  RWE               : 1;  /* bit[3]    : Remote Wake Enable.软件使用该bit使能/不使能设备从L1中远程唤醒。 */
        unsigned int  HIRD              : 4;  /* bit[4-7]  : Host Initiated Resume Duration.软件使用该域告知对接的设备HOST多久后发起resume从而退出L1状态。数值0对应50us，后面该数值每加1，时间增加75us。例如：0001对应125us。 */
        unsigned int  L1_Device_Slot    : 8;  /* bit[8-15] : 软件配置该数值指示 */
        unsigned int  HLE               : 1;  /* bit[16]   : Hardware LPM Enable.当该bit为1时，hardware controller LPM在该端口使能。当HLC=0,该域保留。 */
        unsigned int  reserved          : 11; /* bit[17-27]: 保留 */
        unsigned int  Port_Test_Control : 4;  /* bit[28-31]: 非0数值指示PORT进入测试模式：
                                                             0: Test mode not enable;
                                                             1: Test J_STATE;
                                                             2: Test K_STATE;
                                                             3: Test SE0_NAK;
                                                             4: Test Packet;
                                                             5: Test FORCE_ENABLE;
                                                             6-14: reserved;
                                                             15: Port Test control error. */
    } reg;
} SOC_USB3OTG_PORTPMSC_20_UNION;
#endif
#define SOC_USB3OTG_PORTPMSC_20_L1S_START                (0)
#define SOC_USB3OTG_PORTPMSC_20_L1S_END                  (2)
#define SOC_USB3OTG_PORTPMSC_20_RWE_START                (3)
#define SOC_USB3OTG_PORTPMSC_20_RWE_END                  (3)
#define SOC_USB3OTG_PORTPMSC_20_HIRD_START               (4)
#define SOC_USB3OTG_PORTPMSC_20_HIRD_END                 (7)
#define SOC_USB3OTG_PORTPMSC_20_L1_Device_Slot_START     (8)
#define SOC_USB3OTG_PORTPMSC_20_L1_Device_Slot_END       (15)
#define SOC_USB3OTG_PORTPMSC_20_HLE_START                (16)
#define SOC_USB3OTG_PORTPMSC_20_HLE_END                  (16)
#define SOC_USB3OTG_PORTPMSC_20_Port_Test_Control_START  (28)
#define SOC_USB3OTG_PORTPMSC_20_Port_Test_Control_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_PORTLI_UNION
 结构说明  : PORTLI 寄存器结构定义。地址偏移量:0x0428，初值:0x00000000，宽度:32
 寄存器说明: Port Link Information寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  link_error_count : 16; /* bit[0-15] : 返回端口检测到的link error数。 */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_USB3OTG_PORTLI_UNION;
#endif
#define SOC_USB3OTG_PORTLI_link_error_count_START  (0)
#define SOC_USB3OTG_PORTLI_link_error_count_END    (15)


/*****************************************************************************
 结构名    : SOC_USB3OTG_PORTHLPMC_20_UNION
 结构说明  : PORTHLPMC_20 寄存器结构定义。地址偏移量:0x042C，初值:0x00000000，宽度:32
 寄存器说明: 端口LPM控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HIRDM      : 2;  /* bit[0-1]  :  */
        unsigned int  L1_timeout : 8;  /* bit[2-9]  :  */
        unsigned int  HIRDD      : 4;  /* bit[10-13]:  */
        unsigned int  reserved   : 18; /* bit[14-31]:  */
    } reg;
} SOC_USB3OTG_PORTHLPMC_20_UNION;
#endif
#define SOC_USB3OTG_PORTHLPMC_20_HIRDM_START       (0)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDM_END         (1)
#define SOC_USB3OTG_PORTHLPMC_20_L1_timeout_START  (2)
#define SOC_USB3OTG_PORTHLPMC_20_L1_timeout_END    (9)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDD_START       (10)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDD_END         (13)


/*****************************************************************************
 结构名    : SOC_USB3OTG_MFINDEX_UNION
 结构说明  : MFINDEX 寄存器结构定义。地址偏移量:0x440，初值:0x00000000，宽度:32
 寄存器说明: MicroFrame Index寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  microframe_index : 14; /* bit[0-13] : 每隔125us，该数值加1. */
        unsigned int  reserved         : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_USB3OTG_MFINDEX_UNION;
#endif
#define SOC_USB3OTG_MFINDEX_microframe_index_START  (0)
#define SOC_USB3OTG_MFINDEX_microframe_index_END    (13)


/*****************************************************************************
 结构名    : SOC_USB3OTG_IMAN_UNION
 结构说明  : IMAN 寄存器结构定义。地址偏移量:0x460，初值:0x00000000，宽度:32
 寄存器说明: Interrupter Management寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IP       : 1;  /* bit[0]   : Interrupt Pending.指示当前的中断器状态。
                                                   0：中断器有中断请求;
                                                   1: 中断器没有中断请求. */
        unsigned int  IE       : 1;  /* bit[1]   : Interrupt Enable.指示中断器是否使能产生中断。
                                                   0：中断器禁止产生中断；
                                                   1：当IP=1，并且IMODC为0，那么就会产生中断。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_USB3OTG_IMAN_UNION;
#endif
#define SOC_USB3OTG_IMAN_IP_START        (0)
#define SOC_USB3OTG_IMAN_IP_END          (0)
#define SOC_USB3OTG_IMAN_IE_START        (1)
#define SOC_USB3OTG_IMAN_IE_END          (1)


/*****************************************************************************
 结构名    : SOC_USB3OTG_IMOD_UNION
 结构说明  : IMOD 寄存器结构定义。地址偏移量:0x464，初值:0x00000FA0，宽度:32
 寄存器说明: Interrupt Moderation寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IMODI : 16; /* bit[0-15] : interrupt moderation interval.内部中断的最小间隔，以250ns为间隔增加。当该数值为0，其他中断条件满足时，立即产生中断。 */
        unsigned int  IMODC : 16; /* bit[16-31]: Interrupt Moderation Counter.当IP=0，加载IMODI数值，向下减到0后停止。 */
    } reg;
} SOC_USB3OTG_IMOD_UNION;
#endif
#define SOC_USB3OTG_IMOD_IMODI_START  (0)
#define SOC_USB3OTG_IMOD_IMODI_END    (15)
#define SOC_USB3OTG_IMOD_IMODC_START  (16)
#define SOC_USB3OTG_IMOD_IMODC_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ERSTSZ_UNION
 结构说明  : ERSTSZ 寄存器结构定义。地址偏移量:0x468，初值:0x00000000，宽度:32
 寄存器说明: Event Ring Segment Table Size寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_ring_segment_table_size : 16; /* bit[0-15] : 该域指示有效的Event Ring Segment Table entry的数量。该Table的基地址由Event Ring Segment Table Base Address寄存器指定。该数值的最大值有HCSPARAMS2的ERST_max决定。
                                                                         对于二级中断器，当该数值为0时，Event Ring关闭。对于原始中断器，当该数值为0时，导致Event Ring的不可预知行为。 */
        unsigned int  reserved                      : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_USB3OTG_ERSTSZ_UNION;
#endif
#define SOC_USB3OTG_ERSTSZ_event_ring_segment_table_size_START  (0)
#define SOC_USB3OTG_ERSTSZ_event_ring_segment_table_size_END    (15)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ERSTBA_L_UNION
 结构说明  : ERSTBA_L 寄存器结构定义。地址偏移量:0x470，初值:0x00000000，宽度:32
 寄存器说明: Event Ring Segment Table基地址低位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                              : 6;  /* bit[0-5] : 保留 */
        unsigned int  event_ring_segment_table_base_address : 26; /* bit[6-31]: 与ERSTBA_H一起指示Event Ring Segment Table基地址。当HCH=0时，不能对该域进行修改。 */
    } reg;
} SOC_USB3OTG_ERSTBA_L_UNION;
#endif
#define SOC_USB3OTG_ERSTBA_L_event_ring_segment_table_base_address_START  (6)
#define SOC_USB3OTG_ERSTBA_L_event_ring_segment_table_base_address_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ERSTBA_H_UNION
 结构说明  : ERSTBA_H 寄存器结构定义。地址偏移量:0x474，初值:0x00000000，宽度:32
 寄存器说明: Event Ring Segment Table基地址高位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_ring_segment_table_base_address : 32; /* bit[0-31]: 与ERSTBA_L[31：6]一起指示Event Ring Segment Table基地址。当HCH=0时，不能对该域进行修改。 */
    } reg;
} SOC_USB3OTG_ERSTBA_H_UNION;
#endif
#define SOC_USB3OTG_ERSTBA_H_event_ring_segment_table_base_address_START  (0)
#define SOC_USB3OTG_ERSTBA_H_event_ring_segment_table_base_address_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ERDP_L_UNION
 结构说明  : ERDP_L 寄存器结构定义。地址偏移量:0x478，初值:0x00000000，宽度:32
 寄存器说明: Event Ring Dequeue Pointer低位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DESI                       : 3;  /* bit[0-2] : Dequeue ERST Segment Index.xHC使用该域来加快确认Event Ring full条件。 */
        unsigned int  EHB                        : 1;  /* bit[3]   : Event Handler Busy.当IP=1时该bit置1，并且当event_ring_dequeue_pointer赋值后，软件需要将该bit清0. */
        unsigned int  event_ring_dequeue_pointer : 28; /* bit[4-31]: 与ERDP_H一起指定dequeue pointer的基地址。 */
    } reg;
} SOC_USB3OTG_ERDP_L_UNION;
#endif
#define SOC_USB3OTG_ERDP_L_DESI_START                        (0)
#define SOC_USB3OTG_ERDP_L_DESI_END                          (2)
#define SOC_USB3OTG_ERDP_L_EHB_START                         (3)
#define SOC_USB3OTG_ERDP_L_EHB_END                           (3)
#define SOC_USB3OTG_ERDP_L_event_ring_dequeue_pointer_START  (4)
#define SOC_USB3OTG_ERDP_L_event_ring_dequeue_pointer_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ERDP_H_UNION
 结构说明  : ERDP_H 寄存器结构定义。地址偏移量:0x47C，初值:0x00000000，宽度:32
 寄存器说明: Event Ring Dequeue Pointer高位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_ring_dequeue_pointer : 32; /* bit[0-31]: 与ERDP_L[31：4]一起指定dequeue pointer的基地址。 */
    } reg;
} SOC_USB3OTG_ERDP_H_UNION;
#endif
#define SOC_USB3OTG_ERDP_H_event_ring_dequeue_pointer_START  (0)
#define SOC_USB3OTG_ERDP_H_event_ring_dequeue_pointer_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DB_UNION
 结构说明  : DB 寄存器结构定义。地址偏移量:0x480，初值:0x00000000，宽度:32
 寄存器说明: Doorbell寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DB_tagger    : 8;  /* bit[0-7]  : 显示doorbell指定的目标。数值0专门用于Command Ring。
                                                        Device Context Doorbells(1-255):
                                                        0:reserved;
                                                        1:control EP0 enqueue pointer update
                                                        2:EP1 OUT enqueue pointer update;
                                                        3:EP1 IN enqueue pointer update;
                                                        …
                                                        30:EP15 OUT enqueue pointer update;
                                                        31:EP15 IN enqueue pointer update;
                                                        32-247:reserved;
                                                        248-255:Vendor Defined.
                                                        Host Controller Doorbell:
                                                        0:command doorbell;
                                                        1-247:reserved;
                                                        248-255:Vendor defined.
                                                        软件读该数值时返回0. */
        unsigned int  reserved     : 8;  /* bit[8-15] : 保留 */
        unsigned int  DB_Stream_ID : 16; /* bit[16-31]: 待定 */
    } reg;
} SOC_USB3OTG_DB_UNION;
#endif
#define SOC_USB3OTG_DB_DB_tagger_START     (0)
#define SOC_USB3OTG_DB_DB_tagger_END       (7)
#define SOC_USB3OTG_DB_DB_Stream_ID_START  (16)
#define SOC_USB3OTG_DB_DB_Stream_ID_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_USBLEGSUP_UNION
 结构说明  : USBLEGSUP 寄存器结构定义。地址偏移量:0x8A0，初值:0x00000401，宽度:32
 寄存器说明: USB Legacy Support Capability寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  capability_ID           : 8;  /* bit[0-7]  : 识别扩展了什么功能 */
        unsigned int  next_capability_pointer : 8;  /* bit[8-15] : 指示下个功能的基地址. */
        unsigned int  HC_BIOS_owned_semaphore : 1;  /* bit[16]   : BIOS配置该数值以建立xHC的ownership */
        unsigned int  reserved_0              : 7;  /* bit[17-23]: 保留 */
        unsigned int  HC_OS_owned_semaphore   : 1;  /* bit[24]   : 系统软件配置该bit用以请求xHC的ownership. */
        unsigned int  reserved_1              : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_USB3OTG_USBLEGSUP_UNION;
#endif
#define SOC_USB3OTG_USBLEGSUP_capability_ID_START            (0)
#define SOC_USB3OTG_USBLEGSUP_capability_ID_END              (7)
#define SOC_USB3OTG_USBLEGSUP_next_capability_pointer_START  (8)
#define SOC_USB3OTG_USBLEGSUP_next_capability_pointer_END    (15)
#define SOC_USB3OTG_USBLEGSUP_HC_BIOS_owned_semaphore_START  (16)
#define SOC_USB3OTG_USBLEGSUP_HC_BIOS_owned_semaphore_END    (16)
#define SOC_USB3OTG_USBLEGSUP_HC_OS_owned_semaphore_START    (24)
#define SOC_USB3OTG_USBLEGSUP_HC_OS_owned_semaphore_END      (24)


/*****************************************************************************
 结构名    : SOC_USB3OTG_USBLEGCTLSTS_UNION
 结构说明  : USBLEGCTLSTS 寄存器结构定义。地址偏移量:0x8A4，初值:0x00000000，宽度:32
 寄存器说明: USB legavy support control/status寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  USB_SMI_enable                  : 1;  /* bit[0]    : 当该bit为1，且SMI on event interrupt位也为1，那么控制器立即发出SMI */
        unsigned int  reserved_0                      : 3;  /* bit[1-3]  : 保留 */
        unsigned int  SMI_on_host_system_error_enable : 1;  /* bit[4]    : 当该bit为1，且SMI on host system error位也为1，那么控制器立即发出SMI */
        unsigned int  reserved_1                      : 8;  /* bit[5-12] : 保留 */
        unsigned int  SMI_on_OS_ownership_enable      : 1;  /* bit[13]   : 当该bit为1，且OS owenership change位也为1，那么控制器立即发出SMI */
        unsigned int  SMI_on_PCI_command_enable       : 1;  /* bit[14]   : 当该bit为1，且SMI on PCI cammand位也为1，那么控制器立即发出SMI */
        unsigned int  SMI_on_BAR_enable               : 1;  /* bit[15]   : 当该bit为1，且BAR也为1，那么控制器立即发出SMI */
        unsigned int  SMI_on_event_interrupt          : 1;  /* bit[16]   : 该bit与EINT一致 */
        unsigned int  reserved_2                      : 3;  /* bit[17-19]: 保留 */
        unsigned int  SMI_on_host_system_error        : 1;  /* bit[20]   : 该bit域HSE一致 */
        unsigned int  reserved_3                      : 8;  /* bit[21-28]: 保留 */
        unsigned int  SMI_on_OS_ownership_change      : 1;  /* bit[29]   : 反映USBLEGSUP寄存器HC OS owned semaphore域的变化 */
        unsigned int  SMI_on_PCI_command              : 1;  /* bit[30]   : 当PCI command寄存器被写入时，该bit为1 */
        unsigned int  SMI_on_BAR                      : 1;  /* bit[31]   : 当BAR寄存器被写入时，该bit为1 */
    } reg;
} SOC_USB3OTG_USBLEGCTLSTS_UNION;
#endif
#define SOC_USB3OTG_USBLEGCTLSTS_USB_SMI_enable_START                   (0)
#define SOC_USB3OTG_USBLEGCTLSTS_USB_SMI_enable_END                     (0)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_enable_START  (4)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_enable_END    (4)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_enable_START       (13)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_enable_END         (13)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_enable_START        (14)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_enable_END          (14)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_enable_START                (15)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_enable_END                  (15)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_event_interrupt_START           (16)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_event_interrupt_END             (16)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_START         (20)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_END           (20)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_change_START       (29)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_change_END         (29)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_START               (30)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_END                 (30)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_START                       (31)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_END                         (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GSBUSCFG0_UNION
 结构说明  : GSBUSCFG0 寄存器结构定义。地址偏移量:0xC100，初值:0x0000000E，宽度:32
 寄存器说明: SOC总线配置寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INCRBrstEna    : 1;  /* bit[0]    : 不定长burst使能。注意：该bit必须配置为0。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  INCR4BrstEna   : 1;  /* bit[1]    : INCR4使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  INCR8BrstEna   : 1;  /* bit[2]    : INCR8使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  INCR16BrstEna  : 1;  /* bit[3]    : INCR16使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  INCR32BrstEna  : 1;  /* bit[4]    : INCR32使能。注意：该bit必须配置为0。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  INCR64BrstEna  : 1;  /* bit[5]    : INCR64使能。注意：该bit必须配置为0。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  INCR128BrstEna : 1;  /* bit[6]    : INCR128使能。注意：该bit必须配置为0。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  INCR256BrstEna : 1;  /* bit[7]    : INCR256使能。注意：该bit必须配置为0。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  reserved_0     : 2;  /* bit[8-9]  : 保留。 */
        unsigned int  DescBigEnd     : 1;  /* bit[10]   : 描述符大小端配置。
                                                          0：小端；
                                                          1：大端。 */
        unsigned int  DatBigEnd      : 1;  /* bit[11]   : 数据大小端配置。
                                                          0：小端；
                                                          1：大端。 */
        unsigned int  reserved_1     : 4;  /* bit[12-15]: 保留。 */
        unsigned int  DesWrReqInfo   : 4;  /* bit[16-19]: 写描述符操作AXI-cache配置。 */
        unsigned int  DatWrReqInfo   : 4;  /* bit[20-23]: 写数据操作AXI-cache配置。 */
        unsigned int  DesRdReqInfo   : 4;  /* bit[24-27]: 读描述符操作AXI-cache配置。 */
        unsigned int  DatRdReqInfo   : 4;  /* bit[28-31]: 读数据操作AXI-cache配置。 */
    } reg;
} SOC_USB3OTG_GSBUSCFG0_UNION;
#endif
#define SOC_USB3OTG_GSBUSCFG0_INCRBrstEna_START     (0)
#define SOC_USB3OTG_GSBUSCFG0_INCRBrstEna_END       (0)
#define SOC_USB3OTG_GSBUSCFG0_INCR4BrstEna_START    (1)
#define SOC_USB3OTG_GSBUSCFG0_INCR4BrstEna_END      (1)
#define SOC_USB3OTG_GSBUSCFG0_INCR8BrstEna_START    (2)
#define SOC_USB3OTG_GSBUSCFG0_INCR8BrstEna_END      (2)
#define SOC_USB3OTG_GSBUSCFG0_INCR16BrstEna_START   (3)
#define SOC_USB3OTG_GSBUSCFG0_INCR16BrstEna_END     (3)
#define SOC_USB3OTG_GSBUSCFG0_INCR32BrstEna_START   (4)
#define SOC_USB3OTG_GSBUSCFG0_INCR32BrstEna_END     (4)
#define SOC_USB3OTG_GSBUSCFG0_INCR64BrstEna_START   (5)
#define SOC_USB3OTG_GSBUSCFG0_INCR64BrstEna_END     (5)
#define SOC_USB3OTG_GSBUSCFG0_INCR128BrstEna_START  (6)
#define SOC_USB3OTG_GSBUSCFG0_INCR128BrstEna_END    (6)
#define SOC_USB3OTG_GSBUSCFG0_INCR256BrstEna_START  (7)
#define SOC_USB3OTG_GSBUSCFG0_INCR256BrstEna_END    (7)
#define SOC_USB3OTG_GSBUSCFG0_DescBigEnd_START      (10)
#define SOC_USB3OTG_GSBUSCFG0_DescBigEnd_END        (10)
#define SOC_USB3OTG_GSBUSCFG0_DatBigEnd_START       (11)
#define SOC_USB3OTG_GSBUSCFG0_DatBigEnd_END         (11)
#define SOC_USB3OTG_GSBUSCFG0_DesWrReqInfo_START    (16)
#define SOC_USB3OTG_GSBUSCFG0_DesWrReqInfo_END      (19)
#define SOC_USB3OTG_GSBUSCFG0_DatWrReqInfo_START    (20)
#define SOC_USB3OTG_GSBUSCFG0_DatWrReqInfo_END      (23)
#define SOC_USB3OTG_GSBUSCFG0_DesRdReqInfo_START    (24)
#define SOC_USB3OTG_GSBUSCFG0_DesRdReqInfo_END      (27)
#define SOC_USB3OTG_GSBUSCFG0_DatRdReqInfo_START    (28)
#define SOC_USB3OTG_GSBUSCFG0_DatRdReqInfo_END      (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GSBUSCFG1_UNION
 结构说明  : GSBUSCFG1 寄存器结构定义。地址偏移量:0xC104，初值:0x00000300，宽度:32
 寄存器说明: SOC总线配置寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0     : 8;  /* bit[0-7]  : 保留。 */
        unsigned int  PipeTransLimit : 4;  /* bit[8-11] : AXI传输outstanding深度配置。
                                                          4'h0：深度为1；
                                                          4'h1：深度为2；
                                                          ……
                                                          4'hF：深度为16。 */
        unsigned int  EN1KPAGE       : 1;  /* bit[12]   : 1K页面边界使能。
                                                          默认AXI传输边界为4KB。如果该位使能，则AXI传输边界为1KB，burst传输地址不能跨1K边界。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  reserved_1     : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_USB3OTG_GSBUSCFG1_UNION;
#endif
#define SOC_USB3OTG_GSBUSCFG1_PipeTransLimit_START  (8)
#define SOC_USB3OTG_GSBUSCFG1_PipeTransLimit_END    (11)
#define SOC_USB3OTG_GSBUSCFG1_EN1KPAGE_START        (12)
#define SOC_USB3OTG_GSBUSCFG1_EN1KPAGE_END          (12)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GTXTHRCFG_UNION
 结构说明  : GTXTHRCFG 寄存器结构定义。地址偏移量:0xC108，初值:0x0000，宽度:32
 寄存器说明: 发送水线控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 16; /* bit[0-15] : 保留。 */
        unsigned int  USBMaxTxBurstSize : 8;  /* bit[16-23]: 最大发送burst长度。 */
        unsigned int  USBTxPktCnt       : 4;  /* bit[24-27]: USB发送包个数，仅当USBTxPktCntSel为1时有效。 */
        unsigned int  reserved_1        : 1;  /* bit[28]   : 保留。 */
        unsigned int  USBTxPktCntSel    : 1;  /* bit[29]   : 多包传输水线模式使能。
                                                             如果该bit不使能，发送FIFO中有整包数据开始USB总线传输。
                                                             如果该bit使能，则发送FIFO中预取了USBTxPktCnt个数据包之后开始USB传输。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  reserved_2        : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GTXTHRCFG_UNION;
#endif
#define SOC_USB3OTG_GTXTHRCFG_USBMaxTxBurstSize_START  (16)
#define SOC_USB3OTG_GTXTHRCFG_USBMaxTxBurstSize_END    (23)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCnt_START        (24)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCnt_END          (27)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCntSel_START     (29)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCntSel_END       (29)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GRXTHRCFG_UNION
 结构说明  : GRXTHRCFG 寄存器结构定义。地址偏移量:0xC10C，初值:0x0000，宽度:32
 寄存器说明: 接收水线控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 19; /* bit[0-18] : 保留。 */
        unsigned int  USBMaxRxBurstSize : 5;  /* bit[19-23]: 最大接收burst长度。 */
        unsigned int  USBRxPktCnt       : 4;  /* bit[24-27]: USB接收包个数，仅当USBRxPktCntSel＝1时有效。 */
        unsigned int  reserved_1        : 1;  /* bit[28]   : 保留。 */
        unsigned int  USBRxPktCntSel    : 1;  /* bit[29]   : 多包传输水线模式使能。
                                                             如果该bit不使能，接收FIFO中有1个数据包的空间开始接收USB数据。
                                                             如果该bit使能，则接收FIFO中有USBRxPktCnt个数据包空间之后开始接收USB数据。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  reserved_2        : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GRXTHRCFG_UNION;
#endif
#define SOC_USB3OTG_GRXTHRCFG_USBMaxRxBurstSize_START  (19)
#define SOC_USB3OTG_GRXTHRCFG_USBMaxRxBurstSize_END    (23)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCnt_START        (24)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCnt_END          (27)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCntSel_START     (29)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCntSel_END       (29)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GCTL_UNION
 结构说明  : GCTL 寄存器结构定义。地址偏移量:0xC110，初值:0x00193000，宽度:32
 寄存器说明: 全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DsblClkGtng       : 1;  /* bit[0]    : Disable时钟gating。 */
        unsigned int  GblHibernationEn  : 1;  /* bit[1]    : Hibernation使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  U2EXIT_LFPS       : 1;  /* bit[2]    : U2退出LFPS设置。
                                                             0：248ns的LFPS信号作为有效退出信号；
                                                             1：检测U2退出之前等待8us。 */
        unsigned int  DisScramble       : 1;  /* bit[3]    : 交织去使能。 */
        unsigned int  ScaleDown         : 2;  /* bit[4-5]  : ScaleDown模式。仅用于仿真。 */
        unsigned int  RAMClkSel         : 2;  /* bit[6-7]  : RAM时钟选择。
                                                             00：总线时钟；
                                                             01：PIPE接口时钟；
                                                             10：PIPE接口2分频时钟。
                                                             11：保留。 */
        unsigned int  DebugAttach       : 1;  /* bit[8]    : Attach调试使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  DisU1U2TimerScale : 1;  /* bit[9]    : U1U2 timer scaledown功能去使能。
                                                             仅当ScaleDown配置为2'bx1时有效。 */
        unsigned int  SOFTITPSYNC       : 1;  /* bit[10]   : 软ITP功能使能。
                                                             作为host时，如果使能该功能，则控制器使用ref_clk作为内部ITP计数器时钟。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  CoreSoftReset     : 1;  /* bit[11]   : 控制器软复位控制。
                                                             0：不复位；
                                                             1：复位。 */
        unsigned int  PrtCapDir         : 2;  /* bit[12-13]: 端口配置。
                                                             01：Host；
                                                             10：Device；
                                                             11：OTG。 */
        unsigned int  FrmSclDwn         : 2;  /* bit[14-15]: 帧间隔缩短配置。该域配置SOF/uSOF/ITP周期缩短。
                                                             对于SS/HS模式：
                                                             2'h3：帧间隔缩短为15.625us；
                                                             2'h2：帧间隔缩短为31.25us；
                                                             2'h1：帧间隔缩短为62.5us；
                                                             2'h0：帧间隔为125us。 */
        unsigned int  U2RSTECN          : 1;  /* bit[16]   : 如果POLL或者LMP交换过程中，SS连接失败，device会最为非SS设备连接。
                                                             如果该位配置为1，device在SS连接失败之后，还会尝试3次SS连接。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  BypassSetAddr     : 1;  /* bit[17]   : SetAddress旁路使能。该位使能，则device使用DCFG[DevAddr]作为地址，忽略SetAddress传输。该功能只能用于仿真。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  MasterFiltBypass  : 1;  /* bit[18]   : Filter电路旁路使能。该位配置为1，则输入信号utmiotg_iddig，utmiotg_vbusvalid，utmiotg_bvalid，utmisrp_sessend，pipe3_PowerPresent的Filter电路被旁路。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  GPwrDnScale       : 13; /* bit[19-31]: 低功耗时钟分频系数。指将suspend_clk分频为16KHz的分频系数。 */
    } reg;
} SOC_USB3OTG_GCTL_UNION;
#endif
#define SOC_USB3OTG_GCTL_DsblClkGtng_START        (0)
#define SOC_USB3OTG_GCTL_DsblClkGtng_END          (0)
#define SOC_USB3OTG_GCTL_GblHibernationEn_START   (1)
#define SOC_USB3OTG_GCTL_GblHibernationEn_END     (1)
#define SOC_USB3OTG_GCTL_U2EXIT_LFPS_START        (2)
#define SOC_USB3OTG_GCTL_U2EXIT_LFPS_END          (2)
#define SOC_USB3OTG_GCTL_DisScramble_START        (3)
#define SOC_USB3OTG_GCTL_DisScramble_END          (3)
#define SOC_USB3OTG_GCTL_ScaleDown_START          (4)
#define SOC_USB3OTG_GCTL_ScaleDown_END            (5)
#define SOC_USB3OTG_GCTL_RAMClkSel_START          (6)
#define SOC_USB3OTG_GCTL_RAMClkSel_END            (7)
#define SOC_USB3OTG_GCTL_DebugAttach_START        (8)
#define SOC_USB3OTG_GCTL_DebugAttach_END          (8)
#define SOC_USB3OTG_GCTL_DisU1U2TimerScale_START  (9)
#define SOC_USB3OTG_GCTL_DisU1U2TimerScale_END    (9)
#define SOC_USB3OTG_GCTL_SOFTITPSYNC_START        (10)
#define SOC_USB3OTG_GCTL_SOFTITPSYNC_END          (10)
#define SOC_USB3OTG_GCTL_CoreSoftReset_START      (11)
#define SOC_USB3OTG_GCTL_CoreSoftReset_END        (11)
#define SOC_USB3OTG_GCTL_PrtCapDir_START          (12)
#define SOC_USB3OTG_GCTL_PrtCapDir_END            (13)
#define SOC_USB3OTG_GCTL_FrmSclDwn_START          (14)
#define SOC_USB3OTG_GCTL_FrmSclDwn_END            (15)
#define SOC_USB3OTG_GCTL_U2RSTECN_START           (16)
#define SOC_USB3OTG_GCTL_U2RSTECN_END             (16)
#define SOC_USB3OTG_GCTL_BypassSetAddr_START      (17)
#define SOC_USB3OTG_GCTL_BypassSetAddr_END        (17)
#define SOC_USB3OTG_GCTL_MasterFiltBypass_START   (18)
#define SOC_USB3OTG_GCTL_MasterFiltBypass_END     (18)
#define SOC_USB3OTG_GCTL_GPwrDnScale_START        (19)
#define SOC_USB3OTG_GCTL_GPwrDnScale_END          (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GPMSTS_UNION
 结构说明  : GPMSTS 寄存器结构定义。地址偏移量:0xC114，初值:0x0000，宽度:32
 寄存器说明: 全局电源管理状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  U2Wakeup : 10; /* bit[0-9]  : USB2.0端口唤醒条件。
                                                    Bit[0]：检测到过流；
                                                    Bit[1]：检测到resume；
                                                    Bit[2]：检测到连接；
                                                    Bit[3]：检测到断开连接；
                                                    Bit[4]：上次连接状态；
                                                    Bit[5]：ID状态变化；
                                                    Bit[6]：检测到SRP请求；
                                                    Bit[7]：保留；
                                                    Bit[8]：检测到复位；
                                                    Bit[9]：检测到resume状态变化； */
        unsigned int  reserved_0: 2;  /* bit[10-11]: 保留。 */
        unsigned int  U3Wakeup : 5;  /* bit[12-16]: USB3.0端口唤醒条件。
                                                    Bit[12]：检测到过流；
                                                    bit[13]：检测到Resume；
                                                    bit[14]：检测到连接；
                                                    bit[15]：检测到断开连接；
                                                    bit[16]：上次连接状态。 */
        unsigned int  reserved_1: 11; /* bit[17-27]: 保留。 */
        unsigned int  PortSel  : 4;  /* bit[28-31]: 端口选择。 */
    } reg;
} SOC_USB3OTG_GPMSTS_UNION;
#endif
#define SOC_USB3OTG_GPMSTS_U2Wakeup_START  (0)
#define SOC_USB3OTG_GPMSTS_U2Wakeup_END    (9)
#define SOC_USB3OTG_GPMSTS_U3Wakeup_START  (12)
#define SOC_USB3OTG_GPMSTS_U3Wakeup_END    (16)
#define SOC_USB3OTG_GPMSTS_PortSel_START   (28)
#define SOC_USB3OTG_GPMSTS_PortSel_END     (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GSTS_UNION
 结构说明  : GSTS 寄存器结构定义。地址偏移量:0xC118，初值:0x0000，宽度:32
 寄存器说明: 全局状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 4;  /* bit[0-3]  : 保留。 */
        unsigned int  BusErrAddrVld : 1;  /* bit[4]    : 总线错误。 */
        unsigned int  CSRTimeout    : 1;  /* bit[5]    : 寄存器访问超时，写1清除。 */
        unsigned int  Device_IP     : 1;  /* bit[6]    : Device中断有效。 */
        unsigned int  Host_IP       : 1;  /* bit[7]    : Host中断有效。 */
        unsigned int  ADP_IP        : 1;  /* bit[8]    : ADP中断待处理。 */
        unsigned int  BC_IP         : 1;  /* bit[9]    : BC中断待处理。 */
        unsigned int  OTG_IP        : 1;  /* bit[10]   : 有OTG中断待处理。 */
        unsigned int  reserved_1    : 9;  /* bit[11-19]: 保留。 */
        unsigned int  CBELT         : 12; /* bit[20-31]: 当前BELT(Best Effort Latency Tolerance Value)。 */
    } reg;
} SOC_USB3OTG_GSTS_UNION;
#endif
#define SOC_USB3OTG_GSTS_BusErrAddrVld_START  (4)
#define SOC_USB3OTG_GSTS_BusErrAddrVld_END    (4)
#define SOC_USB3OTG_GSTS_CSRTimeout_START     (5)
#define SOC_USB3OTG_GSTS_CSRTimeout_END       (5)
#define SOC_USB3OTG_GSTS_Device_IP_START      (6)
#define SOC_USB3OTG_GSTS_Device_IP_END        (6)
#define SOC_USB3OTG_GSTS_Host_IP_START        (7)
#define SOC_USB3OTG_GSTS_Host_IP_END          (7)
#define SOC_USB3OTG_GSTS_ADP_IP_START         (8)
#define SOC_USB3OTG_GSTS_ADP_IP_END           (8)
#define SOC_USB3OTG_GSTS_BC_IP_START          (9)
#define SOC_USB3OTG_GSTS_BC_IP_END            (9)
#define SOC_USB3OTG_GSTS_OTG_IP_START         (10)
#define SOC_USB3OTG_GSTS_OTG_IP_END           (10)
#define SOC_USB3OTG_GSTS_CBELT_START          (20)
#define SOC_USB3OTG_GSTS_CBELT_END            (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GUCTL1_UNION
 结构说明  : GUCTL1 寄存器结构定义。地址偏移量:0xC11C，初值:0x0002，宽度:32
 寄存器说明: 用户控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LOA_FILTER_EN : 1;  /* bit[0]   : LOA(Loss of Activity)滤波使能。使能该功能，则至少3次连续检测到LOA才会去使能端口。该设置仅对Host有效。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GUCTL1_UNION;
#endif
#define SOC_USB3OTG_GUCTL1_LOA_FILTER_EN_START  (0)
#define SOC_USB3OTG_GUCTL1_LOA_FILTER_EN_END    (0)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GSNPSID_UNION
 结构说明  : GSNPSID 寄存器结构定义。地址偏移量:0xC120，初值:0x5533290A，宽度:32
 寄存器说明: 控制器版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SynopsysID : 32; /* bit[0-31]: 控制器版本ID。 */
    } reg;
} SOC_USB3OTG_GSNPSID_UNION;
#endif
#define SOC_USB3OTG_GSNPSID_SynopsysID_START  (0)
#define SOC_USB3OTG_GSNPSID_SynopsysID_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GUCTL_UNION
 结构说明  : GUCTL 寄存器结构定义。地址偏移量:0xC12C，初值:0x02008010，宽度:32
 寄存器说明: 用户控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DTFT                : 9;  /* bit[0-8]  : Device超时微调。超时时间为：DTFT*256*8ns。 */
        unsigned int  DTCT                : 2;  /* bit[9-10] : Device超时粗调节。
                                                               00: 用DTFT值代替；
                                                               01: 500us；
                                                               10: 1.5ms；
                                                               11: 6.5ms。 */
        unsigned int  CSR                 : 1;  /* bit[11]   : 在FS Bulk OUT事务之间，插入额外的延迟。
                                                               0：不使能；
                                                               1：host在连续的bulk OUT传输之间插入12us延迟。 */
        unsigned int  ExtCapSuptEN        : 1;  /* bit[12]   : 支持外部扩展xHCI Capability寄存器。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  EnOverlapChk        : 1;  /* bit[13]   : 远程Ux状态退出过程中，使能LFPS重叠检测。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  USBHstInAutoRetryEn : 1;  /* bit[14]   : Host IN传输自动重试使能。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  CMDevAddr           : 1;  /* bit[15]   : device地址兼容模式。
                                                               0：device地址等于slot ID；
                                                               1：收到AddressDevice命令后，device地址递增。
                                                               该bit必须配置为1，0仅用于debug。 */
        unsigned int  ResBwHSEPS          : 1;  /* bit[16]   : 对于HS周期传输，主机保留85％带宽。默认主机保留80％带宽。 */
        unsigned int  SprsCtrlTransEn     : 1;  /* bit[17]   : 稀疏控制事务使能。
                                                               该位使能，host控制器不会在一个微帧内传输多个控制事务。 */
        unsigned int  PSQExtrResSp        : 3;  /* bit[18-20]: PSQ(Protocol Status Queue)额外的保留空间。Debug功能，正常模式不需要使用。 */
        unsigned int  NoExtrDl            : 1;  /* bit[21]   : SOF和第一个包之间的延时控制。
                                                               0：Host在发送SOF之后等待2us之后发送第一个包；
                                                               1：host在发送SOF之后立即发送第一个包。 */
        unsigned int  REFCLKPER           : 10; /* bit[22-31]: 输入时钟信号ref_clk周期配置，以ns为单位。 */
    } reg;
} SOC_USB3OTG_GUCTL_UNION;
#endif
#define SOC_USB3OTG_GUCTL_DTFT_START                 (0)
#define SOC_USB3OTG_GUCTL_DTFT_END                   (8)
#define SOC_USB3OTG_GUCTL_DTCT_START                 (9)
#define SOC_USB3OTG_GUCTL_DTCT_END                   (10)
#define SOC_USB3OTG_GUCTL_CSR_START                  (11)
#define SOC_USB3OTG_GUCTL_CSR_END                    (11)
#define SOC_USB3OTG_GUCTL_ExtCapSuptEN_START         (12)
#define SOC_USB3OTG_GUCTL_ExtCapSuptEN_END           (12)
#define SOC_USB3OTG_GUCTL_EnOverlapChk_START         (13)
#define SOC_USB3OTG_GUCTL_EnOverlapChk_END           (13)
#define SOC_USB3OTG_GUCTL_USBHstInAutoRetryEn_START  (14)
#define SOC_USB3OTG_GUCTL_USBHstInAutoRetryEn_END    (14)
#define SOC_USB3OTG_GUCTL_CMDevAddr_START            (15)
#define SOC_USB3OTG_GUCTL_CMDevAddr_END              (15)
#define SOC_USB3OTG_GUCTL_ResBwHSEPS_START           (16)
#define SOC_USB3OTG_GUCTL_ResBwHSEPS_END             (16)
#define SOC_USB3OTG_GUCTL_SprsCtrlTransEn_START      (17)
#define SOC_USB3OTG_GUCTL_SprsCtrlTransEn_END        (17)
#define SOC_USB3OTG_GUCTL_PSQExtrResSp_START         (18)
#define SOC_USB3OTG_GUCTL_PSQExtrResSp_END           (20)
#define SOC_USB3OTG_GUCTL_NoExtrDl_START             (21)
#define SOC_USB3OTG_GUCTL_NoExtrDl_END               (21)
#define SOC_USB3OTG_GUCTL_REFCLKPER_START            (22)
#define SOC_USB3OTG_GUCTL_REFCLKPER_END              (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GBUSERRADDRL_UNION
 结构说明  : GBUSERRADDRL 寄存器结构定义。地址偏移量:0xC130，初值:0x0000，宽度:32
 寄存器说明: 总线错误地址寄存器L
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BusAddrl : 32; /* bit[0-31]: 总线错误地址,低32位。 */
    } reg;
} SOC_USB3OTG_GBUSERRADDRL_UNION;
#endif
#define SOC_USB3OTG_GBUSERRADDRL_BusAddrl_START  (0)
#define SOC_USB3OTG_GBUSERRADDRL_BusAddrl_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GBUSERRADDRH_UNION
 结构说明  : GBUSERRADDRH 寄存器结构定义。地址偏移量:0xC134，初值:0x0000，宽度:32
 寄存器说明: 总线错误地址寄存器H
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BusAddrh : 32; /* bit[0-31]: 总线错误地址,高32位。 */
    } reg;
} SOC_USB3OTG_GBUSERRADDRH_UNION;
#endif
#define SOC_USB3OTG_GBUSERRADDRH_BusAddrh_START  (0)
#define SOC_USB3OTG_GBUSERRADDRH_BusAddrh_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS0_UNION
 结构说明  : GHWPARAMS0 寄存器结构定义。地址偏移量:0xC140，初值:0x2020400A，宽度:32
 寄存器说明: 硬件参数寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_MODE      : 3;  /* bit[0-2]  : 控制器模式选择，DRD。
                                                              0: Device(NPI or Non-NPI)
                                                              1: Host
                                                              2: DRD
                                                              3：Hub */
        unsigned int  DWC_USB3_MBUS_TYPE : 3;  /* bit[3-5]  : Master总线类型，AXI。
                                                              0:AHB
                                                              1:AXI
                                                              2:Reserved
                                                              3:Native
                                                              4:NPI */
        unsigned int  DWC_USB3_SBUS_TYPE : 2;  /* bit[6-7]  : slave总线类型，AHB。
                                                              0:AHB
                                                              1:AXI
                                                              2:Reserved
                                                              3:Native */
        unsigned int  DWC_USB3_MDWIDTH   : 8;  /* bit[8-15] : master总线数据位宽，64bit。 */
        unsigned int  DWC_USB3_SDWIDTH   : 8;  /* bit[16-23]: slave总线数据位宽，32bit。 */
        unsigned int  DWC_USB3_AWIDTH    : 8;  /* bit[24-31]: 地址位宽，32bit。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS0_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MODE_START       (0)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MODE_END         (2)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MBUS_TYPE_START  (3)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MBUS_TYPE_END    (5)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SBUS_TYPE_START  (6)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SBUS_TYPE_END    (7)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MDWIDTH_START    (8)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MDWIDTH_END      (15)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SDWIDTH_START    (16)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SDWIDTH_END      (23)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_AWIDTH_START     (24)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_AWIDTH_END       (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS1_UNION
 结构说明  : GHWPARAMS1 寄存器结构定义。地址偏移量:0xC144，初值:0x2E0C938，宽度:32
 寄存器说明: 硬件参数寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_IDWIDTH        : 3;  /* bit[0-2]  : ID宽度。 */
        unsigned int  DWC_USB3_BURSTWIDTH     : 3;  /* bit[3-5]  : 总线burst长度信号宽度。 */
        unsigned int  DWC_USB3_DATAINFOWIDTH  : 3;  /* bit[6-8]  : OCP总线datainfo位宽。 */
        unsigned int  DWC_USB3_REQINFOWIDTH   : 3;  /* bit[9-11] : AXI总线awcache位宽。 */
        unsigned int  DWC_USB3_ASPACEWIDTH    : 3;  /* bit[12-14]: AXI总线awprot位宽。 */
        unsigned int  DWC_USB3_DEVICE_NUM_INT : 6;  /* bit[15-20]: Device中断个数。 */
        unsigned int  DWC_USB3_NUM_RAMS       : 2;  /* bit[21-22]: RAM个数。
                                                                   2：2个；
                                                                   3：3个。 */
        unsigned int  DWC_USB3_SRAM_TYP       : 1;  /* bit[23]   : RAM类型选择。
                                                                   0：双端口RAM；
                                                                   1：单端口RAM。 */
        unsigned int  DWC_USB3_EN_PWROPT      : 2;  /* bit[24-25]: 功耗优化策略选择。
                                                                   0：无；
                                                                   1：时钟门控；
                                                                   2：时钟门控和冬眠模式。 */
        unsigned int  reserved                : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS1_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_IDWIDTH_START         (0)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_IDWIDTH_END           (2)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_BURSTWIDTH_START      (3)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_BURSTWIDTH_END        (5)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DATAINFOWIDTH_START   (6)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DATAINFOWIDTH_END     (8)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_REQINFOWIDTH_START    (9)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_REQINFOWIDTH_END      (11)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_ASPACEWIDTH_START     (12)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_ASPACEWIDTH_END       (14)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DEVICE_NUM_INT_START  (15)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DEVICE_NUM_INT_END    (20)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_NUM_RAMS_START        (21)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_NUM_RAMS_END          (22)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_SRAM_TYP_START        (23)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_SRAM_TYP_END          (23)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_EN_PWROPT_START       (24)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_EN_PWROPT_END         (25)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS2_UNION
 结构说明  : GHWPARAMS2 寄存器结构定义。地址偏移量:0xC148，初值:0x12345678，宽度:32
 寄存器说明: 硬件参数寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_USERID : 32; /* bit[0-31]: 用户ID寄存器。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS2_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS2_DWC_USB3_USERID_START  (0)
#define SOC_USB3OTG_GHWPARAMS2_DWC_USB3_USERID_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS3_UNION
 结构说明  : GHWPARAMS3 寄存器结构定义。地址偏移量:0xC14C，初值:0x10420085，宽度:32
 寄存器说明: 硬件参数寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_SSPHY_INTERFACE           : 2;  /* bit[0-1]  : SS PHY接口。
                                                                              0：无；
                                                                              1：PIPE3。 */
        unsigned int  DWC_USB3_HSPHY_INTERFACE           : 2;  /* bit[2-3]  : HS PHY接口。
                                                                              0:NONE
                                                                              1:UTMI+
                                                                              2:ULPI
                                                                              3:UTMI+ and ULPI */
        unsigned int  DWC_USB3_FSPHY_INTERFACE           : 2;  /* bit[4-5]  : FS PHY接口。
                                                                              0：无；
                                                                              1：专有串行接口；
                                                                              2：和UTMI共享。 */
        unsigned int  DWC_USB3_HSPHY_DWIDTH              : 2;  /* bit[6-7]  : UTMI接口数据位宽。
                                                                              0：8bit；
                                                                              1：16bit；
                                                                              2：8/16bit。 */
        unsigned int  reserved_0                         : 2;  /* bit[8-9]  : 保留。 */
        unsigned int  DWC_USB3_VENDOR_CTL_INTERFACE      : 1;  /* bit[10]   : 是否支持UTMI+ Vendor Control接口。
                                                                              0：不支持；
                                                                              1：支持。 */
        unsigned int  reserved_1                         : 1;  /* bit[11]   : 保留。 */
        unsigned int  DWC_USB3_NUM_EPS                   : 6;  /* bit[12-17]: Device支持的端点个数。 */
        unsigned int  DWC_USB3_NUM_IN_EPS                : 5;  /* bit[18-22]: 同时激活的IN端点个数。 */
        unsigned int  DWC_USB3_CACHE_TOTAL_XFER_RESOURCE : 8;  /* bit[23-30]: cache transfer资源。 */
        unsigned int  reserved_2                         : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS3_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_SSPHY_INTERFACE_START            (0)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_SSPHY_INTERFACE_END              (1)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_INTERFACE_START            (2)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_INTERFACE_END              (3)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_FSPHY_INTERFACE_START            (4)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_FSPHY_INTERFACE_END              (5)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_DWIDTH_START               (6)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_DWIDTH_END                 (7)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_VENDOR_CTL_INTERFACE_START       (10)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_VENDOR_CTL_INTERFACE_END         (10)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_EPS_START                    (12)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_EPS_END                      (17)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_IN_EPS_START                 (18)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_IN_EPS_END                   (22)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_CACHE_TOTAL_XFER_RESOURCE_START  (23)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_CACHE_TOTAL_XFER_RESOURCE_END    (30)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS4_UNION
 结构说明  : GHWPARAMS4 寄存器结构定义。地址偏移量:0xC150，初值:0x47822010，宽度:32
 寄存器说明: 硬件参数寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_CACHE_TRBS_PER_TRANSFER : 6;  /* bit[0-5]  : 每个transfer预取的TRB。 */
        unsigned int  reserved_0                       : 7;  /* bit[6-12] : 保留。 */
        unsigned int  DWC_USB3_HIBER_SCRATCHBUFS       : 4;  /* bit[13-16]: 冬眠模式下，保存内部状态的buffer个数。 */
        unsigned int  DWC_USB3_NUM_SS_USB_INSTANCE     : 4;  /* bit[17-20]: 支持SuperSpeed端口个数。 */
        unsigned int  reserved_1                       : 2;  /* bit[21-22]: 保留。 */
        unsigned int  DWC_USB3_EN_ISOC_SUPT            : 1;  /* bit[23]   : 是否支持同步传输。
                                                                            0：不支持；
                                                                            1：支持。 */
        unsigned int  DWC_USB3_BMU_PTL_DEPTH           : 4;  /* bit[24-27]: BMU模块PTL深度。 */
        unsigned int  DWC_USB3_BMU_LSP_DEPTH           : 4;  /* bit[28-31]: BMU模块LSP深度。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS4_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_CACHE_TRBS_PER_TRANSFER_START  (0)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_CACHE_TRBS_PER_TRANSFER_END    (5)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_HIBER_SCRATCHBUFS_START        (13)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_HIBER_SCRATCHBUFS_END          (16)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_NUM_SS_USB_INSTANCE_START      (17)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_NUM_SS_USB_INSTANCE_END        (20)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_EN_ISOC_SUPT_START             (23)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_EN_ISOC_SUPT_END               (23)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_PTL_DEPTH_START            (24)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_PTL_DEPTH_END              (27)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_LSP_DEPTH_START            (28)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_LSP_DEPTH_END              (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS5_UNION
 结构说明  : GHWPARAMS5 寄存器结构定义。地址偏移量:0xC154，初值:0x4204108，宽度:32
 寄存器说明: 硬件参数寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_BMU_BUSGM_DEPTH : 4;  /* bit[0-3]  : AXI总线GM模块buffer深度。 */
        unsigned int  DWC_USB3_RXQ_FIFO_DEPTH  : 6;  /* bit[4-9]  : 接收请求队列深度。 */
        unsigned int  DWC_USB3_TXQ_FIFO_DEPTH  : 6;  /* bit[10-15]: 发送请求队列深度。 */
        unsigned int  DWC_USB3_DWQ_FIFO_DEPTH  : 6;  /* bit[16-21]: 描述符写队列深度。 */
        unsigned int  DWC_USB3_DFQ_FIFO_DEPTH  : 6;  /* bit[22-27]: 描述符预取队列深度。 */
        unsigned int  reserved                 : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS5_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_BMU_BUSGM_DEPTH_START  (0)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_BMU_BUSGM_DEPTH_END    (3)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_RXQ_FIFO_DEPTH_START   (4)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_RXQ_FIFO_DEPTH_END     (9)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_TXQ_FIFO_DEPTH_START   (10)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_TXQ_FIFO_DEPTH_END     (15)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DWQ_FIFO_DEPTH_START   (16)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DWQ_FIFO_DEPTH_END     (21)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DFQ_FIFO_DEPTH_START   (22)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DFQ_FIFO_DEPTH_END     (27)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS6_UNION
 结构说明  : GHWPARAMS6 寄存器结构定义。地址偏移量:0xC158，初值:0x0800BC20，宽度:32
 寄存器说明: 硬件参数寄存器6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_PSQ_FIFO_DEPTH : 6;  /* bit[0-5]  : 协议状态队列深度。 */
        unsigned int  reserved_0              : 1;  /* bit[6]    : 保留。 */
        unsigned int  DWC_USB3_EN_FPGA        : 1;  /* bit[7]    : 是否使能FPGA时序优化。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  reserved_1              : 2;  /* bit[8-9]  : 保留。 */
        unsigned int  DWC_USB3_EN_SRP         : 1;  /* bit[10]   : 是否使能SRP。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  DWC_USB3_EN_HNP         : 1;  /* bit[11]   : 是否使能HNP。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  DWC_USB3_EN_ADP         : 1;  /* bit[12]   : 是否使能ADP。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  DWC_USB3_OTG3_SUPT      : 1;  /* bit[13]   : 是否支持OTG3.0。
                                                                   0：不支持；
                                                                   1：支持。 */
        unsigned int  DWC_USB3_EN_BC          : 1;  /* bit[14]   : BC使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  DWC_USB3_EN_BUS_FILTER  : 1;  /* bit[15]   : 使能OTG相关信号的filter。 */
        unsigned int  DWC_USB3_RAM0_DEPTH     : 16; /* bit[16-31]: RAM0深度。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS6_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_PSQ_FIFO_DEPTH_START  (0)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_PSQ_FIFO_DEPTH_END    (5)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_FPGA_START         (7)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_FPGA_END           (7)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_SRP_START          (10)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_SRP_END            (10)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_HNP_START          (11)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_HNP_END            (11)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_ADP_START          (12)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_ADP_END            (12)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_OTG3_SUPT_START       (13)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_OTG3_SUPT_END         (13)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BC_START           (14)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BC_END             (14)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BUS_FILTER_START   (15)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BUS_FILTER_END     (15)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_RAM0_DEPTH_START      (16)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_RAM0_DEPTH_END        (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS7_UNION
 结构说明  : GHWPARAMS7 寄存器结构定义。地址偏移量:0xC15C，初值:0x07761000，宽度:32
 寄存器说明: 硬件参数寄存器7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_RAM1_DEPTH : 16; /* bit[0-15] : RAM1深度。 */
        unsigned int  DWC_USB3_RAM2_DEPTH : 16; /* bit[16-31]: RAM2深度。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS7_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM1_DEPTH_START  (0)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM1_DEPTH_END    (15)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM2_DEPTH_START  (16)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM2_DEPTH_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GHWPARAMS8_UNION
 结构说明  : GHWPARAMS8 寄存器结构定义。地址偏移量:0xC600，初值:0x000007D0，宽度:32
 寄存器说明: 硬件参数寄存器8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_DCACHE_DEPTH_INFO : 32; /* bit[0-31]: dcache深度信息。 */
    } reg;
} SOC_USB3OTG_GHWPARAMS8_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS8_DWC_USB3_DCACHE_DEPTH_INFO_START  (0)
#define SOC_USB3OTG_GHWPARAMS8_DWC_USB3_DCACHE_DEPTH_INFO_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDBGFIFOSPACE_UNION
 结构说明  : GDBGFIFOSPACE 寄存器结构定义。地址偏移量:0xC160，初值:0x0000，宽度:32
 寄存器说明: Queue/FIFO剩余空间debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FIFOSek        : 8;  /* bit[0-7]  : FIFO/Queue选择。
                                                          8’b0001_1111 to 8'b0000_0000: 发送FIFO31到发送FIFO0；
                                                          8‘b0011_1111 to 8'b0010_0000: 接收FIFO31到接收FIFO0；
                                                          8'b0101_1111 to 8'b0100_0000: 发送请求队列31到发送请求队列0；
                                                          8'b0111_1111 to 8'b0110_0000: 接收请求队列31到接收请求队列0；
                                                          8'b1001_1111 to 8'b1000_0000: 接收信息队列31到接收信息队列0；
                                                          8’b1010_0000: 描述符预取队列；
                                                          8'b1010_0001: 事件队列；
                                                          8'b1010_0010: 协议状态队列。 */
        unsigned int  reserved       : 8;  /* bit[8-15] : 保留。 */
        unsigned int  SpaceAvailable : 16; /* bit[16-31]: 剩余空间。 */
    } reg;
} SOC_USB3OTG_GDBGFIFOSPACE_UNION;
#endif
#define SOC_USB3OTG_GDBGFIFOSPACE_FIFOSek_START         (0)
#define SOC_USB3OTG_GDBGFIFOSPACE_FIFOSek_END           (7)
#define SOC_USB3OTG_GDBGFIFOSPACE_SpaceAvailable_START  (16)
#define SOC_USB3OTG_GDBGFIFOSPACE_SpaceAvailable_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDBGLTSSM_UNION
 结构说明  : GDBGLTSSM 寄存器结构定义。地址偏移量:0xC164，初值:0x0000，宽度:32
 寄存器说明: LTSSM debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ltssm : 32; /* bit[0-31]: LTSSM debug信息。 */
    } reg;
} SOC_USB3OTG_GDBGLTSSM_UNION;
#endif
#define SOC_USB3OTG_GDBGLTSSM_ltssm_START  (0)
#define SOC_USB3OTG_GDBGLTSSM_ltssm_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDBGLNMCC_UNION
 结构说明  : GDBGLNMCC 寄存器结构定义。地址偏移量:0xC168，初值:0x0000，宽度:32
 寄存器说明: LNMCC debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LNMCC_BERC : 9;  /* bit[0-8] : 指示端口误码率信息。 */
        unsigned int  reserved   : 23; /* bit[9-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GDBGLNMCC_UNION;
#endif
#define SOC_USB3OTG_GDBGLNMCC_LNMCC_BERC_START  (0)
#define SOC_USB3OTG_GDBGLNMCC_LNMCC_BERC_END    (8)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GCBGBMU_UNION
 结构说明  : GCBGBMU 寄存器结构定义。地址偏移量:0xC16C，初值:0x0000，宽度:32
 寄存器说明: BMU debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CCU : 4;  /* bit[0-3] : CCU debug信息。 */
        unsigned int  DCU : 4;  /* bit[4-7] : DCU debug信息。 */
        unsigned int  BCU : 24; /* bit[8-31]: BCU debug信息。 */
    } reg;
} SOC_USB3OTG_GCBGBMU_UNION;
#endif
#define SOC_USB3OTG_GCBGBMU_CCU_START  (0)
#define SOC_USB3OTG_GCBGBMU_CCU_END    (3)
#define SOC_USB3OTG_GCBGBMU_DCU_START  (4)
#define SOC_USB3OTG_GCBGBMU_DCU_END    (7)
#define SOC_USB3OTG_GCBGBMU_BCU_START  (8)
#define SOC_USB3OTG_GCBGBMU_BCU_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDBGLSPMUX_UNION
 结构说明  : GDBGLSPMUX 寄存器结构定义。地址偏移量:0xC170，初值:0x0000，宽度:32
 寄存器说明: LSPMUX debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LSPMUX : 32; /* bit[0-31]: LSPMUX debug信息。 */
    } reg;
} SOC_USB3OTG_GDBGLSPMUX_UNION;
#endif
#define SOC_USB3OTG_GDBGLSPMUX_LSPMUX_START  (0)
#define SOC_USB3OTG_GDBGLSPMUX_LSPMUX_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDBGLSP_UNION
 结构说明  : GDBGLSP 寄存器结构定义。地址偏移量:0xC174，初值:0x0000，宽度:32
 寄存器说明: LSP debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LSP : 32; /* bit[0-31]: LSP debug信息。 */
    } reg;
} SOC_USB3OTG_GDBGLSP_UNION;
#endif
#define SOC_USB3OTG_GDBGLSP_LSP_START  (0)
#define SOC_USB3OTG_GDBGLSP_LSP_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDBGEPINFO0_UNION
 结构说明  : GDBGEPINFO0 寄存器结构定义。地址偏移量:0xC178，初值:0x0000，宽度:32
 寄存器说明: endpoint debug寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EpDbg : 32; /* bit[0-31]: endpoint debug信息低32位。 */
    } reg;
} SOC_USB3OTG_GDBGEPINFO0_UNION;
#endif
#define SOC_USB3OTG_GDBGEPINFO0_EpDbg_START  (0)
#define SOC_USB3OTG_GDBGEPINFO0_EpDbg_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDBGEPINFO1_UNION
 结构说明  : GDBGEPINFO1 寄存器结构定义。地址偏移量:0xC17C，初值:0x0000，宽度:32
 寄存器说明: endpoint debug寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EpDbg : 32; /* bit[0-31]: endpoint debug信息高32位。 */
    } reg;
} SOC_USB3OTG_GDBGEPINFO1_UNION;
#endif
#define SOC_USB3OTG_GDBGEPINFO1_EpDbg_START  (0)
#define SOC_USB3OTG_GDBGEPINFO1_EpDbg_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GUSB2PHYCFG_UNION
 结构说明  : GUSB2PHYCFG 寄存器结构定义。地址偏移量:0xC200，初值:0x2400，宽度:32
 寄存器说明: USB2 PHY配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TOutCal           : 3;  /* bit[0-2]  : 超时时间调整。 */
        unsigned int  PHYIf             : 1;  /* bit[3]    : UTMI接口位宽选择。
                                                             0：8bit；
                                                             1：16bit。 */
        unsigned int  reserved_0        : 2;  /* bit[4-5]  : 保留。 */
        unsigned int  SusPHY            : 1;  /* bit[6]    : Suspend USB2.0 PHY。 */
        unsigned int  reserved_1        : 1;  /* bit[7]    : 保留。 */
        unsigned int  EnblSlpM          : 1;  /* bit[8]    : 使能utmi_sleep_n和utmi_l1_suspend_n */
        unsigned int  reserved_2        : 1;  /* bit[9]    : 保留。 */
        unsigned int  USBTrdTim         : 4;  /* bit[10-13]: USB2.0转向时间。
                                                             4'h5：采用16位UTMI接口；
                                                             4'h9：采用8位UTMI接口。 */
        unsigned int  reserved_3        : 16; /* bit[14-29]: 保留。 */
        unsigned int  U2_FREECLK_EXISTS : 1;  /* bit[30]   : USB2.0 PHY是否能提供free clock。
                                                             0：不能；
                                                             1：能。 */
        unsigned int  PHYSoftRst        : 1;  /* bit[31]   : 软复位控制。
                                                             0：不复位；
                                                             1：复位。 */
    } reg;
} SOC_USB3OTG_GUSB2PHYCFG_UNION;
#endif
#define SOC_USB3OTG_GUSB2PHYCFG_TOutCal_START            (0)
#define SOC_USB3OTG_GUSB2PHYCFG_TOutCal_END              (2)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYIf_START              (3)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYIf_END                (3)
#define SOC_USB3OTG_GUSB2PHYCFG_SusPHY_START             (6)
#define SOC_USB3OTG_GUSB2PHYCFG_SusPHY_END               (6)
#define SOC_USB3OTG_GUSB2PHYCFG_EnblSlpM_START           (8)
#define SOC_USB3OTG_GUSB2PHYCFG_EnblSlpM_END             (8)
#define SOC_USB3OTG_GUSB2PHYCFG_USBTrdTim_START          (10)
#define SOC_USB3OTG_GUSB2PHYCFG_USBTrdTim_END            (13)
#define SOC_USB3OTG_GUSB2PHYCFG_U2_FREECLK_EXISTS_START  (30)
#define SOC_USB3OTG_GUSB2PHYCFG_U2_FREECLK_EXISTS_END    (30)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYSoftRst_START         (31)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYSoftRst_END           (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GUSB3PIPECTL_UNION
 结构说明  : GUSB3PIPECTL 寄存器结构定义。地址偏移量:0xC2C0，初值:0x10C8002，宽度:32
 寄存器说明: USB3 PIPE控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ElesticBufferMode   : 1;  /* bit[0]    : Elasticity buffer模式配置。
                                                               1：全空buffer模式；
                                                               0：半满buffer模式。 */
        unsigned int  TxDeemphasis        : 2;  /* bit[1-2]  : 发送信号去加重控制。
                                                               00：6dB去加重；
                                                               01：3.5dB去加重；
                                                               10：无去加重；
                                                               11：保留。 */
        unsigned int  TxMargin            : 3;  /* bit[3-5]  : PIPE TxMargin信号配置。 */
        unsigned int  TxSwing             : 1;  /* bit[6]    : PIPE TxSwing信号配置。 */
        unsigned int  reserved            : 1;  /* bit[7]    : 保留。 */
        unsigned int  RxDetToPolling      : 1;  /* bit[8]    : 从RX_DECT状态进入Polling.LFPS状态延迟控制。
                                                               0：延迟400us；
                                                               1：不延迟。 */
        unsigned int  LFPSFilt            : 1;  /* bit[9]    : LFPS滤波使能。 */
        unsigned int  P3ExSigP2           : 1;  /* bit[10]   : 不经过U3退出握手，直接使PHY进入P2状态。必须配置为0。 */
        unsigned int  P3P2TranOK          : 1;  /* bit[11]   : P2P3状态直接跳转，不需要经过P0状态。必须配置为0。 */
        unsigned int  LFPSP0Algn          : 1;  /* bit[12]   : LFPS信号P0对齐。必须配置为0。 */
        unsigned int  SkipRxDet           : 1;  /* bit[13]   : 跳过接收检测。 */
        unsigned int  AbortRxDetInU2      : 1;  /* bit[14]   : 在U2状态中止接收检测。必须配置为0。 */
        unsigned int  DatWidth            : 2;  /* bit[15-16]: PIPE接口数据位宽。
                                                               00：32bit；
                                                               01：16bit；
                                                               10：8bit；
                                                               11：reserved。 */
        unsigned int  Suspend_en          : 1;  /* bit[17]   : Suspend USB3.0 SS PHY。 */
        unsigned int  DelayP1P2P3En       : 1;  /* bit[18]   : 延迟进入P1/P2/P3状态使能。
                                                               0：使能；
                                                               1：不使能。 */
        unsigned int  DelayP1P2P3         : 3;  /* bit[19-21]: 延迟进入P1/P2/P3状态。 */
        unsigned int  DisRxDetU3RxDet     : 1;  /* bit[22]   : 在U3或者Rx.Det状态，是否使能接收检测。
                                                               0：使能；
                                                               1：不使能。 */
        unsigned int  StartRxdetU3ExDet   : 1;  /* bit[23]   : 使能接收器检测。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  RequestP1P2P3       : 1;  /* bit[24]   : 控制器进入U1/U2/U3状态，则立即请求PHY进入相应的P1/P2/P3状态。
                                                               0：不使能；
                                                               1：使能。
                                                               该位必须配置为1。 */
        unsigned int  U1U2ExitFailToRecov : 1;  /* bit[25]   : U1/U2握手失败状态控制。
                                                               1：如果U1/U2 LFPS握手失败，LTSSM状态机从U1/U2转移到recovery状态，如果recovery失败，LTSSM才转移到SS.Inactive状态；
                                                               0：如果U1/U2 LFPS握手失败，LTSSM状态机从U1/U2转移到SS.Inactive状态。 */
        unsigned int  PingEnhancementEn   : 1;  /* bit[26]   : 延长PING超时时间使能。必须配置为0。
                                                               0：不使能；
                                                               1：使能。 */
        unsigned int  UxExitInPx          : 1;  /* bit[27]   : 低功耗状态退出控制。必须配置为0。
                                                               0：当PHY在P0状态时，控制器退出U1/U2/U3状态；
                                                               1：当PHY在P1/P2/P3状态时，控制器退出相应的U1/U2/U3状态。 */
        unsigned int  DisRxDetP3          : 1;  /* bit[28]   : 在P3状态，是否使能接收检测。
                                                               0：使能；
                                                               1：不使能。 */
        unsigned int  u2SSInactP3ok       : 1;  /* bit[29]   : P3状态控制。
                                                               0：链路处于U2或SS.Inactive，使PHY进入P2状态；
                                                               1：链路处于U2或SS.Inactive，使PHY进入P3状态。 */
        unsigned int  HstPrtCmpl          : 1;  /* bit[30]   : Host端口兼容模式控制。 */
        unsigned int  PHYSoftRst          : 1;  /* bit[31]   : USB3.0 PHY软复位控制。
                                                               0：不复位；
                                                               1：复位。 */
    } reg;
} SOC_USB3OTG_GUSB3PIPECTL_UNION;
#endif
#define SOC_USB3OTG_GUSB3PIPECTL_ElesticBufferMode_START    (0)
#define SOC_USB3OTG_GUSB3PIPECTL_ElesticBufferMode_END      (0)
#define SOC_USB3OTG_GUSB3PIPECTL_TxDeemphasis_START         (1)
#define SOC_USB3OTG_GUSB3PIPECTL_TxDeemphasis_END           (2)
#define SOC_USB3OTG_GUSB3PIPECTL_TxMargin_START             (3)
#define SOC_USB3OTG_GUSB3PIPECTL_TxMargin_END               (5)
#define SOC_USB3OTG_GUSB3PIPECTL_TxSwing_START              (6)
#define SOC_USB3OTG_GUSB3PIPECTL_TxSwing_END                (6)
#define SOC_USB3OTG_GUSB3PIPECTL_RxDetToPolling_START       (8)
#define SOC_USB3OTG_GUSB3PIPECTL_RxDetToPolling_END         (8)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSFilt_START             (9)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSFilt_END               (9)
#define SOC_USB3OTG_GUSB3PIPECTL_P3ExSigP2_START            (10)
#define SOC_USB3OTG_GUSB3PIPECTL_P3ExSigP2_END              (10)
#define SOC_USB3OTG_GUSB3PIPECTL_P3P2TranOK_START           (11)
#define SOC_USB3OTG_GUSB3PIPECTL_P3P2TranOK_END             (11)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSP0Algn_START           (12)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSP0Algn_END             (12)
#define SOC_USB3OTG_GUSB3PIPECTL_SkipRxDet_START            (13)
#define SOC_USB3OTG_GUSB3PIPECTL_SkipRxDet_END              (13)
#define SOC_USB3OTG_GUSB3PIPECTL_AbortRxDetInU2_START       (14)
#define SOC_USB3OTG_GUSB3PIPECTL_AbortRxDetInU2_END         (14)
#define SOC_USB3OTG_GUSB3PIPECTL_DatWidth_START             (15)
#define SOC_USB3OTG_GUSB3PIPECTL_DatWidth_END               (16)
#define SOC_USB3OTG_GUSB3PIPECTL_Suspend_en_START           (17)
#define SOC_USB3OTG_GUSB3PIPECTL_Suspend_en_END             (17)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3En_START        (18)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3En_END          (18)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3_START          (19)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3_END            (21)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetU3RxDet_START      (22)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetU3RxDet_END        (22)
#define SOC_USB3OTG_GUSB3PIPECTL_StartRxdetU3ExDet_START    (23)
#define SOC_USB3OTG_GUSB3PIPECTL_StartRxdetU3ExDet_END      (23)
#define SOC_USB3OTG_GUSB3PIPECTL_RequestP1P2P3_START        (24)
#define SOC_USB3OTG_GUSB3PIPECTL_RequestP1P2P3_END          (24)
#define SOC_USB3OTG_GUSB3PIPECTL_U1U2ExitFailToRecov_START  (25)
#define SOC_USB3OTG_GUSB3PIPECTL_U1U2ExitFailToRecov_END    (25)
#define SOC_USB3OTG_GUSB3PIPECTL_PingEnhancementEn_START    (26)
#define SOC_USB3OTG_GUSB3PIPECTL_PingEnhancementEn_END      (26)
#define SOC_USB3OTG_GUSB3PIPECTL_UxExitInPx_START           (27)
#define SOC_USB3OTG_GUSB3PIPECTL_UxExitInPx_END             (27)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetP3_START           (28)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetP3_END             (28)
#define SOC_USB3OTG_GUSB3PIPECTL_u2SSInactP3ok_START        (29)
#define SOC_USB3OTG_GUSB3PIPECTL_u2SSInactP3ok_END          (29)
#define SOC_USB3OTG_GUSB3PIPECTL_HstPrtCmpl_START           (30)
#define SOC_USB3OTG_GUSB3PIPECTL_HstPrtCmpl_END             (30)
#define SOC_USB3OTG_GUSB3PIPECTL_PHYSoftRst_START           (31)
#define SOC_USB3OTG_GUSB3PIPECTL_PHYSoftRst_END             (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GTXFIFOSIZm_UNION
 结构说明  : GTXFIFOSIZm 寄存器结构定义。地址偏移量:0xC300+m*0x4，初值:0x0000，宽度:32
 寄存器说明: 发送FIFOm大小配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFDep    : 16; /* bit[0-15] : 发送FIFO深度。 */
        unsigned int  TxFStAddr : 16; /* bit[16-31]: 发送FIFO起始地址。 */
    } reg;
} SOC_USB3OTG_GTXFIFOSIZm_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOSIZm_TxFDep_START     (0)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFDep_END       (15)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFStAddr_START  (16)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFStAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GRXFIFOSIZn_UNION
 结构说明  : GRXFIFOSIZn 寄存器结构定义。地址偏移量:0xC380+(n)*0x4，初值:0x0000，宽度:32
 寄存器说明: 接收FIFOn大小配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RxFDep    : 16; /* bit[0-15] : 接收FIFO深度。 */
        unsigned int  RxFStAddr : 16; /* bit[16-31]: 接收FIFO起始地址。 */
    } reg;
} SOC_USB3OTG_GRXFIFOSIZn_UNION;
#endif
#define SOC_USB3OTG_GRXFIFOSIZn_RxFDep_START     (0)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFDep_END       (15)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFStAddr_START  (16)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFStAddr_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GEVNTADRLo_UNION
 结构说明  : GEVNTADRLo 寄存器结构定义。地址偏移量:0xC400，初值:0x0000，宽度:32
 寄存器说明: 事件buffer地址低32位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EvntAdrLo : 32; /* bit[0-31]: 事件buffer地址低32位。 */
    } reg;
} SOC_USB3OTG_GEVNTADRLo_UNION;
#endif
#define SOC_USB3OTG_GEVNTADRLo_EvntAdrLo_START  (0)
#define SOC_USB3OTG_GEVNTADRLo_EvntAdrLo_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GEVNTADRHi_UNION
 结构说明  : GEVNTADRHi 寄存器结构定义。地址偏移量:0xC404，初值:0x0000，宽度:32
 寄存器说明: 事件buffer地址高32位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EvntAdrHi : 32; /* bit[0-31]: 事件buffer地址高32位。 */
    } reg;
} SOC_USB3OTG_GEVNTADRHi_UNION;
#endif
#define SOC_USB3OTG_GEVNTADRHi_EvntAdrHi_START  (0)
#define SOC_USB3OTG_GEVNTADRHi_EvntAdrHi_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GEVNTSIZ_UNION
 结构说明  : GEVNTSIZ 寄存器结构定义。地址偏移量:0xC408，初值:0x0000，宽度:32
 寄存器说明: 事件buffer大小寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EVNTSiz     : 16; /* bit[0-15] : 事件buffer大小，以字节为单位，最小为32字节。 */
        unsigned int  reserved    : 15; /* bit[16-30]: 保留。 */
        unsigned int  EvntIntMask : 1;  /* bit[31]   : 事件中断屏蔽位。设置为1，则中断不会产生。 */
    } reg;
} SOC_USB3OTG_GEVNTSIZ_UNION;
#endif
#define SOC_USB3OTG_GEVNTSIZ_EVNTSiz_START      (0)
#define SOC_USB3OTG_GEVNTSIZ_EVNTSiz_END        (15)
#define SOC_USB3OTG_GEVNTSIZ_EvntIntMask_START  (31)
#define SOC_USB3OTG_GEVNTSIZ_EvntIntMask_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GEVNTCOUNT_UNION
 结构说明  : GEVNTCOUNT 寄存器结构定义。地址偏移量:0xC40C，初值:0x0000，宽度:32
 寄存器说明: 事件数目寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EVNTCount : 16; /* bit[0-15] : 事件数目。
                                                     对该寄存器进行读操作，返回事件buffer内剩余事件个数；
                                                     对该寄存器进行写操作，硬件将剩余事件个数减去软件写入的值。
                                                     该域不为0会触发中断。 */
        unsigned int  reserved  : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GEVNTCOUNT_UNION;
#endif
#define SOC_USB3OTG_GEVNTCOUNT_EVNTCount_START  (0)
#define SOC_USB3OTG_GEVNTCOUNT_EVNTCount_END    (15)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GTXFIFOPRIDEV_UNION
 结构说明  : GTXFIFOPRIDEV 寄存器结构定义。地址偏移量:0xC610，初值:0x0000，宽度:32
 寄存器说明: Device发送FIFO优先级
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFifoPri : 16; /* bit[0-15] : 发送FIFO优先级。用于配置DMA仲裁的优先级。每bit对应一个端点发送FIFO的优先级。
                                                     0：低优先级；
                                                     1：高优先级。 */
        unsigned int  reserved  : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GTXFIFOPRIDEV_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOPRIDEV_TxFifoPri_START  (0)
#define SOC_USB3OTG_GTXFIFOPRIDEV_TxFifoPri_END    (15)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GTXFIFOPRIHST_UNION
 结构说明  : GTXFIFOPRIHST 寄存器结构定义。地址偏移量:0xC618，初值:0x0000，宽度:32
 寄存器说明: Host发送FIFO优先级
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFifoPri : 3;  /* bit[0-2] : 发送FIFO优先级。用于配置DMA仲裁的优先级。Bit[2]对应SuperSpeed端口发送FIFO，bit[1]对应HighSpeed端口发送FIFO，bit[0]对应FullSpeed/LowSpeed端口发送FIFO。
                                                    0：低优先级；
                                                    1：高优先级。 */
        unsigned int  reserved  : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GTXFIFOPRIHST_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOPRIHST_TxFifoPri_START  (0)
#define SOC_USB3OTG_GTXFIFOPRIHST_TxFifoPri_END    (2)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GRXFIFOPRIHST_UNION
 结构说明  : GRXFIFOPRIHST 寄存器结构定义。地址偏移量:0xC61C，初值:0x0000，宽度:32
 寄存器说明: Host接收FIFO优先级
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RxFifoPri : 3;  /* bit[0-2] : 接收FIFO优先级。用于配置DMA仲裁的优先级。Bit[2]对应SuperSpeed端口发送FIFO，bit[1]对应HighSpeed端口发送FIFO，bit[0]对应FullSpeed/LowSpeed端口发送FIFO。
                                                    0：低优先级；
                                                    1：高优先级。 */
        unsigned int  reserved  : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GRXFIFOPRIHST_UNION;
#endif
#define SOC_USB3OTG_GRXFIFOPRIHST_RxFifoPri_START  (0)
#define SOC_USB3OTG_GRXFIFOPRIHST_RxFifoPri_END    (2)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GDMAHLRATIO_UNION
 结构说明  : GDMAHLRATIO 寄存器结构定义。地址偏移量:0xC624，初值:0x0404，宽度:32
 寄存器说明: Host高低优先级权重配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFifoRatio : 5;  /* bit[0-4]  : 发送FIFO配置。 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  RxFifoRatio : 5;  /* bit[8-12] : 接收FIFO配置。SuperSpeed端口与USB2.0端口进行仲裁时，采用Roud-Robin。该域用于配置轮询比例。 */
        unsigned int  reserved_1  : 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_USB3OTG_GDMAHLRATIO_UNION;
#endif
#define SOC_USB3OTG_GDMAHLRATIO_TxFifoRatio_START  (0)
#define SOC_USB3OTG_GDMAHLRATIO_TxFifoRatio_END    (4)
#define SOC_USB3OTG_GDMAHLRATIO_RxFifoRatio_START  (8)
#define SOC_USB3OTG_GDMAHLRATIO_RxFifoRatio_END    (12)


/*****************************************************************************
 结构名    : SOC_USB3OTG_GFLADJ_UNION
 结构说明  : GFLADJ 寄存器结构定义。地址偏移量:0xC630，初值:0x8C80C8A0，宽度:32
 寄存器说明: 帧长度调整寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fladj : 32; /* bit[0-31]: 帧长度调整寄存器。 */
    } reg;
} SOC_USB3OTG_GFLADJ_UNION;
#endif
#define SOC_USB3OTG_GFLADJ_fladj_START  (0)
#define SOC_USB3OTG_GFLADJ_fladj_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DCFG_UNION
 结构说明  : DCFG 寄存器结构定义。地址偏移量:0xC700，初值:0x80000，宽度:32
 寄存器说明: device配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DevSpd         : 3;  /* bit[0-2]  : Device速度。软件配置device能支持的最高枚举速度。
                                                          000：High Speed；
                                                          001：Full Speed；
                                                          100：Super Speed。
                                                          Others：reserved。 */
        unsigned int  DevAddr        : 7;  /* bit[3-9]  : device地址。
                                                          软件必须在收到SetAddress请求后修改该域，在收到USB复位后，将该域清零。 */
        unsigned int  reserved_0     : 2;  /* bit[10-11]: 保留。 */
        unsigned int  IntrNum        : 5;  /* bit[12-16]: 非端点相关的中断数目。 */
        unsigned int  NumP           : 5;  /* bit[17-21]: 接收包个数，用于填充ACK包的NumP域。可以根据接收FIFO大小，描述符中buffer的大小，系统的latency决定该域。 */
        unsigned int  LPMCap         : 1;  /* bit[22]   : LPM使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  IgnoreStreamPP : 1;  /* bit[23]   : 忽略PP(Packets Pending)。仅对支持stream的bulk端点有效。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_USB3OTG_DCFG_UNION;
#endif
#define SOC_USB3OTG_DCFG_DevSpd_START          (0)
#define SOC_USB3OTG_DCFG_DevSpd_END            (2)
#define SOC_USB3OTG_DCFG_DevAddr_START         (3)
#define SOC_USB3OTG_DCFG_DevAddr_END           (9)
#define SOC_USB3OTG_DCFG_IntrNum_START         (12)
#define SOC_USB3OTG_DCFG_IntrNum_END           (16)
#define SOC_USB3OTG_DCFG_NumP_START            (17)
#define SOC_USB3OTG_DCFG_NumP_END              (21)
#define SOC_USB3OTG_DCFG_LPMCap_START          (22)
#define SOC_USB3OTG_DCFG_LPMCap_END            (22)
#define SOC_USB3OTG_DCFG_IgnoreStreamPP_START  (23)
#define SOC_USB3OTG_DCFG_IgnoreStreamPP_END    (23)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DCTL_UNION
 结构说明  : DCTL 寄存器结构定义。地址偏移量:0xC704，初值:0x0000，宽度:32
 寄存器说明: device控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : 保留。 */
        unsigned int  TstCtl          : 4;  /* bit[1-4]  : 测试模式控制：
                                                           0000：测试模式不使能
                                                           0001：Test_J
                                                           0010: Test_K
                                                           0011: Test_SE0_NAK
                                                           0100: Test Packet
                                                           0101: Test_Force_enable
                                                           others:reserved */
        unsigned int  ULstChngReq     : 4;  /* bit[5-8]  : 链路状态变化请求。
                                                           对于SS：
                                                           0000： No Action
                                                           0100: SS.Disabled
                                                           0101: Rx.Detect
                                                           0110: SS.Inactive
                                                           1000: Recovery
                                                           1010: Compliance
                                                           1011: Loopback
                                                           others: reserved
                                                           对于HS/FS/LS：
                                                           1000： Remote wakeup request
                                                           others：reserved */
        unsigned int  AcceptU1Ena     : 1;  /* bit[9]    : 接受U1初始化。 */
        unsigned int  InitU1Ena       : 1;  /* bit[10]   : 初始化U1使能。 */
        unsigned int  AcceptU2Ena     : 1;  /* bit[11]   : 接受U2使能。 */
        unsigned int  InitU2Ena       : 1;  /* bit[12]   : 初始化U2使能。 */
        unsigned int  reserved_1      : 3;  /* bit[13-15]: 保留。 */
        unsigned int  CSS             : 1;  /* bit[16]   : Controller Save State */
        unsigned int  CRS             : 1;  /* bit[17]   : Controller Restore State */
        unsigned int  L1HibernationEn : 1;  /* bit[18]   : L1状态冬眠使能。
                                                           0：不使能；
                                                           1：使能。 */
        unsigned int  KeepConnect     : 1;  /* bit[19]   : 保持连接控制。当设置为1，即使RunStop配置为0，也与Host保持连接状态。 */
        unsigned int  AppL1Res        : 4;  /* bit[20-23]: 当LPM Errata不使能时：
                                                           bit[23]LPM响应。
                                                           如果LPMCap=0，则控制器不返回任何响应。
                                                           如果LPMCap=1：
                                                           0：成功收到LPM包之后，根据发送FIFO状态和OUT端点状态返回ACK包。
                                                           1：成功收到LPM包之后返回ACK包。
                                                           Bit[22:20]保留。
                                                           
                                                           当LPM Errate使能时：
                                                           bit[23:20]LPM NYET响应水线。
                                                           如果LPMCap=0，则控制器不返回任何响应。
                                                           如果LPMCap=1，当满足以下条件时返回ACK：
                                                           （1）没有PID和CRC5错误；
                                                           （2）接收到有效的bLinkState；
                                                           （3）发送FIFO为空，且out端点空闲；
                                                           （4）接收到的BESL小于等于LPM_NYET_thres[3:0]。 */
        unsigned int  HIRD_Thres      : 5;  /* bit[24-28]: HIRD水线。
                                                           同时满足一下条件，控制器同时将输出信号utmi_l1_suspend_n和utmi_sleep_n置为有效：
                                                           ■HIRD值大于或等于HIRD_Thres[3:0]
                                                           ■HIRD_Thres[4]=1
                                                           满足以下条件之一，控制器将输出信号utmi_sleep_n置为有效：
                                                           ■HIRD值小于HIRD_Thres[3:0]
                                                           ■HIRD_Thres[4]=0
                                                           HIRD_Thres[3:0]含义
                                                           0000 60us
                                                           0001 135us
                                                           0010 210us
                                                           0011 285us
                                                           0100 360us
                                                           0101 435us
                                                           0110 510us
                                                           0111 585us
                                                           1000 660us
                                                           1001 735us
                                                           1010 810us
                                                           1011 885us
                                                           1100 960us
                                                           1101－1111 Invalid */
        unsigned int  reserved_2      : 1;  /* bit[29]   : 保留。 */
        unsigned int  CSftRst         : 1;  /* bit[30]   : 控制器软复位操作。
                                                           0：不复位；
                                                           1：复位。 */
        unsigned int  RunStop         : 1;  /* bit[31]   : Run/Stop。写1启动控制器操作，写0停止控制器操作。 */
    } reg;
} SOC_USB3OTG_DCTL_UNION;
#endif
#define SOC_USB3OTG_DCTL_TstCtl_START           (1)
#define SOC_USB3OTG_DCTL_TstCtl_END             (4)
#define SOC_USB3OTG_DCTL_ULstChngReq_START      (5)
#define SOC_USB3OTG_DCTL_ULstChngReq_END        (8)
#define SOC_USB3OTG_DCTL_AcceptU1Ena_START      (9)
#define SOC_USB3OTG_DCTL_AcceptU1Ena_END        (9)
#define SOC_USB3OTG_DCTL_InitU1Ena_START        (10)
#define SOC_USB3OTG_DCTL_InitU1Ena_END          (10)
#define SOC_USB3OTG_DCTL_AcceptU2Ena_START      (11)
#define SOC_USB3OTG_DCTL_AcceptU2Ena_END        (11)
#define SOC_USB3OTG_DCTL_InitU2Ena_START        (12)
#define SOC_USB3OTG_DCTL_InitU2Ena_END          (12)
#define SOC_USB3OTG_DCTL_CSS_START              (16)
#define SOC_USB3OTG_DCTL_CSS_END                (16)
#define SOC_USB3OTG_DCTL_CRS_START              (17)
#define SOC_USB3OTG_DCTL_CRS_END                (17)
#define SOC_USB3OTG_DCTL_L1HibernationEn_START  (18)
#define SOC_USB3OTG_DCTL_L1HibernationEn_END    (18)
#define SOC_USB3OTG_DCTL_KeepConnect_START      (19)
#define SOC_USB3OTG_DCTL_KeepConnect_END        (19)
#define SOC_USB3OTG_DCTL_AppL1Res_START         (20)
#define SOC_USB3OTG_DCTL_AppL1Res_END           (23)
#define SOC_USB3OTG_DCTL_HIRD_Thres_START       (24)
#define SOC_USB3OTG_DCTL_HIRD_Thres_END         (28)
#define SOC_USB3OTG_DCTL_CSftRst_START          (30)
#define SOC_USB3OTG_DCTL_CSftRst_END            (30)
#define SOC_USB3OTG_DCTL_RunStop_START          (31)
#define SOC_USB3OTG_DCTL_RunStop_END            (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DEVNTEN_UNION
 结构说明  : DEVNTEN 寄存器结构定义。地址偏移量:0xC708，初值:0x0000，宽度:32
 寄存器说明: device事件使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DisconnEvtEn        : 1;  /* bit[0]    : 断开连接事件使能。 */
        unsigned int  USBRstEn            : 1;  /* bit[1]    : USB复位事件使能。 */
        unsigned int  ConnectDoneEn       : 1;  /* bit[2]    : 连接完成事件使能。 */
        unsigned int  ULStsChngEn         : 1;  /* bit[3]    : 链路状态变化请求事件使能。 */
        unsigned int  WkUpEvntEn          : 1;  /* bit[4]    : 检测到Resume/Remote Wakeup事件使能。 */
        unsigned int  HibernationReqEvtEn : 1;  /* bit[5]    : Hibernation请求事件使能。 */
        unsigned int  U3L2L1SuspEn        : 1;  /* bit[6]    : U3/L2-L1 suspend事件。 */
        unsigned int  SofEn               : 1;  /* bit[7]    : SOF事件使能。 */
        unsigned int  reserved_0          : 1;  /* bit[8]    : 保留。 */
        unsigned int  ErrticErrEn         : 1;  /* bit[9]    : 不确定错误事件使能。 */
        unsigned int  reserved_1          : 2;  /* bit[10-11]: 保留。 */
        unsigned int  VndrDevTstRcvedEn   : 1;  /* bit[12]   : 收到LMP事件。 */
        unsigned int  reserved_2          : 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_USB3OTG_DEVNTEN_UNION;
#endif
#define SOC_USB3OTG_DEVNTEN_DisconnEvtEn_START         (0)
#define SOC_USB3OTG_DEVNTEN_DisconnEvtEn_END           (0)
#define SOC_USB3OTG_DEVNTEN_USBRstEn_START             (1)
#define SOC_USB3OTG_DEVNTEN_USBRstEn_END               (1)
#define SOC_USB3OTG_DEVNTEN_ConnectDoneEn_START        (2)
#define SOC_USB3OTG_DEVNTEN_ConnectDoneEn_END          (2)
#define SOC_USB3OTG_DEVNTEN_ULStsChngEn_START          (3)
#define SOC_USB3OTG_DEVNTEN_ULStsChngEn_END            (3)
#define SOC_USB3OTG_DEVNTEN_WkUpEvntEn_START           (4)
#define SOC_USB3OTG_DEVNTEN_WkUpEvntEn_END             (4)
#define SOC_USB3OTG_DEVNTEN_HibernationReqEvtEn_START  (5)
#define SOC_USB3OTG_DEVNTEN_HibernationReqEvtEn_END    (5)
#define SOC_USB3OTG_DEVNTEN_U3L2L1SuspEn_START         (6)
#define SOC_USB3OTG_DEVNTEN_U3L2L1SuspEn_END           (6)
#define SOC_USB3OTG_DEVNTEN_SofEn_START                (7)
#define SOC_USB3OTG_DEVNTEN_SofEn_END                  (7)
#define SOC_USB3OTG_DEVNTEN_ErrticErrEn_START          (9)
#define SOC_USB3OTG_DEVNTEN_ErrticErrEn_END            (9)
#define SOC_USB3OTG_DEVNTEN_VndrDevTstRcvedEn_START    (12)
#define SOC_USB3OTG_DEVNTEN_VndrDevTstRcvedEn_END      (12)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DSTS_UNION
 结构说明  : DSTS 寄存器结构定义。地址偏移量:0xC70C，初值:0x0000，宽度:32
 寄存器说明: Device状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ConnectSpd  : 3;  /* bit[0-2]  : 连接速度。
                                                       100：Super Speed；
                                                       000：High Speed；
                                                       001：Full Speed；
                                                       010：LowSpeed；
                                                       011：Full Speed。 */
        unsigned int  SOFFN       : 14; /* bit[3-16] : 帧/微帧号。 */
        unsigned int  RxFIFOEmpty : 1;  /* bit[17]   : 接收FIFO空状态指示。 */
        unsigned int  USBLnkSts   : 4;  /* bit[18-21]: 链路状态。
                                                       对于SS：
                                                       LTSSM状态机状态：
                                                       0000:U0
                                                       0001:U1
                                                       0010:U2
                                                       0011:U3
                                                       0100:SS.Disable
                                                       0101:Rx.Detect
                                                       0110:SS.Inactive
                                                       0111:Poll
                                                       1000:Recovery
                                                       1001:HotReset
                                                       1010:Compliance
                                                       1011:Loopback
                                                       1111:Resume/Reset
                                                       对于HS/FS/LS：
                                                       0000:On state
                                                       0010:Sleep state
                                                       0011:Suspend state
                                                       0100:Disconnect state
                                                       0101:Early suspend state
                                                       1110:Reset */
        unsigned int  DevCtrlHlt  : 1;  /* bit[22]   : 控制器停止。 */
        unsigned int  CoreIdle    : 1;  /* bit[23]   : Idle状态指示。 */
        unsigned int  SSS         : 1;  /* bit[24]   : Save状态指示。 */
        unsigned int  RSS         : 1;  /* bit[25]   : Restore状态指示。 */
        unsigned int  reserved_0  : 2;  /* bit[26-27]: 保留。 */
        unsigned int  SRE         : 1;  /* bit[28]   : Save/Store错误。 */
        unsigned int  DCNRD       : 1;  /* bit[29]   : 控制器没有准备好。
                                                       指示退出hibernation没有完成。 */
        unsigned int  reserved_1  : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_USB3OTG_DSTS_UNION;
#endif
#define SOC_USB3OTG_DSTS_ConnectSpd_START   (0)
#define SOC_USB3OTG_DSTS_ConnectSpd_END     (2)
#define SOC_USB3OTG_DSTS_SOFFN_START        (3)
#define SOC_USB3OTG_DSTS_SOFFN_END          (16)
#define SOC_USB3OTG_DSTS_RxFIFOEmpty_START  (17)
#define SOC_USB3OTG_DSTS_RxFIFOEmpty_END    (17)
#define SOC_USB3OTG_DSTS_USBLnkSts_START    (18)
#define SOC_USB3OTG_DSTS_USBLnkSts_END      (21)
#define SOC_USB3OTG_DSTS_DevCtrlHlt_START   (22)
#define SOC_USB3OTG_DSTS_DevCtrlHlt_END     (22)
#define SOC_USB3OTG_DSTS_CoreIdle_START     (23)
#define SOC_USB3OTG_DSTS_CoreIdle_END       (23)
#define SOC_USB3OTG_DSTS_SSS_START          (24)
#define SOC_USB3OTG_DSTS_SSS_END            (24)
#define SOC_USB3OTG_DSTS_RSS_START          (25)
#define SOC_USB3OTG_DSTS_RSS_END            (25)
#define SOC_USB3OTG_DSTS_SRE_START          (28)
#define SOC_USB3OTG_DSTS_SRE_END            (28)
#define SOC_USB3OTG_DSTS_DCNRD_START        (29)
#define SOC_USB3OTG_DSTS_DCNRD_END          (29)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DGCMDPAR_UNION
 结构说明  : DGCMDPAR 寄存器结构定义。地址偏移量:0xC710，初值:0x0000，宽度:32
 寄存器说明: 一般命令参数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter : 32; /* bit[0-31]: 命令参数。 */
    } reg;
} SOC_USB3OTG_DGCMDPAR_UNION;
#endif
#define SOC_USB3OTG_DGCMDPAR_parameter_START  (0)
#define SOC_USB3OTG_DGCMDPAR_parameter_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DGCMD_UNION
 结构说明  : DGCMD 寄存器结构定义。地址偏移量:0xC714，初值:0x0000，宽度:32
 寄存器说明: 一般命令控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CmdTyp   : 8;  /* bit[0-7]  : 命令类型。
                                                    02h：设置周期参数
                                                    04h：设置便签buffer地址低32位
                                                    05h：设置便签buffer地址高32位
                                                    07h：发送device notification
                                                    08h：选择的FIFO Flush操作
                                                    0Ah：所有的FIFO Flush操作
                                                    0Ch：设置端点NRDY
                                                    10h：Soc总线环回测试 */
        unsigned int  CmdIOC   : 1;  /* bit[8]    : 命令完成中断使能。配置为1，则命令完成之后产生命令完成中断事件。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  reserved_0: 1;  /* bit[9]    : 保留。 */
        unsigned int  CmdAct   : 1;  /* bit[10]   : 命令激活。
                                                    软件写1，控制器开始执行命令。命令完成后该bit自动清零。 */
        unsigned int  reserved_1: 4;  /* bit[11-14]: 保留。 */
        unsigned int  CmdSts   : 1;  /* bit[15]   : 命令状态。
                                                    0：命令成功；
                                                    1：命令错误。 */
        unsigned int  reserved_2: 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_USB3OTG_DGCMD_UNION;
#endif
#define SOC_USB3OTG_DGCMD_CmdTyp_START    (0)
#define SOC_USB3OTG_DGCMD_CmdTyp_END      (7)
#define SOC_USB3OTG_DGCMD_CmdIOC_START    (8)
#define SOC_USB3OTG_DGCMD_CmdIOC_END      (8)
#define SOC_USB3OTG_DGCMD_CmdAct_START    (10)
#define SOC_USB3OTG_DGCMD_CmdAct_END      (10)
#define SOC_USB3OTG_DGCMD_CmdSts_START    (15)
#define SOC_USB3OTG_DGCMD_CmdSts_END      (15)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DALEPENA_UNION
 结构说明  : DALEPENA 寄存器结构定义。地址偏移量:0xC720，初值:0x0000，宽度:32
 寄存器说明: 端点激活寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  USBActEp : 32; /* bit[0-31]: 每bit对应一个端点。
                                                   Bit[0]:EP0-OUT
                                                   bit[1]:EP0_IN
                                                   bit[2]:EP1-OUT
                                                   bit[3]:EP2-IN
                                                   ……
                                                   bit[31]:EP15-IN
                                                   0：端点没有激活；
                                                   1：端点激活。 */
    } reg;
} SOC_USB3OTG_DALEPENA_UNION;
#endif
#define SOC_USB3OTG_DALEPENA_USBActEp_START  (0)
#define SOC_USB3OTG_DALEPENA_USBActEp_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DEPCMDPAR2m_UNION
 结构说明  : DEPCMDPAR2m 寄存器结构定义。地址偏移量:0xC800+m*0x10，初值:0x0000，宽度:32
 寄存器说明: 端点m命令参数寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter2 : 32; /* bit[0-31]: 参数寄存器。 */
    } reg;
} SOC_USB3OTG_DEPCMDPAR2m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR2m_parameter2_START  (0)
#define SOC_USB3OTG_DEPCMDPAR2m_parameter2_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DEPCMDPAR1m_UNION
 结构说明  : DEPCMDPAR1m 寄存器结构定义。地址偏移量:0xC804+m*0x10，初值:0x0000，宽度:32
 寄存器说明: 端点m命令参数寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter1 : 32; /* bit[0-31]: 参数寄存器。 */
    } reg;
} SOC_USB3OTG_DEPCMDPAR1m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR1m_parameter1_START  (0)
#define SOC_USB3OTG_DEPCMDPAR1m_parameter1_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DEPCMDPAR0m_UNION
 结构说明  : DEPCMDPAR0m 寄存器结构定义。地址偏移量:0xC808+m*0x10，初值:0x0000，宽度:32
 寄存器说明: 端点m命令参数寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter0 : 32; /* bit[0-31]: 参数寄存器。 */
    } reg;
} SOC_USB3OTG_DEPCMDPAR0m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR0m_parameter0_START  (0)
#define SOC_USB3OTG_DEPCMDPAR0m_parameter0_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_DEPCMDm_UNION
 结构说明  : DEPCMDm 寄存器结构定义。地址偏移量:0xC80C+m*0x10，初值:0x0000，宽度:32
 寄存器说明: 端点m命令寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CmdTyp        : 4;  /* bit[0-3]  : 命令类型。配置软件请求控制器完成的操作类型。
                                                         0001：端点配置；
                                                         0010: 传输源配置；
                                                         0011: 获取端点状态；
                                                         0100: 设置STALL；
                                                         0101: 清除STALL；
                                                         0110: 启动传输；
                                                         0111: 更新传输；
                                                         1000: 结束传输；
                                                         1001: 启动新的配置；
                                                         others：reserved。 */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : 保留。 */
        unsigned int  CmdIOC        : 1;  /* bit[8]    : 命令完成中断使能。 */
        unsigned int  reserved_1    : 1;  /* bit[9]    : 保留。 */
        unsigned int  CmdAct        : 1;  /* bit[10]   : 命令激活。
                                                         软件写1，控制器开始执行命令。命令完成后该bit自动清零。 */
        unsigned int  HiPri_ForceRM : 1;  /* bit[11]   : HighPriority/ForceRM。 */
        unsigned int  CmdStatus     : 4;  /* bit[12-15]: 命令完成状态。 */
        unsigned int  CommandParam  : 16; /* bit[16-31]: 进行写操作时，该域为命令参数。
                                                         对于非ISO端点的Start Transfer命令：stream ID。
                                                         对于ISO端点的Start Transfer命令：StartMicroFrameNum。
                                                         对于Update Transfer，End Transfer和StartNew Configuration命令：[22:16]为Transfer Resource Index
                                                         
                                                         对于读操作，该域为事件参数。 */
    } reg;
} SOC_USB3OTG_DEPCMDm_UNION;
#endif
#define SOC_USB3OTG_DEPCMDm_CmdTyp_START         (0)
#define SOC_USB3OTG_DEPCMDm_CmdTyp_END           (3)
#define SOC_USB3OTG_DEPCMDm_CmdIOC_START         (8)
#define SOC_USB3OTG_DEPCMDm_CmdIOC_END           (8)
#define SOC_USB3OTG_DEPCMDm_CmdAct_START         (10)
#define SOC_USB3OTG_DEPCMDm_CmdAct_END           (10)
#define SOC_USB3OTG_DEPCMDm_HiPri_ForceRM_START  (11)
#define SOC_USB3OTG_DEPCMDm_HiPri_ForceRM_END    (11)
#define SOC_USB3OTG_DEPCMDm_CmdStatus_START      (12)
#define SOC_USB3OTG_DEPCMDm_CmdStatus_END        (15)
#define SOC_USB3OTG_DEPCMDm_CommandParam_START   (16)
#define SOC_USB3OTG_DEPCMDm_CommandParam_END     (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_OCFG_UNION
 结构说明  : OCFG 寄存器结构定义。地址偏移量:0xCC00，初值:0x0000，宽度:32
 寄存器说明: OTG配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SRPCap          : 1;  /* bit[0]   : SRP使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  HNPCap          : 1;  /* bit[1]   : RSP/HNP使能。
                                                          0：不使能；
                                                          1：使能。 */
        unsigned int  OTGVersion      : 1;  /* bit[2]   : 必须配置为0。 */
        unsigned int  OTGSftRstMsk    : 1;  /* bit[3]   : OTG软复位屏蔽寄存器。
                                                          0：The xHCI-based USBCMD.HCRST and DCTL.CSftRst will reset the OTG logic of the core
                                                          1: The xHCI-based USBCMD.HCRST and DCTL.CSftRst will be masked form the OTG logic of the core。
                                                          当GCTL.PrtCapDir=2'b11时，该bit必须配置为1，否则配置为0。 */
        unsigned int  OTGHibDisMsk    : 1;  /* bit[4]   : 冬眠过程中屏蔽OTG事件。
                                                          0：在Run/Stop配置为1之前，不产生OTG事件；
                                                          1：不屏蔽。
                                                          正常功能该bit必须配置为0。 */
        unsigned int  DisPrtPwrCutOff : 1;  /* bit[5]   : 去使能端口VBUS自动关断。
                                                          0：如果A_WAIT_BCON超时，控制器自动关断VBUS；
                                                          1：不自动关断VBUS。 */
        unsigned int  reserved        : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_USB3OTG_OCFG_UNION;
#endif
#define SOC_USB3OTG_OCFG_SRPCap_START           (0)
#define SOC_USB3OTG_OCFG_SRPCap_END             (0)
#define SOC_USB3OTG_OCFG_HNPCap_START           (1)
#define SOC_USB3OTG_OCFG_HNPCap_END             (1)
#define SOC_USB3OTG_OCFG_OTGVersion_START       (2)
#define SOC_USB3OTG_OCFG_OTGVersion_END         (2)
#define SOC_USB3OTG_OCFG_OTGSftRstMsk_START     (3)
#define SOC_USB3OTG_OCFG_OTGSftRstMsk_END       (3)
#define SOC_USB3OTG_OCFG_OTGHibDisMsk_START     (4)
#define SOC_USB3OTG_OCFG_OTGHibDisMsk_END       (4)
#define SOC_USB3OTG_OCFG_DisPrtPwrCutOff_START  (5)
#define SOC_USB3OTG_OCFG_DisPrtPwrCutOff_END    (5)


/*****************************************************************************
 结构名    : SOC_USB3OTG_OCTL_UNION
 结构说明  : OCTL 寄存器结构定义。地址偏移量:0xCC04，初值:0x0000，宽度:32
 寄存器说明: OTG控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HstSetHNPEn    : 1;  /* bit[0]   : host RSP/HNP使能。
                                                         0：不使能；
                                                         1：使能。 */
        unsigned int  DevSetHNPEn    : 1;  /* bit[1]   : device RSP/HNP使能。
                                                         0：不使能；
                                                         1：使能。 */
        unsigned int  TermSelDLPulse : 1;  /* bit[2]   : 在SRP过程中，配置该bit在数据线上产生脉冲。
                                                         0：用utmi_txvalid产生脉冲；
                                                         1：用utmi_termsel产生脉冲。 */
        unsigned int  SesReq         : 1;  /* bit[3]   : 会话请求。
                                                         0：无请求；
                                                         1：有请求。 */
        unsigned int  HNPReq         : 1;  /* bit[4]   : HNP请求。
                                                         0：无请求；
                                                         1：有请求。 */
        unsigned int  PrtPwrCtl      : 1;  /* bit[5]   : 端口电源控制。
                                                         作为A-device时，配置该bit驱动VBUS。
                                                         0：VBUS不使能；
                                                         1：VBUS使能。 */
        unsigned int  PeriMode       : 1;  /* bit[6]   : 模式配置。
                                                         0：Host模式；
                                                         1：Device模式。 */
        unsigned int  OTG3_GOERR     : 1;  /* bit[7]   : 配置该bit，LTSSM状态机跳转到错误状态。操作完成该bit自动清零。当TRSP_ACK_ERR, TRSP_CNF_ERR或者TRSP_WRST_ERR超时发生，软件必须配置该bit为1。 */
        unsigned int  reserved       : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_USB3OTG_OCTL_UNION;
#endif
#define SOC_USB3OTG_OCTL_HstSetHNPEn_START     (0)
#define SOC_USB3OTG_OCTL_HstSetHNPEn_END       (0)
#define SOC_USB3OTG_OCTL_DevSetHNPEn_START     (1)
#define SOC_USB3OTG_OCTL_DevSetHNPEn_END       (1)
#define SOC_USB3OTG_OCTL_TermSelDLPulse_START  (2)
#define SOC_USB3OTG_OCTL_TermSelDLPulse_END    (2)
#define SOC_USB3OTG_OCTL_SesReq_START          (3)
#define SOC_USB3OTG_OCTL_SesReq_END            (3)
#define SOC_USB3OTG_OCTL_HNPReq_START          (4)
#define SOC_USB3OTG_OCTL_HNPReq_END            (4)
#define SOC_USB3OTG_OCTL_PrtPwrCtl_START       (5)
#define SOC_USB3OTG_OCTL_PrtPwrCtl_END         (5)
#define SOC_USB3OTG_OCTL_PeriMode_START        (6)
#define SOC_USB3OTG_OCTL_PeriMode_END          (6)
#define SOC_USB3OTG_OCTL_OTG3_GOERR_START      (7)
#define SOC_USB3OTG_OCTL_OTG3_GOERR_END        (7)


/*****************************************************************************
 结构名    : SOC_USB3OTG_OEVNT_UNION
 结构说明  : OEVNT 寄存器结构定义。地址偏移量:0xCC08，初值:0x0000，宽度:32
 寄存器说明: OTG事件寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  OEVNTError            : 1;  /* bit[0]    : OTG事件错误。 */
        unsigned int  SesReqSts             : 1;  /* bit[1]    : 会话请求状态。 */
        unsigned int  HstNegStss            : 1;  /* bit[2]    : HNP状态。
                                                                 0：HNP失败；
                                                                 1：HNP成功。 */
        unsigned int  BSesVld               : 1;  /* bit[3]    : B-Session状态。
                                                                 0：无效；
                                                                 1：有效。 */
        unsigned int  reserved_0            : 4;  /* bit[4-7]  : 保留。 */
        unsigned int  OTGBVbsChg            : 1;  /* bit[8]    : 当前模式为B-device模式，VBUS状态变化事件。 */
        unsigned int  OTGBSrpChg            : 1;  /* bit[9]    : 当前模式为B-device模式，SRP状态变化事件。 */
        unsigned int  OTGBHnpChg            : 1;  /* bit[10]   : 当前模式为B-device模式，HNP状态变化事件。 */
        unsigned int  OTGBDevBHostEndEvnt   : 1;  /* bit[11]   : 当前模式为B-device模式，B-device完成host角色事件。 */
        unsigned int  reserved_1            : 4;  /* bit[12-15]: 保留。 */
        unsigned int  OTGADevSessEndDetEvnt : 1;  /* bit[16]   : 会话结束事件。 */
        unsigned int  OTGADevEvtInfo        : 1;  /* bit[17]   : 检测到SRP事件。 */
        unsigned int  OTGADevHNPChngEvnt    : 1;  /* bit[18]   : A-device HNP事件。仅对OTG2.0有效。 */
        unsigned int  OTGADevHostEvnt       : 1;  /* bit[19]   : A-device进入host角色事件。 */
        unsigned int  OTGADevBHostEndEvnt   : 1;  /* bit[20]   : 当前模式为A-device模式，B-device完成host角色事件。 */
        unsigned int  OTGADevIdleEvnt       : 1;  /* bit[21]   : A-device进入A-IDLE状态事件。 */
        unsigned int  HRRInitNotifEvnt      : 1;  /* bit[22]   : 作为A-host或者B-host，控制器收到带initial位的Host Role Request Device Notification TP时，该bit置位。 */
        unsigned int  HRRConfNotifEvnt      : 1;  /* bit[23]   : Host Role Request确认通知事件。
                                                                 作为A-host或者B-host，控制器收到带Confrim位的Host Role Request Device Notification TP时，该bit置位。 */
        unsigned int  OTGConIDStsChngEvnt   : 1;  /* bit[24]   : ID状态变化事件。 */
        unsigned int  OTGHibEntryEvnt       : 1;  /* bit[25]   : 进入冬眠事件。 */
        unsigned int  OTGDevRunStpSetEcnt   : 1;  /* bit[26]   : Device Run/Stop配置事件。 */
        unsigned int  OTGXhciRunStpSetEvnt  : 1;  /* bit[27]   : Host Run/Stop配置事件。 */
        unsigned int  reserved_2            : 3;  /* bit[28-30]: 保留。 */
        unsigned int  DeviceMode            : 1;  /* bit[31]   : 当前模式。
                                                                 0：A-device；
                                                                 1：B-device。 */
    } reg;
} SOC_USB3OTG_OEVNT_UNION;
#endif
#define SOC_USB3OTG_OEVNT_OEVNTError_START             (0)
#define SOC_USB3OTG_OEVNT_OEVNTError_END               (0)
#define SOC_USB3OTG_OEVNT_SesReqSts_START              (1)
#define SOC_USB3OTG_OEVNT_SesReqSts_END                (1)
#define SOC_USB3OTG_OEVNT_HstNegStss_START             (2)
#define SOC_USB3OTG_OEVNT_HstNegStss_END               (2)
#define SOC_USB3OTG_OEVNT_BSesVld_START                (3)
#define SOC_USB3OTG_OEVNT_BSesVld_END                  (3)
#define SOC_USB3OTG_OEVNT_OTGBVbsChg_START             (8)
#define SOC_USB3OTG_OEVNT_OTGBVbsChg_END               (8)
#define SOC_USB3OTG_OEVNT_OTGBSrpChg_START             (9)
#define SOC_USB3OTG_OEVNT_OTGBSrpChg_END               (9)
#define SOC_USB3OTG_OEVNT_OTGBHnpChg_START             (10)
#define SOC_USB3OTG_OEVNT_OTGBHnpChg_END               (10)
#define SOC_USB3OTG_OEVNT_OTGBDevBHostEndEvnt_START    (11)
#define SOC_USB3OTG_OEVNT_OTGBDevBHostEndEvnt_END      (11)
#define SOC_USB3OTG_OEVNT_OTGADevSessEndDetEvnt_START  (16)
#define SOC_USB3OTG_OEVNT_OTGADevSessEndDetEvnt_END    (16)
#define SOC_USB3OTG_OEVNT_OTGADevEvtInfo_START         (17)
#define SOC_USB3OTG_OEVNT_OTGADevEvtInfo_END           (17)
#define SOC_USB3OTG_OEVNT_OTGADevHNPChngEvnt_START     (18)
#define SOC_USB3OTG_OEVNT_OTGADevHNPChngEvnt_END       (18)
#define SOC_USB3OTG_OEVNT_OTGADevHostEvnt_START        (19)
#define SOC_USB3OTG_OEVNT_OTGADevHostEvnt_END          (19)
#define SOC_USB3OTG_OEVNT_OTGADevBHostEndEvnt_START    (20)
#define SOC_USB3OTG_OEVNT_OTGADevBHostEndEvnt_END      (20)
#define SOC_USB3OTG_OEVNT_OTGADevIdleEvnt_START        (21)
#define SOC_USB3OTG_OEVNT_OTGADevIdleEvnt_END          (21)
#define SOC_USB3OTG_OEVNT_HRRInitNotifEvnt_START       (22)
#define SOC_USB3OTG_OEVNT_HRRInitNotifEvnt_END         (22)
#define SOC_USB3OTG_OEVNT_HRRConfNotifEvnt_START       (23)
#define SOC_USB3OTG_OEVNT_HRRConfNotifEvnt_END         (23)
#define SOC_USB3OTG_OEVNT_OTGConIDStsChngEvnt_START    (24)
#define SOC_USB3OTG_OEVNT_OTGConIDStsChngEvnt_END      (24)
#define SOC_USB3OTG_OEVNT_OTGHibEntryEvnt_START        (25)
#define SOC_USB3OTG_OEVNT_OTGHibEntryEvnt_END          (25)
#define SOC_USB3OTG_OEVNT_OTGDevRunStpSetEcnt_START    (26)
#define SOC_USB3OTG_OEVNT_OTGDevRunStpSetEcnt_END      (26)
#define SOC_USB3OTG_OEVNT_OTGXhciRunStpSetEvnt_START   (27)
#define SOC_USB3OTG_OEVNT_OTGXhciRunStpSetEvnt_END     (27)
#define SOC_USB3OTG_OEVNT_DeviceMode_START             (31)
#define SOC_USB3OTG_OEVNT_DeviceMode_END               (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_OEVNTEN_UNION
 结构说明  : OEVNTEN 寄存器结构定义。地址偏移量:0xCC0C，初值:0x0000，宽度:32
 寄存器说明: OTG事件使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 8;  /* bit[0-7]  : 保留。 */
        unsigned int  OTGBVbsChgEn            : 1;  /* bit[8]    : OTGBVbsChg事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGBSrpChgEn            : 1;  /* bit[9]    : OTGBSrpChg事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGBHnpChgEn            : 1;  /* bit[10]   : OTGBHnpChg事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGBDevBHostEndEvntEn   : 1;  /* bit[11]   : OTGBDevBHostEndEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  reserved_1              : 4;  /* bit[12-15]: 保留。 */
        unsigned int  OTGADevSessEndDetEvntEn : 1;  /* bit[16]   : OTGADevSessEnd事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGADevEvtInfoEn        : 1;  /* bit[17]   : OTGADevEvtInfo事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGADevHNPChngEvntEn    : 1;  /* bit[18]   : OTGADevHNPChngEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGADevHostEvntEn       : 1;  /* bit[19]   : OTGADevHostEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGADevBHostEndEvntEn   : 1;  /* bit[20]   : OTGADevBHostEndEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGADevIdleEvntEn       : 1;  /* bit[21]   : OTGADevIdleEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  HRRInitNotifEvntEn      : 1;  /* bit[22]   : HRRInitNotifEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  HRRConfNotifEvntEn      : 1;  /* bit[23]   : HRRConfNotifEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGConIDStsChngEvntEn   : 1;  /* bit[24]   : OTGConIDStsChngEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGHibEntryEvntEn       : 1;  /* bit[25]   : OTGHibEntryEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGDevRunStpSetEcntEn   : 1;  /* bit[26]   : OTGDevRunStpSetEcnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  OTGXhciRunStpSetEvntEn  : 1;  /* bit[27]   : OTGXhciRunStpSetEvnt事件使能。
                                                                   0：不使能；
                                                                   1：使能。 */
        unsigned int  reserved_2              : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_USB3OTG_OEVNTEN_UNION;
#endif
#define SOC_USB3OTG_OEVNTEN_OTGBVbsChgEn_START             (8)
#define SOC_USB3OTG_OEVNTEN_OTGBVbsChgEn_END               (8)
#define SOC_USB3OTG_OEVNTEN_OTGBSrpChgEn_START             (9)
#define SOC_USB3OTG_OEVNTEN_OTGBSrpChgEn_END               (9)
#define SOC_USB3OTG_OEVNTEN_OTGBHnpChgEn_START             (10)
#define SOC_USB3OTG_OEVNTEN_OTGBHnpChgEn_END               (10)
#define SOC_USB3OTG_OEVNTEN_OTGBDevBHostEndEvntEn_START    (11)
#define SOC_USB3OTG_OEVNTEN_OTGBDevBHostEndEvntEn_END      (11)
#define SOC_USB3OTG_OEVNTEN_OTGADevSessEndDetEvntEn_START  (16)
#define SOC_USB3OTG_OEVNTEN_OTGADevSessEndDetEvntEn_END    (16)
#define SOC_USB3OTG_OEVNTEN_OTGADevEvtInfoEn_START         (17)
#define SOC_USB3OTG_OEVNTEN_OTGADevEvtInfoEn_END           (17)
#define SOC_USB3OTG_OEVNTEN_OTGADevHNPChngEvntEn_START     (18)
#define SOC_USB3OTG_OEVNTEN_OTGADevHNPChngEvntEn_END       (18)
#define SOC_USB3OTG_OEVNTEN_OTGADevHostEvntEn_START        (19)
#define SOC_USB3OTG_OEVNTEN_OTGADevHostEvntEn_END          (19)
#define SOC_USB3OTG_OEVNTEN_OTGADevBHostEndEvntEn_START    (20)
#define SOC_USB3OTG_OEVNTEN_OTGADevBHostEndEvntEn_END      (20)
#define SOC_USB3OTG_OEVNTEN_OTGADevIdleEvntEn_START        (21)
#define SOC_USB3OTG_OEVNTEN_OTGADevIdleEvntEn_END          (21)
#define SOC_USB3OTG_OEVNTEN_HRRInitNotifEvntEn_START       (22)
#define SOC_USB3OTG_OEVNTEN_HRRInitNotifEvntEn_END         (22)
#define SOC_USB3OTG_OEVNTEN_HRRConfNotifEvntEn_START       (23)
#define SOC_USB3OTG_OEVNTEN_HRRConfNotifEvntEn_END         (23)
#define SOC_USB3OTG_OEVNTEN_OTGConIDStsChngEvntEn_START    (24)
#define SOC_USB3OTG_OEVNTEN_OTGConIDStsChngEvntEn_END      (24)
#define SOC_USB3OTG_OEVNTEN_OTGHibEntryEvntEn_START        (25)
#define SOC_USB3OTG_OEVNTEN_OTGHibEntryEvntEn_END          (25)
#define SOC_USB3OTG_OEVNTEN_OTGDevRunStpSetEcntEn_START    (26)
#define SOC_USB3OTG_OEVNTEN_OTGDevRunStpSetEcntEn_END      (26)
#define SOC_USB3OTG_OEVNTEN_OTGXhciRunStpSetEvntEn_START   (27)
#define SOC_USB3OTG_OEVNTEN_OTGXhciRunStpSetEvntEn_END     (27)


/*****************************************************************************
 结构名    : SOC_USB3OTG_OSTS_UNION
 结构说明  : OSTS 寄存器结构定义。地址偏移量:0xCC10，初值:0x0000，宽度:32
 寄存器说明: OTG状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ConIDSts        : 1;  /* bit[0]    : ID状态。
                                                           0：A-device；
                                                           1：B-device。 */
        unsigned int  VbusVld         : 1;  /* bit[1]    : VBUS有效状态。
                                                           0：无效；
                                                           1：有效。 */
        unsigned int  BSesVld         : 1;  /* bit[2]    : B会话有效状态。
                                                           0：无效；
                                                           1：有效。 */
        unsigned int  xHCIPrtPower    : 1;  /* bit[3]    : xHCI PORTSC.PP状态。 */
        unsigned int  PeripheralState : 1;  /* bit[4]    : 模式状态。
                                                           0：Host；
                                                           1：Peripheral。 */
        unsigned int  reserved_0      : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  OTG2State       : 4;  /* bit[8-11] : OTG 2.0状态。
                                                           0000：A_IDLE；
                                                           0001: A_WAIT_VRISE；
                                                           0010: A_WAIT_BCON；
                                                           0011: A_WAIT_VFALL；
                                                           0100: A_VBUS_ERR；
                                                           0101: A_HOST；
                                                           0110: A_SUSPEND；
                                                           1111: A_PERIPHERAL；
                                                           0111: A_WAIT_PPWR；
                                                           1000: B_IDLE；
                                                           1001: B_SRP_INIT；
                                                           1010: B_PERIPHERAL；
                                                           1011: B_WAIT_ACON；
                                                           1100: b_HOST；
                                                           1101: A_WAIT_SWITCH；
                                                           1110: B_WAIT_SWITCH；
                                                           others：reserved。 */
        unsigned int  HstRunStp       : 1;  /* bit[12]   : Host Run/Stop状态。
                                                           0：Run/Stop设置为0；
                                                           1：Run/Stop设置为1。 */
        unsigned int  DevRunStp       : 1;  /* bit[13]   : Device Run/Stop状态。
                                                           0：Run/Stop设置为0；
                                                           1：Run/Stop设置为1。 */
        unsigned int  reserved_1      : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_USB3OTG_OSTS_UNION;
#endif
#define SOC_USB3OTG_OSTS_ConIDSts_START         (0)
#define SOC_USB3OTG_OSTS_ConIDSts_END           (0)
#define SOC_USB3OTG_OSTS_VbusVld_START          (1)
#define SOC_USB3OTG_OSTS_VbusVld_END            (1)
#define SOC_USB3OTG_OSTS_BSesVld_START          (2)
#define SOC_USB3OTG_OSTS_BSesVld_END            (2)
#define SOC_USB3OTG_OSTS_xHCIPrtPower_START     (3)
#define SOC_USB3OTG_OSTS_xHCIPrtPower_END       (3)
#define SOC_USB3OTG_OSTS_PeripheralState_START  (4)
#define SOC_USB3OTG_OSTS_PeripheralState_END    (4)
#define SOC_USB3OTG_OSTS_OTG2State_START        (8)
#define SOC_USB3OTG_OSTS_OTG2State_END          (11)
#define SOC_USB3OTG_OSTS_HstRunStp_START        (12)
#define SOC_USB3OTG_OSTS_HstRunStp_END          (12)
#define SOC_USB3OTG_OSTS_DevRunStp_START        (13)
#define SOC_USB3OTG_OSTS_DevRunStp_END          (13)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ADPCFG_UNION
 结构说明  : ADPCFG 寄存器结构定义。地址偏移量:0xCC20，初值:0x0000，宽度:32
 寄存器说明: ADP配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved   : 26; /* bit[0-25] : 保留。 */
        unsigned int  PrbDschg   : 2;  /* bit[26-27]: Probe放电时间。
                                                      00：4ms
                                                      01：8ms
                                                      10：16ms
                                                      11：32ms */
        unsigned int  ProbeDelta : 2;  /* bit[28-29]: Probe Delta配置，以32KHz时钟周期为单位。
                                                      00：1个时钟周期
                                                      01：2个时钟周期
                                                      10：3个时钟周期
                                                      11：4个时钟周期 */
        unsigned int  PrbPer     : 2;  /* bit[30-31]: Probe周期配置。
                                                      00：0.775秒
                                                      01：1.55秒
                                                      10：2.275秒
                                                      11：reserved */
    } reg;
} SOC_USB3OTG_ADPCFG_UNION;
#endif
#define SOC_USB3OTG_ADPCFG_PrbDschg_START    (26)
#define SOC_USB3OTG_ADPCFG_PrbDschg_END      (27)
#define SOC_USB3OTG_ADPCFG_ProbeDelta_START  (28)
#define SOC_USB3OTG_ADPCFG_ProbeDelta_END    (29)
#define SOC_USB3OTG_ADPCFG_PrbPer_START      (30)
#define SOC_USB3OTG_ADPCFG_PrbPer_END        (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ADPCTL_UNION
 结构说明  : ADPCTL 寄存器结构定义。地址偏移量:0xCC24，初值:0x0000，宽度:32
 寄存器说明: ADP控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 24; /* bit[0-23] : 保留。 */
        unsigned int  WB       : 1;  /* bit[24]   : 写busy状态。
                                                    软件在该bit为0的情况下才能读写ADPCFG和ADPCTL寄存器。 */
        unsigned int  ADPRes   : 1;  /* bit[25]   : ADP复位。配置为1复位ADP控制器，复位完成该bit自动清零。 */
        unsigned int  ADPEn    : 1;  /* bit[26]   : ADP使能。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  EnaSns   : 1;  /* bit[27]   : Sense使能。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  EnaPrb   : 1;  /* bit[28]   : Probe使能。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned int  reserved_1: 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_USB3OTG_ADPCTL_UNION;
#endif
#define SOC_USB3OTG_ADPCTL_WB_START        (24)
#define SOC_USB3OTG_ADPCTL_WB_END          (24)
#define SOC_USB3OTG_ADPCTL_ADPRes_START    (25)
#define SOC_USB3OTG_ADPCTL_ADPRes_END      (25)
#define SOC_USB3OTG_ADPCTL_ADPEn_START     (26)
#define SOC_USB3OTG_ADPCTL_ADPEn_END       (26)
#define SOC_USB3OTG_ADPCTL_EnaSns_START    (27)
#define SOC_USB3OTG_ADPCTL_EnaSns_END      (27)
#define SOC_USB3OTG_ADPCTL_EnaPrb_START    (28)
#define SOC_USB3OTG_ADPCTL_EnaPrb_END      (28)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ADPEVNT_UNION
 结构说明  : ADPEVNT 寄存器结构定义。地址偏移量:0xCC28，初值:0x0000，宽度:32
 寄存器说明: ADP事件寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RTIM            : 16; /* bit[0-15] : RAMP时间。 */
        unsigned int  reserved_0      : 9;  /* bit[16-24]: 保留。 */
        unsigned int  ADPRstCmpltEvnt : 1;  /* bit[25]   : ADP复位完成事件。 */
        unsigned int  ADPTimeoutEvnt  : 1;  /* bit[26]   : ADP超时事件。 */
        unsigned int  ADPSnsEvnt      : 1;  /* bit[27]   : ADP Sense事件。 */
        unsigned int  ADPEVTInfo      : 1;  /* bit[28]   : ADP Probe事件。 */
        unsigned int  reserved_1      : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_USB3OTG_ADPEVNT_UNION;
#endif
#define SOC_USB3OTG_ADPEVNT_RTIM_START             (0)
#define SOC_USB3OTG_ADPEVNT_RTIM_END               (15)
#define SOC_USB3OTG_ADPEVNT_ADPRstCmpltEvnt_START  (25)
#define SOC_USB3OTG_ADPEVNT_ADPRstCmpltEvnt_END    (25)
#define SOC_USB3OTG_ADPEVNT_ADPTimeoutEvnt_START   (26)
#define SOC_USB3OTG_ADPEVNT_ADPTimeoutEvnt_END     (26)
#define SOC_USB3OTG_ADPEVNT_ADPSnsEvnt_START       (27)
#define SOC_USB3OTG_ADPEVNT_ADPSnsEvnt_END         (27)
#define SOC_USB3OTG_ADPEVNT_ADPEVTInfo_START       (28)
#define SOC_USB3OTG_ADPEVNT_ADPEVTInfo_END         (28)


/*****************************************************************************
 结构名    : SOC_USB3OTG_ADPEVNTEN_UNION
 结构说明  : ADPEVNTEN 寄存器结构定义。地址偏移量:0xCC28，初值:0x0000，宽度:32
 寄存器说明: ADP事件寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 25; /* bit[0-24] : 保留。 */
        unsigned int  ADPRstCmpltEvntEn : 1;  /* bit[25]   : ADP复位完成事件使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  ADPTimeoutEvntEn  : 1;  /* bit[26]   : ADP超时事件使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  ADPSnsEvntEn      : 1;  /* bit[27]   : ADP Sense事件使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  ADPEVTInfoEn      : 1;  /* bit[28]   : ADP Probe事件使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  reserved_1        : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_USB3OTG_ADPEVNTEN_UNION;
#endif
#define SOC_USB3OTG_ADPEVNTEN_ADPRstCmpltEvntEn_START  (25)
#define SOC_USB3OTG_ADPEVNTEN_ADPRstCmpltEvntEn_END    (25)
#define SOC_USB3OTG_ADPEVNTEN_ADPTimeoutEvntEn_START   (26)
#define SOC_USB3OTG_ADPEVNTEN_ADPTimeoutEvntEn_END     (26)
#define SOC_USB3OTG_ADPEVNTEN_ADPSnsEvntEn_START       (27)
#define SOC_USB3OTG_ADPEVNTEN_ADPSnsEvntEn_END         (27)
#define SOC_USB3OTG_ADPEVNTEN_ADPEVTInfoEn_START       (28)
#define SOC_USB3OTG_ADPEVNTEN_ADPEVTInfoEn_END         (28)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BCFG_UNION
 结构说明  : BCFG 寄存器结构定义。地址偏移量:0xCC30，初值:0x00000000，宽度:32
 寄存器说明: BC配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chirp_en  : 1;  /* bit[0]   : chirp使能。保留。 */
        unsigned int  IDDIG_SEL : 1;  /* bit[1]   : IDDIG选择。
                                                    1：控制器由RID_A和RID_GND的值来决定ID的值
                                                    0：ID的值取决于控制器端口上的IDDIG输入 */
        unsigned int  reserved  : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BCFG_UNION;
#endif
#define SOC_USB3OTG_BCFG_chirp_en_START   (0)
#define SOC_USB3OTG_BCFG_chirp_en_END     (0)
#define SOC_USB3OTG_BCFG_IDDIG_SEL_START  (1)
#define SOC_USB3OTG_BCFG_IDDIG_SEL_END    (1)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BCEVT_UNION
 结构说明  : BCEVT 寄存器结构定义。地址偏移量:0xCC38，初值:0x00000000，宽度:32
 寄存器说明: BC事件寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MultValIdBc : 5;  /* bit[0-4]  : 充电检测ACA接口上的值。
                                                       [4]:bc_rid_float
                                                       [3]:bc_rid_gnd
                                                       [2]:bc_rid_a
                                                       [1]:bc_rid_b
                                                       [0]:bc_rid_c */
        unsigned int  reserved_0  : 19; /* bit[5-23] : 保留。 */
        unsigned int  mv_chngevnt : 1;  /* bit[24]   : 指示ACA接口上的值的变化事件。 */
        unsigned int  reserved_1  : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BCEVT_UNION;
#endif
#define SOC_USB3OTG_BCEVT_MultValIdBc_START  (0)
#define SOC_USB3OTG_BCEVT_MultValIdBc_END    (4)
#define SOC_USB3OTG_BCEVT_mv_chngevnt_START  (24)
#define SOC_USB3OTG_BCEVT_mv_chngevnt_END    (24)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BCEVTEN_UNION
 结构说明  : BCEVTEN 寄存器结构定义。地址偏移量:0xCC3C，初值:0x00000000，宽度:32
 寄存器说明: BC事件使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0     : 24; /* bit[0-23] : 保留。 */
        unsigned int  mv_chngevntena : 1;  /* bit[24]   : 使能ACA值的变化事件。 */
        unsigned int  reserved_1     : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BCEVTEN_UNION;
#endif
#define SOC_USB3OTG_BCEVTEN_mv_chngevntena_START  (24)
#define SOC_USB3OTG_BCEVTEN_mv_chngevntena_END    (24)






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

#endif /* end of soc_usb3otg_interface.h */
